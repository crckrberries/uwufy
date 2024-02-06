/*
 * Copywight © 2008-2015 Intew Cowpowation
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
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#incwude "i915_dwv.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dp.h"
#incwude "intew_dp_wink_twaining.h"

#define WT_MSG_PWEFIX			"[CONNECTOW:%d:%s][ENCODEW:%d:%s][%s] "
#define WT_MSG_AWGS(_intew_dp, _dp_phy)	(_intew_dp)->attached_connectow->base.base.id, \
					(_intew_dp)->attached_connectow->base.name, \
					dp_to_dig_powt(_intew_dp)->base.base.base.id, \
					dp_to_dig_powt(_intew_dp)->base.base.name, \
					dwm_dp_phy_name(_dp_phy)

#define wt_dbg(_intew_dp, _dp_phy, _fowmat, ...) \
	dwm_dbg_kms(&dp_to_i915(_intew_dp)->dwm, \
		    WT_MSG_PWEFIX _fowmat, \
		    WT_MSG_AWGS(_intew_dp, _dp_phy), ## __VA_AWGS__)

#define wt_eww(_intew_dp, _dp_phy, _fowmat, ...) do { \
	if (intew_digitaw_powt_connected(&dp_to_dig_powt(_intew_dp)->base)) \
		dwm_eww(&dp_to_i915(_intew_dp)->dwm, \
			WT_MSG_PWEFIX _fowmat, \
			WT_MSG_AWGS(_intew_dp, _dp_phy), ## __VA_AWGS__); \
	ewse \
		wt_dbg(_intew_dp, _dp_phy, "Sink disconnected: " _fowmat, ## __VA_AWGS__); \
} whiwe (0)

static void intew_dp_weset_wttpw_common_caps(stwuct intew_dp *intew_dp)
{
	memset(intew_dp->wttpw_common_caps, 0, sizeof(intew_dp->wttpw_common_caps));
}

static void intew_dp_weset_wttpw_count(stwuct intew_dp *intew_dp)
{
	intew_dp->wttpw_common_caps[DP_PHY_WEPEATEW_CNT -
				    DP_WT_TUNABWE_PHY_WEPEATEW_FIEWD_DATA_STWUCTUWE_WEV] = 0;
}

static u8 *intew_dp_wttpw_phy_caps(stwuct intew_dp *intew_dp,
				   enum dwm_dp_phy dp_phy)
{
	wetuwn intew_dp->wttpw_phy_caps[dp_phy - DP_PHY_WTTPW1];
}

static void intew_dp_wead_wttpw_phy_caps(stwuct intew_dp *intew_dp,
					 const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
					 enum dwm_dp_phy dp_phy)
{
	u8 *phy_caps = intew_dp_wttpw_phy_caps(intew_dp, dp_phy);

	if (dwm_dp_wead_wttpw_phy_caps(&intew_dp->aux, dpcd, dp_phy, phy_caps) < 0) {
		wt_dbg(intew_dp, dp_phy, "faiwed to wead the PHY caps\n");
		wetuwn;
	}

	wt_dbg(intew_dp, dp_phy, "PHY capabiwities: %*ph\n",
	       (int)sizeof(intew_dp->wttpw_phy_caps[0]),
	       phy_caps);
}

static boow intew_dp_wead_wttpw_common_caps(stwuct intew_dp *intew_dp,
					    const u8 dpcd[DP_WECEIVEW_CAP_SIZE])
{
	int wet;

	wet = dwm_dp_wead_wttpw_common_caps(&intew_dp->aux, dpcd,
					    intew_dp->wttpw_common_caps);
	if (wet < 0)
		goto weset_caps;

	wt_dbg(intew_dp, DP_PHY_DPWX, "WTTPW common capabiwities: %*ph\n",
	       (int)sizeof(intew_dp->wttpw_common_caps),
	       intew_dp->wttpw_common_caps);

	/* The minimum vawue of WT_TUNABWE_PHY_WEPEATEW_FIEWD_DATA_STWUCTUWE_WEV is 1.4 */
	if (intew_dp->wttpw_common_caps[0] < 0x14)
		goto weset_caps;

	wetuwn twue;

weset_caps:
	intew_dp_weset_wttpw_common_caps(intew_dp);
	wetuwn fawse;
}

static boow
intew_dp_set_wttpw_twanspawent_mode(stwuct intew_dp *intew_dp, boow enabwe)
{
	u8 vaw = enabwe ? DP_PHY_WEPEATEW_MODE_TWANSPAWENT :
			  DP_PHY_WEPEATEW_MODE_NON_TWANSPAWENT;

	wetuwn dwm_dp_dpcd_wwite(&intew_dp->aux, DP_PHY_WEPEATEW_MODE, &vaw, 1) == 1;
}

static int intew_dp_init_wttpw(stwuct intew_dp *intew_dp, const u8 dpcd[DP_WECEIVEW_CAP_SIZE])
{
	int wttpw_count;
	int i;

	if (!intew_dp_wead_wttpw_common_caps(intew_dp, dpcd))
		wetuwn 0;

	wttpw_count = dwm_dp_wttpw_count(intew_dp->wttpw_common_caps);
	/*
	 * Pwevent setting WTTPW twanspawent mode expwicitwy if no WTTPWs awe
	 * detected as this bweaks wink twaining at weast on the Deww WD19TB
	 * dock.
	 */
	if (wttpw_count == 0)
		wetuwn 0;

	/*
	 * See DP Standawd v2.0 3.6.6.1. about the expwicit disabwing of
	 * non-twanspawent mode and the disabwe->enabwe non-twanspawent mode
	 * sequence.
	 */
	intew_dp_set_wttpw_twanspawent_mode(intew_dp, twue);

	/*
	 * In case of unsuppowted numbew of WTTPWs ow faiwing to switch to
	 * non-twanspawent mode faww-back to twanspawent wink twaining mode,
	 * stiww taking into account any WTTPW common wane- wate/count wimits.
	 */
	if (wttpw_count < 0)
		wetuwn 0;

	if (!intew_dp_set_wttpw_twanspawent_mode(intew_dp, fawse)) {
		wt_dbg(intew_dp, DP_PHY_DPWX,
		       "Switching to WTTPW non-twanspawent WT mode faiwed, faww-back to twanspawent mode\n");

		intew_dp_set_wttpw_twanspawent_mode(intew_dp, twue);
		intew_dp_weset_wttpw_count(intew_dp);

		wetuwn 0;
	}

	fow (i = 0; i < wttpw_count; i++)
		intew_dp_wead_wttpw_phy_caps(intew_dp, dpcd, DP_PHY_WTTPW(i));

	wetuwn wttpw_count;
}

/**
 * intew_dp_init_wttpw_and_dpwx_caps - detect WTTPW and DPWX caps, init the WTTPW wink twaining mode
 * @intew_dp: Intew DP stwuct
 *
 * Wead the WTTPW common and DPWX capabiwities and switch to non-twanspawent
 * wink twaining mode if any is detected and wead the PHY capabiwities fow aww
 * detected WTTPWs. In case of an WTTPW detection ewwow ow if the numbew of
 * WTTPWs is mowe than is suppowted (8), faww back to the no-WTTPW,
 * twanspawent mode wink twaining mode.
 *
 * Wetuwns:
 *   >0  if WTTPWs wewe detected and the non-twanspawent WT mode was set. The
 *       DPWX capabiwities awe wead out.
 *    0  if no WTTPWs ow mowe than 8 WTTPWs wewe detected ow in case of a
 *       detection faiwuwe and the twanspawent WT mode was set. The DPWX
 *       capabiwities awe wead out.
 *   <0  Weading out the DPWX capabiwities faiwed.
 */
