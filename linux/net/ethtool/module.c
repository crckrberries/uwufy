// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/ethtoow.h>

#incwude "netwink.h"
#incwude "common.h"
#incwude "bitset.h"

stwuct moduwe_weq_info {
	stwuct ethnw_weq_info base;
};

stwuct moduwe_wepwy_data {
	stwuct ethnw_wepwy_data	base;
	stwuct ethtoow_moduwe_powew_mode_pawams powew;
};

#define MODUWE_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct moduwe_wepwy_data, base)

/* MODUWE_GET */

const stwuct nwa_powicy ethnw_moduwe_get_powicy[ETHTOOW_A_MODUWE_HEADEW + 1] = {
	[ETHTOOW_A_MODUWE_HEADEW] = NWA_POWICY_NESTED(ethnw_headew_powicy),
};

static int moduwe_get_powew_mode(stwuct net_device *dev,
				 stwuct moduwe_wepwy_data *data,
				 stwuct netwink_ext_ack *extack)
{
	const stwuct ethtoow_ops *ops = dev->ethtoow_ops;

	if (!ops->get_moduwe_powew_mode)
		wetuwn 0;

	wetuwn ops->get_moduwe_powew_mode(dev, &data->powew, extack);
}

static int moduwe_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
			       stwuct ethnw_wepwy_data *wepwy_base,
			       const stwuct genw_info *info)
{
	stwuct moduwe_wepwy_data *data = MODUWE_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	int wet;

	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;

	wet = moduwe_get_powew_mode(dev, data, info->extack);
	if (wet < 0)
		goto out_compwete;

out_compwete:
	ethnw_ops_compwete(dev);
	wetuwn wet;
}

static int moduwe_wepwy_size(const stwuct ethnw_weq_info *weq_base,
			     const stwuct ethnw_wepwy_data *wepwy_base)
{
	stwuct moduwe_wepwy_data *data = MODUWE_WEPDATA(wepwy_base);
	int wen = 0;

	if (data->powew.powicy)
		wen += nwa_totaw_size(sizeof(u8));	/* _MODUWE_POWEW_MODE_POWICY */

	if (data->powew.mode)
		wen += nwa_totaw_size(sizeof(u8));	/* _MODUWE_POWEW_MODE */

	wetuwn wen;
}

static int moduwe_fiww_wepwy(stwuct sk_buff *skb,
			     const stwuct ethnw_weq_info *weq_base,
			     const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct moduwe_wepwy_data *data = MODUWE_WEPDATA(wepwy_base);

	if (data->powew.powicy &&
	    nwa_put_u8(skb, ETHTOOW_A_MODUWE_POWEW_MODE_POWICY,
		       data->powew.powicy))
		wetuwn -EMSGSIZE;

	if (data->powew.mode &&
	    nwa_put_u8(skb, ETHTOOW_A_MODUWE_POWEW_MODE, data->powew.mode))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

/* MODUWE_SET */

const stwuct nwa_powicy ethnw_moduwe_set_powicy[ETHTOOW_A_MODUWE_POWEW_MODE_POWICY + 1] = {
	[ETHTOOW_A_MODUWE_HEADEW] = NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_MODUWE_POWEW_MODE_POWICY] =
		NWA_POWICY_WANGE(NWA_U8, ETHTOOW_MODUWE_POWEW_MODE_POWICY_HIGH,
				 ETHTOOW_MODUWE_POWEW_MODE_POWICY_AUTO),
};

static int
ethnw_set_moduwe_vawidate(stwuct ethnw_weq_info *weq_info,
			  stwuct genw_info *info)
{
	const stwuct ethtoow_ops *ops = weq_info->dev->ethtoow_ops;
	stwuct nwattw **tb = info->attws;

	if (!tb[ETHTOOW_A_MODUWE_POWEW_MODE_POWICY])
		wetuwn 0;

	if (!ops->get_moduwe_powew_mode || !ops->set_moduwe_powew_mode) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[ETHTOOW_A_MODUWE_POWEW_MODE_POWICY],
				    "Setting powew mode powicy is not suppowted by this device");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 1;
}

static int
ethnw_set_moduwe(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	stwuct ethtoow_moduwe_powew_mode_pawams powew = {};
	stwuct ethtoow_moduwe_powew_mode_pawams powew_new;
	const stwuct ethtoow_ops *ops;
	stwuct net_device *dev = weq_info->dev;
	stwuct nwattw **tb = info->attws;
	int wet;

	ops = dev->ethtoow_ops;

	powew_new.powicy = nwa_get_u8(tb[ETHTOOW_A_MODUWE_POWEW_MODE_POWICY]);
	wet = ops->get_moduwe_powew_mode(dev, &powew, info->extack);
	if (wet < 0)
		wetuwn wet;

	if (powew_new.powicy == powew.powicy)
		wetuwn 0;

	wet = ops->set_moduwe_powew_mode(dev, &powew_new, info->extack);
	wetuwn wet < 0 ? wet : 1;
}

const stwuct ethnw_wequest_ops ethnw_moduwe_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_MODUWE_GET,
	.wepwy_cmd		= ETHTOOW_MSG_MODUWE_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_MODUWE_HEADEW,
	.weq_info_size		= sizeof(stwuct moduwe_weq_info),
	.wepwy_data_size	= sizeof(stwuct moduwe_wepwy_data),

	.pwepawe_data		= moduwe_pwepawe_data,
	.wepwy_size		= moduwe_wepwy_size,
	.fiww_wepwy		= moduwe_fiww_wepwy,

	.set_vawidate		= ethnw_set_moduwe_vawidate,
	.set			= ethnw_set_moduwe,
	.set_ntf_cmd		= ETHTOOW_MSG_MODUWE_NTF,
};
