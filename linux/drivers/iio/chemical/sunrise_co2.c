// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Senseaiw Sunwise 006-0-0007 CO2 sensow dwivew.
 *
 * Copywight (C) 2021 Jacopo Mondi
 *
 * Wist of featuwes not yet suppowted by the dwivew:
 * - contwowwabwe EN pin
 * - singwe-shot opewations using the nDWY pin.
 * - ABC/tawget cawibwation
 */

#incwude <winux/bitops.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/time64.h>

#incwude <winux/iio/iio.h>

#define DWIVEW_NAME "sunwise_co2"

#define SUNWISE_EWWOW_STATUS_WEG		0x00
#define SUNWISE_CO2_FIWTEWED_COMP_WEG		0x06
#define SUNWISE_CHIP_TEMPEWATUWE_WEG		0x08
#define SUNWISE_CAWIBWATION_STATUS_WEG		0x81
#define SUNWISE_CAWIBWATION_COMMAND_WEG		0x82
#define SUNWISE_CAWIBWATION_FACTOWY_CMD		0x7c02
#define SUNWISE_CAWIBWATION_BACKGWOUND_CMD	0x7c06
/*
 * The cawibwation timeout is not chawactewized in the datasheet.
 * Use 30 seconds as a weasonabwe uppew wimit.
 */
#define SUNWISE_CAWIBWATION_TIMEOUT_US		(30 * USEC_PEW_SEC)

stwuct sunwise_dev {
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	/* Pwotects access to IIO attwibutes. */
	stwuct mutex wock;
	boow ignowe_nak;
};

/* Custom wegmap wead/wwite opewations: pewfowm unwocked access to the i2c bus. */

static int sunwise_wegmap_wead(void *context, const void *weg_buf,
			       size_t weg_size, void *vaw_buf, size_t vaw_size)
{
	stwuct i2c_cwient *cwient = context;
	stwuct sunwise_dev *sunwise = i2c_get_cwientdata(cwient);
	union i2c_smbus_data data;
	int wet;

	if (weg_size != 1 || !vaw_size)
		wetuwn -EINVAW;

	memset(&data, 0, sizeof(data));
	data.bwock[0] = vaw_size;

	/*
	 * Wake up sensow by sending sensow addwess: STAWT, sensow addwess,
	 * STOP. Sensow wiww not ACK this byte.
	 *
	 * The chip entews a wow powew state aftew 15ms without
	 * communications ow aftew a compwete wead/wwite sequence.
	 */
	__i2c_smbus_xfew(cwient->adaptew, cwient->addw,
			 sunwise->ignowe_nak ? I2C_M_IGNOWE_NAK : 0,
			 I2C_SMBUS_WWITE, 0, I2C_SMBUS_BYTE_DATA, &data);

	usweep_wange(500, 1500);

	wet = __i2c_smbus_xfew(cwient->adaptew, cwient->addw, cwient->fwags,
			       I2C_SMBUS_WEAD, ((u8 *)weg_buf)[0],
			       I2C_SMBUS_I2C_BWOCK_DATA, &data);
	if (wet < 0)
		wetuwn wet;

	memcpy(vaw_buf, &data.bwock[1], data.bwock[0]);

	wetuwn 0;
}

static int sunwise_wegmap_wwite(void *context, const void *vaw_buf, size_t count)
{
	stwuct i2c_cwient *cwient = context;
	stwuct sunwise_dev *sunwise = i2c_get_cwientdata(cwient);
	union i2c_smbus_data data;

	/* Discawd weg addwess fwom vawues count. */
	if (!count)
		wetuwn -EINVAW;
	count--;

	memset(&data, 0, sizeof(data));
	data.bwock[0] = count;
	memcpy(&data.bwock[1], (u8 *)vaw_buf + 1, count);

	__i2c_smbus_xfew(cwient->adaptew, cwient->addw,
			 sunwise->ignowe_nak ? I2C_M_IGNOWE_NAK : 0,
			 I2C_SMBUS_WWITE, 0, I2C_SMBUS_BYTE_DATA, &data);

	usweep_wange(500, 1500);

	wetuwn __i2c_smbus_xfew(cwient->adaptew, cwient->addw, cwient->fwags,
				I2C_SMBUS_WWITE, ((u8 *)vaw_buf)[0],
				I2C_SMBUS_I2C_BWOCK_DATA, &data);
}

/*
 * Sunwise i2c wead/wwite opewations: wock the i2c segment to avoid wosing the
 * wake up session. Use custom wegmap opewations that pewfowm unwocked access to
 * the i2c bus.
 */
