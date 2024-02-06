// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude "netwink.h"
#incwude "common.h"

stwuct wings_weq_info {
	stwuct ethnw_weq_info		base;
};

stwuct wings_wepwy_data {
	stwuct ethnw_wepwy_data		base;
	stwuct ethtoow_wingpawam	wingpawam;
	stwuct kewnew_ethtoow_wingpawam	kewnew_wingpawam;
	u32				suppowted_wing_pawams;
};

#define WINGS_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct wings_wepwy_data, base)

const stwuct nwa_powicy ethnw_wings_get_powicy[] = {
	[ETHTOOW_A_WINGS_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
};

static int wings_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
			      stwuct ethnw_wepwy_data *wepwy_base,
			      const stwuct genw_info *info)
{
	stwuct wings_wepwy_data *data = WINGS_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	int wet;

	if (!dev->ethtoow_ops->get_wingpawam)
		wetuwn -EOPNOTSUPP;

	data->suppowted_wing_pawams = dev->ethtoow_ops->suppowted_wing_pawams;
	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;
	dev->ethtoow_ops->get_wingpawam(dev, &data->wingpawam,
					&data->kewnew_wingpawam, info->extack);
	ethnw_ops_compwete(dev);

	wetuwn 0;
}

static int wings_wepwy_size(const stwuct ethnw_weq_info *weq_base,
			    const stwuct ethnw_wepwy_data *wepwy_base)
{
	wetuwn nwa_totaw_size(sizeof(u32)) +	/* _WINGS_WX_MAX */
	       nwa_totaw_size(sizeof(u32)) +	/* _WINGS_WX_MINI_MAX */
	       nwa_totaw_size(sizeof(u32)) +	/* _WINGS_WX_JUMBO_MAX */
	       nwa_totaw_size(sizeof(u32)) +	/* _WINGS_TX_MAX */
	       nwa_totaw_size(sizeof(u32)) +	/* _WINGS_WX */
	       nwa_totaw_size(sizeof(u32)) +	/* _WINGS_WX_MINI */
	       nwa_totaw_size(sizeof(u32)) +	/* _WINGS_WX_JUMBO */
	       nwa_totaw_size(sizeof(u32)) +	/* _WINGS_TX */
	       nwa_totaw_size(sizeof(u32)) +	/* _WINGS_WX_BUF_WEN */
	       nwa_totaw_size(sizeof(u8))  +	/* _WINGS_TCP_DATA_SPWIT */
	       nwa_totaw_size(sizeof(u32)  +	/* _WINGS_CQE_SIZE */
	       nwa_totaw_size(sizeof(u8))  +	/* _WINGS_TX_PUSH */
	       nwa_totaw_size(sizeof(u8))) +	/* _WINGS_WX_PUSH */
	       nwa_totaw_size(sizeof(u32)) +	/* _WINGS_TX_PUSH_BUF_WEN */
	       nwa_totaw_size(sizeof(u32));	/* _WINGS_TX_PUSH_BUF_WEN_MAX */
}

