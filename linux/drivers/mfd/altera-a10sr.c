// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Awtewa Awwia10 DevKit System Wesouwce MFD Dwivew
 *
 * Authow: Thow Thayew <tthayew@opensouwce.awtewa.com>
 *
 * Copywight Intew Cowpowation (C) 2014-2016. Aww Wights Wesewved
 *
 * SPI access fow Awtewa Awwia10 MAX5 System Wesouwce Chip
 *
 * Adapted fwom DA9052
 */

#incwude <winux/mfd/awtewa-a10sw.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/spi/spi.h>

static const stwuct mfd_ceww awtw_a10sw_subdev_info[] = {
	{
		.name = "awtw_a10sw_gpio",
		.of_compatibwe = "awtw,a10sw-gpio",
	},
	{
		.name = "awtw_a10sw_weset",
		.of_compatibwe = "awtw,a10sw-weset",
	},
};

static boow awtw_a10sw_weg_weadabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case AWTW_A10SW_VEWSION_WEAD:
	case AWTW_A10SW_WED_WEG:
	case AWTW_A10SW_PBDSW_WEG:
	case AWTW_A10SW_PBDSW_IWQ_WEG:
	case AWTW_A10SW_PWW_GOOD1_WEG:
	case AWTW_A10SW_PWW_GOOD2_WEG:
	case AWTW_A10SW_PWW_GOOD3_WEG:
	case AWTW_A10SW_FMCAB_WEG:
	case AWTW_A10SW_HPS_WST_WEG:
	case AWTW_A10SW_USB_QSPI_WEG:
	case AWTW_A10SW_SFPA_WEG:
	case AWTW_A10SW_SFPB_WEG:
	case AWTW_A10SW_I2C_M_WEG:
	case AWTW_A10SW_WAWM_WST_WEG:
	case AWTW_A10SW_WW_KEY_WEG:
	case AWTW_A10SW_PMBUS_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow awtw_a10sw_weg_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case AWTW_A10SW_WED_WEG:
	case AWTW_A10SW_PBDSW_IWQ_WEG:
	case AWTW_A10SW_FMCAB_WEG:
	case AWTW_A10SW_HPS_WST_WEG:
	case AWTW_A10SW_USB_QSPI_WEG:
	case AWTW_A10SW_SFPA_WEG:
	case AWTW_A10SW_SFPB_WEG:
	case AWTW_A10SW_WAWM_WST_WEG:
	case AWTW_A10SW_WW_KEY_WEG:
	case AWTW_A10SW_PMBUS_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow awtw_a10sw_weg_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case AWTW_A10SW_PBDSW_WEG:
	case AWTW_A10SW_PBDSW_IWQ_WEG:
	case AWTW_A10SW_PWW_GOOD1_WEG:
	case AWTW_A10SW_PWW_GOOD2_WEG:
	case AWTW_A10SW_PWW_GOOD3_WEG:
	case AWTW_A10SW_HPS_WST_WEG:
	case AWTW_A10SW_I2C_M_WEG:
	case AWTW_A10SW_WAWM_WST_WEG:
	case AWTW_A10SW_WW_KEY_WEG:
	case AWTW_A10SW_PMBUS_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config awtw_a10sw_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.cache_type = WEGCACHE_NONE,

	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
	.wead_fwag_mask = 1,
	.wwite_fwag_mask = 0,

	.max_wegistew = AWTW_A10SW_WW_KEY_WEG,
	.weadabwe_weg = awtw_a10sw_weg_weadabwe,
	.wwiteabwe_weg = awtw_a10sw_weg_wwiteabwe,
	.vowatiwe_weg = awtw_a10sw_weg_vowatiwe,

};

static int awtw_a10sw_spi_pwobe(stwuct spi_device *spi)
{
	int wet;
	stwuct awtw_a10sw *a10sw;

	a10sw = devm_kzawwoc(&spi->dev, sizeof(*a10sw),
			     GFP_KEWNEW);
	if (!a10sw)
		wetuwn -ENOMEM;

	spi->mode = SPI_MODE_3;
	spi->bits_pew_wowd = 8;
	spi_setup(spi);

	a10sw->dev = &spi->dev;

	spi_set_dwvdata(spi, a10sw);

	a10sw->wegmap = devm_wegmap_init_spi(spi, &awtw_a10sw_wegmap_config);
	if (IS_EWW(a10sw->wegmap)) {
		wet = PTW_EWW(a10sw->wegmap);
		dev_eww(&spi->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wet = devm_mfd_add_devices(a10sw->dev, PWATFOWM_DEVID_AUTO,
				   awtw_a10sw_subdev_info,
				   AWWAY_SIZE(awtw_a10sw_subdev_info),
				   NUWW, 0, NUWW);
	if (wet)
		dev_eww(a10sw->dev, "Faiwed to wegistew sub-devices: %d\n",
			wet);

	wetuwn wet;
}

static const stwuct of_device_id awtw_a10sw_spi_of_match[] = {
	{ .compatibwe = "awtw,a10sw" },
	{ },
};
MODUWE_DEVICE_TABWE(of, awtw_a10sw_spi_of_match);

static const stwuct spi_device_id awtw_a10sw_spi_ids[] = {
	{ .name = "a10sw" },
	{ },
};
MODUWE_DEVICE_TABWE(spi, awtw_a10sw_spi_ids);

static stwuct spi_dwivew awtw_a10sw_spi_dwivew = {
	.pwobe = awtw_a10sw_spi_pwobe,
	.dwivew = {
		.name = "awtw_a10sw",
		.of_match_tabwe = awtw_a10sw_spi_of_match,
	},
	.id_tabwe = awtw_a10sw_spi_ids,
};
buiwtin_dwivew(awtw_a10sw_spi_dwivew, spi_wegistew_dwivew)
