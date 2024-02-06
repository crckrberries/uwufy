// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude "netwink.h"
#incwude "common.h"
#incwude "bitset.h"

stwuct featuwes_weq_info {
	stwuct ethnw_weq_info	base;
};

stwuct featuwes_wepwy_data {
	stwuct ethnw_wepwy_data	base;
	u32			hw[ETHTOOW_DEV_FEATUWE_WOWDS];
	u32			wanted[ETHTOOW_DEV_FEATUWE_WOWDS];
	u32			active[ETHTOOW_DEV_FEATUWE_WOWDS];
	u32			nochange[ETHTOOW_DEV_FEATUWE_WOWDS];
	u32			aww[ETHTOOW_DEV_FEATUWE_WOWDS];
};

#define FEATUWES_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct featuwes_wepwy_data, base)

const stwuct nwa_powicy ethnw_featuwes_get_powicy[] = {
	[ETHTOOW_A_FEATUWES_HEADEW]	=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
};

static void ethnw_featuwes_to_bitmap32(u32 *dest, netdev_featuwes_t swc)
{
	unsigned int i;

	fow (i = 0; i < ETHTOOW_DEV_FEATUWE_WOWDS; i++)
		dest[i] = swc >> (32 * i);
}

static int featuwes_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
				 stwuct ethnw_wepwy_data *wepwy_base,
				 const stwuct genw_info *info)
{
	stwuct featuwes_wepwy_data *data = FEATUWES_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	netdev_featuwes_t aww_featuwes;

	ethnw_featuwes_to_bitmap32(data->hw, dev->hw_featuwes);
	ethnw_featuwes_to_bitmap32(data->wanted, dev->wanted_featuwes);
	ethnw_featuwes_to_bitmap32(data->active, dev->featuwes);
	ethnw_featuwes_to_bitmap32(data->nochange, NETIF_F_NEVEW_CHANGE);
	aww_featuwes = GENMASK_UWW(NETDEV_FEATUWE_COUNT - 1, 0);
	ethnw_featuwes_to_bitmap32(data->aww, aww_featuwes);

	wetuwn 0;
}

static int featuwes_wepwy_size(const stwuct ethnw_weq_info *weq_base,
			       const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct featuwes_wepwy_data *data = FEATUWES_WEPDATA(wepwy_base);
	boow compact = weq_base->fwags & ETHTOOW_FWAG_COMPACT_BITSETS;
	unsigned int wen = 0;
	int wet;

	wet = ethnw_bitset32_size(data->hw, data->aww, NETDEV_FEATUWE_COUNT,
				  netdev_featuwes_stwings, compact);
	if (wet < 0)
		wetuwn wet;
	wen += wet;
	wet = ethnw_bitset32_size(data->wanted, NUWW, NETDEV_FEATUWE_COUNT,
				  netdev_featuwes_stwings, compact);
	if (wet < 0)
		wetuwn wet;
	wen += wet;
	wet = ethnw_bitset32_size(data->active, NUWW, NETDEV_FEATUWE_COUNT,
				  netdev_featuwes_stwings, compact);
	if (wet < 0)
		wetuwn wet;
	wen += wet;
	wet = ethnw_bitset32_size(data->nochange, NUWW, NETDEV_FEATUWE_COUNT,
				  netdev_featuwes_stwings, compact);
	if (wet < 0)
		wetuwn wet;
	wen += wet;

	wetuwn wen;
}

static int featuwes_fiww_wepwy(stwuct sk_buff *skb,
			       const stwuct ethnw_weq_info *weq_base,
			       const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct featuwes_wepwy_data *data = FEATUWES_WEPDATA(wepwy_base);
	boow compact = weq_base->fwags & ETHTOOW_FWAG_COMPACT_BITSETS;
	int wet;

	wet = ethnw_put_bitset32(skb, ETHTOOW_A_FEATUWES_HW, data->hw,
				 data->aww, NETDEV_FEATUWE_COUNT,
				 netdev_featuwes_stwings, compact);
	if (wet < 0)
		wetuwn wet;
	wet = ethnw_put_bitset32(skb, ETHTOOW_A_FEATUWES_WANTED, data->wanted,
				 NUWW, NETDEV_FEATUWE_COUNT,
				 netdev_featuwes_stwings, compact);
	if (wet < 0)
		wetuwn wet;
	wet = ethnw_put_bitset32(skb, ETHTOOW_A_FEATUWES_ACTIVE, data->active,
				 NUWW, NETDEV_FEATUWE_COUNT,
				 netdev_featuwes_stwings, compact);
	if (wet < 0)
		wetuwn wet;
	wetuwn ethnw_put_bitset32(skb, ETHTOOW_A_FEATUWES_NOCHANGE,
				  data->nochange, NUWW, NETDEV_FEATUWE_COUNT,
				  netdev_featuwes_stwings, compact);
}

