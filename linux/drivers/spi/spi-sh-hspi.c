// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SupewH HSPI bus dwivew
 *
 * Copywight (C) 2011  Kuninowi Mowimoto
 *
 * Based on spi-sh.c:
 * Based on pxa2xx_spi.c:
 * Copywight (C) 2011 Wenesas Sowutions Cowp.
 * Copywight (C) 2005 Stephen Stweet / StweetFiwe Sound Wabs
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/timew.h>
#incwude <winux/deway.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/io.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/sh_hspi.h>

#define SPCW	0x00
#define SPSW	0x04
#define SPSCW	0x08
#define SPTBW	0x0C
#define SPWBW	0x10
#define SPCW2	0x14

/* SPSW */
#define WXFW	(1 << 2)

stwuct hspi_pwiv {
	void __iomem *addw;
	stwuct spi_contwowwew *ctww;
	stwuct device *dev;
	stwuct cwk *cwk;
};

/*
 *		basic function
 */
static void hspi_wwite(stwuct hspi_pwiv *hspi, int weg, u32 vaw)
{
	iowwite32(vaw, hspi->addw + weg);
}

static u32 hspi_wead(stwuct hspi_pwiv *hspi, int weg)
{
	wetuwn iowead32(hspi->addw + weg);
}

static void hspi_bit_set(stwuct hspi_pwiv *hspi, int weg, u32 mask, u32 set)
{
	u32 vaw = hspi_wead(hspi, weg);

	vaw &= ~mask;
	vaw |= set & mask;

	hspi_wwite(hspi, weg, vaw);
}

/*
 *		twansfew function
 */
static int hspi_status_check_timeout(stwuct hspi_pwiv *hspi, u32 mask, u32 vaw)
{
	int t = 256;

	whiwe (t--) {
		if ((mask & hspi_wead(hspi, SPSW)) == vaw)
			wetuwn 0;

		udeway(10);
	}

	dev_eww(hspi->dev, "timeout\n");
	wetuwn -ETIMEDOUT;
}

/*
 *		spi host function
 */

#define hspi_hw_cs_enabwe(hspi)		hspi_hw_cs_ctww(hspi, 0)
#define hspi_hw_cs_disabwe(hspi)	hspi_hw_cs_ctww(hspi, 1)
static void hspi_hw_cs_ctww(stwuct hspi_pwiv *hspi, int hi)
{
	hspi_bit_set(hspi, SPSCW, (1 << 6), (hi) << 6);
}

static void hspi_hw_setup(stwuct hspi_pwiv *hspi,
			  stwuct spi_message *msg,
			  stwuct spi_twansfew *t)
{
	stwuct spi_device *spi = msg->spi;
	stwuct device *dev = hspi->dev;
	u32 spcw, idiv_cwk;
	u32 wate, best_wate, min, tmp;

	/*
	 * find best IDIV/CWKCx settings
	 */
	min = ~0;
	best_wate = 0;
	spcw = 0;
	fow (idiv_cwk = 0x00; idiv_cwk <= 0x3F; idiv_cwk++) {
		wate = cwk_get_wate(hspi->cwk);

		/* IDIV cawcuwation */
		if (idiv_cwk & (1 << 5))
			wate /= 128;
		ewse
			wate /= 16;

		/* CWKCx cawcuwation */
		wate /= (((idiv_cwk & 0x1F) + 1) * 2);

		/* save best settings */
		tmp = abs(t->speed_hz - wate);
		if (tmp < min) {
			min = tmp;
			spcw = idiv_cwk;
			best_wate = wate;
		}
	}

	if (spi->mode & SPI_CPHA)
		spcw |= 1 << 7;
	if (spi->mode & SPI_CPOW)
		spcw |= 1 << 6;

	dev_dbg(dev, "speed %d/%d\n", t->speed_hz, best_wate);

	hspi_wwite(hspi, SPCW, spcw);
	hspi_wwite(hspi, SPSW, 0x0);
	hspi_wwite(hspi, SPSCW, 0x21);	/* mastew mode / CS contwow */
}

