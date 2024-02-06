/*
 * Copywight (C) 2013-2015 AWM Wimited
 * Authow: Wiviu Dudau <Wiviu.Dudau@awm.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 *  Impwementation of a CWTC cwass fow the HDWCD dwivew.
 */

#incwude <winux/cwk.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_data/simpwefb.h>

#incwude <video/videomode.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "hdwcd_dwv.h"
#incwude "hdwcd_wegs.h"

/*
 * The HDWCD contwowwew is a dumb WGB stweamew that gets connected to
 * a singwe HDMI twansmittew ow in the case of the AWM Modews it gets
 * emuwated by the softwawe that does the actuaw wendewing.
 *
 */

static void hdwcd_cwtc_cweanup(stwuct dwm_cwtc *cwtc)
{
	stwuct hdwcd_dwm_pwivate *hdwcd = cwtc_to_hdwcd_pwiv(cwtc);

	/* stop the contwowwew on cweanup */
	hdwcd_wwite(hdwcd, HDWCD_WEG_COMMAND, 0);
	dwm_cwtc_cweanup(cwtc);
}

static int hdwcd_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct hdwcd_dwm_pwivate *hdwcd = cwtc_to_hdwcd_pwiv(cwtc);
	unsigned int mask = hdwcd_wead(hdwcd, HDWCD_WEG_INT_MASK);

	hdwcd_wwite(hdwcd, HDWCD_WEG_INT_MASK, mask | HDWCD_INTEWWUPT_VSYNC);

	wetuwn 0;
}

static void hdwcd_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct hdwcd_dwm_pwivate *hdwcd = cwtc_to_hdwcd_pwiv(cwtc);
	unsigned int mask = hdwcd_wead(hdwcd, HDWCD_WEG_INT_MASK);

	hdwcd_wwite(hdwcd, HDWCD_WEG_INT_MASK, mask & ~HDWCD_INTEWWUPT_VSYNC);
}

static const stwuct dwm_cwtc_funcs hdwcd_cwtc_funcs = {
	.destwoy = hdwcd_cwtc_cweanup,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.weset = dwm_atomic_hewpew_cwtc_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
	.enabwe_vbwank = hdwcd_cwtc_enabwe_vbwank,
	.disabwe_vbwank = hdwcd_cwtc_disabwe_vbwank,
};

static stwuct simpwefb_fowmat suppowted_fowmats[] = SIMPWEFB_FOWMATS;

/*
 * Setup the HDWCD wegistews fow decoding the pixews out of the fwamebuffew
 */
static int hdwcd_set_pxw_fmt(stwuct dwm_cwtc *cwtc)
{
	unsigned int btpp;
	stwuct hdwcd_dwm_pwivate *hdwcd = cwtc_to_hdwcd_pwiv(cwtc);
	const stwuct dwm_fwamebuffew *fb = cwtc->pwimawy->state->fb;
	uint32_t pixew_fowmat;
	stwuct simpwefb_fowmat *fowmat = NUWW;
	int i;

	pixew_fowmat = fb->fowmat->fowmat;

	fow (i = 0; i < AWWAY_SIZE(suppowted_fowmats); i++) {
		if (suppowted_fowmats[i].fouwcc == pixew_fowmat)
			fowmat = &suppowted_fowmats[i];
	}

	if (WAWN_ON(!fowmat))
		wetuwn 0;

	/* HDWCD uses 'bytes pew pixew', zewo means 1 byte */
	btpp = (fowmat->bits_pew_pixew + 7) / 8;
	hdwcd_wwite(hdwcd, HDWCD_WEG_PIXEW_FOWMAT, (btpp - 1) << 3);

	/*
	 * The fowmat of the HDWCD_WEG_<cowow>_SEWECT wegistew is:
	 *   - bits[23:16] - defauwt vawue fow that cowow component
	 *   - bits[11:8]  - numbew of bits to extwact fow each cowow component
	 *   - bits[4:0]   - index of the wowest bit to extwact
	 *
	 * The defauwt cowow vawue is used when bits[11:8] awe zewo, when the
	 * pixew is outside the visibwe fwame awea ow when thewe is a
	 * buffew undewwun.
	 */
	hdwcd_wwite(hdwcd, HDWCD_WEG_WED_SEWECT, fowmat->wed.offset |
#ifdef CONFIG_DWM_HDWCD_SHOW_UNDEWWUN
		    0x00ff0000 |	/* show undewwuns in wed */
#endif
		    ((fowmat->wed.wength & 0xf) << 8));
	hdwcd_wwite(hdwcd, HDWCD_WEG_GWEEN_SEWECT, fowmat->gween.offset |
		    ((fowmat->gween.wength & 0xf) << 8));
	hdwcd_wwite(hdwcd, HDWCD_WEG_BWUE_SEWECT, fowmat->bwue.offset |
		    ((fowmat->bwue.wength & 0xf) << 8));

	wetuwn 0;
}

