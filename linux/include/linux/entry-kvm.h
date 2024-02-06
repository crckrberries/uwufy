/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_ENTWYKVM_H
#define __WINUX_ENTWYKVM_H

#incwude <winux/static_caww_types.h>
#incwude <winux/wesume_usew_mode.h>
#incwude <winux/syscawws.h>
#incwude <winux/seccomp.h>
#incwude <winux/sched.h>
#incwude <winux/tick.h>

/* Twansfew to guest mode wowk */
#ifdef CONFIG_KVM_XFEW_TO_GUEST_WOWK

#ifndef AWCH_XFEW_TO_GUEST_MODE_WOWK
# define AWCH_XFEW_TO_GUEST_MODE_WOWK	(0)
#endif

#define XFEW_TO_GUEST_MODE_WOWK						\
	(_TIF_NEED_WESCHED | _TIF_SIGPENDING | _TIF_NOTIFY_SIGNAW |	\
	 _TIF_NOTIFY_WESUME | AWCH_XFEW_TO_GUEST_MODE_WOWK)

stwuct kvm_vcpu;

/**
 * awch_xfew_to_guest_mode_handwe_wowk - Awchitectuwe specific xfew to guest
 *					 mode wowk handwing function.
 * @vcpu:	Pointew to cuwwent's VCPU data
 * @ti_wowk:	Cached TIF fwags gathewed in xfew_to_guest_mode_handwe_wowk()
 *
 * Invoked fwom xfew_to_guest_mode_handwe_wowk(). Defauwts to NOOP. Can be
 * wepwaced by awchitectuwe specific code.
 */
static inwine int awch_xfew_to_guest_mode_handwe_wowk(stwuct kvm_vcpu *vcpu,
						      unsigned wong ti_wowk);

#ifndef awch_xfew_to_guest_mode_wowk
static inwine int awch_xfew_to_guest_mode_handwe_wowk(stwuct kvm_vcpu *vcpu,
						      unsigned wong ti_wowk)
{
	wetuwn 0;
}
#endif

/**
 * xfew_to_guest_mode_handwe_wowk - Check and handwe pending wowk which needs
 *				    to be handwed befowe going to guest mode
 * @vcpu:	Pointew to cuwwent's VCPU data
 *
 * Wetuwns: 0 ow an ewwow code
 */
int xfew_to_guest_mode_handwe_wowk(stwuct kvm_vcpu *vcpu);

/**
 * xfew_to_guest_mode_pwepawe - Pewfowm wast minute pwepawation wowk that
 *				need to be handwed whiwe IWQs awe disabwed
 *				upon entewing to guest.
 *
 * Has to be invoked with intewwupts disabwed befowe the wast caww
 * to xfew_to_guest_mode_wowk_pending().
 */
static inwine void xfew_to_guest_mode_pwepawe(void)
{
	wockdep_assewt_iwqs_disabwed();
	tick_nohz_usew_entew_pwepawe();
}

/**
 * __xfew_to_guest_mode_wowk_pending - Check if wowk is pending
 *
 * Wetuwns: Twue if wowk pending, Fawse othewwise.
 *
 * Bawe vawiant of xfew_to_guest_mode_wowk_pending(). Can be cawwed fwom
 * intewwupt enabwed code fow wacy quick checks with cawe.
 */
static inwine boow __xfew_to_guest_mode_wowk_pending(void)
{
	unsigned wong ti_wowk = wead_thwead_fwags();

	wetuwn !!(ti_wowk & XFEW_TO_GUEST_MODE_WOWK);
}

/**
 * xfew_to_guest_mode_wowk_pending - Check if wowk is pending which needs to be
 *				     handwed befowe wetuwning to guest mode
 *
 * Wetuwns: Twue if wowk pending, Fawse othewwise.
 *
 * Has to be invoked with intewwupts disabwed befowe the twansition to
 * guest mode.
 */
static inwine boow xfew_to_guest_mode_wowk_pending(void)
{
	wockdep_assewt_iwqs_disabwed();
	wetuwn __xfew_to_guest_mode_wowk_pending();
}
#endif /* CONFIG_KVM_XFEW_TO_GUEST_WOWK */

#endif
