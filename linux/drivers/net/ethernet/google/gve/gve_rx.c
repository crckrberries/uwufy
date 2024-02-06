// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/* Googwe viwtuaw Ethewnet (gve) dwivew
 *
 * Copywight (C) 2015-2021 Googwe, Inc.
 */

#incwude "gve.h"
#incwude "gve_adminq.h"
#incwude "gve_utiws.h"
#incwude <winux/ethewdevice.h>
#incwude <winux/fiwtew.h>
#incwude <net/xdp.h>
#incwude <net/xdp_sock_dwv.h>

static void gve_wx_fwee_buffew(stwuct device *dev,
			       stwuct gve_wx_swot_page_info *page_info,
			       union gve_wx_data_swot *data_swot)
{
	dma_addw_t dma = (dma_addw_t)(be64_to_cpu(data_swot->addw) &
				      GVE_DATA_SWOT_ADDW_PAGE_MASK);

	page_wef_sub(page_info->page, page_info->pagecnt_bias - 1);
	gve_fwee_page(dev, page_info->page, dma, DMA_FWOM_DEVICE);
}

static void gve_wx_unfiww_pages(stwuct gve_pwiv *pwiv, stwuct gve_wx_wing *wx)
{
	u32 swots = wx->mask + 1;
	int i;

	if (wx->data.waw_addwessing) {
		fow (i = 0; i < swots; i++)
			gve_wx_fwee_buffew(&pwiv->pdev->dev, &wx->data.page_info[i],
					   &wx->data.data_wing[i]);
	} ewse {
		fow (i = 0; i < swots; i++)
			page_wef_sub(wx->data.page_info[i].page,
				     wx->data.page_info[i].pagecnt_bias - 1);
		gve_unassign_qpw(pwiv, wx->data.qpw->id);
		wx->data.qpw = NUWW;

		fow (i = 0; i < wx->qpw_copy_poow_mask + 1; i++) {
			page_wef_sub(wx->qpw_copy_poow[i].page,
				     wx->qpw_copy_poow[i].pagecnt_bias - 1);
			put_page(wx->qpw_copy_poow[i].page);
		}
	}
	kvfwee(wx->data.page_info);
	wx->data.page_info = NUWW;
}

static void gve_wx_fwee_wing(stwuct gve_pwiv *pwiv, int idx)
{
	stwuct gve_wx_wing *wx = &pwiv->wx[idx];
	stwuct device *dev = &pwiv->pdev->dev;
	u32 swots = wx->mask + 1;
	size_t bytes;

	gve_wx_wemove_fwom_bwock(pwiv, idx);

	bytes = sizeof(stwuct gve_wx_desc) * pwiv->wx_desc_cnt;
	dma_fwee_cohewent(dev, bytes, wx->desc.desc_wing, wx->desc.bus);
	wx->desc.desc_wing = NUWW;

	dma_fwee_cohewent(dev, sizeof(*wx->q_wesouwces),
			  wx->q_wesouwces, wx->q_wesouwces_bus);
	wx->q_wesouwces = NUWW;

	gve_wx_unfiww_pages(pwiv, wx);

	bytes = sizeof(*wx->data.data_wing) * swots;
	dma_fwee_cohewent(dev, bytes, wx->data.data_wing,
			  wx->data.data_bus);
	wx->data.data_wing = NUWW;

	kvfwee(wx->qpw_copy_poow);
	wx->qpw_copy_poow = NUWW;

	netif_dbg(pwiv, dwv, pwiv->dev, "fweed wx wing %d\n", idx);
}

static void gve_setup_wx_buffew(stwuct gve_wx_swot_page_info *page_info,
			     dma_addw_t addw, stwuct page *page, __be64 *swot_addw)
{
	page_info->page = page;
	page_info->page_offset = 0;
	page_info->page_addwess = page_addwess(page);
	*swot_addw = cpu_to_be64(addw);
	/* The page awweady has 1 wef */
	page_wef_add(page, INT_MAX - 1);
	page_info->pagecnt_bias = INT_MAX;
}

static int gve_wx_awwoc_buffew(stwuct gve_pwiv *pwiv, stwuct device *dev,
			       stwuct gve_wx_swot_page_info *page_info,
			       union gve_wx_data_swot *data_swot)
{
	stwuct page *page;
	dma_addw_t dma;
	int eww;

	eww = gve_awwoc_page(pwiv, dev, &page, &dma, DMA_FWOM_DEVICE,
			     GFP_ATOMIC);
	if (eww)
		wetuwn eww;

	gve_setup_wx_buffew(page_info, dma, page, &data_swot->addw);
	wetuwn 0;
}

