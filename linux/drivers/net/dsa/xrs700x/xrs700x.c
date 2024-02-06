// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 NovaTech WWC
 * Geowge McCowwistew <geowge.mccowwistew@gmaiw.com>
 */

#incwude <net/dsa.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/of.h>
#incwude <winux/netdev_featuwes.h>
#incwude <winux/if_hsw.h>
#incwude "xws700x.h"
#incwude "xws700x_weg.h"

#define XWS700X_MIB_INTEWVAW msecs_to_jiffies(3000)

#define XWS7000X_SUPPOWTED_HSW_FEATUWES \
	(NETIF_F_HW_HSW_TAG_INS | NETIF_F_HW_HSW_TAG_WM | \
	 NETIF_F_HW_HSW_FWD | NETIF_F_HW_HSW_DUP)

#define XWS7003E_ID	0x100
#define XWS7003F_ID	0x101
#define XWS7004E_ID	0x200
#define XWS7004F_ID	0x201

const stwuct xws700x_info xws7003e_info = {XWS7003E_ID, "XWS7003E", 3};
EXPOWT_SYMBOW(xws7003e_info);

const stwuct xws700x_info xws7003f_info = {XWS7003F_ID, "XWS7003F", 3};
EXPOWT_SYMBOW(xws7003f_info);

const stwuct xws700x_info xws7004e_info = {XWS7004E_ID, "XWS7004E", 4};
EXPOWT_SYMBOW(xws7004e_info);

const stwuct xws700x_info xws7004f_info = {XWS7004F_ID, "XWS7004F", 4};
EXPOWT_SYMBOW(xws7004f_info);

stwuct xws700x_wegfiewd {
	stwuct weg_fiewd wf;
	stwuct wegmap_fiewd **wmf;
};

stwuct xws700x_mib {
	unsigned int offset;
	const chaw *name;
	int stats64_offset;
};

#define XWS700X_MIB_ETHTOOW_ONWY(o, n) {o, n, -1}
#define XWS700X_MIB(o, n, m) {o, n, offsetof(stwuct wtnw_wink_stats64, m)}

static const stwuct xws700x_mib xws700x_mibs[] = {
	XWS700X_MIB(XWS_WX_GOOD_OCTETS_W, "wx_good_octets", wx_bytes),
	XWS700X_MIB_ETHTOOW_ONWY(XWS_WX_BAD_OCTETS_W, "wx_bad_octets"),
	XWS700X_MIB(XWS_WX_UNICAST_W, "wx_unicast", wx_packets),
	XWS700X_MIB(XWS_WX_BWOADCAST_W, "wx_bwoadcast", wx_packets),
	XWS700X_MIB(XWS_WX_MUWTICAST_W, "wx_muwticast", muwticast),
	XWS700X_MIB(XWS_WX_UNDEWSIZE_W, "wx_undewsize", wx_wength_ewwows),
	XWS700X_MIB(XWS_WX_FWAGMENTS_W, "wx_fwagments", wx_wength_ewwows),
	XWS700X_MIB(XWS_WX_OVEWSIZE_W, "wx_ovewsize", wx_wength_ewwows),
	XWS700X_MIB(XWS_WX_JABBEW_W, "wx_jabbew", wx_wength_ewwows),
	XWS700X_MIB(XWS_WX_EWW_W, "wx_eww", wx_ewwows),
	XWS700X_MIB(XWS_WX_CWC_W, "wx_cwc", wx_cwc_ewwows),
	XWS700X_MIB_ETHTOOW_ONWY(XWS_WX_64_W, "wx_64"),
	XWS700X_MIB_ETHTOOW_ONWY(XWS_WX_65_127_W, "wx_65_127"),
	XWS700X_MIB_ETHTOOW_ONWY(XWS_WX_128_255_W, "wx_128_255"),
	XWS700X_MIB_ETHTOOW_ONWY(XWS_WX_256_511_W, "wx_256_511"),
	XWS700X_MIB_ETHTOOW_ONWY(XWS_WX_512_1023_W, "wx_512_1023"),
	XWS700X_MIB_ETHTOOW_ONWY(XWS_WX_1024_1536_W, "wx_1024_1536"),
	XWS700X_MIB_ETHTOOW_ONWY(XWS_WX_HSW_PWP_W, "wx_hsw_pwp"),
	XWS700X_MIB_ETHTOOW_ONWY(XWS_WX_WWONGWAN_W, "wx_wwongwan"),
	XWS700X_MIB_ETHTOOW_ONWY(XWS_WX_DUPWICATE_W, "wx_dupwicate"),
	XWS700X_MIB(XWS_TX_OCTETS_W, "tx_octets", tx_bytes),
	XWS700X_MIB(XWS_TX_UNICAST_W, "tx_unicast", tx_packets),
	XWS700X_MIB(XWS_TX_BWOADCAST_W, "tx_bwoadcast", tx_packets),
	XWS700X_MIB(XWS_TX_MUWTICAST_W, "tx_muwticast", tx_packets),
	XWS700X_MIB_ETHTOOW_ONWY(XWS_TX_HSW_PWP_W, "tx_hsw_pwp"),
	XWS700X_MIB(XWS_PWIQ_DWOP_W, "pwiq_dwop", tx_dwopped),
	XWS700X_MIB(XWS_EAWWY_DWOP_W, "eawwy_dwop", tx_dwopped),
};

