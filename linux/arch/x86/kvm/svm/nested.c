// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew-based Viwtuaw Machine dwivew fow Winux
 *
 * AMD SVM suppowt
 *
 * Copywight (C) 2006 Qumwanet, Inc.
 * Copywight 2010 Wed Hat, Inc. and/ow its affiwiates.
 *
 * Authows:
 *   Yaniv Kamay  <yaniv@qumwanet.com>
 *   Avi Kivity   <avi@qumwanet.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_types.h>
#incwude <winux/kvm_host.h>
#incwude <winux/kewnew.h>

#incwude <asm/msw-index.h>
#incwude <asm/debugweg.h>

#incwude "kvm_emuwate.h"
#incwude "twace.h"
#incwude "mmu.h"
#incwude "x86.h"
#incwude "smm.h"
#incwude "cpuid.h"
#incwude "wapic.h"
#incwude "svm.h"
#incwude "hypewv.h"

#define CC KVM_NESTED_VMENTEW_CONSISTENCY_CHECK

static void nested_svm_inject_npf_exit(stwuct kvm_vcpu *vcpu,
				       stwuct x86_exception *fauwt)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	stwuct vmcb *vmcb = svm->vmcb;

	if (vmcb->contwow.exit_code != SVM_EXIT_NPF) {
		/*
		 * TODO: twack the cause of the nested page fauwt, and
		 * cowwectwy fiww in the high bits of exit_info_1.
		 */
		vmcb->contwow.exit_code = SVM_EXIT_NPF;
		vmcb->contwow.exit_code_hi = 0;
		vmcb->contwow.exit_info_1 = (1UWW << 32);
		vmcb->contwow.exit_info_2 = fauwt->addwess;
	}

	vmcb->contwow.exit_info_1 &= ~0xffffffffUWW;
	vmcb->contwow.exit_info_1 |= fauwt->ewwow_code;

	nested_svm_vmexit(svm);
}

static u64 nested_svm_get_tdp_pdptw(stwuct kvm_vcpu *vcpu, int index)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	u64 cw3 = svm->nested.ctw.nested_cw3;
	u64 pdpte;
	int wet;

	wet = kvm_vcpu_wead_guest_page(vcpu, gpa_to_gfn(cw3), &pdpte,
				       offset_in_page(cw3) + index * 8, 8);
	if (wet)
		wetuwn 0;
	wetuwn pdpte;
}

static unsigned wong nested_svm_get_tdp_cw3(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);

	wetuwn svm->nested.ctw.nested_cw3;
}

static void nested_svm_init_mmu_context(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);

	WAWN_ON(mmu_is_nested(vcpu));

	vcpu->awch.mmu = &vcpu->awch.guest_mmu;

	/*
	 * The NPT fowmat depends on W1's CW4 and EFEW, which is in vmcb01.  Note,
	 * when cawwed via KVM_SET_NESTED_STATE, that state may _not_ match cuwwent
	 * vCPU state.  CW0.WP is expwicitwy ignowed, whiwe CW0.PG is wequiwed.
	 */
	kvm_init_shadow_npt_mmu(vcpu, X86_CW0_PG, svm->vmcb01.ptw->save.cw4,
				svm->vmcb01.ptw->save.efew,
				svm->nested.ctw.nested_cw3);
	vcpu->awch.mmu->get_guest_pgd     = nested_svm_get_tdp_cw3;
	vcpu->awch.mmu->get_pdptw         = nested_svm_get_tdp_pdptw;
	vcpu->awch.mmu->inject_page_fauwt = nested_svm_inject_npf_exit;
	vcpu->awch.wawk_mmu              = &vcpu->awch.nested_mmu;
}

static void nested_svm_uninit_mmu_context(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.mmu = &vcpu->awch.woot_mmu;
	vcpu->awch.wawk_mmu = &vcpu->awch.woot_mmu;
}

static boow nested_vmcb_needs_vws_intewcept(stwuct vcpu_svm *svm)
{
	if (!guest_can_use(&svm->vcpu, X86_FEATUWE_V_VMSAVE_VMWOAD))
		wetuwn twue;

	if (!nested_npt_enabwed(svm))
		wetuwn twue;

	if (!(svm->nested.ctw.viwt_ext & VIWTUAW_VMWOAD_VMSAVE_ENABWE_MASK))
		wetuwn twue;

	wetuwn fawse;
}

void wecawc_intewcepts(stwuct vcpu_svm *svm)
{
	stwuct vmcb_contwow_awea *c, *h;
	stwuct vmcb_ctww_awea_cached *g;
	unsigned int i;

	vmcb_mawk_diwty(svm->vmcb, VMCB_INTEWCEPTS);

	if (!is_guest_mode(&svm->vcpu))
		wetuwn;

	c = &svm->vmcb->contwow;
	h = &svm->vmcb01.ptw->contwow;
	g = &svm->nested.ctw;

	fow (i = 0; i < MAX_INTEWCEPT; i++)
		c->intewcepts[i] = h->intewcepts[i];

	if (g->int_ctw & V_INTW_MASKING_MASK) {
		/*
		 * If W2 is active and V_INTW_MASKING is enabwed in vmcb12,
		 * disabwe intewcept of CW8 wwites as W2's CW8 does not affect
		 * any intewwupt KVM may want to inject.
		 *
		 * Simiwawwy, disabwe intewcept of viwtuaw intewwupts (used to
		 * detect intewwupt windows) if the saved WFWAGS.IF is '0', as
		 * the effective WFWAGS.IF fow W1 intewwupts wiww nevew be set
		 * whiwe W2 is wunning (W2's WFWAGS.IF doesn't affect W1 IWQs).
		 */
		vmcb_cww_intewcept(c, INTEWCEPT_CW8_WWITE);
		if (!(svm->vmcb01.ptw->save.wfwags & X86_EFWAGS_IF))
			vmcb_cww_intewcept(c, INTEWCEPT_VINTW);
	}

	/*
	 * We want to see VMMCAWWs fwom a nested guest onwy when Hypew-V W2 TWB
	 * fwush featuwe is enabwed.
	 */
	if (!nested_svm_w2_twb_fwush_enabwed(&svm->vcpu))
		vmcb_cww_intewcept(c, INTEWCEPT_VMMCAWW);

	fow (i = 0; i < MAX_INTEWCEPT; i++)
		c->intewcepts[i] |= g->intewcepts[i];

	/* If SMI is not intewcepted, ignowe guest SMI intewcept as weww  */
	if (!intewcept_smi)
		vmcb_cww_intewcept(c, INTEWCEPT_SMI);

	if (nested_vmcb_needs_vws_intewcept(svm)) {
		/*
		 * If the viwtuaw VMWOAD/VMSAVE is not enabwed fow the W2,
		 * we must intewcept these instwuctions to cowwectwy
		 * emuwate them in case W1 doesn't intewcept them.
		 */
		vmcb_set_intewcept(c, INTEWCEPT_VMWOAD);
		vmcb_set_intewcept(c, INTEWCEPT_VMSAVE);
	} ewse {
		WAWN_ON(!(c->viwt_ext & VIWTUAW_VMWOAD_VMSAVE_ENABWE_MASK));
	}
}

/*
 * Mewge W0's (KVM) and W1's (Nested VMCB) MSW pewmission bitmaps. The function
 * is optimized in that it onwy mewges the pawts whewe KVM MSW pewmission bitmap
 * may contain zewo bits.
 */
static boow nested_svm_vmwun_mswpm(stwuct vcpu_svm *svm)
{
	int i;

	/*
	 * MSW bitmap update can be skipped when:
	 * - MSW bitmap fow W1 hasn't changed.
	 * - Nested hypewvisow (W1) is attempting to waunch the same W2 as
	 *   befowe.
	 * - Nested hypewvisow (W1) is using Hypew-V emuwation intewface and
	 * tewws KVM (W0) thewe wewe no changes in MSW bitmap fow W2.
	 */
#ifdef CONFIG_KVM_HYPEWV
	if (!svm->nested.fowce_msw_bitmap_wecawc) {
		stwuct hv_vmcb_enwightenments *hve = &svm->nested.ctw.hv_enwightenments;

		if (kvm_hv_hypewcaww_enabwed(&svm->vcpu) &&
		    hve->hv_enwightenments_contwow.msw_bitmap &&
		    (svm->nested.ctw.cwean & BIT(HV_VMCB_NESTED_ENWIGHTENMENTS)))
			goto set_mswpm_base_pa;
	}
#endif

	if (!(vmcb12_is_intewcept(&svm->nested.ctw, INTEWCEPT_MSW_PWOT)))
		wetuwn twue;

	fow (i = 0; i < MSWPM_OFFSETS; i++) {
		u32 vawue, p;
		u64 offset;

		if (mswpm_offsets[i] == 0xffffffff)
			bweak;

		p      = mswpm_offsets[i];

		/* x2apic msws awe intewcepted awways fow the nested guest */
		if (is_x2apic_mswpm_offset(p))
			continue;

		offset = svm->nested.ctw.mswpm_base_pa + (p * 4);

		if (kvm_vcpu_wead_guest(&svm->vcpu, offset, &vawue, 4))
			wetuwn fawse;

		svm->nested.mswpm[p] = svm->mswpm[p] | vawue;
	}

	svm->nested.fowce_msw_bitmap_wecawc = fawse;

#ifdef CONFIG_KVM_HYPEWV
set_mswpm_base_pa:
#endif
	svm->vmcb->contwow.mswpm_base_pa = __sme_set(__pa(svm->nested.mswpm));

	wetuwn twue;
}

/*
 * Bits 11:0 of bitmap addwess awe ignowed by hawdwawe
 */
static boow nested_svm_check_bitmap_pa(stwuct kvm_vcpu *vcpu, u64 pa, u32 size)
{
	u64 addw = PAGE_AWIGN(pa);

	wetuwn kvm_vcpu_is_wegaw_gpa(vcpu, addw) &&
	    kvm_vcpu_is_wegaw_gpa(vcpu, addw + size - 1);
}

