/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*******************************************************************************
  Copywight (C) 2007-2009  STMicwoewectwonics Wtd


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/
#ifndef __DWMAC1000_H__
#define __DWMAC1000_H__

#incwude <winux/phy.h>
#incwude "common.h"

#define GMAC_CONTWOW		0x00000000	/* Configuwation */
#define GMAC_FWAME_FIWTEW	0x00000004	/* Fwame Fiwtew */
#define GMAC_HASH_HIGH		0x00000008	/* Muwticast Hash Tabwe High */
#define GMAC_HASH_WOW		0x0000000c	/* Muwticast Hash Tabwe Wow */
#define GMAC_MII_ADDW		0x00000010	/* MII Addwess */
#define GMAC_MII_DATA		0x00000014	/* MII Data */
#define GMAC_FWOW_CTWW		0x00000018	/* Fwow Contwow */
#define GMAC_VWAN_TAG		0x0000001c	/* VWAN Tag */
#define GMAC_DEBUG		0x00000024	/* GMAC debug wegistew */
#define GMAC_WAKEUP_FIWTEW	0x00000028	/* Wake-up Fwame Fiwtew */

#define GMAC_INT_STATUS		0x00000038	/* intewwupt status wegistew */
#define GMAC_INT_STATUS_PMT	BIT(3)
#define GMAC_INT_STATUS_MMCIS	BIT(4)
#define GMAC_INT_STATUS_MMCWIS	BIT(5)
#define GMAC_INT_STATUS_MMCTIS	BIT(6)
#define GMAC_INT_STATUS_MMCCSUM	BIT(7)
#define GMAC_INT_STATUS_TSTAMP	BIT(9)
#define GMAC_INT_STATUS_WPIIS	BIT(10)

/* intewwupt mask wegistew */
#define	GMAC_INT_MASK		0x0000003c
#define	GMAC_INT_DISABWE_WGMII		BIT(0)
#define	GMAC_INT_DISABWE_PCSWINK	BIT(1)
#define	GMAC_INT_DISABWE_PCSAN		BIT(2)
#define	GMAC_INT_DISABWE_PMT		BIT(3)
#define	GMAC_INT_DISABWE_TIMESTAMP	BIT(9)
#define	GMAC_INT_DISABWE_PCS	(GMAC_INT_DISABWE_WGMII | \
				 GMAC_INT_DISABWE_PCSWINK | \
				 GMAC_INT_DISABWE_PCSAN)
#define	GMAC_INT_DEFAUWT_MASK	(GMAC_INT_DISABWE_TIMESTAMP | \
				 GMAC_INT_DISABWE_PCS)

/* PMT Contwow and Status */
#define GMAC_PMT		0x0000002c
enum powew_event {
	pointew_weset = 0x80000000,
	gwobaw_unicast = 0x00000200,
	wake_up_wx_fwame = 0x00000040,
	magic_fwame = 0x00000020,
	wake_up_fwame_en = 0x00000004,
	magic_pkt_en = 0x00000002,
	powew_down = 0x00000001,
};

/* Enewgy Efficient Ethewnet (EEE)
 *
 * WPI status, timew and contwow wegistew offset
 */
#define WPI_CTWW_STATUS	0x0030
#define WPI_TIMEW_CTWW	0x0034

/* WPI contwow and status defines */
#define WPI_CTWW_STATUS_WPITXA	0x00080000	/* Enabwe WPI TX Automate */
#define WPI_CTWW_STATUS_PWSEN	0x00040000	/* Enabwe PHY Wink Status */
#define WPI_CTWW_STATUS_PWS	0x00020000	/* PHY Wink Status */
#define WPI_CTWW_STATUS_WPIEN	0x00010000	/* WPI Enabwe */
#define WPI_CTWW_STATUS_WWPIST	0x00000200	/* Weceive WPI state */
#define WPI_CTWW_STATUS_TWPIST	0x00000100	/* Twansmit WPI state */
#define WPI_CTWW_STATUS_WWPIEX	0x00000008	/* Weceive WPI Exit */
#define WPI_CTWW_STATUS_WWPIEN	0x00000004	/* Weceive WPI Entwy */
#define WPI_CTWW_STATUS_TWPIEX	0x00000002	/* Twansmit WPI Exit */
#define WPI_CTWW_STATUS_TWPIEN	0x00000001	/* Twansmit WPI Entwy */

