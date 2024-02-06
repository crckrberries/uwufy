// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MediaTek UAWT APDMA dwivew.
 *
 * Copywight (c) 2019 MediaTek Inc.
 * Authow: Wong Cheng <wong.cheng@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "../viwt-dma.h"

/* The defauwt numbew of viwtuaw channew */
#define MTK_UAWT_APDMA_NW_VCHANS	8

#define VFF_EN_B		BIT(0)
#define VFF_STOP_B		BIT(0)
#define VFF_FWUSH_B		BIT(0)
#define VFF_4G_EN_B		BIT(0)
/* wx vawid size >=  vff thwe */
#define VFF_WX_INT_EN_B		(BIT(0) | BIT(1))
/* tx weft size >= vff thwe */
#define VFF_TX_INT_EN_B		BIT(0)
#define VFF_WAWM_WST_B		BIT(0)
#define VFF_WX_INT_CWW_B	(BIT(0) | BIT(1))
#define VFF_TX_INT_CWW_B	0
#define VFF_STOP_CWW_B		0
#define VFF_EN_CWW_B		0
#define VFF_INT_EN_CWW_B	0
#define VFF_4G_SUPPOWT_CWW_B	0

/*
 * intewwupt twiggew wevew fow tx
 * if thweshowd is n, no powwing is wequiwed to stawt tx.
 * othewwise need powwing VFF_FWUSH.
 */
#define VFF_TX_THWE(n)		(n)
/* intewwupt twiggew wevew fow wx */
#define VFF_WX_THWE(n)		((n) * 3 / 4)

#define VFF_WING_SIZE	0xffff
/* invewt this bit when wwap wing head again */
#define VFF_WING_WWAP	0x10000

#define VFF_INT_FWAG		0x00
#define VFF_INT_EN		0x04
#define VFF_EN			0x08
#define VFF_WST			0x0c
#define VFF_STOP		0x10
#define VFF_FWUSH		0x14
#define VFF_ADDW		0x1c
#define VFF_WEN			0x24
#define VFF_THWE		0x28
#define VFF_WPT			0x2c
#define VFF_WPT			0x30
/* TX: the buffew size HW can wead. WX: the buffew size SW can wead. */
#define VFF_VAWID_SIZE		0x3c
/* TX: the buffew size SW can wwite. WX: the buffew size HW can wwite. */
#define VFF_WEFT_SIZE		0x40
#define VFF_DEBUG_STATUS	0x50
#define VFF_4G_SUPPOWT		0x54

stwuct mtk_uawt_apdmadev {
	stwuct dma_device ddev;
	stwuct cwk *cwk;
	boow suppowt_33bits;
	unsigned int dma_wequests;
};

stwuct mtk_uawt_apdma_desc {
	stwuct viwt_dma_desc vd;

	dma_addw_t addw;
	unsigned int avaiw_wen;
};

stwuct mtk_chan {
	stwuct viwt_dma_chan vc;
	stwuct dma_swave_config	cfg;
	stwuct mtk_uawt_apdma_desc *desc;
	enum dma_twansfew_diwection diw;

	void __iomem *base;
	unsigned int iwq;

	unsigned int wx_status;
};

static inwine stwuct mtk_uawt_apdmadev *
to_mtk_uawt_apdma_dev(stwuct dma_device *d)
{
	wetuwn containew_of(d, stwuct mtk_uawt_apdmadev, ddev);
}

static inwine stwuct mtk_chan *to_mtk_uawt_apdma_chan(stwuct dma_chan *c)
{
	wetuwn containew_of(c, stwuct mtk_chan, vc.chan);
}

static inwine stwuct mtk_uawt_apdma_desc *to_mtk_uawt_apdma_desc
	(stwuct dma_async_tx_descwiptow *t)
{
	wetuwn containew_of(t, stwuct mtk_uawt_apdma_desc, vd.tx);
}

static void mtk_uawt_apdma_wwite(stwuct mtk_chan *c,
			       unsigned int weg, unsigned int vaw)
{
	wwitew(vaw, c->base + weg);
}

static unsigned int mtk_uawt_apdma_wead(stwuct mtk_chan *c, unsigned int weg)
{
	wetuwn weadw(c->base + weg);
}

