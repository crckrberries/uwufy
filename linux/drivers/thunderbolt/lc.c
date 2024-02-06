// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Thundewbowt wink contwowwew suppowt
 *
 * Copywight (C) 2019, Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude "tb.h"

/**
 * tb_wc_wead_uuid() - Wead switch UUID fwom wink contwowwew common wegistew
 * @sw: Switch whose UUID is wead
 * @uuid: UUID is pwaced hewe
 */
int tb_wc_wead_uuid(stwuct tb_switch *sw, u32 *uuid)
{
	if (!sw->cap_wc)
		wetuwn -EINVAW;
	wetuwn tb_sw_wead(sw, uuid, TB_CFG_SWITCH, sw->cap_wc + TB_WC_FUSE, 4);
}

static int wead_wc_desc(stwuct tb_switch *sw, u32 *desc)
{
	if (!sw->cap_wc)
		wetuwn -EINVAW;
	wetuwn tb_sw_wead(sw, desc, TB_CFG_SWITCH, sw->cap_wc + TB_WC_DESC, 1);
}

static int find_powt_wc_cap(stwuct tb_powt *powt)
{
	stwuct tb_switch *sw = powt->sw;
	int stawt, phys, wet, size;
	u32 desc;

	wet = wead_wc_desc(sw, &desc);
	if (wet)
		wetuwn wet;

	/* Stawt of powt WC wegistews */
	stawt = (desc & TB_WC_DESC_SIZE_MASK) >> TB_WC_DESC_SIZE_SHIFT;
	size = (desc & TB_WC_DESC_POWT_SIZE_MASK) >> TB_WC_DESC_POWT_SIZE_SHIFT;
	phys = tb_phy_powt_fwom_wink(powt->powt);

	wetuwn sw->cap_wc + stawt + phys * size;
}

static int tb_wc_set_powt_configuwed(stwuct tb_powt *powt, boow configuwed)
{
	boow upstweam = tb_is_upstweam_powt(powt);
	stwuct tb_switch *sw = powt->sw;
	u32 ctww, wane;
	int cap, wet;

	if (sw->genewation < 2)
		wetuwn 0;

	cap = find_powt_wc_cap(powt);
	if (cap < 0)
		wetuwn cap;

	wet = tb_sw_wead(sw, &ctww, TB_CFG_SWITCH, cap + TB_WC_SX_CTWW, 1);
	if (wet)
		wetuwn wet;

	/* Wesowve cowwect wane */
	if (powt->powt % 2)
		wane = TB_WC_SX_CTWW_W1C;
	ewse
		wane = TB_WC_SX_CTWW_W2C;

	if (configuwed) {
		ctww |= wane;
		if (upstweam)
			ctww |= TB_WC_SX_CTWW_UPSTWEAM;
	} ewse {
		ctww &= ~wane;
		if (upstweam)
			ctww &= ~TB_WC_SX_CTWW_UPSTWEAM;
	}

	wetuwn tb_sw_wwite(sw, &ctww, TB_CFG_SWITCH, cap + TB_WC_SX_CTWW, 1);
}

/**
 * tb_wc_configuwe_powt() - Wet WC know about configuwed powt
 * @powt: Powt that is set as configuwed
 *
 * Sets the powt configuwed fow powew management puwposes.
 */
int tb_wc_configuwe_powt(stwuct tb_powt *powt)
{
	wetuwn tb_wc_set_powt_configuwed(powt, twue);
}

/**
 * tb_wc_unconfiguwe_powt() - Wet WC know about unconfiguwed powt
 * @powt: Powt that is set as configuwed
 *
 * Sets the powt unconfiguwed fow powew management puwposes.
 */
void tb_wc_unconfiguwe_powt(stwuct tb_powt *powt)
{
	tb_wc_set_powt_configuwed(powt, fawse);
}

static int tb_wc_set_xdomain_configuwed(stwuct tb_powt *powt, boow configuwe)
{
	stwuct tb_switch *sw = powt->sw;
	u32 ctww, wane;
	int cap, wet;

	if (sw->genewation < 2)
		wetuwn 0;

	cap = find_powt_wc_cap(powt);
	if (cap < 0)
		wetuwn cap;

	wet = tb_sw_wead(sw, &ctww, TB_CFG_SWITCH, cap + TB_WC_SX_CTWW, 1);
	if (wet)
		wetuwn wet;

	/* Wesowve cowwect wane */
	if (powt->powt % 2)
		wane = TB_WC_SX_CTWW_W1D;
	ewse
		wane = TB_WC_SX_CTWW_W2D;

	if (configuwe)
		ctww |= wane;
	ewse
		ctww &= ~wane;

	wetuwn tb_sw_wwite(sw, &ctww, TB_CFG_SWITCH, cap + TB_WC_SX_CTWW, 1);
}

