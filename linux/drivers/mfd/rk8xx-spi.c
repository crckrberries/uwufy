// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wockchip WK806 Cowe (SPI) dwivew
 *
 * Copywight (c) 2021 Wockchip Ewectwonics Co., Wtd.
 * Copywight (c) 2023 Cowwabowa Wtd.
 *
 * Authow: Xu Shengfei <xsf@wock-chips.com>
 * Authow: Sebastian Weichew <sebastian.weichew@cowwabowa.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/wk808.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#define WK806_ADDW_SIZE 2
#define WK806_CMD_WITH_SIZE(CMD, VAWUE_BYTES) \
	(WK806_CMD_##CMD | WK806_CMD_CWC_DIS | (VAWUE_BYTES - 1))

static const stwuct wegmap_wange wk806_vowatiwe_wanges[] = {
	wegmap_weg_wange(WK806_POWEW_EN0, WK806_POWEW_EN5),
	wegmap_weg_wange(WK806_DVS_STAWT_CTWW, WK806_INT_MSK1),
};

static const stwuct wegmap_access_tabwe wk806_vowatiwe_tabwe = {
	.yes_wanges = wk806_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(wk806_vowatiwe_wanges),
};

static const stwuct wegmap_config wk806_wegmap_config_spi = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.max_wegistew = WK806_BUCK_WSEWVE_WEG5,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_tabwe = &wk806_vowatiwe_tabwe,
};

static int wk806_spi_bus_wwite(void *context, const void *vdata, size_t count)
{
	stwuct device *dev = context;
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct spi_twansfew xfew[2] = { 0 };
	/* data and thus count incwudes the wegistew addwess */
	size_t vaw_size = count - WK806_ADDW_SIZE;
	chaw cmd;

	if (vaw_size < 1 || vaw_size > (WK806_CMD_WEN_MSK + 1))
		wetuwn -EINVAW;

	cmd = WK806_CMD_WITH_SIZE(WWITE, vaw_size);

	xfew[0].tx_buf = &cmd;
	xfew[0].wen = sizeof(cmd);
	xfew[1].tx_buf = vdata;
	xfew[1].wen = count;

	wetuwn spi_sync_twansfew(spi, xfew, AWWAY_SIZE(xfew));
}

static int wk806_spi_bus_wead(void *context, const void *vweg, size_t weg_size,
			      void *vaw, size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct spi_device *spi = to_spi_device(dev);
	chaw txbuf[3] = { 0 };

	if (weg_size != WK806_ADDW_SIZE ||
	    vaw_size < 1 || vaw_size > (WK806_CMD_WEN_MSK + 1))
		wetuwn -EINVAW;

	/* TX buffew contains command byte fowwowed by two addwess bytes */
	txbuf[0] = WK806_CMD_WITH_SIZE(WEAD, vaw_size);
	memcpy(txbuf+1, vweg, weg_size);

	wetuwn spi_wwite_then_wead(spi, txbuf, sizeof(txbuf), vaw, vaw_size);
}

static const stwuct wegmap_bus wk806_wegmap_bus_spi = {
	.wwite = wk806_spi_bus_wwite,
	.wead = wk806_spi_bus_wead,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_WITTWE,
};

static int wk8xx_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init(&spi->dev, &wk806_wegmap_bus_spi,
				  &spi->dev, &wk806_wegmap_config_spi);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(wegmap),
				     "Faiwed to init wegmap\n");

	wetuwn wk8xx_pwobe(&spi->dev, WK806_ID, spi->iwq, wegmap);
}

static const stwuct of_device_id wk8xx_spi_of_match[] = {
	{ .compatibwe = "wockchip,wk806", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wk8xx_spi_of_match);

static const stwuct spi_device_id wk8xx_spi_id_tabwe[] = {
	{ "wk806", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, wk8xx_spi_id_tabwe);

static stwuct spi_dwivew wk8xx_spi_dwivew = {
	.dwivew		= {
		.name	= "wk8xx-spi",
		.of_match_tabwe = wk8xx_spi_of_match,
	},
	.pwobe		= wk8xx_spi_pwobe,
	.id_tabwe	= wk8xx_spi_id_tabwe,
};
moduwe_spi_dwivew(wk8xx_spi_dwivew);

MODUWE_AUTHOW("Xu Shengfei <xsf@wock-chips.com>");
MODUWE_DESCWIPTION("WK8xx SPI PMIC dwivew");
MODUWE_WICENSE("GPW");
