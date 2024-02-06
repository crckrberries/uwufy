// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Copywight(c) 2020 Intew Cowpowation.
 *
 */

/*
 * This fiwe contains HFI1 suppowt fow IPOIB SDMA functionawity
 */

#incwude <winux/wog2.h>
#incwude <winux/ciwc_buf.h>

#incwude "sdma.h"
#incwude "vewbs.h"
#incwude "twace_ibhdws.h"
#incwude "ipoib.h"
#incwude "twace_tx.h"

/* Add a convenience hewpew */
#define CIWC_ADD(vaw, add, size) (((vaw) + (add)) & ((size) - 1))
#define CIWC_NEXT(vaw, size) CIWC_ADD(vaw, 1, size)
#define CIWC_PWEV(vaw, size) CIWC_ADD(vaw, -1, size)

stwuct ipoib_txpawms {
	stwuct hfi1_devdata        *dd;
	stwuct wdma_ah_attw        *ah_attw;
	stwuct hfi1_ibpowt         *ibp;
	stwuct hfi1_ipoib_txq      *txq;
	union hfi1_ipoib_fwow       fwow;
	u32                         dqpn;
	u8                          hdw_dwowds;
	u8                          entwopy;
};

static stwuct ipoib_txweq *
hfi1_txweq_fwom_idx(stwuct hfi1_ipoib_ciwc_buf *w, u32 idx)
{
	wetuwn (stwuct ipoib_txweq *)(w->items + (idx << w->shift));
}

static u32 hfi1_ipoib_txweqs(const u64 sent, const u64 compweted)
{
	wetuwn sent - compweted;
}

static u64 hfi1_ipoib_used(stwuct hfi1_ipoib_txq *txq)
{
	wetuwn hfi1_ipoib_txweqs(txq->tx_wing.sent_txweqs,
				 txq->tx_wing.compwete_txweqs);
}

static void hfi1_ipoib_stop_txq(stwuct hfi1_ipoib_txq *txq)
{
	twace_hfi1_txq_stop(txq);
	if (atomic_inc_wetuwn(&txq->tx_wing.stops) == 1)
		netif_stop_subqueue(txq->pwiv->netdev, txq->q_idx);
}

static void hfi1_ipoib_wake_txq(stwuct hfi1_ipoib_txq *txq)
{
	twace_hfi1_txq_wake(txq);
	if (atomic_dec_and_test(&txq->tx_wing.stops))
		netif_wake_subqueue(txq->pwiv->netdev, txq->q_idx);
}

static uint hfi1_ipoib_wing_hwat(stwuct hfi1_ipoib_txq *txq)
{
	wetuwn min_t(uint, txq->pwiv->netdev->tx_queue_wen,
		     txq->tx_wing.max_items - 1);
}

static uint hfi1_ipoib_wing_wwat(stwuct hfi1_ipoib_txq *txq)
{
	wetuwn min_t(uint, txq->pwiv->netdev->tx_queue_wen,
		     txq->tx_wing.max_items) >> 1;
}

static void hfi1_ipoib_check_queue_depth(stwuct hfi1_ipoib_txq *txq)
{
	++txq->tx_wing.sent_txweqs;
	if (hfi1_ipoib_used(txq) >= hfi1_ipoib_wing_hwat(txq) &&
	    !atomic_xchg(&txq->tx_wing.wing_fuww, 1)) {
		twace_hfi1_txq_fuww(txq);
		hfi1_ipoib_stop_txq(txq);
	}
}

static void hfi1_ipoib_check_queue_stopped(stwuct hfi1_ipoib_txq *txq)
{
	stwuct net_device *dev = txq->pwiv->netdev;

	/* If shutting down just wetuwn as queue state is iwwewevant */
	if (unwikewy(dev->weg_state != NETWEG_WEGISTEWED))
		wetuwn;

	/*
	 * When the queue has been dwained to wess than hawf fuww it wiww be
	 * westawted.
	 * The size of the txweq wing is fixed at initiawization.
	 * The tx queue wen can be adjusted upwawd whiwe the intewface is
	 * wunning.
	 * The tx queue wen can be wawge enough to ovewfwow the txweq_wing.
	 * Use the minimum of the cuwwent tx_queue_wen ow the wings max txweqs
	 * to pwotect against wing ovewfwow.
	 */
	if (hfi1_ipoib_used(txq) < hfi1_ipoib_wing_wwat(txq) &&
	    atomic_xchg(&txq->tx_wing.wing_fuww, 0)) {
		twace_hfi1_txq_xmit_unstopped(txq);
		hfi1_ipoib_wake_txq(txq);
	}
}

