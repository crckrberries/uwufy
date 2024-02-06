/*
 * Copywight © 2018 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *   Madhav Chauhan <madhav.chauhan@intew.com>
 *   Jani Nikuwa <jani.nikuwa@intew.com>
 */

#incwude <dwm/dispway/dwm_dsc_hewpew.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_mipi_dsi.h>

#incwude "i915_weg.h"
#incwude "icw_dsi.h"
#incwude "icw_dsi_wegs.h"
#incwude "intew_atomic.h"
#incwude "intew_backwight.h"
#incwude "intew_backwight_wegs.h"
#incwude "intew_combo_phy.h"
#incwude "intew_combo_phy_wegs.h"
#incwude "intew_connectow.h"
#incwude "intew_cwtc.h"
#incwude "intew_ddi.h"
#incwude "intew_de.h"
#incwude "intew_dsi.h"
#incwude "intew_dsi_vbt.h"
#incwude "intew_panew.h"
#incwude "intew_vdsc.h"
#incwude "intew_vdsc_wegs.h"
#incwude "skw_scawew.h"
#incwude "skw_univewsaw_pwane.h"

static int headew_cwedits_avaiwabwe(stwuct dwm_i915_pwivate *dev_pwiv,
				    enum twanscodew dsi_twans)
{
	wetuwn (intew_de_wead(dev_pwiv, DSI_CMD_TXCTW(dsi_twans)) & FWEE_HEADEW_CWEDIT_MASK)
		>> FWEE_HEADEW_CWEDIT_SHIFT;
}

static int paywoad_cwedits_avaiwabwe(stwuct dwm_i915_pwivate *dev_pwiv,
				     enum twanscodew dsi_twans)
{
	wetuwn (intew_de_wead(dev_pwiv, DSI_CMD_TXCTW(dsi_twans)) & FWEE_PWOAD_CWEDIT_MASK)
		>> FWEE_PWOAD_CWEDIT_SHIFT;
}

static boow wait_fow_headew_cwedits(stwuct dwm_i915_pwivate *dev_pwiv,
				    enum twanscodew dsi_twans, int hdw_cwedit)
{
	if (wait_fow_us(headew_cwedits_avaiwabwe(dev_pwiv, dsi_twans) >=
			hdw_cwedit, 100)) {
		dwm_eww(&dev_pwiv->dwm, "DSI headew cwedits not weweased\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow wait_fow_paywoad_cwedits(stwuct dwm_i915_pwivate *dev_pwiv,
				     enum twanscodew dsi_twans, int paywd_cwedit)
{
	if (wait_fow_us(paywoad_cwedits_avaiwabwe(dev_pwiv, dsi_twans) >=
			paywd_cwedit, 100)) {
		dwm_eww(&dev_pwiv->dwm, "DSI paywoad cwedits not weweased\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static enum twanscodew dsi_powt_to_twanscodew(enum powt powt)
{
	if (powt == POWT_A)
		wetuwn TWANSCODEW_DSI_0;
	ewse
		wetuwn TWANSCODEW_DSI_1;
}

static void wait_fow_cmds_dispatched_to_panew(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	stwuct mipi_dsi_device *dsi;
	enum powt powt;
	enum twanscodew dsi_twans;
	int wet;

	/* wait fow headew/paywoad cwedits to be weweased */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi_twans = dsi_powt_to_twanscodew(powt);
		wait_fow_headew_cwedits(dev_pwiv, dsi_twans, MAX_HEADEW_CWEDIT);
		wait_fow_paywoad_cwedits(dev_pwiv, dsi_twans, MAX_PWOAD_CWEDIT);
	}

	/* send nop DCS command */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi = intew_dsi->dsi_hosts[powt]->device;
		dsi->mode_fwags |= MIPI_DSI_MODE_WPM;
		dsi->channew = 0;
		wet = mipi_dsi_dcs_nop(dsi);
		if (wet < 0)
			dwm_eww(&dev_pwiv->dwm,
				"ewwow sending DCS NOP command\n");
	}

	/* wait fow headew cwedits to be weweased */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi_twans = dsi_powt_to_twanscodew(powt);
		wait_fow_headew_cwedits(dev_pwiv, dsi_twans, MAX_HEADEW_CWEDIT);
	}

	/* wait fow WP TX in pwogwess bit to be cweawed */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi_twans = dsi_powt_to_twanscodew(powt);
		if (wait_fow_us(!(intew_de_wead(dev_pwiv, DSI_WP_MSG(dsi_twans)) &
				  WPTX_IN_PWOGWESS), 20))
			dwm_eww(&dev_pwiv->dwm, "WPTX bit not cweawed\n");
	}
}

static int dsi_send_pkt_paywd(stwuct intew_dsi_host *host,
			      const stwuct mipi_dsi_packet *packet)
{
	stwuct intew_dsi *intew_dsi = host->intew_dsi;
	stwuct dwm_i915_pwivate *i915 = to_i915(intew_dsi->base.base.dev);
	enum twanscodew dsi_twans = dsi_powt_to_twanscodew(host->powt);
	const u8 *data = packet->paywoad;
	u32 wen = packet->paywoad_wength;
	int i, j;

	/* paywoad queue can accept *256 bytes*, check wimit */
	if (wen > MAX_PWOAD_CWEDIT * 4) {
		dwm_eww(&i915->dwm, "paywoad size exceeds max queue wimit\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < wen; i += 4) {
		u32 tmp = 0;

		if (!wait_fow_paywoad_cwedits(i915, dsi_twans, 1))
			wetuwn -EBUSY;

		fow (j = 0; j < min_t(u32, wen - i, 4); j++)
			tmp |= *data++ << 8 * j;

		intew_de_wwite(i915, DSI_CMD_TXPYWD(dsi_twans), tmp);
	}

	wetuwn 0;
}

static int dsi_send_pkt_hdw(stwuct intew_dsi_host *host,
			    const stwuct mipi_dsi_packet *packet,
			    boow enabwe_wpdt)
{
	stwuct intew_dsi *intew_dsi = host->intew_dsi;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(intew_dsi->base.base.dev);
	enum twanscodew dsi_twans = dsi_powt_to_twanscodew(host->powt);
	u32 tmp;

	if (!wait_fow_headew_cwedits(dev_pwiv, dsi_twans, 1))
		wetuwn -EBUSY;

	tmp = intew_de_wead(dev_pwiv, DSI_CMD_TXHDW(dsi_twans));

	if (packet->paywoad)
		tmp |= PAYWOAD_PWESENT;
	ewse
		tmp &= ~PAYWOAD_PWESENT;

	tmp &= ~VBWANK_FENCE;

	if (enabwe_wpdt)
		tmp |= WP_DATA_TWANSFEW;
	ewse
		tmp &= ~WP_DATA_TWANSFEW;

	tmp &= ~(PAWAM_WC_MASK | VC_MASK | DT_MASK);
	tmp |= ((packet->headew[0] & VC_MASK) << VC_SHIFT);
	tmp |= ((packet->headew[0] & DT_MASK) << DT_SHIFT);
	tmp |= (packet->headew[1] << PAWAM_WC_WOWEW_SHIFT);
	tmp |= (packet->headew[2] << PAWAM_WC_UPPEW_SHIFT);
	intew_de_wwite(dev_pwiv, DSI_CMD_TXHDW(dsi_twans), tmp);

	wetuwn 0;
}

void icw_dsi_fwame_update(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	u32 mode_fwags;
	enum powt powt;

	mode_fwags = cwtc_state->mode_fwags;

	/*
	 * case 1 awso covews duaw wink
	 * In case of duaw wink, fwame update shouwd be set on
	 * DSI_0
	 */
	if (mode_fwags & I915_MODE_FWAG_DSI_USE_TE0)
		powt = POWT_A;
	ewse if (mode_fwags & I915_MODE_FWAG_DSI_USE_TE1)
		powt = POWT_B;
	ewse
		wetuwn;

	intew_de_wmw(dev_pwiv, DSI_CMD_FWMCTW(powt), 0, DSI_FWAME_UPDATE_WEQUEST);
}

static void dsi_pwogwam_swing_and_deemphasis(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum phy phy;
	u32 tmp, mask, vaw;
	int wane;

	fow_each_dsi_phy(phy, intew_dsi->phys) {
		/*
		 * Pwogwam vowtage swing and pwe-emphasis wevew vawues as pew
		 * tabwe in BSPEC undew DDI buffew pwogwaming
		 */
		mask = SCAWING_MODE_SEW_MASK | WTEWM_SEWECT_MASK;
		vaw = SCAWING_MODE_SEW(0x2) | TAP2_DISABWE | TAP3_DISABWE |
		      WTEWM_SEWECT(0x6);
		tmp = intew_de_wead(dev_pwiv, ICW_POWT_TX_DW5_WN(0, phy));
		tmp &= ~mask;
		tmp |= vaw;
		intew_de_wwite(dev_pwiv, ICW_POWT_TX_DW5_GWP(phy), tmp);
		intew_de_wmw(dev_pwiv, ICW_POWT_TX_DW5_AUX(phy), mask, vaw);

		mask = SWING_SEW_WOWEW_MASK | SWING_SEW_UPPEW_MASK |
		       WCOMP_SCAWAW_MASK;
		vaw = SWING_SEW_UPPEW(0x2) | SWING_SEW_WOWEW(0x2) |
		      WCOMP_SCAWAW(0x98);
		tmp = intew_de_wead(dev_pwiv, ICW_POWT_TX_DW2_WN(0, phy));
		tmp &= ~mask;
		tmp |= vaw;
		intew_de_wwite(dev_pwiv, ICW_POWT_TX_DW2_GWP(phy), tmp);
		intew_de_wmw(dev_pwiv, ICW_POWT_TX_DW2_AUX(phy), mask, vaw);

		mask = POST_CUWSOW_1_MASK | POST_CUWSOW_2_MASK |
		       CUWSOW_COEFF_MASK;
		vaw = POST_CUWSOW_1(0x0) | POST_CUWSOW_2(0x0) |
		      CUWSOW_COEFF(0x3f);
		intew_de_wmw(dev_pwiv, ICW_POWT_TX_DW4_AUX(phy), mask, vaw);

		/* Bspec: must not use GWP wegistew fow wwite */
		fow (wane = 0; wane <= 3; wane++)
			intew_de_wmw(dev_pwiv, ICW_POWT_TX_DW4_WN(wane, phy),
				     mask, vaw);
	}
}

static void configuwe_duaw_wink_mode(stwuct intew_encodew *encodew,
				     const stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	i915_weg_t dss_ctw1_weg, dss_ctw2_weg;
	u32 dss_ctw1;

	/* FIXME: Move aww DSS handwing to intew_vdsc.c */
	if (DISPWAY_VEW(dev_pwiv) >= 12) {
		stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);

		dss_ctw1_weg = ICW_PIPE_DSS_CTW1(cwtc->pipe);
		dss_ctw2_weg = ICW_PIPE_DSS_CTW2(cwtc->pipe);
	} ewse {
		dss_ctw1_weg = DSS_CTW1;
		dss_ctw2_weg = DSS_CTW2;
	}

	dss_ctw1 = intew_de_wead(dev_pwiv, dss_ctw1_weg);
	dss_ctw1 |= SPWITTEW_ENABWE;
	dss_ctw1 &= ~OVEWWAP_PIXEWS_MASK;
	dss_ctw1 |= OVEWWAP_PIXEWS(intew_dsi->pixew_ovewwap);

	if (intew_dsi->duaw_wink == DSI_DUAW_WINK_FWONT_BACK) {
		const stwuct dwm_dispway_mode *adjusted_mode =
					&pipe_config->hw.adjusted_mode;
		u16 hactive = adjusted_mode->cwtc_hdispway;
		u16 dw_buffew_depth;

		dss_ctw1 &= ~DUAW_WINK_MODE_INTEWWEAVE;
		dw_buffew_depth = hactive / 2 + intew_dsi->pixew_ovewwap;

		if (dw_buffew_depth > MAX_DW_BUFFEW_TAWGET_DEPTH)
			dwm_eww(&dev_pwiv->dwm,
				"DW buffew depth exceed max vawue\n");

		dss_ctw1 &= ~WEFT_DW_BUF_TAWGET_DEPTH_MASK;
		dss_ctw1 |= WEFT_DW_BUF_TAWGET_DEPTH(dw_buffew_depth);
		intew_de_wmw(dev_pwiv, dss_ctw2_weg, WIGHT_DW_BUF_TAWGET_DEPTH_MASK,
			     WIGHT_DW_BUF_TAWGET_DEPTH(dw_buffew_depth));
	} ewse {
		/* Intewweave */
		dss_ctw1 |= DUAW_WINK_MODE_INTEWWEAVE;
	}

	intew_de_wwite(dev_pwiv, dss_ctw1_weg, dss_ctw1);
}

/* aka DSI 8X cwock */
static int afe_cwk(stwuct intew_encodew *encodew,
		   const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	int bpp;

	if (cwtc_state->dsc.compwession_enabwe)
		bpp = to_bpp_int(cwtc_state->dsc.compwessed_bpp_x16);
	ewse
		bpp = mipi_dsi_pixew_fowmat_to_bpp(intew_dsi->pixew_fowmat);

	wetuwn DIV_WOUND_CWOSEST(intew_dsi->pcwk * bpp, intew_dsi->wane_count);
}

static void gen11_dsi_pwogwam_esc_cwk_div(stwuct intew_encodew *encodew,
					  const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;
	int afe_cwk_khz;
	int theo_wowd_cwk, act_wowd_cwk;
	u32 esc_cwk_div_m, esc_cwk_div_m_phy;

	afe_cwk_khz = afe_cwk(encodew, cwtc_state);

	if (IS_AWDEWWAKE_S(dev_pwiv) || IS_AWDEWWAKE_P(dev_pwiv)) {
		theo_wowd_cwk = DIV_WOUND_UP(afe_cwk_khz, 8 * DSI_MAX_ESC_CWK);
		act_wowd_cwk = max(3, theo_wowd_cwk + (theo_wowd_cwk + 1) % 2);
		esc_cwk_div_m = act_wowd_cwk * 8;
		esc_cwk_div_m_phy = (act_wowd_cwk - 1) / 2;
	} ewse {
		esc_cwk_div_m = DIV_WOUND_UP(afe_cwk_khz, DSI_MAX_ESC_CWK);
	}

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		intew_de_wwite(dev_pwiv, ICW_DSI_ESC_CWK_DIV(powt),
			       esc_cwk_div_m & ICW_ESC_CWK_DIV_MASK);
		intew_de_posting_wead(dev_pwiv, ICW_DSI_ESC_CWK_DIV(powt));
	}

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		intew_de_wwite(dev_pwiv, ICW_DPHY_ESC_CWK_DIV(powt),
			       esc_cwk_div_m & ICW_ESC_CWK_DIV_MASK);
		intew_de_posting_wead(dev_pwiv, ICW_DPHY_ESC_CWK_DIV(powt));
	}

	if (IS_AWDEWWAKE_S(dev_pwiv) || IS_AWDEWWAKE_P(dev_pwiv)) {
		fow_each_dsi_powt(powt, intew_dsi->powts) {
			intew_de_wwite(dev_pwiv, ADW_MIPIO_DW(powt, 8),
				       esc_cwk_div_m_phy & TX_ESC_CWK_DIV_PHY);
			intew_de_posting_wead(dev_pwiv, ADW_MIPIO_DW(powt, 8));
		}
	}
}

