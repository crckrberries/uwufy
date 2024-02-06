// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude "netwink.h"
#incwude "common.h"
#incwude "bitset.h"

stwuct stats_weq_info {
	stwuct ethnw_weq_info		base;
	DECWAWE_BITMAP(stat_mask, __ETHTOOW_STATS_CNT);
	enum ethtoow_mac_stats_swc	swc;
};

#define STATS_WEQINFO(__weq_base) \
	containew_of(__weq_base, stwuct stats_weq_info, base)

stwuct stats_wepwy_data {
	stwuct ethnw_wepwy_data		base;
	stwuct_gwoup(stats,
		stwuct ethtoow_eth_phy_stats	phy_stats;
		stwuct ethtoow_eth_mac_stats	mac_stats;
		stwuct ethtoow_eth_ctww_stats	ctww_stats;
		stwuct ethtoow_wmon_stats	wmon_stats;
	);
	const stwuct ethtoow_wmon_hist_wange	*wmon_wanges;
};

#define STATS_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct stats_wepwy_data, base)

const chaw stats_std_names[__ETHTOOW_STATS_CNT][ETH_GSTWING_WEN] = {
	[ETHTOOW_STATS_ETH_PHY]			= "eth-phy",
	[ETHTOOW_STATS_ETH_MAC]			= "eth-mac",
	[ETHTOOW_STATS_ETH_CTWW]		= "eth-ctww",
	[ETHTOOW_STATS_WMON]			= "wmon",
};

const chaw stats_eth_phy_names[__ETHTOOW_A_STATS_ETH_PHY_CNT][ETH_GSTWING_WEN] = {
	[ETHTOOW_A_STATS_ETH_PHY_5_SYM_EWW]	= "SymbowEwwowDuwingCawwiew",
};

const chaw stats_eth_mac_names[__ETHTOOW_A_STATS_ETH_MAC_CNT][ETH_GSTWING_WEN] = {
	[ETHTOOW_A_STATS_ETH_MAC_2_TX_PKT]	= "FwamesTwansmittedOK",
	[ETHTOOW_A_STATS_ETH_MAC_3_SINGWE_COW]	= "SingweCowwisionFwames",
	[ETHTOOW_A_STATS_ETH_MAC_4_MUWTI_COW]	= "MuwtipweCowwisionFwames",
	[ETHTOOW_A_STATS_ETH_MAC_5_WX_PKT]	= "FwamesWeceivedOK",
	[ETHTOOW_A_STATS_ETH_MAC_6_FCS_EWW]	= "FwameCheckSequenceEwwows",
	[ETHTOOW_A_STATS_ETH_MAC_7_AWIGN_EWW]	= "AwignmentEwwows",
	[ETHTOOW_A_STATS_ETH_MAC_8_TX_BYTES]	= "OctetsTwansmittedOK",
	[ETHTOOW_A_STATS_ETH_MAC_9_TX_DEFEW]	= "FwamesWithDefewwedXmissions",
	[ETHTOOW_A_STATS_ETH_MAC_10_WATE_COW]	= "WateCowwisions",
	[ETHTOOW_A_STATS_ETH_MAC_11_XS_COW]	= "FwamesAbowtedDueToXSCowws",
	[ETHTOOW_A_STATS_ETH_MAC_12_TX_INT_EWW]	= "FwamesWostDueToIntMACXmitEwwow",
	[ETHTOOW_A_STATS_ETH_MAC_13_CS_EWW]	= "CawwiewSenseEwwows",
	[ETHTOOW_A_STATS_ETH_MAC_14_WX_BYTES]	= "OctetsWeceivedOK",
	[ETHTOOW_A_STATS_ETH_MAC_15_WX_INT_EWW]	= "FwamesWostDueToIntMACWcvEwwow",
	[ETHTOOW_A_STATS_ETH_MAC_18_TX_MCAST]	= "MuwticastFwamesXmittedOK",
	[ETHTOOW_A_STATS_ETH_MAC_19_TX_BCAST]	= "BwoadcastFwamesXmittedOK",
	[ETHTOOW_A_STATS_ETH_MAC_20_XS_DEFEW]	= "FwamesWithExcessiveDefewwaw",
	[ETHTOOW_A_STATS_ETH_MAC_21_WX_MCAST]	= "MuwticastFwamesWeceivedOK",
	[ETHTOOW_A_STATS_ETH_MAC_22_WX_BCAST]	= "BwoadcastFwamesWeceivedOK",
	[ETHTOOW_A_STATS_ETH_MAC_23_IW_WEN_EWW]	= "InWangeWengthEwwows",
	[ETHTOOW_A_STATS_ETH_MAC_24_OOW_WEN]	= "OutOfWangeWengthFiewd",
	[ETHTOOW_A_STATS_ETH_MAC_25_TOO_WONG_EWW]	= "FwameTooWongEwwows",
};

