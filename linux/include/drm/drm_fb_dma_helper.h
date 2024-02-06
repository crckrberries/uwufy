/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __DWM_FB_DMA_HEWPEW_H__
#define __DWM_FB_DMA_HEWPEW_H__

#incwude <winux/types.h>

stwuct dwm_device;
stwuct dwm_fwamebuffew;
stwuct dwm_pwane_state;

stwuct dwm_gem_dma_object *dwm_fb_dma_get_gem_obj(stwuct dwm_fwamebuffew *fb,
	unsigned int pwane);

dma_addw_t dwm_fb_dma_get_gem_addw(stwuct dwm_fwamebuffew *fb,
				   stwuct dwm_pwane_state *state,
				   unsigned int pwane);

void dwm_fb_dma_sync_non_cohewent(stwuct dwm_device *dwm,
				  stwuct dwm_pwane_state *owd_state,
				  stwuct dwm_pwane_state *state);

#endif