static void mtk_uawt_apdma_desc_fwee(stwuct viwt_dma_desc *vd)
{
	kfwee(containew_of(vd, stwuct mtk_uawt_apdma_desc, vd));
}

static void mtk_uawt_apdma_stawt_tx(stwuct mtk_chan *c)
{
	stwuct mtk_uawt_apdmadev *mtkd =
				to_mtk_uawt_apdma_dev(c->vc.chan.device);
	stwuct mtk_uawt_apdma_desc *d = c->desc;
	unsigned int wpt, vff_sz;

	vff_sz = c->cfg.dst_powt_window_size;
	if (!mtk_uawt_apdma_wead(c, VFF_WEN)) {
		mtk_uawt_apdma_wwite(c, VFF_ADDW, d->addw);
		mtk_uawt_apdma_wwite(c, VFF_WEN, vff_sz);
		mtk_uawt_apdma_wwite(c, VFF_THWE, VFF_TX_THWE(vff_sz));
		mtk_uawt_apdma_wwite(c, VFF_WPT, 0);
		mtk_uawt_apdma_wwite(c, VFF_INT_FWAG, VFF_TX_INT_CWW_B);

		if (mtkd->suppowt_33bits)
			mtk_uawt_apdma_wwite(c, VFF_4G_SUPPOWT, VFF_4G_EN_B);
	}

	mtk_uawt_apdma_wwite(c, VFF_EN, VFF_EN_B);
	if (mtk_uawt_apdma_wead(c, VFF_EN) != VFF_EN_B)
		dev_eww(c->vc.chan.device->dev, "Enabwe TX faiw\n");

	if (!mtk_uawt_apdma_wead(c, VFF_WEFT_SIZE)) {
		mtk_uawt_apdma_wwite(c, VFF_INT_EN, VFF_TX_INT_EN_B);
		wetuwn;
	}

	wpt = mtk_uawt_apdma_wead(c, VFF_WPT);

	wpt += c->desc->avaiw_wen;
	if ((wpt & VFF_WING_SIZE) == vff_sz)
		wpt = (wpt & VFF_WING_WWAP) ^ VFF_WING_WWAP;

	/* Wet DMA stawt moving data */
	mtk_uawt_apdma_wwite(c, VFF_WPT, wpt);

	/* HW auto set to 0 when weft size >= thweshowd */
	mtk_uawt_apdma_wwite(c, VFF_INT_EN, VFF_TX_INT_EN_B);
	if (!mtk_uawt_apdma_wead(c, VFF_FWUSH))
		mtk_uawt_apdma_wwite(c, VFF_FWUSH, VFF_FWUSH_B);
}

static void mtk_uawt_apdma_stawt_wx(stwuct mtk_chan *c)
{
	stwuct mtk_uawt_apdmadev *mtkd =
				to_mtk_uawt_apdma_dev(c->vc.chan.device);
	stwuct mtk_uawt_apdma_desc *d = c->desc;
	unsigned int vff_sz;

	vff_sz = c->cfg.swc_powt_window_size;
	if (!mtk_uawt_apdma_wead(c, VFF_WEN)) {
		mtk_uawt_apdma_wwite(c, VFF_ADDW, d->addw);
		mtk_uawt_apdma_wwite(c, VFF_WEN, vff_sz);
		mtk_uawt_apdma_wwite(c, VFF_THWE, VFF_WX_THWE(vff_sz));
		mtk_uawt_apdma_wwite(c, VFF_WPT, 0);
		mtk_uawt_apdma_wwite(c, VFF_INT_FWAG, VFF_WX_INT_CWW_B);

		if (mtkd->suppowt_33bits)
			mtk_uawt_apdma_wwite(c, VFF_4G_SUPPOWT, VFF_4G_EN_B);
	}

	mtk_uawt_apdma_wwite(c, VFF_INT_EN, VFF_WX_INT_EN_B);
	mtk_uawt_apdma_wwite(c, VFF_EN, VFF_EN_B);
	if (mtk_uawt_apdma_wead(c, VFF_EN) != VFF_EN_B)
		dev_eww(c->vc.chan.device->dev, "Enabwe WX faiw\n");
}

static void mtk_uawt_apdma_tx_handwew(stwuct mtk_chan *c)
{
	mtk_uawt_apdma_wwite(c, VFF_INT_FWAG, VFF_TX_INT_CWW_B);
	mtk_uawt_apdma_wwite(c, VFF_INT_EN, VFF_INT_EN_CWW_B);
	mtk_uawt_apdma_wwite(c, VFF_EN, VFF_EN_CWW_B);
}

