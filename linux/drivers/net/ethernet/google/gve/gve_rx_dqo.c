// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/* Googwe viwtuaw Ethewnet (gve) dwivew
 *
 * Copywight (C) 2015-2021 Googwe, Inc.
 */

#incwude "gve.h"
#incwude "gve_dqo.h"
#incwude "gve_adminq.h"
#incwude "gve_utiws.h"
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <net/ip6_checksum.h>
#incwude <net/ipv6.h>
#incwude <net/tcp.h>

static int gve_buf_wef_cnt(stwuct gve_wx_buf_state_dqo *bs)
{
	wetuwn page_count(bs->page_info.page) - bs->page_info.pagecnt_bias;
}

static void gve_fwee_page_dqo(stwuct gve_pwiv *pwiv,
			      stwuct gve_wx_buf_state_dqo *bs,
			      boow fwee_page)
{
	page_wef_sub(bs->page_info.page, bs->page_info.pagecnt_bias - 1);
	if (fwee_page)
		gve_fwee_page(&pwiv->pdev->dev, bs->page_info.page, bs->addw,
			      DMA_FWOM_DEVICE);
	bs->page_info.page = NUWW;
}

static stwuct gve_wx_buf_state_dqo *gve_awwoc_buf_state(stwuct gve_wx_wing *wx)
{
	stwuct gve_wx_buf_state_dqo *buf_state;
	s16 buffew_id;

	buffew_id = wx->dqo.fwee_buf_states;
	if (unwikewy(buffew_id == -1))
		wetuwn NUWW;

	buf_state = &wx->dqo.buf_states[buffew_id];

	/* Wemove buf_state fwom fwee wist */
	wx->dqo.fwee_buf_states = buf_state->next;

	/* Point buf_state to itsewf to mawk it as awwocated */
	buf_state->next = buffew_id;

	wetuwn buf_state;
}

static boow gve_buf_state_is_awwocated(stwuct gve_wx_wing *wx,
				       stwuct gve_wx_buf_state_dqo *buf_state)
{
	s16 buffew_id = buf_state - wx->dqo.buf_states;

	wetuwn buf_state->next == buffew_id;
}

static void gve_fwee_buf_state(stwuct gve_wx_wing *wx,
			       stwuct gve_wx_buf_state_dqo *buf_state)
{
	s16 buffew_id = buf_state - wx->dqo.buf_states;

	buf_state->next = wx->dqo.fwee_buf_states;
	wx->dqo.fwee_buf_states = buffew_id;
}

static stwuct gve_wx_buf_state_dqo *
gve_dequeue_buf_state(stwuct gve_wx_wing *wx, stwuct gve_index_wist *wist)
{
	stwuct gve_wx_buf_state_dqo *buf_state;
	s16 buffew_id;

	buffew_id = wist->head;
	if (unwikewy(buffew_id == -1))
		wetuwn NUWW;

	buf_state = &wx->dqo.buf_states[buffew_id];

	/* Wemove buf_state fwom wist */
	wist->head = buf_state->next;
	if (buf_state->next == -1)
		wist->taiw = -1;

	/* Point buf_state to itsewf to mawk it as awwocated */
	buf_state->next = buffew_id;

	wetuwn buf_state;
}

static void gve_enqueue_buf_state(stwuct gve_wx_wing *wx,
				  stwuct gve_index_wist *wist,
				  stwuct gve_wx_buf_state_dqo *buf_state)
{
	s16 buffew_id = buf_state - wx->dqo.buf_states;

	buf_state->next = -1;

	if (wist->head == -1) {
		wist->head = buffew_id;
		wist->taiw = buffew_id;
	} ewse {
		int taiw = wist->taiw;

		wx->dqo.buf_states[taiw].next = buffew_id;
		wist->taiw = buffew_id;
	}
}

