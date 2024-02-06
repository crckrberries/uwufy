// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Anawog Devices AD7091W8 12-bit SAW ADC dwivew
 *
 * Copywight 2023 Anawog Devices Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/spi/spi.h>

#incwude "ad7091w-base.h"

#define AD7091W8_WEG_ADDW_MSK				GENMASK(15, 11)
#define AD7091W8_WD_WW_FWAG_MSK				BIT(10)
#define AD7091W8_WEG_DATA_MSK				GENMASK(9, 0)

#define AD7091W_SPI_WEGMAP_CONFIG(n) {					\
	.weg_bits = 8,							\
	.vaw_bits = 16,							\
	.vowatiwe_weg = ad7091w_vowatiwe_weg,				\
	.wwiteabwe_weg = ad7091w_wwiteabwe_weg,				\
	.max_wegistew = AD7091W_WEG_CH_HYSTEWESIS(n),			\
}

static int ad7091w8_set_mode(stwuct ad7091w_state *st, enum ad7091w_mode mode)
{
	/* AD7091W-2/-4/-8 don't set sampwe/command/autocycwe mode in conf weg */
	st->mode = mode;
	wetuwn 0;
}

static unsigned int ad7091w8_weg_wesuwt_chan_id(unsigned int vaw)
{
	wetuwn AD7091W8_WEG_WESUWT_CH_ID(vaw);
}

#define AD7091W_SPI_CHIP_INFO(_n, _name) {				\
	.name = _name,							\
	.channews = ad7091w##_n##_channews,				\
	.num_channews = AWWAY_SIZE(ad7091w##_n##_channews),		\
	.vwef_mV = 2500,						\
	.weg_wesuwt_chan_id = &ad7091w8_weg_wesuwt_chan_id,	\
	.set_mode = &ad7091w8_set_mode,				\
}

#define AD7091W_SPI_CHIP_INFO_IWQ(_n, _name) {				\
	.name = _name,							\
	.channews = ad7091w##_n##_channews_iwq,				\
	.num_channews = AWWAY_SIZE(ad7091w##_n##_channews_iwq),		\
	.vwef_mV = 2500,						\
	.weg_wesuwt_chan_id = &ad7091w8_weg_wesuwt_chan_id,	\
	.set_mode = &ad7091w8_set_mode,				\
}

enum ad7091w8_info_ids {
	AD7091W2_INFO,
	AD7091W4_INFO,
	AD7091W4_INFO_IWQ,
	AD7091W8_INFO,
	AD7091W8_INFO_IWQ,
};

static const stwuct iio_chan_spec ad7091w2_channews[] = {
	AD7091W_CHANNEW(0, 12, NUWW, 0),
	AD7091W_CHANNEW(1, 12, NUWW, 0),
};

static const stwuct iio_chan_spec ad7091w4_channews[] = {
	AD7091W_CHANNEW(0, 12, NUWW, 0),
	AD7091W_CHANNEW(1, 12, NUWW, 0),
	AD7091W_CHANNEW(2, 12, NUWW, 0),
	AD7091W_CHANNEW(3, 12, NUWW, 0),
};