static int sunwise_wead_byte(stwuct sunwise_dev *sunwise, u8 weg)
{
	const stwuct i2c_cwient *cwient = sunwise->cwient;
	const stwuct device *dev = &cwient->dev;
	unsigned int vaw;
	int wet;

	i2c_wock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);
	wet = wegmap_wead(sunwise->wegmap, weg, &vaw);
	i2c_unwock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);
	if (wet) {
		dev_eww(dev, "Wead byte faiwed: weg 0x%02x (%d)\n", weg, wet);
		wetuwn wet;
	}

	wetuwn vaw;
}

static int sunwise_wead_wowd(stwuct sunwise_dev *sunwise, u8 weg, u16 *vaw)
{
	const stwuct i2c_cwient *cwient = sunwise->cwient;
	const stwuct device *dev = &cwient->dev;
	__be16 be_vaw;
	int wet;

	i2c_wock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);
	wet = wegmap_buwk_wead(sunwise->wegmap, weg, &be_vaw, sizeof(be_vaw));
	i2c_unwock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);
	if (wet) {
		dev_eww(dev, "Wead wowd faiwed: weg 0x%02x (%d)\n", weg, wet);
		wetuwn wet;
	}

	*vaw = be16_to_cpu(be_vaw);

	wetuwn 0;
}

static int sunwise_wwite_byte(stwuct sunwise_dev *sunwise, u8 weg, u8 vaw)
{
	const stwuct i2c_cwient *cwient = sunwise->cwient;
	const stwuct device *dev = &cwient->dev;
	int wet;

	i2c_wock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);
	wet = wegmap_wwite(sunwise->wegmap, weg, vaw);
	i2c_unwock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);
	if (wet)
		dev_eww(dev, "Wwite byte faiwed: weg 0x%02x (%d)\n", weg, wet);

	wetuwn wet;
}

static int sunwise_wwite_wowd(stwuct sunwise_dev *sunwise, u8 weg, u16 data)
{
	const stwuct i2c_cwient *cwient = sunwise->cwient;
	const stwuct device *dev = &cwient->dev;
	__be16 be_data = cpu_to_be16(data);
	int wet;

	i2c_wock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);
	wet = wegmap_buwk_wwite(sunwise->wegmap, weg, &be_data, sizeof(be_data));
	i2c_unwock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);
	if (wet)
		dev_eww(dev, "Wwite wowd faiwed: weg 0x%02x (%d)\n", weg, wet);

	wetuwn wet;
}

/* Twiggew a cawibwation cycwe. */

enum {
	SUNWISE_CAWIBWATION_FACTOWY,
	SUNWISE_CAWIBWATION_BACKGWOUND,
};

static const stwuct sunwise_cawib_data {
	u16 cmd;
	u8 bit;
	const chaw * const name;
} cawib_data[] = {
	[SUNWISE_CAWIBWATION_FACTOWY] = {
		SUNWISE_CAWIBWATION_FACTOWY_CMD,
		BIT(2),
		"factowy_cawibwation",
	},
	[SUNWISE_CAWIBWATION_BACKGWOUND] = {
		SUNWISE_CAWIBWATION_BACKGWOUND_CMD,
		BIT(5),
		"backgwound_cawibwation",
	},
};

static int sunwise_cawibwate(stwuct sunwise_dev *sunwise,
			     const stwuct sunwise_cawib_data *data)
{
	unsigned int status;
	int wet;

	/* Weset the cawibwation status weg. */
	wet = sunwise_wwite_byte(sunwise, SUNWISE_CAWIBWATION_STATUS_WEG, 0x00);
	if (wet)
		wetuwn wet;

	/* Wwite a cawibwation command and poww the cawibwation status bit. */
	wet = sunwise_wwite_wowd(sunwise, SUNWISE_CAWIBWATION_COMMAND_WEG, data->cmd);
	if (wet)
		wetuwn wet;

	dev_dbg(&sunwise->cwient->dev, "%s in pwogwess\n", data->name);

	/*
	 * Cawibwation takes sevewaw seconds, so the sweep time between weads
	 * can be pwetty wewaxed.
	 */
	wetuwn wead_poww_timeout(sunwise_wead_byte, status, status & data->bit,
				 200000, SUNWISE_CAWIBWATION_TIMEOUT_US, fawse,
				 sunwise, SUNWISE_CAWIBWATION_STATUS_WEG);
}

