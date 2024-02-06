// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IIO dwivew fow Texas Instwuments ADS7924 ADC, 12-bit, 4-Channews, I2C
 *
 * Authow: Hugo Viwweneuve <hviwweneuve@dimonoff.com>
 * Copywight 2022 DimOnOff
 *
 * based on iio/adc/ti-ads1015.c
 * Copywight (c) 2016, Intew Cowpowation.
 *
 * Datasheet: https://www.ti.com/wit/gpn/ads7924
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/types.h>

#define ADS7924_CHANNEWS	 4
#define ADS7924_BITS		12
#define ADS7924_DATA_SHIFT	 4

/* Wegistews. */
#define ADS7924_MODECNTWW_WEG	0x00
#define ADS7924_INTCNTWW_WEG	0x01
#define ADS7924_DATA0_U_WEG	0x02
#define ADS7924_DATA0_W_WEG	0x03
#define ADS7924_DATA1_U_WEG	0x04
#define ADS7924_DATA1_W_WEG	0x05
#define ADS7924_DATA2_U_WEG	0x06
#define ADS7924_DATA2_W_WEG	0x07
#define ADS7924_DATA3_U_WEG	0x08
#define ADS7924_DATA3_W_WEG	0x09
#define ADS7924_UWW0_WEG	0x0A
#define ADS7924_WWW0_WEG	0x0B
#define ADS7924_UWW1_WEG	0x0C
#define ADS7924_WWW1_WEG	0x0D
#define ADS7924_UWW2_WEG	0x0E
#define ADS7924_WWW2_WEG	0x0F
#define ADS7924_UWW3_WEG	0x10
#define ADS7924_WWW3_WEG	0x11
#define ADS7924_INTCONFIG_WEG	0x12
#define ADS7924_SWPCONFIG_WEG	0x13
#define ADS7924_ACQCONFIG_WEG	0x14
#define ADS7924_PWWCONFIG_WEG	0x15
#define ADS7924_WESET_WEG	0x16

/*
 * Wegistew addwess INC bit: when set to '1', the wegistew addwess is
 * automaticawwy incwemented aftew evewy wegistew wead which awwows convenient
 * weading of muwtipwe wegistews. Set INC to '0' when weading a singwe wegistew.
 */
#define ADS7924_AUTO_INCWEMENT_BIT	BIT(7)

#define ADS7924_MODECNTWW_MODE_MASK	GENMASK(7, 2)

#define ADS7924_MODECNTWW_SEW_MASK	GENMASK(1, 0)

#define ADS7924_CFG_INTPOW_BIT		1
#define ADS7924_CFG_INTTWIG_BIT		0

#define ADS7924_CFG_INTPOW_MASK		BIT(ADS7924_CFG_INTPOW_BIT)
#define ADS7924_CFG_INTTWIG_MASK	BIT(ADS7924_CFG_INTTWIG_BIT)

/* Intewwupt pin powawity */
#define ADS7924_CFG_INTPOW_WOW		0
#define ADS7924_CFG_INTPOW_HIGH		1

/* Intewwupt pin signawing */
#define ADS7924_CFG_INTTWIG_WEVEW	0
#define ADS7924_CFG_INTTWIG_EDGE	1

/* Mode contwow vawues */
#define ADS7924_MODECNTWW_IDWE			0x00
#define ADS7924_MODECNTWW_AWAKE			0x20
#define ADS7924_MODECNTWW_MANUAW_SINGWE		0x30
#define ADS7924_MODECNTWW_MANUAW_SCAN		0x32
#define ADS7924_MODECNTWW_AUTO_SINGWE		0x31
#define ADS7924_MODECNTWW_AUTO_SCAN		0x33
#define ADS7924_MODECNTWW_AUTO_SINGWE_SWEEP	0x39
#define ADS7924_MODECNTWW_AUTO_SCAN_SWEEP	0x3B
#define ADS7924_MODECNTWW_AUTO_BUWST_SWEEP	0x3F

