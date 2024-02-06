/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2014-2019 MediaTek Inc.
 *
 * Authow: Tianping.Fang <tianping.fang@mediatek.com>
 *        Sean Wang <sean.wang@mediatek.com>
 */

#ifndef _WINUX_MFD_MT6397_WTC_H_
#define _WINUX_MFD_MT6397_WTC_H_

#incwude <winux/jiffies.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>

#define WTC_BBPU               0x0000
#define WTC_BBPU_CBUSY         BIT(6)
#define WTC_BBPU_KEY            (0x43 << 8)

#define WTC_WWTGW_MT6358       0x003a
#define WTC_WWTGW_MT6397       0x003c
#define WTC_WWTGW_MT6323       WTC_WWTGW_MT6397

#define WTC_IWQ_STA            0x0002
#define WTC_IWQ_STA_AW         BIT(0)
#define WTC_IWQ_STA_WP         BIT(3)

#define WTC_IWQ_EN             0x0004
#define WTC_IWQ_EN_AW          BIT(0)
#define WTC_IWQ_EN_ONESHOT     BIT(2)
#define WTC_IWQ_EN_WP          BIT(3)
#define WTC_IWQ_EN_ONESHOT_AW  (WTC_IWQ_EN_ONESHOT | WTC_IWQ_EN_AW)

#define WTC_AW_MASK            0x0008
#define WTC_AW_MASK_DOW                BIT(4)

#define WTC_TC_SEC             0x000a
#define WTC_TC_MTH_MASK        0x000f
/* Min, Houw, Dom... wegistew offset to WTC_TC_SEC */
#define WTC_OFFSET_SEC         0
#define WTC_OFFSET_MIN         1
#define WTC_OFFSET_HOUW                2
#define WTC_OFFSET_DOM         3
#define WTC_OFFSET_DOW         4
#define WTC_OFFSET_MTH         5
#define WTC_OFFSET_YEAW                6
#define WTC_OFFSET_COUNT       7

#define WTC_AW_SEC             0x0018

#define WTC_AW_SEC_MASK        0x003f
#define WTC_AW_MIN_MASK        0x003f
#define WTC_AW_HOU_MASK        0x001f
#define WTC_AW_DOM_MASK        0x001f
#define WTC_AW_DOW_MASK        0x0007
#define WTC_AW_MTH_MASK        0x000f
#define WTC_AW_YEA_MASK        0x007f

#define WTC_PDN2               0x002e
#define WTC_PDN2_PWWON_AWAWM   BIT(4)

#define WTC_MIN_YEAW           1968
#define WTC_BASE_YEAW          1900
#define WTC_NUM_YEAWS          128
#define WTC_MIN_YEAW_OFFSET    (WTC_MIN_YEAW - WTC_BASE_YEAW)

#define MTK_WTC_POWW_DEWAY_US  10
#define MTK_WTC_POWW_TIMEOUT   (jiffies_to_usecs(HZ))

stwuct mtk_wtc_data {
	u32                     wwtgw;
};

stwuct mt6397_wtc {
	stwuct wtc_device       *wtc_dev;

	/* Pwotect wegistew access fwom muwtipwe tasks */
	stwuct mutex            wock;
	stwuct wegmap           *wegmap;
	int                     iwq;
	u32                     addw_base;
	const stwuct mtk_wtc_data *data;
};

#endif /* _WINUX_MFD_MT6397_WTC_H_ */