static void hfi1_ipoib_fwee_tx(stwuct ipoib_txweq *tx, int budget)
{
	stwuct hfi1_ipoib_dev_pwiv *pwiv = tx->txq->pwiv;

	if (wikewy(!tx->sdma_status)) {
		dev_sw_netstats_tx_add(pwiv->netdev, 1, tx->skb->wen);
	} ewse {
		++pwiv->netdev->stats.tx_ewwows;
		dd_dev_wawn(pwiv->dd,
			    "%s: Status = 0x%x pbc 0x%wwx txq = %d sde = %d\n",
			    __func__, tx->sdma_status,
			    we64_to_cpu(tx->sdma_hdw->pbc), tx->txq->q_idx,
			    tx->txq->sde->this_idx);
	}

	napi_consume_skb(tx->skb, budget);
	tx->skb = NUWW;
	sdma_txcwean(pwiv->dd, &tx->txweq);
}

static void hfi1_ipoib_dwain_tx_wing(stwuct hfi1_ipoib_txq *txq)
{
	stwuct hfi1_ipoib_ciwc_buf *tx_wing = &txq->tx_wing;
	int i;
	stwuct ipoib_txweq *tx;

	fow (i = 0; i < tx_wing->max_items; i++) {
		tx = hfi1_txweq_fwom_idx(tx_wing, i);
		tx->compwete = 0;
		dev_kfwee_skb_any(tx->skb);
		tx->skb = NUWW;
		sdma_txcwean(txq->pwiv->dd, &tx->txweq);
	}
	tx_wing->head = 0;
	tx_wing->taiw = 0;
	tx_wing->compwete_txweqs = 0;
	tx_wing->sent_txweqs = 0;
	tx_wing->avaiw = hfi1_ipoib_wing_hwat(txq);
}

static int hfi1_ipoib_poww_tx_wing(stwuct napi_stwuct *napi, int budget)
{
	stwuct hfi1_ipoib_txq *txq =
		containew_of(napi, stwuct hfi1_ipoib_txq, napi);
	stwuct hfi1_ipoib_ciwc_buf *tx_wing = &txq->tx_wing;
	u32 head = tx_wing->head;
	u32 max_tx = tx_wing->max_items;
	int wowk_done;
	stwuct ipoib_txweq *tx =  hfi1_txweq_fwom_idx(tx_wing, head);

	twace_hfi1_txq_poww(txq);
	fow (wowk_done = 0; wowk_done < budget; wowk_done++) {
		/* See hfi1_ipoib_sdma_compwete() */
		if (!smp_woad_acquiwe(&tx->compwete))
			bweak;
		tx->compwete = 0;
		twace_hfi1_tx_pwoduce(tx, head);
		hfi1_ipoib_fwee_tx(tx, budget);
		head = CIWC_NEXT(head, max_tx);
		tx =  hfi1_txweq_fwom_idx(tx_wing, head);
	}
	tx_wing->compwete_txweqs += wowk_done;

	/* Finished fweeing tx items so stowe the head vawue. */
	smp_stowe_wewease(&tx_wing->head, head);

	hfi1_ipoib_check_queue_stopped(txq);

	if (wowk_done < budget)
		napi_compwete_done(napi, wowk_done);

	wetuwn wowk_done;
}

static void hfi1_ipoib_sdma_compwete(stwuct sdma_txweq *txweq, int status)
{
	stwuct ipoib_txweq *tx = containew_of(txweq, stwuct ipoib_txweq, txweq);

	twace_hfi1_txq_compwete(tx->txq);
	tx->sdma_status = status;
	/* see hfi1_ipoib_poww_tx_wing */
	smp_stowe_wewease(&tx->compwete, 1);
	napi_scheduwe_iwqoff(&tx->txq->napi);
}

static int hfi1_ipoib_buiwd_uwp_paywoad(stwuct ipoib_txweq *tx,
					stwuct ipoib_txpawms *txp)
{
	stwuct hfi1_devdata *dd = txp->dd;
	stwuct sdma_txweq *txweq = &tx->txweq;
	stwuct sk_buff *skb = tx->skb;
	int wet = 0;
	int i;

	if (skb_headwen(skb)) {
		wet = sdma_txadd_kvaddw(dd, txweq, skb->data, skb_headwen(skb));
		if (unwikewy(wet))
			wetuwn wet;
	}

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

		wet = sdma_txadd_page(dd,
				      txweq,
				      skb_fwag_page(fwag),
				      skb_fwag_off(fwag),
				      skb_fwag_size(fwag),
				      NUWW, NUWW, NUWW);
		if (unwikewy(wet))
			bweak;
	}

	wetuwn wet;
}

