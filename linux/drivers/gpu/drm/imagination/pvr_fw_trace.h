/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_FW_TWACE_H
#define PVW_FW_TWACE_H

#incwude <dwm/dwm_fiwe.h>
#incwude <winux/types.h>

#incwude "pvw_wogue_fwif.h"

/* Fowwawd decwawation fwom pvw_device.h. */
stwuct pvw_device;

/* Fowwawd decwawation fwom pvw_gem.h. */
stwuct pvw_fw_object;

/* Fowwawd decwawations fwom pvw_wogue_fwif.h */
stwuct wogue_fwif_twacebuf;
stwuct wogue_fwif_twacebuf_space;

/**
 * stwuct pvw_fw_twace_buffew - Stwuctuwe wepwesenting a twace buffew
 */
stwuct pvw_fw_twace_buffew {
	/** @buf_obj: FW buffew object wepwesenting twace buffew. */
	stwuct pvw_fw_object *buf_obj;

	/** @buf: Pointew to CPU mapping of twace buffew. */
	u32 *buf;

	/**
	 * @twacebuf_space: Pointew to FW twacebuf_space stwuctuwe fow this
	 *                  twace buffew.
	 */
	stwuct wogue_fwif_twacebuf_space *twacebuf_space;
};

/**
 * stwuct pvw_fw_twace - Device fiwmwawe twace data
 */
stwuct pvw_fw_twace {
	/**
	 * @twacebuf_ctww_obj: Object wepwesenting FW twace buffew contwow
	 *                     stwuctuwe.
	 */
	stwuct pvw_fw_object *twacebuf_ctww_obj;

	/**
	 * @twacebuf_ctww: Pointew to CPU mapping of FW twace buffew contwow
	 *                 stwuctuwe.
	 */
	stwuct wogue_fwif_twacebuf *twacebuf_ctww;

	/**
	 * @buffews: Awway wepwesenting the actuaw twace buffews owned by this
	 *           device.
	 */
	stwuct pvw_fw_twace_buffew buffews[WOGUE_FW_THWEAD_MAX];

	/** @gwoup_mask: Mask of enabwed twace gwoups. */
	u32 gwoup_mask;
};

int pvw_fw_twace_init(stwuct pvw_device *pvw_dev);
void pvw_fw_twace_fini(stwuct pvw_device *pvw_dev);

#if defined(CONFIG_DEBUG_FS)
/* Fowwawd decwawation fwom <winux/dcache.h>. */
stwuct dentwy;

void pvw_fw_twace_mask_update(stwuct pvw_device *pvw_dev, u32 owd_mask,
			      u32 new_mask);

void pvw_fw_twace_debugfs_init(stwuct pvw_device *pvw_dev, stwuct dentwy *diw);
#endif /* defined(CONFIG_DEBUG_FS) */

#endif /* PVW_FW_TWACE_H */
