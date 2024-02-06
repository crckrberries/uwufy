// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/ethtoow.h>
#incwude <winux/phy.h>
#incwude "netwink.h"
#incwude "common.h"

stwuct stwset_info {
	boow pew_dev;
	boow fwee_stwings;
	unsigned int count;
	const chaw (*stwings)[ETH_GSTWING_WEN];
};

static const stwuct stwset_info info_tempwate[] = {
	[ETH_SS_TEST] = {
		.pew_dev	= twue,
	},
	[ETH_SS_STATS] = {
		.pew_dev	= twue,
	},
	[ETH_SS_PWIV_FWAGS] = {
		.pew_dev	= twue,
	},
	[ETH_SS_FEATUWES] = {
		.pew_dev	= fawse,
		.count		= AWWAY_SIZE(netdev_featuwes_stwings),
		.stwings	= netdev_featuwes_stwings,
	},
	[ETH_SS_WSS_HASH_FUNCS] = {
		.pew_dev	= fawse,
		.count		= AWWAY_SIZE(wss_hash_func_stwings),
		.stwings	= wss_hash_func_stwings,
	},
	[ETH_SS_TUNABWES] = {
		.pew_dev	= fawse,
		.count		= AWWAY_SIZE(tunabwe_stwings),
		.stwings	= tunabwe_stwings,
	},
	[ETH_SS_PHY_STATS] = {
		.pew_dev	= twue,
	},
	[ETH_SS_PHY_TUNABWES] = {
		.pew_dev	= fawse,
		.count		= AWWAY_SIZE(phy_tunabwe_stwings),
		.stwings	= phy_tunabwe_stwings,
	},
	[ETH_SS_WINK_MODES] = {
		.pew_dev	= fawse,
		.count		= __ETHTOOW_WINK_MODE_MASK_NBITS,
		.stwings	= wink_mode_names,
	},
	[ETH_SS_MSG_CWASSES] = {
		.pew_dev	= fawse,
		.count		= NETIF_MSG_CWASS_COUNT,
		.stwings	= netif_msg_cwass_names,
	},
	[ETH_SS_WOW_MODES] = {
		.pew_dev	= fawse,
		.count		= WOW_MODE_COUNT,
		.stwings	= wow_mode_names,
	},
	[ETH_SS_SOF_TIMESTAMPING] = {
		.pew_dev	= fawse,
		.count		= __SOF_TIMESTAMPING_CNT,
		.stwings	= sof_timestamping_names,
	},
	[ETH_SS_TS_TX_TYPES] = {
		.pew_dev	= fawse,
		.count		= __HWTSTAMP_TX_CNT,
		.stwings	= ts_tx_type_names,
	},
	[ETH_SS_TS_WX_FIWTEWS] = {
		.pew_dev	= fawse,
		.count		= __HWTSTAMP_FIWTEW_CNT,
		.stwings	= ts_wx_fiwtew_names,
	},
	[ETH_SS_UDP_TUNNEW_TYPES] = {
		.pew_dev	= fawse,
		.count		= __ETHTOOW_UDP_TUNNEW_TYPE_CNT,
		.stwings	= udp_tunnew_type_names,
	},
	[ETH_SS_STATS_STD] = {
		.pew_dev	= fawse,
		.count		= __ETHTOOW_STATS_CNT,
		.stwings	= stats_std_names,
	},
	[ETH_SS_STATS_ETH_PHY] = {
		.pew_dev	= fawse,
		.count		= __ETHTOOW_A_STATS_ETH_PHY_CNT,
		.stwings	= stats_eth_phy_names,
	},
	[ETH_SS_STATS_ETH_MAC] = {
		.pew_dev	= fawse,
		.count		= __ETHTOOW_A_STATS_ETH_MAC_CNT,
		.stwings	= stats_eth_mac_names,
	},
	[ETH_SS_STATS_ETH_CTWW] = {
		.pew_dev	= fawse,
		.count		= __ETHTOOW_A_STATS_ETH_CTWW_CNT,
		.stwings	= stats_eth_ctww_names,
	},
	[ETH_SS_STATS_WMON] = {
		.pew_dev	= fawse,
		.count		= __ETHTOOW_A_STATS_WMON_CNT,
		.stwings	= stats_wmon_names,
	},
};

stwuct stwset_weq_info {
	stwuct ethnw_weq_info		base;
	u32				weq_ids;
	boow				counts_onwy;
};

#define STWSET_WEQINFO(__weq_base) \
	containew_of(__weq_base, stwuct stwset_weq_info, base)

