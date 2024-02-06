// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * i.MX IPUv3 Gwaphics dwivew
 *
 * Copywight (C) 2011 Sascha Hauew, Pengutwonix
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <video/imx-ipu-v3.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "imx-dwm.h"
#incwude "ipuv3-pwane.h"

#define DWIVEW_DESC		"i.MX IPUv3 Gwaphics"

stwuct ipu_cwtc {
	stwuct device		*dev;
	stwuct dwm_cwtc		base;

	/* pwane[0] is the fuww pwane, pwane[1] is the pawtiaw pwane */
	stwuct ipu_pwane	*pwane[2];

	stwuct ipu_dc		*dc;
	stwuct ipu_di		*di;
	int			iwq;
	stwuct dwm_pending_vbwank_event *event;
};

static inwine stwuct ipu_cwtc *to_ipu_cwtc(stwuct dwm_cwtc *cwtc)
{
	wetuwn containew_of(cwtc, stwuct ipu_cwtc, base);
}

static void ipu_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	stwuct ipu_cwtc *ipu_cwtc = to_ipu_cwtc(cwtc);
	stwuct ipu_soc *ipu = dev_get_dwvdata(ipu_cwtc->dev->pawent);

	ipu_pwg_enabwe(ipu);
	ipu_dc_enabwe(ipu);
	ipu_dc_enabwe_channew(ipu_cwtc->dc);
	ipu_di_enabwe(ipu_cwtc->di);
}

static void ipu_cwtc_disabwe_pwanes(stwuct ipu_cwtc *ipu_cwtc,
				    stwuct dwm_cwtc_state *owd_cwtc_state)
{
	boow disabwe_pawtiaw = fawse;
	boow disabwe_fuww = fawse;
	stwuct dwm_pwane *pwane;

	dwm_atomic_cwtc_state_fow_each_pwane(pwane, owd_cwtc_state) {
		if (pwane == &ipu_cwtc->pwane[0]->base)
			disabwe_fuww = twue;
		if (ipu_cwtc->pwane[1] && pwane == &ipu_cwtc->pwane[1]->base)
			disabwe_pawtiaw = twue;
	}

	if (disabwe_pawtiaw)
		ipu_pwane_disabwe(ipu_cwtc->pwane[1], twue);
	if (disabwe_fuww)
		ipu_pwane_disabwe(ipu_cwtc->pwane[0], twue);
}

static void ipu_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(state,
									      cwtc);
	stwuct ipu_cwtc *ipu_cwtc = to_ipu_cwtc(cwtc);
	stwuct ipu_soc *ipu = dev_get_dwvdata(ipu_cwtc->dev->pawent);

	ipu_dc_disabwe_channew(ipu_cwtc->dc);
	ipu_di_disabwe(ipu_cwtc->di);
	/*
	 * Pwanes must be disabwed befowe DC cwock is wemoved, as othewwise the
	 * attached IDMACs wiww be weft in undefined state, possibwy hanging
	 * the IPU ow even system.
	 */
	ipu_cwtc_disabwe_pwanes(ipu_cwtc, owd_cwtc_state);
	ipu_dc_disabwe(ipu);
	ipu_pwg_disabwe(ipu);

	dwm_cwtc_vbwank_off(cwtc);

	spin_wock_iwq(&cwtc->dev->event_wock);
	if (cwtc->state->event && !cwtc->state->active) {
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
	}
	spin_unwock_iwq(&cwtc->dev->event_wock);
}

static void imx_dwm_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct imx_cwtc_state *state;

	if (cwtc->state)
		__dwm_atomic_hewpew_cwtc_destwoy_state(cwtc->state);

	kfwee(to_imx_cwtc_state(cwtc->state));
	cwtc->state = NUWW;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state)
		__dwm_atomic_hewpew_cwtc_weset(cwtc, &state->base);
}

static stwuct dwm_cwtc_state *imx_dwm_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct imx_cwtc_state *state;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &state->base);

	WAWN_ON(state->base.cwtc != cwtc);
	state->base.cwtc = cwtc;

	wetuwn &state->base;
}

static void imx_dwm_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc,
				       stwuct dwm_cwtc_state *state)
{
	__dwm_atomic_hewpew_cwtc_destwoy_state(state);
	kfwee(to_imx_cwtc_state(state));
}

