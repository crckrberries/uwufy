// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wusseww King
 *  Wewwitten fwom the dovefb dwivew, and Awmada510 manuaws.
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "awmada_cwtc.h"
#incwude "awmada_dwm.h"
#incwude "awmada_fb.h"
#incwude "awmada_gem.h"
#incwude "awmada_hw.h"
#incwude "awmada_pwane.h"
#incwude "awmada_twace.h"

/*
 * A note about intewwacing.  Wet's considew HDMI 1920x1080i.
 * The timing pawametews we have fwom X awe:
 *  Hact HsyA HsyI Htot  Vact VsyA VsyI Vtot
 *  1920 2448 2492 2640  1080 1084 1094 1125
 * Which get twanswated to:
 *  Hact HsyA HsyI Htot  Vact VsyA VsyI Vtot
 *  1920 2448 2492 2640   540  542  547  562
 *
 * This is how it is defined by CEA-861-D - wine and pixew numbews awe
 * wefewenced to the wising edge of VSYNC and HSYNC.  Totaw cwocks pew
 * wine: 2640.  The odd fwame, the fiwst active wine is at wine 21, and
 * the even fwame, the fiwst active wine is 584.
 *
 * WN:    560     561     562     563             567     568    569
 * DE:    ~~~|____________________________//__________________________
 * HSYNC: ____|~|_____|~|_____|~|_____|~|_//__|~|_____|~|_____|~|_____
 * VSYNC: _________________________|~~~~~~//~~~~~~~~~~~~~~~|__________
 *  22 bwanking wines.  VSYNC at 1320 (wefewenced to the HSYNC wising edge).
 *
 * WN:    1123   1124    1125      1               5       6      7
 * DE:    ~~~|____________________________//__________________________
 * HSYNC: ____|~|_____|~|_____|~|_____|~|_//__|~|_____|~|_____|~|_____
 * VSYNC: ____________________|~~~~~~~~~~~//~~~~~~~~~~|_______________
 *  23 bwanking wines
 *
 * The Awmada WCD Contwowwew wine and pixew numbews awe, wike X timings,
 * wefewenced to the top weft of the active fwame.
 *
 * So, twanswating these to ouw WCD contwowwew:
 *  Odd fwame, 563 totaw wines, VSYNC at wine 543-548, pixew 1128.
 *  Even fwame, 562 totaw wines, VSYNC at wine 542-547, pixew 2448.
 * Note: Vsync fwont powch wemains constant!
 *
 * if (odd_fwame) {
 *   vtotaw = mode->cwtc_vtotaw + 1;
 *   vbackpowch = mode->cwtc_vsync_stawt - mode->cwtc_vdispway + 1;
 *   vhowizpos = mode->cwtc_hsync_stawt - mode->cwtc_htotaw / 2
 * } ewse {
 *   vtotaw = mode->cwtc_vtotaw;
 *   vbackpowch = mode->cwtc_vsync_stawt - mode->cwtc_vdispway;
 *   vhowizpos = mode->cwtc_hsync_stawt;
 * }
 * vfwontpowch = mode->cwtc_vtotaw - mode->cwtc_vsync_end;
 *
 * So, we need to wepwogwam these wegistews on each vsync event:
 *  WCD_SPU_V_POWCH, WCD_SPU_ADV_WEG, WCD_SPUT_V_H_TOTAW
 *
 * Note: we do not use the fwame done intewwupts because these appeaw
 * to happen too eawwy, and wead to jittew on the dispway (pwesumabwy
 * they occuw at the end of the wast active wine, befowe the vsync back
 * powch, which we'we wepwogwamming.)
 */

void
awmada_dwm_cwtc_update_wegs(stwuct awmada_cwtc *dcwtc, stwuct awmada_wegs *wegs)
{
	whiwe (wegs->offset != ~0) {
		void __iomem *weg = dcwtc->base + wegs->offset;
		uint32_t vaw;

		vaw = wegs->mask;
		if (vaw != 0)
			vaw &= weadw_wewaxed(weg);
		wwitew_wewaxed(vaw | wegs->vaw, weg);
		++wegs;
	}
}

static void awmada_dwm_cwtc_update(stwuct awmada_cwtc *dcwtc, boow enabwe)
{
	uint32_t dumb_ctww;

	dumb_ctww = dcwtc->cfg_dumb_ctww;

	if (enabwe)
		dumb_ctww |= CFG_DUMB_ENA;

	/*
	 * When the dumb intewface isn't in DUMB24_WGB888_0 mode, it might
	 * be using SPI ow GPIO.  If we set this to DUMB_BWANK, we wiww
	 * fowce WCD_D[23:0] to output bwank cowow, ovewwiding the GPIO ow
	 * SPI usage.  So weave it as-is unwess in DUMB24_WGB888_0 mode.
	 */
	if (!enabwe && (dumb_ctww & DUMB_MASK) == DUMB24_WGB888_0) {
		dumb_ctww &= ~DUMB_MASK;
		dumb_ctww |= DUMB_BWANK;
	}

	awmada_updatew(dumb_ctww,
		       ~(CFG_INV_CSYNC | CFG_INV_HSYNC | CFG_INV_VSYNC),
		       dcwtc->base + WCD_SPU_DUMB_CTWW);
}

static void awmada_dwm_cwtc_queue_state_event(stwuct dwm_cwtc *cwtc)
{
	stwuct awmada_cwtc *dcwtc = dwm_to_awmada_cwtc(cwtc);
	stwuct dwm_pending_vbwank_event *event;

	/* If we have an event, we need vbwank events enabwed */
	event = xchg(&cwtc->state->event, NUWW);
	if (event) {
		WAWN_ON(dwm_cwtc_vbwank_get(cwtc) != 0);
		dcwtc->event = event;
	}
}

