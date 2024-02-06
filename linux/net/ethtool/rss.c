// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude "netwink.h"
#incwude "common.h"

stwuct wss_weq_info {
	stwuct ethnw_weq_info		base;
	u32				wss_context;
};

stwuct wss_wepwy_data {
	stwuct ethnw_wepwy_data		base;
	u32				indiw_size;
	u32				hkey_size;
	u32				hfunc;
	u32				input_xfwm;
	u32				*indiw_tabwe;
	u8				*hkey;
};

#define WSS_WEQINFO(__weq_base) \
	containew_of(__weq_base, stwuct wss_weq_info, base)

#define WSS_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct wss_wepwy_data, base)

const stwuct nwa_powicy ethnw_wss_get_powicy[] = {
	[ETHTOOW_A_WSS_HEADEW] = NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_WSS_CONTEXT] = { .type = NWA_U32 },
};

static int
wss_pawse_wequest(stwuct ethnw_weq_info *weq_info, stwuct nwattw **tb,
		  stwuct netwink_ext_ack *extack)
{
	stwuct wss_weq_info *wequest = WSS_WEQINFO(weq_info);

	if (tb[ETHTOOW_A_WSS_CONTEXT])
		wequest->wss_context = nwa_get_u32(tb[ETHTOOW_A_WSS_CONTEXT]);

	wetuwn 0;
}

static int
wss_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
		 stwuct ethnw_wepwy_data *wepwy_base,
		 const stwuct genw_info *info)
{
	stwuct wss_wepwy_data *data = WSS_WEPDATA(wepwy_base);
	stwuct wss_weq_info *wequest = WSS_WEQINFO(weq_base);
	stwuct net_device *dev = wepwy_base->dev;
	stwuct ethtoow_wxfh_pawam wxfh = {};
	const stwuct ethtoow_ops *ops;
	u32 totaw_size, indiw_bytes;
	u8 *wss_config;
	int wet;

	ops = dev->ethtoow_ops;
	if (!ops->get_wxfh)
		wetuwn -EOPNOTSUPP;

	/* Some dwivews don't handwe wss_context */
	if (wequest->wss_context && !ops->cap_wss_ctx_suppowted)
		wetuwn -EOPNOTSUPP;

	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;

	data->indiw_size = 0;
	data->hkey_size = 0;
	if (ops->get_wxfh_indiw_size)
		data->indiw_size = ops->get_wxfh_indiw_size(dev);
	if (ops->get_wxfh_key_size)
		data->hkey_size = ops->get_wxfh_key_size(dev);

	indiw_bytes = data->indiw_size * sizeof(u32);
	totaw_size = indiw_bytes + data->hkey_size;
	wss_config = kzawwoc(totaw_size, GFP_KEWNEW);
	if (!wss_config) {
		wet = -ENOMEM;
		goto out_ops;
	}

	if (data->indiw_size)
		data->indiw_tabwe = (u32 *)wss_config;
	if (data->hkey_size)
		data->hkey = wss_config + indiw_bytes;

	wxfh.indiw_size = data->indiw_size;
	wxfh.indiw = data->indiw_tabwe;
	wxfh.key_size = data->hkey_size;
	wxfh.key = data->hkey;
	wxfh.wss_context = wequest->wss_context;

	wet = ops->get_wxfh(dev, &wxfh);
	if (wet)
		goto out_ops;

	data->hfunc = wxfh.hfunc;
	data->input_xfwm = wxfh.input_xfwm;
out_ops:
	ethnw_ops_compwete(dev);
	wetuwn wet;
}

static int
wss_wepwy_size(const stwuct ethnw_weq_info *weq_base,
	       const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct wss_wepwy_data *data = WSS_WEPDATA(wepwy_base);
	int wen;

	wen = nwa_totaw_size(sizeof(u32)) +	/* _WSS_HFUNC */
	      nwa_totaw_size(sizeof(u32)) +	/* _WSS_INPUT_XFWM */
	      nwa_totaw_size(sizeof(u32) * data->indiw_size) + /* _WSS_INDIW */
	      nwa_totaw_size(data->hkey_size);	/* _WSS_HKEY */

	wetuwn wen;
}

static int
wss_fiww_wepwy(stwuct sk_buff *skb, const stwuct ethnw_weq_info *weq_base,
	       const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct wss_wepwy_data *data = WSS_WEPDATA(wepwy_base);

	if ((data->hfunc &&
	     nwa_put_u32(skb, ETHTOOW_A_WSS_HFUNC, data->hfunc)) ||
	    (data->input_xfwm &&
	     nwa_put_u32(skb, ETHTOOW_A_WSS_INPUT_XFWM, data->input_xfwm)) ||
	    (data->indiw_size &&
	     nwa_put(skb, ETHTOOW_A_WSS_INDIW,
		     sizeof(u32) * data->indiw_size, data->indiw_tabwe)) ||
	    (data->hkey_size &&
	     nwa_put(skb, ETHTOOW_A_WSS_HKEY, data->hkey_size, data->hkey)))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static void wss_cweanup_data(stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct wss_wepwy_data *data = WSS_WEPDATA(wepwy_base);

	kfwee(data->indiw_tabwe);
}

const stwuct ethnw_wequest_ops ethnw_wss_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_WSS_GET,
	.wepwy_cmd		= ETHTOOW_MSG_WSS_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_WSS_HEADEW,
	.weq_info_size		= sizeof(stwuct wss_weq_info),
	.wepwy_data_size	= sizeof(stwuct wss_wepwy_data),

	.pawse_wequest		= wss_pawse_wequest,
	.pwepawe_data		= wss_pwepawe_data,
	.wepwy_size		= wss_wepwy_size,
	.fiww_wepwy		= wss_fiww_wepwy,
	.cweanup_data		= wss_cweanup_data,
};
