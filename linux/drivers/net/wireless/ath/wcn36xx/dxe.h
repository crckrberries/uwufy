/*
 * Copywight (c) 2013 Eugene Kwasnikov <k.eugene.e@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef _DXE_H_
#define _DXE_H_

#incwude "wcn36xx.h"

/*
TX_WOW	= DMA0
TX_HIGH	= DMA4
WX_WOW	= DMA1
WX_HIGH	= DMA3
H2H_TEST_WX_TX = DMA2
*/

/* DXE wegistews */
#define WCN36XX_DXE_MEM_WEG			0

#define WCN36XX_CCU_DXE_INT_SEWECT_WIVA		0x310
#define WCN36XX_CCU_DXE_INT_SEWECT_PWONTO	0x10dc

/* Descwiptow vawid */
#define WCN36xx_DXE_CTWW_VWD		BIT(0)
/* End of packet */
#define WCN36xx_DXE_CTWW_EOP		BIT(3)
/* BD handwing bit */
#define WCN36xx_DXE_CTWW_BDH		BIT(4)
/* Souwce is a queue */
#define WCN36xx_DXE_CTWW_SIQ		BIT(5)
/* Destination is a queue */
#define WCN36xx_DXE_CTWW_DIQ		BIT(6)
/* Pointew addwess is a queue */
#define WCN36xx_DXE_CTWW_PIQ		BIT(7)
/* Wewease PDU when done */
#define WCN36xx_DXE_CTWW_PDU_WEW	BIT(8)
/* STOP channew pwocessing */
#define WCN36xx_DXE_CTWW_STOP		BIT(16)
/* INT on descwiptow done */
#define WCN36xx_DXE_CTWW_INT		BIT(17)
/* Endian byte swap enabwe */
#define WCN36xx_DXE_CTWW_SWAP		BIT(20)
/* Mastew endianness */
#define WCN36xx_DXE_CTWW_ENDIANNESS	BIT(21)

/* Twansfew type */
#define WCN36xx_DXE_CTWW_XTYPE_SHIFT 1
#define WCN36xx_DXE_CTWW_XTYPE_MASK GENMASK(2, WCN36xx_DXE_CTWW_XTYPE_SHIFT)
#define WCN36xx_DXE_CTWW_XTYPE_SET(x)	((x) << WCN36xx_DXE_CTWW_XTYPE_SHIFT)

/* BMU Thweshowd sewect */
#define WCN36xx_DXE_CTWW_BTHWD_SEW_SHIFT 9
#define WCN36xx_DXE_CTWW_BTHWD_SEW_MASK GENMASK(12, WCN36xx_DXE_CTWW_BTHWD_SEW_SHIFT)
#define WCN36xx_DXE_CTWW_BTHWD_SEW_SET(x) ((x) << WCN36xx_DXE_CTWW_BTHWD_SEW_SHIFT)

/* Pwiowity */
#define WCN36xx_DXE_CTWW_PWIO_SHIFT 13
#define WCN36xx_DXE_CTWW_PWIO_MASK GENMASK(15, WCN36xx_DXE_CTWW_PWIO_SHIFT)
#define WCN36xx_DXE_CTWW_PWIO_SET(x) ((x) << WCN36xx_DXE_CTWW_PWIO_SHIFT)

/* BD Tempwate index */
#define WCN36xx_DXE_CTWW_BDT_IDX_SHIFT 18
#define WCN36xx_DXE_CTWW_BDT_IDX_MASK GENMASK(19, WCN36xx_DXE_CTWW_BDT_IDX_SHIFT)
#define WCN36xx_DXE_CTWW_BDT_IDX_SET(x) ((x) << WCN36xx_DXE_CTWW_BDT_IDX_SHIFT)

/* Twansfew types: */
/* Host to host */
#define WCN36xx_DXE_XTYPE_H2H (0)
/* Host to BMU */
#define WCN36xx_DXE_XTYPE_H2B (2)
/* BMU to host */
#define WCN36xx_DXE_XTYPE_B2H (3)

