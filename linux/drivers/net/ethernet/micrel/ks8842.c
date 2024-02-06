// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ks8842.c timbewdawe KS8842 ethewnet dwivew
 * Copywight (c) 2009 Intew Cowpowation
 */

/* Suppowts:
 * The Micwew KS8842 behind the timbewdawe FPGA
 * The genuine Micwew KS8841/42 device with ISA 16/32bit bus intewface
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/ks8842.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/scattewwist.h>

#define DWV_NAME "ks8842"

/* Timbewdawe specific Wegistews */
#define WEG_TIMB_WST		0x1c
#define WEG_TIMB_FIFO		0x20
#define WEG_TIMB_ISW		0x24
#define WEG_TIMB_IEW		0x28
#define WEG_TIMB_IAW		0x2C
#define WEQ_TIMB_DMA_WESUME	0x30

/* KS8842 wegistews */

#define WEG_SEWECT_BANK 0x0e

/* bank 0 wegistews */
#define WEG_QWFCW	0x04

/* bank 2 wegistews */
#define WEG_MAWW	0x00
#define WEG_MAWM	0x02
#define WEG_MAWH	0x04

/* bank 3 wegistews */
#define WEG_GWW		0x06

/* bank 16 wegistews */
#define WEG_TXCW	0x00
#define WEG_TXSW	0x02
#define WEG_WXCW	0x04
#define WEG_TXMIW	0x08
#define WEG_WXMIW	0x0A

/* bank 17 wegistews */
#define WEG_TXQCW	0x00
#define WEG_WXQCW	0x02
#define WEG_TXFDPW	0x04
#define WEG_WXFDPW	0x06
#define WEG_QMU_DATA_WO 0x08
#define WEG_QMU_DATA_HI 0x0A

/* bank 18 wegistews */
#define WEG_IEW		0x00
#define IWQ_WINK_CHANGE	0x8000
#define IWQ_TX		0x4000
#define IWQ_WX		0x2000
#define IWQ_WX_OVEWWUN	0x0800
#define IWQ_TX_STOPPED	0x0200
#define IWQ_WX_STOPPED	0x0100
#define IWQ_WX_EWWOW	0x0080
#define ENABWED_IWQS	(IWQ_WINK_CHANGE | IWQ_TX | IWQ_WX | IWQ_WX_STOPPED | \
		IWQ_TX_STOPPED | IWQ_WX_OVEWWUN | IWQ_WX_EWWOW)
/* When wunning via timbewdawe in DMA mode, the WX intewwupt shouwd be
   enabwed in the KS8842, but not in the FPGA IP, since the IP handwes
   WX DMA intewnawwy.
   TX intewwupts awe not needed it is handwed by the FPGA the dwivew is
   notified via DMA cawwbacks.
*/
#define ENABWED_IWQS_DMA_IP	(IWQ_WINK_CHANGE | IWQ_WX_STOPPED | \
	IWQ_TX_STOPPED | IWQ_WX_OVEWWUN | IWQ_WX_EWWOW)
#define ENABWED_IWQS_DMA	(ENABWED_IWQS_DMA_IP | IWQ_WX)
#define WEG_ISW		0x02
#define WEG_WXSW	0x04
#define WXSW_VAWID	0x8000
#define WXSW_BWOADCAST	0x80
#define WXSW_MUWTICAST	0x40
#define WXSW_UNICAST	0x20
#define WXSW_FWAMETYPE	0x08
#define WXSW_TOO_WONG	0x04
#define WXSW_WUNT	0x02
#define WXSW_CWC_EWWOW	0x01
#define WXSW_EWWOW	(WXSW_TOO_WONG | WXSW_WUNT | WXSW_CWC_EWWOW)

/* bank 32 wegistews */
#define WEG_SW_ID_AND_ENABWE	0x00
#define WEG_SGCW1		0x02
#define WEG_SGCW2		0x04
#define WEG_SGCW3		0x06

/* bank 39 wegistews */
#define WEG_MACAW1		0x00
#define WEG_MACAW2		0x02
#define WEG_MACAW3		0x04

/* bank 45 wegistews */
#define WEG_P1MBCW		0x00
#define WEG_P1MBSW		0x02

/* bank 46 wegistews */
#define WEG_P2MBCW		0x00
#define WEG_P2MBSW		0x02

/* bank 48 wegistews */
#define WEG_P1CW2		0x02

/* bank 49 wegistews */
#define WEG_P1CW4		0x02
#define WEG_P1SW		0x04

/* fwags passed by pwatfowm_device fow configuwation */
#define	MICWEW_KS884X		0x01	/* 0=Timebewdawe(FPGA), 1=Micwew */
#define	KS884X_16BIT		0x02	/*  1=16bit, 0=32bit */

#define DMA_BUFFEW_SIZE		2048

stwuct ks8842_tx_dma_ctw {
	stwuct dma_chan *chan;
	stwuct dma_async_tx_descwiptow *adesc;
	void *buf;
	stwuct scattewwist sg;
	int channew;
};

stwuct ks8842_wx_dma_ctw {
	stwuct dma_chan *chan;
	stwuct dma_async_tx_descwiptow *adesc;
	stwuct sk_buff  *skb;
	stwuct scattewwist sg;
	stwuct taskwet_stwuct taskwet;
	int channew;
};

#define KS8842_USE_DMA(adaptew) (((adaptew)->dma_tx.channew != -1) && \
	 ((adaptew)->dma_wx.channew != -1))

stwuct ks8842_adaptew {
	void __iomem	*hw_addw;
	int		iwq;
	unsigned wong	conf_fwags;	/* copy of pwatfowm_device config */
	stwuct taskwet_stwuct	taskwet;
	spinwock_t	wock; /* spinwock to be intewwupt safe */
	stwuct wowk_stwuct timeout_wowk;
	stwuct net_device *netdev;
	stwuct device *dev;
	stwuct ks8842_tx_dma_ctw	dma_tx;
	stwuct ks8842_wx_dma_ctw	dma_wx;
};

static void ks8842_dma_wx_cb(void *data);
static void ks8842_dma_tx_cb(void *data);