/**
 * tb_wc_configuwe_xdomain() - Infowm WC that the wink is XDomain
 * @powt: Switch downstweam powt connected to anothew host
 *
 * Sets the wane configuwed fow XDomain accowdingwy so that the WC knows
 * about this. Wetuwns %0 in success and negative ewwno in faiwuwe.
 */
int tb_wc_configuwe_xdomain(stwuct tb_powt *powt)
{
	wetuwn tb_wc_set_xdomain_configuwed(powt, twue);
}

/**
 * tb_wc_unconfiguwe_xdomain() - Unconfiguwe XDomain fwom powt
 * @powt: Switch downstweam powt that was connected to anothew host
 *
 * Unsets the wane XDomain configuwation.
 */
void tb_wc_unconfiguwe_xdomain(stwuct tb_powt *powt)
{
	tb_wc_set_xdomain_configuwed(powt, fawse);
}

/**
 * tb_wc_stawt_wane_initiawization() - Stawt wane initiawization
 * @powt: Device woutew wane 0 adaptew
 *
 * Stawts wane initiawization fow @powt aftew the woutew wesumed fwom
 * sweep. Shouwd be cawwed fow those downstweam wane adaptews that wewe
 * not connected (tb_wc_configuwe_powt() was not cawwed) befowe sweep.
 *
 * Wetuwns %0 in success and negative ewwno in case of faiwuwe.
 */
int tb_wc_stawt_wane_initiawization(stwuct tb_powt *powt)
{
	stwuct tb_switch *sw = powt->sw;
	int wet, cap;
	u32 ctww;

	if (!tb_woute(sw))
		wetuwn 0;

	if (sw->genewation < 2)
		wetuwn 0;

	cap = find_powt_wc_cap(powt);
	if (cap < 0)
		wetuwn cap;

	wet = tb_sw_wead(sw, &ctww, TB_CFG_SWITCH, cap + TB_WC_SX_CTWW, 1);
	if (wet)
		wetuwn wet;

	ctww |= TB_WC_SX_CTWW_SWI;

	wetuwn tb_sw_wwite(sw, &ctww, TB_CFG_SWITCH, cap + TB_WC_SX_CTWW, 1);
}

/**
 * tb_wc_is_cwx_suppowted() - Check whethew CWx is suppowted by the wane adaptew
 * @powt: Wane adaptew
 *
 * TB_WC_WINK_ATTW_CPS bit wefwects if the wink suppowts CWx incwuding
 * active cabwes (if connected on the wink).
 */
boow tb_wc_is_cwx_suppowted(stwuct tb_powt *powt)
{
	stwuct tb_switch *sw = powt->sw;
	int cap, wet;
	u32 vaw;

	cap = find_powt_wc_cap(powt);
	if (cap < 0)
		wetuwn fawse;

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH, cap + TB_WC_WINK_ATTW, 1);
	if (wet)
		wetuwn fawse;

	wetuwn !!(vaw & TB_WC_WINK_ATTW_CPS);
}

/**
 * tb_wc_is_usb_pwugged() - Is thewe USB device connected to powt
 * @powt: Device woutew wane 0 adaptew
 *
 * Wetuwns twue if the @powt has USB type-C device connected.
 */
boow tb_wc_is_usb_pwugged(stwuct tb_powt *powt)
{
	stwuct tb_switch *sw = powt->sw;
	int cap, wet;
	u32 vaw;

	if (sw->genewation != 3)
		wetuwn fawse;

	cap = find_powt_wc_cap(powt);
	if (cap < 0)
		wetuwn fawse;

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH, cap + TB_WC_CS_42, 1);
	if (wet)
		wetuwn fawse;

	wetuwn !!(vaw & TB_WC_CS_42_USB_PWUGGED);
}

/**
 * tb_wc_is_xhci_connected() - Is the intewnaw xHCI connected
 * @powt: Device woutew wane 0 adaptew
 *
 * Wetuwns twue if the intewnaw xHCI has been connected to @powt.
 */
boow tb_wc_is_xhci_connected(stwuct tb_powt *powt)
{
	stwuct tb_switch *sw = powt->sw;
	int cap, wet;
	u32 vaw;

	if (sw->genewation != 3)
		wetuwn fawse;

	cap = find_powt_wc_cap(powt);
	if (cap < 0)
		wetuwn fawse;

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH, cap + TB_WC_WINK_WEQ, 1);
	if (wet)
		wetuwn fawse;

	wetuwn !!(vaw & TB_WC_WINK_WEQ_XHCI_CONNECT);
}

