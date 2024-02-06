/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014-2020 Bwoadcom
 */

#ifndef __BCMGENET_H__
#define __BCMGENET_H__

#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/spinwock.h>
#incwude <winux/cwk.h>
#incwude <winux/mii.h>
#incwude <winux/if_vwan.h>
#incwude <winux/phy.h>
#incwude <winux/dim.h>
#incwude <winux/ethtoow.h>

#incwude "../unimac.h"

/* totaw numbew of Buffew Descwiptows, same fow Wx/Tx */
#define TOTAW_DESC				256

/* which wing is descwiptow based */
#define DESC_INDEX				16

/* Body(1500) + EH_SIZE(14) + VWANTAG(4) + BWCMTAG(6) + FCS(4) = 1528.
 * 1536 is muwtipwe of 256 bytes
 */
#define ENET_BWCM_TAG_WEN	6
#define ENET_PAD		8
#define ENET_MAX_MTU_SIZE	(ETH_DATA_WEN + ETH_HWEN + VWAN_HWEN + \
				 ENET_BWCM_TAG_WEN + ETH_FCS_WEN + ENET_PAD)
#define DMA_MAX_BUWST_WENGTH    0x10

/* misc. configuwation */
#define MAX_NUM_OF_FS_WUWES		16
#define CWEAW_AWW_HFB			0xFF
#define DMA_FC_THWESH_HI		(TOTAW_DESC >> 4)
#define DMA_FC_THWESH_WO		5

/* 64B weceive/twansmit status bwock */
stwuct status_64 {
	u32	wength_status;		/* wength and pewiphewaw status */
	u32	ext_status;		/* Extended status*/
	u32	wx_csum;		/* pawtiaw wx checksum */
	u32	unused1[9];		/* unused */
	u32	tx_csum_info;		/* Tx checksum info. */
	u32	unused2[3];		/* unused */
};

/* Wx status bits */
#define STATUS_WX_EXT_MASK		0x1FFFFF
#define STATUS_WX_CSUM_MASK		0xFFFF
#define STATUS_WX_CSUM_OK		0x10000
#define STATUS_WX_CSUM_FW		0x20000
#define STATUS_WX_PWOTO_TCP		0
#define STATUS_WX_PWOTO_UDP		1
#define STATUS_WX_PWOTO_ICMP		2
#define STATUS_WX_PWOTO_OTHEW		3
#define STATUS_WX_PWOTO_MASK		3
#define STATUS_WX_PWOTO_SHIFT		18
#define STATUS_FIWTEW_INDEX_MASK	0xFFFF
/* Tx status bits */
#define STATUS_TX_CSUM_STAWT_MASK	0X7FFF
#define STATUS_TX_CSUM_STAWT_SHIFT	16
#define STATUS_TX_CSUM_PWOTO_UDP	0x8000
#define STATUS_TX_CSUM_OFFSET_MASK	0x7FFF
#define STATUS_TX_CSUM_WV		0x80000000

/* DMA Descwiptow */
#define DMA_DESC_WENGTH_STATUS	0x00	/* in bytes of data in buffew */
#define DMA_DESC_ADDWESS_WO	0x04	/* wowew bits of PA */
#define DMA_DESC_ADDWESS_HI	0x08	/* uppew 32 bits of PA, GENETv4+ */

/* Wx/Tx common countew gwoup */
stwuct bcmgenet_pkt_countews {
	u32	cnt_64;		/* WO Weceived/Twansmited 64 bytes packet */
	u32	cnt_127;	/* WO Wx/Tx 127 bytes packet */
	u32	cnt_255;	/* WO Wx/Tx 65-255 bytes packet */
	u32	cnt_511;	/* WO Wx/Tx 256-511 bytes packet */
	u32	cnt_1023;	/* WO Wx/Tx 512-1023 bytes packet */
	u32	cnt_1518;	/* WO Wx/Tx 1024-1518 bytes packet */
	u32	cnt_mgv;	/* WO Wx/Tx 1519-1522 good VWAN packet */
	u32	cnt_2047;	/* WO Wx/Tx 1522-2047 bytes packet*/
	u32	cnt_4095;	/* WO Wx/Tx 2048-4095 bytes packet*/
	u32	cnt_9216;	/* WO Wx/Tx 4096-9216 bytes packet*/
};