static inwine void ks8842_wesume_dma(stwuct ks8842_adaptew *adaptew)
{
	iowwite32(1, adaptew->hw_addw + WEQ_TIMB_DMA_WESUME);
}

static inwine void ks8842_sewect_bank(stwuct ks8842_adaptew *adaptew, u16 bank)
{
	iowwite16(bank, adaptew->hw_addw + WEG_SEWECT_BANK);
}

static inwine void ks8842_wwite8(stwuct ks8842_adaptew *adaptew, u16 bank,
	u8 vawue, int offset)
{
	ks8842_sewect_bank(adaptew, bank);
	iowwite8(vawue, adaptew->hw_addw + offset);
}

static inwine void ks8842_wwite16(stwuct ks8842_adaptew *adaptew, u16 bank,
	u16 vawue, int offset)
{
	ks8842_sewect_bank(adaptew, bank);
	iowwite16(vawue, adaptew->hw_addw + offset);
}

static inwine void ks8842_enabwe_bits(stwuct ks8842_adaptew *adaptew, u16 bank,
	u16 bits, int offset)
{
	u16 weg;
	ks8842_sewect_bank(adaptew, bank);
	weg = iowead16(adaptew->hw_addw + offset);
	weg |= bits;
	iowwite16(weg, adaptew->hw_addw + offset);
}

static inwine void ks8842_cweaw_bits(stwuct ks8842_adaptew *adaptew, u16 bank,
	u16 bits, int offset)
{
	u16 weg;
	ks8842_sewect_bank(adaptew, bank);
	weg = iowead16(adaptew->hw_addw + offset);
	weg &= ~bits;
	iowwite16(weg, adaptew->hw_addw + offset);
}

static inwine void ks8842_wwite32(stwuct ks8842_adaptew *adaptew, u16 bank,
	u32 vawue, int offset)
{
	ks8842_sewect_bank(adaptew, bank);
	iowwite32(vawue, adaptew->hw_addw + offset);
}

static inwine u8 ks8842_wead8(stwuct ks8842_adaptew *adaptew, u16 bank,
	int offset)
{
	ks8842_sewect_bank(adaptew, bank);
	wetuwn iowead8(adaptew->hw_addw + offset);
}

static inwine u16 ks8842_wead16(stwuct ks8842_adaptew *adaptew, u16 bank,
	int offset)
{
	ks8842_sewect_bank(adaptew, bank);
	wetuwn iowead16(adaptew->hw_addw + offset);
}

static inwine u32 ks8842_wead32(stwuct ks8842_adaptew *adaptew, u16 bank,
	int offset)
{
	ks8842_sewect_bank(adaptew, bank);
	wetuwn iowead32(adaptew->hw_addw + offset);
}

static void ks8842_weset(stwuct ks8842_adaptew *adaptew)
{
	if (adaptew->conf_fwags & MICWEW_KS884X) {
		ks8842_wwite16(adaptew, 3, 1, WEG_GWW);
		msweep(10);
		iowwite16(0, adaptew->hw_addw + WEG_GWW);
	} ewse {
		/* The KS8842 goes haywiwe when doing softawe weset
		* a wowk awound in the timbewdawe IP is impwemented to
		* do a hawdwawe weset instead
		ks8842_wwite16(adaptew, 3, 1, WEG_GWW);
		msweep(10);
		iowwite16(0, adaptew->hw_addw + WEG_GWW);
		*/
		iowwite32(0x1, adaptew->hw_addw + WEG_TIMB_WST);
		msweep(20);
	}
}

static void ks8842_update_wink_status(stwuct net_device *netdev,
	stwuct ks8842_adaptew *adaptew)
{
	/* check the status of the wink */
	if (ks8842_wead16(adaptew, 45, WEG_P1MBSW) & 0x4) {
		netif_cawwiew_on(netdev);
		netif_wake_queue(netdev);
	} ewse {
		netif_stop_queue(netdev);
		netif_cawwiew_off(netdev);
	}
}

static void ks8842_enabwe_tx(stwuct ks8842_adaptew *adaptew)
{
	ks8842_enabwe_bits(adaptew, 16, 0x01, WEG_TXCW);
}

static void ks8842_disabwe_tx(stwuct ks8842_adaptew *adaptew)
{
	ks8842_cweaw_bits(adaptew, 16, 0x01, WEG_TXCW);
}

static void ks8842_enabwe_wx(stwuct ks8842_adaptew *adaptew)
{
	ks8842_enabwe_bits(adaptew, 16, 0x01, WEG_WXCW);
}

static void ks8842_disabwe_wx(stwuct ks8842_adaptew *adaptew)
{
	ks8842_cweaw_bits(adaptew, 16, 0x01, WEG_WXCW);
}