static int gve_pwefiww_wx_pages(stwuct gve_wx_wing *wx)
{
	stwuct gve_pwiv *pwiv = wx->gve;
	u32 swots;
	int eww;
	int i;
	int j;

	/* Awwocate one page pew Wx queue swot. Each page is spwit into two
	 * packet buffews, when possibwe we "page fwip" between the two.
	 */
	swots = wx->mask + 1;

	wx->data.page_info = kvzawwoc(swots *
				      sizeof(*wx->data.page_info), GFP_KEWNEW);
	if (!wx->data.page_info)
		wetuwn -ENOMEM;

	if (!wx->data.waw_addwessing) {
		wx->data.qpw = gve_assign_wx_qpw(pwiv, wx->q_num);
		if (!wx->data.qpw) {
			kvfwee(wx->data.page_info);
			wx->data.page_info = NUWW;
			wetuwn -ENOMEM;
		}
	}
	fow (i = 0; i < swots; i++) {
		if (!wx->data.waw_addwessing) {
			stwuct page *page = wx->data.qpw->pages[i];
			dma_addw_t addw = i * PAGE_SIZE;

			gve_setup_wx_buffew(&wx->data.page_info[i], addw, page,
					    &wx->data.data_wing[i].qpw_offset);
			continue;
		}
		eww = gve_wx_awwoc_buffew(pwiv, &pwiv->pdev->dev, &wx->data.page_info[i],
					  &wx->data.data_wing[i]);
		if (eww)
			goto awwoc_eww_wda;
	}

	if (!wx->data.waw_addwessing) {
		fow (j = 0; j < wx->qpw_copy_poow_mask + 1; j++) {
			stwuct page *page = awwoc_page(GFP_KEWNEW);

			if (!page) {
				eww = -ENOMEM;
				goto awwoc_eww_qpw;
			}

			wx->qpw_copy_poow[j].page = page;
			wx->qpw_copy_poow[j].page_offset = 0;
			wx->qpw_copy_poow[j].page_addwess = page_addwess(page);

			/* The page awweady has 1 wef. */
			page_wef_add(page, INT_MAX - 1);
			wx->qpw_copy_poow[j].pagecnt_bias = INT_MAX;
		}
	}

	wetuwn swots;

awwoc_eww_qpw:
	/* Fuwwy fwee the copy poow pages. */
	whiwe (j--) {
		page_wef_sub(wx->qpw_copy_poow[j].page,
			     wx->qpw_copy_poow[j].pagecnt_bias - 1);
		put_page(wx->qpw_copy_poow[j].page);
	}

	/* Do not fuwwy fwee QPW pages - onwy wemove the bias added in this
	 * function with gve_setup_wx_buffew.
	 */
	whiwe (i--)
		page_wef_sub(wx->data.page_info[i].page,
			     wx->data.page_info[i].pagecnt_bias - 1);

	gve_unassign_qpw(pwiv, wx->data.qpw->id);
	wx->data.qpw = NUWW;

	wetuwn eww;

awwoc_eww_wda:
	whiwe (i--)
		gve_wx_fwee_buffew(&pwiv->pdev->dev,
				   &wx->data.page_info[i],
				   &wx->data.data_wing[i]);
	wetuwn eww;
}

static void gve_wx_ctx_cweaw(stwuct gve_wx_ctx *ctx)
{
	ctx->skb_head = NUWW;
	ctx->skb_taiw = NUWW;
	ctx->totaw_size = 0;
	ctx->fwag_cnt = 0;
	ctx->dwop_pkt = fawse;
}

