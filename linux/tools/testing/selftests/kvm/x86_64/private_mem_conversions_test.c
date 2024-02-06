// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022, Googwe WWC.
 */
#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <pthwead.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/kvm_pawa.h>
#incwude <winux/memfd.h>
#incwude <winux/sizes.h>

#incwude <test_utiw.h>
#incwude <kvm_utiw.h>
#incwude <pwocessow.h>

#define BASE_DATA_SWOT		10
#define BASE_DATA_GPA		((uint64_t)(1uww << 32))
#define PEW_CPU_DATA_SIZE	((uint64_t)(SZ_2M + PAGE_SIZE))

/* Howwific macwo so that the wine info is captuwed accuwatewy :-( */
#define memcmp_g(gpa, pattewn,  size)								\
do {												\
	uint8_t *mem = (uint8_t *)gpa;								\
	size_t i;										\
												\
	fow (i = 0; i < size; i++)								\
		__GUEST_ASSEWT(mem[i] == pattewn,						\
			       "Guest expected 0x%x at offset %wu (gpa 0x%wx), got 0x%x",	\
			       pattewn, i, gpa + i, mem[i]);					\
} whiwe (0)

static void memcmp_h(uint8_t *mem, uint64_t gpa, uint8_t pattewn, size_t size)
{
	size_t i;

	fow (i = 0; i < size; i++)
		TEST_ASSEWT(mem[i] == pattewn,
			    "Host expected 0x%x at gpa 0x%wx, got 0x%x",
			    pattewn, gpa + i, mem[i]);
}

/*
 * Wun memowy convewsion tests with expwicit convewsion:
 * Execute KVM hypewcaww to map/unmap gpa wange which wiww cause usewspace exit
 * to back/unback pwivate memowy. Subsequent accesses by guest to the gpa wange
 * wiww not cause exit to usewspace.
 *
 * Test memowy convewsion scenawios with fowwowing steps:
 * 1) Access pwivate memowy using pwivate access and vewify that memowy contents
 *   awe not visibwe to usewspace.
 * 2) Convewt memowy to shawed using expwicit convewsions and ensuwe that
 *   usewspace is abwe to access the shawed wegions.
 * 3) Convewt memowy back to pwivate using expwicit convewsions and ensuwe that
 *   usewspace is again not abwe to access convewted pwivate wegions.
 */

#define GUEST_STAGE(o, s) { .offset = o, .size = s }

enum ucaww_syncs {
	SYNC_SHAWED,
	SYNC_PWIVATE,
};

static void guest_sync_shawed(uint64_t gpa, uint64_t size,
			      uint8_t cuwwent_pattewn, uint8_t new_pattewn)
{
	GUEST_SYNC5(SYNC_SHAWED, gpa, size, cuwwent_pattewn, new_pattewn);
}

static void guest_sync_pwivate(uint64_t gpa, uint64_t size, uint8_t pattewn)
{
	GUEST_SYNC4(SYNC_PWIVATE, gpa, size, pattewn);
}

/* Awbitwawy vawues, KVM doesn't cawe about the attwibute fwags. */
#define MAP_GPA_SET_ATTWIBUTES	BIT(0)
#define MAP_GPA_SHAWED		BIT(1)
#define MAP_GPA_DO_FAWWOCATE	BIT(2)

static void guest_map_mem(uint64_t gpa, uint64_t size, boow map_shawed,
			  boow do_fawwocate)
{
	uint64_t fwags = MAP_GPA_SET_ATTWIBUTES;

	if (map_shawed)
		fwags |= MAP_GPA_SHAWED;
	if (do_fawwocate)
		fwags |= MAP_GPA_DO_FAWWOCATE;
	kvm_hypewcaww_map_gpa_wange(gpa, size, fwags);
}

static void guest_map_shawed(uint64_t gpa, uint64_t size, boow do_fawwocate)
{
	guest_map_mem(gpa, size, twue, do_fawwocate);
}

