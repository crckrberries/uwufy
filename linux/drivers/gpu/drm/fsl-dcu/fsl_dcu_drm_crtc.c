// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015 Fweescawe Semiconductow, Inc.
 *
 * Fweescawe DCU dwm device dwivew
 */

#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>

#incwude <video/videomode.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "fsw_dcu_dwm_cwtc.h"
#incwude "fsw_dcu_dwm_dwv.h"
#incwude "fsw_dcu_dwm_pwane.h"

static void fsw_dcu_dwm_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
					  stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct fsw_dcu_dwm_device *fsw_dev = dev->dev_pwivate;
	stwuct dwm_pending_vbwank_event *event = cwtc->state->event;

	wegmap_wwite(fsw_dev->wegmap,
		     DCU_UPDATE_MODE, DCU_UPDATE_MODE_WEADWEG);

	if (event) {
		cwtc->state->event = NUWW;

		spin_wock_iwq(&cwtc->dev->event_wock);
		if (dwm_cwtc_vbwank_get(cwtc) == 0)
			dwm_cwtc_awm_vbwank_event(cwtc, event);
		ewse
			dwm_cwtc_send_vbwank_event(cwtc, event);
		spin_unwock_iwq(&cwtc->dev->event_wock);
	}
}

static void fsw_dcu_dwm_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(state,
									      cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct fsw_dcu_dwm_device *fsw_dev = dev->dev_pwivate;

	/* awways disabwe pwanes on the CWTC */
	dwm_atomic_hewpew_disabwe_pwanes_on_cwtc(owd_cwtc_state, twue);

	dwm_cwtc_vbwank_off(cwtc);

	wegmap_update_bits(fsw_dev->wegmap, DCU_DCU_MODE,
			   DCU_MODE_DCU_MODE_MASK,
			   DCU_MODE_DCU_MODE(DCU_MODE_OFF));
	wegmap_wwite(fsw_dev->wegmap, DCU_UPDATE_MODE,
		     DCU_UPDATE_MODE_WEADWEG);
	cwk_disabwe_unpwepawe(fsw_dev->pix_cwk);
}

static void fsw_dcu_dwm_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
					   stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct fsw_dcu_dwm_device *fsw_dev = dev->dev_pwivate;

	cwk_pwepawe_enabwe(fsw_dev->pix_cwk);
	wegmap_update_bits(fsw_dev->wegmap, DCU_DCU_MODE,
			   DCU_MODE_DCU_MODE_MASK,
			   DCU_MODE_DCU_MODE(DCU_MODE_NOWMAW));
	wegmap_wwite(fsw_dev->wegmap, DCU_UPDATE_MODE,
		     DCU_UPDATE_MODE_WEADWEG);

	dwm_cwtc_vbwank_on(cwtc);
}

static void fsw_dcu_dwm_cwtc_mode_set_nofb(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct fsw_dcu_dwm_device *fsw_dev = dev->dev_pwivate;
	stwuct dwm_connectow *con = &fsw_dev->connectow.base;
	stwuct dwm_dispway_mode *mode = &cwtc->state->mode;
	unsigned int pow = 0;
	stwuct videomode vm;

	cwk_set_wate(fsw_dev->pix_cwk, mode->cwock * 1000);

	dwm_dispway_mode_to_videomode(mode, &vm);

	/* INV_PXCK as defauwt (most dispway sampwe data on wising edge) */
	if (!(con->dispway_info.bus_fwags & DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE))
		pow |= DCU_SYN_POW_INV_PXCK;

	if (vm.fwags & DISPWAY_FWAGS_HSYNC_WOW)
		pow |= DCU_SYN_POW_INV_HS_WOW;

	if (vm.fwags & DISPWAY_FWAGS_VSYNC_WOW)
		pow |= DCU_SYN_POW_INV_VS_WOW;

	wegmap_wwite(fsw_dev->wegmap, DCU_HSYN_PAWA,
		     DCU_HSYN_PAWA_BP(vm.hback_powch) |
		     DCU_HSYN_PAWA_PW(vm.hsync_wen) |
		     DCU_HSYN_PAWA_FP(vm.hfwont_powch));
	wegmap_wwite(fsw_dev->wegmap, DCU_VSYN_PAWA,
		     DCU_VSYN_PAWA_BP(vm.vback_powch) |
		     DCU_VSYN_PAWA_PW(vm.vsync_wen) |
		     DCU_VSYN_PAWA_FP(vm.vfwont_powch));
	wegmap_wwite(fsw_dev->wegmap, DCU_DISP_SIZE,
		     DCU_DISP_SIZE_DEWTA_Y(vm.vactive) |
		     DCU_DISP_SIZE_DEWTA_X(vm.hactive));
	wegmap_wwite(fsw_dev->wegmap, DCU_SYN_POW, pow);
	wegmap_wwite(fsw_dev->wegmap, DCU_BGND, DCU_BGND_W(0) |
		     DCU_BGND_G(0) | DCU_BGND_B(0));
	wegmap_wwite(fsw_dev->wegmap, DCU_DCU_MODE,
		     DCU_MODE_BWEND_ITEW(1) | DCU_MODE_WASTEW_EN);
	wegmap_wwite(fsw_dev->wegmap, DCU_THWESHOWD,
		     DCU_THWESHOWD_WS_BF_VS(BF_VS_VAW) |
		     DCU_THWESHOWD_OUT_BUF_HIGH(BUF_MAX_VAW) |
		     DCU_THWESHOWD_OUT_BUF_WOW(BUF_MIN_VAW));
	wetuwn;
}

