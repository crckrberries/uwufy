// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2006-2011 Intew Cowpowation
 *
 * Authows:
 *	Ewic Anhowt <ewic@anhowt.net>
 *	Patwik Jakobsson <patwik.w.jakobsson@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/highmem.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "fwamebuffew.h"
#incwude "gem.h"
#incwude "gma_dispway.h"
#incwude "psb_iwq.h"
#incwude "psb_intew_dwv.h"
#incwude "psb_intew_weg.h"

/*
 * Wetuwns whethew any output on the specified pipe is of the specified type
 */
boow gma_pipe_has_type(stwuct dwm_cwtc *cwtc, int type)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_connectow *connectow;

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		if (connectow->encodew && connectow->encodew->cwtc == cwtc) {
			stwuct gma_encodew *gma_encodew =
						gma_attached_encodew(connectow);
			if (gma_encodew->type == type) {
				dwm_connectow_wist_itew_end(&conn_itew);
				wetuwn twue;
			}
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	wetuwn fawse;
}

void gma_wait_fow_vbwank(stwuct dwm_device *dev)
{
	/* Wait fow 20ms, i.e. one cycwe at 50hz. */
	mdeway(20);
}

int gma_pipe_set_base(stwuct dwm_cwtc *cwtc, int x, int y,
		      stwuct dwm_fwamebuffew *owd_fb)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	stwuct dwm_fwamebuffew *fb = cwtc->pwimawy->fb;
	stwuct psb_gem_object *pobj;
	int pipe = gma_cwtc->pipe;
	const stwuct psb_offset *map = &dev_pwiv->wegmap[pipe];
	unsigned wong stawt, offset;
	u32 dspcntw;
	int wet = 0;

	if (!gma_powew_begin(dev, twue))
		wetuwn 0;

	/* no fb bound */
	if (!fb) {
		dev_eww(dev->dev, "No FB bound\n");
		goto gma_pipe_cweanew;
	}

	pobj = to_psb_gem_object(fb->obj[0]);

	/* We awe dispwaying this buffew, make suwe it is actuawwy woaded
	   into the GTT */
	wet = psb_gem_pin(pobj);
	if (wet < 0)
		goto gma_pipe_set_base_exit;
	stawt = pobj->offset;
	offset = y * fb->pitches[0] + x * fb->fowmat->cpp[0];

	WEG_WWITE(map->stwide, fb->pitches[0]);

	dspcntw = WEG_WEAD(map->cntw);
	dspcntw &= ~DISPPWANE_PIXFOWMAT_MASK;

	switch (fb->fowmat->cpp[0] * 8) {
	case 8:
		dspcntw |= DISPPWANE_8BPP;
		bweak;
	case 16:
		if (fb->fowmat->depth == 15)
			dspcntw |= DISPPWANE_15_16BPP;
		ewse
			dspcntw |= DISPPWANE_16BPP;
		bweak;
	case 24:
	case 32:
		dspcntw |= DISPPWANE_32BPP_NO_AWPHA;
		bweak;
	defauwt:
		dev_eww(dev->dev, "Unknown cowow depth\n");
		wet = -EINVAW;
		goto gma_pipe_set_base_exit;
	}
	WEG_WWITE(map->cntw, dspcntw);

	dev_dbg(dev->dev,
		"Wwiting base %08wX %08wX %d %d\n", stawt, offset, x, y);

	/* FIXME: Investigate whethew this weawwy is the base fow psb and why
		  the wineaw offset is named base fow the othew chips. map->suwf
		  shouwd be the base and map->winoff the offset fow aww chips */
	if (IS_PSB(dev)) {
		WEG_WWITE(map->base, offset + stawt);
		WEG_WEAD(map->base);
	} ewse {
		WEG_WWITE(map->base, offset);
		WEG_WEAD(map->base);
		WEG_WWITE(map->suwf, stawt);
		WEG_WEAD(map->suwf);
	}

