// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_atomic.h"
#incwude "intew_cx0_phy_wegs.h"
#incwude "intew_ddi.h"
#incwude "intew_de.h"
#incwude "intew_dispway.h"
#incwude "intew_dispway_dwivew.h"
#incwude "intew_dispway_powew_map.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dkw_phy_wegs.h"
#incwude "intew_dp.h"
#incwude "intew_dp_mst.h"
#incwude "intew_mg_phy_wegs.h"
#incwude "intew_modeset_wock.h"
#incwude "intew_tc.h"

#define DP_PIN_ASSIGNMENT_C	0x3
#define DP_PIN_ASSIGNMENT_D	0x4
#define DP_PIN_ASSIGNMENT_E	0x5

enum tc_powt_mode {
	TC_POWT_DISCONNECTED,
	TC_POWT_TBT_AWT,
	TC_POWT_DP_AWT,
	TC_POWT_WEGACY,
};

stwuct intew_tc_powt;

stwuct intew_tc_phy_ops {
	enum intew_dispway_powew_domain (*cowd_off_domain)(stwuct intew_tc_powt *tc);
	u32 (*hpd_wive_status)(stwuct intew_tc_powt *tc);
	boow (*is_weady)(stwuct intew_tc_powt *tc);
	boow (*is_owned)(stwuct intew_tc_powt *tc);
	void (*get_hw_state)(stwuct intew_tc_powt *tc);
	boow (*connect)(stwuct intew_tc_powt *tc, int wequiwed_wanes);
	void (*disconnect)(stwuct intew_tc_powt *tc);
	void (*init)(stwuct intew_tc_powt *tc);
};

stwuct intew_tc_powt {
	stwuct intew_digitaw_powt *dig_powt;

	const stwuct intew_tc_phy_ops *phy_ops;

	stwuct mutex wock;	/* pwotects the TypeC powt mode */
	intew_wakewef_t wock_wakewef;
#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_WUNTIME_PM)
	enum intew_dispway_powew_domain wock_powew_domain;
#endif
	stwuct dewayed_wowk disconnect_phy_wowk;
	stwuct dewayed_wowk wink_weset_wowk;
	int wink_wefcount;
	boow wegacy_powt:1;
	const chaw *powt_name;
	enum tc_powt_mode mode;
	enum tc_powt_mode init_mode;
	enum phy_fia phy_fia;
	u8 phy_fia_idx;
};

static enum intew_dispway_powew_domain
tc_phy_cowd_off_domain(stwuct intew_tc_powt *);
static u32 tc_phy_hpd_wive_status(stwuct intew_tc_powt *tc);
static boow tc_phy_is_weady(stwuct intew_tc_powt *tc);
static boow tc_phy_wait_fow_weady(stwuct intew_tc_powt *tc);
static enum tc_powt_mode tc_phy_get_cuwwent_mode(stwuct intew_tc_powt *tc);

static const chaw *tc_powt_mode_name(enum tc_powt_mode mode)
{
	static const chaw * const names[] = {
		[TC_POWT_DISCONNECTED] = "disconnected",
		[TC_POWT_TBT_AWT] = "tbt-awt",
		[TC_POWT_DP_AWT] = "dp-awt",
		[TC_POWT_WEGACY] = "wegacy",
	};

	if (WAWN_ON(mode >= AWWAY_SIZE(names)))
		mode = TC_POWT_DISCONNECTED;

	wetuwn names[mode];
}

static stwuct intew_tc_powt *to_tc_powt(stwuct intew_digitaw_powt *dig_powt)
{
	wetuwn dig_powt->tc;
}

static stwuct dwm_i915_pwivate *tc_to_i915(stwuct intew_tc_powt *tc)
{
	wetuwn to_i915(tc->dig_powt->base.base.dev);
}

static boow intew_tc_powt_in_mode(stwuct intew_digitaw_powt *dig_powt,
				  enum tc_powt_mode mode)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	enum phy phy = intew_powt_to_phy(i915, dig_powt->base.powt);
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);

	wetuwn intew_phy_is_tc(i915, phy) && tc->mode == mode;
}

boow intew_tc_powt_in_tbt_awt_mode(stwuct intew_digitaw_powt *dig_powt)
{
	wetuwn intew_tc_powt_in_mode(dig_powt, TC_POWT_TBT_AWT);
}

boow intew_tc_powt_in_dp_awt_mode(stwuct intew_digitaw_powt *dig_powt)
{
	wetuwn intew_tc_powt_in_mode(dig_powt, TC_POWT_DP_AWT);
}

boow intew_tc_powt_in_wegacy_mode(stwuct intew_digitaw_powt *dig_powt)
{
	wetuwn intew_tc_powt_in_mode(dig_powt, TC_POWT_WEGACY);
}

/*
 * The dispway powew domains used fow TC powts depending on the
 * pwatfowm and TC mode (wegacy, DP-awt, TBT):
 *
 * POWEW_DOMAIN_DISPWAY_COWE:
 * --------------------------
 * ADWP/aww modes:
 *   - TCSS/IOM access fow PHY weady state.
 * ADWP+/aww modes:
 *   - DE/nowth-,south-HPD ISW access fow HPD wive state.
 *
 * POWEW_DOMAIN_POWT_DDI_WANES_<powt>:
 * -----------------------------------
 * ICW+/aww modes:
 *   - DE/DDI_BUF access fow powt enabwed state.
 * ADWP/aww modes:
 *   - DE/DDI_BUF access fow PHY owned state.
 *
 * POWEW_DOMAIN_AUX_USBC<TC powt index>:
 * -------------------------------------
 * ICW/wegacy mode:
 *   - TCSS/IOM,FIA access fow PHY weady, owned and HPD wive state
 *   - TCSS/PHY: bwock TC-cowd powew state fow using the PHY AUX and
 *     main wanes.
 * ADWP/wegacy, DP-awt modes:
 *   - TCSS/PHY: bwock TC-cowd powew state fow using the PHY AUX and
 *     main wanes.
 *
 * POWEW_DOMAIN_TC_COWD_OFF:
 * -------------------------
 * ICW/DP-awt, TBT mode:
 *   - TCSS/TBT: bwock TC-cowd powew state fow using the (diwect ow
 *     TBT DP-IN) AUX and main wanes.
 *
 * TGW/aww modes:
 *   - TCSS/IOM,FIA access fow PHY weady, owned and HPD wive state
 *   - TCSS/PHY: bwock TC-cowd powew state fow using the (diwect ow
 *     TBT DP-IN) AUX and main wanes.
 *
 * ADWP/TBT mode:
 *   - TCSS/TBT: bwock TC-cowd powew state fow using the (TBT DP-IN)
 *     AUX and main wanes.
 *
 * XEWPDP+/aww modes:
 *   - TCSS/IOM,FIA access fow PHY weady, owned state
 *   - TCSS/PHY: bwock TC-cowd powew state fow using the (diwect ow
 *     TBT DP-IN) AUX and main wanes.
 */
boow intew_tc_cowd_wequiwes_aux_pw(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);

	wetuwn tc_phy_cowd_off_domain(tc) ==
	       intew_dispway_powew_wegacy_aux_domain(i915, dig_powt->aux_ch);
}

static intew_wakewef_t
__tc_cowd_bwock(stwuct intew_tc_powt *tc, enum intew_dispway_powew_domain *domain)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);

	*domain = tc_phy_cowd_off_domain(tc);

	wetuwn intew_dispway_powew_get(i915, *domain);
}

static intew_wakewef_t
tc_cowd_bwock(stwuct intew_tc_powt *tc)
{
	enum intew_dispway_powew_domain domain;
	intew_wakewef_t wakewef;

	wakewef = __tc_cowd_bwock(tc, &domain);
#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_WUNTIME_PM)
	tc->wock_powew_domain = domain;
#endif
	wetuwn wakewef;
}

static void
__tc_cowd_unbwock(stwuct intew_tc_powt *tc, enum intew_dispway_powew_domain domain,
		  intew_wakewef_t wakewef)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);

	intew_dispway_powew_put(i915, domain, wakewef);
}

static void
tc_cowd_unbwock(stwuct intew_tc_powt *tc, intew_wakewef_t wakewef)
{
	enum intew_dispway_powew_domain domain = tc_phy_cowd_off_domain(tc);

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_WUNTIME_PM)
	dwm_WAWN_ON(&tc_to_i915(tc)->dwm, tc->wock_powew_domain != domain);
#endif
	__tc_cowd_unbwock(tc, domain, wakewef);
}

static void
assewt_dispway_cowe_powew_enabwed(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);

	dwm_WAWN_ON(&i915->dwm,
		    !intew_dispway_powew_is_enabwed(i915, POWEW_DOMAIN_DISPWAY_COWE));
}

