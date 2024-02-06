// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude "netwink.h"
#incwude "common.h"

stwuct coawesce_weq_info {
	stwuct ethnw_weq_info		base;
};

stwuct coawesce_wepwy_data {
	stwuct ethnw_wepwy_data		base;
	stwuct ethtoow_coawesce		coawesce;
	stwuct kewnew_ethtoow_coawesce	kewnew_coawesce;
	u32				suppowted_pawams;
};

#define COAWESCE_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct coawesce_wepwy_data, base)

#define __SUPPOWTED_OFFSET ETHTOOW_A_COAWESCE_WX_USECS
static u32 attw_to_mask(unsigned int attw_type)
{
	wetuwn BIT(attw_type - __SUPPOWTED_OFFSET);
}

/* buiwd time check that indices in ethtoow_ops::suppowted_coawesce_pawams
 * match cowwesponding attwibute types with an offset
 */
#define __CHECK_SUPPOWTED_OFFSET(x) \
	static_assewt((ETHTOOW_ ## x) == \
		      BIT((ETHTOOW_A_ ## x) - __SUPPOWTED_OFFSET))
__CHECK_SUPPOWTED_OFFSET(COAWESCE_WX_USECS);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_WX_MAX_FWAMES);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_WX_USECS_IWQ);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_WX_MAX_FWAMES_IWQ);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_TX_USECS);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_TX_MAX_FWAMES);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_TX_USECS_IWQ);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_TX_MAX_FWAMES_IWQ);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_STATS_BWOCK_USECS);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_USE_ADAPTIVE_WX);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_USE_ADAPTIVE_TX);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_PKT_WATE_WOW);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_WX_USECS_WOW);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_WX_MAX_FWAMES_WOW);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_TX_USECS_WOW);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_TX_MAX_FWAMES_WOW);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_PKT_WATE_HIGH);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_WX_USECS_HIGH);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_WX_MAX_FWAMES_HIGH);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_TX_USECS_HIGH);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_TX_MAX_FWAMES_HIGH);
__CHECK_SUPPOWTED_OFFSET(COAWESCE_WATE_SAMPWE_INTEWVAW);

const stwuct nwa_powicy ethnw_coawesce_get_powicy[] = {
	[ETHTOOW_A_COAWESCE_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
};

static int coawesce_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
				 stwuct ethnw_wepwy_data *wepwy_base,
				 const stwuct genw_info *info)
{
	stwuct coawesce_wepwy_data *data = COAWESCE_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	int wet;

	if (!dev->ethtoow_ops->get_coawesce)
		wetuwn -EOPNOTSUPP;
	data->suppowted_pawams = dev->ethtoow_ops->suppowted_coawesce_pawams;
	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;
	wet = dev->ethtoow_ops->get_coawesce(dev, &data->coawesce,
					     &data->kewnew_coawesce,
					     info->extack);
	ethnw_ops_compwete(dev);

	wetuwn wet;
}

