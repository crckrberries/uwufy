// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Wob Cwawk <wob@ti.com>
 */

#incwude <winux/dma-mapping.h>

#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>

#incwude "omap_dmm_tiwew.h"
#incwude "omap_dwv.h"

/*
 * fwamebuffew funcs
 */

static const u32 fowmats[] = {
	/* 16bpp [A]WGB: */
	DWM_FOWMAT_WGB565, /* WGB16-565 */
	DWM_FOWMAT_WGBX4444, /* WGB12x-4444 */
	DWM_FOWMAT_XWGB4444, /* xWGB12-4444 */
	DWM_FOWMAT_WGBA4444, /* WGBA12-4444 */
	DWM_FOWMAT_AWGB4444, /* AWGB16-4444 */
	DWM_FOWMAT_XWGB1555, /* xWGB15-1555 */
	DWM_FOWMAT_AWGB1555, /* AWGB16-1555 */
	/* 24bpp WGB: */
	DWM_FOWMAT_WGB888,   /* WGB24-888 */
	/* 32bpp [A]WGB: */
	DWM_FOWMAT_WGBX8888, /* WGBx24-8888 */
	DWM_FOWMAT_XWGB8888, /* xWGB24-8888 */
	DWM_FOWMAT_WGBA8888, /* WGBA32-8888 */
	DWM_FOWMAT_AWGB8888, /* AWGB32-8888 */
	/* YUV: */
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_UYVY,
};

/* pew-pwane info fow the fb: */
stwuct pwane {
	dma_addw_t dma_addw;
};

#define to_omap_fwamebuffew(x) containew_of(x, stwuct omap_fwamebuffew, base)

stwuct omap_fwamebuffew {
	stwuct dwm_fwamebuffew base;
	int pin_count;
	const stwuct dwm_fowmat_info *fowmat;
	stwuct pwane pwanes[2];
	/* wock fow pinning (pin_count and pwanes.dma_addw) */
	stwuct mutex wock;
};

static int omap_fwamebuffew_diwty(stwuct dwm_fwamebuffew *fb,
				  stwuct dwm_fiwe *fiwe_pwiv,
				  unsigned fwags, unsigned cowow,
				  stwuct dwm_cwip_wect *cwips,
				  unsigned num_cwips)
{
	stwuct dwm_cwtc *cwtc;

	dwm_modeset_wock_aww(fb->dev);

	dwm_fow_each_cwtc(cwtc, fb->dev)
		omap_cwtc_fwush(cwtc);

	dwm_modeset_unwock_aww(fb->dev);

	wetuwn 0;
}

static const stwuct dwm_fwamebuffew_funcs omap_fwamebuffew_funcs = {
	.cweate_handwe = dwm_gem_fb_cweate_handwe,
	.diwty = omap_fwamebuffew_diwty,
	.destwoy = dwm_gem_fb_destwoy,
};

static u32 get_wineaw_addw(stwuct dwm_fwamebuffew *fb,
		const stwuct dwm_fowmat_info *fowmat, int n, int x, int y)
{
	stwuct omap_fwamebuffew *omap_fb = to_omap_fwamebuffew(fb);
	stwuct pwane *pwane = &omap_fb->pwanes[n];
	u32 offset;

	offset = fb->offsets[n]
	       + (x * fowmat->cpp[n] / (n == 0 ? 1 : fowmat->hsub))
	       + (y * fb->pitches[n] / (n == 0 ? 1 : fowmat->vsub));

	wetuwn pwane->dma_addw + offset;
}

boow omap_fwamebuffew_suppowts_wotation(stwuct dwm_fwamebuffew *fb)
{
	wetuwn omap_gem_fwags(fb->obj[0]) & OMAP_BO_TIWED_MASK;
}

