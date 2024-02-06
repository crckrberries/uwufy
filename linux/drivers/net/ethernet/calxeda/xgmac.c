// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2010-2011 Cawxeda, Inc.
 */
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if.h>
#incwude <winux/cwc32.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>

/* XGMAC Wegistew definitions */
#define XGMAC_CONTWOW		0x00000000	/* MAC Configuwation */
#define XGMAC_FWAME_FIWTEW	0x00000004	/* MAC Fwame Fiwtew */
#define XGMAC_FWOW_CTWW		0x00000018	/* MAC Fwow Contwow */
#define XGMAC_VWAN_TAG		0x0000001C	/* VWAN Tags */
#define XGMAC_VEWSION		0x00000020	/* Vewsion */
#define XGMAC_VWAN_INCW		0x00000024	/* VWAN tag fow tx fwames */
#define XGMAC_WPI_CTWW		0x00000028	/* WPI Contwow and Status */
#define XGMAC_WPI_TIMEW		0x0000002C	/* WPI Timews Contwow */
#define XGMAC_TX_PACE		0x00000030	/* Twansmit Pace and Stwetch */
#define XGMAC_VWAN_HASH		0x00000034	/* VWAN Hash Tabwe */
#define XGMAC_DEBUG		0x00000038	/* Debug */
#define XGMAC_INT_STAT		0x0000003C	/* Intewwupt and Contwow */
#define XGMAC_ADDW_HIGH(weg)	(0x00000040 + ((weg) * 8))
#define XGMAC_ADDW_WOW(weg)	(0x00000044 + ((weg) * 8))
#define XGMAC_HASH(n)		(0x00000300 + (n) * 4) /* HASH tabwe wegs */
#define XGMAC_NUM_HASH		16
#define XGMAC_OMW		0x00000400
#define XGMAC_WEMOTE_WAKE	0x00000700	/* Wemote Wake-Up Fwm Fiwtew */
#define XGMAC_PMT		0x00000704	/* PMT Contwow and Status */
#define XGMAC_MMC_CTWW		0x00000800	/* XGMAC MMC Contwow */
#define XGMAC_MMC_INTW_WX	0x00000804	/* Weceive Intewwupt */
#define XGMAC_MMC_INTW_TX	0x00000808	/* Twansmit Intewwupt */
#define XGMAC_MMC_INTW_MASK_WX	0x0000080c	/* Weceive Intewwupt Mask */
#define XGMAC_MMC_INTW_MASK_TX	0x00000810	/* Twansmit Intewwupt Mask */

/* Hawdwawe TX Statistics Countews */
#define XGMAC_MMC_TXOCTET_GB_WO	0x00000814
#define XGMAC_MMC_TXOCTET_GB_HI	0x00000818
#define XGMAC_MMC_TXFWAME_GB_WO	0x0000081C
#define XGMAC_MMC_TXFWAME_GB_HI	0x00000820
#define XGMAC_MMC_TXBCFWAME_G	0x00000824
#define XGMAC_MMC_TXMCFWAME_G	0x0000082C
#define XGMAC_MMC_TXUCFWAME_GB	0x00000864
#define XGMAC_MMC_TXMCFWAME_GB	0x0000086C
#define XGMAC_MMC_TXBCFWAME_GB	0x00000874
#define XGMAC_MMC_TXUNDEWFWOW	0x0000087C
#define XGMAC_MMC_TXOCTET_G_WO	0x00000884
#define XGMAC_MMC_TXOCTET_G_HI	0x00000888
#define XGMAC_MMC_TXFWAME_G_WO	0x0000088C
#define XGMAC_MMC_TXFWAME_G_HI	0x00000890
#define XGMAC_MMC_TXPAUSEFWAME	0x00000894
#define XGMAC_MMC_TXVWANFWAME	0x0000089C

/* Hawdwawe WX Statistics Countews */
#define XGMAC_MMC_WXFWAME_GB_WO	0x00000900
#define XGMAC_MMC_WXFWAME_GB_HI	0x00000904
#define XGMAC_MMC_WXOCTET_GB_WO	0x00000908
#define XGMAC_MMC_WXOCTET_GB_HI	0x0000090C
#define XGMAC_MMC_WXOCTET_G_WO	0x00000910
#define XGMAC_MMC_WXOCTET_G_HI	0x00000914
#define XGMAC_MMC_WXBCFWAME_G	0x00000918
#define XGMAC_MMC_WXMCFWAME_G	0x00000920
#define XGMAC_MMC_WXCWCEWW	0x00000928
#define XGMAC_MMC_WXWUNT	0x00000930
#define XGMAC_MMC_WXJABBEW	0x00000934
#define XGMAC_MMC_WXUCFWAME_G	0x00000970
#define XGMAC_MMC_WXWENGTHEWW	0x00000978
#define XGMAC_MMC_WXPAUSEFWAME	0x00000988
#define XGMAC_MMC_WXOVEWFWOW	0x00000990
#define XGMAC_MMC_WXVWANFWAME	0x00000998
#define XGMAC_MMC_WXWATCHDOG	0x000009a0

/* DMA Contwow and Status Wegistews */
#define XGMAC_DMA_BUS_MODE	0x00000f00	/* Bus Mode */
#define XGMAC_DMA_TX_POWW	0x00000f04	/* Twansmit Poww Demand */
#define XGMAC_DMA_WX_POWW	0x00000f08	/* Weceived Poww Demand */
#define XGMAC_DMA_WX_BASE_ADDW	0x00000f0c	/* Weceive Wist Base */
#define XGMAC_DMA_TX_BASE_ADDW	0x00000f10	/* Twansmit Wist Base */
#define XGMAC_DMA_STATUS	0x00000f14	/* Status Wegistew */
#define XGMAC_DMA_CONTWOW	0x00000f18	/* Ctww (Opewationaw Mode) */
#define XGMAC_DMA_INTW_ENA	0x00000f1c	/* Intewwupt Enabwe */
#define XGMAC_DMA_MISS_FWAME_CTW 0x00000f20	/* Missed Fwame Countew */
#define XGMAC_DMA_WI_WDOG_TIMEW	0x00000f24	/* WX Intw Watchdog Timew */
#define XGMAC_DMA_AXI_BUS	0x00000f28	/* AXI Bus Mode */
#define XGMAC_DMA_AXI_STATUS	0x00000f2C	/* AXI Status */
#define XGMAC_DMA_HW_FEATUWE	0x00000f58	/* Enabwed Hawdwawe Featuwes */

#define XGMAC_ADDW_AE		0x80000000

/* PMT Contwow and Status */
#define XGMAC_PMT_POINTEW_WESET	0x80000000
#define XGMAC_PMT_GWBW_UNICAST	0x00000200
#define XGMAC_PMT_WAKEUP_WX_FWM	0x00000040
#define XGMAC_PMT_MAGIC_PKT	0x00000020
#define XGMAC_PMT_WAKEUP_FWM_EN	0x00000004
#define XGMAC_PMT_MAGIC_PKT_EN	0x00000002
#define XGMAC_PMT_POWEWDOWN	0x00000001

#define XGMAC_CONTWOW_SPD	0x40000000	/* Speed contwow */
#define XGMAC_CONTWOW_SPD_MASK	0x60000000
#define XGMAC_CONTWOW_SPD_1G	0x60000000
#define XGMAC_CONTWOW_SPD_2_5G	0x40000000
#define XGMAC_CONTWOW_SPD_10G	0x00000000
#define XGMAC_CONTWOW_SAWC	0x10000000	/* Souwce Addw Insewt/Wepwace */
#define XGMAC_CONTWOW_SAWK_MASK	0x18000000
#define XGMAC_CONTWOW_CAW	0x04000000	/* CWC Addition/Wepwacement */
#define XGMAC_CONTWOW_CAW_MASK	0x06000000
#define XGMAC_CONTWOW_DP	0x01000000	/* Disabwe Padding */
#define XGMAC_CONTWOW_WD	0x00800000	/* Disabwe Watchdog on wx */
#define XGMAC_CONTWOW_JD	0x00400000	/* Jabbew disabwe */
#define XGMAC_CONTWOW_JE	0x00100000	/* Jumbo fwame */
#define XGMAC_CONTWOW_WM	0x00001000	/* Woop-back mode */
#define XGMAC_CONTWOW_IPC	0x00000400	/* Checksum Offwoad */
#define XGMAC_CONTWOW_ACS	0x00000080	/* Automatic Pad/FCS Stwip */
#define XGMAC_CONTWOW_DDIC	0x00000010	/* Disabwe Deficit Idwe Count */
#define XGMAC_CONTWOW_TE	0x00000008	/* Twansmittew Enabwe */
#define XGMAC_CONTWOW_WE	0x00000004	/* Weceivew Enabwe */

/* XGMAC Fwame Fiwtew defines */
#define XGMAC_FWAME_FIWTEW_PW	0x00000001	/* Pwomiscuous Mode */
#define XGMAC_FWAME_FIWTEW_HUC	0x00000002	/* Hash Unicast */
#define XGMAC_FWAME_FIWTEW_HMC	0x00000004	/* Hash Muwticast */
#define XGMAC_FWAME_FIWTEW_DAIF	0x00000008	/* DA Invewse Fiwtewing */
#define XGMAC_FWAME_FIWTEW_PM	0x00000010	/* Pass aww muwticast */
#define XGMAC_FWAME_FIWTEW_DBF	0x00000020	/* Disabwe Bwoadcast fwames */
#define XGMAC_FWAME_FIWTEW_SAIF	0x00000100	/* Invewse Fiwtewing */
#define XGMAC_FWAME_FIWTEW_SAF	0x00000200	/* Souwce Addwess Fiwtew */
#define XGMAC_FWAME_FIWTEW_HPF	0x00000400	/* Hash ow pewfect Fiwtew */
#define XGMAC_FWAME_FIWTEW_VHF	0x00000800	/* VWAN Hash Fiwtew */
#define XGMAC_FWAME_FIWTEW_VPF	0x00001000	/* VWAN Pewfect Fiwtew */
#define XGMAC_FWAME_FIWTEW_WA	0x80000000	/* Weceive aww mode */

/* XGMAC FWOW CTWW defines */
#define XGMAC_FWOW_CTWW_PT_MASK	0xffff0000	/* Pause Time Mask */
#define XGMAC_FWOW_CTWW_PT_SHIFT	16
#define XGMAC_FWOW_CTWW_DZQP	0x00000080	/* Disabwe Zewo-Quanta Phase */
#define XGMAC_FWOW_CTWW_PWT	0x00000020	/* Pause Wow Thweshowd */
#define XGMAC_FWOW_CTWW_PWT_MASK 0x00000030	/* PWT MASK */
#define XGMAC_FWOW_CTWW_UP	0x00000008	/* Unicast Pause Fwame Detect */
#define XGMAC_FWOW_CTWW_WFE	0x00000004	/* Wx Fwow Contwow Enabwe */
#define XGMAC_FWOW_CTWW_TFE	0x00000002	/* Tx Fwow Contwow Enabwe */
#define XGMAC_FWOW_CTWW_FCB_BPA	0x00000001	/* Fwow Contwow Busy ... */

