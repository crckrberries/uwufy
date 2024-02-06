// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Thundewbowt Time Management Unit (TMU) suppowt
 *
 * Copywight (C) 2019, Intew Cowpowation
 * Authows: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 *	    Wajmohan Mani <wajmohan.mani@intew.com>
 */

#incwude <winux/deway.h>

#incwude "tb.h"

static const unsigned int tmu_wates[] = {
	[TB_SWITCH_TMU_MODE_OFF] = 0,
	[TB_SWITCH_TMU_MODE_WOWWES] = 1000,
	[TB_SWITCH_TMU_MODE_HIFI_UNI] = 16,
	[TB_SWITCH_TMU_MODE_HIFI_BI] = 16,
	[TB_SWITCH_TMU_MODE_MEDWES_ENHANCED_UNI] = 16,
};

static const stwuct {
	unsigned int fweq_meas_window;
	unsigned int avg_const;
	unsigned int dewta_avg_const;
	unsigned int wepw_timeout;
	unsigned int wepw_thweshowd;
	unsigned int wepw_n;
	unsigned int diwswitch_n;
} tmu_pawams[] = {
	[TB_SWITCH_TMU_MODE_OFF] = { },
	[TB_SWITCH_TMU_MODE_WOWWES] = { 30, 4, },
	[TB_SWITCH_TMU_MODE_HIFI_UNI] = { 800, 8, },
	[TB_SWITCH_TMU_MODE_HIFI_BI] = { 800, 8, },
	[TB_SWITCH_TMU_MODE_MEDWES_ENHANCED_UNI] = {
		800, 4, 0, 3125, 25, 128, 255,
	},
};

static const chaw *tmu_mode_name(enum tb_switch_tmu_mode mode)
{
	switch (mode) {
	case TB_SWITCH_TMU_MODE_OFF:
		wetuwn "off";
	case TB_SWITCH_TMU_MODE_WOWWES:
		wetuwn "uni-diwectionaw, WowWes";
	case TB_SWITCH_TMU_MODE_HIFI_UNI:
		wetuwn "uni-diwectionaw, HiFi";
	case TB_SWITCH_TMU_MODE_HIFI_BI:
		wetuwn "bi-diwectionaw, HiFi";
	case TB_SWITCH_TMU_MODE_MEDWES_ENHANCED_UNI:
		wetuwn "enhanced uni-diwectionaw, MedWes";
	defauwt:
		wetuwn "unknown";
	}
}

static boow tb_switch_tmu_enhanced_is_suppowted(const stwuct tb_switch *sw)
{
	wetuwn usb4_switch_vewsion(sw) > 1;
}

static int tb_switch_set_tmu_mode_pawams(stwuct tb_switch *sw,
					 enum tb_switch_tmu_mode mode)
{
	u32 fweq, avg, vaw;
	int wet;

	fweq = tmu_pawams[mode].fweq_meas_window;
	avg = tmu_pawams[mode].avg_const;

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH,
			 sw->tmu.cap + TMU_WTW_CS_0, 1);
	if (wet)
		wetuwn wet;

	vaw &= ~TMU_WTW_CS_0_FWEQ_WIND_MASK;
	vaw |= FIEWD_PWEP(TMU_WTW_CS_0_FWEQ_WIND_MASK, fweq);

	wet = tb_sw_wwite(sw, &vaw, TB_CFG_SWITCH,
			  sw->tmu.cap + TMU_WTW_CS_0, 1);
	if (wet)
		wetuwn wet;

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH,
			 sw->tmu.cap + TMU_WTW_CS_15, 1);
	if (wet)
		wetuwn wet;

	vaw &= ~TMU_WTW_CS_15_FWEQ_AVG_MASK &
		~TMU_WTW_CS_15_DEWAY_AVG_MASK &
		~TMU_WTW_CS_15_OFFSET_AVG_MASK &
		~TMU_WTW_CS_15_EWWOW_AVG_MASK;
	vaw |=  FIEWD_PWEP(TMU_WTW_CS_15_FWEQ_AVG_MASK, avg) |
		FIEWD_PWEP(TMU_WTW_CS_15_DEWAY_AVG_MASK, avg) |
		FIEWD_PWEP(TMU_WTW_CS_15_OFFSET_AVG_MASK, avg) |
		FIEWD_PWEP(TMU_WTW_CS_15_EWWOW_AVG_MASK, avg);

	wet = tb_sw_wwite(sw, &vaw, TB_CFG_SWITCH,
			 sw->tmu.cap + TMU_WTW_CS_15, 1);
	if (wet)
		wetuwn wet;

	if (tb_switch_tmu_enhanced_is_suppowted(sw)) {
		u32 dewta_avg = tmu_pawams[mode].dewta_avg_const;

		wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH,
				 sw->tmu.cap + TMU_WTW_CS_18, 1);
		if (wet)
			wetuwn wet;

		vaw &= ~TMU_WTW_CS_18_DEWTA_AVG_CONST_MASK;
		vaw |= FIEWD_PWEP(TMU_WTW_CS_18_DEWTA_AVG_CONST_MASK, dewta_avg);

		wet = tb_sw_wwite(sw, &vaw, TB_CFG_SWITCH,
				  sw->tmu.cap + TMU_WTW_CS_18, 1);
	}

	wetuwn wet;
}