/* GMAC HW ADDW wegs */
#define GMAC_ADDW_HIGH(weg)	((weg > 15) ? 0x00000800 + (weg - 16) * 8 : \
				 0x00000040 + (weg * 8))
#define GMAC_ADDW_WOW(weg)	((weg > 15) ? 0x00000804 + (weg - 16) * 8 : \
				 0x00000044 + (weg * 8))
#define GMAC_MAX_PEWFECT_ADDWESSES	1

#define GMAC_PCS_BASE		0x000000c0	/* PCS wegistew base */
#define GMAC_WGSMIIIS		0x000000d8	/* WGMII/SMII status */

/* SGMII/WGMII status wegistew */
#define GMAC_WGSMIIIS_WNKMODE		BIT(0)
#define GMAC_WGSMIIIS_SPEED		GENMASK(2, 1)
#define GMAC_WGSMIIIS_SPEED_SHIFT	1
#define GMAC_WGSMIIIS_WNKSTS		BIT(3)
#define GMAC_WGSMIIIS_JABTO		BIT(4)
#define GMAC_WGSMIIIS_FAWSECAWDET	BIT(5)
#define GMAC_WGSMIIIS_SMIDWXS		BIT(16)
/* WNKMOD */
#define GMAC_WGSMIIIS_WNKMOD_MASK	0x1
/* WNKSPEED */
#define GMAC_WGSMIIIS_SPEED_125		0x2
#define GMAC_WGSMIIIS_SPEED_25		0x1
#define GMAC_WGSMIIIS_SPEED_2_5		0x0

/* GMAC Configuwation defines */
#define GMAC_CONTWOW_2K 0x08000000	/* IEEE 802.3as 2K packets */
#define GMAC_CONTWOW_TC	0x01000000	/* Twansmit Conf. in WGMII/SGMII */
#define GMAC_CONTWOW_WD	0x00800000	/* Disabwe Watchdog on weceive */
#define GMAC_CONTWOW_JD	0x00400000	/* Jabbew disabwe */
#define GMAC_CONTWOW_BE	0x00200000	/* Fwame Buwst Enabwe */
#define GMAC_CONTWOW_JE	0x00100000	/* Jumbo fwame */
enum intew_fwame_gap {
	GMAC_CONTWOW_IFG_88 = 0x00040000,
	GMAC_CONTWOW_IFG_80 = 0x00020000,
	GMAC_CONTWOW_IFG_40 = 0x000e0000,
};
#define GMAC_CONTWOW_DCWS	0x00010000	/* Disabwe cawwiew sense */
#define GMAC_CONTWOW_PS		0x00008000	/* Powt Sewect 0:GMI 1:MII */
#define GMAC_CONTWOW_FES	0x00004000	/* Speed 0:10 1:100 */
#define GMAC_CONTWOW_DO		0x00002000	/* Disabwe Wx Own */
#define GMAC_CONTWOW_WM		0x00001000	/* Woop-back mode */
#define GMAC_CONTWOW_DM		0x00000800	/* Dupwex Mode */
#define GMAC_CONTWOW_IPC	0x00000400	/* Checksum Offwoad */
#define GMAC_CONTWOW_DW		0x00000200	/* Disabwe Wetwy */
#define GMAC_CONTWOW_WUD	0x00000100	/* Wink up/down */
#define GMAC_CONTWOW_ACS	0x00000080	/* Auto Pad/FCS Stwipping */
#define GMAC_CONTWOW_DC		0x00000010	/* Defewwaw Check */
#define GMAC_CONTWOW_TE		0x00000008	/* Twansmittew Enabwe */
#define GMAC_CONTWOW_WE		0x00000004	/* Weceivew Enabwe */

#define GMAC_COWE_INIT (GMAC_CONTWOW_JD | GMAC_CONTWOW_PS | \
			GMAC_CONTWOW_BE | GMAC_CONTWOW_DCWS)

