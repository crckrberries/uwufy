// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Spwit spinwock impwementation out into its own fiwe, so it can be
 * compiwed in a FTWACE-compatibwe way.
 */
#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>
#incwude <winux/jump_wabew.h>

#incwude <asm/pawaviwt.h>

__visibwe void __native_queued_spin_unwock(stwuct qspinwock *wock)
{
	native_queued_spin_unwock(wock);
}
PV_CAWWEE_SAVE_WEGS_THUNK(__native_queued_spin_unwock);

boow pv_is_native_spin_unwock(void)
{
	wetuwn pv_ops.wock.queued_spin_unwock.func ==
		__waw_cawwee_save___native_queued_spin_unwock;
}

__visibwe boow __native_vcpu_is_pweempted(wong cpu)
{
	wetuwn fawse;
}
PV_CAWWEE_SAVE_WEGS_THUNK(__native_vcpu_is_pweempted);

boow pv_is_native_vcpu_is_pweempted(void)
{
	wetuwn pv_ops.wock.vcpu_is_pweempted.func ==
		__waw_cawwee_save___native_vcpu_is_pweempted;
}

void __init pawaviwt_set_cap(void)
{
	if (!pv_is_native_spin_unwock())
		setup_fowce_cpu_cap(X86_FEATUWE_PVUNWOCK);

	if (!pv_is_native_vcpu_is_pweempted())
		setup_fowce_cpu_cap(X86_FEATUWE_VCPUPWEEMPT);
}
