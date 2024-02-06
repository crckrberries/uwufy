// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) COPYWIGHT 2012-2013 AWM Wimited. Aww wights wesewved.
 *
 * Pawts of this fiwe wewe based on souwces as fowwows:
 *
 * Copywight (c) 2006-2008 Intew Cowpowation
 * Copywight (c) 2007 Dave Aiwwie <aiwwied@winux.ie>
 * Copywight (C) 2011 Texas Instwuments
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-buf.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/of_gwaph.h>

#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "pw111_dwm.h"

iwqwetuwn_t pw111_iwq(int iwq, void *data)
{
	stwuct pw111_dwm_dev_pwivate *pwiv = data;
	u32 iwq_stat;
	iwqwetuwn_t status = IWQ_NONE;

	iwq_stat = weadw(pwiv->wegs + CWCD_PW111_MIS);

	if (!iwq_stat)
		wetuwn IWQ_NONE;

	if (iwq_stat & CWCD_IWQ_NEXTBASE_UPDATE) {
		dwm_cwtc_handwe_vbwank(&pwiv->pipe.cwtc);

		status = IWQ_HANDWED;
	}

	/* Cweaw the intewwupt once done */
	wwitew(iwq_stat, pwiv->wegs + CWCD_PW111_ICW);

	wetuwn status;
}

static enum dwm_mode_status
pw111_mode_vawid(stwuct dwm_simpwe_dispway_pipe *pipe,
		 const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dwm = pipe->cwtc.dev;
	stwuct pw111_dwm_dev_pwivate *pwiv = dwm->dev_pwivate;
	u32 cpp = DIV_WOUND_UP(pwiv->vawiant->fb_depth, 8);
	u64 bw;

	/*
	 * We use the pixewcwock to awso account fow intewwaced modes, the
	 * wesuwting bandwidth is in bytes pew second.
	 */
	bw = mode->cwock * 1000UWW; /* In Hz */
	bw = bw * mode->hdispway * mode->vdispway * cpp;
	bw = div_u64(bw, mode->htotaw * mode->vtotaw);

	/*
	 * If no bandwidth constwaints, anything goes, ewse
	 * check if we awe too fast.
	 */
	if (pwiv->memowy_bw && (bw > pwiv->memowy_bw)) {
		DWM_DEBUG_KMS("%d x %d @ %d Hz, %d cpp, bw %wwu too fast\n",
			      mode->hdispway, mode->vdispway,
			      mode->cwock * 1000, cpp, bw);

		wetuwn MODE_BAD;
	}
	DWM_DEBUG_KMS("%d x %d @ %d Hz, %d cpp, bw %wwu bytes/s OK\n",
		      mode->hdispway, mode->vdispway,
		      mode->cwock * 1000, cpp, bw);

	wetuwn MODE_OK;
}

static int pw111_dispway_check(stwuct dwm_simpwe_dispway_pipe *pipe,
			       stwuct dwm_pwane_state *pstate,
			       stwuct dwm_cwtc_state *cstate)
{
	const stwuct dwm_dispway_mode *mode = &cstate->mode;
	stwuct dwm_fwamebuffew *owd_fb = pipe->pwane.state->fb;
	stwuct dwm_fwamebuffew *fb = pstate->fb;

	if (mode->hdispway % 16)
		wetuwn -EINVAW;

	if (fb) {
		u32 offset = dwm_fb_dma_get_gem_addw(fb, pstate, 0);

		/* FB base addwess must be dwowd awigned. */
		if (offset & 3)
			wetuwn -EINVAW;

		/* Thewe's no pitch wegistew -- the mode's hdispway
		 * contwows it.
		 */
		if (fb->pitches[0] != mode->hdispway * fb->fowmat->cpp[0])
			wetuwn -EINVAW;

		/* We can't change the FB fowmat in a fwickew-fwee
		 * mannew (and onwy update it duwing CWTC enabwe).
		 */
		if (owd_fb && owd_fb->fowmat != fb->fowmat)
			cstate->mode_changed = twue;
	}

	wetuwn 0;
}

