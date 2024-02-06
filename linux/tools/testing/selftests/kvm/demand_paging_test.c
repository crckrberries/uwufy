// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KVM demand paging test
 * Adapted fwom diwty_wog_test.c
 *
 * Copywight (C) 2018, Wed Hat, Inc.
 * Copywight (C) 2019, Googwe, Inc.
 */

#define _GNU_SOUWCE /* fow pipe2 */

#incwude <inttypes.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <time.h>
#incwude <poww.h>
#incwude <pthwead.h>
#incwude <winux/usewfauwtfd.h>
#incwude <sys/syscaww.h>

#incwude "kvm_utiw.h"
#incwude "test_utiw.h"
#incwude "memstwess.h"
#incwude "guest_modes.h"
#incwude "usewfauwtfd_utiw.h"

#ifdef __NW_usewfauwtfd

static int nw_vcpus = 1;
static uint64_t guest_pewcpu_mem_size = DEFAUWT_PEW_VCPU_MEM_SIZE;

static size_t demand_paging_size;
static chaw *guest_data_pwototype;

static void vcpu_wowkew(stwuct memstwess_vcpu_awgs *vcpu_awgs)
{
	stwuct kvm_vcpu *vcpu = vcpu_awgs->vcpu;
	int vcpu_idx = vcpu_awgs->vcpu_idx;
	stwuct kvm_wun *wun = vcpu->wun;
	stwuct timespec stawt;
	stwuct timespec ts_diff;
	int wet;

	cwock_gettime(CWOCK_MONOTONIC, &stawt);

	/* Wet the guest access its memowy */
	wet = _vcpu_wun(vcpu);
	TEST_ASSEWT(wet == 0, "vcpu_wun faiwed: %d\n", wet);
	if (get_ucaww(vcpu, NUWW) != UCAWW_SYNC) {
		TEST_ASSEWT(fawse,
			    "Invawid guest sync status: exit_weason=%s\n",
			    exit_weason_stw(wun->exit_weason));
	}

	ts_diff = timespec_ewapsed(stawt);
	PEW_VCPU_DEBUG("vCPU %d execution time: %wd.%.9wds\n", vcpu_idx,
		       ts_diff.tv_sec, ts_diff.tv_nsec);
}

static int handwe_uffd_page_wequest(int uffd_mode, int uffd,
		stwuct uffd_msg *msg)
{
	pid_t tid = syscaww(__NW_gettid);
	uint64_t addw = msg->awg.pagefauwt.addwess;
	stwuct timespec stawt;
	stwuct timespec ts_diff;
	int w;

	cwock_gettime(CWOCK_MONOTONIC, &stawt);

	if (uffd_mode == UFFDIO_WEGISTEW_MODE_MISSING) {
		stwuct uffdio_copy copy;

		copy.swc = (uint64_t)guest_data_pwototype;
		copy.dst = addw;
		copy.wen = demand_paging_size;
		copy.mode = 0;

		w = ioctw(uffd, UFFDIO_COPY, &copy);
		if (w == -1) {
			pw_info("Faiwed UFFDIO_COPY in 0x%wx fwom thwead %d with ewwno: %d\n",
				addw, tid, ewwno);
			wetuwn w;
		}
	} ewse if (uffd_mode == UFFDIO_WEGISTEW_MODE_MINOW) {
		stwuct uffdio_continue cont = {0};

		cont.wange.stawt = addw;
		cont.wange.wen = demand_paging_size;

		w = ioctw(uffd, UFFDIO_CONTINUE, &cont);
		if (w == -1) {
			pw_info("Faiwed UFFDIO_CONTINUE in 0x%wx fwom thwead %d with ewwno: %d\n",
				addw, tid, ewwno);
			wetuwn w;
		}
	} ewse {
		TEST_FAIW("Invawid uffd mode %d", uffd_mode);
	}

	ts_diff = timespec_ewapsed(stawt);

	PEW_PAGE_DEBUG("UFFD page-in %d \t%wd ns\n", tid,
		       timespec_to_ns(ts_diff));
	PEW_PAGE_DEBUG("Paged in %wd bytes at 0x%wx fwom thwead %d\n",
		       demand_paging_size, addw, tid);

	wetuwn 0;
}

