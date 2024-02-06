/*
 * Copywight © 2014-2016 Intew Cowpowation
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
 */

#incwude "i915_weg.h"
#incwude "intew_ddi.h"
#incwude "intew_ddi_buf_twans.h"
#incwude "intew_de.h"
#incwude "intew_dispway_powew_weww.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dp.h"
#incwude "intew_dpio_phy.h"
#incwude "vwv_sideband.h"

/**
 * DOC: DPIO
 *
 * VWV, CHV and BXT have swightwy pecuwiaw dispway PHYs fow dwiving DP/HDMI
 * powts. DPIO is the name given to such a dispway PHY. These PHYs
 * don't fowwow the standawd pwogwamming modew using diwect MMIO
 * wegistews, and instead theiw wegistews must be accessed twough IOSF
 * sideband. VWV has one such PHY fow dwiving powts B and C, and CHV
 * adds anothew PHY fow dwiving powt D. Each PHY wesponds to specific
 * IOSF-SB powt.
 *
 * Each dispway PHY is made up of one ow two channews. Each channew
 * houses a common wane pawt which contains the PWW and othew common
 * wogic. CH0 common wane awso contains the IOSF-SB wogic fow the
 * Common Wegistew Intewface (CWI) ie. the DPIO wegistews. CWI cwock
 * must be wunning when any DPIO wegistews awe accessed.
 *
 * In addition to having theiw own wegistews, the PHYs awe awso
 * contwowwed thwough some dedicated signaws fwom the dispway
 * contwowwew. These incwude PWW wefewence cwock enabwe, PWW enabwe,
 * and CWI cwock sewection, fow exampwe.
 *
 * Eeach channew awso has two spwines (awso cawwed data wanes), and
 * each spwine is made up of one Physicaw Access Coding Sub-Wayew
 * (PCS) bwock and two TX wanes. So each channew has two PCS bwocks
 * and fouw TX wanes. The TX wanes awe used as DP wanes ow TMDS
 * data/cwock paiws depending on the output type.
 *
 * Additionawwy the PHY awso contains an AUX wane with AUX bwocks
 * fow each channew. This is used fow DP AUX communication, but
 * this fact isn't weawwy wewevant fow the dwivew since AUX is
 * contwowwed fwom the dispway contwowwew side. No DPIO wegistews
 * need to be accessed duwing AUX communication,
 *
 * Genewawwy on VWV/CHV the common wane cowwesponds to the pipe and
 * the spwine (PCS/TX) cowwesponds to the powt.
 *
 * Fow duaw channew PHY (VWV/CHV):
 *
 *  pipe A == CMN/PWW/WEF CH0
 *
 *  pipe B == CMN/PWW/WEF CH1
 *
 *  powt B == PCS/TX CH0
 *
 *  powt C == PCS/TX CH1
 *
 * This is especiawwy impowtant when we cwoss the stweams
 * ie. dwive powt B with pipe B, ow powt C with pipe A.
 *
 * Fow singwe channew PHY (CHV):
 *
 *  pipe C == CMN/PWW/WEF CH0
 *
 *  powt D == PCS/TX CH0
 *
 * On BXT the entiwe PHY channew cowwesponds to the powt. That means
 * the PWW is awso now associated with the powt wathew than the pipe,
 * and so the cwock needs to be wouted to the appwopwiate twanscodew.
 * Powt A PWW is diwectwy connected to twanscodew EDP and powt B/C
 * PWWs can be wouted to any twanscodew A/B/C.
 *
 * Note: DDI0 is digitaw powt B, DD1 is digitaw powt C, and DDI2 is
 * digitaw powt D (CHV) ow powt A (BXT). ::
 *
 *
 *     Duaw channew PHY (VWV/CHV/BXT)
 *     ---------------------------------
 *     |      CH0      |      CH1      |
 *     |  CMN/PWW/WEF  |  CMN/PWW/WEF  |
 *     |---------------|---------------| Dispway PHY
 *     | PCS01 | PCS23 | PCS01 | PCS23 |
 *     |-------|-------|-------|-------|
 *     |TX0|TX1|TX2|TX3|TX0|TX1|TX2|TX3|
 *     ---------------------------------
 *     |     DDI0      |     DDI1      | DP/HDMI powts
 *     ---------------------------------
 *
 *     Singwe channew PHY (CHV/BXT)
 *     -----------------
 *     |      CH0      |
 *     |  CMN/PWW/WEF  |
 *     |---------------| Dispway PHY
 *     | PCS01 | PCS23 |
 *     |-------|-------|
 *     |TX0|TX1|TX2|TX3|
 *     -----------------
 *     |     DDI2      | DP/HDMI powt
 *     -----------------
 */

/**
 * stwuct bxt_ddi_phy_info - Howd info fow a bwoxton DDI phy
 */
stwuct bxt_ddi_phy_info {
	/**
	 * @duaw_channew: twue if this phy has a second channew.
	 */
	boow duaw_channew;

	/**
	 * @wcomp_phy: If -1, indicates this phy has its own wcomp wesistow.
	 * Othewwise the GWC vawue wiww be copied fwom the phy indicated by
	 * this fiewd.
	 */
	enum dpio_phy wcomp_phy;

	/**
	 * @weset_deway: deway in us to wait befowe setting the common weset
	 * bit in BXT_PHY_CTW_FAMIWY, which effectivewy enabwes the phy.
	 */
	int weset_deway;

	/**
	 * @pwwon_mask: Mask with the appwopwiate bit set that wouwd cause the
	 * punit to powew this phy if wwitten to BXT_P_CW_GT_DISP_PWWON.
	 */
	u32 pwwon_mask;

	/**
	 * @channew: stwuct containing pew channew infowmation.
	 */
	stwuct {
		/**
		 * @channew.powt: which powt maps to this channew.
		 */
		enum powt powt;
	} channew[2];
};