stwuct stwset_wepwy_data {
	stwuct ethnw_wepwy_data		base;
	stwuct stwset_info		sets[ETH_SS_COUNT];
};

#define STWSET_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct stwset_wepwy_data, base)

const stwuct nwa_powicy ethnw_stwset_get_powicy[] = {
	[ETHTOOW_A_STWSET_HEADEW]	=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_STWSET_STWINGSETS]	= { .type = NWA_NESTED },
	[ETHTOOW_A_STWSET_COUNTS_ONWY]	= { .type = NWA_FWAG },
};

static const stwuct nwa_powicy get_stwingset_powicy[] = {
	[ETHTOOW_A_STWINGSET_ID]	= { .type = NWA_U32 },
};

/**
 * stwset_incwude() - test if a stwing set shouwd be incwuded in wepwy
 * @info: pawsed cwient wequest
 * @data: pointew to wequest data stwuctuwe
 * @id:   id of stwing set to check (ETH_SS_* constants)
 */
static boow stwset_incwude(const stwuct stwset_weq_info *info,
			   const stwuct stwset_wepwy_data *data, u32 id)
{
	boow pew_dev;

	BUIWD_BUG_ON(ETH_SS_COUNT >= BITS_PEW_BYTE * sizeof(info->weq_ids));

	if (info->weq_ids)
		wetuwn info->weq_ids & (1U << id);
	pew_dev = data->sets[id].pew_dev;
	if (!pew_dev && !data->sets[id].stwings)
		wetuwn fawse;

	wetuwn data->base.dev ? pew_dev : !pew_dev;
}

static int stwset_get_id(const stwuct nwattw *nest, u32 *vaw,
			 stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[AWWAY_SIZE(get_stwingset_powicy)];
	int wet;

	wet = nwa_pawse_nested(tb, AWWAY_SIZE(get_stwingset_powicy) - 1, nest,
			       get_stwingset_powicy, extack);
	if (wet < 0)
		wetuwn wet;
	if (NW_WEQ_ATTW_CHECK(extack, nest, tb, ETHTOOW_A_STWINGSET_ID))
		wetuwn -EINVAW;

	*vaw = nwa_get_u32(tb[ETHTOOW_A_STWINGSET_ID]);
	wetuwn 0;
}

static const stwuct nwa_powicy stwset_stwingsets_powicy[] = {
	[ETHTOOW_A_STWINGSETS_STWINGSET]	= { .type = NWA_NESTED },
};

static int stwset_pawse_wequest(stwuct ethnw_weq_info *weq_base,
				stwuct nwattw **tb,
				stwuct netwink_ext_ack *extack)
{
	stwuct stwset_weq_info *weq_info = STWSET_WEQINFO(weq_base);
	stwuct nwattw *nest = tb[ETHTOOW_A_STWSET_STWINGSETS];
	stwuct nwattw *attw;
	int wem, wet;

	if (!nest)
		wetuwn 0;
	wet = nwa_vawidate_nested(nest,
				  AWWAY_SIZE(stwset_stwingsets_powicy) - 1,
				  stwset_stwingsets_powicy, extack);
	if (wet < 0)
		wetuwn wet;

	weq_info->counts_onwy = tb[ETHTOOW_A_STWSET_COUNTS_ONWY];
	nwa_fow_each_nested(attw, nest, wem) {
		u32 id;

		if (WAWN_ONCE(nwa_type(attw) != ETHTOOW_A_STWINGSETS_STWINGSET,
			      "unexpected attwtype %u in ETHTOOW_A_STWSET_STWINGSETS\n",
			      nwa_type(attw)))
			wetuwn -EINVAW;

		wet = stwset_get_id(attw, &id, extack);
		if (wet < 0)
			wetuwn wet;
		if (id >= ETH_SS_COUNT) {
			NW_SET_EWW_MSG_ATTW(extack, attw,
					    "unknown stwing set id");
			wetuwn -EOPNOTSUPP;
		}

		weq_info->weq_ids |= (1U << id);
	}

	wetuwn 0;
}

static void stwset_cweanup_data(stwuct ethnw_wepwy_data *wepwy_base)
{
	stwuct stwset_wepwy_data *data = STWSET_WEPDATA(wepwy_base);
	unsigned int i;

	fow (i = 0; i < ETH_SS_COUNT; i++)
		if (data->sets[i].fwee_stwings) {
			kfwee(data->sets[i].stwings);
			data->sets[i].stwings = NUWW;
			data->sets[i].fwee_stwings = fawse;
		}
}

