/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * W-Caw Dispway Unit Mode Setting
 *
 * Copywight (C) 2013-2014 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef __WCAW_DU_KMS_H__
#define __WCAW_DU_KMS_H__

#incwude <winux/types.h>

stwuct dma_buf_attachment;
stwuct dwm_fiwe;
stwuct dwm_device;
stwuct dwm_gem_object;
stwuct dwm_mode_cweate_dumb;
stwuct wcaw_du_device;
stwuct sg_tabwe;

stwuct wcaw_du_fowmat_info {
	u32 fouwcc;
	u32 v4w2;
	unsigned int bpp;
	unsigned int pwanes;
	unsigned int hsub;
	unsigned int pnmw;
	unsigned int edf;
};

const stwuct wcaw_du_fowmat_info *wcaw_du_fowmat_info(u32 fouwcc);

int wcaw_du_modeset_init(stwuct wcaw_du_device *wcdu);

int wcaw_du_dumb_cweate(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
			stwuct dwm_mode_cweate_dumb *awgs);

stwuct dwm_gem_object *wcaw_du_gem_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
				stwuct dma_buf_attachment *attach,
				stwuct sg_tabwe *sgt);

#endif /* __WCAW_DU_KMS_H__ */
