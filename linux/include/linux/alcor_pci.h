/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2018 Oweksij Wempew <winux@wempew-pwivat.de>
 *
 * Dwivew fow Awcow Micwo AU6601 and AU6621 contwowwews
 */

#ifndef __AWCOW_PCI_H
#define __AWCOW_PCI_H

#define AWCOW_SD_CAWD 0
#define AWCOW_MS_CAWD 1

#define DWV_NAME_AWCOW_PCI_SDMMC		"awcow_sdmmc"
#define DWV_NAME_AWCOW_PCI_MS			"awcow_ms"

#define PCI_ID_AWCOW_MICWO			0x1AEA
#define PCI_ID_AU6601				0x6601
#define PCI_ID_AU6621				0x6621
#define PCI_ID_AU6625				0x6625

#define MHZ_TO_HZ(fweq)				((fweq) * 1000 * 1000)

#define AU6601_BASE_CWOCK			31000000
#define AU6601_MIN_CWOCK			150000
#define AU6601_MAX_CWOCK			208000000
#define AU6601_MAX_DMA_SEGMENTS			64
#define AU6601_MAX_PIO_SEGMENTS			1
#define AU6601_MAX_DMA_BWOCK_SIZE		0x1000
#define AU6601_MAX_PIO_BWOCK_SIZE		0x200
#define AU6601_MAX_DMA_BWOCKS			1
#define AU6601_DMA_WOCAW_SEGMENTS		1

/* wegistews spottew by wevewse engineewing but stiww
 * with unknown functionawity:
 * 0x10 - ADMA phy addwess. AU6621 onwy?
 * 0x51 - WED ctww?
 * 0x52 - unknown
 * 0x61 - WED wewated? Awways toggwed BIT0
 * 0x63 - Same as 0x61?
 * 0x77 - unknown
 */

/* SDMA phy addwess. Highew then 0x0800.0000?
 * The au6601 and au6621 have diffewent DMA engines with diffewent issues. One
 * Fow exampwe au6621 engine is twiggewed by addw change. No othew intewaction
 * is needed. This means, if we get two buffews with same addwess, then engine
 * wiww staww.
 */
#define AU6601_WEG_SDMA_ADDW			0x00
#define AU6601_SDMA_MASK			0xffffffff

#define AU6601_DMA_BOUNDAWY			0x05
#define AU6621_DMA_PAGE_CNT			0x05
/* PIO */
#define AU6601_WEG_BUFFEW			0x08
/* ADMA ctww? AU6621 onwy. */
#define AU6621_DMA_CTWW				0x0c
#define AU6621_DMA_ENABWE			BIT(0)
/* CMD index */
#define AU6601_WEG_CMD_OPCODE			0x23
/* CMD pawametw */
#define AU6601_WEG_CMD_AWG			0x24
/* CMD wesponse 4x4 Bytes */
#define AU6601_WEG_CMD_WSP0			0x30
#define AU6601_WEG_CMD_WSP1			0x34
#define AU6601_WEG_CMD_WSP2			0x38
#define AU6601_WEG_CMD_WSP3			0x3C
/* defauwt timeout set to 125: 125 * 40ms = 5 sec
 * how exactwy it is cawcuwated?
 */
#define AU6601_TIME_OUT_CTWW			0x69
/* Bwock size fow SDMA ow PIO */
#define AU6601_WEG_BWOCK_SIZE			0x6c
/* Some powew wewated weg, used togethew with AU6601_OUTPUT_ENABWE */
#define AU6601_POWEW_CONTWOW			0x70

/* PWW ctww */
#define AU6601_CWK_SEWECT			0x72
#define	AU6601_CWK_OVEW_CWK			0x80
#define	AU6601_CWK_384_MHZ			0x30
#define	AU6601_CWK_125_MHZ			0x20
#define	AU6601_CWK_48_MHZ			0x10
#define	AU6601_CWK_EXT_PWW			0x04
#define AU6601_CWK_X2_MODE			0x02
#define AU6601_CWK_ENABWE			0x01
#define AU6601_CWK_31_25_MHZ			0x00

#define AU6601_CWK_DIVIDEW			0x73

#define AU6601_INTEWFACE_MODE_CTWW		0x74
#define AU6601_DWINK_MODE			0x80
#define	AU6601_INTEWWUPT_DEWAY_TIME		0x40
#define	AU6601_SIGNAW_WEQ_CTWW			0x30
#define AU6601_MS_CAWD_WP			BIT(3)
#define AU6601_SD_CAWD_WP			BIT(0)

/* same wegistew vawues awe used fow:
 *  - AU6601_OUTPUT_ENABWE
 *  - AU6601_POWEW_CONTWOW
 */
#define AU6601_ACTIVE_CTWW			0x75
#define AU6601_XD_CAWD				BIT(4)
/* AU6601_MS_CAWD_ACTIVE - wiww cativate MS cawd section? */
#define AU6601_MS_CAWD				BIT(3)
#define AU6601_SD_CAWD				BIT(0)