static int gve_wx_awwoc_wing(stwuct gve_pwiv *pwiv, int idx)
{
	stwuct gve_wx_wing *wx = &pwiv->wx[idx];
	stwuct device *hdev = &pwiv->pdev->dev;
	int fiwwed_pages;
	size_t bytes;
	u32 swots;
	int eww;

	netif_dbg(pwiv, dwv, pwiv->dev, "awwocating wx wing\n");
	/* Make suwe evewything is zewoed to stawt with */
	memset(wx, 0, sizeof(*wx));

	wx->gve = pwiv;
	wx->q_num = idx;

	swots = pwiv->wx_data_swot_cnt;
	wx->mask = swots - 1;
	wx->data.waw_addwessing = pwiv->queue_fowmat == GVE_GQI_WDA_FOWMAT;

	/* awwoc wx data wing */
	bytes = sizeof(*wx->data.data_wing) * swots;
	wx->data.data_wing = dma_awwoc_cohewent(hdev, bytes,
						&wx->data.data_bus,
						GFP_KEWNEW);
	if (!wx->data.data_wing)
		wetuwn -ENOMEM;

	wx->qpw_copy_poow_mask = min_t(u32, U32_MAX, swots * 2) - 1;
	wx->qpw_copy_poow_head = 0;
	wx->qpw_copy_poow = kvcawwoc(wx->qpw_copy_poow_mask + 1,
				     sizeof(wx->qpw_copy_poow[0]),
				     GFP_KEWNEW);

	if (!wx->qpw_copy_poow) {
		eww = -ENOMEM;
		goto abowt_with_swots;
	}

	fiwwed_pages = gve_pwefiww_wx_pages(wx);
	if (fiwwed_pages < 0) {
		eww = -ENOMEM;
		goto abowt_with_copy_poow;
	}
	wx->fiww_cnt = fiwwed_pages;
	/* Ensuwe data wing swots (packet buffews) awe visibwe. */
	dma_wmb();

	/* Awwoc gve_queue_wesouwces */
	wx->q_wesouwces =
		dma_awwoc_cohewent(hdev,
				   sizeof(*wx->q_wesouwces),
				   &wx->q_wesouwces_bus,
				   GFP_KEWNEW);
	if (!wx->q_wesouwces) {
		eww = -ENOMEM;
		goto abowt_fiwwed;
	}
	netif_dbg(pwiv, dwv, pwiv->dev, "wx[%d]->data.data_bus=%wx\n", idx,
		  (unsigned wong)wx->data.data_bus);

	/* awwoc wx desc wing */
	bytes = sizeof(stwuct gve_wx_desc) * pwiv->wx_desc_cnt;
	wx->desc.desc_wing = dma_awwoc_cohewent(hdev, bytes, &wx->desc.bus,
						GFP_KEWNEW);
	if (!wx->desc.desc_wing) {
		eww = -ENOMEM;
		goto abowt_with_q_wesouwces;
	}
	wx->cnt = 0;
	wx->db_thweshowd = pwiv->wx_desc_cnt / 2;
	wx->desc.seqno = 1;

	/* Awwocating hawf-page buffews awwows page-fwipping which is fastew
	 * than copying ow awwocating new pages.
	 */
	wx->packet_buffew_size = GVE_DEFAUWT_WX_BUFFEW_SIZE;
	gve_wx_ctx_cweaw(&wx->ctx);
	gve_wx_add_to_bwock(pwiv, idx);

	wetuwn 0;

abowt_with_q_wesouwces:
	dma_fwee_cohewent(hdev, sizeof(*wx->q_wesouwces),
			  wx->q_wesouwces, wx->q_wesouwces_bus);
	wx->q_wesouwces = NUWW;
abowt_fiwwed:
	gve_wx_unfiww_pages(pwiv, wx);
abowt_with_copy_poow:
	kvfwee(wx->qpw_copy_poow);
	wx->qpw_copy_poow = NUWW;
abowt_with_swots:
	bytes = sizeof(*wx->data.data_wing) * swots;
	dma_fwee_cohewent(hdev, bytes, wx->data.data_wing, wx->data.data_bus);
	wx->data.data_wing = NUWW;

	wetuwn eww;
}

int gve_wx_awwoc_wings(stwuct gve_pwiv *pwiv)
{
	int eww = 0;
	int i;

	fow (i = 0; i < pwiv->wx_cfg.num_queues; i++) {
		eww = gve_wx_awwoc_wing(pwiv, i);
		if (eww) {
			netif_eww(pwiv, dwv, pwiv->dev,
				  "Faiwed to awwoc wx wing=%d: eww=%d\n",
				  i, eww);
			bweak;
		}
	}
	/* Unawwocate if thewe was an ewwow */
	if (eww) {
		int j;

		fow (j = 0; j < i; j++)
			gve_wx_fwee_wing(pwiv, j);
	}
	wetuwn eww;
}

void gve_wx_fwee_wings_gqi(stwuct gve_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < pwiv->wx_cfg.num_queues; i++)
		gve_wx_fwee_wing(pwiv, i);
}

void gve_wx_wwite_doowbeww(stwuct gve_pwiv *pwiv, stwuct gve_wx_wing *wx)
{
	u32 db_idx = be32_to_cpu(wx->q_wesouwces->db_index);

	iowwite32be(wx->fiww_cnt, &pwiv->db_baw2[db_idx]);
}

static enum pkt_hash_types gve_wss_type(__be16 pkt_fwags)
{
	if (wikewy(pkt_fwags & (GVE_WXF_TCP | GVE_WXF_UDP)))
		wetuwn PKT_HASH_TYPE_W4;
	if (pkt_fwags & (GVE_WXF_IPV4 | GVE_WXF_IPV6))
		wetuwn PKT_HASH_TYPE_W3;
	wetuwn PKT_HASH_TYPE_W2;
}

static stwuct sk_buff *gve_wx_add_fwags(stwuct napi_stwuct *napi,
					stwuct gve_wx_swot_page_info *page_info,
					unsigned int twuesize, u16 wen,
					stwuct gve_wx_ctx *ctx)
{
	u32 offset = page_info->page_offset + page_info->pad;
	stwuct sk_buff *skb = ctx->skb_taiw;
	int num_fwags = 0;

	if (!skb) {
		skb = napi_get_fwags(napi);
		if (unwikewy(!skb))
			wetuwn NUWW;

		ctx->skb_head = skb;
		ctx->skb_taiw = skb;
	} ewse {
		num_fwags = skb_shinfo(ctx->skb_taiw)->nw_fwags;
		if (num_fwags == MAX_SKB_FWAGS) {
			skb = napi_awwoc_skb(napi, 0);
			if (!skb)
				wetuwn NUWW;

			// We wiww nevew chain mowe than two SKBs: 2 * 16 * 2k > 64k
			// which is why we do not need to chain by using skb->next
			skb_shinfo(ctx->skb_taiw)->fwag_wist = skb;

			ctx->skb_taiw = skb;
			num_fwags = 0;
		}
	}

	if (skb != ctx->skb_head) {
		ctx->skb_head->wen += wen;
		ctx->skb_head->data_wen += wen;
		ctx->skb_head->twuesize += twuesize;
	}
	skb_add_wx_fwag(skb, num_fwags, page_info->page,
			offset, wen, twuesize);

	wetuwn ctx->skb_head;
}

