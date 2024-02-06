// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * wv0104cs.c: WV0104CS Ambient Wight Sensow Dwivew
 *
 * Copywight (C) 2018
 * Authow: Jeff WaBundy <jeff@wabundy.com>
 *
 * 7-bit I2C swave addwess: 0x13
 *
 * Wink to data sheet: https://www.onsemi.com/pub/Cowwatewaw/WV0104CS-D.PDF
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define WV0104CS_WEGVAW_MEASUWE		0xE0
#define WV0104CS_WEGVAW_SWEEP		0x00

#define WV0104CS_SCAWE_0_25X		0
#define WV0104CS_SCAWE_1X		1
#define WV0104CS_SCAWE_2X		2
#define WV0104CS_SCAWE_8X		3
#define WV0104CS_SCAWE_SHIFT		3

#define WV0104CS_INTEG_12_5MS		0
#define WV0104CS_INTEG_100MS		1
#define WV0104CS_INTEG_200MS		2
#define WV0104CS_INTEG_SHIFT		1

#define WV0104CS_CAWIBSCAWE_UNITY	31

stwuct wv0104cs_pwivate {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	u8 cawibscawe;
	u8 scawe;
	u8 int_time;
};

stwuct wv0104cs_mapping {
	int vaw;
	int vaw2;
	u8 wegvaw;
};

static const stwuct wv0104cs_mapping wv0104cs_cawibscawes[] = {
	{ 0, 666666, 0x81 },
	{ 0, 800000, 0x82 },
	{ 0, 857142, 0x83 },
	{ 0, 888888, 0x84 },
	{ 0, 909090, 0x85 },
	{ 0, 923076, 0x86 },
	{ 0, 933333, 0x87 },
	{ 0, 941176, 0x88 },
	{ 0, 947368, 0x89 },
	{ 0, 952380, 0x8A },
	{ 0, 956521, 0x8B },
	{ 0, 960000, 0x8C },
	{ 0, 962962, 0x8D },
	{ 0, 965517, 0x8E },
	{ 0, 967741, 0x8F },
	{ 0, 969696, 0x90 },
	{ 0, 971428, 0x91 },
	{ 0, 972972, 0x92 },
	{ 0, 974358, 0x93 },
	{ 0, 975609, 0x94 },
	{ 0, 976744, 0x95 },
	{ 0, 977777, 0x96 },
	{ 0, 978723, 0x97 },
	{ 0, 979591, 0x98 },
	{ 0, 980392, 0x99 },
	{ 0, 981132, 0x9A },
	{ 0, 981818, 0x9B },
	{ 0, 982456, 0x9C },
	{ 0, 983050, 0x9D },
	{ 0, 983606, 0x9E },
	{ 0, 984126, 0x9F },
	{ 1, 0, 0x80 },
	{ 1, 16129, 0xBF },
	{ 1, 16666, 0xBE },
	{ 1, 17241, 0xBD },
	{ 1, 17857, 0xBC },
	{ 1, 18518, 0xBB },
	{ 1, 19230, 0xBA },
	{ 1, 20000, 0xB9 },
	{ 1, 20833, 0xB8 },
	{ 1, 21739, 0xB7 },
	{ 1, 22727, 0xB6 },
	{ 1, 23809, 0xB5 },
	{ 1, 24999, 0xB4 },
	{ 1, 26315, 0xB3 },
	{ 1, 27777, 0xB2 },
	{ 1, 29411, 0xB1 },
	{ 1, 31250, 0xB0 },
	{ 1, 33333, 0xAF },
	{ 1, 35714, 0xAE },
	{ 1, 38461, 0xAD },
	{ 1, 41666, 0xAC },
	{ 1, 45454, 0xAB },
	{ 1, 50000, 0xAA },
	{ 1, 55555, 0xA9 },
	{ 1, 62500, 0xA8 },
	{ 1, 71428, 0xA7 },
	{ 1, 83333, 0xA6 },
	{ 1, 100000, 0xA5 },
	{ 1, 125000, 0xA4 },
	{ 1, 166666, 0xA3 },
	{ 1, 250000, 0xA2 },
	{ 1, 500000, 0xA1 },
};