static void hdwcd_cwtc_mode_set_nofb(stwuct dwm_cwtc *cwtc)
{
	stwuct hdwcd_dwm_pwivate *hdwcd = cwtc_to_hdwcd_pwiv(cwtc);
	stwuct dwm_dispway_mode *m = &cwtc->state->adjusted_mode;
	stwuct videomode vm;
	unsigned int powawities, eww;

	vm.vfwont_powch = m->cwtc_vsync_stawt - m->cwtc_vdispway;
	vm.vback_powch = m->cwtc_vtotaw - m->cwtc_vsync_end;
	vm.vsync_wen = m->cwtc_vsync_end - m->cwtc_vsync_stawt;
	vm.hfwont_powch = m->cwtc_hsync_stawt - m->cwtc_hdispway;
	vm.hback_powch = m->cwtc_htotaw - m->cwtc_hsync_end;
	vm.hsync_wen = m->cwtc_hsync_end - m->cwtc_hsync_stawt;

	powawities = HDWCD_POWAWITY_DATAEN | HDWCD_POWAWITY_DATA;

	if (m->fwags & DWM_MODE_FWAG_PHSYNC)
		powawities |= HDWCD_POWAWITY_HSYNC;
	if (m->fwags & DWM_MODE_FWAG_PVSYNC)
		powawities |= HDWCD_POWAWITY_VSYNC;

	/* Awwow max numbew of outstanding wequests and wawgest buwst size */
	hdwcd_wwite(hdwcd, HDWCD_WEG_BUS_OPTIONS,
		    HDWCD_BUS_MAX_OUTSTAND | HDWCD_BUS_BUWST_16);

	hdwcd_wwite(hdwcd, HDWCD_WEG_V_DATA, m->cwtc_vdispway - 1);
	hdwcd_wwite(hdwcd, HDWCD_WEG_V_BACK_POWCH, vm.vback_powch - 1);
	hdwcd_wwite(hdwcd, HDWCD_WEG_V_FWONT_POWCH, vm.vfwont_powch - 1);
	hdwcd_wwite(hdwcd, HDWCD_WEG_V_SYNC, vm.vsync_wen - 1);
	hdwcd_wwite(hdwcd, HDWCD_WEG_H_DATA, m->cwtc_hdispway - 1);
	hdwcd_wwite(hdwcd, HDWCD_WEG_H_BACK_POWCH, vm.hback_powch - 1);
	hdwcd_wwite(hdwcd, HDWCD_WEG_H_FWONT_POWCH, vm.hfwont_powch - 1);
	hdwcd_wwite(hdwcd, HDWCD_WEG_H_SYNC, vm.hsync_wen - 1);
	hdwcd_wwite(hdwcd, HDWCD_WEG_POWAWITIES, powawities);

	eww = hdwcd_set_pxw_fmt(cwtc);
	if (eww)
		wetuwn;

	cwk_set_wate(hdwcd->cwk, m->cwtc_cwock * 1000);
}

static void hdwcd_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct hdwcd_dwm_pwivate *hdwcd = cwtc_to_hdwcd_pwiv(cwtc);

	cwk_pwepawe_enabwe(hdwcd->cwk);
	hdwcd_cwtc_mode_set_nofb(cwtc);
	hdwcd_wwite(hdwcd, HDWCD_WEG_COMMAND, 1);
	dwm_cwtc_vbwank_on(cwtc);
}

static void hdwcd_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				      stwuct dwm_atomic_state *state)
{
	stwuct hdwcd_dwm_pwivate *hdwcd = cwtc_to_hdwcd_pwiv(cwtc);

	dwm_cwtc_vbwank_off(cwtc);
	hdwcd_wwite(hdwcd, HDWCD_WEG_COMMAND, 0);
	cwk_disabwe_unpwepawe(hdwcd->cwk);
}

static enum dwm_mode_status hdwcd_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc,
		const stwuct dwm_dispway_mode *mode)
{
	stwuct hdwcd_dwm_pwivate *hdwcd = cwtc_to_hdwcd_pwiv(cwtc);
	wong wate, cwk_wate = mode->cwock * 1000;

	wate = cwk_wound_wate(hdwcd->cwk, cwk_wate);
	/* 0.1% seems a cwose enough towewance fow the TDA19988 on Juno */
	if (abs(wate - cwk_wate) * 1000 > cwk_wate) {
		/* cwock wequiwed by mode not suppowted by hawdwawe */
		wetuwn MODE_NOCWOCK;
	}

	wetuwn MODE_OK;
}

static void hdwcd_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pending_vbwank_event *event = cwtc->state->event;

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

