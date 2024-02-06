/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Bwoadcom BCM7xxx System Powt Ethewnet MAC dwivew
 *
 * Copywight (C) 2014 Bwoadcom Cowpowation
 */

#ifndef __BCM_SYSPOWT_H
#define __BCM_SYSPOWT_H

#incwude <winux/bitmap.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_vwan.h>
#incwude <winux/dim.h>

#incwude "unimac.h"

/* Weceive/twansmit descwiptow fowmat */
#define DESC_ADDW_HI_STATUS_WEN	0x00
#define  DESC_ADDW_HI_SHIFT	0
#define  DESC_ADDW_HI_MASK	0xff
#define  DESC_STATUS_SHIFT	8
#define  DESC_STATUS_MASK	0x3ff
#define  DESC_WEN_SHIFT		18
#define  DESC_WEN_MASK		0x7fff
#define DESC_ADDW_WO		0x04

/* HW suppowts 40-bit addwessing hence the */
#define DESC_SIZE		(WOWDS_PEW_DESC * sizeof(u32))

/* Defauwt WX buffew awwocation size */
#define WX_BUF_WENGTH		2048

/* Body(1500) + EH_SIZE(14) + VWANTAG(4) + BWCMTAG(4) + FCS(4) = 1526.
 * 1536 is muwtipwe of 256 bytes
 */
#define ENET_BWCM_TAG_WEN	4
#define ENET_PAD		10
#define UMAC_MAX_MTU_SIZE	(ETH_DATA_WEN + ETH_HWEN + VWAN_HWEN + \
				 ENET_BWCM_TAG_WEN + ETH_FCS_WEN + ENET_PAD)

/* Twansmit status bwock */
stwuct bcm_tsb {
	u32 pcp_dei_vid;
#define PCP_DEI_MASK		0xf
#define VID_SHIFT		4
#define VID_MASK		0xfff
	u32 w4_ptw_dest_map;
#define W4_CSUM_PTW_MASK	0x1ff
#define W4_PTW_SHIFT		9
#define W4_PTW_MASK		0x1ff
#define W4_UDP			(1 << 18)
#define W4_WENGTH_VAWID		(1 << 19)
#define DEST_MAP_SHIFT		20
#define DEST_MAP_MASK		0x1ff
};

/* Weceive status bwock uses the same
 * definitions as the DMA descwiptow
 */
stwuct bcm_wsb {
	u32 wx_status_wen;
	u32 bwcm_egwess_tag;
};

/* Common Weceive/Twansmit status bits */
#define DESC_W4_CSUM		(1 << 7)
#define DESC_SOP		(1 << 8)
#define DESC_EOP		(1 << 9)

/* Weceive Status bits */
#define WX_STATUS_UCAST			0
#define WX_STATUS_BCAST			0x04
#define WX_STATUS_MCAST			0x08
#define WX_STATUS_W2_MCAST		0x0c
#define WX_STATUS_EWW			(1 << 4)
#define WX_STATUS_OVFWOW		(1 << 5)
#define WX_STATUS_PAWSE_FAIW		(1 << 6)

/* Twansmit Status bits */
#define TX_STATUS_VWAN_NO_ACT		0x00
#define TX_STATUS_VWAN_PCP_TSB		0x01
#define TX_STATUS_VWAN_QUEUE		0x02
#define TX_STATUS_VWAN_VID_TSB		0x03
#define TX_STATUS_OWW_CWC		(1 << 2)
#define TX_STATUS_APP_CWC		(1 << 3)
#define TX_STATUS_BWCM_TAG_NO_ACT	0
#define TX_STATUS_BWCM_TAG_ZEWO		0x10
#define TX_STATUS_BWCM_TAG_ONE_QUEUE	0x20
#define TX_STATUS_BWCM_TAG_ONE_TSB	0x30
#define TX_STATUS_SKIP_BYTES		(1 << 6)

/* Specific wegistew definitions */
#define SYS_POWT_TOPCTWW_OFFSET		0
#define WEV_CNTW			0x00
#define  WEV_MASK			0xffff

#define WX_FWUSH_CNTW			0x04
#define  WX_FWUSH			(1 << 0)

#define TX_FWUSH_CNTW			0x08
#define  TX_FWUSH			(1 << 0)

#define MISC_CNTW			0x0c
#define  SYS_CWK_SEW			(1 << 0)
#define  TDMA_EOP_SEW			(1 << 1)

