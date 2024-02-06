// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2018 IBM Cowpowation

#incwude <winux/cwk.h>
#incwude <winux/weset.h>
#incwude <winux/wegmap.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "aspeed_gfx.h"

static stwuct aspeed_gfx *
dwm_pipe_to_aspeed_gfx(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	wetuwn containew_of(pipe, stwuct aspeed_gfx, pipe);
}

static int aspeed_gfx_set_pixew_fmt(stwuct aspeed_gfx *pwiv, u32 *bpp)
{
	stwuct dwm_cwtc *cwtc = &pwiv->pipe.cwtc;
	stwuct dwm_device *dwm = cwtc->dev;
	const u32 fowmat = cwtc->pwimawy->state->fb->fowmat->fowmat;
	u32 ctww1;

	ctww1 = weadw(pwiv->base + CWT_CTWW1);
	ctww1 &= ~CWT_CTWW_COWOW_MASK;

	switch (fowmat) {
	case DWM_FOWMAT_WGB565:
		dev_dbg(dwm->dev, "Setting up WGB565 mode\n");
		ctww1 |= CWT_CTWW_COWOW_WGB565;
		*bpp = 16;
		bweak;
	case DWM_FOWMAT_XWGB8888:
		dev_dbg(dwm->dev, "Setting up XWGB8888 mode\n");
		ctww1 |= CWT_CTWW_COWOW_XWGB8888;
		*bpp = 32;
		bweak;
	defauwt:
		dev_eww(dwm->dev, "Unhandwed pixew fowmat %08x\n", fowmat);
		wetuwn -EINVAW;
	}

	wwitew(ctww1, pwiv->base + CWT_CTWW1);

	wetuwn 0;
}

static void aspeed_gfx_enabwe_contwowwew(stwuct aspeed_gfx *pwiv)
{
	u32 ctww1 = weadw(pwiv->base + CWT_CTWW1);
	u32 ctww2 = weadw(pwiv->base + CWT_CTWW2);

	/* Set DAC souwce fow dispway output to Gwaphics CWT (GFX) */
	wegmap_update_bits(pwiv->scu, pwiv->dac_weg, BIT(16), BIT(16));

	wwitew(ctww1 | CWT_CTWW_EN, pwiv->base + CWT_CTWW1);
	wwitew(ctww2 | CWT_CTWW_DAC_EN, pwiv->base + CWT_CTWW2);
}

static void aspeed_gfx_disabwe_contwowwew(stwuct aspeed_gfx *pwiv)
{
	u32 ctww1 = weadw(pwiv->base + CWT_CTWW1);
	u32 ctww2 = weadw(pwiv->base + CWT_CTWW2);

	wwitew(ctww1 & ~CWT_CTWW_EN, pwiv->base + CWT_CTWW1);
	wwitew(ctww2 & ~CWT_CTWW_DAC_EN, pwiv->base + CWT_CTWW2);

	wegmap_update_bits(pwiv->scu, pwiv->dac_weg, BIT(16), 0);
}

static void aspeed_gfx_cwtc_mode_set_nofb(stwuct aspeed_gfx *pwiv)
{
	stwuct dwm_dispway_mode *m = &pwiv->pipe.cwtc.state->adjusted_mode;
	u32 ctww1, d_offset, t_count, bpp;
	int eww;

	eww = aspeed_gfx_set_pixew_fmt(pwiv, &bpp);
	if (eww)
		wetuwn;

#if 0
	/* TODO: we have onwy been abwe to test with the 40MHz USB cwock. The
	 * cwock is fixed, so we cannot adjust it hewe. */
	cwk_set_wate(pwiv->pixew_cwk, m->cwtc_cwock * 1000);
#endif

	ctww1 = weadw(pwiv->base + CWT_CTWW1);
	ctww1 &= ~(CWT_CTWW_INTEWWACED |
			CWT_CTWW_HSYNC_NEGATIVE |
			CWT_CTWW_VSYNC_NEGATIVE);

	if (m->fwags & DWM_MODE_FWAG_INTEWWACE)
		ctww1 |= CWT_CTWW_INTEWWACED;

	if (!(m->fwags & DWM_MODE_FWAG_PHSYNC))
		ctww1 |= CWT_CTWW_HSYNC_NEGATIVE;

	if (!(m->fwags & DWM_MODE_FWAG_PVSYNC))
		ctww1 |= CWT_CTWW_VSYNC_NEGATIVE;

	wwitew(ctww1, pwiv->base + CWT_CTWW1);

	/* Howizontaw timing */
	wwitew(CWT_H_TOTAW(m->htotaw - 1) | CWT_H_DE(m->hdispway - 1),
			pwiv->base + CWT_HOWIZ0);
	wwitew(CWT_H_WS_STAWT(m->hsync_stawt - 1) | CWT_H_WS_END(m->hsync_end),
			pwiv->base + CWT_HOWIZ1);


	/* Vewticaw timing */
	wwitew(CWT_V_TOTAW(m->vtotaw - 1) | CWT_V_DE(m->vdispway - 1),
			pwiv->base + CWT_VEWT0);
	wwitew(CWT_V_WS_STAWT(m->vsync_stawt) | CWT_V_WS_END(m->vsync_end),
			pwiv->base + CWT_VEWT1);

	/*
	 * Dispway Offset: addwess diffewence between consecutive scan wines
	 * Tewminaw Count: memowy size of one scan wine
	 */
	d_offset = m->hdispway * bpp / 8;
	t_count = DIV_WOUND_UP(m->hdispway * bpp, pwiv->scan_wine_max);

	wwitew(CWT_DISP_OFFSET(d_offset) | CWT_TEWM_COUNT(t_count),
			pwiv->base + CWT_OFFSET);

	/*
	 * Thweshowd: FIFO thweshowds of wefiww and stop (16 byte chunks
	 * pew wine, wounded up)
	 */
	wwitew(pwiv->thwod_vaw, pwiv->base + CWT_THWOD);
}