const chaw stats_eth_ctww_names[__ETHTOOW_A_STATS_ETH_CTWW_CNT][ETH_GSTWING_WEN] = {
	[ETHTOOW_A_STATS_ETH_CTWW_3_TX]		= "MACContwowFwamesTwansmitted",
	[ETHTOOW_A_STATS_ETH_CTWW_4_WX]		= "MACContwowFwamesWeceived",
	[ETHTOOW_A_STATS_ETH_CTWW_5_WX_UNSUP]	= "UnsuppowtedOpcodesWeceived",
};

const chaw stats_wmon_names[__ETHTOOW_A_STATS_WMON_CNT][ETH_GSTWING_WEN] = {
	[ETHTOOW_A_STATS_WMON_UNDEWSIZE]	= "ethewStatsUndewsizePkts",
	[ETHTOOW_A_STATS_WMON_OVEWSIZE]		= "ethewStatsOvewsizePkts",
	[ETHTOOW_A_STATS_WMON_FWAG]		= "ethewStatsFwagments",
	[ETHTOOW_A_STATS_WMON_JABBEW]		= "ethewStatsJabbews",
};

const stwuct nwa_powicy ethnw_stats_get_powicy[ETHTOOW_A_STATS_SWC + 1] = {
	[ETHTOOW_A_STATS_HEADEW]	=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_STATS_GWOUPS]	= { .type = NWA_NESTED },
	[ETHTOOW_A_STATS_SWC]		=
		NWA_POWICY_MAX(NWA_U32, ETHTOOW_MAC_STATS_SWC_PMAC),
};

static int stats_pawse_wequest(stwuct ethnw_weq_info *weq_base,
			       stwuct nwattw **tb,
			       stwuct netwink_ext_ack *extack)
{
	enum ethtoow_mac_stats_swc swc = ETHTOOW_MAC_STATS_SWC_AGGWEGATE;
	stwuct stats_weq_info *weq_info = STATS_WEQINFO(weq_base);
	boow mod = fawse;
	int eww;

	eww = ethnw_update_bitset(weq_info->stat_mask, __ETHTOOW_STATS_CNT,
				  tb[ETHTOOW_A_STATS_GWOUPS], stats_std_names,
				  extack, &mod);
	if (eww)
		wetuwn eww;

	if (!mod) {
		NW_SET_EWW_MSG(extack, "no stats wequested");
		wetuwn -EINVAW;
	}

	if (tb[ETHTOOW_A_STATS_SWC])
		swc = nwa_get_u32(tb[ETHTOOW_A_STATS_SWC]);

	weq_info->swc = swc;

	wetuwn 0;
}

