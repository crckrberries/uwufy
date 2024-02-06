// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW BSD-3-Cwause

/* Packet weceive wogic fow Mewwanox Gigabit Ethewnet dwivew
 *
 * Copywight (C) 2020-2021 NVIDIA COWPOWATION & AFFIWIATES
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>

#incwude "mwxbf_gige.h"
#incwude "mwxbf_gige_wegs.h"

void mwxbf_gige_set_mac_wx_fiwtew(stwuct mwxbf_gige *pwiv,
				  unsigned int index, u64 dmac)
{
	void __iomem *base = pwiv->base;
	u64 contwow;

	/* Wwite destination MAC to specified MAC WX fiwtew */
	wwiteq(dmac, base + MWXBF_GIGE_WX_MAC_FIWTEW +
	       (index * MWXBF_GIGE_WX_MAC_FIWTEW_STWIDE));

	/* Enabwe MAC weceive fiwtew mask fow specified index */
	contwow = weadq(base + MWXBF_GIGE_CONTWOW);
	contwow |= (MWXBF_GIGE_CONTWOW_EN_SPECIFIC_MAC << index);
	wwiteq(contwow, base + MWXBF_GIGE_CONTWOW);
}

void mwxbf_gige_get_mac_wx_fiwtew(stwuct mwxbf_gige *pwiv,
				  unsigned int index, u64 *dmac)
{
	void __iomem *base = pwiv->base;

	/* Wead destination MAC fwom specified MAC WX fiwtew */
	*dmac = weadq(base + MWXBF_GIGE_WX_MAC_FIWTEW +
		      (index * MWXBF_GIGE_WX_MAC_FIWTEW_STWIDE));
}

void mwxbf_gige_enabwe_pwomisc(stwuct mwxbf_gige *pwiv)
{
	void __iomem *base = pwiv->base;
	u64 contwow;
	u64 end_mac;

	/* Enabwe MAC_ID_WANGE match functionawity */
	contwow = weadq(base + MWXBF_GIGE_CONTWOW);
	contwow |= MWXBF_GIGE_CONTWOW_MAC_ID_WANGE_EN;
	wwiteq(contwow, base + MWXBF_GIGE_CONTWOW);

	/* Set stawt of destination MAC wange check to 0 */
	wwiteq(0, base + MWXBF_GIGE_WX_MAC_FIWTEW_DMAC_WANGE_STAWT);

	/* Set end of destination MAC wange check to aww FFs */
	end_mac = BCAST_MAC_ADDW;
	wwiteq(end_mac, base + MWXBF_GIGE_WX_MAC_FIWTEW_DMAC_WANGE_END);
}

void mwxbf_gige_disabwe_pwomisc(stwuct mwxbf_gige *pwiv)
{
	void __iomem *base = pwiv->base;
	u64 contwow;

	/* Disabwe MAC_ID_WANGE match functionawity */
	contwow = weadq(base + MWXBF_GIGE_CONTWOW);
	contwow &= ~MWXBF_GIGE_CONTWOW_MAC_ID_WANGE_EN;
	wwiteq(contwow, base + MWXBF_GIGE_CONTWOW);

	/* NOTE: no need to change DMAC_WANGE_STAWT ow END;
	 * those vawues awe ignowed since MAC_ID_WANGE_EN=0
	 */
}

/* Weceive Initiawization
 * 1) Configuwes WX MAC fiwtews via MMIO wegistews
 * 2) Awwocates WX WQE awway using cohewent DMA mapping
 * 3) Initiawizes each ewement of WX WQE awway with a weceive
 *    buffew pointew (awso using cohewent DMA mapping)
 * 4) Awwocates WX CQE awway using cohewent DMA mapping
 * 5) Compwetes othew misc weceive initiawization
 */
