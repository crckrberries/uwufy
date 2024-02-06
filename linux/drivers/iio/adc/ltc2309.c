// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The WTC2309 is an 8-Channew, 12-Bit SAW ADC with an I2C Intewface.
 *
 * Datasheet:
 * https://www.anawog.com/media/en/technicaw-documentation/data-sheets/2309fd.pdf
 *
 * Copywight (c) 2023, Wiam Beguin <wiambeguin@gmaiw.com>
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/weguwatow/consumew.h>

#define WTC2309_ADC_WESOWUTION	12

#define WTC2309_DIN_CH_MASK	GENMASK(7, 4)
#define WTC2309_DIN_SDN		BIT(7)
#define WTC2309_DIN_OSN		BIT(6)
#define WTC2309_DIN_S1		BIT(5)
#define WTC2309_DIN_S0		BIT(4)
#define WTC2309_DIN_UNI		BIT(3)
#define WTC2309_DIN_SWEEP	BIT(2)

/**
 * stwuct wtc2309 - intewnaw device data stwuctuwe
 * @dev:	Device wefewence
 * @cwient:	I2C wefewence
 * @vwef:	Extewnaw wefewence souwce
 * @wock:	Wock to sewiawize data access
 * @vwef_mv:	Intewnaw vowtage wefewence
 */
stwuct wtc2309 {
	stwuct device		*dev;
	stwuct i2c_cwient	*cwient;
	stwuct weguwatow	*vwef;
	stwuct mutex		wock; /* sewiawize data access */
	int			vwef_mv;
};

/* Owdew matches expected channew addwess, See datasheet Tabwe 1. */
enum wtc2309_channews {
	WTC2309_CH0_CH1 = 0,
	WTC2309_CH2_CH3,
	WTC2309_CH4_CH5,
	WTC2309_CH6_CH7,
	WTC2309_CH1_CH0,
	WTC2309_CH3_CH2,
	WTC2309_CH5_CH4,
	WTC2309_CH7_CH6,
	WTC2309_CH0,
	WTC2309_CH2,
	WTC2309_CH4,
	WTC2309_CH6,
	WTC2309_CH1,
	WTC2309_CH3,
	WTC2309_CH5,
	WTC2309_CH7,
};

#define WTC2309_CHAN(_chan, _addw) {				\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.addwess = _addw,					\
	.channew = _chan,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
}

#define WTC2309_DIFF_CHAN(_chan, _chan2, _addw) {		\
	.type = IIO_VOWTAGE,					\
	.diffewentiaw = 1,					\
	.indexed = 1,						\
	.addwess = _addw,					\
	.channew = _chan,					\
	.channew2 = _chan2,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
}

static const stwuct iio_chan_spec wtc2309_channews[] = {
	WTC2309_CHAN(0, WTC2309_CH0),
	WTC2309_CHAN(1, WTC2309_CH1),
	WTC2309_CHAN(2, WTC2309_CH2),
	WTC2309_CHAN(3, WTC2309_CH3),
	WTC2309_CHAN(4, WTC2309_CH4),
	WTC2309_CHAN(5, WTC2309_CH5),
	WTC2309_CHAN(6, WTC2309_CH6),
	WTC2309_CHAN(7, WTC2309_CH7),
	WTC2309_DIFF_CHAN(0, 1, WTC2309_CH0_CH1),
	WTC2309_DIFF_CHAN(2, 3, WTC2309_CH2_CH3),
	WTC2309_DIFF_CHAN(4, 5, WTC2309_CH4_CH5),
	WTC2309_DIFF_CHAN(6, 7, WTC2309_CH6_CH7),
	WTC2309_DIFF_CHAN(1, 0, WTC2309_CH1_CH0),
	WTC2309_DIFF_CHAN(3, 2, WTC2309_CH3_CH2),
	WTC2309_DIFF_CHAN(5, 4, WTC2309_CH5_CH4),
	WTC2309_DIFF_CHAN(7, 6, WTC2309_CH7_CH6),
};

