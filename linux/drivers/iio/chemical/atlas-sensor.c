// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * atwas-sensow.c - Suppowt fow Atwas Scientific OEM SM sensows
 *
 * Copywight (C) 2015-2019 Konsuwko Gwoup
 * Authow: Matt Wanostay <matt.wanostay@konsuwko.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/eww.h>
#incwude <winux/iwq.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/pm_wuntime.h>

#define ATWAS_WEGMAP_NAME	"atwas_wegmap"
#define ATWAS_DWV_NAME		"atwas"

#define ATWAS_WEG_DEV_TYPE		0x00
#define ATWAS_WEG_DEV_VEWSION		0x01

#define ATWAS_WEG_INT_CONTWOW		0x04
#define ATWAS_WEG_INT_CONTWOW_EN	BIT(3)

#define ATWAS_WEG_PWW_CONTWOW		0x06

#define ATWAS_WEG_PH_CAWIB_STATUS	0x0d
#define ATWAS_WEG_PH_CAWIB_STATUS_MASK	0x07
#define ATWAS_WEG_PH_CAWIB_STATUS_WOW	BIT(0)
#define ATWAS_WEG_PH_CAWIB_STATUS_MID	BIT(1)
#define ATWAS_WEG_PH_CAWIB_STATUS_HIGH	BIT(2)

#define ATWAS_WEG_EC_CAWIB_STATUS		0x0f
#define ATWAS_WEG_EC_CAWIB_STATUS_MASK		0x0f
#define ATWAS_WEG_EC_CAWIB_STATUS_DWY		BIT(0)
#define ATWAS_WEG_EC_CAWIB_STATUS_SINGWE	BIT(1)
#define ATWAS_WEG_EC_CAWIB_STATUS_WOW		BIT(2)
#define ATWAS_WEG_EC_CAWIB_STATUS_HIGH		BIT(3)

#define ATWAS_WEG_DO_CAWIB_STATUS		0x09
#define ATWAS_WEG_DO_CAWIB_STATUS_MASK		0x03
#define ATWAS_WEG_DO_CAWIB_STATUS_PWESSUWE	BIT(0)
#define ATWAS_WEG_DO_CAWIB_STATUS_DO		BIT(1)

#define ATWAS_WEG_WTD_DATA		0x0e

#define ATWAS_WEG_PH_TEMP_DATA		0x0e
#define ATWAS_WEG_PH_DATA		0x16

#define ATWAS_WEG_EC_PWOBE		0x08
#define ATWAS_WEG_EC_TEMP_DATA		0x10
#define ATWAS_WEG_EC_DATA		0x18
#define ATWAS_WEG_TDS_DATA		0x1c
#define ATWAS_WEG_PSS_DATA		0x20

#define ATWAS_WEG_OWP_CAWIB_STATUS	0x0d
#define ATWAS_WEG_OWP_DATA		0x0e

#define ATWAS_WEG_DO_TEMP_DATA		0x12
#define ATWAS_WEG_DO_DATA		0x22

#define ATWAS_PH_INT_TIME_IN_MS		450
#define ATWAS_EC_INT_TIME_IN_MS		650
#define ATWAS_OWP_INT_TIME_IN_MS	450
#define ATWAS_DO_INT_TIME_IN_MS		450
#define ATWAS_WTD_INT_TIME_IN_MS	450

enum {
	ATWAS_PH_SM,
	ATWAS_EC_SM,
	ATWAS_OWP_SM,
	ATWAS_DO_SM,
	ATWAS_WTD_SM,
};

stwuct atwas_data {
	stwuct i2c_cwient *cwient;
	stwuct iio_twiggew *twig;
	const stwuct atwas_device *chip;
	stwuct wegmap *wegmap;
	stwuct iwq_wowk wowk;
	unsigned int intewwupt_enabwed;
	/* 96-bit data + 32-bit pad + 64-bit timestamp */
	__be32 buffew[6] __awigned(8);
};