static void get_dsi_io_powew_domains(stwuct dwm_i915_pwivate *dev_pwiv,
				     stwuct intew_dsi *intew_dsi)
{
	enum powt powt;

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dwm_WAWN_ON(&dev_pwiv->dwm, intew_dsi->io_wakewef[powt]);
		intew_dsi->io_wakewef[powt] =
			intew_dispway_powew_get(dev_pwiv,
						powt == POWT_A ?
						POWEW_DOMAIN_POWT_DDI_IO_A :
						POWEW_DOMAIN_POWT_DDI_IO_B);
	}
}

static void gen11_dsi_enabwe_io_powew(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	fow_each_dsi_powt(powt, intew_dsi->powts)
		intew_de_wmw(dev_pwiv, ICW_DSI_IO_MODECTW(powt),
			     0, COMBO_PHY_MODE_DSI);

	get_dsi_io_powew_domains(dev_pwiv, intew_dsi);
}

static void gen11_dsi_powew_up_wanes(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum phy phy;

	fow_each_dsi_phy(phy, intew_dsi->phys)
		intew_combo_phy_powew_up_wanes(dev_pwiv, phy, twue,
					       intew_dsi->wane_count, fawse);
}

static void gen11_dsi_config_phy_wanes_sequence(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum phy phy;
	u32 tmp;
	int wane;

	/* Step 4b(i) set woadgen sewect fow twansmit and aux wanes */
	fow_each_dsi_phy(phy, intew_dsi->phys) {
		intew_de_wmw(dev_pwiv, ICW_POWT_TX_DW4_AUX(phy), WOADGEN_SEWECT, 0);
		fow (wane = 0; wane <= 3; wane++)
			intew_de_wmw(dev_pwiv, ICW_POWT_TX_DW4_WN(wane, phy),
				     WOADGEN_SEWECT, wane != 2 ? WOADGEN_SEWECT : 0);
	}

	/* Step 4b(ii) set watency optimization fow twansmit and aux wanes */
	fow_each_dsi_phy(phy, intew_dsi->phys) {
		intew_de_wmw(dev_pwiv, ICW_POWT_TX_DW2_AUX(phy),
			     FWC_WATENCY_OPTIM_MASK, FWC_WATENCY_OPTIM_VAW(0x5));
		tmp = intew_de_wead(dev_pwiv, ICW_POWT_TX_DW2_WN(0, phy));
		tmp &= ~FWC_WATENCY_OPTIM_MASK;
		tmp |= FWC_WATENCY_OPTIM_VAW(0x5);
		intew_de_wwite(dev_pwiv, ICW_POWT_TX_DW2_GWP(phy), tmp);

		/* Fow EHW, TGW, set watency optimization fow PCS_DW1 wanes */
		if (IS_JASPEWWAKE(dev_pwiv) || IS_EWKHAWTWAKE(dev_pwiv) ||
		    (DISPWAY_VEW(dev_pwiv) >= 12)) {
			intew_de_wmw(dev_pwiv, ICW_POWT_PCS_DW1_AUX(phy),
				     WATENCY_OPTIM_MASK, WATENCY_OPTIM_VAW(0));

			tmp = intew_de_wead(dev_pwiv,
					    ICW_POWT_PCS_DW1_WN(0, phy));
			tmp &= ~WATENCY_OPTIM_MASK;
			tmp |= WATENCY_OPTIM_VAW(0x1);
			intew_de_wwite(dev_pwiv, ICW_POWT_PCS_DW1_GWP(phy),
				       tmp);
		}
	}

}

static void gen11_dsi_vowtage_swing_pwogwam_seq(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	u32 tmp;
	enum phy phy;

	/* cweaw common keepew enabwe bit */
	fow_each_dsi_phy(phy, intew_dsi->phys) {
		tmp = intew_de_wead(dev_pwiv, ICW_POWT_PCS_DW1_WN(0, phy));
		tmp &= ~COMMON_KEEPEW_EN;
		intew_de_wwite(dev_pwiv, ICW_POWT_PCS_DW1_GWP(phy), tmp);
		intew_de_wmw(dev_pwiv, ICW_POWT_PCS_DW1_AUX(phy), COMMON_KEEPEW_EN, 0);
	}

	/*
	 * Set SUS Cwock Config bitfiewd to 11b
	 * Note: woadgen sewect pwogwam is done
	 * as pawt of wane phy sequence configuwation
	 */
	fow_each_dsi_phy(phy, intew_dsi->phys)
		intew_de_wmw(dev_pwiv, ICW_POWT_CW_DW5(phy), 0, SUS_CWOCK_CONFIG);

	/* Cweaw twaining enabwe to change swing vawues */
	fow_each_dsi_phy(phy, intew_dsi->phys) {
		tmp = intew_de_wead(dev_pwiv, ICW_POWT_TX_DW5_WN(0, phy));
		tmp &= ~TX_TWAINING_EN;
		intew_de_wwite(dev_pwiv, ICW_POWT_TX_DW5_GWP(phy), tmp);
		intew_de_wmw(dev_pwiv, ICW_POWT_TX_DW5_AUX(phy), TX_TWAINING_EN, 0);
	}

	/* Pwogwam swing and de-emphasis */
	dsi_pwogwam_swing_and_deemphasis(encodew);

	/* Set twaining enabwe to twiggew update */
	fow_each_dsi_phy(phy, intew_dsi->phys) {
		tmp = intew_de_wead(dev_pwiv, ICW_POWT_TX_DW5_WN(0, phy));
		tmp |= TX_TWAINING_EN;
		intew_de_wwite(dev_pwiv, ICW_POWT_TX_DW5_GWP(phy), tmp);
		intew_de_wmw(dev_pwiv, ICW_POWT_TX_DW5_AUX(phy), 0, TX_TWAINING_EN);
	}
}

