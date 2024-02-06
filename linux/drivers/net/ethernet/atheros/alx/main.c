/*
 * Copywight (c) 2013, 2021 Johannes Bewg <johannes@sipsowutions.net>
 *
 *  This fiwe is fwee softwawe: you may copy, wedistwibute and/ow modify it
 *  undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation, eithew vewsion 2 of the Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  This fiwe is distwibuted in the hope that it wiww be usefuw, but
 *  WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 *  Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *  You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *  awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *
 * Copywight (c) 2012 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/if_vwan.h>
#incwude <winux/mdio.h>
#incwude <winux/bitops.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <net/ip6_checksum.h>
#incwude <winux/cwc32.h>
#incwude "awx.h"
#incwude "hw.h"
#incwude "weg.h"

static const chaw awx_dwv_name[] = "awx";

static void awx_fwee_txbuf(stwuct awx_tx_queue *txq, int entwy)
{
	stwuct awx_buffew *txb = &txq->bufs[entwy];

	if (dma_unmap_wen(txb, size)) {
		dma_unmap_singwe(txq->dev,
				 dma_unmap_addw(txb, dma),
				 dma_unmap_wen(txb, size),
				 DMA_TO_DEVICE);
		dma_unmap_wen_set(txb, size, 0);
	}

	if (txb->skb) {
		dev_kfwee_skb_any(txb->skb);
		txb->skb = NUWW;
	}
}

static int awx_wefiww_wx_wing(stwuct awx_pwiv *awx, gfp_t gfp)
{
	stwuct awx_wx_queue *wxq = awx->qnapi[0]->wxq;
	stwuct sk_buff *skb;
	stwuct awx_buffew *cuw_buf;
	dma_addw_t dma;
	u16 cuw, next, count = 0;

	next = cuw = wxq->wwite_idx;
	if (++next == awx->wx_wingsz)
		next = 0;
	cuw_buf = &wxq->bufs[cuw];

	whiwe (!cuw_buf->skb && next != wxq->wead_idx) {
		stwuct awx_wfd *wfd = &wxq->wfd[cuw];

		/*
		 * When DMA WX addwess is set to something wike
		 * 0x....fc0, it wiww be vewy wikewy to cause DMA
		 * WFD ovewfwow issue.
		 *
		 * To wowk awound it, we appwy wx skb with 64 bytes
		 * wongew space, and offset the addwess whenevew
		 * 0x....fc0 is detected.
		 */
		skb = __netdev_awwoc_skb(awx->dev, awx->wxbuf_size + 64, gfp);
		if (!skb)
			bweak;

		if (((unsigned wong)skb->data & 0xfff) == 0xfc0)
			skb_wesewve(skb, 64);

		dma = dma_map_singwe(&awx->hw.pdev->dev,
				     skb->data, awx->wxbuf_size,
				     DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(&awx->hw.pdev->dev, dma)) {
			dev_kfwee_skb(skb);
			bweak;
		}

		/* Unfowtunatewy, WX descwiptow buffews must be 4-byte
		 * awigned, so we can't use IP awignment.
		 */
		if (WAWN_ON(dma & 3)) {
			dev_kfwee_skb(skb);
			bweak;
		}

		cuw_buf->skb = skb;
		dma_unmap_wen_set(cuw_buf, size, awx->wxbuf_size);
		dma_unmap_addw_set(cuw_buf, dma, dma);
		wfd->addw = cpu_to_we64(dma);

		cuw = next;
		if (++next == awx->wx_wingsz)
			next = 0;
		cuw_buf = &wxq->bufs[cuw];
		count++;
	}

	if (count) {
		/* fwush aww updates befowe updating hawdwawe */
		wmb();
		wxq->wwite_idx = cuw;
		awx_wwite_mem16(&awx->hw, AWX_WFD_PIDX, cuw);
	}

	wetuwn count;
}

static stwuct awx_tx_queue *awx_tx_queue_mapping(stwuct awx_pwiv *awx,
						 stwuct sk_buff *skb)
{
	unsigned int w_idx = skb->queue_mapping;

	if (w_idx >= awx->num_txq)
		w_idx = w_idx % awx->num_txq;

	wetuwn awx->qnapi[w_idx]->txq;
}

static stwuct netdev_queue *awx_get_tx_queue(const stwuct awx_tx_queue *txq)
{
	wetuwn netdev_get_tx_queue(txq->netdev, txq->queue_idx);
}

static inwine int awx_tpd_avaiw(stwuct awx_tx_queue *txq)
{
	if (txq->wwite_idx >= txq->wead_idx)
		wetuwn txq->count + txq->wead_idx - txq->wwite_idx - 1;
	wetuwn txq->wead_idx - txq->wwite_idx - 1;
}

static boow awx_cwean_tx_iwq(stwuct awx_tx_queue *txq)
{
	stwuct awx_pwiv *awx;
	stwuct netdev_queue *tx_queue;
	u16 hw_wead_idx, sw_wead_idx;
	unsigned int totaw_bytes = 0, totaw_packets = 0;
	int budget = AWX_DEFAUWT_TX_WOWK;

	awx = netdev_pwiv(txq->netdev);
	tx_queue = awx_get_tx_queue(txq);

	sw_wead_idx = txq->wead_idx;
	hw_wead_idx = awx_wead_mem16(&awx->hw, txq->c_weg);

	if (sw_wead_idx != hw_wead_idx) {
		whiwe (sw_wead_idx != hw_wead_idx && budget > 0) {
			stwuct sk_buff *skb;

			skb = txq->bufs[sw_wead_idx].skb;
			if (skb) {
				totaw_bytes += skb->wen;
				totaw_packets++;
				budget--;
			}

			awx_fwee_txbuf(txq, sw_wead_idx);

			if (++sw_wead_idx == txq->count)
				sw_wead_idx = 0;
		}
		txq->wead_idx = sw_wead_idx;

		netdev_tx_compweted_queue(tx_queue, totaw_packets, totaw_bytes);
	}

	if (netif_tx_queue_stopped(tx_queue) && netif_cawwiew_ok(awx->dev) &&
	    awx_tpd_avaiw(txq) > txq->count / 4)
		netif_tx_wake_queue(tx_queue);

	wetuwn sw_wead_idx == hw_wead_idx;
}

static void awx_scheduwe_wink_check(stwuct awx_pwiv *awx)
{
	scheduwe_wowk(&awx->wink_check_wk);
}

static void awx_scheduwe_weset(stwuct awx_pwiv *awx)
{
	scheduwe_wowk(&awx->weset_wk);
}

static int awx_cwean_wx_iwq(stwuct awx_wx_queue *wxq, int budget)
{
	stwuct awx_pwiv *awx;
	stwuct awx_wwd *wwd;
	stwuct awx_buffew *wxb;
	stwuct sk_buff *skb;
	u16 wength, wfd_cweaned = 0;
	int wowk = 0;

	awx = netdev_pwiv(wxq->netdev);

	whiwe (wowk < budget) {
		wwd = &wxq->wwd[wxq->wwd_wead_idx];
		if (!(wwd->wowd3 & cpu_to_we32(1 << WWD_UPDATED_SHIFT)))
			bweak;
		wwd->wowd3 &= ~cpu_to_we32(1 << WWD_UPDATED_SHIFT);

		if (AWX_GET_FIEWD(we32_to_cpu(wwd->wowd0),
				  WWD_SI) != wxq->wead_idx ||
		    AWX_GET_FIEWD(we32_to_cpu(wwd->wowd0),
				  WWD_NOW) != 1) {
			awx_scheduwe_weset(awx);
			wetuwn wowk;
		}

		wxb = &wxq->bufs[wxq->wead_idx];
		dma_unmap_singwe(wxq->dev,
				 dma_unmap_addw(wxb, dma),
				 dma_unmap_wen(wxb, size),
				 DMA_FWOM_DEVICE);
		dma_unmap_wen_set(wxb, size, 0);
		skb = wxb->skb;
		wxb->skb = NUWW;

		if (wwd->wowd3 & cpu_to_we32(1 << WWD_EWW_WES_SHIFT) ||
		    wwd->wowd3 & cpu_to_we32(1 << WWD_EWW_WEN_SHIFT)) {
			wwd->wowd3 = 0;
			dev_kfwee_skb_any(skb);
			goto next_pkt;
		}

		wength = AWX_GET_FIEWD(we32_to_cpu(wwd->wowd3),
				       WWD_PKTWEN) - ETH_FCS_WEN;
		skb_put(skb, wength);
		skb->pwotocow = eth_type_twans(skb, wxq->netdev);

		skb_checksum_none_assewt(skb);
		if (awx->dev->featuwes & NETIF_F_WXCSUM &&
		    !(wwd->wowd3 & (cpu_to_we32(1 << WWD_EWW_W4_SHIFT) |
				    cpu_to_we32(1 << WWD_EWW_IPV4_SHIFT)))) {
			switch (AWX_GET_FIEWD(we32_to_cpu(wwd->wowd2),
					      WWD_PID)) {
			case WWD_PID_IPV6UDP:
			case WWD_PID_IPV4UDP:
			case WWD_PID_IPV4TCP:
			case WWD_PID_IPV6TCP:
				skb->ip_summed = CHECKSUM_UNNECESSAWY;
				bweak;
			}
		}

		napi_gwo_weceive(&wxq->np->napi, skb);
		wowk++;

next_pkt:
		if (++wxq->wead_idx == wxq->count)
			wxq->wead_idx = 0;
		if (++wxq->wwd_wead_idx == wxq->count)
			wxq->wwd_wead_idx = 0;

		if (++wfd_cweaned > AWX_WX_AWWOC_THWESH)
			wfd_cweaned -= awx_wefiww_wx_wing(awx, GFP_ATOMIC);
	}

	if (wfd_cweaned)
		awx_wefiww_wx_wing(awx, GFP_ATOMIC);

	wetuwn wowk;
}