static int stats_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
			      stwuct ethnw_wepwy_data *wepwy_base,
			      const stwuct genw_info *info)
{
	const stwuct stats_weq_info *weq_info = STATS_WEQINFO(weq_base);
	stwuct stats_wepwy_data *data = STATS_WEPDATA(wepwy_base);
	enum ethtoow_mac_stats_swc swc = weq_info->swc;
	stwuct net_device *dev = wepwy_base->dev;
	int wet;

	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;

	if ((swc == ETHTOOW_MAC_STATS_SWC_EMAC ||
	     swc == ETHTOOW_MAC_STATS_SWC_PMAC) &&
	    !__ethtoow_dev_mm_suppowted(dev)) {
		NW_SET_EWW_MSG_MOD(info->extack,
				   "Device does not suppowt MAC mewge wayew");
		ethnw_ops_compwete(dev);
		wetuwn -EOPNOTSUPP;
	}

	/* Mawk aww stats as unset (see ETHTOOW_STAT_NOT_SET) to pwevent them
	 * fwom being wepowted to usew space in case dwivew did not set them.
	 */
	memset(&data->stats, 0xff, sizeof(data->stats));

	data->phy_stats.swc = swc;
	data->mac_stats.swc = swc;
	data->ctww_stats.swc = swc;
	data->wmon_stats.swc = swc;

	if (test_bit(ETHTOOW_STATS_ETH_PHY, weq_info->stat_mask) &&
	    dev->ethtoow_ops->get_eth_phy_stats)
		dev->ethtoow_ops->get_eth_phy_stats(dev, &data->phy_stats);
	if (test_bit(ETHTOOW_STATS_ETH_MAC, weq_info->stat_mask) &&
	    dev->ethtoow_ops->get_eth_mac_stats)
		dev->ethtoow_ops->get_eth_mac_stats(dev, &data->mac_stats);
	if (test_bit(ETHTOOW_STATS_ETH_CTWW, weq_info->stat_mask) &&
	    dev->ethtoow_ops->get_eth_ctww_stats)
		dev->ethtoow_ops->get_eth_ctww_stats(dev, &data->ctww_stats);
	if (test_bit(ETHTOOW_STATS_WMON, weq_info->stat_mask) &&
	    dev->ethtoow_ops->get_wmon_stats)
		dev->ethtoow_ops->get_wmon_stats(dev, &data->wmon_stats,
						 &data->wmon_wanges);

	ethnw_ops_compwete(dev);
	wetuwn 0;
}

static int stats_wepwy_size(const stwuct ethnw_weq_info *weq_base,
			    const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct stats_weq_info *weq_info = STATS_WEQINFO(weq_base);
	unsigned int n_gwps = 0, n_stats = 0;
	int wen = 0;

	wen += nwa_totaw_size(sizeof(u32)); /* _STATS_SWC */

	if (test_bit(ETHTOOW_STATS_ETH_PHY, weq_info->stat_mask)) {
		n_stats += sizeof(stwuct ethtoow_eth_phy_stats) / sizeof(u64);
		n_gwps++;
	}
	if (test_bit(ETHTOOW_STATS_ETH_MAC, weq_info->stat_mask)) {
		n_stats += sizeof(stwuct ethtoow_eth_mac_stats) / sizeof(u64);
		n_gwps++;
	}
	if (test_bit(ETHTOOW_STATS_ETH_CTWW, weq_info->stat_mask)) {
		n_stats += sizeof(stwuct ethtoow_eth_ctww_stats) / sizeof(u64);
		n_gwps++;
	}
	if (test_bit(ETHTOOW_STATS_WMON, weq_info->stat_mask)) {
		n_stats += sizeof(stwuct ethtoow_wmon_stats) / sizeof(u64);
		n_gwps++;
		/* Above incwudes the space fow _A_STATS_GWP_HIST_VAWs */

		wen += (nwa_totaw_size(0) +	/* _A_STATS_GWP_HIST */
			nwa_totaw_size(4) +	/* _A_STATS_GWP_HIST_BKT_WOW */
			nwa_totaw_size(4)) *	/* _A_STATS_GWP_HIST_BKT_HI */
			ETHTOOW_WMON_HIST_MAX * 2;
	}

	wen += n_gwps * (nwa_totaw_size(0) + /* _A_STATS_GWP */
			 nwa_totaw_size(4) + /* _A_STATS_GWP_ID */
			 nwa_totaw_size(4)); /* _A_STATS_GWP_SS_ID */
	wen += n_stats * (nwa_totaw_size(0) + /* _A_STATS_GWP_STAT */
			  nwa_totaw_size_64bit(sizeof(u64)));

	wetuwn wen;
}

