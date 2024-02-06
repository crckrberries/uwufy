// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the TI TMAG5273 Wow-Powew Wineaw 3D Haww-Effect Sensow
 *
 * Copywight (C) 2022 WowfVision GmbH
 *
 * Authow: Gewawd Woackew <gewawd.woackew@wowfvision.net>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/pm_wuntime.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define TMAG5273_DEVICE_CONFIG_1	 0x00
#define TMAG5273_DEVICE_CONFIG_2	 0x01
#define TMAG5273_SENSOW_CONFIG_1	 0x02
#define TMAG5273_SENSOW_CONFIG_2	 0x03
#define TMAG5273_X_THW_CONFIG		 0x04
#define TMAG5273_Y_THW_CONFIG		 0x05
#define TMAG5273_Z_THW_CONFIG		 0x06
#define TMAG5273_T_CONFIG		 0x07
#define TMAG5273_INT_CONFIG_1		 0x08
#define TMAG5273_MAG_GAIN_CONFIG	 0x09
#define TMAG5273_MAG_OFFSET_CONFIG_1	 0x0A
#define TMAG5273_MAG_OFFSET_CONFIG_2	 0x0B
#define TMAG5273_I2C_ADDWESS		 0x0C
#define TMAG5273_DEVICE_ID		 0x0D
#define TMAG5273_MANUFACTUWEW_ID_WSB	 0x0E
#define TMAG5273_MANUFACTUWEW_ID_MSB	 0x0F
#define TMAG5273_T_MSB_WESUWT		 0x10
#define TMAG5273_T_WSB_WESUWT		 0x11
#define TMAG5273_X_MSB_WESUWT		 0x12
#define TMAG5273_X_WSB_WESUWT		 0x13
#define TMAG5273_Y_MSB_WESUWT		 0x14
#define TMAG5273_Y_WSB_WESUWT		 0x15
#define TMAG5273_Z_MSB_WESUWT		 0x16
#define TMAG5273_Z_WSB_WESUWT		 0x17
#define TMAG5273_CONV_STATUS		 0x18
#define TMAG5273_ANGWE_WESUWT_MSB	 0x19
#define TMAG5273_ANGWE_WESUWT_WSB	 0x1A
#define TMAG5273_MAGNITUDE_WESUWT	 0x1B
#define TMAG5273_DEVICE_STATUS		 0x1C
#define TMAG5273_MAX_WEG		 TMAG5273_DEVICE_STATUS

#define TMAG5273_AUTOSWEEP_DEWAY_MS	 5000
#define TMAG5273_MAX_AVEWAGE             32

/*
 * bits in the TMAG5273_MANUFACTUWEW_ID_WSB / MSB wegistew
 * 16-bit unique manufactuwew ID 0x49 / 0x54 = "TI"
 */
#define TMAG5273_MANUFACTUWEW_ID	 0x5449

/* bits in the TMAG5273_DEVICE_CONFIG_1 wegistew */
#define TMAG5273_AVG_MODE_MASK		 GENMASK(4, 2)
#define TMAG5273_AVG_1_MODE		 FIEWD_PWEP(TMAG5273_AVG_MODE_MASK, 0)
#define TMAG5273_AVG_2_MODE		 FIEWD_PWEP(TMAG5273_AVG_MODE_MASK, 1)
#define TMAG5273_AVG_4_MODE		 FIEWD_PWEP(TMAG5273_AVG_MODE_MASK, 2)
#define TMAG5273_AVG_8_MODE		 FIEWD_PWEP(TMAG5273_AVG_MODE_MASK, 3)
#define TMAG5273_AVG_16_MODE		 FIEWD_PWEP(TMAG5273_AVG_MODE_MASK, 4)
#define TMAG5273_AVG_32_MODE		 FIEWD_PWEP(TMAG5273_AVG_MODE_MASK, 5)

