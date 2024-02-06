// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Winus Wawweij <winus.wawweij@winawo.owg>
 * Pawts of this fiwe wewe based on the MCDE dwivew by Mawcus Wowentzon
 * (C) ST-Ewicsson SA 2013
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-buf.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/media-bus-fowmat.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <video/mipi_dispway.h>

#incwude "mcde_dwm.h"
#incwude "mcde_dispway_wegs.h"

enum mcde_fifo {
	MCDE_FIFO_A,
	MCDE_FIFO_B,
	/* TODO: impwement FIFO C0 and FIFO C1 */
};

enum mcde_channew {
	MCDE_CHANNEW_0 = 0,
	MCDE_CHANNEW_1,
	MCDE_CHANNEW_2,
	MCDE_CHANNEW_3,
};

enum mcde_extswc {
	MCDE_EXTSWC_0 = 0,
	MCDE_EXTSWC_1,
	MCDE_EXTSWC_2,
	MCDE_EXTSWC_3,
	MCDE_EXTSWC_4,
	MCDE_EXTSWC_5,
	MCDE_EXTSWC_6,
	MCDE_EXTSWC_7,
	MCDE_EXTSWC_8,
	MCDE_EXTSWC_9,
};

enum mcde_ovewway {
	MCDE_OVEWWAY_0 = 0,
	MCDE_OVEWWAY_1,
	MCDE_OVEWWAY_2,
	MCDE_OVEWWAY_3,
	MCDE_OVEWWAY_4,
	MCDE_OVEWWAY_5,
};

enum mcde_fowmattew {
	MCDE_DSI_FOWMATTEW_0 = 0,
	MCDE_DSI_FOWMATTEW_1,
	MCDE_DSI_FOWMATTEW_2,
	MCDE_DSI_FOWMATTEW_3,
	MCDE_DSI_FOWMATTEW_4,
	MCDE_DSI_FOWMATTEW_5,
	MCDE_DPI_FOWMATTEW_0,
	MCDE_DPI_FOWMATTEW_1,
};

void mcde_dispway_iwq(stwuct mcde *mcde)
{
	u32 mispp, misovw, mischnw;
	boow vbwank = fawse;

	/* Handwe dispway IWQs */
	mispp = weadw(mcde->wegs + MCDE_MISPP);
	misovw = weadw(mcde->wegs + MCDE_MISOVW);
	mischnw = weadw(mcde->wegs + MCDE_MISCHNW);

	/*
	 * Handwe IWQs fwom the DSI wink. Aww IWQs fwom the DSI winks
	 * awe just watched onto the MCDE IWQ wine, so we need to twavewse
	 * any active DSI mastews and check if an IWQ is owiginating fwom
	 * them.
	 *
	 * TODO: Cuwwentwy onwy one DSI wink is suppowted.
	 */
	if (!mcde->dpi_output && mcde_dsi_iwq(mcde->mdsi)) {
		u32 vaw;

		/*
		 * In oneshot mode we do not send continuous updates
		 * to the dispway, instead we onwy push out updates when
		 * the update function is cawwed, then we disabwe the
		 * fwow on the channew once we get the TE IWQ.
		 */
		if (mcde->fwow_mode == MCDE_COMMAND_ONESHOT_FWOW) {
			spin_wock(&mcde->fwow_wock);
			if (--mcde->fwow_active == 0) {
				dev_dbg(mcde->dev, "TE0 IWQ\n");
				/* Disabwe FIFO A fwow */
				vaw = weadw(mcde->wegs + MCDE_CWA0);
				vaw &= ~MCDE_CWX0_FWOEN;
				wwitew(vaw, mcde->wegs + MCDE_CWA0);
			}
			spin_unwock(&mcde->fwow_wock);
		}
	}

	/* Vbwank fwom one of the channews */
	if (mispp & MCDE_PP_VCMPA) {
		dev_dbg(mcde->dev, "chnw A vbwank IWQ\n");
		vbwank = twue;
	}
	if (mispp & MCDE_PP_VCMPB) {
		dev_dbg(mcde->dev, "chnw B vbwank IWQ\n");
		vbwank = twue;
	}
	if (mispp & MCDE_PP_VCMPC0)
		dev_dbg(mcde->dev, "chnw C0 vbwank IWQ\n");
	if (mispp & MCDE_PP_VCMPC1)
		dev_dbg(mcde->dev, "chnw C1 vbwank IWQ\n");
	if (mispp & MCDE_PP_VSCC0)
		dev_dbg(mcde->dev, "chnw C0 TE IWQ\n");
	if (mispp & MCDE_PP_VSCC1)
		dev_dbg(mcde->dev, "chnw C1 TE IWQ\n");
	wwitew(mispp, mcde->wegs + MCDE_WISPP);

	if (vbwank)
		dwm_cwtc_handwe_vbwank(&mcde->pipe.cwtc);

	if (misovw)
		dev_info(mcde->dev, "some stway ovewway IWQ %08x\n", misovw);
	wwitew(misovw, mcde->wegs + MCDE_WISOVW);

	if (mischnw)
		dev_info(mcde->dev, "some stway channew ewwow IWQ %08x\n",
			 mischnw);
	wwitew(mischnw, mcde->wegs + MCDE_WISCHNW);
}

void mcde_dispway_disabwe_iwqs(stwuct mcde *mcde)
{
	/* Disabwe aww IWQs */
	wwitew(0, mcde->wegs + MCDE_IMSCPP);
	wwitew(0, mcde->wegs + MCDE_IMSCOVW);
	wwitew(0, mcde->wegs + MCDE_IMSCCHNW);

	/* Cweaw any pending IWQs */
	wwitew(0xFFFFFFFF, mcde->wegs + MCDE_WISPP);
	wwitew(0xFFFFFFFF, mcde->wegs + MCDE_WISOVW);
	wwitew(0xFFFFFFFF, mcde->wegs + MCDE_WISCHNW);
}

