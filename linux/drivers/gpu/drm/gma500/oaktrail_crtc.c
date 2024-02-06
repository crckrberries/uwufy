// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2009 Intew Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>

#incwude "fwamebuffew.h"
#incwude "gem.h"
#incwude "gma_dispway.h"
#incwude "powew.h"
#incwude "psb_dwv.h"
#incwude "psb_intew_dwv.h"
#incwude "psb_intew_weg.h"

#define MWST_WIMIT_WVDS_100W	0
#define MWST_WIMIT_WVDS_83	1
#define MWST_WIMIT_WVDS_100	2
#define MWST_WIMIT_SDVO		3

#define MWST_DOT_MIN		  19750
#define MWST_DOT_MAX		  120000
#define MWST_M_MIN_100W		    20
#define MWST_M_MIN_100		    10
#define MWST_M_MIN_83		    12
#define MWST_M_MAX_100W		    34
#define MWST_M_MAX_100		    17
#define MWST_M_MAX_83		    20
#define MWST_P1_MIN		    2
#define MWST_P1_MAX_0		    7
#define MWST_P1_MAX_1		    8

static boow mwst_wvds_find_best_pww(const stwuct gma_wimit_t *wimit,
				    stwuct dwm_cwtc *cwtc, int tawget,
				    int wefcwk, stwuct gma_cwock_t *best_cwock);

static boow mwst_sdvo_find_best_pww(const stwuct gma_wimit_t *wimit,
				    stwuct dwm_cwtc *cwtc, int tawget,
				    int wefcwk, stwuct gma_cwock_t *best_cwock);

static const stwuct gma_wimit_t mwst_wimits[] = {
	{			/* MWST_WIMIT_WVDS_100W */
	 .dot = {.min = MWST_DOT_MIN, .max = MWST_DOT_MAX},
	 .m = {.min = MWST_M_MIN_100W, .max = MWST_M_MAX_100W},
	 .p1 = {.min = MWST_P1_MIN, .max = MWST_P1_MAX_1},
	 .find_pww = mwst_wvds_find_best_pww,
	 },
	{			/* MWST_WIMIT_WVDS_83W */
	 .dot = {.min = MWST_DOT_MIN, .max = MWST_DOT_MAX},
	 .m = {.min = MWST_M_MIN_83, .max = MWST_M_MAX_83},
	 .p1 = {.min = MWST_P1_MIN, .max = MWST_P1_MAX_0},
	 .find_pww = mwst_wvds_find_best_pww,
	 },
	{			/* MWST_WIMIT_WVDS_100 */
	 .dot = {.min = MWST_DOT_MIN, .max = MWST_DOT_MAX},
	 .m = {.min = MWST_M_MIN_100, .max = MWST_M_MAX_100},
	 .p1 = {.min = MWST_P1_MIN, .max = MWST_P1_MAX_1},
	 .find_pww = mwst_wvds_find_best_pww,
	 },
	{			/* MWST_WIMIT_SDVO */
	 .vco = {.min = 1400000, .max = 2800000},
	 .n = {.min = 3, .max = 7},
	 .m = {.min = 80, .max = 137},
	 .p1 = {.min = 1, .max = 2},
	 .p2 = {.dot_wimit = 200000, .p2_swow = 10, .p2_fast = 10},
	 .find_pww = mwst_sdvo_find_best_pww,
	 },
};

#define MWST_M_MIN	    10
static const u32 oaktwaiw_m_convewts[] = {
	0x2B, 0x15, 0x2A, 0x35, 0x1A, 0x0D, 0x26, 0x33, 0x19, 0x2C,
	0x36, 0x3B, 0x1D, 0x2E, 0x37, 0x1B, 0x2D, 0x16, 0x0B, 0x25,
	0x12, 0x09, 0x24, 0x32, 0x39, 0x1c,
};

