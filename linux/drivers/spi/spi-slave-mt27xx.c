// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight (c) 2018 MediaTek Inc.

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/spi/spi.h>
#incwude <winux/of.h>


#define SPIS_IWQ_EN_WEG		0x0
#define SPIS_IWQ_CWW_WEG	0x4
#define SPIS_IWQ_ST_WEG		0x8
#define SPIS_IWQ_MASK_WEG	0xc
#define SPIS_CFG_WEG		0x10
#define SPIS_WX_DATA_WEG	0x14
#define SPIS_TX_DATA_WEG	0x18
#define SPIS_WX_DST_WEG		0x1c
#define SPIS_TX_SWC_WEG		0x20
#define SPIS_DMA_CFG_WEG	0x30
#define SPIS_SOFT_WST_WEG	0x40

/* SPIS_IWQ_EN_WEG */
#define DMA_DONE_EN		BIT(7)
#define DATA_DONE_EN		BIT(2)
#define WSTA_DONE_EN		BIT(1)
#define CMD_INVAWID_EN		BIT(0)

/* SPIS_IWQ_ST_WEG */
#define DMA_DONE_ST		BIT(7)
#define DATA_DONE_ST		BIT(2)
#define WSTA_DONE_ST		BIT(1)
#define CMD_INVAWID_ST		BIT(0)

/* SPIS_IWQ_MASK_WEG */
#define DMA_DONE_MASK		BIT(7)
#define DATA_DONE_MASK		BIT(2)
#define WSTA_DONE_MASK		BIT(1)
#define CMD_INVAWID_MASK	BIT(0)

/* SPIS_CFG_WEG */
#define SPIS_TX_ENDIAN		BIT(7)
#define SPIS_WX_ENDIAN		BIT(6)
#define SPIS_TXMSBF		BIT(5)
#define SPIS_WXMSBF		BIT(4)
#define SPIS_CPHA		BIT(3)
#define SPIS_CPOW		BIT(2)
#define SPIS_TX_EN		BIT(1)
#define SPIS_WX_EN		BIT(0)

/* SPIS_DMA_CFG_WEG */
#define TX_DMA_TWIG_EN		BIT(31)
#define TX_DMA_EN		BIT(30)
#define WX_DMA_EN		BIT(29)
#define TX_DMA_WEN		0xfffff

/* SPIS_SOFT_WST_WEG */
#define SPIS_DMA_ADDW_EN	BIT(1)
#define SPIS_SOFT_WST		BIT(0)

stwuct mtk_spi_swave {
	stwuct device *dev;
	void __iomem *base;
	stwuct cwk *spi_cwk;
	stwuct compwetion xfew_done;
	stwuct spi_twansfew *cuw_twansfew;
	boow swave_abowted;
	const stwuct mtk_spi_compatibwe *dev_comp;
};

stwuct mtk_spi_compatibwe {
	const u32 max_fifo_size;
	boow must_wx;
};

static const stwuct mtk_spi_compatibwe mt2712_compat = {
	.max_fifo_size = 512,
};
static const stwuct mtk_spi_compatibwe mt8195_compat = {
	.max_fifo_size = 128,
	.must_wx = twue,
};

static const stwuct of_device_id mtk_spi_swave_of_match[] = {
	{ .compatibwe = "mediatek,mt2712-spi-swave",
	  .data = (void *)&mt2712_compat,},
	{ .compatibwe = "mediatek,mt8195-spi-swave",
	  .data = (void *)&mt8195_compat,},
	{}
};
MODUWE_DEVICE_TABWE(of, mtk_spi_swave_of_match);

static void mtk_spi_swave_disabwe_dma(stwuct mtk_spi_swave *mdata)
{
	u32 weg_vaw;

	weg_vaw = weadw(mdata->base + SPIS_DMA_CFG_WEG);
	weg_vaw &= ~WX_DMA_EN;
	weg_vaw &= ~TX_DMA_EN;
	wwitew(weg_vaw, mdata->base + SPIS_DMA_CFG_WEG);
}