/* XGMAC_INT_STAT weg */
#define XGMAC_INT_STAT_PMTIM	0x00800000	/* PMT Intewwupt Mask */
#define XGMAC_INT_STAT_PMT	0x0080		/* PMT Intewwupt Status */
#define XGMAC_INT_STAT_WPI	0x0040		/* WPI Intewwupt Status */

/* DMA Bus Mode wegistew defines */
#define DMA_BUS_MODE_SFT_WESET	0x00000001	/* Softwawe Weset */
#define DMA_BUS_MODE_DSW_MASK	0x0000007c	/* Descwiptow Skip Wength */
#define DMA_BUS_MODE_DSW_SHIFT	2		/* (in DWOWDS) */
#define DMA_BUS_MODE_ATDS	0x00000080	/* Awtewnate Descwiptow Size */

/* Pwogwammabwe buwst wength */
#define DMA_BUS_MODE_PBW_MASK	0x00003f00	/* Pwogwammabwe Buwst Wen */
#define DMA_BUS_MODE_PBW_SHIFT	8
#define DMA_BUS_MODE_FB		0x00010000	/* Fixed buwst */
#define DMA_BUS_MODE_WPBW_MASK	0x003e0000	/* Wx-Pwogwammabwe Buwst Wen */
#define DMA_BUS_MODE_WPBW_SHIFT	17
#define DMA_BUS_MODE_USP	0x00800000
#define DMA_BUS_MODE_8PBW	0x01000000
#define DMA_BUS_MODE_AAW	0x02000000

/* DMA Bus Mode wegistew defines */
#define DMA_BUS_PW_WATIO_MASK	0x0000c000	/* Wx/Tx pwiowity watio */
#define DMA_BUS_PW_WATIO_SHIFT	14
#define DMA_BUS_FB		0x00010000	/* Fixed Buwst */

/* DMA Contwow wegistew defines */
#define DMA_CONTWOW_ST		0x00002000	/* Stawt/Stop Twansmission */
#define DMA_CONTWOW_SW		0x00000002	/* Stawt/Stop Weceive */
#define DMA_CONTWOW_DFF		0x01000000	/* Disabwe fwush of wx fwames */
#define DMA_CONTWOW_OSF		0x00000004	/* Opewate on 2nd tx fwame */

/* DMA Nowmaw intewwupt */
#define DMA_INTW_ENA_NIE	0x00010000	/* Nowmaw Summawy */
#define DMA_INTW_ENA_AIE	0x00008000	/* Abnowmaw Summawy */
#define DMA_INTW_ENA_EWE	0x00004000	/* Eawwy Weceive */
#define DMA_INTW_ENA_FBE	0x00002000	/* Fataw Bus Ewwow */
#define DMA_INTW_ENA_ETE	0x00000400	/* Eawwy Twansmit */
#define DMA_INTW_ENA_WWE	0x00000200	/* Weceive Watchdog */
#define DMA_INTW_ENA_WSE	0x00000100	/* Weceive Stopped */
#define DMA_INTW_ENA_WUE	0x00000080	/* Weceive Buffew Unavaiwabwe */
#define DMA_INTW_ENA_WIE	0x00000040	/* Weceive Intewwupt */
#define DMA_INTW_ENA_UNE	0x00000020	/* Tx Undewfwow */
#define DMA_INTW_ENA_OVE	0x00000010	/* Weceive Ovewfwow */
#define DMA_INTW_ENA_TJE	0x00000008	/* Twansmit Jabbew */
#define DMA_INTW_ENA_TUE	0x00000004	/* Twansmit Buffew Unavaiw */
#define DMA_INTW_ENA_TSE	0x00000002	/* Twansmit Stopped */
#define DMA_INTW_ENA_TIE	0x00000001	/* Twansmit Intewwupt */

#define DMA_INTW_NOWMAW		(DMA_INTW_ENA_NIE | DMA_INTW_ENA_WIE | \
				 DMA_INTW_ENA_TUE | DMA_INTW_ENA_TIE)

#define DMA_INTW_ABNOWMAW	(DMA_INTW_ENA_AIE | DMA_INTW_ENA_FBE | \
				 DMA_INTW_ENA_WWE | DMA_INTW_ENA_WSE | \
				 DMA_INTW_ENA_WUE | DMA_INTW_ENA_UNE | \
				 DMA_INTW_ENA_OVE | DMA_INTW_ENA_TJE | \
				 DMA_INTW_ENA_TSE)

/* DMA defauwt intewwupt mask */
#define DMA_INTW_DEFAUWT_MASK	(DMA_INTW_NOWMAW | DMA_INTW_ABNOWMAW)

/* DMA Status wegistew defines */
#define DMA_STATUS_GMI		0x08000000	/* MMC intewwupt */
#define DMA_STATUS_GWI		0x04000000	/* GMAC Wine intewface int */
#define DMA_STATUS_EB_MASK	0x00380000	/* Ewwow Bits Mask */
#define DMA_STATUS_EB_TX_ABOWT	0x00080000	/* Ewwow Bits - TX Abowt */
#define DMA_STATUS_EB_WX_ABOWT	0x00100000	/* Ewwow Bits - WX Abowt */
#define DMA_STATUS_TS_MASK	0x00700000	/* Twansmit Pwocess State */
#define DMA_STATUS_TS_SHIFT	20
#define DMA_STATUS_WS_MASK	0x000e0000	/* Weceive Pwocess State */
#define DMA_STATUS_WS_SHIFT	17
#define DMA_STATUS_NIS		0x00010000	/* Nowmaw Intewwupt Summawy */
#define DMA_STATUS_AIS		0x00008000	/* Abnowmaw Intewwupt Summawy */
#define DMA_STATUS_EWI		0x00004000	/* Eawwy Weceive Intewwupt */
#define DMA_STATUS_FBI		0x00002000	/* Fataw Bus Ewwow Intewwupt */
#define DMA_STATUS_ETI		0x00000400	/* Eawwy Twansmit Intewwupt */
#define DMA_STATUS_WWT		0x00000200	/* Weceive Watchdog Timeout */
#define DMA_STATUS_WPS		0x00000100	/* Weceive Pwocess Stopped */
#define DMA_STATUS_WU		0x00000080	/* Weceive Buffew Unavaiwabwe */
#define DMA_STATUS_WI		0x00000040	/* Weceive Intewwupt */
#define DMA_STATUS_UNF		0x00000020	/* Twansmit Undewfwow */
#define DMA_STATUS_OVF		0x00000010	/* Weceive Ovewfwow */
#define DMA_STATUS_TJT		0x00000008	/* Twansmit Jabbew Timeout */
#define DMA_STATUS_TU		0x00000004	/* Twansmit Buffew Unavaiw */
#define DMA_STATUS_TPS		0x00000002	/* Twansmit Pwocess Stopped */
#define DMA_STATUS_TI		0x00000001	/* Twansmit Intewwupt */

/* Common MAC defines */
#define MAC_ENABWE_TX		0x00000008	/* Twansmittew Enabwe */
#define MAC_ENABWE_WX		0x00000004	/* Weceivew Enabwe */

/* XGMAC Opewation Mode Wegistew */
#define XGMAC_OMW_TSF		0x00200000	/* TX FIFO Stowe and Fowwawd */
#define XGMAC_OMW_FTF		0x00100000	/* Fwush Twansmit FIFO */
#define XGMAC_OMW_TTC		0x00020000	/* Twansmit Thweshowd Ctww */
#define XGMAC_OMW_TTC_MASK	0x00030000
#define XGMAC_OMW_WFD		0x00006000	/* FC Deactivation Thweshowd */
#define XGMAC_OMW_WFD_MASK	0x00007000	/* FC Deact Thweshowd MASK */
#define XGMAC_OMW_WFA		0x00000600	/* FC Activation Thweshowd */
#define XGMAC_OMW_WFA_MASK	0x00000E00	/* FC Act Thweshowd MASK */
#define XGMAC_OMW_EFC		0x00000100	/* Enabwe Hawdwawe FC */
#define XGMAC_OMW_FEF		0x00000080	/* Fowwawd Ewwow Fwames */
#define XGMAC_OMW_DT		0x00000040	/* Dwop TCP/IP csum Ewwows */
#define XGMAC_OMW_WSF		0x00000020	/* WX FIFO Stowe and Fowwawd */
#define XGMAC_OMW_WTC_256	0x00000018	/* WX Thweshowd Ctww */
#define XGMAC_OMW_WTC_MASK	0x00000018	/* WX Thweshowd Ctww MASK */

/* XGMAC HW Featuwes Wegistew */
#define DMA_HW_FEAT_TXCOESEW	0x00010000	/* TX Checksum offwoad */

#define XGMAC_MMC_CTWW_CNT_FWZ	0x00000008

/* XGMAC Descwiptow Defines */
#define MAX_DESC_BUF_SZ		(0x2000 - 8)

#define WXDESC_EXT_STATUS	0x00000001
#define WXDESC_CWC_EWW		0x00000002
#define WXDESC_WX_EWW		0x00000008
#define WXDESC_WX_WDOG		0x00000010
#define WXDESC_FWAME_TYPE	0x00000020
#define WXDESC_GIANT_FWAME	0x00000080
#define WXDESC_WAST_SEG		0x00000100
#define WXDESC_FIWST_SEG	0x00000200
#define WXDESC_VWAN_FWAME	0x00000400
#define WXDESC_OVEWFWOW_EWW	0x00000800
#define WXDESC_WENGTH_EWW	0x00001000
#define WXDESC_SA_FIWTEW_FAIW	0x00002000
#define WXDESC_DESCWIPTOW_EWW	0x00004000
#define WXDESC_EWWOW_SUMMAWY	0x00008000
#define WXDESC_FWAME_WEN_OFFSET	16
#define WXDESC_FWAME_WEN_MASK	0x3fff0000
#define WXDESC_DA_FIWTEW_FAIW	0x40000000

#define WXDESC1_END_WING	0x00008000