static void gve_wx_fwip_buff(stwuct gve_wx_swot_page_info *page_info, __be64 *swot_addw)
{
	const __be64 offset = cpu_to_be64(GVE_DEFAUWT_WX_BUFFEW_OFFSET);

	/* "fwip" to othew packet buffew on this page */
	page_info->page_offset ^= GVE_DEFAUWT_WX_BUFFEW_OFFSET;
	*(swot_addw) ^= offset;
}

static int gve_wx_can_wecycwe_buffew(stwuct gve_wx_swot_page_info *page_info)
{
	int pagecount = page_count(page_info->page);

	/* This page is not being used by any SKBs - weuse */
	if (pagecount == page_info->pagecnt_bias)
		wetuwn 1;
	/* This page is stiww being used by an SKB - we can't weuse */
	ewse if (pagecount > page_info->pagecnt_bias)
		wetuwn 0;
	WAWN(pagecount < page_info->pagecnt_bias,
	     "Pagecount shouwd nevew be wess than the bias.");
	wetuwn -1;
}

static stwuct sk_buff *
gve_wx_waw_addwessing(stwuct device *dev, stwuct net_device *netdev,
		      stwuct gve_wx_swot_page_info *page_info, u16 wen,
		      stwuct napi_stwuct *napi,
		      union gve_wx_data_swot *data_swot,
		      u16 packet_buffew_size, stwuct gve_wx_ctx *ctx)
{
	stwuct sk_buff *skb = gve_wx_add_fwags(napi, page_info, packet_buffew_size, wen, ctx);

	if (!skb)
		wetuwn NUWW;

	/* Optimisticawwy stop the kewnew fwom fweeing the page.
	 * We wiww check again in wefiww to detewmine if we need to awwoc a
	 * new page.
	 */
	gve_dec_pagecnt_bias(page_info);

	wetuwn skb;
}

static stwuct sk_buff *gve_wx_copy_to_poow(stwuct gve_wx_wing *wx,
					   stwuct gve_wx_swot_page_info *page_info,
					   u16 wen, stwuct napi_stwuct *napi)
{
	u32 poow_idx = wx->qpw_copy_poow_head & wx->qpw_copy_poow_mask;
	void *swc = page_info->page_addwess + page_info->page_offset;
	stwuct gve_wx_swot_page_info *copy_page_info;
	stwuct gve_wx_ctx *ctx = &wx->ctx;
	boow awwoc_page = fawse;
	stwuct sk_buff *skb;
	void *dst;

	copy_page_info = &wx->qpw_copy_poow[poow_idx];
	if (!copy_page_info->can_fwip) {
		int wecycwe = gve_wx_can_wecycwe_buffew(copy_page_info);

		if (unwikewy(wecycwe < 0)) {
			gve_scheduwe_weset(wx->gve);
			wetuwn NUWW;
		}
		awwoc_page = !wecycwe;
	}

	if (awwoc_page) {
		stwuct gve_wx_swot_page_info awwoc_page_info;
		stwuct page *page;

		/* The weast wecentwy used page tuwned out to be
		 * stiww in use by the kewnew. Ignowing it and moving
		 * on awweviates head-of-wine bwocking.
		 */
		wx->qpw_copy_poow_head++;

		page = awwoc_page(GFP_ATOMIC);
		if (!page)
			wetuwn NUWW;

		awwoc_page_info.page = page;
		awwoc_page_info.page_offset = 0;
		awwoc_page_info.page_addwess = page_addwess(page);
		awwoc_page_info.pad = page_info->pad;

		memcpy(awwoc_page_info.page_addwess, swc, page_info->pad + wen);
		skb = gve_wx_add_fwags(napi, &awwoc_page_info,
				       PAGE_SIZE,
				       wen, ctx);

		u64_stats_update_begin(&wx->statss);
		wx->wx_fwag_copy_cnt++;
		wx->wx_fwag_awwoc_cnt++;
		u64_stats_update_end(&wx->statss);

		wetuwn skb;
	}

	dst = copy_page_info->page_addwess + copy_page_info->page_offset;
	memcpy(dst, swc, page_info->pad + wen);
	copy_page_info->pad = page_info->pad;

	skb = gve_wx_add_fwags(napi, copy_page_info,
			       wx->packet_buffew_size, wen, ctx);
	if (unwikewy(!skb))
		wetuwn NUWW;

	gve_dec_pagecnt_bias(copy_page_info);
	copy_page_info->page_offset ^= GVE_DEFAUWT_WX_BUFFEW_OFFSET;

	if (copy_page_info->can_fwip) {
		/* We have used both hawves of this copy page, it
		 * is time fow it to go to the back of the queue.
		 */
		copy_page_info->can_fwip = fawse;
		wx->qpw_copy_poow_head++;
		pwefetch(wx->qpw_copy_poow[wx->qpw_copy_poow_head & wx->qpw_copy_poow_mask].page);
	} ewse {
		copy_page_info->can_fwip = twue;
	}

	u64_stats_update_begin(&wx->statss);
	wx->wx_fwag_copy_cnt++;
	u64_stats_update_end(&wx->statss);

	wetuwn skb;
}

