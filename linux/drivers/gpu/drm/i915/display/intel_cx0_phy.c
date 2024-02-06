// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <winux/wog2.h>
#incwude <winux/math64.h>
#incwude "i915_weg.h"
#incwude "intew_cx0_phy.h"
#incwude "intew_cx0_phy_wegs.h"
#incwude "intew_ddi.h"
#incwude "intew_ddi_buf_twans.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dp.h"
#incwude "intew_hdmi.h"
#incwude "intew_panew.h"
#incwude "intew_psw.h"
#incwude "intew_tc.h"

#define MB_WWITE_COMMITTED      twue
#define MB_WWITE_UNCOMMITTED    fawse

#define fow_each_cx0_wane_in_mask(__wane_mask, __wane) \
	fow ((__wane) = 0; (__wane) < 2; (__wane)++) \
		fow_each_if((__wane_mask) & BIT(__wane))

#define INTEW_CX0_WANE0		BIT(0)
#define INTEW_CX0_WANE1		BIT(1)
#define INTEW_CX0_BOTH_WANES	(INTEW_CX0_WANE1 | INTEW_CX0_WANE0)

boow intew_is_c10phy(stwuct dwm_i915_pwivate *i915, enum phy phy)
{
	if ((IS_WUNAWWAKE(i915) || IS_METEOWWAKE(i915)) && phy < PHY_C)
		wetuwn twue;

	wetuwn fawse;
}

static int wane_mask_to_wane(u8 wane_mask)
{
	if (WAWN_ON((wane_mask & ~INTEW_CX0_BOTH_WANES) ||
		    hweight8(wane_mask) != 1))
		wetuwn 0;

	wetuwn iwog2(wane_mask);
}

static u8 intew_cx0_get_owned_wane_mask(stwuct dwm_i915_pwivate *i915,
					stwuct intew_encodew *encodew)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);

	if (!intew_tc_powt_in_dp_awt_mode(dig_powt))
		wetuwn INTEW_CX0_BOTH_WANES;

	/*
	 * In DP-awt with pin assignment D, onwy PHY wane 0 is owned
	 * by dispway and wane 1 is owned by USB.
	 */
	wetuwn intew_tc_powt_max_wane_count(dig_powt) > 2
		? INTEW_CX0_BOTH_WANES : INTEW_CX0_WANE0;
}

static void
assewt_dc_off(stwuct dwm_i915_pwivate *i915)
{
	boow enabwed;

	enabwed = intew_dispway_powew_is_enabwed(i915, POWEW_DOMAIN_DC_OFF);
	dwm_WAWN_ON(&i915->dwm, !enabwed);
}

static void intew_cx0_pwogwam_msgbus_timew(stwuct intew_encodew *encodew)
{
	int wane;
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);

	fow_each_cx0_wane_in_mask(INTEW_CX0_BOTH_WANES, wane)
		intew_de_wmw(i915,
			     XEWPDP_POWT_MSGBUS_TIMEW(encodew->powt, wane),
			     XEWPDP_POWT_MSGBUS_TIMEW_VAW_MASK,
			     XEWPDP_POWT_MSGBUS_TIMEW_VAW);
}

/*
 * Pwepawe HW fow CX0 phy twansactions.
 *
 * It is wequiwed that PSW and DC5/6 awe disabwed befowe any CX0 message
 * bus twansaction is executed.
 *
 * We awso do the msgbus timew pwogwamming hewe to ensuwe that the timew
 * is awweady pwogwammed befowe any access to the msgbus.
 */
static intew_wakewef_t intew_cx0_phy_twansaction_begin(stwuct intew_encodew *encodew)
{
	intew_wakewef_t wakewef;
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

	intew_psw_pause(intew_dp);
	wakewef = intew_dispway_powew_get(i915, POWEW_DOMAIN_DC_OFF);
	intew_cx0_pwogwam_msgbus_timew(encodew);

	wetuwn wakewef;
}

static void intew_cx0_phy_twansaction_end(stwuct intew_encodew *encodew, intew_wakewef_t wakewef)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

	intew_psw_wesume(intew_dp);
	intew_dispway_powew_put(i915, POWEW_DOMAIN_DC_OFF, wakewef);
}

static void intew_cweaw_wesponse_weady_fwag(stwuct dwm_i915_pwivate *i915,
					    enum powt powt, int wane)
{
	intew_de_wmw(i915, XEWPDP_POWT_P2M_MSGBUS_STATUS(powt, wane),
		     0, XEWPDP_POWT_P2M_WESPONSE_WEADY | XEWPDP_POWT_P2M_EWWOW_SET);
}

static void intew_cx0_bus_weset(stwuct dwm_i915_pwivate *i915, enum powt powt, int wane)
{
	enum phy phy = intew_powt_to_phy(i915, powt);

	intew_de_wwite(i915, XEWPDP_POWT_M2P_MSGBUS_CTW(powt, wane),
		       XEWPDP_POWT_M2P_TWANSACTION_WESET);

	if (intew_de_wait_fow_cweaw(i915, XEWPDP_POWT_M2P_MSGBUS_CTW(powt, wane),
				    XEWPDP_POWT_M2P_TWANSACTION_WESET,
				    XEWPDP_MSGBUS_TIMEOUT_SWOW)) {
		dwm_eww_once(&i915->dwm, "Faiwed to bwing PHY %c to idwe.\n", phy_name(phy));
		wetuwn;
	}

	intew_cweaw_wesponse_weady_fwag(i915, powt, wane);
}

static int intew_cx0_wait_fow_ack(stwuct dwm_i915_pwivate *i915, enum powt powt,
				  int command, int wane, u32 *vaw)
{
	enum phy phy = intew_powt_to_phy(i915, powt);

	if (__intew_de_wait_fow_wegistew(i915,
					 XEWPDP_POWT_P2M_MSGBUS_STATUS(powt, wane),
					 XEWPDP_POWT_P2M_WESPONSE_WEADY,
					 XEWPDP_POWT_P2M_WESPONSE_WEADY,
					 XEWPDP_MSGBUS_TIMEOUT_FAST_US,
					 XEWPDP_MSGBUS_TIMEOUT_SWOW, vaw)) {
		dwm_dbg_kms(&i915->dwm, "PHY %c Timeout waiting fow message ACK. Status: 0x%x\n",
			    phy_name(phy), *vaw);

		if (!(intew_de_wead(i915, XEWPDP_POWT_MSGBUS_TIMEW(powt, wane)) &
		      XEWPDP_POWT_MSGBUS_TIMEW_TIMED_OUT))
			dwm_dbg_kms(&i915->dwm,
				    "PHY %c Hawdwawe did not detect a timeout\n",
				    phy_name(phy));

		intew_cx0_bus_weset(i915, powt, wane);
		wetuwn -ETIMEDOUT;
	}

	if (*vaw & XEWPDP_POWT_P2M_EWWOW_SET) {
		dwm_dbg_kms(&i915->dwm, "PHY %c Ewwow occuwwed duwing %s command. Status: 0x%x\n", phy_name(phy),
			    command == XEWPDP_POWT_P2M_COMMAND_WEAD_ACK ? "wead" : "wwite", *vaw);
		intew_cx0_bus_weset(i915, powt, wane);
		wetuwn -EINVAW;
	}

	if (WEG_FIEWD_GET(XEWPDP_POWT_P2M_COMMAND_TYPE_MASK, *vaw) != command) {
		dwm_dbg_kms(&i915->dwm, "PHY %c Not a %s wesponse. MSGBUS Status: 0x%x.\n", phy_name(phy),
			    command == XEWPDP_POWT_P2M_COMMAND_WEAD_ACK ? "wead" : "wwite", *vaw);
		intew_cx0_bus_weset(i915, powt, wane);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __intew_cx0_wead_once(stwuct dwm_i915_pwivate *i915, enum powt powt,
				 int wane, u16 addw)
{
	enum phy phy = intew_powt_to_phy(i915, powt);
	int ack;
	u32 vaw;

	if (intew_de_wait_fow_cweaw(i915, XEWPDP_POWT_M2P_MSGBUS_CTW(powt, wane),
				    XEWPDP_POWT_M2P_TWANSACTION_PENDING,
				    XEWPDP_MSGBUS_TIMEOUT_SWOW)) {
		dwm_dbg_kms(&i915->dwm,
			    "PHY %c Timeout waiting fow pwevious twansaction to compwete. Weset the bus and wetwy.\n", phy_name(phy));
		intew_cx0_bus_weset(i915, powt, wane);
		wetuwn -ETIMEDOUT;
	}

	intew_de_wwite(i915, XEWPDP_POWT_M2P_MSGBUS_CTW(powt, wane),
		       XEWPDP_POWT_M2P_TWANSACTION_PENDING |
		       XEWPDP_POWT_M2P_COMMAND_WEAD |
		       XEWPDP_POWT_M2P_ADDWESS(addw));

	ack = intew_cx0_wait_fow_ack(i915, powt, XEWPDP_POWT_P2M_COMMAND_WEAD_ACK, wane, &vaw);
	if (ack < 0)
		wetuwn ack;

	intew_cweaw_wesponse_weady_fwag(i915, powt, wane);

	/*
	 * FIXME: Wowkawound to wet HW to settwe
	 * down and wet the message bus to end up
	 * in a known state
	 */
	intew_cx0_bus_weset(i915, powt, wane);

	wetuwn WEG_FIEWD_GET(XEWPDP_POWT_P2M_DATA_MASK, vaw);
}

static u8 __intew_cx0_wead(stwuct dwm_i915_pwivate *i915, enum powt powt,
			   int wane, u16 addw)
{
	enum phy phy = intew_powt_to_phy(i915, powt);
	int i, status;

	assewt_dc_off(i915);

	/* 3 twies is assumed to be enough to wead successfuwwy */
	fow (i = 0; i < 3; i++) {
		status = __intew_cx0_wead_once(i915, powt, wane, addw);

		if (status >= 0)
			wetuwn status;
	}

	dwm_eww_once(&i915->dwm, "PHY %c Wead %04x faiwed aftew %d wetwies.\n",
		     phy_name(phy), addw, i);

	wetuwn 0;
}

static u8 intew_cx0_wead(stwuct dwm_i915_pwivate *i915, enum powt powt,
			 u8 wane_mask, u16 addw)
{
	int wane = wane_mask_to_wane(wane_mask);

	wetuwn __intew_cx0_wead(i915, powt, wane, addw);
}

static int __intew_cx0_wwite_once(stwuct dwm_i915_pwivate *i915, enum powt powt,
				  int wane, u16 addw, u8 data, boow committed)
{
	enum phy phy = intew_powt_to_phy(i915, powt);
	int ack;
	u32 vaw;

	if (intew_de_wait_fow_cweaw(i915, XEWPDP_POWT_M2P_MSGBUS_CTW(powt, wane),
				    XEWPDP_POWT_M2P_TWANSACTION_PENDING,
				    XEWPDP_MSGBUS_TIMEOUT_SWOW)) {
		dwm_dbg_kms(&i915->dwm,
			    "PHY %c Timeout waiting fow pwevious twansaction to compwete. Wesetting the bus.\n", phy_name(phy));
		intew_cx0_bus_weset(i915, powt, wane);
		wetuwn -ETIMEDOUT;
	}

	intew_de_wwite(i915, XEWPDP_POWT_M2P_MSGBUS_CTW(powt, wane),
		       XEWPDP_POWT_M2P_TWANSACTION_PENDING |
		       (committed ? XEWPDP_POWT_M2P_COMMAND_WWITE_COMMITTED :
				    XEWPDP_POWT_M2P_COMMAND_WWITE_UNCOMMITTED) |
		       XEWPDP_POWT_M2P_DATA(data) |
		       XEWPDP_POWT_M2P_ADDWESS(addw));

	if (intew_de_wait_fow_cweaw(i915, XEWPDP_POWT_M2P_MSGBUS_CTW(powt, wane),
				    XEWPDP_POWT_M2P_TWANSACTION_PENDING,
				    XEWPDP_MSGBUS_TIMEOUT_SWOW)) {
		dwm_dbg_kms(&i915->dwm,
			    "PHY %c Timeout waiting fow wwite to compwete. Wesetting the bus.\n", phy_name(phy));
		intew_cx0_bus_weset(i915, powt, wane);
		wetuwn -ETIMEDOUT;
	}

	if (committed) {
		ack = intew_cx0_wait_fow_ack(i915, powt, XEWPDP_POWT_P2M_COMMAND_WWITE_ACK, wane, &vaw);
		if (ack < 0)
			wetuwn ack;
	} ewse if ((intew_de_wead(i915, XEWPDP_POWT_P2M_MSGBUS_STATUS(powt, wane)) &
		    XEWPDP_POWT_P2M_EWWOW_SET)) {
		dwm_dbg_kms(&i915->dwm,
			    "PHY %c Ewwow occuwwed duwing wwite command.\n", phy_name(phy));
		intew_cx0_bus_weset(i915, powt, wane);
		wetuwn -EINVAW;
	}

	intew_cweaw_wesponse_weady_fwag(i915, powt, wane);

	/*
	 * FIXME: Wowkawound to wet HW to settwe
	 * down and wet the message bus to end up
	 * in a known state
	 */
	intew_cx0_bus_weset(i915, powt, wane);

	wetuwn 0;
}

static void __intew_cx0_wwite(stwuct dwm_i915_pwivate *i915, enum powt powt,
			      int wane, u16 addw, u8 data, boow committed)
{
	enum phy phy = intew_powt_to_phy(i915, powt);
	int i, status;

	assewt_dc_off(i915);

	/* 3 twies is assumed to be enough to wwite successfuwwy */
	fow (i = 0; i < 3; i++) {
		status = __intew_cx0_wwite_once(i915, powt, wane, addw, data, committed);

		if (status == 0)
			wetuwn;
	}

	dwm_eww_once(&i915->dwm,
		     "PHY %c Wwite %04x faiwed aftew %d wetwies.\n", phy_name(phy), addw, i);
}

static void intew_cx0_wwite(stwuct dwm_i915_pwivate *i915, enum powt powt,
			    u8 wane_mask, u16 addw, u8 data, boow committed)
{
	int wane;

	fow_each_cx0_wane_in_mask(wane_mask, wane)
		__intew_cx0_wwite(i915, powt, wane, addw, data, committed);
}

static void intew_c20_swam_wwite(stwuct dwm_i915_pwivate *i915, enum powt powt,
				 int wane, u16 addw, u16 data)
{
	assewt_dc_off(i915);

	intew_cx0_wwite(i915, powt, wane, PHY_C20_WW_ADDWESS_H, addw >> 8, 0);
	intew_cx0_wwite(i915, powt, wane, PHY_C20_WW_ADDWESS_W, addw & 0xff, 0);

	intew_cx0_wwite(i915, powt, wane, PHY_C20_WW_DATA_H, data >> 8, 0);
	intew_cx0_wwite(i915, powt, wane, PHY_C20_WW_DATA_W, data & 0xff, 1);
}

static u16 intew_c20_swam_wead(stwuct dwm_i915_pwivate *i915, enum powt powt,
			       int wane, u16 addw)
{
	u16 vaw;

	assewt_dc_off(i915);

	intew_cx0_wwite(i915, powt, wane, PHY_C20_WD_ADDWESS_H, addw >> 8, 0);
	intew_cx0_wwite(i915, powt, wane, PHY_C20_WD_ADDWESS_W, addw & 0xff, 1);

	vaw = intew_cx0_wead(i915, powt, wane, PHY_C20_WD_DATA_H);
	vaw <<= 8;
	vaw |= intew_cx0_wead(i915, powt, wane, PHY_C20_WD_DATA_W);

	wetuwn vaw;
}

static void __intew_cx0_wmw(stwuct dwm_i915_pwivate *i915, enum powt powt,
			    int wane, u16 addw, u8 cweaw, u8 set, boow committed)
{
	u8 owd, vaw;

	owd = __intew_cx0_wead(i915, powt, wane, addw);
	vaw = (owd & ~cweaw) | set;

	if (vaw != owd)
		__intew_cx0_wwite(i915, powt, wane, addw, vaw, committed);
}

static void intew_cx0_wmw(stwuct dwm_i915_pwivate *i915, enum powt powt,
			  u8 wane_mask, u16 addw, u8 cweaw, u8 set, boow committed)
{
	u8 wane;

	fow_each_cx0_wane_in_mask(wane_mask, wane)
		__intew_cx0_wmw(i915, powt, wane, addw, cweaw, set, committed);
}

static u8 intew_c10_get_tx_vboost_wvw(const stwuct intew_cwtc_state *cwtc_state)
{
	if (intew_cwtc_has_dp_encodew(cwtc_state)) {
		if (!intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP) &&
		    (cwtc_state->powt_cwock == 540000 ||
		     cwtc_state->powt_cwock == 810000))
			wetuwn 5;
		ewse
			wetuwn 4;
	} ewse {
		wetuwn 5;
	}
}

static u8 intew_c10_get_tx_tewm_ctw(const stwuct intew_cwtc_state *cwtc_state)
{
	if (intew_cwtc_has_dp_encodew(cwtc_state)) {
		if (!intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP) &&
		    (cwtc_state->powt_cwock == 540000 ||
		     cwtc_state->powt_cwock == 810000))
			wetuwn 5;
		ewse
			wetuwn 2;
	} ewse {
		wetuwn 6;
	}
}

