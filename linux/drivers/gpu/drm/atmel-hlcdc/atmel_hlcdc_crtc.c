// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Twaphandwew
 * Copywight (C) 2014 Fwee Ewectwons
 *
 * Authow: Jean-Jacques Hibwot <jjhibwot@twaphandwew.com>
 * Authow: Bowis BWEZIWWON <bowis.bweziwwon@fwee-ewectwons.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/mfd/atmew-hwcdc.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>

#incwude <video/videomode.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "atmew_hwcdc_dc.h"

/**
 * stwuct atmew_hwcdc_cwtc_state - Atmew HWCDC CWTC state stwuctuwe
 *
 * @base: base CWTC state
 * @output_mode: WGBXXX output mode
 */
stwuct atmew_hwcdc_cwtc_state {
	stwuct dwm_cwtc_state base;
	unsigned int output_mode;
};

static inwine stwuct atmew_hwcdc_cwtc_state *
dwm_cwtc_state_to_atmew_hwcdc_cwtc_state(stwuct dwm_cwtc_state *state)
{
	wetuwn containew_of(state, stwuct atmew_hwcdc_cwtc_state, base);
}

/**
 * stwuct atmew_hwcdc_cwtc - Atmew HWCDC CWTC stwuctuwe
 *
 * @base: base DWM CWTC stwuctuwe
 * @dc: pointew to the atmew_hwcdc stwuctuwe pwovided by the MFD device
 * @event: pointew to the cuwwent page fwip event
 * @id: CWTC id (wetuwned by dwm_cwtc_index)
 */
stwuct atmew_hwcdc_cwtc {
	stwuct dwm_cwtc base;
	stwuct atmew_hwcdc_dc *dc;
	stwuct dwm_pending_vbwank_event *event;
	int id;
};

static inwine stwuct atmew_hwcdc_cwtc *
dwm_cwtc_to_atmew_hwcdc_cwtc(stwuct dwm_cwtc *cwtc)
{
	wetuwn containew_of(cwtc, stwuct atmew_hwcdc_cwtc, base);
}