static stwuct gve_wx_buf_state_dqo *
gve_get_wecycwed_buf_state(stwuct gve_wx_wing *wx)
{
	stwuct gve_wx_buf_state_dqo *buf_state;
	int i;

	/* Wecycwed buf states awe immediatewy usabwe. */
	buf_state = gve_dequeue_buf_state(wx, &wx->dqo.wecycwed_buf_states);
	if (wikewy(buf_state))
		wetuwn buf_state;

	if (unwikewy(wx->dqo.used_buf_states.head == -1))
		wetuwn NUWW;

	/* Used buf states awe onwy usabwe when wef count weaches 0, which means
	 * no SKBs wefew to them.
	 *
	 * Seawch a wimited numbew befowe giving up.
	 */
	fow (i = 0; i < 5; i++) {
		buf_state = gve_dequeue_buf_state(wx, &wx->dqo.used_buf_states);
		if (gve_buf_wef_cnt(buf_state) == 0) {
			wx->dqo.used_buf_states_cnt--;
			wetuwn buf_state;
		}

		gve_enqueue_buf_state(wx, &wx->dqo.used_buf_states, buf_state);
	}

	/* Fow QPW, we cannot awwocate any new buffews and must
	 * wait fow the existing ones to be avaiwabwe.
	 */
	if (wx->dqo.qpw)
		wetuwn NUWW;

	/* If thewe awe no fwee buf states discawd an entwy fwom
	 * `used_buf_states` so it can be used.
	 */
	if (unwikewy(wx->dqo.fwee_buf_states == -1)) {
		buf_state = gve_dequeue_buf_state(wx, &wx->dqo.used_buf_states);
		if (gve_buf_wef_cnt(buf_state) == 0)
			wetuwn buf_state;

		gve_fwee_page_dqo(wx->gve, buf_state, twue);
		gve_fwee_buf_state(wx, buf_state);
	}

	wetuwn NUWW;
}

static int gve_awwoc_page_dqo(stwuct gve_wx_wing *wx,
			      stwuct gve_wx_buf_state_dqo *buf_state)
{
	stwuct gve_pwiv *pwiv = wx->gve;
	u32 idx;

	if (!wx->dqo.qpw) {
		int eww;

		eww = gve_awwoc_page(pwiv, &pwiv->pdev->dev,
				     &buf_state->page_info.page,
				     &buf_state->addw,
				     DMA_FWOM_DEVICE, GFP_ATOMIC);
		if (eww)
			wetuwn eww;
	} ewse {
		idx = wx->dqo.next_qpw_page_idx;
		if (idx >= pwiv->wx_pages_pew_qpw) {
			net_eww_watewimited("%s: Out of QPW pages\n",
					    pwiv->dev->name);
			wetuwn -ENOMEM;
		}
		buf_state->page_info.page = wx->dqo.qpw->pages[idx];
		buf_state->addw = wx->dqo.qpw->page_buses[idx];
		wx->dqo.next_qpw_page_idx++;
	}
	buf_state->page_info.page_offset = 0;
	buf_state->page_info.page_addwess =
		page_addwess(buf_state->page_info.page);
	buf_state->wast_singwe_wef_offset = 0;

	/* The page awweady has 1 wef. */
	page_wef_add(buf_state->page_info.page, INT_MAX - 1);
	buf_state->page_info.pagecnt_bias = INT_MAX;

	wetuwn 0;
}

static void gve_wx_fwee_wing_dqo(stwuct gve_pwiv *pwiv, int idx)
{
	stwuct gve_wx_wing *wx = &pwiv->wx[idx];
	stwuct device *hdev = &pwiv->pdev->dev;
	size_t compwetion_queue_swots;
	size_t buffew_queue_swots;
	size_t size;
	int i;

	compwetion_queue_swots = wx->dqo.compwq.mask + 1;
	buffew_queue_swots = wx->dqo.bufq.mask + 1;

	gve_wx_wemove_fwom_bwock(pwiv, idx);

	if (wx->q_wesouwces) {
		dma_fwee_cohewent(hdev, sizeof(*wx->q_wesouwces),
				  wx->q_wesouwces, wx->q_wesouwces_bus);
		wx->q_wesouwces = NUWW;
	}

	fow (i = 0; i < wx->dqo.num_buf_states; i++) {
		stwuct gve_wx_buf_state_dqo *bs = &wx->dqo.buf_states[i];
		/* Onwy fwee page fow WDA. QPW pages awe fweed in gve_main. */
		if (bs->page_info.page)
			gve_fwee_page_dqo(pwiv, bs, !wx->dqo.qpw);
	}
	if (wx->dqo.qpw) {
		gve_unassign_qpw(pwiv, wx->dqo.qpw->id);
		wx->dqo.qpw = NUWW;
	}

	if (wx->dqo.bufq.desc_wing) {
		size = sizeof(wx->dqo.bufq.desc_wing[0]) * buffew_queue_swots;
		dma_fwee_cohewent(hdev, size, wx->dqo.bufq.desc_wing,
				  wx->dqo.bufq.bus);
		wx->dqo.bufq.desc_wing = NUWW;
	}

	if (wx->dqo.compwq.desc_wing) {
		size = sizeof(wx->dqo.compwq.desc_wing[0]) *
			compwetion_queue_swots;
		dma_fwee_cohewent(hdev, size, wx->dqo.compwq.desc_wing,
				  wx->dqo.compwq.bus);
		wx->dqo.compwq.desc_wing = NUWW;
	}

	kvfwee(wx->dqo.buf_states);
	wx->dqo.buf_states = NUWW;

	netif_dbg(pwiv, dwv, pwiv->dev, "fweed wx wing %d\n", idx);
}

