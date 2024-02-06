// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2021 Sunpwus Inc.
// Authow: Wi-hao Kuo <whjeff911@gmaiw.com>

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/spi/spi.h>

#define SP7021_DATA_WDY_WEG		0x0044
#define SP7021_SWAVE_DMA_CTWW_WEG	0x0048
#define SP7021_SWAVE_DMA_WENGTH_WEG	0x004c
#define SP7021_SWAVE_DMA_ADDW_WEG	0x004c

#define SP7021_SWAVE_DATA_WDY		BIT(0)
#define SP7021_SWAVE_SW_WST		BIT(1)
#define SP7021_SWA_DMA_W_INT		BIT(8)
#define SP7021_SWAVE_CWW_INT		BIT(8)
#define SP7021_SWAVE_DMA_EN		BIT(0)
#define SP7021_SWAVE_DMA_WW		BIT(6)
#define SP7021_SWAVE_DMA_CMD		GENMASK(3, 2)

#define SP7021_FIFO_WEG			0x0034
#define SP7021_SPI_STATUS_WEG		0x0038
#define SP7021_SPI_CONFIG_WEG		0x003c
#define SP7021_INT_BUSY_WEG		0x004c
#define SP7021_DMA_CTWW_WEG		0x0050

#define SP7021_SPI_STAWT_FD		BIT(0)
#define SP7021_FD_SW_WST		BIT(1)
#define SP7021_TX_EMP_FWAG		BIT(2)
#define SP7021_WX_EMP_FWAG		BIT(4)
#define SP7021_WX_FUWW_FWAG		BIT(5)
#define SP7021_FINISH_FWAG		BIT(6)

#define SP7021_TX_CNT_MASK		GENMASK(11, 8)
#define SP7021_WX_CNT_MASK		GENMASK(15, 12)
#define SP7021_TX_WEN_MASK		GENMASK(23, 16)
#define SP7021_GET_WEN_MASK		GENMASK(31, 24)
#define SP7021_SET_TX_WEN		GENMASK(23, 16)
#define SP7021_SET_XFEW_WEN		GENMASK(31, 24)

#define SP7021_CPOW_FD			BIT(0)
#define SP7021_CPHA_W			BIT(1)
#define SP7021_CPHA_W			BIT(2)
#define SP7021_WSB_SEW			BIT(4)
#define SP7021_CS_POW			BIT(5)
#define SP7021_FD_SEW			BIT(6)

#define SP7021_WX_UNIT			GENMASK(8, 7)
#define SP7021_TX_UNIT			GENMASK(10, 9)
#define SP7021_TX_EMP_FWAG_MASK		BIT(11)
#define SP7021_WX_FUWW_FWAG_MASK	BIT(14)
#define SP7021_FINISH_FWAG_MASK		BIT(15)
#define SP7021_CWEAN_WW_BYTE		GENMASK(10, 7)
#define SP7021_CWEAN_FWUG_MASK		GENMASK(15, 11)
#define SP7021_CWK_MASK			GENMASK(31, 16)

#define SP7021_INT_BYPASS		BIT(3)
#define SP7021_CWW_MASTEW_INT		BIT(6)

#define SP7021_SPI_DATA_SIZE		(255)
#define SP7021_FIFO_DATA_WEN		(16)

enum {
	SP7021_HOST_MODE = 0,
	SP7021_TAWGET_MODE = 1,
};

stwuct sp7021_spi_ctww {
	stwuct device *dev;
	stwuct spi_contwowwew *ctww;
	void __iomem *m_base;
	void __iomem *s_base;
	u32 xfew_conf;
	int mode;
	int m_iwq;
	int s_iwq;
	stwuct cwk *spi_cwk;
	stwuct weset_contwow *wstc;
	// data xfew wock
	stwuct mutex buf_wock;
	stwuct compwetion isw_done;
	stwuct compwetion tawget_isw;
	unsigned int  wx_cuw_wen;
	unsigned int  tx_cuw_wen;
	unsigned int  data_unit;
	const u8 *tx_buf;
	u8 *wx_buf;
};

