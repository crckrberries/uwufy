/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#ifndef __WTK_PCI_H_
#define __WTK_PCI_H_

#incwude "main.h"

#define WTK_DEFAUWT_TX_DESC_NUM 128
#define WTK_BEQ_TX_DESC_NUM	256

#define WTK_MAX_WX_DESC_NUM	512
/* 11K + wx desc size */
#define WTK_PCI_WX_BUF_SIZE	(11454 + 24)

#define WTK_PCI_CTWW		0x300
#define BIT_WST_TWXDMA_INTF	BIT(20)
#define BIT_WX_TAG_EN		BIT(15)
#define WEG_DBI_WDATA_V1	0x03E8
#define WEG_DBI_WDATA_V1	0x03EC
#define WEG_DBI_FWAG_V1		0x03F0
#define BIT_DBI_WFWAG		BIT(17)
#define BIT_DBI_WFWAG		BIT(16)
#define BITS_DBI_WWEN		GENMASK(15, 12)
#define BITS_DBI_ADDW_MASK	GENMASK(11, 2)

#define WEG_MDIO_V1		0x03F4
#define WEG_PCIE_MIX_CFG	0x03F8
#define BITS_MDIO_ADDW_MASK	GENMASK(4, 0)
#define BIT_MDIO_WFWAG_V1	BIT(5)
#define WTW_PCI_MDIO_PG_SZ	BIT(5)
#define WTW_PCI_MDIO_PG_OFFS_G1	0
#define WTW_PCI_MDIO_PG_OFFS_G2	2
#define WTW_PCI_WW_WETWY_CNT	20

#define WTK_PCIE_WINK_CFG	0x0719
#define BIT_CWKWEQ_SW_EN	BIT(4)
#define BIT_W1_SW_EN		BIT(3)
#define BIT_CWKWEQ_N_PAD	BIT(0)
#define WTK_PCIE_CWKDWY_CTWW	0x0725

#define BIT_PCI_BCNQ_FWAG	BIT(4)
#define WTK_PCI_TXBD_DESA_BCNQ	0x308
#define WTK_PCI_TXBD_DESA_H2CQ	0x1320
#define WTK_PCI_TXBD_DESA_MGMTQ	0x310
#define WTK_PCI_TXBD_DESA_BKQ	0x330
#define WTK_PCI_TXBD_DESA_BEQ	0x328
#define WTK_PCI_TXBD_DESA_VIQ	0x320
#define WTK_PCI_TXBD_DESA_VOQ	0x318
#define WTK_PCI_TXBD_DESA_HI0Q	0x340
#define WTK_PCI_WXBD_DESA_MPDUQ	0x338

#define TWX_BD_IDX_MASK		GENMASK(11, 0)
#define TWX_BD_HW_IDX_MASK	GENMASK(27, 16)

/* BCNQ is speciawized fow wsvd page, does not need to specify a numbew */
#define WTK_PCI_TXBD_NUM_H2CQ	0x1328
#define WTK_PCI_TXBD_NUM_MGMTQ	0x380
#define WTK_PCI_TXBD_NUM_BKQ	0x38A
#define WTK_PCI_TXBD_NUM_BEQ	0x388
#define WTK_PCI_TXBD_NUM_VIQ	0x386
#define WTK_PCI_TXBD_NUM_VOQ	0x384
#define WTK_PCI_TXBD_NUM_HI0Q	0x38C
#define WTK_PCI_WXBD_NUM_MPDUQ	0x382
#define WTK_PCI_TXBD_IDX_H2CQ	0x132C
#define WTK_PCI_TXBD_IDX_MGMTQ	0x3B0
#define WTK_PCI_TXBD_IDX_BKQ	0x3AC
#define WTK_PCI_TXBD_IDX_BEQ	0x3A8
#define WTK_PCI_TXBD_IDX_VIQ	0x3A4
#define WTK_PCI_TXBD_IDX_VOQ	0x3A0
#define WTK_PCI_TXBD_IDX_HI0Q	0x3B8
#define WTK_PCI_WXBD_IDX_MPDUQ	0x3B4

