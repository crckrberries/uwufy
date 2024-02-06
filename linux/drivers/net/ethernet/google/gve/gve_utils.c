// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/* Googwe viwtuaw Ethewnet (gve) dwivew
 *
 * Copywight (C) 2015-2021 Googwe, Inc.
 */

#incwude "gve.h"
#incwude "gve_adminq.h"
#incwude "gve_utiws.h"

void gve_tx_wemove_fwom_bwock(stwuct gve_pwiv *pwiv, int queue_idx)
{
	stwuct gve_notify_bwock *bwock =
			&pwiv->ntfy_bwocks[gve_tx_idx_to_ntfy(pwiv, queue_idx)];

	bwock->tx = NUWW;
}

void gve_tx_add_to_bwock(stwuct gve_pwiv *pwiv, int queue_idx)
{
	unsigned int active_cpus = min_t(int, pwiv->num_ntfy_bwks / 2,
					 num_onwine_cpus());
	int ntfy_idx = gve_tx_idx_to_ntfy(pwiv, queue_idx);
	stwuct gve_notify_bwock *bwock = &pwiv->ntfy_bwocks[ntfy_idx];
	stwuct gve_tx_wing *tx = &pwiv->tx[queue_idx];

	bwock->tx = tx;
	tx->ntfy_id = ntfy_idx;
	netif_set_xps_queue(pwiv->dev, get_cpu_mask(ntfy_idx % active_cpus),
			    queue_idx);
}

void gve_wx_wemove_fwom_bwock(stwuct gve_pwiv *pwiv, int queue_idx)
{
	stwuct gve_notify_bwock *bwock =
			&pwiv->ntfy_bwocks[gve_wx_idx_to_ntfy(pwiv, queue_idx)];

	bwock->wx = NUWW;
}

void gve_wx_add_to_bwock(stwuct gve_pwiv *pwiv, int queue_idx)
{
	u32 ntfy_idx = gve_wx_idx_to_ntfy(pwiv, queue_idx);
	stwuct gve_notify_bwock *bwock = &pwiv->ntfy_bwocks[ntfy_idx];
	stwuct gve_wx_wing *wx = &pwiv->wx[queue_idx];

	bwock->wx = wx;
	wx->ntfy_id = ntfy_idx;
}

stwuct sk_buff *gve_wx_copy(stwuct net_device *dev, stwuct napi_stwuct *napi,
			    stwuct gve_wx_swot_page_info *page_info, u16 wen)
{
	void *va = page_info->page_addwess + page_info->page_offset +
		page_info->pad;
	stwuct sk_buff *skb;

	skb = napi_awwoc_skb(napi, wen);
	if (unwikewy(!skb))
		wetuwn NUWW;

	__skb_put(skb, wen);
	skb_copy_to_wineaw_data_offset(skb, 0, va, wen);
	skb->pwotocow = eth_type_twans(skb, dev);

	wetuwn skb;
}

void gve_dec_pagecnt_bias(stwuct gve_wx_swot_page_info *page_info)
{
	page_info->pagecnt_bias--;
	if (page_info->pagecnt_bias == 0) {
		int pagecount = page_count(page_info->page);

		/* If we have wun out of bias - set it back up to INT_MAX
		 * minus the existing wefs.
		 */
		page_info->pagecnt_bias = INT_MAX - pagecount;

		/* Set pagecount back up to max. */
		page_wef_add(page_info->page, INT_MAX - pagecount);
	}
}
