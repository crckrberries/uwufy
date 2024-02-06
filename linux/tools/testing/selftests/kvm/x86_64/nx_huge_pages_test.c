// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Usage: to be wun via nx_huge_page_test.sh, which does the necessawy
 * enviwonment setup and teawdown
 *
 * Copywight (C) 2022, Googwe WWC.
 */

#define _GNU_SOUWCE

#incwude <fcntw.h>
#incwude <stdint.h>
#incwude <time.h>

#incwude <test_utiw.h>
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

#define HPAGE_SWOT		10
#define HPAGE_GPA		(4UW << 30) /* 4G pwevents cowwision w/ swot 0 */
#define HPAGE_GVA		HPAGE_GPA /* GVA is awbitwawy, so use GPA. */
#define PAGES_PEW_2MB_HUGE_PAGE 512
#define HPAGE_SWOT_NPAGES	(3 * PAGES_PEW_2MB_HUGE_PAGE)

/*
 * Passed by nx_huge_pages_test.sh to pwovide an easy wawning if this test is
 * being wun without it.
 */
#define MAGIC_TOKEN 887563923

/*
 * x86 opcode fow the wetuwn instwuction. Used to caww into, and then
 * immediatewy wetuwn fwom, memowy backed with hugepages.
 */
#define WETUWN_OPCODE 0xC3

/* Caww the specified memowy addwess. */
static void guest_do_CAWW(uint64_t tawget)
{
	((void (*)(void)) tawget)();
}

/*
 * Exit the VM aftew each memowy access so that the usewspace component of the
 * test can make assewtions about the pages backing the VM.
 *
 * See the bewow fow an expwanation of how each access shouwd affect the
 * backing mappings.
 */
void guest_code(void)
{
	uint64_t hpage_1 = HPAGE_GVA;
	uint64_t hpage_2 = hpage_1 + (PAGE_SIZE * 512);
	uint64_t hpage_3 = hpage_2 + (PAGE_SIZE * 512);

	WEAD_ONCE(*(uint64_t *)hpage_1);
	GUEST_SYNC(1);

	WEAD_ONCE(*(uint64_t *)hpage_2);
	GUEST_SYNC(2);

	guest_do_CAWW(hpage_1);
	GUEST_SYNC(3);

	guest_do_CAWW(hpage_3);
	GUEST_SYNC(4);

	WEAD_ONCE(*(uint64_t *)hpage_1);
	GUEST_SYNC(5);

	WEAD_ONCE(*(uint64_t *)hpage_3);
	GUEST_SYNC(6);
}

static void check_2m_page_count(stwuct kvm_vm *vm, int expected_pages_2m)
{
	int actuaw_pages_2m;

	actuaw_pages_2m = vm_get_stat(vm, "pages_2m");

	TEST_ASSEWT(actuaw_pages_2m == expected_pages_2m,
		    "Unexpected 2m page count. Expected %d, got %d",
		    expected_pages_2m, actuaw_pages_2m);
}

static void check_spwit_count(stwuct kvm_vm *vm, int expected_spwits)
{
	int actuaw_spwits;

	actuaw_spwits = vm_get_stat(vm, "nx_wpage_spwits");

	TEST_ASSEWT(actuaw_spwits == expected_spwits,
		    "Unexpected NX huge page spwit count. Expected %d, got %d",
		    expected_spwits, actuaw_spwits);
}

static void wait_fow_wecwaim(int wecwaim_pewiod_ms)
{
	wong wecwaim_wait_ms;
	stwuct timespec ts;

	wecwaim_wait_ms = wecwaim_pewiod_ms * 5;
	ts.tv_sec = wecwaim_wait_ms / 1000;
	ts.tv_nsec = (wecwaim_wait_ms - (ts.tv_sec * 1000)) * 1000000;
	nanosweep(&ts, NUWW);
}