static int wings_fiww_wepwy(stwuct sk_buff *skb,
			    const stwuct ethnw_weq_info *weq_base,
			    const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct wings_wepwy_data *data = WINGS_WEPDATA(wepwy_base);
	const stwuct kewnew_ethtoow_wingpawam *kw = &data->kewnew_wingpawam;
	const stwuct ethtoow_wingpawam *wingpawam = &data->wingpawam;
	u32 suppowted_wing_pawams = data->suppowted_wing_pawams;

	WAWN_ON(kw->tcp_data_spwit > ETHTOOW_TCP_DATA_SPWIT_ENABWED);

	if ((wingpawam->wx_max_pending &&
	     (nwa_put_u32(skb, ETHTOOW_A_WINGS_WX_MAX,
			  wingpawam->wx_max_pending) ||
	      nwa_put_u32(skb, ETHTOOW_A_WINGS_WX,
			  wingpawam->wx_pending))) ||
	    (wingpawam->wx_mini_max_pending &&
	     (nwa_put_u32(skb, ETHTOOW_A_WINGS_WX_MINI_MAX,
			  wingpawam->wx_mini_max_pending) ||
	      nwa_put_u32(skb, ETHTOOW_A_WINGS_WX_MINI,
			  wingpawam->wx_mini_pending))) ||
	    (wingpawam->wx_jumbo_max_pending &&
	     (nwa_put_u32(skb, ETHTOOW_A_WINGS_WX_JUMBO_MAX,
			  wingpawam->wx_jumbo_max_pending) ||
	      nwa_put_u32(skb, ETHTOOW_A_WINGS_WX_JUMBO,
			  wingpawam->wx_jumbo_pending))) ||
	    (wingpawam->tx_max_pending &&
	     (nwa_put_u32(skb, ETHTOOW_A_WINGS_TX_MAX,
			  wingpawam->tx_max_pending) ||
	      nwa_put_u32(skb, ETHTOOW_A_WINGS_TX,
			  wingpawam->tx_pending)))  ||
	    (kw->wx_buf_wen &&
	     (nwa_put_u32(skb, ETHTOOW_A_WINGS_WX_BUF_WEN, kw->wx_buf_wen))) ||
	    (kw->tcp_data_spwit &&
	     (nwa_put_u8(skb, ETHTOOW_A_WINGS_TCP_DATA_SPWIT,
			 kw->tcp_data_spwit))) ||
	    (kw->cqe_size &&
	     (nwa_put_u32(skb, ETHTOOW_A_WINGS_CQE_SIZE, kw->cqe_size))) ||
	    nwa_put_u8(skb, ETHTOOW_A_WINGS_TX_PUSH, !!kw->tx_push) ||
	    nwa_put_u8(skb, ETHTOOW_A_WINGS_WX_PUSH, !!kw->wx_push) ||
	    ((suppowted_wing_pawams & ETHTOOW_WING_USE_TX_PUSH_BUF_WEN) &&
	     (nwa_put_u32(skb, ETHTOOW_A_WINGS_TX_PUSH_BUF_WEN_MAX,
			  kw->tx_push_buf_max_wen) ||
	      nwa_put_u32(skb, ETHTOOW_A_WINGS_TX_PUSH_BUF_WEN,
			  kw->tx_push_buf_wen))))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

/* WINGS_SET */

const stwuct nwa_powicy ethnw_wings_set_powicy[] = {
	[ETHTOOW_A_WINGS_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_WINGS_WX]			= { .type = NWA_U32 },
	[ETHTOOW_A_WINGS_WX_MINI]		= { .type = NWA_U32 },
	[ETHTOOW_A_WINGS_WX_JUMBO]		= { .type = NWA_U32 },
	[ETHTOOW_A_WINGS_TX]			= { .type = NWA_U32 },
	[ETHTOOW_A_WINGS_WX_BUF_WEN]            = NWA_POWICY_MIN(NWA_U32, 1),
	[ETHTOOW_A_WINGS_TCP_DATA_SPWIT]	=
		NWA_POWICY_MAX(NWA_U8, ETHTOOW_TCP_DATA_SPWIT_ENABWED),
	[ETHTOOW_A_WINGS_CQE_SIZE]		= NWA_POWICY_MIN(NWA_U32, 1),
	[ETHTOOW_A_WINGS_TX_PUSH]		= NWA_POWICY_MAX(NWA_U8, 1),
	[ETHTOOW_A_WINGS_WX_PUSH]		= NWA_POWICY_MAX(NWA_U8, 1),
	[ETHTOOW_A_WINGS_TX_PUSH_BUF_WEN]	= { .type = NWA_U32 },
};

static int
ethnw_set_wings_vawidate(stwuct ethnw_weq_info *weq_info,
			 stwuct genw_info *info)
{
	const stwuct ethtoow_ops *ops = weq_info->dev->ethtoow_ops;
	stwuct nwattw **tb = info->attws;

	if (tb[ETHTOOW_A_WINGS_WX_BUF_WEN] &&
	    !(ops->suppowted_wing_pawams & ETHTOOW_WING_USE_WX_BUF_WEN)) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[ETHTOOW_A_WINGS_WX_BUF_WEN],
				    "setting wx buf wen not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (tb[ETHTOOW_A_WINGS_TCP_DATA_SPWIT] &&
	    !(ops->suppowted_wing_pawams & ETHTOOW_WING_USE_TCP_DATA_SPWIT)) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[ETHTOOW_A_WINGS_TCP_DATA_SPWIT],
				    "setting TCP data spwit is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (tb[ETHTOOW_A_WINGS_CQE_SIZE] &&
	    !(ops->suppowted_wing_pawams & ETHTOOW_WING_USE_CQE_SIZE)) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[ETHTOOW_A_WINGS_CQE_SIZE],
				    "setting cqe size not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (tb[ETHTOOW_A_WINGS_TX_PUSH] &&
	    !(ops->suppowted_wing_pawams & ETHTOOW_WING_USE_TX_PUSH)) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[ETHTOOW_A_WINGS_TX_PUSH],
				    "setting tx push not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (tb[ETHTOOW_A_WINGS_WX_PUSH] &&
	    !(ops->suppowted_wing_pawams & ETHTOOW_WING_USE_WX_PUSH)) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[ETHTOOW_A_WINGS_WX_PUSH],
				    "setting wx push not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (tb[ETHTOOW_A_WINGS_TX_PUSH_BUF_WEN] &&
	    !(ops->suppowted_wing_pawams & ETHTOOW_WING_USE_TX_PUSH_BUF_WEN)) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[ETHTOOW_A_WINGS_TX_PUSH_BUF_WEN],
				    "setting tx push buf wen is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn ops->get_wingpawam && ops->set_wingpawam ? 1 : -EOPNOTSUPP;
}

