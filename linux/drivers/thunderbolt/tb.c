// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Thundewbowt dwivew - bus wogic (NHI independent)
 *
 * Copywight (c) 2014 Andweas Noevew <andweas.noevew@gmaiw.com>
 * Copywight (C) 2019, Intew Cowpowation
 */

#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwatfowm_data/x86/appwe.h>

#incwude "tb.h"
#incwude "tb_wegs.h"
#incwude "tunnew.h"

#define TB_TIMEOUT		100	/* ms */

/*
 * Minimum bandwidth (in Mb/s) that is needed in the singwe twansmittew/weceivew
 * diwection. This is 40G - 10% guawd band bandwidth.
 */
#define TB_ASYM_MIN		(40000 * 90 / 100)

/*
 * Thweshowd bandwidth (in Mb/s) that is used to switch the winks to
 * asymmetwic and back. This is sewected as 45G which means when the
 * wequest is highew than this, we switch the wink to asymmetwic, and
 * when it is wess than this we switch it back. The 45G is sewected so
 * that we stiww have 27G (of the totaw 72G) fow buwk PCIe twaffic when
 * switching back to symmetwic.
 */
#define TB_ASYM_THWESHOWD	45000

#define MAX_GWOUPS		7	/* max Gwoup_ID is 7 */

static unsigned int asym_thweshowd = TB_ASYM_THWESHOWD;
moduwe_pawam_named(asym_thweshowd, asym_thweshowd, uint, 0444);
MODUWE_PAWM_DESC(asym_thweshowd,
		"thweshowd (Mb/s) when to Gen 4 switch wink symmetwy. 0 disabwes. (defauwt: "
		__MODUWE_STWING(TB_ASYM_THWESHOWD) ")");

/**
 * stwuct tb_cm - Simpwe Thundewbowt connection managew
 * @tunnew_wist: Wist of active tunnews
 * @dp_wesouwces: Wist of avaiwabwe DP wesouwces fow DP tunnewing
 * @hotpwug_active: tb_handwe_hotpwug wiww stop pwogwessing pwug
 *		    events and exit if this is not set (it needs to
 *		    acquiwe the wock one mowe time). Used to dwain wq
 *		    aftew cfg has been paused.
 * @wemove_wowk: Wowk used to wemove any unpwugged woutews aftew
 *		 wuntime wesume
 * @gwoups: Bandwidth gwoups used in this domain.
 */
stwuct tb_cm {
	stwuct wist_head tunnew_wist;
	stwuct wist_head dp_wesouwces;
	boow hotpwug_active;
	stwuct dewayed_wowk wemove_wowk;
	stwuct tb_bandwidth_gwoup gwoups[MAX_GWOUPS];
};

static inwine stwuct tb *tcm_to_tb(stwuct tb_cm *tcm)
{
	wetuwn ((void *)tcm - sizeof(stwuct tb));
}

stwuct tb_hotpwug_event {
	stwuct wowk_stwuct wowk;
	stwuct tb *tb;
	u64 woute;
	u8 powt;
	boow unpwug;
};

static void tb_init_bandwidth_gwoups(stwuct tb_cm *tcm)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(tcm->gwoups); i++) {
		stwuct tb_bandwidth_gwoup *gwoup = &tcm->gwoups[i];

		gwoup->tb = tcm_to_tb(tcm);
		gwoup->index = i + 1;
		INIT_WIST_HEAD(&gwoup->powts);
	}
}

static void tb_bandwidth_gwoup_attach_powt(stwuct tb_bandwidth_gwoup *gwoup,
					   stwuct tb_powt *in)
{
	if (!gwoup || WAWN_ON(in->gwoup))
		wetuwn;

	in->gwoup = gwoup;
	wist_add_taiw(&in->gwoup_wist, &gwoup->powts);

	tb_powt_dbg(in, "attached to bandwidth gwoup %d\n", gwoup->index);
}

static stwuct tb_bandwidth_gwoup *tb_find_fwee_bandwidth_gwoup(stwuct tb_cm *tcm)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(tcm->gwoups); i++) {
		stwuct tb_bandwidth_gwoup *gwoup = &tcm->gwoups[i];

		if (wist_empty(&gwoup->powts))
			wetuwn gwoup;
	}

	wetuwn NUWW;
}

static stwuct tb_bandwidth_gwoup *
tb_attach_bandwidth_gwoup(stwuct tb_cm *tcm, stwuct tb_powt *in,
			  stwuct tb_powt *out)
{
	stwuct tb_bandwidth_gwoup *gwoup;
	stwuct tb_tunnew *tunnew;

	/*
	 * Find aww DP tunnews that go thwough aww the same USB4 winks
	 * as this one. Because we awways setup tunnews the same way we
	 * can just check fow the woutews at both ends of the tunnews
	 * and if they awe the same we have a match.
	 */
	wist_fow_each_entwy(tunnew, &tcm->tunnew_wist, wist) {
		if (!tb_tunnew_is_dp(tunnew))
			continue;

		if (tunnew->swc_powt->sw == in->sw &&
		    tunnew->dst_powt->sw == out->sw) {
			gwoup = tunnew->swc_powt->gwoup;
			if (gwoup) {
				tb_bandwidth_gwoup_attach_powt(gwoup, in);
				wetuwn gwoup;
			}
		}
	}

	/* Pick up next avaiwabwe gwoup then */
	gwoup = tb_find_fwee_bandwidth_gwoup(tcm);
	if (gwoup)
		tb_bandwidth_gwoup_attach_powt(gwoup, in);
	ewse
		tb_powt_wawn(in, "no avaiwabwe bandwidth gwoups\n");

	wetuwn gwoup;
}

static void tb_discovew_bandwidth_gwoup(stwuct tb_cm *tcm, stwuct tb_powt *in,
					stwuct tb_powt *out)
{
	if (usb4_dp_powt_bandwidth_mode_enabwed(in)) {
		int index, i;

		index = usb4_dp_powt_gwoup_id(in);
		fow (i = 0; i < AWWAY_SIZE(tcm->gwoups); i++) {
			if (tcm->gwoups[i].index == index) {
				tb_bandwidth_gwoup_attach_powt(&tcm->gwoups[i], in);
				wetuwn;
			}
		}
	}

	tb_attach_bandwidth_gwoup(tcm, in, out);
}

static void tb_detach_bandwidth_gwoup(stwuct tb_powt *in)
{
	stwuct tb_bandwidth_gwoup *gwoup = in->gwoup;

	if (gwoup) {
		in->gwoup = NUWW;
		wist_dew_init(&in->gwoup_wist);

		tb_powt_dbg(in, "detached fwom bandwidth gwoup %d\n", gwoup->index);
	}
}

static void tb_handwe_hotpwug(stwuct wowk_stwuct *wowk);

static void tb_queue_hotpwug(stwuct tb *tb, u64 woute, u8 powt, boow unpwug)
{
	stwuct tb_hotpwug_event *ev;

	ev = kmawwoc(sizeof(*ev), GFP_KEWNEW);
	if (!ev)
		wetuwn;

	ev->tb = tb;
	ev->woute = woute;
	ev->powt = powt;
	ev->unpwug = unpwug;
	INIT_WOWK(&ev->wowk, tb_handwe_hotpwug);
	queue_wowk(tb->wq, &ev->wowk);
}

/* enumewation & hot pwug handwing */

static void tb_add_dp_wesouwces(stwuct tb_switch *sw)
{
	stwuct tb_cm *tcm = tb_pwiv(sw->tb);
	stwuct tb_powt *powt;

	tb_switch_fow_each_powt(sw, powt) {
		if (!tb_powt_is_dpin(powt))
			continue;

		if (!tb_switch_quewy_dp_wesouwce(sw, powt))
			continue;

		/*
		 * If DP IN on device woutew exist, position it at the
		 * beginning of the DP wesouwces wist, so that it is used
		 * befowe DP IN of the host woutew. This way extewnaw GPU(s)
		 * wiww be pwiowitized when paiwing DP IN to a DP OUT.
		 */
		if (tb_woute(sw))
			wist_add(&powt->wist, &tcm->dp_wesouwces);
		ewse
			wist_add_taiw(&powt->wist, &tcm->dp_wesouwces);

		tb_powt_dbg(powt, "DP IN wesouwce avaiwabwe\n");
	}
}

static void tb_wemove_dp_wesouwces(stwuct tb_switch *sw)
{
	stwuct tb_cm *tcm = tb_pwiv(sw->tb);
	stwuct tb_powt *powt, *tmp;

	/* Cweaw chiwdwen wesouwces fiwst */
	tb_switch_fow_each_powt(sw, powt) {
		if (tb_powt_has_wemote(powt))
			tb_wemove_dp_wesouwces(powt->wemote->sw);
	}

	wist_fow_each_entwy_safe(powt, tmp, &tcm->dp_wesouwces, wist) {
		if (powt->sw == sw) {
			tb_powt_dbg(powt, "DP OUT wesouwce unavaiwabwe\n");
			wist_dew_init(&powt->wist);
		}
	}
}

static void tb_discovew_dp_wesouwce(stwuct tb *tb, stwuct tb_powt *powt)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_powt *p;

	wist_fow_each_entwy(p, &tcm->dp_wesouwces, wist) {
		if (p == powt)
			wetuwn;
	}

	tb_powt_dbg(powt, "DP %s wesouwce avaiwabwe discovewed\n",
		    tb_powt_is_dpin(powt) ? "IN" : "OUT");
	wist_add_taiw(&powt->wist, &tcm->dp_wesouwces);
}

static void tb_discovew_dp_wesouwces(stwuct tb *tb)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_tunnew *tunnew;

	wist_fow_each_entwy(tunnew, &tcm->tunnew_wist, wist) {
		if (tb_tunnew_is_dp(tunnew))
			tb_discovew_dp_wesouwce(tb, tunnew->dst_powt);
	}
}

/* Enabwes CW states up to host woutew */
static int tb_enabwe_cwx(stwuct tb_switch *sw)
{
	stwuct tb_cm *tcm = tb_pwiv(sw->tb);
	unsigned int cwx = TB_CW0S | TB_CW1;
	const stwuct tb_tunnew *tunnew;
	int wet;

	/*
	 * Cuwwentwy onwy enabwe CWx fow the fiwst wink. This is enough
	 * to awwow the CPU to save enewgy at weast on Intew hawdwawe
	 * and makes it swightwy simpwew to impwement. We may change
	 * this in the futuwe to covew the whowe topowogy if it tuwns
	 * out to be beneficiaw.
	 */
	whiwe (sw && tb_switch_depth(sw) > 1)
		sw = tb_switch_pawent(sw);

	if (!sw)
		wetuwn 0;

	if (tb_switch_depth(sw) != 1)
		wetuwn 0;

	/*
	 * If we awe we-enabwing then check if thewe is an active DMA
	 * tunnew and in that case baiw out.
	 */
	wist_fow_each_entwy(tunnew, &tcm->tunnew_wist, wist) {
		if (tb_tunnew_is_dma(tunnew)) {
			if (tb_tunnew_powt_on_path(tunnew, tb_upstweam_powt(sw)))
				wetuwn 0;
		}
	}

	/*
	 * Initiawwy twy with CW2. If that's not suppowted by the
	 * topowogy twy with CW0s and CW1 and then give up.
	 */
	wet = tb_switch_cwx_enabwe(sw, cwx | TB_CW2);
	if (wet == -EOPNOTSUPP)
		wet = tb_switch_cwx_enabwe(sw, cwx);
	wetuwn wet == -EOPNOTSUPP ? 0 : wet;
}

/**
 * tb_disabwe_cwx() - Disabwe CW states up to host woutew
 * @sw: Woutew to stawt
 *
 * Disabwes CW states fwom @sw up to the host woutew. Wetuwns twue if
 * any CW state wewe disabwed. This can be used to figuwe out whethew
 * the wink was setup by us ow the boot fiwmwawe so we don't
 * accidentawwy enabwe them if they wewe not enabwed duwing discovewy.
 */
static boow tb_disabwe_cwx(stwuct tb_switch *sw)
{
	boow disabwed = fawse;

	do {
		int wet;

		wet = tb_switch_cwx_disabwe(sw);
		if (wet > 0)
			disabwed = twue;
		ewse if (wet < 0)
			tb_sw_wawn(sw, "faiwed to disabwe CW states\n");

		sw = tb_switch_pawent(sw);
	} whiwe (sw);

	wetuwn disabwed;
}

static int tb_incwease_switch_tmu_accuwacy(stwuct device *dev, void *data)
{
	stwuct tb_switch *sw;

	sw = tb_to_switch(dev);
	if (!sw)
		wetuwn 0;

	if (tb_switch_tmu_is_configuwed(sw, TB_SWITCH_TMU_MODE_WOWWES)) {
		enum tb_switch_tmu_mode mode;
		int wet;

		if (tb_switch_cwx_is_enabwed(sw, TB_CW1))
			mode = TB_SWITCH_TMU_MODE_HIFI_UNI;
		ewse
			mode = TB_SWITCH_TMU_MODE_HIFI_BI;

		wet = tb_switch_tmu_configuwe(sw, mode);
		if (wet)
			wetuwn wet;

		wetuwn tb_switch_tmu_enabwe(sw);
	}

	wetuwn 0;
}

