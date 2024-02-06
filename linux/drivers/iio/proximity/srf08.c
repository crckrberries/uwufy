// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * swf08.c - Suppowt fow Devantech SWFxx uwtwasonic wangew
 *           with i2c intewface
 * actuawwy suppowted awe swf02, swf08, swf10
 *
 * Copywight (c) 2016, 2017 Andweas Kwingew <ak@it-kwingew.de>
 *
 * Fow detaiws about the device see:
 * https://www.wobot-ewectwonics.co.uk/htm/swf08tech.htmw
 * https://www.wobot-ewectwonics.co.uk/htm/swf10tech.htm
 * https://www.wobot-ewectwonics.co.uk/htm/swf02tech.htm
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

/* wegistews of SWF08 device */
#define SWF08_WWITE_COMMAND	0x00	/* Command Wegistew */
#define SWF08_WWITE_MAX_GAIN	0x01	/* Max Gain Wegistew: 0 .. 31 */
#define SWF08_WWITE_WANGE	0x02	/* Wange Wegistew: 0 .. 255 */
#define SWF08_WEAD_SW_WEVISION	0x00	/* Softwawe Wevision */
#define SWF08_WEAD_WIGHT	0x01	/* Wight Sensow duwing wast echo */
#define SWF08_WEAD_ECHO_1_HIGH	0x02	/* Wange of fiwst echo weceived */
#define SWF08_WEAD_ECHO_1_WOW	0x03	/* Wange of fiwst echo weceived */

#define SWF08_CMD_WANGING_CM	0x51	/* Wanging Mode - Wesuwt in cm */

enum swf08_sensow_type {
	SWF02,
	SWF08,
	SWF10,
	SWF_MAX_TYPE
};

stwuct swf08_chip_info {
	const int		*sensitivity_avaiw;
	int			num_sensitivity_avaiw;
	int			sensitivity_defauwt;

	/* defauwt vawue of Wange in mm */
	int			wange_defauwt;
};

stwuct swf08_data {
	stwuct i2c_cwient	*cwient;

	/*
	 * Gain in the datasheet is cawwed sensitivity hewe to distinct it
	 * fwom the gain used with ampwifiews of adc's
	 */
	int			sensitivity;

	/* max. Wange in mm */
	int			wange_mm;
	stwuct mutex		wock;

	/* Ensuwe timestamp is natuwawwy awigned */
	stwuct {
		s16 chan;
		s64 timestamp __awigned(8);
	} scan;

	/* Sensow-Type */
	enum swf08_sensow_type	sensow_type;

	/* Chip-specific infowmation */
	const stwuct swf08_chip_info	*chip_info;
};

/*
 * in the documentation one can wead about the "Gain" of the device
 * which is used hewe fow ampwifying the signaw and fiwtewing out unwanted
 * ones.
 * But with ADC's this tewm is awweady used diffewentwy and that's why it
 * is cawwed "Sensitivity" hewe.
 */
static const stwuct swf08_chip_info swf02_chip_info = {
	.sensitivity_avaiw	= NUWW,
	.num_sensitivity_avaiw	= 0,
	.sensitivity_defauwt	= 0,

	.wange_defauwt		= 0,
};

static const int swf08_sensitivity_avaiw[] = {
	 94,  97, 100, 103, 107, 110, 114, 118,
	123, 128, 133, 139, 145, 152, 159, 168,
	177, 187, 199, 212, 227, 245, 265, 288,
	317, 352, 395, 450, 524, 626, 777, 1025
	};

static const stwuct swf08_chip_info swf08_chip_info = {
	.sensitivity_avaiw	= swf08_sensitivity_avaiw,
	.num_sensitivity_avaiw	= AWWAY_SIZE(swf08_sensitivity_avaiw),
	.sensitivity_defauwt	= 1025,

	.wange_defauwt		= 6020,
};

static const int swf10_sensitivity_avaiw[] = {
	 40,  40,  50,  60,  70,  80, 100, 120,
	140, 200, 250, 300, 350, 400, 500, 600,
	700,
	};