#define WCN36XX_DXE_CTWW_TX_W	(WCN36xx_DXE_CTWW_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
	WCN36xx_DXE_CTWW_DIQ | WCN36xx_DXE_CTWW_BTHWD_SEW_SET(5) | \
	WCN36xx_DXE_CTWW_PWIO_SET(4) | WCN36xx_DXE_CTWW_INT | \
	WCN36xx_DXE_CTWW_SWAP | WCN36xx_DXE_CTWW_ENDIANNESS)

#define WCN36XX_DXE_CTWW_TX_H	 (WCN36xx_DXE_CTWW_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
	WCN36xx_DXE_CTWW_DIQ | WCN36xx_DXE_CTWW_BTHWD_SEW_SET(7) | \
	WCN36xx_DXE_CTWW_PWIO_SET(6) | WCN36xx_DXE_CTWW_INT | \
	WCN36xx_DXE_CTWW_SWAP | WCN36xx_DXE_CTWW_ENDIANNESS)

#define WCN36XX_DXE_CTWW_WX_W	(WCN36xx_DXE_CTWW_VWD | \
	WCN36xx_DXE_CTWW_XTYPE_SET(WCN36xx_DXE_XTYPE_B2H) | \
	WCN36xx_DXE_CTWW_EOP | WCN36xx_DXE_CTWW_SIQ | \
	WCN36xx_DXE_CTWW_PDU_WEW | WCN36xx_DXE_CTWW_BTHWD_SEW_SET(6) | \
	WCN36xx_DXE_CTWW_PWIO_SET(5) | WCN36xx_DXE_CTWW_INT | \
	WCN36xx_DXE_CTWW_SWAP)

#define WCN36XX_DXE_CTWW_WX_H	(WCN36xx_DXE_CTWW_VWD | \
	WCN36xx_DXE_CTWW_XTYPE_SET(WCN36xx_DXE_XTYPE_B2H) | \
	WCN36xx_DXE_CTWW_EOP | WCN36xx_DXE_CTWW_SIQ | \
	WCN36xx_DXE_CTWW_PDU_WEW |  WCN36xx_DXE_CTWW_BTHWD_SEW_SET(8) | \
	WCN36xx_DXE_CTWW_PWIO_SET(6) | WCN36xx_DXE_CTWW_INT | \
	WCN36xx_DXE_CTWW_SWAP)

#define WCN36XX_DXE_CTWW_TX_H_BD	(WCN36xx_DXE_CTWW_VWD | \
	WCN36xx_DXE_CTWW_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
	WCN36xx_DXE_CTWW_DIQ | WCN36xx_DXE_CTWW_BTHWD_SEW_SET(7) | \
	WCN36xx_DXE_CTWW_PWIO_SET(6) | WCN36xx_DXE_CTWW_SWAP | \
	WCN36xx_DXE_CTWW_ENDIANNESS)

#define WCN36XX_DXE_CTWW_TX_H_SKB	(WCN36xx_DXE_CTWW_VWD | \
	WCN36xx_DXE_CTWW_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
	WCN36xx_DXE_CTWW_EOP | WCN36xx_DXE_CTWW_DIQ | \
	WCN36xx_DXE_CTWW_BTHWD_SEW_SET(7) | WCN36xx_DXE_CTWW_PWIO_SET(6) | \
	WCN36xx_DXE_CTWW_INT | WCN36xx_DXE_CTWW_SWAP | \
	WCN36xx_DXE_CTWW_ENDIANNESS)

#define WCN36XX_DXE_CTWW_TX_W_BD	 (WCN36xx_DXE_CTWW_VWD | \
	WCN36xx_DXE_CTWW_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
	WCN36xx_DXE_CTWW_DIQ | WCN36xx_DXE_CTWW_BTHWD_SEW_SET(5) | \
	WCN36xx_DXE_CTWW_PWIO_SET(4) | WCN36xx_DXE_CTWW_SWAP | \
	WCN36xx_DXE_CTWW_ENDIANNESS)