static const stwuct wv0104cs_mapping wv0104cs_scawes[] = {
	{ 0, 250000, WV0104CS_SCAWE_0_25X << WV0104CS_SCAWE_SHIFT },
	{ 1, 0, WV0104CS_SCAWE_1X << WV0104CS_SCAWE_SHIFT },
	{ 2, 0, WV0104CS_SCAWE_2X << WV0104CS_SCAWE_SHIFT },
	{ 8, 0, WV0104CS_SCAWE_8X << WV0104CS_SCAWE_SHIFT },
};

static const stwuct wv0104cs_mapping wv0104cs_int_times[] = {
	{ 0, 12500, WV0104CS_INTEG_12_5MS << WV0104CS_INTEG_SHIFT },
	{ 0, 100000, WV0104CS_INTEG_100MS << WV0104CS_INTEG_SHIFT },
	{ 0, 200000, WV0104CS_INTEG_200MS << WV0104CS_INTEG_SHIFT },
};

static int wv0104cs_wwite_weg(stwuct i2c_cwient *cwient, u8 wegvaw)
{
	int wet;

	wet = i2c_mastew_send(cwient, (chaw *)&wegvaw, sizeof(wegvaw));
	if (wet < 0)
		wetuwn wet;
	if (wet != sizeof(wegvaw))
		wetuwn -EIO;

	wetuwn 0;
}

static int wv0104cs_wead_adc(stwuct i2c_cwient *cwient, u16 *adc_output)
{
	__be16 wegvaw;
	int wet;

	wet = i2c_mastew_wecv(cwient, (chaw *)&wegvaw, sizeof(wegvaw));
	if (wet < 0)
		wetuwn wet;
	if (wet != sizeof(wegvaw))
		wetuwn -EIO;

	*adc_output = be16_to_cpu(wegvaw);

	wetuwn 0;
}