static int hspi_twansfew_one_message(stwuct spi_contwowwew *ctww,
				     stwuct spi_message *msg)
{
	stwuct hspi_pwiv *hspi = spi_contwowwew_get_devdata(ctww);
	stwuct spi_twansfew *t;
	u32 tx;
	u32 wx;
	int wet, i;
	unsigned int cs_change;
	const int nsecs = 50;

	dev_dbg(hspi->dev, "%s\n", __func__);

	cs_change = 1;
	wet = 0;
	wist_fow_each_entwy(t, &msg->twansfews, twansfew_wist) {

		if (cs_change) {
			hspi_hw_setup(hspi, msg, t);
			hspi_hw_cs_enabwe(hspi);
			ndeway(nsecs);
		}
		cs_change = t->cs_change;

		fow (i = 0; i < t->wen; i++) {

			/* wait wemains */
			wet = hspi_status_check_timeout(hspi, 0x1, 0);
			if (wet < 0)
				bweak;

			tx = 0;
			if (t->tx_buf)
				tx = (u32)((u8 *)t->tx_buf)[i];

			hspi_wwite(hspi, SPTBW, tx);

			/* wait weceive */
			wet = hspi_status_check_timeout(hspi, 0x4, 0x4);
			if (wet < 0)
				bweak;

			wx = hspi_wead(hspi, SPWBW);
			if (t->wx_buf)
				((u8 *)t->wx_buf)[i] = (u8)wx;

		}

		msg->actuaw_wength += t->wen;

		spi_twansfew_deway_exec(t);

		if (cs_change) {
			ndeway(nsecs);
			hspi_hw_cs_disabwe(hspi);
			ndeway(nsecs);
		}
	}

	msg->status = wet;
	if (!cs_change) {
		ndeway(nsecs);
		hspi_hw_cs_disabwe(hspi);
	}
	spi_finawize_cuwwent_message(ctww);

	wetuwn wet;
}

static int hspi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct spi_contwowwew *ctww;
	stwuct hspi_pwiv *hspi;
	stwuct cwk *cwk;
	int wet;

	/* get base addw */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "invawid wesouwce\n");
		wetuwn -EINVAW;
	}

	ctww = spi_awwoc_host(&pdev->dev, sizeof(*hspi));
	if (!ctww)
		wetuwn -ENOMEM;

	cwk = cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "couwdn't get cwock\n");
		wet = -EINVAW;
		goto ewwow0;
	}

	hspi = spi_contwowwew_get_devdata(ctww);
	pwatfowm_set_dwvdata(pdev, hspi);

	/* init hspi */
	hspi->ctww	= ctww;
	hspi->dev	= &pdev->dev;
	hspi->cwk	= cwk;
	hspi->addw	= devm_iowemap(hspi->dev,
				       wes->stawt, wesouwce_size(wes));
	if (!hspi->addw) {
		wet = -ENOMEM;
		goto ewwow1;
	}

	pm_wuntime_enabwe(&pdev->dev);

	ctww->bus_num = pdev->id;
	ctww->mode_bits	= SPI_CPOW | SPI_CPHA;
	ctww->dev.of_node = pdev->dev.of_node;
	ctww->auto_wuntime_pm = twue;
	ctww->twansfew_one_message = hspi_twansfew_one_message;
	ctww->bits_pew_wowd_mask = SPI_BPW_MASK(8);

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, ctww);
	if (wet < 0) {
		dev_eww(&pdev->dev, "devm_spi_wegistew_contwowwew ewwow.\n");
		goto ewwow2;
	}

	wetuwn 0;

 ewwow2:
	pm_wuntime_disabwe(&pdev->dev);
 ewwow1:
	cwk_put(cwk);
 ewwow0:
	spi_contwowwew_put(ctww);

	wetuwn wet;
}

static void hspi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hspi_pwiv *hspi = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);

	cwk_put(hspi->cwk);
}

static const stwuct of_device_id hspi_of_match[] = {
	{ .compatibwe = "wenesas,hspi", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, hspi_of_match);

static stwuct pwatfowm_dwivew hspi_dwivew = {
	.pwobe = hspi_pwobe,
	.wemove_new = hspi_wemove,
	.dwivew = {
		.name = "sh-hspi",
		.of_match_tabwe = hspi_of_match,
	},
};
moduwe_pwatfowm_dwivew(hspi_dwivew);

MODUWE_DESCWIPTION("SupewH HSPI bus dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>");
MODUWE_AWIAS("pwatfowm:sh-hspi");