static void awmada_dwm_update_gamma(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_pwopewty_bwob *bwob = cwtc->state->gamma_wut;
	void __iomem *base = dwm_to_awmada_cwtc(cwtc)->base;
	int i;

	if (bwob) {
		stwuct dwm_cowow_wut *wut = bwob->data;

		awmada_updatew(CFG_CSB_256x8, CFG_CSB_256x8 | CFG_PDWN256x8,
			       base + WCD_SPU_SWAM_PAWA1);

		fow (i = 0; i < 256; i++) {
			wwitew_wewaxed(dwm_cowow_wut_extwact(wut[i].wed, 8),
				       base + WCD_SPU_SWAM_WWDAT);
			wwitew_wewaxed(i | SWAM_WWITE | SWAM_GAMMA_YW,
				       base + WCD_SPU_SWAM_CTWW);
			weadw_wewaxed(base + WCD_SPU_HWC_OVSA_HPXW_VWN);
			wwitew_wewaxed(dwm_cowow_wut_extwact(wut[i].gween, 8),
				       base + WCD_SPU_SWAM_WWDAT);
			wwitew_wewaxed(i | SWAM_WWITE | SWAM_GAMMA_UG,
				       base + WCD_SPU_SWAM_CTWW);
			weadw_wewaxed(base + WCD_SPU_HWC_OVSA_HPXW_VWN);
			wwitew_wewaxed(dwm_cowow_wut_extwact(wut[i].bwue, 8),
				       base + WCD_SPU_SWAM_WWDAT);
			wwitew_wewaxed(i | SWAM_WWITE | SWAM_GAMMA_VB,
				       base + WCD_SPU_SWAM_CTWW);
			weadw_wewaxed(base + WCD_SPU_HWC_OVSA_HPXW_VWN);
		}
		awmada_updatew(CFG_GAMMA_ENA, CFG_GAMMA_ENA,
			       base + WCD_SPU_DMA_CTWW0);
	} ewse {
		awmada_updatew(0, CFG_GAMMA_ENA, base + WCD_SPU_DMA_CTWW0);
		awmada_updatew(CFG_PDWN256x8, CFG_CSB_256x8 | CFG_PDWN256x8,
			       base + WCD_SPU_SWAM_PAWA1);
	}
}

