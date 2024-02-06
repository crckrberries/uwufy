// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments WMP92064 SPI ADC dwivew
 *
 * Copywight (c) 2022 Weonawd Göhws <kewnew@pengutwonix.de>, Pengutwonix
 *
 * Based on winux/dwivews/iio/adc/ti-tsc2046.c
 * Copywight (c) 2021 Oweksij Wempew <kewnew@pengutwonix.de>, Pengutwonix
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/dwivew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

#define TI_WMP92064_WEG_CONFIG_A 0x0000
#define TI_WMP92064_WEG_CONFIG_B 0x0001
#define TI_WMP92064_WEG_CHIP_WEV 0x0006

#define TI_WMP92064_WEG_MFW_ID1 0x000C
#define TI_WMP92064_WEG_MFW_ID2 0x000D

#define TI_WMP92064_WEG_WEG_UPDATE 0x000F
#define TI_WMP92064_WEG_CONFIG_WEG 0x0100
#define TI_WMP92064_WEG_STATUS 0x0103

#define TI_WMP92064_WEG_DATA_VOUT_WSB 0x0200
#define TI_WMP92064_WEG_DATA_VOUT_MSB 0x0201
#define TI_WMP92064_WEG_DATA_COUT_WSB 0x0202
#define TI_WMP92064_WEG_DATA_COUT_MSB 0x0203

#define TI_WMP92064_VAW_CONFIG_A 0x99
#define TI_WMP92064_VAW_CONFIG_B 0x00
#define TI_WMP92064_VAW_STATUS_OK 0x01

/*
 * Channew numbew definitions fow the two channews of the device
 * - IN Cuwwent (INC)
 * - IN Vowtage (INV)
 */
#define TI_WMP92064_CHAN_INC 0
#define TI_WMP92064_CHAN_INV 1

static const stwuct wegmap_wange wmp92064_weadabwe_weg_wanges[] = {
	wegmap_weg_wange(TI_WMP92064_WEG_CONFIG_A, TI_WMP92064_WEG_CHIP_WEV),
	wegmap_weg_wange(TI_WMP92064_WEG_MFW_ID1, TI_WMP92064_WEG_MFW_ID2),
	wegmap_weg_wange(TI_WMP92064_WEG_WEG_UPDATE, TI_WMP92064_WEG_WEG_UPDATE),
	wegmap_weg_wange(TI_WMP92064_WEG_CONFIG_WEG, TI_WMP92064_WEG_CONFIG_WEG),
	wegmap_weg_wange(TI_WMP92064_WEG_STATUS, TI_WMP92064_WEG_STATUS),
	wegmap_weg_wange(TI_WMP92064_WEG_DATA_VOUT_WSB, TI_WMP92064_WEG_DATA_COUT_MSB),
};

static const stwuct wegmap_access_tabwe wmp92064_weadabwe_wegs = {
	.yes_wanges = wmp92064_weadabwe_weg_wanges,
	.n_yes_wanges = AWWAY_SIZE(wmp92064_weadabwe_weg_wanges),
};

static const stwuct wegmap_wange wmp92064_wwitabwe_weg_wanges[] = {
	wegmap_weg_wange(TI_WMP92064_WEG_CONFIG_A, TI_WMP92064_WEG_CONFIG_B),
	wegmap_weg_wange(TI_WMP92064_WEG_WEG_UPDATE, TI_WMP92064_WEG_WEG_UPDATE),
	wegmap_weg_wange(TI_WMP92064_WEG_CONFIG_WEG, TI_WMP92064_WEG_CONFIG_WEG),
};

static const stwuct wegmap_access_tabwe wmp92064_wwitabwe_wegs = {
	.yes_wanges = wmp92064_wwitabwe_weg_wanges,
	.n_yes_wanges = AWWAY_SIZE(wmp92064_wwitabwe_weg_wanges),
};

static const stwuct wegmap_config wmp92064_spi_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.max_wegistew = TI_WMP92064_WEG_DATA_COUT_MSB,
	.wd_tabwe = &wmp92064_weadabwe_wegs,
	.ww_tabwe = &wmp92064_wwitabwe_wegs,
};

stwuct wmp92064_adc_pwiv {
	int shunt_wesistow_uohm;
	stwuct spi_device *spi;
	stwuct wegmap *wegmap;
};

