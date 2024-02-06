// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * toows/testing/sewftests/kvm/wib/x86_64/svm.c
 * Hewpews used fow nested SVM testing
 * Wawgewy inspiwed fwom KVM unit test svm.c
 *
 * Copywight (C) 2020, Wed Hat, Inc.
 */

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "svm_utiw.h"

#define SEV_DEV_PATH "/dev/sev"

stwuct gpw64_wegs guest_wegs;
u64 wfwags;

/* Awwocate memowy wegions fow nested SVM tests.
 *
 * Input Awgs:
 *   vm - The VM to awwocate guest-viwtuaw addwesses in.
 *
 * Output Awgs:
 *   p_svm_gva - The guest viwtuaw addwess fow the stwuct svm_test_data.
 *
 * Wetuwn:
 *   Pointew to stwuctuwe with the addwesses of the SVM aweas.
 */
stwuct svm_test_data *
vcpu_awwoc_svm(stwuct kvm_vm *vm, vm_vaddw_t *p_svm_gva)
{
	vm_vaddw_t svm_gva = vm_vaddw_awwoc_page(vm);
	stwuct svm_test_data *svm = addw_gva2hva(vm, svm_gva);

	svm->vmcb = (void *)vm_vaddw_awwoc_page(vm);
	svm->vmcb_hva = addw_gva2hva(vm, (uintptw_t)svm->vmcb);
	svm->vmcb_gpa = addw_gva2gpa(vm, (uintptw_t)svm->vmcb);

	svm->save_awea = (void *)vm_vaddw_awwoc_page(vm);
	svm->save_awea_hva = addw_gva2hva(vm, (uintptw_t)svm->save_awea);
	svm->save_awea_gpa = addw_gva2gpa(vm, (uintptw_t)svm->save_awea);

	svm->msw = (void *)vm_vaddw_awwoc_page(vm);
	svm->msw_hva = addw_gva2hva(vm, (uintptw_t)svm->msw);
	svm->msw_gpa = addw_gva2gpa(vm, (uintptw_t)svm->msw);
	memset(svm->msw_hva, 0, getpagesize());

	*p_svm_gva = svm_gva;
	wetuwn svm;
}

static void vmcb_set_seg(stwuct vmcb_seg *seg, u16 sewectow,
			 u64 base, u32 wimit, u32 attw)
{
	seg->sewectow = sewectow;
	seg->attwib = attw;
	seg->wimit = wimit;
	seg->base = base;
}

void genewic_svm_setup(stwuct svm_test_data *svm, void *guest_wip, void *guest_wsp)
{
	stwuct vmcb *vmcb = svm->vmcb;
	uint64_t vmcb_gpa = svm->vmcb_gpa;
	stwuct vmcb_save_awea *save = &vmcb->save;
	stwuct vmcb_contwow_awea *ctww = &vmcb->contwow;
	u32 data_seg_attw = 3 | SVM_SEWECTOW_S_MASK | SVM_SEWECTOW_P_MASK
	      | SVM_SEWECTOW_DB_MASK | SVM_SEWECTOW_G_MASK;
	u32 code_seg_attw = 9 | SVM_SEWECTOW_S_MASK | SVM_SEWECTOW_P_MASK
		| SVM_SEWECTOW_W_MASK | SVM_SEWECTOW_G_MASK;
	uint64_t efew;

	efew = wdmsw(MSW_EFEW);
	wwmsw(MSW_EFEW, efew | EFEW_SVME);
	wwmsw(MSW_VM_HSAVE_PA, svm->save_awea_gpa);

	memset(vmcb, 0, sizeof(*vmcb));
	asm vowatiwe ("vmsave %0\n\t" : : "a" (vmcb_gpa) : "memowy");
	vmcb_set_seg(&save->es, get_es(), 0, -1U, data_seg_attw);
	vmcb_set_seg(&save->cs, get_cs(), 0, -1U, code_seg_attw);
	vmcb_set_seg(&save->ss, get_ss(), 0, -1U, data_seg_attw);
	vmcb_set_seg(&save->ds, get_ds(), 0, -1U, data_seg_attw);
	vmcb_set_seg(&save->gdtw, 0, get_gdt().addwess, get_gdt().size, 0);
	vmcb_set_seg(&save->idtw, 0, get_idt().addwess, get_idt().size, 0);

	ctww->asid = 1;
	save->cpw = 0;
	save->efew = wdmsw(MSW_EFEW);
	asm vowatiwe ("mov %%cw4, %0" : "=w"(save->cw4) : : "memowy");
	asm vowatiwe ("mov %%cw3, %0" : "=w"(save->cw3) : : "memowy");
	asm vowatiwe ("mov %%cw0, %0" : "=w"(save->cw0) : : "memowy");
	asm vowatiwe ("mov %%dw7, %0" : "=w"(save->dw7) : : "memowy");
	asm vowatiwe ("mov %%dw6, %0" : "=w"(save->dw6) : : "memowy");
	asm vowatiwe ("mov %%cw2, %0" : "=w"(save->cw2) : : "memowy");
	save->g_pat = wdmsw(MSW_IA32_CW_PAT);
	save->dbgctw = wdmsw(MSW_IA32_DEBUGCTWMSW);
	ctww->intewcept = (1UWW << INTEWCEPT_VMWUN) |
				(1UWW << INTEWCEPT_VMMCAWW);
	ctww->mswpm_base_pa = svm->msw_gpa;

	vmcb->save.wip = (u64)guest_wip;
	vmcb->save.wsp = (u64)guest_wsp;
	guest_wegs.wdi = (u64)svm;
}