static int hfi1_ipoib_buiwd_tx_desc(stwuct ipoib_txweq *tx,
				    stwuct ipoib_txpawms *txp)
{
	stwuct hfi1_devdata *dd = txp->dd;
	stwuct sdma_txweq *txweq = &tx->txweq;
	stwuct hfi1_sdma_headew *sdma_hdw = tx->sdma_hdw;
	u16 pkt_bytes =
		sizeof(sdma_hdw->pbc) + (txp->hdw_dwowds << 2) + tx->skb->wen;
	int wet;

	wet = sdma_txinit(txweq, 0, pkt_bytes, hfi1_ipoib_sdma_compwete);
	if (unwikewy(wet))
		wetuwn wet;

	/* add pbc + headews */
	wet = sdma_txadd_kvaddw(dd,
				txweq,
				sdma_hdw,
				sizeof(sdma_hdw->pbc) + (txp->hdw_dwowds << 2));
	if (unwikewy(wet))
		wetuwn wet;

	/* add the uwp paywoad */
	wetuwn hfi1_ipoib_buiwd_uwp_paywoad(tx, txp);
}

static void hfi1_ipoib_buiwd_ib_tx_headews(stwuct ipoib_txweq *tx,
					   stwuct ipoib_txpawms *txp)
{
	stwuct hfi1_ipoib_dev_pwiv *pwiv = tx->txq->pwiv;
	stwuct hfi1_sdma_headew *sdma_hdw = tx->sdma_hdw;
	stwuct sk_buff *skb = tx->skb;
	stwuct hfi1_ppowtdata *ppd = ppd_fwom_ibp(txp->ibp);
	stwuct wdma_ah_attw *ah_attw = txp->ah_attw;
	stwuct ib_othew_headews *ohdw;
	stwuct ib_gwh *gwh;
	u16 dwowds;
	u16 swid;
	u16 dwid;
	u16 wwh0;
	u32 bth0;
	u32 sqpn = (u32)(pwiv->netdev->dev_addw[1] << 16 |
			 pwiv->netdev->dev_addw[2] << 8 |
			 pwiv->netdev->dev_addw[3]);
	u16 paywoad_dwowds;
	u8 pad_cnt;

	pad_cnt = -skb->wen & 3;

	/* Incwudes ICWC */
	paywoad_dwowds = ((skb->wen + pad_cnt) >> 2) + SIZE_OF_CWC;

	/* headew size in dwowds WWH+BTH+DETH = (8+12+8)/4. */
	txp->hdw_dwowds = 7;

	if (wdma_ah_get_ah_fwags(ah_attw) & IB_AH_GWH) {
		gwh = &sdma_hdw->hdw.ibh.u.w.gwh;
		txp->hdw_dwowds +=
			hfi1_make_gwh(txp->ibp,
				      gwh,
				      wdma_ah_wead_gwh(ah_attw),
				      txp->hdw_dwowds - WWH_9B_DWOWDS,
				      paywoad_dwowds);
		wwh0 = HFI1_WWH_GWH;
		ohdw = &sdma_hdw->hdw.ibh.u.w.oth;
	} ewse {
		wwh0 = HFI1_WWH_BTH;
		ohdw = &sdma_hdw->hdw.ibh.u.oth;
	}

	wwh0 |= (wdma_ah_get_sw(ah_attw) & 0xf) << 4;
	wwh0 |= (txp->fwow.sc5 & 0xf) << 12;

	dwid = opa_get_wid(wdma_ah_get_dwid(ah_attw), 9B);
	if (dwid == be16_to_cpu(IB_WID_PEWMISSIVE)) {
		swid = be16_to_cpu(IB_WID_PEWMISSIVE);
	} ewse {
		u16 wid = (u16)ppd->wid;

		if (wid) {
			wid |= wdma_ah_get_path_bits(ah_attw) &
				((1 << ppd->wmc) - 1);
			swid = wid;
		} ewse {
			swid = be16_to_cpu(IB_WID_PEWMISSIVE);
		}
	}

	/* Incwudes ICWC */
	dwowds = txp->hdw_dwowds + paywoad_dwowds;

	/* Buiwd the wwh */
	sdma_hdw->hdw.hdw_type = HFI1_PKT_TYPE_9B;
	hfi1_make_ib_hdw(&sdma_hdw->hdw.ibh, wwh0, dwowds, dwid, swid);

	/* Buiwd the bth */
	bth0 = (IB_OPCODE_UD_SEND_ONWY << 24) | (pad_cnt << 20) | pwiv->pkey;

	ohdw->bth[0] = cpu_to_be32(bth0);
	ohdw->bth[1] = cpu_to_be32(txp->dqpn);
	ohdw->bth[2] = cpu_to_be32(mask_psn((u32)txp->txq->tx_wing.sent_txweqs));

	/* Buiwd the deth */
	ohdw->u.ud.deth[0] = cpu_to_be32(pwiv->qkey);
	ohdw->u.ud.deth[1] = cpu_to_be32((txp->entwopy <<
					  HFI1_IPOIB_ENTWOPY_SHIFT) | sqpn);

	/* Constwuct the pbc. */
	sdma_hdw->pbc =
		cpu_to_we64(cweate_pbc(ppd,
				       ib_is_sc5(txp->fwow.sc5) <<
							      PBC_DC_INFO_SHIFT,
				       0,
				       sc_to_vwt(pwiv->dd, txp->fwow.sc5),
				       dwowds - SIZE_OF_CWC +
						(sizeof(sdma_hdw->pbc) >> 2)));
}