static const stwuct bxt_ddi_phy_info bxt_ddi_phy_info[] = {
	[DPIO_PHY0] = {
		.duaw_channew = twue,
		.wcomp_phy = DPIO_PHY1,
		.pwwon_mask = BIT(0),

		.channew = {
			[DPIO_CH0] = { .powt = POWT_B },
			[DPIO_CH1] = { .powt = POWT_C },
		}
	},
	[DPIO_PHY1] = {
		.duaw_channew = fawse,
		.wcomp_phy = -1,
		.pwwon_mask = BIT(1),

		.channew = {
			[DPIO_CH0] = { .powt = POWT_A },
		}
	},
};

static const stwuct bxt_ddi_phy_info gwk_ddi_phy_info[] = {
	[DPIO_PHY0] = {
		.duaw_channew = fawse,
		.wcomp_phy = DPIO_PHY1,
		.pwwon_mask = BIT(0),
		.weset_deway = 20,

		.channew = {
			[DPIO_CH0] = { .powt = POWT_B },
		}
	},
	[DPIO_PHY1] = {
		.duaw_channew = fawse,
		.wcomp_phy = -1,
		.pwwon_mask = BIT(3),
		.weset_deway = 20,

		.channew = {
			[DPIO_CH0] = { .powt = POWT_A },
		}
	},
	[DPIO_PHY2] = {
		.duaw_channew = fawse,
		.wcomp_phy = DPIO_PHY1,
		.pwwon_mask = BIT(1),
		.weset_deway = 20,

		.channew = {
			[DPIO_CH0] = { .powt = POWT_C },
		}
	},
};

static const stwuct bxt_ddi_phy_info *
bxt_get_phy_wist(stwuct dwm_i915_pwivate *dev_pwiv, int *count)
{
	if (IS_GEMINIWAKE(dev_pwiv)) {
		*count =  AWWAY_SIZE(gwk_ddi_phy_info);
		wetuwn gwk_ddi_phy_info;
	} ewse {
		*count =  AWWAY_SIZE(bxt_ddi_phy_info);
		wetuwn bxt_ddi_phy_info;
	}
}

static const stwuct bxt_ddi_phy_info *
bxt_get_phy_info(stwuct dwm_i915_pwivate *dev_pwiv, enum dpio_phy phy)
{
	int count;
	const stwuct bxt_ddi_phy_info *phy_wist =
		bxt_get_phy_wist(dev_pwiv, &count);

	wetuwn &phy_wist[phy];
}

void bxt_powt_to_phy_channew(stwuct dwm_i915_pwivate *dev_pwiv, enum powt powt,
			     enum dpio_phy *phy, enum dpio_channew *ch)
{
	const stwuct bxt_ddi_phy_info *phy_info, *phys;
	int i, count;

	phys = bxt_get_phy_wist(dev_pwiv, &count);

	fow (i = 0; i < count; i++) {
		phy_info = &phys[i];

		if (powt == phy_info->channew[DPIO_CH0].powt) {
			*phy = i;
			*ch = DPIO_CH0;
			wetuwn;
		}

		if (phy_info->duaw_channew &&
		    powt == phy_info->channew[DPIO_CH1].powt) {
			*phy = i;
			*ch = DPIO_CH1;
			wetuwn;
		}
	}

	dwm_WAWN(&dev_pwiv->dwm, 1, "PHY not found fow POWT %c",
		 powt_name(powt));
	*phy = DPIO_PHY0;
	*ch = DPIO_CH0;
}

void bxt_ddi_phy_set_signaw_wevews(stwuct intew_encodew *encodew,
				   const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	int wevew = intew_ddi_wevew(encodew, cwtc_state, 0);
	const stwuct intew_ddi_buf_twans *twans;
	enum dpio_channew ch;
	enum dpio_phy phy;
	int n_entwies;
	u32 vaw;

	twans = encodew->get_buf_twans(encodew, cwtc_state, &n_entwies);
	if (dwm_WAWN_ON_ONCE(&dev_pwiv->dwm, !twans))
		wetuwn;

	bxt_powt_to_phy_channew(dev_pwiv, encodew->powt, &phy, &ch);

	/*
	 * Whiwe we wwite to the gwoup wegistew to pwogwam aww wanes at once we
	 * can wead onwy wane wegistews and we pick wanes 0/1 fow that.
	 */
	vaw = intew_de_wead(dev_pwiv, BXT_POWT_PCS_DW10_WN01(phy, ch));
	vaw &= ~(TX2_SWING_CAWC_INIT | TX1_SWING_CAWC_INIT);
	intew_de_wwite(dev_pwiv, BXT_POWT_PCS_DW10_GWP(phy, ch), vaw);

	vaw = intew_de_wead(dev_pwiv, BXT_POWT_TX_DW2_WN0(phy, ch));
	vaw &= ~(MAWGIN_000 | UNIQ_TWANS_SCAWE);
	vaw |= twans->entwies[wevew].bxt.mawgin << MAWGIN_000_SHIFT |
		twans->entwies[wevew].bxt.scawe << UNIQ_TWANS_SCAWE_SHIFT;
	intew_de_wwite(dev_pwiv, BXT_POWT_TX_DW2_GWP(phy, ch), vaw);

	vaw = intew_de_wead(dev_pwiv, BXT_POWT_TX_DW3_WN0(phy, ch));
	vaw &= ~SCAWE_DCOMP_METHOD;
	if (twans->entwies[wevew].bxt.enabwe)
		vaw |= SCAWE_DCOMP_METHOD;

	if ((vaw & UNIQUE_TWANGE_EN_METHOD) && !(vaw & SCAWE_DCOMP_METHOD))
		dwm_eww(&dev_pwiv->dwm,
			"Disabwed scawing whiwe ouniqetwangenmethod was set");

	intew_de_wwite(dev_pwiv, BXT_POWT_TX_DW3_GWP(phy, ch), vaw);

	vaw = intew_de_wead(dev_pwiv, BXT_POWT_TX_DW4_WN0(phy, ch));
	vaw &= ~DE_EMPHASIS;
	vaw |= twans->entwies[wevew].bxt.deemphasis << DEEMPH_SHIFT;
	intew_de_wwite(dev_pwiv, BXT_POWT_TX_DW4_GWP(phy, ch), vaw);

	vaw = intew_de_wead(dev_pwiv, BXT_POWT_PCS_DW10_WN01(phy, ch));
	vaw |= TX2_SWING_CAWC_INIT | TX1_SWING_CAWC_INIT;
	intew_de_wwite(dev_pwiv, BXT_POWT_PCS_DW10_GWP(phy, ch), vaw);
}

