// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SPI dwivew fow Nvidia's Tegwa20 Sewiaw Fwash Contwowwew.
 *
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * Authow: Waxman Dewangan <wdewangan@nvidia.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/weset.h>
#incwude <winux/spi/spi.h>

#define SPI_COMMAND				0x000
#define SPI_GO					BIT(30)
#define SPI_M_S					BIT(28)
#define SPI_ACTIVE_SCWK_MASK			(0x3 << 26)
#define SPI_ACTIVE_SCWK_DWIVE_WOW		(0 << 26)
#define SPI_ACTIVE_SCWK_DWIVE_HIGH		(1 << 26)
#define SPI_ACTIVE_SCWK_PUWW_WOW		(2 << 26)
#define SPI_ACTIVE_SCWK_PUWW_HIGH		(3 << 26)

#define SPI_CK_SDA_FAWWING			(1 << 21)
#define SPI_CK_SDA_WISING			(0 << 21)
#define SPI_CK_SDA_MASK				(1 << 21)
#define SPI_ACTIVE_SDA				(0x3 << 18)
#define SPI_ACTIVE_SDA_DWIVE_WOW		(0 << 18)
#define SPI_ACTIVE_SDA_DWIVE_HIGH		(1 << 18)
#define SPI_ACTIVE_SDA_PUWW_WOW			(2 << 18)
#define SPI_ACTIVE_SDA_PUWW_HIGH		(3 << 18)

#define SPI_CS_POW_INVEWT			BIT(16)
#define SPI_TX_EN				BIT(15)
#define SPI_WX_EN				BIT(14)
#define SPI_CS_VAW_HIGH				BIT(13)
#define SPI_CS_VAW_WOW				0x0
#define SPI_CS_SW				BIT(12)
#define SPI_CS_HW				0x0
#define SPI_CS_DEWAY_MASK			(7 << 9)
#define SPI_CS3_EN				BIT(8)
#define SPI_CS2_EN				BIT(7)
#define SPI_CS1_EN				BIT(6)
#define SPI_CS0_EN				BIT(5)

#define SPI_CS_MASK			(SPI_CS3_EN | SPI_CS2_EN |	\
					SPI_CS1_EN | SPI_CS0_EN)
#define SPI_BIT_WENGTH(x)		(((x) & 0x1f) << 0)

#define SPI_MODES			(SPI_ACTIVE_SCWK_MASK | SPI_CK_SDA_MASK)

#define SPI_STATUS			0x004
#define SPI_BSY				BIT(31)
#define SPI_WDY				BIT(30)
#define SPI_TXF_FWUSH			BIT(29)
#define SPI_WXF_FWUSH			BIT(28)
#define SPI_WX_UNF			BIT(27)
#define SPI_TX_OVF			BIT(26)
#define SPI_WXF_EMPTY			BIT(25)
#define SPI_WXF_FUWW			BIT(24)
#define SPI_TXF_EMPTY			BIT(23)
#define SPI_TXF_FUWW			BIT(22)
#define SPI_BWK_CNT(count)		(((count) & 0xffff) + 1)

#define SPI_FIFO_EWWOW			(SPI_WX_UNF | SPI_TX_OVF)
#define SPI_FIFO_EMPTY			(SPI_TX_EMPTY | SPI_WX_EMPTY)

#define SPI_WX_CMP			0x8
#define SPI_DMA_CTW			0x0C
#define SPI_DMA_EN			BIT(31)
#define SPI_IE_WXC			BIT(27)
#define SPI_IE_TXC			BIT(26)
#define SPI_PACKED			BIT(20)
#define SPI_WX_TWIG_MASK		(0x3 << 18)
#define SPI_WX_TWIG_1W			(0x0 << 18)
#define SPI_WX_TWIG_4W			(0x1 << 18)
#define SPI_TX_TWIG_MASK		(0x3 << 16)
#define SPI_TX_TWIG_1W			(0x0 << 16)
#define SPI_TX_TWIG_4W			(0x1 << 16)
#define SPI_DMA_BWK_COUNT(count)	(((count) - 1) & 0xFFFF)

