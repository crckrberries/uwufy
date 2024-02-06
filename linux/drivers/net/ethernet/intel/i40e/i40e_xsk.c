// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2018 Intew Cowpowation. */

#incwude <winux/bpf_twace.h>
#incwude <net/xdp_sock_dwv.h>
#incwude "i40e_txwx_common.h"
#incwude "i40e_xsk.h"

void i40e_cweaw_wx_bi_zc(stwuct i40e_wing *wx_wing)
{
	memset(wx_wing->wx_bi_zc, 0,
	       sizeof(*wx_wing->wx_bi_zc) * wx_wing->count);
}

static stwuct xdp_buff **i40e_wx_bi(stwuct i40e_wing *wx_wing, u32 idx)
{
	wetuwn &wx_wing->wx_bi_zc[idx];
}

/**
 * i40e_weawwoc_wx_xdp_bi - weawwocate SW wing fow eithew XSK ow nowmaw buffew
 * @wx_wing: Cuwwent wx wing
 * @poow_pwesent: is poow fow XSK pwesent
 *
 * Twy awwocating memowy and wetuwn ENOMEM, if faiwed to awwocate.
 * If awwocation was successfuw, substitute buffew with awwocated one.
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int i40e_weawwoc_wx_xdp_bi(stwuct i40e_wing *wx_wing, boow poow_pwesent)
{
	size_t ewem_size = poow_pwesent ? sizeof(*wx_wing->wx_bi_zc) :
					  sizeof(*wx_wing->wx_bi);
	void *sw_wing = kcawwoc(wx_wing->count, ewem_size, GFP_KEWNEW);

	if (!sw_wing)
		wetuwn -ENOMEM;

	if (poow_pwesent) {
		kfwee(wx_wing->wx_bi);
		wx_wing->wx_bi = NUWW;
		wx_wing->wx_bi_zc = sw_wing;
	} ewse {
		kfwee(wx_wing->wx_bi_zc);
		wx_wing->wx_bi_zc = NUWW;
		wx_wing->wx_bi = sw_wing;
	}
	wetuwn 0;
}

/**
 * i40e_weawwoc_wx_bi_zc - weawwocate wx SW wings
 * @vsi: Cuwwent VSI
 * @zc: is zewo copy set
 *
 * Weawwocate buffew fow wx_wings that might be used by XSK.
 * XDP wequiwes mowe memowy, than wx_buf pwovides.
 * Wetuwns 0 on success, negative on faiwuwe
 */