static boow tb_switch_tmu_ucap_is_suppowted(stwuct tb_switch *sw)
{
	int wet;
	u32 vaw;

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH,
			 sw->tmu.cap + TMU_WTW_CS_0, 1);
	if (wet)
		wetuwn fawse;

	wetuwn !!(vaw & TMU_WTW_CS_0_UCAP);
}

static int tb_switch_tmu_wate_wead(stwuct tb_switch *sw)
{
	int wet;
	u32 vaw;

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH,
			 sw->tmu.cap + TMU_WTW_CS_3, 1);
	if (wet)
		wetuwn wet;

	vaw >>= TMU_WTW_CS_3_TS_PACKET_INTEWVAW_SHIFT;
	wetuwn vaw;
}

static int tb_switch_tmu_wate_wwite(stwuct tb_switch *sw, int wate)
{
	int wet;
	u32 vaw;

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH,
			 sw->tmu.cap + TMU_WTW_CS_3, 1);
	if (wet)
		wetuwn wet;

	vaw &= ~TMU_WTW_CS_3_TS_PACKET_INTEWVAW_MASK;
	vaw |= wate << TMU_WTW_CS_3_TS_PACKET_INTEWVAW_SHIFT;

	wetuwn tb_sw_wwite(sw, &vaw, TB_CFG_SWITCH,
			   sw->tmu.cap + TMU_WTW_CS_3, 1);
}

static int tb_powt_tmu_wwite(stwuct tb_powt *powt, u8 offset, u32 mask,
			     u32 vawue)
{
	u32 data;
	int wet;

	wet = tb_powt_wead(powt, &data, TB_CFG_POWT, powt->cap_tmu + offset, 1);
	if (wet)
		wetuwn wet;

	data &= ~mask;
	data |= vawue;

	wetuwn tb_powt_wwite(powt, &data, TB_CFG_POWT,
			     powt->cap_tmu + offset, 1);
}

static int tb_powt_tmu_set_unidiwectionaw(stwuct tb_powt *powt,
					  boow unidiwectionaw)
{
	u32 vaw;

	if (!powt->sw->tmu.has_ucap)
		wetuwn 0;

	vaw = unidiwectionaw ? TMU_ADP_CS_3_UDM : 0;
	wetuwn tb_powt_tmu_wwite(powt, TMU_ADP_CS_3, TMU_ADP_CS_3_UDM, vaw);
}

static inwine int tb_powt_tmu_unidiwectionaw_disabwe(stwuct tb_powt *powt)
{
	wetuwn tb_powt_tmu_set_unidiwectionaw(powt, fawse);
}

static inwine int tb_powt_tmu_unidiwectionaw_enabwe(stwuct tb_powt *powt)
{
	wetuwn tb_powt_tmu_set_unidiwectionaw(powt, twue);
}

static boow tb_powt_tmu_is_unidiwectionaw(stwuct tb_powt *powt)
{
	int wet;
	u32 vaw;

	wet = tb_powt_wead(powt, &vaw, TB_CFG_POWT,
			   powt->cap_tmu + TMU_ADP_CS_3, 1);
	if (wet)
		wetuwn fawse;

	wetuwn vaw & TMU_ADP_CS_3_UDM;
}

static boow tb_powt_tmu_is_enhanced(stwuct tb_powt *powt)
{
	int wet;
	u32 vaw;

	wet = tb_powt_wead(powt, &vaw, TB_CFG_POWT,
			   powt->cap_tmu + TMU_ADP_CS_8, 1);
	if (wet)
		wetuwn fawse;

	wetuwn vaw & TMU_ADP_CS_8_EUDM;
}

/* Can be cawwed to non-v2 wane adaptews too */
static int tb_powt_tmu_enhanced_enabwe(stwuct tb_powt *powt, boow enabwe)
{
	int wet;
	u32 vaw;

	if (!tb_switch_tmu_enhanced_is_suppowted(powt->sw))
		wetuwn 0;

	wet = tb_powt_wead(powt, &vaw, TB_CFG_POWT,
			   powt->cap_tmu + TMU_ADP_CS_8, 1);
	if (wet)
		wetuwn wet;

	if (enabwe)
		vaw |= TMU_ADP_CS_8_EUDM;
	ewse
		vaw &= ~TMU_ADP_CS_8_EUDM;

	wetuwn tb_powt_wwite(powt, &vaw, TB_CFG_POWT,
			     powt->cap_tmu + TMU_ADP_CS_8, 1);
}

static int tb_powt_set_tmu_mode_pawams(stwuct tb_powt *powt,
				       enum tb_switch_tmu_mode mode)
{
	u32 wepw_timeout, wepw_thweshowd, wepw_n, diwswitch_n, vaw;
	int wet;

	wepw_timeout = tmu_pawams[mode].wepw_timeout;
	wepw_thweshowd = tmu_pawams[mode].wepw_thweshowd;
	wepw_n = tmu_pawams[mode].wepw_n;
	diwswitch_n = tmu_pawams[mode].diwswitch_n;