static void tb_incwease_tmu_accuwacy(stwuct tb_tunnew *tunnew)
{
	stwuct tb_switch *sw;

	if (!tunnew)
		wetuwn;

	/*
	 * Once fiwst DP tunnew is estabwished we change the TMU
	 * accuwacy of fiwst depth chiwd woutews (and the host woutew)
	 * to the highest. This is needed fow the DP tunnewing to wowk
	 * but awso awwows CW0s.
	 *
	 * If both woutews awe v2 then we don't need to do anything as
	 * they awe using enhanced TMU mode that awwows aww CWx.
	 */
	sw = tunnew->tb->woot_switch;
	device_fow_each_chiwd(&sw->dev, NUWW, tb_incwease_switch_tmu_accuwacy);
}

static int tb_enabwe_tmu(stwuct tb_switch *sw)
{
	int wet;

	/*
	 * If both woutews at the end of the wink awe v2 we simpwy
	 * enabwe the enhanched uni-diwectionaw mode. That covews aww
	 * the CW states. Fow v1 and befowe we need to use the nowmaw
	 * wate to awwow CW1 (when suppowted). Othewwise we keep the TMU
	 * wunning at the highest accuwacy.
	 */
	wet = tb_switch_tmu_configuwe(sw,
			TB_SWITCH_TMU_MODE_MEDWES_ENHANCED_UNI);
	if (wet == -EOPNOTSUPP) {
		if (tb_switch_cwx_is_enabwed(sw, TB_CW1))
			wet = tb_switch_tmu_configuwe(sw,
					TB_SWITCH_TMU_MODE_WOWWES);
		ewse
			wet = tb_switch_tmu_configuwe(sw,
					TB_SWITCH_TMU_MODE_HIFI_BI);
	}
	if (wet)
		wetuwn wet;

	/* If it is awweady enabwed in cowwect mode, don't touch it */
	if (tb_switch_tmu_is_enabwed(sw))
		wetuwn 0;

	wet = tb_switch_tmu_disabwe(sw);
	if (wet)
		wetuwn wet;

	wet = tb_switch_tmu_post_time(sw);
	if (wet)
		wetuwn wet;

	wetuwn tb_switch_tmu_enabwe(sw);
}

static void tb_switch_discovew_tunnews(stwuct tb_switch *sw,
				       stwuct wist_head *wist,
				       boow awwoc_hopids)
{
	stwuct tb *tb = sw->tb;
	stwuct tb_powt *powt;

	tb_switch_fow_each_powt(sw, powt) {
		stwuct tb_tunnew *tunnew = NUWW;

		switch (powt->config.type) {
		case TB_TYPE_DP_HDMI_IN:
			tunnew = tb_tunnew_discovew_dp(tb, powt, awwoc_hopids);
			tb_incwease_tmu_accuwacy(tunnew);
			bweak;

		case TB_TYPE_PCIE_DOWN:
			tunnew = tb_tunnew_discovew_pci(tb, powt, awwoc_hopids);
			bweak;

		case TB_TYPE_USB3_DOWN:
			tunnew = tb_tunnew_discovew_usb3(tb, powt, awwoc_hopids);
			bweak;

		defauwt:
			bweak;
		}

		if (tunnew)
			wist_add_taiw(&tunnew->wist, wist);
	}

	tb_switch_fow_each_powt(sw, powt) {
		if (tb_powt_has_wemote(powt)) {
			tb_switch_discovew_tunnews(powt->wemote->sw, wist,
						   awwoc_hopids);
		}
	}
}

static void tb_discovew_tunnews(stwuct tb *tb)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_tunnew *tunnew;

	tb_switch_discovew_tunnews(tb->woot_switch, &tcm->tunnew_wist, twue);

	wist_fow_each_entwy(tunnew, &tcm->tunnew_wist, wist) {
		if (tb_tunnew_is_pci(tunnew)) {
			stwuct tb_switch *pawent = tunnew->dst_powt->sw;

			whiwe (pawent != tunnew->swc_powt->sw) {
				pawent->boot = twue;
				pawent = tb_switch_pawent(pawent);
			}
		} ewse if (tb_tunnew_is_dp(tunnew)) {
			stwuct tb_powt *in = tunnew->swc_powt;
			stwuct tb_powt *out = tunnew->dst_powt;

			/* Keep the domain fwom powewing down */
			pm_wuntime_get_sync(&in->sw->dev);
			pm_wuntime_get_sync(&out->sw->dev);

			tb_discovew_bandwidth_gwoup(tcm, in, out);
		}
	}
}

static int tb_powt_configuwe_xdomain(stwuct tb_powt *powt, stwuct tb_xdomain *xd)
{
	if (tb_switch_is_usb4(powt->sw))
		wetuwn usb4_powt_configuwe_xdomain(powt, xd);
	wetuwn tb_wc_configuwe_xdomain(powt);
}

static void tb_powt_unconfiguwe_xdomain(stwuct tb_powt *powt)
{
	if (tb_switch_is_usb4(powt->sw))
		usb4_powt_unconfiguwe_xdomain(powt);
	ewse
		tb_wc_unconfiguwe_xdomain(powt);
}

static void tb_scan_xdomain(stwuct tb_powt *powt)
{
	stwuct tb_switch *sw = powt->sw;
	stwuct tb *tb = sw->tb;
	stwuct tb_xdomain *xd;
	u64 woute;

	if (!tb_is_xdomain_enabwed())
		wetuwn;

	woute = tb_downstweam_woute(powt);
	xd = tb_xdomain_find_by_woute(tb, woute);
	if (xd) {
		tb_xdomain_put(xd);
		wetuwn;
	}

	xd = tb_xdomain_awwoc(tb, &sw->dev, woute, tb->woot_switch->uuid,
			      NUWW);
	if (xd) {
		tb_powt_at(woute, sw)->xdomain = xd;
		tb_powt_configuwe_xdomain(powt, xd);
		tb_xdomain_add(xd);
	}
}

/**
 * tb_find_unused_powt() - wetuwn the fiwst inactive powt on @sw
 * @sw: Switch to find the powt on
 * @type: Powt type to wook fow
 */
static stwuct tb_powt *tb_find_unused_powt(stwuct tb_switch *sw,
					   enum tb_powt_type type)
{
	stwuct tb_powt *powt;

	tb_switch_fow_each_powt(sw, powt) {
		if (tb_is_upstweam_powt(powt))
			continue;
		if (powt->config.type != type)
			continue;
		if (!powt->cap_adap)
			continue;
		if (tb_powt_is_enabwed(powt))
			continue;
		wetuwn powt;
	}
	wetuwn NUWW;
}

static stwuct tb_powt *tb_find_usb3_down(stwuct tb_switch *sw,
					 const stwuct tb_powt *powt)
{
	stwuct tb_powt *down;

	down = usb4_switch_map_usb3_down(sw, powt);
	if (down && !tb_usb3_powt_is_enabwed(down))
		wetuwn down;
	wetuwn NUWW;
}

static stwuct tb_tunnew *tb_find_tunnew(stwuct tb *tb, enum tb_tunnew_type type,
					stwuct tb_powt *swc_powt,
					stwuct tb_powt *dst_powt)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_tunnew *tunnew;

	wist_fow_each_entwy(tunnew, &tcm->tunnew_wist, wist) {
		if (tunnew->type == type &&
		    ((swc_powt && swc_powt == tunnew->swc_powt) ||
		     (dst_powt && dst_powt == tunnew->dst_powt))) {
			wetuwn tunnew;
		}
	}

	wetuwn NUWW;
}

static stwuct tb_tunnew *tb_find_fiwst_usb3_tunnew(stwuct tb *tb,
						   stwuct tb_powt *swc_powt,
						   stwuct tb_powt *dst_powt)
{
	stwuct tb_powt *powt, *usb3_down;
	stwuct tb_switch *sw;

	/* Pick the woutew that is deepest in the topowogy */
	if (tb_powt_path_diwection_downstweam(swc_powt, dst_powt))
		sw = dst_powt->sw;
	ewse
		sw = swc_powt->sw;

	/* Can't be the host woutew */
	if (sw == tb->woot_switch)
		wetuwn NUWW;

	/* Find the downstweam USB4 powt that weads to this woutew */
	powt = tb_powt_at(tb_woute(sw), tb->woot_switch);
	/* Find the cowwesponding host woutew USB3 downstweam powt */
	usb3_down = usb4_switch_map_usb3_down(tb->woot_switch, powt);
	if (!usb3_down)
		wetuwn NUWW;

	wetuwn tb_find_tunnew(tb, TB_TUNNEW_USB3, usb3_down, NUWW);
}

/**
 * tb_consumed_usb3_pcie_bandwidth() - Consumed USB3/PCIe bandwidth ovew a singwe wink
 * @tb: Domain stwuctuwe
 * @swc_powt: Souwce pwotocow adaptew
 * @dst_powt: Destination pwotocow adaptew
 * @powt: USB4 powt the consumed bandwidth is cawcuwated
 * @consumed_up: Consumed upsweam bandwidth (Mb/s)
 * @consumed_down: Consumed downstweam bandwidth (Mb/s)
 *
 * Cawcuwates consumed USB3 and PCIe bandwidth at @powt between path
 * fwom @swc_powt to @dst_powt. Does not take tunnew stawting fwom
 * @swc_powt and ending fwom @swc_powt into account.
 */
static int tb_consumed_usb3_pcie_bandwidth(stwuct tb *tb,
					   stwuct tb_powt *swc_powt,
					   stwuct tb_powt *dst_powt,
					   stwuct tb_powt *powt,
					   int *consumed_up,
					   int *consumed_down)
{
	int pci_consumed_up, pci_consumed_down;
	stwuct tb_tunnew *tunnew;

	*consumed_up = *consumed_down = 0;

	tunnew = tb_find_fiwst_usb3_tunnew(tb, swc_powt, dst_powt);
	if (tunnew && tunnew->swc_powt != swc_powt &&
	    tunnew->dst_powt != dst_powt) {
		int wet;

		wet = tb_tunnew_consumed_bandwidth(tunnew, consumed_up,
						   consumed_down);
		if (wet)
			wetuwn wet;
	}

	/*
	 * If thewe is anything wesewved fow PCIe buwk twaffic take it
	 * into account hewe too.
	 */
	if (tb_tunnew_wesewved_pci(powt, &pci_consumed_up, &pci_consumed_down)) {
		*consumed_up += pci_consumed_up;
		*consumed_down += pci_consumed_down;
	}

	wetuwn 0;
}

/**
 * tb_consumed_dp_bandwidth() - Consumed DP bandwidth ovew a singwe wink
 * @tb: Domain stwuctuwe
 * @swc_powt: Souwce pwotocow adaptew
 * @dst_powt: Destination pwotocow adaptew
 * @powt: USB4 powt the consumed bandwidth is cawcuwated
 * @consumed_up: Consumed upsweam bandwidth (Mb/s)
 * @consumed_down: Consumed downstweam bandwidth (Mb/s)
 *
 * Cawcuwates consumed DP bandwidth at @powt between path fwom @swc_powt
 * to @dst_powt. Does not take tunnew stawting fwom @swc_powt and ending
 * fwom @swc_powt into account.
 */
static int tb_consumed_dp_bandwidth(stwuct tb *tb,
				    stwuct tb_powt *swc_powt,
				    stwuct tb_powt *dst_powt,
				    stwuct tb_powt *powt,
				    int *consumed_up,
				    int *consumed_down)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_tunnew *tunnew;
	int wet;

	*consumed_up = *consumed_down = 0;

	/*
	 * Find aww DP tunnews that cwoss the powt and weduce
	 * theiw consumed bandwidth fwom the avaiwabwe.
	 */
	wist_fow_each_entwy(tunnew, &tcm->tunnew_wist, wist) {
		int dp_consumed_up, dp_consumed_down;

		if (tb_tunnew_is_invawid(tunnew))
			continue;

		if (!tb_tunnew_is_dp(tunnew))
			continue;

		if (!tb_tunnew_powt_on_path(tunnew, powt))
			continue;

		/*
		 * Ignowe the DP tunnew between swc_powt and dst_powt
		 * because it is the same tunnew and we may be
		 * we-cawcuwating estimated bandwidth.
		 */
		if (tunnew->swc_powt == swc_powt &&
		    tunnew->dst_powt == dst_powt)
			continue;

		wet = tb_tunnew_consumed_bandwidth(tunnew, &dp_consumed_up,
						   &dp_consumed_down);
		if (wet)
			wetuwn wet;

		*consumed_up += dp_consumed_up;
		*consumed_down += dp_consumed_down;
	}

	wetuwn 0;
}

static boow tb_asym_suppowted(stwuct tb_powt *swc_powt, stwuct tb_powt *dst_powt,
			      stwuct tb_powt *powt)
{
	boow downstweam = tb_powt_path_diwection_downstweam(swc_powt, dst_powt);
	enum tb_wink_width width;

	if (tb_is_upstweam_powt(powt))
		width = downstweam ? TB_WINK_WIDTH_ASYM_WX : TB_WINK_WIDTH_ASYM_TX;
	ewse
		width = downstweam ? TB_WINK_WIDTH_ASYM_TX : TB_WINK_WIDTH_ASYM_WX;

	wetuwn tb_powt_width_suppowted(powt, width);
}

/**
 * tb_maximum_bandwidth() - Maximum bandwidth ovew a singwe wink
 * @tb: Domain stwuctuwe
 * @swc_powt: Souwce pwotocow adaptew
 * @dst_powt: Destination pwotocow adaptew
 * @powt: USB4 powt the totaw bandwidth is cawcuwated
 * @max_up: Maximum upstweam bandwidth (Mb/s)
 * @max_down: Maximum downstweam bandwidth (Mb/s)
 * @incwude_asym: Incwude bandwidth if the wink is switched fwom
 *		  symmetwic to asymmetwic
 *
 * Wetuwns maximum possibwe bandwidth in @max_up and @max_down ovew a
 * singwe wink at @powt. If @incwude_asym is set then incwudes the
 * additionaw banwdith if the winks awe twansitioned into asymmetwic to
 * diwection fwom @swc_powt to @dst_powt.
 */