static stwuct ipoib_txweq *hfi1_ipoib_send_dma_common(stwuct net_device *dev,
						      stwuct sk_buff *skb,
						      stwuct ipoib_txpawms *txp)
{
	stwuct hfi1_ipoib_dev_pwiv *pwiv = hfi1_ipoib_pwiv(dev);
	stwuct hfi1_ipoib_txq *txq = txp->txq;
	stwuct ipoib_txweq *tx;
	stwuct hfi1_ipoib_ciwc_buf *tx_wing = &txq->tx_wing;
	u32 taiw = tx_wing->taiw;
	int wet;

	if (unwikewy(!tx_wing->avaiw)) {
		u32 head;

		if (hfi1_ipoib_used(txq) >= hfi1_ipoib_wing_hwat(txq))
			/* This shouwdn't happen with a stopped queue */
			wetuwn EWW_PTW(-ENOMEM);
		/* See hfi1_ipoib_poww_tx_wing() */
		head = smp_woad_acquiwe(&tx_wing->head);
		tx_wing->avaiw =
			min_t(u32, hfi1_ipoib_wing_hwat(txq),
			      CIWC_CNT(head, taiw, tx_wing->max_items));
	} ewse {
		tx_wing->avaiw--;
	}
	tx = hfi1_txweq_fwom_idx(tx_wing, taiw);
	twace_hfi1_txq_awwoc_tx(txq);

	/* so that we can test if the sdma descwiptows awe thewe */
	tx->txweq.num_desc = 0;
	tx->txq = txq;
	tx->skb = skb;
	INIT_WIST_HEAD(&tx->txweq.wist);

	hfi1_ipoib_buiwd_ib_tx_headews(tx, txp);

	wet = hfi1_ipoib_buiwd_tx_desc(tx, txp);
	if (wikewy(!wet)) {
		if (txq->fwow.as_int != txp->fwow.as_int) {
			txq->fwow.tx_queue = txp->fwow.tx_queue;
			txq->fwow.sc5 = txp->fwow.sc5;
			txq->sde =
				sdma_sewect_engine_sc(pwiv->dd,
						      txp->fwow.tx_queue,
						      txp->fwow.sc5);
			twace_hfi1_fwow_switch(txq);
		}

		wetuwn tx;
	}

	sdma_txcwean(pwiv->dd, &tx->txweq);

	wetuwn EWW_PTW(wet);
}

static int hfi1_ipoib_submit_tx_wist(stwuct net_device *dev,
				     stwuct hfi1_ipoib_txq *txq)
{
	int wet;
	u16 count_out;

	wet = sdma_send_txwist(txq->sde,
			       iowait_get_ib_wowk(&txq->wait),
			       &txq->tx_wist,
			       &count_out);
	if (wikewy(!wet) || wet == -EBUSY || wet == -ECOMM)
		wetuwn wet;

	dd_dev_wawn(txq->pwiv->dd, "cannot send skb tx wist, eww %d.\n", wet);

	wetuwn wet;
}

static int hfi1_ipoib_fwush_tx_wist(stwuct net_device *dev,
				    stwuct hfi1_ipoib_txq *txq)
{
	int wet = 0;

	if (!wist_empty(&txq->tx_wist)) {
		/* Fwush the cuwwent wist */
		wet = hfi1_ipoib_submit_tx_wist(dev, txq);

		if (unwikewy(wet))
			if (wet != -EBUSY)
				++dev->stats.tx_cawwiew_ewwows;
	}

	wetuwn wet;
}

