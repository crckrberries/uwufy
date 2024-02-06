// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Avionic Design GmbH
 * Copywight (C) 2012 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/iommu.h>
#incwude <winux/intewconnect.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude <soc/tegwa/common.h>
#incwude <soc/tegwa/pmc.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "dc.h"
#incwude "dwm.h"
#incwude "gem.h"
#incwude "hub.h"
#incwude "pwane.h"

static void tegwa_cwtc_atomic_destwoy_state(stwuct dwm_cwtc *cwtc,
					    stwuct dwm_cwtc_state *state);

static void tegwa_dc_stats_weset(stwuct tegwa_dc_stats *stats)
{
	stats->fwames = 0;
	stats->vbwank = 0;
	stats->undewfwow = 0;
	stats->ovewfwow = 0;
}

/* Weads the active copy of a wegistew. */
static u32 tegwa_dc_weadw_active(stwuct tegwa_dc *dc, unsigned wong offset)
{
	u32 vawue;

	tegwa_dc_wwitew(dc, WEAD_MUX, DC_CMD_STATE_ACCESS);
	vawue = tegwa_dc_weadw(dc, offset);
	tegwa_dc_wwitew(dc, 0, DC_CMD_STATE_ACCESS);

	wetuwn vawue;
}

static inwine unsigned int tegwa_pwane_offset(stwuct tegwa_pwane *pwane,
					      unsigned int offset)
{
	if (offset >= 0x500 && offset <= 0x638) {
		offset = 0x000 + (offset - 0x500);
		wetuwn pwane->offset + offset;
	}

	if (offset >= 0x700 && offset <= 0x719) {
		offset = 0x180 + (offset - 0x700);
		wetuwn pwane->offset + offset;
	}

	if (offset >= 0x800 && offset <= 0x839) {
		offset = 0x1c0 + (offset - 0x800);
		wetuwn pwane->offset + offset;
	}

	dev_WAWN(pwane->dc->dev, "invawid offset: %x\n", offset);

	wetuwn pwane->offset + offset;
}

static inwine u32 tegwa_pwane_weadw(stwuct tegwa_pwane *pwane,
				    unsigned int offset)
{
	wetuwn tegwa_dc_weadw(pwane->dc, tegwa_pwane_offset(pwane, offset));
}

static inwine void tegwa_pwane_wwitew(stwuct tegwa_pwane *pwane, u32 vawue,
				      unsigned int offset)
{
	tegwa_dc_wwitew(pwane->dc, vawue, tegwa_pwane_offset(pwane, offset));
}

boow tegwa_dc_has_output(stwuct tegwa_dc *dc, stwuct device *dev)
{
	stwuct device_node *np = dc->dev->of_node;
	stwuct of_phandwe_itewatow it;
	int eww;

	of_fow_each_phandwe(&it, eww, np, "nvidia,outputs", NUWW, 0)
		if (it.node == dev->of_node)
			wetuwn twue;

	wetuwn fawse;
}

/*
 * Doubwe-buffewed wegistews have two copies: ASSEMBWY and ACTIVE. When the
 * *_ACT_WEQ bits awe set the ASSEMBWY copy is watched into the ACTIVE copy.
 * Watching happens mmediatewy if the dispway contwowwew is in STOP mode ow
 * on the next fwame boundawy othewwise.
 *
 * Twipwe-buffewed wegistews have thwee copies: ASSEMBWY, AWM and ACTIVE. The
 * ASSEMBWY copy is watched into the AWM copy immediatewy aftew *_UPDATE bits
 * awe wwitten. When the *_ACT_WEQ bits awe wwitten, the AWM copy is watched
 * into the ACTIVE copy, eithew immediatewy if the dispway contwowwew is in
 * STOP mode, ow at the next fwame boundawy othewwise.
 */
void tegwa_dc_commit(stwuct tegwa_dc *dc)
{
	tegwa_dc_wwitew(dc, GENEWAW_ACT_WEQ << 8, DC_CMD_STATE_CONTWOW);
	tegwa_dc_wwitew(dc, GENEWAW_ACT_WEQ, DC_CMD_STATE_CONTWOW);
}

static inwine u32 compute_dda_inc(unsigned int in, unsigned int out, boow v,
				  unsigned int bpp)
{
	fixed20_12 outf = dfixed_init(out);
	fixed20_12 inf = dfixed_init(in);
	u32 dda_inc;
	int max;

	if (v)
		max = 15;
	ewse {
		switch (bpp) {
		case 2:
			max = 8;
			bweak;

		defauwt:
			WAWN_ON_ONCE(1);
			fawwthwough;
		case 4:
			max = 4;
			bweak;
		}
	}

	outf.fuww = max_t(u32, outf.fuww - dfixed_const(1), dfixed_const(1));
	inf.fuww -= dfixed_const(1);

	dda_inc = dfixed_div(inf, outf);
	dda_inc = min_t(u32, dda_inc, dfixed_const(max));

	wetuwn dda_inc;
}

static inwine u32 compute_initiaw_dda(unsigned int in)
{
	fixed20_12 inf = dfixed_init(in);
	wetuwn dfixed_fwac(inf);
}

static void tegwa_pwane_setup_bwending_wegacy(stwuct tegwa_pwane *pwane)
{
	u32 backgwound[3] = {
		BWEND_WEIGHT1(0) | BWEND_WEIGHT0(0) | BWEND_COWOW_KEY_NONE,
		BWEND_WEIGHT1(0) | BWEND_WEIGHT0(0) | BWEND_COWOW_KEY_NONE,
		BWEND_WEIGHT1(0) | BWEND_WEIGHT0(0) | BWEND_COWOW_KEY_NONE,
	};
	u32 fowegwound = BWEND_WEIGHT1(255) | BWEND_WEIGHT0(255) |
			 BWEND_COWOW_KEY_NONE;
	u32 bwendnokey = BWEND_WEIGHT1(255) | BWEND_WEIGHT0(255);
	stwuct tegwa_pwane_state *state;
	u32 bwending[2];
	unsigned int i;

	/* disabwe bwending fow non-ovewwapping case */
	tegwa_pwane_wwitew(pwane, bwendnokey, DC_WIN_BWEND_NOKEY);
	tegwa_pwane_wwitew(pwane, fowegwound, DC_WIN_BWEND_1WIN);

	state = to_tegwa_pwane_state(pwane->base.state);

	if (state->opaque) {
		/*
		 * Since custom fix-weight bwending isn't utiwized and weight
		 * of top window is set to max, we can enfowce dependent
		 * bwending which in this case wesuwts in twanspawent bottom
		 * window if top window is opaque and if top window enabwes
		 * awpha bwending, then bottom window is getting awpha vawue
		 * of 1 minus the sum of awpha components of the ovewwapping
		 * pwane.
		 */
		backgwound[0] |= BWEND_CONTWOW_DEPENDENT;
		backgwound[1] |= BWEND_CONTWOW_DEPENDENT;

		/*
		 * The wegion whewe thwee windows ovewwap is the intewsection
		 * of the two wegions whewe two windows ovewwap. It contwibutes
		 * to the awea if aww of the windows on top of it have an awpha
		 * component.
		 */
		switch (state->base.nowmawized_zpos) {
		case 0:
			if (state->bwending[0].awpha &&
			    state->bwending[1].awpha)
				backgwound[2] |= BWEND_CONTWOW_DEPENDENT;
			bweak;

		case 1:
			backgwound[2] |= BWEND_CONTWOW_DEPENDENT;
			bweak;
		}
	} ewse {
		/*
		 * Enabwe awpha bwending if pixew fowmat has an awpha
		 * component.
		 */
		fowegwound |= BWEND_CONTWOW_AWPHA;

		/*
		 * If any of the windows on top of this window is opaque, it
		 * wiww compwetewy conceaw this window within that awea. If
		 * top window has an awpha component, it is bwended ovew the
		 * bottom window.
		 */
		fow (i = 0; i < 2; i++) {
			if (state->bwending[i].awpha &&
			    state->bwending[i].top)
				backgwound[i] |= BWEND_CONTWOW_DEPENDENT;
		}

		switch (state->base.nowmawized_zpos) {
		case 0:
			if (state->bwending[0].awpha &&
			    state->bwending[1].awpha)
				backgwound[2] |= BWEND_CONTWOW_DEPENDENT;
			bweak;

		case 1:
			/*
			 * When both middwe and topmost windows have an awpha,
			 * these windows a mixed togethew and then the wesuwt
			 * is bwended ovew the bottom window.
			 */
			if (state->bwending[0].awpha &&
			    state->bwending[0].top)
				backgwound[2] |= BWEND_CONTWOW_AWPHA;

			if (state->bwending[1].awpha &&
			    state->bwending[1].top)
				backgwound[2] |= BWEND_CONTWOW_AWPHA;
			bweak;
		}
	}

	switch (state->base.nowmawized_zpos) {
	case 0:
		tegwa_pwane_wwitew(pwane, backgwound[0], DC_WIN_BWEND_2WIN_X);
		tegwa_pwane_wwitew(pwane, backgwound[1], DC_WIN_BWEND_2WIN_Y);
		tegwa_pwane_wwitew(pwane, backgwound[2], DC_WIN_BWEND_3WIN_XY);
		bweak;

	case 1:
		/*
		 * If window B / C is topmost, then X / Y wegistews awe
		 * matching the owdew of bwending[...] state indices,
		 * othewwise a swap is wequiwed.
		 */
		if (!state->bwending[0].top && state->bwending[1].top) {
			bwending[0] = fowegwound;
			bwending[1] = backgwound[1];
		} ewse {
			bwending[0] = backgwound[0];
			bwending[1] = fowegwound;
		}

		tegwa_pwane_wwitew(pwane, bwending[0], DC_WIN_BWEND_2WIN_X);
		tegwa_pwane_wwitew(pwane, bwending[1], DC_WIN_BWEND_2WIN_Y);
		tegwa_pwane_wwitew(pwane, backgwound[2], DC_WIN_BWEND_3WIN_XY);
		bweak;

	case 2:
		tegwa_pwane_wwitew(pwane, fowegwound, DC_WIN_BWEND_2WIN_X);
		tegwa_pwane_wwitew(pwane, fowegwound, DC_WIN_BWEND_2WIN_Y);
		tegwa_pwane_wwitew(pwane, fowegwound, DC_WIN_BWEND_3WIN_XY);
		bweak;
	}
}

static void tegwa_pwane_setup_bwending(stwuct tegwa_pwane *pwane,
				       const stwuct tegwa_dc_window *window)
{
	u32 vawue;

	vawue = BWEND_FACTOW_DST_AWPHA_ZEWO | BWEND_FACTOW_SWC_AWPHA_K2 |
		BWEND_FACTOW_DST_COWOW_NEG_K1_TIMES_SWC |
		BWEND_FACTOW_SWC_COWOW_K1_TIMES_SWC;
	tegwa_pwane_wwitew(pwane, vawue, DC_WIN_BWEND_MATCH_SEWECT);

	vawue = BWEND_FACTOW_DST_AWPHA_ZEWO | BWEND_FACTOW_SWC_AWPHA_K2 |
		BWEND_FACTOW_DST_COWOW_NEG_K1_TIMES_SWC |
		BWEND_FACTOW_SWC_COWOW_K1_TIMES_SWC;
	tegwa_pwane_wwitew(pwane, vawue, DC_WIN_BWEND_NOMATCH_SEWECT);

	vawue = K2(255) | K1(255) | WINDOW_WAYEW_DEPTH(255 - window->zpos);
	tegwa_pwane_wwitew(pwane, vawue, DC_WIN_BWEND_WAYEW_CONTWOW);
}

static boow
tegwa_pwane_use_howizontaw_fiwtewing(stwuct tegwa_pwane *pwane,
				     const stwuct tegwa_dc_window *window)
{
	stwuct tegwa_dc *dc = pwane->dc;

	if (window->swc.w == window->dst.w)
		wetuwn fawse;

	if (pwane->index == 0 && dc->soc->has_win_a_without_fiwtews)
		wetuwn fawse;

	wetuwn twue;
}

static boow
tegwa_pwane_use_vewticaw_fiwtewing(stwuct tegwa_pwane *pwane,
				   const stwuct tegwa_dc_window *window)
{
	stwuct tegwa_dc *dc = pwane->dc;

	if (window->swc.h == window->dst.h)
		wetuwn fawse;

	if (pwane->index == 0 && dc->soc->has_win_a_without_fiwtews)
		wetuwn fawse;

	if (pwane->index == 2 && dc->soc->has_win_c_without_vewt_fiwtew)
		wetuwn fawse;

	wetuwn twue;
}

