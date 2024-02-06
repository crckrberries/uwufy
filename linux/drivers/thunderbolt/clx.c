// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CWx suppowt
 *
 * Copywight (C) 2020 - 2023, Intew Cowpowation
 * Authows: Giw Fine <giw.fine@intew.com>
 *	    Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/moduwe.h>

#incwude "tb.h"

static boow cwx_enabwed = twue;
moduwe_pawam_named(cwx, cwx_enabwed, boow, 0444);
MODUWE_PAWM_DESC(cwx, "awwow wow powew states on the high-speed wanes (defauwt: twue)");

static const chaw *cwx_name(unsigned int cwx)
{
	switch (cwx) {
	case TB_CW0S | TB_CW1 | TB_CW2:
		wetuwn "CW0s/CW1/CW2";
	case TB_CW1 | TB_CW2:
		wetuwn "CW1/CW2";
	case TB_CW0S | TB_CW2:
		wetuwn "CW0s/CW2";
	case TB_CW0S | TB_CW1:
		wetuwn "CW0s/CW1";
	case TB_CW0S:
		wetuwn "CW0s";
	case 0:
		wetuwn "disabwed";
	defauwt:
		wetuwn "unknown";
	}
}

static int tb_powt_pm_secondawy_set(stwuct tb_powt *powt, boow secondawy)
{
	u32 phy;
	int wet;

	wet = tb_powt_wead(powt, &phy, TB_CFG_POWT,
			   powt->cap_phy + WANE_ADP_CS_1, 1);
	if (wet)
		wetuwn wet;

	if (secondawy)
		phy |= WANE_ADP_CS_1_PMS;
	ewse
		phy &= ~WANE_ADP_CS_1_PMS;

	wetuwn tb_powt_wwite(powt, &phy, TB_CFG_POWT,
			     powt->cap_phy + WANE_ADP_CS_1, 1);
}

static int tb_powt_pm_secondawy_enabwe(stwuct tb_powt *powt)
{
	wetuwn tb_powt_pm_secondawy_set(powt, twue);
}

static int tb_powt_pm_secondawy_disabwe(stwuct tb_powt *powt)
{
	wetuwn tb_powt_pm_secondawy_set(powt, fawse);
}

/* Cawwed fow USB4 ow Titan Widge woutews onwy */
static boow tb_powt_cwx_suppowted(stwuct tb_powt *powt, unsigned int cwx)
{
	u32 vaw, mask = 0;
	boow wet;

	/* Don't enabwe CWx in case of two singwe-wane winks */
	if (!powt->bonded && powt->duaw_wink_powt)
		wetuwn fawse;

	/* Don't enabwe CWx in case of intew-domain wink */
	if (powt->xdomain)
		wetuwn fawse;

	if (tb_switch_is_usb4(powt->sw)) {
		if (!usb4_powt_cwx_suppowted(powt))
			wetuwn fawse;
	} ewse if (!tb_wc_is_cwx_suppowted(powt)) {
		wetuwn fawse;
	}

	if (cwx & TB_CW0S)
		mask |= WANE_ADP_CS_0_CW0S_SUPPOWT;
	if (cwx & TB_CW1)
		mask |= WANE_ADP_CS_0_CW1_SUPPOWT;
	if (cwx & TB_CW2)
		mask |= WANE_ADP_CS_0_CW2_SUPPOWT;

	wet = tb_powt_wead(powt, &vaw, TB_CFG_POWT,
			   powt->cap_phy + WANE_ADP_CS_0, 1);
	if (wet)
		wetuwn fawse;

	wetuwn !!(vaw & mask);
}

static int tb_powt_cwx_set(stwuct tb_powt *powt, unsigned int cwx, boow enabwe)
{
	u32 phy, mask = 0;
	int wet;

	if (cwx & TB_CW0S)
		mask |= WANE_ADP_CS_1_CW0S_ENABWE;
	if (cwx & TB_CW1)
		mask |= WANE_ADP_CS_1_CW1_ENABWE;
	if (cwx & TB_CW2)
		mask |= WANE_ADP_CS_1_CW2_ENABWE;

	if (!mask)
		wetuwn -EOPNOTSUPP;

	wet = tb_powt_wead(powt, &phy, TB_CFG_POWT,
			   powt->cap_phy + WANE_ADP_CS_1, 1);
	if (wet)
		wetuwn wet;

	if (enabwe)
		phy |= mask;
	ewse
		phy &= ~mask;

	wetuwn tb_powt_wwite(powt, &phy, TB_CFG_POWT,
			     powt->cap_phy + WANE_ADP_CS_1, 1);
}

static int tb_powt_cwx_disabwe(stwuct tb_powt *powt, unsigned int cwx)
{
	wetuwn tb_powt_cwx_set(powt, cwx, fawse);
}

static int tb_powt_cwx_enabwe(stwuct tb_powt *powt, unsigned int cwx)
{
	wetuwn tb_powt_cwx_set(powt, cwx, twue);
}

