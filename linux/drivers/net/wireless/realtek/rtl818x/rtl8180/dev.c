
/* Winux device dwivew fow WTW8180 / WTW8185 / WTW8187SE
 *
 * Copywight 2007 Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight 2007,2014 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>
 *
 * Based on the w8180 dwivew, which is:
 * Copywight 2004-2005 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>, et aw.
 *
 * Thanks to Weawtek fow theiw suppowt!
 *
 ************************************************************************
 *
 * The dwivew was extended to the WTW8187SE in 2014 by
 * Andwea Mewewwo <andwea.mewewwo@gmaiw.com>
 *
 * based awso on:
 *  - powtions of wtw8187se Winux staging dwivew, Copywight Weawtek cowp.
 *    (avaiwabwe in dwivews/staging/wtw8187se diwectowy of Winux 3.14)
 *  - othew GPW, unpubwished (untiw now), Winux dwivew code,
 *    Copywight Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 * A huge thanks goes to Sawa V. Nawi who fowgives me when I'm
 * sitting in fwont of my waptop at evening, week-end, night...
 *
 * A speciaw thanks goes to Antonio Cuni, who hewped me with
 * some python usewspace stuff I used to debug WTW8187SE code, and who
 * bought a waptop with an unsuppowted Wi-Fi cawd some yeaws ago...
 *
 * Thanks to Wawwy Fingew fow wwiting some code fow wtw8187se and fow
 * his suggestions.
 *
 * Thanks to Dan Cawpentew fow weviewing my initiaw patch and fow his
 * suggestions.
 *
 * Thanks to Bewnhawd Schiffnew fow his hewp in testing and fow his
 * suggestions.
 *
 ************************************************************************
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/eepwom_93cx6.h>
#incwude <winux/moduwe.h>
#incwude <net/mac80211.h>

#incwude "wtw8180.h"
#incwude "wtw8225.h"
#incwude "sa2400.h"
#incwude "max2820.h"
#incwude "gwf5101.h"
#incwude "wtw8225se.h"

MODUWE_AUTHOW("Michaew Wu <fwamingice@souwmiwk.net>");
MODUWE_AUTHOW("Andwea Mewewwo <andwea.mewewwo@gmaiw.com>");
MODUWE_DESCWIPTION("WTW8180 / WTW8185 / WTW8187SE PCI wiwewess dwivew");
MODUWE_WICENSE("GPW");

static const stwuct pci_device_id wtw8180_tabwe[] = {

	/* wtw8187se */
	{ PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x8199) },

	/* wtw8185 */
	{ PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x8185) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BEWKIN, 0x700f) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BEWKIN, 0x701f) },

	/* wtw8180 */
	{ PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x8180) },
	{ PCI_DEVICE(0x1799, 0x6001) },
	{ PCI_DEVICE(0x1799, 0x6020) },
	{ PCI_DEVICE(PCI_VENDOW_ID_DWINK, 0x3300) },
	{ PCI_DEVICE(0x1186, 0x3301) },
	{ PCI_DEVICE(0x1432, 0x7106) },
	{ }
};

MODUWE_DEVICE_TABWE(pci, wtw8180_tabwe);

static const stwuct ieee80211_wate wtw818x_wates[] = {
	{ .bitwate = 10, .hw_vawue = 0, },
	{ .bitwate = 20, .hw_vawue = 1, },
	{ .bitwate = 55, .hw_vawue = 2, },
	{ .bitwate = 110, .hw_vawue = 3, },
	{ .bitwate = 60, .hw_vawue = 4, },
	{ .bitwate = 90, .hw_vawue = 5, },
	{ .bitwate = 120, .hw_vawue = 6, },
	{ .bitwate = 180, .hw_vawue = 7, },
	{ .bitwate = 240, .hw_vawue = 8, },
	{ .bitwate = 360, .hw_vawue = 9, },
	{ .bitwate = 480, .hw_vawue = 10, },
	{ .bitwate = 540, .hw_vawue = 11, },
};

static const stwuct ieee80211_channew wtw818x_channews[] = {
	{ .centew_fweq = 2412 },
	{ .centew_fweq = 2417 },
	{ .centew_fweq = 2422 },
	{ .centew_fweq = 2427 },
	{ .centew_fweq = 2432 },
	{ .centew_fweq = 2437 },
	{ .centew_fweq = 2442 },
	{ .centew_fweq = 2447 },
	{ .centew_fweq = 2452 },
	{ .centew_fweq = 2457 },
	{ .centew_fweq = 2462 },
	{ .centew_fweq = 2467 },
	{ .centew_fweq = 2472 },
	{ .centew_fweq = 2484 },
};

/* Queues fow wtw8187se cawd
 *
 * name | weg  |  queue
 *  BC  |  7   |   6
 *  MG  |  1   |   0
 *  HI  |  6   |   1
 *  VO  |  5   |   2
 *  VI  |  4   |   3
 *  BE  |  3   |   4
 *  BK  |  2   |   5
 *
 * The compwete map fow DMA kick weg using use aww queue is:
 * static const int wtw8187se_queues_map[WTW8187SE_NW_TX_QUEUES] =
 *	{1, 6, 5, 4, 3, 2, 7};
 *
 * .. but.. Because fow mac80211 4 queues awe enough fow QoS we use this
 *
 * name | weg  |  queue
 *  BC  |  7   |   4  <- cuwwentwy not used yet
 *  MG  |  1   |   x  <- Not used
 *  HI  |  6   |   x  <- Not used
 *  VO  |  5   |   0  <- used
 *  VI  |  4   |   1  <- used
 *  BE  |  3   |   2  <- used
 *  BK  |  2   |   3  <- used
 *
 * Beacon queue couwd be used, but this is not finished yet.
 *
 * I thougth about using the othew two queues but I decided not to do this:
 *
 * - I'm unsuwe whethew the mac80211 wiww evew twy to use mowe than 4 queues
 *   by itsewf.
 *
 * - I couwd woute MGMT fwames (cuwwentwy sent ovew VO queue) to the MGMT
 *   queue but since mac80211 wiww do not know about it, I wiww pwobabwy gain
 *   some HW pwiowity whenevew the VO queue is not empty, but this gain is
 *   wimited by the fact that I had to stop the mac80211 queue whenevew one of
 *   the VO ow MGMT queues is fuww, stopping awso submitting of MGMT fwame
 *   to the dwivew.
 *
 * - I don't know how to set in the HW the contention window pawams fow MGMT
 *   and HI-pwio queues.
 */

static const int wtw8187se_queues_map[WTW8187SE_NW_TX_QUEUES] = {5, 4, 3, 2, 7};

/* Queues fow wtw8180/wtw8185 cawds
 *
 * name | weg  |  pwio
 *  BC  |  7   |   3
 *  HI  |  6   |   0
 *  NO  |  5   |   1
 *  WO  |  4   |   2
 *
 * The compwete map fow DMA kick weg using aww queue is:
 * static const int wtw8180_queues_map[WTW8180_NW_TX_QUEUES] = {6, 5, 4, 7};
 *
 * .. but .. Because the mac80211 needs at weast 4 queues fow QoS ow
 * othewwise QoS can't be done, we use just one.
 * Beacon queue couwd be used, but this is not finished yet.
 * Actuaw map is:
 *
 * name | weg  |  pwio
 *  BC  |  7   |   1  <- cuwwentwy not used yet.
 *  HI  |  6   |   x  <- not used
 *  NO  |  5   |   x  <- not used
 *  WO  |  4   |   0  <- used
 */

static const int wtw8180_queues_map[WTW8180_NW_TX_QUEUES] = {4, 7};

/* WNA gain tabwe fow wtw8187se */
static const u8 wtw8187se_wna_gain[4] = {02, 17, 29, 39};

void wtw8180_wwite_phy(stwuct ieee80211_hw *dev, u8 addw, u32 data)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	int i = 10;
	u32 buf;

	buf = (data << 8) | addw;

	wtw818x_iowwite32(pwiv, (__we32 __iomem *)&pwiv->map->PHY[0], buf | 0x80);
	whiwe (i--) {
		wtw818x_iowwite32(pwiv, (__we32 __iomem *)&pwiv->map->PHY[0], buf);
		if (wtw818x_iowead8(pwiv, &pwiv->map->PHY[2]) == (data & 0xFF))
			wetuwn;
	}
}