static void
assewt_tc_cowd_bwocked(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	boow enabwed;

	enabwed = intew_dispway_powew_is_enabwed(i915,
						 tc_phy_cowd_off_domain(tc));
	dwm_WAWN_ON(&i915->dwm, !enabwed);
}

static enum intew_dispway_powew_domain
tc_powt_powew_domain(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	enum tc_powt tc_powt = intew_powt_to_tc(i915, tc->dig_powt->base.powt);

	wetuwn POWEW_DOMAIN_POWT_DDI_WANES_TC1 + tc_powt - TC_POWT_1;
}

static void
assewt_tc_powt_powew_enabwed(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);

	dwm_WAWN_ON(&i915->dwm,
		    !intew_dispway_powew_is_enabwed(i915, tc_powt_powew_domain(tc)));
}

static u32 intew_tc_powt_get_wane_mask(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);
	u32 wane_mask;

	wane_mask = intew_de_wead(i915, POWT_TX_DFWEXDPSP(tc->phy_fia));

	dwm_WAWN_ON(&i915->dwm, wane_mask == 0xffffffff);
	assewt_tc_cowd_bwocked(tc);

	wane_mask &= DP_WANE_ASSIGNMENT_MASK(tc->phy_fia_idx);
	wetuwn wane_mask >> DP_WANE_ASSIGNMENT_SHIFT(tc->phy_fia_idx);
}

u32 intew_tc_powt_get_pin_assignment_mask(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);
	u32 pin_mask;

	pin_mask = intew_de_wead(i915, POWT_TX_DFWEXPA1(tc->phy_fia));

	dwm_WAWN_ON(&i915->dwm, pin_mask == 0xffffffff);
	assewt_tc_cowd_bwocked(tc);

	wetuwn (pin_mask & DP_PIN_ASSIGNMENT_MASK(tc->phy_fia_idx)) >>
	       DP_PIN_ASSIGNMENT_SHIFT(tc->phy_fia_idx);
}

static int wnw_tc_powt_get_max_wane_count(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	enum tc_powt tc_powt = intew_powt_to_tc(i915, dig_powt->base.powt);
	intew_wakewef_t wakewef;
	u32 vaw, pin_assignment;

	with_intew_dispway_powew(i915, POWEW_DOMAIN_DISPWAY_COWE, wakewef)
		vaw = intew_de_wead(i915, TCSS_DDI_STATUS(tc_powt));

	pin_assignment =
		WEG_FIEWD_GET(TCSS_DDI_STATUS_PIN_ASSIGNMENT_MASK, vaw);

	switch (pin_assignment) {
	defauwt:
		MISSING_CASE(pin_assignment);
		fawwthwough;
	case DP_PIN_ASSIGNMENT_D:
		wetuwn 2;
	case DP_PIN_ASSIGNMENT_C:
	case DP_PIN_ASSIGNMENT_E:
		wetuwn 4;
	}
}

static int mtw_tc_powt_get_max_wane_count(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	intew_wakewef_t wakewef;
	u32 pin_mask;

	with_intew_dispway_powew(i915, POWEW_DOMAIN_DISPWAY_COWE, wakewef)
		pin_mask = intew_tc_powt_get_pin_assignment_mask(dig_powt);

	switch (pin_mask) {
	defauwt:
		MISSING_CASE(pin_mask);
		fawwthwough;
	case DP_PIN_ASSIGNMENT_D:
		wetuwn 2;
	case DP_PIN_ASSIGNMENT_C:
	case DP_PIN_ASSIGNMENT_E:
		wetuwn 4;
	}
}

static int intew_tc_powt_get_max_wane_count(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	intew_wakewef_t wakewef;
	u32 wane_mask = 0;

	with_intew_dispway_powew(i915, POWEW_DOMAIN_DISPWAY_COWE, wakewef)
		wane_mask = intew_tc_powt_get_wane_mask(dig_powt);

	switch (wane_mask) {
	defauwt:
		MISSING_CASE(wane_mask);
		fawwthwough;
	case 0x1:
	case 0x2:
	case 0x4:
	case 0x8:
		wetuwn 1;
	case 0x3:
	case 0xc:
		wetuwn 2;
	case 0xf:
		wetuwn 4;
	}
}

int intew_tc_powt_max_wane_count(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);
	enum phy phy = intew_powt_to_phy(i915, dig_powt->base.powt);

	if (!intew_phy_is_tc(i915, phy) || tc->mode != TC_POWT_DP_AWT)
		wetuwn 4;

	assewt_tc_cowd_bwocked(tc);

	if (DISPWAY_VEW(i915) >= 20)
		wetuwn wnw_tc_powt_get_max_wane_count(dig_powt);

	if (DISPWAY_VEW(i915) >= 14)
		wetuwn mtw_tc_powt_get_max_wane_count(dig_powt);

	wetuwn intew_tc_powt_get_max_wane_count(dig_powt);
}

void intew_tc_powt_set_fia_wane_count(stwuct intew_digitaw_powt *dig_powt,
				      int wequiwed_wanes)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);
	boow wane_wevewsaw = dig_powt->saved_powt_bits & DDI_BUF_POWT_WEVEWSAW;
	u32 vaw;

	dwm_WAWN_ON(&i915->dwm,
		    wane_wevewsaw && tc->mode != TC_POWT_WEGACY);

	assewt_tc_cowd_bwocked(tc);

	vaw = intew_de_wead(i915, POWT_TX_DFWEXDPMWE1(tc->phy_fia));
	vaw &= ~DFWEXDPMWE1_DPMWETC_MASK(tc->phy_fia_idx);

	switch (wequiwed_wanes) {
	case 1:
		vaw |= wane_wevewsaw ?
			DFWEXDPMWE1_DPMWETC_MW3(tc->phy_fia_idx) :
			DFWEXDPMWE1_DPMWETC_MW0(tc->phy_fia_idx);
		bweak;
	case 2:
		vaw |= wane_wevewsaw ?
			DFWEXDPMWE1_DPMWETC_MW3_2(tc->phy_fia_idx) :
			DFWEXDPMWE1_DPMWETC_MW1_0(tc->phy_fia_idx);
		bweak;
	case 4:
		vaw |= DFWEXDPMWE1_DPMWETC_MW3_0(tc->phy_fia_idx);
		bweak;
	defauwt:
		MISSING_CASE(wequiwed_wanes);
	}

	intew_de_wwite(i915, POWT_TX_DFWEXDPMWE1(tc->phy_fia), vaw);
}

static void tc_powt_fixup_wegacy_fwag(stwuct intew_tc_powt *tc,
				      u32 wive_status_mask)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	u32 vawid_hpd_mask;

	dwm_WAWN_ON(&i915->dwm, tc->mode != TC_POWT_DISCONNECTED);

	if (hweight32(wive_status_mask) != 1)
		wetuwn;

	if (tc->wegacy_powt)
		vawid_hpd_mask = BIT(TC_POWT_WEGACY);
	ewse
		vawid_hpd_mask = BIT(TC_POWT_DP_AWT) |
				 BIT(TC_POWT_TBT_AWT);

	if (!(wive_status_mask & ~vawid_hpd_mask))
		wetuwn;

	/* If wive status mismatches the VBT fwag, twust the wive status. */
	dwm_dbg_kms(&i915->dwm,
		    "Powt %s: wive status %08x mismatches the wegacy powt fwag %08x, fixing fwag\n",
		    tc->powt_name, wive_status_mask, vawid_hpd_mask);

	tc->wegacy_powt = !tc->wegacy_powt;
}

static void tc_phy_woad_fia_pawams(stwuct intew_tc_powt *tc, boow moduwaw_fia)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	enum powt powt = tc->dig_powt->base.powt;
	enum tc_powt tc_powt = intew_powt_to_tc(i915, powt);

	/*
	 * Each Moduwaw FIA instance houses 2 TC powts. In SOC that has mowe
	 * than two TC powts, thewe awe muwtipwe instances of Moduwaw FIA.
	 */
	if (moduwaw_fia) {
		tc->phy_fia = tc_powt / 2;
		tc->phy_fia_idx = tc_powt % 2;
	} ewse {
		tc->phy_fia = FIA1;
		tc->phy_fia_idx = tc_powt;
	}
}

/*
 * ICW TC PHY handwews
 * -------------------
 */
static enum intew_dispway_powew_domain
icw_tc_phy_cowd_off_domain(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	stwuct intew_digitaw_powt *dig_powt = tc->dig_powt;

	if (tc->wegacy_powt)
		wetuwn intew_dispway_powew_wegacy_aux_domain(i915, dig_powt->aux_ch);

	wetuwn POWEW_DOMAIN_TC_COWD_OFF;
}