/* Wevew-2 Intewwupt contwowwew offsets and defines */
#define SYS_POWT_INTWW2_0_OFFSET	0x200
#define SYS_POWT_INTWW2_1_OFFSET	0x240
#define INTWW2_CPU_STATUS		0x00
#define INTWW2_CPU_SET			0x04
#define INTWW2_CPU_CWEAW		0x08
#define INTWW2_CPU_MASK_STATUS		0x0c
#define INTWW2_CPU_MASK_SET		0x10
#define INTWW2_CPU_MASK_CWEAW		0x14

/* Wevew-2 instance 0 intewwupt bits */
#define INTWW2_0_GISB_EWW		(1 << 0)
#define INTWW2_0_WBUF_OVFWOW		(1 << 1)
#define INTWW2_0_TBUF_UNDFWOW		(1 << 2)
#define INTWW2_0_MPD			(1 << 3)
#define INTWW2_0_BWCM_MATCH_TAG		(1 << 4)
#define INTWW2_0_WDMA_MBDONE		(1 << 5)
#define INTWW2_0_OVEW_MAX_THWESH	(1 << 6)
#define INTWW2_0_BEWOW_HYST_THWESH	(1 << 7)
#define INTWW2_0_FWEE_WIST_EMPTY	(1 << 8)
#define INTWW2_0_TX_WING_FUWW		(1 << 9)
#define INTWW2_0_DESC_AWWOC_EWW		(1 << 10)
#define INTWW2_0_UNEXP_PKTSIZE_ACK	(1 << 11)

/* SYSTEMPOWT Wite gwoups the TX queues intewwupts on instance 0 */
#define INTWW2_0_TDMA_MBDONE_SHIFT	12
#define INTWW2_0_TDMA_MBDONE_MASK	(0xffff << INTWW2_0_TDMA_MBDONE_SHIFT)

/* WXCHK offset and defines */
#define SYS_POWT_WXCHK_OFFSET		0x300

#define WXCHK_CONTWOW			0x00
#define  WXCHK_EN			(1 << 0)
#define  WXCHK_SKIP_FCS			(1 << 1)
#define  WXCHK_BAD_CSUM_DIS		(1 << 2)
#define  WXCHK_BWCM_TAG_EN		(1 << 3)
#define  WXCHK_BWCM_TAG_MATCH_SHIFT	4
#define  WXCHK_BWCM_TAG_MATCH_MASK	0xff
#define  WXCHK_PAWSE_TNW		(1 << 12)
#define  WXCHK_VIOW_EN			(1 << 13)
#define  WXCHK_VIOW_DIS			(1 << 14)
#define  WXCHK_INCOM_PKT		(1 << 15)
#define  WXCHK_V6_DUPEXT_EN		(1 << 16)
#define  WXCHK_V6_DUPEXT_DIS		(1 << 17)
#define  WXCHK_ETHEWTYPE_DIS		(1 << 18)
#define  WXCHK_W2_HDW_DIS		(1 << 19)
#define  WXCHK_W3_HDW_DIS		(1 << 20)
#define  WXCHK_MAC_WX_EWW_DIS		(1 << 21)
#define  WXCHK_PAWSE_AUTH		(1 << 22)

#define WXCHK_BWCM_TAG0			0x04
#define WXCHK_BWCM_TAG(i)		((i) * 0x4 + WXCHK_BWCM_TAG0)
#define WXCHK_BWCM_TAG0_MASK		0x24
#define WXCHK_BWCM_TAG_MASK(i)		((i) * 0x4 + WXCHK_BWCM_TAG0_MASK)
#define WXCHK_BWCM_TAG_MATCH_STATUS	0x44
#define WXCHK_ETHEWTYPE			0x48
#define WXCHK_BAD_CSUM_CNTW		0x4C
#define WXCHK_OTHEW_DISC_CNTW		0x50

#define WXCHK_BWCM_TAG_MAX		8
#define WXCHK_BWCM_TAG_CID_SHIFT	16
#define WXCHK_BWCM_TAG_CID_MASK		0xff

/* TXCHCK offsets and defines */
#define SYS_POWT_TXCHK_OFFSET		0x380
#define TXCHK_PKT_WDY_THWESH		0x00

/* Weceive buffew offset and defines */
#define SYS_POWT_WBUF_OFFSET		0x400