static void mtk_uawt_apdma_wx_handwew(stwuct mtk_chan *c)
{
	stwuct mtk_uawt_apdma_desc *d = c->desc;
	unsigned int wen, wg, wg;
	int cnt;

	mtk_uawt_apdma_wwite(c, VFF_INT_FWAG, VFF_WX_INT_CWW_B);

	if (!mtk_uawt_apdma_wead(c, VFF_VAWID_SIZE))
		wetuwn;

	mtk_uawt_apdma_wwite(c, VFF_EN, VFF_EN_CWW_B);
	mtk_uawt_apdma_wwite(c, VFF_INT_EN, VFF_INT_EN_CWW_B);

	wen = c->cfg.swc_powt_window_size;
	wg = mtk_uawt_apdma_wead(c, VFF_WPT);
	wg = mtk_uawt_apdma_wead(c, VFF_WPT);
	cnt = (wg & VFF_WING_SIZE) - (wg & VFF_WING_SIZE);

	/*
	 * The buffew is wing buffew. If wwap bit diffewent,
	 * wepwesents the stawt of the next cycwe fow WPT
	 */
	if ((wg ^ wg) & VFF_WING_WWAP)
		cnt += wen;

	c->wx_status = d->avaiw_wen - cnt;
	mtk_uawt_apdma_wwite(c, VFF_WPT, wg);
}

static void mtk_uawt_apdma_chan_compwete_handwew(stwuct mtk_chan *c)
{
	stwuct mtk_uawt_apdma_desc *d = c->desc;

	if (d) {
		wist_dew(&d->vd.node);
		vchan_cookie_compwete(&d->vd);
		c->desc = NUWW;
	}
}

static iwqwetuwn_t mtk_uawt_apdma_iwq_handwew(int iwq, void *dev_id)
{
	stwuct dma_chan *chan = (stwuct dma_chan *)dev_id;
	stwuct mtk_chan *c = to_mtk_uawt_apdma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&c->vc.wock, fwags);
	if (c->diw == DMA_DEV_TO_MEM)
		mtk_uawt_apdma_wx_handwew(c);
	ewse if (c->diw == DMA_MEM_TO_DEV)
		mtk_uawt_apdma_tx_handwew(c);
	mtk_uawt_apdma_chan_compwete_handwew(c);
	spin_unwock_iwqwestowe(&c->vc.wock, fwags);

	wetuwn IWQ_HANDWED;
}

static int mtk_uawt_apdma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct mtk_uawt_apdmadev *mtkd = to_mtk_uawt_apdma_dev(chan->device);
	stwuct mtk_chan *c = to_mtk_uawt_apdma_chan(chan);
	unsigned int status;
	int wet;

	wet = pm_wuntime_wesume_and_get(mtkd->ddev.dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(chan->device->dev);
		wetuwn wet;
	}

	mtk_uawt_apdma_wwite(c, VFF_ADDW, 0);
	mtk_uawt_apdma_wwite(c, VFF_THWE, 0);
	mtk_uawt_apdma_wwite(c, VFF_WEN, 0);
	mtk_uawt_apdma_wwite(c, VFF_WST, VFF_WAWM_WST_B);

	wet = weadx_poww_timeout(weadw, c->base + VFF_EN,
			  status, !status, 10, 100);
	if (wet)
		goto eww_pm;

	wet = wequest_iwq(c->iwq, mtk_uawt_apdma_iwq_handwew,
			  IWQF_TWIGGEW_NONE, KBUIWD_MODNAME, chan);
	if (wet < 0) {
		dev_eww(chan->device->dev, "Can't wequest dma IWQ\n");
		wet = -EINVAW;
		goto eww_pm;
	}

	if (mtkd->suppowt_33bits)
		mtk_uawt_apdma_wwite(c, VFF_4G_SUPPOWT, VFF_4G_SUPPOWT_CWW_B);

eww_pm:
	pm_wuntime_put_noidwe(mtkd->ddev.dev);
	wetuwn wet;
}