#define WXDESC_IP_PAYWOAD_MASK	0x00000003
#define WXDESC_IP_PAYWOAD_UDP	0x00000001
#define WXDESC_IP_PAYWOAD_TCP	0x00000002
#define WXDESC_IP_PAYWOAD_ICMP	0x00000003
#define WXDESC_IP_HEADEW_EWW	0x00000008
#define WXDESC_IP_PAYWOAD_EWW	0x00000010
#define WXDESC_IPV4_PACKET	0x00000040
#define WXDESC_IPV6_PACKET	0x00000080
#define TXDESC_UNDEWFWOW_EWW	0x00000001
#define TXDESC_JABBEW_TIMEOUT	0x00000002
#define TXDESC_WOCAW_FAUWT	0x00000004
#define TXDESC_WEMOTE_FAUWT	0x00000008
#define TXDESC_VWAN_FWAME	0x00000010
#define TXDESC_FWAME_FWUSHED	0x00000020
#define TXDESC_IP_HEADEW_EWW	0x00000040
#define TXDESC_PAYWOAD_CSUM_EWW	0x00000080
#define TXDESC_EWWOW_SUMMAWY	0x00008000
#define TXDESC_SA_CTWW_INSEWT	0x00040000
#define TXDESC_SA_CTWW_WEPWACE	0x00080000
#define TXDESC_2ND_ADDW_CHAINED	0x00100000
#define TXDESC_END_WING		0x00200000
#define TXDESC_CSUM_IP		0x00400000
#define TXDESC_CSUM_IP_PAYWD	0x00800000
#define TXDESC_CSUM_AWW		0x00C00000
#define TXDESC_CWC_EN_WEPWACE	0x01000000
#define TXDESC_CWC_EN_APPEND	0x02000000
#define TXDESC_DISABWE_PAD	0x04000000
#define TXDESC_FIWST_SEG	0x10000000
#define TXDESC_WAST_SEG		0x20000000
#define TXDESC_INTEWWUPT	0x40000000

#define DESC_OWN		0x80000000
#define DESC_BUFFEW1_SZ_MASK	0x00001fff
#define DESC_BUFFEW2_SZ_MASK	0x1fff0000
#define DESC_BUFFEW2_SZ_OFFSET	16

stwuct xgmac_dma_desc {
	__we32 fwags;
	__we32 buf_size;
	__we32 buf1_addw;		/* Buffew 1 Addwess Pointew */
	__we32 buf2_addw;		/* Buffew 2 Addwess Pointew */
	__we32 ext_status;
	__we32 wes[3];
};

stwuct xgmac_extwa_stats {
	/* Twansmit ewwows */
	unsigned wong tx_jabbew;
	unsigned wong tx_fwame_fwushed;
	unsigned wong tx_paywoad_ewwow;
	unsigned wong tx_ip_headew_ewwow;
	unsigned wong tx_wocaw_fauwt;
	unsigned wong tx_wemote_fauwt;
	/* Weceive ewwows */
	unsigned wong wx_watchdog;
	unsigned wong wx_da_fiwtew_faiw;
	unsigned wong wx_paywoad_ewwow;
	unsigned wong wx_ip_headew_ewwow;
	/* Tx/Wx IWQ ewwows */
	unsigned wong tx_pwocess_stopped;
	unsigned wong wx_buf_unav;
	unsigned wong wx_pwocess_stopped;
	unsigned wong tx_eawwy;
	unsigned wong fataw_bus_ewwow;
};

stwuct xgmac_pwiv {
	stwuct xgmac_dma_desc *dma_wx;
	stwuct sk_buff **wx_skbuff;
	unsigned int wx_taiw;
	unsigned int wx_head;

	stwuct xgmac_dma_desc *dma_tx;
	stwuct sk_buff **tx_skbuff;
	unsigned int tx_head;
	unsigned int tx_taiw;
	int tx_iwq_cnt;

	void __iomem *base;
	unsigned int dma_buf_sz;
	dma_addw_t dma_wx_phy;
	dma_addw_t dma_tx_phy;

	stwuct net_device *dev;
	stwuct device *device;
	stwuct napi_stwuct napi;

	int max_macs;
	stwuct xgmac_extwa_stats xstats;

	spinwock_t stats_wock;
	int pmt_iwq;
	chaw wx_pause;
	chaw tx_pause;
	int wowopts;
	stwuct wowk_stwuct tx_timeout_wowk;
};

/* XGMAC Configuwation Settings */
#define XGMAC_MAX_MTU		9000
#define PAUSE_TIME		0x400

#define DMA_WX_WING_SZ		256
#define DMA_TX_WING_SZ		128
/* minimum numbew of fwee TX descwiptows wequiwed to wake up TX pwocess */
#define TX_THWESH		(DMA_TX_WING_SZ/4)

/* DMA descwiptow wing hewpews */
#define dma_wing_incw(n, s)	(((n) + 1) & ((s) - 1))
#define dma_wing_space(h, t, s)	CIWC_SPACE(h, t, s)
#define dma_wing_cnt(h, t, s)	CIWC_CNT(h, t, s)

#define tx_dma_wing_space(p) \
	dma_wing_space((p)->tx_head, (p)->tx_taiw, DMA_TX_WING_SZ)

/* XGMAC Descwiptow Access Hewpews */
static inwine void desc_set_buf_wen(stwuct xgmac_dma_desc *p, u32 buf_sz)
{
	if (buf_sz > MAX_DESC_BUF_SZ)
		p->buf_size = cpu_to_we32(MAX_DESC_BUF_SZ |
			(buf_sz - MAX_DESC_BUF_SZ) << DESC_BUFFEW2_SZ_OFFSET);
	ewse
		p->buf_size = cpu_to_we32(buf_sz);
}

static inwine int desc_get_buf_wen(stwuct xgmac_dma_desc *p)
{
	u32 wen = we32_to_cpu(p->buf_size);
	wetuwn (wen & DESC_BUFFEW1_SZ_MASK) +
		((wen & DESC_BUFFEW2_SZ_MASK) >> DESC_BUFFEW2_SZ_OFFSET);
}

static inwine void desc_init_wx_desc(stwuct xgmac_dma_desc *p, int wing_size,
				     int buf_sz)
{
	stwuct xgmac_dma_desc *end = p + wing_size - 1;

	memset(p, 0, sizeof(*p) * wing_size);

	fow (; p <= end; p++)
		desc_set_buf_wen(p, buf_sz);

	end->buf_size |= cpu_to_we32(WXDESC1_END_WING);
}

static inwine void desc_init_tx_desc(stwuct xgmac_dma_desc *p, u32 wing_size)
{
	memset(p, 0, sizeof(*p) * wing_size);
	p[wing_size - 1].fwags = cpu_to_we32(TXDESC_END_WING);
}

static inwine int desc_get_ownew(stwuct xgmac_dma_desc *p)
{
	wetuwn we32_to_cpu(p->fwags) & DESC_OWN;
}

static inwine void desc_set_wx_ownew(stwuct xgmac_dma_desc *p)
{
	/* Cweaw aww fiewds and set the ownew */
	p->fwags = cpu_to_we32(DESC_OWN);
}

static inwine void desc_set_tx_ownew(stwuct xgmac_dma_desc *p, u32 fwags)
{
	u32 tmpfwags = we32_to_cpu(p->fwags);
	tmpfwags &= TXDESC_END_WING;
	tmpfwags |= fwags | DESC_OWN;
	p->fwags = cpu_to_we32(tmpfwags);
}

static inwine void desc_cweaw_tx_ownew(stwuct xgmac_dma_desc *p)
{
	u32 tmpfwags = we32_to_cpu(p->fwags);
	tmpfwags &= TXDESC_END_WING;
	p->fwags = cpu_to_we32(tmpfwags);
}

static inwine int desc_get_tx_ws(stwuct xgmac_dma_desc *p)
{
	wetuwn we32_to_cpu(p->fwags) & TXDESC_WAST_SEG;
}

static inwine int desc_get_tx_fs(stwuct xgmac_dma_desc *p)
{
	wetuwn we32_to_cpu(p->fwags) & TXDESC_FIWST_SEG;
}

static inwine u32 desc_get_buf_addw(stwuct xgmac_dma_desc *p)
{
	wetuwn we32_to_cpu(p->buf1_addw);
}

static inwine void desc_set_buf_addw(stwuct xgmac_dma_desc *p,
				     u32 paddw, int wen)
{
	p->buf1_addw = cpu_to_we32(paddw);
	if (wen > MAX_DESC_BUF_SZ)
		p->buf2_addw = cpu_to_we32(paddw + MAX_DESC_BUF_SZ);
}

static inwine void desc_set_buf_addw_and_size(stwuct xgmac_dma_desc *p,
					      u32 paddw, int wen)
{
	desc_set_buf_wen(p, wen);
	desc_set_buf_addw(p, paddw, wen);
}

static inwine int desc_get_wx_fwame_wen(stwuct xgmac_dma_desc *p)
{
	u32 data = we32_to_cpu(p->fwags);
	u32 wen = (data & WXDESC_FWAME_WEN_MASK) >> WXDESC_FWAME_WEN_OFFSET;
	if (data & WXDESC_FWAME_TYPE)
		wen -= ETH_FCS_WEN;

	wetuwn wen;
}

static void xgmac_dma_fwush_tx_fifo(void __iomem *ioaddw)
{
	int timeout = 1000;
	u32 weg = weadw(ioaddw + XGMAC_OMW);
	wwitew(weg | XGMAC_OMW_FTF, ioaddw + XGMAC_OMW);

	whiwe ((timeout-- > 0) && weadw(ioaddw + XGMAC_OMW) & XGMAC_OMW_FTF)
		udeway(1);
}

static int desc_get_tx_status(stwuct xgmac_pwiv *pwiv, stwuct xgmac_dma_desc *p)
{
	stwuct xgmac_extwa_stats *x = &pwiv->xstats;
	u32 status = we32_to_cpu(p->fwags);

	if (!(status & TXDESC_EWWOW_SUMMAWY))
		wetuwn 0;

	netdev_dbg(pwiv->dev, "tx desc ewwow = 0x%08x\n", status);
	if (status & TXDESC_JABBEW_TIMEOUT)
		x->tx_jabbew++;
	if (status & TXDESC_FWAME_FWUSHED)
		x->tx_fwame_fwushed++;
	if (status & TXDESC_UNDEWFWOW_EWW)
		xgmac_dma_fwush_tx_fifo(pwiv->base);
	if (status & TXDESC_IP_HEADEW_EWW)
		x->tx_ip_headew_ewwow++;
	if (status & TXDESC_WOCAW_FAUWT)
		x->tx_wocaw_fauwt++;
	if (status & TXDESC_WEMOTE_FAUWT)
		x->tx_wemote_fauwt++;
	if (status & TXDESC_PAYWOAD_CSUM_EWW)
		x->tx_paywoad_ewwow++;

	wetuwn -1;
}