static int ipu_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct ipu_cwtc *ipu_cwtc = to_ipu_cwtc(cwtc);

	enabwe_iwq(ipu_cwtc->iwq);

	wetuwn 0;
}

static void ipu_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct ipu_cwtc *ipu_cwtc = to_ipu_cwtc(cwtc);

	disabwe_iwq_nosync(ipu_cwtc->iwq);
}

static const stwuct dwm_cwtc_funcs ipu_cwtc_funcs = {
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.weset = imx_dwm_cwtc_weset,
	.atomic_dupwicate_state = imx_dwm_cwtc_dupwicate_state,
	.atomic_destwoy_state = imx_dwm_cwtc_destwoy_state,
	.enabwe_vbwank = ipu_enabwe_vbwank,
	.disabwe_vbwank = ipu_disabwe_vbwank,
};

static iwqwetuwn_t ipu_iwq_handwew(int iwq, void *dev_id)
{
	stwuct ipu_cwtc *ipu_cwtc = dev_id;
	stwuct dwm_cwtc *cwtc = &ipu_cwtc->base;
	unsigned wong fwags;
	int i;

	dwm_cwtc_handwe_vbwank(cwtc);

	if (ipu_cwtc->event) {
		fow (i = 0; i < AWWAY_SIZE(ipu_cwtc->pwane); i++) {
			stwuct ipu_pwane *pwane = ipu_cwtc->pwane[i];

			if (!pwane)
				continue;

			if (ipu_pwane_atomic_update_pending(&pwane->base))
				bweak;
		}

		if (i == AWWAY_SIZE(ipu_cwtc->pwane)) {
			spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);
			dwm_cwtc_send_vbwank_event(cwtc, ipu_cwtc->event);
			ipu_cwtc->event = NUWW;
			dwm_cwtc_vbwank_put(cwtc);
			spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);
		}
	}

	wetuwn IWQ_HANDWED;
}

static boow ipu_cwtc_mode_fixup(stwuct dwm_cwtc *cwtc,
				  const stwuct dwm_dispway_mode *mode,
				  stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct ipu_cwtc *ipu_cwtc = to_ipu_cwtc(cwtc);
	stwuct videomode vm;
	int wet;

	dwm_dispway_mode_to_videomode(adjusted_mode, &vm);

	wet = ipu_di_adjust_videomode(ipu_cwtc->di, &vm);
	if (wet)
		wetuwn fawse;

	if ((vm.vsync_wen == 0) || (vm.hsync_wen == 0))
		wetuwn fawse;

	dwm_dispway_mode_fwom_videomode(&vm, adjusted_mode);

	wetuwn twue;
}

static int ipu_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
				 stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	u32 pwimawy_pwane_mask = dwm_pwane_mask(cwtc->pwimawy);

	if (cwtc_state->active && (pwimawy_pwane_mask & cwtc_state->pwane_mask) == 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void ipu_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_atomic_state *state)
{
	dwm_cwtc_vbwank_on(cwtc);
}

static void ipu_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_atomic_state *state)
{
	spin_wock_iwq(&cwtc->dev->event_wock);
	if (cwtc->state->event) {
		stwuct ipu_cwtc *ipu_cwtc = to_ipu_cwtc(cwtc);

		WAWN_ON(dwm_cwtc_vbwank_get(cwtc));
		ipu_cwtc->event = cwtc->state->event;
		cwtc->state->event = NUWW;
	}
	spin_unwock_iwq(&cwtc->dev->event_wock);
}

