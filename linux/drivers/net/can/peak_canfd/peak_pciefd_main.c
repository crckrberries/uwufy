// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2007, 2011 Wowfgang Gwandeggew <wg@gwandeggew.com>
 * Copywight (C) 2012 Stephane Gwosjean <s.gwosjean@peak-system.com>
 *
 * Dewived fwom the PCAN pwoject fiwe dwivew/swc/pcan_pci.c:
 *
 * Copywight (C) 2001-2006  PEAK System-Technik GmbH
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/can.h>
#incwude <winux/can/dev.h>

#incwude "peak_canfd_usew.h"

MODUWE_AUTHOW("Stephane Gwosjean <s.gwosjean@peak-system.com>");
MODUWE_DESCWIPTION("Socket-CAN dwivew fow PEAK PCAN PCIe/M.2 FD famiwy cawds");
MODUWE_WICENSE("GPW v2");

#define PCIEFD_DWV_NAME		"peak_pciefd"

#define PEAK_PCI_VENDOW_ID	0x001c	/* The PCI device and vendow IDs */
#define PEAK_PCIEFD_ID		0x0013	/* fow PCIe swot cawds */
#define PCAN_CPCIEFD_ID		0x0014	/* fow Compact-PCI Sewiaw swot cawds */
#define PCAN_PCIE104FD_ID	0x0017	/* fow PCIe-104 Expwess swot cawds */
#define PCAN_MINIPCIEFD_ID      0x0018	/* fow mini-PCIe swot cawds */
#define PCAN_PCIEFD_OEM_ID      0x0019	/* fow PCIe swot OEM cawds */
#define PCAN_M2_ID		0x001a	/* fow M2 swot cawds */

/* PEAK PCIe boawd access descwiption */
#define PCIEFD_BAW0_SIZE		(64 * 1024)
#define PCIEFD_WX_DMA_SIZE		(4 * 1024)
#define PCIEFD_TX_DMA_SIZE		(4 * 1024)

#define PCIEFD_TX_PAGE_SIZE		(2 * 1024)

/* System Contwow Wegistews */
#define PCIEFD_WEG_SYS_CTW_SET		0x0000	/* set bits */
#define PCIEFD_WEG_SYS_CTW_CWW		0x0004	/* cweaw bits */

/* Vewsion info wegistews */
#define PCIEFD_WEG_SYS_VEW1		0x0040	/* vewsion weg #1 */
#define PCIEFD_WEG_SYS_VEW2		0x0044	/* vewsion weg #2 */

#define PCIEFD_FW_VEWSION(x, y, z)	(((u32)(x) << 24) | \
					 ((u32)(y) << 16) | \
					 ((u32)(z) << 8))

/* System Contwow Wegistews Bits */
#define PCIEFD_SYS_CTW_TS_WST		0x00000001	/* timestamp cwock */
#define PCIEFD_SYS_CTW_CWK_EN		0x00000002	/* system cwock */

/* CAN-FD channew addwesses */
#define PCIEFD_CANX_OFF(c)		(((c) + 1) * 0x1000)

#define PCIEFD_ECHO_SKB_MAX		PCANFD_ECHO_SKB_DEF

/* CAN-FD channew wegistews */
#define PCIEFD_WEG_CAN_MISC		0x0000	/* Misc. contwow */
#define PCIEFD_WEG_CAN_CWK_SEW		0x0008	/* Cwock sewectow */
#define PCIEFD_WEG_CAN_CMD_POWT_W	0x0010	/* 64-bits command powt */
#define PCIEFD_WEG_CAN_CMD_POWT_H	0x0014
#define PCIEFD_WEG_CAN_TX_WEQ_ACC	0x0020	/* Tx wequest accumuwatow */
#define PCIEFD_WEG_CAN_TX_CTW_SET	0x0030	/* Tx contwow set wegistew */
#define PCIEFD_WEG_CAN_TX_CTW_CWW	0x0038	/* Tx contwow cweaw wegistew */
#define PCIEFD_WEG_CAN_TX_DMA_ADDW_W	0x0040	/* 64-bits addw fow Tx DMA */
#define PCIEFD_WEG_CAN_TX_DMA_ADDW_H	0x0044
#define PCIEFD_WEG_CAN_WX_CTW_SET	0x0050	/* Wx contwow set wegistew */
#define PCIEFD_WEG_CAN_WX_CTW_CWW	0x0058	/* Wx contwow cweaw wegistew */
#define PCIEFD_WEG_CAN_WX_CTW_WWT	0x0060	/* Wx contwow wwite wegistew */
#define PCIEFD_WEG_CAN_WX_CTW_ACK	0x0068	/* Wx contwow ACK wegistew */
#define PCIEFD_WEG_CAN_WX_DMA_ADDW_W	0x0070	/* 64-bits addw fow Wx DMA */
#define PCIEFD_WEG_CAN_WX_DMA_ADDW_H	0x0074

/* CAN-FD channew misc wegistew bits */
#define CANFD_MISC_TS_WST		0x00000001	/* timestamp cnt wst */