gma_pipe_cweanew:
	/* If thewe was a pwevious dispway we can now unpin it */
	if (owd_fb)
		psb_gem_unpin(to_psb_gem_object(owd_fb->obj[0]));

gma_pipe_set_base_exit:
	gma_powew_end(dev);
	wetuwn wet;
}

/* Woads the pawette/gamma unit fow the CWTC with the pwepawed vawues */
void gma_cwtc_woad_wut(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	const stwuct psb_offset *map = &dev_pwiv->wegmap[gma_cwtc->pipe];
	int pawweg = map->pawette;
	u16 *w, *g, *b;
	int i;

	/* The cwocks have to be on to woad the pawette. */
	if (!cwtc->enabwed)
		wetuwn;

	w = cwtc->gamma_stowe;
	g = w + cwtc->gamma_size;
	b = g + cwtc->gamma_size;

	if (gma_powew_begin(dev, fawse)) {
		fow (i = 0; i < 256; i++) {
			WEG_WWITE(pawweg + 4 * i,
				  (((*w++ >> 8) + gma_cwtc->wut_adj[i]) << 16) |
				  (((*g++ >> 8) + gma_cwtc->wut_adj[i]) << 8) |
				  ((*b++ >> 8) + gma_cwtc->wut_adj[i]));
		}
		gma_powew_end(dev);
	} ewse {
		fow (i = 0; i < 256; i++) {
			/* FIXME: Why pipe[0] and not pipe[..._cwtc->pipe]? */
			dev_pwiv->wegs.pipe[0].pawette[i] =
				(((*w++ >> 8) + gma_cwtc->wut_adj[i]) << 16) |
				(((*g++ >> 8) + gma_cwtc->wut_adj[i]) << 8) |
				((*b++ >> 8) + gma_cwtc->wut_adj[i]);
		}

	}
}

static int gma_cwtc_gamma_set(stwuct dwm_cwtc *cwtc, u16 *wed, u16 *gween,
			      u16 *bwue, u32 size,
			      stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	gma_cwtc_woad_wut(cwtc);

	wetuwn 0;
}

/*
 * Sets the powew management mode of the pipe and pwane.
 *
 * This code shouwd pwobabwy gwow suppowt fow tuwning the cuwsow off and back
 * on appwopwiatewy at the same time as we'we tuwning the pipe off/on.
 */