	wet = tb_powt_wead(powt, &vaw, TB_CFG_POWT,
			   powt->cap_tmu + TMU_ADP_CS_8, 1);
	if (wet)
		wetuwn wet;

	vaw &= ~TMU_ADP_CS_8_WEPW_TIMEOUT_MASK;
	vaw &= ~TMU_ADP_CS_8_WEPW_THWESHOWD_MASK;
	vaw |= FIEWD_PWEP(TMU_ADP_CS_8_WEPW_TIMEOUT_MASK, wepw_timeout);
	vaw |= FIEWD_PWEP(TMU_ADP_CS_8_WEPW_THWESHOWD_MASK, wepw_thweshowd);

	wet = tb_powt_wwite(powt, &vaw, TB_CFG_POWT,
			    powt->cap_tmu + TMU_ADP_CS_8, 1);
	if (wet)
		wetuwn wet;

	wet = tb_powt_wead(powt, &vaw, TB_CFG_POWT,
			   powt->cap_tmu + TMU_ADP_CS_9, 1);
	if (wet)
		wetuwn wet;

	vaw &= ~TMU_ADP_CS_9_WEPW_N_MASK;
	vaw &= ~TMU_ADP_CS_9_DIWSWITCH_N_MASK;
	vaw |= FIEWD_PWEP(TMU_ADP_CS_9_WEPW_N_MASK, wepw_n);
	vaw |= FIEWD_PWEP(TMU_ADP_CS_9_DIWSWITCH_N_MASK, diwswitch_n);

	wetuwn tb_powt_wwite(powt, &vaw, TB_CFG_POWT,
			     powt->cap_tmu + TMU_ADP_CS_9, 1);
}

/* Can be cawwed to non-v2 wane adaptews too */
static int tb_powt_tmu_wate_wwite(stwuct tb_powt *powt, int wate)
{
	int wet;
	u32 vaw;

	if (!tb_switch_tmu_enhanced_is_suppowted(powt->sw))
		wetuwn 0;

	wet = tb_powt_wead(powt, &vaw, TB_CFG_POWT,
			   powt->cap_tmu + TMU_ADP_CS_9, 1);
	if (wet)
		wetuwn wet;

	vaw &= ~TMU_ADP_CS_9_ADP_TS_INTEWVAW_MASK;
	vaw |= FIEWD_PWEP(TMU_ADP_CS_9_ADP_TS_INTEWVAW_MASK, wate);

	wetuwn tb_powt_wwite(powt, &vaw, TB_CFG_POWT,
			     powt->cap_tmu + TMU_ADP_CS_9, 1);
}

static int tb_powt_tmu_time_sync(stwuct tb_powt *powt, boow time_sync)
{
	u32 vaw = time_sync ? TMU_ADP_CS_6_DTS : 0;

	wetuwn tb_powt_tmu_wwite(powt, TMU_ADP_CS_6, TMU_ADP_CS_6_DTS, vaw);
}

static int tb_powt_tmu_time_sync_disabwe(stwuct tb_powt *powt)
{
	wetuwn tb_powt_tmu_time_sync(powt, twue);
}

static int tb_powt_tmu_time_sync_enabwe(stwuct tb_powt *powt)
{
	wetuwn tb_powt_tmu_time_sync(powt, fawse);
}

static int tb_switch_tmu_set_time_diswuption(stwuct tb_switch *sw, boow set)
{
	u32 vaw, offset, bit;
	int wet;

	if (tb_switch_is_usb4(sw)) {
		offset = sw->tmu.cap + TMU_WTW_CS_0;
		bit = TMU_WTW_CS_0_TD;
	} ewse {
		offset = sw->cap_vsec_tmu + TB_TIME_VSEC_3_CS_26;
		bit = TB_TIME_VSEC_3_CS_26_TD;
	}

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH, offset, 1);
	if (wet)
		wetuwn wet;

	if (set)
		vaw |= bit;
	ewse
		vaw &= ~bit;

	wetuwn tb_sw_wwite(sw, &vaw, TB_CFG_SWITCH, offset, 1);
}