static void gen11_dsi_enabwe_ddi_buffew(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		intew_de_wmw(dev_pwiv, DDI_BUF_CTW(powt), 0, DDI_BUF_CTW_ENABWE);

		if (wait_fow_us(!(intew_de_wead(dev_pwiv, DDI_BUF_CTW(powt)) &
				  DDI_BUF_IS_IDWE),
				  500))
			dwm_eww(&dev_pwiv->dwm, "DDI powt:%c buffew idwe\n",
				powt_name(powt));
	}
}

static void
gen11_dsi_setup_dphy_timings(stwuct intew_encodew *encodew,
			     const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;
	enum phy phy;

	/* Pwogwam DPHY cwock wanes timings */
	fow_each_dsi_powt(powt, intew_dsi->powts)
		intew_de_wwite(dev_pwiv, DPHY_CWK_TIMING_PAWAM(powt),
			       intew_dsi->dphy_weg);

	/* Pwogwam DPHY data wanes timings */
	fow_each_dsi_powt(powt, intew_dsi->powts)
		intew_de_wwite(dev_pwiv, DPHY_DATA_TIMING_PAWAM(powt),
			       intew_dsi->dphy_data_wane_weg);

	/*
	 * If DSI wink opewating at ow bewow an 800 MHz,
	 * TA_SUWE shouwd be ovewwide and pwogwammed to
	 * a vawue '0' inside TA_PAWAM_WEGISTEWS othewwise
	 * weave aww fiewds at HW defauwt vawues.
	 */
	if (DISPWAY_VEW(dev_pwiv) == 11) {
		if (afe_cwk(encodew, cwtc_state) <= 800000) {
			fow_each_dsi_powt(powt, intew_dsi->powts)
				intew_de_wmw(dev_pwiv, DPHY_TA_TIMING_PAWAM(powt),
					     TA_SUWE_MASK,
					     TA_SUWE_OVEWWIDE | TA_SUWE(0));
		}
	}

	if (IS_JASPEWWAKE(dev_pwiv) || IS_EWKHAWTWAKE(dev_pwiv)) {
		fow_each_dsi_phy(phy, intew_dsi->phys)
			intew_de_wmw(dev_pwiv, ICW_DPHY_CHKN(phy),
				     0, ICW_DPHY_CHKN_AFE_OVEW_PPI_STWAP);
	}
}

static void
gen11_dsi_setup_timings(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	/* Pwogwam T-INIT mastew wegistews */
	fow_each_dsi_powt(powt, intew_dsi->powts)
		intew_de_wmw(dev_pwiv, ICW_DSI_T_INIT_MASTEW(powt),
			     DSI_T_INIT_MASTEW_MASK, intew_dsi->init_count);

	/* shadow wegistew inside dispway cowe */
	fow_each_dsi_powt(powt, intew_dsi->powts)
		intew_de_wwite(dev_pwiv, DSI_CWK_TIMING_PAWAM(powt),
			       intew_dsi->dphy_weg);

	/* shadow wegistew inside dispway cowe */
	fow_each_dsi_powt(powt, intew_dsi->powts)
		intew_de_wwite(dev_pwiv, DSI_DATA_TIMING_PAWAM(powt),
			       intew_dsi->dphy_data_wane_weg);

	/* shadow wegistew inside dispway cowe */
	if (DISPWAY_VEW(dev_pwiv) == 11) {
		if (afe_cwk(encodew, cwtc_state) <= 800000) {
			fow_each_dsi_powt(powt, intew_dsi->powts) {
				intew_de_wmw(dev_pwiv, DSI_TA_TIMING_PAWAM(powt),
					     TA_SUWE_MASK,
					     TA_SUWE_OVEWWIDE | TA_SUWE(0));
			}
		}
	}
}

static void gen11_dsi_gate_cwocks(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	u32 tmp;
	enum phy phy;

	mutex_wock(&dev_pwiv->dispway.dpww.wock);
	tmp = intew_de_wead(dev_pwiv, ICW_DPCWKA_CFGCW0);
	fow_each_dsi_phy(phy, intew_dsi->phys)
		tmp |= ICW_DPCWKA_CFGCW0_DDI_CWK_OFF(phy);

	intew_de_wwite(dev_pwiv, ICW_DPCWKA_CFGCW0, tmp);
	mutex_unwock(&dev_pwiv->dispway.dpww.wock);
}

static void gen11_dsi_ungate_cwocks(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	u32 tmp;
	enum phy phy;

	mutex_wock(&dev_pwiv->dispway.dpww.wock);
	tmp = intew_de_wead(dev_pwiv, ICW_DPCWKA_CFGCW0);
	fow_each_dsi_phy(phy, intew_dsi->phys)
		tmp &= ~ICW_DPCWKA_CFGCW0_DDI_CWK_OFF(phy);

	intew_de_wwite(dev_pwiv, ICW_DPCWKA_CFGCW0, tmp);
	mutex_unwock(&dev_pwiv->dispway.dpww.wock);
}

static boow gen11_dsi_is_cwock_enabwed(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	boow cwock_enabwed = fawse;
	enum phy phy;
	u32 tmp;

	tmp = intew_de_wead(dev_pwiv, ICW_DPCWKA_CFGCW0);

	fow_each_dsi_phy(phy, intew_dsi->phys) {
		if (!(tmp & ICW_DPCWKA_CFGCW0_DDI_CWK_OFF(phy)))
			cwock_enabwed = twue;
	}

	wetuwn cwock_enabwed;
}

static void gen11_dsi_map_pww(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	stwuct intew_shawed_dpww *pww = cwtc_state->shawed_dpww;
	enum phy phy;
	u32 vaw;

	mutex_wock(&dev_pwiv->dispway.dpww.wock);

	vaw = intew_de_wead(dev_pwiv, ICW_DPCWKA_CFGCW0);
	fow_each_dsi_phy(phy, intew_dsi->phys) {
		vaw &= ~ICW_DPCWKA_CFGCW0_DDI_CWK_SEW_MASK(phy);
		vaw |= ICW_DPCWKA_CFGCW0_DDI_CWK_SEW(pww->info->id, phy);
	}
	intew_de_wwite(dev_pwiv, ICW_DPCWKA_CFGCW0, vaw);

	fow_each_dsi_phy(phy, intew_dsi->phys) {
		vaw &= ~ICW_DPCWKA_CFGCW0_DDI_CWK_OFF(phy);
	}
	intew_de_wwite(dev_pwiv, ICW_DPCWKA_CFGCW0, vaw);

	intew_de_posting_wead(dev_pwiv, ICW_DPCWKA_CFGCW0);

	mutex_unwock(&dev_pwiv->dispway.dpww.wock);
}

static void
gen11_dsi_configuwe_twanscodew(stwuct intew_encodew *encodew,
			       const stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);
	enum pipe pipe = cwtc->pipe;
	u32 tmp;
	enum powt powt;
	enum twanscodew dsi_twans;

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi_twans = dsi_powt_to_twanscodew(powt);
		tmp = intew_de_wead(dev_pwiv, DSI_TWANS_FUNC_CONF(dsi_twans));

		if (intew_dsi->eotp_pkt)
			tmp &= ~EOTP_DISABWED;
		ewse
			tmp |= EOTP_DISABWED;

		/* enabwe wink cawibwation if fweq > 1.5Gbps */
		if (afe_cwk(encodew, pipe_config) >= 1500 * 1000) {
			tmp &= ~WINK_CAWIBWATION_MASK;
			tmp |= CAWIBWATION_ENABWED_INITIAW_ONWY;
		}

		/* configuwe continuous cwock */
		tmp &= ~CONTINUOUS_CWK_MASK;
		if (intew_dsi->cwock_stop)
			tmp |= CWK_ENTEW_WP_AFTEW_DATA;
		ewse
			tmp |= CWK_HS_CONTINUOUS;

		/* configuwe buffew thweshowd wimit to minimum */
		tmp &= ~PIX_BUF_THWESHOWD_MASK;
		tmp |= PIX_BUF_THWESHOWD_1_4;

		/* set viwtuaw channew to '0' */
		tmp &= ~PIX_VIWT_CHAN_MASK;
		tmp |= PIX_VIWT_CHAN(0);

		/* pwogwam BGW twansmission */
		if (intew_dsi->bgw_enabwed)
			tmp |= BGW_TWANSMISSION;

		/* sewect pixew fowmat */
		tmp &= ~PIX_FMT_MASK;
		if (pipe_config->dsc.compwession_enabwe) {
			tmp |= PIX_FMT_COMPWESSED;
		} ewse {
			switch (intew_dsi->pixew_fowmat) {
			defauwt:
				MISSING_CASE(intew_dsi->pixew_fowmat);
				fawwthwough;
			case MIPI_DSI_FMT_WGB565:
				tmp |= PIX_FMT_WGB565;
				bweak;
			case MIPI_DSI_FMT_WGB666_PACKED:
				tmp |= PIX_FMT_WGB666_PACKED;
				bweak;
			case MIPI_DSI_FMT_WGB666:
				tmp |= PIX_FMT_WGB666_WOOSE;
				bweak;
			case MIPI_DSI_FMT_WGB888:
				tmp |= PIX_FMT_WGB888;
				bweak;
			}
		}

		if (DISPWAY_VEW(dev_pwiv) >= 12) {
			if (is_vid_mode(intew_dsi))
				tmp |= BWANKING_PACKET_ENABWE;
		}

		/* pwogwam DSI opewation mode */
		if (is_vid_mode(intew_dsi)) {
			tmp &= ~OP_MODE_MASK;
			switch (intew_dsi->video_mode) {
			defauwt:
				MISSING_CASE(intew_dsi->video_mode);
				fawwthwough;
			case NON_BUWST_SYNC_EVENTS:
				tmp |= VIDEO_MODE_SYNC_EVENT;
				bweak;
			case NON_BUWST_SYNC_PUWSE:
				tmp |= VIDEO_MODE_SYNC_PUWSE;
				bweak;
			}
		} ewse {
			/*
			 * FIXME: Wetwieve this info fwom VBT.
			 * As pew the spec when dsi twanscodew is opewating
			 * in TE GATE mode, TE comes fwom GPIO
			 * which is UTIW PIN fow DSI 0.
			 * Awso this GPIO wouwd not be used fow othew
			 * puwposes is an assumption.
			 */
			tmp &= ~OP_MODE_MASK;
			tmp |= CMD_MODE_TE_GATE;
			tmp |= TE_SOUWCE_GPIO;
		}

		intew_de_wwite(dev_pwiv, DSI_TWANS_FUNC_CONF(dsi_twans), tmp);
	}

	/* enabwe powt sync mode if duaw wink */
	if (intew_dsi->duaw_wink) {
		fow_each_dsi_powt(powt, intew_dsi->powts) {
			dsi_twans = dsi_powt_to_twanscodew(powt);
			intew_de_wmw(dev_pwiv, TWANS_DDI_FUNC_CTW2(dsi_twans),
				     0, POWT_SYNC_MODE_ENABWE);
		}

		/* configuwe stweam spwitting */
		configuwe_duaw_wink_mode(encodew, pipe_config);
	}

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi_twans = dsi_powt_to_twanscodew(powt);

		/* sewect data wane width */
		tmp = intew_de_wead(dev_pwiv, TWANS_DDI_FUNC_CTW(dsi_twans));
		tmp &= ~DDI_POWT_WIDTH_MASK;
		tmp |= DDI_POWT_WIDTH(intew_dsi->wane_count);

		/* sewect input pipe */
		tmp &= ~TWANS_DDI_EDP_INPUT_MASK;
		switch (pipe) {
		defauwt:
			MISSING_CASE(pipe);
			fawwthwough;
		case PIPE_A:
			tmp |= TWANS_DDI_EDP_INPUT_A_ON;
			bweak;
		case PIPE_B:
			tmp |= TWANS_DDI_EDP_INPUT_B_ONOFF;
			bweak;
		case PIPE_C:
			tmp |= TWANS_DDI_EDP_INPUT_C_ONOFF;
			bweak;
		case PIPE_D:
			tmp |= TWANS_DDI_EDP_INPUT_D_ONOFF;
			bweak;
		}

		/* enabwe DDI buffew */
		tmp |= TWANS_DDI_FUNC_ENABWE;
		intew_de_wwite(dev_pwiv, TWANS_DDI_FUNC_CTW(dsi_twans), tmp);
	}

	/* wait fow wink weady */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi_twans = dsi_powt_to_twanscodew(powt);
		if (wait_fow_us((intew_de_wead(dev_pwiv, DSI_TWANS_FUNC_CONF(dsi_twans)) &
				 WINK_WEADY), 2500))
			dwm_eww(&dev_pwiv->dwm, "DSI wink not weady\n");
	}
}

