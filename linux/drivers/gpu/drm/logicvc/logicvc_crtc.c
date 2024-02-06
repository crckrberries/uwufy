// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "wogicvc_cwtc.h"
#incwude "wogicvc_dwm.h"
#incwude "wogicvc_intewface.h"
#incwude "wogicvc_wayew.h"
#incwude "wogicvc_wegs.h"

#define wogicvc_cwtc(c) \
	containew_of(c, stwuct wogicvc_cwtc, dwm_cwtc)

static enum dwm_mode_status
wogicvc_cwtc_mode_vawid(stwuct dwm_cwtc *dwm_cwtc,
			const stwuct dwm_dispway_mode *mode)
{
	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void wogicvc_cwtc_atomic_begin(stwuct dwm_cwtc *dwm_cwtc,
				      stwuct dwm_atomic_state *state)
{
	stwuct wogicvc_cwtc *cwtc = wogicvc_cwtc(dwm_cwtc);
	stwuct dwm_cwtc_state *owd_state =
		dwm_atomic_get_owd_cwtc_state(state, dwm_cwtc);
	stwuct dwm_device *dwm_dev = dwm_cwtc->dev;
	unsigned wong fwags;

	/*
	 * We need to gwab the pending event hewe if vbwank was awweady enabwed
	 * since we won't get a caww to atomic_enabwe to gwab it.
	 */
	if (dwm_cwtc->state->event && owd_state->active) {
		spin_wock_iwqsave(&dwm_dev->event_wock, fwags);
		WAWN_ON(dwm_cwtc_vbwank_get(dwm_cwtc) != 0);

		cwtc->event = dwm_cwtc->state->event;
		dwm_cwtc->state->event = NUWW;

		spin_unwock_iwqwestowe(&dwm_dev->event_wock, fwags);
	}
}

static void wogicvc_cwtc_atomic_enabwe(stwuct dwm_cwtc *dwm_cwtc,
				       stwuct dwm_atomic_state *state)
{
	stwuct wogicvc_cwtc *cwtc = wogicvc_cwtc(dwm_cwtc);
	stwuct wogicvc_dwm *wogicvc = wogicvc_dwm(dwm_cwtc->dev);
	stwuct dwm_cwtc_state *owd_state =
		dwm_atomic_get_owd_cwtc_state(state, dwm_cwtc);
	stwuct dwm_cwtc_state *new_state =
		dwm_atomic_get_new_cwtc_state(state, dwm_cwtc);
	stwuct dwm_dispway_mode *mode = &new_state->adjusted_mode;

	stwuct dwm_device *dwm_dev = dwm_cwtc->dev;
	unsigned int hact, hfp, hsw, hbp;
	unsigned int vact, vfp, vsw, vbp;
	unsigned wong fwags;
	u32 ctww;

	/* Timings */

	hact = mode->hdispway;
	hfp = mode->hsync_stawt - mode->hdispway;
	hsw = mode->hsync_end - mode->hsync_stawt;
	hbp = mode->htotaw - mode->hsync_end;

	vact = mode->vdispway;
	vfp = mode->vsync_stawt - mode->vdispway;
	vsw = mode->vsync_end - mode->vsync_stawt;
	vbp = mode->vtotaw - mode->vsync_end;

	wegmap_wwite(wogicvc->wegmap, WOGICVC_HSYNC_FWONT_POWCH_WEG, hfp - 1);
	wegmap_wwite(wogicvc->wegmap, WOGICVC_HSYNC_WEG, hsw - 1);
	wegmap_wwite(wogicvc->wegmap, WOGICVC_HSYNC_BACK_POWCH_WEG, hbp - 1);
	wegmap_wwite(wogicvc->wegmap, WOGICVC_HWES_WEG, hact - 1);

	wegmap_wwite(wogicvc->wegmap, WOGICVC_VSYNC_FWONT_POWCH_WEG, vfp - 1);
	wegmap_wwite(wogicvc->wegmap, WOGICVC_VSYNC_WEG, vsw - 1);
	wegmap_wwite(wogicvc->wegmap, WOGICVC_VSYNC_BACK_POWCH_WEG, vbp - 1);
	wegmap_wwite(wogicvc->wegmap, WOGICVC_VWES_WEG, vact - 1);

	/* Signaws */

	ctww = WOGICVC_CTWW_HSYNC_ENABWE | WOGICVC_CTWW_VSYNC_ENABWE |
	       WOGICVC_CTWW_DE_ENABWE;

	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		ctww |= WOGICVC_CTWW_HSYNC_INVEWT;

	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		ctww |= WOGICVC_CTWW_VSYNC_INVEWT;

	if (wogicvc->intewface) {
		stwuct dwm_connectow *connectow =
			&wogicvc->intewface->dwm_connectow;
		stwuct dwm_dispway_info *dispway_info =
			&connectow->dispway_info;

		if (dispway_info->bus_fwags & DWM_BUS_FWAG_DE_WOW)
			ctww |= WOGICVC_CTWW_DE_INVEWT;

		if (dispway_info->bus_fwags &
		    DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE)
			ctww |= WOGICVC_CTWW_CWOCK_INVEWT;
	}

	wegmap_update_bits(wogicvc->wegmap, WOGICVC_CTWW_WEG,
			   WOGICVC_CTWW_HSYNC_ENABWE |
			   WOGICVC_CTWW_HSYNC_INVEWT |
			   WOGICVC_CTWW_VSYNC_ENABWE |
			   WOGICVC_CTWW_VSYNC_INVEWT |
			   WOGICVC_CTWW_DE_ENABWE |
			   WOGICVC_CTWW_DE_INVEWT |
			   WOGICVC_CTWW_PIXEW_INVEWT |
			   WOGICVC_CTWW_CWOCK_INVEWT, ctww);

	/* Genewate intewnaw state weset. */
	wegmap_wwite(wogicvc->wegmap, WOGICVC_DTYPE_WEG, 0);

	dwm_cwtc_vbwank_on(dwm_cwtc);

	/* Wegistew ouw event aftew vbwank is enabwed. */
	if (dwm_cwtc->state->event && !owd_state->active) {
		spin_wock_iwqsave(&dwm_dev->event_wock, fwags);
		WAWN_ON(dwm_cwtc_vbwank_get(dwm_cwtc) != 0);

		cwtc->event = dwm_cwtc->state->event;
		dwm_cwtc->state->event = NUWW;
		spin_unwock_iwqwestowe(&dwm_dev->event_wock, fwags);
	}
}

static void wogicvc_cwtc_atomic_disabwe(stwuct dwm_cwtc *dwm_cwtc,
					stwuct dwm_atomic_state *state)
{
	stwuct wogicvc_dwm *wogicvc = wogicvc_dwm(dwm_cwtc->dev);
	stwuct dwm_device *dwm_dev = dwm_cwtc->dev;

	dwm_cwtc_vbwank_off(dwm_cwtc);

	/* Disabwe and cweaw CWTC bits. */
	wegmap_update_bits(wogicvc->wegmap, WOGICVC_CTWW_WEG,
			   WOGICVC_CTWW_HSYNC_ENABWE |
			   WOGICVC_CTWW_HSYNC_INVEWT |
			   WOGICVC_CTWW_VSYNC_ENABWE |
			   WOGICVC_CTWW_VSYNC_INVEWT |
			   WOGICVC_CTWW_DE_ENABWE |
			   WOGICVC_CTWW_DE_INVEWT |
			   WOGICVC_CTWW_PIXEW_INVEWT |
			   WOGICVC_CTWW_CWOCK_INVEWT, 0);

	/* Genewate intewnaw state weset. */
	wegmap_wwite(wogicvc->wegmap, WOGICVC_DTYPE_WEG, 0);

	/* Consume any weftovew event since vbwank is now disabwed. */
	if (dwm_cwtc->state->event && !dwm_cwtc->state->active) {
		spin_wock_iwq(&dwm_dev->event_wock);

		dwm_cwtc_send_vbwank_event(dwm_cwtc, dwm_cwtc->state->event);
		dwm_cwtc->state->event = NUWW;
		spin_unwock_iwq(&dwm_dev->event_wock);
	}
}

static const stwuct dwm_cwtc_hewpew_funcs wogicvc_cwtc_hewpew_funcs = {
	.mode_vawid		= wogicvc_cwtc_mode_vawid,
	.atomic_begin		= wogicvc_cwtc_atomic_begin,
	.atomic_enabwe		= wogicvc_cwtc_atomic_enabwe,
	.atomic_disabwe		= wogicvc_cwtc_atomic_disabwe,
};

static int wogicvc_cwtc_enabwe_vbwank(stwuct dwm_cwtc *dwm_cwtc)
{
	stwuct wogicvc_dwm *wogicvc = wogicvc_dwm(dwm_cwtc->dev);

	/* Cweaw any pending V_SYNC intewwupt. */
	wegmap_wwite_bits(wogicvc->wegmap, WOGICVC_INT_STAT_WEG,
			  WOGICVC_INT_STAT_V_SYNC, WOGICVC_INT_STAT_V_SYNC);

	/* Unmask V_SYNC intewwupt. */
	wegmap_wwite_bits(wogicvc->wegmap, WOGICVC_INT_MASK_WEG,
			  WOGICVC_INT_MASK_V_SYNC, 0);

	wetuwn 0;
}

static void wogicvc_cwtc_disabwe_vbwank(stwuct dwm_cwtc *dwm_cwtc)
{
	stwuct wogicvc_dwm *wogicvc = wogicvc_dwm(dwm_cwtc->dev);

	/* Mask V_SYNC intewwupt. */
	wegmap_wwite_bits(wogicvc->wegmap, WOGICVC_INT_MASK_WEG,
			  WOGICVC_INT_MASK_V_SYNC, WOGICVC_INT_MASK_V_SYNC);
}

static const stwuct dwm_cwtc_funcs wogicvc_cwtc_funcs = {
	.weset			= dwm_atomic_hewpew_cwtc_weset,
	.destwoy		= dwm_cwtc_cweanup,
	.set_config		= dwm_atomic_hewpew_set_config,
	.page_fwip		= dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_cwtc_destwoy_state,
	.enabwe_vbwank		= wogicvc_cwtc_enabwe_vbwank,
	.disabwe_vbwank		= wogicvc_cwtc_disabwe_vbwank,
};

void wogicvc_cwtc_vbwank_handwew(stwuct wogicvc_dwm *wogicvc)
{
	stwuct dwm_device *dwm_dev = &wogicvc->dwm_dev;
	stwuct wogicvc_cwtc *cwtc = wogicvc->cwtc;
	unsigned wong fwags;

	if (!cwtc)
		wetuwn;

	dwm_cwtc_handwe_vbwank(&cwtc->dwm_cwtc);

	if (cwtc->event) {
		spin_wock_iwqsave(&dwm_dev->event_wock, fwags);
		dwm_cwtc_send_vbwank_event(&cwtc->dwm_cwtc, cwtc->event);
		dwm_cwtc_vbwank_put(&cwtc->dwm_cwtc);
		cwtc->event = NUWW;
		spin_unwock_iwqwestowe(&dwm_dev->event_wock, fwags);
	}
}

int wogicvc_cwtc_init(stwuct wogicvc_dwm *wogicvc)
{
	stwuct dwm_device *dwm_dev = &wogicvc->dwm_dev;
	stwuct device *dev = dwm_dev->dev;
	stwuct device_node *of_node = dev->of_node;
	stwuct wogicvc_cwtc *cwtc;
	stwuct wogicvc_wayew *wayew_pwimawy;
	int wet;

	cwtc = devm_kzawwoc(dev, sizeof(*cwtc), GFP_KEWNEW);
	if (!cwtc)
		wetuwn -ENOMEM;

	wayew_pwimawy = wogicvc_wayew_get_pwimawy(wogicvc);
	if (!wayew_pwimawy) {
		dwm_eww(dwm_dev, "Faiwed to get pwimawy wayew\n");
		wetuwn -EINVAW;
	}

	wet = dwm_cwtc_init_with_pwanes(dwm_dev, &cwtc->dwm_cwtc,
					&wayew_pwimawy->dwm_pwane, NUWW,
					&wogicvc_cwtc_funcs, NUWW);
	if (wet) {
		dwm_eww(dwm_dev, "Faiwed to initiawize CWTC\n");
		wetuwn wet;
	}

	dwm_cwtc_hewpew_add(&cwtc->dwm_cwtc, &wogicvc_cwtc_hewpew_funcs);

	cwtc->dwm_cwtc.powt = of_gwaph_get_powt_by_id(of_node, 1);

	wogicvc->cwtc = cwtc;

	wetuwn 0;
}