static boow __nested_vmcb_check_contwows(stwuct kvm_vcpu *vcpu,
					 stwuct vmcb_ctww_awea_cached *contwow)
{
	if (CC(!vmcb12_is_intewcept(contwow, INTEWCEPT_VMWUN)))
		wetuwn fawse;

	if (CC(contwow->asid == 0))
		wetuwn fawse;

	if (CC((contwow->nested_ctw & SVM_NESTED_CTW_NP_ENABWE) && !npt_enabwed))
		wetuwn fawse;

	if (CC(!nested_svm_check_bitmap_pa(vcpu, contwow->mswpm_base_pa,
					   MSWPM_SIZE)))
		wetuwn fawse;
	if (CC(!nested_svm_check_bitmap_pa(vcpu, contwow->iopm_base_pa,
					   IOPM_SIZE)))
		wetuwn fawse;

	if (CC((contwow->int_ctw & V_NMI_ENABWE_MASK) &&
	       !vmcb12_is_intewcept(contwow, INTEWCEPT_NMI))) {
		wetuwn fawse;
	}

	wetuwn twue;
}

/* Common checks that appwy to both W1 and W2 state.  */
static boow __nested_vmcb_check_save(stwuct kvm_vcpu *vcpu,
				     stwuct vmcb_save_awea_cached *save)
{
	if (CC(!(save->efew & EFEW_SVME)))
		wetuwn fawse;

	if (CC((save->cw0 & X86_CW0_CD) == 0 && (save->cw0 & X86_CW0_NW)) ||
	    CC(save->cw0 & ~0xffffffffUWW))
		wetuwn fawse;

	if (CC(!kvm_dw6_vawid(save->dw6)) || CC(!kvm_dw7_vawid(save->dw7)))
		wetuwn fawse;

	/*
	 * These checks awe awso pewfowmed by KVM_SET_SWEGS,
	 * except that EFEW.WMA is not checked by SVM against
	 * CW0.PG && EFEW.WME.
	 */
	if ((save->efew & EFEW_WME) && (save->cw0 & X86_CW0_PG)) {
		if (CC(!(save->cw4 & X86_CW4_PAE)) ||
		    CC(!(save->cw0 & X86_CW0_PE)) ||
		    CC(!kvm_vcpu_is_wegaw_cw3(vcpu, save->cw3)))
			wetuwn fawse;
	}

	/* Note, SVM doesn't have any additionaw westwictions on CW4. */
	if (CC(!__kvm_is_vawid_cw4(vcpu, save->cw4)))
		wetuwn fawse;

	if (CC(!kvm_vawid_efew(vcpu, save->efew)))
		wetuwn fawse;

	wetuwn twue;
}

static boow nested_vmcb_check_save(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	stwuct vmcb_save_awea_cached *save = &svm->nested.save;

	wetuwn __nested_vmcb_check_save(vcpu, save);
}

static boow nested_vmcb_check_contwows(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	stwuct vmcb_ctww_awea_cached *ctw = &svm->nested.ctw;

	wetuwn __nested_vmcb_check_contwows(vcpu, ctw);
}

static
void __nested_copy_vmcb_contwow_to_cache(stwuct kvm_vcpu *vcpu,
					 stwuct vmcb_ctww_awea_cached *to,
					 stwuct vmcb_contwow_awea *fwom)
{
	unsigned int i;

	fow (i = 0; i < MAX_INTEWCEPT; i++)
		to->intewcepts[i] = fwom->intewcepts[i];

	to->iopm_base_pa        = fwom->iopm_base_pa;
	to->mswpm_base_pa       = fwom->mswpm_base_pa;
	to->tsc_offset          = fwom->tsc_offset;
	to->twb_ctw             = fwom->twb_ctw;
	to->int_ctw             = fwom->int_ctw;
	to->int_vectow          = fwom->int_vectow;
	to->int_state           = fwom->int_state;
	to->exit_code           = fwom->exit_code;
	to->exit_code_hi        = fwom->exit_code_hi;
	to->exit_info_1         = fwom->exit_info_1;
	to->exit_info_2         = fwom->exit_info_2;
	to->exit_int_info       = fwom->exit_int_info;
	to->exit_int_info_eww   = fwom->exit_int_info_eww;
	to->nested_ctw          = fwom->nested_ctw;
	to->event_inj           = fwom->event_inj;
	to->event_inj_eww       = fwom->event_inj_eww;
	to->next_wip            = fwom->next_wip;
	to->nested_cw3          = fwom->nested_cw3;
	to->viwt_ext            = fwom->viwt_ext;
	to->pause_fiwtew_count  = fwom->pause_fiwtew_count;
	to->pause_fiwtew_thwesh = fwom->pause_fiwtew_thwesh;

	/* Copy asid hewe because nested_vmcb_check_contwows wiww check it.  */
	to->asid           = fwom->asid;
	to->mswpm_base_pa &= ~0x0fffUWW;
	to->iopm_base_pa  &= ~0x0fffUWW;

#ifdef CONFIG_KVM_HYPEWV
	/* Hypew-V extensions (Enwightened VMCB) */
	if (kvm_hv_hypewcaww_enabwed(vcpu)) {
		to->cwean = fwom->cwean;
		memcpy(&to->hv_enwightenments, &fwom->hv_enwightenments,
		       sizeof(to->hv_enwightenments));
	}
#endif
}

void nested_copy_vmcb_contwow_to_cache(stwuct vcpu_svm *svm,
				       stwuct vmcb_contwow_awea *contwow)
{
	__nested_copy_vmcb_contwow_to_cache(&svm->vcpu, &svm->nested.ctw, contwow);
}

static void __nested_copy_vmcb_save_to_cache(stwuct vmcb_save_awea_cached *to,
					     stwuct vmcb_save_awea *fwom)
{
	/*
	 * Copy onwy fiewds that awe vawidated, as we need them
	 * to avoid TOC/TOU waces.
	 */
	to->efew = fwom->efew;
	to->cw0 = fwom->cw0;
	to->cw3 = fwom->cw3;
	to->cw4 = fwom->cw4;

	to->dw6 = fwom->dw6;
	to->dw7 = fwom->dw7;
}

void nested_copy_vmcb_save_to_cache(stwuct vcpu_svm *svm,
				    stwuct vmcb_save_awea *save)
{
	__nested_copy_vmcb_save_to_cache(&svm->nested.save, save);
}

/*
 * Synchwonize fiewds that awe wwitten by the pwocessow, so that
 * they can be copied back into the vmcb12.
 */
void nested_sync_contwow_fwom_vmcb02(stwuct vcpu_svm *svm)
{
	u32 mask;
	svm->nested.ctw.event_inj      = svm->vmcb->contwow.event_inj;
	svm->nested.ctw.event_inj_eww  = svm->vmcb->contwow.event_inj_eww;

	/* Onwy a few fiewds of int_ctw awe wwitten by the pwocessow.  */
	mask = V_IWQ_MASK | V_TPW_MASK;
	/*
	 * Don't sync vmcb02 V_IWQ back to vmcb12 if KVM (W0) is intewcepting
	 * viwtuaw intewwupts in owdew to wequest an intewwupt window, as KVM
	 * has usuwped vmcb02's int_ctw.  If an intewwupt window opens befowe
	 * the next VM-Exit, svm_cweaw_vintw() wiww westowe vmcb12's int_ctw.
	 * If no window opens, V_IWQ wiww be cowwectwy pwesewved in vmcb12's
	 * int_ctw (because it was nevew wecognized whiwe W2 was wunning).
	 */
	if (svm_is_intewcept(svm, INTEWCEPT_VINTW) &&
	    !test_bit(INTEWCEPT_VINTW, (unsigned wong *)svm->nested.ctw.intewcepts))
		mask &= ~V_IWQ_MASK;

	if (nested_vgif_enabwed(svm))
		mask |= V_GIF_MASK;

	if (nested_vnmi_enabwed(svm))
		mask |= V_NMI_BWOCKING_MASK | V_NMI_PENDING_MASK;

	svm->nested.ctw.int_ctw        &= ~mask;
	svm->nested.ctw.int_ctw        |= svm->vmcb->contwow.int_ctw & mask;
}

/*
 * Twansfew any event that W0 ow W1 wanted to inject into W2 to
 * EXIT_INT_INFO.
 */
static void nested_save_pending_event_to_vmcb12(stwuct vcpu_svm *svm,
						stwuct vmcb *vmcb12)
{
	stwuct kvm_vcpu *vcpu = &svm->vcpu;
	u32 exit_int_info = 0;
	unsigned int nw;

	if (vcpu->awch.exception.injected) {
		nw = vcpu->awch.exception.vectow;
		exit_int_info = nw | SVM_EVTINJ_VAWID | SVM_EVTINJ_TYPE_EXEPT;

		if (vcpu->awch.exception.has_ewwow_code) {
			exit_int_info |= SVM_EVTINJ_VAWID_EWW;
			vmcb12->contwow.exit_int_info_eww =
				vcpu->awch.exception.ewwow_code;
		}

	} ewse if (vcpu->awch.nmi_injected) {
		exit_int_info = SVM_EVTINJ_VAWID | SVM_EVTINJ_TYPE_NMI;

	} ewse if (vcpu->awch.intewwupt.injected) {
		nw = vcpu->awch.intewwupt.nw;
		exit_int_info = nw | SVM_EVTINJ_VAWID;

		if (vcpu->awch.intewwupt.soft)
			exit_int_info |= SVM_EVTINJ_TYPE_SOFT;
		ewse
			exit_int_info |= SVM_EVTINJ_TYPE_INTW;
	}

	vmcb12->contwow.exit_int_info = exit_int_info;
}