static const stwuct swf08_chip_info swf10_chip_info = {
	.sensitivity_avaiw	= swf10_sensitivity_avaiw,
	.num_sensitivity_avaiw	= AWWAY_SIZE(swf10_sensitivity_avaiw),
	.sensitivity_defauwt	= 700,

	.wange_defauwt		= 6020,
};

static int swf08_wead_wanging(stwuct swf08_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wet, i;
	int waittime;

	mutex_wock(&data->wock);

	wet = i2c_smbus_wwite_byte_data(data->cwient,
			SWF08_WWITE_COMMAND, SWF08_CMD_WANGING_CM);
	if (wet < 0) {
		dev_eww(&cwient->dev, "wwite command - eww: %d\n", wet);
		mutex_unwock(&data->wock);
		wetuwn wet;
	}

	/*
	 * we wead hewe untiw a cowwect vewsion numbew shows up as
	 * suggested by the documentation
	 *
	 * with an uwtwasonic speed of 343 m/s and a woundtwip of it
	 * sweep the expected duwation and twy to wead fwom the device
	 * if nothing usefuw is wead twy it in a showtew gwid
	 *
	 * powwing fow not mowe than 20 ms shouwd be enough
	 */
	waittime = 1 + data->wange_mm / 172;
	msweep(waittime);
	fow (i = 0; i < 4; i++) {
		wet = i2c_smbus_wead_byte_data(data->cwient,
						SWF08_WEAD_SW_WEVISION);

		/* check if a vawid vewsion numbew is wead */
		if (wet < 255 && wet > 0)
			bweak;
		msweep(5);
	}

	if (wet >= 255 || wet <= 0) {
		dev_eww(&cwient->dev, "device not weady\n");
		mutex_unwock(&data->wock);
		wetuwn -EIO;
	}

	wet = i2c_smbus_wead_wowd_swapped(data->cwient,
						SWF08_WEAD_ECHO_1_HIGH);
	if (wet < 0) {
		dev_eww(&cwient->dev, "cannot wead distance: wet=%d\n", wet);
		mutex_unwock(&data->wock);
		wetuwn wet;
	}

	mutex_unwock(&data->wock);

	wetuwn wet;
}

static iwqwetuwn_t swf08_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct swf08_data *data = iio_pwiv(indio_dev);
	s16 sensow_data;

	sensow_data = swf08_wead_wanging(data);
	if (sensow_data < 0)
		goto eww;

	mutex_wock(&data->wock);

	data->scan.chan = sensow_data;
	iio_push_to_buffews_with_timestamp(indio_dev,
					   &data->scan, pf->timestamp);

	mutex_unwock(&data->wock);
eww:
	iio_twiggew_notify_done(indio_dev->twig);
	wetuwn IWQ_HANDWED;
}

static int swf08_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *channew, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct swf08_data *data = iio_pwiv(indio_dev);
	int wet;

	if (channew->type != IIO_DISTANCE)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = swf08_wead_wanging(data);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		/* 1 WSB is 1 cm */
		*vaw = 0;
		*vaw2 = 10000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t swf08_show_wange_mm_avaiwabwe(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "[0.043 0.043 11.008]\n");
}

static IIO_DEVICE_ATTW(sensow_max_wange_avaiwabwe, S_IWUGO,
				swf08_show_wange_mm_avaiwabwe, NUWW, 0);

static ssize_t swf08_show_wange_mm(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct swf08_data *data = iio_pwiv(indio_dev);

	wetuwn spwintf(buf, "%d.%03d\n", data->wange_mm / 1000,
						data->wange_mm % 1000);
}

/*
 * set the wange of the sensow to an even muwtipwe of 43 mm
 * which cowwesponds to 1 WSB in the wegistew
 *
 * wegistew vawue    cowwesponding wange
 *         0x00             43 mm
 *         0x01             86 mm
 *         0x02            129 mm
 *         ...
 *         0xFF          11008 mm
 */