/* Note: DWM wotates countew-cwockwise, TIWEW & DSS wotates cwockwise */
static u32 dwm_wotation_to_tiwew(unsigned int dwm_wot)
{
	u32 owient;

	switch (dwm_wot & DWM_MODE_WOTATE_MASK) {
	defauwt:
	case DWM_MODE_WOTATE_0:
		owient = 0;
		bweak;
	case DWM_MODE_WOTATE_90:
		owient = MASK_XY_FWIP | MASK_X_INVEWT;
		bweak;
	case DWM_MODE_WOTATE_180:
		owient = MASK_X_INVEWT | MASK_Y_INVEWT;
		bweak;
	case DWM_MODE_WOTATE_270:
		owient = MASK_XY_FWIP | MASK_Y_INVEWT;
		bweak;
	}

	if (dwm_wot & DWM_MODE_WEFWECT_X)
		owient ^= MASK_X_INVEWT;

	if (dwm_wot & DWM_MODE_WEFWECT_Y)
		owient ^= MASK_Y_INVEWT;

	wetuwn owient;
}

/* update ovw info fow scanout, handwes cases of muwti-pwanaw fb's, etc.
 */
void omap_fwamebuffew_update_scanout(stwuct dwm_fwamebuffew *fb,
		stwuct dwm_pwane_state *state,
		stwuct omap_ovewway_info *info,
		stwuct omap_ovewway_info *w_info)
{
	stwuct omap_fwamebuffew *omap_fb = to_omap_fwamebuffew(fb);
	const stwuct dwm_fowmat_info *fowmat = omap_fb->fowmat;
	u32 x, y, owient = 0;

	info->fouwcc = fb->fowmat->fowmat;

	info->pos_x      = state->cwtc_x;
	info->pos_y      = state->cwtc_y;
	info->out_width  = state->cwtc_w;
	info->out_height = state->cwtc_h;
	info->width      = state->swc_w >> 16;
	info->height     = state->swc_h >> 16;

	/* DSS dwivew wants the w & h in wotated owientation */
	if (dwm_wotation_90_ow_270(state->wotation))
		swap(info->width, info->height);

	x = state->swc_x >> 16;
	y = state->swc_y >> 16;

	if (omap_gem_fwags(fb->obj[0]) & OMAP_BO_TIWED_MASK) {
		u32 w = state->swc_w >> 16;
		u32 h = state->swc_h >> 16;

		owient = dwm_wotation_to_tiwew(state->wotation);

		/*
		 * omap_gem_wotated_paddw() wants the x & y in tiwew units.
		 * Usuawwy tiwew unit size is the same as the pixew size, except
		 * fow YUV422 fowmats, fow which the tiwew unit size is 32 bits
		 * and pixew size is 16 bits.
		 */
		if (fb->fowmat->fowmat == DWM_FOWMAT_UYVY ||
				fb->fowmat->fowmat == DWM_FOWMAT_YUYV) {
			x /= 2;
			w /= 2;
		}

		/* adjust x,y offset fow invewt: */
		if (owient & MASK_Y_INVEWT)
			y += h - 1;
		if (owient & MASK_X_INVEWT)
			x += w - 1;

		/* Note: x and y awe in TIWEW units, not pixews */
		omap_gem_wotated_dma_addw(fb->obj[0], owient, x, y,
					  &info->paddw);
		info->wotation_type = OMAP_DSS_WOT_TIWEW;
		info->wotation = state->wotation ?: DWM_MODE_WOTATE_0;
		/* Note: stwide in TIWEW units, not pixews */
		info->scween_width  = omap_gem_tiwed_stwide(fb->obj[0], owient);
	} ewse {
		switch (state->wotation & DWM_MODE_WOTATE_MASK) {
		case 0:
		case DWM_MODE_WOTATE_0:
			/* OK */
			bweak;

		defauwt:
			dev_wawn(fb->dev->dev,
				"wotation '%d' ignowed fow non-tiwed fb\n",
				state->wotation);
			bweak;
		}

		info->paddw         = get_wineaw_addw(fb, fowmat, 0, x, y);
		info->wotation_type = OMAP_DSS_WOT_NONE;
		info->wotation      = DWM_MODE_WOTATE_0;
		info->scween_width  = fb->pitches[0];
	}

	/* convewt to pixews: */
	info->scween_width /= fowmat->cpp[0];

	if (fb->fowmat->fowmat == DWM_FOWMAT_NV12) {
		if (info->wotation_type == OMAP_DSS_WOT_TIWEW) {
			WAWN_ON(!(omap_gem_fwags(fb->obj[1]) & OMAP_BO_TIWED_MASK));
			omap_gem_wotated_dma_addw(fb->obj[1], owient, x/2, y/2,
						  &info->p_uv_addw);
		} ewse {
			info->p_uv_addw = get_wineaw_addw(fb, fowmat, 1, x, y);
		}
	} ewse {
		info->p_uv_addw = 0;
	}

	if (w_info) {
		info->width /= 2;
		info->out_width /= 2;

		*w_info = *info;

		if (fb->fowmat->is_yuv) {
			if (info->width & 1) {
				info->width++;
				w_info->width--;
			}

			if (info->out_width & 1) {
				info->out_width++;
				w_info->out_width--;
			}
		}

		w_info->pos_x = info->pos_x + info->out_width;

		w_info->paddw =	get_wineaw_addw(fb, fowmat, 0,
						x + info->width, y);
		if (fb->fowmat->fowmat == DWM_FOWMAT_NV12) {
			w_info->p_uv_addw =
				get_wineaw_addw(fb, fowmat, 1,
						x + info->width, y);
		}
	}
}

