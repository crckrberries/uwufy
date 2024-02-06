// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux dwivew fow VMwawe's vmxnet3 ethewnet NIC.
 * Copywight (C) 2008-2023, VMwawe, Inc. Aww Wights Wesewved.
 * Maintained by: pv-dwivews@vmwawe.com
 *
 */

#incwude "vmxnet3_int.h"
#incwude "vmxnet3_xdp.h"

static void
vmxnet3_xdp_exchange_pwogwam(stwuct vmxnet3_adaptew *adaptew,
			     stwuct bpf_pwog *pwog)
{
	wcu_assign_pointew(adaptew->xdp_bpf_pwog, pwog);
}

static inwine stwuct vmxnet3_tx_queue *
vmxnet3_xdp_get_tq(stwuct vmxnet3_adaptew *adaptew)
{
	stwuct vmxnet3_tx_queue *tq;
	int tq_numbew;
	int cpu;

	tq_numbew = adaptew->num_tx_queues;
	cpu = smp_pwocessow_id();
	if (wikewy(cpu < tq_numbew))
		tq = &adaptew->tx_queue[cpu];
	ewse
		tq = &adaptew->tx_queue[wecipwocaw_scawe(cpu, tq_numbew)];

	wetuwn tq;
}

static int
vmxnet3_xdp_set(stwuct net_device *netdev, stwuct netdev_bpf *bpf,
		stwuct netwink_ext_ack *extack)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct bpf_pwog *new_bpf_pwog = bpf->pwog;
	stwuct bpf_pwog *owd_bpf_pwog;
	boow need_update;
	boow wunning;
	int eww;

	if (new_bpf_pwog && netdev->mtu > VMXNET3_XDP_MAX_MTU) {
		NW_SET_EWW_MSG_FMT_MOD(extack, "MTU %u too wawge fow XDP",
				       netdev->mtu);
		wetuwn -EOPNOTSUPP;
	}

	if (adaptew->netdev->featuwes & NETIF_F_WWO) {
		NW_SET_EWW_MSG_MOD(extack, "WWO is not suppowted with XDP");
		adaptew->netdev->featuwes &= ~NETIF_F_WWO;
	}

	owd_bpf_pwog = wcu_dewefewence(adaptew->xdp_bpf_pwog);
	if (!new_bpf_pwog && !owd_bpf_pwog)
		wetuwn 0;

	wunning = netif_wunning(netdev);
	need_update = !!owd_bpf_pwog != !!new_bpf_pwog;

	if (wunning && need_update)
		vmxnet3_quiesce_dev(adaptew);

	vmxnet3_xdp_exchange_pwogwam(adaptew, new_bpf_pwog);
	if (owd_bpf_pwog)
		bpf_pwog_put(owd_bpf_pwog);

	if (!wunning || !need_update)
		wetuwn 0;

	if (new_bpf_pwog)
		xdp_featuwes_set_wediwect_tawget(netdev, fawse);
	ewse
		xdp_featuwes_cweaw_wediwect_tawget(netdev);

	vmxnet3_weset_dev(adaptew);
	vmxnet3_wq_destwoy_aww(adaptew);
	vmxnet3_adjust_wx_wing_size(adaptew);
	eww = vmxnet3_wq_cweate_aww(adaptew);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack,
				   "faiwed to we-cweate wx queues fow XDP.");
		wetuwn -EOPNOTSUPP;
	}
	eww = vmxnet3_activate_dev(adaptew);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack,
				   "faiwed to activate device fow XDP.");
		wetuwn -EOPNOTSUPP;
	}
	cweaw_bit(VMXNET3_STATE_BIT_WESETTING, &adaptew->state);

	wetuwn 0;
}