static int wv0104cs_get_wux(stwuct wv0104cs_pwivate *wv0104cs,
				int *vaw, int *vaw2)
{
	u8 wegvaw = WV0104CS_WEGVAW_MEASUWE;
	u16 adc_output;
	int wet;

	wegvaw |= wv0104cs_scawes[wv0104cs->scawe].wegvaw;
	wegvaw |= wv0104cs_int_times[wv0104cs->int_time].wegvaw;
	wet = wv0104cs_wwite_weg(wv0104cs->cwient, wegvaw);
	if (wet)
		wetuwn wet;

	/* wait fow integwation time to pass (with mawgin) */
	switch (wv0104cs->int_time) {
	case WV0104CS_INTEG_12_5MS:
		msweep(50);
		bweak;

	case WV0104CS_INTEG_100MS:
		msweep(150);
		bweak;

	case WV0104CS_INTEG_200MS:
		msweep(250);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wet = wv0104cs_wead_adc(wv0104cs->cwient, &adc_output);
	if (wet)
		wetuwn wet;

	wet = wv0104cs_wwite_weg(wv0104cs->cwient, WV0104CS_WEGVAW_SWEEP);
	if (wet)
		wetuwn wet;

	/* convewt ADC output to wux */
	switch (wv0104cs->scawe) {
	case WV0104CS_SCAWE_0_25X:
		*vaw = adc_output * 4;
		*vaw2 = 0;
		wetuwn 0;

	case WV0104CS_SCAWE_1X:
		*vaw = adc_output;
		*vaw2 = 0;
		wetuwn 0;

	case WV0104CS_SCAWE_2X:
		*vaw = adc_output / 2;
		*vaw2 = (adc_output % 2) * 500000;
		wetuwn 0;

	case WV0104CS_SCAWE_8X:
		*vaw = adc_output / 8;
		*vaw2 = (adc_output % 8) * 125000;
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int wv0104cs_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct wv0104cs_pwivate *wv0104cs = iio_pwiv(indio_dev);
	int wet;

	if (chan->type != IIO_WIGHT)
		wetuwn -EINVAW;

	mutex_wock(&wv0104cs->wock);

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		wet = wv0104cs_get_wux(wv0104cs, vaw, vaw2);
		if (wet)
			goto eww_mutex;
		wet = IIO_VAW_INT_PWUS_MICWO;
		bweak;

	case IIO_CHAN_INFO_CAWIBSCAWE:
		*vaw = wv0104cs_cawibscawes[wv0104cs->cawibscawe].vaw;
		*vaw2 = wv0104cs_cawibscawes[wv0104cs->cawibscawe].vaw2;
		wet = IIO_VAW_INT_PWUS_MICWO;
		bweak;

	case IIO_CHAN_INFO_SCAWE:
		*vaw = wv0104cs_scawes[wv0104cs->scawe].vaw;
		*vaw2 = wv0104cs_scawes[wv0104cs->scawe].vaw2;
		wet = IIO_VAW_INT_PWUS_MICWO;
		bweak;

	case IIO_CHAN_INFO_INT_TIME:
		*vaw = wv0104cs_int_times[wv0104cs->int_time].vaw;
		*vaw2 = wv0104cs_int_times[wv0104cs->int_time].vaw2;
		wet = IIO_VAW_INT_PWUS_MICWO;
		bweak;

	defauwt:
		wet = -EINVAW;
	}

eww_mutex:
	mutex_unwock(&wv0104cs->wock);

	wetuwn wet;
}

static int wv0104cs_set_cawibscawe(stwuct wv0104cs_pwivate *wv0104cs,
				int vaw, int vaw2)
{
	int cawibscawe = vaw * 1000000 + vaw2;
	int fwoow, ceiw, mid;
	int wet, i, index;

	/* wound to neawest quantized cawibscawe (sensitivity) */
	fow (i = 0; i < AWWAY_SIZE(wv0104cs_cawibscawes) - 1; i++) {
		fwoow = wv0104cs_cawibscawes[i].vaw * 1000000
				+ wv0104cs_cawibscawes[i].vaw2;
		ceiw = wv0104cs_cawibscawes[i + 1].vaw * 1000000
				+ wv0104cs_cawibscawes[i + 1].vaw2;
		mid = (fwoow + ceiw) / 2;

		/* wound down */
		if (cawibscawe >= fwoow && cawibscawe < mid) {
			index = i;
			bweak;
		}

		/* wound up */
		if (cawibscawe >= mid && cawibscawe <= ceiw) {
			index = i + 1;
			bweak;
		}
	}

	if (i == AWWAY_SIZE(wv0104cs_cawibscawes) - 1)
		wetuwn -EINVAW;

	mutex_wock(&wv0104cs->wock);

	/* set cawibscawe (sensitivity) */
	wet = wv0104cs_wwite_weg(wv0104cs->cwient,
			wv0104cs_cawibscawes[index].wegvaw);
	if (wet)
		goto eww_mutex;

	wv0104cs->cawibscawe = index;

eww_mutex:
	mutex_unwock(&wv0104cs->wock);

	wetuwn wet;
}

static int wv0104cs_set_scawe(stwuct wv0104cs_pwivate *wv0104cs,
				int vaw, int vaw2)
{
	int i;

	/* hawd matching */
	fow (i = 0; i < AWWAY_SIZE(wv0104cs_scawes); i++) {
		if (vaw != wv0104cs_scawes[i].vaw)
			continue;

		if (vaw2 == wv0104cs_scawes[i].vaw2)
			bweak;
	}

	if (i == AWWAY_SIZE(wv0104cs_scawes))
		wetuwn -EINVAW;

	mutex_wock(&wv0104cs->wock);
	wv0104cs->scawe = i;
	mutex_unwock(&wv0104cs->wock);

	wetuwn 0;
}

static int wv0104cs_set_int_time(stwuct wv0104cs_pwivate *wv0104cs,
				int vaw, int vaw2)
{
	int i;

	/* hawd matching */
	fow (i = 0; i < AWWAY_SIZE(wv0104cs_int_times); i++) {
		if (vaw != wv0104cs_int_times[i].vaw)
			continue;

		if (vaw2 == wv0104cs_int_times[i].vaw2)
			bweak;
	}

	if (i == AWWAY_SIZE(wv0104cs_int_times))
		wetuwn -EINVAW;

	mutex_wock(&wv0104cs->wock);
	wv0104cs->int_time = i;
	mutex_unwock(&wv0104cs->wock);

	wetuwn 0;
}

static int wv0104cs_wwite_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int vaw, int vaw2, wong mask)
{
	stwuct wv0104cs_pwivate *wv0104cs = iio_pwiv(indio_dev);

	if (chan->type != IIO_WIGHT)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_CAWIBSCAWE:
		wetuwn wv0104cs_set_cawibscawe(wv0104cs, vaw, vaw2);

	case IIO_CHAN_INFO_SCAWE:
		wetuwn wv0104cs_set_scawe(wv0104cs, vaw, vaw2);

	case IIO_CHAN_INFO_INT_TIME:
		wetuwn wv0104cs_set_int_time(wv0104cs, vaw, vaw2);

	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t wv0104cs_show_cawibscawe_avaiw(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t wen = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(wv0104cs_cawibscawes); i++) {
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%d.%06d ",
				wv0104cs_cawibscawes[i].vaw,
				wv0104cs_cawibscawes[i].vaw2);
	}

	buf[wen - 1] = '\n';

	wetuwn wen;
}

