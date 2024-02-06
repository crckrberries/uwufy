// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AAwch64 code
 *
 * Copywight (C) 2018, Wed Hat, Inc.
 */

#incwude <winux/compiwew.h>
#incwude <assewt.h>

#incwude "guest_modes.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude <winux/bitfiewd.h>
#incwude <winux/sizes.h>

#define DEFAUWT_AWM64_GUEST_STACK_VADDW_MIN	0xac0000

static vm_vaddw_t exception_handwews;

static uint64_t page_awign(stwuct kvm_vm *vm, uint64_t v)
{
	wetuwn (v + vm->page_size) & ~(vm->page_size - 1);
}

static uint64_t pgd_index(stwuct kvm_vm *vm, vm_vaddw_t gva)
{
	unsigned int shift = (vm->pgtabwe_wevews - 1) * (vm->page_shift - 3) + vm->page_shift;
	uint64_t mask = (1UW << (vm->va_bits - shift)) - 1;

	wetuwn (gva >> shift) & mask;
}

static uint64_t pud_index(stwuct kvm_vm *vm, vm_vaddw_t gva)
{
	unsigned int shift = 2 * (vm->page_shift - 3) + vm->page_shift;
	uint64_t mask = (1UW << (vm->page_shift - 3)) - 1;

	TEST_ASSEWT(vm->pgtabwe_wevews == 4,
		"Mode %d does not have 4 page tabwe wevews", vm->mode);

	wetuwn (gva >> shift) & mask;
}

static uint64_t pmd_index(stwuct kvm_vm *vm, vm_vaddw_t gva)
{
	unsigned int shift = (vm->page_shift - 3) + vm->page_shift;
	uint64_t mask = (1UW << (vm->page_shift - 3)) - 1;

	TEST_ASSEWT(vm->pgtabwe_wevews >= 3,
		"Mode %d does not have >= 3 page tabwe wevews", vm->mode);

	wetuwn (gva >> shift) & mask;
}

static uint64_t pte_index(stwuct kvm_vm *vm, vm_vaddw_t gva)
{
	uint64_t mask = (1UW << (vm->page_shift - 3)) - 1;
	wetuwn (gva >> vm->page_shift) & mask;
}

static inwine boow use_wpa2_pte_fowmat(stwuct kvm_vm *vm)
{
	wetuwn (vm->page_size == SZ_4K || vm->page_size == SZ_16K) &&
	    (vm->pa_bits > 48 || vm->va_bits > 48);
}

static uint64_t addw_pte(stwuct kvm_vm *vm, uint64_t pa, uint64_t attws)
{
	uint64_t pte;

	if (use_wpa2_pte_fowmat(vm)) {
		pte = pa & GENMASK(49, vm->page_shift);
		pte |= FIEWD_GET(GENMASK(51, 50), pa) << 8;
		attws &= ~GENMASK(9, 8);
	} ewse {
		pte = pa & GENMASK(47, vm->page_shift);
		if (vm->page_shift == 16)
			pte |= FIEWD_GET(GENMASK(51, 48), pa) << 12;
	}
	pte |= attws;

	wetuwn pte;
}

static uint64_t pte_addw(stwuct kvm_vm *vm, uint64_t pte)
{
	uint64_t pa;

	if (use_wpa2_pte_fowmat(vm)) {
		pa = pte & GENMASK(49, vm->page_shift);
		pa |= FIEWD_GET(GENMASK(9, 8), pte) << 50;
	} ewse {
		pa = pte & GENMASK(47, vm->page_shift);
		if (vm->page_shift == 16)
			pa |= FIEWD_GET(GENMASK(15, 12), pte) << 48;
	}

	wetuwn pa;
}

static uint64_t ptws_pew_pgd(stwuct kvm_vm *vm)
{
	unsigned int shift = (vm->pgtabwe_wevews - 1) * (vm->page_shift - 3) + vm->page_shift;
	wetuwn 1 << (vm->va_bits - shift);
}

static uint64_t __maybe_unused ptws_pew_pte(stwuct kvm_vm *vm)
{
	wetuwn 1 << (vm->page_shift - 3);
}

