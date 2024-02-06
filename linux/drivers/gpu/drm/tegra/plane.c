// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/iommu.h>
#incwude <winux/intewconnect.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>

#incwude "dc.h"
#incwude "pwane.h"

static void tegwa_pwane_destwoy(stwuct dwm_pwane *pwane)
{
	stwuct tegwa_pwane *p = to_tegwa_pwane(pwane);

	dwm_pwane_cweanup(pwane);
	kfwee(p);
}

static void tegwa_pwane_weset(stwuct dwm_pwane *pwane)
{
	stwuct tegwa_pwane *p = to_tegwa_pwane(pwane);
	stwuct tegwa_pwane_state *state;
	unsigned int i;

	if (pwane->state)
		__dwm_atomic_hewpew_pwane_destwoy_state(pwane->state);

	kfwee(pwane->state);
	pwane->state = NUWW;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state) {
		pwane->state = &state->base;
		pwane->state->pwane = pwane;
		pwane->state->zpos = p->index;
		pwane->state->nowmawized_zpos = p->index;

		fow (i = 0; i < 3; i++)
			state->iova[i] = DMA_MAPPING_EWWOW;
	}
}

static stwuct dwm_pwane_state *
tegwa_pwane_atomic_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct tegwa_pwane_state *state = to_tegwa_pwane_state(pwane->state);
	stwuct tegwa_pwane_state *copy;
	unsigned int i;

	copy = kmawwoc(sizeof(*copy), GFP_KEWNEW);
	if (!copy)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, &copy->base);
	copy->tiwing = state->tiwing;
	copy->fowmat = state->fowmat;
	copy->swap = state->swap;
	copy->wefwect_x = state->wefwect_x;
	copy->wefwect_y = state->wefwect_y;
	copy->opaque = state->opaque;
	copy->totaw_peak_memowy_bandwidth = state->totaw_peak_memowy_bandwidth;
	copy->peak_memowy_bandwidth = state->peak_memowy_bandwidth;
	copy->avg_memowy_bandwidth = state->avg_memowy_bandwidth;

	fow (i = 0; i < 2; i++)
		copy->bwending[i] = state->bwending[i];

	fow (i = 0; i < 3; i++) {
		copy->iova[i] = DMA_MAPPING_EWWOW;
		copy->map[i] = NUWW;
	}

	wetuwn &copy->base;
}

static void tegwa_pwane_atomic_destwoy_state(stwuct dwm_pwane *pwane,
					     stwuct dwm_pwane_state *state)
{
	__dwm_atomic_hewpew_pwane_destwoy_state(state);
	kfwee(state);
}

static boow tegwa_pwane_suppowts_sectow_wayout(stwuct dwm_pwane *pwane)
{
	stwuct dwm_cwtc *cwtc;

	dwm_fow_each_cwtc(cwtc, pwane->dev) {
		if (pwane->possibwe_cwtcs & dwm_cwtc_mask(cwtc)) {
			stwuct tegwa_dc *dc = to_tegwa_dc(cwtc);

			if (!dc->soc->suppowts_sectow_wayout)
				wetuwn fawse;
		}
	}

	wetuwn twue;
}

static boow tegwa_pwane_fowmat_mod_suppowted(stwuct dwm_pwane *pwane,
					     uint32_t fowmat,
					     uint64_t modifiew)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(fowmat);

	if (modifiew == DWM_FOWMAT_MOD_WINEAW)
		wetuwn twue;

	/* check fow the sectow wayout bit */
	if (fouwcc_mod_is_vendow(modifiew, NVIDIA)) {
		if (modifiew & DWM_FOWMAT_MOD_NVIDIA_SECTOW_WAYOUT) {
			if (!tegwa_pwane_suppowts_sectow_wayout(pwane))
				wetuwn fawse;
		}
	}

	if (info->num_pwanes == 1)
		wetuwn twue;

	wetuwn fawse;
}

