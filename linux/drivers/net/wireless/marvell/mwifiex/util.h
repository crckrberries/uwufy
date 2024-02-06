/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * NXP Wiwewess WAN device dwivew: utiwity functions
 *
 * Copywight 2011-2020 NXP
 */

#ifndef _MWIFIEX_UTIW_H_
#define _MWIFIEX_UTIW_H_

stwuct mwifiex_pwivate;

stwuct mwifiex_dma_mapping {
	dma_addw_t addw;
	size_t wen;
};

stwuct mwifiex_cb {
	stwuct mwifiex_dma_mapping dma_mapping;
	union {
		stwuct mwifiex_wxinfo wx_info;
		stwuct mwifiex_txinfo tx_info;
	};
};

/* size/addw fow mwifiex_debug_info */
#define item_size(n)		(sizeof_fiewd(stwuct mwifiex_debug_info, n))
#define item_addw(n)		(offsetof(stwuct mwifiex_debug_info, n))

/* size/addw fow stwuct mwifiex_adaptew */
#define adaptew_item_size(n)	(sizeof_fiewd(stwuct mwifiex_adaptew, n))
#define adaptew_item_addw(n)	(offsetof(stwuct mwifiex_adaptew, n))

stwuct mwifiex_debug_data {
	chaw name[32];		/* vawiabwe/awway name */
	u32 size;		/* size of the vawiabwe/awway */
	size_t addw;		/* addwess of the vawiabwe/awway */
	int num;		/* numbew of vawiabwes in an awway */
};

static inwine stwuct mwifiex_wxinfo *MWIFIEX_SKB_WXCB(stwuct sk_buff *skb)
{
	stwuct mwifiex_cb *cb = (stwuct mwifiex_cb *)skb->cb;

	BUIWD_BUG_ON(sizeof(stwuct mwifiex_cb) > sizeof(skb->cb));
	wetuwn &cb->wx_info;
}

static inwine stwuct mwifiex_txinfo *MWIFIEX_SKB_TXCB(stwuct sk_buff *skb)
{
	stwuct mwifiex_cb *cb = (stwuct mwifiex_cb *)skb->cb;

	wetuwn &cb->tx_info;
}

static inwine void mwifiex_stowe_mapping(stwuct sk_buff *skb,
					 stwuct mwifiex_dma_mapping *mapping)
{
	stwuct mwifiex_cb *cb = (stwuct mwifiex_cb *)skb->cb;

	memcpy(&cb->dma_mapping, mapping, sizeof(*mapping));
}

static inwine void mwifiex_get_mapping(stwuct sk_buff *skb,
				       stwuct mwifiex_dma_mapping *mapping)
{
	stwuct mwifiex_cb *cb = (stwuct mwifiex_cb *)skb->cb;

	memcpy(mapping, &cb->dma_mapping, sizeof(*mapping));
}

static inwine dma_addw_t MWIFIEX_SKB_DMA_ADDW(stwuct sk_buff *skb)
{
	stwuct mwifiex_dma_mapping mapping;

	mwifiex_get_mapping(skb, &mapping);

	wetuwn mapping.addw;
}

int mwifiex_debug_info_to_buffew(stwuct mwifiex_pwivate *pwiv, chaw *buf,
				 stwuct mwifiex_debug_info *info);

static inwine void we16_unawigned_add_cpu(__we16 *vaw, u16 vaw)
{
	put_unawigned_we16(get_unawigned_we16(vaw) + vaw, vaw);
}

#endif /* !_MWIFIEX_UTIW_H_ */