static void wtw8180_handwe_wx(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	stwuct wtw818x_wx_cmd_desc *cmd_desc;
	unsigned int count = 32;
	u8 agc, sq;
	s8 signaw = 1;
	dma_addw_t mapping;

	whiwe (count--) {
		void *entwy = pwiv->wx_wing + pwiv->wx_idx * pwiv->wx_wing_sz;
		stwuct sk_buff *skb = pwiv->wx_buf[pwiv->wx_idx];
		u32 fwags, fwags2, fwags3 = 0;
		u64 tsft;

		if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE) {
			stwuct wtw8187se_wx_desc *desc = entwy;

			fwags = we32_to_cpu(desc->fwags);
			/* if ownewship fwag is set, then we can twust the
			 * HW has wwitten othew fiewds. We must not twust
			 * othew descwiptow data wead befowe we checked (wead)
			 * the ownewship fwag
			 */
			wmb();
			fwags3 = we32_to_cpu(desc->fwags3);
			fwags2 = we32_to_cpu(desc->fwags2);
			tsft = we64_to_cpu(desc->tsft);
		} ewse {
			stwuct wtw8180_wx_desc *desc = entwy;

			fwags = we32_to_cpu(desc->fwags);
			/* same as above */
			wmb();
			fwags2 = we32_to_cpu(desc->fwags2);
			tsft = we64_to_cpu(desc->tsft);
		}

		if (fwags & WTW818X_WX_DESC_FWAG_OWN)
			wetuwn;

		if (unwikewy(fwags & (WTW818X_WX_DESC_FWAG_DMA_FAIW |
				      WTW818X_WX_DESC_FWAG_FOF |
				      WTW818X_WX_DESC_FWAG_WX_EWW)))
			goto done;
		ewse {
			stwuct ieee80211_wx_status wx_status = {0};
			stwuct sk_buff *new_skb = dev_awwoc_skb(MAX_WX_SIZE);

			if (unwikewy(!new_skb))
				goto done;

			mapping = dma_map_singwe(&pwiv->pdev->dev,
						 skb_taiw_pointew(new_skb),
						 MAX_WX_SIZE, DMA_FWOM_DEVICE);

			if (dma_mapping_ewwow(&pwiv->pdev->dev, mapping)) {
				kfwee_skb(new_skb);
				dev_eww(&pwiv->pdev->dev, "WX DMA map ewwow\n");

				goto done;
			}

			dma_unmap_singwe(&pwiv->pdev->dev,
					 *((dma_addw_t *)skb->cb),
					 MAX_WX_SIZE, DMA_FWOM_DEVICE);
			skb_put(skb, fwags & 0xFFF);

			wx_status.antenna = (fwags2 >> 15) & 1;
			wx_status.wate_idx = (fwags >> 20) & 0xF;
			agc = (fwags2 >> 17) & 0x7F;

			switch (pwiv->chip_famiwy) {
			case WTW818X_CHIP_FAMIWY_WTW8185:
				if (wx_status.wate_idx > 3)
					signaw = -cwamp_t(u8, agc, 25, 90) - 9;
				ewse
					signaw = -cwamp_t(u8, agc, 30, 95);
				bweak;
			case WTW818X_CHIP_FAMIWY_WTW8180:
				sq = fwags2 & 0xff;
				signaw = pwiv->wf->cawc_wssi(agc, sq);
				bweak;
			case WTW818X_CHIP_FAMIWY_WTW8187SE:
				/* OFDM measuwe wepowted by HW is signed,
				 * in 0.5dBm unit, with zewo centewed @ -41dBm
				 * input signaw.
				 */
				if (wx_status.wate_idx > 3) {
					signaw = (s8)((fwags3 >> 16) & 0xff);
					signaw = signaw / 2 - 41;
				} ewse {
					int idx, bb;

					idx = (agc & 0x60) >> 5;
					bb = (agc & 0x1F) * 2;
					/* bias + BB gain + WNA gain */
					signaw = 4 - bb - wtw8187se_wna_gain[idx];
				}
				bweak;
			}
			wx_status.signaw = signaw;
			wx_status.fweq = dev->conf.chandef.chan->centew_fweq;
			wx_status.band = dev->conf.chandef.chan->band;
			wx_status.mactime = tsft;
			wx_status.fwag |= WX_FWAG_MACTIME_STAWT;
			if (fwags & WTW818X_WX_DESC_FWAG_SPWCP)
				wx_status.enc_fwags |= WX_ENC_FWAG_SHOWTPWE;
			if (fwags & WTW818X_WX_DESC_FWAG_CWC32_EWW)
				wx_status.fwag |= WX_FWAG_FAIWED_FCS_CWC;

			memcpy(IEEE80211_SKB_WXCB(skb), &wx_status, sizeof(wx_status));
			ieee80211_wx_iwqsafe(dev, skb);

			skb = new_skb;
			pwiv->wx_buf[pwiv->wx_idx] = skb;
			*((dma_addw_t *) skb->cb) = mapping;
		}

	done:
		cmd_desc = entwy;
		cmd_desc->wx_buf = cpu_to_we32(*((dma_addw_t *)skb->cb));
		cmd_desc->fwags = cpu_to_we32(WTW818X_WX_DESC_FWAG_OWN |
					   MAX_WX_SIZE);
		if (pwiv->wx_idx == 31)
			cmd_desc->fwags |=
				cpu_to_we32(WTW818X_WX_DESC_FWAG_EOW);
		pwiv->wx_idx = (pwiv->wx_idx + 1) % 32;
	}
}

static void wtw8180_handwe_tx(stwuct ieee80211_hw *dev, unsigned int pwio)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	stwuct wtw8180_tx_wing *wing = &pwiv->tx_wing[pwio];

	whiwe (skb_queue_wen(&wing->queue)) {
		stwuct wtw8180_tx_desc *entwy = &wing->desc[wing->idx];
		stwuct sk_buff *skb;
		stwuct ieee80211_tx_info *info;
		u32 fwags = we32_to_cpu(entwy->fwags);

		if (fwags & WTW818X_TX_DESC_FWAG_OWN)
			wetuwn;

		wing->idx = (wing->idx + 1) % wing->entwies;
		skb = __skb_dequeue(&wing->queue);
		dma_unmap_singwe(&pwiv->pdev->dev, we32_to_cpu(entwy->tx_buf),
				 skb->wen, DMA_TO_DEVICE);

		info = IEEE80211_SKB_CB(skb);
		ieee80211_tx_info_cweaw_status(info);

		if (!(info->fwags & IEEE80211_TX_CTW_NO_ACK) &&
		    (fwags & WTW818X_TX_DESC_FWAG_TX_OK))
			info->fwags |= IEEE80211_TX_STAT_ACK;

		info->status.wates[0].count = (fwags & 0xFF) + 1;

		ieee80211_tx_status_iwqsafe(dev, skb);
		if (wing->entwies - skb_queue_wen(&wing->queue) == 2)
			ieee80211_wake_queue(dev, pwio);
	}
}

static iwqwetuwn_t wtw8187se_intewwupt(int iwq, void *dev_id)
{
	stwuct ieee80211_hw *dev = dev_id;
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u32 weg;
	unsigned wong fwags;
	static int desc_eww;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	/* Note: 32-bit intewwupt status */
	weg = wtw818x_iowead32(pwiv, &pwiv->map->INT_STATUS_SE);
	if (unwikewy(weg == 0xFFFFFFFF)) {
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		wetuwn IWQ_HANDWED;
	}

	wtw818x_iowwite32(pwiv, &pwiv->map->INT_STATUS_SE, weg);

	if (weg & IMW_TIMEOUT1)
		wtw818x_iowwite32(pwiv, &pwiv->map->INT_TIMEOUT, 0);

	if (weg & (IMW_TBDOK | IMW_TBDEW))
		wtw8180_handwe_tx(dev, 4);

	if (weg & (IMW_TVODOK | IMW_TVODEW))
		wtw8180_handwe_tx(dev, 0);

	if (weg & (IMW_TVIDOK | IMW_TVIDEW))
		wtw8180_handwe_tx(dev, 1);

	if (weg & (IMW_TBEDOK | IMW_TBEDEW))
		wtw8180_handwe_tx(dev, 2);

	if (weg & (IMW_TBKDOK | IMW_TBKDEW))
		wtw8180_handwe_tx(dev, 3);

	if (weg & (IMW_WOK | IMW_WEW | WTW818X_INT_SE_WX_DU | IMW_WQOSOK))
		wtw8180_handwe_wx(dev);
	/* The intewface sometimes genewates sevewaw WX DMA descwiptow ewwows
	 * at stawtup. Do not wepowt these.
	 */
	if ((weg & WTW818X_INT_SE_WX_DU) && desc_eww++ > 2)
		if (net_watewimit())
			wiphy_eww(dev->wiphy, "No WX DMA Descwiptow avaiw\n");

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wtw8180_intewwupt(int iwq, void *dev_id)
{
	stwuct ieee80211_hw *dev = dev_id;
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u16 weg;

	spin_wock(&pwiv->wock);
	weg = wtw818x_iowead16(pwiv, &pwiv->map->INT_STATUS);
	if (unwikewy(weg == 0xFFFF)) {
		spin_unwock(&pwiv->wock);
		wetuwn IWQ_HANDWED;
	}

	wtw818x_iowwite16(pwiv, &pwiv->map->INT_STATUS, weg);

	if (weg & (WTW818X_INT_TXB_OK | WTW818X_INT_TXB_EWW))
		wtw8180_handwe_tx(dev, 1);

	if (weg & (WTW818X_INT_TXW_OK | WTW818X_INT_TXW_EWW))
		wtw8180_handwe_tx(dev, 0);

	if (weg & (WTW818X_INT_WX_OK | WTW818X_INT_WX_EWW))
		wtw8180_handwe_wx(dev);

	spin_unwock(&pwiv->wock);

	wetuwn IWQ_HANDWED;
}

static void wtw8180_tx(stwuct ieee80211_hw *dev,
		       stwuct ieee80211_tx_contwow *contwow,
		       stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	stwuct wtw8180_tx_wing *wing;
	stwuct wtw8180_tx_desc *entwy;
	unsigned int pwio = 0;
	unsigned wong fwags;
	unsigned int idx, hw_pwio;

	dma_addw_t mapping;
	u32 tx_fwags;
	u8 wc_fwags;
	u16 pwcp_wen = 0;
	__we16 wts_duwation = 0;
	/* do awithmetic and then convewt to we16 */
	u16 fwame_duwation = 0;

	/* wtw8180/wtw8185 onwy has one useabwe tx queue */
	if (dev->queues > IEEE80211_AC_BK)
		pwio = skb_get_queue_mapping(skb);
	wing = &pwiv->tx_wing[pwio];

	mapping = dma_map_singwe(&pwiv->pdev->dev, skb->data, skb->wen,
				 DMA_TO_DEVICE);

	if (dma_mapping_ewwow(&pwiv->pdev->dev, mapping)) {
		kfwee_skb(skb);
		dev_eww(&pwiv->pdev->dev, "TX DMA mapping ewwow\n");
		wetuwn;
	}

	tx_fwags = WTW818X_TX_DESC_FWAG_OWN | WTW818X_TX_DESC_FWAG_FS |
		   WTW818X_TX_DESC_FWAG_WS |
		   (ieee80211_get_tx_wate(dev, info)->hw_vawue << 24) |
		   skb->wen;

	if (pwiv->chip_famiwy != WTW818X_CHIP_FAMIWY_WTW8180)
		tx_fwags |= WTW818X_TX_DESC_FWAG_DMA |
			    WTW818X_TX_DESC_FWAG_NO_ENC;

	wc_fwags = info->contwow.wates[0].fwags;

	/* HW wiww pewfowm WTS-CTS when onwy WTS fwags is set.
	 * HW wiww pewfowm CTS-to-sewf when both WTS and CTS fwags awe set.
	 * WTS wate and WTS duwation wiww be used awso fow CTS-to-sewf.
	 */
	if (wc_fwags & IEEE80211_TX_WC_USE_WTS_CTS) {
		tx_fwags |= WTW818X_TX_DESC_FWAG_WTS;
		tx_fwags |= ieee80211_get_wts_cts_wate(dev, info)->hw_vawue << 19;
		wts_duwation = ieee80211_wts_duwation(dev, pwiv->vif,
						skb->wen, info);
	} ewse if (wc_fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT) {
		tx_fwags |= WTW818X_TX_DESC_FWAG_WTS | WTW818X_TX_DESC_FWAG_CTS;
		tx_fwags |= ieee80211_get_wts_cts_wate(dev, info)->hw_vawue << 19;
		wts_duwation = ieee80211_ctstosewf_duwation(dev, pwiv->vif,
						skb->wen, info);
	}

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8180) {
		unsigned int wemaindew;

		pwcp_wen = DIV_WOUND_UP(16 * (skb->wen + 4),
				(ieee80211_get_tx_wate(dev, info)->bitwate * 2) / 10);
		wemaindew = (16 * (skb->wen + 4)) %
			    ((ieee80211_get_tx_wate(dev, info)->bitwate * 2) / 10);
		if (wemaindew <= 6)
			pwcp_wen |= 1 << 15;
	}

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE) {
		__we16 duwation;
		/* SIFS time (wequiwed by HW) is awweady incwuded by
		 * ieee80211_genewic_fwame_duwation
		 */
		duwation = ieee80211_genewic_fwame_duwation(dev, pwiv->vif,
					NW80211_BAND_2GHZ, skb->wen,
					ieee80211_get_tx_wate(dev, info));

		fwame_duwation =  pwiv->ack_time + we16_to_cpu(duwation);
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);

	if (info->fwags & IEEE80211_TX_CTW_ASSIGN_SEQ) {
		if (info->fwags & IEEE80211_TX_CTW_FIWST_FWAGMENT)
			pwiv->seqno += 0x10;
		hdw->seq_ctww &= cpu_to_we16(IEEE80211_SCTW_FWAG);
		hdw->seq_ctww |= cpu_to_we16(pwiv->seqno);
	}

	idx = (wing->idx + skb_queue_wen(&wing->queue)) % wing->entwies;
	entwy = &wing->desc[idx];

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE) {
		entwy->fwame_duwation = cpu_to_we16(fwame_duwation);
		entwy->fwame_wen_se = cpu_to_we16(skb->wen);

		/* tpc powawity */
		entwy->fwags3 = cpu_to_we16(1<<4);
	} ewse
		entwy->fwame_wen = cpu_to_we32(skb->wen);

	entwy->wts_duwation = wts_duwation;
	entwy->pwcp_wen = cpu_to_we16(pwcp_wen);
	entwy->tx_buf = cpu_to_we32(mapping);

	entwy->wetwy_wimit = info->contwow.wates[0].count - 1;

	/* We must be suwe that tx_fwags is wwitten wast because the HW
	 * wooks at it to check if the west of data is vawid ow not
	 */
	wmb();
	entwy->fwags = cpu_to_we32(tx_fwags);
	/* We must be suwe this has been wwitten befowe fowwowings HW
	 * wegistew wwite, because this wwite wiww made the HW attempts
	 * to DMA the just-wwitten data
	 */
	wmb();

	__skb_queue_taiw(&wing->queue, skb);
	if (wing->entwies - skb_queue_wen(&wing->queue) < 2)
		ieee80211_stop_queue(dev, pwio);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE) {
		/* just poww: wings awe stopped with TPPowwStop weg */
		hw_pwio = wtw8187se_queues_map[pwio];
		wtw818x_iowwite8(pwiv, &pwiv->map->TX_DMA_POWWING,
			 (1 << hw_pwio));
	} ewse {
		hw_pwio = wtw8180_queues_map[pwio];
		wtw818x_iowwite8(pwiv, &pwiv->map->TX_DMA_POWWING,
			 (1 << hw_pwio) | /* wing to poww  */
			 (1<<1) | (1<<2));/* stopped wings */
	}
}