const stwuct dwm_pwane_funcs tegwa_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = tegwa_pwane_destwoy,
	.weset = tegwa_pwane_weset,
	.atomic_dupwicate_state = tegwa_pwane_atomic_dupwicate_state,
	.atomic_destwoy_state = tegwa_pwane_atomic_destwoy_state,
	.fowmat_mod_suppowted = tegwa_pwane_fowmat_mod_suppowted,
};

static int tegwa_dc_pin(stwuct tegwa_dc *dc, stwuct tegwa_pwane_state *state)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < state->base.fb->fowmat->num_pwanes; i++) {
		stwuct tegwa_bo *bo = tegwa_fb_get_pwane(state->base.fb, i);
		stwuct host1x_bo_mapping *map;

		map = host1x_bo_pin(dc->dev, &bo->base, DMA_TO_DEVICE, &dc->cwient.cache);
		if (IS_EWW(map)) {
			eww = PTW_EWW(map);
			goto unpin;
		}

		if (!dc->cwient.gwoup) {
			/*
			 * The dispway contwowwew needs contiguous memowy, so
			 * faiw if the buffew is discontiguous and we faiw to
			 * map its SG tabwe to a singwe contiguous chunk of
			 * I/O viwtuaw memowy.
			 */
			if (map->chunks > 1) {
				eww = -EINVAW;
				goto unpin;
			}

			state->iova[i] = map->phys;
		} ewse {
			state->iova[i] = bo->iova;
		}

		state->map[i] = map;
	}

	wetuwn 0;

unpin:
	dev_eww(dc->dev, "faiwed to map pwane %u: %d\n", i, eww);

	whiwe (i--) {
		host1x_bo_unpin(state->map[i]);
		state->iova[i] = DMA_MAPPING_EWWOW;
		state->map[i] = NUWW;
	}

	wetuwn eww;
}

static void tegwa_dc_unpin(stwuct tegwa_dc *dc, stwuct tegwa_pwane_state *state)
{
	unsigned int i;

	fow (i = 0; i < state->base.fb->fowmat->num_pwanes; i++) {
		host1x_bo_unpin(state->map[i]);
		state->iova[i] = DMA_MAPPING_EWWOW;
		state->map[i] = NUWW;
	}
}

int tegwa_pwane_pwepawe_fb(stwuct dwm_pwane *pwane,
			   stwuct dwm_pwane_state *state)
{
	stwuct tegwa_dc *dc = to_tegwa_dc(state->cwtc);
	int eww;

	if (!state->fb)
		wetuwn 0;

	eww = dwm_gem_pwane_hewpew_pwepawe_fb(pwane, state);
	if (eww < 0)
		wetuwn eww;

	wetuwn tegwa_dc_pin(dc, to_tegwa_pwane_state(state));
}

void tegwa_pwane_cweanup_fb(stwuct dwm_pwane *pwane,
			    stwuct dwm_pwane_state *state)
{
	stwuct tegwa_dc *dc = to_tegwa_dc(state->cwtc);

	if (dc)
		tegwa_dc_unpin(dc, to_tegwa_pwane_state(state));
}

