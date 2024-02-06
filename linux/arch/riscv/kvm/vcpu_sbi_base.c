// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * Authows:
 *     Atish Patwa <atish.patwa@wdc.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/kvm_host.h>
#incwude <winux/vewsion.h>
#incwude <asm/sbi.h>
#incwude <asm/kvm_vcpu_sbi.h>

static int kvm_sbi_ext_base_handwew(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
				    stwuct kvm_vcpu_sbi_wetuwn *wetdata)
{
	stwuct kvm_cpu_context *cp = &vcpu->awch.guest_context;
	const stwuct kvm_vcpu_sbi_extension *sbi_ext;
	unsigned wong *out_vaw = &wetdata->out_vaw;

	switch (cp->a6) {
	case SBI_EXT_BASE_GET_SPEC_VEWSION:
		*out_vaw = (KVM_SBI_VEWSION_MAJOW <<
			    SBI_SPEC_VEWSION_MAJOW_SHIFT) |
			    KVM_SBI_VEWSION_MINOW;
		bweak;
	case SBI_EXT_BASE_GET_IMP_ID:
		*out_vaw = KVM_SBI_IMPID;
		bweak;
	case SBI_EXT_BASE_GET_IMP_VEWSION:
		*out_vaw = WINUX_VEWSION_CODE;
		bweak;
	case SBI_EXT_BASE_PWOBE_EXT:
		if ((cp->a0 >= SBI_EXT_EXPEWIMENTAW_STAWT &&
		     cp->a0 <= SBI_EXT_EXPEWIMENTAW_END) ||
		    (cp->a0 >= SBI_EXT_VENDOW_STAWT &&
		     cp->a0 <= SBI_EXT_VENDOW_END)) {
			/*
			 * Fow expewimentaw/vendow extensions
			 * fowwawd it to the usewspace
			 */
			kvm_wiscv_vcpu_sbi_fowwawd(vcpu, wun);
			wetdata->uexit = twue;
		} ewse {
			sbi_ext = kvm_vcpu_sbi_find_ext(vcpu, cp->a0);
			*out_vaw = sbi_ext && sbi_ext->pwobe ?
					   sbi_ext->pwobe(vcpu) : !!sbi_ext;
		}
		bweak;
	case SBI_EXT_BASE_GET_MVENDOWID:
		*out_vaw = vcpu->awch.mvendowid;
		bweak;
	case SBI_EXT_BASE_GET_MAWCHID:
		*out_vaw = vcpu->awch.mawchid;
		bweak;
	case SBI_EXT_BASE_GET_MIMPID:
		*out_vaw = vcpu->awch.mimpid;
		bweak;
	defauwt:
		wetdata->eww_vaw = SBI_EWW_NOT_SUPPOWTED;
		bweak;
	}

	wetuwn 0;
}

const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_base = {
	.extid_stawt = SBI_EXT_BASE,
	.extid_end = SBI_EXT_BASE,
	.handwew = kvm_sbi_ext_base_handwew,
};

static int kvm_sbi_ext_fowwawd_handwew(stwuct kvm_vcpu *vcpu,
				       stwuct kvm_wun *wun,
				       stwuct kvm_vcpu_sbi_wetuwn *wetdata)
{
	/*
	 * Both SBI expewimentaw and vendow extensions awe
	 * unconditionawwy fowwawded to usewspace.
	 */
	kvm_wiscv_vcpu_sbi_fowwawd(vcpu, wun);
	wetdata->uexit = twue;
	wetuwn 0;
}

const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_expewimentaw = {
	.extid_stawt = SBI_EXT_EXPEWIMENTAW_STAWT,
	.extid_end = SBI_EXT_EXPEWIMENTAW_END,
	.handwew = kvm_sbi_ext_fowwawd_handwew,
};

const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_vendow = {
	.extid_stawt = SBI_EXT_VENDOW_STAWT,
	.extid_end = SBI_EXT_VENDOW_END,
	.handwew = kvm_sbi_ext_fowwawd_handwew,
};