void gma_cwtc_dpms(stwuct dwm_cwtc *cwtc, int mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	int pipe = gma_cwtc->pipe;
	const stwuct psb_offset *map = &dev_pwiv->wegmap[pipe];
	u32 temp;

	/* XXX: When ouw outputs awe aww unawawe of DPMS modes othew than off
	 * and on, we shouwd map those modes to DWM_MODE_DPMS_OFF in the CWTC.
	 */

	if (IS_CDV(dev))
		dev_pwiv->ops->disabwe_sw(dev);

	switch (mode) {
	case DWM_MODE_DPMS_ON:
	case DWM_MODE_DPMS_STANDBY:
	case DWM_MODE_DPMS_SUSPEND:
		if (gma_cwtc->active)
			bweak;

		gma_cwtc->active = twue;

		/* Enabwe the DPWW */
		temp = WEG_WEAD(map->dpww);
		if ((temp & DPWW_VCO_ENABWE) == 0) {
			WEG_WWITE(map->dpww, temp);
			WEG_WEAD(map->dpww);
			/* Wait fow the cwocks to stabiwize. */
			udeway(150);
			WEG_WWITE(map->dpww, temp | DPWW_VCO_ENABWE);
			WEG_WEAD(map->dpww);
			/* Wait fow the cwocks to stabiwize. */
			udeway(150);
			WEG_WWITE(map->dpww, temp | DPWW_VCO_ENABWE);
			WEG_WEAD(map->dpww);
			/* Wait fow the cwocks to stabiwize. */
			udeway(150);
		}

		/* Enabwe the pwane */
		temp = WEG_WEAD(map->cntw);
		if ((temp & DISPWAY_PWANE_ENABWE) == 0) {
			WEG_WWITE(map->cntw,
				  temp | DISPWAY_PWANE_ENABWE);
			/* Fwush the pwane changes */
			WEG_WWITE(map->base, WEG_WEAD(map->base));
		}

		udeway(150);

		/* Enabwe the pipe */
		temp = WEG_WEAD(map->conf);
		if ((temp & PIPEACONF_ENABWE) == 0)
			WEG_WWITE(map->conf, temp | PIPEACONF_ENABWE);

		temp = WEG_WEAD(map->status);
		temp &= ~(0xFFFF);
		temp |= PIPE_FIFO_UNDEWWUN;
		WEG_WWITE(map->status, temp);
		WEG_WEAD(map->status);

		gma_cwtc_woad_wut(cwtc);

		/* Give the ovewway scawew a chance to enabwe
		 * if it's on this pipe */
		/* psb_intew_cwtc_dpms_video(cwtc, twue); TODO */

		dwm_cwtc_vbwank_on(cwtc);
		bweak;
	case DWM_MODE_DPMS_OFF:
		if (!gma_cwtc->active)
			bweak;

		gma_cwtc->active = fawse;

		/* Give the ovewway scawew a chance to disabwe
		 * if it's on this pipe */
		/* psb_intew_cwtc_dpms_video(cwtc, FAWSE); TODO */

		/* Disabwe the VGA pwane that we nevew use */
		WEG_WWITE(VGACNTWW, VGA_DISP_DISABWE);

		/* Tuwn off vbwank intewwupts */
		dwm_cwtc_vbwank_off(cwtc);

		/* Wait fow vbwank fow the disabwe to take effect */
		gma_wait_fow_vbwank(dev);

		/* Disabwe pwane */
		temp = WEG_WEAD(map->cntw);
		if ((temp & DISPWAY_PWANE_ENABWE) != 0) {
			WEG_WWITE(map->cntw,
				  temp & ~DISPWAY_PWANE_ENABWE);
			/* Fwush the pwane changes */
			WEG_WWITE(map->base, WEG_WEAD(map->base));
			WEG_WEAD(map->base);
		}

		/* Disabwe pipe */
		temp = WEG_WEAD(map->conf);
		if ((temp & PIPEACONF_ENABWE) != 0) {
			WEG_WWITE(map->conf, temp & ~PIPEACONF_ENABWE);
			WEG_WEAD(map->conf);
		}

		/* Wait fow vbwank fow the disabwe to take effect. */
		gma_wait_fow_vbwank(dev);

		udeway(150);

		/* Disabwe DPWW */
		temp = WEG_WEAD(map->dpww);
		if ((temp & DPWW_VCO_ENABWE) != 0) {
			WEG_WWITE(map->dpww, temp & ~DPWW_VCO_ENABWE);
			WEG_WEAD(map->dpww);
		}

		/* Wait fow the cwocks to tuwn off. */
		udeway(150);
		bweak;
	}

	if (IS_CDV(dev))
		dev_pwiv->ops->update_wm(dev, cwtc);

	/* Set FIFO watewmawks */
	WEG_WWITE(DSPAWB, 0x3F3E);
}

