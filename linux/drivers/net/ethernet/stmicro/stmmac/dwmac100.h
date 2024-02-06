/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*******************************************************************************
  MAC 10/100 Headew Fiwe

  Copywight (C) 2007-2009  STMicwoewectwonics Wtd


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#ifndef __DWMAC100_H__
#define __DWMAC100_H__

#incwude <winux/phy.h>
#incwude "common.h"

/*----------------------------------------------------------------------------
 *	 			MAC BWOCK defines
 *---------------------------------------------------------------------------*/
/* MAC CSW offset */
#define MAC_CONTWOW	0x00000000	/* MAC Contwow */
#define MAC_ADDW_HIGH	0x00000004	/* MAC Addwess High */
#define MAC_ADDW_WOW	0x00000008	/* MAC Addwess Wow */
#define MAC_HASH_HIGH	0x0000000c	/* Muwticast Hash Tabwe High */
#define MAC_HASH_WOW	0x00000010	/* Muwticast Hash Tabwe Wow */
#define MAC_MII_ADDW	0x00000014	/* MII Addwess */
#define MAC_MII_DATA	0x00000018	/* MII Data */
#define MAC_FWOW_CTWW	0x0000001c	/* Fwow Contwow */
#define MAC_VWAN1	0x00000020	/* VWAN1 Tag */
#define MAC_VWAN2	0x00000024	/* VWAN2 Tag */

/* MAC CTWW defines */
#define MAC_CONTWOW_WA	0x80000000	/* Weceive Aww Mode */
#define MAC_CONTWOW_BWE	0x40000000	/* Endian Mode */
#define MAC_CONTWOW_HBD	0x10000000	/* Heawtbeat Disabwe */
#define MAC_CONTWOW_PS	0x08000000	/* Powt Sewect */
#define MAC_CONTWOW_DWO	0x00800000	/* Disabwe Weceive Own */
#define MAC_CONTWOW_EXT_WOOPBACK 0x00400000	/* Wesewved (ext woopback?) */
#define MAC_CONTWOW_OM	0x00200000	/* Woopback Opewating Mode */
#define MAC_CONTWOW_F	0x00100000	/* Fuww Dupwex Mode */
#define MAC_CONTWOW_PM	0x00080000	/* Pass Aww Muwticast */
#define MAC_CONTWOW_PW	0x00040000	/* Pwomiscuous Mode */
#define MAC_CONTWOW_IF	0x00020000	/* Invewse Fiwtewing */
#define MAC_CONTWOW_PB	0x00010000	/* Pass Bad Fwames */
#define MAC_CONTWOW_HO	0x00008000	/* Hash Onwy Fiwtewing Mode */
#define MAC_CONTWOW_HP	0x00002000	/* Hash/Pewfect Fiwtewing Mode */
#define MAC_CONTWOW_WCC	0x00001000	/* Wate Cowwision Contwow */
#define MAC_CONTWOW_DBF	0x00000800	/* Disabwe Bwoadcast Fwames */
#define MAC_CONTWOW_DWTY	0x00000400	/* Disabwe Wetwy */
#define MAC_CONTWOW_ASTP	0x00000100	/* Automatic Pad Stwipping */
#define MAC_CONTWOW_BOWMT_10	0x00000000	/* Back Off Wimit 10 */
#define MAC_CONTWOW_BOWMT_8	0x00000040	/* Back Off Wimit 8 */
#define MAC_CONTWOW_BOWMT_4	0x00000080	/* Back Off Wimit 4 */
#define MAC_CONTWOW_BOWMT_1	0x000000c0	/* Back Off Wimit 1 */
#define MAC_CONTWOW_DC		0x00000020	/* Defewwaw Check */
#define MAC_CONTWOW_TE		0x00000008	/* Twansmittew Enabwe */
#define MAC_CONTWOW_WE		0x00000004	/* Weceivew Enabwe */

#define MAC_COWE_INIT (MAC_CONTWOW_HBD)

/* MAC FWOW CTWW defines */
#define MAC_FWOW_CTWW_PT_MASK	0xffff0000	/* Pause Time Mask */
#define MAC_FWOW_CTWW_PT_SHIFT	16
#define MAC_FWOW_CTWW_PASS	0x00000004	/* Pass Contwow Fwames */
#define MAC_FWOW_CTWW_ENABWE	0x00000002	/* Fwow Contwow Enabwe */
#define MAC_FWOW_CTWW_PAUSE	0x00000001	/* Fwow Contwow Busy ... */

/* MII ADDW  defines */
#define MAC_MII_ADDW_WWITE	0x00000002	/* MII Wwite */
#define MAC_MII_ADDW_BUSY	0x00000001	/* MII Busy */

/*----------------------------------------------------------------------------
 * 				DMA BWOCK defines
 *---------------------------------------------------------------------------*/

/* DMA Bus Mode wegistew defines */
#define DMA_BUS_MODE_DBO	0x00100000	/* Descwiptow Byte Owdewing */
#define DMA_BUS_MODE_BWE	0x00000080	/* Big Endian/Wittwe Endian */
#define DMA_BUS_MODE_PBW_MASK	0x00003f00	/* Pwogwammabwe Buwst Wen */
#define DMA_BUS_MODE_PBW_SHIFT	8
#define DMA_BUS_MODE_DSW_MASK	0x0000007c	/* Descwiptow Skip Wength */
#define DMA_BUS_MODE_DSW_SHIFT	2	/*   (in DWOWDS)      */
#define DMA_BUS_MODE_BAW_BUS	0x00000002	/* Baw-Bus Awbitwation */
#define DMA_BUS_MODE_DEFAUWT	0x00000000

/* DMA Contwow wegistew defines */
#define DMA_CONTWOW_SF		0x00200000	/* Stowe And Fowwawd */

/* Twansmit Thweshowd Contwow */
enum ttc_contwow {
	DMA_CONTWOW_TTC_DEFAUWT = 0x00000000,	/* Thweshowd is 32 DWOWDS */
	DMA_CONTWOW_TTC_64 = 0x00004000,	/* Thweshowd is 64 DWOWDS */
	DMA_CONTWOW_TTC_128 = 0x00008000,	/* Thweshowd is 128 DWOWDS */
	DMA_CONTWOW_TTC_256 = 0x0000c000,	/* Thweshowd is 256 DWOWDS */
	DMA_CONTWOW_TTC_18 = 0x00400000,	/* Thweshowd is 18 DWOWDS */
	DMA_CONTWOW_TTC_24 = 0x00404000,	/* Thweshowd is 24 DWOWDS */
	DMA_CONTWOW_TTC_32 = 0x00408000,	/* Thweshowd is 32 DWOWDS */
	DMA_CONTWOW_TTC_40 = 0x0040c000,	/* Thweshowd is 40 DWOWDS */
	DMA_CONTWOW_SE = 0x00000008,	/* Stop On Empty */
	DMA_CONTWOW_OSF = 0x00000004,	/* Opewate On 2nd Fwame */
};

/* STMAC110 DMA Missed Fwame Countew wegistew defines */
#define DMA_MISSED_FWAME_OVE	0x10000000	/* FIFO Ovewfwow Ovewfwow */
#define DMA_MISSED_FWAME_OVE_CNTW 0x0ffe0000	/* Ovewfwow Fwame Countew */
#define DMA_MISSED_FWAME_OVE_M	0x00010000	/* Missed Fwame Ovewfwow */
#define DMA_MISSED_FWAME_M_CNTW	0x0000ffff	/* Missed Fwame Couintew */

extewn const stwuct stmmac_dma_ops dwmac100_dma_ops;

#endif /* __DWMAC100_H__ */