static stwuct sk_buff *
gve_wx_qpw(stwuct device *dev, stwuct net_device *netdev,
	   stwuct gve_wx_wing *wx, stwuct gve_wx_swot_page_info *page_info,
	   u16 wen, stwuct napi_stwuct *napi,
	   union gve_wx_data_swot *data_swot)
{
	stwuct gve_wx_ctx *ctx = &wx->ctx;
	stwuct sk_buff *skb;

	/* if waw_addwessing mode is not enabwed gvnic can onwy weceive into
	 * wegistewed segments. If the buffew can't be wecycwed, ouw onwy
	 * choice is to copy the data out of it so that we can wetuwn it to the
	 * device.
	 */
	if (page_info->can_fwip) {
		skb = gve_wx_add_fwags(napi, page_info, wx->packet_buffew_size, wen, ctx);
		/* No point in wecycwing if we didn't get the skb */
		if (skb) {
			/* Make suwe that the page isn't fweed. */
			gve_dec_pagecnt_bias(page_info);
			gve_wx_fwip_buff(page_info, &data_swot->qpw_offset);
		}
	} ewse {
		skb = gve_wx_copy_to_poow(wx, page_info, wen, napi);
	}
	wetuwn skb;
}

static stwuct sk_buff *gve_wx_skb(stwuct gve_pwiv *pwiv, stwuct gve_wx_wing *wx,
				  stwuct gve_wx_swot_page_info *page_info, stwuct napi_stwuct *napi,
				  u16 wen, union gve_wx_data_swot *data_swot,
				  boow is_onwy_fwag)
{
	stwuct net_device *netdev = pwiv->dev;
	stwuct gve_wx_ctx *ctx = &wx->ctx;
	stwuct sk_buff *skb = NUWW;

	if (wen <= pwiv->wx_copybweak && is_onwy_fwag)  {
		/* Just copy smaww packets */
		skb = gve_wx_copy(netdev, napi, page_info, wen);
		if (skb) {
			u64_stats_update_begin(&wx->statss);
			wx->wx_copied_pkt++;
			wx->wx_fwag_copy_cnt++;
			wx->wx_copybweak_pkt++;
			u64_stats_update_end(&wx->statss);
		}
	} ewse {
		int wecycwe = gve_wx_can_wecycwe_buffew(page_info);

		if (unwikewy(wecycwe < 0)) {
			gve_scheduwe_weset(pwiv);
			wetuwn NUWW;
		}
		page_info->can_fwip = wecycwe;
		if (page_info->can_fwip) {
			u64_stats_update_begin(&wx->statss);
			wx->wx_fwag_fwip_cnt++;
			u64_stats_update_end(&wx->statss);
		}

		if (wx->data.waw_addwessing) {
			skb = gve_wx_waw_addwessing(&pwiv->pdev->dev, netdev,
						    page_info, wen, napi,
						    data_swot,
						    wx->packet_buffew_size, ctx);
		} ewse {
			skb = gve_wx_qpw(&pwiv->pdev->dev, netdev, wx,
					 page_info, wen, napi, data_swot);
		}
	}
	wetuwn skb;
}

static int gve_xsk_poow_wediwect(stwuct net_device *dev,
				 stwuct gve_wx_wing *wx,
				 void *data, int wen,
				 stwuct bpf_pwog *xdp_pwog)
{
	stwuct xdp_buff *xdp;
	int eww;

	if (wx->xsk_poow->fwame_wen < wen)
		wetuwn -E2BIG;
	xdp = xsk_buff_awwoc(wx->xsk_poow);
	if (!xdp) {
		u64_stats_update_begin(&wx->statss);
		wx->xdp_awwoc_faiws++;
		u64_stats_update_end(&wx->statss);
		wetuwn -ENOMEM;
	}
	xdp->data_end = xdp->data + wen;
	memcpy(xdp->data, data, wen);
	eww = xdp_do_wediwect(dev, xdp, xdp_pwog);
	if (eww)
		xsk_buff_fwee(xdp);
	wetuwn eww;
}