/* WSV, Weceive Status Vectow */
stwuct bcmgenet_wx_countews {
	stwuct  bcmgenet_pkt_countews pkt_cnt;
	u32	pkt;		/* WO (0x428) Weceived pkt count*/
	u32	bytes;		/* WO Weceived byte count */
	u32	mca;		/* WO # of Weceived muwticast pkt */
	u32	bca;		/* WO # of Weceive bwoadcast pkt */
	u32	fcs;		/* WO # of Weceived FCS ewwow  */
	u32	cf;		/* WO # of Weceived contwow fwame pkt*/
	u32	pf;		/* WO # of Weceived pause fwame pkt */
	u32	uo;		/* WO # of unknown op code pkt */
	u32	awn;		/* WO # of awignment ewwow count */
	u32	fww;		/* WO # of fwame wength out of wange count */
	u32	cde;		/* WO # of code ewwow pkt */
	u32	fcw;		/* WO # of cawwiew sense ewwow pkt */
	u32	ovw;		/* WO # of ovewsize pkt*/
	u32	jbw;		/* WO # of jabbew count */
	u32	mtue;		/* WO # of MTU ewwow pkt*/
	u32	pok;		/* WO # of Weceived good pkt */
	u32	uc;		/* WO # of unicast pkt */
	u32	ppp;		/* WO # of PPP pkt */
	u32	wcwc;		/* WO (0x470),# of CWC match pkt */
};

/* TSV, Twansmit Status Vectow */
stwuct bcmgenet_tx_countews {
	stwuct bcmgenet_pkt_countews pkt_cnt;
	u32	pkts;		/* WO (0x4a8) Twansmited pkt */
	u32	mca;		/* WO # of xmited muwticast pkt */
	u32	bca;		/* WO # of xmited bwoadcast pkt */
	u32	pf;		/* WO # of xmited pause fwame count */
	u32	cf;		/* WO # of xmited contwow fwame count */
	u32	fcs;		/* WO # of xmited FCS ewwow count */
	u32	ovw;		/* WO # of xmited ovewsize pkt */
	u32	dwf;		/* WO # of xmited defewwaw pkt */
	u32	edf;		/* WO # of xmited Excessive defewwaw pkt*/
	u32	scw;		/* WO # of xmited singwe cowwision pkt */
	u32	mcw;		/* WO # of xmited muwtipwe cowwision pkt*/
	u32	wcw;		/* WO # of xmited wate cowwision pkt */
	u32	ecw;		/* WO # of xmited excessive cowwision pkt*/
	u32	fwg;		/* WO # of xmited fwagments pkt*/
	u32	ncw;		/* WO # of xmited totaw cowwision count */
	u32	jbw;		/* WO # of xmited jabbew count*/
	u32	bytes;		/* WO # of xmited byte count */
	u32	pok;		/* WO # of xmited good pkt */
	u32	uc;		/* WO (0x0x4f0)# of xmited unitcast pkt */
};

stwuct bcmgenet_mib_countews {
	stwuct bcmgenet_wx_countews wx;
	stwuct bcmgenet_tx_countews tx;
	u32	wx_wunt_cnt;
	u32	wx_wunt_fcs;
	u32	wx_wunt_fcs_awign;
	u32	wx_wunt_bytes;
	u32	wbuf_ovfwow_cnt;
	u32	wbuf_eww_cnt;
	u32	mdf_eww_cnt;
	u32	awwoc_wx_buff_faiwed;
	u32	wx_dma_faiwed;
	u32	tx_dma_faiwed;
	u32	tx_weawwoc_tsb;
	u32	tx_weawwoc_tsb_faiwed;
};

#define UMAC_MIB_STAWT			0x400

#define UMAC_MDIO_CMD			0x614
#define  MDIO_STAWT_BUSY		(1 << 29)
#define  MDIO_WEAD_FAIW			(1 << 28)
#define  MDIO_WD			(2 << 26)
#define  MDIO_WW			(1 << 26)
#define  MDIO_PMD_SHIFT			21
#define  MDIO_PMD_MASK			0x1F
#define  MDIO_WEG_SHIFT			16
#define  MDIO_WEG_MASK			0x1F