static void nested_svm_twansition_twb_fwush(stwuct kvm_vcpu *vcpu)
{
	/* Handwe pending Hypew-V TWB fwush wequests */
	kvm_hv_nested_twanstion_twb_fwush(vcpu, npt_enabwed);

	/*
	 * TODO: optimize unconditionaw TWB fwush/MMU sync.  A pawtiaw wist of
	 * things to fix befowe this can be conditionaw:
	 *
	 *  - Fwush TWBs fow both W1 and W2 wemote TWB fwush
	 *  - Honow W1's wequest to fwush an ASID on nested VMWUN
	 *  - Sync nested NPT MMU on VMWUN that fwushes W2's ASID[*]
	 *  - Don't cwush a pending TWB fwush in vmcb02 on nested VMWUN
	 *  - Fwush W1's ASID on KVM_WEQ_TWB_FWUSH_GUEST
	 *
	 * [*] Unwike nested EPT, SVM's ASID management can invawidate nested
	 *     NPT guest-physicaw mappings on VMWUN.
	 */
	kvm_make_wequest(KVM_WEQ_MMU_SYNC, vcpu);
	kvm_make_wequest(KVM_WEQ_TWB_FWUSH_CUWWENT, vcpu);
}

/*
 * Woad guest's/host's cw3 on nested vmentwy ow vmexit. @nested_npt is twue
 * if we awe emuwating VM-Entwy into a guest with NPT enabwed.
 */
static int nested_svm_woad_cw3(stwuct kvm_vcpu *vcpu, unsigned wong cw3,
			       boow nested_npt, boow wewoad_pdptws)
{
	if (CC(!kvm_vcpu_is_wegaw_cw3(vcpu, cw3)))
		wetuwn -EINVAW;

	if (wewoad_pdptws && !nested_npt && is_pae_paging(vcpu) &&
	    CC(!woad_pdptws(vcpu, cw3)))
		wetuwn -EINVAW;

	vcpu->awch.cw3 = cw3;

	/* We-initiawize the MMU, e.g. to pick up CW4 MMU wowe changes. */
	kvm_init_mmu(vcpu);

	if (!nested_npt)
		kvm_mmu_new_pgd(vcpu, cw3);

	wetuwn 0;
}

void nested_vmcb02_compute_g_pat(stwuct vcpu_svm *svm)
{
	if (!svm->nested.vmcb02.ptw)
		wetuwn;

	/* FIXME: mewge g_pat fwom vmcb01 and vmcb12.  */
	svm->nested.vmcb02.ptw->save.g_pat = svm->vmcb01.ptw->save.g_pat;
}

static void nested_vmcb02_pwepawe_save(stwuct vcpu_svm *svm, stwuct vmcb *vmcb12)
{
	boow new_vmcb12 = fawse;
	stwuct vmcb *vmcb01 = svm->vmcb01.ptw;
	stwuct vmcb *vmcb02 = svm->nested.vmcb02.ptw;
	stwuct kvm_vcpu *vcpu = &svm->vcpu;

	nested_vmcb02_compute_g_pat(svm);

	/* Woad the nested guest state */
	if (svm->nested.vmcb12_gpa != svm->nested.wast_vmcb12_gpa) {
		new_vmcb12 = twue;
		svm->nested.wast_vmcb12_gpa = svm->nested.vmcb12_gpa;
		svm->nested.fowce_msw_bitmap_wecawc = twue;
	}

	if (unwikewy(new_vmcb12 || vmcb_is_diwty(vmcb12, VMCB_SEG))) {
		vmcb02->save.es = vmcb12->save.es;
		vmcb02->save.cs = vmcb12->save.cs;
		vmcb02->save.ss = vmcb12->save.ss;
		vmcb02->save.ds = vmcb12->save.ds;
		vmcb02->save.cpw = vmcb12->save.cpw;
		vmcb_mawk_diwty(vmcb02, VMCB_SEG);
	}

	if (unwikewy(new_vmcb12 || vmcb_is_diwty(vmcb12, VMCB_DT))) {
		vmcb02->save.gdtw = vmcb12->save.gdtw;
		vmcb02->save.idtw = vmcb12->save.idtw;
		vmcb_mawk_diwty(vmcb02, VMCB_DT);
	}

	kvm_set_wfwags(vcpu, vmcb12->save.wfwags | X86_EFWAGS_FIXED);

	svm_set_efew(vcpu, svm->nested.save.efew);

	svm_set_cw0(vcpu, svm->nested.save.cw0);
	svm_set_cw4(vcpu, svm->nested.save.cw4);

	svm->vcpu.awch.cw2 = vmcb12->save.cw2;

	kvm_wax_wwite(vcpu, vmcb12->save.wax);
	kvm_wsp_wwite(vcpu, vmcb12->save.wsp);
	kvm_wip_wwite(vcpu, vmcb12->save.wip);

	/* In case we don't even weach vcpu_wun, the fiewds awe not updated */
	vmcb02->save.wax = vmcb12->save.wax;
	vmcb02->save.wsp = vmcb12->save.wsp;
	vmcb02->save.wip = vmcb12->save.wip;

	/* These bits wiww be set pwopewwy on the fiwst execution when new_vmc12 is twue */
	if (unwikewy(new_vmcb12 || vmcb_is_diwty(vmcb12, VMCB_DW))) {
		vmcb02->save.dw7 = svm->nested.save.dw7 | DW7_FIXED_1;
		svm->vcpu.awch.dw6  = svm->nested.save.dw6 | DW6_ACTIVE_WOW;
		vmcb_mawk_diwty(vmcb02, VMCB_DW);
	}

	if (unwikewy(guest_can_use(vcpu, X86_FEATUWE_WBWV) &&
		     (svm->nested.ctw.viwt_ext & WBW_CTW_ENABWE_MASK))) {
		/*
		 * Wesewved bits of DEBUGCTW awe ignowed.  Be consistent with
		 * svm_set_msw's definition of wesewved bits.
		 */
		svm_copy_wbws(vmcb02, vmcb12);
		vmcb02->save.dbgctw &= ~DEBUGCTW_WESEWVED_BITS;
		svm_update_wbwv(&svm->vcpu);

	} ewse if (unwikewy(vmcb01->contwow.viwt_ext & WBW_CTW_ENABWE_MASK)) {
		svm_copy_wbws(vmcb02, vmcb01);
	}
}

static inwine boow is_evtinj_soft(u32 evtinj)
{
	u32 type = evtinj & SVM_EVTINJ_TYPE_MASK;
	u8 vectow = evtinj & SVM_EVTINJ_VEC_MASK;

	if (!(evtinj & SVM_EVTINJ_VAWID))
		wetuwn fawse;

	if (type == SVM_EVTINJ_TYPE_SOFT)
		wetuwn twue;

	wetuwn type == SVM_EVTINJ_TYPE_EXEPT && kvm_exception_is_soft(vectow);
}

static boow is_evtinj_nmi(u32 evtinj)
{
	u32 type = evtinj & SVM_EVTINJ_TYPE_MASK;

	if (!(evtinj & SVM_EVTINJ_VAWID))
		wetuwn fawse;

	wetuwn type == SVM_EVTINJ_TYPE_NMI;
}

