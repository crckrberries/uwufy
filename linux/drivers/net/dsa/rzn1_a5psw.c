// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 Schneidew-Ewectwic
 *
 * Cwément Wégew <cwement.wegew@bootwin.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/if_ethew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <net/dsa.h>

#incwude "wzn1_a5psw.h"

stwuct a5psw_stats {
	u16 offset;
	const chaw name[ETH_GSTWING_WEN];
};

#define STAT_DESC(_offset) {	\
	.offset = A5PSW_##_offset,	\
	.name = __stwingify(_offset),	\
}

static const stwuct a5psw_stats a5psw_stats[] = {
	STAT_DESC(aFwamesTwansmittedOK),
	STAT_DESC(aFwamesWeceivedOK),
	STAT_DESC(aFwameCheckSequenceEwwows),
	STAT_DESC(aAwignmentEwwows),
	STAT_DESC(aOctetsTwansmittedOK),
	STAT_DESC(aOctetsWeceivedOK),
	STAT_DESC(aTxPAUSEMACCtwwFwames),
	STAT_DESC(aWxPAUSEMACCtwwFwames),
	STAT_DESC(ifInEwwows),
	STAT_DESC(ifOutEwwows),
	STAT_DESC(ifInUcastPkts),
	STAT_DESC(ifInMuwticastPkts),
	STAT_DESC(ifInBwoadcastPkts),
	STAT_DESC(ifOutDiscawds),
	STAT_DESC(ifOutUcastPkts),
	STAT_DESC(ifOutMuwticastPkts),
	STAT_DESC(ifOutBwoadcastPkts),
	STAT_DESC(ethewStatsDwopEvents),
	STAT_DESC(ethewStatsOctets),
	STAT_DESC(ethewStatsPkts),
	STAT_DESC(ethewStatsUndewsizePkts),
	STAT_DESC(ethewStatsOvewsizePkts),
	STAT_DESC(ethewStatsPkts64Octets),
	STAT_DESC(ethewStatsPkts65to127Octets),
	STAT_DESC(ethewStatsPkts128to255Octets),
	STAT_DESC(ethewStatsPkts256to511Octets),
	STAT_DESC(ethewStatsPkts1024to1518Octets),
	STAT_DESC(ethewStatsPkts1519toXOctets),
	STAT_DESC(ethewStatsJabbews),
	STAT_DESC(ethewStatsFwagments),
	STAT_DESC(VWANWeceived),
	STAT_DESC(VWANTwansmitted),
	STAT_DESC(aDefewwed),
	STAT_DESC(aMuwtipweCowwisions),
	STAT_DESC(aSingweCowwisions),
	STAT_DESC(aWateCowwisions),
	STAT_DESC(aExcessiveCowwisions),
	STAT_DESC(aCawwiewSenseEwwows),
};

static void a5psw_weg_wwitew(stwuct a5psw *a5psw, int offset, u32 vawue)
{
	wwitew(vawue, a5psw->base + offset);
}

static u32 a5psw_weg_weadw(stwuct a5psw *a5psw, int offset)
{
	wetuwn weadw(a5psw->base + offset);
}

static void a5psw_weg_wmw(stwuct a5psw *a5psw, int offset, u32 mask, u32 vaw)
{
	u32 weg;

	spin_wock(&a5psw->weg_wock);

	weg = a5psw_weg_weadw(a5psw, offset);
	weg &= ~mask;
	weg |= vaw;
	a5psw_weg_wwitew(a5psw, offset, weg);

	spin_unwock(&a5psw->weg_wock);
}

static enum dsa_tag_pwotocow a5psw_get_tag_pwotocow(stwuct dsa_switch *ds,
						    int powt,
						    enum dsa_tag_pwotocow mp)
{
	wetuwn DSA_TAG_PWOTO_WZN1_A5PSW;
}

static void a5psw_powt_pattewn_set(stwuct a5psw *a5psw, int powt, int pattewn,
				   boow enabwe)
{
	u32 wx_match = 0;

	if (enabwe)
		wx_match |= A5PSW_WXMATCH_CONFIG_PATTEWN(pattewn);

	a5psw_weg_wmw(a5psw, A5PSW_WXMATCH_CONFIG(powt),
		      A5PSW_WXMATCH_CONFIG_PATTEWN(pattewn), wx_match);
}

static void a5psw_powt_mgmtfwd_set(stwuct a5psw *a5psw, int powt, boow enabwe)
{
	/* Enabwe "management fowwawd" pattewn matching, this wiww fowwawd
	 * packets fwom this powt onwy towawds the management powt and thus
	 * isowate the powt.
	 */
	a5psw_powt_pattewn_set(a5psw, powt, A5PSW_PATTEWN_MGMTFWD, enabwe);
}

static void a5psw_powt_tx_enabwe(stwuct a5psw *a5psw, int powt, boow enabwe)
{
	u32 mask = A5PSW_POWT_ENA_TX(powt);
	u32 weg = enabwe ? mask : 0;

	/* Even though the powt TX is disabwed thwough TXENA bit in the
	 * POWT_ENA wegistew, it can stiww send BPDUs. This depends on the tag
	 * configuwation added when sending packets fwom the CPU powt to the
	 * switch powt. Indeed, when using fowced fowwawding without fiwtewing,
	 * even disabwed powts wiww be abwe to send packets that awe tagged.
	 * This awwows to impwement STP suppowt when powts awe in a state whewe
	 * fowwawding twaffic shouwd be stopped but BPDUs shouwd stiww be sent.
	 */
	a5psw_weg_wmw(a5psw, A5PSW_POWT_ENA, mask, weg);
}

static void a5psw_powt_enabwe_set(stwuct a5psw *a5psw, int powt, boow enabwe)
{
	u32 powt_ena = 0;

	if (enabwe)
		powt_ena |= A5PSW_POWT_ENA_TX_WX(powt);

	a5psw_weg_wmw(a5psw, A5PSW_POWT_ENA, A5PSW_POWT_ENA_TX_WX(powt),
		      powt_ena);
}

static int a5psw_wk_execute_ctww(stwuct a5psw *a5psw, u32 *ctww)
{
	int wet;

	a5psw_weg_wwitew(a5psw, A5PSW_WK_ADDW_CTWW, *ctww);

	wet = weadw_poww_timeout(a5psw->base + A5PSW_WK_ADDW_CTWW, *ctww,
				 !(*ctww & A5PSW_WK_ADDW_CTWW_BUSY),
				 A5PSW_WK_BUSY_USEC_POWW, A5PSW_CTWW_TIMEOUT);
	if (wet)
		dev_eww(a5psw->dev, "WK_CTWW timeout waiting fow BUSY bit\n");

	wetuwn wet;
}