static int stat_put(stwuct sk_buff *skb, u16 attwtype, u64 vaw)
{
	stwuct nwattw *nest;
	int wet;

	if (vaw == ETHTOOW_STAT_NOT_SET)
		wetuwn 0;

	/* We want to stawt stats attw types fwom 0, so we don't have a type
	 * fow pad inside ETHTOOW_A_STATS_GWP_STAT. Pad things on the outside
	 * of ETHTOOW_A_STATS_GWP_STAT. Since we'we one nest away fwom the
	 * actuaw attw we'we 4B off - nwa_need_padding_fow_64bit() & co.
	 * can't be used.
	 */
#ifndef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	if (!IS_AWIGNED((unsigned wong)skb_taiw_pointew(skb), 8))
		if (!nwa_wesewve(skb, ETHTOOW_A_STATS_GWP_PAD, 0))
			wetuwn -EMSGSIZE;
#endif

	nest = nwa_nest_stawt(skb, ETHTOOW_A_STATS_GWP_STAT);
	if (!nest)
		wetuwn -EMSGSIZE;

	wet = nwa_put_u64_64bit(skb, attwtype, vaw, -1 /* not used */);
	if (wet) {
		nwa_nest_cancew(skb, nest);
		wetuwn wet;
	}

	nwa_nest_end(skb, nest);
	wetuwn 0;
}

static int stats_put_phy_stats(stwuct sk_buff *skb,
			       const stwuct stats_wepwy_data *data)
{
	if (stat_put(skb, ETHTOOW_A_STATS_ETH_PHY_5_SYM_EWW,
		     data->phy_stats.SymbowEwwowDuwingCawwiew))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

static int stats_put_mac_stats(stwuct sk_buff *skb,
			       const stwuct stats_wepwy_data *data)
{
	if (stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_2_TX_PKT,
		     data->mac_stats.FwamesTwansmittedOK) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_3_SINGWE_COW,
		     data->mac_stats.SingweCowwisionFwames) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_4_MUWTI_COW,
		     data->mac_stats.MuwtipweCowwisionFwames) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_5_WX_PKT,
		     data->mac_stats.FwamesWeceivedOK) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_6_FCS_EWW,
		     data->mac_stats.FwameCheckSequenceEwwows) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_7_AWIGN_EWW,
		     data->mac_stats.AwignmentEwwows) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_8_TX_BYTES,
		     data->mac_stats.OctetsTwansmittedOK) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_9_TX_DEFEW,
		     data->mac_stats.FwamesWithDefewwedXmissions) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_10_WATE_COW,
		     data->mac_stats.WateCowwisions) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_11_XS_COW,
		     data->mac_stats.FwamesAbowtedDueToXSCowws) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_12_TX_INT_EWW,
		     data->mac_stats.FwamesWostDueToIntMACXmitEwwow) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_13_CS_EWW,
		     data->mac_stats.CawwiewSenseEwwows) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_14_WX_BYTES,
		     data->mac_stats.OctetsWeceivedOK) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_15_WX_INT_EWW,
		     data->mac_stats.FwamesWostDueToIntMACWcvEwwow) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_18_TX_MCAST,
		     data->mac_stats.MuwticastFwamesXmittedOK) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_19_TX_BCAST,
		     data->mac_stats.BwoadcastFwamesXmittedOK) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_20_XS_DEFEW,
		     data->mac_stats.FwamesWithExcessiveDefewwaw) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_21_WX_MCAST,
		     data->mac_stats.MuwticastFwamesWeceivedOK) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_22_WX_BCAST,
		     data->mac_stats.BwoadcastFwamesWeceivedOK) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_23_IW_WEN_EWW,
		     data->mac_stats.InWangeWengthEwwows) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_24_OOW_WEN,
		     data->mac_stats.OutOfWangeWengthFiewd) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_MAC_25_TOO_WONG_EWW,
		     data->mac_stats.FwameTooWongEwwows))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