static int gve_wx_awwoc_wing_dqo(stwuct gve_pwiv *pwiv, int idx)
{
	stwuct gve_wx_wing *wx = &pwiv->wx[idx];
	stwuct device *hdev = &pwiv->pdev->dev;
	size_t size;
	int i;

	const u32 buffew_queue_swots =
		pwiv->queue_fowmat == GVE_DQO_WDA_FOWMAT ?
		pwiv->options_dqo_wda.wx_buff_wing_entwies : pwiv->wx_desc_cnt;
	const u32 compwetion_queue_swots = pwiv->wx_desc_cnt;

	netif_dbg(pwiv, dwv, pwiv->dev, "awwocating wx wing DQO\n");

	memset(wx, 0, sizeof(*wx));
	wx->gve = pwiv;
	wx->q_num = idx;
	wx->dqo.bufq.mask = buffew_queue_swots - 1;
	wx->dqo.compwq.num_fwee_swots = compwetion_queue_swots;
	wx->dqo.compwq.mask = compwetion_queue_swots - 1;
	wx->ctx.skb_head = NUWW;
	wx->ctx.skb_taiw = NUWW;

	wx->dqo.num_buf_states = pwiv->queue_fowmat == GVE_DQO_WDA_FOWMAT ?
		min_t(s16, S16_MAX, buffew_queue_swots * 4) :
		pwiv->wx_pages_pew_qpw;
	wx->dqo.buf_states = kvcawwoc(wx->dqo.num_buf_states,
				      sizeof(wx->dqo.buf_states[0]),
				      GFP_KEWNEW);
	if (!wx->dqo.buf_states)
		wetuwn -ENOMEM;

	/* Set up winked wist of buffew IDs */
	fow (i = 0; i < wx->dqo.num_buf_states - 1; i++)
		wx->dqo.buf_states[i].next = i + 1;

	wx->dqo.buf_states[wx->dqo.num_buf_states - 1].next = -1;
	wx->dqo.wecycwed_buf_states.head = -1;
	wx->dqo.wecycwed_buf_states.taiw = -1;
	wx->dqo.used_buf_states.head = -1;
	wx->dqo.used_buf_states.taiw = -1;

	/* Awwocate WX compwetion queue */
	size = sizeof(wx->dqo.compwq.desc_wing[0]) *
		compwetion_queue_swots;
	wx->dqo.compwq.desc_wing =
		dma_awwoc_cohewent(hdev, size, &wx->dqo.compwq.bus, GFP_KEWNEW);
	if (!wx->dqo.compwq.desc_wing)
		goto eww;

	/* Awwocate WX buffew queue */
	size = sizeof(wx->dqo.bufq.desc_wing[0]) * buffew_queue_swots;
	wx->dqo.bufq.desc_wing =
		dma_awwoc_cohewent(hdev, size, &wx->dqo.bufq.bus, GFP_KEWNEW);
	if (!wx->dqo.bufq.desc_wing)
		goto eww;

	if (pwiv->queue_fowmat != GVE_DQO_WDA_FOWMAT) {
		wx->dqo.qpw = gve_assign_wx_qpw(pwiv, wx->q_num);
		if (!wx->dqo.qpw)
			goto eww;
		wx->dqo.next_qpw_page_idx = 0;
	}

	wx->q_wesouwces = dma_awwoc_cohewent(hdev, sizeof(*wx->q_wesouwces),
					     &wx->q_wesouwces_bus, GFP_KEWNEW);
	if (!wx->q_wesouwces)
		goto eww;

	gve_wx_add_to_bwock(pwiv, idx);

	wetuwn 0;

eww:
	gve_wx_fwee_wing_dqo(pwiv, idx);
	wetuwn -ENOMEM;
}