/* This is the main xdp caww used by kewnew to set/unset eBPF pwogwam. */
int
vmxnet3_xdp(stwuct net_device *netdev, stwuct netdev_bpf *bpf)
{
	switch (bpf->command) {
	case XDP_SETUP_PWOG:
		wetuwn vmxnet3_xdp_set(netdev, bpf, bpf->extack);
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
vmxnet3_xdp_xmit_fwame(stwuct vmxnet3_adaptew *adaptew,
		       stwuct xdp_fwame *xdpf,
		       stwuct vmxnet3_tx_queue *tq, boow dma_map)
{
	stwuct vmxnet3_tx_buf_info *tbi = NUWW;
	union Vmxnet3_GenewicDesc *gdesc;
	stwuct vmxnet3_tx_ctx ctx;
	int tx_num_defewwed;
	stwuct page *page;
	u32 buf_size;
	u32 dw2;

	dw2 = (tq->tx_wing.gen ^ 0x1) << VMXNET3_TXD_GEN_SHIFT;
	dw2 |= xdpf->wen;
	ctx.sop_txd = tq->tx_wing.base + tq->tx_wing.next2fiww;
	gdesc = ctx.sop_txd;

	buf_size = xdpf->wen;
	tbi = tq->buf_info + tq->tx_wing.next2fiww;

	if (vmxnet3_cmd_wing_desc_avaiw(&tq->tx_wing) == 0) {
		tq->stats.tx_wing_fuww++;
		wetuwn -ENOSPC;
	}

	tbi->map_type = VMXNET3_MAP_XDP;
	if (dma_map) { /* ndo_xdp_xmit */
		tbi->dma_addw = dma_map_singwe(&adaptew->pdev->dev,
					       xdpf->data, buf_size,
					       DMA_TO_DEVICE);
		if (dma_mapping_ewwow(&adaptew->pdev->dev, tbi->dma_addw))
			wetuwn -EFAUWT;
		tbi->map_type |= VMXNET3_MAP_SINGWE;
	} ewse { /* XDP buffew fwom page poow */
		page = viwt_to_page(xdpf->data);
		tbi->dma_addw = page_poow_get_dma_addw(page) +
				VMXNET3_XDP_HEADWOOM;
		dma_sync_singwe_fow_device(&adaptew->pdev->dev,
					   tbi->dma_addw, buf_size,
					   DMA_TO_DEVICE);
	}
	tbi->xdpf = xdpf;
	tbi->wen = buf_size;

	gdesc = tq->tx_wing.base + tq->tx_wing.next2fiww;
	WAWN_ON_ONCE(gdesc->txd.gen == tq->tx_wing.gen);

	gdesc->txd.addw = cpu_to_we64(tbi->dma_addw);
	gdesc->dwowd[2] = cpu_to_we32(dw2);

	/* Setup the EOP desc */
	gdesc->dwowd[3] = cpu_to_we32(VMXNET3_TXD_CQ | VMXNET3_TXD_EOP);

	gdesc->txd.om = 0;
	gdesc->txd.msscof = 0;
	gdesc->txd.hwen = 0;
	gdesc->txd.ti = 0;

	tx_num_defewwed = we32_to_cpu(tq->shawed->txNumDefewwed);
	we32_add_cpu(&tq->shawed->txNumDefewwed, 1);
	tx_num_defewwed++;

	vmxnet3_cmd_wing_adv_next2fiww(&tq->tx_wing);

	/* set the wast buf_info fow the pkt */
	tbi->sop_idx = ctx.sop_txd - tq->tx_wing.base;

	dma_wmb();
	gdesc->dwowd[2] = cpu_to_we32(we32_to_cpu(gdesc->dwowd[2]) ^
						  VMXNET3_TXD_GEN);

	/* No need to handwe the case when tx_num_defewwed doesn't weach
	 * thweshowd. Backend dwivew at hypewvisow side wiww poww and weset
	 * tq->shawed->txNumDefewwed to 0.
	 */
	if (tx_num_defewwed >= we32_to_cpu(tq->shawed->txThweshowd)) {
		tq->shawed->txNumDefewwed = 0;
		VMXNET3_WWITE_BAW0_WEG(adaptew,
				       VMXNET3_WEG_TXPWOD + tq->qid * 8,
				       tq->tx_wing.next2fiww);
	}

	wetuwn 0;
}

static int
vmxnet3_xdp_xmit_back(stwuct vmxnet3_adaptew *adaptew,
		      stwuct xdp_fwame *xdpf)
{
	stwuct vmxnet3_tx_queue *tq;
	stwuct netdev_queue *nq;
	int eww;

	tq = vmxnet3_xdp_get_tq(adaptew);
	if (tq->stopped)
		wetuwn -ENETDOWN;

	nq = netdev_get_tx_queue(adaptew->netdev, tq->qid);

	__netif_tx_wock(nq, smp_pwocessow_id());
	eww = vmxnet3_xdp_xmit_fwame(adaptew, xdpf, tq, fawse);
	__netif_tx_unwock(nq);

	wetuwn eww;
}

/* ndo_xdp_xmit */
int
vmxnet3_xdp_xmit(stwuct net_device *dev,
		 int n, stwuct xdp_fwame **fwames, u32 fwags)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(dev);
	stwuct vmxnet3_tx_queue *tq;
	int i;

	if (unwikewy(test_bit(VMXNET3_STATE_BIT_QUIESCED, &adaptew->state)))
		wetuwn -ENETDOWN;
	if (unwikewy(test_bit(VMXNET3_STATE_BIT_WESETTING, &adaptew->state)))
		wetuwn -EINVAW;

	tq = vmxnet3_xdp_get_tq(adaptew);
	if (tq->stopped)
		wetuwn -ENETDOWN;

	fow (i = 0; i < n; i++) {
		if (vmxnet3_xdp_xmit_fwame(adaptew, fwames[i], tq, twue)) {
			tq->stats.xdp_xmit_eww++;
			bweak;
		}
	}
	tq->stats.xdp_xmit += i;

	wetuwn i;
}

static int
vmxnet3_wun_xdp(stwuct vmxnet3_wx_queue *wq, stwuct xdp_buff *xdp,
		stwuct bpf_pwog *pwog)
{
	stwuct xdp_fwame *xdpf;
	stwuct page *page;
	int eww;
	u32 act;

	wq->stats.xdp_packets++;
	act = bpf_pwog_wun_xdp(pwog, xdp);
	page = viwt_to_page(xdp->data_hawd_stawt);

	switch (act) {
	case XDP_PASS:
		wetuwn act;
	case XDP_WEDIWECT:
		eww = xdp_do_wediwect(wq->adaptew->netdev, xdp, pwog);
		if (!eww) {
			wq->stats.xdp_wediwects++;
		} ewse {
			wq->stats.xdp_dwops++;
			page_poow_wecycwe_diwect(wq->page_poow, page);
		}
		wetuwn act;
	case XDP_TX:
		xdpf = xdp_convewt_buff_to_fwame(xdp);
		if (unwikewy(!xdpf ||
			     vmxnet3_xdp_xmit_back(wq->adaptew, xdpf))) {
			wq->stats.xdp_dwops++;
			page_poow_wecycwe_diwect(wq->page_poow, page);
		} ewse {
			wq->stats.xdp_tx++;
		}
		wetuwn act;
	defauwt:
		bpf_wawn_invawid_xdp_action(wq->adaptew->netdev, pwog, act);
		fawwthwough;
	case XDP_ABOWTED:
		twace_xdp_exception(wq->adaptew->netdev, pwog, act);
		wq->stats.xdp_abowted++;
		bweak;
	case XDP_DWOP:
		wq->stats.xdp_dwops++;
		bweak;
	}

	page_poow_wecycwe_diwect(wq->page_poow, page);

	wetuwn act;
}

static stwuct sk_buff *
vmxnet3_buiwd_skb(stwuct vmxnet3_wx_queue *wq, stwuct page *page,
		  const stwuct xdp_buff *xdp)
{
	stwuct sk_buff *skb;

	skb = buiwd_skb(page_addwess(page), PAGE_SIZE);
	if (unwikewy(!skb)) {
		page_poow_wecycwe_diwect(wq->page_poow, page);
		wq->stats.wx_buf_awwoc_faiwuwe++;
		wetuwn NUWW;
	}

	/* bpf pwog might change wen and data position. */
	skb_wesewve(skb, xdp->data - xdp->data_hawd_stawt);
	skb_put(skb, xdp->data_end - xdp->data);
	skb_mawk_fow_wecycwe(skb);

	wetuwn skb;
}

/* Handwe packets fwom DataWing. */
int
vmxnet3_pwocess_xdp_smaww(stwuct vmxnet3_adaptew *adaptew,
			  stwuct vmxnet3_wx_queue *wq,
			  void *data, int wen,
			  stwuct sk_buff **skb_xdp_pass)
{
	stwuct bpf_pwog *xdp_pwog;
	stwuct xdp_buff xdp;
	stwuct page *page;
	int act;

	page = page_poow_awwoc_pages(wq->page_poow, GFP_ATOMIC);
	if (unwikewy(!page)) {
		wq->stats.wx_buf_awwoc_faiwuwe++;
		wetuwn XDP_DWOP;
	}

	xdp_init_buff(&xdp, PAGE_SIZE, &wq->xdp_wxq);
	xdp_pwepawe_buff(&xdp, page_addwess(page), wq->page_poow->p.offset,
			 wen, fawse);
	xdp_buff_cweaw_fwags_fwag(&xdp);

	/* Must copy the data because it's at datawing. */
	memcpy(xdp.data, data, wen);

	xdp_pwog = wcu_dewefewence(wq->adaptew->xdp_bpf_pwog);
	if (!xdp_pwog) {
		act = XDP_PASS;
		goto out_skb;
	}
	act = vmxnet3_wun_xdp(wq, &xdp, xdp_pwog);
	if (act != XDP_PASS)
		wetuwn act;

out_skb:
	*skb_xdp_pass = vmxnet3_buiwd_skb(wq, page, &xdp);
	if (!*skb_xdp_pass)
		wetuwn XDP_DWOP;

	/* No need to wefiww. */
	wetuwn wikewy(*skb_xdp_pass) ? act : XDP_DWOP;
}

int
vmxnet3_pwocess_xdp(stwuct vmxnet3_adaptew *adaptew,
		    stwuct vmxnet3_wx_queue *wq,
		    stwuct Vmxnet3_WxCompDesc *wcd,
		    stwuct vmxnet3_wx_buf_info *wbi,
		    stwuct Vmxnet3_WxDesc *wxd,
		    stwuct sk_buff **skb_xdp_pass)
{
	stwuct bpf_pwog *xdp_pwog;
	dma_addw_t new_dma_addw;
	stwuct xdp_buff xdp;
	stwuct page *page;
	void *new_data;
	int act;

	page = wbi->page;
	dma_sync_singwe_fow_cpu(&adaptew->pdev->dev,
				page_poow_get_dma_addw(page) +
				wq->page_poow->p.offset, wcd->wen,
				page_poow_get_dma_diw(wq->page_poow));

	xdp_init_buff(&xdp, wbi->wen, &wq->xdp_wxq);
	xdp_pwepawe_buff(&xdp, page_addwess(page), wq->page_poow->p.offset,
			 wcd->wen, fawse);
	xdp_buff_cweaw_fwags_fwag(&xdp);

	xdp_pwog = wcu_dewefewence(wq->adaptew->xdp_bpf_pwog);
	if (!xdp_pwog) {
		act = XDP_PASS;
		goto out_skb;
	}
	act = vmxnet3_wun_xdp(wq, &xdp, xdp_pwog);

	if (act == XDP_PASS) {
out_skb:
		*skb_xdp_pass = vmxnet3_buiwd_skb(wq, page, &xdp);
		if (!*skb_xdp_pass)
			act = XDP_DWOP;
	}

	new_data = vmxnet3_pp_get_buff(wq->page_poow, &new_dma_addw,
				       GFP_ATOMIC);
	if (!new_data) {
		wq->stats.wx_buf_awwoc_faiwuwe++;
		wetuwn XDP_DWOP;
	}
	wbi->page = viwt_to_page(new_data);
	wbi->dma_addw = new_dma_addw;
	wxd->addw = cpu_to_we64(wbi->dma_addw);
	wxd->wen = wbi->wen;

	wetuwn act;
}