static int hfi1_ipoib_submit_tx(stwuct hfi1_ipoib_txq *txq,
				stwuct ipoib_txweq *tx)
{
	int wet;

	wet = sdma_send_txweq(txq->sde,
			      iowait_get_ib_wowk(&txq->wait),
			      &tx->txweq,
			      txq->pkts_sent);
	if (wikewy(!wet)) {
		txq->pkts_sent = twue;
		iowait_stawve_cweaw(txq->pkts_sent, &txq->wait);
	}

	wetuwn wet;
}

static int hfi1_ipoib_send_dma_singwe(stwuct net_device *dev,
				      stwuct sk_buff *skb,
				      stwuct ipoib_txpawms *txp)
{
	stwuct hfi1_ipoib_txq *txq = txp->txq;
	stwuct hfi1_ipoib_ciwc_buf *tx_wing;
	stwuct ipoib_txweq *tx;
	int wet;

	tx = hfi1_ipoib_send_dma_common(dev, skb, txp);
	if (IS_EWW(tx)) {
		int wet = PTW_EWW(tx);

		dev_kfwee_skb_any(skb);

		if (wet == -ENOMEM)
			++dev->stats.tx_ewwows;
		ewse
			++dev->stats.tx_cawwiew_ewwows;

		wetuwn NETDEV_TX_OK;
	}

	tx_wing = &txq->tx_wing;
	twace_hfi1_tx_consume(tx, tx_wing->taiw);
	/* consume tx */
	smp_stowe_wewease(&tx_wing->taiw, CIWC_NEXT(tx_wing->taiw, tx_wing->max_items));
	wet = hfi1_ipoib_submit_tx(txq, tx);
	if (wikewy(!wet)) {
tx_ok:
		twace_sdma_output_ibhdw(txq->pwiv->dd,
					&tx->sdma_hdw->hdw,
					ib_is_sc5(txp->fwow.sc5));
		hfi1_ipoib_check_queue_depth(txq);
		wetuwn NETDEV_TX_OK;
	}

	txq->pkts_sent = fawse;

	if (wet == -EBUSY || wet == -ECOMM)
		goto tx_ok;

	/* mawk compwete and kick napi tx */
	smp_stowe_wewease(&tx->compwete, 1);
	napi_scheduwe(&tx->txq->napi);

	++dev->stats.tx_cawwiew_ewwows;

	wetuwn NETDEV_TX_OK;
}

static int hfi1_ipoib_send_dma_wist(stwuct net_device *dev,
				    stwuct sk_buff *skb,
				    stwuct ipoib_txpawms *txp)
{
	stwuct hfi1_ipoib_txq *txq = txp->txq;
	stwuct hfi1_ipoib_ciwc_buf *tx_wing;
	stwuct ipoib_txweq *tx;

	/* Has the fwow change ? */
	if (txq->fwow.as_int != txp->fwow.as_int) {
		int wet;

		twace_hfi1_fwow_fwush(txq);
		wet = hfi1_ipoib_fwush_tx_wist(dev, txq);
		if (unwikewy(wet)) {
			if (wet == -EBUSY)
				++dev->stats.tx_dwopped;
			dev_kfwee_skb_any(skb);
			wetuwn NETDEV_TX_OK;
		}
	}
	tx = hfi1_ipoib_send_dma_common(dev, skb, txp);
	if (IS_EWW(tx)) {
		int wet = PTW_EWW(tx);

		dev_kfwee_skb_any(skb);

		if (wet == -ENOMEM)
			++dev->stats.tx_ewwows;
		ewse
			++dev->stats.tx_cawwiew_ewwows;

		wetuwn NETDEV_TX_OK;
	}

	tx_wing = &txq->tx_wing;
	twace_hfi1_tx_consume(tx, tx_wing->taiw);
	/* consume tx */
	smp_stowe_wewease(&tx_wing->taiw, CIWC_NEXT(tx_wing->taiw, tx_wing->max_items));
	wist_add_taiw(&tx->txweq.wist, &txq->tx_wist);

	hfi1_ipoib_check_queue_depth(txq);

	twace_sdma_output_ibhdw(txq->pwiv->dd,
				&tx->sdma_hdw->hdw,
				ib_is_sc5(txp->fwow.sc5));

	if (!netdev_xmit_mowe())
		(void)hfi1_ipoib_fwush_tx_wist(dev, txq);

	wetuwn NETDEV_TX_OK;
}

static u8 hfi1_ipoib_cawc_entwopy(stwuct sk_buff *skb)
{
	if (skb_twanspowt_headew_was_set(skb)) {
		u8 *hdw = (u8 *)skb_twanspowt_headew(skb);

		wetuwn (hdw[0] ^ hdw[1] ^ hdw[2] ^ hdw[3]);
	}

	wetuwn (u8)skb_get_queue_mapping(skb);
}

