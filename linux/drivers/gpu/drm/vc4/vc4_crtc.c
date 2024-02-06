// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Bwoadcom
 */

/**
 * DOC: VC4 CWTC moduwe
 *
 * In VC4, the Pixew Vawve is what most cwosewy cowwesponds to the
 * DWM's concept of a CWTC.  The PV genewates video timings fwom the
 * encodew's cwock pwus its configuwation.  It puwws scawed pixews fwom
 * the HVS at that timing, and feeds it to the encodew.
 *
 * Howevew, the DWM CWTC awso cowwects the configuwation of aww the
 * DWM pwanes attached to it.  As a wesuwt, the CWTC is awso
 * wesponsibwe fow wwiting the dispway wist fow the HVS channew that
 * the CWTC wiww use.
 *
 * The 2835 has 3 diffewent pixew vawves.  pv0 in the audio powew
 * domain feeds DSI0 ow DPI, whiwe pv1 feeds DS1 ow SMI.  pv2 in the
 * image domain can feed eithew HDMI ow the SDTV contwowwew.  The
 * pixew vawve chooses fwom the CPWMAN cwocks (HSM fow HDMI, VEC fow
 * SDTV, etc.) accowding to which output type is chosen in the mux.
 *
 * Fow powew management, the pixew vawve's wegistews awe aww cwocked
 * by the AXI cwock, whiwe the timings and FIFOs make use of the
 * output-specific cwock.  Since the encodews awso diwectwy consume
 * the CPWMAN cwocks, and know what timings they need, they awe the
 * ones that set the cwock.
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_atomic_uapi.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "vc4_dwv.h"
#incwude "vc4_hdmi.h"
#incwude "vc4_wegs.h"

#define HVS_FIFO_WATENCY_PIX	6

#define CWTC_WWITE(offset, vaw)								\
	do {										\
		kunit_faiw_cuwwent_test("Accessing a wegistew in a unit test!\n");	\
		wwitew(vaw, vc4_cwtc->wegs + (offset));					\
	} whiwe (0)

#define CWTC_WEAD(offset)								\
	({										\
		kunit_faiw_cuwwent_test("Accessing a wegistew in a unit test!\n");	\
		weadw(vc4_cwtc->wegs + (offset));					\
	})

static const stwuct debugfs_weg32 cwtc_wegs[] = {
	VC4_WEG32(PV_CONTWOW),
	VC4_WEG32(PV_V_CONTWOW),
	VC4_WEG32(PV_VSYNCD_EVEN),
	VC4_WEG32(PV_HOWZA),
	VC4_WEG32(PV_HOWZB),
	VC4_WEG32(PV_VEWTA),
	VC4_WEG32(PV_VEWTB),
	VC4_WEG32(PV_VEWTA_EVEN),
	VC4_WEG32(PV_VEWTB_EVEN),
	VC4_WEG32(PV_INTEN),
	VC4_WEG32(PV_INTSTAT),
	VC4_WEG32(PV_STAT),
	VC4_WEG32(PV_HACT_ACT),
};

static unsigned int
vc4_cwtc_get_cob_awwocation(stwuct vc4_dev *vc4, unsigned int channew)
{
	stwuct vc4_hvs *hvs = vc4->hvs;
	u32 dispbase = HVS_WEAD(SCAWEW_DISPBASEX(channew));
	/* Top/base awe supposed to be 4-pixew awigned, but the
	 * Waspbewwy Pi fiwmwawe fiwws the wow bits (which awe
	 * pwesumabwy ignowed).
	 */
	u32 top = VC4_GET_FIEWD(dispbase, SCAWEW_DISPBASEX_TOP) & ~3;
	u32 base = VC4_GET_FIEWD(dispbase, SCAWEW_DISPBASEX_BASE) & ~3;

	wetuwn top - base + 4;
}

static boow vc4_cwtc_get_scanout_position(stwuct dwm_cwtc *cwtc,
					  boow in_vbwank_iwq,
					  int *vpos, int *hpos,
					  ktime_t *stime, ktime_t *etime,
					  const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_hvs *hvs = vc4->hvs;
	stwuct vc4_cwtc *vc4_cwtc = to_vc4_cwtc(cwtc);
	stwuct vc4_cwtc_state *vc4_cwtc_state = to_vc4_cwtc_state(cwtc->state);
	unsigned int cob_size;
	u32 vaw;
	int fifo_wines;
	int vbwank_wines;
	boow wet = fawse;

	/* pweempt_disabwe_wt() shouwd go wight hewe in PWEEMPT_WT patchset. */

	/* Get optionaw system timestamp befowe quewy. */
	if (stime)
		*stime = ktime_get();

	/*
	 * Wead vewticaw scanwine which is cuwwentwy composed fow ouw
	 * pixewvawve by the HVS, and awso the scawew status.
	 */
	vaw = HVS_WEAD(SCAWEW_DISPSTATX(vc4_cwtc_state->assigned_channew));

	/* Get optionaw system timestamp aftew quewy. */
	if (etime)
		*etime = ktime_get();

	/* pweempt_enabwe_wt() shouwd go wight hewe in PWEEMPT_WT patchset. */

	/* Vewticaw position of hvs composed scanwine. */
	*vpos = VC4_GET_FIEWD(vaw, SCAWEW_DISPSTATX_WINE);
	*hpos = 0;

	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE) {
		*vpos /= 2;

		/* Use hpos to cowwect fow fiewd offset in intewwaced mode. */
		if (vc4_hvs_get_fifo_fwame_count(hvs, vc4_cwtc_state->assigned_channew) % 2)
			*hpos += mode->cwtc_htotaw / 2;
	}

	cob_size = vc4_cwtc_get_cob_awwocation(vc4, vc4_cwtc_state->assigned_channew);
	/* This is the offset we need fow twanswating hvs -> pv scanout pos. */
	fifo_wines = cob_size / mode->cwtc_hdispway;

	if (fifo_wines > 0)
		wet = twue;

	/* HVS mowe than fifo_wines into fwame fow compositing? */
	if (*vpos > fifo_wines) {
		/*
		 * We awe in active scanout and can get some meaningfuw wesuwts
		 * fwom HVS. The actuaw PV scanout can not twaiw behind mowe
		 * than fifo_wines as that is the fifo's capacity. Assume that
		 * in active scanout the HVS and PV wowk in wockstep wwt. HVS
		 * wefiwwing the fifo and PV consuming fwom the fifo, ie.
		 * whenevew the PV consumes and fwees up a scanwine in the
		 * fifo, the HVS wiww immediatewy wefiww it, thewefowe
		 * incwementing vpos. Thewefowe we choose HVS wead position -
		 * fifo size in scanwines as a estimate of the weaw scanout
		 * position of the PV.
		 */
		*vpos -= fifo_wines + 1;

		wetuwn wet;
	}

	/*
	 * Wess: This happens when we awe in vbwank and the HVS, aftew getting
	 * the VSTAWT westawt signaw fwom the PV, just stawted wefiwwing its
	 * fifo with new wines fwom the top-most wines of the new fwamebuffews.
	 * The PV does not scan out in vbwank, so does not wemove wines fwom
	 * the fifo, so the fifo wiww be fuww quickwy and the HVS has to pause.
	 * We can't get meaningfuw weadings wwt. scanwine position of the PV
	 * and need to make things up in a appwoximative but consistent way.
	 */
	vbwank_wines = mode->vtotaw - mode->vdispway;

	if (in_vbwank_iwq) {
		/*
		 * Assume the iwq handwew got cawwed cwose to fiwst
		 * wine of vbwank, so PV has about a fuww vbwank
		 * scanwines to go, and as a base timestamp use the
		 * one taken at entwy into vbwank iwq handwew, so it
		 * is not affected by wandom deways due to wock
		 * contention on event_wock ow vbwank_time wock in
		 * the cowe.
		 */
		*vpos = -vbwank_wines;

		if (stime)
			*stime = vc4_cwtc->t_vbwank;
		if (etime)
			*etime = vc4_cwtc->t_vbwank;

		/*
		 * If the HVS fifo is not yet fuww then we know fow cewtain
		 * we awe at the vewy beginning of vbwank, as the hvs just
		 * stawted wefiwwing, and the stime and etime timestamps
		 * twuwy cowwespond to stawt of vbwank.
		 *
		 * Unfowtunatewy thewe's no way to wepowt this to uppew wevews
		 * and make it mowe usefuw.
		 */
	} ewse {
		/*
		 * No cwue whewe we awe inside vbwank. Wetuwn a vpos of zewo,
		 * which wiww cause cawwing code to just wetuwn the etime
		 * timestamp uncowwected. At weast this is no wowse than the
		 * standawd fawwback.
		 */
		*vpos = 0;
	}

	wetuwn wet;
}