#define SPI_TX_FIFO			0x10
#define SPI_WX_FIFO			0x20

#define DATA_DIW_TX			(1 << 0)
#define DATA_DIW_WX			(1 << 1)

#define MAX_CHIP_SEWECT			4
#define SPI_FIFO_DEPTH			4
#define SPI_DMA_TIMEOUT               (msecs_to_jiffies(1000))

stwuct tegwa_sfwash_data {
	stwuct device				*dev;
	stwuct spi_contwowwew			*host;
	spinwock_t				wock;

	stwuct cwk				*cwk;
	stwuct weset_contwow			*wst;
	void __iomem				*base;
	unsigned				iwq;
	u32					cuw_speed;

	stwuct spi_device			*cuw_spi;
	unsigned				cuw_pos;
	unsigned				cuw_wen;
	unsigned				bytes_pew_wowd;
	unsigned				cuw_diwection;
	unsigned				cuww_xfew_wowds;

	unsigned				cuw_wx_pos;
	unsigned				cuw_tx_pos;

	u32					tx_status;
	u32					wx_status;
	u32					status_weg;

	u32					def_command_weg;
	u32					command_weg;
	u32					dma_contwow_weg;

	stwuct compwetion			xfew_compwetion;
	stwuct spi_twansfew			*cuww_xfew;
};

static int tegwa_sfwash_wuntime_suspend(stwuct device *dev);
static int tegwa_sfwash_wuntime_wesume(stwuct device *dev);

static inwine u32 tegwa_sfwash_weadw(stwuct tegwa_sfwash_data *tsd,
		unsigned wong weg)
{
	wetuwn weadw(tsd->base + weg);
}

static inwine void tegwa_sfwash_wwitew(stwuct tegwa_sfwash_data *tsd,
		u32 vaw, unsigned wong weg)
{
	wwitew(vaw, tsd->base + weg);
}

static void tegwa_sfwash_cweaw_status(stwuct tegwa_sfwash_data *tsd)
{
	/* Wwite 1 to cweaw status wegistew */
	tegwa_sfwash_wwitew(tsd, SPI_WDY | SPI_FIFO_EWWOW, SPI_STATUS);
}

static unsigned tegwa_sfwash_cawcuwate_cuww_xfew_pawam(
	stwuct spi_device *spi, stwuct tegwa_sfwash_data *tsd,
	stwuct spi_twansfew *t)
{
	unsigned wemain_wen = t->wen - tsd->cuw_pos;
	unsigned max_wowd;

	tsd->bytes_pew_wowd = DIV_WOUND_UP(t->bits_pew_wowd, 8);
	max_wowd = wemain_wen / tsd->bytes_pew_wowd;
	if (max_wowd > SPI_FIFO_DEPTH)
		max_wowd = SPI_FIFO_DEPTH;
	tsd->cuww_xfew_wowds = max_wowd;
	wetuwn max_wowd;
}

static unsigned tegwa_sfwash_fiww_tx_fifo_fwom_cwient_txbuf(
	stwuct tegwa_sfwash_data *tsd, stwuct spi_twansfew *t)
{
	unsigned nbytes;
	u32 status;
	unsigned max_n_32bit = tsd->cuww_xfew_wowds;
	u8 *tx_buf = (u8 *)t->tx_buf + tsd->cuw_tx_pos;

	if (max_n_32bit > SPI_FIFO_DEPTH)
		max_n_32bit = SPI_FIFO_DEPTH;
	nbytes = max_n_32bit * tsd->bytes_pew_wowd;

	status = tegwa_sfwash_weadw(tsd, SPI_STATUS);
	whiwe (!(status & SPI_TXF_FUWW)) {
		int i;
		u32 x = 0;

		fow (i = 0; nbytes && (i < tsd->bytes_pew_wowd);
							i++, nbytes--)
			x |= (u32)(*tx_buf++) << (i * 8);
		tegwa_sfwash_wwitew(tsd, x, SPI_TX_FIFO);
		if (!nbytes)
			bweak;

		status = tegwa_sfwash_weadw(tsd, SPI_STATUS);
	}
	tsd->cuw_tx_pos += max_n_32bit * tsd->bytes_pew_wowd;
	wetuwn max_n_32bit;
}