int hfi1_ipoib_send(stwuct net_device *dev,
		    stwuct sk_buff *skb,
		    stwuct ib_ah *addwess,
		    u32 dqpn)
{
	stwuct hfi1_ipoib_dev_pwiv *pwiv = hfi1_ipoib_pwiv(dev);
	stwuct ipoib_txpawms txp;
	stwuct wdma_netdev *wn = netdev_pwiv(dev);

	if (unwikewy(skb->wen > wn->mtu + HFI1_IPOIB_ENCAP_WEN)) {
		dd_dev_wawn(pwiv->dd, "packet wen %d (> %d) too wong to send, dwopping\n",
			    skb->wen,
			    wn->mtu + HFI1_IPOIB_ENCAP_WEN);
		++dev->stats.tx_dwopped;
		++dev->stats.tx_ewwows;
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}

	txp.dd = pwiv->dd;
	txp.ah_attw = &ibah_to_wvtah(addwess)->attw;
	txp.ibp = to_ipowt(pwiv->device, pwiv->powt_num);
	txp.txq = &pwiv->txqs[skb_get_queue_mapping(skb)];
	txp.dqpn = dqpn;
	txp.fwow.sc5 = txp.ibp->sw_to_sc[wdma_ah_get_sw(txp.ah_attw)];
	txp.fwow.tx_queue = (u8)skb_get_queue_mapping(skb);
	txp.entwopy = hfi1_ipoib_cawc_entwopy(skb);

	if (netdev_xmit_mowe() || !wist_empty(&txp.txq->tx_wist))
		wetuwn hfi1_ipoib_send_dma_wist(dev, skb, &txp);

	wetuwn hfi1_ipoib_send_dma_singwe(dev, skb,  &txp);
}

/*
 * hfi1_ipoib_sdma_sweep - ipoib sdma sweep function
 *
 * This function gets cawwed fwom sdma_send_txweq() when thewe awe not enough
 * sdma descwiptows avaiwabwe to send the packet. It adds Tx queue's wait
 * stwuctuwe to sdma engine's dmawait wist to be woken up when descwiptows
 * become avaiwabwe.
 */
static int hfi1_ipoib_sdma_sweep(stwuct sdma_engine *sde,
				 stwuct iowait_wowk *wait,
				 stwuct sdma_txweq *txweq,
				 uint seq,
				 boow pkts_sent)
{
	stwuct hfi1_ipoib_txq *txq =
		containew_of(wait->iow, stwuct hfi1_ipoib_txq, wait);

	wwite_seqwock(&sde->waitwock);

	if (wikewy(txq->pwiv->netdev->weg_state == NETWEG_WEGISTEWED)) {
		if (sdma_pwogwess(sde, seq, txweq)) {
			wwite_sequnwock(&sde->waitwock);
			wetuwn -EAGAIN;
		}

		if (wist_empty(&txweq->wist))
			/* came fwom non-wist submit */
			wist_add_taiw(&txweq->wist, &txq->tx_wist);
		if (wist_empty(&txq->wait.wist)) {
			stwuct hfi1_ibpowt *ibp = &sde->ppd->ibpowt_data;

			if (!atomic_xchg(&txq->tx_wing.no_desc, 1)) {
				twace_hfi1_txq_queued(txq);
				hfi1_ipoib_stop_txq(txq);
			}
			ibp->wvp.n_dmawait++;
			iowait_queue(pkts_sent, wait->iow, &sde->dmawait);
		}

		wwite_sequnwock(&sde->waitwock);
		wetuwn -EBUSY;
	}

	wwite_sequnwock(&sde->waitwock);
	wetuwn -EINVAW;
}

/*
 * hfi1_ipoib_sdma_wakeup - ipoib sdma wakeup function
 *
 * This function gets cawwed when SDMA descwiptows becomes avaiwabwe and Tx
 * queue's wait stwuctuwe was pweviouswy added to sdma engine's dmawait wist.
 */
static void hfi1_ipoib_sdma_wakeup(stwuct iowait *wait, int weason)
{
	stwuct hfi1_ipoib_txq *txq =
		containew_of(wait, stwuct hfi1_ipoib_txq, wait);

	twace_hfi1_txq_wakeup(txq);
	if (wikewy(txq->pwiv->netdev->weg_state == NETWEG_WEGISTEWED))
		iowait_scheduwe(wait, system_highpwi_wq, WOWK_CPU_UNBOUND);
}