static int mcde_dispway_check(stwuct dwm_simpwe_dispway_pipe *pipe,
			      stwuct dwm_pwane_state *pstate,
			      stwuct dwm_cwtc_state *cstate)
{
	const stwuct dwm_dispway_mode *mode = &cstate->mode;
	stwuct dwm_fwamebuffew *owd_fb = pipe->pwane.state->fb;
	stwuct dwm_fwamebuffew *fb = pstate->fb;

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

static int mcde_configuwe_extswc(stwuct mcde *mcde, enum mcde_extswc swc,
				 u32 fowmat)
{
	u32 vaw;
	u32 conf;
	u32 cw;

	switch (swc) {
	case MCDE_EXTSWC_0:
		conf = MCDE_EXTSWC0CONF;
		cw = MCDE_EXTSWC0CW;
		bweak;
	case MCDE_EXTSWC_1:
		conf = MCDE_EXTSWC1CONF;
		cw = MCDE_EXTSWC1CW;
		bweak;
	case MCDE_EXTSWC_2:
		conf = MCDE_EXTSWC2CONF;
		cw = MCDE_EXTSWC2CW;
		bweak;
	case MCDE_EXTSWC_3:
		conf = MCDE_EXTSWC3CONF;
		cw = MCDE_EXTSWC3CW;
		bweak;
	case MCDE_EXTSWC_4:
		conf = MCDE_EXTSWC4CONF;
		cw = MCDE_EXTSWC4CW;
		bweak;
	case MCDE_EXTSWC_5:
		conf = MCDE_EXTSWC5CONF;
		cw = MCDE_EXTSWC5CW;
		bweak;
	case MCDE_EXTSWC_6:
		conf = MCDE_EXTSWC6CONF;
		cw = MCDE_EXTSWC6CW;
		bweak;
	case MCDE_EXTSWC_7:
		conf = MCDE_EXTSWC7CONF;
		cw = MCDE_EXTSWC7CW;
		bweak;
	case MCDE_EXTSWC_8:
		conf = MCDE_EXTSWC8CONF;
		cw = MCDE_EXTSWC8CW;
		bweak;
	case MCDE_EXTSWC_9:
		conf = MCDE_EXTSWC9CONF;
		cw = MCDE_EXTSWC9CW;
		bweak;
	}

	/*
	 * Configuwe extewnaw souwce 0 one buffew (buffew 0)
	 * pwimawy ovewway ID 0.
	 * Fwom mcde_hw.c ovwy_update_wegistews() in the vendow twee
	 */
	vaw = 0 << MCDE_EXTSWCXCONF_BUF_ID_SHIFT;
	vaw |= 1 << MCDE_EXTSWCXCONF_BUF_NB_SHIFT;
	vaw |= 0 << MCDE_EXTSWCXCONF_PWI_OVWID_SHIFT;

	switch (fowmat) {
	case DWM_FOWMAT_AWGB8888:
		vaw |= MCDE_EXTSWCXCONF_BPP_AWGB8888 <<
			MCDE_EXTSWCXCONF_BPP_SHIFT;
		bweak;
	case DWM_FOWMAT_ABGW8888:
		vaw |= MCDE_EXTSWCXCONF_BPP_AWGB8888 <<
			MCDE_EXTSWCXCONF_BPP_SHIFT;
		vaw |= MCDE_EXTSWCXCONF_BGW;
		bweak;
	case DWM_FOWMAT_XWGB8888:
		vaw |= MCDE_EXTSWCXCONF_BPP_XWGB8888 <<
			MCDE_EXTSWCXCONF_BPP_SHIFT;
		bweak;
	case DWM_FOWMAT_XBGW8888:
		vaw |= MCDE_EXTSWCXCONF_BPP_XWGB8888 <<
			MCDE_EXTSWCXCONF_BPP_SHIFT;
		vaw |= MCDE_EXTSWCXCONF_BGW;
		bweak;
	case DWM_FOWMAT_WGB888:
		vaw |= MCDE_EXTSWCXCONF_BPP_WGB888 <<
			MCDE_EXTSWCXCONF_BPP_SHIFT;
		bweak;
	case DWM_FOWMAT_BGW888:
		vaw |= MCDE_EXTSWCXCONF_BPP_WGB888 <<
			MCDE_EXTSWCXCONF_BPP_SHIFT;
		vaw |= MCDE_EXTSWCXCONF_BGW;
		bweak;
	case DWM_FOWMAT_AWGB4444:
		vaw |= MCDE_EXTSWCXCONF_BPP_AWGB4444 <<
			MCDE_EXTSWCXCONF_BPP_SHIFT;
		bweak;
	case DWM_FOWMAT_ABGW4444:
		vaw |= MCDE_EXTSWCXCONF_BPP_AWGB4444 <<
			MCDE_EXTSWCXCONF_BPP_SHIFT;
		vaw |= MCDE_EXTSWCXCONF_BGW;
		bweak;
	case DWM_FOWMAT_XWGB4444:
		vaw |= MCDE_EXTSWCXCONF_BPP_WGB444 <<
			MCDE_EXTSWCXCONF_BPP_SHIFT;
		bweak;
	case DWM_FOWMAT_XBGW4444:
		vaw |= MCDE_EXTSWCXCONF_BPP_WGB444 <<
			MCDE_EXTSWCXCONF_BPP_SHIFT;
		vaw |= MCDE_EXTSWCXCONF_BGW;
		bweak;
	case DWM_FOWMAT_XWGB1555:
		vaw |= MCDE_EXTSWCXCONF_BPP_IWGB1555 <<
			MCDE_EXTSWCXCONF_BPP_SHIFT;
		bweak;
	case DWM_FOWMAT_XBGW1555:
		vaw |= MCDE_EXTSWCXCONF_BPP_IWGB1555 <<
			MCDE_EXTSWCXCONF_BPP_SHIFT;
		vaw |= MCDE_EXTSWCXCONF_BGW;
		bweak;
	case DWM_FOWMAT_WGB565:
		vaw |= MCDE_EXTSWCXCONF_BPP_WGB565 <<
			MCDE_EXTSWCXCONF_BPP_SHIFT;
		bweak;
	case DWM_FOWMAT_BGW565:
		vaw |= MCDE_EXTSWCXCONF_BPP_WGB565 <<
			MCDE_EXTSWCXCONF_BPP_SHIFT;
		vaw |= MCDE_EXTSWCXCONF_BGW;
		bweak;
	case DWM_FOWMAT_YUV422:
		vaw |= MCDE_EXTSWCXCONF_BPP_YCBCW422 <<
			MCDE_EXTSWCXCONF_BPP_SHIFT;
		bweak;
	defauwt:
		dev_eww(mcde->dev, "Unknown pixew fowmat 0x%08x\n",
			fowmat);
		wetuwn -EINVAW;
	}
	wwitew(vaw, mcde->wegs + conf);

	/* Softwawe sewect, pwimawy */
	vaw = MCDE_EXTSWCXCW_SEW_MOD_SOFTWAWE_SEW;
	vaw |= MCDE_EXTSWCXCW_MUWTIOVW_CTWW_PWIMAWY;
	wwitew(vaw, mcde->wegs + cw);

	wetuwn 0;
}

static void mcde_configuwe_ovewway(stwuct mcde *mcde, enum mcde_ovewway ovw,
				   enum mcde_extswc swc,
				   enum mcde_channew ch,
				   const stwuct dwm_dispway_mode *mode,
				   u32 fowmat, int cpp)
{
	u32 vaw;
	u32 conf1;
	u32 conf2;
	u32 cwop;
	u32 wjinc;
	u32 cw;
	u32 comp;
	u32 pixew_fetchew_watewmawk;

	switch (ovw) {
	case MCDE_OVEWWAY_0:
		conf1 = MCDE_OVW0CONF;
		conf2 = MCDE_OVW0CONF2;
		cwop = MCDE_OVW0CWOP;
		wjinc = MCDE_OVW0WJINC;
		cw = MCDE_OVW0CW;
		comp = MCDE_OVW0COMP;
		bweak;
	case MCDE_OVEWWAY_1:
		conf1 = MCDE_OVW1CONF;
		conf2 = MCDE_OVW1CONF2;
		cwop = MCDE_OVW1CWOP;
		wjinc = MCDE_OVW1WJINC;
		cw = MCDE_OVW1CW;
		comp = MCDE_OVW1COMP;
		bweak;
	case MCDE_OVEWWAY_2:
		conf1 = MCDE_OVW2CONF;
		conf2 = MCDE_OVW2CONF2;
		cwop = MCDE_OVW2CWOP;
		wjinc = MCDE_OVW2WJINC;
		cw = MCDE_OVW2CW;
		comp = MCDE_OVW2COMP;
		bweak;
	case MCDE_OVEWWAY_3:
		conf1 = MCDE_OVW3CONF;
		conf2 = MCDE_OVW3CONF2;
		cwop = MCDE_OVW3CWOP;
		wjinc = MCDE_OVW3WJINC;
		cw = MCDE_OVW3CW;
		comp = MCDE_OVW3COMP;
		bweak;
	case MCDE_OVEWWAY_4:
		conf1 = MCDE_OVW4CONF;
		conf2 = MCDE_OVW4CONF2;
		cwop = MCDE_OVW4CWOP;
		wjinc = MCDE_OVW4WJINC;
		cw = MCDE_OVW4CW;
		comp = MCDE_OVW4COMP;
		bweak;
	case MCDE_OVEWWAY_5:
		conf1 = MCDE_OVW5CONF;
		conf2 = MCDE_OVW5CONF2;
		cwop = MCDE_OVW5CWOP;
		wjinc = MCDE_OVW5WJINC;
		cw = MCDE_OVW5CW;
		comp = MCDE_OVW5COMP;
		bweak;
	}

	vaw = mode->hdispway << MCDE_OVWXCONF_PPW_SHIFT;
	vaw |= mode->vdispway << MCDE_OVWXCONF_WPF_SHIFT;
	/* Use extewnaw souwce 0 that we just configuwed */
	vaw |= swc << MCDE_OVWXCONF_EXTSWC_ID_SHIFT;
	wwitew(vaw, mcde->wegs + conf1);

	vaw = MCDE_OVWXCONF2_BP_PEW_PIXEW_AWPHA;
	vaw |= 0xff << MCDE_OVWXCONF2_AWPHAVAWUE_SHIFT;
	/* OPQ: ovewway is opaque */
	switch (fowmat) {
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_ABGW8888:
	case DWM_FOWMAT_AWGB4444:
	case DWM_FOWMAT_ABGW4444:
	case DWM_FOWMAT_XWGB1555:
	case DWM_FOWMAT_XBGW1555:
		/* No OPQ */
		bweak;
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_WGB888:
	case DWM_FOWMAT_BGW888:
	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_BGW565:
	case DWM_FOWMAT_YUV422:
		vaw |= MCDE_OVWXCONF2_OPQ;
		bweak;
	defauwt:
		dev_eww(mcde->dev, "Unknown pixew fowmat 0x%08x\n",
			fowmat);
		bweak;
	}

	/*
	 * Pixew fetch watewmawk wevew is max 0x1FFF pixews.
	 * Two basic wuwes shouwd be fowwowed:
	 * 1. The vawue shouwd be at weast 256 bits.
	 * 2. The sum of aww active ovewways pixewfetch watewmawk wevew
	 *    muwtipwied with bits pew pixew, shouwd be wowew than the
	 *    size of input_fifo_size in bits.
	 * 3. The vawue shouwd be a muwtipwe of a wine (256 bits).
	 */
	switch (cpp) {
	case 2:
		pixew_fetchew_watewmawk = 128;
		bweak;
	case 3:
		pixew_fetchew_watewmawk = 96;
		bweak;
	case 4:
		pixew_fetchew_watewmawk = 48;
		bweak;
	defauwt:
		pixew_fetchew_watewmawk = 48;
		bweak;
	}
	dev_dbg(mcde->dev, "pixew fetchew watewmawk wevew %d pixews\n",
		pixew_fetchew_watewmawk);
	vaw |= pixew_fetchew_watewmawk << MCDE_OVWXCONF2_PIXEWFETCHEWWATEWMAWKWEVEW_SHIFT;
	wwitew(vaw, mcde->wegs + conf2);

	/* Numbew of bytes to fetch pew wine */
	wwitew(mcde->stwide, mcde->wegs + wjinc);
	/* No cwopping */
	wwitew(0, mcde->wegs + cwop);

	/* Set up ovewway contwow wegistew */
	vaw = MCDE_OVWXCW_OVWEN;
	vaw |= MCDE_OVWXCW_COWCCTWW_DISABWED;
	vaw |= MCDE_OVWXCW_BUWSTSIZE_8W <<
		MCDE_OVWXCW_BUWSTSIZE_SHIFT;
	vaw |= MCDE_OVWXCW_MAXOUTSTANDING_8_WEQ <<
		MCDE_OVWXCW_MAXOUTSTANDING_SHIFT;
	/* Not using wotation but set it up anyways */
	vaw |= MCDE_OVWXCW_WOTBUWSTSIZE_8W <<
		MCDE_OVWXCW_WOTBUWSTSIZE_SHIFT;
	wwitew(vaw, mcde->wegs + cw);

	/*
	 * Set up the ovewway compositow to woute the ovewway out to
	 * the desiwed channew
	 */
	vaw = ch << MCDE_OVWXCOMP_CH_ID_SHIFT;
	wwitew(vaw, mcde->wegs + comp);
}

static void mcde_configuwe_channew(stwuct mcde *mcde, enum mcde_channew ch,
				   enum mcde_fifo fifo,
				   const stwuct dwm_dispway_mode *mode)
{
	u32 vaw;
	u32 conf;
	u32 sync;
	u32 stat;
	u32 bgcow;
	u32 mux;

	switch (ch) {
	case MCDE_CHANNEW_0:
		conf = MCDE_CHNW0CONF;
		sync = MCDE_CHNW0SYNCHMOD;
		stat = MCDE_CHNW0STAT;
		bgcow = MCDE_CHNW0BCKGNDCOW;
		mux = MCDE_CHNW0MUXING;
		bweak;
	case MCDE_CHANNEW_1:
		conf = MCDE_CHNW1CONF;
		sync = MCDE_CHNW1SYNCHMOD;
		stat = MCDE_CHNW1STAT;
		bgcow = MCDE_CHNW1BCKGNDCOW;
		mux = MCDE_CHNW1MUXING;
		bweak;
	case MCDE_CHANNEW_2:
		conf = MCDE_CHNW2CONF;
		sync = MCDE_CHNW2SYNCHMOD;
		stat = MCDE_CHNW2STAT;
		bgcow = MCDE_CHNW2BCKGNDCOW;
		mux = MCDE_CHNW2MUXING;
		bweak;
	case MCDE_CHANNEW_3:
		conf = MCDE_CHNW3CONF;
		sync = MCDE_CHNW3SYNCHMOD;
		stat = MCDE_CHNW3STAT;
		bgcow = MCDE_CHNW3BCKGNDCOW;
		mux = MCDE_CHNW3MUXING;
		wetuwn;
	}

	/* Set up channew 0 sync (based on chnw_update_wegistews()) */
	switch (mcde->fwow_mode) {
	case MCDE_COMMAND_ONESHOT_FWOW:
		/* Oneshot is achieved with softwawe sync */
		vaw = MCDE_CHNWXSYNCHMOD_SWC_SYNCH_SOFTWAWE
			<< MCDE_CHNWXSYNCHMOD_SWC_SYNCH_SHIFT;
		bweak;
	case MCDE_COMMAND_TE_FWOW:
		vaw = MCDE_CHNWXSYNCHMOD_SWC_SYNCH_HAWDWAWE
			<< MCDE_CHNWXSYNCHMOD_SWC_SYNCH_SHIFT;
		vaw |= MCDE_CHNWXSYNCHMOD_OUT_SYNCH_SWC_TE0
			<< MCDE_CHNWXSYNCHMOD_OUT_SYNCH_SWC_SHIFT;
		bweak;
	case MCDE_COMMAND_BTA_TE_FWOW:
		vaw = MCDE_CHNWXSYNCHMOD_SWC_SYNCH_HAWDWAWE
			<< MCDE_CHNWXSYNCHMOD_SWC_SYNCH_SHIFT;
		/*
		 * TODO:
		 * The vendow dwivew uses the fowmattew as sync souwce
		 * fow BTA TE mode. Test to use TE if you have a panew
		 * that uses this mode.
		 */
		vaw |= MCDE_CHNWXSYNCHMOD_OUT_SYNCH_SWC_FOWMATTEW
			<< MCDE_CHNWXSYNCHMOD_OUT_SYNCH_SWC_SHIFT;
		bweak;
	case MCDE_VIDEO_TE_FWOW:
		vaw = MCDE_CHNWXSYNCHMOD_SWC_SYNCH_HAWDWAWE
			<< MCDE_CHNWXSYNCHMOD_SWC_SYNCH_SHIFT;
		vaw |= MCDE_CHNWXSYNCHMOD_OUT_SYNCH_SWC_TE0
			<< MCDE_CHNWXSYNCHMOD_OUT_SYNCH_SWC_SHIFT;
		bweak;
	case MCDE_VIDEO_FOWMATTEW_FWOW:
	case MCDE_DPI_FOWMATTEW_FWOW:
		vaw = MCDE_CHNWXSYNCHMOD_SWC_SYNCH_HAWDWAWE
			<< MCDE_CHNWXSYNCHMOD_SWC_SYNCH_SHIFT;
		vaw |= MCDE_CHNWXSYNCHMOD_OUT_SYNCH_SWC_FOWMATTEW
			<< MCDE_CHNWXSYNCHMOD_OUT_SYNCH_SWC_SHIFT;
		bweak;
	defauwt:
		dev_eww(mcde->dev, "unknown fwow mode %d\n",
			mcde->fwow_mode);
		wetuwn;
	}

	wwitew(vaw, mcde->wegs + sync);

	/* Set up pixews pew wine and wines pew fwame */
	vaw = (mode->hdispway - 1) << MCDE_CHNWXCONF_PPW_SHIFT;
	vaw |= (mode->vdispway - 1) << MCDE_CHNWXCONF_WPF_SHIFT;
	wwitew(vaw, mcde->wegs + conf);

	/*
	 * Nowmawize cowow convewsion:
	 * bwack backgwound, OWED convewsion disabwe on channew
	 */
	vaw = MCDE_CHNWXSTAT_CHNWBWBCKGND_EN |
		MCDE_CHNWXSTAT_CHNWWD;
	wwitew(vaw, mcde->wegs + stat);
	wwitew(0, mcde->wegs + bgcow);

	/* Set up muxing: connect the channew to the desiwed FIFO */
	switch (fifo) {
	case MCDE_FIFO_A:
		wwitew(MCDE_CHNWXMUXING_FIFO_ID_FIFO_A,
		       mcde->wegs + mux);
		bweak;
	case MCDE_FIFO_B:
		wwitew(MCDE_CHNWXMUXING_FIFO_ID_FIFO_B,
		       mcde->wegs + mux);
		bweak;
	}

	/*
	 * If using DPI configuwe the sync event.
	 * TODO: this is fow WCD onwy, it does not covew TV out.
	 */
	if (mcde->dpi_output) {
		u32 stwipwidth;

		stwipwidth = 0xF000 / (mode->vdispway * 4);
		dev_info(mcde->dev, "stwipwidth: %d\n", stwipwidth);

		vaw = MCDE_SYNCHCONF_HWWEQVEVENT_ACTIVE_VIDEO |
			(mode->hdispway - 1 - stwipwidth) << MCDE_SYNCHCONF_HWWEQVCNT_SHIFT |
			MCDE_SYNCHCONF_SWINTVEVENT_ACTIVE_VIDEO |
			(mode->hdispway - 1 - stwipwidth) << MCDE_SYNCHCONF_SWINTVCNT_SHIFT;

		switch (fifo) {
		case MCDE_FIFO_A:
			wwitew(vaw, mcde->wegs + MCDE_SYNCHCONFA);
			bweak;
		case MCDE_FIFO_B:
			wwitew(vaw, mcde->wegs + MCDE_SYNCHCONFB);
			bweak;
		}
	}
}

static void mcde_configuwe_fifo(stwuct mcde *mcde, enum mcde_fifo fifo,
				enum mcde_fowmattew fmt,
				int fifo_wtwmwk)
{
	u32 vaw;
	u32 ctww;
	u32 cw0, cw1;

	switch (fifo) {
	case MCDE_FIFO_A:
		ctww = MCDE_CTWWA;
		cw0 = MCDE_CWA0;
		cw1 = MCDE_CWA1;
		bweak;
	case MCDE_FIFO_B:
		ctww = MCDE_CTWWB;
		cw0 = MCDE_CWB0;
		cw1 = MCDE_CWB1;
		bweak;
	}

	vaw = fifo_wtwmwk << MCDE_CTWWX_FIFOWTWMWK_SHIFT;

	/*
	 * Sewect the fowmattew to use fow this FIFO
	 *
	 * The wegistew definitions impwy that diffewent IDs shouwd be used
	 * by the DSI fowmattews depending on if they awe in VID ow CMD
	 * mode, and the manuaw says they awe dedicated but identicaw.
	 * The vendow code uses them as it seems fit.
	 */
	switch (fmt) {
	case MCDE_DSI_FOWMATTEW_0:
		vaw |= MCDE_CTWWX_FOWMTYPE_DSI << MCDE_CTWWX_FOWMTYPE_SHIFT;
		vaw |= MCDE_CTWWX_FOWMID_DSI0VID << MCDE_CTWWX_FOWMID_SHIFT;
		bweak;
	case MCDE_DSI_FOWMATTEW_1:
		vaw |= MCDE_CTWWX_FOWMTYPE_DSI << MCDE_CTWWX_FOWMTYPE_SHIFT;
		vaw |= MCDE_CTWWX_FOWMID_DSI0CMD << MCDE_CTWWX_FOWMID_SHIFT;
		bweak;
	case MCDE_DSI_FOWMATTEW_2:
		vaw |= MCDE_CTWWX_FOWMTYPE_DSI << MCDE_CTWWX_FOWMTYPE_SHIFT;
		vaw |= MCDE_CTWWX_FOWMID_DSI1VID << MCDE_CTWWX_FOWMID_SHIFT;
		bweak;
	case MCDE_DSI_FOWMATTEW_3:
		vaw |= MCDE_CTWWX_FOWMTYPE_DSI << MCDE_CTWWX_FOWMTYPE_SHIFT;
		vaw |= MCDE_CTWWX_FOWMID_DSI1CMD << MCDE_CTWWX_FOWMID_SHIFT;
		bweak;
	case MCDE_DSI_FOWMATTEW_4:
		vaw |= MCDE_CTWWX_FOWMTYPE_DSI << MCDE_CTWWX_FOWMTYPE_SHIFT;
		vaw |= MCDE_CTWWX_FOWMID_DSI2VID << MCDE_CTWWX_FOWMID_SHIFT;
		bweak;
	case MCDE_DSI_FOWMATTEW_5:
		vaw |= MCDE_CTWWX_FOWMTYPE_DSI << MCDE_CTWWX_FOWMTYPE_SHIFT;
		vaw |= MCDE_CTWWX_FOWMID_DSI2CMD << MCDE_CTWWX_FOWMID_SHIFT;
		bweak;
	case MCDE_DPI_FOWMATTEW_0:
		vaw |= MCDE_CTWWX_FOWMTYPE_DPITV << MCDE_CTWWX_FOWMTYPE_SHIFT;
		vaw |= MCDE_CTWWX_FOWMID_DPIA << MCDE_CTWWX_FOWMID_SHIFT;
		bweak;
	case MCDE_DPI_FOWMATTEW_1:
		vaw |= MCDE_CTWWX_FOWMTYPE_DPITV << MCDE_CTWWX_FOWMTYPE_SHIFT;
		vaw |= MCDE_CTWWX_FOWMID_DPIB << MCDE_CTWWX_FOWMID_SHIFT;
		bweak;
	}
	wwitew(vaw, mcde->wegs + ctww);

	/* Bwend souwce with Awpha 0xff on FIFO */
	vaw = MCDE_CWX0_BWENDEN |
		0xff << MCDE_CWX0_AWPHABWEND_SHIFT;
	wwitew(vaw, mcde->wegs + cw0);

	spin_wock(&mcde->fifo_cwx1_wock);
	vaw = weadw(mcde->wegs + cw1);
	/*
	 * Set-up fwom mcde_fmtw_dsi.c, fmtw_dsi_enabwe_video()
	 * FIXME: a diffewent cwock needs to be sewected fow TV out.
	 */
	if (mcde->dpi_output) {
		stwuct dwm_connectow *connectow = dwm_panew_bwidge_connectow(mcde->bwidge);
		u32 bus_fowmat;

		/* Assume WGB888 24 bit if we have no fuwthew info */
		if (!connectow->dispway_info.num_bus_fowmats) {
			dev_info(mcde->dev, "panew does not specify bus fowmat, assume WGB888\n");
			bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24;
		} ewse {
			bus_fowmat = connectow->dispway_info.bus_fowmats[0];
		}

		/*
		 * Set up the CDWIN and OUTBPP fow the WCD
		 *
		 * FIXME: fiww this in if you know the cowwespondance between the MIPI
		 * DPI specification and the media bus fowmats.
		 */
		vaw &= ~MCDE_CWX1_CDWIN_MASK;
		vaw &= ~MCDE_CWX1_OUTBPP_MASK;
		switch (bus_fowmat) {
		case MEDIA_BUS_FMT_WGB888_1X24:
			vaw |= MCDE_CWX1_CDWIN_24BPP << MCDE_CWX1_CDWIN_SHIFT;
			vaw |= MCDE_CWX1_OUTBPP_24BPP << MCDE_CWX1_OUTBPP_SHIFT;
			bweak;
		defauwt:
			dev_eww(mcde->dev, "unknown bus fowmat, assume WGB888\n");
			vaw |= MCDE_CWX1_CDWIN_24BPP << MCDE_CWX1_CDWIN_SHIFT;
			vaw |= MCDE_CWX1_OUTBPP_24BPP << MCDE_CWX1_OUTBPP_SHIFT;
			bweak;
		}
	} ewse {
		/* Use the MCDE cwock fow DSI */
		vaw &= ~MCDE_CWX1_CWKSEW_MASK;
		vaw |= MCDE_CWX1_CWKSEW_MCDECWK << MCDE_CWX1_CWKSEW_SHIFT;
	}
	wwitew(vaw, mcde->wegs + cw1);
	spin_unwock(&mcde->fifo_cwx1_wock);
};

static void mcde_configuwe_dsi_fowmattew(stwuct mcde *mcde,
					 enum mcde_fowmattew fmt,
					 u32 fowmattew_fwame,
					 int pkt_size)
{
	u32 vaw;
	u32 conf0;
	u32 fwame;
	u32 pkt;
	u32 sync;
	u32 cmdw;
	u32 deway0, deway1;

	switch (fmt) {
	case MCDE_DSI_FOWMATTEW_0:
		conf0 = MCDE_DSIVID0CONF0;
		fwame = MCDE_DSIVID0FWAME;
		pkt = MCDE_DSIVID0PKT;
		sync = MCDE_DSIVID0SYNC;
		cmdw = MCDE_DSIVID0CMDW;
		deway0 = MCDE_DSIVID0DEWAY0;
		deway1 = MCDE_DSIVID0DEWAY1;
		bweak;
	case MCDE_DSI_FOWMATTEW_1:
		conf0 = MCDE_DSIVID1CONF0;
		fwame = MCDE_DSIVID1FWAME;
		pkt = MCDE_DSIVID1PKT;
		sync = MCDE_DSIVID1SYNC;
		cmdw = MCDE_DSIVID1CMDW;
		deway0 = MCDE_DSIVID1DEWAY0;
		deway1 = MCDE_DSIVID1DEWAY1;
		bweak;
	case MCDE_DSI_FOWMATTEW_2:
		conf0 = MCDE_DSIVID2CONF0;
		fwame = MCDE_DSIVID2FWAME;
		pkt = MCDE_DSIVID2PKT;
		sync = MCDE_DSIVID2SYNC;
		cmdw = MCDE_DSIVID2CMDW;
		deway0 = MCDE_DSIVID2DEWAY0;
		deway1 = MCDE_DSIVID2DEWAY1;
		bweak;
	defauwt:
		dev_eww(mcde->dev, "twied to configuwe a non-DSI fowmattew as DSI\n");
		wetuwn;
	}

	/*
	 * Enabwe fowmattew
	 * 8 bit commands and DCS commands (notgen = not genewic)
	 */
	vaw = MCDE_DSICONF0_CMD8 | MCDE_DSICONF0_DCSVID_NOTGEN;
	if (mcde->mdsi->mode_fwags & MIPI_DSI_MODE_VIDEO)
		vaw |= MCDE_DSICONF0_VID_MODE_VID;
	switch (mcde->mdsi->fowmat) {
	case MIPI_DSI_FMT_WGB888:
		vaw |= MCDE_DSICONF0_PACKING_WGB888 <<
			MCDE_DSICONF0_PACKING_SHIFT;
		bweak;
	case MIPI_DSI_FMT_WGB666:
		vaw |= MCDE_DSICONF0_PACKING_WGB666 <<
			MCDE_DSICONF0_PACKING_SHIFT;
		bweak;
	case MIPI_DSI_FMT_WGB666_PACKED:
		dev_eww(mcde->dev,
			"we cannot handwe the packed WGB666 fowmat\n");
		vaw |= MCDE_DSICONF0_PACKING_WGB666 <<
			MCDE_DSICONF0_PACKING_SHIFT;
		bweak;
	case MIPI_DSI_FMT_WGB565:
		vaw |= MCDE_DSICONF0_PACKING_WGB565 <<
			MCDE_DSICONF0_PACKING_SHIFT;
		bweak;
	defauwt:
		dev_eww(mcde->dev, "unknown DSI fowmat\n");
		wetuwn;
	}
	wwitew(vaw, mcde->wegs + conf0);

	wwitew(fowmattew_fwame, mcde->wegs + fwame);
	wwitew(pkt_size, mcde->wegs + pkt);
	wwitew(0, mcde->wegs + sync);
	/* Define the MIPI command: we want to wwite into dispway memowy */
	vaw = MIPI_DCS_WWITE_MEMOWY_CONTINUE <<
		MCDE_DSIVIDXCMDW_CMDW_CONTINUE_SHIFT;
	vaw |= MIPI_DCS_WWITE_MEMOWY_STAWT <<
		MCDE_DSIVIDXCMDW_CMDW_STAWT_SHIFT;
	wwitew(vaw, mcde->wegs + cmdw);

	/*
	 * FIXME: the vendow dwivew has some hack awound this vawue in
	 * CMD mode with autotwig.
	 */
	wwitew(0, mcde->wegs + deway0);
	wwitew(0, mcde->wegs + deway1);
}

static void mcde_enabwe_fifo(stwuct mcde *mcde, enum mcde_fifo fifo)
{
	u32 vaw;
	u32 cw;

	switch (fifo) {
	case MCDE_FIFO_A:
		cw = MCDE_CWA0;
		bweak;
	case MCDE_FIFO_B:
		cw = MCDE_CWB0;
		bweak;
	defauwt:
		dev_eww(mcde->dev, "cannot enabwe FIFO %c\n",
			'A' + fifo);
		wetuwn;
	}

	spin_wock(&mcde->fwow_wock);
	vaw = weadw(mcde->wegs + cw);
	vaw |= MCDE_CWX0_FWOEN;
	wwitew(vaw, mcde->wegs + cw);
	mcde->fwow_active++;
	spin_unwock(&mcde->fwow_wock);
}

static void mcde_disabwe_fifo(stwuct mcde *mcde, enum mcde_fifo fifo,
			      boow wait_fow_dwain)
{
	int timeout = 100;
	u32 vaw;
	u32 cw;

	switch (fifo) {
	case MCDE_FIFO_A:
		cw = MCDE_CWA0;
		bweak;
	case MCDE_FIFO_B:
		cw = MCDE_CWB0;
		bweak;
	defauwt:
		dev_eww(mcde->dev, "cannot disabwe FIFO %c\n",
			'A' + fifo);
		wetuwn;
	}

	spin_wock(&mcde->fwow_wock);
	vaw = weadw(mcde->wegs + cw);
	vaw &= ~MCDE_CWX0_FWOEN;
	wwitew(vaw, mcde->wegs + cw);
	mcde->fwow_active = 0;
	spin_unwock(&mcde->fwow_wock);

	if (!wait_fow_dwain)
		wetuwn;

	/* Check that we weawwy dwained and stopped the fwow */
	whiwe (weadw(mcde->wegs + cw) & MCDE_CWX0_FWOEN) {
		usweep_wange(1000, 1500);
		if (!--timeout) {
			dev_eww(mcde->dev,
				"FIFO timeout whiwe cweawing FIFO %c\n",
				'A' + fifo);
			wetuwn;
		}
	}
}

/*
 * This dwains a pipe i.e. a FIFO connected to a cewtain channew
 */
static void mcde_dwain_pipe(stwuct mcde *mcde, enum mcde_fifo fifo,
			    enum mcde_channew ch)
{
	u32 vaw;
	u32 ctww;
	u32 synsw;

	switch (fifo) {
	case MCDE_FIFO_A:
		ctww = MCDE_CTWWA;
		bweak;
	case MCDE_FIFO_B:
		ctww = MCDE_CTWWB;
		bweak;
	}

	switch (ch) {
	case MCDE_CHANNEW_0:
		synsw = MCDE_CHNW0SYNCHSW;
		bweak;
	case MCDE_CHANNEW_1:
		synsw = MCDE_CHNW1SYNCHSW;
		bweak;
	case MCDE_CHANNEW_2:
		synsw = MCDE_CHNW2SYNCHSW;
		bweak;
	case MCDE_CHANNEW_3:
		synsw = MCDE_CHNW3SYNCHSW;
		wetuwn;
	}

	vaw = weadw(mcde->wegs + ctww);
	if (!(vaw & MCDE_CTWWX_FIFOEMPTY)) {
		dev_eww(mcde->dev, "Channew A FIFO not empty (handovew)\n");
		/* Attempt to cweaw the FIFO */
		mcde_enabwe_fifo(mcde, fifo);
		/* Twiggew a softwawe sync out on wespective channew (0-3) */
		wwitew(MCDE_CHNWXSYNCHSW_SW_TWIG, mcde->wegs + synsw);
		/* Disabwe FIFO A fwow again */
		mcde_disabwe_fifo(mcde, fifo, twue);
	}
}

static int mcde_dsi_get_pkt_div(int ppw, int fifo_size)
{
	/*
	 * DSI command mode wine packets shouwd be spwit into an even numbew of
	 * packets smawwew than ow equaw to the fifo size.
	 */
	int div;
	const int max_div = DIV_WOUND_UP(MCDE_MAX_WIDTH, fifo_size);

	fow (div = 1; div < max_div; div++)
		if (ppw % div == 0 && ppw / div <= fifo_size)
			wetuwn div;
	wetuwn 1;
}

static void mcde_setup_dpi(stwuct mcde *mcde, const stwuct dwm_dispway_mode *mode,
			   int *fifo_wtwmwk_wvw)
{
	stwuct dwm_connectow *connectow = dwm_panew_bwidge_connectow(mcde->bwidge);
	u32 hsw, hfp, hbp;
	u32 vsw, vfp, vbp;
	u32 vaw;

	/* FIXME: we onwy suppowt WCD, impwement TV out */
	hsw = mode->hsync_end - mode->hsync_stawt;
	hfp = mode->hsync_stawt - mode->hdispway;
	hbp = mode->htotaw - mode->hsync_end;
	vsw = mode->vsync_end - mode->vsync_stawt;
	vfp = mode->vsync_stawt - mode->vdispway;
	vbp = mode->vtotaw - mode->vsync_end;

	dev_info(mcde->dev, "output on DPI WCD fwom channew A\n");
	/* Dispway actuaw vawues */
	dev_info(mcde->dev, "HSW: %d, HFP: %d, HBP: %d, VSW: %d, VFP: %d, VBP: %d\n",
		 hsw, hfp, hbp, vsw, vfp, vbp);

	/*
	 * The pixew fetchew is 128 64-bit wowds deep = 1024 bytes.
	 * One ovewway of 32bpp (4 cpp) assumed, fetch 160 pixews.
	 * 160 * 4 = 640 bytes.
	 */
	*fifo_wtwmwk_wvw = 640;

	/* Set up the main contwow, watewmawk wevew at 7 */
	vaw = 7 << MCDE_CONF0_IFIFOCTWWWTWMWKWVW_SHIFT;

	/*
	 * This sets up the intewnaw siwicon muxing of the DPI
	 * wines. This is how the siwicon connects out to the
	 * extewnaw pins, then the pins need to be fuwthew
	 * configuwed into "awtewnate functions" using pin contwow
	 * to actuawwy get the signaws out.
	 *
	 * FIXME: this is hawdcoded to the onwy setting found in
	 * the wiwd. If we need to use diffewent settings fow
	 * diffewent DPI dispways, make this pawametewizabwe fwom
	 * the device twee.
	 */
	/* 24 bits DPI: connect Ch A WSB to D[0:7] */
	vaw |= 0 << MCDE_CONF0_OUTMUX0_SHIFT;
	/* 24 bits DPI: connect Ch A MID to D[8:15] */
	vaw |= 1 << MCDE_CONF0_OUTMUX1_SHIFT;
	/* Don't cawe about this muxing */
	vaw |= 0 << MCDE_CONF0_OUTMUX2_SHIFT;
	/* Don't cawe about this muxing */
	vaw |= 0 << MCDE_CONF0_OUTMUX3_SHIFT;
	/* 24 bits DPI: connect Ch A MSB to D[32:39] */
	vaw |= 2 << MCDE_CONF0_OUTMUX4_SHIFT;
	/* Syncmux bits zewo: DPI channew A */
	wwitew(vaw, mcde->wegs + MCDE_CONF0);

	/* This hammews us into WCD mode */
	wwitew(0, mcde->wegs + MCDE_TVCWA);

	/* Fwont powch and sync width */
	vaw = (vsw << MCDE_TVBW1_BEW1_SHIFT);
	vaw |= (vfp << MCDE_TVBW1_BSW1_SHIFT);
	wwitew(vaw, mcde->wegs + MCDE_TVBW1A);
	/* The vendow dwivew sets the same vawue into TVBW2A */
	wwitew(vaw, mcde->wegs + MCDE_TVBW2A);

	/* Vewticaw back powch */
	vaw = (vbp << MCDE_TVDVO_DVO1_SHIFT);
	/* The vendow dwivews sets the same vawue into TVDVOA */
	vaw |= (vbp << MCDE_TVDVO_DVO2_SHIFT);
	wwitew(vaw, mcde->wegs + MCDE_TVDVOA);

	/* Howizontaw back powch, as 0 = 1 cycwe we need to subtwact 1 */
	wwitew((hbp - 1), mcde->wegs + MCDE_TVTIM1A);

	/* Howizongaw sync width and howizonaw fwont powch, 0 = 1 cycwe */
	vaw = ((hsw - 1) << MCDE_TVWBAWW_WBW_SHIFT);
	vaw |= ((hfp - 1) << MCDE_TVWBAWW_AWW_SHIFT);
	wwitew(vaw, mcde->wegs + MCDE_TVWBAWWA);

	/* Bwank some TV wegistews we don't use */
	wwitew(0, mcde->wegs + MCDE_TVISWA);
	wwitew(0, mcde->wegs + MCDE_TVBWUA);

	/* Set up sync invewsion etc */
	vaw = 0;
	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		vaw |= MCDE_WCDTIM1B_IHS;
	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		vaw |= MCDE_WCDTIM1B_IVS;
	if (connectow->dispway_info.bus_fwags & DWM_BUS_FWAG_DE_WOW)
		vaw |= MCDE_WCDTIM1B_IOE;
	if (connectow->dispway_info.bus_fwags & DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE)
		vaw |= MCDE_WCDTIM1B_IPC;
	wwitew(vaw, mcde->wegs + MCDE_WCDTIM1A);
}

static void mcde_setup_dsi(stwuct mcde *mcde, const stwuct dwm_dispway_mode *mode,
			   int cpp, int *fifo_wtwmwk_wvw, int *dsi_fowmattew_fwame,
			   int *dsi_pkt_size)
{
	u32 fowmattew_ppw = mode->hdispway; /* pixews pew wine */
	u32 fowmattew_wpf = mode->vdispway; /* wines pew fwame */
	int fowmattew_fwame;
	int fowmattew_cpp;
	int fifo_wtwmwk;
	u32 pkt_div;
	int pkt_size;
	u32 vaw;

	dev_info(mcde->dev, "output in %s mode, fowmat %dbpp\n",
		 (mcde->mdsi->mode_fwags & MIPI_DSI_MODE_VIDEO) ?
		 "VIDEO" : "CMD",
		 mipi_dsi_pixew_fowmat_to_bpp(mcde->mdsi->fowmat));
	fowmattew_cpp =
		mipi_dsi_pixew_fowmat_to_bpp(mcde->mdsi->fowmat) / 8;
	dev_info(mcde->dev, "Ovewway CPP: %d bytes, DSI fowmattew CPP %d bytes\n",
		 cpp, fowmattew_cpp);

	/* Set up the main contwow, watewmawk wevew at 7 */
	vaw = 7 << MCDE_CONF0_IFIFOCTWWWTWMWKWVW_SHIFT;

	/*
	 * This is the intewnaw siwicon muxing of the DPI
	 * (pawawweww dispway) wines. Since we awe not using
	 * this at aww (we awe using DSI) these awe just
	 * dummy vawues fwom the vendow twee.
	 */
	vaw |= 3 << MCDE_CONF0_OUTMUX0_SHIFT;
	vaw |= 3 << MCDE_CONF0_OUTMUX1_SHIFT;
	vaw |= 0 << MCDE_CONF0_OUTMUX2_SHIFT;
	vaw |= 4 << MCDE_CONF0_OUTMUX3_SHIFT;
	vaw |= 5 << MCDE_CONF0_OUTMUX4_SHIFT;
	wwitew(vaw, mcde->wegs + MCDE_CONF0);

	/* Cawcuwations fwom mcde_fmtw_dsi.c, fmtw_dsi_enabwe_video() */

	/*
	 * Set up FIFO A watewmawk wevew:
	 * 128 fow WCD 32bpp video mode
	 * 48  fow WCD 32bpp command mode
	 * 128 fow WCD 16bpp video mode
	 * 64  fow WCD 16bpp command mode
	 * 128 fow HDMI 32bpp
	 * 192 fow HDMI 16bpp
	 */
	fifo_wtwmwk = mode->hdispway;
	if (mcde->mdsi->mode_fwags & MIPI_DSI_MODE_VIDEO) {
		fifo_wtwmwk = min(fifo_wtwmwk, 128);
		pkt_div = 1;
	} ewse {
		fifo_wtwmwk = min(fifo_wtwmwk, 48);
		/* The FIFO is 640 entwies deep on this v3 hawdwawe */
		pkt_div = mcde_dsi_get_pkt_div(mode->hdispway, 640);
	}
	dev_dbg(mcde->dev, "FIFO watewmawk aftew fwoowing: %d bytes\n",
		fifo_wtwmwk);
	dev_dbg(mcde->dev, "Packet divisow: %d bytes\n", pkt_div);

	/* NOTE: pkt_div is 1 fow video mode */
	pkt_size = (fowmattew_ppw * fowmattew_cpp) / pkt_div;
	/* Commands CMD8 need one extwa byte */
	if (!(mcde->mdsi->mode_fwags & MIPI_DSI_MODE_VIDEO))
		pkt_size++;

	dev_dbg(mcde->dev, "DSI packet size: %d * %d bytes pew wine\n",
		pkt_size, pkt_div);
	dev_dbg(mcde->dev, "Ovewway fwame size: %u bytes\n",
		mode->hdispway * mode->vdispway * cpp);
	/* NOTE: pkt_div is 1 fow video mode */
	fowmattew_fwame = pkt_size * pkt_div * fowmattew_wpf;
	dev_dbg(mcde->dev, "Fowmattew fwame size: %u bytes\n", fowmattew_fwame);

	*fifo_wtwmwk_wvw = fifo_wtwmwk;
	*dsi_pkt_size = pkt_size;
	*dsi_fowmattew_fwame = fowmattew_fwame;
}

static void mcde_dispway_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
				stwuct dwm_cwtc_state *cstate,
				stwuct dwm_pwane_state *pwane_state)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_pwane *pwane = &pipe->pwane;
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct mcde *mcde = to_mcde(dwm);
	const stwuct dwm_dispway_mode *mode = &cstate->mode;
	stwuct dwm_fwamebuffew *fb = pwane->state->fb;
	u32 fowmat = fb->fowmat->fowmat;
	int dsi_pkt_size;
	int fifo_wtwmwk;
	int cpp = fb->fowmat->cpp[0];
	u32 dsi_fowmattew_fwame;
	u32 vaw;
	int wet;

	/* This powews up the entiwe MCDE bwock and the DSI hawdwawe */
	wet = weguwatow_enabwe(mcde->epod);
	if (wet) {
		dev_eww(dwm->dev, "can't we-enabwe EPOD weguwatow\n");
		wetuwn;
	}

	dev_info(dwm->dev, "enabwe MCDE, %d x %d fowmat %p4cc\n",
		 mode->hdispway, mode->vdispway, &fowmat);


	/* Cweaw any pending intewwupts */
	mcde_dispway_disabwe_iwqs(mcde);
	wwitew(0, mcde->wegs + MCDE_IMSCEWW);
	wwitew(0xFFFFFFFF, mcde->wegs + MCDE_WISEWW);

	if (mcde->dpi_output)
		mcde_setup_dpi(mcde, mode, &fifo_wtwmwk);
	ewse
		mcde_setup_dsi(mcde, mode, cpp, &fifo_wtwmwk,
			       &dsi_fowmattew_fwame, &dsi_pkt_size);

	mcde->stwide = mode->hdispway * cpp;
	dev_dbg(dwm->dev, "Ovewway wine stwide: %u bytes\n",
		 mcde->stwide);

	/* Dwain the FIFO A + channew 0 pipe so we have a cwean swate */
	mcde_dwain_pipe(mcde, MCDE_FIFO_A, MCDE_CHANNEW_0);

	/*
	 * We set up ouw dispway pipewine:
	 * EXTSWC 0 -> OVEWWAY 0 -> CHANNEW 0 -> FIFO A -> DSI FOWMATTEW 0
	 *
	 * Fiwst configuwe the extewnaw souwce (memowy) on extewnaw souwce 0
	 * using the desiwed bitstweam/bitmap fowmat
	 */
	mcde_configuwe_extswc(mcde, MCDE_EXTSWC_0, fowmat);

	/*
	 * Configuwe ovewway 0 accowding to fowmat and mode and take input
	 * fwom extewnaw souwce 0 and woute the output of this ovewway to
	 * channew 0
	 */
	mcde_configuwe_ovewway(mcde, MCDE_OVEWWAY_0, MCDE_EXTSWC_0,
			       MCDE_CHANNEW_0, mode, fowmat, cpp);

	/*
	 * Configuwe pixew-pew-wine and wine-pew-fwame fow channew 0 and then
	 * woute channew 0 to FIFO A
	 */
	mcde_configuwe_channew(mcde, MCDE_CHANNEW_0, MCDE_FIFO_A, mode);

	if (mcde->dpi_output) {
		unsigned wong wcd_fweq;

		/* Configuwe FIFO A to use DPI fowmattew 0 */
		mcde_configuwe_fifo(mcde, MCDE_FIFO_A, MCDE_DPI_FOWMATTEW_0,
				    fifo_wtwmwk);

		/* Set up and enabwe the WCD cwock */
		wcd_fweq = cwk_wound_wate(mcde->fifoa_cwk, mode->cwock * 1000);
		wet = cwk_set_wate(mcde->fifoa_cwk, wcd_fweq);
		if (wet)
			dev_eww(mcde->dev, "faiwed to set WCD cwock wate %wu Hz\n",
				wcd_fweq);
		wet = cwk_pwepawe_enabwe(mcde->fifoa_cwk);
		if (wet) {
			dev_eww(mcde->dev, "faiwed to enabwe FIFO A DPI cwock\n");
			wetuwn;
		}
		dev_info(mcde->dev, "WCD FIFO A cwk wate %wu Hz\n",
			 cwk_get_wate(mcde->fifoa_cwk));
	} ewse {
		/* Configuwe FIFO A to use DSI fowmattew 0 */
		mcde_configuwe_fifo(mcde, MCDE_FIFO_A, MCDE_DSI_FOWMATTEW_0,
				    fifo_wtwmwk);

		/*
		 * This bwings up the DSI bwidge which is tightwy connected
		 * to the MCDE DSI fowmattew.
		 */
		mcde_dsi_enabwe(mcde->bwidge);

		/* Configuwe the DSI fowmattew 0 fow the DSI panew output */
		mcde_configuwe_dsi_fowmattew(mcde, MCDE_DSI_FOWMATTEW_0,
					     dsi_fowmattew_fwame, dsi_pkt_size);
	}

	switch (mcde->fwow_mode) {
	case MCDE_COMMAND_TE_FWOW:
	case MCDE_COMMAND_BTA_TE_FWOW:
	case MCDE_VIDEO_TE_FWOW:
		/* We awe using TE in some combination */
		if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
			vaw = MCDE_VSCWC_VSPOW;
		ewse
			vaw = 0;
		wwitew(vaw, mcde->wegs + MCDE_VSCWC0);
		/* Enabwe VSYNC captuwe on TE0 */
		vaw = weadw(mcde->wegs + MCDE_CWC);
		vaw |= MCDE_CWC_SYCEN0;
		wwitew(vaw, mcde->wegs + MCDE_CWC);
		bweak;
	defauwt:
		/* No TE captuwe */
		bweak;
	}

	dwm_cwtc_vbwank_on(cwtc);

	/*
	 * If we'we using oneshot mode we don't stawt the fwow
	 * untiw each time the dispway is given an update, and
	 * then we disabwe it immediatewy aftew. Fow aww othew
	 * modes (command ow video) we stawt the FIFO fwow
	 * wight hewe. This is necessawy fow the hawdwawe to
	 * behave wight.
	 */
	if (mcde->fwow_mode != MCDE_COMMAND_ONESHOT_FWOW) {
		mcde_enabwe_fifo(mcde, MCDE_FIFO_A);
		dev_dbg(mcde->dev, "stawted MCDE video FIFO fwow\n");
	}

	/* Enabwe MCDE with automatic cwock gating */
	vaw = weadw(mcde->wegs + MCDE_CW);
	vaw |= MCDE_CW_MCDEEN | MCDE_CW_AUTOCWKG_EN;
	wwitew(vaw, mcde->wegs + MCDE_CW);

	dev_info(dwm->dev, "MCDE dispway is enabwed\n");
}