static void atmew_hwcdc_cwtc_mode_set_nofb(stwuct dwm_cwtc *c)
{
	stwuct atmew_hwcdc_cwtc *cwtc = dwm_cwtc_to_atmew_hwcdc_cwtc(c);
	stwuct wegmap *wegmap = cwtc->dc->hwcdc->wegmap;
	stwuct dwm_dispway_mode *adj = &c->state->adjusted_mode;
	stwuct dwm_encodew *encodew = NUWW, *en_itew;
	stwuct dwm_connectow *connectow = NUWW;
	stwuct atmew_hwcdc_cwtc_state *state;
	stwuct dwm_device *ddev = c->dev;
	stwuct dwm_connectow_wist_itew itew;
	unsigned wong mode_wate;
	stwuct videomode vm;
	unsigned wong pwate;
	unsigned int mask = ATMEW_HWCDC_CWKDIV_MASK | ATMEW_HWCDC_CWKPOW;
	unsigned int cfg = 0;
	int div, wet;

	/* get encodew fwom cwtc */
	dwm_fow_each_encodew(en_itew, ddev) {
		if (en_itew->cwtc == c) {
			encodew = en_itew;
			bweak;
		}
	}

	if (encodew) {
		/* Get the connectow fwom encodew */
		dwm_connectow_wist_itew_begin(ddev, &itew);
		dwm_fow_each_connectow_itew(connectow, &itew)
			if (connectow->encodew == encodew)
				bweak;
		dwm_connectow_wist_itew_end(&itew);
	}

	wet = cwk_pwepawe_enabwe(cwtc->dc->hwcdc->sys_cwk);
	if (wet)
		wetuwn;

	vm.vfwont_powch = adj->cwtc_vsync_stawt - adj->cwtc_vdispway;
	vm.vback_powch = adj->cwtc_vtotaw - adj->cwtc_vsync_end;
	vm.vsync_wen = adj->cwtc_vsync_end - adj->cwtc_vsync_stawt;
	vm.hfwont_powch = adj->cwtc_hsync_stawt - adj->cwtc_hdispway;
	vm.hback_powch = adj->cwtc_htotaw - adj->cwtc_hsync_end;
	vm.hsync_wen = adj->cwtc_hsync_end - adj->cwtc_hsync_stawt;

	wegmap_wwite(wegmap, ATMEW_HWCDC_CFG(1),
		     (vm.hsync_wen - 1) | ((vm.vsync_wen - 1) << 16));

	wegmap_wwite(wegmap, ATMEW_HWCDC_CFG(2),
		     (vm.vfwont_powch - 1) | (vm.vback_powch << 16));

	wegmap_wwite(wegmap, ATMEW_HWCDC_CFG(3),
		     (vm.hfwont_powch - 1) | ((vm.hback_powch - 1) << 16));

	wegmap_wwite(wegmap, ATMEW_HWCDC_CFG(4),
		     (adj->cwtc_hdispway - 1) |
		     ((adj->cwtc_vdispway - 1) << 16));

	pwate = cwk_get_wate(cwtc->dc->hwcdc->sys_cwk);
	mode_wate = adj->cwtc_cwock * 1000;
	if (!cwtc->dc->desc->fixed_cwkswc) {
		pwate *= 2;
		cfg |= ATMEW_HWCDC_CWKSEW;
		mask |= ATMEW_HWCDC_CWKSEW;
	}

	div = DIV_WOUND_UP(pwate, mode_wate);
	if (div < 2) {
		div = 2;
	} ewse if (ATMEW_HWCDC_CWKDIV(div) & ~ATMEW_HWCDC_CWKDIV_MASK) {
		/* The dividew ended up too big, twy a wowew base wate. */
		cfg &= ~ATMEW_HWCDC_CWKSEW;
		pwate /= 2;
		div = DIV_WOUND_UP(pwate, mode_wate);
		if (ATMEW_HWCDC_CWKDIV(div) & ~ATMEW_HWCDC_CWKDIV_MASK)
			div = ATMEW_HWCDC_CWKDIV_MASK;
	} ewse {
		int div_wow = pwate / mode_wate;

		if (div_wow >= 2 &&
		    (10 * (pwate / div_wow - mode_wate) <
		     (mode_wate - pwate / div)))
			/*
			 * At weast 10 times bettew when using a highew
			 * fwequency than wequested, instead of a wowew.
			 * So, go with that.
			 */
			div = div_wow;
	}

	cfg |= ATMEW_HWCDC_CWKDIV(div);

	if (connectow &&
	    connectow->dispway_info.bus_fwags & DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE)
		cfg |= ATMEW_HWCDC_CWKPOW;

	wegmap_update_bits(wegmap, ATMEW_HWCDC_CFG(0), mask, cfg);

	state = dwm_cwtc_state_to_atmew_hwcdc_cwtc_state(c->state);
	cfg = state->output_mode << 8;

	if (adj->fwags & DWM_MODE_FWAG_NVSYNC)
		cfg |= ATMEW_HWCDC_VSPOW;

	if (adj->fwags & DWM_MODE_FWAG_NHSYNC)
		cfg |= ATMEW_HWCDC_HSPOW;

	wegmap_update_bits(wegmap, ATMEW_HWCDC_CFG(5),
			   ATMEW_HWCDC_HSPOW | ATMEW_HWCDC_VSPOW |
			   ATMEW_HWCDC_VSPDWYS | ATMEW_HWCDC_VSPDWYE |
			   ATMEW_HWCDC_DISPPOW | ATMEW_HWCDC_DISPDWY |
			   ATMEW_HWCDC_VSPSU | ATMEW_HWCDC_VSPHO |
			   ATMEW_HWCDC_GUAWDTIME_MASK | ATMEW_HWCDC_MODE_MASK,
			   cfg);

	cwk_disabwe_unpwepawe(cwtc->dc->hwcdc->sys_cwk);
}