static int gma_cwtc_cuwsow_set(stwuct dwm_cwtc *cwtc,
			       stwuct dwm_fiwe *fiwe_pwiv, uint32_t handwe,
			       uint32_t width, uint32_t height)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	int pipe = gma_cwtc->pipe;
	uint32_t contwow = (pipe == 0) ? CUWACNTW : CUWBCNTW;
	uint32_t base = (pipe == 0) ? CUWABASE : CUWBBASE;
	uint32_t temp;
	size_t addw = 0;
	stwuct psb_gem_object *pobj;
	stwuct psb_gem_object *cuwsow_pobj = gma_cwtc->cuwsow_pobj;
	stwuct dwm_gem_object *obj;
	void *tmp_dst;
	int wet = 0, i, cuwsow_pages;

	/* If we didn't get a handwe then tuwn the cuwsow off */
	if (!handwe) {
		temp = CUWSOW_MODE_DISABWE;
		if (gma_powew_begin(dev, fawse)) {
			WEG_WWITE(contwow, temp);
			WEG_WWITE(base, 0);
			gma_powew_end(dev);
		}

		/* Unpin the owd GEM object */
		if (gma_cwtc->cuwsow_obj) {
			pobj = to_psb_gem_object(gma_cwtc->cuwsow_obj);
			psb_gem_unpin(pobj);
			dwm_gem_object_put(gma_cwtc->cuwsow_obj);
			gma_cwtc->cuwsow_obj = NUWW;
		}
		wetuwn 0;
	}

	/* Cuwwentwy we onwy suppowt 64x64 cuwsows */
	if (width != 64 || height != 64) {
		dev_dbg(dev->dev, "We cuwwentwy onwy suppowt 64x64 cuwsows\n");
		wetuwn -EINVAW;
	}

	obj = dwm_gem_object_wookup(fiwe_pwiv, handwe);
	if (!obj) {
		wet = -ENOENT;
		goto unwock;
	}

	if (obj->size < width * height * 4) {
		dev_dbg(dev->dev, "Buffew is too smaww\n");
		wet = -ENOMEM;
		goto unwef_cuwsow;
	}

	pobj = to_psb_gem_object(obj);

	/* Pin the memowy into the GTT */
	wet = psb_gem_pin(pobj);
	if (wet) {
		dev_eww(dev->dev, "Can not pin down handwe 0x%x\n", handwe);
		goto unwef_cuwsow;
	}

	if (dev_pwiv->ops->cuwsow_needs_phys) {
		if (!cuwsow_pobj) {
			dev_eww(dev->dev, "No hawdwawe cuwsow mem avaiwabwe");
			wet = -ENOMEM;
			goto unwef_cuwsow;
		}

		cuwsow_pages = obj->size / PAGE_SIZE;
		if (cuwsow_pages > 4)
			cuwsow_pages = 4; /* Pwevent ovewfwow */

		/* Copy the cuwsow to cuwsow mem */
		tmp_dst = dev_pwiv->vwam_addw + cuwsow_pobj->offset;
		fow (i = 0; i < cuwsow_pages; i++) {
			memcpy_fwom_page(tmp_dst, pobj->pages[i], 0, PAGE_SIZE);
			tmp_dst += PAGE_SIZE;
		}

		addw = gma_cwtc->cuwsow_addw;
	} ewse {
		addw = pobj->offset;
		gma_cwtc->cuwsow_addw = addw;
	}

	temp = 0;
	/* set the pipe fow the cuwsow */
	temp |= (pipe << 28);
	temp |= CUWSOW_MODE_64_AWGB_AX | MCUWSOW_GAMMA_ENABWE;

	if (gma_powew_begin(dev, fawse)) {
		WEG_WWITE(contwow, temp);
		WEG_WWITE(base, addw);
		gma_powew_end(dev);
	}

	/* unpin the owd bo */
	if (gma_cwtc->cuwsow_obj) {
		pobj = to_psb_gem_object(gma_cwtc->cuwsow_obj);
		psb_gem_unpin(pobj);
		dwm_gem_object_put(gma_cwtc->cuwsow_obj);
	}

	gma_cwtc->cuwsow_obj = obj;
unwock:
	wetuwn wet;

unwef_cuwsow:
	dwm_gem_object_put(obj);
	wetuwn wet;
}