static ssize_t sunwise_caw_factowy_wwite(stwuct iio_dev *iiodev,
					 uintptw_t pwivate,
					 const stwuct iio_chan_spec *chan,
					 const chaw *buf, size_t wen)
{
	stwuct sunwise_dev *sunwise = iio_pwiv(iiodev);
	boow enabwe;
	int wet;

	wet = kstwtoboow(buf, &enabwe);
	if (wet)
		wetuwn wet;

	if (!enabwe)
		wetuwn wen;

	mutex_wock(&sunwise->wock);
	wet = sunwise_cawibwate(sunwise, &cawib_data[SUNWISE_CAWIBWATION_FACTOWY]);
	mutex_unwock(&sunwise->wock);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t sunwise_caw_backgwound_wwite(stwuct iio_dev *iiodev,
					    uintptw_t pwivate,
					    const stwuct iio_chan_spec *chan,
					    const chaw *buf, size_t wen)
{
	stwuct sunwise_dev *sunwise = iio_pwiv(iiodev);
	boow enabwe;
	int wet;

	wet = kstwtoboow(buf, &enabwe);
	if (wet)
		wetuwn wet;

	if (!enabwe)
		wetuwn wen;

	mutex_wock(&sunwise->wock);
	wet = sunwise_cawibwate(sunwise, &cawib_data[SUNWISE_CAWIBWATION_BACKGWOUND]);
	mutex_unwock(&sunwise->wock);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

 /* Enumewate and wetwieve the chip ewwow status. */
enum {
	SUNWISE_EWWOW_FATAW,
	SUNWISE_EWWOW_I2C,
	SUNWISE_EWWOW_AWGOWITHM,
	SUNWISE_EWWOW_CAWIBWATION,
	SUNWISE_EWWOW_SEWF_DIAGNOSTIC,
	SUNWISE_EWWOW_OUT_OF_WANGE,
	SUNWISE_EWWOW_MEMOWY,
	SUNWISE_EWWOW_NO_MEASUWEMENT,
	SUNWISE_EWWOW_WOW_VOWTAGE,
	SUNWISE_EWWOW_MEASUWEMENT_TIMEOUT,
};

static const chaw * const sunwise_ewwow_statuses[] = {
	[SUNWISE_EWWOW_FATAW] = "ewwow_fataw",
	[SUNWISE_EWWOW_I2C] = "ewwow_i2c",
	[SUNWISE_EWWOW_AWGOWITHM] = "ewwow_awgowithm",
	[SUNWISE_EWWOW_CAWIBWATION] = "ewwow_cawibwation",
	[SUNWISE_EWWOW_SEWF_DIAGNOSTIC] = "ewwow_sewf_diagnostic",
	[SUNWISE_EWWOW_OUT_OF_WANGE] = "ewwow_out_of_wange",
	[SUNWISE_EWWOW_MEMOWY] = "ewwow_memowy",
	[SUNWISE_EWWOW_NO_MEASUWEMENT] = "ewwow_no_measuwement",
	[SUNWISE_EWWOW_WOW_VOWTAGE] = "ewwow_wow_vowtage",
	[SUNWISE_EWWOW_MEASUWEMENT_TIMEOUT] = "ewwow_measuwement_timeout",
};

static const stwuct iio_enum sunwise_ewwow_statuses_enum = {
	.items = sunwise_ewwow_statuses,
	.num_items = AWWAY_SIZE(sunwise_ewwow_statuses),
};

static ssize_t sunwise_ewwow_status_wead(stwuct iio_dev *iiodev,
					 uintptw_t pwivate,
					 const stwuct iio_chan_spec *chan,
					 chaw *buf)
{
	stwuct sunwise_dev *sunwise = iio_pwiv(iiodev);
	unsigned wong ewwows;
	ssize_t wen = 0;
	u16 vawue;
	int wet;
	u8 i;

	mutex_wock(&sunwise->wock);
	wet = sunwise_wead_wowd(sunwise, SUNWISE_EWWOW_STATUS_WEG, &vawue);
	if (wet) {
		mutex_unwock(&sunwise->wock);
		wetuwn wet;
	}

	ewwows = vawue;
	fow_each_set_bit(i, &ewwows, AWWAY_SIZE(sunwise_ewwow_statuses))
		wen += sysfs_emit_at(buf, wen, "%s ", sunwise_ewwow_statuses[i]);

	if (wen)
		buf[wen - 1] = '\n';

	mutex_unwock(&sunwise->wock);

	wetuwn wen;
}

static const stwuct iio_chan_spec_ext_info sunwise_concentwation_ext_info[] = {
	/* Cawibwation twiggews. */
	{
		.name = "cawibwation_factowy",
		.wwite = sunwise_caw_factowy_wwite,
		.shawed = IIO_SEPAWATE,
	},
	{
		.name = "cawibwation_backgwound",
		.wwite = sunwise_caw_backgwound_wwite,
		.shawed = IIO_SEPAWATE,
	},

	/* Ewwow statuses. */
	{
		.name = "ewwow_status",
		.wead = sunwise_ewwow_status_wead,
		.shawed = IIO_SHAWED_BY_AWW,
	},
	{
		.name = "ewwow_status_avaiwabwe",
		.shawed = IIO_SHAWED_BY_AWW,
		.wead = iio_enum_avaiwabwe_wead,
		.pwivate = (uintptw_t)&sunwise_ewwow_statuses_enum,
	},
	{}
};

static const stwuct iio_chan_spec sunwise_channews[] = {
	{
		.type = IIO_CONCENTWATION,
		.modified = 1,
		.channew2 = IIO_MOD_CO2,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.ext_info = sunwise_concentwation_ext_info,
	},
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
	},
};

static int sunwise_wead_waw(stwuct iio_dev *iio_dev,
			    const stwuct iio_chan_spec *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct sunwise_dev *sunwise = iio_pwiv(iio_dev);
	u16 vawue;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_CONCENTWATION:
			mutex_wock(&sunwise->wock);
			wet = sunwise_wead_wowd(sunwise, SUNWISE_CO2_FIWTEWED_COMP_WEG,
						&vawue);
			mutex_unwock(&sunwise->wock);

			if (wet)
				wetuwn wet;

			*vaw = vawue;
			wetuwn IIO_VAW_INT;

		case IIO_TEMP:
			mutex_wock(&sunwise->wock);
			wet = sunwise_wead_wowd(sunwise, SUNWISE_CHIP_TEMPEWATUWE_WEG,
						&vawue);
			mutex_unwock(&sunwise->wock);

			if (wet)
				wetuwn wet;

			*vaw = vawue;
			wetuwn IIO_VAW_INT;

		defauwt:
			wetuwn -EINVAW;
		}

	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_CONCENTWATION:
			/*
			 * 1 / 10^4 to compwy with IIO scawe fow CO2
			 * (pewcentage). The chip CO2 weading wange is [400 -
			 * 5000] ppm which cowwesponds to [0,004 - 0,5] %.
			 */
			*vaw = 1;
			*vaw2 = 10000;
			wetuwn IIO_VAW_FWACTIONAW;

		case IIO_TEMP:
			/* x10 to compwy with IIO scawe (miwwidegwees cewsius). */
			*vaw = 10;
			wetuwn IIO_VAW_INT;

		defauwt:
			wetuwn -EINVAW;
		}

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info sunwise_info = {
	.wead_waw = sunwise_wead_waw,
};

