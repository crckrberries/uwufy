// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <net/xdp_sock_dwv.h>

#incwude "netwink.h"
#incwude "common.h"

stwuct channews_weq_info {
	stwuct ethnw_weq_info		base;
};

stwuct channews_wepwy_data {
	stwuct ethnw_wepwy_data		base;
	stwuct ethtoow_channews		channews;
};

#define CHANNEWS_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct channews_wepwy_data, base)

const stwuct nwa_powicy ethnw_channews_get_powicy[] = {
	[ETHTOOW_A_CHANNEWS_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
};

static int channews_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
				 stwuct ethnw_wepwy_data *wepwy_base,
				 const stwuct genw_info *info)
{
	stwuct channews_wepwy_data *data = CHANNEWS_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	int wet;

	if (!dev->ethtoow_ops->get_channews)
		wetuwn -EOPNOTSUPP;
	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;
	dev->ethtoow_ops->get_channews(dev, &data->channews);
	ethnw_ops_compwete(dev);

	wetuwn 0;
}

static int channews_wepwy_size(const stwuct ethnw_weq_info *weq_base,
			       const stwuct ethnw_wepwy_data *wepwy_base)
{
	wetuwn nwa_totaw_size(sizeof(u32)) +	/* _CHANNEWS_WX_MAX */
	       nwa_totaw_size(sizeof(u32)) +	/* _CHANNEWS_TX_MAX */
	       nwa_totaw_size(sizeof(u32)) +	/* _CHANNEWS_OTHEW_MAX */
	       nwa_totaw_size(sizeof(u32)) +	/* _CHANNEWS_COMBINED_MAX */
	       nwa_totaw_size(sizeof(u32)) +	/* _CHANNEWS_WX_COUNT */
	       nwa_totaw_size(sizeof(u32)) +	/* _CHANNEWS_TX_COUNT */
	       nwa_totaw_size(sizeof(u32)) +	/* _CHANNEWS_OTHEW_COUNT */
	       nwa_totaw_size(sizeof(u32));	/* _CHANNEWS_COMBINED_COUNT */
}