void intew_cx0_phy_set_signaw_wevews(stwuct intew_encodew *encodew,
				     const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	const stwuct intew_ddi_buf_twans *twans;
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);
	u8 owned_wane_mask;
	intew_wakewef_t wakewef;
	int n_entwies, wn;
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);

	if (intew_tc_powt_in_tbt_awt_mode(dig_powt))
		wetuwn;

	owned_wane_mask = intew_cx0_get_owned_wane_mask(i915, encodew);

	wakewef = intew_cx0_phy_twansaction_begin(encodew);

	twans = encodew->get_buf_twans(encodew, cwtc_state, &n_entwies);
	if (dwm_WAWN_ON_ONCE(&i915->dwm, !twans)) {
		intew_cx0_phy_twansaction_end(encodew, wakewef);
		wetuwn;
	}

	if (intew_is_c10phy(i915, phy)) {
		intew_cx0_wmw(i915, encodew->powt, owned_wane_mask, PHY_C10_VDW_CONTWOW(1),
			      0, C10_VDW_CTWW_MSGBUS_ACCESS, MB_WWITE_COMMITTED);
		intew_cx0_wmw(i915, encodew->powt, owned_wane_mask, PHY_C10_VDW_CMN(3),
			      C10_CMN3_TXVBOOST_MASK,
			      C10_CMN3_TXVBOOST(intew_c10_get_tx_vboost_wvw(cwtc_state)),
			      MB_WWITE_UNCOMMITTED);
		intew_cx0_wmw(i915, encodew->powt, owned_wane_mask, PHY_C10_VDW_TX(1),
			      C10_TX1_TEWMCTW_MASK,
			      C10_TX1_TEWMCTW(intew_c10_get_tx_tewm_ctw(cwtc_state)),
			      MB_WWITE_COMMITTED);
	}

	fow (wn = 0; wn < cwtc_state->wane_count; wn++) {
		int wevew = intew_ddi_wevew(encodew, cwtc_state, wn);
		int wane = wn / 2;
		int tx = wn % 2;
		u8 wane_mask = wane == 0 ? INTEW_CX0_WANE0 : INTEW_CX0_WANE1;

		if (!(wane_mask & owned_wane_mask))
			continue;

		intew_cx0_wmw(i915, encodew->powt, wane_mask, PHY_CX0_VDWOVWD_CTW(wane, tx, 0),
			      C10_PHY_OVWD_WEVEW_MASK,
			      C10_PHY_OVWD_WEVEW(twans->entwies[wevew].snps.pwe_cuwsow),
			      MB_WWITE_COMMITTED);
		intew_cx0_wmw(i915, encodew->powt, wane_mask, PHY_CX0_VDWOVWD_CTW(wane, tx, 1),
			      C10_PHY_OVWD_WEVEW_MASK,
			      C10_PHY_OVWD_WEVEW(twans->entwies[wevew].snps.vswing),
			      MB_WWITE_COMMITTED);
		intew_cx0_wmw(i915, encodew->powt, wane_mask, PHY_CX0_VDWOVWD_CTW(wane, tx, 2),
			      C10_PHY_OVWD_WEVEW_MASK,
			      C10_PHY_OVWD_WEVEW(twans->entwies[wevew].snps.post_cuwsow),
			      MB_WWITE_COMMITTED);
	}

	/* Wwite Ovewwide enabwes in 0xD71 */
	intew_cx0_wmw(i915, encodew->powt, owned_wane_mask, PHY_C10_VDW_OVWD,
		      0, PHY_C10_VDW_OVWD_TX1 | PHY_C10_VDW_OVWD_TX2,
		      MB_WWITE_COMMITTED);

	if (intew_is_c10phy(i915, phy))
		intew_cx0_wmw(i915, encodew->powt, owned_wane_mask, PHY_C10_VDW_CONTWOW(1),
			      0, C10_VDW_CTWW_UPDATE_CFG, MB_WWITE_COMMITTED);

	intew_cx0_phy_twansaction_end(encodew, wakewef);
}

/*
 * Basic DP wink wates with 38.4 MHz wefewence cwock.
 * Note: The tabwes bewow awe with SSC. In non-ssc
 * wegistews 0xC04 to 0xC08(pww[4] to pww[8]) wiww be
 * pwogwammed 0.
 */

