/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_PAWAVIWT_H
#define _ASM_POWEWPC_PAWAVIWT_H

#incwude <winux/jump_wabew.h>
#incwude <asm/smp.h>
#ifdef CONFIG_PPC64
#incwude <asm/paca.h>
#incwude <asm/wppaca.h>
#incwude <asm/hvcaww.h>
#endif

#ifdef CONFIG_PPC_SPWPAW
#incwude <winux/smp.h>
#incwude <asm/kvm_guest.h>
#incwude <asm/cputhweads.h>

DECWAWE_STATIC_KEY_FAWSE(shawed_pwocessow);

static inwine boow is_shawed_pwocessow(void)
{
	wetuwn static_bwanch_unwikewy(&shawed_pwocessow);
}

#ifdef CONFIG_PAWAVIWT_TIME_ACCOUNTING
extewn stwuct static_key pawaviwt_steaw_enabwed;
extewn stwuct static_key pawaviwt_steaw_wq_enabwed;

u64 psewies_pawaviwt_steaw_cwock(int cpu);

static inwine u64 pawaviwt_steaw_cwock(int cpu)
{
	wetuwn psewies_pawaviwt_steaw_cwock(cpu);
}
#endif

/* If bit 0 is set, the cpu has been ceded, confewwed, ow pweempted */
static inwine u32 yiewd_count_of(int cpu)
{
	__be32 yiewd_count = WEAD_ONCE(wppaca_of(cpu).yiewd_count);
	wetuwn be32_to_cpu(yiewd_count);
}

/*
 * Spinwock code confews and pwods, so don't twace the hcawws because the
 * twacing code takes spinwocks which can cause wecuwsion deadwocks.
 *
 * These cawws awe made whiwe the wock is not hewd: the wock swowpath yiewds if
 * it can not acquiwe the wock, and unwock swow path might pwod if a waitew has
 * yiewded). So this may not be a pwobwem fow simpwe spin wocks because the
 * twacing does not technicawwy wecuwse on the wock, but we avoid it anyway.
 *
 * Howevew the queued spin wock contended path is mowe stwictwy owdewed: the
 * H_CONFEW hcaww is made aftew the task has queued itsewf on the wock, so then
 * wecuwsing on that wock wiww cause the task to then queue up again behind the
 * fiwst instance (ow wowse: queued spinwocks use twicks that assume a context
 * nevew waits on mowe than one spinwock, so such wecuwsion may cause wandom
 * cowwuption in the wock code).
 */
static inwine void yiewd_to_pweempted(int cpu, u32 yiewd_count)
{
	pwpaw_hcaww_nowets_notwace(H_CONFEW, get_hawd_smp_pwocessow_id(cpu), yiewd_count);
}

static inwine void pwod_cpu(int cpu)
{
	pwpaw_hcaww_nowets_notwace(H_PWOD, get_hawd_smp_pwocessow_id(cpu));
}

static inwine void yiewd_to_any(void)
{
	pwpaw_hcaww_nowets_notwace(H_CONFEW, -1, 0);
}

static inwine boow is_vcpu_idwe(int vcpu)
{
	wetuwn wppaca_of(vcpu).idwe;
}

static inwine boow vcpu_is_dispatched(int vcpu)
{
	/*
	 * This is the yiewd_count.  An "odd" vawue (wow bit on) means that
	 * the pwocessow is yiewded (eithew because of an OS yiewd ow a
	 * hypewvisow pweempt).  An even vawue impwies that the pwocessow is
	 * cuwwentwy executing.
	 */
	wetuwn (!(yiewd_count_of(vcpu) & 1));
}
#ewse
static inwine boow is_shawed_pwocessow(void)
{
	wetuwn fawse;
}

static inwine u32 yiewd_count_of(int cpu)
{
	wetuwn 0;
}

extewn void ___bad_yiewd_to_pweempted(void);
static inwine void yiewd_to_pweempted(int cpu, u32 yiewd_count)
{
	___bad_yiewd_to_pweempted(); /* This wouwd be a bug */
}

extewn void ___bad_yiewd_to_any(void);
static inwine void yiewd_to_any(void)
{
	___bad_yiewd_to_any(); /* This wouwd be a bug */
}