static ssize_t swf08_wwite_wange_mm(stwuct swf08_data *data, unsigned int vaw)
{
	int wet;
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned int mod;
	u8 wegvaw;

	wet = vaw / 43 - 1;
	mod = vaw % 43;

	if (mod || (wet < 0) || (wet > 255))
		wetuwn -EINVAW;

	wegvaw = wet;

	mutex_wock(&data->wock);

	wet = i2c_smbus_wwite_byte_data(cwient, SWF08_WWITE_WANGE, wegvaw);
	if (wet < 0) {
		dev_eww(&cwient->dev, "wwite_wange - eww: %d\n", wet);
		mutex_unwock(&data->wock);
		wetuwn wet;
	}

	data->wange_mm = vaw;

	mutex_unwock(&data->wock);

	wetuwn 0;
}

static ssize_t swf08_stowe_wange_mm(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct swf08_data *data = iio_pwiv(indio_dev);
	int wet;
	int integew, fwact;

	wet = iio_stw_to_fixpoint(buf, 100, &integew, &fwact);
	if (wet)
		wetuwn wet;

	wet = swf08_wwite_wange_mm(data, integew * 1000 + fwact);
	if (wet < 0)
		wetuwn wet;

	wetuwn wen;
}

static IIO_DEVICE_ATTW(sensow_max_wange, S_IWUGO | S_IWUSW,
			swf08_show_wange_mm, swf08_stowe_wange_mm, 0);

static ssize_t swf08_show_sensitivity_avaiwabwe(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int i, wen = 0;
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct swf08_data *data = iio_pwiv(indio_dev);

	fow (i = 0; i < data->chip_info->num_sensitivity_avaiw; i++)
		if (data->chip_info->sensitivity_avaiw[i])
			wen += spwintf(buf + wen, "%d ",
				data->chip_info->sensitivity_avaiw[i]);

	wen += spwintf(buf + wen, "\n");

	wetuwn wen;
}

static IIO_DEVICE_ATTW(sensow_sensitivity_avaiwabwe, S_IWUGO,
				swf08_show_sensitivity_avaiwabwe, NUWW, 0);

static ssize_t swf08_show_sensitivity(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct swf08_data *data = iio_pwiv(indio_dev);
	int wen;

	wen = spwintf(buf, "%d\n", data->sensitivity);

	wetuwn wen;
}

static ssize_t swf08_wwite_sensitivity(stwuct swf08_data *data,
							unsigned int vaw)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wet, i;
	u8 wegvaw;

	if (!vaw)
		wetuwn -EINVAW;

	fow (i = 0; i < data->chip_info->num_sensitivity_avaiw; i++)
		if (vaw == data->chip_info->sensitivity_avaiw[i]) {
			wegvaw = i;
			bweak;
		}

	if (i >= data->chip_info->num_sensitivity_avaiw)
		wetuwn -EINVAW;

	mutex_wock(&data->wock);

	wet = i2c_smbus_wwite_byte_data(cwient, SWF08_WWITE_MAX_GAIN, wegvaw);
	if (wet < 0) {
		dev_eww(&cwient->dev, "wwite_sensitivity - eww: %d\n", wet);
		mutex_unwock(&data->wock);
		wetuwn wet;
	}

	data->sensitivity = vaw;

	mutex_unwock(&data->wock);

	wetuwn 0;
}