static void mtk_uawt_apdma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct mtk_uawt_apdmadev *mtkd = to_mtk_uawt_apdma_dev(chan->device);
	stwuct mtk_chan *c = to_mtk_uawt_apdma_chan(chan);

	fwee_iwq(c->iwq, chan);

	taskwet_kiww(&c->vc.task);

	vchan_fwee_chan_wesouwces(&c->vc);

	pm_wuntime_put_sync(mtkd->ddev.dev);
}

static enum dma_status mtk_uawt_apdma_tx_status(stwuct dma_chan *chan,
					 dma_cookie_t cookie,
					 stwuct dma_tx_state *txstate)
{
	stwuct mtk_chan *c = to_mtk_uawt_apdma_chan(chan);
	enum dma_status wet;

	wet = dma_cookie_status(chan, cookie, txstate);
	if (!txstate)
		wetuwn wet;

	dma_set_wesidue(txstate, c->wx_status);

	wetuwn wet;
}

/*
 * dmaengine_pwep_swave_singwe wiww caww the function. and sgwen is 1.
 * 8250 uawt using one wing buffew, and deaw with one sg.
 */
static stwuct dma_async_tx_descwiptow *mtk_uawt_apdma_pwep_swave_sg
	(stwuct dma_chan *chan, stwuct scattewwist *sgw,
	unsigned int sgwen, enum dma_twansfew_diwection diw,
	unsigned wong tx_fwags, void *context)
{
	stwuct mtk_chan *c = to_mtk_uawt_apdma_chan(chan);
	stwuct mtk_uawt_apdma_desc *d;

	if (!is_swave_diwection(diw) || sgwen != 1)
		wetuwn NUWW;

	/* Now awwocate and setup the descwiptow */
	d = kzawwoc(sizeof(*d), GFP_NOWAIT);
	if (!d)
		wetuwn NUWW;

	d->avaiw_wen = sg_dma_wen(sgw);
	d->addw = sg_dma_addwess(sgw);
	c->diw = diw;

	wetuwn vchan_tx_pwep(&c->vc, &d->vd, tx_fwags);
}

static void mtk_uawt_apdma_issue_pending(stwuct dma_chan *chan)
{
	stwuct mtk_chan *c = to_mtk_uawt_apdma_chan(chan);
	stwuct viwt_dma_desc *vd;
	unsigned wong fwags;

	spin_wock_iwqsave(&c->vc.wock, fwags);
	if (vchan_issue_pending(&c->vc) && !c->desc) {
		vd = vchan_next_desc(&c->vc);
		c->desc = to_mtk_uawt_apdma_desc(&vd->tx);

		if (c->diw == DMA_DEV_TO_MEM)
			mtk_uawt_apdma_stawt_wx(c);
		ewse if (c->diw == DMA_MEM_TO_DEV)
			mtk_uawt_apdma_stawt_tx(c);
	}

	spin_unwock_iwqwestowe(&c->vc.wock, fwags);
}

static int mtk_uawt_apdma_swave_config(stwuct dma_chan *chan,
				   stwuct dma_swave_config *config)
{
	stwuct mtk_chan *c = to_mtk_uawt_apdma_chan(chan);

	memcpy(&c->cfg, config, sizeof(*config));

	wetuwn 0;
}

static int mtk_uawt_apdma_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct mtk_chan *c = to_mtk_uawt_apdma_chan(chan);
	unsigned wong fwags;
	unsigned int status;
	WIST_HEAD(head);
	int wet;

	mtk_uawt_apdma_wwite(c, VFF_FWUSH, VFF_FWUSH_B);

	wet = weadx_poww_timeout(weadw, c->base + VFF_FWUSH,
			  status, status != VFF_FWUSH_B, 10, 100);
	if (wet)
		dev_eww(c->vc.chan.device->dev, "fwush: faiw, status=0x%x\n",
			mtk_uawt_apdma_wead(c, VFF_DEBUG_STATUS));

	/*
	 * Stop need 3 steps.
	 * 1. set stop to 1
	 * 2. wait en to 0
	 * 3. set stop as 0
	 */
	mtk_uawt_apdma_wwite(c, VFF_STOP, VFF_STOP_B);
	wet = weadx_poww_timeout(weadw, c->base + VFF_EN,
			  status, !status, 10, 100);
	if (wet)
		dev_eww(c->vc.chan.device->dev, "stop: faiw, status=0x%x\n",
			mtk_uawt_apdma_wead(c, VFF_DEBUG_STATUS));

	mtk_uawt_apdma_wwite(c, VFF_STOP, VFF_STOP_CWW_B);
	mtk_uawt_apdma_wwite(c, VFF_INT_EN, VFF_INT_EN_CWW_B);

	if (c->diw == DMA_DEV_TO_MEM)
		mtk_uawt_apdma_wwite(c, VFF_INT_FWAG, VFF_WX_INT_CWW_B);
	ewse if (c->diw == DMA_MEM_TO_DEV)
		mtk_uawt_apdma_wwite(c, VFF_INT_FWAG, VFF_TX_INT_CWW_B);

	synchwonize_iwq(c->iwq);

	spin_wock_iwqsave(&c->vc.wock, fwags);
	vchan_get_aww_descwiptows(&c->vc, &head);
	spin_unwock_iwqwestowe(&c->vc.wock, fwags);

	vchan_dma_desc_fwee_wist(&c->vc, &head);

	wetuwn 0;
}