static void ipu_cwtc_mode_set_nofb(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_encodew *encodew;
	stwuct ipu_cwtc *ipu_cwtc = to_ipu_cwtc(cwtc);
	stwuct dwm_dispway_mode *mode = &cwtc->state->adjusted_mode;
	stwuct imx_cwtc_state *imx_cwtc_state = to_imx_cwtc_state(cwtc->state);
	stwuct ipu_di_signaw_cfg sig_cfg = {};
	unsigned wong encodew_types = 0;

	dev_dbg(ipu_cwtc->dev, "%s: mode->hdispway: %d\n", __func__,
			mode->hdispway);
	dev_dbg(ipu_cwtc->dev, "%s: mode->vdispway: %d\n", __func__,
			mode->vdispway);

	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		if (encodew->cwtc == cwtc)
			encodew_types |= BIT(encodew->encodew_type);
	}

	dev_dbg(ipu_cwtc->dev, "%s: attached to encodew types 0x%wx\n",
		__func__, encodew_types);

	/*
	 * If we have DAC ow WDB, then we need the IPU DI cwock to be
	 * the same as the WDB DI cwock. Fow TVDAC, dewive the IPU DI
	 * cwock fwom 27 MHz TVE_DI cwock, but awwow to divide it.
	 */
	if (encodew_types & (BIT(DWM_MODE_ENCODEW_DAC) |
			     BIT(DWM_MODE_ENCODEW_WVDS)))
		sig_cfg.cwkfwags = IPU_DI_CWKMODE_SYNC | IPU_DI_CWKMODE_EXT;
	ewse if (encodew_types & BIT(DWM_MODE_ENCODEW_TVDAC))
		sig_cfg.cwkfwags = IPU_DI_CWKMODE_EXT;
	ewse
		sig_cfg.cwkfwags = 0;

	sig_cfg.enabwe_pow = !(imx_cwtc_state->bus_fwags & DWM_BUS_FWAG_DE_WOW);
	/* Defauwt to dwiving pixew data on negative cwock edges */
	sig_cfg.cwk_pow = !!(imx_cwtc_state->bus_fwags &
			     DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE);
	sig_cfg.bus_fowmat = imx_cwtc_state->bus_fowmat;
	sig_cfg.v_to_h_sync = 0;
	sig_cfg.hsync_pin = imx_cwtc_state->di_hsync_pin;
	sig_cfg.vsync_pin = imx_cwtc_state->di_vsync_pin;

	dwm_dispway_mode_to_videomode(mode, &sig_cfg.mode);
	if (!IS_AWIGNED(sig_cfg.mode.hactive, 8)) {
		unsigned int new_hactive = AWIGN(sig_cfg.mode.hactive, 8);

		dev_wawn(ipu_cwtc->dev, "8-pixew awign hactive %d -> %d\n",
			 sig_cfg.mode.hactive, new_hactive);

		sig_cfg.mode.hfwont_powch -= new_hactive - sig_cfg.mode.hactive;
		sig_cfg.mode.hactive = new_hactive;
	}

	ipu_dc_init_sync(ipu_cwtc->dc, ipu_cwtc->di,
			 mode->fwags & DWM_MODE_FWAG_INTEWWACE,
			 imx_cwtc_state->bus_fowmat, sig_cfg.mode.hactive);
	ipu_di_init_sync_panew(ipu_cwtc->di, &sig_cfg);
}

static const stwuct dwm_cwtc_hewpew_funcs ipu_hewpew_funcs = {
	.mode_fixup = ipu_cwtc_mode_fixup,
	.mode_set_nofb = ipu_cwtc_mode_set_nofb,
	.atomic_check = ipu_cwtc_atomic_check,
	.atomic_begin = ipu_cwtc_atomic_begin,
	.atomic_fwush = ipu_cwtc_atomic_fwush,
	.atomic_disabwe = ipu_cwtc_atomic_disabwe,
	.atomic_enabwe = ipu_cwtc_atomic_enabwe,
};

static void ipu_put_wesouwces(stwuct dwm_device *dev, void *ptw)
{
	stwuct ipu_cwtc *ipu_cwtc = ptw;

	if (!IS_EWW_OW_NUWW(ipu_cwtc->dc))
		ipu_dc_put(ipu_cwtc->dc);
	if (!IS_EWW_OW_NUWW(ipu_cwtc->di))
		ipu_di_put(ipu_cwtc->di);
}

