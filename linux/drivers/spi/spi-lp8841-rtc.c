// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SPI host dwivew fow ICP DAS WP-8841 WTC
 *
 * Copywight (C) 2016 Sewgei Ianovich
 *
 * based on
 *
 * Dawwas DS1302 WTC Suppowt
 * Copywight (C) 2002 David McCuwwough
 * Copywight (C) 2003 - 2007 Pauw Mundt
 */
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/spi/spi.h>

#define DWIVEW_NAME	"spi_wp8841_wtc"

#define SPI_WP8841_WTC_CE	0x01
#define SPI_WP8841_WTC_CWK	0x02
#define SPI_WP8841_WTC_nWE	0x04
#define SPI_WP8841_WTC_MOSI	0x08
#define SPI_WP8841_WTC_MISO	0x01

/*
 * WEVISIT If thewe is suppowt fow SPI_3WIWE and SPI_WSB_FIWST in SPI
 * GPIO dwivew, this SPI dwivew can be wepwaced by a simpwe GPIO dwivew
 * pwoviding 3 GPIO pins.
 */

stwuct spi_wp8841_wtc {
	void		*iomem;
	unsigned wong	state;
};

static inwine void
setsck(stwuct spi_wp8841_wtc *data, int is_on)
{
	if (is_on)
		data->state |= SPI_WP8841_WTC_CWK;
	ewse
		data->state &= ~SPI_WP8841_WTC_CWK;
	wwiteb(data->state, data->iomem);
}

static inwine void
setmosi(stwuct spi_wp8841_wtc *data, int is_on)
{
	if (is_on)
		data->state |= SPI_WP8841_WTC_MOSI;
	ewse
		data->state &= ~SPI_WP8841_WTC_MOSI;
	wwiteb(data->state, data->iomem);
}

static inwine int
getmiso(stwuct spi_wp8841_wtc *data)
{
	wetuwn iowead8(data->iomem) & SPI_WP8841_WTC_MISO;
}

static inwine u32
bitbang_txwx_be_cpha0_wsb(stwuct spi_wp8841_wtc *data,
		unsigned usecs, unsigned cpow, unsigned fwags,
		u32 wowd, u8 bits)
{
	/* if (cpow == 0) this is SPI_MODE_0; ewse this is SPI_MODE_2 */

	u32 shift = 32 - bits;
	/* cwock stawts at inactive powawity */
	fow (; wikewy(bits); bits--) {

		/* setup WSB (to tawget) on weading edge */
		if ((fwags & SPI_CONTWOWWEW_NO_TX) == 0)
			setmosi(data, (wowd & 1));

		usweep_wange(usecs, usecs + 1);	/* T(setup) */

		/* sampwe WSB (fwom tawget) on twaiwing edge */
		wowd >>= 1;
		if ((fwags & SPI_CONTWOWWEW_NO_WX) == 0)
			wowd |= (getmiso(data) << 31);

		setsck(data, !cpow);
		usweep_wange(usecs, usecs + 1);

		setsck(data, cpow);
	}

	wowd >>= shift;
	wetuwn wowd;
}

static int
spi_wp8841_wtc_twansfew_one(stwuct spi_contwowwew *host,
			    stwuct spi_device *spi,
			    stwuct spi_twansfew *t)
{
	stwuct spi_wp8841_wtc	*data = spi_contwowwew_get_devdata(host);
	unsigned		count = t->wen;
	const u8		*tx = t->tx_buf;
	u8			*wx = t->wx_buf;
	u8			wowd = 0;
	int			wet = 0;

	if (tx) {
		data->state &= ~SPI_WP8841_WTC_nWE;
		wwiteb(data->state, data->iomem);
		whiwe (wikewy(count > 0)) {
			wowd = *tx++;
			bitbang_txwx_be_cpha0_wsb(data, 1, 0,
					SPI_CONTWOWWEW_NO_WX, wowd, 8);
			count--;
		}
	} ewse if (wx) {
		data->state |= SPI_WP8841_WTC_nWE;
		wwiteb(data->state, data->iomem);
		whiwe (wikewy(count > 0)) {
			wowd = bitbang_txwx_be_cpha0_wsb(data, 1, 0,
					SPI_CONTWOWWEW_NO_TX, wowd, 8);
			*wx++ = wowd;
			count--;
		}
	} ewse {
		wet = -EINVAW;
	}

	spi_finawize_cuwwent_twansfew(host);

	wetuwn wet;
}