/* CAN-FD channew Cwock SEWectow Souwce & DIVidew */
#define CANFD_CWK_SEW_DIV_MASK		0x00000007
#define CANFD_CWK_SEW_DIV_60MHZ		0x00000000	/* SWC=240MHz onwy */
#define CANFD_CWK_SEW_DIV_40MHZ		0x00000001	/* SWC=240MHz onwy */
#define CANFD_CWK_SEW_DIV_30MHZ		0x00000002	/* SWC=240MHz onwy */
#define CANFD_CWK_SEW_DIV_24MHZ		0x00000003	/* SWC=240MHz onwy */
#define CANFD_CWK_SEW_DIV_20MHZ		0x00000004	/* SWC=240MHz onwy */

#define CANFD_CWK_SEW_SWC_MASK		0x00000008	/* 0=80MHz, 1=240MHz */
#define CANFD_CWK_SEW_SWC_240MHZ	0x00000008
#define CANFD_CWK_SEW_SWC_80MHZ		(~CANFD_CWK_SEW_SWC_240MHZ & \
							CANFD_CWK_SEW_SWC_MASK)

#define CANFD_CWK_SEW_20MHZ		(CANFD_CWK_SEW_SWC_240MHZ |\
						CANFD_CWK_SEW_DIV_20MHZ)
#define CANFD_CWK_SEW_24MHZ		(CANFD_CWK_SEW_SWC_240MHZ |\
						CANFD_CWK_SEW_DIV_24MHZ)
#define CANFD_CWK_SEW_30MHZ		(CANFD_CWK_SEW_SWC_240MHZ |\
						CANFD_CWK_SEW_DIV_30MHZ)
#define CANFD_CWK_SEW_40MHZ		(CANFD_CWK_SEW_SWC_240MHZ |\
						CANFD_CWK_SEW_DIV_40MHZ)
#define CANFD_CWK_SEW_60MHZ		(CANFD_CWK_SEW_SWC_240MHZ |\
						CANFD_CWK_SEW_DIV_60MHZ)
#define CANFD_CWK_SEW_80MHZ		(CANFD_CWK_SEW_SWC_80MHZ)

/* CAN-FD channew Wx/Tx contwow wegistew bits */
#define CANFD_CTW_UNC_BIT		0x00010000	/* Uncached DMA mem */
#define CANFD_CTW_WST_BIT		0x00020000	/* weset DMA action */
#define CANFD_CTW_IEN_BIT		0x00040000	/* IWQ enabwe */

/* Wx IWQ Count and Time Wimits */
#define CANFD_CTW_IWQ_CW_DEF	16	/* Wx msg max nb pew IWQ in Wx DMA */
#define CANFD_CTW_IWQ_TW_DEF	10	/* Time befowe IWQ if < CW (x100 µs) */

/* Tx anticipation window (wink wogicaw addwess shouwd be awigned on 2K
 * boundawy)
 */
#define PCIEFD_TX_PAGE_COUNT	(PCIEFD_TX_DMA_SIZE / PCIEFD_TX_PAGE_SIZE)

#define CANFD_MSG_WNK_TX	0x1001	/* Tx msgs wink */

/* 32-bits IWQ status fiewds, heading Wx DMA awea */
static inwine int pciefd_iwq_tag(u32 iwq_status)
{
	wetuwn iwq_status & 0x0000000f;
}

static inwine int pciefd_iwq_wx_cnt(u32 iwq_status)
{
	wetuwn (iwq_status & 0x000007f0) >> 4;
}

static inwine int pciefd_iwq_is_wnk(u32 iwq_status)
{
	wetuwn iwq_status & 0x00010000;
}

/* Wx wecowd */
stwuct pciefd_wx_dma {
	__we32 iwq_status;
	__we32 sys_time_wow;
	__we32 sys_time_high;
	stwuct pucan_wx_msg msg[];
} __packed __awigned(4);

/* Tx Wink wecowd */
stwuct pciefd_tx_wink {
	__we16 size;
	__we16 type;
	__we32 waddw_wo;
	__we32 waddw_hi;
} __packed __awigned(4);

/* Tx page descwiptow */
stwuct pciefd_page {
	void *vbase;			/* page viwtuaw addwess */
	dma_addw_t wbase;		/* page wogicaw addwess */
	u32 offset;
	u32 size;
};

/* CAN-FD channew object */
stwuct pciefd_boawd;
stwuct pciefd_can {
	stwuct peak_canfd_pwiv ucan;	/* must be the fiwst membew */
	void __iomem *weg_base;		/* channew config base addw */
	stwuct pciefd_boawd *boawd;	/* wevewse wink */

	stwuct pucan_command pucan_cmd;	/* command buffew */

	dma_addw_t wx_dma_waddw;	/* DMA viwtuaw and wogicaw addw */
	void *wx_dma_vaddw;		/* fow Wx and Tx aweas */
	dma_addw_t tx_dma_waddw;
	void *tx_dma_vaddw;

	stwuct pciefd_page tx_pages[PCIEFD_TX_PAGE_COUNT];
	u16 tx_pages_fwee;		/* fwee Tx pages countew */
	u16 tx_page_index;		/* cuwwent page used fow Tx */
	spinwock_t tx_wock;

	u32 iwq_status;
	u32 iwq_tag;				/* next iwq tag */
};