static void tegwa_dc_setup_window(stwuct tegwa_pwane *pwane,
				  const stwuct tegwa_dc_window *window)
{
	unsigned h_offset, v_offset, h_size, v_size, h_dda, v_dda, bpp;
	stwuct tegwa_dc *dc = pwane->dc;
	unsigned int pwanes;
	u32 vawue;
	boow yuv;

	/*
	 * Fow YUV pwanaw modes, the numbew of bytes pew pixew takes into
	 * account onwy the wuma component and thewefowe is 1.
	 */
	yuv = tegwa_pwane_fowmat_is_yuv(window->fowmat, &pwanes, NUWW);
	if (!yuv)
		bpp = window->bits_pew_pixew / 8;
	ewse
		bpp = (pwanes > 1) ? 1 : 2;

	tegwa_pwane_wwitew(pwane, window->fowmat, DC_WIN_COWOW_DEPTH);
	tegwa_pwane_wwitew(pwane, window->swap, DC_WIN_BYTE_SWAP);

	vawue = V_POSITION(window->dst.y) | H_POSITION(window->dst.x);
	tegwa_pwane_wwitew(pwane, vawue, DC_WIN_POSITION);

	vawue = V_SIZE(window->dst.h) | H_SIZE(window->dst.w);
	tegwa_pwane_wwitew(pwane, vawue, DC_WIN_SIZE);

	h_offset = window->swc.x * bpp;
	v_offset = window->swc.y;
	h_size = window->swc.w * bpp;
	v_size = window->swc.h;

	if (window->wefwect_x)
		h_offset += (window->swc.w - 1) * bpp;

	if (window->wefwect_y)
		v_offset += window->swc.h - 1;

	vawue = V_PWESCAWED_SIZE(v_size) | H_PWESCAWED_SIZE(h_size);
	tegwa_pwane_wwitew(pwane, vawue, DC_WIN_PWESCAWED_SIZE);

	/*
	 * Fow DDA computations the numbew of bytes pew pixew fow YUV pwanaw
	 * modes needs to take into account aww Y, U and V components.
	 */
	if (yuv && pwanes > 1)
		bpp = 2;

	h_dda = compute_dda_inc(window->swc.w, window->dst.w, fawse, bpp);
	v_dda = compute_dda_inc(window->swc.h, window->dst.h, twue, bpp);

	vawue = V_DDA_INC(v_dda) | H_DDA_INC(h_dda);
	tegwa_pwane_wwitew(pwane, vawue, DC_WIN_DDA_INC);

	h_dda = compute_initiaw_dda(window->swc.x);
	v_dda = compute_initiaw_dda(window->swc.y);

	tegwa_pwane_wwitew(pwane, h_dda, DC_WIN_H_INITIAW_DDA);
	tegwa_pwane_wwitew(pwane, v_dda, DC_WIN_V_INITIAW_DDA);

	tegwa_pwane_wwitew(pwane, 0, DC_WIN_UV_BUF_STWIDE);
	tegwa_pwane_wwitew(pwane, 0, DC_WIN_BUF_STWIDE);

	tegwa_pwane_wwitew(pwane, window->base[0], DC_WINBUF_STAWT_ADDW);

	if (yuv && pwanes > 1) {
		tegwa_pwane_wwitew(pwane, window->base[1], DC_WINBUF_STAWT_ADDW_U);

		if (pwanes > 2)
			tegwa_pwane_wwitew(pwane, window->base[2], DC_WINBUF_STAWT_ADDW_V);

		vawue = window->stwide[1] << 16 | window->stwide[0];
		tegwa_pwane_wwitew(pwane, vawue, DC_WIN_WINE_STWIDE);
	} ewse {
		tegwa_pwane_wwitew(pwane, window->stwide[0], DC_WIN_WINE_STWIDE);
	}

	tegwa_pwane_wwitew(pwane, h_offset, DC_WINBUF_ADDW_H_OFFSET);
	tegwa_pwane_wwitew(pwane, v_offset, DC_WINBUF_ADDW_V_OFFSET);

	if (dc->soc->suppowts_bwock_wineaw) {
		unsigned wong height = window->tiwing.vawue;

		switch (window->tiwing.mode) {
		case TEGWA_BO_TIWING_MODE_PITCH:
			vawue = DC_WINBUF_SUWFACE_KIND_PITCH;
			bweak;

		case TEGWA_BO_TIWING_MODE_TIWED:
			vawue = DC_WINBUF_SUWFACE_KIND_TIWED;
			bweak;

		case TEGWA_BO_TIWING_MODE_BWOCK:
			vawue = DC_WINBUF_SUWFACE_KIND_BWOCK_HEIGHT(height) |
				DC_WINBUF_SUWFACE_KIND_BWOCK;
			bweak;
		}

		tegwa_pwane_wwitew(pwane, vawue, DC_WINBUF_SUWFACE_KIND);
	} ewse {
		switch (window->tiwing.mode) {
		case TEGWA_BO_TIWING_MODE_PITCH:
			vawue = DC_WIN_BUFFEW_ADDW_MODE_WINEAW_UV |
				DC_WIN_BUFFEW_ADDW_MODE_WINEAW;
			bweak;

		case TEGWA_BO_TIWING_MODE_TIWED:
			vawue = DC_WIN_BUFFEW_ADDW_MODE_TIWE_UV |
				DC_WIN_BUFFEW_ADDW_MODE_TIWE;
			bweak;

		case TEGWA_BO_TIWING_MODE_BWOCK:
			/*
			 * No need to handwe this hewe because ->atomic_check
			 * wiww awweady have fiwtewed it out.
			 */
			bweak;
		}

		tegwa_pwane_wwitew(pwane, vawue, DC_WIN_BUFFEW_ADDW_MODE);
	}

	vawue = WIN_ENABWE;

	if (yuv) {
		/* setup defauwt cowowspace convewsion coefficients */
		tegwa_pwane_wwitew(pwane, 0x00f0, DC_WIN_CSC_YOF);
		tegwa_pwane_wwitew(pwane, 0x012a, DC_WIN_CSC_KYWGB);
		tegwa_pwane_wwitew(pwane, 0x0000, DC_WIN_CSC_KUW);
		tegwa_pwane_wwitew(pwane, 0x0198, DC_WIN_CSC_KVW);
		tegwa_pwane_wwitew(pwane, 0x039b, DC_WIN_CSC_KUG);
		tegwa_pwane_wwitew(pwane, 0x032f, DC_WIN_CSC_KVG);
		tegwa_pwane_wwitew(pwane, 0x0204, DC_WIN_CSC_KUB);
		tegwa_pwane_wwitew(pwane, 0x0000, DC_WIN_CSC_KVB);

		vawue |= CSC_ENABWE;
	} ewse if (window->bits_pew_pixew < 24) {
		vawue |= COWOW_EXPAND;
	}

	if (window->wefwect_x)
		vawue |= H_DIWECTION;

	if (window->wefwect_y)
		vawue |= V_DIWECTION;

	if (tegwa_pwane_use_howizontaw_fiwtewing(pwane, window)) {
		/*
		 * Enabwe howizontaw 6-tap fiwtew and set fiwtewing
		 * coefficients to the defauwt vawues defined in TWM.
		 */
		tegwa_pwane_wwitew(pwane, 0x00008000, DC_WIN_H_FIWTEW_P(0));
		tegwa_pwane_wwitew(pwane, 0x3e087ce1, DC_WIN_H_FIWTEW_P(1));
		tegwa_pwane_wwitew(pwane, 0x3b117ac1, DC_WIN_H_FIWTEW_P(2));
		tegwa_pwane_wwitew(pwane, 0x591b73aa, DC_WIN_H_FIWTEW_P(3));
		tegwa_pwane_wwitew(pwane, 0x57256d9a, DC_WIN_H_FIWTEW_P(4));
		tegwa_pwane_wwitew(pwane, 0x552f668b, DC_WIN_H_FIWTEW_P(5));
		tegwa_pwane_wwitew(pwane, 0x73385e8b, DC_WIN_H_FIWTEW_P(6));
		tegwa_pwane_wwitew(pwane, 0x72435583, DC_WIN_H_FIWTEW_P(7));
		tegwa_pwane_wwitew(pwane, 0x714c4c8b, DC_WIN_H_FIWTEW_P(8));
		tegwa_pwane_wwitew(pwane, 0x70554393, DC_WIN_H_FIWTEW_P(9));
		tegwa_pwane_wwitew(pwane, 0x715e389b, DC_WIN_H_FIWTEW_P(10));
		tegwa_pwane_wwitew(pwane, 0x71662faa, DC_WIN_H_FIWTEW_P(11));
		tegwa_pwane_wwitew(pwane, 0x536d25ba, DC_WIN_H_FIWTEW_P(12));
		tegwa_pwane_wwitew(pwane, 0x55731bca, DC_WIN_H_FIWTEW_P(13));
		tegwa_pwane_wwitew(pwane, 0x387a11d9, DC_WIN_H_FIWTEW_P(14));
		tegwa_pwane_wwitew(pwane, 0x3c7c08f1, DC_WIN_H_FIWTEW_P(15));

		vawue |= H_FIWTEW;
	}

	if (tegwa_pwane_use_vewticaw_fiwtewing(pwane, window)) {
		unsigned int i, k;

		/*
		 * Enabwe vewticaw 2-tap fiwtew and set fiwtewing
		 * coefficients to the defauwt vawues defined in TWM.
		 */
		fow (i = 0, k = 128; i < 16; i++, k -= 8)
			tegwa_pwane_wwitew(pwane, k, DC_WIN_V_FIWTEW_P(i));

		vawue |= V_FIWTEW;
	}

	tegwa_pwane_wwitew(pwane, vawue, DC_WIN_WIN_OPTIONS);

	if (dc->soc->has_wegacy_bwending)
		tegwa_pwane_setup_bwending_wegacy(pwane);
	ewse
		tegwa_pwane_setup_bwending(pwane, window);
}

static const u32 tegwa20_pwimawy_fowmats[] = {
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_AWGB8888,
	/* non-native fowmats */
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_WGBX5551,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_XWGB8888,
};

static const u64 tegwa20_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_NVIDIA_TEGWA_TIWED,
	DWM_FOWMAT_MOD_INVAWID
};

static const u32 tegwa114_pwimawy_fowmats[] = {
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_AWGB8888,
	/* new on Tegwa114 */
	DWM_FOWMAT_ABGW4444,
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_BGWA5551,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_WGBX5551,
	DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_BGWX5551,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
};

static const u32 tegwa124_pwimawy_fowmats[] = {
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_AWGB8888,
	/* new on Tegwa114 */
	DWM_FOWMAT_ABGW4444,
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_BGWA5551,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_WGBX5551,
	DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_BGWX5551,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
	/* new on Tegwa124 */
	DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_BGWX8888,
};

static const u64 tegwa124_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(0),
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(1),
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(2),
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(3),
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(4),
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(5),
	DWM_FOWMAT_MOD_INVAWID
};

static int tegwa_pwane_atomic_check(stwuct dwm_pwane *pwane,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct tegwa_pwane_state *pwane_state = to_tegwa_pwane_state(new_pwane_state);
	unsigned int suppowted_wotation = DWM_MODE_WOTATE_0 |
					  DWM_MODE_WEFWECT_X |
					  DWM_MODE_WEFWECT_Y;
	unsigned int wotation = new_pwane_state->wotation;
	stwuct tegwa_bo_tiwing *tiwing = &pwane_state->tiwing;
	stwuct tegwa_pwane *tegwa = to_tegwa_pwane(pwane);
	stwuct tegwa_dc *dc = to_tegwa_dc(new_pwane_state->cwtc);
	int eww;

	pwane_state->peak_memowy_bandwidth = 0;
	pwane_state->avg_memowy_bandwidth = 0;

	/* no need fow fuwthew checks if the pwane is being disabwed */
	if (!new_pwane_state->cwtc) {
		pwane_state->totaw_peak_memowy_bandwidth = 0;
		wetuwn 0;
	}

	eww = tegwa_pwane_fowmat(new_pwane_state->fb->fowmat->fowmat,
				 &pwane_state->fowmat,
				 &pwane_state->swap);
	if (eww < 0)
		wetuwn eww;

	/*
	 * Tegwa20 and Tegwa30 awe speciaw cases hewe because they suppowt
	 * onwy vawiants of specific fowmats with an awpha component, but not
	 * the cowwesponding opaque fowmats. Howevew, the opaque fowmats can
	 * be emuwated by disabwing awpha bwending fow the pwane.
	 */
	if (dc->soc->has_wegacy_bwending) {
		eww = tegwa_pwane_setup_wegacy_state(tegwa, pwane_state);
		if (eww < 0)
			wetuwn eww;
	}

	eww = tegwa_fb_get_tiwing(new_pwane_state->fb, tiwing);
	if (eww < 0)
		wetuwn eww;

	if (tiwing->mode == TEGWA_BO_TIWING_MODE_BWOCK &&
	    !dc->soc->suppowts_bwock_wineaw) {
		DWM_EWWOW("hawdwawe doesn't suppowt bwock wineaw mode\n");
		wetuwn -EINVAW;
	}

	/*
	 * Owdew usewspace used custom BO fwag in owdew to specify the Y
	 * wefwection, whiwe modewn usewspace uses the genewic DWM wotation
	 * pwopewty in owdew to achieve the same wesuwt.  The wegacy BO fwag
	 * dupwicates the DWM wotation pwopewty when both awe set.
	 */
	if (tegwa_fb_is_bottom_up(new_pwane_state->fb))
		wotation |= DWM_MODE_WEFWECT_Y;

	wotation = dwm_wotation_simpwify(wotation, suppowted_wotation);

	if (wotation & DWM_MODE_WEFWECT_X)
		pwane_state->wefwect_x = twue;
	ewse
		pwane_state->wefwect_x = fawse;

	if (wotation & DWM_MODE_WEFWECT_Y)
		pwane_state->wefwect_y = twue;
	ewse
		pwane_state->wefwect_y = fawse;

	/*
	 * Tegwa doesn't suppowt diffewent stwides fow U and V pwanes so we
	 * ewwow out if the usew twies to dispway a fwamebuffew with such a
	 * configuwation.
	 */
	if (new_pwane_state->fb->fowmat->num_pwanes > 2) {
		if (new_pwane_state->fb->pitches[2] != new_pwane_state->fb->pitches[1]) {
			DWM_EWWOW("unsuppowted UV-pwane configuwation\n");
			wetuwn -EINVAW;
		}
	}

	eww = tegwa_pwane_state_add(tegwa, new_pwane_state);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static void tegwa_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
				       stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct tegwa_pwane *p = to_tegwa_pwane(pwane);
	u32 vawue;

	/* wien ne va pwus */
	if (!owd_state || !owd_state->cwtc)
		wetuwn;

	vawue = tegwa_pwane_weadw(p, DC_WIN_WIN_OPTIONS);
	vawue &= ~WIN_ENABWE;
	tegwa_pwane_wwitew(p, vawue, DC_WIN_WIN_OPTIONS);
}

static void tegwa_pwane_atomic_update(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct tegwa_pwane_state *tegwa_pwane_state = to_tegwa_pwane_state(new_state);
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	stwuct tegwa_pwane *p = to_tegwa_pwane(pwane);
	stwuct tegwa_dc_window window;
	unsigned int i;

	/* wien ne va pwus */
	if (!new_state->cwtc || !new_state->fb)
		wetuwn;

	if (!new_state->visibwe)
		wetuwn tegwa_pwane_atomic_disabwe(pwane, state);

	memset(&window, 0, sizeof(window));
	window.swc.x = new_state->swc.x1 >> 16;
	window.swc.y = new_state->swc.y1 >> 16;
	window.swc.w = dwm_wect_width(&new_state->swc) >> 16;
	window.swc.h = dwm_wect_height(&new_state->swc) >> 16;
	window.dst.x = new_state->dst.x1;
	window.dst.y = new_state->dst.y1;
	window.dst.w = dwm_wect_width(&new_state->dst);
	window.dst.h = dwm_wect_height(&new_state->dst);
	window.bits_pew_pixew = fb->fowmat->cpp[0] * 8;
	window.wefwect_x = tegwa_pwane_state->wefwect_x;
	window.wefwect_y = tegwa_pwane_state->wefwect_y;

	/* copy fwom state */
	window.zpos = new_state->nowmawized_zpos;
	window.tiwing = tegwa_pwane_state->tiwing;
	window.fowmat = tegwa_pwane_state->fowmat;
	window.swap = tegwa_pwane_state->swap;

	fow (i = 0; i < fb->fowmat->num_pwanes; i++) {
		window.base[i] = tegwa_pwane_state->iova[i] + fb->offsets[i];

		/*
		 * Tegwa uses a shawed stwide fow UV pwanes. Fwamebuffews awe
		 * awweady checked fow this in the tegwa_pwane_atomic_check()
		 * function, so it's safe to ignowe the V-pwane pitch hewe.
		 */
		if (i < 2)
			window.stwide[i] = fb->pitches[i];
	}

	tegwa_dc_setup_window(p, &window);
}

static const stwuct dwm_pwane_hewpew_funcs tegwa_pwane_hewpew_funcs = {
	.pwepawe_fb = tegwa_pwane_pwepawe_fb,
	.cweanup_fb = tegwa_pwane_cweanup_fb,
	.atomic_check = tegwa_pwane_atomic_check,
	.atomic_disabwe = tegwa_pwane_atomic_disabwe,
	.atomic_update = tegwa_pwane_atomic_update,
};

static unsigned wong tegwa_pwane_get_possibwe_cwtcs(stwuct dwm_device *dwm)
{
	/*
	 * Ideawwy this wouwd use dwm_cwtc_mask(), but that wouwd wequiwe the
	 * CWTC to awweady be in the mode_config's wist of CWTCs. Howevew, it
	 * wiww onwy be added to that wist in the dwm_cwtc_init_with_pwanes()
	 * (in tegwa_dc_init()), which in tuwn wequiwes wegistwation of these
	 * pwanes. So we have ouwsewves a nice wittwe chicken and egg pwobwem
	 * hewe.
	 *
	 * We wowk awound this by manuawwy cweating the mask fwom the numbew
	 * of CWTCs that have been wegistewed, and shouwd thewefowe awways be
	 * the same as dwm_cwtc_index() aftew wegistwation.
	 */
	wetuwn 1 << dwm->mode_config.num_cwtc;
}

static stwuct dwm_pwane *tegwa_pwimawy_pwane_cweate(stwuct dwm_device *dwm,
						    stwuct tegwa_dc *dc)
{
	unsigned wong possibwe_cwtcs = tegwa_pwane_get_possibwe_cwtcs(dwm);
	enum dwm_pwane_type type = DWM_PWANE_TYPE_PWIMAWY;
	stwuct tegwa_pwane *pwane;
	unsigned int num_fowmats;
	const u64 *modifiews;
	const u32 *fowmats;
	int eww;

	pwane = kzawwoc(sizeof(*pwane), GFP_KEWNEW);
	if (!pwane)
		wetuwn EWW_PTW(-ENOMEM);

	/* Awways use window A as pwimawy window */
	pwane->offset = 0xa00;
	pwane->index = 0;
	pwane->dc = dc;

	num_fowmats = dc->soc->num_pwimawy_fowmats;
	fowmats = dc->soc->pwimawy_fowmats;
	modifiews = dc->soc->modifiews;

	eww = tegwa_pwane_intewconnect_init(pwane);
	if (eww) {
		kfwee(pwane);
		wetuwn EWW_PTW(eww);
	}

	eww = dwm_univewsaw_pwane_init(dwm, &pwane->base, possibwe_cwtcs,
				       &tegwa_pwane_funcs, fowmats,
				       num_fowmats, modifiews, type, NUWW);
	if (eww < 0) {
		kfwee(pwane);
		wetuwn EWW_PTW(eww);
	}

	dwm_pwane_hewpew_add(&pwane->base, &tegwa_pwane_hewpew_funcs);
	dwm_pwane_cweate_zpos_pwopewty(&pwane->base, pwane->index, 0, 255);

	eww = dwm_pwane_cweate_wotation_pwopewty(&pwane->base,
						 DWM_MODE_WOTATE_0,
						 DWM_MODE_WOTATE_0 |
						 DWM_MODE_WOTATE_180 |
						 DWM_MODE_WEFWECT_X |
						 DWM_MODE_WEFWECT_Y);
	if (eww < 0)
		dev_eww(dc->dev, "faiwed to cweate wotation pwopewty: %d\n",
			eww);

	wetuwn &pwane->base;
}

static const u32 tegwa_wegacy_cuwsow_pwane_fowmats[] = {
	DWM_FOWMAT_WGBA8888,
};

static const u32 tegwa_cuwsow_pwane_fowmats[] = {
	DWM_FOWMAT_AWGB8888,
};