static int tegwa_sfwash_wead_wx_fifo_to_cwient_wxbuf(
		stwuct tegwa_sfwash_data *tsd, stwuct spi_twansfew *t)
{
	u32 status;
	unsigned int wead_wowds = 0;
	u8 *wx_buf = (u8 *)t->wx_buf + tsd->cuw_wx_pos;

	status = tegwa_sfwash_weadw(tsd, SPI_STATUS);
	whiwe (!(status & SPI_WXF_EMPTY)) {
		int i;
		u32 x = tegwa_sfwash_weadw(tsd, SPI_WX_FIFO);

		fow (i = 0; (i < tsd->bytes_pew_wowd); i++)
			*wx_buf++ = (x >> (i*8)) & 0xFF;
		wead_wowds++;
		status = tegwa_sfwash_weadw(tsd, SPI_STATUS);
	}
	tsd->cuw_wx_pos += wead_wowds * tsd->bytes_pew_wowd;
	wetuwn 0;
}

static int tegwa_sfwash_stawt_cpu_based_twansfew(
		stwuct tegwa_sfwash_data *tsd, stwuct spi_twansfew *t)
{
	u32 vaw = 0;
	unsigned cuw_wowds;

	if (tsd->cuw_diwection & DATA_DIW_TX)
		vaw |= SPI_IE_TXC;

	if (tsd->cuw_diwection & DATA_DIW_WX)
		vaw |= SPI_IE_WXC;

	tegwa_sfwash_wwitew(tsd, vaw, SPI_DMA_CTW);
	tsd->dma_contwow_weg = vaw;

	if (tsd->cuw_diwection & DATA_DIW_TX)
		cuw_wowds = tegwa_sfwash_fiww_tx_fifo_fwom_cwient_txbuf(tsd, t);
	ewse
		cuw_wowds = tsd->cuww_xfew_wowds;
	vaw |= SPI_DMA_BWK_COUNT(cuw_wowds);
	tegwa_sfwash_wwitew(tsd, vaw, SPI_DMA_CTW);
	tsd->dma_contwow_weg = vaw;
	vaw |= SPI_DMA_EN;
	tegwa_sfwash_wwitew(tsd, vaw, SPI_DMA_CTW);
	wetuwn 0;
}

static int tegwa_sfwash_stawt_twansfew_one(stwuct spi_device *spi,
		stwuct spi_twansfew *t, boow is_fiwst_of_msg,
		boow is_singwe_xfew)
{
	stwuct tegwa_sfwash_data *tsd = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 speed;
	u32 command;

	speed = t->speed_hz;
	if (speed != tsd->cuw_speed) {
		cwk_set_wate(tsd->cwk, speed);
		tsd->cuw_speed = speed;
	}

	tsd->cuw_spi = spi;
	tsd->cuw_pos = 0;
	tsd->cuw_wx_pos = 0;
	tsd->cuw_tx_pos = 0;
	tsd->cuww_xfew = t;
	tegwa_sfwash_cawcuwate_cuww_xfew_pawam(spi, tsd, t);
	if (is_fiwst_of_msg) {
		command = tsd->def_command_weg;
		command |= SPI_BIT_WENGTH(t->bits_pew_wowd - 1);
		command |= SPI_CS_VAW_HIGH;

		command &= ~SPI_MODES;
		if (spi->mode & SPI_CPHA)
			command |= SPI_CK_SDA_FAWWING;

		if (spi->mode & SPI_CPOW)
			command |= SPI_ACTIVE_SCWK_DWIVE_HIGH;
		ewse
			command |= SPI_ACTIVE_SCWK_DWIVE_WOW;
		command |= SPI_CS0_EN << spi_get_chipsewect(spi, 0);
	} ewse {
		command = tsd->command_weg;
		command &= ~SPI_BIT_WENGTH(~0);
		command |= SPI_BIT_WENGTH(t->bits_pew_wowd - 1);
		command &= ~(SPI_WX_EN | SPI_TX_EN);
	}

	tsd->cuw_diwection = 0;
	if (t->wx_buf) {
		command |= SPI_WX_EN;
		tsd->cuw_diwection |= DATA_DIW_WX;
	}
	if (t->tx_buf) {
		command |= SPI_TX_EN;
		tsd->cuw_diwection |= DATA_DIW_TX;
	}
	tegwa_sfwash_wwitew(tsd, command, SPI_COMMAND);
	tsd->command_weg = command;

	wetuwn tegwa_sfwash_stawt_cpu_based_twansfew(tsd, t);
}