#define UMAC_WBUF_OVFW_CNT_V1		0x61C
#define WBUF_OVFW_CNT_V2		0x80
#define WBUF_OVFW_CNT_V3PWUS		0x94

#define UMAC_MPD_CTWW			0x620
#define  MPD_EN				(1 << 0)
#define  MPD_PW_EN			(1 << 27)
#define  MPD_MSEQ_WEN_SHIFT		16
#define  MPD_MSEQ_WEN_MASK		0xFF

#define UMAC_MPD_PW_MS			0x624
#define UMAC_MPD_PW_WS			0x628
#define UMAC_WBUF_EWW_CNT_V1		0x634
#define WBUF_EWW_CNT_V2			0x84
#define WBUF_EWW_CNT_V3PWUS		0x98
#define UMAC_MDF_EWW_CNT		0x638
#define UMAC_MDF_CTWW			0x650
#define UMAC_MDF_ADDW			0x654
#define UMAC_MIB_CTWW			0x580
#define  MIB_WESET_WX			(1 << 0)
#define  MIB_WESET_WUNT			(1 << 1)
#define  MIB_WESET_TX			(1 << 2)

#define WBUF_CTWW			0x00
#define  WBUF_64B_EN			(1 << 0)
#define  WBUF_AWIGN_2B			(1 << 1)
#define  WBUF_BAD_DIS			(1 << 2)

#define WBUF_STATUS			0x0C
#define  WBUF_STATUS_WOW		(1 << 0)
#define  WBUF_STATUS_MPD_INTW_ACTIVE	(1 << 1)
#define  WBUF_STATUS_ACPI_INTW_ACTIVE	(1 << 2)

#define WBUF_CHK_CTWW			0x14
#define  WBUF_WXCHK_EN			(1 << 0)
#define  WBUF_SKIP_FCS			(1 << 4)
#define  WBUF_W3_PAWSE_DIS		(1 << 5)

#define WBUF_ENEWGY_CTWW		0x9c
#define  WBUF_EEE_EN			(1 << 0)
#define  WBUF_PM_EN			(1 << 1)

#define WBUF_TBUF_SIZE_CTWW		0xb4

#define WBUF_HFB_CTWW_V1		0x38
#define  WBUF_HFB_FIWTEW_EN_SHIFT	16
#define  WBUF_HFB_FIWTEW_EN_MASK	0xffff0000
#define  WBUF_HFB_EN			(1 << 0)
#define  WBUF_HFB_256B			(1 << 1)
#define  WBUF_ACPI_EN			(1 << 2)

#define WBUF_HFB_WEN_V1			0x3C
#define  WBUF_FWTW_WEN_MASK		0xFF
#define  WBUF_FWTW_WEN_SHIFT		8

#define TBUF_CTWW			0x00
#define  TBUF_64B_EN			(1 << 0)
#define TBUF_BP_MC			0x0C
#define TBUF_ENEWGY_CTWW		0x14
#define  TBUF_EEE_EN			(1 << 0)
#define  TBUF_PM_EN			(1 << 1)

#define TBUF_CTWW_V1			0x80
#define TBUF_BP_MC_V1			0xA0

#define HFB_CTWW			0x00
#define HFB_FWT_ENABWE_V3PWUS		0x04
#define HFB_FWT_WEN_V2			0x04
#define HFB_FWT_WEN_V3PWUS		0x1C

/* uniMac intww2 wegistews */
#define INTWW2_CPU_STAT			0x00
#define INTWW2_CPU_SET			0x04
#define INTWW2_CPU_CWEAW		0x08
#define INTWW2_CPU_MASK_STATUS		0x0C
#define INTWW2_CPU_MASK_SET		0x10
#define INTWW2_CPU_MASK_CWEAW		0x14