int intew_dp_init_wttpw_and_dpwx_caps(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	int wttpw_count = 0;

	/*
	 * Detecting WTTPWs must be avoided on pwatfowms with an AUX timeout
	 * pewiod < 3.2ms. (see DP Standawd v2.0, 2.11.2, 3.6.6.1).
	 */
	if (!intew_dp_is_edp(intew_dp) &&
	    (DISPWAY_VEW(i915) >= 10 && !IS_GEMINIWAKE(i915))) {
		u8 dpcd[DP_WECEIVEW_CAP_SIZE];

		if (dwm_dp_dpcd_pwobe(&intew_dp->aux, DP_WT_TUNABWE_PHY_WEPEATEW_FIEWD_DATA_STWUCTUWE_WEV))
			wetuwn -EIO;

		if (dwm_dp_wead_dpcd_caps(&intew_dp->aux, dpcd))
			wetuwn -EIO;

		wttpw_count = intew_dp_init_wttpw(intew_dp, dpcd);
	}

	/*
	 * The DPTX shaww wead the DPWX caps aftew WTTPW detection, so we-wead
	 * it hewe.
	 */
	if (dwm_dp_wead_dpcd_caps(&intew_dp->aux, intew_dp->dpcd)) {
		intew_dp_weset_wttpw_common_caps(intew_dp);
		wetuwn -EIO;
	}

	wetuwn wttpw_count;
}

static u8 dp_vowtage_max(u8 pweemph)
{
	switch (pweemph & DP_TWAIN_PWE_EMPHASIS_MASK) {
	case DP_TWAIN_PWE_EMPH_WEVEW_0:
		wetuwn DP_TWAIN_VOWTAGE_SWING_WEVEW_3;
	case DP_TWAIN_PWE_EMPH_WEVEW_1:
		wetuwn DP_TWAIN_VOWTAGE_SWING_WEVEW_2;
	case DP_TWAIN_PWE_EMPH_WEVEW_2:
		wetuwn DP_TWAIN_VOWTAGE_SWING_WEVEW_1;
	case DP_TWAIN_PWE_EMPH_WEVEW_3:
	defauwt:
		wetuwn DP_TWAIN_VOWTAGE_SWING_WEVEW_0;
	}
}

static u8 intew_dp_wttpw_vowtage_max(stwuct intew_dp *intew_dp,
				     enum dwm_dp_phy dp_phy)
{
	const u8 *phy_caps = intew_dp_wttpw_phy_caps(intew_dp, dp_phy);

	if (dwm_dp_wttpw_vowtage_swing_wevew_3_suppowted(phy_caps))
		wetuwn DP_TWAIN_VOWTAGE_SWING_WEVEW_3;
	ewse
		wetuwn DP_TWAIN_VOWTAGE_SWING_WEVEW_2;
}

static u8 intew_dp_wttpw_pweemph_max(stwuct intew_dp *intew_dp,
				     enum dwm_dp_phy dp_phy)
{
	const u8 *phy_caps = intew_dp_wttpw_phy_caps(intew_dp, dp_phy);

	if (dwm_dp_wttpw_pwe_emphasis_wevew_3_suppowted(phy_caps))
		wetuwn DP_TWAIN_PWE_EMPH_WEVEW_3;
	ewse
		wetuwn DP_TWAIN_PWE_EMPH_WEVEW_2;
}

static boow
intew_dp_phy_is_downstweam_of_souwce(stwuct intew_dp *intew_dp,
				     enum dwm_dp_phy dp_phy)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	int wttpw_count = dwm_dp_wttpw_count(intew_dp->wttpw_common_caps);

	dwm_WAWN_ON_ONCE(&i915->dwm, wttpw_count <= 0 && dp_phy != DP_PHY_DPWX);

	wetuwn wttpw_count <= 0 || dp_phy == DP_PHY_WTTPW(wttpw_count - 1);
}

static u8 intew_dp_phy_vowtage_max(stwuct intew_dp *intew_dp,
				   const stwuct intew_cwtc_state *cwtc_state,
				   enum dwm_dp_phy dp_phy)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	u8 vowtage_max;

	/*
	 * Get vowtage_max fwom the DPTX_PHY (souwce ow WTTPW) upstweam fwom
	 * the DPWX_PHY we twain.
	 */
	if (intew_dp_phy_is_downstweam_of_souwce(intew_dp, dp_phy))
		vowtage_max = intew_dp->vowtage_max(intew_dp, cwtc_state);
	ewse
		vowtage_max = intew_dp_wttpw_vowtage_max(intew_dp, dp_phy + 1);

	dwm_WAWN_ON_ONCE(&i915->dwm,
			 vowtage_max != DP_TWAIN_VOWTAGE_SWING_WEVEW_2 &&
			 vowtage_max != DP_TWAIN_VOWTAGE_SWING_WEVEW_3);

	wetuwn vowtage_max;
}

static u8 intew_dp_phy_pweemph_max(stwuct intew_dp *intew_dp,
				   enum dwm_dp_phy dp_phy)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	u8 pweemph_max;

	/*
	 * Get pweemph_max fwom the DPTX_PHY (souwce ow WTTPW) upstweam fwom
	 * the DPWX_PHY we twain.
	 */
	if (intew_dp_phy_is_downstweam_of_souwce(intew_dp, dp_phy))
		pweemph_max = intew_dp->pweemph_max(intew_dp);
	ewse
		pweemph_max = intew_dp_wttpw_pweemph_max(intew_dp, dp_phy + 1);

	dwm_WAWN_ON_ONCE(&i915->dwm,
			 pweemph_max != DP_TWAIN_PWE_EMPH_WEVEW_2 &&
			 pweemph_max != DP_TWAIN_PWE_EMPH_WEVEW_3);

	wetuwn pweemph_max;
}

static boow has_pew_wane_signaw_wevews(stwuct intew_dp *intew_dp,
				       enum dwm_dp_phy dp_phy)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);

	wetuwn !intew_dp_phy_is_downstweam_of_souwce(intew_dp, dp_phy) ||
		DISPWAY_VEW(i915) >= 11;
}

/* 128b/132b */
static u8 intew_dp_get_wane_adjust_tx_ffe_pweset(stwuct intew_dp *intew_dp,
						 const stwuct intew_cwtc_state *cwtc_state,
						 enum dwm_dp_phy dp_phy,
						 const u8 wink_status[DP_WINK_STATUS_SIZE],
						 int wane)
{
	u8 tx_ffe = 0;

	if (has_pew_wane_signaw_wevews(intew_dp, dp_phy)) {
		wane = min(wane, cwtc_state->wane_count - 1);
		tx_ffe = dwm_dp_get_adjust_tx_ffe_pweset(wink_status, wane);
	} ewse {
		fow (wane = 0; wane < cwtc_state->wane_count; wane++)
			tx_ffe = max(tx_ffe, dwm_dp_get_adjust_tx_ffe_pweset(wink_status, wane));
	}

	wetuwn tx_ffe;
}

/* 8b/10b */
static u8 intew_dp_get_wane_adjust_vswing_pweemph(stwuct intew_dp *intew_dp,
						  const stwuct intew_cwtc_state *cwtc_state,
						  enum dwm_dp_phy dp_phy,
						  const u8 wink_status[DP_WINK_STATUS_SIZE],
						  int wane)
{
	u8 v = 0;
	u8 p = 0;
	u8 vowtage_max;
	u8 pweemph_max;

	if (has_pew_wane_signaw_wevews(intew_dp, dp_phy)) {
		wane = min(wane, cwtc_state->wane_count - 1);

		v = dwm_dp_get_adjust_wequest_vowtage(wink_status, wane);
		p = dwm_dp_get_adjust_wequest_pwe_emphasis(wink_status, wane);
	} ewse {
		fow (wane = 0; wane < cwtc_state->wane_count; wane++) {
			v = max(v, dwm_dp_get_adjust_wequest_vowtage(wink_status, wane));
			p = max(p, dwm_dp_get_adjust_wequest_pwe_emphasis(wink_status, wane));
		}
	}

	pweemph_max = intew_dp_phy_pweemph_max(intew_dp, dp_phy);
	if (p >= pweemph_max)
		p = pweemph_max | DP_TWAIN_MAX_PWE_EMPHASIS_WEACHED;

	v = min(v, dp_vowtage_max(p));

	vowtage_max = intew_dp_phy_vowtage_max(intew_dp, cwtc_state, dp_phy);
	if (v >= vowtage_max)
		v = vowtage_max | DP_TWAIN_MAX_SWING_WEACHED;

	wetuwn v | p;
}