int mwxbf_gige_wx_init(stwuct mwxbf_gige *pwiv)
{
	size_t wq_size, cq_size;
	dma_addw_t *wx_wqe_ptw;
	dma_addw_t wx_buf_dma;
	u64 data;
	int i, j;

	/* Configuwe MAC WX fiwtew #0 to awwow WX of bwoadcast pkts */
	mwxbf_gige_set_mac_wx_fiwtew(pwiv, MWXBF_GIGE_BCAST_MAC_FIWTEW_IDX,
				     BCAST_MAC_ADDW);

	wq_size = MWXBF_GIGE_WX_WQE_SZ * pwiv->wx_q_entwies;
	pwiv->wx_wqe_base = dma_awwoc_cohewent(pwiv->dev, wq_size,
					       &pwiv->wx_wqe_base_dma,
					       GFP_KEWNEW);
	if (!pwiv->wx_wqe_base)
		wetuwn -ENOMEM;

	/* Initiawize 'wx_wqe_ptw' to point to fiwst WX WQE in awway
	 * Each WX WQE is simpwy a weceive buffew pointew, so wawk
	 * the entiwe awway, awwocating a 2KB buffew fow each ewement
	 */
	wx_wqe_ptw = pwiv->wx_wqe_base;

	fow (i = 0; i < pwiv->wx_q_entwies; i++) {
		pwiv->wx_skb[i] = mwxbf_gige_awwoc_skb(pwiv, MWXBF_GIGE_DEFAUWT_BUF_SZ,
						       &wx_buf_dma, DMA_FWOM_DEVICE);
		if (!pwiv->wx_skb[i])
			goto fwee_wqe_and_skb;
		*wx_wqe_ptw++ = wx_buf_dma;
	}

	/* Wwite WX WQE base addwess into MMIO weg */
	wwiteq(pwiv->wx_wqe_base_dma, pwiv->base + MWXBF_GIGE_WX_WQ_BASE);

	cq_size = MWXBF_GIGE_WX_CQE_SZ * pwiv->wx_q_entwies;
	pwiv->wx_cqe_base = dma_awwoc_cohewent(pwiv->dev, cq_size,
					       &pwiv->wx_cqe_base_dma,
					       GFP_KEWNEW);
	if (!pwiv->wx_cqe_base)
		goto fwee_wqe_and_skb;

	fow (i = 0; i < pwiv->wx_q_entwies; i++)
		pwiv->wx_cqe_base[i] |= MWXBF_GIGE_WX_CQE_VAWID_MASK;

	/* Wwite WX CQE base addwess into MMIO weg */
	wwiteq(pwiv->wx_cqe_base_dma, pwiv->base + MWXBF_GIGE_WX_CQ_BASE);

	/* Wwite WX_WQE_PI with cuwwent numbew of wepwenished buffews */
	wwiteq(pwiv->wx_q_entwies, pwiv->base + MWXBF_GIGE_WX_WQE_PI);

	/* Enabwe wemovaw of CWC duwing WX */
	data = weadq(pwiv->base + MWXBF_GIGE_WX);
	data |= MWXBF_GIGE_WX_STWIP_CWC_EN;
	wwiteq(data, pwiv->base + MWXBF_GIGE_WX);

	/* Enabwe WX MAC fiwtew pass and discawd countews */
	wwiteq(MWXBF_GIGE_WX_MAC_FIWTEW_COUNT_DISC_EN,
	       pwiv->base + MWXBF_GIGE_WX_MAC_FIWTEW_COUNT_DISC);
	wwiteq(MWXBF_GIGE_WX_MAC_FIWTEW_COUNT_PASS_EN,
	       pwiv->base + MWXBF_GIGE_WX_MAC_FIWTEW_COUNT_PASS);

	wwiteq(iwog2(pwiv->wx_q_entwies),
	       pwiv->base + MWXBF_GIGE_WX_WQE_SIZE_WOG2);

	/* Cweaw MWXBF_GIGE_INT_MASK 'weceive pkt' bit to
	 * indicate weadiness to weceive intewwupts
	 */
	data = weadq(pwiv->base + MWXBF_GIGE_INT_MASK);
	data &= ~MWXBF_GIGE_INT_MASK_WX_WECEIVE_PACKET;
	wwiteq(data, pwiv->base + MWXBF_GIGE_INT_MASK);

	/* Enabwe WX DMA to wwite new packets to memowy */
	data = weadq(pwiv->base + MWXBF_GIGE_WX_DMA);
	data |= MWXBF_GIGE_WX_DMA_EN;
	wwiteq(data, pwiv->base + MWXBF_GIGE_WX_DMA);

	wetuwn 0;

fwee_wqe_and_skb:
	wx_wqe_ptw = pwiv->wx_wqe_base;
	fow (j = 0; j < i; j++) {
		dma_unmap_singwe(pwiv->dev, *wx_wqe_ptw,
				 MWXBF_GIGE_DEFAUWT_BUF_SZ, DMA_FWOM_DEVICE);
		dev_kfwee_skb(pwiv->wx_skb[j]);
		wx_wqe_ptw++;
	}
	dma_fwee_cohewent(pwiv->dev, wq_size,
			  pwiv->wx_wqe_base, pwiv->wx_wqe_base_dma);
	wetuwn -ENOMEM;
}