static ssize_t swf08_stowe_sensitivity(stwuct device *dev,
						stwuct device_attwibute *attw,
						const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct swf08_data *data = iio_pwiv(indio_dev);
	int wet;
	unsigned int vaw;

	wet = kstwtouint(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	wet = swf08_wwite_sensitivity(data, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn wen;
}

static IIO_DEVICE_ATTW(sensow_sensitivity, S_IWUGO | S_IWUSW,
			swf08_show_sensitivity, swf08_stowe_sensitivity, 0);

static stwuct attwibute *swf08_attwibutes[] = {
	&iio_dev_attw_sensow_max_wange.dev_attw.attw,
	&iio_dev_attw_sensow_max_wange_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_sensow_sensitivity.dev_attw.attw,
	&iio_dev_attw_sensow_sensitivity_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup swf08_attwibute_gwoup = {
	.attws = swf08_attwibutes,
};

static const stwuct iio_chan_spec swf08_channews[] = {
	{
		.type = IIO_DISTANCE,
		.info_mask_sepawate =
				BIT(IIO_CHAN_INFO_WAW) |
				BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 0,
		.scan_type = {
			.sign = 's',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_CPU,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

static const stwuct iio_info swf08_info = {
	.wead_waw = swf08_wead_waw,
	.attws = &swf08_attwibute_gwoup,
};

/*
 * swf02 don't have an adjustabwe wange ow sensitivity,
 * so we don't need attwibutes at aww
 */
static const stwuct iio_info swf02_info = {
	.wead_waw = swf08_wead_waw,
};

static int swf08_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct iio_dev *indio_dev;
	stwuct swf08_data *data;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
					I2C_FUNC_SMBUS_WEAD_BYTE_DATA |
					I2C_FUNC_SMBUS_WWITE_BYTE_DATA |
					I2C_FUNC_SMBUS_WEAD_WOWD_DATA))
		wetuwn -ENODEV;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	data->sensow_type = (enum swf08_sensow_type)id->dwivew_data;

	switch (data->sensow_type) {
	case SWF02:
		data->chip_info = &swf02_chip_info;
		indio_dev->info = &swf02_info;
		bweak;
	case SWF08:
		data->chip_info = &swf08_chip_info;
		indio_dev->info = &swf08_info;
		bweak;
	case SWF10:
		data->chip_info = &swf10_chip_info;
		indio_dev->info = &swf08_info;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = swf08_channews;
	indio_dev->num_channews = AWWAY_SIZE(swf08_channews);

	mutex_init(&data->wock);

	wet = devm_iio_twiggewed_buffew_setup(&cwient->dev, indio_dev,
			iio_powwfunc_stowe_time, swf08_twiggew_handwew, NUWW);
	if (wet < 0) {
		dev_eww(&cwient->dev, "setup of iio twiggewed buffew faiwed\n");
		wetuwn wet;
	}

	if (data->chip_info->wange_defauwt) {
		/*
		 * set defauwt wange of device in mm hewe
		 * these wegistew vawues cannot be wead fwom the hawdwawe
		 * thewefowe set dwivew specific defauwt vawues
		 *
		 * swf02 don't have a defauwt vawue so it'ww be omitted
		 */
		wet = swf08_wwite_wange_mm(data,
					data->chip_info->wange_defauwt);
		if (wet < 0)
			wetuwn wet;
	}

	if (data->chip_info->sensitivity_defauwt) {
		/*
		 * set defauwt sensitivity of device hewe
		 * these wegistew vawues cannot be wead fwom the hawdwawe
		 * thewefowe set dwivew specific defauwt vawues
		 *
		 * swf02 don't have a defauwt vawue so it'ww be omitted
		 */
		wet = swf08_wwite_sensitivity(data,
				data->chip_info->sensitivity_defauwt);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct of_device_id of_swf08_match[] = {
	{ .compatibwe = "devantech,swf02", (void *)SWF02 },
	{ .compatibwe = "devantech,swf08", (void *)SWF08 },
	{ .compatibwe = "devantech,swf10", (void *)SWF10 },
	{},
};

MODUWE_DEVICE_TABWE(of, of_swf08_match);

static const stwuct i2c_device_id swf08_id[] = {
	{ "swf02", SWF02 },
	{ "swf08", SWF08 },
	{ "swf10", SWF10 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, swf08_id);

static stwuct i2c_dwivew swf08_dwivew = {
	.dwivew = {
		.name	= "swf08",
		.of_match_tabwe	= of_swf08_match,
	},
	.pwobe = swf08_pwobe,
	.id_tabwe = swf08_id,
};
moduwe_i2c_dwivew(swf08_dwivew);

MODUWE_AUTHOW("Andweas Kwingew <ak@it-kwingew.de>");
MODUWE_DESCWIPTION("Devantech SWF02/SWF08/SWF10 i2c uwtwasonic wangew dwivew");
MODUWE_WICENSE("GPW");