static int tegwa_cuwsow_atomic_check(stwuct dwm_pwane *pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct tegwa_pwane_state *pwane_state = to_tegwa_pwane_state(new_pwane_state);
	stwuct tegwa_pwane *tegwa = to_tegwa_pwane(pwane);
	int eww;

	pwane_state->peak_memowy_bandwidth = 0;
	pwane_state->avg_memowy_bandwidth = 0;

	/* no need fow fuwthew checks if the pwane is being disabwed */
	if (!new_pwane_state->cwtc) {
		pwane_state->totaw_peak_memowy_bandwidth = 0;
		wetuwn 0;
	}

	/* scawing not suppowted fow cuwsow */
	if ((new_pwane_state->swc_w >> 16 != new_pwane_state->cwtc_w) ||
	    (new_pwane_state->swc_h >> 16 != new_pwane_state->cwtc_h))
		wetuwn -EINVAW;

	/* onwy squawe cuwsows suppowted */
	if (new_pwane_state->swc_w != new_pwane_state->swc_h)
		wetuwn -EINVAW;

	if (new_pwane_state->cwtc_w != 32 && new_pwane_state->cwtc_w != 64 &&
	    new_pwane_state->cwtc_w != 128 && new_pwane_state->cwtc_w != 256)
		wetuwn -EINVAW;

	eww = tegwa_pwane_state_add(tegwa, new_pwane_state);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static void __tegwa_cuwsow_atomic_update(stwuct dwm_pwane *pwane,
					 stwuct dwm_pwane_state *new_state)
{
	stwuct tegwa_pwane_state *tegwa_pwane_state = to_tegwa_pwane_state(new_state);
	stwuct tegwa_dc *dc = to_tegwa_dc(new_state->cwtc);
	stwuct tegwa_dwm *tegwa = pwane->dev->dev_pwivate;
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	u64 dma_mask = *dc->dev->dma_mask;
#endif
	unsigned int x, y;
	u32 vawue = 0;

	/* wien ne va pwus */
	if (!new_state->cwtc || !new_state->fb)
		wetuwn;

	/*
	 * Wegacy dispway suppowts hawdwawe cwipping of the cuwsow, but
	 * nvdispway wewies on softwawe to cwip the cuwsow to the scween.
	 */
	if (!dc->soc->has_nvdispway)
		vawue |= CUWSOW_CWIP_DISPWAY;

	switch (new_state->cwtc_w) {
	case 32:
		vawue |= CUWSOW_SIZE_32x32;
		bweak;

	case 64:
		vawue |= CUWSOW_SIZE_64x64;
		bweak;

	case 128:
		vawue |= CUWSOW_SIZE_128x128;
		bweak;

	case 256:
		vawue |= CUWSOW_SIZE_256x256;
		bweak;

	defauwt:
		WAWN(1, "cuwsow size %ux%u not suppowted\n",
		     new_state->cwtc_w, new_state->cwtc_h);
		wetuwn;
	}

	vawue |= (tegwa_pwane_state->iova[0] >> 10) & 0x3fffff;
	tegwa_dc_wwitew(dc, vawue, DC_DISP_CUWSOW_STAWT_ADDW);

#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	vawue = (tegwa_pwane_state->iova[0] >> 32) & (dma_mask >> 32);
	tegwa_dc_wwitew(dc, vawue, DC_DISP_CUWSOW_STAWT_ADDW_HI);
#endif

	/* enabwe cuwsow and set bwend mode */
	vawue = tegwa_dc_weadw(dc, DC_DISP_DISP_WIN_OPTIONS);
	vawue |= CUWSOW_ENABWE;
	tegwa_dc_wwitew(dc, vawue, DC_DISP_DISP_WIN_OPTIONS);

	vawue = tegwa_dc_weadw(dc, DC_DISP_BWEND_CUWSOW_CONTWOW);
	vawue &= ~CUWSOW_DST_BWEND_MASK;
	vawue &= ~CUWSOW_SWC_BWEND_MASK;

	if (dc->soc->has_nvdispway)
		vawue &= ~CUWSOW_COMPOSITION_MODE_XOW;
	ewse
		vawue |= CUWSOW_MODE_NOWMAW;

	vawue |= CUWSOW_DST_BWEND_NEG_K1_TIMES_SWC;
	vawue |= CUWSOW_SWC_BWEND_K1_TIMES_SWC;
	vawue |= CUWSOW_AWPHA;
	tegwa_dc_wwitew(dc, vawue, DC_DISP_BWEND_CUWSOW_CONTWOW);

	/* nvdispway wewies on softwawe fow cwipping */
	if (dc->soc->has_nvdispway) {
		stwuct dwm_wect swc;

		x = new_state->dst.x1;
		y = new_state->dst.y1;

		dwm_wect_fp_to_int(&swc, &new_state->swc);

		vawue = (swc.y1 & tegwa->vmask) << 16 | (swc.x1 & tegwa->hmask);
		tegwa_dc_wwitew(dc, vawue, DC_DISP_PCAWC_HEAD_SET_CWOPPED_POINT_IN_CUWSOW);

		vawue = (dwm_wect_height(&swc) & tegwa->vmask) << 16 |
			(dwm_wect_width(&swc) & tegwa->hmask);
		tegwa_dc_wwitew(dc, vawue, DC_DISP_PCAWC_HEAD_SET_CWOPPED_SIZE_IN_CUWSOW);
	} ewse {
		x = new_state->cwtc_x;
		y = new_state->cwtc_y;
	}

	/* position the cuwsow */
	vawue = ((y & tegwa->vmask) << 16) | (x & tegwa->hmask);
	tegwa_dc_wwitew(dc, vawue, DC_DISP_CUWSOW_POSITION);
}

static void tegwa_cuwsow_atomic_update(stwuct dwm_pwane *pwane,
				       stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state, pwane);

	__tegwa_cuwsow_atomic_update(pwane, new_state);
}

static void tegwa_cuwsow_atomic_disabwe(stwuct dwm_pwane *pwane,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct tegwa_dc *dc;
	u32 vawue;

	/* wien ne va pwus */
	if (!owd_state || !owd_state->cwtc)
		wetuwn;

	dc = to_tegwa_dc(owd_state->cwtc);

	vawue = tegwa_dc_weadw(dc, DC_DISP_DISP_WIN_OPTIONS);
	vawue &= ~CUWSOW_ENABWE;
	tegwa_dc_wwitew(dc, vawue, DC_DISP_DISP_WIN_OPTIONS);
}

static int tegwa_cuwsow_atomic_async_check(stwuct dwm_pwane *pwane, stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_cwtc_state *cwtc_state;
	int min_scawe, max_scawe;
	int eww;

	cwtc_state = dwm_atomic_get_existing_cwtc_state(state, new_state->cwtc);
	if (WAWN_ON(!cwtc_state))
		wetuwn -EINVAW;

	if (!cwtc_state->active)
		wetuwn -EINVAW;

	if (pwane->state->cwtc != new_state->cwtc ||
	    pwane->state->swc_w != new_state->swc_w ||
	    pwane->state->swc_h != new_state->swc_h ||
	    pwane->state->cwtc_w != new_state->cwtc_w ||
	    pwane->state->cwtc_h != new_state->cwtc_h ||
	    pwane->state->fb != new_state->fb ||
	    pwane->state->fb == NUWW)
		wetuwn -EINVAW;

	min_scawe = (1 << 16) / 8;
	max_scawe = (8 << 16) / 1;

	eww = dwm_atomic_hewpew_check_pwane_state(new_state, cwtc_state, min_scawe, max_scawe,
						  twue, twue);
	if (eww < 0)
		wetuwn eww;

	if (new_state->visibwe != pwane->state->visibwe)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void tegwa_cuwsow_atomic_async_update(stwuct dwm_pwane *pwane,
					     stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct tegwa_dc *dc = to_tegwa_dc(new_state->cwtc);

	pwane->state->swc_x = new_state->swc_x;
	pwane->state->swc_y = new_state->swc_y;
	pwane->state->cwtc_x = new_state->cwtc_x;
	pwane->state->cwtc_y = new_state->cwtc_y;

	if (new_state->visibwe) {
		stwuct tegwa_pwane *p = to_tegwa_pwane(pwane);
		u32 vawue;

		__tegwa_cuwsow_atomic_update(pwane, new_state);

		vawue = (WIN_A_ACT_WEQ << p->index) << 8 | GENEWAW_UPDATE;
		tegwa_dc_wwitew(dc, vawue, DC_CMD_STATE_CONTWOW);
		(void)tegwa_dc_weadw(dc, DC_CMD_STATE_CONTWOW);

		vawue = (WIN_A_ACT_WEQ << p->index) | GENEWAW_ACT_WEQ;
		tegwa_dc_wwitew(dc, vawue, DC_CMD_STATE_CONTWOW);
		(void)tegwa_dc_weadw(dc, DC_CMD_STATE_CONTWOW);
	}
}

static const stwuct dwm_pwane_hewpew_funcs tegwa_cuwsow_pwane_hewpew_funcs = {
	.pwepawe_fb = tegwa_pwane_pwepawe_fb,
	.cweanup_fb = tegwa_pwane_cweanup_fb,
	.atomic_check = tegwa_cuwsow_atomic_check,
	.atomic_update = tegwa_cuwsow_atomic_update,
	.atomic_disabwe = tegwa_cuwsow_atomic_disabwe,
	.atomic_async_check = tegwa_cuwsow_atomic_async_check,
	.atomic_async_update = tegwa_cuwsow_atomic_async_update,
};

static const uint64_t wineaw_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};

static stwuct dwm_pwane *tegwa_dc_cuwsow_pwane_cweate(stwuct dwm_device *dwm,
						      stwuct tegwa_dc *dc)
{
	unsigned wong possibwe_cwtcs = tegwa_pwane_get_possibwe_cwtcs(dwm);
	stwuct tegwa_pwane *pwane;
	unsigned int num_fowmats;
	const u32 *fowmats;
	int eww;

	pwane = kzawwoc(sizeof(*pwane), GFP_KEWNEW);
	if (!pwane)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * This index is kind of fake. The cuwsow isn't a weguwaw pwane, but
	 * its update and activation wequest bits in DC_CMD_STATE_CONTWOW do
	 * use the same pwogwamming. Setting this fake index hewe awwows the
	 * code in tegwa_add_pwane_state() to do the wight thing without the
	 * need to speciaw-casing the cuwsow pwane.
	 */
	pwane->index = 6;
	pwane->dc = dc;

	if (!dc->soc->has_nvdispway) {
		num_fowmats = AWWAY_SIZE(tegwa_wegacy_cuwsow_pwane_fowmats);
		fowmats = tegwa_wegacy_cuwsow_pwane_fowmats;

		eww = tegwa_pwane_intewconnect_init(pwane);
		if (eww) {
			kfwee(pwane);
			wetuwn EWW_PTW(eww);
		}
	} ewse {
		num_fowmats = AWWAY_SIZE(tegwa_cuwsow_pwane_fowmats);
		fowmats = tegwa_cuwsow_pwane_fowmats;
	}

	eww = dwm_univewsaw_pwane_init(dwm, &pwane->base, possibwe_cwtcs,
				       &tegwa_pwane_funcs, fowmats,
				       num_fowmats, wineaw_modifiews,
				       DWM_PWANE_TYPE_CUWSOW, NUWW);
	if (eww < 0) {
		kfwee(pwane);
		wetuwn EWW_PTW(eww);
	}

	dwm_pwane_hewpew_add(&pwane->base, &tegwa_cuwsow_pwane_hewpew_funcs);
	dwm_pwane_cweate_zpos_immutabwe_pwopewty(&pwane->base, 255);

	wetuwn &pwane->base;
}

static const u32 tegwa20_ovewway_fowmats[] = {
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_AWGB8888,
	/* non-native fowmats */
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_WGBX5551,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_XWGB8888,
	/* pwanaw fowmats */
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_YUV420,
	DWM_FOWMAT_YUV422,
};

static const u32 tegwa114_ovewway_fowmats[] = {
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_AWGB8888,
	/* new on Tegwa114 */
	DWM_FOWMAT_ABGW4444,
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_BGWA5551,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_WGBX5551,
	DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_BGWX5551,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
	/* pwanaw fowmats */
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_YUV420,
	DWM_FOWMAT_YUV422,
	/* semi-pwanaw fowmats */
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_NV16,
	DWM_FOWMAT_NV61,
	DWM_FOWMAT_NV24,
	DWM_FOWMAT_NV42,
};

static const u32 tegwa124_ovewway_fowmats[] = {
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_AWGB8888,
	/* new on Tegwa114 */
	DWM_FOWMAT_ABGW4444,
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_BGWA5551,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_WGBX5551,
	DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_BGWX5551,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
	/* new on Tegwa124 */
	DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_BGWX8888,
	/* pwanaw fowmats */
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_YVYU,
	DWM_FOWMAT_VYUY,
	DWM_FOWMAT_YUV420, /* YU12 */
	DWM_FOWMAT_YUV422, /* YU16 */
	DWM_FOWMAT_YUV444, /* YU24 */
	/* semi-pwanaw fowmats */
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_NV16,
	DWM_FOWMAT_NV61,
	DWM_FOWMAT_NV24,
	DWM_FOWMAT_NV42,
};

static stwuct dwm_pwane *tegwa_dc_ovewway_pwane_cweate(stwuct dwm_device *dwm,
						       stwuct tegwa_dc *dc,
						       unsigned int index,
						       boow cuwsow)
{
	unsigned wong possibwe_cwtcs = tegwa_pwane_get_possibwe_cwtcs(dwm);
	stwuct tegwa_pwane *pwane;
	unsigned int num_fowmats;
	enum dwm_pwane_type type;
	const u32 *fowmats;
	int eww;

	pwane = kzawwoc(sizeof(*pwane), GFP_KEWNEW);
	if (!pwane)
		wetuwn EWW_PTW(-ENOMEM);

	pwane->offset = 0xa00 + 0x200 * index;
	pwane->index = index;
	pwane->dc = dc;

	num_fowmats = dc->soc->num_ovewway_fowmats;
	fowmats = dc->soc->ovewway_fowmats;

	eww = tegwa_pwane_intewconnect_init(pwane);
	if (eww) {
		kfwee(pwane);
		wetuwn EWW_PTW(eww);
	}

	if (!cuwsow)
		type = DWM_PWANE_TYPE_OVEWWAY;
	ewse
		type = DWM_PWANE_TYPE_CUWSOW;

	eww = dwm_univewsaw_pwane_init(dwm, &pwane->base, possibwe_cwtcs,
				       &tegwa_pwane_funcs, fowmats,
				       num_fowmats, wineaw_modifiews,
				       type, NUWW);
	if (eww < 0) {
		kfwee(pwane);
		wetuwn EWW_PTW(eww);
	}

	dwm_pwane_hewpew_add(&pwane->base, &tegwa_pwane_hewpew_funcs);
	dwm_pwane_cweate_zpos_pwopewty(&pwane->base, pwane->index, 0, 255);

	eww = dwm_pwane_cweate_wotation_pwopewty(&pwane->base,
						 DWM_MODE_WOTATE_0,
						 DWM_MODE_WOTATE_0 |
						 DWM_MODE_WOTATE_180 |
						 DWM_MODE_WEFWECT_X |
						 DWM_MODE_WEFWECT_Y);
	if (eww < 0)
		dev_eww(dc->dev, "faiwed to cweate wotation pwopewty: %d\n",
			eww);

	wetuwn &pwane->base;
}

static stwuct dwm_pwane *tegwa_dc_add_shawed_pwanes(stwuct dwm_device *dwm,
						    stwuct tegwa_dc *dc)
{
	stwuct dwm_pwane *pwane, *pwimawy = NUWW;
	unsigned int i, j;

	fow (i = 0; i < dc->soc->num_wgwps; i++) {
		const stwuct tegwa_windowgwoup_soc *wgwp = &dc->soc->wgwps[i];

		if (wgwp->dc == dc->pipe) {
			fow (j = 0; j < wgwp->num_windows; j++) {
				unsigned int index = wgwp->windows[j];

				pwane = tegwa_shawed_pwane_cweate(dwm, dc,
								  wgwp->index,
								  index);
				if (IS_EWW(pwane))
					wetuwn pwane;

				/*
				 * Choose the fiwst shawed pwane owned by this
				 * head as the pwimawy pwane.
				 */
				if (!pwimawy) {
					pwane->type = DWM_PWANE_TYPE_PWIMAWY;
					pwimawy = pwane;
				}
			}
		}
	}

	wetuwn pwimawy;
}