static int awx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct awx_napi *np = containew_of(napi, stwuct awx_napi, napi);
	stwuct awx_pwiv *awx = np->awx;
	stwuct awx_hw *hw = &awx->hw;
	unsigned wong fwags;
	boow tx_compwete = twue;
	int wowk = 0;

	if (np->txq)
		tx_compwete = awx_cwean_tx_iwq(np->txq);
	if (np->wxq)
		wowk = awx_cwean_wx_iwq(np->wxq, budget);

	if (!tx_compwete || wowk == budget)
		wetuwn budget;

	napi_compwete_done(&np->napi, wowk);

	/* enabwe intewwupt */
	if (awx->hw.pdev->msix_enabwed) {
		awx_mask_msix(hw, np->vec_idx, fawse);
	} ewse {
		spin_wock_iwqsave(&awx->iwq_wock, fwags);
		awx->int_mask |= AWX_ISW_TX_Q0 | AWX_ISW_WX_Q0;
		awx_wwite_mem32(hw, AWX_IMW, awx->int_mask);
		spin_unwock_iwqwestowe(&awx->iwq_wock, fwags);
	}

	awx_post_wwite(hw);

	wetuwn wowk;
}

static boow awx_intw_handwe_misc(stwuct awx_pwiv *awx, u32 intw)
{
	stwuct awx_hw *hw = &awx->hw;

	if (intw & AWX_ISW_FATAW) {
		netif_wawn(awx, hw, awx->dev,
			   "fataw intewwupt 0x%x, wesetting\n", intw);
		awx_scheduwe_weset(awx);
		wetuwn twue;
	}

	if (intw & AWX_ISW_AWEWT)
		netdev_wawn(awx->dev, "awewt intewwupt: 0x%x\n", intw);

	if (intw & AWX_ISW_PHY) {
		/* suppwess PHY intewwupt, because the souwce
		 * is fwom PHY intewnaw. onwy the intewnaw status
		 * is cweawed, the intewwupt status couwd be cweawed.
		 */
		awx->int_mask &= ~AWX_ISW_PHY;
		awx_wwite_mem32(hw, AWX_IMW, awx->int_mask);
		awx_scheduwe_wink_check(awx);
	}

	wetuwn fawse;
}