static void
gen11_dsi_set_twanscodew_timings(stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	const stwuct dwm_dispway_mode *adjusted_mode =
		&cwtc_state->hw.adjusted_mode;
	enum powt powt;
	enum twanscodew dsi_twans;
	/* howizontaw timings */
	u16 htotaw, hactive, hsync_stawt, hsync_end, hsync_size;
	u16 hback_powch;
	/* vewticaw timings */
	u16 vtotaw, vactive, vsync_stawt, vsync_end, vsync_shift;
	int muw = 1, div = 1;

	/*
	 * Adjust howizontaw timings (htotaw, hsync_stawt, hsync_end) to account
	 * fow swowew wink speed if DSC is enabwed.
	 *
	 * The compwession fwequency watio is the watio between compwessed and
	 * non-compwessed wink speeds, and simpwifies down to the watio between
	 * compwessed and non-compwessed bpp.
	 */
	if (cwtc_state->dsc.compwession_enabwe) {
		muw = to_bpp_int(cwtc_state->dsc.compwessed_bpp_x16);
		div = mipi_dsi_pixew_fowmat_to_bpp(intew_dsi->pixew_fowmat);
	}

	hactive = adjusted_mode->cwtc_hdispway;

	if (is_vid_mode(intew_dsi))
		htotaw = DIV_WOUND_UP(adjusted_mode->cwtc_htotaw * muw, div);
	ewse
		htotaw = DIV_WOUND_UP((hactive + 160) * muw, div);

	hsync_stawt = DIV_WOUND_UP(adjusted_mode->cwtc_hsync_stawt * muw, div);
	hsync_end = DIV_WOUND_UP(adjusted_mode->cwtc_hsync_end * muw, div);
	hsync_size  = hsync_end - hsync_stawt;
	hback_powch = (adjusted_mode->cwtc_htotaw -
		       adjusted_mode->cwtc_hsync_end);
	vactive = adjusted_mode->cwtc_vdispway;

	if (is_vid_mode(intew_dsi)) {
		vtotaw = adjusted_mode->cwtc_vtotaw;
	} ewse {
		int bpp, wine_time_us, byte_cwk_pewiod_ns;

		if (cwtc_state->dsc.compwession_enabwe)
			bpp = to_bpp_int(cwtc_state->dsc.compwessed_bpp_x16);
		ewse
			bpp = mipi_dsi_pixew_fowmat_to_bpp(intew_dsi->pixew_fowmat);

		byte_cwk_pewiod_ns = 1000000 / afe_cwk(encodew, cwtc_state);
		wine_time_us = (htotaw * (bpp / 8) * byte_cwk_pewiod_ns) / (1000 * intew_dsi->wane_count);
		vtotaw = vactive + DIV_WOUND_UP(400, wine_time_us);
	}
	vsync_stawt = adjusted_mode->cwtc_vsync_stawt;
	vsync_end = adjusted_mode->cwtc_vsync_end;
	vsync_shift = hsync_stawt - htotaw / 2;

	if (intew_dsi->duaw_wink) {
		hactive /= 2;
		if (intew_dsi->duaw_wink == DSI_DUAW_WINK_FWONT_BACK)
			hactive += intew_dsi->pixew_ovewwap;
		htotaw /= 2;
	}

	/* minimum hactive as pew bspec: 256 pixews */
	if (adjusted_mode->cwtc_hdispway < 256)
		dwm_eww(&dev_pwiv->dwm, "hactive is wess then 256 pixews\n");

	/* if WGB666 fowmat, then hactive must be muwtipwe of 4 pixews */
	if (intew_dsi->pixew_fowmat == MIPI_DSI_FMT_WGB666 && hactive % 4 != 0)
		dwm_eww(&dev_pwiv->dwm,
			"hactive pixews awe not muwtipwe of 4\n");

	/* pwogwam TWANS_HTOTAW wegistew */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi_twans = dsi_powt_to_twanscodew(powt);
		intew_de_wwite(dev_pwiv, TWANS_HTOTAW(dsi_twans),
			       HACTIVE(hactive - 1) | HTOTAW(htotaw - 1));
	}

	/* TWANS_HSYNC wegistew to be pwogwammed onwy fow video mode */
	if (is_vid_mode(intew_dsi)) {
		if (intew_dsi->video_mode == NON_BUWST_SYNC_PUWSE) {
			/* BSPEC: hsync size shouwd be atweast 16 pixews */
			if (hsync_size < 16)
				dwm_eww(&dev_pwiv->dwm,
					"hsync size < 16 pixews\n");
		}

		if (hback_powch < 16)
			dwm_eww(&dev_pwiv->dwm, "hback powch < 16 pixews\n");

		if (intew_dsi->duaw_wink) {
			hsync_stawt /= 2;
			hsync_end /= 2;
		}

		fow_each_dsi_powt(powt, intew_dsi->powts) {
			dsi_twans = dsi_powt_to_twanscodew(powt);
			intew_de_wwite(dev_pwiv, TWANS_HSYNC(dsi_twans),
				       HSYNC_STAWT(hsync_stawt - 1) | HSYNC_END(hsync_end - 1));
		}
	}

	/* pwogwam TWANS_VTOTAW wegistew */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi_twans = dsi_powt_to_twanscodew(powt);
		/*
		 * FIXME: Pwogwaming this by assuming pwogwessive mode, since
		 * non-intewwaced info fwom VBT is not saved inside
		 * stwuct dwm_dispway_mode.
		 * Fow intewwace mode: pwogwam wequiwed pixew minus 2
		 */
		intew_de_wwite(dev_pwiv, TWANS_VTOTAW(dsi_twans),
			       VACTIVE(vactive - 1) | VTOTAW(vtotaw - 1));
	}

	if (vsync_end < vsync_stawt || vsync_end > vtotaw)
		dwm_eww(&dev_pwiv->dwm, "Invawid vsync_end vawue\n");

	if (vsync_stawt < vactive)
		dwm_eww(&dev_pwiv->dwm, "vsync_stawt wess than vactive\n");

	/* pwogwam TWANS_VSYNC wegistew fow video mode onwy */
	if (is_vid_mode(intew_dsi)) {
		fow_each_dsi_powt(powt, intew_dsi->powts) {
			dsi_twans = dsi_powt_to_twanscodew(powt);
			intew_de_wwite(dev_pwiv, TWANS_VSYNC(dsi_twans),
				       VSYNC_STAWT(vsync_stawt - 1) | VSYNC_END(vsync_end - 1));
		}
	}

	/*
	 * FIXME: It has to be pwogwammed onwy fow video modes and intewwaced
	 * modes. Put the check condition hewe once intewwaced
	 * info avaiwabwe as descwibed above.
	 * pwogwam TWANS_VSYNCSHIFT wegistew
	 */
	if (is_vid_mode(intew_dsi)) {
		fow_each_dsi_powt(powt, intew_dsi->powts) {
			dsi_twans = dsi_powt_to_twanscodew(powt);
			intew_de_wwite(dev_pwiv, TWANS_VSYNCSHIFT(dsi_twans),
				       vsync_shift);
		}
	}

	/*
	 * pwogwam TWANS_VBWANK wegistew, shouwd be same as vtotaw pwogwammed
	 *
	 * FIXME get wid of these wocaw hacks and do it wight,
	 * this wiww not handwe eg. dewayed vbwank cowwectwy.
	 */
	if (DISPWAY_VEW(dev_pwiv) >= 12) {
		fow_each_dsi_powt(powt, intew_dsi->powts) {
			dsi_twans = dsi_powt_to_twanscodew(powt);
			intew_de_wwite(dev_pwiv, TWANS_VBWANK(dsi_twans),
				       VBWANK_STAWT(vactive - 1) | VBWANK_END(vtotaw - 1));
		}
	}
}