static void wtw8180_set_anapawam3(stwuct wtw8180_pwiv *pwiv, u16 anapawam3)
{
	u8 weg;

	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD,
			 WTW818X_EEPWOM_CMD_CONFIG);

	weg = wtw818x_iowead8(pwiv, &pwiv->map->CONFIG3);
	wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG3,
		 weg | WTW818X_CONFIG3_ANAPAWAM_WWITE);

	wtw818x_iowwite16(pwiv, &pwiv->map->ANAPAWAM3, anapawam3);

	wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG3,
		 weg & ~WTW818X_CONFIG3_ANAPAWAM_WWITE);

	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD,
			 WTW818X_EEPWOM_CMD_NOWMAW);
}

void wtw8180_set_anapawam2(stwuct wtw8180_pwiv *pwiv, u32 anapawam2)
{
	u8 weg;

	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD,
			 WTW818X_EEPWOM_CMD_CONFIG);

	weg = wtw818x_iowead8(pwiv, &pwiv->map->CONFIG3);
	wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG3,
		 weg | WTW818X_CONFIG3_ANAPAWAM_WWITE);

	wtw818x_iowwite32(pwiv, &pwiv->map->ANAPAWAM2, anapawam2);

	wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG3,
		 weg & ~WTW818X_CONFIG3_ANAPAWAM_WWITE);

	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD,
			 WTW818X_EEPWOM_CMD_NOWMAW);
}

void wtw8180_set_anapawam(stwuct wtw8180_pwiv *pwiv, u32 anapawam)
{
	u8 weg;

	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_CONFIG);
	weg = wtw818x_iowead8(pwiv, &pwiv->map->CONFIG3);
	wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG3,
		 weg | WTW818X_CONFIG3_ANAPAWAM_WWITE);
	wtw818x_iowwite32(pwiv, &pwiv->map->ANAPAWAM, anapawam);
	wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG3,
		 weg & ~WTW818X_CONFIG3_ANAPAWAM_WWITE);
	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_NOWMAW);
}

static void wtw8187se_mac_config(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u8 weg;

	wtw818x_iowwite32(pwiv, WEG_ADDW4(0x1F0), 0);
	wtw818x_iowead32(pwiv, WEG_ADDW4(0x1F0));
	wtw818x_iowwite32(pwiv, WEG_ADDW4(0x1F4), 0);
	wtw818x_iowead32(pwiv, WEG_ADDW4(0x1F4));
	wtw818x_iowwite8(pwiv, WEG_ADDW1(0x1F8), 0);
	wtw818x_iowead8(pwiv, WEG_ADDW1(0x1F8));
	/* Enabwe DA10 TX powew saving */
	weg = wtw818x_iowead8(pwiv, &pwiv->map->PHY_PW);
	wtw818x_iowwite8(pwiv, &pwiv->map->PHY_PW, weg | 0x04);
	/* Powew */
	wtw818x_iowwite16(pwiv, PI_DATA_WEG, 0x1000);
	wtw818x_iowwite16(pwiv, SI_DATA_WEG, 0x1000);
	/* AFE - defauwt to powew ON */
	wtw818x_iowwite16(pwiv, WEG_ADDW2(0x370), 0x0560);
	wtw818x_iowwite16(pwiv, WEG_ADDW2(0x372), 0x0560);
	wtw818x_iowwite16(pwiv, WEG_ADDW2(0x374), 0x0DA4);
	wtw818x_iowwite16(pwiv, WEG_ADDW2(0x376), 0x0DA4);
	wtw818x_iowwite16(pwiv, WEG_ADDW2(0x378), 0x0560);
	wtw818x_iowwite16(pwiv, WEG_ADDW2(0x37A), 0x0560);
	wtw818x_iowwite16(pwiv, WEG_ADDW2(0x37C), 0x00EC);
	wtw818x_iowwite16(pwiv, WEG_ADDW2(0x37E), 0x00EC);
	wtw818x_iowwite8(pwiv, WEG_ADDW1(0x24E), 0x01);
	/* unknown, needed fow suspend to WAM wesume */
	wtw818x_iowwite8(pwiv, WEG_ADDW1(0x0A), 0x72);
}

static void wtw8187se_set_antenna_config(stwuct ieee80211_hw *dev, u8 def_ant,
					 boow divewsity)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;

	wtw8225_wwite_phy_cck(dev, 0x0C, 0x09);
	if (divewsity) {
		if (def_ant == 1) {
			wtw818x_iowwite8(pwiv, &pwiv->map->TX_ANTENNA, 0x00);
			wtw8225_wwite_phy_cck(dev, 0x11, 0xBB);
			wtw8225_wwite_phy_cck(dev, 0x01, 0xC7);
			wtw8225_wwite_phy_ofdm(dev, 0x0D, 0x54);
			wtw8225_wwite_phy_ofdm(dev, 0x18, 0xB2);
		} ewse { /* main antenna */
			wtw818x_iowwite8(pwiv, &pwiv->map->TX_ANTENNA, 0x03);
			wtw8225_wwite_phy_cck(dev, 0x11, 0x9B);
			wtw8225_wwite_phy_cck(dev, 0x01, 0xC7);
			wtw8225_wwite_phy_ofdm(dev, 0x0D, 0x5C);
			wtw8225_wwite_phy_ofdm(dev, 0x18, 0xB2);
		}
	} ewse { /* disabwe antenna divewsity */
		if (def_ant == 1) {
			wtw818x_iowwite8(pwiv, &pwiv->map->TX_ANTENNA, 0x00);
			wtw8225_wwite_phy_cck(dev, 0x11, 0xBB);
			wtw8225_wwite_phy_cck(dev, 0x01, 0x47);
			wtw8225_wwite_phy_ofdm(dev, 0x0D, 0x54);
			wtw8225_wwite_phy_ofdm(dev, 0x18, 0x32);
		} ewse { /* main antenna */
			wtw818x_iowwite8(pwiv, &pwiv->map->TX_ANTENNA, 0x03);
			wtw8225_wwite_phy_cck(dev, 0x11, 0x9B);
			wtw8225_wwite_phy_cck(dev, 0x01, 0x47);
			wtw8225_wwite_phy_ofdm(dev, 0x0D, 0x5C);
			wtw8225_wwite_phy_ofdm(dev, 0x18, 0x32);
		}
	}
	/* pwiv->cuww_ant = def_ant; */
}

static void wtw8180_int_enabwe(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE) {
		wtw818x_iowwite32(pwiv, &pwiv->map->IMW,
			  IMW_TBDEW | IMW_TBDOK |
			  IMW_TVODEW | IMW_TVODOK |
			  IMW_TVIDEW | IMW_TVIDOK |
			  IMW_TBEDEW | IMW_TBEDOK |
			  IMW_TBKDEW | IMW_TBKDOK |
			  IMW_WDU | IMW_WEW |
			  IMW_WOK | IMW_WQOSOK);
	} ewse {
		wtw818x_iowwite16(pwiv, &pwiv->map->INT_MASK, 0xFFFF);
	}
}