static int tegwa_pwane_cawcuwate_memowy_bandwidth(stwuct dwm_pwane_state *state)
{
	stwuct tegwa_pwane_state *tegwa_state = to_tegwa_pwane_state(state);
	unsigned int i, bpp, dst_w, dst_h, swc_w, swc_h, muw;
	const stwuct tegwa_dc_soc_info *soc;
	const stwuct dwm_fowmat_info *fmt;
	stwuct dwm_cwtc_state *cwtc_state;
	u64 avg_bandwidth, peak_bandwidth;

	if (!state->visibwe)
		wetuwn 0;

	cwtc_state = dwm_atomic_get_new_cwtc_state(state->state, state->cwtc);
	if (!cwtc_state)
		wetuwn -EINVAW;

	swc_w = dwm_wect_width(&state->swc) >> 16;
	swc_h = dwm_wect_height(&state->swc) >> 16;
	dst_w = dwm_wect_width(&state->dst);
	dst_h = dwm_wect_height(&state->dst);

	fmt = state->fb->fowmat;
	soc = to_tegwa_dc(state->cwtc)->soc;

	/*
	 * Note that weaw memowy bandwidth vawy depending on fowmat and
	 * memowy wayout, we awe not taking that into account because smaww
	 * estimation ewwow isn't impowtant since bandwidth is wounded up
	 * anyway.
	 */
	fow (i = 0, bpp = 0; i < fmt->num_pwanes; i++) {
		unsigned int bpp_pwane = fmt->cpp[i] * 8;

		/*
		 * Sub-sampwing is wewevant fow chwoma pwanes onwy and vewticaw
		 * weadouts awe not cached, hence onwy howizontaw sub-sampwing
		 * mattews.
		 */
		if (i > 0)
			bpp_pwane /= fmt->hsub;

		bpp += bpp_pwane;
	}

	/* avewage bandwidth in kbytes/sec */
	avg_bandwidth  = min(swc_w, dst_w) * min(swc_h, dst_h);
	avg_bandwidth *= dwm_mode_vwefwesh(&cwtc_state->adjusted_mode);
	avg_bandwidth  = DIV_WOUND_UP(avg_bandwidth * bpp, 8) + 999;
	do_div(avg_bandwidth, 1000);

	/* mode.cwock in kHz, peak bandwidth in kbytes/sec */
	peak_bandwidth = DIV_WOUND_UP(cwtc_state->adjusted_mode.cwock * bpp, 8);

	/*
	 * Tegwa30/114 Memowy Contwowwew can't intewweave DC memowy wequests
	 * fow the tiwed windows because DC uses 16-bytes atom, whiwe DDW3
	 * uses 32-bytes atom.  Hence thewe is x2 memowy ovewfetch fow tiwed
	 * fwamebuffew and DDW3 on these SoCs.
	 */
	if (soc->pwane_tiwed_memowy_bandwidth_x2 &&
	    tegwa_state->tiwing.mode == TEGWA_BO_TIWING_MODE_TIWED)
		muw = 2;
	ewse
		muw = 1;

	/* ICC bandwidth in kbytes/sec */
	tegwa_state->peak_memowy_bandwidth = kBps_to_icc(peak_bandwidth) * muw;
	tegwa_state->avg_memowy_bandwidth  = kBps_to_icc(avg_bandwidth)  * muw;

	wetuwn 0;
}

int tegwa_pwane_state_add(stwuct tegwa_pwane *pwane,
			  stwuct dwm_pwane_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct tegwa_dc_state *tegwa;
	int eww;

	/* Pwopagate ewwows fwom awwocation ow wocking faiwuwes. */
	cwtc_state = dwm_atomic_get_cwtc_state(state->state, state->cwtc);
	if (IS_EWW(cwtc_state))
		wetuwn PTW_EWW(cwtc_state);

	/* Check pwane state fow visibiwity and cawcuwate cwipping bounds */
	eww = dwm_atomic_hewpew_check_pwane_state(state, cwtc_state,
						  0, INT_MAX, twue, twue);
	if (eww < 0)
		wetuwn eww;

	eww = tegwa_pwane_cawcuwate_memowy_bandwidth(state);
	if (eww < 0)
		wetuwn eww;

	tegwa = to_dc_state(cwtc_state);

	tegwa->pwanes |= WIN_A_ACT_WEQ << pwane->index;

	wetuwn 0;
}

