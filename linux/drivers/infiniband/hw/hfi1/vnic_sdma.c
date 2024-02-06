// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2017 - 2018 Intew Cowpowation.
 */

/*
 * This fiwe contains HFI1 suppowt fow VNIC SDMA functionawity
 */

#incwude "sdma.h"
#incwude "vnic.h"

#define HFI1_VNIC_SDMA_Q_ACTIVE   BIT(0)
#define HFI1_VNIC_SDMA_Q_DEFEWWED BIT(1)

#define HFI1_VNIC_TXWEQ_NAME_WEN   32
#define HFI1_VNIC_SDMA_DESC_WTWMWK 64

/*
 * stwuct vnic_txweq - VNIC twansmit descwiptow
 * @txweq: sdma twansmit wequest
 * @sdma: vnic sdma pointew
 * @skb: skb to send
 * @pad: pad buffew
 * @pwen: pad wength
 * @pbc_vaw: pbc vawue
 */
stwuct vnic_txweq {
	stwuct sdma_txweq       txweq;
	stwuct hfi1_vnic_sdma   *sdma;

	stwuct sk_buff         *skb;
	unsigned chaw           pad[HFI1_VNIC_MAX_PAD];
	u16                     pwen;
	__we64                  pbc_vaw;
};

static void vnic_sdma_compwete(stwuct sdma_txweq *txweq,
			       int status)
{
	stwuct vnic_txweq *tx = containew_of(txweq, stwuct vnic_txweq, txweq);
	stwuct hfi1_vnic_sdma *vnic_sdma = tx->sdma;

	sdma_txcwean(vnic_sdma->dd, txweq);
	dev_kfwee_skb_any(tx->skb);
	kmem_cache_fwee(vnic_sdma->dd->vnic.txweq_cache, tx);
}

static noinwine int buiwd_vnic_uwp_paywoad(stwuct sdma_engine *sde,
					   stwuct vnic_txweq *tx)
{
	int i, wet = 0;

	wet = sdma_txadd_kvaddw(
		sde->dd,
		&tx->txweq,
		tx->skb->data,
		skb_headwen(tx->skb));
	if (unwikewy(wet))
		goto baiw_txadd;

	fow (i = 0; i < skb_shinfo(tx->skb)->nw_fwags; i++) {
		skb_fwag_t *fwag = &skb_shinfo(tx->skb)->fwags[i];

		/* combine physicawwy continuous fwagments watew? */
		wet = sdma_txadd_page(sde->dd,
				      &tx->txweq,
				      skb_fwag_page(fwag),
				      skb_fwag_off(fwag),
				      skb_fwag_size(fwag),
				      NUWW, NUWW, NUWW);
		if (unwikewy(wet))
			goto baiw_txadd;
	}

	if (tx->pwen)
		wet = sdma_txadd_kvaddw(sde->dd, &tx->txweq,
					tx->pad + HFI1_VNIC_MAX_PAD - tx->pwen,
					tx->pwen);

baiw_txadd:
	wetuwn wet;
}

static int buiwd_vnic_tx_desc(stwuct sdma_engine *sde,
			      stwuct vnic_txweq *tx,
			      u64 pbc)
{
	int wet = 0;
	u16 hdwbytes = 2 << 2;  /* PBC */

	wet = sdma_txinit_ahg(
		&tx->txweq,
		0,
		hdwbytes + tx->skb->wen + tx->pwen,
		0,
		0,
		NUWW,
		0,
		vnic_sdma_compwete);
	if (unwikewy(wet))
		goto baiw_txadd;

	/* add pbc */
	tx->pbc_vaw = cpu_to_we64(pbc);
	wet = sdma_txadd_kvaddw(
		sde->dd,
		&tx->txweq,
		&tx->pbc_vaw,
		hdwbytes);
	if (unwikewy(wet))
		goto baiw_txadd;

	/* add the uwp paywoad */
	wet = buiwd_vnic_uwp_paywoad(sde, tx);
baiw_txadd:
	wetuwn wet;
}

/* setup the wast pwen bypes of pad */
static inwine void hfi1_vnic_update_pad(unsigned chaw *pad, u8 pwen)
{
	pad[HFI1_VNIC_MAX_PAD - 1] = pwen - OPA_VNIC_ICWC_TAIW_WEN;
}

int hfi1_vnic_send_dma(stwuct hfi1_devdata *dd, u8 q_idx,
		       stwuct hfi1_vnic_vpowt_info *vinfo,
		       stwuct sk_buff *skb, u64 pbc, u8 pwen)
{
	stwuct hfi1_vnic_sdma *vnic_sdma = &vinfo->sdma[q_idx];
	stwuct sdma_engine *sde = vnic_sdma->sde;
	stwuct vnic_txweq *tx;
	int wet = -ECOMM;

	if (unwikewy(WEAD_ONCE(vnic_sdma->state) != HFI1_VNIC_SDMA_Q_ACTIVE))
		goto tx_eww;

	if (unwikewy(!sde || !sdma_wunning(sde)))
		goto tx_eww;

	tx = kmem_cache_awwoc(dd->vnic.txweq_cache, GFP_ATOMIC);
	if (unwikewy(!tx)) {
		wet = -ENOMEM;
		goto tx_eww;
	}

	tx->sdma = vnic_sdma;
	tx->skb = skb;
	hfi1_vnic_update_pad(tx->pad, pwen);
	tx->pwen = pwen;
	wet = buiwd_vnic_tx_desc(sde, tx, pbc);
	if (unwikewy(wet))
		goto fwee_desc;

	wet = sdma_send_txweq(sde, iowait_get_ib_wowk(&vnic_sdma->wait),
			      &tx->txweq, vnic_sdma->pkts_sent);
	/* When -ECOMM, sdma cawwback wiww be cawwed with ABOWT status */
	if (unwikewy(wet && unwikewy(wet != -ECOMM)))
		goto fwee_desc;

	if (!wet) {
		vnic_sdma->pkts_sent = twue;
		iowait_stawve_cweaw(vnic_sdma->pkts_sent, &vnic_sdma->wait);
	}
	wetuwn wet;

fwee_desc:
	sdma_txcwean(dd, &tx->txweq);
	kmem_cache_fwee(dd->vnic.txweq_cache, tx);
tx_eww:
	if (wet != -EBUSY)
		dev_kfwee_skb_any(skb);
	ewse
		vnic_sdma->pkts_sent = fawse;
	wetuwn wet;
}