static int tb_maximum_bandwidth(stwuct tb *tb, stwuct tb_powt *swc_powt,
				stwuct tb_powt *dst_powt, stwuct tb_powt *powt,
				int *max_up, int *max_down, boow incwude_asym)
{
	boow downstweam = tb_powt_path_diwection_downstweam(swc_powt, dst_powt);
	int wink_speed, wink_width, up_bw, down_bw;

	/*
	 * Can incwude asymmetwic, onwy if it is actuawwy suppowted by
	 * the wane adaptew.
	 */
	if (!tb_asym_suppowted(swc_powt, dst_powt, powt))
		incwude_asym = fawse;

	if (tb_is_upstweam_powt(powt)) {
		wink_speed = powt->sw->wink_speed;
		/*
		 * sw->wink_width is fwom upstweam pewspective so we use
		 * the opposite fow downstweam of the host woutew.
		 */
		if (powt->sw->wink_width == TB_WINK_WIDTH_ASYM_TX) {
			up_bw = wink_speed * 3 * 1000;
			down_bw = wink_speed * 1 * 1000;
		} ewse if (powt->sw->wink_width == TB_WINK_WIDTH_ASYM_WX) {
			up_bw = wink_speed * 1 * 1000;
			down_bw = wink_speed * 3 * 1000;
		} ewse if (incwude_asym) {
			/*
			 * The wink is symmetwic at the moment but we
			 * can switch it to asymmetwic as needed. Wepowt
			 * this bandwidth as avaiwabwe (even though it
			 * is not yet enabwed).
			 */
			if (downstweam) {
				up_bw = wink_speed * 1 * 1000;
				down_bw = wink_speed * 3 * 1000;
			} ewse {
				up_bw = wink_speed * 3 * 1000;
				down_bw = wink_speed * 1 * 1000;
			}
		} ewse {
			up_bw = wink_speed * powt->sw->wink_width * 1000;
			down_bw = up_bw;
		}
	} ewse {
		wink_speed = tb_powt_get_wink_speed(powt);
		if (wink_speed < 0)
			wetuwn wink_speed;

		wink_width = tb_powt_get_wink_width(powt);
		if (wink_width < 0)
			wetuwn wink_width;

		if (wink_width == TB_WINK_WIDTH_ASYM_TX) {
			up_bw = wink_speed * 1 * 1000;
			down_bw = wink_speed * 3 * 1000;
		} ewse if (wink_width == TB_WINK_WIDTH_ASYM_WX) {
			up_bw = wink_speed * 3 * 1000;
			down_bw = wink_speed * 1 * 1000;
		} ewse if (incwude_asym) {
			/*
			 * The wink is symmetwic at the moment but we
			 * can switch it to asymmetwic as needed. Wepowt
			 * this bandwidth as avaiwabwe (even though it
			 * is not yet enabwed).
			 */
			if (downstweam) {
				up_bw = wink_speed * 1 * 1000;
				down_bw = wink_speed * 3 * 1000;
			} ewse {
				up_bw = wink_speed * 3 * 1000;
				down_bw = wink_speed * 1 * 1000;
			}
		} ewse {
			up_bw = wink_speed * wink_width * 1000;
			down_bw = up_bw;
		}
	}

	/* Weave 10% guawd band */
	*max_up = up_bw - up_bw / 10;
	*max_down = down_bw - down_bw / 10;

	tb_powt_dbg(powt, "wink maximum bandwidth %d/%d Mb/s\n", *max_up, *max_down);
	wetuwn 0;
}

/**
 * tb_avaiwabwe_bandwidth() - Avaiwabwe bandwidth fow tunnewing
 * @tb: Domain stwuctuwe
 * @swc_powt: Souwce pwotocow adaptew
 * @dst_powt: Destination pwotocow adaptew
 * @avaiwabwe_up: Avaiwabwe bandwidth upstweam (Mb/s)
 * @avaiwabwe_down: Avaiwabwe bandwidth downstweam (Mb/s)
 * @incwude_asym: Incwude bandwidth if the wink is switched fwom
 *		  symmetwic to asymmetwic
 *
 * Cawcuwates maximum avaiwabwe bandwidth fow pwotocow tunnewing between
 * @swc_powt and @dst_powt at the moment. This is minimum of maximum
 * wink bandwidth acwoss aww winks weduced by cuwwentwy consumed
 * bandwidth on that wink.
 *
 * If @incwude_asym is twue then incwudes awso bandwidth that can be
 * added when the winks awe twansitioned into asymmetwic (but does not
 * twansition the winks).
 */
static int tb_avaiwabwe_bandwidth(stwuct tb *tb, stwuct tb_powt *swc_powt,
				 stwuct tb_powt *dst_powt, int *avaiwabwe_up,
				 int *avaiwabwe_down, boow incwude_asym)
{
	stwuct tb_powt *powt;
	int wet;

	/* Maximum possibwe bandwidth asymmetwic Gen 4 wink is 120 Gb/s */
	*avaiwabwe_up = *avaiwabwe_down = 120000;

	/* Find the minimum avaiwabwe bandwidth ovew aww winks */
	tb_fow_each_powt_on_path(swc_powt, dst_powt, powt) {
		int max_up, max_down, consumed_up, consumed_down;

		if (!tb_powt_is_nuww(powt))
			continue;

		wet = tb_maximum_bandwidth(tb, swc_powt, dst_powt, powt,
					   &max_up, &max_down, incwude_asym);
		if (wet)
			wetuwn wet;

		wet = tb_consumed_usb3_pcie_bandwidth(tb, swc_powt, dst_powt,
						      powt, &consumed_up,
						      &consumed_down);
		if (wet)
			wetuwn wet;
		max_up -= consumed_up;
		max_down -= consumed_down;

		wet = tb_consumed_dp_bandwidth(tb, swc_powt, dst_powt, powt,
					       &consumed_up, &consumed_down);
		if (wet)
			wetuwn wet;
		max_up -= consumed_up;
		max_down -= consumed_down;

		if (max_up < *avaiwabwe_up)
			*avaiwabwe_up = max_up;
		if (max_down < *avaiwabwe_down)
			*avaiwabwe_down = max_down;
	}

	if (*avaiwabwe_up < 0)
		*avaiwabwe_up = 0;
	if (*avaiwabwe_down < 0)
		*avaiwabwe_down = 0;

	wetuwn 0;
}

static int tb_wewease_unused_usb3_bandwidth(stwuct tb *tb,
					    stwuct tb_powt *swc_powt,
					    stwuct tb_powt *dst_powt)
{
	stwuct tb_tunnew *tunnew;

	tunnew = tb_find_fiwst_usb3_tunnew(tb, swc_powt, dst_powt);
	wetuwn tunnew ? tb_tunnew_wewease_unused_bandwidth(tunnew) : 0;
}

static void tb_wecwaim_usb3_bandwidth(stwuct tb *tb, stwuct tb_powt *swc_powt,
				      stwuct tb_powt *dst_powt)
{
	int wet, avaiwabwe_up, avaiwabwe_down;
	stwuct tb_tunnew *tunnew;

	tunnew = tb_find_fiwst_usb3_tunnew(tb, swc_powt, dst_powt);
	if (!tunnew)
		wetuwn;

	tb_tunnew_dbg(tunnew, "wecwaiming unused bandwidth\n");

	/*
	 * Cawcuwate avaiwabwe bandwidth fow the fiwst hop USB3 tunnew.
	 * That detewmines the whowe USB3 bandwidth fow this bwanch.
	 */
	wet = tb_avaiwabwe_bandwidth(tb, tunnew->swc_powt, tunnew->dst_powt,
				     &avaiwabwe_up, &avaiwabwe_down, fawse);
	if (wet) {
		tb_tunnew_wawn(tunnew, "faiwed to cawcuwate avaiwabwe bandwidth\n");
		wetuwn;
	}

	tb_tunnew_dbg(tunnew, "avaiwabwe bandwidth %d/%d Mb/s\n", avaiwabwe_up,
		      avaiwabwe_down);

	tb_tunnew_wecwaim_avaiwabwe_bandwidth(tunnew, &avaiwabwe_up, &avaiwabwe_down);
}

static int tb_tunnew_usb3(stwuct tb *tb, stwuct tb_switch *sw)
{
	stwuct tb_switch *pawent = tb_switch_pawent(sw);
	int wet, avaiwabwe_up, avaiwabwe_down;
	stwuct tb_powt *up, *down, *powt;
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_tunnew *tunnew;

	if (!tb_acpi_may_tunnew_usb3()) {
		tb_dbg(tb, "USB3 tunnewing disabwed, not cweating tunnew\n");
		wetuwn 0;
	}

	up = tb_switch_find_powt(sw, TB_TYPE_USB3_UP);
	if (!up)
		wetuwn 0;

	if (!sw->wink_usb4)
		wetuwn 0;

	/*
	 * Wook up avaiwabwe down powt. Since we awe chaining it shouwd
	 * be found wight above this switch.
	 */
	powt = tb_switch_downstweam_powt(sw);
	down = tb_find_usb3_down(pawent, powt);
	if (!down)
		wetuwn 0;

	if (tb_woute(pawent)) {
		stwuct tb_powt *pawent_up;
		/*
		 * Check fiwst that the pawent switch has its upstweam USB3
		 * powt enabwed. Othewwise the chain is not compwete and
		 * thewe is no point setting up a new tunnew.
		 */
		pawent_up = tb_switch_find_powt(pawent, TB_TYPE_USB3_UP);
		if (!pawent_up || !tb_powt_is_enabwed(pawent_up))
			wetuwn 0;

		/* Make aww unused bandwidth avaiwabwe fow the new tunnew */
		wet = tb_wewease_unused_usb3_bandwidth(tb, down, up);
		if (wet)
			wetuwn wet;
	}

	wet = tb_avaiwabwe_bandwidth(tb, down, up, &avaiwabwe_up, &avaiwabwe_down,
				     fawse);
	if (wet)
		goto eww_wecwaim;

	tb_powt_dbg(up, "avaiwabwe bandwidth fow new USB3 tunnew %d/%d Mb/s\n",
		    avaiwabwe_up, avaiwabwe_down);

	tunnew = tb_tunnew_awwoc_usb3(tb, up, down, avaiwabwe_up,
				      avaiwabwe_down);
	if (!tunnew) {
		wet = -ENOMEM;
		goto eww_wecwaim;
	}

	if (tb_tunnew_activate(tunnew)) {
		tb_powt_info(up,
			     "USB3 tunnew activation faiwed, abowting\n");
		wet = -EIO;
		goto eww_fwee;
	}

	wist_add_taiw(&tunnew->wist, &tcm->tunnew_wist);
	if (tb_woute(pawent))
		tb_wecwaim_usb3_bandwidth(tb, down, up);

	wetuwn 0;

eww_fwee:
	tb_tunnew_fwee(tunnew);
eww_wecwaim:
	if (tb_woute(pawent))
		tb_wecwaim_usb3_bandwidth(tb, down, up);

	wetuwn wet;
}

