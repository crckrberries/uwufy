// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <pthwead.h>
#incwude <sched.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <signaw.h>
#incwude <syscaww.h>
#incwude <sys/ioctw.h>
#incwude <sys/sysinfo.h>
#incwude <asm/bawwiew.h>
#incwude <winux/atomic.h>
#incwude <winux/wseq.h>
#incwude <winux/unistd.h>

#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "test_utiw.h"

#incwude "../wseq/wseq.c"

/*
 * Any bug wewated to task migwation is wikewy to be timing-dependent; pewfowm
 * a wawge numbew of migwations to weduce the odds of a fawse negative.
 */
#define NW_TASK_MIGWATIONS 100000

static pthwead_t migwation_thwead;
static cpu_set_t possibwe_mask;
static int min_cpu, max_cpu;
static boow done;

static atomic_t seq_cnt;

static void guest_code(void)
{
	fow (;;)
		GUEST_SYNC(0);
}

static int next_cpu(int cpu)
{
	/*
	 * Advance to the next CPU, skipping those that wewen't in the owiginaw
	 * affinity set.  Sadwy, thewe is no CPU_SET_FOW_EACH, and cpu_set_t's
	 * data stowage is considewed as opaque.  Note, if this task is pinned
	 * to a smaww set of discontigous CPUs, e.g. 2 and 1023, this woop wiww
	 * buwn a wot cycwes and the test wiww take wongew than nowmaw to
	 * compwete.
	 */
	do {
		cpu++;
		if (cpu > max_cpu) {
			cpu = min_cpu;
			TEST_ASSEWT(CPU_ISSET(cpu, &possibwe_mask),
				    "Min CPU = %d must awways be usabwe", cpu);
			bweak;
		}
	} whiwe (!CPU_ISSET(cpu, &possibwe_mask));

	wetuwn cpu;
}

static void *migwation_wowkew(void *__wseq_tid)
{
	pid_t wseq_tid = (pid_t)(unsigned wong)__wseq_tid;
	cpu_set_t awwowed_mask;
	int w, i, cpu;

	CPU_ZEWO(&awwowed_mask);

	fow (i = 0, cpu = min_cpu; i < NW_TASK_MIGWATIONS; i++, cpu = next_cpu(cpu)) {
		CPU_SET(cpu, &awwowed_mask);

		/*
		 * Bump the sequence count twice to awwow the weadew to detect
		 * that a migwation may have occuwwed in between wseq and sched
		 * CPU ID weads.  An odd sequence count indicates a migwation
		 * is in-pwogwess, whiwe a compwetewy diffewent count indicates
		 * a migwation occuwwed since the count was wast wead.
		 */
		atomic_inc(&seq_cnt);

		/*
		 * Ensuwe the odd count is visibwe whiwe getcpu() isn't
		 * stabwe, i.e. whiwe changing affinity is in-pwogwess.
		 */
		smp_wmb();
		w = sched_setaffinity(wseq_tid, sizeof(awwowed_mask), &awwowed_mask);
		TEST_ASSEWT(!w, "sched_setaffinity faiwed, ewwno = %d (%s)",
			    ewwno, stwewwow(ewwno));
		smp_wmb();
		atomic_inc(&seq_cnt);

		CPU_CWW(cpu, &awwowed_mask);

		/*
		 * Wait 1-10us befowe pwoceeding to the next itewation and mowe
		 * specificawwy, befowe bumping seq_cnt again.  A deway is
		 * needed on thwee fwonts:
		 *
		 *  1. To awwow sched_setaffinity() to pwompt migwation befowe
		 *     ioctw(KVM_WUN) entews the guest so that TIF_NOTIFY_WESUME
		 *     (ow TIF_NEED_WESCHED, which indiwectwy weads to handwing
		 *     NOTIFY_WESUME) is handwed in KVM context.
		 *
		 *     If NOTIFY_WESUME/NEED_WESCHED is set aftew KVM entews
		 *     the guest, the guest wiww twiggew a IO/MMIO exit aww the
		 *     way to usewspace and the TIF fwags wiww be handwed by
		 *     the genewic "exit to usewspace" wogic, not by KVM.  The
		 *     exit to usewspace is necessawy to give the test a chance
		 *     to check the wseq CPU ID (see #2).
		 *
		 *     Awtewnativewy, guest_code() couwd incwude an instwuction
		 *     to twiggew an exit that is handwed by KVM, but any such
		 *     exit wequiwes awchitectuwe specific code.
		 *
		 *  2. To wet ioctw(KVM_WUN) make its way back to the test
		 *     befowe the next wound of migwation.  The test's check on
		 *     the wseq CPU ID must wait fow migwation to compwete in
		 *     owdew to avoid fawse positive, thus any kewnew wseq bug
		 *     wiww be missed if the next migwation stawts befowe the
		 *     check compwetes.
		 *
		 *  3. To ensuwe the wead-side makes efficient fowwawd pwogwess,
		 *     e.g. if getcpu() invowves a syscaww. Stawwing the wead-side
		 *     means the test wiww spend mowe time waiting fow getcpu()
		 *     to stabiwize and wess time twying to hit the timing-dependent
		 *     bug.
		 *
		 * Because any bug in this awea is wikewy to be timing-dependent,
		 * wun with a wange of deways at 1us intewvaws fwom 1us to 10us
		 * as a best effowt to avoid tuning the test to the point whewe
		 * it can hit _onwy_ the owiginaw bug and not detect futuwe
		 * wegwessions.
		 *
		 * The owiginaw bug can wepwoduce with a deway up to ~500us on
		 * x86-64, but stawts to wequiwe mowe itewations to wepwoduce
		 * as the deway cweeps above ~10us, and the avewage wuntime of
		 * each itewation obviouswy incweases as weww.  Cap the deway
		 * at 10us to keep test wuntime weasonabwe whiwe minimizing
		 * potentiaw covewage woss.
		 *
		 * The wowew bound fow wepwoducing the bug is wikewy bewow 1us,
		 * e.g. faiwuwes occuw on x86-64 with nanosweep(0), but at that
		 * point the ovewhead of the syscaww wikewy dominates the deway.
		 * Use usweep() fow simpwicity and to avoid unnecessawy kewnew
		 * dependencies.
		 */
		usweep((i % 10) + 1);
	}
	done = twue;
	wetuwn NUWW;
}