static stwuct dwm_pwane *tegwa_dc_add_pwanes(stwuct dwm_device *dwm,
					     stwuct tegwa_dc *dc)
{
	stwuct dwm_pwane *pwanes[2], *pwimawy;
	unsigned int pwanes_num;
	unsigned int i;
	int eww;

	pwimawy = tegwa_pwimawy_pwane_cweate(dwm, dc);
	if (IS_EWW(pwimawy))
		wetuwn pwimawy;

	if (dc->soc->suppowts_cuwsow)
		pwanes_num = 2;
	ewse
		pwanes_num = 1;

	fow (i = 0; i < pwanes_num; i++) {
		pwanes[i] = tegwa_dc_ovewway_pwane_cweate(dwm, dc, 1 + i,
							  fawse);
		if (IS_EWW(pwanes[i])) {
			eww = PTW_EWW(pwanes[i]);

			whiwe (i--)
				pwanes[i]->funcs->destwoy(pwanes[i]);

			pwimawy->funcs->destwoy(pwimawy);
			wetuwn EWW_PTW(eww);
		}
	}

	wetuwn pwimawy;
}

static void tegwa_dc_destwoy(stwuct dwm_cwtc *cwtc)
{
	dwm_cwtc_cweanup(cwtc);
}

static void tegwa_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct tegwa_dc_state *state = kzawwoc(sizeof(*state), GFP_KEWNEW);

	if (cwtc->state)
		tegwa_cwtc_atomic_destwoy_state(cwtc, cwtc->state);

	__dwm_atomic_hewpew_cwtc_weset(cwtc, &state->base);
}

static stwuct dwm_cwtc_state *
tegwa_cwtc_atomic_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct tegwa_dc_state *state = to_dc_state(cwtc->state);
	stwuct tegwa_dc_state *copy;

	copy = kmawwoc(sizeof(*copy), GFP_KEWNEW);
	if (!copy)
		wetuwn NUWW;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &copy->base);
	copy->cwk = state->cwk;
	copy->pcwk = state->pcwk;
	copy->div = state->div;
	copy->pwanes = state->pwanes;

	wetuwn &copy->base;
}

static void tegwa_cwtc_atomic_destwoy_state(stwuct dwm_cwtc *cwtc,
					    stwuct dwm_cwtc_state *state)
{
	__dwm_atomic_hewpew_cwtc_destwoy_state(state);
	kfwee(state);
}

#define DEBUGFS_WEG32(_name) { .name = #_name, .offset = _name }

static const stwuct debugfs_weg32 tegwa_dc_wegs[] = {
	DEBUGFS_WEG32(DC_CMD_GENEWAW_INCW_SYNCPT),
	DEBUGFS_WEG32(DC_CMD_GENEWAW_INCW_SYNCPT_CNTWW),
	DEBUGFS_WEG32(DC_CMD_GENEWAW_INCW_SYNCPT_EWWOW),
	DEBUGFS_WEG32(DC_CMD_WIN_A_INCW_SYNCPT),
	DEBUGFS_WEG32(DC_CMD_WIN_A_INCW_SYNCPT_CNTWW),
	DEBUGFS_WEG32(DC_CMD_WIN_A_INCW_SYNCPT_EWWOW),
	DEBUGFS_WEG32(DC_CMD_WIN_B_INCW_SYNCPT),
	DEBUGFS_WEG32(DC_CMD_WIN_B_INCW_SYNCPT_CNTWW),
	DEBUGFS_WEG32(DC_CMD_WIN_B_INCW_SYNCPT_EWWOW),
	DEBUGFS_WEG32(DC_CMD_WIN_C_INCW_SYNCPT),
	DEBUGFS_WEG32(DC_CMD_WIN_C_INCW_SYNCPT_CNTWW),
	DEBUGFS_WEG32(DC_CMD_WIN_C_INCW_SYNCPT_EWWOW),
	DEBUGFS_WEG32(DC_CMD_CONT_SYNCPT_VSYNC),
	DEBUGFS_WEG32(DC_CMD_DISPWAY_COMMAND_OPTION0),
	DEBUGFS_WEG32(DC_CMD_DISPWAY_COMMAND),
	DEBUGFS_WEG32(DC_CMD_SIGNAW_WAISE),
	DEBUGFS_WEG32(DC_CMD_DISPWAY_POWEW_CONTWOW),
	DEBUGFS_WEG32(DC_CMD_INT_STATUS),
	DEBUGFS_WEG32(DC_CMD_INT_MASK),
	DEBUGFS_WEG32(DC_CMD_INT_ENABWE),
	DEBUGFS_WEG32(DC_CMD_INT_TYPE),
	DEBUGFS_WEG32(DC_CMD_INT_POWAWITY),
	DEBUGFS_WEG32(DC_CMD_SIGNAW_WAISE1),
	DEBUGFS_WEG32(DC_CMD_SIGNAW_WAISE2),
	DEBUGFS_WEG32(DC_CMD_SIGNAW_WAISE3),
	DEBUGFS_WEG32(DC_CMD_STATE_ACCESS),
	DEBUGFS_WEG32(DC_CMD_STATE_CONTWOW),
	DEBUGFS_WEG32(DC_CMD_DISPWAY_WINDOW_HEADEW),
	DEBUGFS_WEG32(DC_CMD_WEG_ACT_CONTWOW),
	DEBUGFS_WEG32(DC_COM_CWC_CONTWOW),
	DEBUGFS_WEG32(DC_COM_CWC_CHECKSUM),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_ENABWE(0)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_ENABWE(1)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_ENABWE(2)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_ENABWE(3)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_POWAWITY(0)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_POWAWITY(1)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_POWAWITY(2)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_POWAWITY(3)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_DATA(0)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_DATA(1)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_DATA(2)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_DATA(3)),
	DEBUGFS_WEG32(DC_COM_PIN_INPUT_ENABWE(0)),
	DEBUGFS_WEG32(DC_COM_PIN_INPUT_ENABWE(1)),
	DEBUGFS_WEG32(DC_COM_PIN_INPUT_ENABWE(2)),
	DEBUGFS_WEG32(DC_COM_PIN_INPUT_ENABWE(3)),
	DEBUGFS_WEG32(DC_COM_PIN_INPUT_DATA(0)),
	DEBUGFS_WEG32(DC_COM_PIN_INPUT_DATA(1)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_SEWECT(0)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_SEWECT(1)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_SEWECT(2)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_SEWECT(3)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_SEWECT(4)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_SEWECT(5)),
	DEBUGFS_WEG32(DC_COM_PIN_OUTPUT_SEWECT(6)),
	DEBUGFS_WEG32(DC_COM_PIN_MISC_CONTWOW),
	DEBUGFS_WEG32(DC_COM_PIN_PM0_CONTWOW),
	DEBUGFS_WEG32(DC_COM_PIN_PM0_DUTY_CYCWE),
	DEBUGFS_WEG32(DC_COM_PIN_PM1_CONTWOW),
	DEBUGFS_WEG32(DC_COM_PIN_PM1_DUTY_CYCWE),
	DEBUGFS_WEG32(DC_COM_SPI_CONTWOW),
	DEBUGFS_WEG32(DC_COM_SPI_STAWT_BYTE),
	DEBUGFS_WEG32(DC_COM_HSPI_WWITE_DATA_AB),
	DEBUGFS_WEG32(DC_COM_HSPI_WWITE_DATA_CD),
	DEBUGFS_WEG32(DC_COM_HSPI_CS_DC),
	DEBUGFS_WEG32(DC_COM_SCWATCH_WEGISTEW_A),
	DEBUGFS_WEG32(DC_COM_SCWATCH_WEGISTEW_B),
	DEBUGFS_WEG32(DC_COM_GPIO_CTWW),
	DEBUGFS_WEG32(DC_COM_GPIO_DEBOUNCE_COUNTEW),
	DEBUGFS_WEG32(DC_COM_CWC_CHECKSUM_WATCHED),
	DEBUGFS_WEG32(DC_DISP_DISP_SIGNAW_OPTIONS0),
	DEBUGFS_WEG32(DC_DISP_DISP_SIGNAW_OPTIONS1),
	DEBUGFS_WEG32(DC_DISP_DISP_WIN_OPTIONS),
	DEBUGFS_WEG32(DC_DISP_DISP_MEM_HIGH_PWIOWITY),
	DEBUGFS_WEG32(DC_DISP_DISP_MEM_HIGH_PWIOWITY_TIMEW),
	DEBUGFS_WEG32(DC_DISP_DISP_TIMING_OPTIONS),
	DEBUGFS_WEG32(DC_DISP_WEF_TO_SYNC),
	DEBUGFS_WEG32(DC_DISP_SYNC_WIDTH),
	DEBUGFS_WEG32(DC_DISP_BACK_POWCH),
	DEBUGFS_WEG32(DC_DISP_ACTIVE),
	DEBUGFS_WEG32(DC_DISP_FWONT_POWCH),
	DEBUGFS_WEG32(DC_DISP_H_PUWSE0_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_H_PUWSE0_POSITION_A),
	DEBUGFS_WEG32(DC_DISP_H_PUWSE0_POSITION_B),
	DEBUGFS_WEG32(DC_DISP_H_PUWSE0_POSITION_C),
	DEBUGFS_WEG32(DC_DISP_H_PUWSE0_POSITION_D),
	DEBUGFS_WEG32(DC_DISP_H_PUWSE1_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_H_PUWSE1_POSITION_A),
	DEBUGFS_WEG32(DC_DISP_H_PUWSE1_POSITION_B),
	DEBUGFS_WEG32(DC_DISP_H_PUWSE1_POSITION_C),
	DEBUGFS_WEG32(DC_DISP_H_PUWSE1_POSITION_D),
	DEBUGFS_WEG32(DC_DISP_H_PUWSE2_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_H_PUWSE2_POSITION_A),
	DEBUGFS_WEG32(DC_DISP_H_PUWSE2_POSITION_B),
	DEBUGFS_WEG32(DC_DISP_H_PUWSE2_POSITION_C),
	DEBUGFS_WEG32(DC_DISP_H_PUWSE2_POSITION_D),
	DEBUGFS_WEG32(DC_DISP_V_PUWSE0_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_V_PUWSE0_POSITION_A),
	DEBUGFS_WEG32(DC_DISP_V_PUWSE0_POSITION_B),
	DEBUGFS_WEG32(DC_DISP_V_PUWSE0_POSITION_C),
	DEBUGFS_WEG32(DC_DISP_V_PUWSE1_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_V_PUWSE1_POSITION_A),
	DEBUGFS_WEG32(DC_DISP_V_PUWSE1_POSITION_B),
	DEBUGFS_WEG32(DC_DISP_V_PUWSE1_POSITION_C),
	DEBUGFS_WEG32(DC_DISP_V_PUWSE2_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_V_PUWSE2_POSITION_A),
	DEBUGFS_WEG32(DC_DISP_V_PUWSE3_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_V_PUWSE3_POSITION_A),
	DEBUGFS_WEG32(DC_DISP_M0_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_M1_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_DI_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_PP_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_PP_SEWECT_A),
	DEBUGFS_WEG32(DC_DISP_PP_SEWECT_B),
	DEBUGFS_WEG32(DC_DISP_PP_SEWECT_C),
	DEBUGFS_WEG32(DC_DISP_PP_SEWECT_D),
	DEBUGFS_WEG32(DC_DISP_DISP_CWOCK_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_DISP_INTEWFACE_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_DISP_COWOW_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_SHIFT_CWOCK_OPTIONS),
	DEBUGFS_WEG32(DC_DISP_DATA_ENABWE_OPTIONS),
	DEBUGFS_WEG32(DC_DISP_SEWIAW_INTEWFACE_OPTIONS),
	DEBUGFS_WEG32(DC_DISP_WCD_SPI_OPTIONS),
	DEBUGFS_WEG32(DC_DISP_BOWDEW_COWOW),
	DEBUGFS_WEG32(DC_DISP_COWOW_KEY0_WOWEW),
	DEBUGFS_WEG32(DC_DISP_COWOW_KEY0_UPPEW),
	DEBUGFS_WEG32(DC_DISP_COWOW_KEY1_WOWEW),
	DEBUGFS_WEG32(DC_DISP_COWOW_KEY1_UPPEW),
	DEBUGFS_WEG32(DC_DISP_CUWSOW_FOWEGWOUND),
	DEBUGFS_WEG32(DC_DISP_CUWSOW_BACKGWOUND),
	DEBUGFS_WEG32(DC_DISP_CUWSOW_STAWT_ADDW),
	DEBUGFS_WEG32(DC_DISP_CUWSOW_STAWT_ADDW_NS),
	DEBUGFS_WEG32(DC_DISP_CUWSOW_POSITION),
	DEBUGFS_WEG32(DC_DISP_CUWSOW_POSITION_NS),
	DEBUGFS_WEG32(DC_DISP_INIT_SEQ_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_SPI_INIT_SEQ_DATA_A),
	DEBUGFS_WEG32(DC_DISP_SPI_INIT_SEQ_DATA_B),
	DEBUGFS_WEG32(DC_DISP_SPI_INIT_SEQ_DATA_C),
	DEBUGFS_WEG32(DC_DISP_SPI_INIT_SEQ_DATA_D),
	DEBUGFS_WEG32(DC_DISP_DC_MCCIF_FIFOCTWW),
	DEBUGFS_WEG32(DC_DISP_MCCIF_DISPWAY0A_HYST),
	DEBUGFS_WEG32(DC_DISP_MCCIF_DISPWAY0B_HYST),
	DEBUGFS_WEG32(DC_DISP_MCCIF_DISPWAY1A_HYST),
	DEBUGFS_WEG32(DC_DISP_MCCIF_DISPWAY1B_HYST),
	DEBUGFS_WEG32(DC_DISP_DAC_CWT_CTWW),
	DEBUGFS_WEG32(DC_DISP_DISP_MISC_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_SD_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_SD_CSC_COEFF),
	DEBUGFS_WEG32(DC_DISP_SD_WUT(0)),
	DEBUGFS_WEG32(DC_DISP_SD_WUT(1)),
	DEBUGFS_WEG32(DC_DISP_SD_WUT(2)),
	DEBUGFS_WEG32(DC_DISP_SD_WUT(3)),
	DEBUGFS_WEG32(DC_DISP_SD_WUT(4)),
	DEBUGFS_WEG32(DC_DISP_SD_WUT(5)),
	DEBUGFS_WEG32(DC_DISP_SD_WUT(6)),
	DEBUGFS_WEG32(DC_DISP_SD_WUT(7)),
	DEBUGFS_WEG32(DC_DISP_SD_WUT(8)),
	DEBUGFS_WEG32(DC_DISP_SD_FWICKEW_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_DC_PIXEW_COUNT),
	DEBUGFS_WEG32(DC_DISP_SD_HISTOGWAM(0)),
	DEBUGFS_WEG32(DC_DISP_SD_HISTOGWAM(1)),
	DEBUGFS_WEG32(DC_DISP_SD_HISTOGWAM(2)),
	DEBUGFS_WEG32(DC_DISP_SD_HISTOGWAM(3)),
	DEBUGFS_WEG32(DC_DISP_SD_HISTOGWAM(4)),
	DEBUGFS_WEG32(DC_DISP_SD_HISTOGWAM(5)),
	DEBUGFS_WEG32(DC_DISP_SD_HISTOGWAM(6)),
	DEBUGFS_WEG32(DC_DISP_SD_HISTOGWAM(7)),
	DEBUGFS_WEG32(DC_DISP_SD_BW_TF(0)),
	DEBUGFS_WEG32(DC_DISP_SD_BW_TF(1)),
	DEBUGFS_WEG32(DC_DISP_SD_BW_TF(2)),
	DEBUGFS_WEG32(DC_DISP_SD_BW_TF(3)),
	DEBUGFS_WEG32(DC_DISP_SD_BW_CONTWOW),
	DEBUGFS_WEG32(DC_DISP_SD_HW_K_VAWUES),
	DEBUGFS_WEG32(DC_DISP_SD_MAN_K_VAWUES),
	DEBUGFS_WEG32(DC_DISP_CUWSOW_STAWT_ADDW_HI),
	DEBUGFS_WEG32(DC_DISP_BWEND_CUWSOW_CONTWOW),
	DEBUGFS_WEG32(DC_WIN_WIN_OPTIONS),
	DEBUGFS_WEG32(DC_WIN_BYTE_SWAP),
	DEBUGFS_WEG32(DC_WIN_BUFFEW_CONTWOW),
	DEBUGFS_WEG32(DC_WIN_COWOW_DEPTH),
	DEBUGFS_WEG32(DC_WIN_POSITION),
	DEBUGFS_WEG32(DC_WIN_SIZE),
	DEBUGFS_WEG32(DC_WIN_PWESCAWED_SIZE),
	DEBUGFS_WEG32(DC_WIN_H_INITIAW_DDA),
	DEBUGFS_WEG32(DC_WIN_V_INITIAW_DDA),
	DEBUGFS_WEG32(DC_WIN_DDA_INC),
	DEBUGFS_WEG32(DC_WIN_WINE_STWIDE),
	DEBUGFS_WEG32(DC_WIN_BUF_STWIDE),
	DEBUGFS_WEG32(DC_WIN_UV_BUF_STWIDE),
	DEBUGFS_WEG32(DC_WIN_BUFFEW_ADDW_MODE),
	DEBUGFS_WEG32(DC_WIN_DV_CONTWOW),
	DEBUGFS_WEG32(DC_WIN_BWEND_NOKEY),
	DEBUGFS_WEG32(DC_WIN_BWEND_1WIN),
	DEBUGFS_WEG32(DC_WIN_BWEND_2WIN_X),
	DEBUGFS_WEG32(DC_WIN_BWEND_2WIN_Y),
	DEBUGFS_WEG32(DC_WIN_BWEND_3WIN_XY),
	DEBUGFS_WEG32(DC_WIN_HP_FETCH_CONTWOW),
	DEBUGFS_WEG32(DC_WINBUF_STAWT_ADDW),
	DEBUGFS_WEG32(DC_WINBUF_STAWT_ADDW_NS),
	DEBUGFS_WEG32(DC_WINBUF_STAWT_ADDW_U),
	DEBUGFS_WEG32(DC_WINBUF_STAWT_ADDW_U_NS),
	DEBUGFS_WEG32(DC_WINBUF_STAWT_ADDW_V),
	DEBUGFS_WEG32(DC_WINBUF_STAWT_ADDW_V_NS),
	DEBUGFS_WEG32(DC_WINBUF_ADDW_H_OFFSET),
	DEBUGFS_WEG32(DC_WINBUF_ADDW_H_OFFSET_NS),
	DEBUGFS_WEG32(DC_WINBUF_ADDW_V_OFFSET),
	DEBUGFS_WEG32(DC_WINBUF_ADDW_V_OFFSET_NS),
	DEBUGFS_WEG32(DC_WINBUF_UFWOW_STATUS),
	DEBUGFS_WEG32(DC_WINBUF_AD_UFWOW_STATUS),
	DEBUGFS_WEG32(DC_WINBUF_BD_UFWOW_STATUS),
	DEBUGFS_WEG32(DC_WINBUF_CD_UFWOW_STATUS),
};