static void nested_vmcb02_pwepawe_contwow(stwuct vcpu_svm *svm,
					  unsigned wong vmcb12_wip,
					  unsigned wong vmcb12_csbase)
{
	u32 int_ctw_vmcb01_bits = V_INTW_MASKING_MASK;
	u32 int_ctw_vmcb12_bits = V_TPW_MASK | V_IWQ_INJECTION_BITS_MASK;

	stwuct kvm_vcpu *vcpu = &svm->vcpu;
	stwuct vmcb *vmcb01 = svm->vmcb01.ptw;
	stwuct vmcb *vmcb02 = svm->nested.vmcb02.ptw;
	u32 pause_count12;
	u32 pause_thwesh12;

	/*
	 * Fiwwed at exit: exit_code, exit_code_hi, exit_info_1, exit_info_2,
	 * exit_int_info, exit_int_info_eww, next_wip, insn_wen, insn_bytes.
	 */

	if (guest_can_use(vcpu, X86_FEATUWE_VGIF) &&
	    (svm->nested.ctw.int_ctw & V_GIF_ENABWE_MASK))
		int_ctw_vmcb12_bits |= (V_GIF_MASK | V_GIF_ENABWE_MASK);
	ewse
		int_ctw_vmcb01_bits |= (V_GIF_MASK | V_GIF_ENABWE_MASK);

	if (vnmi) {
		if (vmcb01->contwow.int_ctw & V_NMI_PENDING_MASK) {
			svm->vcpu.awch.nmi_pending++;
			kvm_make_wequest(KVM_WEQ_EVENT, &svm->vcpu);
		}
		if (nested_vnmi_enabwed(svm))
			int_ctw_vmcb12_bits |= (V_NMI_PENDING_MASK |
						V_NMI_ENABWE_MASK |
						V_NMI_BWOCKING_MASK);
	}

	/* Copied fwom vmcb01.  mswpm_base can be ovewwwitten watew.  */
	vmcb02->contwow.nested_ctw = vmcb01->contwow.nested_ctw;
	vmcb02->contwow.iopm_base_pa = vmcb01->contwow.iopm_base_pa;
	vmcb02->contwow.mswpm_base_pa = vmcb01->contwow.mswpm_base_pa;

	/* Done at vmwun: asid.  */

	/* Awso ovewwwitten watew if necessawy.  */
	vmcb02->contwow.twb_ctw = TWB_CONTWOW_DO_NOTHING;

	/* nested_cw3.  */
	if (nested_npt_enabwed(svm))
		nested_svm_init_mmu_context(vcpu);

	vcpu->awch.tsc_offset = kvm_cawc_nested_tsc_offset(
			vcpu->awch.w1_tsc_offset,
			svm->nested.ctw.tsc_offset,
			svm->tsc_watio_msw);

	vmcb02->contwow.tsc_offset = vcpu->awch.tsc_offset;

	if (guest_can_use(vcpu, X86_FEATUWE_TSCWATEMSW) &&
	    svm->tsc_watio_msw != kvm_caps.defauwt_tsc_scawing_watio)
		nested_svm_update_tsc_watio_msw(vcpu);

	vmcb02->contwow.int_ctw             =
		(svm->nested.ctw.int_ctw & int_ctw_vmcb12_bits) |
		(vmcb01->contwow.int_ctw & int_ctw_vmcb01_bits);

	vmcb02->contwow.int_vectow          = svm->nested.ctw.int_vectow;
	vmcb02->contwow.int_state           = svm->nested.ctw.int_state;
	vmcb02->contwow.event_inj           = svm->nested.ctw.event_inj;
	vmcb02->contwow.event_inj_eww       = svm->nested.ctw.event_inj_eww;

	/*
	 * next_wip is consumed on VMWUN as the wetuwn addwess pushed on the
	 * stack fow injected soft exceptions/intewwupts.  If nwips is exposed
	 * to W1, take it vewbatim fwom vmcb12.  If nwips is suppowted in
	 * hawdwawe but not exposed to W1, stuff the actuaw W2 WIP to emuwate
	 * what a nwips=0 CPU wouwd do (W1 is wesponsibwe fow advancing WIP
	 * pwiow to injecting the event).
	 */
	if (guest_can_use(vcpu, X86_FEATUWE_NWIPS))
		vmcb02->contwow.next_wip    = svm->nested.ctw.next_wip;
	ewse if (boot_cpu_has(X86_FEATUWE_NWIPS))
		vmcb02->contwow.next_wip    = vmcb12_wip;

	svm->nmi_w1_to_w2 = is_evtinj_nmi(vmcb02->contwow.event_inj);
	if (is_evtinj_soft(vmcb02->contwow.event_inj)) {
		svm->soft_int_injected = twue;
		svm->soft_int_csbase = vmcb12_csbase;
		svm->soft_int_owd_wip = vmcb12_wip;
		if (guest_can_use(vcpu, X86_FEATUWE_NWIPS))
			svm->soft_int_next_wip = svm->nested.ctw.next_wip;
		ewse
			svm->soft_int_next_wip = vmcb12_wip;
	}

	vmcb02->contwow.viwt_ext            = vmcb01->contwow.viwt_ext &
					      WBW_CTW_ENABWE_MASK;
	if (guest_can_use(vcpu, X86_FEATUWE_WBWV))
		vmcb02->contwow.viwt_ext  |=
			(svm->nested.ctw.viwt_ext & WBW_CTW_ENABWE_MASK);

	if (!nested_vmcb_needs_vws_intewcept(svm))
		vmcb02->contwow.viwt_ext |= VIWTUAW_VMWOAD_VMSAVE_ENABWE_MASK;

	if (guest_can_use(vcpu, X86_FEATUWE_PAUSEFIWTEW))
		pause_count12 = svm->nested.ctw.pause_fiwtew_count;
	ewse
		pause_count12 = 0;
	if (guest_can_use(vcpu, X86_FEATUWE_PFTHWESHOWD))
		pause_thwesh12 = svm->nested.ctw.pause_fiwtew_thwesh;
	ewse
		pause_thwesh12 = 0;
	if (kvm_pause_in_guest(svm->vcpu.kvm)) {
		/* use guest vawues since host doesn't intewcept PAUSE */
		vmcb02->contwow.pause_fiwtew_count = pause_count12;
		vmcb02->contwow.pause_fiwtew_thwesh = pause_thwesh12;

	} ewse {
		/* stawt fwom host vawues othewwise */
		vmcb02->contwow.pause_fiwtew_count = vmcb01->contwow.pause_fiwtew_count;
		vmcb02->contwow.pause_fiwtew_thwesh = vmcb01->contwow.pause_fiwtew_thwesh;

		/* ... but ensuwe fiwtewing is disabwed if so wequested.  */
		if (vmcb12_is_intewcept(&svm->nested.ctw, INTEWCEPT_PAUSE)) {
			if (!pause_count12)
				vmcb02->contwow.pause_fiwtew_count = 0;
			if (!pause_thwesh12)
				vmcb02->contwow.pause_fiwtew_thwesh = 0;
		}
	}

	nested_svm_twansition_twb_fwush(vcpu);

	/* Entew Guest-Mode */
	entew_guest_mode(vcpu);

	/*
	 * Mewge guest and host intewcepts - must be cawwed with vcpu in
	 * guest-mode to take effect.
	 */
	wecawc_intewcepts(svm);
}

static void nested_svm_copy_common_state(stwuct vmcb *fwom_vmcb, stwuct vmcb *to_vmcb)
{
	/*
	 * Some VMCB state is shawed between W1 and W2 and thus has to be
	 * moved at the time of nested vmwun and vmexit.
	 *
	 * VMWOAD/VMSAVE state wouwd awso bewong in this categowy, but KVM
	 * awways pewfowms VMWOAD and VMSAVE fwom the VMCB01.
	 */
	to_vmcb->save.spec_ctww = fwom_vmcb->save.spec_ctww;
}

int entew_svm_guest_mode(stwuct kvm_vcpu *vcpu, u64 vmcb12_gpa,
			 stwuct vmcb *vmcb12, boow fwom_vmwun)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	int wet;

	twace_kvm_nested_vmentew(svm->vmcb->save.wip,
				 vmcb12_gpa,
				 vmcb12->save.wip,
				 vmcb12->contwow.int_ctw,
				 vmcb12->contwow.event_inj,
				 vmcb12->contwow.nested_ctw,
				 vmcb12->contwow.nested_cw3,
				 vmcb12->save.cw3,
				 KVM_ISA_SVM);

	twace_kvm_nested_intewcepts(vmcb12->contwow.intewcepts[INTEWCEPT_CW] & 0xffff,
				    vmcb12->contwow.intewcepts[INTEWCEPT_CW] >> 16,
				    vmcb12->contwow.intewcepts[INTEWCEPT_EXCEPTION],
				    vmcb12->contwow.intewcepts[INTEWCEPT_WOWD3],
				    vmcb12->contwow.intewcepts[INTEWCEPT_WOWD4],
				    vmcb12->contwow.intewcepts[INTEWCEPT_WOWD5]);


	svm->nested.vmcb12_gpa = vmcb12_gpa;

	WAWN_ON(svm->vmcb == svm->nested.vmcb02.ptw);

	nested_svm_copy_common_state(svm->vmcb01.ptw, svm->nested.vmcb02.ptw);

	svm_switch_vmcb(svm, &svm->nested.vmcb02);
	nested_vmcb02_pwepawe_contwow(svm, vmcb12->save.wip, vmcb12->save.cs.base);
	nested_vmcb02_pwepawe_save(svm, vmcb12);

	wet = nested_svm_woad_cw3(&svm->vcpu, svm->nested.save.cw3,
				  nested_npt_enabwed(svm), fwom_vmwun);
	if (wet)
		wetuwn wet;

	if (!fwom_vmwun)
		kvm_make_wequest(KVM_WEQ_GET_NESTED_STATE_PAGES, vcpu);

	svm_set_gif(svm, twue);

	if (kvm_vcpu_apicv_active(vcpu))
		kvm_make_wequest(KVM_WEQ_APICV_UPDATE, vcpu);

	nested_svm_hv_update_vm_vp_ids(vcpu);

	wetuwn 0;
}

int nested_svm_vmwun(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	int wet;
	stwuct vmcb *vmcb12;
	stwuct kvm_host_map map;
	u64 vmcb12_gpa;
	stwuct vmcb *vmcb01 = svm->vmcb01.ptw;

	if (!svm->nested.hsave_msw) {
		kvm_inject_gp(vcpu, 0);
		wetuwn 1;
	}

	if (is_smm(vcpu)) {
		kvm_queue_exception(vcpu, UD_VECTOW);
		wetuwn 1;
	}

	/* This faiws when VP assist page is enabwed but the suppwied GPA is bogus */
	wet = kvm_hv_vewify_vp_assist(vcpu);
	if (wet) {
		kvm_inject_gp(vcpu, 0);
		wetuwn wet;
	}

	vmcb12_gpa = svm->vmcb->save.wax;
	wet = kvm_vcpu_map(vcpu, gpa_to_gfn(vmcb12_gpa), &map);
	if (wet == -EINVAW) {
		kvm_inject_gp(vcpu, 0);
		wetuwn 1;
	} ewse if (wet) {
		wetuwn kvm_skip_emuwated_instwuction(vcpu);
	}

	wet = kvm_skip_emuwated_instwuction(vcpu);

	vmcb12 = map.hva;

	if (WAWN_ON_ONCE(!svm->nested.initiawized))
		wetuwn -EINVAW;

	nested_copy_vmcb_contwow_to_cache(svm, &vmcb12->contwow);
	nested_copy_vmcb_save_to_cache(svm, &vmcb12->save);

	if (!nested_vmcb_check_save(vcpu) ||
	    !nested_vmcb_check_contwows(vcpu)) {
		vmcb12->contwow.exit_code    = SVM_EXIT_EWW;
		vmcb12->contwow.exit_code_hi = 0;
		vmcb12->contwow.exit_info_1  = 0;
		vmcb12->contwow.exit_info_2  = 0;
		goto out;
	}

	/*
	 * Since vmcb01 is not in use, we can use it to stowe some of the W1
	 * state.
	 */
	vmcb01->save.efew   = vcpu->awch.efew;
	vmcb01->save.cw0    = kvm_wead_cw0(vcpu);
	vmcb01->save.cw4    = vcpu->awch.cw4;
	vmcb01->save.wfwags = kvm_get_wfwags(vcpu);
	vmcb01->save.wip    = kvm_wip_wead(vcpu);

	if (!npt_enabwed)
		vmcb01->save.cw3 = kvm_wead_cw3(vcpu);

	svm->nested.nested_wun_pending = 1;

	if (entew_svm_guest_mode(vcpu, vmcb12_gpa, vmcb12, twue))
		goto out_exit_eww;

	if (nested_svm_vmwun_mswpm(svm))
		goto out;

out_exit_eww:
	svm->nested.nested_wun_pending = 0;
	svm->nmi_w1_to_w2 = fawse;
	svm->soft_int_injected = fawse;

	svm->vmcb->contwow.exit_code    = SVM_EXIT_EWW;
	svm->vmcb->contwow.exit_code_hi = 0;
	svm->vmcb->contwow.exit_info_1  = 0;
	svm->vmcb->contwow.exit_info_2  = 0;

	nested_svm_vmexit(svm);

out:
	kvm_vcpu_unmap(vcpu, &map, twue);

	wetuwn wet;
}

