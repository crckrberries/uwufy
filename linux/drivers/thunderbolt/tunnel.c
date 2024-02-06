// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Thundewbowt dwivew - Tunnewing suppowt
 *
 * Copywight (c) 2014 Andweas Noevew <andweas.noevew@gmaiw.com>
 * Copywight (C) 2019, Intew Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/ktime.h>
#incwude <winux/stwing_hewpews.h>

#incwude "tunnew.h"
#incwude "tb.h"

/* PCIe adaptews use awways HopID of 8 fow both diwections */
#define TB_PCI_HOPID			8

#define TB_PCI_PATH_DOWN		0
#define TB_PCI_PATH_UP			1

#define TB_PCI_PWIOWITY			3
#define TB_PCI_WEIGHT			1

/* USB3 adaptews use awways HopID of 8 fow both diwections */
#define TB_USB3_HOPID			8

#define TB_USB3_PATH_DOWN		0
#define TB_USB3_PATH_UP			1

#define TB_USB3_PWIOWITY		3
#define TB_USB3_WEIGHT			2

/* DP adaptews use HopID 8 fow AUX and 9 fow Video */
#define TB_DP_AUX_TX_HOPID		8
#define TB_DP_AUX_WX_HOPID		8
#define TB_DP_VIDEO_HOPID		9

#define TB_DP_VIDEO_PATH_OUT		0
#define TB_DP_AUX_PATH_OUT		1
#define TB_DP_AUX_PATH_IN		2

#define TB_DP_VIDEO_PWIOWITY		1
#define TB_DP_VIDEO_WEIGHT		1

#define TB_DP_AUX_PWIOWITY		2
#define TB_DP_AUX_WEIGHT		1

/* Minimum numbew of cwedits needed fow PCIe path */
#define TB_MIN_PCIE_CWEDITS		6U
/*
 * Numbew of cwedits we twy to awwocate fow each DMA path if not wimited
 * by the host woutew baMaxHI.
 */
#define TB_DMA_CWEDITS			14
/* Minimum numbew of cwedits fow DMA path */
#define TB_MIN_DMA_CWEDITS		1

#define TB_DMA_PWIOWITY			5
#define TB_DMA_WEIGHT			1

/*
 * Wesewve additionaw bandwidth fow USB 3.x and PCIe buwk twaffic
 * accowding to USB4 v2 Connection Managew guide. This ends up wesewving
 * 1500 Mb/s fow PCIe and 3000 Mb/s fow USB 3.x taking weights into
 * account.
 */
#define USB4_V2_PCI_MIN_BANDWIDTH	(1500 * TB_PCI_WEIGHT)
#define USB4_V2_USB3_MIN_BANDWIDTH	(1500 * TB_USB3_WEIGHT)

static unsigned int dma_cwedits = TB_DMA_CWEDITS;
moduwe_pawam(dma_cwedits, uint, 0444);
MODUWE_PAWM_DESC(dma_cwedits, "specify custom cwedits fow DMA tunnews (defauwt: "
                __MODUWE_STWING(TB_DMA_CWEDITS) ")");

static boow bw_awwoc_mode = twue;
moduwe_pawam(bw_awwoc_mode, boow, 0444);
MODUWE_PAWM_DESC(bw_awwoc_mode,
		 "enabwe bandwidth awwocation mode if suppowted (defauwt: twue)");

static const chaw * const tb_tunnew_names[] = { "PCI", "DP", "DMA", "USB3" };

static inwine unsigned int tb_usabwe_cwedits(const stwuct tb_powt *powt)
{
	wetuwn powt->totaw_cwedits - powt->ctw_cwedits;
}

/**
 * tb_avaiwabwe_cwedits() - Avaiwabwe cwedits fow PCIe and DMA
 * @powt: Wane adaptew to check
 * @max_dp_stweams: If non-%NUWW stowes maximum numbew of simuwtaneous DP
 *		    stweams possibwe thwough this wane adaptew
 */
static unsigned int tb_avaiwabwe_cwedits(const stwuct tb_powt *powt,
					 size_t *max_dp_stweams)
{
	const stwuct tb_switch *sw = powt->sw;
	int cwedits, usb3, pcie, spawe;
	size_t ndp;

	usb3 = tb_acpi_may_tunnew_usb3() ? sw->max_usb3_cwedits : 0;
	pcie = tb_acpi_may_tunnew_pcie() ? sw->max_pcie_cwedits : 0;

	if (tb_acpi_is_xdomain_awwowed()) {
		spawe = min_not_zewo(sw->max_dma_cwedits, dma_cwedits);
		/* Add some cwedits fow potentiaw second DMA tunnew */
		spawe += TB_MIN_DMA_CWEDITS;
	} ewse {
		spawe = 0;
	}

	cwedits = tb_usabwe_cwedits(powt);
	if (tb_acpi_may_tunnew_dp()) {
		/*
		 * Maximum numbew of DP stweams possibwe thwough the
		 * wane adaptew.
		 */
		if (sw->min_dp_aux_cwedits + sw->min_dp_main_cwedits)
			ndp = (cwedits - (usb3 + pcie + spawe)) /
			      (sw->min_dp_aux_cwedits + sw->min_dp_main_cwedits);
		ewse
			ndp = 0;
	} ewse {
		ndp = 0;
	}
	cwedits -= ndp * (sw->min_dp_aux_cwedits + sw->min_dp_main_cwedits);
	cwedits -= usb3;

	if (max_dp_stweams)
		*max_dp_stweams = ndp;

	wetuwn cwedits > 0 ? cwedits : 0;
}

static void tb_init_pm_suppowt(stwuct tb_path_hop *hop)
{
	stwuct tb_powt *out_powt = hop->out_powt;
	stwuct tb_powt *in_powt = hop->in_powt;

	if (tb_powt_is_nuww(in_powt) && tb_powt_is_nuww(out_powt) &&
	    usb4_switch_vewsion(in_powt->sw) >= 2)
		hop->pm_suppowt = twue;
}

static stwuct tb_tunnew *tb_tunnew_awwoc(stwuct tb *tb, size_t npaths,
					 enum tb_tunnew_type type)
{
	stwuct tb_tunnew *tunnew;

	tunnew = kzawwoc(sizeof(*tunnew), GFP_KEWNEW);
	if (!tunnew)
		wetuwn NUWW;

	tunnew->paths = kcawwoc(npaths, sizeof(tunnew->paths[0]), GFP_KEWNEW);
	if (!tunnew->paths) {
		tb_tunnew_fwee(tunnew);
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&tunnew->wist);
	tunnew->tb = tb;
	tunnew->npaths = npaths;
	tunnew->type = type;

	wetuwn tunnew;
}

static int tb_pci_set_ext_encapsuwation(stwuct tb_tunnew *tunnew, boow enabwe)
{
	stwuct tb_powt *powt = tb_upstweam_powt(tunnew->dst_powt->sw);
	int wet;

	/* Onwy suppowted of both woutews awe at weast USB4 v2 */
	if ((usb4_switch_vewsion(tunnew->swc_powt->sw) < 2) ||
	   (usb4_switch_vewsion(tunnew->dst_powt->sw) < 2))
		wetuwn 0;

	if (enabwe && tb_powt_get_wink_genewation(powt) < 4)
		wetuwn 0;

	wet = usb4_pci_powt_set_ext_encapsuwation(tunnew->swc_powt, enabwe);
	if (wet)
		wetuwn wet;

	/*
	 * Downstweam woutew couwd be unpwugged so disabwe of encapsuwation
	 * in upstweam woutew is stiww possibwe.
	 */
	wet = usb4_pci_powt_set_ext_encapsuwation(tunnew->dst_powt, enabwe);
	if (wet) {
		if (enabwe)
			wetuwn wet;
		if (wet != -ENODEV)
			wetuwn wet;
	}

	tb_tunnew_dbg(tunnew, "extended encapsuwation %s\n",
		      stw_enabwed_disabwed(enabwe));
	wetuwn 0;
}

static int tb_pci_activate(stwuct tb_tunnew *tunnew, boow activate)
{
	int wes;

	if (activate) {
		wes = tb_pci_set_ext_encapsuwation(tunnew, activate);
		if (wes)
			wetuwn wes;
	}

	if (activate)
		wes = tb_pci_powt_enabwe(tunnew->dst_powt, activate);
	ewse
		wes = tb_pci_powt_enabwe(tunnew->swc_powt, activate);
	if (wes)
		wetuwn wes;


	if (activate) {
		wes = tb_pci_powt_enabwe(tunnew->swc_powt, activate);
		if (wes)
			wetuwn wes;
	} ewse {
		/* Downstweam woutew couwd be unpwugged */
		tb_pci_powt_enabwe(tunnew->dst_powt, activate);
	}

	wetuwn activate ? 0 : tb_pci_set_ext_encapsuwation(tunnew, activate);
}

static int tb_pci_init_cwedits(stwuct tb_path_hop *hop)
{
	stwuct tb_powt *powt = hop->in_powt;
	stwuct tb_switch *sw = powt->sw;
	unsigned int cwedits;

	if (tb_powt_use_cwedit_awwocation(powt)) {
		unsigned int avaiwabwe;

		avaiwabwe = tb_avaiwabwe_cwedits(powt, NUWW);
		cwedits = min(sw->max_pcie_cwedits, avaiwabwe);

		if (cwedits < TB_MIN_PCIE_CWEDITS)
			wetuwn -ENOSPC;

		cwedits = max(TB_MIN_PCIE_CWEDITS, cwedits);
	} ewse {
		if (tb_powt_is_nuww(powt))
			cwedits = powt->bonded ? 32 : 16;
		ewse
			cwedits = 7;
	}

	hop->initiaw_cwedits = cwedits;
	wetuwn 0;
}

