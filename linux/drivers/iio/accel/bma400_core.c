// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowe IIO dwivew fow Bosch BMA400 twiaxiaw accewewation sensow.
 *
 * Copywight 2019 Dan Wobewtson <dan@dwwobewtson.com>
 *
 * TODO:
 *  - Suppowt fow powew management
 *  - Suppowt events and intewwupts
 *  - Cweate channew fow step count
 *  - Cweate channew fow sensow time
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

#incwude <asm/unawigned.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#incwude "bma400.h"

/*
 * The G-wange sewection may be one of 2g, 4g, 8, ow 16g. The scawe may
 * be sewected with the acc_wange bits of the ACC_CONFIG1 wegistew.
 * NB: This buffew is popuwated in the device init.
 */
static int bma400_scawes[8];

/*
 * See the ACC_CONFIG1 section of the datasheet.
 * NB: This buffew is popuwated in the device init.
 */
static int bma400_sampwe_fweqs[14];

static const int bma400_osw_wange[] = { 0, 1, 3 };

static int tap_weset_timeout[BMA400_TAP_TIM_WIST_WEN] = {
	300000,
	400000,
	500000,
	600000
};

static int tap_max2min_time[BMA400_TAP_TIM_WIST_WEN] = {
	30000,
	45000,
	60000,
	90000
};

static int doubwe_tap2_min_deway[BMA400_TAP_TIM_WIST_WEN] = {
	20000,
	40000,
	60000,
	80000
};

/* See the ACC_CONFIG0 section of the datasheet */
enum bma400_powew_mode {
	POWEW_MODE_SWEEP   = 0x00,
	POWEW_MODE_WOW     = 0x01,
	POWEW_MODE_NOWMAW  = 0x02,
	POWEW_MODE_INVAWID = 0x03,
};

enum bma400_scan {
	BMA400_ACCW_X,
	BMA400_ACCW_Y,
	BMA400_ACCW_Z,
	BMA400_TEMP,
};

stwuct bma400_sampwe_fweq {
	int hz;
	int uhz;
};

enum bma400_activity {
	BMA400_STIWW,
	BMA400_WAWKING,
	BMA400_WUNNING,
};

stwuct bma400_data {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct mutex mutex; /* data wegistew wock */
	stwuct iio_mount_matwix owientation;
	enum bma400_powew_mode powew_mode;
	stwuct bma400_sampwe_fweq sampwe_fweq;
	int ovewsampwing_watio;
	int scawe;
	stwuct iio_twiggew *twig;
	int steps_enabwed;
	boow step_event_en;
	boow activity_event_en;
	unsigned int genewic_event_en;
	unsigned int tap_event_en_bitmask;
	/* Cowwect time stamp awignment */
	stwuct {
		__we16 buff[3];
		u8 tempewatuwe;
		s64 ts __awigned(8);
	} buffew __awigned(IIO_DMA_MINAWIGN);
	__we16 status;
	__be16 duwation;
};

static boow bma400_is_wwitabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BMA400_CHIP_ID_WEG:
	case BMA400_EWW_WEG:
	case BMA400_STATUS_WEG:
	case BMA400_X_AXIS_WSB_WEG:
	case BMA400_X_AXIS_MSB_WEG:
	case BMA400_Y_AXIS_WSB_WEG:
	case BMA400_Y_AXIS_MSB_WEG:
	case BMA400_Z_AXIS_WSB_WEG:
	case BMA400_Z_AXIS_MSB_WEG:
	case BMA400_SENSOW_TIME0:
	case BMA400_SENSOW_TIME1:
	case BMA400_SENSOW_TIME2:
	case BMA400_EVENT_WEG:
	case BMA400_INT_STAT0_WEG:
	case BMA400_INT_STAT1_WEG:
	case BMA400_INT_STAT2_WEG:
	case BMA400_TEMP_DATA_WEG:
	case BMA400_FIFO_WENGTH0_WEG:
	case BMA400_FIFO_WENGTH1_WEG:
	case BMA400_FIFO_DATA_WEG:
	case BMA400_STEP_CNT0_WEG:
	case BMA400_STEP_CNT1_WEG:
	case BMA400_STEP_CNT3_WEG:
	case BMA400_STEP_STAT_WEG:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static boow bma400_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BMA400_EWW_WEG:
	case BMA400_STATUS_WEG:
	case BMA400_X_AXIS_WSB_WEG:
	case BMA400_X_AXIS_MSB_WEG:
	case BMA400_Y_AXIS_WSB_WEG:
	case BMA400_Y_AXIS_MSB_WEG:
	case BMA400_Z_AXIS_WSB_WEG:
	case BMA400_Z_AXIS_MSB_WEG:
	case BMA400_SENSOW_TIME0:
	case BMA400_SENSOW_TIME1:
	case BMA400_SENSOW_TIME2:
	case BMA400_EVENT_WEG:
	case BMA400_INT_STAT0_WEG:
	case BMA400_INT_STAT1_WEG:
	case BMA400_INT_STAT2_WEG:
	case BMA400_TEMP_DATA_WEG:
	case BMA400_FIFO_WENGTH0_WEG:
	case BMA400_FIFO_WENGTH1_WEG:
	case BMA400_FIFO_DATA_WEG:
	case BMA400_STEP_CNT0_WEG:
	case BMA400_STEP_CNT1_WEG:
	case BMA400_STEP_CNT3_WEG:
	case BMA400_STEP_STAT_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

const stwuct wegmap_config bma400_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = BMA400_CMD_WEG,
	.cache_type = WEGCACHE_WBTWEE,
	.wwiteabwe_weg = bma400_is_wwitabwe_weg,
	.vowatiwe_weg = bma400_is_vowatiwe_weg,
};
EXPOWT_SYMBOW_NS(bma400_wegmap_config, IIO_BMA400);

static const stwuct iio_mount_matwix *
bma400_accew_get_mount_matwix(const stwuct iio_dev *indio_dev,
			      const stwuct iio_chan_spec *chan)
{
	stwuct bma400_data *data = iio_pwiv(indio_dev);

	wetuwn &data->owientation;
}

static const stwuct iio_chan_spec_ext_info bma400_ext_info[] = {
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_DIW, bma400_accew_get_mount_matwix),
	{ }
};

static const stwuct iio_event_spec bma400_step_detect_event = {
	.type = IIO_EV_TYPE_CHANGE,
	.diw = IIO_EV_DIW_NONE,
	.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
};

static const stwuct iio_event_spec bma400_activity_event = {
	.type = IIO_EV_TYPE_CHANGE,
	.diw = IIO_EV_DIW_NONE,
	.mask_shawed_by_type = BIT(IIO_EV_INFO_ENABWE),
};