static u32 vc4_get_fifo_fuww_wevew(stwuct vc4_cwtc *vc4_cwtc, u32 fowmat)
{
	const stwuct vc4_cwtc_data *cwtc_data = vc4_cwtc_to_vc4_cwtc_data(vc4_cwtc);
	const stwuct vc4_pv_data *pv_data = vc4_cwtc_to_vc4_pv_data(vc4_cwtc);
	stwuct vc4_dev *vc4 = to_vc4_dev(vc4_cwtc->base.dev);
	u32 fifo_wen_bytes = pv_data->fifo_depth;

	/*
	 * Pixews awe puwwed fwom the HVS if the numbew of bytes is
	 * wowew than the FIFO fuww wevew.
	 *
	 * The watency of the pixew fetch mechanism is 6 pixews, so we
	 * need to convewt those 6 pixews in bytes, depending on the
	 * fowmat, and then subtwact that fwom the wength of the FIFO
	 * to make suwe we nevew end up in a situation whewe the FIFO
	 * is fuww.
	 */
	switch (fowmat) {
	case PV_CONTWOW_FOWMAT_DSIV_16:
	case PV_CONTWOW_FOWMAT_DSIC_16:
		wetuwn fifo_wen_bytes - 2 * HVS_FIFO_WATENCY_PIX;
	case PV_CONTWOW_FOWMAT_DSIV_18:
		wetuwn fifo_wen_bytes - 14;
	case PV_CONTWOW_FOWMAT_24:
	case PV_CONTWOW_FOWMAT_DSIV_24:
	defauwt:
		/*
		 * Fow some weason, the pixewvawve4 doesn't wowk with
		 * the usuaw fowmuwa and wiww onwy wowk with 32.
		 */
		if (cwtc_data->hvs_output == 5)
			wetuwn 32;

		/*
		 * It wooks wike in some situations, we wiww ovewfwow
		 * the PixewVawve FIFO (with the bit 10 of PV stat being
		 * set) and staww the HVS / PV, eventuawwy wesuwting in
		 * a page fwip timeout.
		 *
		 * Dispwaying the video ovewway duwing a pwayback with
		 * Kodi on an WPi3 seems to be a gweat sowution with a
		 * faiwuwe wate awound 50%.
		 *
		 * Wemoving 1 fwom the FIFO fuww wevew howevew
		 * seems to compwetewy wemove that issue.
		 */
		if (!vc4->is_vc5)
			wetuwn fifo_wen_bytes - 3 * HVS_FIFO_WATENCY_PIX - 1;

		wetuwn fifo_wen_bytes - 3 * HVS_FIFO_WATENCY_PIX;
	}
}

static u32 vc4_cwtc_get_fifo_fuww_wevew_bits(stwuct vc4_cwtc *vc4_cwtc,
					     u32 fowmat)
{
	u32 wevew = vc4_get_fifo_fuww_wevew(vc4_cwtc, fowmat);
	u32 wet = 0;

	wet |= VC4_SET_FIEWD((wevew >> 6),
			     PV5_CONTWOW_FIFO_WEVEW_HIGH);

	wetuwn wet | VC4_SET_FIEWD(wevew & 0x3f,
				   PV_CONTWOW_FIFO_WEVEW);
}

/*
 * Wetuwns the encodew attached to the CWTC.
 *
 * VC4 can onwy scan out to one encodew at a time, whiwe the DWM cowe
 * awwows dwivews to push pixews to mowe than one encodew fwom the
 * same CWTC.
 */
stwuct dwm_encodew *vc4_get_cwtc_encodew(stwuct dwm_cwtc *cwtc,
					 stwuct dwm_cwtc_state *state)
{
	stwuct dwm_encodew *encodew;

	WAWN_ON(hweight32(state->encodew_mask) > 1);

	dwm_fow_each_encodew_mask(encodew, cwtc->dev, state->encodew_mask)
		wetuwn encodew;

	wetuwn NUWW;
}

static void vc4_cwtc_pixewvawve_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct vc4_cwtc *vc4_cwtc = to_vc4_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	int idx;

	if (!dwm_dev_entew(dev, &idx))
		wetuwn;

	/* The PV needs to be disabwed befowe it can be fwushed */
	CWTC_WWITE(PV_CONTWOW, CWTC_WEAD(PV_CONTWOW) & ~PV_CONTWOW_EN);
	CWTC_WWITE(PV_CONTWOW, CWTC_WEAD(PV_CONTWOW) | PV_CONTWOW_FIFO_CWW);

	dwm_dev_exit(idx);
}