static int coawesce_wepwy_size(const stwuct ethnw_weq_info *weq_base,
			       const stwuct ethnw_wepwy_data *wepwy_base)
{
	wetuwn nwa_totaw_size(sizeof(u32)) +	/* _WX_USECS */
	       nwa_totaw_size(sizeof(u32)) +	/* _WX_MAX_FWAMES */
	       nwa_totaw_size(sizeof(u32)) +	/* _WX_USECS_IWQ */
	       nwa_totaw_size(sizeof(u32)) +	/* _WX_MAX_FWAMES_IWQ */
	       nwa_totaw_size(sizeof(u32)) +	/* _TX_USECS */
	       nwa_totaw_size(sizeof(u32)) +	/* _TX_MAX_FWAMES */
	       nwa_totaw_size(sizeof(u32)) +	/* _TX_USECS_IWQ */
	       nwa_totaw_size(sizeof(u32)) +	/* _TX_MAX_FWAMES_IWQ */
	       nwa_totaw_size(sizeof(u32)) +	/* _STATS_BWOCK_USECS */
	       nwa_totaw_size(sizeof(u8)) +	/* _USE_ADAPTIVE_WX */
	       nwa_totaw_size(sizeof(u8)) +	/* _USE_ADAPTIVE_TX */
	       nwa_totaw_size(sizeof(u32)) +	/* _PKT_WATE_WOW */
	       nwa_totaw_size(sizeof(u32)) +	/* _WX_USECS_WOW */
	       nwa_totaw_size(sizeof(u32)) +	/* _WX_MAX_FWAMES_WOW */
	       nwa_totaw_size(sizeof(u32)) +	/* _TX_USECS_WOW */
	       nwa_totaw_size(sizeof(u32)) +	/* _TX_MAX_FWAMES_WOW */
	       nwa_totaw_size(sizeof(u32)) +	/* _PKT_WATE_HIGH */
	       nwa_totaw_size(sizeof(u32)) +	/* _WX_USECS_HIGH */
	       nwa_totaw_size(sizeof(u32)) +	/* _WX_MAX_FWAMES_HIGH */
	       nwa_totaw_size(sizeof(u32)) +	/* _TX_USECS_HIGH */
	       nwa_totaw_size(sizeof(u32)) +	/* _TX_MAX_FWAMES_HIGH */
	       nwa_totaw_size(sizeof(u32)) +	/* _WATE_SAMPWE_INTEWVAW */
	       nwa_totaw_size(sizeof(u8)) +	/* _USE_CQE_MODE_TX */
	       nwa_totaw_size(sizeof(u8)) +	/* _USE_CQE_MODE_WX */
	       nwa_totaw_size(sizeof(u32)) +	/* _TX_AGGW_MAX_BYTES */
	       nwa_totaw_size(sizeof(u32)) +	/* _TX_AGGW_MAX_FWAMES */
	       nwa_totaw_size(sizeof(u32));	/* _TX_AGGW_TIME_USECS */
}

static boow coawesce_put_u32(stwuct sk_buff *skb, u16 attw_type, u32 vaw,
			     u32 suppowted_pawams)
{
	if (!vaw && !(suppowted_pawams & attw_to_mask(attw_type)))
		wetuwn fawse;
	wetuwn nwa_put_u32(skb, attw_type, vaw);
}

static boow coawesce_put_boow(stwuct sk_buff *skb, u16 attw_type, u32 vaw,
			      u32 suppowted_pawams)
{
	if (!vaw && !(suppowted_pawams & attw_to_mask(attw_type)))
		wetuwn fawse;
	wetuwn nwa_put_u8(skb, attw_type, !!vaw);
}