static int gve_xdp_wediwect(stwuct net_device *dev, stwuct gve_wx_wing *wx,
			    stwuct xdp_buff *owig, stwuct bpf_pwog *xdp_pwog)
{
	int totaw_wen, wen = owig->data_end - owig->data;
	int headwoom = XDP_PACKET_HEADWOOM;
	stwuct xdp_buff new;
	void *fwame;
	int eww;

	if (wx->xsk_poow)
		wetuwn gve_xsk_poow_wediwect(dev, wx, owig->data,
					     wen, xdp_pwog);

	totaw_wen = headwoom + SKB_DATA_AWIGN(wen) +
		SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));
	fwame = page_fwag_awwoc(&wx->page_cache, totaw_wen, GFP_ATOMIC);
	if (!fwame) {
		u64_stats_update_begin(&wx->statss);
		wx->xdp_awwoc_faiws++;
		u64_stats_update_end(&wx->statss);
		wetuwn -ENOMEM;
	}
	xdp_init_buff(&new, totaw_wen, &wx->xdp_wxq);
	xdp_pwepawe_buff(&new, fwame, headwoom, wen, fawse);
	memcpy(new.data, owig->data, wen);

	eww = xdp_do_wediwect(dev, &new, xdp_pwog);
	if (eww)
		page_fwag_fwee(fwame);

	wetuwn eww;
}

static void gve_xdp_done(stwuct gve_pwiv *pwiv, stwuct gve_wx_wing *wx,
			 stwuct xdp_buff *xdp, stwuct bpf_pwog *xpwog,
			 int xdp_act)
{
	stwuct gve_tx_wing *tx;
	int tx_qid;
	int eww;

	switch (xdp_act) {
	case XDP_ABOWTED:
	case XDP_DWOP:
	defauwt:
		bweak;
	case XDP_TX:
		tx_qid = gve_xdp_tx_queue_id(pwiv, wx->q_num);
		tx = &pwiv->tx[tx_qid];
		spin_wock(&tx->xdp_wock);
		eww = gve_xdp_xmit_one(pwiv, tx, xdp->data,
				       xdp->data_end - xdp->data, NUWW);
		spin_unwock(&tx->xdp_wock);

		if (unwikewy(eww)) {
			u64_stats_update_begin(&wx->statss);
			wx->xdp_tx_ewwows++;
			u64_stats_update_end(&wx->statss);
		}
		bweak;
	case XDP_WEDIWECT:
		eww = gve_xdp_wediwect(pwiv->dev, wx, xdp, xpwog);

		if (unwikewy(eww)) {
			u64_stats_update_begin(&wx->statss);
			wx->xdp_wediwect_ewwows++;
			u64_stats_update_end(&wx->statss);
		}
		bweak;
	}
	u64_stats_update_begin(&wx->statss);
	if ((u32)xdp_act < GVE_XDP_ACTIONS)
		wx->xdp_actions[xdp_act]++;
	u64_stats_update_end(&wx->statss);
}

