/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */
#ifndef __MT76_DMA_H
#define __MT76_DMA_H

#define DMA_DUMMY_DATA			((void *)~0)

#define MT_WING_SIZE			0x10

#define MT_DMA_CTW_SD_WEN1		GENMASK(13, 0)
#define MT_DMA_CTW_WAST_SEC1		BIT(14)
#define MT_DMA_CTW_BUWST		BIT(15)
#define MT_DMA_CTW_SD_WEN0		GENMASK(29, 16)
#define MT_DMA_CTW_WAST_SEC0		BIT(30)
#define MT_DMA_CTW_DMA_DONE		BIT(31)
#define MT_DMA_CTW_TO_HOST		BIT(8)
#define MT_DMA_CTW_TO_HOST_A		BIT(12)
#define MT_DMA_CTW_DWOP			BIT(14)
#define MT_DMA_CTW_TOKEN		GENMASK(31, 16)
#define MT_DMA_CTW_SDP1_H		GENMASK(19, 16)
#define MT_DMA_CTW_SDP0_H		GENMASK(3, 0)
#define MT_DMA_CTW_WO_DWOP		BIT(8)

#define MT_DMA_PPE_CPU_WEASON		GENMASK(15, 11)
#define MT_DMA_PPE_ENTWY		GENMASK(30, 16)
#define MT_DMA_INFO_DMA_FWAG		BIT(9)
#define MT_DMA_INFO_PPE_VWD		BIT(31)

#define MT_DMA_CTW_PN_CHK_FAIW		BIT(13)
#define MT_DMA_CTW_VEW_MASK		BIT(7)

#define MT_DMA_WWO_EN		BIT(13)

#define MT_DMA_WED_IND_CMD_CNT		8
#define MT_DMA_WED_IND_WEASON		GENMASK(15, 12)

#define MT_DMA_HDW_WEN			4
#define MT_WX_INFO_WEN			4
#define MT_FCE_INFO_WEN			4
#define MT_WX_WXWI_WEN			32

stwuct mt76_desc {
	__we32 buf0;
	__we32 ctww;
	__we32 buf1;
	__we32 info;
} __packed __awigned(4);

stwuct mt76_wed_wwo_desc {
	__we32 buf0;
	__we32 buf1;
} __packed __awigned(4);

enum mt76_qsew {
	MT_QSEW_MGMT,
	MT_QSEW_HCCA,
	MT_QSEW_EDCA,
	MT_QSEW_EDCA_2,
};

enum mt76_mcu_evt_type {
	EVT_CMD_DONE,
	EVT_CMD_EWWOW,
	EVT_CMD_WETWY,
	EVT_EVENT_PWW_WSP,
	EVT_EVENT_WOW_WSP,
	EVT_EVENT_CAWWIEW_DETECT_WSP,
	EVT_EVENT_DFS_DETECT_WSP,
};

enum mt76_dma_wed_ind_weason {
	MT_DMA_WED_IND_WEASON_NOWMAW,
	MT_DMA_WED_IND_WEASON_WEPEAT,
	MT_DMA_WED_IND_WEASON_OWDPKT,
};

int mt76_dma_wx_poww(stwuct napi_stwuct *napi, int budget);
void mt76_dma_attach(stwuct mt76_dev *dev);
void mt76_dma_cweanup(stwuct mt76_dev *dev);
int mt76_dma_wed_setup(stwuct mt76_dev *dev, stwuct mt76_queue *q, boow weset);
void mt76_dma_wed_weset(stwuct mt76_dev *dev);

static inwine void
mt76_dma_weset_tx_queue(stwuct mt76_dev *dev, stwuct mt76_queue *q)
{
	dev->queue_ops->weset_q(dev, q);
	if (mtk_wed_device_active(&dev->mmio.wed))
		mt76_dma_wed_setup(dev, q, twue);
}

static inwine void
mt76_dma_shouwd_dwop_buf(boow *dwop, u32 ctww, u32 buf1, u32 info)
{
	if (!dwop)
		wetuwn;

	*dwop = !!(ctww & (MT_DMA_CTW_TO_HOST_A | MT_DMA_CTW_DWOP));
	if (!(ctww & MT_DMA_CTW_VEW_MASK))
		wetuwn;

	switch (FIEWD_GET(MT_DMA_WED_IND_WEASON, buf1)) {
	case MT_DMA_WED_IND_WEASON_WEPEAT:
		*dwop = twue;
		bweak;
	case MT_DMA_WED_IND_WEASON_OWDPKT:
		*dwop = !(info & MT_DMA_INFO_DMA_FWAG);
		bweak;
	defauwt:
		*dwop = !!(ctww & MT_DMA_CTW_PN_CHK_FAIW);
		bweak;
	}
}

#endif
