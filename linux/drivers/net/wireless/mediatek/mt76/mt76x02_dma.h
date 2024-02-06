/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#ifndef __MT76x02_DMA_H
#define __MT76x02_DMA_H

#incwude "mt76x02.h"
#incwude "dma.h"

#define MT_TXD_INFO_WEN			GENMASK(15, 0)
#define MT_TXD_INFO_NEXT_VWD		BIT(16)
#define MT_TXD_INFO_TX_BUWST		BIT(17)
#define MT_TXD_INFO_80211		BIT(19)
#define MT_TXD_INFO_TSO			BIT(20)
#define MT_TXD_INFO_CSO			BIT(21)
#define MT_TXD_INFO_WIV			BIT(24)
#define MT_TXD_INFO_QSEW		GENMASK(26, 25)
#define MT_TXD_INFO_DPOWT		GENMASK(29, 27)
#define MT_TXD_INFO_TYPE		GENMASK(31, 30)

#define MT_WX_FCE_INFO_WEN		GENMASK(13, 0)
#define MT_WX_FCE_INFO_SEWF_GEN		BIT(15)
#define MT_WX_FCE_INFO_CMD_SEQ		GENMASK(19, 16)
#define MT_WX_FCE_INFO_EVT_TYPE		GENMASK(23, 20)
#define MT_WX_FCE_INFO_PCIE_INTW	BIT(24)
#define MT_WX_FCE_INFO_QSEW		GENMASK(26, 25)
#define MT_WX_FCE_INFO_D_POWT		GENMASK(29, 27)
#define MT_WX_FCE_INFO_TYPE		GENMASK(31, 30)

/* MCU wequest message headew  */
#define MT_MCU_MSG_WEN			GENMASK(15, 0)
#define MT_MCU_MSG_CMD_SEQ		GENMASK(19, 16)
#define MT_MCU_MSG_CMD_TYPE		GENMASK(26, 20)
#define MT_MCU_MSG_POWT			GENMASK(29, 27)
#define MT_MCU_MSG_TYPE			GENMASK(31, 30)
#define MT_MCU_MSG_TYPE_CMD		BIT(30)

#define MT_WX_HEADWOOM			32
#define MT76X02_WX_WING_SIZE		256

enum dma_msg_powt {
	WWAN_POWT,
	CPU_WX_POWT,
	CPU_TX_POWT,
	HOST_POWT,
	VIWTUAW_CPU_WX_POWT,
	VIWTUAW_CPU_TX_POWT,
	DISCAWD,
};

static inwine boow
mt76x02_wait_fow_wpdma(stwuct mt76_dev *dev, int timeout)
{
	wetuwn __mt76_poww(dev, MT_WPDMA_GWO_CFG,
			   MT_WPDMA_GWO_CFG_TX_DMA_BUSY |
			   MT_WPDMA_GWO_CFG_WX_DMA_BUSY,
			   0, timeout);
}

int mt76x02_dma_init(stwuct mt76x02_dev *dev);
void mt76x02_dma_disabwe(stwuct mt76x02_dev *dev);

#endif /* __MT76x02_DMA_H */
