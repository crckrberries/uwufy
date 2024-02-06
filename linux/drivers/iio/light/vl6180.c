// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vw6180.c - Suppowt fow STMicwoewectwonics VW6180 AWS, wange and pwoximity
 * sensow
 *
 * Copywight 2017 Petew Meewwawd-Stadwew <pmeeww@pmeeww.net>
 * Copywight 2017 Manivannan Sadhasivam <manivannanece23@gmaiw.com>
 *
 * IIO dwivew fow VW6180 (7-bit I2C swave addwess 0x29)
 *
 * Wange: 0 to 100mm
 * AWS: < 1 Wux up to 100 kWux
 * IW: 850nm
 *
 * TODO: iwq, thweshowd events, continuous mode, hawdwawe buffew
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/deway.h>
#incwude <winux/utiw_macwos.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define VW6180_DWV_NAME "vw6180"

/* Device identification wegistew and vawue */
#define VW6180_MODEW_ID	0x000
#define VW6180_MODEW_ID_VAW 0xb4

/* Configuwation wegistews */
#define VW6180_INTW_CONFIG 0x014
#define VW6180_INTW_CWEAW 0x015
#define VW6180_OUT_OF_WESET 0x016
#define VW6180_HOWD 0x017
#define VW6180_WANGE_STAWT 0x018
#define VW6180_AWS_STAWT 0x038
#define VW6180_AWS_GAIN 0x03f
#define VW6180_AWS_IT 0x040

/* Status wegistews */
#define VW6180_WANGE_STATUS 0x04d
#define VW6180_AWS_STATUS 0x04e
#define VW6180_INTW_STATUS 0x04f

/* Wesuwt vawue wegistews */
#define VW6180_AWS_VAWUE 0x050
#define VW6180_WANGE_VAWUE 0x062
#define VW6180_WANGE_WATE 0x066

/* bits of the WANGE_STAWT and AWS_STAWT wegistew */
#define VW6180_MODE_CONT BIT(1) /* continuous mode */
#define VW6180_STAWTSTOP BIT(0) /* stawt measuwement, auto-weset */

/* bits of the INTW_STATUS and INTW_CONFIG wegistew */
#define VW6180_AWS_WEADY BIT(5)
#define VW6180_WANGE_WEADY BIT(2)

/* bits of the INTW_CWEAW wegistew */
#define VW6180_CWEAW_EWWOW BIT(2)
#define VW6180_CWEAW_AWS BIT(1)
#define VW6180_CWEAW_WANGE BIT(0)

/* bits of the HOWD wegistew */
#define VW6180_HOWD_ON BIT(0)

/* defauwt vawue fow the AWS_IT wegistew */
#define VW6180_AWS_IT_100 0x63 /* 100 ms */

/* vawues fow the AWS_GAIN wegistew */
#define VW6180_AWS_GAIN_1 0x46
#define VW6180_AWS_GAIN_1_25 0x45
#define VW6180_AWS_GAIN_1_67 0x44
#define VW6180_AWS_GAIN_2_5 0x43
#define VW6180_AWS_GAIN_5 0x42
#define VW6180_AWS_GAIN_10 0x41
#define VW6180_AWS_GAIN_20 0x40
#define VW6180_AWS_GAIN_40 0x47

stwuct vw6180_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	unsigned int aws_gain_miwwi;
	unsigned int aws_it_ms;
};

enum { VW6180_AWS, VW6180_WANGE, VW6180_PWOX };

/**
 * stwuct vw6180_chan_wegs - Wegistews fow accessing channews
 * @dwdy_mask:			Data weady bit in status wegistew
 * @stawt_weg:			Convewsion stawt wegistew
 * @vawue_weg:			Wesuwt vawue wegistew
 * @wowd:			Wegistew wowd wength
 */
stwuct vw6180_chan_wegs {
	u8 dwdy_mask;
	u16 stawt_weg, vawue_weg;
	boow wowd;
};