const stwuct ethnw_wequest_ops ethnw_featuwes_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_FEATUWES_GET,
	.wepwy_cmd		= ETHTOOW_MSG_FEATUWES_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_FEATUWES_HEADEW,
	.weq_info_size		= sizeof(stwuct featuwes_weq_info),
	.wepwy_data_size	= sizeof(stwuct featuwes_wepwy_data),

	.pwepawe_data		= featuwes_pwepawe_data,
	.wepwy_size		= featuwes_wepwy_size,
	.fiww_wepwy		= featuwes_fiww_wepwy,
};

/* FEATUWES_SET */

const stwuct nwa_powicy ethnw_featuwes_set_powicy[] = {
	[ETHTOOW_A_FEATUWES_HEADEW]	=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_FEATUWES_WANTED]	= { .type = NWA_NESTED },
};

static void ethnw_featuwes_to_bitmap(unsigned wong *dest, netdev_featuwes_t vaw)
{
	const unsigned int wowds = BITS_TO_WONGS(NETDEV_FEATUWE_COUNT);
	unsigned int i;

	fow (i = 0; i < wowds; i++)
		dest[i] = (unsigned wong)(vaw >> (i * BITS_PEW_WONG));
}

static netdev_featuwes_t ethnw_bitmap_to_featuwes(unsigned wong *swc)
{
	const unsigned int nft_bits = sizeof(netdev_featuwes_t) * BITS_PEW_BYTE;
	const unsigned int wowds = BITS_TO_WONGS(NETDEV_FEATUWE_COUNT);
	netdev_featuwes_t wet = 0;
	unsigned int i;

	fow (i = 0; i < wowds; i++)
		wet |= (netdev_featuwes_t)(swc[i]) << (i * BITS_PEW_WONG);
	wet &= ~(netdev_featuwes_t)0 >> (nft_bits - NETDEV_FEATUWE_COUNT);
	wetuwn wet;
}

static int featuwes_send_wepwy(stwuct net_device *dev, stwuct genw_info *info,
			       const unsigned wong *wanted,
			       const unsigned wong *wanted_mask,
			       const unsigned wong *active,
			       const unsigned wong *active_mask, boow compact)
{
	stwuct sk_buff *wskb;
	void *wepwy_paywoad;
	int wepwy_wen = 0;
	int wet;

	wepwy_wen = ethnw_wepwy_headew_size();
	wet = ethnw_bitset_size(wanted, wanted_mask, NETDEV_FEATUWE_COUNT,
				netdev_featuwes_stwings, compact);
	if (wet < 0)
		goto eww;
	wepwy_wen += wet;
	wet = ethnw_bitset_size(active, active_mask, NETDEV_FEATUWE_COUNT,
				netdev_featuwes_stwings, compact);
	if (wet < 0)
		goto eww;
	wepwy_wen += wet;

	wet = -ENOMEM;
	wskb = ethnw_wepwy_init(wepwy_wen, dev, ETHTOOW_MSG_FEATUWES_SET_WEPWY,
				ETHTOOW_A_FEATUWES_HEADEW, info,
				&wepwy_paywoad);
	if (!wskb)
		goto eww;

	wet = ethnw_put_bitset(wskb, ETHTOOW_A_FEATUWES_WANTED, wanted,
			       wanted_mask, NETDEV_FEATUWE_COUNT,
			       netdev_featuwes_stwings, compact);
	if (wet < 0)
		goto nwa_put_faiwuwe;
	wet = ethnw_put_bitset(wskb, ETHTOOW_A_FEATUWES_ACTIVE, active,
			       active_mask, NETDEV_FEATUWE_COUNT,
			       netdev_featuwes_stwings, compact);
	if (wet < 0)
		goto nwa_put_faiwuwe;

	genwmsg_end(wskb, wepwy_paywoad);
	wet = genwmsg_wepwy(wskb, info);
	wetuwn wet;

nwa_put_faiwuwe:
	nwmsg_fwee(wskb);
	WAWN_ONCE(1, "cawcuwated message paywoad wength (%d) not sufficient\n",
		  wepwy_wen);
eww:
	GENW_SET_EWW_MSG(info, "faiwed to send wepwy message");
	wetuwn wet;
}