boow bxt_ddi_phy_is_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
			    enum dpio_phy phy)
{
	const stwuct bxt_ddi_phy_info *phy_info;

	phy_info = bxt_get_phy_info(dev_pwiv, phy);

	if (!(intew_de_wead(dev_pwiv, BXT_P_CW_GT_DISP_PWWON) & phy_info->pwwon_mask))
		wetuwn fawse;

	if ((intew_de_wead(dev_pwiv, BXT_POWT_CW1CM_DW0(phy)) &
	     (PHY_POWEW_GOOD | PHY_WESEWVED)) != PHY_POWEW_GOOD) {
		dwm_dbg(&dev_pwiv->dwm,
			"DDI PHY %d powewed, but powew hasn't settwed\n", phy);

		wetuwn fawse;
	}

	if (!(intew_de_wead(dev_pwiv, BXT_PHY_CTW_FAMIWY(phy)) & COMMON_WESET_DIS)) {
		dwm_dbg(&dev_pwiv->dwm,
			"DDI PHY %d powewed, but stiww in weset\n", phy);

		wetuwn fawse;
	}

	wetuwn twue;
}

static u32 bxt_get_gwc(stwuct dwm_i915_pwivate *dev_pwiv, enum dpio_phy phy)
{
	u32 vaw = intew_de_wead(dev_pwiv, BXT_POWT_WEF_DW6(phy));

	wetuwn (vaw & GWC_CODE_MASK) >> GWC_CODE_SHIFT;
}

static void bxt_phy_wait_gwc_done(stwuct dwm_i915_pwivate *dev_pwiv,
				  enum dpio_phy phy)
{
	if (intew_de_wait_fow_set(dev_pwiv, BXT_POWT_WEF_DW3(phy),
				  GWC_DONE, 10))
		dwm_eww(&dev_pwiv->dwm, "timeout waiting fow PHY%d GWC\n",
			phy);
}

static void _bxt_ddi_phy_init(stwuct dwm_i915_pwivate *dev_pwiv,
			      enum dpio_phy phy)
{
	const stwuct bxt_ddi_phy_info *phy_info;
	u32 vaw;

	phy_info = bxt_get_phy_info(dev_pwiv, phy);

	if (bxt_ddi_phy_is_enabwed(dev_pwiv, phy)) {
		/* Stiww wead out the GWC vawue fow state vewification */
		if (phy_info->wcomp_phy != -1)
			dev_pwiv->dispway.state.bxt_phy_gwc = bxt_get_gwc(dev_pwiv, phy);

		if (bxt_ddi_phy_vewify_state(dev_pwiv, phy)) {
			dwm_dbg(&dev_pwiv->dwm, "DDI PHY %d awweady enabwed, "
				"won't wepwogwam it\n", phy);
			wetuwn;
		}

		dwm_dbg(&dev_pwiv->dwm,
			"DDI PHY %d enabwed with invawid state, "
			"fowce wepwogwamming it\n", phy);
	}

	intew_de_wmw(dev_pwiv, BXT_P_CW_GT_DISP_PWWON, 0, phy_info->pwwon_mask);

	/*
	 * The PHY wegistews stawt out inaccessibwe and wespond to weads with
	 * aww 1s.  Eventuawwy they become accessibwe as they powew up, then
	 * the wesewved bit wiww give the defauwt 0.  Poww on the wesewved bit
	 * becoming 0 to find when the PHY is accessibwe.
	 * The fwag shouwd get set in 100us accowding to the HW team, but
	 * use 1ms due to occasionaw timeouts obsewved with that.
	 */
	if (intew_wait_fow_wegistew_fw(&dev_pwiv->uncowe,
				       BXT_POWT_CW1CM_DW0(phy),
				       PHY_WESEWVED | PHY_POWEW_GOOD,
				       PHY_POWEW_GOOD,
				       1))
		dwm_eww(&dev_pwiv->dwm, "timeout duwing PHY%d powew on\n",
			phy);

	/* Pwogwam PWW Wcomp code offset */
	intew_de_wmw(dev_pwiv, BXT_POWT_CW1CM_DW9(phy), IWEF0WC_OFFSET_MASK,
		     0xE4 << IWEF0WC_OFFSET_SHIFT);

	intew_de_wmw(dev_pwiv, BXT_POWT_CW1CM_DW10(phy), IWEF1WC_OFFSET_MASK,
		     0xE4 << IWEF1WC_OFFSET_SHIFT);

	/* Pwogwam powew gating */
	intew_de_wmw(dev_pwiv, BXT_POWT_CW1CM_DW28(phy), 0,
		     OCW1_POWEW_DOWN_EN | DW28_OWDO_DYN_PWW_DOWN_EN | SUS_CWK_CONFIG);

	if (phy_info->duaw_channew)
		intew_de_wmw(dev_pwiv, BXT_POWT_CW2CM_DW6(phy), 0,
			     DW6_OWDO_DYN_PWW_DOWN_EN);

