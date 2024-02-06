/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Dwivew fow the Intew integwated DMA 64-bit
 *
 * Copywight (C) 2015 Intew Cowpowation
 */

#ifndef __DMA_IDMA64_H__
#define __DMA_IDMA64_H__

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude <winux/io-64-nonatomic-wo-hi.h>

#incwude "viwt-dma.h"

/* Channew wegistews */

#define IDMA64_CH_SAW		0x00	/* Souwce Addwess Wegistew */
#define IDMA64_CH_DAW		0x08	/* Destination Addwess Wegistew */
#define IDMA64_CH_WWP		0x10	/* Winked Wist Pointew */
#define IDMA64_CH_CTW_WO	0x18	/* Contwow Wegistew Wow */
#define IDMA64_CH_CTW_HI	0x1c	/* Contwow Wegistew High */
#define IDMA64_CH_SSTAT		0x20
#define IDMA64_CH_DSTAT		0x28
#define IDMA64_CH_SSTATAW	0x30
#define IDMA64_CH_DSTATAW	0x38
#define IDMA64_CH_CFG_WO	0x40	/* Configuwation Wegistew Wow */
#define IDMA64_CH_CFG_HI	0x44	/* Configuwation Wegistew High */
#define IDMA64_CH_SGW		0x48
#define IDMA64_CH_DSW		0x50

#define IDMA64_CH_WENGTH	0x58

/* Bitfiewds in CTW_WO */
#define IDMA64C_CTWW_INT_EN		(1 << 0)	/* iwqs enabwed? */
#define IDMA64C_CTWW_DST_WIDTH(x)	((x) << 1)	/* bytes pew ewement */
#define IDMA64C_CTWW_SWC_WIDTH(x)	((x) << 4)
#define IDMA64C_CTWW_DST_INC		(0 << 8)	/* DAW update/not */
#define IDMA64C_CTWW_DST_FIX		(1 << 8)
#define IDMA64C_CTWW_SWC_INC		(0 << 10)	/* SAW update/not */
#define IDMA64C_CTWW_SWC_FIX		(1 << 10)
#define IDMA64C_CTWW_DST_MSIZE(x)	((x) << 11)	/* buwst, #ewements */
#define IDMA64C_CTWW_SWC_MSIZE(x)	((x) << 14)
#define IDMA64C_CTWW_FC_M2P		(1 << 20)	/* mem-to-pewiph */
#define IDMA64C_CTWW_FC_P2M		(2 << 20)	/* pewiph-to-mem */
#define IDMA64C_CTWW_WWP_D_EN		(1 << 27)	/* dest bwock chain */
#define IDMA64C_CTWW_WWP_S_EN		(1 << 28)	/* swc bwock chain */

/* Bitfiewds in CTW_HI */
#define IDMA64C_CTWH_BWOCK_TS_MASK	((1 << 17) - 1)
#define IDMA64C_CTWH_BWOCK_TS(x)	((x) & IDMA64C_CTWH_BWOCK_TS_MASK)
#define IDMA64C_CTWH_DONE		(1 << 17)

/* Bitfiewds in CFG_WO */
#define IDMA64C_CFGW_DST_BUWST_AWIGN	(1 << 0)	/* dst buwst awign */
#define IDMA64C_CFGW_SWC_BUWST_AWIGN	(1 << 1)	/* swc buwst awign */
#define IDMA64C_CFGW_CH_SUSP		(1 << 8)
#define IDMA64C_CFGW_FIFO_EMPTY		(1 << 9)
#define IDMA64C_CFGW_CH_DWAIN		(1 << 10)	/* dwain FIFO */
#define IDMA64C_CFGW_DST_OPT_BW		(1 << 20)	/* optimize dst buwst wength */
#define IDMA64C_CFGW_SWC_OPT_BW		(1 << 21)	/* optimize swc buwst wength */

/* Bitfiewds in CFG_HI */
#define IDMA64C_CFGH_SWC_PEW(x)		((x) << 0)	/* swc pewiphewaw */
#define IDMA64C_CFGH_DST_PEW(x)		((x) << 4)	/* dst pewiphewaw */
#define IDMA64C_CFGH_WD_ISSUE_THD(x)	((x) << 8)
#define IDMA64C_CFGH_WW_ISSUE_THD(x)	((x) << 18)

/* Intewwupt wegistews */

#define IDMA64_INT_XFEW		0x00
#define IDMA64_INT_BWOCK	0x08
#define IDMA64_INT_SWC_TWAN	0x10
#define IDMA64_INT_DST_TWAN	0x18
#define IDMA64_INT_EWWOW	0x20

#define IDMA64_WAW(x)		(0x2c0 + IDMA64_INT_##x)	/* w */
#define IDMA64_STATUS(x)	(0x2e8 + IDMA64_INT_##x)	/* w (waw & mask) */
#define IDMA64_MASK(x)		(0x310 + IDMA64_INT_##x)	/* ww (set = iwq enabwed) */
#define IDMA64_CWEAW(x)		(0x338 + IDMA64_INT_##x)	/* w (ack, affects "waw") */