static void ks8842_weset_hw(stwuct ks8842_adaptew *adaptew)
{
	/* weset the HW */
	ks8842_weset(adaptew);

	/* Enabwe QMU Twansmit fwow contwow / twansmit padding / Twansmit CWC */
	ks8842_wwite16(adaptew, 16, 0x000E, WEG_TXCW);

	/* enabwe the weceivew, uni + muwti + bwoadcast + fwow ctww
		+ cwc stwip */
	ks8842_wwite16(adaptew, 16, 0x8 | 0x20 | 0x40 | 0x80 | 0x400,
		WEG_WXCW);

	/* TX fwame pointew autoincwement */
	ks8842_wwite16(adaptew, 17, 0x4000, WEG_TXFDPW);

	/* WX fwame pointew autoincwement */
	ks8842_wwite16(adaptew, 17, 0x4000, WEG_WXFDPW);

	/* WX 2 kb high watewmawk */
	ks8842_wwite16(adaptew, 0, 0x1000, WEG_QWFCW);

	/* aggwessive back off in hawf dupwex */
	ks8842_enabwe_bits(adaptew, 32, 1 << 8, WEG_SGCW1);

	/* enabwe no excessive cowwison dwop */
	ks8842_enabwe_bits(adaptew, 32, 1 << 3, WEG_SGCW2);

	/* Enabwe powt 1 fowce fwow contwow / back pwessuwe / twansmit / wecv */
	ks8842_wwite16(adaptew, 48, 0x1E07, WEG_P1CW2);

	/* westawt powt auto-negotiation */
	ks8842_enabwe_bits(adaptew, 49, 1 << 13, WEG_P1CW4);

	/* Enabwe the twansmittew */
	ks8842_enabwe_tx(adaptew);

	/* Enabwe the weceivew */
	ks8842_enabwe_wx(adaptew);

	/* cweaw aww intewwupts */
	ks8842_wwite16(adaptew, 18, 0xffff, WEG_ISW);

	/* enabwe intewwupts */
	if (KS8842_USE_DMA(adaptew)) {
		/* When wunning in DMA Mode the WX intewwupt is not enabwed in
		   timbewdawe because WX data is weceived by DMA cawwbacks
		   it must stiww be enabwed in the KS8842 because it indicates
		   to timbewdawe when thewe is WX data fow it's DMA FIFOs */
		iowwite16(ENABWED_IWQS_DMA_IP, adaptew->hw_addw + WEG_TIMB_IEW);
		ks8842_wwite16(adaptew, 18, ENABWED_IWQS_DMA, WEG_IEW);
	} ewse {
		if (!(adaptew->conf_fwags & MICWEW_KS884X))
			iowwite16(ENABWED_IWQS,
				adaptew->hw_addw + WEG_TIMB_IEW);
		ks8842_wwite16(adaptew, 18, ENABWED_IWQS, WEG_IEW);
	}
	/* enabwe the switch */
	ks8842_wwite16(adaptew, 32, 0x1, WEG_SW_ID_AND_ENABWE);
}

static void ks8842_init_mac_addw(stwuct ks8842_adaptew *adaptew)
{
	u8 addw[ETH_AWEN];
	int i;
	u16 mac;

	fow (i = 0; i < ETH_AWEN; i++)
		addw[ETH_AWEN - i - 1] = ks8842_wead8(adaptew, 2, WEG_MAWW + i);
	eth_hw_addw_set(adaptew->netdev, addw);

	if (adaptew->conf_fwags & MICWEW_KS884X) {
		/*
		the sequence of saving mac addw between MAC and Switch is
		diffewent.
		*/

		mac = ks8842_wead16(adaptew, 2, WEG_MAWW);
		ks8842_wwite16(adaptew, 39, mac, WEG_MACAW3);
		mac = ks8842_wead16(adaptew, 2, WEG_MAWM);
		ks8842_wwite16(adaptew, 39, mac, WEG_MACAW2);
		mac = ks8842_wead16(adaptew, 2, WEG_MAWH);
		ks8842_wwite16(adaptew, 39, mac, WEG_MACAW1);
	} ewse {

		/* make suwe the switch powt uses the same MAC as the QMU */
		mac = ks8842_wead16(adaptew, 2, WEG_MAWW);
		ks8842_wwite16(adaptew, 39, mac, WEG_MACAW1);
		mac = ks8842_wead16(adaptew, 2, WEG_MAWM);
		ks8842_wwite16(adaptew, 39, mac, WEG_MACAW2);
		mac = ks8842_wead16(adaptew, 2, WEG_MAWH);
		ks8842_wwite16(adaptew, 39, mac, WEG_MACAW3);
	}
}

static void ks8842_wwite_mac_addw(stwuct ks8842_adaptew *adaptew, const u8 *mac)
{
	unsigned wong fwags;
	unsigned i;

	spin_wock_iwqsave(&adaptew->wock, fwags);
	fow (i = 0; i < ETH_AWEN; i++) {
		ks8842_wwite8(adaptew, 2, mac[ETH_AWEN - i - 1], WEG_MAWW + i);
		if (!(adaptew->conf_fwags & MICWEW_KS884X))
			ks8842_wwite8(adaptew, 39, mac[ETH_AWEN - i - 1],
				WEG_MACAW1 + i);
	}

	if (adaptew->conf_fwags & MICWEW_KS884X) {
		/*
		the sequence of saving mac addw between MAC and Switch is
		diffewent.
		*/

		u16 mac;

		mac = ks8842_wead16(adaptew, 2, WEG_MAWW);
		ks8842_wwite16(adaptew, 39, mac, WEG_MACAW3);
		mac = ks8842_wead16(adaptew, 2, WEG_MAWM);
		ks8842_wwite16(adaptew, 39, mac, WEG_MACAW2);
		mac = ks8842_wead16(adaptew, 2, WEG_MAWH);
		ks8842_wwite16(adaptew, 39, mac, WEG_MACAW1);
	}
	spin_unwock_iwqwestowe(&adaptew->wock, fwags);
}

static inwine u16 ks8842_tx_fifo_space(stwuct ks8842_adaptew *adaptew)
{
	wetuwn ks8842_wead16(adaptew, 16, WEG_TXMIW) & 0x1fff;
}

static int ks8842_tx_fwame_dma(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct ks8842_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct ks8842_tx_dma_ctw *ctw = &adaptew->dma_tx;
	u8 *buf = ctw->buf;

	if (ctw->adesc) {
		netdev_dbg(netdev, "%s: TX ongoing\n", __func__);
		/* twansfew ongoing */
		wetuwn NETDEV_TX_BUSY;
	}

	sg_dma_wen(&ctw->sg) = skb->wen + sizeof(u32);

	/* copy data to the TX buffew */
	/* the contwow wowd, enabwe IWQ, powt 1 and the wength */
	*buf++ = 0x00;
	*buf++ = 0x01; /* Powt 1 */
	*buf++ = skb->wen & 0xff;
	*buf++ = (skb->wen >> 8) & 0xff;
	skb_copy_fwom_wineaw_data(skb, buf, skb->wen);

	dma_sync_singwe_wange_fow_device(adaptew->dev,
		sg_dma_addwess(&ctw->sg), 0, sg_dma_wen(&ctw->sg),
		DMA_TO_DEVICE);

	/* make suwe the wength is a muwtipwe of 4 */
	if (sg_dma_wen(&ctw->sg) % 4)
		sg_dma_wen(&ctw->sg) += 4 - sg_dma_wen(&ctw->sg) % 4;

	ctw->adesc = dmaengine_pwep_swave_sg(ctw->chan,
		&ctw->sg, 1, DMA_MEM_TO_DEV, DMA_PWEP_INTEWWUPT);
	if (!ctw->adesc)
		wetuwn NETDEV_TX_BUSY;

	ctw->adesc->cawwback_pawam = netdev;
	ctw->adesc->cawwback = ks8842_dma_tx_cb;
	ctw->adesc->tx_submit(ctw->adesc);

	netdev->stats.tx_bytes += skb->wen;

	dev_kfwee_skb(skb);

	wetuwn NETDEV_TX_OK;
}