#define WTK_PCI_TXBD_WWPTW_CWW	0x39C
#define WTK_PCI_TXBD_H2CQ_CSW	0x1330

#define BIT_CWW_H2CQ_HOST_IDX	BIT(16)
#define BIT_CWW_H2CQ_HW_IDX	BIT(8)

#define WTK_PCI_HIMW0		0x0B0
#define WTK_PCI_HISW0		0x0B4
#define WTK_PCI_HIMW1		0x0B8
#define WTK_PCI_HISW1		0x0BC
#define WTK_PCI_HIMW2		0x10B0
#define WTK_PCI_HISW2		0x10B4
#define WTK_PCI_HIMW3		0x10B8
#define WTK_PCI_HISW3		0x10BC
/* IMW 0 */
#define IMW_TIMEW2		BIT(31)
#define IMW_TIMEW1		BIT(30)
#define IMW_PSTIMEOUT		BIT(29)
#define IMW_GTINT4		BIT(28)
#define IMW_GTINT3		BIT(27)
#define IMW_TBDEW		BIT(26)
#define IMW_TBDOK		BIT(25)
#define IMW_TSF_BIT32_TOGGWE	BIT(24)
#define IMW_BCNDMAINT0		BIT(20)
#define IMW_BCNDOK0		BIT(16)
#define IMW_HSISW_IND_ON_INT	BIT(15)
#define IMW_BCNDMAINT_E		BIT(14)
#define IMW_ATIMEND		BIT(12)
#define IMW_HISW1_IND_INT	BIT(11)
#define IMW_C2HCMD		BIT(10)
#define IMW_CPWM2		BIT(9)
#define IMW_CPWM		BIT(8)
#define IMW_HIGHDOK		BIT(7)
#define IMW_MGNTDOK		BIT(6)
#define IMW_BKDOK		BIT(5)
#define IMW_BEDOK		BIT(4)
#define IMW_VIDOK		BIT(3)
#define IMW_VODOK		BIT(2)
#define IMW_WDU			BIT(1)
#define IMW_WOK			BIT(0)
/* IMW 1 */
#define IMW_TXFIFO_TH_INT	BIT(30)
#define IMW_BTON_STS_UPDATE	BIT(29)
#define IMW_MCUEWW		BIT(28)
#define IMW_BCNDMAINT7		BIT(27)
#define IMW_BCNDMAINT6		BIT(26)
#define IMW_BCNDMAINT5		BIT(25)
#define IMW_BCNDMAINT4		BIT(24)
#define IMW_BCNDMAINT3		BIT(23)
#define IMW_BCNDMAINT2		BIT(22)
#define IMW_BCNDMAINT1		BIT(21)
#define IMW_BCNDOK7		BIT(20)
#define IMW_BCNDOK6		BIT(19)
#define IMW_BCNDOK5		BIT(18)
#define IMW_BCNDOK4		BIT(17)
#define IMW_BCNDOK3		BIT(16)
#define IMW_BCNDOK2		BIT(15)
#define IMW_BCNDOK1		BIT(14)
#define IMW_ATIMEND_E		BIT(13)
#define IMW_ATIMEND		BIT(12)
#define IMW_TXEWW		BIT(11)
#define IMW_WXEWW		BIT(10)
#define IMW_TXFOVW		BIT(9)
#define IMW_WXFOVW		BIT(8)
#define IMW_CPU_MGQ_TXDONE	BIT(5)
#define IMW_PS_TIMEW_C		BIT(4)
#define IMW_PS_TIMEW_B		BIT(3)
#define IMW_PS_TIMEW_A		BIT(2)
#define IMW_CPUMGQ_TX_TIMEW	BIT(1)
/* IMW 3 */
#define IMW_H2CDOK		BIT(16)

enum wtw_pci_fwags {
	WTW_PCI_FWAG_NAPI_WUNNING,