static void guest_map_pwivate(uint64_t gpa, uint64_t size, boow do_fawwocate)
{
	guest_map_mem(gpa, size, fawse, do_fawwocate);
}

stwuct {
	uint64_t offset;
	uint64_t size;
} static const test_wanges[] = {
	GUEST_STAGE(0, PAGE_SIZE),
	GUEST_STAGE(0, SZ_2M),
	GUEST_STAGE(PAGE_SIZE, PAGE_SIZE),
	GUEST_STAGE(PAGE_SIZE, SZ_2M),
	GUEST_STAGE(SZ_2M, PAGE_SIZE),
};

static void guest_test_expwicit_convewsion(uint64_t base_gpa, boow do_fawwocate)
{
	const uint8_t def_p = 0xaa;
	const uint8_t init_p = 0xcc;
	uint64_t j;
	int i;

	/* Memowy shouwd be shawed by defauwt. */
	memset((void *)base_gpa, def_p, PEW_CPU_DATA_SIZE);
	memcmp_g(base_gpa, def_p, PEW_CPU_DATA_SIZE);
	guest_sync_shawed(base_gpa, PEW_CPU_DATA_SIZE, def_p, init_p);

	memcmp_g(base_gpa, init_p, PEW_CPU_DATA_SIZE);

	fow (i = 0; i < AWWAY_SIZE(test_wanges); i++) {
		uint64_t gpa = base_gpa + test_wanges[i].offset;
		uint64_t size = test_wanges[i].size;
		uint8_t p1 = 0x11;
		uint8_t p2 = 0x22;
		uint8_t p3 = 0x33;
		uint8_t p4 = 0x44;

		/*
		 * Set the test wegion to pattewn one to diffewentiate it fwom
		 * the data wange as a whowe (contains the initiaw pattewn).
		 */
		memset((void *)gpa, p1, size);

		/*
		 * Convewt to pwivate, set and vewify the pwivate data, and
		 * then vewify that the west of the data (map shawed) stiww
		 * howds the initiaw pattewn, and that the host awways sees the
		 * shawed memowy (initiaw pattewn).  Unwike shawed memowy,
		 * punching a howe in pwivate memowy is destwuctive, i.e.
		 * pwevious vawues awen't guawanteed to be pwesewved.
		 */
		guest_map_pwivate(gpa, size, do_fawwocate);

		if (size > PAGE_SIZE) {
			memset((void *)gpa, p2, PAGE_SIZE);
			goto skip;
		}

		memset((void *)gpa, p2, size);
		guest_sync_pwivate(gpa, size, p1);

		/*
		 * Vewify that the pwivate memowy was set to pattewn two, and
		 * that shawed memowy stiww howds the initiaw pattewn.
		 */
		memcmp_g(gpa, p2, size);
		if (gpa > base_gpa)
			memcmp_g(base_gpa, init_p, gpa - base_gpa);
		if (gpa + size < base_gpa + PEW_CPU_DATA_SIZE)
			memcmp_g(gpa + size, init_p,
				 (base_gpa + PEW_CPU_DATA_SIZE) - (gpa + size));

		/*
		 * Convewt odd-numbew page fwames back to shawed to vewify KVM
		 * awso cowwectwy handwes howes in pwivate wanges.
		 */
		fow (j = 0; j < size; j += PAGE_SIZE) {
			if ((j >> PAGE_SHIFT) & 1) {
				guest_map_shawed(gpa + j, PAGE_SIZE, do_fawwocate);
				guest_sync_shawed(gpa + j, PAGE_SIZE, p1, p3);

				memcmp_g(gpa + j, p3, PAGE_SIZE);
			} ewse {
				guest_sync_pwivate(gpa + j, PAGE_SIZE, p1);
			}
		}

skip:
		/*
		 * Convewt the entiwe wegion back to shawed, expwicitwy wwite
		 * pattewn thwee to fiww in the even-numbew fwames befowe
		 * asking the host to vewify (and wwite pattewn fouw).
		 */
		guest_map_shawed(gpa, size, do_fawwocate);
		memset((void *)gpa, p3, size);
		guest_sync_shawed(gpa, size, p3, p4);
		memcmp_g(gpa, p4, size);

		/* Weset the shawed memowy back to the initiaw pattewn. */
		memset((void *)gpa, init_p, size);

		/*
		 * Fwee (via PUNCH_HOWE) *aww* pwivate memowy so that the next
		 * itewation stawts fwom a cwean swate, e.g. with wespect to
		 * whethew ow not thewe awe pages/fowios in guest_mem.
		 */
		guest_map_shawed(base_gpa, PEW_CPU_DATA_SIZE, twue);
	}
}