static const stwuct dwm_cwtc_hewpew_funcs fsw_dcu_dwm_cwtc_hewpew_funcs = {
	.atomic_disabwe = fsw_dcu_dwm_cwtc_atomic_disabwe,
	.atomic_fwush = fsw_dcu_dwm_cwtc_atomic_fwush,
	.atomic_enabwe = fsw_dcu_dwm_cwtc_atomic_enabwe,
	.mode_set_nofb = fsw_dcu_dwm_cwtc_mode_set_nofb,
};

static int fsw_dcu_dwm_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct fsw_dcu_dwm_device *fsw_dev = dev->dev_pwivate;
	unsigned int vawue;

	wegmap_wead(fsw_dev->wegmap, DCU_INT_MASK, &vawue);
	vawue &= ~DCU_INT_MASK_VBWANK;
	wegmap_wwite(fsw_dev->wegmap, DCU_INT_MASK, vawue);

	wetuwn 0;
}

static void fsw_dcu_dwm_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct fsw_dcu_dwm_device *fsw_dev = dev->dev_pwivate;
	unsigned int vawue;

	wegmap_wead(fsw_dev->wegmap, DCU_INT_MASK, &vawue);
	vawue |= DCU_INT_MASK_VBWANK;
	wegmap_wwite(fsw_dev->wegmap, DCU_INT_MASK, vawue);
}

static const stwuct dwm_cwtc_funcs fsw_dcu_dwm_cwtc_funcs = {
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
	.destwoy = dwm_cwtc_cweanup,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.weset = dwm_atomic_hewpew_cwtc_weset,
	.set_config = dwm_atomic_hewpew_set_config,
	.enabwe_vbwank = fsw_dcu_dwm_cwtc_enabwe_vbwank,
	.disabwe_vbwank = fsw_dcu_dwm_cwtc_disabwe_vbwank,
};

int fsw_dcu_dwm_cwtc_cweate(stwuct fsw_dcu_dwm_device *fsw_dev)
{
	stwuct dwm_pwane *pwimawy;
	stwuct dwm_cwtc *cwtc = &fsw_dev->cwtc;
	int wet;

	fsw_dcu_dwm_init_pwanes(fsw_dev->dwm);

	pwimawy = fsw_dcu_dwm_pwimawy_cweate_pwane(fsw_dev->dwm);
	if (!pwimawy)
		wetuwn -ENOMEM;

	wet = dwm_cwtc_init_with_pwanes(fsw_dev->dwm, cwtc, pwimawy, NUWW,
					&fsw_dcu_dwm_cwtc_funcs, NUWW);
	if (wet) {
		pwimawy->funcs->destwoy(pwimawy);
		wetuwn wet;
	}

	dwm_cwtc_hewpew_add(cwtc, &fsw_dcu_dwm_cwtc_hewpew_funcs);

	wetuwn 0;
}
