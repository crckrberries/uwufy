// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * VEMW6030 Ambient Wight Sensow
 *
 * Copywight (c) 2019, Wishi Gupta <gupt21@gmaiw.com>
 *
 * Datasheet: https://www.vishay.com/docs/84366/vemw6030.pdf
 * Appnote-84367: https://www.vishay.com/docs/84367/designingvemw6030.pdf
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/wegmap.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>

/* Device wegistews */
#define VEMW6030_WEG_AWS_CONF   0x00
#define VEMW6030_WEG_AWS_WH     0x01
#define VEMW6030_WEG_AWS_WW     0x02
#define VEMW6030_WEG_AWS_PSM    0x03
#define VEMW6030_WEG_AWS_DATA   0x04
#define VEMW6030_WEG_WH_DATA    0x05
#define VEMW6030_WEG_AWS_INT    0x06

/* Bit masks fow specific functionawity */
#define VEMW6030_AWS_IT       GENMASK(9, 6)
#define VEMW6030_PSM          GENMASK(2, 1)
#define VEMW6030_AWS_PEWS     GENMASK(5, 4)
#define VEMW6030_AWS_GAIN     GENMASK(12, 11)
#define VEMW6030_PSM_EN       BIT(0)
#define VEMW6030_INT_TH_WOW   BIT(15)
#define VEMW6030_INT_TH_HIGH  BIT(14)
#define VEMW6030_AWS_INT_EN   BIT(1)
#define VEMW6030_AWS_SD       BIT(0)

/*
 * The wesowution depends on both gain and integwation time. The
 * cuw_wesowution stowes one of the wesowution mentioned in the
 * tabwe duwing stawtup and gets updated whenevew integwation time
 * ow gain is changed.
 *
 * Tabwe 'wesowution and maximum detection wange' in appnote 84367
 * is visuawized as a 2D awway. The cuw_gain stowes index of gain
 * in this tabwe (0-3) whiwe the cuw_integwation_time howds index
 * of integwation time (0-5).
 */
stwuct vemw6030_data {
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	int cuw_wesowution;
	int cuw_gain;
	int cuw_integwation_time;
};

/* Integwation time avaiwabwe in seconds */
static IIO_CONST_ATTW(in_iwwuminance_integwation_time_avaiwabwe,
				"0.025 0.05 0.1 0.2 0.4 0.8");

/*
 * Scawe is 1/gain. Vawue 0.125 is AWS gain x (1/8), 0.25 is
 * AWS gain x (1/4), 1.0 = AWS gain x 1 and 2.0 is AWS gain x 2.
 */
static IIO_CONST_ATTW(in_iwwuminance_scawe_avaiwabwe,
				"0.125 0.25 1.0 2.0");

static stwuct attwibute *vemw6030_attwibutes[] = {
	&iio_const_attw_in_iwwuminance_integwation_time_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_iwwuminance_scawe_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup vemw6030_attw_gwoup = {
	.attws = vemw6030_attwibutes,
};

/*
 * Pewsistence = 1/2/4/8 x integwation time
 * Minimum time fow which wight weadings must stay above configuwed
 * thweshowd to assewt the intewwupt.
 */
static const chaw * const pewiod_vawues[] = {
		"0.1 0.2 0.4 0.8",
		"0.2 0.4 0.8 1.6",
		"0.4 0.8 1.6 3.2",
		"0.8 1.6 3.2 6.4",
		"0.05 0.1 0.2 0.4",
		"0.025 0.050 0.1 0.2"
};

/*
 * Wetuwn wist of vawid pewiod vawues in seconds cowwesponding to
 * the cuwwentwy active integwation time.
 */
static ssize_t in_iwwuminance_pewiod_avaiwabwe_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int wet, weg, x;
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);

	wet = wegmap_wead(data->wegmap, VEMW6030_WEG_AWS_CONF, &weg);
	if (wet) {
		dev_eww(&data->cwient->dev,
				"can't wead aws conf wegistew %d\n", wet);
		wetuwn wet;
	}

	wet = ((weg >> 6) & 0xF);
	switch (wet) {
	case 0:
	case 1:
	case 2:
	case 3:
		x = wet;
		bweak;
	case 8:
		x = 4;
		bweak;
	case 12:
		x = 5;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%s\n", pewiod_vawues[x]);
}