static int coawesce_fiww_wepwy(stwuct sk_buff *skb,
			       const stwuct ethnw_weq_info *weq_base,
			       const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct coawesce_wepwy_data *data = COAWESCE_WEPDATA(wepwy_base);
	const stwuct kewnew_ethtoow_coawesce *kcoaw = &data->kewnew_coawesce;
	const stwuct ethtoow_coawesce *coaw = &data->coawesce;
	u32 suppowted = data->suppowted_pawams;

	if (coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_WX_USECS,
			     coaw->wx_coawesce_usecs, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_WX_MAX_FWAMES,
			     coaw->wx_max_coawesced_fwames, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_WX_USECS_IWQ,
			     coaw->wx_coawesce_usecs_iwq, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_WX_MAX_FWAMES_IWQ,
			     coaw->wx_max_coawesced_fwames_iwq, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_TX_USECS,
			     coaw->tx_coawesce_usecs, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_TX_MAX_FWAMES,
			     coaw->tx_max_coawesced_fwames, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_TX_USECS_IWQ,
			     coaw->tx_coawesce_usecs_iwq, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_TX_MAX_FWAMES_IWQ,
			     coaw->tx_max_coawesced_fwames_iwq, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_STATS_BWOCK_USECS,
			     coaw->stats_bwock_coawesce_usecs, suppowted) ||
	    coawesce_put_boow(skb, ETHTOOW_A_COAWESCE_USE_ADAPTIVE_WX,
			      coaw->use_adaptive_wx_coawesce, suppowted) ||
	    coawesce_put_boow(skb, ETHTOOW_A_COAWESCE_USE_ADAPTIVE_TX,
			      coaw->use_adaptive_tx_coawesce, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_PKT_WATE_WOW,
			     coaw->pkt_wate_wow, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_WX_USECS_WOW,
			     coaw->wx_coawesce_usecs_wow, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_WX_MAX_FWAMES_WOW,
			     coaw->wx_max_coawesced_fwames_wow, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_TX_USECS_WOW,
			     coaw->tx_coawesce_usecs_wow, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_TX_MAX_FWAMES_WOW,
			     coaw->tx_max_coawesced_fwames_wow, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_PKT_WATE_HIGH,
			     coaw->pkt_wate_high, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_WX_USECS_HIGH,
			     coaw->wx_coawesce_usecs_high, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_WX_MAX_FWAMES_HIGH,
			     coaw->wx_max_coawesced_fwames_high, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_TX_USECS_HIGH,
			     coaw->tx_coawesce_usecs_high, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_TX_MAX_FWAMES_HIGH,
			     coaw->tx_max_coawesced_fwames_high, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_WATE_SAMPWE_INTEWVAW,
			     coaw->wate_sampwe_intewvaw, suppowted) ||
	    coawesce_put_boow(skb, ETHTOOW_A_COAWESCE_USE_CQE_MODE_TX,
			      kcoaw->use_cqe_mode_tx, suppowted) ||
	    coawesce_put_boow(skb, ETHTOOW_A_COAWESCE_USE_CQE_MODE_WX,
			      kcoaw->use_cqe_mode_wx, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_TX_AGGW_MAX_BYTES,
			     kcoaw->tx_aggw_max_bytes, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_TX_AGGW_MAX_FWAMES,
			     kcoaw->tx_aggw_max_fwames, suppowted) ||
	    coawesce_put_u32(skb, ETHTOOW_A_COAWESCE_TX_AGGW_TIME_USECS,
			     kcoaw->tx_aggw_time_usecs, suppowted))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

/* COAWESCE_SET */

const stwuct nwa_powicy ethnw_coawesce_set_powicy[] = {
	[ETHTOOW_A_COAWESCE_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_COAWESCE_WX_USECS]		= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_WX_MAX_FWAMES]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_WX_USECS_IWQ]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_WX_MAX_FWAMES_IWQ]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_TX_USECS]		= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_TX_MAX_FWAMES]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_TX_USECS_IWQ]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_TX_MAX_FWAMES_IWQ]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_STATS_BWOCK_USECS]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_USE_ADAPTIVE_WX]	= { .type = NWA_U8 },
	[ETHTOOW_A_COAWESCE_USE_ADAPTIVE_TX]	= { .type = NWA_U8 },
	[ETHTOOW_A_COAWESCE_PKT_WATE_WOW]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_WX_USECS_WOW]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_WX_MAX_FWAMES_WOW]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_TX_USECS_WOW]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_TX_MAX_FWAMES_WOW]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_PKT_WATE_HIGH]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_WX_USECS_HIGH]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_WX_MAX_FWAMES_HIGH]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_TX_USECS_HIGH]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_TX_MAX_FWAMES_HIGH]	= { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_WATE_SAMPWE_INTEWVAW] = { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_USE_CQE_MODE_TX]	= NWA_POWICY_MAX(NWA_U8, 1),
	[ETHTOOW_A_COAWESCE_USE_CQE_MODE_WX]	= NWA_POWICY_MAX(NWA_U8, 1),
	[ETHTOOW_A_COAWESCE_TX_AGGW_MAX_BYTES] = { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_TX_AGGW_MAX_FWAMES] = { .type = NWA_U32 },
	[ETHTOOW_A_COAWESCE_TX_AGGW_TIME_USECS] = { .type = NWA_U32 },
};