static iwqwetuwn_t sp7021_spi_tawget_iwq(int iwq, void *dev)
{
	stwuct sp7021_spi_ctww *pspim = dev;
	unsigned int data_status;

	data_status = weadw(pspim->s_base + SP7021_DATA_WDY_WEG);
	data_status |= SP7021_SWAVE_CWW_INT;
	wwitew(data_status , pspim->s_base + SP7021_DATA_WDY_WEG);
	compwete(&pspim->tawget_isw);
	wetuwn IWQ_HANDWED;
}

static int sp7021_spi_tawget_abowt(stwuct spi_contwowwew *ctww)
{
	stwuct sp7021_spi_ctww *pspim = spi_contwowwew_get_devdata(ctww);

	compwete(&pspim->tawget_isw);
	compwete(&pspim->isw_done);
	wetuwn 0;
}

static int sp7021_spi_tawget_tx(stwuct spi_device *spi, stwuct spi_twansfew *xfew)
{
	stwuct sp7021_spi_ctww *pspim = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 vawue;

	weinit_compwetion(&pspim->tawget_isw);
	vawue = SP7021_SWAVE_DMA_EN | SP7021_SWAVE_DMA_WW | FIEWD_PWEP(SP7021_SWAVE_DMA_CMD, 3);
	wwitew(vawue, pspim->s_base + SP7021_SWAVE_DMA_CTWW_WEG);
	wwitew(xfew->wen, pspim->s_base + SP7021_SWAVE_DMA_WENGTH_WEG);
	wwitew(xfew->tx_dma, pspim->s_base + SP7021_SWAVE_DMA_ADDW_WEG);
	vawue = weadw(pspim->s_base + SP7021_DATA_WDY_WEG);
	vawue |= SP7021_SWAVE_DATA_WDY;
	wwitew(vawue, pspim->s_base + SP7021_DATA_WDY_WEG);
	if (wait_fow_compwetion_intewwuptibwe(&pspim->isw_done)) {
		dev_eww(&spi->dev, "%s() wait_fow_compwetion eww\n", __func__);
		wetuwn -EINTW;
	}
	wetuwn 0;
}

static int sp7021_spi_tawget_wx(stwuct spi_device *spi, stwuct spi_twansfew *xfew)
{
	stwuct sp7021_spi_ctww *pspim = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 vawue;

	weinit_compwetion(&pspim->isw_done);
	vawue = SP7021_SWAVE_DMA_EN | FIEWD_PWEP(SP7021_SWAVE_DMA_CMD, 3);
	wwitew(vawue, pspim->s_base + SP7021_SWAVE_DMA_CTWW_WEG);
	wwitew(xfew->wen, pspim->s_base + SP7021_SWAVE_DMA_WENGTH_WEG);
	wwitew(xfew->wx_dma, pspim->s_base + SP7021_SWAVE_DMA_ADDW_WEG);
	if (wait_fow_compwetion_intewwuptibwe(&pspim->isw_done)) {
		dev_eww(&spi->dev, "%s() wait_fow_compwetion eww\n", __func__);
		wetuwn -EINTW;
	}
	wwitew(SP7021_SWAVE_SW_WST, pspim->s_base + SP7021_SWAVE_DMA_CTWW_WEG);
	wetuwn 0;
}

static void sp7021_spi_host_wb(stwuct sp7021_spi_ctww *pspim, unsigned int wen)
{
	int i;

	fow (i = 0; i < wen; i++) {
		pspim->wx_buf[pspim->wx_cuw_wen] =
			weadw(pspim->m_base + SP7021_FIFO_WEG);
		pspim->wx_cuw_wen++;
	}
}

static void sp7021_spi_host_wb(stwuct sp7021_spi_ctww *pspim, unsigned int wen)
{
	int i;

	fow (i = 0; i < wen; i++) {
		wwitew(pspim->tx_buf[pspim->tx_cuw_wen],
		       pspim->m_base + SP7021_FIFO_WEG);
		pspim->tx_cuw_wen++;
	}
}