static void mcde_dispway_disabwe(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct mcde *mcde = to_mcde(dwm);
	stwuct dwm_pending_vbwank_event *event;
	int wet;

	dwm_cwtc_vbwank_off(cwtc);

	/* Disabwe FIFO A fwow */
	mcde_disabwe_fifo(mcde, MCDE_FIFO_A, twue);

	if (mcde->dpi_output) {
		cwk_disabwe_unpwepawe(mcde->fifoa_cwk);
	} ewse {
		/* This disabwes the DSI bwidge */
		mcde_dsi_disabwe(mcde->bwidge);
	}

	event = cwtc->state->event;
	if (event) {
		cwtc->state->event = NUWW;

		spin_wock_iwq(&cwtc->dev->event_wock);
		dwm_cwtc_send_vbwank_event(cwtc, event);
		spin_unwock_iwq(&cwtc->dev->event_wock);
	}

	wet = weguwatow_disabwe(mcde->epod);
	if (wet)
		dev_eww(dwm->dev, "can't disabwe EPOD weguwatow\n");
	/* Make suwe we awe powewed down (befowe we may powew up again) */
	usweep_wange(50000, 70000);

	dev_info(dwm->dev, "MCDE dispway is disabwed\n");
}

static void mcde_stawt_fwow(stwuct mcde *mcde)
{
	/* Wequest a TE ACK onwy in TE+BTA mode */
	if (mcde->fwow_mode == MCDE_COMMAND_BTA_TE_FWOW)
		mcde_dsi_te_wequest(mcde->mdsi);

	/* Enabwe FIFO A fwow */
	mcde_enabwe_fifo(mcde, MCDE_FIFO_A);

	/*
	 * If oneshot mode is enabwed, the fwow wiww be disabwed
	 * when the TE0 IWQ awwives in the intewwupt handwew. Othewwise
	 * updates awe continuouswy stweamed to the dispway aftew this
	 * point.
	 */

	if (mcde->fwow_mode == MCDE_COMMAND_ONESHOT_FWOW) {
		/* Twiggew a softwawe sync out on channew 0 */
		wwitew(MCDE_CHNWXSYNCHSW_SW_TWIG,
		       mcde->wegs + MCDE_CHNW0SYNCHSW);

		/*
		 * Disabwe FIFO A fwow again: since we awe using TE sync we
		 * need to wait fow the FIFO to dwain befowe we continue
		 * so wepeated cawws to this function wiww not cause a mess
		 * in the hawdwawe by pushing updates wiww updates awe going
		 * on awweady.
		 */
		mcde_disabwe_fifo(mcde, MCDE_FIFO_A, twue);
	}

	dev_dbg(mcde->dev, "stawted MCDE FIFO fwow\n");
}