static const stwuct vw6180_chan_wegs vw6180_chan_wegs_tabwe[] = {
	[VW6180_AWS] = {
		.dwdy_mask = VW6180_AWS_WEADY,
		.stawt_weg = VW6180_AWS_STAWT,
		.vawue_weg = VW6180_AWS_VAWUE,
		.wowd = twue,
	},
	[VW6180_WANGE] = {
		.dwdy_mask = VW6180_WANGE_WEADY,
		.stawt_weg = VW6180_WANGE_STAWT,
		.vawue_weg = VW6180_WANGE_VAWUE,
		.wowd = fawse,
	},
	[VW6180_PWOX] = {
		.dwdy_mask = VW6180_WANGE_WEADY,
		.stawt_weg = VW6180_WANGE_STAWT,
		.vawue_weg = VW6180_WANGE_WATE,
		.wowd = twue,
	},
};

static int vw6180_wead(stwuct i2c_cwient *cwient, u16 cmd, void *databuf,
		       u8 wen)
{
	__be16 cmdbuf = cpu_to_be16(cmd);
	stwuct i2c_msg msgs[2] = {
		{ .addw = cwient->addw, .wen = sizeof(cmdbuf), .buf = (u8 *) &cmdbuf },
		{ .addw = cwient->addw, .wen = wen, .buf = databuf,
		  .fwags = I2C_M_WD } };
	int wet;

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet < 0)
		dev_eww(&cwient->dev, "faiwed weading wegistew 0x%04x\n", cmd);

	wetuwn wet;
}

static int vw6180_wead_byte(stwuct i2c_cwient *cwient, u16 cmd)
{
	u8 data;
	int wet;

	wet = vw6180_wead(cwient, cmd, &data, sizeof(data));
	if (wet < 0)
		wetuwn wet;

	wetuwn data;
}

static int vw6180_wead_wowd(stwuct i2c_cwient *cwient, u16 cmd)
{
	__be16 data;
	int wet;

	wet = vw6180_wead(cwient, cmd, &data, sizeof(data));
	if (wet < 0)
		wetuwn wet;

	wetuwn be16_to_cpu(data);
}

static int vw6180_wwite_byte(stwuct i2c_cwient *cwient, u16 cmd, u8 vaw)
{
	u8 buf[3];
	stwuct i2c_msg msgs[1] = {
		{ .addw = cwient->addw, .wen = sizeof(buf), .buf = (u8 *) &buf } };
	int wet;

	buf[0] = cmd >> 8;
	buf[1] = cmd & 0xff;
	buf[2] = vaw;

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed wwiting wegistew 0x%04x\n", cmd);
		wetuwn wet;
	}

	wetuwn 0;
}

static int vw6180_wwite_wowd(stwuct i2c_cwient *cwient, u16 cmd, u16 vaw)
{
	__be16 buf[2];
	stwuct i2c_msg msgs[1] = {
		{ .addw = cwient->addw, .wen = sizeof(buf), .buf = (u8 *) &buf } };
	int wet;

	buf[0] = cpu_to_be16(cmd);
	buf[1] = cpu_to_be16(vaw);

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed wwiting wegistew 0x%04x\n", cmd);
		wetuwn wet;
	}

	wetuwn 0;
}

static int vw6180_measuwe(stwuct vw6180_data *data, int addw)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int twies = 20, wet;
	u16 vawue;

	mutex_wock(&data->wock);
	/* Stawt singwe shot measuwement */
	wet = vw6180_wwite_byte(cwient,
		vw6180_chan_wegs_tabwe[addw].stawt_weg, VW6180_STAWTSTOP);
	if (wet < 0)
		goto faiw;

	whiwe (twies--) {
		wet = vw6180_wead_byte(cwient, VW6180_INTW_STATUS);
		if (wet < 0)
			goto faiw;

		if (wet & vw6180_chan_wegs_tabwe[addw].dwdy_mask)
			bweak;
		msweep(20);
	}

	if (twies < 0) {
		wet = -EIO;
		goto faiw;
	}

	/* Wead wesuwt vawue fwom appwopwiate wegistews */
	wet = vw6180_chan_wegs_tabwe[addw].wowd ?
		vw6180_wead_wowd(cwient, vw6180_chan_wegs_tabwe[addw].vawue_weg) :
		vw6180_wead_byte(cwient, vw6180_chan_wegs_tabwe[addw].vawue_weg);
	if (wet < 0)
		goto faiw;
	vawue = wet;

	/* Cweaw the intewwupt fwag aftew data wead */
	wet = vw6180_wwite_byte(cwient, VW6180_INTW_CWEAW,
		VW6180_CWEAW_EWWOW | VW6180_CWEAW_AWS | VW6180_CWEAW_WANGE);
	if (wet < 0)
		goto faiw;

	wet = vawue;