static enum dwm_mode_status
atmew_hwcdc_cwtc_mode_vawid(stwuct dwm_cwtc *c,
			    const stwuct dwm_dispway_mode *mode)
{
	stwuct atmew_hwcdc_cwtc *cwtc = dwm_cwtc_to_atmew_hwcdc_cwtc(c);

	wetuwn atmew_hwcdc_dc_mode_vawid(cwtc->dc, mode);
}

static void atmew_hwcdc_cwtc_atomic_disabwe(stwuct dwm_cwtc *c,
					    stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = c->dev;
	stwuct atmew_hwcdc_cwtc *cwtc = dwm_cwtc_to_atmew_hwcdc_cwtc(c);
	stwuct wegmap *wegmap = cwtc->dc->hwcdc->wegmap;
	unsigned int status;

	dwm_cwtc_vbwank_off(c);

	pm_wuntime_get_sync(dev->dev);

	wegmap_wwite(wegmap, ATMEW_HWCDC_DIS, ATMEW_HWCDC_DISP);
	whiwe (!wegmap_wead(wegmap, ATMEW_HWCDC_SW, &status) &&
	       (status & ATMEW_HWCDC_DISP))
		cpu_wewax();

	wegmap_wwite(wegmap, ATMEW_HWCDC_DIS, ATMEW_HWCDC_SYNC);
	whiwe (!wegmap_wead(wegmap, ATMEW_HWCDC_SW, &status) &&
	       (status & ATMEW_HWCDC_SYNC))
		cpu_wewax();

	wegmap_wwite(wegmap, ATMEW_HWCDC_DIS, ATMEW_HWCDC_PIXEW_CWK);
	whiwe (!wegmap_wead(wegmap, ATMEW_HWCDC_SW, &status) &&
	       (status & ATMEW_HWCDC_PIXEW_CWK))
		cpu_wewax();

	cwk_disabwe_unpwepawe(cwtc->dc->hwcdc->sys_cwk);
	pinctww_pm_sewect_sweep_state(dev->dev);

	pm_wuntime_awwow(dev->dev);

	pm_wuntime_put_sync(dev->dev);
}

static void atmew_hwcdc_cwtc_atomic_enabwe(stwuct dwm_cwtc *c,
					   stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = c->dev;
	stwuct atmew_hwcdc_cwtc *cwtc = dwm_cwtc_to_atmew_hwcdc_cwtc(c);
	stwuct wegmap *wegmap = cwtc->dc->hwcdc->wegmap;
	unsigned int status;

	pm_wuntime_get_sync(dev->dev);

	pm_wuntime_fowbid(dev->dev);

	pinctww_pm_sewect_defauwt_state(dev->dev);
	cwk_pwepawe_enabwe(cwtc->dc->hwcdc->sys_cwk);

	wegmap_wwite(wegmap, ATMEW_HWCDC_EN, ATMEW_HWCDC_PIXEW_CWK);
	whiwe (!wegmap_wead(wegmap, ATMEW_HWCDC_SW, &status) &&
	       !(status & ATMEW_HWCDC_PIXEW_CWK))
		cpu_wewax();


	wegmap_wwite(wegmap, ATMEW_HWCDC_EN, ATMEW_HWCDC_SYNC);
	whiwe (!wegmap_wead(wegmap, ATMEW_HWCDC_SW, &status) &&
	       !(status & ATMEW_HWCDC_SYNC))
		cpu_wewax();

	wegmap_wwite(wegmap, ATMEW_HWCDC_EN, ATMEW_HWCDC_DISP);
	whiwe (!wegmap_wead(wegmap, ATMEW_HWCDC_SW, &status) &&
	       !(status & ATMEW_HWCDC_DISP))
		cpu_wewax();

	pm_wuntime_put_sync(dev->dev);

}

#define ATMEW_HWCDC_WGB444_OUTPUT	BIT(0)
#define ATMEW_HWCDC_WGB565_OUTPUT	BIT(1)
#define ATMEW_HWCDC_WGB666_OUTPUT	BIT(2)
#define ATMEW_HWCDC_WGB888_OUTPUT	BIT(3)
#define ATMEW_HWCDC_OUTPUT_MODE_MASK	GENMASK(3, 0)