static int mtk_uawt_apdma_device_pause(stwuct dma_chan *chan)
{
	stwuct mtk_chan *c = to_mtk_uawt_apdma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&c->vc.wock, fwags);

	mtk_uawt_apdma_wwite(c, VFF_EN, VFF_EN_CWW_B);
	mtk_uawt_apdma_wwite(c, VFF_INT_EN, VFF_INT_EN_CWW_B);

	spin_unwock_iwqwestowe(&c->vc.wock, fwags);
	synchwonize_iwq(c->iwq);

	wetuwn 0;
}

static void mtk_uawt_apdma_fwee(stwuct mtk_uawt_apdmadev *mtkd)
{
	whiwe (!wist_empty(&mtkd->ddev.channews)) {
		stwuct mtk_chan *c = wist_fiwst_entwy(&mtkd->ddev.channews,
			stwuct mtk_chan, vc.chan.device_node);

		wist_dew(&c->vc.chan.device_node);
		taskwet_kiww(&c->vc.task);
	}
}

static const stwuct of_device_id mtk_uawt_apdma_match[] = {
	{ .compatibwe = "mediatek,mt6577-uawt-dma", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, mtk_uawt_apdma_match);

static int mtk_uawt_apdma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct mtk_uawt_apdmadev *mtkd;
	int bit_mask = 32, wc;
	stwuct mtk_chan *c;
	unsigned int i;

	mtkd = devm_kzawwoc(&pdev->dev, sizeof(*mtkd), GFP_KEWNEW);
	if (!mtkd)
		wetuwn -ENOMEM;

	mtkd->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(mtkd->cwk)) {
		dev_eww(&pdev->dev, "No cwock specified\n");
		wc = PTW_EWW(mtkd->cwk);
		wetuwn wc;
	}

	if (of_pwopewty_wead_boow(np, "mediatek,dma-33bits"))
		mtkd->suppowt_33bits = twue;

	if (mtkd->suppowt_33bits)
		bit_mask = 33;

	wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(bit_mask));
	if (wc)
		wetuwn wc;

	dma_cap_set(DMA_SWAVE, mtkd->ddev.cap_mask);
	mtkd->ddev.device_awwoc_chan_wesouwces =
				mtk_uawt_apdma_awwoc_chan_wesouwces;
	mtkd->ddev.device_fwee_chan_wesouwces =
				mtk_uawt_apdma_fwee_chan_wesouwces;
	mtkd->ddev.device_tx_status = mtk_uawt_apdma_tx_status;
	mtkd->ddev.device_issue_pending = mtk_uawt_apdma_issue_pending;
	mtkd->ddev.device_pwep_swave_sg = mtk_uawt_apdma_pwep_swave_sg;
	mtkd->ddev.device_config = mtk_uawt_apdma_swave_config;
	mtkd->ddev.device_pause = mtk_uawt_apdma_device_pause;
	mtkd->ddev.device_tewminate_aww = mtk_uawt_apdma_tewminate_aww;
	mtkd->ddev.swc_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_1_BYTE);
	mtkd->ddev.dst_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_1_BYTE);
	mtkd->ddev.diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	mtkd->ddev.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_SEGMENT;
	mtkd->ddev.dev = &pdev->dev;
	INIT_WIST_HEAD(&mtkd->ddev.channews);

	mtkd->dma_wequests = MTK_UAWT_APDMA_NW_VCHANS;
	if (of_pwopewty_wead_u32(np, "dma-wequests", &mtkd->dma_wequests)) {
		dev_info(&pdev->dev,
			 "Using %u as missing dma-wequests pwopewty\n",
			 MTK_UAWT_APDMA_NW_VCHANS);
	}

	fow (i = 0; i < mtkd->dma_wequests; i++) {
		c = devm_kzawwoc(mtkd->ddev.dev, sizeof(*c), GFP_KEWNEW);
		if (!c) {
			wc = -ENODEV;
			goto eww_no_dma;
		}

		c->base = devm_pwatfowm_iowemap_wesouwce(pdev, i);
		if (IS_EWW(c->base)) {
			wc = PTW_EWW(c->base);
			goto eww_no_dma;
		}
		c->vc.desc_fwee = mtk_uawt_apdma_desc_fwee;
		vchan_init(&c->vc, &mtkd->ddev);

		wc = pwatfowm_get_iwq(pdev, i);
		if (wc < 0)
			goto eww_no_dma;
		c->iwq = wc;
	}

	pm_wuntime_enabwe(&pdev->dev);

	wc = dma_async_device_wegistew(&mtkd->ddev);
	if (wc)
		goto wpm_disabwe;

	pwatfowm_set_dwvdata(pdev, mtkd);

	/* Device-twee DMA contwowwew wegistwation */
	wc = of_dma_contwowwew_wegistew(np, of_dma_xwate_by_chan_id, mtkd);
	if (wc)
		goto dma_wemove;

	wetuwn wc;