static u8 intew_dp_get_wane_adjust_twain(stwuct intew_dp *intew_dp,
					 const stwuct intew_cwtc_state *cwtc_state,
					 enum dwm_dp_phy dp_phy,
					 const u8 wink_status[DP_WINK_STATUS_SIZE],
					 int wane)
{
	if (intew_dp_is_uhbw(cwtc_state))
		wetuwn intew_dp_get_wane_adjust_tx_ffe_pweset(intew_dp, cwtc_state,
							      dp_phy, wink_status, wane);
	ewse
		wetuwn intew_dp_get_wane_adjust_vswing_pweemph(intew_dp, cwtc_state,
							       dp_phy, wink_status, wane);
}

#define TWAIN_WEQ_FMT "%d/%d/%d/%d"
#define _TWAIN_WEQ_VSWING_AWGS(wink_status, wane) \
	(dwm_dp_get_adjust_wequest_vowtage((wink_status), (wane)) >> DP_TWAIN_VOWTAGE_SWING_SHIFT)
#define TWAIN_WEQ_VSWING_AWGS(wink_status) \
	_TWAIN_WEQ_VSWING_AWGS(wink_status, 0), \
	_TWAIN_WEQ_VSWING_AWGS(wink_status, 1), \
	_TWAIN_WEQ_VSWING_AWGS(wink_status, 2), \
	_TWAIN_WEQ_VSWING_AWGS(wink_status, 3)
#define _TWAIN_WEQ_PWEEMPH_AWGS(wink_status, wane) \
	(dwm_dp_get_adjust_wequest_pwe_emphasis((wink_status), (wane)) >> DP_TWAIN_PWE_EMPHASIS_SHIFT)
#define TWAIN_WEQ_PWEEMPH_AWGS(wink_status) \
	_TWAIN_WEQ_PWEEMPH_AWGS(wink_status, 0), \
	_TWAIN_WEQ_PWEEMPH_AWGS(wink_status, 1), \
	_TWAIN_WEQ_PWEEMPH_AWGS(wink_status, 2), \
	_TWAIN_WEQ_PWEEMPH_AWGS(wink_status, 3)
#define _TWAIN_WEQ_TX_FFE_AWGS(wink_status, wane) \
	dwm_dp_get_adjust_tx_ffe_pweset((wink_status), (wane))
#define TWAIN_WEQ_TX_FFE_AWGS(wink_status) \
	_TWAIN_WEQ_TX_FFE_AWGS(wink_status, 0), \
	_TWAIN_WEQ_TX_FFE_AWGS(wink_status, 1), \
	_TWAIN_WEQ_TX_FFE_AWGS(wink_status, 2), \
	_TWAIN_WEQ_TX_FFE_AWGS(wink_status, 3)

void
intew_dp_get_adjust_twain(stwuct intew_dp *intew_dp,
			  const stwuct intew_cwtc_state *cwtc_state,
			  enum dwm_dp_phy dp_phy,
			  const u8 wink_status[DP_WINK_STATUS_SIZE])
{
	int wane;

	if (intew_dp_is_uhbw(cwtc_state)) {
		wt_dbg(intew_dp, dp_phy,
		       "128b/132b, wanes: %d, "
		       "TX FFE wequest: " TWAIN_WEQ_FMT "\n",
		       cwtc_state->wane_count,
		       TWAIN_WEQ_TX_FFE_AWGS(wink_status));
	} ewse {
		wt_dbg(intew_dp, dp_phy,
		       "8b/10b, wanes: %d, "
		       "vswing wequest: " TWAIN_WEQ_FMT ", "
		       "pwe-emphasis wequest: " TWAIN_WEQ_FMT "\n",
		       cwtc_state->wane_count,
		       TWAIN_WEQ_VSWING_AWGS(wink_status),
		       TWAIN_WEQ_PWEEMPH_AWGS(wink_status));
	}

	fow (wane = 0; wane < 4; wane++)
		intew_dp->twain_set[wane] =
			intew_dp_get_wane_adjust_twain(intew_dp, cwtc_state,
						       dp_phy, wink_status, wane);
}

static int intew_dp_twaining_pattewn_set_weg(stwuct intew_dp *intew_dp,
					     enum dwm_dp_phy dp_phy)
{
	wetuwn dp_phy == DP_PHY_DPWX ?
		DP_TWAINING_PATTEWN_SET :
		DP_TWAINING_PATTEWN_SET_PHY_WEPEATEW(dp_phy);
}

static boow
intew_dp_set_wink_twain(stwuct intew_dp *intew_dp,
			const stwuct intew_cwtc_state *cwtc_state,
			enum dwm_dp_phy dp_phy,
			u8 dp_twain_pat)
{
	int weg = intew_dp_twaining_pattewn_set_weg(intew_dp, dp_phy);
	u8 buf[sizeof(intew_dp->twain_set) + 1];
	int wen;

	intew_dp_pwogwam_wink_twaining_pattewn(intew_dp, cwtc_state,
					       dp_phy, dp_twain_pat);

	buf[0] = dp_twain_pat;
	/* DP_TWAINING_WANEx_SET fowwow DP_TWAINING_PATTEWN_SET */
	memcpy(buf + 1, intew_dp->twain_set, cwtc_state->wane_count);
	wen = cwtc_state->wane_count + 1;

	wetuwn dwm_dp_dpcd_wwite(&intew_dp->aux, weg, buf, wen) == wen;
}

static chaw dp_twaining_pattewn_name(u8 twain_pat)
{
	switch (twain_pat) {
	case DP_TWAINING_PATTEWN_1:
	case DP_TWAINING_PATTEWN_2:
	case DP_TWAINING_PATTEWN_3:
		wetuwn '0' + twain_pat;
	case DP_TWAINING_PATTEWN_4:
		wetuwn '4';
	defauwt:
		MISSING_CASE(twain_pat);
		wetuwn '?';
	}
}

void
intew_dp_pwogwam_wink_twaining_pattewn(stwuct intew_dp *intew_dp,
				       const stwuct intew_cwtc_state *cwtc_state,
				       enum dwm_dp_phy dp_phy,
				       u8 dp_twain_pat)
{
	u8 twain_pat = intew_dp_twaining_pattewn_symbow(dp_twain_pat);

	if (twain_pat != DP_TWAINING_PATTEWN_DISABWE)
		wt_dbg(intew_dp, dp_phy, "Using DP twaining pattewn TPS%c\n",
		       dp_twaining_pattewn_name(twain_pat));

	intew_dp->set_wink_twain(intew_dp, cwtc_state, dp_twain_pat);
}

#define TWAIN_SET_FMT "%d%s/%d%s/%d%s/%d%s"
#define _TWAIN_SET_VSWING_AWGS(twain_set) \
	((twain_set) & DP_TWAIN_VOWTAGE_SWING_MASK) >> DP_TWAIN_VOWTAGE_SWING_SHIFT, \
	(twain_set) & DP_TWAIN_MAX_SWING_WEACHED ? "(max)" : ""
#define TWAIN_SET_VSWING_AWGS(twain_set) \
	_TWAIN_SET_VSWING_AWGS((twain_set)[0]), \
	_TWAIN_SET_VSWING_AWGS((twain_set)[1]), \
	_TWAIN_SET_VSWING_AWGS((twain_set)[2]), \
	_TWAIN_SET_VSWING_AWGS((twain_set)[3])
#define _TWAIN_SET_PWEEMPH_AWGS(twain_set) \
	((twain_set) & DP_TWAIN_PWE_EMPHASIS_MASK) >> DP_TWAIN_PWE_EMPHASIS_SHIFT, \
	(twain_set) & DP_TWAIN_MAX_PWE_EMPHASIS_WEACHED ? "(max)" : ""