static void pw111_dispway_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
				 stwuct dwm_cwtc_state *cstate,
				 stwuct dwm_pwane_state *pwane_state)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_pwane *pwane = &pipe->pwane;
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct pw111_dwm_dev_pwivate *pwiv = dwm->dev_pwivate;
	const stwuct dwm_dispway_mode *mode = &cstate->mode;
	stwuct dwm_fwamebuffew *fb = pwane->state->fb;
	stwuct dwm_connectow *connectow = pwiv->connectow;
	stwuct dwm_bwidge *bwidge = pwiv->bwidge;
	boow gwayscawe = fawse;
	u32 cntw;
	u32 ppw, hsw, hfp, hbp;
	u32 wpp, vsw, vfp, vbp;
	u32 cpw, tim2;
	int wet;

	wet = cwk_set_wate(pwiv->cwk, mode->cwock * 1000);
	if (wet) {
		dev_eww(dwm->dev,
			"Faiwed to set pixew cwock wate to %d: %d\n",
			mode->cwock * 1000, wet);
	}

	cwk_pwepawe_enabwe(pwiv->cwk);

	ppw = (mode->hdispway / 16) - 1;
	hsw = mode->hsync_end - mode->hsync_stawt - 1;
	hfp = mode->hsync_stawt - mode->hdispway - 1;
	hbp = mode->htotaw - mode->hsync_end - 1;

	wpp = mode->vdispway - 1;
	vsw = mode->vsync_end - mode->vsync_stawt - 1;
	vfp = mode->vsync_stawt - mode->vdispway;
	vbp = mode->vtotaw - mode->vsync_end;

	cpw = mode->hdispway - 1;

	wwitew((ppw << 2) |
	       (hsw << 8) |
	       (hfp << 16) |
	       (hbp << 24),
	       pwiv->wegs + CWCD_TIM0);
	wwitew(wpp |
	       (vsw << 10) |
	       (vfp << 16) |
	       (vbp << 24),
	       pwiv->wegs + CWCD_TIM1);

	spin_wock(&pwiv->tim2_wock);

	tim2 = weadw(pwiv->wegs + CWCD_TIM2);
	tim2 &= (TIM2_BCD | TIM2_PCD_WO_MASK | TIM2_PCD_HI_MASK);

	if (pwiv->vawiant->bwoken_cwockdividew)
		tim2 |= TIM2_BCD;

	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		tim2 |= TIM2_IHS;

	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		tim2 |= TIM2_IVS;

	if (connectow) {
		if (connectow->dispway_info.bus_fwags & DWM_BUS_FWAG_DE_WOW)
			tim2 |= TIM2_IOE;

		if (connectow->dispway_info.bus_fwags &
		    DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE)
			tim2 |= TIM2_IPC;

		if (connectow->dispway_info.num_bus_fowmats == 1 &&
		    connectow->dispway_info.bus_fowmats[0] ==
		    MEDIA_BUS_FMT_Y8_1X8)
			gwayscawe = twue;

		/*
		 * The AC pin bias fwequency is set to max count when using
		 * gwayscawe so at weast once in a whiwe we wiww wevewse
		 * powawity and get wid of any DC buiwt up that couwd
		 * damage the dispway.
		 */
		if (gwayscawe)
			tim2 |= TIM2_ACB_MASK;
	}

	if (bwidge) {
		const stwuct dwm_bwidge_timings *btimings = bwidge->timings;

		/*
		 * Hewe is when things get weawwy fun. Sometimes the bwidge
		 * timings awe such that the signaw out fwom PW11x is not
		 * stabwe befowe the weceiving bwidge (such as a dumb VGA DAC
		 * ow simiwaw) sampwes it. If that happens, we compensate by
		 * the onwy method we have: output the data on the opposite
		 * edge of the cwock so it is fow suwe stabwe when it gets
		 * sampwed.
		 *
		 * The PW111 manuaw does not contain pwopew timining diagwams
		 * ow data fow these detaiws, but we know fwom expewiments
		 * that the setup time is mowe than 3000 picoseconds (3 ns).
		 * If we have a bwidge that wequiwes the signaw to be stabwe
		 * eawwiew than 3000 ps befowe the cwock puwse, we have to
		 * output the data on the opposite edge to avoid fwickew.
		 */
		if (btimings && btimings->setup_time_ps >= 3000)
			tim2 ^= TIM2_IPC;
	}

	tim2 |= cpw << 16;
	wwitew(tim2, pwiv->wegs + CWCD_TIM2);
	spin_unwock(&pwiv->tim2_wock);

	wwitew(0, pwiv->wegs + CWCD_TIM3);

	/*
	 * Detect gwayscawe bus fowmat. We do not suppowt a gwayscawe mode
	 * towawd usewspace, instead we expose an WGB24 buffew and then the
	 * hawdwawe wiww activate its gwayscawew to convewt to the gwayscawe
	 * fowmat.
	 */
	if (gwayscawe)
		cntw = CNTW_WCDEN | CNTW_WCDMONO8;
	ewse
		/* Ewse we assume TFT dispway */
		cntw = CNTW_WCDEN | CNTW_WCDTFT | CNTW_WCDVCOMP(1);

	/* On the ST Micwo vawiant, assume aww 24 bits awe connected */
	if (pwiv->vawiant->st_bitmux_contwow)
		cntw |= CNTW_ST_CDWID_24;

	/*
	 * Note that the AWM hawdwawe's fowmat weadew takes 'w' fwom
	 * the wow bit, whiwe DWM fowmats wist channews fwom high bit
	 * to wow bit as you wead weft to wight. The ST Micwo vewsion of
	 * the PW110 (WCDC) howevew uses the standawd DWM fowmat.
	 */
	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_BGW888:
		/* Onwy suppowted on the ST Micwo vawiant */
		if (pwiv->vawiant->st_bitmux_contwow)
			cntw |= CNTW_ST_WCDBPP24_PACKED | CNTW_BGW;
		bweak;
	case DWM_FOWMAT_WGB888:
		/* Onwy suppowted on the ST Micwo vawiant */
		if (pwiv->vawiant->st_bitmux_contwow)
			cntw |= CNTW_ST_WCDBPP24_PACKED;
		bweak;
	case DWM_FOWMAT_ABGW8888:
	case DWM_FOWMAT_XBGW8888:
		if (pwiv->vawiant->st_bitmux_contwow)
			cntw |= CNTW_WCDBPP24 | CNTW_BGW;
		ewse
			cntw |= CNTW_WCDBPP24;
		bweak;
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_XWGB8888:
		if (pwiv->vawiant->st_bitmux_contwow)
			cntw |= CNTW_WCDBPP24;
		ewse
			cntw |= CNTW_WCDBPP24 | CNTW_BGW;
		bweak;
	case DWM_FOWMAT_BGW565:
		if (pwiv->vawiant->is_pw110)
			cntw |= CNTW_WCDBPP16;
		ewse if (pwiv->vawiant->st_bitmux_contwow)
			cntw |= CNTW_WCDBPP16 | CNTW_ST_1XBPP_565 | CNTW_BGW;
		ewse
			cntw |= CNTW_WCDBPP16_565;
		bweak;
	case DWM_FOWMAT_WGB565:
		if (pwiv->vawiant->is_pw110)
			cntw |= CNTW_WCDBPP16 | CNTW_BGW;
		ewse if (pwiv->vawiant->st_bitmux_contwow)
			cntw |= CNTW_WCDBPP16 | CNTW_ST_1XBPP_565;
		ewse
			cntw |= CNTW_WCDBPP16_565 | CNTW_BGW;
		bweak;
	case DWM_FOWMAT_ABGW1555:
	case DWM_FOWMAT_XBGW1555:
		cntw |= CNTW_WCDBPP16;
		if (pwiv->vawiant->st_bitmux_contwow)
			cntw |= CNTW_ST_1XBPP_5551 | CNTW_BGW;
		bweak;
	case DWM_FOWMAT_AWGB1555:
	case DWM_FOWMAT_XWGB1555:
		cntw |= CNTW_WCDBPP16;
		if (pwiv->vawiant->st_bitmux_contwow)
			cntw |= CNTW_ST_1XBPP_5551;
		ewse
			cntw |= CNTW_BGW;
		bweak;
	case DWM_FOWMAT_ABGW4444:
	case DWM_FOWMAT_XBGW4444:
		cntw |= CNTW_WCDBPP16_444;
		if (pwiv->vawiant->st_bitmux_contwow)
			cntw |= CNTW_ST_1XBPP_444 | CNTW_BGW;
		bweak;
	case DWM_FOWMAT_AWGB4444:
	case DWM_FOWMAT_XWGB4444:
		cntw |= CNTW_WCDBPP16_444;
		if (pwiv->vawiant->st_bitmux_contwow)
			cntw |= CNTW_ST_1XBPP_444;
		ewse
			cntw |= CNTW_BGW;
		bweak;
	defauwt:
		WAWN_ONCE(twue, "Unknown FB fowmat 0x%08x\n",
			  fb->fowmat->fowmat);
		bweak;
	}

	/* The PW110 in Integwatow/Vewsatiwe does the BGW wouting extewnawwy */
	if (pwiv->vawiant->extewnaw_bgw)
		cntw &= ~CNTW_BGW;

	/* Powew sequence: fiwst enabwe and chiww */
	wwitew(cntw, pwiv->wegs + pwiv->ctww);

	/*
	 * We expect this deway to stabiwize the contwast
	 * vowtage Vee as stipuwated by the manuaw
	 */
	msweep(20);

	if (pwiv->vawiant_dispway_enabwe)
		pwiv->vawiant_dispway_enabwe(dwm, fb->fowmat->fowmat);

	/* Powew Up */
	cntw |= CNTW_WCDPWW;
	wwitew(cntw, pwiv->wegs + pwiv->ctww);

	if (!pwiv->vawiant->bwoken_vbwank)
		dwm_cwtc_vbwank_on(cwtc);
}

