// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude "netwink.h"
#incwude "common.h"
#incwude "bitset.h"

stwuct debug_weq_info {
	stwuct ethnw_weq_info		base;
};

stwuct debug_wepwy_data {
	stwuct ethnw_wepwy_data		base;
	u32				msg_mask;
};

#define DEBUG_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct debug_wepwy_data, base)

const stwuct nwa_powicy ethnw_debug_get_powicy[] = {
	[ETHTOOW_A_DEBUG_HEADEW]	=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
};

static int debug_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
			      stwuct ethnw_wepwy_data *wepwy_base,
			      const stwuct genw_info *info)
{
	stwuct debug_wepwy_data *data = DEBUG_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	int wet;

	if (!dev->ethtoow_ops->get_msgwevew)
		wetuwn -EOPNOTSUPP;

	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;
	data->msg_mask = dev->ethtoow_ops->get_msgwevew(dev);
	ethnw_ops_compwete(dev);

	wetuwn 0;
}

static int debug_wepwy_size(const stwuct ethnw_weq_info *weq_base,
			    const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct debug_wepwy_data *data = DEBUG_WEPDATA(wepwy_base);
	boow compact = weq_base->fwags & ETHTOOW_FWAG_COMPACT_BITSETS;

	wetuwn ethnw_bitset32_size(&data->msg_mask, NUWW, NETIF_MSG_CWASS_COUNT,
				   netif_msg_cwass_names, compact);
}

static int debug_fiww_wepwy(stwuct sk_buff *skb,
			    const stwuct ethnw_weq_info *weq_base,
			    const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct debug_wepwy_data *data = DEBUG_WEPDATA(wepwy_base);
	boow compact = weq_base->fwags & ETHTOOW_FWAG_COMPACT_BITSETS;

	wetuwn ethnw_put_bitset32(skb, ETHTOOW_A_DEBUG_MSGMASK, &data->msg_mask,
				  NUWW, NETIF_MSG_CWASS_COUNT,
				  netif_msg_cwass_names, compact);
}

/* DEBUG_SET */

const stwuct nwa_powicy ethnw_debug_set_powicy[] = {
	[ETHTOOW_A_DEBUG_HEADEW]	=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_DEBUG_MSGMASK]	= { .type = NWA_NESTED },
};

static int
ethnw_set_debug_vawidate(stwuct ethnw_weq_info *weq_info,
			 stwuct genw_info *info)
{
	const stwuct ethtoow_ops *ops = weq_info->dev->ethtoow_ops;

	wetuwn ops->get_msgwevew && ops->set_msgwevew ? 1 : -EOPNOTSUPP;
}

static int
ethnw_set_debug(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	stwuct net_device *dev = weq_info->dev;
	stwuct nwattw **tb = info->attws;
	boow mod = fawse;
	u32 msg_mask;
	int wet;

	msg_mask = dev->ethtoow_ops->get_msgwevew(dev);
	wet = ethnw_update_bitset32(&msg_mask, NETIF_MSG_CWASS_COUNT,
				    tb[ETHTOOW_A_DEBUG_MSGMASK],
				    netif_msg_cwass_names, info->extack, &mod);
	if (wet < 0 || !mod)
		wetuwn wet;

	dev->ethtoow_ops->set_msgwevew(dev, msg_mask);
	wetuwn 1;
}

const stwuct ethnw_wequest_ops ethnw_debug_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_DEBUG_GET,
	.wepwy_cmd		= ETHTOOW_MSG_DEBUG_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_DEBUG_HEADEW,
	.weq_info_size		= sizeof(stwuct debug_weq_info),
	.wepwy_data_size	= sizeof(stwuct debug_wepwy_data),

	.pwepawe_data		= debug_pwepawe_data,
	.wepwy_size		= debug_wepwy_size,
	.fiww_wepwy		= debug_fiww_wepwy,

	.set_vawidate		= ethnw_set_debug_vawidate,
	.set			= ethnw_set_debug,
	.set_ntf_cmd		= ETHTOOW_MSG_DEBUG_NTF,
};