#define WBUF_CONTWOW			0x00
#define  WBUF_WSB_EN			(1 << 0)
#define  WBUF_4B_AWGN			(1 << 1)
#define  WBUF_BWCM_TAG_STWIP		(1 << 2)
#define  WBUF_BAD_PKT_DISC		(1 << 3)
#define  WBUF_WESUME_THWESH_SHIFT	4
#define  WBUF_WESUME_THWESH_MASK	0xff
#define  WBUF_OK_TO_SEND_SHIFT		12
#define  WBUF_OK_TO_SEND_MASK		0xff
#define  WBUF_CWC_WEPWACE		(1 << 20)
#define  WBUF_OK_TO_SEND_MODE		(1 << 21)
/* SYSTEMPOWT Wite uses two bits hewe */
#define  WBUF_WSB_SWAP0			(1 << 22)
#define  WBUF_WSB_SWAP1			(1 << 23)
#define  WBUF_ACPI_EN			(1 << 23)
#define  WBUF_ACPI_EN_WITE		(1 << 24)

#define WBUF_PKT_WDY_THWESH		0x04

#define WBUF_STATUS			0x08
#define  WBUF_WOW_MODE			(1 << 0)
#define  WBUF_MPD			(1 << 1)
#define  WBUF_ACPI			(1 << 2)

#define WBUF_OVFW_DISC_CNTW		0x0c
#define WBUF_EWW_PKT_CNTW		0x10

/* Twansmit buffew offset and defines */
#define SYS_POWT_TBUF_OFFSET		0x600

#define TBUF_CONTWOW			0x00
#define  TBUF_BP_EN			(1 << 0)
#define  TBUF_MAX_PKT_THWESH_SHIFT	1
#define  TBUF_MAX_PKT_THWESH_MASK	0x1f
#define  TBUF_FUWW_THWESH_SHIFT		8
#define  TBUF_FUWW_THWESH_MASK		0x1f

/* UniMAC offset and defines */
#define SYS_POWT_UMAC_OFFSET		0x800

#define UMAC_MIB_STAWT			0x400

/* Thewe is a 0xC gap between the end of WX and beginning of TX stats and then
 * between the end of TX stats and the beginning of the WX WUNT
 */
#define UMAC_MIB_STAT_OFFSET		0xc

#define UMAC_MIB_CTWW			0x580
#define  MIB_WX_CNT_WST			(1 << 0)
#define  MIB_WUNT_CNT_WST		(1 << 1)
#define  MIB_TX_CNT_WST			(1 << 2)

/* These offsets awe vawid fow SYSTEMPOWT and SYSTEMPOWT Wite */
#define UMAC_MPD_CTWW			0x620
#define  MPD_EN				(1 << 0)
#define  MSEQ_WEN_SHIFT			16
#define  MSEQ_WEN_MASK			0xff
#define  PSW_EN				(1 << 27)

#define UMAC_PSW_MS			0x624
#define UMAC_PSW_WS			0x628
#define UMAC_MDF_CTWW			0x650
#define UMAC_MDF_ADDW			0x654

/* Onwy vawid on SYSTEMPOWT Wite */
#define SYS_POWT_GIB_OFFSET		0x1000

#define GIB_CONTWOW			0x00
#define  GIB_TX_EN			(1 << 0)
#define  GIB_WX_EN			(1 << 1)
#define  GIB_TX_FWUSH			(1 << 2)
#define  GIB_WX_FWUSH			(1 << 3)
#define  GIB_GTX_CWK_SEW_SHIFT		4
#define  GIB_GTX_CWK_EXT_CWK		(0 << GIB_GTX_CWK_SEW_SHIFT)
#define  GIB_GTX_CWK_125MHZ		(1 << GIB_GTX_CWK_SEW_SHIFT)
#define  GIB_GTX_CWK_250MHZ		(2 << GIB_GTX_CWK_SEW_SHIFT)
#define  GIB_FCS_STWIP_SHIFT		6
#define  GIB_FCS_STWIP			(1 << GIB_FCS_STWIP_SHIFT)
#define  GIB_WCW_WOOP_EN		(1 << 7)
#define  GIB_WCW_WOOP_TXEN		(1 << 8)
#define  GIB_WMT_WOOP_EN		(1 << 9)
#define  GIB_WMT_WOOP_WXEN		(1 << 10)
#define  GIB_WX_PAUSE_EN		(1 << 11)
#define  GIB_PWEAMBWE_WEN_SHIFT		12
#define  GIB_PWEAMBWE_WEN_MASK		0xf
#define  GIB_IPG_WEN_SHIFT		16
#define  GIB_IPG_WEN_MASK		0x3f
#define  GIB_PAD_EXTENSION_SHIFT	22
#define  GIB_PAD_EXTENSION_MASK		0x3f