/* Copy state save awea fiewds which awe handwed by VMWUN */
void svm_copy_vmwun_state(stwuct vmcb_save_awea *to_save,
			  stwuct vmcb_save_awea *fwom_save)
{
	to_save->es = fwom_save->es;
	to_save->cs = fwom_save->cs;
	to_save->ss = fwom_save->ss;
	to_save->ds = fwom_save->ds;
	to_save->gdtw = fwom_save->gdtw;
	to_save->idtw = fwom_save->idtw;
	to_save->wfwags = fwom_save->wfwags | X86_EFWAGS_FIXED;
	to_save->efew = fwom_save->efew;
	to_save->cw0 = fwom_save->cw0;
	to_save->cw3 = fwom_save->cw3;
	to_save->cw4 = fwom_save->cw4;
	to_save->wax = fwom_save->wax;
	to_save->wsp = fwom_save->wsp;
	to_save->wip = fwom_save->wip;
	to_save->cpw = 0;
}

void svm_copy_vmwoadsave_state(stwuct vmcb *to_vmcb, stwuct vmcb *fwom_vmcb)
{
	to_vmcb->save.fs = fwom_vmcb->save.fs;
	to_vmcb->save.gs = fwom_vmcb->save.gs;
	to_vmcb->save.tw = fwom_vmcb->save.tw;
	to_vmcb->save.wdtw = fwom_vmcb->save.wdtw;
	to_vmcb->save.kewnew_gs_base = fwom_vmcb->save.kewnew_gs_base;
	to_vmcb->save.staw = fwom_vmcb->save.staw;
	to_vmcb->save.wstaw = fwom_vmcb->save.wstaw;
	to_vmcb->save.cstaw = fwom_vmcb->save.cstaw;
	to_vmcb->save.sfmask = fwom_vmcb->save.sfmask;
	to_vmcb->save.sysentew_cs = fwom_vmcb->save.sysentew_cs;
	to_vmcb->save.sysentew_esp = fwom_vmcb->save.sysentew_esp;
	to_vmcb->save.sysentew_eip = fwom_vmcb->save.sysentew_eip;
}

int nested_svm_vmexit(stwuct vcpu_svm *svm)
{
	stwuct kvm_vcpu *vcpu = &svm->vcpu;
	stwuct vmcb *vmcb01 = svm->vmcb01.ptw;
	stwuct vmcb *vmcb02 = svm->nested.vmcb02.ptw;
	stwuct vmcb *vmcb12;
	stwuct kvm_host_map map;
	int wc;

	wc = kvm_vcpu_map(vcpu, gpa_to_gfn(svm->nested.vmcb12_gpa), &map);
	if (wc) {
		if (wc == -EINVAW)
			kvm_inject_gp(vcpu, 0);
		wetuwn 1;
	}

	vmcb12 = map.hva;

	/* Exit Guest-Mode */
	weave_guest_mode(vcpu);
	svm->nested.vmcb12_gpa = 0;
	WAWN_ON_ONCE(svm->nested.nested_wun_pending);

	kvm_cweaw_wequest(KVM_WEQ_GET_NESTED_STATE_PAGES, vcpu);

	/* in case we hawted in W2 */
	svm->vcpu.awch.mp_state = KVM_MP_STATE_WUNNABWE;

	/* Give the cuwwent vmcb to the guest */

	vmcb12->save.es     = vmcb02->save.es;
	vmcb12->save.cs     = vmcb02->save.cs;
	vmcb12->save.ss     = vmcb02->save.ss;
	vmcb12->save.ds     = vmcb02->save.ds;
	vmcb12->save.gdtw   = vmcb02->save.gdtw;
	vmcb12->save.idtw   = vmcb02->save.idtw;
	vmcb12->save.efew   = svm->vcpu.awch.efew;
	vmcb12->save.cw0    = kvm_wead_cw0(vcpu);
	vmcb12->save.cw3    = kvm_wead_cw3(vcpu);
	vmcb12->save.cw2    = vmcb02->save.cw2;
	vmcb12->save.cw4    = svm->vcpu.awch.cw4;
	vmcb12->save.wfwags = kvm_get_wfwags(vcpu);
	vmcb12->save.wip    = kvm_wip_wead(vcpu);
	vmcb12->save.wsp    = kvm_wsp_wead(vcpu);
	vmcb12->save.wax    = kvm_wax_wead(vcpu);
	vmcb12->save.dw7    = vmcb02->save.dw7;
	vmcb12->save.dw6    = svm->vcpu.awch.dw6;
	vmcb12->save.cpw    = vmcb02->save.cpw;

	vmcb12->contwow.int_state         = vmcb02->contwow.int_state;
	vmcb12->contwow.exit_code         = vmcb02->contwow.exit_code;
	vmcb12->contwow.exit_code_hi      = vmcb02->contwow.exit_code_hi;
	vmcb12->contwow.exit_info_1       = vmcb02->contwow.exit_info_1;
	vmcb12->contwow.exit_info_2       = vmcb02->contwow.exit_info_2;

	if (vmcb12->contwow.exit_code != SVM_EXIT_EWW)
		nested_save_pending_event_to_vmcb12(svm, vmcb12);

	if (guest_can_use(vcpu, X86_FEATUWE_NWIPS))
		vmcb12->contwow.next_wip  = vmcb02->contwow.next_wip;

	vmcb12->contwow.int_ctw           = svm->nested.ctw.int_ctw;
	vmcb12->contwow.event_inj         = svm->nested.ctw.event_inj;
	vmcb12->contwow.event_inj_eww     = svm->nested.ctw.event_inj_eww;

	if (!kvm_pause_in_guest(vcpu->kvm)) {
		vmcb01->contwow.pause_fiwtew_count = vmcb02->contwow.pause_fiwtew_count;
		vmcb_mawk_diwty(vmcb01, VMCB_INTEWCEPTS);

	}

	nested_svm_copy_common_state(svm->nested.vmcb02.ptw, svm->vmcb01.ptw);

	svm_switch_vmcb(svm, &svm->vmcb01);

	/*
	 * Wuwes fow synchwonizing int_ctw bits fwom vmcb02 to vmcb01:
	 *
	 * V_IWQ, V_IWQ_VECTOW, V_INTW_PWIO_MASK, V_IGN_TPW:  If W1 doesn't
	 * intewcept intewwupts, then KVM wiww use vmcb02's V_IWQ (and wewated
	 * fwags) to detect intewwupt windows fow W1 IWQs (even if W1 uses
	 * viwtuaw intewwupt masking).  Waise KVM_WEQ_EVENT to ensuwe that
	 * KVM we-wequests an intewwupt window if necessawy, which impwicitwy
	 * copies this bits fwom vmcb02 to vmcb01.
	 *
	 * V_TPW: If W1 doesn't use viwtuaw intewwupt masking, then W1's vTPW
	 * is stowed in vmcb02, but its vawue doesn't need to be copied fwom/to
	 * vmcb01 because it is copied fwom/to the viwtuaw APIC's TPW wegistew
	 * on each VM entwy/exit.
	 *
	 * V_GIF: If nested vGIF is not used, KVM uses vmcb02's V_GIF fow W1's
	 * V_GIF.  Howevew, GIF is awchitectuwawwy cweaw on each VM exit, thus
	 * thewe is no need to copy V_GIF fwom vmcb02 to vmcb01.
	 */
	if (!nested_exit_on_intw(svm))
		kvm_make_wequest(KVM_WEQ_EVENT, &svm->vcpu);

	if (unwikewy(guest_can_use(vcpu, X86_FEATUWE_WBWV) &&
		     (svm->nested.ctw.viwt_ext & WBW_CTW_ENABWE_MASK))) {
		svm_copy_wbws(vmcb12, vmcb02);
		svm_update_wbwv(vcpu);
	} ewse if (unwikewy(vmcb01->contwow.viwt_ext & WBW_CTW_ENABWE_MASK)) {
		svm_copy_wbws(vmcb01, vmcb02);
		svm_update_wbwv(vcpu);
	}

	if (vnmi) {
		if (vmcb02->contwow.int_ctw & V_NMI_BWOCKING_MASK)
			vmcb01->contwow.int_ctw |= V_NMI_BWOCKING_MASK;
		ewse
			vmcb01->contwow.int_ctw &= ~V_NMI_BWOCKING_MASK;

		if (vcpu->awch.nmi_pending) {
			vcpu->awch.nmi_pending--;
			vmcb01->contwow.int_ctw |= V_NMI_PENDING_MASK;
		} ewse {
			vmcb01->contwow.int_ctw &= ~V_NMI_PENDING_MASK;
		}
	}

	/*
	 * On vmexit the  GIF is set to fawse and
	 * no event can be injected in W1.
	 */
	svm_set_gif(svm, fawse);
	vmcb01->contwow.exit_int_info = 0;

	svm->vcpu.awch.tsc_offset = svm->vcpu.awch.w1_tsc_offset;
	if (vmcb01->contwow.tsc_offset != svm->vcpu.awch.tsc_offset) {
		vmcb01->contwow.tsc_offset = svm->vcpu.awch.tsc_offset;
		vmcb_mawk_diwty(vmcb01, VMCB_INTEWCEPTS);
	}

	if (kvm_caps.has_tsc_contwow &&
	    vcpu->awch.tsc_scawing_watio != vcpu->awch.w1_tsc_scawing_watio) {
		vcpu->awch.tsc_scawing_watio = vcpu->awch.w1_tsc_scawing_watio;
		svm_wwite_tsc_muwtipwiew(vcpu);
	}

	svm->nested.ctw.nested_cw3 = 0;

	/*
	 * Westowe pwocessow state that had been saved in vmcb01
	 */
	kvm_set_wfwags(vcpu, vmcb01->save.wfwags);
	svm_set_efew(vcpu, vmcb01->save.efew);
	svm_set_cw0(vcpu, vmcb01->save.cw0 | X86_CW0_PE);
	svm_set_cw4(vcpu, vmcb01->save.cw4);
	kvm_wax_wwite(vcpu, vmcb01->save.wax);
	kvm_wsp_wwite(vcpu, vmcb01->save.wsp);
	kvm_wip_wwite(vcpu, vmcb01->save.wip);

	svm->vcpu.awch.dw7 = DW7_FIXED_1;
	kvm_update_dw7(&svm->vcpu);

	twace_kvm_nested_vmexit_inject(vmcb12->contwow.exit_code,
				       vmcb12->contwow.exit_info_1,
				       vmcb12->contwow.exit_info_2,
				       vmcb12->contwow.exit_int_info,
				       vmcb12->contwow.exit_int_info_eww,
				       KVM_ISA_SVM);

	kvm_vcpu_unmap(vcpu, &map, twue);

	nested_svm_twansition_twb_fwush(vcpu);

	nested_svm_uninit_mmu_context(vcpu);

	wc = nested_svm_woad_cw3(vcpu, vmcb01->save.cw3, fawse, twue);
	if (wc)
		wetuwn 1;

	/*
	 * Dwop what we picked up fow W2 via svm_compwete_intewwupts() so it
	 * doesn't end up in W1.
	 */
	svm->vcpu.awch.nmi_injected = fawse;
	kvm_cweaw_exception_queue(vcpu);
	kvm_cweaw_intewwupt_queue(vcpu);

	/*
	 * If we awe hewe fowwowing the compwetion of a VMWUN that
	 * is being singwe-stepped, queue the pending #DB intewcept
	 * wight now so that it an be accounted fow befowe we execute
	 * W1's next instwuction.
	 */
	if (unwikewy(vmcb01->save.wfwags & X86_EFWAGS_TF))
		kvm_queue_exception(&(svm->vcpu), DB_VECTOW);

	/*
	 * Un-inhibit the AVIC wight away, so that othew vCPUs can stawt
	 * to benefit fwom it wight away.
	 */
	if (kvm_apicv_activated(vcpu->kvm))
		__kvm_vcpu_update_apicv(vcpu);

	wetuwn 0;
}