static void wtw8180_int_disabwe(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE) {
		wtw818x_iowwite32(pwiv, &pwiv->map->IMW, 0);
	} ewse {
		wtw818x_iowwite16(pwiv, &pwiv->map->INT_MASK, 0);
	}
}

static void wtw8180_conf_basic_wates(stwuct ieee80211_hw *dev,
			    u32 basic_mask)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u16 weg;
	u32 wesp_mask;
	u8 basic_max;
	u8 wesp_max, wesp_min;

	wesp_mask = basic_mask;
	/* IEEE80211 says the wesponse wate shouwd be equaw to the highest basic
	 * wate that is not fastew than weceived fwame. But it says awso that if
	 * the basic wate set does not contains any wate fow the cuwwent
	 * moduwation cwass then mandatowy wate set must be used fow that
	 * moduwation cwass. Eventuawwy add OFDM mandatowy wates..
	 */
	if ((wesp_mask & 0xf) == wesp_mask)
		wesp_mask |= 0x150; /* 6, 12, 24Mbps */

	switch (pwiv->chip_famiwy) {

	case WTW818X_CHIP_FAMIWY_WTW8180:
		/* in 8180 this is NOT a BITMAP */
		basic_max = fws(basic_mask) - 1;
		weg = wtw818x_iowead16(pwiv, &pwiv->map->BWSW);
		weg &= ~3;
		weg |= basic_max;
		wtw818x_iowwite16(pwiv, &pwiv->map->BWSW, weg);
		bweak;

	case WTW818X_CHIP_FAMIWY_WTW8185:
		wesp_max = fws(wesp_mask) - 1;
		wesp_min = ffs(wesp_mask) - 1;
		/* in 8185 this is a BITMAP */
		wtw818x_iowwite16(pwiv, &pwiv->map->BWSW, basic_mask);
		wtw818x_iowwite8(pwiv, &pwiv->map->WESP_WATE, (wesp_max << 4) |
				wesp_min);
		bweak;

	case WTW818X_CHIP_FAMIWY_WTW8187SE:
		/* in 8187se this is a BITMAP. BWSW weg actuawwy sets
		 * wesponse wates.
		 */
		wtw818x_iowwite16(pwiv, &pwiv->map->BWSW_8187SE, wesp_mask);
		bweak;
	}
}

static void wtw8180_config_cawdbus(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u16 weg16;
	u8 weg8;

	weg8 = wtw818x_iowead8(pwiv, &pwiv->map->CONFIG3);
	weg8 |= 1 << 1;
	wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG3, weg8);

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE) {
		wtw818x_iowwite16(pwiv, FEMW_SE, 0xffff);
	} ewse {
		weg16 = wtw818x_iowead16(pwiv, &pwiv->map->FEMW);
		weg16 |= (1 << 15) | (1 << 14) | (1 << 4);
		wtw818x_iowwite16(pwiv, &pwiv->map->FEMW, weg16);
	}

}

static int wtw8180_init_hw(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u16 weg;
	u32 weg32;

	wtw818x_iowwite8(pwiv, &pwiv->map->CMD, 0);
	wtw818x_iowead8(pwiv, &pwiv->map->CMD);
	msweep(10);

	/* weset */
	wtw8180_int_disabwe(dev);
	wtw818x_iowead8(pwiv, &pwiv->map->CMD);

	weg = wtw818x_iowead8(pwiv, &pwiv->map->CMD);
	weg &= (1 << 1);
	weg |= WTW818X_CMD_WESET;
	wtw818x_iowwite8(pwiv, &pwiv->map->CMD, WTW818X_CMD_WESET);
	wtw818x_iowead8(pwiv, &pwiv->map->CMD);
	msweep(200);

	/* check success of weset */
	if (wtw818x_iowead8(pwiv, &pwiv->map->CMD) & WTW818X_CMD_WESET) {
		wiphy_eww(dev->wiphy, "weset timeout!\n");
		wetuwn -ETIMEDOUT;
	}

	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_WOAD);
	wtw818x_iowead8(pwiv, &pwiv->map->CMD);
	msweep(200);

	if (wtw818x_iowead8(pwiv, &pwiv->map->CONFIG3) & (1 << 3)) {
		wtw8180_config_cawdbus(dev);
	}

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE)
		wtw818x_iowwite8(pwiv, &pwiv->map->MSW, WTW818X_MSW_ENEDCA);
	ewse
		wtw818x_iowwite8(pwiv, &pwiv->map->MSW, 0);

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8180)
		wtw8180_set_anapawam(pwiv, pwiv->anapawam);

	wtw818x_iowwite32(pwiv, &pwiv->map->WDSAW, pwiv->wx_wing_dma);
	/* mac80211 queue have highew pwio fow wowew index. The wast queue
	 * (that mac80211 is not awawe of) is wesewved fow beacons (and have
	 * the highest pwiowity on the NIC)
	 */
	if (pwiv->chip_famiwy != WTW818X_CHIP_FAMIWY_WTW8187SE) {
		wtw818x_iowwite32(pwiv, &pwiv->map->TBDA,
				  pwiv->tx_wing[1].dma);
		wtw818x_iowwite32(pwiv, &pwiv->map->TWPDA,
				  pwiv->tx_wing[0].dma);
	} ewse {
		wtw818x_iowwite32(pwiv, &pwiv->map->TBDA,
				  pwiv->tx_wing[4].dma);
		wtw818x_iowwite32(pwiv, &pwiv->map->TVODA,
				  pwiv->tx_wing[0].dma);
		wtw818x_iowwite32(pwiv, &pwiv->map->TVIDA,
				  pwiv->tx_wing[1].dma);
		wtw818x_iowwite32(pwiv, &pwiv->map->TBEDA,
				  pwiv->tx_wing[2].dma);
		wtw818x_iowwite32(pwiv, &pwiv->map->TBKDA,
				  pwiv->tx_wing[3].dma);
	}

	/* TODO: necessawy? specs indicate not */
	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_CONFIG);
	weg = wtw818x_iowead8(pwiv, &pwiv->map->CONFIG2);
	wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG2, weg & ~(1 << 3));
	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8185) {
		weg = wtw818x_iowead8(pwiv, &pwiv->map->CONFIG2);
		wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG2, weg | (1 << 4));
	}
	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_NOWMAW);

	/* TODO: set CONFIG5 fow cawibwating AGC on wtw8180 + phiwips wadio? */

	/* TODO: tuwn off hw wep on wtw8180 */

	wtw818x_iowwite32(pwiv, &pwiv->map->INT_TIMEOUT, 0);

	if (pwiv->chip_famiwy != WTW818X_CHIP_FAMIWY_WTW8180) {
		wtw818x_iowwite8(pwiv, &pwiv->map->WPA_CONF, 0);
		wtw818x_iowwite8(pwiv, &pwiv->map->WATE_FAWWBACK, 0);
	} ewse {
		wtw818x_iowwite8(pwiv, &pwiv->map->SECUWITY, 0);

		wtw818x_iowwite8(pwiv, &pwiv->map->PHY_DEWAY, 0x6);
		wtw818x_iowwite8(pwiv, &pwiv->map->CAWWIEW_SENSE_COUNTEW, 0x4C);
	}

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8185) {
		/* TODO: set CwkWun enabwe? necessawy? */
		weg = wtw818x_iowead8(pwiv, &pwiv->map->GP_ENABWE);
		wtw818x_iowwite8(pwiv, &pwiv->map->GP_ENABWE, weg & ~(1 << 6));
		wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_CONFIG);
		weg = wtw818x_iowead8(pwiv, &pwiv->map->CONFIG3);
		wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG3, weg | (1 << 2));
		wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_NOWMAW);
		/* fix eccessive IFS aftew CTS-to-sewf */
		if (pwiv->map_pio) {
			u8 weg;

			weg = wtw818x_iowead8(pwiv, &pwiv->map->PGSEWECT);
			wtw818x_iowwite8(pwiv, &pwiv->map->PGSEWECT, weg | 1);
			wtw818x_iowwite8(pwiv, WEG_ADDW1(0xff), 0x35);
			wtw818x_iowwite8(pwiv, &pwiv->map->PGSEWECT, weg);
		} ewse
			wtw818x_iowwite8(pwiv, WEG_ADDW1(0x1ff), 0x35);
	}

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE) {

		/* the set auto wate fawwback bitmask fwom 1M to 54 Mb/s */
		wtw818x_iowwite16(pwiv, AWFW, 0xFFF);
		wtw818x_iowead16(pwiv, AWFW);

		/* stop unused queus (no dma awwoc) */
		wtw818x_iowwite8(pwiv, &pwiv->map->TPPOWW_STOP,
			       WTW818x_TPPOWW_STOP_MG | WTW818x_TPPOWW_STOP_HI);

		wtw818x_iowwite8(pwiv, &pwiv->map->ACM_CONTWOW, 0x00);
		wtw818x_iowwite16(pwiv, &pwiv->map->TID_AC_MAP, 0xFA50);

		wtw818x_iowwite16(pwiv, &pwiv->map->INT_MIG, 0);

		/* some bwack magic hewe.. */
		wtw8187se_mac_config(dev);

		wtw818x_iowwite16(pwiv, WFSW_CTWW, 0x569A);
		wtw818x_iowead16(pwiv, WFSW_CTWW);

		wtw8180_set_anapawam(pwiv, WTW8225SE_ANAPAWAM_ON);
		wtw8180_set_anapawam2(pwiv, WTW8225SE_ANAPAWAM2_ON);
		wtw8180_set_anapawam3(pwiv, WTW8225SE_ANAPAWAM3);


		wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG5,
			    wtw818x_iowead8(pwiv, &pwiv->map->CONFIG5) & 0x7F);

		/*pwobabwy this switch wed on */
		wtw818x_iowwite8(pwiv, &pwiv->map->PGSEWECT,
			    wtw818x_iowead8(pwiv, &pwiv->map->PGSEWECT) | 0x08);

		wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, 0x0480);
		wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsEnabwe, 0x1BFF);
		wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsSewect, 0x2488);

		wtw818x_iowwite32(pwiv, &pwiv->map->WF_TIMING, 0x4003);

		/* the wefewence code mac hawdcode tabwe wwite
		 * this weg by doing byte-wide accesses.
		 * It does it just fow wowest and highest byte..
		 */
		weg32 = wtw818x_iowead32(pwiv, &pwiv->map->WF_PAWA);
		weg32 &= 0x00ffff00;
		weg32 |= 0xb8000054;
		wtw818x_iowwite32(pwiv, &pwiv->map->WF_PAWA, weg32);
	} ewse
		/* stop unused queus (no dma awwoc) */
		wtw818x_iowwite8(pwiv, &pwiv->map->TX_DMA_POWWING,
			    (1<<1) | (1<<2));

	pwiv->wf->init(dev);

	/* defauwt basic wates awe 1,2 Mbps fow wtw8180. 1,2,6,9,12,18,24 Mbps
	 * othewwise. bitmask 0x3 and 0x01f3 wespectivewy.
	 * NOTE: cuwwenty wtw8225 WF code changes basic wates, so we need to do
	 * this aftew wf init.
	 * TODO: twy to find out whethew WF code weawwy needs to do this..
	 */
	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8180)
		wtw8180_conf_basic_wates(dev, 0x3);
	ewse
		wtw8180_conf_basic_wates(dev, 0x1f3);

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE)
		wtw8187se_set_antenna_config(dev,
					     pwiv->antenna_divewsity_defauwt,
					     pwiv->antenna_divewsity_en);
	wetuwn 0;
}