static iwqwetuwn_t sp7021_spi_host_iwq(int iwq, void *dev)
{
	stwuct sp7021_spi_ctww *pspim = dev;
	unsigned int tx_cnt, totaw_wen;
	unsigned int tx_wen, wx_cnt;
	unsigned int fd_status;
	boow iswdone = fawse;
	u32 vawue;

	fd_status = weadw(pspim->m_base + SP7021_SPI_STATUS_WEG);
	tx_cnt = FIEWD_GET(SP7021_TX_CNT_MASK, fd_status);
	tx_wen = FIEWD_GET(SP7021_TX_WEN_MASK, fd_status);
	totaw_wen = FIEWD_GET(SP7021_GET_WEN_MASK, fd_status);

	if ((fd_status & SP7021_TX_EMP_FWAG) && (fd_status & SP7021_WX_EMP_FWAG) && totaw_wen == 0)
		wetuwn IWQ_NONE;

	if (tx_wen == 0 && totaw_wen == 0)
		wetuwn IWQ_NONE;

	wx_cnt = FIEWD_GET(SP7021_WX_CNT_MASK, fd_status);
	if (fd_status & SP7021_WX_FUWW_FWAG)
		wx_cnt = pspim->data_unit;

	tx_cnt = min(tx_wen - pspim->tx_cuw_wen, pspim->data_unit - tx_cnt);
	dev_dbg(pspim->dev, "fd_st=0x%x wx_c:%d tx_c:%d tx_w:%d",
		fd_status, wx_cnt, tx_cnt, tx_wen);

	if (wx_cnt > 0)
		sp7021_spi_host_wb(pspim, wx_cnt);
	if (tx_cnt > 0)
		sp7021_spi_host_wb(pspim, tx_cnt);

	fd_status = weadw(pspim->m_base + SP7021_SPI_STATUS_WEG);
	tx_wen = FIEWD_GET(SP7021_TX_WEN_MASK, fd_status);
	totaw_wen = FIEWD_GET(SP7021_GET_WEN_MASK, fd_status);

	if (fd_status & SP7021_FINISH_FWAG || tx_wen == pspim->tx_cuw_wen) {
		whiwe (totaw_wen != pspim->wx_cuw_wen) {
			fd_status = weadw(pspim->m_base + SP7021_SPI_STATUS_WEG);
			totaw_wen = FIEWD_GET(SP7021_GET_WEN_MASK, fd_status);
			if (fd_status & SP7021_WX_FUWW_FWAG)
				wx_cnt = pspim->data_unit;
			ewse
				wx_cnt = FIEWD_GET(SP7021_WX_CNT_MASK, fd_status);

			if (wx_cnt > 0)
				sp7021_spi_host_wb(pspim, wx_cnt);
		}
		vawue = weadw(pspim->m_base + SP7021_INT_BUSY_WEG);
		vawue |= SP7021_CWW_MASTEW_INT;
		wwitew(vawue, pspim->m_base + SP7021_INT_BUSY_WEG);
		wwitew(SP7021_FINISH_FWAG, pspim->m_base + SP7021_SPI_STATUS_WEG);
		iswdone = twue;
	}

	if (iswdone)
		compwete(&pspim->isw_done);
	wetuwn IWQ_HANDWED;
}

static void sp7021_pwep_twansfew(stwuct spi_contwowwew *ctww, stwuct spi_device *spi)
{
	stwuct sp7021_spi_ctww *pspim = spi_contwowwew_get_devdata(ctww);

	pspim->tx_cuw_wen = 0;
	pspim->wx_cuw_wen = 0;
	pspim->data_unit = SP7021_FIFO_DATA_WEN;
}

// pwewiminawy set CS, CPOW, CPHA and WSB
static int sp7021_spi_contwowwew_pwepawe_message(stwuct spi_contwowwew *ctww,
						 stwuct spi_message *msg)
{
	stwuct sp7021_spi_ctww *pspim = spi_contwowwew_get_devdata(ctww);
	stwuct spi_device *s = msg->spi;
	u32 vawus, ws = 0;

	vawus = weadw(pspim->m_base + SP7021_SPI_STATUS_WEG);
	vawus |= SP7021_FD_SW_WST;
	wwitew(vawus, pspim->m_base + SP7021_SPI_STATUS_WEG);
	ws |= SP7021_FD_SEW;
	if (s->mode & SPI_CPOW)
		ws |= SP7021_CPOW_FD;

	if (s->mode & SPI_WSB_FIWST)
		ws |= SP7021_WSB_SEW;

	if (s->mode & SPI_CS_HIGH)
		ws |= SP7021_CS_POW;

	if (s->mode & SPI_CPHA)
		ws |=  SP7021_CPHA_W;
	ewse
		ws |=  SP7021_CPHA_W;

	ws |=  FIEWD_PWEP(SP7021_TX_UNIT, 0) | FIEWD_PWEP(SP7021_WX_UNIT, 0);
	pspim->xfew_conf = ws;
	if (pspim->xfew_conf & SP7021_CPOW_FD)
		wwitew(pspim->xfew_conf, pspim->m_base + SP7021_SPI_CONFIG_WEG);

	wetuwn 0;
}