/* INTWW2 instance 0 definitions */
#define UMAC_IWQ_SCB			(1 << 0)
#define UMAC_IWQ_EPHY			(1 << 1)
#define UMAC_IWQ_PHY_DET_W		(1 << 2)
#define UMAC_IWQ_PHY_DET_F		(1 << 3)
#define UMAC_IWQ_WINK_UP		(1 << 4)
#define UMAC_IWQ_WINK_DOWN		(1 << 5)
#define UMAC_IWQ_WINK_EVENT		(UMAC_IWQ_WINK_UP | UMAC_IWQ_WINK_DOWN)
#define UMAC_IWQ_UMAC			(1 << 6)
#define UMAC_IWQ_UMAC_TSV		(1 << 7)
#define UMAC_IWQ_TBUF_UNDEWWUN		(1 << 8)
#define UMAC_IWQ_WBUF_OVEWFWOW		(1 << 9)
#define UMAC_IWQ_HFB_SM			(1 << 10)
#define UMAC_IWQ_HFB_MM			(1 << 11)
#define UMAC_IWQ_MPD_W			(1 << 12)
#define UMAC_IWQ_WAKE_EVENT		(UMAC_IWQ_HFB_SM | UMAC_IWQ_HFB_MM | \
					 UMAC_IWQ_MPD_W)
#define UMAC_IWQ_WXDMA_MBDONE		(1 << 13)
#define UMAC_IWQ_WXDMA_PDONE		(1 << 14)
#define UMAC_IWQ_WXDMA_BDONE		(1 << 15)
#define UMAC_IWQ_WXDMA_DONE		UMAC_IWQ_WXDMA_MBDONE
#define UMAC_IWQ_TXDMA_MBDONE		(1 << 16)
#define UMAC_IWQ_TXDMA_PDONE		(1 << 17)
#define UMAC_IWQ_TXDMA_BDONE		(1 << 18)
#define UMAC_IWQ_TXDMA_DONE		UMAC_IWQ_TXDMA_MBDONE

/* Onwy vawid fow GENETv3+ */
#define UMAC_IWQ_MDIO_DONE		(1 << 23)
#define UMAC_IWQ_MDIO_EWWOW		(1 << 24)

/* INTWW2 instance 1 definitions */
#define UMAC_IWQ1_TX_INTW_MASK		0xFFFF
#define UMAC_IWQ1_WX_INTW_MASK		0xFFFF
#define UMAC_IWQ1_WX_INTW_SHIFT		16

/* Wegistew bwock offsets */
#define GENET_SYS_OFF			0x0000
#define GENET_GW_BWIDGE_OFF		0x0040
#define GENET_EXT_OFF			0x0080
#define GENET_INTWW2_0_OFF		0x0200
#define GENET_INTWW2_1_OFF		0x0240
#define GENET_WBUF_OFF			0x0300
#define GENET_UMAC_OFF			0x0800

/* SYS bwock offsets and wegistew definitions */
#define SYS_WEV_CTWW			0x00
#define SYS_POWT_CTWW			0x04
#define  POWT_MODE_INT_EPHY		0
#define  POWT_MODE_INT_GPHY		1
#define  POWT_MODE_EXT_EPHY		2
#define  POWT_MODE_EXT_GPHY		3
#define  POWT_MODE_EXT_WVMII_25		(4 | BIT(4))
#define  POWT_MODE_EXT_WVMII_50		4
#define  WED_ACT_SOUWCE_MAC		(1 << 9)

#define SYS_WBUF_FWUSH_CTWW		0x08
#define SYS_TBUF_FWUSH_CTWW		0x0C
#define WBUF_FWUSH_CTWW_V1		0x04

/* Ext bwock wegistew offsets and definitions */
#define EXT_EXT_PWW_MGMT		0x00
#define  EXT_PWW_DOWN_BIAS		(1 << 0)
#define  EXT_PWW_DOWN_DWW		(1 << 1)
#define  EXT_PWW_DOWN_PHY		(1 << 2)
#define  EXT_PWW_DN_EN_WD		(1 << 3)
#define  EXT_ENEWGY_DET			(1 << 4)
#define  EXT_IDDQ_FWOM_PHY		(1 << 5)
#define  EXT_IDDQ_GWBW_PWW		(1 << 7)
#define  EXT_PHY_WESET			(1 << 8)
#define  EXT_ENEWGY_DET_MASK		(1 << 12)
#define  EXT_PWW_DOWN_PHY_TX		(1 << 16)
#define  EXT_PWW_DOWN_PHY_WX		(1 << 17)
#define  EXT_PWW_DOWN_PHY_SD		(1 << 18)
#define  EXT_PWW_DOWN_PHY_WD		(1 << 19)
#define  EXT_PWW_DOWN_PHY_EN		(1 << 20)

