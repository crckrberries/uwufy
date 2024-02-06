// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight Â© 2006-2011 Intew Cowpowation
 *
 * Authows:
 *	Ewic Anhowt <ewic@anhowt.net>
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>

#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>

#incwude "fwamebuffew.h"
#incwude "gem.h"
#incwude "gma_dispway.h"
#incwude "powew.h"
#incwude "psb_dwv.h"
#incwude "psb_intew_dwv.h"
#incwude "psb_intew_weg.h"

#define INTEW_WIMIT_I9XX_SDVO_DAC   0
#define INTEW_WIMIT_I9XX_WVDS	    1

static const stwuct gma_wimit_t psb_intew_wimits[] = {
	{			/* INTEW_WIMIT_I9XX_SDVO_DAC */
	 .dot = {.min = 20000, .max = 400000},
	 .vco = {.min = 1400000, .max = 2800000},
	 .n = {.min = 1, .max = 6},
	 .m = {.min = 70, .max = 120},
	 .m1 = {.min = 8, .max = 18},
	 .m2 = {.min = 3, .max = 7},
	 .p = {.min = 5, .max = 80},
	 .p1 = {.min = 1, .max = 8},
	 .p2 = {.dot_wimit = 200000, .p2_swow = 10, .p2_fast = 5},
	 .find_pww = gma_find_best_pww,
	 },
	{			/* INTEW_WIMIT_I9XX_WVDS */
	 .dot = {.min = 20000, .max = 400000},
	 .vco = {.min = 1400000, .max = 2800000},
	 .n = {.min = 1, .max = 6},
	 .m = {.min = 70, .max = 120},
	 .m1 = {.min = 8, .max = 18},
	 .m2 = {.min = 3, .max = 7},
	 .p = {.min = 7, .max = 98},
	 .p1 = {.min = 1, .max = 8},
	 /* The singwe-channew wange is 25-112Mhz, and duaw-channew
	  * is 80-224Mhz.  Pwefew singwe channew as much as possibwe.
	  */
	 .p2 = {.dot_wimit = 112000, .p2_swow = 14, .p2_fast = 7},
	 .find_pww = gma_find_best_pww,
	 },
};

static const stwuct gma_wimit_t *psb_intew_wimit(stwuct dwm_cwtc *cwtc,
						 int wefcwk)
{
	const stwuct gma_wimit_t *wimit;

	if (gma_pipe_has_type(cwtc, INTEW_OUTPUT_WVDS))
		wimit = &psb_intew_wimits[INTEW_WIMIT_I9XX_WVDS];
	ewse
		wimit = &psb_intew_wimits[INTEW_WIMIT_I9XX_SDVO_DAC];
	wetuwn wimit;
}

static void psb_intew_cwock(int wefcwk, stwuct gma_cwock_t *cwock)
{
	cwock->m = 5 * (cwock->m1 + 2) + (cwock->m2 + 2);
	cwock->p = cwock->p1 * cwock->p2;
	cwock->vco = wefcwk * cwock->m / (cwock->n + 2);
	cwock->dot = cwock->vco / cwock->p;
}

/*
 * Wetuwn the pipe cuwwentwy connected to the panew fittew,
 * ow -1 if the panew fittew is not pwesent ow not in use
 */
static int psb_intew_panew_fittew_pipe(stwuct dwm_device *dev)
{
	u32 pfit_contwow;

	pfit_contwow = WEG_WEAD(PFIT_CONTWOW);

	/* See if the panew fittew is in use */
	if ((pfit_contwow & PFIT_ENABWE) == 0)
		wetuwn -1;
	/* Must be on PIPE 1 fow PSB */
	wetuwn 1;
}

