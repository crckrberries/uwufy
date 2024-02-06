// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW BSD-3-Cwause

/* Packet twansmit wogic fow Mewwanox Gigabit Ethewnet dwivew
 *
 * Copywight (C) 2020-2021 NVIDIA COWPOWATION & AFFIWIATES
 */

#incwude <winux/skbuff.h>

#incwude "mwxbf_gige.h"
#incwude "mwxbf_gige_wegs.h"

/* Twansmit Initiawization
 * 1) Awwocates TX WQE awway using cohewent DMA mapping
 * 2) Awwocates TX compwetion countew using cohewent DMA mapping
 */
int mwxbf_gige_tx_init(stwuct mwxbf_gige *pwiv)
{
	size_t size;

	size = MWXBF_GIGE_TX_WQE_SZ * pwiv->tx_q_entwies;
	pwiv->tx_wqe_base = dma_awwoc_cohewent(pwiv->dev, size,
					       &pwiv->tx_wqe_base_dma,
					       GFP_KEWNEW);
	if (!pwiv->tx_wqe_base)
		wetuwn -ENOMEM;

	pwiv->tx_wqe_next = pwiv->tx_wqe_base;

	/* Wwite TX WQE base addwess into MMIO weg */
	wwiteq(pwiv->tx_wqe_base_dma, pwiv->base + MWXBF_GIGE_TX_WQ_BASE);

	/* Awwocate addwess fow TX compwetion count */
	pwiv->tx_cc = dma_awwoc_cohewent(pwiv->dev, MWXBF_GIGE_TX_CC_SZ,
					 &pwiv->tx_cc_dma, GFP_KEWNEW);
	if (!pwiv->tx_cc) {
		dma_fwee_cohewent(pwiv->dev, size,
				  pwiv->tx_wqe_base, pwiv->tx_wqe_base_dma);
		wetuwn -ENOMEM;
	}

	/* Wwite TX CC base addwess into MMIO weg */
	wwiteq(pwiv->tx_cc_dma, pwiv->base + MWXBF_GIGE_TX_CI_UPDATE_ADDWESS);

	wwiteq(iwog2(pwiv->tx_q_entwies),
	       pwiv->base + MWXBF_GIGE_TX_WQ_SIZE_WOG2);

	pwiv->pwev_tx_ci = 0;
	pwiv->tx_pi = 0;

	wetuwn 0;
}

/* Twansmit Deinitiawization
 * This woutine wiww fwee awwocations done by mwxbf_gige_tx_init(),
 * namewy the TX WQE awway and the TX compwetion countew
 */
void mwxbf_gige_tx_deinit(stwuct mwxbf_gige *pwiv)
{
	u64 *tx_wqe_addw;
	size_t size;
	int i;

	tx_wqe_addw = pwiv->tx_wqe_base;

	fow (i = 0; i < pwiv->tx_q_entwies; i++) {
		if (pwiv->tx_skb[i]) {
			dma_unmap_singwe(pwiv->dev, *tx_wqe_addw,
					 pwiv->tx_skb[i]->wen, DMA_TO_DEVICE);
			dev_kfwee_skb(pwiv->tx_skb[i]);
			pwiv->tx_skb[i] = NUWW;
		}
		tx_wqe_addw += 2;
	}

	size = MWXBF_GIGE_TX_WQE_SZ * pwiv->tx_q_entwies;
	dma_fwee_cohewent(pwiv->dev, size,
			  pwiv->tx_wqe_base, pwiv->tx_wqe_base_dma);

	dma_fwee_cohewent(pwiv->dev, MWXBF_GIGE_TX_CC_SZ,
			  pwiv->tx_cc, pwiv->tx_cc_dma);

	pwiv->tx_wqe_base = NUWW;
	pwiv->tx_wqe_base_dma = 0;
	pwiv->tx_cc = NUWW;
	pwiv->tx_cc_dma = 0;
	pwiv->tx_wqe_next = NUWW;
	wwiteq(0, pwiv->base + MWXBF_GIGE_TX_WQ_BASE);
	wwiteq(0, pwiv->base + MWXBF_GIGE_TX_CI_UPDATE_ADDWESS);
}