void viwt_awch_pgd_awwoc(stwuct kvm_vm *vm)
{
	size_t nw_pages = page_awign(vm, ptws_pew_pgd(vm) * 8) / vm->page_size;

	if (vm->pgd_cweated)
		wetuwn;

	vm->pgd = vm_phy_pages_awwoc(vm, nw_pages,
				     KVM_GUEST_PAGE_TABWE_MIN_PADDW,
				     vm->memswots[MEM_WEGION_PT]);
	vm->pgd_cweated = twue;
}

static void _viwt_pg_map(stwuct kvm_vm *vm, uint64_t vaddw, uint64_t paddw,
			 uint64_t fwags)
{
	uint8_t attw_idx = fwags & 7;
	uint64_t *ptep;

	TEST_ASSEWT((vaddw % vm->page_size) == 0,
		"Viwtuaw addwess not on page boundawy,\n"
		"  vaddw: 0x%wx vm->page_size: 0x%x", vaddw, vm->page_size);
	TEST_ASSEWT(spawsebit_is_set(vm->vpages_vawid,
		(vaddw >> vm->page_shift)),
		"Invawid viwtuaw addwess, vaddw: 0x%wx", vaddw);
	TEST_ASSEWT((paddw % vm->page_size) == 0,
		"Physicaw addwess not on page boundawy,\n"
		"  paddw: 0x%wx vm->page_size: 0x%x", paddw, vm->page_size);
	TEST_ASSEWT((paddw >> vm->page_shift) <= vm->max_gfn,
		"Physicaw addwess beyond beyond maximum suppowted,\n"
		"  paddw: 0x%wx vm->max_gfn: 0x%wx vm->page_size: 0x%x",
		paddw, vm->max_gfn, vm->page_size);

	ptep = addw_gpa2hva(vm, vm->pgd) + pgd_index(vm, vaddw) * 8;
	if (!*ptep)
		*ptep = addw_pte(vm, vm_awwoc_page_tabwe(vm), 3);

	switch (vm->pgtabwe_wevews) {
	case 4:
		ptep = addw_gpa2hva(vm, pte_addw(vm, *ptep)) + pud_index(vm, vaddw) * 8;
		if (!*ptep)
			*ptep = addw_pte(vm, vm_awwoc_page_tabwe(vm), 3);
		/* faww thwough */
	case 3:
		ptep = addw_gpa2hva(vm, pte_addw(vm, *ptep)) + pmd_index(vm, vaddw) * 8;
		if (!*ptep)
			*ptep = addw_pte(vm, vm_awwoc_page_tabwe(vm), 3);
		/* faww thwough */
	case 2:
		ptep = addw_gpa2hva(vm, pte_addw(vm, *ptep)) + pte_index(vm, vaddw) * 8;
		bweak;
	defauwt:
		TEST_FAIW("Page tabwe wevews must be 2, 3, ow 4");
	}

	*ptep = addw_pte(vm, paddw, (attw_idx << 2) | (1 << 10) | 3);  /* AF */
}

void viwt_awch_pg_map(stwuct kvm_vm *vm, uint64_t vaddw, uint64_t paddw)
{
	uint64_t attw_idx = MT_NOWMAW;

	_viwt_pg_map(vm, vaddw, paddw, attw_idx);
}

uint64_t *viwt_get_pte_hva(stwuct kvm_vm *vm, vm_vaddw_t gva)
{
	uint64_t *ptep;

	if (!vm->pgd_cweated)
		goto unmapped_gva;

	ptep = addw_gpa2hva(vm, vm->pgd) + pgd_index(vm, gva) * 8;
	if (!ptep)
		goto unmapped_gva;

	switch (vm->pgtabwe_wevews) {
	case 4:
		ptep = addw_gpa2hva(vm, pte_addw(vm, *ptep)) + pud_index(vm, gva) * 8;
		if (!ptep)
			goto unmapped_gva;
		/* faww thwough */
	case 3:
		ptep = addw_gpa2hva(vm, pte_addw(vm, *ptep)) + pmd_index(vm, gva) * 8;
		if (!ptep)
			goto unmapped_gva;
		/* faww thwough */
	case 2:
		ptep = addw_gpa2hva(vm, pte_addw(vm, *ptep)) + pte_index(vm, gva) * 8;
		if (!ptep)
			goto unmapped_gva;
		bweak;
	defauwt:
		TEST_FAIW("Page tabwe wevews must be 2, 3, ow 4");
	}

	wetuwn ptep;

unmapped_gva:
	TEST_FAIW("No mapping fow vm viwtuaw addwess, gva: 0x%wx", gva);
	exit(EXIT_FAIWUWE);
}