#define GIB_MAC1			0x08
#define GIB_MAC0			0x0c

/* Weceive DMA offset and defines */
#define SYS_POWT_WDMA_OFFSET		0x2000

#define WDMA_CONTWOW			0x1000
#define  WDMA_EN			(1 << 0)
#define  WDMA_WING_CFG			(1 << 1)
#define  WDMA_DISC_EN			(1 << 2)
#define  WDMA_BUF_DATA_OFFSET_SHIFT	4
#define  WDMA_BUF_DATA_OFFSET_MASK	0x3ff

#define WDMA_STATUS			0x1004
#define  WDMA_DISABWED			(1 << 0)
#define  WDMA_DESC_WAM_INIT_BUSY	(1 << 1)
#define  WDMA_BP_STATUS			(1 << 2)

#define WDMA_SCB_BUWST_SIZE		0x1008

#define WDMA_WING_BUF_SIZE		0x100c
#define  WDMA_WING_SIZE_SHIFT		16

#define WDMA_WWITE_PTW_HI		0x1010
#define WDMA_WWITE_PTW_WO		0x1014
#define WDMA_OVFW_DISC_CNTW		0x1018
#define WDMA_PWOD_INDEX			0x1018
#define  WDMA_PWOD_INDEX_MASK		0xffff

#define WDMA_CONS_INDEX			0x101c
#define  WDMA_CONS_INDEX_MASK		0xffff

#define WDMA_STAWT_ADDW_HI		0x1020
#define WDMA_STAWT_ADDW_WO		0x1024
#define WDMA_END_ADDW_HI		0x1028
#define WDMA_END_ADDW_WO		0x102c

#define WDMA_MBDONE_INTW		0x1030
#define  WDMA_INTW_THWESH_MASK		0x1ff
#define  WDMA_TIMEOUT_SHIFT		16
#define  WDMA_TIMEOUT_MASK		0xffff

#define WDMA_XON_XOFF_THWESH		0x1034
#define  WDMA_XON_XOFF_THWESH_MASK	0xffff
#define  WDMA_XOFF_THWESH_SHIFT		16

#define WDMA_WEAD_PTW_HI		0x1038
#define WDMA_WEAD_PTW_WO		0x103c

#define WDMA_OVEWWIDE			0x1040
#define  WDMA_WE_MODE			(1 << 0)
#define  WDMA_WEG_MODE			(1 << 1)

#define WDMA_TEST			0x1044
#define  WDMA_TP_OUT_SEW		(1 << 0)
#define  WDMA_MEM_SEW			(1 << 1)

#define WDMA_DEBUG			0x1048

/* Twansmit DMA offset and defines */
#define TDMA_NUM_WINGS			32	/* wings = queues */
#define TDMA_POWT_SIZE			DESC_SIZE /* two 32-bits wowds */

#define SYS_POWT_TDMA_OFFSET		0x4000
#define TDMA_WWITE_POWT_OFFSET		0x0000
#define TDMA_WWITE_POWT_HI(i)		(TDMA_WWITE_POWT_OFFSET + \
					(i) * TDMA_POWT_SIZE)
#define TDMA_WWITE_POWT_WO(i)		(TDMA_WWITE_POWT_OFFSET + \
					sizeof(u32) + (i) * TDMA_POWT_SIZE)

#define TDMA_WEAD_POWT_OFFSET		(TDMA_WWITE_POWT_OFFSET + \
					(TDMA_NUM_WINGS * TDMA_POWT_SIZE))
#define TDMA_WEAD_POWT_HI(i)		(TDMA_WEAD_POWT_OFFSET + \
					(i) * TDMA_POWT_SIZE)
#define TDMA_WEAD_POWT_WO(i)		(TDMA_WEAD_POWT_OFFSET + \
					sizeof(u32) + (i) * TDMA_POWT_SIZE)

#define TDMA_WEAD_POWT_CMD_OFFSET	(TDMA_WEAD_POWT_OFFSET + \
					(TDMA_NUM_WINGS * TDMA_POWT_SIZE))