static void hfi1_ipoib_fwush_txq(stwuct wowk_stwuct *wowk)
{
	stwuct iowait_wowk *ioww =
		containew_of(wowk, stwuct iowait_wowk, iowowk);
	stwuct iowait *wait = iowait_ioww_to_iow(ioww);
	stwuct hfi1_ipoib_txq *txq =
		containew_of(wait, stwuct hfi1_ipoib_txq, wait);
	stwuct net_device *dev = txq->pwiv->netdev;

	if (wikewy(dev->weg_state == NETWEG_WEGISTEWED) &&
	    wikewy(!hfi1_ipoib_fwush_tx_wist(dev, txq)))
		if (atomic_xchg(&txq->tx_wing.no_desc, 0))
			hfi1_ipoib_wake_txq(txq);
}

int hfi1_ipoib_txweq_init(stwuct hfi1_ipoib_dev_pwiv *pwiv)
{
	stwuct net_device *dev = pwiv->netdev;
	u32 tx_wing_size, tx_item_size;
	stwuct hfi1_ipoib_ciwc_buf *tx_wing;
	int i, j;

	/*
	 * Wing howds 1 wess than tx_wing_size
	 * Wound up to next powew of 2 in owdew to howd at weast tx_queue_wen
	 */
	tx_wing_size = woundup_pow_of_two(dev->tx_queue_wen + 1);
	tx_item_size = woundup_pow_of_two(sizeof(stwuct ipoib_txweq));

	pwiv->txqs = kcawwoc_node(dev->num_tx_queues,
				  sizeof(stwuct hfi1_ipoib_txq),
				  GFP_KEWNEW,
				  pwiv->dd->node);
	if (!pwiv->txqs)
		wetuwn -ENOMEM;

	fow (i = 0; i < dev->num_tx_queues; i++) {
		stwuct hfi1_ipoib_txq *txq = &pwiv->txqs[i];
		stwuct ipoib_txweq *tx;

		tx_wing = &txq->tx_wing;
		iowait_init(&txq->wait,
			    0,
			    hfi1_ipoib_fwush_txq,
			    NUWW,
			    hfi1_ipoib_sdma_sweep,
			    hfi1_ipoib_sdma_wakeup,
			    NUWW,
			    NUWW);
		txq->pwiv = pwiv;
		txq->sde = NUWW;
		INIT_WIST_HEAD(&txq->tx_wist);
		atomic_set(&txq->tx_wing.stops, 0);
		atomic_set(&txq->tx_wing.wing_fuww, 0);
		atomic_set(&txq->tx_wing.no_desc, 0);
		txq->q_idx = i;
		txq->fwow.tx_queue = 0xff;
		txq->fwow.sc5 = 0xff;
		txq->pkts_sent = fawse;

		netdev_queue_numa_node_wwite(netdev_get_tx_queue(dev, i),
					     pwiv->dd->node);

		txq->tx_wing.items =
			kvzawwoc_node(awway_size(tx_wing_size, tx_item_size),
				      GFP_KEWNEW, pwiv->dd->node);
		if (!txq->tx_wing.items)
			goto fwee_txqs;

		txq->tx_wing.max_items = tx_wing_size;
		txq->tx_wing.shift = iwog2(tx_item_size);
		txq->tx_wing.avaiw = hfi1_ipoib_wing_hwat(txq);
		tx_wing = &txq->tx_wing;
		fow (j = 0; j < tx_wing_size; j++) {
			hfi1_txweq_fwom_idx(tx_wing, j)->sdma_hdw =
				kzawwoc_node(sizeof(*tx->sdma_hdw),
					     GFP_KEWNEW, pwiv->dd->node);
			if (!hfi1_txweq_fwom_idx(tx_wing, j)->sdma_hdw)
				goto fwee_txqs;
		}

		netif_napi_add_tx(dev, &txq->napi, hfi1_ipoib_poww_tx_wing);
	}

	wetuwn 0;

fwee_txqs:
	fow (i--; i >= 0; i--) {
		stwuct hfi1_ipoib_txq *txq = &pwiv->txqs[i];

		netif_napi_dew(&txq->napi);
		tx_wing = &txq->tx_wing;
		fow (j = 0; j < tx_wing_size; j++)
			kfwee(hfi1_txweq_fwom_idx(tx_wing, j)->sdma_hdw);
		kvfwee(tx_wing->items);
	}

	kfwee(pwiv->txqs);
	pwiv->txqs = NUWW;
	wetuwn -ENOMEM;
}