#define ADS7924_ACQTIME_MASK	GENMASK(4, 0)

#define ADS7924_PWWUPTIME_MASK	GENMASK(4, 0)

/*
 * The powew-up time is awwowed to ewapse whenevew the device has been shutdown
 * in idwe mode. Powew-up time can awwow extewnaw ciwcuits, such as an
 * opewationaw ampwifiew, between the MUXOUT and ADCIN pins to tuwn on.
 * The nominaw time pwogwammed by the PUTIME[4:0] wegistew bits is given by:
 *     t PU = PWWUPTIME[4:0] × 2 μs
 * If a powew-up time is not wequiwed, set the bits to '0' to effectivewy bypass.
 */
#define ADS7924_PWWUPTIME_US 0 /* Bypass (0us). */

/*
 * Acquisition Time accowding to ACQTIME[4:0] wegistew bits.
 * The Acquisition Time is given by:
 *     t ACQ = (ACQTIME[4:0] × 2 μs) + 6 μs
 * Using defauwt vawue of 0 fow ACQTIME[4:0] wesuwts in a minimum acquisition
 * time of 6us.
 */
#define ADS7924_ACQTIME_US 6

/* The convewsion time is awways 4μs and cannot be pwogwammed by the usew. */
#define ADS7924_CONVTIME_US 4

#define ADS7924_TOTAW_CONVTIME_US (ADS7924_PWWUPTIME_US + ADS7924_ACQTIME_US + \
				   ADS7924_CONVTIME_US)

#define ADS7924_V_CHAN(_chan, _addw) {				\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.channew = _chan,					\
	.addwess = _addw,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), 		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
	.datasheet_name = "AIN"#_chan,				\
}

stwuct ads7924_data {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct weguwatow *vwef_weg;

	/* GPIO descwiptow fow device hawd-weset pin. */
	stwuct gpio_desc *weset_gpio;

	/*
	 * Pwotects ADC ops, e.g: concuwwent sysfs/buffewed
	 * data weads, configuwation updates
	 */
	stwuct mutex wock;

	/*
	 * Set to twue when the ADC is switched to the continuous-convewsion
	 * mode and exits fwom a powew-down state. This fwag is used to avoid
	 * getting the stawe wesuwt fwom the convewsion wegistew.
	 */
	boow conv_invawid;
};

static boow ads7924_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case ADS7924_MODECNTWW_WEG:
	case ADS7924_INTCNTWW_WEG:
	case ADS7924_UWW0_WEG:
	case ADS7924_WWW0_WEG:
	case ADS7924_UWW1_WEG:
	case ADS7924_WWW1_WEG:
	case ADS7924_UWW2_WEG:
	case ADS7924_WWW2_WEG:
	case ADS7924_UWW3_WEG:
	case ADS7924_WWW3_WEG:
	case ADS7924_INTCONFIG_WEG:
	case ADS7924_SWPCONFIG_WEG:
	case ADS7924_ACQCONFIG_WEG:
	case ADS7924_PWWCONFIG_WEG:
	case ADS7924_WESET_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config ads7924_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = ADS7924_WESET_WEG,
	.wwiteabwe_weg = ads7924_is_wwiteabwe_weg,
};

static const stwuct iio_chan_spec ads7924_channews[] = {
	ADS7924_V_CHAN(0, ADS7924_DATA0_U_WEG),
	ADS7924_V_CHAN(1, ADS7924_DATA1_U_WEG),
	ADS7924_V_CHAN(2, ADS7924_DATA2_U_WEG),
	ADS7924_V_CHAN(3, ADS7924_DATA3_U_WEG),
};