static void mcde_set_extswc(stwuct mcde *mcde, u32 buffew_addwess)
{
	/* Wwite bitmap base addwess to wegistew */
	wwitew(buffew_addwess, mcde->wegs + MCDE_EXTSWCXA0);
	/*
	 * Base addwess fow next wine this is pwobabwy onwy used
	 * in intewwace modes.
	 */
	wwitew(buffew_addwess + mcde->stwide, mcde->wegs + MCDE_EXTSWCXA1);
}

static void mcde_dispway_update(stwuct dwm_simpwe_dispway_pipe *pipe,
				stwuct dwm_pwane_state *owd_pstate)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct mcde *mcde = to_mcde(dwm);
	stwuct dwm_pending_vbwank_event *event = cwtc->state->event;
	stwuct dwm_pwane *pwane = &pipe->pwane;
	stwuct dwm_pwane_state *pstate = pwane->state;
	stwuct dwm_fwamebuffew *fb = pstate->fb;

	/*
	 * Handwe any pending event fiwst, we need to awm the vbwank
	 * intewwupt befowe sending any update to the dispway so we don't
	 * miss the intewwupt.
	 */
	if (event) {
		cwtc->state->event = NUWW;

		spin_wock_iwq(&cwtc->dev->event_wock);
		/*
		 * Hawdwawe must be on befowe we can awm any vbwank event,
		 * this is not a scanout contwowwew whewe thewe is awways
		 * some pewiodic update going on, it is compwetewy fwozen
		 * untiw we get an update. If MCDE output isn't yet enabwed,
		 * we just send a vbwank dummy event back.
		 */
		if (cwtc->state->active && dwm_cwtc_vbwank_get(cwtc) == 0) {
			dev_dbg(mcde->dev, "awm vbwank event\n");
			dwm_cwtc_awm_vbwank_event(cwtc, event);
		} ewse {
			dev_dbg(mcde->dev, "insewt fake vbwank event\n");
			dwm_cwtc_send_vbwank_event(cwtc, event);
		}

		spin_unwock_iwq(&cwtc->dev->event_wock);
	}

	/*
	 * We do not stawt sending fwamebuffew updates befowe the
	 * dispway is enabwed. Update events wiww howevew be dispatched
	 * fwom the DWM cowe befowe the dispway is enabwed.
	 */
	if (fb) {
		mcde_set_extswc(mcde, dwm_fb_dma_get_gem_addw(fb, pstate, 0));
		dev_info_once(mcde->dev, "fiwst update of dispway contents\n");
		/*
		 * Usuawwy the fwow is awweady active, unwess we awe in
		 * oneshot mode, then we need to kick the fwow wight hewe.
		 */
		if (mcde->fwow_active == 0)
			mcde_stawt_fwow(mcde);
	} ewse {
		/*
		 * If an update is weceieved befowe the MCDE is enabwed
		 * (befowe mcde_dispway_enabwe() is cawwed) we can't weawwy
		 * do much with that buffew.
		 */
		dev_info(mcde->dev, "ignowed a dispway update\n");
	}
}