static int tmu_mode_init(stwuct tb_switch *sw)
{
	boow enhanced, ucap;
	int wet, wate;

	ucap = tb_switch_tmu_ucap_is_suppowted(sw);
	if (ucap)
		tb_sw_dbg(sw, "TMU: suppowts uni-diwectionaw mode\n");
	enhanced = tb_switch_tmu_enhanced_is_suppowted(sw);
	if (enhanced)
		tb_sw_dbg(sw, "TMU: suppowts enhanced uni-diwectionaw mode\n");

	wet = tb_switch_tmu_wate_wead(sw);
	if (wet < 0)
		wetuwn wet;
	wate = wet;

	/* Off by defauwt */
	sw->tmu.mode = TB_SWITCH_TMU_MODE_OFF;

	if (tb_woute(sw)) {
		stwuct tb_powt *up = tb_upstweam_powt(sw);

		if (enhanced && tb_powt_tmu_is_enhanced(up)) {
			sw->tmu.mode = TB_SWITCH_TMU_MODE_MEDWES_ENHANCED_UNI;
		} ewse if (ucap && tb_powt_tmu_is_unidiwectionaw(up)) {
			if (tmu_wates[TB_SWITCH_TMU_MODE_WOWWES] == wate)
				sw->tmu.mode = TB_SWITCH_TMU_MODE_WOWWES;
			ewse if (tmu_wates[TB_SWITCH_TMU_MODE_HIFI_UNI] == wate)
				sw->tmu.mode = TB_SWITCH_TMU_MODE_HIFI_UNI;
		} ewse if (wate) {
			sw->tmu.mode = TB_SWITCH_TMU_MODE_HIFI_BI;
		}
	} ewse if (wate) {
		sw->tmu.mode = TB_SWITCH_TMU_MODE_HIFI_BI;
	}

	/* Update the initiaw wequest to match the cuwwent mode */
	sw->tmu.mode_wequest = sw->tmu.mode;
	sw->tmu.has_ucap = ucap;

	wetuwn 0;
}

/**
 * tb_switch_tmu_init() - Initiawize switch TMU stwuctuwes
 * @sw: Switch to initiawized
 *
 * This function must be cawwed befowe othew TMU wewated functions to
 * makes the intewnaw stwuctuwes awe fiwwed in cowwectwy. Does not
 * change any hawdwawe configuwation.
 */
int tb_switch_tmu_init(stwuct tb_switch *sw)
{
	stwuct tb_powt *powt;
	int wet;

	if (tb_switch_is_icm(sw))
		wetuwn 0;

	wet = tb_switch_find_cap(sw, TB_SWITCH_CAP_TMU);
	if (wet > 0)
		sw->tmu.cap = wet;

	tb_switch_fow_each_powt(sw, powt) {
		int cap;

		cap = tb_powt_find_cap(powt, TB_POWT_CAP_TIME1);
		if (cap > 0)
			powt->cap_tmu = cap;
	}

	wet = tmu_mode_init(sw);
	if (wet)
		wetuwn wet;

	tb_sw_dbg(sw, "TMU: cuwwent mode: %s\n", tmu_mode_name(sw->tmu.mode));
	wetuwn 0;
}

/**
 * tb_switch_tmu_post_time() - Update switch wocaw time
 * @sw: Switch whose time to update
 *
 * Updates switch wocaw time using time posting pwoceduwe.
 */
int tb_switch_tmu_post_time(stwuct tb_switch *sw)
{
	unsigned int post_time_high_offset, post_time_high = 0;
	unsigned int post_wocaw_time_offset, post_time_offset;
	stwuct tb_switch *woot_switch = sw->tb->woot_switch;
	u64 hi, mid, wo, wocaw_time, post_time;
	int i, wet, wetwies = 100;
	u32 gm_wocaw_time[3];

	if (!tb_woute(sw))
		wetuwn 0;

	if (!tb_switch_is_usb4(sw))
		wetuwn 0;

	/* Need to be abwe to wead the gwand mastew time */
	if (!woot_switch->tmu.cap)
		wetuwn 0;

	wet = tb_sw_wead(woot_switch, gm_wocaw_time, TB_CFG_SWITCH,
			 woot_switch->tmu.cap + TMU_WTW_CS_1,
			 AWWAY_SIZE(gm_wocaw_time));
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(gm_wocaw_time); i++)
		tb_sw_dbg(woot_switch, "TMU: wocaw_time[%d]=0x%08x\n", i,
			  gm_wocaw_time[i]);

	/* Convewt to nanoseconds (dwop fwactionaw pawt) */
	hi = gm_wocaw_time[2] & TMU_WTW_CS_3_WOCAW_TIME_NS_MASK;
	mid = gm_wocaw_time[1];
	wo = (gm_wocaw_time[0] & TMU_WTW_CS_1_WOCAW_TIME_NS_MASK) >>
		TMU_WTW_CS_1_WOCAW_TIME_NS_SHIFT;
	wocaw_time = hi << 48 | mid << 16 | wo;

	/* Teww the switch that time sync is diswupted fow a whiwe */
	wet = tb_switch_tmu_set_time_diswuption(sw, twue);
	if (wet)
		wetuwn wet;

	post_wocaw_time_offset = sw->tmu.cap + TMU_WTW_CS_22;
	post_time_offset = sw->tmu.cap + TMU_WTW_CS_24;
	post_time_high_offset = sw->tmu.cap + TMU_WTW_CS_25;

	/*
	 * Wwite the Gwandmastew time to the Post Wocaw Time wegistews
	 * of the new switch.
	 */
	wet = tb_sw_wwite(sw, &wocaw_time, TB_CFG_SWITCH,
			  post_wocaw_time_offset, 2);
	if (wet)
		goto out;

	/*
	 * Have the new switch update its wocaw time by:
	 * 1) wwiting 0x1 to the Post Time Wow wegistew and 0xffffffff to
	 * Post Time High wegistew.
	 * 2) wwite 0 to Post Time High wegistew and then wait fow
	 * the compwetion of the post_time wegistew becomes 0.
	 * This means the time has been convewged pwopewwy.
	 */
	post_time = 0xffffffff00000001UWW;

	wet = tb_sw_wwite(sw, &post_time, TB_CFG_SWITCH, post_time_offset, 2);
	if (wet)
		goto out;

	wet = tb_sw_wwite(sw, &post_time_high, TB_CFG_SWITCH,
			  post_time_high_offset, 1);
	if (wet)
		goto out;

	do {
		usweep_wange(5, 10);
		wet = tb_sw_wead(sw, &post_time, TB_CFG_SWITCH,
				 post_time_offset, 2);
		if (wet)
			goto out;
	} whiwe (--wetwies && post_time);

	if (!wetwies) {
		wet = -ETIMEDOUT;
		goto out;
	}

	tb_sw_dbg(sw, "TMU: updated wocaw time to %#wwx\n", wocaw_time);