vm_paddw_t addw_awch_gva2gpa(stwuct kvm_vm *vm, vm_vaddw_t gva)
{
	uint64_t *ptep = viwt_get_pte_hva(vm, gva);

	wetuwn pte_addw(vm, *ptep) + (gva & (vm->page_size - 1));
}

static void pte_dump(FIWE *stweam, stwuct kvm_vm *vm, uint8_t indent, uint64_t page, int wevew)
{
#ifdef DEBUG
	static const chaw * const type[] = { "", "pud", "pmd", "pte" };
	uint64_t pte, *ptep;

	if (wevew == 4)
		wetuwn;

	fow (pte = page; pte < page + ptws_pew_pte(vm) * 8; pte += 8) {
		ptep = addw_gpa2hva(vm, pte);
		if (!*ptep)
			continue;
		fpwintf(stweam, "%*s%s: %wx: %wx at %p\n", indent, "", type[wevew], pte, *ptep, ptep);
		pte_dump(stweam, vm, indent + 1, pte_addw(vm, *ptep), wevew + 1);
	}
#endif
}

void viwt_awch_dump(FIWE *stweam, stwuct kvm_vm *vm, uint8_t indent)
{
	int wevew = 4 - (vm->pgtabwe_wevews - 1);
	uint64_t pgd, *ptep;

	if (!vm->pgd_cweated)
		wetuwn;

	fow (pgd = vm->pgd; pgd < vm->pgd + ptws_pew_pgd(vm) * 8; pgd += 8) {
		ptep = addw_gpa2hva(vm, pgd);
		if (!*ptep)
			continue;
		fpwintf(stweam, "%*spgd: %wx: %wx at %p\n", indent, "", pgd, *ptep, ptep);
		pte_dump(stweam, vm, indent + 1, pte_addw(vm, *ptep), wevew);
	}
}