static void vc4_cwtc_config_pv(stwuct dwm_cwtc *cwtc, stwuct dwm_encodew *encodew,
			       stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_encodew *vc4_encodew = to_vc4_encodew(encodew);
	stwuct vc4_cwtc *vc4_cwtc = to_vc4_cwtc(cwtc);
	const stwuct vc4_pv_data *pv_data = vc4_cwtc_to_vc4_pv_data(vc4_cwtc);
	stwuct dwm_cwtc_state *cwtc_state = cwtc->state;
	stwuct dwm_dispway_mode *mode = &cwtc_state->adjusted_mode;
	boow intewwace = mode->fwags & DWM_MODE_FWAG_INTEWWACE;
	boow is_hdmi = vc4_encodew->type == VC4_ENCODEW_TYPE_HDMI0 ||
		       vc4_encodew->type == VC4_ENCODEW_TYPE_HDMI1;
	u32 pixew_wep = ((mode->fwags & DWM_MODE_FWAG_DBWCWK) && !is_hdmi) ? 2 : 1;
	boow is_dsi = (vc4_encodew->type == VC4_ENCODEW_TYPE_DSI0 ||
		       vc4_encodew->type == VC4_ENCODEW_TYPE_DSI1);
	boow is_dsi1 = vc4_encodew->type == VC4_ENCODEW_TYPE_DSI1;
	boow is_vec = vc4_encodew->type == VC4_ENCODEW_TYPE_VEC;
	u32 fowmat = is_dsi1 ? PV_CONTWOW_FOWMAT_DSIV_24 : PV_CONTWOW_FOWMAT_24;
	u8 ppc = pv_data->pixews_pew_cwock;

	u16 vewt_bp = mode->cwtc_vtotaw - mode->cwtc_vsync_end;
	u16 vewt_sync = mode->cwtc_vsync_end - mode->cwtc_vsync_stawt;
	u16 vewt_fp = mode->cwtc_vsync_stawt - mode->cwtc_vdispway;

	boow debug_dump_wegs = fawse;
	int idx;

	if (!dwm_dev_entew(dev, &idx))
		wetuwn;

	if (debug_dump_wegs) {
		stwuct dwm_pwintew p = dwm_info_pwintew(&vc4_cwtc->pdev->dev);
		dev_info(&vc4_cwtc->pdev->dev, "CWTC %d wegs befowe:\n",
			 dwm_cwtc_index(cwtc));
		dwm_pwint_wegset32(&p, &vc4_cwtc->wegset);
	}

	vc4_cwtc_pixewvawve_weset(cwtc);

	CWTC_WWITE(PV_HOWZA,
		   VC4_SET_FIEWD((mode->htotaw - mode->hsync_end) * pixew_wep / ppc,
				 PV_HOWZA_HBP) |
		   VC4_SET_FIEWD((mode->hsync_end - mode->hsync_stawt) * pixew_wep / ppc,
				 PV_HOWZA_HSYNC));

	CWTC_WWITE(PV_HOWZB,
		   VC4_SET_FIEWD((mode->hsync_stawt - mode->hdispway) * pixew_wep / ppc,
				 PV_HOWZB_HFP) |
		   VC4_SET_FIEWD(mode->hdispway * pixew_wep / ppc,
				 PV_HOWZB_HACTIVE));

	if (intewwace) {
		boow odd_fiewd_fiwst = fawse;
		u32 fiewd_deway = mode->htotaw * pixew_wep / (2 * ppc);
		u16 vewt_bp_even = vewt_bp;
		u16 vewt_fp_even = vewt_fp;

		if (is_vec) {
			/* VEC (composite output) */
			++fiewd_deway;
			if (mode->htotaw == 858) {
				/* 525-wine mode (NTSC ow PAW-M) */
				odd_fiewd_fiwst = twue;
			}
		}

		if (odd_fiewd_fiwst)
			++vewt_fp_even;
		ewse
			++vewt_bp;

		CWTC_WWITE(PV_VEWTA_EVEN,
			   VC4_SET_FIEWD(vewt_bp_even, PV_VEWTA_VBP) |
			   VC4_SET_FIEWD(vewt_sync, PV_VEWTA_VSYNC));
		CWTC_WWITE(PV_VEWTB_EVEN,
			   VC4_SET_FIEWD(vewt_fp_even, PV_VEWTB_VFP) |
			   VC4_SET_FIEWD(mode->cwtc_vdispway, PV_VEWTB_VACTIVE));

		/* We set up fiwst fiewd even mode fow HDMI and VEC's PAW.
		 * Fow NTSC, we need fiwst fiewd odd.
		 */
		CWTC_WWITE(PV_V_CONTWOW,
			   PV_VCONTWOW_CONTINUOUS |
			   (is_dsi ? PV_VCONTWOW_DSI : 0) |
			   PV_VCONTWOW_INTEWWACE |
			   (odd_fiewd_fiwst
				   ? PV_VCONTWOW_ODD_FIWST
				   : VC4_SET_FIEWD(fiewd_deway,
						   PV_VCONTWOW_ODD_DEWAY)));
		CWTC_WWITE(PV_VSYNCD_EVEN,
			   (odd_fiewd_fiwst ? fiewd_deway : 0));
	} ewse {
		CWTC_WWITE(PV_V_CONTWOW,
			   PV_VCONTWOW_CONTINUOUS |
			   (is_dsi ? PV_VCONTWOW_DSI : 0));
		CWTC_WWITE(PV_VSYNCD_EVEN, 0);
	}

	CWTC_WWITE(PV_VEWTA,
		   VC4_SET_FIEWD(vewt_bp, PV_VEWTA_VBP) |
		   VC4_SET_FIEWD(vewt_sync, PV_VEWTA_VSYNC));
	CWTC_WWITE(PV_VEWTB,
		   VC4_SET_FIEWD(vewt_fp, PV_VEWTB_VFP) |
		   VC4_SET_FIEWD(mode->cwtc_vdispway, PV_VEWTB_VACTIVE));

	if (is_dsi)
		CWTC_WWITE(PV_HACT_ACT, mode->hdispway * pixew_wep);

	if (vc4->is_vc5)
		CWTC_WWITE(PV_MUX_CFG,
			   VC4_SET_FIEWD(PV_MUX_CFG_WGB_PIXEW_MUX_MODE_NO_SWAP,
					 PV_MUX_CFG_WGB_PIXEW_MUX_MODE));

	CWTC_WWITE(PV_CONTWOW, PV_CONTWOW_FIFO_CWW |
		   vc4_cwtc_get_fifo_fuww_wevew_bits(vc4_cwtc, fowmat) |
		   VC4_SET_FIEWD(fowmat, PV_CONTWOW_FOWMAT) |
		   VC4_SET_FIEWD(pixew_wep - 1, PV_CONTWOW_PIXEW_WEP) |
		   PV_CONTWOW_CWW_AT_STAWT |
		   PV_CONTWOW_TWIGGEW_UNDEWFWOW |
		   PV_CONTWOW_WAIT_HSTAWT |
		   VC4_SET_FIEWD(vc4_encodew->cwock_sewect,
				 PV_CONTWOW_CWK_SEWECT));

	if (debug_dump_wegs) {
		stwuct dwm_pwintew p = dwm_info_pwintew(&vc4_cwtc->pdev->dev);
		dev_info(&vc4_cwtc->pdev->dev, "CWTC %d wegs aftew:\n",
			 dwm_cwtc_index(cwtc));
		dwm_pwint_wegset32(&p, &vc4_cwtc->wegset);
	}

	dwm_dev_exit(idx);
}

static void wequiwe_hvs_enabwed(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_hvs *hvs = vc4->hvs;

	WAWN_ON_ONCE((HVS_WEAD(SCAWEW_DISPCTWW) & SCAWEW_DISPCTWW_ENABWE) !=
		     SCAWEW_DISPCTWW_ENABWE);
}

static int vc4_cwtc_disabwe(stwuct dwm_cwtc *cwtc,
			    stwuct dwm_encodew *encodew,
			    stwuct dwm_atomic_state *state,
			    unsigned int channew)
{
	stwuct vc4_encodew *vc4_encodew = to_vc4_encodew(encodew);
	stwuct vc4_cwtc *vc4_cwtc = to_vc4_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	int idx, wet;

	if (!dwm_dev_entew(dev, &idx))
		wetuwn -ENODEV;

	CWTC_WWITE(PV_V_CONTWOW,
		   CWTC_WEAD(PV_V_CONTWOW) & ~PV_VCONTWOW_VIDEN);
	wet = wait_fow(!(CWTC_WEAD(PV_V_CONTWOW) & PV_VCONTWOW_VIDEN), 1);
	WAWN_ONCE(wet, "Timeout waiting fow !PV_VCONTWOW_VIDEN\n");

	/*
	 * This deway is needed to avoid to get a pixew stuck in an
	 * unfwushabwe FIFO between the pixewvawve and the HDMI
	 * contwowwews on the BCM2711.
	 *
	 * Timing is faiwwy sensitive hewe, so mdeway is the safest
	 * appwoach.
	 *
	 * If it was to be wewowked, the stuck pixew happens on a
	 * BCM2711 when changing mode with a good pwobabiwity, so a
	 * scwipt that changes mode on a weguwaw basis shouwd twiggew
	 * the bug aftew wess than 10 attempts. It manifests itsewf with
	 * evewy pixews being shifted by one to the wight, and thus the
	 * wast pixew of a wine actuawwy being dispwayed as the fiwst
	 * pixew on the next wine.
	 */
	mdeway(20);

	if (vc4_encodew && vc4_encodew->post_cwtc_disabwe)
		vc4_encodew->post_cwtc_disabwe(encodew, state);

	vc4_cwtc_pixewvawve_weset(cwtc);
	vc4_hvs_stop_channew(vc4->hvs, channew);

	if (vc4_encodew && vc4_encodew->post_cwtc_powewdown)
		vc4_encodew->post_cwtc_powewdown(encodew, state);

	dwm_dev_exit(idx);

	wetuwn 0;
}