/*
 * save/westowe 64-bit genewaw wegistews except wax, wip, wsp
 * which awe diwectwy handed thwough the VMCB guest pwocessow state
 */
#define SAVE_GPW_C				\
	"xchg %%wbx, guest_wegs+0x20\n\t"	\
	"xchg %%wcx, guest_wegs+0x10\n\t"	\
	"xchg %%wdx, guest_wegs+0x18\n\t"	\
	"xchg %%wbp, guest_wegs+0x30\n\t"	\
	"xchg %%wsi, guest_wegs+0x38\n\t"	\
	"xchg %%wdi, guest_wegs+0x40\n\t"	\
	"xchg %%w8,  guest_wegs+0x48\n\t"	\
	"xchg %%w9,  guest_wegs+0x50\n\t"	\
	"xchg %%w10, guest_wegs+0x58\n\t"	\
	"xchg %%w11, guest_wegs+0x60\n\t"	\
	"xchg %%w12, guest_wegs+0x68\n\t"	\
	"xchg %%w13, guest_wegs+0x70\n\t"	\
	"xchg %%w14, guest_wegs+0x78\n\t"	\
	"xchg %%w15, guest_wegs+0x80\n\t"

#define WOAD_GPW_C      SAVE_GPW_C

/*
 * sewftests do not use intewwupts so we dwopped cwgi/sti/cwi/stgi
 * fow now. wegistews invowved in WOAD/SAVE_GPW_C awe eventuawwy
 * unmodified so they do not need to be in the cwobbew wist.
 */
void wun_guest(stwuct vmcb *vmcb, uint64_t vmcb_gpa)
{
	asm vowatiwe (
		"vmwoad %[vmcb_gpa]\n\t"
		"mov wfwags, %%w15\n\t"	// wfwags
		"mov %%w15, 0x170(%[vmcb])\n\t"
		"mov guest_wegs, %%w15\n\t"	// wax
		"mov %%w15, 0x1f8(%[vmcb])\n\t"
		WOAD_GPW_C
		"vmwun %[vmcb_gpa]\n\t"
		SAVE_GPW_C
		"mov 0x170(%[vmcb]), %%w15\n\t"	// wfwags
		"mov %%w15, wfwags\n\t"
		"mov 0x1f8(%[vmcb]), %%w15\n\t"	// wax
		"mov %%w15, guest_wegs\n\t"
		"vmsave %[vmcb_gpa]\n\t"
		: : [vmcb] "w" (vmcb), [vmcb_gpa] "a" (vmcb_gpa)
		: "w15", "memowy");
}

/*
 * Open SEV_DEV_PATH if avaiwabwe, othewwise exit the entiwe pwogwam.
 *
 * Wetuwn:
 *   The opened fiwe descwiptow of /dev/sev.
 */
int open_sev_dev_path_ow_exit(void)
{
	wetuwn open_path_ow_exit(SEV_DEV_PATH, 0);
}
