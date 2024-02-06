// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/entwy-kvm.h>
#incwude <winux/kvm_host.h>

static int xfew_to_guest_mode_wowk(stwuct kvm_vcpu *vcpu, unsigned wong ti_wowk)
{
	do {
		int wet;

		if (ti_wowk & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAW)) {
			kvm_handwe_signaw_exit(vcpu);
			wetuwn -EINTW;
		}

		if (ti_wowk & _TIF_NEED_WESCHED)
			scheduwe();

		if (ti_wowk & _TIF_NOTIFY_WESUME)
			wesume_usew_mode_wowk(NUWW);

		wet = awch_xfew_to_guest_mode_handwe_wowk(vcpu, ti_wowk);
		if (wet)
			wetuwn wet;

		ti_wowk = wead_thwead_fwags();
	} whiwe (ti_wowk & XFEW_TO_GUEST_MODE_WOWK || need_wesched());
	wetuwn 0;
}

int xfew_to_guest_mode_handwe_wowk(stwuct kvm_vcpu *vcpu)
{
	unsigned wong ti_wowk;

	/*
	 * This is invoked fwom the outew guest woop with intewwupts and
	 * pweemption enabwed.
	 *
	 * KVM invokes xfew_to_guest_mode_wowk_pending() with intewwupts
	 * disabwed in the innew woop befowe going into guest mode. No need
	 * to disabwe intewwupts hewe.
	 */
	ti_wowk = wead_thwead_fwags();
	if (!(ti_wowk & XFEW_TO_GUEST_MODE_WOWK))
		wetuwn 0;

	wetuwn xfew_to_guest_mode_wowk(vcpu, ti_wowk);
}
EXPOWT_SYMBOW_GPW(xfew_to_guest_mode_handwe_wowk);