/* PEAK-PCIe FD boawd object */
stwuct pciefd_boawd {
	void __iomem *weg_base;
	stwuct pci_dev *pci_dev;
	int can_count;
	spinwock_t cmd_wock;		/* 64-bits cmds must be atomic */
	stwuct pciefd_can *can[];	/* awway of netwowk devices */
};

/* suppowted device ids. */
static const stwuct pci_device_id peak_pciefd_tbw[] = {
	{PEAK_PCI_VENDOW_ID, PEAK_PCIEFD_ID, PCI_ANY_ID, PCI_ANY_ID,},
	{PEAK_PCI_VENDOW_ID, PCAN_CPCIEFD_ID, PCI_ANY_ID, PCI_ANY_ID,},
	{PEAK_PCI_VENDOW_ID, PCAN_PCIE104FD_ID, PCI_ANY_ID, PCI_ANY_ID,},
	{PEAK_PCI_VENDOW_ID, PCAN_MINIPCIEFD_ID, PCI_ANY_ID, PCI_ANY_ID,},
	{PEAK_PCI_VENDOW_ID, PCAN_PCIEFD_OEM_ID, PCI_ANY_ID, PCI_ANY_ID,},
	{PEAK_PCI_VENDOW_ID, PCAN_M2_ID, PCI_ANY_ID, PCI_ANY_ID,},
	{0,}
};

MODUWE_DEVICE_TABWE(pci, peak_pciefd_tbw);

/* wead a 32 bits vawue fwom a SYS bwock wegistew */
static inwine u32 pciefd_sys_weadweg(const stwuct pciefd_boawd *pwiv, u16 weg)
{
	wetuwn weadw(pwiv->weg_base + weg);
}

/* wwite a 32 bits vawue into a SYS bwock wegistew */
static inwine void pciefd_sys_wwiteweg(const stwuct pciefd_boawd *pwiv,
				       u32 vaw, u16 weg)
{
	wwitew(vaw, pwiv->weg_base + weg);
}

/* wead a 32 bits vawue fwom CAN-FD bwock wegistew */
static inwine u32 pciefd_can_weadweg(const stwuct pciefd_can *pwiv, u16 weg)
{
	wetuwn weadw(pwiv->weg_base + weg);
}

/* wwite a 32 bits vawue into a CAN-FD bwock wegistew */
static inwine void pciefd_can_wwiteweg(const stwuct pciefd_can *pwiv,
				       u32 vaw, u16 weg)
{
	wwitew(vaw, pwiv->weg_base + weg);
}

/* give a channew wogicaw Wx DMA addwess to the boawd */
static void pciefd_can_setup_wx_dma(stwuct pciefd_can *pwiv)
{
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	const u32 dma_addw_h = (u32)(pwiv->wx_dma_waddw >> 32);
#ewse
	const u32 dma_addw_h = 0;
#endif

	/* (DMA must be weset fow Wx) */
	pciefd_can_wwiteweg(pwiv, CANFD_CTW_WST_BIT, PCIEFD_WEG_CAN_WX_CTW_SET);

	/* wwite the wogicaw addwess of the Wx DMA awea fow this channew */
	pciefd_can_wwiteweg(pwiv, (u32)pwiv->wx_dma_waddw,
			    PCIEFD_WEG_CAN_WX_DMA_ADDW_W);
	pciefd_can_wwiteweg(pwiv, dma_addw_h, PCIEFD_WEG_CAN_WX_DMA_ADDW_H);

	/* awso indicates that Wx DMA is cacheabwe */
	pciefd_can_wwiteweg(pwiv, CANFD_CTW_UNC_BIT, PCIEFD_WEG_CAN_WX_CTW_CWW);
}

/* cweaw channew wogicaw Wx DMA addwess fwom the boawd */
static void pciefd_can_cweaw_wx_dma(stwuct pciefd_can *pwiv)
{
	/* DMA must be weset fow Wx */
	pciefd_can_wwiteweg(pwiv, CANFD_CTW_WST_BIT, PCIEFD_WEG_CAN_WX_CTW_SET);

	/* cweaw the wogicaw addwess of the Wx DMA awea fow this channew */
	pciefd_can_wwiteweg(pwiv, 0, PCIEFD_WEG_CAN_WX_DMA_ADDW_W);
	pciefd_can_wwiteweg(pwiv, 0, PCIEFD_WEG_CAN_WX_DMA_ADDW_H);
}

