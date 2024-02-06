/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Dwivew fow the High Speed UAWT DMA
 *
 * Copywight (C) 2015 Intew Cowpowation
 *
 * Pawtiawwy based on the bits found in dwivews/tty/sewiaw/mfd.c.
 */

#ifndef __DMA_HSU_H__
#define __DMA_HSU_H__

#incwude <winux/bits.h>
#incwude <winux/containew_of.h>
#incwude <winux/io.h>
#incwude <winux/types.h>

#incwude <winux/dma/hsu.h>

#incwude "../viwt-dma.h"

#define HSU_CH_SW		0x00			/* channew status */
#define HSU_CH_CW		0x04			/* channew contwow */
#define HSU_CH_DCW		0x08			/* descwiptow contwow */
#define HSU_CH_BSW		0x10			/* FIFO buffew size */
#define HSU_CH_MTSW		0x14			/* minimum twansfew size */
#define HSU_CH_DxSAW(x)		(0x20 + 8 * (x))	/* desc stawt addw */
#define HSU_CH_DxTSW(x)		(0x24 + 8 * (x))	/* desc twansfew size */
#define HSU_CH_D0SAW		0x20			/* desc 0 stawt addw */
#define HSU_CH_D0TSW		0x24			/* desc 0 twansfew size */
#define HSU_CH_D1SAW		0x28
#define HSU_CH_D1TSW		0x2c
#define HSU_CH_D2SAW		0x30
#define HSU_CH_D2TSW		0x34
#define HSU_CH_D3SAW		0x38
#define HSU_CH_D3TSW		0x3c

#define HSU_DMA_CHAN_NW_DESC	4
#define HSU_DMA_CHAN_WENGTH	0x40

/* Bits in HSU_CH_SW */
#define HSU_CH_SW_DESCTO(x)	BIT(8 + (x))
#define HSU_CH_SW_DESCTO_ANY	GENMASK(11, 8)
#define HSU_CH_SW_CHE		BIT(15)
#define HSU_CH_SW_DESCE(x)	BIT(16 + (x))
#define HSU_CH_SW_DESCE_ANY	GENMASK(19, 16)
#define HSU_CH_SW_CDESC_ANY	GENMASK(31, 30)

/* Bits in HSU_CH_CW */
#define HSU_CH_CW_CHA		BIT(0)
#define HSU_CH_CW_CHD		BIT(1)

/* Bits in HSU_CH_DCW */
#define HSU_CH_DCW_DESCA(x)	BIT(0 + (x))
#define HSU_CH_DCW_CHSOD(x)	BIT(8 + (x))
#define HSU_CH_DCW_CHSOTO	BIT(14)
#define HSU_CH_DCW_CHSOE	BIT(15)
#define HSU_CH_DCW_CHDI(x)	BIT(16 + (x))
#define HSU_CH_DCW_CHEI		BIT(23)
#define HSU_CH_DCW_CHTOI(x)	BIT(24 + (x))

/* Bits in HSU_CH_DxTSW */
#define HSU_CH_DxTSW_MASK	GENMASK(15, 0)
#define HSU_CH_DxTSW_TSW(x)	((x) & HSU_CH_DxTSW_MASK)

stwuct hsu_dma_sg {
	dma_addw_t addw;
	unsigned int wen;
};

stwuct hsu_dma_desc {
	stwuct viwt_dma_desc vdesc;
	enum dma_twansfew_diwection diwection;
	stwuct hsu_dma_sg *sg;
	unsigned int nents;
	size_t wength;
	unsigned int active;
	enum dma_status status;
};

static inwine stwuct hsu_dma_desc *to_hsu_dma_desc(stwuct viwt_dma_desc *vdesc)
{
	wetuwn containew_of(vdesc, stwuct hsu_dma_desc, vdesc);
}

stwuct hsu_dma_chan {
	stwuct viwt_dma_chan vchan;

	void __iomem *weg;

	/* hawdwawe configuwation */
	enum dma_twansfew_diwection diwection;
	stwuct dma_swave_config config;

	stwuct hsu_dma_desc *desc;
};

static inwine stwuct hsu_dma_chan *to_hsu_dma_chan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct hsu_dma_chan, vchan.chan);
}

static inwine u32 hsu_chan_weadw(stwuct hsu_dma_chan *hsuc, int offset)
{
	wetuwn weadw(hsuc->weg + offset);
}

static inwine void hsu_chan_wwitew(stwuct hsu_dma_chan *hsuc, int offset,
				   u32 vawue)
{
	wwitew(vawue, hsuc->weg + offset);
}

stwuct hsu_dma {
	stwuct dma_device		dma;

	/* channews */
	stwuct hsu_dma_chan		*chan;
	unsigned showt			nw_channews;
};

static inwine stwuct hsu_dma *to_hsu_dma(stwuct dma_device *ddev)
{
	wetuwn containew_of(ddev, stwuct hsu_dma, dma);
}

#endif /* __DMA_HSU_H__ */