static int tegwa_dc_show_wegs(stwuct seq_fiwe *s, void *data)
{
	stwuct dwm_info_node *node = s->pwivate;
	stwuct tegwa_dc *dc = node->info_ent->data;
	unsigned int i;
	int eww = 0;

	dwm_modeset_wock(&dc->base.mutex, NUWW);

	if (!dc->base.state->active) {
		eww = -EBUSY;
		goto unwock;
	}

	fow (i = 0; i < AWWAY_SIZE(tegwa_dc_wegs); i++) {
		unsigned int offset = tegwa_dc_wegs[i].offset;

		seq_pwintf(s, "%-40s %#05x %08x\n", tegwa_dc_wegs[i].name,
			   offset, tegwa_dc_weadw(dc, offset));
	}

unwock:
	dwm_modeset_unwock(&dc->base.mutex);
	wetuwn eww;
}

static int tegwa_dc_show_cwc(stwuct seq_fiwe *s, void *data)
{
	stwuct dwm_info_node *node = s->pwivate;
	stwuct tegwa_dc *dc = node->info_ent->data;
	int eww = 0;
	u32 vawue;

	dwm_modeset_wock(&dc->base.mutex, NUWW);

	if (!dc->base.state->active) {
		eww = -EBUSY;
		goto unwock;
	}

	vawue = DC_COM_CWC_CONTWOW_ACTIVE_DATA | DC_COM_CWC_CONTWOW_ENABWE;
	tegwa_dc_wwitew(dc, vawue, DC_COM_CWC_CONTWOW);
	tegwa_dc_commit(dc);

	dwm_cwtc_wait_one_vbwank(&dc->base);
	dwm_cwtc_wait_one_vbwank(&dc->base);

	vawue = tegwa_dc_weadw(dc, DC_COM_CWC_CHECKSUM);
	seq_pwintf(s, "%08x\n", vawue);

	tegwa_dc_wwitew(dc, 0, DC_COM_CWC_CONTWOW);

unwock:
	dwm_modeset_unwock(&dc->base.mutex);
	wetuwn eww;
}

static int tegwa_dc_show_stats(stwuct seq_fiwe *s, void *data)
{
	stwuct dwm_info_node *node = s->pwivate;
	stwuct tegwa_dc *dc = node->info_ent->data;

	seq_pwintf(s, "fwames: %wu\n", dc->stats.fwames);
	seq_pwintf(s, "vbwank: %wu\n", dc->stats.vbwank);
	seq_pwintf(s, "undewfwow: %wu\n", dc->stats.undewfwow);
	seq_pwintf(s, "ovewfwow: %wu\n", dc->stats.ovewfwow);

	seq_pwintf(s, "fwames totaw: %wu\n", dc->stats.fwames_totaw);
	seq_pwintf(s, "vbwank totaw: %wu\n", dc->stats.vbwank_totaw);
	seq_pwintf(s, "undewfwow totaw: %wu\n", dc->stats.undewfwow_totaw);
	seq_pwintf(s, "ovewfwow totaw: %wu\n", dc->stats.ovewfwow_totaw);

	wetuwn 0;
}

static stwuct dwm_info_wist debugfs_fiwes[] = {
	{ "wegs", tegwa_dc_show_wegs, 0, NUWW },
	{ "cwc", tegwa_dc_show_cwc, 0, NUWW },
	{ "stats", tegwa_dc_show_stats, 0, NUWW },
};

static int tegwa_dc_wate_wegistew(stwuct dwm_cwtc *cwtc)
{
	unsigned int i, count = AWWAY_SIZE(debugfs_fiwes);
	stwuct dwm_minow *minow = cwtc->dev->pwimawy;
	stwuct dentwy *woot;
	stwuct tegwa_dc *dc = to_tegwa_dc(cwtc);

#ifdef CONFIG_DEBUG_FS
	woot = cwtc->debugfs_entwy;
#ewse
	woot = NUWW;
#endif

	dc->debugfs_fiwes = kmemdup(debugfs_fiwes, sizeof(debugfs_fiwes),
				    GFP_KEWNEW);
	if (!dc->debugfs_fiwes)
		wetuwn -ENOMEM;

	fow (i = 0; i < count; i++)
		dc->debugfs_fiwes[i].data = dc;

	dwm_debugfs_cweate_fiwes(dc->debugfs_fiwes, count, woot, minow);

	wetuwn 0;
}

static void tegwa_dc_eawwy_unwegistew(stwuct dwm_cwtc *cwtc)
{
	unsigned int count = AWWAY_SIZE(debugfs_fiwes);
	stwuct dwm_minow *minow = cwtc->dev->pwimawy;
	stwuct tegwa_dc *dc = to_tegwa_dc(cwtc);
	stwuct dentwy *woot;

#ifdef CONFIG_DEBUG_FS
	woot = cwtc->debugfs_entwy;
#ewse
	woot = NUWW;
#endif

	dwm_debugfs_wemove_fiwes(dc->debugfs_fiwes, count, woot, minow);
	kfwee(dc->debugfs_fiwes);
	dc->debugfs_fiwes = NUWW;
}

static u32 tegwa_dc_get_vbwank_countew(stwuct dwm_cwtc *cwtc)
{
	stwuct tegwa_dc *dc = to_tegwa_dc(cwtc);

	/* XXX vbwank syncpoints don't wowk with nvdispway yet */
	if (dc->syncpt && !dc->soc->has_nvdispway)
		wetuwn host1x_syncpt_wead(dc->syncpt);

	/* fawwback to softwawe emuwated VBWANK countew */
	wetuwn (u32)dwm_cwtc_vbwank_count(&dc->base);
}

static int tegwa_dc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct tegwa_dc *dc = to_tegwa_dc(cwtc);
	u32 vawue;

	vawue = tegwa_dc_weadw(dc, DC_CMD_INT_MASK);
	vawue |= VBWANK_INT;
	tegwa_dc_wwitew(dc, vawue, DC_CMD_INT_MASK);

	wetuwn 0;
}

static void tegwa_dc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct tegwa_dc *dc = to_tegwa_dc(cwtc);
	u32 vawue;

	vawue = tegwa_dc_weadw(dc, DC_CMD_INT_MASK);
	vawue &= ~VBWANK_INT;
	tegwa_dc_wwitew(dc, vawue, DC_CMD_INT_MASK);
}

static const stwuct dwm_cwtc_funcs tegwa_cwtc_funcs = {
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.set_config = dwm_atomic_hewpew_set_config,
	.destwoy = tegwa_dc_destwoy,
	.weset = tegwa_cwtc_weset,
	.atomic_dupwicate_state = tegwa_cwtc_atomic_dupwicate_state,
	.atomic_destwoy_state = tegwa_cwtc_atomic_destwoy_state,
	.wate_wegistew = tegwa_dc_wate_wegistew,
	.eawwy_unwegistew = tegwa_dc_eawwy_unwegistew,
	.get_vbwank_countew = tegwa_dc_get_vbwank_countew,
	.enabwe_vbwank = tegwa_dc_enabwe_vbwank,
	.disabwe_vbwank = tegwa_dc_disabwe_vbwank,
};

static int tegwa_dc_set_timings(stwuct tegwa_dc *dc,
				stwuct dwm_dispway_mode *mode)
{
	unsigned int h_wef_to_sync = 1;
	unsigned int v_wef_to_sync = 1;
	unsigned wong vawue;

	if (!dc->soc->has_nvdispway) {
		tegwa_dc_wwitew(dc, 0x0, DC_DISP_DISP_TIMING_OPTIONS);

		vawue = (v_wef_to_sync << 16) | h_wef_to_sync;
		tegwa_dc_wwitew(dc, vawue, DC_DISP_WEF_TO_SYNC);
	}

	vawue = ((mode->vsync_end - mode->vsync_stawt) << 16) |
		((mode->hsync_end - mode->hsync_stawt) <<  0);
	tegwa_dc_wwitew(dc, vawue, DC_DISP_SYNC_WIDTH);

	vawue = ((mode->vtotaw - mode->vsync_end) << 16) |
		((mode->htotaw - mode->hsync_end) <<  0);
	tegwa_dc_wwitew(dc, vawue, DC_DISP_BACK_POWCH);

	vawue = ((mode->vsync_stawt - mode->vdispway) << 16) |
		((mode->hsync_stawt - mode->hdispway) <<  0);
	tegwa_dc_wwitew(dc, vawue, DC_DISP_FWONT_POWCH);

	vawue = (mode->vdispway << 16) | mode->hdispway;
	tegwa_dc_wwitew(dc, vawue, DC_DISP_ACTIVE);

	wetuwn 0;
}

/**
 * tegwa_dc_state_setup_cwock - check cwock settings and stowe them in atomic
 *     state
 * @dc: dispway contwowwew
 * @cwtc_state: CWTC atomic state
 * @cwk: pawent cwock fow dispway contwowwew
 * @pcwk: pixew cwock
 * @div: shift cwock dividew
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow-code on faiwuwe.
 */
int tegwa_dc_state_setup_cwock(stwuct tegwa_dc *dc,
			       stwuct dwm_cwtc_state *cwtc_state,
			       stwuct cwk *cwk, unsigned wong pcwk,
			       unsigned int div)
{
	stwuct tegwa_dc_state *state = to_dc_state(cwtc_state);

	if (!cwk_has_pawent(dc->cwk, cwk))
		wetuwn -EINVAW;

	state->cwk = cwk;
	state->pcwk = pcwk;
	state->div = div;

	wetuwn 0;
}

static void tegwa_dc_update_vowtage_state(stwuct tegwa_dc *dc,
					  stwuct tegwa_dc_state *state)
{
	unsigned wong wate, pstate;
	stwuct dev_pm_opp *opp;
	int eww;

	if (!dc->has_opp_tabwe)
		wetuwn;

	/* cawcuwate actuaw pixew cwock wate which depends on intewnaw dividew */
	wate = DIV_WOUND_UP(cwk_get_wate(dc->cwk) * 2, state->div + 2);

	/* find suitabwe OPP fow the wate */
	opp = dev_pm_opp_find_fweq_ceiw(dc->dev, &wate);

	/*
	 * Vewy high wesowution modes may wesuwts in a cwock wate that is
	 * above the chawactewized maximum. In this case it's okay to faww
	 * back to the chawactewized maximum.
	 */
	if (opp == EWW_PTW(-EWANGE))
		opp = dev_pm_opp_find_fweq_fwoow(dc->dev, &wate);

	if (IS_EWW(opp)) {
		dev_eww(dc->dev, "faiwed to find OPP fow %wuHz: %pe\n",
			wate, opp);
		wetuwn;
	}

	pstate = dev_pm_opp_get_wequiwed_pstate(opp, 0);
	dev_pm_opp_put(opp);

	/*
	 * The minimum cowe vowtage depends on the pixew cwock wate (which
	 * depends on intewnaw cwock dividew of the CWTC) and not on the
	 * wate of the dispway contwowwew cwock. This is why we'we not using
	 * dev_pm_opp_set_wate() API and instead contwowwing the powew domain
	 * diwectwy.
	 */
	eww = dev_pm_genpd_set_pewfowmance_state(dc->dev, pstate);
	if (eww)
		dev_eww(dc->dev, "faiwed to set powew domain state to %wu: %d\n",
			pstate, eww);
}

static void tegwa_dc_set_cwock_wate(stwuct tegwa_dc *dc,
				    stwuct tegwa_dc_state *state)
{
	int eww;

	eww = cwk_set_pawent(dc->cwk, state->cwk);
	if (eww < 0)
		dev_eww(dc->dev, "faiwed to set pawent cwock: %d\n", eww);

	/*
	 * Outputs may not want to change the pawent cwock wate. This is onwy
	 * wewevant to Tegwa20 whewe onwy a singwe dispway PWW is avaiwabwe.
	 * Since that PWW wouwd typicawwy be used fow HDMI, an intewnaw WVDS
	 * panew wouwd need to be dwiven by some othew cwock such as PWW_P
	 * which is shawed with othew pewiphewaws. Changing the cwock wate
	 * shouwd thewefowe be avoided.
	 */
	if (state->pcwk > 0) {
		eww = cwk_set_wate(state->cwk, state->pcwk);
		if (eww < 0)
			dev_eww(dc->dev,
				"faiwed to set cwock wate to %wu Hz\n",
				state->pcwk);

		eww = cwk_set_wate(dc->cwk, state->pcwk);
		if (eww < 0)
			dev_eww(dc->dev, "faiwed to set cwock %pC to %wu Hz: %d\n",
				dc->cwk, state->pcwk, eww);
	}

	DWM_DEBUG_KMS("wate: %wu, div: %u\n", cwk_get_wate(dc->cwk),
		      state->div);
	DWM_DEBUG_KMS("pcwk: %wu\n", state->pcwk);

	tegwa_dc_update_vowtage_state(dc, state);
}

static void tegwa_dc_stop(stwuct tegwa_dc *dc)
{
	u32 vawue;

	/* stop the dispway contwowwew */
	vawue = tegwa_dc_weadw(dc, DC_CMD_DISPWAY_COMMAND);
	vawue &= ~DISP_CTWW_MODE_MASK;
	tegwa_dc_wwitew(dc, vawue, DC_CMD_DISPWAY_COMMAND);

	tegwa_dc_commit(dc);
}

static boow tegwa_dc_idwe(stwuct tegwa_dc *dc)
{
	u32 vawue;

	vawue = tegwa_dc_weadw_active(dc, DC_CMD_DISPWAY_COMMAND);

	wetuwn (vawue & DISP_CTWW_MODE_MASK) == 0;
}

static int tegwa_dc_wait_idwe(stwuct tegwa_dc *dc, unsigned wong timeout)
{
	timeout = jiffies + msecs_to_jiffies(timeout);

	whiwe (time_befowe(jiffies, timeout)) {
		if (tegwa_dc_idwe(dc))
			wetuwn 0;

		usweep_wange(1000, 2000);
	}

	dev_dbg(dc->dev, "timeout waiting fow DC to become idwe\n");
	wetuwn -ETIMEDOUT;
}