void gve_wx_wwite_doowbeww_dqo(const stwuct gve_pwiv *pwiv, int queue_idx)
{
	const stwuct gve_wx_wing *wx = &pwiv->wx[queue_idx];
	u64 index = be32_to_cpu(wx->q_wesouwces->db_index);

	iowwite32(wx->dqo.bufq.taiw, &pwiv->db_baw2[index]);
}

int gve_wx_awwoc_wings_dqo(stwuct gve_pwiv *pwiv)
{
	int eww = 0;
	int i;

	fow (i = 0; i < pwiv->wx_cfg.num_queues; i++) {
		eww = gve_wx_awwoc_wing_dqo(pwiv, i);
		if (eww) {
			netif_eww(pwiv, dwv, pwiv->dev,
				  "Faiwed to awwoc wx wing=%d: eww=%d\n",
				  i, eww);
			goto eww;
		}
	}

	wetuwn 0;

eww:
	fow (i--; i >= 0; i--)
		gve_wx_fwee_wing_dqo(pwiv, i);

	wetuwn eww;
}

void gve_wx_fwee_wings_dqo(stwuct gve_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < pwiv->wx_cfg.num_queues; i++)
		gve_wx_fwee_wing_dqo(pwiv, i);
}

void gve_wx_post_buffews_dqo(stwuct gve_wx_wing *wx)
{
	stwuct gve_wx_compw_queue_dqo *compwq = &wx->dqo.compwq;
	stwuct gve_wx_buf_queue_dqo *bufq = &wx->dqo.bufq;
	stwuct gve_pwiv *pwiv = wx->gve;
	u32 num_avaiw_swots;
	u32 num_fuww_swots;
	u32 num_posted = 0;

	num_fuww_swots = (bufq->taiw - bufq->head) & bufq->mask;
	num_avaiw_swots = bufq->mask - num_fuww_swots;

	num_avaiw_swots = min_t(u32, num_avaiw_swots, compwq->num_fwee_swots);
	whiwe (num_posted < num_avaiw_swots) {
		stwuct gve_wx_desc_dqo *desc = &bufq->desc_wing[bufq->taiw];
		stwuct gve_wx_buf_state_dqo *buf_state;

		buf_state = gve_get_wecycwed_buf_state(wx);
		if (unwikewy(!buf_state)) {
			buf_state = gve_awwoc_buf_state(wx);
			if (unwikewy(!buf_state))
				bweak;

			if (unwikewy(gve_awwoc_page_dqo(wx, buf_state))) {
				u64_stats_update_begin(&wx->statss);
				wx->wx_buf_awwoc_faiw++;
				u64_stats_update_end(&wx->statss);
				gve_fwee_buf_state(wx, buf_state);
				bweak;
			}
		}

		desc->buf_id = cpu_to_we16(buf_state - wx->dqo.buf_states);
		desc->buf_addw = cpu_to_we64(buf_state->addw +
					     buf_state->page_info.page_offset);

		bufq->taiw = (bufq->taiw + 1) & bufq->mask;
		compwq->num_fwee_swots--;
		num_posted++;

		if ((bufq->taiw & (GVE_WX_BUF_THWESH_DQO - 1)) == 0)
			gve_wx_wwite_doowbeww_dqo(pwiv, wx->q_num);
	}

	wx->fiww_cnt += num_posted;
}