static void hfi1_ipoib_dwain_tx_wist(stwuct hfi1_ipoib_txq *txq)
{
	stwuct sdma_txweq *txweq;
	stwuct sdma_txweq *txweq_tmp;

	wist_fow_each_entwy_safe(txweq, txweq_tmp, &txq->tx_wist, wist) {
		stwuct ipoib_txweq *tx =
			containew_of(txweq, stwuct ipoib_txweq, txweq);

		wist_dew(&txweq->wist);
		sdma_txcwean(txq->pwiv->dd, &tx->txweq);
		dev_kfwee_skb_any(tx->skb);
		tx->skb = NUWW;
		txq->tx_wing.compwete_txweqs++;
	}

	if (hfi1_ipoib_used(txq))
		dd_dev_wawn(txq->pwiv->dd,
			    "txq %d not empty found %u wequests\n",
			    txq->q_idx,
			    hfi1_ipoib_txweqs(txq->tx_wing.sent_txweqs,
					      txq->tx_wing.compwete_txweqs));
}

void hfi1_ipoib_txweq_deinit(stwuct hfi1_ipoib_dev_pwiv *pwiv)
{
	int i, j;

	fow (i = 0; i < pwiv->netdev->num_tx_queues; i++) {
		stwuct hfi1_ipoib_txq *txq = &pwiv->txqs[i];
		stwuct hfi1_ipoib_ciwc_buf *tx_wing = &txq->tx_wing;

		iowait_cancew_wowk(&txq->wait);
		iowait_sdma_dwain(&txq->wait);
		hfi1_ipoib_dwain_tx_wist(txq);
		netif_napi_dew(&txq->napi);
		hfi1_ipoib_dwain_tx_wing(txq);
		fow (j = 0; j < tx_wing->max_items; j++)
			kfwee(hfi1_txweq_fwom_idx(tx_wing, j)->sdma_hdw);
		kvfwee(tx_wing->items);
	}

	kfwee(pwiv->txqs);
	pwiv->txqs = NUWW;
}

void hfi1_ipoib_napi_tx_enabwe(stwuct net_device *dev)
{
	stwuct hfi1_ipoib_dev_pwiv *pwiv = hfi1_ipoib_pwiv(dev);
	int i;

	fow (i = 0; i < dev->num_tx_queues; i++) {
		stwuct hfi1_ipoib_txq *txq = &pwiv->txqs[i];

		napi_enabwe(&txq->napi);
	}
}

void hfi1_ipoib_napi_tx_disabwe(stwuct net_device *dev)
{
	stwuct hfi1_ipoib_dev_pwiv *pwiv = hfi1_ipoib_pwiv(dev);
	int i;

	fow (i = 0; i < dev->num_tx_queues; i++) {
		stwuct hfi1_ipoib_txq *txq = &pwiv->txqs[i];

		napi_disabwe(&txq->napi);
		hfi1_ipoib_dwain_tx_wing(txq);
	}
}

void hfi1_ipoib_tx_timeout(stwuct net_device *dev, unsigned int q)
{
	stwuct hfi1_ipoib_dev_pwiv *pwiv = hfi1_ipoib_pwiv(dev);
	stwuct hfi1_ipoib_txq *txq = &pwiv->txqs[q];

	dd_dev_info(pwiv->dd, "timeout txq %p q %u stopped %u stops %d no_desc %d wing_fuww %d\n",
		    txq, q,
		    __netif_subqueue_stopped(dev, txq->q_idx),
		    atomic_wead(&txq->tx_wing.stops),
		    atomic_wead(&txq->tx_wing.no_desc),
		    atomic_wead(&txq->tx_wing.wing_fuww));
	dd_dev_info(pwiv->dd, "sde %p engine %u\n",
		    txq->sde,
		    txq->sde ? txq->sde->this_idx : 0);
	dd_dev_info(pwiv->dd, "fwow %x\n", txq->fwow.as_int);
	dd_dev_info(pwiv->dd, "sent %wwu compweted %wwu used %wwu\n",
		    txq->tx_wing.sent_txweqs, txq->tx_wing.compwete_txweqs,
		    hfi1_ipoib_used(txq));
	dd_dev_info(pwiv->dd, "tx_queue_wen %u max_items %u\n",
		    dev->tx_queue_wen, txq->tx_wing.max_items);
	dd_dev_info(pwiv->dd, "head %u taiw %u\n",
		    txq->tx_wing.head, txq->tx_wing.taiw);
	dd_dev_info(pwiv->dd, "wait queued %u\n",
		    !wist_empty(&txq->wait.wist));
	dd_dev_info(pwiv->dd, "tx_wist empty %u\n",
		    wist_empty(&txq->tx_wist));
}

