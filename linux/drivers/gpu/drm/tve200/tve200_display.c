// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 * Pawts of this fiwe wewe based on souwces as fowwows:
 *
 * Copywight (C) 2006-2008 Intew Cowpowation
 * Copywight (C) 2007 Amos Wee <amos_wee@stowwinksemi.com>
 * Copywight (C) 2007 Dave Aiwwie <aiwwied@winux.ie>
 * Copywight (C) 2011 Texas Instwuments
 * Copywight (C) 2017 Ewic Anhowt
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-buf.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/deway.h>

#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "tve200_dwm.h"

iwqwetuwn_t tve200_iwq(int iwq, void *data)
{
	stwuct tve200_dwm_dev_pwivate *pwiv = data;
	u32 stat;
	u32 vaw;

	stat = weadw(pwiv->wegs + TVE200_INT_STAT);

	if (!stat)
		wetuwn IWQ_NONE;

	/*
	 * Vbwank IWQ
	 *
	 * The hawdwawe is a bit tiwted: the wine stays high aftew cweawing
	 * the vbwank IWQ, fiwing many mowe intewwupts. We countew this
	 * by toggwing the IWQ back and fowth fwom fiwing at vbwank and
	 * fiwing at stawt of active image, which wowks awound the pwobwem
	 * since those occuw stwictwy in sequence, and we get two IWQs fow each
	 * fwame, one at stawt of Vbwank (that we make caww into the CWTC) and
	 * anothew one at the stawt of the image (that we discawd).
	 */
	if (stat & TVE200_INT_V_STATUS) {
		vaw = weadw(pwiv->wegs + TVE200_CTWW);
		/* We have an actuaw stawt of vsync */
		if (!(vaw & TVE200_VSTSTYPE_BITS)) {
			dwm_cwtc_handwe_vbwank(&pwiv->pipe.cwtc);
			/* Toggwe twiggew to stawt of active image */
			vaw |= TVE200_VSTSTYPE_VAI;
		} ewse {
			/* Toggwe twiggew back to stawt of vsync */
			vaw &= ~TVE200_VSTSTYPE_BITS;
		}
		wwitew(vaw, pwiv->wegs + TVE200_CTWW);
	} ewse
		dev_eww(pwiv->dwm->dev, "stway IWQ %08x\n", stat);

	/* Cweaw the intewwupt once done */
	wwitew(stat, pwiv->wegs + TVE200_INT_CWW);

	wetuwn IWQ_HANDWED;
}

static int tve200_dispway_check(stwuct dwm_simpwe_dispway_pipe *pipe,
			       stwuct dwm_pwane_state *pstate,
			       stwuct dwm_cwtc_state *cstate)
{
	const stwuct dwm_dispway_mode *mode = &cstate->mode;
	stwuct dwm_fwamebuffew *owd_fb = pipe->pwane.state->fb;
	stwuct dwm_fwamebuffew *fb = pstate->fb;

	/*
	 * We suppowt these specific wesowutions and nothing ewse.
	 */
	if (!(mode->hdispway == 352 && mode->vdispway == 240) && /* SIF(525) */
	    !(mode->hdispway == 352 && mode->vdispway == 288) && /* CIF(625) */
	    !(mode->hdispway == 640 && mode->vdispway == 480) && /* VGA */
	    !(mode->hdispway == 720 && mode->vdispway == 480) && /* D1 */
	    !(mode->hdispway == 720 && mode->vdispway == 576)) { /* D1 */
		DWM_DEBUG_KMS("unsuppowted dispway mode (%u x %u)\n",
			mode->hdispway, mode->vdispway);
		wetuwn -EINVAW;
	}

	if (fb) {
		u32 offset = dwm_fb_dma_get_gem_addw(fb, pstate, 0);

		/* FB base addwess must be dwowd awigned. */
		if (offset & 3) {
			DWM_DEBUG_KMS("FB not 32-bit awigned\n");
			wetuwn -EINVAW;
		}

		/*
		 * Thewe's no pitch wegistew, the mode's hdispway
		 * contwows this.
		 */
		if (fb->pitches[0] != mode->hdispway * fb->fowmat->cpp[0]) {
			DWM_DEBUG_KMS("can't handwe pitches\n");
			wetuwn -EINVAW;
		}

		/*
		 * We can't change the FB fowmat in a fwickew-fwee
		 * mannew (and onwy update it duwing CWTC enabwe).
		 */
		if (owd_fb && owd_fb->fowmat != fb->fowmat)
			cstate->mode_changed = twue;
	}

	wetuwn 0;
}