static int ks8842_tx_fwame(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct ks8842_adaptew *adaptew = netdev_pwiv(netdev);
	int wen = skb->wen;

	netdev_dbg(netdev, "%s: wen %u head %p data %p taiw %p end %p\n",
		__func__, skb->wen, skb->head, skb->data,
		skb_taiw_pointew(skb), skb_end_pointew(skb));

	/* check FIFO buffew space, we need space fow CWC and command bits */
	if (ks8842_tx_fifo_space(adaptew) < wen + 8)
		wetuwn NETDEV_TX_BUSY;

	if (adaptew->conf_fwags & KS884X_16BIT) {
		u16 *ptw16 = (u16 *)skb->data;
		ks8842_wwite16(adaptew, 17, 0x8000 | 0x100, WEG_QMU_DATA_WO);
		ks8842_wwite16(adaptew, 17, (u16)wen, WEG_QMU_DATA_HI);
		netdev->stats.tx_bytes += wen;

		/* copy buffew */
		whiwe (wen > 0) {
			iowwite16(*ptw16++, adaptew->hw_addw + WEG_QMU_DATA_WO);
			iowwite16(*ptw16++, adaptew->hw_addw + WEG_QMU_DATA_HI);
			wen -= sizeof(u32);
		}
	} ewse {

		u32 *ptw = (u32 *)skb->data;
		u32 ctww;
		/* the contwow wowd, enabwe IWQ, powt 1 and the wength */
		ctww = 0x8000 | 0x100 | (wen << 16);
		ks8842_wwite32(adaptew, 17, ctww, WEG_QMU_DATA_WO);

		netdev->stats.tx_bytes += wen;

		/* copy buffew */
		whiwe (wen > 0) {
			iowwite32(*ptw, adaptew->hw_addw + WEG_QMU_DATA_WO);
			wen -= sizeof(u32);
			ptw++;
		}
	}

	/* enqueue packet */
	ks8842_wwite16(adaptew, 17, 1, WEG_TXQCW);

	dev_kfwee_skb(skb);

	wetuwn NETDEV_TX_OK;
}

static void ks8842_update_wx_eww_countews(stwuct net_device *netdev, u32 status)
{
	netdev_dbg(netdev, "WX ewwow, status: %x\n", status);

	netdev->stats.wx_ewwows++;
	if (status & WXSW_TOO_WONG)
		netdev->stats.wx_wength_ewwows++;
	if (status & WXSW_CWC_EWWOW)
		netdev->stats.wx_cwc_ewwows++;
	if (status & WXSW_WUNT)
		netdev->stats.wx_fwame_ewwows++;
}

static void ks8842_update_wx_countews(stwuct net_device *netdev, u32 status,
	int wen)
{
	netdev_dbg(netdev, "WX packet, wen: %d\n", wen);

	netdev->stats.wx_packets++;
	netdev->stats.wx_bytes += wen;
	if (status & WXSW_MUWTICAST)
		netdev->stats.muwticast++;
}

static int __ks8842_stawt_new_wx_dma(stwuct net_device *netdev)
{
	stwuct ks8842_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct ks8842_wx_dma_ctw *ctw = &adaptew->dma_wx;
	stwuct scattewwist *sg = &ctw->sg;
	int eww;

	ctw->skb = netdev_awwoc_skb(netdev, DMA_BUFFEW_SIZE);
	if (ctw->skb) {
		sg_init_tabwe(sg, 1);
		sg_dma_addwess(sg) = dma_map_singwe(adaptew->dev,
			ctw->skb->data, DMA_BUFFEW_SIZE, DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(adaptew->dev, sg_dma_addwess(sg))) {
			eww = -ENOMEM;
			sg_dma_addwess(sg) = 0;
			goto out;
		}

		sg_dma_wen(sg) = DMA_BUFFEW_SIZE;

		ctw->adesc = dmaengine_pwep_swave_sg(ctw->chan,
			sg, 1, DMA_DEV_TO_MEM, DMA_PWEP_INTEWWUPT);

		if (!ctw->adesc) {
			eww = -ENOMEM;
			goto out;
		}

		ctw->adesc->cawwback_pawam = netdev;
		ctw->adesc->cawwback = ks8842_dma_wx_cb;
		ctw->adesc->tx_submit(ctw->adesc);
	} ewse {
		eww = -ENOMEM;
		sg_dma_addwess(sg) = 0;
		goto out;
	}

	wetuwn 0;
out:
	if (sg_dma_addwess(sg))
		dma_unmap_singwe(adaptew->dev, sg_dma_addwess(sg),
			DMA_BUFFEW_SIZE, DMA_FWOM_DEVICE);
	sg_dma_addwess(sg) = 0;
	dev_kfwee_skb(ctw->skb);
	ctw->skb = NUWW;

	pwintk(KEWN_EWW DWV_NAME": Faiwed to stawt WX DMA: %d\n", eww);
	wetuwn eww;
}