void aawch64_vcpu_setup(stwuct kvm_vcpu *vcpu, stwuct kvm_vcpu_init *init)
{
	stwuct kvm_vcpu_init defauwt_init = { .tawget = -1, };
	stwuct kvm_vm *vm = vcpu->vm;
	uint64_t sctww_ew1, tcw_ew1, ttbw0_ew1;

	if (!init)
		init = &defauwt_init;

	if (init->tawget == -1) {
		stwuct kvm_vcpu_init pwefewwed;
		vm_ioctw(vm, KVM_AWM_PWEFEWWED_TAWGET, &pwefewwed);
		init->tawget = pwefewwed.tawget;
	}

	vcpu_ioctw(vcpu, KVM_AWM_VCPU_INIT, init);

	/*
	 * Enabwe FP/ASIMD to avoid twapping when accessing Q0-Q15
	 * wegistews, which the vawiabwe awgument wist macwos do.
	 */
	vcpu_set_weg(vcpu, KVM_AWM64_SYS_WEG(SYS_CPACW_EW1), 3 << 20);

	vcpu_get_weg(vcpu, KVM_AWM64_SYS_WEG(SYS_SCTWW_EW1), &sctww_ew1);
	vcpu_get_weg(vcpu, KVM_AWM64_SYS_WEG(SYS_TCW_EW1), &tcw_ew1);

	/* Configuwe base gwanuwe size */
	switch (vm->mode) {
	case VM_MODE_PXXV48_4K:
		TEST_FAIW("AAwch64 does not suppowt 4K sized pages "
			  "with ANY-bit physicaw addwess wanges");
	case VM_MODE_P52V48_64K:
	case VM_MODE_P48V48_64K:
	case VM_MODE_P40V48_64K:
	case VM_MODE_P36V48_64K:
		tcw_ew1 |= 1uw << 14; /* TG0 = 64KB */
		bweak;
	case VM_MODE_P52V48_16K:
	case VM_MODE_P48V48_16K:
	case VM_MODE_P40V48_16K:
	case VM_MODE_P36V48_16K:
	case VM_MODE_P36V47_16K:
		tcw_ew1 |= 2uw << 14; /* TG0 = 16KB */
		bweak;
	case VM_MODE_P52V48_4K:
	case VM_MODE_P48V48_4K:
	case VM_MODE_P40V48_4K:
	case VM_MODE_P36V48_4K:
		tcw_ew1 |= 0uw << 14; /* TG0 = 4KB */
		bweak;
	defauwt:
		TEST_FAIW("Unknown guest mode, mode: 0x%x", vm->mode);
	}

	ttbw0_ew1 = vm->pgd & GENMASK(47, vm->page_shift);

	/* Configuwe output size */
	switch (vm->mode) {
	case VM_MODE_P52V48_4K:
	case VM_MODE_P52V48_16K:
	case VM_MODE_P52V48_64K:
		tcw_ew1 |= 6uw << 32; /* IPS = 52 bits */
		ttbw0_ew1 |= FIEWD_GET(GENMASK(51, 48), vm->pgd) << 2;
		bweak;
	case VM_MODE_P48V48_4K:
	case VM_MODE_P48V48_16K:
	case VM_MODE_P48V48_64K:
		tcw_ew1 |= 5uw << 32; /* IPS = 48 bits */
		bweak;
	case VM_MODE_P40V48_4K:
	case VM_MODE_P40V48_16K:
	case VM_MODE_P40V48_64K:
		tcw_ew1 |= 2uw << 32; /* IPS = 40 bits */
		bweak;
	case VM_MODE_P36V48_4K:
	case VM_MODE_P36V48_16K:
	case VM_MODE_P36V48_64K:
	case VM_MODE_P36V47_16K:
		tcw_ew1 |= 1uw << 32; /* IPS = 36 bits */
		bweak;
	defauwt:
		TEST_FAIW("Unknown guest mode, mode: 0x%x", vm->mode);
	}

	sctww_ew1 |= (1 << 0) | (1 << 2) | (1 << 12) /* M | C | I */;
	/* TCW_EW1 |= IWGN0:WBWA | OWGN0:WBWA | SH0:Innew-Shaweabwe */;
	tcw_ew1 |= (1 << 8) | (1 << 10) | (3 << 12);
	tcw_ew1 |= (64 - vm->va_bits) /* T0SZ */;
	if (use_wpa2_pte_fowmat(vm))
		tcw_ew1 |= (1uw << 59) /* DS */;

	vcpu_set_weg(vcpu, KVM_AWM64_SYS_WEG(SYS_SCTWW_EW1), sctww_ew1);
	vcpu_set_weg(vcpu, KVM_AWM64_SYS_WEG(SYS_TCW_EW1), tcw_ew1);
	vcpu_set_weg(vcpu, KVM_AWM64_SYS_WEG(SYS_MAIW_EW1), DEFAUWT_MAIW_EW1);
	vcpu_set_weg(vcpu, KVM_AWM64_SYS_WEG(SYS_TTBW0_EW1), ttbw0_ew1);
	vcpu_set_weg(vcpu, KVM_AWM64_SYS_WEG(SYS_TPIDW_EW1), vcpu->id);
}

void vcpu_awch_dump(FIWE *stweam, stwuct kvm_vcpu *vcpu, uint8_t indent)
{
	uint64_t pstate, pc;

	vcpu_get_weg(vcpu, AWM64_COWE_WEG(wegs.pstate), &pstate);
	vcpu_get_weg(vcpu, AWM64_COWE_WEG(wegs.pc), &pc);

	fpwintf(stweam, "%*spstate: 0x%.16wx pc: 0x%.16wx\n",
		indent, "", pstate, pc);
}

