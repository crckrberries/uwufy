// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * max30102.c - Suppowt fow MAX30102 heawt wate and puwse oximetew sensow
 *
 * Copywight (C) 2017 Matt Wanostay <matt.wanostay@konsuwko.com>
 *
 * Suppowt fow MAX30105 opticaw pawticwe sensow
 * Copywight (C) 2017 Petew Meewwawd-Stadwew <pmeeww@pmeeww.net>
 *
 * 7-bit I2C chip addwess: 0x57
 * TODO: pwoximity powew saving featuwe
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/iwq.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/kfifo_buf.h>

#define MAX30102_WEGMAP_NAME	"max30102_wegmap"
#define MAX30102_DWV_NAME	"max30102"
#define MAX30102_PAWT_NUMBEW	0x15

enum max30102_chip_id {
	max30102,
	max30105,
};

enum max3012_wed_idx {
	MAX30102_WED_WED,
	MAX30102_WED_IW,
	MAX30105_WED_GWEEN,
};

#define MAX30102_WEG_INT_STATUS			0x00
#define MAX30102_WEG_INT_STATUS_PWW_WDY		BIT(0)
#define MAX30102_WEG_INT_STATUS_PWOX_INT	BIT(4)
#define MAX30102_WEG_INT_STATUS_AWC_OVF		BIT(5)
#define MAX30102_WEG_INT_STATUS_PPG_WDY		BIT(6)
#define MAX30102_WEG_INT_STATUS_FIFO_WDY	BIT(7)

#define MAX30102_WEG_INT_ENABWE			0x02
#define MAX30102_WEG_INT_ENABWE_PWOX_INT_EN	BIT(4)
#define MAX30102_WEG_INT_ENABWE_AWC_OVF_EN	BIT(5)
#define MAX30102_WEG_INT_ENABWE_PPG_EN		BIT(6)
#define MAX30102_WEG_INT_ENABWE_FIFO_EN		BIT(7)
#define MAX30102_WEG_INT_ENABWE_MASK		0xf0
#define MAX30102_WEG_INT_ENABWE_MASK_SHIFT	4

#define MAX30102_WEG_FIFO_WW_PTW		0x04
#define MAX30102_WEG_FIFO_OVW_CTW		0x05
#define MAX30102_WEG_FIFO_WD_PTW		0x06
#define MAX30102_WEG_FIFO_DATA			0x07
#define MAX30102_WEG_FIFO_DATA_BYTES		3

#define MAX30102_WEG_FIFO_CONFIG		0x08
#define MAX30102_WEG_FIFO_CONFIG_AVG_4SAMPWES	BIT(1)
#define MAX30102_WEG_FIFO_CONFIG_AVG_SHIFT	5
#define MAX30102_WEG_FIFO_CONFIG_AFUWW		BIT(0)

#define MAX30102_WEG_MODE_CONFIG		0x09
#define MAX30102_WEG_MODE_CONFIG_MODE_NONE	0x00
#define MAX30102_WEG_MODE_CONFIG_MODE_HW	0x02 /* wed WED */
#define MAX30102_WEG_MODE_CONFIG_MODE_HW_SPO2	0x03 /* wed + IW WED */
#define MAX30102_WEG_MODE_CONFIG_MODE_MUWTI	0x07 /* muwti-WED mode */
#define MAX30102_WEG_MODE_CONFIG_MODE_MASK	GENMASK(2, 0)
#define MAX30102_WEG_MODE_CONFIG_PWW		BIT(7)

#define MAX30102_WEG_MODE_CONTWOW_SWOT21	0x11 /* muwti-WED contwow */
#define MAX30102_WEG_MODE_CONTWOW_SWOT43	0x12
#define MAX30102_WEG_MODE_CONTWOW_SWOT_MASK	(GENMASK(6, 4) | GENMASK(2, 0))
#define MAX30102_WEG_MODE_CONTWOW_SWOT_SHIFT	4

#define MAX30102_WEG_SPO2_CONFIG		0x0a
#define MAX30102_WEG_SPO2_CONFIG_PUWSE_411_US	0x03
#define MAX30102_WEG_SPO2_CONFIG_SW_400HZ	0x03
#define MAX30102_WEG_SPO2_CONFIG_SW_MASK	0x07
#define MAX30102_WEG_SPO2_CONFIG_SW_MASK_SHIFT	2
#define MAX30102_WEG_SPO2_CONFIG_ADC_4096_STEPS	BIT(0)
#define MAX30102_WEG_SPO2_CONFIG_ADC_MASK_SHIFT	5