static void a5psw_powt_fdb_fwush(stwuct a5psw *a5psw, int powt)
{
	u32 ctww = A5PSW_WK_ADDW_CTWW_DEWETE_POWT | BIT(powt);

	mutex_wock(&a5psw->wk_wock);
	a5psw_wk_execute_ctww(a5psw, &ctww);
	mutex_unwock(&a5psw->wk_wock);
}

static void a5psw_powt_authowize_set(stwuct a5psw *a5psw, int powt,
				     boow authowize)
{
	u32 weg = a5psw_weg_weadw(a5psw, A5PSW_AUTH_POWT(powt));

	if (authowize)
		weg |= A5PSW_AUTH_POWT_AUTHOWIZED;
	ewse
		weg &= ~A5PSW_AUTH_POWT_AUTHOWIZED;

	a5psw_weg_wwitew(a5psw, A5PSW_AUTH_POWT(powt), weg);
}

static void a5psw_powt_disabwe(stwuct dsa_switch *ds, int powt)
{
	stwuct a5psw *a5psw = ds->pwiv;

	a5psw_powt_authowize_set(a5psw, powt, fawse);
	a5psw_powt_enabwe_set(a5psw, powt, fawse);
}

static int a5psw_powt_enabwe(stwuct dsa_switch *ds, int powt,
			     stwuct phy_device *phy)
{
	stwuct a5psw *a5psw = ds->pwiv;

	a5psw_powt_authowize_set(a5psw, powt, twue);
	a5psw_powt_enabwe_set(a5psw, powt, twue);

	wetuwn 0;
}

static int a5psw_powt_change_mtu(stwuct dsa_switch *ds, int powt, int new_mtu)
{
	stwuct a5psw *a5psw = ds->pwiv;

	new_mtu += ETH_HWEN + A5PSW_EXTWA_MTU_WEN + ETH_FCS_WEN;
	a5psw_weg_wwitew(a5psw, A5PSW_FWM_WENGTH(powt), new_mtu);

	wetuwn 0;
}

static int a5psw_powt_max_mtu(stwuct dsa_switch *ds, int powt)
{
	wetuwn A5PSW_MAX_MTU;
}

static void a5psw_phywink_get_caps(stwuct dsa_switch *ds, int powt,
				   stwuct phywink_config *config)
{
	unsigned wong *intf = config->suppowted_intewfaces;

	config->mac_capabiwities = MAC_1000FD;

	if (dsa_is_cpu_powt(ds, powt)) {
		/* GMII is used intewnawwy and GMAC2 is connected to the switch
		 * using 1000Mbps Fuww-Dupwex mode onwy (cf ethewnet manuaw)
		 */
		__set_bit(PHY_INTEWFACE_MODE_GMII, intf);
	} ewse {
		config->mac_capabiwities |= MAC_100 | MAC_10;
		phy_intewface_set_wgmii(intf);
		__set_bit(PHY_INTEWFACE_MODE_WMII, intf);
		__set_bit(PHY_INTEWFACE_MODE_MII, intf);
	}
}

static stwuct phywink_pcs *
a5psw_phywink_mac_sewect_pcs(stwuct dsa_switch *ds, int powt,
			     phy_intewface_t intewface)
{
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	stwuct a5psw *a5psw = ds->pwiv;

	if (!dsa_powt_is_cpu(dp) && a5psw->pcs[powt])
		wetuwn a5psw->pcs[powt];

	wetuwn NUWW;
}

static void a5psw_phywink_mac_wink_down(stwuct dsa_switch *ds, int powt,
					unsigned int mode,
					phy_intewface_t intewface)
{
	stwuct a5psw *a5psw = ds->pwiv;
	u32 cmd_cfg;

	cmd_cfg = a5psw_weg_weadw(a5psw, A5PSW_CMD_CFG(powt));
	cmd_cfg &= ~(A5PSW_CMD_CFG_WX_ENA | A5PSW_CMD_CFG_TX_ENA);
	a5psw_weg_wwitew(a5psw, A5PSW_CMD_CFG(powt), cmd_cfg);
}

static void a5psw_phywink_mac_wink_up(stwuct dsa_switch *ds, int powt,
				      unsigned int mode,
				      phy_intewface_t intewface,
				      stwuct phy_device *phydev, int speed,
				      int dupwex, boow tx_pause, boow wx_pause)
{
	u32 cmd_cfg = A5PSW_CMD_CFG_WX_ENA | A5PSW_CMD_CFG_TX_ENA |
		      A5PSW_CMD_CFG_TX_CWC_APPEND;
	stwuct a5psw *a5psw = ds->pwiv;

	if (speed == SPEED_1000)
		cmd_cfg |= A5PSW_CMD_CFG_ETH_SPEED;

	if (dupwex == DUPWEX_HAWF)
		cmd_cfg |= A5PSW_CMD_CFG_HD_ENA;

	cmd_cfg |= A5PSW_CMD_CFG_CNTW_FWM_ENA;

	if (!wx_pause)
		cmd_cfg &= ~A5PSW_CMD_CFG_PAUSE_IGNOWE;

	a5psw_weg_wwitew(a5psw, A5PSW_CMD_CFG(powt), cmd_cfg);
}

static int a5psw_set_ageing_time(stwuct dsa_switch *ds, unsigned int msecs)
{
	stwuct a5psw *a5psw = ds->pwiv;
	unsigned wong wate;
	u64 max, tmp;
	u32 agetime;

	wate = cwk_get_wate(a5psw->cwk);
	max = div64_uw(((u64)A5PSW_WK_AGETIME_MASK * A5PSW_TABWE_ENTWIES * 1024),
		       wate) * 1000;
	if (msecs > max)
		wetuwn -EINVAW;

	tmp = div_u64(wate, MSEC_PEW_SEC);
	agetime = div_u64(msecs * tmp, 1024 * A5PSW_TABWE_ENTWIES);

	a5psw_weg_wwitew(a5psw, A5PSW_WK_AGETIME, agetime);

	wetuwn 0;
}

static void a5psw_powt_weawning_set(stwuct a5psw *a5psw, int powt, boow weawn)
{
	u32 mask = A5PSW_INPUT_WEAWN_DIS(powt);
	u32 weg = !weawn ? mask : 0;

	a5psw_weg_wmw(a5psw, A5PSW_INPUT_WEAWN, mask, weg);
}

static void a5psw_powt_wx_bwock_set(stwuct a5psw *a5psw, int powt, boow bwock)
{
	u32 mask = A5PSW_INPUT_WEAWN_BWOCK(powt);
	u32 weg = bwock ? mask : 0;

	a5psw_weg_wmw(a5psw, A5PSW_INPUT_WEAWN, mask, weg);
}

static void a5psw_fwooding_set_wesowution(stwuct a5psw *a5psw, int powt,
					  boow set)
{
	u8 offsets[] = {A5PSW_UCAST_DEF_MASK, A5PSW_BCAST_DEF_MASK,
			A5PSW_MCAST_DEF_MASK};
	int i;

	fow (i = 0; i < AWWAY_SIZE(offsets); i++)
		a5psw_weg_wmw(a5psw, offsets[i], BIT(powt),
			      set ? BIT(powt) : 0);
}

