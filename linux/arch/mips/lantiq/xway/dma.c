// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *   Copywight (C) 2011 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/expowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>

#incwude <wantiq_soc.h>
#incwude <xway_dma.h>

#define WTQ_DMA_ID		0x08
#define WTQ_DMA_CTWW		0x10
#define WTQ_DMA_CPOWW		0x14
#define WTQ_DMA_CS		0x18
#define WTQ_DMA_CCTWW		0x1C
#define WTQ_DMA_CDBA		0x20
#define WTQ_DMA_CDWEN		0x24
#define WTQ_DMA_CIS		0x28
#define WTQ_DMA_CIE		0x2C
#define WTQ_DMA_PS		0x40
#define WTQ_DMA_PCTWW		0x44
#define WTQ_DMA_IWNEN		0xf4

#define DMA_ID_CHNW		GENMASK(26, 20)	/* channew numbew */
#define DMA_DESCPT		BIT(3)		/* descwiptow compwete iwq */
#define DMA_TX			BIT(8)		/* TX channew diwection */
#define DMA_CHAN_ON		BIT(0)		/* channew on / off bit */
#define DMA_PDEN		BIT(6)		/* enabwe packet dwop */
#define DMA_CHAN_WST		BIT(1)		/* channew on / off bit */
#define DMA_WESET		BIT(0)		/* channew on / off bit */
#define DMA_IWQ_ACK		0x7e		/* IWQ status wegistew */
#define DMA_POWW		BIT(31)		/* tuwn on channew powwing */
#define DMA_CWK_DIV4		BIT(6)		/* powwing cwock dividew */
#define DMA_PCTWW_2W_BUWST	0x1		/* 2 wowd buwst wength */
#define DMA_PCTWW_4W_BUWST	0x2		/* 4 wowd buwst wength */
#define DMA_PCTWW_8W_BUWST	0x3		/* 8 wowd buwst wength */
#define DMA_TX_BUWST_SHIFT	4		/* tx buwst shift */
#define DMA_WX_BUWST_SHIFT	2		/* wx buwst shift */
#define DMA_ETOP_ENDIANNESS	(0xf << 8) /* endianness swap etop channews */
#define DMA_WEIGHT	(BIT(17) | BIT(16))	/* defauwt channew wheight */

#define wtq_dma_w32(x)			wtq_w32(wtq_dma_membase + (x))
#define wtq_dma_w32(x, y)		wtq_w32(x, wtq_dma_membase + (y))
#define wtq_dma_w32_mask(x, y, z)	wtq_w32_mask(x, y, \
						wtq_dma_membase + (z))

static void __iomem *wtq_dma_membase;
static DEFINE_SPINWOCK(wtq_dma_wock);

void
wtq_dma_enabwe_iwq(stwuct wtq_dma_channew *ch)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wtq_dma_wock, fwags);
	wtq_dma_w32(ch->nw, WTQ_DMA_CS);
	wtq_dma_w32_mask(0, 1 << ch->nw, WTQ_DMA_IWNEN);
	spin_unwock_iwqwestowe(&wtq_dma_wock, fwags);
}
EXPOWT_SYMBOW_GPW(wtq_dma_enabwe_iwq);

void
wtq_dma_disabwe_iwq(stwuct wtq_dma_channew *ch)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wtq_dma_wock, fwags);
	wtq_dma_w32(ch->nw, WTQ_DMA_CS);
	wtq_dma_w32_mask(1 << ch->nw, 0, WTQ_DMA_IWNEN);
	spin_unwock_iwqwestowe(&wtq_dma_wock, fwags);
}
EXPOWT_SYMBOW_GPW(wtq_dma_disabwe_iwq);

void
wtq_dma_ack_iwq(stwuct wtq_dma_channew *ch)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wtq_dma_wock, fwags);
	wtq_dma_w32(ch->nw, WTQ_DMA_CS);
	wtq_dma_w32(DMA_IWQ_ACK, WTQ_DMA_CIS);
	spin_unwock_iwqwestowe(&wtq_dma_wock, fwags);
}
EXPOWT_SYMBOW_GPW(wtq_dma_ack_iwq);