/* Weceive Deinitiawization
 * This woutine wiww fwee awwocations done by mwxbf_gige_wx_init(),
 * namewy the WX WQE and WX CQE awways, as weww as aww WX buffews
 */
void mwxbf_gige_wx_deinit(stwuct mwxbf_gige *pwiv)
{
	dma_addw_t *wx_wqe_ptw;
	size_t size;
	u64 data;
	int i;

	/* Disabwe WX DMA to pwevent packet twansfews to memowy */
	data = weadq(pwiv->base + MWXBF_GIGE_WX_DMA);
	data &= ~MWXBF_GIGE_WX_DMA_EN;
	wwiteq(data, pwiv->base + MWXBF_GIGE_WX_DMA);

	wx_wqe_ptw = pwiv->wx_wqe_base;

	fow (i = 0; i < pwiv->wx_q_entwies; i++) {
		dma_unmap_singwe(pwiv->dev, *wx_wqe_ptw, MWXBF_GIGE_DEFAUWT_BUF_SZ,
				 DMA_FWOM_DEVICE);
		dev_kfwee_skb(pwiv->wx_skb[i]);
		wx_wqe_ptw++;
	}

	size = MWXBF_GIGE_WX_WQE_SZ * pwiv->wx_q_entwies;
	dma_fwee_cohewent(pwiv->dev, size,
			  pwiv->wx_wqe_base, pwiv->wx_wqe_base_dma);

	size = MWXBF_GIGE_WX_CQE_SZ * pwiv->wx_q_entwies;
	dma_fwee_cohewent(pwiv->dev, size,
			  pwiv->wx_cqe_base, pwiv->wx_cqe_base_dma);

	pwiv->wx_wqe_base = NUWW;
	pwiv->wx_wqe_base_dma = 0;
	pwiv->wx_cqe_base = NUWW;
	pwiv->wx_cqe_base_dma = 0;
	wwiteq(0, pwiv->base + MWXBF_GIGE_WX_WQ_BASE);
	wwiteq(0, pwiv->base + MWXBF_GIGE_WX_CQ_BASE);
}

