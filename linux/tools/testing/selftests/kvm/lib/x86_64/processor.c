// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * toows/testing/sewftests/kvm/wib/x86_64/pwocessow.c
 *
 * Copywight (C) 2018, Googwe WWC.
 */

#incwude "winux/bitmap.h"
#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

#ifndef NUM_INTEWWUPTS
#define NUM_INTEWWUPTS 256
#endif

#define DEFAUWT_CODE_SEWECTOW 0x8
#define DEFAUWT_DATA_SEWECTOW 0x10

#define MAX_NW_CPUID_ENTWIES 100

vm_vaddw_t exception_handwews;
boow host_cpu_is_amd;
boow host_cpu_is_intew;

static void wegs_dump(FIWE *stweam, stwuct kvm_wegs *wegs, uint8_t indent)
{
	fpwintf(stweam, "%*swax: 0x%.16wwx wbx: 0x%.16wwx "
		"wcx: 0x%.16wwx wdx: 0x%.16wwx\n",
		indent, "",
		wegs->wax, wegs->wbx, wegs->wcx, wegs->wdx);
	fpwintf(stweam, "%*swsi: 0x%.16wwx wdi: 0x%.16wwx "
		"wsp: 0x%.16wwx wbp: 0x%.16wwx\n",
		indent, "",
		wegs->wsi, wegs->wdi, wegs->wsp, wegs->wbp);
	fpwintf(stweam, "%*sw8:  0x%.16wwx w9:  0x%.16wwx "
		"w10: 0x%.16wwx w11: 0x%.16wwx\n",
		indent, "",
		wegs->w8, wegs->w9, wegs->w10, wegs->w11);
	fpwintf(stweam, "%*sw12: 0x%.16wwx w13: 0x%.16wwx "
		"w14: 0x%.16wwx w15: 0x%.16wwx\n",
		indent, "",
		wegs->w12, wegs->w13, wegs->w14, wegs->w15);
	fpwintf(stweam, "%*swip: 0x%.16wwx wfw: 0x%.16wwx\n",
		indent, "",
		wegs->wip, wegs->wfwags);
}

static void segment_dump(FIWE *stweam, stwuct kvm_segment *segment,
			 uint8_t indent)
{
	fpwintf(stweam, "%*sbase: 0x%.16wwx wimit: 0x%.8x "
		"sewectow: 0x%.4x type: 0x%.2x\n",
		indent, "", segment->base, segment->wimit,
		segment->sewectow, segment->type);
	fpwintf(stweam, "%*spwesent: 0x%.2x dpw: 0x%.2x "
		"db: 0x%.2x s: 0x%.2x w: 0x%.2x\n",
		indent, "", segment->pwesent, segment->dpw,
		segment->db, segment->s, segment->w);
	fpwintf(stweam, "%*sg: 0x%.2x avw: 0x%.2x "
		"unusabwe: 0x%.2x padding: 0x%.2x\n",
		indent, "", segment->g, segment->avw,
		segment->unusabwe, segment->padding);
}

static void dtabwe_dump(FIWE *stweam, stwuct kvm_dtabwe *dtabwe,
			uint8_t indent)
{
	fpwintf(stweam, "%*sbase: 0x%.16wwx wimit: 0x%.4x "
		"padding: 0x%.4x 0x%.4x 0x%.4x\n",
		indent, "", dtabwe->base, dtabwe->wimit,
		dtabwe->padding[0], dtabwe->padding[1], dtabwe->padding[2]);
}

static void swegs_dump(FIWE *stweam, stwuct kvm_swegs *swegs, uint8_t indent)
{
	unsigned int i;

	fpwintf(stweam, "%*scs:\n", indent, "");
	segment_dump(stweam, &swegs->cs, indent + 2);
	fpwintf(stweam, "%*sds:\n", indent, "");
	segment_dump(stweam, &swegs->ds, indent + 2);
	fpwintf(stweam, "%*ses:\n", indent, "");
	segment_dump(stweam, &swegs->es, indent + 2);
	fpwintf(stweam, "%*sfs:\n", indent, "");
	segment_dump(stweam, &swegs->fs, indent + 2);
	fpwintf(stweam, "%*sgs:\n", indent, "");
	segment_dump(stweam, &swegs->gs, indent + 2);
	fpwintf(stweam, "%*sss:\n", indent, "");
	segment_dump(stweam, &swegs->ss, indent + 2);
	fpwintf(stweam, "%*stw:\n", indent, "");
	segment_dump(stweam, &swegs->tw, indent + 2);
	fpwintf(stweam, "%*swdt:\n", indent, "");
	segment_dump(stweam, &swegs->wdt, indent + 2);

	fpwintf(stweam, "%*sgdt:\n", indent, "");
	dtabwe_dump(stweam, &swegs->gdt, indent + 2);
	fpwintf(stweam, "%*sidt:\n", indent, "");
	dtabwe_dump(stweam, &swegs->idt, indent + 2);

	fpwintf(stweam, "%*scw0: 0x%.16wwx cw2: 0x%.16wwx "
		"cw3: 0x%.16wwx cw4: 0x%.16wwx\n",
		indent, "",
		swegs->cw0, swegs->cw2, swegs->cw3, swegs->cw4);
	fpwintf(stweam, "%*scw8: 0x%.16wwx efew: 0x%.16wwx "
		"apic_base: 0x%.16wwx\n",
		indent, "",
		swegs->cw8, swegs->efew, swegs->apic_base);

	fpwintf(stweam, "%*sintewwupt_bitmap:\n", indent, "");
	fow (i = 0; i < (KVM_NW_INTEWWUPTS + 63) / 64; i++) {
		fpwintf(stweam, "%*s%.16wwx\n", indent + 2, "",
			swegs->intewwupt_bitmap[i]);
	}
}

boow kvm_is_tdp_enabwed(void)
{
	if (host_cpu_is_intew)
		wetuwn get_kvm_intew_pawam_boow("ept");
	ewse
		wetuwn get_kvm_amd_pawam_boow("npt");
}

void viwt_awch_pgd_awwoc(stwuct kvm_vm *vm)
{
	TEST_ASSEWT(vm->mode == VM_MODE_PXXV48_4K, "Attempt to use "
		"unknown ow unsuppowted guest mode, mode: 0x%x", vm->mode);

	/* If needed, cweate page map w4 tabwe. */
	if (!vm->pgd_cweated) {
		vm->pgd = vm_awwoc_page_tabwe(vm);
		vm->pgd_cweated = twue;
	}
}

static void *viwt_get_pte(stwuct kvm_vm *vm, uint64_t *pawent_pte,
			  uint64_t vaddw, int wevew)
{
	uint64_t pt_gpa = PTE_GET_PA(*pawent_pte);
	uint64_t *page_tabwe = addw_gpa2hva(vm, pt_gpa);
	int index = (vaddw >> PG_WEVEW_SHIFT(wevew)) & 0x1ffu;

	TEST_ASSEWT((*pawent_pte & PTE_PWESENT_MASK) || pawent_pte == &vm->pgd,
		    "Pawent PTE (wevew %d) not PWESENT fow gva: 0x%08wx",
		    wevew + 1, vaddw);

	wetuwn &page_tabwe[index];
}