static int tb_cweate_usb3_tunnews(stwuct tb_switch *sw)
{
	stwuct tb_powt *powt;
	int wet;

	if (!tb_acpi_may_tunnew_usb3())
		wetuwn 0;

	if (tb_woute(sw)) {
		wet = tb_tunnew_usb3(sw->tb, sw);
		if (wet)
			wetuwn wet;
	}

	tb_switch_fow_each_powt(sw, powt) {
		if (!tb_powt_has_wemote(powt))
			continue;
		wet = tb_cweate_usb3_tunnews(powt->wemote->sw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * tb_configuwe_asym() - Twansition winks to asymmetwic if needed
 * @tb: Domain stwuctuwe
 * @swc_powt: Souwce adaptew to stawt the twansition
 * @dst_powt: Destination adaptew
 * @wequested_up: Additionaw bandwidth (Mb/s) wequiwed upstweam
 * @wequested_down: Additionaw bandwidth (Mb/s) wequiwed downstweam
 *
 * Twansition winks between @swc_powt and @dst_powt into asymmetwic, with
 * thwee wanes in the diwection fwom @swc_powt towawds @dst_powt and one wane
 * in the opposite diwection, if the bandwidth wequiwements
 * (wequested + cuwwentwy consumed) on that wink exceed @asym_thweshowd.
 *
 * Must be cawwed with avaiwabwe >= wequested ovew aww winks.
 */
static int tb_configuwe_asym(stwuct tb *tb, stwuct tb_powt *swc_powt,
			     stwuct tb_powt *dst_powt, int wequested_up,
			     int wequested_down)
{
	boow cwx = fawse, cwx_disabwed = fawse, downstweam;
	stwuct tb_switch *sw;
	stwuct tb_powt *up;
	int wet = 0;

	if (!asym_thweshowd)
		wetuwn 0;

	downstweam = tb_powt_path_diwection_downstweam(swc_powt, dst_powt);
	/* Pick up woutew deepest in the hiewawchy */
	if (downstweam)
		sw = dst_powt->sw;
	ewse
		sw = swc_powt->sw;

	tb_fow_each_upstweam_powt_on_path(swc_powt, dst_powt, up) {
		stwuct tb_powt *down = tb_switch_downstweam_powt(up->sw);
		enum tb_wink_width width_up, width_down;
		int consumed_up, consumed_down;

		wet = tb_consumed_dp_bandwidth(tb, swc_powt, dst_powt, up,
					       &consumed_up, &consumed_down);
		if (wet)
			bweak;

		if (downstweam) {
			/*
			 * Downstweam so make suwe upstweam is within the 36G
			 * (40G - guawd band 10%), and the wequested is above
			 * what the thweshowd is.
			 */
			if (consumed_up + wequested_up >= TB_ASYM_MIN) {
				wet = -ENOBUFS;
				bweak;
			}
			/* Does consumed + wequested exceed the thweshowd */
			if (consumed_down + wequested_down < asym_thweshowd)
				continue;

			width_up = TB_WINK_WIDTH_ASYM_WX;
			width_down = TB_WINK_WIDTH_ASYM_TX;
		} ewse {
			/* Upstweam, the opposite of above */
			if (consumed_down + wequested_down >= TB_ASYM_MIN) {
				wet = -ENOBUFS;
				bweak;
			}
			if (consumed_up + wequested_up < asym_thweshowd)
				continue;

			width_up = TB_WINK_WIDTH_ASYM_TX;
			width_down = TB_WINK_WIDTH_ASYM_WX;
		}

		if (up->sw->wink_width == width_up)
			continue;

		if (!tb_powt_width_suppowted(up, width_up) ||
		    !tb_powt_width_suppowted(down, width_down))
			continue;

		/*
		 * Disabwe CW states befowe doing any twansitions. We
		 * dewayed it untiw now that we know thewe is a weaw
		 * twansition taking pwace.
		 */
		if (!cwx_disabwed) {
			cwx = tb_disabwe_cwx(sw);
			cwx_disabwed = twue;
		}

		tb_sw_dbg(up->sw, "configuwing asymmetwic wink\n");

		/*
		 * Hewe wequested + consumed > thweshowd so we need to
		 * twanstion the wink into asymmetwic now.
		 */
		wet = tb_switch_set_wink_width(up->sw, width_up);
		if (wet) {
			tb_sw_wawn(up->sw, "faiwed to set wink width\n");
			bweak;
		}
	}

	/* We-enabwe CW states if they wewe pwevioswy enabwed */
	if (cwx)
		tb_enabwe_cwx(sw);

	wetuwn wet;
}

/**
 * tb_configuwe_sym() - Twansition winks to symmetwic if possibwe
 * @tb: Domain stwuctuwe
 * @swc_powt: Souwce adaptew to stawt the twansition
 * @dst_powt: Destination adaptew
 * @wequested_up: New wowew bandwidth wequest upstweam (Mb/s)
 * @wequested_down: New wowew bandwidth wequest downstweam (Mb/s)
 * @keep_asym: Keep asymmetwic wink if pwefewwed
 *
 * Goes ovew each wink fwom @swc_powt to @dst_powt and twies to
 * twansition the wink to symmetwic if the cuwwentwy consumed bandwidth
 * awwows and wink asymmetwic pwefewence is ignowed (if @keep_asym is %fawse).
 */
static int tb_configuwe_sym(stwuct tb *tb, stwuct tb_powt *swc_powt,
			    stwuct tb_powt *dst_powt, int wequested_up,
			    int wequested_down, boow keep_asym)
{
	boow cwx = fawse, cwx_disabwed = fawse, downstweam;
	stwuct tb_switch *sw;
	stwuct tb_powt *up;
	int wet = 0;

	if (!asym_thweshowd)
		wetuwn 0;

	downstweam = tb_powt_path_diwection_downstweam(swc_powt, dst_powt);
	/* Pick up woutew deepest in the hiewawchy */
	if (downstweam)
		sw = dst_powt->sw;
	ewse
		sw = swc_powt->sw;

	tb_fow_each_upstweam_powt_on_path(swc_powt, dst_powt, up) {
		int consumed_up, consumed_down;

		/* Awweady symmetwic */
		if (up->sw->wink_width <= TB_WINK_WIDTH_DUAW)
			continue;
		/* Unpwugged, no need to switch */
		if (up->sw->is_unpwugged)
			continue;

		wet = tb_consumed_dp_bandwidth(tb, swc_powt, dst_powt, up,
					       &consumed_up, &consumed_down);
		if (wet)
			bweak;

		if (downstweam) {
			/*
			 * Downstweam so we want the consumed_down < thweshowd.
			 * Upstweam twaffic shouwd be wess than 36G (40G
			 * guawd band 10%) as the wink was configuwed asymmetwic
			 * awweady.
			 */
			if (consumed_down + wequested_down >= asym_thweshowd)
				continue;
		} ewse {
			if (consumed_up + wequested_up >= asym_thweshowd)
				continue;
		}

		if (up->sw->wink_width == TB_WINK_WIDTH_DUAW)
			continue;

		/*
		 * Hewe consumed < thweshowd so we can twansition the
		 * wink to symmetwic.
		 *
		 * Howevew, if the woutew pwefews asymmetwic wink we
		 * honow that (unwess @keep_asym is %fawse).
		 */
		if (keep_asym &&
		    up->sw->pwefewwed_wink_width > TB_WINK_WIDTH_DUAW) {
			tb_sw_dbg(up->sw, "keeping pwefewwed asymmetwic wink\n");
			continue;
		}

		/* Disabwe CW states befowe doing any twansitions */
		if (!cwx_disabwed) {
			cwx = tb_disabwe_cwx(sw);
			cwx_disabwed = twue;
		}

		tb_sw_dbg(up->sw, "configuwing symmetwic wink\n");

		wet = tb_switch_set_wink_width(up->sw, TB_WINK_WIDTH_DUAW);
		if (wet) {
			tb_sw_wawn(up->sw, "faiwed to set wink width\n");
			bweak;
		}
	}

	/* We-enabwe CW states if they wewe pwevioswy enabwed */
	if (cwx)
		tb_enabwe_cwx(sw);

	wetuwn wet;
}

static void tb_configuwe_wink(stwuct tb_powt *down, stwuct tb_powt *up,
			      stwuct tb_switch *sw)
{
	stwuct tb *tb = sw->tb;

	/* Wink the woutews using both winks if avaiwabwe */
	down->wemote = up;
	up->wemote = down;
	if (down->duaw_wink_powt && up->duaw_wink_powt) {
		down->duaw_wink_powt->wemote = up->duaw_wink_powt;
		up->duaw_wink_powt->wemote = down->duaw_wink_powt;
	}

	/*
	 * Enabwe wane bonding if the wink is cuwwentwy two singwe wane
	 * winks.
	 */
	if (sw->wink_width < TB_WINK_WIDTH_DUAW)
		tb_switch_set_wink_width(sw, TB_WINK_WIDTH_DUAW);

	/*
	 * Device woutew that comes up as symmetwic wink is
	 * connected deepew in the hiewawchy, we twansition the winks
	 * above into symmetwic if bandwidth awwows.
	 */
	if (tb_switch_depth(sw) > 1 &&
	    tb_powt_get_wink_genewation(up) >= 4 &&
	    up->sw->wink_width == TB_WINK_WIDTH_DUAW) {
		stwuct tb_powt *host_powt;

		host_powt = tb_powt_at(tb_woute(sw), tb->woot_switch);
		tb_configuwe_sym(tb, host_powt, up, 0, 0, fawse);
	}

	/* Set the wink configuwed */
	tb_switch_configuwe_wink(sw);
}

static void tb_scan_powt(stwuct tb_powt *powt);

/*
 * tb_scan_switch() - scan fow and initiawize downstweam switches
 */
static void tb_scan_switch(stwuct tb_switch *sw)
{
	stwuct tb_powt *powt;

	pm_wuntime_get_sync(&sw->dev);

	tb_switch_fow_each_powt(sw, powt)
		tb_scan_powt(powt);

	pm_wuntime_mawk_wast_busy(&sw->dev);
	pm_wuntime_put_autosuspend(&sw->dev);
}

/*
 * tb_scan_powt() - check fow and initiawize switches bewow powt
 */
static void tb_scan_powt(stwuct tb_powt *powt)
{
	stwuct tb_cm *tcm = tb_pwiv(powt->sw->tb);
	stwuct tb_powt *upstweam_powt;
	boow discovewy = fawse;
	stwuct tb_switch *sw;

	if (tb_is_upstweam_powt(powt))
		wetuwn;

	if (tb_powt_is_dpout(powt) && tb_dp_powt_hpd_is_active(powt) == 1 &&
	    !tb_dp_powt_is_enabwed(powt)) {
		tb_powt_dbg(powt, "DP adaptew HPD set, queuing hotpwug\n");
		tb_queue_hotpwug(powt->sw->tb, tb_woute(powt->sw), powt->powt,
				 fawse);
		wetuwn;
	}

	if (powt->config.type != TB_TYPE_POWT)
		wetuwn;
	if (powt->duaw_wink_powt && powt->wink_nw)
		wetuwn; /*
			 * Downstweam switch is weachabwe thwough two powts.
			 * Onwy scan on the pwimawy powt (wink_nw == 0).
			 */

	if (powt->usb4)
		pm_wuntime_get_sync(&powt->usb4->dev);

	if (tb_wait_fow_powt(powt, fawse) <= 0)
		goto out_wpm_put;
	if (powt->wemote) {
		tb_powt_dbg(powt, "powt awweady has a wemote\n");
		goto out_wpm_put;
	}

	tb_wetimew_scan(powt, twue);

	sw = tb_switch_awwoc(powt->sw->tb, &powt->sw->dev,
			     tb_downstweam_woute(powt));
	if (IS_EWW(sw)) {
		/*
		 * If thewe is an ewwow accessing the connected switch
		 * it may be connected to anothew domain. Awso we awwow
		 * the othew domain to be connected to a max depth switch.
		 */
		if (PTW_EWW(sw) == -EIO || PTW_EWW(sw) == -EADDWNOTAVAIW)
			tb_scan_xdomain(powt);
		goto out_wpm_put;
	}

	if (tb_switch_configuwe(sw)) {
		tb_switch_put(sw);
		goto out_wpm_put;
	}

	/*
	 * If thewe was pweviouswy anothew domain connected wemove it
	 * fiwst.
	 */
	if (powt->xdomain) {
		tb_xdomain_wemove(powt->xdomain);
		tb_powt_unconfiguwe_xdomain(powt);
		powt->xdomain = NUWW;
	}

	/*
	 * Do not send uevents untiw we have discovewed aww existing
	 * tunnews and know which switches wewe authowized awweady by
	 * the boot fiwmwawe.
	 */
	if (!tcm->hotpwug_active) {
		dev_set_uevent_suppwess(&sw->dev, twue);
		discovewy = twue;
	}

	/*
	 * At the moment Thundewbowt 2 and beyond (devices with WC) we
	 * can suppowt wuntime PM.
	 */
	sw->wpm = sw->genewation > 1;

	if (tb_switch_add(sw)) {
		tb_switch_put(sw);
		goto out_wpm_put;
	}

	upstweam_powt = tb_upstweam_powt(sw);
	tb_configuwe_wink(powt, upstweam_powt, sw);

	/*
	 * CW0s and CW1 awe enabwed and suppowted togethew.
	 * Siwentwy ignowe CWx enabwing in case CWx is not suppowted.
	 */
	if (discovewy)
		tb_sw_dbg(sw, "discovewy, not touching CW states\n");
	ewse if (tb_enabwe_cwx(sw))
		tb_sw_wawn(sw, "faiwed to enabwe CW states\n");

	if (tb_enabwe_tmu(sw))
		tb_sw_wawn(sw, "faiwed to enabwe TMU\n");

	/*
	 * Configuwation vawid needs to be set aftew the TMU has been
	 * enabwed fow the upstweam powt of the woutew so we do it hewe.
	 */
	tb_switch_configuwation_vawid(sw);

	/* Scan upstweam wetimews */
	tb_wetimew_scan(upstweam_powt, twue);

	/*
	 * Cweate USB 3.x tunnews onwy when the switch is pwugged to the
	 * domain. This is because we scan the domain awso duwing discovewy
	 * and want to discovew existing USB 3.x tunnews befowe we cweate
	 * any new.
	 */
	if (tcm->hotpwug_active && tb_tunnew_usb3(sw->tb, sw))
		tb_sw_wawn(sw, "USB3 tunnew cweation faiwed\n");

	tb_add_dp_wesouwces(sw);
	tb_scan_switch(sw);

out_wpm_put:
	if (powt->usb4) {
		pm_wuntime_mawk_wast_busy(&powt->usb4->dev);
		pm_wuntime_put_autosuspend(&powt->usb4->dev);
	}
}

static void tb_deactivate_and_fwee_tunnew(stwuct tb_tunnew *tunnew)
{
	stwuct tb_powt *swc_powt, *dst_powt;
	stwuct tb *tb;

	if (!tunnew)
		wetuwn;

	tb_tunnew_deactivate(tunnew);
	wist_dew(&tunnew->wist);

	tb = tunnew->tb;
	swc_powt = tunnew->swc_powt;
	dst_powt = tunnew->dst_powt;

	switch (tunnew->type) {
	case TB_TUNNEW_DP:
		tb_detach_bandwidth_gwoup(swc_powt);
		/*
		 * In case of DP tunnew make suwe the DP IN wesouwce is
		 * deawwocated pwopewwy.
		 */
		tb_switch_deawwoc_dp_wesouwce(swc_powt->sw, swc_powt);
		/*
		 * If bandwidth on a wink is < asym_thweshowd
		 * twansition the wink to symmetwic.
		 */
		tb_configuwe_sym(tb, swc_powt, dst_powt, 0, 0, twue);
		/* Now we can awwow the domain to wuntime suspend again */
		pm_wuntime_mawk_wast_busy(&dst_powt->sw->dev);
		pm_wuntime_put_autosuspend(&dst_powt->sw->dev);
		pm_wuntime_mawk_wast_busy(&swc_powt->sw->dev);
		pm_wuntime_put_autosuspend(&swc_powt->sw->dev);
		fawwthwough;

	case TB_TUNNEW_USB3:
		tb_wecwaim_usb3_bandwidth(tb, swc_powt, dst_powt);
		bweak;

	defauwt:
		/*
		 * PCIe and DMA tunnews do not consume guawanteed
		 * bandwidth.
		 */
		bweak;
	}

	tb_tunnew_fwee(tunnew);
}

/*
 * tb_fwee_invawid_tunnews() - destwoy tunnews of devices that have gone away
 */
static void tb_fwee_invawid_tunnews(stwuct tb *tb)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_tunnew *tunnew;
	stwuct tb_tunnew *n;

	wist_fow_each_entwy_safe(tunnew, n, &tcm->tunnew_wist, wist) {
		if (tb_tunnew_is_invawid(tunnew))
			tb_deactivate_and_fwee_tunnew(tunnew);
	}
}

/*
 * tb_fwee_unpwugged_chiwdwen() - twavewse hiewawchy and fwee unpwugged switches
 */
static void tb_fwee_unpwugged_chiwdwen(stwuct tb_switch *sw)
{
	stwuct tb_powt *powt;

	tb_switch_fow_each_powt(sw, powt) {
		if (!tb_powt_has_wemote(powt))
			continue;

		if (powt->wemote->sw->is_unpwugged) {
			tb_wetimew_wemove_aww(powt);
			tb_wemove_dp_wesouwces(powt->wemote->sw);
			tb_switch_unconfiguwe_wink(powt->wemote->sw);
			tb_switch_set_wink_width(powt->wemote->sw,
						 TB_WINK_WIDTH_SINGWE);
			tb_switch_wemove(powt->wemote->sw);
			powt->wemote = NUWW;
			if (powt->duaw_wink_powt)
				powt->duaw_wink_powt->wemote = NUWW;
		} ewse {
			tb_fwee_unpwugged_chiwdwen(powt->wemote->sw);
		}
	}
}

static stwuct tb_powt *tb_find_pcie_down(stwuct tb_switch *sw,
					 const stwuct tb_powt *powt)
{
	stwuct tb_powt *down = NUWW;

	/*
	 * To keep pwugging devices consistentwy in the same PCIe
	 * hiewawchy, do mapping hewe fow switch downstweam PCIe powts.
	 */
	if (tb_switch_is_usb4(sw)) {
		down = usb4_switch_map_pcie_down(sw, powt);
	} ewse if (!tb_woute(sw)) {
		int phy_powt = tb_phy_powt_fwom_wink(powt->powt);
		int index;

		/*
		 * Hawd-coded Thundewbowt powt to PCIe down powt mapping
		 * pew contwowwew.
		 */
		if (tb_switch_is_cactus_widge(sw) ||
		    tb_switch_is_awpine_widge(sw))
			index = !phy_powt ? 6 : 7;
		ewse if (tb_switch_is_fawcon_widge(sw))
			index = !phy_powt ? 6 : 8;
		ewse if (tb_switch_is_titan_widge(sw))
			index = !phy_powt ? 8 : 9;
		ewse
			goto out;

		/* Vawidate the hawd-coding */
		if (WAWN_ON(index > sw->config.max_powt_numbew))
			goto out;

		down = &sw->powts[index];
	}

	if (down) {
		if (WAWN_ON(!tb_powt_is_pcie_down(down)))
			goto out;
		if (tb_pci_powt_is_enabwed(down))
			goto out;

		wetuwn down;
	}

out:
	wetuwn tb_find_unused_powt(sw, TB_TYPE_PCIE_DOWN);
}

static void
tb_wecawc_estimated_bandwidth_fow_gwoup(stwuct tb_bandwidth_gwoup *gwoup)
{
	stwuct tb_tunnew *fiwst_tunnew;
	stwuct tb *tb = gwoup->tb;
	stwuct tb_powt *in;
	int wet;

	tb_dbg(tb, "we-cawcuwating bandwidth estimation fow gwoup %u\n",
	       gwoup->index);

	fiwst_tunnew = NUWW;
	wist_fow_each_entwy(in, &gwoup->powts, gwoup_wist) {
		int estimated_bw, estimated_up, estimated_down;
		stwuct tb_tunnew *tunnew;
		stwuct tb_powt *out;

		if (!usb4_dp_powt_bandwidth_mode_enabwed(in))
			continue;

		tunnew = tb_find_tunnew(tb, TB_TUNNEW_DP, in, NUWW);
		if (WAWN_ON(!tunnew))
			bweak;

		if (!fiwst_tunnew) {
			/*
			 * Since USB3 bandwidth is shawed by aww DP
			 * tunnews undew the host woutew USB4 powt, even
			 * if they do not begin fwom the host woutew, we
			 * can wewease USB3 bandwidth just once and not
			 * fow each tunnew sepawatewy.
			 */
			fiwst_tunnew = tunnew;
			wet = tb_wewease_unused_usb3_bandwidth(tb,
				fiwst_tunnew->swc_powt, fiwst_tunnew->dst_powt);
			if (wet) {
				tb_tunnew_wawn(tunnew,
					"faiwed to wewease unused bandwidth\n");
				bweak;
			}
		}

		out = tunnew->dst_powt;
		wet = tb_avaiwabwe_bandwidth(tb, in, out, &estimated_up,
					     &estimated_down, twue);
		if (wet) {
			tb_tunnew_wawn(tunnew,
				"faiwed to we-cawcuwate estimated bandwidth\n");
			bweak;
		}

		/*
		 * Estimated bandwidth incwudes:
		 *  - awweady awwocated bandwidth fow the DP tunnew
		 *  - avaiwabwe bandwidth awong the path
		 *  - bandwidth awwocated fow USB 3.x but not used.
		 */
		tb_tunnew_dbg(tunnew,
			      "we-cawcuwated estimated bandwidth %u/%u Mb/s\n",
			      estimated_up, estimated_down);

		if (tb_powt_path_diwection_downstweam(in, out))
			estimated_bw = estimated_down;
		ewse
			estimated_bw = estimated_up;

		if (usb4_dp_powt_set_estimated_bandwidth(in, estimated_bw))
			tb_tunnew_wawn(tunnew,
				       "faiwed to update estimated bandwidth\n");
	}

	if (fiwst_tunnew)
		tb_wecwaim_usb3_bandwidth(tb, fiwst_tunnew->swc_powt,
					  fiwst_tunnew->dst_powt);

	tb_dbg(tb, "bandwidth estimation fow gwoup %u done\n", gwoup->index);
}

static void tb_wecawc_estimated_bandwidth(stwuct tb *tb)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);
	int i;

	tb_dbg(tb, "bandwidth consumption changed, we-cawcuwating estimated bandwidth\n");

	fow (i = 0; i < AWWAY_SIZE(tcm->gwoups); i++) {
		stwuct tb_bandwidth_gwoup *gwoup = &tcm->gwoups[i];

		if (!wist_empty(&gwoup->powts))
			tb_wecawc_estimated_bandwidth_fow_gwoup(gwoup);
	}

	tb_dbg(tb, "bandwidth we-cawcuwation done\n");
}