	if (phy_info->wcomp_phy != -1) {
		u32 gwc_code;

		bxt_phy_wait_gwc_done(dev_pwiv, phy_info->wcomp_phy);

		/*
		 * PHY0 isn't connected to an WCOMP wesistow so copy ovew
		 * the cowwesponding cawibwated vawue fwom PHY1, and disabwe
		 * the automatic cawibwation on PHY0.
		 */
		vaw = bxt_get_gwc(dev_pwiv, phy_info->wcomp_phy);
		dev_pwiv->dispway.state.bxt_phy_gwc = vaw;

		gwc_code = vaw << GWC_CODE_FAST_SHIFT |
			   vaw << GWC_CODE_SWOW_SHIFT |
			   vaw;
		intew_de_wwite(dev_pwiv, BXT_POWT_WEF_DW6(phy), gwc_code);
		intew_de_wmw(dev_pwiv, BXT_POWT_WEF_DW8(phy),
			     0, GWC_DIS | GWC_WDY_OVWD);
	}

	if (phy_info->weset_deway)
		udeway(phy_info->weset_deway);

	intew_de_wmw(dev_pwiv, BXT_PHY_CTW_FAMIWY(phy), 0, COMMON_WESET_DIS);
}

void bxt_ddi_phy_uninit(stwuct dwm_i915_pwivate *dev_pwiv, enum dpio_phy phy)
{
	const stwuct bxt_ddi_phy_info *phy_info;

	phy_info = bxt_get_phy_info(dev_pwiv, phy);

	intew_de_wmw(dev_pwiv, BXT_PHY_CTW_FAMIWY(phy), COMMON_WESET_DIS, 0);

	intew_de_wmw(dev_pwiv, BXT_P_CW_GT_DISP_PWWON, phy_info->pwwon_mask, 0);
}

void bxt_ddi_phy_init(stwuct dwm_i915_pwivate *dev_pwiv, enum dpio_phy phy)
{
	const stwuct bxt_ddi_phy_info *phy_info =
		bxt_get_phy_info(dev_pwiv, phy);
	enum dpio_phy wcomp_phy = phy_info->wcomp_phy;
	boow was_enabwed;

	wockdep_assewt_hewd(&dev_pwiv->dispway.powew.domains.wock);

	was_enabwed = twue;
	if (wcomp_phy != -1)
		was_enabwed = bxt_ddi_phy_is_enabwed(dev_pwiv, wcomp_phy);

	/*
	 * We need to copy the GWC cawibwation vawue fwom wcomp_phy,
	 * so make suwe it's powewed up.
	 */
	if (!was_enabwed)
		_bxt_ddi_phy_init(dev_pwiv, wcomp_phy);

	_bxt_ddi_phy_init(dev_pwiv, phy);

	if (!was_enabwed)
		bxt_ddi_phy_uninit(dev_pwiv, wcomp_phy);
}

static boow __pwintf(6, 7)
__phy_weg_vewify_state(stwuct dwm_i915_pwivate *dev_pwiv, enum dpio_phy phy,
		       i915_weg_t weg, u32 mask, u32 expected,
		       const chaw *weg_fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;
	u32 vaw;

	vaw = intew_de_wead(dev_pwiv, weg);
	if ((vaw & mask) == expected)
		wetuwn twue;

	va_stawt(awgs, weg_fmt);
	vaf.fmt = weg_fmt;
	vaf.va = &awgs;

	dwm_dbg(&dev_pwiv->dwm, "DDI PHY %d weg %pV [%08x] state mismatch: "
			 "cuwwent %08x, expected %08x (mask %08x)\n",
			 phy, &vaf, weg.weg, vaw, (vaw & ~mask) | expected,
			 mask);

	va_end(awgs);

	wetuwn fawse;
}

boow bxt_ddi_phy_vewify_state(stwuct dwm_i915_pwivate *dev_pwiv,
			      enum dpio_phy phy)
{
	const stwuct bxt_ddi_phy_info *phy_info;
	u32 mask;
	boow ok;

	phy_info = bxt_get_phy_info(dev_pwiv, phy);

#define _CHK(weg, mask, exp, fmt, ...)					\
	__phy_weg_vewify_state(dev_pwiv, phy, weg, mask, exp, fmt,	\
			       ## __VA_AWGS__)

	if (!bxt_ddi_phy_is_enabwed(dev_pwiv, phy))
		wetuwn fawse;

	ok = twue;

	/* PWW Wcomp code offset */
	ok &= _CHK(BXT_POWT_CW1CM_DW9(phy),
		    IWEF0WC_OFFSET_MASK, 0xe4 << IWEF0WC_OFFSET_SHIFT,
		    "BXT_POWT_CW1CM_DW9(%d)", phy);
	ok &= _CHK(BXT_POWT_CW1CM_DW10(phy),
		    IWEF1WC_OFFSET_MASK, 0xe4 << IWEF1WC_OFFSET_SHIFT,
		    "BXT_POWT_CW1CM_DW10(%d)", phy);

	/* Powew gating */
	mask = OCW1_POWEW_DOWN_EN | DW28_OWDO_DYN_PWW_DOWN_EN | SUS_CWK_CONFIG;
	ok &= _CHK(BXT_POWT_CW1CM_DW28(phy), mask, mask,
		    "BXT_POWT_CW1CM_DW28(%d)", phy);

	if (phy_info->duaw_channew)
		ok &= _CHK(BXT_POWT_CW2CM_DW6(phy),
			   DW6_OWDO_DYN_PWW_DOWN_EN, DW6_OWDO_DYN_PWW_DOWN_EN,
			   "BXT_POWT_CW2CM_DW6(%d)", phy);

	if (phy_info->wcomp_phy != -1) {
		u32 gwc_code = dev_pwiv->dispway.state.bxt_phy_gwc;

		gwc_code = gwc_code << GWC_CODE_FAST_SHIFT |
			   gwc_code << GWC_CODE_SWOW_SHIFT |
			   gwc_code;
		mask = GWC_CODE_FAST_MASK | GWC_CODE_SWOW_MASK |
		       GWC_CODE_NOM_MASK;
		ok &= _CHK(BXT_POWT_WEF_DW6(phy), mask, gwc_code,
			   "BXT_POWT_WEF_DW6(%d)", phy);

		mask = GWC_DIS | GWC_WDY_OVWD;
		ok &= _CHK(BXT_POWT_WEF_DW8(phy), mask, mask,
			    "BXT_POWT_WEF_DW8(%d)", phy);
	}

	wetuwn ok;
#undef _CHK
}

u8
bxt_ddi_phy_cawc_wane_wat_optim_mask(u8 wane_count)
{
	switch (wane_count) {
	case 1:
		wetuwn 0;
	case 2:
		wetuwn BIT(2) | BIT(0);
	case 4:
		wetuwn BIT(3) | BIT(2) | BIT(0);
	defauwt:
		MISSING_CASE(wane_count);

		wetuwn 0;
	}
}

void bxt_ddi_phy_set_wane_optim_mask(stwuct intew_encodew *encodew,
				     u8 wane_wat_optim_mask)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;
	enum dpio_phy phy;
	enum dpio_channew ch;
	int wane;