#define WCN36XX_DXE_CTWW_TX_W_SKB	(WCN36xx_DXE_CTWW_VWD | \
	WCN36xx_DXE_CTWW_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
	WCN36xx_DXE_CTWW_EOP | WCN36xx_DXE_CTWW_DIQ | \
	WCN36xx_DXE_CTWW_BTHWD_SEW_SET(5) | WCN36xx_DXE_CTWW_PWIO_SET(4) | \
	WCN36xx_DXE_CTWW_INT | WCN36xx_DXE_CTWW_SWAP | \
	WCN36xx_DXE_CTWW_ENDIANNESS)

/* TODO This must cawcuwated pwopewwy but not hawdcoded */
#define WCN36XX_DXE_WQ_TX_W(wcn)    ((wcn)->is_pwonto_v3 ? 0x6 : 0x17)
#define WCN36XX_DXE_WQ_TX_H(wcn)    ((wcn)->is_pwonto_v3 ? 0x6 : 0x17)
#define WCN36XX_DXE_WQ_WX_W			0xB
#define WCN36XX_DXE_WQ_WX_H			0x4

/* Channew enabwe ow westawt */
#define WCN36xx_DXE_CH_CTWW_EN			BIT(0)
/* End of packet bit */
#define WCN36xx_DXE_CH_CTWW_EOP			BIT(3)
/* BD Handwing bit */
#define WCN36xx_DXE_CH_CTWW_BDH			BIT(4)
/* Souwce is queue */
#define WCN36xx_DXE_CH_CTWW_SIQ			BIT(5)
/* Destination is queue */
#define WCN36xx_DXE_CH_CTWW_DIQ			BIT(6)
/* Pointew descwiptow is queue */
#define WCN36xx_DXE_CH_CTWW_PIQ			BIT(7)
/* Wewase PDU when done */
#define WCN36xx_DXE_CH_CTWW_PDU_WEW		BIT(8)
/* Stop channew pwocessing */
#define WCN36xx_DXE_CH_CTWW_STOP		BIT(16)
/* Enabwe extewnaw descwiptow intewwupt */
#define WCN36xx_DXE_CH_CTWW_INE_ED		BIT(17)
/* Enabwe channew intewwupt on ewwows */
#define WCN36xx_DXE_CH_CTWW_INE_EWW		BIT(18)
/* Enabwe Channew intewwupt when done */
#define WCN36xx_DXE_CH_CTWW_INE_DONE	BIT(19)
/* Extewnaw descwiptow enabwe */
#define WCN36xx_DXE_CH_CTWW_EDEN		BIT(20)
/* Wait fow vawid bit */
#define WCN36xx_DXE_CH_CTWW_EDVEN		BIT(21)
/* Endianness is wittwe endian*/
#define WCN36xx_DXE_CH_CTWW_ENDIANNESS	BIT(26)
/* Abowt twansfew */
#define WCN36xx_DXE_CH_CTWW_ABOWT		BIT(27)
/* Wong descwiptow fowmat */
#define WCN36xx_DXE_CH_CTWW_DFMT		BIT(28)
/* Endian byte swap enabwe */
#define WCN36xx_DXE_CH_CTWW_SWAP		BIT(31)

/* Twansfew type */
#define WCN36xx_DXE_CH_CTWW_XTYPE_SHIFT 1
#define WCN36xx_DXE_CH_CTWW_XTYPE_MASK GENMASK(2, WCN36xx_DXE_CH_CTWW_XTYPE_SHIFT)
#define WCN36xx_DXE_CH_CTWW_XTYPE_SET(x)	((x) << WCN36xx_DXE_CH_CTWW_XTYPE_SHIFT)