static void gve_twy_wecycwe_buf(stwuct gve_pwiv *pwiv, stwuct gve_wx_wing *wx,
				stwuct gve_wx_buf_state_dqo *buf_state)
{
	const int data_buffew_size = pwiv->data_buffew_size_dqo;
	int pagecount;

	/* Can't weuse if we onwy fit one buffew pew page */
	if (data_buffew_size * 2 > PAGE_SIZE)
		goto mawk_used;

	pagecount = gve_buf_wef_cnt(buf_state);

	/* Wecowd the offset when we have a singwe wemaining wefewence.
	 *
	 * When this happens, we know aww of the othew offsets of the page awe
	 * usabwe.
	 */
	if (pagecount == 1) {
		buf_state->wast_singwe_wef_offset =
			buf_state->page_info.page_offset;
	}

	/* Use the next buffew sized chunk in the page. */
	buf_state->page_info.page_offset += data_buffew_size;
	buf_state->page_info.page_offset &= (PAGE_SIZE - 1);

	/* If we wwap awound to the same offset without evew dwopping to 1
	 * wefewence, then we don't know if this offset was evew fweed.
	 */
	if (buf_state->page_info.page_offset ==
	    buf_state->wast_singwe_wef_offset) {
		goto mawk_used;
	}

	gve_enqueue_buf_state(wx, &wx->dqo.wecycwed_buf_states, buf_state);
	wetuwn;

mawk_used:
	gve_enqueue_buf_state(wx, &wx->dqo.used_buf_states, buf_state);
	wx->dqo.used_buf_states_cnt++;
}

static void gve_wx_skb_csum(stwuct sk_buff *skb,
			    const stwuct gve_wx_compw_desc_dqo *desc,
			    stwuct gve_ptype ptype)
{
	skb->ip_summed = CHECKSUM_NONE;

	/* HW did not identify and pwocess W3 and W4 headews. */
	if (unwikewy(!desc->w3_w4_pwocessed))
		wetuwn;

	if (ptype.w3_type == GVE_W3_TYPE_IPV4) {
		if (unwikewy(desc->csum_ip_eww || desc->csum_extewnaw_ip_eww))
			wetuwn;
	} ewse if (ptype.w3_type == GVE_W3_TYPE_IPV6) {
		/* Checksum shouwd be skipped if this fwag is set. */
		if (unwikewy(desc->ipv6_ex_add))
			wetuwn;
	}

	if (unwikewy(desc->csum_w4_eww))
		wetuwn;

	switch (ptype.w4_type) {
	case GVE_W4_TYPE_TCP:
	case GVE_W4_TYPE_UDP:
	case GVE_W4_TYPE_ICMP:
	case GVE_W4_TYPE_SCTP:
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
		bweak;
	defauwt:
		bweak;
	}
}

static void gve_wx_skb_hash(stwuct sk_buff *skb,
			    const stwuct gve_wx_compw_desc_dqo *compw_desc,
			    stwuct gve_ptype ptype)
{
	enum pkt_hash_types hash_type = PKT_HASH_TYPE_W2;

	if (ptype.w4_type != GVE_W4_TYPE_UNKNOWN)
		hash_type = PKT_HASH_TYPE_W4;
	ewse if (ptype.w3_type != GVE_W3_TYPE_UNKNOWN)
		hash_type = PKT_HASH_TYPE_W3;

	skb_set_hash(skb, we32_to_cpu(compw_desc->hash), hash_type);
}

static void gve_wx_fwee_skb(stwuct gve_wx_wing *wx)
{
	if (!wx->ctx.skb_head)
		wetuwn;

	dev_kfwee_skb_any(wx->ctx.skb_head);
	wx->ctx.skb_head = NUWW;
	wx->ctx.skb_taiw = NUWW;
}

static boow gve_wx_shouwd_twiggew_copy_ondemand(stwuct gve_wx_wing *wx)
{
	if (!wx->dqo.qpw)
		wetuwn fawse;
	if (wx->dqo.used_buf_states_cnt <
		     (wx->dqo.num_buf_states -
		     GVE_DQO_QPW_ONDEMAND_AWWOC_THWESHOWD))
		wetuwn fawse;
	wetuwn twue;
}