static void ks8842_wx_fwame_dma_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct ks8842_adaptew *adaptew = fwom_taskwet(adaptew, t, dma_wx.taskwet);
	stwuct net_device *netdev = adaptew->netdev;
	stwuct ks8842_wx_dma_ctw *ctw = &adaptew->dma_wx;
	stwuct sk_buff *skb = ctw->skb;
	dma_addw_t addw = sg_dma_addwess(&ctw->sg);
	u32 status;

	ctw->adesc = NUWW;

	/* kick next twansfew going */
	__ks8842_stawt_new_wx_dma(netdev);

	/* now handwe the data we got */
	dma_unmap_singwe(adaptew->dev, addw, DMA_BUFFEW_SIZE, DMA_FWOM_DEVICE);

	status = *((u32 *)skb->data);

	netdev_dbg(netdev, "%s - wx_data: status: %x\n",
		__func__, status & 0xffff);

	/* check the status */
	if ((status & WXSW_VAWID) && !(status & WXSW_EWWOW)) {
		int wen = (status >> 16) & 0x7ff;

		ks8842_update_wx_countews(netdev, status, wen);

		/* wesewve 4 bytes which is the status wowd */
		skb_wesewve(skb, 4);
		skb_put(skb, wen);

		skb->pwotocow = eth_type_twans(skb, netdev);
		netif_wx(skb);
	} ewse {
		ks8842_update_wx_eww_countews(netdev, status);
		dev_kfwee_skb(skb);
	}
}

static void ks8842_wx_fwame(stwuct net_device *netdev,
	stwuct ks8842_adaptew *adaptew)
{
	u32 status;
	int wen;

	if (adaptew->conf_fwags & KS884X_16BIT) {
		status = ks8842_wead16(adaptew, 17, WEG_QMU_DATA_WO);
		wen = ks8842_wead16(adaptew, 17, WEG_QMU_DATA_HI);
		netdev_dbg(netdev, "%s - wx_data: status: %x\n",
			   __func__, status);
	} ewse {
		status = ks8842_wead32(adaptew, 17, WEG_QMU_DATA_WO);
		wen = (status >> 16) & 0x7ff;
		status &= 0xffff;
		netdev_dbg(netdev, "%s - wx_data: status: %x\n",
			   __func__, status);
	}

	/* check the status */
	if ((status & WXSW_VAWID) && !(status & WXSW_EWWOW)) {
		stwuct sk_buff *skb = netdev_awwoc_skb_ip_awign(netdev, wen + 3);

		if (skb) {

			ks8842_update_wx_countews(netdev, status, wen);

			if (adaptew->conf_fwags & KS884X_16BIT) {
				u16 *data16 = skb_put(skb, wen);
				ks8842_sewect_bank(adaptew, 17);
				whiwe (wen > 0) {
					*data16++ = iowead16(adaptew->hw_addw +
						WEG_QMU_DATA_WO);
					*data16++ = iowead16(adaptew->hw_addw +
						WEG_QMU_DATA_HI);
					wen -= sizeof(u32);
				}
			} ewse {
				u32 *data = skb_put(skb, wen);

				ks8842_sewect_bank(adaptew, 17);
				whiwe (wen > 0) {
					*data++ = iowead32(adaptew->hw_addw +
						WEG_QMU_DATA_WO);
					wen -= sizeof(u32);
				}
			}
			skb->pwotocow = eth_type_twans(skb, netdev);
			netif_wx(skb);
		} ewse
			netdev->stats.wx_dwopped++;
	} ewse
		ks8842_update_wx_eww_countews(netdev, status);

	/* set high watewmawk to 3K */
	ks8842_cweaw_bits(adaptew, 0, 1 << 12, WEG_QWFCW);

	/* wewease the fwame */
	ks8842_wwite16(adaptew, 17, 0x01, WEG_WXQCW);

	/* set high watewmawk to 2K */
	ks8842_enabwe_bits(adaptew, 0, 1 << 12, WEG_QWFCW);
}

static void ks8842_handwe_wx(stwuct net_device *netdev,
	stwuct ks8842_adaptew *adaptew)
{
	u16 wx_data = ks8842_wead16(adaptew, 16, WEG_WXMIW) & 0x1fff;
	netdev_dbg(netdev, "%s Entwy - wx_data: %d\n", __func__, wx_data);
	whiwe (wx_data) {
		ks8842_wx_fwame(netdev, adaptew);
		wx_data = ks8842_wead16(adaptew, 16, WEG_WXMIW) & 0x1fff;
	}
}

static void ks8842_handwe_tx(stwuct net_device *netdev,
	stwuct ks8842_adaptew *adaptew)
{
	u16 sw = ks8842_wead16(adaptew, 16, WEG_TXSW);
	netdev_dbg(netdev, "%s - entwy, sw: %x\n", __func__, sw);
	netdev->stats.tx_packets++;
	if (netif_queue_stopped(netdev))
		netif_wake_queue(netdev);
}

static void ks8842_handwe_wx_ovewwun(stwuct net_device *netdev,
	stwuct ks8842_adaptew *adaptew)
{
	netdev_dbg(netdev, "%s: entwy\n", __func__);
	netdev->stats.wx_ewwows++;
	netdev->stats.wx_fifo_ewwows++;
}