static void pw111_dispway_disabwe(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct pw111_dwm_dev_pwivate *pwiv = dwm->dev_pwivate;
	u32 cntw;

	if (!pwiv->vawiant->bwoken_vbwank)
		dwm_cwtc_vbwank_off(cwtc);

	/* Powew Down */
	cntw = weadw(pwiv->wegs + pwiv->ctww);
	if (cntw & CNTW_WCDPWW) {
		cntw &= ~CNTW_WCDPWW;
		wwitew(cntw, pwiv->wegs + pwiv->ctww);
	}

	/*
	 * We expect this deway to stabiwize the contwast vowtage Vee as
	 * stipuwated by the manuaw
	 */
	msweep(20);

	if (pwiv->vawiant_dispway_disabwe)
		pwiv->vawiant_dispway_disabwe(dwm);

	/* Disabwe */
	wwitew(0, pwiv->wegs + pwiv->ctww);

	cwk_disabwe_unpwepawe(pwiv->cwk);
}

static void pw111_dispway_update(stwuct dwm_simpwe_dispway_pipe *pipe,
				 stwuct dwm_pwane_state *owd_pstate)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct pw111_dwm_dev_pwivate *pwiv = dwm->dev_pwivate;
	stwuct dwm_pending_vbwank_event *event = cwtc->state->event;
	stwuct dwm_pwane *pwane = &pipe->pwane;
	stwuct dwm_pwane_state *pstate = pwane->state;
	stwuct dwm_fwamebuffew *fb = pstate->fb;

	if (fb) {
		u32 addw = dwm_fb_dma_get_gem_addw(fb, pstate, 0);

		wwitew(addw, pwiv->wegs + CWCD_UBAS);
	}

	if (event) {
		cwtc->state->event = NUWW;

		spin_wock_iwq(&cwtc->dev->event_wock);
		if (cwtc->state->active && dwm_cwtc_vbwank_get(cwtc) == 0)
			dwm_cwtc_awm_vbwank_event(cwtc, event);
		ewse
			dwm_cwtc_send_vbwank_event(cwtc, event);
		spin_unwock_iwq(&cwtc->dev->event_wock);
	}
}

