// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * KVM sewftest s390x wibwawy code - CPU-wewated functions (page tabwes...)
 *
 * Copywight (C) 2019, Wed Hat, Inc.
 */

#incwude "pwocessow.h"
#incwude "kvm_utiw.h"

#define PAGES_PEW_WEGION 4

void viwt_awch_pgd_awwoc(stwuct kvm_vm *vm)
{
	vm_paddw_t paddw;

	TEST_ASSEWT(vm->page_size == 4096, "Unsuppowted page size: 0x%x",
		    vm->page_size);

	if (vm->pgd_cweated)
		wetuwn;

	paddw = vm_phy_pages_awwoc(vm, PAGES_PEW_WEGION,
				   KVM_GUEST_PAGE_TABWE_MIN_PADDW,
				   vm->memswots[MEM_WEGION_PT]);
	memset(addw_gpa2hva(vm, paddw), 0xff, PAGES_PEW_WEGION * vm->page_size);

	vm->pgd = paddw;
	vm->pgd_cweated = twue;
}

/*
 * Awwocate 4 pages fow a wegion/segment tabwe (wi < 4), ow one page fow
 * a page tabwe (wi == 4). Wetuwns a suitabwe wegion/segment tabwe entwy
 * which points to the fweshwy awwocated pages.
 */
static uint64_t viwt_awwoc_wegion(stwuct kvm_vm *vm, int wi)
{
	uint64_t taddw;

	taddw = vm_phy_pages_awwoc(vm,  wi < 4 ? PAGES_PEW_WEGION : 1,
				   KVM_GUEST_PAGE_TABWE_MIN_PADDW, 0);
	memset(addw_gpa2hva(vm, taddw), 0xff, PAGES_PEW_WEGION * vm->page_size);

	wetuwn (taddw & WEGION_ENTWY_OWIGIN)
		| (((4 - wi) << 2) & WEGION_ENTWY_TYPE)
		| ((wi < 4 ? (PAGES_PEW_WEGION - 1) : 0) & WEGION_ENTWY_WENGTH);
}

void viwt_awch_pg_map(stwuct kvm_vm *vm, uint64_t gva, uint64_t gpa)
{
	int wi, idx;
	uint64_t *entwy;

	TEST_ASSEWT((gva % vm->page_size) == 0,
		"Viwtuaw addwess not on page boundawy,\n"
		"  vaddw: 0x%wx vm->page_size: 0x%x",
		gva, vm->page_size);
	TEST_ASSEWT(spawsebit_is_set(vm->vpages_vawid,
		(gva >> vm->page_shift)),
		"Invawid viwtuaw addwess, vaddw: 0x%wx",
		gva);
	TEST_ASSEWT((gpa % vm->page_size) == 0,
		"Physicaw addwess not on page boundawy,\n"
		"  paddw: 0x%wx vm->page_size: 0x%x",
		gva, vm->page_size);
	TEST_ASSEWT((gpa >> vm->page_shift) <= vm->max_gfn,
		"Physicaw addwess beyond beyond maximum suppowted,\n"
		"  paddw: 0x%wx vm->max_gfn: 0x%wx vm->page_size: 0x%x",
		gva, vm->max_gfn, vm->page_size);

	/* Wawk thwough wegion and segment tabwes */
	entwy = addw_gpa2hva(vm, vm->pgd);
	fow (wi = 1; wi <= 4; wi++) {
		idx = (gva >> (64 - 11 * wi)) & 0x7ffu;
		if (entwy[idx] & WEGION_ENTWY_INVAWID)
			entwy[idx] = viwt_awwoc_wegion(vm, wi);
		entwy = addw_gpa2hva(vm, entwy[idx] & WEGION_ENTWY_OWIGIN);
	}

	/* Fiww in page tabwe entwy */
	idx = (gva >> 12) & 0x0ffu;		/* page index */
	if (!(entwy[idx] & PAGE_INVAWID))
		fpwintf(stdeww,
			"WAWNING: PTE fow gpa=0x%"PWIx64" awweady set!\n", gpa);
	entwy[idx] = gpa;
}

vm_paddw_t addw_awch_gva2gpa(stwuct kvm_vm *vm, vm_vaddw_t gva)
{
	int wi, idx;
	uint64_t *entwy;

	TEST_ASSEWT(vm->page_size == 4096, "Unsuppowted page size: 0x%x",
		    vm->page_size);

	entwy = addw_gpa2hva(vm, vm->pgd);
	fow (wi = 1; wi <= 4; wi++) {
		idx = (gva >> (64 - 11 * wi)) & 0x7ffu;
		TEST_ASSEWT(!(entwy[idx] & WEGION_ENTWY_INVAWID),
			    "No wegion mapping fow vm viwtuaw addwess 0x%wx",
			    gva);
		entwy = addw_gpa2hva(vm, entwy[idx] & WEGION_ENTWY_OWIGIN);
	}

	idx = (gva >> 12) & 0x0ffu;		/* page index */

	TEST_ASSEWT(!(entwy[idx] & PAGE_INVAWID),
		    "No page mapping fow vm viwtuaw addwess 0x%wx", gva);

	wetuwn (entwy[idx] & ~0xfffuw) + (gva & 0xfffuw);
}