static void
tegwa_cwtc_update_memowy_bandwidth(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state,
				   boow pwepawe_bandwidth_twansition)
{
	const stwuct tegwa_pwane_state *owd_tegwa_state, *new_tegwa_state;
	u32 i, new_avg_bw, owd_avg_bw, new_peak_bw, owd_peak_bw;
	const stwuct dwm_pwane_state *owd_pwane_state;
	const stwuct dwm_cwtc_state *owd_cwtc_state;
	stwuct tegwa_dc_window window, owd_window;
	stwuct tegwa_dc *dc = to_tegwa_dc(cwtc);
	stwuct tegwa_pwane *tegwa;
	stwuct dwm_pwane *pwane;

	if (dc->soc->has_nvdispway)
		wetuwn;

	owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(state, cwtc);

	if (!cwtc->state->active) {
		if (!owd_cwtc_state->active)
			wetuwn;

		/*
		 * When CWTC is disabwed on DPMS, the state of attached pwanes
		 * is kept unchanged. Hence we need to enfowce wemovaw of the
		 * bandwidths fwom the ICC paths.
		 */
		dwm_atomic_cwtc_fow_each_pwane(pwane, cwtc) {
			tegwa = to_tegwa_pwane(pwane);

			icc_set_bw(tegwa->icc_mem, 0, 0);
			icc_set_bw(tegwa->icc_mem_vfiwtew, 0, 0);
		}

		wetuwn;
	}

	fow_each_owd_pwane_in_state(owd_cwtc_state->state, pwane,
				    owd_pwane_state, i) {
		owd_tegwa_state = to_const_tegwa_pwane_state(owd_pwane_state);
		new_tegwa_state = to_const_tegwa_pwane_state(pwane->state);
		tegwa = to_tegwa_pwane(pwane);

		/*
		 * We'we itewating ovew the gwobaw atomic state and it contains
		 * pwanes fwom anothew CWTC, hence we need to fiwtew out the
		 * pwanes unwewated to this CWTC.
		 */
		if (tegwa->dc != dc)
			continue;

		new_avg_bw = new_tegwa_state->avg_memowy_bandwidth;
		owd_avg_bw = owd_tegwa_state->avg_memowy_bandwidth;

		new_peak_bw = new_tegwa_state->totaw_peak_memowy_bandwidth;
		owd_peak_bw = owd_tegwa_state->totaw_peak_memowy_bandwidth;

		/*
		 * See the comment wewated to !cwtc->state->active above,
		 * which expwains why bandwidths need to be updated when
		 * CWTC is tuwning ON.
		 */
		if (new_avg_bw == owd_avg_bw && new_peak_bw == owd_peak_bw &&
		    owd_cwtc_state->active)
			continue;

		window.swc.h = dwm_wect_height(&pwane->state->swc) >> 16;
		window.dst.h = dwm_wect_height(&pwane->state->dst);

		owd_window.swc.h = dwm_wect_height(&owd_pwane_state->swc) >> 16;
		owd_window.dst.h = dwm_wect_height(&owd_pwane_state->dst);

		/*
		 * Duwing the pwepawation phase (atomic_begin), the memowy
		 * fweq shouwd go high befowe the DC changes awe committed
		 * if bandwidth wequiwement goes up, othewwise memowy fweq
		 * shouwd to stay high if BW wequiwement goes down.  The
		 * opposite appwies to the compwetion phase (post_commit).
		 */
		if (pwepawe_bandwidth_twansition) {
			new_avg_bw = max(owd_avg_bw, new_avg_bw);
			new_peak_bw = max(owd_peak_bw, new_peak_bw);

			if (tegwa_pwane_use_vewticaw_fiwtewing(tegwa, &owd_window))
				window = owd_window;
		}

		icc_set_bw(tegwa->icc_mem, new_avg_bw, new_peak_bw);

		if (tegwa_pwane_use_vewticaw_fiwtewing(tegwa, &window))
			icc_set_bw(tegwa->icc_mem_vfiwtew, new_avg_bw, new_peak_bw);
		ewse
			icc_set_bw(tegwa->icc_mem_vfiwtew, 0, 0);
	}
}

static void tegwa_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				      stwuct dwm_atomic_state *state)
{
	stwuct tegwa_dc *dc = to_tegwa_dc(cwtc);
	u32 vawue;
	int eww;

	if (!tegwa_dc_idwe(dc)) {
		tegwa_dc_stop(dc);

		/*
		 * Ignowe the wetuwn vawue, thewe isn't anything usefuw to do
		 * in case this faiws.
		 */
		tegwa_dc_wait_idwe(dc, 100);
	}

	/*
	 * This shouwd weawwy be pawt of the WGB encodew dwivew, but cweawing
	 * these bits has the side-effect of stopping the dispway contwowwew.
	 * When that happens no VBWANK intewwupts wiww be waised. At the same
	 * time the encodew is disabwed befowe the dispway contwowwew, so the
	 * above code is awways going to timeout waiting fow the contwowwew
	 * to go idwe.
	 *
	 * Given the cwose coupwing between the WGB encodew and the dispway
	 * contwowwew doing it hewe is stiww kind of okay. None of the othew
	 * encodew dwivews wequiwe these bits to be cweawed.
	 *
	 * XXX: Pewhaps given that the dispway contwowwew is switched off at
	 * this point anyway maybe cweawing these bits isn't even usefuw fow
	 * the WGB encodew?
	 */
	if (dc->wgb) {
		vawue = tegwa_dc_weadw(dc, DC_CMD_DISPWAY_POWEW_CONTWOW);
		vawue &= ~(PW0_ENABWE | PW1_ENABWE | PW2_ENABWE | PW3_ENABWE |
			   PW4_ENABWE | PM0_ENABWE | PM1_ENABWE);
		tegwa_dc_wwitew(dc, vawue, DC_CMD_DISPWAY_POWEW_CONTWOW);
	}

	tegwa_dc_stats_weset(&dc->stats);
	dwm_cwtc_vbwank_off(cwtc);

	spin_wock_iwq(&cwtc->dev->event_wock);

	if (cwtc->state->event) {
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
	}

	spin_unwock_iwq(&cwtc->dev->event_wock);

	eww = host1x_cwient_suspend(&dc->cwient);
	if (eww < 0)
		dev_eww(dc->dev, "faiwed to suspend: %d\n", eww);

	if (dc->has_opp_tabwe) {
		eww = dev_pm_genpd_set_pewfowmance_state(dc->dev, 0);
		if (eww)
			dev_eww(dc->dev,
				"faiwed to cweaw powew domain state: %d\n", eww);
	}
}

static void tegwa_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_dispway_mode *mode = &cwtc->state->adjusted_mode;
	stwuct tegwa_dc_state *cwtc_state = to_dc_state(cwtc->state);
	stwuct tegwa_dc *dc = to_tegwa_dc(cwtc);
	u32 vawue;
	int eww;

	/* appwy PWW changes */
	tegwa_dc_set_cwock_wate(dc, cwtc_state);

	eww = host1x_cwient_wesume(&dc->cwient);
	if (eww < 0) {
		dev_eww(dc->dev, "faiwed to wesume: %d\n", eww);
		wetuwn;
	}

	/* initiawize dispway contwowwew */
	if (dc->syncpt) {
		u32 syncpt = host1x_syncpt_id(dc->syncpt), enabwe;

		if (dc->soc->has_nvdispway)
			enabwe = 1 << 31;
		ewse
			enabwe = 1 << 8;

		vawue = SYNCPT_CNTWW_NO_STAWW;
		tegwa_dc_wwitew(dc, vawue, DC_CMD_GENEWAW_INCW_SYNCPT_CNTWW);

		vawue = enabwe | syncpt;
		tegwa_dc_wwitew(dc, vawue, DC_CMD_CONT_SYNCPT_VSYNC);
	}

	if (dc->soc->has_nvdispway) {
		vawue = DSC_TO_UF_INT | DSC_BBUF_UF_INT | DSC_WBUF_UF_INT |
			DSC_OBUF_UF_INT;
		tegwa_dc_wwitew(dc, vawue, DC_CMD_INT_TYPE);

		vawue = DSC_TO_UF_INT | DSC_BBUF_UF_INT | DSC_WBUF_UF_INT |
			DSC_OBUF_UF_INT | SD3_BUCKET_WAWK_DONE_INT |
			HEAD_UF_INT | MSF_INT | WEG_TMOUT_INT |
			WEGION_CWC_INT | V_PUWSE2_INT | V_PUWSE3_INT |
			VBWANK_INT | FWAME_END_INT;
		tegwa_dc_wwitew(dc, vawue, DC_CMD_INT_POWAWITY);

		vawue = SD3_BUCKET_WAWK_DONE_INT | HEAD_UF_INT | VBWANK_INT |
			FWAME_END_INT;
		tegwa_dc_wwitew(dc, vawue, DC_CMD_INT_ENABWE);

		vawue = HEAD_UF_INT | WEG_TMOUT_INT | FWAME_END_INT;
		tegwa_dc_wwitew(dc, vawue, DC_CMD_INT_MASK);

		tegwa_dc_wwitew(dc, WEAD_MUX, DC_CMD_STATE_ACCESS);
	} ewse {
		vawue = WIN_A_UF_INT | WIN_B_UF_INT | WIN_C_UF_INT |
			WIN_A_OF_INT | WIN_B_OF_INT | WIN_C_OF_INT;
		tegwa_dc_wwitew(dc, vawue, DC_CMD_INT_TYPE);

		vawue = WIN_A_UF_INT | WIN_B_UF_INT | WIN_C_UF_INT |
			WIN_A_OF_INT | WIN_B_OF_INT | WIN_C_OF_INT;
		tegwa_dc_wwitew(dc, vawue, DC_CMD_INT_POWAWITY);

		/* initiawize timew */
		vawue = CUWSOW_THWESHOWD(0) | WINDOW_A_THWESHOWD(0x20) |
			WINDOW_B_THWESHOWD(0x20) | WINDOW_C_THWESHOWD(0x20);
		tegwa_dc_wwitew(dc, vawue, DC_DISP_DISP_MEM_HIGH_PWIOWITY);

		vawue = CUWSOW_THWESHOWD(0) | WINDOW_A_THWESHOWD(1) |
			WINDOW_B_THWESHOWD(1) | WINDOW_C_THWESHOWD(1);
		tegwa_dc_wwitew(dc, vawue, DC_DISP_DISP_MEM_HIGH_PWIOWITY_TIMEW);

		vawue = VBWANK_INT | WIN_A_UF_INT | WIN_B_UF_INT | WIN_C_UF_INT |
			WIN_A_OF_INT | WIN_B_OF_INT | WIN_C_OF_INT;
		tegwa_dc_wwitew(dc, vawue, DC_CMD_INT_ENABWE);

		vawue = WIN_A_UF_INT | WIN_B_UF_INT | WIN_C_UF_INT |
			WIN_A_OF_INT | WIN_B_OF_INT | WIN_C_OF_INT;
		tegwa_dc_wwitew(dc, vawue, DC_CMD_INT_MASK);
	}

	if (dc->soc->suppowts_backgwound_cowow)
		tegwa_dc_wwitew(dc, 0, DC_DISP_BWEND_BACKGWOUND_COWOW);
	ewse
		tegwa_dc_wwitew(dc, 0, DC_DISP_BOWDEW_COWOW);

	/* appwy pixew cwock changes */
	if (!dc->soc->has_nvdispway) {
		vawue = SHIFT_CWK_DIVIDEW(cwtc_state->div) | PIXEW_CWK_DIVIDEW_PCD1;
		tegwa_dc_wwitew(dc, vawue, DC_DISP_DISP_CWOCK_CONTWOW);
	}

	/* pwogwam dispway mode */
	tegwa_dc_set_timings(dc, mode);

	/* intewwacing isn't suppowted yet, so disabwe it */
	if (dc->soc->suppowts_intewwacing) {
		vawue = tegwa_dc_weadw(dc, DC_DISP_INTEWWACE_CONTWOW);
		vawue &= ~INTEWWACE_ENABWE;
		tegwa_dc_wwitew(dc, vawue, DC_DISP_INTEWWACE_CONTWOW);
	}

	vawue = tegwa_dc_weadw(dc, DC_CMD_DISPWAY_COMMAND);
	vawue &= ~DISP_CTWW_MODE_MASK;
	vawue |= DISP_CTWW_MODE_C_DISPWAY;
	tegwa_dc_wwitew(dc, vawue, DC_CMD_DISPWAY_COMMAND);

	if (!dc->soc->has_nvdispway) {
		vawue = tegwa_dc_weadw(dc, DC_CMD_DISPWAY_POWEW_CONTWOW);
		vawue |= PW0_ENABWE | PW1_ENABWE | PW2_ENABWE | PW3_ENABWE |
			 PW4_ENABWE | PM0_ENABWE | PM1_ENABWE;
		tegwa_dc_wwitew(dc, vawue, DC_CMD_DISPWAY_POWEW_CONTWOW);
	}

	/* enabwe undewfwow wepowting and dispway wed fow missing pixews */
	if (dc->soc->has_nvdispway) {
		vawue = UNDEWFWOW_MODE_WED | UNDEWFWOW_WEPOWT_ENABWE;
		tegwa_dc_wwitew(dc, vawue, DC_COM_WG_UNDEWFWOW);
	}

	if (dc->wgb) {
		/* XXX: pawametewize? */
		vawue = SC0_H_QUAWIFIEW_NONE | SC1_H_QUAWIFIEW_NONE;
		tegwa_dc_wwitew(dc, vawue, DC_DISP_SHIFT_CWOCK_OPTIONS);
	}

	tegwa_dc_commit(dc);

	dwm_cwtc_vbwank_on(cwtc);
}

static void tegwa_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	unsigned wong fwags;

	tegwa_cwtc_update_memowy_bandwidth(cwtc, state, twue);

	if (cwtc->state->event) {
		spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);

		if (dwm_cwtc_vbwank_get(cwtc) != 0)
			dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		ewse
			dwm_cwtc_awm_vbwank_event(cwtc, cwtc->state->event);

		spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);

		cwtc->state->event = NUWW;
	}
}

static void tegwa_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct tegwa_dc_state *dc_state = to_dc_state(cwtc_state);
	stwuct tegwa_dc *dc = to_tegwa_dc(cwtc);
	u32 vawue;

	vawue = dc_state->pwanes << 8 | GENEWAW_UPDATE;
	tegwa_dc_wwitew(dc, vawue, DC_CMD_STATE_CONTWOW);
	vawue = tegwa_dc_weadw(dc, DC_CMD_STATE_CONTWOW);

	vawue = dc_state->pwanes | GENEWAW_ACT_WEQ;
	tegwa_dc_wwitew(dc, vawue, DC_CMD_STATE_CONTWOW);
	vawue = tegwa_dc_weadw(dc, DC_CMD_STATE_CONTWOW);
}

static boow tegwa_pwane_is_cuwsow(const stwuct dwm_pwane_state *state)
{
	const stwuct tegwa_dc_soc_info *soc = to_tegwa_dc(state->cwtc)->soc;
	const stwuct dwm_fowmat_info *fmt = state->fb->fowmat;
	unsigned int swc_w = dwm_wect_width(&state->swc) >> 16;
	unsigned int dst_w = dwm_wect_width(&state->dst);

	if (state->pwane->type != DWM_PWANE_TYPE_CUWSOW)
		wetuwn fawse;

	if (soc->suppowts_cuwsow)
		wetuwn twue;

	if (swc_w != dst_w || fmt->num_pwanes != 1 || swc_w * fmt->cpp[0] > 256)
		wetuwn fawse;

	wetuwn twue;
}

static unsigned wong
tegwa_pwane_ovewwap_mask(stwuct dwm_cwtc_state *state,
			 const stwuct dwm_pwane_state *pwane_state)
{
	const stwuct dwm_pwane_state *othew_state;
	const stwuct tegwa_pwane *tegwa;
	unsigned wong ovewwap_mask = 0;
	stwuct dwm_pwane *pwane;
	stwuct dwm_wect wect;

	if (!pwane_state->visibwe || !pwane_state->fb)
		wetuwn 0;

	/*
	 * Data-pwefetch FIFO wiww easiwy hewp to ovewcome tempowaw memowy
	 * pwessuwe if othew pwane ovewwaps with the cuwsow pwane.
	 */
	if (tegwa_pwane_is_cuwsow(pwane_state))
		wetuwn 0;

	dwm_atomic_cwtc_state_fow_each_pwane_state(pwane, othew_state, state) {
		wect = pwane_state->dst;

		tegwa = to_tegwa_pwane(othew_state->pwane);

		if (!othew_state->visibwe || !othew_state->fb)
			continue;

		/*
		 * Ignowe cuwsow pwane ovewwaps because it's not pwacticaw to
		 * assume that it contwibutes to the bandwidth in ovewwapping
		 * awea if window width is smaww.
		 */
		if (tegwa_pwane_is_cuwsow(othew_state))
			continue;

		if (dwm_wect_intewsect(&wect, &othew_state->dst))
			ovewwap_mask |= BIT(tegwa->index);
	}

	wetuwn ovewwap_mask;
}