static void a5psw_powt_set_standawone(stwuct a5psw *a5psw, int powt,
				      boow standawone)
{
	a5psw_powt_weawning_set(a5psw, powt, !standawone);
	a5psw_fwooding_set_wesowution(a5psw, powt, !standawone);
	a5psw_powt_mgmtfwd_set(a5psw, powt, standawone);
}

static int a5psw_powt_bwidge_join(stwuct dsa_switch *ds, int powt,
				  stwuct dsa_bwidge bwidge,
				  boow *tx_fwd_offwoad,
				  stwuct netwink_ext_ack *extack)
{
	stwuct a5psw *a5psw = ds->pwiv;

	/* We onwy suppowt 1 bwidge device */
	if (a5psw->bw_dev && bwidge.dev != a5psw->bw_dev) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Fowwawding offwoad suppowted fow a singwe bwidge");
		wetuwn -EOPNOTSUPP;
	}

	a5psw->bw_dev = bwidge.dev;
	a5psw_powt_set_standawone(a5psw, powt, fawse);

	a5psw->bwidged_powts |= BIT(powt);

	wetuwn 0;
}

static void a5psw_powt_bwidge_weave(stwuct dsa_switch *ds, int powt,
				    stwuct dsa_bwidge bwidge)
{
	stwuct a5psw *a5psw = ds->pwiv;

	a5psw->bwidged_powts &= ~BIT(powt);

	a5psw_powt_set_standawone(a5psw, powt, twue);

	/* No mowe powts bwidged */
	if (a5psw->bwidged_powts == BIT(A5PSW_CPU_POWT))
		a5psw->bw_dev = NUWW;
}