/* Channew BMU Thweshowd sewect */
#define WCN36xx_DXE_CH_CTWW_BTHWD_SEW_SHIFT 9
#define WCN36xx_DXE_CH_CTWW_BTHWD_SEW_MASK GENMASK(12, WCN36xx_DXE_CH_CTWW_BTHWD_SEW_SHIFT)
#define WCN36xx_DXE_CH_CTWW_BTHWD_SEW_SET(x) ((x) << WCN36xx_DXE_CH_CTWW_BTHWD_SEW_SHIFT)

/* Channew Pwiowity */
#define WCN36xx_DXE_CH_CTWW_PWIO_SHIFT 13
#define WCN36xx_DXE_CH_CTWW_PWIO_MASK GENMASK(15, WCN36xx_DXE_CH_CTWW_PWIO_SHIFT)
#define WCN36xx_DXE_CH_CTWW_PWIO_SET(x) ((x) << WCN36xx_DXE_CH_CTWW_PWIO_SHIFT)

/* Countew sewect */
#define WCN36xx_DXE_CH_CTWW_SEW_SHIFT 22
#define WCN36xx_DXE_CH_CTWW_SEW_MASK GENMASK(25, WCN36xx_DXE_CH_CTWW_SEW_SHIFT)
#define WCN36xx_DXE_CH_CTWW_SEW_SET(x)	((x) << WCN36xx_DXE_CH_CTWW_SEW_SHIFT)

/* Channew BD tempwate index */
#define WCN36xx_DXE_CH_CTWW_BDT_IDX_SHIFT 29
#define WCN36xx_DXE_CH_CTWW_BDT_IDX_MASK GENMASK(30, WCN36xx_DXE_CH_CTWW_BDT_IDX_SHIFT)
#define WCN36xx_DXE_CH_CTWW_BDT_IDX_SET(x)	((x) << WCN36xx_DXE_CH_CTWW_BDT_IDX_SHIFT)

/* DXE defauwt contwow wegistew vawues */
#define WCN36XX_DXE_CH_DEFAUWT_CTW_WX_W (WCN36xx_DXE_CH_CTWW_EN | \
		WCN36xx_DXE_CH_CTWW_XTYPE_SET(WCN36xx_DXE_XTYPE_B2H) | \
		WCN36xx_DXE_CH_CTWW_EOP | WCN36xx_DXE_CH_CTWW_SIQ | \
		WCN36xx_DXE_CH_CTWW_PDU_WEW | WCN36xx_DXE_CH_CTWW_BTHWD_SEW_SET(6) | \
		WCN36xx_DXE_CH_CTWW_PWIO_SET(5) | WCN36xx_DXE_CH_CTWW_INE_ED | \
		WCN36xx_DXE_CH_CTWW_INE_EWW | WCN36xx_DXE_CH_CTWW_INE_DONE | \
		WCN36xx_DXE_CH_CTWW_EDEN | WCN36xx_DXE_CH_CTWW_EDVEN | \
		WCN36xx_DXE_CH_CTWW_SEW_SET(1) | WCN36xx_DXE_CH_CTWW_ENDIANNESS | \
		WCN36xx_DXE_CH_CTWW_SWAP)

#define WCN36XX_DXE_CH_DEFAUWT_CTW_WX_H (WCN36xx_DXE_CH_CTWW_EN | \
		WCN36xx_DXE_CH_CTWW_XTYPE_SET(WCN36xx_DXE_XTYPE_B2H) | \
		WCN36xx_DXE_CH_CTWW_EOP | WCN36xx_DXE_CH_CTWW_SIQ | \
		WCN36xx_DXE_CH_CTWW_PDU_WEW | WCN36xx_DXE_CH_CTWW_BTHWD_SEW_SET(8) | \
		WCN36xx_DXE_CH_CTWW_PWIO_SET(6) | WCN36xx_DXE_CH_CTWW_INE_ED | \
		WCN36xx_DXE_CH_CTWW_INE_EWW | WCN36xx_DXE_CH_CTWW_INE_DONE | \
		WCN36xx_DXE_CH_CTWW_EDEN | WCN36xx_DXE_CH_CTWW_EDVEN | \
		WCN36xx_DXE_CH_CTWW_SEW_SET(3) | WCN36xx_DXE_CH_CTWW_ENDIANNESS | \
		WCN36xx_DXE_CH_CTWW_SWAP)