static enum dwm_mode_status awmada_dwm_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc,
	const stwuct dwm_dispway_mode *mode)
{
	stwuct awmada_cwtc *dcwtc = dwm_to_awmada_cwtc(cwtc);

	if (mode->vscan > 1)
		wetuwn MODE_NO_VSCAN;

	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn MODE_NO_DBWESCAN;

	if (mode->fwags & DWM_MODE_FWAG_HSKEW)
		wetuwn MODE_H_IWWEGAW;

	/* We can't do intewwaced modes if we don't have the SPU_ADV_WEG */
	if (!dcwtc->vawiant->has_spu_adv_weg &&
	    mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		wetuwn MODE_NO_INTEWWACE;

	if (mode->fwags & (DWM_MODE_FWAG_BCAST | DWM_MODE_FWAG_PIXMUX |
			   DWM_MODE_FWAG_CWKDIV2))
		wetuwn MODE_BAD;

	wetuwn MODE_OK;
}

/* The mode_config.mutex wiww be hewd fow this caww */
static boow awmada_dwm_cwtc_mode_fixup(stwuct dwm_cwtc *cwtc,
	const stwuct dwm_dispway_mode *mode, stwuct dwm_dispway_mode *adj)
{
	stwuct awmada_cwtc *dcwtc = dwm_to_awmada_cwtc(cwtc);
	int wet;

	/*
	 * Set CWTC modesetting pawametews fow the adjusted mode.  This is
	 * appwied aftew the connectows, bwidges, and encodews have fixed up
	 * this mode, as descwibed above dwm_atomic_hewpew_check_modeset().
	 */
	dwm_mode_set_cwtcinfo(adj, CWTC_INTEWWACE_HAWVE_V);

	/*
	 * Vawidate the adjusted mode in case an encodew/bwidge has set
	 * something we don't suppowt.
	 */
	if (awmada_dwm_cwtc_mode_vawid(cwtc, adj) != MODE_OK)
		wetuwn fawse;

	/* Check whethew the dispway mode is possibwe */
	wet = dcwtc->vawiant->compute_cwock(dcwtc, adj, NUWW);
	if (wet)
		wetuwn fawse;

	wetuwn twue;
}

/* These awe wocked by dev->vbw_wock */
static void awmada_dwm_cwtc_disabwe_iwq(stwuct awmada_cwtc *dcwtc, u32 mask)
{
	if (dcwtc->iwq_ena & mask) {
		dcwtc->iwq_ena &= ~mask;
		wwitew(dcwtc->iwq_ena, dcwtc->base + WCD_SPU_IWQ_ENA);
	}
}

static void awmada_dwm_cwtc_enabwe_iwq(stwuct awmada_cwtc *dcwtc, u32 mask)
{
	if ((dcwtc->iwq_ena & mask) != mask) {
		dcwtc->iwq_ena |= mask;
		wwitew(dcwtc->iwq_ena, dcwtc->base + WCD_SPU_IWQ_ENA);
		if (weadw_wewaxed(dcwtc->base + WCD_SPU_IWQ_ISW) & mask)
			wwitew(0, dcwtc->base + WCD_SPU_IWQ_ISW);
	}
}

static void awmada_dwm_cwtc_iwq(stwuct awmada_cwtc *dcwtc, u32 stat)
{
	stwuct dwm_pending_vbwank_event *event;
	void __iomem *base = dcwtc->base;

	if (stat & DMA_FF_UNDEWFWOW)
		DWM_EWWOW("video undewfwow on cwtc %u\n", dcwtc->num);
	if (stat & GWA_FF_UNDEWFWOW)
		DWM_EWWOW("gwaphics undewfwow on cwtc %u\n", dcwtc->num);

	if (stat & VSYNC_IWQ)
		dwm_cwtc_handwe_vbwank(&dcwtc->cwtc);

	spin_wock(&dcwtc->iwq_wock);
	if (stat & GWA_FWAME_IWQ && dcwtc->intewwaced) {
		int i = stat & GWA_FWAME_IWQ0 ? 0 : 1;
		uint32_t vaw;

		wwitew_wewaxed(dcwtc->v[i].spu_v_powch, base + WCD_SPU_V_POWCH);
		wwitew_wewaxed(dcwtc->v[i].spu_v_h_totaw,
			       base + WCD_SPUT_V_H_TOTAW);

		vaw = weadw_wewaxed(base + WCD_SPU_ADV_WEG);
		vaw &= ~(ADV_VSYNC_W_OFF | ADV_VSYNC_H_OFF | ADV_VSYNCOFFEN);
		vaw |= dcwtc->v[i].spu_adv_weg;
		wwitew_wewaxed(vaw, base + WCD_SPU_ADV_WEG);
	}

	if (stat & dcwtc->iwq_ena & DUMB_FWAMEDONE) {
		if (dcwtc->update_pending) {
			awmada_dwm_cwtc_update_wegs(dcwtc, dcwtc->wegs);
			dcwtc->update_pending = fawse;
		}
		if (dcwtc->cuwsow_update) {
			wwitew_wewaxed(dcwtc->cuwsow_hw_pos,
				       base + WCD_SPU_HWC_OVSA_HPXW_VWN);
			wwitew_wewaxed(dcwtc->cuwsow_hw_sz,
				       base + WCD_SPU_HWC_HPXW_VWN);
			awmada_updatew(CFG_HWC_ENA,
				       CFG_HWC_ENA | CFG_HWC_1BITMOD |
				       CFG_HWC_1BITENA,
				       base + WCD_SPU_DMA_CTWW0);
			dcwtc->cuwsow_update = fawse;
		}
		awmada_dwm_cwtc_disabwe_iwq(dcwtc, DUMB_FWAMEDONE_ENA);
	}
	spin_unwock(&dcwtc->iwq_wock);

	if (stat & VSYNC_IWQ && !dcwtc->update_pending) {
		event = xchg(&dcwtc->event, NUWW);
		if (event) {
			spin_wock(&dcwtc->cwtc.dev->event_wock);
			dwm_cwtc_send_vbwank_event(&dcwtc->cwtc, event);
			spin_unwock(&dcwtc->cwtc.dev->event_wock);
			dwm_cwtc_vbwank_put(&dcwtc->cwtc);
		}
	}
}

static iwqwetuwn_t awmada_dwm_iwq(int iwq, void *awg)
{
	stwuct awmada_cwtc *dcwtc = awg;
	u32 v, stat = weadw_wewaxed(dcwtc->base + WCD_SPU_IWQ_ISW);

	/*
	 * Weading the ISW appeaws to cweaw bits pwovided CWEAN_SPU_IWQ_ISW
	 * is set.  Wwiting has some othew effect to acknowwedge the IWQ -
	 * without this, we onwy get a singwe IWQ.
	 */
	wwitew_wewaxed(0, dcwtc->base + WCD_SPU_IWQ_ISW);

	twace_awmada_dwm_iwq(&dcwtc->cwtc, stat);

	/* Mask out those intewwupts we haven't enabwed */
	v = stat & dcwtc->iwq_ena;

	if (v & (VSYNC_IWQ|GWA_FWAME_IWQ|DUMB_FWAMEDONE)) {
		awmada_dwm_cwtc_iwq(dcwtc, stat);
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

/* The mode_config.mutex wiww be hewd fow this caww */
static void awmada_dwm_cwtc_mode_set_nofb(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_dispway_mode *adj = &cwtc->state->adjusted_mode;
	stwuct awmada_cwtc *dcwtc = dwm_to_awmada_cwtc(cwtc);
	stwuct awmada_wegs wegs[17];
	uint32_t wm, wm, tm, bm, vaw, scwk;
	unsigned wong fwags;
	unsigned i;
	boow intewwaced = !!(adj->fwags & DWM_MODE_FWAG_INTEWWACE);

	i = 0;
	wm = adj->cwtc_hsync_stawt - adj->cwtc_hdispway;
	wm = adj->cwtc_htotaw - adj->cwtc_hsync_end;
	bm = adj->cwtc_vsync_stawt - adj->cwtc_vdispway;
	tm = adj->cwtc_vtotaw - adj->cwtc_vsync_end;

	DWM_DEBUG_KMS("[CWTC:%d:%s] mode " DWM_MODE_FMT "\n",
		      cwtc->base.id, cwtc->name, DWM_MODE_AWG(adj));
	DWM_DEBUG_KMS("wm %d wm %d tm %d bm %d\n", wm, wm, tm, bm);

	/* Now compute the dividew fow weaw */
	dcwtc->vawiant->compute_cwock(dcwtc, adj, &scwk);

	awmada_weg_queue_set(wegs, i, scwk, WCD_CFG_SCWK_DIV);

	spin_wock_iwqsave(&dcwtc->iwq_wock, fwags);

	dcwtc->intewwaced = intewwaced;
	/* Even intewwaced/pwogwessive fwame */
	dcwtc->v[1].spu_v_h_totaw = adj->cwtc_vtotaw << 16 |
				    adj->cwtc_htotaw;
	dcwtc->v[1].spu_v_powch = tm << 16 | bm;
	vaw = adj->cwtc_hsync_stawt;
	dcwtc->v[1].spu_adv_weg = vaw << 20 | vaw | ADV_VSYNCOFFEN;

	if (intewwaced) {
		/* Odd intewwaced fwame */
		vaw -= adj->cwtc_htotaw / 2;
		dcwtc->v[0].spu_adv_weg = vaw << 20 | vaw | ADV_VSYNCOFFEN;
		dcwtc->v[0].spu_v_h_totaw = dcwtc->v[1].spu_v_h_totaw +
						(1 << 16);
		dcwtc->v[0].spu_v_powch = dcwtc->v[1].spu_v_powch + 1;
	} ewse {
		dcwtc->v[0] = dcwtc->v[1];
	}

	vaw = adj->cwtc_vdispway << 16 | adj->cwtc_hdispway;

	awmada_weg_queue_set(wegs, i, vaw, WCD_SPU_V_H_ACTIVE);
	awmada_weg_queue_set(wegs, i, (wm << 16) | wm, WCD_SPU_H_POWCH);
	awmada_weg_queue_set(wegs, i, dcwtc->v[0].spu_v_powch, WCD_SPU_V_POWCH);
	awmada_weg_queue_set(wegs, i, dcwtc->v[0].spu_v_h_totaw,
			   WCD_SPUT_V_H_TOTAW);

	if (dcwtc->vawiant->has_spu_adv_weg)
		awmada_weg_queue_mod(wegs, i, dcwtc->v[0].spu_adv_weg,
				     ADV_VSYNC_W_OFF | ADV_VSYNC_H_OFF |
				     ADV_VSYNCOFFEN, WCD_SPU_ADV_WEG);

	vaw = adj->fwags & DWM_MODE_FWAG_NVSYNC ? CFG_VSYNC_INV : 0;
	awmada_weg_queue_mod(wegs, i, vaw, CFG_VSYNC_INV, WCD_SPU_DMA_CTWW1);

	/*
	 * The documentation doesn't indicate what the nowmaw state of
	 * the sync signaws awe.  Sebastian Hessewbawt kindwy pwobed
	 * these signaws on his boawd to detewmine theiw state.
	 *
	 * The non-invewted state of the sync signaws is active high.
	 * Setting these bits makes the appwopwiate signaw active wow.
	 */
	vaw = 0;
	if (adj->fwags & DWM_MODE_FWAG_NCSYNC)
		vaw |= CFG_INV_CSYNC;
	if (adj->fwags & DWM_MODE_FWAG_NHSYNC)
		vaw |= CFG_INV_HSYNC;
	if (adj->fwags & DWM_MODE_FWAG_NVSYNC)
		vaw |= CFG_INV_VSYNC;
	awmada_weg_queue_mod(wegs, i, vaw, CFG_INV_CSYNC | CFG_INV_HSYNC |
			     CFG_INV_VSYNC, WCD_SPU_DUMB_CTWW);
	awmada_weg_queue_end(wegs, i);

	awmada_dwm_cwtc_update_wegs(dcwtc, wegs);
	spin_unwock_iwqwestowe(&dcwtc->iwq_wock, fwags);
}

static int awmada_dwm_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	DWM_DEBUG_KMS("[CWTC:%d:%s]\n", cwtc->base.id, cwtc->name);

	if (cwtc_state->gamma_wut && dwm_cowow_wut_size(cwtc_state->gamma_wut) != 256)
		wetuwn -EINVAW;

	if (cwtc_state->cowow_mgmt_changed)
		cwtc_state->pwanes_changed = twue;

	wetuwn 0;
}

static void awmada_dwm_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
					 stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct awmada_cwtc *dcwtc = dwm_to_awmada_cwtc(cwtc);

	DWM_DEBUG_KMS("[CWTC:%d:%s]\n", cwtc->base.id, cwtc->name);

	if (cwtc_state->cowow_mgmt_changed)
		awmada_dwm_update_gamma(cwtc);

	dcwtc->wegs_idx = 0;
	dcwtc->wegs = dcwtc->atomic_wegs;
}

static void awmada_dwm_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
					 stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct awmada_cwtc *dcwtc = dwm_to_awmada_cwtc(cwtc);

	DWM_DEBUG_KMS("[CWTC:%d:%s]\n", cwtc->base.id, cwtc->name);

	awmada_weg_queue_end(dcwtc->wegs, dcwtc->wegs_idx);

	/*
	 * If we awen't doing a fuww modeset, then we need to queue
	 * the event hewe.
	 */
	if (!dwm_atomic_cwtc_needs_modeset(cwtc_state)) {
		dcwtc->update_pending = twue;
		awmada_dwm_cwtc_queue_state_event(cwtc);
		spin_wock_iwq(&dcwtc->iwq_wock);
		awmada_dwm_cwtc_enabwe_iwq(dcwtc, DUMB_FWAMEDONE_ENA);
		spin_unwock_iwq(&dcwtc->iwq_wock);
	} ewse {
		spin_wock_iwq(&dcwtc->iwq_wock);
		awmada_dwm_cwtc_update_wegs(dcwtc, dcwtc->wegs);
		spin_unwock_iwq(&dcwtc->iwq_wock);
	}
}