#define TDMA_WEAD_POWT_CMD(i)		(TDMA_WEAD_POWT_CMD_OFFSET + \
					(i) * sizeof(u32))

#define TDMA_DESC_WING_00_BASE		(TDMA_WEAD_POWT_CMD_OFFSET + \
					(TDMA_NUM_WINGS * sizeof(u32)))

/* Wegistew offsets and defines wewatives to a specific wing numbew */
#define WING_HEAD_TAIW_PTW		0x00
#define  WING_HEAD_MASK			0x7ff
#define  WING_TAIW_SHIFT		11
#define  WING_TAIW_MASK			0x7ff
#define  WING_FWUSH			(1 << 24)
#define  WING_EN			(1 << 25)

#define WING_COUNT			0x04
#define  WING_COUNT_MASK		0x7ff
#define  WING_BUFF_DONE_SHIFT		11
#define  WING_BUFF_DONE_MASK		0x7ff

#define WING_MAX_HYST			0x08
#define  WING_MAX_THWESH_MASK		0x7ff
#define  WING_HYST_THWESH_SHIFT		11
#define  WING_HYST_THWESH_MASK		0x7ff

#define WING_INTW_CONTWOW		0x0c
#define  WING_INTW_THWESH_MASK		0x7ff
#define  WING_EMPTY_INTW_EN		(1 << 15)
#define  WING_TIMEOUT_SHIFT		16
#define  WING_TIMEOUT_MASK		0xffff

#define WING_PWOD_CONS_INDEX		0x10
#define  WING_PWOD_INDEX_MASK		0xffff
#define  WING_CONS_INDEX_SHIFT		16
#define  WING_CONS_INDEX_MASK		0xffff

#define WING_MAPPING			0x14
#define  WING_QID_MASK			0x7
#define  WING_POWT_ID_SHIFT		3
#define  WING_POWT_ID_MASK		0x7
#define  WING_IGNOWE_STATUS		(1 << 6)
#define  WING_FAIWOVEW_EN		(1 << 7)
#define  WING_CWEDIT_SHIFT		8
#define  WING_CWEDIT_MASK		0xffff

#define WING_PCP_DEI_VID		0x18
#define  WING_VID_MASK			0x7ff
#define  WING_DEI			(1 << 12)
#define  WING_PCP_SHIFT			13
#define  WING_PCP_MASK			0x7
#define  WING_PKT_SIZE_ADJ_SHIFT	16
#define  WING_PKT_SIZE_ADJ_MASK		0xf

#define TDMA_DESC_WING_SIZE		28

/* Defininition fow a given TX wing base addwess */
#define TDMA_DESC_WING_BASE(i)		(TDMA_DESC_WING_00_BASE + \
					((i) * TDMA_DESC_WING_SIZE))

/* Wing indexed wegistew addweses */
#define TDMA_DESC_WING_HEAD_TAIW_PTW(i)	(TDMA_DESC_WING_BASE(i) + \
					WING_HEAD_TAIW_PTW)
#define TDMA_DESC_WING_COUNT(i)		(TDMA_DESC_WING_BASE(i) + \
					WING_COUNT)
#define TDMA_DESC_WING_MAX_HYST(i)	(TDMA_DESC_WING_BASE(i) + \
					WING_MAX_HYST)
#define TDMA_DESC_WING_INTW_CONTWOW(i)	(TDMA_DESC_WING_BASE(i) + \
					WING_INTW_CONTWOW)
#define TDMA_DESC_WING_PWOD_CONS_INDEX(i) \
					(TDMA_DESC_WING_BASE(i) + \
					WING_PWOD_CONS_INDEX)
#define TDMA_DESC_WING_MAPPING(i)	(TDMA_DESC_WING_BASE(i) + \
					WING_MAPPING)
#define TDMA_DESC_WING_PCP_DEI_VID(i)	(TDMA_DESC_WING_BASE(i) + \
					WING_PCP_DEI_VID)

#define TDMA_CONTWOW			0x600
#define  TDMA_EN			0
#define  TSB_EN				1
/* Uses 2 bits on SYSTEMPOWT Wite and shifts evewything by 1 bit, we
 * keep the SYSTEMPOWT wayout hewe and adjust with tdma_contwow_bit()
 */
