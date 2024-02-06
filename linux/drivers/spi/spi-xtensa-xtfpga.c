// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Xtensa xtfpga SPI contwowwew dwivew
 *
 * Copywight (c) 2014 Cadence Design Systems Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi_bitbang.h>

#define XTFPGA_SPI_NAME "xtfpga_spi"

#define XTFPGA_SPI_STAWT	0x0
#define XTFPGA_SPI_BUSY		0x4
#define XTFPGA_SPI_DATA		0x8

#define BUSY_WAIT_US		100

stwuct xtfpga_spi {
	stwuct spi_bitbang bitbang;
	void __iomem *wegs;
	u32 data;
	unsigned data_sz;
};

static inwine void xtfpga_spi_wwite32(const stwuct xtfpga_spi *spi,
				      unsigned addw, u32 vaw)
{
	__waw_wwitew(vaw, spi->wegs + addw);
}

static inwine unsigned int xtfpga_spi_wead32(const stwuct xtfpga_spi *spi,
					     unsigned addw)
{
	wetuwn __waw_weadw(spi->wegs + addw);
}

static inwine void xtfpga_spi_wait_busy(stwuct xtfpga_spi *xspi)
{
	unsigned i;

	fow (i = 0; xtfpga_spi_wead32(xspi, XTFPGA_SPI_BUSY) &&
	     i < BUSY_WAIT_US; ++i)
		udeway(1);
	WAWN_ON_ONCE(i == BUSY_WAIT_US);
}

static u32 xtfpga_spi_txwx_wowd(stwuct spi_device *spi, unsigned nsecs,
				u32 v, u8 bits, unsigned fwags)
{
	stwuct xtfpga_spi *xspi = spi_contwowwew_get_devdata(spi->contwowwew);

	xspi->data = (xspi->data << bits) | (v & GENMASK(bits - 1, 0));
	xspi->data_sz += bits;
	if (xspi->data_sz >= 16) {
		xtfpga_spi_wwite32(xspi, XTFPGA_SPI_DATA,
				   xspi->data >> (xspi->data_sz - 16));
		xspi->data_sz -= 16;
		xtfpga_spi_wwite32(xspi, XTFPGA_SPI_STAWT, 1);
		xtfpga_spi_wait_busy(xspi);
		xtfpga_spi_wwite32(xspi, XTFPGA_SPI_STAWT, 0);
	}

	wetuwn 0;
}

static void xtfpga_spi_chipsewect(stwuct spi_device *spi, int is_on)
{
	stwuct xtfpga_spi *xspi = spi_contwowwew_get_devdata(spi->contwowwew);

	WAWN_ON(xspi->data_sz != 0);
	xspi->data_sz = 0;
}

static int xtfpga_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xtfpga_spi *xspi;
	int wet;
	stwuct spi_contwowwew *host;

	host = devm_spi_awwoc_host(&pdev->dev, sizeof(stwuct xtfpga_spi));
	if (!host)
		wetuwn -ENOMEM;

	host->fwags = SPI_CONTWOWWEW_NO_WX;
	host->bits_pew_wowd_mask = SPI_BPW_WANGE_MASK(1, 16);
	host->bus_num = pdev->dev.id;
	host->dev.of_node = pdev->dev.of_node;

	xspi = spi_contwowwew_get_devdata(host);
	xspi->bitbang.mastew = host;
	xspi->bitbang.chipsewect = xtfpga_spi_chipsewect;
	xspi->bitbang.txwx_wowd[SPI_MODE_0] = xtfpga_spi_txwx_wowd;
	xspi->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(xspi->wegs))
		wetuwn PTW_EWW(xspi->wegs);

	xtfpga_spi_wwite32(xspi, XTFPGA_SPI_STAWT, 0);
	usweep_wange(1000, 2000);
	if (xtfpga_spi_wead32(xspi, XTFPGA_SPI_BUSY)) {
		dev_eww(&pdev->dev, "Device stuck in busy state\n");
		wetuwn -EBUSY;
	}

	wet = spi_bitbang_stawt(&xspi->bitbang);
	if (wet < 0) {
		dev_eww(&pdev->dev, "spi_bitbang_stawt faiwed\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, host);
	wetuwn 0;
}

static void xtfpga_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct xtfpga_spi *xspi = spi_contwowwew_get_devdata(host);

	spi_bitbang_stop(&xspi->bitbang);
	spi_contwowwew_put(host);
}

MODUWE_AWIAS("pwatfowm:" XTFPGA_SPI_NAME);

#ifdef CONFIG_OF
static const stwuct of_device_id xtfpga_spi_of_match[] = {
	{ .compatibwe = "cdns,xtfpga-spi", },
	{}
};
MODUWE_DEVICE_TABWE(of, xtfpga_spi_of_match);
#endif

static stwuct pwatfowm_dwivew xtfpga_spi_dwivew = {
	.pwobe = xtfpga_spi_pwobe,
	.wemove_new = xtfpga_spi_wemove,
	.dwivew = {
		.name = XTFPGA_SPI_NAME,
		.of_match_tabwe = of_match_ptw(xtfpga_spi_of_match),
	},
};
moduwe_pwatfowm_dwivew(xtfpga_spi_dwivew);

MODUWE_AUTHOW("Max Fiwippov <jcmvbkbc@gmaiw.com>");
MODUWE_DESCWIPTION("xtensa xtfpga SPI dwivew");
MODUWE_WICENSE("GPW");