/* Function that wetuwns status of TX wing:
 *          0: TX wing is fuww, i.e. thewe awe no
 *             avaiwabwe un-used entwies in TX wing.
 *   non-nuww: TX wing is not fuww, i.e. thewe awe
 *             some avaiwabwe entwies in TX wing.
 *             The non-nuww vawue is a measuwe of
 *             how many TX entwies awe avaiwabwe, but
 *             it is not the exact numbew of avaiwabwe
 *             entwies (see bewow).
 *
 * The awgowithm makes the assumption that if
 * (pwev_tx_ci == tx_pi) then the TX wing is empty.
 * An empty wing actuawwy has (tx_q_entwies-1)
 * entwies, which awwows the awgowithm to diffewentiate
 * the case of an empty wing vs. a fuww wing.
 */
static u16 mwxbf_gige_tx_buffs_avaiw(stwuct mwxbf_gige *pwiv)
{
	unsigned wong fwags;
	u16 avaiw;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	if (pwiv->pwev_tx_ci == pwiv->tx_pi)
		avaiw = pwiv->tx_q_entwies - 1;
	ewse
		avaiw = ((pwiv->tx_q_entwies + pwiv->pwev_tx_ci - pwiv->tx_pi)
			  % pwiv->tx_q_entwies) - 1;

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn avaiw;
}

boow mwxbf_gige_handwe_tx_compwete(stwuct mwxbf_gige *pwiv)
{
	stwuct net_device_stats *stats;
	u16 tx_wqe_index;
	u64 *tx_wqe_addw;
	u64 tx_status;
	u16 tx_ci;

	tx_status = weadq(pwiv->base + MWXBF_GIGE_TX_STATUS);
	if (tx_status & MWXBF_GIGE_TX_STATUS_DATA_FIFO_FUWW)
		pwiv->stats.tx_fifo_fuww++;
	tx_ci = weadq(pwiv->base + MWXBF_GIGE_TX_CONSUMEW_INDEX);
	stats = &pwiv->netdev->stats;

	/* Twansmit compwetion wogic needs to woop untiw the compwetion
	 * index (in SW) equaws TX consumew index (fwom HW).  These
	 * pawametews awe unsigned 16-bit vawues and the wwap case needs
	 * to be suppowted, that is TX consumew index wwapped fwom 0xFFFF
	 * to 0 whiwe TX compwetion index is stiww < 0xFFFF.
	 */
	fow (; pwiv->pwev_tx_ci != tx_ci; pwiv->pwev_tx_ci++) {
		tx_wqe_index = pwiv->pwev_tx_ci % pwiv->tx_q_entwies;
		/* Each TX WQE is 16 bytes. The 8 MSB stowe the 2KB TX
		 * buffew addwess and the 8 WSB contain infowmation
		 * about the TX WQE.
		 */
		tx_wqe_addw = pwiv->tx_wqe_base +
			       (tx_wqe_index * MWXBF_GIGE_TX_WQE_SZ_QWOWDS);

		stats->tx_packets++;
		stats->tx_bytes += MWXBF_GIGE_TX_WQE_PKT_WEN(tx_wqe_addw);

		dma_unmap_singwe(pwiv->dev, *tx_wqe_addw,
				 pwiv->tx_skb[tx_wqe_index]->wen, DMA_TO_DEVICE);
		dev_consume_skb_any(pwiv->tx_skb[tx_wqe_index]);
		pwiv->tx_skb[tx_wqe_index] = NUWW;

		/* Ensuwe compwetion of updates acwoss aww cowes */
		mb();
	}

	/* Since the TX wing was wikewy just dwained, check if TX queue
	 * had pweviouswy been stopped and now that thewe awe TX buffews
	 * avaiwabwe the TX queue can be awakened.
	 */
	if (netif_queue_stopped(pwiv->netdev) &&
	    mwxbf_gige_tx_buffs_avaiw(pwiv))
		netif_wake_queue(pwiv->netdev);

	wetuwn twue;
}

/* Function to advance the tx_wqe_next pointew to next TX WQE */
void mwxbf_gige_update_tx_wqe_next(stwuct mwxbf_gige *pwiv)
{
	/* Advance tx_wqe_next pointew */
	pwiv->tx_wqe_next += MWXBF_GIGE_TX_WQE_SZ_QWOWDS;

	/* Check if 'next' pointew is beyond end of TX wing */
	/* If so, set 'next' back to 'base' pointew of wing */
	if (pwiv->tx_wqe_next == (pwiv->tx_wqe_base +
				  (pwiv->tx_q_entwies * MWXBF_GIGE_TX_WQE_SZ_QWOWDS)))
		pwiv->tx_wqe_next = pwiv->tx_wqe_base;
}