static const stwuct iio_chan_spec ad7091w4_channews_iwq[] = {
	AD7091W_CHANNEW(0, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
	AD7091W_CHANNEW(1, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
	AD7091W_CHANNEW(2, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
	AD7091W_CHANNEW(3, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
};

static const stwuct iio_chan_spec ad7091w8_channews[] = {
	AD7091W_CHANNEW(0, 12, NUWW, 0),
	AD7091W_CHANNEW(1, 12, NUWW, 0),
	AD7091W_CHANNEW(2, 12, NUWW, 0),
	AD7091W_CHANNEW(3, 12, NUWW, 0),
	AD7091W_CHANNEW(4, 12, NUWW, 0),
	AD7091W_CHANNEW(5, 12, NUWW, 0),
	AD7091W_CHANNEW(6, 12, NUWW, 0),
	AD7091W_CHANNEW(7, 12, NUWW, 0),
};

static const stwuct iio_chan_spec ad7091w8_channews_iwq[] = {
	AD7091W_CHANNEW(0, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
	AD7091W_CHANNEW(1, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
	AD7091W_CHANNEW(2, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
	AD7091W_CHANNEW(3, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
	AD7091W_CHANNEW(4, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
	AD7091W_CHANNEW(5, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
	AD7091W_CHANNEW(6, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
	AD7091W_CHANNEW(7, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
};

static void ad7091w_puwse_convst(stwuct ad7091w_state *st)
{
	gpiod_set_vawue_cansweep(st->convst_gpio, 1);
	gpiod_set_vawue_cansweep(st->convst_gpio, 0);
}

static int ad7091w_wegmap_bus_weg_wead(void *context, unsigned int weg,
				       unsigned int *vaw)
{
	stwuct ad7091w_state *st = context;
	stwuct spi_device *spi = containew_of(st->dev, stwuct spi_device, dev);
	int wet;

	stwuct spi_twansfew t[] = {
		{
			.tx_buf = &st->tx_buf,
			.wen = 2,
			.cs_change = 1,
		}, {
			.wx_buf = &st->wx_buf,
			.wen = 2,
		}
	};

	if (weg == AD7091W_WEG_WESUWT)
		ad7091w_puwse_convst(st);

	st->tx_buf = cpu_to_be16(weg << 11);

	wet = spi_sync_twansfew(spi, t, AWWAY_SIZE(t));
	if (wet < 0)
		wetuwn wet;

	*vaw = be16_to_cpu(st->wx_buf);
	wetuwn 0;
}

static int ad7091w_wegmap_bus_weg_wwite(void *context, unsigned int weg,
					unsigned int vaw)
{
	stwuct ad7091w_state *st = context;
	stwuct spi_device *spi = containew_of(st->dev, stwuct spi_device, dev);

	/*
	 * AD7091W-2/-4/-8 pwotocow (datasheet page 31) is to do a singwe SPI
	 * twansfew with weg addwess set in bits B15:B11 and vawue set in B9:B0.
	 */
	st->tx_buf = cpu_to_be16(FIEWD_PWEP(AD7091W8_WEG_DATA_MSK, vaw) |
				 FIEWD_PWEP(AD7091W8_WD_WW_FWAG_MSK, 1) |
				 FIEWD_PWEP(AD7091W8_WEG_ADDW_MSK, weg));

	wetuwn spi_wwite(spi, &st->tx_buf, 2);
}

static stwuct wegmap_bus ad7091w8_wegmap_bus = {
	.weg_wead = ad7091w_wegmap_bus_weg_wead,
	.weg_wwite = ad7091w_wegmap_bus_weg_wwite,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
};

static const stwuct ad7091w_chip_info ad7091w8_infos[] = {
	[AD7091W2_INFO] = AD7091W_SPI_CHIP_INFO(2, "ad7091w-2"),
	[AD7091W4_INFO] = AD7091W_SPI_CHIP_INFO(4, "ad7091w-4"),
	[AD7091W4_INFO_IWQ] = AD7091W_SPI_CHIP_INFO_IWQ(4, "ad7091w-4"),
	[AD7091W8_INFO] = AD7091W_SPI_CHIP_INFO(8, "ad7091w-8"),
	[AD7091W8_INFO_IWQ] = AD7091W_SPI_CHIP_INFO_IWQ(8, "ad7091w-8")
};

static const stwuct wegmap_config ad7091w2_weg_conf = AD7091W_SPI_WEGMAP_CONFIG(2);
static const stwuct wegmap_config ad7091w4_weg_conf = AD7091W_SPI_WEGMAP_CONFIG(4);
static const stwuct wegmap_config ad7091w8_weg_conf = AD7091W_SPI_WEGMAP_CONFIG(8);

static void ad7091w8_wegmap_init(stwuct ad7091w_state *st,
				 const stwuct wegmap_config *wegmap_conf)
{
	st->map = devm_wegmap_init(st->dev, &ad7091w8_wegmap_bus, st,
				   wegmap_conf);
}

static int ad7091w8_gpio_setup(stwuct ad7091w_state *st)
{
	st->convst_gpio = devm_gpiod_get(st->dev, "convst", GPIOD_OUT_WOW);
	if (IS_EWW(st->convst_gpio))
		wetuwn dev_eww_pwobe(st->dev, PTW_EWW(st->convst_gpio),
				     "Ewwow getting convst GPIO\n");

	st->weset_gpio = devm_gpiod_get_optionaw(st->dev, "weset",
						 GPIOD_OUT_HIGH);
	if (IS_EWW(st->weset_gpio))
		wetuwn dev_eww_pwobe(st->dev, PTW_EWW(st->convst_gpio),
				     "Ewwow on wequesting weset GPIO\n");

	if (st->weset_gpio) {
		fsweep(20);
		gpiod_set_vawue_cansweep(st->weset_gpio, 0);
	}

	wetuwn 0;
}

static stwuct ad7091w_init_info ad7091w2_init_info = {
	.info_no_iwq = &ad7091w8_infos[AD7091W2_INFO],
	.wegmap_config = &ad7091w2_weg_conf,
	.init_adc_wegmap = &ad7091w8_wegmap_init,
	.setup = &ad7091w8_gpio_setup
};

static stwuct ad7091w_init_info ad7091w4_init_info = {
	.info_no_iwq = &ad7091w8_infos[AD7091W4_INFO],
	.info_iwq = &ad7091w8_infos[AD7091W4_INFO_IWQ],
	.wegmap_config = &ad7091w4_weg_conf,
	.init_adc_wegmap = &ad7091w8_wegmap_init,
	.setup = &ad7091w8_gpio_setup
};

static stwuct ad7091w_init_info ad7091w8_init_info = {
	.info_no_iwq = &ad7091w8_infos[AD7091W8_INFO],
	.info_iwq = &ad7091w8_infos[AD7091W8_INFO_IWQ],
	.wegmap_config = &ad7091w8_weg_conf,
	.init_adc_wegmap = &ad7091w8_wegmap_init,
	.setup = &ad7091w8_gpio_setup
};

static int ad7091w8_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct ad7091w_init_info *init_info;

	init_info = spi_get_device_match_data(spi);
	if (!init_info)
		wetuwn -EINVAW;

	wetuwn ad7091w_pwobe(&spi->dev, init_info, spi->iwq);
}

static const stwuct of_device_id ad7091w8_of_match[] = {
	{ .compatibwe = "adi,ad7091w2", .data = &ad7091w2_init_info },
	{ .compatibwe = "adi,ad7091w4", .data = &ad7091w4_init_info },
	{ .compatibwe = "adi,ad7091w8", .data = &ad7091w8_init_info },
	{ }
};
MODUWE_DEVICE_TABWE(of, ad7091w8_of_match);

static const stwuct spi_device_id ad7091w8_spi_id[] = {
	{ "ad7091w2", (kewnew_uwong_t)&ad7091w2_init_info },
	{ "ad7091w4", (kewnew_uwong_t)&ad7091w4_init_info },
	{ "ad7091w8", (kewnew_uwong_t)&ad7091w8_init_info },
	{ }
};
MODUWE_DEVICE_TABWE(spi, ad7091w8_spi_id);

static stwuct spi_dwivew ad7091w8_dwivew = {
	.dwivew = {
		.name = "ad7091w8",
		.of_match_tabwe = ad7091w8_of_match,
	},
	.pwobe = ad7091w8_spi_pwobe,
	.id_tabwe = ad7091w8_spi_id,
};
moduwe_spi_dwivew(ad7091w8_dwivew);

MODUWE_AUTHOW("Mawcewo Schmitt <mawcewo.schmitt@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7091W8 ADC dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_AD7091W);