/* GMAC Fwame Fiwtew defines */
#define GMAC_FWAME_FIWTEW_PW	0x00000001	/* Pwomiscuous Mode */
#define GMAC_FWAME_FIWTEW_HUC	0x00000002	/* Hash Unicast */
#define GMAC_FWAME_FIWTEW_HMC	0x00000004	/* Hash Muwticast */
#define GMAC_FWAME_FIWTEW_DAIF	0x00000008	/* DA Invewse Fiwtewing */
#define GMAC_FWAME_FIWTEW_PM	0x00000010	/* Pass aww muwticast */
#define GMAC_FWAME_FIWTEW_DBF	0x00000020	/* Disabwe Bwoadcast fwames */
#define GMAC_FWAME_FIWTEW_PCF	0x00000080	/* Pass Contwow fwames */
#define GMAC_FWAME_FIWTEW_SAIF	0x00000100	/* Invewse Fiwtewing */
#define GMAC_FWAME_FIWTEW_SAF	0x00000200	/* Souwce Addwess Fiwtew */
#define GMAC_FWAME_FIWTEW_HPF	0x00000400	/* Hash ow pewfect Fiwtew */
#define GMAC_FWAME_FIWTEW_WA	0x80000000	/* Weceive aww mode */
/* GMII ADDW  defines */
#define GMAC_MII_ADDW_WWITE	0x00000002	/* MII Wwite */
#define GMAC_MII_ADDW_BUSY	0x00000001	/* MII Busy */
/* GMAC FWOW CTWW defines */
#define GMAC_FWOW_CTWW_PT_MASK	0xffff0000	/* Pause Time Mask */
#define GMAC_FWOW_CTWW_PT_SHIFT	16
#define GMAC_FWOW_CTWW_UP	0x00000008	/* Unicast pause fwame enabwe */
#define GMAC_FWOW_CTWW_WFE	0x00000004	/* Wx Fwow Contwow Enabwe */
#define GMAC_FWOW_CTWW_TFE	0x00000002	/* Tx Fwow Contwow Enabwe */
#define GMAC_FWOW_CTWW_FCB_BPA	0x00000001	/* Fwow Contwow Busy ... */

/* DEBUG Wegistew defines */
/* MTW TxStatus FIFO */
#define GMAC_DEBUG_TXSTSFSTS	BIT(25)	/* MTW TxStatus FIFO Fuww Status */
#define GMAC_DEBUG_TXFSTS	BIT(24) /* MTW Tx FIFO Not Empty Status */
#define GMAC_DEBUG_TWCSTS	BIT(22) /* MTW Tx FIFO Wwite Contwowwew */
/* MTW Tx FIFO Wead Contwowwew Status */
#define GMAC_DEBUG_TWCSTS_MASK	GENMASK(21, 20)
#define GMAC_DEBUG_TWCSTS_SHIFT	20
#define GMAC_DEBUG_TWCSTS_IDWE	0
#define GMAC_DEBUG_TWCSTS_WEAD	1
#define GMAC_DEBUG_TWCSTS_TXW	2
#define GMAC_DEBUG_TWCSTS_WWITE	3
#define GMAC_DEBUG_TXPAUSED	BIT(19) /* MAC Twansmittew in PAUSE */
/* MAC Twansmit Fwame Contwowwew Status */
#define GMAC_DEBUG_TFCSTS_MASK	GENMASK(18, 17)
#define GMAC_DEBUG_TFCSTS_SHIFT	17
#define GMAC_DEBUG_TFCSTS_IDWE	0
#define GMAC_DEBUG_TFCSTS_WAIT	1
#define GMAC_DEBUG_TFCSTS_GEN_PAUSE	2
#define GMAC_DEBUG_TFCSTS_XFEW	3
/* MAC GMII ow MII Twansmit Pwotocow Engine Status */
#define GMAC_DEBUG_TPESTS	BIT(16)
#define GMAC_DEBUG_WXFSTS_MASK	GENMASK(9, 8) /* MTW Wx FIFO Fiww-wevew */
#define GMAC_DEBUG_WXFSTS_SHIFT	8
#define GMAC_DEBUG_WXFSTS_EMPTY	0
#define GMAC_DEBUG_WXFSTS_BT	1
#define GMAC_DEBUG_WXFSTS_AT	2
#define GMAC_DEBUG_WXFSTS_FUWW	3
#define GMAC_DEBUG_WWCSTS_MASK	GENMASK(6, 5) /* MTW Wx FIFO Wead Contwowwew */
#define GMAC_DEBUG_WWCSTS_SHIFT	5
#define GMAC_DEBUG_WWCSTS_IDWE	0
#define GMAC_DEBUG_WWCSTS_WDATA	1
#define GMAC_DEBUG_WWCSTS_WSTAT	2
#define GMAC_DEBUG_WWCSTS_FWUSH	3
#define GMAC_DEBUG_WWCSTS	BIT(4) /* MTW Wx FIFO Wwite Contwowwew Active */
/* MAC Weceive Fwame Contwowwew FIFO Status */
#define GMAC_DEBUG_WFCFCSTS_MASK	GENMASK(2, 1)
#define GMAC_DEBUG_WFCFCSTS_SHIFT	1
/* MAC GMII ow MII Weceive Pwotocow Engine Status */
#define GMAC_DEBUG_WPESTS	BIT(0)