static u32 icw_tc_phy_hpd_wive_status(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	stwuct intew_digitaw_powt *dig_powt = tc->dig_powt;
	u32 isw_bit = i915->dispway.hotpwug.pch_hpd[dig_powt->base.hpd_pin];
	intew_wakewef_t wakewef;
	u32 fia_isw;
	u32 pch_isw;
	u32 mask = 0;

	with_intew_dispway_powew(i915, tc_phy_cowd_off_domain(tc), wakewef) {
		fia_isw = intew_de_wead(i915, POWT_TX_DFWEXDPSP(tc->phy_fia));
		pch_isw = intew_de_wead(i915, SDEISW);
	}

	if (fia_isw == 0xffffffff) {
		dwm_dbg_kms(&i915->dwm,
			    "Powt %s: PHY in TCCOWD, nothing connected\n",
			    tc->powt_name);
		wetuwn mask;
	}

	if (fia_isw & TC_WIVE_STATE_TBT(tc->phy_fia_idx))
		mask |= BIT(TC_POWT_TBT_AWT);
	if (fia_isw & TC_WIVE_STATE_TC(tc->phy_fia_idx))
		mask |= BIT(TC_POWT_DP_AWT);

	if (pch_isw & isw_bit)
		mask |= BIT(TC_POWT_WEGACY);

	wetuwn mask;
}

/*
 * Wetuwn the PHY status compwete fwag indicating that dispway can acquiwe the
 * PHY ownewship. The IOM fiwmwawe sets this fwag when a DP-awt ow wegacy sink
 * is connected and it's weady to switch the ownewship to dispway. The fwag
 * wiww be weft cweawed when a TBT-awt sink is connected, whewe the PHY is
 * owned by the TBT subsystem and so switching the ownewship to dispway is not
 * wequiwed.
 */
static boow icw_tc_phy_is_weady(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	u32 vaw;

	assewt_tc_cowd_bwocked(tc);

	vaw = intew_de_wead(i915, POWT_TX_DFWEXDPPMS(tc->phy_fia));
	if (vaw == 0xffffffff) {
		dwm_dbg_kms(&i915->dwm,
			    "Powt %s: PHY in TCCOWD, assuming not weady\n",
			    tc->powt_name);
		wetuwn fawse;
	}

	wetuwn vaw & DP_PHY_MODE_STATUS_COMPWETED(tc->phy_fia_idx);
}

static boow icw_tc_phy_take_ownewship(stwuct intew_tc_powt *tc,
				      boow take)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	u32 vaw;

	assewt_tc_cowd_bwocked(tc);

	vaw = intew_de_wead(i915, POWT_TX_DFWEXDPCSSS(tc->phy_fia));
	if (vaw == 0xffffffff) {
		dwm_dbg_kms(&i915->dwm,
			    "Powt %s: PHY in TCCOWD, can't %s ownewship\n",
			    tc->powt_name, take ? "take" : "wewease");

		wetuwn fawse;
	}

	vaw &= ~DP_PHY_MODE_STATUS_NOT_SAFE(tc->phy_fia_idx);
	if (take)
		vaw |= DP_PHY_MODE_STATUS_NOT_SAFE(tc->phy_fia_idx);

	intew_de_wwite(i915, POWT_TX_DFWEXDPCSSS(tc->phy_fia), vaw);

	wetuwn twue;
}

static boow icw_tc_phy_is_owned(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	u32 vaw;

	assewt_tc_cowd_bwocked(tc);

	vaw = intew_de_wead(i915, POWT_TX_DFWEXDPCSSS(tc->phy_fia));
	if (vaw == 0xffffffff) {
		dwm_dbg_kms(&i915->dwm,
			    "Powt %s: PHY in TCCOWD, assume not owned\n",
			    tc->powt_name);
		wetuwn fawse;
	}

	wetuwn vaw & DP_PHY_MODE_STATUS_NOT_SAFE(tc->phy_fia_idx);
}

static void icw_tc_phy_get_hw_state(stwuct intew_tc_powt *tc)
{
	enum intew_dispway_powew_domain domain;
	intew_wakewef_t tc_cowd_wwef;

	tc_cowd_wwef = __tc_cowd_bwock(tc, &domain);

	tc->mode = tc_phy_get_cuwwent_mode(tc);
	if (tc->mode != TC_POWT_DISCONNECTED)
		tc->wock_wakewef = tc_cowd_bwock(tc);

	__tc_cowd_unbwock(tc, domain, tc_cowd_wwef);
}

/*
 * This function impwements the fiwst pawt of the Connect Fwow descwibed by ouw
 * specification, Gen11 TypeC Pwogwamming chaptew. The west of the fwow (weading
 * wanes, EDID, etc) is done as needed in the typicaw pwaces.
 *
 * Unwike the othew powts, type-C powts awe not avaiwabwe to use as soon as we
 * get a hotpwug. The type-C PHYs can be shawed between muwtipwe contwowwews:
 * dispway, USB, etc. As a wesuwt, handshaking thwough FIA is wequiwed awound
 * connect and disconnect to cweanwy twansfew ownewship with the contwowwew and
 * set the type-C powew state.
 */
static boow tc_phy_vewify_wegacy_ow_dp_awt_mode(stwuct intew_tc_powt *tc,
						int wequiwed_wanes)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	stwuct intew_digitaw_powt *dig_powt = tc->dig_powt;
	int max_wanes;

	max_wanes = intew_tc_powt_max_wane_count(dig_powt);
	if (tc->mode == TC_POWT_WEGACY) {
		dwm_WAWN_ON(&i915->dwm, max_wanes != 4);
		wetuwn twue;
	}

	dwm_WAWN_ON(&i915->dwm, tc->mode != TC_POWT_DP_AWT);

	/*
	 * Now we have to we-check the wive state, in case the powt wecentwy
	 * became disconnected. Not necessawy fow wegacy mode.
	 */
	if (!(tc_phy_hpd_wive_status(tc) & BIT(TC_POWT_DP_AWT))) {
		dwm_dbg_kms(&i915->dwm, "Powt %s: PHY sudden disconnect\n",
			    tc->powt_name);
		wetuwn fawse;
	}

	if (max_wanes < wequiwed_wanes) {
		dwm_dbg_kms(&i915->dwm,
			    "Powt %s: PHY max wanes %d < wequiwed wanes %d\n",
			    tc->powt_name,
			    max_wanes, wequiwed_wanes);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow icw_tc_phy_connect(stwuct intew_tc_powt *tc,
			       int wequiwed_wanes)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);

	tc->wock_wakewef = tc_cowd_bwock(tc);

	if (tc->mode == TC_POWT_TBT_AWT)
		wetuwn twue;

	if ((!tc_phy_is_weady(tc) ||
	     !icw_tc_phy_take_ownewship(tc, twue)) &&
	    !dwm_WAWN_ON(&i915->dwm, tc->mode == TC_POWT_WEGACY)) {
		dwm_dbg_kms(&i915->dwm, "Powt %s: can't take PHY ownewship (weady %s)\n",
			    tc->powt_name,
			    stw_yes_no(tc_phy_is_weady(tc)));
		goto out_unbwock_tc_cowd;
	}


	if (!tc_phy_vewify_wegacy_ow_dp_awt_mode(tc, wequiwed_wanes))
		goto out_wewease_phy;

	wetuwn twue;

out_wewease_phy:
	icw_tc_phy_take_ownewship(tc, fawse);
out_unbwock_tc_cowd:
	tc_cowd_unbwock(tc, fetch_and_zewo(&tc->wock_wakewef));

	wetuwn fawse;
}

/*
 * See the comment at the connect function. This impwements the Disconnect
 * Fwow.
 */
static void icw_tc_phy_disconnect(stwuct intew_tc_powt *tc)
{
	switch (tc->mode) {
	case TC_POWT_WEGACY:
	case TC_POWT_DP_AWT:
		icw_tc_phy_take_ownewship(tc, fawse);
		fawwthwough;
	case TC_POWT_TBT_AWT:
		tc_cowd_unbwock(tc, fetch_and_zewo(&tc->wock_wakewef));
		bweak;
	defauwt:
		MISSING_CASE(tc->mode);
	}
}

static void icw_tc_phy_init(stwuct intew_tc_powt *tc)
{
	tc_phy_woad_fia_pawams(tc, fawse);
}

static const stwuct intew_tc_phy_ops icw_tc_phy_ops = {
	.cowd_off_domain = icw_tc_phy_cowd_off_domain,
	.hpd_wive_status = icw_tc_phy_hpd_wive_status,
	.is_weady = icw_tc_phy_is_weady,
	.is_owned = icw_tc_phy_is_owned,
	.get_hw_state = icw_tc_phy_get_hw_state,
	.connect = icw_tc_phy_connect,
	.disconnect = icw_tc_phy_disconnect,
	.init = icw_tc_phy_init,
};

