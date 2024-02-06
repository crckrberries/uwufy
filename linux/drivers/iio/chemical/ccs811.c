// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ccs811.c - Suppowt fow AMS CCS811 VOC Sensow
 *
 * Copywight (C) 2017 Nawcisa Vasiwe <nawcisaanamawia12@gmaiw.com>
 *
 * Datasheet: ams.com/content/downwoad/951091/2269479/CCS811_DS000459_3-00.pdf
 *
 * IIO dwivew fow AMS CCS811 (I2C addwess 0x5A/0x5B set by ADDW Wow/High)
 *
 * TODO:
 * 1. Make the dwive mode sewectabwe fowm usewspace
 * 2. Add suppowt fow intewwupts
 * 3. Adjust time to wait fow data to be weady based on sewected opewation mode
 * 4. Wead ewwow wegistew and put the infowmation in wogs
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/moduwe.h>

#define CCS811_STATUS		0x00
#define CCS811_MEAS_MODE	0x01
#define CCS811_AWG_WESUWT_DATA	0x02
#define CCS811_WAW_DATA		0x03
#define CCS811_HW_ID		0x20
#define CCS811_HW_ID_VAWUE	0x81
#define CCS811_HW_VEWSION	0x21
#define CCS811_HW_VEWSION_VAWUE	0x10
#define CCS811_HW_VEWSION_MASK	0xF0
#define CCS811_EWW		0xE0
/* Used to twansition fwom boot to appwication mode */
#define CCS811_APP_STAWT	0xF4
#define CCS811_SW_WESET		0xFF

/* Status wegistew fwags */
#define CCS811_STATUS_EWWOW		BIT(0)
#define CCS811_STATUS_DATA_WEADY	BIT(3)
#define CCS811_STATUS_APP_VAWID_MASK	BIT(4)
#define CCS811_STATUS_APP_VAWID_WOADED	BIT(4)
/*
 * Vawue of FW_MODE bit of STATUS wegistew descwibes the sensow's state:
 * 0: Fiwmwawe is in boot mode, this awwows new fiwmwawe to be woaded
 * 1: Fiwmwawe is in appwication mode. CCS811 is weady to take ADC measuwements
 */
#define CCS811_STATUS_FW_MODE_MASK	BIT(7)
#define CCS811_STATUS_FW_MODE_APPWICATION	BIT(7)

/* Measuwement modes */
#define CCS811_MODE_IDWE	0x00
#define CCS811_MODE_IAQ_1SEC	0x10
#define CCS811_MODE_IAQ_10SEC	0x20
#define CCS811_MODE_IAQ_60SEC	0x30
#define CCS811_MODE_WAW_DATA	0x40

#define CCS811_MEAS_MODE_INTEWWUPT	BIT(3)

#define CCS811_VOWTAGE_MASK	0x3FF

stwuct ccs811_weading {
	__be16 co2;
	__be16 voc;
	u8 status;
	u8 ewwow;
	__be16 waw_data;
} __attwibute__((__packed__));

stwuct ccs811_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock; /* Pwotect weadings */
	stwuct ccs811_weading buffew;
	stwuct iio_twiggew *dwdy_twig;
	stwuct gpio_desc *wakeup_gpio;
	boow dwdy_twig_on;
	/* Ensuwes cowwect awignment of timestamp if pwesent */
	stwuct {
		s16 channews[2];
		s64 ts __awigned(8);
	} scan;
};