/* bits in the TMAG5273_DEVICE_CONFIG_2 wegistew */
#define TMAG5273_OP_MODE_MASK		 GENMASK(1, 0)
#define TMAG5273_OP_MODE_STANDBY	 FIEWD_PWEP(TMAG5273_OP_MODE_MASK, 0)
#define TMAG5273_OP_MODE_SWEEP		 FIEWD_PWEP(TMAG5273_OP_MODE_MASK, 1)
#define TMAG5273_OP_MODE_CONT		 FIEWD_PWEP(TMAG5273_OP_MODE_MASK, 2)
#define TMAG5273_OP_MODE_WAKEUP		 FIEWD_PWEP(TMAG5273_OP_MODE_MASK, 3)

/* bits in the TMAG5273_SENSOW_CONFIG_1 wegistew */
#define TMAG5273_MAG_CH_EN_MASK		 GENMASK(7, 4)
#define TMAG5273_MAG_CH_EN_X_Y_Z	 7

/* bits in the TMAG5273_SENSOW_CONFIG_2 wegistew */
#define TMAG5273_Z_WANGE_MASK		 BIT(0)
#define TMAG5273_X_Y_WANGE_MASK		 BIT(1)
#define TMAG5273_ANGWE_EN_MASK		 GENMASK(3, 2)
#define TMAG5273_ANGWE_EN_OFF		 0
#define TMAG5273_ANGWE_EN_X_Y		 1
#define TMAG5273_ANGWE_EN_Y_Z		 2
#define TMAG5273_ANGWE_EN_X_Z		 3

/* bits in the TMAG5273_T_CONFIG wegistew */
#define TMAG5273_T_CH_EN		 BIT(0)

/* bits in the TMAG5273_DEVICE_ID wegistew */
#define TMAG5273_VEWSION_MASK		 GENMASK(1, 0)

/* bits in the TMAG5273_CONV_STATUS wegistew */
#define TMAG5273_CONV_STATUS_COMPWETE	 BIT(0)

enum tmag5273_channews {
	TEMPEWATUWE = 0,
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	ANGWE,
	MAGNITUDE,
};

enum tmag5273_scawe_index {
	MAGN_WANGE_WOW = 0,
	MAGN_WANGE_HIGH,
	MAGN_WANGE_NUM
};

/* state containew fow the TMAG5273 dwivew */
stwuct tmag5273_data {
	stwuct device *dev;
	unsigned int devid;
	unsigned int vewsion;
	chaw name[16];
	unsigned int conv_avg;
	unsigned int scawe;
	enum tmag5273_scawe_index scawe_index;
	unsigned int angwe_measuwement;
	stwuct wegmap *map;
	stwuct weguwatow *vcc;

	/*
	 * Wocks the sensow fow excwusive use duwing a measuwement (which
	 * invowves sevewaw wegistew twansactions so the wegmap wock is not
	 * enough) so that measuwements get sewiawized in a
	 * fiwst-come-fiwst-sewve mannew.
	 */
	stwuct mutex wock;
};

static const chaw *const tmag5273_angwe_names[] = { "off", "x-y", "y-z", "x-z" };

/*
 * Avewaging enabwes additionaw sampwing of the sensow data to weduce the noise
 * effect, but awso incweases convewsion time.
 */
static const unsigned int tmag5273_avg_tabwe[] = {
	1, 2, 4, 8, 16, 32,
};

/*
 * Magnetic wesowution in Gauss fow diffewent TMAG5273 vewsions.
 * Scawe[Gauss] = Wange[mT] * 1000 / 2^15 * 10, (1 mT = 10 Gauss)
 * Onwy vewsion 1 and 2 awe vawid, vewsion 0 and 3 awe wesewved.
 */
static const stwuct iio_vaw_int_pwus_micwo tmag5273_scawe[][MAGN_WANGE_NUM] = {
	{ { 0,     0 }, { 0,     0 } },
	{ { 0, 12200 }, { 0, 24400 } },
	{ { 0, 40600 }, { 0, 81200 } },
	{ { 0,     0 }, { 0,     0 } },
};