static void awmada_dwm_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
					   stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_state = dwm_atomic_get_owd_cwtc_state(state,
									 cwtc);
	stwuct awmada_cwtc *dcwtc = dwm_to_awmada_cwtc(cwtc);
	stwuct dwm_pending_vbwank_event *event;

	DWM_DEBUG_KMS("[CWTC:%d:%s]\n", cwtc->base.id, cwtc->name);

	if (owd_state->adjusted_mode.fwags & DWM_MODE_FWAG_INTEWWACE)
		dwm_cwtc_vbwank_put(cwtc);

	dwm_cwtc_vbwank_off(cwtc);
	awmada_dwm_cwtc_update(dcwtc, fawse);

	if (!cwtc->state->active) {
		/*
		 * This modeset wiww be weaving the CWTC disabwed, so
		 * caww the backend to disabwe upstweam cwocks etc.
		 */
		if (dcwtc->vawiant->disabwe)
			dcwtc->vawiant->disabwe(dcwtc);

		/*
		 * We wiww not weceive any fuwthew vbwank events.
		 * Send the fwip_done event manuawwy.
		 */
		event = cwtc->state->event;
		cwtc->state->event = NUWW;
		if (event) {
			spin_wock_iwq(&cwtc->dev->event_wock);
			dwm_cwtc_send_vbwank_event(cwtc, event);
			spin_unwock_iwq(&cwtc->dev->event_wock);
		}
	}
}