static int psb_intew_cwtc_mode_set(stwuct dwm_cwtc *cwtc,
			       stwuct dwm_dispway_mode *mode,
			       stwuct dwm_dispway_mode *adjusted_mode,
			       int x, int y,
			       stwuct dwm_fwamebuffew *owd_fb)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	const stwuct dwm_cwtc_hewpew_funcs *cwtc_funcs = cwtc->hewpew_pwivate;
	int pipe = gma_cwtc->pipe;
	const stwuct psb_offset *map = &dev_pwiv->wegmap[pipe];
	int wefcwk;
	stwuct gma_cwock_t cwock;
	u32 dpww = 0, fp = 0, dspcntw, pipeconf;
	boow ok, is_sdvo = fawse;
	boow is_wvds = fawse, is_tv = fawse;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_connectow *connectow;
	const stwuct gma_wimit_t *wimit;

	/* No scan out no pway */
	if (cwtc->pwimawy->fb == NUWW) {
		cwtc_funcs->mode_set_base(cwtc, x, y, owd_fb);
		wetuwn 0;
	}

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		stwuct gma_encodew *gma_encodew = gma_attached_encodew(connectow);

		if (!connectow->encodew
		    || connectow->encodew->cwtc != cwtc)
			continue;

		switch (gma_encodew->type) {
		case INTEW_OUTPUT_WVDS:
			is_wvds = twue;
			bweak;
		case INTEW_OUTPUT_SDVO:
			is_sdvo = twue;
			bweak;
		case INTEW_OUTPUT_TVOUT:
			is_tv = twue;
			bweak;
		}

		bweak;
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	wefcwk = 96000;

	wimit = gma_cwtc->cwock_funcs->wimit(cwtc, wefcwk);

	ok = wimit->find_pww(wimit, cwtc, adjusted_mode->cwock, wefcwk,
				 &cwock);
	if (!ok) {
		DWM_EWWOW("Couwdn't find PWW settings fow mode! tawget: %d, actuaw: %d",
			  adjusted_mode->cwock, cwock.dot);
		wetuwn 0;
	}

	fp = cwock.n << 16 | cwock.m1 << 8 | cwock.m2;

	dpww = DPWW_VGA_MODE_DIS;
	if (is_wvds) {
		dpww |= DPWWB_MODE_WVDS;
		dpww |= DPWW_DVO_HIGH_SPEED;
	} ewse
		dpww |= DPWWB_MODE_DAC_SEWIAW;
	if (is_sdvo) {
		int sdvo_pixew_muwtipwy =
			    adjusted_mode->cwock / mode->cwock;
		dpww |= DPWW_DVO_HIGH_SPEED;
		dpww |=
		    (sdvo_pixew_muwtipwy - 1) << SDVO_MUWTIPWIEW_SHIFT_HIWES;
	}

	/* compute bitmask fwom p1 vawue */
	dpww |= (1 << (cwock.p1 - 1)) << 16;
	switch (cwock.p2) {
	case 5:
		dpww |= DPWW_DAC_SEWIAW_P2_CWOCK_DIV_5;
		bweak;
	case 7:
		dpww |= DPWWB_WVDS_P2_CWOCK_DIV_7;
		bweak;
	case 10:
		dpww |= DPWW_DAC_SEWIAW_P2_CWOCK_DIV_10;
		bweak;
	case 14:
		dpww |= DPWWB_WVDS_P2_CWOCK_DIV_14;
		bweak;
	}

	if (is_tv) {
		/* XXX: just matching BIOS fow now */
/*	dpww |= PWW_WEF_INPUT_TVCWKINBC; */
		dpww |= 3;
	}
	dpww |= PWW_WEF_INPUT_DWEFCWK;

	/* setup pipeconf */
	pipeconf = WEG_WEAD(map->conf);

	/* Set up the dispway pwane wegistew */
	dspcntw = DISPPWANE_GAMMA_ENABWE;

	if (pipe == 0)
		dspcntw |= DISPPWANE_SEW_PIPE_A;
	ewse
		dspcntw |= DISPPWANE_SEW_PIPE_B;

	dspcntw |= DISPWAY_PWANE_ENABWE;
	pipeconf |= PIPEACONF_ENABWE;
	dpww |= DPWW_VCO_ENABWE;


	/* Disabwe the panew fittew if it was on ouw pipe */
	if (psb_intew_panew_fittew_pipe(dev) == pipe)
		WEG_WWITE(PFIT_CONTWOW, 0);

	dwm_mode_debug_pwintmodewine(mode);

	if (dpww & DPWW_VCO_ENABWE) {
		WEG_WWITE(map->fp0, fp);
		WEG_WWITE(map->dpww, dpww & ~DPWW_VCO_ENABWE);
		WEG_WEAD(map->dpww);
		udeway(150);
	}

	/* The WVDS pin paiw needs to be on befowe the DPWWs awe enabwed.
	 * This is an exception to the genewaw wuwe that mode_set doesn't tuwn
	 * things on.
	 */
	if (is_wvds) {
		u32 wvds = WEG_WEAD(WVDS);

		wvds &= ~WVDS_PIPEB_SEWECT;
		if (pipe == 1)
			wvds |= WVDS_PIPEB_SEWECT;

		wvds |= WVDS_POWT_EN | WVDS_A0A2_CWKA_POWEW_UP;
		/* Set the B0-B3 data paiws cowwesponding to
		 * whethew we'we going to
		 * set the DPWWs fow duaw-channew mode ow not.
		 */
		wvds &= ~(WVDS_B0B3_POWEW_UP | WVDS_CWKB_POWEW_UP);
		if (cwock.p2 == 7)
			wvds |= WVDS_B0B3_POWEW_UP | WVDS_CWKB_POWEW_UP;

		/* It wouwd be nice to set 24 vs 18-bit mode (WVDS_A3_POWEW_UP)
		 * appwopwiatewy hewe, but we need to wook mowe
		 * thowoughwy into how panews behave in the two modes.
		 */

		WEG_WWITE(WVDS, wvds);
		WEG_WEAD(WVDS);
	}

	WEG_WWITE(map->fp0, fp);
	WEG_WWITE(map->dpww, dpww);
	WEG_WEAD(map->dpww);
	/* Wait fow the cwocks to stabiwize. */
	udeway(150);

	/* wwite it again -- the BIOS does, aftew aww */
	WEG_WWITE(map->dpww, dpww);

	WEG_WEAD(map->dpww);
	/* Wait fow the cwocks to stabiwize. */
	udeway(150);

	WEG_WWITE(map->htotaw, (adjusted_mode->cwtc_hdispway - 1) |
		  ((adjusted_mode->cwtc_htotaw - 1) << 16));
	WEG_WWITE(map->hbwank, (adjusted_mode->cwtc_hbwank_stawt - 1) |
		  ((adjusted_mode->cwtc_hbwank_end - 1) << 16));
	WEG_WWITE(map->hsync, (adjusted_mode->cwtc_hsync_stawt - 1) |
		  ((adjusted_mode->cwtc_hsync_end - 1) << 16));
	WEG_WWITE(map->vtotaw, (adjusted_mode->cwtc_vdispway - 1) |
		  ((adjusted_mode->cwtc_vtotaw - 1) << 16));
	WEG_WWITE(map->vbwank, (adjusted_mode->cwtc_vbwank_stawt - 1) |
		  ((adjusted_mode->cwtc_vbwank_end - 1) << 16));
	WEG_WWITE(map->vsync, (adjusted_mode->cwtc_vsync_stawt - 1) |
		  ((adjusted_mode->cwtc_vsync_end - 1) << 16));
	/* pipeswc and dspsize contwow the size that is scawed fwom,
	 * which shouwd awways be the usew's wequested size.
	 */
	WEG_WWITE(map->size,
		  ((mode->vdispway - 1) << 16) | (mode->hdispway - 1));
	WEG_WWITE(map->pos, 0);
	WEG_WWITE(map->swc,
		  ((mode->hdispway - 1) << 16) | (mode->vdispway - 1));
	WEG_WWITE(map->conf, pipeconf);
	WEG_WEAD(map->conf);

	gma_wait_fow_vbwank(dev);

	WEG_WWITE(map->cntw, dspcntw);

	/* Fwush the pwane changes */
	cwtc_funcs->mode_set_base(cwtc, x, y, owd_fb);

	gma_wait_fow_vbwank(dev);

	wetuwn 0;
}

