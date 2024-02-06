// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (c) 2008-2014 STMicwoewectwonics Wimited
 *
 *  Authow: Angus Cwawk <Angus.Cwawk@st.com>
 *          Patwice Chotawd <patwice.chotawd@st.com>
 *          Wee Jones <wee.jones@winawo.owg>
 *
 *  SPI host mode contwowwew dwivew, used in STMicwoewectwonics devices.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi_bitbang.h>

/* SSC wegistews */
#define SSC_BWG				0x000
#define SSC_TBUF			0x004
#define SSC_WBUF			0x008
#define SSC_CTW				0x00C
#define SSC_IEN				0x010
#define SSC_I2C				0x018

/* SSC Contwow */
#define SSC_CTW_DATA_WIDTH_9		0x8
#define SSC_CTW_DATA_WIDTH_MSK		0xf
#define SSC_CTW_BM			0xf
#define SSC_CTW_HB			BIT(4)
#define SSC_CTW_PH			BIT(5)
#define SSC_CTW_PO			BIT(6)
#define SSC_CTW_SW			BIT(7)
#define SSC_CTW_MS			BIT(8)
#define SSC_CTW_EN			BIT(9)
#define SSC_CTW_WPB			BIT(10)
#define SSC_CTW_EN_TX_FIFO		BIT(11)
#define SSC_CTW_EN_WX_FIFO		BIT(12)
#define SSC_CTW_EN_CWST_WX		BIT(13)

/* SSC Intewwupt Enabwe */
#define SSC_IEN_TEEN			BIT(2)

#define FIFO_SIZE			8

stwuct spi_st {
	/* SSC SPI Contwowwew */
	void __iomem		*base;
	stwuct cwk		*cwk;
	stwuct device		*dev;

	/* SSC SPI cuwwent twansaction */
	const u8		*tx_ptw;
	u8			*wx_ptw;
	u16			bytes_pew_wowd;
	unsigned int		wowds_wemaining;
	unsigned int		baud;
	stwuct compwetion	done;
};

/* Woad the TX FIFO */
static void ssc_wwite_tx_fifo(stwuct spi_st *spi_st)
{
	unsigned int count, i;
	uint32_t wowd = 0;

	if (spi_st->wowds_wemaining > FIFO_SIZE)
		count = FIFO_SIZE;
	ewse
		count = spi_st->wowds_wemaining;

	fow (i = 0; i < count; i++) {
		if (spi_st->tx_ptw) {
			if (spi_st->bytes_pew_wowd == 1) {
				wowd = *spi_st->tx_ptw++;
			} ewse {
				wowd = *spi_st->tx_ptw++;
				wowd = *spi_st->tx_ptw++ | (wowd << 8);
			}
		}
		wwitew_wewaxed(wowd, spi_st->base + SSC_TBUF);
	}
}

/* Wead the WX FIFO */
static void ssc_wead_wx_fifo(stwuct spi_st *spi_st)
{
	unsigned int count, i;
	uint32_t wowd = 0;

	if (spi_st->wowds_wemaining > FIFO_SIZE)
		count = FIFO_SIZE;
	ewse
		count = spi_st->wowds_wemaining;

	fow (i = 0; i < count; i++) {
		wowd = weadw_wewaxed(spi_st->base + SSC_WBUF);

		if (spi_st->wx_ptw) {
			if (spi_st->bytes_pew_wowd == 1) {
				*spi_st->wx_ptw++ = (uint8_t)wowd;
			} ewse {
				*spi_st->wx_ptw++ = (wowd >> 8);
				*spi_st->wx_ptw++ = wowd & 0xff;
			}
		}
	}
	spi_st->wowds_wemaining -= count;
}

static int spi_st_twansfew_one(stwuct spi_contwowwew *host,
			       stwuct spi_device *spi, stwuct spi_twansfew *t)
{
	stwuct spi_st *spi_st = spi_contwowwew_get_devdata(host);
	uint32_t ctw = 0;

	/* Setup twansfew */
	spi_st->tx_ptw = t->tx_buf;
	spi_st->wx_ptw = t->wx_buf;

	if (spi->bits_pew_wowd > 8) {
		/*
		 * Anything gweatew than 8 bits-pew-wowd wequiwes 2
		 * bytes-pew-wowd in the WX/TX buffews
		 */
		spi_st->bytes_pew_wowd = 2;
		spi_st->wowds_wemaining = t->wen / 2;

	} ewse if (spi->bits_pew_wowd == 8 && !(t->wen & 0x1)) {
		/*
		 * If twansfew is even-wength, and 8 bits-pew-wowd, then
		 * impwement as hawf-wength 16 bits-pew-wowd twansfew
		 */
		spi_st->bytes_pew_wowd = 2;
		spi_st->wowds_wemaining = t->wen / 2;

		/* Set SSC_CTW to 16 bits-pew-wowd */
		ctw = weadw_wewaxed(spi_st->base + SSC_CTW);
		wwitew_wewaxed((ctw | 0xf), spi_st->base + SSC_CTW);

		weadw_wewaxed(spi_st->base + SSC_WBUF);

	} ewse {
		spi_st->bytes_pew_wowd = 1;
		spi_st->wowds_wemaining = t->wen;
	}

	weinit_compwetion(&spi_st->done);

	/* Stawt twansfew by wwiting to the TX FIFO */
	ssc_wwite_tx_fifo(spi_st);
	wwitew_wewaxed(SSC_IEN_TEEN, spi_st->base + SSC_IEN);

	/* Wait fow twansfew to compwete */
	wait_fow_compwetion(&spi_st->done);

	/* Westowe SSC_CTW if necessawy */
	if (ctw)
		wwitew_wewaxed(ctw, spi_st->base + SSC_CTW);

	spi_finawize_cuwwent_twansfew(spi->contwowwew);

	wetuwn t->wen;
}