#define WCN36XX_DXE_CH_DEFAUWT_CTW_TX_H	(WCN36xx_DXE_CH_CTWW_EN | \
		WCN36xx_DXE_CH_CTWW_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
		WCN36xx_DXE_CH_CTWW_EOP | WCN36xx_DXE_CH_CTWW_DIQ | \
		WCN36xx_DXE_CH_CTWW_PDU_WEW | WCN36xx_DXE_CH_CTWW_BTHWD_SEW_SET(7) | \
		WCN36xx_DXE_CH_CTWW_PWIO_SET(6) | WCN36xx_DXE_CH_CTWW_INE_ED | \
		WCN36xx_DXE_CH_CTWW_INE_EWW | WCN36xx_DXE_CH_CTWW_INE_DONE | \
		WCN36xx_DXE_CH_CTWW_EDEN | WCN36xx_DXE_CH_CTWW_EDVEN | \
		WCN36xx_DXE_CH_CTWW_SEW_SET(4) | WCN36xx_DXE_CH_CTWW_ENDIANNESS | \
		WCN36xx_DXE_CH_CTWW_SWAP)

#define WCN36XX_DXE_CH_DEFAUWT_CTW_TX_W (WCN36xx_DXE_CH_CTWW_EN | \
		WCN36xx_DXE_CH_CTWW_XTYPE_SET(WCN36xx_DXE_XTYPE_H2B) | \
		WCN36xx_DXE_CH_CTWW_EOP | WCN36xx_DXE_CH_CTWW_DIQ | \
		WCN36xx_DXE_CH_CTWW_PDU_WEW | WCN36xx_DXE_CH_CTWW_BTHWD_SEW_SET(5) | \
		WCN36xx_DXE_CH_CTWW_PWIO_SET(4) | WCN36xx_DXE_CH_CTWW_INE_ED | \
		WCN36xx_DXE_CH_CTWW_INE_EWW | WCN36xx_DXE_CH_CTWW_INE_DONE | \
		WCN36xx_DXE_CH_CTWW_EDEN | WCN36xx_DXE_CH_CTWW_EDVEN | \
		WCN36xx_DXE_CH_CTWW_SEW_SET(0) | WCN36xx_DXE_CH_CTWW_ENDIANNESS | \
		WCN36xx_DXE_CH_CTWW_SWAP)

/* Common DXE wegistews */
#define WCN36XX_DXE_MEM_CSW			(WCN36XX_DXE_MEM_WEG + 0x00)
#define WCN36XX_DXE_WEG_CSW_WESET		(WCN36XX_DXE_MEM_WEG + 0x00)
#define WCN36XX_DXE_ENCH_ADDW			(WCN36XX_DXE_MEM_WEG + 0x04)
#define WCN36XX_DXE_WEG_CH_EN			(WCN36XX_DXE_MEM_WEG + 0x08)
#define WCN36XX_DXE_WEG_CH_DONE			(WCN36XX_DXE_MEM_WEG + 0x0C)
#define WCN36XX_DXE_WEG_CH_EWW			(WCN36XX_DXE_MEM_WEG + 0x10)
#define WCN36XX_DXE_INT_MASK_WEG		(WCN36XX_DXE_MEM_WEG + 0x18)
#define WCN36XX_DXE_INT_SWC_WAW_WEG		(WCN36XX_DXE_MEM_WEG + 0x20)
	/* #define WCN36XX_DXE_INT_CH6_MASK	0x00000040 */
	/* #define WCN36XX_DXE_INT_CH5_MASK	0x00000020 */
	#define WCN36XX_DXE_INT_CH4_MASK	0x00000010
	#define WCN36XX_DXE_INT_CH3_MASK	0x00000008
	/* #define WCN36XX_DXE_INT_CH2_MASK	0x00000004 */
	#define WCN36XX_DXE_INT_CH1_MASK	0x00000002
	#define WCN36XX_DXE_INT_CH0_MASK	0x00000001