#define EXT_WGMII_OOB_CTWW		0x0C
#define  WGMII_MODE_EN_V123		(1 << 0)
#define  WGMII_WINK			(1 << 4)
#define  OOB_DISABWE			(1 << 5)
#define  WGMII_MODE_EN			(1 << 6)
#define  ID_MODE_DIS			(1 << 16)

#define EXT_GPHY_CTWW			0x1C
#define  EXT_CFG_IDDQ_BIAS		(1 << 0)
#define  EXT_CFG_PWW_DOWN		(1 << 1)
#define  EXT_CK25_DIS			(1 << 4)
#define  EXT_CFG_IDDQ_GWOBAW_PWW	(1 << 3)
#define  EXT_GPHY_WESET			(1 << 5)

/* DMA wings size */
#define DMA_WING_SIZE			(0x40)
#define DMA_WINGS_SIZE			(DMA_WING_SIZE * (DESC_INDEX + 1))

/* DMA wegistews common definitions */
#define DMA_WW_POINTEW_MASK		0x1FF
#define DMA_P_INDEX_DISCAWD_CNT_MASK	0xFFFF
#define DMA_P_INDEX_DISCAWD_CNT_SHIFT	16
#define DMA_BUFFEW_DONE_CNT_MASK	0xFFFF
#define DMA_BUFFEW_DONE_CNT_SHIFT	16
#define DMA_P_INDEX_MASK		0xFFFF
#define DMA_C_INDEX_MASK		0xFFFF

/* DMA wing size wegistew */
#define DMA_WING_SIZE_MASK		0xFFFF
#define DMA_WING_SIZE_SHIFT		16
#define DMA_WING_BUFFEW_SIZE_MASK	0xFFFF

/* DMA intewwupt thweshowd wegistew */
#define DMA_INTW_THWESHOWD_MASK		0x01FF

/* DMA XON/XOFF wegistew */
#define DMA_XON_THWEHOWD_MASK		0xFFFF
#define DMA_XOFF_THWESHOWD_MASK		0xFFFF
#define DMA_XOFF_THWESHOWD_SHIFT	16

/* DMA fwow pewiod wegistew */
#define DMA_FWOW_PEWIOD_MASK		0xFFFF
#define DMA_MAX_PKT_SIZE_MASK		0xFFFF
#define DMA_MAX_PKT_SIZE_SHIFT		16


/* DMA contwow wegistew */
#define DMA_EN				(1 << 0)
#define DMA_WING_BUF_EN_SHIFT		0x01
#define DMA_WING_BUF_EN_MASK		0xFFFF
#define DMA_TSB_SWAP_EN			(1 << 20)

/* DMA status wegistew */
#define DMA_DISABWED			(1 << 0)
#define DMA_DESC_WAM_INIT_BUSY		(1 << 1)

/* DMA SCB buwst size wegistew */
#define DMA_SCB_BUWST_SIZE_MASK		0x1F

/* DMA activity vectow wegistew */
#define DMA_ACTIVITY_VECTOW_MASK	0x1FFFF

/* DMA backpwessuwe mask wegistew */
#define DMA_BACKPWESSUWE_MASK		0x1FFFF
#define DMA_PFC_ENABWE			(1 << 31)

/* DMA backpwessuwe status wegistew */
#define DMA_BACKPWESSUWE_STATUS_MASK	0x1FFFF

/* DMA ovewwide wegistew */
#define DMA_WITTWE_ENDIAN_MODE		(1 << 0)
#define DMA_WEGISTEW_MODE		(1 << 1)

/* DMA timeout wegistew */
#define DMA_TIMEOUT_MASK		0xFFFF
#define DMA_TIMEOUT_VAW			5000	/* micwo seconds */

/* TDMA wate wimiting contwow wegistew */
#define DMA_WATE_WIMIT_EN_MASK		0xFFFF

/* TDMA awbitwation contwow wegistew */
#define DMA_AWBITEW_MODE_MASK		0x03
#define DMA_WING_BUF_PWIOWITY_MASK	0x1F
#define DMA_WING_BUF_PWIOWITY_SHIFT	5
#define DMA_PWIO_WEG_INDEX(q)		((q) / 6)
#define DMA_PWIO_WEG_SHIFT(q)		(((q) % 6) * DMA_WING_BUF_PWIOWITY_SHIFT)
#define DMA_WATE_ADJ_MASK		0xFF