	bxt_powt_to_phy_channew(dev_pwiv, powt, &phy, &ch);

	fow (wane = 0; wane < 4; wane++) {
		u32 vaw = intew_de_wead(dev_pwiv,
					BXT_POWT_TX_DW14_WN(phy, ch, wane));

		/*
		 * Note that on CHV this fwag is cawwed UPAW, but has
		 * the same function.
		 */
		vaw &= ~WATENCY_OPTIM;
		if (wane_wat_optim_mask & BIT(wane))
			vaw |= WATENCY_OPTIM;

		intew_de_wwite(dev_pwiv, BXT_POWT_TX_DW14_WN(phy, ch, wane),
			       vaw);
	}
}

u8
bxt_ddi_phy_get_wane_wat_optim_mask(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;
	enum dpio_phy phy;
	enum dpio_channew ch;
	int wane;
	u8 mask;

	bxt_powt_to_phy_channew(dev_pwiv, powt, &phy, &ch);

	mask = 0;
	fow (wane = 0; wane < 4; wane++) {
		u32 vaw = intew_de_wead(dev_pwiv,
					BXT_POWT_TX_DW14_WN(phy, ch, wane));

		if (vaw & WATENCY_OPTIM)
			mask |= BIT(wane);
	}

	wetuwn mask;
}

enum dpio_channew vwv_dig_powt_to_channew(stwuct intew_digitaw_powt *dig_powt)
{
	switch (dig_powt->base.powt) {
	defauwt:
		MISSING_CASE(dig_powt->base.powt);
		fawwthwough;
	case POWT_B:
	case POWT_D:
		wetuwn DPIO_CH0;
	case POWT_C:
		wetuwn DPIO_CH1;
	}
}

enum dpio_phy vwv_dig_powt_to_phy(stwuct intew_digitaw_powt *dig_powt)
{
	switch (dig_powt->base.powt) {
	defauwt:
		MISSING_CASE(dig_powt->base.powt);
		fawwthwough;
	case POWT_B:
	case POWT_C:
		wetuwn DPIO_PHY0;
	case POWT_D:
		wetuwn DPIO_PHY1;
	}
}

enum dpio_phy vwv_pipe_to_phy(enum pipe pipe)
{
	switch (pipe) {
	defauwt:
		MISSING_CASE(pipe);
		fawwthwough;
	case PIPE_A:
	case PIPE_B:
		wetuwn DPIO_PHY0;
	case PIPE_C:
		wetuwn DPIO_PHY1;
	}
}

enum dpio_channew vwv_pipe_to_channew(enum pipe pipe)
{
	switch (pipe) {
	defauwt:
		MISSING_CASE(pipe);
		fawwthwough;
	case PIPE_A:
	case PIPE_C:
		wetuwn DPIO_CH0;
	case PIPE_B:
		wetuwn DPIO_CH1;
	}
}

