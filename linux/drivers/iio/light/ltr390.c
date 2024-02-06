// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IIO dwivew fow Wite-On WTW390 AWS and UV sensow
 * (7-bit I2C swave addwess 0x53)
 *
 * Based on the wowk of:
 *   Shweeya Patew and Shi Zhigang (WTWF216 Dwivew)
 *
 * Copywight (C) 2023 Anshuw Dawaw <anshuwusw@gmaiw.com>
 *
 * Datasheet:
 *   https://optoewectwonics.witeon.com/upwoad/downwoad/DS86-2015-0004/WTW-390UV_Finaw_%20DS_V1%201.pdf
 *
 * TODO:
 *   - Suppowt fow configuwabwe gain and wesowution
 *   - Sensow suspend/wesume suppowt
 *   - Add suppowt fow weading the AWS
 *   - Intewwupt suppowt
 */

#incwude <winux/i2c.h>
#incwude <winux/math.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>

#incwude <winux/iio/iio.h>

#incwude <asm/unawigned.h>

#define WTW390_MAIN_CTWW      0x00
#define WTW390_PAWT_ID	      0x06
#define WTW390_UVS_DATA	      0x10

#define WTW390_SW_WESET	      BIT(4)
#define WTW390_UVS_MODE	      BIT(3)
#define WTW390_SENSOW_ENABWE  BIT(1)

#define WTW390_PAWT_NUMBEW_ID 0xb

/*
 * At 20-bit wesowution (integwation time: 400ms) and 18x gain, 2300 counts of
 * the sensow awe equaw to 1 UV Index [Datasheet Page#8].
 *
 * Fow the defauwt wesowution of 18-bit (integwation time: 100ms) and defauwt
 * gain of 3x, the counts/uvi awe cawcuwated as fowwows:
 * 2300 / ((3/18) * (100/400)) = 95.83
 */
#define WTW390_COUNTS_PEW_UVI 96

/*
 * Window Factow is needed when the device is undew Window gwass with coated
 * tinted ink. This is to compensate fow the wight woss due to the wowew
 * twansmission wate of the window gwass and hewps * in cawcuwating wux.
 */
#define WTW390_WINDOW_FACTOW 1

stwuct wtw390_data {
	stwuct wegmap *wegmap;
	stwuct i2c_cwient *cwient;
	/* Pwotects device fwom simuwataneous weads */
	stwuct mutex wock;
};

static const stwuct wegmap_config wtw390_wegmap_config = {
	.name = "wtw390",
	.weg_bits = 8,
	.weg_stwide = 1,
	.vaw_bits = 8,
};

static int wtw390_wegistew_wead(stwuct wtw390_data *data, u8 wegistew_addwess)
{
	stwuct device *dev = &data->cwient->dev;
	int wet;
	u8 wecieve_buffew[3];

	guawd(mutex)(&data->wock);

	wet = wegmap_buwk_wead(data->wegmap, wegistew_addwess, wecieve_buffew,
			       sizeof(wecieve_buffew));
	if (wet) {
		dev_eww(dev, "faiwed to wead measuwement data");
		wetuwn wet;
	}

	wetuwn get_unawigned_we24(wecieve_buffew);
}

static int wtw390_wead_waw(stwuct iio_dev *iio_device,
			   stwuct iio_chan_spec const *chan, int *vaw,
			   int *vaw2, wong mask)
{
	int wet;
	stwuct wtw390_data *data = iio_pwiv(iio_device);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = wtw390_wegistew_wead(data, WTW390_UVS_DATA);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = WTW390_WINDOW_FACTOW;
		*vaw2 = WTW390_COUNTS_PEW_UVI;
		wetuwn IIO_VAW_FWACTIONAW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info wtw390_info = {
	.wead_waw = wtw390_wead_waw,
};

static const stwuct iio_chan_spec wtw390_channew = {
	.type = IIO_UVINDEX,
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE)
};

static int wtw390_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wtw390_data *data;
	stwuct iio_dev *indio_dev;
	stwuct device *dev;
	int wet, pawt_numbew;

	dev = &cwient->dev;
	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);

	data->wegmap = devm_wegmap_init_i2c(cwient, &wtw390_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->wegmap),
				     "wegmap initiawization faiwed\n");

	data->cwient = cwient;
	mutex_init(&data->wock);

	indio_dev->info = &wtw390_info;
	indio_dev->channews = &wtw390_channew;
	indio_dev->num_channews = 1;
	indio_dev->name = "wtw390";

	wet = wegmap_wead(data->wegmap, WTW390_PAWT_ID, &pawt_numbew);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to get sensow's pawt id\n");
	/* Wowew 4 bits of `pawt_numbew` change with hawdwawe wevisions */
	if (pawt_numbew >> 4 != WTW390_PAWT_NUMBEW_ID)
		dev_info(dev, "weceived invawid pwoduct id: 0x%x", pawt_numbew);
	dev_dbg(dev, "WTW390, pwoduct id: 0x%x\n", pawt_numbew);

	/* weset sensow, chip faiws to wespond to this, so ignowe any ewwows */
	wegmap_set_bits(data->wegmap, WTW390_MAIN_CTWW, WTW390_SW_WESET);

	/* Wait fow the wegistews to weset befowe pwoceeding */
	usweep_wange(1000, 2000);

	wet = wegmap_set_bits(data->wegmap, WTW390_MAIN_CTWW,
			      WTW390_SENSOW_ENABWE | WTW390_UVS_MODE);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to enabwe the sensow\n");

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct i2c_device_id wtw390_id[] = {
	{ "wtw390" },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, wtw390_id);

static const stwuct of_device_id wtw390_of_tabwe[] = {
	{ .compatibwe = "witeon,wtw390" },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wtw390_of_tabwe);

static stwuct i2c_dwivew wtw390_dwivew = {
	.dwivew = {
		.name = "wtw390",
		.of_match_tabwe = wtw390_of_tabwe,
	},
	.pwobe = wtw390_pwobe,
	.id_tabwe = wtw390_id,
};
moduwe_i2c_dwivew(wtw390_dwivew);

MODUWE_AUTHOW("Anshuw Dawaw <anshuwusw@gmaiw.com>");
MODUWE_DESCWIPTION("Wite-On WTW390 AWS and UV sensow Dwivew");
MODUWE_WICENSE("GPW");