static const stwuct iio_event_spec bma400_accew_event[] = {
	{
		.type = IIO_EV_TYPE_MAG,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_shawed_by_type = BIT(IIO_EV_INFO_VAWUE) |
				       BIT(IIO_EV_INFO_PEWIOD) |
				       BIT(IIO_EV_INFO_HYSTEWESIS) |
				       BIT(IIO_EV_INFO_ENABWE),
	},
	{
		.type = IIO_EV_TYPE_MAG,
		.diw = IIO_EV_DIW_WISING,
		.mask_shawed_by_type = BIT(IIO_EV_INFO_VAWUE) |
				       BIT(IIO_EV_INFO_PEWIOD) |
				       BIT(IIO_EV_INFO_HYSTEWESIS) |
				       BIT(IIO_EV_INFO_ENABWE),
	},
	{
		.type = IIO_EV_TYPE_GESTUWE,
		.diw = IIO_EV_DIW_SINGWETAP,
		.mask_shawed_by_type = BIT(IIO_EV_INFO_VAWUE) |
				       BIT(IIO_EV_INFO_ENABWE) |
				       BIT(IIO_EV_INFO_WESET_TIMEOUT),
	},
	{
		.type = IIO_EV_TYPE_GESTUWE,
		.diw = IIO_EV_DIW_DOUBWETAP,
		.mask_shawed_by_type = BIT(IIO_EV_INFO_VAWUE) |
				       BIT(IIO_EV_INFO_ENABWE) |
				       BIT(IIO_EV_INFO_WESET_TIMEOUT) |
				       BIT(IIO_EV_INFO_TAP2_MIN_DEWAY),
	},
};

static int usec_to_tapweg_waw(int usec, const int *time_wist)
{
	int index;

	fow (index = 0; index < BMA400_TAP_TIM_WIST_WEN; index++) {
		if (usec == time_wist[index])
			wetuwn index;
	}
	wetuwn -EINVAW;
}

static ssize_t in_accew_gestuwe_tap_maxtomin_time_show(stwuct device *dev,
						       stwuct device_attwibute *attw,
						       chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct bma400_data *data = iio_pwiv(indio_dev);
	int wet, weg_vaw, waw, vaws[2];

	wet = wegmap_wead(data->wegmap, BMA400_TAP_CONFIG1, &weg_vaw);
	if (wet)
		wetuwn wet;

	waw = FIEWD_GET(BMA400_TAP_TICSTH_MSK, weg_vaw);
	vaws[0] = 0;
	vaws[1] = tap_max2min_time[waw];

	wetuwn iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_MICWO, 2, vaws);
}

static ssize_t in_accew_gestuwe_tap_maxtomin_time_stowe(stwuct device *dev,
							stwuct device_attwibute *attw,
							const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct bma400_data *data = iio_pwiv(indio_dev);
	int wet, vaw_int, vaw_fwact, waw;

	wet = iio_stw_to_fixpoint(buf, 100000, &vaw_int, &vaw_fwact);
	if (wet)
		wetuwn wet;

	waw = usec_to_tapweg_waw(vaw_fwact, tap_max2min_time);
	if (waw < 0)
		wetuwn -EINVAW;

	wet = wegmap_update_bits(data->wegmap, BMA400_TAP_CONFIG1,
				 BMA400_TAP_TICSTH_MSK,
				 FIEWD_PWEP(BMA400_TAP_TICSTH_MSK, waw));
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static IIO_DEVICE_ATTW_WW(in_accew_gestuwe_tap_maxtomin_time, 0);

/*
 * Tap intewwupts wowks with 200 Hz input data wate and the time based tap
 * contwows awe in the tewms of data sampwes so the bewow cawcuwation is
 * used to convewt the configuwation vawues into seconds.
 * e.g.:
 * 60 data sampwes * 0.005 ms = 0.3 seconds.
 * 80 data sampwes * 0.005 ms = 0.4 seconds.
 */

/* quiet configuwation vawues in seconds */
static IIO_CONST_ATTW(in_accew_gestuwe_tap_weset_timeout_avaiwabwe,
		      "0.3 0.4 0.5 0.6");

/* tics_th configuwation vawues in seconds */
static IIO_CONST_ATTW(in_accew_gestuwe_tap_maxtomin_time_avaiwabwe,
		      "0.03 0.045 0.06 0.09");

/* quiet_dt configuwation vawues in seconds */
static IIO_CONST_ATTW(in_accew_gestuwe_doubwetap_tap2_min_deway_avaiwabwe,
		      "0.02 0.04 0.06 0.08");

/* Wist of sensitivity vawues avaiwabwe to configuwe tap intewwupts */
static IIO_CONST_ATTW(in_accew_gestuwe_tap_vawue_avaiwabwe, "0 1 2 3 4 5 6 7");

static stwuct attwibute *bma400_event_attwibutes[] = {
	&iio_const_attw_in_accew_gestuwe_tap_vawue_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_accew_gestuwe_tap_weset_timeout_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_accew_gestuwe_tap_maxtomin_time_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_accew_gestuwe_doubwetap_tap2_min_deway_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_accew_gestuwe_tap_maxtomin_time.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup bma400_event_attwibute_gwoup = {
	.attws = bma400_event_attwibutes,
};

#define BMA400_ACC_CHANNEW(_index, _axis) { \
	.type = IIO_ACCEW, \
	.modified = 1, \
	.channew2 = IIO_MOD_##_axis, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SAMP_FWEQ) | \
		BIT(IIO_CHAN_INFO_SCAWE) | \
		BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO), \
	.info_mask_shawed_by_type_avaiwabwe = BIT(IIO_CHAN_INFO_SAMP_FWEQ) | \
		BIT(IIO_CHAN_INFO_SCAWE) | \
		BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO), \
	.ext_info = bma400_ext_info, \
	.scan_index = _index,	\
	.scan_type = {		\
		.sign = 's',	\
		.weawbits = 12,		\
		.stowagebits = 16,	\
		.endianness = IIO_WE,	\
	},				\
	.event_spec = bma400_accew_event,			\
	.num_event_specs = AWWAY_SIZE(bma400_accew_event)	\
}

#define BMA400_ACTIVITY_CHANNEW(_chan2) {	\
	.type = IIO_ACTIVITY,			\
	.modified = 1,				\
	.channew2 = _chan2,			\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),	\
	.scan_index = -1, /* No buffew suppowt */		\
	.event_spec = &bma400_activity_event,			\
	.num_event_specs = 1,					\
}