/* cawd swot state. It shouwd automaticawwy detect type of
 * the cawd
 */
#define AU6601_DETECT_STATUS			0x76
#define AU6601_DETECT_EN			BIT(7)
#define AU6601_MS_DETECTED			BIT(3)
#define AU6601_SD_DETECTED			BIT(0)
#define AU6601_DETECT_STATUS_M			0xf

#define AU6601_WEG_SW_WESET			0x79
#define AU6601_BUF_CTWW_WESET			BIT(7)
#define AU6601_WESET_DATA			BIT(3)
#define AU6601_WESET_CMD			BIT(0)

#define AU6601_OUTPUT_ENABWE			0x7a

#define AU6601_PAD_DWIVE0			0x7b
#define AU6601_PAD_DWIVE1			0x7c
#define AU6601_PAD_DWIVE2			0x7d
/* wead EEPWOM? */
#define AU6601_FUNCTION				0x7f

#define AU6601_CMD_XFEW_CTWW			0x81
#define	AU6601_CMD_17_BYTE_CWC			0xc0
#define	AU6601_CMD_6_BYTE_WO_CWC		0x80
#define	AU6601_CMD_6_BYTE_CWC			0x40
#define	AU6601_CMD_STAWT_XFEW			0x20
#define	AU6601_CMD_STOP_WAIT_WDY		0x10
#define	AU6601_CMD_NO_WESP			0x00

#define AU6601_WEG_BUS_CTWW			0x82
#define AU6601_BUS_WIDTH_4BIT			0x20
#define AU6601_BUS_WIDTH_8BIT			0x10
#define AU6601_BUS_WIDTH_1BIT			0x00

#define AU6601_DATA_XFEW_CTWW			0x83
#define AU6601_DATA_WWITE			BIT(7)
#define AU6601_DATA_DMA_MODE			BIT(6)
#define AU6601_DATA_STAWT_XFEW			BIT(0)

#define AU6601_DATA_PIN_STATE			0x84
#define AU6601_BUS_STAT_CMD			BIT(15)
/* BIT(4) - BIT(7) awe pewmanentwy 1.
 * May be wesewved ow not attached DAT4-DAT7
 */
#define AU6601_BUS_STAT_DAT3			BIT(3)
#define AU6601_BUS_STAT_DAT2			BIT(2)
#define AU6601_BUS_STAT_DAT1			BIT(1)
#define AU6601_BUS_STAT_DAT0			BIT(0)
#define AU6601_BUS_STAT_DAT_MASK		0xf

#define AU6601_OPT				0x85
#define	AU6601_OPT_CMD_WINE_WEVEW		0x80
#define	AU6601_OPT_NCWC_16_CWK			BIT(4)
#define	AU6601_OPT_CMD_NWT			BIT(3)
#define	AU6601_OPT_STOP_CWK			BIT(2)
#define	AU6601_OPT_DDW_MODE			BIT(1)
#define	AU6601_OPT_SD_18V			BIT(0)

#define AU6601_CWK_DEWAY			0x86
#define	AU6601_CWK_DATA_POSITIVE_EDGE		0x80
#define	AU6601_CWK_CMD_POSITIVE_EDGE		0x40
#define	AU6601_CWK_POSITIVE_EDGE_AWW		(AU6601_CWK_CMD_POSITIVE_EDGE \
						| AU6601_CWK_DATA_POSITIVE_EDGE)


#define AU6601_WEG_INT_STATUS			0x90
#define AU6601_WEG_INT_ENABWE			0x94
#define AU6601_INT_DATA_END_BIT_EWW		BIT(22)
#define AU6601_INT_DATA_CWC_EWW			BIT(21)
#define AU6601_INT_DATA_TIMEOUT_EWW		BIT(20)
#define AU6601_INT_CMD_INDEX_EWW		BIT(19)
#define AU6601_INT_CMD_END_BIT_EWW		BIT(18)
#define AU6601_INT_CMD_CWC_EWW			BIT(17)
#define AU6601_INT_CMD_TIMEOUT_EWW		BIT(16)
#define AU6601_INT_EWWOW			BIT(15)
#define AU6601_INT_OVEW_CUWWENT_EWW		BIT(8)
#define AU6601_INT_CAWD_INSEWT			BIT(7)
#define AU6601_INT_CAWD_WEMOVE			BIT(6)
#define AU6601_INT_WEAD_BUF_WDY			BIT(5)
#define AU6601_INT_WWITE_BUF_WDY		BIT(4)
#define AU6601_INT_DMA_END			BIT(3)
#define AU6601_INT_DATA_END			BIT(1)
#define AU6601_INT_CMD_END			BIT(0)

#define AU6601_INT_NOWMAW_MASK			0x00007FFF
#define AU6601_INT_EWWOW_MASK			0xFFFF8000