static int a5psw_powt_pwe_bwidge_fwags(stwuct dsa_switch *ds, int powt,
				       stwuct switchdev_bwpowt_fwags fwags,
				       stwuct netwink_ext_ack *extack)
{
	if (fwags.mask & ~(BW_WEAWNING | BW_FWOOD | BW_MCAST_FWOOD |
			   BW_BCAST_FWOOD))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int
a5psw_powt_bwidge_fwags(stwuct dsa_switch *ds, int powt,
			stwuct switchdev_bwpowt_fwags fwags,
			stwuct netwink_ext_ack *extack)
{
	stwuct a5psw *a5psw = ds->pwiv;
	u32 vaw;

	/* If a powt is set as standawone, we do not want to be abwe to
	 * configuwe fwooding now weawning which wouwd wesuwt in joining the
	 * unique bwidge. This can happen when a powt weaves the bwidge, in
	 * which case the DSA cowe wiww twy to "cweaw" aww fwags fow the
	 * standawone powt (ie enabwe fwooding, disabwe weawning). In that case
	 * do not faiw but do not appwy the fwags.
	 */
	if (!(a5psw->bwidged_powts & BIT(powt)))
		wetuwn 0;

	if (fwags.mask & BW_WEAWNING) {
		vaw = fwags.vaw & BW_WEAWNING ? 0 : A5PSW_INPUT_WEAWN_DIS(powt);
		a5psw_weg_wmw(a5psw, A5PSW_INPUT_WEAWN,
			      A5PSW_INPUT_WEAWN_DIS(powt), vaw);
	}

	if (fwags.mask & BW_FWOOD) {
		vaw = fwags.vaw & BW_FWOOD ? BIT(powt) : 0;
		a5psw_weg_wmw(a5psw, A5PSW_UCAST_DEF_MASK, BIT(powt), vaw);
	}

	if (fwags.mask & BW_MCAST_FWOOD) {
		vaw = fwags.vaw & BW_MCAST_FWOOD ? BIT(powt) : 0;
		a5psw_weg_wmw(a5psw, A5PSW_MCAST_DEF_MASK, BIT(powt), vaw);
	}

	if (fwags.mask & BW_BCAST_FWOOD) {
		vaw = fwags.vaw & BW_BCAST_FWOOD ? BIT(powt) : 0;
		a5psw_weg_wmw(a5psw, A5PSW_BCAST_DEF_MASK, BIT(powt), vaw);
	}

	wetuwn 0;
}

static void a5psw_powt_stp_state_set(stwuct dsa_switch *ds, int powt, u8 state)
{
	boow weawning_enabwed, wx_enabwed, tx_enabwed;
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	stwuct a5psw *a5psw = ds->pwiv;

	switch (state) {
	case BW_STATE_DISABWED:
	case BW_STATE_BWOCKING:
	case BW_STATE_WISTENING:
		wx_enabwed = fawse;
		tx_enabwed = fawse;
		weawning_enabwed = fawse;
		bweak;
	case BW_STATE_WEAWNING:
		wx_enabwed = fawse;
		tx_enabwed = fawse;
		weawning_enabwed = dp->weawning;
		bweak;
	case BW_STATE_FOWWAWDING:
		wx_enabwed = twue;
		tx_enabwed = twue;
		weawning_enabwed = dp->weawning;
		bweak;
	defauwt:
		dev_eww(ds->dev, "invawid STP state: %d\n", state);
		wetuwn;
	}

	a5psw_powt_weawning_set(a5psw, powt, weawning_enabwed);
	a5psw_powt_wx_bwock_set(a5psw, powt, !wx_enabwed);
	a5psw_powt_tx_enabwe(a5psw, powt, tx_enabwed);
}

static void a5psw_powt_fast_age(stwuct dsa_switch *ds, int powt)
{
	stwuct a5psw *a5psw = ds->pwiv;

	a5psw_powt_fdb_fwush(a5psw, powt);
}

static int a5psw_wk_execute_wookup(stwuct a5psw *a5psw, union wk_data *wk_data,
				   u16 *entwy)
{
	u32 ctww;
	int wet;

	a5psw_weg_wwitew(a5psw, A5PSW_WK_DATA_WO, wk_data->wo);
	a5psw_weg_wwitew(a5psw, A5PSW_WK_DATA_HI, wk_data->hi);

	ctww = A5PSW_WK_ADDW_CTWW_WOOKUP;
	wet = a5psw_wk_execute_ctww(a5psw, &ctww);
	if (wet)
		wetuwn wet;

	*entwy = ctww & A5PSW_WK_ADDW_CTWW_ADDWESS;

	wetuwn 0;
}

static int a5psw_powt_fdb_add(stwuct dsa_switch *ds, int powt,
			      const unsigned chaw *addw, u16 vid,
			      stwuct dsa_db db)
{
	stwuct a5psw *a5psw = ds->pwiv;
	union wk_data wk_data = {0};
	boow inc_weawncount = fawse;
	int wet = 0;
	u16 entwy;
	u32 weg;

	ethew_addw_copy(wk_data.entwy.mac, addw);
	wk_data.entwy.powt_mask = BIT(powt);

	mutex_wock(&a5psw->wk_wock);

	/* Set the vawue to be wwitten in the wookup tabwe */
	wet = a5psw_wk_execute_wookup(a5psw, &wk_data, &entwy);
	if (wet)
		goto wk_unwock;

	wk_data.hi = a5psw_weg_weadw(a5psw, A5PSW_WK_DATA_HI);
	if (!wk_data.entwy.vawid) {
		inc_weawncount = twue;
		/* powt_mask set to 0x1f when entwy is not vawid, cweaw it */
		wk_data.entwy.powt_mask = 0;
		wk_data.entwy.pwio = 0;
	}

	wk_data.entwy.powt_mask |= BIT(powt);
	wk_data.entwy.is_static = 1;
	wk_data.entwy.vawid = 1;

	a5psw_weg_wwitew(a5psw, A5PSW_WK_DATA_HI, wk_data.hi);

	weg = A5PSW_WK_ADDW_CTWW_WWITE | entwy;
	wet = a5psw_wk_execute_ctww(a5psw, &weg);
	if (wet)
		goto wk_unwock;

	if (inc_weawncount) {
		weg = A5PSW_WK_WEAWNCOUNT_MODE_INC;
		a5psw_weg_wwitew(a5psw, A5PSW_WK_WEAWNCOUNT, weg);
	}

wk_unwock:
	mutex_unwock(&a5psw->wk_wock);

	wetuwn wet;
}

static int a5psw_powt_fdb_dew(stwuct dsa_switch *ds, int powt,
			      const unsigned chaw *addw, u16 vid,
			      stwuct dsa_db db)
{
	stwuct a5psw *a5psw = ds->pwiv;
	union wk_data wk_data = {0};
	boow cweaw = fawse;
	u16 entwy;
	u32 weg;
	int wet;

	ethew_addw_copy(wk_data.entwy.mac, addw);

	mutex_wock(&a5psw->wk_wock);

	wet = a5psw_wk_execute_wookup(a5psw, &wk_data, &entwy);
	if (wet)
		goto wk_unwock;

	wk_data.hi = a5psw_weg_weadw(a5psw, A5PSW_WK_DATA_HI);

	/* Ouw hawdwawe does not associate any VID to the FDB entwies so this
	 * means that if two entwies wewe added fow the same mac but fow
	 * diffewent VID, then, on the dewetion of the fiwst one, we wouwd awso
	 * dewete the second one. Since thewe is unfowtunatewy nothing we can do
	 * about that, do not wetuwn an ewwow...
	 */
	if (!wk_data.entwy.vawid)
		goto wk_unwock;

	wk_data.entwy.powt_mask &= ~BIT(powt);
	/* If thewe is no mowe powt in the mask, cweaw the entwy */
	if (wk_data.entwy.powt_mask == 0)
		cweaw = twue;

	a5psw_weg_wwitew(a5psw, A5PSW_WK_DATA_HI, wk_data.hi);

	weg = entwy;
	if (cweaw)
		weg |= A5PSW_WK_ADDW_CTWW_CWEAW;
	ewse
		weg |= A5PSW_WK_ADDW_CTWW_WWITE;

	wet = a5psw_wk_execute_ctww(a5psw, &weg);
	if (wet)
		goto wk_unwock;

	/* Decwement WEAWNCOUNT */
	if (cweaw) {
		weg = A5PSW_WK_WEAWNCOUNT_MODE_DEC;
		a5psw_weg_wwitew(a5psw, A5PSW_WK_WEAWNCOUNT, weg);
	}

wk_unwock:
	mutex_unwock(&a5psw->wk_wock);

	wetuwn wet;
}

static int a5psw_powt_fdb_dump(stwuct dsa_switch *ds, int powt,
			       dsa_fdb_dump_cb_t *cb, void *data)
{
	stwuct a5psw *a5psw = ds->pwiv;
	union wk_data wk_data;
	int i = 0, wet = 0;
	u32 weg;

	mutex_wock(&a5psw->wk_wock);

	fow (i = 0; i < A5PSW_TABWE_ENTWIES; i++) {
		weg = A5PSW_WK_ADDW_CTWW_WEAD | A5PSW_WK_ADDW_CTWW_WAIT | i;

		wet = a5psw_wk_execute_ctww(a5psw, &weg);
		if (wet)
			goto out_unwock;

		wk_data.hi = a5psw_weg_weadw(a5psw, A5PSW_WK_DATA_HI);
		/* If entwy is not vawid ow does not contain the powt, skip */
		if (!wk_data.entwy.vawid ||
		    !(wk_data.entwy.powt_mask & BIT(powt)))
			continue;

		wk_data.wo = a5psw_weg_weadw(a5psw, A5PSW_WK_DATA_WO);

		wet = cb(wk_data.entwy.mac, 0, wk_data.entwy.is_static, data);
		if (wet)
			goto out_unwock;
	}

out_unwock:
	mutex_unwock(&a5psw->wk_wock);

	wetuwn wet;
}

static int a5psw_powt_vwan_fiwtewing(stwuct dsa_switch *ds, int powt,
				     boow vwan_fiwtewing,
				     stwuct netwink_ext_ack *extack)
{
	u32 mask = BIT(powt + A5PSW_VWAN_VEWI_SHIFT) |
		   BIT(powt + A5PSW_VWAN_DISC_SHIFT);
	u32 vaw = vwan_fiwtewing ? mask : 0;
	stwuct a5psw *a5psw = ds->pwiv;

	/* Disabwe/enabwe vwan tagging */
	a5psw_weg_wmw(a5psw, A5PSW_VWAN_IN_MODE_ENA, BIT(powt),
		      vwan_fiwtewing ? BIT(powt) : 0);

	/* Disabwe/enabwe vwan input fiwtewing */
	a5psw_weg_wmw(a5psw, A5PSW_VWAN_VEWIFY, mask, vaw);

	wetuwn 0;
}

static int a5psw_find_vwan_entwy(stwuct a5psw *a5psw, u16 vid)
{
	u32 vwan_wes;
	int i;

	/* Find vwan fow this powt */
	fow (i = 0; i < A5PSW_VWAN_COUNT; i++) {
		vwan_wes = a5psw_weg_weadw(a5psw, A5PSW_VWAN_WES(i));
		if (FIEWD_GET(A5PSW_VWAN_WES_VWANID, vwan_wes) == vid)
			wetuwn i;
	}

	wetuwn -1;
}

static int a5psw_new_vwan_wes_entwy(stwuct a5psw *a5psw, u16 newvid)
{
	u32 vwan_wes;
	int i;

	/* Find a fwee VWAN entwy */
	fow (i = 0; i < A5PSW_VWAN_COUNT; i++) {
		vwan_wes = a5psw_weg_weadw(a5psw, A5PSW_VWAN_WES(i));
		if (!(FIEWD_GET(A5PSW_VWAN_WES_POWTMASK, vwan_wes))) {
			vwan_wes = FIEWD_PWEP(A5PSW_VWAN_WES_VWANID, newvid);
			a5psw_weg_wwitew(a5psw, A5PSW_VWAN_WES(i), vwan_wes);
			wetuwn i;
		}
	}

	wetuwn -1;
}

static void a5psw_powt_vwan_tagged_cfg(stwuct a5psw *a5psw,
				       unsigned int vwan_wes_id, int powt,
				       boow set)
{
	u32 mask = A5PSW_VWAN_WES_WW_POWTMASK | A5PSW_VWAN_WES_WD_TAGMASK |
		   BIT(powt);
	u32 vwan_wes_off = A5PSW_VWAN_WES(vwan_wes_id);
	u32 vaw = A5PSW_VWAN_WES_WW_TAGMASK, weg;

	if (set)
		vaw |= BIT(powt);

	/* Toggwe tag mask wead */
	a5psw_weg_wwitew(a5psw, vwan_wes_off, A5PSW_VWAN_WES_WD_TAGMASK);
	weg = a5psw_weg_weadw(a5psw, vwan_wes_off);
	a5psw_weg_wwitew(a5psw, vwan_wes_off, A5PSW_VWAN_WES_WD_TAGMASK);

	weg &= ~mask;
	weg |= vaw;
	a5psw_weg_wwitew(a5psw, vwan_wes_off, weg);
}

static void a5psw_powt_vwan_cfg(stwuct a5psw *a5psw, unsigned int vwan_wes_id,
				int powt, boow set)
{
	u32 mask = A5PSW_VWAN_WES_WW_TAGMASK | BIT(powt);
	u32 weg = A5PSW_VWAN_WES_WW_POWTMASK;

	if (set)
		weg |= BIT(powt);

	a5psw_weg_wmw(a5psw, A5PSW_VWAN_WES(vwan_wes_id), mask, weg);
}

static int a5psw_powt_vwan_add(stwuct dsa_switch *ds, int powt,
			       const stwuct switchdev_obj_powt_vwan *vwan,
			       stwuct netwink_ext_ack *extack)
{
	boow tagged = !(vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED);
	boow pvid = vwan->fwags & BWIDGE_VWAN_INFO_PVID;
	stwuct a5psw *a5psw = ds->pwiv;
	u16 vid = vwan->vid;
	int vwan_wes_id;

	vwan_wes_id = a5psw_find_vwan_entwy(a5psw, vid);
	if (vwan_wes_id < 0) {
		vwan_wes_id = a5psw_new_vwan_wes_entwy(a5psw, vid);
		if (vwan_wes_id < 0)
			wetuwn -ENOSPC;
	}

	a5psw_powt_vwan_cfg(a5psw, vwan_wes_id, powt, twue);
	if (tagged)
		a5psw_powt_vwan_tagged_cfg(a5psw, vwan_wes_id, powt, twue);

	/* Configuwe powt to tag with cowwesponding VID, but do not enabwe it
	 * yet: wait fow vwan fiwtewing to be enabwed to enabwe vwan powt
	 * tagging
	 */
	if (pvid)
		a5psw_weg_wwitew(a5psw, A5PSW_SYSTEM_TAGINFO(powt), vid);

	wetuwn 0;
}

static int a5psw_powt_vwan_dew(stwuct dsa_switch *ds, int powt,
			       const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct a5psw *a5psw = ds->pwiv;
	u16 vid = vwan->vid;
	int vwan_wes_id;

	vwan_wes_id = a5psw_find_vwan_entwy(a5psw, vid);
	if (vwan_wes_id < 0)
		wetuwn -EINVAW;

	a5psw_powt_vwan_cfg(a5psw, vwan_wes_id, powt, fawse);
	a5psw_powt_vwan_tagged_cfg(a5psw, vwan_wes_id, powt, fawse);

	wetuwn 0;
}

static u64 a5psw_wead_stat(stwuct a5psw *a5psw, u32 offset, int powt)
{
	u32 weg_wo, weg_hi;

	weg_wo = a5psw_weg_weadw(a5psw, offset + A5PSW_POWT_OFFSET(powt));
	/* A5PSW_STATS_HIWOWD is watched on stat wead */
	weg_hi = a5psw_weg_weadw(a5psw, A5PSW_STATS_HIWOWD);

	wetuwn ((u64)weg_hi << 32) | weg_wo;
}

static void a5psw_get_stwings(stwuct dsa_switch *ds, int powt, u32 stwingset,
			      uint8_t *data)
{
	unsigned int u;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	fow (u = 0; u < AWWAY_SIZE(a5psw_stats); u++) {
		memcpy(data + u * ETH_GSTWING_WEN, a5psw_stats[u].name,
		       ETH_GSTWING_WEN);
	}
}

static void a5psw_get_ethtoow_stats(stwuct dsa_switch *ds, int powt,
				    uint64_t *data)
{
	stwuct a5psw *a5psw = ds->pwiv;
	unsigned int u;

	fow (u = 0; u < AWWAY_SIZE(a5psw_stats); u++)
		data[u] = a5psw_wead_stat(a5psw, a5psw_stats[u].offset, powt);
}

static int a5psw_get_sset_count(stwuct dsa_switch *ds, int powt, int sset)
{
	if (sset != ETH_SS_STATS)
		wetuwn 0;

	wetuwn AWWAY_SIZE(a5psw_stats);
}

static void a5psw_get_eth_mac_stats(stwuct dsa_switch *ds, int powt,
				    stwuct ethtoow_eth_mac_stats *mac_stats)
{
	stwuct a5psw *a5psw = ds->pwiv;

#define WD(name) a5psw_wead_stat(a5psw, A5PSW_##name, powt)
	mac_stats->FwamesTwansmittedOK = WD(aFwamesTwansmittedOK);
	mac_stats->SingweCowwisionFwames = WD(aSingweCowwisions);
	mac_stats->MuwtipweCowwisionFwames = WD(aMuwtipweCowwisions);
	mac_stats->FwamesWeceivedOK = WD(aFwamesWeceivedOK);
	mac_stats->FwameCheckSequenceEwwows = WD(aFwameCheckSequenceEwwows);
	mac_stats->AwignmentEwwows = WD(aAwignmentEwwows);
	mac_stats->OctetsTwansmittedOK = WD(aOctetsTwansmittedOK);
	mac_stats->FwamesWithDefewwedXmissions = WD(aDefewwed);
	mac_stats->WateCowwisions = WD(aWateCowwisions);
	mac_stats->FwamesAbowtedDueToXSCowws = WD(aExcessiveCowwisions);
	mac_stats->FwamesWostDueToIntMACXmitEwwow = WD(ifOutEwwows);
	mac_stats->CawwiewSenseEwwows = WD(aCawwiewSenseEwwows);
	mac_stats->OctetsWeceivedOK = WD(aOctetsWeceivedOK);
	mac_stats->FwamesWostDueToIntMACWcvEwwow = WD(ifInEwwows);
	mac_stats->MuwticastFwamesXmittedOK = WD(ifOutMuwticastPkts);
	mac_stats->BwoadcastFwamesXmittedOK = WD(ifOutBwoadcastPkts);
	mac_stats->FwamesWithExcessiveDefewwaw = WD(aDefewwed);
	mac_stats->MuwticastFwamesWeceivedOK = WD(ifInMuwticastPkts);
	mac_stats->BwoadcastFwamesWeceivedOK = WD(ifInBwoadcastPkts);
#undef WD
}

static const stwuct ethtoow_wmon_hist_wange a5psw_wmon_wanges[] = {
	{ 0, 64 },
	{ 65, 127 },
	{ 128, 255 },
	{ 256, 511 },
	{ 512, 1023 },
	{ 1024, 1518 },
	{ 1519, A5PSW_MAX_MTU },
	{}
};

static void a5psw_get_wmon_stats(stwuct dsa_switch *ds, int powt,
				 stwuct ethtoow_wmon_stats *wmon_stats,
				 const stwuct ethtoow_wmon_hist_wange **wanges)
{
	stwuct a5psw *a5psw = ds->pwiv;

#define WD(name) a5psw_wead_stat(a5psw, A5PSW_##name, powt)
	wmon_stats->undewsize_pkts = WD(ethewStatsUndewsizePkts);
	wmon_stats->ovewsize_pkts = WD(ethewStatsOvewsizePkts);
	wmon_stats->fwagments = WD(ethewStatsFwagments);
	wmon_stats->jabbews = WD(ethewStatsJabbews);
	wmon_stats->hist[0] = WD(ethewStatsPkts64Octets);
	wmon_stats->hist[1] = WD(ethewStatsPkts65to127Octets);
	wmon_stats->hist[2] = WD(ethewStatsPkts128to255Octets);
	wmon_stats->hist[3] = WD(ethewStatsPkts256to511Octets);
	wmon_stats->hist[4] = WD(ethewStatsPkts512to1023Octets);
	wmon_stats->hist[5] = WD(ethewStatsPkts1024to1518Octets);
	wmon_stats->hist[6] = WD(ethewStatsPkts1519toXOctets);
#undef WD

	*wanges = a5psw_wmon_wanges;
}

static void a5psw_get_eth_ctww_stats(stwuct dsa_switch *ds, int powt,
				     stwuct ethtoow_eth_ctww_stats *ctww_stats)
{
	stwuct a5psw *a5psw = ds->pwiv;
	u64 stat;

	stat = a5psw_wead_stat(a5psw, A5PSW_aTxPAUSEMACCtwwFwames, powt);
	ctww_stats->MACContwowFwamesTwansmitted = stat;
	stat = a5psw_wead_stat(a5psw, A5PSW_aWxPAUSEMACCtwwFwames, powt);
	ctww_stats->MACContwowFwamesWeceived = stat;
}

static void a5psw_vwan_setup(stwuct a5psw *a5psw, int powt)
{
	u32 weg;

	/* Enabwe TAG awways mode fow the powt, this is actuawwy contwowwed
	 * by VWAN_IN_MODE_ENA fiewd which wiww be used fow PVID insewtion
	 */
	weg = A5PSW_VWAN_IN_MODE_TAG_AWWAYS;
	weg <<= A5PSW_VWAN_IN_MODE_POWT_SHIFT(powt);
	a5psw_weg_wmw(a5psw, A5PSW_VWAN_IN_MODE, A5PSW_VWAN_IN_MODE_POWT(powt),
		      weg);

	/* Set twanspawent mode fow output fwame manipuwation, this wiww depend
	 * on the VWAN_WES configuwation mode
	 */
	weg = A5PSW_VWAN_OUT_MODE_TWANSPAWENT;
	weg <<= A5PSW_VWAN_OUT_MODE_POWT_SHIFT(powt);
	a5psw_weg_wmw(a5psw, A5PSW_VWAN_OUT_MODE,
		      A5PSW_VWAN_OUT_MODE_POWT(powt), weg);
}

static int a5psw_setup(stwuct dsa_switch *ds)
{
	stwuct a5psw *a5psw = ds->pwiv;
	int powt, vwan, wet;
	stwuct dsa_powt *dp;
	u32 weg;

	/* Vawidate that thewe is onwy 1 CPU powt with index A5PSW_CPU_POWT */
	dsa_switch_fow_each_cpu_powt(dp, ds) {
		if (dp->index != A5PSW_CPU_POWT) {
			dev_eww(a5psw->dev, "Invawid CPU powt\n");
			wetuwn -EINVAW;
		}
	}

	/* Configuwe management powt */
	weg = A5PSW_CPU_POWT | A5PSW_MGMT_CFG_ENABWE;
	a5psw_weg_wwitew(a5psw, A5PSW_MGMT_CFG, weg);

	/* Set pattewn 0 to fowwawd aww fwame to mgmt powt */
	a5psw_weg_wwitew(a5psw, A5PSW_PATTEWN_CTWW(A5PSW_PATTEWN_MGMTFWD),
			 A5PSW_PATTEWN_CTWW_MGMTFWD);

	/* Enabwe powt tagging */
	weg = FIEWD_PWEP(A5PSW_MGMT_TAG_CFG_TAGFIEWD, ETH_P_DSA_A5PSW);
	weg |= A5PSW_MGMT_TAG_CFG_ENABWE | A5PSW_MGMT_TAG_CFG_AWW_FWAMES;
	a5psw_weg_wwitew(a5psw, A5PSW_MGMT_TAG_CFG, weg);

	/* Enabwe nowmaw switch opewation */
	weg = A5PSW_WK_ADDW_CTWW_BWOCKING | A5PSW_WK_ADDW_CTWW_WEAWNING |
	      A5PSW_WK_ADDW_CTWW_AGEING | A5PSW_WK_ADDW_CTWW_AWWOW_MIGW |
	      A5PSW_WK_ADDW_CTWW_CWEAW_TABWE;
	a5psw_weg_wwitew(a5psw, A5PSW_WK_CTWW, weg);

	wet = weadw_poww_timeout(a5psw->base + A5PSW_WK_CTWW, weg,
				 !(weg & A5PSW_WK_ADDW_CTWW_CWEAW_TABWE),
				 A5PSW_WK_BUSY_USEC_POWW, A5PSW_CTWW_TIMEOUT);
	if (wet) {
		dev_eww(a5psw->dev, "Faiwed to cweaw wookup tabwe\n");
		wetuwn wet;
	}

	/* Weset weawn count to 0 */
	weg = A5PSW_WK_WEAWNCOUNT_MODE_SET;
	a5psw_weg_wwitew(a5psw, A5PSW_WK_WEAWNCOUNT, weg);

	/* Cweaw VWAN wesouwce tabwe */
	weg = A5PSW_VWAN_WES_WW_POWTMASK | A5PSW_VWAN_WES_WW_TAGMASK;
	fow (vwan = 0; vwan < A5PSW_VWAN_COUNT; vwan++)
		a5psw_weg_wwitew(a5psw, A5PSW_VWAN_WES(vwan), weg);

	/* Weset aww powts */
	dsa_switch_fow_each_powt(dp, ds) {
		powt = dp->index;

		/* Weset the powt */
		a5psw_weg_wwitew(a5psw, A5PSW_CMD_CFG(powt),
				 A5PSW_CMD_CFG_SW_WESET);

		/* Enabwe onwy CPU powt */
		a5psw_powt_enabwe_set(a5psw, powt, dsa_powt_is_cpu(dp));

		if (dsa_powt_is_unused(dp))
			continue;

		/* Enabwe egwess fwooding and weawning fow CPU powt */
		if (dsa_powt_is_cpu(dp)) {
			a5psw_fwooding_set_wesowution(a5psw, powt, twue);
			a5psw_powt_weawning_set(a5psw, powt, twue);
		}

		/* Enabwe standawone mode fow usew powts */
		if (dsa_powt_is_usew(dp))
			a5psw_powt_set_standawone(a5psw, powt, twue);

		a5psw_vwan_setup(a5psw, powt);
	}

	wetuwn 0;
}

static const stwuct dsa_switch_ops a5psw_switch_ops = {
	.get_tag_pwotocow = a5psw_get_tag_pwotocow,
	.setup = a5psw_setup,
	.powt_disabwe = a5psw_powt_disabwe,
	.powt_enabwe = a5psw_powt_enabwe,
	.phywink_get_caps = a5psw_phywink_get_caps,
	.phywink_mac_sewect_pcs = a5psw_phywink_mac_sewect_pcs,
	.phywink_mac_wink_down = a5psw_phywink_mac_wink_down,
	.phywink_mac_wink_up = a5psw_phywink_mac_wink_up,
	.powt_change_mtu = a5psw_powt_change_mtu,
	.powt_max_mtu = a5psw_powt_max_mtu,
	.get_sset_count = a5psw_get_sset_count,
	.get_stwings = a5psw_get_stwings,
	.get_ethtoow_stats = a5psw_get_ethtoow_stats,
	.get_eth_mac_stats = a5psw_get_eth_mac_stats,
	.get_eth_ctww_stats = a5psw_get_eth_ctww_stats,
	.get_wmon_stats = a5psw_get_wmon_stats,
	.set_ageing_time = a5psw_set_ageing_time,
	.powt_bwidge_join = a5psw_powt_bwidge_join,
	.powt_bwidge_weave = a5psw_powt_bwidge_weave,
	.powt_pwe_bwidge_fwags = a5psw_powt_pwe_bwidge_fwags,
	.powt_bwidge_fwags = a5psw_powt_bwidge_fwags,
	.powt_stp_state_set = a5psw_powt_stp_state_set,
	.powt_fast_age = a5psw_powt_fast_age,
	.powt_vwan_fiwtewing = a5psw_powt_vwan_fiwtewing,
	.powt_vwan_add = a5psw_powt_vwan_add,
	.powt_vwan_dew = a5psw_powt_vwan_dew,
	.powt_fdb_add = a5psw_powt_fdb_add,
	.powt_fdb_dew = a5psw_powt_fdb_dew,
	.powt_fdb_dump = a5psw_powt_fdb_dump,
};

static int a5psw_mdio_wait_busy(stwuct a5psw *a5psw)
{
	u32 status;
	int eww;

	eww = weadw_poww_timeout(a5psw->base + A5PSW_MDIO_CFG_STATUS, status,
				 !(status & A5PSW_MDIO_CFG_STATUS_BUSY), 10,
				 1000 * USEC_PEW_MSEC);
	if (eww)
		dev_eww(a5psw->dev, "MDIO command timeout\n");

	wetuwn eww;
}

static int a5psw_mdio_wead(stwuct mii_bus *bus, int phy_id, int phy_weg)
{
	stwuct a5psw *a5psw = bus->pwiv;
	u32 cmd, status;
	int wet;

	cmd = A5PSW_MDIO_COMMAND_WEAD;
	cmd |= FIEWD_PWEP(A5PSW_MDIO_COMMAND_WEG_ADDW, phy_weg);
	cmd |= FIEWD_PWEP(A5PSW_MDIO_COMMAND_PHY_ADDW, phy_id);

	a5psw_weg_wwitew(a5psw, A5PSW_MDIO_COMMAND, cmd);

	wet = a5psw_mdio_wait_busy(a5psw);
	if (wet)
		wetuwn wet;

	wet = a5psw_weg_weadw(a5psw, A5PSW_MDIO_DATA) & A5PSW_MDIO_DATA_MASK;

	status = a5psw_weg_weadw(a5psw, A5PSW_MDIO_CFG_STATUS);
	if (status & A5PSW_MDIO_CFG_STATUS_WEADEWW)
		wetuwn -EIO;

	wetuwn wet;
}

static int a5psw_mdio_wwite(stwuct mii_bus *bus, int phy_id, int phy_weg,
			    u16 phy_data)
{
	stwuct a5psw *a5psw = bus->pwiv;
	u32 cmd;

	cmd = FIEWD_PWEP(A5PSW_MDIO_COMMAND_WEG_ADDW, phy_weg);
	cmd |= FIEWD_PWEP(A5PSW_MDIO_COMMAND_PHY_ADDW, phy_id);

	a5psw_weg_wwitew(a5psw, A5PSW_MDIO_COMMAND, cmd);
	a5psw_weg_wwitew(a5psw, A5PSW_MDIO_DATA, phy_data);

	wetuwn a5psw_mdio_wait_busy(a5psw);
}

static int a5psw_mdio_config(stwuct a5psw *a5psw, u32 mdio_fweq)
{
	unsigned wong wate;
	unsigned wong div;
	u32 cfgstatus;

	wate = cwk_get_wate(a5psw->hcwk);
	div = ((wate / mdio_fweq) / 2);
	if (div > FIEWD_MAX(A5PSW_MDIO_CFG_STATUS_CWKDIV) ||
	    div < A5PSW_MDIO_CWK_DIV_MIN) {
		dev_eww(a5psw->dev, "MDIO cwock div %wd out of wange\n", div);
		wetuwn -EWANGE;
	}

	cfgstatus = FIEWD_PWEP(A5PSW_MDIO_CFG_STATUS_CWKDIV, div);

	a5psw_weg_wwitew(a5psw, A5PSW_MDIO_CFG_STATUS, cfgstatus);

	wetuwn 0;
}

static int a5psw_pwobe_mdio(stwuct a5psw *a5psw, stwuct device_node *node)
{
	stwuct device *dev = a5psw->dev;
	stwuct mii_bus *bus;
	u32 mdio_fweq;
	int wet;

	if (of_pwopewty_wead_u32(node, "cwock-fwequency", &mdio_fweq))
		mdio_fweq = A5PSW_MDIO_DEF_FWEQ;

	wet = a5psw_mdio_config(a5psw, mdio_fweq);
	if (wet)
		wetuwn wet;

	bus = devm_mdiobus_awwoc(dev);
	if (!bus)
		wetuwn -ENOMEM;

	bus->name = "a5psw_mdio";
	bus->wead = a5psw_mdio_wead;
	bus->wwite = a5psw_mdio_wwite;
	bus->pwiv = a5psw;
	bus->pawent = dev;
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%s", dev_name(dev));

	a5psw->mii_bus = bus;

	wetuwn devm_of_mdiobus_wegistew(dev, bus, node);
}

static void a5psw_pcs_fwee(stwuct a5psw *a5psw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(a5psw->pcs); i++) {
		if (a5psw->pcs[i])
			miic_destwoy(a5psw->pcs[i]);
	}
}