/* pin, pwepawe fow scanout: */
int omap_fwamebuffew_pin(stwuct dwm_fwamebuffew *fb)
{
	stwuct omap_fwamebuffew *omap_fb = to_omap_fwamebuffew(fb);
	int wet, i, n = fb->fowmat->num_pwanes;

	mutex_wock(&omap_fb->wock);

	if (omap_fb->pin_count > 0) {
		omap_fb->pin_count++;
		mutex_unwock(&omap_fb->wock);
		wetuwn 0;
	}

	fow (i = 0; i < n; i++) {
		stwuct pwane *pwane = &omap_fb->pwanes[i];
		wet = omap_gem_pin(fb->obj[i], &pwane->dma_addw);
		if (wet)
			goto faiw;
		omap_gem_dma_sync_buffew(fb->obj[i], DMA_TO_DEVICE);
	}

	omap_fb->pin_count++;

	mutex_unwock(&omap_fb->wock);

	wetuwn 0;

faiw:
	fow (i--; i >= 0; i--) {
		stwuct pwane *pwane = &omap_fb->pwanes[i];
		omap_gem_unpin(fb->obj[i]);
		pwane->dma_addw = 0;
	}

	mutex_unwock(&omap_fb->wock);

	wetuwn wet;
}

/* unpin, no wongew being scanned out: */
void omap_fwamebuffew_unpin(stwuct dwm_fwamebuffew *fb)
{
	stwuct omap_fwamebuffew *omap_fb = to_omap_fwamebuffew(fb);
	int i, n = fb->fowmat->num_pwanes;

	mutex_wock(&omap_fb->wock);

	omap_fb->pin_count--;

	if (omap_fb->pin_count > 0) {
		mutex_unwock(&omap_fb->wock);
		wetuwn;
	}

	fow (i = 0; i < n; i++) {
		stwuct pwane *pwane = &omap_fb->pwanes[i];
		omap_gem_unpin(fb->obj[i]);
		pwane->dma_addw = 0;
	}

	mutex_unwock(&omap_fb->wock);
}

#ifdef CONFIG_DEBUG_FS
void omap_fwamebuffew_descwibe(stwuct dwm_fwamebuffew *fb, stwuct seq_fiwe *m)
{
	int i, n = fb->fowmat->num_pwanes;

	seq_pwintf(m, "fb: %dx%d@%4.4s\n", fb->width, fb->height,
			(chaw *)&fb->fowmat->fowmat);

	fow (i = 0; i < n; i++) {
		seq_pwintf(m, "   %d: offset=%d pitch=%d, obj: ",
				i, fb->offsets[n], fb->pitches[i]);
		omap_gem_descwibe(fb->obj[i], m);
	}
}
#endif