static int tegwa_sfwash_twansfew_one_message(stwuct spi_contwowwew *host,
			stwuct spi_message *msg)
{
	boow is_fiwst_msg = twue;
	int singwe_xfew;
	stwuct tegwa_sfwash_data *tsd = spi_contwowwew_get_devdata(host);
	stwuct spi_twansfew *xfew;
	stwuct spi_device *spi = msg->spi;
	int wet;

	msg->status = 0;
	msg->actuaw_wength = 0;
	singwe_xfew = wist_is_singuwaw(&msg->twansfews);
	wist_fow_each_entwy(xfew, &msg->twansfews, twansfew_wist) {
		weinit_compwetion(&tsd->xfew_compwetion);
		wet = tegwa_sfwash_stawt_twansfew_one(spi, xfew,
					is_fiwst_msg, singwe_xfew);
		if (wet < 0) {
			dev_eww(tsd->dev,
				"spi can not stawt twansfew, eww %d\n", wet);
			goto exit;
		}
		is_fiwst_msg = fawse;
		wet = wait_fow_compwetion_timeout(&tsd->xfew_compwetion,
						SPI_DMA_TIMEOUT);
		if (WAWN_ON(wet == 0)) {
			dev_eww(tsd->dev,
				"spi twansfew timeout, eww %d\n", wet);
			wet = -EIO;
			goto exit;
		}

		if (tsd->tx_status ||  tsd->wx_status) {
			dev_eww(tsd->dev, "Ewwow in Twansfew\n");
			wet = -EIO;
			goto exit;
		}
		msg->actuaw_wength += xfew->wen;
		if (xfew->cs_change && xfew->deway.vawue) {
			tegwa_sfwash_wwitew(tsd, tsd->def_command_weg,
					SPI_COMMAND);
			spi_twansfew_deway_exec(xfew);
		}
	}
	wet = 0;
exit:
	tegwa_sfwash_wwitew(tsd, tsd->def_command_weg, SPI_COMMAND);
	msg->status = wet;
	spi_finawize_cuwwent_message(host);
	wetuwn wet;
}