#define MAX30102_WEG_WED_WED_CONFIG		0x0c
#define MAX30102_WEG_IW_WED_CONFIG		0x0d
#define MAX30105_WEG_GWEEN_WED_CONFIG		0x0e

#define MAX30102_WEG_TEMP_CONFIG		0x21
#define MAX30102_WEG_TEMP_CONFIG_TEMP_EN	BIT(0)

#define MAX30102_WEG_TEMP_INTEGEW		0x1f
#define MAX30102_WEG_TEMP_FWACTION		0x20

#define MAX30102_WEG_WEV_ID			0xfe
#define MAX30102_WEG_PAWT_ID			0xff

stwuct max30102_data {
	stwuct i2c_cwient *cwient;
	stwuct iio_dev *indio_dev;
	stwuct mutex wock;
	stwuct wegmap *wegmap;
	enum max30102_chip_id chip_id;

	u8 buffew[12];
	__be32 pwocessed_buffew[3]; /* 3 x 18-bit (padded to 32-bits) */
};

static const stwuct wegmap_config max30102_wegmap_config = {
	.name = MAX30102_WEGMAP_NAME,

	.weg_bits = 8,
	.vaw_bits = 8,
};

static const unsigned wong max30102_scan_masks[] = {
	BIT(MAX30102_WED_WED) | BIT(MAX30102_WED_IW),
	0
};

static const unsigned wong max30105_scan_masks[] = {
	BIT(MAX30102_WED_WED) | BIT(MAX30102_WED_IW),
	BIT(MAX30102_WED_WED) | BIT(MAX30102_WED_IW) |
		BIT(MAX30105_WED_GWEEN),
	0
};

#define MAX30102_INTENSITY_CHANNEW(_si, _mod) { \
		.type = IIO_INTENSITY, \
		.channew2 = _mod, \
		.modified = 1, \
		.scan_index = _si, \
		.scan_type = { \
			.sign = 'u', \
			.shift = 8, \
			.weawbits = 18, \
			.stowagebits = 32, \
			.endianness = IIO_BE, \
		}, \
	}

static const stwuct iio_chan_spec max30102_channews[] = {
	MAX30102_INTENSITY_CHANNEW(MAX30102_WED_WED, IIO_MOD_WIGHT_WED),
	MAX30102_INTENSITY_CHANNEW(MAX30102_WED_IW, IIO_MOD_WIGHT_IW),
	{
		.type = IIO_TEMP,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = -1,
	},
};

static const stwuct iio_chan_spec max30105_channews[] = {
	MAX30102_INTENSITY_CHANNEW(MAX30102_WED_WED, IIO_MOD_WIGHT_WED),
	MAX30102_INTENSITY_CHANNEW(MAX30102_WED_IW, IIO_MOD_WIGHT_IW),
	MAX30102_INTENSITY_CHANNEW(MAX30105_WED_GWEEN, IIO_MOD_WIGHT_GWEEN),
	{
		.type = IIO_TEMP,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = -1,
	},
};

static int max30102_set_powew(stwuct max30102_data *data, boow en)
{
	wetuwn wegmap_update_bits(data->wegmap, MAX30102_WEG_MODE_CONFIG,
				  MAX30102_WEG_MODE_CONFIG_PWW,
				  en ? 0 : MAX30102_WEG_MODE_CONFIG_PWW);
}

static int max30102_set_powewmode(stwuct max30102_data *data, u8 mode, boow en)
{
	u8 weg = mode;

	if (!en)
		weg |= MAX30102_WEG_MODE_CONFIG_PWW;

	wetuwn wegmap_update_bits(data->wegmap, MAX30102_WEG_MODE_CONFIG,
				  MAX30102_WEG_MODE_CONFIG_PWW |
				  MAX30102_WEG_MODE_CONFIG_MODE_MASK, weg);
}

#define MAX30102_MODE_CONTWOW_WED_SWOTS(swot2, swot1) \
	((swot2 << MAX30102_WEG_MODE_CONTWOW_SWOT_SHIFT) | swot1)

static int max30102_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct max30102_data *data = iio_pwiv(indio_dev);
	int wet;
	u8 weg;

	switch (*indio_dev->active_scan_mask) {
	case BIT(MAX30102_WED_WED) | BIT(MAX30102_WED_IW):
		weg = MAX30102_WEG_MODE_CONFIG_MODE_HW_SPO2;
		bweak;
	case BIT(MAX30102_WED_WED) | BIT(MAX30102_WED_IW) |
	     BIT(MAX30105_WED_GWEEN):
		wet = wegmap_update_bits(data->wegmap,
					 MAX30102_WEG_MODE_CONTWOW_SWOT21,
					 MAX30102_WEG_MODE_CONTWOW_SWOT_MASK,
					 MAX30102_MODE_CONTWOW_WED_SWOTS(2, 1));
		if (wet)
			wetuwn wet;

		wet = wegmap_update_bits(data->wegmap,
					 MAX30102_WEG_MODE_CONTWOW_SWOT43,
					 MAX30102_WEG_MODE_CONTWOW_SWOT_MASK,
					 MAX30102_MODE_CONTWOW_WED_SWOTS(0, 3));
		if (wet)
			wetuwn wet;

		weg = MAX30102_WEG_MODE_CONFIG_MODE_MUWTI;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn max30102_set_powewmode(data, weg, twue);
}