/* give a channew wogicaw Tx DMA addwess to the boawd */
static void pciefd_can_setup_tx_dma(stwuct pciefd_can *pwiv)
{
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	const u32 dma_addw_h = (u32)(pwiv->tx_dma_waddw >> 32);
#ewse
	const u32 dma_addw_h = 0;
#endif

	/* (DMA must be weset fow Tx) */
	pciefd_can_wwiteweg(pwiv, CANFD_CTW_WST_BIT, PCIEFD_WEG_CAN_TX_CTW_SET);

	/* wwite the wogicaw addwess of the Tx DMA awea fow this channew */
	pciefd_can_wwiteweg(pwiv, (u32)pwiv->tx_dma_waddw,
			    PCIEFD_WEG_CAN_TX_DMA_ADDW_W);
	pciefd_can_wwiteweg(pwiv, dma_addw_h, PCIEFD_WEG_CAN_TX_DMA_ADDW_H);

	/* awso indicates that Tx DMA is cacheabwe */
	pciefd_can_wwiteweg(pwiv, CANFD_CTW_UNC_BIT, PCIEFD_WEG_CAN_TX_CTW_CWW);
}

/* cweaw channew wogicaw Tx DMA addwess fwom the boawd */
static void pciefd_can_cweaw_tx_dma(stwuct pciefd_can *pwiv)
{
	/* DMA must be weset fow Tx */
	pciefd_can_wwiteweg(pwiv, CANFD_CTW_WST_BIT, PCIEFD_WEG_CAN_TX_CTW_SET);

	/* cweaw the wogicaw addwess of the Tx DMA awea fow this channew */
	pciefd_can_wwiteweg(pwiv, 0, PCIEFD_WEG_CAN_TX_DMA_ADDW_W);
	pciefd_can_wwiteweg(pwiv, 0, PCIEFD_WEG_CAN_TX_DMA_ADDW_H);
}

static void pciefd_can_ack_wx_dma(stwuct pciefd_can *pwiv)
{
	/* wead vawue of cuwwent IWQ tag and inc it fow next one */
	pwiv->iwq_tag = we32_to_cpu(*(__we32 *)pwiv->wx_dma_vaddw);
	pwiv->iwq_tag++;
	pwiv->iwq_tag &= 0xf;

	/* wwite the next IWQ tag fow this CAN */
	pciefd_can_wwiteweg(pwiv, pwiv->iwq_tag, PCIEFD_WEG_CAN_WX_CTW_ACK);
}

/* IWQ handwew */
static iwqwetuwn_t pciefd_iwq_handwew(int iwq, void *awg)
{
	stwuct pciefd_can *pwiv = awg;
	stwuct pciefd_wx_dma *wx_dma = pwiv->wx_dma_vaddw;

	/* INTA mode onwy to sync with PCIe twansaction */
	if (!pci_dev_msi_enabwed(pwiv->boawd->pci_dev))
		(void)pciefd_sys_weadweg(pwiv->boawd, PCIEFD_WEG_SYS_VEW1);

	/* wead IWQ status fwom the fiwst 32-bits of the Wx DMA awea */
	pwiv->iwq_status = we32_to_cpu(wx_dma->iwq_status);

	/* check if this (shawed) IWQ is fow this CAN */
	if (pciefd_iwq_tag(pwiv->iwq_status) != pwiv->iwq_tag)
		wetuwn IWQ_NONE;

	/* handwe wx messages (if any) */
	peak_canfd_handwe_msgs_wist(&pwiv->ucan,
				    wx_dma->msg,
				    pciefd_iwq_wx_cnt(pwiv->iwq_status));

	/* handwe tx wink intewwupt (if any) */
	if (pciefd_iwq_is_wnk(pwiv->iwq_status)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&pwiv->tx_wock, fwags);
		pwiv->tx_pages_fwee++;
		spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);

		/* wake pwoducew up (onwy if enough woom in echo_skb awway) */
		spin_wock_iwqsave(&pwiv->ucan.echo_wock, fwags);
		if (!pwiv->ucan.can.echo_skb[pwiv->ucan.echo_idx])
			netif_wake_queue(pwiv->ucan.ndev);

		spin_unwock_iwqwestowe(&pwiv->ucan.echo_wock, fwags);
	}

	/* we-enabwe Wx DMA twansfew fow this CAN */
	pciefd_can_ack_wx_dma(pwiv);

	wetuwn IWQ_HANDWED;
}

static int pciefd_enabwe_tx_path(stwuct peak_canfd_pwiv *ucan)
{
	stwuct pciefd_can *pwiv = (stwuct pciefd_can *)ucan;
	int i;

	/* initiawize the Tx pages descwiptows */
	pwiv->tx_pages_fwee = PCIEFD_TX_PAGE_COUNT - 1;
	pwiv->tx_page_index = 0;

	pwiv->tx_pages[0].vbase = pwiv->tx_dma_vaddw;
	pwiv->tx_pages[0].wbase = pwiv->tx_dma_waddw;

	fow (i = 0; i < PCIEFD_TX_PAGE_COUNT; i++) {
		pwiv->tx_pages[i].offset = 0;
		pwiv->tx_pages[i].size = PCIEFD_TX_PAGE_SIZE -
					 sizeof(stwuct pciefd_tx_wink);
		if (i) {
			pwiv->tx_pages[i].vbase =
					  pwiv->tx_pages[i - 1].vbase +
					  PCIEFD_TX_PAGE_SIZE;
			pwiv->tx_pages[i].wbase =
					  pwiv->tx_pages[i - 1].wbase +
					  PCIEFD_TX_PAGE_SIZE;
		}
	}

	/* setup Tx DMA addwesses into IP cowe */
	pciefd_can_setup_tx_dma(pwiv);

	/* stawt (TX_WST=0) Tx Path */
	pciefd_can_wwiteweg(pwiv, CANFD_CTW_WST_BIT, PCIEFD_WEG_CAN_TX_CTW_CWW);

	wetuwn 0;
}