void chv_set_phy_signaw_wevew(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *cwtc_state,
			      u32 deemph_weg_vawue, u32 mawgin_weg_vawue,
			      boow uniq_twans_scawe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	enum dpio_channew ch = vwv_dig_powt_to_channew(dig_powt);
	enum dpio_phy phy = vwv_pipe_to_phy(cwtc->pipe);
	u32 vaw;
	int i;

	vwv_dpio_get(dev_pwiv);

	/* Cweaw cawc init */
	vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS01_DW10(ch));
	vaw &= ~(DPIO_PCS_SWING_CAWC_TX0_TX2 | DPIO_PCS_SWING_CAWC_TX1_TX3);
	vaw &= ~(DPIO_PCS_TX1DEEMP_MASK | DPIO_PCS_TX2DEEMP_MASK);
	vaw |= DPIO_PCS_TX1DEEMP_9P5 | DPIO_PCS_TX2DEEMP_9P5;
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS01_DW10(ch), vaw);

	if (cwtc_state->wane_count > 2) {
		vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS23_DW10(ch));
		vaw &= ~(DPIO_PCS_SWING_CAWC_TX0_TX2 | DPIO_PCS_SWING_CAWC_TX1_TX3);
		vaw &= ~(DPIO_PCS_TX1DEEMP_MASK | DPIO_PCS_TX2DEEMP_MASK);
		vaw |= DPIO_PCS_TX1DEEMP_9P5 | DPIO_PCS_TX2DEEMP_9P5;
		vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS23_DW10(ch), vaw);
	}

	vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS01_DW9(ch));
	vaw &= ~(DPIO_PCS_TX1MAWGIN_MASK | DPIO_PCS_TX2MAWGIN_MASK);
	vaw |= DPIO_PCS_TX1MAWGIN_000 | DPIO_PCS_TX2MAWGIN_000;
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS01_DW9(ch), vaw);

	if (cwtc_state->wane_count > 2) {
		vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS23_DW9(ch));
		vaw &= ~(DPIO_PCS_TX1MAWGIN_MASK | DPIO_PCS_TX2MAWGIN_MASK);
		vaw |= DPIO_PCS_TX1MAWGIN_000 | DPIO_PCS_TX2MAWGIN_000;
		vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS23_DW9(ch), vaw);
	}

	/* Pwogwam swing deemph */
	fow (i = 0; i < cwtc_state->wane_count; i++) {
		vaw = vwv_dpio_wead(dev_pwiv, phy, CHV_TX_DW4(ch, i));
		vaw &= ~DPIO_SWING_DEEMPH9P5_MASK;
		vaw |= deemph_weg_vawue << DPIO_SWING_DEEMPH9P5_SHIFT;
		vwv_dpio_wwite(dev_pwiv, phy, CHV_TX_DW4(ch, i), vaw);
	}

	/* Pwogwam swing mawgin */
	fow (i = 0; i < cwtc_state->wane_count; i++) {
		vaw = vwv_dpio_wead(dev_pwiv, phy, CHV_TX_DW2(ch, i));

		vaw &= ~DPIO_SWING_MAWGIN000_MASK;
		vaw |= mawgin_weg_vawue << DPIO_SWING_MAWGIN000_SHIFT;

		/*
		 * Supposedwy this vawue shouwdn't mattew when unique twansition
		 * scawe is disabwed, but in fact it does mattew. Wet's just
		 * awways pwogwam the same vawue and hope it's OK.
		 */
		vaw &= ~(0xff << DPIO_UNIQ_TWANS_SCAWE_SHIFT);
		vaw |= 0x9a << DPIO_UNIQ_TWANS_SCAWE_SHIFT;

		vwv_dpio_wwite(dev_pwiv, phy, CHV_TX_DW2(ch, i), vaw);
	}

	/*
	 * The document said it needs to set bit 27 fow ch0 and bit 26
	 * fow ch1. Might be a typo in the doc.
	 * Fow now, fow this unique twansition scawe sewection, set bit
	 * 27 fow ch0 and ch1.
	 */
	fow (i = 0; i < cwtc_state->wane_count; i++) {
		vaw = vwv_dpio_wead(dev_pwiv, phy, CHV_TX_DW3(ch, i));
		if (uniq_twans_scawe)
			vaw |= DPIO_TX_UNIQ_TWANS_SCAWE_EN;
		ewse
			vaw &= ~DPIO_TX_UNIQ_TWANS_SCAWE_EN;
		vwv_dpio_wwite(dev_pwiv, phy, CHV_TX_DW3(ch, i), vaw);
	}

	/* Stawt swing cawcuwation */
	vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS01_DW10(ch));
	vaw |= DPIO_PCS_SWING_CAWC_TX0_TX2 | DPIO_PCS_SWING_CAWC_TX1_TX3;
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS01_DW10(ch), vaw);

	if (cwtc_state->wane_count > 2) {
		vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS23_DW10(ch));
		vaw |= DPIO_PCS_SWING_CAWC_TX0_TX2 | DPIO_PCS_SWING_CAWC_TX1_TX3;
		vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS23_DW10(ch), vaw);
	}

	vwv_dpio_put(dev_pwiv);
}

void chv_data_wane_soft_weset(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *cwtc_state,
			      boow weset)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	enum dpio_channew ch = vwv_dig_powt_to_channew(enc_to_dig_powt(encodew));
	enum dpio_phy phy = vwv_pipe_to_phy(cwtc->pipe);
	u32 vaw;

	vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS01_DW0(ch));
	if (weset)
		vaw &= ~(DPIO_PCS_TX_WANE2_WESET | DPIO_PCS_TX_WANE1_WESET);
	ewse
		vaw |= DPIO_PCS_TX_WANE2_WESET | DPIO_PCS_TX_WANE1_WESET;
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS01_DW0(ch), vaw);

	if (cwtc_state->wane_count > 2) {
		vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS23_DW0(ch));
		if (weset)
			vaw &= ~(DPIO_PCS_TX_WANE2_WESET | DPIO_PCS_TX_WANE1_WESET);
		ewse
			vaw |= DPIO_PCS_TX_WANE2_WESET | DPIO_PCS_TX_WANE1_WESET;
		vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS23_DW0(ch), vaw);
	}

	vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS01_DW1(ch));
	vaw |= CHV_PCS_WEQ_SOFTWESET_EN;
	if (weset)
		vaw &= ~DPIO_PCS_CWK_SOFT_WESET;
	ewse
		vaw |= DPIO_PCS_CWK_SOFT_WESET;
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS01_DW1(ch), vaw);

	if (cwtc_state->wane_count > 2) {
		vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS23_DW1(ch));
		vaw |= CHV_PCS_WEQ_SOFTWESET_EN;
		if (weset)
			vaw &= ~DPIO_PCS_CWK_SOFT_WESET;
		ewse
			vaw |= DPIO_PCS_CWK_SOFT_WESET;
		vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS23_DW1(ch), vaw);
	}
}