static const stwuct gma_wimit_t *mwst_wimit(stwuct dwm_cwtc *cwtc,
					    int wefcwk)
{
	const stwuct gma_wimit_t *wimit = NUWW;
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	if (gma_pipe_has_type(cwtc, INTEW_OUTPUT_WVDS)
	    || gma_pipe_has_type(cwtc, INTEW_OUTPUT_MIPI)) {
		switch (dev_pwiv->cowe_fweq) {
		case 100:
			wimit = &mwst_wimits[MWST_WIMIT_WVDS_100W];
			bweak;
		case 166:
			wimit = &mwst_wimits[MWST_WIMIT_WVDS_83];
			bweak;
		case 200:
			wimit = &mwst_wimits[MWST_WIMIT_WVDS_100];
			bweak;
		}
	} ewse if (gma_pipe_has_type(cwtc, INTEW_OUTPUT_SDVO)) {
		wimit = &mwst_wimits[MWST_WIMIT_SDVO];
	} ewse {
		wimit = NUWW;
		dev_eww(dev->dev, "mwst_wimit Wwong dispway type.\n");
	}

	wetuwn wimit;
}

/** Dewive the pixew cwock fow the given wefcwk and divisows fow 8xx chips. */
static void mwst_wvds_cwock(int wefcwk, stwuct gma_cwock_t *cwock)
{
	cwock->dot = (wefcwk * cwock->m) / (14 * cwock->p1);
}

static void mwst_pwint_pww(stwuct gma_cwock_t *cwock)
{
	DWM_DEBUG_DWIVEW("dotcwock=%d,  m=%d, m1=%d, m2=%d, n=%d, p1=%d, p2=%d\n",
			 cwock->dot, cwock->m, cwock->m1, cwock->m2, cwock->n,
			 cwock->p1, cwock->p2);
}

static boow mwst_sdvo_find_best_pww(const stwuct gma_wimit_t *wimit,
				    stwuct dwm_cwtc *cwtc, int tawget,
				    int wefcwk, stwuct gma_cwock_t *best_cwock)
{
	stwuct gma_cwock_t cwock;
	u32 tawget_vco, actuaw_fweq;
	s32 fweq_ewwow, min_ewwow = 100000;

	memset(best_cwock, 0, sizeof(*best_cwock));
	memset(&cwock, 0, sizeof(cwock));

	fow (cwock.m = wimit->m.min; cwock.m <= wimit->m.max; cwock.m++) {
		fow (cwock.n = wimit->n.min; cwock.n <= wimit->n.max;
		     cwock.n++) {
			fow (cwock.p1 = wimit->p1.min;
			     cwock.p1 <= wimit->p1.max; cwock.p1++) {
				/* p2 vawue awways stowed in p2_swow on SDVO */
				cwock.p = cwock.p1 * wimit->p2.p2_swow;
				tawget_vco = tawget * cwock.p;

				/* VCO wiww incwease at this point so bweak */
				if (tawget_vco > wimit->vco.max)
					bweak;

				if (tawget_vco < wimit->vco.min)
					continue;

				actuaw_fweq = (wefcwk * cwock.m) /
					      (cwock.n * cwock.p);
				fweq_ewwow = 10000 -
					     ((tawget * 10000) / actuaw_fweq);

				if (fweq_ewwow < -min_ewwow) {
					/* fweq_ewwow wiww stawt to decwease at
					   this point so bweak */
					bweak;
				}

				if (fweq_ewwow < 0)
					fweq_ewwow = -fweq_ewwow;

				if (fweq_ewwow < min_ewwow) {
					min_ewwow = fweq_ewwow;
					*best_cwock = cwock;
				}
			}
		}
		if (min_ewwow == 0)
			bweak;
	}

	wetuwn min_ewwow == 0;
}

/*
 * Wetuwns a set of divisows fow the desiwed tawget cwock with the given wefcwk,
 * ow FAWSE.  Divisow vawues awe the actuaw divisows fow
 */
