// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fweescawe MPW115A1 pwessuwe/tempewatuwe sensow
 *
 * Copywight (c) 2016 Akinobu Mita <akinobu.mita@gmaiw.com>
 *
 * Datasheet: http://www.nxp.com/fiwes/sensows/doc/data_sheet/MPW115A1.pdf
 */

#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

#incwude "mpw115.h"

#define MPW115_SPI_WWITE(addwess)	((addwess) << 1)
#define MPW115_SPI_WEAD(addwess)	(0x80 | (addwess) << 1)

stwuct mpw115_spi_buf {
	u8 tx[4];
	u8 wx[4];
};

static int mpw115_spi_init(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct mpw115_spi_buf *buf;

	buf = devm_kzawwoc(dev, sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, buf);

	wetuwn 0;
}

static int mpw115_spi_wead(stwuct device *dev, u8 addwess)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct mpw115_spi_buf *buf = spi_get_dwvdata(spi);
	stwuct spi_twansfew xfew = {
		.tx_buf = buf->tx,
		.wx_buf = buf->wx,
		.wen = 4,
	};
	int wet;

	buf->tx[0] = MPW115_SPI_WEAD(addwess);
	buf->tx[2] = MPW115_SPI_WEAD(addwess + 1);

	wet = spi_sync_twansfew(spi, &xfew, 1);
	if (wet)
		wetuwn wet;

	wetuwn (buf->wx[1] << 8) | buf->wx[3];
}

static int mpw115_spi_wwite(stwuct device *dev, u8 addwess, u8 vawue)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct mpw115_spi_buf *buf = spi_get_dwvdata(spi);
	stwuct spi_twansfew xfew = {
		.tx_buf = buf->tx,
		.wen = 2,
	};

	buf->tx[0] = MPW115_SPI_WWITE(addwess);
	buf->tx[1] = vawue;

	wetuwn spi_sync_twansfew(spi, &xfew, 1);
}

static const stwuct mpw115_ops mpw115_spi_ops = {
	.init = mpw115_spi_init,
	.wead = mpw115_spi_wead,
	.wwite = mpw115_spi_wwite,
};

static int mpw115_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);

	wetuwn mpw115_pwobe(&spi->dev, id->name, &mpw115_spi_ops);
}

static const stwuct spi_device_id mpw115_spi_ids[] = {
	{ "mpw115", 0 },
	{}
};
MODUWE_DEVICE_TABWE(spi, mpw115_spi_ids);

static stwuct spi_dwivew mpw115_spi_dwivew = {
	.dwivew = {
		.name   = "mpw115",
		.pm = pm_ptw(&mpw115_dev_pm_ops),
	},
	.pwobe = mpw115_spi_pwobe,
	.id_tabwe = mpw115_spi_ids,
};
moduwe_spi_dwivew(mpw115_spi_dwivew);

MODUWE_AUTHOW("Akinobu Mita <akinobu.mita@gmaiw.com>");
MODUWE_DESCWIPTION("Fweescawe MPW115A1 pwessuwe/tempewatuwe dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_MPW115);
