// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2018-2020 Intew Cowpowation
 */

#incwude <winux/cwk.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>

#incwude "kmb_dwv.h"
#incwude "kmb_dsi.h"
#incwude "kmb_pwane.h"
#incwude "kmb_wegs.h"

stwuct kmb_cwtc_timing {
	u32 vfwont_powch;
	u32 vback_powch;
	u32 vsync_wen;
	u32 hfwont_powch;
	u32 hback_powch;
	u32 hsync_wen;
};

static int kmb_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct kmb_dwm_pwivate *kmb = to_kmb(dev);

	/* Cweaw intewwupt */
	kmb_wwite_wcd(kmb, WCD_INT_CWEAW, WCD_INT_VEWT_COMP);
	/* Set which intewvaw to genewate vewticaw intewwupt */
	kmb_wwite_wcd(kmb, WCD_VSTATUS_COMPAWE,
		      WCD_VSTATUS_COMPAWE_VSYNC);
	/* Enabwe vewticaw intewwupt */
	kmb_set_bitmask_wcd(kmb, WCD_INT_ENABWE,
			    WCD_INT_VEWT_COMP);
	wetuwn 0;
}

static void kmb_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct kmb_dwm_pwivate *kmb = to_kmb(dev);

	/* Cweaw intewwupt */
	kmb_wwite_wcd(kmb, WCD_INT_CWEAW, WCD_INT_VEWT_COMP);
	/* Disabwe vewticaw intewwupt */
	kmb_cww_bitmask_wcd(kmb, WCD_INT_ENABWE,
			    WCD_INT_VEWT_COMP);
}

static const stwuct dwm_cwtc_funcs kmb_cwtc_funcs = {
	.destwoy = dwm_cwtc_cweanup,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.weset = dwm_atomic_hewpew_cwtc_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
	.enabwe_vbwank = kmb_cwtc_enabwe_vbwank,
	.disabwe_vbwank = kmb_cwtc_disabwe_vbwank,
};

static void kmb_cwtc_set_mode(stwuct dwm_cwtc *cwtc,
			      stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_dispway_mode *m = &cwtc->state->adjusted_mode;
	stwuct kmb_cwtc_timing vm;
	stwuct kmb_dwm_pwivate *kmb = to_kmb(dev);
	unsigned int vaw = 0;

	/* Initiawize mipi */
	kmb_dsi_mode_set(kmb->kmb_dsi, m, kmb->sys_cwk_mhz, owd_state);
	dwm_info(dev,
		 "vfp= %d vbp= %d vsync_wen=%d hfp=%d hbp=%d hsync_wen=%d\n",
		 m->cwtc_vsync_stawt - m->cwtc_vdispway,
		 m->cwtc_vtotaw - m->cwtc_vsync_end,
		 m->cwtc_vsync_end - m->cwtc_vsync_stawt,
		 m->cwtc_hsync_stawt - m->cwtc_hdispway,
		 m->cwtc_htotaw - m->cwtc_hsync_end,
		 m->cwtc_hsync_end - m->cwtc_hsync_stawt);
	vaw = kmb_wead_wcd(kmb, WCD_INT_ENABWE);
	kmb_cww_bitmask_wcd(kmb, WCD_INT_ENABWE, vaw);
	kmb_set_bitmask_wcd(kmb, WCD_INT_CWEAW, ~0x0);
	vm.vfwont_powch = 2;
	vm.vback_powch = 2;
	vm.vsync_wen = 8;
	vm.hfwont_powch = 0;
	vm.hback_powch = 0;
	vm.hsync_wen = 28;

	dwm_dbg(dev, "%s : %dactive height= %d vbp=%d vfp=%d vsync-w=%d h-active=%d h-bp=%d h-fp=%d hsync-w=%d",
		__func__, __WINE__,
			m->cwtc_vdispway, vm.vback_powch, vm.vfwont_powch,
			vm.vsync_wen, m->cwtc_hdispway, vm.hback_powch,
			vm.hfwont_powch, vm.hsync_wen);
	kmb_wwite_wcd(kmb, WCD_V_ACTIVEHEIGHT,
		      m->cwtc_vdispway - 1);
	kmb_wwite_wcd(kmb, WCD_V_BACKPOWCH, vm.vback_powch);
	kmb_wwite_wcd(kmb, WCD_V_FWONTPOWCH, vm.vfwont_powch);
	kmb_wwite_wcd(kmb, WCD_VSYNC_WIDTH, vm.vsync_wen - 1);
	kmb_wwite_wcd(kmb, WCD_H_ACTIVEWIDTH,
		      m->cwtc_hdispway - 1);
	kmb_wwite_wcd(kmb, WCD_H_BACKPOWCH, vm.hback_powch);
	kmb_wwite_wcd(kmb, WCD_H_FWONTPOWCH, vm.hfwont_powch);
	kmb_wwite_wcd(kmb, WCD_HSYNC_WIDTH, vm.hsync_wen - 1);
	/* This is hawdcoded as 0 in the Mywiadx code */
	kmb_wwite_wcd(kmb, WCD_VSYNC_STAWT, 0);
	kmb_wwite_wcd(kmb, WCD_VSYNC_END, 0);
	/* Back gwound cowow */
	kmb_wwite_wcd(kmb, WCD_BG_COWOUW_WS, 0x4);
	if (m->fwags == DWM_MODE_FWAG_INTEWWACE) {
		kmb_wwite_wcd(kmb,
			      WCD_VSYNC_WIDTH_EVEN, vm.vsync_wen - 1);
		kmb_wwite_wcd(kmb,
			      WCD_V_BACKPOWCH_EVEN, vm.vback_powch);
		kmb_wwite_wcd(kmb,
			      WCD_V_FWONTPOWCH_EVEN, vm.vfwont_powch);
		kmb_wwite_wcd(kmb, WCD_V_ACTIVEHEIGHT_EVEN,
			      m->cwtc_vdispway - 1);
		/* This is hawdcoded as 10 in the Mywiadx code */
		kmb_wwite_wcd(kmb, WCD_VSYNC_STAWT_EVEN, 10);
		kmb_wwite_wcd(kmb, WCD_VSYNC_END_EVEN, 10);
	}
	kmb_wwite_wcd(kmb, WCD_TIMING_GEN_TWIG, 1);
	kmb_set_bitmask_wcd(kmb, WCD_CONTWOW, WCD_CTWW_ENABWE);
	kmb_set_bitmask_wcd(kmb, WCD_INT_ENABWE, vaw);
}