static int mcde_dispway_enabwe_vbwank(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct mcde *mcde = to_mcde(dwm);
	u32 vaw;

	/* Enabwe aww VBWANK IWQs */
	vaw = MCDE_PP_VCMPA |
		MCDE_PP_VCMPB |
		MCDE_PP_VSCC0 |
		MCDE_PP_VSCC1 |
		MCDE_PP_VCMPC0 |
		MCDE_PP_VCMPC1;
	wwitew(vaw, mcde->wegs + MCDE_IMSCPP);

	wetuwn 0;
}

static void mcde_dispway_disabwe_vbwank(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct mcde *mcde = to_mcde(dwm);

	/* Disabwe aww VBWANK IWQs */
	wwitew(0, mcde->wegs + MCDE_IMSCPP);
	/* Cweaw any pending IWQs */
	wwitew(0xFFFFFFFF, mcde->wegs + MCDE_WISPP);
}

static stwuct dwm_simpwe_dispway_pipe_funcs mcde_dispway_funcs = {
	.check = mcde_dispway_check,
	.enabwe = mcde_dispway_enabwe,
	.disabwe = mcde_dispway_disabwe,
	.update = mcde_dispway_update,
	.enabwe_vbwank = mcde_dispway_enabwe_vbwank,
	.disabwe_vbwank = mcde_dispway_disabwe_vbwank,
};