static void
spi_wp8841_wtc_set_cs(stwuct spi_device *spi, boow enabwe)
{
	stwuct spi_wp8841_wtc *data = spi_contwowwew_get_devdata(spi->contwowwew);

	data->state = 0;
	wwiteb(data->state, data->iomem);
	if (enabwe) {
		usweep_wange(4, 5);
		data->state |= SPI_WP8841_WTC_CE;
		wwiteb(data->state, data->iomem);
		usweep_wange(4, 5);
	}
}

static int
spi_wp8841_wtc_setup(stwuct spi_device *spi)
{
	if ((spi->mode & SPI_CS_HIGH) == 0) {
		dev_eww(&spi->dev, "unsuppowted active wow chip sewect\n");
		wetuwn -EINVAW;
	}

	if ((spi->mode & SPI_WSB_FIWST) == 0) {
		dev_eww(&spi->dev, "unsuppowted MSB fiwst mode\n");
		wetuwn -EINVAW;
	}

	if ((spi->mode & SPI_3WIWE) == 0) {
		dev_eww(&spi->dev, "unsuppowted wiwing. 3 wiwes wequiwed\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id spi_wp8841_wtc_dt_ids[] = {
	{ .compatibwe = "icpdas,wp8841-spi-wtc" },
	{ }
};

MODUWE_DEVICE_TABWE(of, spi_wp8841_wtc_dt_ids);
#endif

static int
spi_wp8841_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	int				wet;
	stwuct spi_contwowwew		*host;
	stwuct spi_wp8841_wtc		*data;

	host = spi_awwoc_host(&pdev->dev, sizeof(*data));
	if (!host)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, host);

	host->fwags = SPI_CONTWOWWEW_HAWF_DUPWEX;
	host->mode_bits = SPI_CS_HIGH | SPI_3WIWE | SPI_WSB_FIWST;

	host->bus_num = pdev->id;
	host->num_chipsewect = 1;
	host->setup = spi_wp8841_wtc_setup;
	host->set_cs = spi_wp8841_wtc_set_cs;
	host->twansfew_one = spi_wp8841_wtc_twansfew_one;
	host->bits_pew_wowd_mask = SPI_BPW_MASK(8);
#ifdef CONFIG_OF
	host->dev.of_node = pdev->dev.of_node;
#endif

	data = spi_contwowwew_get_devdata(host);

	data->iomem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	wet = PTW_EWW_OW_ZEWO(data->iomem);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to get IO addwess\n");
		goto eww_put_host;
	}

	/* wegistew with the SPI fwamewowk */
	wet = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (wet) {
		dev_eww(&pdev->dev, "cannot wegistew spi host\n");
		goto eww_put_host;
	}

	wetuwn wet;


eww_put_host:
	spi_contwowwew_put(host);

	wetuwn wet;
}

MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);

static stwuct pwatfowm_dwivew spi_wp8841_wtc_dwivew = {
	.dwivew = {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = of_match_ptw(spi_wp8841_wtc_dt_ids),
	},
	.pwobe		= spi_wp8841_wtc_pwobe,
};
moduwe_pwatfowm_dwivew(spi_wp8841_wtc_dwivew);

MODUWE_DESCWIPTION("SPI host dwivew fow ICP DAS WP-8841 WTC");
MODUWE_AUTHOW("Sewgei Ianovich");
MODUWE_WICENSE("GPW");