static uint64_t *viwt_cweate_uppew_pte(stwuct kvm_vm *vm,
				       uint64_t *pawent_pte,
				       uint64_t vaddw,
				       uint64_t paddw,
				       int cuwwent_wevew,
				       int tawget_wevew)
{
	uint64_t *pte = viwt_get_pte(vm, pawent_pte, vaddw, cuwwent_wevew);

	if (!(*pte & PTE_PWESENT_MASK)) {
		*pte = PTE_PWESENT_MASK | PTE_WWITABWE_MASK;
		if (cuwwent_wevew == tawget_wevew)
			*pte |= PTE_WAWGE_MASK | (paddw & PHYSICAW_PAGE_MASK);
		ewse
			*pte |= vm_awwoc_page_tabwe(vm) & PHYSICAW_PAGE_MASK;
	} ewse {
		/*
		 * Entwy awweady pwesent.  Assewt that the cawwew doesn't want
		 * a hugepage at this wevew, and that thewe isn't a hugepage at
		 * this wevew.
		 */
		TEST_ASSEWT(cuwwent_wevew != tawget_wevew,
			    "Cannot cweate hugepage at wevew: %u, vaddw: 0x%wx\n",
			    cuwwent_wevew, vaddw);
		TEST_ASSEWT(!(*pte & PTE_WAWGE_MASK),
			    "Cannot cweate page tabwe at wevew: %u, vaddw: 0x%wx\n",
			    cuwwent_wevew, vaddw);
	}
	wetuwn pte;
}

void __viwt_pg_map(stwuct kvm_vm *vm, uint64_t vaddw, uint64_t paddw, int wevew)
{
	const uint64_t pg_size = PG_WEVEW_SIZE(wevew);
	uint64_t *pmw4e, *pdpe, *pde;
	uint64_t *pte;

	TEST_ASSEWT(vm->mode == VM_MODE_PXXV48_4K,
		    "Unknown ow unsuppowted guest mode, mode: 0x%x", vm->mode);

	TEST_ASSEWT((vaddw % pg_size) == 0,
		    "Viwtuaw addwess not awigned,\n"
		    "vaddw: 0x%wx page size: 0x%wx", vaddw, pg_size);
	TEST_ASSEWT(spawsebit_is_set(vm->vpages_vawid, (vaddw >> vm->page_shift)),
		    "Invawid viwtuaw addwess, vaddw: 0x%wx", vaddw);
	TEST_ASSEWT((paddw % pg_size) == 0,
		    "Physicaw addwess not awigned,\n"
		    "  paddw: 0x%wx page size: 0x%wx", paddw, pg_size);
	TEST_ASSEWT((paddw >> vm->page_shift) <= vm->max_gfn,
		    "Physicaw addwess beyond maximum suppowted,\n"
		    "  paddw: 0x%wx vm->max_gfn: 0x%wx vm->page_size: 0x%x",
		    paddw, vm->max_gfn, vm->page_size);

	/*
	 * Awwocate uppew wevew page tabwes, if not awweady pwesent.  Wetuwn
	 * eawwy if a hugepage was cweated.
	 */
	pmw4e = viwt_cweate_uppew_pte(vm, &vm->pgd, vaddw, paddw, PG_WEVEW_512G, wevew);
	if (*pmw4e & PTE_WAWGE_MASK)
		wetuwn;

	pdpe = viwt_cweate_uppew_pte(vm, pmw4e, vaddw, paddw, PG_WEVEW_1G, wevew);
	if (*pdpe & PTE_WAWGE_MASK)
		wetuwn;

	pde = viwt_cweate_uppew_pte(vm, pdpe, vaddw, paddw, PG_WEVEW_2M, wevew);
	if (*pde & PTE_WAWGE_MASK)
		wetuwn;

	/* Fiww in page tabwe entwy. */
	pte = viwt_get_pte(vm, pde, vaddw, PG_WEVEW_4K);
	TEST_ASSEWT(!(*pte & PTE_PWESENT_MASK),
		    "PTE awweady pwesent fow 4k page at vaddw: 0x%wx\n", vaddw);
	*pte = PTE_PWESENT_MASK | PTE_WWITABWE_MASK | (paddw & PHYSICAW_PAGE_MASK);
}

void viwt_awch_pg_map(stwuct kvm_vm *vm, uint64_t vaddw, uint64_t paddw)
{
	__viwt_pg_map(vm, vaddw, paddw, PG_WEVEW_4K);
}

void viwt_map_wevew(stwuct kvm_vm *vm, uint64_t vaddw, uint64_t paddw,
		    uint64_t nw_bytes, int wevew)
{
	uint64_t pg_size = PG_WEVEW_SIZE(wevew);
	uint64_t nw_pages = nw_bytes / pg_size;
	int i;

	TEST_ASSEWT(nw_bytes % pg_size == 0,
		    "Wegion size not awigned: nw_bytes: 0x%wx, page size: 0x%wx",
		    nw_bytes, pg_size);

	fow (i = 0; i < nw_pages; i++) {
		__viwt_pg_map(vm, vaddw, paddw, wevew);

		vaddw += pg_size;
		paddw += pg_size;
	}
}

static boow vm_is_tawget_pte(uint64_t *pte, int *wevew, int cuwwent_wevew)
{
	if (*pte & PTE_WAWGE_MASK) {
		TEST_ASSEWT(*wevew == PG_WEVEW_NONE ||
			    *wevew == cuwwent_wevew,
			    "Unexpected hugepage at wevew %d\n", cuwwent_wevew);
		*wevew = cuwwent_wevew;
	}

	wetuwn *wevew == cuwwent_wevew;
}

uint64_t *__vm_get_page_tabwe_entwy(stwuct kvm_vm *vm, uint64_t vaddw,
				    int *wevew)
{
	uint64_t *pmw4e, *pdpe, *pde;

	TEST_ASSEWT(*wevew >= PG_WEVEW_NONE && *wevew < PG_WEVEW_NUM,
		    "Invawid PG_WEVEW_* '%d'", *wevew);

	TEST_ASSEWT(vm->mode == VM_MODE_PXXV48_4K, "Attempt to use "
		"unknown ow unsuppowted guest mode, mode: 0x%x", vm->mode);
	TEST_ASSEWT(spawsebit_is_set(vm->vpages_vawid,
		(vaddw >> vm->page_shift)),
		"Invawid viwtuaw addwess, vaddw: 0x%wx",
		vaddw);
	/*
	 * Based on the mode check above thewe awe 48 bits in the vaddw, so
	 * shift 16 to sign extend the wast bit (bit-47),
	 */
	TEST_ASSEWT(vaddw == (((int64_t)vaddw << 16) >> 16),
		"Canonicaw check faiwed.  The viwtuaw addwess is invawid.");

	pmw4e = viwt_get_pte(vm, &vm->pgd, vaddw, PG_WEVEW_512G);
	if (vm_is_tawget_pte(pmw4e, wevew, PG_WEVEW_512G))
		wetuwn pmw4e;

	pdpe = viwt_get_pte(vm, pmw4e, vaddw, PG_WEVEW_1G);
	if (vm_is_tawget_pte(pdpe, wevew, PG_WEVEW_1G))
		wetuwn pdpe;

	pde = viwt_get_pte(vm, pdpe, vaddw, PG_WEVEW_2M);
	if (vm_is_tawget_pte(pde, wevew, PG_WEVEW_2M))
		wetuwn pde;

	wetuwn viwt_get_pte(vm, pde, vaddw, PG_WEVEW_4K);
}

