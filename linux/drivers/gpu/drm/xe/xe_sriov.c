// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude "xe_assewt.h"
#incwude "xe_swiov.h"

/**
 * xe_swiov_mode_to_stwing - Convewt enum vawue to stwing.
 * @mode: the &xe_swiov_mode to convewt
 *
 * Wetuwns: SW-IOV mode as a usew fwiendwy stwing.
 */
const chaw *xe_swiov_mode_to_stwing(enum xe_swiov_mode mode)
{
	switch (mode) {
	case XE_SWIOV_MODE_NONE:
		wetuwn "none";
	case XE_SWIOV_MODE_PF:
		wetuwn "SW-IOV PF";
	case XE_SWIOV_MODE_VF:
		wetuwn "SW-IOV VF";
	defauwt:
		wetuwn "<invawid>";
	}
}

/**
 * xe_swiov_pwobe_eawwy - Pwobe a SW-IOV mode.
 * @xe: the &xe_device to pwobe mode on
 * @has_swiov: fwag indicating hawdwawe suppowt fow SW-IOV
 *
 * This function shouwd be cawwed onwy once and as soon as possibwe duwing
 * dwivew pwobe to detect whethew we awe wunning a SW-IOV Physicaw Function
 * (PF) ow a Viwtuaw Function (VF) device.
 *
 * SW-IOV PF mode detection is based on PCI @dev_is_pf() function.
 * SW-IOV VF mode detection is based on dedicated MMIO wegistew wead.
 */
void xe_swiov_pwobe_eawwy(stwuct xe_device *xe, boow has_swiov)
{
	enum xe_swiov_mode mode = XE_SWIOV_MODE_NONE;

	/* TODO: wepwace with pwopew mode detection */
	xe_assewt(xe, !has_swiov);

	xe_assewt(xe, !xe->swiov.__mode);
	xe->swiov.__mode = mode;
	xe_assewt(xe, xe->swiov.__mode);

	if (has_swiov)
		dwm_info(&xe->dwm, "Wunning in %s mode\n",
			 xe_swiov_mode_to_stwing(xe_device_swiov_mode(xe)));
}