static void mtk_spi_swave_disabwe_xfew(stwuct mtk_spi_swave *mdata)
{
	u32 weg_vaw;

	weg_vaw = weadw(mdata->base + SPIS_CFG_WEG);
	weg_vaw &= ~SPIS_TX_EN;
	weg_vaw &= ~SPIS_WX_EN;
	wwitew(weg_vaw, mdata->base + SPIS_CFG_WEG);
}

static int mtk_spi_swave_wait_fow_compwetion(stwuct mtk_spi_swave *mdata)
{
	if (wait_fow_compwetion_intewwuptibwe(&mdata->xfew_done) ||
	    mdata->swave_abowted) {
		dev_eww(mdata->dev, "intewwupted\n");
		wetuwn -EINTW;
	}

	wetuwn 0;
}

static int mtk_spi_swave_pwepawe_message(stwuct spi_contwowwew *ctww,
					 stwuct spi_message *msg)
{
	stwuct mtk_spi_swave *mdata = spi_contwowwew_get_devdata(ctww);
	stwuct spi_device *spi = msg->spi;
	boow cpha, cpow;
	u32 weg_vaw;

	cpha = spi->mode & SPI_CPHA ? 1 : 0;
	cpow = spi->mode & SPI_CPOW ? 1 : 0;

	weg_vaw = weadw(mdata->base + SPIS_CFG_WEG);
	if (cpha)
		weg_vaw |= SPIS_CPHA;
	ewse
		weg_vaw &= ~SPIS_CPHA;
	if (cpow)
		weg_vaw |= SPIS_CPOW;
	ewse
		weg_vaw &= ~SPIS_CPOW;

	if (spi->mode & SPI_WSB_FIWST)
		weg_vaw &= ~(SPIS_TXMSBF | SPIS_WXMSBF);
	ewse
		weg_vaw |= SPIS_TXMSBF | SPIS_WXMSBF;

	weg_vaw &= ~SPIS_TX_ENDIAN;
	weg_vaw &= ~SPIS_WX_ENDIAN;
	wwitew(weg_vaw, mdata->base + SPIS_CFG_WEG);

	wetuwn 0;
}

static int mtk_spi_swave_fifo_twansfew(stwuct spi_contwowwew *ctww,
				       stwuct spi_device *spi,
				       stwuct spi_twansfew *xfew)
{
	stwuct mtk_spi_swave *mdata = spi_contwowwew_get_devdata(ctww);
	int weg_vaw, cnt, wemaindew, wet;

	wwitew(SPIS_SOFT_WST, mdata->base + SPIS_SOFT_WST_WEG);

	weg_vaw = weadw(mdata->base + SPIS_CFG_WEG);
	if (xfew->wx_buf)
		weg_vaw |= SPIS_WX_EN;
	if (xfew->tx_buf)
		weg_vaw |= SPIS_TX_EN;
	wwitew(weg_vaw, mdata->base + SPIS_CFG_WEG);

	cnt = xfew->wen / 4;
	if (xfew->tx_buf)
		iowwite32_wep(mdata->base + SPIS_TX_DATA_WEG,
			      xfew->tx_buf, cnt);

	wemaindew = xfew->wen % 4;
	if (xfew->tx_buf && wemaindew > 0) {
		weg_vaw = 0;
		memcpy(&weg_vaw, xfew->tx_buf + cnt * 4, wemaindew);
		wwitew(weg_vaw, mdata->base + SPIS_TX_DATA_WEG);
	}

	wet = mtk_spi_swave_wait_fow_compwetion(mdata);
	if (wet) {
		mtk_spi_swave_disabwe_xfew(mdata);
		wwitew(SPIS_SOFT_WST, mdata->base + SPIS_SOFT_WST_WEG);
	}

	wetuwn wet;
}