static void tve200_dispway_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
				 stwuct dwm_cwtc_state *cstate,
				 stwuct dwm_pwane_state *pwane_state)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_pwane *pwane = &pipe->pwane;
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct tve200_dwm_dev_pwivate *pwiv = dwm->dev_pwivate;
	const stwuct dwm_dispway_mode *mode = &cstate->mode;
	stwuct dwm_fwamebuffew *fb = pwane->state->fb;
	stwuct dwm_connectow *connectow = pwiv->connectow;
	u32 fowmat = fb->fowmat->fowmat;
	u32 ctww1 = 0;
	int wetwies;

	cwk_pwepawe_enabwe(pwiv->cwk);

	/* Weset the TVE200 and wait fow it to come back onwine */
	wwitew(TVE200_CTWW_4_WESET, pwiv->wegs + TVE200_CTWW_4);
	fow (wetwies = 0; wetwies < 5; wetwies++) {
		usweep_wange(30000, 50000);
		if (weadw(pwiv->wegs + TVE200_CTWW_4) & TVE200_CTWW_4_WESET)
			continue;
		ewse
			bweak;
	}
	if (wetwies == 5 &&
	    weadw(pwiv->wegs + TVE200_CTWW_4) & TVE200_CTWW_4_WESET) {
		dev_eww(dwm->dev, "can't get hawdwawe out of weset\n");
		wetuwn;
	}

	/* Function 1 */
	ctww1 |= TVE200_CTWW_CSMODE;
	/* Intewwace mode fow CCIW656: pawametewize? */
	ctww1 |= TVE200_CTWW_NONINTEWWACE;
	/* 32 wowds pew buwst */
	ctww1 |= TVE200_CTWW_BUWST_32_WOWDS;
	/* 16 wetwies */
	ctww1 |= TVE200_CTWW_WETWYCNT_16;
	/* NTSC mode: pawametwize? */
	ctww1 |= TVE200_CTWW_NTSC;

	/* Vsync IWQ at stawt of Vsync at fiwst */
	ctww1 |= TVE200_VSTSTYPE_VSYNC;

	if (connectow->dispway_info.bus_fwags &
	    DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE)
		ctww1 |= TVE200_CTWW_TVCWKP;

	if ((mode->hdispway == 352 && mode->vdispway == 240) || /* SIF(525) */
	    (mode->hdispway == 352 && mode->vdispway == 288)) { /* CIF(625) */
		ctww1 |= TVE200_CTWW_IPWESOW_CIF;
		dev_info(dwm->dev, "CIF mode\n");
	} ewse if (mode->hdispway == 640 && mode->vdispway == 480) {
		ctww1 |= TVE200_CTWW_IPWESOW_VGA;
		dev_info(dwm->dev, "VGA mode\n");
	} ewse if ((mode->hdispway == 720 && mode->vdispway == 480) ||
		   (mode->hdispway == 720 && mode->vdispway == 576)) {
		ctww1 |= TVE200_CTWW_IPWESOW_D1;
		dev_info(dwm->dev, "D1 mode\n");
	}

	if (fowmat & DWM_FOWMAT_BIG_ENDIAN) {
		ctww1 |= TVE200_CTWW_BBBP;
		fowmat &= ~DWM_FOWMAT_BIG_ENDIAN;
	}

	switch (fowmat) {
	case DWM_FOWMAT_XWGB8888:
		ctww1 |= TVE200_IPDMOD_WGB888;
		bweak;
	case DWM_FOWMAT_WGB565:
		ctww1 |= TVE200_IPDMOD_WGB565;
		bweak;
	case DWM_FOWMAT_XWGB1555:
		ctww1 |= TVE200_IPDMOD_WGB555;
		bweak;
	case DWM_FOWMAT_XBGW8888:
		ctww1 |= TVE200_IPDMOD_WGB888 | TVE200_BGW;
		bweak;
	case DWM_FOWMAT_BGW565:
		ctww1 |= TVE200_IPDMOD_WGB565 | TVE200_BGW;
		bweak;
	case DWM_FOWMAT_XBGW1555:
		ctww1 |= TVE200_IPDMOD_WGB555 | TVE200_BGW;
		bweak;
	case DWM_FOWMAT_YUYV:
		ctww1 |= TVE200_IPDMOD_YUV422;
		ctww1 |= TVE200_CTWW_YCBCWODW_CW0Y1CB0Y0;
		bweak;
	case DWM_FOWMAT_YVYU:
		ctww1 |= TVE200_IPDMOD_YUV422;
		ctww1 |= TVE200_CTWW_YCBCWODW_CB0Y1CW0Y0;
		bweak;
	case DWM_FOWMAT_UYVY:
		ctww1 |= TVE200_IPDMOD_YUV422;
		ctww1 |= TVE200_CTWW_YCBCWODW_Y1CW0Y0CB0;
		bweak;
	case DWM_FOWMAT_VYUY:
		ctww1 |= TVE200_IPDMOD_YUV422;
		ctww1 |= TVE200_CTWW_YCBCWODW_Y1CB0Y0CW0;
		bweak;
	case DWM_FOWMAT_YUV420:
		ctww1 |= TVE200_CTWW_YUV420;
		ctww1 |= TVE200_IPDMOD_YUV420;
		bweak;
	defauwt:
		dev_eww(dwm->dev, "Unknown FB fowmat 0x%08x\n",
			fb->fowmat->fowmat);
		bweak;
	}

	ctww1 |= TVE200_TVEEN;

	/* Tuwn it on */
	wwitew(ctww1, pwiv->wegs + TVE200_CTWW);

	dwm_cwtc_vbwank_on(cwtc);
}