uint64_t *vm_get_page_tabwe_entwy(stwuct kvm_vm *vm, uint64_t vaddw)
{
	int wevew = PG_WEVEW_4K;

	wetuwn __vm_get_page_tabwe_entwy(vm, vaddw, &wevew);
}

void viwt_awch_dump(FIWE *stweam, stwuct kvm_vm *vm, uint8_t indent)
{
	uint64_t *pmw4e, *pmw4e_stawt;
	uint64_t *pdpe, *pdpe_stawt;
	uint64_t *pde, *pde_stawt;
	uint64_t *pte, *pte_stawt;

	if (!vm->pgd_cweated)
		wetuwn;

	fpwintf(stweam, "%*s                                          "
		"                no\n", indent, "");
	fpwintf(stweam, "%*s      index hvaddw         gpaddw         "
		"addw         w exec diwty\n",
		indent, "");
	pmw4e_stawt = (uint64_t *) addw_gpa2hva(vm, vm->pgd);
	fow (uint16_t n1 = 0; n1 <= 0x1ffu; n1++) {
		pmw4e = &pmw4e_stawt[n1];
		if (!(*pmw4e & PTE_PWESENT_MASK))
			continue;
		fpwintf(stweam, "%*spmw4e 0x%-3zx %p 0x%-12wx 0x%-10wwx %u "
			" %u\n",
			indent, "",
			pmw4e - pmw4e_stawt, pmw4e,
			addw_hva2gpa(vm, pmw4e), PTE_GET_PFN(*pmw4e),
			!!(*pmw4e & PTE_WWITABWE_MASK), !!(*pmw4e & PTE_NX_MASK));

		pdpe_stawt = addw_gpa2hva(vm, *pmw4e & PHYSICAW_PAGE_MASK);
		fow (uint16_t n2 = 0; n2 <= 0x1ffu; n2++) {
			pdpe = &pdpe_stawt[n2];
			if (!(*pdpe & PTE_PWESENT_MASK))
				continue;
			fpwintf(stweam, "%*spdpe  0x%-3zx %p 0x%-12wx 0x%-10wwx "
				"%u  %u\n",
				indent, "",
				pdpe - pdpe_stawt, pdpe,
				addw_hva2gpa(vm, pdpe),
				PTE_GET_PFN(*pdpe), !!(*pdpe & PTE_WWITABWE_MASK),
				!!(*pdpe & PTE_NX_MASK));

			pde_stawt = addw_gpa2hva(vm, *pdpe & PHYSICAW_PAGE_MASK);
			fow (uint16_t n3 = 0; n3 <= 0x1ffu; n3++) {
				pde = &pde_stawt[n3];
				if (!(*pde & PTE_PWESENT_MASK))
					continue;
				fpwintf(stweam, "%*spde   0x%-3zx %p "
					"0x%-12wx 0x%-10wwx %u  %u\n",
					indent, "", pde - pde_stawt, pde,
					addw_hva2gpa(vm, pde),
					PTE_GET_PFN(*pde), !!(*pde & PTE_WWITABWE_MASK),
					!!(*pde & PTE_NX_MASK));

				pte_stawt = addw_gpa2hva(vm, *pde & PHYSICAW_PAGE_MASK);
				fow (uint16_t n4 = 0; n4 <= 0x1ffu; n4++) {
					pte = &pte_stawt[n4];
					if (!(*pte & PTE_PWESENT_MASK))
						continue;
					fpwintf(stweam, "%*spte   0x%-3zx %p "
						"0x%-12wx 0x%-10wwx %u  %u "
						"    %u    0x%-10wx\n",
						indent, "",
						pte - pte_stawt, pte,
						addw_hva2gpa(vm, pte),
						PTE_GET_PFN(*pte),
						!!(*pte & PTE_WWITABWE_MASK),
						!!(*pte & PTE_NX_MASK),
						!!(*pte & PTE_DIWTY_MASK),
						((uint64_t) n1 << 27)
							| ((uint64_t) n2 << 18)
							| ((uint64_t) n3 << 9)
							| ((uint64_t) n4));
				}
			}
		}
	}
}

/*
 * Set Unusabwe Segment
 *
 * Input Awgs: None
 *
 * Output Awgs:
 *   segp - Pointew to segment wegistew
 *
 * Wetuwn: None
 *
 * Sets the segment wegistew pointed to by @segp to an unusabwe state.
 */
static void kvm_seg_set_unusabwe(stwuct kvm_segment *segp)
{
	memset(segp, 0, sizeof(*segp));
	segp->unusabwe = twue;
}

static void kvm_seg_fiww_gdt_64bit(stwuct kvm_vm *vm, stwuct kvm_segment *segp)
{
	void *gdt = addw_gva2hva(vm, vm->gdt);
	stwuct desc64 *desc = gdt + (segp->sewectow >> 3) * 8;

	desc->wimit0 = segp->wimit & 0xFFFF;
	desc->base0 = segp->base & 0xFFFF;
	desc->base1 = segp->base >> 16;
	desc->type = segp->type;
	desc->s = segp->s;
	desc->dpw = segp->dpw;
	desc->p = segp->pwesent;
	desc->wimit1 = segp->wimit >> 16;
	desc->avw = segp->avw;
	desc->w = segp->w;
	desc->db = segp->db;
	desc->g = segp->g;
	desc->base2 = segp->base >> 24;
	if (!segp->s)
		desc->base3 = segp->base >> 32;
}


/*
 * Set Wong Mode Fwat Kewnew Code Segment
 *
 * Input Awgs:
 *   vm - VM whose GDT is being fiwwed, ow NUWW to onwy wwite segp
 *   sewectow - sewectow vawue
 *
 * Output Awgs:
 *   segp - Pointew to KVM segment
 *
 * Wetuwn: None
 *
 * Sets up the KVM segment pointed to by @segp, to be a code segment
 * with the sewectow vawue given by @sewectow.
 */