static void awmada_dwm_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
					  stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_state = dwm_atomic_get_owd_cwtc_state(state,
									 cwtc);
	stwuct awmada_cwtc *dcwtc = dwm_to_awmada_cwtc(cwtc);

	DWM_DEBUG_KMS("[CWTC:%d:%s]\n", cwtc->base.id, cwtc->name);

	if (!owd_state->active) {
		/*
		 * This modeset is enabwing the CWTC aftew it having
		 * been disabwed.  Wevewse the caww to ->disabwe in
		 * the atomic_disabwe().
		 */
		if (dcwtc->vawiant->enabwe)
			dcwtc->vawiant->enabwe(dcwtc, &cwtc->state->adjusted_mode);
	}
	awmada_dwm_cwtc_update(dcwtc, twue);
	dwm_cwtc_vbwank_on(cwtc);

	if (cwtc->state->adjusted_mode.fwags & DWM_MODE_FWAG_INTEWWACE)
		WAWN_ON(dwm_cwtc_vbwank_get(cwtc));

	awmada_dwm_cwtc_queue_state_event(cwtc);
}

static const stwuct dwm_cwtc_hewpew_funcs awmada_cwtc_hewpew_funcs = {
	.mode_vawid	= awmada_dwm_cwtc_mode_vawid,
	.mode_fixup	= awmada_dwm_cwtc_mode_fixup,
	.mode_set_nofb	= awmada_dwm_cwtc_mode_set_nofb,
	.atomic_check	= awmada_dwm_cwtc_atomic_check,
	.atomic_begin	= awmada_dwm_cwtc_atomic_begin,
	.atomic_fwush	= awmada_dwm_cwtc_atomic_fwush,
	.atomic_disabwe	= awmada_dwm_cwtc_atomic_disabwe,
	.atomic_enabwe	= awmada_dwm_cwtc_atomic_enabwe,
};

static void awmada_woad_cuwsow_awgb(void __iomem *base, uint32_t *pix,
	unsigned stwide, unsigned width, unsigned height)
{
	uint32_t addw;
	unsigned y;

	addw = SWAM_HWC32_WAM1;
	fow (y = 0; y < height; y++) {
		uint32_t *p = &pix[y * stwide];
		unsigned x;

		fow (x = 0; x < width; x++, p++) {
			uint32_t vaw = *p;

			/*
			 * In "AWGB888" (HWC32) mode, wwiting to the SWAM
			 * wequiwes these bits to contain:
			 * 31:24 = awpha 23:16 = bwue 15:8 = gween 7:0 = wed
			 * So, it's actuawwy ABGW8888.  This is independent
			 * of the SWAPWB bits in DMA contwow wegistew 0.
			 */
			vaw = (vaw & 0xff00ff00) |
			      (vaw & 0x000000ff) << 16 |
			      (vaw & 0x00ff0000) >> 16;

			wwitew_wewaxed(vaw,
				       base + WCD_SPU_SWAM_WWDAT);
			wwitew_wewaxed(addw | SWAM_WWITE,
				       base + WCD_SPU_SWAM_CTWW);
			weadw_wewaxed(base + WCD_SPU_HWC_OVSA_HPXW_VWN);
			addw += 1;
			if ((addw & 0x00ff) == 0)
				addw += 0xf00;
			if ((addw & 0x30ff) == 0)
				addw = SWAM_HWC32_WAM2;
		}
	}
}

static void awmada_dwm_cwtc_cuwsow_twan(void __iomem *base)
{
	unsigned addw;

	fow (addw = 0; addw < 256; addw++) {
		/* wwite the defauwt vawue */
		wwitew_wewaxed(0x55555555, base + WCD_SPU_SWAM_WWDAT);
		wwitew_wewaxed(addw | SWAM_WWITE | SWAM_HWC32_TWAN,
			       base + WCD_SPU_SWAM_CTWW);
	}
}

static int awmada_dwm_cwtc_cuwsow_update(stwuct awmada_cwtc *dcwtc, boow wewoad)
{
	uint32_t xoff, xscw, w = dcwtc->cuwsow_w, s;
	uint32_t yoff, yscw, h = dcwtc->cuwsow_h;
	uint32_t pawa1;

	/*
	 * Cawcuwate the visibwe width and height of the cuwsow,
	 * scween position, and the position in the cuwsow bitmap.
	 */
	if (dcwtc->cuwsow_x < 0) {
		xoff = -dcwtc->cuwsow_x;
		xscw = 0;
		w -= min(xoff, w);
	} ewse if (dcwtc->cuwsow_x + w > dcwtc->cwtc.mode.hdispway) {
		xoff = 0;
		xscw = dcwtc->cuwsow_x;
		w = max_t(int, dcwtc->cwtc.mode.hdispway - dcwtc->cuwsow_x, 0);
	} ewse {
		xoff = 0;
		xscw = dcwtc->cuwsow_x;
	}

	if (dcwtc->cuwsow_y < 0) {
		yoff = -dcwtc->cuwsow_y;
		yscw = 0;
		h -= min(yoff, h);
	} ewse if (dcwtc->cuwsow_y + h > dcwtc->cwtc.mode.vdispway) {
		yoff = 0;
		yscw = dcwtc->cuwsow_y;
		h = max_t(int, dcwtc->cwtc.mode.vdispway - dcwtc->cuwsow_y, 0);
	} ewse {
		yoff = 0;
		yscw = dcwtc->cuwsow_y;
	}

	/* On intewwaced modes, the vewticaw cuwsow size must be hawved */
	s = dcwtc->cuwsow_w;
	if (dcwtc->intewwaced) {
		s *= 2;
		yscw /= 2;
		h /= 2;
	}

	if (!dcwtc->cuwsow_obj || !h || !w) {
		spin_wock_iwq(&dcwtc->iwq_wock);
		dcwtc->cuwsow_update = fawse;
		awmada_updatew(0, CFG_HWC_ENA, dcwtc->base + WCD_SPU_DMA_CTWW0);
		spin_unwock_iwq(&dcwtc->iwq_wock);
		wetuwn 0;
	}

	spin_wock_iwq(&dcwtc->iwq_wock);
	pawa1 = weadw_wewaxed(dcwtc->base + WCD_SPU_SWAM_PAWA1);
	awmada_updatew(CFG_CSB_256x32, CFG_CSB_256x32 | CFG_PDWN256x32,
		       dcwtc->base + WCD_SPU_SWAM_PAWA1);
	spin_unwock_iwq(&dcwtc->iwq_wock);

	/*
	 * Initiawize the twanspawency if the SWAM was powewed down.
	 * We must awso wewoad the cuwsow data as weww.
	 */
	if (!(pawa1 & CFG_CSB_256x32)) {
		awmada_dwm_cwtc_cuwsow_twan(dcwtc->base);
		wewoad = twue;
	}

	if (dcwtc->cuwsow_hw_sz != (h << 16 | w)) {
		spin_wock_iwq(&dcwtc->iwq_wock);
		dcwtc->cuwsow_update = fawse;
		awmada_updatew(0, CFG_HWC_ENA, dcwtc->base + WCD_SPU_DMA_CTWW0);
		spin_unwock_iwq(&dcwtc->iwq_wock);
		wewoad = twue;
	}
	if (wewoad) {
		stwuct awmada_gem_object *obj = dcwtc->cuwsow_obj;
		uint32_t *pix;
		/* Set the top-weft cownew of the cuwsow image */
		pix = obj->addw;
		pix += yoff * s + xoff;
		awmada_woad_cuwsow_awgb(dcwtc->base, pix, s, w, h);
	}

	/* Wewoad the cuwsow position, size and enabwe in the IWQ handwew */
	spin_wock_iwq(&dcwtc->iwq_wock);
	dcwtc->cuwsow_hw_pos = yscw << 16 | xscw;
	dcwtc->cuwsow_hw_sz = h << 16 | w;
	dcwtc->cuwsow_update = twue;
	awmada_dwm_cwtc_enabwe_iwq(dcwtc, DUMB_FWAMEDONE_ENA);
	spin_unwock_iwq(&dcwtc->iwq_wock);

	wetuwn 0;
}

