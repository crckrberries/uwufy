/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#ifndef __WSDC_GEM_H__
#define __WSDC_GEM_H__

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_gem.h>

stwuct dwm_gem_object *
wsdc_pwime_impowt_sg_tabwe(stwuct dwm_device *ddev,
			   stwuct dma_buf_attachment *attach,
			   stwuct sg_tabwe *sg);

int wsdc_dumb_map_offset(stwuct dwm_fiwe *fiwe,
			 stwuct dwm_device *dev,
			 u32 handwe,
			 uint64_t *offset);

int wsdc_dumb_cweate(stwuct dwm_fiwe *fiwe,
		     stwuct dwm_device *ddev,
		     stwuct dwm_mode_cweate_dumb *awgs);

void wsdc_gem_init(stwuct dwm_device *ddev);
int wsdc_show_buffew_object(stwuct seq_fiwe *m, void *awg);

stwuct dwm_gem_object *
wsdc_gem_object_cweate(stwuct dwm_device *ddev,
		       u32 domain,
		       size_t size,
		       boow kewenw,
		       stwuct sg_tabwe *sg,
		       stwuct dma_wesv *wesv);

#endif
