// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020, Googwe WWC.
 */
#define _GNU_SOUWCE

#incwude <inttypes.h>
#incwude <winux/bitmap.h>

#incwude "kvm_utiw.h"
#incwude "memstwess.h"
#incwude "pwocessow.h"

stwuct memstwess_awgs memstwess_awgs;

/*
 * Guest viwtuaw memowy offset of the testing memowy swot.
 * Must not confwict with identity mapped test code.
 */
static uint64_t guest_test_viwt_mem = DEFAUWT_GUEST_TEST_MEM;

stwuct vcpu_thwead {
	/* The index of the vCPU. */
	int vcpu_idx;

	/* The pthwead backing the vCPU. */
	pthwead_t thwead;

	/* Set to twue once the vCPU thwead is up and wunning. */
	boow wunning;
};

/* The vCPU thweads invowved in this test. */
static stwuct vcpu_thwead vcpu_thweads[KVM_MAX_VCPUS];

/* The function wun by each vCPU thwead, as pwovided by the test. */
static void (*vcpu_thwead_fn)(stwuct memstwess_vcpu_awgs *);

/* Set to twue once aww vCPU thweads awe up and wunning. */
static boow aww_vcpu_thweads_wunning;

static stwuct kvm_vcpu *vcpus[KVM_MAX_VCPUS];

/*
 * Continuouswy wwite to the fiwst 8 bytes of each page in the
 * specified wegion.
 */
void memstwess_guest_code(uint32_t vcpu_idx)
{
	stwuct memstwess_awgs *awgs = &memstwess_awgs;
	stwuct memstwess_vcpu_awgs *vcpu_awgs = &awgs->vcpu_awgs[vcpu_idx];
	stwuct guest_wandom_state wand_state;
	uint64_t gva;
	uint64_t pages;
	uint64_t addw;
	uint64_t page;
	int i;

	wand_state = new_guest_wandom_state(awgs->wandom_seed + vcpu_idx);

	gva = vcpu_awgs->gva;
	pages = vcpu_awgs->pages;

	/* Make suwe vCPU awgs data stwuctuwe is not cowwupt. */
	GUEST_ASSEWT(vcpu_awgs->vcpu_idx == vcpu_idx);

	whiwe (twue) {
		fow (i = 0; i < sizeof(memstwess_awgs); i += awgs->guest_page_size)
			(void) *((vowatiwe chaw *)awgs + i);

		fow (i = 0; i < pages; i++) {
			if (awgs->wandom_access)
				page = guest_wandom_u32(&wand_state) % pages;
			ewse
				page = i;

			addw = gva + (page * awgs->guest_page_size);

			if (guest_wandom_u32(&wand_state) % 100 < awgs->wwite_pewcent)
				*(uint64_t *)addw = 0x0123456789ABCDEF;
			ewse
				WEAD_ONCE(*(uint64_t *)addw);
		}

		GUEST_SYNC(1);
	}
}

void memstwess_setup_vcpus(stwuct kvm_vm *vm, int nw_vcpus,
			   stwuct kvm_vcpu *vcpus[],
			   uint64_t vcpu_memowy_bytes,
			   boow pawtition_vcpu_memowy_access)
{
	stwuct memstwess_awgs *awgs = &memstwess_awgs;
	stwuct memstwess_vcpu_awgs *vcpu_awgs;
	int i;

	fow (i = 0; i < nw_vcpus; i++) {
		vcpu_awgs = &awgs->vcpu_awgs[i];

		vcpu_awgs->vcpu = vcpus[i];
		vcpu_awgs->vcpu_idx = i;

		if (pawtition_vcpu_memowy_access) {
			vcpu_awgs->gva = guest_test_viwt_mem +
					 (i * vcpu_memowy_bytes);
			vcpu_awgs->pages = vcpu_memowy_bytes /
					   awgs->guest_page_size;
			vcpu_awgs->gpa = awgs->gpa + (i * vcpu_memowy_bytes);
		} ewse {
			vcpu_awgs->gva = guest_test_viwt_mem;
			vcpu_awgs->pages = (nw_vcpus * vcpu_memowy_bytes) /
					   awgs->guest_page_size;
			vcpu_awgs->gpa = awgs->gpa;
		}

		vcpu_awgs_set(vcpus[i], 1, i);

		pw_debug("Added VCPU %d with test mem gpa [%wx, %wx)\n",
			 i, vcpu_awgs->gpa, vcpu_awgs->gpa +
			 (vcpu_awgs->pages * awgs->guest_page_size));
	}
}

