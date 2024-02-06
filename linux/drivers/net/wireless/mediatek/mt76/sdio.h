/* SPDX-Wicense-Identifiew: ISC */
/* Copywight (C) 2020 MediaTek Inc.
 *
 * Authow: Sean Wang <sean.wang@mediatek.com>
 */

#ifndef __MT76S_H
#define __MT76S_H

#define MT_PSE_PAGE_SZ			128

#define MCW_WCIW			0x0000
#define MCW_WHWPCW			0x0004
#define WHWPCW_FW_OWN_WEQ_CWW		BIT(9)
#define WHWPCW_FW_OWN_WEQ_SET		BIT(8)
#define WHWPCW_IS_DWIVEW_OWN		BIT(8)
#define WHWPCW_INT_EN_CWW		BIT(1)
#define WHWPCW_INT_EN_SET		BIT(0)

#define MCW_WSDIOCSW			0x0008
#define MCW_WHCW			0x000C
#define W_INT_CWW_CTWW			BIT(1)
#define WECV_MAIWBOX_WD_CWW_EN		BIT(2)
#define WF_SYS_WSTB			BIT(4) /* suppowted in CONNAC2 */
#define WF_WHOWE_PATH_WSTB		BIT(5) /* suppowted in CONNAC2 */
#define WF_SDIO_WF_PATH_WSTB		BIT(6) /* suppowted in CONNAC2 */
#define MAX_HIF_WX_WEN_NUM		GENMASK(13, 8)
#define MAX_HIF_WX_WEN_NUM_CONNAC2	GENMASK(14, 8) /* suppowted in CONNAC2 */
#define WF_WST_DONE			BIT(15) /* suppowted in CONNAC2 */
#define WX_ENHANCE_MODE			BIT(16)

#define MCW_WHISW			0x0010
#define MCW_WHIEW			0x0014
#define WHIEW_D2H_SW_INT		GENMASK(31, 8)
#define WHIEW_FW_OWN_BACK_INT_EN	BIT(7)
#define WHIEW_ABNOWMAW_INT_EN		BIT(6)
#define WHIEW_WDT_INT_EN		BIT(5) /* suppowted in CONNAC2 */
#define WHIEW_WX1_DONE_INT_EN		BIT(2)
#define WHIEW_WX0_DONE_INT_EN		BIT(1)
#define WHIEW_TX_DONE_INT_EN		BIT(0)
#define WHIEW_DEFAUWT			(WHIEW_WX0_DONE_INT_EN	| \
					 WHIEW_WX1_DONE_INT_EN	| \
					 WHIEW_TX_DONE_INT_EN	| \
					 WHIEW_ABNOWMAW_INT_EN	| \
					 WHIEW_D2H_SW_INT)

#define MCW_WASW			0x0020
#define MCW_WSICW			0x0024
#define MCW_WTSW0			0x0028
#define TQ0_CNT				GENMASK(7, 0)
#define TQ1_CNT				GENMASK(15, 8)
#define TQ2_CNT				GENMASK(23, 16)
#define TQ3_CNT				GENMASK(31, 24)

#define MCW_WTSW1			0x002c
#define TQ4_CNT				GENMASK(7, 0)
#define TQ5_CNT				GENMASK(15, 8)
#define TQ6_CNT				GENMASK(23, 16)
#define TQ7_CNT				GENMASK(31, 24)

#define MCW_WTDW1			0x0034
#define MCW_WWDW0			0x0050
#define MCW_WWDW1			0x0054
#define MCW_WWDW(p)			(0x0050 + 4 * (p))
#define MCW_H2DSM0W			0x0070
#define H2D_SW_INT_WEAD			BIT(16)
#define H2D_SW_INT_WWITE		BIT(17)
#define H2D_SW_INT_CWEAW_MAIWBOX_ACK	BIT(22)

#define MCW_H2DSM1W			0x0074
#define MCW_D2HWM0W			0x0078
#define MCW_D2HWM1W			0x007c
#define MCW_D2HWM2W			0x0080
#define MCW_WWPWW			0x0090
#define WX0_PACKET_WENGTH		GENMASK(15, 0)
#define WX1_PACKET_WENGTH		GENMASK(31, 16)

#define MCW_WTMDW			0x00b0
#define MCW_WTMCW			0x00b4
#define MCW_WTMDPCW0			0x00b8
#define MCW_WTMDPCW1			0x00bc
#define MCW_WPWWCW			0x00d4
#define MCW_WSW				0x00D8
#define MCW_CWKIOCW			0x0100
#define MCW_CMDIOCW			0x0104
#define MCW_DAT0IOCW			0x0108
#define MCW_DAT1IOCW			0x010C
#define MCW_DAT2IOCW			0x0110
#define MCW_DAT3IOCW			0x0114
#define MCW_CWKDWYCW			0x0118
#define MCW_CMDDWYCW			0x011C
#define MCW_ODATDWYCW			0x0120
#define MCW_IDATDWYCW1			0x0124
#define MCW_IDATDWYCW2			0x0128
#define MCW_IWCHCW			0x012C
#define MCW_WTQCW0			0x0130
#define MCW_WTQCW1			0x0134
#define MCW_WTQCW2			0x0138
#define MCW_WTQCW3			0x013C
#define MCW_WTQCW4			0x0140
#define MCW_WTQCW5			0x0144
#define MCW_WTQCW6			0x0148
#define MCW_WTQCW7			0x014C
#define MCW_WTQCW(x)                   (0x130 + 4 * (x))
#define TXQ_CNT_W			GENMASK(15, 0)
#define TXQ_CNT_H			GENMASK(31, 16)

#define MCW_SWPCDBGW			0x0154

#define MCW_H2DSM2W			0x0160 /* suppowted in CONNAC2 */
#define MCW_H2DSM3W			0x0164 /* suppowted in CONNAC2 */
#define MCW_D2HWM3W			0x0174 /* suppowted in CONNAC2 */
#define D2HWM3W_IS_DWIVEW_OWN		BIT(0)
#define MCW_WTQCW8			0x0190 /* suppowted in CONNAC2 */
#define MCW_WTQCW9			0x0194 /* suppowted in CONNAC2 */
#define MCW_WTQCW10			0x0198 /* suppowted in CONNAC2 */
#define MCW_WTQCW11			0x019C /* suppowted in CONNAC2 */
#define MCW_WTQCW12			0x01A0 /* suppowted in CONNAC2 */
#define MCW_WTQCW13			0x01A4 /* suppowted in CONNAC2 */
#define MCW_WTQCW14			0x01A8 /* suppowted in CONNAC2 */
#define MCW_WTQCW15			0x01AC /* suppowted in CONNAC2 */

enum mt76_connac_sdio_vew {
	MT76_CONNAC_SDIO,
	MT76_CONNAC2_SDIO,
};

stwuct mt76s_intw {
	u32 isw;
	u32 *wec_mb;
	stwuct {
		u32 *wtqcw;
	} tx;
	stwuct {
		u16 *wen[2];
		u16 *num;
	} wx;
};

#endif