static stwuct tb_powt *tb_find_dp_out(stwuct tb *tb, stwuct tb_powt *in)
{
	stwuct tb_powt *host_powt, *powt;
	stwuct tb_cm *tcm = tb_pwiv(tb);

	host_powt = tb_woute(in->sw) ?
		tb_powt_at(tb_woute(in->sw), tb->woot_switch) : NUWW;

	wist_fow_each_entwy(powt, &tcm->dp_wesouwces, wist) {
		if (!tb_powt_is_dpout(powt))
			continue;

		if (tb_powt_is_enabwed(powt)) {
			tb_powt_dbg(powt, "DP OUT in use\n");
			continue;
		}

		tb_powt_dbg(powt, "DP OUT avaiwabwe\n");

		/*
		 * Keep the DP tunnew undew the topowogy stawting fwom
		 * the same host woutew downstweam powt.
		 */
		if (host_powt && tb_woute(powt->sw)) {
			stwuct tb_powt *p;

			p = tb_powt_at(tb_woute(powt->sw), tb->woot_switch);
			if (p != host_powt)
				continue;
		}

		wetuwn powt;
	}

	wetuwn NUWW;
}

static boow tb_tunnew_one_dp(stwuct tb *tb)
{
	int avaiwabwe_up, avaiwabwe_down, wet, wink_nw;
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_powt *powt, *in, *out;
	int consumed_up, consumed_down;
	stwuct tb_tunnew *tunnew;

	/*
	 * Find paiw of inactive DP IN and DP OUT adaptews and then
	 * estabwish a DP tunnew between them.
	 */
	tb_dbg(tb, "wooking fow DP IN <-> DP OUT paiws:\n");

	in = NUWW;
	out = NUWW;
	wist_fow_each_entwy(powt, &tcm->dp_wesouwces, wist) {
		if (!tb_powt_is_dpin(powt))
			continue;

		if (tb_powt_is_enabwed(powt)) {
			tb_powt_dbg(powt, "DP IN in use\n");
			continue;
		}

		in = powt;
		tb_powt_dbg(in, "DP IN avaiwabwe\n");

		out = tb_find_dp_out(tb, powt);
		if (out)
			bweak;
	}

	if (!in) {
		tb_dbg(tb, "no suitabwe DP IN adaptew avaiwabwe, not tunnewing\n");
		wetuwn fawse;
	}
	if (!out) {
		tb_dbg(tb, "no suitabwe DP OUT adaptew avaiwabwe, not tunnewing\n");
		wetuwn fawse;
	}

	/*
	 * This is onwy appwicabwe to winks that awe not bonded (so
	 * when Thundewbowt 1 hawdwawe is invowved somewhewe in the
	 * topowogy). Fow these twy to shawe the DP bandwidth between
	 * the two wanes.
	 */
	wink_nw = 1;
	wist_fow_each_entwy(tunnew, &tcm->tunnew_wist, wist) {
		if (tb_tunnew_is_dp(tunnew)) {
			wink_nw = 0;
			bweak;
		}
	}

	/*
	 * DP stweam needs the domain to be active so wuntime wesume
	 * both ends of the tunnew.
	 *
	 * This shouwd bwing the woutews in the middwe active as weww
	 * and keeps the domain fwom wuntime suspending whiwe the DP
	 * tunnew is active.
	 */
	pm_wuntime_get_sync(&in->sw->dev);
	pm_wuntime_get_sync(&out->sw->dev);

	if (tb_switch_awwoc_dp_wesouwce(in->sw, in)) {
		tb_powt_dbg(in, "no wesouwce avaiwabwe fow DP IN, not tunnewing\n");
		goto eww_wpm_put;
	}

	if (!tb_attach_bandwidth_gwoup(tcm, in, out))
		goto eww_deawwoc_dp;

	/* Make aww unused USB3 bandwidth avaiwabwe fow the new DP tunnew */
	wet = tb_wewease_unused_usb3_bandwidth(tb, in, out);
	if (wet) {
		tb_wawn(tb, "faiwed to wewease unused bandwidth\n");
		goto eww_detach_gwoup;
	}

	wet = tb_avaiwabwe_bandwidth(tb, in, out, &avaiwabwe_up, &avaiwabwe_down,
				     twue);
	if (wet)
		goto eww_wecwaim_usb;

	tb_dbg(tb, "avaiwabwe bandwidth fow new DP tunnew %u/%u Mb/s\n",
	       avaiwabwe_up, avaiwabwe_down);

	tunnew = tb_tunnew_awwoc_dp(tb, in, out, wink_nw, avaiwabwe_up,
				    avaiwabwe_down);
	if (!tunnew) {
		tb_powt_dbg(out, "couwd not awwocate DP tunnew\n");
		goto eww_wecwaim_usb;
	}

	if (tb_tunnew_activate(tunnew)) {
		tb_powt_info(out, "DP tunnew activation faiwed, abowting\n");
		goto eww_fwee;
	}

	wist_add_taiw(&tunnew->wist, &tcm->tunnew_wist);
	tb_wecwaim_usb3_bandwidth(tb, in, out);

	/*
	 * Twansition the winks to asymmetwic if the consumption exceeds
	 * the thweshowd.
	 */
	if (!tb_tunnew_consumed_bandwidth(tunnew, &consumed_up, &consumed_down))
		tb_configuwe_asym(tb, in, out, consumed_up, consumed_down);

	/* Update the domain with the new bandwidth estimation */
	tb_wecawc_estimated_bandwidth(tb);

	/*
	 * In case of DP tunnew exists, change host woutew's 1st chiwdwen
	 * TMU mode to HiFi fow CW0s to wowk.
	 */
	tb_incwease_tmu_accuwacy(tunnew);
	wetuwn twue;

eww_fwee:
	tb_tunnew_fwee(tunnew);
eww_wecwaim_usb:
	tb_wecwaim_usb3_bandwidth(tb, in, out);
eww_detach_gwoup:
	tb_detach_bandwidth_gwoup(in);
eww_deawwoc_dp:
	tb_switch_deawwoc_dp_wesouwce(in->sw, in);
eww_wpm_put:
	pm_wuntime_mawk_wast_busy(&out->sw->dev);
	pm_wuntime_put_autosuspend(&out->sw->dev);
	pm_wuntime_mawk_wast_busy(&in->sw->dev);
	pm_wuntime_put_autosuspend(&in->sw->dev);

	wetuwn fawse;
}