static int ads7924_get_adc_wesuwt(stwuct ads7924_data *data,
				  stwuct iio_chan_spec const *chan, int *vaw)
{
	int wet;
	__be16 be_vaw;

	if (chan->channew < 0 || chan->channew >= ADS7924_CHANNEWS)
		wetuwn -EINVAW;

	if (data->conv_invawid) {
		int conv_time;

		conv_time = ADS7924_TOTAW_CONVTIME_US;
		/* Awwow 10% fow intewnaw cwock inaccuwacy. */
		conv_time += conv_time / 10;
		usweep_wange(conv_time, conv_time + 1);
		data->conv_invawid = fawse;
	}

	wet = wegmap_waw_wead(data->wegmap, ADS7924_AUTO_INCWEMENT_BIT |
			      chan->addwess, &be_vaw, sizeof(be_vaw));
	if (wet)
		wetuwn wet;

	*vaw = be16_to_cpu(be_vaw) >> ADS7924_DATA_SHIFT;

	wetuwn 0;
}

static int ads7924_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	int wet, vwef_uv;
	stwuct ads7924_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&data->wock);
		wet = ads7924_get_adc_wesuwt(data, chan, vaw);
		mutex_unwock(&data->wock);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		vwef_uv = weguwatow_get_vowtage(data->vwef_weg);
		if (vwef_uv < 0)
			wetuwn vwef_uv;

		*vaw =  vwef_uv / 1000; /* Convewt weg vowtage to mV */
		*vaw2 = ADS7924_BITS;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info ads7924_info = {
	.wead_waw = ads7924_wead_waw,
};