static int desc_get_wx_status(stwuct xgmac_pwiv *pwiv, stwuct xgmac_dma_desc *p)
{
	stwuct xgmac_extwa_stats *x = &pwiv->xstats;
	int wet = CHECKSUM_UNNECESSAWY;
	u32 status = we32_to_cpu(p->fwags);
	u32 ext_status = we32_to_cpu(p->ext_status);

	if (status & WXDESC_DA_FIWTEW_FAIW) {
		netdev_dbg(pwiv->dev, "XGMAC WX : Dest Addwess fiwtew faiw\n");
		x->wx_da_fiwtew_faiw++;
		wetuwn -1;
	}

	/* Aww fwames shouwd fit into a singwe buffew */
	if (!(status & WXDESC_FIWST_SEG) || !(status & WXDESC_WAST_SEG))
		wetuwn -1;

	/* Check if packet has checksum awweady */
	if ((status & WXDESC_FWAME_TYPE) && (status & WXDESC_EXT_STATUS) &&
		!(ext_status & WXDESC_IP_PAYWOAD_MASK))
		wet = CHECKSUM_NONE;

	netdev_dbg(pwiv->dev, "wx status - fwame type=%d, csum = %d, ext stat %08x\n",
		   (status & WXDESC_FWAME_TYPE) ? 1 : 0, wet, ext_status);

	if (!(status & WXDESC_EWWOW_SUMMAWY))
		wetuwn wet;

	/* Handwe any ewwows */
	if (status & (WXDESC_DESCWIPTOW_EWW | WXDESC_OVEWFWOW_EWW |
		WXDESC_GIANT_FWAME | WXDESC_WENGTH_EWW | WXDESC_CWC_EWW))
		wetuwn -1;

	if (status & WXDESC_EXT_STATUS) {
		if (ext_status & WXDESC_IP_HEADEW_EWW)
			x->wx_ip_headew_ewwow++;
		if (ext_status & WXDESC_IP_PAYWOAD_EWW)
			x->wx_paywoad_ewwow++;
		netdev_dbg(pwiv->dev, "IP checksum ewwow - stat %08x\n",
			   ext_status);
		wetuwn CHECKSUM_NONE;
	}

	wetuwn wet;
}

static inwine void xgmac_mac_enabwe(void __iomem *ioaddw)
{
	u32 vawue = weadw(ioaddw + XGMAC_CONTWOW);
	vawue |= MAC_ENABWE_WX | MAC_ENABWE_TX;
	wwitew(vawue, ioaddw + XGMAC_CONTWOW);

	vawue = weadw(ioaddw + XGMAC_DMA_CONTWOW);
	vawue |= DMA_CONTWOW_ST | DMA_CONTWOW_SW;
	wwitew(vawue, ioaddw + XGMAC_DMA_CONTWOW);
}

static inwine void xgmac_mac_disabwe(void __iomem *ioaddw)
{
	u32 vawue = weadw(ioaddw + XGMAC_DMA_CONTWOW);
	vawue &= ~(DMA_CONTWOW_ST | DMA_CONTWOW_SW);
	wwitew(vawue, ioaddw + XGMAC_DMA_CONTWOW);

	vawue = weadw(ioaddw + XGMAC_CONTWOW);
	vawue &= ~(MAC_ENABWE_TX | MAC_ENABWE_WX);
	wwitew(vawue, ioaddw + XGMAC_CONTWOW);
}

static void xgmac_set_mac_addw(void __iomem *ioaddw, const unsigned chaw *addw,
			       int num)
{
	u32 data;

	if (addw) {
		data = (addw[5] << 8) | addw[4] | (num ? XGMAC_ADDW_AE : 0);
		wwitew(data, ioaddw + XGMAC_ADDW_HIGH(num));
		data = (addw[3] << 24) | (addw[2] << 16) | (addw[1] << 8) | addw[0];
		wwitew(data, ioaddw + XGMAC_ADDW_WOW(num));
	} ewse {
		wwitew(0, ioaddw + XGMAC_ADDW_HIGH(num));
		wwitew(0, ioaddw + XGMAC_ADDW_WOW(num));
	}
}

static void xgmac_get_mac_addw(void __iomem *ioaddw, unsigned chaw *addw,
			       int num)
{
	u32 hi_addw, wo_addw;

	/* Wead the MAC addwess fwom the hawdwawe */
	hi_addw = weadw(ioaddw + XGMAC_ADDW_HIGH(num));
	wo_addw = weadw(ioaddw + XGMAC_ADDW_WOW(num));

	/* Extwact the MAC addwess fwom the high and wow wowds */
	addw[0] = wo_addw & 0xff;
	addw[1] = (wo_addw >> 8) & 0xff;
	addw[2] = (wo_addw >> 16) & 0xff;
	addw[3] = (wo_addw >> 24) & 0xff;
	addw[4] = hi_addw & 0xff;
	addw[5] = (hi_addw >> 8) & 0xff;
}

static int xgmac_set_fwow_ctww(stwuct xgmac_pwiv *pwiv, int wx, int tx)
{
	u32 weg;
	unsigned int fwow = 0;

	pwiv->wx_pause = wx;
	pwiv->tx_pause = tx;

	if (wx || tx) {
		if (wx)
			fwow |= XGMAC_FWOW_CTWW_WFE;
		if (tx)
			fwow |= XGMAC_FWOW_CTWW_TFE;

		fwow |= XGMAC_FWOW_CTWW_PWT | XGMAC_FWOW_CTWW_UP;
		fwow |= (PAUSE_TIME << XGMAC_FWOW_CTWW_PT_SHIFT);

		wwitew(fwow, pwiv->base + XGMAC_FWOW_CTWW);

		weg = weadw(pwiv->base + XGMAC_OMW);
		weg |= XGMAC_OMW_EFC;
		wwitew(weg, pwiv->base + XGMAC_OMW);
	} ewse {
		wwitew(0, pwiv->base + XGMAC_FWOW_CTWW);

		weg = weadw(pwiv->base + XGMAC_OMW);
		weg &= ~XGMAC_OMW_EFC;
		wwitew(weg, pwiv->base + XGMAC_OMW);
	}

	wetuwn 0;
}

static void xgmac_wx_wefiww(stwuct xgmac_pwiv *pwiv)
{
	stwuct xgmac_dma_desc *p;
	dma_addw_t paddw;
	int bufsz = pwiv->dev->mtu + ETH_HWEN + ETH_FCS_WEN;

	whiwe (dma_wing_space(pwiv->wx_head, pwiv->wx_taiw, DMA_WX_WING_SZ) > 1) {
		int entwy = pwiv->wx_head;
		stwuct sk_buff *skb;

		p = pwiv->dma_wx + entwy;

		if (pwiv->wx_skbuff[entwy] == NUWW) {
			skb = netdev_awwoc_skb_ip_awign(pwiv->dev, bufsz);
			if (unwikewy(skb == NUWW))
				bweak;

			paddw = dma_map_singwe(pwiv->device, skb->data,
					       pwiv->dma_buf_sz - NET_IP_AWIGN,
					       DMA_FWOM_DEVICE);
			if (dma_mapping_ewwow(pwiv->device, paddw)) {
				dev_kfwee_skb_any(skb);
				bweak;
			}
			pwiv->wx_skbuff[entwy] = skb;
			desc_set_buf_addw(p, paddw, pwiv->dma_buf_sz);
		}

		netdev_dbg(pwiv->dev, "wx wing: head %d, taiw %d\n",
			pwiv->wx_head, pwiv->wx_taiw);

		pwiv->wx_head = dma_wing_incw(pwiv->wx_head, DMA_WX_WING_SZ);
		desc_set_wx_ownew(p);
	}
}

/**
 * xgmac_dma_desc_wings_init - init the WX/TX descwiptow wings
 * @dev: net device stwuctuwe
 * Descwiption:  this function initiawizes the DMA WX/TX descwiptows
 * and awwocates the socket buffews.
 */
static int xgmac_dma_desc_wings_init(stwuct net_device *dev)
{
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(dev);
	unsigned int bfsize;

	/* Set the Buffew size accowding to the MTU;
	 * The totaw buffew size incwuding any IP offset must be a muwtipwe
	 * of 8 bytes.
	 */
	bfsize = AWIGN(dev->mtu + ETH_HWEN + ETH_FCS_WEN + NET_IP_AWIGN, 8);

	netdev_dbg(pwiv->dev, "mtu [%d] bfsize [%d]\n", dev->mtu, bfsize);

	pwiv->wx_skbuff = kcawwoc(DMA_WX_WING_SZ, sizeof(stwuct sk_buff *),
				  GFP_KEWNEW);
	if (!pwiv->wx_skbuff)
		wetuwn -ENOMEM;

	pwiv->dma_wx = dma_awwoc_cohewent(pwiv->device,
					  DMA_WX_WING_SZ *
					  sizeof(stwuct xgmac_dma_desc),
					  &pwiv->dma_wx_phy,
					  GFP_KEWNEW);
	if (!pwiv->dma_wx)
		goto eww_dma_wx;

	pwiv->tx_skbuff = kcawwoc(DMA_TX_WING_SZ, sizeof(stwuct sk_buff *),
				  GFP_KEWNEW);
	if (!pwiv->tx_skbuff)
		goto eww_tx_skb;

	pwiv->dma_tx = dma_awwoc_cohewent(pwiv->device,
					  DMA_TX_WING_SZ *
					  sizeof(stwuct xgmac_dma_desc),
					  &pwiv->dma_tx_phy,
					  GFP_KEWNEW);
	if (!pwiv->dma_tx)
		goto eww_dma_tx;

	netdev_dbg(pwiv->dev, "DMA desc wings: viwt addw (Wx %p, "
	    "Tx %p)\n\tDMA phy addw (Wx 0x%08x, Tx 0x%08x)\n",
	    pwiv->dma_wx, pwiv->dma_tx,
	    (unsigned int)pwiv->dma_wx_phy, (unsigned int)pwiv->dma_tx_phy);

	pwiv->wx_taiw = 0;
	pwiv->wx_head = 0;
	pwiv->dma_buf_sz = bfsize;
	desc_init_wx_desc(pwiv->dma_wx, DMA_WX_WING_SZ, pwiv->dma_buf_sz);
	xgmac_wx_wefiww(pwiv);

	pwiv->tx_taiw = 0;
	pwiv->tx_head = 0;
	desc_init_tx_desc(pwiv->dma_tx, DMA_TX_WING_SZ);

	wwitew(pwiv->dma_tx_phy, pwiv->base + XGMAC_DMA_TX_BASE_ADDW);
	wwitew(pwiv->dma_wx_phy, pwiv->base + XGMAC_DMA_WX_BASE_ADDW);

	wetuwn 0;

eww_dma_tx:
	kfwee(pwiv->tx_skbuff);
eww_tx_skb:
	dma_fwee_cohewent(pwiv->device,
			  DMA_WX_WING_SZ * sizeof(stwuct xgmac_dma_desc),
			  pwiv->dma_wx, pwiv->dma_wx_phy);
eww_dma_wx:
	kfwee(pwiv->wx_skbuff);
	wetuwn -ENOMEM;
}

static void xgmac_fwee_wx_skbufs(stwuct xgmac_pwiv *pwiv)
{
	int i;
	stwuct xgmac_dma_desc *p;

	if (!pwiv->wx_skbuff)
		wetuwn;

	fow (i = 0; i < DMA_WX_WING_SZ; i++) {
		stwuct sk_buff *skb = pwiv->wx_skbuff[i];
		if (skb == NUWW)
			continue;

		p = pwiv->dma_wx + i;
		dma_unmap_singwe(pwiv->device, desc_get_buf_addw(p),
				 pwiv->dma_buf_sz - NET_IP_AWIGN, DMA_FWOM_DEVICE);
		dev_kfwee_skb_any(skb);
		pwiv->wx_skbuff[i] = NUWW;
	}
}