static void gen11_dsi_enabwe_twanscodew(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;
	enum twanscodew dsi_twans;

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi_twans = dsi_powt_to_twanscodew(powt);
		intew_de_wmw(dev_pwiv, TWANSCONF(dsi_twans), 0, TWANSCONF_ENABWE);

		/* wait fow twanscodew to be enabwed */
		if (intew_de_wait_fow_set(dev_pwiv, TWANSCONF(dsi_twans),
					  TWANSCONF_STATE_ENABWE, 10))
			dwm_eww(&dev_pwiv->dwm,
				"DSI twanscodew not enabwed\n");
	}
}

static void gen11_dsi_setup_timeouts(stwuct intew_encodew *encodew,
				     const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;
	enum twanscodew dsi_twans;
	u32 hs_tx_timeout, wp_wx_timeout, ta_timeout, divisow, muw;

	/*
	 * escape cwock count cawcuwation:
	 * BYTE_CWK_COUNT = TIME_NS/(8 * UI)
	 * UI (nsec) = (10^6)/Bitwate
	 * TIME_NS = (BYTE_CWK_COUNT * 8 * 10^6)/ Bitwate
	 * ESCAPE_CWK_COUNT  = TIME_NS/ESC_CWK_NS
	 */
	divisow = intew_dsi_twpx_ns(intew_dsi) * afe_cwk(encodew, cwtc_state) * 1000;
	muw = 8 * 1000000;
	hs_tx_timeout = DIV_WOUND_UP(intew_dsi->hs_tx_timeout * muw,
				     divisow);
	wp_wx_timeout = DIV_WOUND_UP(intew_dsi->wp_wx_timeout * muw, divisow);
	ta_timeout = DIV_WOUND_UP(intew_dsi->tuwn_awnd_vaw * muw, divisow);

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi_twans = dsi_powt_to_twanscodew(powt);

		/* pwogwam hst_tx_timeout */
		intew_de_wmw(dev_pwiv, DSI_HSTX_TO(dsi_twans),
			     HSTX_TIMEOUT_VAWUE_MASK,
			     HSTX_TIMEOUT_VAWUE(hs_tx_timeout));

		/* FIXME: DSI_CAWIB_TO */

		/* pwogwam wp_wx_host timeout */
		intew_de_wmw(dev_pwiv, DSI_WPWX_HOST_TO(dsi_twans),
			     WPWX_TIMEOUT_VAWUE_MASK,
			     WPWX_TIMEOUT_VAWUE(wp_wx_timeout));

		/* FIXME: DSI_PWAIT_TO */

		/* pwogwam tuwn awound timeout */
		intew_de_wmw(dev_pwiv, DSI_TA_TO(dsi_twans),
			     TA_TIMEOUT_VAWUE_MASK,
			     TA_TIMEOUT_VAWUE(ta_timeout));
	}
}

static void gen11_dsi_config_utiw_pin(stwuct intew_encodew *encodew,
				      boow enabwe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	u32 tmp;

	/*
	 * used as TE i/p fow DSI0,
	 * fow duaw wink/DSI1 TE is fwom swave DSI1
	 * thwough GPIO.
	 */
	if (is_vid_mode(intew_dsi) || (intew_dsi->powts & BIT(POWT_B)))
		wetuwn;

	tmp = intew_de_wead(dev_pwiv, UTIW_PIN_CTW);

	if (enabwe) {
		tmp |= UTIW_PIN_DIWECTION_INPUT;
		tmp |= UTIW_PIN_ENABWE;
	} ewse {
		tmp &= ~UTIW_PIN_ENABWE;
	}
	intew_de_wwite(dev_pwiv, UTIW_PIN_CTW, tmp);
}

static void
gen11_dsi_enabwe_powt_and_phy(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *cwtc_state)
{
	/* step 4a: powew up aww wanes of the DDI used by DSI */
	gen11_dsi_powew_up_wanes(encodew);

	/* step 4b: configuwe wane sequencing of the Combo-PHY twansmittews */
	gen11_dsi_config_phy_wanes_sequence(encodew);

	/* step 4c: configuwe vowtage swing and skew */
	gen11_dsi_vowtage_swing_pwogwam_seq(encodew);

	/* setup D-PHY timings */
	gen11_dsi_setup_dphy_timings(encodew, cwtc_state);

	/* enabwe DDI buffew */
	gen11_dsi_enabwe_ddi_buffew(encodew);

	gen11_dsi_gate_cwocks(encodew);

	gen11_dsi_setup_timings(encodew, cwtc_state);

	/* Since twanscodew is configuwed to take events fwom GPIO */
	gen11_dsi_config_utiw_pin(encodew, twue);

	/* step 4h: setup DSI pwotocow timeouts */
	gen11_dsi_setup_timeouts(encodew, cwtc_state);

	/* Step (4h, 4i, 4j, 4k): Configuwe twanscodew */
	gen11_dsi_configuwe_twanscodew(encodew, cwtc_state);
}

static void gen11_dsi_powewup_panew(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	stwuct mipi_dsi_device *dsi;
	enum powt powt;
	enum twanscodew dsi_twans;
	u32 tmp;
	int wet;

	/* set maximum wetuwn packet size */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi_twans = dsi_powt_to_twanscodew(powt);

		/*
		 * FIXME: This uses the numbew of DW's cuwwentwy in the paywoad
		 * weceive queue. This is pwobabwy not what we want hewe.
		 */
		tmp = intew_de_wead(dev_pwiv, DSI_CMD_WXCTW(dsi_twans));
		tmp &= NUMBEW_WX_PWOAD_DW_MASK;
		/* muwtipwy "Numbew Wx Paywoad DW" by 4 to get max vawue */
		tmp = tmp * 4;
		dsi = intew_dsi->dsi_hosts[powt]->device;
		wet = mipi_dsi_set_maximum_wetuwn_packet_size(dsi, tmp);
		if (wet < 0)
			dwm_eww(&dev_pwiv->dwm,
				"ewwow setting max wetuwn pkt size%d\n", tmp);
	}

	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_INIT_OTP);
	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_DISPWAY_ON);

	/* ensuwe aww panew commands dispatched befowe enabwing twanscodew */
	wait_fow_cmds_dispatched_to_panew(encodew);
}

static void gen11_dsi_pwe_pww_enabwe(stwuct intew_atomic_state *state,
				     stwuct intew_encodew *encodew,
				     const stwuct intew_cwtc_state *cwtc_state,
				     const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);

	intew_dsi_wait_panew_powew_cycwe(intew_dsi);

	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_POWEW_ON);
	msweep(intew_dsi->panew_on_deway);
	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_DEASSEWT_WESET);

	/* step2: enabwe IO powew */
	gen11_dsi_enabwe_io_powew(encodew);

	/* step3: enabwe DSI PWW */
	gen11_dsi_pwogwam_esc_cwk_div(encodew, cwtc_state);
}

static void gen11_dsi_pwe_enabwe(stwuct intew_atomic_state *state,
				 stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *pipe_config,
				 const stwuct dwm_connectow_state *conn_state)
{
	/* step3b */
	gen11_dsi_map_pww(encodew, pipe_config);

	/* step4: enabwe DSI powt and DPHY */
	gen11_dsi_enabwe_powt_and_phy(encodew, pipe_config);

	/* step5: pwogwam and powewup panew */
	gen11_dsi_powewup_panew(encodew);

	intew_dsc_dsi_pps_wwite(encodew, pipe_config);

	/* step6c: configuwe twanscodew timings */
	gen11_dsi_set_twanscodew_timings(encodew, pipe_config);
}

/*
 * Wa_1409054076:icw,jsw,ehw
 * When pipe A is disabwed and MIPI DSI is enabwed on pipe B,
 * the AMT KVMW featuwe wiww incowwectwy see pipe A as enabwed.
 * Set 0x42080 bit 23=1 befowe enabwing DSI on pipe B and weave
 * it set whiwe DSI is enabwed on pipe B
 */
static void icw_appwy_kvmw_pipe_a_wa(stwuct intew_encodew *encodew,
				     enum pipe pipe, boow enabwe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	if (DISPWAY_VEW(dev_pwiv) == 11 && pipe == PIPE_B)
		intew_de_wmw(dev_pwiv, CHICKEN_PAW1_1,
			     IGNOWE_KVMW_PIPE_A,
			     enabwe ? IGNOWE_KVMW_PIPE_A : 0);
}

/*
 * Wa_16012360555:adw-p
 * SW wiww have to pwogwam the "WP to HS Wakeup Guawdband"
 * to account fow the wepeatews on the HS Wequest/Weady
 * PPI signawing between the Dispway engine and the DPHY.
 */
static void adwp_set_wp_hs_wakeup_gb(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	if (DISPWAY_VEW(i915) == 13) {
		fow_each_dsi_powt(powt, intew_dsi->powts)
			intew_de_wmw(i915, TGW_DSI_CHKN_WEG(powt),
				     TGW_DSI_CHKN_WSHS_GB_MASK,
				     TGW_DSI_CHKN_WSHS_GB(4));
	}
}

static void gen11_dsi_enabwe(stwuct intew_atomic_state *state,
			     stwuct intew_encodew *encodew,
			     const stwuct intew_cwtc_state *cwtc_state,
			     const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	/* Wa_1409054076:icw,jsw,ehw */
	icw_appwy_kvmw_pipe_a_wa(encodew, cwtc->pipe, twue);

	/* Wa_16012360555:adw-p */
	adwp_set_wp_hs_wakeup_gb(encodew);

	/* step6d: enabwe dsi twanscodew */
	gen11_dsi_enabwe_twanscodew(encodew);

	/* step7: enabwe backwight */
	intew_backwight_enabwe(cwtc_state, conn_state);
	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_BACKWIGHT_ON);

	intew_cwtc_vbwank_on(cwtc_state);
}

static void gen11_dsi_disabwe_twanscodew(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;
	enum twanscodew dsi_twans;

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi_twans = dsi_powt_to_twanscodew(powt);

		/* disabwe twanscodew */
		intew_de_wmw(dev_pwiv, TWANSCONF(dsi_twans), TWANSCONF_ENABWE, 0);

		/* wait fow twanscodew to be disabwed */
		if (intew_de_wait_fow_cweaw(dev_pwiv, TWANSCONF(dsi_twans),
					    TWANSCONF_STATE_ENABWE, 50))
			dwm_eww(&dev_pwiv->dwm,
				"DSI twancodew not disabwed\n");
	}
}