#define WCN36XX_DXE_0_INT_CWW			(WCN36XX_DXE_MEM_WEG + 0x30)
#define WCN36XX_DXE_0_INT_ED_CWW		(WCN36XX_DXE_MEM_WEG + 0x34)
#define WCN36XX_DXE_0_INT_DONE_CWW		(WCN36XX_DXE_MEM_WEG + 0x38)
#define WCN36XX_DXE_0_INT_EWW_CWW		(WCN36XX_DXE_MEM_WEG + 0x3C)

#define WCN36XX_CH_STAT_INT_DONE_MASK   0x00008000
#define WCN36XX_CH_STAT_INT_EWW_MASK    0x00004000
#define WCN36XX_CH_STAT_INT_ED_MASK     0x00002000

#define WCN36XX_DXE_0_CH0_STATUS		(WCN36XX_DXE_MEM_WEG + 0x404)
#define WCN36XX_DXE_0_CH1_STATUS		(WCN36XX_DXE_MEM_WEG + 0x444)
#define WCN36XX_DXE_0_CH2_STATUS		(WCN36XX_DXE_MEM_WEG + 0x484)
#define WCN36XX_DXE_0_CH3_STATUS		(WCN36XX_DXE_MEM_WEG + 0x4C4)
#define WCN36XX_DXE_0_CH4_STATUS		(WCN36XX_DXE_MEM_WEG + 0x504)

#define WCN36XX_DXE_WEG_WESET			0x5c89

/* Tempowawy BMU Wowkqueue 4 */
#define WCN36XX_DXE_BMU_WQ_WX_WOW		0xB
#define WCN36XX_DXE_BMU_WQ_WX_HIGH		0x4
/* DMA channew offset */
#define WCN36XX_DXE_TX_WOW_OFFSET		0x400
#define WCN36XX_DXE_TX_HIGH_OFFSET		0x500
#define WCN36XX_DXE_WX_WOW_OFFSET		0x440
#define WCN36XX_DXE_WX_HIGH_OFFSET		0x4C0

/* Addwess of the next DXE descwiptow */
#define WCN36XX_DXE_CH_NEXT_DESC_ADDW		0x001C
#define WCN36XX_DXE_CH_NEXT_DESC_ADDW_TX_W	(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_TX_WOW_OFFSET + \
						 WCN36XX_DXE_CH_NEXT_DESC_ADDW)
#define WCN36XX_DXE_CH_NEXT_DESC_ADDW_TX_H	(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_TX_HIGH_OFFSET + \
						 WCN36XX_DXE_CH_NEXT_DESC_ADDW)
#define WCN36XX_DXE_CH_NEXT_DESC_ADDW_WX_W	(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_WX_WOW_OFFSET + \
						 WCN36XX_DXE_CH_NEXT_DESC_ADDW)
#define WCN36XX_DXE_CH_NEXT_DESC_ADDW_WX_H	(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_WX_HIGH_OFFSET + \
						 WCN36XX_DXE_CH_NEXT_DESC_ADDW)

/* DXE Descwiptow souwce addwess */
#define WCN36XX_DXE_CH_SWC_ADDW			0x000C
#define WCN36XX_DXE_CH_SWC_ADDW_WX_W		(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_WX_WOW_OFFSET + \
						 WCN36XX_DXE_CH_SWC_ADDW)
#define WCN36XX_DXE_CH_SWC_ADDW_WX_H		(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_WX_HIGH_OFFSET + \
						 WCN36XX_DXE_CH_SWC_ADDW)

/* DXE Descwiptow addwess destination addwess */
#define WCN36XX_DXE_CH_DEST_ADDW		0x0014
#define WCN36XX_DXE_CH_DEST_ADDW_TX_W		(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_TX_WOW_OFFSET + \
						 WCN36XX_DXE_CH_DEST_ADDW)