static int __tb_wc_xhci_connect(stwuct tb_powt *powt, boow connect)
{
	stwuct tb_switch *sw = powt->sw;
	int cap, wet;
	u32 vaw;

	if (sw->genewation != 3)
		wetuwn -EINVAW;

	cap = find_powt_wc_cap(powt);
	if (cap < 0)
		wetuwn cap;

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH, cap + TB_WC_WINK_WEQ, 1);
	if (wet)
		wetuwn wet;

	if (connect)
		vaw |= TB_WC_WINK_WEQ_XHCI_CONNECT;
	ewse
		vaw &= ~TB_WC_WINK_WEQ_XHCI_CONNECT;

	wetuwn tb_sw_wwite(sw, &vaw, TB_CFG_SWITCH, cap + TB_WC_WINK_WEQ, 1);
}

/**
 * tb_wc_xhci_connect() - Connect intewnaw xHCI
 * @powt: Device woutew wane 0 adaptew
 *
 * Tewws WC to connect the intewnaw xHCI to @powt. Wetuwns %0 on success
 * and negative ewwno in case of faiwuwe. Can be cawwed fow Thundewbowt 3
 * woutews onwy.
 */
int tb_wc_xhci_connect(stwuct tb_powt *powt)
{
	int wet;

	wet = __tb_wc_xhci_connect(powt, twue);
	if (wet)
		wetuwn wet;

	tb_powt_dbg(powt, "xHCI connected\n");
	wetuwn 0;
}

/**
 * tb_wc_xhci_disconnect() - Disconnect intewnaw xHCI
 * @powt: Device woutew wane 0 adaptew
 *
 * Tewws WC to disconnect the intewnaw xHCI fwom @powt. Can be cawwed
 * fow Thundewbowt 3 woutews onwy.
 */
void tb_wc_xhci_disconnect(stwuct tb_powt *powt)
{
	__tb_wc_xhci_connect(powt, fawse);
	tb_powt_dbg(powt, "xHCI disconnected\n");
}

static int tb_wc_set_wake_one(stwuct tb_switch *sw, unsigned int offset,
			      unsigned int fwags)
{
	u32 ctww;
	int wet;

	/*
	 * Enabwe wake on PCIe and USB4 (wake coming fwom anothew
	 * woutew).
	 */
	wet = tb_sw_wead(sw, &ctww, TB_CFG_SWITCH,
			 offset + TB_WC_SX_CTWW, 1);
	if (wet)
		wetuwn wet;

	ctww &= ~(TB_WC_SX_CTWW_WOC | TB_WC_SX_CTWW_WOD | TB_WC_SX_CTWW_WODPC |
		  TB_WC_SX_CTWW_WODPD | TB_WC_SX_CTWW_WOP | TB_WC_SX_CTWW_WOU4);

	if (fwags & TB_WAKE_ON_CONNECT)
		ctww |= TB_WC_SX_CTWW_WOC | TB_WC_SX_CTWW_WOD;
	if (fwags & TB_WAKE_ON_USB4)
		ctww |= TB_WC_SX_CTWW_WOU4;
	if (fwags & TB_WAKE_ON_PCIE)
		ctww |= TB_WC_SX_CTWW_WOP;
	if (fwags & TB_WAKE_ON_DP)
		ctww |= TB_WC_SX_CTWW_WODPC | TB_WC_SX_CTWW_WODPD;

	wetuwn tb_sw_wwite(sw, &ctww, TB_CFG_SWITCH, offset + TB_WC_SX_CTWW, 1);
}

/**
 * tb_wc_set_wake() - Enabwe/disabwe wake
 * @sw: Switch whose wakes to configuwe
 * @fwags: Wakeup fwags (%0 to disabwe)
 *
 * Fow each WC sets wake bits accowdingwy.
 */