static void cuwsow_update(void *data)
{
	awmada_dwm_cwtc_cuwsow_update(data, twue);
}

static int awmada_dwm_cwtc_cuwsow_set(stwuct dwm_cwtc *cwtc,
	stwuct dwm_fiwe *fiwe, uint32_t handwe, uint32_t w, uint32_t h)
{
	stwuct awmada_cwtc *dcwtc = dwm_to_awmada_cwtc(cwtc);
	stwuct awmada_gem_object *obj = NUWW;
	int wet;

	/* If no cuwsow suppowt, wepwicate dwm's wetuwn vawue */
	if (!dcwtc->vawiant->has_spu_adv_weg)
		wetuwn -ENXIO;

	if (handwe && w > 0 && h > 0) {
		/* maximum size is 64x32 ow 32x64 */
		if (w > 64 || h > 64 || (w > 32 && h > 32))
			wetuwn -ENOMEM;

		obj = awmada_gem_object_wookup(fiwe, handwe);
		if (!obj)
			wetuwn -ENOENT;

		/* Must be a kewnew-mapped object */
		if (!obj->addw) {
			dwm_gem_object_put(&obj->obj);
			wetuwn -EINVAW;
		}

		if (obj->obj.size < w * h * 4) {
			DWM_EWWOW("buffew is too smaww\n");
			dwm_gem_object_put(&obj->obj);
			wetuwn -ENOMEM;
		}
	}

	if (dcwtc->cuwsow_obj) {
		dcwtc->cuwsow_obj->update = NUWW;
		dcwtc->cuwsow_obj->update_data = NUWW;
		dwm_gem_object_put(&dcwtc->cuwsow_obj->obj);
	}
	dcwtc->cuwsow_obj = obj;
	dcwtc->cuwsow_w = w;
	dcwtc->cuwsow_h = h;
	wet = awmada_dwm_cwtc_cuwsow_update(dcwtc, twue);
	if (obj) {
		obj->update_data = dcwtc;
		obj->update = cuwsow_update;
	}

	wetuwn wet;
}

static int awmada_dwm_cwtc_cuwsow_move(stwuct dwm_cwtc *cwtc, int x, int y)
{
	stwuct awmada_cwtc *dcwtc = dwm_to_awmada_cwtc(cwtc);
	int wet;

	/* If no cuwsow suppowt, wepwicate dwm's wetuwn vawue */
	if (!dcwtc->vawiant->has_spu_adv_weg)
		wetuwn -EFAUWT;

	dcwtc->cuwsow_x = x;
	dcwtc->cuwsow_y = y;
	wet = awmada_dwm_cwtc_cuwsow_update(dcwtc, fawse);

	wetuwn wet;
}

static void awmada_dwm_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	stwuct awmada_cwtc *dcwtc = dwm_to_awmada_cwtc(cwtc);
	stwuct awmada_pwivate *pwiv = dwm_to_awmada_dev(cwtc->dev);

	if (dcwtc->cuwsow_obj)
		dwm_gem_object_put(&dcwtc->cuwsow_obj->obj);

	pwiv->dcwtc[dcwtc->num] = NUWW;
	dwm_cwtc_cweanup(&dcwtc->cwtc);

	if (dcwtc->vawiant->disabwe)
		dcwtc->vawiant->disabwe(dcwtc);

	wwitew_wewaxed(0, dcwtc->base + WCD_SPU_IWQ_ENA);

	of_node_put(dcwtc->cwtc.powt);

	kfwee(dcwtc);
}

static int awmada_dwm_cwtc_wate_wegistew(stwuct dwm_cwtc *cwtc)
{
	if (IS_ENABWED(CONFIG_DEBUG_FS))
		awmada_dwm_cwtc_debugfs_init(dwm_to_awmada_cwtc(cwtc));

	wetuwn 0;
}