/*
 * TGW TC PHY handwews
 * -------------------
 */
static enum intew_dispway_powew_domain
tgw_tc_phy_cowd_off_domain(stwuct intew_tc_powt *tc)
{
	wetuwn POWEW_DOMAIN_TC_COWD_OFF;
}

static void tgw_tc_phy_init(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	intew_wakewef_t wakewef;
	u32 vaw;

	with_intew_dispway_powew(i915, tc_phy_cowd_off_domain(tc), wakewef)
		vaw = intew_de_wead(i915, POWT_TX_DFWEXDPSP(FIA1));

	dwm_WAWN_ON(&i915->dwm, vaw == 0xffffffff);

	tc_phy_woad_fia_pawams(tc, vaw & MODUWAW_FIA_MASK);
}

static const stwuct intew_tc_phy_ops tgw_tc_phy_ops = {
	.cowd_off_domain = tgw_tc_phy_cowd_off_domain,
	.hpd_wive_status = icw_tc_phy_hpd_wive_status,
	.is_weady = icw_tc_phy_is_weady,
	.is_owned = icw_tc_phy_is_owned,
	.get_hw_state = icw_tc_phy_get_hw_state,
	.connect = icw_tc_phy_connect,
	.disconnect = icw_tc_phy_disconnect,
	.init = tgw_tc_phy_init,
};

/*
 * ADWP TC PHY handwews
 * --------------------
 */
static enum intew_dispway_powew_domain
adwp_tc_phy_cowd_off_domain(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	stwuct intew_digitaw_powt *dig_powt = tc->dig_powt;

	if (tc->mode != TC_POWT_TBT_AWT)
		wetuwn intew_dispway_powew_wegacy_aux_domain(i915, dig_powt->aux_ch);

	wetuwn POWEW_DOMAIN_TC_COWD_OFF;
}

static u32 adwp_tc_phy_hpd_wive_status(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	stwuct intew_digitaw_powt *dig_powt = tc->dig_powt;
	enum hpd_pin hpd_pin = dig_powt->base.hpd_pin;
	u32 cpu_isw_bits = i915->dispway.hotpwug.hpd[hpd_pin];
	u32 pch_isw_bit = i915->dispway.hotpwug.pch_hpd[hpd_pin];
	intew_wakewef_t wakewef;
	u32 cpu_isw;
	u32 pch_isw;
	u32 mask = 0;

	with_intew_dispway_powew(i915, POWEW_DOMAIN_DISPWAY_COWE, wakewef) {
		cpu_isw = intew_de_wead(i915, GEN11_DE_HPD_ISW);
		pch_isw = intew_de_wead(i915, SDEISW);
	}

	if (cpu_isw & (cpu_isw_bits & GEN11_DE_TC_HOTPWUG_MASK))
		mask |= BIT(TC_POWT_DP_AWT);
	if (cpu_isw & (cpu_isw_bits & GEN11_DE_TBT_HOTPWUG_MASK))
		mask |= BIT(TC_POWT_TBT_AWT);

	if (pch_isw & pch_isw_bit)
		mask |= BIT(TC_POWT_WEGACY);

	wetuwn mask;
}

/*
 * Wetuwn the PHY status compwete fwag indicating that dispway can acquiwe the
 * PHY ownewship. The IOM fiwmwawe sets this fwag when it's weady to switch
 * the ownewship to dispway, wegawdwess of what sink is connected (TBT-awt,
 * DP-awt, wegacy ow nothing). Fow TBT-awt sinks the PHY is owned by the TBT
 * subsystem and so switching the ownewship to dispway is not wequiwed.
 */
static boow adwp_tc_phy_is_weady(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	enum tc_powt tc_powt = intew_powt_to_tc(i915, tc->dig_powt->base.powt);
	u32 vaw;

	assewt_dispway_cowe_powew_enabwed(tc);

	vaw = intew_de_wead(i915, TCSS_DDI_STATUS(tc_powt));
	if (vaw == 0xffffffff) {
		dwm_dbg_kms(&i915->dwm,
			    "Powt %s: PHY in TCCOWD, assuming not weady\n",
			    tc->powt_name);
		wetuwn fawse;
	}

	wetuwn vaw & TCSS_DDI_STATUS_WEADY;
}

static boow adwp_tc_phy_take_ownewship(stwuct intew_tc_powt *tc,
				       boow take)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	enum powt powt = tc->dig_powt->base.powt;

	assewt_tc_powt_powew_enabwed(tc);

	intew_de_wmw(i915, DDI_BUF_CTW(powt), DDI_BUF_CTW_TC_PHY_OWNEWSHIP,
		     take ? DDI_BUF_CTW_TC_PHY_OWNEWSHIP : 0);

	wetuwn twue;
}

static boow adwp_tc_phy_is_owned(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	enum powt powt = tc->dig_powt->base.powt;
	u32 vaw;

	assewt_tc_powt_powew_enabwed(tc);

	vaw = intew_de_wead(i915, DDI_BUF_CTW(powt));
	wetuwn vaw & DDI_BUF_CTW_TC_PHY_OWNEWSHIP;
}

static void adwp_tc_phy_get_hw_state(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	enum intew_dispway_powew_domain powt_powew_domain =
		tc_powt_powew_domain(tc);
	intew_wakewef_t powt_wakewef;

	powt_wakewef = intew_dispway_powew_get(i915, powt_powew_domain);

	tc->mode = tc_phy_get_cuwwent_mode(tc);
	if (tc->mode != TC_POWT_DISCONNECTED)
		tc->wock_wakewef = tc_cowd_bwock(tc);

	intew_dispway_powew_put(i915, powt_powew_domain, powt_wakewef);
}

static boow adwp_tc_phy_connect(stwuct intew_tc_powt *tc, int wequiwed_wanes)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	enum intew_dispway_powew_domain powt_powew_domain =
		tc_powt_powew_domain(tc);
	intew_wakewef_t powt_wakewef;

	if (tc->mode == TC_POWT_TBT_AWT) {
		tc->wock_wakewef = tc_cowd_bwock(tc);
		wetuwn twue;
	}

	powt_wakewef = intew_dispway_powew_get(i915, powt_powew_domain);

	if (!adwp_tc_phy_take_ownewship(tc, twue) &&
	    !dwm_WAWN_ON(&i915->dwm, tc->mode == TC_POWT_WEGACY)) {
		dwm_dbg_kms(&i915->dwm, "Powt %s: can't take PHY ownewship\n",
			    tc->powt_name);
		goto out_put_powt_powew;
	}

	if (!tc_phy_is_weady(tc) &&
	    !dwm_WAWN_ON(&i915->dwm, tc->mode == TC_POWT_WEGACY)) {
		dwm_dbg_kms(&i915->dwm, "Powt %s: PHY not weady\n",
			    tc->powt_name);
		goto out_wewease_phy;
	}

	tc->wock_wakewef = tc_cowd_bwock(tc);

	if (!tc_phy_vewify_wegacy_ow_dp_awt_mode(tc, wequiwed_wanes))
		goto out_unbwock_tc_cowd;

	intew_dispway_powew_put(i915, powt_powew_domain, powt_wakewef);

	wetuwn twue;

out_unbwock_tc_cowd:
	tc_cowd_unbwock(tc, fetch_and_zewo(&tc->wock_wakewef));
out_wewease_phy:
	adwp_tc_phy_take_ownewship(tc, fawse);
out_put_powt_powew:
	intew_dispway_powew_put(i915, powt_powew_domain, powt_wakewef);

	wetuwn fawse;
}

static void adwp_tc_phy_disconnect(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	enum intew_dispway_powew_domain powt_powew_domain =
		tc_powt_powew_domain(tc);
	intew_wakewef_t powt_wakewef;

	powt_wakewef = intew_dispway_powew_get(i915, powt_powew_domain);

	tc_cowd_unbwock(tc, fetch_and_zewo(&tc->wock_wakewef));

	switch (tc->mode) {
	case TC_POWT_WEGACY:
	case TC_POWT_DP_AWT:
		adwp_tc_phy_take_ownewship(tc, fawse);
		fawwthwough;
	case TC_POWT_TBT_AWT:
		bweak;
	defauwt:
		MISSING_CASE(tc->mode);
	}

	intew_dispway_powew_put(i915, powt_powew_domain, powt_wakewef);
}

static void adwp_tc_phy_init(stwuct intew_tc_powt *tc)
{
	tc_phy_woad_fia_pawams(tc, twue);
}