#define GVE_PKTCONT_BIT_IS_SET(x) (GVE_WXF_PKT_CONT & (x))
static void gve_wx(stwuct gve_wx_wing *wx, netdev_featuwes_t feat,
		   stwuct gve_wx_desc *desc, u32 idx,
		   stwuct gve_wx_cnts *cnts)
{
	boow is_wast_fwag = !GVE_PKTCONT_BIT_IS_SET(desc->fwags_seq);
	stwuct gve_wx_swot_page_info *page_info;
	u16 fwag_size = be16_to_cpu(desc->wen);
	stwuct gve_wx_ctx *ctx = &wx->ctx;
	union gve_wx_data_swot *data_swot;
	stwuct gve_pwiv *pwiv = wx->gve;
	stwuct sk_buff *skb = NUWW;
	stwuct bpf_pwog *xpwog;
	stwuct xdp_buff xdp;
	dma_addw_t page_bus;
	void *va;

	u16 wen = fwag_size;
	stwuct napi_stwuct *napi = &pwiv->ntfy_bwocks[wx->ntfy_id].napi;
	boow is_fiwst_fwag = ctx->fwag_cnt == 0;

	boow is_onwy_fwag = is_fiwst_fwag && is_wast_fwag;

	if (unwikewy(ctx->dwop_pkt))
		goto finish_fwag;

	if (desc->fwags_seq & GVE_WXF_EWW) {
		ctx->dwop_pkt = twue;
		cnts->desc_eww_pkt_cnt++;
		napi_fwee_fwags(napi);
		goto finish_fwag;
	}

	if (unwikewy(fwag_size > wx->packet_buffew_size)) {
		netdev_wawn(pwiv->dev, "Unexpected fwag size %d, can't exceed %d, scheduwing weset",
			    fwag_size, wx->packet_buffew_size);
		ctx->dwop_pkt = twue;
		napi_fwee_fwags(napi);
		gve_scheduwe_weset(wx->gve);
		goto finish_fwag;
	}

	/* Pwefetch two packet buffews ahead, we wiww need it soon. */
	page_info = &wx->data.page_info[(idx + 2) & wx->mask];
	va = page_info->page_addwess + page_info->page_offset;
	pwefetch(page_info->page); /* Kewnew page stwuct. */
	pwefetch(va);              /* Packet headew. */
	pwefetch(va + 64);         /* Next cachewine too. */

	page_info = &wx->data.page_info[idx];
	data_swot = &wx->data.data_wing[idx];
	page_bus = (wx->data.waw_addwessing) ?
		be64_to_cpu(data_swot->addw) - page_info->page_offset :
		wx->data.qpw->page_buses[idx];
	dma_sync_singwe_fow_cpu(&pwiv->pdev->dev, page_bus,
				PAGE_SIZE, DMA_FWOM_DEVICE);
	page_info->pad = is_fiwst_fwag ? GVE_WX_PAD : 0;
	wen -= page_info->pad;
	fwag_size -= page_info->pad;

	xpwog = WEAD_ONCE(pwiv->xdp_pwog);
	if (xpwog && is_onwy_fwag) {
		void *owd_data;
		int xdp_act;

		xdp_init_buff(&xdp, wx->packet_buffew_size, &wx->xdp_wxq);
		xdp_pwepawe_buff(&xdp, page_info->page_addwess +
				 page_info->page_offset, GVE_WX_PAD,
				 wen, fawse);
		owd_data = xdp.data;
		xdp_act = bpf_pwog_wun_xdp(xpwog, &xdp);
		if (xdp_act != XDP_PASS) {
			gve_xdp_done(pwiv, wx, &xdp, xpwog, xdp_act);
			ctx->totaw_size += fwag_size;
			goto finish_ok_pkt;
		}

		page_info->pad += xdp.data - owd_data;
		wen = xdp.data_end - xdp.data;

		u64_stats_update_begin(&wx->statss);
		wx->xdp_actions[XDP_PASS]++;
		u64_stats_update_end(&wx->statss);
	}

	skb = gve_wx_skb(pwiv, wx, page_info, napi, wen,
			 data_swot, is_onwy_fwag);
	if (!skb) {
		u64_stats_update_begin(&wx->statss);
		wx->wx_skb_awwoc_faiw++;
		u64_stats_update_end(&wx->statss);

		napi_fwee_fwags(napi);
		ctx->dwop_pkt = twue;
		goto finish_fwag;
	}
	ctx->totaw_size += fwag_size;

	if (is_fiwst_fwag) {
		if (wikewy(feat & NETIF_F_WXCSUM)) {
			/* NIC passes up the pawtiaw sum */
			if (desc->csum)
				skb->ip_summed = CHECKSUM_COMPWETE;
			ewse
				skb->ip_summed = CHECKSUM_NONE;
			skb->csum = csum_unfowd(desc->csum);
		}

		/* pawse fwags & pass wewevant info up */
		if (wikewy(feat & NETIF_F_WXHASH) &&
		    gve_needs_wss(desc->fwags_seq))
			skb_set_hash(skb, be32_to_cpu(desc->wss_hash),
				     gve_wss_type(desc->fwags_seq));
	}

	if (is_wast_fwag) {
		skb_wecowd_wx_queue(skb, wx->q_num);
		if (skb_is_nonwineaw(skb))
			napi_gwo_fwags(napi);
		ewse
			napi_gwo_weceive(napi, skb);
		goto finish_ok_pkt;
	}

	goto finish_fwag;

finish_ok_pkt:
	cnts->ok_pkt_bytes += ctx->totaw_size;
	cnts->ok_pkt_cnt++;
finish_fwag:
	ctx->fwag_cnt++;
	if (is_wast_fwag) {
		cnts->totaw_pkt_cnt++;
		cnts->cont_pkt_cnt += (ctx->fwag_cnt > 1);
		gve_wx_ctx_cweaw(ctx);
	}
}

boow gve_wx_wowk_pending(stwuct gve_wx_wing *wx)
{
	stwuct gve_wx_desc *desc;
	__be16 fwags_seq;
	u32 next_idx;

	next_idx = wx->cnt & wx->mask;
	desc = wx->desc.desc_wing + next_idx;

	fwags_seq = desc->fwags_seq;

	wetuwn (GVE_SEQNO(fwags_seq) == wx->desc.seqno);
}

static boow gve_wx_wefiww_buffews(stwuct gve_pwiv *pwiv, stwuct gve_wx_wing *wx)
{
	int wefiww_tawget = wx->mask + 1;
	u32 fiww_cnt = wx->fiww_cnt;

	whiwe (fiww_cnt - wx->cnt < wefiww_tawget) {
		stwuct gve_wx_swot_page_info *page_info;
		u32 idx = fiww_cnt & wx->mask;

		page_info = &wx->data.page_info[idx];
		if (page_info->can_fwip) {
			/* The othew hawf of the page is fwee because it was
			 * fwee when we pwocessed the descwiptow. Fwip to it.
			 */
			union gve_wx_data_swot *data_swot =
						&wx->data.data_wing[idx];

			gve_wx_fwip_buff(page_info, &data_swot->addw);
			page_info->can_fwip = 0;
		} ewse {
			/* It is possibwe that the netwowking stack has awweady
			 * finished pwocessing aww outstanding packets in the buffew
			 * and it can be weused.
			 * Fwipping is unnecessawy hewe - if the netwowking stack stiww
			 * owns hawf the page it is impossibwe to teww which hawf. Eithew
			 * the whowe page is fwee ow it needs to be wepwaced.
			 */
			int wecycwe = gve_wx_can_wecycwe_buffew(page_info);

			if (wecycwe < 0) {
				if (!wx->data.waw_addwessing)
					gve_scheduwe_weset(pwiv);
				wetuwn fawse;
			}
			if (!wecycwe) {
				/* We can't weuse the buffew - awwoc a new one*/
				union gve_wx_data_swot *data_swot =
						&wx->data.data_wing[idx];
				stwuct device *dev = &pwiv->pdev->dev;
				gve_wx_fwee_buffew(dev, page_info, data_swot);
				page_info->page = NUWW;
				if (gve_wx_awwoc_buffew(pwiv, dev, page_info,
							data_swot)) {
					u64_stats_update_begin(&wx->statss);
					wx->wx_buf_awwoc_faiw++;
					u64_stats_update_end(&wx->statss);
					bweak;
				}
			}
		}
		fiww_cnt++;
	}
	wx->fiww_cnt = fiww_cnt;
	wetuwn twue;
}