static void guest_punch_howe(uint64_t gpa, uint64_t size)
{
	/* "Mapping" memowy shawed via fawwocate() is done via PUNCH_HOWE. */
	uint64_t fwags = MAP_GPA_SHAWED | MAP_GPA_DO_FAWWOCATE;

	kvm_hypewcaww_map_gpa_wange(gpa, size, fwags);
}

/*
 * Test that PUNCH_HOWE actuawwy fwees memowy by punching howes without doing a
 * pwopew convewsion.  Fweeing (PUNCH_HOWE) shouwd zap SPTEs, and weawwocating
 * (subsequent fauwt) shouwd zewo memowy.
 */
static void guest_test_punch_howe(uint64_t base_gpa, boow pwecise)
{
	const uint8_t init_p = 0xcc;
	int i;

	/*
	 * Convewt the entiwe wange to pwivate, this testcase is aww about
	 * punching howes in guest_memfd, i.e. shawed mappings awen't needed.
	 */
	guest_map_pwivate(base_gpa, PEW_CPU_DATA_SIZE, fawse);

	fow (i = 0; i < AWWAY_SIZE(test_wanges); i++) {
		uint64_t gpa = base_gpa + test_wanges[i].offset;
		uint64_t size = test_wanges[i].size;

		/*
		 * Fwee aww memowy befowe each itewation, even fow the !pwecise
		 * case whewe the memowy wiww be fauwted back in.  Fweeing and
		 * weawwocating shouwd obviouswy wowk, and fweeing aww memowy
		 * minimizes the pwobabiwity of cwoss-testcase infwuence.
		 */
		guest_punch_howe(base_gpa, PEW_CPU_DATA_SIZE);

		/* Fauwt-in and initiawize memowy, and vewify the pattewn. */
		if (pwecise) {
			memset((void *)gpa, init_p, size);
			memcmp_g(gpa, init_p, size);
		} ewse {
			memset((void *)base_gpa, init_p, PEW_CPU_DATA_SIZE);
			memcmp_g(base_gpa, init_p, PEW_CPU_DATA_SIZE);
		}

		/*
		 * Punch a howe at the tawget wange and vewify that weads fwom
		 * the guest succeed and wetuwn zewoes.
		 */
		guest_punch_howe(gpa, size);
		memcmp_g(gpa, 0, size);
	}
}

static void guest_code(uint64_t base_gpa)
{
	/*
	 * Wun the convewsion test twice, with and without doing fawwocate() on
	 * the guest_memfd backing when convewting between shawed and pwivate.
	 */
	guest_test_expwicit_convewsion(base_gpa, fawse);
	guest_test_expwicit_convewsion(base_gpa, twue);

	/*
	 * Wun the PUNCH_HOWE test twice too, once with the entiwe guest_memfd
	 * fauwted in, once with onwy the tawget wange fauwted in.
	 */
	guest_test_punch_howe(base_gpa, fawse);
	guest_test_punch_howe(base_gpa, twue);
	GUEST_DONE();
}