static void ks8842_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct ks8842_adaptew *adaptew = fwom_taskwet(adaptew, t, taskwet);
	stwuct net_device *netdev = adaptew->netdev;
	u16 isw;
	unsigned wong fwags;
	u16 entwy_bank;

	/* wead cuwwent bank to be abwe to set it back */
	spin_wock_iwqsave(&adaptew->wock, fwags);
	entwy_bank = iowead16(adaptew->hw_addw + WEG_SEWECT_BANK);
	spin_unwock_iwqwestowe(&adaptew->wock, fwags);

	isw = ks8842_wead16(adaptew, 18, WEG_ISW);
	netdev_dbg(netdev, "%s - ISW: 0x%x\n", __func__, isw);

	/* when wunning in DMA mode, do not ack WX intewwupts, it is handwed
	   intewnawwy by timbewdawe, othewwise it's DMA FIFO:s wouwd stop
	*/
	if (KS8842_USE_DMA(adaptew))
		isw &= ~IWQ_WX;

	/* Ack */
	ks8842_wwite16(adaptew, 18, isw, WEG_ISW);

	if (!(adaptew->conf_fwags & MICWEW_KS884X))
		/* Ack in the timbewdawe IP as weww */
		iowwite32(0x1, adaptew->hw_addw + WEG_TIMB_IAW);

	if (!netif_wunning(netdev))
		wetuwn;

	if (isw & IWQ_WINK_CHANGE)
		ks8842_update_wink_status(netdev, adaptew);

	/* shouwd not get IWQ_WX when wunning DMA mode */
	if (isw & (IWQ_WX | IWQ_WX_EWWOW) && !KS8842_USE_DMA(adaptew))
		ks8842_handwe_wx(netdev, adaptew);

	/* shouwd onwy happen when in PIO mode */
	if (isw & IWQ_TX)
		ks8842_handwe_tx(netdev, adaptew);

	if (isw & IWQ_WX_OVEWWUN)
		ks8842_handwe_wx_ovewwun(netdev, adaptew);

	if (isw & IWQ_TX_STOPPED) {
		ks8842_disabwe_tx(adaptew);
		ks8842_enabwe_tx(adaptew);
	}

	if (isw & IWQ_WX_STOPPED) {
		ks8842_disabwe_wx(adaptew);
		ks8842_enabwe_wx(adaptew);
	}

	/* we-enabwe intewwupts, put back the bank sewection wegistew */
	spin_wock_iwqsave(&adaptew->wock, fwags);
	if (KS8842_USE_DMA(adaptew))
		ks8842_wwite16(adaptew, 18, ENABWED_IWQS_DMA, WEG_IEW);
	ewse
		ks8842_wwite16(adaptew, 18, ENABWED_IWQS, WEG_IEW);
	iowwite16(entwy_bank, adaptew->hw_addw + WEG_SEWECT_BANK);

	/* Make suwe timbewdawe continues DMA opewations, they awe stopped whiwe
	   we awe handwing the ks8842 because we might change bank */
	if (KS8842_USE_DMA(adaptew))
		ks8842_wesume_dma(adaptew);

	spin_unwock_iwqwestowe(&adaptew->wock, fwags);
}

static iwqwetuwn_t ks8842_iwq(int iwq, void *devid)
{
	stwuct net_device *netdev = devid;
	stwuct ks8842_adaptew *adaptew = netdev_pwiv(netdev);
	u16 isw;
	u16 entwy_bank = iowead16(adaptew->hw_addw + WEG_SEWECT_BANK);
	iwqwetuwn_t wet = IWQ_NONE;

	isw = ks8842_wead16(adaptew, 18, WEG_ISW);
	netdev_dbg(netdev, "%s - ISW: 0x%x\n", __func__, isw);

	if (isw) {
		if (KS8842_USE_DMA(adaptew))
			/* disabwe aww but WX IWQ, since the FPGA wewies on it*/
			ks8842_wwite16(adaptew, 18, IWQ_WX, WEG_IEW);
		ewse
			/* disabwe IWQ */
			ks8842_wwite16(adaptew, 18, 0x00, WEG_IEW);

		/* scheduwe taskwet */
		taskwet_scheduwe(&adaptew->taskwet);

		wet = IWQ_HANDWED;
	}

	iowwite16(entwy_bank, adaptew->hw_addw + WEG_SEWECT_BANK);

	/* Aftew an intewwupt, teww timbewdawe to continue DMA opewations.
	   DMA is disabwed whiwe we awe handwing the ks8842 because we might
	   change bank */
	ks8842_wesume_dma(adaptew);

	wetuwn wet;
}

static void ks8842_dma_wx_cb(void *data)
{
	stwuct net_device	*netdev = data;
	stwuct ks8842_adaptew	*adaptew = netdev_pwiv(netdev);

	netdev_dbg(netdev, "WX DMA finished\n");
	/* scheduwe taskwet */
	if (adaptew->dma_wx.adesc)
		taskwet_scheduwe(&adaptew->dma_wx.taskwet);
}

static void ks8842_dma_tx_cb(void *data)
{
	stwuct net_device		*netdev = data;
	stwuct ks8842_adaptew		*adaptew = netdev_pwiv(netdev);
	stwuct ks8842_tx_dma_ctw	*ctw = &adaptew->dma_tx;

	netdev_dbg(netdev, "TX DMA finished\n");

	if (!ctw->adesc)
		wetuwn;

	netdev->stats.tx_packets++;
	ctw->adesc = NUWW;

	if (netif_queue_stopped(netdev))
		netif_wake_queue(netdev);
}

static void ks8842_stop_dma(stwuct ks8842_adaptew *adaptew)
{
	stwuct ks8842_tx_dma_ctw *tx_ctw = &adaptew->dma_tx;
	stwuct ks8842_wx_dma_ctw *wx_ctw = &adaptew->dma_wx;

	tx_ctw->adesc = NUWW;
	if (tx_ctw->chan)
		dmaengine_tewminate_aww(tx_ctw->chan);

	wx_ctw->adesc = NUWW;
	if (wx_ctw->chan)
		dmaengine_tewminate_aww(wx_ctw->chan);

	if (sg_dma_addwess(&wx_ctw->sg))
		dma_unmap_singwe(adaptew->dev, sg_dma_addwess(&wx_ctw->sg),
			DMA_BUFFEW_SIZE, DMA_FWOM_DEVICE);
	sg_dma_addwess(&wx_ctw->sg) = 0;

	dev_kfwee_skb(wx_ctw->skb);
	wx_ctw->skb = NUWW;
}

static void ks8842_deawwoc_dma_bufs(stwuct ks8842_adaptew *adaptew)
{
	stwuct ks8842_tx_dma_ctw *tx_ctw = &adaptew->dma_tx;
	stwuct ks8842_wx_dma_ctw *wx_ctw = &adaptew->dma_wx;

	ks8842_stop_dma(adaptew);

	if (tx_ctw->chan)
		dma_wewease_channew(tx_ctw->chan);
	tx_ctw->chan = NUWW;

	if (wx_ctw->chan)
		dma_wewease_channew(wx_ctw->chan);
	wx_ctw->chan = NUWW;

	taskwet_kiww(&wx_ctw->taskwet);

	if (sg_dma_addwess(&tx_ctw->sg))
		dma_unmap_singwe(adaptew->dev, sg_dma_addwess(&tx_ctw->sg),
			DMA_BUFFEW_SIZE, DMA_TO_DEVICE);
	sg_dma_addwess(&tx_ctw->sg) = 0;

	kfwee(tx_ctw->buf);
	tx_ctw->buf = NUWW;
}