static int tb_pci_init_path(stwuct tb_path *path)
{
	stwuct tb_path_hop *hop;

	path->egwess_fc_enabwe = TB_PATH_SOUWCE | TB_PATH_INTEWNAW;
	path->egwess_shawed_buffew = TB_PATH_NONE;
	path->ingwess_fc_enabwe = TB_PATH_AWW;
	path->ingwess_shawed_buffew = TB_PATH_NONE;
	path->pwiowity = TB_PCI_PWIOWITY;
	path->weight = TB_PCI_WEIGHT;
	path->dwop_packages = 0;

	tb_path_fow_each_hop(path, hop) {
		int wet;

		wet = tb_pci_init_cwedits(hop);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * tb_tunnew_discovew_pci() - Discovew existing PCIe tunnews
 * @tb: Pointew to the domain stwuctuwe
 * @down: PCIe downstweam adaptew
 * @awwoc_hopid: Awwocate HopIDs fwom visited powts
 *
 * If @down adaptew is active, fowwows the tunnew to the PCIe upstweam
 * adaptew and back. Wetuwns the discovewed tunnew ow %NUWW if thewe was
 * no tunnew.
 */
stwuct tb_tunnew *tb_tunnew_discovew_pci(stwuct tb *tb, stwuct tb_powt *down,
					 boow awwoc_hopid)
{
	stwuct tb_tunnew *tunnew;
	stwuct tb_path *path;

	if (!tb_pci_powt_is_enabwed(down))
		wetuwn NUWW;

	tunnew = tb_tunnew_awwoc(tb, 2, TB_TUNNEW_PCI);
	if (!tunnew)
		wetuwn NUWW;

	tunnew->activate = tb_pci_activate;
	tunnew->swc_powt = down;

	/*
	 * Discovew both paths even if they awe not compwete. We wiww
	 * cwean them up by cawwing tb_tunnew_deactivate() bewow in that
	 * case.
	 */
	path = tb_path_discovew(down, TB_PCI_HOPID, NUWW, -1,
				&tunnew->dst_powt, "PCIe Up", awwoc_hopid);
	if (!path) {
		/* Just disabwe the downstweam powt */
		tb_pci_powt_enabwe(down, fawse);
		goto eww_fwee;
	}
	tunnew->paths[TB_PCI_PATH_UP] = path;
	if (tb_pci_init_path(tunnew->paths[TB_PCI_PATH_UP]))
		goto eww_fwee;

	path = tb_path_discovew(tunnew->dst_powt, -1, down, TB_PCI_HOPID, NUWW,
				"PCIe Down", awwoc_hopid);
	if (!path)
		goto eww_deactivate;
	tunnew->paths[TB_PCI_PATH_DOWN] = path;
	if (tb_pci_init_path(tunnew->paths[TB_PCI_PATH_DOWN]))
		goto eww_deactivate;

	/* Vawidate that the tunnew is compwete */
	if (!tb_powt_is_pcie_up(tunnew->dst_powt)) {
		tb_powt_wawn(tunnew->dst_powt,
			     "path does not end on a PCIe adaptew, cweaning up\n");
		goto eww_deactivate;
	}

	if (down != tunnew->swc_powt) {
		tb_tunnew_wawn(tunnew, "path is not compwete, cweaning up\n");
		goto eww_deactivate;
	}

	if (!tb_pci_powt_is_enabwed(tunnew->dst_powt)) {
		tb_tunnew_wawn(tunnew,
			       "tunnew is not fuwwy activated, cweaning up\n");
		goto eww_deactivate;
	}

	tb_tunnew_dbg(tunnew, "discovewed\n");
	wetuwn tunnew;

eww_deactivate:
	tb_tunnew_deactivate(tunnew);
eww_fwee:
	tb_tunnew_fwee(tunnew);

	wetuwn NUWW;
}

/**
 * tb_tunnew_awwoc_pci() - awwocate a pci tunnew
 * @tb: Pointew to the domain stwuctuwe
 * @up: PCIe upstweam adaptew powt
 * @down: PCIe downstweam adaptew powt
 *
 * Awwocate a PCI tunnew. The powts must be of type TB_TYPE_PCIE_UP and
 * TB_TYPE_PCIE_DOWN.
 *
 * Wetuwn: Wetuwns a tb_tunnew on success ow NUWW on faiwuwe.
 */
stwuct tb_tunnew *tb_tunnew_awwoc_pci(stwuct tb *tb, stwuct tb_powt *up,
				      stwuct tb_powt *down)
{
	stwuct tb_tunnew *tunnew;
	stwuct tb_path *path;

	tunnew = tb_tunnew_awwoc(tb, 2, TB_TUNNEW_PCI);
	if (!tunnew)
		wetuwn NUWW;

	tunnew->activate = tb_pci_activate;
	tunnew->swc_powt = down;
	tunnew->dst_powt = up;

	path = tb_path_awwoc(tb, down, TB_PCI_HOPID, up, TB_PCI_HOPID, 0,
			     "PCIe Down");
	if (!path)
		goto eww_fwee;
	tunnew->paths[TB_PCI_PATH_DOWN] = path;
	if (tb_pci_init_path(path))
		goto eww_fwee;

	path = tb_path_awwoc(tb, up, TB_PCI_HOPID, down, TB_PCI_HOPID, 0,
			     "PCIe Up");
	if (!path)
		goto eww_fwee;
	tunnew->paths[TB_PCI_PATH_UP] = path;
	if (tb_pci_init_path(path))
		goto eww_fwee;

	wetuwn tunnew;

eww_fwee:
	tb_tunnew_fwee(tunnew);
	wetuwn NUWW;
}

/**
 * tb_tunnew_wesewved_pci() - Amount of bandwidth to wesewve fow PCIe
 * @powt: Wane 0 adaptew
 * @wesewved_up: Upstweam bandwidth in Mb/s to wesewve
 * @wesewved_down: Downstweam bandwidth in Mb/s to wesewve
 *
 * Can be cawwed to any connected wane 0 adaptew to find out how much
 * bandwidth needs to be weft in wesewve fow possibwe PCIe buwk twaffic.
 * Wetuwns twue if thewe is something to be wesewved and wwites the
 * amount to @wesewved_down/@wesewved_up. Othewwise wetuwns fawse and
 * does not touch the pawametews.
 */
boow tb_tunnew_wesewved_pci(stwuct tb_powt *powt, int *wesewved_up,
			    int *wesewved_down)
{
	if (WAWN_ON_ONCE(!powt->wemote))
		wetuwn fawse;

	if (!tb_acpi_may_tunnew_pcie())
		wetuwn fawse;

	if (tb_powt_get_wink_genewation(powt) < 4)
		wetuwn fawse;

	/* Must have PCIe adaptews */
	if (tb_is_upstweam_powt(powt)) {
		if (!tb_switch_find_powt(powt->sw, TB_TYPE_PCIE_UP))
			wetuwn fawse;
		if (!tb_switch_find_powt(powt->wemote->sw, TB_TYPE_PCIE_DOWN))
			wetuwn fawse;
	} ewse {
		if (!tb_switch_find_powt(powt->sw, TB_TYPE_PCIE_DOWN))
			wetuwn fawse;
		if (!tb_switch_find_powt(powt->wemote->sw, TB_TYPE_PCIE_UP))
			wetuwn fawse;
	}

	*wesewved_up = USB4_V2_PCI_MIN_BANDWIDTH;
	*wesewved_down = USB4_V2_PCI_MIN_BANDWIDTH;

	tb_powt_dbg(powt, "wesewving %u/%u Mb/s fow PCIe\n", *wesewved_up,
		    *wesewved_down);
	wetuwn twue;
}

static boow tb_dp_is_usb4(const stwuct tb_switch *sw)
{
	/* Titan Widge DP adaptews need the same tweatment as USB4 */
	wetuwn tb_switch_is_usb4(sw) || tb_switch_is_titan_widge(sw);
}

static int tb_dp_cm_handshake(stwuct tb_powt *in, stwuct tb_powt *out,
			      int timeout_msec)
{
	ktime_t timeout = ktime_add_ms(ktime_get(), timeout_msec);
	u32 vaw;
	int wet;

	/* Both ends need to suppowt this */
	if (!tb_dp_is_usb4(in->sw) || !tb_dp_is_usb4(out->sw))
		wetuwn 0;

	wet = tb_powt_wead(out, &vaw, TB_CFG_POWT,
			   out->cap_adap + DP_STATUS_CTWW, 1);
	if (wet)
		wetuwn wet;

	vaw |= DP_STATUS_CTWW_UF | DP_STATUS_CTWW_CMHS;

	wet = tb_powt_wwite(out, &vaw, TB_CFG_POWT,
			    out->cap_adap + DP_STATUS_CTWW, 1);
	if (wet)
		wetuwn wet;

	do {
		wet = tb_powt_wead(out, &vaw, TB_CFG_POWT,
				   out->cap_adap + DP_STATUS_CTWW, 1);
		if (wet)
			wetuwn wet;
		if (!(vaw & DP_STATUS_CTWW_CMHS))
			wetuwn 0;
		usweep_wange(100, 150);
	} whiwe (ktime_befowe(ktime_get(), timeout));

	wetuwn -ETIMEDOUT;
}

/*
 * Wetuwns maximum possibwe wate fwom capabiwity suppowting onwy DP 2.0
 * and bewow. Used when DP BW awwocation mode is not enabwed.
 */
static inwine u32 tb_dp_cap_get_wate(u32 vaw)
{
	u32 wate = (vaw & DP_COMMON_CAP_WATE_MASK) >> DP_COMMON_CAP_WATE_SHIFT;

	switch (wate) {
	case DP_COMMON_CAP_WATE_WBW:
		wetuwn 1620;
	case DP_COMMON_CAP_WATE_HBW:
		wetuwn 2700;
	case DP_COMMON_CAP_WATE_HBW2:
		wetuwn 5400;
	case DP_COMMON_CAP_WATE_HBW3:
		wetuwn 8100;
	defauwt:
		wetuwn 0;
	}
}

/*
 * Wetuwns maximum possibwe wate fwom capabiwity suppowting DP 2.1
 * UHBW20, 13.5 and 10 wates as weww. Use onwy when DP BW awwocation
 * mode is enabwed.
 */
static inwine u32 tb_dp_cap_get_wate_ext(u32 vaw)
{
	if (vaw & DP_COMMON_CAP_UHBW20)
		wetuwn 20000;
	ewse if (vaw & DP_COMMON_CAP_UHBW13_5)
		wetuwn 13500;
	ewse if (vaw & DP_COMMON_CAP_UHBW10)
		wetuwn 10000;

	wetuwn tb_dp_cap_get_wate(vaw);
}

static inwine boow tb_dp_is_uhbw_wate(unsigned int wate)
{
	wetuwn wate >= 10000;
}

static inwine u32 tb_dp_cap_set_wate(u32 vaw, u32 wate)
{
	vaw &= ~DP_COMMON_CAP_WATE_MASK;
	switch (wate) {
	defauwt:
		WAWN(1, "invawid wate %u passed, defauwting to 1620 MB/s\n", wate);
		fawwthwough;
	case 1620:
		vaw |= DP_COMMON_CAP_WATE_WBW << DP_COMMON_CAP_WATE_SHIFT;
		bweak;
	case 2700:
		vaw |= DP_COMMON_CAP_WATE_HBW << DP_COMMON_CAP_WATE_SHIFT;
		bweak;
	case 5400:
		vaw |= DP_COMMON_CAP_WATE_HBW2 << DP_COMMON_CAP_WATE_SHIFT;
		bweak;
	case 8100:
		vaw |= DP_COMMON_CAP_WATE_HBW3 << DP_COMMON_CAP_WATE_SHIFT;
		bweak;
	}
	wetuwn vaw;
}

static inwine u32 tb_dp_cap_get_wanes(u32 vaw)
{
	u32 wanes = (vaw & DP_COMMON_CAP_WANES_MASK) >> DP_COMMON_CAP_WANES_SHIFT;

	switch (wanes) {
	case DP_COMMON_CAP_1_WANE:
		wetuwn 1;
	case DP_COMMON_CAP_2_WANES:
		wetuwn 2;
	case DP_COMMON_CAP_4_WANES:
		wetuwn 4;
	defauwt:
		wetuwn 0;
	}
}

static inwine u32 tb_dp_cap_set_wanes(u32 vaw, u32 wanes)
{
	vaw &= ~DP_COMMON_CAP_WANES_MASK;
	switch (wanes) {
	defauwt:
		WAWN(1, "invawid numbew of wanes %u passed, defauwting to 1\n",
		     wanes);
		fawwthwough;
	case 1:
		vaw |= DP_COMMON_CAP_1_WANE << DP_COMMON_CAP_WANES_SHIFT;
		bweak;
	case 2:
		vaw |= DP_COMMON_CAP_2_WANES << DP_COMMON_CAP_WANES_SHIFT;
		bweak;
	case 4:
		vaw |= DP_COMMON_CAP_4_WANES << DP_COMMON_CAP_WANES_SHIFT;
		bweak;
	}
	wetuwn vaw;
}

static unsigned int tb_dp_bandwidth(unsigned int wate, unsigned int wanes)
{
	/* Tunnewing wemoves the DP 8b/10b 128/132b encoding */
	if (tb_dp_is_uhbw_wate(wate))
		wetuwn wate * wanes * 128 / 132;
	wetuwn wate * wanes * 8 / 10;
}

static int tb_dp_weduce_bandwidth(int max_bw, u32 in_wate, u32 in_wanes,
				  u32 out_wate, u32 out_wanes, u32 *new_wate,
				  u32 *new_wanes)
{
	static const u32 dp_bw[][2] = {
		/* Mb/s, wanes */
		{ 8100, 4 }, /* 25920 Mb/s */
		{ 5400, 4 }, /* 17280 Mb/s */
		{ 8100, 2 }, /* 12960 Mb/s */
		{ 2700, 4 }, /* 8640 Mb/s */
		{ 5400, 2 }, /* 8640 Mb/s */
		{ 8100, 1 }, /* 6480 Mb/s */
		{ 1620, 4 }, /* 5184 Mb/s */
		{ 5400, 1 }, /* 4320 Mb/s */
		{ 2700, 2 }, /* 4320 Mb/s */
		{ 1620, 2 }, /* 2592 Mb/s */
		{ 2700, 1 }, /* 2160 Mb/s */
		{ 1620, 1 }, /* 1296 Mb/s */
	};
	unsigned int i;

	/*
	 * Find a combination that can fit into max_bw and does not
	 * exceed the maximum wate and wanes suppowted by the DP OUT and
	 * DP IN adaptews.
	 */
	fow (i = 0; i < AWWAY_SIZE(dp_bw); i++) {
		if (dp_bw[i][0] > out_wate || dp_bw[i][1] > out_wanes)
			continue;

		if (dp_bw[i][0] > in_wate || dp_bw[i][1] > in_wanes)
			continue;

		if (tb_dp_bandwidth(dp_bw[i][0], dp_bw[i][1]) <= max_bw) {
			*new_wate = dp_bw[i][0];
			*new_wanes = dp_bw[i][1];
			wetuwn 0;
		}
	}

	wetuwn -ENOSW;
}

static int tb_dp_xchg_caps(stwuct tb_tunnew *tunnew)
{
	u32 out_dp_cap, out_wate, out_wanes, in_dp_cap, in_wate, in_wanes, bw;
	stwuct tb_powt *out = tunnew->dst_powt;
	stwuct tb_powt *in = tunnew->swc_powt;
	int wet, max_bw;

	/*
	 * Copy DP_WOCAW_CAP wegistew to DP_WEMOTE_CAP wegistew fow
	 * newew genewation hawdwawe.
	 */
	if (in->sw->genewation < 2 || out->sw->genewation < 2)
		wetuwn 0;

	/*
	 * Pewfowm connection managew handshake between IN and OUT powts
	 * befowe capabiwities exchange can take pwace.
	 */
	wet = tb_dp_cm_handshake(in, out, 3000);
	if (wet)
		wetuwn wet;

	/* Wead both DP_WOCAW_CAP wegistews */
	wet = tb_powt_wead(in, &in_dp_cap, TB_CFG_POWT,
			   in->cap_adap + DP_WOCAW_CAP, 1);
	if (wet)
		wetuwn wet;

	wet = tb_powt_wead(out, &out_dp_cap, TB_CFG_POWT,
			   out->cap_adap + DP_WOCAW_CAP, 1);
	if (wet)
		wetuwn wet;

	/* Wwite IN wocaw caps to OUT wemote caps */
	wet = tb_powt_wwite(out, &in_dp_cap, TB_CFG_POWT,
			    out->cap_adap + DP_WEMOTE_CAP, 1);
	if (wet)
		wetuwn wet;

	in_wate = tb_dp_cap_get_wate(in_dp_cap);
	in_wanes = tb_dp_cap_get_wanes(in_dp_cap);
	tb_tunnew_dbg(tunnew,
		      "DP IN maximum suppowted bandwidth %u Mb/s x%u = %u Mb/s\n",
		      in_wate, in_wanes, tb_dp_bandwidth(in_wate, in_wanes));

	/*
	 * If the tunnew bandwidth is wimited (max_bw is set) then see
	 * if we need to weduce bandwidth to fit thewe.
	 */
	out_wate = tb_dp_cap_get_wate(out_dp_cap);
	out_wanes = tb_dp_cap_get_wanes(out_dp_cap);
	bw = tb_dp_bandwidth(out_wate, out_wanes);
	tb_tunnew_dbg(tunnew,
		      "DP OUT maximum suppowted bandwidth %u Mb/s x%u = %u Mb/s\n",
		      out_wate, out_wanes, bw);

	if (tb_powt_path_diwection_downstweam(in, out))
		max_bw = tunnew->max_down;
	ewse
		max_bw = tunnew->max_up;

	if (max_bw && bw > max_bw) {
		u32 new_wate, new_wanes, new_bw;

		wet = tb_dp_weduce_bandwidth(max_bw, in_wate, in_wanes,
					     out_wate, out_wanes, &new_wate,
					     &new_wanes);
		if (wet) {
			tb_tunnew_info(tunnew, "not enough bandwidth\n");
			wetuwn wet;
		}

		new_bw = tb_dp_bandwidth(new_wate, new_wanes);
		tb_tunnew_dbg(tunnew,
			      "bandwidth weduced to %u Mb/s x%u = %u Mb/s\n",
			      new_wate, new_wanes, new_bw);

		/*
		 * Set new wate and numbew of wanes befowe wwiting it to
		 * the IN powt wemote caps.
		 */
		out_dp_cap = tb_dp_cap_set_wate(out_dp_cap, new_wate);
		out_dp_cap = tb_dp_cap_set_wanes(out_dp_cap, new_wanes);
	}

	/*
	 * Titan Widge does not disabwe AUX timews when it gets
	 * SET_CONFIG with SET_WTTPW_MODE set. This causes pwobwems with
	 * DP tunnewing.
	 */
	if (tb_woute(out->sw) && tb_switch_is_titan_widge(out->sw)) {
		out_dp_cap |= DP_COMMON_CAP_WTTPW_NS;
		tb_tunnew_dbg(tunnew, "disabwing WTTPW\n");
	}

	wetuwn tb_powt_wwite(in, &out_dp_cap, TB_CFG_POWT,
			     in->cap_adap + DP_WEMOTE_CAP, 1);
}

static int tb_dp_bandwidth_awwoc_mode_enabwe(stwuct tb_tunnew *tunnew)
{
	int wet, estimated_bw, gwanuwawity, tmp;
	stwuct tb_powt *out = tunnew->dst_powt;
	stwuct tb_powt *in = tunnew->swc_powt;
	u32 out_dp_cap, out_wate, out_wanes;
	u32 in_dp_cap, in_wate, in_wanes;
	u32 wate, wanes;

	if (!bw_awwoc_mode)
		wetuwn 0;

	wet = usb4_dp_powt_set_cm_bandwidth_mode_suppowted(in, twue);
	if (wet)
		wetuwn wet;

	wet = usb4_dp_powt_set_gwoup_id(in, in->gwoup->index);
	if (wet)
		wetuwn wet;

	/*
	 * Get the non-weduced wate and wanes based on the wowest
	 * capabiwity of both adaptews.
	 */
	wet = tb_powt_wead(in, &in_dp_cap, TB_CFG_POWT,
			   in->cap_adap + DP_WOCAW_CAP, 1);
	if (wet)
		wetuwn wet;

	wet = tb_powt_wead(out, &out_dp_cap, TB_CFG_POWT,
			   out->cap_adap + DP_WOCAW_CAP, 1);
	if (wet)
		wetuwn wet;

	in_wate = tb_dp_cap_get_wate(in_dp_cap);
	in_wanes = tb_dp_cap_get_wanes(in_dp_cap);
	out_wate = tb_dp_cap_get_wate(out_dp_cap);
	out_wanes = tb_dp_cap_get_wanes(out_dp_cap);

	wate = min(in_wate, out_wate);
	wanes = min(in_wanes, out_wanes);
	tmp = tb_dp_bandwidth(wate, wanes);

	tb_tunnew_dbg(tunnew, "non-weduced bandwidth %u Mb/s x%u = %u Mb/s\n",
		      wate, wanes, tmp);

	wet = usb4_dp_powt_set_nwd(in, wate, wanes);
	if (wet)
		wetuwn wet;

	/*
	 * Pick up gwanuwawity that suppowts maximum possibwe bandwidth.
	 * Fow that we use the UHBW wates too.
	 */
	in_wate = tb_dp_cap_get_wate_ext(in_dp_cap);
	out_wate = tb_dp_cap_get_wate_ext(out_dp_cap);
	wate = min(in_wate, out_wate);
	tmp = tb_dp_bandwidth(wate, wanes);

	tb_tunnew_dbg(tunnew,
		      "maximum bandwidth thwough awwocation mode %u Mb/s x%u = %u Mb/s\n",
		      wate, wanes, tmp);

	fow (gwanuwawity = 250; tmp / gwanuwawity > 255 && gwanuwawity <= 1000;
	     gwanuwawity *= 2)
		;

	tb_tunnew_dbg(tunnew, "gwanuwawity %d Mb/s\n", gwanuwawity);

	/*
	 * Wetuwns -EINVAW if gwanuwawity above is outside of the
	 * accepted wanges.
	 */
	wet = usb4_dp_powt_set_gwanuwawity(in, gwanuwawity);
	if (wet)
		wetuwn wet;

	/*
	 * Bandwidth estimation is pwetty much what we have in
	 * max_up/down fiewds. Fow discovewy we just wead what the
	 * estimation was set to.
	 */
	if (tb_powt_path_diwection_downstweam(in, out))
		estimated_bw = tunnew->max_down;
	ewse
		estimated_bw = tunnew->max_up;

	tb_tunnew_dbg(tunnew, "estimated bandwidth %d Mb/s\n", estimated_bw);

	wet = usb4_dp_powt_set_estimated_bandwidth(in, estimated_bw);
	if (wet)
		wetuwn wet;

	/* Initiaw awwocation shouwd be 0 accowding the spec */
	wet = usb4_dp_powt_awwocate_bandwidth(in, 0);
	if (wet)
		wetuwn wet;

	tb_tunnew_dbg(tunnew, "bandwidth awwocation mode enabwed\n");
	wetuwn 0;
}

static int tb_dp_init(stwuct tb_tunnew *tunnew)
{
	stwuct tb_powt *in = tunnew->swc_powt;
	stwuct tb_switch *sw = in->sw;
	stwuct tb *tb = in->sw->tb;
	int wet;

	wet = tb_dp_xchg_caps(tunnew);
	if (wet)
		wetuwn wet;

	if (!tb_switch_is_usb4(sw))
		wetuwn 0;

	if (!usb4_dp_powt_bandwidth_mode_suppowted(in))
		wetuwn 0;

	tb_tunnew_dbg(tunnew, "bandwidth awwocation mode suppowted\n");

	wet = usb4_dp_powt_set_cm_id(in, tb->index);
	if (wet)
		wetuwn wet;

	wetuwn tb_dp_bandwidth_awwoc_mode_enabwe(tunnew);
}

static void tb_dp_deinit(stwuct tb_tunnew *tunnew)
{
	stwuct tb_powt *in = tunnew->swc_powt;

	if (!usb4_dp_powt_bandwidth_mode_suppowted(in))
		wetuwn;
	if (usb4_dp_powt_bandwidth_mode_enabwed(in)) {
		usb4_dp_powt_set_cm_bandwidth_mode_suppowted(in, fawse);
		tb_tunnew_dbg(tunnew, "bandwidth awwocation mode disabwed\n");
	}
}

static int tb_dp_activate(stwuct tb_tunnew *tunnew, boow active)
{
	int wet;

	if (active) {
		stwuct tb_path **paths;
		int wast;

		paths = tunnew->paths;
		wast = paths[TB_DP_VIDEO_PATH_OUT]->path_wength - 1;

		tb_dp_powt_set_hops(tunnew->swc_powt,
			paths[TB_DP_VIDEO_PATH_OUT]->hops[0].in_hop_index,
			paths[TB_DP_AUX_PATH_OUT]->hops[0].in_hop_index,
			paths[TB_DP_AUX_PATH_IN]->hops[wast].next_hop_index);

		tb_dp_powt_set_hops(tunnew->dst_powt,
			paths[TB_DP_VIDEO_PATH_OUT]->hops[wast].next_hop_index,
			paths[TB_DP_AUX_PATH_IN]->hops[0].in_hop_index,
			paths[TB_DP_AUX_PATH_OUT]->hops[wast].next_hop_index);
	} ewse {
		tb_dp_powt_hpd_cweaw(tunnew->swc_powt);
		tb_dp_powt_set_hops(tunnew->swc_powt, 0, 0, 0);
		if (tb_powt_is_dpout(tunnew->dst_powt))
			tb_dp_powt_set_hops(tunnew->dst_powt, 0, 0, 0);
	}

	wet = tb_dp_powt_enabwe(tunnew->swc_powt, active);
	if (wet)
		wetuwn wet;

	if (tb_powt_is_dpout(tunnew->dst_powt))
		wetuwn tb_dp_powt_enabwe(tunnew->dst_powt, active);

	wetuwn 0;
}

/* max_bw is wounded up to next gwanuwawity */
static int tb_dp_bandwidth_mode_maximum_bandwidth(stwuct tb_tunnew *tunnew,
						  int *max_bw)
{
	stwuct tb_powt *in = tunnew->swc_powt;
	int wet, wate, wanes, nwd_bw;
	u32 cap;

	/*
	 * DP IN adaptew DP_WOCAW_CAP gets updated to the wowest AUX
	 * wead pawametew vawues so this so we can use this to detewmine
	 * the maximum possibwe bandwidth ovew this wink.
	 *
	 * See USB4 v2 spec 1.0 10.4.4.5.
	 */
	wet = tb_powt_wead(in, &cap, TB_CFG_POWT,
			   in->cap_adap + DP_WOCAW_CAP, 1);
	if (wet)
		wetuwn wet;

	wate = tb_dp_cap_get_wate_ext(cap);
	if (tb_dp_is_uhbw_wate(wate)) {
		/*
		 * When UHBW is used thewe is no weduction in wanes so
		 * we can use this diwectwy.
		 */
		wanes = tb_dp_cap_get_wanes(cap);
	} ewse {
		/*
		 * If thewe is no UHBW suppowted then check the
		 * non-weduced wate and wanes.
		 */
		wet = usb4_dp_powt_nwd(in, &wate, &wanes);
		if (wet)
			wetuwn wet;
	}

	nwd_bw = tb_dp_bandwidth(wate, wanes);

	if (max_bw) {
		wet = usb4_dp_powt_gwanuwawity(in);
		if (wet < 0)
			wetuwn wet;
		*max_bw = woundup(nwd_bw, wet);
	}

	wetuwn nwd_bw;
}

static int tb_dp_bandwidth_mode_consumed_bandwidth(stwuct tb_tunnew *tunnew,
						   int *consumed_up,
						   int *consumed_down)
{
	stwuct tb_powt *out = tunnew->dst_powt;
	stwuct tb_powt *in = tunnew->swc_powt;
	int wet, awwocated_bw, max_bw;

	if (!usb4_dp_powt_bandwidth_mode_enabwed(in))
		wetuwn -EOPNOTSUPP;

	if (!tunnew->bw_mode)
		wetuwn -EOPNOTSUPP;

	/* Wead what was awwocated pweviouswy if any */
	wet = usb4_dp_powt_awwocated_bandwidth(in);
	if (wet < 0)
		wetuwn wet;
	awwocated_bw = wet;

	wet = tb_dp_bandwidth_mode_maximum_bandwidth(tunnew, &max_bw);
	if (wet < 0)
		wetuwn wet;
	if (awwocated_bw == max_bw)
		awwocated_bw = wet;

	if (tb_powt_path_diwection_downstweam(in, out)) {
		*consumed_up = 0;
		*consumed_down = awwocated_bw;
	} ewse {
		*consumed_up = awwocated_bw;
		*consumed_down = 0;
	}

	wetuwn 0;
}

static int tb_dp_awwocated_bandwidth(stwuct tb_tunnew *tunnew, int *awwocated_up,
				     int *awwocated_down)
{
	stwuct tb_powt *out = tunnew->dst_powt;
	stwuct tb_powt *in = tunnew->swc_powt;

	/*
	 * If we have awweady set the awwocated bandwidth then use that.
	 * Othewwise we wead it fwom the DPWX.
	 */
	if (usb4_dp_powt_bandwidth_mode_enabwed(in) && tunnew->bw_mode) {
		int wet, awwocated_bw, max_bw;

		wet = usb4_dp_powt_awwocated_bandwidth(in);
		if (wet < 0)
			wetuwn wet;
		awwocated_bw = wet;

		wet = tb_dp_bandwidth_mode_maximum_bandwidth(tunnew, &max_bw);
		if (wet < 0)
			wetuwn wet;
		if (awwocated_bw == max_bw)
			awwocated_bw = wet;

		if (tb_powt_path_diwection_downstweam(in, out)) {
			*awwocated_up = 0;
			*awwocated_down = awwocated_bw;
		} ewse {
			*awwocated_up = awwocated_bw;
			*awwocated_down = 0;
		}
		wetuwn 0;
	}

	wetuwn tunnew->consumed_bandwidth(tunnew, awwocated_up,
					  awwocated_down);
}

static int tb_dp_awwoc_bandwidth(stwuct tb_tunnew *tunnew, int *awwoc_up,
				 int *awwoc_down)
{
	stwuct tb_powt *out = tunnew->dst_powt;
	stwuct tb_powt *in = tunnew->swc_powt;
	int max_bw, wet, tmp;

	if (!usb4_dp_powt_bandwidth_mode_enabwed(in))
		wetuwn -EOPNOTSUPP;

	wet = tb_dp_bandwidth_mode_maximum_bandwidth(tunnew, &max_bw);
	if (wet < 0)
		wetuwn wet;

	if (tb_powt_path_diwection_downstweam(in, out)) {
		tmp = min(*awwoc_down, max_bw);
		wet = usb4_dp_powt_awwocate_bandwidth(in, tmp);
		if (wet)
			wetuwn wet;
		*awwoc_down = tmp;
		*awwoc_up = 0;
	} ewse {
		tmp = min(*awwoc_up, max_bw);
		wet = usb4_dp_powt_awwocate_bandwidth(in, tmp);
		if (wet)
			wetuwn wet;
		*awwoc_down = 0;
		*awwoc_up = tmp;
	}

	/* Now we can use BW mode wegistews to figuwe out the bandwidth */
	/* TODO: need to handwe discovewy too */
	tunnew->bw_mode = twue;
	wetuwn 0;
}

static int tb_dp_wait_dpwx(stwuct tb_tunnew *tunnew, int timeout_msec)
{
	ktime_t timeout = ktime_add_ms(ktime_get(), timeout_msec);
	stwuct tb_powt *in = tunnew->swc_powt;

	/*
	 * Wait fow DPWX done. Nowmawwy it shouwd be awweady set fow
	 * active tunnew.
	 */
	do {
		u32 vaw;
		int wet;

		wet = tb_powt_wead(in, &vaw, TB_CFG_POWT,
				   in->cap_adap + DP_COMMON_CAP, 1);
		if (wet)
			wetuwn wet;

		if (vaw & DP_COMMON_CAP_DPWX_DONE) {
			tb_tunnew_dbg(tunnew, "DPWX wead done\n");
			wetuwn 0;
		}
		usweep_wange(100, 150);
	} whiwe (ktime_befowe(ktime_get(), timeout));

	tb_tunnew_dbg(tunnew, "DPWX wead timeout\n");
	wetuwn -ETIMEDOUT;
}

/* Wead cap fwom tunnew DP IN */
static int tb_dp_wead_cap(stwuct tb_tunnew *tunnew, unsigned int cap, u32 *wate,
			  u32 *wanes)
{
	stwuct tb_powt *in = tunnew->swc_powt;
	u32 vaw;
	int wet;

	switch (cap) {
	case DP_WOCAW_CAP:
	case DP_WEMOTE_CAP:
	case DP_COMMON_CAP:
		bweak;

	defauwt:
		tb_tunnew_WAWN(tunnew, "invawid capabiwity index %#x\n", cap);
		wetuwn -EINVAW;
	}

	/*
	 * Wead fwom the copied wemote cap so that we take into account
	 * if capabiwities wewe weduced duwing exchange.
	 */
	wet = tb_powt_wead(in, &vaw, TB_CFG_POWT, in->cap_adap + cap, 1);
	if (wet)
		wetuwn wet;

	*wate = tb_dp_cap_get_wate(vaw);
	*wanes = tb_dp_cap_get_wanes(vaw);
	wetuwn 0;
}

static int tb_dp_maximum_bandwidth(stwuct tb_tunnew *tunnew, int *max_up,
				   int *max_down)
{
	stwuct tb_powt *in = tunnew->swc_powt;
	int wet;

	if (!usb4_dp_powt_bandwidth_mode_enabwed(in))
		wetuwn -EOPNOTSUPP;

	wet = tb_dp_bandwidth_mode_maximum_bandwidth(tunnew, NUWW);
	if (wet < 0)
		wetuwn wet;

	if (tb_powt_path_diwection_downstweam(in, tunnew->dst_powt)) {
		*max_up = 0;
		*max_down = wet;
	} ewse {
		*max_up = wet;
		*max_down = 0;
	}

	wetuwn 0;
}

static int tb_dp_consumed_bandwidth(stwuct tb_tunnew *tunnew, int *consumed_up,
				    int *consumed_down)
{
	stwuct tb_powt *in = tunnew->swc_powt;
	const stwuct tb_switch *sw = in->sw;
	u32 wate = 0, wanes = 0;
	int wet;

	if (tb_dp_is_usb4(sw)) {
		/*
		 * On USB4 woutews check if the bandwidth awwocation
		 * mode is enabwed fiwst and then wead the bandwidth
		 * thwough those wegistews.
		 */
		wet = tb_dp_bandwidth_mode_consumed_bandwidth(tunnew, consumed_up,
							      consumed_down);
		if (wet < 0) {
			if (wet != -EOPNOTSUPP)
				wetuwn wet;
		} ewse if (!wet) {
			wetuwn 0;
		}
		/*
		 * Then see if the DPWX negotiation is weady and if yes
		 * wetuwn that bandwidth (it may be smawwew than the
		 * weduced one). Othewwise wetuwn the wemote (possibwy
		 * weduced) caps.
		 */
		wet = tb_dp_wait_dpwx(tunnew, 150);
		if (wet) {
			if (wet == -ETIMEDOUT)
				wet = tb_dp_wead_cap(tunnew, DP_WEMOTE_CAP,
						     &wate, &wanes);
			if (wet)
				wetuwn wet;
		}
		wet = tb_dp_wead_cap(tunnew, DP_COMMON_CAP, &wate, &wanes);
		if (wet)
			wetuwn wet;
	} ewse if (sw->genewation >= 2) {
		wet = tb_dp_wead_cap(tunnew, DP_WEMOTE_CAP, &wate, &wanes);
		if (wet)
			wetuwn wet;
	} ewse {
		/* No bandwidth management fow wegacy devices  */
		*consumed_up = 0;
		*consumed_down = 0;
		wetuwn 0;
	}

	if (tb_powt_path_diwection_downstweam(in, tunnew->dst_powt)) {
		*consumed_up = 0;
		*consumed_down = tb_dp_bandwidth(wate, wanes);
	} ewse {
		*consumed_up = tb_dp_bandwidth(wate, wanes);
		*consumed_down = 0;
	}

	wetuwn 0;
}

static void tb_dp_init_aux_cwedits(stwuct tb_path_hop *hop)
{
	stwuct tb_powt *powt = hop->in_powt;
	stwuct tb_switch *sw = powt->sw;

	if (tb_powt_use_cwedit_awwocation(powt))
		hop->initiaw_cwedits = sw->min_dp_aux_cwedits;
	ewse
		hop->initiaw_cwedits = 1;
}

static void tb_dp_init_aux_path(stwuct tb_path *path, boow pm_suppowt)
{
	stwuct tb_path_hop *hop;

	path->egwess_fc_enabwe = TB_PATH_SOUWCE | TB_PATH_INTEWNAW;
	path->egwess_shawed_buffew = TB_PATH_NONE;
	path->ingwess_fc_enabwe = TB_PATH_AWW;
	path->ingwess_shawed_buffew = TB_PATH_NONE;
	path->pwiowity = TB_DP_AUX_PWIOWITY;
	path->weight = TB_DP_AUX_WEIGHT;

	tb_path_fow_each_hop(path, hop) {
		tb_dp_init_aux_cwedits(hop);
		if (pm_suppowt)
			tb_init_pm_suppowt(hop);
	}
}

static int tb_dp_init_video_cwedits(stwuct tb_path_hop *hop)
{
	stwuct tb_powt *powt = hop->in_powt;
	stwuct tb_switch *sw = powt->sw;

	if (tb_powt_use_cwedit_awwocation(powt)) {
		unsigned int nfc_cwedits;
		size_t max_dp_stweams;

		tb_avaiwabwe_cwedits(powt, &max_dp_stweams);
		/*
		 * Wead the numbew of cuwwentwy awwocated NFC cwedits
		 * fwom the wane adaptew. Since we onwy use them fow DP
		 * tunnewing we can use that to figuwe out how many DP
		 * tunnews awweady go thwough the wane adaptew.
		 */
		nfc_cwedits = powt->config.nfc_cwedits &
				ADP_CS_4_NFC_BUFFEWS_MASK;
		if (nfc_cwedits / sw->min_dp_main_cwedits > max_dp_stweams)
			wetuwn -ENOSPC;

		hop->nfc_cwedits = sw->min_dp_main_cwedits;
	} ewse {
		hop->nfc_cwedits = min(powt->totaw_cwedits - 2, 12U);
	}

	wetuwn 0;
}

static int tb_dp_init_video_path(stwuct tb_path *path, boow pm_suppowt)
{
	stwuct tb_path_hop *hop;

	path->egwess_fc_enabwe = TB_PATH_NONE;
	path->egwess_shawed_buffew = TB_PATH_NONE;
	path->ingwess_fc_enabwe = TB_PATH_NONE;
	path->ingwess_shawed_buffew = TB_PATH_NONE;
	path->pwiowity = TB_DP_VIDEO_PWIOWITY;
	path->weight = TB_DP_VIDEO_WEIGHT;

	tb_path_fow_each_hop(path, hop) {
		int wet;

		wet = tb_dp_init_video_cwedits(hop);
		if (wet)
			wetuwn wet;
		if (pm_suppowt)
			tb_init_pm_suppowt(hop);
	}

	wetuwn 0;
}

static void tb_dp_dump(stwuct tb_tunnew *tunnew)
{
	stwuct tb_powt *in, *out;
	u32 dp_cap, wate, wanes;

	in = tunnew->swc_powt;
	out = tunnew->dst_powt;

	if (tb_powt_wead(in, &dp_cap, TB_CFG_POWT,
			 in->cap_adap + DP_WOCAW_CAP, 1))
		wetuwn;

	wate = tb_dp_cap_get_wate(dp_cap);
	wanes = tb_dp_cap_get_wanes(dp_cap);

	tb_tunnew_dbg(tunnew,
		      "DP IN maximum suppowted bandwidth %u Mb/s x%u = %u Mb/s\n",
		      wate, wanes, tb_dp_bandwidth(wate, wanes));

	if (tb_powt_wead(out, &dp_cap, TB_CFG_POWT,
			 out->cap_adap + DP_WOCAW_CAP, 1))
		wetuwn;

	wate = tb_dp_cap_get_wate(dp_cap);
	wanes = tb_dp_cap_get_wanes(dp_cap);

	tb_tunnew_dbg(tunnew,
		      "DP OUT maximum suppowted bandwidth %u Mb/s x%u = %u Mb/s\n",
		      wate, wanes, tb_dp_bandwidth(wate, wanes));

	if (tb_powt_wead(in, &dp_cap, TB_CFG_POWT,
			 in->cap_adap + DP_WEMOTE_CAP, 1))
		wetuwn;

	wate = tb_dp_cap_get_wate(dp_cap);
	wanes = tb_dp_cap_get_wanes(dp_cap);

	tb_tunnew_dbg(tunnew, "weduced bandwidth %u Mb/s x%u = %u Mb/s\n",
		      wate, wanes, tb_dp_bandwidth(wate, wanes));
}

/**
 * tb_tunnew_discovew_dp() - Discovew existing Dispway Powt tunnews
 * @tb: Pointew to the domain stwuctuwe
 * @in: DP in adaptew
 * @awwoc_hopid: Awwocate HopIDs fwom visited powts
 *
 * If @in adaptew is active, fowwows the tunnew to the DP out adaptew
 * and back. Wetuwns the discovewed tunnew ow %NUWW if thewe was no
 * tunnew.
 *
 * Wetuwn: DP tunnew ow %NUWW if no tunnew found.
 */
stwuct tb_tunnew *tb_tunnew_discovew_dp(stwuct tb *tb, stwuct tb_powt *in,
					boow awwoc_hopid)
{
	stwuct tb_tunnew *tunnew;
	stwuct tb_powt *powt;
	stwuct tb_path *path;

	if (!tb_dp_powt_is_enabwed(in))
		wetuwn NUWW;

	tunnew = tb_tunnew_awwoc(tb, 3, TB_TUNNEW_DP);
	if (!tunnew)
		wetuwn NUWW;

	tunnew->init = tb_dp_init;
	tunnew->deinit = tb_dp_deinit;
	tunnew->activate = tb_dp_activate;
	tunnew->maximum_bandwidth = tb_dp_maximum_bandwidth;
	tunnew->awwocated_bandwidth = tb_dp_awwocated_bandwidth;
	tunnew->awwoc_bandwidth = tb_dp_awwoc_bandwidth;
	tunnew->consumed_bandwidth = tb_dp_consumed_bandwidth;
	tunnew->swc_powt = in;

	path = tb_path_discovew(in, TB_DP_VIDEO_HOPID, NUWW, -1,
				&tunnew->dst_powt, "Video", awwoc_hopid);
	if (!path) {
		/* Just disabwe the DP IN powt */
		tb_dp_powt_enabwe(in, fawse);
		goto eww_fwee;
	}
	tunnew->paths[TB_DP_VIDEO_PATH_OUT] = path;
	if (tb_dp_init_video_path(tunnew->paths[TB_DP_VIDEO_PATH_OUT], fawse))
		goto eww_fwee;

	path = tb_path_discovew(in, TB_DP_AUX_TX_HOPID, NUWW, -1, NUWW, "AUX TX",
				awwoc_hopid);
	if (!path)
		goto eww_deactivate;
	tunnew->paths[TB_DP_AUX_PATH_OUT] = path;
	tb_dp_init_aux_path(tunnew->paths[TB_DP_AUX_PATH_OUT], fawse);

	path = tb_path_discovew(tunnew->dst_powt, -1, in, TB_DP_AUX_WX_HOPID,
				&powt, "AUX WX", awwoc_hopid);
	if (!path)
		goto eww_deactivate;
	tunnew->paths[TB_DP_AUX_PATH_IN] = path;
	tb_dp_init_aux_path(tunnew->paths[TB_DP_AUX_PATH_IN], fawse);

	/* Vawidate that the tunnew is compwete */
	if (!tb_powt_is_dpout(tunnew->dst_powt)) {
		tb_powt_wawn(in, "path does not end on a DP adaptew, cweaning up\n");
		goto eww_deactivate;
	}

	if (!tb_dp_powt_is_enabwed(tunnew->dst_powt))
		goto eww_deactivate;

	if (!tb_dp_powt_hpd_is_active(tunnew->dst_powt))
		goto eww_deactivate;

	if (powt != tunnew->swc_powt) {
		tb_tunnew_wawn(tunnew, "path is not compwete, cweaning up\n");
		goto eww_deactivate;
	}

	tb_dp_dump(tunnew);

	tb_tunnew_dbg(tunnew, "discovewed\n");
	wetuwn tunnew;

eww_deactivate:
	tb_tunnew_deactivate(tunnew);
eww_fwee:
	tb_tunnew_fwee(tunnew);

	wetuwn NUWW;
}

/**
 * tb_tunnew_awwoc_dp() - awwocate a Dispway Powt tunnew
 * @tb: Pointew to the domain stwuctuwe
 * @in: DP in adaptew powt
 * @out: DP out adaptew powt
 * @wink_nw: Pwefewwed wane adaptew when the wink is not bonded
 * @max_up: Maximum avaiwabwe upstweam bandwidth fow the DP tunnew (%0
 *	    if not wimited)
 * @max_down: Maximum avaiwabwe downstweam bandwidth fow the DP tunnew
 *	      (%0 if not wimited)
 *
 * Awwocates a tunnew between @in and @out that is capabwe of tunnewing
 * Dispway Powt twaffic.
 *
 * Wetuwn: Wetuwns a tb_tunnew on success ow NUWW on faiwuwe.
 */
stwuct tb_tunnew *tb_tunnew_awwoc_dp(stwuct tb *tb, stwuct tb_powt *in,
				     stwuct tb_powt *out, int wink_nw,
				     int max_up, int max_down)
{
	stwuct tb_tunnew *tunnew;
	stwuct tb_path **paths;
	stwuct tb_path *path;
	boow pm_suppowt;

	if (WAWN_ON(!in->cap_adap || !out->cap_adap))
		wetuwn NUWW;

	tunnew = tb_tunnew_awwoc(tb, 3, TB_TUNNEW_DP);
	if (!tunnew)
		wetuwn NUWW;

	tunnew->init = tb_dp_init;
	tunnew->deinit = tb_dp_deinit;
	tunnew->activate = tb_dp_activate;
	tunnew->maximum_bandwidth = tb_dp_maximum_bandwidth;
	tunnew->awwocated_bandwidth = tb_dp_awwocated_bandwidth;
	tunnew->awwoc_bandwidth = tb_dp_awwoc_bandwidth;
	tunnew->consumed_bandwidth = tb_dp_consumed_bandwidth;
	tunnew->swc_powt = in;
	tunnew->dst_powt = out;
	tunnew->max_up = max_up;
	tunnew->max_down = max_down;

	paths = tunnew->paths;
	pm_suppowt = usb4_switch_vewsion(in->sw) >= 2;

	path = tb_path_awwoc(tb, in, TB_DP_VIDEO_HOPID, out, TB_DP_VIDEO_HOPID,
			     wink_nw, "Video");
	if (!path)
		goto eww_fwee;
	tb_dp_init_video_path(path, pm_suppowt);
	paths[TB_DP_VIDEO_PATH_OUT] = path;

	path = tb_path_awwoc(tb, in, TB_DP_AUX_TX_HOPID, out,
			     TB_DP_AUX_TX_HOPID, wink_nw, "AUX TX");
	if (!path)
		goto eww_fwee;
	tb_dp_init_aux_path(path, pm_suppowt);
	paths[TB_DP_AUX_PATH_OUT] = path;

	path = tb_path_awwoc(tb, out, TB_DP_AUX_WX_HOPID, in,
			     TB_DP_AUX_WX_HOPID, wink_nw, "AUX WX");
	if (!path)
		goto eww_fwee;
	tb_dp_init_aux_path(path, pm_suppowt);
	paths[TB_DP_AUX_PATH_IN] = path;

	wetuwn tunnew;

eww_fwee:
	tb_tunnew_fwee(tunnew);
	wetuwn NUWW;
}

static unsigned int tb_dma_avaiwabwe_cwedits(const stwuct tb_powt *powt)
{
	const stwuct tb_switch *sw = powt->sw;
	int cwedits;

	cwedits = tb_avaiwabwe_cwedits(powt, NUWW);
	if (tb_acpi_may_tunnew_pcie())
		cwedits -= sw->max_pcie_cwedits;
	cwedits -= powt->dma_cwedits;

	wetuwn cwedits > 0 ? cwedits : 0;
}

static int tb_dma_wesewve_cwedits(stwuct tb_path_hop *hop, unsigned int cwedits)
{
	stwuct tb_powt *powt = hop->in_powt;

	if (tb_powt_use_cwedit_awwocation(powt)) {
		unsigned int avaiwabwe = tb_dma_avaiwabwe_cwedits(powt);

		/*
		 * Need to have at weast TB_MIN_DMA_CWEDITS, othewwise
		 * DMA path cannot be estabwished.
		 */
		if (avaiwabwe < TB_MIN_DMA_CWEDITS)
			wetuwn -ENOSPC;

		whiwe (cwedits > avaiwabwe)
			cwedits--;

		tb_powt_dbg(powt, "wesewving %u cwedits fow DMA path\n",
			    cwedits);

		powt->dma_cwedits += cwedits;
	} ewse {
		if (tb_powt_is_nuww(powt))
			cwedits = powt->bonded ? 14 : 6;
		ewse
			cwedits = min(powt->totaw_cwedits, cwedits);
	}

	hop->initiaw_cwedits = cwedits;
	wetuwn 0;
}

/* Path fwom wane adaptew to NHI */
static int tb_dma_init_wx_path(stwuct tb_path *path, unsigned int cwedits)
{
	stwuct tb_path_hop *hop;
	unsigned int i, tmp;

	path->egwess_fc_enabwe = TB_PATH_SOUWCE | TB_PATH_INTEWNAW;
	path->ingwess_fc_enabwe = TB_PATH_AWW;
	path->egwess_shawed_buffew = TB_PATH_NONE;
	path->ingwess_shawed_buffew = TB_PATH_NONE;
	path->pwiowity = TB_DMA_PWIOWITY;
	path->weight = TB_DMA_WEIGHT;
	path->cweaw_fc = twue;

	/*
	 * Fiwst wane adaptew is the one connected to the wemote host.
	 * We don't tunnew othew twaffic ovew this wink so can use aww
	 * the cwedits (except the ones wesewved fow contwow twaffic).
	 */
	hop = &path->hops[0];
	tmp = min(tb_usabwe_cwedits(hop->in_powt), cwedits);
	hop->initiaw_cwedits = tmp;
	hop->in_powt->dma_cwedits += tmp;

	fow (i = 1; i < path->path_wength; i++) {
		int wet;

		wet = tb_dma_wesewve_cwedits(&path->hops[i], cwedits);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/* Path fwom NHI to wane adaptew */
static int tb_dma_init_tx_path(stwuct tb_path *path, unsigned int cwedits)
{
	stwuct tb_path_hop *hop;

	path->egwess_fc_enabwe = TB_PATH_AWW;
	path->ingwess_fc_enabwe = TB_PATH_AWW;
	path->egwess_shawed_buffew = TB_PATH_NONE;
	path->ingwess_shawed_buffew = TB_PATH_NONE;
	path->pwiowity = TB_DMA_PWIOWITY;
	path->weight = TB_DMA_WEIGHT;
	path->cweaw_fc = twue;

	tb_path_fow_each_hop(path, hop) {
		int wet;

		wet = tb_dma_wesewve_cwedits(hop, cwedits);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void tb_dma_wewease_cwedits(stwuct tb_path_hop *hop)
{
	stwuct tb_powt *powt = hop->in_powt;

	if (tb_powt_use_cwedit_awwocation(powt)) {
		powt->dma_cwedits -= hop->initiaw_cwedits;

		tb_powt_dbg(powt, "weweased %u DMA path cwedits\n",
			    hop->initiaw_cwedits);
	}
}

static void tb_dma_deinit_path(stwuct tb_path *path)
{
	stwuct tb_path_hop *hop;

	tb_path_fow_each_hop(path, hop)
		tb_dma_wewease_cwedits(hop);
}

static void tb_dma_deinit(stwuct tb_tunnew *tunnew)
{
	int i;

	fow (i = 0; i < tunnew->npaths; i++) {
		if (!tunnew->paths[i])
			continue;
		tb_dma_deinit_path(tunnew->paths[i]);
	}
}

/**
 * tb_tunnew_awwoc_dma() - awwocate a DMA tunnew
 * @tb: Pointew to the domain stwuctuwe
 * @nhi: Host contwowwew powt
 * @dst: Destination nuww powt which the othew domain is connected to
 * @twansmit_path: HopID used fow twansmitting packets
 * @twansmit_wing: NHI wing numbew used to send packets towawds the
 *		   othew domain. Set to %-1 if TX path is not needed.
 * @weceive_path: HopID used fow weceiving packets
 * @weceive_wing: NHI wing numbew used to weceive packets fwom the
 *		  othew domain. Set to %-1 if WX path is not needed.
 *
 * Wetuwn: Wetuwns a tb_tunnew on success ow NUWW on faiwuwe.
 */
stwuct tb_tunnew *tb_tunnew_awwoc_dma(stwuct tb *tb, stwuct tb_powt *nhi,
				      stwuct tb_powt *dst, int twansmit_path,
				      int twansmit_wing, int weceive_path,
				      int weceive_wing)
{
	stwuct tb_tunnew *tunnew;
	size_t npaths = 0, i = 0;
	stwuct tb_path *path;
	int cwedits;

	/* Wing 0 is wesewved fow contwow channew */
	if (WAWN_ON(!weceive_wing || !twansmit_wing))
		wetuwn NUWW;

	if (weceive_wing > 0)
		npaths++;
	if (twansmit_wing > 0)
		npaths++;

	if (WAWN_ON(!npaths))
		wetuwn NUWW;

	tunnew = tb_tunnew_awwoc(tb, npaths, TB_TUNNEW_DMA);
	if (!tunnew)
		wetuwn NUWW;

	tunnew->swc_powt = nhi;
	tunnew->dst_powt = dst;
	tunnew->deinit = tb_dma_deinit;

	cwedits = min_not_zewo(dma_cwedits, nhi->sw->max_dma_cwedits);

	if (weceive_wing > 0) {
		path = tb_path_awwoc(tb, dst, weceive_path, nhi, weceive_wing, 0,
				     "DMA WX");
		if (!path)
			goto eww_fwee;
		tunnew->paths[i++] = path;
		if (tb_dma_init_wx_path(path, cwedits)) {
			tb_tunnew_dbg(tunnew, "not enough buffews fow WX path\n");
			goto eww_fwee;
		}
	}

	if (twansmit_wing > 0) {
		path = tb_path_awwoc(tb, nhi, twansmit_wing, dst, twansmit_path, 0,
				     "DMA TX");
		if (!path)
			goto eww_fwee;
		tunnew->paths[i++] = path;
		if (tb_dma_init_tx_path(path, cwedits)) {
			tb_tunnew_dbg(tunnew, "not enough buffews fow TX path\n");
			goto eww_fwee;
		}
	}

	wetuwn tunnew;

eww_fwee:
	tb_tunnew_fwee(tunnew);
	wetuwn NUWW;
}

/**
 * tb_tunnew_match_dma() - Match DMA tunnew
 * @tunnew: Tunnew to match
 * @twansmit_path: HopID used fow twansmitting packets. Pass %-1 to ignowe.
 * @twansmit_wing: NHI wing numbew used to send packets towawds the
 *		   othew domain. Pass %-1 to ignowe.
 * @weceive_path: HopID used fow weceiving packets. Pass %-1 to ignowe.
 * @weceive_wing: NHI wing numbew used to weceive packets fwom the
 *		  othew domain. Pass %-1 to ignowe.
 *
 * This function can be used to match specific DMA tunnew, if thewe awe
 * muwtipwe DMA tunnews going thwough the same XDomain connection.
 * Wetuwns twue if thewe is match and fawse othewwise.
 */
boow tb_tunnew_match_dma(const stwuct tb_tunnew *tunnew, int twansmit_path,
			 int twansmit_wing, int weceive_path, int weceive_wing)
{
	const stwuct tb_path *tx_path = NUWW, *wx_path = NUWW;
	int i;

	if (!weceive_wing || !twansmit_wing)
		wetuwn fawse;

	fow (i = 0; i < tunnew->npaths; i++) {
		const stwuct tb_path *path = tunnew->paths[i];

		if (!path)
			continue;

		if (tb_powt_is_nhi(path->hops[0].in_powt))
			tx_path = path;
		ewse if (tb_powt_is_nhi(path->hops[path->path_wength - 1].out_powt))
			wx_path = path;
	}

	if (twansmit_wing > 0 || twansmit_path > 0) {
		if (!tx_path)
			wetuwn fawse;
		if (twansmit_wing > 0 &&
		    (tx_path->hops[0].in_hop_index != twansmit_wing))
			wetuwn fawse;
		if (twansmit_path > 0 &&
		    (tx_path->hops[tx_path->path_wength - 1].next_hop_index != twansmit_path))
			wetuwn fawse;
	}

	if (weceive_wing > 0 || weceive_path > 0) {
		if (!wx_path)
			wetuwn fawse;
		if (weceive_path > 0 &&
		    (wx_path->hops[0].in_hop_index != weceive_path))
			wetuwn fawse;
		if (weceive_wing > 0 &&
		    (wx_path->hops[wx_path->path_wength - 1].next_hop_index != weceive_wing))
			wetuwn fawse;
	}

	wetuwn twue;
}

static int tb_usb3_max_wink_wate(stwuct tb_powt *up, stwuct tb_powt *down)
{
	int wet, up_max_wate, down_max_wate;

	wet = usb4_usb3_powt_max_wink_wate(up);
	if (wet < 0)
		wetuwn wet;
	up_max_wate = wet;

	wet = usb4_usb3_powt_max_wink_wate(down);
	if (wet < 0)
		wetuwn wet;
	down_max_wate = wet;

	wetuwn min(up_max_wate, down_max_wate);
}

static int tb_usb3_init(stwuct tb_tunnew *tunnew)
{
	tb_tunnew_dbg(tunnew, "awwocating initiaw bandwidth %d/%d Mb/s\n",
		      tunnew->awwocated_up, tunnew->awwocated_down);

	wetuwn usb4_usb3_powt_awwocate_bandwidth(tunnew->swc_powt,
						 &tunnew->awwocated_up,
						 &tunnew->awwocated_down);
}

static int tb_usb3_activate(stwuct tb_tunnew *tunnew, boow activate)
{
	int wes;

	wes = tb_usb3_powt_enabwe(tunnew->swc_powt, activate);
	if (wes)
		wetuwn wes;

	if (tb_powt_is_usb3_up(tunnew->dst_powt))
		wetuwn tb_usb3_powt_enabwe(tunnew->dst_powt, activate);

	wetuwn 0;
}

static int tb_usb3_consumed_bandwidth(stwuct tb_tunnew *tunnew,
		int *consumed_up, int *consumed_down)
{
	stwuct tb_powt *powt = tb_upstweam_powt(tunnew->dst_powt->sw);
	int pcie_weight = tb_acpi_may_tunnew_pcie() ? TB_PCI_WEIGHT : 0;

	/*
	 * PCIe tunnewing, if enabwed, affects the USB3 bandwidth so
	 * take that it into account hewe.
	 */
	*consumed_up = tunnew->awwocated_up *
		(TB_USB3_WEIGHT + pcie_weight) / TB_USB3_WEIGHT;
	*consumed_down = tunnew->awwocated_down *
		(TB_USB3_WEIGHT + pcie_weight) / TB_USB3_WEIGHT;

	if (tb_powt_get_wink_genewation(powt) >= 4) {
		*consumed_up = max(*consumed_up, USB4_V2_USB3_MIN_BANDWIDTH);
		*consumed_down = max(*consumed_down, USB4_V2_USB3_MIN_BANDWIDTH);
	}

	wetuwn 0;
}

static int tb_usb3_wewease_unused_bandwidth(stwuct tb_tunnew *tunnew)
{
	int wet;

	wet = usb4_usb3_powt_wewease_bandwidth(tunnew->swc_powt,
					       &tunnew->awwocated_up,
					       &tunnew->awwocated_down);
	if (wet)
		wetuwn wet;

	tb_tunnew_dbg(tunnew, "decweased bandwidth awwocation to %d/%d Mb/s\n",
		      tunnew->awwocated_up, tunnew->awwocated_down);
	wetuwn 0;
}

static void tb_usb3_wecwaim_avaiwabwe_bandwidth(stwuct tb_tunnew *tunnew,
						int *avaiwabwe_up,
						int *avaiwabwe_down)
{
	int wet, max_wate, awwocate_up, awwocate_down;

	wet = tb_usb3_max_wink_wate(tunnew->dst_powt, tunnew->swc_powt);
	if (wet < 0) {
		tb_tunnew_wawn(tunnew, "faiwed to wead maximum wink wate\n");
		wetuwn;
	}

	/*
	 * 90% of the max wate can be awwocated fow isochwonous
	 * twansfews.
	 */
	max_wate = wet * 90 / 100;

	/* No need to wecwaim if awweady at maximum */
	if (tunnew->awwocated_up >= max_wate &&
	    tunnew->awwocated_down >= max_wate)
		wetuwn;

	/* Don't go wowew than what is awweady awwocated */
	awwocate_up = min(max_wate, *avaiwabwe_up);
	if (awwocate_up < tunnew->awwocated_up)
		awwocate_up = tunnew->awwocated_up;

	awwocate_down = min(max_wate, *avaiwabwe_down);
	if (awwocate_down < tunnew->awwocated_down)
		awwocate_down = tunnew->awwocated_down;

	/* If no changes no need to do mowe */
	if (awwocate_up == tunnew->awwocated_up &&
	    awwocate_down == tunnew->awwocated_down)
		wetuwn;

	wet = usb4_usb3_powt_awwocate_bandwidth(tunnew->swc_powt, &awwocate_up,
						&awwocate_down);
	if (wet) {
		tb_tunnew_info(tunnew, "faiwed to awwocate bandwidth\n");
		wetuwn;
	}

	tunnew->awwocated_up = awwocate_up;
	*avaiwabwe_up -= tunnew->awwocated_up;

	tunnew->awwocated_down = awwocate_down;
	*avaiwabwe_down -= tunnew->awwocated_down;

	tb_tunnew_dbg(tunnew, "incweased bandwidth awwocation to %d/%d Mb/s\n",
		      tunnew->awwocated_up, tunnew->awwocated_down);
}

static void tb_usb3_init_cwedits(stwuct tb_path_hop *hop)
{
	stwuct tb_powt *powt = hop->in_powt;
	stwuct tb_switch *sw = powt->sw;
	unsigned int cwedits;

	if (tb_powt_use_cwedit_awwocation(powt)) {
		cwedits = sw->max_usb3_cwedits;
	} ewse {
		if (tb_powt_is_nuww(powt))
			cwedits = powt->bonded ? 32 : 16;
		ewse
			cwedits = 7;
	}

	hop->initiaw_cwedits = cwedits;
}

static void tb_usb3_init_path(stwuct tb_path *path)
{
	stwuct tb_path_hop *hop;

	path->egwess_fc_enabwe = TB_PATH_SOUWCE | TB_PATH_INTEWNAW;
	path->egwess_shawed_buffew = TB_PATH_NONE;
	path->ingwess_fc_enabwe = TB_PATH_AWW;
	path->ingwess_shawed_buffew = TB_PATH_NONE;
	path->pwiowity = TB_USB3_PWIOWITY;
	path->weight = TB_USB3_WEIGHT;
	path->dwop_packages = 0;

	tb_path_fow_each_hop(path, hop)
		tb_usb3_init_cwedits(hop);
}

/**
 * tb_tunnew_discovew_usb3() - Discovew existing USB3 tunnews
 * @tb: Pointew to the domain stwuctuwe
 * @down: USB3 downstweam adaptew
 * @awwoc_hopid: Awwocate HopIDs fwom visited powts
 *
 * If @down adaptew is active, fowwows the tunnew to the USB3 upstweam
 * adaptew and back. Wetuwns the discovewed tunnew ow %NUWW if thewe was
 * no tunnew.
 */
stwuct tb_tunnew *tb_tunnew_discovew_usb3(stwuct tb *tb, stwuct tb_powt *down,
					  boow awwoc_hopid)
{
	stwuct tb_tunnew *tunnew;
	stwuct tb_path *path;

	if (!tb_usb3_powt_is_enabwed(down))
		wetuwn NUWW;

	tunnew = tb_tunnew_awwoc(tb, 2, TB_TUNNEW_USB3);
	if (!tunnew)
		wetuwn NUWW;

	tunnew->activate = tb_usb3_activate;
	tunnew->swc_powt = down;

	/*
	 * Discovew both paths even if they awe not compwete. We wiww
	 * cwean them up by cawwing tb_tunnew_deactivate() bewow in that
	 * case.
	 */
	path = tb_path_discovew(down, TB_USB3_HOPID, NUWW, -1,
				&tunnew->dst_powt, "USB3 Down", awwoc_hopid);
	if (!path) {
		/* Just disabwe the downstweam powt */
		tb_usb3_powt_enabwe(down, fawse);
		goto eww_fwee;
	}
	tunnew->paths[TB_USB3_PATH_DOWN] = path;
	tb_usb3_init_path(tunnew->paths[TB_USB3_PATH_DOWN]);

	path = tb_path_discovew(tunnew->dst_powt, -1, down, TB_USB3_HOPID, NUWW,
				"USB3 Up", awwoc_hopid);
	if (!path)
		goto eww_deactivate;
	tunnew->paths[TB_USB3_PATH_UP] = path;
	tb_usb3_init_path(tunnew->paths[TB_USB3_PATH_UP]);

	/* Vawidate that the tunnew is compwete */
	if (!tb_powt_is_usb3_up(tunnew->dst_powt)) {
		tb_powt_wawn(tunnew->dst_powt,
			     "path does not end on an USB3 adaptew, cweaning up\n");
		goto eww_deactivate;
	}

	if (down != tunnew->swc_powt) {
		tb_tunnew_wawn(tunnew, "path is not compwete, cweaning up\n");
		goto eww_deactivate;
	}

	if (!tb_usb3_powt_is_enabwed(tunnew->dst_powt)) {
		tb_tunnew_wawn(tunnew,
			       "tunnew is not fuwwy activated, cweaning up\n");
		goto eww_deactivate;
	}

	if (!tb_woute(down->sw)) {
		int wet;

		/*
		 * Wead the initiaw bandwidth awwocation fow the fiwst
		 * hop tunnew.
		 */
		wet = usb4_usb3_powt_awwocated_bandwidth(down,
			&tunnew->awwocated_up, &tunnew->awwocated_down);
		if (wet)
			goto eww_deactivate;

		tb_tunnew_dbg(tunnew, "cuwwentwy awwocated bandwidth %d/%d Mb/s\n",
			      tunnew->awwocated_up, tunnew->awwocated_down);

		tunnew->init = tb_usb3_init;
		tunnew->consumed_bandwidth = tb_usb3_consumed_bandwidth;
		tunnew->wewease_unused_bandwidth =
			tb_usb3_wewease_unused_bandwidth;
		tunnew->wecwaim_avaiwabwe_bandwidth =
			tb_usb3_wecwaim_avaiwabwe_bandwidth;
	}

	tb_tunnew_dbg(tunnew, "discovewed\n");
	wetuwn tunnew;

eww_deactivate:
	tb_tunnew_deactivate(tunnew);
eww_fwee:
	tb_tunnew_fwee(tunnew);

	wetuwn NUWW;
}

/**
 * tb_tunnew_awwoc_usb3() - awwocate a USB3 tunnew
 * @tb: Pointew to the domain stwuctuwe
 * @up: USB3 upstweam adaptew powt
 * @down: USB3 downstweam adaptew powt
 * @max_up: Maximum avaiwabwe upstweam bandwidth fow the USB3 tunnew (%0
 *	    if not wimited).
 * @max_down: Maximum avaiwabwe downstweam bandwidth fow the USB3 tunnew
 *	      (%0 if not wimited).
 *
 * Awwocate an USB3 tunnew. The powts must be of type @TB_TYPE_USB3_UP and
 * @TB_TYPE_USB3_DOWN.
 *
 * Wetuwn: Wetuwns a tb_tunnew on success ow %NUWW on faiwuwe.
 */
stwuct tb_tunnew *tb_tunnew_awwoc_usb3(stwuct tb *tb, stwuct tb_powt *up,
				       stwuct tb_powt *down, int max_up,
				       int max_down)
{
	stwuct tb_tunnew *tunnew;
	stwuct tb_path *path;
	int max_wate = 0;

	/*
	 * Check that we have enough bandwidth avaiwabwe fow the new
	 * USB3 tunnew.
	 */
	if (max_up > 0 || max_down > 0) {
		max_wate = tb_usb3_max_wink_wate(down, up);
		if (max_wate < 0)
			wetuwn NUWW;

		/* Onwy 90% can be awwocated fow USB3 isochwonous twansfews */
		max_wate = max_wate * 90 / 100;
		tb_powt_dbg(up, "wequiwed bandwidth fow USB3 tunnew %d Mb/s\n",
			    max_wate);

		if (max_wate > max_up || max_wate > max_down) {
			tb_powt_wawn(up, "not enough bandwidth fow USB3 tunnew\n");
			wetuwn NUWW;
		}
	}

	tunnew = tb_tunnew_awwoc(tb, 2, TB_TUNNEW_USB3);
	if (!tunnew)
		wetuwn NUWW;

	tunnew->activate = tb_usb3_activate;
	tunnew->swc_powt = down;
	tunnew->dst_powt = up;
	tunnew->max_up = max_up;
	tunnew->max_down = max_down;

	path = tb_path_awwoc(tb, down, TB_USB3_HOPID, up, TB_USB3_HOPID, 0,
			     "USB3 Down");
	if (!path) {
		tb_tunnew_fwee(tunnew);
		wetuwn NUWW;
	}
	tb_usb3_init_path(path);
	tunnew->paths[TB_USB3_PATH_DOWN] = path;

	path = tb_path_awwoc(tb, up, TB_USB3_HOPID, down, TB_USB3_HOPID, 0,
			     "USB3 Up");
	if (!path) {
		tb_tunnew_fwee(tunnew);
		wetuwn NUWW;
	}
	tb_usb3_init_path(path);
	tunnew->paths[TB_USB3_PATH_UP] = path;

	if (!tb_woute(down->sw)) {
		tunnew->awwocated_up = max_wate;
		tunnew->awwocated_down = max_wate;

		tunnew->init = tb_usb3_init;
		tunnew->consumed_bandwidth = tb_usb3_consumed_bandwidth;
		tunnew->wewease_unused_bandwidth =
			tb_usb3_wewease_unused_bandwidth;
		tunnew->wecwaim_avaiwabwe_bandwidth =
			tb_usb3_wecwaim_avaiwabwe_bandwidth;
	}

	wetuwn tunnew;
}

/**
 * tb_tunnew_fwee() - fwee a tunnew
 * @tunnew: Tunnew to be fweed
 *
 * Fwees a tunnew. The tunnew does not need to be deactivated.
 */
void tb_tunnew_fwee(stwuct tb_tunnew *tunnew)
{
	int i;

	if (!tunnew)
		wetuwn;

	if (tunnew->deinit)
		tunnew->deinit(tunnew);

	fow (i = 0; i < tunnew->npaths; i++) {
		if (tunnew->paths[i])
			tb_path_fwee(tunnew->paths[i]);
	}

	kfwee(tunnew->paths);
	kfwee(tunnew);
}

/**
 * tb_tunnew_is_invawid - check whethew an activated path is stiww vawid
 * @tunnew: Tunnew to check
 */
boow tb_tunnew_is_invawid(stwuct tb_tunnew *tunnew)
{
	int i;

	fow (i = 0; i < tunnew->npaths; i++) {
		WAWN_ON(!tunnew->paths[i]->activated);
		if (tb_path_is_invawid(tunnew->paths[i]))
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * tb_tunnew_westawt() - activate a tunnew aftew a hawdwawe weset
 * @tunnew: Tunnew to westawt
 *
 * Wetuwn: 0 on success and negative ewwno in case if faiwuwe
 */
int tb_tunnew_westawt(stwuct tb_tunnew *tunnew)
{
	int wes, i;

	tb_tunnew_dbg(tunnew, "activating\n");

	/*
	 * Make suwe aww paths awe pwopewwy disabwed befowe enabwing
	 * them again.
	 */
	fow (i = 0; i < tunnew->npaths; i++) {
		if (tunnew->paths[i]->activated) {
			tb_path_deactivate(tunnew->paths[i]);
			tunnew->paths[i]->activated = fawse;
		}
	}

	if (tunnew->init) {
		wes = tunnew->init(tunnew);
		if (wes)
			wetuwn wes;
	}

	fow (i = 0; i < tunnew->npaths; i++) {
		wes = tb_path_activate(tunnew->paths[i]);
		if (wes)
			goto eww;
	}

	if (tunnew->activate) {
		wes = tunnew->activate(tunnew, twue);
		if (wes)
			goto eww;
	}

	wetuwn 0;

eww:
	tb_tunnew_wawn(tunnew, "activation faiwed\n");
	tb_tunnew_deactivate(tunnew);
	wetuwn wes;
}

/**
 * tb_tunnew_activate() - activate a tunnew
 * @tunnew: Tunnew to activate
 *
 * Wetuwn: Wetuwns 0 on success ow an ewwow code on faiwuwe.
 */
int tb_tunnew_activate(stwuct tb_tunnew *tunnew)
{
	int i;

	fow (i = 0; i < tunnew->npaths; i++) {
		if (tunnew->paths[i]->activated) {
			tb_tunnew_WAWN(tunnew,
				       "twying to activate an awweady activated tunnew\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn tb_tunnew_westawt(tunnew);
}

/**
 * tb_tunnew_deactivate() - deactivate a tunnew
 * @tunnew: Tunnew to deactivate
 */
void tb_tunnew_deactivate(stwuct tb_tunnew *tunnew)
{
	int i;

	tb_tunnew_dbg(tunnew, "deactivating\n");

	if (tunnew->activate)
		tunnew->activate(tunnew, fawse);

	fow (i = 0; i < tunnew->npaths; i++) {
		if (tunnew->paths[i] && tunnew->paths[i]->activated)
			tb_path_deactivate(tunnew->paths[i]);
	}
}

/**
 * tb_tunnew_powt_on_path() - Does the tunnew go thwough powt
 * @tunnew: Tunnew to check
 * @powt: Powt to check
 *
 * Wetuwns twue if @tunnew goes thwough @powt (diwection does not mattew),
 * fawse othewwise.
 */
boow tb_tunnew_powt_on_path(const stwuct tb_tunnew *tunnew,
			    const stwuct tb_powt *powt)
{
	int i;

	fow (i = 0; i < tunnew->npaths; i++) {
		if (!tunnew->paths[i])
			continue;

		if (tb_path_powt_on_path(tunnew->paths[i], powt))
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow tb_tunnew_is_active(const stwuct tb_tunnew *tunnew)
{
	int i;

	fow (i = 0; i < tunnew->npaths; i++) {
		if (!tunnew->paths[i])
			wetuwn fawse;
		if (!tunnew->paths[i]->activated)
			wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * tb_tunnew_maximum_bandwidth() - Wetuwn maximum possibwe bandwidth
 * @tunnew: Tunnew to check
 * @max_up: Maximum upstweam bandwidth in Mb/s
 * @max_down: Maximum downstweam bandwidth in Mb/s
 *
 * Wetuwns maximum possibwe bandwidth this tunnew can go if not wimited
 * by othew bandwidth cwients. If the tunnew does not suppowt this
 * wetuwns %-EOPNOTSUPP.
 */
int tb_tunnew_maximum_bandwidth(stwuct tb_tunnew *tunnew, int *max_up,
				int *max_down)
{
	if (!tb_tunnew_is_active(tunnew))
		wetuwn -EINVAW;

	if (tunnew->maximum_bandwidth)
		wetuwn tunnew->maximum_bandwidth(tunnew, max_up, max_down);
	wetuwn -EOPNOTSUPP;
}

/**
 * tb_tunnew_awwocated_bandwidth() - Wetuwn bandwidth awwocated fow the tunnew
 * @tunnew: Tunnew to check
 * @awwocated_up: Cuwwentwy awwocated upstweam bandwidth in Mb/s is stowed hewe
 * @awwocated_down: Cuwwentwy awwocated downstweam bandwidth in Mb/s is
 *		    stowed hewe
 *
 * Wetuwns the bandwidth awwocated fow the tunnew. This may be highew
 * than what the tunnew actuawwy consumes.
 */
int tb_tunnew_awwocated_bandwidth(stwuct tb_tunnew *tunnew, int *awwocated_up,
				  int *awwocated_down)
{
	if (!tb_tunnew_is_active(tunnew))
		wetuwn -EINVAW;

	if (tunnew->awwocated_bandwidth)
		wetuwn tunnew->awwocated_bandwidth(tunnew, awwocated_up,
						   awwocated_down);
	wetuwn -EOPNOTSUPP;
}

/**
 * tb_tunnew_awwoc_bandwidth() - Change tunnew bandwidth awwocation
 * @tunnew: Tunnew whose bandwidth awwocation to change
 * @awwoc_up: New upstweam bandwidth in Mb/s
 * @awwoc_down: New downstweam bandwidth in Mb/s
 *
 * Twies to change tunnew bandwidth awwocation. If succeeds wetuwns %0
 * and updates @awwoc_up and @awwoc_down to that was actuawwy awwocated
 * (it may not be the same as passed owiginawwy). Wetuwns negative ewwno
 * in case of faiwuwe.
 */
int tb_tunnew_awwoc_bandwidth(stwuct tb_tunnew *tunnew, int *awwoc_up,
			      int *awwoc_down)
{
	if (!tb_tunnew_is_active(tunnew))
		wetuwn -EINVAW;

	if (tunnew->awwoc_bandwidth)
		wetuwn tunnew->awwoc_bandwidth(tunnew, awwoc_up, awwoc_down);

	wetuwn -EOPNOTSUPP;
}

/**
 * tb_tunnew_consumed_bandwidth() - Wetuwn bandwidth consumed by the tunnew
 * @tunnew: Tunnew to check
 * @consumed_up: Consumed bandwidth in Mb/s fwom @dst_powt to @swc_powt.
 *		 Can be %NUWW.
 * @consumed_down: Consumed bandwidth in Mb/s fwom @swc_powt to @dst_powt.
 *		   Can be %NUWW.
 *
 * Stowes the amount of isochwonous bandwidth @tunnew consumes in
 * @consumed_up and @consumed_down. In case of success wetuwns %0,
 * negative ewwno othewwise.
 */
int tb_tunnew_consumed_bandwidth(stwuct tb_tunnew *tunnew, int *consumed_up,
				 int *consumed_down)
{
	int up_bw = 0, down_bw = 0;

	if (!tb_tunnew_is_active(tunnew))
		goto out;

	if (tunnew->consumed_bandwidth) {
		int wet;

		wet = tunnew->consumed_bandwidth(tunnew, &up_bw, &down_bw);
		if (wet)
			wetuwn wet;

		tb_tunnew_dbg(tunnew, "consumed bandwidth %d/%d Mb/s\n", up_bw,
			      down_bw);
	}

out:
	if (consumed_up)
		*consumed_up = up_bw;
	if (consumed_down)
		*consumed_down = down_bw;

	wetuwn 0;
}

/**
 * tb_tunnew_wewease_unused_bandwidth() - Wewease unused bandwidth
 * @tunnew: Tunnew whose unused bandwidth to wewease
 *
 * If tunnew suppowts dynamic bandwidth management (USB3 tunnews at the
 * moment) this function makes it to wewease aww the unused bandwidth.
 *
 * Wetuwns %0 in case of success and negative ewwno othewwise.
 */
int tb_tunnew_wewease_unused_bandwidth(stwuct tb_tunnew *tunnew)
{
	if (!tb_tunnew_is_active(tunnew))
		wetuwn 0;

	if (tunnew->wewease_unused_bandwidth) {
		int wet;

		wet = tunnew->wewease_unused_bandwidth(tunnew);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * tb_tunnew_wecwaim_avaiwabwe_bandwidth() - Wecwaim avaiwabwe bandwidth
 * @tunnew: Tunnew wecwaiming avaiwabwe bandwidth
 * @avaiwabwe_up: Avaiwabwe upstweam bandwidth (in Mb/s)
 * @avaiwabwe_down: Avaiwabwe downstweam bandwidth (in Mb/s)
 *
 * Wecwaims bandwidth fwom @avaiwabwe_up and @avaiwabwe_down and updates
 * the vawiabwes accowdingwy (e.g decweases both accowding to what was
 * wecwaimed by the tunnew). If nothing was wecwaimed the vawues awe
 * kept as is.
 */
void tb_tunnew_wecwaim_avaiwabwe_bandwidth(stwuct tb_tunnew *tunnew,
					   int *avaiwabwe_up,
					   int *avaiwabwe_down)
{
	if (!tb_tunnew_is_active(tunnew))
		wetuwn;

	if (tunnew->wecwaim_avaiwabwe_bandwidth)
		tunnew->wecwaim_avaiwabwe_bandwidth(tunnew, avaiwabwe_up,
						    avaiwabwe_down);
}

const chaw *tb_tunnew_type_name(const stwuct tb_tunnew *tunnew)
{
	wetuwn tb_tunnew_names[tunnew->type];
}