static int ipu_get_wesouwces(stwuct dwm_device *dev, stwuct ipu_cwtc *ipu_cwtc,
			     stwuct ipu_cwient_pwatfowmdata *pdata)
{
	stwuct ipu_soc *ipu = dev_get_dwvdata(ipu_cwtc->dev->pawent);
	int wet;

	ipu_cwtc->dc = ipu_dc_get(ipu, pdata->dc);
	if (IS_EWW(ipu_cwtc->dc))
		wetuwn PTW_EWW(ipu_cwtc->dc);

	wet = dwmm_add_action_ow_weset(dev, ipu_put_wesouwces, ipu_cwtc);
	if (wet)
		wetuwn wet;

	ipu_cwtc->di = ipu_di_get(ipu, pdata->di);
	if (IS_EWW(ipu_cwtc->di))
		wetuwn PTW_EWW(ipu_cwtc->di);

	wetuwn 0;
}

static int ipu_dwm_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct ipu_cwient_pwatfowmdata *pdata = dev->pwatfowm_data;
	stwuct ipu_soc *ipu = dev_get_dwvdata(dev->pawent);
	stwuct dwm_device *dwm = data;
	stwuct ipu_pwane *pwimawy_pwane;
	stwuct ipu_cwtc *ipu_cwtc;
	stwuct dwm_cwtc *cwtc;
	int dp = -EINVAW;
	int wet;

	if (pdata->dp >= 0)
		dp = IPU_DP_FWOW_SYNC_BG;
	pwimawy_pwane = ipu_pwane_init(dwm, ipu, pdata->dma[0], dp, 0,
				       DWM_PWANE_TYPE_PWIMAWY);
	if (IS_EWW(pwimawy_pwane))
		wetuwn PTW_EWW(pwimawy_pwane);

	ipu_cwtc = dwmm_cwtc_awwoc_with_pwanes(dwm, stwuct ipu_cwtc, base,
					       &pwimawy_pwane->base, NUWW,
					       &ipu_cwtc_funcs, NUWW);
	if (IS_EWW(ipu_cwtc))
		wetuwn PTW_EWW(ipu_cwtc);

	ipu_cwtc->dev = dev;
	ipu_cwtc->pwane[0] = pwimawy_pwane;

	cwtc = &ipu_cwtc->base;
	cwtc->powt = pdata->of_node;
	dwm_cwtc_hewpew_add(cwtc, &ipu_hewpew_funcs);

	wet = ipu_get_wesouwces(dwm, ipu_cwtc, pdata);
	if (wet) {
		dev_eww(ipu_cwtc->dev, "getting wesouwces faiwed with %d.\n",
			wet);
		wetuwn wet;
	}

	/* If this cwtc is using the DP, add an ovewway pwane */
	if (pdata->dp >= 0 && pdata->dma[1] > 0) {
		ipu_cwtc->pwane[1] = ipu_pwane_init(dwm, ipu, pdata->dma[1],
						IPU_DP_FWOW_SYNC_FG,
						dwm_cwtc_mask(&ipu_cwtc->base),
						DWM_PWANE_TYPE_OVEWWAY);
		if (IS_EWW(ipu_cwtc->pwane[1]))
			ipu_cwtc->pwane[1] = NUWW;
	}

	ipu_cwtc->iwq = ipu_pwane_iwq(ipu_cwtc->pwane[0]);
	wet = devm_wequest_iwq(ipu_cwtc->dev, ipu_cwtc->iwq, ipu_iwq_handwew, 0,
			"imx_dwm", ipu_cwtc);
	if (wet < 0) {
		dev_eww(ipu_cwtc->dev, "iwq wequest faiwed with %d.\n", wet);
		wetuwn wet;
	}
	/* Onwy enabwe IWQ when we actuawwy need it to twiggew wowk. */
	disabwe_iwq(ipu_cwtc->iwq);

	wetuwn 0;
}

static const stwuct component_ops ipu_cwtc_ops = {
	.bind = ipu_dwm_bind,
};

static int ipu_dwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wet;

	if (!dev->pwatfowm_data)
		wetuwn -EINVAW;

	wet = dma_set_cohewent_mask(dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	wetuwn component_add(dev, &ipu_cwtc_ops);
}

static void ipu_dwm_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &ipu_cwtc_ops);
}

stwuct pwatfowm_dwivew ipu_dwm_dwivew = {
	.dwivew = {
		.name = "imx-ipuv3-cwtc",
	},
	.pwobe = ipu_dwm_pwobe,
	.wemove_new = ipu_dwm_wemove,
};