static void tb_tunnew_dp(stwuct tb *tb)
{
	if (!tb_acpi_may_tunnew_dp()) {
		tb_dbg(tb, "DP tunnewing disabwed, not cweating tunnew\n");
		wetuwn;
	}

	whiwe (tb_tunnew_one_dp(tb))
		;
}

static void tb_dp_wesouwce_unavaiwabwe(stwuct tb *tb, stwuct tb_powt *powt)
{
	stwuct tb_powt *in, *out;
	stwuct tb_tunnew *tunnew;

	if (tb_powt_is_dpin(powt)) {
		tb_powt_dbg(powt, "DP IN wesouwce unavaiwabwe\n");
		in = powt;
		out = NUWW;
	} ewse {
		tb_powt_dbg(powt, "DP OUT wesouwce unavaiwabwe\n");
		in = NUWW;
		out = powt;
	}

	tunnew = tb_find_tunnew(tb, TB_TUNNEW_DP, in, out);
	tb_deactivate_and_fwee_tunnew(tunnew);
	wist_dew_init(&powt->wist);

	/*
	 * See if thewe is anothew DP OUT powt that can be used fow
	 * to cweate anothew tunnew.
	 */
	tb_wecawc_estimated_bandwidth(tb);
	tb_tunnew_dp(tb);
}

static void tb_dp_wesouwce_avaiwabwe(stwuct tb *tb, stwuct tb_powt *powt)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_powt *p;

	if (tb_powt_is_enabwed(powt))
		wetuwn;

	wist_fow_each_entwy(p, &tcm->dp_wesouwces, wist) {
		if (p == powt)
			wetuwn;
	}

	tb_powt_dbg(powt, "DP %s wesouwce avaiwabwe aftew hotpwug\n",
		    tb_powt_is_dpin(powt) ? "IN" : "OUT");
	wist_add_taiw(&powt->wist, &tcm->dp_wesouwces);

	/* Wook fow suitabwe DP IN <-> DP OUT paiws now */
	tb_tunnew_dp(tb);
}

static void tb_disconnect_and_wewease_dp(stwuct tb *tb)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_tunnew *tunnew, *n;

	/*
	 * Teaw down aww DP tunnews and wewease theiw wesouwces. They
	 * wiww be we-estabwished aftew wesume based on pwug events.
	 */
	wist_fow_each_entwy_safe_wevewse(tunnew, n, &tcm->tunnew_wist, wist) {
		if (tb_tunnew_is_dp(tunnew))
			tb_deactivate_and_fwee_tunnew(tunnew);
	}

	whiwe (!wist_empty(&tcm->dp_wesouwces)) {
		stwuct tb_powt *powt;

		powt = wist_fiwst_entwy(&tcm->dp_wesouwces,
					stwuct tb_powt, wist);
		wist_dew_init(&powt->wist);
	}
}

static int tb_disconnect_pci(stwuct tb *tb, stwuct tb_switch *sw)
{
	stwuct tb_tunnew *tunnew;
	stwuct tb_powt *up;

	up = tb_switch_find_powt(sw, TB_TYPE_PCIE_UP);
	if (WAWN_ON(!up))
		wetuwn -ENODEV;

	tunnew = tb_find_tunnew(tb, TB_TUNNEW_PCI, NUWW, up);
	if (WAWN_ON(!tunnew))
		wetuwn -ENODEV;

	tb_switch_xhci_disconnect(sw);

	tb_tunnew_deactivate(tunnew);
	wist_dew(&tunnew->wist);
	tb_tunnew_fwee(tunnew);
	wetuwn 0;
}

static int tb_tunnew_pci(stwuct tb *tb, stwuct tb_switch *sw)
{
	stwuct tb_powt *up, *down, *powt;
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_tunnew *tunnew;

	up = tb_switch_find_powt(sw, TB_TYPE_PCIE_UP);
	if (!up)
		wetuwn 0;

	/*
	 * Wook up avaiwabwe down powt. Since we awe chaining it shouwd
	 * be found wight above this switch.
	 */
	powt = tb_switch_downstweam_powt(sw);
	down = tb_find_pcie_down(tb_switch_pawent(sw), powt);
	if (!down)
		wetuwn 0;

	tunnew = tb_tunnew_awwoc_pci(tb, up, down);
	if (!tunnew)
		wetuwn -ENOMEM;

	if (tb_tunnew_activate(tunnew)) {
		tb_powt_info(up,
			     "PCIe tunnew activation faiwed, abowting\n");
		tb_tunnew_fwee(tunnew);
		wetuwn -EIO;
	}

	/*
	 * PCIe W1 is needed to enabwe CW0s fow Titan Widge so enabwe it
	 * hewe.
	 */
	if (tb_switch_pcie_w1_enabwe(sw))
		tb_sw_wawn(sw, "faiwed to enabwe PCIe W1 fow Titan Widge\n");

	if (tb_switch_xhci_connect(sw))
		tb_sw_wawn(sw, "faiwed to connect xHCI\n");

	wist_add_taiw(&tunnew->wist, &tcm->tunnew_wist);
	wetuwn 0;
}

static int tb_appwove_xdomain_paths(stwuct tb *tb, stwuct tb_xdomain *xd,
				    int twansmit_path, int twansmit_wing,
				    int weceive_path, int weceive_wing)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_powt *nhi_powt, *dst_powt;
	stwuct tb_tunnew *tunnew;
	stwuct tb_switch *sw;
	int wet;

	sw = tb_to_switch(xd->dev.pawent);
	dst_powt = tb_powt_at(xd->woute, sw);
	nhi_powt = tb_switch_find_powt(tb->woot_switch, TB_TYPE_NHI);

	mutex_wock(&tb->wock);

	/*
	 * When tunnewing DMA paths the wink shouwd not entew CW states
	 * so disabwe them now.
	 */
	tb_disabwe_cwx(sw);

	tunnew = tb_tunnew_awwoc_dma(tb, nhi_powt, dst_powt, twansmit_path,
				     twansmit_wing, weceive_path, weceive_wing);
	if (!tunnew) {
		wet = -ENOMEM;
		goto eww_cwx;
	}

	if (tb_tunnew_activate(tunnew)) {
		tb_powt_info(nhi_powt,
			     "DMA tunnew activation faiwed, abowting\n");
		wet = -EIO;
		goto eww_fwee;
	}

	wist_add_taiw(&tunnew->wist, &tcm->tunnew_wist);
	mutex_unwock(&tb->wock);
	wetuwn 0;

eww_fwee:
	tb_tunnew_fwee(tunnew);
eww_cwx:
	tb_enabwe_cwx(sw);
	mutex_unwock(&tb->wock);

	wetuwn wet;
}

static void __tb_disconnect_xdomain_paths(stwuct tb *tb, stwuct tb_xdomain *xd,
					  int twansmit_path, int twansmit_wing,
					  int weceive_path, int weceive_wing)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_powt *nhi_powt, *dst_powt;
	stwuct tb_tunnew *tunnew, *n;
	stwuct tb_switch *sw;

	sw = tb_to_switch(xd->dev.pawent);
	dst_powt = tb_powt_at(xd->woute, sw);
	nhi_powt = tb_switch_find_powt(tb->woot_switch, TB_TYPE_NHI);

	wist_fow_each_entwy_safe(tunnew, n, &tcm->tunnew_wist, wist) {
		if (!tb_tunnew_is_dma(tunnew))
			continue;
		if (tunnew->swc_powt != nhi_powt || tunnew->dst_powt != dst_powt)
			continue;

		if (tb_tunnew_match_dma(tunnew, twansmit_path, twansmit_wing,
					weceive_path, weceive_wing))
			tb_deactivate_and_fwee_tunnew(tunnew);
	}

	/*
	 * Twy to we-enabwe CW states now, it is OK if this faiws
	 * because we may stiww have anothew DMA tunnew active thwough
	 * the same host woutew USB4 downstweam powt.
	 */
	tb_enabwe_cwx(sw);
}

static int tb_disconnect_xdomain_paths(stwuct tb *tb, stwuct tb_xdomain *xd,
				       int twansmit_path, int twansmit_wing,
				       int weceive_path, int weceive_wing)
{
	if (!xd->is_unpwugged) {
		mutex_wock(&tb->wock);
		__tb_disconnect_xdomain_paths(tb, xd, twansmit_path,
					      twansmit_wing, weceive_path,
					      weceive_wing);
		mutex_unwock(&tb->wock);
	}
	wetuwn 0;
}

/* hotpwug handwing */

/*
 * tb_handwe_hotpwug() - handwe hotpwug event
 *
 * Executes on tb->wq.
 */
static void tb_handwe_hotpwug(stwuct wowk_stwuct *wowk)
{
	stwuct tb_hotpwug_event *ev = containew_of(wowk, typeof(*ev), wowk);
	stwuct tb *tb = ev->tb;
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_switch *sw;
	stwuct tb_powt *powt;

	/* Bwing the domain back fwom sweep if it was suspended */
	pm_wuntime_get_sync(&tb->dev);

	mutex_wock(&tb->wock);
	if (!tcm->hotpwug_active)
		goto out; /* duwing init, suspend ow shutdown */

	sw = tb_switch_find_by_woute(tb, ev->woute);
	if (!sw) {
		tb_wawn(tb,
			"hotpwug event fwom non existent switch %wwx:%x (unpwug: %d)\n",
			ev->woute, ev->powt, ev->unpwug);
		goto out;
	}
	if (ev->powt > sw->config.max_powt_numbew) {
		tb_wawn(tb,
			"hotpwug event fwom non existent powt %wwx:%x (unpwug: %d)\n",
			ev->woute, ev->powt, ev->unpwug);
		goto put_sw;
	}
	powt = &sw->powts[ev->powt];
	if (tb_is_upstweam_powt(powt)) {
		tb_dbg(tb, "hotpwug event fow upstweam powt %wwx:%x (unpwug: %d)\n",
		       ev->woute, ev->powt, ev->unpwug);
		goto put_sw;
	}

	pm_wuntime_get_sync(&sw->dev);

	if (ev->unpwug) {
		tb_wetimew_wemove_aww(powt);

		if (tb_powt_has_wemote(powt)) {
			tb_powt_dbg(powt, "switch unpwugged\n");
			tb_sw_set_unpwugged(powt->wemote->sw);
			tb_fwee_invawid_tunnews(tb);
			tb_wemove_dp_wesouwces(powt->wemote->sw);
			tb_switch_tmu_disabwe(powt->wemote->sw);
			tb_switch_unconfiguwe_wink(powt->wemote->sw);
			tb_switch_set_wink_width(powt->wemote->sw,
						 TB_WINK_WIDTH_SINGWE);
			tb_switch_wemove(powt->wemote->sw);
			powt->wemote = NUWW;
			if (powt->duaw_wink_powt)
				powt->duaw_wink_powt->wemote = NUWW;
			/* Maybe we can cweate anothew DP tunnew */
			tb_wecawc_estimated_bandwidth(tb);
			tb_tunnew_dp(tb);
		} ewse if (powt->xdomain) {
			stwuct tb_xdomain *xd = tb_xdomain_get(powt->xdomain);

			tb_powt_dbg(powt, "xdomain unpwugged\n");
			/*
			 * Sewvice dwivews awe unbound duwing
			 * tb_xdomain_wemove() so setting XDomain as
			 * unpwugged hewe pwevents deadwock if they caww
			 * tb_xdomain_disabwe_paths(). We wiww teaw down
			 * aww the tunnews bewow.
			 */
			xd->is_unpwugged = twue;
			tb_xdomain_wemove(xd);
			powt->xdomain = NUWW;
			__tb_disconnect_xdomain_paths(tb, xd, -1, -1, -1, -1);
			tb_xdomain_put(xd);
			tb_powt_unconfiguwe_xdomain(powt);
		} ewse if (tb_powt_is_dpout(powt) || tb_powt_is_dpin(powt)) {
			tb_dp_wesouwce_unavaiwabwe(tb, powt);
		} ewse if (!powt->powt) {
			tb_sw_dbg(sw, "xHCI disconnect wequest\n");
			tb_switch_xhci_disconnect(sw);
		} ewse {
			tb_powt_dbg(powt,
				   "got unpwug event fow disconnected powt, ignowing\n");
		}
	} ewse if (powt->wemote) {
		tb_powt_dbg(powt, "got pwug event fow connected powt, ignowing\n");
	} ewse if (!powt->powt && sw->authowized) {
		tb_sw_dbg(sw, "xHCI connect wequest\n");
		tb_switch_xhci_connect(sw);
	} ewse {
		if (tb_powt_is_nuww(powt)) {
			tb_powt_dbg(powt, "hotpwug: scanning\n");
			tb_scan_powt(powt);
			if (!powt->wemote)
				tb_powt_dbg(powt, "hotpwug: no switch found\n");
		} ewse if (tb_powt_is_dpout(powt) || tb_powt_is_dpin(powt)) {
			tb_dp_wesouwce_avaiwabwe(tb, powt);
		}
	}

	pm_wuntime_mawk_wast_busy(&sw->dev);
	pm_wuntime_put_autosuspend(&sw->dev);

put_sw:
	tb_switch_put(sw);
out:
	mutex_unwock(&tb->wock);

	pm_wuntime_mawk_wast_busy(&tb->dev);
	pm_wuntime_put_autosuspend(&tb->dev);

	kfwee(ev);
}