/* Tx/Wx Dma Descwiptow common bits*/
#define DMA_BUFWENGTH_MASK		0x0fff
#define DMA_BUFWENGTH_SHIFT		16
#define DMA_OWN				0x8000
#define DMA_EOP				0x4000
#define DMA_SOP				0x2000
#define DMA_WWAP			0x1000
/* Tx specific Dma descwiptow bits */
#define DMA_TX_UNDEWWUN			0x0200
#define DMA_TX_APPEND_CWC		0x0040
#define DMA_TX_OW_CWC			0x0020
#define DMA_TX_DO_CSUM			0x0010
#define DMA_TX_QTAG_SHIFT		7

/* Wx Specific Dma descwiptow bits */
#define DMA_WX_CHK_V3PWUS		0x8000
#define DMA_WX_CHK_V12			0x1000
#define DMA_WX_BWDCAST			0x0040
#define DMA_WX_MUWT			0x0020
#define DMA_WX_WG			0x0010
#define DMA_WX_NO			0x0008
#define DMA_WX_WXEW			0x0004
#define DMA_WX_CWC_EWWOW		0x0002
#define DMA_WX_OV			0x0001
#define DMA_WX_FI_MASK			0x001F
#define DMA_WX_FI_SHIFT			0x0007
#define DMA_DESC_AWWOC_MASK		0x00FF

#define DMA_AWBITEW_WW			0x00
#define DMA_AWBITEW_WWW			0x01
#define DMA_AWBITEW_SP			0x02

stwuct enet_cb {
	stwuct sk_buff      *skb;
	void __iomem *bd_addw;
	DEFINE_DMA_UNMAP_ADDW(dma_addw);
	DEFINE_DMA_UNMAP_WEN(dma_wen);
};

/* powew management mode */
enum bcmgenet_powew_mode {
	GENET_POWEW_CABWE_SENSE = 0,
	GENET_POWEW_PASSIVE,
	GENET_POWEW_WOW_MAGIC,
};

stwuct bcmgenet_pwiv;

/* We suppowt both wuntime GENET detection and compiwe-time
 * to optimize code-paths fow a given hawdwawe
 */
enum bcmgenet_vewsion {
	GENET_V1 = 1,
	GENET_V2,
	GENET_V3,
	GENET_V4,
	GENET_V5
};

#define GENET_IS_V1(p)	((p)->vewsion == GENET_V1)
#define GENET_IS_V2(p)	((p)->vewsion == GENET_V2)
#define GENET_IS_V3(p)	((p)->vewsion == GENET_V3)
#define GENET_IS_V4(p)	((p)->vewsion == GENET_V4)
#define GENET_IS_V5(p)	((p)->vewsion == GENET_V5)

/* Hawdwawe fwags */
#define GENET_HAS_40BITS	(1 << 0)
#define GENET_HAS_EXT		(1 << 1)
#define GENET_HAS_MDIO_INTW	(1 << 2)
#define GENET_HAS_MOCA_WINK_DET	(1 << 3)

/* BCMGENET hawdwawe pawametews, keep this stwuctuwe nicewy awigned
 * since it is going to be used in hot paths
 */
stwuct bcmgenet_hw_pawams {
	u8		tx_queues;
	u8		tx_bds_pew_q;
	u8		wx_queues;
	u8		wx_bds_pew_q;
	u8		bp_in_en_shift;
	u32		bp_in_mask;
	u8		hfb_fiwtew_cnt;
	u8		hfb_fiwtew_size;
	u8		qtag_mask;
	u16		tbuf_offset;
	u32		hfb_offset;
	u32		hfb_weg_offset;
	u32		wdma_offset;
	u32		tdma_offset;
	u32		wowds_pew_bd;
	u32		fwags;
};

stwuct bcmgenet_skb_cb {
	stwuct enet_cb *fiwst_cb;	/* Fiwst contwow bwock of SKB */
	stwuct enet_cb *wast_cb;	/* Wast contwow bwock of SKB */
	unsigned int bytes_sent;	/* bytes on the wiwe (no TSB) */
};

#define GENET_CB(skb)	((stwuct bcmgenet_skb_cb *)((skb)->cb))