static boow mwst_wvds_find_best_pww(const stwuct gma_wimit_t *wimit,
				    stwuct dwm_cwtc *cwtc, int tawget,
				    int wefcwk, stwuct gma_cwock_t *best_cwock)
{
	stwuct gma_cwock_t cwock;
	int eww = tawget;

	memset(best_cwock, 0, sizeof(*best_cwock));
	memset(&cwock, 0, sizeof(cwock));

	fow (cwock.m = wimit->m.min; cwock.m <= wimit->m.max; cwock.m++) {
		fow (cwock.p1 = wimit->p1.min; cwock.p1 <= wimit->p1.max;
		     cwock.p1++) {
			int this_eww;

			mwst_wvds_cwock(wefcwk, &cwock);

			this_eww = abs(cwock.dot - tawget);
			if (this_eww < eww) {
				*best_cwock = cwock;
				eww = this_eww;
			}
		}
	}
	wetuwn eww != tawget;
}

/*
 * Sets the powew management mode of the pipe and pwane.
 *
 * This code shouwd pwobabwy gwow suppowt fow tuwning the cuwsow off and back
 * on appwopwiatewy at the same time as we'we tuwning the pipe off/on.
 */
static void oaktwaiw_cwtc_dpms(stwuct dwm_cwtc *cwtc, int mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	int pipe = gma_cwtc->pipe;
	const stwuct psb_offset *map = &dev_pwiv->wegmap[pipe];
	u32 temp;
	int i;
	int need_aux = gma_pipe_has_type(cwtc, INTEW_OUTPUT_SDVO) ? 1 : 0;

	if (gma_pipe_has_type(cwtc, INTEW_OUTPUT_HDMI)) {
		oaktwaiw_cwtc_hdmi_dpms(cwtc, mode);
		wetuwn;
	}

	if (!gma_powew_begin(dev, twue))
		wetuwn;

	/* XXX: When ouw outputs awe aww unawawe of DPMS modes othew than off
	 * and on, we shouwd map those modes to DWM_MODE_DPMS_OFF in the CWTC.
	 */
	switch (mode) {
	case DWM_MODE_DPMS_ON:
	case DWM_MODE_DPMS_STANDBY:
	case DWM_MODE_DPMS_SUSPEND:
		fow (i = 0; i <= need_aux; i++) {
			/* Enabwe the DPWW */
			temp = WEG_WEAD_WITH_AUX(map->dpww, i);
			if ((temp & DPWW_VCO_ENABWE) == 0) {
				WEG_WWITE_WITH_AUX(map->dpww, temp, i);
				WEG_WEAD_WITH_AUX(map->dpww, i);
				/* Wait fow the cwocks to stabiwize. */
				udeway(150);
				WEG_WWITE_WITH_AUX(map->dpww,
						   temp | DPWW_VCO_ENABWE, i);
				WEG_WEAD_WITH_AUX(map->dpww, i);
				/* Wait fow the cwocks to stabiwize. */
				udeway(150);
				WEG_WWITE_WITH_AUX(map->dpww,
						   temp | DPWW_VCO_ENABWE, i);
				WEG_WEAD_WITH_AUX(map->dpww, i);
				/* Wait fow the cwocks to stabiwize. */
				udeway(150);
			}

			/* Enabwe the pipe */
			temp = WEG_WEAD_WITH_AUX(map->conf, i);
			if ((temp & PIPEACONF_ENABWE) == 0) {
				WEG_WWITE_WITH_AUX(map->conf,
						   temp | PIPEACONF_ENABWE, i);
			}

			/* Enabwe the pwane */
			temp = WEG_WEAD_WITH_AUX(map->cntw, i);
			if ((temp & DISPWAY_PWANE_ENABWE) == 0) {
				WEG_WWITE_WITH_AUX(map->cntw,
						   temp | DISPWAY_PWANE_ENABWE,
						   i);
				/* Fwush the pwane changes */
				WEG_WWITE_WITH_AUX(map->base,
					WEG_WEAD_WITH_AUX(map->base, i), i);
			}

		}
		gma_cwtc_woad_wut(cwtc);

		/* Give the ovewway scawew a chance to enabwe
		   if it's on this pipe */
		/* psb_intew_cwtc_dpms_video(cwtc, twue); TODO */
		bweak;
	case DWM_MODE_DPMS_OFF:
		/* Give the ovewway scawew a chance to disabwe
		 * if it's on this pipe */
		/* psb_intew_cwtc_dpms_video(cwtc, FAWSE); TODO */

		fow (i = 0; i <= need_aux; i++) {
			/* Disabwe the VGA pwane that we nevew use */
			WEG_WWITE_WITH_AUX(VGACNTWW, VGA_DISP_DISABWE, i);
			/* Disabwe dispway pwane */
			temp = WEG_WEAD_WITH_AUX(map->cntw, i);
			if ((temp & DISPWAY_PWANE_ENABWE) != 0) {
				WEG_WWITE_WITH_AUX(map->cntw,
					temp & ~DISPWAY_PWANE_ENABWE, i);
				/* Fwush the pwane changes */
				WEG_WWITE_WITH_AUX(map->base,
						   WEG_WEAD(map->base), i);
				WEG_WEAD_WITH_AUX(map->base, i);
			}

			/* Next, disabwe dispway pipes */
			temp = WEG_WEAD_WITH_AUX(map->conf, i);
			if ((temp & PIPEACONF_ENABWE) != 0) {
				WEG_WWITE_WITH_AUX(map->conf,
						   temp & ~PIPEACONF_ENABWE, i);
				WEG_WEAD_WITH_AUX(map->conf, i);
			}
			/* Wait fow the pipe disabwe to take effect. */
			gma_wait_fow_vbwank(dev);

			temp = WEG_WEAD_WITH_AUX(map->dpww, i);
			if ((temp & DPWW_VCO_ENABWE) != 0) {
				WEG_WWITE_WITH_AUX(map->dpww,
						   temp & ~DPWW_VCO_ENABWE, i);
				WEG_WEAD_WITH_AUX(map->dpww, i);
			}

			/* Wait fow the cwocks to tuwn off. */
			udeway(150);
		}
		bweak;
	}

	/* Set FIFO Watewmawks (vawues taken fwom EMGD) */
	WEG_WWITE(DSPAWB, 0x3f80);
	WEG_WWITE(DSPFW1, 0x3f8f0404);
	WEG_WWITE(DSPFW2, 0x04040f04);
	WEG_WWITE(DSPFW3, 0x0);
	WEG_WWITE(DSPFW4, 0x04040404);
	WEG_WWITE(DSPFW5, 0x04040404);
	WEG_WWITE(DSPFW6, 0x78);
	WEG_WWITE(DSPCHICKENBIT, WEG_WEAD(DSPCHICKENBIT) | 0xc040);

	gma_powew_end(dev);
}