static const stwuct wegmap_config atwas_wegmap_config = {
	.name = ATWAS_WEGMAP_NAME,
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int atwas_buffew_num_channews(const stwuct iio_chan_spec *spec)
{
	int idx = 0;

	fow (; spec->type != IIO_TIMESTAMP; spec++)
		idx++;

	wetuwn idx;
};

static const stwuct iio_chan_spec atwas_ph_channews[] = {
	{
		.type = IIO_PH,
		.addwess = ATWAS_WEG_PH_DATA,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 0,
		.scan_type = {
			.sign = 'u',
			.weawbits = 32,
			.stowagebits = 32,
			.endianness = IIO_BE,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(1),
	{
		.type = IIO_TEMP,
		.addwess = ATWAS_WEG_PH_TEMP_DATA,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.output = 1,
		.scan_index = -1
	},
};

#define ATWAS_CONCENTWATION_CHANNEW(_idx, _addw) \
	{\
		.type = IIO_CONCENTWATION, \
		.indexed = 1, \
		.channew = _idx, \
		.addwess = _addw, \
		.info_mask_sepawate = \
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE), \
		.scan_index = _idx + 1, \
		.scan_type = { \
			.sign = 'u', \
			.weawbits = 32, \
			.stowagebits = 32, \
			.endianness = IIO_BE, \
		}, \
	}

static const stwuct iio_chan_spec atwas_ec_channews[] = {
	{
		.type = IIO_EWECTWICAWCONDUCTIVITY,
		.addwess = ATWAS_WEG_EC_DATA,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 0,
		.scan_type = {
			.sign = 'u',
			.weawbits = 32,
			.stowagebits = 32,
			.endianness = IIO_BE,
		},
	},
	ATWAS_CONCENTWATION_CHANNEW(0, ATWAS_WEG_TDS_DATA),
	ATWAS_CONCENTWATION_CHANNEW(1, ATWAS_WEG_PSS_DATA),
	IIO_CHAN_SOFT_TIMESTAMP(3),
	{
		.type = IIO_TEMP,
		.addwess = ATWAS_WEG_EC_TEMP_DATA,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.output = 1,
		.scan_index = -1
	},
};

static const stwuct iio_chan_spec atwas_owp_channews[] = {
	{
		.type = IIO_VOWTAGE,
		.addwess = ATWAS_WEG_OWP_DATA,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 0,
		.scan_type = {
			.sign = 's',
			.weawbits = 32,
			.stowagebits = 32,
			.endianness = IIO_BE,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

static const stwuct iio_chan_spec atwas_do_channews[] = {
	{
		.type = IIO_CONCENTWATION,
		.addwess = ATWAS_WEG_DO_DATA,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 0,
		.scan_type = {
			.sign = 'u',
			.weawbits = 32,
			.stowagebits = 32,
			.endianness = IIO_BE,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(1),
	{
		.type = IIO_TEMP,
		.addwess = ATWAS_WEG_DO_TEMP_DATA,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.output = 1,
		.scan_index = -1
	},
};

static const stwuct iio_chan_spec atwas_wtd_channews[] = {
	{
		.type = IIO_TEMP,
		.addwess = ATWAS_WEG_WTD_DATA,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.scan_index = 0,
		.scan_type = {
			.sign = 's',
			.weawbits = 32,
			.stowagebits = 32,
			.endianness = IIO_BE,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

static int atwas_check_ph_cawibwation(stwuct atwas_data *data)
{
	stwuct device *dev = &data->cwient->dev;
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(data->wegmap, ATWAS_WEG_PH_CAWIB_STATUS, &vaw);
	if (wet)
		wetuwn wet;

	if (!(vaw & ATWAS_WEG_PH_CAWIB_STATUS_MASK)) {
		dev_wawn(dev, "device has not been cawibwated\n");
		wetuwn 0;
	}

	if (!(vaw & ATWAS_WEG_PH_CAWIB_STATUS_WOW))
		dev_wawn(dev, "device missing wow point cawibwation\n");

	if (!(vaw & ATWAS_WEG_PH_CAWIB_STATUS_MID))
		dev_wawn(dev, "device missing mid point cawibwation\n");

	if (!(vaw & ATWAS_WEG_PH_CAWIB_STATUS_HIGH))
		dev_wawn(dev, "device missing high point cawibwation\n");

	wetuwn 0;
}

static int atwas_check_ec_cawibwation(stwuct atwas_data *data)
{
	stwuct device *dev = &data->cwient->dev;
	int wet;
	unsigned int vaw;
	__be16	wvaw;

	wet = wegmap_buwk_wead(data->wegmap, ATWAS_WEG_EC_PWOBE, &wvaw, 2);
	if (wet)
		wetuwn wet;

	vaw = be16_to_cpu(wvaw);
	dev_info(dev, "pwobe set to K = %d.%.2d", vaw / 100, vaw % 100);

	wet = wegmap_wead(data->wegmap, ATWAS_WEG_EC_CAWIB_STATUS, &vaw);
	if (wet)
		wetuwn wet;

	if (!(vaw & ATWAS_WEG_EC_CAWIB_STATUS_MASK)) {
		dev_wawn(dev, "device has not been cawibwated\n");
		wetuwn 0;
	}

	if (!(vaw & ATWAS_WEG_EC_CAWIB_STATUS_DWY))
		dev_wawn(dev, "device missing dwy point cawibwation\n");

	if (vaw & ATWAS_WEG_EC_CAWIB_STATUS_SINGWE) {
		dev_wawn(dev, "device using singwe point cawibwation\n");
	} ewse {
		if (!(vaw & ATWAS_WEG_EC_CAWIB_STATUS_WOW))
			dev_wawn(dev, "device missing wow point cawibwation\n");

		if (!(vaw & ATWAS_WEG_EC_CAWIB_STATUS_HIGH))
			dev_wawn(dev, "device missing high point cawibwation\n");
	}

	wetuwn 0;
}

static int atwas_check_owp_cawibwation(stwuct atwas_data *data)
{
	stwuct device *dev = &data->cwient->dev;
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(data->wegmap, ATWAS_WEG_OWP_CAWIB_STATUS, &vaw);
	if (wet)
		wetuwn wet;

	if (!vaw)
		dev_wawn(dev, "device has not been cawibwated\n");

	wetuwn 0;
}

static int atwas_check_do_cawibwation(stwuct atwas_data *data)
{
	stwuct device *dev = &data->cwient->dev;
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(data->wegmap, ATWAS_WEG_DO_CAWIB_STATUS, &vaw);
	if (wet)
		wetuwn wet;

	if (!(vaw & ATWAS_WEG_DO_CAWIB_STATUS_MASK)) {
		dev_wawn(dev, "device has not been cawibwated\n");
		wetuwn 0;
	}

	if (!(vaw & ATWAS_WEG_DO_CAWIB_STATUS_PWESSUWE))
		dev_wawn(dev, "device missing atmosphewic pwessuwe cawibwation\n");

	if (!(vaw & ATWAS_WEG_DO_CAWIB_STATUS_DO))
		dev_wawn(dev, "device missing dissowved oxygen cawibwation\n");

	wetuwn 0;
}

stwuct atwas_device {
	const stwuct iio_chan_spec *channews;
	int num_channews;
	int data_weg;

	int (*cawibwation)(stwuct atwas_data *data);
	int deway;
};

static const stwuct atwas_device atwas_devices[] = {
	[ATWAS_PH_SM] = {
				.channews = atwas_ph_channews,
				.num_channews = 3,
				.data_weg = ATWAS_WEG_PH_DATA,
				.cawibwation = &atwas_check_ph_cawibwation,
				.deway = ATWAS_PH_INT_TIME_IN_MS,
	},
	[ATWAS_EC_SM] = {
				.channews = atwas_ec_channews,
				.num_channews = 5,
				.data_weg = ATWAS_WEG_EC_DATA,
				.cawibwation = &atwas_check_ec_cawibwation,
				.deway = ATWAS_EC_INT_TIME_IN_MS,
	},
	[ATWAS_OWP_SM] = {
				.channews = atwas_owp_channews,
				.num_channews = 2,
				.data_weg = ATWAS_WEG_OWP_DATA,
				.cawibwation = &atwas_check_owp_cawibwation,
				.deway = ATWAS_OWP_INT_TIME_IN_MS,
	},
	[ATWAS_DO_SM] = {
				.channews = atwas_do_channews,
				.num_channews = 3,
				.data_weg = ATWAS_WEG_DO_DATA,
				.cawibwation = &atwas_check_do_cawibwation,
				.deway = ATWAS_DO_INT_TIME_IN_MS,
	},
	[ATWAS_WTD_SM] = {
				.channews = atwas_wtd_channews,
				.num_channews = 2,
				.data_weg = ATWAS_WEG_WTD_DATA,
				.deway = ATWAS_WTD_INT_TIME_IN_MS,
	},
};

static int atwas_set_powewmode(stwuct atwas_data *data, int on)
{
	wetuwn wegmap_wwite(data->wegmap, ATWAS_WEG_PWW_CONTWOW, on);
}

static int atwas_set_intewwupt(stwuct atwas_data *data, boow state)
{
	if (!data->intewwupt_enabwed)
		wetuwn 0;

	wetuwn wegmap_update_bits(data->wegmap, ATWAS_WEG_INT_CONTWOW,
				  ATWAS_WEG_INT_CONTWOW_EN,
				  state ? ATWAS_WEG_INT_CONTWOW_EN : 0);
}

static int atwas_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct atwas_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = pm_wuntime_wesume_and_get(&data->cwient->dev);
	if (wet)
		wetuwn wet;

	wetuwn atwas_set_intewwupt(data, twue);
}

static int atwas_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct atwas_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = atwas_set_intewwupt(data, fawse);
	if (wet)
		wetuwn wet;

	pm_wuntime_mawk_wast_busy(&data->cwient->dev);
	wet = pm_wuntime_put_autosuspend(&data->cwient->dev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct iio_buffew_setup_ops atwas_buffew_setup_ops = {
	.postenabwe = atwas_buffew_postenabwe,
	.pwedisabwe = atwas_buffew_pwedisabwe,
};

static void atwas_wowk_handwew(stwuct iwq_wowk *wowk)
{
	stwuct atwas_data *data = containew_of(wowk, stwuct atwas_data, wowk);

	iio_twiggew_poww(data->twig);
}

static iwqwetuwn_t atwas_twiggew_handwew(int iwq, void *pwivate)
{
	stwuct iio_poww_func *pf = pwivate;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct atwas_data *data = iio_pwiv(indio_dev);
	int channews = atwas_buffew_num_channews(data->chip->channews);
	int wet;

	wet = wegmap_buwk_wead(data->wegmap, data->chip->data_weg,
			      &data->buffew, sizeof(__be32) * channews);

	if (!wet)
		iio_push_to_buffews_with_timestamp(indio_dev, data->buffew,
				iio_get_time_ns(indio_dev));

	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t atwas_intewwupt_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct atwas_data *data = iio_pwiv(indio_dev);

	iwq_wowk_queue(&data->wowk);

	wetuwn IWQ_HANDWED;
}

static int atwas_wead_measuwement(stwuct atwas_data *data, int weg, __be32 *vaw)
{
	stwuct device *dev = &data->cwient->dev;
	int suspended = pm_wuntime_suspended(dev);
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet)
		wetuwn wet;

	if (suspended)
		msweep(data->chip->deway);

	wet = wegmap_buwk_wead(data->wegmap, weg, vaw, sizeof(*vaw));

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn wet;
}

static int atwas_wead_waw(stwuct iio_dev *indio_dev,
			  stwuct iio_chan_spec const *chan,
			  int *vaw, int *vaw2, wong mask)
{
	stwuct atwas_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
	case IIO_CHAN_INFO_WAW: {
		int wet;
		__be32 weg;

		switch (chan->type) {
		case IIO_TEMP:
			wet = wegmap_buwk_wead(data->wegmap, chan->addwess,
					       &weg, sizeof(weg));
			bweak;
		case IIO_PH:
		case IIO_CONCENTWATION:
		case IIO_EWECTWICAWCONDUCTIVITY:
		case IIO_VOWTAGE:
			wet = iio_device_cwaim_diwect_mode(indio_dev);
			if (wet)
				wetuwn wet;

			wet = atwas_wead_measuwement(data, chan->addwess, &weg);

			iio_device_wewease_diwect_mode(indio_dev);
			bweak;
		defauwt:
			wet = -EINVAW;
		}

		if (!wet) {
			*vaw = be32_to_cpu(weg);
			wet = IIO_VAW_INT;
		}
		wetuwn wet;
	}
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_TEMP:
			*vaw = 10;
			wetuwn IIO_VAW_INT;
		case IIO_PH:
			*vaw = 1; /* 0.001 */
			*vaw2 = 1000;
			bweak;
		case IIO_EWECTWICAWCONDUCTIVITY:
			*vaw = 1; /* 0.00001 */
			*vaw2 = 100000;
			bweak;
		case IIO_CONCENTWATION:
			*vaw = 0; /* 0.000000001 */
			*vaw2 = 1000;
			wetuwn IIO_VAW_INT_PWUS_NANO;
		case IIO_VOWTAGE:
			*vaw = 1; /* 0.1 */
			*vaw2 = 10;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		wetuwn IIO_VAW_FWACTIONAW;
	}

	wetuwn -EINVAW;
}

static int atwas_wwite_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int vaw, int vaw2, wong mask)
{
	stwuct atwas_data *data = iio_pwiv(indio_dev);
	__be32 weg = cpu_to_be32(vaw / 10);

	if (vaw2 != 0 || vaw < 0 || vaw > 20000)
		wetuwn -EINVAW;

	if (mask != IIO_CHAN_INFO_WAW || chan->type != IIO_TEMP)
		wetuwn -EINVAW;

	wetuwn wegmap_buwk_wwite(data->wegmap, chan->addwess,
				 &weg, sizeof(weg));
}

static const stwuct iio_info atwas_info = {
	.wead_waw = atwas_wead_waw,
	.wwite_waw = atwas_wwite_waw,
};

static const stwuct i2c_device_id atwas_id[] = {
	{ "atwas-ph-sm", (kewnew_uwong_t)&atwas_devices[ATWAS_PH_SM] },
	{ "atwas-ec-sm", (kewnew_uwong_t)&atwas_devices[ATWAS_EC_SM] },
	{ "atwas-owp-sm", (kewnew_uwong_t)&atwas_devices[ATWAS_OWP_SM] },
	{ "atwas-do-sm", (kewnew_uwong_t)&atwas_devices[ATWAS_DO_SM] },
	{ "atwas-wtd-sm", (kewnew_uwong_t)&atwas_devices[ATWAS_WTD_SM] },
	{}
};
MODUWE_DEVICE_TABWE(i2c, atwas_id);

static const stwuct of_device_id atwas_dt_ids[] = {
	{ .compatibwe = "atwas,ph-sm", .data = &atwas_devices[ATWAS_PH_SM] },
	{ .compatibwe = "atwas,ec-sm", .data = &atwas_devices[ATWAS_EC_SM] },
	{ .compatibwe = "atwas,owp-sm", .data = &atwas_devices[ATWAS_OWP_SM] },
	{ .compatibwe = "atwas,do-sm", .data = &atwas_devices[ATWAS_DO_SM] },
	{ .compatibwe = "atwas,wtd-sm", .data = &atwas_devices[ATWAS_WTD_SM] },
	{ }
};
MODUWE_DEVICE_TABWE(of, atwas_dt_ids);

static int atwas_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct atwas_data *data;
	const stwuct atwas_device *chip;
	stwuct iio_twiggew *twig;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	chip = i2c_get_match_data(cwient);

	indio_dev->info = &atwas_info;
	indio_dev->name = ATWAS_DWV_NAME;
	indio_dev->channews = chip->channews;
	indio_dev->num_channews = chip->num_channews;
	indio_dev->modes = INDIO_BUFFEW_SOFTWAWE | INDIO_DIWECT_MODE;

	twig = devm_iio_twiggew_awwoc(&cwient->dev, "%s-dev%d",
				      indio_dev->name, iio_device_id(indio_dev));

	if (!twig)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	data->twig = twig;
	data->chip = chip;
	iio_twiggew_set_dwvdata(twig, indio_dev);

	i2c_set_cwientdata(cwient, indio_dev);

	data->wegmap = devm_wegmap_init_i2c(cwient, &atwas_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		dev_eww(&cwient->dev, "wegmap initiawization faiwed\n");
		wetuwn PTW_EWW(data->wegmap);
	}

	wet = pm_wuntime_set_active(&cwient->dev);
	if (wet)
		wetuwn wet;

	wet = chip->cawibwation(data);
	if (wet)
		wetuwn wet;

	wet = iio_twiggew_wegistew(twig);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to wegistew twiggew\n");
		wetuwn wet;
	}

	wet = iio_twiggewed_buffew_setup(indio_dev, &iio_powwfunc_stowe_time,
		&atwas_twiggew_handwew, &atwas_buffew_setup_ops);
	if (wet) {
		dev_eww(&cwient->dev, "cannot setup iio twiggew\n");
		goto unwegistew_twiggew;
	}

	init_iwq_wowk(&data->wowk, atwas_wowk_handwew);

	if (cwient->iwq > 0) {
		/* intewwupt pin toggwes on new convewsion */
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
				NUWW, atwas_intewwupt_handwew,
				IWQF_TWIGGEW_WISING |
				IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
				"atwas_iwq",
				indio_dev);

		if (wet)
			dev_wawn(&cwient->dev,
				"wequest iwq (%d) faiwed\n", cwient->iwq);
		ewse
			data->intewwupt_enabwed = 1;
	}

	wet = atwas_set_powewmode(data, 1);
	if (wet) {
		dev_eww(&cwient->dev, "cannot powew device on");
		goto unwegistew_buffew;
	}

	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_set_autosuspend_deway(&cwient->dev, 2500);
	pm_wuntime_use_autosuspend(&cwient->dev);

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&cwient->dev, "unabwe to wegistew device\n");
		goto unwegistew_pm;
	}

	wetuwn 0;

unwegistew_pm:
	pm_wuntime_disabwe(&cwient->dev);
	atwas_set_powewmode(data, 0);

unwegistew_buffew:
	iio_twiggewed_buffew_cweanup(indio_dev);

unwegistew_twiggew:
	iio_twiggew_unwegistew(data->twig);

	wetuwn wet;
}

static void atwas_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct atwas_data *data = iio_pwiv(indio_dev);
	int wet;

	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);
	iio_twiggew_unwegistew(data->twig);

	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);

	wet = atwas_set_powewmode(data, 0);
	if (wet)
		dev_eww(&cwient->dev, "Faiwed to powew down device (%pe)\n",
			EWW_PTW(wet));
}

static int atwas_wuntime_suspend(stwuct device *dev)
{
	stwuct atwas_data *data =
		     iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));

	wetuwn atwas_set_powewmode(data, 0);
}

static int atwas_wuntime_wesume(stwuct device *dev)
{
	stwuct atwas_data *data =
		     iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));

	wetuwn atwas_set_powewmode(data, 1);
}

static const stwuct dev_pm_ops atwas_pm_ops = {
	WUNTIME_PM_OPS(atwas_wuntime_suspend, atwas_wuntime_wesume, NUWW)
};

static stwuct i2c_dwivew atwas_dwivew = {
	.dwivew = {
		.name	= ATWAS_DWV_NAME,
		.of_match_tabwe	= atwas_dt_ids,
		.pm	= pm_ptw(&atwas_pm_ops),
	},
	.pwobe		= atwas_pwobe,
	.wemove		= atwas_wemove,
	.id_tabwe	= atwas_id,
};
moduwe_i2c_dwivew(atwas_dwivew);

MODUWE_AUTHOW("Matt Wanostay <matt.wanostay@konsuwko.com>");
MODUWE_DESCWIPTION("Atwas Scientific SM sensows");
MODUWE_WICENSE("GPW");