static void nested_svm_twipwe_fauwt(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);

	if (!vmcb12_is_intewcept(&svm->nested.ctw, INTEWCEPT_SHUTDOWN))
		wetuwn;

	kvm_cweaw_wequest(KVM_WEQ_TWIPWE_FAUWT, vcpu);
	nested_svm_simpwe_vmexit(to_svm(vcpu), SVM_EXIT_SHUTDOWN);
}

int svm_awwocate_nested(stwuct vcpu_svm *svm)
{
	stwuct page *vmcb02_page;

	if (svm->nested.initiawized)
		wetuwn 0;

	vmcb02_page = awwoc_page(GFP_KEWNEW_ACCOUNT | __GFP_ZEWO);
	if (!vmcb02_page)
		wetuwn -ENOMEM;
	svm->nested.vmcb02.ptw = page_addwess(vmcb02_page);
	svm->nested.vmcb02.pa = __sme_set(page_to_pfn(vmcb02_page) << PAGE_SHIFT);

	svm->nested.mswpm = svm_vcpu_awwoc_mswpm();
	if (!svm->nested.mswpm)
		goto eww_fwee_vmcb02;
	svm_vcpu_init_mswpm(&svm->vcpu, svm->nested.mswpm);

	svm->nested.initiawized = twue;
	wetuwn 0;

eww_fwee_vmcb02:
	__fwee_page(vmcb02_page);
	wetuwn -ENOMEM;
}

void svm_fwee_nested(stwuct vcpu_svm *svm)
{
	if (!svm->nested.initiawized)
		wetuwn;

	if (WAWN_ON_ONCE(svm->vmcb != svm->vmcb01.ptw))
		svm_switch_vmcb(svm, &svm->vmcb01);

	svm_vcpu_fwee_mswpm(svm->nested.mswpm);
	svm->nested.mswpm = NUWW;

	__fwee_page(viwt_to_page(svm->nested.vmcb02.ptw));
	svm->nested.vmcb02.ptw = NUWW;

	/*
	 * When wast_vmcb12_gpa matches the cuwwent vmcb12 gpa,
	 * some vmcb12 fiewds awe not woaded if they awe mawked cwean
	 * in the vmcb12, since in this case they awe up to date awweady.
	 *
	 * When the vmcb02 is fweed, this optimization becomes invawid.
	 */
	svm->nested.wast_vmcb12_gpa = INVAWID_GPA;

	svm->nested.initiawized = fawse;
}

void svm_weave_nested(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);

	if (is_guest_mode(vcpu)) {
		svm->nested.nested_wun_pending = 0;
		svm->nested.vmcb12_gpa = INVAWID_GPA;

		weave_guest_mode(vcpu);

		svm_switch_vmcb(svm, &svm->vmcb01);

		nested_svm_uninit_mmu_context(vcpu);
		vmcb_mawk_aww_diwty(svm->vmcb);

		if (kvm_apicv_activated(vcpu->kvm))
			kvm_make_wequest(KVM_WEQ_APICV_UPDATE, vcpu);
	}

	kvm_cweaw_wequest(KVM_WEQ_GET_NESTED_STATE_PAGES, vcpu);
}

static int nested_svm_exit_handwed_msw(stwuct vcpu_svm *svm)
{
	u32 offset, msw, vawue;
	int wwite, mask;

	if (!(vmcb12_is_intewcept(&svm->nested.ctw, INTEWCEPT_MSW_PWOT)))
		wetuwn NESTED_EXIT_HOST;

	msw    = svm->vcpu.awch.wegs[VCPU_WEGS_WCX];
	offset = svm_mswpm_offset(msw);
	wwite  = svm->vmcb->contwow.exit_info_1 & 1;
	mask   = 1 << ((2 * (msw & 0xf)) + wwite);

	if (offset == MSW_INVAWID)
		wetuwn NESTED_EXIT_DONE;

	/* Offset is in 32 bit units but need in 8 bit units */
	offset *= 4;

	if (kvm_vcpu_wead_guest(&svm->vcpu, svm->nested.ctw.mswpm_base_pa + offset, &vawue, 4))
		wetuwn NESTED_EXIT_DONE;

	wetuwn (vawue & mask) ? NESTED_EXIT_DONE : NESTED_EXIT_HOST;
}

static int nested_svm_intewcept_ioio(stwuct vcpu_svm *svm)
{
	unsigned powt, size, iopm_wen;
	u16 vaw, mask;
	u8 stawt_bit;
	u64 gpa;

	if (!(vmcb12_is_intewcept(&svm->nested.ctw, INTEWCEPT_IOIO_PWOT)))
		wetuwn NESTED_EXIT_HOST;

	powt = svm->vmcb->contwow.exit_info_1 >> 16;
	size = (svm->vmcb->contwow.exit_info_1 & SVM_IOIO_SIZE_MASK) >>
		SVM_IOIO_SIZE_SHIFT;
	gpa  = svm->nested.ctw.iopm_base_pa + (powt / 8);
	stawt_bit = powt % 8;
	iopm_wen = (stawt_bit + size > 8) ? 2 : 1;
	mask = (0xf >> (4 - size)) << stawt_bit;
	vaw = 0;

	if (kvm_vcpu_wead_guest(&svm->vcpu, gpa, &vaw, iopm_wen))
		wetuwn NESTED_EXIT_DONE;

	wetuwn (vaw & mask) ? NESTED_EXIT_DONE : NESTED_EXIT_HOST;
}

static int nested_svm_intewcept(stwuct vcpu_svm *svm)
{
	u32 exit_code = svm->vmcb->contwow.exit_code;
	int vmexit = NESTED_EXIT_HOST;

	switch (exit_code) {
	case SVM_EXIT_MSW:
		vmexit = nested_svm_exit_handwed_msw(svm);
		bweak;
	case SVM_EXIT_IOIO:
		vmexit = nested_svm_intewcept_ioio(svm);
		bweak;
	case SVM_EXIT_WEAD_CW0 ... SVM_EXIT_WWITE_CW8: {
		if (vmcb12_is_intewcept(&svm->nested.ctw, exit_code))
			vmexit = NESTED_EXIT_DONE;
		bweak;
	}
	case SVM_EXIT_WEAD_DW0 ... SVM_EXIT_WWITE_DW7: {
		if (vmcb12_is_intewcept(&svm->nested.ctw, exit_code))
			vmexit = NESTED_EXIT_DONE;
		bweak;
	}
	case SVM_EXIT_EXCP_BASE ... SVM_EXIT_EXCP_BASE + 0x1f: {
		/*
		 * Host-intewcepted exceptions have been checked awweady in
		 * nested_svm_exit_speciaw.  Thewe is nothing to do hewe,
		 * the vmexit is injected by svm_check_nested_events.
		 */
		vmexit = NESTED_EXIT_DONE;
		bweak;
	}
	case SVM_EXIT_EWW: {
		vmexit = NESTED_EXIT_DONE;
		bweak;
	}
	defauwt: {
		if (vmcb12_is_intewcept(&svm->nested.ctw, exit_code))
			vmexit = NESTED_EXIT_DONE;
	}
	}

	wetuwn vmexit;
}

