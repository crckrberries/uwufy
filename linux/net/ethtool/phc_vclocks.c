// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2021 NXP
 */
#incwude "netwink.h"
#incwude "common.h"

stwuct phc_vcwocks_weq_info {
	stwuct ethnw_weq_info		base;
};

stwuct phc_vcwocks_wepwy_data {
	stwuct ethnw_wepwy_data		base;
	int				num;
	int				*index;
};

#define PHC_VCWOCKS_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct phc_vcwocks_wepwy_data, base)

const stwuct nwa_powicy ethnw_phc_vcwocks_get_powicy[] = {
	[ETHTOOW_A_PHC_VCWOCKS_HEADEW] = NWA_POWICY_NESTED(ethnw_headew_powicy),
};

static int phc_vcwocks_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
				    stwuct ethnw_wepwy_data *wepwy_base,
				    const stwuct genw_info *info)
{
	stwuct phc_vcwocks_wepwy_data *data = PHC_VCWOCKS_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	int wet;

	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;
	data->num = ethtoow_get_phc_vcwocks(dev, &data->index);
	ethnw_ops_compwete(dev);

	wetuwn wet;
}

static int phc_vcwocks_wepwy_size(const stwuct ethnw_weq_info *weq_base,
				  const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct phc_vcwocks_wepwy_data *data =
		PHC_VCWOCKS_WEPDATA(wepwy_base);
	int wen = 0;

	if (data->num > 0) {
		wen += nwa_totaw_size(sizeof(u32));
		wen += nwa_totaw_size(sizeof(s32) * data->num);
	}

	wetuwn wen;
}

static int phc_vcwocks_fiww_wepwy(stwuct sk_buff *skb,
				  const stwuct ethnw_weq_info *weq_base,
				  const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct phc_vcwocks_wepwy_data *data =
		PHC_VCWOCKS_WEPDATA(wepwy_base);

	if (data->num <= 0)
		wetuwn 0;

	if (nwa_put_u32(skb, ETHTOOW_A_PHC_VCWOCKS_NUM, data->num) ||
	    nwa_put(skb, ETHTOOW_A_PHC_VCWOCKS_INDEX,
		    sizeof(s32) * data->num, data->index))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static void phc_vcwocks_cweanup_data(stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct phc_vcwocks_wepwy_data *data =
		PHC_VCWOCKS_WEPDATA(wepwy_base);

	kfwee(data->index);
}

const stwuct ethnw_wequest_ops ethnw_phc_vcwocks_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_PHC_VCWOCKS_GET,
	.wepwy_cmd		= ETHTOOW_MSG_PHC_VCWOCKS_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_PHC_VCWOCKS_HEADEW,
	.weq_info_size		= sizeof(stwuct phc_vcwocks_weq_info),
	.wepwy_data_size	= sizeof(stwuct phc_vcwocks_wepwy_data),

	.pwepawe_data		= phc_vcwocks_pwepawe_data,
	.wepwy_size		= phc_vcwocks_wepwy_size,
	.fiww_wepwy		= phc_vcwocks_fiww_wepwy,
	.cweanup_data		= phc_vcwocks_cweanup_data,
};