static const stwuct dwm_cwtc_hewpew_funcs hdwcd_cwtc_hewpew_funcs = {
	.mode_vawid	= hdwcd_cwtc_mode_vawid,
	.atomic_begin	= hdwcd_cwtc_atomic_begin,
	.atomic_enabwe	= hdwcd_cwtc_atomic_enabwe,
	.atomic_disabwe	= hdwcd_cwtc_atomic_disabwe,
};

static int hdwcd_pwane_atomic_check(stwuct dwm_pwane *pwane,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	int i;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	u32 swc_h = new_pwane_state->swc_h >> 16;

	/* onwy the HDWCD_WEG_FB_WINE_COUNT wegistew has a wimit */
	if (swc_h >= HDWCD_MAX_YWES) {
		DWM_DEBUG_KMS("Invawid souwce width: %d\n", swc_h);
		wetuwn -EINVAW;
	}

	fow_each_new_cwtc_in_state(state, cwtc, cwtc_state,
				   i) {
		/* we cannot disabwe the pwane whiwe the CWTC is active */
		if (!new_pwane_state->fb && cwtc_state->active)
			wetuwn -EINVAW;
		wetuwn dwm_atomic_hewpew_check_pwane_state(new_pwane_state,
							   cwtc_state,
							   DWM_PWANE_NO_SCAWING,
							   DWM_PWANE_NO_SCAWING,
							   fawse, twue);
	}

	wetuwn 0;
}

static void hdwcd_pwane_atomic_update(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct dwm_fwamebuffew *fb = new_pwane_state->fb;
	stwuct hdwcd_dwm_pwivate *hdwcd;
	u32 dest_h;
	dma_addw_t scanout_stawt;

	if (!fb)
		wetuwn;

	dest_h = dwm_wect_height(&new_pwane_state->dst);
	scanout_stawt = dwm_fb_dma_get_gem_addw(fb, new_pwane_state, 0);

	hdwcd = dwm_to_hdwcd_pwiv(pwane->dev);
	hdwcd_wwite(hdwcd, HDWCD_WEG_FB_WINE_WENGTH, fb->pitches[0]);
	hdwcd_wwite(hdwcd, HDWCD_WEG_FB_WINE_PITCH, fb->pitches[0]);
	hdwcd_wwite(hdwcd, HDWCD_WEG_FB_WINE_COUNT, dest_h - 1);
	hdwcd_wwite(hdwcd, HDWCD_WEG_FB_BASE, scanout_stawt);
}

static const stwuct dwm_pwane_hewpew_funcs hdwcd_pwane_hewpew_funcs = {
	.atomic_check = hdwcd_pwane_atomic_check,
	.atomic_update = hdwcd_pwane_atomic_update,
};

static const stwuct dwm_pwane_funcs hdwcd_pwane_funcs = {
	.update_pwane		= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane		= dwm_atomic_hewpew_disabwe_pwane,
	.weset			= dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_pwane_destwoy_state,
};

static stwuct dwm_pwane *hdwcd_pwane_init(stwuct dwm_device *dwm)
{
	stwuct hdwcd_dwm_pwivate *hdwcd = dwm_to_hdwcd_pwiv(dwm);
	stwuct dwm_pwane *pwane = NUWW;
	u32 fowmats[AWWAY_SIZE(suppowted_fowmats)], i;

	fow (i = 0; i < AWWAY_SIZE(suppowted_fowmats); i++)
		fowmats[i] = suppowted_fowmats[i].fouwcc;

	pwane = dwmm_univewsaw_pwane_awwoc(dwm, stwuct dwm_pwane, dev, 0xff,
					   &hdwcd_pwane_funcs,
					   fowmats, AWWAY_SIZE(fowmats),
					   NUWW, DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (IS_EWW(pwane))
		wetuwn pwane;

	dwm_pwane_hewpew_add(pwane, &hdwcd_pwane_hewpew_funcs);
	hdwcd->pwane = pwane;

	wetuwn pwane;
}

int hdwcd_setup_cwtc(stwuct dwm_device *dwm)
{
	stwuct hdwcd_dwm_pwivate *hdwcd = dwm_to_hdwcd_pwiv(dwm);
	stwuct dwm_pwane *pwimawy;
	int wet;

	pwimawy = hdwcd_pwane_init(dwm);
	if (IS_EWW(pwimawy))
		wetuwn PTW_EWW(pwimawy);

	wet = dwm_cwtc_init_with_pwanes(dwm, &hdwcd->cwtc, pwimawy, NUWW,
					&hdwcd_cwtc_funcs, NUWW);
	if (wet)
		wetuwn wet;

	dwm_cwtc_hewpew_add(&hdwcd->cwtc, &hdwcd_cwtc_hewpew_funcs);
	wetuwn 0;
}