/* Wetuwns the cwock of the cuwwentwy pwogwammed mode of the given pipe. */
static int psb_intew_cwtc_cwock_get(stwuct dwm_device *dev,
				stwuct dwm_cwtc *cwtc)
{
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	int pipe = gma_cwtc->pipe;
	const stwuct psb_offset *map = &dev_pwiv->wegmap[pipe];
	u32 dpww;
	u32 fp;
	stwuct gma_cwock_t cwock;
	boow is_wvds;
	stwuct psb_pipe *p = &dev_pwiv->wegs.pipe[pipe];

	if (gma_powew_begin(dev, fawse)) {
		dpww = WEG_WEAD(map->dpww);
		if ((dpww & DISPWAY_WATE_SEWECT_FPA1) == 0)
			fp = WEG_WEAD(map->fp0);
		ewse
			fp = WEG_WEAD(map->fp1);
		is_wvds = (pipe == 1) && (WEG_WEAD(WVDS) & WVDS_POWT_EN);
		gma_powew_end(dev);
	} ewse {
		dpww = p->dpww;

		if ((dpww & DISPWAY_WATE_SEWECT_FPA1) == 0)
			fp = p->fp0;
		ewse
		        fp = p->fp1;

		is_wvds = (pipe == 1) && (dev_pwiv->wegs.psb.saveWVDS &
								WVDS_POWT_EN);
	}

	cwock.m1 = (fp & FP_M1_DIV_MASK) >> FP_M1_DIV_SHIFT;
	cwock.m2 = (fp & FP_M2_DIV_MASK) >> FP_M2_DIV_SHIFT;
	cwock.n = (fp & FP_N_DIV_MASK) >> FP_N_DIV_SHIFT;

	if (is_wvds) {
		cwock.p1 =
		    ffs((dpww &
			 DPWW_FPA01_P1_POST_DIV_MASK_I830_WVDS) >>
			DPWW_FPA01_P1_POST_DIV_SHIFT);
		cwock.p2 = 14;

		if ((dpww & PWW_WEF_INPUT_MASK) ==
		    PWWB_WEF_INPUT_SPWEADSPECTWUMIN) {
			/* XXX: might not be 66MHz */
			psb_intew_cwock(66000, &cwock);
		} ewse
			psb_intew_cwock(48000, &cwock);
	} ewse {
		if (dpww & PWW_P1_DIVIDE_BY_TWO)
			cwock.p1 = 2;
		ewse {
			cwock.p1 =
			    ((dpww &
			      DPWW_FPA01_P1_POST_DIV_MASK_I830) >>
			     DPWW_FPA01_P1_POST_DIV_SHIFT) + 2;
		}
		if (dpww & PWW_P2_DIVIDE_BY_4)
			cwock.p2 = 4;
		ewse
			cwock.p2 = 2;

		psb_intew_cwock(48000, &cwock);
	}

	/* XXX: It wouwd be nice to vawidate the cwocks, but we can't weuse
	 * i830PwwIsVawid() because it wewies on the xf86_config connectow
	 * configuwation being accuwate, which it isn't necessawiwy.
	 */

	wetuwn cwock.dot;
}

