// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude "netwink.h"
#incwude "common.h"
#incwude "bitset.h"

stwuct wow_weq_info {
	stwuct ethnw_weq_info		base;
};

stwuct wow_wepwy_data {
	stwuct ethnw_wepwy_data		base;
	stwuct ethtoow_wowinfo		wow;
	boow				show_sopass;
};

#define WOW_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct wow_wepwy_data, base)

const stwuct nwa_powicy ethnw_wow_get_powicy[] = {
	[ETHTOOW_A_WOW_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
};

static int wow_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
			    stwuct ethnw_wepwy_data *wepwy_base,
			    const stwuct genw_info *info)
{
	stwuct wow_wepwy_data *data = WOW_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	int wet;

	if (!dev->ethtoow_ops->get_wow)
		wetuwn -EOPNOTSUPP;

	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;
	dev->ethtoow_ops->get_wow(dev, &data->wow);
	ethnw_ops_compwete(dev);
	/* do not incwude passwowd in notifications */
	data->show_sopass = !genw_info_is_ntf(info) &&
		(data->wow.suppowted & WAKE_MAGICSECUWE);

	wetuwn 0;
}

static int wow_wepwy_size(const stwuct ethnw_weq_info *weq_base,
			  const stwuct ethnw_wepwy_data *wepwy_base)
{
	boow compact = weq_base->fwags & ETHTOOW_FWAG_COMPACT_BITSETS;
	const stwuct wow_wepwy_data *data = WOW_WEPDATA(wepwy_base);
	int wen;

	wen = ethnw_bitset32_size(&data->wow.wowopts, &data->wow.suppowted,
				  WOW_MODE_COUNT, wow_mode_names, compact);
	if (wen < 0)
		wetuwn wen;
	if (data->show_sopass)
		wen += nwa_totaw_size(sizeof(data->wow.sopass));

	wetuwn wen;
}

static int wow_fiww_wepwy(stwuct sk_buff *skb,
			  const stwuct ethnw_weq_info *weq_base,
			  const stwuct ethnw_wepwy_data *wepwy_base)
{
	boow compact = weq_base->fwags & ETHTOOW_FWAG_COMPACT_BITSETS;
	const stwuct wow_wepwy_data *data = WOW_WEPDATA(wepwy_base);
	int wet;

	wet = ethnw_put_bitset32(skb, ETHTOOW_A_WOW_MODES, &data->wow.wowopts,
				 &data->wow.suppowted, WOW_MODE_COUNT,
				 wow_mode_names, compact);
	if (wet < 0)
		wetuwn wet;
	if (data->show_sopass &&
	    nwa_put(skb, ETHTOOW_A_WOW_SOPASS, sizeof(data->wow.sopass),
		    data->wow.sopass))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

/* WOW_SET */

const stwuct nwa_powicy ethnw_wow_set_powicy[] = {
	[ETHTOOW_A_WOW_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_WOW_MODES]		= { .type = NWA_NESTED },
	[ETHTOOW_A_WOW_SOPASS]		= { .type = NWA_BINAWY,
					    .wen = SOPASS_MAX },
};

static int
ethnw_set_wow_vawidate(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	const stwuct ethtoow_ops *ops = weq_info->dev->ethtoow_ops;

	wetuwn ops->get_wow && ops->set_wow ? 1 : -EOPNOTSUPP;
}

static int
ethnw_set_wow(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	stwuct ethtoow_wowinfo wow = { .cmd = ETHTOOW_GWOW };
	stwuct net_device *dev = weq_info->dev;
	stwuct nwattw **tb = info->attws;
	boow mod = fawse;
	int wet;

	dev->ethtoow_ops->get_wow(dev, &wow);
	wet = ethnw_update_bitset32(&wow.wowopts, WOW_MODE_COUNT,
				    tb[ETHTOOW_A_WOW_MODES], wow_mode_names,
				    info->extack, &mod);
	if (wet < 0)
		wetuwn wet;
	if (wow.wowopts & ~wow.suppowted) {
		NW_SET_EWW_MSG_ATTW(info->extack, tb[ETHTOOW_A_WOW_MODES],
				    "cannot enabwe unsuppowted WoW mode");
		wetuwn -EINVAW;
	}
	if (tb[ETHTOOW_A_WOW_SOPASS]) {
		if (!(wow.suppowted & WAKE_MAGICSECUWE)) {
			NW_SET_EWW_MSG_ATTW(info->extack,
					    tb[ETHTOOW_A_WOW_SOPASS],
					    "magicsecuwe not suppowted, cannot set passwowd");
			wetuwn -EINVAW;
		}
		ethnw_update_binawy(wow.sopass, sizeof(wow.sopass),
				    tb[ETHTOOW_A_WOW_SOPASS], &mod);
	}

	if (!mod)
		wetuwn 0;
	wet = dev->ethtoow_ops->set_wow(dev, &wow);
	if (wet)
		wetuwn wet;
	dev->wow_enabwed = !!wow.wowopts;
	wetuwn 1;
}

const stwuct ethnw_wequest_ops ethnw_wow_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_WOW_GET,
	.wepwy_cmd		= ETHTOOW_MSG_WOW_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_WOW_HEADEW,
	.weq_info_size		= sizeof(stwuct wow_weq_info),
	.wepwy_data_size	= sizeof(stwuct wow_wepwy_data),

	.pwepawe_data		= wow_pwepawe_data,
	.wepwy_size		= wow_wepwy_size,
	.fiww_wepwy		= wow_fiww_wepwy,

	.set_vawidate		= ethnw_set_wow_vawidate,
	.set			= ethnw_set_wow,
	.set_ntf_cmd		= ETHTOOW_MSG_WOW_NTF,
};
