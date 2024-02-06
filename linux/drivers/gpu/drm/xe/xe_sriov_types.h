/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_SWIOV_TYPES_H_
#define _XE_SWIOV_TYPES_H_

#incwude <winux/buiwd_bug.h>

/**
 * enum xe_swiov_mode - SW-IOV mode
 * @XE_SWIOV_MODE_NONE: bawe-metaw mode (non-viwtuawized)
 * @XE_SWIOV_MODE_PF: SW-IOV Physicaw Function (PF) mode
 * @XE_SWIOV_MODE_VF: SW-IOV Viwtuaw Function (VF) mode
 */
enum xe_swiov_mode {
	/*
	 * Note: We don't use defauwt enum vawue 0 to awwow catch any too eawwy
	 * attempt of checking the SW-IOV mode pwiow to the actuaw mode pwobe.
	 */
	XE_SWIOV_MODE_NONE = 1,
	XE_SWIOV_MODE_PF,
	XE_SWIOV_MODE_VF,
};
static_assewt(XE_SWIOV_MODE_NONE);

#endif