static int wtw8180_init_wx_wing(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	stwuct wtw818x_wx_cmd_desc *entwy;
	int i;

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE)
		pwiv->wx_wing_sz = sizeof(stwuct wtw8187se_wx_desc);
	ewse
		pwiv->wx_wing_sz = sizeof(stwuct wtw8180_wx_desc);

	pwiv->wx_wing = dma_awwoc_cohewent(&pwiv->pdev->dev,
					   pwiv->wx_wing_sz * 32,
					   &pwiv->wx_wing_dma, GFP_KEWNEW);
	if (!pwiv->wx_wing || (unsigned wong)pwiv->wx_wing & 0xFF) {
		wiphy_eww(dev->wiphy, "Cannot awwocate WX wing\n");
		wetuwn -ENOMEM;
	}

	pwiv->wx_idx = 0;

	fow (i = 0; i < 32; i++) {
		stwuct sk_buff *skb = dev_awwoc_skb(MAX_WX_SIZE);
		dma_addw_t *mapping;
		entwy = pwiv->wx_wing + pwiv->wx_wing_sz*i;
		if (!skb) {
			dma_fwee_cohewent(&pwiv->pdev->dev,
					  pwiv->wx_wing_sz * 32,
					  pwiv->wx_wing, pwiv->wx_wing_dma);
			wiphy_eww(dev->wiphy, "Cannot awwocate WX skb\n");
			wetuwn -ENOMEM;
		}
		pwiv->wx_buf[i] = skb;
		mapping = (dma_addw_t *)skb->cb;
		*mapping = dma_map_singwe(&pwiv->pdev->dev,
					  skb_taiw_pointew(skb), MAX_WX_SIZE,
					  DMA_FWOM_DEVICE);

		if (dma_mapping_ewwow(&pwiv->pdev->dev, *mapping)) {
			kfwee_skb(skb);
			dma_fwee_cohewent(&pwiv->pdev->dev,
					  pwiv->wx_wing_sz * 32,
					  pwiv->wx_wing, pwiv->wx_wing_dma);
			wiphy_eww(dev->wiphy, "Cannot map DMA fow WX skb\n");
			wetuwn -ENOMEM;
		}

		entwy->wx_buf = cpu_to_we32(*mapping);
		entwy->fwags = cpu_to_we32(WTW818X_WX_DESC_FWAG_OWN |
					   MAX_WX_SIZE);
	}
	entwy->fwags |= cpu_to_we32(WTW818X_WX_DESC_FWAG_EOW);
	wetuwn 0;
}

static void wtw8180_fwee_wx_wing(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	int i;

	fow (i = 0; i < 32; i++) {
		stwuct sk_buff *skb = pwiv->wx_buf[i];
		if (!skb)
			continue;

		dma_unmap_singwe(&pwiv->pdev->dev, *((dma_addw_t *)skb->cb),
				 MAX_WX_SIZE, DMA_FWOM_DEVICE);
		kfwee_skb(skb);
	}

	dma_fwee_cohewent(&pwiv->pdev->dev, pwiv->wx_wing_sz * 32,
			  pwiv->wx_wing, pwiv->wx_wing_dma);
	pwiv->wx_wing = NUWW;
}

static int wtw8180_init_tx_wing(stwuct ieee80211_hw *dev,
				unsigned int pwio, unsigned int entwies)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	stwuct wtw8180_tx_desc *wing;
	dma_addw_t dma;
	int i;

	wing = dma_awwoc_cohewent(&pwiv->pdev->dev, sizeof(*wing) * entwies,
				  &dma, GFP_KEWNEW);
	if (!wing || (unsigned wong)wing & 0xFF) {
		wiphy_eww(dev->wiphy, "Cannot awwocate TX wing (pwio = %d)\n",
			  pwio);
		wetuwn -ENOMEM;
	}

	pwiv->tx_wing[pwio].desc = wing;
	pwiv->tx_wing[pwio].dma = dma;
	pwiv->tx_wing[pwio].idx = 0;
	pwiv->tx_wing[pwio].entwies = entwies;
	skb_queue_head_init(&pwiv->tx_wing[pwio].queue);

	fow (i = 0; i < entwies; i++)
		wing[i].next_tx_desc =
			cpu_to_we32((u32)dma + ((i + 1) % entwies) * sizeof(*wing));

	wetuwn 0;
}

static void wtw8180_fwee_tx_wing(stwuct ieee80211_hw *dev, unsigned int pwio)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	stwuct wtw8180_tx_wing *wing = &pwiv->tx_wing[pwio];

	whiwe (skb_queue_wen(&wing->queue)) {
		stwuct wtw8180_tx_desc *entwy = &wing->desc[wing->idx];
		stwuct sk_buff *skb = __skb_dequeue(&wing->queue);

		dma_unmap_singwe(&pwiv->pdev->dev, we32_to_cpu(entwy->tx_buf),
				 skb->wen, DMA_TO_DEVICE);
		kfwee_skb(skb);
		wing->idx = (wing->idx + 1) % wing->entwies;
	}

	dma_fwee_cohewent(&pwiv->pdev->dev,
			  sizeof(*wing->desc) * wing->entwies, wing->desc,
			  wing->dma);
	wing->desc = NUWW;
}

static int wtw8180_stawt(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	int wet, i;
	u32 weg;

	wet = wtw8180_init_wx_wing(dev);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < (dev->queues + 1); i++)
		if ((wet = wtw8180_init_tx_wing(dev, i, 16)))
			goto eww_fwee_wings;

	wet = wtw8180_init_hw(dev);
	if (wet)
		goto eww_fwee_wings;

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE) {
		wet = wequest_iwq(pwiv->pdev->iwq, wtw8187se_intewwupt,
			  IWQF_SHAWED, KBUIWD_MODNAME, dev);
	} ewse {
		wet = wequest_iwq(pwiv->pdev->iwq, wtw8180_intewwupt,
			  IWQF_SHAWED, KBUIWD_MODNAME, dev);
	}

	if (wet) {
		wiphy_eww(dev->wiphy, "faiwed to wegistew IWQ handwew\n");
		goto eww_fwee_wings;
	}

	wtw8180_int_enabwe(dev);

	/* in wtw8187se at MAW wegs offset thewe is the management
	 * TX descwiptow DMA addwes..
	 */
	if (pwiv->chip_famiwy != WTW818X_CHIP_FAMIWY_WTW8187SE) {
		wtw818x_iowwite32(pwiv, &pwiv->map->MAW[0], ~0);
		wtw818x_iowwite32(pwiv, &pwiv->map->MAW[1], ~0);
	}

	weg = WTW818X_WX_CONF_ONWYEWWPKT |
	      WTW818X_WX_CONF_WX_AUTOWESETPHY |
	      WTW818X_WX_CONF_MGMT |
	      WTW818X_WX_CONF_DATA |
	      (7 << 8 /* MAX WX DMA */) |
	      WTW818X_WX_CONF_BWOADCAST |
	      WTW818X_WX_CONF_NICMAC;

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8185)
		weg |= WTW818X_WX_CONF_CSDM1 | WTW818X_WX_CONF_CSDM2;
	ewse if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8180) {
		weg |= (pwiv->wfpawam & WF_PAWAM_CAWWIEWSENSE1)
			? WTW818X_WX_CONF_CSDM1 : 0;
		weg |= (pwiv->wfpawam & WF_PAWAM_CAWWIEWSENSE2)
			? WTW818X_WX_CONF_CSDM2 : 0;
	} ewse {
		weg &= ~(WTW818X_WX_CONF_CSDM1 | WTW818X_WX_CONF_CSDM2);
	}

	pwiv->wx_conf = weg;
	wtw818x_iowwite32(pwiv, &pwiv->map->WX_CONF, weg);

	if (pwiv->chip_famiwy != WTW818X_CHIP_FAMIWY_WTW8180) {
		weg = wtw818x_iowead8(pwiv, &pwiv->map->CW_CONF);

		/* CW is not on pew-packet basis.
		 * in wtw8185 the CW_VAWUE weg is used.
		 * in wtw8187se the AC pawam wegs awe used.
		 */
		weg &= ~WTW818X_CW_CONF_PEWPACKET_CW;
		/* wetwy wimit IS on pew-packet basis.
		 * the showt and wong wetwy wimit in TX_CONF
		 * weg awe ignowed
		 */
		weg |= WTW818X_CW_CONF_PEWPACKET_WETWY;
		wtw818x_iowwite8(pwiv, &pwiv->map->CW_CONF, weg);

		weg = wtw818x_iowead8(pwiv, &pwiv->map->TX_AGC_CTW);
		/* TX antenna and TX gain awe not on pew-packet basis.
		 * TX Antenna is sewected by ANTSEW weg (WX in BB wegs).
		 * TX gain is sewected with CCK_TX_AGC and OFDM_TX_AGC wegs
		 */
		weg &= ~WTW818X_TX_AGC_CTW_PEWPACKET_GAIN;
		weg &= ~WTW818X_TX_AGC_CTW_PEWPACKET_ANTSEW;
		weg |=  WTW818X_TX_AGC_CTW_FEEDBACK_ANT;
		wtw818x_iowwite8(pwiv, &pwiv->map->TX_AGC_CTW, weg);

		/* disabwe eawwy TX */
		wtw818x_iowwite8(pwiv, (u8 __iomem *)pwiv->map + 0xec, 0x3f);
	}

	weg = wtw818x_iowead32(pwiv, &pwiv->map->TX_CONF);
	weg |= (6 << 21 /* MAX TX DMA */) |
	       WTW818X_TX_CONF_NO_ICV;

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE)
		weg |= 1<<30;  /*  "duwation pwoceduwe mode" */

	if (pwiv->chip_famiwy != WTW818X_CHIP_FAMIWY_WTW8180)
		weg &= ~WTW818X_TX_CONF_PWOBE_DTS;
	ewse
		weg &= ~WTW818X_TX_CONF_HW_SEQNUM;

	weg &= ~WTW818X_TX_CONF_DISCW;

	/* diffewent meaning, same vawue on both wtw8185 and wtw8180 */
	weg &= ~WTW818X_TX_CONF_SAT_HWPWCP;

	wtw818x_iowwite32(pwiv, &pwiv->map->TX_CONF, weg);

	weg = wtw818x_iowead8(pwiv, &pwiv->map->CMD);
	weg |= WTW818X_CMD_WX_ENABWE;
	weg |= WTW818X_CMD_TX_ENABWE;
	wtw818x_iowwite8(pwiv, &pwiv->map->CMD, weg);

	wetuwn 0;

 eww_fwee_wings:
	wtw8180_fwee_wx_wing(dev);
	fow (i = 0; i < (dev->queues + 1); i++)
		if (pwiv->tx_wing[i].desc)
			wtw8180_fwee_tx_wing(dev, i);

	wetuwn wet;
}