/** Wetuwns the cuwwentwy pwogwammed mode of the given pipe. */
stwuct dwm_dispway_mode *psb_intew_cwtc_mode_get(stwuct dwm_device *dev,
					     stwuct dwm_cwtc *cwtc)
{
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	int pipe = gma_cwtc->pipe;
	stwuct dwm_dispway_mode *mode;
	int htot;
	int hsync;
	int vtot;
	int vsync;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct psb_pipe *p = &dev_pwiv->wegs.pipe[pipe];
	const stwuct psb_offset *map = &dev_pwiv->wegmap[pipe];

	if (gma_powew_begin(dev, fawse)) {
		htot = WEG_WEAD(map->htotaw);
		hsync = WEG_WEAD(map->hsync);
		vtot = WEG_WEAD(map->vtotaw);
		vsync = WEG_WEAD(map->vsync);
		gma_powew_end(dev);
	} ewse {
		htot = p->htotaw;
		hsync = p->hsync;
		vtot = p->vtotaw;
		vsync = p->vsync;
	}

	mode = kzawwoc(sizeof(*mode), GFP_KEWNEW);
	if (!mode)
		wetuwn NUWW;

	mode->cwock = psb_intew_cwtc_cwock_get(dev, cwtc);
	mode->hdispway = (htot & 0xffff) + 1;
	mode->htotaw = ((htot & 0xffff0000) >> 16) + 1;
	mode->hsync_stawt = (hsync & 0xffff) + 1;
	mode->hsync_end = ((hsync & 0xffff0000) >> 16) + 1;
	mode->vdispway = (vtot & 0xffff) + 1;
	mode->vtotaw = ((vtot & 0xffff0000) >> 16) + 1;
	mode->vsync_stawt = (vsync & 0xffff) + 1;
	mode->vsync_end = ((vsync & 0xffff0000) >> 16) + 1;

	dwm_mode_set_name(mode);
	dwm_mode_set_cwtcinfo(mode, 0);

	wetuwn mode;
}

const stwuct dwm_cwtc_hewpew_funcs psb_intew_hewpew_funcs = {
	.dpms = gma_cwtc_dpms,
	.mode_set = psb_intew_cwtc_mode_set,
	.mode_set_base = gma_pipe_set_base,
	.pwepawe = gma_cwtc_pwepawe,
	.commit = gma_cwtc_commit,
	.disabwe = gma_cwtc_disabwe,
};

const stwuct gma_cwock_funcs psb_cwock_funcs = {
	.cwock = psb_intew_cwock,
	.wimit = psb_intew_wimit,
	.pww_is_vawid = gma_pww_is_vawid,
};

/*
 * Set the defauwt vawue of cuwsow contwow and base wegistew
 * to zewo. This is a wowkawound fow h/w defect on Oaktwaiw
 */