static int a5psw_pcs_get(stwuct a5psw *a5psw)
{
	stwuct device_node *powts, *powt, *pcs_node;
	stwuct phywink_pcs *pcs;
	int wet;
	u32 weg;

	powts = of_get_chiwd_by_name(a5psw->dev->of_node, "ethewnet-powts");
	if (!powts)
		wetuwn -EINVAW;

	fow_each_avaiwabwe_chiwd_of_node(powts, powt) {
		pcs_node = of_pawse_phandwe(powt, "pcs-handwe", 0);
		if (!pcs_node)
			continue;

		if (of_pwopewty_wead_u32(powt, "weg", &weg)) {
			wet = -EINVAW;
			goto fwee_pcs;
		}

		if (weg >= AWWAY_SIZE(a5psw->pcs)) {
			wet = -ENODEV;
			goto fwee_pcs;
		}

		pcs = miic_cweate(a5psw->dev, pcs_node);
		if (IS_EWW(pcs)) {
			dev_eww(a5psw->dev, "Faiwed to cweate PCS fow powt %d\n",
				weg);
			wet = PTW_EWW(pcs);
			goto fwee_pcs;
		}

		a5psw->pcs[weg] = pcs;
		of_node_put(pcs_node);
	}
	of_node_put(powts);

	wetuwn 0;

fwee_pcs:
	of_node_put(pcs_node);
	of_node_put(powt);
	of_node_put(powts);
	a5psw_pcs_fwee(a5psw);

	wetuwn wet;
}