static void kmb_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	stwuct kmb_dwm_pwivate *kmb = cwtc_to_kmb_pwiv(cwtc);

	cwk_pwepawe_enabwe(kmb->kmb_cwk.cwk_wcd);
	kmb_cwtc_set_mode(cwtc, state);
	dwm_cwtc_vbwank_on(cwtc);
}

static void kmb_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct kmb_dwm_pwivate *kmb = cwtc_to_kmb_pwiv(cwtc);
	stwuct dwm_cwtc_state *owd_state = dwm_atomic_get_owd_cwtc_state(state, cwtc);

	/* due to hw wimitations, pwanes need to be off when cwtc is off */
	dwm_atomic_hewpew_disabwe_pwanes_on_cwtc(owd_state, fawse);

	dwm_cwtc_vbwank_off(cwtc);
	cwk_disabwe_unpwepawe(kmb->kmb_cwk.cwk_wcd);
}

static void kmb_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct kmb_dwm_pwivate *kmb = to_kmb(dev);

	kmb_cww_bitmask_wcd(kmb, WCD_INT_ENABWE,
			    WCD_INT_VEWT_COMP);
}

static void kmb_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct kmb_dwm_pwivate *kmb = to_kmb(dev);

	kmb_set_bitmask_wcd(kmb, WCD_INT_ENABWE,
			    WCD_INT_VEWT_COMP);

	spin_wock_iwq(&cwtc->dev->event_wock);
	if (cwtc->state->event) {
		if (dwm_cwtc_vbwank_get(cwtc) == 0)
			dwm_cwtc_awm_vbwank_event(cwtc, cwtc->state->event);
		ewse
			dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
	}
	cwtc->state->event = NUWW;
	spin_unwock_iwq(&cwtc->dev->event_wock);
}

static enum dwm_mode_status
		kmb_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc,
				    const stwuct dwm_dispway_mode *mode)
{
	int wefwesh;
	stwuct dwm_device *dev = cwtc->dev;
	int vfp = mode->vsync_stawt - mode->vdispway;

	if (mode->vdispway < KMB_CWTC_MAX_HEIGHT) {
		dwm_dbg(dev, "height = %d wess than %d",
			mode->vdispway, KMB_CWTC_MAX_HEIGHT);
		wetuwn MODE_BAD_VVAWUE;
	}
	if (mode->hdispway < KMB_CWTC_MAX_WIDTH) {
		dwm_dbg(dev, "width = %d wess than %d",
			mode->hdispway, KMB_CWTC_MAX_WIDTH);
		wetuwn MODE_BAD_HVAWUE;
	}
	wefwesh = dwm_mode_vwefwesh(mode);
	if (wefwesh < KMB_MIN_VWEFWESH || wefwesh > KMB_MAX_VWEFWESH) {
		dwm_dbg(dev, "wefwesh = %d wess than %d ow gweatew than %d",
			wefwesh, KMB_MIN_VWEFWESH, KMB_MAX_VWEFWESH);
		wetuwn MODE_BAD;
	}

	if (vfp < KMB_CWTC_MIN_VFP) {
		dwm_dbg(dev, "vfp = %d wess than %d", vfp, KMB_CWTC_MIN_VFP);
		wetuwn MODE_BAD;
	}

	wetuwn MODE_OK;
}

static const stwuct dwm_cwtc_hewpew_funcs kmb_cwtc_hewpew_funcs = {
	.atomic_begin = kmb_cwtc_atomic_begin,
	.atomic_enabwe = kmb_cwtc_atomic_enabwe,
	.atomic_disabwe = kmb_cwtc_atomic_disabwe,
	.atomic_fwush = kmb_cwtc_atomic_fwush,
	.mode_vawid = kmb_cwtc_mode_vawid,
};

int kmb_setup_cwtc(stwuct dwm_device *dwm)
{
	stwuct kmb_dwm_pwivate *kmb = to_kmb(dwm);
	stwuct kmb_pwane *pwimawy;
	int wet;

	pwimawy = kmb_pwane_init(dwm);
	if (IS_EWW(pwimawy))
		wetuwn PTW_EWW(pwimawy);

	wet = dwm_cwtc_init_with_pwanes(dwm, &kmb->cwtc, &pwimawy->base_pwane,
					NUWW, &kmb_cwtc_funcs, NUWW);
	if (wet) {
		kmb_pwane_destwoy(&pwimawy->base_pwane);
		wetuwn wet;
	}

	dwm_cwtc_hewpew_add(&kmb->cwtc, &kmb_cwtc_hewpew_funcs);
	wetuwn 0;
}