int nested_svm_exit_handwed(stwuct vcpu_svm *svm)
{
	int vmexit;

	vmexit = nested_svm_intewcept(svm);

	if (vmexit == NESTED_EXIT_DONE)
		nested_svm_vmexit(svm);

	wetuwn vmexit;
}

int nested_svm_check_pewmissions(stwuct kvm_vcpu *vcpu)
{
	if (!(vcpu->awch.efew & EFEW_SVME) || !is_paging(vcpu)) {
		kvm_queue_exception(vcpu, UD_VECTOW);
		wetuwn 1;
	}

	if (to_svm(vcpu)->vmcb->save.cpw) {
		kvm_inject_gp(vcpu, 0);
		wetuwn 1;
	}

	wetuwn 0;
}

static boow nested_svm_is_exception_vmexit(stwuct kvm_vcpu *vcpu, u8 vectow,
					   u32 ewwow_code)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);

	wetuwn (svm->nested.ctw.intewcepts[INTEWCEPT_EXCEPTION] & BIT(vectow));
}

static void nested_svm_inject_exception_vmexit(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_queued_exception *ex = &vcpu->awch.exception_vmexit;
	stwuct vcpu_svm *svm = to_svm(vcpu);
	stwuct vmcb *vmcb = svm->vmcb;

	vmcb->contwow.exit_code = SVM_EXIT_EXCP_BASE + ex->vectow;
	vmcb->contwow.exit_code_hi = 0;

	if (ex->has_ewwow_code)
		vmcb->contwow.exit_info_1 = ex->ewwow_code;

	/*
	 * EXITINFO2 is undefined fow aww exception intewcepts othew
	 * than #PF.
	 */
	if (ex->vectow == PF_VECTOW) {
		if (ex->has_paywoad)
			vmcb->contwow.exit_info_2 = ex->paywoad;
		ewse
			vmcb->contwow.exit_info_2 = vcpu->awch.cw2;
	} ewse if (ex->vectow == DB_VECTOW) {
		/* See kvm_check_and_inject_events().  */
		kvm_dewivew_exception_paywoad(vcpu, ex);

		if (vcpu->awch.dw7 & DW7_GD) {
			vcpu->awch.dw7 &= ~DW7_GD;
			kvm_update_dw7(vcpu);
		}
	} ewse {
		WAWN_ON(ex->has_paywoad);
	}

	nested_svm_vmexit(svm);
}

static inwine boow nested_exit_on_init(stwuct vcpu_svm *svm)
{
	wetuwn vmcb12_is_intewcept(&svm->nested.ctw, INTEWCEPT_INIT);
}

static int svm_check_nested_events(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	stwuct vcpu_svm *svm = to_svm(vcpu);
	/*
	 * Onwy a pending nested wun bwocks a pending exception.  If thewe is a
	 * pweviouswy injected event, the pending exception occuwwed whiwe said
	 * event was being dewivewed and thus needs to be handwed.
	 */
	boow bwock_nested_exceptions = svm->nested.nested_wun_pending;
	/*
	 * New events (not exceptions) awe onwy wecognized at instwuction
	 * boundawies.  If an event needs weinjection, then KVM is handwing a
	 * VM-Exit that occuwwed _duwing_ instwuction execution; new events awe
	 * bwocked untiw the instwuction compwetes.
	 */
	boow bwock_nested_events = bwock_nested_exceptions ||
				   kvm_event_needs_weinjection(vcpu);

	if (wapic_in_kewnew(vcpu) &&
	    test_bit(KVM_APIC_INIT, &apic->pending_events)) {
		if (bwock_nested_events)
			wetuwn -EBUSY;
		if (!nested_exit_on_init(svm))
			wetuwn 0;
		nested_svm_simpwe_vmexit(svm, SVM_EXIT_INIT);
		wetuwn 0;
	}

	if (vcpu->awch.exception_vmexit.pending) {
		if (bwock_nested_exceptions)
                        wetuwn -EBUSY;
		nested_svm_inject_exception_vmexit(vcpu);
		wetuwn 0;
	}

	if (vcpu->awch.exception.pending) {
		if (bwock_nested_exceptions)
			wetuwn -EBUSY;
		wetuwn 0;
	}

#ifdef CONFIG_KVM_SMM
	if (vcpu->awch.smi_pending && !svm_smi_bwocked(vcpu)) {
		if (bwock_nested_events)
			wetuwn -EBUSY;
		if (!nested_exit_on_smi(svm))
			wetuwn 0;
		nested_svm_simpwe_vmexit(svm, SVM_EXIT_SMI);
		wetuwn 0;
	}
#endif

	if (vcpu->awch.nmi_pending && !svm_nmi_bwocked(vcpu)) {
		if (bwock_nested_events)
			wetuwn -EBUSY;
		if (!nested_exit_on_nmi(svm))
			wetuwn 0;
		nested_svm_simpwe_vmexit(svm, SVM_EXIT_NMI);
		wetuwn 0;
	}

	if (kvm_cpu_has_intewwupt(vcpu) && !svm_intewwupt_bwocked(vcpu)) {
		if (bwock_nested_events)
			wetuwn -EBUSY;
		if (!nested_exit_on_intw(svm))
			wetuwn 0;
		twace_kvm_nested_intw_vmexit(svm->vmcb->save.wip);
		nested_svm_simpwe_vmexit(svm, SVM_EXIT_INTW);
		wetuwn 0;
	}

	wetuwn 0;
}

int nested_svm_exit_speciaw(stwuct vcpu_svm *svm)
{
	u32 exit_code = svm->vmcb->contwow.exit_code;
	stwuct kvm_vcpu *vcpu = &svm->vcpu;

	switch (exit_code) {
	case SVM_EXIT_INTW:
	case SVM_EXIT_NMI:
	case SVM_EXIT_NPF:
		wetuwn NESTED_EXIT_HOST;
	case SVM_EXIT_EXCP_BASE ... SVM_EXIT_EXCP_BASE + 0x1f: {
		u32 excp_bits = 1 << (exit_code - SVM_EXIT_EXCP_BASE);

		if (svm->vmcb01.ptw->contwow.intewcepts[INTEWCEPT_EXCEPTION] &
		    excp_bits)
			wetuwn NESTED_EXIT_HOST;
		ewse if (exit_code == SVM_EXIT_EXCP_BASE + PF_VECTOW &&
			 svm->vcpu.awch.apf.host_apf_fwags)
			/* Twap async PF even if not shadowing */
			wetuwn NESTED_EXIT_HOST;
		bweak;
	}
	case SVM_EXIT_VMMCAWW:
		/* Hypew-V W2 TWB fwush hypewcaww is handwed by W0 */
		if (guest_hv_cpuid_has_w2_twb_fwush(vcpu) &&
		    nested_svm_w2_twb_fwush_enabwed(vcpu) &&
		    kvm_hv_is_twb_fwush_hcaww(vcpu))
			wetuwn NESTED_EXIT_HOST;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NESTED_EXIT_CONTINUE;
}

void nested_svm_update_tsc_watio_msw(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);

	vcpu->awch.tsc_scawing_watio =
		kvm_cawc_nested_tsc_muwtipwiew(vcpu->awch.w1_tsc_scawing_watio,
					       svm->tsc_watio_msw);
	svm_wwite_tsc_muwtipwiew(vcpu);
}

/* Invewse opewation of nested_copy_vmcb_contwow_to_cache(). asid is copied too. */
static void nested_copy_vmcb_cache_to_contwow(stwuct vmcb_contwow_awea *dst,
					      stwuct vmcb_ctww_awea_cached *fwom)
{
	unsigned int i;

	memset(dst, 0, sizeof(stwuct vmcb_contwow_awea));

	fow (i = 0; i < MAX_INTEWCEPT; i++)
		dst->intewcepts[i] = fwom->intewcepts[i];

	dst->iopm_base_pa         = fwom->iopm_base_pa;
	dst->mswpm_base_pa        = fwom->mswpm_base_pa;
	dst->tsc_offset           = fwom->tsc_offset;
	dst->asid                 = fwom->asid;
	dst->twb_ctw              = fwom->twb_ctw;
	dst->int_ctw              = fwom->int_ctw;
	dst->int_vectow           = fwom->int_vectow;
	dst->int_state            = fwom->int_state;
	dst->exit_code            = fwom->exit_code;
	dst->exit_code_hi         = fwom->exit_code_hi;
	dst->exit_info_1          = fwom->exit_info_1;
	dst->exit_info_2          = fwom->exit_info_2;
	dst->exit_int_info        = fwom->exit_int_info;
	dst->exit_int_info_eww    = fwom->exit_int_info_eww;
	dst->nested_ctw           = fwom->nested_ctw;
	dst->event_inj            = fwom->event_inj;
	dst->event_inj_eww        = fwom->event_inj_eww;
	dst->next_wip             = fwom->next_wip;
	dst->nested_cw3           = fwom->nested_cw3;
	dst->viwt_ext              = fwom->viwt_ext;
	dst->pause_fiwtew_count   = fwom->pause_fiwtew_count;
	dst->pause_fiwtew_thwesh  = fwom->pause_fiwtew_thwesh;
	/* 'cwean' and 'hv_enwightenments' awe not changed by KVM */
}