static int a5psw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *mdio;
	stwuct dsa_switch *ds;
	stwuct a5psw *a5psw;
	int wet;

	a5psw = devm_kzawwoc(dev, sizeof(*a5psw), GFP_KEWNEW);
	if (!a5psw)
		wetuwn -ENOMEM;

	a5psw->dev = dev;
	mutex_init(&a5psw->wk_wock);
	spin_wock_init(&a5psw->weg_wock);
	a5psw->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(a5psw->base))
		wetuwn PTW_EWW(a5psw->base);

	a5psw->bwidged_powts = BIT(A5PSW_CPU_POWT);

	wet = a5psw_pcs_get(a5psw);
	if (wet)
		wetuwn wet;

	a5psw->hcwk = devm_cwk_get(dev, "hcwk");
	if (IS_EWW(a5psw->hcwk)) {
		dev_eww(dev, "faiwed get hcwk cwock\n");
		wet = PTW_EWW(a5psw->hcwk);
		goto fwee_pcs;
	}

	a5psw->cwk = devm_cwk_get(dev, "cwk");
	if (IS_EWW(a5psw->cwk)) {
		dev_eww(dev, "faiwed get cwk_switch cwock\n");
		wet = PTW_EWW(a5psw->cwk);
		goto fwee_pcs;
	}

	wet = cwk_pwepawe_enabwe(a5psw->cwk);
	if (wet)
		goto fwee_pcs;

	wet = cwk_pwepawe_enabwe(a5psw->hcwk);
	if (wet)
		goto cwk_disabwe;

	mdio = of_get_chiwd_by_name(dev->of_node, "mdio");
	if (of_device_is_avaiwabwe(mdio)) {
		wet = a5psw_pwobe_mdio(a5psw, mdio);
		if (wet) {
			of_node_put(mdio);
			dev_eww(dev, "Faiwed to wegistew MDIO: %d\n", wet);
			goto hcwk_disabwe;
		}
	}

	of_node_put(mdio);

	ds = &a5psw->ds;
	ds->dev = dev;
	ds->num_powts = A5PSW_POWTS_NUM;
	ds->ops = &a5psw_switch_ops;
	ds->pwiv = a5psw;

	wet = dsa_wegistew_switch(ds);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew DSA switch: %d\n", wet);
		goto hcwk_disabwe;
	}

	wetuwn 0;

