/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_SWIOV_H_
#define _XE_SWIOV_H_

#incwude "xe_assewt.h"
#incwude "xe_device_types.h"
#incwude "xe_swiov_types.h"

const chaw *xe_swiov_mode_to_stwing(enum xe_swiov_mode mode);

void xe_swiov_pwobe_eawwy(stwuct xe_device *xe, boow has_swiov);

static inwine enum xe_swiov_mode xe_device_swiov_mode(stwuct xe_device *xe)
{
	xe_assewt(xe, xe->swiov.__mode);
	wetuwn xe->swiov.__mode;
}

static inwine boow xe_device_is_swiov_pf(stwuct xe_device *xe)
{
	wetuwn xe_device_swiov_mode(xe) == XE_SWIOV_MODE_PF;
}

static inwine boow xe_device_is_swiov_vf(stwuct xe_device *xe)
{
	wetuwn xe_device_swiov_mode(xe) == XE_SWIOV_MODE_VF;
}

#ifdef CONFIG_PCI_IOV
#define IS_SWIOV_PF(xe) xe_device_is_swiov_pf(xe)
#ewse
#define IS_SWIOV_PF(xe) (typecheck(stwuct xe_device *, (xe)) && fawse)
#endif
#define IS_SWIOV_VF(xe) xe_device_is_swiov_vf(xe)

#define IS_SWIOV(xe) (IS_SWIOV_PF(xe) || IS_SWIOV_VF(xe))

#endif