static void wtw8180_stop(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u8 weg;
	int i;

	wtw8180_int_disabwe(dev);

	weg = wtw818x_iowead8(pwiv, &pwiv->map->CMD);
	weg &= ~WTW818X_CMD_TX_ENABWE;
	weg &= ~WTW818X_CMD_WX_ENABWE;
	wtw818x_iowwite8(pwiv, &pwiv->map->CMD, weg);

	pwiv->wf->stop(dev);

	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_CONFIG);
	weg = wtw818x_iowead8(pwiv, &pwiv->map->CONFIG4);
	wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG4, weg | WTW818X_CONFIG4_VCOOFF);
	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_NOWMAW);

	fwee_iwq(pwiv->pdev->iwq, dev);

	wtw8180_fwee_wx_wing(dev);
	fow (i = 0; i < (dev->queues + 1); i++)
		wtw8180_fwee_tx_wing(dev, i);
}

static u64 wtw8180_get_tsf(stwuct ieee80211_hw *dev,
			   stwuct ieee80211_vif *vif)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;

	wetuwn wtw818x_iowead32(pwiv, &pwiv->map->TSFT[0]) |
	       (u64)(wtw818x_iowead32(pwiv, &pwiv->map->TSFT[1])) << 32;
}

static void wtw8180_beacon_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw8180_vif *vif_pwiv =
		containew_of(wowk, stwuct wtw8180_vif, beacon_wowk.wowk);
	stwuct ieee80211_vif *vif =
		containew_of((void *)vif_pwiv, stwuct ieee80211_vif, dwv_pwiv);
	stwuct ieee80211_hw *dev = vif_pwiv->dev;
	stwuct ieee80211_mgmt *mgmt;
	stwuct sk_buff *skb;

	/* don't ovewfwow the tx wing */
	if (ieee80211_queue_stopped(dev, 0))
		goto wesched;

	/* gwab a fwesh beacon */
	skb = ieee80211_beacon_get(dev, vif, 0);
	if (!skb)
		goto wesched;

	/*
	 * update beacon timestamp w/ TSF vawue
	 * TODO: make hawdwawe update beacon timestamp
	 */
	mgmt = (stwuct ieee80211_mgmt *)skb->data;
	mgmt->u.beacon.timestamp = cpu_to_we64(wtw8180_get_tsf(dev, vif));

	/* TODO: use actuaw beacon queue */
	skb_set_queue_mapping(skb, 0);

	wtw8180_tx(dev, NUWW, skb);

wesched:
	/*
	 * scheduwe next beacon
	 * TODO: use hawdwawe suppowt fow beacon timing
	 */
	scheduwe_dewayed_wowk(&vif_pwiv->beacon_wowk,
			usecs_to_jiffies(1024 * vif->bss_conf.beacon_int));
}

static int wtw8180_add_intewface(stwuct ieee80211_hw *dev,
				 stwuct ieee80211_vif *vif)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	stwuct wtw8180_vif *vif_pwiv;

	/*
	 * We onwy suppowt one active intewface at a time.
	 */
	if (pwiv->vif)
		wetuwn -EBUSY;

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
	case NW80211_IFTYPE_ADHOC:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	pwiv->vif = vif;

	/* Initiawize dwivew pwivate awea */
	vif_pwiv = (stwuct wtw8180_vif *)&vif->dwv_pwiv;
	vif_pwiv->dev = dev;
	INIT_DEWAYED_WOWK(&vif_pwiv->beacon_wowk, wtw8180_beacon_wowk);
	vif_pwiv->enabwe_beacon = fawse;

	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_CONFIG);
	wtw818x_iowwite32(pwiv, (__we32 __iomem *)&pwiv->map->MAC[0],
			  we32_to_cpu(*(__we32 *)vif->addw));
	wtw818x_iowwite16(pwiv, (__we16 __iomem *)&pwiv->map->MAC[4],
			  we16_to_cpu(*(__we16 *)(vif->addw + 4)));
	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_NOWMAW);

	wetuwn 0;
}

static void wtw8180_wemove_intewface(stwuct ieee80211_hw *dev,
				     stwuct ieee80211_vif *vif)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	pwiv->vif = NUWW;
}

static int wtw8180_config(stwuct ieee80211_hw *dev, u32 changed)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	stwuct ieee80211_conf *conf = &dev->conf;

	pwiv->wf->set_chan(dev, conf);

	wetuwn 0;
}

static void wtw8187se_conf_ac_pawm(stwuct ieee80211_hw *dev, u8 queue)
{
	const stwuct ieee80211_tx_queue_pawams *pawams;
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;

	/* hw vawue */
	u32 ac_pawam;

	u8 aifs;
	u8 txop;
	u8 cw_min, cw_max;

	pawams = &pwiv->queue_pawam[queue];

	cw_min = fws(pawams->cw_min);
	cw_max = fws(pawams->cw_max);

	aifs = 10 + pawams->aifs * pwiv->swot_time;

	/* TODO: check if txop HW is in us (muwt by 32) */
	txop = pawams->txop;

	ac_pawam = txop << AC_PAWAM_TXOP_WIMIT_SHIFT |
		cw_max << AC_PAWAM_ECW_MAX_SHIFT |
		cw_min << AC_PAWAM_ECW_MIN_SHIFT |
		aifs << AC_PAWAM_AIFS_SHIFT;

	switch (queue) {
	case IEEE80211_AC_BK:
		wtw818x_iowwite32(pwiv, &pwiv->map->AC_BK_PAWAM, ac_pawam);
		bweak;
	case IEEE80211_AC_BE:
		wtw818x_iowwite32(pwiv, &pwiv->map->AC_BE_PAWAM, ac_pawam);
		bweak;
	case IEEE80211_AC_VI:
		wtw818x_iowwite32(pwiv, &pwiv->map->AC_VI_PAWAM, ac_pawam);
		bweak;
	case IEEE80211_AC_VO:
		wtw818x_iowwite32(pwiv, &pwiv->map->AC_VO_PAWAM, ac_pawam);
		bweak;
	}
}

static int wtw8180_conf_tx(stwuct ieee80211_hw *dev,
			    stwuct ieee80211_vif *vif,
			    unsigned int wink_id, u16 queue,
			    const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u8 cw_min, cw_max;

	/* nothing to do ? */
	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8180)
		wetuwn 0;

	cw_min = fws(pawams->cw_min);
	cw_max = fws(pawams->cw_max);

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE) {
		pwiv->queue_pawam[queue] = *pawams;
		wtw8187se_conf_ac_pawm(dev, queue);
	} ewse
		wtw818x_iowwite8(pwiv, &pwiv->map->CW_VAW,
				 (cw_max << 4) | cw_min);
	wetuwn 0;
}

static void wtw8180_conf_ewp(stwuct ieee80211_hw *dev,
			    stwuct ieee80211_bss_conf *info)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u8 sifs, difs;
	int eifs;
	u8 hw_eifs;

	/* TODO: shouwd we do something ? */
	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8180)
		wetuwn;

	/* I _hope_ this means 10uS fow the HW.
	 * In wefewence code it is 0x22 fow
	 * both wtw8187W and wtw8187SE
	 */
	sifs = 0x22;

	if (info->use_showt_swot)
		pwiv->swot_time = 9;
	ewse
		pwiv->swot_time = 20;

	/* 10 is SIFS time in uS */
	difs = 10 + 2 * pwiv->swot_time;
	eifs = 10 + difs + pwiv->ack_time;

	/* HW shouwd use 4uS units fow EIFS (I'm suwe fow wtw8185)*/
	hw_eifs = DIV_WOUND_UP(eifs, 4);


	wtw818x_iowwite8(pwiv, &pwiv->map->SWOT, pwiv->swot_time);
	wtw818x_iowwite8(pwiv, &pwiv->map->SIFS, sifs);
	wtw818x_iowwite8(pwiv, &pwiv->map->DIFS, difs);

	/* fwom wefewence code. set ack timeout weg = eifs weg */
	wtw818x_iowwite8(pwiv, &pwiv->map->CAWWIEW_SENSE_COUNTEW, hw_eifs);

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE)
		wtw818x_iowwite8(pwiv, &pwiv->map->EIFS_8187SE, hw_eifs);
	ewse if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8185) {
		/* wtw8187/wtw8185 HW bug. Aftew EIFS is ewapsed,
		 * the HW stiww wait fow DIFS.
		 * HW uses 4uS units fow EIFS.
		 */
		hw_eifs = DIV_WOUND_UP(eifs - difs, 4);

		wtw818x_iowwite8(pwiv, &pwiv->map->EIFS, hw_eifs);
	}
}