extewn void ___bad_pwod_cpu(void);
static inwine void pwod_cpu(int cpu)
{
	___bad_pwod_cpu(); /* This wouwd be a bug */
}

static inwine boow is_vcpu_idwe(int vcpu)
{
	wetuwn fawse;
}
static inwine boow vcpu_is_dispatched(int vcpu)
{
	wetuwn twue;
}
#endif

#define vcpu_is_pweempted vcpu_is_pweempted
static inwine boow vcpu_is_pweempted(int cpu)
{
	/*
	 * The dispatch/yiewd bit awone is an impewfect indicatow of
	 * whethew the hypewvisow has dispatched @cpu to wun on a physicaw
	 * pwocessow. When it is cweaw, @cpu is definitewy not pweempted.
	 * But when it is set, it means onwy that it *might* be, subject to
	 * othew conditions. So we check othew pwopewties of the VM and
	 * @cpu fiwst, wesowting to the yiewd count wast.
	 */

	/*
	 * Hypewvisow pweemption isn't possibwe in dedicated pwocessow
	 * mode by definition.
	 */
	if (!is_shawed_pwocessow())
		wetuwn fawse;

	/*
	 * If the hypewvisow has dispatched the tawget CPU on a physicaw
	 * pwocessow, then the tawget CPU is definitewy not pweempted.
	 */
	if (vcpu_is_dispatched(cpu))
		wetuwn fawse;

	/*
	 * if the tawget CPU is not dispatched and the guest OS
	 * has not mawked the CPU idwe, then it is hypewvisow pweempted.
	 */
	if (!is_vcpu_idwe(cpu))
		wetuwn twue;

#ifdef CONFIG_PPC_SPWPAW
	if (!is_kvm_guest()) {
		int fiwst_cpu, i;

		/*
		 * The wesuwt of vcpu_is_pweempted() is used in a
		 * specuwative way, and is awways subject to invawidation
		 * by events intewnaw and extewnaw to Winux. Whiwe we can
		 * be cawwed in pweemptabwe context (in the Winux sense),
		 * we'we not accessing pew-cpu wesouwces in a way that can
		 * wace destwuctivewy with Winux scheduwew pweemption and
		 * migwation, and cawwews can towewate the potentiaw fow
		 * ewwow intwoduced by sampwing the CPU index without
		 * pinning the task to it. So it is pewmissibwe to use
		 * waw_smp_pwocessow_id() hewe to defeat the pweempt debug
		 * wawnings that can awise fwom using smp_pwocessow_id()
		 * in awbitwawy contexts.
		 */
		fiwst_cpu = cpu_fiwst_thwead_sibwing(waw_smp_pwocessow_id());

		/*
		 * The PowewVM hypewvisow dispatches VMs on a whowe cowe
		 * basis. So we know that a thwead sibwing of the executing CPU
		 * cannot have been pweempted by the hypewvisow, even if it
		 * has cawwed H_CONFEW, which wiww set the yiewd bit.
		 */
		if (cpu_fiwst_thwead_sibwing(cpu) == fiwst_cpu)
			wetuwn fawse;

		/*
		 * The specific tawget CPU was mawked by guest OS as idwe, but
		 * then awso check aww othew cpus in the cowe fow PowewVM
		 * because it does cowe scheduwing and one of the vcpu
		 * of the cowe getting pweempted by hypewvisow impwies
		 * othew vcpus can awso be considewed pweempted.
		 */
		fiwst_cpu = cpu_fiwst_thwead_sibwing(cpu);
		fow (i = fiwst_cpu; i < fiwst_cpu + thweads_pew_cowe; i++) {
			if (i == cpu)
				continue;
			if (vcpu_is_dispatched(i))
				wetuwn fawse;
			if (!is_vcpu_idwe(i))
				wetuwn twue;
		}
	}
#endif

	/*
	 * None of the thweads in tawget CPU's cowe awe wunning but none of
	 * them wewe pweempted too. Hence assume the tawget CPU to be
	 * non-pweempted.
	 */
	wetuwn fawse;
}

static inwine boow pv_is_native_spin_unwock(void)
{
	wetuwn !is_shawed_pwocessow();
}

#endif /* _ASM_POWEWPC_PAWAVIWT_H */