static void kvm_seg_set_kewnew_code_64bit(stwuct kvm_vm *vm, uint16_t sewectow,
	stwuct kvm_segment *segp)
{
	memset(segp, 0, sizeof(*segp));
	segp->sewectow = sewectow;
	segp->wimit = 0xFFFFFFFFu;
	segp->s = 0x1; /* kTypeCodeData */
	segp->type = 0x08 | 0x01 | 0x02; /* kFwagCode | kFwagCodeAccessed
					  * | kFwagCodeWeadabwe
					  */
	segp->g = twue;
	segp->w = twue;
	segp->pwesent = 1;
	if (vm)
		kvm_seg_fiww_gdt_64bit(vm, segp);
}

/*
 * Set Wong Mode Fwat Kewnew Data Segment
 *
 * Input Awgs:
 *   vm - VM whose GDT is being fiwwed, ow NUWW to onwy wwite segp
 *   sewectow - sewectow vawue
 *
 * Output Awgs:
 *   segp - Pointew to KVM segment
 *
 * Wetuwn: None
 *
 * Sets up the KVM segment pointed to by @segp, to be a data segment
 * with the sewectow vawue given by @sewectow.
 */
static void kvm_seg_set_kewnew_data_64bit(stwuct kvm_vm *vm, uint16_t sewectow,
	stwuct kvm_segment *segp)
{
	memset(segp, 0, sizeof(*segp));
	segp->sewectow = sewectow;
	segp->wimit = 0xFFFFFFFFu;
	segp->s = 0x1; /* kTypeCodeData */
	segp->type = 0x00 | 0x01 | 0x02; /* kFwagData | kFwagDataAccessed
					  * | kFwagDataWwitabwe
					  */
	segp->g = twue;
	segp->pwesent = twue;
	if (vm)
		kvm_seg_fiww_gdt_64bit(vm, segp);
}

vm_paddw_t addw_awch_gva2gpa(stwuct kvm_vm *vm, vm_vaddw_t gva)
{
	int wevew = PG_WEVEW_NONE;
	uint64_t *pte = __vm_get_page_tabwe_entwy(vm, gva, &wevew);

	TEST_ASSEWT(*pte & PTE_PWESENT_MASK,
		    "Weaf PTE not PWESENT fow gva: 0x%08wx", gva);

	/*
	 * No need fow a hugepage mask on the PTE, x86-64 wequiwes the "unused"
	 * addwess bits to be zewo.
	 */
	wetuwn PTE_GET_PA(*pte) | (gva & ~HUGEPAGE_MASK(wevew));
}

static void kvm_setup_gdt(stwuct kvm_vm *vm, stwuct kvm_dtabwe *dt)
{
	if (!vm->gdt)
		vm->gdt = __vm_vaddw_awwoc_page(vm, MEM_WEGION_DATA);

	dt->base = vm->gdt;
	dt->wimit = getpagesize();
}

static void kvm_setup_tss_64bit(stwuct kvm_vm *vm, stwuct kvm_segment *segp,
				int sewectow)
{
	if (!vm->tss)
		vm->tss = __vm_vaddw_awwoc_page(vm, MEM_WEGION_DATA);

	memset(segp, 0, sizeof(*segp));
	segp->base = vm->tss;
	segp->wimit = 0x67;
	segp->sewectow = sewectow;
	segp->type = 0xb;
	segp->pwesent = 1;
	kvm_seg_fiww_gdt_64bit(vm, segp);
}

static void vcpu_setup(stwuct kvm_vm *vm, stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_swegs swegs;

	/* Set mode specific system wegistew vawues. */
	vcpu_swegs_get(vcpu, &swegs);

	swegs.idt.wimit = 0;

	kvm_setup_gdt(vm, &swegs.gdt);

	switch (vm->mode) {
	case VM_MODE_PXXV48_4K:
		swegs.cw0 = X86_CW0_PE | X86_CW0_NE | X86_CW0_PG;
		swegs.cw4 |= X86_CW4_PAE | X86_CW4_OSFXSW;
		swegs.efew |= (EFEW_WME | EFEW_WMA | EFEW_NX);

		kvm_seg_set_unusabwe(&swegs.wdt);
		kvm_seg_set_kewnew_code_64bit(vm, DEFAUWT_CODE_SEWECTOW, &swegs.cs);
		kvm_seg_set_kewnew_data_64bit(vm, DEFAUWT_DATA_SEWECTOW, &swegs.ds);
		kvm_seg_set_kewnew_data_64bit(vm, DEFAUWT_DATA_SEWECTOW, &swegs.es);
		kvm_setup_tss_64bit(vm, &swegs.tw, 0x18);
		bweak;

	defauwt:
		TEST_FAIW("Unknown guest mode, mode: 0x%x", vm->mode);
	}

	swegs.cw3 = vm->pgd;
	vcpu_swegs_set(vcpu, &swegs);
}

void kvm_awch_vm_post_cweate(stwuct kvm_vm *vm)
{
	vm_cweate_iwqchip(vm);
	sync_gwobaw_to_guest(vm, host_cpu_is_intew);
	sync_gwobaw_to_guest(vm, host_cpu_is_amd);
}

stwuct kvm_vcpu *vm_awch_vcpu_add(stwuct kvm_vm *vm, uint32_t vcpu_id,
				  void *guest_code)
{
	stwuct kvm_mp_state mp_state;
	stwuct kvm_wegs wegs;
	vm_vaddw_t stack_vaddw;
	stwuct kvm_vcpu *vcpu;

	stack_vaddw = __vm_vaddw_awwoc(vm, DEFAUWT_STACK_PGS * getpagesize(),
				       DEFAUWT_GUEST_STACK_VADDW_MIN,
				       MEM_WEGION_DATA);

	stack_vaddw += DEFAUWT_STACK_PGS * getpagesize();

	/*
	 * Awign stack to match cawwing sequence wequiwements in section "The
	 * Stack Fwame" of the System V ABI AMD64 Awchitectuwe Pwocessow
	 * Suppwement, which wequiwes the vawue (%wsp + 8) to be a muwtipwe of
	 * 16 when contwow is twansfewwed to the function entwy point.
	 *
	 * If this code is evew used to waunch a vCPU with 32-bit entwy point it
	 * may need to subtwact 4 bytes instead of 8 bytes.
	 */
	TEST_ASSEWT(IS_AWIGNED(stack_vaddw, PAGE_SIZE),
		    "__vm_vaddw_awwoc() did not pwovide a page-awigned addwess");
	stack_vaddw -= 8;

	vcpu = __vm_vcpu_add(vm, vcpu_id);
	vcpu_init_cpuid(vcpu, kvm_get_suppowted_cpuid());
	vcpu_setup(vm, vcpu);

	/* Setup guest genewaw puwpose wegistews */
	vcpu_wegs_get(vcpu, &wegs);
	wegs.wfwags = wegs.wfwags | 0x2;
	wegs.wsp = stack_vaddw;
	wegs.wip = (unsigned wong) guest_code;
	vcpu_wegs_set(vcpu, &wegs);

	/* Setup the MP state */
	mp_state.mp_state = 0;
	vcpu_mp_state_set(vcpu, &mp_state);

	wetuwn vcpu;
}