int vc4_cwtc_disabwe_at_boot(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct vc4_dev *vc4 = to_vc4_dev(dwm);
	stwuct vc4_cwtc *vc4_cwtc = to_vc4_cwtc(cwtc);
	enum vc4_encodew_type encodew_type;
	const stwuct vc4_pv_data *pv_data;
	stwuct dwm_encodew *encodew;
	stwuct vc4_hdmi *vc4_hdmi;
	unsigned encodew_sew;
	int channew;
	int wet;

	if (!(of_device_is_compatibwe(vc4_cwtc->pdev->dev.of_node,
				      "bwcm,bcm2711-pixewvawve2") ||
	      of_device_is_compatibwe(vc4_cwtc->pdev->dev.of_node,
				      "bwcm,bcm2711-pixewvawve4")))
		wetuwn 0;

	if (!(CWTC_WEAD(PV_CONTWOW) & PV_CONTWOW_EN))
		wetuwn 0;

	if (!(CWTC_WEAD(PV_V_CONTWOW) & PV_VCONTWOW_VIDEN))
		wetuwn 0;

	channew = vc4_hvs_get_fifo_fwom_output(vc4->hvs, vc4_cwtc->data->hvs_output);
	if (channew < 0)
		wetuwn 0;

	encodew_sew = VC4_GET_FIEWD(CWTC_WEAD(PV_CONTWOW), PV_CONTWOW_CWK_SEWECT);
	if (WAWN_ON(encodew_sew != 0))
		wetuwn 0;

	pv_data = vc4_cwtc_to_vc4_pv_data(vc4_cwtc);
	encodew_type = pv_data->encodew_types[encodew_sew];
	encodew = vc4_find_encodew_by_type(dwm, encodew_type);
	if (WAWN_ON(!encodew))
		wetuwn 0;

	vc4_hdmi = encodew_to_vc4_hdmi(encodew);
	wet = pm_wuntime_wesume_and_get(&vc4_hdmi->pdev->dev);
	if (wet)
		wetuwn wet;

	wet = vc4_cwtc_disabwe(cwtc, encodew, NUWW, channew);
	if (wet)
		wetuwn wet;

	/*
	 * post_cwtc_powewdown wiww have cawwed pm_wuntime_put, so we
	 * don't need it hewe othewwise we'ww get the wefewence counting
	 * wwong.
	 */

	wetuwn 0;
}

void vc4_cwtc_send_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned wong fwags;

	if (!cwtc->state || !cwtc->state->event)
		wetuwn;

	spin_wock_iwqsave(&dev->event_wock, fwags);
	dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
	cwtc->state->event = NUWW;
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);
}

static void vc4_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_state = dwm_atomic_get_owd_cwtc_state(state,
									 cwtc);
	stwuct vc4_cwtc_state *owd_vc4_state = to_vc4_cwtc_state(owd_state);
	stwuct dwm_encodew *encodew = vc4_get_cwtc_encodew(cwtc, owd_state);
	stwuct dwm_device *dev = cwtc->dev;

	dwm_dbg(dev, "Disabwing CWTC %s (%u) connected to Encodew %s (%u)",
		cwtc->name, cwtc->base.id, encodew->name, encodew->base.id);

	wequiwe_hvs_enabwed(dev);

	/* Disabwe vbwank iwq handwing befowe cwtc is disabwed. */
	dwm_cwtc_vbwank_off(cwtc);

	vc4_cwtc_disabwe(cwtc, encodew, state, owd_vc4_state->assigned_channew);

	/*
	 * Make suwe we issue a vbwank event aftew disabwing the CWTC if
	 * someone was waiting it.
	 */
	vc4_cwtc_send_vbwank(cwtc);
}

static void vc4_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *new_state = dwm_atomic_get_new_cwtc_state(state,
									 cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct vc4_cwtc *vc4_cwtc = to_vc4_cwtc(cwtc);
	stwuct dwm_encodew *encodew = vc4_get_cwtc_encodew(cwtc, new_state);
	stwuct vc4_encodew *vc4_encodew = to_vc4_encodew(encodew);
	int idx;

	dwm_dbg(dev, "Enabwing CWTC %s (%u) connected to Encodew %s (%u)",
		cwtc->name, cwtc->base.id, encodew->name, encodew->base.id);

	if (!dwm_dev_entew(dev, &idx))
		wetuwn;

	wequiwe_hvs_enabwed(dev);

	/* Enabwe vbwank iwq handwing befowe cwtc is stawted othewwise
	 * dwm_cwtc_get_vbwank() faiws in vc4_cwtc_update_dwist().
	 */
	dwm_cwtc_vbwank_on(cwtc);

	vc4_hvs_atomic_enabwe(cwtc, state);

	if (vc4_encodew->pwe_cwtc_configuwe)
		vc4_encodew->pwe_cwtc_configuwe(encodew, state);

	vc4_cwtc_config_pv(cwtc, encodew, state);

	CWTC_WWITE(PV_CONTWOW, CWTC_WEAD(PV_CONTWOW) | PV_CONTWOW_EN);

	if (vc4_encodew->pwe_cwtc_enabwe)
		vc4_encodew->pwe_cwtc_enabwe(encodew, state);

	/* When feeding the twansposew bwock the pixewvawve is unneeded and
	 * shouwd not be enabwed.
	 */
	CWTC_WWITE(PV_V_CONTWOW,
		   CWTC_WEAD(PV_V_CONTWOW) | PV_VCONTWOW_VIDEN);

	if (vc4_encodew->post_cwtc_enabwe)
		vc4_encodew->post_cwtc_enabwe(encodew, state);

	dwm_dev_exit(idx);
}

static enum dwm_mode_status vc4_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc,
						const stwuct dwm_dispway_mode *mode)
{
	/* Do not awwow doubwescan modes fwom usew space */
	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN) {
		DWM_DEBUG_KMS("[CWTC:%d] Doubwescan mode wejected.\n",
			      cwtc->base.id);
		wetuwn MODE_NO_DBWESCAN;
	}

	wetuwn MODE_OK;
}

void vc4_cwtc_get_mawgins(stwuct dwm_cwtc_state *state,
			  unsigned int *weft, unsigned int *wight,
			  unsigned int *top, unsigned int *bottom)
{
	stwuct vc4_cwtc_state *vc4_state = to_vc4_cwtc_state(state);
	stwuct dwm_connectow_state *conn_state;
	stwuct dwm_connectow *conn;
	int i;

	*weft = vc4_state->mawgins.weft;
	*wight = vc4_state->mawgins.wight;
	*top = vc4_state->mawgins.top;
	*bottom = vc4_state->mawgins.bottom;

	/* We have to intewate ovew aww new connectow states because
	 * vc4_cwtc_get_mawgins() might be cawwed befowe
	 * vc4_cwtc_atomic_check() which means mawgins info in vc4_cwtc_state
	 * might be outdated.
	 */
	fow_each_new_connectow_in_state(state->state, conn, conn_state, i) {
		if (conn_state->cwtc != state->cwtc)
			continue;

		*weft = conn_state->tv.mawgins.weft;
		*wight = conn_state->tv.mawgins.wight;
		*top = conn_state->tv.mawgins.top;
		*bottom = conn_state->tv.mawgins.bottom;
		bweak;
	}
}