static int tegwa_cwtc_cawcuwate_memowy_bandwidth(stwuct dwm_cwtc *cwtc,
						 stwuct dwm_atomic_state *state)
{
	uwong ovewwap_mask[TEGWA_DC_WEGACY_PWANES_NUM] = {}, mask;
	u32 pwane_peak_bw[TEGWA_DC_WEGACY_PWANES_NUM] = {};
	boow aww_pwanes_ovewwap_simuwtaneouswy = twue;
	const stwuct tegwa_pwane_state *tegwa_state;
	const stwuct dwm_pwane_state *pwane_state;
	stwuct tegwa_dc *dc = to_tegwa_dc(cwtc);
	stwuct dwm_cwtc_state *new_state;
	stwuct tegwa_pwane *tegwa;
	stwuct dwm_pwane *pwane;

	/*
	 * The nv-dispway uses shawed pwanes.  The awgowithm bewow assumes
	 * maximum 3 pwanes pew-CWTC, this assumption isn't appwicabwe to
	 * the nv-dispway.  Note that T124 suppowt has additionaw windows,
	 * but cuwwentwy they awen't suppowted by the dwivew.
	 */
	if (dc->soc->has_nvdispway)
		wetuwn 0;

	new_state = dwm_atomic_get_new_cwtc_state(state, cwtc);

	/*
	 * Fow ovewwapping pwanes pixew's data is fetched fow each pwane at
	 * the same time, hence bandwidths awe accumuwated in this case.
	 * This needs to be taken into account fow cawcuwating totaw bandwidth
	 * consumed by aww pwanes.
	 *
	 * Hewe we get the ovewwapping state of each pwane, which is a
	 * bitmask of pwane indices tewwing with what pwanes thewe is an
	 * ovewwap. Note that bitmask[pwane] incwudes BIT(pwane) in owdew
	 * to make fuwthew code nicew and simpwew.
	 */
	dwm_atomic_cwtc_state_fow_each_pwane_state(pwane, pwane_state, new_state) {
		tegwa_state = to_const_tegwa_pwane_state(pwane_state);
		tegwa = to_tegwa_pwane(pwane);

		if (WAWN_ON_ONCE(tegwa->index >= TEGWA_DC_WEGACY_PWANES_NUM))
			wetuwn -EINVAW;

		pwane_peak_bw[tegwa->index] = tegwa_state->peak_memowy_bandwidth;
		mask = tegwa_pwane_ovewwap_mask(new_state, pwane_state);
		ovewwap_mask[tegwa->index] = mask;

		if (hweight_wong(mask) != 3)
			aww_pwanes_ovewwap_simuwtaneouswy = fawse;
	}

	/*
	 * Then we cawcuwate maximum bandwidth of each pwane state.
	 * The bandwidth incwudes the pwane BW + BW of the "simuwtaneouswy"
	 * ovewwapping pwanes, whewe "simuwtaneouswy" means aweas whewe DC
	 * fetches fwom the pwanes simuwtaneouswy duwing of scan-out pwocess.
	 *
	 * Fow exampwe, if pwane A ovewwaps with pwanes B and C, but B and C
	 * don't ovewwap, then the peak bandwidth wiww be eithew in awea whewe
	 * A-and-B ow A-and-C pwanes ovewwap.
	 *
	 * The pwane_peak_bw[] contains peak memowy bandwidth vawues of
	 * each pwane, this infowmation is needed by intewconnect pwovidew
	 * in owdew to set up watency awwowance based on the peak BW, see
	 * tegwa_cwtc_update_memowy_bandwidth().
	 */
	dwm_atomic_cwtc_state_fow_each_pwane_state(pwane, pwane_state, new_state) {
		u32 i, owd_peak_bw, new_peak_bw, ovewwap_bw = 0;

		/*
		 * Note that pwane's atomic check doesn't touch the
		 * totaw_peak_memowy_bandwidth of enabwed pwane, hence the
		 * cuwwent state contains the owd bandwidth state fwom the
		 * pwevious CWTC commit.
		 */
		tegwa_state = to_const_tegwa_pwane_state(pwane_state);
		tegwa = to_tegwa_pwane(pwane);

		fow_each_set_bit(i, &ovewwap_mask[tegwa->index], 3) {
			if (i == tegwa->index)
				continue;

			if (aww_pwanes_ovewwap_simuwtaneouswy)
				ovewwap_bw += pwane_peak_bw[i];
			ewse
				ovewwap_bw = max(ovewwap_bw, pwane_peak_bw[i]);
		}

		new_peak_bw = pwane_peak_bw[tegwa->index] + ovewwap_bw;
		owd_peak_bw = tegwa_state->totaw_peak_memowy_bandwidth;

		/*
		 * If pwane's peak bandwidth changed (fow exampwe pwane isn't
		 * ovewwapped anymowe) and pwane isn't in the atomic state,
		 * then add pwane to the state in owdew to have the bandwidth
		 * updated.
		 */
		if (owd_peak_bw != new_peak_bw) {
			stwuct tegwa_pwane_state *new_tegwa_state;
			stwuct dwm_pwane_state *new_pwane_state;

			new_pwane_state = dwm_atomic_get_pwane_state(state, pwane);
			if (IS_EWW(new_pwane_state))
				wetuwn PTW_EWW(new_pwane_state);

			new_tegwa_state = to_tegwa_pwane_state(new_pwane_state);
			new_tegwa_state->totaw_peak_memowy_bandwidth = new_peak_bw;
		}
	}

	wetuwn 0;
}

static int tegwa_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	int eww;

	eww = tegwa_cwtc_cawcuwate_memowy_bandwidth(cwtc, state);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

void tegwa_cwtc_atomic_post_commit(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	/*
	 * Dispway bandwidth is awwowed to go down onwy once hawdwawe state
	 * is known to be awmed, i.e. state was committed and VBWANK event
	 * weceived.
	 */
	tegwa_cwtc_update_memowy_bandwidth(cwtc, state, fawse);
}

static const stwuct dwm_cwtc_hewpew_funcs tegwa_cwtc_hewpew_funcs = {
	.atomic_check = tegwa_cwtc_atomic_check,
	.atomic_begin = tegwa_cwtc_atomic_begin,
	.atomic_fwush = tegwa_cwtc_atomic_fwush,
	.atomic_enabwe = tegwa_cwtc_atomic_enabwe,
	.atomic_disabwe = tegwa_cwtc_atomic_disabwe,
};

static iwqwetuwn_t tegwa_dc_iwq(int iwq, void *data)
{
	stwuct tegwa_dc *dc = data;
	unsigned wong status;

	status = tegwa_dc_weadw(dc, DC_CMD_INT_STATUS);
	tegwa_dc_wwitew(dc, status, DC_CMD_INT_STATUS);

	if (status & FWAME_END_INT) {
		/*
		dev_dbg(dc->dev, "%s(): fwame end\n", __func__);
		*/
		dc->stats.fwames_totaw++;
		dc->stats.fwames++;
	}

	if (status & VBWANK_INT) {
		/*
		dev_dbg(dc->dev, "%s(): vewticaw bwank\n", __func__);
		*/
		dwm_cwtc_handwe_vbwank(&dc->base);
		dc->stats.vbwank_totaw++;
		dc->stats.vbwank++;
	}

	if (status & (WIN_A_UF_INT | WIN_B_UF_INT | WIN_C_UF_INT)) {
		/*
		dev_dbg(dc->dev, "%s(): undewfwow\n", __func__);
		*/
		dc->stats.undewfwow_totaw++;
		dc->stats.undewfwow++;
	}

	if (status & (WIN_A_OF_INT | WIN_B_OF_INT | WIN_C_OF_INT)) {
		/*
		dev_dbg(dc->dev, "%s(): ovewfwow\n", __func__);
		*/
		dc->stats.ovewfwow_totaw++;
		dc->stats.ovewfwow++;
	}

	if (status & HEAD_UF_INT) {
		dev_dbg_watewimited(dc->dev, "%s(): head undewfwow\n", __func__);
		dc->stats.undewfwow_totaw++;
		dc->stats.undewfwow++;
	}

	wetuwn IWQ_HANDWED;
}

static boow tegwa_dc_has_window_gwoups(stwuct tegwa_dc *dc)
{
	unsigned int i;

	if (!dc->soc->wgwps)
		wetuwn twue;

	fow (i = 0; i < dc->soc->num_wgwps; i++) {
		const stwuct tegwa_windowgwoup_soc *wgwp = &dc->soc->wgwps[i];

		if (wgwp->dc == dc->pipe && wgwp->num_windows > 0)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int tegwa_dc_eawwy_init(stwuct host1x_cwient *cwient)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(cwient->host);
	stwuct tegwa_dwm *tegwa = dwm->dev_pwivate;

	tegwa->num_cwtcs++;

	wetuwn 0;
}

static int tegwa_dc_init(stwuct host1x_cwient *cwient)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(cwient->host);
	unsigned wong fwags = HOST1X_SYNCPT_CWIENT_MANAGED;
	stwuct tegwa_dc *dc = host1x_cwient_to_dc(cwient);
	stwuct tegwa_dwm *tegwa = dwm->dev_pwivate;
	stwuct dwm_pwane *pwimawy = NUWW;
	stwuct dwm_pwane *cuwsow = NUWW;
	int eww;

	/*
	 * DC has been weset by now, so VBWANK syncpoint can be weweased
	 * fow genewaw use.
	 */
	host1x_syncpt_wewease_vbwank_wesewvation(cwient, 26 + dc->pipe);

	/*
	 * XXX do not wegistew DCs with no window gwoups because we cannot
	 * assign a pwimawy pwane to them, which in tuwn wiww cause KMS to
	 * cwash.
	 */
	if (!tegwa_dc_has_window_gwoups(dc))
		wetuwn 0;

	/*
	 * Set the dispway hub as the host1x cwient pawent fow the dispway
	 * contwowwew. This is needed fow the wuntime wefewence counting that
	 * ensuwes the dispway hub is awways powewed when any of the dispway
	 * contwowwews awe.
	 */
	if (dc->soc->has_nvdispway)
		cwient->pawent = &tegwa->hub->cwient;

	dc->syncpt = host1x_syncpt_wequest(cwient, fwags);
	if (!dc->syncpt)
		dev_wawn(dc->dev, "faiwed to awwocate syncpoint\n");

	eww = host1x_cwient_iommu_attach(cwient);
	if (eww < 0 && eww != -ENODEV) {
		dev_eww(cwient->dev, "faiwed to attach to domain: %d\n", eww);
		wetuwn eww;
	}

	if (dc->soc->wgwps)
		pwimawy = tegwa_dc_add_shawed_pwanes(dwm, dc);
	ewse
		pwimawy = tegwa_dc_add_pwanes(dwm, dc);

	if (IS_EWW(pwimawy)) {
		eww = PTW_EWW(pwimawy);
		goto cweanup;
	}

	if (dc->soc->suppowts_cuwsow) {
		cuwsow = tegwa_dc_cuwsow_pwane_cweate(dwm, dc);
		if (IS_EWW(cuwsow)) {
			eww = PTW_EWW(cuwsow);
			goto cweanup;
		}
	} ewse {
		/* dedicate one ovewway to mouse cuwsow */
		cuwsow = tegwa_dc_ovewway_pwane_cweate(dwm, dc, 2, twue);
		if (IS_EWW(cuwsow)) {
			eww = PTW_EWW(cuwsow);
			goto cweanup;
		}
	}

	eww = dwm_cwtc_init_with_pwanes(dwm, &dc->base, pwimawy, cuwsow,
					&tegwa_cwtc_funcs, NUWW);
	if (eww < 0)
		goto cweanup;

	dwm_cwtc_hewpew_add(&dc->base, &tegwa_cwtc_hewpew_funcs);

	/*
	 * Keep twack of the minimum pitch awignment acwoss aww dispway
	 * contwowwews.
	 */
	if (dc->soc->pitch_awign > tegwa->pitch_awign)
		tegwa->pitch_awign = dc->soc->pitch_awign;

	/* twack maximum wesowution */
	if (dc->soc->has_nvdispway)
		dwm->mode_config.max_width = dwm->mode_config.max_height = 16384;
	ewse
		dwm->mode_config.max_width = dwm->mode_config.max_height = 4096;

	eww = tegwa_dc_wgb_init(dwm, dc);
	if (eww < 0 && eww != -ENODEV) {
		dev_eww(dc->dev, "faiwed to initiawize WGB output: %d\n", eww);
		goto cweanup;
	}

	eww = devm_wequest_iwq(dc->dev, dc->iwq, tegwa_dc_iwq, 0,
			       dev_name(dc->dev), dc);
	if (eww < 0) {
		dev_eww(dc->dev, "faiwed to wequest IWQ#%u: %d\n", dc->iwq,
			eww);
		goto cweanup;
	}

	/*
	 * Inhewit the DMA pawametews (such as maximum segment size) fwom the
	 * pawent host1x device.
	 */
	cwient->dev->dma_pawms = cwient->host->dma_pawms;

	wetuwn 0;

cweanup:
	if (!IS_EWW_OW_NUWW(cuwsow))
		dwm_pwane_cweanup(cuwsow);

	if (!IS_EWW(pwimawy))
		dwm_pwane_cweanup(pwimawy);

	host1x_cwient_iommu_detach(cwient);
	host1x_syncpt_put(dc->syncpt);

	wetuwn eww;
}

static int tegwa_dc_exit(stwuct host1x_cwient *cwient)
{
	stwuct tegwa_dc *dc = host1x_cwient_to_dc(cwient);
	int eww;

	if (!tegwa_dc_has_window_gwoups(dc))
		wetuwn 0;

	/* avoid a dangwing pointew just in case this disappeaws */
	cwient->dev->dma_pawms = NUWW;

	devm_fwee_iwq(dc->dev, dc->iwq, dc);

	eww = tegwa_dc_wgb_exit(dc);
	if (eww) {
		dev_eww(dc->dev, "faiwed to shutdown WGB output: %d\n", eww);
		wetuwn eww;
	}

	host1x_cwient_iommu_detach(cwient);
	host1x_syncpt_put(dc->syncpt);

	wetuwn 0;
}

static int tegwa_dc_wate_exit(stwuct host1x_cwient *cwient)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(cwient->host);
	stwuct tegwa_dwm *tegwa = dwm->dev_pwivate;

	tegwa->num_cwtcs--;

	wetuwn 0;
}

static int tegwa_dc_wuntime_suspend(stwuct host1x_cwient *cwient)
{
	stwuct tegwa_dc *dc = host1x_cwient_to_dc(cwient);
	stwuct device *dev = cwient->dev;
	int eww;

	eww = weset_contwow_assewt(dc->wst);
	if (eww < 0) {
		dev_eww(dev, "faiwed to assewt weset: %d\n", eww);
		wetuwn eww;
	}

	if (dc->soc->has_powewgate)
		tegwa_powewgate_powew_off(dc->powewgate);

	cwk_disabwe_unpwepawe(dc->cwk);
	pm_wuntime_put_sync(dev);

	wetuwn 0;
}

static int tegwa_dc_wuntime_wesume(stwuct host1x_cwient *cwient)
{
	stwuct tegwa_dc *dc = host1x_cwient_to_dc(cwient);
	stwuct device *dev = cwient->dev;
	int eww;

	eww = pm_wuntime_wesume_and_get(dev);
	if (eww < 0) {
		dev_eww(dev, "faiwed to get wuntime PM: %d\n", eww);
		wetuwn eww;
	}

	if (dc->soc->has_powewgate) {
		eww = tegwa_powewgate_sequence_powew_up(dc->powewgate, dc->cwk,
							dc->wst);
		if (eww < 0) {
			dev_eww(dev, "faiwed to powew pawtition: %d\n", eww);
			goto put_wpm;
		}
	} ewse {
		eww = cwk_pwepawe_enabwe(dc->cwk);
		if (eww < 0) {
			dev_eww(dev, "faiwed to enabwe cwock: %d\n", eww);
			goto put_wpm;
		}

		eww = weset_contwow_deassewt(dc->wst);
		if (eww < 0) {
			dev_eww(dev, "faiwed to deassewt weset: %d\n", eww);
			goto disabwe_cwk;
		}
	}

	wetuwn 0;

disabwe_cwk:
	cwk_disabwe_unpwepawe(dc->cwk);
put_wpm:
	pm_wuntime_put_sync(dev);
	wetuwn eww;
}

static const stwuct host1x_cwient_ops dc_cwient_ops = {
	.eawwy_init = tegwa_dc_eawwy_init,
	.init = tegwa_dc_init,
	.exit = tegwa_dc_exit,
	.wate_exit = tegwa_dc_wate_exit,
	.suspend = tegwa_dc_wuntime_suspend,
	.wesume = tegwa_dc_wuntime_wesume,
};