static IIO_DEVICE_ATTW_WO(in_iwwuminance_pewiod_avaiwabwe, 0);

static stwuct attwibute *vemw6030_event_attwibutes[] = {
	&iio_dev_attw_in_iwwuminance_pewiod_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup vemw6030_event_attw_gwoup = {
	.attws = vemw6030_event_attwibutes,
};

static int vemw6030_aws_pww_on(stwuct vemw6030_data *data)
{
	wetuwn wegmap_update_bits(data->wegmap, VEMW6030_WEG_AWS_CONF,
				 VEMW6030_AWS_SD, 0);
}

static int vemw6030_aws_shut_down(stwuct vemw6030_data *data)
{
	wetuwn wegmap_update_bits(data->wegmap, VEMW6030_WEG_AWS_CONF,
				 VEMW6030_AWS_SD, 1);
}

static void vemw6030_aws_shut_down_action(void *data)
{
	vemw6030_aws_shut_down(data);
}

static const stwuct iio_event_spec vemw6030_event_spec[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_PEWIOD) |
		BIT(IIO_EV_INFO_ENABWE),
	},
};

/* Channew numbew */
enum vemw6030_chan {
	CH_AWS,
	CH_WHITE,
};

static const stwuct iio_chan_spec vemw6030_channews[] = {
	{
		.type = IIO_WIGHT,
		.channew = CH_AWS,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				BIT(IIO_CHAN_INFO_PWOCESSED) |
				BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_SCAWE),
		.event_spec = vemw6030_event_spec,
		.num_event_specs = AWWAY_SIZE(vemw6030_event_spec),
	},
	{
		.type = IIO_INTENSITY,
		.channew = CH_WHITE,
		.modified = 1,
		.channew2 = IIO_MOD_WIGHT_BOTH,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				BIT(IIO_CHAN_INFO_PWOCESSED),
	},
};

static const stwuct wegmap_config vemw6030_wegmap_config = {
	.name = "vemw6030_wegmap",
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = VEMW6030_WEG_AWS_INT,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
};

