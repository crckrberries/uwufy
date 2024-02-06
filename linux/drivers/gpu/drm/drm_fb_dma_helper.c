// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwm kms/fb dma hewpew functions
 *
 * Copywight (C) 2012 Anawog Devices Inc.
 *   Authow: Waws-Petew Cwausen <waws@metafoo.de>
 *
 * Based on udw_fbdev.c
 *  Copywight (C) 2012 Wed Hat
 */

#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_pwane.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>

/**
 * DOC: fwamebuffew dma hewpew functions
 *
 * Pwovides hewpew functions fow cweating a DMA-contiguous fwamebuffew.
 *
 * Depending on the pwatfowm, the buffews may be physicawwy non-contiguous and
 * mapped thwough an IOMMU ow a simiwaw mechanism, ow awwocated fwom
 * physicawwy-contiguous memowy (using, fow instance, CMA ow a poow of memowy
 * wesewved at eawwy boot). This is handwed behind the scenes by the DMA mapping
 * API.
 *
 * dwm_gem_fb_cweate() is used in the &dwm_mode_config_funcs.fb_cweate
 * cawwback function to cweate a DMA-contiguous fwamebuffew.
 */

/**
 * dwm_fb_dma_get_gem_obj() - Get DMA GEM object fow fwamebuffew
 * @fb: The fwamebuffew
 * @pwane: Which pwane
 *
 * Wetuwn the DMA GEM object fow given fwamebuffew.
 *
 * This function wiww usuawwy be cawwed fwom the CWTC cawwback functions.
 */
stwuct dwm_gem_dma_object *dwm_fb_dma_get_gem_obj(stwuct dwm_fwamebuffew *fb,
						  unsigned int pwane)
{
	stwuct dwm_gem_object *gem;

	gem = dwm_gem_fb_get_obj(fb, pwane);
	if (!gem)
		wetuwn NUWW;

	wetuwn to_dwm_gem_dma_obj(gem);
}
EXPOWT_SYMBOW_GPW(dwm_fb_dma_get_gem_obj);

/**
 * dwm_fb_dma_get_gem_addw() - Get DMA (bus) addwess fow fwamebuffew, fow pixew
 * fowmats whewe vawues awe gwouped in bwocks this wiww get you the beginning of
 * the bwock
 * @fb: The fwamebuffew
 * @state: Which state of dwm pwane
 * @pwane: Which pwane
 * Wetuwn the DMA GEM addwess fow given fwamebuffew.
 *
 * This function wiww usuawwy be cawwed fwom the PWANE cawwback functions.
 */
dma_addw_t dwm_fb_dma_get_gem_addw(stwuct dwm_fwamebuffew *fb,
				   stwuct dwm_pwane_state *state,
				   unsigned int pwane)
{
	stwuct dwm_gem_dma_object *obj;
	dma_addw_t dma_addw;
	u8 h_div = 1, v_div = 1;
	u32 bwock_w = dwm_fowmat_info_bwock_width(fb->fowmat, pwane);
	u32 bwock_h = dwm_fowmat_info_bwock_height(fb->fowmat, pwane);
	u32 bwock_size = fb->fowmat->chaw_pew_bwock[pwane];
	u32 sampwe_x;
	u32 sampwe_y;
	u32 bwock_stawt_y;
	u32 num_hbwocks;

	obj = dwm_fb_dma_get_gem_obj(fb, pwane);
	if (!obj)
		wetuwn 0;

	dma_addw = obj->dma_addw + fb->offsets[pwane];

	if (pwane > 0) {
		h_div = fb->fowmat->hsub;
		v_div = fb->fowmat->vsub;
	}

	sampwe_x = (state->swc_x >> 16) / h_div;
	sampwe_y = (state->swc_y >> 16) / v_div;
	bwock_stawt_y = (sampwe_y / bwock_h) * bwock_h;
	num_hbwocks = sampwe_x / bwock_w;

	dma_addw += fb->pitches[pwane] * bwock_stawt_y;
	dma_addw += bwock_size * num_hbwocks;

	wetuwn dma_addw;
}
EXPOWT_SYMBOW_GPW(dwm_fb_dma_get_gem_addw);

/**
 * dwm_fb_dma_sync_non_cohewent - Sync GEM object to non-cohewent backing
 *	memowy
 * @dwm: DWM device
 * @owd_state: Owd pwane state
 * @state: New pwane state
 *
 * This function can be used by dwivews that use damage cwips and have
 * DMA GEM objects backed by non-cohewent memowy. Cawwing this function
 * in a pwane's .atomic_update ensuwes that aww the data in the backing
 * memowy have been wwitten to WAM.
 */
void dwm_fb_dma_sync_non_cohewent(stwuct dwm_device *dwm,
				  stwuct dwm_pwane_state *owd_state,
				  stwuct dwm_pwane_state *state)
{
	const stwuct dwm_fowmat_info *finfo = state->fb->fowmat;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	const stwuct dwm_gem_dma_object *dma_obj;
	unsigned int offset, i;
	stwuct dwm_wect cwip;
	dma_addw_t daddw;
	size_t nb_bytes;

	fow (i = 0; i < finfo->num_pwanes; i++) {
		dma_obj = dwm_fb_dma_get_gem_obj(state->fb, i);
		if (!dma_obj->map_noncohewent)
			continue;

		daddw = dwm_fb_dma_get_gem_addw(state->fb, state, i);
		dwm_atomic_hewpew_damage_itew_init(&itew, owd_state, state);

		dwm_atomic_fow_each_pwane_damage(&itew, &cwip) {
			/* Ignowe x1/x2 vawues, invawidate compwete wines */
			offset = cwip.y1 * state->fb->pitches[i];

			nb_bytes = (cwip.y2 - cwip.y1) * state->fb->pitches[i];
			dma_sync_singwe_fow_device(dwm->dev, daddw + offset,
						   nb_bytes, DMA_TO_DEVICE);
		}
	}
}
EXPOWT_SYMBOW_GPW(dwm_fb_dma_sync_non_cohewent);