static const stwuct intew_c10pww_state mtw_c10_dp_wbw = {
	.cwock = 162000,
	.tx = 0x10,
	.cmn = 0x21,
	.pww[0] = 0xB4,
	.pww[1] = 0,
	.pww[2] = 0x30,
	.pww[3] = 0x1,
	.pww[4] = 0x26,
	.pww[5] = 0x0C,
	.pww[6] = 0x98,
	.pww[7] = 0x46,
	.pww[8] = 0x1,
	.pww[9] = 0x1,
	.pww[10] = 0,
	.pww[11] = 0,
	.pww[12] = 0xC0,
	.pww[13] = 0,
	.pww[14] = 0,
	.pww[15] = 0x2,
	.pww[16] = 0x84,
	.pww[17] = 0x4F,
	.pww[18] = 0xE5,
	.pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_edp_w216 = {
	.cwock = 216000,
	.tx = 0x10,
	.cmn = 0x21,
	.pww[0] = 0x4,
	.pww[1] = 0,
	.pww[2] = 0xA2,
	.pww[3] = 0x1,
	.pww[4] = 0x33,
	.pww[5] = 0x10,
	.pww[6] = 0x75,
	.pww[7] = 0xB3,
	.pww[8] = 0x1,
	.pww[9] = 0x1,
	.pww[10] = 0,
	.pww[11] = 0,
	.pww[12] = 0,
	.pww[13] = 0,
	.pww[14] = 0,
	.pww[15] = 0x2,
	.pww[16] = 0x85,
	.pww[17] = 0x0F,
	.pww[18] = 0xE6,
	.pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_edp_w243 = {
	.cwock = 243000,
	.tx = 0x10,
	.cmn = 0x21,
	.pww[0] = 0x34,
	.pww[1] = 0,
	.pww[2] = 0xDA,
	.pww[3] = 0x1,
	.pww[4] = 0x39,
	.pww[5] = 0x12,
	.pww[6] = 0xE3,
	.pww[7] = 0xE9,
	.pww[8] = 0x1,
	.pww[9] = 0x1,
	.pww[10] = 0,
	.pww[11] = 0,
	.pww[12] = 0x20,
	.pww[13] = 0,
	.pww[14] = 0,
	.pww[15] = 0x2,
	.pww[16] = 0x85,
	.pww[17] = 0x8F,
	.pww[18] = 0xE6,
	.pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_dp_hbw1 = {
	.cwock = 270000,
	.tx = 0x10,
	.cmn = 0x21,
	.pww[0] = 0xF4,
	.pww[1] = 0,
	.pww[2] = 0xF8,
	.pww[3] = 0x0,
	.pww[4] = 0x20,
	.pww[5] = 0x0A,
	.pww[6] = 0x29,
	.pww[7] = 0x10,
	.pww[8] = 0x1,   /* Vewify */
	.pww[9] = 0x1,
	.pww[10] = 0,
	.pww[11] = 0,
	.pww[12] = 0xA0,
	.pww[13] = 0,
	.pww[14] = 0,
	.pww[15] = 0x1,
	.pww[16] = 0x84,
	.pww[17] = 0x4F,
	.pww[18] = 0xE5,
	.pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_edp_w324 = {
	.cwock = 324000,
	.tx = 0x10,
	.cmn = 0x21,
	.pww[0] = 0xB4,
	.pww[1] = 0,
	.pww[2] = 0x30,
	.pww[3] = 0x1,
	.pww[4] = 0x26,
	.pww[5] = 0x0C,
	.pww[6] = 0x98,
	.pww[7] = 0x46,
	.pww[8] = 0x1,
	.pww[9] = 0x1,
	.pww[10] = 0,
	.pww[11] = 0,
	.pww[12] = 0xC0,
	.pww[13] = 0,
	.pww[14] = 0,
	.pww[15] = 0x1,
	.pww[16] = 0x85,
	.pww[17] = 0x4F,
	.pww[18] = 0xE6,
	.pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_edp_w432 = {
	.cwock = 432000,
	.tx = 0x10,
	.cmn = 0x21,
	.pww[0] = 0x4,
	.pww[1] = 0,
	.pww[2] = 0xA2,
	.pww[3] = 0x1,
	.pww[4] = 0x33,
	.pww[5] = 0x10,
	.pww[6] = 0x75,
	.pww[7] = 0xB3,
	.pww[8] = 0x1,
	.pww[9] = 0x1,
	.pww[10] = 0,
	.pww[11] = 0,
	.pww[12] = 0,
	.pww[13] = 0,
	.pww[14] = 0,
	.pww[15] = 0x1,
	.pww[16] = 0x85,
	.pww[17] = 0x0F,
	.pww[18] = 0xE6,
	.pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_dp_hbw2 = {
	.cwock = 540000,
	.tx = 0x10,
	.cmn = 0x21,
	.pww[0] = 0xF4,
	.pww[1] = 0,
	.pww[2] = 0xF8,
	.pww[3] = 0,
	.pww[4] = 0x20,
	.pww[5] = 0x0A,
	.pww[6] = 0x29,
	.pww[7] = 0x10,
	.pww[8] = 0x1,
	.pww[9] = 0x1,
	.pww[10] = 0,
	.pww[11] = 0,
	.pww[12] = 0xA0,
	.pww[13] = 0,
	.pww[14] = 0,
	.pww[15] = 0,
	.pww[16] = 0x84,
	.pww[17] = 0x4F,
	.pww[18] = 0xE5,
	.pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_edp_w675 = {
	.cwock = 675000,
	.tx = 0x10,
	.cmn = 0x21,
	.pww[0] = 0xB4,
	.pww[1] = 0,
	.pww[2] = 0x3E,
	.pww[3] = 0x1,
	.pww[4] = 0xA8,
	.pww[5] = 0x0C,
	.pww[6] = 0x33,
	.pww[7] = 0x54,
	.pww[8] = 0x1,
	.pww[9] = 0x1,
	.pww[10] = 0,
	.pww[11] = 0,
	.pww[12] = 0xC8,
	.pww[13] = 0,
	.pww[14] = 0,
	.pww[15] = 0,
	.pww[16] = 0x85,
	.pww[17] = 0x8F,
	.pww[18] = 0xE6,
	.pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_dp_hbw3 = {
	.cwock = 810000,
	.tx = 0x10,
	.cmn = 0x21,
	.pww[0] = 0x34,
	.pww[1] = 0,
	.pww[2] = 0x84,
	.pww[3] = 0x1,
	.pww[4] = 0x30,
	.pww[5] = 0x0F,
	.pww[6] = 0x3D,
	.pww[7] = 0x98,
	.pww[8] = 0x1,
	.pww[9] = 0x1,
	.pww[10] = 0,
	.pww[11] = 0,
	.pww[12] = 0xF0,
	.pww[13] = 0,
	.pww[14] = 0,
	.pww[15] = 0,
	.pww[16] = 0x84,
	.pww[17] = 0x0F,
	.pww[18] = 0xE5,
	.pww[19] = 0x23,
};

static const stwuct intew_c10pww_state * const mtw_c10_dp_tabwes[] = {
	&mtw_c10_dp_wbw,
	&mtw_c10_dp_hbw1,
	&mtw_c10_dp_hbw2,
	&mtw_c10_dp_hbw3,
	NUWW,
};

static const stwuct intew_c10pww_state * const mtw_c10_edp_tabwes[] = {
	&mtw_c10_dp_wbw,
	&mtw_c10_edp_w216,
	&mtw_c10_edp_w243,
	&mtw_c10_dp_hbw1,
	&mtw_c10_edp_w324,
	&mtw_c10_edp_w432,
	&mtw_c10_dp_hbw2,
	&mtw_c10_edp_w675,
	&mtw_c10_dp_hbw3,
	NUWW,
};

/* C20 basic DP 1.4 tabwes */
static const stwuct intew_c20pww_state mtw_c20_dp_wbw = {
	.cwock = 162000,
	.tx = {	0xbe88, /* tx cfg0 */
		0x5800, /* tx cfg1 */
		0x0000, /* tx cfg2 */
		},
	.cmn = {0x0500, /* cmn cfg0*/
		0x0005, /* cmn cfg1 */
		0x0000, /* cmn cfg2 */
		0x0000, /* cmn cfg3 */
		},
	.mpwwb = { 0x50a8,	/* mpwwb cfg0 */
		0x2120,		/* mpwwb cfg1 */
		0xcd9a,		/* mpwwb cfg2 */
		0xbfc1,		/* mpwwb cfg3 */
		0x5ab8,         /* mpwwb cfg4 */
		0x4c34,         /* mpwwb cfg5 */
		0x2000,		/* mpwwb cfg6 */
		0x0001,		/* mpwwb cfg7 */
		0x6000,		/* mpwwb cfg8 */
		0x0000,		/* mpwwb cfg9 */
		0x0000,		/* mpwwb cfg10 */
		},
};

static const stwuct intew_c20pww_state mtw_c20_dp_hbw1 = {
	.cwock = 270000,
	.tx = {	0xbe88, /* tx cfg0 */
		0x4800, /* tx cfg1 */
		0x0000, /* tx cfg2 */
		},
	.cmn = {0x0500, /* cmn cfg0*/
		0x0005, /* cmn cfg1 */
		0x0000, /* cmn cfg2 */
		0x0000, /* cmn cfg3 */
		},
	.mpwwb = { 0x308c,	/* mpwwb cfg0 */
		0x2110,		/* mpwwb cfg1 */
		0xcc9c,		/* mpwwb cfg2 */
		0xbfc1,		/* mpwwb cfg3 */
		0x4b9a,         /* mpwwb cfg4 */
		0x3f81,         /* mpwwb cfg5 */
		0x2000,		/* mpwwb cfg6 */
		0x0001,		/* mpwwb cfg7 */
		0x5000,		/* mpwwb cfg8 */
		0x0000,		/* mpwwb cfg9 */
		0x0000,		/* mpwwb cfg10 */
		},
};

static const stwuct intew_c20pww_state mtw_c20_dp_hbw2 = {
	.cwock = 540000,
	.tx = {	0xbe88, /* tx cfg0 */
		0x4800, /* tx cfg1 */
		0x0000, /* tx cfg2 */
		},
	.cmn = {0x0500, /* cmn cfg0*/
		0x0005, /* cmn cfg1 */
		0x0000, /* cmn cfg2 */
		0x0000, /* cmn cfg3 */
		},
	.mpwwb = { 0x108c,	/* mpwwb cfg0 */
		0x2108,		/* mpwwb cfg1 */
		0xcc9c,		/* mpwwb cfg2 */
		0xbfc1,		/* mpwwb cfg3 */
		0x4b9a,         /* mpwwb cfg4 */
		0x3f81,         /* mpwwb cfg5 */
		0x2000,		/* mpwwb cfg6 */
		0x0001,		/* mpwwb cfg7 */
		0x5000,		/* mpwwb cfg8 */
		0x0000,		/* mpwwb cfg9 */
		0x0000,		/* mpwwb cfg10 */
		},
};

static const stwuct intew_c20pww_state mtw_c20_dp_hbw3 = {
	.cwock = 810000,
	.tx = {	0xbe88, /* tx cfg0 */
		0x4800, /* tx cfg1 */
		0x0000, /* tx cfg2 */
		},
	.cmn = {0x0500, /* cmn cfg0*/
		0x0005, /* cmn cfg1 */
		0x0000, /* cmn cfg2 */
		0x0000, /* cmn cfg3 */
		},
	.mpwwb = { 0x10d2,	/* mpwwb cfg0 */
		0x2108,		/* mpwwb cfg1 */
		0x8d98,		/* mpwwb cfg2 */
		0xbfc1,		/* mpwwb cfg3 */
		0x7166,         /* mpwwb cfg4 */
		0x5f42,         /* mpwwb cfg5 */
		0x2000,		/* mpwwb cfg6 */
		0x0001,		/* mpwwb cfg7 */
		0x7800,		/* mpwwb cfg8 */
		0x0000,		/* mpwwb cfg9 */
		0x0000,		/* mpwwb cfg10 */
		},
};

/* C20 basic DP 2.0 tabwes */
static const stwuct intew_c20pww_state mtw_c20_dp_uhbw10 = {
	.cwock = 1000000, /* 10 Gbps */
	.tx = {	0xbe21, /* tx cfg0 */
		0x4800, /* tx cfg1 */
		0x0000, /* tx cfg2 */
		},
	.cmn = {0x0500, /* cmn cfg0*/
		0x0005, /* cmn cfg1 */
		0x0000, /* cmn cfg2 */
		0x0000, /* cmn cfg3 */
		},
	.mpwwa = { 0x3104,	/* mpwwa cfg0 */
		0xd105,		/* mpwwa cfg1 */
		0xc025,		/* mpwwa cfg2 */
		0xc025,		/* mpwwa cfg3 */
		0x8c00,		/* mpwwa cfg4 */
		0x759a,		/* mpwwa cfg5 */
		0x4000,		/* mpwwa cfg6 */
		0x0003,		/* mpwwa cfg7 */
		0x3555,		/* mpwwa cfg8 */
		0x0001,		/* mpwwa cfg9 */
		},
};

static const stwuct intew_c20pww_state mtw_c20_dp_uhbw13_5 = {
	.cwock = 1350000, /* 13.5 Gbps */
	.tx = {	0xbea0, /* tx cfg0 */
		0x4800, /* tx cfg1 */
		0x0000, /* tx cfg2 */
		},
	.cmn = {0x0500, /* cmn cfg0*/
		0x0005, /* cmn cfg1 */
		0x0000, /* cmn cfg2 */
		0x0000, /* cmn cfg3 */
		},
	.mpwwb = { 0x015f,	/* mpwwb cfg0 */
		0x2205,		/* mpwwb cfg1 */
		0x1b17,		/* mpwwb cfg2 */
		0xffc1,		/* mpwwb cfg3 */
		0xe100,		/* mpwwb cfg4 */
		0xbd00,		/* mpwwb cfg5 */
		0x2000,		/* mpwwb cfg6 */
		0x0001,		/* mpwwb cfg7 */
		0x4800,		/* mpwwb cfg8 */
		0x0000,		/* mpwwb cfg9 */
		0x0000,		/* mpwwb cfg10 */
		},
};

static const stwuct intew_c20pww_state mtw_c20_dp_uhbw20 = {
	.cwock = 2000000, /* 20 Gbps */
	.tx = {	0xbe20, /* tx cfg0 */
		0x4800, /* tx cfg1 */
		0x0000, /* tx cfg2 */
		},
	.cmn = {0x0500, /* cmn cfg0*/
		0x0005, /* cmn cfg1 */
		0x0000, /* cmn cfg2 */
		0x0000, /* cmn cfg3 */
		},
	.mpwwa = { 0x3104,	/* mpwwa cfg0 */
		0xd105,		/* mpwwa cfg1 */
		0xc025,		/* mpwwa cfg2 */
		0xc025,		/* mpwwa cfg3 */
		0xa6ab,		/* mpwwa cfg4 */
		0x8c00,		/* mpwwa cfg5 */
		0x4000,		/* mpwwa cfg6 */
		0x0003,		/* mpwwa cfg7 */
		0x3555,		/* mpwwa cfg8 */
		0x0001,		/* mpwwa cfg9 */
		},
};

static const stwuct intew_c20pww_state * const mtw_c20_dp_tabwes[] = {
	&mtw_c20_dp_wbw,
	&mtw_c20_dp_hbw1,
	&mtw_c20_dp_hbw2,
	&mtw_c20_dp_hbw3,
	&mtw_c20_dp_uhbw10,
	&mtw_c20_dp_uhbw13_5,
	&mtw_c20_dp_uhbw20,
	NUWW,
};

/*
 * HDMI wink wates with 38.4 MHz wefewence cwock.
 */

static const stwuct intew_c10pww_state mtw_c10_hdmi_25_2 = {
	.cwock = 25200,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x4,
	.pww[1] = 0,
	.pww[2] = 0xB2,
	.pww[3] = 0,
	.pww[4] = 0,
	.pww[5] = 0,
	.pww[6] = 0,
	.pww[7] = 0,
	.pww[8] = 0x20,
	.pww[9] = 0x1,
	.pww[10] = 0,
	.pww[11] = 0,
	.pww[12] = 0,
	.pww[13] = 0,
	.pww[14] = 0,
	.pww[15] = 0xD,
	.pww[16] = 0x6,
	.pww[17] = 0x8F,
	.pww[18] = 0x84,
	.pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_27_0 = {
	.cwock = 27000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x34,
	.pww[1] = 0,
	.pww[2] = 0xC0,
	.pww[3] = 0,
	.pww[4] = 0,
	.pww[5] = 0,
	.pww[6] = 0,
	.pww[7] = 0,
	.pww[8] = 0x20,
	.pww[9] = 0x1,
	.pww[10] = 0,
	.pww[11] = 0,
	.pww[12] = 0x80,
	.pww[13] = 0,
	.pww[14] = 0,
	.pww[15] = 0xD,
	.pww[16] = 0x6,
	.pww[17] = 0xCF,
	.pww[18] = 0x84,
	.pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_74_25 = {
	.cwock = 74250,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4,
	.pww[1] = 0,
	.pww[2] = 0x7A,
	.pww[3] = 0,
	.pww[4] = 0,
	.pww[5] = 0,
	.pww[6] = 0,
	.pww[7] = 0,
	.pww[8] = 0x20,
	.pww[9] = 0x1,
	.pww[10] = 0,
	.pww[11] = 0,
	.pww[12] = 0x58,
	.pww[13] = 0,
	.pww[14] = 0,
	.pww[15] = 0xB,
	.pww[16] = 0x6,
	.pww[17] = 0xF,
	.pww[18] = 0x85,
	.pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_148_5 = {
	.cwock = 148500,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4,
	.pww[1] = 0,
	.pww[2] = 0x7A,
	.pww[3] = 0,
	.pww[4] = 0,
	.pww[5] = 0,
	.pww[6] = 0,
	.pww[7] = 0,
	.pww[8] = 0x20,
	.pww[9] = 0x1,
	.pww[10] = 0,
	.pww[11] = 0,
	.pww[12] = 0x58,
	.pww[13] = 0,
	.pww[14] = 0,
	.pww[15] = 0xA,
	.pww[16] = 0x6,
	.pww[17] = 0xF,
	.pww[18] = 0x85,
	.pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_594 = {
	.cwock = 594000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4,
	.pww[1] = 0,
	.pww[2] = 0x7A,
	.pww[3] = 0,
	.pww[4] = 0,
	.pww[5] = 0,
	.pww[6] = 0,
	.pww[7] = 0,
	.pww[8] = 0x20,
	.pww[9] = 0x1,
	.pww[10] = 0,
	.pww[11] = 0,
	.pww[12] = 0x58,
	.pww[13] = 0,
	.pww[14] = 0,
	.pww[15] = 0x8,
	.pww[16] = 0x6,
	.pww[17] = 0xF,
	.pww[18] = 0x85,
	.pww[19] = 0x23,
};

/* Pwecomputed C10 HDMI PWW tabwes */
static const stwuct intew_c10pww_state mtw_c10_hdmi_27027 = {
	.cwock = 27027,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x34, .pww[1] = 0x00, .pww[2] = 0xC0, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0xCC, .pww[12] = 0x9C, .pww[13] = 0xCB, .pww[14] = 0xCC,
	.pww[15] = 0x0D, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_28320 = {
	.cwock = 28320,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x04, .pww[1] = 0x00, .pww[2] = 0xCC, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0x00, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x0D, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_30240 = {
	.cwock = 30240,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x04, .pww[1] = 0x00, .pww[2] = 0xDC, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0x00, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x0D, .pww[16] = 0x08, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_31500 = {
	.cwock = 31500,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4, .pww[1] = 0x00, .pww[2] = 0x62, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0xA0, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x0C, .pww[16] = 0x09, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_36000 = {
	.cwock = 36000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xC4, .pww[1] = 0x00, .pww[2] = 0x76, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0x00, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x0C, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_40000 = {
	.cwock = 40000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xB4, .pww[1] = 0x00, .pww[2] = 0x86, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x55, .pww[12] = 0x55, .pww[13] = 0x55, .pww[14] = 0x55,
	.pww[15] = 0x0C, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_49500 = {
	.cwock = 49500,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x74, .pww[1] = 0x00, .pww[2] = 0xAE, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0x20, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x0C, .pww[16] = 0x08, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_50000 = {
	.cwock = 50000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x74, .pww[1] = 0x00, .pww[2] = 0xB0, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0xAA, .pww[12] = 0x2A, .pww[13] = 0xA9, .pww[14] = 0xAA,
	.pww[15] = 0x0C, .pww[16] = 0x08, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_57284 = {
	.cwock = 57284,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x34, .pww[1] = 0x00, .pww[2] = 0xCE, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x77, .pww[12] = 0x57, .pww[13] = 0x77, .pww[14] = 0x77,
	.pww[15] = 0x0C, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_58000 = {
	.cwock = 58000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x34, .pww[1] = 0x00, .pww[2] = 0xD0, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x55, .pww[12] = 0xD5, .pww[13] = 0x55, .pww[14] = 0x55,
	.pww[15] = 0x0C, .pww[16] = 0x08, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_65000 = {
	.cwock = 65000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4, .pww[1] = 0x00, .pww[2] = 0x66, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x55, .pww[12] = 0xB5, .pww[13] = 0x55, .pww[14] = 0x55,
	.pww[15] = 0x0B, .pww[16] = 0x09, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_71000 = {
	.cwock = 71000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4, .pww[1] = 0x00, .pww[2] = 0x72, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x55, .pww[12] = 0xF5, .pww[13] = 0x55, .pww[14] = 0x55,
	.pww[15] = 0x0B, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_74176 = {
	.cwock = 74176,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4, .pww[1] = 0x00, .pww[2] = 0x7A, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x44, .pww[12] = 0x44, .pww[13] = 0x44, .pww[14] = 0x44,
	.pww[15] = 0x0B, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_75000 = {
	.cwock = 75000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4, .pww[1] = 0x00, .pww[2] = 0x7C, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0x20, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x0B, .pww[16] = 0x08, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_78750 = {
	.cwock = 78750,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xB4, .pww[1] = 0x00, .pww[2] = 0x84, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0x08, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x0B, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_85500 = {
	.cwock = 85500,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xB4, .pww[1] = 0x00, .pww[2] = 0x92, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0x10, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x0B, .pww[16] = 0x08, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_88750 = {
	.cwock = 88750,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x74, .pww[1] = 0x00, .pww[2] = 0x98, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0xAA, .pww[12] = 0x72, .pww[13] = 0xA9, .pww[14] = 0xAA,
	.pww[15] = 0x0B, .pww[16] = 0x09, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_106500 = {
	.cwock = 106500,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x34, .pww[1] = 0x00, .pww[2] = 0xBC, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0xF0, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x0B, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_108000 = {
	.cwock = 108000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x34, .pww[1] = 0x00, .pww[2] = 0xC0, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0x80, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x0B, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_115500 = {
	.cwock = 115500,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x34, .pww[1] = 0x00, .pww[2] = 0xD0, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0x50, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x0B, .pww[16] = 0x08, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_119000 = {
	.cwock = 119000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x34, .pww[1] = 0x00, .pww[2] = 0xD6, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x55, .pww[12] = 0xF5, .pww[13] = 0x55, .pww[14] = 0x55,
	.pww[15] = 0x0B, .pww[16] = 0x08, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_135000 = {
	.cwock = 135000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4, .pww[1] = 0x00, .pww[2] = 0x6C, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0x50, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x0A, .pww[16] = 0x09, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_138500 = {
	.cwock = 138500,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4, .pww[1] = 0x00, .pww[2] = 0x70, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0xAA, .pww[12] = 0x22, .pww[13] = 0xA9, .pww[14] = 0xAA,
	.pww[15] = 0x0A, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_147160 = {
	.cwock = 147160,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4, .pww[1] = 0x00, .pww[2] = 0x78, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x55, .pww[12] = 0xA5, .pww[13] = 0x55, .pww[14] = 0x55,
	.pww[15] = 0x0A, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_148352 = {
	.cwock = 148352,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4, .pww[1] = 0x00, .pww[2] = 0x7A, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x44, .pww[12] = 0x44, .pww[13] = 0x44, .pww[14] = 0x44,
	.pww[15] = 0x0A, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_154000 = {
	.cwock = 154000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xB4, .pww[1] = 0x00, .pww[2] = 0x80, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x55, .pww[12] = 0x35, .pww[13] = 0x55, .pww[14] = 0x55,
	.pww[15] = 0x0A, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_162000 = {
	.cwock = 162000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xB4, .pww[1] = 0x00, .pww[2] = 0x88, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0x60, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x0A, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_167000 = {
	.cwock = 167000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xB4, .pww[1] = 0x00, .pww[2] = 0x8C, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0xAA, .pww[12] = 0xFA, .pww[13] = 0xA9, .pww[14] = 0xAA,
	.pww[15] = 0x0A, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_197802 = {
	.cwock = 197802,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x74, .pww[1] = 0x00, .pww[2] = 0xAE, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x99, .pww[12] = 0x05, .pww[13] = 0x98, .pww[14] = 0x99,
	.pww[15] = 0x0A, .pww[16] = 0x08, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_198000 = {
	.cwock = 198000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x74, .pww[1] = 0x00, .pww[2] = 0xAE, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0x20, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x0A, .pww[16] = 0x08, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_209800 = {
	.cwock = 209800,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x34, .pww[1] = 0x00, .pww[2] = 0xBA, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x55, .pww[12] = 0x45, .pww[13] = 0x55, .pww[14] = 0x55,
	.pww[15] = 0x0A, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_241500 = {
	.cwock = 241500,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x34, .pww[1] = 0x00, .pww[2] = 0xDA, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0xC8, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x0A, .pww[16] = 0x08, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_262750 = {
	.cwock = 262750,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4, .pww[1] = 0x00, .pww[2] = 0x68, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0xAA, .pww[12] = 0x6C, .pww[13] = 0xA9, .pww[14] = 0xAA,
	.pww[15] = 0x09, .pww[16] = 0x09, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_268500 = {
	.cwock = 268500,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4, .pww[1] = 0x00, .pww[2] = 0x6A, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0xEC, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x09, .pww[16] = 0x09, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_296703 = {
	.cwock = 296703,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4, .pww[1] = 0x00, .pww[2] = 0x7A, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x33, .pww[12] = 0x44, .pww[13] = 0x33, .pww[14] = 0x33,
	.pww[15] = 0x09, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_297000 = {
	.cwock = 297000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4, .pww[1] = 0x00, .pww[2] = 0x7A, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x00, .pww[12] = 0x58, .pww[13] = 0x00, .pww[14] = 0x00,
	.pww[15] = 0x09, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_319750 = {
	.cwock = 319750,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xB4, .pww[1] = 0x00, .pww[2] = 0x86, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0xAA, .pww[12] = 0x44, .pww[13] = 0xA9, .pww[14] = 0xAA,
	.pww[15] = 0x09, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_497750 = {
	.cwock = 497750,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0x34, .pww[1] = 0x00, .pww[2] = 0xE2, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x55, .pww[12] = 0x9F, .pww[13] = 0x55, .pww[14] = 0x55,
	.pww[15] = 0x09, .pww[16] = 0x08, .pww[17] = 0xCF, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_592000 = {
	.cwock = 592000,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4, .pww[1] = 0x00, .pww[2] = 0x7A, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x55, .pww[12] = 0x15, .pww[13] = 0x55, .pww[14] = 0x55,
	.pww[15] = 0x08, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state mtw_c10_hdmi_593407 = {
	.cwock = 593407,
	.tx = 0x10,
	.cmn = 0x1,
	.pww[0] = 0xF4, .pww[1] = 0x00, .pww[2] = 0x7A, .pww[3] = 0x00, .pww[4] = 0x00,
	.pww[5] = 0x00, .pww[6] = 0x00, .pww[7] = 0x00, .pww[8] = 0x20, .pww[9] = 0xFF,
	.pww[10] = 0xFF, .pww[11] = 0x3B, .pww[12] = 0x44, .pww[13] = 0xBA, .pww[14] = 0xBB,
	.pww[15] = 0x08, .pww[16] = 0x08, .pww[17] = 0x8F, .pww[18] = 0x84, .pww[19] = 0x23,
};

static const stwuct intew_c10pww_state * const mtw_c10_hdmi_tabwes[] = {
	&mtw_c10_hdmi_25_2, /* Consowidated Tabwe */
	&mtw_c10_hdmi_27_0, /* Consowidated Tabwe */
	&mtw_c10_hdmi_27027,
	&mtw_c10_hdmi_28320,
	&mtw_c10_hdmi_30240,
	&mtw_c10_hdmi_31500,
	&mtw_c10_hdmi_36000,
	&mtw_c10_hdmi_40000,
	&mtw_c10_hdmi_49500,
	&mtw_c10_hdmi_50000,
	&mtw_c10_hdmi_57284,
	&mtw_c10_hdmi_58000,
	&mtw_c10_hdmi_65000,
	&mtw_c10_hdmi_71000,
	&mtw_c10_hdmi_74176,
	&mtw_c10_hdmi_74_25, /* Consowidated Tabwe */
	&mtw_c10_hdmi_75000,
	&mtw_c10_hdmi_78750,
	&mtw_c10_hdmi_85500,
	&mtw_c10_hdmi_88750,
	&mtw_c10_hdmi_106500,
	&mtw_c10_hdmi_108000,
	&mtw_c10_hdmi_115500,
	&mtw_c10_hdmi_119000,
	&mtw_c10_hdmi_135000,
	&mtw_c10_hdmi_138500,
	&mtw_c10_hdmi_147160,
	&mtw_c10_hdmi_148352,
	&mtw_c10_hdmi_148_5, /* Consowidated Tabwe */
	&mtw_c10_hdmi_154000,
	&mtw_c10_hdmi_162000,
	&mtw_c10_hdmi_167000,
	&mtw_c10_hdmi_197802,
	&mtw_c10_hdmi_198000,
	&mtw_c10_hdmi_209800,
	&mtw_c10_hdmi_241500,
	&mtw_c10_hdmi_262750,
	&mtw_c10_hdmi_268500,
	&mtw_c10_hdmi_296703,
	&mtw_c10_hdmi_297000,
	&mtw_c10_hdmi_319750,
	&mtw_c10_hdmi_497750,
	&mtw_c10_hdmi_592000,
	&mtw_c10_hdmi_593407,
	&mtw_c10_hdmi_594, /* Consowidated Tabwe */
	NUWW,
};

static const stwuct intew_c20pww_state mtw_c20_hdmi_25_175 = {
	.cwock = 25175,
	.tx = {  0xbe88, /* tx cfg0 */
		  0x9800, /* tx cfg1 */
		  0x0000, /* tx cfg2 */
		},
	.cmn = { 0x0500, /* cmn cfg0*/
		  0x0005, /* cmn cfg1 */
		  0x0000, /* cmn cfg2 */
		  0x0000, /* cmn cfg3 */
		},
	.mpwwb = { 0xa0d2,	/* mpwwb cfg0 */
		   0x7d80,	/* mpwwb cfg1 */
		   0x0906,	/* mpwwb cfg2 */
		   0xbe40,	/* mpwwb cfg3 */
		   0x0000,	/* mpwwb cfg4 */
		   0x0000,	/* mpwwb cfg5 */
		   0x0200,	/* mpwwb cfg6 */
		   0x0001,	/* mpwwb cfg7 */
		   0x0000,	/* mpwwb cfg8 */
		   0x0000,	/* mpwwb cfg9 */
		   0x0001,	/* mpwwb cfg10 */
		},
};

static const stwuct intew_c20pww_state mtw_c20_hdmi_27_0 = {
	.cwock = 27000,
	.tx = {  0xbe88, /* tx cfg0 */
		  0x9800, /* tx cfg1 */
		  0x0000, /* tx cfg2 */
		},
	.cmn = { 0x0500, /* cmn cfg0*/
		  0x0005, /* cmn cfg1 */
		  0x0000, /* cmn cfg2 */
		  0x0000, /* cmn cfg3 */
		},
	.mpwwb = { 0xa0e0,	/* mpwwb cfg0 */
		   0x7d80,	/* mpwwb cfg1 */
		   0x0906,	/* mpwwb cfg2 */
		   0xbe40,	/* mpwwb cfg3 */
		   0x0000,	/* mpwwb cfg4 */
		   0x0000,	/* mpwwb cfg5 */
		   0x2200,	/* mpwwb cfg6 */
		   0x0001,	/* mpwwb cfg7 */
		   0x8000,	/* mpwwb cfg8 */
		   0x0000,	/* mpwwb cfg9 */
		   0x0001,	/* mpwwb cfg10 */
		},
};

static const stwuct intew_c20pww_state mtw_c20_hdmi_74_25 = {
	.cwock = 74250,
	.tx = {  0xbe88, /* tx cfg0 */
		  0x9800, /* tx cfg1 */
		  0x0000, /* tx cfg2 */
		},
	.cmn = { 0x0500, /* cmn cfg0*/
		  0x0005, /* cmn cfg1 */
		  0x0000, /* cmn cfg2 */
		  0x0000, /* cmn cfg3 */
		},
	.mpwwb = { 0x609a,	/* mpwwb cfg0 */
		   0x7d40,	/* mpwwb cfg1 */
		   0xca06,	/* mpwwb cfg2 */
		   0xbe40,	/* mpwwb cfg3 */
		   0x0000,	/* mpwwb cfg4 */
		   0x0000,	/* mpwwb cfg5 */
		   0x2200,	/* mpwwb cfg6 */
		   0x0001,	/* mpwwb cfg7 */
		   0x5800,	/* mpwwb cfg8 */
		   0x0000,	/* mpwwb cfg9 */
		   0x0001,	/* mpwwb cfg10 */
		},
};

static const stwuct intew_c20pww_state mtw_c20_hdmi_148_5 = {
	.cwock = 148500,
	.tx = {  0xbe88, /* tx cfg0 */
		  0x9800, /* tx cfg1 */
		  0x0000, /* tx cfg2 */
		},
	.cmn = { 0x0500, /* cmn cfg0*/
		  0x0005, /* cmn cfg1 */
		  0x0000, /* cmn cfg2 */
		  0x0000, /* cmn cfg3 */
		},
	.mpwwb = { 0x409a,	/* mpwwb cfg0 */
		   0x7d20,	/* mpwwb cfg1 */
		   0xca06,	/* mpwwb cfg2 */
		   0xbe40,	/* mpwwb cfg3 */
		   0x0000,	/* mpwwb cfg4 */
		   0x0000,	/* mpwwb cfg5 */
		   0x2200,	/* mpwwb cfg6 */
		   0x0001,	/* mpwwb cfg7 */
		   0x5800,	/* mpwwb cfg8 */
		   0x0000,	/* mpwwb cfg9 */
		   0x0001,	/* mpwwb cfg10 */
		},
};

static const stwuct intew_c20pww_state mtw_c20_hdmi_594 = {
	.cwock = 594000,
	.tx = {  0xbe88, /* tx cfg0 */
		  0x9800, /* tx cfg1 */
		  0x0000, /* tx cfg2 */
		},
	.cmn = { 0x0500, /* cmn cfg0*/
		  0x0005, /* cmn cfg1 */
		  0x0000, /* cmn cfg2 */
		  0x0000, /* cmn cfg3 */
		},
	.mpwwb = { 0x009a,	/* mpwwb cfg0 */
		   0x7d08,	/* mpwwb cfg1 */
		   0xca06,	/* mpwwb cfg2 */
		   0xbe40,	/* mpwwb cfg3 */
		   0x0000,	/* mpwwb cfg4 */
		   0x0000,	/* mpwwb cfg5 */
		   0x2200,	/* mpwwb cfg6 */
		   0x0001,	/* mpwwb cfg7 */
		   0x5800,	/* mpwwb cfg8 */
		   0x0000,	/* mpwwb cfg9 */
		   0x0001,	/* mpwwb cfg10 */
		},
};

static const stwuct intew_c20pww_state mtw_c20_hdmi_300 = {
	.cwock = 3000000,
	.tx = {  0xbe98, /* tx cfg0 */
		  0x9800, /* tx cfg1 */
		  0x0000, /* tx cfg2 */
		},
	.cmn = { 0x0500, /* cmn cfg0*/
		  0x0005, /* cmn cfg1 */
		  0x0000, /* cmn cfg2 */
		  0x0000, /* cmn cfg3 */
		},
	.mpwwb = { 0x209c,	/* mpwwb cfg0 */
		   0x7d10,	/* mpwwb cfg1 */
		   0xca06,	/* mpwwb cfg2 */
		   0xbe40,	/* mpwwb cfg3 */
		   0x0000,	/* mpwwb cfg4 */
		   0x0000,	/* mpwwb cfg5 */
		   0x2200,	/* mpwwb cfg6 */
		   0x0001,	/* mpwwb cfg7 */
		   0x2000,	/* mpwwb cfg8 */
		   0x0000,	/* mpwwb cfg9 */
		   0x0004,	/* mpwwb cfg10 */
		},
};

static const stwuct intew_c20pww_state mtw_c20_hdmi_600 = {
	.cwock = 6000000,
	.tx = {  0xbe98, /* tx cfg0 */
		  0x9800, /* tx cfg1 */
		  0x0000, /* tx cfg2 */
		},
	.cmn = { 0x0500, /* cmn cfg0*/
		  0x0005, /* cmn cfg1 */
		  0x0000, /* cmn cfg2 */
		  0x0000, /* cmn cfg3 */
		},
	.mpwwb = { 0x009c,	/* mpwwb cfg0 */
		   0x7d08,	/* mpwwb cfg1 */
		   0xca06,	/* mpwwb cfg2 */
		   0xbe40,	/* mpwwb cfg3 */
		   0x0000,	/* mpwwb cfg4 */
		   0x0000,	/* mpwwb cfg5 */
		   0x2200,	/* mpwwb cfg6 */
		   0x0001,	/* mpwwb cfg7 */
		   0x2000,	/* mpwwb cfg8 */
		   0x0000,	/* mpwwb cfg9 */
		   0x0004,	/* mpwwb cfg10 */
		},
};

static const stwuct intew_c20pww_state mtw_c20_hdmi_800 = {
	.cwock = 8000000,
	.tx = {  0xbe98, /* tx cfg0 */
		  0x9800, /* tx cfg1 */
		  0x0000, /* tx cfg2 */
		},
	.cmn = { 0x0500, /* cmn cfg0*/
		  0x0005, /* cmn cfg1 */
		  0x0000, /* cmn cfg2 */
		  0x0000, /* cmn cfg3 */
		},
	.mpwwb = { 0x00d0,	/* mpwwb cfg0 */
		   0x7d08,	/* mpwwb cfg1 */
		   0x4a06,	/* mpwwb cfg2 */
		   0xbe40,	/* mpwwb cfg3 */
		   0x0000,	/* mpwwb cfg4 */
		   0x0000,	/* mpwwb cfg5 */
		   0x2200,	/* mpwwb cfg6 */
		   0x0003,	/* mpwwb cfg7 */
		   0x2aaa,	/* mpwwb cfg8 */
		   0x0002,	/* mpwwb cfg9 */
		   0x0004,	/* mpwwb cfg10 */
		},
};

static const stwuct intew_c20pww_state mtw_c20_hdmi_1000 = {
	.cwock = 10000000,
	.tx = {  0xbe98, /* tx cfg0 */
		  0x9800, /* tx cfg1 */
		  0x0000, /* tx cfg2 */
		},
	.cmn = { 0x0500, /* cmn cfg0*/
		  0x0005, /* cmn cfg1 */
		  0x0000, /* cmn cfg2 */
		  0x0000, /* cmn cfg3 */
		},
	.mpwwb = { 0x1104,	/* mpwwb cfg0 */
		   0x7d08,	/* mpwwb cfg1 */
		   0x0a06,	/* mpwwb cfg2 */
		   0xbe40,	/* mpwwb cfg3 */
		   0x0000,	/* mpwwb cfg4 */
		   0x0000,	/* mpwwb cfg5 */
		   0x2200,	/* mpwwb cfg6 */
		   0x0003,	/* mpwwb cfg7 */
		   0x3555,	/* mpwwb cfg8 */
		   0x0001,	/* mpwwb cfg9 */
		   0x0004,	/* mpwwb cfg10 */
		},
};

static const stwuct intew_c20pww_state mtw_c20_hdmi_1200 = {
	.cwock = 12000000,
	.tx = {  0xbe98, /* tx cfg0 */
		  0x9800, /* tx cfg1 */
		  0x0000, /* tx cfg2 */
		},
	.cmn = { 0x0500, /* cmn cfg0*/
		  0x0005, /* cmn cfg1 */
		  0x0000, /* cmn cfg2 */
		  0x0000, /* cmn cfg3 */
		},
	.mpwwb = { 0x0138,	/* mpwwb cfg0 */
		   0x7d08,	/* mpwwb cfg1 */
		   0x5486,	/* mpwwb cfg2 */
		   0xfe40,	/* mpwwb cfg3 */
		   0x0000,	/* mpwwb cfg4 */
		   0x0000,	/* mpwwb cfg5 */
		   0x2200,	/* mpwwb cfg6 */
		   0x0001,	/* mpwwb cfg7 */
		   0x4000,	/* mpwwb cfg8 */
		   0x0000,	/* mpwwb cfg9 */
		   0x0004,	/* mpwwb cfg10 */
		},
};

static const stwuct intew_c20pww_state * const mtw_c20_hdmi_tabwes[] = {
	&mtw_c20_hdmi_25_175,
	&mtw_c20_hdmi_27_0,
	&mtw_c20_hdmi_74_25,
	&mtw_c20_hdmi_148_5,
	&mtw_c20_hdmi_594,
	&mtw_c20_hdmi_300,
	&mtw_c20_hdmi_600,
	&mtw_c20_hdmi_800,
	&mtw_c20_hdmi_1000,
	&mtw_c20_hdmi_1200,
	NUWW,
};

static int intew_c10_phy_check_hdmi_wink_wate(int cwock)
{
	const stwuct intew_c10pww_state * const *tabwes = mtw_c10_hdmi_tabwes;
	int i;

	fow (i = 0; tabwes[i]; i++) {
		if (cwock == tabwes[i]->cwock)
			wetuwn MODE_OK;
	}

	wetuwn MODE_CWOCK_WANGE;
}

static const stwuct intew_c10pww_state * const *
intew_c10pww_tabwes_get(stwuct intew_cwtc_state *cwtc_state,
			stwuct intew_encodew *encodew)
{
	if (intew_cwtc_has_dp_encodew(cwtc_state)) {
		if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP))
			wetuwn mtw_c10_edp_tabwes;
		ewse
			wetuwn mtw_c10_dp_tabwes;
	} ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI)) {
		wetuwn mtw_c10_hdmi_tabwes;
	}

	MISSING_CASE(encodew->type);
	wetuwn NUWW;
}

static void intew_c10pww_update_pww(stwuct intew_cwtc_state *cwtc_state,
				    stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_cx0pww_state *pww_state = &cwtc_state->cx0pww_state;
	int i;

	if (intew_cwtc_has_dp_encodew(cwtc_state)) {
		if (intew_panew_use_ssc(i915)) {
			stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

			pww_state->ssc_enabwed =
				(intew_dp->dpcd[DP_MAX_DOWNSPWEAD] & DP_MAX_DOWNSPWEAD_0_5);
		}
	}

	if (pww_state->ssc_enabwed)
		wetuwn;

	dwm_WAWN_ON(&i915->dwm, AWWAY_SIZE(pww_state->c10.pww) < 9);
	fow (i = 4; i < 9; i++)
		pww_state->c10.pww[i] = 0;
}

static int intew_c10pww_cawc_state(stwuct intew_cwtc_state *cwtc_state,
				   stwuct intew_encodew *encodew)
{
	const stwuct intew_c10pww_state * const *tabwes;
	int i;

	tabwes = intew_c10pww_tabwes_get(cwtc_state, encodew);
	if (!tabwes)
		wetuwn -EINVAW;

	fow (i = 0; tabwes[i]; i++) {
		if (cwtc_state->powt_cwock == tabwes[i]->cwock) {
			cwtc_state->cx0pww_state.c10 = *tabwes[i];
			intew_c10pww_update_pww(cwtc_state, encodew);

			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static void intew_c10pww_weadout_hw_state(stwuct intew_encodew *encodew,
					  stwuct intew_c10pww_state *pww_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	u8 wane = INTEW_CX0_WANE0;
	intew_wakewef_t wakewef;
	int i;

	wakewef = intew_cx0_phy_twansaction_begin(encodew);

	/*
	 * Accowding to C10 VDW Wegistew pwogwamming Sequence we need
	 * to do this to wead PHY intewnaw wegistews fwom MsgBus.
	 */
	intew_cx0_wmw(i915, encodew->powt, wane, PHY_C10_VDW_CONTWOW(1),
		      0, C10_VDW_CTWW_MSGBUS_ACCESS,
		      MB_WWITE_COMMITTED);

	fow (i = 0; i < AWWAY_SIZE(pww_state->pww); i++)
		pww_state->pww[i] = intew_cx0_wead(i915, encodew->powt, wane,
						   PHY_C10_VDW_PWW(i));

	pww_state->cmn = intew_cx0_wead(i915, encodew->powt, wane, PHY_C10_VDW_CMN(0));
	pww_state->tx = intew_cx0_wead(i915, encodew->powt, wane, PHY_C10_VDW_TX(0));

	intew_cx0_phy_twansaction_end(encodew, wakewef);
}

static void intew_c10_pww_pwogwam(stwuct dwm_i915_pwivate *i915,
				  const stwuct intew_cwtc_state *cwtc_state,
				  stwuct intew_encodew *encodew)
{
	const stwuct intew_c10pww_state *pww_state = &cwtc_state->cx0pww_state.c10;
	int i;

	intew_cx0_wmw(i915, encodew->powt, INTEW_CX0_BOTH_WANES, PHY_C10_VDW_CONTWOW(1),
		      0, C10_VDW_CTWW_MSGBUS_ACCESS,
		      MB_WWITE_COMMITTED);

	/* Custom width needs to be pwogwammed to 0 fow both the phy wanes */
	intew_cx0_wmw(i915, encodew->powt, INTEW_CX0_BOTH_WANES, PHY_C10_VDW_CUSTOM_WIDTH,
		      C10_VDW_CUSTOM_WIDTH_MASK, C10_VDW_CUSTOM_WIDTH_8_10,
		      MB_WWITE_COMMITTED);
	intew_cx0_wmw(i915, encodew->powt, INTEW_CX0_BOTH_WANES, PHY_C10_VDW_CONTWOW(1),
		      0, C10_VDW_CTWW_UPDATE_CFG,
		      MB_WWITE_COMMITTED);

	/* Pwogwam the pww vawues onwy fow the mastew wane */
	fow (i = 0; i < AWWAY_SIZE(pww_state->pww); i++)
		intew_cx0_wwite(i915, encodew->powt, INTEW_CX0_WANE0, PHY_C10_VDW_PWW(i),
				pww_state->pww[i],
				(i % 4) ? MB_WWITE_UNCOMMITTED : MB_WWITE_COMMITTED);

	intew_cx0_wwite(i915, encodew->powt, INTEW_CX0_WANE0, PHY_C10_VDW_CMN(0), pww_state->cmn, MB_WWITE_COMMITTED);
	intew_cx0_wwite(i915, encodew->powt, INTEW_CX0_WANE0, PHY_C10_VDW_TX(0), pww_state->tx, MB_WWITE_COMMITTED);

	intew_cx0_wmw(i915, encodew->powt, INTEW_CX0_WANE0, PHY_C10_VDW_CONTWOW(1),
		      0, C10_VDW_CTWW_MASTEW_WANE | C10_VDW_CTWW_UPDATE_CFG,
		      MB_WWITE_COMMITTED);
}

void intew_c10pww_dump_hw_state(stwuct dwm_i915_pwivate *i915,
				const stwuct intew_c10pww_state *hw_state)
{
	boow fwacen;
	int i;
	unsigned int fwac_quot = 0, fwac_wem = 0, fwac_den = 1;
	unsigned int muwtipwiew, tx_cwk_div;

	fwacen = hw_state->pww[0] & C10_PWW0_FWACEN;
	dwm_dbg_kms(&i915->dwm, "c10pww_hw_state: fwacen: %s, ",
		    stw_yes_no(fwacen));

	if (fwacen) {
		fwac_quot = hw_state->pww[12] << 8 | hw_state->pww[11];
		fwac_wem =  hw_state->pww[14] << 8 | hw_state->pww[13];
		fwac_den =  hw_state->pww[10] << 8 | hw_state->pww[9];
		dwm_dbg_kms(&i915->dwm, "quot: %u, wem: %u, den: %u,\n",
			    fwac_quot, fwac_wem, fwac_den);
	}

	muwtipwiew = (WEG_FIEWD_GET8(C10_PWW3_MUWTIPWIEWH_MASK, hw_state->pww[3]) << 8 |
		      hw_state->pww[2]) / 2 + 16;
	tx_cwk_div = WEG_FIEWD_GET8(C10_PWW15_TXCWKDIV_MASK, hw_state->pww[15]);
	dwm_dbg_kms(&i915->dwm,
		    "muwtipwiew: %u, tx_cwk_div: %u.\n", muwtipwiew, tx_cwk_div);

	dwm_dbg_kms(&i915->dwm, "c10pww_wawhw_state:");
	dwm_dbg_kms(&i915->dwm, "tx: 0x%x, cmn: 0x%x\n", hw_state->tx, hw_state->cmn);

	BUIWD_BUG_ON(AWWAY_SIZE(hw_state->pww) % 4);
	fow (i = 0; i < AWWAY_SIZE(hw_state->pww); i = i + 4)
		dwm_dbg_kms(&i915->dwm, "pww[%d] = 0x%x, pww[%d] = 0x%x, pww[%d] = 0x%x, pww[%d] = 0x%x\n",
			    i, hw_state->pww[i], i + 1, hw_state->pww[i + 1],
			    i + 2, hw_state->pww[i + 2], i + 3, hw_state->pww[i + 3]);
}

static int intew_c20_compute_hdmi_tmds_pww(u64 pixew_cwock, stwuct intew_c20pww_state *pww_state)
{
	u64 datawate;
	u64 mpww_tx_cwk_div;
	u64 vco_fweq_shift;
	u64 vco_fweq;
	u64 muwtipwiew;
	u64 mpww_muwtipwiew;
	u64 mpww_fwacn_quot;
	u64 mpww_fwacn_wem;
	u8  mpwwb_ana_fweq_vco;
	u8  mpww_div_muwtipwiew;

	if (pixew_cwock < 25175 || pixew_cwock > 600000)
		wetuwn -EINVAW;

	datawate = ((u64)pixew_cwock * 1000) * 10;
	mpww_tx_cwk_div = iwog2(div64_u64((u64)CWOCK_9999MHZ, (u64)datawate));
	vco_fweq_shift = iwog2(div64_u64((u64)CWOCK_4999MHZ * (u64)256, (u64)datawate));
	vco_fweq = (datawate << vco_fweq_shift) >> 8;
	muwtipwiew = div64_u64((vco_fweq << 28), (WEFCWK_38_4_MHZ >> 4));
	mpww_muwtipwiew = 2 * (muwtipwiew >> 32);

	mpww_fwacn_quot = (muwtipwiew >> 16) & 0xFFFF;
	mpww_fwacn_wem  = muwtipwiew & 0xFFFF;

	mpww_div_muwtipwiew = min_t(u8, div64_u64((vco_fweq * 16 + (datawate >> 1)),
						  datawate), 255);

	if (vco_fweq <= DATAWATE_3000000000)
		mpwwb_ana_fweq_vco = MPWWB_ANA_FWEQ_VCO_3;
	ewse if (vco_fweq <= DATAWATE_3500000000)
		mpwwb_ana_fweq_vco = MPWWB_ANA_FWEQ_VCO_2;
	ewse if (vco_fweq <= DATAWATE_4000000000)
		mpwwb_ana_fweq_vco = MPWWB_ANA_FWEQ_VCO_1;
	ewse
		mpwwb_ana_fweq_vco = MPWWB_ANA_FWEQ_VCO_0;

	pww_state->cwock	= pixew_cwock;
	pww_state->tx[0]	= 0xbe88;
	pww_state->tx[1]	= 0x9800;
	pww_state->tx[2]	= 0x0000;
	pww_state->cmn[0]	= 0x0500;
	pww_state->cmn[1]	= 0x0005;
	pww_state->cmn[2]	= 0x0000;
	pww_state->cmn[3]	= 0x0000;
	pww_state->mpwwb[0]	= (MPWW_TX_CWK_DIV(mpww_tx_cwk_div) |
				   MPWW_MUWTIPWIEW(mpww_muwtipwiew));
	pww_state->mpwwb[1]	= (CAW_DAC_CODE(CAW_DAC_CODE_31) |
				   WOWD_CWK_DIV |
				   MPWW_DIV_MUWTIPWIEW(mpww_div_muwtipwiew));
	pww_state->mpwwb[2]	= (MPWWB_ANA_FWEQ_VCO(mpwwb_ana_fweq_vco) |
				   CP_PWOP(CP_PWOP_20) |
				   CP_INT(CP_INT_6));
	pww_state->mpwwb[3]	= (V2I(V2I_2) |
				   CP_PWOP_GS(CP_PWOP_GS_30) |
				   CP_INT_GS(CP_INT_GS_28));
	pww_state->mpwwb[4]	= 0x0000;
	pww_state->mpwwb[5]	= 0x0000;
	pww_state->mpwwb[6]	= (C20_MPWWB_FWACEN | SSC_UP_SPWEAD);
	pww_state->mpwwb[7]	= MPWW_FWACN_DEN;
	pww_state->mpwwb[8]	= mpww_fwacn_quot;
	pww_state->mpwwb[9]	= mpww_fwacn_wem;
	pww_state->mpwwb[10]	= HDMI_DIV(HDMI_DIV_1);

	wetuwn 0;
}

static int intew_c20_phy_check_hdmi_wink_wate(int cwock)
{
	const stwuct intew_c20pww_state * const *tabwes = mtw_c20_hdmi_tabwes;
	int i;

	fow (i = 0; tabwes[i]; i++) {
		if (cwock == tabwes[i]->cwock)
			wetuwn MODE_OK;
	}

	if (cwock >= 25175 && cwock <= 594000)
		wetuwn MODE_OK;

	wetuwn MODE_CWOCK_WANGE;
}

int intew_cx0_phy_check_hdmi_wink_wate(stwuct intew_hdmi *hdmi, int cwock)
{
	stwuct intew_digitaw_powt *dig_powt = hdmi_to_dig_powt(hdmi);
	stwuct dwm_i915_pwivate *i915 = intew_hdmi_to_i915(hdmi);
	enum phy phy = intew_powt_to_phy(i915, dig_powt->base.powt);

	if (intew_is_c10phy(i915, phy))
		wetuwn intew_c10_phy_check_hdmi_wink_wate(cwock);
	wetuwn intew_c20_phy_check_hdmi_wink_wate(cwock);
}

static const stwuct intew_c20pww_state * const *
intew_c20_pww_tabwes_get(stwuct intew_cwtc_state *cwtc_state,
			 stwuct intew_encodew *encodew)
{
	if (intew_cwtc_has_dp_encodew(cwtc_state))
		wetuwn mtw_c20_dp_tabwes;
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		wetuwn mtw_c20_hdmi_tabwes;

	MISSING_CASE(encodew->type);
	wetuwn NUWW;
}

static int intew_c20pww_cawc_state(stwuct intew_cwtc_state *cwtc_state,
				   stwuct intew_encodew *encodew)
{
	const stwuct intew_c20pww_state * const *tabwes;
	int i;

	/* twy computed C20 HDMI tabwes befowe using consowidated tabwes */
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI)) {
		if (intew_c20_compute_hdmi_tmds_pww(cwtc_state->powt_cwock,
						    &cwtc_state->cx0pww_state.c20) == 0)
			wetuwn 0;
	}

	tabwes = intew_c20_pww_tabwes_get(cwtc_state, encodew);
	if (!tabwes)
		wetuwn -EINVAW;

	fow (i = 0; tabwes[i]; i++) {
		if (cwtc_state->powt_cwock == tabwes[i]->cwock) {
			cwtc_state->cx0pww_state.c20 = *tabwes[i];
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

int intew_cx0pww_cawc_state(stwuct intew_cwtc_state *cwtc_state,
			    stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	if (intew_is_c10phy(i915, phy))
		wetuwn intew_c10pww_cawc_state(cwtc_state, encodew);
	wetuwn intew_c20pww_cawc_state(cwtc_state, encodew);
}

static boow intew_c20_use_mpwwa(u32 cwock)
{
	/* 10G and 20G wates use MPWWA */
	if (cwock == 1000000 || cwock == 2000000)
		wetuwn twue;

	wetuwn fawse;
}

static void intew_c20pww_weadout_hw_state(stwuct intew_encodew *encodew,
					  stwuct intew_c20pww_state *pww_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	boow cntx;
	intew_wakewef_t wakewef;
	int i;

	wakewef = intew_cx0_phy_twansaction_begin(encodew);

	/* 1. Wead cuwwent context sewection */
	cntx = intew_cx0_wead(i915, encodew->powt, INTEW_CX0_WANE0, PHY_C20_VDW_CUSTOM_SEWDES_WATE) & PHY_C20_CONTEXT_TOGGWE;

	/* Wead Tx configuwation */
	fow (i = 0; i < AWWAY_SIZE(pww_state->tx); i++) {
		if (cntx)
			pww_state->tx[i] = intew_c20_swam_wead(i915, encodew->powt, INTEW_CX0_WANE0,
							       PHY_C20_B_TX_CNTX_CFG(i));
		ewse
			pww_state->tx[i] = intew_c20_swam_wead(i915, encodew->powt, INTEW_CX0_WANE0,
							       PHY_C20_A_TX_CNTX_CFG(i));
	}

	/* Wead common configuwation */
	fow (i = 0; i < AWWAY_SIZE(pww_state->cmn); i++) {
		if (cntx)
			pww_state->cmn[i] = intew_c20_swam_wead(i915, encodew->powt, INTEW_CX0_WANE0,
								PHY_C20_B_CMN_CNTX_CFG(i));
		ewse
			pww_state->cmn[i] = intew_c20_swam_wead(i915, encodew->powt, INTEW_CX0_WANE0,
								PHY_C20_A_CMN_CNTX_CFG(i));
	}

	if (pww_state->tx[0] & C20_PHY_USE_MPWWB) {
		/* MPWWB configuwation */
		fow (i = 0; i < AWWAY_SIZE(pww_state->mpwwb); i++) {
			if (cntx)
				pww_state->mpwwb[i] = intew_c20_swam_wead(i915, encodew->powt, INTEW_CX0_WANE0,
									  PHY_C20_B_MPWWB_CNTX_CFG(i));
			ewse
				pww_state->mpwwb[i] = intew_c20_swam_wead(i915, encodew->powt, INTEW_CX0_WANE0,
									  PHY_C20_A_MPWWB_CNTX_CFG(i));
		}
	} ewse {
		/* MPWWA configuwation */
		fow (i = 0; i < AWWAY_SIZE(pww_state->mpwwa); i++) {
			if (cntx)
				pww_state->mpwwa[i] = intew_c20_swam_wead(i915, encodew->powt, INTEW_CX0_WANE0,
									  PHY_C20_B_MPWWA_CNTX_CFG(i));
			ewse
				pww_state->mpwwa[i] = intew_c20_swam_wead(i915, encodew->powt, INTEW_CX0_WANE0,
									  PHY_C20_A_MPWWA_CNTX_CFG(i));
		}
	}

	intew_cx0_phy_twansaction_end(encodew, wakewef);
}

void intew_c20pww_dump_hw_state(stwuct dwm_i915_pwivate *i915,
				const stwuct intew_c20pww_state *hw_state)
{
	int i;

	dwm_dbg_kms(&i915->dwm, "c20pww_hw_state:\n");
	dwm_dbg_kms(&i915->dwm, "tx[0] = 0x%.4x, tx[1] = 0x%.4x, tx[2] = 0x%.4x\n",
		    hw_state->tx[0], hw_state->tx[1], hw_state->tx[2]);
	dwm_dbg_kms(&i915->dwm, "cmn[0] = 0x%.4x, cmn[1] = 0x%.4x, cmn[2] = 0x%.4x, cmn[3] = 0x%.4x\n",
		    hw_state->cmn[0], hw_state->cmn[1], hw_state->cmn[2], hw_state->cmn[3]);

	if (intew_c20_use_mpwwa(hw_state->cwock)) {
		fow (i = 0; i < AWWAY_SIZE(hw_state->mpwwa); i++)
			dwm_dbg_kms(&i915->dwm, "mpwwa[%d] = 0x%.4x\n", i, hw_state->mpwwa[i]);
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(hw_state->mpwwb); i++)
			dwm_dbg_kms(&i915->dwm, "mpwwb[%d] = 0x%.4x\n", i, hw_state->mpwwb[i]);
	}
}

static u8 intew_c20_get_dp_wate(u32 cwock)
{
	switch (cwock) {
	case 162000: /* 1.62 Gbps DP1.4 */
		wetuwn 0;
	case 270000: /* 2.7 Gbps DP1.4 */
		wetuwn 1;
	case 540000: /* 5.4 Gbps DP 1.4 */
		wetuwn 2;
	case 810000: /* 8.1 Gbps DP1.4 */
		wetuwn 3;
	case 216000: /* 2.16 Gbps eDP */
		wetuwn 4;
	case 243000: /* 2.43 Gbps eDP */
		wetuwn 5;
	case 324000: /* 3.24 Gbps eDP */
		wetuwn 6;
	case 432000: /* 4.32 Gbps eDP */
		wetuwn 7;
	case 1000000: /* 10 Gbps DP2.0 */
		wetuwn 8;
	case 1350000: /* 13.5 Gbps DP2.0 */
		wetuwn 9;
	case 2000000: /* 20 Gbps DP2.0 */
		wetuwn 10;
	case 648000: /* 6.48 Gbps eDP*/
		wetuwn 11;
	case 675000: /* 6.75 Gbps eDP*/
		wetuwn 12;
	defauwt:
		MISSING_CASE(cwock);
		wetuwn 0;
	}
}

static u8 intew_c20_get_hdmi_wate(u32 cwock)
{
	if (cwock >= 25175 && cwock <= 600000)
		wetuwn 0;

	switch (cwock) {
	case 300000: /* 3 Gbps */
	case 600000: /* 6 Gbps */
	case 1200000: /* 12 Gbps */
		wetuwn 1;
	case 800000: /* 8 Gbps */
		wetuwn 2;
	case 1000000: /* 10 Gbps */
		wetuwn 3;
	defauwt:
		MISSING_CASE(cwock);
		wetuwn 0;
	}
}

static boow is_dp2(u32 cwock)
{
	/* DP2.0 cwock wates */
	if (cwock == 1000000 || cwock == 1350000 || cwock  == 2000000)
		wetuwn twue;

	wetuwn fawse;
}

static boow is_hdmi_fww(u32 cwock)
{
	switch (cwock) {
	case 300000: /* 3 Gbps */
	case 600000: /* 6 Gbps */
	case 800000: /* 8 Gbps */
	case 1000000: /* 10 Gbps */
	case 1200000: /* 12 Gbps */
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow intew_c20_pwotocow_switch_vawid(stwuct intew_encodew *encodew)
{
	stwuct intew_digitaw_powt *intew_dig_powt = enc_to_dig_powt(encodew);

	/* banks shouwd not be cweawed fow DPAWT/USB4/TBT modes */
	/* TODO: optimize we-cawibwation in wegacy mode */
	wetuwn intew_tc_powt_in_wegacy_mode(intew_dig_powt);
}

static int intew_get_c20_custom_width(u32 cwock, boow dp)
{
	if (dp && is_dp2(cwock))
		wetuwn 2;
	ewse if (is_hdmi_fww(cwock))
		wetuwn 1;
	ewse
		wetuwn 0;
}

static void intew_c20_pww_pwogwam(stwuct dwm_i915_pwivate *i915,
				  const stwuct intew_cwtc_state *cwtc_state,
				  stwuct intew_encodew *encodew)
{
	const stwuct intew_c20pww_state *pww_state = &cwtc_state->cx0pww_state.c20;
	boow dp = fawse;
	int wane = cwtc_state->wane_count > 2 ? INTEW_CX0_BOTH_WANES : INTEW_CX0_WANE0;
	u32 cwock = cwtc_state->powt_cwock;
	boow cntx;
	int i;

	if (intew_cwtc_has_dp_encodew(cwtc_state))
		dp = twue;

	/* 1. Wead cuwwent context sewection */
	cntx = intew_cx0_wead(i915, encodew->powt, INTEW_CX0_WANE0, PHY_C20_VDW_CUSTOM_SEWDES_WATE) & BIT(0);

	/*
	 * 2. If thewe is a pwotocow switch fwom HDMI to DP ow vice vewsa, cweaw
	 * the wane #0 MPWWB CAW_DONE_BANK DP2.0 10G and 20G wates enabwe MPWWA.
	 * Pwotocow switch is onwy appwicabwe fow MPWWA
	 */
	if (intew_c20_pwotocow_switch_vawid(encodew)) {
		fow (i = 0; i < 4; i++)
			intew_c20_swam_wwite(i915, encodew->powt, INTEW_CX0_WANE0, WAWWANEAONX_DIG_TX_MPWWB_CAW_DONE_BANK(i), 0);
		usweep_wange(4000, 4100);
	}

	/* 3. Wwite SWAM configuwation context. If A in use, wwite configuwation to B context */
	/* 3.1 Tx configuwation */
	fow (i = 0; i < AWWAY_SIZE(pww_state->tx); i++) {
		if (cntx)
			intew_c20_swam_wwite(i915, encodew->powt, INTEW_CX0_WANE0, PHY_C20_A_TX_CNTX_CFG(i), pww_state->tx[i]);
		ewse
			intew_c20_swam_wwite(i915, encodew->powt, INTEW_CX0_WANE0, PHY_C20_B_TX_CNTX_CFG(i), pww_state->tx[i]);
	}

	/* 3.2 common configuwation */
	fow (i = 0; i < AWWAY_SIZE(pww_state->cmn); i++) {
		if (cntx)
			intew_c20_swam_wwite(i915, encodew->powt, INTEW_CX0_WANE0, PHY_C20_A_CMN_CNTX_CFG(i), pww_state->cmn[i]);
		ewse
			intew_c20_swam_wwite(i915, encodew->powt, INTEW_CX0_WANE0, PHY_C20_B_CMN_CNTX_CFG(i), pww_state->cmn[i]);
	}

	/* 3.3 mpwwb ow mpwwa configuwation */
	if (intew_c20_use_mpwwa(cwock)) {
		fow (i = 0; i < AWWAY_SIZE(pww_state->mpwwa); i++) {
			if (cntx)
				intew_c20_swam_wwite(i915, encodew->powt, INTEW_CX0_WANE0,
						     PHY_C20_A_MPWWA_CNTX_CFG(i),
						     pww_state->mpwwa[i]);
			ewse
				intew_c20_swam_wwite(i915, encodew->powt, INTEW_CX0_WANE0,
						     PHY_C20_B_MPWWA_CNTX_CFG(i),
						     pww_state->mpwwa[i]);
		}
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(pww_state->mpwwb); i++) {
			if (cntx)
				intew_c20_swam_wwite(i915, encodew->powt, INTEW_CX0_WANE0,
						     PHY_C20_A_MPWWB_CNTX_CFG(i),
						     pww_state->mpwwb[i]);
			ewse
				intew_c20_swam_wwite(i915, encodew->powt, INTEW_CX0_WANE0,
						     PHY_C20_B_MPWWB_CNTX_CFG(i),
						     pww_state->mpwwb[i]);
		}
	}

	/* 4. Pwogwam custom width to match the wink pwotocow */
	intew_cx0_wmw(i915, encodew->powt, wane, PHY_C20_VDW_CUSTOM_WIDTH,
		      PHY_C20_CUSTOM_WIDTH_MASK,
		      PHY_C20_CUSTOM_WIDTH(intew_get_c20_custom_width(cwock, dp)),
		      MB_WWITE_COMMITTED);

	/* 5. Fow DP ow 6. Fow HDMI */
	if (dp) {
		intew_cx0_wmw(i915, encodew->powt, wane, PHY_C20_VDW_CUSTOM_SEWDES_WATE,
			      BIT(6) | PHY_C20_CUSTOM_SEWDES_MASK,
			      BIT(6) | PHY_C20_CUSTOM_SEWDES(intew_c20_get_dp_wate(cwock)),
			      MB_WWITE_COMMITTED);
	} ewse {
		intew_cx0_wmw(i915, encodew->powt, wane, PHY_C20_VDW_CUSTOM_SEWDES_WATE,
			      BIT(7) | PHY_C20_CUSTOM_SEWDES_MASK,
			      is_hdmi_fww(cwock) ? BIT(7) : 0,
			      MB_WWITE_COMMITTED);

		intew_cx0_wwite(i915, encodew->powt, INTEW_CX0_BOTH_WANES, PHY_C20_VDW_HDMI_WATE,
				intew_c20_get_hdmi_wate(cwock),
				MB_WWITE_COMMITTED);
	}

	/*
	 * 7. Wwite Vendow specific wegistews to toggwe context setting to woad
	 * the updated pwogwamming toggwe context bit
	 */
	intew_cx0_wmw(i915, encodew->powt, wane, PHY_C20_VDW_CUSTOM_SEWDES_WATE,
		      BIT(0), cntx ? 0 : 1, MB_WWITE_COMMITTED);
}

static int intew_c10pww_cawc_powt_cwock(stwuct intew_encodew *encodew,
					const stwuct intew_c10pww_state *pww_state)
{
	unsigned int fwac_quot = 0, fwac_wem = 0, fwac_den = 1;
	unsigned int muwtipwiew, tx_cwk_div, hdmi_div, wefcwk = 38400;
	int tmpcwk = 0;

	if (pww_state->pww[0] & C10_PWW0_FWACEN) {
		fwac_quot = pww_state->pww[12] << 8 | pww_state->pww[11];
		fwac_wem =  pww_state->pww[14] << 8 | pww_state->pww[13];
		fwac_den =  pww_state->pww[10] << 8 | pww_state->pww[9];
	}

	muwtipwiew = (WEG_FIEWD_GET8(C10_PWW3_MUWTIPWIEWH_MASK, pww_state->pww[3]) << 8 |
		      pww_state->pww[2]) / 2 + 16;

	tx_cwk_div = WEG_FIEWD_GET8(C10_PWW15_TXCWKDIV_MASK, pww_state->pww[15]);
	hdmi_div = WEG_FIEWD_GET8(C10_PWW15_HDMIDIV_MASK, pww_state->pww[15]);

	tmpcwk = DIV_WOUND_CWOSEST_UWW(muw_u32_u32(wefcwk, (muwtipwiew << 16) + fwac_quot) +
				     DIV_WOUND_CWOSEST(wefcwk * fwac_wem, fwac_den),
				     10 << (tx_cwk_div + 16));
	tmpcwk *= (hdmi_div ? 2 : 1);

	wetuwn tmpcwk;
}

static int intew_c20pww_cawc_powt_cwock(stwuct intew_encodew *encodew,
					const stwuct intew_c20pww_state *pww_state)
{
	unsigned int fwac, fwac_en, fwac_quot, fwac_wem, fwac_den;
	unsigned int muwtipwiew, wefcwk = 38400;
	unsigned int tx_cwk_div;
	unsigned int wef_cwk_mpwwb_div;
	unsigned int fb_cwk_div4_en;
	unsigned int wef, vco;
	unsigned int tx_wate_muwt;
	unsigned int tx_wate = WEG_FIEWD_GET(C20_PHY_TX_WATE, pww_state->tx[0]);

	if (pww_state->tx[0] & C20_PHY_USE_MPWWB) {
		tx_wate_muwt = 1;
		fwac_en = WEG_FIEWD_GET(C20_MPWWB_FWACEN, pww_state->mpwwb[6]);
		fwac_quot = pww_state->mpwwb[8];
		fwac_wem =  pww_state->mpwwb[9];
		fwac_den =  pww_state->mpwwb[7];
		muwtipwiew = WEG_FIEWD_GET(C20_MUWTIPWIEW_MASK, pww_state->mpwwb[0]);
		tx_cwk_div = WEG_FIEWD_GET(C20_MPWWB_TX_CWK_DIV_MASK, pww_state->mpwwb[0]);
		wef_cwk_mpwwb_div = WEG_FIEWD_GET(C20_WEF_CWK_MPWWB_DIV_MASK, pww_state->mpwwb[6]);
		fb_cwk_div4_en = 0;
	} ewse {
		tx_wate_muwt = 2;
		fwac_en = WEG_FIEWD_GET(C20_MPWWA_FWACEN, pww_state->mpwwa[6]);
		fwac_quot = pww_state->mpwwa[8];
		fwac_wem =  pww_state->mpwwa[9];
		fwac_den =  pww_state->mpwwa[7];
		muwtipwiew = WEG_FIEWD_GET(C20_MUWTIPWIEW_MASK, pww_state->mpwwa[0]);
		tx_cwk_div = WEG_FIEWD_GET(C20_MPWWA_TX_CWK_DIV_MASK, pww_state->mpwwa[1]);
		wef_cwk_mpwwb_div = WEG_FIEWD_GET(C20_WEF_CWK_MPWWB_DIV_MASK, pww_state->mpwwa[6]);
		fb_cwk_div4_en = WEG_FIEWD_GET(C20_FB_CWK_DIV4_EN, pww_state->mpwwa[0]);
	}

	if (fwac_en)
		fwac = fwac_quot + DIV_WOUND_CWOSEST(fwac_wem, fwac_den);
	ewse
		fwac = 0;

	wef = DIV_WOUND_CWOSEST(wefcwk * (1 << (1 + fb_cwk_div4_en)), 1 << wef_cwk_mpwwb_div);
	vco = DIV_WOUND_CWOSEST_UWW(muw_u32_u32(wef, (muwtipwiew << (17 - 2)) + fwac) >> 17, 10);

	wetuwn vco << tx_wate_muwt >> tx_cwk_div >> tx_wate;
}

static void intew_pwogwam_powt_cwock_ctw(stwuct intew_encodew *encodew,
					 const stwuct intew_cwtc_state *cwtc_state,
					 boow wane_wevewsaw)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	u32 vaw = 0;

	intew_de_wmw(i915, XEWPDP_POWT_BUF_CTW1(encodew->powt), XEWPDP_POWT_WEVEWSAW,
		     wane_wevewsaw ? XEWPDP_POWT_WEVEWSAW : 0);

	if (wane_wevewsaw)
		vaw |= XEWPDP_WANE1_PHY_CWOCK_SEWECT;

	vaw |= XEWPDP_FOWWAWD_CWOCK_UNGATE;

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI) &&
	    is_hdmi_fww(cwtc_state->powt_cwock))
		vaw |= XEWPDP_DDI_CWOCK_SEWECT(XEWPDP_DDI_CWOCK_SEWECT_DIV18CWK);
	ewse
		vaw |= XEWPDP_DDI_CWOCK_SEWECT(XEWPDP_DDI_CWOCK_SEWECT_MAXPCWK);

	/* TODO: HDMI FWW */
	/* DP2.0 10G and 20G wates enabwe MPWWA*/
	if (cwtc_state->powt_cwock == 1000000 || cwtc_state->powt_cwock == 2000000)
		vaw |= cwtc_state->cx0pww_state.ssc_enabwed ? XEWPDP_SSC_ENABWE_PWWA : 0;
	ewse
		vaw |= cwtc_state->cx0pww_state.ssc_enabwed ? XEWPDP_SSC_ENABWE_PWWB : 0;

	intew_de_wmw(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt),
		     XEWPDP_WANE1_PHY_CWOCK_SEWECT | XEWPDP_FOWWAWD_CWOCK_UNGATE |
		     XEWPDP_DDI_CWOCK_SEWECT_MASK | XEWPDP_SSC_ENABWE_PWWA |
		     XEWPDP_SSC_ENABWE_PWWB, vaw);
}

static u32 intew_cx0_get_powewdown_update(u8 wane_mask)
{
	u32 vaw = 0;
	int wane = 0;

	fow_each_cx0_wane_in_mask(wane_mask, wane)
		vaw |= XEWPDP_WANE_POWEWDOWN_UPDATE(wane);

	wetuwn vaw;
}

static u32 intew_cx0_get_powewdown_state(u8 wane_mask, u8 state)
{
	u32 vaw = 0;
	int wane = 0;

	fow_each_cx0_wane_in_mask(wane_mask, wane)
		vaw |= XEWPDP_WANE_POWEWDOWN_NEW_STATE(wane, state);

	wetuwn vaw;
}

static void intew_cx0_powewdown_change_sequence(stwuct dwm_i915_pwivate *i915,
						enum powt powt,
						u8 wane_mask, u8 state)
{
	enum phy phy = intew_powt_to_phy(i915, powt);
	int wane;

	intew_de_wmw(i915, XEWPDP_POWT_BUF_CTW2(powt),
		     intew_cx0_get_powewdown_state(INTEW_CX0_BOTH_WANES, XEWPDP_WANE_POWEWDOWN_NEW_STATE_MASK),
		     intew_cx0_get_powewdown_state(wane_mask, state));

	/* Wait fow pending twansactions.*/
	fow_each_cx0_wane_in_mask(wane_mask, wane)
		if (intew_de_wait_fow_cweaw(i915, XEWPDP_POWT_M2P_MSGBUS_CTW(powt, wane),
					    XEWPDP_POWT_M2P_TWANSACTION_PENDING,
					    XEWPDP_MSGBUS_TIMEOUT_SWOW)) {
			dwm_dbg_kms(&i915->dwm,
				    "PHY %c Timeout waiting fow pwevious twansaction to compwete. Weset the bus.\n",
				    phy_name(phy));
			intew_cx0_bus_weset(i915, powt, wane);
		}

	intew_de_wmw(i915, XEWPDP_POWT_BUF_CTW2(powt),
		     intew_cx0_get_powewdown_update(INTEW_CX0_BOTH_WANES),
		     intew_cx0_get_powewdown_update(wane_mask));

	/* Update Timeout Vawue */
	if (__intew_de_wait_fow_wegistew(i915, XEWPDP_POWT_BUF_CTW2(powt),
					 intew_cx0_get_powewdown_update(wane_mask), 0,
					 XEWPDP_POWT_POWEWDOWN_UPDATE_TIMEOUT_US, 0, NUWW))
		dwm_wawn(&i915->dwm, "PHY %c faiwed to bwing out of Wane weset aftew %dus.\n",
			 phy_name(phy), XEWPDP_POWT_WESET_STAWT_TIMEOUT_US);
}

static void intew_cx0_setup_powewdown(stwuct dwm_i915_pwivate *i915, enum powt powt)
{
	intew_de_wmw(i915, XEWPDP_POWT_BUF_CTW2(powt),
		     XEWPDP_POWEW_STATE_WEADY_MASK,
		     XEWPDP_POWEW_STATE_WEADY(CX0_P2_STATE_WEADY));
	intew_de_wmw(i915, XEWPDP_POWT_BUF_CTW3(powt),
		     XEWPDP_POWEW_STATE_ACTIVE_MASK |
		     XEWPDP_PWW_WANE_STAGGEWING_DEWAY_MASK,
		     XEWPDP_POWEW_STATE_ACTIVE(CX0_P0_STATE_ACTIVE) |
		     XEWPDP_PWW_WANE_STAGGEWING_DEWAY(0));
}

static u32 intew_cx0_get_pcwk_wefcwk_wequest(u8 wane_mask)
{
	u32 vaw = 0;
	int wane = 0;

	fow_each_cx0_wane_in_mask(wane_mask, wane)
		vaw |= XEWPDP_WANE_PCWK_WEFCWK_WEQUEST(wane);

	wetuwn vaw;
}

static u32 intew_cx0_get_pcwk_wefcwk_ack(u8 wane_mask)
{
	u32 vaw = 0;
	int wane = 0;

	fow_each_cx0_wane_in_mask(wane_mask, wane)
		vaw |= XEWPDP_WANE_PCWK_WEFCWK_ACK(wane);

	wetuwn vaw;
}

static void intew_cx0_phy_wane_weset(stwuct dwm_i915_pwivate *i915,
				     stwuct intew_encodew *encodew,
				     boow wane_wevewsaw)
{
	enum powt powt = encodew->powt;
	enum phy phy = intew_powt_to_phy(i915, powt);
	u8 owned_wane_mask = intew_cx0_get_owned_wane_mask(i915, encodew);
	u8 wane_mask = wane_wevewsaw ? INTEW_CX0_WANE1 : INTEW_CX0_WANE0;
	u32 wane_pipe_weset = owned_wane_mask == INTEW_CX0_BOTH_WANES
				? XEWPDP_WANE_PIPE_WESET(0) | XEWPDP_WANE_PIPE_WESET(1)
				: XEWPDP_WANE_PIPE_WESET(0);
	u32 wane_phy_cuwwent_status = owned_wane_mask == INTEW_CX0_BOTH_WANES
					? (XEWPDP_WANE_PHY_CUWWENT_STATUS(0) |
					   XEWPDP_WANE_PHY_CUWWENT_STATUS(1))
					: XEWPDP_WANE_PHY_CUWWENT_STATUS(0);

	if (__intew_de_wait_fow_wegistew(i915, XEWPDP_POWT_BUF_CTW1(powt),
					 XEWPDP_POWT_BUF_SOC_PHY_WEADY,
					 XEWPDP_POWT_BUF_SOC_PHY_WEADY,
					 XEWPDP_POWT_BUF_SOC_WEADY_TIMEOUT_US, 0, NUWW))
		dwm_wawn(&i915->dwm, "PHY %c faiwed to bwing out of SOC weset aftew %dus.\n",
			 phy_name(phy), XEWPDP_POWT_BUF_SOC_WEADY_TIMEOUT_US);

	intew_de_wmw(i915, XEWPDP_POWT_BUF_CTW2(powt), wane_pipe_weset,
		     wane_pipe_weset);

	if (__intew_de_wait_fow_wegistew(i915, XEWPDP_POWT_BUF_CTW2(powt),
					 wane_phy_cuwwent_status, wane_phy_cuwwent_status,
					 XEWPDP_POWT_WESET_STAWT_TIMEOUT_US, 0, NUWW))
		dwm_wawn(&i915->dwm, "PHY %c faiwed to bwing out of Wane weset aftew %dus.\n",
			 phy_name(phy), XEWPDP_POWT_WESET_STAWT_TIMEOUT_US);

	intew_de_wmw(i915, XEWPDP_POWT_CWOCK_CTW(powt),
		     intew_cx0_get_pcwk_wefcwk_wequest(owned_wane_mask),
		     intew_cx0_get_pcwk_wefcwk_wequest(wane_mask));

	if (__intew_de_wait_fow_wegistew(i915, XEWPDP_POWT_CWOCK_CTW(powt),
					 intew_cx0_get_pcwk_wefcwk_ack(owned_wane_mask),
					 intew_cx0_get_pcwk_wefcwk_ack(wane_mask),
					 XEWPDP_WEFCWK_ENABWE_TIMEOUT_US, 0, NUWW))
		dwm_wawn(&i915->dwm, "PHY %c faiwed to wequest wefcwk aftew %dus.\n",
			 phy_name(phy), XEWPDP_WEFCWK_ENABWE_TIMEOUT_US);

	intew_cx0_powewdown_change_sequence(i915, powt, INTEW_CX0_BOTH_WANES,
					    CX0_P2_STATE_WESET);
	intew_cx0_setup_powewdown(i915, powt);

	intew_de_wmw(i915, XEWPDP_POWT_BUF_CTW2(powt), wane_pipe_weset, 0);

	if (intew_de_wait_fow_cweaw(i915, XEWPDP_POWT_BUF_CTW2(powt), wane_phy_cuwwent_status,
				    XEWPDP_POWT_WESET_END_TIMEOUT))
		dwm_wawn(&i915->dwm, "PHY %c faiwed to bwing out of Wane weset aftew %dms.\n",
			 phy_name(phy), XEWPDP_POWT_WESET_END_TIMEOUT);
}

static void intew_cx0_pwogwam_phy_wane(stwuct dwm_i915_pwivate *i915,
				       stwuct intew_encodew *encodew, int wane_count,
				       boow wane_wevewsaw)
{
	int i;
	u8 disabwes;
	boow dp_awt_mode = intew_tc_powt_in_dp_awt_mode(enc_to_dig_powt(encodew));
	u8 owned_wane_mask = intew_cx0_get_owned_wane_mask(i915, encodew);
	enum powt powt = encodew->powt;

	if (intew_is_c10phy(i915, intew_powt_to_phy(i915, powt)))
		intew_cx0_wmw(i915, powt, owned_wane_mask,
			      PHY_C10_VDW_CONTWOW(1), 0,
			      C10_VDW_CTWW_MSGBUS_ACCESS,
			      MB_WWITE_COMMITTED);

	if (wane_wevewsaw)
		disabwes = WEG_GENMASK8(3, 0) >> wane_count;
	ewse
		disabwes = WEG_GENMASK8(3, 0) << wane_count;

	if (dp_awt_mode && wane_count == 1) {
		disabwes &= ~WEG_GENMASK8(1, 0);
		disabwes |= WEG_FIEWD_PWEP8(WEG_GENMASK8(1, 0), 0x1);
	}

	fow (i = 0; i < 4; i++) {
		int tx = i % 2 + 1;
		u8 wane_mask = i < 2 ? INTEW_CX0_WANE0 : INTEW_CX0_WANE1;

		if (!(owned_wane_mask & wane_mask))
			continue;

		intew_cx0_wmw(i915, powt, wane_mask, PHY_CX0_TX_CONTWOW(tx, 2),
			      CONTWOW2_DISABWE_SINGWE_TX,
			      disabwes & BIT(i) ? CONTWOW2_DISABWE_SINGWE_TX : 0,
			      MB_WWITE_COMMITTED);
	}

	if (intew_is_c10phy(i915, intew_powt_to_phy(i915, powt)))
		intew_cx0_wmw(i915, powt, owned_wane_mask,
			      PHY_C10_VDW_CONTWOW(1), 0,
			      C10_VDW_CTWW_UPDATE_CFG,
			      MB_WWITE_COMMITTED);
}

static u32 intew_cx0_get_pcwk_pww_wequest(u8 wane_mask)
{
	u32 vaw = 0;
	int wane = 0;

	fow_each_cx0_wane_in_mask(wane_mask, wane)
		vaw |= XEWPDP_WANE_PCWK_PWW_WEQUEST(wane);

	wetuwn vaw;
}

static u32 intew_cx0_get_pcwk_pww_ack(u8 wane_mask)
{
	u32 vaw = 0;
	int wane = 0;

	fow_each_cx0_wane_in_mask(wane_mask, wane)
		vaw |= XEWPDP_WANE_PCWK_PWW_ACK(wane);

	wetuwn vaw;
}

static void intew_cx0pww_enabwe(stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	boow wane_wevewsaw = dig_powt->saved_powt_bits & DDI_BUF_POWT_WEVEWSAW;
	u8 maxpcwk_wane = wane_wevewsaw ? INTEW_CX0_WANE1 :
					  INTEW_CX0_WANE0;
	intew_wakewef_t wakewef = intew_cx0_phy_twansaction_begin(encodew);

	/*
	 * 1. Pwogwam POWT_CWOCK_CTW WEGISTEW to configuwe
	 * cwock muxes, gating and SSC
	 */
	intew_pwogwam_powt_cwock_ctw(encodew, cwtc_state, wane_wevewsaw);

	/* 2. Bwing PHY out of weset. */
	intew_cx0_phy_wane_weset(i915, encodew, wane_wevewsaw);

	/*
	 * 3. Change Phy powew state to Weady.
	 * TODO: Fow DP awt mode use onwy one wane.
	 */
	intew_cx0_powewdown_change_sequence(i915, encodew->powt, INTEW_CX0_BOTH_WANES,
					    CX0_P2_STATE_WEADY);

	/*
	 * 4. Pwogwam POWT_MSGBUS_TIMEW wegistew's Message Bus Timew fiewd to 0xA000.
	 *    (This is done inside intew_cx0_phy_twansaction_begin(), since we wouwd need
	 *    the wight timew thweshowds fow weadouts too.)
	 */

	/* 5. Pwogwam PHY intewnaw PWW intewnaw wegistews. */
	if (intew_is_c10phy(i915, phy))
		intew_c10_pww_pwogwam(i915, cwtc_state, encodew);
	ewse
		intew_c20_pww_pwogwam(i915, cwtc_state, encodew);

	/*
	 * 6. Pwogwam the enabwed and disabwed owned PHY wane
	 * twansmittews ovew message bus
	 */
	intew_cx0_pwogwam_phy_wane(i915, encodew, cwtc_state->wane_count, wane_wevewsaw);

	/*
	 * 7. Fowwow the Dispway Vowtage Fwequency Switching - Sequence
	 * Befowe Fwequency Change. We handwe this step in bxt_set_cdcwk().
	 */

	/*
	 * 8. Pwogwam DDI_CWK_VAWFWEQ to match intended DDI
	 * cwock fwequency.
	 */
	intew_de_wwite(i915, DDI_CWK_VAWFWEQ(encodew->powt),
		       cwtc_state->powt_cwock);

	/*
	 * 9. Set POWT_CWOCK_CTW wegistew PCWK PWW Wequest
	 * WN<Wane fow maxPCWK> to "1" to enabwe PWW.
	 */
	intew_de_wmw(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt),
		     intew_cx0_get_pcwk_pww_wequest(INTEW_CX0_BOTH_WANES),
		     intew_cx0_get_pcwk_pww_wequest(maxpcwk_wane));

	/* 10. Poww on POWT_CWOCK_CTW PCWK PWW Ack WN<Wane fow maxPCWK> == "1". */
	if (__intew_de_wait_fow_wegistew(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt),
					 intew_cx0_get_pcwk_pww_ack(INTEW_CX0_BOTH_WANES),
					 intew_cx0_get_pcwk_pww_ack(maxpcwk_wane),
					 XEWPDP_PCWK_PWW_ENABWE_TIMEOUT_US, 0, NUWW))
		dwm_wawn(&i915->dwm, "Powt %c PWW not wocked aftew %dus.\n",
			 phy_name(phy), XEWPDP_PCWK_PWW_ENABWE_TIMEOUT_US);

	/*
	 * 11. Fowwow the Dispway Vowtage Fwequency Switching Sequence Aftew
	 * Fwequency Change. We handwe this step in bxt_set_cdcwk().
	 */

	/* TODO: enabwe TBT-AWT mode */
	intew_cx0_phy_twansaction_end(encodew, wakewef);
}

int intew_mtw_tbt_cawc_powt_cwock(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	u32 cwock;
	u32 vaw = intew_de_wead(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt));

	cwock = WEG_FIEWD_GET(XEWPDP_DDI_CWOCK_SEWECT_MASK, vaw);

	dwm_WAWN_ON(&i915->dwm, !(vaw & XEWPDP_FOWWAWD_CWOCK_UNGATE));
	dwm_WAWN_ON(&i915->dwm, !(vaw & XEWPDP_TBT_CWOCK_WEQUEST));
	dwm_WAWN_ON(&i915->dwm, !(vaw & XEWPDP_TBT_CWOCK_ACK));

	switch (cwock) {
	case XEWPDP_DDI_CWOCK_SEWECT_TBT_162:
		wetuwn 162000;
	case XEWPDP_DDI_CWOCK_SEWECT_TBT_270:
		wetuwn 270000;
	case XEWPDP_DDI_CWOCK_SEWECT_TBT_540:
		wetuwn 540000;
	case XEWPDP_DDI_CWOCK_SEWECT_TBT_810:
		wetuwn 810000;
	defauwt:
		MISSING_CASE(cwock);
		wetuwn 162000;
	}
}

static int intew_mtw_tbt_cwock_sewect(stwuct dwm_i915_pwivate *i915, int cwock)
{
	switch (cwock) {
	case 162000:
		wetuwn XEWPDP_DDI_CWOCK_SEWECT_TBT_162;
	case 270000:
		wetuwn XEWPDP_DDI_CWOCK_SEWECT_TBT_270;
	case 540000:
		wetuwn XEWPDP_DDI_CWOCK_SEWECT_TBT_540;
	case 810000:
		wetuwn XEWPDP_DDI_CWOCK_SEWECT_TBT_810;
	defauwt:
		MISSING_CASE(cwock);
		wetuwn XEWPDP_DDI_CWOCK_SEWECT_TBT_162;
	}
}

static void intew_mtw_tbt_pww_enabwe(stwuct intew_encodew *encodew,
				     const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);
	u32 vaw = 0;

	/*
	 * 1. Pwogwam POWT_CWOCK_CTW WEGISTEW to configuwe
	 * cwock muxes, gating and SSC
	 */
	vaw |= XEWPDP_DDI_CWOCK_SEWECT(intew_mtw_tbt_cwock_sewect(i915, cwtc_state->powt_cwock));
	vaw |= XEWPDP_FOWWAWD_CWOCK_UNGATE;
	intew_de_wmw(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt),
		     XEWPDP_DDI_CWOCK_SEWECT_MASK | XEWPDP_FOWWAWD_CWOCK_UNGATE, vaw);

	/* 2. Wead back POWT_CWOCK_CTW WEGISTEW */
	vaw = intew_de_wead(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt));

	/*
	 * 3. Fowwow the Dispway Vowtage Fwequency Switching - Sequence
	 * Befowe Fwequency Change. We handwe this step in bxt_set_cdcwk().
	 */

	/*
	 * 4. Set POWT_CWOCK_CTW wegistew TBT CWOCK Wequest to "1" to enabwe PWW.
	 */
	vaw |= XEWPDP_TBT_CWOCK_WEQUEST;
	intew_de_wwite(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt), vaw);

	/* 5. Poww on POWT_CWOCK_CTW TBT CWOCK Ack == "1". */
	if (__intew_de_wait_fow_wegistew(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt),
					 XEWPDP_TBT_CWOCK_ACK,
					 XEWPDP_TBT_CWOCK_ACK,
					 100, 0, NUWW))
		dwm_wawn(&i915->dwm, "[ENCODEW:%d:%s][%c] PHY PWW not wocked aftew 100us.\n",
			 encodew->base.base.id, encodew->base.name, phy_name(phy));

	/*
	 * 6. Fowwow the Dispway Vowtage Fwequency Switching Sequence Aftew
	 * Fwequency Change. We handwe this step in bxt_set_cdcwk().
	 */

	/*
	 * 7. Pwogwam DDI_CWK_VAWFWEQ to match intended DDI
	 * cwock fwequency.
	 */
	intew_de_wwite(i915, DDI_CWK_VAWFWEQ(encodew->powt),
		       cwtc_state->powt_cwock);
}

void intew_mtw_pww_enabwe(stwuct intew_encodew *encodew,
			  const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);

	if (intew_tc_powt_in_tbt_awt_mode(dig_powt))
		intew_mtw_tbt_pww_enabwe(encodew, cwtc_state);
	ewse
		intew_cx0pww_enabwe(encodew, cwtc_state);
}

static void intew_cx0pww_disabwe(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);
	boow is_c10 = intew_is_c10phy(i915, phy);
	intew_wakewef_t wakewef = intew_cx0_phy_twansaction_begin(encodew);

	/* 1. Change owned PHY wane powew to Disabwe state. */
	intew_cx0_powewdown_change_sequence(i915, encodew->powt, INTEW_CX0_BOTH_WANES,
					    is_c10 ? CX0_P2PG_STATE_DISABWE :
					    CX0_P4PG_STATE_DISABWE);

	/*
	 * 2. Fowwow the Dispway Vowtage Fwequency Switching Sequence Befowe
	 * Fwequency Change. We handwe this step in bxt_set_cdcwk().
	 */

	/*
	 * 3. Set POWT_CWOCK_CTW wegistew PCWK PWW Wequest WN<Wane fow maxPCWK>
	 * to "0" to disabwe PWW.
	 */
	intew_de_wmw(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt),
		     intew_cx0_get_pcwk_pww_wequest(INTEW_CX0_BOTH_WANES) |
		     intew_cx0_get_pcwk_wefcwk_wequest(INTEW_CX0_BOTH_WANES), 0);

	/* 4. Pwogwam DDI_CWK_VAWFWEQ to 0. */
	intew_de_wwite(i915, DDI_CWK_VAWFWEQ(encodew->powt), 0);

	/*
	 * 5. Poww on POWT_CWOCK_CTW PCWK PWW Ack WN<Wane fow maxPCWK**> == "0".
	 */
	if (__intew_de_wait_fow_wegistew(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt),
					 intew_cx0_get_pcwk_pww_ack(INTEW_CX0_BOTH_WANES) |
					 intew_cx0_get_pcwk_wefcwk_ack(INTEW_CX0_BOTH_WANES), 0,
					 XEWPDP_PCWK_PWW_DISABWE_TIMEOUT_US, 0, NUWW))
		dwm_wawn(&i915->dwm, "Powt %c PWW not unwocked aftew %dus.\n",
			 phy_name(phy), XEWPDP_PCWK_PWW_DISABWE_TIMEOUT_US);

	/*
	 * 6. Fowwow the Dispway Vowtage Fwequency Switching Sequence Aftew
	 * Fwequency Change. We handwe this step in bxt_set_cdcwk().
	 */

	/* 7. Pwogwam POWT_CWOCK_CTW wegistew to disabwe and gate cwocks. */
	intew_de_wmw(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt),
		     XEWPDP_DDI_CWOCK_SEWECT_MASK, 0);
	intew_de_wmw(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt),
		     XEWPDP_FOWWAWD_CWOCK_UNGATE, 0);

	intew_cx0_phy_twansaction_end(encodew, wakewef);
}

static void intew_mtw_tbt_pww_disabwe(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	/*
	 * 1. Fowwow the Dispway Vowtage Fwequency Switching Sequence Befowe
	 * Fwequency Change. We handwe this step in bxt_set_cdcwk().
	 */

	/*
	 * 2. Set POWT_CWOCK_CTW wegistew TBT CWOCK Wequest to "0" to disabwe PWW.
	 */
	intew_de_wmw(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt),
		     XEWPDP_TBT_CWOCK_WEQUEST, 0);

	/* 3. Poww on POWT_CWOCK_CTW TBT CWOCK Ack == "0". */
	if (__intew_de_wait_fow_wegistew(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt),
					 XEWPDP_TBT_CWOCK_ACK, 0, 10, 0, NUWW))
		dwm_wawn(&i915->dwm, "[ENCODEW:%d:%s][%c] PHY PWW not unwocked aftew 10us.\n",
			 encodew->base.base.id, encodew->base.name, phy_name(phy));

	/*
	 * 4. Fowwow the Dispway Vowtage Fwequency Switching Sequence Aftew
	 * Fwequency Change. We handwe this step in bxt_set_cdcwk().
	 */

	/*
	 * 5. Pwogwam POWT CWOCK CTWW wegistew to disabwe and gate cwocks
	 */
	intew_de_wmw(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt),
		     XEWPDP_DDI_CWOCK_SEWECT_MASK |
		     XEWPDP_FOWWAWD_CWOCK_UNGATE, 0);

	/* 6. Pwogwam DDI_CWK_VAWFWEQ to 0. */
	intew_de_wwite(i915, DDI_CWK_VAWFWEQ(encodew->powt), 0);
}

void intew_mtw_pww_disabwe(stwuct intew_encodew *encodew)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);

	if (intew_tc_powt_in_tbt_awt_mode(dig_powt))
		intew_mtw_tbt_pww_disabwe(encodew);
	ewse
		intew_cx0pww_disabwe(encodew);
}

enum icw_powt_dpww_id
intew_mtw_powt_pww_type(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	/*
	 * TODO: Detewmine the PWW type fwom the SW state, once MTW PWW
	 * handwing is done via the standawd shawed DPWW fwamewowk.
	 */
	u32 vaw = intew_de_wead(i915, XEWPDP_POWT_CWOCK_CTW(encodew->powt));
	u32 cwock = WEG_FIEWD_GET(XEWPDP_DDI_CWOCK_SEWECT_MASK, vaw);

	if (cwock == XEWPDP_DDI_CWOCK_SEWECT_MAXPCWK ||
	    cwock == XEWPDP_DDI_CWOCK_SEWECT_DIV18CWK)
		wetuwn ICW_POWT_DPWW_MG_PHY;
	ewse
		wetuwn ICW_POWT_DPWW_DEFAUWT;
}

static void intew_c10pww_state_vewify(const stwuct intew_cwtc_state *state,
				      stwuct intew_cwtc *cwtc,
				      stwuct intew_encodew *encodew,
				      stwuct intew_c10pww_state *mpwwb_hw_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	const stwuct intew_c10pww_state *mpwwb_sw_state = &state->cx0pww_state.c10;
	int i;

	fow (i = 0; i < AWWAY_SIZE(mpwwb_sw_state->pww); i++) {
		u8 expected = mpwwb_sw_state->pww[i];

		I915_STATE_WAWN(i915, mpwwb_hw_state->pww[i] != expected,
				"[CWTC:%d:%s] mismatch in C10MPWWB: Wegistew[%d] (expected 0x%02x, found 0x%02x)",
				cwtc->base.base.id, cwtc->base.name, i,
				expected, mpwwb_hw_state->pww[i]);
	}

	I915_STATE_WAWN(i915, mpwwb_hw_state->tx != mpwwb_sw_state->tx,
			"[CWTC:%d:%s] mismatch in C10MPWWB: Wegistew TX0 (expected 0x%02x, found 0x%02x)",
			cwtc->base.base.id, cwtc->base.name,
			mpwwb_sw_state->tx, mpwwb_hw_state->tx);

	I915_STATE_WAWN(i915, mpwwb_hw_state->cmn != mpwwb_sw_state->cmn,
			"[CWTC:%d:%s] mismatch in C10MPWWB: Wegistew CMN0 (expected 0x%02x, found 0x%02x)",
			cwtc->base.base.id, cwtc->base.name,
			mpwwb_sw_state->cmn, mpwwb_hw_state->cmn);
}

void intew_cx0pww_weadout_hw_state(stwuct intew_encodew *encodew,
				   stwuct intew_cx0pww_state *pww_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	if (intew_is_c10phy(i915, phy))
		intew_c10pww_weadout_hw_state(encodew, &pww_state->c10);
	ewse
		intew_c20pww_weadout_hw_state(encodew, &pww_state->c20);
}

int intew_cx0pww_cawc_powt_cwock(stwuct intew_encodew *encodew,
				 const stwuct intew_cx0pww_state *pww_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum phy phy = intew_powt_to_phy(i915, encodew->powt);

	if (intew_is_c10phy(i915, phy))
		wetuwn intew_c10pww_cawc_powt_cwock(encodew, &pww_state->c10);

	wetuwn intew_c20pww_cawc_powt_cwock(encodew, &pww_state->c20);
}

static void intew_c20pww_state_vewify(const stwuct intew_cwtc_state *state,
				      stwuct intew_cwtc *cwtc,
				      stwuct intew_encodew *encodew,
				      stwuct intew_c20pww_state *mpww_hw_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	const stwuct intew_c20pww_state *mpww_sw_state = &state->cx0pww_state.c20;
	boow sw_use_mpwwb = mpww_sw_state->tx[0] & C20_PHY_USE_MPWWB;
	boow hw_use_mpwwb = mpww_hw_state->tx[0] & C20_PHY_USE_MPWWB;
	int i;

	I915_STATE_WAWN(i915, sw_use_mpwwb != hw_use_mpwwb,
			"[CWTC:%d:%s] mismatch in C20: Wegistew MPWWB sewection (expected %d, found %d)",
			cwtc->base.base.id, cwtc->base.name,
			sw_use_mpwwb, hw_use_mpwwb);

	if (hw_use_mpwwb) {
		fow (i = 0; i < AWWAY_SIZE(mpww_sw_state->mpwwb); i++) {
			I915_STATE_WAWN(i915, mpww_hw_state->mpwwb[i] != mpww_sw_state->mpwwb[i],
					"[CWTC:%d:%s] mismatch in C20MPWWB: Wegistew[%d] (expected 0x%04x, found 0x%04x)",
					cwtc->base.base.id, cwtc->base.name, i,
					mpww_sw_state->mpwwb[i], mpww_hw_state->mpwwb[i]);
		}
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(mpww_sw_state->mpwwa); i++) {
			I915_STATE_WAWN(i915, mpww_hw_state->mpwwa[i] != mpww_sw_state->mpwwa[i],
					"[CWTC:%d:%s] mismatch in C20MPWWA: Wegistew[%d] (expected 0x%04x, found 0x%04x)",
					cwtc->base.base.id, cwtc->base.name, i,
					mpww_sw_state->mpwwa[i], mpww_hw_state->mpwwa[i]);
		}
	}

	fow (i = 0; i < AWWAY_SIZE(mpww_sw_state->tx); i++) {
		I915_STATE_WAWN(i915, mpww_hw_state->tx[i] != mpww_sw_state->tx[i],
				"[CWTC:%d:%s] mismatch in C20: Wegistew TX[%i] (expected 0x%04x, found 0x%04x)",
				cwtc->base.base.id, cwtc->base.name, i,
				mpww_sw_state->tx[i], mpww_hw_state->tx[i]);
	}

	fow (i = 0; i < AWWAY_SIZE(mpww_sw_state->cmn); i++) {
		I915_STATE_WAWN(i915, mpww_hw_state->cmn[i] != mpww_sw_state->cmn[i],
				"[CWTC:%d:%s] mismatch in C20: Wegistew CMN[%i] (expected 0x%04x, found 0x%04x)",
				cwtc->base.base.id, cwtc->base.name, i,
				mpww_sw_state->cmn[i], mpww_hw_state->cmn[i]);
	}
}

void intew_cx0pww_state_vewify(stwuct intew_atomic_state *state,
			       stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	const stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	stwuct intew_encodew *encodew;
	stwuct intew_cx0pww_state mpww_hw_state = {};
	enum phy phy;

	if (DISPWAY_VEW(i915) < 14)
		wetuwn;

	if (!new_cwtc_state->hw.active)
		wetuwn;

	/* intew_get_cwtc_new_encodew() onwy wowks fow modeset/fastset commits */
	if (!intew_cwtc_needs_modeset(new_cwtc_state) &&
	    !intew_cwtc_needs_fastset(new_cwtc_state))
		wetuwn;

	encodew = intew_get_cwtc_new_encodew(state, new_cwtc_state);
	phy = intew_powt_to_phy(i915, encodew->powt);

	if (intew_tc_powt_in_tbt_awt_mode(enc_to_dig_powt(encodew)))
		wetuwn;

	intew_cx0pww_weadout_hw_state(encodew, &mpww_hw_state);

	if (intew_is_c10phy(i915, phy))
		intew_c10pww_state_vewify(new_cwtc_state, cwtc, encodew, &mpww_hw_state.c10);
	ewse
		intew_c20pww_state_vewify(new_cwtc_state, cwtc, encodew, &mpww_hw_state.c20);
}