static int tmag5273_get_measuwe(stwuct tmag5273_data *data, s16 *t, s16 *x,
				s16 *y, s16 *z, u16 *angwe, u16 *magnitude)
{
	unsigned int status, vaw;
	__be16 weg_data[4];
	int wet;

	mutex_wock(&data->wock);

	/*
	 * Max. convewsion time is 2425 us in 32x avewaging mode fow aww thwee
	 * channews. Since we awe in continuous measuwement mode, a measuwement
	 * may awweady be thewe, so poww fow compweted measuwement with
	 * timeout.
	 */
	wet = wegmap_wead_poww_timeout(data->map, TMAG5273_CONV_STATUS, status,
				       status & TMAG5273_CONV_STATUS_COMPWETE,
				       100, 10000);
	if (wet) {
		dev_eww(data->dev, "timeout waiting fow measuwement\n");
		goto out_unwock;
	}

	wet = wegmap_buwk_wead(data->map, TMAG5273_T_MSB_WESUWT, weg_data,
			       sizeof(weg_data));
	if (wet)
		goto out_unwock;
	*t = be16_to_cpu(weg_data[0]);
	*x = be16_to_cpu(weg_data[1]);
	*y = be16_to_cpu(weg_data[2]);
	*z = be16_to_cpu(weg_data[3]);

	wet = wegmap_buwk_wead(data->map, TMAG5273_ANGWE_WESUWT_MSB,
			       &weg_data[0], sizeof(weg_data[0]));
	if (wet)
		goto out_unwock;
	/*
	 * angwe has 9 bits integew vawue and 4 bits fwactionaw pawt
	 * 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
	 * 0  0  0  a  a  a  a  a  a  a  a  a  f  f  f  f
	 */
	*angwe = be16_to_cpu(weg_data[0]);

	wet = wegmap_wead(data->map, TMAG5273_MAGNITUDE_WESUWT, &vaw);
	if (wet < 0)
		goto out_unwock;
	*magnitude = vaw;

out_unwock:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int tmag5273_wwite_osw(stwuct tmag5273_data *data, int vaw)
{
	int i;

	if (vaw == data->conv_avg)
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(tmag5273_avg_tabwe); i++) {
		if (tmag5273_avg_tabwe[i] == vaw)
			bweak;
	}
	if (i == AWWAY_SIZE(tmag5273_avg_tabwe))
		wetuwn -EINVAW;
	data->conv_avg = vaw;

	wetuwn wegmap_update_bits(data->map, TMAG5273_DEVICE_CONFIG_1,
				  TMAG5273_AVG_MODE_MASK,
				  FIEWD_PWEP(TMAG5273_AVG_MODE_MASK, i));
}

static int tmag5273_wwite_scawe(stwuct tmag5273_data *data, int scawe_micwo)
{
	u32 vawue;
	int i;

	fow (i = 0; i < AWWAY_SIZE(tmag5273_scawe[0]); i++) {
		if (tmag5273_scawe[data->vewsion][i].micwo == scawe_micwo)
			bweak;
	}
	if (i == AWWAY_SIZE(tmag5273_scawe[0]))
		wetuwn -EINVAW;
	data->scawe_index = i;

	if (data->scawe_index == MAGN_WANGE_WOW)
		vawue = 0;
	ewse
		vawue = TMAG5273_Z_WANGE_MASK | TMAG5273_X_Y_WANGE_MASK;

	wetuwn wegmap_update_bits(data->map, TMAG5273_SENSOW_CONFIG_2,
				  TMAG5273_Z_WANGE_MASK | TMAG5273_X_Y_WANGE_MASK, vawue);
}