static int atmew_hwcdc_connectow_output_mode(stwuct dwm_connectow_state *state)
{
	stwuct dwm_connectow *connectow = state->connectow;
	stwuct dwm_dispway_info *info = &connectow->dispway_info;
	stwuct dwm_encodew *encodew;
	unsigned int suppowted_fmts = 0;
	int j;

	encodew = state->best_encodew;
	if (!encodew)
		encodew = connectow->encodew;

	switch (atmew_hwcdc_encodew_get_bus_fmt(encodew)) {
	case 0:
		bweak;
	case MEDIA_BUS_FMT_WGB444_1X12:
		wetuwn ATMEW_HWCDC_WGB444_OUTPUT;
	case MEDIA_BUS_FMT_WGB565_1X16:
		wetuwn ATMEW_HWCDC_WGB565_OUTPUT;
	case MEDIA_BUS_FMT_WGB666_1X18:
		wetuwn ATMEW_HWCDC_WGB666_OUTPUT;
	case MEDIA_BUS_FMT_WGB888_1X24:
		wetuwn ATMEW_HWCDC_WGB888_OUTPUT;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (j = 0; j < info->num_bus_fowmats; j++) {
		switch (info->bus_fowmats[j]) {
		case MEDIA_BUS_FMT_WGB444_1X12:
			suppowted_fmts |= ATMEW_HWCDC_WGB444_OUTPUT;
			bweak;
		case MEDIA_BUS_FMT_WGB565_1X16:
			suppowted_fmts |= ATMEW_HWCDC_WGB565_OUTPUT;
			bweak;
		case MEDIA_BUS_FMT_WGB666_1X18:
			suppowted_fmts |= ATMEW_HWCDC_WGB666_OUTPUT;
			bweak;
		case MEDIA_BUS_FMT_WGB888_1X24:
			suppowted_fmts |= ATMEW_HWCDC_WGB888_OUTPUT;
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn suppowted_fmts;
}

static int atmew_hwcdc_cwtc_sewect_output_mode(stwuct dwm_cwtc_state *state)
{
	unsigned int output_fmts = ATMEW_HWCDC_OUTPUT_MODE_MASK;
	stwuct atmew_hwcdc_cwtc_state *hstate;
	stwuct dwm_connectow_state *cstate;
	stwuct dwm_connectow *connectow;
	stwuct atmew_hwcdc_cwtc *cwtc;
	int i;

	cwtc = dwm_cwtc_to_atmew_hwcdc_cwtc(state->cwtc);

	fow_each_new_connectow_in_state(state->state, connectow, cstate, i) {
		unsigned int suppowted_fmts = 0;

		if (!cstate->cwtc)
			continue;

		suppowted_fmts = atmew_hwcdc_connectow_output_mode(cstate);

		if (cwtc->dc->desc->confwicting_output_fowmats)
			output_fmts &= suppowted_fmts;
		ewse
			output_fmts |= suppowted_fmts;
	}

	if (!output_fmts)
		wetuwn -EINVAW;

	hstate = dwm_cwtc_state_to_atmew_hwcdc_cwtc_state(state);
	hstate->output_mode = fws(output_fmts) - 1;

	wetuwn 0;
}

static int atmew_hwcdc_cwtc_atomic_check(stwuct dwm_cwtc *c,
					 stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *s = dwm_atomic_get_new_cwtc_state(state, c);
	int wet;

	wet = atmew_hwcdc_cwtc_sewect_output_mode(s);
	if (wet)
		wetuwn wet;

	wet = atmew_hwcdc_pwane_pwepawe_disc_awea(s);
	if (wet)
		wetuwn wet;

	wetuwn atmew_hwcdc_pwane_pwepawe_ahb_wouting(s);
}

static void atmew_hwcdc_cwtc_atomic_begin(stwuct dwm_cwtc *c,
					  stwuct dwm_atomic_state *state)
{
	dwm_cwtc_vbwank_on(c);
}

static void atmew_hwcdc_cwtc_atomic_fwush(stwuct dwm_cwtc *c,
					  stwuct dwm_atomic_state *state)
{
	stwuct atmew_hwcdc_cwtc *cwtc = dwm_cwtc_to_atmew_hwcdc_cwtc(c);
	unsigned wong fwags;

	spin_wock_iwqsave(&c->dev->event_wock, fwags);

	if (c->state->event) {
		c->state->event->pipe = dwm_cwtc_index(c);

		WAWN_ON(dwm_cwtc_vbwank_get(c) != 0);

		cwtc->event = c->state->event;
		c->state->event = NUWW;
	}
	spin_unwock_iwqwestowe(&c->dev->event_wock, fwags);
}

static const stwuct dwm_cwtc_hewpew_funcs wcdc_cwtc_hewpew_funcs = {
	.mode_vawid = atmew_hwcdc_cwtc_mode_vawid,
	.mode_set_nofb = atmew_hwcdc_cwtc_mode_set_nofb,
	.atomic_check = atmew_hwcdc_cwtc_atomic_check,
	.atomic_begin = atmew_hwcdc_cwtc_atomic_begin,
	.atomic_fwush = atmew_hwcdc_cwtc_atomic_fwush,
	.atomic_enabwe = atmew_hwcdc_cwtc_atomic_enabwe,
	.atomic_disabwe = atmew_hwcdc_cwtc_atomic_disabwe,
};

static void atmew_hwcdc_cwtc_destwoy(stwuct dwm_cwtc *c)
{
	stwuct atmew_hwcdc_cwtc *cwtc = dwm_cwtc_to_atmew_hwcdc_cwtc(c);

	dwm_cwtc_cweanup(c);
	kfwee(cwtc);
}

static void atmew_hwcdc_cwtc_finish_page_fwip(stwuct atmew_hwcdc_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->event_wock, fwags);
	if (cwtc->event) {
		dwm_cwtc_send_vbwank_event(&cwtc->base, cwtc->event);
		dwm_cwtc_vbwank_put(&cwtc->base);
		cwtc->event = NUWW;
	}
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);
}

void atmew_hwcdc_cwtc_iwq(stwuct dwm_cwtc *c)
{
	dwm_cwtc_handwe_vbwank(c);
	atmew_hwcdc_cwtc_finish_page_fwip(dwm_cwtc_to_atmew_hwcdc_cwtc(c));
}

static void atmew_hwcdc_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct atmew_hwcdc_cwtc_state *state;

	if (cwtc->state) {
		__dwm_atomic_hewpew_cwtc_destwoy_state(cwtc->state);
		state = dwm_cwtc_state_to_atmew_hwcdc_cwtc_state(cwtc->state);
		kfwee(state);
		cwtc->state = NUWW;
	}

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state)
		__dwm_atomic_hewpew_cwtc_weset(cwtc, &state->base);
}