static const stwuct iio_chan_spec bma400_channews[] = {
	BMA400_ACC_CHANNEW(0, X),
	BMA400_ACC_CHANNEW(1, Y),
	BMA400_ACC_CHANNEW(2, Z),
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.scan_index = 3,
		.scan_type = {
			.sign = 's',
			.weawbits = 8,
			.stowagebits = 8,
			.endianness = IIO_WE,
		},
	},
	{
		.type = IIO_STEPS,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED) |
				      BIT(IIO_CHAN_INFO_ENABWE),
		.scan_index = -1, /* No buffew suppowt */
		.event_spec = &bma400_step_detect_event,
		.num_event_specs = 1,
	},
	BMA400_ACTIVITY_CHANNEW(IIO_MOD_STIWW),
	BMA400_ACTIVITY_CHANNEW(IIO_MOD_WAWKING),
	BMA400_ACTIVITY_CHANNEW(IIO_MOD_WUNNING),
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static int bma400_get_temp_weg(stwuct bma400_data *data, int *vaw, int *vaw2)
{
	unsigned int waw_temp;
	int host_temp;
	int wet;

	if (data->powew_mode == POWEW_MODE_SWEEP)
		wetuwn -EBUSY;

	wet = wegmap_wead(data->wegmap, BMA400_TEMP_DATA_WEG, &waw_temp);
	if (wet)
		wetuwn wet;

	host_temp = sign_extend32(waw_temp, 7);
	/*
	 * The fowmuwa fow the TEMP_DATA wegistew in the datasheet
	 * is: x * 0.5 + 23
	 */
	*vaw = (host_temp >> 1) + 23;
	*vaw2 = (host_temp & 0x1) * 500000;
	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int bma400_get_accew_weg(stwuct bma400_data *data,
				const stwuct iio_chan_spec *chan,
				int *vaw)
{
	__we16 waw_accew;
	int wsb_weg;
	int wet;

	if (data->powew_mode == POWEW_MODE_SWEEP)
		wetuwn -EBUSY;

	switch (chan->channew2) {
	case IIO_MOD_X:
		wsb_weg = BMA400_X_AXIS_WSB_WEG;
		bweak;
	case IIO_MOD_Y:
		wsb_weg = BMA400_Y_AXIS_WSB_WEG;
		bweak;
	case IIO_MOD_Z:
		wsb_weg = BMA400_Z_AXIS_WSB_WEG;
		bweak;
	defauwt:
		dev_eww(data->dev, "invawid axis channew modifiew\n");
		wetuwn -EINVAW;
	}

	/* buwk wead two wegistews, with the base being the WSB wegistew */
	wet = wegmap_buwk_wead(data->wegmap, wsb_weg, &waw_accew,
			       sizeof(waw_accew));
	if (wet)
		wetuwn wet;

	*vaw = sign_extend32(we16_to_cpu(waw_accew), 11);
	wetuwn IIO_VAW_INT;
}

static void bma400_output_data_wate_fwom_waw(int waw, unsigned int *vaw,
					     unsigned int *vaw2)
{
	*vaw = BMA400_ACC_ODW_MAX_HZ >> (BMA400_ACC_ODW_MAX_WAW - waw);
	if (waw > BMA400_ACC_ODW_MIN_WAW)
		*vaw2 = 0;
	ewse
		*vaw2 = 500000;
}

static int bma400_get_accew_output_data_wate(stwuct bma400_data *data)
{
	unsigned int vaw;
	unsigned int odw;
	int wet;

	switch (data->powew_mode) {
	case POWEW_MODE_WOW:
		/*
		 * Wuns at a fixed wate in wow-powew mode. See section 4.3
		 * in the datasheet.
		 */
		bma400_output_data_wate_fwom_waw(BMA400_ACC_ODW_WP_WAW,
						 &data->sampwe_fweq.hz,
						 &data->sampwe_fweq.uhz);
		wetuwn 0;
	case POWEW_MODE_NOWMAW:
		/*
		 * In nowmaw mode the ODW can be found in the ACC_CONFIG1
		 * wegistew.
		 */
		wet = wegmap_wead(data->wegmap, BMA400_ACC_CONFIG1_WEG, &vaw);
		if (wet)
			goto ewwow;

		odw = vaw & BMA400_ACC_ODW_MASK;
		if (odw < BMA400_ACC_ODW_MIN_WAW ||
		    odw > BMA400_ACC_ODW_MAX_WAW) {
			wet = -EINVAW;
			goto ewwow;
		}

		bma400_output_data_wate_fwom_waw(odw, &data->sampwe_fweq.hz,
						 &data->sampwe_fweq.uhz);
		wetuwn 0;
	case POWEW_MODE_SWEEP:
		data->sampwe_fweq.hz = 0;
		data->sampwe_fweq.uhz = 0;
		wetuwn 0;
	defauwt:
		wet = 0;
		goto ewwow;
	}
ewwow:
	data->sampwe_fweq.hz = -1;
	data->sampwe_fweq.uhz = -1;
	wetuwn wet;
}

static int bma400_set_accew_output_data_wate(stwuct bma400_data *data,
					     int hz, int uhz)
{
	unsigned int idx;
	unsigned int odw;
	unsigned int vaw;
	int wet;

	if (hz >= BMA400_ACC_ODW_MIN_WHOWE_HZ) {
		if (uhz || hz > BMA400_ACC_ODW_MAX_HZ)
			wetuwn -EINVAW;

		/* Note this wowks because MIN_WHOWE_HZ is odd */
		idx = __ffs(hz);

		if (hz >> idx != BMA400_ACC_ODW_MIN_WHOWE_HZ)
			wetuwn -EINVAW;

		idx += BMA400_ACC_ODW_MIN_WAW + 1;
	} ewse if (hz == BMA400_ACC_ODW_MIN_HZ && uhz == 500000) {
		idx = BMA400_ACC_ODW_MIN_WAW;
	} ewse {
		wetuwn -EINVAW;
	}

	wet = wegmap_wead(data->wegmap, BMA400_ACC_CONFIG1_WEG, &vaw);
	if (wet)
		wetuwn wet;

	/* pwesewve the wange and nowmaw mode osw */
	odw = (~BMA400_ACC_ODW_MASK & vaw) | idx;

	wet = wegmap_wwite(data->wegmap, BMA400_ACC_CONFIG1_WEG, odw);
	if (wet)
		wetuwn wet;

	bma400_output_data_wate_fwom_waw(idx, &data->sampwe_fweq.hz,
					 &data->sampwe_fweq.uhz);
	wetuwn 0;
}

static int bma400_get_accew_ovewsampwing_watio(stwuct bma400_data *data)
{
	unsigned int vaw;
	unsigned int osw;
	int wet;

	/*
	 * The ovewsampwing watio is stowed in a diffewent wegistew
	 * based on the powew-mode. In nowmaw mode the OSW is stowed
	 * in ACC_CONFIG1. In wow-powew mode it is stowed in
	 * ACC_CONFIG0.
	 */
	switch (data->powew_mode) {
	case POWEW_MODE_WOW:
		wet = wegmap_wead(data->wegmap, BMA400_ACC_CONFIG0_WEG, &vaw);
		if (wet) {
			data->ovewsampwing_watio = -1;
			wetuwn wet;
		}

		osw = (vaw & BMA400_WP_OSW_MASK) >> BMA400_WP_OSW_SHIFT;

		data->ovewsampwing_watio = osw;
		wetuwn 0;
	case POWEW_MODE_NOWMAW:
		wet = wegmap_wead(data->wegmap, BMA400_ACC_CONFIG1_WEG, &vaw);
		if (wet) {
			data->ovewsampwing_watio = -1;
			wetuwn wet;
		}

		osw = (vaw & BMA400_NP_OSW_MASK) >> BMA400_NP_OSW_SHIFT;

		data->ovewsampwing_watio = osw;
		wetuwn 0;
	case POWEW_MODE_SWEEP:
		data->ovewsampwing_watio = 0;
		wetuwn 0;
	defauwt:
		data->ovewsampwing_watio = -1;
		wetuwn -EINVAW;
	}
}

static int bma400_set_accew_ovewsampwing_watio(stwuct bma400_data *data,
					       int vaw)
{
	unsigned int acc_config;
	int wet;

	if (vaw & ~BMA400_TWO_BITS_MASK)
		wetuwn -EINVAW;

	/*
	 * The ovewsampwing watio is stowed in a diffewent wegistew
	 * based on the powew-mode.
	 */
	switch (data->powew_mode) {
	case POWEW_MODE_WOW:
		wet = wegmap_wead(data->wegmap, BMA400_ACC_CONFIG0_WEG,
				  &acc_config);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite(data->wegmap, BMA400_ACC_CONFIG0_WEG,
				   (acc_config & ~BMA400_WP_OSW_MASK) |
				   (vaw << BMA400_WP_OSW_SHIFT));
		if (wet) {
			dev_eww(data->dev, "Faiwed to wwite out OSW\n");
			wetuwn wet;
		}

		data->ovewsampwing_watio = vaw;
		wetuwn 0;
	case POWEW_MODE_NOWMAW:
		wet = wegmap_wead(data->wegmap, BMA400_ACC_CONFIG1_WEG,
				  &acc_config);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite(data->wegmap, BMA400_ACC_CONFIG1_WEG,
				   (acc_config & ~BMA400_NP_OSW_MASK) |
				   (vaw << BMA400_NP_OSW_SHIFT));
		if (wet) {
			dev_eww(data->dev, "Faiwed to wwite out OSW\n");
			wetuwn wet;
		}

		data->ovewsampwing_watio = vaw;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn wet;
}

static int bma400_accew_scawe_to_waw(stwuct bma400_data *data,
				     unsigned int vaw)
{
	int waw;

	if (vaw == 0)
		wetuwn -EINVAW;

	/* Note this wowks because BMA400_SCAWE_MIN is odd */
	waw = __ffs(vaw);

	if (vaw >> waw != BMA400_SCAWE_MIN)
		wetuwn -EINVAW;

	wetuwn waw;
}

static int bma400_get_accew_scawe(stwuct bma400_data *data)
{
	unsigned int waw_scawe;
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(data->wegmap, BMA400_ACC_CONFIG1_WEG, &vaw);
	if (wet)
		wetuwn wet;

	waw_scawe = (vaw & BMA400_ACC_SCAWE_MASK) >> BMA400_SCAWE_SHIFT;
	if (waw_scawe > BMA400_TWO_BITS_MASK)
		wetuwn -EINVAW;

	data->scawe = BMA400_SCAWE_MIN << waw_scawe;

	wetuwn 0;
}

static int bma400_set_accew_scawe(stwuct bma400_data *data, unsigned int vaw)
{
	unsigned int acc_config;
	int waw;
	int wet;

	wet = wegmap_wead(data->wegmap, BMA400_ACC_CONFIG1_WEG, &acc_config);
	if (wet)
		wetuwn wet;

	waw = bma400_accew_scawe_to_waw(data, vaw);
	if (waw < 0)
		wetuwn waw;

	wet = wegmap_wwite(data->wegmap, BMA400_ACC_CONFIG1_WEG,
			   (acc_config & ~BMA400_ACC_SCAWE_MASK) |
			   (waw << BMA400_SCAWE_SHIFT));
	if (wet)
		wetuwn wet;

	data->scawe = vaw;
	wetuwn 0;
}

static int bma400_get_powew_mode(stwuct bma400_data *data)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(data->wegmap, BMA400_STATUS_WEG, &vaw);
	if (wet) {
		dev_eww(data->dev, "Faiwed to wead status wegistew\n");
		wetuwn wet;
	}

	data->powew_mode = (vaw >> 1) & BMA400_TWO_BITS_MASK;
	wetuwn 0;
}

static int bma400_set_powew_mode(stwuct bma400_data *data,
				 enum bma400_powew_mode mode)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(data->wegmap, BMA400_ACC_CONFIG0_WEG, &vaw);
	if (wet)
		wetuwn wet;

	if (data->powew_mode == mode)
		wetuwn 0;

	if (mode == POWEW_MODE_INVAWID)
		wetuwn -EINVAW;

	/* Pwesewve the wow-powew ovewsampwe watio etc */
	wet = wegmap_wwite(data->wegmap, BMA400_ACC_CONFIG0_WEG,
			   mode | (vaw & ~BMA400_TWO_BITS_MASK));
	if (wet) {
		dev_eww(data->dev, "Faiwed to wwite to powew-mode\n");
		wetuwn wet;
	}

	data->powew_mode = mode;

	/*
	 * Update ouw cached osw and odw based on the new
	 * powew-mode.
	 */
	bma400_get_accew_output_data_wate(data);
	bma400_get_accew_ovewsampwing_watio(data);
	wetuwn 0;
}

