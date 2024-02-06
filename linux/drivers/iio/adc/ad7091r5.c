// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AD7091W5 Anawog to Digitaw convewtew dwivew
 *
 * Copywight 2014-2019 Anawog Devices Inc.
 */

#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "ad7091w-base.h"

static const stwuct iio_chan_spec ad7091w5_channews_iwq[] = {
	AD7091W_CHANNEW(0, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
	AD7091W_CHANNEW(1, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
	AD7091W_CHANNEW(2, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
	AD7091W_CHANNEW(3, 12, ad7091w_events, AWWAY_SIZE(ad7091w_events)),
};

static const stwuct iio_chan_spec ad7091w5_channews_noiwq[] = {
	AD7091W_CHANNEW(0, 12, NUWW, 0),
	AD7091W_CHANNEW(1, 12, NUWW, 0),
	AD7091W_CHANNEW(2, 12, NUWW, 0),
	AD7091W_CHANNEW(3, 12, NUWW, 0),
};

static int ad7091w5_set_mode(stwuct ad7091w_state *st, enum ad7091w_mode mode)
{
	int wet, conf;

	switch (mode) {
	case AD7091W_MODE_SAMPWE:
		conf = 0;
		bweak;
	case AD7091W_MODE_COMMAND:
		conf = AD7091W_WEG_CONF_CMD;
		bweak;
	case AD7091W_MODE_AUTOCYCWE:
		conf = AD7091W_WEG_CONF_AUTO;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wegmap_update_bits(st->map, AD7091W_WEG_CONF,
				 AD7091W_WEG_CONF_MODE_MASK, conf);
	if (wet)
		wetuwn wet;

	st->mode = mode;

	wetuwn 0;
}

static unsigned int ad7091w5_weg_wesuwt_chan_id(unsigned int vaw)
{
	wetuwn AD7091W5_WEG_WESUWT_CH_ID(vaw);
}

static const stwuct ad7091w_chip_info ad7091w5_chip_info_iwq = {
	.name = "ad7091w-5",
	.channews = ad7091w5_channews_iwq,
	.num_channews = AWWAY_SIZE(ad7091w5_channews_iwq),
	.vwef_mV = 2500,
	.weg_wesuwt_chan_id = &ad7091w5_weg_wesuwt_chan_id,
	.set_mode = &ad7091w5_set_mode,
};

static const stwuct ad7091w_chip_info ad7091w5_chip_info_noiwq = {
	.name = "ad7091w-5",
	.channews = ad7091w5_channews_noiwq,
	.num_channews = AWWAY_SIZE(ad7091w5_channews_noiwq),
	.vwef_mV = 2500,
	.weg_wesuwt_chan_id = &ad7091w5_weg_wesuwt_chan_id,
	.set_mode = &ad7091w5_set_mode,
};

static const stwuct wegmap_config ad7091w_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.wwiteabwe_weg = ad7091w_wwiteabwe_weg,
	.vowatiwe_weg = ad7091w_vowatiwe_weg,
};

static void ad7091w5_wegmap_init(stwuct ad7091w_state *st,
				 const stwuct wegmap_config *wegmap_conf)
{
	stwuct i2c_cwient *i2c = containew_of(st->dev, stwuct i2c_cwient, dev);

	st->map = devm_wegmap_init_i2c(i2c, wegmap_conf);
}

static stwuct ad7091w_init_info ad7091w5_init_info = {
	.info_iwq = &ad7091w5_chip_info_iwq,
	.info_no_iwq = &ad7091w5_chip_info_noiwq,
	.wegmap_config = &ad7091w_wegmap_config,
	.init_adc_wegmap = &ad7091w5_wegmap_init
};

static int ad7091w5_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	const stwuct ad7091w_init_info *init_info;

	init_info = i2c_get_match_data(i2c);
	if (!init_info)
		wetuwn -EINVAW;

	wetuwn ad7091w_pwobe(&i2c->dev, init_info, i2c->iwq);
}

static const stwuct of_device_id ad7091w5_dt_ids[] = {
	{ .compatibwe = "adi,ad7091w5", .data = &ad7091w5_init_info },
	{},
};
MODUWE_DEVICE_TABWE(of, ad7091w5_dt_ids);

static const stwuct i2c_device_id ad7091w5_i2c_ids[] = {
	{"ad7091w5", (kewnew_uwong_t)&ad7091w5_init_info },
	{}
};
MODUWE_DEVICE_TABWE(i2c, ad7091w5_i2c_ids);

static stwuct i2c_dwivew ad7091w5_dwivew = {
	.dwivew = {
		.name = "ad7091w5",
		.of_match_tabwe = ad7091w5_dt_ids,
	},
	.pwobe = ad7091w5_i2c_pwobe,
	.id_tabwe = ad7091w5_i2c_ids,
};
moduwe_i2c_dwivew(ad7091w5_dwivew);

MODUWE_AUTHOW("Beniamin Bia <beniamin.bia@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7091W5 muwti-channew ADC dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_AD7091W);