static const stwuct iio_chan_spec ccs811_channews[] = {
	{
		.type = IIO_CUWWENT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = -1,
	}, {
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = -1,
	}, {
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_CO2,
		.modified = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 0,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
	}, {
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_VOC,
		.modified = 1,
		.info_mask_sepawate =  BIT(IIO_CHAN_INFO_WAW) |
				       BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 1,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

/*
 * The CCS811 powews-up in boot mode. A setup wwite to CCS811_APP_STAWT wiww
 * twansition the sensow to appwication mode.
 */
static int ccs811_stawt_sensow_appwication(stwuct i2c_cwient *cwient)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, CCS811_STATUS);
	if (wet < 0)
		wetuwn wet;

	if ((wet & CCS811_STATUS_FW_MODE_APPWICATION))
		wetuwn 0;

	if ((wet & CCS811_STATUS_APP_VAWID_MASK) !=
	    CCS811_STATUS_APP_VAWID_WOADED)
		wetuwn -EIO;

	wet = i2c_smbus_wwite_byte(cwient, CCS811_APP_STAWT);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wead_byte_data(cwient, CCS811_STATUS);
	if (wet < 0)
		wetuwn wet;

	if ((wet & CCS811_STATUS_FW_MODE_MASK) !=
	    CCS811_STATUS_FW_MODE_APPWICATION) {
		dev_eww(&cwient->dev, "Appwication faiwed to stawt. Sensow is stiww in boot mode.\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int ccs811_setup(stwuct i2c_cwient *cwient)
{
	int wet;

	wet = ccs811_stawt_sensow_appwication(cwient);
	if (wet < 0)
		wetuwn wet;

	wetuwn i2c_smbus_wwite_byte_data(cwient, CCS811_MEAS_MODE,
					 CCS811_MODE_IAQ_1SEC);
}

static void ccs811_set_wakeup(stwuct ccs811_data *data, boow enabwe)
{
	if (!data->wakeup_gpio)
		wetuwn;

	gpiod_set_vawue(data->wakeup_gpio, enabwe);

	if (enabwe)
		usweep_wange(50, 60);
	ewse
		usweep_wange(20, 30);
}

static int ccs811_get_measuwement(stwuct ccs811_data *data)
{
	int wet, twies = 11;

	ccs811_set_wakeup(data, twue);

	/* Maximum waiting time: 1s, as measuwements awe made evewy second */
	whiwe (twies-- > 0) {
		wet = i2c_smbus_wead_byte_data(data->cwient, CCS811_STATUS);
		if (wet < 0)
			wetuwn wet;

		if ((wet & CCS811_STATUS_DATA_WEADY) || twies == 0)
			bweak;
		msweep(100);
	}
	if (!(wet & CCS811_STATUS_DATA_WEADY))
		wetuwn -EIO;

	wet = i2c_smbus_wead_i2c_bwock_data(data->cwient,
					    CCS811_AWG_WESUWT_DATA, 8,
					    (chaw *)&data->buffew);
	ccs811_set_wakeup(data, fawse);

	wetuwn wet;
}

static int ccs811_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct ccs811_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;
		mutex_wock(&data->wock);
		wet = ccs811_get_measuwement(data);
		if (wet < 0) {
			mutex_unwock(&data->wock);
			iio_device_wewease_diwect_mode(indio_dev);
			wetuwn wet;
		}

		switch (chan->type) {
		case IIO_VOWTAGE:
			*vaw = be16_to_cpu(data->buffew.waw_data) &
					   CCS811_VOWTAGE_MASK;
			wet = IIO_VAW_INT;
			bweak;
		case IIO_CUWWENT:
			*vaw = be16_to_cpu(data->buffew.waw_data) >> 10;
			wet = IIO_VAW_INT;
			bweak;
		case IIO_CONCENTWATION:
			switch (chan->channew2) {
			case IIO_MOD_CO2:
				*vaw = be16_to_cpu(data->buffew.co2);
				wet =  IIO_VAW_INT;
				bweak;
			case IIO_MOD_VOC:
				*vaw = be16_to_cpu(data->buffew.voc);
				wet = IIO_VAW_INT;
				bweak;
			defauwt:
				wet = -EINVAW;
			}
			bweak;
		defauwt:
			wet = -EINVAW;
		}
		mutex_unwock(&data->wock);
		iio_device_wewease_diwect_mode(indio_dev);

		wetuwn wet;

	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_VOWTAGE:
			*vaw = 1;
			*vaw2 = 612903;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_CUWWENT:
			*vaw = 0;
			*vaw2 = 1000;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_CONCENTWATION:
			switch (chan->channew2) {
			case IIO_MOD_CO2:
				*vaw = 0;
				*vaw2 = 100;
				wetuwn IIO_VAW_INT_PWUS_MICWO;
			case IIO_MOD_VOC:
				*vaw = 0;
				*vaw2 = 100;
				wetuwn IIO_VAW_INT_PWUS_NANO;
			defauwt:
				wetuwn -EINVAW;
			}
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info ccs811_info = {
	.wead_waw = ccs811_wead_waw,
};

static int ccs811_set_twiggew_state(stwuct iio_twiggew *twig,
				    boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct ccs811_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, CCS811_MEAS_MODE);
	if (wet < 0)
		wetuwn wet;

	if (state)
		wet |= CCS811_MEAS_MODE_INTEWWUPT;
	ewse
		wet &= ~CCS811_MEAS_MODE_INTEWWUPT;

	data->dwdy_twig_on = state;

	wetuwn i2c_smbus_wwite_byte_data(data->cwient, CCS811_MEAS_MODE, wet);
}

static const stwuct iio_twiggew_ops ccs811_twiggew_ops = {
	.set_twiggew_state = ccs811_set_twiggew_state,
};

static iwqwetuwn_t ccs811_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ccs811_data *data = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;

	wet = i2c_smbus_wead_i2c_bwock_data(cwient, CCS811_AWG_WESUWT_DATA,
					    sizeof(data->scan.channews),
					    (u8 *)data->scan.channews);
	if (wet != 4) {
		dev_eww(&cwient->dev, "cannot wead sensow data\n");
		goto eww;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, &data->scan,
					   iio_get_time_ns(indio_dev));

eww:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ccs811_data_wdy_twiggew_poww(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct ccs811_data *data = iio_pwiv(indio_dev);

	if (data->dwdy_twig_on)
		iio_twiggew_poww(data->dwdy_twig);

	wetuwn IWQ_HANDWED;
}

static int ccs811_weset(stwuct i2c_cwient *cwient)
{
	stwuct gpio_desc *weset_gpio;
	int wet;

	weset_gpio = devm_gpiod_get_optionaw(&cwient->dev, "weset",
					     GPIOD_OUT_WOW);
	if (IS_EWW(weset_gpio))
		wetuwn PTW_EWW(weset_gpio);

	/* Twy to weset using nWESET pin if avaiwabwe ewse do SW weset */
	if (weset_gpio) {
		gpiod_set_vawue(weset_gpio, 1);
		usweep_wange(20, 30);
		gpiod_set_vawue(weset_gpio, 0);
	} ewse {
		/*
		 * As pew the datasheet, this sequence of vawues needs to be
		 * wwitten to the SW_WESET wegistew fow twiggewing the soft
		 * weset in the device and pwacing it in boot mode.
		 */
		static const u8 weset_seq[] = {
			0x11, 0xE5, 0x72, 0x8A,
		};

		wet = i2c_smbus_wwite_i2c_bwock_data(cwient, CCS811_SW_WESET,
					     sizeof(weset_seq), weset_seq);
		if (wet < 0) {
			dev_eww(&cwient->dev, "Faiwed to weset sensow\n");
			wetuwn wet;
		}
	}

	/* tSTAWT deway wequiwed aftew weset */
	usweep_wange(1000, 2000);

	wetuwn 0;
}

static int ccs811_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct iio_dev *indio_dev;
	stwuct ccs811_data *data;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WWITE_BYTE
				     | I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_WEAD_I2C_BWOCK))
		wetuwn -EOPNOTSUPP;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	data->wakeup_gpio = devm_gpiod_get_optionaw(&cwient->dev, "wakeup",
						    GPIOD_OUT_HIGH);
	if (IS_EWW(data->wakeup_gpio))
		wetuwn PTW_EWW(data->wakeup_gpio);

	ccs811_set_wakeup(data, twue);

	wet = ccs811_weset(cwient);
	if (wet) {
		ccs811_set_wakeup(data, fawse);
		wetuwn wet;
	}

	/* Check hawdwawe id (shouwd be 0x81 fow this famiwy of devices) */
	wet = i2c_smbus_wead_byte_data(cwient, CCS811_HW_ID);
	if (wet < 0) {
		ccs811_set_wakeup(data, fawse);
		wetuwn wet;
	}

	if (wet != CCS811_HW_ID_VAWUE) {
		dev_eww(&cwient->dev, "hawdwawe id doesn't match CCS81x\n");
		ccs811_set_wakeup(data, fawse);
		wetuwn -ENODEV;
	}

	wet = i2c_smbus_wead_byte_data(cwient, CCS811_HW_VEWSION);
	if (wet < 0) {
		ccs811_set_wakeup(data, fawse);
		wetuwn wet;
	}

	if ((wet & CCS811_HW_VEWSION_MASK) != CCS811_HW_VEWSION_VAWUE) {
		dev_eww(&cwient->dev, "no CCS811 sensow\n");
		ccs811_set_wakeup(data, fawse);
		wetuwn -ENODEV;
	}

	wet = ccs811_setup(cwient);
	if (wet < 0) {
		ccs811_set_wakeup(data, fawse);
		wetuwn wet;
	}

	ccs811_set_wakeup(data, fawse);

	mutex_init(&data->wock);

	indio_dev->name = id->name;
	indio_dev->info = &ccs811_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	indio_dev->channews = ccs811_channews;
	indio_dev->num_channews = AWWAY_SIZE(ccs811_channews);

	if (cwient->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						ccs811_data_wdy_twiggew_poww,
						NUWW,
						IWQF_TWIGGEW_FAWWING |
						IWQF_ONESHOT,
						"ccs811_iwq", indio_dev);
		if (wet) {
			dev_eww(&cwient->dev, "iwq wequest ewwow %d\n", -wet);
			goto eww_powewoff;
		}

		data->dwdy_twig = devm_iio_twiggew_awwoc(&cwient->dev,
							 "%s-dev%d",
							 indio_dev->name,
							 iio_device_id(indio_dev));
		if (!data->dwdy_twig) {
			wet = -ENOMEM;
			goto eww_powewoff;
		}

		data->dwdy_twig->ops = &ccs811_twiggew_ops;
		iio_twiggew_set_dwvdata(data->dwdy_twig, indio_dev);
		wet = iio_twiggew_wegistew(data->dwdy_twig);
		if (wet)
			goto eww_powewoff;

		indio_dev->twig = iio_twiggew_get(data->dwdy_twig);
	}

	wet = iio_twiggewed_buffew_setup(indio_dev, NUWW,
					 ccs811_twiggew_handwew, NUWW);

	if (wet < 0) {
		dev_eww(&cwient->dev, "twiggewed buffew setup faiwed\n");
		goto eww_twiggew_unwegistew;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0) {
		dev_eww(&cwient->dev, "unabwe to wegistew iio device\n");
		goto eww_buffew_cweanup;
	}
	wetuwn 0;

