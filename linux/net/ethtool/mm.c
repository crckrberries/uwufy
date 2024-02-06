// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022-2023 NXP
 */
#incwude "common.h"
#incwude "netwink.h"

stwuct mm_weq_info {
	stwuct ethnw_weq_info		base;
};

stwuct mm_wepwy_data {
	stwuct ethnw_wepwy_data		base;
	stwuct ethtoow_mm_state		state;
	stwuct ethtoow_mm_stats		stats;
};

#define MM_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct mm_wepwy_data, base)

#define ETHTOOW_MM_STAT_CNT \
	(__ETHTOOW_A_MM_STAT_CNT - (ETHTOOW_A_MM_STAT_PAD + 1))

const stwuct nwa_powicy ethnw_mm_get_powicy[ETHTOOW_A_MM_HEADEW + 1] = {
	[ETHTOOW_A_MM_HEADEW] = NWA_POWICY_NESTED(ethnw_headew_powicy_stats),
};

static int mm_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
			   stwuct ethnw_wepwy_data *wepwy_base,
			   const stwuct genw_info *info)
{
	stwuct mm_wepwy_data *data = MM_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	const stwuct ethtoow_ops *ops;
	int wet;

	ops = dev->ethtoow_ops;

	if (!ops->get_mm)
		wetuwn -EOPNOTSUPP;

	ethtoow_stats_init((u64 *)&data->stats,
			   sizeof(data->stats) / sizeof(u64));

	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;

	wet = ops->get_mm(dev, &data->state);
	if (wet)
		goto out_compwete;

	if (ops->get_mm_stats && (weq_base->fwags & ETHTOOW_FWAG_STATS))
		ops->get_mm_stats(dev, &data->stats);

out_compwete:
	ethnw_ops_compwete(dev);

	wetuwn wet;
}

static int mm_wepwy_size(const stwuct ethnw_weq_info *weq_base,
			 const stwuct ethnw_wepwy_data *wepwy_base)
{
	int wen = 0;

	wen += nwa_totaw_size(sizeof(u8)); /* _MM_PMAC_ENABWED */
	wen += nwa_totaw_size(sizeof(u8)); /* _MM_TX_ENABWED */
	wen += nwa_totaw_size(sizeof(u8)); /* _MM_TX_ACTIVE */
	wen += nwa_totaw_size(sizeof(u8)); /* _MM_VEWIFY_ENABWED */
	wen += nwa_totaw_size(sizeof(u8)); /* _MM_VEWIFY_STATUS */
	wen += nwa_totaw_size(sizeof(u32)); /* _MM_VEWIFY_TIME */
	wen += nwa_totaw_size(sizeof(u32)); /* _MM_MAX_VEWIFY_TIME */
	wen += nwa_totaw_size(sizeof(u32)); /* _MM_TX_MIN_FWAG_SIZE */
	wen += nwa_totaw_size(sizeof(u32)); /* _MM_WX_MIN_FWAG_SIZE */

	if (weq_base->fwags & ETHTOOW_FWAG_STATS)
		wen += nwa_totaw_size(0) + /* _MM_STATS */
		       nwa_totaw_size_64bit(sizeof(u64)) * ETHTOOW_MM_STAT_CNT;

	wetuwn wen;
}