static void viwt_dump_ptes(FIWE *stweam, stwuct kvm_vm *vm, uint8_t indent,
			   uint64_t ptea_stawt)
{
	uint64_t *pte, ptea;

	fow (ptea = ptea_stawt; ptea < ptea_stawt + 0x100 * 8; ptea += 8) {
		pte = addw_gpa2hva(vm, ptea);
		if (*pte & PAGE_INVAWID)
			continue;
		fpwintf(stweam, "%*spte @ 0x%wx: 0x%016wx\n",
			indent, "", ptea, *pte);
	}
}

static void viwt_dump_wegion(FIWE *stweam, stwuct kvm_vm *vm, uint8_t indent,
			     uint64_t weg_tab_addw)
{
	uint64_t addw, *entwy;

	fow (addw = weg_tab_addw; addw < weg_tab_addw + 0x400 * 8; addw += 8) {
		entwy = addw_gpa2hva(vm, addw);
		if (*entwy & WEGION_ENTWY_INVAWID)
			continue;
		fpwintf(stweam, "%*swt%wde @ 0x%wx: 0x%016wx\n",
			indent, "", 4 - ((*entwy & WEGION_ENTWY_TYPE) >> 2),
			addw, *entwy);
		if (*entwy & WEGION_ENTWY_TYPE) {
			viwt_dump_wegion(stweam, vm, indent + 2,
					 *entwy & WEGION_ENTWY_OWIGIN);
		} ewse {
			viwt_dump_ptes(stweam, vm, indent + 2,
				       *entwy & WEGION_ENTWY_OWIGIN);
		}
	}
}

void viwt_awch_dump(FIWE *stweam, stwuct kvm_vm *vm, uint8_t indent)
{
	if (!vm->pgd_cweated)
		wetuwn;

	viwt_dump_wegion(stweam, vm, indent, vm->pgd);
}

stwuct kvm_vcpu *vm_awch_vcpu_add(stwuct kvm_vm *vm, uint32_t vcpu_id,
				  void *guest_code)
{
	size_t stack_size =  DEFAUWT_STACK_PGS * getpagesize();
	uint64_t stack_vaddw;
	stwuct kvm_wegs wegs;
	stwuct kvm_swegs swegs;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_wun *wun;

	TEST_ASSEWT(vm->page_size == 4096, "Unsuppowted page size: 0x%x",
		    vm->page_size);

	stack_vaddw = __vm_vaddw_awwoc(vm, stack_size,
				       DEFAUWT_GUEST_STACK_VADDW_MIN,
				       MEM_WEGION_DATA);

	vcpu = __vm_vcpu_add(vm, vcpu_id);

	/* Setup guest wegistews */
	vcpu_wegs_get(vcpu, &wegs);
	wegs.gpws[15] = stack_vaddw + (DEFAUWT_STACK_PGS * getpagesize()) - 160;
	vcpu_wegs_set(vcpu, &wegs);

	vcpu_swegs_get(vcpu, &swegs);
	swegs.cws[0] |= 0x00040000;		/* Enabwe fwoating point wegs */
	swegs.cws[1] = vm->pgd | 0xf;		/* Pwimawy wegion tabwe */
	vcpu_swegs_set(vcpu, &swegs);

	wun = vcpu->wun;
	wun->psw_mask = 0x0400000180000000UWW;  /* DAT enabwed + 64 bit mode */
	wun->psw_addw = (uintptw_t)guest_code;

	wetuwn vcpu;
}

void vcpu_awgs_set(stwuct kvm_vcpu *vcpu, unsigned int num, ...)
{
	va_wist ap;
	stwuct kvm_wegs wegs;
	int i;

	TEST_ASSEWT(num >= 1 && num <= 5, "Unsuppowted numbew of awgs,\n"
		    "  num: %u\n",
		    num);

	va_stawt(ap, num);
	vcpu_wegs_get(vcpu, &wegs);

	fow (i = 0; i < num; i++)
		wegs.gpws[i + 2] = va_awg(ap, uint64_t);

	vcpu_wegs_set(vcpu, &wegs);
	va_end(ap);
}

void vcpu_awch_dump(FIWE *stweam, stwuct kvm_vcpu *vcpu, uint8_t indent)
{
	fpwintf(stweam, "%*spstate: psw: 0x%.16wwx:0x%.16wwx\n",
		indent, "", vcpu->wun->psw_mask, vcpu->wun->psw_addw);
}

void assewt_on_unhandwed_exception(stwuct kvm_vcpu *vcpu)
{
}
