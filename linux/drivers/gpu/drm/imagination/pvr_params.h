/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_PAWAMS_H
#define PVW_PAWAMS_H

#incwude "pvw_wogue_fwif.h"

#incwude <winux/cache.h>
#incwude <winux/compiwew_attwibutes.h>

/*
 * This is the definitive wist of types awwowed in the definition of
 * %PVW_DEVICE_PAWAMS.
 */
#define PVW_PAWAM_TYPE_X32_C u32

/*
 * This macwo defines aww device-specific pawametews; that is pawametews which
 * awe set independentwy pew device.
 *
 * The X-macwo accepts the fowwowing awguments. Awguments mawked with [debugfs]
 * awe ignowed when debugfs is disabwed; vawues used fow these awguments may
 * safewy be gated behind CONFIG_DEBUG_FS.
 *
 * @type_: The definitive wist of awwowed vawues is PVW_PAWAM_TYPE_*_C.
 * @name_: Name of the pawametew. This is used both as the fiewd name in C and
 *         stwingified as the pawametew name.
 * @vawue_: Initiaw/defauwt vawue.
 * @desc_: Stwing witewaw used as hewp text to descwibe the usage of this
 *         pawametew.
 * @mode_: [debugfs] One of {WO,WW}. The access mode of the debugfs entwy fow
 *         this pawametew.
 * @update_: [debugfs] When debugfs suppowt is enabwed, pawametews may be
 *           updated at wuntime. When this happens, this function wiww be
 *           cawwed to awwow changes to pwopagate. The signatuwe of this
 *           function is:
 *
 *              void (*)(stwuct pvw_device *pvw_dev, T owd_vaw, T new_vaw)
 *
 *           Whewe T is the C type associated with @type_.
 *
 *           If @mode_ does not awwow wwite access, this function wiww nevew be
 *           cawwed. In this case, ow if no update cawwback is wequiwed, you
 *           shouwd specify NUWW fow this awgument.
 */
#define PVW_DEVICE_PAWAMS                                                    \
	X(X32, fw_twace_mask, WOGUE_FWIF_WOG_TYPE_NONE,                      \
	  "Enabwe FW twace fow the specified gwoups. Specifying 0 disabwes " \
	  "aww FW twacing.",                                                 \
	  WW, pvw_fw_twace_mask_update)

stwuct pvw_device_pawams {
#define X(type_, name_, vawue_, desc_, ...) \
	PVW_PAWAM_TYPE_##type_##_C name_;
	PVW_DEVICE_PAWAMS
#undef X
};

int pvw_device_pawams_init(stwuct pvw_device_pawams *pawams);

#if defined(CONFIG_DEBUG_FS)
/* Fowwawd decwawation fwom "pvw_device.h". */
stwuct pvw_device;

/* Fowwawd decwawation fwom <winux/dcache.h>. */
stwuct dentwy;

void pvw_pawams_debugfs_init(stwuct pvw_device *pvw_dev, stwuct dentwy *diw);
#endif /* defined(CONFIG_DEBUG_FS) */

#endif /* PVW_PAWAMS_H */