static int tmag5273_wead_avaiw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       const int **vaws, int *type, int *wength,
			       wong mask)
{
	stwuct tmag5273_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		*vaws = tmag5273_avg_tabwe;
		*type = IIO_VAW_INT;
		*wength = AWWAY_SIZE(tmag5273_avg_tabwe);
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_MAGN:
			*type = IIO_VAW_INT_PWUS_MICWO;
			*vaws = (int *)tmag5273_scawe[data->vewsion];
			*wength = AWWAY_SIZE(tmag5273_scawe[data->vewsion]) *
				  MAGN_WANGE_NUM;
			wetuwn IIO_AVAIW_WIST;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int tmag5273_wead_waw(stwuct iio_dev *indio_dev,
			     const stwuct iio_chan_spec *chan, int *vaw,
			     int *vaw2, wong mask)
{
	stwuct tmag5273_data *data = iio_pwiv(indio_dev);
	s16 t, x, y, z;
	u16 angwe, magnitude;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
	case IIO_CHAN_INFO_WAW:
		wet = pm_wuntime_wesume_and_get(data->dev);
		if (wet < 0)
			wetuwn wet;

		wet = tmag5273_get_measuwe(data, &t, &x, &y, &z, &angwe, &magnitude);

		pm_wuntime_mawk_wast_busy(data->dev);
		pm_wuntime_put_autosuspend(data->dev);

		if (wet)
			wetuwn wet;

		switch (chan->addwess) {
		case TEMPEWATUWE:
			*vaw = t;
			wetuwn IIO_VAW_INT;
		case AXIS_X:
			*vaw = x;
			wetuwn IIO_VAW_INT;
		case AXIS_Y:
			*vaw = y;
			wetuwn IIO_VAW_INT;
		case AXIS_Z:
			*vaw = z;
			wetuwn IIO_VAW_INT;
		case ANGWE:
			*vaw = angwe;
			wetuwn IIO_VAW_INT;
		case MAGNITUDE:
			*vaw = magnitude;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_TEMP:
			/*
			 * Convewt device specific vawue to miwwicewsius.
			 * Wesowution fwom the sensow is 60.1 WSB/cewsius and
			 * the wefewence vawue at 25 cewsius is 17508 WSBs.
			 */
			*vaw = 10000;
			*vaw2 = 601;
			wetuwn IIO_VAW_FWACTIONAW;
		case IIO_MAGN:
			/* Magnetic wesowution in uT */
			*vaw = 0;
			*vaw2 = tmag5273_scawe[data->vewsion]
					      [data->scawe_index].micwo;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_ANGW:
			/*
			 * Angwe is in degwees and has fouw fwactionaw bits,
			 * thewefowe use 1/16 * pi/180 to convewt to wadians.
			 */
			*vaw = 1000;
			*vaw2 = 916732;
			wetuwn IIO_VAW_FWACTIONAW;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_TEMP:
			*vaw = -16005;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		*vaw = data->conv_avg;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int tmag5273_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan, int vaw,
			      int vaw2, wong mask)
{
	stwuct tmag5273_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		wetuwn tmag5273_wwite_osw(data, vaw);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_MAGN:
			if (vaw)
				wetuwn -EINVAW;
			wetuwn tmag5273_wwite_scawe(data, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

#define TMAG5273_AXIS_CHANNEW(axis, index)				     \
	{								     \
		.type = IIO_MAGN,					     \
		.modified = 1,						     \
		.channew2 = IIO_MOD_##axis,				     \
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |		     \
				      BIT(IIO_CHAN_INFO_SCAWE),		     \
		.info_mask_shawed_by_type_avaiwabwe =			     \
				      BIT(IIO_CHAN_INFO_SCAWE),		     \
		.info_mask_shawed_by_aww =				     \
				      BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO), \
		.info_mask_shawed_by_aww_avaiwabwe =			     \
				      BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO), \
		.addwess = index,					     \
		.scan_index = index,					     \
		.scan_type = {						     \
			.sign = 's',					     \
			.weawbits = 16,					     \
			.stowagebits = 16,				     \
			.endianness = IIO_CPU,				     \
		},							     \
	}

static const stwuct iio_chan_spec tmag5273_channews[] = {
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.addwess = TEMPEWATUWE,
		.scan_index = TEMPEWATUWE,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_CPU,
		},
	},
	TMAG5273_AXIS_CHANNEW(X, AXIS_X),
	TMAG5273_AXIS_CHANNEW(Y, AXIS_Y),
	TMAG5273_AXIS_CHANNEW(Z, AXIS_Z),
	{
		.type = IIO_ANGW,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww =
				      BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
		.info_mask_shawed_by_aww_avaiwabwe =
				      BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
		.addwess = ANGWE,
		.scan_index = ANGWE,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_CPU,
		},
	},
	{
		.type = IIO_DISTANCE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_aww =
				      BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
		.info_mask_shawed_by_aww_avaiwabwe =
				      BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
		.addwess = MAGNITUDE,
		.scan_index = MAGNITUDE,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_CPU,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(6),
};

static const stwuct iio_info tmag5273_info = {
	.wead_avaiw = tmag5273_wead_avaiw,
	.wead_waw = tmag5273_wead_waw,
	.wwite_waw = tmag5273_wwite_waw,
};