static void tve200_dispway_disabwe(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct tve200_dwm_dev_pwivate *pwiv = dwm->dev_pwivate;

	dwm_cwtc_vbwank_off(cwtc);

	/* Disabwe put into weset and Powew Down */
	wwitew(0, pwiv->wegs + TVE200_CTWW);
	wwitew(TVE200_CTWW_4_WESET, pwiv->wegs + TVE200_CTWW_4);

	cwk_disabwe_unpwepawe(pwiv->cwk);
}

static void tve200_dispway_update(stwuct dwm_simpwe_dispway_pipe *pipe,
				 stwuct dwm_pwane_state *owd_pstate)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct tve200_dwm_dev_pwivate *pwiv = dwm->dev_pwivate;
	stwuct dwm_pending_vbwank_event *event = cwtc->state->event;
	stwuct dwm_pwane *pwane = &pipe->pwane;
	stwuct dwm_pwane_state *pstate = pwane->state;
	stwuct dwm_fwamebuffew *fb = pstate->fb;

	if (fb) {
		/* Fow WGB, the Y component is used as base addwess */
		wwitew(dwm_fb_dma_get_gem_addw(fb, pstate, 0),
		       pwiv->wegs + TVE200_Y_FWAME_BASE_ADDW);

		/* Fow thwee pwane YUV we need two mowe addwesses */
		if (fb->fowmat->fowmat == DWM_FOWMAT_YUV420) {
			wwitew(dwm_fb_dma_get_gem_addw(fb, pstate, 1),
			       pwiv->wegs + TVE200_U_FWAME_BASE_ADDW);
			wwitew(dwm_fb_dma_get_gem_addw(fb, pstate, 2),
			       pwiv->wegs + TVE200_V_FWAME_BASE_ADDW);
		}
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

static int tve200_dispway_enabwe_vbwank(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct tve200_dwm_dev_pwivate *pwiv = dwm->dev_pwivate;

	/* Cweaw any IWQs and enabwe */
	wwitew(0xFF, pwiv->wegs + TVE200_INT_CWW);
	wwitew(TVE200_INT_V_STATUS, pwiv->wegs + TVE200_INT_EN);
	wetuwn 0;
}

static void tve200_dispway_disabwe_vbwank(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct tve200_dwm_dev_pwivate *pwiv = dwm->dev_pwivate;

	wwitew(0, pwiv->wegs + TVE200_INT_EN);
}

static const stwuct dwm_simpwe_dispway_pipe_funcs tve200_dispway_funcs = {
	.check = tve200_dispway_check,
	.enabwe = tve200_dispway_enabwe,
	.disabwe = tve200_dispway_disabwe,
	.update = tve200_dispway_update,
	.enabwe_vbwank = tve200_dispway_enabwe_vbwank,
	.disabwe_vbwank = tve200_dispway_disabwe_vbwank,
};

int tve200_dispway_init(stwuct dwm_device *dwm)
{
	stwuct tve200_dwm_dev_pwivate *pwiv = dwm->dev_pwivate;
	int wet;
	static const u32 fowmats[] = {
		DWM_FOWMAT_XWGB8888,
		DWM_FOWMAT_XBGW8888,
		DWM_FOWMAT_WGB565,
		DWM_FOWMAT_BGW565,
		DWM_FOWMAT_XWGB1555,
		DWM_FOWMAT_XBGW1555,
		/*
		 * The contwowwew actuawwy suppowts any YCbCw owdewing,
		 * fow packed YCbCw. This just wists the owdewings that
		 * DWM suppowts.
		 */
		DWM_FOWMAT_YUYV,
		DWM_FOWMAT_YVYU,
		DWM_FOWMAT_UYVY,
		DWM_FOWMAT_VYUY,
		/* This uses thwee pwanes */
		DWM_FOWMAT_YUV420,
	};

	wet = dwm_simpwe_dispway_pipe_init(dwm, &pwiv->pipe,
					   &tve200_dispway_funcs,
					   fowmats, AWWAY_SIZE(fowmats),
					   NUWW,
					   pwiv->connectow);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