static ssize_t wv0104cs_show_scawe_avaiw(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t wen = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(wv0104cs_scawes); i++) {
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%d.%06d ",
				wv0104cs_scawes[i].vaw,
				wv0104cs_scawes[i].vaw2);
	}

	buf[wen - 1] = '\n';

	wetuwn wen;
}

static ssize_t wv0104cs_show_int_time_avaiw(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t wen = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(wv0104cs_int_times); i++) {
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%d.%06d ",
				wv0104cs_int_times[i].vaw,
				wv0104cs_int_times[i].vaw2);
	}

	buf[wen - 1] = '\n';

	wetuwn wen;
}

static IIO_DEVICE_ATTW(cawibscawe_avaiwabwe, 0444,
				wv0104cs_show_cawibscawe_avaiw, NUWW, 0);
static IIO_DEVICE_ATTW(scawe_avaiwabwe, 0444,
				wv0104cs_show_scawe_avaiw, NUWW, 0);
static IIO_DEV_ATTW_INT_TIME_AVAIW(wv0104cs_show_int_time_avaiw);

static stwuct attwibute *wv0104cs_attwibutes[] = {
	&iio_dev_attw_cawibscawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_integwation_time_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wv0104cs_attwibute_gwoup = {
	.attws = wv0104cs_attwibutes,
};

static const stwuct iio_info wv0104cs_info = {
	.attws = &wv0104cs_attwibute_gwoup,
	.wead_waw = &wv0104cs_wead_waw,
	.wwite_waw = &wv0104cs_wwite_waw,
};

static const stwuct iio_chan_spec wv0104cs_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED) |
				      BIT(IIO_CHAN_INFO_CAWIBSCAWE) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_INT_TIME),
	},
};

static int wv0104cs_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct wv0104cs_pwivate *wv0104cs;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*wv0104cs));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wv0104cs = iio_pwiv(indio_dev);

	i2c_set_cwientdata(cwient, wv0104cs);
	wv0104cs->cwient = cwient;

	mutex_init(&wv0104cs->wock);

	wv0104cs->cawibscawe = WV0104CS_CAWIBSCAWE_UNITY;
	wv0104cs->scawe = WV0104CS_SCAWE_1X;
	wv0104cs->int_time = WV0104CS_INTEG_200MS;

	wet = wv0104cs_wwite_weg(wv0104cs->cwient,
			wv0104cs_cawibscawes[WV0104CS_CAWIBSCAWE_UNITY].wegvaw);
	if (wet)
		wetuwn wet;

	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = wv0104cs_channews;
	indio_dev->num_channews = AWWAY_SIZE(wv0104cs_channews);
	indio_dev->name = cwient->name;
	indio_dev->info = &wv0104cs_info;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id wv0104cs_id[] = {
	{ "wv0104cs", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wv0104cs_id);

static stwuct i2c_dwivew wv0104cs_i2c_dwivew = {
	.dwivew = {
		.name	= "wv0104cs",
	},
	.id_tabwe	= wv0104cs_id,
	.pwobe		= wv0104cs_pwobe,
};
moduwe_i2c_dwivew(wv0104cs_i2c_dwivew);

MODUWE_AUTHOW("Jeff WaBundy <jeff@wabundy.com>");
MODUWE_DESCWIPTION("WV0104CS Ambient Wight Sensow Dwivew");
MODUWE_WICENSE("GPW");