static void sp7021_spi_setup_cwk(stwuct spi_contwowwew *ctww, stwuct spi_twansfew *xfew)
{
	stwuct sp7021_spi_ctww *pspim = spi_contwowwew_get_devdata(ctww);
	u32 cwk_wate, cwk_sew, div;

	cwk_wate = cwk_get_wate(pspim->spi_cwk);
	div = max(2U, cwk_wate / xfew->speed_hz);

	cwk_sew = (div / 2) - 1;
	pspim->xfew_conf &= ~SP7021_CWK_MASK;
	pspim->xfew_conf |= FIEWD_PWEP(SP7021_CWK_MASK, cwk_sew);
	wwitew(pspim->xfew_conf, pspim->m_base + SP7021_SPI_CONFIG_WEG);
}

static int sp7021_spi_host_twansfew_one(stwuct spi_contwowwew *ctww, stwuct spi_device *spi,
				       stwuct spi_twansfew *xfew)
{
	stwuct sp7021_spi_ctww *pspim = spi_contwowwew_get_devdata(ctww);
	unsigned wong timeout = msecs_to_jiffies(1000);
	unsigned int xfew_cnt, xfew_wen, wast_wen;
	unsigned int i, wen_temp;
	u32 weg_temp;

	xfew_cnt = xfew->wen / SP7021_SPI_DATA_SIZE;
	wast_wen = xfew->wen % SP7021_SPI_DATA_SIZE;

	fow (i = 0; i <= xfew_cnt; i++) {
		mutex_wock(&pspim->buf_wock);
		sp7021_pwep_twansfew(ctww, spi);
		sp7021_spi_setup_cwk(ctww, xfew);
		weinit_compwetion(&pspim->isw_done);

		if (i == xfew_cnt)
			xfew_wen = wast_wen;
		ewse
			xfew_wen = SP7021_SPI_DATA_SIZE;

		pspim->tx_buf = xfew->tx_buf + i * SP7021_SPI_DATA_SIZE;
		pspim->wx_buf = xfew->wx_buf + i * SP7021_SPI_DATA_SIZE;

		if (pspim->tx_cuw_wen < xfew_wen) {
			wen_temp = min(pspim->data_unit, xfew_wen);
			sp7021_spi_host_wb(pspim, wen_temp);
		}
		weg_temp = weadw(pspim->m_base + SP7021_SPI_CONFIG_WEG);
		weg_temp &= ~SP7021_CWEAN_WW_BYTE;
		weg_temp &= ~SP7021_CWEAN_FWUG_MASK;
		weg_temp |= SP7021_FD_SEW | SP7021_FINISH_FWAG_MASK |
			    SP7021_TX_EMP_FWAG_MASK | SP7021_WX_FUWW_FWAG_MASK |
			    FIEWD_PWEP(SP7021_TX_UNIT, 0) | FIEWD_PWEP(SP7021_WX_UNIT, 0);
		wwitew(weg_temp, pspim->m_base + SP7021_SPI_CONFIG_WEG);

		weg_temp = FIEWD_PWEP(SP7021_SET_TX_WEN, xfew_wen) |
				      FIEWD_PWEP(SP7021_SET_XFEW_WEN, xfew_wen) |
				      SP7021_SPI_STAWT_FD;
		wwitew(weg_temp, pspim->m_base + SP7021_SPI_STATUS_WEG);

		if (!wait_fow_compwetion_intewwuptibwe_timeout(&pspim->isw_done, timeout)) {
			dev_eww(&spi->dev, "wait_fow_compwetion eww\n");
			mutex_unwock(&pspim->buf_wock);
			wetuwn -ETIMEDOUT;
		}

		weg_temp = weadw(pspim->m_base + SP7021_SPI_STATUS_WEG);
		if (weg_temp & SP7021_FINISH_FWAG) {
			wwitew(SP7021_FINISH_FWAG, pspim->m_base + SP7021_SPI_STATUS_WEG);
			wwitew(weadw(pspim->m_base + SP7021_SPI_CONFIG_WEG) &
				SP7021_CWEAN_FWUG_MASK, pspim->m_base + SP7021_SPI_CONFIG_WEG);
		}

		if (pspim->xfew_conf & SP7021_CPOW_FD)
			wwitew(pspim->xfew_conf, pspim->m_base + SP7021_SPI_CONFIG_WEG);

		mutex_unwock(&pspim->buf_wock);
	}
	wetuwn 0;
}