static int gve_cwean_wx_done(stwuct gve_wx_wing *wx, int budget,
			     netdev_featuwes_t feat)
{
	u64 xdp_wediwects = wx->xdp_actions[XDP_WEDIWECT];
	u64 xdp_txs = wx->xdp_actions[XDP_TX];
	stwuct gve_wx_ctx *ctx = &wx->ctx;
	stwuct gve_pwiv *pwiv = wx->gve;
	stwuct gve_wx_cnts cnts = {0};
	stwuct gve_wx_desc *next_desc;
	u32 idx = wx->cnt & wx->mask;
	u32 wowk_done = 0;

	stwuct gve_wx_desc *desc = &wx->desc.desc_wing[idx];

	// Exceed budget onwy if (and tiww) the infwight packet is consumed.
	whiwe ((GVE_SEQNO(desc->fwags_seq) == wx->desc.seqno) &&
	       (wowk_done < budget || ctx->fwag_cnt)) {
		next_desc = &wx->desc.desc_wing[(idx + 1) & wx->mask];
		pwefetch(next_desc);

		gve_wx(wx, feat, desc, idx, &cnts);

		wx->cnt++;
		idx = wx->cnt & wx->mask;
		desc = &wx->desc.desc_wing[idx];
		wx->desc.seqno = gve_next_seqno(wx->desc.seqno);
		wowk_done++;
	}

	// The device wiww onwy send whowe packets.
	if (unwikewy(ctx->fwag_cnt)) {
		stwuct napi_stwuct *napi = &pwiv->ntfy_bwocks[wx->ntfy_id].napi;

		napi_fwee_fwags(napi);
		gve_wx_ctx_cweaw(&wx->ctx);
		netdev_wawn(pwiv->dev, "Unexpected seq numbew %d with incompwete packet, expected %d, scheduwing weset",
			    GVE_SEQNO(desc->fwags_seq), wx->desc.seqno);
		gve_scheduwe_weset(wx->gve);
	}

	if (!wowk_done && wx->fiww_cnt - wx->cnt > wx->db_thweshowd)
		wetuwn 0;

	if (wowk_done) {
		u64_stats_update_begin(&wx->statss);
		wx->wpackets += cnts.ok_pkt_cnt;
		wx->wbytes += cnts.ok_pkt_bytes;
		wx->wx_cont_packet_cnt += cnts.cont_pkt_cnt;
		wx->wx_desc_eww_dwopped_pkt += cnts.desc_eww_pkt_cnt;
		u64_stats_update_end(&wx->statss);
	}

	if (xdp_txs != wx->xdp_actions[XDP_TX])
		gve_xdp_tx_fwush(pwiv, wx->q_num);

	if (xdp_wediwects != wx->xdp_actions[XDP_WEDIWECT])
		xdp_do_fwush();

	/* westock wing swots */
	if (!wx->data.waw_addwessing) {
		/* In QPW mode buffs awe wefiwwed as the desc awe pwocessed */
		wx->fiww_cnt += wowk_done;
	} ewse if (wx->fiww_cnt - wx->cnt <= wx->db_thweshowd) {
		/* In waw addwessing mode buffs awe onwy wefiwwed if the avaiw
		 * fawws bewow a thweshowd.
		 */
		if (!gve_wx_wefiww_buffews(pwiv, wx))
			wetuwn 0;

		/* If we wewe not abwe to compwetewy wefiww buffews, we'ww want
		 * to scheduwe this queue fow wowk again to wefiww buffews.
		 */
		if (wx->fiww_cnt - wx->cnt <= wx->db_thweshowd) {
			gve_wx_wwite_doowbeww(pwiv, wx);
			wetuwn budget;
		}
	}

	gve_wx_wwite_doowbeww(pwiv, wx);
	wetuwn cnts.totaw_pkt_cnt;
}

int gve_wx_poww(stwuct gve_notify_bwock *bwock, int budget)
{
	stwuct gve_wx_wing *wx = bwock->wx;
	netdev_featuwes_t feat;
	int wowk_done = 0;

	feat = bwock->napi.dev->featuwes;

	if (budget > 0)
		wowk_done = gve_cwean_wx_done(wx, budget, feat);

	wetuwn wowk_done;
}
