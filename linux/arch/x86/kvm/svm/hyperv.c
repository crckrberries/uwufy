// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD SVM specific code fow Hypew-V on KVM.
 *
 * Copywight 2022 Wed Hat, Inc. and/ow its affiwiates.
 */
#incwude "hypewv.h"

void svm_hv_inject_synthetic_vmexit_post_twb_fwush(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);

	svm->vmcb->contwow.exit_code = HV_SVM_EXITCODE_ENW;
	svm->vmcb->contwow.exit_code_hi = 0;
	svm->vmcb->contwow.exit_info_1 = HV_SVM_ENW_EXITCODE_TWAP_AFTEW_FWUSH;
	svm->vmcb->contwow.exit_info_2 = 0;
	nested_svm_vmexit(svm);
}