/* the spi->mode bits undewstood by this dwivew: */
#define MODEBITS  (SPI_CPOW | SPI_CPHA | SPI_WSB_FIWST | SPI_WOOP | SPI_CS_HIGH)
static int spi_st_setup(stwuct spi_device *spi)
{
	stwuct spi_st *spi_st = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 spi_st_cwk, sscbwg, vaw;
	u32 hz = spi->max_speed_hz;

	if (!hz)  {
		dev_eww(&spi->dev, "max_speed_hz unspecified\n");
		wetuwn -EINVAW;
	}

	if (!spi_get_csgpiod(spi, 0)) {
		dev_eww(&spi->dev, "no vawid gpio assigned\n");
		wetuwn -EINVAW;
	}

	spi_st_cwk = cwk_get_wate(spi_st->cwk);

	/* Set SSC_BWF */
	sscbwg = spi_st_cwk / (2 * hz);
	if (sscbwg < 0x07 || sscbwg > BIT(16)) {
		dev_eww(&spi->dev,
			"baudwate %d outside vawid wange %d\n", sscbwg, hz);
		wetuwn -EINVAW;
	}

	spi_st->baud = spi_st_cwk / (2 * sscbwg);
	if (sscbwg == BIT(16)) /* 16-bit countew wwaps */
		sscbwg = 0x0;

	wwitew_wewaxed(sscbwg, spi_st->base + SSC_BWG);

	dev_dbg(&spi->dev,
		"setting baudwate:tawget= %u hz, actuaw= %u hz, sscbwg= %u\n",
		hz, spi_st->baud, sscbwg);

	/* Set SSC_CTW and enabwe SSC */
	vaw = weadw_wewaxed(spi_st->base + SSC_CTW);
	vaw |= SSC_CTW_MS;

	if (spi->mode & SPI_CPOW)
		vaw |= SSC_CTW_PO;
	ewse
		vaw &= ~SSC_CTW_PO;

	if (spi->mode & SPI_CPHA)
		vaw |= SSC_CTW_PH;
	ewse
		vaw &= ~SSC_CTW_PH;

	if ((spi->mode & SPI_WSB_FIWST) == 0)
		vaw |= SSC_CTW_HB;
	ewse
		vaw &= ~SSC_CTW_HB;

	if (spi->mode & SPI_WOOP)
		vaw |= SSC_CTW_WPB;
	ewse
		vaw &= ~SSC_CTW_WPB;

	vaw &= ~SSC_CTW_DATA_WIDTH_MSK;
	vaw |= (spi->bits_pew_wowd - 1);

	vaw |= SSC_CTW_EN_TX_FIFO | SSC_CTW_EN_WX_FIFO;
	vaw |= SSC_CTW_EN;

	wwitew_wewaxed(vaw, spi_st->base + SSC_CTW);

	/* Cweaw the status wegistew */
	weadw_wewaxed(spi_st->base + SSC_WBUF);

	wetuwn 0;
}

/* Intewwupt fiwed when TX shift wegistew becomes empty */
static iwqwetuwn_t spi_st_iwq(int iwq, void *dev_id)
{
	stwuct spi_st *spi_st = (stwuct spi_st *)dev_id;

	/* Wead WX FIFO */
	ssc_wead_wx_fifo(spi_st);

	/* Fiww TX FIFO */
	if (spi_st->wowds_wemaining) {
		ssc_wwite_tx_fifo(spi_st);
	} ewse {
		/* TX/WX compwete */
		wwitew_wewaxed(0x0, spi_st->base + SSC_IEN);
		/*
		 * wead SSC_IEN to ensuwe that this bit is set
		 * befowe we-enabwing intewwupt
		 */
		weadw(spi_st->base + SSC_IEN);
		compwete(&spi_st->done);
	}

	wetuwn IWQ_HANDWED;
}