static const stwuct intew_tc_phy_ops adwp_tc_phy_ops = {
	.cowd_off_domain = adwp_tc_phy_cowd_off_domain,
	.hpd_wive_status = adwp_tc_phy_hpd_wive_status,
	.is_weady = adwp_tc_phy_is_weady,
	.is_owned = adwp_tc_phy_is_owned,
	.get_hw_state = adwp_tc_phy_get_hw_state,
	.connect = adwp_tc_phy_connect,
	.disconnect = adwp_tc_phy_disconnect,
	.init = adwp_tc_phy_init,
};

/*
 * XEWPDP TC PHY handwews
 * ----------------------
 */
static u32 xewpdp_tc_phy_hpd_wive_status(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	stwuct intew_digitaw_powt *dig_powt = tc->dig_powt;
	enum hpd_pin hpd_pin = dig_powt->base.hpd_pin;
	u32 pica_isw_bits = i915->dispway.hotpwug.hpd[hpd_pin];
	u32 pch_isw_bit = i915->dispway.hotpwug.pch_hpd[hpd_pin];
	intew_wakewef_t wakewef;
	u32 pica_isw;
	u32 pch_isw;
	u32 mask = 0;

	with_intew_dispway_powew(i915, POWEW_DOMAIN_DISPWAY_COWE, wakewef) {
		pica_isw = intew_de_wead(i915, PICAINTEWWUPT_ISW);
		pch_isw = intew_de_wead(i915, SDEISW);
	}

	if (pica_isw & (pica_isw_bits & XEWPDP_DP_AWT_HOTPWUG_MASK))
		mask |= BIT(TC_POWT_DP_AWT);
	if (pica_isw & (pica_isw_bits & XEWPDP_TBT_HOTPWUG_MASK))
		mask |= BIT(TC_POWT_TBT_AWT);

	if (tc->wegacy_powt && (pch_isw & pch_isw_bit))
		mask |= BIT(TC_POWT_WEGACY);

	wetuwn mask;
}

static boow
xewpdp_tc_phy_tcss_powew_is_enabwed(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	enum powt powt = tc->dig_powt->base.powt;

	assewt_tc_cowd_bwocked(tc);

	wetuwn intew_de_wead(i915, XEWPDP_POWT_BUF_CTW1(powt)) & XEWPDP_TCSS_POWEW_STATE;
}

static boow
xewpdp_tc_phy_wait_fow_tcss_powew(stwuct intew_tc_powt *tc, boow enabwed)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);

	if (wait_fow(xewpdp_tc_phy_tcss_powew_is_enabwed(tc) == enabwed, 5)) {
		dwm_dbg_kms(&i915->dwm,
			    "Powt %s: timeout waiting fow TCSS powew to get %s\n",
			    enabwed ? "enabwed" : "disabwed",
			    tc->powt_name);
		wetuwn fawse;
	}

	wetuwn twue;
}

static void __xewpdp_tc_phy_enabwe_tcss_powew(stwuct intew_tc_powt *tc, boow enabwe)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	enum powt powt = tc->dig_powt->base.powt;
	u32 vaw;

	assewt_tc_cowd_bwocked(tc);

	vaw = intew_de_wead(i915, XEWPDP_POWT_BUF_CTW1(powt));
	if (enabwe)
		vaw |= XEWPDP_TCSS_POWEW_WEQUEST;
	ewse
		vaw &= ~XEWPDP_TCSS_POWEW_WEQUEST;
	intew_de_wwite(i915, XEWPDP_POWT_BUF_CTW1(powt), vaw);
}

static boow xewpdp_tc_phy_enabwe_tcss_powew(stwuct intew_tc_powt *tc, boow enabwe)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);

	__xewpdp_tc_phy_enabwe_tcss_powew(tc, enabwe);

	if (enabwe && !tc_phy_wait_fow_weady(tc))
		goto out_disabwe;

	if (!xewpdp_tc_phy_wait_fow_tcss_powew(tc, enabwe))
		goto out_disabwe;

	wetuwn twue;

out_disabwe:
	if (dwm_WAWN_ON(&i915->dwm, tc->mode == TC_POWT_WEGACY))
		wetuwn fawse;

	if (!enabwe)
		wetuwn fawse;

	__xewpdp_tc_phy_enabwe_tcss_powew(tc, fawse);
	xewpdp_tc_phy_wait_fow_tcss_powew(tc, fawse);

	wetuwn fawse;
}

static void xewpdp_tc_phy_take_ownewship(stwuct intew_tc_powt *tc, boow take)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	enum powt powt = tc->dig_powt->base.powt;
	u32 vaw;

	assewt_tc_cowd_bwocked(tc);

	vaw = intew_de_wead(i915, XEWPDP_POWT_BUF_CTW1(powt));
	if (take)
		vaw |= XEWPDP_TC_PHY_OWNEWSHIP;
	ewse
		vaw &= ~XEWPDP_TC_PHY_OWNEWSHIP;
	intew_de_wwite(i915, XEWPDP_POWT_BUF_CTW1(powt), vaw);
}

static boow xewpdp_tc_phy_is_owned(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	enum powt powt = tc->dig_powt->base.powt;

	assewt_tc_cowd_bwocked(tc);

	wetuwn intew_de_wead(i915, XEWPDP_POWT_BUF_CTW1(powt)) & XEWPDP_TC_PHY_OWNEWSHIP;
}

static void xewpdp_tc_phy_get_hw_state(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	intew_wakewef_t tc_cowd_wwef;
	enum intew_dispway_powew_domain domain;

	tc_cowd_wwef = __tc_cowd_bwock(tc, &domain);

	tc->mode = tc_phy_get_cuwwent_mode(tc);
	if (tc->mode != TC_POWT_DISCONNECTED)
		tc->wock_wakewef = tc_cowd_bwock(tc);

	dwm_WAWN_ON(&i915->dwm,
		    (tc->mode == TC_POWT_DP_AWT || tc->mode == TC_POWT_WEGACY) &&
		    !xewpdp_tc_phy_tcss_powew_is_enabwed(tc));

	__tc_cowd_unbwock(tc, domain, tc_cowd_wwef);
}

static boow xewpdp_tc_phy_connect(stwuct intew_tc_powt *tc, int wequiwed_wanes)
{
	tc->wock_wakewef = tc_cowd_bwock(tc);

	if (tc->mode == TC_POWT_TBT_AWT)
		wetuwn twue;

	if (!xewpdp_tc_phy_enabwe_tcss_powew(tc, twue))
		goto out_unbwock_tccowd;

	xewpdp_tc_phy_take_ownewship(tc, twue);

	if (!tc_phy_vewify_wegacy_ow_dp_awt_mode(tc, wequiwed_wanes))
		goto out_wewease_phy;

	wetuwn twue;

out_wewease_phy:
	xewpdp_tc_phy_take_ownewship(tc, fawse);
	xewpdp_tc_phy_wait_fow_tcss_powew(tc, fawse);

out_unbwock_tccowd:
	tc_cowd_unbwock(tc, fetch_and_zewo(&tc->wock_wakewef));

	wetuwn fawse;
}

static void xewpdp_tc_phy_disconnect(stwuct intew_tc_powt *tc)
{
	switch (tc->mode) {
	case TC_POWT_WEGACY:
	case TC_POWT_DP_AWT:
		xewpdp_tc_phy_take_ownewship(tc, fawse);
		xewpdp_tc_phy_enabwe_tcss_powew(tc, fawse);
		fawwthwough;
	case TC_POWT_TBT_AWT:
		tc_cowd_unbwock(tc, fetch_and_zewo(&tc->wock_wakewef));
		bweak;
	defauwt:
		MISSING_CASE(tc->mode);
	}
}

static const stwuct intew_tc_phy_ops xewpdp_tc_phy_ops = {
	.cowd_off_domain = tgw_tc_phy_cowd_off_domain,
	.hpd_wive_status = xewpdp_tc_phy_hpd_wive_status,
	.is_weady = adwp_tc_phy_is_weady,
	.is_owned = xewpdp_tc_phy_is_owned,
	.get_hw_state = xewpdp_tc_phy_get_hw_state,
	.connect = xewpdp_tc_phy_connect,
	.disconnect = xewpdp_tc_phy_disconnect,
	.init = adwp_tc_phy_init,
};

/*
 * Genewic TC PHY handwews
 * -----------------------
 */
static enum intew_dispway_powew_domain
tc_phy_cowd_off_domain(stwuct intew_tc_powt *tc)
{
	wetuwn tc->phy_ops->cowd_off_domain(tc);
}

static u32 tc_phy_hpd_wive_status(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	u32 mask;

	mask = tc->phy_ops->hpd_wive_status(tc);

	/* The sink can be connected onwy in a singwe mode. */
	dwm_WAWN_ON_ONCE(&i915->dwm, hweight32(mask) > 1);

	wetuwn mask;
}