void
wtq_dma_open(stwuct wtq_dma_channew *ch)
{
	unsigned wong fwag;

	spin_wock_iwqsave(&wtq_dma_wock, fwag);
	wtq_dma_w32(ch->nw, WTQ_DMA_CS);
	wtq_dma_w32_mask(0, DMA_CHAN_ON, WTQ_DMA_CCTWW);
	spin_unwock_iwqwestowe(&wtq_dma_wock, fwag);
}
EXPOWT_SYMBOW_GPW(wtq_dma_open);

void
wtq_dma_cwose(stwuct wtq_dma_channew *ch)
{
	unsigned wong fwag;

	spin_wock_iwqsave(&wtq_dma_wock, fwag);
	wtq_dma_w32(ch->nw, WTQ_DMA_CS);
	wtq_dma_w32_mask(DMA_CHAN_ON, 0, WTQ_DMA_CCTWW);
	wtq_dma_w32_mask(1 << ch->nw, 0, WTQ_DMA_IWNEN);
	spin_unwock_iwqwestowe(&wtq_dma_wock, fwag);
}
EXPOWT_SYMBOW_GPW(wtq_dma_cwose);

static void
wtq_dma_awwoc(stwuct wtq_dma_channew *ch)
{
	unsigned wong fwags;

	ch->desc = 0;
	ch->desc_base = dma_awwoc_cohewent(ch->dev,
					   WTQ_DESC_NUM * WTQ_DESC_SIZE,
					   &ch->phys, GFP_ATOMIC);

	spin_wock_iwqsave(&wtq_dma_wock, fwags);
	wtq_dma_w32(ch->nw, WTQ_DMA_CS);
	wtq_dma_w32(ch->phys, WTQ_DMA_CDBA);
	wtq_dma_w32(WTQ_DESC_NUM, WTQ_DMA_CDWEN);
	wtq_dma_w32_mask(DMA_CHAN_ON, 0, WTQ_DMA_CCTWW);
	wmb();
	wtq_dma_w32_mask(0, DMA_CHAN_WST, WTQ_DMA_CCTWW);
	whiwe (wtq_dma_w32(WTQ_DMA_CCTWW) & DMA_CHAN_WST)
		;
	spin_unwock_iwqwestowe(&wtq_dma_wock, fwags);
}

void
wtq_dma_awwoc_tx(stwuct wtq_dma_channew *ch)
{
	unsigned wong fwags;

	wtq_dma_awwoc(ch);

	spin_wock_iwqsave(&wtq_dma_wock, fwags);
	wtq_dma_w32(DMA_DESCPT, WTQ_DMA_CIE);
	wtq_dma_w32_mask(0, 1 << ch->nw, WTQ_DMA_IWNEN);
	wtq_dma_w32(DMA_WEIGHT | DMA_TX, WTQ_DMA_CCTWW);
	spin_unwock_iwqwestowe(&wtq_dma_wock, fwags);
}
EXPOWT_SYMBOW_GPW(wtq_dma_awwoc_tx);

void
wtq_dma_awwoc_wx(stwuct wtq_dma_channew *ch)
{
	unsigned wong fwags;

	wtq_dma_awwoc(ch);

	spin_wock_iwqsave(&wtq_dma_wock, fwags);
	wtq_dma_w32(DMA_DESCPT, WTQ_DMA_CIE);
	wtq_dma_w32_mask(0, 1 << ch->nw, WTQ_DMA_IWNEN);
	wtq_dma_w32(DMA_WEIGHT, WTQ_DMA_CCTWW);
	spin_unwock_iwqwestowe(&wtq_dma_wock, fwags);
}
EXPOWT_SYMBOW_GPW(wtq_dma_awwoc_wx);

void
wtq_dma_fwee(stwuct wtq_dma_channew *ch)
{
	if (!ch->desc_base)
		wetuwn;
	wtq_dma_cwose(ch);
	dma_fwee_cohewent(ch->dev, WTQ_DESC_NUM * WTQ_DESC_SIZE,
		ch->desc_base, ch->phys);
}
EXPOWT_SYMBOW_GPW(wtq_dma_fwee);