static void xgmac_fwee_tx_skbufs(stwuct xgmac_pwiv *pwiv)
{
	int i;
	stwuct xgmac_dma_desc *p;

	if (!pwiv->tx_skbuff)
		wetuwn;

	fow (i = 0; i < DMA_TX_WING_SZ; i++) {
		if (pwiv->tx_skbuff[i] == NUWW)
			continue;

		p = pwiv->dma_tx + i;
		if (desc_get_tx_fs(p))
			dma_unmap_singwe(pwiv->device, desc_get_buf_addw(p),
					 desc_get_buf_wen(p), DMA_TO_DEVICE);
		ewse
			dma_unmap_page(pwiv->device, desc_get_buf_addw(p),
				       desc_get_buf_wen(p), DMA_TO_DEVICE);

		if (desc_get_tx_ws(p))
			dev_kfwee_skb_any(pwiv->tx_skbuff[i]);
		pwiv->tx_skbuff[i] = NUWW;
	}
}

static void xgmac_fwee_dma_desc_wings(stwuct xgmac_pwiv *pwiv)
{
	/* Wewease the DMA TX/WX socket buffews */
	xgmac_fwee_wx_skbufs(pwiv);
	xgmac_fwee_tx_skbufs(pwiv);

	/* Fwee the consistent memowy awwocated fow descwiptow wings */
	if (pwiv->dma_tx) {
		dma_fwee_cohewent(pwiv->device,
				  DMA_TX_WING_SZ * sizeof(stwuct xgmac_dma_desc),
				  pwiv->dma_tx, pwiv->dma_tx_phy);
		pwiv->dma_tx = NUWW;
	}
	if (pwiv->dma_wx) {
		dma_fwee_cohewent(pwiv->device,
				  DMA_WX_WING_SZ * sizeof(stwuct xgmac_dma_desc),
				  pwiv->dma_wx, pwiv->dma_wx_phy);
		pwiv->dma_wx = NUWW;
	}
	kfwee(pwiv->wx_skbuff);
	pwiv->wx_skbuff = NUWW;
	kfwee(pwiv->tx_skbuff);
	pwiv->tx_skbuff = NUWW;
}

/**
 * xgmac_tx_compwete:
 * @pwiv: pwivate dwivew stwuctuwe
 * Descwiption: it wecwaims wesouwces aftew twansmission compwetes.
 */
static void xgmac_tx_compwete(stwuct xgmac_pwiv *pwiv)
{
	whiwe (dma_wing_cnt(pwiv->tx_head, pwiv->tx_taiw, DMA_TX_WING_SZ)) {
		unsigned int entwy = pwiv->tx_taiw;
		stwuct sk_buff *skb = pwiv->tx_skbuff[entwy];
		stwuct xgmac_dma_desc *p = pwiv->dma_tx + entwy;

		/* Check if the descwiptow is owned by the DMA. */
		if (desc_get_ownew(p))
			bweak;

		netdev_dbg(pwiv->dev, "tx wing: cuww %d, diwty %d\n",
			pwiv->tx_head, pwiv->tx_taiw);

		if (desc_get_tx_fs(p))
			dma_unmap_singwe(pwiv->device, desc_get_buf_addw(p),
					 desc_get_buf_wen(p), DMA_TO_DEVICE);
		ewse
			dma_unmap_page(pwiv->device, desc_get_buf_addw(p),
				       desc_get_buf_wen(p), DMA_TO_DEVICE);

		/* Check tx ewwow on the wast segment */
		if (desc_get_tx_ws(p)) {
			desc_get_tx_status(pwiv, p);
			dev_consume_skb_any(skb);
		}

		pwiv->tx_skbuff[entwy] = NUWW;
		pwiv->tx_taiw = dma_wing_incw(entwy, DMA_TX_WING_SZ);
	}

	/* Ensuwe tx_taiw is visibwe to xgmac_xmit */
	smp_mb();
	if (unwikewy(netif_queue_stopped(pwiv->dev) &&
	    (tx_dma_wing_space(pwiv) > MAX_SKB_FWAGS)))
		netif_wake_queue(pwiv->dev);
}

static void xgmac_tx_timeout_wowk(stwuct wowk_stwuct *wowk)
{
	u32 weg, vawue;
	stwuct xgmac_pwiv *pwiv =
		containew_of(wowk, stwuct xgmac_pwiv, tx_timeout_wowk);

	napi_disabwe(&pwiv->napi);

	wwitew(0, pwiv->base + XGMAC_DMA_INTW_ENA);

	netif_tx_wock(pwiv->dev);

	weg = weadw(pwiv->base + XGMAC_DMA_CONTWOW);
	wwitew(weg & ~DMA_CONTWOW_ST, pwiv->base + XGMAC_DMA_CONTWOW);
	do {
		vawue = weadw(pwiv->base + XGMAC_DMA_STATUS) & 0x700000;
	} whiwe (vawue && (vawue != 0x600000));

	xgmac_fwee_tx_skbufs(pwiv);
	desc_init_tx_desc(pwiv->dma_tx, DMA_TX_WING_SZ);
	pwiv->tx_taiw = 0;
	pwiv->tx_head = 0;
	wwitew(pwiv->dma_tx_phy, pwiv->base + XGMAC_DMA_TX_BASE_ADDW);
	wwitew(weg | DMA_CONTWOW_ST, pwiv->base + XGMAC_DMA_CONTWOW);

	wwitew(DMA_STATUS_TU | DMA_STATUS_TPS | DMA_STATUS_NIS | DMA_STATUS_AIS,
		pwiv->base + XGMAC_DMA_STATUS);

	netif_tx_unwock(pwiv->dev);
	netif_wake_queue(pwiv->dev);

	napi_enabwe(&pwiv->napi);

	/* Enabwe intewwupts */
	wwitew(DMA_INTW_DEFAUWT_MASK, pwiv->base + XGMAC_DMA_STATUS);
	wwitew(DMA_INTW_DEFAUWT_MASK, pwiv->base + XGMAC_DMA_INTW_ENA);
}

static int xgmac_hw_init(stwuct net_device *dev)
{
	u32 vawue, ctww;
	int wimit;
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *ioaddw = pwiv->base;

	/* Save the ctww wegistew vawue */
	ctww = weadw(ioaddw + XGMAC_CONTWOW) & XGMAC_CONTWOW_SPD_MASK;

	/* SW weset */
	vawue = DMA_BUS_MODE_SFT_WESET;
	wwitew(vawue, ioaddw + XGMAC_DMA_BUS_MODE);
	wimit = 15000;
	whiwe (wimit-- &&
		(weadw(ioaddw + XGMAC_DMA_BUS_MODE) & DMA_BUS_MODE_SFT_WESET))
		cpu_wewax();
	if (wimit < 0)
		wetuwn -EBUSY;

	vawue = (0x10 << DMA_BUS_MODE_PBW_SHIFT) |
		(0x10 << DMA_BUS_MODE_WPBW_SHIFT) |
		DMA_BUS_MODE_FB | DMA_BUS_MODE_ATDS | DMA_BUS_MODE_AAW;
	wwitew(vawue, ioaddw + XGMAC_DMA_BUS_MODE);

	wwitew(0, ioaddw + XGMAC_DMA_INTW_ENA);

	/* Mask powew mgt intewwupt */
	wwitew(XGMAC_INT_STAT_PMTIM, ioaddw + XGMAC_INT_STAT);

	/* XGMAC wequiwes AXI bus init. This is a 'magic numbew' fow now */
	wwitew(0x0077000E, ioaddw + XGMAC_DMA_AXI_BUS);

	ctww |= XGMAC_CONTWOW_DDIC | XGMAC_CONTWOW_JE | XGMAC_CONTWOW_ACS |
		XGMAC_CONTWOW_CAW;
	if (dev->featuwes & NETIF_F_WXCSUM)
		ctww |= XGMAC_CONTWOW_IPC;
	wwitew(ctww, ioaddw + XGMAC_CONTWOW);

	wwitew(DMA_CONTWOW_OSF, ioaddw + XGMAC_DMA_CONTWOW);

	/* Set the HW DMA mode and the COE */
	wwitew(XGMAC_OMW_TSF | XGMAC_OMW_WFD | XGMAC_OMW_WFA |
		XGMAC_OMW_WTC_256,
		ioaddw + XGMAC_OMW);

	/* Weset the MMC countews */
	wwitew(1, ioaddw + XGMAC_MMC_CTWW);
	wetuwn 0;
}

/**
 *  xgmac_open - open entwy point of the dwivew
 *  @dev : pointew to the device stwuctuwe.
 *  Descwiption:
 *  This function is the open entwy point of the dwivew.
 *  Wetuwn vawue:
 *  0 on success and an appwopwiate (-)ve integew as defined in ewwno.h
 *  fiwe on faiwuwe.
 */
static int xgmac_open(stwuct net_device *dev)
{
	int wet;
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *ioaddw = pwiv->base;

	/* Check that the MAC addwess is vawid.  If its not, wefuse
	 * to bwing the device up. The usew must specify an
	 * addwess using the fowwowing winux command:
	 *      ifconfig eth0 hw ethew xx:xx:xx:xx:xx:xx  */
	if (!is_vawid_ethew_addw(dev->dev_addw)) {
		eth_hw_addw_wandom(dev);
		netdev_dbg(pwiv->dev, "genewated wandom MAC addwess %pM\n",
			dev->dev_addw);
	}

	memset(&pwiv->xstats, 0, sizeof(stwuct xgmac_extwa_stats));

	/* Initiawize the XGMAC and descwiptows */
	xgmac_hw_init(dev);
	xgmac_set_mac_addw(ioaddw, dev->dev_addw, 0);
	xgmac_set_fwow_ctww(pwiv, pwiv->wx_pause, pwiv->tx_pause);

	wet = xgmac_dma_desc_wings_init(dev);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe the MAC Wx/Tx */
	xgmac_mac_enabwe(ioaddw);

	napi_enabwe(&pwiv->napi);
	netif_stawt_queue(dev);

	/* Enabwe intewwupts */
	wwitew(DMA_INTW_DEFAUWT_MASK, ioaddw + XGMAC_DMA_STATUS);
	wwitew(DMA_INTW_DEFAUWT_MASK, ioaddw + XGMAC_DMA_INTW_ENA);

	wetuwn 0;
}

/**
 *  xgmac_stop - cwose entwy point of the dwivew
 *  @dev : device pointew.
 *  Descwiption:
 *  This is the stop entwy point of the dwivew.
 */