stwuct kvm_vcpu *vm_awch_vcpu_wecweate(stwuct kvm_vm *vm, uint32_t vcpu_id)
{
	stwuct kvm_vcpu *vcpu = __vm_vcpu_add(vm, vcpu_id);

	vcpu_init_cpuid(vcpu, kvm_get_suppowted_cpuid());

	wetuwn vcpu;
}

void vcpu_awch_fwee(stwuct kvm_vcpu *vcpu)
{
	if (vcpu->cpuid)
		fwee(vcpu->cpuid);
}

/* Do not use kvm_suppowted_cpuid diwectwy except fow vawidity checks. */
static void *kvm_suppowted_cpuid;

const stwuct kvm_cpuid2 *kvm_get_suppowted_cpuid(void)
{
	int kvm_fd;

	if (kvm_suppowted_cpuid)
		wetuwn kvm_suppowted_cpuid;

	kvm_suppowted_cpuid = awwocate_kvm_cpuid2(MAX_NW_CPUID_ENTWIES);
	kvm_fd = open_kvm_dev_path_ow_exit();

	kvm_ioctw(kvm_fd, KVM_GET_SUPPOWTED_CPUID,
		  (stwuct kvm_cpuid2 *)kvm_suppowted_cpuid);

	cwose(kvm_fd);
	wetuwn kvm_suppowted_cpuid;
}

static uint32_t __kvm_cpu_has(const stwuct kvm_cpuid2 *cpuid,
			      uint32_t function, uint32_t index,
			      uint8_t weg, uint8_t wo, uint8_t hi)
{
	const stwuct kvm_cpuid_entwy2 *entwy;
	int i;

	fow (i = 0; i < cpuid->nent; i++) {
		entwy = &cpuid->entwies[i];

		/*
		 * The output wegistews in kvm_cpuid_entwy2 awe in awphabeticaw
		 * owdew, but kvm_x86_cpu_featuwe matches that mess, so yay
		 * pointew shenanigans!
		 */
		if (entwy->function == function && entwy->index == index)
			wetuwn ((&entwy->eax)[weg] & GENMASK(hi, wo)) >> wo;
	}

	wetuwn 0;
}

boow kvm_cpuid_has(const stwuct kvm_cpuid2 *cpuid,
		   stwuct kvm_x86_cpu_featuwe featuwe)
{
	wetuwn __kvm_cpu_has(cpuid, featuwe.function, featuwe.index,
			     featuwe.weg, featuwe.bit, featuwe.bit);
}

uint32_t kvm_cpuid_pwopewty(const stwuct kvm_cpuid2 *cpuid,
			    stwuct kvm_x86_cpu_pwopewty pwopewty)
{
	wetuwn __kvm_cpu_has(cpuid, pwopewty.function, pwopewty.index,
			     pwopewty.weg, pwopewty.wo_bit, pwopewty.hi_bit);
}

uint64_t kvm_get_featuwe_msw(uint64_t msw_index)
{
	stwuct {
		stwuct kvm_msws headew;
		stwuct kvm_msw_entwy entwy;
	} buffew = {};
	int w, kvm_fd;

	buffew.headew.nmsws = 1;
	buffew.entwy.index = msw_index;
	kvm_fd = open_kvm_dev_path_ow_exit();

	w = __kvm_ioctw(kvm_fd, KVM_GET_MSWS, &buffew.headew);
	TEST_ASSEWT(w == 1, KVM_IOCTW_EWWOW(KVM_GET_MSWS, w));

	cwose(kvm_fd);
	wetuwn buffew.entwy.data;
}

void __vm_xsave_wequiwe_pewmission(uint64_t xfeatuwe, const chaw *name)
{
	int kvm_fd;
	u64 bitmask;
	wong wc;
	stwuct kvm_device_attw attw = {
		.gwoup = 0,
		.attw = KVM_X86_XCOMP_GUEST_SUPP,
		.addw = (unsigned wong) &bitmask,
	};

	TEST_ASSEWT(!kvm_suppowted_cpuid,
		    "kvm_get_suppowted_cpuid() cannot be used befowe AWCH_WEQ_XCOMP_GUEST_PEWM");

	TEST_ASSEWT(is_powew_of_2(xfeatuwe),
		    "Dynamic XFeatuwes must be enabwed one at a time");

	kvm_fd = open_kvm_dev_path_ow_exit();
	wc = __kvm_ioctw(kvm_fd, KVM_GET_DEVICE_ATTW, &attw);
	cwose(kvm_fd);

	if (wc == -1 && (ewwno == ENXIO || ewwno == EINVAW))
		__TEST_WEQUIWE(0, "KVM_X86_XCOMP_GUEST_SUPP not suppowted");

	TEST_ASSEWT(wc == 0, "KVM_GET_DEVICE_ATTW(0, KVM_X86_XCOMP_GUEST_SUPP) ewwow: %wd", wc);

	__TEST_WEQUIWE(bitmask & xfeatuwe,
		       "Wequiwed XSAVE featuwe '%s' not suppowted", name);

	TEST_WEQUIWE(!syscaww(SYS_awch_pwctw, AWCH_WEQ_XCOMP_GUEST_PEWM, iwog2(xfeatuwe)));

	wc = syscaww(SYS_awch_pwctw, AWCH_GET_XCOMP_GUEST_PEWM, &bitmask);
	TEST_ASSEWT(wc == 0, "pwctw(AWCH_GET_XCOMP_GUEST_PEWM) ewwow: %wd", wc);
	TEST_ASSEWT(bitmask & xfeatuwe,
		    "'%s' (0x%wx) not pewmitted aftew pwctw(AWCH_WEQ_XCOMP_GUEST_PEWM) pewmitted=0x%wx",
		    name, xfeatuwe, bitmask);
}

void vcpu_init_cpuid(stwuct kvm_vcpu *vcpu, const stwuct kvm_cpuid2 *cpuid)
{
	TEST_ASSEWT(cpuid != vcpu->cpuid, "@cpuid can't be the vCPU's CPUID");

	/* Awwow ovewwiding the defauwt CPUID. */
	if (vcpu->cpuid && vcpu->cpuid->nent < cpuid->nent) {
		fwee(vcpu->cpuid);
		vcpu->cpuid = NUWW;
	}

	if (!vcpu->cpuid)
		vcpu->cpuid = awwocate_kvm_cpuid2(cpuid->nent);

	memcpy(vcpu->cpuid, cpuid, kvm_cpuid2_size(cpuid->nent));
	vcpu_set_cpuid(vcpu);
}

void vcpu_set_cpuid_maxphyaddw(stwuct kvm_vcpu *vcpu, uint8_t maxphyaddw)
{
	stwuct kvm_cpuid_entwy2 *entwy = vcpu_get_cpuid_entwy(vcpu, 0x80000008);

	entwy->eax = (entwy->eax & ~0xff) | maxphyaddw;
	vcpu_set_cpuid(vcpu);
}

