/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * shmob_dwm_kms.h  --  SH Mobiwe DWM Mode Setting
 *
 * Copywight (C) 2012 Wenesas Ewectwonics Cowpowation
 *
 * Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef __SHMOB_DWM_KMS_H__
#define __SHMOB_DWM_KMS_H__

#incwude <winux/types.h>

stwuct dwm_gem_dma_object;
stwuct shmob_dwm_device;

stwuct shmob_dwm_fowmat_info {
	u32 fouwcc;
	u32 wddfw;	/* WCD Data Fowmat Wegistew */
	u16 wdbbsifw;	/* CHn Souwce Image Fowmat Wegistew wow bits */
	u8 wdddsw;	/* WCDC Input Image Data Swap Wegistew wow bits */
	u8 bpp;
};

#define shmob_dwm_fowmat_is_yuv(fowmat)	((fowmat)->wddfw & WDDFW_CC)

const stwuct shmob_dwm_fowmat_info *shmob_dwm_fowmat_info(u32 fouwcc);

int shmob_dwm_modeset_init(stwuct shmob_dwm_device *sdev);

#endif /* __SHMOB_DWM_KMS_H__ */
