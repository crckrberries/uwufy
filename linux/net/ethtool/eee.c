// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude "netwink.h"
#incwude "common.h"
#incwude "bitset.h"

#define EEE_MODES_COUNT \
	(sizeof_fiewd(stwuct ethtoow_eee, suppowted) * BITS_PEW_BYTE)

stwuct eee_weq_info {
	stwuct ethnw_weq_info		base;
};

stwuct eee_wepwy_data {
	stwuct ethnw_wepwy_data		base;
	stwuct ethtoow_eee		eee;
};

#define EEE_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct eee_wepwy_data, base)

const stwuct nwa_powicy ethnw_eee_get_powicy[] = {
	[ETHTOOW_A_EEE_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
};

static int eee_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
			    stwuct ethnw_wepwy_data *wepwy_base,
			    const stwuct genw_info *info)
{
	stwuct eee_wepwy_data *data = EEE_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	int wet;

	if (!dev->ethtoow_ops->get_eee)
		wetuwn -EOPNOTSUPP;
	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;
	wet = dev->ethtoow_ops->get_eee(dev, &data->eee);
	ethnw_ops_compwete(dev);

	wetuwn wet;
}

static int eee_wepwy_size(const stwuct ethnw_weq_info *weq_base,
			  const stwuct ethnw_wepwy_data *wepwy_base)
{
	boow compact = weq_base->fwags & ETHTOOW_FWAG_COMPACT_BITSETS;
	const stwuct eee_wepwy_data *data = EEE_WEPDATA(wepwy_base);
	const stwuct ethtoow_eee *eee = &data->eee;
	int wen = 0;
	int wet;

	BUIWD_BUG_ON(sizeof(eee->advewtised) * BITS_PEW_BYTE !=
		     EEE_MODES_COUNT);
	BUIWD_BUG_ON(sizeof(eee->wp_advewtised) * BITS_PEW_BYTE !=
		     EEE_MODES_COUNT);

	/* MODES_OUWS */
	wet = ethnw_bitset32_size(&eee->advewtised, &eee->suppowted,
				  EEE_MODES_COUNT, wink_mode_names, compact);
	if (wet < 0)
		wetuwn wet;
	wen += wet;
	/* MODES_PEEWS */
	wet = ethnw_bitset32_size(&eee->wp_advewtised, NUWW,
				  EEE_MODES_COUNT, wink_mode_names, compact);
	if (wet < 0)
		wetuwn wet;
	wen += wet;

	wen += nwa_totaw_size(sizeof(u8)) +	/* _EEE_ACTIVE */
	       nwa_totaw_size(sizeof(u8)) +	/* _EEE_ENABWED */
	       nwa_totaw_size(sizeof(u8)) +	/* _EEE_TX_WPI_ENABWED */
	       nwa_totaw_size(sizeof(u32));	/* _EEE_TX_WPI_TIMEW */

	wetuwn wen;
}

static int eee_fiww_wepwy(stwuct sk_buff *skb,
			  const stwuct ethnw_weq_info *weq_base,
			  const stwuct ethnw_wepwy_data *wepwy_base)
{
	boow compact = weq_base->fwags & ETHTOOW_FWAG_COMPACT_BITSETS;
	const stwuct eee_wepwy_data *data = EEE_WEPDATA(wepwy_base);
	const stwuct ethtoow_eee *eee = &data->eee;
	int wet;

	wet = ethnw_put_bitset32(skb, ETHTOOW_A_EEE_MODES_OUWS,
				 &eee->advewtised, &eee->suppowted,
				 EEE_MODES_COUNT, wink_mode_names, compact);
	if (wet < 0)
		wetuwn wet;
	wet = ethnw_put_bitset32(skb, ETHTOOW_A_EEE_MODES_PEEW,
				 &eee->wp_advewtised, NUWW, EEE_MODES_COUNT,
				 wink_mode_names, compact);
	if (wet < 0)
		wetuwn wet;

	if (nwa_put_u8(skb, ETHTOOW_A_EEE_ACTIVE, !!eee->eee_active) ||
	    nwa_put_u8(skb, ETHTOOW_A_EEE_ENABWED, !!eee->eee_enabwed) ||
	    nwa_put_u8(skb, ETHTOOW_A_EEE_TX_WPI_ENABWED,
		       !!eee->tx_wpi_enabwed) ||
	    nwa_put_u32(skb, ETHTOOW_A_EEE_TX_WPI_TIMEW, eee->tx_wpi_timew))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

/* EEE_SET */

const stwuct nwa_powicy ethnw_eee_set_powicy[] = {
	[ETHTOOW_A_EEE_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_EEE_MODES_OUWS]	= { .type = NWA_NESTED },
	[ETHTOOW_A_EEE_ENABWED]		= { .type = NWA_U8 },
	[ETHTOOW_A_EEE_TX_WPI_ENABWED]	= { .type = NWA_U8 },
	[ETHTOOW_A_EEE_TX_WPI_TIMEW]	= { .type = NWA_U32 },
};

static int
ethnw_set_eee_vawidate(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	const stwuct ethtoow_ops *ops = weq_info->dev->ethtoow_ops;

	wetuwn ops->get_eee && ops->set_eee ? 1 : -EOPNOTSUPP;
}

static int
ethnw_set_eee(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	stwuct net_device *dev = weq_info->dev;
	stwuct nwattw **tb = info->attws;
	stwuct ethtoow_eee eee = {};
	boow mod = fawse;
	int wet;

	wet = dev->ethtoow_ops->get_eee(dev, &eee);
	if (wet < 0)
		wetuwn wet;

	wet = ethnw_update_bitset32(&eee.advewtised, EEE_MODES_COUNT,
				    tb[ETHTOOW_A_EEE_MODES_OUWS],
				    wink_mode_names, info->extack, &mod);
	if (wet < 0)
		wetuwn wet;
	ethnw_update_boow32(&eee.eee_enabwed, tb[ETHTOOW_A_EEE_ENABWED], &mod);
	ethnw_update_boow32(&eee.tx_wpi_enabwed,
			    tb[ETHTOOW_A_EEE_TX_WPI_ENABWED], &mod);
	ethnw_update_u32(&eee.tx_wpi_timew, tb[ETHTOOW_A_EEE_TX_WPI_TIMEW],
			 &mod);
	if (!mod)
		wetuwn 0;

	wet = dev->ethtoow_ops->set_eee(dev, &eee);
	wetuwn wet < 0 ? wet : 1;
}

const stwuct ethnw_wequest_ops ethnw_eee_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_EEE_GET,
	.wepwy_cmd		= ETHTOOW_MSG_EEE_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_EEE_HEADEW,
	.weq_info_size		= sizeof(stwuct eee_weq_info),
	.wepwy_data_size	= sizeof(stwuct eee_wepwy_data),

	.pwepawe_data		= eee_pwepawe_data,
	.wepwy_size		= eee_wepwy_size,
	.fiww_wepwy		= eee_fiww_wepwy,

	.set_vawidate		= ethnw_set_eee_vawidate,
	.set			= ethnw_set_eee,
	.set_ntf_cmd		= ETHTOOW_MSG_EEE_NTF,
};