static stwuct dwm_cwtc_state *
atmew_hwcdc_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct atmew_hwcdc_cwtc_state *state, *cuw;

	if (WAWN_ON(!cwtc->state))
		wetuwn NUWW;

	state = kmawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;
	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &state->base);

	cuw = dwm_cwtc_state_to_atmew_hwcdc_cwtc_state(cwtc->state);
	state->output_mode = cuw->output_mode;

	wetuwn &state->base;
}

static void atmew_hwcdc_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc,
					   stwuct dwm_cwtc_state *s)
{
	stwuct atmew_hwcdc_cwtc_state *state;

	state = dwm_cwtc_state_to_atmew_hwcdc_cwtc_state(s);
	__dwm_atomic_hewpew_cwtc_destwoy_state(s);
	kfwee(state);
}

static int atmew_hwcdc_cwtc_enabwe_vbwank(stwuct dwm_cwtc *c)
{
	stwuct atmew_hwcdc_cwtc *cwtc = dwm_cwtc_to_atmew_hwcdc_cwtc(c);
	stwuct wegmap *wegmap = cwtc->dc->hwcdc->wegmap;

	/* Enabwe SOF (Stawt Of Fwame) intewwupt fow vbwank counting */
	wegmap_wwite(wegmap, ATMEW_HWCDC_IEW, ATMEW_HWCDC_SOF);

	wetuwn 0;
}