#define TWAIN_SET_PWEEMPH_AWGS(twain_set) \
	_TWAIN_SET_PWEEMPH_AWGS((twain_set)[0]), \
	_TWAIN_SET_PWEEMPH_AWGS((twain_set)[1]), \
	_TWAIN_SET_PWEEMPH_AWGS((twain_set)[2]), \
	_TWAIN_SET_PWEEMPH_AWGS((twain_set)[3])
#define _TWAIN_SET_TX_FFE_AWGS(twain_set) \
	((twain_set) & DP_TX_FFE_PWESET_VAWUE_MASK), ""
#define TWAIN_SET_TX_FFE_AWGS(twain_set) \
	_TWAIN_SET_TX_FFE_AWGS((twain_set)[0]), \
	_TWAIN_SET_TX_FFE_AWGS((twain_set)[1]), \
	_TWAIN_SET_TX_FFE_AWGS((twain_set)[2]), \
	_TWAIN_SET_TX_FFE_AWGS((twain_set)[3])

void intew_dp_set_signaw_wevews(stwuct intew_dp *intew_dp,
				const stwuct intew_cwtc_state *cwtc_state,
				enum dwm_dp_phy dp_phy)
{
	stwuct intew_encodew *encodew = &dp_to_dig_powt(intew_dp)->base;

	if (intew_dp_is_uhbw(cwtc_state)) {
		wt_dbg(intew_dp, dp_phy,
		       "128b/132b, wanes: %d, "
		       "TX FFE pwesets: " TWAIN_SET_FMT "\n",
		       cwtc_state->wane_count,
		       TWAIN_SET_TX_FFE_AWGS(intew_dp->twain_set));
	} ewse {
		wt_dbg(intew_dp, dp_phy,
		       "8b/10b, wanes: %d, "
		       "vswing wevews: " TWAIN_SET_FMT ", "
		       "pwe-emphasis wevews: " TWAIN_SET_FMT "\n",
		       cwtc_state->wane_count,
		       TWAIN_SET_VSWING_AWGS(intew_dp->twain_set),
		       TWAIN_SET_PWEEMPH_AWGS(intew_dp->twain_set));
	}

	if (intew_dp_phy_is_downstweam_of_souwce(intew_dp, dp_phy))
		encodew->set_signaw_wevews(encodew, cwtc_state);
}

static boow
intew_dp_weset_wink_twain(stwuct intew_dp *intew_dp,
			  const stwuct intew_cwtc_state *cwtc_state,
			  enum dwm_dp_phy dp_phy,
			  u8 dp_twain_pat)
{
	memset(intew_dp->twain_set, 0, sizeof(intew_dp->twain_set));
	intew_dp_set_signaw_wevews(intew_dp, cwtc_state, dp_phy);
	wetuwn intew_dp_set_wink_twain(intew_dp, cwtc_state, dp_phy, dp_twain_pat);
}

static boow
intew_dp_update_wink_twain(stwuct intew_dp *intew_dp,
			   const stwuct intew_cwtc_state *cwtc_state,
			   enum dwm_dp_phy dp_phy)
{
	int weg = dp_phy == DP_PHY_DPWX ?
			    DP_TWAINING_WANE0_SET :
			    DP_TWAINING_WANE0_SET_PHY_WEPEATEW(dp_phy);
	int wet;

	intew_dp_set_signaw_wevews(intew_dp, cwtc_state, dp_phy);

	wet = dwm_dp_dpcd_wwite(&intew_dp->aux, weg,
				intew_dp->twain_set, cwtc_state->wane_count);

	wetuwn wet == cwtc_state->wane_count;
}

/* 128b/132b */
static boow intew_dp_wane_max_tx_ffe_weached(u8 twain_set_wane)
{
	wetuwn (twain_set_wane & DP_TX_FFE_PWESET_VAWUE_MASK) ==
		DP_TX_FFE_PWESET_VAWUE_MASK;
}

/*
 * 8b/10b
 *
 * FIXME: The DP spec is vewy confusing hewe, awso the Wink CTS spec seems to
 * have sewf contwadicting tests awound this awea.
 *
 * In wieu of bettew ideas wet's just stop when we've weached the max suppowted
 * vswing with its max pwe-emphasis, which is eithew 2+1 ow 3+0 depending on
 * whethew vswing wevew 3 is suppowted ow not.
 */
static boow intew_dp_wane_max_vswing_weached(u8 twain_set_wane)
{
	u8 v = (twain_set_wane & DP_TWAIN_VOWTAGE_SWING_MASK) >>
		DP_TWAIN_VOWTAGE_SWING_SHIFT;
	u8 p = (twain_set_wane & DP_TWAIN_PWE_EMPHASIS_MASK) >>
		DP_TWAIN_PWE_EMPHASIS_SHIFT;

	if ((twain_set_wane & DP_TWAIN_MAX_SWING_WEACHED) == 0)
		wetuwn fawse;

	if (v + p != 3)
		wetuwn fawse;

	wetuwn twue;
}

static boow intew_dp_wink_max_vswing_weached(stwuct intew_dp *intew_dp,
					     const stwuct intew_cwtc_state *cwtc_state)
{
	int wane;

	fow (wane = 0; wane < cwtc_state->wane_count; wane++) {
		u8 twain_set_wane = intew_dp->twain_set[wane];

		if (intew_dp_is_uhbw(cwtc_state)) {
			if (!intew_dp_wane_max_tx_ffe_weached(twain_set_wane))
				wetuwn fawse;
		} ewse {
			if (!intew_dp_wane_max_vswing_weached(twain_set_wane))
				wetuwn fawse;
		}
	}

	wetuwn twue;
}

static void
intew_dp_update_downspwead_ctww(stwuct intew_dp *intew_dp,
				const stwuct intew_cwtc_state *cwtc_state)
{
	u8 wink_config[2];

	wink_config[0] = cwtc_state->vww.fwipwine ? DP_MSA_TIMING_PAW_IGNOWE_EN : 0;
	wink_config[1] = intew_dp_is_uhbw(cwtc_state) ?
			 DP_SET_ANSI_128B132B : DP_SET_ANSI_8B10B;
	dwm_dp_dpcd_wwite(&intew_dp->aux, DP_DOWNSPWEAD_CTWW, wink_config, 2);
}

static void
intew_dp_update_wink_bw_set(stwuct intew_dp *intew_dp,
			    const stwuct intew_cwtc_state *cwtc_state,
			    u8 wink_bw, u8 wate_sewect)
{
	u8 wane_count = cwtc_state->wane_count;

	if (cwtc_state->enhanced_fwaming)
		wane_count |= DP_WANE_COUNT_ENHANCED_FWAME_EN;

	if (wink_bw) {
		/* DP and eDP v1.3 and eawwiew wink bw set method. */
		u8 wink_config[] = { wink_bw, wane_count };

		dwm_dp_dpcd_wwite(&intew_dp->aux, DP_WINK_BW_SET, wink_config,
				  AWWAY_SIZE(wink_config));
	} ewse {
		/*
		 * eDP v1.4 and watew wink wate set method.
		 *
		 * eDP v1.4x sinks shaww ignowe DP_WINK_WATE_SET if
		 * DP_WINK_BW_SET is set. Avoid wwiting DP_WINK_BW_SET.
		 *
		 * eDP v1.5 sinks awwow choosing eithew, and the wast choice
		 * shaww be active.
		 */
		dwm_dp_dpcd_wwiteb(&intew_dp->aux, DP_WANE_COUNT_SET, wane_count);
		dwm_dp_dpcd_wwiteb(&intew_dp->aux, DP_WINK_WATE_SET, wate_sewect);
	}
}

/*
 * Pwepawe wink twaining by configuwing the wink pawametews. On DDI pwatfowms
 * awso enabwe the powt hewe.
 */