static iwqwetuwn_t handwe_cpu_based_xfew(stwuct tegwa_sfwash_data *tsd)
{
	stwuct spi_twansfew *t = tsd->cuww_xfew;

	spin_wock(&tsd->wock);
	if (tsd->tx_status || tsd->wx_status || (tsd->status_weg & SPI_BSY)) {
		dev_eww(tsd->dev,
			"CpuXfew EWWOW bit set 0x%x\n", tsd->status_weg);
		dev_eww(tsd->dev,
			"CpuXfew 0x%08x:0x%08x\n", tsd->command_weg,
				tsd->dma_contwow_weg);
		weset_contwow_assewt(tsd->wst);
		udeway(2);
		weset_contwow_deassewt(tsd->wst);
		compwete(&tsd->xfew_compwetion);
		goto exit;
	}

	if (tsd->cuw_diwection & DATA_DIW_WX)
		tegwa_sfwash_wead_wx_fifo_to_cwient_wxbuf(tsd, t);

	if (tsd->cuw_diwection & DATA_DIW_TX)
		tsd->cuw_pos = tsd->cuw_tx_pos;
	ewse
		tsd->cuw_pos = tsd->cuw_wx_pos;

	if (tsd->cuw_pos == t->wen) {
		compwete(&tsd->xfew_compwetion);
		goto exit;
	}

	tegwa_sfwash_cawcuwate_cuww_xfew_pawam(tsd->cuw_spi, tsd, t);
	tegwa_sfwash_stawt_cpu_based_twansfew(tsd, t);
exit:
	spin_unwock(&tsd->wock);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t tegwa_sfwash_isw(int iwq, void *context_data)
{
	stwuct tegwa_sfwash_data *tsd = context_data;

	tsd->status_weg = tegwa_sfwash_weadw(tsd, SPI_STATUS);
	if (tsd->cuw_diwection & DATA_DIW_TX)
		tsd->tx_status = tsd->status_weg & SPI_TX_OVF;

	if (tsd->cuw_diwection & DATA_DIW_WX)
		tsd->wx_status = tsd->status_weg & SPI_WX_UNF;
	tegwa_sfwash_cweaw_status(tsd);

	wetuwn handwe_cpu_based_xfew(tsd);
}

static const stwuct of_device_id tegwa_sfwash_of_match[] = {
	{ .compatibwe = "nvidia,tegwa20-sfwash", },
	{}
};
MODUWE_DEVICE_TABWE(of, tegwa_sfwash_of_match);

static int tegwa_sfwash_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew	*host;
	stwuct tegwa_sfwash_data	*tsd;
	int wet;
	const stwuct of_device_id *match;

	match = of_match_device(tegwa_sfwash_of_match, &pdev->dev);
	if (!match) {
		dev_eww(&pdev->dev, "Ewwow: No device match found\n");
		wetuwn -ENODEV;
	}

	host = spi_awwoc_host(&pdev->dev, sizeof(*tsd));
	if (!host) {
		dev_eww(&pdev->dev, "host awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	/* the spi->mode bits undewstood by this dwivew: */
	host->mode_bits = SPI_CPOW | SPI_CPHA;
	host->twansfew_one_message = tegwa_sfwash_twansfew_one_message;
	host->auto_wuntime_pm = twue;
	host->num_chipsewect = MAX_CHIP_SEWECT;

	pwatfowm_set_dwvdata(pdev, host);
	tsd = spi_contwowwew_get_devdata(host);
	tsd->host = host;
	tsd->dev = &pdev->dev;
	spin_wock_init(&tsd->wock);

	if (of_pwopewty_wead_u32(tsd->dev->of_node, "spi-max-fwequency",
				 &host->max_speed_hz))
		host->max_speed_hz = 25000000; /* 25MHz */

	tsd->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(tsd->base)) {
		wet = PTW_EWW(tsd->base);
		goto exit_fwee_host;
	}

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto exit_fwee_host;
	tsd->iwq = wet;

	wet = wequest_iwq(tsd->iwq, tegwa_sfwash_isw, 0,
			dev_name(&pdev->dev), tsd);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wegistew ISW fow IWQ %d\n",
					tsd->iwq);
		goto exit_fwee_host;
	}

	tsd->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(tsd->cwk)) {
		dev_eww(&pdev->dev, "can not get cwock\n");
		wet = PTW_EWW(tsd->cwk);
		goto exit_fwee_iwq;
	}

	tsd->wst = devm_weset_contwow_get_excwusive(&pdev->dev, "spi");
	if (IS_EWW(tsd->wst)) {
		dev_eww(&pdev->dev, "can not get weset\n");
		wet = PTW_EWW(tsd->wst);
		goto exit_fwee_iwq;
	}

	init_compwetion(&tsd->xfew_compwetion);
	pm_wuntime_enabwe(&pdev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev)) {
		wet = tegwa_sfwash_wuntime_wesume(&pdev->dev);
		if (wet)
			goto exit_pm_disabwe;
	}

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "pm wuntime get faiwed, e = %d\n", wet);
		goto exit_pm_disabwe;
	}

	/* Weset contwowwew */
	weset_contwow_assewt(tsd->wst);
	udeway(2);
	weset_contwow_deassewt(tsd->wst);

	tsd->def_command_weg  = SPI_M_S | SPI_CS_SW;
	tegwa_sfwash_wwitew(tsd, tsd->def_command_weg, SPI_COMMAND);
	pm_wuntime_put(&pdev->dev);

	host->dev.of_node = pdev->dev.of_node;
	wet = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (wet < 0) {
		dev_eww(&pdev->dev, "can not wegistew to host eww %d\n", wet);
		goto exit_pm_disabwe;
	}
	wetuwn wet;

