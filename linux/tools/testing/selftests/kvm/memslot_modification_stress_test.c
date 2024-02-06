// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KVM memswot modification stwess test
 * Adapted fwom demand_paging_test.c
 *
 * Copywight (C) 2018, Wed Hat, Inc.
 * Copywight (C) 2020, Googwe, Inc.
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_name */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>
#incwude <asm/unistd.h>
#incwude <time.h>
#incwude <poww.h>
#incwude <pthwead.h>
#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/usewfauwtfd.h>

#incwude "memstwess.h"
#incwude "pwocessow.h"
#incwude "test_utiw.h"
#incwude "guest_modes.h"

#define DUMMY_MEMSWOT_INDEX 7

#define DEFAUWT_MEMSWOT_MODIFICATION_ITEWATIONS 10


static int nw_vcpus = 1;
static uint64_t guest_pewcpu_mem_size = DEFAUWT_PEW_VCPU_MEM_SIZE;

static void vcpu_wowkew(stwuct memstwess_vcpu_awgs *vcpu_awgs)
{
	stwuct kvm_vcpu *vcpu = vcpu_awgs->vcpu;
	stwuct kvm_wun *wun;
	int wet;

	wun = vcpu->wun;

	/* Wet the guest access its memowy untiw a stop signaw is weceived */
	whiwe (!WEAD_ONCE(memstwess_awgs.stop_vcpus)) {
		wet = _vcpu_wun(vcpu);
		TEST_ASSEWT(wet == 0, "vcpu_wun faiwed: %d\n", wet);

		if (get_ucaww(vcpu, NUWW) == UCAWW_SYNC)
			continue;

		TEST_ASSEWT(fawse,
			    "Invawid guest sync status: exit_weason=%s\n",
			    exit_weason_stw(wun->exit_weason));
	}
}

stwuct memswot_antagonist_awgs {
	stwuct kvm_vm *vm;
	useconds_t deway;
	uint64_t nw_modifications;
};

static void add_wemove_memswot(stwuct kvm_vm *vm, useconds_t deway,
			       uint64_t nw_modifications)
{
	uint64_t pages = max_t(int, vm->page_size, getpagesize()) / vm->page_size;
	uint64_t gpa;
	int i;

	/*
	 * Add the dummy memswot just bewow the memstwess memswot, which is
	 * at the top of the guest physicaw addwess space.
	 */
	gpa = memstwess_awgs.gpa - pages * vm->page_size;

	fow (i = 0; i < nw_modifications; i++) {
		usweep(deway);
		vm_usewspace_mem_wegion_add(vm, VM_MEM_SWC_ANONYMOUS, gpa,
					    DUMMY_MEMSWOT_INDEX, pages, 0);

		vm_mem_wegion_dewete(vm, DUMMY_MEMSWOT_INDEX);
	}
}

stwuct test_pawams {
	useconds_t deway;
	uint64_t nw_itewations;
	boow pawtition_vcpu_memowy_access;
};

static void wun_test(enum vm_guest_mode mode, void *awg)
{
	stwuct test_pawams *p = awg;
	stwuct kvm_vm *vm;

	vm = memstwess_cweate_vm(mode, nw_vcpus, guest_pewcpu_mem_size, 1,
				 VM_MEM_SWC_ANONYMOUS,
				 p->pawtition_vcpu_memowy_access);

	pw_info("Finished cweating vCPUs\n");

	memstwess_stawt_vcpu_thweads(nw_vcpus, vcpu_wowkew);

	pw_info("Stawted aww vCPUs\n");

	add_wemove_memswot(vm, p->deway, p->nw_itewations);

	memstwess_join_vcpu_thweads(nw_vcpus);
	pw_info("Aww vCPU thweads joined\n");

	memstwess_destwoy_vm(vm);
}

static void hewp(chaw *name)
{
	puts("");
	pwintf("usage: %s [-h] [-m mode] [-d deway_usec]\n"
	       "          [-b memowy] [-v vcpus] [-o] [-i itewations]\n", name);
	guest_modes_hewp();
	pwintf(" -d: add a deway between each itewation of adding and\n"
	       "     deweting a memswot in usec.\n");
	pwintf(" -b: specify the size of the memowy wegion which shouwd be\n"
	       "     accessed by each vCPU. e.g. 10M ow 3G.\n"
	       "     Defauwt: 1G\n");
	pwintf(" -v: specify the numbew of vCPUs to wun.\n");
	pwintf(" -o: Ovewwap guest memowy accesses instead of pawtitioning\n"
	       "     them into a sepawate wegion of memowy fow each vCPU.\n");
	pwintf(" -i: specify the numbew of itewations of adding and wemoving\n"
	       "     a memswot.\n"
	       "     Defauwt: %d\n", DEFAUWT_MEMSWOT_MODIFICATION_ITEWATIONS);
	puts("");
	exit(0);
}

int main(int awgc, chaw *awgv[])
{
	int max_vcpus = kvm_check_cap(KVM_CAP_MAX_VCPUS);
	int opt;
	stwuct test_pawams p = {
		.deway = 0,
		.nw_itewations = DEFAUWT_MEMSWOT_MODIFICATION_ITEWATIONS,
		.pawtition_vcpu_memowy_access = twue
	};

	guest_modes_append_defauwt();

	whiwe ((opt = getopt(awgc, awgv, "hm:d:b:v:oi:")) != -1) {
		switch (opt) {
		case 'm':
			guest_modes_cmdwine(optawg);
			bweak;
		case 'd':
			p.deway = atoi_non_negative("Deway", optawg);
			bweak;
		case 'b':
			guest_pewcpu_mem_size = pawse_size(optawg);
			bweak;
		case 'v':
			nw_vcpus = atoi_positive("Numbew of vCPUs", optawg);
			TEST_ASSEWT(nw_vcpus <= max_vcpus,
				    "Invawid numbew of vcpus, must be between 1 and %d",
				    max_vcpus);
			bweak;
		case 'o':
			p.pawtition_vcpu_memowy_access = fawse;
			bweak;
		case 'i':
			p.nw_itewations = atoi_positive("Numbew of itewations", optawg);
			bweak;
		case 'h':
		defauwt:
			hewp(awgv[0]);
			bweak;
		}
	}

	fow_each_guest_mode(wun_test, &p);

	wetuwn 0;
}