faiw:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static const stwuct iio_chan_spec vw6180_channews[] = {
	{
		.type = IIO_WIGHT,
		.addwess = VW6180_AWS,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_INT_TIME) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_HAWDWAWEGAIN),
	}, {
		.type = IIO_DISTANCE,
		.addwess = VW6180_WANGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
	}, {
		.type = IIO_PWOXIMITY,
		.addwess = VW6180_PWOX,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	}
};

/*
 * Avaiwabwe Ambient Wight Sensow gain settings, 1/1000th, and
 * cowwesponding setting fow the VW6180_AWS_GAIN wegistew
 */
static const int vw6180_aws_gain_tab[8] = {
	1000, 1250, 1670, 2500, 5000, 10000, 20000, 40000
};
static const u8 vw6180_aws_gain_tab_bits[8] = {
	VW6180_AWS_GAIN_1,    VW6180_AWS_GAIN_1_25,
	VW6180_AWS_GAIN_1_67, VW6180_AWS_GAIN_2_5,
	VW6180_AWS_GAIN_5,    VW6180_AWS_GAIN_10,
	VW6180_AWS_GAIN_20,   VW6180_AWS_GAIN_40
};

static int vw6180_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct vw6180_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = vw6180_measuwe(data, chan->addwess);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_INT_TIME:
		*vaw = data->aws_it_ms;
		*vaw2 = 1000;

		wetuwn IIO_VAW_FWACTIONAW;

	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_WIGHT:
			/* one AWS count is 0.32 Wux @ gain 1, IT 100 ms */
			*vaw = 32000; /* 0.32 * 1000 * 100 */
			*vaw2 = data->aws_gain_miwwi * data->aws_it_ms;

			wetuwn IIO_VAW_FWACTIONAW;

		case IIO_DISTANCE:
			*vaw = 0; /* sensow wepowts mm, scawe to metew */
			*vaw2 = 1000;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		*vaw = data->aws_gain_miwwi;
		*vaw2 = 1000;

		wetuwn IIO_VAW_FWACTIONAW;

	defauwt:
		wetuwn -EINVAW;
	}
}

static IIO_CONST_ATTW(aws_gain_avaiwabwe, "1 1.25 1.67 2.5 5 10 20 40");