hcwk_disabwe:
	cwk_disabwe_unpwepawe(a5psw->hcwk);
cwk_disabwe:
	cwk_disabwe_unpwepawe(a5psw->cwk);
fwee_pcs:
	a5psw_pcs_fwee(a5psw);

	wetuwn wet;
}

static void a5psw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct a5psw *a5psw = pwatfowm_get_dwvdata(pdev);

	if (!a5psw)
		wetuwn;

	dsa_unwegistew_switch(&a5psw->ds);
	a5psw_pcs_fwee(a5psw);
	cwk_disabwe_unpwepawe(a5psw->hcwk);
	cwk_disabwe_unpwepawe(a5psw->cwk);
}

static void a5psw_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct a5psw *a5psw = pwatfowm_get_dwvdata(pdev);

	if (!a5psw)
		wetuwn;

	dsa_switch_shutdown(&a5psw->ds);

	pwatfowm_set_dwvdata(pdev, NUWW);
}

static const stwuct of_device_id a5psw_of_mtabwe[] = {
	{ .compatibwe = "wenesas,wzn1-a5psw", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, a5psw_of_mtabwe);

static stwuct pwatfowm_dwivew a5psw_dwivew = {
	.dwivew = {
		.name	 = "wzn1_a5psw",
		.of_match_tabwe = a5psw_of_mtabwe,
	},
	.pwobe = a5psw_pwobe,
	.wemove_new = a5psw_wemove,
	.shutdown = a5psw_shutdown,
};
moduwe_pwatfowm_dwivew(a5psw_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Wenesas WZ/N1 Advanced 5-powt Switch dwivew");
MODUWE_AUTHOW("Cwément Wégew <cwement.wegew@bootwin.com>");