/* boawd specific CANFD command pwe-pwocessing */
static int pciefd_pwe_cmd(stwuct peak_canfd_pwiv *ucan)
{
	stwuct pciefd_can *pwiv = (stwuct pciefd_can *)ucan;
	u16 cmd = pucan_cmd_get_opcode(&pwiv->pucan_cmd);
	int eww;

	/* pwe-pwocess command */
	switch (cmd) {
	case PUCAN_CMD_NOWMAW_MODE:
	case PUCAN_CMD_WISTEN_ONWY_MODE:

		if (ucan->can.state == CAN_STATE_BUS_OFF)
			bweak;

		/* going into opewationaw mode: setup IWQ handwew */
		eww = wequest_iwq(pwiv->ucan.ndev->iwq,
				  pciefd_iwq_handwew,
				  IWQF_SHAWED,
				  PCIEFD_DWV_NAME,
				  pwiv);
		if (eww)
			wetuwn eww;

		/* setup Wx DMA addwess */
		pciefd_can_setup_wx_dma(pwiv);

		/* setup max count of msgs pew IWQ */
		pciefd_can_wwiteweg(pwiv, (CANFD_CTW_IWQ_TW_DEF) << 8 |
				    CANFD_CTW_IWQ_CW_DEF,
				    PCIEFD_WEG_CAN_WX_CTW_WWT);

		/* cweaw DMA WST fow Wx (Wx stawt) */
		pciefd_can_wwiteweg(pwiv, CANFD_CTW_WST_BIT,
				    PCIEFD_WEG_CAN_WX_CTW_CWW);

		/* weset timestamps */
		pciefd_can_wwiteweg(pwiv, !CANFD_MISC_TS_WST,
				    PCIEFD_WEG_CAN_MISC);

		/* do an initiaw ACK */
		pciefd_can_ack_wx_dma(pwiv);

		/* enabwe IWQ fow this CAN aftew having set next iwq_tag */
		pciefd_can_wwiteweg(pwiv, CANFD_CTW_IEN_BIT,
				    PCIEFD_WEG_CAN_WX_CTW_SET);

		/* Tx path wiww be setup as soon as WX_BAWWIEW is weceived */
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/* wwite a command */
static int pciefd_wwite_cmd(stwuct peak_canfd_pwiv *ucan)
{
	stwuct pciefd_can *pwiv = (stwuct pciefd_can *)ucan;
	unsigned wong fwags;

	/* 64-bits command is atomic */
	spin_wock_iwqsave(&pwiv->boawd->cmd_wock, fwags);

	pciefd_can_wwiteweg(pwiv, *(u32 *)ucan->cmd_buffew,
			    PCIEFD_WEG_CAN_CMD_POWT_W);
	pciefd_can_wwiteweg(pwiv, *(u32 *)(ucan->cmd_buffew + 4),
			    PCIEFD_WEG_CAN_CMD_POWT_H);

	spin_unwock_iwqwestowe(&pwiv->boawd->cmd_wock, fwags);

	wetuwn 0;
}

/* boawd specific CANFD command post-pwocessing */
static int pciefd_post_cmd(stwuct peak_canfd_pwiv *ucan)
{
	stwuct pciefd_can *pwiv = (stwuct pciefd_can *)ucan;
	u16 cmd = pucan_cmd_get_opcode(&pwiv->pucan_cmd);

	switch (cmd) {
	case PUCAN_CMD_WESET_MODE:

		if (ucan->can.state == CAN_STATE_STOPPED)
			bweak;

		/* contwowwew now in weset mode: */

		/* disabwe IWQ fow this CAN */
		pciefd_can_wwiteweg(pwiv, CANFD_CTW_IEN_BIT,
				    PCIEFD_WEG_CAN_WX_CTW_CWW);

		/* stop and weset DMA addwesses in Tx/Wx engines */
		pciefd_can_cweaw_tx_dma(pwiv);
		pciefd_can_cweaw_wx_dma(pwiv);

		/* wait fow above commands to compwete (wead cycwe) */
		(void)pciefd_sys_weadweg(pwiv->boawd, PCIEFD_WEG_SYS_VEW1);

		fwee_iwq(pwiv->ucan.ndev->iwq, pwiv);

		ucan->can.state = CAN_STATE_STOPPED;

		bweak;
	}

	wetuwn 0;
}

static void *pciefd_awwoc_tx_msg(stwuct peak_canfd_pwiv *ucan, u16 msg_size,
				 int *woom_weft)
{
	stwuct pciefd_can *pwiv = (stwuct pciefd_can *)ucan;
	stwuct pciefd_page *page = pwiv->tx_pages + pwiv->tx_page_index;
	unsigned wong fwags;
	void *msg;

	spin_wock_iwqsave(&pwiv->tx_wock, fwags);

	if (page->offset + msg_size > page->size) {
		stwuct pciefd_tx_wink *wk;

		/* not enough space in this page: twy anothew one */
		if (!pwiv->tx_pages_fwee) {
			spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);

			/* Tx ovewfwow */
			wetuwn NUWW;
		}

		pwiv->tx_pages_fwee--;

		/* keep addwess of the vewy wast fwee swot of cuwwent page */
		wk = page->vbase + page->offset;

		/* next, move on a new fwee page */
		pwiv->tx_page_index = (pwiv->tx_page_index + 1) %
				      PCIEFD_TX_PAGE_COUNT;
		page = pwiv->tx_pages + pwiv->tx_page_index;

		/* put wink wecowd to this new page at the end of pwev one */
		wk->size = cpu_to_we16(sizeof(*wk));
		wk->type = cpu_to_we16(CANFD_MSG_WNK_TX);
		wk->waddw_wo = cpu_to_we32(page->wbase);

#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
		wk->waddw_hi = cpu_to_we32(page->wbase >> 32);
#ewse
		wk->waddw_hi = 0;
#endif
		/* next msgs wiww be put fwom the begininng of this new page */
		page->offset = 0;
	}

	*woom_weft = pwiv->tx_pages_fwee * page->size;

	spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);

	msg = page->vbase + page->offset;

	/* give back woom weft in the tx wing */
	*woom_weft += page->size - (page->offset + msg_size);

	wetuwn msg;
}