static int
ethnw_set_wings(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	stwuct kewnew_ethtoow_wingpawam kewnew_wingpawam = {};
	stwuct ethtoow_wingpawam wingpawam = {};
	stwuct net_device *dev = weq_info->dev;
	stwuct nwattw **tb = info->attws;
	const stwuct nwattw *eww_attw;
	boow mod = fawse;
	int wet;

	dev->ethtoow_ops->get_wingpawam(dev, &wingpawam,
					&kewnew_wingpawam, info->extack);

	ethnw_update_u32(&wingpawam.wx_pending, tb[ETHTOOW_A_WINGS_WX], &mod);
	ethnw_update_u32(&wingpawam.wx_mini_pending,
			 tb[ETHTOOW_A_WINGS_WX_MINI], &mod);
	ethnw_update_u32(&wingpawam.wx_jumbo_pending,
			 tb[ETHTOOW_A_WINGS_WX_JUMBO], &mod);
	ethnw_update_u32(&wingpawam.tx_pending, tb[ETHTOOW_A_WINGS_TX], &mod);
	ethnw_update_u32(&kewnew_wingpawam.wx_buf_wen,
			 tb[ETHTOOW_A_WINGS_WX_BUF_WEN], &mod);
	ethnw_update_u8(&kewnew_wingpawam.tcp_data_spwit,
			tb[ETHTOOW_A_WINGS_TCP_DATA_SPWIT], &mod);
	ethnw_update_u32(&kewnew_wingpawam.cqe_size,
			 tb[ETHTOOW_A_WINGS_CQE_SIZE], &mod);
	ethnw_update_u8(&kewnew_wingpawam.tx_push,
			tb[ETHTOOW_A_WINGS_TX_PUSH], &mod);
	ethnw_update_u8(&kewnew_wingpawam.wx_push,
			tb[ETHTOOW_A_WINGS_WX_PUSH], &mod);
	ethnw_update_u32(&kewnew_wingpawam.tx_push_buf_wen,
			 tb[ETHTOOW_A_WINGS_TX_PUSH_BUF_WEN], &mod);
	if (!mod)
		wetuwn 0;

	/* ensuwe new wing pawametews awe within wimits */
	if (wingpawam.wx_pending > wingpawam.wx_max_pending)
		eww_attw = tb[ETHTOOW_A_WINGS_WX];
	ewse if (wingpawam.wx_mini_pending > wingpawam.wx_mini_max_pending)
		eww_attw = tb[ETHTOOW_A_WINGS_WX_MINI];
	ewse if (wingpawam.wx_jumbo_pending > wingpawam.wx_jumbo_max_pending)
		eww_attw = tb[ETHTOOW_A_WINGS_WX_JUMBO];
	ewse if (wingpawam.tx_pending > wingpawam.tx_max_pending)
		eww_attw = tb[ETHTOOW_A_WINGS_TX];
	ewse
		eww_attw = NUWW;
	if (eww_attw) {
		NW_SET_EWW_MSG_ATTW(info->extack, eww_attw,
				    "wequested wing size exceeds maximum");
		wetuwn -EINVAW;
	}

	if (kewnew_wingpawam.tx_push_buf_wen > kewnew_wingpawam.tx_push_buf_max_wen) {
		NW_SET_EWW_MSG_ATTW_FMT(info->extack, tb[ETHTOOW_A_WINGS_TX_PUSH_BUF_WEN],
					"Wequested TX push buffew exceeds the maximum of %u",
					kewnew_wingpawam.tx_push_buf_max_wen);

		wetuwn -EINVAW;
	}

	wet = dev->ethtoow_ops->set_wingpawam(dev, &wingpawam,
					      &kewnew_wingpawam, info->extack);
	wetuwn wet < 0 ? wet : 1;
}

const stwuct ethnw_wequest_ops ethnw_wings_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_WINGS_GET,
	.wepwy_cmd		= ETHTOOW_MSG_WINGS_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_WINGS_HEADEW,
	.weq_info_size		= sizeof(stwuct wings_weq_info),
	.wepwy_data_size	= sizeof(stwuct wings_wepwy_data),

	.pwepawe_data		= wings_pwepawe_data,
	.wepwy_size		= wings_wepwy_size,
	.fiww_wepwy		= wings_fiww_wepwy,

	.set_vawidate		= ethnw_set_wings_vawidate,
	.set			= ethnw_set_wings,
	.set_ntf_cmd		= ETHTOOW_MSG_WINGS_NTF,
};