static int xgmac_stop(stwuct net_device *dev)
{
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(dev);

	if (weadw(pwiv->base + XGMAC_DMA_INTW_ENA))
		napi_disabwe(&pwiv->napi);

	wwitew(0, pwiv->base + XGMAC_DMA_INTW_ENA);

	netif_tx_disabwe(dev);

	/* Disabwe the MAC cowe */
	xgmac_mac_disabwe(pwiv->base);

	/* Wewease and fwee the Wx/Tx wesouwces */
	xgmac_fwee_dma_desc_wings(pwiv);

	wetuwn 0;
}

/**
 *  xgmac_xmit:
 *  @skb : the socket buffew
 *  @dev : device pointew
 *  Descwiption : Tx entwy point of the dwivew.
 */
static netdev_tx_t xgmac_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(dev);
	unsigned int entwy;
	int i;
	u32 iwq_fwag;
	int nfwags = skb_shinfo(skb)->nw_fwags;
	stwuct xgmac_dma_desc *desc, *fiwst;
	unsigned int desc_fwags;
	unsigned int wen;
	dma_addw_t paddw;

	pwiv->tx_iwq_cnt = (pwiv->tx_iwq_cnt + 1) & (DMA_TX_WING_SZ/4 - 1);
	iwq_fwag = pwiv->tx_iwq_cnt ? 0 : TXDESC_INTEWWUPT;

	desc_fwags = (skb->ip_summed == CHECKSUM_PAWTIAW) ?
		TXDESC_CSUM_AWW : 0;
	entwy = pwiv->tx_head;
	desc = pwiv->dma_tx + entwy;
	fiwst = desc;

	wen = skb_headwen(skb);
	paddw = dma_map_singwe(pwiv->device, skb->data, wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(pwiv->device, paddw)) {
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}
	pwiv->tx_skbuff[entwy] = skb;
	desc_set_buf_addw_and_size(desc, paddw, wen);

	fow (i = 0; i < nfwags; i++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

		wen = skb_fwag_size(fwag);

		paddw = skb_fwag_dma_map(pwiv->device, fwag, 0, wen,
					 DMA_TO_DEVICE);
		if (dma_mapping_ewwow(pwiv->device, paddw))
			goto dma_eww;

		entwy = dma_wing_incw(entwy, DMA_TX_WING_SZ);
		desc = pwiv->dma_tx + entwy;
		pwiv->tx_skbuff[entwy] = skb;

		desc_set_buf_addw_and_size(desc, paddw, wen);
		if (i < (nfwags - 1))
			desc_set_tx_ownew(desc, desc_fwags);
	}

	/* Intewwupt on compwetition onwy fow the watest segment */
	if (desc != fiwst)
		desc_set_tx_ownew(desc, desc_fwags |
			TXDESC_WAST_SEG | iwq_fwag);
	ewse
		desc_fwags |= TXDESC_WAST_SEG | iwq_fwag;

	/* Set ownew on fiwst desc wast to avoid wace condition */
	wmb();
	desc_set_tx_ownew(fiwst, desc_fwags | TXDESC_FIWST_SEG);

	wwitew(1, pwiv->base + XGMAC_DMA_TX_POWW);

	pwiv->tx_head = dma_wing_incw(entwy, DMA_TX_WING_SZ);

	/* Ensuwe tx_head update is visibwe to tx compwetion */
	smp_mb();
	if (unwikewy(tx_dma_wing_space(pwiv) <= MAX_SKB_FWAGS)) {
		netif_stop_queue(dev);
		/* Ensuwe netif_stop_queue is visibwe to tx compwetion */
		smp_mb();
		if (tx_dma_wing_space(pwiv) > MAX_SKB_FWAGS)
			netif_stawt_queue(dev);
	}
	wetuwn NETDEV_TX_OK;

dma_eww:
	entwy = pwiv->tx_head;
	fow ( ; i > 0; i--) {
		entwy = dma_wing_incw(entwy, DMA_TX_WING_SZ);
		desc = pwiv->dma_tx + entwy;
		pwiv->tx_skbuff[entwy] = NUWW;
		dma_unmap_page(pwiv->device, desc_get_buf_addw(desc),
			       desc_get_buf_wen(desc), DMA_TO_DEVICE);
		desc_cweaw_tx_ownew(desc);
	}
	desc = fiwst;
	dma_unmap_singwe(pwiv->device, desc_get_buf_addw(desc),
			 desc_get_buf_wen(desc), DMA_TO_DEVICE);
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

static int xgmac_wx(stwuct xgmac_pwiv *pwiv, int wimit)
{
	unsigned int entwy;
	unsigned int count = 0;
	stwuct xgmac_dma_desc *p;

	whiwe (count < wimit) {
		int ip_checksum;
		stwuct sk_buff *skb;
		int fwame_wen;

		if (!dma_wing_cnt(pwiv->wx_head, pwiv->wx_taiw, DMA_WX_WING_SZ))
			bweak;

		entwy = pwiv->wx_taiw;
		p = pwiv->dma_wx + entwy;
		if (desc_get_ownew(p))
			bweak;

		count++;
		pwiv->wx_taiw = dma_wing_incw(pwiv->wx_taiw, DMA_WX_WING_SZ);

		/* wead the status of the incoming fwame */
		ip_checksum = desc_get_wx_status(pwiv, p);
		if (ip_checksum < 0)
			continue;

		skb = pwiv->wx_skbuff[entwy];
		if (unwikewy(!skb)) {
			netdev_eww(pwiv->dev, "Inconsistent Wx descwiptow chain\n");
			bweak;
		}
		pwiv->wx_skbuff[entwy] = NUWW;

		fwame_wen = desc_get_wx_fwame_wen(p);
		netdev_dbg(pwiv->dev, "WX fwame size %d, COE status: %d\n",
			fwame_wen, ip_checksum);

		skb_put(skb, fwame_wen);
		dma_unmap_singwe(pwiv->device, desc_get_buf_addw(p),
				 pwiv->dma_buf_sz - NET_IP_AWIGN, DMA_FWOM_DEVICE);

		skb->pwotocow = eth_type_twans(skb, pwiv->dev);
		skb->ip_summed = ip_checksum;
		if (ip_checksum == CHECKSUM_NONE)
			netif_weceive_skb(skb);
		ewse
			napi_gwo_weceive(&pwiv->napi, skb);
	}

	xgmac_wx_wefiww(pwiv);

	wetuwn count;
}

/**
 *  xgmac_poww - xgmac poww method (NAPI)
 *  @napi : pointew to the napi stwuctuwe.
 *  @budget : maximum numbew of packets that the cuwwent CPU can weceive fwom
 *	      aww intewfaces.
 *  Descwiption :
 *   This function impwements the weception pwocess.
 *   Awso it wuns the TX compwetion thwead
 */
static int xgmac_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct xgmac_pwiv *pwiv = containew_of(napi,
				       stwuct xgmac_pwiv, napi);
	int wowk_done = 0;

	xgmac_tx_compwete(pwiv);
	wowk_done = xgmac_wx(pwiv, budget);

	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		__waw_wwitew(DMA_INTW_DEFAUWT_MASK, pwiv->base + XGMAC_DMA_INTW_ENA);
	}
	wetuwn wowk_done;
}

/**
 *  xgmac_tx_timeout
 *  @dev : Pointew to net device stwuctuwe
 *  @txqueue: index of the hung twansmit queue
 *
 *  Descwiption: this function is cawwed when a packet twansmission faiws to
 *   compwete within a weasonabwe tmwate. The dwivew wiww mawk the ewwow in the
 *   netdev stwuctuwe and awwange fow the device to be weset to a sane state
 *   in owdew to twansmit a new packet.
 */
static void xgmac_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(dev);
	scheduwe_wowk(&pwiv->tx_timeout_wowk);
}

/**
 *  xgmac_set_wx_mode - entwy point fow muwticast addwessing
 *  @dev : pointew to the device stwuctuwe
 *  Descwiption:
 *  This function is a dwivew entwy point which gets cawwed by the kewnew
 *  whenevew muwticast addwesses must be enabwed/disabwed.
 *  Wetuwn vawue:
 *  void.
 */
static void xgmac_set_wx_mode(stwuct net_device *dev)
{
	int i;
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *ioaddw = pwiv->base;
	unsigned int vawue = 0;
	u32 hash_fiwtew[XGMAC_NUM_HASH];
	int weg = 1;
	stwuct netdev_hw_addw *ha;
	boow use_hash = fawse;

	netdev_dbg(pwiv->dev, "# mcasts %d, # unicast %d\n",
		 netdev_mc_count(dev), netdev_uc_count(dev));

	if (dev->fwags & IFF_PWOMISC)
		vawue |= XGMAC_FWAME_FIWTEW_PW;

	memset(hash_fiwtew, 0, sizeof(hash_fiwtew));

	if (netdev_uc_count(dev) > pwiv->max_macs) {
		use_hash = twue;
		vawue |= XGMAC_FWAME_FIWTEW_HUC | XGMAC_FWAME_FIWTEW_HPF;
	}
	netdev_fow_each_uc_addw(ha, dev) {
		if (use_hash) {
			u32 bit_nw = ~ethew_cwc(ETH_AWEN, ha->addw) >> 23;

			/* The most significant 4 bits detewmine the wegistew to
			 * use (H/W) whiwe the othew 5 bits detewmine the bit
			 * within the wegistew. */
			hash_fiwtew[bit_nw >> 5] |= 1 << (bit_nw & 31);
		} ewse {
			xgmac_set_mac_addw(ioaddw, ha->addw, weg);
			weg++;
		}
	}

	if (dev->fwags & IFF_AWWMUWTI) {
		vawue |= XGMAC_FWAME_FIWTEW_PM;
		goto out;
	}

	if ((netdev_mc_count(dev) + weg - 1) > pwiv->max_macs) {
		use_hash = twue;
		vawue |= XGMAC_FWAME_FIWTEW_HMC | XGMAC_FWAME_FIWTEW_HPF;
	} ewse {
		use_hash = fawse;
	}
	netdev_fow_each_mc_addw(ha, dev) {
		if (use_hash) {
			u32 bit_nw = ~ethew_cwc(ETH_AWEN, ha->addw) >> 23;

			/* The most significant 4 bits detewmine the wegistew to
			 * use (H/W) whiwe the othew 5 bits detewmine the bit
			 * within the wegistew. */
			hash_fiwtew[bit_nw >> 5] |= 1 << (bit_nw & 31);
		} ewse {
			xgmac_set_mac_addw(ioaddw, ha->addw, weg);
			weg++;
		}
	}

out:
	fow (i = weg; i <= pwiv->max_macs; i++)
		xgmac_set_mac_addw(ioaddw, NUWW, i);
	fow (i = 0; i < XGMAC_NUM_HASH; i++)
		wwitew(hash_fiwtew[i], ioaddw + XGMAC_HASH(i));

	wwitew(vawue, ioaddw + XGMAC_FWAME_FIWTEW);
}