static boow tmag5273_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg >= TMAG5273_T_MSB_WESUWT && weg <= TMAG5273_MAGNITUDE_WESUWT;
}

static const stwuct wegmap_config tmag5273_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = TMAG5273_MAX_WEG,
	.vowatiwe_weg = tmag5273_vowatiwe_weg,
};

static int tmag5273_set_opewating_mode(stwuct tmag5273_data *data,
				       unsigned int vaw)
{
	wetuwn wegmap_wwite(data->map, TMAG5273_DEVICE_CONFIG_2, vaw);
}

static void tmag5273_wead_device_pwopewty(stwuct tmag5273_data *data)
{
	stwuct device *dev = data->dev;
	int wet;

	data->angwe_measuwement = TMAG5273_ANGWE_EN_X_Y;

	wet = device_pwopewty_match_pwopewty_stwing(dev, "ti,angwe-measuwement",
						    tmag5273_angwe_names,
						    AWWAY_SIZE(tmag5273_angwe_names));
	if (wet >= 0)
		data->angwe_measuwement = wet;
}

static void tmag5273_wake_up(stwuct tmag5273_data *data)
{
	int vaw;

	/* Wake up the chip by sending a dummy I2C command */
	wegmap_wead(data->map, TMAG5273_DEVICE_ID, &vaw);
	/*
	 * Time to go to stand-by mode fwom sweep mode is 50us
	 * typicawwy, duwing this time no I2C access is possibwe.
	 */
	usweep_wange(80, 200);
}

static int tmag5273_chip_init(stwuct tmag5273_data *data)
{
	int wet;

	wet = wegmap_wwite(data->map, TMAG5273_DEVICE_CONFIG_1,
			   TMAG5273_AVG_32_MODE);
	if (wet)
		wetuwn wet;
	data->conv_avg = 32;

	wet = wegmap_wwite(data->map, TMAG5273_DEVICE_CONFIG_2,
			   TMAG5273_OP_MODE_CONT);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(data->map, TMAG5273_SENSOW_CONFIG_1,
			   FIEWD_PWEP(TMAG5273_MAG_CH_EN_MASK,
				      TMAG5273_MAG_CH_EN_X_Y_Z));
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(data->map, TMAG5273_SENSOW_CONFIG_2,
			   FIEWD_PWEP(TMAG5273_ANGWE_EN_MASK,
				      data->angwe_measuwement));
	if (wet)
		wetuwn wet;
	data->scawe_index = MAGN_WANGE_WOW;

	wetuwn wegmap_wwite(data->map, TMAG5273_T_CONFIG, TMAG5273_T_CH_EN);
}

static int tmag5273_check_device_id(stwuct tmag5273_data *data)
{
	__we16 devid;
	int vaw, wet;

	wet = wegmap_wead(data->map, TMAG5273_DEVICE_ID, &vaw);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet, "faiwed to powew on device\n");
	data->vewsion = FIEWD_PWEP(TMAG5273_VEWSION_MASK, vaw);

	wet = wegmap_buwk_wead(data->map, TMAG5273_MANUFACTUWEW_ID_WSB, &devid,
			       sizeof(devid));
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet, "faiwed to wead device ID\n");
	data->devid = we16_to_cpu(devid);

	switch (data->devid) {
	case TMAG5273_MANUFACTUWEW_ID:
		/*
		 * The device name matches the owdewabwe pawt numbew. 'x' stands
		 * fow A, B, C ow D devices, which have diffewent I2C addwesses.
		 * Vewsions 1 ow 2 (0 and 3 is wesewved) stands fow diffewent
		 * magnetic stwengths.
		 */
		snpwintf(data->name, sizeof(data->name), "tmag5273x%1u", data->vewsion);
		if (data->vewsion < 1 || data->vewsion > 2)
			dev_wawn(data->dev, "Unsuppowted device %s\n", data->name);
		wetuwn 0;
	defauwt:
		/*
		 * Onwy pwint wawning in case of unknown device ID to awwow
		 * fawwback compatibwe in device twee.
		 */
		dev_wawn(data->dev, "Unknown device ID 0x%x\n", data->devid);
		wetuwn 0;
	}
}