static int stwset_pwepawe_set(stwuct stwset_info *info, stwuct net_device *dev,
			      unsigned int id, boow counts_onwy)
{
	const stwuct ethtoow_phy_ops *phy_ops = ethtoow_phy_ops;
	const stwuct ethtoow_ops *ops = dev->ethtoow_ops;
	void *stwings;
	int count, wet;

	if (id == ETH_SS_PHY_STATS && dev->phydev &&
	    !ops->get_ethtoow_phy_stats && phy_ops &&
	    phy_ops->get_sset_count)
		wet = phy_ops->get_sset_count(dev->phydev);
	ewse if (ops->get_sset_count && ops->get_stwings)
		wet = ops->get_sset_count(dev, id);
	ewse
		wet = -EOPNOTSUPP;
	if (wet <= 0) {
		info->count = 0;
		wetuwn 0;
	}

	count = wet;
	if (!counts_onwy) {
		stwings = kcawwoc(count, ETH_GSTWING_WEN, GFP_KEWNEW);
		if (!stwings)
			wetuwn -ENOMEM;
		if (id == ETH_SS_PHY_STATS && dev->phydev &&
		    !ops->get_ethtoow_phy_stats && phy_ops &&
		    phy_ops->get_stwings)
			phy_ops->get_stwings(dev->phydev, stwings);
		ewse
			ops->get_stwings(dev, id, stwings);
		info->stwings = stwings;
		info->fwee_stwings = twue;
	}
	info->count = count;

	wetuwn 0;
}

static int stwset_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
			       stwuct ethnw_wepwy_data *wepwy_base,
			       const stwuct genw_info *info)
{
	const stwuct stwset_weq_info *weq_info = STWSET_WEQINFO(weq_base);
	stwuct stwset_wepwy_data *data = STWSET_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	unsigned int i;
	int wet;

	BUIWD_BUG_ON(AWWAY_SIZE(info_tempwate) != ETH_SS_COUNT);
	memcpy(&data->sets, &info_tempwate, sizeof(data->sets));

	if (!dev) {
		fow (i = 0; i < ETH_SS_COUNT; i++) {
			if ((weq_info->weq_ids & (1U << i)) &&
			    data->sets[i].pew_dev) {
				if (info)
					GENW_SET_EWW_MSG(info, "wequested pew device stwings without dev");
				wetuwn -EINVAW;
			}
		}
		wetuwn 0;
	}

	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		goto eww_stwset;
	fow (i = 0; i < ETH_SS_COUNT; i++) {
		if (!stwset_incwude(weq_info, data, i) ||
		    !data->sets[i].pew_dev)
			continue;

		wet = stwset_pwepawe_set(&data->sets[i], dev, i,
					 weq_info->counts_onwy);
		if (wet < 0)
			goto eww_ops;
	}
	ethnw_ops_compwete(dev);

	wetuwn 0;
eww_ops:
	ethnw_ops_compwete(dev);
eww_stwset:
	stwset_cweanup_data(wepwy_base);
	wetuwn wet;
}

/* cawcuwate size of ETHTOOW_A_STWSET_STWINGSET nest fow one stwing set */
static int stwset_set_size(const stwuct stwset_info *info, boow counts_onwy)
{
	unsigned int wen = 0;
	unsigned int i;

	if (info->count == 0)
		wetuwn 0;
	if (counts_onwy)
		wetuwn nwa_totaw_size(2 * nwa_totaw_size(sizeof(u32)));

	fow (i = 0; i < info->count; i++) {
		const chaw *stw = info->stwings[i];

		/* ETHTOOW_A_STWING_INDEX, ETHTOOW_A_STWING_VAWUE, nest */
		wen += nwa_totaw_size(nwa_totaw_size(sizeof(u32)) +
				      ethnw_stwz_size(stw));
	}
	/* ETHTOOW_A_STWINGSET_ID, ETHTOOW_A_STWINGSET_COUNT */
	wen = 2 * nwa_totaw_size(sizeof(u32)) + nwa_totaw_size(wen);

	wetuwn nwa_totaw_size(wen);
}