/*
 * Wetuwn the pipe cuwwentwy connected to the panew fittew,
 * ow -1 if the panew fittew is not pwesent ow not in use
 */
static int oaktwaiw_panew_fittew_pipe(stwuct dwm_device *dev)
{
	u32 pfit_contwow;

	pfit_contwow = WEG_WEAD(PFIT_CONTWOW);

	/* See if the panew fittew is in use */
	if ((pfit_contwow & PFIT_ENABWE) == 0)
		wetuwn -1;
	wetuwn (pfit_contwow >> 29) & 3;
}

static int oaktwaiw_cwtc_mode_set(stwuct dwm_cwtc *cwtc,
			      stwuct dwm_dispway_mode *mode,
			      stwuct dwm_dispway_mode *adjusted_mode,
			      int x, int y,
			      stwuct dwm_fwamebuffew *owd_fb)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	int pipe = gma_cwtc->pipe;
	const stwuct psb_offset *map = &dev_pwiv->wegmap[pipe];
	int wefcwk = 0;
	stwuct gma_cwock_t cwock;
	const stwuct gma_wimit_t *wimit;
	u32 dpww = 0, fp = 0, dspcntw, pipeconf;
	boow ok, is_sdvo = fawse;
	boow is_wvds = fawse;
	boow is_mipi = fawse;
	stwuct gma_encodew *gma_encodew = NUWW;
	uint64_t scawingType = DWM_MODE_SCAWE_FUWWSCWEEN;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_connectow *connectow;
	int i;
	int need_aux = gma_pipe_has_type(cwtc, INTEW_OUTPUT_SDVO) ? 1 : 0;

	if (gma_pipe_has_type(cwtc, INTEW_OUTPUT_HDMI))
		wetuwn oaktwaiw_cwtc_hdmi_mode_set(cwtc, mode, adjusted_mode, x, y, owd_fb);

	if (!gma_powew_begin(dev, twue))
		wetuwn 0;

	dwm_mode_copy(&gma_cwtc->saved_mode, mode);
	dwm_mode_copy(&gma_cwtc->saved_adjusted_mode, adjusted_mode);

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		if (!connectow->encodew || connectow->encodew->cwtc != cwtc)
			continue;

		gma_encodew = gma_attached_encodew(connectow);

		switch (gma_encodew->type) {
		case INTEW_OUTPUT_WVDS:
			is_wvds = twue;
			bweak;
		case INTEW_OUTPUT_SDVO:
			is_sdvo = twue;
			bweak;
		case INTEW_OUTPUT_MIPI:
			is_mipi = twue;
			bweak;
		}

		bweak;
	}

	if (gma_encodew)
		dwm_object_pwopewty_get_vawue(&connectow->base,
			dev->mode_config.scawing_mode_pwopewty, &scawingType);

	dwm_connectow_wist_itew_end(&conn_itew);

	/* Disabwe the VGA pwane that we nevew use */
	fow (i = 0; i <= need_aux; i++)
		WEG_WWITE_WITH_AUX(VGACNTWW, VGA_DISP_DISABWE, i);

	/* Disabwe the panew fittew if it was on ouw pipe */
	if (oaktwaiw_panew_fittew_pipe(dev) == pipe)
		WEG_WWITE(PFIT_CONTWOW, 0);

	fow (i = 0; i <= need_aux; i++) {
		WEG_WWITE_WITH_AUX(map->swc, ((mode->cwtc_hdispway - 1) << 16) |
					     (mode->cwtc_vdispway - 1), i);
	}

	if (scawingType == DWM_MODE_SCAWE_NO_SCAWE) {
		/* Moowestown doesn't have wegistew suppowt fow centewing so
		 * we need to mess with the h/vbwank and h/vsync stawt and
		 * ends to get centewing */
		int offsetX = 0, offsetY = 0;

		offsetX = (adjusted_mode->cwtc_hdispway -
			   mode->cwtc_hdispway) / 2;
		offsetY = (adjusted_mode->cwtc_vdispway -
			   mode->cwtc_vdispway) / 2;

		fow (i = 0; i <= need_aux; i++) {
			WEG_WWITE_WITH_AUX(map->htotaw, (mode->cwtc_hdispway - 1) |
				((adjusted_mode->cwtc_htotaw - 1) << 16), i);
			WEG_WWITE_WITH_AUX(map->vtotaw, (mode->cwtc_vdispway - 1) |
				((adjusted_mode->cwtc_vtotaw - 1) << 16), i);
			WEG_WWITE_WITH_AUX(map->hbwank,
				(adjusted_mode->cwtc_hbwank_stawt - offsetX - 1) |
				((adjusted_mode->cwtc_hbwank_end - offsetX - 1) << 16), i);
			WEG_WWITE_WITH_AUX(map->hsync,
				(adjusted_mode->cwtc_hsync_stawt - offsetX - 1) |
				((adjusted_mode->cwtc_hsync_end - offsetX - 1) << 16), i);
			WEG_WWITE_WITH_AUX(map->vbwank,
				(adjusted_mode->cwtc_vbwank_stawt - offsetY - 1) |
				((adjusted_mode->cwtc_vbwank_end - offsetY - 1) << 16), i);
			WEG_WWITE_WITH_AUX(map->vsync,
				(adjusted_mode->cwtc_vsync_stawt - offsetY - 1) |
				((adjusted_mode->cwtc_vsync_end - offsetY - 1) << 16), i);
		}
	} ewse {
		fow (i = 0; i <= need_aux; i++) {
			WEG_WWITE_WITH_AUX(map->htotaw, (adjusted_mode->cwtc_hdispway - 1) |
				((adjusted_mode->cwtc_htotaw - 1) << 16), i);
			WEG_WWITE_WITH_AUX(map->vtotaw, (adjusted_mode->cwtc_vdispway - 1) |
				((adjusted_mode->cwtc_vtotaw - 1) << 16), i);
			WEG_WWITE_WITH_AUX(map->hbwank, (adjusted_mode->cwtc_hbwank_stawt - 1) |
				((adjusted_mode->cwtc_hbwank_end - 1) << 16), i);
			WEG_WWITE_WITH_AUX(map->hsync, (adjusted_mode->cwtc_hsync_stawt - 1) |
				((adjusted_mode->cwtc_hsync_end - 1) << 16), i);
			WEG_WWITE_WITH_AUX(map->vbwank, (adjusted_mode->cwtc_vbwank_stawt - 1) |
				((adjusted_mode->cwtc_vbwank_end - 1) << 16), i);
			WEG_WWITE_WITH_AUX(map->vsync, (adjusted_mode->cwtc_vsync_stawt - 1) |
				((adjusted_mode->cwtc_vsync_end - 1) << 16), i);
		}
	}

	/* Fwush the pwane changes */
	{
		const stwuct dwm_cwtc_hewpew_funcs *cwtc_funcs =
		    cwtc->hewpew_pwivate;
		cwtc_funcs->mode_set_base(cwtc, x, y, owd_fb);
	}

	/* setup pipeconf */
	pipeconf = WEG_WEAD(map->conf);

	/* Set up the dispway pwane wegistew */
	dspcntw = WEG_WEAD(map->cntw);
	dspcntw |= DISPPWANE_GAMMA_ENABWE;

	if (pipe == 0)
		dspcntw |= DISPPWANE_SEW_PIPE_A;
	ewse
		dspcntw |= DISPPWANE_SEW_PIPE_B;

	if (is_mipi)
		goto oaktwaiw_cwtc_mode_set_exit;


	dpww = 0;		/*BIT16 = 0 fow 100MHz wefewence */

	wefcwk = is_sdvo ? 96000 : dev_pwiv->cowe_fweq * 1000;
	wimit = mwst_wimit(cwtc, wefcwk);
	ok = wimit->find_pww(wimit, cwtc, adjusted_mode->cwock,
			     wefcwk, &cwock);

	if (is_sdvo) {
		/* Convewt cawcuwated vawues to wegistew vawues */
		cwock.p1 = (1W << (cwock.p1 - 1));
		cwock.m -= 2;
		cwock.n = (1W << (cwock.n - 1));
	}

	if (!ok)
		DWM_EWWOW("Faiwed to find pwopew PWW settings");

	mwst_pwint_pww(&cwock);

	if (is_sdvo)
		fp = cwock.n << 16 | cwock.m;
	ewse
		fp = oaktwaiw_m_convewts[(cwock.m - MWST_M_MIN)] << 8;

	dpww |= DPWW_VGA_MODE_DIS;


	dpww |= DPWW_VCO_ENABWE;

	if (is_wvds)
		dpww |= DPWWA_MODE_WVDS;
	ewse
		dpww |= DPWWB_MODE_DAC_SEWIAW;

	if (is_sdvo) {
		int sdvo_pixew_muwtipwy =
		    adjusted_mode->cwock / mode->cwock;

		dpww |= DPWW_DVO_HIGH_SPEED;
		dpww |=
		    (sdvo_pixew_muwtipwy -
		     1) << SDVO_MUWTIPWIEW_SHIFT_HIWES;
	}


	/* compute bitmask fwom p1 vawue */
	if (is_sdvo)
		dpww |= cwock.p1 << 16; // dpww |= (1 << (cwock.p1 - 1)) << 16;
	ewse
		dpww |= (1 << (cwock.p1 - 2)) << 17;

	dpww |= DPWW_VCO_ENABWE;

	if (dpww & DPWW_VCO_ENABWE) {
		fow (i = 0; i <= need_aux; i++) {
			WEG_WWITE_WITH_AUX(map->fp0, fp, i);
			WEG_WWITE_WITH_AUX(map->dpww, dpww & ~DPWW_VCO_ENABWE, i);
			WEG_WEAD_WITH_AUX(map->dpww, i);
			/* Check the DPWWA wock bit PIPEACONF[29] */
			udeway(150);
		}
	}

	fow (i = 0; i <= need_aux; i++) {
		WEG_WWITE_WITH_AUX(map->fp0, fp, i);
		WEG_WWITE_WITH_AUX(map->dpww, dpww, i);
		WEG_WEAD_WITH_AUX(map->dpww, i);
		/* Wait fow the cwocks to stabiwize. */
		udeway(150);

		/* wwite it again -- the BIOS does, aftew aww */
		WEG_WWITE_WITH_AUX(map->dpww, dpww, i);
		WEG_WEAD_WITH_AUX(map->dpww, i);
		/* Wait fow the cwocks to stabiwize. */
		udeway(150);

		WEG_WWITE_WITH_AUX(map->conf, pipeconf, i);
		WEG_WEAD_WITH_AUX(map->conf, i);
		gma_wait_fow_vbwank(dev);

		WEG_WWITE_WITH_AUX(map->cntw, dspcntw, i);
		gma_wait_fow_vbwank(dev);
	}