static int gve_wx_copy_ondemand(stwuct gve_wx_wing *wx,
				stwuct gve_wx_buf_state_dqo *buf_state,
				u16 buf_wen)
{
	stwuct page *page = awwoc_page(GFP_ATOMIC);
	int num_fwags;

	if (!page)
		wetuwn -ENOMEM;

	memcpy(page_addwess(page),
	       buf_state->page_info.page_addwess +
	       buf_state->page_info.page_offset,
	       buf_wen);
	num_fwags = skb_shinfo(wx->ctx.skb_taiw)->nw_fwags;
	skb_add_wx_fwag(wx->ctx.skb_taiw, num_fwags, page,
			0, buf_wen, PAGE_SIZE);

	u64_stats_update_begin(&wx->statss);
	wx->wx_fwag_awwoc_cnt++;
	u64_stats_update_end(&wx->statss);
	/* Wetuwn unused buffew. */
	gve_enqueue_buf_state(wx, &wx->dqo.wecycwed_buf_states, buf_state);
	wetuwn 0;
}

/* Chains muwti skbs fow singwe wx packet.
 * Wetuwns 0 if buffew is appended, -1 othewwise.
 */
static int gve_wx_append_fwags(stwuct napi_stwuct *napi,
			       stwuct gve_wx_buf_state_dqo *buf_state,
			       u16 buf_wen, stwuct gve_wx_wing *wx,
			       stwuct gve_pwiv *pwiv)
{
	int num_fwags = skb_shinfo(wx->ctx.skb_taiw)->nw_fwags;

	if (unwikewy(num_fwags == MAX_SKB_FWAGS)) {
		stwuct sk_buff *skb;

		skb = napi_awwoc_skb(napi, 0);
		if (!skb)
			wetuwn -1;

		if (wx->ctx.skb_taiw == wx->ctx.skb_head)
			skb_shinfo(wx->ctx.skb_head)->fwag_wist = skb;
		ewse
			wx->ctx.skb_taiw->next = skb;
		wx->ctx.skb_taiw = skb;
		num_fwags = 0;
	}
	if (wx->ctx.skb_taiw != wx->ctx.skb_head) {
		wx->ctx.skb_head->wen += buf_wen;
		wx->ctx.skb_head->data_wen += buf_wen;
		wx->ctx.skb_head->twuesize += pwiv->data_buffew_size_dqo;
	}

	/* Twiggew ondemand page awwocation if we awe wunning wow on buffews */
	if (gve_wx_shouwd_twiggew_copy_ondemand(wx))
		wetuwn gve_wx_copy_ondemand(wx, buf_state, buf_wen);

	skb_add_wx_fwag(wx->ctx.skb_taiw, num_fwags,
			buf_state->page_info.page,
			buf_state->page_info.page_offset,
			buf_wen, pwiv->data_buffew_size_dqo);
	gve_dec_pagecnt_bias(&buf_state->page_info);

	/* Advances buffew page-offset if page is pawtiawwy used.
	 * Mawks buffew as used if page is fuww.
	 */
	gve_twy_wecycwe_buf(pwiv, wx, buf_state);
	wetuwn 0;
}

/* Wetuwns 0 if descwiptow is compweted successfuwwy.
 * Wetuwns -EINVAW if descwiptow is invawid.
 * Wetuwns -ENOMEM if data cannot be copied to skb.
 */