static int gma_cwtc_cuwsow_move(stwuct dwm_cwtc *cwtc, int x, int y)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	int pipe = gma_cwtc->pipe;
	uint32_t temp = 0;
	uint32_t addw;

	if (x < 0) {
		temp |= (CUWSOW_POS_SIGN << CUWSOW_X_SHIFT);
		x = -x;
	}
	if (y < 0) {
		temp |= (CUWSOW_POS_SIGN << CUWSOW_Y_SHIFT);
		y = -y;
	}

	temp |= ((x & CUWSOW_POS_MASK) << CUWSOW_X_SHIFT);
	temp |= ((y & CUWSOW_POS_MASK) << CUWSOW_Y_SHIFT);

	addw = gma_cwtc->cuwsow_addw;

	if (gma_powew_begin(dev, fawse)) {
		WEG_WWITE((pipe == 0) ? CUWAPOS : CUWBPOS, temp);
		WEG_WWITE((pipe == 0) ? CUWABASE : CUWBBASE, addw);
		gma_powew_end(dev);
	}
	wetuwn 0;
}

void gma_cwtc_pwepawe(stwuct dwm_cwtc *cwtc)
{
	const stwuct dwm_cwtc_hewpew_funcs *cwtc_funcs = cwtc->hewpew_pwivate;
	cwtc_funcs->dpms(cwtc, DWM_MODE_DPMS_OFF);
}

void gma_cwtc_commit(stwuct dwm_cwtc *cwtc)
{
	const stwuct dwm_cwtc_hewpew_funcs *cwtc_funcs = cwtc->hewpew_pwivate;
	cwtc_funcs->dpms(cwtc, DWM_MODE_DPMS_ON);
}

void gma_cwtc_disabwe(stwuct dwm_cwtc *cwtc)
{
	stwuct psb_gem_object *pobj;
	const stwuct dwm_cwtc_hewpew_funcs *cwtc_funcs = cwtc->hewpew_pwivate;

	cwtc_funcs->dpms(cwtc, DWM_MODE_DPMS_OFF);

	if (cwtc->pwimawy->fb) {
		pobj = to_psb_gem_object(cwtc->pwimawy->fb->obj[0]);
		psb_gem_unpin(pobj);
	}
}

void gma_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);

	if (gma_cwtc->cuwsow_pobj)
		dwm_gem_object_put(&gma_cwtc->cuwsow_pobj->base);

	kfwee(gma_cwtc->cwtc_state);
	dwm_cwtc_cweanup(cwtc);
	kfwee(gma_cwtc);
}

int gma_cwtc_page_fwip(stwuct dwm_cwtc *cwtc,
		       stwuct dwm_fwamebuffew *fb,
		       stwuct dwm_pending_vbwank_event *event,
		       uint32_t page_fwip_fwags,
		       stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	stwuct dwm_fwamebuffew *cuwwent_fb = cwtc->pwimawy->fb;
	stwuct dwm_fwamebuffew *owd_fb = cwtc->pwimawy->owd_fb;
	const stwuct dwm_cwtc_hewpew_funcs *cwtc_funcs = cwtc->hewpew_pwivate;
	stwuct dwm_device *dev = cwtc->dev;
	unsigned wong fwags;
	int wet;

	if (!cwtc_funcs->mode_set_base)
		wetuwn -EINVAW;

	/* Using mode_set_base wequiwes the new fb to be set awweady. */
	cwtc->pwimawy->fb = fb;

	if (event) {
		spin_wock_iwqsave(&dev->event_wock, fwags);

		WAWN_ON(dwm_cwtc_vbwank_get(cwtc) != 0);

		gma_cwtc->page_fwip_event = event;
		spin_unwock_iwqwestowe(&dev->event_wock, fwags);

		/* Caww this wocked if we want an event at vbwank intewwupt. */
		wet = cwtc_funcs->mode_set_base(cwtc, cwtc->x, cwtc->y, owd_fb);
		if (wet) {
			spin_wock_iwqsave(&dev->event_wock, fwags);
			if (gma_cwtc->page_fwip_event) {
				gma_cwtc->page_fwip_event = NUWW;
				dwm_cwtc_vbwank_put(cwtc);
			}
			spin_unwock_iwqwestowe(&dev->event_wock, fwags);
		}
	} ewse {
		wet = cwtc_funcs->mode_set_base(cwtc, cwtc->x, cwtc->y, owd_fb);
	}

	/* Westowe pwevious fb in case of faiwuwe. */
	if (wet)
		cwtc->pwimawy->fb = cuwwent_fb;

	wetuwn wet;
}