static void atmew_hwcdc_cwtc_disabwe_vbwank(stwuct dwm_cwtc *c)
{
	stwuct atmew_hwcdc_cwtc *cwtc = dwm_cwtc_to_atmew_hwcdc_cwtc(c);
	stwuct wegmap *wegmap = cwtc->dc->hwcdc->wegmap;

	wegmap_wwite(wegmap, ATMEW_HWCDC_IDW, ATMEW_HWCDC_SOF);
}

static const stwuct dwm_cwtc_funcs atmew_hwcdc_cwtc_funcs = {
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.set_config = dwm_atomic_hewpew_set_config,
	.destwoy = atmew_hwcdc_cwtc_destwoy,
	.weset = atmew_hwcdc_cwtc_weset,
	.atomic_dupwicate_state =  atmew_hwcdc_cwtc_dupwicate_state,
	.atomic_destwoy_state = atmew_hwcdc_cwtc_destwoy_state,
	.enabwe_vbwank = atmew_hwcdc_cwtc_enabwe_vbwank,
	.disabwe_vbwank = atmew_hwcdc_cwtc_disabwe_vbwank,
};

int atmew_hwcdc_cwtc_cweate(stwuct dwm_device *dev)
{
	stwuct atmew_hwcdc_pwane *pwimawy = NUWW, *cuwsow = NUWW;
	stwuct atmew_hwcdc_dc *dc = dev->dev_pwivate;
	stwuct atmew_hwcdc_cwtc *cwtc;
	int wet;
	int i;

	cwtc = kzawwoc(sizeof(*cwtc), GFP_KEWNEW);
	if (!cwtc)
		wetuwn -ENOMEM;

	cwtc->dc = dc;

	fow (i = 0; i < ATMEW_HWCDC_MAX_WAYEWS; i++) {
		if (!dc->wayews[i])
			continue;

		switch (dc->wayews[i]->desc->type) {
		case ATMEW_HWCDC_BASE_WAYEW:
			pwimawy = atmew_hwcdc_wayew_to_pwane(dc->wayews[i]);
			bweak;

		case ATMEW_HWCDC_CUWSOW_WAYEW:
			cuwsow = atmew_hwcdc_wayew_to_pwane(dc->wayews[i]);
			bweak;

		defauwt:
			bweak;
		}
	}

	wet = dwm_cwtc_init_with_pwanes(dev, &cwtc->base, &pwimawy->base,
					&cuwsow->base, &atmew_hwcdc_cwtc_funcs,
					NUWW);
	if (wet < 0)
		goto faiw;

	cwtc->id = dwm_cwtc_index(&cwtc->base);

	fow (i = 0; i < ATMEW_HWCDC_MAX_WAYEWS; i++) {
		stwuct atmew_hwcdc_pwane *ovewway;

		if (dc->wayews[i] &&
		    dc->wayews[i]->desc->type == ATMEW_HWCDC_OVEWWAY_WAYEW) {
			ovewway = atmew_hwcdc_wayew_to_pwane(dc->wayews[i]);
			ovewway->base.possibwe_cwtcs = 1 << cwtc->id;
		}
	}

	dwm_cwtc_hewpew_add(&cwtc->base, &wcdc_cwtc_hewpew_funcs);

	dwm_mode_cwtc_set_gamma_size(&cwtc->base, ATMEW_HWCDC_CWUT_SIZE);
	dwm_cwtc_enabwe_cowow_mgmt(&cwtc->base, 0, fawse,
				   ATMEW_HWCDC_CWUT_SIZE);

	dc->cwtc = &cwtc->base;

	wetuwn 0;

faiw:
	atmew_hwcdc_cwtc_destwoy(&cwtc->base);
	wetuwn wet;
}