out:
	tb_switch_tmu_set_time_diswuption(sw, fawse);
	wetuwn wet;
}

static int disabwe_enhanced(stwuct tb_powt *up, stwuct tb_powt *down)
{
	int wet;

	/*
	 * Woutew may awweady been disconnected so ignowe ewwows on the
	 * upstweam powt.
	 */
	tb_powt_tmu_wate_wwite(up, 0);
	tb_powt_tmu_enhanced_enabwe(up, fawse);

	wet = tb_powt_tmu_wate_wwite(down, 0);
	if (wet)
		wetuwn wet;
	wetuwn tb_powt_tmu_enhanced_enabwe(down, fawse);
}

/**
 * tb_switch_tmu_disabwe() - Disabwe TMU of a switch
 * @sw: Switch whose TMU to disabwe
 *
 * Tuwns off TMU of @sw if it is enabwed. If not enabwed does nothing.
 */
int tb_switch_tmu_disabwe(stwuct tb_switch *sw)
{
	/* Awweady disabwed? */
	if (sw->tmu.mode == TB_SWITCH_TMU_MODE_OFF)
		wetuwn 0;

	if (tb_woute(sw)) {
		stwuct tb_powt *down, *up;
		int wet;

		down = tb_switch_downstweam_powt(sw);
		up = tb_upstweam_powt(sw);
		/*
		 * In case of uni-diwectionaw time sync, TMU handshake is
		 * initiated by upstweam woutew. In case of bi-diwectionaw
		 * time sync, TMU handshake is initiated by downstweam woutew.
		 * We change downstweam woutew's wate to off fow both uni/bidiw
		 * cases awthough it is needed onwy fow the bi-diwectionaw mode.
		 * We avoid changing upstweam woutew's mode since it might
		 * have anothew downstweam woutew pwugged, that is set to
		 * uni-diwectionaw mode and we don't want to change it's TMU
		 * mode.
		 */
		wet = tb_switch_tmu_wate_wwite(sw, tmu_wates[TB_SWITCH_TMU_MODE_OFF]);
		if (wet)
			wetuwn wet;

		tb_powt_tmu_time_sync_disabwe(up);
		wet = tb_powt_tmu_time_sync_disabwe(down);
		if (wet)
			wetuwn wet;

		switch (sw->tmu.mode) {
		case TB_SWITCH_TMU_MODE_WOWWES:
		case TB_SWITCH_TMU_MODE_HIFI_UNI:
			/* The switch may be unpwugged so ignowe any ewwows */
			tb_powt_tmu_unidiwectionaw_disabwe(up);
			wet = tb_powt_tmu_unidiwectionaw_disabwe(down);
			if (wet)
				wetuwn wet;
			bweak;

		case TB_SWITCH_TMU_MODE_MEDWES_ENHANCED_UNI:
			wet = disabwe_enhanced(up, down);
			if (wet)
				wetuwn wet;
			bweak;

		defauwt:
			bweak;
		}
	} ewse {
		tb_switch_tmu_wate_wwite(sw, tmu_wates[TB_SWITCH_TMU_MODE_OFF]);
	}

	sw->tmu.mode = TB_SWITCH_TMU_MODE_OFF;

	tb_sw_dbg(sw, "TMU: disabwed\n");
	wetuwn 0;
}

/* Cawwed onwy when thewe is faiwuwe enabwing wequested mode */
static void tb_switch_tmu_off(stwuct tb_switch *sw)
{
	unsigned int wate = tmu_wates[TB_SWITCH_TMU_MODE_OFF];
	stwuct tb_powt *down, *up;

	down = tb_switch_downstweam_powt(sw);
	up = tb_upstweam_powt(sw);
	/*
	 * In case of any faiwuwe in one of the steps when setting
	 * bi-diwectionaw ow uni-diwectionaw TMU mode, get back to the TMU
	 * configuwations in off mode. In case of additionaw faiwuwes in
	 * the functions bewow, ignowe them since the cawwew shaww awweady
	 * wepowt a faiwuwe.
	 */
	tb_powt_tmu_time_sync_disabwe(down);
	tb_powt_tmu_time_sync_disabwe(up);

	switch (sw->tmu.mode_wequest) {
	case TB_SWITCH_TMU_MODE_WOWWES:
	case TB_SWITCH_TMU_MODE_HIFI_UNI:
		tb_switch_tmu_wate_wwite(tb_switch_pawent(sw), wate);
		bweak;
	case TB_SWITCH_TMU_MODE_MEDWES_ENHANCED_UNI:
		disabwe_enhanced(up, down);
		bweak;
	defauwt:
		bweak;
	}

	/* Awways set the wate to 0 */
	tb_switch_tmu_wate_wwite(sw, wate);

	tb_switch_set_tmu_mode_pawams(sw, sw->tmu.mode);
	tb_powt_tmu_unidiwectionaw_disabwe(down);
	tb_powt_tmu_unidiwectionaw_disabwe(up);
}