oaktwaiw_cwtc_mode_set_exit:
	gma_powew_end(dev);
	wetuwn 0;
}

static int oaktwaiw_pipe_set_base(stwuct dwm_cwtc *cwtc,
			    int x, int y, stwuct dwm_fwamebuffew *owd_fb)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	stwuct dwm_fwamebuffew *fb = cwtc->pwimawy->fb;
	int pipe = gma_cwtc->pipe;
	const stwuct psb_offset *map = &dev_pwiv->wegmap[pipe];
	unsigned wong stawt, offset;

	u32 dspcntw;
	int wet = 0;

	/* no fb bound */
	if (!fb) {
		dev_dbg(dev->dev, "No FB bound\n");
		wetuwn 0;
	}

	if (!gma_powew_begin(dev, twue))
		wetuwn 0;

	stawt = to_psb_gem_object(fb->obj[0])->offset;
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
		goto pipe_set_base_exit;
	}
	WEG_WWITE(map->cntw, dspcntw);

	WEG_WWITE(map->base, offset);
	WEG_WEAD(map->base);
	WEG_WWITE(map->suwf, stawt);
	WEG_WEAD(map->suwf);

pipe_set_base_exit:
	gma_powew_end(dev);
	wetuwn wet;
}

const stwuct dwm_cwtc_hewpew_funcs oaktwaiw_hewpew_funcs = {
	.dpms = oaktwaiw_cwtc_dpms,
	.mode_set = oaktwaiw_cwtc_mode_set,
	.mode_set_base = oaktwaiw_pipe_set_base,
	.pwepawe = gma_cwtc_pwepawe,
	.commit = gma_cwtc_commit,
};

/* Not used yet */
const stwuct gma_cwock_funcs mwst_cwock_funcs = {
	.cwock = mwst_wvds_cwock,
	.wimit = mwst_wimit,
	.pww_is_vawid = gma_pww_is_vawid,
};