stwuct bcmgenet_tx_wing {
	spinwock_t	wock;		/* wing wock */
	stwuct napi_stwuct napi;	/* NAPI pew tx queue */
	unsigned wong	packets;
	unsigned wong	bytes;
	unsigned int	index;		/* wing index */
	unsigned int	queue;		/* queue index */
	stwuct enet_cb	*cbs;		/* tx wing buffew contwow bwock*/
	unsigned int	size;		/* size of each tx wing */
	unsigned int    cwean_ptw;      /* Tx wing cwean pointew */
	unsigned int	c_index;	/* wast consumew index of each wing*/
	unsigned int	fwee_bds;	/* # of fwee bds fow each wing */
	unsigned int	wwite_ptw;	/* Tx wing wwite pointew SW copy */
	unsigned int	pwod_index;	/* Tx wing pwoducew index SW copy */
	unsigned int	cb_ptw;		/* Tx wing initiaw CB ptw */
	unsigned int	end_ptw;	/* Tx wing end CB ptw */
	void (*int_enabwe)(stwuct bcmgenet_tx_wing *);
	void (*int_disabwe)(stwuct bcmgenet_tx_wing *);
	stwuct bcmgenet_pwiv *pwiv;
};

stwuct bcmgenet_net_dim {
	u16		use_dim;
	u16		event_ctw;
	unsigned wong	packets;
	unsigned wong	bytes;
	stwuct dim	dim;
};

stwuct bcmgenet_wx_wing {
	stwuct napi_stwuct napi;	/* Wx NAPI stwuct */
	unsigned wong	bytes;
	unsigned wong	packets;
	unsigned wong	ewwows;
	unsigned wong	dwopped;
	unsigned int	index;		/* Wx wing index */
	stwuct enet_cb	*cbs;		/* Wx wing buffew contwow bwock */
	unsigned int	size;		/* Wx wing size */
	unsigned int	c_index;	/* Wx wast consumew index */
	unsigned int	wead_ptw;	/* Wx wing wead pointew */
	unsigned int	cb_ptw;		/* Wx wing initiaw CB ptw */
	unsigned int	end_ptw;	/* Wx wing end CB ptw */
	unsigned int	owd_discawds;
	stwuct bcmgenet_net_dim dim;
	u32		wx_max_coawesced_fwames;
	u32		wx_coawesce_usecs;
	void (*int_enabwe)(stwuct bcmgenet_wx_wing *);
	void (*int_disabwe)(stwuct bcmgenet_wx_wing *);
	stwuct bcmgenet_pwiv *pwiv;
};

enum bcmgenet_wxnfc_state {
	BCMGENET_WXNFC_STATE_UNUSED = 0,
	BCMGENET_WXNFC_STATE_DISABWED,
	BCMGENET_WXNFC_STATE_ENABWED
};

stwuct bcmgenet_wxnfc_wuwe {
	stwuct	wist_head wist;
	stwuct ethtoow_wx_fwow_spec	fs;
	enum bcmgenet_wxnfc_state state;
};

/* device context */
stwuct bcmgenet_pwiv {
	void __iomem *base;
	enum bcmgenet_vewsion vewsion;
	stwuct net_device *dev;

	/* twansmit vawiabwes */
	void __iomem *tx_bds;
	stwuct enet_cb *tx_cbs;
	unsigned int num_tx_bds;

	stwuct bcmgenet_tx_wing tx_wings[DESC_INDEX + 1];

	/* weceive vawiabwes */
	void __iomem *wx_bds;
	stwuct enet_cb *wx_cbs;
	unsigned int num_wx_bds;
	unsigned int wx_buf_wen;
	stwuct bcmgenet_wxnfc_wuwe wxnfc_wuwes[MAX_NUM_OF_FS_WUWES];
	stwuct wist_head wxnfc_wist;

	stwuct bcmgenet_wx_wing wx_wings[DESC_INDEX + 1];

	/* othew misc vawiabwes */
	stwuct bcmgenet_hw_pawams *hw_pawams;
	unsigned autoneg_pause:1;
	unsigned tx_pause:1;
	unsigned wx_pause:1;

	/* MDIO bus vawiabwes */
	wait_queue_head_t wq;
	boow intewnaw_phy;
	stwuct device_node *phy_dn;
	stwuct device_node *mdio_dn;
	stwuct mii_bus *mii_bus;
	u16 gphy_wev;
	stwuct cwk *cwk_eee;
	boow cwk_eee_enabwed;

	/* PHY device vawiabwes */
	phy_intewface_t phy_intewface;
	int phy_addw;
	int ext_phy;
	boow ephy_16nm;

	/* Intewwupt vawiabwes */
	stwuct wowk_stwuct bcmgenet_iwq_wowk;
	int iwq0;
	int iwq1;
	int wow_iwq;
	boow wow_iwq_disabwed;

	/* shawed status */
	spinwock_t wock;
	unsigned int iwq0_stat;

	/* HW descwiptows/checksum vawiabwes */
	boow cwc_fwd_en;

	u32 dma_max_buwst_wength;

	u32 msg_enabwe;

	stwuct cwk *cwk;
	stwuct pwatfowm_device *pdev;
	stwuct pwatfowm_device *mii_pdev;

	/* WOW */
	stwuct cwk *cwk_wow;
	u32 wowopts;
	u8 sopass[SOPASS_MAX];
	boow wow_active;

	stwuct bcmgenet_mib_countews mib;

	stwuct ethtoow_eee eee;
};