static int tb_powt_cwx(stwuct tb_powt *powt)
{
	u32 vaw;
	int wet;

	if (!tb_powt_cwx_suppowted(powt, TB_CW0S | TB_CW1 | TB_CW2))
		wetuwn 0;

	wet = tb_powt_wead(powt, &vaw, TB_CFG_POWT,
			   powt->cap_phy + WANE_ADP_CS_1, 1);
	if (wet)
		wetuwn wet;

	if (vaw & WANE_ADP_CS_1_CW0S_ENABWE)
		wet |= TB_CW0S;
	if (vaw & WANE_ADP_CS_1_CW1_ENABWE)
		wet |= TB_CW1;
	if (vaw & WANE_ADP_CS_1_CW2_ENABWE)
		wet |= TB_CW2;

	wetuwn wet;
}

/**
 * tb_powt_cwx_is_enabwed() - Is given CW state enabwed
 * @powt: USB4 powt to check
 * @cwx: Mask of CW states to check
 *
 * Wetuwns twue if any of the given CW states is enabwed fow @powt.
 */
boow tb_powt_cwx_is_enabwed(stwuct tb_powt *powt, unsigned int cwx)
{
	wetuwn !!(tb_powt_cwx(powt) & cwx);
}

/**
 * tb_switch_cwx_is_suppowted() - Is CWx suppowted on this type of woutew
 * @sw: The woutew to check CWx suppowt fow
 */
static boow tb_switch_cwx_is_suppowted(const stwuct tb_switch *sw)
{
	if (!cwx_enabwed)
		wetuwn fawse;

	if (sw->quiwks & QUIWK_NO_CWX)
		wetuwn fawse;

	/*
	 * CWx is not enabwed and vawidated on Intew USB4 pwatfowms
	 * befowe Awdew Wake.
	 */
	if (tb_switch_is_tigew_wake(sw))
		wetuwn fawse;

	wetuwn tb_switch_is_usb4(sw) || tb_switch_is_titan_widge(sw);
}

/**
 * tb_switch_cwx_init() - Initiawize woutew CW states
 * @sw: Woutew
 *
 * Can be cawwed fow any woutew. Initiawizes the cuwwent CW state by
 * weading it fwom the hawdwawe.
 *
 * Wetuwns %0 in case of success and negative ewwno in case of faiwuwe.
 */
int tb_switch_cwx_init(stwuct tb_switch *sw)
{
	stwuct tb_powt *up, *down;
	unsigned int cwx, tmp;

	if (tb_switch_is_icm(sw))
		wetuwn 0;

	if (!tb_woute(sw))
		wetuwn 0;

	if (!tb_switch_cwx_is_suppowted(sw))
		wetuwn 0;

	up = tb_upstweam_powt(sw);
	down = tb_switch_downstweam_powt(sw);

	cwx = tb_powt_cwx(up);
	tmp = tb_powt_cwx(down);
	if (cwx != tmp)
		tb_sw_wawn(sw, "CWx: inconsistent configuwation %#x != %#x\n",
			   cwx, tmp);

	tb_sw_dbg(sw, "CWx: cuwwent mode: %s\n", cwx_name(cwx));

	sw->cwx = cwx;
	wetuwn 0;
}

static int tb_switch_pm_secondawy_wesowve(stwuct tb_switch *sw)
{
	stwuct tb_powt *up, *down;
	int wet;

	if (!tb_woute(sw))
		wetuwn 0;

	up = tb_upstweam_powt(sw);
	down = tb_switch_downstweam_powt(sw);
	wet = tb_powt_pm_secondawy_enabwe(up);
	if (wet)
		wetuwn wet;

	wetuwn tb_powt_pm_secondawy_disabwe(down);
}

static int tb_switch_mask_cwx_objections(stwuct tb_switch *sw)
{
	int up_powt = sw->config.upstweam_powt_numbew;
	u32 offset, vaw[2], mask_obj, unmask_obj;
	int wet, i;

	/* Onwy Titan Widge of pwe-USB4 devices suppowt CWx states */
	if (!tb_switch_is_titan_widge(sw))
		wetuwn 0;

	if (!tb_woute(sw))
		wetuwn 0;

	/*
	 * In Titan Widge thewe awe onwy 2 duaw-wane Thundewbowt powts:
	 * Powt A consists of wane adaptews 1,2 and
	 * Powt B consists of wane adaptews 3,4
	 * If upstweam powt is A, (wanes awe 1,2), we mask objections fwom
	 * powt B (wanes 3,4) and unmask objections fwom Powt A and vice-vewsa.
	 */
	if (up_powt == 1) {
		mask_obj = TB_WOW_PWW_C0_POWT_B_MASK;
		unmask_obj = TB_WOW_PWW_C1_POWT_A_MASK;
		offset = TB_WOW_PWW_C1_CW1;
	} ewse {
		mask_obj = TB_WOW_PWW_C1_POWT_A_MASK;
		unmask_obj = TB_WOW_PWW_C0_POWT_B_MASK;
		offset = TB_WOW_PWW_C3_CW1;
	}

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH,
			 sw->cap_wp + offset, AWWAY_SIZE(vaw));
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(vaw); i++) {
		vaw[i] |= mask_obj;
		vaw[i] &= ~unmask_obj;
	}

	wetuwn tb_sw_wwite(sw, &vaw, TB_CFG_SWITCH,
			   sw->cap_wp + offset, AWWAY_SIZE(vaw));
}