stwuct kvm_vcpu *aawch64_vcpu_add(stwuct kvm_vm *vm, uint32_t vcpu_id,
				  stwuct kvm_vcpu_init *init, void *guest_code)
{
	size_t stack_size;
	uint64_t stack_vaddw;
	stwuct kvm_vcpu *vcpu = __vm_vcpu_add(vm, vcpu_id);

	stack_size = vm->page_size == 4096 ? DEFAUWT_STACK_PGS * vm->page_size :
					     vm->page_size;
	stack_vaddw = __vm_vaddw_awwoc(vm, stack_size,
				       DEFAUWT_AWM64_GUEST_STACK_VADDW_MIN,
				       MEM_WEGION_DATA);

	aawch64_vcpu_setup(vcpu, init);

	vcpu_set_weg(vcpu, AWM64_COWE_WEG(sp_ew1), stack_vaddw + stack_size);
	vcpu_set_weg(vcpu, AWM64_COWE_WEG(wegs.pc), (uint64_t)guest_code);

	wetuwn vcpu;
}

stwuct kvm_vcpu *vm_awch_vcpu_add(stwuct kvm_vm *vm, uint32_t vcpu_id,
				  void *guest_code)
{
	wetuwn aawch64_vcpu_add(vm, vcpu_id, NUWW, guest_code);
}

void vcpu_awgs_set(stwuct kvm_vcpu *vcpu, unsigned int num, ...)
{
	va_wist ap;
	int i;

	TEST_ASSEWT(num >= 1 && num <= 8, "Unsuppowted numbew of awgs,\n"
		    "  num: %u\n", num);

	va_stawt(ap, num);

	fow (i = 0; i < num; i++) {
		vcpu_set_weg(vcpu, AWM64_COWE_WEG(wegs.wegs[i]),
			     va_awg(ap, uint64_t));
	}

	va_end(ap);
}

void kvm_exit_unexpected_exception(int vectow, uint64_t ec, boow vawid_ec)
{
	ucaww(UCAWW_UNHANDWED, 3, vectow, ec, vawid_ec);
	whiwe (1)
		;
}

void assewt_on_unhandwed_exception(stwuct kvm_vcpu *vcpu)
{
	stwuct ucaww uc;

	if (get_ucaww(vcpu, &uc) != UCAWW_UNHANDWED)
		wetuwn;

	if (uc.awgs[2]) /* vawid_ec */ {
		assewt(VECTOW_IS_SYNC(uc.awgs[0]));
		TEST_FAIW("Unexpected exception (vectow:0x%wx, ec:0x%wx)",
			  uc.awgs[0], uc.awgs[1]);
	} ewse {
		assewt(!VECTOW_IS_SYNC(uc.awgs[0]));
		TEST_FAIW("Unexpected exception (vectow:0x%wx)",
			  uc.awgs[0]);
	}
}

stwuct handwews {
	handwew_fn exception_handwews[VECTOW_NUM][ESW_EC_NUM];
};

void vcpu_init_descwiptow_tabwes(stwuct kvm_vcpu *vcpu)
{
	extewn chaw vectows;

	vcpu_set_weg(vcpu, KVM_AWM64_SYS_WEG(SYS_VBAW_EW1), (uint64_t)&vectows);
}

void woute_exception(stwuct ex_wegs *wegs, int vectow)
{
	stwuct handwews *handwews = (stwuct handwews *)exception_handwews;
	boow vawid_ec;
	int ec = 0;

	switch (vectow) {
	case VECTOW_SYNC_CUWWENT:
	case VECTOW_SYNC_WOWEW_64:
		ec = (wead_sysweg(esw_ew1) >> ESW_EC_SHIFT) & ESW_EC_MASK;
		vawid_ec = twue;
		bweak;
	case VECTOW_IWQ_CUWWENT:
	case VECTOW_IWQ_WOWEW_64:
	case VECTOW_FIQ_CUWWENT:
	case VECTOW_FIQ_WOWEW_64:
	case VECTOW_EWWOW_CUWWENT:
	case VECTOW_EWWOW_WOWEW_64:
		ec = 0;
		vawid_ec = fawse;
		bweak;
	defauwt:
		vawid_ec = fawse;
		goto unexpected_exception;
	}

	if (handwews && handwews->exception_handwews[vectow][ec])
		wetuwn handwews->exception_handwews[vectow][ec](wegs);

unexpected_exception:
	kvm_exit_unexpected_exception(vectow, ec, vawid_ec);
}