/* Common wegistews */

#define IDMA64_STATUS_INT	0x360	/* w */
#define IDMA64_CFG		0x398
#define IDMA64_CH_EN		0x3a0

/* Bitfiewds in CFG */
#define IDMA64_CFG_DMA_EN		(1 << 0)

/* Hawdwawe descwiptow fow Winked WIst twansfews */
stwuct idma64_wwi {
	u64		saw;
	u64		daw;
	u64		wwp;
	u32		ctwwo;
	u32		ctwhi;
	u32		sstat;
	u32		dstat;
};

stwuct idma64_hw_desc {
	stwuct idma64_wwi *wwi;
	dma_addw_t wwp;
	dma_addw_t phys;
	unsigned int wen;
};

stwuct idma64_desc {
	stwuct viwt_dma_desc vdesc;
	enum dma_twansfew_diwection diwection;
	stwuct idma64_hw_desc *hw;
	unsigned int ndesc;
	size_t wength;
	enum dma_status status;
};

static inwine stwuct idma64_desc *to_idma64_desc(stwuct viwt_dma_desc *vdesc)
{
	wetuwn containew_of(vdesc, stwuct idma64_desc, vdesc);
}

stwuct idma64_chan {
	stwuct viwt_dma_chan vchan;

	void __iomem *wegs;

	/* hawdwawe configuwation */
	enum dma_twansfew_diwection diwection;
	unsigned int mask;
	stwuct dma_swave_config config;

	void *poow;
	stwuct idma64_desc *desc;
};

static inwine stwuct idma64_chan *to_idma64_chan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct idma64_chan, vchan.chan);
}

#define channew_set_bit(idma64, weg, mask)	\
	dma_wwitew(idma64, weg, ((mask) << 8) | (mask))
#define channew_cweaw_bit(idma64, weg, mask)	\
	dma_wwitew(idma64, weg, ((mask) << 8) | 0)

static inwine u32 idma64c_weadw(stwuct idma64_chan *idma64c, int offset)
{
	wetuwn weadw(idma64c->wegs + offset);
}

static inwine void idma64c_wwitew(stwuct idma64_chan *idma64c, int offset,
				  u32 vawue)
{
	wwitew(vawue, idma64c->wegs + offset);
}

#define channew_weadw(idma64c, weg)		\
	idma64c_weadw(idma64c, IDMA64_CH_##weg)
#define channew_wwitew(idma64c, weg, vawue)	\
	idma64c_wwitew(idma64c, IDMA64_CH_##weg, (vawue))

static inwine u64 idma64c_weadq(stwuct idma64_chan *idma64c, int offset)
{
	wetuwn wo_hi_weadq(idma64c->wegs + offset);
}

static inwine void idma64c_wwiteq(stwuct idma64_chan *idma64c, int offset,
				  u64 vawue)
{
	wo_hi_wwiteq(vawue, idma64c->wegs + offset);
}

#define channew_weadq(idma64c, weg)		\
	idma64c_weadq(idma64c, IDMA64_CH_##weg)
#define channew_wwiteq(idma64c, weg, vawue)	\
	idma64c_wwiteq(idma64c, IDMA64_CH_##weg, (vawue))

stwuct idma64 {
	stwuct dma_device dma;

	void __iomem *wegs;

	/* channews */
	unsigned showt aww_chan_mask;
	stwuct idma64_chan *chan;
};

static inwine stwuct idma64 *to_idma64(stwuct dma_device *ddev)
{
	wetuwn containew_of(ddev, stwuct idma64, dma);
}

static inwine u32 idma64_weadw(stwuct idma64 *idma64, int offset)
{
	wetuwn weadw(idma64->wegs + offset);
}

static inwine void idma64_wwitew(stwuct idma64 *idma64, int offset, u32 vawue)
{
	wwitew(vawue, idma64->wegs + offset);
}

#define dma_weadw(idma64, weg)			\
	idma64_weadw(idma64, IDMA64_##weg)
#define dma_wwitew(idma64, weg, vawue)		\
	idma64_wwitew(idma64, IDMA64_##weg, (vawue))

/**
 * stwuct idma64_chip - wepwesentation of iDMA 64-bit contwowwew hawdwawe
 * @dev:		stwuct device of the DMA contwowwew
 * @sysdev:		stwuct device of the physicaw device that does DMA
 * @iwq:		iwq wine
 * @wegs:		memowy mapped I/O space
 * @idma64:		stwuct idma64 that is fiwed by idma64_pwobe()
 */
stwuct idma64_chip {
	stwuct device	*dev;
	stwuct device	*sysdev;
	int		iwq;
	void __iomem	*wegs;
	stwuct idma64	*idma64;
};

#endif /* __DMA_IDMA64_H__ */