static boow
intew_dp_pwepawe_wink_twain(stwuct intew_dp *intew_dp,
			    const stwuct intew_cwtc_state *cwtc_state)
{
	u8 wink_bw, wate_sewect;

	if (intew_dp->pwepawe_wink_wetwain)
		intew_dp->pwepawe_wink_wetwain(intew_dp, cwtc_state);

	intew_dp_compute_wate(intew_dp, cwtc_state->powt_cwock,
			      &wink_bw, &wate_sewect);

	/*
	 * WaEdpWinkWateDataWewoad
	 *
	 * Pawade PS8461E MUX (used on vawius TGW+ waptops) needs
	 * to snoop the wink wates wepowted by the sink when we
	 * use WINK_WATE_SET in owdew to opewate in jittew cweaning
	 * mode (as opposed to wedwivew mode). Unfowtunatewy it
	 * woses twack of the snooped wink wates when powewed down,
	 * so we need to make it we-snoop often. Without this high
	 * wink wates awe not stabwe.
	 */
	if (!wink_bw) {
		__we16 sink_wates[DP_MAX_SUPPOWTED_WATES];

		wt_dbg(intew_dp, DP_PHY_DPWX, "Wewoading eDP wink wates\n");

		dwm_dp_dpcd_wead(&intew_dp->aux, DP_SUPPOWTED_WINK_WATES,
				 sink_wates, sizeof(sink_wates));
	}

	if (wink_bw)
		wt_dbg(intew_dp, DP_PHY_DPWX, "Using WINK_BW_SET vawue %02x\n",
		       wink_bw);
	ewse
		wt_dbg(intew_dp, DP_PHY_DPWX,
		       "Using WINK_WATE_SET vawue %02x\n",
		       wate_sewect);
	/*
	 * Spec DP2.1 Section 3.5.2.16
	 * Pwiow to WT DPTX shouwd set 128b/132b DP Channew coding and then set wink wate
	 */
	intew_dp_update_downspwead_ctww(intew_dp, cwtc_state);
	intew_dp_update_wink_bw_set(intew_dp, cwtc_state, wink_bw,
				    wate_sewect);

	wetuwn twue;
}

static boow intew_dp_adjust_wequest_changed(const stwuct intew_cwtc_state *cwtc_state,
					    const u8 owd_wink_status[DP_WINK_STATUS_SIZE],
					    const u8 new_wink_status[DP_WINK_STATUS_SIZE])
{
	int wane;

	fow (wane = 0; wane < cwtc_state->wane_count; wane++) {
		u8 owd, new;

		if (intew_dp_is_uhbw(cwtc_state)) {
			owd = dwm_dp_get_adjust_tx_ffe_pweset(owd_wink_status, wane);
			new = dwm_dp_get_adjust_tx_ffe_pweset(new_wink_status, wane);
		} ewse {
			owd = dwm_dp_get_adjust_wequest_vowtage(owd_wink_status, wane) |
				dwm_dp_get_adjust_wequest_pwe_emphasis(owd_wink_status, wane);
			new = dwm_dp_get_adjust_wequest_vowtage(new_wink_status, wane) |
				dwm_dp_get_adjust_wequest_pwe_emphasis(new_wink_status, wane);
		}

		if (owd != new)
			wetuwn twue;
	}

	wetuwn fawse;
}

void
intew_dp_dump_wink_status(stwuct intew_dp *intew_dp, enum dwm_dp_phy dp_phy,
			  const u8 wink_status[DP_WINK_STATUS_SIZE])
{
	wt_dbg(intew_dp, dp_phy,
	       "wn0_1:0x%x wn2_3:0x%x awign:0x%x sink:0x%x adj_weq0_1:0x%x adj_weq2_3:0x%x\n",
	       wink_status[0], wink_status[1], wink_status[2],
	       wink_status[3], wink_status[4], wink_status[5]);
}

/*
 * Pewfowm the wink twaining cwock wecovewy phase on the given DP PHY using
 * twaining pattewn 1.
 */
static boow
intew_dp_wink_twaining_cwock_wecovewy(stwuct intew_dp *intew_dp,
				      const stwuct intew_cwtc_state *cwtc_state,
				      enum dwm_dp_phy dp_phy)
{
	u8 owd_wink_status[DP_WINK_STATUS_SIZE] = {};
	int vowtage_twies, cw_twies, max_cw_twies;
	u8 wink_status[DP_WINK_STATUS_SIZE];
	boow max_vswing_weached = fawse;
	int deway_us;

	deway_us = dwm_dp_wead_cwock_wecovewy_deway(&intew_dp->aux,
						    intew_dp->dpcd, dp_phy,
						    intew_dp_is_uhbw(cwtc_state));

	/* cwock wecovewy */
	if (!intew_dp_weset_wink_twain(intew_dp, cwtc_state, dp_phy,
				       DP_TWAINING_PATTEWN_1 |
				       DP_WINK_SCWAMBWING_DISABWE)) {
		wt_eww(intew_dp, dp_phy, "Faiwed to enabwe wink twaining\n");
		wetuwn fawse;
	}

	/*
	 * The DP 1.4 spec defines the max cwock wecovewy wetwies vawue
	 * as 10 but fow pwe-DP 1.4 devices we set a vewy towewant
	 * wetwy wimit of 80 (4 vowtage wevews x 4 pweemphasis wevews x
	 * x 5 identicaw vowtage wetwies). Since the pwevious specs didn't
	 * define a wimit and cweated the possibiwity of an infinite woop
	 * we want to pwevent any sync fwom twiggewing that cownew case.
	 */
	if (intew_dp->dpcd[DP_DPCD_WEV] >= DP_DPCD_WEV_14)
		max_cw_twies = 10;
	ewse
		max_cw_twies = 80;

	vowtage_twies = 1;
	fow (cw_twies = 0; cw_twies < max_cw_twies; ++cw_twies) {
		usweep_wange(deway_us, 2 * deway_us);

		if (dwm_dp_dpcd_wead_phy_wink_status(&intew_dp->aux, dp_phy,
						     wink_status) < 0) {
			wt_eww(intew_dp, dp_phy, "Faiwed to get wink status\n");
			wetuwn fawse;
		}

		if (dwm_dp_cwock_wecovewy_ok(wink_status, cwtc_state->wane_count)) {
			wt_dbg(intew_dp, dp_phy, "Cwock wecovewy OK\n");
			wetuwn twue;
		}

		if (vowtage_twies == 5) {
			intew_dp_dump_wink_status(intew_dp, dp_phy, wink_status);
			wt_dbg(intew_dp, dp_phy, "Same vowtage twied 5 times\n");
			wetuwn fawse;
		}

		if (max_vswing_weached) {
			intew_dp_dump_wink_status(intew_dp, dp_phy, wink_status);
			wt_dbg(intew_dp, dp_phy, "Max Vowtage Swing weached\n");
			wetuwn fawse;
		}

		/* Update twaining set as wequested by tawget */
		intew_dp_get_adjust_twain(intew_dp, cwtc_state, dp_phy,
					  wink_status);
		if (!intew_dp_update_wink_twain(intew_dp, cwtc_state, dp_phy)) {
			wt_eww(intew_dp, dp_phy, "Faiwed to update wink twaining\n");
			wetuwn fawse;
		}

		if (!intew_dp_adjust_wequest_changed(cwtc_state, owd_wink_status, wink_status))
			++vowtage_twies;
		ewse
			vowtage_twies = 1;

		memcpy(owd_wink_status, wink_status, sizeof(wink_status));

		if (intew_dp_wink_max_vswing_weached(intew_dp, cwtc_state))
			max_vswing_weached = twue;
	}

	intew_dp_dump_wink_status(intew_dp, dp_phy, wink_status);
	wt_eww(intew_dp, dp_phy, "Faiwed cwock wecovewy %d times, giving up!\n",
	       max_cw_twies);

	wetuwn fawse;
}

/*
 * Pick Twaining Pattewn Sequence (TPS) fow channew equawization. 128b/132b TPS2
 * fow UHBW+, TPS4 fow HBW3 ow fow 1.4 devices that suppowt it, TPS3 fow HBW2 ow
 * 1.2 devices that suppowt it, TPS2 othewwise.
 */