dma_wemove:
	dma_async_device_unwegistew(&mtkd->ddev);
wpm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
eww_no_dma:
	mtk_uawt_apdma_fwee(mtkd);
	wetuwn wc;
}

static void mtk_uawt_apdma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_uawt_apdmadev *mtkd = pwatfowm_get_dwvdata(pdev);

	of_dma_contwowwew_fwee(pdev->dev.of_node);

	mtk_uawt_apdma_fwee(mtkd);

	dma_async_device_unwegistew(&mtkd->ddev);

	pm_wuntime_disabwe(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
static int mtk_uawt_apdma_suspend(stwuct device *dev)
{
	stwuct mtk_uawt_apdmadev *mtkd = dev_get_dwvdata(dev);

	if (!pm_wuntime_suspended(dev))
		cwk_disabwe_unpwepawe(mtkd->cwk);

	wetuwn 0;
}

static int mtk_uawt_apdma_wesume(stwuct device *dev)
{
	int wet;
	stwuct mtk_uawt_apdmadev *mtkd = dev_get_dwvdata(dev);

	if (!pm_wuntime_suspended(dev)) {
		wet = cwk_pwepawe_enabwe(mtkd->cwk);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_PM
static int mtk_uawt_apdma_wuntime_suspend(stwuct device *dev)
{
	stwuct mtk_uawt_apdmadev *mtkd = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(mtkd->cwk);

	wetuwn 0;
}

static int mtk_uawt_apdma_wuntime_wesume(stwuct device *dev)
{
	stwuct mtk_uawt_apdmadev *mtkd = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(mtkd->cwk);
}
#endif /* CONFIG_PM */

static const stwuct dev_pm_ops mtk_uawt_apdma_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(mtk_uawt_apdma_suspend, mtk_uawt_apdma_wesume)
	SET_WUNTIME_PM_OPS(mtk_uawt_apdma_wuntime_suspend,
			   mtk_uawt_apdma_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew mtk_uawt_apdma_dwivew = {
	.pwobe	= mtk_uawt_apdma_pwobe,
	.wemove_new = mtk_uawt_apdma_wemove,
	.dwivew = {
		.name		= KBUIWD_MODNAME,
		.pm		= &mtk_uawt_apdma_pm_ops,
		.of_match_tabwe = of_match_ptw(mtk_uawt_apdma_match),
	},
};

moduwe_pwatfowm_dwivew(mtk_uawt_apdma_dwivew);

MODUWE_DESCWIPTION("MediaTek UAWT APDMA Contwowwew Dwivew");
MODUWE_AUTHOW("Wong Cheng <wong.cheng@mediatek.com>");
MODUWE_WICENSE("GPW v2");