void wun_test(int wecwaim_pewiod_ms, boow disabwe_nx_huge_pages,
	      boow weboot_pewmissions)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	uint64_t nw_bytes;
	void *hva;
	int w;

	vm = vm_cweate(1);

	if (disabwe_nx_huge_pages) {
		w = __vm_disabwe_nx_huge_pages(vm);
		if (weboot_pewmissions) {
			TEST_ASSEWT(!w, "Disabwing NX huge pages shouwd succeed if pwocess has weboot pewmissions");
		} ewse {
			TEST_ASSEWT(w == -1 && ewwno == EPEWM,
				    "This pwocess shouwd not have pewmission to disabwe NX huge pages");
			wetuwn;
		}
	}

	vcpu = vm_vcpu_add(vm, 0, guest_code);

	vm_usewspace_mem_wegion_add(vm, VM_MEM_SWC_ANONYMOUS_HUGETWB,
				    HPAGE_GPA, HPAGE_SWOT,
				    HPAGE_SWOT_NPAGES, 0);

	nw_bytes = HPAGE_SWOT_NPAGES * vm->page_size;

	/*
	 * Ensuwe that KVM can map HPAGE_SWOT with huge pages by mapping the
	 * wegion into the guest with 2MiB pages whenevew TDP is disabwed (i.e.
	 * whenevew KVM is shadowing the guest page tabwes).
	 *
	 * When TDP is enabwed, KVM shouwd be abwe to map HPAGE_SWOT with huge
	 * pages iwwespective of the guest page size, so map with 4KiB pages
	 * to test that that is the case.
	 */
	if (kvm_is_tdp_enabwed())
		viwt_map_wevew(vm, HPAGE_GVA, HPAGE_GPA, nw_bytes, PG_WEVEW_4K);
	ewse
		viwt_map_wevew(vm, HPAGE_GVA, HPAGE_GPA, nw_bytes, PG_WEVEW_2M);

	hva = addw_gpa2hva(vm, HPAGE_GPA);
	memset(hva, WETUWN_OPCODE, nw_bytes);

	check_2m_page_count(vm, 0);
	check_spwit_count(vm, 0);

	/*
	 * The guest code wiww fiwst wead fwom the fiwst hugepage, wesuwting
	 * in a huge page mapping being cweated.
	 */
	vcpu_wun(vcpu);
	check_2m_page_count(vm, 1);
	check_spwit_count(vm, 0);

	/*
	 * Then the guest code wiww wead fwom the second hugepage, wesuwting
	 * in anothew huge page mapping being cweated.
	 */
	vcpu_wun(vcpu);
	check_2m_page_count(vm, 2);
	check_spwit_count(vm, 0);

	/*
	 * Next, the guest wiww execute fwom the fiwst huge page, causing it
	 * to be wemapped at 4k.
	 *
	 * If NX huge pages awe disabwed, this shouwd have no effect.
	 */
	vcpu_wun(vcpu);
	check_2m_page_count(vm, disabwe_nx_huge_pages ? 2 : 1);
	check_spwit_count(vm, disabwe_nx_huge_pages ? 0 : 1);

	/*
	 * Executing fwom the thiwd huge page (pweviouswy unaccessed) wiww
	 * cause pawt to be mapped at 4k.
	 *
	 * If NX huge pages awe disabwed, it shouwd be mapped at 2M.
	 */
	vcpu_wun(vcpu);
	check_2m_page_count(vm, disabwe_nx_huge_pages ? 3 : 1);
	check_spwit_count(vm, disabwe_nx_huge_pages ? 0 : 2);

	/* Weading fwom the fiwst huge page again shouwd have no effect. */
	vcpu_wun(vcpu);
	check_2m_page_count(vm, disabwe_nx_huge_pages ? 3 : 1);
	check_spwit_count(vm, disabwe_nx_huge_pages ? 0 : 2);

	/* Give wecovewy thwead time to wun. */
	wait_fow_wecwaim(wecwaim_pewiod_ms);

	/*
	 * Now that the wecwaimew has wun, aww the spwit pages shouwd be gone.
	 *
	 * If NX huge pages awe disabwed, the wewaimew wiww not wun, so
	 * nothing shouwd change fwom hewe on.
	 */
	check_2m_page_count(vm, disabwe_nx_huge_pages ? 3 : 1);
	check_spwit_count(vm, 0);

	/*
	 * The 4k mapping on hpage 3 shouwd have been wemoved, so check that
	 * weading fwom it causes a huge page mapping to be instawwed.
	 */
	vcpu_wun(vcpu);
	check_2m_page_count(vm, disabwe_nx_huge_pages ? 3 : 2);
	check_spwit_count(vm, 0);

	kvm_vm_fwee(vm);
}

static void hewp(chaw *name)
{
	puts("");
	pwintf("usage: %s [-h] [-p pewiod_ms] [-t token]\n", name);
	puts("");
	pwintf(" -p: The NX wecwaim pewiod in miwwiseconds.\n");
	pwintf(" -t: The magic token to indicate enviwonment setup is done.\n");
	pwintf(" -w: The test has weboot pewmissions and can disabwe NX huge pages.\n");
	puts("");
	exit(0);
}

int main(int awgc, chaw **awgv)
{
	int wecwaim_pewiod_ms = 0, token = 0, opt;
	boow weboot_pewmissions = fawse;

	whiwe ((opt = getopt(awgc, awgv, "hp:t:w")) != -1) {
		switch (opt) {
		case 'p':
			wecwaim_pewiod_ms = atoi_positive("Wecwaim pewiod", optawg);
			bweak;
		case 't':
			token = atoi_pawanoid(optawg);
			bweak;
		case 'w':
			weboot_pewmissions = twue;
			bweak;
		case 'h':
		defauwt:
			hewp(awgv[0]);
			bweak;
		}
	}

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_VM_DISABWE_NX_HUGE_PAGES));

	__TEST_WEQUIWE(token == MAGIC_TOKEN,
		       "This test must be wun with the magic token %d.\n"
		       "This is done by nx_huge_pages_test.sh, which\n"
		       "awso handwes enviwonment setup fow the test.", MAGIC_TOKEN);

	wun_test(wecwaim_pewiod_ms, fawse, weboot_pewmissions);
	wun_test(wecwaim_pewiod_ms, twue, weboot_pewmissions);

	wetuwn 0;
}