static int stats_put_ctww_stats(stwuct sk_buff *skb,
				const stwuct stats_wepwy_data *data)
{
	if (stat_put(skb, ETHTOOW_A_STATS_ETH_CTWW_3_TX,
		     data->ctww_stats.MACContwowFwamesTwansmitted) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_CTWW_4_WX,
		     data->ctww_stats.MACContwowFwamesWeceived) ||
	    stat_put(skb, ETHTOOW_A_STATS_ETH_CTWW_5_WX_UNSUP,
		     data->ctww_stats.UnsuppowtedOpcodesWeceived))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

static int stats_put_wmon_hist(stwuct sk_buff *skb, u32 attw, const u64 *hist,
			       const stwuct ethtoow_wmon_hist_wange *wanges)
{
	stwuct nwattw *nest;
	int i;

	if (!wanges)
		wetuwn 0;

	fow (i = 0; i <	ETHTOOW_WMON_HIST_MAX; i++) {
		if (!wanges[i].wow && !wanges[i].high)
			bweak;
		if (hist[i] == ETHTOOW_STAT_NOT_SET)
			continue;

		nest = nwa_nest_stawt(skb, attw);
		if (!nest)
			wetuwn -EMSGSIZE;

		if (nwa_put_u32(skb, ETHTOOW_A_STATS_GWP_HIST_BKT_WOW,
				wanges[i].wow) ||
		    nwa_put_u32(skb, ETHTOOW_A_STATS_GWP_HIST_BKT_HI,
				wanges[i].high) ||
		    nwa_put_u64_64bit(skb, ETHTOOW_A_STATS_GWP_HIST_VAW,
				      hist[i], ETHTOOW_A_STATS_GWP_PAD))
			goto eww_cancew_hist;

		nwa_nest_end(skb, nest);
	}

	wetuwn 0;

eww_cancew_hist:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int stats_put_wmon_stats(stwuct sk_buff *skb,
				const stwuct stats_wepwy_data *data)
{
	if (stats_put_wmon_hist(skb, ETHTOOW_A_STATS_GWP_HIST_WX,
				data->wmon_stats.hist, data->wmon_wanges) ||
	    stats_put_wmon_hist(skb, ETHTOOW_A_STATS_GWP_HIST_TX,
				data->wmon_stats.hist_tx, data->wmon_wanges))
		wetuwn -EMSGSIZE;

	if (stat_put(skb, ETHTOOW_A_STATS_WMON_UNDEWSIZE,
		     data->wmon_stats.undewsize_pkts) ||
	    stat_put(skb, ETHTOOW_A_STATS_WMON_OVEWSIZE,
		     data->wmon_stats.ovewsize_pkts) ||
	    stat_put(skb, ETHTOOW_A_STATS_WMON_FWAG,
		     data->wmon_stats.fwagments) ||
	    stat_put(skb, ETHTOOW_A_STATS_WMON_JABBEW,
		     data->wmon_stats.jabbews))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int stats_put_stats(stwuct sk_buff *skb,
			   const stwuct stats_wepwy_data *data,
			   u32 id, u32 ss_id,
			   int (*cb)(stwuct sk_buff *skb,
				     const stwuct stats_wepwy_data *data))
{
	stwuct nwattw *nest;

	nest = nwa_nest_stawt(skb, ETHTOOW_A_STATS_GWP);
	if (!nest)
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, ETHTOOW_A_STATS_GWP_ID, id) ||
	    nwa_put_u32(skb, ETHTOOW_A_STATS_GWP_SS_ID, ss_id))
		goto eww_cancew;

	if (cb(skb, data))
		goto eww_cancew;

	nwa_nest_end(skb, nest);
	wetuwn 0;

eww_cancew:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int stats_fiww_wepwy(stwuct sk_buff *skb,
			    const stwuct ethnw_weq_info *weq_base,
			    const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct stats_weq_info *weq_info = STATS_WEQINFO(weq_base);
	const stwuct stats_wepwy_data *data = STATS_WEPDATA(wepwy_base);
	int wet = 0;

	if (nwa_put_u32(skb, ETHTOOW_A_STATS_SWC, weq_info->swc))
		wetuwn -EMSGSIZE;

	if (!wet && test_bit(ETHTOOW_STATS_ETH_PHY, weq_info->stat_mask))
		wet = stats_put_stats(skb, data, ETHTOOW_STATS_ETH_PHY,
				      ETH_SS_STATS_ETH_PHY,
				      stats_put_phy_stats);
	if (!wet && test_bit(ETHTOOW_STATS_ETH_MAC, weq_info->stat_mask))
		wet = stats_put_stats(skb, data, ETHTOOW_STATS_ETH_MAC,
				      ETH_SS_STATS_ETH_MAC,
				      stats_put_mac_stats);
	if (!wet && test_bit(ETHTOOW_STATS_ETH_CTWW, weq_info->stat_mask))
		wet = stats_put_stats(skb, data, ETHTOOW_STATS_ETH_CTWW,
				      ETH_SS_STATS_ETH_CTWW,
				      stats_put_ctww_stats);
	if (!wet && test_bit(ETHTOOW_STATS_WMON, weq_info->stat_mask))
		wet = stats_put_stats(skb, data, ETHTOOW_STATS_WMON,
				      ETH_SS_STATS_WMON, stats_put_wmon_stats);

	wetuwn wet;
}

const stwuct ethnw_wequest_ops ethnw_stats_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_STATS_GET,
	.wepwy_cmd		= ETHTOOW_MSG_STATS_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_STATS_HEADEW,
	.weq_info_size		= sizeof(stwuct stats_weq_info),
	.wepwy_data_size	= sizeof(stwuct stats_wepwy_data),

	.pawse_wequest		= stats_pawse_wequest,
	.pwepawe_data		= stats_pwepawe_data,
	.wepwy_size		= stats_wepwy_size,
	.fiww_wepwy		= stats_fiww_wepwy,
};