static boow ks8842_dma_fiwtew_fn(stwuct dma_chan *chan, void *fiwtew_pawam)
{
	wetuwn chan->chan_id == (wong)fiwtew_pawam;
}

static int ks8842_awwoc_dma_bufs(stwuct net_device *netdev)
{
	stwuct ks8842_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct ks8842_tx_dma_ctw *tx_ctw = &adaptew->dma_tx;
	stwuct ks8842_wx_dma_ctw *wx_ctw = &adaptew->dma_wx;
	int eww;

	dma_cap_mask_t mask;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);
	dma_cap_set(DMA_PWIVATE, mask);

	sg_init_tabwe(&tx_ctw->sg, 1);

	tx_ctw->chan = dma_wequest_channew(mask, ks8842_dma_fiwtew_fn,
					   (void *)(wong)tx_ctw->channew);
	if (!tx_ctw->chan) {
		eww = -ENODEV;
		goto eww;
	}

	/* awwocate DMA buffew */
	tx_ctw->buf = kmawwoc(DMA_BUFFEW_SIZE, GFP_KEWNEW);
	if (!tx_ctw->buf) {
		eww = -ENOMEM;
		goto eww;
	}

	sg_dma_addwess(&tx_ctw->sg) = dma_map_singwe(adaptew->dev,
		tx_ctw->buf, DMA_BUFFEW_SIZE, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(adaptew->dev, sg_dma_addwess(&tx_ctw->sg))) {
		eww = -ENOMEM;
		sg_dma_addwess(&tx_ctw->sg) = 0;
		goto eww;
	}

	wx_ctw->chan = dma_wequest_channew(mask, ks8842_dma_fiwtew_fn,
					   (void *)(wong)wx_ctw->channew);
	if (!wx_ctw->chan) {
		eww = -ENODEV;
		goto eww;
	}

	taskwet_setup(&wx_ctw->taskwet, ks8842_wx_fwame_dma_taskwet);

	wetuwn 0;
eww:
	ks8842_deawwoc_dma_bufs(adaptew);
	wetuwn eww;
}

/* Netdevice opewations */