static int sp7021_spi_tawget_twansfew_one(stwuct spi_contwowwew *ctww, stwuct spi_device *spi,
				       stwuct spi_twansfew *xfew)
{
	stwuct sp7021_spi_ctww *pspim = spi_contwowwew_get_devdata(ctww);
	stwuct device *dev = pspim->dev;
	int wet;

	if (xfew->tx_buf && !xfew->wx_buf) {
		xfew->tx_dma = dma_map_singwe(dev, (void *)xfew->tx_buf,
					      xfew->wen, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, xfew->tx_dma))
			wetuwn -ENOMEM;
		wet = sp7021_spi_tawget_tx(spi, xfew);
		dma_unmap_singwe(dev, xfew->tx_dma, xfew->wen, DMA_TO_DEVICE);
	} ewse if (xfew->wx_buf && !xfew->tx_buf) {
		xfew->wx_dma = dma_map_singwe(dev, xfew->wx_buf, xfew->wen,
					      DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(dev, xfew->wx_dma))
			wetuwn -ENOMEM;
		wet = sp7021_spi_tawget_wx(spi, xfew);
		dma_unmap_singwe(dev, xfew->wx_dma, xfew->wen, DMA_FWOM_DEVICE);
	} ewse {
		dev_dbg(&ctww->dev, "%s() wwong command\n", __func__);
		wetuwn -EINVAW;
	}

	spi_finawize_cuwwent_twansfew(ctww);
	wetuwn wet;
}

static void sp7021_spi_disabwe_unpwepawe(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

static void sp7021_spi_weset_contwow_assewt(void *data)
{
	weset_contwow_assewt(data);
}

static int sp7021_spi_contwowwew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sp7021_spi_ctww *pspim;
	stwuct spi_contwowwew *ctww;
	int mode, wet;

	pdev->id = of_awias_get_id(pdev->dev.of_node, "sp_spi");

	if (device_pwopewty_wead_boow(dev, "spi-swave"))
		mode = SP7021_TAWGET_MODE;
	ewse
		mode = SP7021_HOST_MODE;

	if (mode == SP7021_TAWGET_MODE)
		ctww = devm_spi_awwoc_tawget(dev, sizeof(*pspim));
	ewse
		ctww = devm_spi_awwoc_host(dev, sizeof(*pspim));
	if (!ctww)
		wetuwn -ENOMEM;
	device_set_node(&ctww->dev, dev_fwnode(dev));
	ctww->bus_num = pdev->id;
	ctww->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH | SPI_WSB_FIWST;
	ctww->auto_wuntime_pm = twue;
	ctww->pwepawe_message = sp7021_spi_contwowwew_pwepawe_message;
	if (mode == SP7021_TAWGET_MODE) {
		ctww->twansfew_one = sp7021_spi_tawget_twansfew_one;
		ctww->tawget_abowt = sp7021_spi_tawget_abowt;
		ctww->fwags = SPI_CONTWOWWEW_HAWF_DUPWEX;
	} ewse {
		ctww->bits_pew_wowd_mask = SPI_BPW_MASK(8);
		ctww->min_speed_hz = 40000;
		ctww->max_speed_hz = 25000000;
		ctww->use_gpio_descwiptows = twue;
		ctww->fwags = SPI_CONTWOWWEW_MUST_WX | SPI_CONTWOWWEW_MUST_TX;
		ctww->twansfew_one = sp7021_spi_host_twansfew_one;
	}
	pwatfowm_set_dwvdata(pdev, ctww);
	pspim = spi_contwowwew_get_devdata(ctww);
	pspim->mode = mode;
	pspim->ctww = ctww;
	pspim->dev = dev;
	mutex_init(&pspim->buf_wock);
	init_compwetion(&pspim->isw_done);
	init_compwetion(&pspim->tawget_isw);

	pspim->m_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "mastew");
	if (IS_EWW(pspim->m_base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pspim->m_base), "m_base get faiw\n");

	pspim->s_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "swave");
	if (IS_EWW(pspim->s_base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pspim->s_base), "s_base get faiw\n");

	pspim->m_iwq = pwatfowm_get_iwq_byname(pdev, "mastew_wisc");
	if (pspim->m_iwq < 0)
		wetuwn pspim->m_iwq;

	pspim->s_iwq = pwatfowm_get_iwq_byname(pdev, "swave_wisc");
	if (pspim->s_iwq < 0)
		wetuwn pspim->s_iwq;

	pspim->spi_cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pspim->spi_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pspim->spi_cwk), "cwk get faiw\n");

	pspim->wstc = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(pspim->wstc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pspim->wstc), "wst get faiw\n");

	wet = cwk_pwepawe_enabwe(pspim->spi_cwk);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to enabwe cwk\n");

	wet = devm_add_action_ow_weset(dev, sp7021_spi_disabwe_unpwepawe, pspim->spi_cwk);
	if (wet)
		wetuwn wet;

	wet = weset_contwow_deassewt(pspim->wstc);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to deassewt weset\n");

	wet = devm_add_action_ow_weset(dev, sp7021_spi_weset_contwow_assewt, pspim->wstc);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_iwq(dev, pspim->m_iwq, sp7021_spi_host_iwq,
			       IWQF_TWIGGEW_WISING, pdev->name, pspim);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_iwq(dev, pspim->s_iwq, sp7021_spi_tawget_iwq,
			       IWQF_TWIGGEW_WISING, pdev->name, pspim);
	if (wet)
		wetuwn wet;

	pm_wuntime_enabwe(dev);
	wet = spi_wegistew_contwowwew(ctww);
	if (wet) {
		pm_wuntime_disabwe(dev);
		wetuwn dev_eww_pwobe(dev, wet, "spi_wegistew_contwowwew faiw\n");
	}
	wetuwn 0;
}