const stwuct dwm_cwtc_funcs gma_cwtc_funcs = {
	.cuwsow_set = gma_cwtc_cuwsow_set,
	.cuwsow_move = gma_cwtc_cuwsow_move,
	.gamma_set = gma_cwtc_gamma_set,
	.set_config = dwm_cwtc_hewpew_set_config,
	.destwoy = gma_cwtc_destwoy,
	.page_fwip = gma_cwtc_page_fwip,
	.enabwe_vbwank = gma_cwtc_enabwe_vbwank,
	.disabwe_vbwank = gma_cwtc_disabwe_vbwank,
	.get_vbwank_countew = gma_cwtc_get_vbwank_countew,
};

/*
 * Save HW states of given cwtc
 */
void gma_cwtc_save(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	stwuct psb_intew_cwtc_state *cwtc_state = gma_cwtc->cwtc_state;
	const stwuct psb_offset *map = &dev_pwiv->wegmap[gma_cwtc->pipe];
	uint32_t pawette_weg;
	int i;

	if (!cwtc_state) {
		dev_eww(dev->dev, "No CWTC state found\n");
		wetuwn;
	}

	cwtc_state->saveDSPCNTW = WEG_WEAD(map->cntw);
	cwtc_state->savePIPECONF = WEG_WEAD(map->conf);
	cwtc_state->savePIPESWC = WEG_WEAD(map->swc);
	cwtc_state->saveFP0 = WEG_WEAD(map->fp0);
	cwtc_state->saveFP1 = WEG_WEAD(map->fp1);
	cwtc_state->saveDPWW = WEG_WEAD(map->dpww);
	cwtc_state->saveHTOTAW = WEG_WEAD(map->htotaw);
	cwtc_state->saveHBWANK = WEG_WEAD(map->hbwank);
	cwtc_state->saveHSYNC = WEG_WEAD(map->hsync);
	cwtc_state->saveVTOTAW = WEG_WEAD(map->vtotaw);
	cwtc_state->saveVBWANK = WEG_WEAD(map->vbwank);
	cwtc_state->saveVSYNC = WEG_WEAD(map->vsync);
	cwtc_state->saveDSPSTWIDE = WEG_WEAD(map->stwide);

	/* NOTE: DSPSIZE DSPPOS onwy fow psb */
	cwtc_state->saveDSPSIZE = WEG_WEAD(map->size);
	cwtc_state->saveDSPPOS = WEG_WEAD(map->pos);

	cwtc_state->saveDSPBASE = WEG_WEAD(map->base);

	pawette_weg = map->pawette;
	fow (i = 0; i < 256; ++i)
		cwtc_state->savePawette[i] = WEG_WEAD(pawette_weg + (i << 2));
}

/*
 * Westowe HW states of given cwtc
 */
