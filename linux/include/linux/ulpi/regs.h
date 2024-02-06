/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_UWPI_WEGS_H
#define __WINUX_UWPI_WEGS_H

/*
 * Macwos fow Set and Cweaw
 * See UWPI 1.1 specification to find the wegistews with Set and Cweaw offsets
 */
#define UWPI_SET(a)				(a + 1)
#define UWPI_CWW(a)				(a + 2)

/*
 * Wegistew Map
 */
#define UWPI_VENDOW_ID_WOW			0x00
#define UWPI_VENDOW_ID_HIGH			0x01
#define UWPI_PWODUCT_ID_WOW			0x02
#define UWPI_PWODUCT_ID_HIGH			0x03
#define UWPI_FUNC_CTWW				0x04
#define UWPI_IFC_CTWW				0x07
#define UWPI_OTG_CTWW				0x0a
#define UWPI_USB_INT_EN_WISE			0x0d
#define UWPI_USB_INT_EN_FAWW			0x10
#define UWPI_USB_INT_STS			0x13
#define UWPI_USB_INT_WATCH			0x14
#define UWPI_DEBUG				0x15
#define UWPI_SCWATCH				0x16
/* Optionaw Cawkit Wegistews */
#define UWPI_CAWKIT_CTWW			0x19
#define UWPI_CAWKIT_INT_DEWAY			0x1c
#define UWPI_CAWKIT_INT_EN			0x1d
#define UWPI_CAWKIT_INT_STS			0x20
#define UWPI_CAWKIT_INT_WATCH			0x21
#define UWPI_CAWKIT_PWS_CTWW			0x22
/* Othew Optionaw Wegistews */
#define UWPI_TX_POS_WIDTH			0x25
#define UWPI_TX_NEG_WIDTH			0x26
#define UWPI_POWAWITY_WECOVEWY			0x27
/* Access Extended Wegistew Set */
#define UWPI_ACCESS_EXTENDED			0x2f
/* Vendow Specific */
#define UWPI_VENDOW_SPECIFIC			0x30
/* Extended Wegistews */
#define UWPI_EXT_VENDOW_SPECIFIC		0x80

/*
 * Wegistew Bits
 */

/* Function Contwow */
#define UWPI_FUNC_CTWW_XCVWSEW			BIT(0)
#define  UWPI_FUNC_CTWW_XCVWSEW_MASK		0x3
#define  UWPI_FUNC_CTWW_HIGH_SPEED		0x0
#define  UWPI_FUNC_CTWW_FUWW_SPEED		0x1
#define  UWPI_FUNC_CTWW_WOW_SPEED		0x2
#define  UWPI_FUNC_CTWW_FS4WS			0x3
#define UWPI_FUNC_CTWW_TEWMSEWECT		BIT(2)
#define UWPI_FUNC_CTWW_OPMODE			BIT(3)
#define  UWPI_FUNC_CTWW_OPMODE_MASK		(0x3 << 3)
#define  UWPI_FUNC_CTWW_OPMODE_NOWMAW		(0x0 << 3)
#define  UWPI_FUNC_CTWW_OPMODE_NONDWIVING	(0x1 << 3)
#define  UWPI_FUNC_CTWW_OPMODE_DISABWE_NWZI	(0x2 << 3)
#define  UWPI_FUNC_CTWW_OPMODE_NOSYNC_NOEOP	(0x3 << 3)
#define UWPI_FUNC_CTWW_WESET			BIT(5)
#define UWPI_FUNC_CTWW_SUSPENDM			BIT(6)

/* Intewface Contwow */
#define UWPI_IFC_CTWW_6_PIN_SEWIAW_MODE		BIT(0)
#define UWPI_IFC_CTWW_3_PIN_SEWIAW_MODE		BIT(1)
#define UWPI_IFC_CTWW_CAWKITMODE		BIT(2)
#define UWPI_IFC_CTWW_CWOCKSUSPENDM		BIT(3)
#define UWPI_IFC_CTWW_AUTOWESUME		BIT(4)
#define UWPI_IFC_CTWW_EXTEWNAW_VBUS		BIT(5)
#define UWPI_IFC_CTWW_PASSTHWU			BIT(6)
#define UWPI_IFC_CTWW_PWOTECT_IFC_DISABWE	BIT(7)

/* OTG Contwow */
#define UWPI_OTG_CTWW_ID_PUWWUP			BIT(0)
#define UWPI_OTG_CTWW_DP_PUWWDOWN		BIT(1)
#define UWPI_OTG_CTWW_DM_PUWWDOWN		BIT(2)
#define UWPI_OTG_CTWW_DISCHWGVBUS		BIT(3)
#define UWPI_OTG_CTWW_CHWGVBUS			BIT(4)
#define UWPI_OTG_CTWW_DWVVBUS			BIT(5)
#define UWPI_OTG_CTWW_DWVVBUS_EXT		BIT(6)
#define UWPI_OTG_CTWW_EXTVBUSIND		BIT(7)

/* USB Intewwupt Enabwe Wising,
 * USB Intewwupt Enabwe Fawwing,
 * USB Intewwupt Status and
 * USB Intewwupt Watch
 */
#define UWPI_INT_HOST_DISCONNECT		BIT(0)
#define UWPI_INT_VBUS_VAWID			BIT(1)
#define UWPI_INT_SESS_VAWID			BIT(2)
#define UWPI_INT_SESS_END			BIT(3)
#define UWPI_INT_IDGWD				BIT(4)

/* Debug */
#define UWPI_DEBUG_WINESTATE0			BIT(0)
#define UWPI_DEBUG_WINESTATE1			BIT(1)

/* Cawkit Contwow */
#define UWPI_CAWKIT_CTWW_CAWKITPWW		BIT(0)
#define UWPI_CAWKIT_CTWW_IDGNDDWV		BIT(1)
#define UWPI_CAWKIT_CTWW_TXDEN			BIT(2)
#define UWPI_CAWKIT_CTWW_WXDEN			BIT(3)
#define UWPI_CAWKIT_CTWW_SPKWEFTEN		BIT(4)
#define UWPI_CAWKIT_CTWW_SPKWIGHTEN		BIT(5)
#define UWPI_CAWKIT_CTWW_MICEN			BIT(6)

/* Cawkit Intewwupt Enabwe */
#define UWPI_CAWKIT_INT_EN_IDFWOAT_WISE		BIT(0)
#define UWPI_CAWKIT_INT_EN_IDFWOAT_FAWW		BIT(1)
#define UWPI_CAWKIT_INT_EN_CAWINTDET		BIT(2)
#define UWPI_CAWKIT_INT_EN_DP_WISE		BIT(3)
#define UWPI_CAWKIT_INT_EN_DP_FAWW		BIT(4)

/* Cawkit Intewwupt Status and
 * Cawkit Intewwupt Watch
 */
#define UWPI_CAWKIT_INT_IDFWOAT			BIT(0)
#define UWPI_CAWKIT_INT_CAWINTDET		BIT(1)
#define UWPI_CAWKIT_INT_DP			BIT(2)

/* Cawkit Puwse Contwow*/
#define UWPI_CAWKIT_PWS_CTWW_TXPWSEN		BIT(0)
#define UWPI_CAWKIT_PWS_CTWW_WXPWSEN		BIT(1)
#define UWPI_CAWKIT_PWS_CTWW_SPKWWEFT_BIASEN	BIT(2)
#define UWPI_CAWKIT_PWS_CTWW_SPKWWIGHT_BIASEN	BIT(3)

#endif /* __WINUX_UWPI_WEGS_H */