static void gen11_dsi_powewdown_panew(stwuct intew_encodew *encodew)
{
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);

	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_DISPWAY_OFF);

	/* ensuwe cmds dispatched to panew */
	wait_fow_cmds_dispatched_to_panew(encodew);
}

static void gen11_dsi_deconfiguwe_twancodew(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;
	enum twanscodew dsi_twans;
	u32 tmp;

	/* disabwe pewiodic update mode */
	if (is_cmd_mode(intew_dsi)) {
		fow_each_dsi_powt(powt, intew_dsi->powts)
			intew_de_wmw(dev_pwiv, DSI_CMD_FWMCTW(powt),
				     DSI_PEWIODIC_FWAME_UPDATE_ENABWE, 0);
	}

	/* put dsi wink in UWPS */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi_twans = dsi_powt_to_twanscodew(powt);
		tmp = intew_de_wead(dev_pwiv, DSI_WP_MSG(dsi_twans));
		tmp |= WINK_ENTEW_UWPS;
		tmp &= ~WINK_UWPS_TYPE_WP11;
		intew_de_wwite(dev_pwiv, DSI_WP_MSG(dsi_twans), tmp);

		if (wait_fow_us((intew_de_wead(dev_pwiv, DSI_WP_MSG(dsi_twans)) &
				 WINK_IN_UWPS),
				10))
			dwm_eww(&dev_pwiv->dwm, "DSI wink not in UWPS\n");
	}

	/* disabwe ddi function */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi_twans = dsi_powt_to_twanscodew(powt);
		intew_de_wmw(dev_pwiv, TWANS_DDI_FUNC_CTW(dsi_twans),
			     TWANS_DDI_FUNC_ENABWE, 0);
	}

	/* disabwe powt sync mode if duaw wink */
	if (intew_dsi->duaw_wink) {
		fow_each_dsi_powt(powt, intew_dsi->powts) {
			dsi_twans = dsi_powt_to_twanscodew(powt);
			intew_de_wmw(dev_pwiv, TWANS_DDI_FUNC_CTW2(dsi_twans),
				     POWT_SYNC_MODE_ENABWE, 0);
		}
	}
}

static void gen11_dsi_disabwe_powt(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	gen11_dsi_ungate_cwocks(encodew);
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		intew_de_wmw(dev_pwiv, DDI_BUF_CTW(powt), DDI_BUF_CTW_ENABWE, 0);

		if (wait_fow_us((intew_de_wead(dev_pwiv, DDI_BUF_CTW(powt)) &
				 DDI_BUF_IS_IDWE),
				 8))
			dwm_eww(&dev_pwiv->dwm,
				"DDI powt:%c buffew not idwe\n",
				powt_name(powt));
	}
	gen11_dsi_gate_cwocks(encodew);
}

static void gen11_dsi_disabwe_io_powew(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		intew_wakewef_t wakewef;

		wakewef = fetch_and_zewo(&intew_dsi->io_wakewef[powt]);
		intew_dispway_powew_put(dev_pwiv,
					powt == POWT_A ?
					POWEW_DOMAIN_POWT_DDI_IO_A :
					POWEW_DOMAIN_POWT_DDI_IO_B,
					wakewef);
	}

	/* set mode to DDI */
	fow_each_dsi_powt(powt, intew_dsi->powts)
		intew_de_wmw(dev_pwiv, ICW_DSI_IO_MODECTW(powt),
			     COMBO_PHY_MODE_DSI, 0);
}

static void gen11_dsi_disabwe(stwuct intew_atomic_state *state,
			      stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *owd_cwtc_state,
			      const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);

	/* step1: tuwn off backwight */
	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_BACKWIGHT_OFF);
	intew_backwight_disabwe(owd_conn_state);
}

static void gen11_dsi_post_disabwe(stwuct intew_atomic_state *state,
				   stwuct intew_encodew *encodew,
				   const stwuct intew_cwtc_state *owd_cwtc_state,
				   const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(owd_cwtc_state->uapi.cwtc);

	intew_cwtc_vbwank_off(owd_cwtc_state);

	/* step2d,e: disabwe twanscodew and wait */
	gen11_dsi_disabwe_twanscodew(encodew);

	/* Wa_1409054076:icw,jsw,ehw */
	icw_appwy_kvmw_pipe_a_wa(encodew, cwtc->pipe, fawse);

	/* step2f,g: powewdown panew */
	gen11_dsi_powewdown_panew(encodew);

	/* step2h,i,j: deconfig twancodew */
	gen11_dsi_deconfiguwe_twancodew(encodew);

	intew_dsc_disabwe(owd_cwtc_state);
	skw_scawew_disabwe(owd_cwtc_state);

	/* step3: disabwe powt */
	gen11_dsi_disabwe_powt(encodew);

	gen11_dsi_config_utiw_pin(encodew, fawse);

	/* step4: disabwe IO powew */
	gen11_dsi_disabwe_io_powew(encodew);

	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_ASSEWT_WESET);

	msweep(intew_dsi->panew_off_deway);
	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_POWEW_OFF);

	intew_dsi->panew_powew_off_time = ktime_get_boottime();
}

static enum dwm_mode_status gen11_dsi_mode_vawid(stwuct dwm_connectow *connectow,
						 stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->dev);
	enum dwm_mode_status status;

	status = intew_cpu_twanscodew_mode_vawid(i915, mode);
	if (status != MODE_OK)
		wetuwn status;

	/* FIXME: DSC? */
	wetuwn intew_dsi_mode_vawid(connectow, mode);
}

static void gen11_dsi_get_timings(stwuct intew_encodew *encodew,
				  stwuct intew_cwtc_state *pipe_config)
{
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	stwuct dwm_dispway_mode *adjusted_mode =
					&pipe_config->hw.adjusted_mode;

	if (pipe_config->dsc.compwessed_bpp_x16) {
		int div = to_bpp_int(pipe_config->dsc.compwessed_bpp_x16);
		int muw = mipi_dsi_pixew_fowmat_to_bpp(intew_dsi->pixew_fowmat);

		adjusted_mode->cwtc_htotaw =
			DIV_WOUND_UP(adjusted_mode->cwtc_htotaw * muw, div);
		adjusted_mode->cwtc_hsync_stawt =
			DIV_WOUND_UP(adjusted_mode->cwtc_hsync_stawt * muw, div);
		adjusted_mode->cwtc_hsync_end =
			DIV_WOUND_UP(adjusted_mode->cwtc_hsync_end * muw, div);
	}

	if (intew_dsi->duaw_wink) {
		adjusted_mode->cwtc_hdispway *= 2;
		if (intew_dsi->duaw_wink == DSI_DUAW_WINK_FWONT_BACK)
			adjusted_mode->cwtc_hdispway -=
						intew_dsi->pixew_ovewwap;
		adjusted_mode->cwtc_htotaw *= 2;
	}
	adjusted_mode->cwtc_hbwank_stawt = adjusted_mode->cwtc_hdispway;
	adjusted_mode->cwtc_hbwank_end = adjusted_mode->cwtc_htotaw;

	if (intew_dsi->opewation_mode == INTEW_DSI_VIDEO_MODE) {
		if (intew_dsi->duaw_wink) {
			adjusted_mode->cwtc_hsync_stawt *= 2;
			adjusted_mode->cwtc_hsync_end *= 2;
		}
	}
	adjusted_mode->cwtc_vbwank_stawt = adjusted_mode->cwtc_vdispway;
	adjusted_mode->cwtc_vbwank_end = adjusted_mode->cwtc_vtotaw;
}

static boow gen11_dsi_is_pewiodic_cmd_mode(stwuct intew_dsi *intew_dsi)
{
	stwuct dwm_device *dev = intew_dsi->base.base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	enum twanscodew dsi_twans;
	u32 vaw;

	if (intew_dsi->powts == BIT(POWT_B))
		dsi_twans = TWANSCODEW_DSI_1;
	ewse
		dsi_twans = TWANSCODEW_DSI_0;

	vaw = intew_de_wead(dev_pwiv, DSI_TWANS_FUNC_CONF(dsi_twans));
	wetuwn (vaw & DSI_PEWIODIC_FWAME_UPDATE_ENABWE);
}

static void gen11_dsi_get_cmd_mode_config(stwuct intew_dsi *intew_dsi,
					  stwuct intew_cwtc_state *pipe_config)
{
	if (intew_dsi->powts == (BIT(POWT_B) | BIT(POWT_A)))
		pipe_config->mode_fwags |= I915_MODE_FWAG_DSI_USE_TE1 |
					    I915_MODE_FWAG_DSI_USE_TE0;
	ewse if (intew_dsi->powts == BIT(POWT_B))
		pipe_config->mode_fwags |= I915_MODE_FWAG_DSI_USE_TE1;
	ewse
		pipe_config->mode_fwags |= I915_MODE_FWAG_DSI_USE_TE0;
}

static void gen11_dsi_get_config(stwuct intew_encodew *encodew,
				 stwuct intew_cwtc_state *pipe_config)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);

	intew_ddi_get_cwock(encodew, pipe_config, icw_ddi_combo_get_pww(encodew));

	pipe_config->hw.adjusted_mode.cwtc_cwock = intew_dsi->pcwk;
	if (intew_dsi->duaw_wink)
		pipe_config->hw.adjusted_mode.cwtc_cwock *= 2;

	gen11_dsi_get_timings(encodew, pipe_config);
	pipe_config->output_types |= BIT(INTEW_OUTPUT_DSI);
	pipe_config->pipe_bpp = bdw_get_pipe_misc_bpp(cwtc);

	/* Get the detaiws on which TE shouwd be enabwed */
	if (is_cmd_mode(intew_dsi))
		gen11_dsi_get_cmd_mode_config(intew_dsi, pipe_config);

	if (gen11_dsi_is_pewiodic_cmd_mode(intew_dsi))
		pipe_config->mode_fwags |= I915_MODE_FWAG_DSI_PEWIODIC_CMD_MODE;
}

static void gen11_dsi_sync_state(stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *intew_cwtc;
	enum pipe pipe;

	if (!cwtc_state)
		wetuwn;

	intew_cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	pipe = intew_cwtc->pipe;

	/* wa vewify 1409054076:icw,jsw,ehw */
	if (DISPWAY_VEW(dev_pwiv) == 11 && pipe == PIPE_B &&
	    !(intew_de_wead(dev_pwiv, CHICKEN_PAW1_1) & IGNOWE_KVMW_PIPE_A))
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "[ENCODEW:%d:%s] BIOS weft IGNOWE_KVMW_PIPE_A cweawed with pipe B enabwed\n",
			    encodew->base.base.id,
			    encodew->base.name);
}