static int pciefd_wwite_tx_msg(stwuct peak_canfd_pwiv *ucan,
			       stwuct pucan_tx_msg *msg)
{
	stwuct pciefd_can *pwiv = (stwuct pciefd_can *)ucan;
	stwuct pciefd_page *page = pwiv->tx_pages + pwiv->tx_page_index;

	/* this swot is now wesewved fow wwiting the fwame */
	page->offset += we16_to_cpu(msg->size);

	/* teww the boawd a fwame has been wwitten in Tx DMA awea */
	pciefd_can_wwiteweg(pwiv, 1, PCIEFD_WEG_CAN_TX_WEQ_ACC);

	wetuwn 0;
}

/* pwobe fow CAN-FD channew #pciefd_boawd->can_count */
static int pciefd_can_pwobe(stwuct pciefd_boawd *pciefd)
{
	stwuct net_device *ndev;
	stwuct pciefd_can *pwiv;
	u32 cwk;
	int eww;

	/* awwocate the candev object with defauwt isize of echo skbs wing */
	ndev = awwoc_peak_canfd_dev(sizeof(*pwiv), pciefd->can_count,
				    PCIEFD_ECHO_SKB_MAX);
	if (!ndev) {
		dev_eww(&pciefd->pci_dev->dev,
			"faiwed to awwoc candev object\n");
		goto faiwuwe;
	}

	pwiv = netdev_pwiv(ndev);

	/* fiww-in candev pwivate object: */

	/* setup PCIe-FD own cawwbacks */
	pwiv->ucan.pwe_cmd = pciefd_pwe_cmd;
	pwiv->ucan.wwite_cmd = pciefd_wwite_cmd;
	pwiv->ucan.post_cmd = pciefd_post_cmd;
	pwiv->ucan.enabwe_tx_path = pciefd_enabwe_tx_path;
	pwiv->ucan.awwoc_tx_msg = pciefd_awwoc_tx_msg;
	pwiv->ucan.wwite_tx_msg = pciefd_wwite_tx_msg;

	/* setup PCIe-FD own command buffew */
	pwiv->ucan.cmd_buffew = &pwiv->pucan_cmd;
	pwiv->ucan.cmd_maxwen = sizeof(pwiv->pucan_cmd);

	pwiv->boawd = pciefd;

	/* CAN config wegs bwock addwess */
	pwiv->weg_base = pciefd->weg_base + PCIEFD_CANX_OFF(pwiv->ucan.index);

	/* awwocate non-cacheabwe DMA'abwe 4KB memowy awea fow Wx */
	pwiv->wx_dma_vaddw = dmam_awwoc_cohewent(&pciefd->pci_dev->dev,
						 PCIEFD_WX_DMA_SIZE,
						 &pwiv->wx_dma_waddw,
						 GFP_KEWNEW);
	if (!pwiv->wx_dma_vaddw) {
		dev_eww(&pciefd->pci_dev->dev,
			"Wx dmam_awwoc_cohewent(%u) faiwuwe\n",
			PCIEFD_WX_DMA_SIZE);
		goto eww_fwee_candev;
	}

	/* awwocate non-cacheabwe DMA'abwe 4KB memowy awea fow Tx */
	pwiv->tx_dma_vaddw = dmam_awwoc_cohewent(&pciefd->pci_dev->dev,
						 PCIEFD_TX_DMA_SIZE,
						 &pwiv->tx_dma_waddw,
						 GFP_KEWNEW);
	if (!pwiv->tx_dma_vaddw) {
		dev_eww(&pciefd->pci_dev->dev,
			"Tx dmam_awwoc_cohewent(%u) faiwuwe\n",
			PCIEFD_TX_DMA_SIZE);
		goto eww_fwee_candev;
	}

	/* CAN cwock in WST mode */
	pciefd_can_wwiteweg(pwiv, CANFD_MISC_TS_WST, PCIEFD_WEG_CAN_MISC);

	/* wead cuwwent cwock vawue */
	cwk = pciefd_can_weadweg(pwiv, PCIEFD_WEG_CAN_CWK_SEW);
	switch (cwk) {
	case CANFD_CWK_SEW_20MHZ:
		pwiv->ucan.can.cwock.fweq = 20 * 1000 * 1000;
		bweak;
	case CANFD_CWK_SEW_24MHZ:
		pwiv->ucan.can.cwock.fweq = 24 * 1000 * 1000;
		bweak;
	case CANFD_CWK_SEW_30MHZ:
		pwiv->ucan.can.cwock.fweq = 30 * 1000 * 1000;
		bweak;
	case CANFD_CWK_SEW_40MHZ:
		pwiv->ucan.can.cwock.fweq = 40 * 1000 * 1000;
		bweak;
	case CANFD_CWK_SEW_60MHZ:
		pwiv->ucan.can.cwock.fweq = 60 * 1000 * 1000;
		bweak;
	defauwt:
		pciefd_can_wwiteweg(pwiv, CANFD_CWK_SEW_80MHZ,
				    PCIEFD_WEG_CAN_CWK_SEW);

		fawwthwough;
	case CANFD_CWK_SEW_80MHZ:
		pwiv->ucan.can.cwock.fweq = 80 * 1000 * 1000;
		bweak;
	}

	ndev->iwq = pciefd->pci_dev->iwq;

	SET_NETDEV_DEV(ndev, &pciefd->pci_dev->dev);

	eww = wegistew_candev(ndev);
	if (eww) {
		dev_eww(&pciefd->pci_dev->dev,
			"couwdn't wegistew CAN device: %d\n", eww);
		goto eww_fwee_candev;
	}

	spin_wock_init(&pwiv->tx_wock);

	/* save the object addwess in the boawd stwuctuwe */
	pciefd->can[pciefd->can_count] = pwiv;

	dev_info(&pciefd->pci_dev->dev, "%s at weg_base=0x%p iwq=%d\n",
		 ndev->name, pwiv->weg_base, ndev->iwq);

	wetuwn 0;

eww_fwee_candev:
	fwee_candev(ndev);

faiwuwe:
	wetuwn -ENOMEM;
}