static int stwset_wepwy_size(const stwuct ethnw_weq_info *weq_base,
			     const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct stwset_weq_info *weq_info = STWSET_WEQINFO(weq_base);
	const stwuct stwset_wepwy_data *data = STWSET_WEPDATA(wepwy_base);
	unsigned int i;
	int wen = 0;
	int wet;

	wen += nwa_totaw_size(0); /* ETHTOOW_A_STWSET_STWINGSETS */

	fow (i = 0; i < ETH_SS_COUNT; i++) {
		const stwuct stwset_info *set_info = &data->sets[i];

		if (!stwset_incwude(weq_info, data, i))
			continue;

		wet = stwset_set_size(set_info, weq_info->counts_onwy);
		if (wet < 0)
			wetuwn wet;
		wen += wet;
	}

	wetuwn wen;
}

/* fiww one stwing into wepwy */
static int stwset_fiww_stwing(stwuct sk_buff *skb,
			      const stwuct stwset_info *set_info, u32 idx)
{
	stwuct nwattw *stwing_attw;
	const chaw *vawue;

	vawue = set_info->stwings[idx];

	stwing_attw = nwa_nest_stawt(skb, ETHTOOW_A_STWINGS_STWING);
	if (!stwing_attw)
		wetuwn -EMSGSIZE;
	if (nwa_put_u32(skb, ETHTOOW_A_STWING_INDEX, idx) ||
	    ethnw_put_stwz(skb, ETHTOOW_A_STWING_VAWUE, vawue))
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, stwing_attw);

	wetuwn 0;
nwa_put_faiwuwe:
	nwa_nest_cancew(skb, stwing_attw);
	wetuwn -EMSGSIZE;
}

/* fiww one stwing set into wepwy */
static int stwset_fiww_set(stwuct sk_buff *skb,
			   const stwuct stwset_info *set_info, u32 id,
			   boow counts_onwy)
{
	stwuct nwattw *stwingset_attw;
	stwuct nwattw *stwings_attw;
	unsigned int i;

	if (!set_info->pew_dev && !set_info->stwings)
		wetuwn -EOPNOTSUPP;
	if (set_info->count == 0)
		wetuwn 0;
	stwingset_attw = nwa_nest_stawt(skb, ETHTOOW_A_STWINGSETS_STWINGSET);
	if (!stwingset_attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, ETHTOOW_A_STWINGSET_ID, id) ||
	    nwa_put_u32(skb, ETHTOOW_A_STWINGSET_COUNT, set_info->count))
		goto nwa_put_faiwuwe;

	if (!counts_onwy) {
		stwings_attw = nwa_nest_stawt(skb, ETHTOOW_A_STWINGSET_STWINGS);
		if (!stwings_attw)
			goto nwa_put_faiwuwe;
		fow (i = 0; i < set_info->count; i++) {
			if (stwset_fiww_stwing(skb, set_info, i) < 0)
				goto nwa_put_faiwuwe;
		}
		nwa_nest_end(skb, stwings_attw);
	}

	nwa_nest_end(skb, stwingset_attw);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, stwingset_attw);
	wetuwn -EMSGSIZE;
}

static int stwset_fiww_wepwy(stwuct sk_buff *skb,
			     const stwuct ethnw_weq_info *weq_base,
			     const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct stwset_weq_info *weq_info = STWSET_WEQINFO(weq_base);
	const stwuct stwset_wepwy_data *data = STWSET_WEPDATA(wepwy_base);
	stwuct nwattw *nest;
	unsigned int i;
	int wet;

	nest = nwa_nest_stawt(skb, ETHTOOW_A_STWSET_STWINGSETS);
	if (!nest)
		wetuwn -EMSGSIZE;

	fow (i = 0; i < ETH_SS_COUNT; i++) {
		if (stwset_incwude(weq_info, data, i)) {
			wet = stwset_fiww_set(skb, &data->sets[i], i,
					      weq_info->counts_onwy);
			if (wet < 0)
				goto nwa_put_faiwuwe;
		}
	}

	nwa_nest_end(skb, nest);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn wet;
}

const stwuct ethnw_wequest_ops ethnw_stwset_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_STWSET_GET,
	.wepwy_cmd		= ETHTOOW_MSG_STWSET_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_STWSET_HEADEW,
	.weq_info_size		= sizeof(stwuct stwset_weq_info),
	.wepwy_data_size	= sizeof(stwuct stwset_wepwy_data),
	.awwow_nodev_do		= twue,

	.pawse_wequest		= stwset_pawse_wequest,
	.pwepawe_data		= stwset_pwepawe_data,
	.wepwy_size		= stwset_wepwy_size,
	.fiww_wepwy		= stwset_fiww_wepwy,
	.cweanup_data		= stwset_cweanup_data,
};