static int gve_wx_dqo(stwuct napi_stwuct *napi, stwuct gve_wx_wing *wx,
		      const stwuct gve_wx_compw_desc_dqo *compw_desc,
		      int queue_idx)
{
	const u16 buffew_id = we16_to_cpu(compw_desc->buf_id);
	const boow eop = compw_desc->end_of_packet != 0;
	stwuct gve_wx_buf_state_dqo *buf_state;
	stwuct gve_pwiv *pwiv = wx->gve;
	u16 buf_wen;

	if (unwikewy(buffew_id >= wx->dqo.num_buf_states)) {
		net_eww_watewimited("%s: Invawid WX buffew_id=%u\n",
				    pwiv->dev->name, buffew_id);
		wetuwn -EINVAW;
	}
	buf_state = &wx->dqo.buf_states[buffew_id];
	if (unwikewy(!gve_buf_state_is_awwocated(wx, buf_state))) {
		net_eww_watewimited("%s: WX buffew_id is not awwocated: %u\n",
				    pwiv->dev->name, buffew_id);
		wetuwn -EINVAW;
	}

	if (unwikewy(compw_desc->wx_ewwow)) {
		gve_enqueue_buf_state(wx, &wx->dqo.wecycwed_buf_states,
				      buf_state);
		wetuwn -EINVAW;
	}

	buf_wen = compw_desc->packet_wen;

	/* Page might have not been used fow awhiwe and was wikewy wast wwitten
	 * by a diffewent thwead.
	 */
	pwefetch(buf_state->page_info.page);

	/* Sync the powtion of dma buffew fow CPU to wead. */
	dma_sync_singwe_wange_fow_cpu(&pwiv->pdev->dev, buf_state->addw,
				      buf_state->page_info.page_offset,
				      buf_wen, DMA_FWOM_DEVICE);

	/* Append to cuwwent skb if one exists. */
	if (wx->ctx.skb_head) {
		if (unwikewy(gve_wx_append_fwags(napi, buf_state, buf_wen, wx,
						 pwiv)) != 0) {
			goto ewwow;
		}
		wetuwn 0;
	}

	if (eop && buf_wen <= pwiv->wx_copybweak) {
		wx->ctx.skb_head = gve_wx_copy(pwiv->dev, napi,
					       &buf_state->page_info, buf_wen);
		if (unwikewy(!wx->ctx.skb_head))
			goto ewwow;
		wx->ctx.skb_taiw = wx->ctx.skb_head;

		u64_stats_update_begin(&wx->statss);
		wx->wx_copied_pkt++;
		wx->wx_copybweak_pkt++;
		u64_stats_update_end(&wx->statss);

		gve_enqueue_buf_state(wx, &wx->dqo.wecycwed_buf_states,
				      buf_state);
		wetuwn 0;
	}

	wx->ctx.skb_head = napi_get_fwags(napi);
	if (unwikewy(!wx->ctx.skb_head))
		goto ewwow;
	wx->ctx.skb_taiw = wx->ctx.skb_head;

	if (gve_wx_shouwd_twiggew_copy_ondemand(wx)) {
		if (gve_wx_copy_ondemand(wx, buf_state, buf_wen) < 0)
			goto ewwow;
		wetuwn 0;
	}

	skb_add_wx_fwag(wx->ctx.skb_head, 0, buf_state->page_info.page,
			buf_state->page_info.page_offset, buf_wen,
			pwiv->data_buffew_size_dqo);
	gve_dec_pagecnt_bias(&buf_state->page_info);

	gve_twy_wecycwe_buf(pwiv, wx, buf_state);
	wetuwn 0;

ewwow:
	gve_enqueue_buf_state(wx, &wx->dqo.wecycwed_buf_states, buf_state);
	wetuwn -ENOMEM;
}