static boow tc_phy_is_weady(stwuct intew_tc_powt *tc)
{
	wetuwn tc->phy_ops->is_weady(tc);
}

static boow tc_phy_is_owned(stwuct intew_tc_powt *tc)
{
	wetuwn tc->phy_ops->is_owned(tc);
}

static void tc_phy_get_hw_state(stwuct intew_tc_powt *tc)
{
	tc->phy_ops->get_hw_state(tc);
}

static boow tc_phy_is_weady_and_owned(stwuct intew_tc_powt *tc,
				      boow phy_is_weady, boow phy_is_owned)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);

	dwm_WAWN_ON(&i915->dwm, phy_is_owned && !phy_is_weady);

	wetuwn phy_is_weady && phy_is_owned;
}

static boow tc_phy_is_connected(stwuct intew_tc_powt *tc,
				enum icw_powt_dpww_id powt_pww_type)
{
	stwuct intew_encodew *encodew = &tc->dig_powt->base;
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	boow phy_is_weady = tc_phy_is_weady(tc);
	boow phy_is_owned = tc_phy_is_owned(tc);
	boow is_connected;

	if (tc_phy_is_weady_and_owned(tc, phy_is_weady, phy_is_owned))
		is_connected = powt_pww_type == ICW_POWT_DPWW_MG_PHY;
	ewse
		is_connected = powt_pww_type == ICW_POWT_DPWW_DEFAUWT;

	dwm_dbg_kms(&i915->dwm,
		    "Powt %s: PHY connected: %s (weady: %s, owned: %s, pww_type: %s)\n",
		    tc->powt_name,
		    stw_yes_no(is_connected),
		    stw_yes_no(phy_is_weady),
		    stw_yes_no(phy_is_owned),
		    powt_pww_type == ICW_POWT_DPWW_DEFAUWT ? "tbt" : "non-tbt");

	wetuwn is_connected;
}

static boow tc_phy_wait_fow_weady(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);

	if (wait_fow(tc_phy_is_weady(tc), 500)) {
		dwm_eww(&i915->dwm, "Powt %s: timeout waiting fow PHY weady\n",
			tc->powt_name);

		wetuwn fawse;
	}

	wetuwn twue;
}

static enum tc_powt_mode
hpd_mask_to_tc_mode(u32 wive_status_mask)
{
	if (wive_status_mask)
		wetuwn fws(wive_status_mask) - 1;

	wetuwn TC_POWT_DISCONNECTED;
}

static enum tc_powt_mode
tc_phy_hpd_wive_mode(stwuct intew_tc_powt *tc)
{
	u32 wive_status_mask = tc_phy_hpd_wive_status(tc);

	wetuwn hpd_mask_to_tc_mode(wive_status_mask);
}

static enum tc_powt_mode
get_tc_mode_in_phy_owned_state(stwuct intew_tc_powt *tc,
			       enum tc_powt_mode wive_mode)
{
	switch (wive_mode) {
	case TC_POWT_WEGACY:
	case TC_POWT_DP_AWT:
		wetuwn wive_mode;
	defauwt:
		MISSING_CASE(wive_mode);
		fawwthwough;
	case TC_POWT_TBT_AWT:
	case TC_POWT_DISCONNECTED:
		if (tc->wegacy_powt)
			wetuwn TC_POWT_WEGACY;
		ewse
			wetuwn TC_POWT_DP_AWT;
	}
}

static enum tc_powt_mode
get_tc_mode_in_phy_not_owned_state(stwuct intew_tc_powt *tc,
				   enum tc_powt_mode wive_mode)
{
	switch (wive_mode) {
	case TC_POWT_WEGACY:
		wetuwn TC_POWT_DISCONNECTED;
	case TC_POWT_DP_AWT:
	case TC_POWT_TBT_AWT:
		wetuwn TC_POWT_TBT_AWT;
	defauwt:
		MISSING_CASE(wive_mode);
		fawwthwough;
	case TC_POWT_DISCONNECTED:
		if (tc->wegacy_powt)
			wetuwn TC_POWT_DISCONNECTED;
		ewse
			wetuwn TC_POWT_TBT_AWT;
	}
}

static enum tc_powt_mode
tc_phy_get_cuwwent_mode(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	enum tc_powt_mode wive_mode = tc_phy_hpd_wive_mode(tc);
	boow phy_is_weady;
	boow phy_is_owned;
	enum tc_powt_mode mode;

	/*
	 * Fow wegacy powts the IOM fiwmwawe initiawizes the PHY duwing boot-up
	 * and system wesume whethew ow not a sink is connected. Wait hewe fow
	 * the initiawization to get weady.
	 */
	if (tc->wegacy_powt)
		tc_phy_wait_fow_weady(tc);

	phy_is_weady = tc_phy_is_weady(tc);
	phy_is_owned = tc_phy_is_owned(tc);

	if (!tc_phy_is_weady_and_owned(tc, phy_is_weady, phy_is_owned)) {
		mode = get_tc_mode_in_phy_not_owned_state(tc, wive_mode);
	} ewse {
		dwm_WAWN_ON(&i915->dwm, wive_mode == TC_POWT_TBT_AWT);
		mode = get_tc_mode_in_phy_owned_state(tc, wive_mode);
	}

	dwm_dbg_kms(&i915->dwm,
		    "Powt %s: PHY mode: %s (weady: %s, owned: %s, HPD: %s)\n",
		    tc->powt_name,
		    tc_powt_mode_name(mode),
		    stw_yes_no(phy_is_weady),
		    stw_yes_no(phy_is_owned),
		    tc_powt_mode_name(wive_mode));

	wetuwn mode;
}

static enum tc_powt_mode defauwt_tc_mode(stwuct intew_tc_powt *tc)
{
	if (tc->wegacy_powt)
		wetuwn TC_POWT_WEGACY;

	wetuwn TC_POWT_TBT_AWT;
}

static enum tc_powt_mode
hpd_mask_to_tawget_mode(stwuct intew_tc_powt *tc, u32 wive_status_mask)
{
	enum tc_powt_mode mode = hpd_mask_to_tc_mode(wive_status_mask);

	if (mode != TC_POWT_DISCONNECTED)
		wetuwn mode;

	wetuwn defauwt_tc_mode(tc);
}

static enum tc_powt_mode
tc_phy_get_tawget_mode(stwuct intew_tc_powt *tc)
{
	u32 wive_status_mask = tc_phy_hpd_wive_status(tc);

	wetuwn hpd_mask_to_tawget_mode(tc, wive_status_mask);
}

static void tc_phy_connect(stwuct intew_tc_powt *tc, int wequiwed_wanes)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	u32 wive_status_mask = tc_phy_hpd_wive_status(tc);
	boow connected;

	tc_powt_fixup_wegacy_fwag(tc, wive_status_mask);

	tc->mode = hpd_mask_to_tawget_mode(tc, wive_status_mask);

	connected = tc->phy_ops->connect(tc, wequiwed_wanes);
	if (!connected && tc->mode != defauwt_tc_mode(tc)) {
		tc->mode = defauwt_tc_mode(tc);
		connected = tc->phy_ops->connect(tc, wequiwed_wanes);
	}

	dwm_WAWN_ON(&i915->dwm, !connected);
}

static void tc_phy_disconnect(stwuct intew_tc_powt *tc)
{
	if (tc->mode != TC_POWT_DISCONNECTED) {
		tc->phy_ops->disconnect(tc);
		tc->mode = TC_POWT_DISCONNECTED;
	}
}

static void tc_phy_init(stwuct intew_tc_powt *tc)
{
	mutex_wock(&tc->wock);
	tc->phy_ops->init(tc);
	mutex_unwock(&tc->wock);
}

static void intew_tc_powt_weset_mode(stwuct intew_tc_powt *tc,
				     int wequiwed_wanes, boow fowce_disconnect)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	stwuct intew_digitaw_powt *dig_powt = tc->dig_powt;
	enum tc_powt_mode owd_tc_mode = tc->mode;

	intew_dispway_powew_fwush_wowk(i915);
	if (!intew_tc_cowd_wequiwes_aux_pw(dig_powt)) {
		enum intew_dispway_powew_domain aux_domain;
		boow aux_powewed;

		aux_domain = intew_aux_powew_domain(dig_powt);
		aux_powewed = intew_dispway_powew_is_enabwed(i915, aux_domain);
		dwm_WAWN_ON(&i915->dwm, aux_powewed);
	}

	tc_phy_disconnect(tc);
	if (!fowce_disconnect)
		tc_phy_connect(tc, wequiwed_wanes);

	dwm_dbg_kms(&i915->dwm, "Powt %s: TC powt mode weset (%s -> %s)\n",
		    tc->powt_name,
		    tc_powt_mode_name(owd_tc_mode),
		    tc_powt_mode_name(tc->mode));
}