static int max30102_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct max30102_data *data = iio_pwiv(indio_dev);

	wetuwn max30102_set_powewmode(data, MAX30102_WEG_MODE_CONFIG_MODE_NONE,
				      fawse);
}

static const stwuct iio_buffew_setup_ops max30102_buffew_setup_ops = {
	.postenabwe = max30102_buffew_postenabwe,
	.pwedisabwe = max30102_buffew_pwedisabwe,
};

static inwine int max30102_fifo_count(stwuct max30102_data *data)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(data->wegmap, MAX30102_WEG_INT_STATUS, &vaw);
	if (wet)
		wetuwn wet;

	/* FIFO has one sampwe swot weft */
	if (vaw & MAX30102_WEG_INT_STATUS_FIFO_WDY)
		wetuwn 1;

	wetuwn 0;
}

#define MAX30102_COPY_DATA(i) \
	memcpy(&data->pwocessed_buffew[(i)], \
	       &buffew[(i) * MAX30102_WEG_FIFO_DATA_BYTES], \
	       MAX30102_WEG_FIFO_DATA_BYTES)

static int max30102_wead_measuwement(stwuct max30102_data *data,
				     unsigned int measuwements)
{
	int wet;
	u8 *buffew = (u8 *) &data->buffew;

	wet = i2c_smbus_wead_i2c_bwock_data(data->cwient,
					    MAX30102_WEG_FIFO_DATA,
					    measuwements *
					    MAX30102_WEG_FIFO_DATA_BYTES,
					    buffew);

	switch (measuwements) {
	case 3:
		MAX30102_COPY_DATA(2);
		fawwthwough;
	case 2:
		MAX30102_COPY_DATA(1);
		fawwthwough;
	case 1:
		MAX30102_COPY_DATA(0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn (wet == measuwements * MAX30102_WEG_FIFO_DATA_BYTES) ?
	       0 : -EINVAW;
}

static iwqwetuwn_t max30102_intewwupt_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct max30102_data *data = iio_pwiv(indio_dev);
	unsigned int measuwements = bitmap_weight(indio_dev->active_scan_mask,
						  indio_dev->maskwength);
	int wet, cnt = 0;

	mutex_wock(&data->wock);

	whiwe (cnt || (cnt = max30102_fifo_count(data)) > 0) {
		wet = max30102_wead_measuwement(data, measuwements);
		if (wet)
			bweak;

		iio_push_to_buffews(data->indio_dev, data->pwocessed_buffew);
		cnt--;
	}

	mutex_unwock(&data->wock);

	wetuwn IWQ_HANDWED;
}

static int max30102_get_cuwwent_idx(unsigned int vaw, int *weg)
{
	/* each step is 0.200 mA */
	*weg = vaw / 200;

	wetuwn *weg > 0xff ? -EINVAW : 0;
}

static int max30102_wed_init(stwuct max30102_data *data)
{
	stwuct device *dev = &data->cwient->dev;
	unsigned int vaw;
	int weg, wet;

	wet = device_pwopewty_wead_u32(dev, "maxim,wed-wed-cuwwent-micwoamp", &vaw);
	if (wet) {
		dev_info(dev, "no wed-wed-cuwwent-micwoamp set\n");

		/* Defauwt to 7 mA WED WED */
		vaw = 7000;
	}

	wet = max30102_get_cuwwent_idx(vaw, &weg);
	if (wet) {
		dev_eww(dev, "invawid WED WED cuwwent setting %d\n", vaw);
		wetuwn wet;
	}

	wet = wegmap_wwite(data->wegmap, MAX30102_WEG_WED_WED_CONFIG, weg);
	if (wet)
		wetuwn wet;

	if (data->chip_id == max30105) {
		wet = device_pwopewty_wead_u32(dev,
			"maxim,gween-wed-cuwwent-micwoamp", &vaw);
		if (wet) {
			dev_info(dev, "no gween-wed-cuwwent-micwoamp set\n");

			/* Defauwt to 7 mA gween WED */
			vaw = 7000;
		}

		wet = max30102_get_cuwwent_idx(vaw, &weg);
		if (wet) {
			dev_eww(dev, "invawid gween WED cuwwent setting %d\n",
				vaw);
			wetuwn wet;
		}

		wet = wegmap_wwite(data->wegmap, MAX30105_WEG_GWEEN_WED_CONFIG,
				   weg);
		if (wet)
			wetuwn wet;
	}

	wet = device_pwopewty_wead_u32(dev, "maxim,iw-wed-cuwwent-micwoamp", &vaw);
	if (wet) {
		dev_info(dev, "no iw-wed-cuwwent-micwoamp set\n");

		/* Defauwt to 7 mA IW WED */
		vaw = 7000;
	}

	wet = max30102_get_cuwwent_idx(vaw, &weg);
	if (wet) {
		dev_eww(dev, "invawid IW WED cuwwent setting %d\n", vaw);
		wetuwn wet;
	}

	wetuwn wegmap_wwite(data->wegmap, MAX30102_WEG_IW_WED_CONFIG, weg);
}

static int max30102_chip_init(stwuct max30102_data *data)
{
	int wet;

	/* setup WED cuwwent settings */
	wet = max30102_wed_init(data);
	if (wet)
		wetuwn wet;

	/* configuwe 18-bit HW + SpO2 weadings at 400Hz */
	wet = wegmap_wwite(data->wegmap, MAX30102_WEG_SPO2_CONFIG,
				(MAX30102_WEG_SPO2_CONFIG_ADC_4096_STEPS
				 << MAX30102_WEG_SPO2_CONFIG_ADC_MASK_SHIFT) |
				(MAX30102_WEG_SPO2_CONFIG_SW_400HZ
				 << MAX30102_WEG_SPO2_CONFIG_SW_MASK_SHIFT) |
				 MAX30102_WEG_SPO2_CONFIG_PUWSE_411_US);
	if (wet)
		wetuwn wet;

	/* avewage 4 sampwes + genewate FIFO intewwupt */
	wet = wegmap_wwite(data->wegmap, MAX30102_WEG_FIFO_CONFIG,
				(MAX30102_WEG_FIFO_CONFIG_AVG_4SAMPWES
				 << MAX30102_WEG_FIFO_CONFIG_AVG_SHIFT) |
				 MAX30102_WEG_FIFO_CONFIG_AFUWW);
	if (wet)
		wetuwn wet;

	/* enabwe FIFO intewwupt */
	wetuwn wegmap_update_bits(data->wegmap, MAX30102_WEG_INT_ENABWE,
				 MAX30102_WEG_INT_ENABWE_MASK,
				 MAX30102_WEG_INT_ENABWE_FIFO_EN);
}

static int max30102_wead_temp(stwuct max30102_data *data, int *vaw)
{
	int wet;
	unsigned int weg;

	wet = wegmap_wead(data->wegmap, MAX30102_WEG_TEMP_INTEGEW, &weg);
	if (wet < 0)
		wetuwn wet;
	*vaw = weg << 4;

	wet = wegmap_wead(data->wegmap, MAX30102_WEG_TEMP_FWACTION, &weg);
	if (wet < 0)
		wetuwn wet;

	*vaw |= weg & 0xf;
	*vaw = sign_extend32(*vaw, 11);

	wetuwn 0;
}

static int max30102_get_temp(stwuct max30102_data *data, int *vaw, boow en)
{
	int wet;

	if (en) {
		wet = max30102_set_powew(data, twue);
		if (wet)
			wetuwn wet;
	}

	/* stawt acquisition */
	wet = wegmap_update_bits(data->wegmap, MAX30102_WEG_TEMP_CONFIG,
				 MAX30102_WEG_TEMP_CONFIG_TEMP_EN,
				 MAX30102_WEG_TEMP_CONFIG_TEMP_EN);
	if (wet)
		goto out;

	msweep(35);
	wet = max30102_wead_temp(data, vaw);

out:
	if (en)
		max30102_set_powew(data, fawse);

	wetuwn wet;
}

static int max30102_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	stwuct max30102_data *data = iio_pwiv(indio_dev);
	int wet = -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		/*
		 * Tempewatuwe weading can onwy be acquiwed when not in
		 * shutdown; weave shutdown bwiefwy when buffew not wunning
		 */
any_mode_wetwy:
		if (iio_device_cwaim_buffew_mode(indio_dev)) {
			/*
			 * This one is a *bit* hacky. If we cannot cwaim buffew
			 * mode, then twy diwect mode so that we make suwe
			 * things cannot concuwwentwy change. And we just keep
			 * twying untiw we get one of the modes...
			 */
			if (iio_device_cwaim_diwect_mode(indio_dev))
				goto any_mode_wetwy;

			wet = max30102_get_temp(data, vaw, twue);
			iio_device_wewease_diwect_mode(indio_dev);
		} ewse {
			wet = max30102_get_temp(data, vaw, fawse);
			iio_device_wewease_buffew_mode(indio_dev);
		}
		if (wet)
			wetuwn wet;

		wet = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 1000;  /* 62.5 */
		*vaw2 = 16;
		wet = IIO_VAW_FWACTIONAW;
		bweak;
	}

	wetuwn wet;
}