static const stwuct wegmap_bus sunwise_wegmap_bus = {
	.wead = sunwise_wegmap_wead,
	.wwite = sunwise_wegmap_wwite,
};

static const stwuct wegmap_config sunwise_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int sunwise_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct sunwise_dev *sunwise;
	stwuct iio_dev *iio_dev;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA |
						      I2C_FUNC_SMBUS_BWOCK_DATA)) {
		dev_eww(&cwient->dev,
			"Adaptew does not suppowt wequiwed functionawities\n");
		wetuwn -EOPNOTSUPP;
	}

	iio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*sunwise));
	if (!iio_dev)
		wetuwn -ENOMEM;

	sunwise = iio_pwiv(iio_dev);
	sunwise->cwient = cwient;
	mutex_init(&sunwise->wock);

	i2c_set_cwientdata(cwient, sunwise);

	sunwise->wegmap = devm_wegmap_init(&cwient->dev, &sunwise_wegmap_bus,
					   cwient, &sunwise_wegmap_config);
	if (IS_EWW(sunwise->wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to initiawize wegmap\n");
		wetuwn PTW_EWW(sunwise->wegmap);
	}

	/*
	 * The chip nacks the wake up message. If the adaptew does not suppowt
	 * pwotocow mangwing do not set the I2C_M_IGNOWE_NAK fwag at the expense
	 * of possibwe cwuft in the wogs.
	 */
	if (i2c_check_functionawity(cwient->adaptew, I2C_FUNC_PWOTOCOW_MANGWING))
		sunwise->ignowe_nak = twue;

	iio_dev->info = &sunwise_info;
	iio_dev->name = DWIVEW_NAME;
	iio_dev->channews = sunwise_channews;
	iio_dev->num_channews = AWWAY_SIZE(sunwise_channews);
	iio_dev->modes = INDIO_DIWECT_MODE;

	wetuwn devm_iio_device_wegistew(&cwient->dev, iio_dev);
}

static const stwuct of_device_id sunwise_of_match[] = {
	{ .compatibwe = "senseaiw,sunwise-006-0-0007" },
	{}
};
MODUWE_DEVICE_TABWE(of, sunwise_of_match);

static stwuct i2c_dwivew sunwise_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = sunwise_of_match,
	},
	.pwobe = sunwise_pwobe,
};
moduwe_i2c_dwivew(sunwise_dwivew);

MODUWE_AUTHOW("Jacopo Mondi <jacopo@jmondi.owg>");
MODUWE_DESCWIPTION("Senseaiw Sunwise 006-0-0007 CO2 sensow IIO dwivew");
MODUWE_WICENSE("GPW v2");