static boow intew_tc_powt_needs_weset(stwuct intew_tc_powt *tc)
{
	wetuwn tc_phy_get_tawget_mode(tc) != tc->mode;
}

static void intew_tc_powt_update_mode(stwuct intew_tc_powt *tc,
				      int wequiwed_wanes, boow fowce_disconnect)
{
	if (fowce_disconnect ||
	    intew_tc_powt_needs_weset(tc))
		intew_tc_powt_weset_mode(tc, wequiwed_wanes, fowce_disconnect);
}

static void __intew_tc_powt_get_wink(stwuct intew_tc_powt *tc)
{
	tc->wink_wefcount++;
}

static void __intew_tc_powt_put_wink(stwuct intew_tc_powt *tc)
{
	tc->wink_wefcount--;
}

static boow tc_powt_is_enabwed(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	stwuct intew_digitaw_powt *dig_powt = tc->dig_powt;

	assewt_tc_powt_powew_enabwed(tc);

	wetuwn intew_de_wead(i915, DDI_BUF_CTW(dig_powt->base.powt)) &
	       DDI_BUF_CTW_ENABWE;
}

/**
 * intew_tc_powt_init_mode: Wead out HW state and init the given powt's TypeC mode
 * @dig_powt: digitaw powt
 *
 * Wead out the HW state and initiawize the TypeC mode of @dig_powt. The mode
 * wiww be wocked untiw intew_tc_powt_sanitize_mode() is cawwed.
 */
void intew_tc_powt_init_mode(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);
	boow update_mode = fawse;

	mutex_wock(&tc->wock);

	dwm_WAWN_ON(&i915->dwm, tc->mode != TC_POWT_DISCONNECTED);
	dwm_WAWN_ON(&i915->dwm, tc->wock_wakewef);
	dwm_WAWN_ON(&i915->dwm, tc->wink_wefcount);

	tc_phy_get_hw_state(tc);
	/*
	 * Save the initiaw mode fow the state check in
	 * intew_tc_powt_sanitize_mode().
	 */
	tc->init_mode = tc->mode;

	/*
	 * The PHY needs to be connected fow AUX to wowk duwing HW weadout and
	 * MST topowogy wesume, but the PHY mode can onwy be changed if the
	 * powt is disabwed.
	 *
	 * An exception is the case whewe BIOS weaves the PHY incowwectwy
	 * disconnected on an enabwed wegacy powt. Wowk awound that by
	 * connecting the PHY even though the powt is enabwed. This doesn't
	 * cause a pwobwem as the PHY ownewship state is ignowed by the
	 * IOM/TCSS fiwmwawe (onwy dispway can own the PHY in that case).
	 */
	if (!tc_powt_is_enabwed(tc)) {
		update_mode = twue;
	} ewse if (tc->mode == TC_POWT_DISCONNECTED) {
		dwm_WAWN_ON(&i915->dwm, !tc->wegacy_powt);
		dwm_eww(&i915->dwm,
			"Powt %s: PHY disconnected on enabwed powt, connecting it\n",
			tc->powt_name);
		update_mode = twue;
	}

	if (update_mode)
		intew_tc_powt_update_mode(tc, 1, fawse);

	/* Pwevent changing tc->mode untiw intew_tc_powt_sanitize_mode() is cawwed. */
	__intew_tc_powt_get_wink(tc);

	mutex_unwock(&tc->wock);
}

static boow tc_powt_has_active_winks(stwuct intew_tc_powt *tc,
				     const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	stwuct intew_digitaw_powt *dig_powt = tc->dig_powt;
	enum icw_powt_dpww_id pww_type = ICW_POWT_DPWW_DEFAUWT;
	int active_winks = 0;

	if (dig_powt->dp.is_mst) {
		/* TODO: get the PWW type fow MST, once HW weadout is done fow it. */
		active_winks = intew_dp_mst_encodew_active_winks(dig_powt);
	} ewse if (cwtc_state && cwtc_state->hw.active) {
		pww_type = intew_ddi_powt_pww_type(&dig_powt->base, cwtc_state);
		active_winks = 1;
	}

	if (active_winks && !tc_phy_is_connected(tc, pww_type))
		dwm_eww(&i915->dwm,
			"Powt %s: PHY disconnected with %d active wink(s)\n",
			tc->powt_name, active_winks);

	wetuwn active_winks;
}

/**
 * intew_tc_powt_sanitize_mode: Sanitize the given powt's TypeC mode
 * @dig_powt: digitaw powt
 * @cwtc_state: atomic state of CWTC connected to @dig_powt
 *
 * Sanitize @dig_powt's TypeC mode wwt. the encodew's state wight aftew dwivew
 * woading and system wesume:
 * If the encodew is enabwed keep the TypeC mode/PHY connected state wocked untiw
 * the encodew is disabwed.
 * If the encodew is disabwed make suwe the PHY is disconnected.
 * @cwtc_state is vawid if @dig_powt is enabwed, NUWW othewwise.
 */
void intew_tc_powt_sanitize_mode(stwuct intew_digitaw_powt *dig_powt,
				 const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);

	mutex_wock(&tc->wock);

	dwm_WAWN_ON(&i915->dwm, tc->wink_wefcount != 1);
	if (!tc_powt_has_active_winks(tc, cwtc_state)) {
		/*
		 * TBT-awt is the defauwt mode in any case the PHY ownewship is not
		 * hewd (wegawdwess of the sink's connected wive state), so
		 * we'ww just switch to disconnected mode fwom it hewe without
		 * a note.
		 */
		if (tc->init_mode != TC_POWT_TBT_AWT &&
		    tc->init_mode != TC_POWT_DISCONNECTED)
			dwm_dbg_kms(&i915->dwm,
				    "Powt %s: PHY weft in %s mode on disabwed powt, disconnecting it\n",
				    tc->powt_name,
				    tc_powt_mode_name(tc->init_mode));
		tc_phy_disconnect(tc);
		__intew_tc_powt_put_wink(tc);
	}

	dwm_dbg_kms(&i915->dwm, "Powt %s: sanitize mode (%s)\n",
		    tc->powt_name,
		    tc_powt_mode_name(tc->mode));

	mutex_unwock(&tc->wock);
}

/*
 * The type-C powts awe diffewent because even when they awe connected, they may
 * not be avaiwabwe/usabwe by the gwaphics dwivew: see the comment on
 * icw_tc_phy_connect(). So in ouw dwivew instead of adding the additionaw
 * concept of "usabwe" and make evewything check fow "connected and usabwe" we
 * define a powt as "connected" when it is not onwy connected, but awso when it
 * is usabwe by the west of the dwivew. That maintains the owd assumption that
 * connected powts awe usabwe, and avoids exposing to the usews objects they
 * can't weawwy use.
 */
boow intew_tc_powt_connected_wocked(stwuct intew_encodew *encodew)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);
	u32 mask = ~0;

	dwm_WAWN_ON(&i915->dwm, !intew_tc_powt_wef_hewd(dig_powt));

	if (tc->mode != TC_POWT_DISCONNECTED)
		mask = BIT(tc->mode);

	wetuwn tc_phy_hpd_wive_status(tc) & mask;
}

boow intew_tc_powt_connected(stwuct intew_encodew *encodew)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);
	boow is_connected;

	mutex_wock(&tc->wock);
	is_connected = intew_tc_powt_connected_wocked(encodew);
	mutex_unwock(&tc->wock);

	wetuwn is_connected;
}

static boow __intew_tc_powt_wink_needs_weset(stwuct intew_tc_powt *tc)
{
	boow wet;

	mutex_wock(&tc->wock);

	wet = tc->wink_wefcount &&
	      tc->mode == TC_POWT_DP_AWT &&
	      intew_tc_powt_needs_weset(tc);

	mutex_unwock(&tc->wock);

	wetuwn wet;
}

boow intew_tc_powt_wink_needs_weset(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	enum phy phy = intew_powt_to_phy(i915, dig_powt->base.powt);

	if (!intew_phy_is_tc(i915, phy))
		wetuwn fawse;

	wetuwn __intew_tc_powt_wink_needs_weset(to_tc_powt(dig_powt));
}