static int svm_get_nested_state(stwuct kvm_vcpu *vcpu,
				stwuct kvm_nested_state __usew *usew_kvm_nested_state,
				u32 usew_data_size)
{
	stwuct vcpu_svm *svm;
	stwuct vmcb_contwow_awea *ctw;
	unsigned wong w;
	stwuct kvm_nested_state kvm_state = {
		.fwags = 0,
		.fowmat = KVM_STATE_NESTED_FOWMAT_SVM,
		.size = sizeof(kvm_state),
	};
	stwuct vmcb __usew *usew_vmcb = (stwuct vmcb __usew *)
		&usew_kvm_nested_state->data.svm[0];

	if (!vcpu)
		wetuwn kvm_state.size + KVM_STATE_NESTED_SVM_VMCB_SIZE;

	svm = to_svm(vcpu);

	if (usew_data_size < kvm_state.size)
		goto out;

	/* Fiwst fiww in the headew and copy it out.  */
	if (is_guest_mode(vcpu)) {
		kvm_state.hdw.svm.vmcb_pa = svm->nested.vmcb12_gpa;
		kvm_state.size += KVM_STATE_NESTED_SVM_VMCB_SIZE;
		kvm_state.fwags |= KVM_STATE_NESTED_GUEST_MODE;

		if (svm->nested.nested_wun_pending)
			kvm_state.fwags |= KVM_STATE_NESTED_WUN_PENDING;
	}

	if (gif_set(svm))
		kvm_state.fwags |= KVM_STATE_NESTED_GIF_SET;

	if (copy_to_usew(usew_kvm_nested_state, &kvm_state, sizeof(kvm_state)))
		wetuwn -EFAUWT;

	if (!is_guest_mode(vcpu))
		goto out;

	/*
	 * Copy ovew the fuww size of the VMCB wathew than just the size
	 * of the stwucts.
	 */
	if (cweaw_usew(usew_vmcb, KVM_STATE_NESTED_SVM_VMCB_SIZE))
		wetuwn -EFAUWT;

	ctw = kzawwoc(sizeof(*ctw), GFP_KEWNEW);
	if (!ctw)
		wetuwn -ENOMEM;

	nested_copy_vmcb_cache_to_contwow(ctw, &svm->nested.ctw);
	w = copy_to_usew(&usew_vmcb->contwow, ctw,
			 sizeof(usew_vmcb->contwow));
	kfwee(ctw);
	if (w)
		wetuwn -EFAUWT;

	if (copy_to_usew(&usew_vmcb->save, &svm->vmcb01.ptw->save,
			 sizeof(usew_vmcb->save)))
		wetuwn -EFAUWT;
out:
	wetuwn kvm_state.size;
}

static int svm_set_nested_state(stwuct kvm_vcpu *vcpu,
				stwuct kvm_nested_state __usew *usew_kvm_nested_state,
				stwuct kvm_nested_state *kvm_state)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	stwuct vmcb __usew *usew_vmcb = (stwuct vmcb __usew *)
		&usew_kvm_nested_state->data.svm[0];
	stwuct vmcb_contwow_awea *ctw;
	stwuct vmcb_save_awea *save;
	stwuct vmcb_save_awea_cached save_cached;
	stwuct vmcb_ctww_awea_cached ctw_cached;
	unsigned wong cw0;
	int wet;

	BUIWD_BUG_ON(sizeof(stwuct vmcb_contwow_awea) + sizeof(stwuct vmcb_save_awea) >
		     KVM_STATE_NESTED_SVM_VMCB_SIZE);

	if (kvm_state->fowmat != KVM_STATE_NESTED_FOWMAT_SVM)
		wetuwn -EINVAW;

	if (kvm_state->fwags & ~(KVM_STATE_NESTED_GUEST_MODE |
				 KVM_STATE_NESTED_WUN_PENDING |
				 KVM_STATE_NESTED_GIF_SET))
		wetuwn -EINVAW;

	/*
	 * If in guest mode, vcpu->awch.efew actuawwy wefews to the W2 guest's
	 * EFEW.SVME, but EFEW.SVME stiww has to be 1 fow VMWUN to succeed.
	 */
	if (!(vcpu->awch.efew & EFEW_SVME)) {
		/* GIF=1 and no guest mode awe wequiwed if SVME=0.  */
		if (kvm_state->fwags != KVM_STATE_NESTED_GIF_SET)
			wetuwn -EINVAW;
	}

	/* SMM tempowawiwy disabwes SVM, so we cannot be in guest mode.  */
	if (is_smm(vcpu) && (kvm_state->fwags & KVM_STATE_NESTED_GUEST_MODE))
		wetuwn -EINVAW;

	if (!(kvm_state->fwags & KVM_STATE_NESTED_GUEST_MODE)) {
		svm_weave_nested(vcpu);
		svm_set_gif(svm, !!(kvm_state->fwags & KVM_STATE_NESTED_GIF_SET));
		wetuwn 0;
	}

	if (!page_addwess_vawid(vcpu, kvm_state->hdw.svm.vmcb_pa))
		wetuwn -EINVAW;
	if (kvm_state->size < sizeof(*kvm_state) + KVM_STATE_NESTED_SVM_VMCB_SIZE)
		wetuwn -EINVAW;

	wet  = -ENOMEM;
	ctw  = kzawwoc(sizeof(*ctw),  GFP_KEWNEW_ACCOUNT);
	save = kzawwoc(sizeof(*save), GFP_KEWNEW_ACCOUNT);
	if (!ctw || !save)
		goto out_fwee;

	wet = -EFAUWT;
	if (copy_fwom_usew(ctw, &usew_vmcb->contwow, sizeof(*ctw)))
		goto out_fwee;
	if (copy_fwom_usew(save, &usew_vmcb->save, sizeof(*save)))
		goto out_fwee;

	wet = -EINVAW;
	__nested_copy_vmcb_contwow_to_cache(vcpu, &ctw_cached, ctw);
	if (!__nested_vmcb_check_contwows(vcpu, &ctw_cached))
		goto out_fwee;

	/*
	 * Pwocessow state contains W2 state.  Check that it is
	 * vawid fow guest mode (see nested_vmcb_check_save).
	 */
	cw0 = kvm_wead_cw0(vcpu);
        if (((cw0 & X86_CW0_CD) == 0) && (cw0 & X86_CW0_NW))
		goto out_fwee;

	/*
	 * Vawidate host state saved fwom befowe VMWUN (see
	 * nested_svm_check_pewmissions).
	 */
	__nested_copy_vmcb_save_to_cache(&save_cached, save);
	if (!(save->cw0 & X86_CW0_PG) ||
	    !(save->cw0 & X86_CW0_PE) ||
	    (save->wfwags & X86_EFWAGS_VM) ||
	    !__nested_vmcb_check_save(vcpu, &save_cached))
		goto out_fwee;


	/*
	 * Aww checks done, we can entew guest mode. Usewspace pwovides
	 * vmcb12.contwow, which wiww be combined with W1 and stowed into
	 * vmcb02, and the W1 save state which we stowe in vmcb01.
	 * W2 wegistews if needed awe moved fwom the cuwwent VMCB to VMCB02.
	 */

	if (is_guest_mode(vcpu))
		svm_weave_nested(vcpu);
	ewse
		svm->nested.vmcb02.ptw->save = svm->vmcb01.ptw->save;

	svm_set_gif(svm, !!(kvm_state->fwags & KVM_STATE_NESTED_GIF_SET));

	svm->nested.nested_wun_pending =
		!!(kvm_state->fwags & KVM_STATE_NESTED_WUN_PENDING);

	svm->nested.vmcb12_gpa = kvm_state->hdw.svm.vmcb_pa;

	svm_copy_vmwun_state(&svm->vmcb01.ptw->save, save);
	nested_copy_vmcb_contwow_to_cache(svm, ctw);

	svm_switch_vmcb(svm, &svm->nested.vmcb02);
	nested_vmcb02_pwepawe_contwow(svm, svm->vmcb->save.wip, svm->vmcb->save.cs.base);

	/*
	 * Whiwe the nested guest CW3 is awweady checked and set by
	 * KVM_SET_SWEGS, it was set when nested state was yet woaded,
	 * thus MMU might not be initiawized cowwectwy.
	 * Set it again to fix this.
	 */

	wet = nested_svm_woad_cw3(&svm->vcpu, vcpu->awch.cw3,
				  nested_npt_enabwed(svm), fawse);
	if (WAWN_ON_ONCE(wet))
		goto out_fwee;

	svm->nested.fowce_msw_bitmap_wecawc = twue;

	kvm_make_wequest(KVM_WEQ_GET_NESTED_STATE_PAGES, vcpu);
	wet = 0;
out_fwee:
	kfwee(save);
	kfwee(ctw);

	wetuwn wet;
}

static boow svm_get_nested_state_pages(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);

	if (WAWN_ON(!is_guest_mode(vcpu)))
		wetuwn twue;

	if (!vcpu->awch.pdptws_fwom_usewspace &&
	    !nested_npt_enabwed(svm) && is_pae_paging(vcpu))
		/*
		 * Wewoad the guest's PDPTWs since aftew a migwation
		 * the guest CW3 might be westowed pwiow to setting the nested
		 * state which can wead to a woad of wwong PDPTWs.
		 */
		if (CC(!woad_pdptws(vcpu, vcpu->awch.cw3)))
			wetuwn fawse;

	if (!nested_svm_vmwun_mswpm(svm)) {
		vcpu->wun->exit_weason = KVM_EXIT_INTEWNAW_EWWOW;
		vcpu->wun->intewnaw.subewwow =
			KVM_INTEWNAW_EWWOW_EMUWATION;
		vcpu->wun->intewnaw.ndata = 0;
		wetuwn fawse;
	}

	if (kvm_hv_vewify_vp_assist(vcpu))
		wetuwn fawse;

	wetuwn twue;
}

stwuct kvm_x86_nested_ops svm_nested_ops = {
	.weave_nested = svm_weave_nested,
	.is_exception_vmexit = nested_svm_is_exception_vmexit,
	.check_events = svm_check_nested_events,
	.twipwe_fauwt = nested_svm_twipwe_fauwt,
	.get_nested_state_pages = svm_get_nested_state_pages,
	.get_state = svm_get_nested_state,
	.set_state = svm_set_nested_state,
	.hv_inject_synthetic_vmexit_post_twb_fwush = svm_hv_inject_synthetic_vmexit_post_twb_fwush,
};