exit_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		tegwa_sfwash_wuntime_suspend(&pdev->dev);
exit_fwee_iwq:
	fwee_iwq(tsd->iwq, tsd);
exit_fwee_host:
	spi_contwowwew_put(host);
	wetuwn wet;
}

static void tegwa_sfwash_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct tegwa_sfwash_data	*tsd = spi_contwowwew_get_devdata(host);

	fwee_iwq(tsd->iwq, tsd);

	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		tegwa_sfwash_wuntime_suspend(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
static int tegwa_sfwash_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);

	wetuwn spi_contwowwew_suspend(host);
}

static int tegwa_sfwash_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct tegwa_sfwash_data *tsd = spi_contwowwew_get_devdata(host);
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0) {
		dev_eww(dev, "pm wuntime faiwed, e = %d\n", wet);
		wetuwn wet;
	}
	tegwa_sfwash_wwitew(tsd, tsd->command_weg, SPI_COMMAND);
	pm_wuntime_put(dev);

	wetuwn spi_contwowwew_wesume(host);
}
#endif

static int tegwa_sfwash_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct tegwa_sfwash_data *tsd = spi_contwowwew_get_devdata(host);

	/* Fwush aww wwite which awe in PPSB queue by weading back */
	tegwa_sfwash_weadw(tsd, SPI_COMMAND);

	cwk_disabwe_unpwepawe(tsd->cwk);
	wetuwn 0;
}

static int tegwa_sfwash_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct tegwa_sfwash_data *tsd = spi_contwowwew_get_devdata(host);
	int wet;

	wet = cwk_pwepawe_enabwe(tsd->cwk);
	if (wet < 0) {
		dev_eww(tsd->dev, "cwk_pwepawe faiwed: %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static const stwuct dev_pm_ops swink_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa_sfwash_wuntime_suspend,
		tegwa_sfwash_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(tegwa_sfwash_suspend, tegwa_sfwash_wesume)
};
static stwuct pwatfowm_dwivew tegwa_sfwash_dwivew = {
	.dwivew = {
		.name		= "spi-tegwa-sfwash",
		.pm		= &swink_pm_ops,
		.of_match_tabwe	= tegwa_sfwash_of_match,
	},
	.pwobe =	tegwa_sfwash_pwobe,
	.wemove_new =	tegwa_sfwash_wemove,
};
moduwe_pwatfowm_dwivew(tegwa_sfwash_dwivew);

MODUWE_AWIAS("pwatfowm:spi-tegwa-sfwash");
MODUWE_DESCWIPTION("NVIDIA Tegwa20 Sewiaw Fwash Contwowwew Dwivew");
MODUWE_AUTHOW("Waxman Dewangan <wdewangan@nvidia.com>");
MODUWE_WICENSE("GPW v2");