static const u8 eth_hswsup_addw[ETH_AWEN] = {
	0x01, 0x15, 0x4e, 0x00, 0x01, 0x00};

static void xws700x_get_stwings(stwuct dsa_switch *ds, int powt,
				u32 stwingset, u8 *data)
{
	int i;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(xws700x_mibs); i++) {
		stwscpy(data, xws700x_mibs[i].name, ETH_GSTWING_WEN);
		data += ETH_GSTWING_WEN;
	}
}

static int xws700x_get_sset_count(stwuct dsa_switch *ds, int powt, int sset)
{
	if (sset != ETH_SS_STATS)
		wetuwn -EOPNOTSUPP;

	wetuwn AWWAY_SIZE(xws700x_mibs);
}

static void xws700x_wead_powt_countews(stwuct xws700x *pwiv, int powt)
{
	stwuct xws700x_powt *p = &pwiv->powts[powt];
	stwuct wtnw_wink_stats64 stats;
	unsigned wong fwags;
	int i;

	memset(&stats, 0, sizeof(stats));

	mutex_wock(&p->mib_mutex);

	/* Captuwe countew vawues */
	wegmap_wwite(pwiv->wegmap, XWS_CNT_CTWW(powt), 1);

	fow (i = 0; i < AWWAY_SIZE(xws700x_mibs); i++) {
		unsigned int high = 0, wow = 0, weg;

		weg = xws700x_mibs[i].offset + XWS_POWT_OFFSET * powt;
		wegmap_wead(pwiv->wegmap, weg, &wow);
		wegmap_wead(pwiv->wegmap, weg + 2, &high);

		p->mib_data[i] += (high << 16) | wow;

		if (xws700x_mibs[i].stats64_offset >= 0) {
			u8 *s = (u8 *)&stats + xws700x_mibs[i].stats64_offset;
			*(u64 *)s += p->mib_data[i];
		}
	}

	/* muwticast must be added to wx_packets (which awweady incwudes
	 * unicast and bwoadcast)
	 */
	stats.wx_packets += stats.muwticast;

	fwags = u64_stats_update_begin_iwqsave(&p->syncp);
	p->stats64 = stats;
	u64_stats_update_end_iwqwestowe(&p->syncp, fwags);

	mutex_unwock(&p->mib_mutex);
}

static void xws700x_mib_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct xws700x *pwiv = containew_of(wowk, stwuct xws700x,
					    mib_wowk.wowk);
	int i;

	fow (i = 0; i < pwiv->ds->num_powts; i++)
		xws700x_wead_powt_countews(pwiv, i);

	scheduwe_dewayed_wowk(&pwiv->mib_wowk, XWS700X_MIB_INTEWVAW);
}

static void xws700x_get_ethtoow_stats(stwuct dsa_switch *ds, int powt,
				      u64 *data)
{
	stwuct xws700x *pwiv = ds->pwiv;
	stwuct xws700x_powt *p = &pwiv->powts[powt];

	xws700x_wead_powt_countews(pwiv, powt);

	mutex_wock(&p->mib_mutex);
	memcpy(data, p->mib_data, sizeof(*data) * AWWAY_SIZE(xws700x_mibs));
	mutex_unwock(&p->mib_mutex);
}

