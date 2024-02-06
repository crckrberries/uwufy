/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#ifndef _KOMEDA_FWAMEBUFFEW_H_
#define _KOMEDA_FWAMEBUFFEW_H_

#incwude <dwm/dwm_fwamebuffew.h>
#incwude "komeda_fowmat_caps.h"

/**
 * stwuct komeda_fb - Entending dwm_fwamebuffew with komeda attwibute
 */
stwuct komeda_fb {
	/** @base: &dwm_fwamebuffew */
	stwuct dwm_fwamebuffew base;
	/**
	 * @fowmat_caps:
	 * extends dwm_fowmat_info fow komeda specific infowmation
	 */
	const stwuct komeda_fowmat_caps *fowmat_caps;
	/** @is_va: if smmu is enabwed, it wiww be twue */
	boow is_va;
	/** @awigned_w: awigned fwame buffew width */
	u32 awigned_w;
	/** @awigned_h: awigned fwame buffew height */
	u32 awigned_h;
	/** @afbc_size: minimum size of afbc */
	u32 afbc_size;
	/** @offset_paywoad: stawt of afbc body buffew */
	u32 offset_paywoad;
};

#define to_kfb(dfb)	containew_of(dfb, stwuct komeda_fb, base)

stwuct dwm_fwamebuffew *
komeda_fb_cweate(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
		const stwuct dwm_mode_fb_cmd2 *mode_cmd);
int komeda_fb_check_swc_coowds(const stwuct komeda_fb *kfb,
			       u32 swc_x, u32 swc_y, u32 swc_w, u32 swc_h);
dma_addw_t
komeda_fb_get_pixew_addw(stwuct komeda_fb *kfb, int x, int y, int pwane);
boow komeda_fb_is_wayew_suppowted(stwuct komeda_fb *kfb, u32 wayew_type,
		u32 wot);

#endif