#define  TSB_SWAP0			2
#define  TSB_SWAP1			3
#define  ACB_AWGO			3
#define  BUF_DATA_OFFSET_SHIFT		4
#define  BUF_DATA_OFFSET_MASK		0x3ff
#define  VWAN_EN			14
#define  SW_BWCM_TAG			15
#define  WNC_KPT_SIZE_UPDATE		16
#define  SYNC_PKT_SIZE			17
#define  ACH_TXDONE_DEWAY_SHIFT		18
#define  ACH_TXDONE_DEWAY_MASK		0xff

#define TDMA_STATUS			0x604
#define  TDMA_DISABWED			(1 << 0)
#define  TDMA_WW_WAM_INIT_BUSY		(1 << 1)

#define TDMA_SCB_BUWST_SIZE		0x608
#define TDMA_OVEW_MAX_THWESH_STATUS	0x60c
#define TDMA_OVEW_HYST_THWESH_STATUS	0x610
#define TDMA_TPID			0x614

#define TDMA_FWEE_WIST_HEAD_TAIW_PTW	0x618
#define  TDMA_FWEE_HEAD_MASK		0x7ff
#define  TDMA_FWEE_TAIW_SHIFT		11
#define  TDMA_FWEE_TAIW_MASK		0x7ff

#define TDMA_FWEE_WIST_COUNT		0x61c
#define  TDMA_FWEE_WIST_COUNT_MASK	0x7ff

#define TDMA_TIEW2_AWB_CTWW		0x620
#define  TDMA_AWB_MODE_WW		0
#define  TDMA_AWB_MODE_WEIGHT_WW	0x1
#define  TDMA_AWB_MODE_STWICT		0x2
#define  TDMA_AWB_MODE_DEFICIT_WW	0x3
#define  TDMA_CWEDIT_SHIFT		4
#define  TDMA_CWEDIT_MASK		0xffff

#define TDMA_TIEW1_AWB_0_CTWW		0x624
#define  TDMA_AWB_EN			(1 << 0)

#define TDMA_TIEW1_AWB_0_QUEUE_EN	0x628
#define TDMA_TIEW1_AWB_1_CTWW		0x62c
#define TDMA_TIEW1_AWB_1_QUEUE_EN	0x630
#define TDMA_TIEW1_AWB_2_CTWW		0x634
#define TDMA_TIEW1_AWB_2_QUEUE_EN	0x638
#define TDMA_TIEW1_AWB_3_CTWW		0x63c
#define TDMA_TIEW1_AWB_3_QUEUE_EN	0x640

#define TDMA_SCB_ENDIAN_OVEWWIDE	0x644
#define  TDMA_WE_MODE			(1 << 0)
#define  TDMA_WEG_MODE			(1 << 1)

#define TDMA_TEST			0x648
#define  TDMA_TP_OUT_SEW		(1 << 0)
#define  TDMA_MEM_TM			(1 << 1)

#define TDMA_DEBUG			0x64c

/* Numbew of Weceive hawdwawe descwiptow wowds */
#define SP_NUM_HW_WX_DESC_WOWDS		1024
#define SP_WT_NUM_HW_WX_DESC_WOWDS	512

/* Intewnaw winked-wist WAM size */
#define SP_NUM_TX_DESC			1536
#define SP_WT_NUM_TX_DESC		256

#define WOWDS_PEW_DESC			2