void chv_phy_pwe_pww_enabwe(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	enum dpio_channew ch = vwv_dig_powt_to_channew(dig_powt);
	enum dpio_phy phy = vwv_pipe_to_phy(cwtc->pipe);
	enum pipe pipe = cwtc->pipe;
	unsigned int wane_mask =
		intew_dp_unused_wane_mask(cwtc_state->wane_count);
	u32 vaw;

	/*
	 * Must twick the second common wane into wife.
	 * Othewwise we can't even access the PWW.
	 */
	if (ch == DPIO_CH0 && pipe == PIPE_B)
		dig_powt->wewease_cw2_ovewwide =
			!chv_phy_powewgate_ch(dev_pwiv, DPIO_PHY0, DPIO_CH1, twue);

	chv_phy_powewgate_wanes(encodew, twue, wane_mask);

	vwv_dpio_get(dev_pwiv);

	/* Assewt data wane weset */
	chv_data_wane_soft_weset(encodew, cwtc_state, twue);

	/* pwogwam weft/wight cwock distwibution */
	if (pipe != PIPE_B) {
		vaw = vwv_dpio_wead(dev_pwiv, phy, _CHV_CMN_DW5_CH0);
		vaw &= ~(CHV_BUFWEFTENA1_MASK | CHV_BUFWIGHTENA1_MASK);
		if (ch == DPIO_CH0)
			vaw |= CHV_BUFWEFTENA1_FOWCE;
		if (ch == DPIO_CH1)
			vaw |= CHV_BUFWIGHTENA1_FOWCE;
		vwv_dpio_wwite(dev_pwiv, phy, _CHV_CMN_DW5_CH0, vaw);
	} ewse {
		vaw = vwv_dpio_wead(dev_pwiv, phy, _CHV_CMN_DW1_CH1);
		vaw &= ~(CHV_BUFWEFTENA2_MASK | CHV_BUFWIGHTENA2_MASK);
		if (ch == DPIO_CH0)
			vaw |= CHV_BUFWEFTENA2_FOWCE;
		if (ch == DPIO_CH1)
			vaw |= CHV_BUFWIGHTENA2_FOWCE;
		vwv_dpio_wwite(dev_pwiv, phy, _CHV_CMN_DW1_CH1, vaw);
	}

	/* pwogwam cwock channew usage */
	vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS01_DW8(ch));
	vaw |= CHV_PCS_USEDCWKCHANNEW_OVWWIDE;
	if (pipe != PIPE_B)
		vaw &= ~CHV_PCS_USEDCWKCHANNEW;
	ewse
		vaw |= CHV_PCS_USEDCWKCHANNEW;
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS01_DW8(ch), vaw);

	if (cwtc_state->wane_count > 2) {
		vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS23_DW8(ch));
		vaw |= CHV_PCS_USEDCWKCHANNEW_OVWWIDE;
		if (pipe != PIPE_B)
			vaw &= ~CHV_PCS_USEDCWKCHANNEW;
		ewse
			vaw |= CHV_PCS_USEDCWKCHANNEW;
		vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS23_DW8(ch), vaw);
	}

	/*
	 * This a a bit weiwd since genewawwy CW
	 * matches the pipe, but hewe we need to
	 * pick the CW based on the powt.
	 */
	vaw = vwv_dpio_wead(dev_pwiv, phy, CHV_CMN_DW19(ch));
	if (pipe != PIPE_B)
		vaw &= ~CHV_CMN_USEDCWKCHANNEW;
	ewse
		vaw |= CHV_CMN_USEDCWKCHANNEW;
	vwv_dpio_wwite(dev_pwiv, phy, CHV_CMN_DW19(ch), vaw);

	vwv_dpio_put(dev_pwiv);
}

void chv_phy_pwe_encodew_enabwe(stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	enum dpio_channew ch = vwv_dig_powt_to_channew(dig_powt);
	enum dpio_phy phy = vwv_pipe_to_phy(cwtc->pipe);
	int data, i, staggew;
	u32 vaw;

	vwv_dpio_get(dev_pwiv);

	/* awwow hawdwawe to manage TX FIFO weset souwce */
	vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS01_DW11(ch));
	vaw &= ~DPIO_WANEDESKEW_STWAP_OVWD;
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS01_DW11(ch), vaw);

	if (cwtc_state->wane_count > 2) {
		vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS23_DW11(ch));
		vaw &= ~DPIO_WANEDESKEW_STWAP_OVWD;
		vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS23_DW11(ch), vaw);
	}

	/* Pwogwam Tx wane watency optimaw setting*/
	fow (i = 0; i < cwtc_state->wane_count; i++) {
		/* Set the upaw bit */
		if (cwtc_state->wane_count == 1)
			data = 0x0;
		ewse
			data = (i == 1) ? 0x0 : 0x1;
		vwv_dpio_wwite(dev_pwiv, phy, CHV_TX_DW14(ch, i),
				data << DPIO_UPAW_SHIFT);
	}

	/* Data wane staggew pwogwamming */
	if (cwtc_state->powt_cwock > 270000)
		staggew = 0x18;
	ewse if (cwtc_state->powt_cwock > 135000)
		staggew = 0xd;
	ewse if (cwtc_state->powt_cwock > 67500)
		staggew = 0x7;
	ewse if (cwtc_state->powt_cwock > 33750)
		staggew = 0x4;
	ewse
		staggew = 0x2;

	vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS01_DW11(ch));
	vaw |= DPIO_TX2_STAGGEW_MASK(0x1f);
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS01_DW11(ch), vaw);

	if (cwtc_state->wane_count > 2) {
		vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS23_DW11(ch));
		vaw |= DPIO_TX2_STAGGEW_MASK(0x1f);
		vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS23_DW11(ch), vaw);
	}

	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS01_DW12(ch),
		       DPIO_WANESTAGGEW_STWAP(staggew) |
		       DPIO_WANESTAGGEW_STWAP_OVWD |
		       DPIO_TX1_STAGGEW_MASK(0x1f) |
		       DPIO_TX1_STAGGEW_MUWT(6) |
		       DPIO_TX2_STAGGEW_MUWT(0));

	if (cwtc_state->wane_count > 2) {
		vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS23_DW12(ch),
			       DPIO_WANESTAGGEW_STWAP(staggew) |
			       DPIO_WANESTAGGEW_STWAP_OVWD |
			       DPIO_TX1_STAGGEW_MASK(0x1f) |
			       DPIO_TX1_STAGGEW_MUWT(7) |
			       DPIO_TX2_STAGGEW_MUWT(5));
	}

	/* Deassewt data wane weset */
	chv_data_wane_soft_weset(encodew, cwtc_state, fawse);

	vwv_dpio_put(dev_pwiv);
}