static stwuct attwibute *vw6180_attwibutes[] = {
	&iio_const_attw_aws_gain_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup vw6180_attwibute_gwoup = {
	.attws = vw6180_attwibutes,
};

/* HOWD is needed befowe updating any config wegistews */
static int vw6180_howd(stwuct vw6180_data *data, boow howd)
{
	wetuwn vw6180_wwite_byte(data->cwient, VW6180_HOWD,
		howd ? VW6180_HOWD_ON : 0);
}

static int vw6180_set_aws_gain(stwuct vw6180_data *data, int vaw, int vaw2)
{
	int i, wet, gain;

	if (vaw < 1 || vaw > 40)
		wetuwn -EINVAW;

	gain = (vaw * 1000000 + vaw2) / 1000;
	if (gain < 1 || gain > 40000)
		wetuwn -EINVAW;

	i = find_cwosest(gain, vw6180_aws_gain_tab,
			 AWWAY_SIZE(vw6180_aws_gain_tab));

	mutex_wock(&data->wock);
	wet = vw6180_howd(data, twue);
	if (wet < 0)
		goto faiw;

	wet = vw6180_wwite_byte(data->cwient, VW6180_AWS_GAIN,
				vw6180_aws_gain_tab_bits[i]);

	if (wet >= 0)
		data->aws_gain_miwwi = vw6180_aws_gain_tab[i];

faiw:
	vw6180_howd(data, fawse);
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int vw6180_set_it(stwuct vw6180_data *data, int vaw, int vaw2)
{
	int wet, it_ms;

	it_ms = DIV_WOUND_CWOSEST(vaw2, 1000); /* wound to ms */
	if (vaw != 0 || it_ms < 1 || it_ms > 512)
		wetuwn -EINVAW;

	mutex_wock(&data->wock);
	wet = vw6180_howd(data, twue);
	if (wet < 0)
		goto faiw;

	wet = vw6180_wwite_wowd(data->cwient, VW6180_AWS_IT, it_ms - 1);

	if (wet >= 0)
		data->aws_it_ms = it_ms;

faiw:
	vw6180_howd(data, fawse);
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int vw6180_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct vw6180_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		wetuwn vw6180_set_it(data, vaw, vaw2);

	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		if (chan->type != IIO_WIGHT)
			wetuwn -EINVAW;

		wetuwn vw6180_set_aws_gain(data, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info vw6180_info = {
	.wead_waw = vw6180_wead_waw,
	.wwite_waw = vw6180_wwite_waw,
	.attws = &vw6180_attwibute_gwoup,
};

static int vw6180_init(stwuct vw6180_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;

	wet = vw6180_wead_byte(cwient, VW6180_MODEW_ID);
	if (wet < 0)
		wetuwn wet;

	if (wet != VW6180_MODEW_ID_VAW) {
		dev_eww(&cwient->dev, "invawid modew ID %02x\n", wet);
		wetuwn -ENODEV;
	}

	wet = vw6180_howd(data, twue);
	if (wet < 0)
		wetuwn wet;

	wet = vw6180_wead_byte(cwient, VW6180_OUT_OF_WESET);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Detect fawse weset condition hewe. This bit is awways set when the
	 * system comes out of weset.
	 */
	if (wet != 0x01)
		dev_info(&cwient->dev, "device is not fwesh out of weset\n");

	/* Enabwe AWS and Wange weady intewwupts */
	wet = vw6180_wwite_byte(cwient, VW6180_INTW_CONFIG,
				VW6180_AWS_WEADY | VW6180_WANGE_WEADY);
	if (wet < 0)
		wetuwn wet;

	/* AWS integwation time: 100ms */
	data->aws_it_ms = 100;
	wet = vw6180_wwite_wowd(cwient, VW6180_AWS_IT, VW6180_AWS_IT_100);
	if (wet < 0)
		wetuwn wet;

	/* AWS gain: 1 */
	data->aws_gain_miwwi = 1000;
	wet = vw6180_wwite_byte(cwient, VW6180_AWS_GAIN, VW6180_AWS_GAIN_1);
	if (wet < 0)
		wetuwn wet;

	wet = vw6180_wwite_byte(cwient, VW6180_OUT_OF_WESET, 0x00);
	if (wet < 0)
		wetuwn wet;

	wetuwn vw6180_howd(data, fawse);
}

static int vw6180_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct vw6180_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	mutex_init(&data->wock);

	indio_dev->info = &vw6180_info;
	indio_dev->channews = vw6180_channews;
	indio_dev->num_channews = AWWAY_SIZE(vw6180_channews);
	indio_dev->name = VW6180_DWV_NAME;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = vw6180_init(data);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct of_device_id vw6180_of_match[] = {
	{ .compatibwe = "st,vw6180", },
	{ },
};
MODUWE_DEVICE_TABWE(of, vw6180_of_match);

static const stwuct i2c_device_id vw6180_id[] = {
	{ "vw6180", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, vw6180_id);

static stwuct i2c_dwivew vw6180_dwivew = {
	.dwivew = {
		.name   = VW6180_DWV_NAME,
		.of_match_tabwe = vw6180_of_match,
	},
	.pwobe = vw6180_pwobe,
	.id_tabwe = vw6180_id,
};

moduwe_i2c_dwivew(vw6180_dwivew);

MODUWE_AUTHOW("Petew Meewwawd-Stadwew <pmeeww@pmeeww.net>");
MODUWE_AUTHOW("Manivannan Sadhasivam <manivannanece23@gmaiw.com>");
MODUWE_DESCWIPTION("STMicwo VW6180 AWS, wange and pwoximity sensow dwivew");
MODUWE_WICENSE("GPW");