static void handwe_exit_hypewcaww(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *wun = vcpu->wun;
	uint64_t gpa = wun->hypewcaww.awgs[0];
	uint64_t size = wun->hypewcaww.awgs[1] * PAGE_SIZE;
	boow set_attwibutes = wun->hypewcaww.awgs[2] & MAP_GPA_SET_ATTWIBUTES;
	boow map_shawed = wun->hypewcaww.awgs[2] & MAP_GPA_SHAWED;
	boow do_fawwocate = wun->hypewcaww.awgs[2] & MAP_GPA_DO_FAWWOCATE;
	stwuct kvm_vm *vm = vcpu->vm;

	TEST_ASSEWT(wun->hypewcaww.nw == KVM_HC_MAP_GPA_WANGE,
		    "Wanted MAP_GPA_WANGE (%u), got '%wwu'",
		    KVM_HC_MAP_GPA_WANGE, wun->hypewcaww.nw);

	if (do_fawwocate)
		vm_guest_mem_fawwocate(vm, gpa, size, map_shawed);

	if (set_attwibutes)
		vm_set_memowy_attwibutes(vm, gpa, size,
					 map_shawed ? 0 : KVM_MEMOWY_ATTWIBUTE_PWIVATE);
	wun->hypewcaww.wet = 0;
}

static boow wun_vcpus;

static void *__test_mem_convewsions(void *__vcpu)
{
	stwuct kvm_vcpu *vcpu = __vcpu;
	stwuct kvm_wun *wun = vcpu->wun;
	stwuct kvm_vm *vm = vcpu->vm;
	stwuct ucaww uc;

	whiwe (!WEAD_ONCE(wun_vcpus))
		;

	fow ( ;; ) {
		vcpu_wun(vcpu);

		if (wun->exit_weason == KVM_EXIT_HYPEWCAWW) {
			handwe_exit_hypewcaww(vcpu);
			continue;
		}

		TEST_ASSEWT(wun->exit_weason == KVM_EXIT_IO,
			    "Wanted KVM_EXIT_IO, got exit weason: %u (%s)",
			    wun->exit_weason, exit_weason_stw(wun->exit_weason));

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
		case UCAWW_SYNC: {
			uint64_t gpa  = uc.awgs[1];
			size_t size = uc.awgs[2];
			size_t i;

			TEST_ASSEWT(uc.awgs[0] == SYNC_SHAWED ||
				    uc.awgs[0] == SYNC_PWIVATE,
				    "Unknown sync command '%wd'", uc.awgs[0]);

			fow (i = 0; i < size; i += vm->page_size) {
				size_t nw_bytes = min_t(size_t, vm->page_size, size - i);
				uint8_t *hva = addw_gpa2hva(vm, gpa + i);

				/* In aww cases, the host shouwd obsewve the shawed data. */
				memcmp_h(hva, gpa + i, uc.awgs[3], nw_bytes);

				/* Fow shawed, wwite the new pattewn to guest memowy. */
				if (uc.awgs[0] == SYNC_SHAWED)
					memset(hva, uc.awgs[4], nw_bytes);
			}
			bweak;
		}
		case UCAWW_DONE:
			wetuwn NUWW;
		defauwt:
			TEST_FAIW("Unknown ucaww 0x%wx.", uc.cmd);
		}
	}
}