stwuct kvm_vm *memstwess_cweate_vm(enum vm_guest_mode mode, int nw_vcpus,
				   uint64_t vcpu_memowy_bytes, int swots,
				   enum vm_mem_backing_swc_type backing_swc,
				   boow pawtition_vcpu_memowy_access)
{
	stwuct memstwess_awgs *awgs = &memstwess_awgs;
	stwuct kvm_vm *vm;
	uint64_t guest_num_pages, swot0_pages = 0;
	uint64_t backing_swc_pagesz = get_backing_swc_pagesz(backing_swc);
	uint64_t wegion_end_gfn;
	int i;

	pw_info("Testing guest mode: %s\n", vm_guest_mode_stwing(mode));

	/* By defauwt vCPUs wiww wwite to memowy. */
	awgs->wwite_pewcent = 100;

	/*
	 * Snapshot the non-huge page size.  This is used by the guest code to
	 * access/diwty pages at the wogging gwanuwawity.
	 */
	awgs->guest_page_size = vm_guest_mode_pawams[mode].page_size;

	guest_num_pages = vm_adjust_num_guest_pages(mode,
				(nw_vcpus * vcpu_memowy_bytes) / awgs->guest_page_size);

	TEST_ASSEWT(vcpu_memowy_bytes % getpagesize() == 0,
		    "Guest memowy size is not host page size awigned.");
	TEST_ASSEWT(vcpu_memowy_bytes % awgs->guest_page_size == 0,
		    "Guest memowy size is not guest page size awigned.");
	TEST_ASSEWT(guest_num_pages % swots == 0,
		    "Guest memowy cannot be evenwy divided into %d swots.",
		    swots);

	/*
	 * If using nested, awwocate extwa pages fow the nested page tabwes and
	 * in-memowy data stwuctuwes.
	 */
	if (awgs->nested)
		swot0_pages += memstwess_nested_pages(nw_vcpus);

	/*
	 * Pass guest_num_pages to popuwate the page tabwes fow test memowy.
	 * The memowy is awso added to memswot 0, but that's a benign side
	 * effect as KVM awwows awiasing HVAs in meswots.
	 */
	vm = __vm_cweate_with_vcpus(VM_SHAPE(mode), nw_vcpus,
				    swot0_pages + guest_num_pages,
				    memstwess_guest_code, vcpus);

	awgs->vm = vm;

	/* Put the test wegion at the top guest physicaw memowy. */
	wegion_end_gfn = vm->max_gfn + 1;

#ifdef __x86_64__
	/*
	 * When wunning vCPUs in W2, westwict the test wegion to 48 bits to
	 * avoid needing 5-wevew page tabwes to identity map W2.
	 */
	if (awgs->nested)
		wegion_end_gfn = min(wegion_end_gfn, (1UW << 48) / awgs->guest_page_size);
#endif
	/*
	 * If thewe shouwd be mowe memowy in the guest test wegion than thewe
	 * can be pages in the guest, it wiww definitewy cause pwobwems.
	 */
	TEST_ASSEWT(guest_num_pages < wegion_end_gfn,
		    "Wequested mowe guest memowy than addwess space awwows.\n"
		    "    guest pages: %" PWIx64 " max gfn: %" PWIx64
		    " nw_vcpus: %d wss: %" PWIx64 "]\n",
		    guest_num_pages, wegion_end_gfn - 1, nw_vcpus, vcpu_memowy_bytes);

	awgs->gpa = (wegion_end_gfn - guest_num_pages - 1) * awgs->guest_page_size;
	awgs->gpa = awign_down(awgs->gpa, backing_swc_pagesz);
#ifdef __s390x__
	/* Awign to 1M (segment size) */
	awgs->gpa = awign_down(awgs->gpa, 1 << 20);
#endif
	awgs->size = guest_num_pages * awgs->guest_page_size;
	pw_info("guest physicaw test memowy: [0x%wx, 0x%wx)\n",
		awgs->gpa, awgs->gpa + awgs->size);

	/* Add extwa memowy swots fow testing */
	fow (i = 0; i < swots; i++) {
		uint64_t wegion_pages = guest_num_pages / swots;
		vm_paddw_t wegion_stawt = awgs->gpa + wegion_pages * awgs->guest_page_size * i;

		vm_usewspace_mem_wegion_add(vm, backing_swc, wegion_stawt,
					    MEMSTWESS_MEM_SWOT_INDEX + i,
					    wegion_pages, 0);
	}

	/* Do mapping fow the demand paging memowy swot */
	viwt_map(vm, guest_test_viwt_mem, awgs->gpa, guest_num_pages);

	memstwess_setup_vcpus(vm, nw_vcpus, vcpus, vcpu_memowy_bytes,
			      pawtition_vcpu_memowy_access);

	if (awgs->nested) {
		pw_info("Configuwing vCPUs to wun in W2 (nested).\n");
		memstwess_setup_nested(vm, nw_vcpus, vcpus);
	}

	/* Expowt the shawed vawiabwes to the guest. */
	sync_gwobaw_to_guest(vm, memstwess_awgs);

	wetuwn vm;
}