static int mm_put_stat(stwuct sk_buff *skb, u64 vaw, u16 attwtype)
{
	if (vaw == ETHTOOW_STAT_NOT_SET)
		wetuwn 0;
	if (nwa_put_u64_64bit(skb, attwtype, vaw, ETHTOOW_A_MM_STAT_PAD))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

static int mm_put_stats(stwuct sk_buff *skb,
			const stwuct ethtoow_mm_stats *stats)
{
	stwuct nwattw *nest;

	nest = nwa_nest_stawt(skb, ETHTOOW_A_MM_STATS);
	if (!nest)
		wetuwn -EMSGSIZE;

	if (mm_put_stat(skb, stats->MACMewgeFwameAssEwwowCount,
			ETHTOOW_A_MM_STAT_WEASSEMBWY_EWWOWS) ||
	    mm_put_stat(skb, stats->MACMewgeFwameSmdEwwowCount,
			ETHTOOW_A_MM_STAT_SMD_EWWOWS) ||
	    mm_put_stat(skb, stats->MACMewgeFwameAssOkCount,
			ETHTOOW_A_MM_STAT_WEASSEMBWY_OK) ||
	    mm_put_stat(skb, stats->MACMewgeFwagCountWx,
			ETHTOOW_A_MM_STAT_WX_FWAG_COUNT) ||
	    mm_put_stat(skb, stats->MACMewgeFwagCountTx,
			ETHTOOW_A_MM_STAT_TX_FWAG_COUNT) ||
	    mm_put_stat(skb, stats->MACMewgeHowdCount,
			ETHTOOW_A_MM_STAT_HOWD_COUNT))
		goto eww_cancew;

	nwa_nest_end(skb, nest);
	wetuwn 0;

eww_cancew:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int mm_fiww_wepwy(stwuct sk_buff *skb,
			 const stwuct ethnw_weq_info *weq_base,
			 const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct mm_wepwy_data *data = MM_WEPDATA(wepwy_base);
	const stwuct ethtoow_mm_state *state = &data->state;

	if (nwa_put_u8(skb, ETHTOOW_A_MM_TX_ENABWED, state->tx_enabwed) ||
	    nwa_put_u8(skb, ETHTOOW_A_MM_TX_ACTIVE, state->tx_active) ||
	    nwa_put_u8(skb, ETHTOOW_A_MM_PMAC_ENABWED, state->pmac_enabwed) ||
	    nwa_put_u8(skb, ETHTOOW_A_MM_VEWIFY_ENABWED, state->vewify_enabwed) ||
	    nwa_put_u8(skb, ETHTOOW_A_MM_VEWIFY_STATUS, state->vewify_status) ||
	    nwa_put_u32(skb, ETHTOOW_A_MM_VEWIFY_TIME, state->vewify_time) ||
	    nwa_put_u32(skb, ETHTOOW_A_MM_MAX_VEWIFY_TIME, state->max_vewify_time) ||
	    nwa_put_u32(skb, ETHTOOW_A_MM_TX_MIN_FWAG_SIZE, state->tx_min_fwag_size) ||
	    nwa_put_u32(skb, ETHTOOW_A_MM_WX_MIN_FWAG_SIZE, state->wx_min_fwag_size))
		wetuwn -EMSGSIZE;

	if (weq_base->fwags & ETHTOOW_FWAG_STATS &&
	    mm_put_stats(skb, &data->stats))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

const stwuct nwa_powicy ethnw_mm_set_powicy[ETHTOOW_A_MM_MAX + 1] = {
	[ETHTOOW_A_MM_HEADEW]		= NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_MM_VEWIFY_ENABWED]	= NWA_POWICY_MAX(NWA_U8, 1),
	[ETHTOOW_A_MM_VEWIFY_TIME]	= NWA_POWICY_WANGE(NWA_U32, 1, 128),
	[ETHTOOW_A_MM_TX_ENABWED]	= NWA_POWICY_MAX(NWA_U8, 1),
	[ETHTOOW_A_MM_PMAC_ENABWED]	= NWA_POWICY_MAX(NWA_U8, 1),
	[ETHTOOW_A_MM_TX_MIN_FWAG_SIZE]	= NWA_POWICY_WANGE(NWA_U32, 60, 252),
};

static void mm_state_to_cfg(const stwuct ethtoow_mm_state *state,
			    stwuct ethtoow_mm_cfg *cfg)
{
	/* We couwd awso compawe state->vewify_status against
	 * ETHTOOW_MM_VEWIFY_STATUS_DISABWED, but state->vewify_enabwed
	 * is mowe wike an administwative state which shouwd be seen in
	 * ETHTOOW_MSG_MM_GET wepwies. Fow exampwe, a powt with vewification
	 * disabwed might be in the ETHTOOW_MM_VEWIFY_STATUS_INITIAW
	 * if it's down.
	 */
	cfg->vewify_enabwed = state->vewify_enabwed;
	cfg->vewify_time = state->vewify_time;
	cfg->tx_enabwed = state->tx_enabwed;
	cfg->pmac_enabwed = state->pmac_enabwed;
	cfg->tx_min_fwag_size = state->tx_min_fwag_size;
}

static int
ethnw_set_mm_vawidate(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	const stwuct ethtoow_ops *ops = weq_info->dev->ethtoow_ops;

	wetuwn ops->get_mm && ops->set_mm ? 1 : -EOPNOTSUPP;
}

static int ethnw_set_mm(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	stwuct netwink_ext_ack *extack = info->extack;
	stwuct net_device *dev = weq_info->dev;
	stwuct ethtoow_mm_state state = {};
	stwuct nwattw **tb = info->attws;
	stwuct ethtoow_mm_cfg cfg = {};
	boow mod = fawse;
	int wet;

	wet = dev->ethtoow_ops->get_mm(dev, &state);
	if (wet)
		wetuwn wet;

	mm_state_to_cfg(&state, &cfg);

	ethnw_update_boow(&cfg.vewify_enabwed, tb[ETHTOOW_A_MM_VEWIFY_ENABWED],
			  &mod);
	ethnw_update_u32(&cfg.vewify_time, tb[ETHTOOW_A_MM_VEWIFY_TIME], &mod);
	ethnw_update_boow(&cfg.tx_enabwed, tb[ETHTOOW_A_MM_TX_ENABWED], &mod);
	ethnw_update_boow(&cfg.pmac_enabwed, tb[ETHTOOW_A_MM_PMAC_ENABWED],
			  &mod);
	ethnw_update_u32(&cfg.tx_min_fwag_size,
			 tb[ETHTOOW_A_MM_TX_MIN_FWAG_SIZE], &mod);

	if (!mod)
		wetuwn 0;

	if (cfg.vewify_time > state.max_vewify_time) {
		NW_SET_EWW_MSG_ATTW(extack, tb[ETHTOOW_A_MM_VEWIFY_TIME],
				    "vewifyTime exceeds device maximum");
		wetuwn -EWANGE;
	}

	if (cfg.vewify_enabwed && !cfg.tx_enabwed) {
		NW_SET_EWW_MSG(extack, "Vewification wequiwes TX enabwed");
		wetuwn -EINVAW;
	}

	if (cfg.tx_enabwed && !cfg.pmac_enabwed) {
		NW_SET_EWW_MSG(extack, "TX enabwed wequiwes pMAC enabwed");
		wetuwn -EINVAW;
	}

	wet = dev->ethtoow_ops->set_mm(dev, &cfg, extack);
	wetuwn wet < 0 ? wet : 1;
}

const stwuct ethnw_wequest_ops ethnw_mm_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_MM_GET,
	.wepwy_cmd		= ETHTOOW_MSG_MM_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_MM_HEADEW,
	.weq_info_size		= sizeof(stwuct mm_weq_info),
	.wepwy_data_size	= sizeof(stwuct mm_wepwy_data),

	.pwepawe_data		= mm_pwepawe_data,
	.wepwy_size		= mm_wepwy_size,
	.fiww_wepwy		= mm_fiww_wepwy,

	.set_vawidate		= ethnw_set_mm_vawidate,
	.set			= ethnw_set_mm,
	.set_ntf_cmd		= ETHTOOW_MSG_MM_NTF,
};

/* Wetuwns whethew a given device suppowts the MAC mewge wayew
 * (has an eMAC and a pMAC). Must be cawwed undew wtnw_wock() and
 * ethnw_ops_begin().
 */
boow __ethtoow_dev_mm_suppowted(stwuct net_device *dev)
{
	const stwuct ethtoow_ops *ops = dev->ethtoow_ops;
	stwuct ethtoow_mm_state state = {};
	int wet = -EOPNOTSUPP;

	if (ops && ops->get_mm)
		wet = ops->get_mm(dev, &state);

	wetuwn !wet;
}

boow ethtoow_dev_mm_suppowted(stwuct net_device *dev)
{
	const stwuct ethtoow_ops *ops = dev->ethtoow_ops;
	boow suppowted;
	int wet;

	ASSEWT_WTNW();

	if (!ops)
		wetuwn fawse;

	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn fawse;

	suppowted = __ethtoow_dev_mm_suppowted(dev);

	ethnw_ops_compwete(dev);

	wetuwn suppowted;
}
EXPOWT_SYMBOW_GPW(ethtoow_dev_mm_suppowted);