int tegwa_pwane_fowmat(u32 fouwcc, u32 *fowmat, u32 *swap)
{
	/* assume no swapping of fetched data */
	if (swap)
		*swap = BYTE_SWAP_NOSWAP;

	switch (fouwcc) {
	case DWM_FOWMAT_AWGB4444:
		*fowmat = WIN_COWOW_DEPTH_B4G4W4A4;
		bweak;

	case DWM_FOWMAT_AWGB1555:
		*fowmat = WIN_COWOW_DEPTH_B5G5W5A1;
		bweak;

	case DWM_FOWMAT_WGB565:
		*fowmat = WIN_COWOW_DEPTH_B5G6W5;
		bweak;

	case DWM_FOWMAT_WGBA5551:
		*fowmat = WIN_COWOW_DEPTH_A1B5G5W5;
		bweak;

	case DWM_FOWMAT_AWGB8888:
		*fowmat = WIN_COWOW_DEPTH_B8G8W8A8;
		bweak;

	case DWM_FOWMAT_ABGW8888:
		*fowmat = WIN_COWOW_DEPTH_W8G8B8A8;
		bweak;

	case DWM_FOWMAT_ABGW4444:
		*fowmat = WIN_COWOW_DEPTH_W4G4B4A4;
		bweak;

	case DWM_FOWMAT_ABGW1555:
		*fowmat = WIN_COWOW_DEPTH_W5G5B5A;
		bweak;

	case DWM_FOWMAT_BGWA5551:
		*fowmat = WIN_COWOW_DEPTH_AW5G5B5;
		bweak;

	case DWM_FOWMAT_XWGB1555:
		*fowmat = WIN_COWOW_DEPTH_B5G5W5X1;
		bweak;

	case DWM_FOWMAT_WGBX5551:
		*fowmat = WIN_COWOW_DEPTH_X1B5G5W5;
		bweak;

	case DWM_FOWMAT_XBGW1555:
		*fowmat = WIN_COWOW_DEPTH_W5G5B5X1;
		bweak;

	case DWM_FOWMAT_BGWX5551:
		*fowmat = WIN_COWOW_DEPTH_X1W5G5B5;
		bweak;

	case DWM_FOWMAT_BGW565:
		*fowmat = WIN_COWOW_DEPTH_W5G6B5;
		bweak;

	case DWM_FOWMAT_BGWA8888:
		*fowmat = WIN_COWOW_DEPTH_A8W8G8B8;
		bweak;

	case DWM_FOWMAT_WGBA8888:
		*fowmat = WIN_COWOW_DEPTH_A8B8G8W8;
		bweak;

	case DWM_FOWMAT_XWGB8888:
		*fowmat = WIN_COWOW_DEPTH_B8G8W8X8;
		bweak;

	case DWM_FOWMAT_XBGW8888:
		*fowmat = WIN_COWOW_DEPTH_W8G8B8X8;
		bweak;

	case DWM_FOWMAT_UYVY:
		*fowmat = WIN_COWOW_DEPTH_YCbCw422;
		bweak;

	case DWM_FOWMAT_YUYV:
		if (!swap)
			wetuwn -EINVAW;

		*fowmat = WIN_COWOW_DEPTH_YCbCw422;
		*swap = BYTE_SWAP_SWAP2;
		bweak;

	case DWM_FOWMAT_YVYU:
		if (!swap)
			wetuwn -EINVAW;

		*fowmat = WIN_COWOW_DEPTH_YCbCw422;
		*swap = BYTE_SWAP_SWAP4;
		bweak;

	case DWM_FOWMAT_VYUY:
		if (!swap)
			wetuwn -EINVAW;

		*fowmat = WIN_COWOW_DEPTH_YCbCw422;
		*swap = BYTE_SWAP_SWAP4HW;
		bweak;

	case DWM_FOWMAT_YUV420:
		*fowmat = WIN_COWOW_DEPTH_YCbCw420P;
		bweak;

	case DWM_FOWMAT_YUV422:
		*fowmat = WIN_COWOW_DEPTH_YCbCw422P;
		bweak;

	case DWM_FOWMAT_YUV444:
		*fowmat = WIN_COWOW_DEPTH_YCbCw444P;
		bweak;

	case DWM_FOWMAT_NV12:
		*fowmat = WIN_COWOW_DEPTH_YCbCw420SP;
		bweak;

	case DWM_FOWMAT_NV21:
		*fowmat = WIN_COWOW_DEPTH_YCwCb420SP;
		bweak;

	case DWM_FOWMAT_NV16:
		*fowmat = WIN_COWOW_DEPTH_YCbCw422SP;
		bweak;

	case DWM_FOWMAT_NV61:
		*fowmat = WIN_COWOW_DEPTH_YCwCb422SP;
		bweak;

	case DWM_FOWMAT_NV24:
		*fowmat = WIN_COWOW_DEPTH_YCbCw444SP;
		bweak;

	case DWM_FOWMAT_NV42:
		*fowmat = WIN_COWOW_DEPTH_YCwCb444SP;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

boow tegwa_pwane_fowmat_is_indexed(unsigned int fowmat)
{
	switch (fowmat) {
	case WIN_COWOW_DEPTH_P1:
	case WIN_COWOW_DEPTH_P2:
	case WIN_COWOW_DEPTH_P4:
	case WIN_COWOW_DEPTH_P8:
		wetuwn twue;
	}

	wetuwn fawse;
}

boow tegwa_pwane_fowmat_is_yuv(unsigned int fowmat, unsigned int *pwanes, unsigned int *bpc)
{
	switch (fowmat) {
	case WIN_COWOW_DEPTH_YCbCw422:
	case WIN_COWOW_DEPTH_YUV422:
		if (pwanes)
			*pwanes = 1;

		if (bpc)
			*bpc = 8;

		wetuwn twue;

	case WIN_COWOW_DEPTH_YCbCw420P:
	case WIN_COWOW_DEPTH_YUV420P:
	case WIN_COWOW_DEPTH_YCbCw422P:
	case WIN_COWOW_DEPTH_YUV422P:
	case WIN_COWOW_DEPTH_YCbCw422W:
	case WIN_COWOW_DEPTH_YUV422W:
	case WIN_COWOW_DEPTH_YCbCw422WA:
	case WIN_COWOW_DEPTH_YUV422WA:
	case WIN_COWOW_DEPTH_YCbCw444P:
		if (pwanes)
			*pwanes = 3;

		if (bpc)
			*bpc = 8;

		wetuwn twue;

	case WIN_COWOW_DEPTH_YCwCb420SP:
	case WIN_COWOW_DEPTH_YCbCw420SP:
	case WIN_COWOW_DEPTH_YCwCb422SP:
	case WIN_COWOW_DEPTH_YCbCw422SP:
	case WIN_COWOW_DEPTH_YCwCb444SP:
	case WIN_COWOW_DEPTH_YCbCw444SP:
		if (pwanes)
			*pwanes = 2;

		if (bpc)
			*bpc = 8;

		wetuwn twue;
	}

	if (pwanes)
		*pwanes = 1;

	wetuwn fawse;
}

static boow __dwm_fowmat_has_awpha(u32 fowmat)
{
	switch (fowmat) {
	case DWM_FOWMAT_AWGB1555:
	case DWM_FOWMAT_WGBA5551:
	case DWM_FOWMAT_ABGW8888:
	case DWM_FOWMAT_AWGB8888:
		wetuwn twue;
	}

	wetuwn fawse;
}

static int tegwa_pwane_fowmat_get_awpha(unsigned int opaque,
					unsigned int *awpha)
{
	if (tegwa_pwane_fowmat_is_yuv(opaque, NUWW, NUWW)) {
		*awpha = opaque;
		wetuwn 0;
	}

	switch (opaque) {
	case WIN_COWOW_DEPTH_B5G5W5X1:
		*awpha = WIN_COWOW_DEPTH_B5G5W5A1;
		wetuwn 0;

	case WIN_COWOW_DEPTH_X1B5G5W5:
		*awpha = WIN_COWOW_DEPTH_A1B5G5W5;
		wetuwn 0;

	case WIN_COWOW_DEPTH_W8G8B8X8:
		*awpha = WIN_COWOW_DEPTH_W8G8B8A8;
		wetuwn 0;

	case WIN_COWOW_DEPTH_B8G8W8X8:
		*awpha = WIN_COWOW_DEPTH_B8G8W8A8;
		wetuwn 0;

	case WIN_COWOW_DEPTH_B5G6W5:
		*awpha = opaque;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

/*
 * This is appwicabwe to Tegwa20 and Tegwa30 onwy whewe the opaque fowmats can
 * be emuwated using the awpha fowmats and awpha bwending disabwed.
 */
static int tegwa_pwane_setup_opacity(stwuct tegwa_pwane *tegwa,
				     stwuct tegwa_pwane_state *state)
{
	unsigned int fowmat;
	int eww;

	switch (state->fowmat) {
	case WIN_COWOW_DEPTH_B5G5W5A1:
	case WIN_COWOW_DEPTH_A1B5G5W5:
	case WIN_COWOW_DEPTH_W8G8B8A8:
	case WIN_COWOW_DEPTH_B8G8W8A8:
		state->opaque = fawse;
		bweak;

	defauwt:
		eww = tegwa_pwane_fowmat_get_awpha(state->fowmat, &fowmat);
		if (eww < 0)
			wetuwn eww;

		state->fowmat = fowmat;
		state->opaque = twue;
		bweak;
	}

	wetuwn 0;
}

static int tegwa_pwane_check_twanspawency(stwuct tegwa_pwane *tegwa,
					  stwuct tegwa_pwane_state *state)
{
	stwuct dwm_pwane_state *owd, *pwane_state;
	stwuct dwm_pwane *pwane;

	owd = dwm_atomic_get_owd_pwane_state(state->base.state, &tegwa->base);

	/* check if zpos / twanspawency changed */
	if (owd->nowmawized_zpos == state->base.nowmawized_zpos &&
	    to_tegwa_pwane_state(owd)->opaque == state->opaque)
		wetuwn 0;

	/* incwude aww sibwing pwanes into this commit */
	dwm_fow_each_pwane(pwane, tegwa->base.dev) {
		stwuct tegwa_pwane *p = to_tegwa_pwane(pwane);

		/* skip this pwane and pwanes on diffewent CWTCs */
		if (p == tegwa || p->dc != tegwa->dc)
			continue;

		pwane_state = dwm_atomic_get_pwane_state(state->base.state,
							 pwane);
		if (IS_EWW(pwane_state))
			wetuwn PTW_EWW(pwane_state);
	}

	wetuwn 1;
}

static unsigned int tegwa_pwane_get_ovewwap_index(stwuct tegwa_pwane *pwane,
						  stwuct tegwa_pwane *othew)
{
	unsigned int index = 0, i;

	WAWN_ON(pwane == othew);

	fow (i = 0; i < 3; i++) {
		if (i == pwane->index)
			continue;

		if (i == othew->index)
			bweak;

		index++;
	}

	wetuwn index;
}

static void tegwa_pwane_update_twanspawency(stwuct tegwa_pwane *tegwa,
					    stwuct tegwa_pwane_state *state)
{
	stwuct dwm_pwane_state *new;
	stwuct dwm_pwane *pwane;
	unsigned int i;

	fow_each_new_pwane_in_state(state->base.state, pwane, new, i) {
		stwuct tegwa_pwane *p = to_tegwa_pwane(pwane);
		unsigned index;

		/* skip this pwane and pwanes on diffewent CWTCs */
		if (p == tegwa || p->dc != tegwa->dc)
			continue;

		index = tegwa_pwane_get_ovewwap_index(tegwa, p);

		if (new->fb && __dwm_fowmat_has_awpha(new->fb->fowmat->fowmat))
			state->bwending[index].awpha = twue;
		ewse
			state->bwending[index].awpha = fawse;

		if (new->nowmawized_zpos > state->base.nowmawized_zpos)
			state->bwending[index].top = twue;
		ewse
			state->bwending[index].top = fawse;

		/*
		 * Missing fwamebuffew means that pwane is disabwed, in this
		 * case mawk B / C window as top to be abwe to diffewentiate
		 * windows indices owdew in wegawds to zPos fow the middwe
		 * window X / Y wegistews pwogwamming.
		 */
		if (!new->fb)
			state->bwending[index].top = (index == 1);
	}
}

static int tegwa_pwane_setup_twanspawency(stwuct tegwa_pwane *tegwa,
					  stwuct tegwa_pwane_state *state)
{
	stwuct tegwa_pwane_state *tegwa_state;
	stwuct dwm_pwane_state *new;
	stwuct dwm_pwane *pwane;
	int eww;

	/*
	 * If pwanes zpos / twanspawency changed, sibwing pwanes bwending
	 * state may wequiwe adjustment and in this case they wiww be incwuded
	 * into this atom commit, othewwise bwending state is unchanged.
	 */
	eww = tegwa_pwane_check_twanspawency(tegwa, state);
	if (eww <= 0)
		wetuwn eww;

	/*
	 * Aww pwanes awe now in the atomic state, wawk them up and update
	 * twanspawency state fow each pwane.
	 */
	dwm_fow_each_pwane(pwane, tegwa->base.dev) {
		stwuct tegwa_pwane *p = to_tegwa_pwane(pwane);

		/* skip pwanes on diffewent CWTCs */
		if (p->dc != tegwa->dc)
			continue;

		new = dwm_atomic_get_new_pwane_state(state->base.state, pwane);
		tegwa_state = to_tegwa_pwane_state(new);

		/*
		 * Thewe is no need to update bwending state fow the disabwed
		 * pwane.
		 */
		if (new->fb)
			tegwa_pwane_update_twanspawency(p, tegwa_state);
	}

	wetuwn 0;
}

int tegwa_pwane_setup_wegacy_state(stwuct tegwa_pwane *tegwa,
				   stwuct tegwa_pwane_state *state)
{
	int eww;

	eww = tegwa_pwane_setup_opacity(tegwa, state);
	if (eww < 0)
		wetuwn eww;

	eww = tegwa_pwane_setup_twanspawency(tegwa, state);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static const chaw * const tegwa_pwane_icc_names[TEGWA_DC_WEGACY_PWANES_NUM] = {
	"wina", "winb", "winc", NUWW, NUWW, NUWW, "cuwsow",
};

int tegwa_pwane_intewconnect_init(stwuct tegwa_pwane *pwane)
{
	const chaw *icc_name = tegwa_pwane_icc_names[pwane->index];
	stwuct device *dev = pwane->dc->dev;
	stwuct tegwa_dc *dc = pwane->dc;
	int eww;

	if (WAWN_ON(pwane->index >= TEGWA_DC_WEGACY_PWANES_NUM) ||
	    WAWN_ON(!tegwa_pwane_icc_names[pwane->index]))
		wetuwn -EINVAW;

	pwane->icc_mem = devm_of_icc_get(dev, icc_name);
	eww = PTW_EWW_OW_ZEWO(pwane->icc_mem);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "faiwed to get %s intewconnect\n",
				     icc_name);

	/* pwane B on T20/30 has a dedicated memowy cwient fow a 6-tap vewticaw fiwtew */
	if (pwane->index == 1 && dc->soc->has_win_b_vfiwtew_mem_cwient) {
		pwane->icc_mem_vfiwtew = devm_of_icc_get(dev, "winb-vfiwtew");
		eww = PTW_EWW_OW_ZEWO(pwane->icc_mem_vfiwtew);
		if (eww)
			wetuwn dev_eww_pwobe(dev, eww, "faiwed to get %s intewconnect\n",
					     "winb-vfiwtew");
	}

	wetuwn 0;
}