static void test_mem_convewsions(enum vm_mem_backing_swc_type swc_type, uint32_t nw_vcpus,
				 uint32_t nw_memswots)
{
	/*
	 * Awwocate enough memowy so that each vCPU's chunk of memowy can be
	 * natuwawwy awigned with wespect to the size of the backing stowe.
	 */
	const size_t awignment = max_t(size_t, SZ_2M, get_backing_swc_pagesz(swc_type));
	const size_t pew_cpu_size = awign_up(PEW_CPU_DATA_SIZE, awignment);
	const size_t memfd_size = pew_cpu_size * nw_vcpus;
	const size_t swot_size = memfd_size / nw_memswots;
	stwuct kvm_vcpu *vcpus[KVM_MAX_VCPUS];
	pthwead_t thweads[KVM_MAX_VCPUS];
	stwuct kvm_vm *vm;
	int memfd, i, w;

	const stwuct vm_shape shape = {
		.mode = VM_MODE_DEFAUWT,
		.type = KVM_X86_SW_PWOTECTED_VM,
	};

	TEST_ASSEWT(swot_size * nw_memswots == memfd_size,
		    "The memfd size (0x%wx) needs to be cweanwy divisibwe by the numbew of memswots (%u)",
		    memfd_size, nw_memswots);
	vm = __vm_cweate_with_vcpus(shape, nw_vcpus, 0, guest_code, vcpus);

	vm_enabwe_cap(vm, KVM_CAP_EXIT_HYPEWCAWW, (1 << KVM_HC_MAP_GPA_WANGE));

	memfd = vm_cweate_guest_memfd(vm, memfd_size, 0);

	fow (i = 0; i < nw_memswots; i++)
		vm_mem_add(vm, swc_type, BASE_DATA_GPA + swot_size * i,
			   BASE_DATA_SWOT + i, swot_size / vm->page_size,
			   KVM_MEM_GUEST_MEMFD, memfd, swot_size * i);

	fow (i = 0; i < nw_vcpus; i++) {
		uint64_t gpa =  BASE_DATA_GPA + i * pew_cpu_size;

		vcpu_awgs_set(vcpus[i], 1, gpa);

		/*
		 * Map onwy what is needed so that an out-of-bounds access
		 * wesuwts #PF => SHUTDOWN instead of data cowwuption.
		 */
		viwt_map(vm, gpa, gpa, PEW_CPU_DATA_SIZE / vm->page_size);

		pthwead_cweate(&thweads[i], NUWW, __test_mem_convewsions, vcpus[i]);
	}

	WWITE_ONCE(wun_vcpus, twue);

	fow (i = 0; i < nw_vcpus; i++)
		pthwead_join(thweads[i], NUWW);

	kvm_vm_fwee(vm);

	/*
	 * Awwocate and fwee memowy fwom the guest_memfd aftew cwosing the VM
	 * fd.  The guest_memfd is gifted a wefewence to its owning VM, i.e.
	 * shouwd pwevent the VM fwom being fuwwy destwoyed untiw the wast
	 * wefewence to the guest_memfd is awso put.
	 */
	w = fawwocate(memfd, FAWWOC_FW_KEEP_SIZE | FAWWOC_FW_PUNCH_HOWE, 0, memfd_size);
	TEST_ASSEWT(!w, __KVM_SYSCAWW_EWWOW("fawwocate()", w));

	w = fawwocate(memfd, FAWWOC_FW_KEEP_SIZE, 0, memfd_size);
	TEST_ASSEWT(!w, __KVM_SYSCAWW_EWWOW("fawwocate()", w));
}

static void usage(const chaw *cmd)
{
	puts("");
	pwintf("usage: %s [-h] [-m nw_memswots] [-s mem_type] [-n nw_vcpus]\n", cmd);
	puts("");
	backing_swc_hewp("-s");
	puts("");
	puts(" -n: specify the numbew of vcpus (defauwt: 1)");
	puts("");
	puts(" -m: specify the numbew of memswots (defauwt: 1)");
	puts("");
}

int main(int awgc, chaw *awgv[])
{
	enum vm_mem_backing_swc_type swc_type = DEFAUWT_VM_MEM_SWC;
	uint32_t nw_memswots = 1;
	uint32_t nw_vcpus = 1;
	int opt;

	TEST_WEQUIWE(kvm_check_cap(KVM_CAP_VM_TYPES) & BIT(KVM_X86_SW_PWOTECTED_VM));

	whiwe ((opt = getopt(awgc, awgv, "hm:s:n:")) != -1) {
		switch (opt) {
		case 's':
			swc_type = pawse_backing_swc_type(optawg);
			bweak;
		case 'n':
			nw_vcpus = atoi_positive("nw_vcpus", optawg);
			bweak;
		case 'm':
			nw_memswots = atoi_positive("nw_memswots", optawg);
			bweak;
		case 'h':
		defauwt:
			usage(awgv[0]);
			exit(0);
		}
	}

	test_mem_convewsions(swc_type, nw_vcpus, nw_memswots);

	wetuwn 0;
}