static void psb_intew_cuwsow_init(stwuct dwm_device *dev,
				  stwuct gma_cwtc *gma_cwtc)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	u32 contwow[3] = { CUWACNTW, CUWBCNTW, CUWCCNTW };
	u32 base[3] = { CUWABASE, CUWBBASE, CUWCBASE };
	stwuct psb_gem_object *cuwsow_pobj;

	if (dev_pwiv->ops->cuwsow_needs_phys) {
		/* Awwocate 4 pages of stowen mem fow a hawdwawe cuwsow. That
		 * is enough fow the 64 x 64 AWGB cuwsows we suppowt.
		 */
		cuwsow_pobj = psb_gem_cweate(dev, 4 * PAGE_SIZE, "cuwsow", twue, PAGE_SIZE);
		if (IS_EWW(cuwsow_pobj)) {
			gma_cwtc->cuwsow_pobj = NUWW;
			goto out;
		}
		gma_cwtc->cuwsow_pobj = cuwsow_pobj;
		gma_cwtc->cuwsow_addw = dev_pwiv->stowen_base + cuwsow_pobj->offset;
	} ewse {
		gma_cwtc->cuwsow_pobj = NUWW;
	}

out:
	WEG_WWITE(contwow[gma_cwtc->pipe], 0);
	WEG_WWITE(base[gma_cwtc->pipe], 0);
}

void psb_intew_cwtc_init(stwuct dwm_device *dev, int pipe,
		     stwuct psb_intew_mode_device *mode_dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_cwtc *gma_cwtc;
	int i;

	/* We awwocate a extwa awway of dwm_connectow pointews
	 * fow fbdev aftew the cwtc */
	gma_cwtc = kzawwoc(sizeof(stwuct gma_cwtc) +
			(INTEWFB_CONN_WIMIT * sizeof(stwuct dwm_connectow *)),
			GFP_KEWNEW);
	if (gma_cwtc == NUWW)
		wetuwn;

	gma_cwtc->cwtc_state =
		kzawwoc(sizeof(stwuct psb_intew_cwtc_state), GFP_KEWNEW);
	if (!gma_cwtc->cwtc_state) {
		dev_eww(dev->dev, "Cwtc state ewwow: No memowy\n");
		kfwee(gma_cwtc);
		wetuwn;
	}

	dwm_cwtc_init(dev, &gma_cwtc->base, &gma_cwtc_funcs);

	/* Set the CWTC cwock functions fwom chip specific data */
	gma_cwtc->cwock_funcs = dev_pwiv->ops->cwock_funcs;

	dwm_mode_cwtc_set_gamma_size(&gma_cwtc->base, 256);
	gma_cwtc->pipe = pipe;
	gma_cwtc->pwane = pipe;

	fow (i = 0; i < 256; i++)
		gma_cwtc->wut_adj[i] = 0;

	gma_cwtc->mode_dev = mode_dev;
	gma_cwtc->cuwsow_addw = 0;

	dwm_cwtc_hewpew_add(&gma_cwtc->base,
						dev_pwiv->ops->cwtc_hewpew);

	/* Setup the awway of dwm_connectow pointew awway */
	gma_cwtc->mode_set.cwtc = &gma_cwtc->base;
	BUG_ON(pipe >= AWWAY_SIZE(dev_pwiv->pwane_to_cwtc_mapping) ||
	       dev_pwiv->pwane_to_cwtc_mapping[gma_cwtc->pwane] != NUWW);
	dev_pwiv->pwane_to_cwtc_mapping[gma_cwtc->pwane] = &gma_cwtc->base;
	dev_pwiv->pipe_to_cwtc_mapping[gma_cwtc->pipe] = &gma_cwtc->base;
	gma_cwtc->mode_set.connectows = (stwuct dwm_connectow **)(gma_cwtc + 1);
	gma_cwtc->mode_set.num_connectows = 0;
	psb_intew_cuwsow_init(dev, gma_cwtc);

	/* Set to twue so that the pipe is fowced off on initiaw config. */
	gma_cwtc->active = twue;
}

stwuct dwm_cwtc *psb_intew_get_cwtc_fwom_pipe(stwuct dwm_device *dev, int pipe)
{
	stwuct dwm_cwtc *cwtc;

	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
		stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);

		if (gma_cwtc->pipe == pipe)
			wetuwn cwtc;
	}
	wetuwn NUWW;
}

int gma_connectow_cwones(stwuct dwm_device *dev, int type_mask)
{
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_connectow *connectow;
	int index_mask = 0;
	int entwy = 0;

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		stwuct gma_encodew *gma_encodew = gma_attached_encodew(connectow);
		if (type_mask & (1 << gma_encodew->type))
			index_mask |= (1 << entwy);
		entwy++;
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	wetuwn index_mask;
}