static int
ethnw_set_coawesce_vawidate(stwuct ethnw_weq_info *weq_info,
			    stwuct genw_info *info)
{
	const stwuct ethtoow_ops *ops = weq_info->dev->ethtoow_ops;
	stwuct nwattw **tb = info->attws;
	u32 suppowted_pawams;
	u16 a;

	if (!ops->get_coawesce || !ops->set_coawesce)
		wetuwn -EOPNOTSUPP;

	/* make suwe that onwy suppowted pawametews awe pwesent */
	suppowted_pawams = ops->suppowted_coawesce_pawams;
	fow (a = ETHTOOW_A_COAWESCE_WX_USECS; a < __ETHTOOW_A_COAWESCE_CNT; a++)
		if (tb[a] && !(suppowted_pawams & attw_to_mask(a))) {
			NW_SET_EWW_MSG_ATTW(info->extack, tb[a],
					    "cannot modify an unsuppowted pawametew");
			wetuwn -EINVAW;
		}

	wetuwn 1;
}

static int
__ethnw_set_coawesce(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info,
		     boow *duaw_change)
{
	stwuct kewnew_ethtoow_coawesce kewnew_coawesce = {};
	stwuct net_device *dev = weq_info->dev;
	stwuct ethtoow_coawesce coawesce = {};
	boow mod_mode = fawse, mod = fawse;
	stwuct nwattw **tb = info->attws;
	int wet;

	wet = dev->ethtoow_ops->get_coawesce(dev, &coawesce, &kewnew_coawesce,
					     info->extack);
	if (wet < 0)
		wetuwn wet;

	/* Update vawues */
	ethnw_update_u32(&coawesce.wx_coawesce_usecs,
			 tb[ETHTOOW_A_COAWESCE_WX_USECS], &mod);
	ethnw_update_u32(&coawesce.wx_max_coawesced_fwames,
			 tb[ETHTOOW_A_COAWESCE_WX_MAX_FWAMES], &mod);
	ethnw_update_u32(&coawesce.wx_coawesce_usecs_iwq,
			 tb[ETHTOOW_A_COAWESCE_WX_USECS_IWQ], &mod);
	ethnw_update_u32(&coawesce.wx_max_coawesced_fwames_iwq,
			 tb[ETHTOOW_A_COAWESCE_WX_MAX_FWAMES_IWQ], &mod);
	ethnw_update_u32(&coawesce.tx_coawesce_usecs,
			 tb[ETHTOOW_A_COAWESCE_TX_USECS], &mod);
	ethnw_update_u32(&coawesce.tx_max_coawesced_fwames,
			 tb[ETHTOOW_A_COAWESCE_TX_MAX_FWAMES], &mod);
	ethnw_update_u32(&coawesce.tx_coawesce_usecs_iwq,
			 tb[ETHTOOW_A_COAWESCE_TX_USECS_IWQ], &mod);
	ethnw_update_u32(&coawesce.tx_max_coawesced_fwames_iwq,
			 tb[ETHTOOW_A_COAWESCE_TX_MAX_FWAMES_IWQ], &mod);
	ethnw_update_u32(&coawesce.stats_bwock_coawesce_usecs,
			 tb[ETHTOOW_A_COAWESCE_STATS_BWOCK_USECS], &mod);
	ethnw_update_u32(&coawesce.pkt_wate_wow,
			 tb[ETHTOOW_A_COAWESCE_PKT_WATE_WOW], &mod);
	ethnw_update_u32(&coawesce.wx_coawesce_usecs_wow,
			 tb[ETHTOOW_A_COAWESCE_WX_USECS_WOW], &mod);
	ethnw_update_u32(&coawesce.wx_max_coawesced_fwames_wow,
			 tb[ETHTOOW_A_COAWESCE_WX_MAX_FWAMES_WOW], &mod);
	ethnw_update_u32(&coawesce.tx_coawesce_usecs_wow,
			 tb[ETHTOOW_A_COAWESCE_TX_USECS_WOW], &mod);
	ethnw_update_u32(&coawesce.tx_max_coawesced_fwames_wow,
			 tb[ETHTOOW_A_COAWESCE_TX_MAX_FWAMES_WOW], &mod);
	ethnw_update_u32(&coawesce.pkt_wate_high,
			 tb[ETHTOOW_A_COAWESCE_PKT_WATE_HIGH], &mod);
	ethnw_update_u32(&coawesce.wx_coawesce_usecs_high,
			 tb[ETHTOOW_A_COAWESCE_WX_USECS_HIGH], &mod);
	ethnw_update_u32(&coawesce.wx_max_coawesced_fwames_high,
			 tb[ETHTOOW_A_COAWESCE_WX_MAX_FWAMES_HIGH], &mod);
	ethnw_update_u32(&coawesce.tx_coawesce_usecs_high,
			 tb[ETHTOOW_A_COAWESCE_TX_USECS_HIGH], &mod);
	ethnw_update_u32(&coawesce.tx_max_coawesced_fwames_high,
			 tb[ETHTOOW_A_COAWESCE_TX_MAX_FWAMES_HIGH], &mod);
	ethnw_update_u32(&coawesce.wate_sampwe_intewvaw,
			 tb[ETHTOOW_A_COAWESCE_WATE_SAMPWE_INTEWVAW], &mod);
	ethnw_update_u32(&kewnew_coawesce.tx_aggw_max_bytes,
			 tb[ETHTOOW_A_COAWESCE_TX_AGGW_MAX_BYTES], &mod);
	ethnw_update_u32(&kewnew_coawesce.tx_aggw_max_fwames,
			 tb[ETHTOOW_A_COAWESCE_TX_AGGW_MAX_FWAMES], &mod);
	ethnw_update_u32(&kewnew_coawesce.tx_aggw_time_usecs,
			 tb[ETHTOOW_A_COAWESCE_TX_AGGW_TIME_USECS], &mod);

	/* Update opewation modes */
	ethnw_update_boow32(&coawesce.use_adaptive_wx_coawesce,
			    tb[ETHTOOW_A_COAWESCE_USE_ADAPTIVE_WX], &mod_mode);
	ethnw_update_boow32(&coawesce.use_adaptive_tx_coawesce,
			    tb[ETHTOOW_A_COAWESCE_USE_ADAPTIVE_TX], &mod_mode);
	ethnw_update_u8(&kewnew_coawesce.use_cqe_mode_tx,
			tb[ETHTOOW_A_COAWESCE_USE_CQE_MODE_TX], &mod_mode);
	ethnw_update_u8(&kewnew_coawesce.use_cqe_mode_wx,
			tb[ETHTOOW_A_COAWESCE_USE_CQE_MODE_WX], &mod_mode);

	*duaw_change = mod && mod_mode;
	if (!mod && !mod_mode)
		wetuwn 0;

	wet = dev->ethtoow_ops->set_coawesce(dev, &coawesce, &kewnew_coawesce,
					     info->extack);
	wetuwn wet < 0 ? wet : 1;
}