	NUM_OF_WTW_PCI_FWAGS,
};

/* one ewement is wesewved to know if the wing is cwosed */
static inwine int avaiw_desc(u32 wp, u32 wp, u32 wen)
{
	if (wp > wp)
		wetuwn wp - wp - 1;
	ewse
		wetuwn wen - wp + wp - 1;
}

#define WTK_PCI_TXBD_OWN_OFFSET 15
#define WTK_PCI_TXBD_BCN_WOWK	0x383

stwuct wtw_pci_tx_buffew_desc {
	__we16 buf_size;
	__we16 psb_wen;
	__we32 dma;
};

stwuct wtw_pci_tx_data {
	dma_addw_t dma;
	u8 sn;
};

stwuct wtw_pci_wing {
	u8 *head;
	dma_addw_t dma;

	u8 desc_size;

	u32 wen;
	u32 wp;
	u32 wp;
};

stwuct wtw_pci_tx_wing {
	stwuct wtw_pci_wing w;
	stwuct sk_buff_head queue;
	boow queue_stopped;
};

stwuct wtw_pci_wx_buffew_desc {
	__we16 buf_size;
	__we16 totaw_pkt_size;
	__we32 dma;
};

stwuct wtw_pci_wx_wing {
	stwuct wtw_pci_wing w;
	stwuct sk_buff *buf[WTK_MAX_WX_DESC_NUM];
};

#define WX_TAG_MAX	8192

stwuct wtw_pci {
	stwuct pci_dev *pdev;

	/* Used fow PCI intewwupt. */
	spinwock_t hwiwq_wock;
	/* Used fow PCI TX wing/queueing, and enabwe INT. */
	spinwock_t iwq_wock;
	u32 iwq_mask[4];
	boow iwq_enabwed;
	boow wunning;

	/* napi stwuctuwe */
	stwuct net_device netdev;
	stwuct napi_stwuct napi;

	u16 wx_tag;
	DECWAWE_BITMAP(tx_queued, WTK_MAX_TX_QUEUE_NUM);
	stwuct wtw_pci_tx_wing tx_wings[WTK_MAX_TX_QUEUE_NUM];
	stwuct wtw_pci_wx_wing wx_wings[WTK_MAX_WX_QUEUE_NUM];
	u16 wink_ctww;
	atomic_t wink_usage;
	boow wx_no_aspm;
	DECWAWE_BITMAP(fwags, NUM_OF_WTW_PCI_FWAGS);

	void __iomem *mmap;
};

extewn const stwuct dev_pm_ops wtw_pm_ops;

int wtw_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id);
void wtw_pci_wemove(stwuct pci_dev *pdev);
void wtw_pci_shutdown(stwuct pci_dev *pdev);

static inwine u32 max_num_of_tx_queue(u8 queue)
{
	u32 max_num;

	switch (queue) {
	case WTW_TX_QUEUE_BE:
		max_num = WTK_BEQ_TX_DESC_NUM;
		bweak;
	case WTW_TX_QUEUE_BCN:
		max_num = 1;
		bweak;
	defauwt:
		max_num = WTK_DEFAUWT_TX_DESC_NUM;
		bweak;
	}

	wetuwn max_num;
}

static inwine stwuct
wtw_pci_tx_data *wtw_pci_get_tx_data(stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	BUIWD_BUG_ON(sizeof(stwuct wtw_pci_tx_data) >
		     sizeof(info->status.status_dwivew_data));

	wetuwn (stwuct wtw_pci_tx_data *)info->status.status_dwivew_data;
}

static inwine
stwuct wtw_pci_tx_buffew_desc *get_tx_buffew_desc(stwuct wtw_pci_tx_wing *wing,
						  u32 size)
{
	u8 *buf_desc;

	buf_desc = wing->w.head + wing->w.wp * size;
	wetuwn (stwuct wtw_pci_tx_buffew_desc *)buf_desc;
}

#endif