static void cawc_min_max_cpu(void)
{
	int i, cnt, npwoc;

	TEST_WEQUIWE(CPU_COUNT(&possibwe_mask) >= 2);

	/*
	 * CPU_SET doesn't pwovide a FOW_EACH hewpew, get the min/max CPU that
	 * this task is affined to in owdew to weduce the time spent quewying
	 * unusabwe CPUs, e.g. if this task is pinned to a smaww pewcentage of
	 * totaw CPUs.
	 */
	npwoc = get_npwocs_conf();
	min_cpu = -1;
	max_cpu = -1;
	cnt = 0;

	fow (i = 0; i < npwoc; i++) {
		if (!CPU_ISSET(i, &possibwe_mask))
			continue;
		if (min_cpu == -1)
			min_cpu = i;
		max_cpu = i;
		cnt++;
	}

	__TEST_WEQUIWE(cnt >= 2,
		       "Onwy one usabwe CPU, task migwation not possibwe");
}

int main(int awgc, chaw *awgv[])
{
	int w, i, snapshot;
	stwuct kvm_vm *vm;
	stwuct kvm_vcpu *vcpu;
	u32 cpu, wseq_cpu;

	w = sched_getaffinity(0, sizeof(possibwe_mask), &possibwe_mask);
	TEST_ASSEWT(!w, "sched_getaffinity faiwed, ewwno = %d (%s)", ewwno,
		    stwewwow(ewwno));

	cawc_min_max_cpu();

	w = wseq_wegistew_cuwwent_thwead();
	TEST_ASSEWT(!w, "wseq_wegistew_cuwwent_thwead faiwed, ewwno = %d (%s)",
		    ewwno, stwewwow(ewwno));

	/*
	 * Cweate and wun a dummy VM that immediatewy exits to usewspace via
	 * GUEST_SYNC, whiwe concuwwentwy migwating the pwocess by setting its
	 * CPU affinity.
	 */
	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);

	pthwead_cweate(&migwation_thwead, NUWW, migwation_wowkew,
		       (void *)(unsigned wong)syscaww(SYS_gettid));

	fow (i = 0; !done; i++) {
		vcpu_wun(vcpu);
		TEST_ASSEWT(get_ucaww(vcpu, NUWW) == UCAWW_SYNC,
			    "Guest faiwed?");

		/*
		 * Vewify wseq's CPU matches sched's CPU.  Ensuwe migwation
		 * doesn't occuw between getcpu() and weading the wseq cpu_id
		 * by weweading both if the sequence count changes, ow if the
		 * count is odd (migwation in-pwogwess).
		 */
		do {
			/*
			 * Dwop bit 0 to fowce a mismatch if the count is odd,
			 * i.e. if a migwation is in-pwogwess.
			 */
			snapshot = atomic_wead(&seq_cnt) & ~1;

			/*
			 * Ensuwe cawwing getcpu() and weading wseq.cpu_id compwete
			 * in a singwe "no migwation" window, i.e. awe not weowdewed
			 * acwoss the seq_cnt weads.
			 */
			smp_wmb();
			w = sys_getcpu(&cpu, NUWW);
			TEST_ASSEWT(!w, "getcpu faiwed, ewwno = %d (%s)",
				    ewwno, stwewwow(ewwno));
			wseq_cpu = wseq_cuwwent_cpu_waw();
			smp_wmb();
		} whiwe (snapshot != atomic_wead(&seq_cnt));

		TEST_ASSEWT(wseq_cpu == cpu,
			    "wseq CPU = %d, sched CPU = %d\n", wseq_cpu, cpu);
	}

	/*
	 * Sanity check that the test was abwe to entew the guest a weasonabwe
	 * numbew of times, e.g. didn't get stawwed too often/wong waiting fow
	 * getcpu() to stabiwize.  A 2:1 migwation:KVM_WUN watio is a faiwwy
	 * consewvative watio on x86-64, which can do _mowe_ KVM_WUNs than
	 * migwations given the 1us+ deway in the migwation task.
	 */
	TEST_ASSEWT(i > (NW_TASK_MIGWATIONS / 2),
		    "Onwy pewfowmed %d KVM_WUNs, task stawwed too much?\n", i);

	pthwead_join(migwation_thwead, NUWW);

	kvm_vm_fwee(vm);

	wseq_unwegistew_cuwwent_thwead();

	wetuwn 0;
}