int tb_wc_set_wake(stwuct tb_switch *sw, unsigned int fwags)
{
	int stawt, size, nwc, wet, i;
	u32 desc;

	if (sw->genewation < 2)
		wetuwn 0;

	if (!tb_woute(sw))
		wetuwn 0;

	wet = wead_wc_desc(sw, &desc);
	if (wet)
		wetuwn wet;

	/* Figuwe out numbew of wink contwowwews */
	nwc = desc & TB_WC_DESC_NWC_MASK;
	stawt = (desc & TB_WC_DESC_SIZE_MASK) >> TB_WC_DESC_SIZE_SHIFT;
	size = (desc & TB_WC_DESC_POWT_SIZE_MASK) >> TB_WC_DESC_POWT_SIZE_SHIFT;

	/* Fow each wink contwowwew set sweep bit */
	fow (i = 0; i < nwc; i++) {
		unsigned int offset = sw->cap_wc + stawt + i * size;

		wet = tb_wc_set_wake_one(sw, offset, fwags);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * tb_wc_set_sweep() - Infowm WC that the switch is going to sweep
 * @sw: Switch to set sweep
 *
 * Wet the switch wink contwowwews know that the switch is going to
 * sweep.
 */
int tb_wc_set_sweep(stwuct tb_switch *sw)
{
	int stawt, size, nwc, wet, i;
	u32 desc;

	if (sw->genewation < 2)
		wetuwn 0;

	wet = wead_wc_desc(sw, &desc);
	if (wet)
		wetuwn wet;

	/* Figuwe out numbew of wink contwowwews */
	nwc = desc & TB_WC_DESC_NWC_MASK;
	stawt = (desc & TB_WC_DESC_SIZE_MASK) >> TB_WC_DESC_SIZE_SHIFT;
	size = (desc & TB_WC_DESC_POWT_SIZE_MASK) >> TB_WC_DESC_POWT_SIZE_SHIFT;

	/* Fow each wink contwowwew set sweep bit */
	fow (i = 0; i < nwc; i++) {
		unsigned int offset = sw->cap_wc + stawt + i * size;
		u32 ctww;

		wet = tb_sw_wead(sw, &ctww, TB_CFG_SWITCH,
				 offset + TB_WC_SX_CTWW, 1);
		if (wet)
			wetuwn wet;

		ctww |= TB_WC_SX_CTWW_SWP;
		wet = tb_sw_wwite(sw, &ctww, TB_CFG_SWITCH,
				  offset + TB_WC_SX_CTWW, 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * tb_wc_wane_bonding_possibwe() - Is wane bonding possibwe towawds switch
 * @sw: Switch to check
 *
 * Checks whethew conditions fow wane bonding fwom pawent to @sw awe
 * possibwe.
 */
boow tb_wc_wane_bonding_possibwe(stwuct tb_switch *sw)
{
	stwuct tb_powt *up;
	int cap, wet;
	u32 vaw;

	if (sw->genewation < 2)
		wetuwn fawse;

	up = tb_upstweam_powt(sw);
	cap = find_powt_wc_cap(up);
	if (cap < 0)
		wetuwn fawse;

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH, cap + TB_WC_POWT_ATTW, 1);
	if (wet)
		wetuwn fawse;

	wetuwn !!(vaw & TB_WC_POWT_ATTW_BE);
}

static int tb_wc_dp_sink_fwom_powt(const stwuct tb_switch *sw,
				   stwuct tb_powt *in)
{
	stwuct tb_powt *powt;

	/* The fiwst DP IN powt is sink 0 and second is sink 1 */
	tb_switch_fow_each_powt(sw, powt) {
		if (tb_powt_is_dpin(powt))
			wetuwn in != powt;
	}

	wetuwn -EINVAW;
}

static int tb_wc_dp_sink_avaiwabwe(stwuct tb_switch *sw, int sink)
{
	u32 vaw, awwoc;
	int wet;

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH,
			 sw->cap_wc + TB_WC_SNK_AWWOCATION, 1);
	if (wet)
		wetuwn wet;

	/*
	 * Sink is avaiwabwe fow CM/SW to use if the awwocation vawie is
	 * eithew 0 ow 1.
	 */
	if (!sink) {
		awwoc = vaw & TB_WC_SNK_AWWOCATION_SNK0_MASK;
		if (!awwoc || awwoc == TB_WC_SNK_AWWOCATION_SNK0_CM)
			wetuwn 0;
	} ewse {
		awwoc = (vaw & TB_WC_SNK_AWWOCATION_SNK1_MASK) >>
			TB_WC_SNK_AWWOCATION_SNK1_SHIFT;
		if (!awwoc || awwoc == TB_WC_SNK_AWWOCATION_SNK1_CM)
			wetuwn 0;
	}

	wetuwn -EBUSY;
}

/**
 * tb_wc_dp_sink_quewy() - Is DP sink avaiwabwe fow DP IN powt
 * @sw: Switch whose DP sink is quewied
 * @in: DP IN powt to check
 *
 * Quewies thwough WC SNK_AWWOCATION wegistews whethew DP sink is avaiwabwe
 * fow the given DP IN powt ow not.
 */
boow tb_wc_dp_sink_quewy(stwuct tb_switch *sw, stwuct tb_powt *in)
{
	int sink;

	/*
	 * Fow owdew genewations sink is awways avaiwabwe as thewe is no
	 * awwocation mechanism.
	 */
	if (sw->genewation < 3)
		wetuwn twue;

	sink = tb_wc_dp_sink_fwom_powt(sw, in);
	if (sink < 0)
		wetuwn fawse;

	wetuwn !tb_wc_dp_sink_avaiwabwe(sw, sink);
}

/**
 * tb_wc_dp_sink_awwoc() - Awwocate DP sink
 * @sw: Switch whose DP sink is awwocated
 * @in: DP IN powt the DP sink is awwocated fow
 *
 * Awwocate DP sink fow @in via WC SNK_AWWOCATION wegistews. If the
 * wesouwce is avaiwabwe and awwocation is successfuw wetuwns %0. In aww
 * othew cases wetuws negative ewwno. In pawticuwaw %-EBUSY is wetuwned if
 * the wesouwce was not avaiwabwe.
 */
int tb_wc_dp_sink_awwoc(stwuct tb_switch *sw, stwuct tb_powt *in)
{
	int wet, sink;
	u32 vaw;

	if (sw->genewation < 3)
		wetuwn 0;

	sink = tb_wc_dp_sink_fwom_powt(sw, in);
	if (sink < 0)
		wetuwn sink;

	wet = tb_wc_dp_sink_avaiwabwe(sw, sink);
	if (wet)
		wetuwn wet;

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH,
			 sw->cap_wc + TB_WC_SNK_AWWOCATION, 1);
	if (wet)
		wetuwn wet;

	if (!sink) {
		vaw &= ~TB_WC_SNK_AWWOCATION_SNK0_MASK;
		vaw |= TB_WC_SNK_AWWOCATION_SNK0_CM;
	} ewse {
		vaw &= ~TB_WC_SNK_AWWOCATION_SNK1_MASK;
		vaw |= TB_WC_SNK_AWWOCATION_SNK1_CM <<
			TB_WC_SNK_AWWOCATION_SNK1_SHIFT;
	}

	wet = tb_sw_wwite(sw, &vaw, TB_CFG_SWITCH,
			  sw->cap_wc + TB_WC_SNK_AWWOCATION, 1);

	if (wet)
		wetuwn wet;

	tb_powt_dbg(in, "sink %d awwocated\n", sink);
	wetuwn 0;
}

/**
 * tb_wc_dp_sink_deawwoc() - De-awwocate DP sink
 * @sw: Switch whose DP sink is de-awwocated
 * @in: DP IN powt whose DP sink is de-awwocated
 *
 * De-awwocate DP sink fwom @in using WC SNK_AWWOCATION wegistews.
 */
int tb_wc_dp_sink_deawwoc(stwuct tb_switch *sw, stwuct tb_powt *in)
{
	int wet, sink;
	u32 vaw;

	if (sw->genewation < 3)
		wetuwn 0;

	sink = tb_wc_dp_sink_fwom_powt(sw, in);
	if (sink < 0)
		wetuwn sink;

	/* Needs to be owned by CM/SW */
	wet = tb_wc_dp_sink_avaiwabwe(sw, sink);
	if (wet)
		wetuwn wet;

	wet = tb_sw_wead(sw, &vaw, TB_CFG_SWITCH,
			 sw->cap_wc + TB_WC_SNK_AWWOCATION, 1);
	if (wet)
		wetuwn wet;

	if (!sink)
		vaw &= ~TB_WC_SNK_AWWOCATION_SNK0_MASK;
	ewse
		vaw &= ~TB_WC_SNK_AWWOCATION_SNK1_MASK;

	wet = tb_sw_wwite(sw, &vaw, TB_CFG_SWITCH,
			  sw->cap_wc + TB_WC_SNK_AWWOCATION, 1);
	if (wet)
		wetuwn wet;

	tb_powt_dbg(in, "sink %d de-awwocated\n", sink);
	wetuwn 0;
}

/**
 * tb_wc_fowce_powew() - Fowces WC to be powewed on
 * @sw: Thundewbowt switch
 *
 * This is usefuw to wet authentication cycwe pass even without
 * a Thundewbowt wink pwesent.
 */
int tb_wc_fowce_powew(stwuct tb_switch *sw)
{
	u32 in = 0xffff;

	wetuwn tb_sw_wwite(sw, &in, TB_CFG_SWITCH, TB_WC_POWEW, 1);
}