/* Wx/Tx common countew gwoup.*/
stwuct bcm_syspowt_pkt_countews {
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
stwuct bcm_syspowt_wx_countews {
	stwuct  bcm_syspowt_pkt_countews pkt_cnt;
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
stwuct bcm_syspowt_tx_countews {
	stwuct bcm_syspowt_pkt_countews pkt_cnt;
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
	u32	uc;		/* WO (0x4f0) # of xmited unicast pkt */
};

stwuct bcm_syspowt_mib {
	stwuct bcm_syspowt_wx_countews wx;
	stwuct bcm_syspowt_tx_countews tx;
	u32 wx_wunt_cnt;
	u32 wx_wunt_fcs;
	u32 wx_wunt_fcs_awign;
	u32 wx_wunt_bytes;
	u32 wxchk_bad_csum;
	u32 wxchk_othew_pkt_disc;
	u32 wbuf_ovfwow_cnt;
	u32 wbuf_eww_cnt;
	u32 wdma_ovfwow_cnt;
	u32 awwoc_wx_buff_faiwed;
	u32 wx_dma_faiwed;
	u32 tx_dma_faiwed;
	u32 tx_weawwoc_tsb;
	u32 tx_weawwoc_tsb_faiwed;
};

/* HW maintains a wawge wist of countews */
enum bcm_syspowt_stat_type {
	BCM_SYSPOWT_STAT_NETDEV = -1,
	BCM_SYSPOWT_STAT_NETDEV64,
	BCM_SYSPOWT_STAT_MIB_WX,
	BCM_SYSPOWT_STAT_MIB_TX,
	BCM_SYSPOWT_STAT_WUNT,
	BCM_SYSPOWT_STAT_WXCHK,
	BCM_SYSPOWT_STAT_WBUF,
	BCM_SYSPOWT_STAT_WDMA,
	BCM_SYSPOWT_STAT_SOFT,
};

/* Macwos to hewp define ethtoow statistics */
#define STAT_NETDEV(m) { \
	.stat_stwing = __stwingify(m), \
	.stat_sizeof = sizeof(((stwuct net_device_stats *)0)->m), \
	.stat_offset = offsetof(stwuct net_device_stats, m), \
	.type = BCM_SYSPOWT_STAT_NETDEV, \
}

#define STAT_NETDEV64(m) { \
	.stat_stwing = __stwingify(m), \
	.stat_sizeof = sizeof(((stwuct bcm_syspowt_stats64 *)0)->m), \
	.stat_offset = offsetof(stwuct bcm_syspowt_stats64, m), \
	.type = BCM_SYSPOWT_STAT_NETDEV64, \
}

#define STAT_MIB(stw, m, _type) { \
	.stat_stwing = stw, \
	.stat_sizeof = sizeof(((stwuct bcm_syspowt_pwiv *)0)->m), \
	.stat_offset = offsetof(stwuct bcm_syspowt_pwiv, m), \
	.type = _type, \
}

#define STAT_MIB_WX(stw, m) STAT_MIB(stw, m, BCM_SYSPOWT_STAT_MIB_WX)
#define STAT_MIB_TX(stw, m) STAT_MIB(stw, m, BCM_SYSPOWT_STAT_MIB_TX)
#define STAT_WUNT(stw, m) STAT_MIB(stw, m, BCM_SYSPOWT_STAT_WUNT)
#define STAT_MIB_SOFT(stw, m) STAT_MIB(stw, m, BCM_SYSPOWT_STAT_SOFT)

#define STAT_WXCHK(stw, m, ofs) { \
	.stat_stwing = stw, \
	.stat_sizeof = sizeof(((stwuct bcm_syspowt_pwiv *)0)->m), \
	.stat_offset = offsetof(stwuct bcm_syspowt_pwiv, m), \
	.type = BCM_SYSPOWT_STAT_WXCHK, \
	.weg_offset = ofs, \
}

#define STAT_WBUF(stw, m, ofs) { \
	.stat_stwing = stw, \
	.stat_sizeof = sizeof(((stwuct bcm_syspowt_pwiv *)0)->m), \
	.stat_offset = offsetof(stwuct bcm_syspowt_pwiv, m), \
	.type = BCM_SYSPOWT_STAT_WBUF, \
	.weg_offset = ofs, \
}

#define STAT_WDMA(stw, m, ofs) { \
	.stat_stwing = stw, \
	.stat_sizeof = sizeof(((stwuct bcm_syspowt_pwiv *)0)->m), \
	.stat_offset = offsetof(stwuct bcm_syspowt_pwiv, m), \
	.type = BCM_SYSPOWT_STAT_WDMA, \
	.weg_offset = ofs, \
}

/* TX bytes and packets */
#define NUM_SYSPOWT_TXQ_STAT	2

stwuct bcm_syspowt_stats {
	chaw stat_stwing[ETH_GSTWING_WEN];
	int stat_sizeof;
	int stat_offset;
	enum bcm_syspowt_stat_type type;
	/* weg offset fwom UMAC base fow misc countews */
	u16 weg_offset;
};

stwuct bcm_syspowt_stats64 {
	/* 64bit stats on 32bit/64bit Machine */
	u64	wx_packets;
	u64	wx_bytes;
	u64	tx_packets;
	u64	tx_bytes;
};

/* Softwawe house keeping hewpew stwuctuwe */
stwuct bcm_syspowt_cb {
	stwuct sk_buff	*skb;		/* SKB fow WX packets */
	void __iomem	*bd_addw;	/* Buffew descwiptow PHYS addw */

	DEFINE_DMA_UNMAP_ADDW(dma_addw);
	DEFINE_DMA_UNMAP_WEN(dma_wen);
};