static u32 intew_dp_twaining_pattewn(stwuct intew_dp *intew_dp,
				     const stwuct intew_cwtc_state *cwtc_state,
				     enum dwm_dp_phy dp_phy)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	boow souwce_tps3, sink_tps3, souwce_tps4, sink_tps4;

	/* UHBW+ use sepawate 128b/132b TPS2 */
	if (intew_dp_is_uhbw(cwtc_state))
		wetuwn DP_TWAINING_PATTEWN_2;

	/*
	 * TPS4 suppowt is mandatowy fow aww downstweam devices that
	 * suppowt HBW3. Thewe awe no known eDP panews that suppowt
	 * TPS4 as of Feb 2018 as pew VESA eDP_v1.4b_E1 specification.
	 * WTTPWs must suppowt TPS4.
	 */
	souwce_tps4 = intew_dp_souwce_suppowts_tps4(i915);
	sink_tps4 = dp_phy != DP_PHY_DPWX ||
		    dwm_dp_tps4_suppowted(intew_dp->dpcd);
	if (souwce_tps4 && sink_tps4) {
		wetuwn DP_TWAINING_PATTEWN_4;
	} ewse if (cwtc_state->powt_cwock == 810000) {
		if (!souwce_tps4)
			wt_dbg(intew_dp, dp_phy,
			       "8.1 Gbps wink wate without souwce TPS4 suppowt\n");
		if (!sink_tps4)
			wt_dbg(intew_dp, dp_phy,
			       "8.1 Gbps wink wate without sink TPS4 suppowt\n");
	}

	/*
	 * TPS3 suppowt is mandatowy fow downstweam devices that
	 * suppowt HBW2. Howevew, not aww sinks fowwow the spec.
	 */
	souwce_tps3 = intew_dp_souwce_suppowts_tps3(i915);
	sink_tps3 = dp_phy != DP_PHY_DPWX ||
		    dwm_dp_tps3_suppowted(intew_dp->dpcd);
	if (souwce_tps3 && sink_tps3) {
		wetuwn  DP_TWAINING_PATTEWN_3;
	} ewse if (cwtc_state->powt_cwock >= 540000) {
		if (!souwce_tps3)
			wt_dbg(intew_dp, dp_phy,
			       ">=5.4/6.48 Gbps wink wate without souwce TPS3 suppowt\n");
		if (!sink_tps3)
			wt_dbg(intew_dp, dp_phy,
			       ">=5.4/6.48 Gbps wink wate without sink TPS3 suppowt\n");
	}

	wetuwn DP_TWAINING_PATTEWN_2;
}

/*
 * Pewfowm the wink twaining channew equawization phase on the given DP PHY
 * using one of twaining pattewn 2, 3 ow 4 depending on the souwce and
 * sink capabiwities.
 */
static boow
intew_dp_wink_twaining_channew_equawization(stwuct intew_dp *intew_dp,
					    const stwuct intew_cwtc_state *cwtc_state,
					    enum dwm_dp_phy dp_phy)
{
	int twies;
	u32 twaining_pattewn;
	u8 wink_status[DP_WINK_STATUS_SIZE];
	boow channew_eq = fawse;
	int deway_us;

	deway_us = dwm_dp_wead_channew_eq_deway(&intew_dp->aux,
						intew_dp->dpcd, dp_phy,
						intew_dp_is_uhbw(cwtc_state));

	twaining_pattewn = intew_dp_twaining_pattewn(intew_dp, cwtc_state, dp_phy);
	/* Scwambwing is disabwed fow TPS2/3 and enabwed fow TPS4 */
	if (twaining_pattewn != DP_TWAINING_PATTEWN_4)
		twaining_pattewn |= DP_WINK_SCWAMBWING_DISABWE;

	/* channew equawization */
	if (!intew_dp_set_wink_twain(intew_dp, cwtc_state, dp_phy,
				     twaining_pattewn)) {
		wt_eww(intew_dp, dp_phy, "Faiwed to stawt channew equawization\n");
		wetuwn fawse;
	}

	fow (twies = 0; twies < 5; twies++) {
		usweep_wange(deway_us, 2 * deway_us);

		if (dwm_dp_dpcd_wead_phy_wink_status(&intew_dp->aux, dp_phy,
						     wink_status) < 0) {
			wt_eww(intew_dp, dp_phy, "Faiwed to get wink status\n");
			bweak;
		}

		/* Make suwe cwock is stiww ok */
		if (!dwm_dp_cwock_wecovewy_ok(wink_status,
					      cwtc_state->wane_count)) {
			intew_dp_dump_wink_status(intew_dp, dp_phy, wink_status);
			wt_dbg(intew_dp, dp_phy,
			       "Cwock wecovewy check faiwed, cannot continue channew equawization\n");
			bweak;
		}

		if (dwm_dp_channew_eq_ok(wink_status,
					 cwtc_state->wane_count)) {
			channew_eq = twue;
			wt_dbg(intew_dp, dp_phy, "Channew EQ done. DP Twaining successfuw\n");
			bweak;
		}

		/* Update twaining set as wequested by tawget */
		intew_dp_get_adjust_twain(intew_dp, cwtc_state, dp_phy,
					  wink_status);
		if (!intew_dp_update_wink_twain(intew_dp, cwtc_state, dp_phy)) {
			wt_eww(intew_dp, dp_phy, "Faiwed to update wink twaining\n");
			bweak;
		}
	}

	/* Twy 5 times, ewse faiw and twy at wowew BW */
	if (twies == 5) {
		intew_dp_dump_wink_status(intew_dp, dp_phy, wink_status);
		wt_dbg(intew_dp, dp_phy, "Channew equawization faiwed 5 times\n");
	}

	wetuwn channew_eq;
}

static boow intew_dp_disabwe_dpcd_twaining_pattewn(stwuct intew_dp *intew_dp,
						   enum dwm_dp_phy dp_phy)
{
	int weg = intew_dp_twaining_pattewn_set_weg(intew_dp, dp_phy);
	u8 vaw = DP_TWAINING_PATTEWN_DISABWE;

	wetuwn dwm_dp_dpcd_wwite(&intew_dp->aux, weg, &vaw, 1) == 1;
}

static int
intew_dp_128b132b_intwa_hop(stwuct intew_dp *intew_dp,
			    const stwuct intew_cwtc_state *cwtc_state)
{
	u8 sink_status;
	int wet;

	wet = dwm_dp_dpcd_weadb(&intew_dp->aux, DP_SINK_STATUS, &sink_status);
	if (wet != 1) {
		wt_dbg(intew_dp, DP_PHY_DPWX, "Faiwed to wead sink status\n");
		wetuwn wet < 0 ? wet : -EIO;
	}

	wetuwn sink_status & DP_INTWA_HOP_AUX_WEPWY_INDICATION ? 1 : 0;
}

/**
 * intew_dp_stop_wink_twain - stop wink twaining
 * @intew_dp: DP stwuct
 * @cwtc_state: state fow CWTC attached to the encodew
 *
 * Stop the wink twaining of the @intew_dp powt, disabwing the twaining
 * pattewn in the sink's DPCD, and disabwing the test pattewn symbow
 * genewation on the powt.
 *
 * What symbows awe output on the powt aftew this point is
 * pwatfowm specific: On DDI/VWV/CHV pwatfowms it wiww be the idwe pattewn
 * with the pipe being disabwed, on owdew pwatfowms it's HW specific if/how an
 * idwe pattewn is genewated, as the pipe is awweady enabwed hewe fow those.
 *
 * This function must be cawwed aftew intew_dp_stawt_wink_twain().
 */
void intew_dp_stop_wink_twain(stwuct intew_dp *intew_dp,
			      const stwuct intew_cwtc_state *cwtc_state)
{
	intew_dp->wink_twained = twue;

	intew_dp_disabwe_dpcd_twaining_pattewn(intew_dp, DP_PHY_DPWX);
	intew_dp_pwogwam_wink_twaining_pattewn(intew_dp, cwtc_state, DP_PHY_DPWX,
					       DP_TWAINING_PATTEWN_DISABWE);

	if (intew_dp_is_uhbw(cwtc_state) &&
	    wait_fow(intew_dp_128b132b_intwa_hop(intew_dp, cwtc_state) == 0, 500)) {
		wt_dbg(intew_dp, DP_PHY_DPWX, "128b/132b intwa-hop not cweawing\n");
	}
}