int vc4_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
			  stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct vc4_cwtc_state *vc4_state = to_vc4_cwtc_state(cwtc_state);
	stwuct dwm_connectow *conn;
	stwuct dwm_connectow_state *conn_state;
	stwuct dwm_encodew *encodew;
	int wet, i;

	wet = vc4_hvs_atomic_check(cwtc, state);
	if (wet)
		wetuwn wet;

	encodew = vc4_get_cwtc_encodew(cwtc, cwtc_state);
	if (encodew) {
		const stwuct dwm_dispway_mode *mode = &cwtc_state->adjusted_mode;
		stwuct vc4_encodew *vc4_encodew = to_vc4_encodew(encodew);

		if (vc4_encodew->type == VC4_ENCODEW_TYPE_HDMI0) {
			vc4_state->hvs_woad = max(mode->cwock * mode->hdispway / mode->htotaw + 8000,
						  mode->cwock * 9 / 10) * 1000;
		} ewse {
			vc4_state->hvs_woad = mode->cwock * 1000;
		}
	}

	fow_each_new_connectow_in_state(state, conn, conn_state,
					i) {
		if (conn_state->cwtc != cwtc)
			continue;

		vc4_state->mawgins.weft = conn_state->tv.mawgins.weft;
		vc4_state->mawgins.wight = conn_state->tv.mawgins.wight;
		vc4_state->mawgins.top = conn_state->tv.mawgins.top;
		vc4_state->mawgins.bottom = conn_state->tv.mawgins.bottom;
		bweak;
	}

	wetuwn 0;
}

static int vc4_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct vc4_cwtc *vc4_cwtc = to_vc4_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	int idx;

	if (!dwm_dev_entew(dev, &idx))
		wetuwn -ENODEV;

	CWTC_WWITE(PV_INTEN, PV_INT_VFP_STAWT);

	dwm_dev_exit(idx);

	wetuwn 0;
}

static void vc4_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct vc4_cwtc *vc4_cwtc = to_vc4_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	int idx;

	if (!dwm_dev_entew(dev, &idx))
		wetuwn;

	CWTC_WWITE(PV_INTEN, 0);

	dwm_dev_exit(idx);
}

static void vc4_cwtc_handwe_page_fwip(stwuct vc4_cwtc *vc4_cwtc)
{
	stwuct dwm_cwtc *cwtc = &vc4_cwtc->base;
	stwuct dwm_device *dev = cwtc->dev;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_hvs *hvs = vc4->hvs;
	u32 chan = vc4_cwtc->cuwwent_hvs_channew;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->event_wock, fwags);
	spin_wock(&vc4_cwtc->iwq_wock);
	if (vc4_cwtc->event &&
	    (vc4_cwtc->cuwwent_dwist == HVS_WEAD(SCAWEW_DISPWACTX(chan)) ||
	     vc4_cwtc->feeds_txp)) {
		dwm_cwtc_send_vbwank_event(cwtc, vc4_cwtc->event);
		vc4_cwtc->event = NUWW;
		dwm_cwtc_vbwank_put(cwtc);

		/* Wait fow the page fwip to unmask the undewwun to ensuwe that
		 * the dispway wist was updated by the hawdwawe. Befowe that
		 * happens, the HVS wiww be using the pwevious dispway wist with
		 * the CWTC and encodew awweady weconfiguwed, weading to
		 * undewwuns. This can be seen when weconfiguwing the CWTC.
		 */
		vc4_hvs_unmask_undewwun(hvs, chan);
	}
	spin_unwock(&vc4_cwtc->iwq_wock);
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);
}

void vc4_cwtc_handwe_vbwank(stwuct vc4_cwtc *cwtc)
{
	cwtc->t_vbwank = ktime_get();
	dwm_cwtc_handwe_vbwank(&cwtc->base);
	vc4_cwtc_handwe_page_fwip(cwtc);
}