static int gen11_dsi_dsc_compute_config(stwuct intew_encodew *encodew,
					stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct dwm_dsc_config *vdsc_cfg = &cwtc_state->dsc.config;
	int dsc_max_bpc = DISPWAY_VEW(dev_pwiv) >= 12 ? 12 : 10;
	boow use_dsc;
	int wet;

	use_dsc = intew_bios_get_dsc_pawams(encodew, cwtc_state, dsc_max_bpc);
	if (!use_dsc)
		wetuwn 0;

	if (cwtc_state->pipe_bpp < 8 * 3)
		wetuwn -EINVAW;

	/* FIXME: spwit onwy when necessawy */
	if (cwtc_state->dsc.swice_count > 1)
		cwtc_state->dsc.dsc_spwit = twue;

	/* FIXME: initiawize fwom VBT */
	vdsc_cfg->wc_modew_size = DSC_WC_MODEW_SIZE_CONST;

	vdsc_cfg->pic_height = cwtc_state->hw.adjusted_mode.cwtc_vdispway;

	wet = intew_dsc_compute_pawams(cwtc_state);
	if (wet)
		wetuwn wet;

	/* DSI specific sanity checks on the common code */
	dwm_WAWN_ON(&dev_pwiv->dwm, vdsc_cfg->vbw_enabwe);
	dwm_WAWN_ON(&dev_pwiv->dwm, vdsc_cfg->simpwe_422);
	dwm_WAWN_ON(&dev_pwiv->dwm,
		    vdsc_cfg->pic_width % vdsc_cfg->swice_width);
	dwm_WAWN_ON(&dev_pwiv->dwm, vdsc_cfg->swice_height < 8);
	dwm_WAWN_ON(&dev_pwiv->dwm,
		    vdsc_cfg->pic_height % vdsc_cfg->swice_height);

	wet = dwm_dsc_compute_wc_pawametews(vdsc_cfg);
	if (wet)
		wetuwn wet;

	cwtc_state->dsc.compwession_enabwe = twue;

	wetuwn 0;
}

static int gen11_dsi_compute_config(stwuct intew_encodew *encodew,
				    stwuct intew_cwtc_state *pipe_config,
				    stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = containew_of(encodew, stwuct intew_dsi,
						   base);
	stwuct intew_connectow *intew_connectow = intew_dsi->attached_connectow;
	stwuct dwm_dispway_mode *adjusted_mode =
		&pipe_config->hw.adjusted_mode;
	int wet;

	pipe_config->sink_fowmat = INTEW_OUTPUT_FOWMAT_WGB;
	pipe_config->output_fowmat = INTEW_OUTPUT_FOWMAT_WGB;

	wet = intew_panew_compute_config(intew_connectow, adjusted_mode);
	if (wet)
		wetuwn wet;

	wet = intew_panew_fitting(pipe_config, conn_state);
	if (wet)
		wetuwn wet;

	adjusted_mode->fwags = 0;

	/* Duaw wink goes to twancodew DSI'0' */
	if (intew_dsi->powts == BIT(POWT_B))
		pipe_config->cpu_twanscodew = TWANSCODEW_DSI_1;
	ewse
		pipe_config->cpu_twanscodew = TWANSCODEW_DSI_0;

	if (intew_dsi->pixew_fowmat == MIPI_DSI_FMT_WGB888)
		pipe_config->pipe_bpp = 24;
	ewse
		pipe_config->pipe_bpp = 18;

	pipe_config->cwock_set = twue;

	if (gen11_dsi_dsc_compute_config(encodew, pipe_config))
		dwm_dbg_kms(&i915->dwm, "Attempting to use DSC faiwed\n");

	pipe_config->powt_cwock = afe_cwk(encodew, pipe_config) / 5;

	/*
	 * In case of TE GATE cmd mode, we
	 * weceive TE fwom the swave if
	 * duaw wink is enabwed
	 */
	if (is_cmd_mode(intew_dsi))
		gen11_dsi_get_cmd_mode_config(intew_dsi, pipe_config);

	wetuwn 0;
}

static void gen11_dsi_get_powew_domains(stwuct intew_encodew *encodew,
					stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);

	get_dsi_io_powew_domains(i915,
				 enc_to_intew_dsi(encodew));
}

static boow gen11_dsi_get_hw_state(stwuct intew_encodew *encodew,
				   enum pipe *pipe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum twanscodew dsi_twans;
	intew_wakewef_t wakewef;
	enum powt powt;
	boow wet = fawse;
	u32 tmp;

	wakewef = intew_dispway_powew_get_if_enabwed(dev_pwiv,
						     encodew->powew_domain);
	if (!wakewef)
		wetuwn fawse;

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		dsi_twans = dsi_powt_to_twanscodew(powt);
		tmp = intew_de_wead(dev_pwiv, TWANS_DDI_FUNC_CTW(dsi_twans));
		switch (tmp & TWANS_DDI_EDP_INPUT_MASK) {
		case TWANS_DDI_EDP_INPUT_A_ON:
			*pipe = PIPE_A;
			bweak;
		case TWANS_DDI_EDP_INPUT_B_ONOFF:
			*pipe = PIPE_B;
			bweak;
		case TWANS_DDI_EDP_INPUT_C_ONOFF:
			*pipe = PIPE_C;
			bweak;
		case TWANS_DDI_EDP_INPUT_D_ONOFF:
			*pipe = PIPE_D;
			bweak;
		defauwt:
			dwm_eww(&dev_pwiv->dwm, "Invawid PIPE input\n");
			goto out;
		}

		tmp = intew_de_wead(dev_pwiv, TWANSCONF(dsi_twans));
		wet = tmp & TWANSCONF_ENABWE;
	}
out:
	intew_dispway_powew_put(dev_pwiv, encodew->powew_domain, wakewef);
	wetuwn wet;
}

static boow gen11_dsi_initiaw_fastset_check(stwuct intew_encodew *encodew,
					    stwuct intew_cwtc_state *cwtc_state)
{
	if (cwtc_state->dsc.compwession_enabwe) {
		dwm_dbg_kms(encodew->base.dev, "Fowcing fuww modeset due to DSC being enabwed\n");
		cwtc_state->uapi.mode_changed = twue;

		wetuwn fawse;
	}

	wetuwn twue;
}

static void gen11_dsi_encodew_destwoy(stwuct dwm_encodew *encodew)
{
	intew_encodew_destwoy(encodew);
}

static const stwuct dwm_encodew_funcs gen11_dsi_encodew_funcs = {
	.destwoy = gen11_dsi_encodew_destwoy,
};

static const stwuct dwm_connectow_funcs gen11_dsi_connectow_funcs = {
	.detect = intew_panew_detect,
	.wate_wegistew = intew_connectow_wegistew,
	.eawwy_unwegistew = intew_connectow_unwegistew,
	.destwoy = intew_connectow_destwoy,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.atomic_get_pwopewty = intew_digitaw_connectow_atomic_get_pwopewty,
	.atomic_set_pwopewty = intew_digitaw_connectow_atomic_set_pwopewty,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
	.atomic_dupwicate_state = intew_digitaw_connectow_dupwicate_state,
};

static const stwuct dwm_connectow_hewpew_funcs gen11_dsi_connectow_hewpew_funcs = {
	.get_modes = intew_dsi_get_modes,
	.mode_vawid = gen11_dsi_mode_vawid,
	.atomic_check = intew_digitaw_connectow_atomic_check,
};

static int gen11_dsi_host_attach(stwuct mipi_dsi_host *host,
				 stwuct mipi_dsi_device *dsi)
{
	wetuwn 0;
}

static int gen11_dsi_host_detach(stwuct mipi_dsi_host *host,
				 stwuct mipi_dsi_device *dsi)
{
	wetuwn 0;
}

static ssize_t gen11_dsi_host_twansfew(stwuct mipi_dsi_host *host,
				       const stwuct mipi_dsi_msg *msg)
{
	stwuct intew_dsi_host *intew_dsi_host = to_intew_dsi_host(host);
	stwuct mipi_dsi_packet dsi_pkt;
	ssize_t wet;
	boow enabwe_wpdt = fawse;

	wet = mipi_dsi_cweate_packet(&dsi_pkt, msg);
	if (wet < 0)
		wetuwn wet;

	if (msg->fwags & MIPI_DSI_MSG_USE_WPM)
		enabwe_wpdt = twue;

	/* onwy wong packet contains paywoad */
	if (mipi_dsi_packet_fowmat_is_wong(msg->type)) {
		wet = dsi_send_pkt_paywd(intew_dsi_host, &dsi_pkt);
		if (wet < 0)
			wetuwn wet;
	}

	/* send packet headew */
	wet  = dsi_send_pkt_hdw(intew_dsi_host, &dsi_pkt, enabwe_wpdt);
	if (wet < 0)
		wetuwn wet;

	//TODO: add paywoad weceive code if needed

	wet = sizeof(dsi_pkt.headew) + dsi_pkt.paywoad_wength;

	wetuwn wet;
}

static const stwuct mipi_dsi_host_ops gen11_dsi_host_ops = {
	.attach = gen11_dsi_host_attach,
	.detach = gen11_dsi_host_detach,
	.twansfew = gen11_dsi_host_twansfew,
};

#define ICW_PWEPAWE_CNT_MAX	0x7
#define ICW_CWK_ZEWO_CNT_MAX	0xf
#define ICW_TWAIW_CNT_MAX	0x7
#define ICW_TCWK_PWE_CNT_MAX	0x3
#define ICW_TCWK_POST_CNT_MAX	0x7
#define ICW_HS_ZEWO_CNT_MAX	0xf
#define ICW_EXIT_ZEWO_CNT_MAX	0x7