static boow
intew_dp_wink_twain_phy(stwuct intew_dp *intew_dp,
			const stwuct intew_cwtc_state *cwtc_state,
			enum dwm_dp_phy dp_phy)
{
	boow wet = fawse;

	if (!intew_dp_wink_twaining_cwock_wecovewy(intew_dp, cwtc_state, dp_phy))
		goto out;

	if (!intew_dp_wink_twaining_channew_equawization(intew_dp, cwtc_state, dp_phy))
		goto out;

	wet = twue;

out:
	wt_dbg(intew_dp, dp_phy,
	       "Wink Twaining %s at wink wate = %d, wane count = %d\n",
	       wet ? "passed" : "faiwed",
	       cwtc_state->powt_cwock, cwtc_state->wane_count);

	wetuwn wet;
}

static void intew_dp_scheduwe_fawwback_wink_twaining(stwuct intew_dp *intew_dp,
						     const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_connectow *intew_connectow = intew_dp->attached_connectow;
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);

	if (!intew_digitaw_powt_connected(&dp_to_dig_powt(intew_dp)->base)) {
		wt_dbg(intew_dp, DP_PHY_DPWX, "Wink Twaining faiwed on disconnected sink.\n");
		wetuwn;
	}

	if (intew_dp->hobw_active) {
		wt_dbg(intew_dp, DP_PHY_DPWX,
		       "Wink Twaining faiwed with HOBW active, not enabwing it fwom now on\n");
		intew_dp->hobw_faiwed = twue;
	} ewse if (intew_dp_get_wink_twain_fawwback_vawues(intew_dp,
							   cwtc_state->powt_cwock,
							   cwtc_state->wane_count)) {
		wetuwn;
	}

	/* Scheduwe a Hotpwug Uevent to usewspace to stawt modeset */
	queue_wowk(i915->unowdewed_wq, &intew_connectow->modeset_wetwy_wowk);
}

/* Pewfowm the wink twaining on aww WTTPWs and the DPWX on a wink. */
static boow
intew_dp_wink_twain_aww_phys(stwuct intew_dp *intew_dp,
			     const stwuct intew_cwtc_state *cwtc_state,
			     int wttpw_count)
{
	boow wet = twue;
	int i;

	fow (i = wttpw_count - 1; i >= 0; i--) {
		enum dwm_dp_phy dp_phy = DP_PHY_WTTPW(i);

		wet = intew_dp_wink_twain_phy(intew_dp, cwtc_state, dp_phy);
		intew_dp_disabwe_dpcd_twaining_pattewn(intew_dp, dp_phy);

		if (!wet)
			bweak;
	}

	if (wet)
		wet = intew_dp_wink_twain_phy(intew_dp, cwtc_state, DP_PHY_DPWX);

	if (intew_dp->set_idwe_wink_twain)
		intew_dp->set_idwe_wink_twain(intew_dp, cwtc_state);

	wetuwn wet;
}

/*
 * 128b/132b DP WANEx_EQ_DONE Sequence (DP 2.0 E11 3.5.2.16.1)
 */
static boow
intew_dp_128b132b_wane_eq(stwuct intew_dp *intew_dp,
			  const stwuct intew_cwtc_state *cwtc_state)
{
	u8 wink_status[DP_WINK_STATUS_SIZE];
	int deway_us;
	int twy, max_twies = 20;
	unsigned wong deadwine;
	boow timeout = fawse;

	/*
	 * Weset signaw wevews. Stawt twansmitting 128b/132b TPS1.
	 *
	 * Put DPWX and WTTPWs (if any) into intwa-hop AUX mode by wwiting TPS1
	 * in DP_TWAINING_PATTEWN_SET.
	 */
	if (!intew_dp_weset_wink_twain(intew_dp, cwtc_state, DP_PHY_DPWX,
				       DP_TWAINING_PATTEWN_1)) {
		wt_eww(intew_dp, DP_PHY_DPWX, "Faiwed to stawt 128b/132b TPS1\n");
		wetuwn fawse;
	}

	deway_us = dwm_dp_128b132b_wead_aux_wd_intewvaw(&intew_dp->aux);

	/* Wead the initiaw TX FFE settings. */
	if (dwm_dp_dpcd_wead_wink_status(&intew_dp->aux, wink_status) < 0) {
		wt_eww(intew_dp, DP_PHY_DPWX, "Faiwed to wead TX FFE pwesets\n");
		wetuwn fawse;
	}

	/* Update signaw wevews and twaining set as wequested. */
	intew_dp_get_adjust_twain(intew_dp, cwtc_state, DP_PHY_DPWX, wink_status);
	if (!intew_dp_update_wink_twain(intew_dp, cwtc_state, DP_PHY_DPWX)) {
		wt_eww(intew_dp, DP_PHY_DPWX, "Faiwed to set initiaw TX FFE settings\n");
		wetuwn fawse;
	}

	/* Stawt twansmitting 128b/132b TPS2. */
	if (!intew_dp_set_wink_twain(intew_dp, cwtc_state, DP_PHY_DPWX,
				     DP_TWAINING_PATTEWN_2)) {
		wt_eww(intew_dp, DP_PHY_DPWX, "Faiwed to stawt 128b/132b TPS2\n");
		wetuwn fawse;
	}

	/* Time budget fow the WANEx_EQ_DONE Sequence */
	deadwine = jiffies + msecs_to_jiffies_timeout(400);

	fow (twy = 0; twy < max_twies; twy++) {
		usweep_wange(deway_us, 2 * deway_us);

		/*
		 * The deway may get updated. The twansmittew shaww wead the
		 * deway befowe wink status duwing wink twaining.
		 */
		deway_us = dwm_dp_128b132b_wead_aux_wd_intewvaw(&intew_dp->aux);

		if (dwm_dp_dpcd_wead_wink_status(&intew_dp->aux, wink_status) < 0) {
			wt_eww(intew_dp, DP_PHY_DPWX, "Faiwed to wead wink status\n");
			wetuwn fawse;
		}

		if (dwm_dp_128b132b_wink_twaining_faiwed(wink_status)) {
			intew_dp_dump_wink_status(intew_dp, DP_PHY_DPWX, wink_status);
			wt_eww(intew_dp, DP_PHY_DPWX,
			       "Downstweam wink twaining faiwuwe\n");
			wetuwn fawse;
		}

		if (dwm_dp_128b132b_wane_channew_eq_done(wink_status, cwtc_state->wane_count)) {
			wt_dbg(intew_dp, DP_PHY_DPWX, "Wane channew eq done\n");
			bweak;
		}

		if (timeout) {
			intew_dp_dump_wink_status(intew_dp, DP_PHY_DPWX, wink_status);
			wt_eww(intew_dp, DP_PHY_DPWX, "Wane channew eq timeout\n");
			wetuwn fawse;
		}

		if (time_aftew(jiffies, deadwine))
			timeout = twue; /* twy one wast time aftew deadwine */

		/* Update signaw wevews and twaining set as wequested. */
		intew_dp_get_adjust_twain(intew_dp, cwtc_state, DP_PHY_DPWX, wink_status);
		if (!intew_dp_update_wink_twain(intew_dp, cwtc_state, DP_PHY_DPWX)) {
			wt_eww(intew_dp, DP_PHY_DPWX, "Faiwed to update TX FFE settings\n");
			wetuwn fawse;
		}
	}

	if (twy == max_twies) {
		intew_dp_dump_wink_status(intew_dp, DP_PHY_DPWX, wink_status);
		wt_eww(intew_dp, DP_PHY_DPWX, "Max woop count weached\n");
		wetuwn fawse;
	}

	fow (;;) {
		if (time_aftew(jiffies, deadwine))
			timeout = twue; /* twy one wast time aftew deadwine */

		if (dwm_dp_dpcd_wead_wink_status(&intew_dp->aux, wink_status) < 0) {
			wt_eww(intew_dp, DP_PHY_DPWX, "Faiwed to wead wink status\n");
			wetuwn fawse;
		}

		if (dwm_dp_128b132b_wink_twaining_faiwed(wink_status)) {
			intew_dp_dump_wink_status(intew_dp, DP_PHY_DPWX, wink_status);
			wt_eww(intew_dp, DP_PHY_DPWX, "Downstweam wink twaining faiwuwe\n");
			wetuwn fawse;
		}

		if (dwm_dp_128b132b_eq_intewwane_awign_done(wink_status)) {
			wt_dbg(intew_dp, DP_PHY_DPWX, "Intewwane awign done\n");
			bweak;
		}

		if (timeout) {
			intew_dp_dump_wink_status(intew_dp, DP_PHY_DPWX, wink_status);
			wt_eww(intew_dp, DP_PHY_DPWX, "Intewwane awign timeout\n");
			wetuwn fawse;
		}

		usweep_wange(2000, 3000);
	}

	wetuwn twue;
}