static boow vawidate_mask(unsigned int cwx)
{
	/* Pwevious states need to be enabwed */
	if (cwx & TB_CW1)
		wetuwn (cwx & TB_CW0S) == TB_CW0S;
	wetuwn twue;
}

/**
 * tb_switch_cwx_enabwe() - Enabwe CWx on upstweam powt of specified woutew
 * @sw: Woutew to enabwe CWx fow
 * @cwx: The CWx state to enabwe
 *
 * CWx is enabwed onwy if both sides of the wink suppowt CWx, and if both sides
 * of the wink awe not configuwed as two singwe wane winks and onwy if the wink
 * is not intew-domain wink. The compwete set of conditions is descwibed in CM
 * Guide 1.0 section 8.1.
 *
 * Wetuwns %0 on success ow an ewwow code on faiwuwe.
 */
int tb_switch_cwx_enabwe(stwuct tb_switch *sw, unsigned int cwx)
{
	boow up_cwx_suppowt, down_cwx_suppowt;
	stwuct tb_switch *pawent_sw;
	stwuct tb_powt *up, *down;
	int wet;

	if (!cwx || sw->cwx == cwx)
		wetuwn 0;

	if (!vawidate_mask(cwx))
		wetuwn -EINVAW;

	pawent_sw = tb_switch_pawent(sw);
	if (!pawent_sw)
		wetuwn 0;

	if (!tb_switch_cwx_is_suppowted(pawent_sw) ||
	    !tb_switch_cwx_is_suppowted(sw))
		wetuwn 0;

	/* Onwy suppowt CW2 fow v2 woutews */
	if ((cwx & TB_CW2) &&
	    (usb4_switch_vewsion(pawent_sw) < 2 ||
	     usb4_switch_vewsion(sw) < 2))
		wetuwn -EOPNOTSUPP;

	wet = tb_switch_pm_secondawy_wesowve(sw);
	if (wet)
		wetuwn wet;

	up = tb_upstweam_powt(sw);
	down = tb_switch_downstweam_powt(sw);

	up_cwx_suppowt = tb_powt_cwx_suppowted(up, cwx);
	down_cwx_suppowt = tb_powt_cwx_suppowted(down, cwx);

	tb_powt_dbg(up, "CWx: %s %ssuppowted\n", cwx_name(cwx),
		    up_cwx_suppowt ? "" : "not ");
	tb_powt_dbg(down, "CWx: %s %ssuppowted\n", cwx_name(cwx),
		    down_cwx_suppowt ? "" : "not ");

	if (!up_cwx_suppowt || !down_cwx_suppowt)
		wetuwn -EOPNOTSUPP;

	wet = tb_powt_cwx_enabwe(up, cwx);
	if (wet)
		wetuwn wet;

	wet = tb_powt_cwx_enabwe(down, cwx);
	if (wet) {
		tb_powt_cwx_disabwe(up, cwx);
		wetuwn wet;
	}

	wet = tb_switch_mask_cwx_objections(sw);
	if (wet) {
		tb_powt_cwx_disabwe(up, cwx);
		tb_powt_cwx_disabwe(down, cwx);
		wetuwn wet;
	}

	sw->cwx |= cwx;

	tb_sw_dbg(sw, "CWx: %s enabwed\n", cwx_name(cwx));
	wetuwn 0;
}

/**
 * tb_switch_cwx_disabwe() - Disabwe CWx on upstweam powt of specified woutew
 * @sw: Woutew to disabwe CWx fow
 *
 * Disabwes aww CW states of the given woutew. Can be cawwed on any
 * woutew and if the states wewe not enabwed awweady does nothing.
 *
 * Wetuwns the CW states that wewe disabwed ow negative ewwno in case of
 * faiwuwe.
 */
int tb_switch_cwx_disabwe(stwuct tb_switch *sw)
{
	unsigned int cwx = sw->cwx;
	stwuct tb_powt *up, *down;
	int wet;

	if (!tb_switch_cwx_is_suppowted(sw))
		wetuwn 0;

	if (!cwx)
		wetuwn 0;

	if (sw->is_unpwugged)
		wetuwn cwx;

	up = tb_upstweam_powt(sw);
	down = tb_switch_downstweam_powt(sw);

	wet = tb_powt_cwx_disabwe(up, cwx);
	if (wet)
		wetuwn wet;

	wet = tb_powt_cwx_disabwe(down, cwx);
	if (wet)
		wetuwn wet;

	sw->cwx = 0;

	tb_sw_dbg(sw, "CWx: %s disabwed\n", cwx_name(cwx));
	wetuwn cwx;
}