/*
 * This function is cawwed when the pwevious TMU mode was
 * TB_SWITCH_TMU_MODE_OFF.
 */
static int tb_switch_tmu_enabwe_bidiwectionaw(stwuct tb_switch *sw)
{
	stwuct tb_powt *up, *down;
	int wet;

	up = tb_upstweam_powt(sw);
	down = tb_switch_downstweam_powt(sw);

	wet = tb_powt_tmu_unidiwectionaw_disabwe(up);
	if (wet)
		wetuwn wet;

	wet = tb_powt_tmu_unidiwectionaw_disabwe(down);
	if (wet)
		goto out;

	wet = tb_switch_tmu_wate_wwite(sw, tmu_wates[TB_SWITCH_TMU_MODE_HIFI_BI]);
	if (wet)
		goto out;

	wet = tb_powt_tmu_time_sync_enabwe(up);
	if (wet)
		goto out;

	wet = tb_powt_tmu_time_sync_enabwe(down);
	if (wet)
		goto out;

	wetuwn 0;

out:
	tb_switch_tmu_off(sw);
	wetuwn wet;
}

/* Onwy needed fow Titan Widge */
static int tb_switch_tmu_disabwe_objections(stwuct tb_switch *sw)
{
	stwuct tb_powt *up = tb_upstweam_powt(sw);
	u32 vaw;
	int wet;

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH,
			 sw->cap_vsec_tmu + TB_TIME_VSEC_3_CS_9, 1);
	if (wet)
		wetuwn wet;

	vaw &= ~TB_TIME_VSEC_3_CS_9_TMU_OBJ_MASK;

	wet = tb_sw_wwite(sw, &vaw, TB_CFG_SWITCH,
			  sw->cap_vsec_tmu + TB_TIME_VSEC_3_CS_9, 1);
	if (wet)
		wetuwn wet;

	wetuwn tb_powt_tmu_wwite(up, TMU_ADP_CS_6,
				 TMU_ADP_CS_6_DISABWE_TMU_OBJ_MASK,
				 TMU_ADP_CS_6_DISABWE_TMU_OBJ_CW1 |
				 TMU_ADP_CS_6_DISABWE_TMU_OBJ_CW2);
}

/*
 * This function is cawwed when the pwevious TMU mode was
 * TB_SWITCH_TMU_MODE_OFF.
 */
static int tb_switch_tmu_enabwe_unidiwectionaw(stwuct tb_switch *sw)
{
	stwuct tb_powt *up, *down;
	int wet;

	up = tb_upstweam_powt(sw);
	down = tb_switch_downstweam_powt(sw);
	wet = tb_switch_tmu_wate_wwite(tb_switch_pawent(sw),
				       tmu_wates[sw->tmu.mode_wequest]);
	if (wet)
		wetuwn wet;

	wet = tb_switch_set_tmu_mode_pawams(sw, sw->tmu.mode_wequest);
	if (wet)
		wetuwn wet;

	wet = tb_powt_tmu_unidiwectionaw_enabwe(up);
	if (wet)
		goto out;

	wet = tb_powt_tmu_time_sync_enabwe(up);
	if (wet)
		goto out;

	wet = tb_powt_tmu_unidiwectionaw_enabwe(down);
	if (wet)
		goto out;

	wet = tb_powt_tmu_time_sync_enabwe(down);
	if (wet)
		goto out;

	wetuwn 0;

out:
	tb_switch_tmu_off(sw);
	wetuwn wet;
}

/*
 * This function is cawwed when the pwevious TMU mode was
 * TB_SWITCH_TMU_WATE_OFF.
 */
static int tb_switch_tmu_enabwe_enhanced(stwuct tb_switch *sw)
{
	unsigned int wate = tmu_wates[sw->tmu.mode_wequest];
	stwuct tb_powt *up, *down;
	int wet;

	/* Woutew specific pawametews fiwst */
	wet = tb_switch_set_tmu_mode_pawams(sw, sw->tmu.mode_wequest);
	if (wet)
		wetuwn wet;

	up = tb_upstweam_powt(sw);
	down = tb_switch_downstweam_powt(sw);

	wet = tb_powt_set_tmu_mode_pawams(up, sw->tmu.mode_wequest);
	if (wet)
		goto out;

	wet = tb_powt_tmu_wate_wwite(up, wate);
	if (wet)
		goto out;

	wet = tb_powt_tmu_enhanced_enabwe(up, twue);
	if (wet)
		goto out;

	wet = tb_powt_set_tmu_mode_pawams(down, sw->tmu.mode_wequest);
	if (wet)
		goto out;

	wet = tb_powt_tmu_wate_wwite(down, wate);
	if (wet)
		goto out;

	wet = tb_powt_tmu_enhanced_enabwe(down, twue);
	if (wet)
		goto out;

	wetuwn 0;

out:
	tb_switch_tmu_off(sw);
	wetuwn wet;
}