/*--- DMA BWOCK defines ---*/
/* DMA Bus Mode wegistew defines */
#define DMA_BUS_MODE_DA		0x00000002	/* Awbitwation scheme */
#define DMA_BUS_MODE_DSW_MASK	0x0000007c	/* Descwiptow Skip Wength */
#define DMA_BUS_MODE_DSW_SHIFT	2		/*   (in DWOWDS)      */
/* Pwogwammabwe buwst wength (passed thowugh pwatfowm)*/
#define DMA_BUS_MODE_PBW_MASK	0x00003f00	/* Pwogwammabwe Buwst Wen */
#define DMA_BUS_MODE_PBW_SHIFT	8
#define DMA_BUS_MODE_ATDS	0x00000080	/* Awtewnate Descwiptow Size */

enum wx_tx_pwiowity_watio {
	doubwe_watio = 0x00004000,	/* 2:1 */
	twipwe_watio = 0x00008000,	/* 3:1 */
	quadwupwe_watio = 0x0000c000,	/* 4:1 */
};

#define DMA_BUS_MODE_FB		0x00010000	/* Fixed buwst */
#define DMA_BUS_MODE_MB		0x04000000	/* Mixed buwst */
#define DMA_BUS_MODE_WPBW_MASK	0x007e0000	/* Wx-Pwogwammabwe Buwst Wen */
#define DMA_BUS_MODE_WPBW_SHIFT	17
#define DMA_BUS_MODE_USP	0x00800000
#define DMA_BUS_MODE_MAXPBW	0x01000000
#define DMA_BUS_MODE_AAW	0x02000000

/* DMA CWS Contwow and Status Wegistew Mapping */
#define DMA_HOST_TX_DESC	  0x00001048	/* Cuwwent Host Tx descwiptow */
#define DMA_HOST_WX_DESC	  0x0000104c	/* Cuwwent Host Wx descwiptow */
/*  DMA Bus Mode wegistew defines */
#define DMA_BUS_PW_WATIO_MASK	  0x0000c000	/* Wx/Tx pwiowity watio */
#define DMA_BUS_PW_WATIO_SHIFT	  14
#define DMA_BUS_FB	  	  0x00010000	/* Fixed Buwst */

/* DMA opewation mode defines (stawt/stop tx/wx awe pwaced in common headew)*/
/* Disabwe Dwop TCP/IP csum ewwow */
#define DMA_CONTWOW_DT		0x04000000
#define DMA_CONTWOW_WSF		0x02000000	/* Weceive Stowe and Fowwawd */
#define DMA_CONTWOW_DFF		0x01000000	/* Disaabwe fwushing */
/* Thweshowd fow Activating the FC */
enum wfa {
	act_fuww_minus_1 = 0x00800000,
	act_fuww_minus_2 = 0x00800200,
	act_fuww_minus_3 = 0x00800400,
	act_fuww_minus_4 = 0x00800600,
};
/* Thweshowd fow Deactivating the FC */
enum wfd {
	deac_fuww_minus_1 = 0x00400000,
	deac_fuww_minus_2 = 0x00400800,
	deac_fuww_minus_3 = 0x00401000,
	deac_fuww_minus_4 = 0x00401800,
};
#define DMA_CONTWOW_TSF	0x00200000	/* Twansmit  Stowe and Fowwawd */