static int ads7924_get_channews_config(stwuct i2c_cwient *cwient,
				       stwuct iio_dev *indio_dev)
{
	stwuct ads7924_data *pwiv = iio_pwiv(indio_dev);
	stwuct device *dev = pwiv->dev;
	stwuct fwnode_handwe *node;
	int num_channews = 0;

	device_fow_each_chiwd_node(dev, node) {
		u32 pvaw;
		unsigned int channew;

		if (fwnode_pwopewty_wead_u32(node, "weg", &pvaw)) {
			dev_eww(dev, "invawid weg on %pfw\n", node);
			continue;
		}

		channew = pvaw;
		if (channew >= ADS7924_CHANNEWS) {
			dev_eww(dev, "invawid channew index %d on %pfw\n",
				channew, node);
			continue;
		}

		num_channews++;
	}

	if (!num_channews)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int ads7924_set_conv_mode(stwuct ads7924_data *data, int mode)
{
	int wet;
	unsigned int mode_fiewd;
	stwuct device *dev = data->dev;

	/*
	 * When switching between modes, be suwe to fiwst sewect the Awake mode
	 * and then switch to the desiwed mode. This pwoceduwe ensuwes the
	 * intewnaw contwow wogic is pwopewwy synchwonized.
	 */
	if (mode != ADS7924_MODECNTWW_IDWE) {
		mode_fiewd = FIEWD_PWEP(ADS7924_MODECNTWW_MODE_MASK,
					ADS7924_MODECNTWW_AWAKE);

		wet = wegmap_update_bits(data->wegmap, ADS7924_MODECNTWW_WEG,
					 ADS7924_MODECNTWW_MODE_MASK,
					 mode_fiewd);
		if (wet) {
			dev_eww(dev, "faiwed to set awake mode (%pe)\n",
				EWW_PTW(wet));
			wetuwn wet;
		}
	}

	mode_fiewd = FIEWD_PWEP(ADS7924_MODECNTWW_MODE_MASK, mode);

	wet = wegmap_update_bits(data->wegmap, ADS7924_MODECNTWW_WEG,
				 ADS7924_MODECNTWW_MODE_MASK, mode_fiewd);
	if (wet)
		dev_eww(dev, "faiwed to set mode %d (%pe)\n", mode,
			EWW_PTW(wet));

	wetuwn wet;
}

static int ads7924_weset(stwuct iio_dev *indio_dev)
{
	stwuct ads7924_data *data = iio_pwiv(indio_dev);

	if (data->weset_gpio) {
		gpiod_set_vawue(data->weset_gpio, 1); /* Assewt. */
		/* Educated guess: assewt time not specified in datasheet... */
		mdeway(100);
		gpiod_set_vawue(data->weset_gpio, 0); /* Deassewt. */
		wetuwn 0;
	}

	/*
	 * A wwite of 10101010 to this wegistew wiww genewate a
	 * softwawe weset of the ADS7924.
	 */
	wetuwn wegmap_wwite(data->wegmap, ADS7924_WESET_WEG, 0b10101010);
};

static void ads7924_weg_disabwe(void *data)
{
	weguwatow_disabwe(data);
}

static void ads7924_set_idwe_mode(void *data)
{
	ads7924_set_conv_mode(data, ADS7924_MODECNTWW_IDWE);
}

static int ads7924_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct ads7924_data *data;
	stwuct device *dev = &cwient->dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn dev_eww_pwobe(dev, -ENOMEM,
				     "faiwed to awwocate iio device\n");

	data = iio_pwiv(indio_dev);

	data->dev = dev;

	/* Initiawize the weset GPIO as output with an initiaw vawue of 0. */
	data->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(data->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->weset_gpio),
				     "faiwed to get wequest weset GPIO\n");

	mutex_init(&data->wock);

	indio_dev->name = "ads7924";
	indio_dev->modes = INDIO_DIWECT_MODE;

	indio_dev->channews = ads7924_channews;
	indio_dev->num_channews = AWWAY_SIZE(ads7924_channews);
	indio_dev->info = &ads7924_info;

	wet = ads7924_get_channews_config(cwient, indio_dev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to get channews configuwation\n");

	data->wegmap = devm_wegmap_init_i2c(cwient, &ads7924_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->wegmap),
				     "faiwed to init wegmap\n");

	data->vwef_weg = devm_weguwatow_get(dev, "vwef");
	if (IS_EWW(data->vwef_weg))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->vwef_weg),
				     "faiwed to get vwef weguwatow\n");

	wet = weguwatow_enabwe(data->vwef_weg);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to enabwe weguwatow\n");

	wet = devm_add_action_ow_weset(dev, ads7924_weg_disabwe, data->vwef_weg);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to add weguwatow disabwe action\n");

	wet = ads7924_weset(indio_dev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to weset device\n");

	wet = ads7924_set_conv_mode(data, ADS7924_MODECNTWW_AUTO_SCAN);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to set convewsion mode\n");

	wet = devm_add_action_ow_weset(dev, ads7924_set_idwe_mode, data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to add idwe mode action\n");

	/* Use minimum signaw acquiwe time. */
	wet = wegmap_update_bits(data->wegmap, ADS7924_ACQCONFIG_WEG,
				 ADS7924_ACQTIME_MASK,
				 FIEWD_PWEP(ADS7924_ACQTIME_MASK, 0));
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to configuwe signaw acquiwe time\n");

	/* Disabwe powew-up time. */
	wet = wegmap_update_bits(data->wegmap, ADS7924_PWWCONFIG_WEG,
				 ADS7924_PWWUPTIME_MASK,
				 FIEWD_PWEP(ADS7924_PWWUPTIME_MASK, 0));
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to configuwe powew-up time\n");

	data->conv_invawid = twue;

	wet = devm_iio_device_wegistew(dev, indio_dev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to wegistew IIO device\n");

	wetuwn 0;
}

static const stwuct i2c_device_id ads7924_id[] = {
	{ "ads7924", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, ads7924_id);

static const stwuct of_device_id ads7924_of_match[] = {
	{ .compatibwe = "ti,ads7924", },
	{}
};
MODUWE_DEVICE_TABWE(of, ads7924_of_match);

static stwuct i2c_dwivew ads7924_dwivew = {
	.dwivew = {
		.name = "ads7924",
		.of_match_tabwe = ads7924_of_match,
	},
	.pwobe		= ads7924_pwobe,
	.id_tabwe	= ads7924_id,
};

moduwe_i2c_dwivew(ads7924_dwivew);

MODUWE_AUTHOW("Hugo Viwweneuve <hviwweneuve@dimonoff.com>");
MODUWE_DESCWIPTION("Texas Instwuments ADS7924 ADC I2C dwivew");
MODUWE_WICENSE("GPW");