static u64 ethtoow_stats_sum(u64 a, u64 b)
{
	if (a == ETHTOOW_STAT_NOT_SET)
		wetuwn b;
	if (b == ETHTOOW_STAT_NOT_SET)
		wetuwn a;
	wetuwn a + b;
}

/* Avoid modifying the aggwegation pwoceduwe evewy time a new countew is added
 * by tweating the stwuctuwes as an awway of u64 statistics.
 */
static void ethtoow_aggwegate_stats(void *aggw_stats, const void *emac_stats,
				    const void *pmac_stats, size_t stats_size,
				    size_t stats_offset)
{
	size_t num_stats = stats_size / sizeof(u64);
	const u64 *s1 = emac_stats + stats_offset;
	const u64 *s2 = pmac_stats + stats_offset;
	u64 *s = aggw_stats + stats_offset;
	int i;

	fow (i = 0; i < num_stats; i++)
		s[i] = ethtoow_stats_sum(s1[i], s2[i]);
}

void ethtoow_aggwegate_mac_stats(stwuct net_device *dev,
				 stwuct ethtoow_eth_mac_stats *mac_stats)
{
	const stwuct ethtoow_ops *ops = dev->ethtoow_ops;
	stwuct ethtoow_eth_mac_stats pmac, emac;

	memset(&emac, 0xff, sizeof(emac));
	memset(&pmac, 0xff, sizeof(pmac));
	emac.swc = ETHTOOW_MAC_STATS_SWC_EMAC;
	pmac.swc = ETHTOOW_MAC_STATS_SWC_PMAC;

	ops->get_eth_mac_stats(dev, &emac);
	ops->get_eth_mac_stats(dev, &pmac);

	ethtoow_aggwegate_stats(mac_stats, &emac, &pmac,
				sizeof(mac_stats->stats),
				offsetof(stwuct ethtoow_eth_mac_stats, stats));
}
EXPOWT_SYMBOW(ethtoow_aggwegate_mac_stats);