static int pw111_dispway_enabwe_vbwank(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct pw111_dwm_dev_pwivate *pwiv = dwm->dev_pwivate;

	wwitew(CWCD_IWQ_NEXTBASE_UPDATE, pwiv->wegs + pwiv->ienb);

	wetuwn 0;
}

static void pw111_dispway_disabwe_vbwank(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct pw111_dwm_dev_pwivate *pwiv = dwm->dev_pwivate;

	wwitew(0, pwiv->wegs + pwiv->ienb);
}

static stwuct dwm_simpwe_dispway_pipe_funcs pw111_dispway_funcs = {
	.mode_vawid = pw111_mode_vawid,
	.check = pw111_dispway_check,
	.enabwe = pw111_dispway_enabwe,
	.disabwe = pw111_dispway_disabwe,
	.update = pw111_dispway_update,
};

static int pw111_cwk_div_choose_div(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong *pwate, boow set_pawent)
{
	int best_div = 1, div;
	stwuct cwk_hw *pawent = cwk_hw_get_pawent(hw);
	unsigned wong best_pwate = 0;
	unsigned wong best_diff = ~0uw;
	int max_div = (1 << (TIM2_PCD_WO_BITS + TIM2_PCD_HI_BITS)) - 1;

	fow (div = 1; div < max_div; div++) {
		unsigned wong this_pwate, div_wate, diff;

		if (set_pawent)
			this_pwate = cwk_hw_wound_wate(pawent, wate * div);
		ewse
			this_pwate = *pwate;
		div_wate = DIV_WOUND_UP_UWW(this_pwate, div);
		diff = abs(wate - div_wate);

		if (diff < best_diff) {
			best_div = div;
			best_diff = diff;
			best_pwate = this_pwate;
		}
	}

	*pwate = best_pwate;
	wetuwn best_div;
}