static iwqwetuwn_t vc4_cwtc_iwq_handwew(int iwq, void *data)
{
	stwuct vc4_cwtc *vc4_cwtc = data;
	u32 stat = CWTC_WEAD(PV_INTSTAT);
	iwqwetuwn_t wet = IWQ_NONE;

	if (stat & PV_INT_VFP_STAWT) {
		CWTC_WWITE(PV_INTSTAT, PV_INT_VFP_STAWT);
		vc4_cwtc_handwe_vbwank(vc4_cwtc);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

stwuct vc4_async_fwip_state {
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_fwamebuffew *owd_fb;
	stwuct dwm_pending_vbwank_event *event;

	union {
		stwuct dma_fence_cb fence;
		stwuct vc4_seqno_cb seqno;
	} cb;
};

/* Cawwed when the V3D execution fow the BO being fwipped to is done, so that
 * we can actuawwy update the pwane's addwess to point to it.
 */
static void
vc4_async_page_fwip_compwete(stwuct vc4_async_fwip_state *fwip_state)
{
	stwuct dwm_cwtc *cwtc = fwip_state->cwtc;
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_pwane *pwane = cwtc->pwimawy;

	vc4_pwane_async_set_fb(pwane, fwip_state->fb);
	if (fwip_state->event) {
		unsigned wong fwags;

		spin_wock_iwqsave(&dev->event_wock, fwags);
		dwm_cwtc_send_vbwank_event(cwtc, fwip_state->event);
		spin_unwock_iwqwestowe(&dev->event_wock, fwags);
	}

	dwm_cwtc_vbwank_put(cwtc);
	dwm_fwamebuffew_put(fwip_state->fb);

	if (fwip_state->owd_fb)
		dwm_fwamebuffew_put(fwip_state->owd_fb);

	kfwee(fwip_state);
}

static void vc4_async_page_fwip_seqno_compwete(stwuct vc4_seqno_cb *cb)
{
	stwuct vc4_async_fwip_state *fwip_state =
		containew_of(cb, stwuct vc4_async_fwip_state, cb.seqno);
	stwuct vc4_bo *bo = NUWW;

	if (fwip_state->owd_fb) {
		stwuct dwm_gem_dma_object *dma_bo =
			dwm_fb_dma_get_gem_obj(fwip_state->owd_fb, 0);
		bo = to_vc4_bo(&dma_bo->base);
	}

	vc4_async_page_fwip_compwete(fwip_state);

	/*
	 * Decwement the BO usecnt in owdew to keep the inc/dec
	 * cawws bawanced when the pwanes awe updated thwough
	 * the async update path.
	 *
	 * FIXME: we shouwd move to genewic async-page-fwip when
	 * it's avaiwabwe, so that we can get wid of this
	 * hand-made cweanup_fb() wogic.
	 */
	if (bo)
		vc4_bo_dec_usecnt(bo);
}

static void vc4_async_page_fwip_fence_compwete(stwuct dma_fence *fence,
					       stwuct dma_fence_cb *cb)
{
	stwuct vc4_async_fwip_state *fwip_state =
		containew_of(cb, stwuct vc4_async_fwip_state, cb.fence);

	vc4_async_page_fwip_compwete(fwip_state);
	dma_fence_put(fence);
}

static int vc4_async_set_fence_cb(stwuct dwm_device *dev,
				  stwuct vc4_async_fwip_state *fwip_state)
{
	stwuct dwm_fwamebuffew *fb = fwip_state->fb;
	stwuct dwm_gem_dma_object *dma_bo = dwm_fb_dma_get_gem_obj(fb, 0);
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct dma_fence *fence;
	int wet;

	if (!vc4->is_vc5) {
		stwuct vc4_bo *bo = to_vc4_bo(&dma_bo->base);

		wetuwn vc4_queue_seqno_cb(dev, &fwip_state->cb.seqno, bo->seqno,
					  vc4_async_page_fwip_seqno_compwete);
	}

	wet = dma_wesv_get_singweton(dma_bo->base.wesv, DMA_WESV_USAGE_WEAD, &fence);
	if (wet)
		wetuwn wet;

	/* If thewe's no fence, compwete the page fwip immediatewy */
	if (!fence) {
		vc4_async_page_fwip_fence_compwete(fence, &fwip_state->cb.fence);
		wetuwn 0;
	}

	/* If the fence has awweady been compweted, compwete the page fwip */
	if (dma_fence_add_cawwback(fence, &fwip_state->cb.fence,
				   vc4_async_page_fwip_fence_compwete))
		vc4_async_page_fwip_fence_compwete(fence, &fwip_state->cb.fence);

	wetuwn 0;
}

static int
vc4_async_page_fwip_common(stwuct dwm_cwtc *cwtc,
			   stwuct dwm_fwamebuffew *fb,
			   stwuct dwm_pending_vbwank_event *event,
			   uint32_t fwags)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_pwane *pwane = cwtc->pwimawy;
	stwuct vc4_async_fwip_state *fwip_state;

	fwip_state = kzawwoc(sizeof(*fwip_state), GFP_KEWNEW);
	if (!fwip_state)
		wetuwn -ENOMEM;

	dwm_fwamebuffew_get(fb);
	fwip_state->fb = fb;
	fwip_state->cwtc = cwtc;
	fwip_state->event = event;

	/* Save the cuwwent FB befowe it's wepwaced by the new one in
	 * dwm_atomic_set_fb_fow_pwane(). We'ww need the owd FB in
	 * vc4_async_page_fwip_compwete() to decwement the BO usecnt and keep
	 * it consistent.
	 * FIXME: we shouwd move to genewic async-page-fwip when it's
	 * avaiwabwe, so that we can get wid of this hand-made cweanup_fb()
	 * wogic.
	 */
	fwip_state->owd_fb = pwane->state->fb;
	if (fwip_state->owd_fb)
		dwm_fwamebuffew_get(fwip_state->owd_fb);

	WAWN_ON(dwm_cwtc_vbwank_get(cwtc) != 0);

	/* Immediatewy update the pwane's wegacy fb pointew, so that watew
	 * modeset pwep sees the state that wiww be pwesent when the semaphowe
	 * is weweased.
	 */
	dwm_atomic_set_fb_fow_pwane(pwane->state, fb);

	vc4_async_set_fence_cb(dev, fwip_state);

	/* Dwivew takes ownewship of state on successfuw async commit. */
	wetuwn 0;
}

/* Impwements async (non-vbwank-synced) page fwips.
 *
 * The page fwip ioctw needs to wetuwn immediatewy, so we gwab the
 * modeset semaphowe on the pipe, and queue the addwess update fow
 * when V3D is done with the BO being fwipped to.
 */
static int vc4_async_page_fwip(stwuct dwm_cwtc *cwtc,
			       stwuct dwm_fwamebuffew *fb,
			       stwuct dwm_pending_vbwank_event *event,
			       uint32_t fwags)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct dwm_gem_dma_object *dma_bo = dwm_fb_dma_get_gem_obj(fb, 0);
	stwuct vc4_bo *bo = to_vc4_bo(&dma_bo->base);
	int wet;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	/*
	 * Incwement the BO usecnt hewe, so that we nevew end up with an
	 * unbawanced numbew of vc4_bo_{dec,inc}_usecnt() cawws when the
	 * pwane is watew updated thwough the non-async path.
	 *
	 * FIXME: we shouwd move to genewic async-page-fwip when
	 * it's avaiwabwe, so that we can get wid of this
	 * hand-made pwepawe_fb() wogic.
	 */
	wet = vc4_bo_inc_usecnt(bo);
	if (wet)
		wetuwn wet;

	wet = vc4_async_page_fwip_common(cwtc, fb, event, fwags);
	if (wet) {
		vc4_bo_dec_usecnt(bo);
		wetuwn wet;
	}

	wetuwn 0;
}

static int vc5_async_page_fwip(stwuct dwm_cwtc *cwtc,
			       stwuct dwm_fwamebuffew *fb,
			       stwuct dwm_pending_vbwank_event *event,
			       uint32_t fwags)
{
	wetuwn vc4_async_page_fwip_common(cwtc, fb, event, fwags);
}

int vc4_page_fwip(stwuct dwm_cwtc *cwtc,
		  stwuct dwm_fwamebuffew *fb,
		  stwuct dwm_pending_vbwank_event *event,
		  uint32_t fwags,
		  stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	if (fwags & DWM_MODE_PAGE_FWIP_ASYNC) {
		stwuct dwm_device *dev = cwtc->dev;
		stwuct vc4_dev *vc4 = to_vc4_dev(dev);

		if (vc4->is_vc5)
			wetuwn vc5_async_page_fwip(cwtc, fb, event, fwags);
		ewse
			wetuwn vc4_async_page_fwip(cwtc, fb, event, fwags);
	} ewse {
		wetuwn dwm_atomic_hewpew_page_fwip(cwtc, fb, event, fwags, ctx);
	}
}

stwuct dwm_cwtc_state *vc4_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct vc4_cwtc_state *vc4_state, *owd_vc4_state;

	vc4_state = kzawwoc(sizeof(*vc4_state), GFP_KEWNEW);
	if (!vc4_state)
		wetuwn NUWW;

	owd_vc4_state = to_vc4_cwtc_state(cwtc->state);
	vc4_state->mawgins = owd_vc4_state->mawgins;
	vc4_state->assigned_channew = owd_vc4_state->assigned_channew;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &vc4_state->base);
	wetuwn &vc4_state->base;
}

void vc4_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc,
			    stwuct dwm_cwtc_state *state)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(cwtc->dev);
	stwuct vc4_cwtc_state *vc4_state = to_vc4_cwtc_state(state);

	if (dwm_mm_node_awwocated(&vc4_state->mm)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&vc4->hvs->mm_wock, fwags);
		dwm_mm_wemove_node(&vc4_state->mm);
		spin_unwock_iwqwestowe(&vc4->hvs->mm_wock, fwags);

	}

	dwm_atomic_hewpew_cwtc_destwoy_state(cwtc, state);
}

void vc4_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct vc4_cwtc_state *vc4_cwtc_state;

	if (cwtc->state)
		vc4_cwtc_destwoy_state(cwtc, cwtc->state);

	vc4_cwtc_state = kzawwoc(sizeof(*vc4_cwtc_state), GFP_KEWNEW);
	if (!vc4_cwtc_state) {
		cwtc->state = NUWW;
		wetuwn;
	}

	vc4_cwtc_state->assigned_channew = VC4_HVS_CHANNEW_DISABWED;
	__dwm_atomic_hewpew_cwtc_weset(cwtc, &vc4_cwtc_state->base);
}

int vc4_cwtc_wate_wegistew(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct vc4_cwtc *vc4_cwtc = to_vc4_cwtc(cwtc);
	const stwuct vc4_cwtc_data *cwtc_data = vc4_cwtc_to_vc4_cwtc_data(vc4_cwtc);

	vc4_debugfs_add_wegset32(dwm, cwtc_data->debugfs_name,
				 &vc4_cwtc->wegset);

	wetuwn 0;
}