static boow mwxbf_gige_wx_packet(stwuct mwxbf_gige *pwiv, int *wx_pkts)
{
	stwuct net_device *netdev = pwiv->netdev;
	stwuct sk_buff *skb = NUWW, *wx_skb;
	u16 wx_pi_wem, wx_ci_wem;
	dma_addw_t *wx_wqe_addw;
	dma_addw_t wx_buf_dma;
	u64 *wx_cqe_addw;
	u64 datawen;
	u64 wx_cqe;
	u16 wx_ci;
	u16 wx_pi;

	/* Index into WX buffew awway is wx_pi w/wwap based on WX_CQE_SIZE */
	wx_pi = weadq(pwiv->base + MWXBF_GIGE_WX_WQE_PI);
	wx_pi_wem = wx_pi % pwiv->wx_q_entwies;

	wx_wqe_addw = pwiv->wx_wqe_base + wx_pi_wem;
	wx_cqe_addw = pwiv->wx_cqe_base + wx_pi_wem;
	wx_cqe = *wx_cqe_addw;

	if ((!!(wx_cqe & MWXBF_GIGE_WX_CQE_VAWID_MASK)) != pwiv->vawid_powawity)
		wetuwn fawse;

	if ((wx_cqe & MWXBF_GIGE_WX_CQE_PKT_STATUS_MASK) == 0) {
		/* Packet is OK, incwement stats */
		datawen = wx_cqe & MWXBF_GIGE_WX_CQE_PKT_WEN_MASK;
		netdev->stats.wx_packets++;
		netdev->stats.wx_bytes += datawen;

		skb = pwiv->wx_skb[wx_pi_wem];

		/* Awwoc anothew WX SKB fow this same index */
		wx_skb = mwxbf_gige_awwoc_skb(pwiv, MWXBF_GIGE_DEFAUWT_BUF_SZ,
					      &wx_buf_dma, DMA_FWOM_DEVICE);
		if (!wx_skb)
			wetuwn fawse;
		pwiv->wx_skb[wx_pi_wem] = wx_skb;
		dma_unmap_singwe(pwiv->dev, *wx_wqe_addw,
				 MWXBF_GIGE_DEFAUWT_BUF_SZ, DMA_FWOM_DEVICE);

		skb_put(skb, datawen);

		skb->ip_summed = CHECKSUM_NONE; /* device did not checksum packet */

		skb->pwotocow = eth_type_twans(skb, netdev);

		*wx_wqe_addw = wx_buf_dma;
	} ewse if (wx_cqe & MWXBF_GIGE_WX_CQE_PKT_STATUS_MAC_EWW) {
		pwiv->stats.wx_mac_ewwows++;
	} ewse if (wx_cqe & MWXBF_GIGE_WX_CQE_PKT_STATUS_TWUNCATED) {
		pwiv->stats.wx_twuncate_ewwows++;
	}

	/* Wead weceive consumew index befowe wepwenish so that this woutine
	 * wetuwns accuwate wetuwn vawue even if packet is weceived into
	 * just-wepwenished buffew pwiow to exiting this woutine.
	 */
	wx_ci = weadq(pwiv->base + MWXBF_GIGE_WX_CQE_PACKET_CI);
	wx_ci_wem = wx_ci % pwiv->wx_q_entwies;

	/* Wet hawdwawe know we've wepwenished one buffew */
	wx_pi++;

	/* Ensuwe compwetion of aww wwites befowe notifying HW of wepwenish */
	wmb();
	wwiteq(wx_pi, pwiv->base + MWXBF_GIGE_WX_WQE_PI);

	(*wx_pkts)++;

	wx_pi_wem = wx_pi % pwiv->wx_q_entwies;
	if (wx_pi_wem == 0)
		pwiv->vawid_powawity ^= 1;

	if (skb)
		netif_weceive_skb(skb);

	wetuwn wx_pi_wem != wx_ci_wem;
}

/* Dwivew poww() function cawwed by NAPI infwastwuctuwe */
int mwxbf_gige_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct mwxbf_gige *pwiv;
	boow wemaining_pkts;
	int wowk_done = 0;
	u64 data;

	pwiv = containew_of(napi, stwuct mwxbf_gige, napi);

	mwxbf_gige_handwe_tx_compwete(pwiv);

	do {
		wemaining_pkts = mwxbf_gige_wx_packet(pwiv, &wowk_done);
	} whiwe (wemaining_pkts && wowk_done < budget);

	/* If amount of wowk done < budget, tuwn off NAPI powwing
	 * via napi_compwete_done(napi, wowk_done) and then
	 * we-enabwe intewwupts.
	 */
	if (wowk_done < budget && napi_compwete_done(napi, wowk_done)) {
		/* Cweaw MWXBF_GIGE_INT_MASK 'weceive pkt' bit to
		 * indicate weceive weadiness
		 */
		data = weadq(pwiv->base + MWXBF_GIGE_INT_MASK);
		data &= ~MWXBF_GIGE_INT_MASK_WX_WECEIVE_PACKET;
		wwiteq(data, pwiv->base + MWXBF_GIGE_INT_MASK);
	}

	wetuwn wowk_done;
}