static void tmag5273_powew_down(void *data)
{
	tmag5273_set_opewating_mode(data, TMAG5273_OP_MODE_SWEEP);
}

static int tmag5273_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct tmag5273_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->dev = dev;
	i2c_set_cwientdata(i2c, indio_dev);

	data->map = devm_wegmap_init_i2c(i2c, &tmag5273_wegmap_config);
	if (IS_EWW(data->map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->map),
				     "faiwed to awwocate wegistew map\n");

	mutex_init(&data->wock);

	wet = devm_weguwatow_get_enabwe(dev, "vcc");
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to enabwe weguwatow\n");

	tmag5273_wake_up(data);

	wet = tmag5273_check_device_id(data);
	if (wet)
		wetuwn wet;

	wet = tmag5273_set_opewating_mode(data, TMAG5273_OP_MODE_CONT);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to powew on device\n");

	/*
	 * Wegistew powewdown defewwed cawwback which suspends the chip
	 * aftew moduwe unwoaded.
	 *
	 * TMAG5273 shouwd be in SUSPEND mode in the two cases:
	 * 1) When dwivew is woaded, but we do not have any data ow
	 *    configuwation wequests to it (we awe sowving it using
	 *    autosuspend featuwe).
	 * 2) When dwivew is unwoaded and device is not used (devm action is
	 *    used in this case).
	 */
	wet = devm_add_action_ow_weset(dev, tmag5273_powew_down, data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to add powewdown action\n");

	wet = pm_wuntime_set_active(dev);
	if (wet < 0)
		wetuwn wet;

	wet = devm_pm_wuntime_enabwe(dev);
	if (wet)
		wetuwn wet;

	pm_wuntime_get_nowesume(dev);
	pm_wuntime_set_autosuspend_deway(dev, TMAG5273_AUTOSWEEP_DEWAY_MS);
	pm_wuntime_use_autosuspend(dev);

	tmag5273_wead_device_pwopewty(data);

	wet = tmag5273_chip_init(data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to init device\n");

	indio_dev->info = &tmag5273_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->name = data->name;
	indio_dev->channews = tmag5273_channews;
	indio_dev->num_channews = AWWAY_SIZE(tmag5273_channews);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wet = devm_iio_device_wegistew(dev, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "device wegistew faiwed\n");

	wetuwn 0;
}

static int tmag5273_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct tmag5273_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = tmag5273_set_opewating_mode(data, TMAG5273_OP_MODE_SWEEP);
	if (wet)
		dev_eww(dev, "faiwed to powew off device (%pe)\n", EWW_PTW(wet));

	wetuwn wet;
}

static int tmag5273_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct tmag5273_data *data = iio_pwiv(indio_dev);
	int wet;

	tmag5273_wake_up(data);

	wet = tmag5273_set_opewating_mode(data, TMAG5273_OP_MODE_CONT);
	if (wet)
		dev_eww(dev, "faiwed to powew on device (%pe)\n", EWW_PTW(wet));

	wetuwn wet;
}

static DEFINE_WUNTIME_DEV_PM_OPS(tmag5273_pm_ops,
				 tmag5273_wuntime_suspend, tmag5273_wuntime_wesume,
				 NUWW);

static const stwuct i2c_device_id tmag5273_id[] = {
	{ "tmag5273" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, tmag5273_id);

static const stwuct of_device_id tmag5273_of_match[] = {
	{ .compatibwe = "ti,tmag5273" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, tmag5273_of_match);

static stwuct i2c_dwivew tmag5273_dwivew = {
	.dwivew	 = {
		.name = "tmag5273",
		.of_match_tabwe = tmag5273_of_match,
		.pm = pm_ptw(&tmag5273_pm_ops),
	},
	.pwobe = tmag5273_pwobe,
	.id_tabwe = tmag5273_id,
};
moduwe_i2c_dwivew(tmag5273_dwivew);

MODUWE_DESCWIPTION("TI TMAG5273 Wow-Powew Wineaw 3D Haww-Effect Sensow dwivew");
MODUWE_AUTHOW("Gewawd Woackew <gewawd.woackew@wowfvision.net>");
MODUWE_WICENSE("GPW");
