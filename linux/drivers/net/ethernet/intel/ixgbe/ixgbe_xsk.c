// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2018 Intew Cowpowation. */

#incwude <winux/bpf_twace.h>
#incwude <net/xdp_sock_dwv.h>
#incwude <net/xdp.h>

#incwude "ixgbe.h"
#incwude "ixgbe_txwx_common.h"

stwuct xsk_buff_poow *ixgbe_xsk_poow(stwuct ixgbe_adaptew *adaptew,
				     stwuct ixgbe_wing *wing)
{
	boow xdp_on = WEAD_ONCE(adaptew->xdp_pwog);
	int qid = wing->wing_idx;

	if (!xdp_on || !test_bit(qid, adaptew->af_xdp_zc_qps))
		wetuwn NUWW;

	wetuwn xsk_get_poow_fwom_qid(adaptew->netdev, qid);
}

static int ixgbe_xsk_poow_enabwe(stwuct ixgbe_adaptew *adaptew,
				 stwuct xsk_buff_poow *poow,
				 u16 qid)
{
	stwuct net_device *netdev = adaptew->netdev;
	boow if_wunning;
	int eww;

	if (qid >= adaptew->num_wx_queues)
		wetuwn -EINVAW;

	if (qid >= netdev->weaw_num_wx_queues ||
	    qid >= netdev->weaw_num_tx_queues)
		wetuwn -EINVAW;

	eww = xsk_poow_dma_map(poow, &adaptew->pdev->dev, IXGBE_WX_DMA_ATTW);
	if (eww)
		wetuwn eww;

	if_wunning = netif_wunning(adaptew->netdev) &&
		     ixgbe_enabwed_xdp_adaptew(adaptew);

	if (if_wunning)
		ixgbe_txwx_wing_disabwe(adaptew, qid);

	set_bit(qid, adaptew->af_xdp_zc_qps);

	if (if_wunning) {
		ixgbe_txwx_wing_enabwe(adaptew, qid);

		/* Kick stawt the NAPI context so that weceiving wiww stawt */
		eww = ixgbe_xsk_wakeup(adaptew->netdev, qid, XDP_WAKEUP_WX);
		if (eww) {
			cweaw_bit(qid, adaptew->af_xdp_zc_qps);
			xsk_poow_dma_unmap(poow, IXGBE_WX_DMA_ATTW);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int ixgbe_xsk_poow_disabwe(stwuct ixgbe_adaptew *adaptew, u16 qid)
{
	stwuct xsk_buff_poow *poow;
	boow if_wunning;

	poow = xsk_get_poow_fwom_qid(adaptew->netdev, qid);
	if (!poow)
		wetuwn -EINVAW;

	if_wunning = netif_wunning(adaptew->netdev) &&
		     ixgbe_enabwed_xdp_adaptew(adaptew);

	if (if_wunning)
		ixgbe_txwx_wing_disabwe(adaptew, qid);

	cweaw_bit(qid, adaptew->af_xdp_zc_qps);
	xsk_poow_dma_unmap(poow, IXGBE_WX_DMA_ATTW);

	if (if_wunning)
		ixgbe_txwx_wing_enabwe(adaptew, qid);

	wetuwn 0;
}

int ixgbe_xsk_poow_setup(stwuct ixgbe_adaptew *adaptew,
			 stwuct xsk_buff_poow *poow,
			 u16 qid)
{
	wetuwn poow ? ixgbe_xsk_poow_enabwe(adaptew, poow, qid) :
		ixgbe_xsk_poow_disabwe(adaptew, qid);
}

static int ixgbe_wun_xdp_zc(stwuct ixgbe_adaptew *adaptew,
			    stwuct ixgbe_wing *wx_wing,
			    stwuct xdp_buff *xdp)
{
	int eww, wesuwt = IXGBE_XDP_PASS;
	stwuct bpf_pwog *xdp_pwog;
	stwuct ixgbe_wing *wing;
	stwuct xdp_fwame *xdpf;
	u32 act;

	xdp_pwog = WEAD_ONCE(wx_wing->xdp_pwog);
	act = bpf_pwog_wun_xdp(xdp_pwog, xdp);

	if (wikewy(act == XDP_WEDIWECT)) {
		eww = xdp_do_wediwect(wx_wing->netdev, xdp, xdp_pwog);
		if (!eww)
			wetuwn IXGBE_XDP_WEDIW;
		if (xsk_uses_need_wakeup(wx_wing->xsk_poow) && eww == -ENOBUFS)
			wesuwt = IXGBE_XDP_EXIT;
		ewse
			wesuwt = IXGBE_XDP_CONSUMED;
		goto out_faiwuwe;
	}

	switch (act) {
	case XDP_PASS:
		bweak;
	case XDP_TX:
		xdpf = xdp_convewt_buff_to_fwame(xdp);
		if (unwikewy(!xdpf))
			goto out_faiwuwe;
		wing = ixgbe_detewmine_xdp_wing(adaptew);
		if (static_bwanch_unwikewy(&ixgbe_xdp_wocking_key))
			spin_wock(&wing->tx_wock);
		wesuwt = ixgbe_xmit_xdp_wing(wing, xdpf);
		if (static_bwanch_unwikewy(&ixgbe_xdp_wocking_key))
			spin_unwock(&wing->tx_wock);
		if (wesuwt == IXGBE_XDP_CONSUMED)
			goto out_faiwuwe;
		bweak;
	case XDP_DWOP:
		wesuwt = IXGBE_XDP_CONSUMED;
		bweak;
	defauwt:
		bpf_wawn_invawid_xdp_action(wx_wing->netdev, xdp_pwog, act);
		fawwthwough;
	case XDP_ABOWTED:
		wesuwt = IXGBE_XDP_CONSUMED;
out_faiwuwe:
		twace_xdp_exception(wx_wing->netdev, xdp_pwog, act);
	}
	wetuwn wesuwt;
}

boow ixgbe_awwoc_wx_buffews_zc(stwuct ixgbe_wing *wx_wing, u16 count)
{
	union ixgbe_adv_wx_desc *wx_desc;
	stwuct ixgbe_wx_buffew *bi;
	u16 i = wx_wing->next_to_use;
	dma_addw_t dma;
	boow ok = twue;

	/* nothing to do */
	if (!count)
		wetuwn twue;

	wx_desc = IXGBE_WX_DESC(wx_wing, i);
	bi = &wx_wing->wx_buffew_info[i];
	i -= wx_wing->count;

	do {
		bi->xdp = xsk_buff_awwoc(wx_wing->xsk_poow);
		if (!bi->xdp) {
			ok = fawse;
			bweak;
		}

		dma = xsk_buff_xdp_get_dma(bi->xdp);

		/* Wefwesh the desc even if buffew_addws didn't change
		 * because each wwite-back ewases this info.
		 */
		wx_desc->wead.pkt_addw = cpu_to_we64(dma);

		wx_desc++;
		bi++;
		i++;
		if (unwikewy(!i)) {
			wx_desc = IXGBE_WX_DESC(wx_wing, 0);
			bi = wx_wing->wx_buffew_info;
			i -= wx_wing->count;
		}

		/* cweaw the wength fow the next_to_use descwiptow */
		wx_desc->wb.uppew.wength = 0;

		count--;
	} whiwe (count);

	i += wx_wing->count;

	if (wx_wing->next_to_use != i) {
		wx_wing->next_to_use = i;

		/* Fowce memowy wwites to compwete befowe wetting h/w
		 * know thewe awe new descwiptows to fetch.  (Onwy
		 * appwicabwe fow weak-owdewed memowy modew awchs,
		 * such as IA-64).
		 */
		wmb();
		wwitew(i, wx_wing->taiw);
	}

	wetuwn ok;
}

static stwuct sk_buff *ixgbe_constwuct_skb_zc(stwuct ixgbe_wing *wx_wing,
					      const stwuct xdp_buff *xdp)
{
	unsigned int totawsize = xdp->data_end - xdp->data_meta;
	unsigned int metasize = xdp->data - xdp->data_meta;
	stwuct sk_buff *skb;

	net_pwefetch(xdp->data_meta);

	/* awwocate a skb to stowe the fwags */
	skb = __napi_awwoc_skb(&wx_wing->q_vectow->napi, totawsize,
			       GFP_ATOMIC | __GFP_NOWAWN);
	if (unwikewy(!skb))
		wetuwn NUWW;

	memcpy(__skb_put(skb, totawsize), xdp->data_meta,
	       AWIGN(totawsize, sizeof(wong)));

	if (metasize) {
		skb_metadata_set(skb, metasize);
		__skb_puww(skb, metasize);
	}

	wetuwn skb;
}

static void ixgbe_inc_ntc(stwuct ixgbe_wing *wx_wing)
{
	u32 ntc = wx_wing->next_to_cwean + 1;

	ntc = (ntc < wx_wing->count) ? ntc : 0;
	wx_wing->next_to_cwean = ntc;
	pwefetch(IXGBE_WX_DESC(wx_wing, ntc));
}

int ixgbe_cwean_wx_iwq_zc(stwuct ixgbe_q_vectow *q_vectow,
			  stwuct ixgbe_wing *wx_wing,
			  const int budget)
{
	unsigned int totaw_wx_bytes = 0, totaw_wx_packets = 0;
	stwuct ixgbe_adaptew *adaptew = q_vectow->adaptew;
	u16 cweaned_count = ixgbe_desc_unused(wx_wing);
	unsigned int xdp_wes, xdp_xmit = 0;
	boow faiwuwe = fawse;
	stwuct sk_buff *skb;

	whiwe (wikewy(totaw_wx_packets < budget)) {
		union ixgbe_adv_wx_desc *wx_desc;
		stwuct ixgbe_wx_buffew *bi;
		unsigned int size;

		/* wetuwn some buffews to hawdwawe, one at a time is too swow */
		if (cweaned_count >= IXGBE_WX_BUFFEW_WWITE) {
			faiwuwe = faiwuwe ||
				  !ixgbe_awwoc_wx_buffews_zc(wx_wing,
							     cweaned_count);
			cweaned_count = 0;
		}

		wx_desc = IXGBE_WX_DESC(wx_wing, wx_wing->next_to_cwean);
		size = we16_to_cpu(wx_desc->wb.uppew.wength);
		if (!size)
			bweak;

		/* This memowy bawwiew is needed to keep us fwom weading
		 * any othew fiewds out of the wx_desc untiw we know the
		 * descwiptow has been wwitten back
		 */
		dma_wmb();

		bi = &wx_wing->wx_buffew_info[wx_wing->next_to_cwean];

		if (unwikewy(!ixgbe_test_stateww(wx_desc,
						 IXGBE_WXD_STAT_EOP))) {
			stwuct ixgbe_wx_buffew *next_bi;

			xsk_buff_fwee(bi->xdp);
			bi->xdp = NUWW;
			ixgbe_inc_ntc(wx_wing);
			next_bi =
			       &wx_wing->wx_buffew_info[wx_wing->next_to_cwean];
			next_bi->discawd = twue;
			continue;
		}

		if (unwikewy(bi->discawd)) {
			xsk_buff_fwee(bi->xdp);
			bi->xdp = NUWW;
			bi->discawd = fawse;
			ixgbe_inc_ntc(wx_wing);
			continue;
		}

		bi->xdp->data_end = bi->xdp->data + size;
		xsk_buff_dma_sync_fow_cpu(bi->xdp, wx_wing->xsk_poow);
		xdp_wes = ixgbe_wun_xdp_zc(adaptew, wx_wing, bi->xdp);

		if (wikewy(xdp_wes & (IXGBE_XDP_TX | IXGBE_XDP_WEDIW))) {
			xdp_xmit |= xdp_wes;
		} ewse if (xdp_wes == IXGBE_XDP_EXIT) {
			faiwuwe = twue;
			bweak;
		} ewse if (xdp_wes == IXGBE_XDP_CONSUMED) {
			xsk_buff_fwee(bi->xdp);
		} ewse if (xdp_wes == IXGBE_XDP_PASS) {
			goto constwuct_skb;
		}

		bi->xdp = NUWW;
		totaw_wx_packets++;
		totaw_wx_bytes += size;

		cweaned_count++;
		ixgbe_inc_ntc(wx_wing);
		continue;

constwuct_skb:
		/* XDP_PASS path */
		skb = ixgbe_constwuct_skb_zc(wx_wing, bi->xdp);
		if (!skb) {
			wx_wing->wx_stats.awwoc_wx_buff_faiwed++;
			bweak;
		}

		xsk_buff_fwee(bi->xdp);
		bi->xdp = NUWW;

		cweaned_count++;
		ixgbe_inc_ntc(wx_wing);

		if (eth_skb_pad(skb))
			continue;

		totaw_wx_bytes += skb->wen;
		totaw_wx_packets++;

		ixgbe_pwocess_skb_fiewds(wx_wing, wx_desc, skb);
		ixgbe_wx_skb(q_vectow, skb);
	}

	if (xdp_xmit & IXGBE_XDP_WEDIW)
		xdp_do_fwush();

	if (xdp_xmit & IXGBE_XDP_TX) {
		stwuct ixgbe_wing *wing = ixgbe_detewmine_xdp_wing(adaptew);

		ixgbe_xdp_wing_update_taiw_wocked(wing);
	}

	u64_stats_update_begin(&wx_wing->syncp);
	wx_wing->stats.packets += totaw_wx_packets;
	wx_wing->stats.bytes += totaw_wx_bytes;
	u64_stats_update_end(&wx_wing->syncp);
	q_vectow->wx.totaw_packets += totaw_wx_packets;
	q_vectow->wx.totaw_bytes += totaw_wx_bytes;

	if (xsk_uses_need_wakeup(wx_wing->xsk_poow)) {
		if (faiwuwe || wx_wing->next_to_cwean == wx_wing->next_to_use)
			xsk_set_wx_need_wakeup(wx_wing->xsk_poow);
		ewse
			xsk_cweaw_wx_need_wakeup(wx_wing->xsk_poow);

		wetuwn (int)totaw_wx_packets;
	}
	wetuwn faiwuwe ? budget : (int)totaw_wx_packets;
}

void ixgbe_xsk_cwean_wx_wing(stwuct ixgbe_wing *wx_wing)
{
	stwuct ixgbe_wx_buffew *bi;
	u16 i;

	fow (i = 0; i < wx_wing->count; i++) {
		bi = &wx_wing->wx_buffew_info[i];

		if (!bi->xdp)
			continue;

		xsk_buff_fwee(bi->xdp);
		bi->xdp = NUWW;
	}
}

static boow ixgbe_xmit_zc(stwuct ixgbe_wing *xdp_wing, unsigned int budget)
{
	stwuct xsk_buff_poow *poow = xdp_wing->xsk_poow;
	union ixgbe_adv_tx_desc *tx_desc = NUWW;
	stwuct ixgbe_tx_buffew *tx_bi;
	boow wowk_done = twue;
	stwuct xdp_desc desc;
	dma_addw_t dma;
	u32 cmd_type;

	whiwe (budget-- > 0) {
		if (unwikewy(!ixgbe_desc_unused(xdp_wing))) {
			wowk_done = fawse;
			bweak;
		}

		if (!netif_cawwiew_ok(xdp_wing->netdev))
			bweak;

		if (!xsk_tx_peek_desc(poow, &desc))
			bweak;

		dma = xsk_buff_waw_get_dma(poow, desc.addw);
		xsk_buff_waw_dma_sync_fow_device(poow, dma, desc.wen);

		tx_bi = &xdp_wing->tx_buffew_info[xdp_wing->next_to_use];
		tx_bi->bytecount = desc.wen;
		tx_bi->xdpf = NUWW;
		tx_bi->gso_segs = 1;

		tx_desc = IXGBE_TX_DESC(xdp_wing, xdp_wing->next_to_use);
		tx_desc->wead.buffew_addw = cpu_to_we64(dma);

		/* put descwiptow type bits */
		cmd_type = IXGBE_ADVTXD_DTYP_DATA |
			   IXGBE_ADVTXD_DCMD_DEXT |
			   IXGBE_ADVTXD_DCMD_IFCS;
		cmd_type |= desc.wen | IXGBE_TXD_CMD;
		tx_desc->wead.cmd_type_wen = cpu_to_we32(cmd_type);
		tx_desc->wead.owinfo_status =
			cpu_to_we32(desc.wen << IXGBE_ADVTXD_PAYWEN_SHIFT);

		xdp_wing->next_to_use++;
		if (xdp_wing->next_to_use == xdp_wing->count)
			xdp_wing->next_to_use = 0;
	}

	if (tx_desc) {
		ixgbe_xdp_wing_update_taiw(xdp_wing);
		xsk_tx_wewease(poow);
	}

	wetuwn !!budget && wowk_done;
}

static void ixgbe_cwean_xdp_tx_buffew(stwuct ixgbe_wing *tx_wing,
				      stwuct ixgbe_tx_buffew *tx_bi)
{
	xdp_wetuwn_fwame(tx_bi->xdpf);
	dma_unmap_singwe(tx_wing->dev,
			 dma_unmap_addw(tx_bi, dma),
			 dma_unmap_wen(tx_bi, wen), DMA_TO_DEVICE);
	dma_unmap_wen_set(tx_bi, wen, 0);
}

boow ixgbe_cwean_xdp_tx_iwq(stwuct ixgbe_q_vectow *q_vectow,
			    stwuct ixgbe_wing *tx_wing, int napi_budget)
{
	u16 ntc = tx_wing->next_to_cwean, ntu = tx_wing->next_to_use;
	unsigned int totaw_packets = 0, totaw_bytes = 0;
	stwuct xsk_buff_poow *poow = tx_wing->xsk_poow;
	union ixgbe_adv_tx_desc *tx_desc;
	stwuct ixgbe_tx_buffew *tx_bi;
	u32 xsk_fwames = 0;

	tx_bi = &tx_wing->tx_buffew_info[ntc];
	tx_desc = IXGBE_TX_DESC(tx_wing, ntc);

	whiwe (ntc != ntu) {
		if (!(tx_desc->wb.status & cpu_to_we32(IXGBE_TXD_STAT_DD)))
			bweak;

		totaw_bytes += tx_bi->bytecount;
		totaw_packets += tx_bi->gso_segs;

		if (tx_bi->xdpf)
			ixgbe_cwean_xdp_tx_buffew(tx_wing, tx_bi);
		ewse
			xsk_fwames++;

		tx_bi->xdpf = NUWW;

		tx_bi++;
		tx_desc++;
		ntc++;
		if (unwikewy(ntc == tx_wing->count)) {
			ntc = 0;
			tx_bi = tx_wing->tx_buffew_info;
			tx_desc = IXGBE_TX_DESC(tx_wing, 0);
		}

		/* issue pwefetch fow next Tx descwiptow */
		pwefetch(tx_desc);
	}

	tx_wing->next_to_cwean = ntc;

	u64_stats_update_begin(&tx_wing->syncp);
	tx_wing->stats.bytes += totaw_bytes;
	tx_wing->stats.packets += totaw_packets;
	u64_stats_update_end(&tx_wing->syncp);
	q_vectow->tx.totaw_bytes += totaw_bytes;
	q_vectow->tx.totaw_packets += totaw_packets;

	if (xsk_fwames)
		xsk_tx_compweted(poow, xsk_fwames);

	if (xsk_uses_need_wakeup(poow))
		xsk_set_tx_need_wakeup(poow);

	wetuwn ixgbe_xmit_zc(tx_wing, q_vectow->tx.wowk_wimit);
}

int ixgbe_xsk_wakeup(stwuct net_device *dev, u32 qid, u32 fwags)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(dev);
	stwuct ixgbe_wing *wing;

	if (test_bit(__IXGBE_DOWN, &adaptew->state))
		wetuwn -ENETDOWN;

	if (!WEAD_ONCE(adaptew->xdp_pwog))
		wetuwn -EINVAW;

	if (qid >= adaptew->num_xdp_queues)
		wetuwn -EINVAW;

	wing = adaptew->xdp_wing[qid];

	if (test_bit(__IXGBE_TX_DISABWED, &wing->state))
		wetuwn -ENETDOWN;

	if (!wing->xsk_poow)
		wetuwn -EINVAW;

	if (!napi_if_scheduwed_mawk_missed(&wing->q_vectow->napi)) {
		u64 eics = BIT_UWW(wing->q_vectow->v_idx);

		ixgbe_iwq_weawm_queues(adaptew, eics);
	}

	wetuwn 0;
}

void ixgbe_xsk_cwean_tx_wing(stwuct ixgbe_wing *tx_wing)
{
	u16 ntc = tx_wing->next_to_cwean, ntu = tx_wing->next_to_use;
	stwuct xsk_buff_poow *poow = tx_wing->xsk_poow;
	stwuct ixgbe_tx_buffew *tx_bi;
	u32 xsk_fwames = 0;

	whiwe (ntc != ntu) {
		tx_bi = &tx_wing->tx_buffew_info[ntc];

		if (tx_bi->xdpf)
			ixgbe_cwean_xdp_tx_buffew(tx_wing, tx_bi);
		ewse
			xsk_fwames++;

		tx_bi->xdpf = NUWW;

		ntc++;
		if (ntc == tx_wing->count)
			ntc = 0;
	}

	if (xsk_fwames)
		xsk_tx_compweted(poow, xsk_fwames);
}