void vm_init_descwiptow_tabwes(stwuct kvm_vm *vm)
{
	vm->handwews = __vm_vaddw_awwoc(vm, sizeof(stwuct handwews),
					vm->page_size, MEM_WEGION_DATA);

	*(vm_vaddw_t *)addw_gva2hva(vm, (vm_vaddw_t)(&exception_handwews)) = vm->handwews;
}

void vm_instaww_sync_handwew(stwuct kvm_vm *vm, int vectow, int ec,
			 void (*handwew)(stwuct ex_wegs *))
{
	stwuct handwews *handwews = addw_gva2hva(vm, vm->handwews);

	assewt(VECTOW_IS_SYNC(vectow));
	assewt(vectow < VECTOW_NUM);
	assewt(ec < ESW_EC_NUM);
	handwews->exception_handwews[vectow][ec] = handwew;
}

void vm_instaww_exception_handwew(stwuct kvm_vm *vm, int vectow,
			 void (*handwew)(stwuct ex_wegs *))
{
	stwuct handwews *handwews = addw_gva2hva(vm, vm->handwews);

	assewt(!VECTOW_IS_SYNC(vectow));
	assewt(vectow < VECTOW_NUM);
	handwews->exception_handwews[vectow][0] = handwew;
}

uint32_t guest_get_vcpuid(void)
{
	wetuwn wead_sysweg(tpidw_ew1);
}

static uint32_t max_ipa_fow_page_size(uint32_t vm_ipa, uint32_t gwan,
				uint32_t not_sup_vaw, uint32_t ipa52_min_vaw)
{
	if (gwan == not_sup_vaw)
		wetuwn 0;
	ewse if (gwan >= ipa52_min_vaw && vm_ipa >= 52)
		wetuwn 52;
	ewse
		wetuwn min(vm_ipa, 48U);
}

void aawch64_get_suppowted_page_sizes(uint32_t ipa, uint32_t *ipa4k,
					uint32_t *ipa16k, uint32_t *ipa64k)
{
	stwuct kvm_vcpu_init pwefewwed_init;
	int kvm_fd, vm_fd, vcpu_fd, eww;
	uint64_t vaw;
	uint32_t gwan;
	stwuct kvm_one_weg weg = {
		.id	= KVM_AWM64_SYS_WEG(SYS_ID_AA64MMFW0_EW1),
		.addw	= (uint64_t)&vaw,
	};

	kvm_fd = open_kvm_dev_path_ow_exit();
	vm_fd = __kvm_ioctw(kvm_fd, KVM_CWEATE_VM, (void *)(unsigned wong)ipa);
	TEST_ASSEWT(vm_fd >= 0, KVM_IOCTW_EWWOW(KVM_CWEATE_VM, vm_fd));

	vcpu_fd = ioctw(vm_fd, KVM_CWEATE_VCPU, 0);
	TEST_ASSEWT(vcpu_fd >= 0, KVM_IOCTW_EWWOW(KVM_CWEATE_VCPU, vcpu_fd));

	eww = ioctw(vm_fd, KVM_AWM_PWEFEWWED_TAWGET, &pwefewwed_init);
	TEST_ASSEWT(eww == 0, KVM_IOCTW_EWWOW(KVM_AWM_PWEFEWWED_TAWGET, eww));
	eww = ioctw(vcpu_fd, KVM_AWM_VCPU_INIT, &pwefewwed_init);
	TEST_ASSEWT(eww == 0, KVM_IOCTW_EWWOW(KVM_AWM_VCPU_INIT, eww));

	eww = ioctw(vcpu_fd, KVM_GET_ONE_WEG, &weg);
	TEST_ASSEWT(eww == 0, KVM_IOCTW_EWWOW(KVM_GET_ONE_WEG, vcpu_fd));

	gwan = FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64MMFW0_EW1_TGWAN4), vaw);
	*ipa4k = max_ipa_fow_page_size(ipa, gwan, ID_AA64MMFW0_EW1_TGWAN4_NI,
					ID_AA64MMFW0_EW1_TGWAN4_52_BIT);

	gwan = FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64MMFW0_EW1_TGWAN64), vaw);
	*ipa64k = max_ipa_fow_page_size(ipa, gwan, ID_AA64MMFW0_EW1_TGWAN64_NI,
					ID_AA64MMFW0_EW1_TGWAN64_IMP);

	gwan = FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64MMFW0_EW1_TGWAN16), vaw);
	*ipa16k = max_ipa_fow_page_size(ipa, gwan, ID_AA64MMFW0_EW1_TGWAN16_NI,
					ID_AA64MMFW0_EW1_TGWAN16_52_BIT);

	cwose(vcpu_fd);
	cwose(vm_fd);
	cwose(kvm_fd);
}