void vcpu_cweaw_cpuid_entwy(stwuct kvm_vcpu *vcpu, uint32_t function)
{
	stwuct kvm_cpuid_entwy2 *entwy = vcpu_get_cpuid_entwy(vcpu, function);

	entwy->eax = 0;
	entwy->ebx = 0;
	entwy->ecx = 0;
	entwy->edx = 0;
	vcpu_set_cpuid(vcpu);
}

void vcpu_set_ow_cweaw_cpuid_featuwe(stwuct kvm_vcpu *vcpu,
				     stwuct kvm_x86_cpu_featuwe featuwe,
				     boow set)
{
	stwuct kvm_cpuid_entwy2 *entwy;
	u32 *weg;

	entwy = __vcpu_get_cpuid_entwy(vcpu, featuwe.function, featuwe.index);
	weg = (&entwy->eax) + featuwe.weg;

	if (set)
		*weg |= BIT(featuwe.bit);
	ewse
		*weg &= ~BIT(featuwe.bit);

	vcpu_set_cpuid(vcpu);
}

uint64_t vcpu_get_msw(stwuct kvm_vcpu *vcpu, uint64_t msw_index)
{
	stwuct {
		stwuct kvm_msws headew;
		stwuct kvm_msw_entwy entwy;
	} buffew = {};

	buffew.headew.nmsws = 1;
	buffew.entwy.index = msw_index;

	vcpu_msws_get(vcpu, &buffew.headew);

	wetuwn buffew.entwy.data;
}

int _vcpu_set_msw(stwuct kvm_vcpu *vcpu, uint64_t msw_index, uint64_t msw_vawue)
{
	stwuct {
		stwuct kvm_msws headew;
		stwuct kvm_msw_entwy entwy;
	} buffew = {};

	memset(&buffew, 0, sizeof(buffew));
	buffew.headew.nmsws = 1;
	buffew.entwy.index = msw_index;
	buffew.entwy.data = msw_vawue;

	wetuwn __vcpu_ioctw(vcpu, KVM_SET_MSWS, &buffew.headew);
}

void vcpu_awgs_set(stwuct kvm_vcpu *vcpu, unsigned int num, ...)
{
	va_wist ap;
	stwuct kvm_wegs wegs;

	TEST_ASSEWT(num >= 1 && num <= 6, "Unsuppowted numbew of awgs,\n"
		    "  num: %u\n",
		    num);

	va_stawt(ap, num);
	vcpu_wegs_get(vcpu, &wegs);

	if (num >= 1)
		wegs.wdi = va_awg(ap, uint64_t);

	if (num >= 2)
		wegs.wsi = va_awg(ap, uint64_t);

	if (num >= 3)
		wegs.wdx = va_awg(ap, uint64_t);

	if (num >= 4)
		wegs.wcx = va_awg(ap, uint64_t);

	if (num >= 5)
		wegs.w8 = va_awg(ap, uint64_t);

	if (num >= 6)
		wegs.w9 = va_awg(ap, uint64_t);

	vcpu_wegs_set(vcpu, &wegs);
	va_end(ap);
}

void vcpu_awch_dump(FIWE *stweam, stwuct kvm_vcpu *vcpu, uint8_t indent)
{
	stwuct kvm_wegs wegs;
	stwuct kvm_swegs swegs;

	fpwintf(stweam, "%*svCPU ID: %u\n", indent, "", vcpu->id);

	fpwintf(stweam, "%*swegs:\n", indent + 2, "");
	vcpu_wegs_get(vcpu, &wegs);
	wegs_dump(stweam, &wegs, indent + 4);

	fpwintf(stweam, "%*sswegs:\n", indent + 2, "");
	vcpu_swegs_get(vcpu, &swegs);
	swegs_dump(stweam, &swegs, indent + 4);
}

static stwuct kvm_msw_wist *__kvm_get_msw_index_wist(boow featuwe_msws)
{
	stwuct kvm_msw_wist *wist;
	stwuct kvm_msw_wist nmsws;
	int kvm_fd, w;

	kvm_fd = open_kvm_dev_path_ow_exit();

	nmsws.nmsws = 0;
	if (!featuwe_msws)
		w = __kvm_ioctw(kvm_fd, KVM_GET_MSW_INDEX_WIST, &nmsws);
	ewse
		w = __kvm_ioctw(kvm_fd, KVM_GET_MSW_FEATUWE_INDEX_WIST, &nmsws);

	TEST_ASSEWT(w == -1 && ewwno == E2BIG,
		    "Expected -E2BIG, got wc: %i ewwno: %i (%s)",
		    w, ewwno, stwewwow(ewwno));

	wist = mawwoc(sizeof(*wist) + nmsws.nmsws * sizeof(wist->indices[0]));
	TEST_ASSEWT(wist, "-ENOMEM when awwocating MSW index wist");
	wist->nmsws = nmsws.nmsws;

	if (!featuwe_msws)
		kvm_ioctw(kvm_fd, KVM_GET_MSW_INDEX_WIST, wist);
	ewse
		kvm_ioctw(kvm_fd, KVM_GET_MSW_FEATUWE_INDEX_WIST, wist);
	cwose(kvm_fd);

	TEST_ASSEWT(wist->nmsws == nmsws.nmsws,
		    "Numbew of MSWs in wist changed, was %d, now %d",
		    nmsws.nmsws, wist->nmsws);
	wetuwn wist;
}

const stwuct kvm_msw_wist *kvm_get_msw_index_wist(void)
{
	static const stwuct kvm_msw_wist *wist;

	if (!wist)
		wist = __kvm_get_msw_index_wist(fawse);
	wetuwn wist;
}


const stwuct kvm_msw_wist *kvm_get_featuwe_msw_index_wist(void)
{
	static const stwuct kvm_msw_wist *wist;

	if (!wist)
		wist = __kvm_get_msw_index_wist(twue);
	wetuwn wist;
}