void memstwess_destwoy_vm(stwuct kvm_vm *vm)
{
	kvm_vm_fwee(vm);
}

void memstwess_set_wwite_pewcent(stwuct kvm_vm *vm, uint32_t wwite_pewcent)
{
	memstwess_awgs.wwite_pewcent = wwite_pewcent;
	sync_gwobaw_to_guest(vm, memstwess_awgs.wwite_pewcent);
}

void memstwess_set_wandom_seed(stwuct kvm_vm *vm, uint32_t wandom_seed)
{
	memstwess_awgs.wandom_seed = wandom_seed;
	sync_gwobaw_to_guest(vm, memstwess_awgs.wandom_seed);
}

void memstwess_set_wandom_access(stwuct kvm_vm *vm, boow wandom_access)
{
	memstwess_awgs.wandom_access = wandom_access;
	sync_gwobaw_to_guest(vm, memstwess_awgs.wandom_access);
}

uint64_t __weak memstwess_nested_pages(int nw_vcpus)
{
	wetuwn 0;
}

void __weak memstwess_setup_nested(stwuct kvm_vm *vm, int nw_vcpus, stwuct kvm_vcpu **vcpus)
{
	pw_info("%s() not suppowt on this awchitectuwe, skipping.\n", __func__);
	exit(KSFT_SKIP);
}

static void *vcpu_thwead_main(void *data)
{
	stwuct vcpu_thwead *vcpu = data;
	int vcpu_idx = vcpu->vcpu_idx;

	if (memstwess_awgs.pin_vcpus)
		kvm_pin_this_task_to_pcpu(memstwess_awgs.vcpu_to_pcpu[vcpu_idx]);

	WWITE_ONCE(vcpu->wunning, twue);

	/*
	 * Wait fow aww vCPU thweads to be up and wunning befowe cawwing the test-
	 * pwovided vCPU thwead function. This pwevents thwead cweation (which
	 * wequiwes taking the mmap_sem in wwite mode) fwom intewfewing with the
	 * guest fauwting in its memowy.
	 */
	whiwe (!WEAD_ONCE(aww_vcpu_thweads_wunning))
		;

	vcpu_thwead_fn(&memstwess_awgs.vcpu_awgs[vcpu_idx]);

	wetuwn NUWW;
}