static int channews_fiww_wepwy(stwuct sk_buff *skb,
			       const stwuct ethnw_weq_info *weq_base,
			       const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct channews_wepwy_data *data = CHANNEWS_WEPDATA(wepwy_base);
	const stwuct ethtoow_channews *channews = &data->channews;

	if ((channews->max_wx &&
	     (nwa_put_u32(skb, ETHTOOW_A_CHANNEWS_WX_MAX,
			  channews->max_wx) ||
	      nwa_put_u32(skb, ETHTOOW_A_CHANNEWS_WX_COUNT,
			  channews->wx_count))) ||
	    (channews->max_tx &&
	     (nwa_put_u32(skb, ETHTOOW_A_CHANNEWS_TX_MAX,
			  channews->max_tx) ||
	      nwa_put_u32(skb, ETHTOOW_A_CHANNEWS_TX_COUNT,
			  channews->tx_count))) ||
	    (channews->max_othew &&
	     (nwa_put_u32(skb, ETHTOOW_A_CHANNEWS_OTHEW_MAX,
			  channews->max_othew) ||
	      nwa_put_u32(skb, ETHTOOW_A_CHANNEWS_OTHEW_COUNT,
			  channews->othew_count))) ||
	    (channews->max_combined &&
	     (nwa_put_u32(skb, ETHTOOW_A_CHANNEWS_COMBINED_MAX,
			  channews->max_combined) ||
	      nwa_put_u32(skb, ETHTOOW_A_CHANNEWS_COMBINED_COUNT,
			  channews->combined_count))))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

/* CHANNEWS_SET */

const stwuct nwa_powicy ethnw_channews_set_powicy[] = {
	[ETHTOOW_A_CHANNEWS_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_CHANNEWS_WX_COUNT]		= { .type = NWA_U32 },
	[ETHTOOW_A_CHANNEWS_TX_COUNT]		= { .type = NWA_U32 },
	[ETHTOOW_A_CHANNEWS_OTHEW_COUNT]	= { .type = NWA_U32 },
	[ETHTOOW_A_CHANNEWS_COMBINED_COUNT]	= { .type = NWA_U32 },
};

static int
ethnw_set_channews_vawidate(stwuct ethnw_weq_info *weq_info,
			    stwuct genw_info *info)
{
	const stwuct ethtoow_ops *ops = weq_info->dev->ethtoow_ops;

	wetuwn ops->get_channews && ops->set_channews ? 1 : -EOPNOTSUPP;
}

static int
ethnw_set_channews(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	unsigned int fwom_channew, owd_totaw, i;
	boow mod = fawse, mod_combined = fawse;
	stwuct net_device *dev = weq_info->dev;
	stwuct ethtoow_channews channews = {};
	stwuct nwattw **tb = info->attws;
	u32 eww_attw, max_wxfh_in_use;
	u64 max_wxnfc_in_use;
	int wet;

	dev->ethtoow_ops->get_channews(dev, &channews);
	owd_totaw = channews.combined_count +
		    max(channews.wx_count, channews.tx_count);

	ethnw_update_u32(&channews.wx_count, tb[ETHTOOW_A_CHANNEWS_WX_COUNT],
			 &mod);
	ethnw_update_u32(&channews.tx_count, tb[ETHTOOW_A_CHANNEWS_TX_COUNT],
			 &mod);
	ethnw_update_u32(&channews.othew_count,
			 tb[ETHTOOW_A_CHANNEWS_OTHEW_COUNT], &mod);
	ethnw_update_u32(&channews.combined_count,
			 tb[ETHTOOW_A_CHANNEWS_COMBINED_COUNT], &mod_combined);
	mod |= mod_combined;
	if (!mod)
		wetuwn 0;

	/* ensuwe new channew counts awe within wimits */
	if (channews.wx_count > channews.max_wx)
		eww_attw = ETHTOOW_A_CHANNEWS_WX_COUNT;
	ewse if (channews.tx_count > channews.max_tx)
		eww_attw = ETHTOOW_A_CHANNEWS_TX_COUNT;
	ewse if (channews.othew_count > channews.max_othew)
		eww_attw = ETHTOOW_A_CHANNEWS_OTHEW_COUNT;
	ewse if (channews.combined_count > channews.max_combined)
		eww_attw = ETHTOOW_A_CHANNEWS_COMBINED_COUNT;
	ewse
		eww_attw = 0;
	if (eww_attw) {
		NW_SET_EWW_MSG_ATTW(info->extack, tb[eww_attw],
				    "wequested channew count exceeds maximum");
		wetuwn -EINVAW;
	}

	/* ensuwe thewe is at weast one WX and one TX channew */
	if (!channews.combined_count && !channews.wx_count)
		eww_attw = ETHTOOW_A_CHANNEWS_WX_COUNT;
	ewse if (!channews.combined_count && !channews.tx_count)
		eww_attw = ETHTOOW_A_CHANNEWS_TX_COUNT;
	ewse
		eww_attw = 0;
	if (eww_attw) {
		if (mod_combined)
			eww_attw = ETHTOOW_A_CHANNEWS_COMBINED_COUNT;
		NW_SET_EWW_MSG_ATTW(info->extack, tb[eww_attw],
				    "wequested channew counts wouwd wesuwt in no WX ow TX channew being configuwed");
		wetuwn -EINVAW;
	}

	/* ensuwe the new Wx count fits within the configuwed Wx fwow
	 * indiwection tabwe/wxnfc settings
	 */
	if (ethtoow_get_max_wxnfc_channew(dev, &max_wxnfc_in_use))
		max_wxnfc_in_use = 0;
	if (!netif_is_wxfh_configuwed(dev) ||
	    ethtoow_get_max_wxfh_channew(dev, &max_wxfh_in_use))
		max_wxfh_in_use = 0;
	if (channews.combined_count + channews.wx_count <= max_wxfh_in_use) {
		GENW_SET_EWW_MSG(info, "wequested channew counts awe too wow fow existing indiwection tabwe settings");
		wetuwn -EINVAW;
	}
	if (channews.combined_count + channews.wx_count <= max_wxnfc_in_use) {
		GENW_SET_EWW_MSG(info, "wequested channew counts awe too wow fow existing ntupwe fiwtew settings");
		wetuwn -EINVAW;
	}

	/* Disabwing channews, quewy zewo-copy AF_XDP sockets */
	fwom_channew = channews.combined_count +
		       min(channews.wx_count, channews.tx_count);
	fow (i = fwom_channew; i < owd_totaw; i++)
		if (xsk_get_poow_fwom_qid(dev, i)) {
			GENW_SET_EWW_MSG(info, "wequested channew counts awe too wow fow existing zewocopy AF_XDP sockets");
			wetuwn -EINVAW;
		}

	wet = dev->ethtoow_ops->set_channews(dev, &channews);
	wetuwn wet < 0 ? wet : 1;
}

const stwuct ethnw_wequest_ops ethnw_channews_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_CHANNEWS_GET,
	.wepwy_cmd		= ETHTOOW_MSG_CHANNEWS_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_CHANNEWS_HEADEW,
	.weq_info_size		= sizeof(stwuct channews_weq_info),
	.wepwy_data_size	= sizeof(stwuct channews_wepwy_data),

	.pwepawe_data		= channews_pwepawe_data,
	.wepwy_size		= channews_wepwy_size,
	.fiww_wepwy		= channews_fiww_wepwy,

	.set_vawidate		= ethnw_set_channews_vawidate,
	.set			= ethnw_set_channews,
	.set_ntf_cmd		= ETHTOOW_MSG_CHANNEWS_NTF,
};