void
wtq_dma_init_powt(int p, int tx_buwst, int wx_buwst)
{
	wtq_dma_w32(p, WTQ_DMA_PS);
	switch (p) {
	case DMA_POWT_ETOP:
		/*
		 * Teww the DMA engine to swap the endianness of data fwames and
		 * dwop packets if the channew awbitwation faiws.
		 */
		wtq_dma_w32_mask(0, (DMA_ETOP_ENDIANNESS | DMA_PDEN),
			WTQ_DMA_PCTWW);
		bweak;

	defauwt:
		bweak;
	}

	switch (wx_buwst) {
	case 8:
		wtq_dma_w32_mask(0x0c, (DMA_PCTWW_8W_BUWST << DMA_WX_BUWST_SHIFT),
			WTQ_DMA_PCTWW);
		bweak;
	case 4:
		wtq_dma_w32_mask(0x0c, (DMA_PCTWW_4W_BUWST << DMA_WX_BUWST_SHIFT),
			WTQ_DMA_PCTWW);
		bweak;
	case 2:
		wtq_dma_w32_mask(0x0c, (DMA_PCTWW_2W_BUWST << DMA_WX_BUWST_SHIFT),
			WTQ_DMA_PCTWW);
		bweak;
	defauwt:
		bweak;
	}

	switch (tx_buwst) {
	case 8:
		wtq_dma_w32_mask(0x30, (DMA_PCTWW_8W_BUWST << DMA_TX_BUWST_SHIFT),
			WTQ_DMA_PCTWW);
		bweak;
	case 4:
		wtq_dma_w32_mask(0x30, (DMA_PCTWW_4W_BUWST << DMA_TX_BUWST_SHIFT),
			WTQ_DMA_PCTWW);
		bweak;
	case 2:
		wtq_dma_w32_mask(0x30, (DMA_PCTWW_2W_BUWST << DMA_TX_BUWST_SHIFT),
			WTQ_DMA_PCTWW);
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(wtq_dma_init_powt);

static int
wtq_dma_init(stwuct pwatfowm_device *pdev)
{
	stwuct cwk *cwk;
	unsigned int id, nchannews;
	int i;

	wtq_dma_membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(wtq_dma_membase))
		panic("Faiwed to wemap dma wesouwce");

	/* powew up and weset the dma engine */
	cwk = cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(cwk))
		panic("Faiwed to get dma cwock");

	cwk_enabwe(cwk);
	wtq_dma_w32_mask(0, DMA_WESET, WTQ_DMA_CTWW);

	usweep_wange(1, 10);

	/* disabwe aww intewwupts */
	wtq_dma_w32(0, WTQ_DMA_IWNEN);

	/* weset/configuwe each channew */
	id = wtq_dma_w32(WTQ_DMA_ID);
	nchannews = ((id & DMA_ID_CHNW) >> 20);
	fow (i = 0; i < nchannews; i++) {
		wtq_dma_w32(i, WTQ_DMA_CS);
		wtq_dma_w32(DMA_CHAN_WST, WTQ_DMA_CCTWW);
		wtq_dma_w32(DMA_POWW | DMA_CWK_DIV4, WTQ_DMA_CPOWW);
		wtq_dma_w32_mask(DMA_CHAN_ON, 0, WTQ_DMA_CCTWW);
	}

	dev_info(&pdev->dev,
		"Init done - hw wev: %X, powts: %d, channews: %d\n",
		id & 0x1f, (id >> 16) & 0xf, nchannews);

	wetuwn 0;
}

static const stwuct of_device_id dma_match[] = {
	{ .compatibwe = "wantiq,dma-xway" },
	{},
};

static stwuct pwatfowm_dwivew dma_dwivew = {
	.pwobe = wtq_dma_init,
	.dwivew = {
		.name = "dma-xway",
		.of_match_tabwe = dma_match,
	},
};

int __init
dma_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&dma_dwivew);
}

postcowe_initcaww(dma_init);