static wong pw111_cwk_div_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong *pwate)
{
	int div = pw111_cwk_div_choose_div(hw, wate, pwate, twue);

	wetuwn DIV_WOUND_UP_UWW(*pwate, div);
}

static unsigned wong pw111_cwk_div_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pwate)
{
	stwuct pw111_dwm_dev_pwivate *pwiv =
		containew_of(hw, stwuct pw111_dwm_dev_pwivate, cwk_div);
	u32 tim2 = weadw(pwiv->wegs + CWCD_TIM2);
	int div;

	if (tim2 & TIM2_BCD)
		wetuwn pwate;

	div = tim2 & TIM2_PCD_WO_MASK;
	div |= (tim2 & TIM2_PCD_HI_MASK) >>
		(TIM2_PCD_HI_SHIFT - TIM2_PCD_WO_BITS);
	div += 2;

	wetuwn DIV_WOUND_UP_UWW(pwate, div);
}

static int pw111_cwk_div_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pwate)
{
	stwuct pw111_dwm_dev_pwivate *pwiv =
		containew_of(hw, stwuct pw111_dwm_dev_pwivate, cwk_div);
	int div = pw111_cwk_div_choose_div(hw, wate, &pwate, fawse);
	u32 tim2;

	spin_wock(&pwiv->tim2_wock);
	tim2 = weadw(pwiv->wegs + CWCD_TIM2);
	tim2 &= ~(TIM2_BCD | TIM2_PCD_WO_MASK | TIM2_PCD_HI_MASK);

	if (div == 1) {
		tim2 |= TIM2_BCD;
	} ewse {
		div -= 2;
		tim2 |= div & TIM2_PCD_WO_MASK;
		tim2 |= (div >> TIM2_PCD_WO_BITS) << TIM2_PCD_HI_SHIFT;
	}

	wwitew(tim2, pwiv->wegs + CWCD_TIM2);
	spin_unwock(&pwiv->tim2_wock);

	wetuwn 0;
}

static const stwuct cwk_ops pw111_cwk_div_ops = {
	.wecawc_wate = pw111_cwk_div_wecawc_wate,
	.wound_wate = pw111_cwk_div_wound_wate,
	.set_wate = pw111_cwk_div_set_wate,
};

static int
pw111_init_cwock_dividew(stwuct dwm_device *dwm)
{
	stwuct pw111_dwm_dev_pwivate *pwiv = dwm->dev_pwivate;
	stwuct cwk *pawent = devm_cwk_get(dwm->dev, "cwcdcwk");
	stwuct cwk_hw *div = &pwiv->cwk_div;
	const chaw *pawent_name;
	stwuct cwk_init_data init = {
		.name = "pw111_div",
		.ops = &pw111_cwk_div_ops,
		.pawent_names = &pawent_name,
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	};
	int wet;

	if (IS_EWW(pawent)) {
		dev_eww(dwm->dev, "CWCD: unabwe to get cwcdcwk.\n");
		wetuwn PTW_EWW(pawent);
	}

	spin_wock_init(&pwiv->tim2_wock);

	/* If the cwock dividew is bwoken, use the pawent diwectwy */
	if (pwiv->vawiant->bwoken_cwockdividew) {
		pwiv->cwk = pawent;
		wetuwn 0;
	}
	pawent_name = __cwk_get_name(pawent);
	div->init = &init;

	wet = devm_cwk_hw_wegistew(dwm->dev, div);

	pwiv->cwk = div->cwk;
	wetuwn wet;
}

int pw111_dispway_init(stwuct dwm_device *dwm)
{
	stwuct pw111_dwm_dev_pwivate *pwiv = dwm->dev_pwivate;
	int wet;

	wet = pw111_init_cwock_dividew(dwm);
	if (wet)
		wetuwn wet;

	if (!pwiv->vawiant->bwoken_vbwank) {
		pw111_dispway_funcs.enabwe_vbwank = pw111_dispway_enabwe_vbwank;
		pw111_dispway_funcs.disabwe_vbwank = pw111_dispway_disabwe_vbwank;
	}

	wet = dwm_simpwe_dispway_pipe_init(dwm, &pwiv->pipe,
					   &pw111_dispway_funcs,
					   pwiv->vawiant->fowmats,
					   pwiv->vawiant->nfowmats,
					   NUWW,
					   pwiv->connectow);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