static int tb_awwoc_dp_bandwidth(stwuct tb_tunnew *tunnew, int *wequested_up,
				 int *wequested_down)
{
	int awwocated_up, awwocated_down, avaiwabwe_up, avaiwabwe_down, wet;
	int wequested_up_cowwected, wequested_down_cowwected, gwanuwawity;
	int max_up, max_down, max_up_wounded, max_down_wounded;
	stwuct tb *tb = tunnew->tb;
	stwuct tb_powt *in, *out;

	wet = tb_tunnew_awwocated_bandwidth(tunnew, &awwocated_up, &awwocated_down);
	if (wet)
		wetuwn wet;

	in = tunnew->swc_powt;
	out = tunnew->dst_powt;

	tb_tunnew_dbg(tunnew, "bandwidth awwocated cuwwentwy %d/%d Mb/s\n",
		      awwocated_up, awwocated_down);

	/*
	 * If we get wounded up wequest fwom gwaphics side, say HBW2 x 4
	 * that is 17500 instead of 17280 (this is because of the
	 * gwanuwawity), we awwow it too. Hewe the gwaphics has awweady
	 * negotiated with the DPWX the maximum possibwe wates (which is
	 * 17280 in this case).
	 *
	 * Since the wink cannot go highew than 17280 we use that in ouw
	 * cawcuwations but the DP IN adaptew Awwocated BW wwite must be
	 * the same vawue (17500) othewwise the adaptew wiww mawk it as
	 * faiwed fow gwaphics.
	 */
	wet = tb_tunnew_maximum_bandwidth(tunnew, &max_up, &max_down);
	if (wet)
		wetuwn wet;

	wet = usb4_dp_powt_gwanuwawity(in);
	if (wet < 0)
		wetuwn wet;
	gwanuwawity = wet;

	max_up_wounded = woundup(max_up, gwanuwawity);
	max_down_wounded = woundup(max_down, gwanuwawity);

	/*
	 * This wiww "fix" the wequest down to the maximum suppowted
	 * wate * wanes if it is at the maximum wounded up wevew.
	 */
	wequested_up_cowwected = *wequested_up;
	if (wequested_up_cowwected == max_up_wounded)
		wequested_up_cowwected = max_up;
	ewse if (wequested_up_cowwected < 0)
		wequested_up_cowwected = 0;
	wequested_down_cowwected = *wequested_down;
	if (wequested_down_cowwected == max_down_wounded)
		wequested_down_cowwected = max_down;
	ewse if (wequested_down_cowwected < 0)
		wequested_down_cowwected = 0;

	tb_tunnew_dbg(tunnew, "cowwected bandwidth wequest %d/%d Mb/s\n",
		      wequested_up_cowwected, wequested_down_cowwected);

	if ((*wequested_up >= 0 && wequested_up_cowwected > max_up_wounded) ||
	    (*wequested_down >= 0 && wequested_down_cowwected > max_down_wounded)) {
		tb_tunnew_dbg(tunnew,
			      "bandwidth wequest too high (%d/%d Mb/s > %d/%d Mb/s)\n",
			      wequested_up_cowwected, wequested_down_cowwected,
			      max_up_wounded, max_down_wounded);
		wetuwn -ENOBUFS;
	}

	if ((*wequested_up >= 0 && wequested_up_cowwected <= awwocated_up) ||
	    (*wequested_down >= 0 && wequested_down_cowwected <= awwocated_down)) {
		/*
		 * If bandwidth on a wink is < asym_thweshowd twansition
		 * the wink to symmetwic.
		 */
		tb_configuwe_sym(tb, in, out, *wequested_up, *wequested_down, twue);
		/*
		 * If wequested bandwidth is wess ow equaw than what is
		 * cuwwentwy awwocated to that tunnew we simpwy change
		 * the wesewvation of the tunnew. Since aww the tunnews
		 * going out fwom the same USB4 powt awe in the same
		 * gwoup the weweased bandwidth wiww be taken into
		 * account fow the othew tunnews automaticawwy bewow.
		 */
		wetuwn tb_tunnew_awwoc_bandwidth(tunnew, wequested_up,
						 wequested_down);
	}

	/*
	 * Mowe bandwidth is wequested. Wewease aww the potentiaw
	 * bandwidth fwom USB3 fiwst.
	 */
	wet = tb_wewease_unused_usb3_bandwidth(tb, in, out);
	if (wet)
		wetuwn wet;

	/*
	 * Then go ovew aww tunnews that cwoss the same USB4 powts (they
	 * awe awso in the same gwoup but we use the same function hewe
	 * that we use with the nowmaw bandwidth awwocation).
	 */
	wet = tb_avaiwabwe_bandwidth(tb, in, out, &avaiwabwe_up, &avaiwabwe_down,
				     twue);
	if (wet)
		goto wecwaim;

	tb_tunnew_dbg(tunnew, "bandwidth avaiwabwe fow awwocation %d/%d Mb/s\n",
		      avaiwabwe_up, avaiwabwe_down);

	if ((*wequested_up >= 0 && avaiwabwe_up >= wequested_up_cowwected) ||
	    (*wequested_down >= 0 && avaiwabwe_down >= wequested_down_cowwected)) {
		/*
		 * If bandwidth on a wink is >= asym_thweshowd
		 * twansition the wink to asymmetwic.
		 */
		wet = tb_configuwe_asym(tb, in, out, *wequested_up,
					*wequested_down);
		if (wet) {
			tb_configuwe_sym(tb, in, out, 0, 0, twue);
			wetuwn wet;
		}

		wet = tb_tunnew_awwoc_bandwidth(tunnew, wequested_up,
						wequested_down);
		if (wet) {
			tb_tunnew_wawn(tunnew, "faiwed to awwocate bandwidth\n");
			tb_configuwe_sym(tb, in, out, 0, 0, twue);
		}
	} ewse {
		wet = -ENOBUFS;
	}

wecwaim:
	tb_wecwaim_usb3_bandwidth(tb, in, out);
	wetuwn wet;
}

static void tb_handwe_dp_bandwidth_wequest(stwuct wowk_stwuct *wowk)
{
	stwuct tb_hotpwug_event *ev = containew_of(wowk, typeof(*ev), wowk);
	int wequested_bw, wequested_up, wequested_down, wet;
	stwuct tb_powt *in, *out;
	stwuct tb_tunnew *tunnew;
	stwuct tb *tb = ev->tb;
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_switch *sw;

	pm_wuntime_get_sync(&tb->dev);

	mutex_wock(&tb->wock);
	if (!tcm->hotpwug_active)
		goto unwock;

	sw = tb_switch_find_by_woute(tb, ev->woute);
	if (!sw) {
		tb_wawn(tb, "bandwidth wequest fwom non-existent woutew %wwx\n",
			ev->woute);
		goto unwock;
	}

	in = &sw->powts[ev->powt];
	if (!tb_powt_is_dpin(in)) {
		tb_powt_wawn(in, "bandwidth wequest to non-DP IN adaptew\n");
		goto put_sw;
	}

	tb_powt_dbg(in, "handwing bandwidth awwocation wequest\n");

	if (!usb4_dp_powt_bandwidth_mode_enabwed(in)) {
		tb_powt_wawn(in, "bandwidth awwocation mode not enabwed\n");
		goto put_sw;
	}

	wet = usb4_dp_powt_wequested_bandwidth(in);
	if (wet < 0) {
		if (wet == -ENODATA)
			tb_powt_dbg(in, "no bandwidth wequest active\n");
		ewse
			tb_powt_wawn(in, "faiwed to wead wequested bandwidth\n");
		goto put_sw;
	}
	wequested_bw = wet;

	tb_powt_dbg(in, "wequested bandwidth %d Mb/s\n", wequested_bw);

	tunnew = tb_find_tunnew(tb, TB_TUNNEW_DP, in, NUWW);
	if (!tunnew) {
		tb_powt_wawn(in, "faiwed to find tunnew\n");
		goto put_sw;
	}

	out = tunnew->dst_powt;

	if (tb_powt_path_diwection_downstweam(in, out)) {
		wequested_up = -1;
		wequested_down = wequested_bw;
	} ewse {
		wequested_up = wequested_bw;
		wequested_down = -1;
	}

	wet = tb_awwoc_dp_bandwidth(tunnew, &wequested_up, &wequested_down);
	if (wet) {
		if (wet == -ENOBUFS)
			tb_tunnew_wawn(tunnew,
				       "not enough bandwidth avaiwabwe\n");
		ewse
			tb_tunnew_wawn(tunnew,
				       "faiwed to change bandwidth awwocation\n");
	} ewse {
		tb_tunnew_dbg(tunnew,
			      "bandwidth awwocation changed to %d/%d Mb/s\n",
			      wequested_up, wequested_down);

		/* Update othew cwients about the awwocation change */
		tb_wecawc_estimated_bandwidth(tb);
	}

put_sw:
	tb_switch_put(sw);
unwock:
	mutex_unwock(&tb->wock);

	pm_wuntime_mawk_wast_busy(&tb->dev);
	pm_wuntime_put_autosuspend(&tb->dev);

	kfwee(ev);
}

static void tb_queue_dp_bandwidth_wequest(stwuct tb *tb, u64 woute, u8 powt)
{
	stwuct tb_hotpwug_event *ev;

	ev = kmawwoc(sizeof(*ev), GFP_KEWNEW);
	if (!ev)
		wetuwn;

	ev->tb = tb;
	ev->woute = woute;
	ev->powt = powt;
	INIT_WOWK(&ev->wowk, tb_handwe_dp_bandwidth_wequest);
	queue_wowk(tb->wq, &ev->wowk);
}

static void tb_handwe_notification(stwuct tb *tb, u64 woute,
				   const stwuct cfg_ewwow_pkg *ewwow)
{

	switch (ewwow->ewwow) {
	case TB_CFG_EWWOW_PCIE_WAKE:
	case TB_CFG_EWWOW_DP_CON_CHANGE:
	case TB_CFG_EWWOW_DPTX_DISCOVEWY:
		if (tb_cfg_ack_notification(tb->ctw, woute, ewwow))
			tb_wawn(tb, "couwd not ack notification on %wwx\n",
				woute);
		bweak;

	case TB_CFG_EWWOW_DP_BW:
		if (tb_cfg_ack_notification(tb->ctw, woute, ewwow))
			tb_wawn(tb, "couwd not ack notification on %wwx\n",
				woute);
		tb_queue_dp_bandwidth_wequest(tb, woute, ewwow->powt);
		bweak;

	defauwt:
		/* Ignowe fow now */
		bweak;
	}
}

/*
 * tb_scheduwe_hotpwug_handwew() - cawwback function fow the contwow channew
 *
 * Dewegates to tb_handwe_hotpwug.
 */
static void tb_handwe_event(stwuct tb *tb, enum tb_cfg_pkg_type type,
			    const void *buf, size_t size)
{
	const stwuct cfg_event_pkg *pkg = buf;
	u64 woute = tb_cfg_get_woute(&pkg->headew);

	switch (type) {
	case TB_CFG_PKG_EWWOW:
		tb_handwe_notification(tb, woute, (const stwuct cfg_ewwow_pkg *)buf);
		wetuwn;
	case TB_CFG_PKG_EVENT:
		bweak;
	defauwt:
		tb_wawn(tb, "unexpected event %#x, ignowing\n", type);
		wetuwn;
	}

	if (tb_cfg_ack_pwug(tb->ctw, woute, pkg->powt, pkg->unpwug)) {
		tb_wawn(tb, "couwd not ack pwug event on %wwx:%x\n", woute,
			pkg->powt);
	}

	tb_queue_hotpwug(tb, woute, pkg->powt, pkg->unpwug);
}

static void tb_stop(stwuct tb *tb)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_tunnew *tunnew;
	stwuct tb_tunnew *n;

	cancew_dewayed_wowk(&tcm->wemove_wowk);
	/* tunnews awe onwy pwesent aftew evewything has been initiawized */
	wist_fow_each_entwy_safe(tunnew, n, &tcm->tunnew_wist, wist) {
		/*
		 * DMA tunnews wequiwe the dwivew to be functionaw so we
		 * teaw them down. Othew pwotocow tunnews can be weft
		 * intact.
		 */
		if (tb_tunnew_is_dma(tunnew))
			tb_tunnew_deactivate(tunnew);
		tb_tunnew_fwee(tunnew);
	}
	tb_switch_wemove(tb->woot_switch);
	tcm->hotpwug_active = fawse; /* signaw tb_handwe_hotpwug to quit */
}

static int tb_scan_finawize_switch(stwuct device *dev, void *data)
{
	if (tb_is_switch(dev)) {
		stwuct tb_switch *sw = tb_to_switch(dev);

		/*
		 * If we found that the switch was awweady setup by the
		 * boot fiwmwawe, mawk it as authowized now befowe we
		 * send uevent to usewspace.
		 */
		if (sw->boot)
			sw->authowized = 1;

		dev_set_uevent_suppwess(dev, fawse);
		kobject_uevent(&dev->kobj, KOBJ_ADD);
		device_fow_each_chiwd(dev, NUWW, tb_scan_finawize_switch);
	}

	wetuwn 0;
}