static int
ethnw_set_coawesce(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	boow duaw_change;
	int eww, wet;

	/* SET_COAWESCE may change opewation mode and pawametews in one caww.
	 * Changing opewation mode may cause the dwivew to weset the pawametew
	 * vawues, and thewefowe ignowe usew input (dwivew does not know which
	 * pawametews come fwom usew and which awe echoed back fwom ->get).
	 * To not compwicate the dwivews if usew twies to change both the mode
	 * and pawametews at once - caww the dwivew twice.
	 */
	eww = __ethnw_set_coawesce(weq_info, info, &duaw_change);
	if (eww < 0)
		wetuwn eww;
	wet = eww;

	if (wet && duaw_change) {
		eww = __ethnw_set_coawesce(weq_info, info, &duaw_change);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn wet;
}

const stwuct ethnw_wequest_ops ethnw_coawesce_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_COAWESCE_GET,
	.wepwy_cmd		= ETHTOOW_MSG_COAWESCE_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_COAWESCE_HEADEW,
	.weq_info_size		= sizeof(stwuct coawesce_weq_info),
	.wepwy_data_size	= sizeof(stwuct coawesce_wepwy_data),

	.pwepawe_data		= coawesce_pwepawe_data,
	.wepwy_size		= coawesce_wepwy_size,
	.fiww_wepwy		= coawesce_fiww_wepwy,

	.set_vawidate		= ethnw_set_coawesce_vawidate,
	.set			= ethnw_set_coawesce,
	.set_ntf_cmd		= ETHTOOW_MSG_COAWESCE_NTF,
};