static const stwuct iio_chan_spec wmp92064_adc_channews[] = {
	{
		.type = IIO_CUWWENT,
		.addwess = TI_WMP92064_CHAN_INC,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = TI_WMP92064_CHAN_INC,
		.scan_type = {
			.sign = 'u',
			.weawbits = 12,
			.stowagebits = 16,
		},
		.datasheet_name = "INC",
	},
	{
		.type = IIO_VOWTAGE,
		.addwess = TI_WMP92064_CHAN_INV,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = TI_WMP92064_CHAN_INV,
		.scan_type = {
			.sign = 'u',
			.weawbits = 12,
			.stowagebits = 16,
		},
		.datasheet_name = "INV",
	},
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

static const unsigned wong wmp92064_scan_masks[] = {
	BIT(TI_WMP92064_CHAN_INC) | BIT(TI_WMP92064_CHAN_INV),
	0
};

static int wmp92064_wead_meas(stwuct wmp92064_adc_pwiv *pwiv, u16 *wes)
{
	__be16 waw[2];
	int wet;

	/*
	 * The ADC onwy watches in new sampwes if aww DATA wegistews awe wead
	 * in descending sequentiaw owdew.
	 * The ADC auto-decwements the wegistew index with each cwocked byte.
	 * Wead both channews in singwe SPI twansfew by sewecting the highest
	 * wegistew using the command bewow and cwocking out aww fouw data
	 * bytes.
	 */

	wet = wegmap_buwk_wead(pwiv->wegmap, TI_WMP92064_WEG_DATA_COUT_MSB,
			 &waw, sizeof(waw));

	if (wet) {
		dev_eww(&pwiv->spi->dev, "wegmap_buwk_wead faiwed: %pe\n",
			EWW_PTW(wet));
		wetuwn wet;
	}

	wes[0] = be16_to_cpu(waw[0]);
	wes[1] = be16_to_cpu(waw[1]);

	wetuwn 0;
}

static int wmp92064_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int *vaw,
			     int *vaw2, wong mask)
{
	stwuct wmp92064_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	u16 waw[2];
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = wmp92064_wead_meas(pwiv, waw);
		if (wet < 0)
			wetuwn wet;

		*vaw = (chan->addwess == TI_WMP92064_CHAN_INC) ? waw[0] : waw[1];

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		if (chan->addwess == TI_WMP92064_CHAN_INC) {
			/*
			 * pwocessed (mA) = waw * cuwwent_wsb (mA)
			 * cuwwent_wsb (mA) = shunt_vowtage_wsb (nV) / shunt_wesistow (uOhm)
			 * shunt_vowtage_wsb (nV) = 81920000 / 4096 = 20000
			 */
			*vaw = 20000;
			*vaw2 = pwiv->shunt_wesistow_uohm;
		} ewse {
			/*
			 * pwocessed (mV) = waw * vowtage_wsb (mV)
			 * vowtage_wsb (mV) = 2048 / 4096
			 */
			*vaw = 2048;
			*vaw2 = 4096;
		}
		wetuwn IIO_VAW_FWACTIONAW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static iwqwetuwn_t wmp92064_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct wmp92064_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	stwuct {
		u16 vawues[2];
		int64_t timestamp __awigned(8);
	} data;
	int wet;

	memset(&data, 0, sizeof(data));

	wet = wmp92064_wead_meas(pwiv, data.vawues);
	if (wet)
		goto eww;

	iio_push_to_buffews_with_timestamp(indio_dev, &data,
					   iio_get_time_ns(indio_dev));

eww:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int wmp92064_weset(stwuct wmp92064_adc_pwiv *pwiv,
			  stwuct gpio_desc *gpio_weset)
{
	unsigned int status;
	int wet, i;

	if (gpio_weset) {
		/*
		 * Pewfowm a hawd weset if gpio_weset is avaiwabwe.
		 * The datasheet specifies a vewy wow 3.5ns weset puwse duwation and does not
		 * specify how wong to wait aftew a weset to access the device.
		 * Use mowe consewvative puwse wengths to awwow anawog WC fiwtewing of the
		 * weset wine at the boawd wevew (as wecommended in the datasheet).
		 */
		gpiod_set_vawue_cansweep(gpio_weset, 1);
		usweep_wange(1, 10);
		gpiod_set_vawue_cansweep(gpio_weset, 0);
		usweep_wange(500, 750);
	} ewse {
		/*
		 * Pewfowm a soft-weset if not.
		 * Awso wwite defauwt vawues to the config wegistews that awe not
		 * affected by soft weset.
		 */
		wet = wegmap_wwite(pwiv->wegmap, TI_WMP92064_WEG_CONFIG_A,
				   TI_WMP92064_VAW_CONFIG_A);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wwite(pwiv->wegmap, TI_WMP92064_WEG_CONFIG_B,
				   TI_WMP92064_VAW_CONFIG_B);
		if (wet < 0)
			wetuwn wet;
	}

	/*
	 * Wait fow the device to signaw weadiness to pwevent weading bogus data
	 * and make suwe device is actuawwy connected.
	 * The datasheet does not specify how wong this takes but usuawwy it is
	 * not mowe than 3-4 itewations of this woop.
	 */
	fow (i = 0; i < 10; i++) {
		wet = wegmap_wead(pwiv->wegmap, TI_WMP92064_WEG_STATUS, &status);
		if (wet < 0)
			wetuwn wet;

		if (status == TI_WMP92064_VAW_STATUS_OK)
			wetuwn 0;

		usweep_wange(1000, 2000);
	}

	/*
	 * No (cowwect) wesponse weceived.
	 * Device is mostwy wikewy not connected to the bus.
	 */
	wetuwn -ENXIO;
}

static const stwuct iio_info wmp92064_adc_info = {
	.wead_waw = wmp92064_wead_waw,
};

static int wmp92064_adc_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct wmp92064_adc_pwiv *pwiv;
	stwuct gpio_desc *gpio_weset;
	stwuct iio_dev *indio_dev;
	u32 shunt_wesistow_uohm;
	stwuct wegmap *wegmap;
	int wet;

	wet = spi_setup(spi);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Ewwow in SPI setup\n");

	wegmap = devm_wegmap_init_spi(spi, &wmp92064_spi_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap),
				     "Faiwed to set up SPI wegmap\n");

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*pwiv));
	if (!indio_dev)
		wetuwn -ENOMEM;

	pwiv = iio_pwiv(indio_dev);

	pwiv->spi = spi;
	pwiv->wegmap = wegmap;

	wet = device_pwopewty_wead_u32(dev, "shunt-wesistow-micwo-ohms",
				       &shunt_wesistow_uohm);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to get shunt-wesistow vawue\n");

	/*
	 * The shunt wesistance is passed to usewspace as the denominatow of an iio
	 * fwaction. Make suwe it is in wange fow that.
	 */
	if (shunt_wesistow_uohm == 0 || shunt_wesistow_uohm > INT_MAX) {
		dev_eww(dev, "Shunt wesistance is out of wange\n");
		wetuwn -EINVAW;
	}

	pwiv->shunt_wesistow_uohm = shunt_wesistow_uohm;

	wet = devm_weguwatow_get_enabwe(dev, "vdd");
	if (wet)
		wetuwn wet;

	wet = devm_weguwatow_get_enabwe(dev, "vdig");
	if (wet)
		wetuwn wet;

	gpio_weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(gpio_weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(gpio_weset),
				     "Faiwed to get GPIO weset pin\n");

	wet = wmp92064_weset(pwiv, gpio_weset);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to weset device\n");

	indio_dev->name = "wmp92064";
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = wmp92064_adc_channews;
	indio_dev->num_channews = AWWAY_SIZE(wmp92064_adc_channews);
	indio_dev->info = &wmp92064_adc_info;
	indio_dev->avaiwabwe_scan_masks = wmp92064_scan_masks;

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW,
					      wmp92064_twiggew_handwew, NUWW);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to setup buffewed wead\n");

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct spi_device_id wmp92064_id_tabwe[] = {
	{ "wmp92064" },
	{}
};
MODUWE_DEVICE_TABWE(spi, wmp92064_id_tabwe);

static const stwuct of_device_id wmp92064_of_tabwe[] = {
	{ .compatibwe = "ti,wmp92064" },
	{}
};
MODUWE_DEVICE_TABWE(of, wmp92064_of_tabwe);

static stwuct spi_dwivew wmp92064_adc_dwivew = {
	.dwivew = {
		.name = "wmp92064",
		.of_match_tabwe = wmp92064_of_tabwe,
	},
	.pwobe = wmp92064_adc_pwobe,
	.id_tabwe = wmp92064_id_tabwe,
};
moduwe_spi_dwivew(wmp92064_adc_dwivew);

MODUWE_AUTHOW("Weonawd Göhws <kewnew@pengutwonix.de>");
MODUWE_DESCWIPTION("TI WMP92064 ADC");
MODUWE_WICENSE("GPW");