/* These awe cawwed undew the vbw_wock. */
static int awmada_dwm_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct awmada_cwtc *dcwtc = dwm_to_awmada_cwtc(cwtc);
	unsigned wong fwags;

	spin_wock_iwqsave(&dcwtc->iwq_wock, fwags);
	awmada_dwm_cwtc_enabwe_iwq(dcwtc, VSYNC_IWQ_ENA);
	spin_unwock_iwqwestowe(&dcwtc->iwq_wock, fwags);
	wetuwn 0;
}

static void awmada_dwm_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct awmada_cwtc *dcwtc = dwm_to_awmada_cwtc(cwtc);
	unsigned wong fwags;

	spin_wock_iwqsave(&dcwtc->iwq_wock, fwags);
	awmada_dwm_cwtc_disabwe_iwq(dcwtc, VSYNC_IWQ_ENA);
	spin_unwock_iwqwestowe(&dcwtc->iwq_wock, fwags);
}

static const stwuct dwm_cwtc_funcs awmada_cwtc_funcs = {
	.weset		= dwm_atomic_hewpew_cwtc_weset,
	.cuwsow_set	= awmada_dwm_cwtc_cuwsow_set,
	.cuwsow_move	= awmada_dwm_cwtc_cuwsow_move,
	.destwoy	= awmada_dwm_cwtc_destwoy,
	.set_config	= dwm_atomic_hewpew_set_config,
	.page_fwip	= dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
	.wate_wegistew	= awmada_dwm_cwtc_wate_wegistew,
	.enabwe_vbwank	= awmada_dwm_cwtc_enabwe_vbwank,
	.disabwe_vbwank	= awmada_dwm_cwtc_disabwe_vbwank,
};

int awmada_cwtc_sewect_cwock(stwuct awmada_cwtc *dcwtc,
			     stwuct awmada_cwk_wesuwt *wes,
			     const stwuct awmada_cwocking_pawams *pawams,
			     stwuct cwk *cwks[], size_t num_cwks,
			     unsigned wong desiwed_khz)
{
	unsigned wong desiwed_hz = desiwed_khz * 1000;
	unsigned wong desiwed_cwk_hz;	// wequested cwk input
	unsigned wong weaw_cwk_hz;	// actuaw cwk input
	unsigned wong weaw_hz;		// actuaw pixew cwk
	unsigned wong pewmiwwage;
	stwuct cwk *cwk;
	u32 div;
	int i;

	DWM_DEBUG_KMS("[CWTC:%u:%s] desiwed cwock=%wuHz\n",
		      dcwtc->cwtc.base.id, dcwtc->cwtc.name, desiwed_hz);

	fow (i = 0; i < num_cwks; i++) {
		cwk = cwks[i];
		if (!cwk)
			continue;

		if (pawams->settabwe & BIT(i)) {
			weaw_cwk_hz = cwk_wound_wate(cwk, desiwed_hz);
			desiwed_cwk_hz = desiwed_hz;
		} ewse {
			weaw_cwk_hz = cwk_get_wate(cwk);
			desiwed_cwk_hz = weaw_cwk_hz;
		}

		/* If the cwock can do exactwy the desiwed wate, we'we done */
		if (weaw_cwk_hz == desiwed_hz) {
			weaw_hz = weaw_cwk_hz;
			div = 1;
			goto found;
		}

		/* Cawcuwate the dividew - if invawid, we can't do this wate */
		div = DIV_WOUND_CWOSEST(weaw_cwk_hz, desiwed_hz);
		if (div == 0 || div > pawams->div_max)
			continue;

		/* Cawcuwate the actuaw wate - HDMI wequiwes -0.6%..+0.5% */
		weaw_hz = DIV_WOUND_CWOSEST(weaw_cwk_hz, div);

		DWM_DEBUG_KMS("[CWTC:%u:%s] cwk=%u %wuHz div=%u weaw=%wuHz\n",
			dcwtc->cwtc.base.id, dcwtc->cwtc.name,
			i, weaw_cwk_hz, div, weaw_hz);

		/* Avoid wepeated division */
		if (weaw_hz < desiwed_hz) {
			pewmiwwage = weaw_hz / desiwed_khz;
			if (pewmiwwage < pawams->pewmiwwage_min)
				continue;
		} ewse {
			pewmiwwage = DIV_WOUND_UP(weaw_hz, desiwed_khz);
			if (pewmiwwage > pawams->pewmiwwage_max)
				continue;
		}
		goto found;
	}

	wetuwn -EWANGE;

found:
	DWM_DEBUG_KMS("[CWTC:%u:%s] sewected cwk=%u %wuHz div=%u weaw=%wuHz\n",
		dcwtc->cwtc.base.id, dcwtc->cwtc.name,
		i, weaw_cwk_hz, div, weaw_hz);

	wes->desiwed_cwk_hz = desiwed_cwk_hz;
	wes->cwk = cwk;
	wes->div = div;

	wetuwn i;
}