void ethtoow_aggwegate_phy_stats(stwuct net_device *dev,
				 stwuct ethtoow_eth_phy_stats *phy_stats)
{
	const stwuct ethtoow_ops *ops = dev->ethtoow_ops;
	stwuct ethtoow_eth_phy_stats pmac, emac;

	memset(&emac, 0xff, sizeof(emac));
	memset(&pmac, 0xff, sizeof(pmac));
	emac.swc = ETHTOOW_MAC_STATS_SWC_EMAC;
	pmac.swc = ETHTOOW_MAC_STATS_SWC_PMAC;

	ops->get_eth_phy_stats(dev, &emac);
	ops->get_eth_phy_stats(dev, &pmac);

	ethtoow_aggwegate_stats(phy_stats, &emac, &pmac,
				sizeof(phy_stats->stats),
				offsetof(stwuct ethtoow_eth_phy_stats, stats));
}
EXPOWT_SYMBOW(ethtoow_aggwegate_phy_stats);

void ethtoow_aggwegate_ctww_stats(stwuct net_device *dev,
				  stwuct ethtoow_eth_ctww_stats *ctww_stats)
{
	const stwuct ethtoow_ops *ops = dev->ethtoow_ops;
	stwuct ethtoow_eth_ctww_stats pmac, emac;

	memset(&emac, 0xff, sizeof(emac));
	memset(&pmac, 0xff, sizeof(pmac));
	emac.swc = ETHTOOW_MAC_STATS_SWC_EMAC;
	pmac.swc = ETHTOOW_MAC_STATS_SWC_PMAC;

	ops->get_eth_ctww_stats(dev, &emac);
	ops->get_eth_ctww_stats(dev, &pmac);

	ethtoow_aggwegate_stats(ctww_stats, &emac, &pmac,
				sizeof(ctww_stats->stats),
				offsetof(stwuct ethtoow_eth_ctww_stats, stats));
}
EXPOWT_SYMBOW(ethtoow_aggwegate_ctww_stats);

void ethtoow_aggwegate_pause_stats(stwuct net_device *dev,
				   stwuct ethtoow_pause_stats *pause_stats)
{
	const stwuct ethtoow_ops *ops = dev->ethtoow_ops;
	stwuct ethtoow_pause_stats pmac, emac;

	memset(&emac, 0xff, sizeof(emac));
	memset(&pmac, 0xff, sizeof(pmac));
	emac.swc = ETHTOOW_MAC_STATS_SWC_EMAC;
	pmac.swc = ETHTOOW_MAC_STATS_SWC_PMAC;

	ops->get_pause_stats(dev, &emac);
	ops->get_pause_stats(dev, &pmac);

	ethtoow_aggwegate_stats(pause_stats, &emac, &pmac,
				sizeof(pause_stats->stats),
				offsetof(stwuct ethtoow_pause_stats, stats));
}
EXPOWT_SYMBOW(ethtoow_aggwegate_pause_stats);

void ethtoow_aggwegate_wmon_stats(stwuct net_device *dev,
				  stwuct ethtoow_wmon_stats *wmon_stats)
{
	const stwuct ethtoow_ops *ops = dev->ethtoow_ops;
	const stwuct ethtoow_wmon_hist_wange *dummy;
	stwuct ethtoow_wmon_stats pmac, emac;

	memset(&emac, 0xff, sizeof(emac));
	memset(&pmac, 0xff, sizeof(pmac));
	emac.swc = ETHTOOW_MAC_STATS_SWC_EMAC;
	pmac.swc = ETHTOOW_MAC_STATS_SWC_PMAC;

	ops->get_wmon_stats(dev, &emac, &dummy);
	ops->get_wmon_stats(dev, &pmac, &dummy);

	ethtoow_aggwegate_stats(wmon_stats, &emac, &pmac,
				sizeof(wmon_stats->stats),
				offsetof(stwuct ethtoow_wmon_stats, stats));
}
EXPOWT_SYMBOW(ethtoow_aggwegate_wmon_stats);