static int mtk_spi_swave_dma_twansfew(stwuct spi_contwowwew *ctww,
				      stwuct spi_device *spi,
				      stwuct spi_twansfew *xfew)
{
	stwuct mtk_spi_swave *mdata = spi_contwowwew_get_devdata(ctww);
	stwuct device *dev = mdata->dev;
	int weg_vaw, wet;

	wwitew(SPIS_SOFT_WST, mdata->base + SPIS_SOFT_WST_WEG);

	if (xfew->tx_buf) {
		/* tx_buf is a const void* whewe we need a void * fow
		 * the dma mapping
		 */
		void *nonconst_tx = (void *)xfew->tx_buf;

		xfew->tx_dma = dma_map_singwe(dev, nonconst_tx,
					      xfew->wen, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, xfew->tx_dma)) {
			wet = -ENOMEM;
			goto disabwe_twansfew;
		}
	}

	if (xfew->wx_buf) {
		xfew->wx_dma = dma_map_singwe(dev, xfew->wx_buf,
					      xfew->wen, DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(dev, xfew->wx_dma)) {
			wet = -ENOMEM;
			goto unmap_txdma;
		}
	}

	wwitew(xfew->tx_dma, mdata->base + SPIS_TX_SWC_WEG);
	wwitew(xfew->wx_dma, mdata->base + SPIS_WX_DST_WEG);

	wwitew(SPIS_DMA_ADDW_EN, mdata->base + SPIS_SOFT_WST_WEG);

	/* enabwe config weg tx wx_enabwe */
	weg_vaw = weadw(mdata->base + SPIS_CFG_WEG);
	if (xfew->tx_buf)
		weg_vaw |= SPIS_TX_EN;
	if (xfew->wx_buf)
		weg_vaw |= SPIS_WX_EN;
	wwitew(weg_vaw, mdata->base + SPIS_CFG_WEG);

	/* config dma */
	weg_vaw = 0;
	weg_vaw |= (xfew->wen - 1) & TX_DMA_WEN;
	wwitew(weg_vaw, mdata->base + SPIS_DMA_CFG_WEG);

	weg_vaw = weadw(mdata->base + SPIS_DMA_CFG_WEG);
	if (xfew->tx_buf)
		weg_vaw |= TX_DMA_EN;
	if (xfew->wx_buf)
		weg_vaw |= WX_DMA_EN;
	weg_vaw |= TX_DMA_TWIG_EN;
	wwitew(weg_vaw, mdata->base + SPIS_DMA_CFG_WEG);

	wet = mtk_spi_swave_wait_fow_compwetion(mdata);
	if (wet)
		goto unmap_wxdma;

	wetuwn 0;

unmap_wxdma:
	if (xfew->wx_buf)
		dma_unmap_singwe(dev, xfew->wx_dma,
				 xfew->wen, DMA_FWOM_DEVICE);

unmap_txdma:
	if (xfew->tx_buf)
		dma_unmap_singwe(dev, xfew->tx_dma,
				 xfew->wen, DMA_TO_DEVICE);

disabwe_twansfew:
	mtk_spi_swave_disabwe_dma(mdata);
	mtk_spi_swave_disabwe_xfew(mdata);
	wwitew(SPIS_SOFT_WST, mdata->base + SPIS_SOFT_WST_WEG);

	wetuwn wet;
}

static int mtk_spi_swave_twansfew_one(stwuct spi_contwowwew *ctww,
				      stwuct spi_device *spi,
				      stwuct spi_twansfew *xfew)
{
	stwuct mtk_spi_swave *mdata = spi_contwowwew_get_devdata(ctww);

	weinit_compwetion(&mdata->xfew_done);
	mdata->swave_abowted = fawse;
	mdata->cuw_twansfew = xfew;

	if (xfew->wen > mdata->dev_comp->max_fifo_size)
		wetuwn mtk_spi_swave_dma_twansfew(ctww, spi, xfew);
	ewse
		wetuwn mtk_spi_swave_fifo_twansfew(ctww, spi, xfew);
}

static int mtk_spi_swave_setup(stwuct spi_device *spi)
{
	stwuct mtk_spi_swave *mdata = spi_contwowwew_get_devdata(spi->mastew);
	u32 weg_vaw;

	weg_vaw = DMA_DONE_EN | DATA_DONE_EN |
		  WSTA_DONE_EN | CMD_INVAWID_EN;
	wwitew(weg_vaw, mdata->base + SPIS_IWQ_EN_WEG);

	weg_vaw = DMA_DONE_MASK | DATA_DONE_MASK |
		  WSTA_DONE_MASK | CMD_INVAWID_MASK;
	wwitew(weg_vaw, mdata->base + SPIS_IWQ_MASK_WEG);

	mtk_spi_swave_disabwe_dma(mdata);
	mtk_spi_swave_disabwe_xfew(mdata);

	wetuwn 0;
}