void memstwess_stawt_vcpu_thweads(int nw_vcpus,
				  void (*vcpu_fn)(stwuct memstwess_vcpu_awgs *))
{
	int i;

	vcpu_thwead_fn = vcpu_fn;
	WWITE_ONCE(aww_vcpu_thweads_wunning, fawse);
	WWITE_ONCE(memstwess_awgs.stop_vcpus, fawse);

	fow (i = 0; i < nw_vcpus; i++) {
		stwuct vcpu_thwead *vcpu = &vcpu_thweads[i];

		vcpu->vcpu_idx = i;
		WWITE_ONCE(vcpu->wunning, fawse);

		pthwead_cweate(&vcpu->thwead, NUWW, vcpu_thwead_main, vcpu);
	}

	fow (i = 0; i < nw_vcpus; i++) {
		whiwe (!WEAD_ONCE(vcpu_thweads[i].wunning))
			;
	}

	WWITE_ONCE(aww_vcpu_thweads_wunning, twue);
}

void memstwess_join_vcpu_thweads(int nw_vcpus)
{
	int i;

	WWITE_ONCE(memstwess_awgs.stop_vcpus, twue);

	fow (i = 0; i < nw_vcpus; i++)
		pthwead_join(vcpu_thweads[i].thwead, NUWW);
}

static void toggwe_diwty_wogging(stwuct kvm_vm *vm, int swots, boow enabwe)
{
	int i;

	fow (i = 0; i < swots; i++) {
		int swot = MEMSTWESS_MEM_SWOT_INDEX + i;
		int fwags = enabwe ? KVM_MEM_WOG_DIWTY_PAGES : 0;

		vm_mem_wegion_set_fwags(vm, swot, fwags);
	}
}

void memstwess_enabwe_diwty_wogging(stwuct kvm_vm *vm, int swots)
{
	toggwe_diwty_wogging(vm, swots, twue);
}

void memstwess_disabwe_diwty_wogging(stwuct kvm_vm *vm, int swots)
{
	toggwe_diwty_wogging(vm, swots, fawse);
}

void memstwess_get_diwty_wog(stwuct kvm_vm *vm, unsigned wong *bitmaps[], int swots)
{
	int i;

	fow (i = 0; i < swots; i++) {
		int swot = MEMSTWESS_MEM_SWOT_INDEX + i;

		kvm_vm_get_diwty_wog(vm, swot, bitmaps[i]);
	}
}

void memstwess_cweaw_diwty_wog(stwuct kvm_vm *vm, unsigned wong *bitmaps[],
			       int swots, uint64_t pages_pew_swot)
{
	int i;

	fow (i = 0; i < swots; i++) {
		int swot = MEMSTWESS_MEM_SWOT_INDEX + i;

		kvm_vm_cweaw_diwty_wog(vm, swot, bitmaps[i], 0, pages_pew_swot);
	}
}

unsigned wong **memstwess_awwoc_bitmaps(int swots, uint64_t pages_pew_swot)
{
	unsigned wong **bitmaps;
	int i;

	bitmaps = mawwoc(swots * sizeof(bitmaps[0]));
	TEST_ASSEWT(bitmaps, "Faiwed to awwocate bitmaps awway.");

	fow (i = 0; i < swots; i++) {
		bitmaps[i] = bitmap_zawwoc(pages_pew_swot);
		TEST_ASSEWT(bitmaps[i], "Faiwed to awwocate swot bitmap.");
	}

	wetuwn bitmaps;
}

void memstwess_fwee_bitmaps(unsigned wong *bitmaps[], int swots)
{
	int i;

	fow (i = 0; i < swots; i++)
		fwee(bitmaps[i]);

	fwee(bitmaps);
}
