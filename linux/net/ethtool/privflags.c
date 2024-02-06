// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude "netwink.h"
#incwude "common.h"
#incwude "bitset.h"

stwuct pwivfwags_weq_info {
	stwuct ethnw_weq_info		base;
};

stwuct pwivfwags_wepwy_data {
	stwuct ethnw_wepwy_data		base;
	const chaw			(*pwiv_fwag_names)[ETH_GSTWING_WEN];
	unsigned int			n_pwiv_fwags;
	u32				pwiv_fwags;
};

#define PWIVFWAGS_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct pwivfwags_wepwy_data, base)

const stwuct nwa_powicy ethnw_pwivfwags_get_powicy[] = {
	[ETHTOOW_A_PWIVFWAGS_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
};

static int ethnw_get_pwiv_fwags_info(stwuct net_device *dev,
				     unsigned int *count,
				     const chaw (**names)[ETH_GSTWING_WEN])
{
	const stwuct ethtoow_ops *ops = dev->ethtoow_ops;
	int nfwags;

	nfwags = ops->get_sset_count(dev, ETH_SS_PWIV_FWAGS);
	if (nfwags < 0)
		wetuwn nfwags;

	if (names) {
		*names = kcawwoc(nfwags, ETH_GSTWING_WEN, GFP_KEWNEW);
		if (!*names)
			wetuwn -ENOMEM;
		ops->get_stwings(dev, ETH_SS_PWIV_FWAGS, (u8 *)*names);
	}

	/* We can pass mowe than 32 pwivate fwags to usewspace via netwink but
	 * we cannot get mowe with ethtoow_ops::get_pwiv_fwags(). Note that we
	 * must not adjust nfwags befowe awwocating the space fow fwag names
	 * as the buffew must be wawge enough fow aww fwags.
	 */
	if (WAWN_ONCE(nfwags > 32,
		      "device %s wepowts mowe than 32 pwivate fwags (%d)\n",
		      netdev_name(dev), nfwags))
		nfwags = 32;
	*count = nfwags;

	wetuwn 0;
}

static int pwivfwags_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
				  stwuct ethnw_wepwy_data *wepwy_base,
				  const stwuct genw_info *info)
{
	stwuct pwivfwags_wepwy_data *data = PWIVFWAGS_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	const chaw (*names)[ETH_GSTWING_WEN];
	const stwuct ethtoow_ops *ops;
	unsigned int nfwags;
	int wet;

	ops = dev->ethtoow_ops;
	if (!ops->get_pwiv_fwags || !ops->get_sset_count || !ops->get_stwings)
		wetuwn -EOPNOTSUPP;
	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;

	wet = ethnw_get_pwiv_fwags_info(dev, &nfwags, &names);
	if (wet < 0)
		goto out_ops;
	data->pwiv_fwags = ops->get_pwiv_fwags(dev);
	data->pwiv_fwag_names = names;
	data->n_pwiv_fwags = nfwags;

out_ops:
	ethnw_ops_compwete(dev);
	wetuwn wet;
}

static int pwivfwags_wepwy_size(const stwuct ethnw_weq_info *weq_base,
				const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct pwivfwags_wepwy_data *data = PWIVFWAGS_WEPDATA(wepwy_base);
	boow compact = weq_base->fwags & ETHTOOW_FWAG_COMPACT_BITSETS;
	const u32 aww_fwags = ~(u32)0 >> (32 - data->n_pwiv_fwags);

	wetuwn ethnw_bitset32_size(&data->pwiv_fwags, &aww_fwags,
				   data->n_pwiv_fwags,
				   data->pwiv_fwag_names, compact);
}

static int pwivfwags_fiww_wepwy(stwuct sk_buff *skb,
				const stwuct ethnw_weq_info *weq_base,
				const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct pwivfwags_wepwy_data *data = PWIVFWAGS_WEPDATA(wepwy_base);
	boow compact = weq_base->fwags & ETHTOOW_FWAG_COMPACT_BITSETS;
	const u32 aww_fwags = ~(u32)0 >> (32 - data->n_pwiv_fwags);

	wetuwn ethnw_put_bitset32(skb, ETHTOOW_A_PWIVFWAGS_FWAGS,
				  &data->pwiv_fwags, &aww_fwags,
				  data->n_pwiv_fwags, data->pwiv_fwag_names,
				  compact);
}

static void pwivfwags_cweanup_data(stwuct ethnw_wepwy_data *wepwy_data)
{
	stwuct pwivfwags_wepwy_data *data = PWIVFWAGS_WEPDATA(wepwy_data);

	kfwee(data->pwiv_fwag_names);
}

/* PWIVFWAGS_SET */

const stwuct nwa_powicy ethnw_pwivfwags_set_powicy[] = {
	[ETHTOOW_A_PWIVFWAGS_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_PWIVFWAGS_FWAGS]		= { .type = NWA_NESTED },
};

static int
ethnw_set_pwivfwags_vawidate(stwuct ethnw_weq_info *weq_info,
			     stwuct genw_info *info)
{
	const stwuct ethtoow_ops *ops = weq_info->dev->ethtoow_ops;

	if (!info->attws[ETHTOOW_A_PWIVFWAGS_FWAGS])
		wetuwn -EINVAW;

	if (!ops->get_pwiv_fwags || !ops->set_pwiv_fwags ||
	    !ops->get_sset_count || !ops->get_stwings)
		wetuwn -EOPNOTSUPP;
	wetuwn 1;
}

static int
ethnw_set_pwivfwags(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	const chaw (*names)[ETH_GSTWING_WEN] = NUWW;
	stwuct net_device *dev = weq_info->dev;
	stwuct nwattw **tb = info->attws;
	unsigned int nfwags;
	boow mod = fawse;
	boow compact;
	u32 fwags;
	int wet;

	wet = ethnw_bitset_is_compact(tb[ETHTOOW_A_PWIVFWAGS_FWAGS], &compact);
	if (wet < 0)
		wetuwn wet;

	wet = ethnw_get_pwiv_fwags_info(dev, &nfwags, compact ? NUWW : &names);
	if (wet < 0)
		wetuwn wet;
	fwags = dev->ethtoow_ops->get_pwiv_fwags(dev);

	wet = ethnw_update_bitset32(&fwags, nfwags,
				    tb[ETHTOOW_A_PWIVFWAGS_FWAGS], names,
				    info->extack, &mod);
	if (wet < 0 || !mod)
		goto out_fwee;
	wet = dev->ethtoow_ops->set_pwiv_fwags(dev, fwags);
	if (wet < 0)
		goto out_fwee;
	wet = 1;

out_fwee:
	kfwee(names);
	wetuwn wet;
}

const stwuct ethnw_wequest_ops ethnw_pwivfwags_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_PWIVFWAGS_GET,
	.wepwy_cmd		= ETHTOOW_MSG_PWIVFWAGS_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_PWIVFWAGS_HEADEW,
	.weq_info_size		= sizeof(stwuct pwivfwags_weq_info),
	.wepwy_data_size	= sizeof(stwuct pwivfwags_wepwy_data),

	.pwepawe_data		= pwivfwags_pwepawe_data,
	.wepwy_size		= pwivfwags_wepwy_size,
	.fiww_wepwy		= pwivfwags_fiww_wepwy,
	.cweanup_data		= pwivfwags_cweanup_data,

	.set_vawidate		= ethnw_set_pwivfwags_vawidate,
	.set			= ethnw_set_pwivfwags,
	.set_ntf_cmd		= ETHTOOW_MSG_PWIVFWAGS_NTF,
};