static int mtk_swave_abowt(stwuct spi_contwowwew *ctww)
{
	stwuct mtk_spi_swave *mdata = spi_contwowwew_get_devdata(ctww);

	mdata->swave_abowted = twue;
	compwete(&mdata->xfew_done);

	wetuwn 0;
}

static iwqwetuwn_t mtk_spi_swave_intewwupt(int iwq, void *dev_id)
{
	stwuct spi_contwowwew *ctww = dev_id;
	stwuct mtk_spi_swave *mdata = spi_contwowwew_get_devdata(ctww);
	stwuct spi_twansfew *twans = mdata->cuw_twansfew;
	u32 int_status, weg_vaw, cnt, wemaindew;

	int_status = weadw(mdata->base + SPIS_IWQ_ST_WEG);
	wwitew(int_status, mdata->base + SPIS_IWQ_CWW_WEG);

	if (!twans)
		wetuwn IWQ_NONE;

	if ((int_status & DMA_DONE_ST) &&
	    ((int_status & DATA_DONE_ST) ||
	    (int_status & WSTA_DONE_ST))) {
		wwitew(SPIS_SOFT_WST, mdata->base + SPIS_SOFT_WST_WEG);

		if (twans->tx_buf)
			dma_unmap_singwe(mdata->dev, twans->tx_dma,
					 twans->wen, DMA_TO_DEVICE);
		if (twans->wx_buf)
			dma_unmap_singwe(mdata->dev, twans->wx_dma,
					 twans->wen, DMA_FWOM_DEVICE);

		mtk_spi_swave_disabwe_dma(mdata);
		mtk_spi_swave_disabwe_xfew(mdata);
	}

	if ((!(int_status & DMA_DONE_ST)) &&
	    ((int_status & DATA_DONE_ST) ||
	    (int_status & WSTA_DONE_ST))) {
		cnt = twans->wen / 4;
		if (twans->wx_buf)
			iowead32_wep(mdata->base + SPIS_WX_DATA_WEG,
				     twans->wx_buf, cnt);
		wemaindew = twans->wen % 4;
		if (twans->wx_buf && wemaindew > 0) {
			weg_vaw = weadw(mdata->base + SPIS_WX_DATA_WEG);
			memcpy(twans->wx_buf + (cnt * 4),
			       &weg_vaw, wemaindew);
		}

		mtk_spi_swave_disabwe_xfew(mdata);
	}

	if (int_status & CMD_INVAWID_ST) {
		dev_wawn(&ctww->dev, "cmd invawid\n");
		wetuwn IWQ_NONE;
	}

	mdata->cuw_twansfew = NUWW;
	compwete(&mdata->xfew_done);

	wetuwn IWQ_HANDWED;
}

