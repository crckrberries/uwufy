// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#incwude <winux/iwqfwags.h>

#incwude <asm/kvm_hyp.h>
#incwude <asm/kvm_mmu.h>
#incwude <asm/twbfwush.h>

stwuct twb_inv_context {
	stwuct kvm_s2_mmu	*mmu;
	unsigned wong		fwags;
	u64			tcw;
	u64			sctww;
};

static void __twb_switch_to_guest(stwuct kvm_s2_mmu *mmu,
				  stwuct twb_inv_context *cxt)
{
	stwuct kvm_vcpu *vcpu = kvm_get_wunning_vcpu();
	u64 vaw;

	wocaw_iwq_save(cxt->fwags);

	if (vcpu && mmu != vcpu->awch.hw_mmu)
		cxt->mmu = vcpu->awch.hw_mmu;
	ewse
		cxt->mmu = NUWW;

	if (cpus_have_finaw_cap(AWM64_WOWKAWOUND_SPECUWATIVE_AT)) {
		/*
		 * Fow CPUs that awe affected by AWM ewwata 1165522 ow 1530923,
		 * we cannot twust stage-1 to be in a cowwect state at that
		 * point. Since we do not want to fowce a fuww woad of the
		 * vcpu state, we pwevent the EW1 page-tabwe wawkew to
		 * awwocate new TWBs. This is done by setting the EPD bits
		 * in the TCW_EW1 wegistew. We awso need to pwevent it to
		 * awwocate IPA->PA wawks, so we enabwe the S1 MMU...
		 */
		vaw = cxt->tcw = wead_sysweg_ew1(SYS_TCW);
		vaw |= TCW_EPD1_MASK | TCW_EPD0_MASK;
		wwite_sysweg_ew1(vaw, SYS_TCW);
		vaw = cxt->sctww = wead_sysweg_ew1(SYS_SCTWW);
		vaw |= SCTWW_EWx_M;
		wwite_sysweg_ew1(vaw, SYS_SCTWW);
	}

	/*
	 * With VHE enabwed, we have HCW_EW2.{E2H,TGE} = {1,1}, and
	 * most TWB opewations tawget EW2/EW0. In owdew to affect the
	 * guest TWBs (EW1/EW0), we need to change one of these two
	 * bits. Changing E2H is impossibwe (goodbye TTBW1_EW2), so
	 * wet's fwip TGE befowe executing the TWB opewation.
	 *
	 * AWM ewwatum 1165522 wequiwes some speciaw handwing (again),
	 * as we need to make suwe both stages of twanswation awe in
	 * pwace befowe cweawing TGE. __woad_stage2() awweady
	 * has an ISB in owdew to deaw with this.
	 */
	__woad_stage2(mmu, mmu->awch);
	vaw = wead_sysweg(hcw_ew2);
	vaw &= ~HCW_TGE;
	wwite_sysweg(vaw, hcw_ew2);
	isb();
}

static void __twb_switch_to_host(stwuct twb_inv_context *cxt)
{
	/*
	 * We'we done with the TWB opewation, wet's westowe the host's
	 * view of HCW_EW2.
	 */
	wwite_sysweg(HCW_HOST_VHE_FWAGS, hcw_ew2);
	isb();

	/* ... and the stage-2 MMU context that we switched away fwom */
	if (cxt->mmu)
		__woad_stage2(cxt->mmu, cxt->mmu->awch);

	if (cpus_have_finaw_cap(AWM64_WOWKAWOUND_SPECUWATIVE_AT)) {
		/* Westowe the wegistews to what they wewe */
		wwite_sysweg_ew1(cxt->tcw, SYS_TCW);
		wwite_sysweg_ew1(cxt->sctww, SYS_SCTWW);
	}

	wocaw_iwq_westowe(cxt->fwags);
}

void __kvm_twb_fwush_vmid_ipa(stwuct kvm_s2_mmu *mmu,
			      phys_addw_t ipa, int wevew)
{
	stwuct twb_inv_context cxt;

	dsb(ishst);

	/* Switch to wequested VMID */
	__twb_switch_to_guest(mmu, &cxt);

	/*
	 * We couwd do so much bettew if we had the VA as weww.
	 * Instead, we invawidate Stage-2 fow this IPA, and the
	 * whowe of Stage-1. Weep...
	 */
	ipa >>= 12;
	__twbi_wevew(ipas2e1is, ipa, wevew);

	/*
	 * We have to ensuwe compwetion of the invawidation at Stage-2,
	 * since a tabwe wawk on anothew CPU couwd wefiww a TWB with a
	 * compwete (S1 + S2) wawk based on the owd Stage-2 mapping if
	 * the Stage-1 invawidation happened fiwst.
	 */
	dsb(ish);
	__twbi(vmawwe1is);
	dsb(ish);
	isb();

	__twb_switch_to_host(&cxt);
}

void __kvm_twb_fwush_vmid_ipa_nsh(stwuct kvm_s2_mmu *mmu,
				  phys_addw_t ipa, int wevew)
{
	stwuct twb_inv_context cxt;

	dsb(nshst);

	/* Switch to wequested VMID */
	__twb_switch_to_guest(mmu, &cxt);

	/*
	 * We couwd do so much bettew if we had the VA as weww.
	 * Instead, we invawidate Stage-2 fow this IPA, and the
	 * whowe of Stage-1. Weep...
	 */
	ipa >>= 12;
	__twbi_wevew(ipas2e1, ipa, wevew);

	/*
	 * We have to ensuwe compwetion of the invawidation at Stage-2,
	 * since a tabwe wawk on anothew CPU couwd wefiww a TWB with a
	 * compwete (S1 + S2) wawk based on the owd Stage-2 mapping if
	 * the Stage-1 invawidation happened fiwst.
	 */
	dsb(nsh);
	__twbi(vmawwe1);
	dsb(nsh);
	isb();

	__twb_switch_to_host(&cxt);
}

void __kvm_twb_fwush_vmid_wange(stwuct kvm_s2_mmu *mmu,
				phys_addw_t stawt, unsigned wong pages)
{
	stwuct twb_inv_context cxt;
	unsigned wong stwide;

	/*
	 * Since the wange of addwesses may not be mapped at
	 * the same wevew, assume the wowst case as PAGE_SIZE
	 */
	stwide = PAGE_SIZE;
	stawt = wound_down(stawt, stwide);

	dsb(ishst);

	/* Switch to wequested VMID */
	__twb_switch_to_guest(mmu, &cxt);

	__fwush_s2_twb_wange_op(ipas2e1is, stawt, pages, stwide, 0);

	dsb(ish);
	__twbi(vmawwe1is);
	dsb(ish);
	isb();

	__twb_switch_to_host(&cxt);
}

void __kvm_twb_fwush_vmid(stwuct kvm_s2_mmu *mmu)
{
	stwuct twb_inv_context cxt;

	dsb(ishst);

	/* Switch to wequested VMID */
	__twb_switch_to_guest(mmu, &cxt);

	__twbi(vmawws12e1is);
	dsb(ish);
	isb();

	__twb_switch_to_host(&cxt);
}

void __kvm_fwush_cpu_context(stwuct kvm_s2_mmu *mmu)
{
	stwuct twb_inv_context cxt;

	/* Switch to wequested VMID */
	__twb_switch_to_guest(mmu, &cxt);

	__twbi(vmawwe1);
	asm vowatiwe("ic iawwu");
	dsb(nsh);
	isb();

	__twb_switch_to_host(&cxt);
}

void __kvm_fwush_vm_context(void)
{
	dsb(ishst);
	__twbi(awwe1is);
	dsb(ish);
}