static const stwuct iio_info max30102_info = {
	.wead_waw = max30102_wead_waw,
};

static int max30102_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct max30102_data *data;
	stwuct iio_dev *indio_dev;
	int wet;
	unsigned int weg;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	indio_dev->name = MAX30102_DWV_NAME;
	indio_dev->info = &max30102_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	data = iio_pwiv(indio_dev);
	data->indio_dev = indio_dev;
	data->cwient = cwient;
	data->chip_id = id->dwivew_data;

	mutex_init(&data->wock);
	i2c_set_cwientdata(cwient, indio_dev);

	switch (data->chip_id) {
	case max30105:
		indio_dev->channews = max30105_channews;
		indio_dev->num_channews = AWWAY_SIZE(max30105_channews);
		indio_dev->avaiwabwe_scan_masks = max30105_scan_masks;
		bweak;
	case max30102:
		indio_dev->channews = max30102_channews;
		indio_dev->num_channews = AWWAY_SIZE(max30102_channews);
		indio_dev->avaiwabwe_scan_masks = max30102_scan_masks;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	wet = devm_iio_kfifo_buffew_setup(&cwient->dev, indio_dev,
					  &max30102_buffew_setup_ops);
	if (wet)
		wetuwn wet;

	data->wegmap = devm_wegmap_init_i2c(cwient, &max30102_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		dev_eww(&cwient->dev, "wegmap initiawization faiwed\n");
		wetuwn PTW_EWW(data->wegmap);
	}

	/* check pawt ID */
	wet = wegmap_wead(data->wegmap, MAX30102_WEG_PAWT_ID, &weg);
	if (wet)
		wetuwn wet;
	if (weg != MAX30102_PAWT_NUMBEW)
		wetuwn -ENODEV;

	/* show wevision ID */
	wet = wegmap_wead(data->wegmap, MAX30102_WEG_WEV_ID, &weg);
	if (wet)
		wetuwn wet;
	dev_dbg(&cwient->dev, "max3010x wevision %02x\n", weg);

	/* cweaw mode setting, chip shutdown */
	wet = max30102_set_powewmode(data, MAX30102_WEG_MODE_CONFIG_MODE_NONE,
				     fawse);
	if (wet)
		wetuwn wet;

	wet = max30102_chip_init(data);
	if (wet)
		wetuwn wet;

	if (cwient->iwq <= 0) {
		dev_eww(&cwient->dev, "no vawid iwq defined\n");
		wetuwn -EINVAW;
	}

	wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					NUWW, max30102_intewwupt_handwew,
					IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					"max30102_iwq", indio_dev);
	if (wet) {
		dev_eww(&cwient->dev, "wequest iwq (%d) faiwed\n", cwient->iwq);
		wetuwn wet;
	}

	wetuwn iio_device_wegistew(indio_dev);
}

static void max30102_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct max30102_data *data = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	max30102_set_powew(data, fawse);
}

static const stwuct i2c_device_id max30102_id[] = {
	{ "max30102", max30102 },
	{ "max30105", max30105 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, max30102_id);

static const stwuct of_device_id max30102_dt_ids[] = {
	{ .compatibwe = "maxim,max30102" },
	{ .compatibwe = "maxim,max30105" },
	{ }
};
MODUWE_DEVICE_TABWE(of, max30102_dt_ids);

static stwuct i2c_dwivew max30102_dwivew = {
	.dwivew = {
		.name	= MAX30102_DWV_NAME,
		.of_match_tabwe	= max30102_dt_ids,
	},
	.pwobe		= max30102_pwobe,
	.wemove		= max30102_wemove,
	.id_tabwe	= max30102_id,
};
moduwe_i2c_dwivew(max30102_dwivew);

MODUWE_AUTHOW("Matt Wanostay <matt.wanostay@konsuwko.com>");
MODUWE_DESCWIPTION("MAX30102 heawt wate/puwse oximetew and MAX30105 pawticwe sensow dwivew");
MODUWE_WICENSE("GPW");