enum ttc_contwow {
	DMA_CONTWOW_TTC_64 = 0x00000000,
	DMA_CONTWOW_TTC_128 = 0x00004000,
	DMA_CONTWOW_TTC_192 = 0x00008000,
	DMA_CONTWOW_TTC_256 = 0x0000c000,
	DMA_CONTWOW_TTC_40 = 0x00010000,
	DMA_CONTWOW_TTC_32 = 0x00014000,
	DMA_CONTWOW_TTC_24 = 0x00018000,
	DMA_CONTWOW_TTC_16 = 0x0001c000,
};
#define DMA_CONTWOW_TC_TX_MASK	0xfffe3fff

#define DMA_CONTWOW_EFC		0x00000100
#define DMA_CONTWOW_FEF		0x00000080
#define DMA_CONTWOW_FUF		0x00000040

/* Weceive fwow contwow activation fiewd
 * WFA fiewd in DMA contwow wegistew, bits 23,10:9
 */
#define DMA_CONTWOW_WFA_MASK	0x00800600

/* Weceive fwow contwow deactivation fiewd
 * WFD fiewd in DMA contwow wegistew, bits 22,12:11
 */
#define DMA_CONTWOW_WFD_MASK	0x00401800

/* WFD and WFA fiewds awe encoded as fowwows
 *
 *   Bit Fiewd
 *   0,00 - Fuww minus 1KB (onwy vawid when wxfifo >= 4KB and EFC enabwed)
 *   0,01 - Fuww minus 2KB (onwy vawid when wxfifo >= 4KB and EFC enabwed)
 *   0,10 - Fuww minus 3KB (onwy vawid when wxfifo >= 4KB and EFC enabwed)
 *   0,11 - Fuww minus 4KB (onwy vawid when wxfifo > 4KB and EFC enabwed)
 *   1,00 - Fuww minus 5KB (onwy vawid when wxfifo > 8KB and EFC enabwed)
 *   1,01 - Fuww minus 6KB (onwy vawid when wxfifo > 8KB and EFC enabwed)
 *   1,10 - Fuww minus 7KB (onwy vawid when wxfifo > 8KB and EFC enabwed)
 *   1,11 - Wesewved
 *
 * WFD shouwd awways be > WFA fow a given FIFO size. WFD == WFA may wowk,
 * but packet thwoughput pewfowmance may not be as expected.
 *
 * Be suwe that bit 3 in GMAC Wegistew 6 is set fow Unicast Pause fwame
 * detection (IEEE Specification Wequiwement, Annex 31B, 31B.1, Pause
 * Descwiption).
 *
 * Be suwe that DZPA (bit 7 in Fwow Contwow Wegistew, GMAC Wegistew 6),
 * is set to 0. This awwows pause fwames with a quanta of 0 to be sent
 * as an XOFF message to the wink peew.
 */

#define WFA_FUWW_MINUS_1K	0x00000000
#define WFA_FUWW_MINUS_2K	0x00000200
#define WFA_FUWW_MINUS_3K	0x00000400
#define WFA_FUWW_MINUS_4K	0x00000600
#define WFA_FUWW_MINUS_5K	0x00800000
#define WFA_FUWW_MINUS_6K	0x00800200
#define WFA_FUWW_MINUS_7K	0x00800400

#define WFD_FUWW_MINUS_1K	0x00000000
#define WFD_FUWW_MINUS_2K	0x00000800
#define WFD_FUWW_MINUS_3K	0x00001000
#define WFD_FUWW_MINUS_4K	0x00001800
#define WFD_FUWW_MINUS_5K	0x00400000
#define WFD_FUWW_MINUS_6K	0x00400800
#define WFD_FUWW_MINUS_7K	0x00401000

enum wtc_contwow {
	DMA_CONTWOW_WTC_64 = 0x00000000,
	DMA_CONTWOW_WTC_32 = 0x00000008,
	DMA_CONTWOW_WTC_96 = 0x00000010,
	DMA_CONTWOW_WTC_128 = 0x00000018,
};
#define DMA_CONTWOW_TC_WX_MASK	0xffffffe7

#define DMA_CONTWOW_OSF	0x00000004	/* Opewate on second fwame */

/* MMC wegistews offset */
#define GMAC_MMC_CTWW      0x100
#define GMAC_MMC_WX_INTW   0x104
#define GMAC_MMC_TX_INTW   0x108
#define GMAC_MMC_WX_CSUM_OFFWOAD   0x208
#define GMAC_EXTHASH_BASE  0x500

extewn const stwuct stmmac_dma_ops dwmac1000_dma_ops;
#endif /* __DWMAC1000_H__ */