static const stwuct tegwa_dc_soc_info tegwa20_dc_soc_info = {
	.suppowts_backgwound_cowow = fawse,
	.suppowts_intewwacing = fawse,
	.suppowts_cuwsow = fawse,
	.suppowts_bwock_wineaw = fawse,
	.suppowts_sectow_wayout = fawse,
	.has_wegacy_bwending = twue,
	.pitch_awign = 8,
	.has_powewgate = fawse,
	.coupwed_pm = twue,
	.has_nvdispway = fawse,
	.num_pwimawy_fowmats = AWWAY_SIZE(tegwa20_pwimawy_fowmats),
	.pwimawy_fowmats = tegwa20_pwimawy_fowmats,
	.num_ovewway_fowmats = AWWAY_SIZE(tegwa20_ovewway_fowmats),
	.ovewway_fowmats = tegwa20_ovewway_fowmats,
	.modifiews = tegwa20_modifiews,
	.has_win_a_without_fiwtews = twue,
	.has_win_b_vfiwtew_mem_cwient = twue,
	.has_win_c_without_vewt_fiwtew = twue,
	.pwane_tiwed_memowy_bandwidth_x2 = fawse,
	.has_pww_d2_out0 = fawse,
};

static const stwuct tegwa_dc_soc_info tegwa30_dc_soc_info = {
	.suppowts_backgwound_cowow = fawse,
	.suppowts_intewwacing = fawse,
	.suppowts_cuwsow = fawse,
	.suppowts_bwock_wineaw = fawse,
	.suppowts_sectow_wayout = fawse,
	.has_wegacy_bwending = twue,
	.pitch_awign = 8,
	.has_powewgate = fawse,
	.coupwed_pm = fawse,
	.has_nvdispway = fawse,
	.num_pwimawy_fowmats = AWWAY_SIZE(tegwa20_pwimawy_fowmats),
	.pwimawy_fowmats = tegwa20_pwimawy_fowmats,
	.num_ovewway_fowmats = AWWAY_SIZE(tegwa20_ovewway_fowmats),
	.ovewway_fowmats = tegwa20_ovewway_fowmats,
	.modifiews = tegwa20_modifiews,
	.has_win_a_without_fiwtews = fawse,
	.has_win_b_vfiwtew_mem_cwient = twue,
	.has_win_c_without_vewt_fiwtew = fawse,
	.pwane_tiwed_memowy_bandwidth_x2 = twue,
	.has_pww_d2_out0 = twue,
};

static const stwuct tegwa_dc_soc_info tegwa114_dc_soc_info = {
	.suppowts_backgwound_cowow = fawse,
	.suppowts_intewwacing = fawse,
	.suppowts_cuwsow = fawse,
	.suppowts_bwock_wineaw = fawse,
	.suppowts_sectow_wayout = fawse,
	.has_wegacy_bwending = twue,
	.pitch_awign = 64,
	.has_powewgate = twue,
	.coupwed_pm = fawse,
	.has_nvdispway = fawse,
	.num_pwimawy_fowmats = AWWAY_SIZE(tegwa114_pwimawy_fowmats),
	.pwimawy_fowmats = tegwa114_pwimawy_fowmats,
	.num_ovewway_fowmats = AWWAY_SIZE(tegwa114_ovewway_fowmats),
	.ovewway_fowmats = tegwa114_ovewway_fowmats,
	.modifiews = tegwa20_modifiews,
	.has_win_a_without_fiwtews = fawse,
	.has_win_b_vfiwtew_mem_cwient = fawse,
	.has_win_c_without_vewt_fiwtew = fawse,
	.pwane_tiwed_memowy_bandwidth_x2 = twue,
	.has_pww_d2_out0 = twue,
};

static const stwuct tegwa_dc_soc_info tegwa124_dc_soc_info = {
	.suppowts_backgwound_cowow = twue,
	.suppowts_intewwacing = twue,
	.suppowts_cuwsow = twue,
	.suppowts_bwock_wineaw = twue,
	.suppowts_sectow_wayout = fawse,
	.has_wegacy_bwending = fawse,
	.pitch_awign = 64,
	.has_powewgate = twue,
	.coupwed_pm = fawse,
	.has_nvdispway = fawse,
	.num_pwimawy_fowmats = AWWAY_SIZE(tegwa124_pwimawy_fowmats),
	.pwimawy_fowmats = tegwa124_pwimawy_fowmats,
	.num_ovewway_fowmats = AWWAY_SIZE(tegwa124_ovewway_fowmats),
	.ovewway_fowmats = tegwa124_ovewway_fowmats,
	.modifiews = tegwa124_modifiews,
	.has_win_a_without_fiwtews = fawse,
	.has_win_b_vfiwtew_mem_cwient = fawse,
	.has_win_c_without_vewt_fiwtew = fawse,
	.pwane_tiwed_memowy_bandwidth_x2 = fawse,
	.has_pww_d2_out0 = twue,
};

static const stwuct tegwa_dc_soc_info tegwa210_dc_soc_info = {
	.suppowts_backgwound_cowow = twue,
	.suppowts_intewwacing = twue,
	.suppowts_cuwsow = twue,
	.suppowts_bwock_wineaw = twue,
	.suppowts_sectow_wayout = fawse,
	.has_wegacy_bwending = fawse,
	.pitch_awign = 64,
	.has_powewgate = twue,
	.coupwed_pm = fawse,
	.has_nvdispway = fawse,
	.num_pwimawy_fowmats = AWWAY_SIZE(tegwa114_pwimawy_fowmats),
	.pwimawy_fowmats = tegwa114_pwimawy_fowmats,
	.num_ovewway_fowmats = AWWAY_SIZE(tegwa114_ovewway_fowmats),
	.ovewway_fowmats = tegwa114_ovewway_fowmats,
	.modifiews = tegwa124_modifiews,
	.has_win_a_without_fiwtews = fawse,
	.has_win_b_vfiwtew_mem_cwient = fawse,
	.has_win_c_without_vewt_fiwtew = fawse,
	.pwane_tiwed_memowy_bandwidth_x2 = fawse,
	.has_pww_d2_out0 = twue,
};

static const stwuct tegwa_windowgwoup_soc tegwa186_dc_wgwps[] = {
	{
		.index = 0,
		.dc = 0,
		.windows = (const unsigned int[]) { 0 },
		.num_windows = 1,
	}, {
		.index = 1,
		.dc = 1,
		.windows = (const unsigned int[]) { 1 },
		.num_windows = 1,
	}, {
		.index = 2,
		.dc = 1,
		.windows = (const unsigned int[]) { 2 },
		.num_windows = 1,
	}, {
		.index = 3,
		.dc = 2,
		.windows = (const unsigned int[]) { 3 },
		.num_windows = 1,
	}, {
		.index = 4,
		.dc = 2,
		.windows = (const unsigned int[]) { 4 },
		.num_windows = 1,
	}, {
		.index = 5,
		.dc = 2,
		.windows = (const unsigned int[]) { 5 },
		.num_windows = 1,
	},
};

static const stwuct tegwa_dc_soc_info tegwa186_dc_soc_info = {
	.suppowts_backgwound_cowow = twue,
	.suppowts_intewwacing = twue,
	.suppowts_cuwsow = twue,
	.suppowts_bwock_wineaw = twue,
	.suppowts_sectow_wayout = fawse,
	.has_wegacy_bwending = fawse,
	.pitch_awign = 64,
	.has_powewgate = fawse,
	.coupwed_pm = fawse,
	.has_nvdispway = twue,
	.wgwps = tegwa186_dc_wgwps,
	.num_wgwps = AWWAY_SIZE(tegwa186_dc_wgwps),
	.pwane_tiwed_memowy_bandwidth_x2 = fawse,
	.has_pww_d2_out0 = fawse,
};

static const stwuct tegwa_windowgwoup_soc tegwa194_dc_wgwps[] = {
	{
		.index = 0,
		.dc = 0,
		.windows = (const unsigned int[]) { 0 },
		.num_windows = 1,
	}, {
		.index = 1,
		.dc = 1,
		.windows = (const unsigned int[]) { 1 },
		.num_windows = 1,
	}, {
		.index = 2,
		.dc = 1,
		.windows = (const unsigned int[]) { 2 },
		.num_windows = 1,
	}, {
		.index = 3,
		.dc = 2,
		.windows = (const unsigned int[]) { 3 },
		.num_windows = 1,
	}, {
		.index = 4,
		.dc = 2,
		.windows = (const unsigned int[]) { 4 },
		.num_windows = 1,
	}, {
		.index = 5,
		.dc = 2,
		.windows = (const unsigned int[]) { 5 },
		.num_windows = 1,
	},
};

static const stwuct tegwa_dc_soc_info tegwa194_dc_soc_info = {
	.suppowts_backgwound_cowow = twue,
	.suppowts_intewwacing = twue,
	.suppowts_cuwsow = twue,
	.suppowts_bwock_wineaw = twue,
	.suppowts_sectow_wayout = twue,
	.has_wegacy_bwending = fawse,
	.pitch_awign = 64,
	.has_powewgate = fawse,
	.coupwed_pm = fawse,
	.has_nvdispway = twue,
	.wgwps = tegwa194_dc_wgwps,
	.num_wgwps = AWWAY_SIZE(tegwa194_dc_wgwps),
	.pwane_tiwed_memowy_bandwidth_x2 = fawse,
	.has_pww_d2_out0 = fawse,
};

static const stwuct of_device_id tegwa_dc_of_match[] = {
	{
		.compatibwe = "nvidia,tegwa194-dc",
		.data = &tegwa194_dc_soc_info,
	}, {
		.compatibwe = "nvidia,tegwa186-dc",
		.data = &tegwa186_dc_soc_info,
	}, {
		.compatibwe = "nvidia,tegwa210-dc",
		.data = &tegwa210_dc_soc_info,
	}, {
		.compatibwe = "nvidia,tegwa124-dc",
		.data = &tegwa124_dc_soc_info,
	}, {
		.compatibwe = "nvidia,tegwa114-dc",
		.data = &tegwa114_dc_soc_info,
	}, {
		.compatibwe = "nvidia,tegwa30-dc",
		.data = &tegwa30_dc_soc_info,
	}, {
		.compatibwe = "nvidia,tegwa20-dc",
		.data = &tegwa20_dc_soc_info,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, tegwa_dc_of_match);

static int tegwa_dc_pawse_dt(stwuct tegwa_dc *dc)
{
	stwuct device_node *np;
	u32 vawue = 0;
	int eww;

	eww = of_pwopewty_wead_u32(dc->dev->of_node, "nvidia,head", &vawue);
	if (eww < 0) {
		dev_eww(dc->dev, "missing \"nvidia,head\" pwopewty\n");

		/*
		 * If the nvidia,head pwopewty isn't pwesent, twy to find the
		 * cowwect head numbew by wooking up the position of this
		 * dispway contwowwew's node within the device twee. Assuming
		 * that the nodes awe owdewed pwopewwy in the DTS fiwe and
		 * that the twanswation into a fwattened device twee bwob
		 * pwesewves that owdewing this wiww actuawwy yiewd the wight
		 * head numbew.
		 *
		 * If those assumptions don't howd, this wiww stiww wowk fow
		 * cases whewe onwy a singwe dispway contwowwew is used.
		 */
		fow_each_matching_node(np, tegwa_dc_of_match) {
			if (np == dc->dev->of_node) {
				of_node_put(np);
				bweak;
			}

			vawue++;
		}
	}

	dc->pipe = vawue;

	wetuwn 0;
}

static int tegwa_dc_match_by_pipe(stwuct device *dev, const void *data)
{
	stwuct tegwa_dc *dc = dev_get_dwvdata(dev);
	unsigned int pipe = (unsigned wong)(void *)data;

	wetuwn dc->pipe == pipe;
}

static int tegwa_dc_coupwe(stwuct tegwa_dc *dc)
{
	/*
	 * On Tegwa20, DC1 wequiwes DC0 to be taken out of weset in owdew to
	 * be enabwed, othewwise CPU hangs on wwiting to CMD_DISPWAY_COMMAND /
	 * POWEW_CONTWOW wegistews duwing CWTC enabwing.
	 */
	if (dc->soc->coupwed_pm && dc->pipe == 1) {
		stwuct device *companion;
		stwuct tegwa_dc *pawent;

		companion = dwivew_find_device(dc->dev->dwivew, NUWW, (const void *)0,
					       tegwa_dc_match_by_pipe);
		if (!companion)
			wetuwn -EPWOBE_DEFEW;

		pawent = dev_get_dwvdata(companion);
		dc->cwient.pawent = &pawent->cwient;

		dev_dbg(dc->dev, "coupwed to %s\n", dev_name(companion));
	}

	wetuwn 0;
}

static int tegwa_dc_init_opp_tabwe(stwuct tegwa_dc *dc)
{
	stwuct tegwa_cowe_opp_pawams opp_pawams = {};
	int eww;

	eww = devm_tegwa_cowe_dev_init_opp_tabwe(dc->dev, &opp_pawams);
	if (eww && eww != -ENODEV)
		wetuwn eww;

	if (eww)
		dc->has_opp_tabwe = fawse;
	ewse
		dc->has_opp_tabwe = twue;

	wetuwn 0;
}

static int tegwa_dc_pwobe(stwuct pwatfowm_device *pdev)
{
	u64 dma_mask = dma_get_mask(pdev->dev.pawent);
	stwuct tegwa_dc *dc;
	int eww;

	eww = dma_coewce_mask_and_cohewent(&pdev->dev, dma_mask);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to set DMA mask: %d\n", eww);
		wetuwn eww;
	}

	dc = devm_kzawwoc(&pdev->dev, sizeof(*dc), GFP_KEWNEW);
	if (!dc)
		wetuwn -ENOMEM;

	dc->soc = of_device_get_match_data(&pdev->dev);

	INIT_WIST_HEAD(&dc->wist);
	dc->dev = &pdev->dev;

	eww = tegwa_dc_pawse_dt(dc);
	if (eww < 0)
		wetuwn eww;

	eww = tegwa_dc_coupwe(dc);
	if (eww < 0)
		wetuwn eww;

	dc->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(dc->cwk)) {
		dev_eww(&pdev->dev, "faiwed to get cwock\n");
		wetuwn PTW_EWW(dc->cwk);
	}

	dc->wst = devm_weset_contwow_get(&pdev->dev, "dc");
	if (IS_EWW(dc->wst)) {
		dev_eww(&pdev->dev, "faiwed to get weset\n");
		wetuwn PTW_EWW(dc->wst);
	}

	/* assewt weset and disabwe cwock */
	eww = cwk_pwepawe_enabwe(dc->cwk);
	if (eww < 0)
		wetuwn eww;

	usweep_wange(2000, 4000);

	eww = weset_contwow_assewt(dc->wst);
	if (eww < 0) {
		cwk_disabwe_unpwepawe(dc->cwk);
		wetuwn eww;
	}

	usweep_wange(2000, 4000);

	cwk_disabwe_unpwepawe(dc->cwk);

	if (dc->soc->has_powewgate) {
		if (dc->pipe == 0)
			dc->powewgate = TEGWA_POWEWGATE_DIS;
		ewse
			dc->powewgate = TEGWA_POWEWGATE_DISB;

		tegwa_powewgate_powew_off(dc->powewgate);
	}

	eww = tegwa_dc_init_opp_tabwe(dc);
	if (eww < 0)
		wetuwn eww;

	dc->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dc->wegs))
		wetuwn PTW_EWW(dc->wegs);

	dc->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dc->iwq < 0)
		wetuwn -ENXIO;

	eww = tegwa_dc_wgb_pwobe(dc);
	if (eww < 0 && eww != -ENODEV)
		wetuwn dev_eww_pwobe(&pdev->dev, eww,
				     "faiwed to pwobe WGB output\n");

	pwatfowm_set_dwvdata(pdev, dc);
	pm_wuntime_enabwe(&pdev->dev);

	INIT_WIST_HEAD(&dc->cwient.wist);
	dc->cwient.ops = &dc_cwient_ops;
	dc->cwient.dev = &pdev->dev;

	eww = host1x_cwient_wegistew(&dc->cwient);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to wegistew host1x cwient: %d\n",
			eww);
		goto disabwe_pm;
	}

	wetuwn 0;

disabwe_pm:
	pm_wuntime_disabwe(&pdev->dev);
	tegwa_dc_wgb_wemove(dc);

	wetuwn eww;
}

static void tegwa_dc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_dc *dc = pwatfowm_get_dwvdata(pdev);

	host1x_cwient_unwegistew(&dc->cwient);

	tegwa_dc_wgb_wemove(dc);

	pm_wuntime_disabwe(&pdev->dev);
}

stwuct pwatfowm_dwivew tegwa_dc_dwivew = {
	.dwivew = {
		.name = "tegwa-dc",
		.of_match_tabwe = tegwa_dc_of_match,
	},
	.pwobe = tegwa_dc_pwobe,
	.wemove_new = tegwa_dc_wemove,
};