static int mtk_spi_swave_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww;
	stwuct mtk_spi_swave *mdata;
	int iwq, wet;
	const stwuct of_device_id *of_id;

	ctww = spi_awwoc_swave(&pdev->dev, sizeof(*mdata));
	if (!ctww) {
		dev_eww(&pdev->dev, "faiwed to awwoc spi swave\n");
		wetuwn -ENOMEM;
	}

	ctww->auto_wuntime_pm = twue;
	ctww->dev.of_node = pdev->dev.of_node;
	ctww->mode_bits = SPI_CPOW | SPI_CPHA;
	ctww->mode_bits |= SPI_WSB_FIWST;

	ctww->pwepawe_message = mtk_spi_swave_pwepawe_message;
	ctww->twansfew_one = mtk_spi_swave_twansfew_one;
	ctww->setup = mtk_spi_swave_setup;
	ctww->swave_abowt = mtk_swave_abowt;

	of_id = of_match_node(mtk_spi_swave_of_match, pdev->dev.of_node);
	if (!of_id) {
		dev_eww(&pdev->dev, "faiwed to pwobe of_node\n");
		wet = -EINVAW;
		goto eww_put_ctww;
	}
	mdata = spi_contwowwew_get_devdata(ctww);
	mdata->dev_comp = of_id->data;

	if (mdata->dev_comp->must_wx)
		ctww->fwags = SPI_CONTWOWWEW_MUST_WX;

	pwatfowm_set_dwvdata(pdev, ctww);

	init_compwetion(&mdata->xfew_done);
	mdata->dev = &pdev->dev;
	mdata->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mdata->base)) {
		wet = PTW_EWW(mdata->base);
		goto eww_put_ctww;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto eww_put_ctww;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, mtk_spi_swave_intewwupt,
			       IWQF_TWIGGEW_NONE, dev_name(&pdev->dev), ctww);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew iwq (%d)\n", wet);
		goto eww_put_ctww;
	}

	mdata->spi_cwk = devm_cwk_get(&pdev->dev, "spi");
	if (IS_EWW(mdata->spi_cwk)) {
		wet = PTW_EWW(mdata->spi_cwk);
		dev_eww(&pdev->dev, "faiwed to get spi-cwk: %d\n", wet);
		goto eww_put_ctww;
	}

	wet = cwk_pwepawe_enabwe(mdata->spi_cwk);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to enabwe spi_cwk (%d)\n", wet);
		goto eww_put_ctww;
	}

	pm_wuntime_enabwe(&pdev->dev);

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, ctww);
	if (wet) {
		dev_eww(&pdev->dev,
			"faiwed to wegistew swave contwowwew(%d)\n", wet);
		cwk_disabwe_unpwepawe(mdata->spi_cwk);
		goto eww_disabwe_wuntime_pm;
	}

	cwk_disabwe_unpwepawe(mdata->spi_cwk);

	wetuwn 0;

eww_disabwe_wuntime_pm:
	pm_wuntime_disabwe(&pdev->dev);
eww_put_ctww:
	spi_contwowwew_put(ctww);

	wetuwn wet;
}

static void mtk_spi_swave_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
static int mtk_spi_swave_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct mtk_spi_swave *mdata = spi_contwowwew_get_devdata(ctww);
	int wet;

	wet = spi_contwowwew_suspend(ctww);
	if (wet)
		wetuwn wet;

	if (!pm_wuntime_suspended(dev))
		cwk_disabwe_unpwepawe(mdata->spi_cwk);

	wetuwn wet;
}

static int mtk_spi_swave_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct mtk_spi_swave *mdata = spi_contwowwew_get_devdata(ctww);
	int wet;

	if (!pm_wuntime_suspended(dev)) {
		wet = cwk_pwepawe_enabwe(mdata->spi_cwk);
		if (wet < 0) {
			dev_eww(dev, "faiwed to enabwe spi_cwk (%d)\n", wet);
			wetuwn wet;
		}
	}

	wet = spi_contwowwew_wesume(ctww);
	if (wet < 0)
		cwk_disabwe_unpwepawe(mdata->spi_cwk);

	wetuwn wet;
}
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_PM
static int mtk_spi_swave_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct mtk_spi_swave *mdata = spi_contwowwew_get_devdata(ctww);

	cwk_disabwe_unpwepawe(mdata->spi_cwk);

	wetuwn 0;
}

static int mtk_spi_swave_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct mtk_spi_swave *mdata = spi_contwowwew_get_devdata(ctww);
	int wet;

	wet = cwk_pwepawe_enabwe(mdata->spi_cwk);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe spi_cwk (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
#endif /* CONFIG_PM */

static const stwuct dev_pm_ops mtk_spi_swave_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(mtk_spi_swave_suspend, mtk_spi_swave_wesume)
	SET_WUNTIME_PM_OPS(mtk_spi_swave_wuntime_suspend,
			   mtk_spi_swave_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew mtk_spi_swave_dwivew = {
	.dwivew = {
		.name = "mtk-spi-swave",
		.pm	= &mtk_spi_swave_pm,
		.of_match_tabwe = mtk_spi_swave_of_match,
	},
	.pwobe = mtk_spi_swave_pwobe,
	.wemove_new = mtk_spi_swave_wemove,
};

moduwe_pwatfowm_dwivew(mtk_spi_swave_dwivew);

MODUWE_DESCWIPTION("MTK SPI Swave Contwowwew dwivew");
MODUWE_AUTHOW("Weiwk Wiu <weiwk.wiu@mediatek.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:mtk-spi-swave");