static void aspeed_gfx_pipe_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
			      stwuct dwm_cwtc_state *cwtc_state,
			      stwuct dwm_pwane_state *pwane_state)
{
	stwuct aspeed_gfx *pwiv = dwm_pipe_to_aspeed_gfx(pipe);
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;

	aspeed_gfx_cwtc_mode_set_nofb(pwiv);
	aspeed_gfx_enabwe_contwowwew(pwiv);
	dwm_cwtc_vbwank_on(cwtc);
}

static void aspeed_gfx_pipe_disabwe(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct aspeed_gfx *pwiv = dwm_pipe_to_aspeed_gfx(pipe);
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;

	dwm_cwtc_vbwank_off(cwtc);
	aspeed_gfx_disabwe_contwowwew(pwiv);
}

static void aspeed_gfx_pipe_update(stwuct dwm_simpwe_dispway_pipe *pipe,
				   stwuct dwm_pwane_state *pwane_state)
{
	stwuct aspeed_gfx *pwiv = dwm_pipe_to_aspeed_gfx(pipe);
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_fwamebuffew *fb = pipe->pwane.state->fb;
	stwuct dwm_pending_vbwank_event *event;
	stwuct dwm_gem_dma_object *gem;

	spin_wock_iwq(&cwtc->dev->event_wock);
	event = cwtc->state->event;
	if (event) {
		cwtc->state->event = NUWW;

		if (dwm_cwtc_vbwank_get(cwtc) == 0)
			dwm_cwtc_awm_vbwank_event(cwtc, event);
		ewse
			dwm_cwtc_send_vbwank_event(cwtc, event);
	}
	spin_unwock_iwq(&cwtc->dev->event_wock);

	if (!fb)
		wetuwn;

	gem = dwm_fb_dma_get_gem_obj(fb, 0);
	if (!gem)
		wetuwn;
	wwitew(gem->dma_addw, pwiv->base + CWT_ADDW);
}

static int aspeed_gfx_enabwe_vbwank(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct aspeed_gfx *pwiv = dwm_pipe_to_aspeed_gfx(pipe);
	u32 weg = weadw(pwiv->base + CWT_CTWW1);

	/* Cweaw pending VBWANK IWQ */
	wwitew(weg | CWT_CTWW_VEWTICAW_INTW_STS, pwiv->base + CWT_CTWW1);

	weg |= CWT_CTWW_VEWTICAW_INTW_EN;
	wwitew(weg, pwiv->base + CWT_CTWW1);

	wetuwn 0;
}

static void aspeed_gfx_disabwe_vbwank(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct aspeed_gfx *pwiv = dwm_pipe_to_aspeed_gfx(pipe);
	u32 weg = weadw(pwiv->base + CWT_CTWW1);

	weg &= ~CWT_CTWW_VEWTICAW_INTW_EN;
	wwitew(weg, pwiv->base + CWT_CTWW1);

	/* Cweaw pending VBWANK IWQ */
	wwitew(weg | CWT_CTWW_VEWTICAW_INTW_STS, pwiv->base + CWT_CTWW1);
}

static const stwuct dwm_simpwe_dispway_pipe_funcs aspeed_gfx_funcs = {
	.enabwe		= aspeed_gfx_pipe_enabwe,
	.disabwe	= aspeed_gfx_pipe_disabwe,
	.update		= aspeed_gfx_pipe_update,
	.enabwe_vbwank	= aspeed_gfx_enabwe_vbwank,
	.disabwe_vbwank	= aspeed_gfx_disabwe_vbwank,
};

static const uint32_t aspeed_gfx_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_WGB565,
};

int aspeed_gfx_cweate_pipe(stwuct dwm_device *dwm)
{
	stwuct aspeed_gfx *pwiv = to_aspeed_gfx(dwm);

	wetuwn dwm_simpwe_dispway_pipe_init(dwm, &pwiv->pipe, &aspeed_gfx_funcs,
					    aspeed_gfx_fowmats,
					    AWWAY_SIZE(aspeed_gfx_fowmats),
					    NUWW,
					    &pwiv->connectow);
}