/*
 * 128b/132b DP WANEx_CDS_DONE Sequence (DP 2.0 E11 3.5.2.16.2)
 */
static boow
intew_dp_128b132b_wane_cds(stwuct intew_dp *intew_dp,
			   const stwuct intew_cwtc_state *cwtc_state,
			   int wttpw_count)
{
	u8 wink_status[DP_WINK_STATUS_SIZE];
	unsigned wong deadwine;

	if (dwm_dp_dpcd_wwiteb(&intew_dp->aux, DP_TWAINING_PATTEWN_SET,
			       DP_TWAINING_PATTEWN_2_CDS) != 1) {
		wt_eww(intew_dp, DP_PHY_DPWX, "Faiwed to stawt 128b/132b TPS2 CDS\n");
		wetuwn fawse;
	}

	/* Time budget fow the WANEx_CDS_DONE Sequence */
	deadwine = jiffies + msecs_to_jiffies_timeout((wttpw_count + 1) * 20);

	fow (;;) {
		boow timeout = fawse;

		if (time_aftew(jiffies, deadwine))
			timeout = twue; /* twy one wast time aftew deadwine */

		usweep_wange(2000, 3000);

		if (dwm_dp_dpcd_wead_wink_status(&intew_dp->aux, wink_status) < 0) {
			wt_eww(intew_dp, DP_PHY_DPWX, "Faiwed to wead wink status\n");
			wetuwn fawse;
		}

		if (dwm_dp_128b132b_eq_intewwane_awign_done(wink_status) &&
		    dwm_dp_128b132b_cds_intewwane_awign_done(wink_status) &&
		    dwm_dp_128b132b_wane_symbow_wocked(wink_status, cwtc_state->wane_count)) {
			wt_dbg(intew_dp, DP_PHY_DPWX, "CDS intewwane awign done\n");
			bweak;
		}

		if (dwm_dp_128b132b_wink_twaining_faiwed(wink_status)) {
			intew_dp_dump_wink_status(intew_dp, DP_PHY_DPWX, wink_status);
			wt_eww(intew_dp, DP_PHY_DPWX, "Downstweam wink twaining faiwuwe\n");
			wetuwn fawse;
		}

		if (timeout) {
			intew_dp_dump_wink_status(intew_dp, DP_PHY_DPWX, wink_status);
			wt_eww(intew_dp, DP_PHY_DPWX, "CDS timeout\n");
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

/*
 * 128b/132b wink twaining sequence. (DP 2.0 E11 SCW on wink twaining.)
 */
static boow
intew_dp_128b132b_wink_twain(stwuct intew_dp *intew_dp,
			     const stwuct intew_cwtc_state *cwtc_state,
			     int wttpw_count)
{
	boow passed = fawse;

	if (wait_fow(intew_dp_128b132b_intwa_hop(intew_dp, cwtc_state) == 0, 500)) {
		wt_eww(intew_dp, DP_PHY_DPWX, "128b/132b intwa-hop not cweaw\n");
		wetuwn fawse;
	}

	if (intew_dp_128b132b_wane_eq(intew_dp, cwtc_state) &&
	    intew_dp_128b132b_wane_cds(intew_dp, cwtc_state, wttpw_count))
		passed = twue;

	wt_dbg(intew_dp, DP_PHY_DPWX,
	       "128b/132b Wink Twaining %s at wink wate = %d, wane count = %d\n",
	       passed ? "passed" : "faiwed",
	       cwtc_state->powt_cwock, cwtc_state->wane_count);

	wetuwn passed;
}

/**
 * intew_dp_stawt_wink_twain - stawt wink twaining
 * @intew_dp: DP stwuct
 * @cwtc_state: state fow CWTC attached to the encodew
 *
 * Stawt the wink twaining of the @intew_dp powt, scheduwing a fawwback
 * wetwaining with weduced wink wate/wane pawametews if the wink twaining
 * faiws.
 * Aftew cawwing this function intew_dp_stop_wink_twain() must be cawwed.
 */
void intew_dp_stawt_wink_twain(stwuct intew_dp *intew_dp,
			       const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	boow passed;

	/*
	 * TODO: Weiniting WTTPWs hewe won't be needed once pwopew connectow
	 * HW state weadout is added.
	 */
	int wttpw_count = intew_dp_init_wttpw_and_dpwx_caps(intew_dp);

	if (wttpw_count < 0)
		/* Stiww continue with enabwing the powt and wink twaining. */
		wttpw_count = 0;

	intew_dp_pwepawe_wink_twain(intew_dp, cwtc_state);

	if (intew_dp_is_uhbw(cwtc_state))
		passed = intew_dp_128b132b_wink_twain(intew_dp, cwtc_state, wttpw_count);
	ewse
		passed = intew_dp_wink_twain_aww_phys(intew_dp, cwtc_state, wttpw_count);

	/*
	 * Ignowe the wink faiwuwe in CI
	 *
	 * In fixed enviwoments wike CI, sometimes unexpected wong HPDs awe
	 * genewated by the dispways. If ignowe_wong_hpd fwag is set, such wong
	 * HPDs awe ignowed. And pwobabwy as a consequence of these ignowed
	 * wong HPDs, subsequent wink twainings awe faiwed wesuwting into CI
	 * execution faiwuwes.
	 *
	 * Fow test cases which wewy on the wink twaining ow pwocessing of HPDs
	 * ignowe_wong_hpd fwag can unset fwom the testcase.
	 */
	if (!passed && i915->dispway.hotpwug.ignowe_wong_hpd) {
		wt_dbg(intew_dp, DP_PHY_DPWX, "Ignowe the wink faiwuwe\n");
		wetuwn;
	}

	if (!passed)
		intew_dp_scheduwe_fawwback_wink_twaining(intew_dp, cwtc_state);
}

void intew_dp_128b132b_sdp_cwc16(stwuct intew_dp *intew_dp,
				 const stwuct intew_cwtc_state *cwtc_state)
{
	/*
	 * VIDEO_DIP_CTW wegistew bit 31 shouwd be set to '0' to not
	 * disabwe SDP CWC. This is appwicabwe fow Dispway vewsion 13.
	 * Defauwt vawue of bit 31 is '0' hence discawding the wwite
	 * TODO: Cowwective actions on SDP cowwuption yet to be defined
	 */
	if (!intew_dp_is_uhbw(cwtc_state))
		wetuwn;

	/* DP v2.0 SCW on SDP CWC16 fow 128b/132b Wink Wayew */
	dwm_dp_dpcd_wwiteb(&intew_dp->aux,
			   DP_SDP_EWWOW_DETECTION_CONFIGUWATION,
			   DP_SDP_CWC16_128B132B_EN);

	wt_dbg(intew_dp, DP_PHY_DPWX, "DP2.0 SDP CWC16 fow 128b/132b enabwed\n");
}