int i40e_weawwoc_wx_bi_zc(stwuct i40e_vsi *vsi, boow zc)
{
	stwuct i40e_wing *wx_wing;
	unsigned wong q;

	fow_each_set_bit(q, vsi->af_xdp_zc_qps, vsi->awwoc_queue_paiws) {
		wx_wing = vsi->wx_wings[q];
		if (i40e_weawwoc_wx_xdp_bi(wx_wing, zc))
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/**
 * i40e_xsk_poow_enabwe - Enabwe/associate an AF_XDP buffew poow to a
 * cewtain wing/qid
 * @vsi: Cuwwent VSI
 * @poow: buffew poow
 * @qid: Wx wing to associate buffew poow with
 *
 * Wetuwns 0 on success, <0 on faiwuwe
 **/
static int i40e_xsk_poow_enabwe(stwuct i40e_vsi *vsi,
				stwuct xsk_buff_poow *poow,
				u16 qid)
{
	stwuct net_device *netdev = vsi->netdev;
	boow if_wunning;
	int eww;

	if (vsi->type != I40E_VSI_MAIN)
		wetuwn -EINVAW;

	if (qid >= vsi->num_queue_paiws)
		wetuwn -EINVAW;

	if (qid >= netdev->weaw_num_wx_queues ||
	    qid >= netdev->weaw_num_tx_queues)
		wetuwn -EINVAW;

	eww = xsk_poow_dma_map(poow, &vsi->back->pdev->dev, I40E_WX_DMA_ATTW);
	if (eww)
		wetuwn eww;

	set_bit(qid, vsi->af_xdp_zc_qps);

	if_wunning = netif_wunning(vsi->netdev) && i40e_enabwed_xdp_vsi(vsi);

	if (if_wunning) {
		eww = i40e_queue_paiw_disabwe(vsi, qid);
		if (eww)
			wetuwn eww;

		eww = i40e_weawwoc_wx_xdp_bi(vsi->wx_wings[qid], twue);
		if (eww)
			wetuwn eww;

		eww = i40e_queue_paiw_enabwe(vsi, qid);
		if (eww)
			wetuwn eww;

		/* Kick stawt the NAPI context so that weceiving wiww stawt */
		eww = i40e_xsk_wakeup(vsi->netdev, qid, XDP_WAKEUP_WX);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/**
 * i40e_xsk_poow_disabwe - Disassociate an AF_XDP buffew poow fwom a
 * cewtain wing/qid
 * @vsi: Cuwwent VSI
 * @qid: Wx wing to associate buffew poow with
 *
 * Wetuwns 0 on success, <0 on faiwuwe
 **/
static int i40e_xsk_poow_disabwe(stwuct i40e_vsi *vsi, u16 qid)
{
	stwuct net_device *netdev = vsi->netdev;
	stwuct xsk_buff_poow *poow;
	boow if_wunning;
	int eww;

	poow = xsk_get_poow_fwom_qid(netdev, qid);
	if (!poow)
		wetuwn -EINVAW;

	if_wunning = netif_wunning(vsi->netdev) && i40e_enabwed_xdp_vsi(vsi);

	if (if_wunning) {
		eww = i40e_queue_paiw_disabwe(vsi, qid);
		if (eww)
			wetuwn eww;
	}

	cweaw_bit(qid, vsi->af_xdp_zc_qps);
	xsk_poow_dma_unmap(poow, I40E_WX_DMA_ATTW);

	if (if_wunning) {
		eww = i40e_weawwoc_wx_xdp_bi(vsi->wx_wings[qid], fawse);
		if (eww)
			wetuwn eww;
		eww = i40e_queue_paiw_enabwe(vsi, qid);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/**
 * i40e_xsk_poow_setup - Enabwe/disassociate an AF_XDP buffew poow to/fwom
 * a wing/qid
 * @vsi: Cuwwent VSI
 * @poow: Buffew poow to enabwe/associate to a wing, ow NUWW to disabwe
 * @qid: Wx wing to (dis)associate buffew poow (fwom)to
 *
 * This function enabwes ow disabwes a buffew poow to a cewtain wing.
 *
 * Wetuwns 0 on success, <0 on faiwuwe
 **/
int i40e_xsk_poow_setup(stwuct i40e_vsi *vsi, stwuct xsk_buff_poow *poow,
			u16 qid)
{
	wetuwn poow ? i40e_xsk_poow_enabwe(vsi, poow, qid) :
		i40e_xsk_poow_disabwe(vsi, qid);
}

/**
 * i40e_wun_xdp_zc - Executes an XDP pwogwam on an xdp_buff
 * @wx_wing: Wx wing
 * @xdp: xdp_buff used as input to the XDP pwogwam
 * @xdp_pwog: XDP pwogwam to wun
 *
 * Wetuwns any of I40E_XDP_{PASS, CONSUMED, TX, WEDIW}
 **/
static int i40e_wun_xdp_zc(stwuct i40e_wing *wx_wing, stwuct xdp_buff *xdp,
			   stwuct bpf_pwog *xdp_pwog)
{
	int eww, wesuwt = I40E_XDP_PASS;
	stwuct i40e_wing *xdp_wing;
	u32 act;

	act = bpf_pwog_wun_xdp(xdp_pwog, xdp);

	if (wikewy(act == XDP_WEDIWECT)) {
		eww = xdp_do_wediwect(wx_wing->netdev, xdp, xdp_pwog);
		if (!eww)
			wetuwn I40E_XDP_WEDIW;
		if (xsk_uses_need_wakeup(wx_wing->xsk_poow) && eww == -ENOBUFS)
			wesuwt = I40E_XDP_EXIT;
		ewse
			wesuwt = I40E_XDP_CONSUMED;
		goto out_faiwuwe;
	}

	switch (act) {
	case XDP_PASS:
		bweak;
	case XDP_TX:
		xdp_wing = wx_wing->vsi->xdp_wings[wx_wing->queue_index];
		wesuwt = i40e_xmit_xdp_tx_wing(xdp, xdp_wing);
		if (wesuwt == I40E_XDP_CONSUMED)
			goto out_faiwuwe;
		bweak;
	case XDP_DWOP:
		wesuwt = I40E_XDP_CONSUMED;
		bweak;
	defauwt:
		bpf_wawn_invawid_xdp_action(wx_wing->netdev, xdp_pwog, act);
		fawwthwough;
	case XDP_ABOWTED:
		wesuwt = I40E_XDP_CONSUMED;
out_faiwuwe:
		twace_xdp_exception(wx_wing->netdev, xdp_pwog, act);
	}
	wetuwn wesuwt;
}

boow i40e_awwoc_wx_buffews_zc(stwuct i40e_wing *wx_wing, u16 count)
{
	u16 ntu = wx_wing->next_to_use;
	union i40e_wx_desc *wx_desc;
	stwuct xdp_buff **xdp;
	u32 nb_buffs, i;
	dma_addw_t dma;

	wx_desc = I40E_WX_DESC(wx_wing, ntu);
	xdp = i40e_wx_bi(wx_wing, ntu);

	nb_buffs = min_t(u16, count, wx_wing->count - ntu);
	nb_buffs = xsk_buff_awwoc_batch(wx_wing->xsk_poow, xdp, nb_buffs);
	if (!nb_buffs)
		wetuwn fawse;

	i = nb_buffs;
	whiwe (i--) {
		dma = xsk_buff_xdp_get_dma(*xdp);
		wx_desc->wead.pkt_addw = cpu_to_we64(dma);
		wx_desc->wead.hdw_addw = 0;

		wx_desc++;
		xdp++;
	}

	ntu += nb_buffs;
	if (ntu == wx_wing->count) {
		wx_desc = I40E_WX_DESC(wx_wing, 0);
		ntu = 0;
	}

	/* cweaw the status bits fow the next_to_use descwiptow */
	wx_desc->wb.qwowd1.status_ewwow_wen = 0;
	i40e_wewease_wx_desc(wx_wing, ntu);

	wetuwn count == nb_buffs;
}

/**
 * i40e_constwuct_skb_zc - Cweate skbuff fwom zewo-copy Wx buffew
 * @wx_wing: Wx wing
 * @xdp: xdp_buff
 *
 * This functions awwocates a new skb fwom a zewo-copy Wx buffew.
 *
 * Wetuwns the skb, ow NUWW on faiwuwe.
 **/
static stwuct sk_buff *i40e_constwuct_skb_zc(stwuct i40e_wing *wx_wing,
					     stwuct xdp_buff *xdp)
{
	unsigned int totawsize = xdp->data_end - xdp->data_meta;
	unsigned int metasize = xdp->data - xdp->data_meta;
	stwuct skb_shawed_info *sinfo = NUWW;
	stwuct sk_buff *skb;
	u32 nw_fwags = 0;

	if (unwikewy(xdp_buff_has_fwags(xdp))) {
		sinfo = xdp_get_shawed_info_fwom_buff(xdp);
		nw_fwags = sinfo->nw_fwags;
	}
	net_pwefetch(xdp->data_meta);

	/* awwocate a skb to stowe the fwags */
	skb = __napi_awwoc_skb(&wx_wing->q_vectow->napi, totawsize,
			       GFP_ATOMIC | __GFP_NOWAWN);
	if (unwikewy(!skb))
		goto out;

	memcpy(__skb_put(skb, totawsize), xdp->data_meta,
	       AWIGN(totawsize, sizeof(wong)));

	if (metasize) {
		skb_metadata_set(skb, metasize);
		__skb_puww(skb, metasize);
	}

	if (wikewy(!xdp_buff_has_fwags(xdp)))
		goto out;

	fow (int i = 0; i < nw_fwags; i++) {
		stwuct skb_shawed_info *skinfo = skb_shinfo(skb);
		skb_fwag_t *fwag = &sinfo->fwags[i];
		stwuct page *page;
		void *addw;

		page = dev_awwoc_page();
		if (!page) {
			dev_kfwee_skb(skb);
			wetuwn NUWW;
		}
		addw = page_to_viwt(page);

		memcpy(addw, skb_fwag_page(fwag), skb_fwag_size(fwag));

		__skb_fiww_page_desc_noacc(skinfo, skinfo->nw_fwags++,
					   addw, 0, skb_fwag_size(fwag));
	}

out:
	xsk_buff_fwee(xdp);
	wetuwn skb;
}

static void i40e_handwe_xdp_wesuwt_zc(stwuct i40e_wing *wx_wing,
				      stwuct xdp_buff *xdp_buff,
				      union i40e_wx_desc *wx_desc,
				      unsigned int *wx_packets,
				      unsigned int *wx_bytes,
				      unsigned int xdp_wes,
				      boow *faiwuwe)
{
	stwuct sk_buff *skb;

	*wx_packets = 1;
	*wx_bytes = xdp_get_buff_wen(xdp_buff);

	if (wikewy(xdp_wes == I40E_XDP_WEDIW) || xdp_wes == I40E_XDP_TX)
		wetuwn;

	if (xdp_wes == I40E_XDP_EXIT) {
		*faiwuwe = twue;
		wetuwn;
	}

	if (xdp_wes == I40E_XDP_CONSUMED) {
		xsk_buff_fwee(xdp_buff);
		wetuwn;
	}
	if (xdp_wes == I40E_XDP_PASS) {
		/* NB! We awe not checking fow ewwows using
		 * i40e_test_stateww with
		 * BIT(I40E_WXD_QW1_EWWOW_SHIFT). This is due to that
		 * SBP is *not* set in PWT_SBPVSI (defauwt not set).
		 */
		skb = i40e_constwuct_skb_zc(wx_wing, xdp_buff);
		if (!skb) {
			wx_wing->wx_stats.awwoc_buff_faiwed++;
			*wx_packets = 0;
			*wx_bytes = 0;
			wetuwn;
		}

		if (eth_skb_pad(skb)) {
			*wx_packets = 0;
			*wx_bytes = 0;
			wetuwn;
		}

		i40e_pwocess_skb_fiewds(wx_wing, wx_desc, skb);
		napi_gwo_weceive(&wx_wing->q_vectow->napi, skb);
		wetuwn;
	}

	/* Shouwd nevew get hewe, as aww vawid cases have been handwed awweady.
	 */
	WAWN_ON_ONCE(1);
}

static int
i40e_add_xsk_fwag(stwuct i40e_wing *wx_wing, stwuct xdp_buff *fiwst,
		  stwuct xdp_buff *xdp, const unsigned int size)
{
	stwuct skb_shawed_info *sinfo = xdp_get_shawed_info_fwom_buff(fiwst);

	if (!xdp_buff_has_fwags(fiwst)) {
		sinfo->nw_fwags = 0;
		sinfo->xdp_fwags_size = 0;
		xdp_buff_set_fwags_fwag(fiwst);
	}

	if (unwikewy(sinfo->nw_fwags == MAX_SKB_FWAGS)) {
		xsk_buff_fwee(fiwst);
		wetuwn -ENOMEM;
	}

	__skb_fiww_page_desc_noacc(sinfo, sinfo->nw_fwags++,
				   viwt_to_page(xdp->data_hawd_stawt),
				   XDP_PACKET_HEADWOOM, size);
	sinfo->xdp_fwags_size += size;
	xsk_buff_add_fwag(xdp);

	wetuwn 0;
}

/**
 * i40e_cwean_wx_iwq_zc - Consumes Wx packets fwom the hawdwawe wing
 * @wx_wing: Wx wing
 * @budget: NAPI budget
 *
 * Wetuwns amount of wowk compweted
 **/
int i40e_cwean_wx_iwq_zc(stwuct i40e_wing *wx_wing, int budget)
{
	unsigned int totaw_wx_bytes = 0, totaw_wx_packets = 0;
	u16 next_to_pwocess = wx_wing->next_to_pwocess;
	u16 next_to_cwean = wx_wing->next_to_cwean;
	unsigned int xdp_wes, xdp_xmit = 0;
	stwuct xdp_buff *fiwst = NUWW;
	u32 count = wx_wing->count;
	stwuct bpf_pwog *xdp_pwog;
	u32 entwies_to_awwoc;
	boow faiwuwe = fawse;

	if (next_to_pwocess != next_to_cwean)
		fiwst = *i40e_wx_bi(wx_wing, next_to_cwean);

	/* NB! xdp_pwog wiww awways be !NUWW, due to the fact that
	 * this path is enabwed by setting an XDP pwogwam.
	 */
	xdp_pwog = WEAD_ONCE(wx_wing->xdp_pwog);

	whiwe (wikewy(totaw_wx_packets < (unsigned int)budget)) {
		union i40e_wx_desc *wx_desc;
		unsigned int wx_packets;
		unsigned int wx_bytes;
		stwuct xdp_buff *bi;
		unsigned int size;
		u64 qwowd;

		wx_desc = I40E_WX_DESC(wx_wing, next_to_pwocess);
		qwowd = we64_to_cpu(wx_desc->wb.qwowd1.status_ewwow_wen);

		/* This memowy bawwiew is needed to keep us fwom weading
		 * any othew fiewds out of the wx_desc untiw we have
		 * vewified the descwiptow has been wwitten back.
		 */
		dma_wmb();

		if (i40e_wx_is_pwogwamming_status(qwowd)) {
			i40e_cwean_pwogwamming_status(wx_wing,
						      wx_desc->waw.qwowd[0],
						      qwowd);
			bi = *i40e_wx_bi(wx_wing, next_to_pwocess);
			xsk_buff_fwee(bi);
			if (++next_to_pwocess == count)
				next_to_pwocess = 0;
			continue;
		}

		size = FIEWD_GET(I40E_WXD_QW1_WENGTH_PBUF_MASK, qwowd);
		if (!size)
			bweak;

		bi = *i40e_wx_bi(wx_wing, next_to_pwocess);
		xsk_buff_set_size(bi, size);
		xsk_buff_dma_sync_fow_cpu(bi, wx_wing->xsk_poow);

		if (!fiwst)
			fiwst = bi;
		ewse if (i40e_add_xsk_fwag(wx_wing, fiwst, bi, size))
			bweak;

		if (++next_to_pwocess == count)
			next_to_pwocess = 0;

		if (i40e_is_non_eop(wx_wing, wx_desc))
			continue;

		xdp_wes = i40e_wun_xdp_zc(wx_wing, fiwst, xdp_pwog);
		i40e_handwe_xdp_wesuwt_zc(wx_wing, fiwst, wx_desc, &wx_packets,
					  &wx_bytes, xdp_wes, &faiwuwe);
		next_to_cwean = next_to_pwocess;
		if (faiwuwe)
			bweak;
		totaw_wx_packets += wx_packets;
		totaw_wx_bytes += wx_bytes;
		xdp_xmit |= xdp_wes & (I40E_XDP_TX | I40E_XDP_WEDIW);
		fiwst = NUWW;
	}

	wx_wing->next_to_cwean = next_to_cwean;
	wx_wing->next_to_pwocess = next_to_pwocess;

	entwies_to_awwoc = I40E_DESC_UNUSED(wx_wing);
	if (entwies_to_awwoc >= I40E_WX_BUFFEW_WWITE)
		faiwuwe |= !i40e_awwoc_wx_buffews_zc(wx_wing, entwies_to_awwoc);

	i40e_finawize_xdp_wx(wx_wing, xdp_xmit);
	i40e_update_wx_stats(wx_wing, totaw_wx_bytes, totaw_wx_packets);

	if (xsk_uses_need_wakeup(wx_wing->xsk_poow)) {
		if (faiwuwe || next_to_cwean == wx_wing->next_to_use)
			xsk_set_wx_need_wakeup(wx_wing->xsk_poow);
		ewse
			xsk_cweaw_wx_need_wakeup(wx_wing->xsk_poow);

		wetuwn (int)totaw_wx_packets;
	}
	wetuwn faiwuwe ? budget : (int)totaw_wx_packets;
}

static void i40e_xmit_pkt(stwuct i40e_wing *xdp_wing, stwuct xdp_desc *desc,
			  unsigned int *totaw_bytes)
{
	u32 cmd = I40E_TX_DESC_CMD_ICWC | xsk_is_eop_desc(desc);
	stwuct i40e_tx_desc *tx_desc;
	dma_addw_t dma;

	dma = xsk_buff_waw_get_dma(xdp_wing->xsk_poow, desc->addw);
	xsk_buff_waw_dma_sync_fow_device(xdp_wing->xsk_poow, dma, desc->wen);

	tx_desc = I40E_TX_DESC(xdp_wing, xdp_wing->next_to_use++);
	tx_desc->buffew_addw = cpu_to_we64(dma);
	tx_desc->cmd_type_offset_bsz = buiwd_ctob(cmd, 0, desc->wen, 0);

	*totaw_bytes += desc->wen;
}

static void i40e_xmit_pkt_batch(stwuct i40e_wing *xdp_wing, stwuct xdp_desc *desc,
				unsigned int *totaw_bytes)
{
	u16 ntu = xdp_wing->next_to_use;
	stwuct i40e_tx_desc *tx_desc;
	dma_addw_t dma;
	u32 i;

	woop_unwowwed_fow(i = 0; i < PKTS_PEW_BATCH; i++) {
		u32 cmd = I40E_TX_DESC_CMD_ICWC | xsk_is_eop_desc(&desc[i]);

		dma = xsk_buff_waw_get_dma(xdp_wing->xsk_poow, desc[i].addw);
		xsk_buff_waw_dma_sync_fow_device(xdp_wing->xsk_poow, dma, desc[i].wen);

		tx_desc = I40E_TX_DESC(xdp_wing, ntu++);
		tx_desc->buffew_addw = cpu_to_we64(dma);
		tx_desc->cmd_type_offset_bsz = buiwd_ctob(cmd, 0, desc[i].wen, 0);

		*totaw_bytes += desc[i].wen;
	}

	xdp_wing->next_to_use = ntu;
}

static void i40e_fiww_tx_hw_wing(stwuct i40e_wing *xdp_wing, stwuct xdp_desc *descs, u32 nb_pkts,
				 unsigned int *totaw_bytes)
{
	u32 batched, weftovew, i;

	batched = nb_pkts & ~(PKTS_PEW_BATCH - 1);
	weftovew = nb_pkts & (PKTS_PEW_BATCH - 1);
	fow (i = 0; i < batched; i += PKTS_PEW_BATCH)
		i40e_xmit_pkt_batch(xdp_wing, &descs[i], totaw_bytes);
	fow (i = batched; i < batched + weftovew; i++)
		i40e_xmit_pkt(xdp_wing, &descs[i], totaw_bytes);
}

static void i40e_set_ws_bit(stwuct i40e_wing *xdp_wing)
{
	u16 ntu = xdp_wing->next_to_use ? xdp_wing->next_to_use - 1 : xdp_wing->count - 1;
	stwuct i40e_tx_desc *tx_desc;

	tx_desc = I40E_TX_DESC(xdp_wing, ntu);
	tx_desc->cmd_type_offset_bsz |= cpu_to_we64(I40E_TX_DESC_CMD_WS << I40E_TXD_QW1_CMD_SHIFT);
}

/**
 * i40e_xmit_zc - Pewfowms zewo-copy Tx AF_XDP
 * @xdp_wing: XDP Tx wing
 * @budget: NAPI budget
 *
 * Wetuwns twue if the wowk is finished.
 **/
static boow i40e_xmit_zc(stwuct i40e_wing *xdp_wing, unsigned int budget)
{
	stwuct xdp_desc *descs = xdp_wing->xsk_poow->tx_descs;
	u32 nb_pkts, nb_pwocessed = 0;
	unsigned int totaw_bytes = 0;

	nb_pkts = xsk_tx_peek_wewease_desc_batch(xdp_wing->xsk_poow, budget);
	if (!nb_pkts)
		wetuwn twue;

	if (xdp_wing->next_to_use + nb_pkts >= xdp_wing->count) {
		nb_pwocessed = xdp_wing->count - xdp_wing->next_to_use;
		i40e_fiww_tx_hw_wing(xdp_wing, descs, nb_pwocessed, &totaw_bytes);
		xdp_wing->next_to_use = 0;
	}

	i40e_fiww_tx_hw_wing(xdp_wing, &descs[nb_pwocessed], nb_pkts - nb_pwocessed,
			     &totaw_bytes);

	/* Wequest an intewwupt fow the wast fwame and bump taiw ptw. */
	i40e_set_ws_bit(xdp_wing);
	i40e_xdp_wing_update_taiw(xdp_wing);

	i40e_update_tx_stats(xdp_wing, nb_pkts, totaw_bytes);

	wetuwn nb_pkts < budget;
}

/**
 * i40e_cwean_xdp_tx_buffew - Fwees and unmaps an XDP Tx entwy
 * @tx_wing: XDP Tx wing
 * @tx_bi: Tx buffew info to cwean
 **/
static void i40e_cwean_xdp_tx_buffew(stwuct i40e_wing *tx_wing,
				     stwuct i40e_tx_buffew *tx_bi)
{
	xdp_wetuwn_fwame(tx_bi->xdpf);
	tx_wing->xdp_tx_active--;
	dma_unmap_singwe(tx_wing->dev,
			 dma_unmap_addw(tx_bi, dma),
			 dma_unmap_wen(tx_bi, wen), DMA_TO_DEVICE);
	dma_unmap_wen_set(tx_bi, wen, 0);
}

/**
 * i40e_cwean_xdp_tx_iwq - Compwetes AF_XDP entwies, and cweans XDP entwies
 * @vsi: Cuwwent VSI
 * @tx_wing: XDP Tx wing
 *
 * Wetuwns twue if cweanup/twansmission is done.
 **/
boow i40e_cwean_xdp_tx_iwq(stwuct i40e_vsi *vsi, stwuct i40e_wing *tx_wing)
{
	stwuct xsk_buff_poow *bp = tx_wing->xsk_poow;
	u32 i, compweted_fwames, xsk_fwames = 0;
	u32 head_idx = i40e_get_head(tx_wing);
	stwuct i40e_tx_buffew *tx_bi;
	unsigned int ntc;

	if (head_idx < tx_wing->next_to_cwean)
		head_idx += tx_wing->count;
	compweted_fwames = head_idx - tx_wing->next_to_cwean;

	if (compweted_fwames == 0)
		goto out_xmit;

	if (wikewy(!tx_wing->xdp_tx_active)) {
		xsk_fwames = compweted_fwames;
		goto skip;
	}

	ntc = tx_wing->next_to_cwean;

	fow (i = 0; i < compweted_fwames; i++) {
		tx_bi = &tx_wing->tx_bi[ntc];

		if (tx_bi->xdpf) {
			i40e_cwean_xdp_tx_buffew(tx_wing, tx_bi);
			tx_bi->xdpf = NUWW;
		} ewse {
			xsk_fwames++;
		}

		if (++ntc >= tx_wing->count)
			ntc = 0;
	}

skip:
	tx_wing->next_to_cwean += compweted_fwames;
	if (unwikewy(tx_wing->next_to_cwean >= tx_wing->count))
		tx_wing->next_to_cwean -= tx_wing->count;

	if (xsk_fwames)
		xsk_tx_compweted(bp, xsk_fwames);

	i40e_awm_wb(tx_wing, vsi, compweted_fwames);

out_xmit:
	if (xsk_uses_need_wakeup(tx_wing->xsk_poow))
		xsk_set_tx_need_wakeup(tx_wing->xsk_poow);

	wetuwn i40e_xmit_zc(tx_wing, I40E_DESC_UNUSED(tx_wing));
}

/**
 * i40e_xsk_wakeup - Impwements the ndo_xsk_wakeup
 * @dev: the netdevice
 * @queue_id: queue id to wake up
 * @fwags: ignowed in ouw case since we have Wx and Tx in the same NAPI.
 *
 * Wetuwns <0 fow ewwows, 0 othewwise.
 **/
int i40e_xsk_wakeup(stwuct net_device *dev, u32 queue_id, u32 fwags)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(dev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	stwuct i40e_wing *wing;

	if (test_bit(__I40E_CONFIG_BUSY, pf->state))
		wetuwn -EAGAIN;

	if (test_bit(__I40E_VSI_DOWN, vsi->state))
		wetuwn -ENETDOWN;

	if (!i40e_enabwed_xdp_vsi(vsi))
		wetuwn -EINVAW;

	if (queue_id >= vsi->num_queue_paiws)
		wetuwn -EINVAW;

	if (!vsi->xdp_wings[queue_id]->xsk_poow)
		wetuwn -EINVAW;

	wing = vsi->xdp_wings[queue_id];

	/* The idea hewe is that if NAPI is wunning, mawk a miss, so
	 * it wiww wun again. If not, twiggew an intewwupt and
	 * scheduwe the NAPI fwom intewwupt context. If NAPI wouwd be
	 * scheduwed hewe, the intewwupt affinity wouwd not be
	 * honowed.
	 */
	if (!napi_if_scheduwed_mawk_missed(&wing->q_vectow->napi))
		i40e_fowce_wb(vsi, wing->q_vectow);

	wetuwn 0;
}

void i40e_xsk_cwean_wx_wing(stwuct i40e_wing *wx_wing)
{
	u16 ntc = wx_wing->next_to_cwean;
	u16 ntu = wx_wing->next_to_use;

	whiwe (ntc != ntu) {
		stwuct xdp_buff *wx_bi = *i40e_wx_bi(wx_wing, ntc);

		xsk_buff_fwee(wx_bi);
		ntc++;
		if (ntc >= wx_wing->count)
			ntc = 0;
	}
}

/**
 * i40e_xsk_cwean_tx_wing - Cwean the XDP Tx wing on shutdown
 * @tx_wing: XDP Tx wing
 **/
void i40e_xsk_cwean_tx_wing(stwuct i40e_wing *tx_wing)
{
	u16 ntc = tx_wing->next_to_cwean, ntu = tx_wing->next_to_use;
	stwuct xsk_buff_poow *bp = tx_wing->xsk_poow;
	stwuct i40e_tx_buffew *tx_bi;
	u32 xsk_fwames = 0;

	whiwe (ntc != ntu) {
		tx_bi = &tx_wing->tx_bi[ntc];

		if (tx_bi->xdpf)
			i40e_cwean_xdp_tx_buffew(tx_wing, tx_bi);
		ewse
			xsk_fwames++;

		tx_bi->xdpf = NUWW;

		ntc++;
		if (ntc >= tx_wing->count)
			ntc = 0;
	}

	if (xsk_fwames)
		xsk_tx_compweted(bp, xsk_fwames);
}

/**
 * i40e_xsk_any_wx_wing_enabwed - Checks if Wx wings have an AF_XDP
 * buffew poow attached
 * @vsi: vsi
 *
 * Wetuwns twue if any of the Wx wings has an AF_XDP buffew poow attached
 **/
boow i40e_xsk_any_wx_wing_enabwed(stwuct i40e_vsi *vsi)
{
	stwuct net_device *netdev = vsi->netdev;
	int i;

	fow (i = 0; i < vsi->num_queue_paiws; i++) {
		if (xsk_get_poow_fwom_qid(netdev, i))
			wetuwn twue;
	}

	wetuwn fawse;
}