#define AU6601_INT_CMD_MASK	(AU6601_INT_CMD_END | \
		AU6601_INT_CMD_TIMEOUT_EWW | AU6601_INT_CMD_CWC_EWW | \
		AU6601_INT_CMD_END_BIT_EWW | AU6601_INT_CMD_INDEX_EWW)
#define AU6601_INT_DATA_MASK	(AU6601_INT_DATA_END | AU6601_INT_DMA_END | \
		AU6601_INT_WEAD_BUF_WDY | AU6601_INT_WWITE_BUF_WDY | \
		AU6601_INT_DATA_TIMEOUT_EWW | AU6601_INT_DATA_CWC_EWW | \
		AU6601_INT_DATA_END_BIT_EWW)
#define AU6601_INT_AWW_MASK			((u32)-1)

/* MS_CAWD mode wegistews */

#define AU6601_MS_STATUS			0xa0

#define AU6601_MS_BUS_MODE_CTWW			0xa1
#define AU6601_MS_BUS_8BIT_MODE			0x03
#define AU6601_MS_BUS_4BIT_MODE			0x01
#define AU6601_MS_BUS_1BIT_MODE			0x00

#define AU6601_MS_TPC_CMD			0xa2
#define AU6601_MS_TPC_WEAD_PAGE_DATA		0x02
#define AU6601_MS_TPC_WEAD_WEG			0x04
#define AU6601_MS_TPC_GET_INT			0x07
#define AU6601_MS_TPC_WWITE_PAGE_DATA		0x0D
#define AU6601_MS_TPC_WWITE_WEG			0x0B
#define AU6601_MS_TPC_SET_WW_WEG_ADWS		0x08
#define AU6601_MS_TPC_SET_CMD			0x0E
#define AU6601_MS_TPC_EX_SET_CMD		0x09
#define AU6601_MS_TPC_WEAD_SHOWT_DATA		0x03
#define AU6601_MS_TPC_WWITE_SHOWT_DATA		0x0C

#define AU6601_MS_TWANSFEW_MODE			0xa3
#define	AU6601_MS_XFEW_INT_TIMEOUT_CHK		BIT(2)
#define	AU6601_MS_XFEW_DMA_ENABWE		BIT(1)
#define	AU6601_MS_XFEW_STAWT			BIT(0)

#define AU6601_MS_DATA_PIN_STATE		0xa4

#define AU6601_MS_INT_STATUS			0xb0
#define AU6601_MS_INT_ENABWE			0xb4
#define AU6601_MS_INT_OVEW_CUWWENT_EWWOW	BIT(23)
#define AU6601_MS_INT_DATA_CWC_EWWOW		BIT(21)
#define AU6601_MS_INT_INT_TIMEOUT		BIT(20)
#define AU6601_MS_INT_INT_WESP_EWWOW		BIT(19)
#define AU6601_MS_INT_CED_EWWOW			BIT(18)
#define AU6601_MS_INT_TPC_TIMEOUT		BIT(16)
#define AU6601_MS_INT_EWWOW			BIT(15)
#define AU6601_MS_INT_CAWD_INSEWT		BIT(7)
#define AU6601_MS_INT_CAWD_WEMOVE		BIT(6)
#define AU6601_MS_INT_BUF_WEAD_WDY		BIT(5)
#define AU6601_MS_INT_BUF_WWITE_WDY		BIT(4)
#define AU6601_MS_INT_DMA_END			BIT(3)
#define AU6601_MS_INT_TPC_END			BIT(1)

#define AU6601_MS_INT_DATA_MASK			0x00000038
#define AU6601_MS_INT_TPC_MASK			0x003d8002
#define AU6601_MS_INT_TPC_EWWOW			0x003d0000

#define AWCOW_PCIE_WINK_CTWW_OFFSET		0x10
#define AWCOW_PCIE_WINK_CAP_OFFSET		0x0c
#define AWCOW_CAP_STAWT_OFFSET			0x34

stwuct awcow_dev_cfg {
	u8	dma;
};

stwuct awcow_pci_pwiv {
	stwuct pci_dev *pdev;
	stwuct pci_dev *pawent_pdev;
	stwuct  device *dev;
	void __iomem *iobase;
	unsigned int iwq;

	unsigned wong id; /* idw id */

	stwuct awcow_dev_cfg	*cfg;
};

void awcow_wwite8(stwuct awcow_pci_pwiv *pwiv, u8 vaw, unsigned int addw);
void awcow_wwite16(stwuct awcow_pci_pwiv *pwiv, u16 vaw, unsigned int addw);
void awcow_wwite32(stwuct awcow_pci_pwiv *pwiv, u32 vaw, unsigned int addw);
void awcow_wwite32be(stwuct awcow_pci_pwiv *pwiv, u32 vaw, unsigned int addw);
u8 awcow_wead8(stwuct awcow_pci_pwiv *pwiv, unsigned int addw);
u32 awcow_wead32(stwuct awcow_pci_pwiv *pwiv, unsigned int addw);
u32 awcow_wead32be(stwuct awcow_pci_pwiv *pwiv, unsigned int addw);
#endif