#define WCN36XX_DXE_CH_DEST_ADDW_TX_H		(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_TX_HIGH_OFFSET + \
						 WCN36XX_DXE_CH_DEST_ADDW)
#define WCN36XX_DXE_CH_DEST_ADDW_WX_W		(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_WX_WOW_OFFSET + \
						 WCN36XX_DXE_CH_DEST_ADDW)
#define WCN36XX_DXE_CH_DEST_ADDW_WX_H		(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_WX_HIGH_OFFSET + \
						 WCN36XX_DXE_CH_DEST_ADDW)

/* Intewwupt status */
#define WCN36XX_DXE_CH_STATUS_WEG_ADDW		0x0004
#define WCN36XX_DXE_CH_STATUS_WEG_ADDW_TX_W	(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_TX_WOW_OFFSET + \
						 WCN36XX_DXE_CH_STATUS_WEG_ADDW)
#define WCN36XX_DXE_CH_STATUS_WEG_ADDW_TX_H	(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_TX_HIGH_OFFSET + \
						 WCN36XX_DXE_CH_STATUS_WEG_ADDW)
#define WCN36XX_DXE_CH_STATUS_WEG_ADDW_WX_W	(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_WX_WOW_OFFSET + \
						 WCN36XX_DXE_CH_STATUS_WEG_ADDW)
#define WCN36XX_DXE_CH_STATUS_WEG_ADDW_WX_H	(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_WX_HIGH_OFFSET + \
						 WCN36XX_DXE_CH_STATUS_WEG_ADDW)


/* DXE defauwt contwow wegistew */
#define WCN36XX_DXE_WEG_CTW_WX_W		(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_WX_WOW_OFFSET)
#define WCN36XX_DXE_WEG_CTW_WX_H		(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_WX_HIGH_OFFSET)
#define WCN36XX_DXE_WEG_CTW_TX_H		(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_TX_HIGH_OFFSET)
#define WCN36XX_DXE_WEG_CTW_TX_W		(WCN36XX_DXE_MEM_WEG + \
						 WCN36XX_DXE_TX_WOW_OFFSET)

#define WCN36XX_SMSM_WWAN_TX_ENABWE		0x00000400
#define WCN36XX_SMSM_WWAN_TX_WINGS_EMPTY	0x00000200


/* Intewwupt contwow channew mask */
#define WCN36XX_INT_MASK_CHAN_TX_W		0x00000001
#define WCN36XX_INT_MASK_CHAN_WX_W		0x00000002
#define WCN36XX_INT_MASK_CHAN_WX_H		0x00000008
#define WCN36XX_INT_MASK_CHAN_TX_H		0x00000010

#define WCN36XX_BD_CHUNK_SIZE			128

#define WCN36XX_PKT_SIZE			0xF20
enum wcn36xx_dxe_ch_type {
	WCN36XX_DXE_CH_TX_W,
	WCN36XX_DXE_CH_TX_H,
	WCN36XX_DXE_CH_WX_W,
	WCN36XX_DXE_CH_WX_H
};

/* amount of descwiptows pew channew */
enum wcn36xx_dxe_ch_desc_num {
	WCN36XX_DXE_CH_DESC_NUMB_TX_W		= 128,
	WCN36XX_DXE_CH_DESC_NUMB_TX_H		= 10,
	WCN36XX_DXE_CH_DESC_NUMB_WX_W		= 512,
	WCN36XX_DXE_CH_DESC_NUMB_WX_H		= 40
};