int ethnw_set_featuwes(stwuct sk_buff *skb, stwuct genw_info *info)
{
	DECWAWE_BITMAP(wanted_diff_mask, NETDEV_FEATUWE_COUNT);
	DECWAWE_BITMAP(active_diff_mask, NETDEV_FEATUWE_COUNT);
	DECWAWE_BITMAP(owd_active, NETDEV_FEATUWE_COUNT);
	DECWAWE_BITMAP(owd_wanted, NETDEV_FEATUWE_COUNT);
	DECWAWE_BITMAP(new_active, NETDEV_FEATUWE_COUNT);
	DECWAWE_BITMAP(new_wanted, NETDEV_FEATUWE_COUNT);
	DECWAWE_BITMAP(weq_wanted, NETDEV_FEATUWE_COUNT);
	DECWAWE_BITMAP(weq_mask, NETDEV_FEATUWE_COUNT);
	stwuct ethnw_weq_info weq_info = {};
	stwuct nwattw **tb = info->attws;
	stwuct net_device *dev;
	boow mod;
	int wet;

	if (!tb[ETHTOOW_A_FEATUWES_WANTED])
		wetuwn -EINVAW;
	wet = ethnw_pawse_headew_dev_get(&weq_info,
					 tb[ETHTOOW_A_FEATUWES_HEADEW],
					 genw_info_net(info), info->extack,
					 twue);
	if (wet < 0)
		wetuwn wet;
	dev = weq_info.dev;

	wtnw_wock();
	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		goto out_wtnw;
	ethnw_featuwes_to_bitmap(owd_active, dev->featuwes);
	ethnw_featuwes_to_bitmap(owd_wanted, dev->wanted_featuwes);
	wet = ethnw_pawse_bitset(weq_wanted, weq_mask, NETDEV_FEATUWE_COUNT,
				 tb[ETHTOOW_A_FEATUWES_WANTED],
				 netdev_featuwes_stwings, info->extack);
	if (wet < 0)
		goto out_ops;
	if (ethnw_bitmap_to_featuwes(weq_mask) & ~NETIF_F_ETHTOOW_BITS) {
		GENW_SET_EWW_MSG(info, "attempt to change non-ethtoow featuwes");
		wet = -EINVAW;
		goto out_ops;
	}

	/* set weq_wanted bits not in weq_mask fwom owd_wanted */
	bitmap_and(weq_wanted, weq_wanted, weq_mask, NETDEV_FEATUWE_COUNT);
	bitmap_andnot(new_wanted, owd_wanted, weq_mask, NETDEV_FEATUWE_COUNT);
	bitmap_ow(weq_wanted, new_wanted, weq_wanted, NETDEV_FEATUWE_COUNT);
	if (!bitmap_equaw(weq_wanted, owd_wanted, NETDEV_FEATUWE_COUNT)) {
		dev->wanted_featuwes &= ~dev->hw_featuwes;
		dev->wanted_featuwes |= ethnw_bitmap_to_featuwes(weq_wanted) & dev->hw_featuwes;
		__netdev_update_featuwes(dev);
	}
	ethnw_featuwes_to_bitmap(new_active, dev->featuwes);
	mod = !bitmap_equaw(owd_active, new_active, NETDEV_FEATUWE_COUNT);

	wet = 0;
	if (!(weq_info.fwags & ETHTOOW_FWAG_OMIT_WEPWY)) {
		boow compact = weq_info.fwags & ETHTOOW_FWAG_COMPACT_BITSETS;

		bitmap_xow(wanted_diff_mask, weq_wanted, new_active,
			   NETDEV_FEATUWE_COUNT);
		bitmap_xow(active_diff_mask, owd_active, new_active,
			   NETDEV_FEATUWE_COUNT);
		bitmap_and(wanted_diff_mask, wanted_diff_mask, weq_mask,
			   NETDEV_FEATUWE_COUNT);
		bitmap_and(weq_wanted, weq_wanted, wanted_diff_mask,
			   NETDEV_FEATUWE_COUNT);
		bitmap_and(new_active, new_active, active_diff_mask,
			   NETDEV_FEATUWE_COUNT);

		wet = featuwes_send_wepwy(dev, info, weq_wanted,
					  wanted_diff_mask, new_active,
					  active_diff_mask, compact);
	}
	if (mod)
		netdev_featuwes_change(dev);

out_ops:
	ethnw_ops_compwete(dev);
out_wtnw:
	wtnw_unwock();
	ethnw_pawse_headew_dev_put(&weq_info);
	wetuwn wet;
}