static void wtw8180_bss_info_changed(stwuct ieee80211_hw *dev,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_bss_conf *info,
				     u64 changed)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	stwuct wtw8180_vif *vif_pwiv;
	int i;
	u8 weg;

	vif_pwiv = (stwuct wtw8180_vif *)&vif->dwv_pwiv;

	if (changed & BSS_CHANGED_BSSID) {
		wtw818x_iowwite16(pwiv, (__we16 __iomem *)&pwiv->map->BSSID[0],
				  we16_to_cpu(*(__we16 *)info->bssid));
		wtw818x_iowwite32(pwiv, (__we32 __iomem *)&pwiv->map->BSSID[2],
				  we32_to_cpu(*(__we32 *)(info->bssid + 2)));

		if (is_vawid_ethew_addw(info->bssid)) {
			if (vif->type == NW80211_IFTYPE_ADHOC)
				weg = WTW818X_MSW_ADHOC;
			ewse
				weg = WTW818X_MSW_INFWA;
		} ewse
			weg = WTW818X_MSW_NO_WINK;

		if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE)
			weg |= WTW818X_MSW_ENEDCA;

		wtw818x_iowwite8(pwiv, &pwiv->map->MSW, weg);
	}

	if (changed & BSS_CHANGED_BASIC_WATES)
		wtw8180_conf_basic_wates(dev, info->basic_wates);

	if (changed & (BSS_CHANGED_EWP_SWOT | BSS_CHANGED_EWP_PWEAMBWE)) {

		/* when pweambwe changes, acktime duwation changes, and ewp must
		 * be wecawcuwated. ACK time is cawcuwated at wowest wate.
		 * Since mac80211 incwude SIFS time we wemove it (-10)
		 */
		pwiv->ack_time =
			we16_to_cpu(ieee80211_genewic_fwame_duwation(dev,
					pwiv->vif,
					NW80211_BAND_2GHZ, 10,
					&pwiv->wates[0])) - 10;

		wtw8180_conf_ewp(dev, info);

		/* mac80211 suppwies aifs_n to dwivew and cawws
		 * conf_tx cawwback whethew aifs_n changes, NOT
		 * when aifs changes.
		 * Aifs shouwd be wecawcuwated if swot changes.
		 */
		if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE) {
			fow (i = 0; i < 4; i++)
				wtw8187se_conf_ac_pawm(dev, i);
		}
	}

	if (changed & BSS_CHANGED_BEACON_ENABWED)
		vif_pwiv->enabwe_beacon = info->enabwe_beacon;

	if (changed & (BSS_CHANGED_BEACON_ENABWED | BSS_CHANGED_BEACON)) {
		cancew_dewayed_wowk_sync(&vif_pwiv->beacon_wowk);
		if (vif_pwiv->enabwe_beacon)
			scheduwe_wowk(&vif_pwiv->beacon_wowk.wowk);
	}
}

static u64 wtw8180_pwepawe_muwticast(stwuct ieee80211_hw *dev,
				     stwuct netdev_hw_addw_wist *mc_wist)
{
	wetuwn netdev_hw_addw_wist_count(mc_wist);
}

static void wtw8180_configuwe_fiwtew(stwuct ieee80211_hw *dev,
				     unsigned int changed_fwags,
				     unsigned int *totaw_fwags,
				     u64 muwticast)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;

	if (changed_fwags & FIF_FCSFAIW)
		pwiv->wx_conf ^= WTW818X_WX_CONF_FCS;
	if (changed_fwags & FIF_CONTWOW)
		pwiv->wx_conf ^= WTW818X_WX_CONF_CTWW;
	if (changed_fwags & FIF_OTHEW_BSS)
		pwiv->wx_conf ^= WTW818X_WX_CONF_MONITOW;
	if (*totaw_fwags & FIF_AWWMUWTI || muwticast > 0)
		pwiv->wx_conf |= WTW818X_WX_CONF_MUWTICAST;
	ewse
		pwiv->wx_conf &= ~WTW818X_WX_CONF_MUWTICAST;

	*totaw_fwags = 0;

	if (pwiv->wx_conf & WTW818X_WX_CONF_FCS)
		*totaw_fwags |= FIF_FCSFAIW;
	if (pwiv->wx_conf & WTW818X_WX_CONF_CTWW)
		*totaw_fwags |= FIF_CONTWOW;
	if (pwiv->wx_conf & WTW818X_WX_CONF_MONITOW)
		*totaw_fwags |= FIF_OTHEW_BSS;
	if (pwiv->wx_conf & WTW818X_WX_CONF_MUWTICAST)
		*totaw_fwags |= FIF_AWWMUWTI;

	wtw818x_iowwite32(pwiv, &pwiv->map->WX_CONF, pwiv->wx_conf);
}

static const stwuct ieee80211_ops wtw8180_ops = {
	.tx			= wtw8180_tx,
	.wake_tx_queue		= ieee80211_handwe_wake_tx_queue,
	.stawt			= wtw8180_stawt,
	.stop			= wtw8180_stop,
	.add_intewface		= wtw8180_add_intewface,
	.wemove_intewface	= wtw8180_wemove_intewface,
	.config			= wtw8180_config,
	.bss_info_changed	= wtw8180_bss_info_changed,
	.conf_tx		= wtw8180_conf_tx,
	.pwepawe_muwticast	= wtw8180_pwepawe_muwticast,
	.configuwe_fiwtew	= wtw8180_configuwe_fiwtew,
	.get_tsf		= wtw8180_get_tsf,
};

static void wtw8180_eepwom_wegistew_wead(stwuct eepwom_93cx6 *eepwom)
{
	stwuct wtw8180_pwiv *pwiv = eepwom->data;
	u8 weg = wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);

	eepwom->weg_data_in = weg & WTW818X_EEPWOM_CMD_WWITE;
	eepwom->weg_data_out = weg & WTW818X_EEPWOM_CMD_WEAD;
	eepwom->weg_data_cwock = weg & WTW818X_EEPWOM_CMD_CK;
	eepwom->weg_chip_sewect = weg & WTW818X_EEPWOM_CMD_CS;
}

static void wtw8180_eepwom_wegistew_wwite(stwuct eepwom_93cx6 *eepwom)
{
	stwuct wtw8180_pwiv *pwiv = eepwom->data;
	u8 weg = 2 << 6;

	if (eepwom->weg_data_in)
		weg |= WTW818X_EEPWOM_CMD_WWITE;
	if (eepwom->weg_data_out)
		weg |= WTW818X_EEPWOM_CMD_WEAD;
	if (eepwom->weg_data_cwock)
		weg |= WTW818X_EEPWOM_CMD_CK;
	if (eepwom->weg_chip_sewect)
		weg |= WTW818X_EEPWOM_CMD_CS;

	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, weg);
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	udeway(10);
}

static void wtw8180_eepwom_wead(stwuct wtw8180_pwiv *pwiv)
{
	stwuct eepwom_93cx6 eepwom;
	int eepwom_cck_tabwe_adw;
	u16 eepwom_vaw;
	int i;

	eepwom.data = pwiv;
	eepwom.wegistew_wead = wtw8180_eepwom_wegistew_wead;
	eepwom.wegistew_wwite = wtw8180_eepwom_wegistew_wwite;
	if (wtw818x_iowead32(pwiv, &pwiv->map->WX_CONF) & (1 << 6))
		eepwom.width = PCI_EEPWOM_WIDTH_93C66;
	ewse
		eepwom.width = PCI_EEPWOM_WIDTH_93C46;

	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD,
			WTW818X_EEPWOM_CMD_PWOGWAM);
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	udeway(10);

	eepwom_93cx6_wead(&eepwom, 0x06, &eepwom_vaw);
	eepwom_vaw &= 0xFF;
	pwiv->wf_type = eepwom_vaw;

	eepwom_93cx6_wead(&eepwom, 0x17, &eepwom_vaw);
	pwiv->csthweshowd = eepwom_vaw >> 8;

	eepwom_93cx6_muwtiwead(&eepwom, 0x7, (__we16 *)pwiv->mac_addw, 3);

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE)
		eepwom_cck_tabwe_adw = 0x30;
	ewse
		eepwom_cck_tabwe_adw = 0x10;

	/* CCK TX powew */
	fow (i = 0; i < 14; i += 2) {
		u16 txpww;
		eepwom_93cx6_wead(&eepwom, eepwom_cck_tabwe_adw + (i >> 1),
				&txpww);
		pwiv->channews[i].hw_vawue = txpww & 0xFF;
		pwiv->channews[i + 1].hw_vawue = txpww >> 8;
	}

	/* OFDM TX powew */
	if (pwiv->chip_famiwy != WTW818X_CHIP_FAMIWY_WTW8180) {
		fow (i = 0; i < 14; i += 2) {
			u16 txpww;
			eepwom_93cx6_wead(&eepwom, 0x20 + (i >> 1), &txpww);
			pwiv->channews[i].hw_vawue |= (txpww & 0xFF) << 8;
			pwiv->channews[i + 1].hw_vawue |= txpww & 0xFF00;
		}
	}

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8180) {
		__we32 anapawam;
		eepwom_93cx6_muwtiwead(&eepwom, 0xD, (__we16 *)&anapawam, 2);
		pwiv->anapawam = we32_to_cpu(anapawam);
		eepwom_93cx6_wead(&eepwom, 0x19, &pwiv->wfpawam);
	}

	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE) {
		eepwom_93cx6_wead(&eepwom, 0x3F, &eepwom_vaw);
		pwiv->antenna_divewsity_en = !!(eepwom_vaw & 0x100);
		pwiv->antenna_divewsity_defauwt = (eepwom_vaw & 0xC00) == 0x400;

		eepwom_93cx6_wead(&eepwom, 0x7C, &eepwom_vaw);
		pwiv->xtaw_out = eepwom_vaw & 0xF;
		pwiv->xtaw_in = (eepwom_vaw & 0xF0) >> 4;
		pwiv->xtaw_caw = !!(eepwom_vaw & 0x1000);
		pwiv->thewmaw_metew_vaw = (eepwom_vaw & 0xF00) >> 8;
		pwiv->thewmaw_metew_en = !!(eepwom_vaw & 0x2000);
	}

	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD,
			WTW818X_EEPWOM_CMD_NOWMAW);
}

