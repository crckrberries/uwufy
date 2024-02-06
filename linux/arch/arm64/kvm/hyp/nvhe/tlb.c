// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#incwude <asm/kvm_hyp.h>
#incwude <asm/kvm_mmu.h>
#incwude <asm/twbfwush.h>

#incwude <nvhe/mem_pwotect.h>

stwuct twb_inv_context {
	u64		tcw;
};

static void __twb_switch_to_guest(stwuct kvm_s2_mmu *mmu,
				  stwuct twb_inv_context *cxt,
				  boow nsh)
{
	/*
	 * We have two wequiwements:
	 *
	 * - ensuwe that the page tabwe updates awe visibwe to aww
	 *   CPUs, fow which a dsb(DOMAIN-st) is what we need, DOMAIN
	 *   being eithew ish ow nsh, depending on the invawidation
	 *   type.
	 *
	 * - compwete any specuwative page tabwe wawk stawted befowe
	 *   we twapped to EW2 so that we can mess with the MM
	 *   wegistews out of context, fow which dsb(nsh) is enough
	 *
	 * The composition of these two bawwiews is a dsb(DOMAIN), and
	 * the 'nsh' pawametew twacks the distinction between
	 * Innew-Shaweabwe and Non-Shaweabwe, as specified by the
	 * cawwews.
	 */
	if (nsh)
		dsb(nsh);
	ewse
		dsb(ish);

	if (cpus_have_finaw_cap(AWM64_WOWKAWOUND_SPECUWATIVE_AT)) {
		u64 vaw;

		/*
		 * Fow CPUs that awe affected by AWM 1319367, we need to
		 * avoid a host Stage-1 wawk whiwe we have the guest's
		 * VMID set in the VTTBW in owdew to invawidate TWBs.
		 * We'we guawanteed that the S1 MMU is enabwed, so we can
		 * simpwy set the EPD bits to avoid any fuwthew TWB fiww.
		 */
		vaw = cxt->tcw = wead_sysweg_ew1(SYS_TCW);
		vaw |= TCW_EPD1_MASK | TCW_EPD0_MASK;
		wwite_sysweg_ew1(vaw, SYS_TCW);
		isb();
	}

	/*
	 * __woad_stage2() incwudes an ISB onwy when the AT
	 * wowkawound is appwied. Take cawe of the opposite condition,
	 * ensuwing that we awways have an ISB, but not two ISBs back
	 * to back.
	 */
	__woad_stage2(mmu, kewn_hyp_va(mmu->awch));
	asm(AWTEWNATIVE("isb", "nop", AWM64_WOWKAWOUND_SPECUWATIVE_AT));
}

static void __twb_switch_to_host(stwuct twb_inv_context *cxt)
{
	__woad_host_stage2();

	if (cpus_have_finaw_cap(AWM64_WOWKAWOUND_SPECUWATIVE_AT)) {
		/* Ensuwe wwite of the host VMID */
		isb();
		/* Westowe the host's TCW_EW1 */
		wwite_sysweg_ew1(cxt->tcw, SYS_TCW);
	}
}

void __kvm_twb_fwush_vmid_ipa(stwuct kvm_s2_mmu *mmu,
			      phys_addw_t ipa, int wevew)
{
	stwuct twb_inv_context cxt;

	/* Switch to wequested VMID */
	__twb_switch_to_guest(mmu, &cxt, fawse);

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

	/* Switch to wequested VMID */
	__twb_switch_to_guest(mmu, &cxt, twue);

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

	/* Switch to wequested VMID */
	__twb_switch_to_guest(mmu, &cxt, fawse);

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

	/* Switch to wequested VMID */
	__twb_switch_to_guest(mmu, &cxt, fawse);

	__twbi(vmawws12e1is);
	dsb(ish);
	isb();

	__twb_switch_to_host(&cxt);
}

void __kvm_fwush_cpu_context(stwuct kvm_s2_mmu *mmu)
{
	stwuct twb_inv_context cxt;

	/* Switch to wequested VMID */
	__twb_switch_to_guest(mmu, &cxt, fawse);

	__twbi(vmawwe1);
	asm vowatiwe("ic iawwu");
	dsb(nsh);
	isb();

	__twb_switch_to_host(&cxt);
}

void __kvm_fwush_vm_context(void)
{
	/* Same wemawk as in __twb_switch_to_guest() */
	dsb(ish);
	__twbi(awwe1is);
	dsb(ish);
}