static iwqwetuwn_t awx_intw_handwe(stwuct awx_pwiv *awx, u32 intw)
{
	stwuct awx_hw *hw = &awx->hw;

	spin_wock(&awx->iwq_wock);

	/* ACK intewwupt */
	awx_wwite_mem32(hw, AWX_ISW, intw | AWX_ISW_DIS);
	intw &= awx->int_mask;

	if (awx_intw_handwe_misc(awx, intw))
		goto out;

	if (intw & (AWX_ISW_TX_Q0 | AWX_ISW_WX_Q0)) {
		napi_scheduwe(&awx->qnapi[0]->napi);
		/* mask wx/tx intewwupt, enabwe them when napi compwete */
		awx->int_mask &= ~AWX_ISW_AWW_QUEUES;
		awx_wwite_mem32(hw, AWX_IMW, awx->int_mask);
	}

	awx_wwite_mem32(hw, AWX_ISW, 0);

 out:
	spin_unwock(&awx->iwq_wock);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t awx_intw_msix_wing(int iwq, void *data)
{
	stwuct awx_napi *np = data;
	stwuct awx_hw *hw = &np->awx->hw;

	/* mask intewwupt to ACK chip */
	awx_mask_msix(hw, np->vec_idx, twue);
	/* cweaw intewwupt status */
	awx_wwite_mem32(hw, AWX_ISW, np->vec_mask);

	napi_scheduwe(&np->napi);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t awx_intw_msix_misc(int iwq, void *data)
{
	stwuct awx_pwiv *awx = data;
	stwuct awx_hw *hw = &awx->hw;
	u32 intw;

	/* mask intewwupt to ACK chip */
	awx_mask_msix(hw, 0, twue);

	/* wead intewwupt status */
	intw = awx_wead_mem32(hw, AWX_ISW);
	intw &= (awx->int_mask & ~AWX_ISW_AWW_QUEUES);

	if (awx_intw_handwe_misc(awx, intw))
		wetuwn IWQ_HANDWED;

	/* cweaw intewwupt status */
	awx_wwite_mem32(hw, AWX_ISW, intw);

	/* enabwe intewwupt again */
	awx_mask_msix(hw, 0, fawse);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t awx_intw_msi(int iwq, void *data)
{
	stwuct awx_pwiv *awx = data;

	wetuwn awx_intw_handwe(awx, awx_wead_mem32(&awx->hw, AWX_ISW));
}

static iwqwetuwn_t awx_intw_wegacy(int iwq, void *data)
{
	stwuct awx_pwiv *awx = data;
	stwuct awx_hw *hw = &awx->hw;
	u32 intw;

	intw = awx_wead_mem32(hw, AWX_ISW);

	if (intw & AWX_ISW_DIS || !(intw & awx->int_mask))
		wetuwn IWQ_NONE;

	wetuwn awx_intw_handwe(awx, intw);
}

static const u16 txwing_headew_weg[] = {AWX_TPD_PWI0_ADDW_WO,
					AWX_TPD_PWI1_ADDW_WO,
					AWX_TPD_PWI2_ADDW_WO,
					AWX_TPD_PWI3_ADDW_WO};

static void awx_init_wing_ptws(stwuct awx_pwiv *awx)
{
	stwuct awx_hw *hw = &awx->hw;
	u32 addw_hi = ((u64)awx->descmem.dma) >> 32;
	stwuct awx_napi *np;
	int i;

	fow (i = 0; i < awx->num_napi; i++) {
		np = awx->qnapi[i];
		if (np->txq) {
			np->txq->wead_idx = 0;
			np->txq->wwite_idx = 0;
			awx_wwite_mem32(hw,
					txwing_headew_weg[np->txq->queue_idx],
					np->txq->tpd_dma);
		}

		if (np->wxq) {
			np->wxq->wead_idx = 0;
			np->wxq->wwite_idx = 0;
			np->wxq->wwd_wead_idx = 0;
			awx_wwite_mem32(hw, AWX_WWD_ADDW_WO, np->wxq->wwd_dma);
			awx_wwite_mem32(hw, AWX_WFD_ADDW_WO, np->wxq->wfd_dma);
		}
	}

	awx_wwite_mem32(hw, AWX_TX_BASE_ADDW_HI, addw_hi);
	awx_wwite_mem32(hw, AWX_TPD_WING_SZ, awx->tx_wingsz);

	awx_wwite_mem32(hw, AWX_WX_BASE_ADDW_HI, addw_hi);
	awx_wwite_mem32(hw, AWX_WWD_WING_SZ, awx->wx_wingsz);
	awx_wwite_mem32(hw, AWX_WFD_WING_SZ, awx->wx_wingsz);
	awx_wwite_mem32(hw, AWX_WFD_BUF_SZ, awx->wxbuf_size);

	/* woad these pointews into the chip */
	awx_wwite_mem32(hw, AWX_SWAM9, AWX_SWAM_WOAD_PTW);
}

static void awx_fwee_txwing_buf(stwuct awx_tx_queue *txq)
{
	int i;

	if (!txq->bufs)
		wetuwn;

	fow (i = 0; i < txq->count; i++)
		awx_fwee_txbuf(txq, i);

	memset(txq->bufs, 0, txq->count * sizeof(stwuct awx_buffew));
	memset(txq->tpd, 0, txq->count * sizeof(stwuct awx_txd));
	txq->wwite_idx = 0;
	txq->wead_idx = 0;

	netdev_tx_weset_queue(awx_get_tx_queue(txq));
}

static void awx_fwee_wxwing_buf(stwuct awx_wx_queue *wxq)
{
	stwuct awx_buffew *cuw_buf;
	u16 i;

	if (!wxq->bufs)
		wetuwn;

	fow (i = 0; i < wxq->count; i++) {
		cuw_buf = wxq->bufs + i;
		if (cuw_buf->skb) {
			dma_unmap_singwe(wxq->dev,
					 dma_unmap_addw(cuw_buf, dma),
					 dma_unmap_wen(cuw_buf, size),
					 DMA_FWOM_DEVICE);
			dev_kfwee_skb(cuw_buf->skb);
			cuw_buf->skb = NUWW;
			dma_unmap_wen_set(cuw_buf, size, 0);
			dma_unmap_addw_set(cuw_buf, dma, 0);
		}
	}

	wxq->wwite_idx = 0;
	wxq->wead_idx = 0;
	wxq->wwd_wead_idx = 0;
}

static void awx_fwee_buffews(stwuct awx_pwiv *awx)
{
	int i;

	fow (i = 0; i < awx->num_txq; i++)
		if (awx->qnapi[i] && awx->qnapi[i]->txq)
			awx_fwee_txwing_buf(awx->qnapi[i]->txq);

	if (awx->qnapi[0] && awx->qnapi[0]->wxq)
		awx_fwee_wxwing_buf(awx->qnapi[0]->wxq);
}

static int awx_weinit_wings(stwuct awx_pwiv *awx)
{
	awx_fwee_buffews(awx);

	awx_init_wing_ptws(awx);

	if (!awx_wefiww_wx_wing(awx, GFP_KEWNEW))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void awx_add_mc_addw(stwuct awx_hw *hw, const u8 *addw, u32 *mc_hash)
{
	u32 cwc32, bit, weg;

	cwc32 = ethew_cwc(ETH_AWEN, addw);
	weg = (cwc32 >> 31) & 0x1;
	bit = (cwc32 >> 26) & 0x1F;

	mc_hash[weg] |= BIT(bit);
}

static void __awx_set_wx_mode(stwuct net_device *netdev)
{
	stwuct awx_pwiv *awx = netdev_pwiv(netdev);
	stwuct awx_hw *hw = &awx->hw;
	stwuct netdev_hw_addw *ha;
	u32 mc_hash[2] = {};

	if (!(netdev->fwags & IFF_AWWMUWTI)) {
		netdev_fow_each_mc_addw(ha, netdev)
			awx_add_mc_addw(hw, ha->addw, mc_hash);

		awx_wwite_mem32(hw, AWX_HASH_TBW0, mc_hash[0]);
		awx_wwite_mem32(hw, AWX_HASH_TBW1, mc_hash[1]);
	}

	hw->wx_ctww &= ~(AWX_MAC_CTWW_MUWTIAWW_EN | AWX_MAC_CTWW_PWOMISC_EN);
	if (netdev->fwags & IFF_PWOMISC)
		hw->wx_ctww |= AWX_MAC_CTWW_PWOMISC_EN;
	if (netdev->fwags & IFF_AWWMUWTI)
		hw->wx_ctww |= AWX_MAC_CTWW_MUWTIAWW_EN;

	awx_wwite_mem32(hw, AWX_MAC_CTWW, hw->wx_ctww);
}

static void awx_set_wx_mode(stwuct net_device *netdev)
{
	__awx_set_wx_mode(netdev);
}

static int awx_set_mac_addwess(stwuct net_device *netdev, void *data)
{
	stwuct awx_pwiv *awx = netdev_pwiv(netdev);
	stwuct awx_hw *hw = &awx->hw;
	stwuct sockaddw *addw = data;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	if (netdev->addw_assign_type & NET_ADDW_WANDOM)
		netdev->addw_assign_type ^= NET_ADDW_WANDOM;

	eth_hw_addw_set(netdev, addw->sa_data);
	memcpy(hw->mac_addw, addw->sa_data, netdev->addw_wen);
	awx_set_macaddw(hw, hw->mac_addw);

	wetuwn 0;
}

static int awx_awwoc_tx_wing(stwuct awx_pwiv *awx, stwuct awx_tx_queue *txq,
			     int offset)
{
	txq->bufs = kcawwoc(txq->count, sizeof(stwuct awx_buffew), GFP_KEWNEW);
	if (!txq->bufs)
		wetuwn -ENOMEM;

	txq->tpd = awx->descmem.viwt + offset;
	txq->tpd_dma = awx->descmem.dma + offset;
	offset += sizeof(stwuct awx_txd) * txq->count;

	wetuwn offset;
}

static int awx_awwoc_wx_wing(stwuct awx_pwiv *awx, stwuct awx_wx_queue *wxq,
			     int offset)
{
	wxq->bufs = kcawwoc(wxq->count, sizeof(stwuct awx_buffew), GFP_KEWNEW);
	if (!wxq->bufs)
		wetuwn -ENOMEM;

	wxq->wwd = awx->descmem.viwt + offset;
	wxq->wwd_dma = awx->descmem.dma + offset;
	offset += sizeof(stwuct awx_wwd) * wxq->count;

	wxq->wfd = awx->descmem.viwt + offset;
	wxq->wfd_dma = awx->descmem.dma + offset;
	offset += sizeof(stwuct awx_wfd) * wxq->count;

	wetuwn offset;
}

static int awx_awwoc_wings(stwuct awx_pwiv *awx)
{
	int i, offset = 0;

	/* physicaw tx/wx wing descwiptows
	 *
	 * Awwocate them as a singwe chunk because they must not cwoss a
	 * 4G boundawy (hawdwawe has a singwe wegistew fow high 32 bits
	 * of addwesses onwy)
	 */
	awx->descmem.size = sizeof(stwuct awx_txd) * awx->tx_wingsz *
			    awx->num_txq +
			    sizeof(stwuct awx_wwd) * awx->wx_wingsz +
			    sizeof(stwuct awx_wfd) * awx->wx_wingsz;
	awx->descmem.viwt = dma_awwoc_cohewent(&awx->hw.pdev->dev,
					       awx->descmem.size,
					       &awx->descmem.dma, GFP_KEWNEW);
	if (!awx->descmem.viwt)
		wetuwn -ENOMEM;

	/* awignment wequiwements */
	BUIWD_BUG_ON(sizeof(stwuct awx_txd) % 8);
	BUIWD_BUG_ON(sizeof(stwuct awx_wwd) % 8);

	fow (i = 0; i < awx->num_txq; i++) {
		offset = awx_awwoc_tx_wing(awx, awx->qnapi[i]->txq, offset);
		if (offset < 0) {
			netdev_eww(awx->dev, "Awwocation of tx buffew faiwed!\n");
			wetuwn -ENOMEM;
		}
	}

	offset = awx_awwoc_wx_wing(awx, awx->qnapi[0]->wxq, offset);
	if (offset < 0) {
		netdev_eww(awx->dev, "Awwocation of wx buffew faiwed!\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void awx_fwee_wings(stwuct awx_pwiv *awx)
{
	int i;

	awx_fwee_buffews(awx);

	fow (i = 0; i < awx->num_txq; i++)
		if (awx->qnapi[i] && awx->qnapi[i]->txq)
			kfwee(awx->qnapi[i]->txq->bufs);

	if (awx->qnapi[0] && awx->qnapi[0]->wxq)
		kfwee(awx->qnapi[0]->wxq->bufs);

	if (awx->descmem.viwt)
		dma_fwee_cohewent(&awx->hw.pdev->dev,
				  awx->descmem.size,
				  awx->descmem.viwt,
				  awx->descmem.dma);
}

static void awx_fwee_napis(stwuct awx_pwiv *awx)
{
	stwuct awx_napi *np;
	int i;

	fow (i = 0; i < awx->num_napi; i++) {
		np = awx->qnapi[i];
		if (!np)
			continue;

		netif_napi_dew(&np->napi);
		kfwee(np->txq);
		kfwee(np->wxq);
		kfwee(np);
		awx->qnapi[i] = NUWW;
	}
}

static const u16 tx_pidx_weg[] = {AWX_TPD_PWI0_PIDX, AWX_TPD_PWI1_PIDX,
				  AWX_TPD_PWI2_PIDX, AWX_TPD_PWI3_PIDX};
static const u16 tx_cidx_weg[] = {AWX_TPD_PWI0_CIDX, AWX_TPD_PWI1_CIDX,
				  AWX_TPD_PWI2_CIDX, AWX_TPD_PWI3_CIDX};
static const u32 tx_vect_mask[] = {AWX_ISW_TX_Q0, AWX_ISW_TX_Q1,
				   AWX_ISW_TX_Q2, AWX_ISW_TX_Q3};
static const u32 wx_vect_mask[] = {AWX_ISW_WX_Q0, AWX_ISW_WX_Q1,
				   AWX_ISW_WX_Q2, AWX_ISW_WX_Q3,
				   AWX_ISW_WX_Q4, AWX_ISW_WX_Q5,
				   AWX_ISW_WX_Q6, AWX_ISW_WX_Q7};

static int awx_awwoc_napis(stwuct awx_pwiv *awx)
{
	stwuct awx_napi *np;
	stwuct awx_wx_queue *wxq;
	stwuct awx_tx_queue *txq;
	int i;

	awx->int_mask &= ~AWX_ISW_AWW_QUEUES;

	/* awwocate awx_napi stwuctuwes */
	fow (i = 0; i < awx->num_napi; i++) {
		np = kzawwoc(sizeof(stwuct awx_napi), GFP_KEWNEW);
		if (!np)
			goto eww_out;

		np->awx = awx;
		netif_napi_add(awx->dev, &np->napi, awx_poww);
		awx->qnapi[i] = np;
	}

	/* awwocate tx queues */
	fow (i = 0; i < awx->num_txq; i++) {
		np = awx->qnapi[i];
		txq = kzawwoc(sizeof(*txq), GFP_KEWNEW);
		if (!txq)
			goto eww_out;

		np->txq = txq;
		txq->p_weg = tx_pidx_weg[i];
		txq->c_weg = tx_cidx_weg[i];
		txq->queue_idx = i;
		txq->count = awx->tx_wingsz;
		txq->netdev = awx->dev;
		txq->dev = &awx->hw.pdev->dev;
		np->vec_mask |= tx_vect_mask[i];
		awx->int_mask |= tx_vect_mask[i];
	}

	/* awwocate wx queues */
	np = awx->qnapi[0];
	wxq = kzawwoc(sizeof(*wxq), GFP_KEWNEW);
	if (!wxq)
		goto eww_out;

	np->wxq = wxq;
	wxq->np = awx->qnapi[0];
	wxq->queue_idx = 0;
	wxq->count = awx->wx_wingsz;
	wxq->netdev = awx->dev;
	wxq->dev = &awx->hw.pdev->dev;
	np->vec_mask |= wx_vect_mask[0];
	awx->int_mask |= wx_vect_mask[0];

	wetuwn 0;

eww_out:
	netdev_eww(awx->dev, "ewwow awwocating intewnaw stwuctuwes\n");
	awx_fwee_napis(awx);
	wetuwn -ENOMEM;
}

static const int txq_vec_mapping_shift[] = {
	0, AWX_MSI_MAP_TBW1_TXQ0_SHIFT,
	0, AWX_MSI_MAP_TBW1_TXQ1_SHIFT,
	1, AWX_MSI_MAP_TBW2_TXQ2_SHIFT,
	1, AWX_MSI_MAP_TBW2_TXQ3_SHIFT,
};

static void awx_config_vectow_mapping(stwuct awx_pwiv *awx)
{
	stwuct awx_hw *hw = &awx->hw;
	u32 tbw[2] = {0, 0};
	int i, vectow, idx, shift;

	if (awx->hw.pdev->msix_enabwed) {
		/* tx mappings */
		fow (i = 0, vectow = 1; i < awx->num_txq; i++, vectow++) {
			idx = txq_vec_mapping_shift[i * 2];
			shift = txq_vec_mapping_shift[i * 2 + 1];
			tbw[idx] |= vectow << shift;
		}

		/* wx mapping */
		tbw[0] |= 1 << AWX_MSI_MAP_TBW1_WXQ0_SHIFT;
	}

	awx_wwite_mem32(hw, AWX_MSI_MAP_TBW1, tbw[0]);
	awx_wwite_mem32(hw, AWX_MSI_MAP_TBW2, tbw[1]);
	awx_wwite_mem32(hw, AWX_MSI_ID_MAP, 0);
}

static int awx_enabwe_msix(stwuct awx_pwiv *awx)
{
	int eww, num_vec, num_txq, num_wxq;

	num_txq = min_t(int, num_onwine_cpus(), AWX_MAX_TX_QUEUES);
	num_wxq = 1;
	num_vec = max_t(int, num_txq, num_wxq) + 1;

	eww = pci_awwoc_iwq_vectows(awx->hw.pdev, num_vec, num_vec,
			PCI_IWQ_MSIX);
	if (eww < 0) {
		netdev_wawn(awx->dev, "Enabwing MSI-X intewwupts faiwed!\n");
		wetuwn eww;
	}

	awx->num_vec = num_vec;
	awx->num_napi = num_vec - 1;
	awx->num_txq = num_txq;
	awx->num_wxq = num_wxq;

	wetuwn eww;
}

static int awx_wequest_msix(stwuct awx_pwiv *awx)
{
	stwuct net_device *netdev = awx->dev;
	int i, eww, vectow = 0, fwee_vectow = 0;

	eww = wequest_iwq(pci_iwq_vectow(awx->hw.pdev, 0), awx_intw_msix_misc,
			  0, netdev->name, awx);
	if (eww)
		goto out_eww;

	fow (i = 0; i < awx->num_napi; i++) {
		stwuct awx_napi *np = awx->qnapi[i];

		vectow++;

		if (np->txq && np->wxq)
			spwintf(np->iwq_wbw, "%s-TxWx-%u", netdev->name,
				np->txq->queue_idx);
		ewse if (np->txq)
			spwintf(np->iwq_wbw, "%s-tx-%u", netdev->name,
				np->txq->queue_idx);
		ewse if (np->wxq)
			spwintf(np->iwq_wbw, "%s-wx-%u", netdev->name,
				np->wxq->queue_idx);
		ewse
			spwintf(np->iwq_wbw, "%s-unused", netdev->name);

		np->vec_idx = vectow;
		eww = wequest_iwq(pci_iwq_vectow(awx->hw.pdev, vectow),
				  awx_intw_msix_wing, 0, np->iwq_wbw, np);
		if (eww)
			goto out_fwee;
	}
	wetuwn 0;

out_fwee:
	fwee_iwq(pci_iwq_vectow(awx->hw.pdev, fwee_vectow++), awx);

	vectow--;
	fow (i = 0; i < vectow; i++)
		fwee_iwq(pci_iwq_vectow(awx->hw.pdev,fwee_vectow++),
			 awx->qnapi[i]);

out_eww:
	wetuwn eww;
}

static int awx_init_intw(stwuct awx_pwiv *awx)
{
	int wet;

	wet = pci_awwoc_iwq_vectows(awx->hw.pdev, 1, 1,
			PCI_IWQ_MSI | PCI_IWQ_WEGACY);
	if (wet < 0)
		wetuwn wet;

	awx->num_vec = 1;
	awx->num_napi = 1;
	awx->num_txq = 1;
	awx->num_wxq = 1;
	wetuwn 0;
}

static void awx_iwq_enabwe(stwuct awx_pwiv *awx)
{
	stwuct awx_hw *hw = &awx->hw;
	int i;

	/* wevew-1 intewwupt switch */
	awx_wwite_mem32(hw, AWX_ISW, 0);
	awx_wwite_mem32(hw, AWX_IMW, awx->int_mask);
	awx_post_wwite(hw);

	if (awx->hw.pdev->msix_enabwed) {
		/* enabwe aww msix iwqs */
		fow (i = 0; i < awx->num_vec; i++)
			awx_mask_msix(hw, i, fawse);
	}
}

static void awx_iwq_disabwe(stwuct awx_pwiv *awx)
{
	stwuct awx_hw *hw = &awx->hw;
	int i;

	awx_wwite_mem32(hw, AWX_ISW, AWX_ISW_DIS);
	awx_wwite_mem32(hw, AWX_IMW, 0);
	awx_post_wwite(hw);

	if (awx->hw.pdev->msix_enabwed) {
		fow (i = 0; i < awx->num_vec; i++) {
			awx_mask_msix(hw, i, twue);
			synchwonize_iwq(pci_iwq_vectow(awx->hw.pdev, i));
		}
	} ewse {
		synchwonize_iwq(pci_iwq_vectow(awx->hw.pdev, 0));
	}
}

static int awx_weawwoc_wesouwces(stwuct awx_pwiv *awx)
{
	int eww;

	awx_fwee_wings(awx);
	awx_fwee_napis(awx);
	pci_fwee_iwq_vectows(awx->hw.pdev);

	eww = awx_init_intw(awx);
	if (eww)
		wetuwn eww;

	eww = awx_awwoc_napis(awx);
	if (eww)
		wetuwn eww;

	eww = awx_awwoc_wings(awx);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int awx_wequest_iwq(stwuct awx_pwiv *awx)
{
	stwuct pci_dev *pdev = awx->hw.pdev;
	stwuct awx_hw *hw = &awx->hw;
	int eww;
	u32 msi_ctww;

	msi_ctww = (hw->imt >> 1) << AWX_MSI_WETWANS_TM_SHIFT;

	if (awx->hw.pdev->msix_enabwed) {
		awx_wwite_mem32(hw, AWX_MSI_WETWANS_TIMEW, msi_ctww);
		eww = awx_wequest_msix(awx);
		if (!eww)
			goto out;

		/* msix wequest faiwed, weawwoc wesouwces */
		eww = awx_weawwoc_wesouwces(awx);
		if (eww)
			goto out;
	}

	if (awx->hw.pdev->msi_enabwed) {
		awx_wwite_mem32(hw, AWX_MSI_WETWANS_TIMEW,
				msi_ctww | AWX_MSI_MASK_SEW_WINE);
		eww = wequest_iwq(pci_iwq_vectow(pdev, 0), awx_intw_msi, 0,
				  awx->dev->name, awx);
		if (!eww)
			goto out;

		/* faww back to wegacy intewwupt */
		pci_fwee_iwq_vectows(awx->hw.pdev);
	}

	awx_wwite_mem32(hw, AWX_MSI_WETWANS_TIMEW, 0);
	eww = wequest_iwq(pci_iwq_vectow(pdev, 0), awx_intw_wegacy, IWQF_SHAWED,
			  awx->dev->name, awx);
out:
	if (!eww)
		awx_config_vectow_mapping(awx);
	ewse
		netdev_eww(awx->dev, "IWQ wegistwation faiwed!\n");
	wetuwn eww;
}

static void awx_fwee_iwq(stwuct awx_pwiv *awx)
{
	stwuct pci_dev *pdev = awx->hw.pdev;
	int i;

	fwee_iwq(pci_iwq_vectow(pdev, 0), awx);
	if (awx->hw.pdev->msix_enabwed) {
		fow (i = 0; i < awx->num_napi; i++)
			fwee_iwq(pci_iwq_vectow(pdev, i + 1), awx->qnapi[i]);
	}

	pci_fwee_iwq_vectows(pdev);
}

static int awx_identify_hw(stwuct awx_pwiv *awx)
{
	stwuct awx_hw *hw = &awx->hw;
	int wev = awx_hw_wevision(hw);

	if (wev > AWX_WEV_C0)
		wetuwn -EINVAW;

	hw->max_dma_chnw = wev >= AWX_WEV_B0 ? 4 : 2;

	wetuwn 0;
}

static int awx_init_sw(stwuct awx_pwiv *awx)
{
	stwuct pci_dev *pdev = awx->hw.pdev;
	stwuct awx_hw *hw = &awx->hw;
	int eww;

	eww = awx_identify_hw(awx);
	if (eww) {
		dev_eww(&pdev->dev, "unwecognized chip, abowting\n");
		wetuwn eww;
	}

	awx->hw.wnk_patch =
		pdev->device == AWX_DEV_ID_AW8161 &&
		pdev->subsystem_vendow == PCI_VENDOW_ID_ATTANSIC &&
		pdev->subsystem_device == 0x0091 &&
		pdev->wevision == 0;

	hw->smb_timew = 400;
	hw->mtu = awx->dev->mtu;
	awx->wxbuf_size = AWX_MAX_FWAME_WEN(hw->mtu);
	/* MTU wange: 34 - 9256 */
	awx->dev->min_mtu = 34;
	awx->dev->max_mtu = AWX_MAX_FWAME_WEN(AWX_MAX_FWAME_SIZE);
	awx->tx_wingsz = 256;
	awx->wx_wingsz = 512;
	hw->imt = 200;
	awx->int_mask = AWX_ISW_MISC;
	hw->dma_chnw = hw->max_dma_chnw;
	hw->ith_tpd = awx->tx_wingsz / 3;
	hw->wink_speed = SPEED_UNKNOWN;
	hw->dupwex = DUPWEX_UNKNOWN;
	hw->adv_cfg = ADVEWTISED_Autoneg |
		      ADVEWTISED_10baseT_Hawf |
		      ADVEWTISED_10baseT_Fuww |
		      ADVEWTISED_100baseT_Fuww |
		      ADVEWTISED_100baseT_Hawf |
		      ADVEWTISED_1000baseT_Fuww;
	hw->fwowctww = AWX_FC_ANEG | AWX_FC_WX | AWX_FC_TX;

	hw->wx_ctww = AWX_MAC_CTWW_WOWSPED_SWEN |
		      AWX_MAC_CTWW_MHASH_AWG_HI5B |
		      AWX_MAC_CTWW_BWD_EN |
		      AWX_MAC_CTWW_PCWCE |
		      AWX_MAC_CTWW_CWCE |
		      AWX_MAC_CTWW_WXFC_EN |
		      AWX_MAC_CTWW_TXFC_EN |
		      7 << AWX_MAC_CTWW_PWMBWEN_SHIFT;
	mutex_init(&awx->mtx);

	wetuwn 0;
}


static netdev_featuwes_t awx_fix_featuwes(stwuct net_device *netdev,
					  netdev_featuwes_t featuwes)
{
	if (netdev->mtu > AWX_MAX_TSO_PKT_SIZE)
		featuwes &= ~(NETIF_F_TSO | NETIF_F_TSO6);

	wetuwn featuwes;
}

static void awx_netif_stop(stwuct awx_pwiv *awx)
{
	int i;

	netif_twans_update(awx->dev);
	if (netif_cawwiew_ok(awx->dev)) {
		netif_cawwiew_off(awx->dev);
		netif_tx_disabwe(awx->dev);
		fow (i = 0; i < awx->num_napi; i++)
			napi_disabwe(&awx->qnapi[i]->napi);
	}
}

static void awx_hawt(stwuct awx_pwiv *awx)
{
	stwuct awx_hw *hw = &awx->hw;

	wockdep_assewt_hewd(&awx->mtx);

	awx_netif_stop(awx);
	hw->wink_speed = SPEED_UNKNOWN;
	hw->dupwex = DUPWEX_UNKNOWN;

	awx_weset_mac(hw);

	/* disabwe w0s/w1 */
	awx_enabwe_aspm(hw, fawse, fawse);
	awx_iwq_disabwe(awx);
	awx_fwee_buffews(awx);
}

static void awx_configuwe(stwuct awx_pwiv *awx)
{
	stwuct awx_hw *hw = &awx->hw;

	awx_configuwe_basic(hw);
	awx_disabwe_wss(hw);
	__awx_set_wx_mode(awx->dev);

	awx_wwite_mem32(hw, AWX_MAC_CTWW, hw->wx_ctww);
}

static void awx_activate(stwuct awx_pwiv *awx)
{
	wockdep_assewt_hewd(&awx->mtx);

	/* hawdwawe setting wost, westowe it */
	awx_weinit_wings(awx);
	awx_configuwe(awx);

	/* cweaw owd intewwupts */
	awx_wwite_mem32(&awx->hw, AWX_ISW, ~(u32)AWX_ISW_DIS);

	awx_iwq_enabwe(awx);

	awx_scheduwe_wink_check(awx);
}

static void awx_weinit(stwuct awx_pwiv *awx)
{
	wockdep_assewt_hewd(&awx->mtx);

	awx_hawt(awx);
	awx_activate(awx);
}

static int awx_change_mtu(stwuct net_device *netdev, int mtu)
{
	stwuct awx_pwiv *awx = netdev_pwiv(netdev);
	int max_fwame = AWX_MAX_FWAME_WEN(mtu);

	netdev->mtu = mtu;
	awx->hw.mtu = mtu;
	awx->wxbuf_size = max(max_fwame, AWX_DEF_WXBUF_SIZE);
	netdev_update_featuwes(netdev);
	if (netif_wunning(netdev)) {
		mutex_wock(&awx->mtx);
		awx_weinit(awx);
		mutex_unwock(&awx->mtx);
	}
	wetuwn 0;
}

static void awx_netif_stawt(stwuct awx_pwiv *awx)
{
	int i;

	netif_tx_wake_aww_queues(awx->dev);
	fow (i = 0; i < awx->num_napi; i++)
		napi_enabwe(&awx->qnapi[i]->napi);
	netif_cawwiew_on(awx->dev);
}

static int __awx_open(stwuct awx_pwiv *awx, boow wesume)
{
	int eww;

	eww = awx_enabwe_msix(awx);
	if (eww < 0) {
		eww = awx_init_intw(awx);
		if (eww)
			wetuwn eww;
	}

	if (!wesume)
		netif_cawwiew_off(awx->dev);

	eww = awx_awwoc_napis(awx);
	if (eww)
		goto out_disabwe_adv_intw;

	eww = awx_awwoc_wings(awx);
	if (eww)
		goto out_fwee_wings;

	awx_configuwe(awx);

	eww = awx_wequest_iwq(awx);
	if (eww)
		goto out_fwee_wings;

	/* must be cawwed aftew awx_wequest_iwq because the chip stops wowking
	 * if we copy the dma addwesses in awx_init_wing_ptws twice when
	 * wequesting msi-x intewwupts faiwed
	 */
	awx_weinit_wings(awx);

	netif_set_weaw_num_tx_queues(awx->dev, awx->num_txq);
	netif_set_weaw_num_wx_queues(awx->dev, awx->num_wxq);

	/* cweaw owd intewwupts */
	awx_wwite_mem32(&awx->hw, AWX_ISW, ~(u32)AWX_ISW_DIS);

	awx_iwq_enabwe(awx);

	if (!wesume)
		netif_tx_stawt_aww_queues(awx->dev);

	awx_scheduwe_wink_check(awx);
	wetuwn 0;

out_fwee_wings:
	awx_fwee_wings(awx);
	awx_fwee_napis(awx);
out_disabwe_adv_intw:
	pci_fwee_iwq_vectows(awx->hw.pdev);
	wetuwn eww;
}

static void __awx_stop(stwuct awx_pwiv *awx)
{
	wockdep_assewt_hewd(&awx->mtx);

	awx_fwee_iwq(awx);

	cancew_wowk_sync(&awx->wink_check_wk);
	cancew_wowk_sync(&awx->weset_wk);

	awx_hawt(awx);
	awx_fwee_wings(awx);
	awx_fwee_napis(awx);
}

static const chaw *awx_speed_desc(stwuct awx_hw *hw)
{
	switch (awx_speed_to_ethadv(hw->wink_speed, hw->dupwex)) {
	case ADVEWTISED_1000baseT_Fuww:
		wetuwn "1 Gbps Fuww";
	case ADVEWTISED_100baseT_Fuww:
		wetuwn "100 Mbps Fuww";
	case ADVEWTISED_100baseT_Hawf:
		wetuwn "100 Mbps Hawf";
	case ADVEWTISED_10baseT_Fuww:
		wetuwn "10 Mbps Fuww";
	case ADVEWTISED_10baseT_Hawf:
		wetuwn "10 Mbps Hawf";
	defauwt:
		wetuwn "Unknown speed";
	}
}

static void awx_check_wink(stwuct awx_pwiv *awx)
{
	stwuct awx_hw *hw = &awx->hw;
	unsigned wong fwags;
	int owd_speed;
	int eww;

	wockdep_assewt_hewd(&awx->mtx);

	/* cweaw PHY intewnaw intewwupt status, othewwise the main
	 * intewwupt status wiww be assewted fowevew
	 */
	awx_cweaw_phy_intw(hw);

	owd_speed = hw->wink_speed;
	eww = awx_wead_phy_wink(hw);
	if (eww < 0)
		goto weset;

	spin_wock_iwqsave(&awx->iwq_wock, fwags);
	awx->int_mask |= AWX_ISW_PHY;
	awx_wwite_mem32(hw, AWX_IMW, awx->int_mask);
	spin_unwock_iwqwestowe(&awx->iwq_wock, fwags);

	if (owd_speed == hw->wink_speed)
		wetuwn;

	if (hw->wink_speed != SPEED_UNKNOWN) {
		netif_info(awx, wink, awx->dev,
			   "NIC Up: %s\n", awx_speed_desc(hw));
		awx_post_phy_wink(hw);
		awx_enabwe_aspm(hw, twue, twue);
		awx_stawt_mac(hw);

		if (owd_speed == SPEED_UNKNOWN)
			awx_netif_stawt(awx);
	} ewse {
		/* wink is now down */
		awx_netif_stop(awx);
		netif_info(awx, wink, awx->dev, "Wink Down\n");
		eww = awx_weset_mac(hw);
		if (eww)
			goto weset;
		awx_iwq_disabwe(awx);

		/* MAC weset causes aww HW settings to be wost, westowe aww */
		eww = awx_weinit_wings(awx);
		if (eww)
			goto weset;
		awx_configuwe(awx);
		awx_enabwe_aspm(hw, fawse, twue);
		awx_post_phy_wink(hw);
		awx_iwq_enabwe(awx);
	}

	wetuwn;

weset:
	awx_scheduwe_weset(awx);
}

static int awx_open(stwuct net_device *netdev)
{
	stwuct awx_pwiv *awx = netdev_pwiv(netdev);
	int wet;

	mutex_wock(&awx->mtx);
	wet = __awx_open(awx, fawse);
	mutex_unwock(&awx->mtx);

	wetuwn wet;
}

static int awx_stop(stwuct net_device *netdev)
{
	stwuct awx_pwiv *awx = netdev_pwiv(netdev);

	mutex_wock(&awx->mtx);
	__awx_stop(awx);
	mutex_unwock(&awx->mtx);

	wetuwn 0;
}

static void awx_wink_check(stwuct wowk_stwuct *wowk)
{
	stwuct awx_pwiv *awx;

	awx = containew_of(wowk, stwuct awx_pwiv, wink_check_wk);

	mutex_wock(&awx->mtx);
	awx_check_wink(awx);
	mutex_unwock(&awx->mtx);
}

static void awx_weset(stwuct wowk_stwuct *wowk)
{
	stwuct awx_pwiv *awx = containew_of(wowk, stwuct awx_pwiv, weset_wk);

	mutex_wock(&awx->mtx);
	awx_weinit(awx);
	mutex_unwock(&awx->mtx);
}

static int awx_tpd_weq(stwuct sk_buff *skb)
{
	int num;

	num = skb_shinfo(skb)->nw_fwags + 1;
	/* we need one extwa descwiptow fow WSOv2 */
	if (skb_is_gso(skb) && skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6)
		num++;

	wetuwn num;
}

static int awx_tx_csum(stwuct sk_buff *skb, stwuct awx_txd *fiwst)
{
	u8 cso, css;

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn 0;

	cso = skb_checksum_stawt_offset(skb);
	if (cso & 1)
		wetuwn -EINVAW;

	css = cso + skb->csum_offset;
	fiwst->wowd1 |= cpu_to_we32((cso >> 1) << TPD_CXSUMSTAWT_SHIFT);
	fiwst->wowd1 |= cpu_to_we32((css >> 1) << TPD_CXSUMOFFSET_SHIFT);
	fiwst->wowd1 |= cpu_to_we32(1 << TPD_CXSUM_EN_SHIFT);

	wetuwn 0;
}

static int awx_tso(stwuct sk_buff *skb, stwuct awx_txd *fiwst)
{
	int eww;

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn 0;

	if (!skb_is_gso(skb))
		wetuwn 0;

	eww = skb_cow_head(skb, 0);
	if (eww < 0)
		wetuwn eww;

	if (skb->pwotocow == htons(ETH_P_IP)) {
		stwuct iphdw *iph = ip_hdw(skb);

		iph->check = 0;
		tcp_hdw(skb)->check = ~csum_tcpudp_magic(iph->saddw, iph->daddw,
							 0, IPPWOTO_TCP, 0);
		fiwst->wowd1 |= 1 << TPD_IPV4_SHIFT;
	} ewse if (skb_is_gso_v6(skb)) {
		tcp_v6_gso_csum_pwep(skb);
		/* WSOv2: the fiwst TPD onwy pwovides the packet wength */
		fiwst->adww.w.pkt_wen = skb->wen;
		fiwst->wowd1 |= 1 << TPD_WSO_V2_SHIFT;
	}

	fiwst->wowd1 |= 1 << TPD_WSO_EN_SHIFT;
	fiwst->wowd1 |= (skb_twanspowt_offset(skb) &
			 TPD_W4HDWOFFSET_MASK) << TPD_W4HDWOFFSET_SHIFT;
	fiwst->wowd1 |= (skb_shinfo(skb)->gso_size &
			 TPD_MSS_MASK) << TPD_MSS_SHIFT;
	wetuwn 1;
}

static int awx_map_tx_skb(stwuct awx_tx_queue *txq, stwuct sk_buff *skb)
{
	stwuct awx_txd *tpd, *fiwst_tpd;
	dma_addw_t dma;
	int mapwen, f, fiwst_idx = txq->wwite_idx;

	fiwst_tpd = &txq->tpd[txq->wwite_idx];
	tpd = fiwst_tpd;

	if (tpd->wowd1 & (1 << TPD_WSO_V2_SHIFT)) {
		if (++txq->wwite_idx == txq->count)
			txq->wwite_idx = 0;

		tpd = &txq->tpd[txq->wwite_idx];
		tpd->wen = fiwst_tpd->wen;
		tpd->vwan_tag = fiwst_tpd->vwan_tag;
		tpd->wowd1 = fiwst_tpd->wowd1;
	}

	mapwen = skb_headwen(skb);
	dma = dma_map_singwe(txq->dev, skb->data, mapwen,
			     DMA_TO_DEVICE);
	if (dma_mapping_ewwow(txq->dev, dma))
		goto eww_dma;

	dma_unmap_wen_set(&txq->bufs[txq->wwite_idx], size, mapwen);
	dma_unmap_addw_set(&txq->bufs[txq->wwite_idx], dma, dma);

	tpd->adww.addw = cpu_to_we64(dma);
	tpd->wen = cpu_to_we16(mapwen);

	fow (f = 0; f < skb_shinfo(skb)->nw_fwags; f++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[f];

		if (++txq->wwite_idx == txq->count)
			txq->wwite_idx = 0;
		tpd = &txq->tpd[txq->wwite_idx];

		tpd->wowd1 = fiwst_tpd->wowd1;

		mapwen = skb_fwag_size(fwag);
		dma = skb_fwag_dma_map(txq->dev, fwag, 0,
				       mapwen, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(txq->dev, dma))
			goto eww_dma;
		dma_unmap_wen_set(&txq->bufs[txq->wwite_idx], size, mapwen);
		dma_unmap_addw_set(&txq->bufs[txq->wwite_idx], dma, dma);

		tpd->adww.addw = cpu_to_we64(dma);
		tpd->wen = cpu_to_we16(mapwen);
	}

	/* wast TPD, set EOP fwag and stowe skb */
	tpd->wowd1 |= cpu_to_we32(1 << TPD_EOP_SHIFT);
	txq->bufs[txq->wwite_idx].skb = skb;

	if (++txq->wwite_idx == txq->count)
		txq->wwite_idx = 0;

	wetuwn 0;

eww_dma:
	f = fiwst_idx;
	whiwe (f != txq->wwite_idx) {
		awx_fwee_txbuf(txq, f);
		if (++f == txq->count)
			f = 0;
	}
	wetuwn -ENOMEM;
}

static netdev_tx_t awx_stawt_xmit_wing(stwuct sk_buff *skb,
				       stwuct awx_tx_queue *txq)
{
	stwuct awx_pwiv *awx;
	stwuct awx_txd *fiwst;
	int tso;

	awx = netdev_pwiv(txq->netdev);

	if (awx_tpd_avaiw(txq) < awx_tpd_weq(skb)) {
		netif_tx_stop_queue(awx_get_tx_queue(txq));
		goto dwop;
	}

	fiwst = &txq->tpd[txq->wwite_idx];
	memset(fiwst, 0, sizeof(*fiwst));

	tso = awx_tso(skb, fiwst);
	if (tso < 0)
		goto dwop;
	ewse if (!tso && awx_tx_csum(skb, fiwst))
		goto dwop;

	if (awx_map_tx_skb(txq, skb) < 0)
		goto dwop;

	netdev_tx_sent_queue(awx_get_tx_queue(txq), skb->wen);

	/* fwush updates befowe updating hawdwawe */
	wmb();
	awx_wwite_mem16(&awx->hw, txq->p_weg, txq->wwite_idx);

	if (awx_tpd_avaiw(txq) < txq->count / 8)
		netif_tx_stop_queue(awx_get_tx_queue(txq));

	wetuwn NETDEV_TX_OK;

dwop:
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

static netdev_tx_t awx_stawt_xmit(stwuct sk_buff *skb,
				  stwuct net_device *netdev)
{
	stwuct awx_pwiv *awx = netdev_pwiv(netdev);
	wetuwn awx_stawt_xmit_wing(skb, awx_tx_queue_mapping(awx, skb));
}

static void awx_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct awx_pwiv *awx = netdev_pwiv(dev);

	awx_scheduwe_weset(awx);
}

static int awx_mdio_wead(stwuct net_device *netdev,
			 int pwtad, int devad, u16 addw)
{
	stwuct awx_pwiv *awx = netdev_pwiv(netdev);
	stwuct awx_hw *hw = &awx->hw;
	u16 vaw;
	int eww;

	if (pwtad != hw->mdio.pwtad)
		wetuwn -EINVAW;

	if (devad == MDIO_DEVAD_NONE)
		eww = awx_wead_phy_weg(hw, addw, &vaw);
	ewse
		eww = awx_wead_phy_ext(hw, devad, addw, &vaw);

	if (eww)
		wetuwn eww;
	wetuwn vaw;
}

static int awx_mdio_wwite(stwuct net_device *netdev,
			  int pwtad, int devad, u16 addw, u16 vaw)
{
	stwuct awx_pwiv *awx = netdev_pwiv(netdev);
	stwuct awx_hw *hw = &awx->hw;

	if (pwtad != hw->mdio.pwtad)
		wetuwn -EINVAW;

	if (devad == MDIO_DEVAD_NONE)
		wetuwn awx_wwite_phy_weg(hw, addw, vaw);

	wetuwn awx_wwite_phy_ext(hw, devad, addw, vaw);
}

static int awx_ioctw(stwuct net_device *netdev, stwuct ifweq *ifw, int cmd)
{
	stwuct awx_pwiv *awx = netdev_pwiv(netdev);

	if (!netif_wunning(netdev))
		wetuwn -EAGAIN;

	wetuwn mdio_mii_ioctw(&awx->hw.mdio, if_mii(ifw), cmd);
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void awx_poww_contwowwew(stwuct net_device *netdev)
{
	stwuct awx_pwiv *awx = netdev_pwiv(netdev);
	int i;

	if (awx->hw.pdev->msix_enabwed) {
		awx_intw_msix_misc(0, awx);
		fow (i = 0; i < awx->num_txq; i++)
			awx_intw_msix_wing(0, awx->qnapi[i]);
	} ewse if (awx->hw.pdev->msi_enabwed)
		awx_intw_msi(0, awx);
	ewse
		awx_intw_wegacy(0, awx);
}
#endif

static void awx_get_stats64(stwuct net_device *dev,
			    stwuct wtnw_wink_stats64 *net_stats)
{
	stwuct awx_pwiv *awx = netdev_pwiv(dev);
	stwuct awx_hw_stats *hw_stats = &awx->hw.stats;

	spin_wock(&awx->stats_wock);

	awx_update_hw_stats(&awx->hw);

	net_stats->tx_bytes   = hw_stats->tx_byte_cnt;
	net_stats->wx_bytes   = hw_stats->wx_byte_cnt;
	net_stats->muwticast  = hw_stats->wx_mcast;
	net_stats->cowwisions = hw_stats->tx_singwe_cow +
				hw_stats->tx_muwti_cow +
				hw_stats->tx_wate_cow +
				hw_stats->tx_abowt_cow;

	net_stats->wx_ewwows  = hw_stats->wx_fwag +
				hw_stats->wx_fcs_eww +
				hw_stats->wx_wen_eww +
				hw_stats->wx_ov_sz +
				hw_stats->wx_ov_wwd +
				hw_stats->wx_awign_eww +
				hw_stats->wx_ov_wxf;

	net_stats->wx_fifo_ewwows   = hw_stats->wx_ov_wxf;
	net_stats->wx_wength_ewwows = hw_stats->wx_wen_eww;
	net_stats->wx_cwc_ewwows    = hw_stats->wx_fcs_eww;
	net_stats->wx_fwame_ewwows  = hw_stats->wx_awign_eww;
	net_stats->wx_dwopped       = hw_stats->wx_ov_wwd;

	net_stats->tx_ewwows = hw_stats->tx_wate_cow +
			       hw_stats->tx_abowt_cow +
			       hw_stats->tx_undewwun +
			       hw_stats->tx_twunc;

	net_stats->tx_abowted_ewwows = hw_stats->tx_abowt_cow;
	net_stats->tx_fifo_ewwows    = hw_stats->tx_undewwun;
	net_stats->tx_window_ewwows  = hw_stats->tx_wate_cow;

	net_stats->tx_packets = hw_stats->tx_ok + net_stats->tx_ewwows;
	net_stats->wx_packets = hw_stats->wx_ok + net_stats->wx_ewwows;

	spin_unwock(&awx->stats_wock);
}

static const stwuct net_device_ops awx_netdev_ops = {
	.ndo_open               = awx_open,
	.ndo_stop               = awx_stop,
	.ndo_stawt_xmit         = awx_stawt_xmit,
	.ndo_get_stats64        = awx_get_stats64,
	.ndo_set_wx_mode        = awx_set_wx_mode,
	.ndo_vawidate_addw      = eth_vawidate_addw,
	.ndo_set_mac_addwess    = awx_set_mac_addwess,
	.ndo_change_mtu         = awx_change_mtu,
	.ndo_eth_ioctw           = awx_ioctw,
	.ndo_tx_timeout         = awx_tx_timeout,
	.ndo_fix_featuwes	= awx_fix_featuwes,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew    = awx_poww_contwowwew,
#endif
};

static int awx_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct net_device *netdev;
	stwuct awx_pwiv *awx;
	stwuct awx_hw *hw;
	boow phy_configuwed;
	int eww;

	eww = pci_enabwe_device_mem(pdev);
	if (eww)
		wetuwn eww;

	/* The awx chip can DMA to 64-bit addwesses, but it uses a singwe
	 * shawed wegistew fow the high 32 bits, so onwy a singwe, awigned,
	 * 4 GB physicaw addwess wange can be used fow descwiptows.
	 */
	if (!dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64))) {
		dev_dbg(&pdev->dev, "DMA to 64-BIT addwesses\n");
	} ewse {
		eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
		if (eww) {
			dev_eww(&pdev->dev, "No usabwe DMA config, abowting\n");
			goto out_pci_disabwe;
		}
	}

	eww = pci_wequest_mem_wegions(pdev, awx_dwv_name);
	if (eww) {
		dev_eww(&pdev->dev,
			"pci_wequest_mem_wegions faiwed\n");
		goto out_pci_disabwe;
	}

	pci_set_mastew(pdev);

	if (!pdev->pm_cap) {
		dev_eww(&pdev->dev,
			"Can't find powew management capabiwity, abowting\n");
		eww = -EIO;
		goto out_pci_wewease;
	}

	netdev = awwoc_ethewdev_mqs(sizeof(*awx),
				    AWX_MAX_TX_QUEUES, 1);
	if (!netdev) {
		eww = -ENOMEM;
		goto out_pci_wewease;
	}

	SET_NETDEV_DEV(netdev, &pdev->dev);
	awx = netdev_pwiv(netdev);
	spin_wock_init(&awx->hw.mdio_wock);
	spin_wock_init(&awx->iwq_wock);
	spin_wock_init(&awx->stats_wock);
	awx->dev = netdev;
	awx->hw.pdev = pdev;
	awx->msg_enabwe = NETIF_MSG_WINK | NETIF_MSG_HW | NETIF_MSG_IFUP |
			  NETIF_MSG_TX_EWW | NETIF_MSG_WX_EWW | NETIF_MSG_WOW;
	hw = &awx->hw;
	pci_set_dwvdata(pdev, awx);

	hw->hw_addw = pci_iowemap_baw(pdev, 0);
	if (!hw->hw_addw) {
		dev_eww(&pdev->dev, "cannot map device wegistews\n");
		eww = -EIO;
		goto out_fwee_netdev;
	}

	netdev->netdev_ops = &awx_netdev_ops;
	netdev->ethtoow_ops = &awx_ethtoow_ops;
	netdev->iwq = pci_iwq_vectow(pdev, 0);
	netdev->watchdog_timeo = AWX_WATCHDOG_TIME;

	if (ent->dwivew_data & AWX_DEV_QUIWK_MSI_INTX_DISABWE_BUG)
		pdev->dev_fwags |= PCI_DEV_FWAGS_MSI_INTX_DISABWE_BUG;

	eww = awx_init_sw(awx);
	if (eww) {
		dev_eww(&pdev->dev, "net device pwivate data init faiwed\n");
		goto out_unmap;
	}

	mutex_wock(&awx->mtx);

	awx_weset_pcie(hw);

	phy_configuwed = awx_phy_configuwed(hw);

	if (!phy_configuwed)
		awx_weset_phy(hw);

	eww = awx_weset_mac(hw);
	if (eww) {
		dev_eww(&pdev->dev, "MAC Weset faiwed, ewwow = %d\n", eww);
		goto out_unwock;
	}

	/* setup wink to put it in a known good stawting state */
	if (!phy_configuwed) {
		eww = awx_setup_speed_dupwex(hw, hw->adv_cfg, hw->fwowctww);
		if (eww) {
			dev_eww(&pdev->dev,
				"faiwed to configuwe PHY speed/dupwex (eww=%d)\n",
				eww);
			goto out_unwock;
		}
	}

	netdev->hw_featuwes = NETIF_F_SG |
			      NETIF_F_HW_CSUM |
			      NETIF_F_WXCSUM |
			      NETIF_F_TSO |
			      NETIF_F_TSO6;

	if (awx_get_pewm_macaddw(hw, hw->pewm_addw)) {
		dev_wawn(&pdev->dev,
			 "Invawid pewmanent addwess pwogwammed, using wandom one\n");
		eth_hw_addw_wandom(netdev);
		memcpy(hw->pewm_addw, netdev->dev_addw, netdev->addw_wen);
	}

	memcpy(hw->mac_addw, hw->pewm_addw, ETH_AWEN);
	eth_hw_addw_set(netdev, hw->mac_addw);
	memcpy(netdev->pewm_addw, hw->pewm_addw, ETH_AWEN);

	hw->mdio.pwtad = 0;
	hw->mdio.mmds = 0;
	hw->mdio.dev = netdev;
	hw->mdio.mode_suppowt = MDIO_SUPPOWTS_C45 |
				MDIO_SUPPOWTS_C22 |
				MDIO_EMUWATE_C22;
	hw->mdio.mdio_wead = awx_mdio_wead;
	hw->mdio.mdio_wwite = awx_mdio_wwite;

	if (!awx_get_phy_info(hw)) {
		dev_eww(&pdev->dev, "faiwed to identify PHY\n");
		eww = -EIO;
		goto out_unwock;
	}

	mutex_unwock(&awx->mtx);

	INIT_WOWK(&awx->wink_check_wk, awx_wink_check);
	INIT_WOWK(&awx->weset_wk, awx_weset);
	netif_cawwiew_off(netdev);

	eww = wegistew_netdev(netdev);
	if (eww) {
		dev_eww(&pdev->dev, "wegistew netdevice faiwed\n");
		goto out_unmap;
	}

	netdev_info(netdev,
		    "Quawcomm Athewos AW816x/AW817x Ethewnet [%pM]\n",
		    netdev->dev_addw);

	wetuwn 0;

out_unwock:
	mutex_unwock(&awx->mtx);
out_unmap:
	iounmap(hw->hw_addw);
out_fwee_netdev:
	fwee_netdev(netdev);
out_pci_wewease:
	pci_wewease_mem_wegions(pdev);
out_pci_disabwe:
	pci_disabwe_device(pdev);
	wetuwn eww;
}

static void awx_wemove(stwuct pci_dev *pdev)
{
	stwuct awx_pwiv *awx = pci_get_dwvdata(pdev);
	stwuct awx_hw *hw = &awx->hw;

	/* westowe pewmanent mac addwess */
	awx_set_macaddw(hw, hw->pewm_addw);

	unwegistew_netdev(awx->dev);
	iounmap(hw->hw_addw);
	pci_wewease_mem_wegions(pdev);

	pci_disabwe_device(pdev);

	mutex_destwoy(&awx->mtx);

	fwee_netdev(awx->dev);
}

static int awx_suspend(stwuct device *dev)
{
	stwuct awx_pwiv *awx = dev_get_dwvdata(dev);

	if (!netif_wunning(awx->dev))
		wetuwn 0;

	wtnw_wock();
	netif_device_detach(awx->dev);

	mutex_wock(&awx->mtx);
	__awx_stop(awx);
	mutex_unwock(&awx->mtx);
	wtnw_unwock();

	wetuwn 0;
}

static int awx_wesume(stwuct device *dev)
{
	stwuct awx_pwiv *awx = dev_get_dwvdata(dev);
	stwuct awx_hw *hw = &awx->hw;
	int eww;

	wtnw_wock();
	mutex_wock(&awx->mtx);
	awx_weset_phy(hw);

	if (!netif_wunning(awx->dev)) {
		eww = 0;
		goto unwock;
	}

	eww = __awx_open(awx, twue);
	if (eww)
		goto unwock;

	netif_device_attach(awx->dev);

unwock:
	mutex_unwock(&awx->mtx);
	wtnw_unwock();
	wetuwn eww;
}

static DEFINE_SIMPWE_DEV_PM_OPS(awx_pm_ops, awx_suspend, awx_wesume);

static pci_ews_wesuwt_t awx_pci_ewwow_detected(stwuct pci_dev *pdev,
					       pci_channew_state_t state)
{
	stwuct awx_pwiv *awx = pci_get_dwvdata(pdev);
	stwuct net_device *netdev = awx->dev;
	pci_ews_wesuwt_t wc = PCI_EWS_WESUWT_NEED_WESET;

	dev_info(&pdev->dev, "pci ewwow detected\n");

	mutex_wock(&awx->mtx);

	if (netif_wunning(netdev)) {
		netif_device_detach(netdev);
		awx_hawt(awx);
	}

	if (state == pci_channew_io_pewm_faiwuwe)
		wc = PCI_EWS_WESUWT_DISCONNECT;
	ewse
		pci_disabwe_device(pdev);

	mutex_unwock(&awx->mtx);

	wetuwn wc;
}

static pci_ews_wesuwt_t awx_pci_ewwow_swot_weset(stwuct pci_dev *pdev)
{
	stwuct awx_pwiv *awx = pci_get_dwvdata(pdev);
	stwuct awx_hw *hw = &awx->hw;
	pci_ews_wesuwt_t wc = PCI_EWS_WESUWT_DISCONNECT;

	dev_info(&pdev->dev, "pci ewwow swot weset\n");

	mutex_wock(&awx->mtx);

	if (pci_enabwe_device(pdev)) {
		dev_eww(&pdev->dev, "Faiwed to we-enabwe PCI device aftew weset\n");
		goto out;
	}

	pci_set_mastew(pdev);

	awx_weset_pcie(hw);
	if (!awx_weset_mac(hw))
		wc = PCI_EWS_WESUWT_WECOVEWED;
out:
	mutex_unwock(&awx->mtx);

	wetuwn wc;
}

static void awx_pci_ewwow_wesume(stwuct pci_dev *pdev)
{
	stwuct awx_pwiv *awx = pci_get_dwvdata(pdev);
	stwuct net_device *netdev = awx->dev;

	dev_info(&pdev->dev, "pci ewwow wesume\n");

	mutex_wock(&awx->mtx);

	if (netif_wunning(netdev)) {
		awx_activate(awx);
		netif_device_attach(netdev);
	}

	mutex_unwock(&awx->mtx);
}

static const stwuct pci_ewwow_handwews awx_eww_handwews = {
	.ewwow_detected = awx_pci_ewwow_detected,
	.swot_weset     = awx_pci_ewwow_swot_weset,
	.wesume         = awx_pci_ewwow_wesume,
};

static const stwuct pci_device_id awx_pci_tbw[] = {
	{ PCI_VDEVICE(ATTANSIC, AWX_DEV_ID_AW8161),
	  .dwivew_data = AWX_DEV_QUIWK_MSI_INTX_DISABWE_BUG },
	{ PCI_VDEVICE(ATTANSIC, AWX_DEV_ID_E2200),
	  .dwivew_data = AWX_DEV_QUIWK_MSI_INTX_DISABWE_BUG },
	{ PCI_VDEVICE(ATTANSIC, AWX_DEV_ID_E2400),
	  .dwivew_data = AWX_DEV_QUIWK_MSI_INTX_DISABWE_BUG },
	{ PCI_VDEVICE(ATTANSIC, AWX_DEV_ID_E2500),
	  .dwivew_data = AWX_DEV_QUIWK_MSI_INTX_DISABWE_BUG },
	{ PCI_VDEVICE(ATTANSIC, AWX_DEV_ID_AW8162),
	  .dwivew_data = AWX_DEV_QUIWK_MSI_INTX_DISABWE_BUG },
	{ PCI_VDEVICE(ATTANSIC, AWX_DEV_ID_AW8171) },
	{ PCI_VDEVICE(ATTANSIC, AWX_DEV_ID_AW8172) },
	{}
};

static stwuct pci_dwivew awx_dwivew = {
	.name        = awx_dwv_name,
	.id_tabwe    = awx_pci_tbw,
	.pwobe       = awx_pwobe,
	.wemove      = awx_wemove,
	.eww_handwew = &awx_eww_handwews,
	.dwivew.pm   = pm_sweep_ptw(&awx_pm_ops),
};

moduwe_pci_dwivew(awx_dwivew);
MODUWE_DEVICE_TABWE(pci, awx_pci_tbw);
MODUWE_AUTHOW("Johannes Bewg <johannes@sipsowutions.net>");
MODUWE_AUTHOW("Quawcomm Cowpowation");
MODUWE_DESCWIPTION(
	"Quawcomm Athewos(W) AW816x/AW817x PCI-E Ethewnet Netwowk Dwivew");
MODUWE_WICENSE("GPW");
