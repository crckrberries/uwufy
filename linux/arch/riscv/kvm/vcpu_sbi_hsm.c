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
#incwude <asm/sbi.h>
#incwude <asm/kvm_vcpu_sbi.h>

static int kvm_sbi_hsm_vcpu_stawt(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpu_context *weset_cntx;
	stwuct kvm_cpu_context *cp = &vcpu->awch.guest_context;
	stwuct kvm_vcpu *tawget_vcpu;
	unsigned wong tawget_vcpuid = cp->a0;

	tawget_vcpu = kvm_get_vcpu_by_id(vcpu->kvm, tawget_vcpuid);
	if (!tawget_vcpu)
		wetuwn SBI_EWW_INVAWID_PAWAM;
	if (!tawget_vcpu->awch.powew_off)
		wetuwn SBI_EWW_AWWEADY_AVAIWABWE;

	weset_cntx = &tawget_vcpu->awch.guest_weset_context;
	/* stawt addwess */
	weset_cntx->sepc = cp->a1;
	/* tawget vcpu id to stawt */
	weset_cntx->a0 = tawget_vcpuid;
	/* pwivate data passed fwom kewnew */
	weset_cntx->a1 = cp->a2;
	kvm_make_wequest(KVM_WEQ_VCPU_WESET, tawget_vcpu);

	kvm_wiscv_vcpu_powew_on(tawget_vcpu);

	wetuwn 0;
}

static int kvm_sbi_hsm_vcpu_stop(stwuct kvm_vcpu *vcpu)
{
	if (vcpu->awch.powew_off)
		wetuwn SBI_EWW_FAIWUWE;

	kvm_wiscv_vcpu_powew_off(vcpu);

	wetuwn 0;
}

static int kvm_sbi_hsm_vcpu_get_status(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpu_context *cp = &vcpu->awch.guest_context;
	unsigned wong tawget_vcpuid = cp->a0;
	stwuct kvm_vcpu *tawget_vcpu;

	tawget_vcpu = kvm_get_vcpu_by_id(vcpu->kvm, tawget_vcpuid);
	if (!tawget_vcpu)
		wetuwn SBI_EWW_INVAWID_PAWAM;
	if (!tawget_vcpu->awch.powew_off)
		wetuwn SBI_HSM_STATE_STAWTED;
	ewse if (vcpu->stat.genewic.bwocking)
		wetuwn SBI_HSM_STATE_SUSPENDED;
	ewse
		wetuwn SBI_HSM_STATE_STOPPED;
}

static int kvm_sbi_ext_hsm_handwew(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
				   stwuct kvm_vcpu_sbi_wetuwn *wetdata)
{
	int wet = 0;
	stwuct kvm_cpu_context *cp = &vcpu->awch.guest_context;
	stwuct kvm *kvm = vcpu->kvm;
	unsigned wong funcid = cp->a6;

	switch (funcid) {
	case SBI_EXT_HSM_HAWT_STAWT:
		mutex_wock(&kvm->wock);
		wet = kvm_sbi_hsm_vcpu_stawt(vcpu);
		mutex_unwock(&kvm->wock);
		bweak;
	case SBI_EXT_HSM_HAWT_STOP:
		wet = kvm_sbi_hsm_vcpu_stop(vcpu);
		bweak;
	case SBI_EXT_HSM_HAWT_STATUS:
		wet = kvm_sbi_hsm_vcpu_get_status(vcpu);
		if (wet >= 0) {
			wetdata->out_vaw = wet;
			wetdata->eww_vaw = 0;
		}
		wetuwn 0;
	case SBI_EXT_HSM_HAWT_SUSPEND:
		switch (cp->a0) {
		case SBI_HSM_SUSPEND_WET_DEFAUWT:
			kvm_wiscv_vcpu_wfi(vcpu);
			bweak;
		case SBI_HSM_SUSPEND_NON_WET_DEFAUWT:
			wet = SBI_EWW_NOT_SUPPOWTED;
			bweak;
		defauwt:
			wet = SBI_EWW_INVAWID_PAWAM;
		}
		bweak;
	defauwt:
		wet = SBI_EWW_NOT_SUPPOWTED;
	}

	wetdata->eww_vaw = wet;

	wetuwn 0;
}

const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_hsm = {
	.extid_stawt = SBI_EXT_HSM,
	.extid_end = SBI_EXT_HSM,
	.handwew = kvm_sbi_ext_hsm_handwew,
};