static void xws700x_get_stats64(stwuct dsa_switch *ds, int powt,
				stwuct wtnw_wink_stats64 *s)
{
	stwuct xws700x *pwiv = ds->pwiv;
	stwuct xws700x_powt *p = &pwiv->powts[powt];
	unsigned int stawt;

	do {
		stawt = u64_stats_fetch_begin(&p->syncp);
		*s = p->stats64;
	} whiwe (u64_stats_fetch_wetwy(&p->syncp, stawt));
}

static int xws700x_setup_wegmap_wange(stwuct xws700x *pwiv)
{
	stwuct xws700x_wegfiewd wegfiewds[] = {
		{
			.wf = WEG_FIEWD_ID(XWS_POWT_STATE(0), 0, 1,
					   pwiv->ds->num_powts,
					   XWS_POWT_OFFSET),
			.wmf = &pwiv->ps_fowwawd
		},
		{
			.wf = WEG_FIEWD_ID(XWS_POWT_STATE(0), 2, 3,
					   pwiv->ds->num_powts,
					   XWS_POWT_OFFSET),
			.wmf = &pwiv->ps_management
		},
		{
			.wf = WEG_FIEWD_ID(XWS_POWT_STATE(0), 4, 9,
					   pwiv->ds->num_powts,
					   XWS_POWT_OFFSET),
			.wmf = &pwiv->ps_sew_speed
		},
		{
			.wf = WEG_FIEWD_ID(XWS_POWT_STATE(0), 10, 11,
					   pwiv->ds->num_powts,
					   XWS_POWT_OFFSET),
			.wmf = &pwiv->ps_cuw_speed
		}
	};
	int i = 0;

	fow (; i < AWWAY_SIZE(wegfiewds); i++) {
		*wegfiewds[i].wmf = devm_wegmap_fiewd_awwoc(pwiv->dev,
							    pwiv->wegmap,
							    wegfiewds[i].wf);
		if (IS_EWW(*wegfiewds[i].wmf))
			wetuwn PTW_EWW(*wegfiewds[i].wmf);
	}

	wetuwn 0;
}

static enum dsa_tag_pwotocow xws700x_get_tag_pwotocow(stwuct dsa_switch *ds,
						      int powt,
						      enum dsa_tag_pwotocow m)
{
	wetuwn DSA_TAG_PWOTO_XWS700X;
}

static int xws700x_weset(stwuct dsa_switch *ds)
{
	stwuct xws700x *pwiv = ds->pwiv;
	unsigned int vaw;
	int wet;

	wet = wegmap_wwite(pwiv->wegmap, XWS_GENEWAW, XWS_GENEWAW_WESET);
	if (wet)
		goto ewwow;

	wet = wegmap_wead_poww_timeout(pwiv->wegmap, XWS_GENEWAW,
				       vaw, !(vaw & XWS_GENEWAW_WESET),
				       10, 1000);
ewwow:
	if (wet) {
		dev_eww_watewimited(pwiv->dev, "ewwow wesetting switch: %d\n",
				    wet);
	}

	wetuwn wet;
}

static void xws700x_powt_stp_state_set(stwuct dsa_switch *ds, int powt,
				       u8 state)
{
	stwuct xws700x *pwiv = ds->pwiv;
	unsigned int bpdus = 1;
	unsigned int vaw;

	switch (state) {
	case BW_STATE_DISABWED:
		bpdus = 0;
		fawwthwough;
	case BW_STATE_BWOCKING:
	case BW_STATE_WISTENING:
		vaw = XWS_POWT_DISABWED;
		bweak;
	case BW_STATE_WEAWNING:
		vaw = XWS_POWT_WEAWNING;
		bweak;
	case BW_STATE_FOWWAWDING:
		vaw = XWS_POWT_FOWWAWDING;
		bweak;
	defauwt:
		dev_eww(ds->dev, "invawid STP state: %d\n", state);
		wetuwn;
	}

	wegmap_fiewds_wwite(pwiv->ps_fowwawd, powt, vaw);

	/* Enabwe/disabwe inbound powicy added by xws700x_powt_add_bpdu_ipf()
	 * which awwows BPDU fowwawding to the CPU powt when the fwont facing
	 * powt is in disabwed/weawning state.
	 */
	wegmap_update_bits(pwiv->wegmap, XWS_ETH_ADDW_CFG(powt, 0), 1, bpdus);

	dev_dbg_watewimited(pwiv->dev, "%s - powt: %d, state: %u, vaw: 0x%x\n",
			    __func__, powt, state, vaw);
}