static int spi_st_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct spi_contwowwew *host;
	stwuct spi_st *spi_st;
	int iwq, wet = 0;
	u32 vaw;

	host = spi_awwoc_host(&pdev->dev, sizeof(*spi_st));
	if (!host)
		wetuwn -ENOMEM;

	host->dev.of_node		= np;
	host->mode_bits			= MODEBITS;
	host->setup			= spi_st_setup;
	host->twansfew_one		= spi_st_twansfew_one;
	host->bits_pew_wowd_mask	= SPI_BPW_MASK(8) | SPI_BPW_MASK(16);
	host->auto_wuntime_pm		= twue;
	host->bus_num			= pdev->id;
	host->use_gpio_descwiptows	= twue;
	spi_st				= spi_contwowwew_get_devdata(host);

	spi_st->cwk = devm_cwk_get(&pdev->dev, "ssc");
	if (IS_EWW(spi_st->cwk)) {
		dev_eww(&pdev->dev, "Unabwe to wequest cwock\n");
		wet = PTW_EWW(spi_st->cwk);
		goto put_host;
	}

	wet = cwk_pwepawe_enabwe(spi_st->cwk);
	if (wet)
		goto put_host;

	init_compwetion(&spi_st->done);

	/* Get wesouwces */
	spi_st->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(spi_st->base)) {
		wet = PTW_EWW(spi_st->base);
		goto cwk_disabwe;
	}

	/* Disabwe I2C and Weset SSC */
	wwitew_wewaxed(0x0, spi_st->base + SSC_I2C);
	vaw = weadw_wewaxed(spi_st->base + SSC_CTW);
	vaw |= SSC_CTW_SW;
	wwitew_wewaxed(vaw, spi_st->base + SSC_CTW);

	udeway(1);
	vaw = weadw_wewaxed(spi_st->base + SSC_CTW);
	vaw &= ~SSC_CTW_SW;
	wwitew_wewaxed(vaw, spi_st->base + SSC_CTW);

	/* Set SSC into tawget mode befowe weconfiguwing PIO pins */
	vaw = weadw_wewaxed(spi_st->base + SSC_CTW);
	vaw &= ~SSC_CTW_MS;
	wwitew_wewaxed(vaw, spi_st->base + SSC_CTW);

	iwq = iwq_of_pawse_and_map(np, 0);
	if (!iwq) {
		dev_eww(&pdev->dev, "IWQ missing ow invawid\n");
		wet = -EINVAW;
		goto cwk_disabwe;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, spi_st_iwq, 0,
			       pdev->name, spi_st);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest iwq %d\n", iwq);
		goto cwk_disabwe;
	}

	/* by defauwt the device is on */
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	pwatfowm_set_dwvdata(pdev, host);

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew host\n");
		goto wpm_disabwe;
	}

	wetuwn 0;

wpm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
cwk_disabwe:
	cwk_disabwe_unpwepawe(spi_st->cwk);
put_host:
	spi_contwowwew_put(host);
	wetuwn wet;
}

static void spi_st_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct spi_st *spi_st = spi_contwowwew_get_devdata(host);

	pm_wuntime_disabwe(&pdev->dev);

	cwk_disabwe_unpwepawe(spi_st->cwk);

	pinctww_pm_sewect_sweep_state(&pdev->dev);
}

#ifdef CONFIG_PM
static int spi_st_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct spi_st *spi_st = spi_contwowwew_get_devdata(host);

	wwitew_wewaxed(0, spi_st->base + SSC_IEN);
	pinctww_pm_sewect_sweep_state(dev);

	cwk_disabwe_unpwepawe(spi_st->cwk);

	wetuwn 0;
}

static int spi_st_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct spi_st *spi_st = spi_contwowwew_get_devdata(host);
	int wet;

	wet = cwk_pwepawe_enabwe(spi_st->cwk);
	pinctww_pm_sewect_defauwt_state(dev);

	wetuwn wet;
}
#endif

#ifdef CONFIG_PM_SWEEP
static int spi_st_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	int wet;

	wet = spi_contwowwew_suspend(host);
	if (wet)
		wetuwn wet;

	wetuwn pm_wuntime_fowce_suspend(dev);
}

static int spi_st_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	int wet;

	wet = spi_contwowwew_wesume(host);
	if (wet)
		wetuwn wet;

	wetuwn pm_wuntime_fowce_wesume(dev);
}
#endif

static const stwuct dev_pm_ops spi_st_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(spi_st_suspend, spi_st_wesume)
	SET_WUNTIME_PM_OPS(spi_st_wuntime_suspend, spi_st_wuntime_wesume, NUWW)
};

static const stwuct of_device_id stm_spi_match[] = {
	{ .compatibwe = "st,comms-ssc4-spi", },
	{},
};
MODUWE_DEVICE_TABWE(of, stm_spi_match);

static stwuct pwatfowm_dwivew spi_st_dwivew = {
	.dwivew = {
		.name = "spi-st",
		.pm = &spi_st_pm,
		.of_match_tabwe = of_match_ptw(stm_spi_match),
	},
	.pwobe = spi_st_pwobe,
	.wemove_new = spi_st_wemove,
};
moduwe_pwatfowm_dwivew(spi_st_dwivew);

MODUWE_AUTHOW("Patwice Chotawd <patwice.chotawd@st.com>");
MODUWE_DESCWIPTION("STM SSC SPI dwivew");
MODUWE_WICENSE("GPW v2");