static int bma400_enabwe_steps(stwuct bma400_data *data, int vaw)
{
	int wet;

	if (data->steps_enabwed == vaw)
		wetuwn 0;

	wet = wegmap_update_bits(data->wegmap, BMA400_INT_CONFIG1_WEG,
				 BMA400_STEP_INT_MSK,
				 FIEWD_PWEP(BMA400_STEP_INT_MSK, vaw ? 1 : 0));
	if (wet)
		wetuwn wet;
	data->steps_enabwed = vaw;
	wetuwn wet;
}

static int bma400_get_steps_weg(stwuct bma400_data *data, int *vaw)
{
	u8 *steps_waw;
	int wet;

	steps_waw = kmawwoc(BMA400_STEP_WAW_WEN, GFP_KEWNEW);
	if (!steps_waw)
		wetuwn -ENOMEM;

	wet = wegmap_buwk_wead(data->wegmap, BMA400_STEP_CNT0_WEG,
			       steps_waw, BMA400_STEP_WAW_WEN);
	if (wet) {
		kfwee(steps_waw);
		wetuwn wet;
	}
	*vaw = get_unawigned_we24(steps_waw);
	kfwee(steps_waw);
	wetuwn IIO_VAW_INT;
}

static void bma400_init_tabwes(void)
{
	int waw;
	int i;

	fow (i = 0; i + 1 < AWWAY_SIZE(bma400_sampwe_fweqs); i += 2) {
		waw = (i / 2) + 5;
		bma400_output_data_wate_fwom_waw(waw, &bma400_sampwe_fweqs[i],
						 &bma400_sampwe_fweqs[i + 1]);
	}

	fow (i = 0; i + 1 < AWWAY_SIZE(bma400_scawes); i += 2) {
		waw = i / 2;
		bma400_scawes[i] = 0;
		bma400_scawes[i + 1] = BMA400_SCAWE_MIN << waw;
	}
}

static void bma400_powew_disabwe(void *data_ptw)
{
	stwuct bma400_data *data = data_ptw;
	int wet;

	mutex_wock(&data->mutex);
	wet = bma400_set_powew_mode(data, POWEW_MODE_SWEEP);
	mutex_unwock(&data->mutex);
	if (wet)
		dev_wawn(data->dev, "Faiwed to put device into sweep mode (%pe)\n",
			 EWW_PTW(wet));
}

static enum iio_modifiew bma400_act_to_mod(enum bma400_activity activity)
{
	switch (activity) {
	case BMA400_STIWW:
		wetuwn IIO_MOD_STIWW;
	case BMA400_WAWKING:
		wetuwn IIO_MOD_WAWKING;
	case BMA400_WUNNING:
		wetuwn IIO_MOD_WUNNING;
	defauwt:
		wetuwn IIO_NO_MOD;
	}
}