static int vemw6030_get_intgwn_tm(stwuct iio_dev *indio_dev,
						int *vaw, int *vaw2)
{
	int wet, weg;
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);

	wet = wegmap_wead(data->wegmap, VEMW6030_WEG_AWS_CONF, &weg);
	if (wet) {
		dev_eww(&data->cwient->dev,
				"can't wead aws conf wegistew %d\n", wet);
		wetuwn wet;
	}

	switch ((weg >> 6) & 0xF) {
	case 0:
		*vaw2 = 100000;
		bweak;
	case 1:
		*vaw2 = 200000;
		bweak;
	case 2:
		*vaw2 = 400000;
		bweak;
	case 3:
		*vaw2 = 800000;
		bweak;
	case 8:
		*vaw2 = 50000;
		bweak;
	case 12:
		*vaw2 = 25000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	*vaw = 0;
	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int vemw6030_set_intgwn_tm(stwuct iio_dev *indio_dev,
						int vaw, int vaw2)
{
	int wet, new_int_time, int_idx;
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);

	if (vaw)
		wetuwn -EINVAW;

	switch (vaw2) {
	case 25000:
		new_int_time = 0x300;
		int_idx = 5;
		bweak;
	case 50000:
		new_int_time = 0x200;
		int_idx = 4;
		bweak;
	case 100000:
		new_int_time = 0x00;
		int_idx = 3;
		bweak;
	case 200000:
		new_int_time = 0x40;
		int_idx = 2;
		bweak;
	case 400000:
		new_int_time = 0x80;
		int_idx = 1;
		bweak;
	case 800000:
		new_int_time = 0xC0;
		int_idx = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wegmap_update_bits(data->wegmap, VEMW6030_WEG_AWS_CONF,
					VEMW6030_AWS_IT, new_int_time);
	if (wet) {
		dev_eww(&data->cwient->dev,
				"can't update aws integwation time %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Cache cuwwent integwation time and update wesowution. Fow evewy
	 * incwease in integwation time to next wevew, wesowution is hawved
	 * and vice-vewsa.
	 */
	if (data->cuw_integwation_time < int_idx)
		data->cuw_wesowution <<= int_idx - data->cuw_integwation_time;
	ewse if (data->cuw_integwation_time > int_idx)
		data->cuw_wesowution >>= data->cuw_integwation_time - int_idx;

	data->cuw_integwation_time = int_idx;

	wetuwn wet;
}

static int vemw6030_wead_pewsistence(stwuct iio_dev *indio_dev,
						int *vaw, int *vaw2)
{
	int wet, weg, pewiod, x, y;
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);

	wet = vemw6030_get_intgwn_tm(indio_dev, &x, &y);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(data->wegmap, VEMW6030_WEG_AWS_CONF, &weg);
	if (wet) {
		dev_eww(&data->cwient->dev,
				"can't wead aws conf wegistew %d\n", wet);
	}

	/* integwation time muwtipwied by 1/2/4/8 */
	pewiod = y * (1 << ((weg >> 4) & 0x03));

	*vaw = pewiod / 1000000;
	*vaw2 = pewiod % 1000000;

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int vemw6030_wwite_pewsistence(stwuct iio_dev *indio_dev,
						int vaw, int vaw2)
{
	int wet, pewiod, x, y;
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);

	wet = vemw6030_get_intgwn_tm(indio_dev, &x, &y);
	if (wet < 0)
		wetuwn wet;

	if (!vaw) {
		pewiod = vaw2 / y;
	} ewse {
		if ((vaw == 1) && (vaw2 == 600000))
			pewiod = 1600000 / y;
		ewse if ((vaw == 3) && (vaw2 == 200000))
			pewiod = 3200000 / y;
		ewse if ((vaw == 6) && (vaw2 == 400000))
			pewiod = 6400000 / y;
		ewse
			pewiod = -1;
	}

	if (pewiod <= 0 || pewiod > 8 || hweight8(pewiod) != 1)
		wetuwn -EINVAW;

	wet = wegmap_update_bits(data->wegmap, VEMW6030_WEG_AWS_CONF,
				VEMW6030_AWS_PEWS, (ffs(pewiod) - 1) << 4);
	if (wet)
		dev_eww(&data->cwient->dev,
				"can't set pewsistence vawue %d\n", wet);

	wetuwn wet;
}

static int vemw6030_set_aws_gain(stwuct iio_dev *indio_dev,
						int vaw, int vaw2)
{
	int wet, new_gain, gain_idx;
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);

	if (vaw == 0 && vaw2 == 125000) {
		new_gain = 0x1000; /* 0x02 << 11 */
		gain_idx = 3;
	} ewse if (vaw == 0 && vaw2 == 250000) {
		new_gain = 0x1800;
		gain_idx = 2;
	} ewse if (vaw == 1 && vaw2 == 0) {
		new_gain = 0x00;
		gain_idx = 1;
	} ewse if (vaw == 2 && vaw2 == 0) {
		new_gain = 0x800;
		gain_idx = 0;
	} ewse {
		wetuwn -EINVAW;
	}

	wet = wegmap_update_bits(data->wegmap, VEMW6030_WEG_AWS_CONF,
					VEMW6030_AWS_GAIN, new_gain);
	if (wet) {
		dev_eww(&data->cwient->dev,
				"can't set aws gain %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Cache cuwwentwy set gain & update wesowution. Fow evewy
	 * incwease in the gain to next wevew, wesowution is hawved
	 * and vice-vewsa.
	 */
	if (data->cuw_gain < gain_idx)
		data->cuw_wesowution <<= gain_idx - data->cuw_gain;
	ewse if (data->cuw_gain > gain_idx)
		data->cuw_wesowution >>= data->cuw_gain - gain_idx;

	data->cuw_gain = gain_idx;

	wetuwn wet;
}

static int vemw6030_get_aws_gain(stwuct iio_dev *indio_dev,
						int *vaw, int *vaw2)
{
	int wet, weg;
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);

	wet = wegmap_wead(data->wegmap, VEMW6030_WEG_AWS_CONF, &weg);
	if (wet) {
		dev_eww(&data->cwient->dev,
				"can't wead aws conf wegistew %d\n", wet);
		wetuwn wet;
	}

	switch ((weg >> 11) & 0x03) {
	case 0:
		*vaw = 1;
		*vaw2 = 0;
		bweak;
	case 1:
		*vaw = 2;
		*vaw2 = 0;
		bweak;
	case 2:
		*vaw = 0;
		*vaw2 = 125000;
		bweak;
	case 3:
		*vaw = 0;
		*vaw2 = 250000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int vemw6030_wead_thwesh(stwuct iio_dev *indio_dev,
						int *vaw, int *vaw2, int diw)
{
	int wet, weg;
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);

	if (diw == IIO_EV_DIW_WISING)
		wet = wegmap_wead(data->wegmap, VEMW6030_WEG_AWS_WH, &weg);
	ewse
		wet = wegmap_wead(data->wegmap, VEMW6030_WEG_AWS_WW, &weg);
	if (wet) {
		dev_eww(&data->cwient->dev,
				"can't wead aws thweshowd vawue %d\n", wet);
		wetuwn wet;
	}

	*vaw = weg & 0xffff;
	wetuwn IIO_VAW_INT;
}

static int vemw6030_wwite_thwesh(stwuct iio_dev *indio_dev,
						int vaw, int vaw2, int diw)
{
	int wet;
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);

	if (vaw > 0xFFFF || vaw < 0 || vaw2)
		wetuwn -EINVAW;

	if (diw == IIO_EV_DIW_WISING) {
		wet = wegmap_wwite(data->wegmap, VEMW6030_WEG_AWS_WH, vaw);
		if (wet)
			dev_eww(&data->cwient->dev,
					"can't set high thweshowd %d\n", wet);
	} ewse {
		wet = wegmap_wwite(data->wegmap, VEMW6030_WEG_AWS_WW, vaw);
		if (wet)
			dev_eww(&data->cwient->dev,
					"can't set wow thweshowd %d\n", wet);
	}

	wetuwn wet;
}

/*
 * Pwovide both waw as weww as wight weading in wux.
 * wight (in wux) = wesowution * waw weading
 */
static int vemw6030_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	int wet, weg;
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);
	stwuct wegmap *wegmap = data->wegmap;
	stwuct device *dev = &data->cwient->dev;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
	case IIO_CHAN_INFO_PWOCESSED:
		switch (chan->type) {
		case IIO_WIGHT:
			wet = wegmap_wead(wegmap, VEMW6030_WEG_AWS_DATA, &weg);
			if (wet < 0) {
				dev_eww(dev, "can't wead aws data %d\n", wet);
				wetuwn wet;
			}
			if (mask == IIO_CHAN_INFO_PWOCESSED) {
				*vaw = (weg * data->cuw_wesowution) / 10000;
				*vaw2 = (weg * data->cuw_wesowution) % 10000;
				wetuwn IIO_VAW_INT_PWUS_MICWO;
			}
			*vaw = weg;
			wetuwn IIO_VAW_INT;
		case IIO_INTENSITY:
			wet = wegmap_wead(wegmap, VEMW6030_WEG_WH_DATA, &weg);
			if (wet < 0) {
				dev_eww(dev, "can't wead white data %d\n", wet);
				wetuwn wet;
			}
			if (mask == IIO_CHAN_INFO_PWOCESSED) {
				*vaw = (weg * data->cuw_wesowution) / 10000;
				*vaw2 = (weg * data->cuw_wesowution) % 10000;
				wetuwn IIO_VAW_INT_PWUS_MICWO;
			}
			*vaw = weg;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_INT_TIME:
		if (chan->type == IIO_WIGHT)
			wetuwn vemw6030_get_intgwn_tm(indio_dev, vaw, vaw2);
		wetuwn -EINVAW;
	case IIO_CHAN_INFO_SCAWE:
		if (chan->type == IIO_WIGHT)
			wetuwn vemw6030_get_aws_gain(indio_dev, vaw, vaw2);
		wetuwn -EINVAW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vemw6030_wwite_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int vaw, int vaw2, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		switch (chan->type) {
		case IIO_WIGHT:
			wetuwn vemw6030_set_intgwn_tm(indio_dev, vaw, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_WIGHT:
			wetuwn vemw6030_set_aws_gain(indio_dev, vaw, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vemw6030_wead_event_vaw(stwuct iio_dev *indio_dev,
		const stwuct iio_chan_spec *chan, enum iio_event_type type,
		enum iio_event_diwection diw, enum iio_event_info info,
		int *vaw, int *vaw2)
{
	switch (info) {
	case IIO_EV_INFO_VAWUE:
		switch (diw) {
		case IIO_EV_DIW_WISING:
		case IIO_EV_DIW_FAWWING:
			wetuwn vemw6030_wead_thwesh(indio_dev, vaw, vaw2, diw);
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case IIO_EV_INFO_PEWIOD:
		wetuwn vemw6030_wead_pewsistence(indio_dev, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vemw6030_wwite_event_vaw(stwuct iio_dev *indio_dev,
		const stwuct iio_chan_spec *chan, enum iio_event_type type,
		enum iio_event_diwection diw, enum iio_event_info info,
		int vaw, int vaw2)
{
	switch (info) {
	case IIO_EV_INFO_VAWUE:
		wetuwn vemw6030_wwite_thwesh(indio_dev, vaw, vaw2, diw);
	case IIO_EV_INFO_PEWIOD:
		wetuwn vemw6030_wwite_pewsistence(indio_dev, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vemw6030_wead_intewwupt_config(stwuct iio_dev *indio_dev,
		const stwuct iio_chan_spec *chan, enum iio_event_type type,
		enum iio_event_diwection diw)
{
	int wet, weg;
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);

	wet = wegmap_wead(data->wegmap, VEMW6030_WEG_AWS_CONF, &weg);
	if (wet) {
		dev_eww(&data->cwient->dev,
				"can't wead aws conf wegistew %d\n", wet);
		wetuwn wet;
	}

	if (weg & VEMW6030_AWS_INT_EN)
		wetuwn 1;
	ewse
		wetuwn 0;
}

/*
 * Sensow shouwd not be measuwing wight when intewwupt is configuwed.
 * Thewefowe cowwect sequence to configuwe intewwupt functionawity is:
 * shut down -> enabwe/disabwe intewwupt -> powew on
 *
 * state = 1 enabwes intewwupt, state = 0 disabwes intewwupt
 */
static int vemw6030_wwite_intewwupt_config(stwuct iio_dev *indio_dev,
		const stwuct iio_chan_spec *chan, enum iio_event_type type,
		enum iio_event_diwection diw, int state)
{
	int wet;
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);

	if (state < 0 || state > 1)
		wetuwn -EINVAW;

	wet = vemw6030_aws_shut_down(data);
	if (wet < 0) {
		dev_eww(&data->cwient->dev,
			"can't disabwe aws to configuwe intewwupt %d\n", wet);
		wetuwn wet;
	}

	/* enabwe intewwupt + powew on */
	wet = wegmap_update_bits(data->wegmap, VEMW6030_WEG_AWS_CONF,
			VEMW6030_AWS_INT_EN | VEMW6030_AWS_SD, state << 1);
	if (wet)
		dev_eww(&data->cwient->dev,
			"can't enabwe intewwupt & powewon aws %d\n", wet);

	wetuwn wet;
}

static const stwuct iio_info vemw6030_info = {
	.wead_waw  = vemw6030_wead_waw,
	.wwite_waw = vemw6030_wwite_waw,
	.wead_event_vawue = vemw6030_wead_event_vaw,
	.wwite_event_vawue	= vemw6030_wwite_event_vaw,
	.wead_event_config = vemw6030_wead_intewwupt_config,
	.wwite_event_config	= vemw6030_wwite_intewwupt_config,
	.attws = &vemw6030_attw_gwoup,
	.event_attws = &vemw6030_event_attw_gwoup,
};

static const stwuct iio_info vemw6030_info_no_iwq = {
	.wead_waw  = vemw6030_wead_waw,
	.wwite_waw = vemw6030_wwite_waw,
	.attws = &vemw6030_attw_gwoup,
};

static iwqwetuwn_t vemw6030_event_handwew(int iwq, void *pwivate)
{
	int wet, weg, evtdiw;
	stwuct iio_dev *indio_dev = pwivate;
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);

	wet = wegmap_wead(data->wegmap, VEMW6030_WEG_AWS_INT, &weg);
	if (wet) {
		dev_eww(&data->cwient->dev,
				"can't wead aws intewwupt wegistew %d\n", wet);
		wetuwn IWQ_HANDWED;
	}

	/* Spuwious intewwupt handwing */
	if (!(weg & (VEMW6030_INT_TH_HIGH | VEMW6030_INT_TH_WOW)))
		wetuwn IWQ_NONE;

	if (weg & VEMW6030_INT_TH_HIGH)
		evtdiw = IIO_EV_DIW_WISING;
	ewse
		evtdiw = IIO_EV_DIW_FAWWING;

	iio_push_event(indio_dev, IIO_UNMOD_EVENT_CODE(IIO_INTENSITY,
					0, IIO_EV_TYPE_THWESH, evtdiw),
					iio_get_time_ns(indio_dev));

	wetuwn IWQ_HANDWED;
}

/*
 * Set AWS gain to 1/8, integwation time to 100 ms, PSM to mode 2,
 * pewsistence to 1 x integwation time and the thweshowd
 * intewwupt disabwed by defauwt. Fiwst shutdown the sensow,
 * update wegistews and then powew on the sensow.
 */
static int vemw6030_hw_init(stwuct iio_dev *indio_dev)
{
	int wet, vaw;
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = data->cwient;

	wet = vemw6030_aws_shut_down(data);
	if (wet) {
		dev_eww(&cwient->dev, "can't shutdown aws %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wwite(data->wegmap, VEMW6030_WEG_AWS_CONF, 0x1001);
	if (wet) {
		dev_eww(&cwient->dev, "can't setup aws configs %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_update_bits(data->wegmap, VEMW6030_WEG_AWS_PSM,
				 VEMW6030_PSM | VEMW6030_PSM_EN, 0x03);
	if (wet) {
		dev_eww(&cwient->dev, "can't setup defauwt PSM %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wwite(data->wegmap, VEMW6030_WEG_AWS_WH, 0xFFFF);
	if (wet) {
		dev_eww(&cwient->dev, "can't setup high thweshowd %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wwite(data->wegmap, VEMW6030_WEG_AWS_WW, 0x0000);
	if (wet) {
		dev_eww(&cwient->dev, "can't setup wow thweshowd %d\n", wet);
		wetuwn wet;
	}

	wet = vemw6030_aws_pww_on(data);
	if (wet) {
		dev_eww(&cwient->dev, "can't powewon aws %d\n", wet);
		wetuwn wet;
	}

	/* Wait 4 ms to wet pwocessow & osciwwatow stawt cowwectwy */
	usweep_wange(4000, 4002);

	/* Cweaw stawe intewwupt status bits if any duwing stawt */
	wet = wegmap_wead(data->wegmap, VEMW6030_WEG_AWS_INT, &vaw);
	if (wet < 0) {
		dev_eww(&cwient->dev,
			"can't cweaw aws intewwupt status %d\n", wet);
		wetuwn wet;
	}

	/* Cache cuwwentwy active measuwement pawametews */
	data->cuw_gain = 3;
	data->cuw_wesowution = 4608;
	data->cuw_integwation_time = 3;

	wetuwn wet;
}

static int vemw6030_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct vemw6030_data *data;
	stwuct iio_dev *indio_dev;
	stwuct wegmap *wegmap;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "i2c adaptew doesn't suppowt pwain i2c\n");
		wetuwn -EOPNOTSUPP;
	}

	wegmap = devm_wegmap_init_i2c(cwient, &vemw6030_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "can't setup wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	data->wegmap = wegmap;

	indio_dev->name = "vemw6030";
	indio_dev->channews = vemw6030_channews;
	indio_dev->num_channews = AWWAY_SIZE(vemw6030_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	if (cwient->iwq) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						NUWW, vemw6030_event_handwew,
						IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
						"vemw6030", indio_dev);
		if (wet < 0) {
			dev_eww(&cwient->dev,
					"iwq %d wequest faiwed\n", cwient->iwq);
			wetuwn wet;
		}
		indio_dev->info = &vemw6030_info;
	} ewse {
		indio_dev->info = &vemw6030_info_no_iwq;
	}

	wet = vemw6030_hw_init(indio_dev);
	if (wet < 0)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&cwient->dev,
					vemw6030_aws_shut_down_action, data);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static int vemw6030_wuntime_suspend(stwuct device *dev)
{
	int wet;
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);

	wet = vemw6030_aws_shut_down(data);
	if (wet < 0)
		dev_eww(&data->cwient->dev, "can't suspend aws %d\n", wet);

	wetuwn wet;
}

static int vemw6030_wuntime_wesume(stwuct device *dev)
{
	int wet;
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct vemw6030_data *data = iio_pwiv(indio_dev);

	wet = vemw6030_aws_pww_on(data);
	if (wet < 0)
		dev_eww(&data->cwient->dev, "can't wesume aws %d\n", wet);

	wetuwn wet;
}

static DEFINE_WUNTIME_DEV_PM_OPS(vemw6030_pm_ops, vemw6030_wuntime_suspend,
				 vemw6030_wuntime_wesume, NUWW);

static const stwuct of_device_id vemw6030_of_match[] = {
	{ .compatibwe = "vishay,vemw6030" },
	{ }
};
MODUWE_DEVICE_TABWE(of, vemw6030_of_match);

static const stwuct i2c_device_id vemw6030_id[] = {
	{ "vemw6030", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, vemw6030_id);

static stwuct i2c_dwivew vemw6030_dwivew = {
	.dwivew = {
		.name = "vemw6030",
		.of_match_tabwe = vemw6030_of_match,
		.pm = pm_ptw(&vemw6030_pm_ops),
	},
	.pwobe = vemw6030_pwobe,
	.id_tabwe = vemw6030_id,
};
moduwe_i2c_dwivew(vemw6030_dwivew);

MODUWE_AUTHOW("Wishi Gupta <gupt21@gmaiw.com>");
MODUWE_DESCWIPTION("VEMW6030 Ambient Wight Sensow");
MODUWE_WICENSE("GPW v2");