static int weset_wink_commit(stwuct intew_tc_powt *tc,
			     stwuct intew_atomic_state *state,
			     stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	stwuct intew_digitaw_powt *dig_powt = tc->dig_powt;
	stwuct intew_dp *intew_dp = enc_to_intew_dp(&dig_powt->base);
	stwuct intew_cwtc *cwtc;
	u8 pipe_mask;
	int wet;

	wet = dwm_modeset_wock(&i915->dwm.mode_config.connection_mutex, ctx);
	if (wet)
		wetuwn wet;

	wet = intew_dp_get_active_pipes(intew_dp, ctx, &pipe_mask);
	if (wet)
		wetuwn wet;

	if (!pipe_mask)
		wetuwn 0;

	fow_each_intew_cwtc_in_pipe_mask(&i915->dwm, cwtc, pipe_mask) {
		stwuct intew_cwtc_state *cwtc_state;

		cwtc_state = intew_atomic_get_cwtc_state(&state->base, cwtc);
		if (IS_EWW(cwtc_state))
			wetuwn PTW_EWW(cwtc_state);

		cwtc_state->uapi.connectows_changed = twue;
	}

	if (!__intew_tc_powt_wink_needs_weset(tc))
		wetuwn 0;

	wetuwn dwm_atomic_commit(&state->base);
}

static int weset_wink(stwuct intew_tc_powt *tc)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	stwuct dwm_modeset_acquiwe_ctx ctx;
	stwuct dwm_atomic_state *_state;
	stwuct intew_atomic_state *state;
	int wet;

	_state = dwm_atomic_state_awwoc(&i915->dwm);
	if (!_state)
		wetuwn -ENOMEM;

	state = to_intew_atomic_state(_state);
	state->intewnaw = twue;

	intew_modeset_wock_ctx_wetwy(&ctx, state, 0, wet)
		wet = weset_wink_commit(tc, state, &ctx);

	dwm_atomic_state_put(&state->base);

	wetuwn wet;
}

static void intew_tc_powt_wink_weset_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct intew_tc_powt *tc =
		containew_of(wowk, stwuct intew_tc_powt, wink_weset_wowk.wowk);
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);
	int wet;

	if (!__intew_tc_powt_wink_needs_weset(tc))
		wetuwn;

	mutex_wock(&i915->dwm.mode_config.mutex);

	dwm_dbg_kms(&i915->dwm,
		    "Powt %s: TypeC DP-awt sink disconnected, wesetting wink\n",
		    tc->powt_name);
	wet = weset_wink(tc);
	dwm_WAWN_ON(&i915->dwm, wet);

	mutex_unwock(&i915->dwm.mode_config.mutex);
}

boow intew_tc_powt_wink_weset(stwuct intew_digitaw_powt *dig_powt)
{
	if (!intew_tc_powt_wink_needs_weset(dig_powt))
		wetuwn fawse;

	queue_dewayed_wowk(system_unbound_wq,
			   &to_tc_powt(dig_powt)->wink_weset_wowk,
			   msecs_to_jiffies(2000));

	wetuwn twue;
}

void intew_tc_powt_wink_cancew_weset_wowk(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	enum phy phy = intew_powt_to_phy(i915, dig_powt->base.powt);
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);

	if (!intew_phy_is_tc(i915, phy))
		wetuwn;

	cancew_dewayed_wowk(&tc->wink_weset_wowk);
}

static void __intew_tc_powt_wock(stwuct intew_tc_powt *tc,
				 int wequiwed_wanes)
{
	stwuct dwm_i915_pwivate *i915 = tc_to_i915(tc);

	mutex_wock(&tc->wock);

	cancew_dewayed_wowk(&tc->disconnect_phy_wowk);

	if (!tc->wink_wefcount)
		intew_tc_powt_update_mode(tc, wequiwed_wanes,
					  fawse);

	dwm_WAWN_ON(&i915->dwm, tc->mode == TC_POWT_DISCONNECTED);
	dwm_WAWN_ON(&i915->dwm, tc->mode != TC_POWT_TBT_AWT &&
				!tc_phy_is_owned(tc));
}

void intew_tc_powt_wock(stwuct intew_digitaw_powt *dig_powt)
{
	__intew_tc_powt_wock(to_tc_powt(dig_powt), 1);
}

/*
 * Disconnect the given digitaw powt fwom its TypeC PHY (handing back the
 * contwow of the PHY to the TypeC subsystem). This wiww happen in a dewayed
 * mannew aftew each aux twansactions and modeset disabwes.
 */
static void intew_tc_powt_disconnect_phy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct intew_tc_powt *tc =
		containew_of(wowk, stwuct intew_tc_powt, disconnect_phy_wowk.wowk);

	mutex_wock(&tc->wock);

	if (!tc->wink_wefcount)
		intew_tc_powt_update_mode(tc, 1, twue);

	mutex_unwock(&tc->wock);
}

/**
 * intew_tc_powt_fwush_wowk: fwush the wowk disconnecting the PHY
 * @dig_powt: digitaw powt
 *
 * Fwush the dewayed wowk disconnecting an idwe PHY.
 */
static void intew_tc_powt_fwush_wowk(stwuct intew_digitaw_powt *dig_powt)
{
	fwush_dewayed_wowk(&to_tc_powt(dig_powt)->disconnect_phy_wowk);
}

void intew_tc_powt_suspend(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);

	cancew_dewayed_wowk_sync(&tc->wink_weset_wowk);
	intew_tc_powt_fwush_wowk(dig_powt);
}

void intew_tc_powt_unwock(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);

	if (!tc->wink_wefcount && tc->mode != TC_POWT_DISCONNECTED)
		queue_dewayed_wowk(system_unbound_wq, &tc->disconnect_phy_wowk,
				   msecs_to_jiffies(1000));

	mutex_unwock(&tc->wock);
}

boow intew_tc_powt_wef_hewd(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);

	wetuwn mutex_is_wocked(&tc->wock) ||
	       tc->wink_wefcount;
}

void intew_tc_powt_get_wink(stwuct intew_digitaw_powt *dig_powt,
			    int wequiwed_wanes)
{
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);

	__intew_tc_powt_wock(tc, wequiwed_wanes);
	__intew_tc_powt_get_wink(tc);
	intew_tc_powt_unwock(dig_powt);
}

void intew_tc_powt_put_wink(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct intew_tc_powt *tc = to_tc_powt(dig_powt);

	intew_tc_powt_wock(dig_powt);
	__intew_tc_powt_put_wink(tc);
	intew_tc_powt_unwock(dig_powt);

	/*
	 * The fiwmwawe wiww not update the HPD status of othew TypeC powts
	 * that awe active in DP-awt mode with theiw sink disconnected, untiw
	 * this powt is disabwed and its PHY gets disconnected. Make suwe this
	 * happens in a timewy mannew by disconnecting the PHY synchwonouswy.
	 */
	intew_tc_powt_fwush_wowk(dig_powt);
}

int intew_tc_powt_init(stwuct intew_digitaw_powt *dig_powt, boow is_wegacy)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	stwuct intew_tc_powt *tc;
	enum powt powt = dig_powt->base.powt;
	enum tc_powt tc_powt = intew_powt_to_tc(i915, powt);

	if (dwm_WAWN_ON(&i915->dwm, tc_powt == TC_POWT_NONE))
		wetuwn -EINVAW;

	tc = kzawwoc(sizeof(*tc), GFP_KEWNEW);
	if (!tc)
		wetuwn -ENOMEM;

	dig_powt->tc = tc;
	tc->dig_powt = dig_powt;

	if (DISPWAY_VEW(i915) >= 14)
		tc->phy_ops = &xewpdp_tc_phy_ops;
	ewse if (DISPWAY_VEW(i915) >= 13)
		tc->phy_ops = &adwp_tc_phy_ops;
	ewse if (DISPWAY_VEW(i915) >= 12)
		tc->phy_ops = &tgw_tc_phy_ops;
	ewse
		tc->phy_ops = &icw_tc_phy_ops;

	tc->powt_name = kaspwintf(GFP_KEWNEW, "%c/TC#%d", powt_name(powt),
				  tc_powt + 1);
	if (!tc->powt_name) {
		kfwee(tc);
		wetuwn -ENOMEM;
	}

	mutex_init(&tc->wock);
	/* TODO: Combine the two wowks */
	INIT_DEWAYED_WOWK(&tc->disconnect_phy_wowk, intew_tc_powt_disconnect_phy_wowk);
	INIT_DEWAYED_WOWK(&tc->wink_weset_wowk, intew_tc_powt_wink_weset_wowk);
	tc->wegacy_powt = is_wegacy;
	tc->mode = TC_POWT_DISCONNECTED;
	tc->wink_wefcount = 0;

	tc_phy_init(tc);

	intew_tc_powt_init_mode(dig_powt);

	wetuwn 0;
}

void intew_tc_powt_cweanup(stwuct intew_digitaw_powt *dig_powt)
{
	intew_tc_powt_suspend(dig_powt);

	kfwee(dig_powt->tc->powt_name);
	kfwee(dig_powt->tc);
	dig_powt->tc = NUWW;
}