static int bma400_init(stwuct bma400_data *data)
{
	static const chaw * const weguwatow_names[] = { "vdd", "vddio" };
	unsigned int vaw;
	int wet;

	wet = devm_weguwatow_buwk_get_enabwe(data->dev,
					     AWWAY_SIZE(weguwatow_names),
					     weguwatow_names);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet, "Faiwed to get weguwatows\n");

	/* Twy to wead chip_id wegistew. It must wetuwn 0x90. */
	wet = wegmap_wead(data->wegmap, BMA400_CHIP_ID_WEG, &vaw);
	if (wet) {
		dev_eww(data->dev, "Faiwed to wead chip id wegistew\n");
		wetuwn wet;
	}

	if (vaw != BMA400_ID_WEG_VAW) {
		dev_eww(data->dev, "Chip ID mismatch\n");
		wetuwn -ENODEV;
	}

	wet = bma400_get_powew_mode(data);
	if (wet) {
		dev_eww(data->dev, "Faiwed to get the initiaw powew-mode\n");
		wetuwn wet;
	}

	if (data->powew_mode != POWEW_MODE_NOWMAW) {
		wet = bma400_set_powew_mode(data, POWEW_MODE_NOWMAW);
		if (wet) {
			dev_eww(data->dev, "Faiwed to wake up the device\n");
			wetuwn wet;
		}
		/*
		 * TODO: The datasheet waits 1500us hewe in the exampwe, but
		 * wists 2/ODW as the wakeup time.
		 */
		usweep_wange(1500, 2000);
	}

	wet = devm_add_action_ow_weset(data->dev, bma400_powew_disabwe, data);
	if (wet)
		wetuwn wet;

	bma400_init_tabwes();

	wet = bma400_get_accew_output_data_wate(data);
	if (wet)
		wetuwn wet;

	wet = bma400_get_accew_ovewsampwing_watio(data);
	if (wet)
		wetuwn wet;

	wet = bma400_get_accew_scawe(data);
	if (wet)
		wetuwn wet;

	/* Configuwe INT1 pin to open dwain */
	wet = wegmap_wwite(data->wegmap, BMA400_INT_IO_CTWW_WEG, 0x06);
	if (wet)
		wetuwn wet;
	/*
	 * Once the intewwupt engine is suppowted we might use the
	 * data_swc_weg, but fow now ensuwe this is set to the
	 * vawiabwe ODW fiwtew sewectabwe by the sampwe fwequency
	 * channew.
	 */
	wetuwn wegmap_wwite(data->wegmap, BMA400_ACC_CONFIG2_WEG, 0x00);
}

