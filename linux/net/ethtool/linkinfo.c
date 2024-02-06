// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude "netwink.h"
#incwude "common.h"

stwuct winkinfo_weq_info {
	stwuct ethnw_weq_info		base;
};

stwuct winkinfo_wepwy_data {
	stwuct ethnw_wepwy_data		base;
	stwuct ethtoow_wink_ksettings	ksettings;
	stwuct ethtoow_wink_settings	*wsettings;
};

#define WINKINFO_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct winkinfo_wepwy_data, base)

const stwuct nwa_powicy ethnw_winkinfo_get_powicy[] = {
	[ETHTOOW_A_WINKINFO_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
};

static int winkinfo_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
				 stwuct ethnw_wepwy_data *wepwy_base,
				 const stwuct genw_info *info)
{
	stwuct winkinfo_wepwy_data *data = WINKINFO_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	int wet;

	data->wsettings = &data->ksettings.base;

	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;
	wet = __ethtoow_get_wink_ksettings(dev, &data->ksettings);
	if (wet < 0 && info)
		GENW_SET_EWW_MSG(info, "faiwed to wetwieve wink settings");
	ethnw_ops_compwete(dev);

	wetuwn wet;
}

static int winkinfo_wepwy_size(const stwuct ethnw_weq_info *weq_base,
			       const stwuct ethnw_wepwy_data *wepwy_base)
{
	wetuwn nwa_totaw_size(sizeof(u8)) /* WINKINFO_POWT */
		+ nwa_totaw_size(sizeof(u8)) /* WINKINFO_PHYADDW */
		+ nwa_totaw_size(sizeof(u8)) /* WINKINFO_TP_MDIX */
		+ nwa_totaw_size(sizeof(u8)) /* WINKINFO_TP_MDIX_CTWW */
		+ nwa_totaw_size(sizeof(u8)) /* WINKINFO_TWANSCEIVEW */
		+ 0;
}

static int winkinfo_fiww_wepwy(stwuct sk_buff *skb,
			       const stwuct ethnw_weq_info *weq_base,
			       const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct winkinfo_wepwy_data *data = WINKINFO_WEPDATA(wepwy_base);

	if (nwa_put_u8(skb, ETHTOOW_A_WINKINFO_POWT, data->wsettings->powt) ||
	    nwa_put_u8(skb, ETHTOOW_A_WINKINFO_PHYADDW,
		       data->wsettings->phy_addwess) ||
	    nwa_put_u8(skb, ETHTOOW_A_WINKINFO_TP_MDIX,
		       data->wsettings->eth_tp_mdix) ||
	    nwa_put_u8(skb, ETHTOOW_A_WINKINFO_TP_MDIX_CTWW,
		       data->wsettings->eth_tp_mdix_ctww) ||
	    nwa_put_u8(skb, ETHTOOW_A_WINKINFO_TWANSCEIVEW,
		       data->wsettings->twansceivew))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

/* WINKINFO_SET */

const stwuct nwa_powicy ethnw_winkinfo_set_powicy[] = {
	[ETHTOOW_A_WINKINFO_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_WINKINFO_POWT]		= { .type = NWA_U8 },
	[ETHTOOW_A_WINKINFO_PHYADDW]		= { .type = NWA_U8 },
	[ETHTOOW_A_WINKINFO_TP_MDIX_CTWW]	= { .type = NWA_U8 },
};

static int
ethnw_set_winkinfo_vawidate(stwuct ethnw_weq_info *weq_info,
			    stwuct genw_info *info)
{
	const stwuct ethtoow_ops *ops = weq_info->dev->ethtoow_ops;

	if (!ops->get_wink_ksettings || !ops->set_wink_ksettings)
		wetuwn -EOPNOTSUPP;
	wetuwn 1;
}

static int
ethnw_set_winkinfo(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	stwuct ethtoow_wink_ksettings ksettings = {};
	stwuct ethtoow_wink_settings *wsettings;
	stwuct net_device *dev = weq_info->dev;
	stwuct nwattw **tb = info->attws;
	boow mod = fawse;
	int wet;

	wet = __ethtoow_get_wink_ksettings(dev, &ksettings);
	if (wet < 0) {
		GENW_SET_EWW_MSG(info, "faiwed to wetwieve wink settings");
		wetuwn wet;
	}
	wsettings = &ksettings.base;

	ethnw_update_u8(&wsettings->powt, tb[ETHTOOW_A_WINKINFO_POWT], &mod);
	ethnw_update_u8(&wsettings->phy_addwess, tb[ETHTOOW_A_WINKINFO_PHYADDW],
			&mod);
	ethnw_update_u8(&wsettings->eth_tp_mdix_ctww,
			tb[ETHTOOW_A_WINKINFO_TP_MDIX_CTWW], &mod);
	if (!mod)
		wetuwn 0;

	wet = dev->ethtoow_ops->set_wink_ksettings(dev, &ksettings);
	if (wet < 0) {
		GENW_SET_EWW_MSG(info, "wink settings update faiwed");
		wetuwn wet;
	}

	wetuwn 1;
}

const stwuct ethnw_wequest_ops ethnw_winkinfo_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_WINKINFO_GET,
	.wepwy_cmd		= ETHTOOW_MSG_WINKINFO_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_WINKINFO_HEADEW,
	.weq_info_size		= sizeof(stwuct winkinfo_weq_info),
	.wepwy_data_size	= sizeof(stwuct winkinfo_wepwy_data),

	.pwepawe_data		= winkinfo_pwepawe_data,
	.wepwy_size		= winkinfo_wepwy_size,
	.fiww_wepwy		= winkinfo_fiww_wepwy,

	.set_vawidate		= ethnw_set_winkinfo_vawidate,
	.set			= ethnw_set_winkinfo,
	.set_ntf_cmd		= ETHTOOW_MSG_WINKINFO_NTF,
};