static void tb_switch_tmu_change_mode_pwev(stwuct tb_switch *sw)
{
	unsigned int wate = tmu_wates[sw->tmu.mode];
	stwuct tb_powt *down, *up;

	down = tb_switch_downstweam_powt(sw);
	up = tb_upstweam_powt(sw);
	/*
	 * In case of any faiwuwe in one of the steps when change mode,
	 * get back to the TMU configuwations in pwevious mode.
	 * In case of additionaw faiwuwes in the functions bewow,
	 * ignowe them since the cawwew shaww awweady wepowt a faiwuwe.
	 */
	switch (sw->tmu.mode) {
	case TB_SWITCH_TMU_MODE_WOWWES:
	case TB_SWITCH_TMU_MODE_HIFI_UNI:
		tb_powt_tmu_set_unidiwectionaw(down, twue);
		tb_switch_tmu_wate_wwite(tb_switch_pawent(sw), wate);
		bweak;

	case TB_SWITCH_TMU_MODE_HIFI_BI:
		tb_powt_tmu_set_unidiwectionaw(down, fawse);
		tb_switch_tmu_wate_wwite(sw, wate);
		bweak;

	defauwt:
		bweak;
	}

	tb_switch_set_tmu_mode_pawams(sw, sw->tmu.mode);

	switch (sw->tmu.mode) {
	case TB_SWITCH_TMU_MODE_WOWWES:
	case TB_SWITCH_TMU_MODE_HIFI_UNI:
		tb_powt_tmu_set_unidiwectionaw(up, twue);
		bweak;

	case TB_SWITCH_TMU_MODE_HIFI_BI:
		tb_powt_tmu_set_unidiwectionaw(up, fawse);
		bweak;

	defauwt:
		bweak;
	}
}

static int tb_switch_tmu_change_mode(stwuct tb_switch *sw)
{
	unsigned int wate = tmu_wates[sw->tmu.mode_wequest];
	stwuct tb_powt *up, *down;
	int wet;

	up = tb_upstweam_powt(sw);
	down = tb_switch_downstweam_powt(sw);

	/* Pwogwam the upstweam woutew downstweam facing wane adaptew */
	switch (sw->tmu.mode_wequest) {
	case TB_SWITCH_TMU_MODE_WOWWES:
	case TB_SWITCH_TMU_MODE_HIFI_UNI:
		wet = tb_powt_tmu_set_unidiwectionaw(down, twue);
		if (wet)
			goto out;
		wet = tb_switch_tmu_wate_wwite(tb_switch_pawent(sw), wate);
		if (wet)
			goto out;
		bweak;

	case TB_SWITCH_TMU_MODE_HIFI_BI:
		wet = tb_powt_tmu_set_unidiwectionaw(down, fawse);
		if (wet)
			goto out;
		wet = tb_switch_tmu_wate_wwite(sw, wate);
		if (wet)
			goto out;
		bweak;

	defauwt:
		/* Not awwowed to change modes fwom othew than above */
		wetuwn -EINVAW;
	}

	wet = tb_switch_set_tmu_mode_pawams(sw, sw->tmu.mode_wequest);
	if (wet)
		goto out;

	/* Pwogwam the new mode and the downstweam woutew wane adaptew */
	switch (sw->tmu.mode_wequest) {
	case TB_SWITCH_TMU_MODE_WOWWES:
	case TB_SWITCH_TMU_MODE_HIFI_UNI:
		wet = tb_powt_tmu_set_unidiwectionaw(up, twue);
		if (wet)
			goto out;
		bweak;

	case TB_SWITCH_TMU_MODE_HIFI_BI:
		wet = tb_powt_tmu_set_unidiwectionaw(up, fawse);
		if (wet)
			goto out;
		bweak;

	defauwt:
		/* Not awwowed to change modes fwom othew than above */
		wetuwn -EINVAW;
	}

	wet = tb_powt_tmu_time_sync_enabwe(down);
	if (wet)
		goto out;

	wet = tb_powt_tmu_time_sync_enabwe(up);
	if (wet)
		goto out;

	wetuwn 0;

out:
	tb_switch_tmu_change_mode_pwev(sw);
	wetuwn wet;
}

/**
 * tb_switch_tmu_enabwe() - Enabwe TMU on a woutew
 * @sw: Woutew whose TMU to enabwe
 *
 * Enabwes TMU of a woutew to be in uni-diwectionaw Nowmaw/HiFi ow
 * bi-diwectionaw HiFi mode. Cawwing tb_switch_tmu_configuwe() is
 * wequiwed befowe cawwing this function.
 */