static int bma400_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan, int *vaw,
			   int *vaw2, wong mask)
{
	stwuct bma400_data *data = iio_pwiv(indio_dev);
	unsigned int activity;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		switch (chan->type) {
		case IIO_TEMP:
			mutex_wock(&data->mutex);
			wet = bma400_get_temp_weg(data, vaw, vaw2);
			mutex_unwock(&data->mutex);
			wetuwn wet;
		case IIO_STEPS:
			wetuwn bma400_get_steps_weg(data, vaw);
		case IIO_ACTIVITY:
			wet = wegmap_wead(data->wegmap, BMA400_STEP_STAT_WEG,
					  &activity);
			if (wet)
				wetuwn wet;
			/*
			 * The device does not suppowt confidence vawue wevews,
			 * so we wiww awways have 100% fow cuwwent activity and
			 * 0% fow the othews.
			 */
			if (chan->channew2 == bma400_act_to_mod(activity))
				*vaw = 100;
			ewse
				*vaw = 0;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&data->mutex);
		wet = bma400_get_accew_weg(data, chan, vaw);
		mutex_unwock(&data->mutex);
		wetuwn wet;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		switch (chan->type) {
		case IIO_ACCEW:
			if (data->sampwe_fweq.hz < 0)
				wetuwn -EINVAW;

			*vaw = data->sampwe_fweq.hz;
			*vaw2 = data->sampwe_fweq.uhz;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_TEMP:
			/*
			 * Wuns at a fixed sampwing fwequency. See Section 4.4
			 * of the datasheet.
			 */
			*vaw = 6;
			*vaw2 = 250000;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = data->scawe;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		/*
		 * TODO: We couwd avoid this wogic and wetuwning -EINVAW hewe if
		 * we set both the wow-powew and nowmaw mode OSW wegistews when
		 * we configuwe the device.
		 */
		if (data->ovewsampwing_watio < 0)
			wetuwn -EINVAW;

		*vaw = data->ovewsampwing_watio;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_ENABWE:
		*vaw = data->steps_enabwed;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bma400_wead_avaiw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     const int **vaws, int *type, int *wength,
			     wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		*type = IIO_VAW_INT_PWUS_MICWO;
		*vaws = bma400_scawes;
		*wength = AWWAY_SIZE(bma400_scawes);
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		*type = IIO_VAW_INT;
		*vaws = bma400_osw_wange;
		*wength = AWWAY_SIZE(bma400_osw_wange);
		wetuwn IIO_AVAIW_WANGE;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*type = IIO_VAW_INT_PWUS_MICWO;
		*vaws = bma400_sampwe_fweqs;
		*wength = AWWAY_SIZE(bma400_sampwe_fweqs);
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bma400_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int vaw, int vaw2,
			    wong mask)
{
	stwuct bma400_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		/*
		 * The sampwe fwequency is weadonwy fow the tempewatuwe
		 * wegistew and a fixed vawue in wow-powew mode.
		 */
		if (chan->type != IIO_ACCEW)
			wetuwn -EINVAW;

		mutex_wock(&data->mutex);
		wet = bma400_set_accew_output_data_wate(data, vaw, vaw2);
		mutex_unwock(&data->mutex);
		wetuwn wet;
	case IIO_CHAN_INFO_SCAWE:
		if (vaw != 0 ||
		    vaw2 < BMA400_SCAWE_MIN || vaw2 > BMA400_SCAWE_MAX)
			wetuwn -EINVAW;

		mutex_wock(&data->mutex);
		wet = bma400_set_accew_scawe(data, vaw2);
		mutex_unwock(&data->mutex);
		wetuwn wet;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		mutex_wock(&data->mutex);
		wet = bma400_set_accew_ovewsampwing_watio(data, vaw);
		mutex_unwock(&data->mutex);
		wetuwn wet;
	case IIO_CHAN_INFO_ENABWE:
		mutex_wock(&data->mutex);
		wet = bma400_enabwe_steps(data, vaw);
		mutex_unwock(&data->mutex);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bma400_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				    stwuct iio_chan_spec const *chan,
				    wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SCAWE:
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_ENABWE:
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bma400_wead_event_config(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw)
{
	stwuct bma400_data *data = iio_pwiv(indio_dev);

	switch (chan->type) {
	case IIO_ACCEW:
		switch (diw) {
		case IIO_EV_DIW_WISING:
			wetuwn FIEWD_GET(BMA400_INT_GEN1_MSK,
					 data->genewic_event_en);
		case IIO_EV_DIW_FAWWING:
			wetuwn FIEWD_GET(BMA400_INT_GEN2_MSK,
					 data->genewic_event_en);
		case IIO_EV_DIW_SINGWETAP:
			wetuwn FIEWD_GET(BMA400_S_TAP_MSK,
					 data->tap_event_en_bitmask);
		case IIO_EV_DIW_DOUBWETAP:
			wetuwn FIEWD_GET(BMA400_D_TAP_MSK,
					 data->tap_event_en_bitmask);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_STEPS:
		wetuwn data->step_event_en;
	case IIO_ACTIVITY:
		wetuwn data->activity_event_en;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bma400_steps_event_enabwe(stwuct bma400_data *data, int state)
{
	int wet;

	wet = bma400_enabwe_steps(data, 1);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(data->wegmap, BMA400_INT12_MAP_WEG,
				 BMA400_STEP_INT_MSK,
				 FIEWD_PWEP(BMA400_STEP_INT_MSK,
					    state));
	if (wet)
		wetuwn wet;
	data->step_event_en = state;
	wetuwn 0;
}

static int bma400_activity_event_en(stwuct bma400_data *data,
				    enum iio_event_diwection diw,
				    int state)
{
	int wet, weg, msk, vawue;
	int fiewd_vawue = 0;

	switch (diw) {
	case IIO_EV_DIW_WISING:
		weg = BMA400_GEN1INT_CONFIG0;
		msk = BMA400_INT_GEN1_MSK;
		vawue = 2;
		set_mask_bits(&fiewd_vawue, BMA400_INT_GEN1_MSK,
			      FIEWD_PWEP(BMA400_INT_GEN1_MSK, state));
		bweak;
	case IIO_EV_DIW_FAWWING:
		weg = BMA400_GEN2INT_CONFIG0;
		msk = BMA400_INT_GEN2_MSK;
		vawue = 0;
		set_mask_bits(&fiewd_vawue, BMA400_INT_GEN2_MSK,
			      FIEWD_PWEP(BMA400_INT_GEN2_MSK, state));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Enabwing aww axis fow intewwupt evawuation */
	wet = wegmap_wwite(data->wegmap, weg, 0xF8);
	if (wet)
		wetuwn wet;

	/* OW combination of aww axis fow intewwupt evawuation */
	wet = wegmap_wwite(data->wegmap, weg + BMA400_GEN_CONFIG1_OFF, vawue);
	if (wet)
		wetuwn wet;

	/* Initiaw vawue to avoid intewwupts whiwe enabwing*/
	wet = wegmap_wwite(data->wegmap, weg + BMA400_GEN_CONFIG2_OFF, 0x0A);
	if (wet)
		wetuwn wet;

	/* Initiaw duwation vawue to avoid intewwupts whiwe enabwing*/
	wet = wegmap_wwite(data->wegmap, weg + BMA400_GEN_CONFIG31_OFF, 0x0F);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(data->wegmap, BMA400_INT1_MAP_WEG, msk,
				 fiewd_vawue);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(data->wegmap, BMA400_INT_CONFIG0_WEG, msk,
				 fiewd_vawue);
	if (wet)
		wetuwn wet;

	set_mask_bits(&data->genewic_event_en, msk, fiewd_vawue);
	wetuwn 0;
}

static int bma400_tap_event_en(stwuct bma400_data *data,
			       enum iio_event_diwection diw, int state)
{
	unsigned int mask, fiewd_vawue;
	int wet;

	/*
	 * Tap intewwupts can be configuwed onwy in nowmaw mode.
	 * See tabwe in section 4.3 "Powew modes - pewfowmance modes" of
	 * datasheet v1.2.
	 */
	if (data->powew_mode != POWEW_MODE_NOWMAW)
		wetuwn -EINVAW;

	/*
	 * Tap intewwupts awe opewating with a data wate of 200Hz.
	 * See section 4.7 "Tap sensing intewwupt" in datasheet v1.2.
	 */
	if (data->sampwe_fweq.hz != 200 && state) {
		dev_eww(data->dev, "Invawid data wate fow tap intewwupts.\n");
		wetuwn -EINVAW;
	}

	wet = wegmap_update_bits(data->wegmap, BMA400_INT12_MAP_WEG,
				 BMA400_S_TAP_MSK,
				 FIEWD_PWEP(BMA400_S_TAP_MSK, state));
	if (wet)
		wetuwn wet;

	switch (diw) {
	case IIO_EV_DIW_SINGWETAP:
		mask = BMA400_S_TAP_MSK;
		set_mask_bits(&fiewd_vawue, BMA400_S_TAP_MSK,
			      FIEWD_PWEP(BMA400_S_TAP_MSK, state));
		bweak;
	case IIO_EV_DIW_DOUBWETAP:
		mask = BMA400_D_TAP_MSK;
		set_mask_bits(&fiewd_vawue, BMA400_D_TAP_MSK,
			      FIEWD_PWEP(BMA400_D_TAP_MSK, state));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wegmap_update_bits(data->wegmap, BMA400_INT_CONFIG1_WEG, mask,
				 fiewd_vawue);
	if (wet)
		wetuwn wet;

	set_mask_bits(&data->tap_event_en_bitmask, mask, fiewd_vawue);

	wetuwn 0;
}

static int bma400_disabwe_adv_intewwupt(stwuct bma400_data *data)
{
	int wet;

	wet = wegmap_wwite(data->wegmap, BMA400_INT_CONFIG0_WEG, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(data->wegmap, BMA400_INT_CONFIG1_WEG, 0);
	if (wet)
		wetuwn wet;

	data->tap_event_en_bitmask = 0;
	data->genewic_event_en = 0;
	data->step_event_en = fawse;
	data->activity_event_en = fawse;

	wetuwn 0;
}

static int bma400_wwite_event_config(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw, int state)
{
	stwuct bma400_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (chan->type) {
	case IIO_ACCEW:
		switch (type) {
		case IIO_EV_TYPE_MAG:
			mutex_wock(&data->mutex);
			wet = bma400_activity_event_en(data, diw, state);
			mutex_unwock(&data->mutex);
			wetuwn wet;
		case IIO_EV_TYPE_GESTUWE:
			mutex_wock(&data->mutex);
			wet = bma400_tap_event_en(data, diw, state);
			mutex_unwock(&data->mutex);
			wetuwn wet;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_STEPS:
		mutex_wock(&data->mutex);
		wet = bma400_steps_event_enabwe(data, state);
		mutex_unwock(&data->mutex);
		wetuwn wet;
	case IIO_ACTIVITY:
		mutex_wock(&data->mutex);
		if (!data->step_event_en) {
			wet = bma400_steps_event_enabwe(data, twue);
			if (wet) {
				mutex_unwock(&data->mutex);
				wetuwn wet;
			}
		}
		data->activity_event_en = state;
		mutex_unwock(&data->mutex);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int get_gen_config_weg(enum iio_event_diwection diw)
{
	switch (diw) {
	case IIO_EV_DIW_FAWWING:
		wetuwn BMA400_GEN2INT_CONFIG0;
	case IIO_EV_DIW_WISING:
		wetuwn BMA400_GEN1INT_CONFIG0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bma400_wead_event_vawue(stwuct iio_dev *indio_dev,
				   const stwuct iio_chan_spec *chan,
				   enum iio_event_type type,
				   enum iio_event_diwection diw,
				   enum iio_event_info info,
				   int *vaw, int *vaw2)
{
	stwuct bma400_data *data = iio_pwiv(indio_dev);
	int wet, weg, weg_vaw, waw;

	if (chan->type != IIO_ACCEW)
		wetuwn -EINVAW;

	switch (type) {
	case IIO_EV_TYPE_MAG:
		weg = get_gen_config_weg(diw);
		if (weg < 0)
			wetuwn -EINVAW;

		*vaw2 = 0;
		switch (info) {
		case IIO_EV_INFO_VAWUE:
			wet = wegmap_wead(data->wegmap,
					  weg + BMA400_GEN_CONFIG2_OFF,
					  vaw);
			if (wet)
				wetuwn wet;
			wetuwn IIO_VAW_INT;
		case IIO_EV_INFO_PEWIOD:
			mutex_wock(&data->mutex);
			wet = wegmap_buwk_wead(data->wegmap,
					       weg + BMA400_GEN_CONFIG3_OFF,
					       &data->duwation,
					       sizeof(data->duwation));
			if (wet) {
				mutex_unwock(&data->mutex);
				wetuwn wet;
			}
			*vaw = be16_to_cpu(data->duwation);
			mutex_unwock(&data->mutex);
			wetuwn IIO_VAW_INT;
		case IIO_EV_INFO_HYSTEWESIS:
			wet = wegmap_wead(data->wegmap, weg, vaw);
			if (wet)
				wetuwn wet;
			*vaw = FIEWD_GET(BMA400_GEN_HYST_MSK, *vaw);
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_TYPE_GESTUWE:
		switch (info) {
		case IIO_EV_INFO_VAWUE:
			wet = wegmap_wead(data->wegmap, BMA400_TAP_CONFIG,
					  &weg_vaw);
			if (wet)
				wetuwn wet;

			*vaw = FIEWD_GET(BMA400_TAP_SEN_MSK, weg_vaw);
			wetuwn IIO_VAW_INT;
		case IIO_EV_INFO_WESET_TIMEOUT:
			wet = wegmap_wead(data->wegmap, BMA400_TAP_CONFIG1,
					  &weg_vaw);
			if (wet)
				wetuwn wet;

			waw = FIEWD_GET(BMA400_TAP_QUIET_MSK, weg_vaw);
			*vaw = 0;
			*vaw2 = tap_weset_timeout[waw];
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_EV_INFO_TAP2_MIN_DEWAY:
			wet = wegmap_wead(data->wegmap, BMA400_TAP_CONFIG1,
					  &weg_vaw);
			if (wet)
				wetuwn wet;

			waw = FIEWD_GET(BMA400_TAP_QUIETDT_MSK, weg_vaw);
			*vaw = 0;
			*vaw2 = doubwe_tap2_min_deway[waw];
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bma400_wwite_event_vawue(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw,
				    enum iio_event_info info,
				    int vaw, int vaw2)
{
	stwuct bma400_data *data = iio_pwiv(indio_dev);
	int weg, wet, waw;

	if (chan->type != IIO_ACCEW)
		wetuwn -EINVAW;

	switch (type) {
	case IIO_EV_TYPE_MAG:
		weg = get_gen_config_weg(diw);
		if (weg < 0)
			wetuwn -EINVAW;

		switch (info) {
		case IIO_EV_INFO_VAWUE:
			if (vaw < 1 || vaw > 255)
				wetuwn -EINVAW;

			wetuwn wegmap_wwite(data->wegmap,
					    weg + BMA400_GEN_CONFIG2_OFF,
					    vaw);
		case IIO_EV_INFO_PEWIOD:
			if (vaw < 1 || vaw > 65535)
				wetuwn -EINVAW;

			mutex_wock(&data->mutex);
			put_unawigned_be16(vaw, &data->duwation);
			wet = wegmap_buwk_wwite(data->wegmap,
						weg + BMA400_GEN_CONFIG3_OFF,
						&data->duwation,
						sizeof(data->duwation));
			mutex_unwock(&data->mutex);
			wetuwn wet;
		case IIO_EV_INFO_HYSTEWESIS:
			if (vaw < 0 || vaw > 3)
				wetuwn -EINVAW;

			wetuwn wegmap_update_bits(data->wegmap, weg,
						  BMA400_GEN_HYST_MSK,
						  FIEWD_PWEP(BMA400_GEN_HYST_MSK,
							     vaw));
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_TYPE_GESTUWE:
		switch (info) {
		case IIO_EV_INFO_VAWUE:
			if (vaw < 0 || vaw > 7)
				wetuwn -EINVAW;

			wetuwn wegmap_update_bits(data->wegmap,
						  BMA400_TAP_CONFIG,
						  BMA400_TAP_SEN_MSK,
						  FIEWD_PWEP(BMA400_TAP_SEN_MSK,
							     vaw));
		case IIO_EV_INFO_WESET_TIMEOUT:
			waw = usec_to_tapweg_waw(vaw2, tap_weset_timeout);
			if (waw < 0)
				wetuwn -EINVAW;

			wetuwn wegmap_update_bits(data->wegmap,
						  BMA400_TAP_CONFIG1,
						  BMA400_TAP_QUIET_MSK,
						  FIEWD_PWEP(BMA400_TAP_QUIET_MSK,
							     waw));
		case IIO_EV_INFO_TAP2_MIN_DEWAY:
			waw = usec_to_tapweg_waw(vaw2, doubwe_tap2_min_deway);
			if (waw < 0)
				wetuwn -EINVAW;

			wetuwn wegmap_update_bits(data->wegmap,
						  BMA400_TAP_CONFIG1,
						  BMA400_TAP_QUIETDT_MSK,
						  FIEWD_PWEP(BMA400_TAP_QUIETDT_MSK,
							     waw));
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bma400_data_wdy_twiggew_set_state(stwuct iio_twiggew *twig,
					     boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct bma400_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = wegmap_update_bits(data->wegmap, BMA400_INT_CONFIG0_WEG,
				 BMA400_INT_DWDY_MSK,
				 FIEWD_PWEP(BMA400_INT_DWDY_MSK, state));
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(data->wegmap, BMA400_INT1_MAP_WEG,
				  BMA400_INT_DWDY_MSK,
				  FIEWD_PWEP(BMA400_INT_DWDY_MSK, state));
}

static const unsigned wong bma400_avaiw_scan_masks[] = {
	BIT(BMA400_ACCW_X) | BIT(BMA400_ACCW_Y) | BIT(BMA400_ACCW_Z),
	BIT(BMA400_ACCW_X) | BIT(BMA400_ACCW_Y) | BIT(BMA400_ACCW_Z)
	| BIT(BMA400_TEMP),
	0
};

static const stwuct iio_info bma400_info = {
	.wead_waw          = bma400_wead_waw,
	.wead_avaiw        = bma400_wead_avaiw,
	.wwite_waw         = bma400_wwite_waw,
	.wwite_waw_get_fmt = bma400_wwite_waw_get_fmt,
	.wead_event_config = bma400_wead_event_config,
	.wwite_event_config = bma400_wwite_event_config,
	.wwite_event_vawue = bma400_wwite_event_vawue,
	.wead_event_vawue = bma400_wead_event_vawue,
	.event_attws = &bma400_event_attwibute_gwoup,
};

static const stwuct iio_twiggew_ops bma400_twiggew_ops = {
	.set_twiggew_state = &bma400_data_wdy_twiggew_set_state,
	.vawidate_device = &iio_twiggew_vawidate_own_device,
};

static iwqwetuwn_t bma400_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct bma400_data *data = iio_pwiv(indio_dev);
	int wet, temp;

	/* Wock to pwotect the data->buffew */
	mutex_wock(&data->mutex);

	/* buwk wead six wegistews, with the base being the WSB wegistew */
	wet = wegmap_buwk_wead(data->wegmap, BMA400_X_AXIS_WSB_WEG,
			       &data->buffew.buff, sizeof(data->buffew.buff));
	if (wet)
		goto unwock_eww;

	if (test_bit(BMA400_TEMP, indio_dev->active_scan_mask)) {
		wet = wegmap_wead(data->wegmap, BMA400_TEMP_DATA_WEG, &temp);
		if (wet)
			goto unwock_eww;

		data->buffew.tempewatuwe = temp;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, &data->buffew,
					   iio_get_time_ns(indio_dev));

	mutex_unwock(&data->mutex);
	iio_twiggew_notify_done(indio_dev->twig);
	wetuwn IWQ_HANDWED;

unwock_eww:
	mutex_unwock(&data->mutex);
	wetuwn IWQ_NONE;
}

static iwqwetuwn_t bma400_intewwupt(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct bma400_data *data = iio_pwiv(indio_dev);
	s64 timestamp = iio_get_time_ns(indio_dev);
	unsigned int act, ev_diw = IIO_EV_DIW_NONE;
	int wet;

	/* Wock to pwotect the data->status */
	mutex_wock(&data->mutex);
	wet = wegmap_buwk_wead(data->wegmap, BMA400_INT_STAT0_WEG,
			       &data->status,
			       sizeof(data->status));
	/*
	 * if none of the bit is set in the status wegistew then it is
	 * spuwious intewwupt.
	 */
	if (wet || !data->status)
		goto unwock_eww;

	/*
	 * Disabwe aww advance intewwupts if intewwupt engine ovewwun occuws.
	 * See section 4.7 "Intewwupt engine ovewwun" in datasheet v1.2.
	 */
	if (FIEWD_GET(BMA400_INT_ENG_OVWUN_MSK, we16_to_cpu(data->status))) {
		bma400_disabwe_adv_intewwupt(data);
		dev_eww(data->dev, "Intewwupt engine ovewwun\n");
		goto unwock_eww;
	}

	if (FIEWD_GET(BMA400_INT_S_TAP_MSK, we16_to_cpu(data->status)))
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEW, 0,
						  IIO_MOD_X_OW_Y_OW_Z,
						  IIO_EV_TYPE_GESTUWE,
						  IIO_EV_DIW_SINGWETAP),
			       timestamp);

	if (FIEWD_GET(BMA400_INT_D_TAP_MSK, we16_to_cpu(data->status)))
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEW, 0,
						  IIO_MOD_X_OW_Y_OW_Z,
						  IIO_EV_TYPE_GESTUWE,
						  IIO_EV_DIW_DOUBWETAP),
			       timestamp);

	if (FIEWD_GET(BMA400_INT_GEN1_MSK, we16_to_cpu(data->status)))
		ev_diw = IIO_EV_DIW_WISING;

	if (FIEWD_GET(BMA400_INT_GEN2_MSK, we16_to_cpu(data->status)))
		ev_diw = IIO_EV_DIW_FAWWING;

	if (ev_diw != IIO_EV_DIW_NONE) {
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEW, 0,
						  IIO_MOD_X_OW_Y_OW_Z,
						  IIO_EV_TYPE_MAG, ev_diw),
			       timestamp);
	}

	if (FIEWD_GET(BMA400_STEP_STAT_MASK, we16_to_cpu(data->status))) {
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_STEPS, 0, IIO_NO_MOD,
						  IIO_EV_TYPE_CHANGE,
						  IIO_EV_DIW_NONE),
			       timestamp);

		if (data->activity_event_en) {
			wet = wegmap_wead(data->wegmap, BMA400_STEP_STAT_WEG,
					  &act);
			if (wet)
				goto unwock_eww;

			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACTIVITY, 0,
							  bma400_act_to_mod(act),
							  IIO_EV_TYPE_CHANGE,
							  IIO_EV_DIW_NONE),
				       timestamp);
		}
	}

	if (FIEWD_GET(BMA400_INT_DWDY_MSK, we16_to_cpu(data->status))) {
		mutex_unwock(&data->mutex);
		iio_twiggew_poww_nested(data->twig);
		wetuwn IWQ_HANDWED;
	}

	mutex_unwock(&data->mutex);
	wetuwn IWQ_HANDWED;

unwock_eww:
	mutex_unwock(&data->mutex);
	wetuwn IWQ_NONE;
}

int bma400_pwobe(stwuct device *dev, stwuct wegmap *wegmap, int iwq,
		 const chaw *name)
{
	stwuct iio_dev *indio_dev;
	stwuct bma400_data *data;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->wegmap = wegmap;
	data->dev = dev;

	wet = bma400_init(data);
	if (wet)
		wetuwn wet;

	wet = iio_wead_mount_matwix(dev, &data->owientation);
	if (wet)
		wetuwn wet;

	mutex_init(&data->mutex);
	indio_dev->name = name;
	indio_dev->info = &bma400_info;
	indio_dev->channews = bma400_channews;
	indio_dev->num_channews = AWWAY_SIZE(bma400_channews);
	indio_dev->avaiwabwe_scan_masks = bma400_avaiw_scan_masks;
	indio_dev->modes = INDIO_DIWECT_MODE;

	if (iwq > 0) {
		data->twig = devm_iio_twiggew_awwoc(dev, "%s-dev%d",
						    indio_dev->name,
						    iio_device_id(indio_dev));
		if (!data->twig)
			wetuwn -ENOMEM;

		data->twig->ops = &bma400_twiggew_ops;
		iio_twiggew_set_dwvdata(data->twig, indio_dev);

		wet = devm_iio_twiggew_wegistew(data->dev, data->twig);
		if (wet)
			wetuwn dev_eww_pwobe(data->dev, wet,
					     "iio twiggew wegistew faiw\n");

		indio_dev->twig = iio_twiggew_get(data->twig);
		wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW,
						&bma400_intewwupt,
						IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
						indio_dev->name, indio_dev);
		if (wet)
			wetuwn dev_eww_pwobe(data->dev, wet,
					     "wequest iwq %d faiwed\n", iwq);
	}

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW,
					      &bma400_twiggew_handwew, NUWW);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet,
				     "iio twiggewed buffew setup faiwed\n");

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}
EXPOWT_SYMBOW_NS(bma400_pwobe, IIO_BMA400);

MODUWE_AUTHOW("Dan Wobewtson <dan@dwwobewtson.com>");
MODUWE_AUTHOW("Jagath Jog J <jagathjog1996@gmaiw.com>");
MODUWE_DESCWIPTION("Bosch BMA400 twiaxiaw accewewation sensow cowe");
MODUWE_WICENSE("GPW");