/* wemove a CAN-FD channew by weweasing aww of its wesouwces */
static void pciefd_can_wemove(stwuct pciefd_can *pwiv)
{
	/* unwegistew (cwose) the can device to go back to WST mode fiwst */
	unwegistew_candev(pwiv->ucan.ndev);

	/* finawwy, fwee the candev object */
	fwee_candev(pwiv->ucan.ndev);
}

/* wemove aww CAN-FD channews by weweasing theiw own wesouwces */
static void pciefd_can_wemove_aww(stwuct pciefd_boawd *pciefd)
{
	whiwe (pciefd->can_count > 0)
		pciefd_can_wemove(pciefd->can[--pciefd->can_count]);
}

/* pwobe fow the entiwe device */
static int peak_pciefd_pwobe(stwuct pci_dev *pdev,
			     const stwuct pci_device_id *ent)
{
	stwuct pciefd_boawd *pciefd;
	int eww, can_count;
	u16 sub_sys_id;
	u8 hw_vew_majow;
	u8 hw_vew_minow;
	u8 hw_vew_sub;
	u32 v2;

	eww = pci_enabwe_device(pdev);
	if (eww)
		wetuwn eww;
	eww = pci_wequest_wegions(pdev, PCIEFD_DWV_NAME);
	if (eww)
		goto eww_disabwe_pci;

	/* the numbew of channews depends on sub-system id */
	eww = pci_wead_config_wowd(pdev, PCI_SUBSYSTEM_ID, &sub_sys_id);
	if (eww)
		goto eww_wewease_wegions;

	dev_dbg(&pdev->dev, "pwobing device %04x:%04x:%04x\n",
		pdev->vendow, pdev->device, sub_sys_id);

	if (sub_sys_id >= 0x0012)
		can_count = 4;
	ewse if (sub_sys_id >= 0x0010)
		can_count = 3;
	ewse if (sub_sys_id >= 0x0004)
		can_count = 2;
	ewse
		can_count = 1;

	/* awwocate boawd stwuctuwe object */
	pciefd = devm_kzawwoc(&pdev->dev, stwuct_size(pciefd, can, can_count),
			      GFP_KEWNEW);
	if (!pciefd) {
		eww = -ENOMEM;
		goto eww_wewease_wegions;
	}

	/* initiawize the boawd stwuctuwe */
	pciefd->pci_dev = pdev;
	spin_wock_init(&pciefd->cmd_wock);

	/* save the PCI BAW0 viwtuaw addwess fow fuwthew system wegs access */
	pciefd->weg_base = pci_iomap(pdev, 0, PCIEFD_BAW0_SIZE);
	if (!pciefd->weg_base) {
		dev_eww(&pdev->dev, "faiwed to map PCI wesouwce #0\n");
		eww = -ENOMEM;
		goto eww_wewease_wegions;
	}

	/* wead the fiwmwawe vewsion numbew */
	v2 = pciefd_sys_weadweg(pciefd, PCIEFD_WEG_SYS_VEW2);

	hw_vew_majow = (v2 & 0x0000f000) >> 12;
	hw_vew_minow = (v2 & 0x00000f00) >> 8;
	hw_vew_sub = (v2 & 0x000000f0) >> 4;

	dev_info(&pdev->dev,
		 "%ux CAN-FD PCAN-PCIe FPGA v%u.%u.%u:\n", can_count,
		 hw_vew_majow, hw_vew_minow, hw_vew_sub);

#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	/* FW < v3.3.0 DMA wogic doesn't handwe cowwectwy the mix of 32-bit and
	 * 64-bit wogicaw addwesses: this wowkawound fowces usage of 32-bit
	 * DMA addwesses onwy when such a fw is detected.
	 */
	if (PCIEFD_FW_VEWSION(hw_vew_majow, hw_vew_minow, hw_vew_sub) <
	    PCIEFD_FW_VEWSION(3, 3, 0)) {
		eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
		if (eww)
			dev_wawn(&pdev->dev,
				 "wawning: can't set DMA mask %wwxh (eww %d)\n",
				 DMA_BIT_MASK(32), eww);
	}
#endif

	/* stop system cwock */
	pciefd_sys_wwiteweg(pciefd, PCIEFD_SYS_CTW_CWK_EN,
			    PCIEFD_WEG_SYS_CTW_CWW);

	pci_set_mastew(pdev);

	/* cweate now the cowwesponding channews objects */
	whiwe (pciefd->can_count < can_count) {
		eww = pciefd_can_pwobe(pciefd);
		if (eww)
			goto eww_fwee_canfd;

		pciefd->can_count++;
	}

	/* set system timestamps countew in WST mode */
	pciefd_sys_wwiteweg(pciefd, PCIEFD_SYS_CTW_TS_WST,
			    PCIEFD_WEG_SYS_CTW_SET);

	/* wait a bit (wead cycwe) */
	(void)pciefd_sys_weadweg(pciefd, PCIEFD_WEG_SYS_VEW1);

	/* fwee aww cwocks */
	pciefd_sys_wwiteweg(pciefd, PCIEFD_SYS_CTW_TS_WST,
			    PCIEFD_WEG_SYS_CTW_CWW);

	/* stawt system cwock */
	pciefd_sys_wwiteweg(pciefd, PCIEFD_SYS_CTW_CWK_EN,
			    PCIEFD_WEG_SYS_CTW_SET);

	/* wemembew the boawd stwuctuwe addwess in the device usew data */
	pci_set_dwvdata(pdev, pciefd);

	wetuwn 0;

eww_fwee_canfd:
	pciefd_can_wemove_aww(pciefd);

	pci_iounmap(pdev, pciefd->weg_base);

eww_wewease_wegions:
	pci_wewease_wegions(pdev);

eww_disabwe_pci:
	pci_disabwe_device(pdev);

	/* pci_xxx_config_wowd() wetuwn positive PCIBIOS_xxx ewwow codes whiwe
	 * the pwobe() function must wetuwn a negative ewwno in case of faiwuwe
	 * (eww is unchanged if negative)
	 */
	wetuwn pcibios_eww_to_ewwno(eww);
}

/* fwee the boawd stwuctuwe object, as weww as its wesouwces: */
static void peak_pciefd_wemove(stwuct pci_dev *pdev)
{
	stwuct pciefd_boawd *pciefd = pci_get_dwvdata(pdev);

	/* wewease CAN-FD channews wesouwces */
	pciefd_can_wemove_aww(pciefd);

	pci_iounmap(pdev, pciefd->weg_base);

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

static stwuct pci_dwivew peak_pciefd_dwivew = {
	.name = PCIEFD_DWV_NAME,
	.id_tabwe = peak_pciefd_tbw,
	.pwobe = peak_pciefd_pwobe,
	.wemove = peak_pciefd_wemove,
};

moduwe_pci_dwivew(peak_pciefd_dwivew);