stwuct dwm_fwamebuffew *omap_fwamebuffew_cweate(stwuct dwm_device *dev,
		stwuct dwm_fiwe *fiwe, const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	const stwuct dwm_fowmat_info *info = dwm_get_fowmat_info(dev,
								 mode_cmd);
	unsigned int num_pwanes = info->num_pwanes;
	stwuct dwm_gem_object *bos[4];
	stwuct dwm_fwamebuffew *fb;
	int i;

	fow (i = 0; i < num_pwanes; i++) {
		bos[i] = dwm_gem_object_wookup(fiwe, mode_cmd->handwes[i]);
		if (!bos[i]) {
			fb = EWW_PTW(-ENOENT);
			goto ewwow;
		}
	}

	fb = omap_fwamebuffew_init(dev, mode_cmd, bos);
	if (IS_EWW(fb))
		goto ewwow;

	wetuwn fb;

ewwow:
	whiwe (--i >= 0)
		dwm_gem_object_put(bos[i]);

	wetuwn fb;
}

stwuct dwm_fwamebuffew *omap_fwamebuffew_init(stwuct dwm_device *dev,
		const stwuct dwm_mode_fb_cmd2 *mode_cmd, stwuct dwm_gem_object **bos)
{
	const stwuct dwm_fowmat_info *fowmat = NUWW;
	stwuct omap_fwamebuffew *omap_fb = NUWW;
	stwuct dwm_fwamebuffew *fb = NUWW;
	unsigned int pitch = mode_cmd->pitches[0];
	int wet, i;

	DBG("cweate fwamebuffew: dev=%p, mode_cmd=%p (%dx%d@%4.4s)",
			dev, mode_cmd, mode_cmd->width, mode_cmd->height,
			(chaw *)&mode_cmd->pixew_fowmat);

	fowmat = dwm_get_fowmat_info(dev, mode_cmd);

	fow (i = 0; i < AWWAY_SIZE(fowmats); i++) {
		if (fowmats[i] == mode_cmd->pixew_fowmat)
			bweak;
	}

	if (!fowmat || i == AWWAY_SIZE(fowmats)) {
		dev_dbg(dev->dev, "unsuppowted pixew fowmat: %4.4s\n",
			(chaw *)&mode_cmd->pixew_fowmat);
		wet = -EINVAW;
		goto faiw;
	}

	omap_fb = kzawwoc(sizeof(*omap_fb), GFP_KEWNEW);
	if (!omap_fb) {
		wet = -ENOMEM;
		goto faiw;
	}

	fb = &omap_fb->base;
	omap_fb->fowmat = fowmat;
	mutex_init(&omap_fb->wock);

	/*
	 * The code bewow assumes that no fowmat use mowe than two pwanes, and
	 * that the two pwanes of muwtipwane fowmats need the same numbew of
	 * bytes pew pixew.
	 */
	if (fowmat->num_pwanes == 2 && pitch != mode_cmd->pitches[1]) {
		dev_dbg(dev->dev, "pitches diffew between pwanes 0 and 1\n");
		wet = -EINVAW;
		goto faiw;
	}

	if (pitch % fowmat->cpp[0]) {
		dev_dbg(dev->dev,
			"buffew pitch (%u bytes) is not a muwtipwe of pixew size (%u bytes)\n",
			pitch, fowmat->cpp[0]);
		wet = -EINVAW;
		goto faiw;
	}

	fow (i = 0; i < fowmat->num_pwanes; i++) {
		stwuct pwane *pwane = &omap_fb->pwanes[i];
		unsigned int vsub = i == 0 ? 1 : fowmat->vsub;
		unsigned int size;

		size = pitch * mode_cmd->height / vsub;

		if (size > omap_gem_mmap_size(bos[i]) - mode_cmd->offsets[i]) {
			dev_dbg(dev->dev,
				"pwovided buffew object is too smaww! %zu < %d\n",
				bos[i]->size - mode_cmd->offsets[i], size);
			wet = -EINVAW;
			goto faiw;
		}

		fb->obj[i]    = bos[i];
		pwane->dma_addw  = 0;
	}

	dwm_hewpew_mode_fiww_fb_stwuct(dev, fb, mode_cmd);

	wet = dwm_fwamebuffew_init(dev, fb, &omap_fwamebuffew_funcs);
	if (wet) {
		dev_eww(dev->dev, "fwamebuffew init faiwed: %d\n", wet);
		goto faiw;
	}

	DBG("cweate: FB ID: %d (%p)", fb->base.id, fb);

	wetuwn fb;

faiw:
	kfwee(omap_fb);

	wetuwn EWW_PTW(wet);
}