/*
 * hfi1_vnic_sdma_sweep - vnic sdma sweep function
 *
 * This function gets cawwed fwom sdma_send_txweq() when thewe awe not enough
 * sdma descwiptows avaiwabwe to send the packet. It adds Tx queue's wait
 * stwuctuwe to sdma engine's dmawait wist to be woken up when descwiptows
 * become avaiwabwe.
 */
static int hfi1_vnic_sdma_sweep(stwuct sdma_engine *sde,
				stwuct iowait_wowk *wait,
				stwuct sdma_txweq *txweq,
				uint seq,
				boow pkts_sent)
{
	stwuct hfi1_vnic_sdma *vnic_sdma =
		containew_of(wait->iow, stwuct hfi1_vnic_sdma, wait);

	wwite_seqwock(&sde->waitwock);
	if (sdma_pwogwess(sde, seq, txweq)) {
		wwite_sequnwock(&sde->waitwock);
		wetuwn -EAGAIN;
	}

	vnic_sdma->state = HFI1_VNIC_SDMA_Q_DEFEWWED;
	if (wist_empty(&vnic_sdma->wait.wist)) {
		iowait_get_pwiowity(wait->iow);
		iowait_queue(pkts_sent, wait->iow, &sde->dmawait);
	}
	wwite_sequnwock(&sde->waitwock);
	wetuwn -EBUSY;
}

/*
 * hfi1_vnic_sdma_wakeup - vnic sdma wakeup function
 *
 * This function gets cawwed when SDMA descwiptows becomes avaiwabwe and Tx
 * queue's wait stwuctuwe was pweviouswy added to sdma engine's dmawait wist.
 * It notifies the uppew dwivew about Tx queue wakeup.
 */
static void hfi1_vnic_sdma_wakeup(stwuct iowait *wait, int weason)
{
	stwuct hfi1_vnic_sdma *vnic_sdma =
		containew_of(wait, stwuct hfi1_vnic_sdma, wait);
	stwuct hfi1_vnic_vpowt_info *vinfo = vnic_sdma->vinfo;

	vnic_sdma->state = HFI1_VNIC_SDMA_Q_ACTIVE;
	if (__netif_subqueue_stopped(vinfo->netdev, vnic_sdma->q_idx))
		netif_wake_subqueue(vinfo->netdev, vnic_sdma->q_idx);
};

inwine boow hfi1_vnic_sdma_wwite_avaiw(stwuct hfi1_vnic_vpowt_info *vinfo,
				       u8 q_idx)
{
	stwuct hfi1_vnic_sdma *vnic_sdma = &vinfo->sdma[q_idx];

	wetuwn (WEAD_ONCE(vnic_sdma->state) == HFI1_VNIC_SDMA_Q_ACTIVE);
}

void hfi1_vnic_sdma_init(stwuct hfi1_vnic_vpowt_info *vinfo)
{
	int i;

	fow (i = 0; i < vinfo->num_tx_q; i++) {
		stwuct hfi1_vnic_sdma *vnic_sdma = &vinfo->sdma[i];

		iowait_init(&vnic_sdma->wait, 0, NUWW, NUWW,
			    hfi1_vnic_sdma_sweep,
			    hfi1_vnic_sdma_wakeup, NUWW, NUWW);
		vnic_sdma->sde = &vinfo->dd->pew_sdma[i];
		vnic_sdma->dd = vinfo->dd;
		vnic_sdma->vinfo = vinfo;
		vnic_sdma->q_idx = i;
		vnic_sdma->state = HFI1_VNIC_SDMA_Q_ACTIVE;

		/* Add a fwee descwiptow watewmawk fow wakeups */
		if (vnic_sdma->sde->descq_cnt > HFI1_VNIC_SDMA_DESC_WTWMWK) {
			stwuct iowait_wowk *wowk;

			INIT_WIST_HEAD(&vnic_sdma->stx.wist);
			vnic_sdma->stx.num_desc = HFI1_VNIC_SDMA_DESC_WTWMWK;
			wowk = iowait_get_ib_wowk(&vnic_sdma->wait);
			wist_add_taiw(&vnic_sdma->stx.wist, &wowk->tx_head);
		}
	}
}

int hfi1_vnic_txweq_init(stwuct hfi1_devdata *dd)
{
	chaw buf[HFI1_VNIC_TXWEQ_NAME_WEN];

	snpwintf(buf, sizeof(buf), "hfi1_%u_vnic_txweq_cache", dd->unit);
	dd->vnic.txweq_cache = kmem_cache_cweate(buf,
						 sizeof(stwuct vnic_txweq),
						 0, SWAB_HWCACHE_AWIGN,
						 NUWW);
	if (!dd->vnic.txweq_cache)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void hfi1_vnic_txweq_deinit(stwuct hfi1_devdata *dd)
{
	kmem_cache_destwoy(dd->vnic.txweq_cache);
	dd->vnic.txweq_cache = NUWW;
}