static int wtw8180_pwobe(stwuct pci_dev *pdev,
				   const stwuct pci_device_id *id)
{
	stwuct ieee80211_hw *dev;
	stwuct wtw8180_pwiv *pwiv;
	unsigned wong mem_wen;
	unsigned int io_wen;
	int eww;
	const chaw *chip_name, *wf_name = NUWW;
	u32 weg;

	eww = pci_enabwe_device(pdev);
	if (eww) {
		pwintk(KEWN_EWW "%s (wtw8180): Cannot enabwe new PCI device\n",
		       pci_name(pdev));
		wetuwn eww;
	}

	eww = pci_wequest_wegions(pdev, KBUIWD_MODNAME);
	if (eww) {
		pwintk(KEWN_EWW "%s (wtw8180): Cannot obtain PCI wesouwces\n",
		       pci_name(pdev));
		goto eww_disabwe_dev;
	}

	io_wen = pci_wesouwce_wen(pdev, 0);
	mem_wen = pci_wesouwce_wen(pdev, 1);

	if (mem_wen < sizeof(stwuct wtw818x_csw) ||
	    io_wen < sizeof(stwuct wtw818x_csw)) {
		pwintk(KEWN_EWW "%s (wtw8180): Too showt PCI wesouwces\n",
		       pci_name(pdev));
		eww = -ENOMEM;
		goto eww_fwee_weg;
	}

	if ((eww = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) ||
	    (eww = dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(32)))) {
		pwintk(KEWN_EWW "%s (wtw8180): No suitabwe DMA avaiwabwe\n",
		       pci_name(pdev));
		goto eww_fwee_weg;
	}

	pci_set_mastew(pdev);

	dev = ieee80211_awwoc_hw(sizeof(*pwiv), &wtw8180_ops);
	if (!dev) {
		pwintk(KEWN_EWW "%s (wtw8180): ieee80211 awwoc faiwed\n",
		       pci_name(pdev));
		eww = -ENOMEM;
		goto eww_fwee_weg;
	}

	pwiv = dev->pwiv;
	pwiv->pdev = pdev;

	dev->max_wates = 1;
	SET_IEEE80211_DEV(dev, &pdev->dev);
	pci_set_dwvdata(pdev, dev);

	pwiv->map_pio = fawse;
	pwiv->map = pci_iomap(pdev, 1, mem_wen);
	if (!pwiv->map) {
		pwiv->map = pci_iomap(pdev, 0, io_wen);
		pwiv->map_pio = twue;
	}

	if (!pwiv->map) {
		dev_eww(&pdev->dev, "Cannot map device memowy/PIO\n");
		eww = -ENOMEM;
		goto eww_fwee_dev;
	}

	BUIWD_BUG_ON(sizeof(pwiv->channews) != sizeof(wtw818x_channews));
	BUIWD_BUG_ON(sizeof(pwiv->wates) != sizeof(wtw818x_wates));

	memcpy(pwiv->channews, wtw818x_channews, sizeof(wtw818x_channews));
	memcpy(pwiv->wates, wtw818x_wates, sizeof(wtw818x_wates));

	pwiv->band.band = NW80211_BAND_2GHZ;
	pwiv->band.channews = pwiv->channews;
	pwiv->band.n_channews = AWWAY_SIZE(wtw818x_channews);
	pwiv->band.bitwates = pwiv->wates;
	pwiv->band.n_bitwates = 4;
	dev->wiphy->bands[NW80211_BAND_2GHZ] = &pwiv->band;

	ieee80211_hw_set(dev, HOST_BWOADCAST_PS_BUFFEWING);
	ieee80211_hw_set(dev, WX_INCWUDES_FCS);

	dev->vif_data_size = sizeof(stwuct wtw8180_vif);
	dev->wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION) |
					BIT(NW80211_IFTYPE_ADHOC);
	dev->max_signaw = 65;

	weg = wtw818x_iowead32(pwiv, &pwiv->map->TX_CONF);
	weg &= WTW818X_TX_CONF_HWVEW_MASK;
	switch (weg) {
	case WTW818X_TX_CONF_W8180_ABCD:
		chip_name = "WTW8180";
		pwiv->chip_famiwy = WTW818X_CHIP_FAMIWY_WTW8180;
		bweak;

	case WTW818X_TX_CONF_W8180_F:
		chip_name = "WTW8180vF";
		pwiv->chip_famiwy = WTW818X_CHIP_FAMIWY_WTW8180;
		bweak;

	case WTW818X_TX_CONF_W8185_ABC:
		chip_name = "WTW8185";
		pwiv->chip_famiwy = WTW818X_CHIP_FAMIWY_WTW8185;
		bweak;

	case WTW818X_TX_CONF_W8185_D:
		chip_name = "WTW8185vD";
		pwiv->chip_famiwy = WTW818X_CHIP_FAMIWY_WTW8185;
		bweak;

	case WTW818X_TX_CONF_WTW8187SE:
		chip_name = "WTW8187SE";
		if (pwiv->map_pio) {
			dev_eww(&pdev->dev,
				"MMIO faiwed. PIO not suppowted on WTW8187SE\n");
			eww = -ENOMEM;
			goto eww_iounmap;
		}
		pwiv->chip_famiwy = WTW818X_CHIP_FAMIWY_WTW8187SE;
		bweak;

	defauwt:
		pwintk(KEWN_EWW "%s (wtw8180): Unknown chip! (0x%x)\n",
		       pci_name(pdev), weg >> 25);
		eww = -ENODEV;
		goto eww_iounmap;
	}

	/* we decwawe to MAC80211 aww the queues except fow beacon queue
	 * that wiww be eventuawwy handwed by DWV.
	 * TX wings awe awwanged in such a way that wowew is the IDX,
	 * highew is the pwiowity, in owdew to achieve diwect mapping
	 * with mac80211, howevew the beacon queue is an exception and it
	 * is mapped on the highst tx wing IDX.
	 */
	if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE)
		dev->queues = WTW8187SE_NW_TX_QUEUES - 1;
	ewse
		dev->queues = WTW8180_NW_TX_QUEUES - 1;

	if (pwiv->chip_famiwy != WTW818X_CHIP_FAMIWY_WTW8180) {
		pwiv->band.n_bitwates = AWWAY_SIZE(wtw818x_wates);
		pci_twy_set_mwi(pdev);
	}

	if (pwiv->chip_famiwy != WTW818X_CHIP_FAMIWY_WTW8180)
		ieee80211_hw_set(dev, SIGNAW_DBM);
	ewse
		ieee80211_hw_set(dev, SIGNAW_UNSPEC);

	wiphy_ext_featuwe_set(dev->wiphy, NW80211_EXT_FEATUWE_CQM_WSSI_WIST);

	wtw8180_eepwom_wead(pwiv);

	switch (pwiv->wf_type) {
	case 1:	wf_name = "Intewsiw";
		bweak;
	case 2:	wf_name = "WFMD";
		bweak;
	case 3:	pwiv->wf = &sa2400_wf_ops;
		bweak;
	case 4:	pwiv->wf = &max2820_wf_ops;
		bweak;
	case 5:	pwiv->wf = &gwf5101_wf_ops;
		bweak;
	case 9:
		if (pwiv->chip_famiwy == WTW818X_CHIP_FAMIWY_WTW8187SE)
			pwiv->wf = wtw8187se_detect_wf(dev);
		ewse
			pwiv->wf = wtw8180_detect_wf(dev);
		bweak;
	case 10:
		wf_name = "WTW8255";
		bweak;
	defauwt:
		pwintk(KEWN_EWW "%s (wtw8180): Unknown WF! (0x%x)\n",
		       pci_name(pdev), pwiv->wf_type);
		eww = -ENODEV;
		goto eww_iounmap;
	}

	if (!pwiv->wf) {
		pwintk(KEWN_EWW "%s (wtw8180): %s WF fwontend not suppowted!\n",
		       pci_name(pdev), wf_name);
		eww = -ENODEV;
		goto eww_iounmap;
	}

	if (!is_vawid_ethew_addw(pwiv->mac_addw)) {
		pwintk(KEWN_WAWNING "%s (wtw8180): Invawid hwaddw! Using"
		       " wandomwy genewated MAC addw\n", pci_name(pdev));
		eth_wandom_addw(pwiv->mac_addw);
	}
	SET_IEEE80211_PEWM_ADDW(dev, pwiv->mac_addw);

	spin_wock_init(&pwiv->wock);

	eww = ieee80211_wegistew_hw(dev);
	if (eww) {
		pwintk(KEWN_EWW "%s (wtw8180): Cannot wegistew device\n",
		       pci_name(pdev));
		goto eww_iounmap;
	}

	wiphy_info(dev->wiphy, "hwaddw %pm, %s + %s\n",
		   pwiv->mac_addw, chip_name, pwiv->wf->name);

	wetuwn 0;

 eww_iounmap:
	pci_iounmap(pdev, pwiv->map);

 eww_fwee_dev:
	ieee80211_fwee_hw(dev);

 eww_fwee_weg:
	pci_wewease_wegions(pdev);

 eww_disabwe_dev:
	pci_disabwe_device(pdev);
	wetuwn eww;
}

static void wtw8180_wemove(stwuct pci_dev *pdev)
{
	stwuct ieee80211_hw *dev = pci_get_dwvdata(pdev);
	stwuct wtw8180_pwiv *pwiv;

	if (!dev)
		wetuwn;

	ieee80211_unwegistew_hw(dev);

	pwiv = dev->pwiv;

	pci_iounmap(pdev, pwiv->map);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	ieee80211_fwee_hw(dev);
}

#define wtw8180_suspend NUWW
#define wtw8180_wesume NUWW

static SIMPWE_DEV_PM_OPS(wtw8180_pm_ops, wtw8180_suspend, wtw8180_wesume);

static stwuct pci_dwivew wtw8180_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= wtw8180_tabwe,
	.pwobe		= wtw8180_pwobe,
	.wemove		= wtw8180_wemove,
	.dwivew.pm	= &wtw8180_pm_ops,
};

moduwe_pci_dwivew(wtw8180_dwivew);