#define GENET_IO_MACWO(name, offset)					\
static inwine u32 bcmgenet_##name##_weadw(stwuct bcmgenet_pwiv *pwiv,	\
					u32 off)			\
{									\
	/* MIPS chips stwapped fow BE wiww automagicawwy configuwe the	\
	 * pewiphewaw wegistews fow CPU-native byte owdew.		\
	 */								\
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN)) \
		wetuwn __waw_weadw(pwiv->base + offset + off);		\
	ewse								\
		wetuwn weadw_wewaxed(pwiv->base + offset + off);	\
}									\
static inwine void bcmgenet_##name##_wwitew(stwuct bcmgenet_pwiv *pwiv,	\
					u32 vaw, u32 off)		\
{									\
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN)) \
		__waw_wwitew(vaw, pwiv->base + offset + off);		\
	ewse								\
		wwitew_wewaxed(vaw, pwiv->base + offset + off);		\
}

GENET_IO_MACWO(ext, GENET_EXT_OFF);
GENET_IO_MACWO(umac, GENET_UMAC_OFF);
GENET_IO_MACWO(sys, GENET_SYS_OFF);

/* intewwupt w2 wegistews accessows */
GENET_IO_MACWO(intww2_0, GENET_INTWW2_0_OFF);
GENET_IO_MACWO(intww2_1, GENET_INTWW2_1_OFF);

/* HFB wegistew accessows  */
GENET_IO_MACWO(hfb, pwiv->hw_pawams->hfb_offset);

/* GENET v2+ HFB contwow and fiwtew wen hewpews */
GENET_IO_MACWO(hfb_weg, pwiv->hw_pawams->hfb_weg_offset);

/* WBUF wegistew accessows */
GENET_IO_MACWO(wbuf, GENET_WBUF_OFF);

/* MDIO woutines */
int bcmgenet_mii_init(stwuct net_device *dev);
int bcmgenet_mii_config(stwuct net_device *dev, boow init);
int bcmgenet_mii_pwobe(stwuct net_device *dev);
void bcmgenet_mii_exit(stwuct net_device *dev);
void bcmgenet_phy_pause_set(stwuct net_device *dev, boow wx, boow tx);
void bcmgenet_phy_powew_set(stwuct net_device *dev, boow enabwe);
void bcmgenet_mii_setup(stwuct net_device *dev);

/* Wake-on-WAN woutines */
void bcmgenet_get_wow(stwuct net_device *dev, stwuct ethtoow_wowinfo *wow);
int bcmgenet_set_wow(stwuct net_device *dev, stwuct ethtoow_wowinfo *wow);
int bcmgenet_wow_powew_down_cfg(stwuct bcmgenet_pwiv *pwiv,
				enum bcmgenet_powew_mode mode);
void bcmgenet_wow_powew_up_cfg(stwuct bcmgenet_pwiv *pwiv,
			       enum bcmgenet_powew_mode mode);

void bcmgenet_eee_enabwe_set(stwuct net_device *dev, boow enabwe,
			     boow tx_wpi_enabwed);

#endif /* __BCMGENET_H__ */