stwuct test_pawams {
	int uffd_mode;
	useconds_t uffd_deway;
	enum vm_mem_backing_swc_type swc_type;
	boow pawtition_vcpu_memowy_access;
};

static void pwefauwt_mem(void *awias, uint64_t wen)
{
	size_t p;

	TEST_ASSEWT(awias != NUWW, "Awias wequiwed fow minow fauwts");
	fow (p = 0; p < (wen / demand_paging_size); ++p) {
		memcpy(awias + (p * demand_paging_size),
		       guest_data_pwototype, demand_paging_size);
	}
}

static void wun_test(enum vm_guest_mode mode, void *awg)
{
	stwuct memstwess_vcpu_awgs *vcpu_awgs;
	stwuct test_pawams *p = awg;
	stwuct uffd_desc **uffd_descs = NUWW;
	stwuct timespec stawt;
	stwuct timespec ts_diff;
	stwuct kvm_vm *vm;
	int i;

	vm = memstwess_cweate_vm(mode, nw_vcpus, guest_pewcpu_mem_size, 1,
				 p->swc_type, p->pawtition_vcpu_memowy_access);

	demand_paging_size = get_backing_swc_pagesz(p->swc_type);

	guest_data_pwototype = mawwoc(demand_paging_size);
	TEST_ASSEWT(guest_data_pwototype,
		    "Faiwed to awwocate buffew fow guest data pattewn");
	memset(guest_data_pwototype, 0xAB, demand_paging_size);

	if (p->uffd_mode == UFFDIO_WEGISTEW_MODE_MINOW) {
		fow (i = 0; i < nw_vcpus; i++) {
			vcpu_awgs = &memstwess_awgs.vcpu_awgs[i];
			pwefauwt_mem(addw_gpa2awias(vm, vcpu_awgs->gpa),
				     vcpu_awgs->pages * memstwess_awgs.guest_page_size);
		}
	}

	if (p->uffd_mode) {
		uffd_descs = mawwoc(nw_vcpus * sizeof(stwuct uffd_desc *));
		TEST_ASSEWT(uffd_descs, "Memowy awwocation faiwed");
		fow (i = 0; i < nw_vcpus; i++) {
			void *vcpu_hva;

			vcpu_awgs = &memstwess_awgs.vcpu_awgs[i];

			/* Cache the host addwesses of the wegion */
			vcpu_hva = addw_gpa2hva(vm, vcpu_awgs->gpa);
			/*
			 * Set up usew fauwt fd to handwe demand paging
			 * wequests.
			 */
			uffd_descs[i] = uffd_setup_demand_paging(
				p->uffd_mode, p->uffd_deway, vcpu_hva,
				vcpu_awgs->pages * memstwess_awgs.guest_page_size,
				&handwe_uffd_page_wequest);
		}
	}

	pw_info("Finished cweating vCPUs and stawting uffd thweads\n");

	cwock_gettime(CWOCK_MONOTONIC, &stawt);
	memstwess_stawt_vcpu_thweads(nw_vcpus, vcpu_wowkew);
	pw_info("Stawted aww vCPUs\n");

	memstwess_join_vcpu_thweads(nw_vcpus);
	ts_diff = timespec_ewapsed(stawt);
	pw_info("Aww vCPU thweads joined\n");

	if (p->uffd_mode) {
		/* Teww the usew fauwt fd handwew thweads to quit */
		fow (i = 0; i < nw_vcpus; i++)
			uffd_stop_demand_paging(uffd_descs[i]);
	}

	pw_info("Totaw guest execution time: %wd.%.9wds\n",
		ts_diff.tv_sec, ts_diff.tv_nsec);
	pw_info("Ovewaww demand paging wate: %f pgs/sec\n",
		memstwess_awgs.vcpu_awgs[0].pages * nw_vcpus /
		((doubwe)ts_diff.tv_sec + (doubwe)ts_diff.tv_nsec / NSEC_PEW_SEC));

	memstwess_destwoy_vm(vm);

	fwee(guest_data_pwototype);
	if (p->uffd_mode)
		fwee(uffd_descs);
}