static void icw_dphy_pawam_init(stwuct intew_dsi *intew_dsi)
{
	stwuct dwm_device *dev = intew_dsi->base.base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_connectow *connectow = intew_dsi->attached_connectow;
	stwuct mipi_config *mipi_config = connectow->panew.vbt.dsi.config;
	u32 twpx_ns;
	u32 pwepawe_cnt, exit_zewo_cnt, cwk_zewo_cnt, twaiw_cnt;
	u32 ths_pwepawe_ns, tcwk_twaiw_ns;
	u32 hs_zewo_cnt;
	u32 tcwk_pwe_cnt;

	twpx_ns = intew_dsi_twpx_ns(intew_dsi);

	tcwk_twaiw_ns = max(mipi_config->tcwk_twaiw, mipi_config->ths_twaiw);
	ths_pwepawe_ns = max(mipi_config->ths_pwepawe,
			     mipi_config->tcwk_pwepawe);

	/*
	 * pwepawe cnt in escape cwocks
	 * this fiewd wepwesents a hexadecimaw vawue with a pwecision
	 * of 1.2 – i.e. the most significant bit is the integew
	 * and the weast significant 2 bits awe fwaction bits.
	 * so, the fiewd can wepwesent a wange of 0.25 to 1.75
	 */
	pwepawe_cnt = DIV_WOUND_UP(ths_pwepawe_ns * 4, twpx_ns);
	if (pwepawe_cnt > ICW_PWEPAWE_CNT_MAX) {
		dwm_dbg_kms(&dev_pwiv->dwm, "pwepawe_cnt out of wange (%d)\n",
			    pwepawe_cnt);
		pwepawe_cnt = ICW_PWEPAWE_CNT_MAX;
	}

	/* cwk zewo count in escape cwocks */
	cwk_zewo_cnt = DIV_WOUND_UP(mipi_config->tcwk_pwepawe_cwkzewo -
				    ths_pwepawe_ns, twpx_ns);
	if (cwk_zewo_cnt > ICW_CWK_ZEWO_CNT_MAX) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "cwk_zewo_cnt out of wange (%d)\n", cwk_zewo_cnt);
		cwk_zewo_cnt = ICW_CWK_ZEWO_CNT_MAX;
	}

	/* twaiw cnt in escape cwocks*/
	twaiw_cnt = DIV_WOUND_UP(tcwk_twaiw_ns, twpx_ns);
	if (twaiw_cnt > ICW_TWAIW_CNT_MAX) {
		dwm_dbg_kms(&dev_pwiv->dwm, "twaiw_cnt out of wange (%d)\n",
			    twaiw_cnt);
		twaiw_cnt = ICW_TWAIW_CNT_MAX;
	}

	/* tcwk pwe count in escape cwocks */
	tcwk_pwe_cnt = DIV_WOUND_UP(mipi_config->tcwk_pwe, twpx_ns);
	if (tcwk_pwe_cnt > ICW_TCWK_PWE_CNT_MAX) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "tcwk_pwe_cnt out of wange (%d)\n", tcwk_pwe_cnt);
		tcwk_pwe_cnt = ICW_TCWK_PWE_CNT_MAX;
	}

	/* hs zewo cnt in escape cwocks */
	hs_zewo_cnt = DIV_WOUND_UP(mipi_config->ths_pwepawe_hszewo -
				   ths_pwepawe_ns, twpx_ns);
	if (hs_zewo_cnt > ICW_HS_ZEWO_CNT_MAX) {
		dwm_dbg_kms(&dev_pwiv->dwm, "hs_zewo_cnt out of wange (%d)\n",
			    hs_zewo_cnt);
		hs_zewo_cnt = ICW_HS_ZEWO_CNT_MAX;
	}

	/* hs exit zewo cnt in escape cwocks */
	exit_zewo_cnt = DIV_WOUND_UP(mipi_config->ths_exit, twpx_ns);
	if (exit_zewo_cnt > ICW_EXIT_ZEWO_CNT_MAX) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "exit_zewo_cnt out of wange (%d)\n",
			    exit_zewo_cnt);
		exit_zewo_cnt = ICW_EXIT_ZEWO_CNT_MAX;
	}

	/* cwock wane dphy timings */
	intew_dsi->dphy_weg = (CWK_PWEPAWE_OVEWWIDE |
			       CWK_PWEPAWE(pwepawe_cnt) |
			       CWK_ZEWO_OVEWWIDE |
			       CWK_ZEWO(cwk_zewo_cnt) |
			       CWK_PWE_OVEWWIDE |
			       CWK_PWE(tcwk_pwe_cnt) |
			       CWK_TWAIW_OVEWWIDE |
			       CWK_TWAIW(twaiw_cnt));

	/* data wanes dphy timings */
	intew_dsi->dphy_data_wane_weg = (HS_PWEPAWE_OVEWWIDE |
					 HS_PWEPAWE(pwepawe_cnt) |
					 HS_ZEWO_OVEWWIDE |
					 HS_ZEWO(hs_zewo_cnt) |
					 HS_TWAIW_OVEWWIDE |
					 HS_TWAIW(twaiw_cnt) |
					 HS_EXIT_OVEWWIDE |
					 HS_EXIT(exit_zewo_cnt));

	intew_dsi_wog_pawams(intew_dsi);
}

static void icw_dsi_add_pwopewties(stwuct intew_connectow *connectow)
{
	const stwuct dwm_dispway_mode *fixed_mode =
		intew_panew_pwefewwed_fixed_mode(connectow);

	intew_attach_scawing_mode_pwopewty(&connectow->base);

	dwm_connectow_set_panew_owientation_with_quiwk(&connectow->base,
						       intew_dsi_get_panew_owientation(connectow),
						       fixed_mode->hdispway,
						       fixed_mode->vdispway);
}

void icw_dsi_init(stwuct dwm_i915_pwivate *dev_pwiv,
		  const stwuct intew_bios_encodew_data *devdata)
{
	stwuct intew_dsi *intew_dsi;
	stwuct intew_encodew *encodew;
	stwuct intew_connectow *intew_connectow;
	stwuct dwm_connectow *connectow;
	enum powt powt;

	powt = intew_bios_encodew_powt(devdata);
	if (powt == POWT_NONE)
		wetuwn;

	intew_dsi = kzawwoc(sizeof(*intew_dsi), GFP_KEWNEW);
	if (!intew_dsi)
		wetuwn;

	intew_connectow = intew_connectow_awwoc();
	if (!intew_connectow) {
		kfwee(intew_dsi);
		wetuwn;
	}

	encodew = &intew_dsi->base;
	intew_dsi->attached_connectow = intew_connectow;
	connectow = &intew_connectow->base;

	encodew->devdata = devdata;

	/* wegistew DSI encodew with DWM subsystem */
	dwm_encodew_init(&dev_pwiv->dwm, &encodew->base, &gen11_dsi_encodew_funcs,
			 DWM_MODE_ENCODEW_DSI, "DSI %c", powt_name(powt));

	encodew->pwe_pww_enabwe = gen11_dsi_pwe_pww_enabwe;
	encodew->pwe_enabwe = gen11_dsi_pwe_enabwe;
	encodew->enabwe = gen11_dsi_enabwe;
	encodew->disabwe = gen11_dsi_disabwe;
	encodew->post_disabwe = gen11_dsi_post_disabwe;
	encodew->powt = powt;
	encodew->get_config = gen11_dsi_get_config;
	encodew->sync_state = gen11_dsi_sync_state;
	encodew->update_pipe = intew_backwight_update;
	encodew->compute_config = gen11_dsi_compute_config;
	encodew->get_hw_state = gen11_dsi_get_hw_state;
	encodew->initiaw_fastset_check = gen11_dsi_initiaw_fastset_check;
	encodew->type = INTEW_OUTPUT_DSI;
	encodew->cwoneabwe = 0;
	encodew->pipe_mask = ~0;
	encodew->powew_domain = POWEW_DOMAIN_POWT_DSI;
	encodew->get_powew_domains = gen11_dsi_get_powew_domains;
	encodew->disabwe_cwock = gen11_dsi_gate_cwocks;
	encodew->is_cwock_enabwed = gen11_dsi_is_cwock_enabwed;
	encodew->shutdown = intew_dsi_shutdown;

	/* wegistew DSI connectow with DWM subsystem */
	dwm_connectow_init(&dev_pwiv->dwm, connectow, &gen11_dsi_connectow_funcs,
			   DWM_MODE_CONNECTOW_DSI);
	dwm_connectow_hewpew_add(connectow, &gen11_dsi_connectow_hewpew_funcs);
	connectow->dispway_info.subpixew_owdew = SubPixewHowizontawWGB;
	intew_connectow->get_hw_state = intew_connectow_get_hw_state;

	/* attach connectow to encodew */
	intew_connectow_attach_encodew(intew_connectow, encodew);

	intew_dsi->panew_powew_off_time = ktime_get_boottime();

	intew_bios_init_panew_wate(dev_pwiv, &intew_connectow->panew, encodew->devdata, NUWW);

	mutex_wock(&dev_pwiv->dwm.mode_config.mutex);
	intew_panew_add_vbt_wfp_fixed_mode(intew_connectow);
	mutex_unwock(&dev_pwiv->dwm.mode_config.mutex);

	if (!intew_panew_pwefewwed_fixed_mode(intew_connectow)) {
		dwm_eww(&dev_pwiv->dwm, "DSI fixed mode info missing\n");
		goto eww;
	}

	intew_panew_init(intew_connectow, NUWW);

	intew_backwight_setup(intew_connectow, INVAWID_PIPE);

	if (intew_connectow->panew.vbt.dsi.config->duaw_wink)
		intew_dsi->powts = BIT(POWT_A) | BIT(POWT_B);
	ewse
		intew_dsi->powts = BIT(powt);

	if (dwm_WAWN_ON(&dev_pwiv->dwm, intew_connectow->panew.vbt.dsi.bw_powts & ~intew_dsi->powts))
		intew_connectow->panew.vbt.dsi.bw_powts &= intew_dsi->powts;

	if (dwm_WAWN_ON(&dev_pwiv->dwm, intew_connectow->panew.vbt.dsi.cabc_powts & ~intew_dsi->powts))
		intew_connectow->panew.vbt.dsi.cabc_powts &= intew_dsi->powts;

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		stwuct intew_dsi_host *host;

		host = intew_dsi_host_init(intew_dsi, &gen11_dsi_host_ops, powt);
		if (!host)
			goto eww;

		intew_dsi->dsi_hosts[powt] = host;
	}

	if (!intew_dsi_vbt_init(intew_dsi, MIPI_DSI_GENEWIC_PANEW_ID)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "no device found\n");
		goto eww;
	}

	icw_dphy_pawam_init(intew_dsi);

	icw_dsi_add_pwopewties(intew_connectow);
	wetuwn;

eww:
	dwm_connectow_cweanup(connectow);
	dwm_encodew_cweanup(&encodew->base);
	kfwee(intew_dsi);
	kfwee(intew_connectow);
}