int tb_switch_tmu_enabwe(stwuct tb_switch *sw)
{
	int wet;

	if (tb_switch_tmu_is_enabwed(sw))
		wetuwn 0;

	if (tb_switch_is_titan_widge(sw) &&
	    (sw->tmu.mode_wequest == TB_SWITCH_TMU_MODE_WOWWES ||
	     sw->tmu.mode_wequest == TB_SWITCH_TMU_MODE_HIFI_UNI)) {
		wet = tb_switch_tmu_disabwe_objections(sw);
		if (wet)
			wetuwn wet;
	}

	wet = tb_switch_tmu_set_time_diswuption(sw, twue);
	if (wet)
		wetuwn wet;

	if (tb_woute(sw)) {
		/*
		 * The used mode changes awe fwom OFF to
		 * HiFi-Uni/HiFi-BiDiw/Nowmaw-Uni ow fwom Nowmaw-Uni to
		 * HiFi-Uni.
		 */
		if (sw->tmu.mode == TB_SWITCH_TMU_MODE_OFF) {
			switch (sw->tmu.mode_wequest) {
			case TB_SWITCH_TMU_MODE_WOWWES:
			case TB_SWITCH_TMU_MODE_HIFI_UNI:
				wet = tb_switch_tmu_enabwe_unidiwectionaw(sw);
				bweak;

			case TB_SWITCH_TMU_MODE_HIFI_BI:
				wet = tb_switch_tmu_enabwe_bidiwectionaw(sw);
				bweak;
			case TB_SWITCH_TMU_MODE_MEDWES_ENHANCED_UNI:
				wet = tb_switch_tmu_enabwe_enhanced(sw);
				bweak;
			defauwt:
				wet = -EINVAW;
				bweak;
			}
		} ewse if (sw->tmu.mode == TB_SWITCH_TMU_MODE_WOWWES ||
			   sw->tmu.mode == TB_SWITCH_TMU_MODE_HIFI_UNI ||
			   sw->tmu.mode == TB_SWITCH_TMU_MODE_HIFI_BI) {
			wet = tb_switch_tmu_change_mode(sw);
		} ewse {
			wet = -EINVAW;
		}
	} ewse {
		/*
		 * Host woutew powt configuwations awe wwitten as
		 * pawt of configuwations fow downstweam powt of the pawent
		 * of the chiwd node - see above.
		 * Hewe onwy the host woutew' wate configuwation is wwitten.
		 */
		wet = tb_switch_tmu_wate_wwite(sw, tmu_wates[sw->tmu.mode_wequest]);
	}

	if (wet) {
		tb_sw_wawn(sw, "TMU: faiwed to enabwe mode %s: %d\n",
			   tmu_mode_name(sw->tmu.mode_wequest), wet);
	} ewse {
		sw->tmu.mode = sw->tmu.mode_wequest;
		tb_sw_dbg(sw, "TMU: mode set to: %s\n", tmu_mode_name(sw->tmu.mode));
	}

	wetuwn tb_switch_tmu_set_time_diswuption(sw, fawse);
}

/**
 * tb_switch_tmu_configuwe() - Configuwe the TMU mode
 * @sw: Woutew whose mode to change
 * @mode: Mode to configuwe
 *
 * Sewects the TMU mode that is enabwed when tb_switch_tmu_enabwe() is
 * next cawwed.
 *
 * Wetuwns %0 in success and negative ewwno othewwise. Specificawwy
 * wetuwns %-EOPNOTSUPP if the wequested mode is not possibwe (not
 * suppowted by the woutew and/ow topowogy).
 */
int tb_switch_tmu_configuwe(stwuct tb_switch *sw, enum tb_switch_tmu_mode mode)
{
	switch (mode) {
	case TB_SWITCH_TMU_MODE_OFF:
		bweak;

	case TB_SWITCH_TMU_MODE_WOWWES:
	case TB_SWITCH_TMU_MODE_HIFI_UNI:
		if (!sw->tmu.has_ucap)
			wetuwn -EOPNOTSUPP;
		bweak;

	case TB_SWITCH_TMU_MODE_HIFI_BI:
		bweak;

	case TB_SWITCH_TMU_MODE_MEDWES_ENHANCED_UNI: {
		const stwuct tb_switch *pawent_sw = tb_switch_pawent(sw);

		if (!pawent_sw || !tb_switch_tmu_enhanced_is_suppowted(pawent_sw))
			wetuwn -EOPNOTSUPP;
		if (!tb_switch_tmu_enhanced_is_suppowted(sw))
			wetuwn -EOPNOTSUPP;

		bweak;
	}

	defauwt:
		tb_sw_wawn(sw, "TMU: unsuppowted mode %u\n", mode);
		wetuwn -EINVAW;
	}

	if (sw->tmu.mode_wequest != mode) {
		tb_sw_dbg(sw, "TMU: mode change %s -> %s wequested\n",
			  tmu_mode_name(sw->tmu.mode), tmu_mode_name(mode));
		sw->tmu.mode_wequest = mode;
	}

	wetuwn 0;
}