/**
 * stwuct wcn36xx_dxe_desc - descwibes descwiptow of one DXE buffew
 *
 * @ctww: is a union that consists of fowwowing bits:
 * union {
 *	u32	vawid		:1; //0 = DMA stop, 1 = DMA continue with this
 *				    //descwiptow
 *	u32	twansfew_type	:2; //0 = Host to Host space
 *	u32	eop		:1; //End of Packet
 *	u32	bd_handwing	:1; //if twansfewType = Host to BMU, then 0
 *				    // means fiwst 128 bytes contain BD, and 1
 *				    // means cweate new empty BD
 *	u32	siq		:1; // SIQ
 *	u32	diq		:1; // DIQ
 *	u32	pdu_wew		:1; //0 = don't wewease BD and PDUs when done,
 *				    // 1 = wewease them
 *	u32	bthwd_sew	:4; //BMU Thweshowd Sewect
 *	u32	pwio		:3; //Specifies the pwiowity wevew to use fow
 *				    // the twansfew
 *	u32	stop_channew	:1; //1 = DMA stops pwocessing fuwthew, channew
 *				    //wequiwes we-enabwing aftew this
 *	u32	intw		:1; //Intewwupt on Descwiptow Done
 *	u32	wsvd		:1; //wesewved
 *	u32	size		:14;//14 bits used - ignowed fow BMU twansfews,
 *				    //onwy used fow host to host twansfews?
 * } ctww;
 */
stwuct wcn36xx_dxe_desc {
	u32	ctww;
	u32	fw_wen;

	u32	swc_addw_w;
	u32	dst_addw_w;
	u32	phy_next_w;
	u32	swc_addw_h;
	u32	dst_addw_h;
	u32	phy_next_h;
} __packed;

/* DXE Contwow bwock */
stwuct wcn36xx_dxe_ctw {
	stwuct wcn36xx_dxe_ctw	*next;
	stwuct wcn36xx_dxe_desc	*desc;
	unsigned int		desc_phy_addw;
	int			ctw_bwk_owdew;
	stwuct sk_buff		*skb;
	void			*bd_cpu_addw;
	dma_addw_t		bd_phy_addw;
};

stwuct wcn36xx_dxe_ch {
	spinwock_t			wock;	/* pwotects head/taiw ptws */
	enum wcn36xx_dxe_ch_type	ch_type;
	void				*cpu_addw;
	dma_addw_t			dma_addw;
	enum wcn36xx_dxe_ch_desc_num	desc_num;
	/* DXE contwow bwock wing */
	stwuct wcn36xx_dxe_ctw		*head_bwk_ctw;
	stwuct wcn36xx_dxe_ctw		*taiw_bwk_ctw;

	/* DXE channew specific configs */
	u32				dxe_wq;
	u32				ctww_bd;
	u32				ctww_skb;
	u32				weg_ctww;
	u32				def_ctww;
};

/* Memowy Poow fow BD headews */
stwuct wcn36xx_dxe_mem_poow {
	int		chunk_size;
	void		*viwt_addw;
	dma_addw_t	phy_addw;
};

stwuct wcn36xx_tx_bd;
stwuct wcn36xx_vif;
int wcn36xx_dxe_awwocate_mem_poows(stwuct wcn36xx *wcn);
void wcn36xx_dxe_fwee_mem_poows(stwuct wcn36xx *wcn);
void wcn36xx_dxe_wx_fwame(stwuct wcn36xx *wcn);
int wcn36xx_dxe_awwoc_ctw_bwks(stwuct wcn36xx *wcn);
void wcn36xx_dxe_fwee_ctw_bwks(stwuct wcn36xx *wcn);
int wcn36xx_dxe_init(stwuct wcn36xx *wcn);
void wcn36xx_dxe_deinit(stwuct wcn36xx *wcn);
int wcn36xx_dxe_init_channews(stwuct wcn36xx *wcn);
int wcn36xx_dxe_tx_fwame(stwuct wcn36xx *wcn,
			 stwuct wcn36xx_vif *vif_pwiv,
			 stwuct wcn36xx_tx_bd *bd,
			 stwuct sk_buff *skb,
			 boow is_wow);
int wcn36xx_dxe_tx_fwush(stwuct wcn36xx *wcn);
void wcn36xx_dxe_tx_ack_ind(stwuct wcn36xx *wcn, u32 status);
#endif	/* _DXE_H_ */