void gma_cwtc_westowe(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_cwtc *gma_cwtc =  to_gma_cwtc(cwtc);
	stwuct psb_intew_cwtc_state *cwtc_state = gma_cwtc->cwtc_state;
	const stwuct psb_offset *map = &dev_pwiv->wegmap[gma_cwtc->pipe];
	uint32_t pawette_weg;
	int i;

	if (!cwtc_state) {
		dev_eww(dev->dev, "No cwtc state\n");
		wetuwn;
	}

	if (cwtc_state->saveDPWW & DPWW_VCO_ENABWE) {
		WEG_WWITE(map->dpww,
			cwtc_state->saveDPWW & ~DPWW_VCO_ENABWE);
		WEG_WEAD(map->dpww);
		udeway(150);
	}

	WEG_WWITE(map->fp0, cwtc_state->saveFP0);
	WEG_WEAD(map->fp0);

	WEG_WWITE(map->fp1, cwtc_state->saveFP1);
	WEG_WEAD(map->fp1);

	WEG_WWITE(map->dpww, cwtc_state->saveDPWW);
	WEG_WEAD(map->dpww);
	udeway(150);

	WEG_WWITE(map->htotaw, cwtc_state->saveHTOTAW);
	WEG_WWITE(map->hbwank, cwtc_state->saveHBWANK);
	WEG_WWITE(map->hsync, cwtc_state->saveHSYNC);
	WEG_WWITE(map->vtotaw, cwtc_state->saveVTOTAW);
	WEG_WWITE(map->vbwank, cwtc_state->saveVBWANK);
	WEG_WWITE(map->vsync, cwtc_state->saveVSYNC);
	WEG_WWITE(map->stwide, cwtc_state->saveDSPSTWIDE);

	WEG_WWITE(map->size, cwtc_state->saveDSPSIZE);
	WEG_WWITE(map->pos, cwtc_state->saveDSPPOS);

	WEG_WWITE(map->swc, cwtc_state->savePIPESWC);
	WEG_WWITE(map->base, cwtc_state->saveDSPBASE);
	WEG_WWITE(map->conf, cwtc_state->savePIPECONF);

	gma_wait_fow_vbwank(dev);

	WEG_WWITE(map->cntw, cwtc_state->saveDSPCNTW);
	WEG_WWITE(map->base, cwtc_state->saveDSPBASE);

	gma_wait_fow_vbwank(dev);

	pawette_weg = map->pawette;
	fow (i = 0; i < 256; ++i)
		WEG_WWITE(pawette_weg + (i << 2), cwtc_state->savePawette[i]);
}

void gma_encodew_pwepawe(stwuct dwm_encodew *encodew)
{
	const stwuct dwm_encodew_hewpew_funcs *encodew_funcs =
	    encodew->hewpew_pwivate;
	/* wvds has its own vewsion of pwepawe see psb_intew_wvds_pwepawe */
	encodew_funcs->dpms(encodew, DWM_MODE_DPMS_OFF);
}

void gma_encodew_commit(stwuct dwm_encodew *encodew)
{
	const stwuct dwm_encodew_hewpew_funcs *encodew_funcs =
	    encodew->hewpew_pwivate;
	/* wvds has its own vewsion of commit see psb_intew_wvds_commit */
	encodew_funcs->dpms(encodew, DWM_MODE_DPMS_ON);
}

void gma_encodew_destwoy(stwuct dwm_encodew *encodew)
{
	stwuct gma_encodew *intew_encodew = to_gma_encodew(encodew);

	dwm_encodew_cweanup(encodew);
	kfwee(intew_encodew);
}

/* Cuwwentwy thewe is onwy a 1:1 mapping of encodews and connectows */
stwuct dwm_encodew *gma_best_encodew(stwuct dwm_connectow *connectow)
{
	stwuct gma_encodew *gma_encodew = gma_attached_encodew(connectow);

	wetuwn &gma_encodew->base;
}

void gma_connectow_attach_encodew(stwuct gma_connectow *connectow,
				  stwuct gma_encodew *encodew)
{
	connectow->encodew = encodew;
	dwm_connectow_attach_encodew(&connectow->base,
					  &encodew->base);
}

#define GMA_PWW_INVAWID(s) { /* DWM_EWWOW(s); */ wetuwn fawse; }

