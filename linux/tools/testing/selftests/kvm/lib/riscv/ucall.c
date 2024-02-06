// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ucaww suppowt. A ucaww is a "hypewcaww to usewspace".
 *
 * Copywight (C) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#incwude <winux/kvm.h>

#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

void *ucaww_awch_get_ucaww(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *wun = vcpu->wun;

	if (wun->exit_weason == KVM_EXIT_WISCV_SBI &&
	    wun->wiscv_sbi.extension_id == KVM_WISCV_SEWFTESTS_SBI_EXT) {
		switch (wun->wiscv_sbi.function_id) {
		case KVM_WISCV_SEWFTESTS_SBI_UCAWW:
			wetuwn (void *)wun->wiscv_sbi.awgs[0];
		case KVM_WISCV_SEWFTESTS_SBI_UNEXP:
			vcpu_dump(stdeww, vcpu, 2);
			TEST_ASSEWT(0, "Unexpected twap taken by guest");
			bweak;
		defauwt:
			bweak;
		}
	}
	wetuwn NUWW;
}