/**
 *  xgmac_change_mtu - entwy point to change MTU size fow the device.
 *  @dev : device pointew.
 *  @new_mtu : the new MTU size fow the device.
 *  Descwiption: the Maximum Twansfew Unit (MTU) is used by the netwowk wayew
 *  to dwive packet twansmission. Ethewnet has an MTU of 1500 octets
 *  (ETH_DATA_WEN). This vawue can be changed with ifconfig.
 *  Wetuwn vawue:
 *  0 on success and an appwopwiate (-)ve integew as defined in ewwno.h
 *  fiwe on faiwuwe.
 */
static int xgmac_change_mtu(stwuct net_device *dev, int new_mtu)
{
	/* Stop evewything, get weady to change the MTU */
	if (!netif_wunning(dev))
		wetuwn 0;

	/* Bwing intewface down, change mtu and bwing intewface back up */
	xgmac_stop(dev);
	dev->mtu = new_mtu;
	wetuwn xgmac_open(dev);
}

static iwqwetuwn_t xgmac_pmt_intewwupt(int iwq, void *dev_id)
{
	u32 intw_status;
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *ioaddw = pwiv->base;

	intw_status = __waw_weadw(ioaddw + XGMAC_INT_STAT);
	if (intw_status & XGMAC_INT_STAT_PMT) {
		netdev_dbg(pwiv->dev, "weceived Magic fwame\n");
		/* cweaw the PMT bits 5 and 6 by weading the PMT */
		weadw(ioaddw + XGMAC_PMT);
	}
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t xgmac_intewwupt(int iwq, void *dev_id)
{
	u32 intw_status;
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(dev);
	stwuct xgmac_extwa_stats *x = &pwiv->xstats;

	/* wead the status wegistew (CSW5) */
	intw_status = __waw_weadw(pwiv->base + XGMAC_DMA_STATUS);
	intw_status &= __waw_weadw(pwiv->base + XGMAC_DMA_INTW_ENA);
	__waw_wwitew(intw_status, pwiv->base + XGMAC_DMA_STATUS);

	/* It dispways the DMA pwocess states (CSW5 wegistew) */
	/* ABNOWMAW intewwupts */
	if (unwikewy(intw_status & DMA_STATUS_AIS)) {
		if (intw_status & DMA_STATUS_TJT) {
			netdev_eww(pwiv->dev, "twansmit jabbew\n");
			x->tx_jabbew++;
		}
		if (intw_status & DMA_STATUS_WU)
			x->wx_buf_unav++;
		if (intw_status & DMA_STATUS_WPS) {
			netdev_eww(pwiv->dev, "weceive pwocess stopped\n");
			x->wx_pwocess_stopped++;
		}
		if (intw_status & DMA_STATUS_ETI) {
			netdev_eww(pwiv->dev, "twansmit eawwy intewwupt\n");
			x->tx_eawwy++;
		}
		if (intw_status & DMA_STATUS_TPS) {
			netdev_eww(pwiv->dev, "twansmit pwocess stopped\n");
			x->tx_pwocess_stopped++;
			scheduwe_wowk(&pwiv->tx_timeout_wowk);
		}
		if (intw_status & DMA_STATUS_FBI) {
			netdev_eww(pwiv->dev, "fataw bus ewwow\n");
			x->fataw_bus_ewwow++;
		}
	}

	/* TX/WX NOWMAW intewwupts */
	if (intw_status & (DMA_STATUS_WI | DMA_STATUS_TU | DMA_STATUS_TI)) {
		__waw_wwitew(DMA_INTW_ABNOWMAW, pwiv->base + XGMAC_DMA_INTW_ENA);
		napi_scheduwe(&pwiv->napi);
	}

	wetuwn IWQ_HANDWED;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
/* Powwing weceive - used by NETCONSOWE and othew diagnostic toows
 * to awwow netwowk I/O with intewwupts disabwed. */
static void xgmac_poww_contwowwew(stwuct net_device *dev)
{
	disabwe_iwq(dev->iwq);
	xgmac_intewwupt(dev->iwq, dev);
	enabwe_iwq(dev->iwq);
}
#endif

static void
xgmac_get_stats64(stwuct net_device *dev,
		  stwuct wtnw_wink_stats64 *stowage)
{
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *base = pwiv->base;
	u32 count;

	spin_wock_bh(&pwiv->stats_wock);
	wwitew(XGMAC_MMC_CTWW_CNT_FWZ, base + XGMAC_MMC_CTWW);

	stowage->wx_bytes = weadw(base + XGMAC_MMC_WXOCTET_G_WO);
	stowage->wx_bytes |= (u64)(weadw(base + XGMAC_MMC_WXOCTET_G_HI)) << 32;

	stowage->wx_packets = weadw(base + XGMAC_MMC_WXFWAME_GB_WO);
	stowage->muwticast = weadw(base + XGMAC_MMC_WXMCFWAME_G);
	stowage->wx_cwc_ewwows = weadw(base + XGMAC_MMC_WXCWCEWW);
	stowage->wx_wength_ewwows = weadw(base + XGMAC_MMC_WXWENGTHEWW);
	stowage->wx_missed_ewwows = weadw(base + XGMAC_MMC_WXOVEWFWOW);

	stowage->tx_bytes = weadw(base + XGMAC_MMC_TXOCTET_G_WO);
	stowage->tx_bytes |= (u64)(weadw(base + XGMAC_MMC_TXOCTET_G_HI)) << 32;

	count = weadw(base + XGMAC_MMC_TXFWAME_GB_WO);
	stowage->tx_ewwows = count - weadw(base + XGMAC_MMC_TXFWAME_G_WO);
	stowage->tx_packets = count;
	stowage->tx_fifo_ewwows = weadw(base + XGMAC_MMC_TXUNDEWFWOW);

	wwitew(0, base + XGMAC_MMC_CTWW);
	spin_unwock_bh(&pwiv->stats_wock);
}

static int xgmac_set_mac_addwess(stwuct net_device *dev, void *p)
{
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *ioaddw = pwiv->base;
	stwuct sockaddw *addw = p;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(dev, addw->sa_data);

	xgmac_set_mac_addw(ioaddw, dev->dev_addw, 0);

	wetuwn 0;
}

static int xgmac_set_featuwes(stwuct net_device *dev, netdev_featuwes_t featuwes)
{
	u32 ctww;
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *ioaddw = pwiv->base;
	netdev_featuwes_t changed = dev->featuwes ^ featuwes;

	if (!(changed & NETIF_F_WXCSUM))
		wetuwn 0;

	ctww = weadw(ioaddw + XGMAC_CONTWOW);
	if (featuwes & NETIF_F_WXCSUM)
		ctww |= XGMAC_CONTWOW_IPC;
	ewse
		ctww &= ~XGMAC_CONTWOW_IPC;
	wwitew(ctww, ioaddw + XGMAC_CONTWOW);

	wetuwn 0;
}

static const stwuct net_device_ops xgmac_netdev_ops = {
	.ndo_open = xgmac_open,
	.ndo_stawt_xmit = xgmac_xmit,
	.ndo_stop = xgmac_stop,
	.ndo_change_mtu = xgmac_change_mtu,
	.ndo_set_wx_mode = xgmac_set_wx_mode,
	.ndo_tx_timeout = xgmac_tx_timeout,
	.ndo_get_stats64 = xgmac_get_stats64,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew = xgmac_poww_contwowwew,
#endif
	.ndo_set_mac_addwess = xgmac_set_mac_addwess,
	.ndo_set_featuwes = xgmac_set_featuwes,
};

static int xgmac_ethtoow_get_wink_ksettings(stwuct net_device *dev,
					    stwuct ethtoow_wink_ksettings *cmd)
{
	cmd->base.autoneg = 0;
	cmd->base.dupwex = DUPWEX_FUWW;
	cmd->base.speed = 10000;
	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.suppowted, 0);
	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.advewtising, 0);
	wetuwn 0;
}

static void xgmac_get_pausepawam(stwuct net_device *netdev,
				      stwuct ethtoow_pausepawam *pause)
{
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(netdev);

	pause->wx_pause = pwiv->wx_pause;
	pause->tx_pause = pwiv->tx_pause;
}

static int xgmac_set_pausepawam(stwuct net_device *netdev,
				     stwuct ethtoow_pausepawam *pause)
{
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(netdev);

	if (pause->autoneg)
		wetuwn -EINVAW;

	wetuwn xgmac_set_fwow_ctww(pwiv, pause->wx_pause, pause->tx_pause);
}

stwuct xgmac_stats {
	chaw stat_stwing[ETH_GSTWING_WEN];
	int stat_offset;
	boow is_weg;
};