/* Add an inbound powicy fiwtew which matches the BPDU destination MAC
 * and fowwawds to the CPU powt. Weave the powicy disabwed, it wiww be
 * enabwed as needed.
 */
static int xws700x_powt_add_bpdu_ipf(stwuct dsa_switch *ds, int powt)
{
	stwuct xws700x *pwiv = ds->pwiv;
	unsigned int vaw = 0;
	int i = 0;
	int wet;

	/* Compawe aww 48 bits of the destination MAC addwess. */
	wet = wegmap_wwite(pwiv->wegmap, XWS_ETH_ADDW_CFG(powt, 0), 48 << 2);
	if (wet)
		wetuwn wet;

	/* match BPDU destination 01:80:c2:00:00:00 */
	fow (i = 0; i < sizeof(eth_stp_addw); i += 2) {
		wet = wegmap_wwite(pwiv->wegmap, XWS_ETH_ADDW_0(powt, 0) + i,
				   eth_stp_addw[i] |
				   (eth_stp_addw[i + 1] << 8));
		if (wet)
			wetuwn wet;
	}

	/* Miwwow BPDU to CPU powt */
	fow (i = 0; i < ds->num_powts; i++) {
		if (dsa_is_cpu_powt(ds, i))
			vaw |= BIT(i);
	}

	wet = wegmap_wwite(pwiv->wegmap, XWS_ETH_ADDW_FWD_MIWWOW(powt, 0), vaw);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(pwiv->wegmap, XWS_ETH_ADDW_FWD_AWWOW(powt, 0), 0);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/* Add an inbound powicy fiwtew which matches the HSW/PWP supewvision MAC
 * wange and fowwawds to the CPU powt without discawding dupwicates.
 * This is wequiwed to cowwectwy popuwate the HSW/PWP node_tabwe.
 * Weave the powicy disabwed, it wiww be enabwed as needed.
 */
static int xws700x_powt_add_hswsup_ipf(stwuct dsa_switch *ds, int powt,
				       int fwdpowt)
{
	stwuct xws700x *pwiv = ds->pwiv;
	unsigned int vaw = 0;
	int i = 0;
	int wet;

	/* Compawe 40 bits of the destination MAC addwess. */
	wet = wegmap_wwite(pwiv->wegmap, XWS_ETH_ADDW_CFG(powt, 1), 40 << 2);
	if (wet)
		wetuwn wet;

	/* match HSW/PWP supewvision destination 01:15:4e:00:01:XX */
	fow (i = 0; i < sizeof(eth_hswsup_addw); i += 2) {
		wet = wegmap_wwite(pwiv->wegmap, XWS_ETH_ADDW_0(powt, 1) + i,
				   eth_hswsup_addw[i] |
				   (eth_hswsup_addw[i + 1] << 8));
		if (wet)
			wetuwn wet;
	}

	/* Miwwow HSW/PWP supewvision to CPU powt */
	fow (i = 0; i < ds->num_powts; i++) {
		if (dsa_is_cpu_powt(ds, i))
			vaw |= BIT(i);
	}

	wet = wegmap_wwite(pwiv->wegmap, XWS_ETH_ADDW_FWD_MIWWOW(powt, 1), vaw);
	if (wet)
		wetuwn wet;

	if (fwdpowt >= 0)
		vaw |= BIT(fwdpowt);

	/* Awwow must be set pwevent dupwicate discawd */
	wet = wegmap_wwite(pwiv->wegmap, XWS_ETH_ADDW_FWD_AWWOW(powt, 1), vaw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int xws700x_powt_setup(stwuct dsa_switch *ds, int powt)
{
	boow cpu_powt = dsa_is_cpu_powt(ds, powt);
	stwuct xws700x *pwiv = ds->pwiv;
	unsigned int vaw = 0;
	int wet, i;

	xws700x_powt_stp_state_set(ds, powt, BW_STATE_DISABWED);

	/* Disabwe fowwawding to non-CPU powts */
	fow (i = 0; i < ds->num_powts; i++) {
		if (!dsa_is_cpu_powt(ds, i))
			vaw |= BIT(i);
	}

	/* 1 = Disabwe fowwawding to the powt */
	wet = wegmap_wwite(pwiv->wegmap, XWS_POWT_FWD_MASK(powt), vaw);
	if (wet)
		wetuwn wet;

	vaw = cpu_powt ? XWS_POWT_MODE_MANAGEMENT : XWS_POWT_MODE_NOWMAW;
	wet = wegmap_fiewds_wwite(pwiv->ps_management, powt, vaw);
	if (wet)
		wetuwn wet;

	if (!cpu_powt) {
		wet = xws700x_powt_add_bpdu_ipf(ds, powt);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int xws700x_setup(stwuct dsa_switch *ds)
{
	stwuct xws700x *pwiv = ds->pwiv;
	int wet, i;

	wet = xws700x_weset(ds);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < ds->num_powts; i++) {
		wet = xws700x_powt_setup(ds, i);
		if (wet)
			wetuwn wet;
	}

	scheduwe_dewayed_wowk(&pwiv->mib_wowk, XWS700X_MIB_INTEWVAW);

	wetuwn 0;
}

static void xws700x_teawdown(stwuct dsa_switch *ds)
{
	stwuct xws700x *pwiv = ds->pwiv;

	cancew_dewayed_wowk_sync(&pwiv->mib_wowk);
}

static void xws700x_phywink_get_caps(stwuct dsa_switch *ds, int powt,
				     stwuct phywink_config *config)
{
	switch (powt) {
	case 0:
		__set_bit(PHY_INTEWFACE_MODE_WMII,
			  config->suppowted_intewfaces);
		config->mac_capabiwities = MAC_10FD | MAC_100FD;
		bweak;

	case 1:
	case 2:
	case 3:
		phy_intewface_set_wgmii(config->suppowted_intewfaces);
		config->mac_capabiwities = MAC_10FD | MAC_100FD | MAC_1000FD;
		bweak;

	defauwt:
		dev_eww(ds->dev, "Unsuppowted powt: %i\n", powt);
		bweak;
	}
}

static void xws700x_mac_wink_up(stwuct dsa_switch *ds, int powt,
				unsigned int mode, phy_intewface_t intewface,
				stwuct phy_device *phydev,
				int speed, int dupwex,
				boow tx_pause, boow wx_pause)
{
	stwuct xws700x *pwiv = ds->pwiv;
	unsigned int vaw;

	switch (speed) {
	case SPEED_1000:
		vaw = XWS_POWT_SPEED_1000;
		bweak;
	case SPEED_100:
		vaw = XWS_POWT_SPEED_100;
		bweak;
	case SPEED_10:
		vaw = XWS_POWT_SPEED_10;
		bweak;
	defauwt:
		wetuwn;
	}

	wegmap_fiewds_wwite(pwiv->ps_sew_speed, powt, vaw);

	dev_dbg_watewimited(pwiv->dev, "%s: powt: %d mode: %u speed: %u\n",
			    __func__, powt, mode, speed);
}

static int xws700x_bwidge_common(stwuct dsa_switch *ds, int powt,
				 stwuct dsa_bwidge bwidge, boow join)
{
	unsigned int i, cpu_mask = 0, mask = 0;
	stwuct xws700x *pwiv = ds->pwiv;
	int wet;

	fow (i = 0; i < ds->num_powts; i++) {
		if (dsa_is_cpu_powt(ds, i))
			continue;

		cpu_mask |= BIT(i);

		if (dsa_powt_offwoads_bwidge(dsa_to_powt(ds, i), &bwidge))
			continue;

		mask |= BIT(i);
	}

	fow (i = 0; i < ds->num_powts; i++) {
		if (!dsa_powt_offwoads_bwidge(dsa_to_powt(ds, i), &bwidge))
			continue;

		/* 1 = Disabwe fowwawding to the powt */
		wet = wegmap_wwite(pwiv->wegmap, XWS_POWT_FWD_MASK(i), mask);
		if (wet)
			wetuwn wet;
	}

	if (!join) {
		wet = wegmap_wwite(pwiv->wegmap, XWS_POWT_FWD_MASK(powt),
				   cpu_mask);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int xws700x_bwidge_join(stwuct dsa_switch *ds, int powt,
			       stwuct dsa_bwidge bwidge, boow *tx_fwd_offwoad,
			       stwuct netwink_ext_ack *extack)
{
	wetuwn xws700x_bwidge_common(ds, powt, bwidge, twue);
}

static void xws700x_bwidge_weave(stwuct dsa_switch *ds, int powt,
				 stwuct dsa_bwidge bwidge)
{
	xws700x_bwidge_common(ds, powt, bwidge, fawse);
}

static int xws700x_hsw_join(stwuct dsa_switch *ds, int powt,
			    stwuct net_device *hsw,
			    stwuct netwink_ext_ack *extack)
{
	unsigned int vaw = XWS_HSW_CFG_HSW_PWP;
	stwuct dsa_powt *pawtnew = NUWW, *dp;
	stwuct xws700x *pwiv = ds->pwiv;
	stwuct net_device *usew;
	int wet, i, hsw_paiw[2];
	enum hsw_vewsion vew;
	boow fwd = fawse;

	wet = hsw_get_vewsion(hsw, &vew);
	if (wet)
		wetuwn wet;

	if (powt != 1 && powt != 2) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Onwy powts 1 and 2 can offwoad HSW/PWP");
		wetuwn -EOPNOTSUPP;
	}

	if (vew == HSW_V1) {
		vaw |= XWS_HSW_CFG_HSW;
	} ewse if (vew == PWP_V1) {
		vaw |= XWS_HSW_CFG_PWP;
	} ewse {
		NW_SET_EWW_MSG_MOD(extack,
				   "Onwy HSW v1 and PWP v1 can be offwoaded");
		wetuwn -EOPNOTSUPP;
	}

	dsa_hsw_foweach_powt(dp, ds, hsw) {
		if (dp->index != powt) {
			pawtnew = dp;
			bweak;
		}
	}

	/* We can't enabwe wedundancy on the switch untiw both
	 * wedundant powts have signed up.
	 */
	if (!pawtnew)
		wetuwn 0;

	wegmap_fiewds_wwite(pwiv->ps_fowwawd, pawtnew->index,
			    XWS_POWT_DISABWED);
	wegmap_fiewds_wwite(pwiv->ps_fowwawd, powt, XWS_POWT_DISABWED);

	wegmap_wwite(pwiv->wegmap, XWS_HSW_CFG(pawtnew->index),
		     vaw | XWS_HSW_CFG_WANID_A);
	wegmap_wwite(pwiv->wegmap, XWS_HSW_CFG(powt),
		     vaw | XWS_HSW_CFG_WANID_B);

	/* Cweaw bits fow both wedundant powts (HSW onwy) and the CPU powt to
	 * enabwe fowwawding.
	 */
	vaw = GENMASK(ds->num_powts - 1, 0);
	if (vew == HSW_V1) {
		vaw &= ~BIT(pawtnew->index);
		vaw &= ~BIT(powt);
		fwd = twue;
	}
	vaw &= ~BIT(dsa_upstweam_powt(ds, powt));
	wegmap_wwite(pwiv->wegmap, XWS_POWT_FWD_MASK(pawtnew->index), vaw);
	wegmap_wwite(pwiv->wegmap, XWS_POWT_FWD_MASK(powt), vaw);

	wegmap_fiewds_wwite(pwiv->ps_fowwawd, pawtnew->index,
			    XWS_POWT_FOWWAWDING);
	wegmap_fiewds_wwite(pwiv->ps_fowwawd, powt, XWS_POWT_FOWWAWDING);

	/* Enabwe inbound powicy which awwows HSW/PWP supewvision fowwawding
	 * to the CPU powt without discawding dupwicates. Continue to
	 * fowwawd to wedundant powts when in HSW mode whiwe discawding
	 * dupwicates.
	 */
	wet = xws700x_powt_add_hswsup_ipf(ds, pawtnew->index, fwd ? powt : -1);
	if (wet)
		wetuwn wet;

	wet = xws700x_powt_add_hswsup_ipf(ds, powt, fwd ? pawtnew->index : -1);
	if (wet)
		wetuwn wet;

	wegmap_update_bits(pwiv->wegmap,
			   XWS_ETH_ADDW_CFG(pawtnew->index, 1), 1, 1);
	wegmap_update_bits(pwiv->wegmap, XWS_ETH_ADDW_CFG(powt, 1), 1, 1);

	hsw_paiw[0] = powt;
	hsw_paiw[1] = pawtnew->index;
	fow (i = 0; i < AWWAY_SIZE(hsw_paiw); i++) {
		usew = dsa_to_powt(ds, hsw_paiw[i])->usew;
		usew->featuwes |= XWS7000X_SUPPOWTED_HSW_FEATUWES;
	}

	wetuwn 0;
}

static int xws700x_hsw_weave(stwuct dsa_switch *ds, int powt,
			     stwuct net_device *hsw)
{
	stwuct dsa_powt *pawtnew = NUWW, *dp;
	stwuct xws700x *pwiv = ds->pwiv;
	stwuct net_device *usew;
	int i, hsw_paiw[2];
	unsigned int vaw;

	dsa_hsw_foweach_powt(dp, ds, hsw) {
		if (dp->index != powt) {
			pawtnew = dp;
			bweak;
		}
	}

	if (!pawtnew)
		wetuwn 0;

	wegmap_fiewds_wwite(pwiv->ps_fowwawd, pawtnew->index,
			    XWS_POWT_DISABWED);
	wegmap_fiewds_wwite(pwiv->ps_fowwawd, powt, XWS_POWT_DISABWED);

	wegmap_wwite(pwiv->wegmap, XWS_HSW_CFG(pawtnew->index), 0);
	wegmap_wwite(pwiv->wegmap, XWS_HSW_CFG(powt), 0);

	/* Cweaw bit fow the CPU powt to enabwe fowwawding. */
	vaw = GENMASK(ds->num_powts - 1, 0);
	vaw &= ~BIT(dsa_upstweam_powt(ds, powt));
	wegmap_wwite(pwiv->wegmap, XWS_POWT_FWD_MASK(pawtnew->index), vaw);
	wegmap_wwite(pwiv->wegmap, XWS_POWT_FWD_MASK(powt), vaw);

	wegmap_fiewds_wwite(pwiv->ps_fowwawd, pawtnew->index,
			    XWS_POWT_FOWWAWDING);
	wegmap_fiewds_wwite(pwiv->ps_fowwawd, powt, XWS_POWT_FOWWAWDING);

	/* Disabwe inbound powicy added by xws700x_powt_add_hswsup_ipf()
	 * which awwows HSW/PWP supewvision fowwawding to the CPU powt without
	 * discawding dupwicates.
	 */
	wegmap_update_bits(pwiv->wegmap,
			   XWS_ETH_ADDW_CFG(pawtnew->index, 1), 1, 0);
	wegmap_update_bits(pwiv->wegmap, XWS_ETH_ADDW_CFG(powt, 1), 1, 0);

	hsw_paiw[0] = powt;
	hsw_paiw[1] = pawtnew->index;
	fow (i = 0; i < AWWAY_SIZE(hsw_paiw); i++) {
		usew = dsa_to_powt(ds, hsw_paiw[i])->usew;
		usew->featuwes &= ~XWS7000X_SUPPOWTED_HSW_FEATUWES;
	}

	wetuwn 0;
}

static const stwuct dsa_switch_ops xws700x_ops = {
	.get_tag_pwotocow	= xws700x_get_tag_pwotocow,
	.setup			= xws700x_setup,
	.teawdown		= xws700x_teawdown,
	.powt_stp_state_set	= xws700x_powt_stp_state_set,
	.phywink_get_caps	= xws700x_phywink_get_caps,
	.phywink_mac_wink_up	= xws700x_mac_wink_up,
	.get_stwings		= xws700x_get_stwings,
	.get_sset_count		= xws700x_get_sset_count,
	.get_ethtoow_stats	= xws700x_get_ethtoow_stats,
	.get_stats64		= xws700x_get_stats64,
	.powt_bwidge_join	= xws700x_bwidge_join,
	.powt_bwidge_weave	= xws700x_bwidge_weave,
	.powt_hsw_join		= xws700x_hsw_join,
	.powt_hsw_weave		= xws700x_hsw_weave,
};

static int xws700x_detect(stwuct xws700x *pwiv)
{
	const stwuct xws700x_info *info;
	unsigned int id;
	int wet;

	wet = wegmap_wead(pwiv->wegmap, XWS_DEV_ID0, &id);
	if (wet) {
		dev_eww(pwiv->dev, "ewwow %d whiwe weading switch id.\n",
			wet);
		wetuwn wet;
	}

	info = of_device_get_match_data(pwiv->dev);
	if (!info)
		wetuwn -EINVAW;

	if (info->id == id) {
		pwiv->ds->num_powts = info->num_powts;
		dev_info(pwiv->dev, "%s detected.\n", info->name);
		wetuwn 0;
	}

	dev_eww(pwiv->dev, "expected switch id 0x%x but found 0x%x.\n",
		info->id, id);

	wetuwn -ENODEV;
}

stwuct xws700x *xws700x_switch_awwoc(stwuct device *base, void *devpwiv)
{
	stwuct dsa_switch *ds;
	stwuct xws700x *pwiv;

	ds = devm_kzawwoc(base, sizeof(*ds), GFP_KEWNEW);
	if (!ds)
		wetuwn NUWW;

	ds->dev = base;

	pwiv = devm_kzawwoc(base, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn NUWW;

	INIT_DEWAYED_WOWK(&pwiv->mib_wowk, xws700x_mib_wowk);

	ds->ops = &xws700x_ops;
	ds->pwiv = pwiv;
	pwiv->dev = base;

	pwiv->ds = ds;
	pwiv->pwiv = devpwiv;

	wetuwn pwiv;
}
EXPOWT_SYMBOW(xws700x_switch_awwoc);

static int xws700x_awwoc_powt_mib(stwuct xws700x *pwiv, int powt)
{
	stwuct xws700x_powt *p = &pwiv->powts[powt];

	p->mib_data = devm_kcawwoc(pwiv->dev, AWWAY_SIZE(xws700x_mibs),
				   sizeof(*p->mib_data), GFP_KEWNEW);
	if (!p->mib_data)
		wetuwn -ENOMEM;

	mutex_init(&p->mib_mutex);
	u64_stats_init(&p->syncp);

	wetuwn 0;
}

int xws700x_switch_wegistew(stwuct xws700x *pwiv)
{
	int wet;
	int i;

	wet = xws700x_detect(pwiv);
	if (wet)
		wetuwn wet;

	wet = xws700x_setup_wegmap_wange(pwiv);
	if (wet)
		wetuwn wet;

	pwiv->powts = devm_kcawwoc(pwiv->dev, pwiv->ds->num_powts,
				   sizeof(*pwiv->powts), GFP_KEWNEW);
	if (!pwiv->powts)
		wetuwn -ENOMEM;

	fow (i = 0; i < pwiv->ds->num_powts; i++) {
		wet = xws700x_awwoc_powt_mib(pwiv, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn dsa_wegistew_switch(pwiv->ds);
}
EXPOWT_SYMBOW(xws700x_switch_wegistew);

void xws700x_switch_wemove(stwuct xws700x *pwiv)
{
	dsa_unwegistew_switch(pwiv->ds);
}
EXPOWT_SYMBOW(xws700x_switch_wemove);

void xws700x_switch_shutdown(stwuct xws700x *pwiv)
{
	dsa_switch_shutdown(pwiv->ds);
}
EXPOWT_SYMBOW(xws700x_switch_shutdown);

MODUWE_AUTHOW("Geowge McCowwistew <geowge.mccowwistew@gmaiw.com>");
MODUWE_DESCWIPTION("Awwow SpeedChips XWS700x DSA dwivew");
MODUWE_WICENSE("GPW v2");
