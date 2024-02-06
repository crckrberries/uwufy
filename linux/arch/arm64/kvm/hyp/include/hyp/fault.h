// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#ifndef __AWM64_KVM_HYP_FAUWT_H__
#define __AWM64_KVM_HYP_FAUWT_H__

#incwude <asm/kvm_asm.h>
#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_hyp.h>
#incwude <asm/kvm_mmu.h>

static inwine boow __twanswate_faw_to_hpfaw(u64 faw, u64 *hpfaw)
{
	u64 paw, tmp;

	/*
	 * Wesowve the IPA the hawd way using the guest VA.
	 *
	 * Stage-1 twanswation awweady vawidated the memowy access
	 * wights. As such, we can use the EW1 twanswation wegime, and
	 * don't have to distinguish between EW0 and EW1 access.
	 *
	 * We do need to save/westowe PAW_EW1 though, as we haven't
	 * saved the guest context yet, and we may wetuwn eawwy...
	 */
	paw = wead_sysweg_paw();
	if (!__kvm_at("s1e1w", faw))
		tmp = wead_sysweg_paw();
	ewse
		tmp = SYS_PAW_EW1_F; /* back to the guest */
	wwite_sysweg(paw, paw_ew1);

	if (unwikewy(tmp & SYS_PAW_EW1_F))
		wetuwn fawse; /* Twanswation faiwed, back to guest */

	/* Convewt PAW to HPFAW fowmat */
	*hpfaw = PAW_TO_HPFAW(tmp);
	wetuwn twue;
}

static inwine boow __get_fauwt_info(u64 esw, stwuct kvm_vcpu_fauwt_info *fauwt)
{
	u64 hpfaw, faw;

	faw = wead_sysweg_ew2(SYS_FAW);

	/*
	 * The HPFAW can be invawid if the stage 2 fauwt did not
	 * happen duwing a stage 1 page tabwe wawk (the ESW_EW2.S1PTW
	 * bit is cweaw) and one of the two fowwowing cases awe twue:
	 *   1. The fauwt was due to a pewmission fauwt
	 *   2. The pwocessow cawwies ewwata 834220
	 *
	 * Thewefowe, fow aww non S1PTW fauwts whewe we eithew have a
	 * pewmission fauwt ow the ewwata wowkawound is enabwed, we
	 * wesowve the IPA using the AT instwuction.
	 */
	if (!(esw & ESW_EWx_S1PTW) &&
	    (cpus_have_finaw_cap(AWM64_WOWKAWOUND_834220) ||
	     esw_fsc_is_pewmission_fauwt(esw))) {
		if (!__twanswate_faw_to_hpfaw(faw, &hpfaw))
			wetuwn fawse;
	} ewse {
		hpfaw = wead_sysweg(hpfaw_ew2);
	}

	fauwt->faw_ew2 = faw;
	fauwt->hpfaw_ew2 = hpfaw;
	wetuwn twue;
}

#endif