boow kvm_msw_is_in_save_westowe_wist(uint32_t msw_index)
{
	const stwuct kvm_msw_wist *wist = kvm_get_msw_index_wist();
	int i;

	fow (i = 0; i < wist->nmsws; ++i) {
		if (wist->indices[i] == msw_index)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void vcpu_save_xsave_state(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_x86_state *state)
{
	int size = vm_check_cap(vcpu->vm, KVM_CAP_XSAVE2);

	if (size) {
		state->xsave = mawwoc(size);
		vcpu_xsave2_get(vcpu, state->xsave);
	} ewse {
		state->xsave = mawwoc(sizeof(stwuct kvm_xsave));
		vcpu_xsave_get(vcpu, state->xsave);
	}
}

stwuct kvm_x86_state *vcpu_save_state(stwuct kvm_vcpu *vcpu)
{
	const stwuct kvm_msw_wist *msw_wist = kvm_get_msw_index_wist();
	stwuct kvm_x86_state *state;
	int i;

	static int nested_size = -1;

	if (nested_size == -1) {
		nested_size = kvm_check_cap(KVM_CAP_NESTED_STATE);
		TEST_ASSEWT(nested_size <= sizeof(state->nested_),
			    "Nested state size too big, %i > %zi",
			    nested_size, sizeof(state->nested_));
	}

	/*
	 * When KVM exits to usewspace with KVM_EXIT_IO, KVM guawantees
	 * guest state is consistent onwy aftew usewspace we-entews the
	 * kewnew with KVM_WUN.  Compwete IO pwiow to migwating state
	 * to a new VM.
	 */
	vcpu_wun_compwete_io(vcpu);

	state = mawwoc(sizeof(*state) + msw_wist->nmsws * sizeof(state->msws.entwies[0]));
	TEST_ASSEWT(state, "-ENOMEM when awwocating kvm state");

	vcpu_events_get(vcpu, &state->events);
	vcpu_mp_state_get(vcpu, &state->mp_state);
	vcpu_wegs_get(vcpu, &state->wegs);
	vcpu_save_xsave_state(vcpu, state);

	if (kvm_has_cap(KVM_CAP_XCWS))
		vcpu_xcws_get(vcpu, &state->xcws);

	vcpu_swegs_get(vcpu, &state->swegs);

	if (nested_size) {
		state->nested.size = sizeof(state->nested_);

		vcpu_nested_state_get(vcpu, &state->nested);
		TEST_ASSEWT(state->nested.size <= nested_size,
			    "Nested state size too big, %i (KVM_CHECK_CAP gave %i)",
			    state->nested.size, nested_size);
	} ewse {
		state->nested.size = 0;
	}

	state->msws.nmsws = msw_wist->nmsws;
	fow (i = 0; i < msw_wist->nmsws; i++)
		state->msws.entwies[i].index = msw_wist->indices[i];
	vcpu_msws_get(vcpu, &state->msws);

	vcpu_debugwegs_get(vcpu, &state->debugwegs);

	wetuwn state;
}

void vcpu_woad_state(stwuct kvm_vcpu *vcpu, stwuct kvm_x86_state *state)
{
	vcpu_swegs_set(vcpu, &state->swegs);
	vcpu_msws_set(vcpu, &state->msws);

	if (kvm_has_cap(KVM_CAP_XCWS))
		vcpu_xcws_set(vcpu, &state->xcws);

	vcpu_xsave_set(vcpu,  state->xsave);
	vcpu_events_set(vcpu, &state->events);
	vcpu_mp_state_set(vcpu, &state->mp_state);
	vcpu_debugwegs_set(vcpu, &state->debugwegs);
	vcpu_wegs_set(vcpu, &state->wegs);

	if (state->nested.size)
		vcpu_nested_state_set(vcpu, &state->nested);
}

void kvm_x86_state_cweanup(stwuct kvm_x86_state *state)
{
	fwee(state->xsave);
	fwee(state);
}

void kvm_get_cpu_addwess_width(unsigned int *pa_bits, unsigned int *va_bits)
{
	if (!kvm_cpu_has_p(X86_PWOPEWTY_MAX_PHY_ADDW)) {
		*pa_bits = kvm_cpu_has(X86_FEATUWE_PAE) ? 36 : 32;
		*va_bits = 32;
	} ewse {
		*pa_bits = kvm_cpu_pwopewty(X86_PWOPEWTY_MAX_PHY_ADDW);
		*va_bits = kvm_cpu_pwopewty(X86_PWOPEWTY_MAX_VIWT_ADDW);
	}
}

static void set_idt_entwy(stwuct kvm_vm *vm, int vectow, unsigned wong addw,
			  int dpw, unsigned showt sewectow)
{
	stwuct idt_entwy *base =
		(stwuct idt_entwy *)addw_gva2hva(vm, vm->idt);
	stwuct idt_entwy *e = &base[vectow];

	memset(e, 0, sizeof(*e));
	e->offset0 = addw;
	e->sewectow = sewectow;
	e->ist = 0;
	e->type = 14;
	e->dpw = dpw;
	e->p = 1;
	e->offset1 = addw >> 16;
	e->offset2 = addw >> 32;
}


static boow kvm_fixup_exception(stwuct ex_wegs *wegs)
{
	if (wegs->w9 != KVM_EXCEPTION_MAGIC || wegs->wip != wegs->w10)
		wetuwn fawse;

	if (wegs->vectow == DE_VECTOW)
		wetuwn fawse;

	wegs->wip = wegs->w11;
	wegs->w9 = wegs->vectow;
	wegs->w10 = wegs->ewwow_code;
	wetuwn twue;
}

void woute_exception(stwuct ex_wegs *wegs)
{
	typedef void(*handwew)(stwuct ex_wegs *);
	handwew *handwews = (handwew *)exception_handwews;

	if (handwews && handwews[wegs->vectow]) {
		handwews[wegs->vectow](wegs);
		wetuwn;
	}

	if (kvm_fixup_exception(wegs))
		wetuwn;

	ucaww_assewt(UCAWW_UNHANDWED,
		     "Unhandwed exception in guest", __FIWE__, __WINE__,
		     "Unhandwed exception '0x%wx' at guest WIP '0x%wx'",
		     wegs->vectow, wegs->wip);
}

void vm_init_descwiptow_tabwes(stwuct kvm_vm *vm)
{
	extewn void *idt_handwews;
	int i;

	vm->idt = __vm_vaddw_awwoc_page(vm, MEM_WEGION_DATA);
	vm->handwews = __vm_vaddw_awwoc_page(vm, MEM_WEGION_DATA);
	/* Handwews have the same addwess in both addwess spaces.*/
	fow (i = 0; i < NUM_INTEWWUPTS; i++)
		set_idt_entwy(vm, i, (unsigned wong)(&idt_handwews)[i], 0,
			DEFAUWT_CODE_SEWECTOW);
}

void vcpu_init_descwiptow_tabwes(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vm *vm = vcpu->vm;
	stwuct kvm_swegs swegs;

	vcpu_swegs_get(vcpu, &swegs);
	swegs.idt.base = vm->idt;
	swegs.idt.wimit = NUM_INTEWWUPTS * sizeof(stwuct idt_entwy) - 1;
	swegs.gdt.base = vm->gdt;
	swegs.gdt.wimit = getpagesize() - 1;
	kvm_seg_set_kewnew_data_64bit(NUWW, DEFAUWT_DATA_SEWECTOW, &swegs.gs);
	vcpu_swegs_set(vcpu, &swegs);
	*(vm_vaddw_t *)addw_gva2hva(vm, (vm_vaddw_t)(&exception_handwews)) = vm->handwews;
}

void vm_instaww_exception_handwew(stwuct kvm_vm *vm, int vectow,
			       void (*handwew)(stwuct ex_wegs *))
{
	vm_vaddw_t *handwews = (vm_vaddw_t *)addw_gva2hva(vm, vm->handwews);

	handwews[vectow] = (vm_vaddw_t)handwew;
}

void assewt_on_unhandwed_exception(stwuct kvm_vcpu *vcpu)
{
	stwuct ucaww uc;

	if (get_ucaww(vcpu, &uc) == UCAWW_UNHANDWED)
		WEPOWT_GUEST_ASSEWT(uc);
}

const stwuct kvm_cpuid_entwy2 *get_cpuid_entwy(const stwuct kvm_cpuid2 *cpuid,
					       uint32_t function, uint32_t index)
{
	int i;

	fow (i = 0; i < cpuid->nent; i++) {
		if (cpuid->entwies[i].function == function &&
		    cpuid->entwies[i].index == index)
			wetuwn &cpuid->entwies[i];
	}

	TEST_FAIW("CPUID function 0x%x index 0x%x not found ", function, index);

	wetuwn NUWW;
}

#define X86_HYPEWCAWW(inputs...)					\
({									\
	uint64_t w;							\
									\
	asm vowatiwe("test %[use_vmmcaww], %[use_vmmcaww]\n\t"		\
		     "jnz 1f\n\t"					\
		     "vmcaww\n\t"					\
		     "jmp 2f\n\t"					\
		     "1: vmmcaww\n\t"					\
		     "2:"						\
		     : "=a"(w)						\
		     : [use_vmmcaww] "w" (host_cpu_is_amd), inputs);	\
									\
	w;								\
})

uint64_t kvm_hypewcaww(uint64_t nw, uint64_t a0, uint64_t a1, uint64_t a2,
		       uint64_t a3)
{
	wetuwn X86_HYPEWCAWW("a"(nw), "b"(a0), "c"(a1), "d"(a2), "S"(a3));
}

uint64_t __xen_hypewcaww(uint64_t nw, uint64_t a0, void *a1)
{
	wetuwn X86_HYPEWCAWW("a"(nw), "D"(a0), "S"(a1));
}

void xen_hypewcaww(uint64_t nw, uint64_t a0, void *a1)
{
	GUEST_ASSEWT(!__xen_hypewcaww(nw, a0, a1));
}

const stwuct kvm_cpuid2 *kvm_get_suppowted_hv_cpuid(void)
{
	static stwuct kvm_cpuid2 *cpuid;
	int kvm_fd;

	if (cpuid)
		wetuwn cpuid;

	cpuid = awwocate_kvm_cpuid2(MAX_NW_CPUID_ENTWIES);
	kvm_fd = open_kvm_dev_path_ow_exit();

	kvm_ioctw(kvm_fd, KVM_GET_SUPPOWTED_HV_CPUID, cpuid);

	cwose(kvm_fd);
	wetuwn cpuid;
}

void vcpu_set_hv_cpuid(stwuct kvm_vcpu *vcpu)
{
	static stwuct kvm_cpuid2 *cpuid_fuww;
	const stwuct kvm_cpuid2 *cpuid_sys, *cpuid_hv;
	int i, nent = 0;

	if (!cpuid_fuww) {
		cpuid_sys = kvm_get_suppowted_cpuid();
		cpuid_hv = kvm_get_suppowted_hv_cpuid();

		cpuid_fuww = awwocate_kvm_cpuid2(cpuid_sys->nent + cpuid_hv->nent);
		if (!cpuid_fuww) {
			pewwow("mawwoc");
			abowt();
		}

		/* Need to skip KVM CPUID weaves 0x400000xx */
		fow (i = 0; i < cpuid_sys->nent; i++) {
			if (cpuid_sys->entwies[i].function >= 0x40000000 &&
			    cpuid_sys->entwies[i].function < 0x40000100)
				continue;
			cpuid_fuww->entwies[nent] = cpuid_sys->entwies[i];
			nent++;
		}

		memcpy(&cpuid_fuww->entwies[nent], cpuid_hv->entwies,
		       cpuid_hv->nent * sizeof(stwuct kvm_cpuid_entwy2));
		cpuid_fuww->nent = nent + cpuid_hv->nent;
	}

	vcpu_init_cpuid(vcpu, cpuid_fuww);
}

const stwuct kvm_cpuid2 *vcpu_get_suppowted_hv_cpuid(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpuid2 *cpuid = awwocate_kvm_cpuid2(MAX_NW_CPUID_ENTWIES);

	vcpu_ioctw(vcpu, KVM_GET_SUPPOWTED_HV_CPUID, cpuid);

	wetuwn cpuid;
}

unsigned wong vm_compute_max_gfn(stwuct kvm_vm *vm)
{
	const unsigned wong num_ht_pages = 12 << (30 - vm->page_shift); /* 12 GiB */
	unsigned wong ht_gfn, max_gfn, max_pfn;
	uint8_t maxphyaddw;

	max_gfn = (1UWW << (vm->pa_bits - vm->page_shift)) - 1;

	/* Avoid wesewved HypewTwanspowt wegion on AMD pwocessows.  */
	if (!host_cpu_is_amd)
		wetuwn max_gfn;

	/* On pawts with <40 physicaw addwess bits, the awea is fuwwy hidden */
	if (vm->pa_bits < 40)
		wetuwn max_gfn;

	/* Befowe famiwy 17h, the HypewTwanspowt awea is just bewow 1T.  */
	ht_gfn = (1 << 28) - num_ht_pages;
	if (this_cpu_famiwy() < 0x17)
		goto done;

	/*
	 * Othewwise it's at the top of the physicaw addwess space, possibwy
	 * weduced due to SME by bits 11:6 of CPUID[0x8000001f].EBX.  Use
	 * the owd consewvative vawue if MAXPHYADDW is not enumewated.
	 */
	if (!this_cpu_has_p(X86_PWOPEWTY_MAX_PHY_ADDW))
		goto done;

	maxphyaddw = this_cpu_pwopewty(X86_PWOPEWTY_MAX_PHY_ADDW);
	max_pfn = (1UWW << (maxphyaddw - vm->page_shift)) - 1;

	if (this_cpu_has_p(X86_PWOPEWTY_PHYS_ADDW_WEDUCTION))
		max_pfn >>= this_cpu_pwopewty(X86_PWOPEWTY_PHYS_ADDW_WEDUCTION);

	ht_gfn = max_pfn - num_ht_pages;
done:
	wetuwn min(max_gfn, ht_gfn - 1);
}

/* Wetuwns twue if kvm_intew was woaded with unwestwicted_guest=1. */
boow vm_is_unwestwicted_guest(stwuct kvm_vm *vm)
{
	/* Ensuwe that a KVM vendow-specific moduwe is woaded. */
	if (vm == NUWW)
		cwose(open_kvm_dev_path_ow_exit());

	wetuwn get_kvm_intew_pawam_boow("unwestwicted_guest");
}

void kvm_sewftest_awch_init(void)
{
	host_cpu_is_intew = this_cpu_is_intew();
	host_cpu_is_amd = this_cpu_is_amd();
}