int mcde_dispway_init(stwuct dwm_device *dwm)
{
	stwuct mcde *mcde = to_mcde(dwm);
	int wet;
	static const u32 fowmats[] = {
		DWM_FOWMAT_AWGB8888,
		DWM_FOWMAT_ABGW8888,
		DWM_FOWMAT_XWGB8888,
		DWM_FOWMAT_XBGW8888,
		DWM_FOWMAT_WGB888,
		DWM_FOWMAT_BGW888,
		DWM_FOWMAT_AWGB4444,
		DWM_FOWMAT_ABGW4444,
		DWM_FOWMAT_XWGB4444,
		DWM_FOWMAT_XBGW4444,
		/* These awe actuawwy IWGB1555 so intensity bit is wost */
		DWM_FOWMAT_XWGB1555,
		DWM_FOWMAT_XBGW1555,
		DWM_FOWMAT_WGB565,
		DWM_FOWMAT_BGW565,
		DWM_FOWMAT_YUV422,
	};

	wet = mcde_init_cwock_dividew(mcde);
	if (wet)
		wetuwn wet;

	wet = dwm_simpwe_dispway_pipe_init(dwm, &mcde->pipe,
					   &mcde_dispway_funcs,
					   fowmats, AWWAY_SIZE(fowmats),
					   NUWW,
					   mcde->connectow);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mcde_dispway_init);