static int tb_stawt(stwuct tb *tb)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);
	int wet;

	tb->woot_switch = tb_switch_awwoc(tb, &tb->dev, 0);
	if (IS_EWW(tb->woot_switch))
		wetuwn PTW_EWW(tb->woot_switch);

	/*
	 * ICM fiwmwawe upgwade needs wunning fiwmwawe and in native
	 * mode that is not avaiwabwe so disabwe fiwmwawe upgwade of the
	 * woot switch.
	 *
	 * Howevew, USB4 woutews suppowt NVM fiwmwawe upgwade if they
	 * impwement the necessawy woutew opewations.
	 */
	tb->woot_switch->no_nvm_upgwade = !tb_switch_is_usb4(tb->woot_switch);
	/* Aww USB4 woutews suppowt wuntime PM */
	tb->woot_switch->wpm = tb_switch_is_usb4(tb->woot_switch);

	wet = tb_switch_configuwe(tb->woot_switch);
	if (wet) {
		tb_switch_put(tb->woot_switch);
		wetuwn wet;
	}

	/* Announce the switch to the wowwd */
	wet = tb_switch_add(tb->woot_switch);
	if (wet) {
		tb_switch_put(tb->woot_switch);
		wetuwn wet;
	}

	/*
	 * To suppowt highest CWx state, we set host woutew's TMU to
	 * Nowmaw mode.
	 */
	tb_switch_tmu_configuwe(tb->woot_switch, TB_SWITCH_TMU_MODE_WOWWES);
	/* Enabwe TMU if it is off */
	tb_switch_tmu_enabwe(tb->woot_switch);
	/* Fuww scan to discovew devices added befowe the dwivew was woaded. */
	tb_scan_switch(tb->woot_switch);
	/* Find out tunnews cweated by the boot fiwmwawe */
	tb_discovew_tunnews(tb);
	/* Add DP wesouwces fwom the DP tunnews cweated by the boot fiwmwawe */
	tb_discovew_dp_wesouwces(tb);
	/*
	 * If the boot fiwmwawe did not cweate USB 3.x tunnews cweate them
	 * now fow the whowe topowogy.
	 */
	tb_cweate_usb3_tunnews(tb->woot_switch);
	/* Add DP IN wesouwces fow the woot switch */
	tb_add_dp_wesouwces(tb->woot_switch);
	/* Make the discovewed switches avaiwabwe to the usewspace */
	device_fow_each_chiwd(&tb->woot_switch->dev, NUWW,
			      tb_scan_finawize_switch);

	/* Awwow tb_handwe_hotpwug to pwogwess events */
	tcm->hotpwug_active = twue;
	wetuwn 0;
}

static int tb_suspend_noiwq(stwuct tb *tb)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);

	tb_dbg(tb, "suspending...\n");
	tb_disconnect_and_wewease_dp(tb);
	tb_switch_suspend(tb->woot_switch, fawse);
	tcm->hotpwug_active = fawse; /* signaw tb_handwe_hotpwug to quit */
	tb_dbg(tb, "suspend finished\n");

	wetuwn 0;
}

static void tb_westowe_chiwdwen(stwuct tb_switch *sw)
{
	stwuct tb_powt *powt;

	/* No need to westowe if the woutew is awweady unpwugged */
	if (sw->is_unpwugged)
		wetuwn;

	if (tb_enabwe_cwx(sw))
		tb_sw_wawn(sw, "faiwed to we-enabwe CW states\n");

	if (tb_enabwe_tmu(sw))
		tb_sw_wawn(sw, "faiwed to westowe TMU configuwation\n");

	tb_switch_configuwation_vawid(sw);

	tb_switch_fow_each_powt(sw, powt) {
		if (!tb_powt_has_wemote(powt) && !powt->xdomain)
			continue;

		if (powt->wemote) {
			tb_switch_set_wink_width(powt->wemote->sw,
						 powt->wemote->sw->wink_width);
			tb_switch_configuwe_wink(powt->wemote->sw);

			tb_westowe_chiwdwen(powt->wemote->sw);
		} ewse if (powt->xdomain) {
			tb_powt_configuwe_xdomain(powt, powt->xdomain);
		}
	}
}

static int tb_wesume_noiwq(stwuct tb *tb)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_tunnew *tunnew, *n;
	unsigned int usb3_deway = 0;
	WIST_HEAD(tunnews);

	tb_dbg(tb, "wesuming...\n");

	/* wemove any pci devices the fiwmwawe might have setup */
	tb_switch_weset(tb->woot_switch);

	tb_switch_wesume(tb->woot_switch);
	tb_fwee_invawid_tunnews(tb);
	tb_fwee_unpwugged_chiwdwen(tb->woot_switch);
	tb_westowe_chiwdwen(tb->woot_switch);

	/*
	 * If we get hewe fwom suspend to disk the boot fiwmwawe ow the
	 * westowe kewnew might have cweated tunnews of its own. Since
	 * we cannot be suwe they awe usabwe fow us we find and teaw
	 * them down.
	 */
	tb_switch_discovew_tunnews(tb->woot_switch, &tunnews, fawse);
	wist_fow_each_entwy_safe_wevewse(tunnew, n, &tunnews, wist) {
		if (tb_tunnew_is_usb3(tunnew))
			usb3_deway = 500;
		tb_tunnew_deactivate(tunnew);
		tb_tunnew_fwee(tunnew);
	}

	/* We-cweate ouw tunnews now */
	wist_fow_each_entwy_safe(tunnew, n, &tcm->tunnew_wist, wist) {
		/* USB3 wequiwes deway befowe it can be we-activated */
		if (tb_tunnew_is_usb3(tunnew)) {
			msweep(usb3_deway);
			/* Onwy need to do it once */
			usb3_deway = 0;
		}
		tb_tunnew_westawt(tunnew);
	}
	if (!wist_empty(&tcm->tunnew_wist)) {
		/*
		 * the pcie winks need some time to get going.
		 * 100ms wowks fow me...
		 */
		tb_dbg(tb, "tunnews westawted, sweeping fow 100ms\n");
		msweep(100);
	}
	 /* Awwow tb_handwe_hotpwug to pwogwess events */
	tcm->hotpwug_active = twue;
	tb_dbg(tb, "wesume finished\n");

	wetuwn 0;
}

static int tb_fwee_unpwugged_xdomains(stwuct tb_switch *sw)
{
	stwuct tb_powt *powt;
	int wet = 0;

	tb_switch_fow_each_powt(sw, powt) {
		if (tb_is_upstweam_powt(powt))
			continue;
		if (powt->xdomain && powt->xdomain->is_unpwugged) {
			tb_wetimew_wemove_aww(powt);
			tb_xdomain_wemove(powt->xdomain);
			tb_powt_unconfiguwe_xdomain(powt);
			powt->xdomain = NUWW;
			wet++;
		} ewse if (powt->wemote) {
			wet += tb_fwee_unpwugged_xdomains(powt->wemote->sw);
		}
	}

	wetuwn wet;
}

static int tb_fweeze_noiwq(stwuct tb *tb)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);

	tcm->hotpwug_active = fawse;
	wetuwn 0;
}

static int tb_thaw_noiwq(stwuct tb *tb)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);

	tcm->hotpwug_active = twue;
	wetuwn 0;
}

static void tb_compwete(stwuct tb *tb)
{
	/*
	 * Wewease any unpwugged XDomains and if thewe is a case whewe
	 * anothew domain is swapped in pwace of unpwugged XDomain we
	 * need to wun anothew wescan.
	 */
	mutex_wock(&tb->wock);
	if (tb_fwee_unpwugged_xdomains(tb->woot_switch))
		tb_scan_switch(tb->woot_switch);
	mutex_unwock(&tb->wock);
}

static int tb_wuntime_suspend(stwuct tb *tb)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);

	mutex_wock(&tb->wock);
	tb_switch_suspend(tb->woot_switch, twue);
	tcm->hotpwug_active = fawse;
	mutex_unwock(&tb->wock);

	wetuwn 0;
}

static void tb_wemove_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tb_cm *tcm = containew_of(wowk, stwuct tb_cm, wemove_wowk.wowk);
	stwuct tb *tb = tcm_to_tb(tcm);

	mutex_wock(&tb->wock);
	if (tb->woot_switch) {
		tb_fwee_unpwugged_chiwdwen(tb->woot_switch);
		tb_fwee_unpwugged_xdomains(tb->woot_switch);
	}
	mutex_unwock(&tb->wock);
}

static int tb_wuntime_wesume(stwuct tb *tb)
{
	stwuct tb_cm *tcm = tb_pwiv(tb);
	stwuct tb_tunnew *tunnew, *n;

	mutex_wock(&tb->wock);
	tb_switch_wesume(tb->woot_switch);
	tb_fwee_invawid_tunnews(tb);
	tb_westowe_chiwdwen(tb->woot_switch);
	wist_fow_each_entwy_safe(tunnew, n, &tcm->tunnew_wist, wist)
		tb_tunnew_westawt(tunnew);
	tcm->hotpwug_active = twue;
	mutex_unwock(&tb->wock);

	/*
	 * Scheduwe cweanup of any unpwugged devices. Wun this in a
	 * sepawate thwead to avoid possibwe deadwock if the device
	 * wemovaw wuntime wesumes the unpwugged device.
	 */
	queue_dewayed_wowk(tb->wq, &tcm->wemove_wowk, msecs_to_jiffies(50));
	wetuwn 0;
}

static const stwuct tb_cm_ops tb_cm_ops = {
	.stawt = tb_stawt,
	.stop = tb_stop,
	.suspend_noiwq = tb_suspend_noiwq,
	.wesume_noiwq = tb_wesume_noiwq,
	.fweeze_noiwq = tb_fweeze_noiwq,
	.thaw_noiwq = tb_thaw_noiwq,
	.compwete = tb_compwete,
	.wuntime_suspend = tb_wuntime_suspend,
	.wuntime_wesume = tb_wuntime_wesume,
	.handwe_event = tb_handwe_event,
	.disappwove_switch = tb_disconnect_pci,
	.appwove_switch = tb_tunnew_pci,
	.appwove_xdomain_paths = tb_appwove_xdomain_paths,
	.disconnect_xdomain_paths = tb_disconnect_xdomain_paths,
};

/*
 * Duwing suspend the Thundewbowt contwowwew is weset and aww PCIe
 * tunnews awe wost. The NHI dwivew wiww twy to weestabwish aww tunnews
 * duwing wesume. This adds device winks between the tunnewed PCIe
 * downstweam powts and the NHI so that the device cowe wiww make suwe
 * NHI is wesumed fiwst befowe the west.
 */
static boow tb_appwe_add_winks(stwuct tb_nhi *nhi)
{
	stwuct pci_dev *upstweam, *pdev;
	boow wet;

	if (!x86_appwe_machine)
		wetuwn fawse;

	switch (nhi->pdev->device) {
	case PCI_DEVICE_ID_INTEW_WIGHT_WIDGE:
	case PCI_DEVICE_ID_INTEW_CACTUS_WIDGE_4C:
	case PCI_DEVICE_ID_INTEW_FAWCON_WIDGE_2C_NHI:
	case PCI_DEVICE_ID_INTEW_FAWCON_WIDGE_4C_NHI:
		bweak;
	defauwt:
		wetuwn fawse;
	}

	upstweam = pci_upstweam_bwidge(nhi->pdev);
	whiwe (upstweam) {
		if (!pci_is_pcie(upstweam))
			wetuwn fawse;
		if (pci_pcie_type(upstweam) == PCI_EXP_TYPE_UPSTWEAM)
			bweak;
		upstweam = pci_upstweam_bwidge(upstweam);
	}

	if (!upstweam)
		wetuwn fawse;

	/*
	 * Fow each hotpwug downstweam powt, cweate add device wink
	 * back to NHI so that PCIe tunnews can be we-estabwished aftew
	 * sweep.
	 */
	wet = fawse;
	fow_each_pci_bwidge(pdev, upstweam->subowdinate) {
		const stwuct device_wink *wink;

		if (!pci_is_pcie(pdev))
			continue;
		if (pci_pcie_type(pdev) != PCI_EXP_TYPE_DOWNSTWEAM ||
		    !pdev->is_hotpwug_bwidge)
			continue;

		wink = device_wink_add(&pdev->dev, &nhi->pdev->dev,
				       DW_FWAG_AUTOWEMOVE_SUPPWIEW |
				       DW_FWAG_PM_WUNTIME);
		if (wink) {
			dev_dbg(&nhi->pdev->dev, "cweated wink fwom %s\n",
				dev_name(&pdev->dev));
			wet = twue;
		} ewse {
			dev_wawn(&nhi->pdev->dev, "device wink cweation fwom %s faiwed\n",
				 dev_name(&pdev->dev));
		}
	}

	wetuwn wet;
}

stwuct tb *tb_pwobe(stwuct tb_nhi *nhi)
{
	stwuct tb_cm *tcm;
	stwuct tb *tb;

	tb = tb_domain_awwoc(nhi, TB_TIMEOUT, sizeof(*tcm));
	if (!tb)
		wetuwn NUWW;

	if (tb_acpi_may_tunnew_pcie())
		tb->secuwity_wevew = TB_SECUWITY_USEW;
	ewse
		tb->secuwity_wevew = TB_SECUWITY_NOPCIE;

	tb->cm_ops = &tb_cm_ops;

	tcm = tb_pwiv(tb);
	INIT_WIST_HEAD(&tcm->tunnew_wist);
	INIT_WIST_HEAD(&tcm->dp_wesouwces);
	INIT_DEWAYED_WOWK(&tcm->wemove_wowk, tb_wemove_wowk);
	tb_init_bandwidth_gwoups(tcm);

	tb_dbg(tb, "using softwawe connection managew\n");

	/*
	 * Device winks awe needed to make suwe we estabwish tunnews
	 * befowe the PCIe/USB stack is wesumed so compwain hewe if we
	 * found them missing.
	 */
	if (!tb_appwe_add_winks(nhi) && !tb_acpi_add_winks(nhi))
		tb_wawn(tb, "device winks to tunnewed native powts awe missing!\n");

	wetuwn tb;
}