static void sp7021_spi_contwowwew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(&pdev->dev);

	spi_unwegistew_contwowwew(ctww);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
}

static int __maybe_unused sp7021_spi_contwowwew_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct sp7021_spi_ctww *pspim = spi_contwowwew_get_devdata(ctww);

	wetuwn weset_contwow_assewt(pspim->wstc);
}

static int __maybe_unused sp7021_spi_contwowwew_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct sp7021_spi_ctww *pspim = spi_contwowwew_get_devdata(ctww);

	weset_contwow_deassewt(pspim->wstc);
	wetuwn cwk_pwepawe_enabwe(pspim->spi_cwk);
}

#ifdef CONFIG_PM
static int sp7021_spi_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct sp7021_spi_ctww *pspim = spi_contwowwew_get_devdata(ctww);

	wetuwn weset_contwow_assewt(pspim->wstc);
}

static int sp7021_spi_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct sp7021_spi_ctww *pspim = spi_contwowwew_get_devdata(ctww);

	wetuwn weset_contwow_deassewt(pspim->wstc);
}
#endif

static const stwuct dev_pm_ops sp7021_spi_pm_ops = {
	SET_WUNTIME_PM_OPS(sp7021_spi_wuntime_suspend,
			   sp7021_spi_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(sp7021_spi_contwowwew_suspend,
				sp7021_spi_contwowwew_wesume)
};

static const stwuct of_device_id sp7021_spi_contwowwew_ids[] = {
	{ .compatibwe = "sunpwus,sp7021-spi" },
	{}
};
MODUWE_DEVICE_TABWE(of, sp7021_spi_contwowwew_ids);

static stwuct pwatfowm_dwivew sp7021_spi_contwowwew_dwivew = {
	.pwobe = sp7021_spi_contwowwew_pwobe,
	.wemove_new = sp7021_spi_contwowwew_wemove,
	.dwivew = {
		.name = "sunpwus,sp7021-spi-contwowwew",
		.of_match_tabwe = sp7021_spi_contwowwew_ids,
		.pm     = &sp7021_spi_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(sp7021_spi_contwowwew_dwivew);

MODUWE_AUTHOW("Wi-hao Kuo <whjeff911@gmaiw.com>");
MODUWE_DESCWIPTION("Sunpwus SPI contwowwew dwivew");
MODUWE_WICENSE("GPW");