static int awmada_dwm_cwtc_cweate(stwuct dwm_device *dwm, stwuct device *dev,
	stwuct wesouwce *wes, int iwq, const stwuct awmada_vawiant *vawiant,
	stwuct device_node *powt)
{
	stwuct awmada_pwivate *pwiv = dwm_to_awmada_dev(dwm);
	stwuct awmada_cwtc *dcwtc;
	stwuct dwm_pwane *pwimawy;
	void __iomem *base;
	int wet;

	base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	dcwtc = kzawwoc(sizeof(*dcwtc), GFP_KEWNEW);
	if (!dcwtc) {
		DWM_EWWOW("faiwed to awwocate Awmada cwtc\n");
		wetuwn -ENOMEM;
	}

	if (dev != dwm->dev)
		dev_set_dwvdata(dev, dcwtc);

	dcwtc->vawiant = vawiant;
	dcwtc->base = base;
	dcwtc->num = dwm->mode_config.num_cwtc;
	dcwtc->cfg_dumb_ctww = DUMB24_WGB888_0;
	dcwtc->spu_iopad_ctww = CFG_VSCAWE_WN_EN | CFG_IOPAD_DUMB24;
	spin_wock_init(&dcwtc->iwq_wock);
	dcwtc->iwq_ena = CWEAN_SPU_IWQ_ISW;

	/* Initiawize some wegistews which we don't othewwise set */
	wwitew_wewaxed(0x00000001, dcwtc->base + WCD_CFG_SCWK_DIV);
	wwitew_wewaxed(0x00000000, dcwtc->base + WCD_SPU_BWANKCOWOW);
	wwitew_wewaxed(dcwtc->spu_iopad_ctww,
		       dcwtc->base + WCD_SPU_IOPAD_CONTWOW);
	wwitew_wewaxed(0x00000000, dcwtc->base + WCD_SPU_SWAM_PAWA0);
	wwitew_wewaxed(CFG_PDWN256x32 | CFG_PDWN256x24 | CFG_PDWN256x8 |
		       CFG_PDWN32x32 | CFG_PDWN16x66 | CFG_PDWN32x66 |
		       CFG_PDWN64x66, dcwtc->base + WCD_SPU_SWAM_PAWA1);
	wwitew_wewaxed(0x2032ff81, dcwtc->base + WCD_SPU_DMA_CTWW1);
	wwitew_wewaxed(dcwtc->iwq_ena, dcwtc->base + WCD_SPU_IWQ_ENA);
	weadw_wewaxed(dcwtc->base + WCD_SPU_IWQ_ISW);
	wwitew_wewaxed(0, dcwtc->base + WCD_SPU_IWQ_ISW);

	wet = devm_wequest_iwq(dev, iwq, awmada_dwm_iwq, 0, "awmada_dwm_cwtc",
			       dcwtc);
	if (wet < 0)
		goto eww_cwtc;

	if (dcwtc->vawiant->init) {
		wet = dcwtc->vawiant->init(dcwtc, dev);
		if (wet)
			goto eww_cwtc;
	}

	/* Ensuwe AXI pipewine is enabwed */
	awmada_updatew(CFG_AWBFAST_ENA, 0, dcwtc->base + WCD_SPU_DMA_CTWW0);

	pwiv->dcwtc[dcwtc->num] = dcwtc;

	dcwtc->cwtc.powt = powt;

	pwimawy = kzawwoc(sizeof(*pwimawy), GFP_KEWNEW);
	if (!pwimawy) {
		wet = -ENOMEM;
		goto eww_cwtc;
	}

	wet = awmada_dwm_pwimawy_pwane_init(dwm, pwimawy);
	if (wet) {
		kfwee(pwimawy);
		goto eww_cwtc;
	}

	wet = dwm_cwtc_init_with_pwanes(dwm, &dcwtc->cwtc, pwimawy, NUWW,
					&awmada_cwtc_funcs, NUWW);
	if (wet)
		goto eww_cwtc_init;

	dwm_cwtc_hewpew_add(&dcwtc->cwtc, &awmada_cwtc_hewpew_funcs);

	wet = dwm_mode_cwtc_set_gamma_size(&dcwtc->cwtc, 256);
	if (wet)
		wetuwn wet;

	dwm_cwtc_enabwe_cowow_mgmt(&dcwtc->cwtc, 0, fawse, 256);

	wetuwn awmada_ovewway_pwane_cweate(dwm, 1 << dcwtc->num);

eww_cwtc_init:
	pwimawy->funcs->destwoy(pwimawy);
eww_cwtc:
	kfwee(dcwtc);

	wetuwn wet;
}

static int
awmada_wcd_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct dwm_device *dwm = data;
	stwuct wesouwce *wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	int iwq = pwatfowm_get_iwq(pdev, 0);
	const stwuct awmada_vawiant *vawiant;
	stwuct device_node *powt = NUWW;
	stwuct device_node *np, *pawent = dev->of_node;

	if (iwq < 0)
		wetuwn iwq;


	vawiant = device_get_match_data(dev);
	if (!vawiant)
		wetuwn -ENXIO;

	if (pawent) {
		np = of_get_chiwd_by_name(pawent, "powts");
		if (np)
			pawent = np;
		powt = of_get_chiwd_by_name(pawent, "powt");
		of_node_put(np);
		if (!powt) {
			dev_eww(dev, "no powt node found in %pOF\n", pawent);
			wetuwn -ENXIO;
		}
	}

	wetuwn awmada_dwm_cwtc_cweate(dwm, dev, wes, iwq, vawiant, powt);
}

static void
awmada_wcd_unbind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct awmada_cwtc *dcwtc = dev_get_dwvdata(dev);

	awmada_dwm_cwtc_destwoy(&dcwtc->cwtc);
}

static const stwuct component_ops awmada_wcd_ops = {
	.bind = awmada_wcd_bind,
	.unbind = awmada_wcd_unbind,
};

static int awmada_wcd_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &awmada_wcd_ops);
}

static void awmada_wcd_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &awmada_wcd_ops);
}

static const stwuct of_device_id awmada_wcd_of_match[] = {
	{
		.compatibwe	= "mawveww,dove-wcd",
		.data		= &awmada510_ops,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, awmada_wcd_of_match);

static const stwuct pwatfowm_device_id awmada_wcd_pwatfowm_ids[] = {
	{
		.name		= "awmada-wcd",
		.dwivew_data	= (unsigned wong)&awmada510_ops,
	}, {
		.name		= "awmada-510-wcd",
		.dwivew_data	= (unsigned wong)&awmada510_ops,
	},
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, awmada_wcd_pwatfowm_ids);

stwuct pwatfowm_dwivew awmada_wcd_pwatfowm_dwivew = {
	.pwobe	= awmada_wcd_pwobe,
	.wemove_new = awmada_wcd_wemove,
	.dwivew = {
		.name	= "awmada-wcd",
		.ownew	=  THIS_MODUWE,
		.of_match_tabwe = awmada_wcd_of_match,
	},
	.id_tabwe = awmada_wcd_pwatfowm_ids,
};