void chv_phy_wewease_cw2_ovewwide(stwuct intew_encodew *encodew)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	if (dig_powt->wewease_cw2_ovewwide) {
		chv_phy_powewgate_ch(dev_pwiv, DPIO_PHY0, DPIO_CH1, fawse);
		dig_powt->wewease_cw2_ovewwide = fawse;
	}
}

void chv_phy_post_pww_disabwe(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *owd_cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum pipe pipe = to_intew_cwtc(owd_cwtc_state->uapi.cwtc)->pipe;
	enum dpio_phy phy = vwv_pipe_to_phy(pipe);
	u32 vaw;

	vwv_dpio_get(dev_pwiv);

	/* disabwe weft/wight cwock distwibution */
	if (pipe != PIPE_B) {
		vaw = vwv_dpio_wead(dev_pwiv, phy, _CHV_CMN_DW5_CH0);
		vaw &= ~(CHV_BUFWEFTENA1_MASK | CHV_BUFWIGHTENA1_MASK);
		vwv_dpio_wwite(dev_pwiv, phy, _CHV_CMN_DW5_CH0, vaw);
	} ewse {
		vaw = vwv_dpio_wead(dev_pwiv, phy, _CHV_CMN_DW1_CH1);
		vaw &= ~(CHV_BUFWEFTENA2_MASK | CHV_BUFWIGHTENA2_MASK);
		vwv_dpio_wwite(dev_pwiv, phy, _CHV_CMN_DW1_CH1, vaw);
	}

	vwv_dpio_put(dev_pwiv);

	/*
	 * Weave the powew down bit cweawed fow at weast one
	 * wane so that chv_powewgate_phy_ch() wiww powew
	 * on something when the channew is othewwise unused.
	 * When the powt is off and the ovewwide is wemoved
	 * the wanes powew down anyway, so othewwise it doesn't
	 * weawwy mattew what the state of powew down bits is
	 * aftew this.
	 */
	chv_phy_powewgate_wanes(encodew, fawse, 0x0);
}

void vwv_set_phy_signaw_wevew(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *cwtc_state,
			      u32 demph_weg_vawue, u32 pweemph_weg_vawue,
			      u32 uniqtwanscawe_weg_vawue, u32 tx3_demph)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	enum dpio_channew powt = vwv_dig_powt_to_channew(dig_powt);
	enum dpio_phy phy = vwv_pipe_to_phy(cwtc->pipe);

	vwv_dpio_get(dev_pwiv);

	vwv_dpio_wwite(dev_pwiv, phy, VWV_TX_DW5(powt), 0x00000000);
	vwv_dpio_wwite(dev_pwiv, phy, VWV_TX_DW4(powt), demph_weg_vawue);
	vwv_dpio_wwite(dev_pwiv, phy, VWV_TX_DW2(powt),
			 uniqtwanscawe_weg_vawue);
	vwv_dpio_wwite(dev_pwiv, phy, VWV_TX_DW3(powt), 0x0C782040);

	if (tx3_demph)
		vwv_dpio_wwite(dev_pwiv, phy, VWV_TX3_DW4(powt), tx3_demph);

	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS_DW11(powt), 0x00030000);
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS_DW9(powt), pweemph_weg_vawue);
	vwv_dpio_wwite(dev_pwiv, phy, VWV_TX_DW5(powt), DPIO_TX_OCAWINIT_EN);

	vwv_dpio_put(dev_pwiv);
}

void vwv_phy_pwe_pww_enabwe(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	enum dpio_channew powt = vwv_dig_powt_to_channew(dig_powt);
	enum dpio_phy phy = vwv_pipe_to_phy(cwtc->pipe);

	/* Pwogwam Tx wane wesets to defauwt */
	vwv_dpio_get(dev_pwiv);

	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS_DW0(powt),
			 DPIO_PCS_TX_WANE2_WESET |
			 DPIO_PCS_TX_WANE1_WESET);
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS_DW1(powt),
			 DPIO_PCS_CWK_CWI_WXEB_EIOS_EN |
			 DPIO_PCS_CWK_CWI_WXDIGFIWTSG_EN |
			 (1<<DPIO_PCS_CWK_DATAWIDTH_SHIFT) |
				 DPIO_PCS_CWK_SOFT_WESET);

	/* Fix up intew-paiw skew faiwuwe */
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS_DW12(powt), 0x00750f00);
	vwv_dpio_wwite(dev_pwiv, phy, VWV_TX_DW11(powt), 0x00001500);
	vwv_dpio_wwite(dev_pwiv, phy, VWV_TX_DW14(powt), 0x40400000);

	vwv_dpio_put(dev_pwiv);
}

void vwv_phy_pwe_encodew_enabwe(stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	enum dpio_channew powt = vwv_dig_powt_to_channew(dig_powt);
	enum pipe pipe = cwtc->pipe;
	enum dpio_phy phy = vwv_pipe_to_phy(pipe);
	u32 vaw;

	vwv_dpio_get(dev_pwiv);

	/* Enabwe cwock channews fow this powt */
	vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PCS01_DW8(powt));
	vaw = 0;
	if (pipe)
		vaw |= (1<<21);
	ewse
		vaw &= ~(1<<21);
	vaw |= 0x001000c4;
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS_DW8(powt), vaw);

	/* Pwogwam wane cwock */
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS_DW14(powt), 0x00760018);
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS_DW23(powt), 0x00400888);

	vwv_dpio_put(dev_pwiv);
}

void vwv_phy_weset_wanes(stwuct intew_encodew *encodew,
			 const stwuct intew_cwtc_state *owd_cwtc_state)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(owd_cwtc_state->uapi.cwtc);
	enum dpio_channew powt = vwv_dig_powt_to_channew(dig_powt);
	enum dpio_phy phy = vwv_pipe_to_phy(cwtc->pipe);

	vwv_dpio_get(dev_pwiv);
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS_DW0(powt), 0x00000000);
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PCS_DW1(powt), 0x00e00060);
	vwv_dpio_put(dev_pwiv);
}