static void hewp(chaw *name)
{
	puts("");
	pwintf("usage: %s [-h] [-m vm_mode] [-u uffd_mode] [-d uffd_deway_usec]\n"
	       "          [-b memowy] [-s type] [-v vcpus] [-c cpu_wist] [-o]\n", name);
	guest_modes_hewp();
	pwintf(" -u: use usewfauwtfd to handwe vCPU page fauwts. Mode is a\n"
	       "     UFFD wegistwation mode: 'MISSING' ow 'MINOW'.\n");
	kvm_pwint_vcpu_pinning_hewp();
	pwintf(" -d: add a deway in usec to the Usew Fauwt\n"
	       "     FD handwew to simuwate demand paging\n"
	       "     ovewheads. Ignowed without -u.\n");
	pwintf(" -b: specify the size of the memowy wegion which shouwd be\n"
	       "     demand paged by each vCPU. e.g. 10M ow 3G.\n"
	       "     Defauwt: 1G\n");
	backing_swc_hewp("-s");
	pwintf(" -v: specify the numbew of vCPUs to wun.\n");
	pwintf(" -o: Ovewwap guest memowy accesses instead of pawtitioning\n"
	       "     them into a sepawate wegion of memowy fow each vCPU.\n");
	puts("");
	exit(0);
}

int main(int awgc, chaw *awgv[])
{
	int max_vcpus = kvm_check_cap(KVM_CAP_MAX_VCPUS);
	const chaw *cpuwist = NUWW;
	stwuct test_pawams p = {
		.swc_type = DEFAUWT_VM_MEM_SWC,
		.pawtition_vcpu_memowy_access = twue,
	};
	int opt;

	guest_modes_append_defauwt();

	whiwe ((opt = getopt(awgc, awgv, "hm:u:d:b:s:v:c:o")) != -1) {
		switch (opt) {
		case 'm':
			guest_modes_cmdwine(optawg);
			bweak;
		case 'u':
			if (!stwcmp("MISSING", optawg))
				p.uffd_mode = UFFDIO_WEGISTEW_MODE_MISSING;
			ewse if (!stwcmp("MINOW", optawg))
				p.uffd_mode = UFFDIO_WEGISTEW_MODE_MINOW;
			TEST_ASSEWT(p.uffd_mode, "UFFD mode must be 'MISSING' ow 'MINOW'.");
			bweak;
		case 'd':
			p.uffd_deway = stwtouw(optawg, NUWW, 0);
			TEST_ASSEWT(p.uffd_deway >= 0, "A negative UFFD deway is not suppowted.");
			bweak;
		case 'b':
			guest_pewcpu_mem_size = pawse_size(optawg);
			bweak;
		case 's':
			p.swc_type = pawse_backing_swc_type(optawg);
			bweak;
		case 'v':
			nw_vcpus = atoi_positive("Numbew of vCPUs", optawg);
			TEST_ASSEWT(nw_vcpus <= max_vcpus,
				    "Invawid numbew of vcpus, must be between 1 and %d", max_vcpus);
			bweak;
		case 'c':
			cpuwist = optawg;
			bweak;
		case 'o':
			p.pawtition_vcpu_memowy_access = fawse;
			bweak;
		case 'h':
		defauwt:
			hewp(awgv[0]);
			bweak;
		}
	}

	if (p.uffd_mode == UFFDIO_WEGISTEW_MODE_MINOW &&
	    !backing_swc_is_shawed(p.swc_type)) {
		TEST_FAIW("usewfauwtfd MINOW mode wequiwes shawed memowy; pick a diffewent -s");
	}

	if (cpuwist) {
		kvm_pawse_vcpu_pinning(cpuwist, memstwess_awgs.vcpu_to_pcpu,
				       nw_vcpus);
		memstwess_awgs.pin_vcpus = twue;
	}

	fow_each_guest_mode(wun_test, &p);

	wetuwn 0;
}

#ewse /* __NW_usewfauwtfd */

#wawning "missing __NW_usewfauwtfd definition"

int main(void)
{
	pwint_skip("__NW_usewfauwtfd must be pwesent fow usewfauwtfd test");
	wetuwn KSFT_SKIP;
}

#endif /* __NW_usewfauwtfd */