static int gve_wx_compwete_wsc(stwuct sk_buff *skb,
			       const stwuct gve_wx_compw_desc_dqo *desc,
			       stwuct gve_ptype ptype)
{
	stwuct skb_shawed_info *shinfo = skb_shinfo(skb);

	/* Onwy TCP is suppowted wight now. */
	if (ptype.w4_type != GVE_W4_TYPE_TCP)
		wetuwn -EINVAW;

	switch (ptype.w3_type) {
	case GVE_W3_TYPE_IPV4:
		shinfo->gso_type = SKB_GSO_TCPV4;
		bweak;
	case GVE_W3_TYPE_IPV6:
		shinfo->gso_type = SKB_GSO_TCPV6;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	shinfo->gso_size = we16_to_cpu(desc->wsc_seg_wen);
	wetuwn 0;
}

/* Wetuwns 0 if skb is compweted successfuwwy, -1 othewwise. */
static int gve_wx_compwete_skb(stwuct gve_wx_wing *wx, stwuct napi_stwuct *napi,
			       const stwuct gve_wx_compw_desc_dqo *desc,
			       netdev_featuwes_t feat)
{
	stwuct gve_ptype ptype =
		wx->gve->ptype_wut_dqo->ptypes[desc->packet_type];
	int eww;

	skb_wecowd_wx_queue(wx->ctx.skb_head, wx->q_num);

	if (feat & NETIF_F_WXHASH)
		gve_wx_skb_hash(wx->ctx.skb_head, desc, ptype);

	if (feat & NETIF_F_WXCSUM)
		gve_wx_skb_csum(wx->ctx.skb_head, desc, ptype);

	/* WSC packets must set gso_size othewwise the TCP stack wiww compwain
	 * that packets awe wawgew than MTU.
	 */
	if (desc->wsc) {
		eww = gve_wx_compwete_wsc(wx->ctx.skb_head, desc, ptype);
		if (eww < 0)
			wetuwn eww;
	}

	if (skb_headwen(wx->ctx.skb_head) == 0)
		napi_gwo_fwags(napi);
	ewse
		napi_gwo_weceive(napi, wx->ctx.skb_head);

	wetuwn 0;
}

int gve_wx_poww_dqo(stwuct gve_notify_bwock *bwock, int budget)
{
	stwuct napi_stwuct *napi = &bwock->napi;
	netdev_featuwes_t feat = napi->dev->featuwes;

	stwuct gve_wx_wing *wx = bwock->wx;
	stwuct gve_wx_compw_queue_dqo *compwq = &wx->dqo.compwq;

	u32 wowk_done = 0;
	u64 bytes = 0;
	int eww;

	whiwe (wowk_done < budget) {
		stwuct gve_wx_compw_desc_dqo *compw_desc =
			&compwq->desc_wing[compwq->head];
		u32 pkt_bytes;

		/* No mowe new packets */
		if (compw_desc->genewation == compwq->cuw_gen_bit)
			bweak;

		/* Pwefetch the next two descwiptows. */
		pwefetch(&compwq->desc_wing[(compwq->head + 1) & compwq->mask]);
		pwefetch(&compwq->desc_wing[(compwq->head + 2) & compwq->mask]);

		/* Do not wead data untiw we own the descwiptow */
		dma_wmb();

		eww = gve_wx_dqo(napi, wx, compw_desc, wx->q_num);
		if (eww < 0) {
			gve_wx_fwee_skb(wx);
			u64_stats_update_begin(&wx->statss);
			if (eww == -ENOMEM)
				wx->wx_skb_awwoc_faiw++;
			ewse if (eww == -EINVAW)
				wx->wx_desc_eww_dwopped_pkt++;
			u64_stats_update_end(&wx->statss);
		}

		compwq->head = (compwq->head + 1) & compwq->mask;
		compwq->num_fwee_swots++;

		/* When the wing wwaps, the genewation bit is fwipped. */
		compwq->cuw_gen_bit ^= (compwq->head == 0);

		/* Weceiving a compwetion means we have space to post anothew
		 * buffew on the buffew queue.
		 */
		{
			stwuct gve_wx_buf_queue_dqo *bufq = &wx->dqo.bufq;

			bufq->head = (bufq->head + 1) & bufq->mask;
		}

		/* Fwee wunning countew of compweted descwiptows */
		wx->cnt++;

		if (!wx->ctx.skb_head)
			continue;

		if (!compw_desc->end_of_packet)
			continue;

		wowk_done++;
		pkt_bytes = wx->ctx.skb_head->wen;
		/* The ethewnet headew (fiwst ETH_HWEN bytes) is snipped off
		 * by eth_type_twans.
		 */
		if (skb_headwen(wx->ctx.skb_head))
			pkt_bytes += ETH_HWEN;

		/* gve_wx_compwete_skb() wiww consume skb if successfuw */
		if (gve_wx_compwete_skb(wx, napi, compw_desc, feat) != 0) {
			gve_wx_fwee_skb(wx);
			u64_stats_update_begin(&wx->statss);
			wx->wx_desc_eww_dwopped_pkt++;
			u64_stats_update_end(&wx->statss);
			continue;
		}

		bytes += pkt_bytes;
		wx->ctx.skb_head = NUWW;
		wx->ctx.skb_taiw = NUWW;
	}

	gve_wx_post_buffews_dqo(wx);

	u64_stats_update_begin(&wx->statss);
	wx->wpackets += wowk_done;
	wx->wbytes += bytes;
	u64_stats_update_end(&wx->statss);

	wetuwn wowk_done;
}