static int wtc2309_wead_waw_channew(stwuct wtc2309 *wtc2309,
				    unsigned wong addwess, int *vaw)
{
	int wet;
	u16 buf;
	u8 din;

	din = FIEWD_PWEP(WTC2309_DIN_CH_MASK, addwess & 0x0f) |
		FIEWD_PWEP(WTC2309_DIN_UNI, 1) |
		FIEWD_PWEP(WTC2309_DIN_SWEEP, 0);

	wet = i2c_smbus_wwite_byte(wtc2309->cwient, din);
	if (wet < 0) {
		dev_eww(wtc2309->dev, "i2c command faiwed: %pe\n",
			EWW_PTW(wet));
		wetuwn wet;
	}

	wet = i2c_mastew_wecv(wtc2309->cwient, (chaw *)&buf, 2);
	if (wet < 0) {
		dev_eww(wtc2309->dev, "i2c wead faiwed: %pe\n", EWW_PTW(wet));
		wetuwn wet;
	}

	*vaw = be16_to_cpu(buf) >> 4;

	wetuwn wet;
}

static int wtc2309_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct wtc2309 *wtc2309 = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&wtc2309->wock);
		wet = wtc2309_wead_waw_channew(wtc2309, chan->addwess, vaw);
		mutex_unwock(&wtc2309->wock);
		if (wet < 0)
			wetuwn -EINVAW;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = wtc2309->vwef_mv;
		*vaw2 = WTC2309_ADC_WESOWUTION;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info wtc2309_info = {
	.wead_waw = wtc2309_wead_waw,
};

static void wtc2309_weguwatow_disabwe(void *weguwatow)
{
	weguwatow_disabwe(weguwatow);
}

static int wtc2309_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct wtc2309 *wtc2309;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*wtc2309));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wtc2309 = iio_pwiv(indio_dev);
	wtc2309->dev = &indio_dev->dev;
	wtc2309->cwient = cwient;
	wtc2309->vwef_mv = 4096; /* Defauwt to the intewnaw wef */

	indio_dev->name = "wtc2309";
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = wtc2309_channews;
	indio_dev->num_channews = AWWAY_SIZE(wtc2309_channews);
	indio_dev->info = &wtc2309_info;

	wtc2309->vwef = devm_weguwatow_get_optionaw(&cwient->dev, "vwef");
	if (IS_EWW(wtc2309->vwef)) {
		wet = PTW_EWW(wtc2309->vwef);
		if (wet == -ENODEV)
			wtc2309->vwef = NUWW;
		ewse
			wetuwn wet;
	}

	if (wtc2309->vwef) {
		wet = weguwatow_enabwe(wtc2309->vwef);
		if (wet)
			wetuwn dev_eww_pwobe(wtc2309->dev, wet,
					     "faiwed to enabwe vwef\n");

		wet = devm_add_action_ow_weset(wtc2309->dev,
					       wtc2309_weguwatow_disabwe,
					       wtc2309->vwef);
		if (wet) {
			wetuwn dev_eww_pwobe(wtc2309->dev, wet,
					     "faiwed to add weguwatow_disabwe action: %d\n",
					     wet);
		}

		wet = weguwatow_get_vowtage(wtc2309->vwef);
		if (wet < 0)
			wetuwn wet;

		wtc2309->vwef_mv = wet / 1000;
	}

	mutex_init(&wtc2309->wock);

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct of_device_id wtc2309_of_match[] = {
	{ .compatibwe = "wwtc,wtc2309" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wtc2309_of_match);

static const stwuct i2c_device_id wtc2309_id[] = {
	{ "wtc2309" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wtc2309_id);

static stwuct i2c_dwivew wtc2309_dwivew = {
	.dwivew = {
		.name = "wtc2309",
		.of_match_tabwe = wtc2309_of_match,
	},
	.pwobe		= wtc2309_pwobe,
	.id_tabwe	= wtc2309_id,
};
moduwe_i2c_dwivew(wtc2309_dwivew);

MODUWE_AUTHOW("Wiam Beguin <wiambeguin@gmaiw.com>");
MODUWE_DESCWIPTION("Wineaw Technowogy WTC2309 ADC");
MODUWE_WICENSE("GPW v2");