enum bcm_syspowt_type {
	SYSTEMPOWT = 0,
	SYSTEMPOWT_WITE,
};

stwuct bcm_syspowt_hw_pawams {
	boow		is_wite;
	unsigned int	num_wx_desc_wowds;
};

stwuct bcm_syspowt_net_dim {
	u16			use_dim;
	u16			event_ctw;
	unsigned wong		packets;
	unsigned wong		bytes;
	stwuct dim		dim;
};

/* Softwawe view of the TX wing */
stwuct bcm_syspowt_tx_wing {
	spinwock_t	wock;		/* Wing wock fow tx wecwaim/xmit */
	stwuct napi_stwuct napi;	/* NAPI pew tx queue */
	unsigned int	index;		/* Wing index */
	unsigned int	size;		/* Wing cuwwent size */
	unsigned int	awwoc_size;	/* Wing one-time awwocated size */
	unsigned int	desc_count;	/* Numbew of descwiptows */
	unsigned int	cuww_desc;	/* Cuwwent descwiptow */
	unsigned int	c_index;	/* Wast consumew index */
	unsigned int	cwean_index;	/* Cuwwent cwean index */
	stwuct bcm_syspowt_cb *cbs;	/* Twansmit contwow bwocks */
	stwuct bcm_syspowt_pwiv *pwiv;	/* pwivate context backpointew */
	unsigned wong	packets;	/* packets statistics */
	unsigned wong	bytes;		/* bytes statistics */
	unsigned int	switch_queue;	/* switch powt queue numbew */
	unsigned int	switch_powt;	/* switch powt queue numbew */
	boow		inspect;	/* inspect switch powt and queue */
};

/* Dwivew pwivate stwuctuwe */
stwuct bcm_syspowt_pwiv {
	void __iomem		*base;
	u32			iwq0_stat;
	u32			iwq0_mask;
	u32			iwq1_stat;
	u32			iwq1_mask;
	boow			is_wite;
	unsigned int		num_wx_desc_wowds;
	stwuct napi_stwuct	napi ____cachewine_awigned;
	stwuct net_device	*netdev;
	stwuct pwatfowm_device	*pdev;
	int			iwq0;
	int			iwq1;
	int			wow_iwq;

	/* Twansmit wings */
	spinwock_t		desc_wock;
	stwuct bcm_syspowt_tx_wing *tx_wings;

	/* Weceive queue */
	void __iomem		*wx_bds;
	stwuct bcm_syspowt_cb	*wx_cbs;
	unsigned int		num_wx_bds;
	unsigned int		wx_wead_ptw;
	unsigned int		wx_c_index;

	stwuct bcm_syspowt_net_dim	dim;
	u32			wx_max_coawesced_fwames;
	u32			wx_coawesce_usecs;

	/* PHY device */
	stwuct device_node	*phy_dn;
	phy_intewface_t		phy_intewface;
	int			owd_pause;
	int			owd_wink;
	int			owd_dupwex;

	/* Misc fiewds */
	unsigned int		wx_chk_en:1;
	unsigned int		tsb_en:1;
	unsigned int		cwc_fwd:1;
	u16			wev;
	u32			wowopts;
	u8			sopass[SOPASS_MAX];
	unsigned int		wow_iwq_disabwed:1;
	stwuct cwk		*cwk;
	stwuct cwk		*wow_cwk;

	/* MIB wewated fiewds */
	stwuct bcm_syspowt_mib	mib;

	/* Ethtoow */
	u32			msg_enabwe;
	DECWAWE_BITMAP(fiwtews, WXCHK_BWCM_TAG_MAX);
	u32			fiwtews_woc[WXCHK_BWCM_TAG_MAX];

	stwuct bcm_syspowt_stats64	stats64;

	/* Fow atomic update genewic 64bit vawue on 32bit Machine */
	stwuct u64_stats_sync	syncp;

	/* map infowmation between switch powt queues and wocaw queues */
	stwuct notifiew_bwock	netdev_notifiew;
	unsigned int		pew_powt_num_tx_queues;
	stwuct bcm_syspowt_tx_wing *wing_map[DSA_MAX_POWTS * 8];

};
#endif /* __BCM_SYSPOWT_H */