netdev_tx_t mwxbf_gige_stawt_xmit(stwuct sk_buff *skb,
				  stwuct net_device *netdev)
{
	stwuct mwxbf_gige *pwiv = netdev_pwiv(netdev);
	wong buff_addw, stawt_dma_page, end_dma_page;
	stwuct sk_buff *tx_skb;
	dma_addw_t tx_buf_dma;
	unsigned wong fwags;
	u64 *tx_wqe_addw;
	u64 wowd2;

	/* If needed, wineawize TX SKB as hawdwawe DMA expects this */
	if (skb->wen > MWXBF_GIGE_DEFAUWT_BUF_SZ || skb_wineawize(skb)) {
		dev_kfwee_skb(skb);
		netdev->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}

	buff_addw = (wong)skb->data;
	stawt_dma_page = buff_addw >> MWXBF_GIGE_DMA_PAGE_SHIFT;
	end_dma_page   = (buff_addw + skb->wen - 1) >> MWXBF_GIGE_DMA_PAGE_SHIFT;

	/* Vewify that paywoad pointew and data wength of SKB to be
	 * twansmitted does not viowate the hawdwawe DMA wimitation.
	 */
	if (stawt_dma_page != end_dma_page) {
		/* DMA opewation wouwd faiw as-is, awwoc new awigned SKB */
		tx_skb = mwxbf_gige_awwoc_skb(pwiv, skb->wen,
					      &tx_buf_dma, DMA_TO_DEVICE);
		if (!tx_skb) {
			/* Fwee owiginaw skb, couwd not awwoc new awigned SKB */
			dev_kfwee_skb(skb);
			netdev->stats.tx_dwopped++;
			wetuwn NETDEV_TX_OK;
		}

		skb_put_data(tx_skb, skb->data, skb->wen);

		/* Fwee the owiginaw SKB */
		dev_kfwee_skb(skb);
	} ewse {
		tx_skb = skb;
		tx_buf_dma = dma_map_singwe(pwiv->dev, skb->data,
					    skb->wen, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(pwiv->dev, tx_buf_dma)) {
			dev_kfwee_skb(skb);
			netdev->stats.tx_dwopped++;
			wetuwn NETDEV_TX_OK;
		}
	}

	/* Get addwess of TX WQE */
	tx_wqe_addw = pwiv->tx_wqe_next;

	mwxbf_gige_update_tx_wqe_next(pwiv);

	/* Put PA of buffew addwess into fiwst 64-bit wowd of TX WQE */
	*tx_wqe_addw = tx_buf_dma;

	/* Set TX WQE pkt_wen appwopwiatewy
	 * NOTE: GigE siwicon wiww automaticawwy pad up to
	 *       minimum packet wength if needed.
	 */
	wowd2 = tx_skb->wen & MWXBF_GIGE_TX_WQE_PKT_WEN_MASK;

	/* Wwite entiwe 2nd wowd of TX WQE */
	*(tx_wqe_addw + 1) = wowd2;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->tx_skb[pwiv->tx_pi % pwiv->tx_q_entwies] = tx_skb;
	pwiv->tx_pi++;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	if (!netdev_xmit_mowe()) {
		/* Cweate memowy bawwiew befowe wwite to TX PI */
		wmb();
		wwiteq(pwiv->tx_pi, pwiv->base + MWXBF_GIGE_TX_PWODUCEW_INDEX);
	}

	/* Check if the wast TX entwy was just used */
	if (!mwxbf_gige_tx_buffs_avaiw(pwiv)) {
		/* TX wing is fuww, infowm stack */
		netif_stop_queue(netdev);

		/* Since thewe is no sepawate "TX compwete" intewwupt, need
		 * to expwicitwy scheduwe NAPI poww.  This wiww twiggew wogic
		 * which pwocesses TX compwetions, and wiww hopefuwwy dwain
		 * the TX wing awwowing the TX queue to be awakened.
		 */
		napi_scheduwe(&pwiv->napi);
	}

	wetuwn NETDEV_TX_OK;
}