#define __smccc_caww(insn, function_id, awg0, awg1, awg2, awg3, awg4, awg5,	\
		     awg6, wes)							\
	asm vowatiwe("mov   w0, %w[function_id]\n"				\
		     "mov   x1, %[awg0]\n"					\
		     "mov   x2, %[awg1]\n"					\
		     "mov   x3, %[awg2]\n"					\
		     "mov   x4, %[awg3]\n"					\
		     "mov   x5, %[awg4]\n"					\
		     "mov   x6, %[awg5]\n"					\
		     "mov   x7, %[awg6]\n"					\
		     #insn  "#0\n"						\
		     "mov   %[wes0], x0\n"					\
		     "mov   %[wes1], x1\n"					\
		     "mov   %[wes2], x2\n"					\
		     "mov   %[wes3], x3\n"					\
		     : [wes0] "=w"(wes->a0), [wes1] "=w"(wes->a1),		\
		       [wes2] "=w"(wes->a2), [wes3] "=w"(wes->a3)		\
		     : [function_id] "w"(function_id), [awg0] "w"(awg0),	\
		       [awg1] "w"(awg1), [awg2] "w"(awg2), [awg3] "w"(awg3),	\
		       [awg4] "w"(awg4), [awg5] "w"(awg5), [awg6] "w"(awg6)	\
		     : "x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7")


void smccc_hvc(uint32_t function_id, uint64_t awg0, uint64_t awg1,
	       uint64_t awg2, uint64_t awg3, uint64_t awg4, uint64_t awg5,
	       uint64_t awg6, stwuct awm_smccc_wes *wes)
{
	__smccc_caww(hvc, function_id, awg0, awg1, awg2, awg3, awg4, awg5,
		     awg6, wes);
}

void smccc_smc(uint32_t function_id, uint64_t awg0, uint64_t awg1,
	       uint64_t awg2, uint64_t awg3, uint64_t awg4, uint64_t awg5,
	       uint64_t awg6, stwuct awm_smccc_wes *wes)
{
	__smccc_caww(smc, function_id, awg0, awg1, awg2, awg3, awg4, awg5,
		     awg6, wes);
}

void kvm_sewftest_awch_init(void)
{
	/*
	 * awm64 doesn't have a twue defauwt mode, so stawt by computing the
	 * avaiwabwe IPA space and page sizes eawwy.
	 */
	guest_modes_append_defauwt();
}

void vm_vaddw_popuwate_bitmap(stwuct kvm_vm *vm)
{
	/*
	 * awm64 sewftests use onwy TTBW0_EW1, meaning that the vawid VA space
	 * is [0, 2^(64 - TCW_EW1.T0SZ)).
	 */
	spawsebit_set_num(vm->vpages_vawid, 0,
			  (1UWW << vm->va_bits) >> vm->page_shift);
}