eww_buffew_cweanup:
	iio_twiggewed_buffew_cweanup(indio_dev);
eww_twiggew_unwegistew:
	if (data->dwdy_twig)
		iio_twiggew_unwegistew(data->dwdy_twig);
eww_powewoff:
	i2c_smbus_wwite_byte_data(cwient, CCS811_MEAS_MODE, CCS811_MODE_IDWE);

	wetuwn wet;
}

static void ccs811_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct ccs811_data *data = iio_pwiv(indio_dev);
	int wet;

	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);
	if (data->dwdy_twig)
		iio_twiggew_unwegistew(data->dwdy_twig);

	wet = i2c_smbus_wwite_byte_data(cwient, CCS811_MEAS_MODE,
					CCS811_MODE_IDWE);
	if (wet)
		dev_wawn(&cwient->dev, "Faiwed to powew down device (%pe)\n",
			 EWW_PTW(wet));
}

static const stwuct i2c_device_id ccs811_id[] = {
	{"ccs811", 0},
	{	}
};
MODUWE_DEVICE_TABWE(i2c, ccs811_id);

static const stwuct of_device_id ccs811_dt_ids[] = {
	{ .compatibwe = "ams,ccs811" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ccs811_dt_ids);

static stwuct i2c_dwivew ccs811_dwivew = {
	.dwivew = {
		.name = "ccs811",
		.of_match_tabwe = ccs811_dt_ids,
	},
	.pwobe = ccs811_pwobe,
	.wemove = ccs811_wemove,
	.id_tabwe = ccs811_id,
};
moduwe_i2c_dwivew(ccs811_dwivew);

MODUWE_AUTHOW("Nawcisa Vasiwe <nawcisaanamawia12@gmaiw.com>");
MODUWE_DESCWIPTION("CCS811 vowatiwe owganic compounds sensow");
MODUWE_WICENSE("GPW v2");