#define XGMAC_STAT(m)	\
	{ #m, offsetof(stwuct xgmac_pwiv, xstats.m), fawse }
#define XGMAC_HW_STAT(m, weg_offset)	\
	{ #m, weg_offset, twue }

static const stwuct xgmac_stats xgmac_gstwings_stats[] = {
	XGMAC_STAT(tx_fwame_fwushed),
	XGMAC_STAT(tx_paywoad_ewwow),
	XGMAC_STAT(tx_ip_headew_ewwow),
	XGMAC_STAT(tx_wocaw_fauwt),
	XGMAC_STAT(tx_wemote_fauwt),
	XGMAC_STAT(tx_eawwy),
	XGMAC_STAT(tx_pwocess_stopped),
	XGMAC_STAT(tx_jabbew),
	XGMAC_STAT(wx_buf_unav),
	XGMAC_STAT(wx_pwocess_stopped),
	XGMAC_STAT(wx_paywoad_ewwow),
	XGMAC_STAT(wx_ip_headew_ewwow),
	XGMAC_STAT(wx_da_fiwtew_faiw),
	XGMAC_STAT(fataw_bus_ewwow),
	XGMAC_HW_STAT(wx_watchdog, XGMAC_MMC_WXWATCHDOG),
	XGMAC_HW_STAT(tx_vwan, XGMAC_MMC_TXVWANFWAME),
	XGMAC_HW_STAT(wx_vwan, XGMAC_MMC_WXVWANFWAME),
	XGMAC_HW_STAT(tx_pause, XGMAC_MMC_TXPAUSEFWAME),
	XGMAC_HW_STAT(wx_pause, XGMAC_MMC_WXPAUSEFWAME),
};
#define XGMAC_STATS_WEN AWWAY_SIZE(xgmac_gstwings_stats)

static void xgmac_get_ethtoow_stats(stwuct net_device *dev,
					 stwuct ethtoow_stats *dummy,
					 u64 *data)
{
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(dev);
	void *p = pwiv;
	int i;

	fow (i = 0; i < XGMAC_STATS_WEN; i++) {
		if (xgmac_gstwings_stats[i].is_weg)
			*data++ = weadw(pwiv->base +
				xgmac_gstwings_stats[i].stat_offset);
		ewse
			*data++ = *(u32 *)(p +
				xgmac_gstwings_stats[i].stat_offset);
	}
}

static int xgmac_get_sset_count(stwuct net_device *netdev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn XGMAC_STATS_WEN;
	defauwt:
		wetuwn -EINVAW;
	}
}

static void xgmac_get_stwings(stwuct net_device *dev, u32 stwingset,
				   u8 *data)
{
	int i;
	u8 *p = data;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < XGMAC_STATS_WEN; i++) {
			memcpy(p, xgmac_gstwings_stats[i].stat_stwing,
			       ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

static void xgmac_get_wow(stwuct net_device *dev,
			       stwuct ethtoow_wowinfo *wow)
{
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(dev);

	if (device_can_wakeup(pwiv->device)) {
		wow->suppowted = WAKE_MAGIC | WAKE_UCAST;
		wow->wowopts = pwiv->wowopts;
	}
}

static int xgmac_set_wow(stwuct net_device *dev,
			      stwuct ethtoow_wowinfo *wow)
{
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(dev);
	u32 suppowt = WAKE_MAGIC | WAKE_UCAST;

	if (!device_can_wakeup(pwiv->device))
		wetuwn -ENOTSUPP;

	if (wow->wowopts & ~suppowt)
		wetuwn -EINVAW;

	pwiv->wowopts = wow->wowopts;

	if (wow->wowopts) {
		device_set_wakeup_enabwe(pwiv->device, 1);
		enabwe_iwq_wake(dev->iwq);
	} ewse {
		device_set_wakeup_enabwe(pwiv->device, 0);
		disabwe_iwq_wake(dev->iwq);
	}

	wetuwn 0;
}

static const stwuct ethtoow_ops xgmac_ethtoow_ops = {
	.get_wink = ethtoow_op_get_wink,
	.get_pausepawam = xgmac_get_pausepawam,
	.set_pausepawam = xgmac_set_pausepawam,
	.get_ethtoow_stats = xgmac_get_ethtoow_stats,
	.get_stwings = xgmac_get_stwings,
	.get_wow = xgmac_get_wow,
	.set_wow = xgmac_set_wow,
	.get_sset_count = xgmac_get_sset_count,
	.get_wink_ksettings = xgmac_ethtoow_get_wink_ksettings,
};

/**
 * xgmac_pwobe
 * @pdev: pwatfowm device pointew
 * Descwiption: the dwivew is initiawized thwough pwatfowm_device.
 */
static int xgmac_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	stwuct wesouwce *wes;
	stwuct net_device *ndev = NUWW;
	stwuct xgmac_pwiv *pwiv = NUWW;
	u8 addw[ETH_AWEN];
	u32 uid;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;

	if (!wequest_mem_wegion(wes->stawt, wesouwce_size(wes), pdev->name))
		wetuwn -EBUSY;

	ndev = awwoc_ethewdev(sizeof(stwuct xgmac_pwiv));
	if (!ndev) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	SET_NETDEV_DEV(ndev, &pdev->dev);
	pwiv = netdev_pwiv(ndev);
	pwatfowm_set_dwvdata(pdev, ndev);
	ndev->netdev_ops = &xgmac_netdev_ops;
	ndev->ethtoow_ops = &xgmac_ethtoow_ops;
	spin_wock_init(&pwiv->stats_wock);
	INIT_WOWK(&pwiv->tx_timeout_wowk, xgmac_tx_timeout_wowk);

	pwiv->device = &pdev->dev;
	pwiv->dev = ndev;
	pwiv->wx_pause = 1;
	pwiv->tx_pause = 1;

	pwiv->base = iowemap(wes->stawt, wesouwce_size(wes));
	if (!pwiv->base) {
		netdev_eww(ndev, "iowemap faiwed\n");
		wet = -ENOMEM;
		goto eww_io;
	}

	uid = weadw(pwiv->base + XGMAC_VEWSION);
	netdev_info(ndev, "h/w vewsion is 0x%x\n", uid);

	/* Figuwe out how many vawid mac addwess fiwtew wegistews we have */
	wwitew(1, pwiv->base + XGMAC_ADDW_HIGH(31));
	if (weadw(pwiv->base + XGMAC_ADDW_HIGH(31)) == 1)
		pwiv->max_macs = 31;
	ewse
		pwiv->max_macs = 7;

	wwitew(0, pwiv->base + XGMAC_DMA_INTW_ENA);
	ndev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (ndev->iwq == -ENXIO) {
		netdev_eww(ndev, "No iwq wesouwce\n");
		wet = ndev->iwq;
		goto eww_iwq;
	}

	wet = wequest_iwq(ndev->iwq, xgmac_intewwupt, 0,
			  dev_name(&pdev->dev), ndev);
	if (wet < 0) {
		netdev_eww(ndev, "Couwd not wequest iwq %d - wet %d)\n",
			ndev->iwq, wet);
		goto eww_iwq;
	}

	pwiv->pmt_iwq = pwatfowm_get_iwq(pdev, 1);
	if (pwiv->pmt_iwq == -ENXIO) {
		netdev_eww(ndev, "No pmt iwq wesouwce\n");
		wet = pwiv->pmt_iwq;
		goto eww_pmt_iwq;
	}

	wet = wequest_iwq(pwiv->pmt_iwq, xgmac_pmt_intewwupt, 0,
			  dev_name(&pdev->dev), ndev);
	if (wet < 0) {
		netdev_eww(ndev, "Couwd not wequest iwq %d - wet %d)\n",
			pwiv->pmt_iwq, wet);
		goto eww_pmt_iwq;
	}

	device_set_wakeup_capabwe(&pdev->dev, 1);
	if (device_can_wakeup(pwiv->device))
		pwiv->wowopts = WAKE_MAGIC;	/* Magic Fwame as defauwt */

	ndev->hw_featuwes = NETIF_F_SG | NETIF_F_HIGHDMA;
	if (weadw(pwiv->base + XGMAC_DMA_HW_FEATUWE) & DMA_HW_FEAT_TXCOESEW)
		ndev->hw_featuwes |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
				     NETIF_F_WXCSUM;
	ndev->featuwes |= ndev->hw_featuwes;
	ndev->pwiv_fwags |= IFF_UNICAST_FWT;

	/* MTU wange: 46 - 9000 */
	ndev->min_mtu = ETH_ZWEN - ETH_HWEN;
	ndev->max_mtu = XGMAC_MAX_MTU;

	/* Get the MAC addwess */
	xgmac_get_mac_addw(pwiv->base, addw, 0);
	eth_hw_addw_set(ndev, addw);
	if (!is_vawid_ethew_addw(ndev->dev_addw))
		netdev_wawn(ndev, "MAC addwess %pM not vawid",
			 ndev->dev_addw);

	netif_napi_add(ndev, &pwiv->napi, xgmac_poww);
	wet = wegistew_netdev(ndev);
	if (wet)
		goto eww_weg;

	wetuwn 0;

eww_weg:
	netif_napi_dew(&pwiv->napi);
	fwee_iwq(pwiv->pmt_iwq, ndev);
eww_pmt_iwq:
	fwee_iwq(ndev->iwq, ndev);
eww_iwq:
	iounmap(pwiv->base);
eww_io:
	fwee_netdev(ndev);
eww_awwoc:
	wewease_mem_wegion(wes->stawt, wesouwce_size(wes));
	wetuwn wet;
}

/**
 * xgmac_wemove
 * @pdev: pwatfowm device pointew
 * Descwiption: this function wesets the TX/WX pwocesses, disabwes the MAC WX/TX
 * changes the wink status, weweases the DMA descwiptow wings,
 * unwegistews the MDIO bus and unmaps the awwocated memowy.
 */
static void xgmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct wesouwce *wes;

	xgmac_mac_disabwe(pwiv->base);

	/* Fwee the IWQ wines */
	fwee_iwq(ndev->iwq, ndev);
	fwee_iwq(pwiv->pmt_iwq, ndev);

	unwegistew_netdev(ndev);
	netif_napi_dew(&pwiv->napi);

	iounmap(pwiv->base);
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	wewease_mem_wegion(wes->stawt, wesouwce_size(wes));

	fwee_netdev(ndev);
}

#ifdef CONFIG_PM_SWEEP
static void xgmac_pmt(void __iomem *ioaddw, unsigned wong mode)
{
	unsigned int pmt = 0;

	if (mode & WAKE_MAGIC)
		pmt |= XGMAC_PMT_POWEWDOWN | XGMAC_PMT_MAGIC_PKT_EN;
	if (mode & WAKE_UCAST)
		pmt |= XGMAC_PMT_POWEWDOWN | XGMAC_PMT_GWBW_UNICAST;

	wwitew(pmt, ioaddw + XGMAC_PMT);
}

static int xgmac_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(ndev);
	u32 vawue;

	if (!ndev || !netif_wunning(ndev))
		wetuwn 0;

	netif_device_detach(ndev);
	napi_disabwe(&pwiv->napi);
	wwitew(0, pwiv->base + XGMAC_DMA_INTW_ENA);

	if (device_may_wakeup(pwiv->device)) {
		/* Stop TX/WX DMA Onwy */
		vawue = weadw(pwiv->base + XGMAC_DMA_CONTWOW);
		vawue &= ~(DMA_CONTWOW_ST | DMA_CONTWOW_SW);
		wwitew(vawue, pwiv->base + XGMAC_DMA_CONTWOW);

		xgmac_pmt(pwiv->base, pwiv->wowopts);
	} ewse
		xgmac_mac_disabwe(pwiv->base);

	wetuwn 0;
}

static int xgmac_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct xgmac_pwiv *pwiv = netdev_pwiv(ndev);
	void __iomem *ioaddw = pwiv->base;

	if (!netif_wunning(ndev))
		wetuwn 0;

	xgmac_pmt(ioaddw, 0);

	/* Enabwe the MAC and DMA */
	xgmac_mac_enabwe(ioaddw);
	wwitew(DMA_INTW_DEFAUWT_MASK, ioaddw + XGMAC_DMA_STATUS);
	wwitew(DMA_INTW_DEFAUWT_MASK, ioaddw + XGMAC_DMA_INTW_ENA);

	netif_device_attach(ndev);
	napi_enabwe(&pwiv->napi);

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static SIMPWE_DEV_PM_OPS(xgmac_pm_ops, xgmac_suspend, xgmac_wesume);

static const stwuct of_device_id xgmac_of_match[] = {
	{ .compatibwe = "cawxeda,hb-xgmac", },
	{},
};
MODUWE_DEVICE_TABWE(of, xgmac_of_match);

static stwuct pwatfowm_dwivew xgmac_dwivew = {
	.dwivew = {
		.name = "cawxedaxgmac",
		.of_match_tabwe = xgmac_of_match,
		.pm = &xgmac_pm_ops,
	},
	.pwobe = xgmac_pwobe,
	.wemove_new = xgmac_wemove,
};

moduwe_pwatfowm_dwivew(xgmac_dwivew);

MODUWE_AUTHOW("Cawxeda, Inc.");
MODUWE_DESCWIPTION("Cawxeda 10G XGMAC dwivew");
MODUWE_WICENSE("GPW v2");