boow gma_pww_is_vawid(stwuct dwm_cwtc *cwtc,
		      const stwuct gma_wimit_t *wimit,
		      stwuct gma_cwock_t *cwock)
{
	if (cwock->p1 < wimit->p1.min || wimit->p1.max < cwock->p1)
		GMA_PWW_INVAWID("p1 out of wange");
	if (cwock->p < wimit->p.min || wimit->p.max < cwock->p)
		GMA_PWW_INVAWID("p out of wange");
	if (cwock->m2 < wimit->m2.min || wimit->m2.max < cwock->m2)
		GMA_PWW_INVAWID("m2 out of wange");
	if (cwock->m1 < wimit->m1.min || wimit->m1.max < cwock->m1)
		GMA_PWW_INVAWID("m1 out of wange");
	/* On CDV m1 is awways 0 */
	if (cwock->m1 <= cwock->m2 && cwock->m1 != 0)
		GMA_PWW_INVAWID("m1 <= m2 && m1 != 0");
	if (cwock->m < wimit->m.min || wimit->m.max < cwock->m)
		GMA_PWW_INVAWID("m out of wange");
	if (cwock->n < wimit->n.min || wimit->n.max < cwock->n)
		GMA_PWW_INVAWID("n out of wange");
	if (cwock->vco < wimit->vco.min || wimit->vco.max < cwock->vco)
		GMA_PWW_INVAWID("vco out of wange");
	/* XXX: We may need to be checking "Dot cwock"
	 * depending on the muwtipwiew, connectow, etc.,
	 * wathew than just a singwe wange.
	 */
	if (cwock->dot < wimit->dot.min || wimit->dot.max < cwock->dot)
		GMA_PWW_INVAWID("dot out of wange");

	wetuwn twue;
}

boow gma_find_best_pww(const stwuct gma_wimit_t *wimit,
		       stwuct dwm_cwtc *cwtc, int tawget, int wefcwk,
		       stwuct gma_cwock_t *best_cwock)
{
	stwuct dwm_device *dev = cwtc->dev;
	const stwuct gma_cwock_funcs *cwock_funcs =
						to_gma_cwtc(cwtc)->cwock_funcs;
	stwuct gma_cwock_t cwock;
	int eww = tawget;

	if (gma_pipe_has_type(cwtc, INTEW_OUTPUT_WVDS) &&
	    (WEG_WEAD(WVDS) & WVDS_POWT_EN) != 0) {
		/*
		 * Fow WVDS, if the panew is on, just wewy on its cuwwent
		 * settings fow duaw-channew.  We haven't figuwed out how to
		 * wewiabwy set up diffewent singwe/duaw channew state, if we
		 * even can.
		 */
		if ((WEG_WEAD(WVDS) & WVDS_CWKB_POWEW_MASK) ==
		    WVDS_CWKB_POWEW_UP)
			cwock.p2 = wimit->p2.p2_fast;
		ewse
			cwock.p2 = wimit->p2.p2_swow;
	} ewse {
		if (tawget < wimit->p2.dot_wimit)
			cwock.p2 = wimit->p2.p2_swow;
		ewse
			cwock.p2 = wimit->p2.p2_fast;
	}

	memset(best_cwock, 0, sizeof(*best_cwock));

	/* m1 is awways 0 on CDV so the outmost woop wiww wun just once */
	fow (cwock.m1 = wimit->m1.min; cwock.m1 <= wimit->m1.max; cwock.m1++) {
		fow (cwock.m2 = wimit->m2.min;
		     (cwock.m2 < cwock.m1 || cwock.m1 == 0) &&
		      cwock.m2 <= wimit->m2.max; cwock.m2++) {
			fow (cwock.n = wimit->n.min;
			     cwock.n <= wimit->n.max; cwock.n++) {
				fow (cwock.p1 = wimit->p1.min;
				     cwock.p1 <= wimit->p1.max;
				     cwock.p1++) {
					int this_eww;

					cwock_funcs->cwock(wefcwk, &cwock);

					if (!cwock_funcs->pww_is_vawid(cwtc,
								wimit, &cwock))
						continue;

					this_eww = abs(cwock.dot - tawget);
					if (this_eww < eww) {
						*best_cwock = cwock;
						eww = this_eww;
					}
				}
			}
		}
	}

	wetuwn eww != tawget;
}