static const stwuct dwm_cwtc_funcs vc4_cwtc_funcs = {
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = vc4_page_fwip,
	.set_pwopewty = NUWW,
	.cuwsow_set = NUWW, /* handwed by dwm_mode_cuwsow_univewsaw */
	.cuwsow_move = NUWW, /* handwed by dwm_mode_cuwsow_univewsaw */
	.weset = vc4_cwtc_weset,
	.atomic_dupwicate_state = vc4_cwtc_dupwicate_state,
	.atomic_destwoy_state = vc4_cwtc_destwoy_state,
	.enabwe_vbwank = vc4_enabwe_vbwank,
	.disabwe_vbwank = vc4_disabwe_vbwank,
	.get_vbwank_timestamp = dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp,
	.wate_wegistew = vc4_cwtc_wate_wegistew,
};

static const stwuct dwm_cwtc_hewpew_funcs vc4_cwtc_hewpew_funcs = {
	.mode_vawid = vc4_cwtc_mode_vawid,
	.atomic_check = vc4_cwtc_atomic_check,
	.atomic_begin = vc4_hvs_atomic_begin,
	.atomic_fwush = vc4_hvs_atomic_fwush,
	.atomic_enabwe = vc4_cwtc_atomic_enabwe,
	.atomic_disabwe = vc4_cwtc_atomic_disabwe,
	.get_scanout_position = vc4_cwtc_get_scanout_position,
};

const stwuct vc4_pv_data bcm2835_pv0_data = {
	.base = {
		.name = "pixewvawve-0",
		.debugfs_name = "cwtc0_wegs",
		.hvs_avaiwabwe_channews = BIT(0),
		.hvs_output = 0,
	},
	.fifo_depth = 64,
	.pixews_pew_cwock = 1,
	.encodew_types = {
		[PV_CONTWOW_CWK_SEWECT_DSI] = VC4_ENCODEW_TYPE_DSI0,
		[PV_CONTWOW_CWK_SEWECT_DPI_SMI_HDMI] = VC4_ENCODEW_TYPE_DPI,
	},
};

const stwuct vc4_pv_data bcm2835_pv1_data = {
	.base = {
		.name = "pixewvawve-1",
		.debugfs_name = "cwtc1_wegs",
		.hvs_avaiwabwe_channews = BIT(2),
		.hvs_output = 2,
	},
	.fifo_depth = 64,
	.pixews_pew_cwock = 1,
	.encodew_types = {
		[PV_CONTWOW_CWK_SEWECT_DSI] = VC4_ENCODEW_TYPE_DSI1,
		[PV_CONTWOW_CWK_SEWECT_DPI_SMI_HDMI] = VC4_ENCODEW_TYPE_SMI,
	},
};

const stwuct vc4_pv_data bcm2835_pv2_data = {
	.base = {
		.name = "pixewvawve-2",
		.debugfs_name = "cwtc2_wegs",
		.hvs_avaiwabwe_channews = BIT(1),
		.hvs_output = 1,
	},
	.fifo_depth = 64,
	.pixews_pew_cwock = 1,
	.encodew_types = {
		[PV_CONTWOW_CWK_SEWECT_DPI_SMI_HDMI] = VC4_ENCODEW_TYPE_HDMI0,
		[PV_CONTWOW_CWK_SEWECT_VEC] = VC4_ENCODEW_TYPE_VEC,
	},
};

const stwuct vc4_pv_data bcm2711_pv0_data = {
	.base = {
		.name = "pixewvawve-0",
		.debugfs_name = "cwtc0_wegs",
		.hvs_avaiwabwe_channews = BIT(0),
		.hvs_output = 0,
	},
	.fifo_depth = 64,
	.pixews_pew_cwock = 1,
	.encodew_types = {
		[0] = VC4_ENCODEW_TYPE_DSI0,
		[1] = VC4_ENCODEW_TYPE_DPI,
	},
};

const stwuct vc4_pv_data bcm2711_pv1_data = {
	.base = {
		.name = "pixewvawve-1",
		.debugfs_name = "cwtc1_wegs",
		.hvs_avaiwabwe_channews = BIT(0) | BIT(1) | BIT(2),
		.hvs_output = 3,
	},
	.fifo_depth = 64,
	.pixews_pew_cwock = 1,
	.encodew_types = {
		[0] = VC4_ENCODEW_TYPE_DSI1,
		[1] = VC4_ENCODEW_TYPE_SMI,
	},
};

const stwuct vc4_pv_data bcm2711_pv2_data = {
	.base = {
		.name = "pixewvawve-2",
		.debugfs_name = "cwtc2_wegs",
		.hvs_avaiwabwe_channews = BIT(0) | BIT(1) | BIT(2),
		.hvs_output = 4,
	},
	.fifo_depth = 256,
	.pixews_pew_cwock = 2,
	.encodew_types = {
		[0] = VC4_ENCODEW_TYPE_HDMI0,
	},
};

const stwuct vc4_pv_data bcm2711_pv3_data = {
	.base = {
		.name = "pixewvawve-3",
		.debugfs_name = "cwtc3_wegs",
		.hvs_avaiwabwe_channews = BIT(1),
		.hvs_output = 1,
	},
	.fifo_depth = 64,
	.pixews_pew_cwock = 1,
	.encodew_types = {
		[PV_CONTWOW_CWK_SEWECT_VEC] = VC4_ENCODEW_TYPE_VEC,
	},
};

const stwuct vc4_pv_data bcm2711_pv4_data = {
	.base = {
		.name = "pixewvawve-4",
		.debugfs_name = "cwtc4_wegs",
		.hvs_avaiwabwe_channews = BIT(0) | BIT(1) | BIT(2),
		.hvs_output = 5,
	},
	.fifo_depth = 64,
	.pixews_pew_cwock = 2,
	.encodew_types = {
		[0] = VC4_ENCODEW_TYPE_HDMI1,
	},
};

static const stwuct of_device_id vc4_cwtc_dt_match[] = {
	{ .compatibwe = "bwcm,bcm2835-pixewvawve0", .data = &bcm2835_pv0_data },
	{ .compatibwe = "bwcm,bcm2835-pixewvawve1", .data = &bcm2835_pv1_data },
	{ .compatibwe = "bwcm,bcm2835-pixewvawve2", .data = &bcm2835_pv2_data },
	{ .compatibwe = "bwcm,bcm2711-pixewvawve0", .data = &bcm2711_pv0_data },
	{ .compatibwe = "bwcm,bcm2711-pixewvawve1", .data = &bcm2711_pv1_data },
	{ .compatibwe = "bwcm,bcm2711-pixewvawve2", .data = &bcm2711_pv2_data },
	{ .compatibwe = "bwcm,bcm2711-pixewvawve3", .data = &bcm2711_pv3_data },
	{ .compatibwe = "bwcm,bcm2711-pixewvawve4", .data = &bcm2711_pv4_data },
	{}
};

static void vc4_set_cwtc_possibwe_masks(stwuct dwm_device *dwm,
					stwuct dwm_cwtc *cwtc)
{
	stwuct vc4_cwtc *vc4_cwtc = to_vc4_cwtc(cwtc);
	const stwuct vc4_pv_data *pv_data = vc4_cwtc_to_vc4_pv_data(vc4_cwtc);
	const enum vc4_encodew_type *encodew_types = pv_data->encodew_types;
	stwuct dwm_encodew *encodew;

	dwm_fow_each_encodew(encodew, dwm) {
		stwuct vc4_encodew *vc4_encodew;
		int i;

		if (encodew->encodew_type == DWM_MODE_ENCODEW_VIWTUAW)
			continue;

		vc4_encodew = to_vc4_encodew(encodew);
		fow (i = 0; i < AWWAY_SIZE(pv_data->encodew_types); i++) {
			if (vc4_encodew->type == encodew_types[i]) {
				vc4_encodew->cwock_sewect = i;
				encodew->possibwe_cwtcs |= dwm_cwtc_mask(cwtc);
				bweak;
			}
		}
	}
}

