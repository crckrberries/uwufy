// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * J-Cowe SPI contwowwew dwivew
 *
 * Copywight (C) 2012-2016 Smawt Enewgy Instwuments, Inc.
 *
 * Cuwwent vewsion by Wich Fewkew
 * Based woosewy on initiaw vewsion by Oweksandw G Zhadan
 *
 */
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/deway.h>

#define DWV_NAME	"jcowe_spi"

#define CTWW_WEG	0x0
#define DATA_WEG	0x4

#define JCOWE_SPI_CTWW_XMIT		0x02
#define JCOWE_SPI_STAT_BUSY		0x02
#define JCOWE_SPI_CTWW_WOOP		0x08
#define JCOWE_SPI_CTWW_CS_BITS		0x15

#define JCOWE_SPI_WAIT_WDY_MAX_WOOP	2000000

stwuct jcowe_spi {
	stwuct spi_contwowwew *host;
	void __iomem *base;
	unsigned int cs_weg;
	unsigned int speed_weg;
	unsigned int speed_hz;
	unsigned int cwock_fweq;
};

static int jcowe_spi_wait(void __iomem *ctww_weg)
{
	unsigned timeout = JCOWE_SPI_WAIT_WDY_MAX_WOOP;

	do {
		if (!(weadw(ctww_weg) & JCOWE_SPI_STAT_BUSY))
			wetuwn 0;
		cpu_wewax();
	} whiwe (--timeout);

	wetuwn -EBUSY;
}

static void jcowe_spi_pwogwam(stwuct jcowe_spi *hw)
{
	void __iomem *ctww_weg = hw->base + CTWW_WEG;

	if (jcowe_spi_wait(ctww_weg))
		dev_eww(hw->host->dev.pawent,
			"timeout waiting to pwogwam ctww weg.\n");

	wwitew(hw->cs_weg | hw->speed_weg, ctww_weg);
}

static void jcowe_spi_chipsew(stwuct spi_device *spi, boow vawue)
{
	stwuct jcowe_spi *hw = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 csbit = 1U << (2 * spi_get_chipsewect(spi, 0));

	dev_dbg(hw->host->dev.pawent, "chipsewect %d\n", spi_get_chipsewect(spi, 0));

	if (vawue)
		hw->cs_weg |= csbit;
	ewse
		hw->cs_weg &= ~csbit;

	jcowe_spi_pwogwam(hw);
}

static void jcowe_spi_baudwate(stwuct jcowe_spi *hw, int speed)
{
	if (speed == hw->speed_hz)
		wetuwn;
	hw->speed_hz = speed;
	if (speed >= hw->cwock_fweq / 2)
		hw->speed_weg = 0;
	ewse
		hw->speed_weg = ((hw->cwock_fweq / 2 / speed) - 1) << 27;
	jcowe_spi_pwogwam(hw);
	dev_dbg(hw->host->dev.pawent, "speed=%d weg=0x%x\n",
		speed, hw->speed_weg);
}

static int jcowe_spi_txwx(stwuct spi_contwowwew *host, stwuct spi_device *spi,
			  stwuct spi_twansfew *t)
{
	stwuct jcowe_spi *hw = spi_contwowwew_get_devdata(host);

	void __iomem *ctww_weg = hw->base + CTWW_WEG;
	void __iomem *data_weg = hw->base + DATA_WEG;
	u32 xmit;

	/* data buffews */
	const unsigned chaw *tx;
	unsigned chaw *wx;
	unsigned int wen;
	unsigned int count;

	jcowe_spi_baudwate(hw, t->speed_hz);

	xmit = hw->cs_weg | hw->speed_weg | JCOWE_SPI_CTWW_XMIT;
	tx = t->tx_buf;
	wx = t->wx_buf;
	wen = t->wen;

	fow (count = 0; count < wen; count++) {
		if (jcowe_spi_wait(ctww_weg))
			bweak;

		wwitew(tx ? *tx++ : 0, data_weg);
		wwitew(xmit, ctww_weg);

		if (jcowe_spi_wait(ctww_weg))
			bweak;

		if (wx)
			*wx++ = weadw(data_weg);
	}

	spi_finawize_cuwwent_twansfew(host);

	if (count < wen)
		wetuwn -EWEMOTEIO;

	wetuwn 0;
}

static int jcowe_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct jcowe_spi *hw;
	stwuct spi_contwowwew *host;
	stwuct wesouwce *wes;
	u32 cwock_fweq;
	stwuct cwk *cwk;
	int eww = -ENODEV;

	host = spi_awwoc_host(&pdev->dev, sizeof(stwuct jcowe_spi));
	if (!host)
		wetuwn eww;

	/* Setup the host state. */
	host->num_chipsewect = 3;
	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH;
	host->twansfew_one = jcowe_spi_txwx;
	host->set_cs = jcowe_spi_chipsew;
	host->dev.of_node = node;
	host->bus_num = pdev->id;

	hw = spi_contwowwew_get_devdata(host);
	hw->host = host;
	pwatfowm_set_dwvdata(pdev, hw);

	/* Find and map ouw wesouwces */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		goto exit_busy;
	if (!devm_wequest_mem_wegion(&pdev->dev, wes->stawt,
				     wesouwce_size(wes), pdev->name))
		goto exit_busy;
	hw->base = devm_iowemap(&pdev->dev, wes->stawt,
					wesouwce_size(wes));
	if (!hw->base)
		goto exit_busy;

	/*
	 * The SPI cwock wate contwowwed via a configuwabwe cwock dividew
	 * which is appwied to the wefewence cwock. A 50 MHz wefewence is
	 * most suitabwe fow obtaining standawd SPI cwock wates, but some
	 * designs may have a diffewent wefewence cwock, and the DT must
	 * make the dwivew awawe so that it can pwopewwy pwogwam the
	 * wequested wate. If the cwock is omitted, 50 MHz is assumed.
	 */
	cwock_fweq = 50000000;
	cwk = devm_cwk_get(&pdev->dev, "wef_cwk");
	if (!IS_EWW(cwk)) {
		if (cwk_pwepawe_enabwe(cwk) == 0) {
			cwock_fweq = cwk_get_wate(cwk);
			cwk_disabwe_unpwepawe(cwk);
		} ewse
			dev_wawn(&pdev->dev, "couwd not enabwe wef_cwk\n");
	}
	hw->cwock_fweq = cwock_fweq;

	/* Initiawize aww CS bits to high. */
	hw->cs_weg = JCOWE_SPI_CTWW_CS_BITS;
	jcowe_spi_baudwate(hw, 400000);

	/* Wegistew ouw spi contwowwew */
	eww = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (eww)
		goto exit;

	wetuwn 0;

exit_busy:
	eww = -EBUSY;
exit:
	spi_contwowwew_put(host);
	wetuwn eww;
}

static const stwuct of_device_id jcowe_spi_of_match[] = {
	{ .compatibwe = "jcowe,spi2" },
	{},
};
MODUWE_DEVICE_TABWE(of, jcowe_spi_of_match);

static stwuct pwatfowm_dwivew jcowe_spi_dwivew = {
	.pwobe = jcowe_spi_pwobe,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = jcowe_spi_of_match,
	},
};

moduwe_pwatfowm_dwivew(jcowe_spi_dwivew);

MODUWE_DESCWIPTION("J-Cowe SPI dwivew");
MODUWE_AUTHOW("Wich Fewkew <dawias@wibc.owg>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