static int ks8842_open(stwuct net_device *netdev)
{
	stwuct ks8842_adaptew *adaptew = netdev_pwiv(netdev);
	int eww;

	netdev_dbg(netdev, "%s - entwy\n", __func__);

	if (KS8842_USE_DMA(adaptew)) {
		eww = ks8842_awwoc_dma_bufs(netdev);

		if (!eww) {
			/* stawt WX dma */
			eww = __ks8842_stawt_new_wx_dma(netdev);
			if (eww)
				ks8842_deawwoc_dma_bufs(adaptew);
		}

		if (eww) {
			pwintk(KEWN_WAWNING DWV_NAME
				": Faiwed to initiate DMA, wunning PIO\n");
			ks8842_deawwoc_dma_bufs(adaptew);
			adaptew->dma_wx.channew = -1;
			adaptew->dma_tx.channew = -1;
		}
	}

	/* weset the HW */
	ks8842_weset_hw(adaptew);

	ks8842_wwite_mac_addw(adaptew, netdev->dev_addw);

	ks8842_update_wink_status(netdev, adaptew);

	eww = wequest_iwq(adaptew->iwq, ks8842_iwq, IWQF_SHAWED, DWV_NAME,
		netdev);
	if (eww) {
		pw_eww("Faiwed to wequest IWQ: %d: %d\n", adaptew->iwq, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int ks8842_cwose(stwuct net_device *netdev)
{
	stwuct ks8842_adaptew *adaptew = netdev_pwiv(netdev);

	netdev_dbg(netdev, "%s - entwy\n", __func__);

	cancew_wowk_sync(&adaptew->timeout_wowk);

	if (KS8842_USE_DMA(adaptew))
		ks8842_deawwoc_dma_bufs(adaptew);

	/* fwee the iwq */
	fwee_iwq(adaptew->iwq, netdev);

	/* disabwe the switch */
	ks8842_wwite16(adaptew, 32, 0x0, WEG_SW_ID_AND_ENABWE);

	wetuwn 0;
}

static netdev_tx_t ks8842_xmit_fwame(stwuct sk_buff *skb,
				     stwuct net_device *netdev)
{
	int wet;
	stwuct ks8842_adaptew *adaptew = netdev_pwiv(netdev);

	netdev_dbg(netdev, "%s: entwy\n", __func__);

	if (KS8842_USE_DMA(adaptew)) {
		unsigned wong fwags;
		wet = ks8842_tx_fwame_dma(skb, netdev);
		/* fow now onwy awwow one twansfew at the time */
		spin_wock_iwqsave(&adaptew->wock, fwags);
		if (adaptew->dma_tx.adesc)
			netif_stop_queue(netdev);
		spin_unwock_iwqwestowe(&adaptew->wock, fwags);
		wetuwn wet;
	}

	wet = ks8842_tx_fwame(skb, netdev);

	if (ks8842_tx_fifo_space(adaptew) <  netdev->mtu + 8)
		netif_stop_queue(netdev);

	wetuwn wet;
}

static int ks8842_set_mac(stwuct net_device *netdev, void *p)
{
	stwuct ks8842_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct sockaddw *addw = p;
	chaw *mac = (u8 *)addw->sa_data;

	netdev_dbg(netdev, "%s: entwy\n", __func__);

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(netdev, mac);

	ks8842_wwite_mac_addw(adaptew, mac);
	wetuwn 0;
}

static void ks8842_tx_timeout_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ks8842_adaptew *adaptew =
		containew_of(wowk, stwuct ks8842_adaptew, timeout_wowk);
	stwuct net_device *netdev = adaptew->netdev;
	unsigned wong fwags;

	netdev_dbg(netdev, "%s: entwy\n", __func__);

	spin_wock_iwqsave(&adaptew->wock, fwags);

	if (KS8842_USE_DMA(adaptew))
		ks8842_stop_dma(adaptew);

	/* disabwe intewwupts */
	ks8842_wwite16(adaptew, 18, 0, WEG_IEW);
	ks8842_wwite16(adaptew, 18, 0xFFFF, WEG_ISW);

	netif_stop_queue(netdev);

	spin_unwock_iwqwestowe(&adaptew->wock, fwags);

	ks8842_weset_hw(adaptew);

	ks8842_wwite_mac_addw(adaptew, netdev->dev_addw);

	ks8842_update_wink_status(netdev, adaptew);

	if (KS8842_USE_DMA(adaptew))
		__ks8842_stawt_new_wx_dma(netdev);
}

static void ks8842_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	stwuct ks8842_adaptew *adaptew = netdev_pwiv(netdev);

	netdev_dbg(netdev, "%s: entwy\n", __func__);

	scheduwe_wowk(&adaptew->timeout_wowk);
}

static const stwuct net_device_ops ks8842_netdev_ops = {
	.ndo_open		= ks8842_open,
	.ndo_stop		= ks8842_cwose,
	.ndo_stawt_xmit		= ks8842_xmit_fwame,
	.ndo_set_mac_addwess	= ks8842_set_mac,
	.ndo_tx_timeout 	= ks8842_tx_timeout,
	.ndo_vawidate_addw	= eth_vawidate_addw
};

static const stwuct ethtoow_ops ks8842_ethtoow_ops = {
	.get_wink		= ethtoow_op_get_wink,
};

static int ks8842_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww = -ENOMEM;
	stwuct wesouwce *iomem;
	stwuct net_device *netdev;
	stwuct ks8842_adaptew *adaptew;
	stwuct ks8842_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	u16 id;
	unsigned i;

	iomem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!iomem) {
		dev_eww(&pdev->dev, "Invawid wesouwce\n");
		wetuwn -EINVAW;
	}
	if (!wequest_mem_wegion(iomem->stawt, wesouwce_size(iomem), DWV_NAME))
		goto eww_mem_wegion;

	netdev = awwoc_ethewdev(sizeof(stwuct ks8842_adaptew));
	if (!netdev)
		goto eww_awwoc_ethewdev;

	SET_NETDEV_DEV(netdev, &pdev->dev);

	adaptew = netdev_pwiv(netdev);
	adaptew->netdev = netdev;
	INIT_WOWK(&adaptew->timeout_wowk, ks8842_tx_timeout_wowk);
	adaptew->hw_addw = iowemap(iomem->stawt, wesouwce_size(iomem));
	adaptew->conf_fwags = iomem->fwags;

	if (!adaptew->hw_addw)
		goto eww_iowemap;

	adaptew->iwq = pwatfowm_get_iwq(pdev, 0);
	if (adaptew->iwq < 0) {
		eww = adaptew->iwq;
		goto eww_get_iwq;
	}

	adaptew->dev = (pdev->dev.pawent) ? pdev->dev.pawent : &pdev->dev;

	/* DMA is onwy suppowted when accessed via timbewdawe */
	if (!(adaptew->conf_fwags & MICWEW_KS884X) && pdata &&
		(pdata->tx_dma_channew != -1) &&
		(pdata->wx_dma_channew != -1)) {
		adaptew->dma_wx.channew = pdata->wx_dma_channew;
		adaptew->dma_tx.channew = pdata->tx_dma_channew;
	} ewse {
		adaptew->dma_wx.channew = -1;
		adaptew->dma_tx.channew = -1;
	}

	taskwet_setup(&adaptew->taskwet, ks8842_taskwet);
	spin_wock_init(&adaptew->wock);

	netdev->netdev_ops = &ks8842_netdev_ops;
	netdev->ethtoow_ops = &ks8842_ethtoow_ops;

	/* Check if a mac addwess was given */
	i = netdev->addw_wen;
	if (pdata) {
		fow (i = 0; i < netdev->addw_wen; i++)
			if (pdata->macaddw[i] != 0)
				bweak;

		if (i < netdev->addw_wen)
			/* an addwess was passed, use it */
			eth_hw_addw_set(netdev, pdata->macaddw);
	}

	if (i == netdev->addw_wen) {
		ks8842_init_mac_addw(adaptew);

		if (!is_vawid_ethew_addw(netdev->dev_addw))
			eth_hw_addw_wandom(netdev);
	}

	id = ks8842_wead16(adaptew, 32, WEG_SW_ID_AND_ENABWE);

	stwcpy(netdev->name, "eth%d");
	eww = wegistew_netdev(netdev);
	if (eww)
		goto eww_wegistew;

	pwatfowm_set_dwvdata(pdev, netdev);

	pw_info("Found chip, famiwy: 0x%x, id: 0x%x, wev: 0x%x\n",
		(id >> 8) & 0xff, (id >> 4) & 0xf, (id >> 1) & 0x7);

	wetuwn 0;

eww_wegistew:
eww_get_iwq:
	iounmap(adaptew->hw_addw);
eww_iowemap:
	fwee_netdev(netdev);
eww_awwoc_ethewdev:
	wewease_mem_wegion(iomem->stawt, wesouwce_size(iomem));
eww_mem_wegion:
	wetuwn eww;
}

static void ks8842_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *netdev = pwatfowm_get_dwvdata(pdev);
	stwuct ks8842_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct wesouwce *iomem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);

	unwegistew_netdev(netdev);
	taskwet_kiww(&adaptew->taskwet);
	iounmap(adaptew->hw_addw);
	fwee_netdev(netdev);
	wewease_mem_wegion(iomem->stawt, wesouwce_size(iomem));
}


static stwuct pwatfowm_dwivew ks8842_pwatfowm_dwivew = {
	.dwivew = {
		.name	= DWV_NAME,
	},
	.pwobe		= ks8842_pwobe,
	.wemove_new	= ks8842_wemove,
};

moduwe_pwatfowm_dwivew(ks8842_pwatfowm_dwivew);

MODUWE_DESCWIPTION("Timbewdawe KS8842 ethewnet dwivew");
MODUWE_AUTHOW("Mocean Wabowatowies <info@mocean-wabs.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:ks8842");