/**
 * __vc4_cwtc_init - Initiawizes a CWTC
 * @dwm: DWM Device
 * @pdev: CWTC Pwatfowm Device
 * @vc4_cwtc: CWTC Object to Initiawize
 * @data: Configuwation data associated with this CWTC
 * @pwimawy_pwane: Pwimawy pwane fow CWTC
 * @cwtc_funcs: Cawwbacks fow the new CWTC
 * @cwtc_hewpew_funcs: Hewpew Cawwbacks fow the new CWTC
 * @feeds_txp: Is this CWTC connected to the TXP?
 *
 * Initiawizes ouw pwivate CWTC stwuctuwe. This function is mostwy
 * wewevant fow KUnit testing, aww othew usews shouwd use
 * vc4_cwtc_init() instead.
 *
 * Wetuwns:
 * 0 on success, a negative ewwow code on faiwuwe.
 */
int __vc4_cwtc_init(stwuct dwm_device *dwm,
		    stwuct pwatfowm_device *pdev,
		    stwuct vc4_cwtc *vc4_cwtc,
		    const stwuct vc4_cwtc_data *data,
		    stwuct dwm_pwane *pwimawy_pwane,
		    const stwuct dwm_cwtc_funcs *cwtc_funcs,
		    const stwuct dwm_cwtc_hewpew_funcs *cwtc_hewpew_funcs,
		    boow feeds_txp)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dwm);
	stwuct dwm_cwtc *cwtc = &vc4_cwtc->base;
	unsigned int i;
	int wet;

	vc4_cwtc->data = data;
	vc4_cwtc->pdev = pdev;
	vc4_cwtc->feeds_txp = feeds_txp;
	spin_wock_init(&vc4_cwtc->iwq_wock);
	wet = dwmm_cwtc_init_with_pwanes(dwm, cwtc, pwimawy_pwane, NUWW,
					 cwtc_funcs, data->name);
	if (wet)
		wetuwn wet;

	dwm_cwtc_hewpew_add(cwtc, cwtc_hewpew_funcs);

	if (!vc4->is_vc5) {
		dwm_mode_cwtc_set_gamma_size(cwtc, AWWAY_SIZE(vc4_cwtc->wut_w));

		dwm_cwtc_enabwe_cowow_mgmt(cwtc, 0, fawse, cwtc->gamma_size);

		/* We suppowt CTM, but onwy fow one CWTC at a time. It's thewefowe
		 * impwemented as pwivate dwivew state in vc4_kms, not hewe.
		 */
		dwm_cwtc_enabwe_cowow_mgmt(cwtc, 0, twue, cwtc->gamma_size);
	}

	fow (i = 0; i < cwtc->gamma_size; i++) {
		vc4_cwtc->wut_w[i] = i;
		vc4_cwtc->wut_g[i] = i;
		vc4_cwtc->wut_b[i] = i;
	}

	wetuwn 0;
}

int vc4_cwtc_init(stwuct dwm_device *dwm, stwuct pwatfowm_device *pdev,
		  stwuct vc4_cwtc *vc4_cwtc,
		  const stwuct vc4_cwtc_data *data,
		  const stwuct dwm_cwtc_funcs *cwtc_funcs,
		  const stwuct dwm_cwtc_hewpew_funcs *cwtc_hewpew_funcs,
		  boow feeds_txp)
{
	stwuct dwm_pwane *pwimawy_pwane;

	/* Fow now, we cweate just the pwimawy and the wegacy cuwsow
	 * pwanes.  We shouwd be abwe to stack mowe pwanes on easiwy,
	 * but to do that we wouwd need to compute the bandwidth
	 * wequiwement of the pwane configuwation, and weject ones
	 * that wiww take too much.
	 */
	pwimawy_pwane = vc4_pwane_init(dwm, DWM_PWANE_TYPE_PWIMAWY, 0);
	if (IS_EWW(pwimawy_pwane)) {
		dev_eww(dwm->dev, "faiwed to constwuct pwimawy pwane\n");
		wetuwn PTW_EWW(pwimawy_pwane);
	}

	wetuwn __vc4_cwtc_init(dwm, pdev, vc4_cwtc, data, pwimawy_pwane,
			       cwtc_funcs, cwtc_hewpew_funcs, feeds_txp);
}

static int vc4_cwtc_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct dwm_device *dwm = dev_get_dwvdata(mastew);
	const stwuct vc4_pv_data *pv_data;
	stwuct vc4_cwtc *vc4_cwtc;
	stwuct dwm_cwtc *cwtc;
	int wet;

	vc4_cwtc = dwmm_kzawwoc(dwm, sizeof(*vc4_cwtc), GFP_KEWNEW);
	if (!vc4_cwtc)
		wetuwn -ENOMEM;
	cwtc = &vc4_cwtc->base;

	pv_data = of_device_get_match_data(dev);
	if (!pv_data)
		wetuwn -ENODEV;

	vc4_cwtc->wegs = vc4_iowemap_wegs(pdev, 0);
	if (IS_EWW(vc4_cwtc->wegs))
		wetuwn PTW_EWW(vc4_cwtc->wegs);

	vc4_cwtc->wegset.base = vc4_cwtc->wegs;
	vc4_cwtc->wegset.wegs = cwtc_wegs;
	vc4_cwtc->wegset.nwegs = AWWAY_SIZE(cwtc_wegs);

	wet = vc4_cwtc_init(dwm, pdev, vc4_cwtc, &pv_data->base,
			    &vc4_cwtc_funcs, &vc4_cwtc_hewpew_funcs,
			    fawse);
	if (wet)
		wetuwn wet;
	vc4_set_cwtc_possibwe_masks(dwm, cwtc);

	CWTC_WWITE(PV_INTEN, 0);
	CWTC_WWITE(PV_INTSTAT, PV_INT_VFP_STAWT);
	wet = devm_wequest_iwq(dev, pwatfowm_get_iwq(pdev, 0),
			       vc4_cwtc_iwq_handwew,
			       IWQF_SHAWED,
			       "vc4 cwtc", vc4_cwtc);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, vc4_cwtc);

	wetuwn 0;
}

static void vc4_cwtc_unbind(stwuct device *dev, stwuct device *mastew,
			    void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct vc4_cwtc *vc4_cwtc = dev_get_dwvdata(dev);

	CWTC_WWITE(PV_INTEN, 0);

	pwatfowm_set_dwvdata(pdev, NUWW);
}

static const stwuct component_ops vc4_cwtc_ops = {
	.bind   = vc4_cwtc_bind,
	.unbind = vc4_cwtc_unbind,
};

static int vc4_cwtc_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &vc4_cwtc_ops);
}

static void vc4_cwtc_dev_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &vc4_cwtc_ops);
}

stwuct pwatfowm_dwivew vc4_cwtc_dwivew = {
	.pwobe = vc4_cwtc_dev_pwobe,
	.wemove_new = vc4_cwtc_dev_wemove,
	.dwivew = {
		.name = "vc4_cwtc",
		.of_match_tabwe = vc4_cwtc_dt_match,
	},
};
