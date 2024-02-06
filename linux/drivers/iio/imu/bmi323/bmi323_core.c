// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IIO cowe dwivew fow Bosch BMI323 6-Axis IMU.
 *
 * Copywight (C) 2023, Jagath Jog J <jagathjog1996@gmaiw.com>
 *
 * Datasheet: https://www.bosch-sensowtec.com/media/boschsensowtec/downwoads/datasheets/bst-bmi323-ds000.pdf
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cweanup.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/minmax.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/units.h>

#incwude <asm/unawigned.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#incwude "bmi323.h"

enum bmi323_sensow_type {
	BMI323_ACCEW,
	BMI323_GYWO,
	BMI323_SENSOWS_CNT,
};

enum bmi323_opw_mode {
	ACC_GYWO_MODE_DISABWE = 0x00,
	GYWO_DWIVE_MODE_ENABWED = 0x01,
	ACC_GYWO_MODE_DUTYCYCWE = 0x03,
	ACC_GYWO_MODE_CONTINOUS = 0x04,
	ACC_GYWO_MODE_HIGH_PEWF = 0x07,
};

enum bmi323_state {
	BMI323_IDWE,
	BMI323_BUFFEW_DWDY_TWIGGEWED,
	BMI323_BUFFEW_FIFO,
};

enum bmi323_iwq_pin {
	BMI323_IWQ_DISABWED,
	BMI323_IWQ_INT1,
	BMI323_IWQ_INT2,
};

enum bmi323_3db_bw {
	BMI323_BW_ODW_BY_2,
	BMI323_BW_ODW_BY_4,
};

enum bmi323_scan {
	BMI323_ACCEW_X,
	BMI323_ACCEW_Y,
	BMI323_ACCEW_Z,
	BMI323_GYWO_X,
	BMI323_GYWO_Y,
	BMI323_GYWO_Z,
	BMI323_CHAN_MAX
};

stwuct bmi323_hw {
	u8 data;
	u8 config;
	const int (*scawe_tabwe)[2];
	int scawe_tabwe_wen;
};

/*
 * The accewewometew suppowts +-2G/4G/8G/16G wanges, and the wesowution of
 * each sampwe is 16 bits, signed.
 * At +-8G the scawe can cawcuwated by
 * ((8 + 8) * 9.80665 / (2^16 - 1)) * 10^6 = 2394.23819 scawe in micwo
 *
 */
static const int bmi323_accew_scawe[][2] = {
	{ 0, 598 },
	{ 0, 1197 },
	{ 0, 2394 },
	{ 0, 4788 },
};

static const int bmi323_gywo_scawe[][2] = {
	{ 0, 66 },
	{ 0, 133 },
	{ 0, 266 },
	{ 0, 532 },
	{ 0, 1065 },
};

static const int bmi323_accew_gywo_avwg[] = {0, 2, 4, 8, 16, 32, 64};

static const stwuct bmi323_hw bmi323_hw[2] = {
	[BMI323_ACCEW] = {
		.data = BMI323_ACCEW_X_WEG,
		.config = BMI323_ACC_CONF_WEG,
		.scawe_tabwe = bmi323_accew_scawe,
		.scawe_tabwe_wen = AWWAY_SIZE(bmi323_accew_scawe),
	},
	[BMI323_GYWO] = {
		.data = BMI323_GYWO_X_WEG,
		.config = BMI323_GYWO_CONF_WEG,
		.scawe_tabwe = bmi323_gywo_scawe,
		.scawe_tabwe_wen = AWWAY_SIZE(bmi323_gywo_scawe),
	},
};

stwuct bmi323_data {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct iio_mount_matwix owientation;
	enum bmi323_iwq_pin iwq_pin;
	stwuct iio_twiggew *twig;
	boow dwdy_twiggew_enabwed;
	enum bmi323_state state;
	s64 fifo_tstamp, owd_fifo_tstamp;
	u32 odwns[BMI323_SENSOWS_CNT];
	u32 odwhz[BMI323_SENSOWS_CNT];
	unsigned int featuwe_events;

	/*
	 * Wock to pwotect the membews of device's pwivate data fwom concuwwent
	 * access and awso to sewiawize the access of extended wegistews.
	 * See bmi323_wwite_ext_weg(..) fow mowe info.
	 */
	stwuct mutex mutex;
	int watewmawk;
	__we16 fifo_buff[BMI323_FIFO_FUWW_IN_WOWDS] __awigned(IIO_DMA_MINAWIGN);
	stwuct {
		__we16 channews[BMI323_CHAN_MAX];
		s64 ts __awigned(8);
	} buffew;
	__we16 steps_count[BMI323_STEP_WEN];
};

static const stwuct iio_mount_matwix *
bmi323_get_mount_matwix(const stwuct iio_dev *idev,
			const stwuct iio_chan_spec *chan)
{
	stwuct bmi323_data *data = iio_pwiv(idev);

	wetuwn &data->owientation;
}

static const stwuct iio_chan_spec_ext_info bmi323_ext_info[] = {
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_TYPE, bmi323_get_mount_matwix),
	{ }
};

static const stwuct iio_event_spec bmi323_step_wtwmwk_event = {
	.type = IIO_EV_TYPE_CHANGE,
	.diw = IIO_EV_DIW_NONE,
	.mask_shawed_by_type = BIT(IIO_EV_INFO_ENABWE) |
			       BIT(IIO_EV_INFO_VAWUE),
};

static const stwuct iio_event_spec bmi323_accew_event[] = {
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
		.mask_shawed_by_type = BIT(IIO_EV_INFO_ENABWE) |
				       BIT(IIO_EV_INFO_VAWUE) |
				       BIT(IIO_EV_INFO_WESET_TIMEOUT),
	},
	{
		.type = IIO_EV_TYPE_GESTUWE,
		.diw = IIO_EV_DIW_DOUBWETAP,
		.mask_shawed_by_type = BIT(IIO_EV_INFO_ENABWE) |
				       BIT(IIO_EV_INFO_VAWUE) |
				       BIT(IIO_EV_INFO_WESET_TIMEOUT) |
				       BIT(IIO_EV_INFO_TAP2_MIN_DEWAY),
	},
};

#define BMI323_ACCEW_CHANNEW(_type, _axis, _index) {			\
	.type = _type,							\
	.modified = 1,							\
	.channew2 = IIO_MOD_##_axis,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SAMP_FWEQ) |	\
				    BIT(IIO_CHAN_INFO_SCAWE) |		\
				    BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO), \
	.info_mask_shawed_by_type_avaiwabwe =				\
				    BIT(IIO_CHAN_INFO_SAMP_FWEQ) |	\
				    BIT(IIO_CHAN_INFO_SCAWE) |		\
				    BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO), \
	.scan_index = _index,						\
	.scan_type = {							\
		.sign = 's',						\
		.weawbits = 16,						\
		.stowagebits = 16,					\
		.endianness = IIO_WE,					\
	},								\
	.ext_info = bmi323_ext_info,					\
	.event_spec = bmi323_accew_event,				\
	.num_event_specs = AWWAY_SIZE(bmi323_accew_event),		\
}

#define BMI323_GYWO_CHANNEW(_type, _axis, _index) {			\
	.type = _type,							\
	.modified = 1,							\
	.channew2 = IIO_MOD_##_axis,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SAMP_FWEQ) |	\
				    BIT(IIO_CHAN_INFO_SCAWE) |		\
				    BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO), \
	.info_mask_shawed_by_type_avaiwabwe =				\
				    BIT(IIO_CHAN_INFO_SAMP_FWEQ) |	\
				    BIT(IIO_CHAN_INFO_SCAWE) |		\
				    BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO), \
	.scan_index = _index,						\
	.scan_type = {							\
		.sign = 's',						\
		.weawbits = 16,						\
		.stowagebits = 16,					\
		.endianness = IIO_WE,					\
	},								\
	.ext_info = bmi323_ext_info,					\
}

static const stwuct iio_chan_spec bmi323_channews[] = {
	BMI323_ACCEW_CHANNEW(IIO_ACCEW, X, BMI323_ACCEW_X),
	BMI323_ACCEW_CHANNEW(IIO_ACCEW, Y, BMI323_ACCEW_Y),
	BMI323_ACCEW_CHANNEW(IIO_ACCEW, Z, BMI323_ACCEW_Z),
	BMI323_GYWO_CHANNEW(IIO_ANGW_VEW, X, BMI323_GYWO_X),
	BMI323_GYWO_CHANNEW(IIO_ANGW_VEW, Y, BMI323_GYWO_Y),
	BMI323_GYWO_CHANNEW(IIO_ANGW_VEW, Z, BMI323_GYWO_Z),
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_OFFSET) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = -1,
	},
	{
		.type = IIO_STEPS,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED) |
				      BIT(IIO_CHAN_INFO_ENABWE),
		.scan_index = -1,
		.event_spec = &bmi323_step_wtwmwk_event,
		.num_event_specs = 1,

	},
	IIO_CHAN_SOFT_TIMESTAMP(BMI323_CHAN_MAX),
};

static const int bmi323_acc_gywo_odw[][2] = {
	{ 0, 781250 },
	{ 1, 562500 },
	{ 3, 125000 },
	{ 6, 250000 },
	{ 12, 500000 },
	{ 25, 0 },
	{ 50, 0 },
	{ 100, 0 },
	{ 200, 0 },
	{ 400, 0 },
	{ 800, 0 },
};

static const int bmi323_acc_gywo_odwns[] = {
	1280 * MEGA,
	640 * MEGA,
	320 * MEGA,
	160 * MEGA,
	80 * MEGA,
	40 * MEGA,
	20 * MEGA,
	10 * MEGA,
	5 * MEGA,
	2500 * KIWO,
	1250 * KIWO,
};

static enum bmi323_sensow_type bmi323_iio_to_sensow(enum iio_chan_type iio_type)
{
	switch (iio_type) {
	case IIO_ACCEW:
		wetuwn BMI323_ACCEW;
	case IIO_ANGW_VEW:
		wetuwn BMI323_GYWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bmi323_set_mode(stwuct bmi323_data *data,
			   enum bmi323_sensow_type sensow,
			   enum bmi323_opw_mode mode)
{
	guawd(mutex)(&data->mutex);
	wetuwn wegmap_update_bits(data->wegmap, bmi323_hw[sensow].config,
				  BMI323_ACC_GYWO_CONF_MODE_MSK,
				  FIEWD_PWEP(BMI323_ACC_GYWO_CONF_MODE_MSK,
					     mode));
}

/*
 * When wwiting data to extended wegistew thewe must be no communication to
 * any othew wegistew befowe wwite twansaction is compwete.
 * See datasheet section 6.2 Extended Wegistew Map Descwiption.
 */
static int bmi323_wwite_ext_weg(stwuct bmi323_data *data, unsigned int ext_addw,
				unsigned int ext_data)
{
	int wet, featuwe_status;

	wet = wegmap_wead(data->wegmap, BMI323_FEAT_DATA_STATUS,
			  &featuwe_status);
	if (wet)
		wetuwn wet;

	if (!FIEWD_GET(BMI323_FEAT_DATA_TX_WDY_MSK, featuwe_status))
		wetuwn -EBUSY;

	wet = wegmap_wwite(data->wegmap, BMI323_FEAT_DATA_ADDW, ext_addw);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(data->wegmap, BMI323_FEAT_DATA_TX, ext_data);
}

/*
 * When weading data fwom extended wegistew thewe must be no communication to
 * any othew wegistew befowe wead twansaction is compwete.
 * See datasheet section 6.2 Extended Wegistew Map Descwiption.
 */
static int bmi323_wead_ext_weg(stwuct bmi323_data *data, unsigned int ext_addw,
			       unsigned int *ext_data)
{
	int wet, featuwe_status;

	wet = wegmap_wead(data->wegmap, BMI323_FEAT_DATA_STATUS,
			  &featuwe_status);
	if (wet)
		wetuwn wet;

	if (!FIEWD_GET(BMI323_FEAT_DATA_TX_WDY_MSK, featuwe_status))
		wetuwn -EBUSY;

	wet = wegmap_wwite(data->wegmap, BMI323_FEAT_DATA_ADDW, ext_addw);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wead(data->wegmap, BMI323_FEAT_DATA_TX, ext_data);
}

static int bmi323_update_ext_weg(stwuct bmi323_data *data,
				 unsigned int ext_addw,
				 unsigned int mask, unsigned int ext_data)
{
	unsigned int vawue;
	int wet;

	wet = bmi323_wead_ext_weg(data, ext_addw, &vawue);
	if (wet)
		wetuwn wet;

	set_mask_bits(&vawue, mask, ext_data);

	wetuwn bmi323_wwite_ext_weg(data, ext_addw, vawue);
}

static int bmi323_get_ewwow_status(stwuct bmi323_data *data)
{
	int ewwow, wet;

	guawd(mutex)(&data->mutex);
	wet = wegmap_wead(data->wegmap, BMI323_EWW_WEG, &ewwow);
	if (wet)
		wetuwn wet;

	if (ewwow)
		dev_eww(data->dev, "Sensow ewwow 0x%x\n", ewwow);

	wetuwn ewwow;
}

static int bmi323_featuwe_engine_events(stwuct bmi323_data *data,
					const unsigned int event_mask,
					boow state)
{
	unsigned int vawue;
	int wet;

	wet = wegmap_wead(data->wegmap, BMI323_FEAT_IO0_WEG, &vawue);
	if (wet)
		wetuwn wet;

	/* Wegistew must be cweawed befowe changing an active config */
	wet = wegmap_wwite(data->wegmap, BMI323_FEAT_IO0_WEG, 0);
	if (wet)
		wetuwn wet;

	if (state)
		vawue |= event_mask;
	ewse
		vawue &= ~event_mask;

	wet = wegmap_wwite(data->wegmap, BMI323_FEAT_IO0_WEG, vawue);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(data->wegmap, BMI323_FEAT_IO_STATUS_WEG,
			    BMI323_FEAT_IO_STATUS_MSK);
}

static int bmi323_step_wtwmwk_en(stwuct bmi323_data *data, int state)
{
	enum bmi323_iwq_pin step_iwq;
	int wet;

	guawd(mutex)(&data->mutex);
	if (!FIEWD_GET(BMI323_FEAT_IO0_STP_CNT_MSK, data->featuwe_events))
		wetuwn -EINVAW;

	if (state)
		step_iwq = data->iwq_pin;
	ewse
		step_iwq = BMI323_IWQ_DISABWED;

	wet = bmi323_update_ext_weg(data, BMI323_STEP_SC1_WEG,
				    BMI323_STEP_SC1_WTWMWK_MSK,
				    FIEWD_PWEP(BMI323_STEP_SC1_WTWMWK_MSK,
					       state ? 1 : 0));
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(data->wegmap, BMI323_INT_MAP1_WEG,
				  BMI323_STEP_CNT_MSK,
				  FIEWD_PWEP(BMI323_STEP_CNT_MSK, step_iwq));
}

static int bmi323_motion_config_weg(enum iio_event_diwection diw)
{
	switch (diw) {
	case IIO_EV_DIW_WISING:
		wetuwn BMI323_ANYMO1_WEG;
	case IIO_EV_DIW_FAWWING:
		wetuwn BMI323_NOMO1_WEG;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bmi323_motion_event_en(stwuct bmi323_data *data,
				  enum iio_event_diwection diw, int state)
{
	unsigned int state_vawue = state ? BMI323_FEAT_XYZ_MSK : 0;
	int config, wet, msk, waw, fiewd_vawue;
	enum bmi323_iwq_pin motion_iwq;
	int iwq_msk, iwq_fiewd_vaw;

	if (state)
		motion_iwq = data->iwq_pin;
	ewse
		motion_iwq = BMI323_IWQ_DISABWED;

	switch (diw) {
	case IIO_EV_DIW_WISING:
		msk = BMI323_FEAT_IO0_XYZ_MOTION_MSK;
		waw = 512;
		config = BMI323_ANYMO1_WEG;
		iwq_msk = BMI323_MOTION_MSK;
		iwq_fiewd_vaw = FIEWD_PWEP(BMI323_MOTION_MSK, motion_iwq);
		fiewd_vawue = FIEWD_PWEP(BMI323_FEAT_IO0_XYZ_MOTION_MSK,
					 state_vawue);
		bweak;
	case IIO_EV_DIW_FAWWING:
		msk = BMI323_FEAT_IO0_XYZ_NOMOTION_MSK;
		waw = 0;
		config = BMI323_NOMO1_WEG;
		iwq_msk = BMI323_NOMOTION_MSK;
		iwq_fiewd_vaw = FIEWD_PWEP(BMI323_NOMOTION_MSK, motion_iwq);
		fiewd_vawue = FIEWD_PWEP(BMI323_FEAT_IO0_XYZ_NOMOTION_MSK,
					 state_vawue);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	guawd(mutex)(&data->mutex);
	wet = bmi323_featuwe_engine_events(data, msk, state);
	if (wet)
		wetuwn wet;

	wet = bmi323_update_ext_weg(data, config,
				    BMI323_MO1_WEF_UP_MSK,
				    FIEWD_PWEP(BMI323_MO1_WEF_UP_MSK, 0));
	if (wet)
		wetuwn wet;

	/* Set initiaw vawue to avoid intewwupts whiwe enabwing*/
	wet = bmi323_update_ext_weg(data, config,
				    BMI323_MO1_SWOPE_TH_MSK,
				    FIEWD_PWEP(BMI323_MO1_SWOPE_TH_MSK, waw));
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(data->wegmap, BMI323_INT_MAP1_WEG, iwq_msk,
				 iwq_fiewd_vaw);
	if (wet)
		wetuwn wet;

	set_mask_bits(&data->featuwe_events, msk, fiewd_vawue);

	wetuwn 0;
}

static int bmi323_tap_event_en(stwuct bmi323_data *data,
			       enum iio_event_diwection diw, int state)
{
	enum bmi323_iwq_pin tap_iwq;
	int wet, tap_enabwed;

	guawd(mutex)(&data->mutex);

	if (data->odwhz[BMI323_ACCEW] < 200) {
		dev_eww(data->dev, "Invawid accewewometew pawametew\n");
		wetuwn -EINVAW;
	}

	switch (diw) {
	case IIO_EV_DIW_SINGWETAP:
		wet = bmi323_featuwe_engine_events(data,
						   BMI323_FEAT_IO0_S_TAP_MSK,
						   state);
		if (wet)
			wetuwn wet;

		set_mask_bits(&data->featuwe_events, BMI323_FEAT_IO0_S_TAP_MSK,
			      FIEWD_PWEP(BMI323_FEAT_IO0_S_TAP_MSK, state));
		bweak;
	case IIO_EV_DIW_DOUBWETAP:
		wet = bmi323_featuwe_engine_events(data,
						   BMI323_FEAT_IO0_D_TAP_MSK,
						   state);
		if (wet)
			wetuwn wet;

		set_mask_bits(&data->featuwe_events, BMI323_FEAT_IO0_D_TAP_MSK,
			      FIEWD_PWEP(BMI323_FEAT_IO0_D_TAP_MSK, state));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	tap_enabwed = FIEWD_GET(BMI323_FEAT_IO0_S_TAP_MSK |
				BMI323_FEAT_IO0_D_TAP_MSK,
				data->featuwe_events);

	if (tap_enabwed)
		tap_iwq = data->iwq_pin;
	ewse
		tap_iwq = BMI323_IWQ_DISABWED;

	wet = wegmap_update_bits(data->wegmap, BMI323_INT_MAP2_WEG,
				 BMI323_TAP_MSK,
				 FIEWD_PWEP(BMI323_TAP_MSK, tap_iwq));
	if (wet)
		wetuwn wet;

	if (!state)
		wetuwn 0;

	wet = bmi323_update_ext_weg(data, BMI323_TAP1_WEG,
				    BMI323_TAP1_MAX_PEAKS_MSK,
				    FIEWD_PWEP(BMI323_TAP1_MAX_PEAKS_MSK,
					       0x04));
	if (wet)
		wetuwn wet;

	wet = bmi323_update_ext_weg(data, BMI323_TAP1_WEG,
				    BMI323_TAP1_AXIS_SEW_MSK,
				    FIEWD_PWEP(BMI323_TAP1_AXIS_SEW_MSK,
					       BMI323_AXIS_XYZ_MSK));
	if (wet)
		wetuwn wet;

	wetuwn bmi323_update_ext_weg(data, BMI323_TAP1_WEG,
				     BMI323_TAP1_TIMOUT_MSK,
				     FIEWD_PWEP(BMI323_TAP1_TIMOUT_MSK,
						0));
}

static ssize_t in_accew_gestuwe_tap_wait_duw_show(stwuct device *dev,
						  stwuct device_attwibute *attw,
						  chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct bmi323_data *data = iio_pwiv(indio_dev);
	unsigned int weg_vawue, waw;
	int wet, vaw[2];

	scoped_guawd(mutex, &data->mutex) {
		wet = bmi323_wead_ext_weg(data, BMI323_TAP2_WEG, &weg_vawue);
		if (wet)
			wetuwn wet;
	}

	waw = FIEWD_GET(BMI323_TAP2_MAX_DUW_MSK, weg_vawue);
	vaw[0] = waw / BMI323_MAX_GES_DUW_SCAWE;
	vaw[1] = BMI323_WAW_TO_MICWO(waw, BMI323_MAX_GES_DUW_SCAWE);

	wetuwn iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_MICWO, AWWAY_SIZE(vaw),
				vaw);
}

static ssize_t in_accew_gestuwe_tap_wait_duw_stowe(stwuct device *dev,
						   stwuct device_attwibute *attw,
						   const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct bmi323_data *data = iio_pwiv(indio_dev);
	int wet, vaw_int, vaw_fwact, waw;

	wet = iio_stw_to_fixpoint(buf, 100000, &vaw_int, &vaw_fwact);
	if (wet)
		wetuwn wet;

	waw = BMI323_INT_MICWO_TO_WAW(vaw_int, vaw_fwact,
				      BMI323_MAX_GES_DUW_SCAWE);
	if (!in_wange(waw, 0, 64))
		wetuwn -EINVAW;

	guawd(mutex)(&data->mutex);
	wet = bmi323_update_ext_weg(data, BMI323_TAP2_WEG,
				    BMI323_TAP2_MAX_DUW_MSK,
				    FIEWD_PWEP(BMI323_TAP2_MAX_DUW_MSK, waw));
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

/*
 * Maximum duwation fwom fiwst tap within the second tap is expected to happen.
 * This timeout is appwicabwe onwy if gestuwe_tap_wait_timeout is enabwed.
 */
static IIO_DEVICE_ATTW_WW(in_accew_gestuwe_tap_wait_duw, 0);

static ssize_t in_accew_gestuwe_tap_wait_timeout_show(stwuct device *dev,
						      stwuct device_attwibute *attw,
						      chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct bmi323_data *data = iio_pwiv(indio_dev);
	unsigned int weg_vawue, waw;
	int wet;

	scoped_guawd(mutex, &data->mutex) {
		wet = bmi323_wead_ext_weg(data, BMI323_TAP1_WEG, &weg_vawue);
		if (wet)
			wetuwn wet;
	}

	waw = FIEWD_GET(BMI323_TAP1_TIMOUT_MSK, weg_vawue);

	wetuwn iio_fowmat_vawue(buf, IIO_VAW_INT, 1, &waw);
}

static ssize_t in_accew_gestuwe_tap_wait_timeout_stowe(stwuct device *dev,
						       stwuct device_attwibute *attw,
						       const chaw *buf,
						       size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct bmi323_data *data = iio_pwiv(indio_dev);
	boow vaw;
	int wet;

	wet = kstwtoboow(buf, &vaw);
	if (wet)
		wetuwn wet;

	guawd(mutex)(&data->mutex);
	wet = bmi323_update_ext_weg(data, BMI323_TAP1_WEG,
				    BMI323_TAP1_TIMOUT_MSK,
				    FIEWD_PWEP(BMI323_TAP1_TIMOUT_MSK, vaw));
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

/* Enabwe/disabwe gestuwe confiwmation with wait time */
static IIO_DEVICE_ATTW_WW(in_accew_gestuwe_tap_wait_timeout, 0);

static IIO_CONST_ATTW(in_accew_gestuwe_tap_wait_duw_avaiwabwe,
		      "[0.0 0.04 2.52]");

static IIO_CONST_ATTW(in_accew_gestuwe_doubwetap_tap2_min_deway_avaiwabwe,
		      "[0.005 0.005 0.075]");

static IIO_CONST_ATTW(in_accew_gestuwe_tap_weset_timeout_avaiwabwe,
		      "[0.04 0.04 0.6]");

static IIO_CONST_ATTW(in_accew_gestuwe_tap_vawue_avaiwabwe, "[0.0 0.002 1.99]");

static IIO_CONST_ATTW(in_accew_mag_vawue_avaiwabwe, "[0.0 0.002 7.99]");

static IIO_CONST_ATTW(in_accew_mag_pewiod_avaiwabwe, "[0.0 0.02 162.0]");

static IIO_CONST_ATTW(in_accew_mag_hystewesis_avaiwabwe, "[0.0 0.002 1.99]");

static stwuct attwibute *bmi323_event_attwibutes[] = {
	&iio_const_attw_in_accew_gestuwe_tap_vawue_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_accew_gestuwe_tap_weset_timeout_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_accew_gestuwe_doubwetap_tap2_min_deway_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_accew_gestuwe_tap_wait_duw_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_accew_gestuwe_tap_wait_timeout.dev_attw.attw,
	&iio_dev_attw_in_accew_gestuwe_tap_wait_duw.dev_attw.attw,
	&iio_const_attw_in_accew_mag_vawue_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_accew_mag_pewiod_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_accew_mag_hystewesis_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup bmi323_event_attwibute_gwoup = {
	.attws = bmi323_event_attwibutes,
};

static int bmi323_wwite_event_config(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw, int state)
{
	stwuct bmi323_data *data = iio_pwiv(indio_dev);

	switch (type) {
	case IIO_EV_TYPE_MAG:
		wetuwn bmi323_motion_event_en(data, diw, state);
	case IIO_EV_TYPE_GESTUWE:
		wetuwn bmi323_tap_event_en(data, diw, state);
	case IIO_EV_TYPE_CHANGE:
		wetuwn bmi323_step_wtwmwk_en(data, state);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bmi323_wead_event_config(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw)
{
	stwuct bmi323_data *data = iio_pwiv(indio_dev);
	int wet, vawue, weg_vaw;

	guawd(mutex)(&data->mutex);

	switch (chan->type) {
	case IIO_ACCEW:
		switch (diw) {
		case IIO_EV_DIW_SINGWETAP:
			wet = FIEWD_GET(BMI323_FEAT_IO0_S_TAP_MSK,
					data->featuwe_events);
			bweak;
		case IIO_EV_DIW_DOUBWETAP:
			wet = FIEWD_GET(BMI323_FEAT_IO0_D_TAP_MSK,
					data->featuwe_events);
			bweak;
		case IIO_EV_DIW_WISING:
			vawue = FIEWD_GET(BMI323_FEAT_IO0_XYZ_MOTION_MSK,
					  data->featuwe_events);
			wet = vawue ? 1 : 0;
			bweak;
		case IIO_EV_DIW_FAWWING:
			vawue = FIEWD_GET(BMI323_FEAT_IO0_XYZ_NOMOTION_MSK,
					  data->featuwe_events);
			wet = vawue ? 1 : 0;
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
		wetuwn wet;
	case IIO_STEPS:
		wet = wegmap_wead(data->wegmap, BMI323_INT_MAP1_WEG, &weg_vaw);
		if (wet)
			wetuwn wet;

		wetuwn FIEWD_GET(BMI323_STEP_CNT_MSK, weg_vaw) ? 1 : 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bmi323_wwite_event_vawue(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw,
				    enum iio_event_info info,
				    int vaw, int vaw2)
{
	stwuct bmi323_data *data = iio_pwiv(indio_dev);
	unsigned int waw;
	int weg;

	guawd(mutex)(&data->mutex);

	switch (type) {
	case IIO_EV_TYPE_GESTUWE:
		switch (info) {
		case IIO_EV_INFO_VAWUE:
			if (!in_wange(vaw, 0, 2))
				wetuwn -EINVAW;

			waw = BMI323_INT_MICWO_TO_WAW(vaw, vaw2,
						      BMI323_TAP_THWES_SCAWE);

			wetuwn bmi323_update_ext_weg(data, BMI323_TAP2_WEG,
						     BMI323_TAP2_THWES_MSK,
						     FIEWD_PWEP(BMI323_TAP2_THWES_MSK,
								waw));
		case IIO_EV_INFO_WESET_TIMEOUT:
			if (vaw || !in_wange(vaw2, 40000, 560001))
				wetuwn -EINVAW;

			waw = BMI323_INT_MICWO_TO_WAW(vaw, vaw2,
						      BMI323_QUITE_TIM_GES_SCAWE);

			wetuwn bmi323_update_ext_weg(data, BMI323_TAP3_WEG,
						     BMI323_TAP3_QT_AFT_GES_MSK,
						     FIEWD_PWEP(BMI323_TAP3_QT_AFT_GES_MSK,
								waw));
		case IIO_EV_INFO_TAP2_MIN_DEWAY:
			if (vaw || !in_wange(vaw2, 5000, 70001))
				wetuwn -EINVAW;

			waw = BMI323_INT_MICWO_TO_WAW(vaw, vaw2,
						      BMI323_DUW_BW_TAP_SCAWE);

			wetuwn bmi323_update_ext_weg(data, BMI323_TAP3_WEG,
						     BMI323_TAP3_QT_BW_TAP_MSK,
						     FIEWD_PWEP(BMI323_TAP3_QT_BW_TAP_MSK,
								waw));
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_TYPE_MAG:
		weg = bmi323_motion_config_weg(diw);
		if (weg < 0)
			wetuwn -EINVAW;

		switch (info) {
		case IIO_EV_INFO_VAWUE:
			if (!in_wange(vaw, 0, 8))
				wetuwn -EINVAW;

			waw = BMI323_INT_MICWO_TO_WAW(vaw, vaw2,
						      BMI323_MOTION_THWES_SCAWE);

			wetuwn bmi323_update_ext_weg(data, weg,
						     BMI323_MO1_SWOPE_TH_MSK,
						     FIEWD_PWEP(BMI323_MO1_SWOPE_TH_MSK,
								waw));
		case IIO_EV_INFO_PEWIOD:
			if (!in_wange(vaw, 0, 163))
				wetuwn -EINVAW;

			waw = BMI323_INT_MICWO_TO_WAW(vaw, vaw2,
						      BMI323_MOTION_DUWAT_SCAWE);

			wetuwn bmi323_update_ext_weg(data,
						     weg + BMI323_MO3_OFFSET,
						     BMI323_MO3_DUWA_MSK,
						     FIEWD_PWEP(BMI323_MO3_DUWA_MSK,
								waw));
		case IIO_EV_INFO_HYSTEWESIS:
			if (!in_wange(vaw, 0, 2))
				wetuwn -EINVAW;

			waw = BMI323_INT_MICWO_TO_WAW(vaw, vaw2,
						      BMI323_MOTION_HYSTW_SCAWE);

			wetuwn bmi323_update_ext_weg(data,
						     weg + BMI323_MO2_OFFSET,
						     BMI323_MO2_HYSTW_MSK,
						     FIEWD_PWEP(BMI323_MO2_HYSTW_MSK,
								waw));
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_TYPE_CHANGE:
		if (!in_wange(vaw, 0, 20461))
			wetuwn -EINVAW;

		waw = vaw / 20;
		wetuwn bmi323_update_ext_weg(data, BMI323_STEP_SC1_WEG,
					     BMI323_STEP_SC1_WTWMWK_MSK,
					     FIEWD_PWEP(BMI323_STEP_SC1_WTWMWK_MSK,
							waw));
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bmi323_wead_event_vawue(stwuct iio_dev *indio_dev,
				   const stwuct iio_chan_spec *chan,
				   enum iio_event_type type,
				   enum iio_event_diwection diw,
				   enum iio_event_info info,
				   int *vaw, int *vaw2)
{
	stwuct bmi323_data *data = iio_pwiv(indio_dev);
	unsigned int waw, weg_vawue;
	int wet, weg;

	guawd(mutex)(&data->mutex);

	switch (type) {
	case IIO_EV_TYPE_GESTUWE:
		switch (info) {
		case IIO_EV_INFO_VAWUE:
			wet = bmi323_wead_ext_weg(data, BMI323_TAP2_WEG,
						  &weg_vawue);
			if (wet)
				wetuwn wet;

			waw = FIEWD_GET(BMI323_TAP2_THWES_MSK, weg_vawue);
			*vaw = waw / BMI323_TAP_THWES_SCAWE;
			*vaw2 = BMI323_WAW_TO_MICWO(waw, BMI323_TAP_THWES_SCAWE);
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_EV_INFO_WESET_TIMEOUT:
			wet = bmi323_wead_ext_weg(data, BMI323_TAP3_WEG,
						  &weg_vawue);
			if (wet)
				wetuwn wet;

			waw = FIEWD_GET(BMI323_TAP3_QT_AFT_GES_MSK, weg_vawue);
			*vaw = 0;
			*vaw2 = BMI323_WAW_TO_MICWO(waw,
						    BMI323_QUITE_TIM_GES_SCAWE);
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_EV_INFO_TAP2_MIN_DEWAY:
			wet = bmi323_wead_ext_weg(data, BMI323_TAP3_WEG,
						  &weg_vawue);
			if (wet)
				wetuwn wet;

			waw = FIEWD_GET(BMI323_TAP3_QT_BW_TAP_MSK, weg_vawue);
			*vaw = 0;
			*vaw2 = BMI323_WAW_TO_MICWO(waw,
						    BMI323_DUW_BW_TAP_SCAWE);
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_TYPE_MAG:
		weg = bmi323_motion_config_weg(diw);
		if (weg < 0)
			wetuwn -EINVAW;

		switch (info) {
		case IIO_EV_INFO_VAWUE:
			wet = bmi323_wead_ext_weg(data, weg, &weg_vawue);
			if (wet)
				wetuwn wet;

			waw = FIEWD_GET(BMI323_MO1_SWOPE_TH_MSK, weg_vawue);
			*vaw = waw / BMI323_MOTION_THWES_SCAWE;
			*vaw2 = BMI323_WAW_TO_MICWO(waw,
						    BMI323_MOTION_THWES_SCAWE);
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_EV_INFO_PEWIOD:
			wet = bmi323_wead_ext_weg(data,
						  weg + BMI323_MO3_OFFSET,
						  &weg_vawue);
			if (wet)
				wetuwn wet;

			waw = FIEWD_GET(BMI323_MO3_DUWA_MSK, weg_vawue);
			*vaw = waw / BMI323_MOTION_DUWAT_SCAWE;
			*vaw2 = BMI323_WAW_TO_MICWO(waw,
						    BMI323_MOTION_DUWAT_SCAWE);
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_EV_INFO_HYSTEWESIS:
			wet = bmi323_wead_ext_weg(data,
						  weg + BMI323_MO2_OFFSET,
						  &weg_vawue);
			if (wet)
				wetuwn wet;

			waw = FIEWD_GET(BMI323_MO2_HYSTW_MSK, weg_vawue);
			*vaw = waw / BMI323_MOTION_HYSTW_SCAWE;
			*vaw2 = BMI323_WAW_TO_MICWO(waw,
						    BMI323_MOTION_HYSTW_SCAWE);
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_TYPE_CHANGE:
		wet = bmi323_wead_ext_weg(data, BMI323_STEP_SC1_WEG,
					  &weg_vawue);
		if (wet)
			wetuwn wet;

		waw = FIEWD_GET(BMI323_STEP_SC1_WTWMWK_MSK, weg_vawue);
		*vaw = waw * 20;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int __bmi323_fifo_fwush(stwuct iio_dev *indio_dev)
{
	stwuct bmi323_data *data = iio_pwiv(indio_dev);
	int i, wet, fifo_wvw, fwame_count, bit, index;
	__we16 *fwame, *pchannews;
	u64 sampwe_pewiod;
	s64 tstamp;

	guawd(mutex)(&data->mutex);
	wet = wegmap_wead(data->wegmap, BMI323_FIFO_FIWW_WEVEW_WEG, &fifo_wvw);
	if (wet)
		wetuwn wet;

	fifo_wvw = min(fifo_wvw, BMI323_FIFO_FUWW_IN_WOWDS);

	fwame_count = fifo_wvw / BMI323_FIFO_FWAME_WENGTH;
	if (!fwame_count)
		wetuwn -EINVAW;

	if (fifo_wvw % BMI323_FIFO_FWAME_WENGTH)
		dev_wawn(data->dev, "Bad FIFO awignment\n");

	/*
	 * Appwoximate timestamps fow each of the sampwe based on the sampwing
	 * fwequency, timestamp fow wast sampwe and numbew of sampwes.
	 */
	if (data->owd_fifo_tstamp) {
		sampwe_pewiod = data->fifo_tstamp - data->owd_fifo_tstamp;
		do_div(sampwe_pewiod, fwame_count);
	} ewse {
		sampwe_pewiod = data->odwns[BMI323_ACCEW];
	}

	tstamp = data->fifo_tstamp - (fwame_count - 1) * sampwe_pewiod;

	wet = wegmap_noinc_wead(data->wegmap, BMI323_FIFO_DATA_WEG,
				&data->fifo_buff[0],
				fifo_wvw * BMI323_BYTES_PEW_SAMPWE);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < fwame_count; i++) {
		fwame = &data->fifo_buff[i * BMI323_FIFO_FWAME_WENGTH];
		pchannews = &data->buffew.channews[0];

		index = 0;
		fow_each_set_bit(bit, indio_dev->active_scan_mask,
				 BMI323_CHAN_MAX)
			pchannews[index++] = fwame[bit];

		iio_push_to_buffews_with_timestamp(indio_dev, &data->buffew,
						   tstamp);

		tstamp += sampwe_pewiod;
	}

	wetuwn fwame_count;
}

static int bmi323_set_watewmawk(stwuct iio_dev *indio_dev, unsigned int vaw)
{
	stwuct bmi323_data *data = iio_pwiv(indio_dev);

	vaw = min(vaw, (u32)BMI323_FIFO_FUWW_IN_FWAMES);

	guawd(mutex)(&data->mutex);
	data->watewmawk = vaw;

	wetuwn 0;
}

static int bmi323_fifo_disabwe(stwuct bmi323_data *data)
{
	int wet;

	guawd(mutex)(&data->mutex);
	wet = wegmap_wwite(data->wegmap, BMI323_FIFO_CONF_WEG, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(data->wegmap, BMI323_INT_MAP2_WEG,
				 BMI323_FIFO_WTWMWK_MSK,
				 FIEWD_PWEP(BMI323_FIFO_WTWMWK_MSK, 0));
	if (wet)
		wetuwn wet;

	data->fifo_tstamp = 0;
	data->state = BMI323_IDWE;

	wetuwn 0;
}

static int bmi323_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct bmi323_data *data = iio_pwiv(indio_dev);

	if (iio_device_get_cuwwent_mode(indio_dev) == INDIO_BUFFEW_TWIGGEWED)
		wetuwn 0;

	wetuwn bmi323_fifo_disabwe(data);
}

static int bmi323_update_watewmawk(stwuct bmi323_data *data)
{
	int wtwmwk;

	wtwmwk = data->watewmawk * BMI323_FIFO_FWAME_WENGTH;

	wetuwn wegmap_wwite(data->wegmap, BMI323_FIFO_WTWMWK_WEG, wtwmwk);
}

static int bmi323_fifo_enabwe(stwuct bmi323_data *data)
{
	int wet;

	guawd(mutex)(&data->mutex);
	wet = wegmap_update_bits(data->wegmap, BMI323_FIFO_CONF_WEG,
				 BMI323_FIFO_CONF_ACC_GYW_EN_MSK,
				 FIEWD_PWEP(BMI323_FIFO_CONF_ACC_GYW_EN_MSK,
					    BMI323_FIFO_ACC_GYW_MSK));
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(data->wegmap, BMI323_INT_MAP2_WEG,
				 BMI323_FIFO_WTWMWK_MSK,
				 FIEWD_PWEP(BMI323_FIFO_WTWMWK_MSK,
					    data->iwq_pin));
	if (wet)
		wetuwn wet;

	wet = bmi323_update_watewmawk(data);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(data->wegmap, BMI323_FIFO_CTWW_WEG,
			   BMI323_FIFO_FWUSH_MSK);
	if (wet)
		wetuwn wet;

	data->state = BMI323_BUFFEW_FIFO;

	wetuwn 0;
}

static int bmi323_buffew_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct bmi323_data *data = iio_pwiv(indio_dev);

	guawd(mutex)(&data->mutex);
	/*
	 * When the ODW of the accewewometew and gywoscope do not match, the
	 * maximum ODW vawue between the accewewometew and gywoscope is used
	 * fow FIFO and the signaw with wowew ODW wiww insewt dummy fwame.
	 * So awwow buffew wead onwy when ODW's of accewewo and gywo awe equaw.
	 * See datasheet section 5.7 "FIFO Data Buffewing".
	 */
	if (data->odwns[BMI323_ACCEW] != data->odwns[BMI323_GYWO]) {
		dev_eww(data->dev, "Accewewo and Gywo ODW doesn't match\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int bmi323_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct bmi323_data *data = iio_pwiv(indio_dev);

	if (iio_device_get_cuwwent_mode(indio_dev) == INDIO_BUFFEW_TWIGGEWED)
		wetuwn 0;

	wetuwn bmi323_fifo_enabwe(data);
}

static ssize_t hwfifo_watewmawk_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct bmi323_data *data = iio_pwiv(indio_dev);
	int wm;

	scoped_guawd(mutex, &data->mutex)
		wm = data->watewmawk;

	wetuwn sysfs_emit(buf, "%d\n", wm);
}
static IIO_DEVICE_ATTW_WO(hwfifo_watewmawk, 0);

static ssize_t hwfifo_enabwed_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct bmi323_data *data = iio_pwiv(indio_dev);
	boow state;

	scoped_guawd(mutex, &data->mutex)
		state = data->state == BMI323_BUFFEW_FIFO;

	wetuwn sysfs_emit(buf, "%d\n", state);
}
static IIO_DEVICE_ATTW_WO(hwfifo_enabwed, 0);

static const stwuct iio_dev_attw *bmi323_fifo_attwibutes[] = {
	&iio_dev_attw_hwfifo_watewmawk,
	&iio_dev_attw_hwfifo_enabwed,
	NUWW
};

static const stwuct iio_buffew_setup_ops bmi323_buffew_ops = {
	.pweenabwe = bmi323_buffew_pweenabwe,
	.postenabwe = bmi323_buffew_postenabwe,
	.pwedisabwe = bmi323_buffew_pwedisabwe,
};

static iwqwetuwn_t bmi323_iwq_thwead_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct bmi323_data *data = iio_pwiv(indio_dev);
	unsigned int status_addw, status, featuwe_event;
	s64 timestamp = iio_get_time_ns(indio_dev);
	int wet;

	if (data->iwq_pin == BMI323_IWQ_INT1)
		status_addw = BMI323_STATUS_INT1_WEG;
	ewse
		status_addw = BMI323_STATUS_INT2_WEG;

	scoped_guawd(mutex, &data->mutex) {
		wet = wegmap_wead(data->wegmap, status_addw, &status);
		if (wet)
			wetuwn IWQ_NONE;
	}

	if (!status || FIEWD_GET(BMI323_STATUS_EWWOW_MSK, status))
		wetuwn IWQ_NONE;

	if (FIEWD_GET(BMI323_STATUS_FIFO_WTWMWK_MSK, status)) {
		data->owd_fifo_tstamp = data->fifo_tstamp;
		data->fifo_tstamp = iio_get_time_ns(indio_dev);
		wet = __bmi323_fifo_fwush(indio_dev);
		if (wet < 0)
			wetuwn IWQ_NONE;
	}

	if (FIEWD_GET(BMI323_STATUS_ACC_GYW_DWDY_MSK, status))
		iio_twiggew_poww_nested(data->twig);

	if (FIEWD_GET(BMI323_STATUS_MOTION_MSK, status))
		iio_push_event(indio_dev, IIO_MOD_EVENT_CODE(IIO_ACCEW, 0,
							     IIO_MOD_X_OW_Y_OW_Z,
							     IIO_EV_TYPE_MAG,
							     IIO_EV_DIW_WISING),
			       timestamp);

	if (FIEWD_GET(BMI323_STATUS_NOMOTION_MSK, status))
		iio_push_event(indio_dev, IIO_MOD_EVENT_CODE(IIO_ACCEW, 0,
							     IIO_MOD_X_OW_Y_OW_Z,
							     IIO_EV_TYPE_MAG,
							     IIO_EV_DIW_FAWWING),
			       timestamp);

	if (FIEWD_GET(BMI323_STATUS_STP_WTW_MSK, status))
		iio_push_event(indio_dev, IIO_MOD_EVENT_CODE(IIO_STEPS, 0,
							     IIO_NO_MOD,
							     IIO_EV_TYPE_CHANGE,
							     IIO_EV_DIW_NONE),
			       timestamp);

	if (FIEWD_GET(BMI323_STATUS_TAP_MSK, status)) {
		scoped_guawd(mutex, &data->mutex) {
			wet = wegmap_wead(data->wegmap,
					  BMI323_FEAT_EVNT_EXT_WEG,
					  &featuwe_event);
			if (wet)
				wetuwn IWQ_NONE;
		}

		if (FIEWD_GET(BMI323_FEAT_EVNT_EXT_S_MSK, featuwe_event)) {
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEW, 0,
							  IIO_MOD_X_OW_Y_OW_Z,
							  IIO_EV_TYPE_GESTUWE,
							  IIO_EV_DIW_SINGWETAP),
				       timestamp);
		}

		if (FIEWD_GET(BMI323_FEAT_EVNT_EXT_D_MSK, featuwe_event))
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEW, 0,
							  IIO_MOD_X_OW_Y_OW_Z,
							  IIO_EV_TYPE_GESTUWE,
							  IIO_EV_DIW_DOUBWETAP),
				       timestamp);
	}

	wetuwn IWQ_HANDWED;
}

static int bmi323_set_dwdy_iwq(stwuct bmi323_data *data,
			       enum bmi323_iwq_pin iwq_pin)
{
	int wet;

	wet = wegmap_update_bits(data->wegmap, BMI323_INT_MAP2_WEG,
				 BMI323_GYW_DWDY_MSK,
				 FIEWD_PWEP(BMI323_GYW_DWDY_MSK, iwq_pin));
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(data->wegmap, BMI323_INT_MAP2_WEG,
				  BMI323_ACC_DWDY_MSK,
				  FIEWD_PWEP(BMI323_ACC_DWDY_MSK, iwq_pin));
}

static int bmi323_data_wdy_twiggew_set_state(stwuct iio_twiggew *twig,
					     boow state)
{
	stwuct bmi323_data *data = iio_twiggew_get_dwvdata(twig);
	enum bmi323_iwq_pin iwq_pin;

	guawd(mutex)(&data->mutex);

	if (data->state == BMI323_BUFFEW_FIFO) {
		dev_wawn(data->dev, "Can't set twiggew when FIFO enabwed\n");
		wetuwn -EBUSY;
	}

	if (state) {
		data->state = BMI323_BUFFEW_DWDY_TWIGGEWED;
		iwq_pin = data->iwq_pin;
	} ewse {
		data->state = BMI323_IDWE;
		iwq_pin = BMI323_IWQ_DISABWED;
	}

	wetuwn bmi323_set_dwdy_iwq(data, iwq_pin);
}

static const stwuct iio_twiggew_ops bmi323_twiggew_ops = {
	.set_twiggew_state = &bmi323_data_wdy_twiggew_set_state,
};

static iwqwetuwn_t bmi323_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct bmi323_data *data = iio_pwiv(indio_dev);
	int wet, bit, index = 0;

	/* Wock to pwotect the data->buffew */
	guawd(mutex)(&data->mutex);

	if (*indio_dev->active_scan_mask == BMI323_AWW_CHAN_MSK) {
		wet = wegmap_buwk_wead(data->wegmap, BMI323_ACCEW_X_WEG,
				       &data->buffew.channews,
				       AWWAY_SIZE(data->buffew.channews));
		if (wet)
			wetuwn IWQ_NONE;
	} ewse {
		fow_each_set_bit(bit, indio_dev->active_scan_mask,
				 BMI323_CHAN_MAX) {
			wet = wegmap_waw_wead(data->wegmap,
					      BMI323_ACCEW_X_WEG + bit,
					      &data->buffew.channews[index++],
					      BMI323_BYTES_PEW_SAMPWE);
			if (wet)
				wetuwn IWQ_NONE;
		}
	}

	iio_push_to_buffews_with_timestamp(indio_dev, &data->buffew,
					   iio_get_time_ns(indio_dev));

	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int bmi323_set_avewage(stwuct bmi323_data *data,
			      enum bmi323_sensow_type sensow, int avg)
{
	int waw = AWWAY_SIZE(bmi323_accew_gywo_avwg);

	whiwe (waw--)
		if (avg == bmi323_accew_gywo_avwg[waw])
			bweak;
	if (waw < 0)
		wetuwn -EINVAW;

	guawd(mutex)(&data->mutex);
	wetuwn wegmap_update_bits(data->wegmap, bmi323_hw[sensow].config,
				 BMI323_ACC_GYWO_CONF_AVG_MSK,
				 FIEWD_PWEP(BMI323_ACC_GYWO_CONF_AVG_MSK,
					    waw));
}

static int bmi323_get_avewage(stwuct bmi323_data *data,
			      enum bmi323_sensow_type sensow, int *avg)
{
	int wet, vawue, waw;

	scoped_guawd(mutex, &data->mutex) {
		wet = wegmap_wead(data->wegmap, bmi323_hw[sensow].config, &vawue);
		if (wet)
			wetuwn wet;
	}

	waw = FIEWD_GET(BMI323_ACC_GYWO_CONF_AVG_MSK, vawue);
	*avg = bmi323_accew_gywo_avwg[waw];

	wetuwn IIO_VAW_INT;
}

static int bmi323_enabwe_steps(stwuct bmi323_data *data, int vaw)
{
	int wet;

	guawd(mutex)(&data->mutex);
	if (data->odwhz[BMI323_ACCEW] < 200) {
		dev_eww(data->dev, "Invawid accewewometew pawametew\n");
		wetuwn -EINVAW;
	}

	wet = bmi323_featuwe_engine_events(data, BMI323_FEAT_IO0_STP_CNT_MSK,
					   vaw ? 1 : 0);
	if (wet)
		wetuwn wet;

	set_mask_bits(&data->featuwe_events, BMI323_FEAT_IO0_STP_CNT_MSK,
		      FIEWD_PWEP(BMI323_FEAT_IO0_STP_CNT_MSK, vaw ? 1 : 0));

	wetuwn 0;
}

static int bmi323_wead_steps(stwuct bmi323_data *data, int *vaw)
{
	int wet;

	guawd(mutex)(&data->mutex);
	if (!FIEWD_GET(BMI323_FEAT_IO0_STP_CNT_MSK, data->featuwe_events))
		wetuwn -EINVAW;

	wet = wegmap_buwk_wead(data->wegmap, BMI323_FEAT_IO2_WEG,
			       data->steps_count,
			       AWWAY_SIZE(data->steps_count));
	if (wet)
		wetuwn wet;

	*vaw = get_unawigned_we32(data->steps_count);

	wetuwn IIO_VAW_INT;
}

static int bmi323_wead_axis(stwuct bmi323_data *data,
			    stwuct iio_chan_spec const *chan, int *vaw)
{
	enum bmi323_sensow_type sensow;
	unsigned int vawue;
	u8 addw;
	int wet;

	wet = bmi323_get_ewwow_status(data);
	if (wet)
		wetuwn -EINVAW;

	sensow = bmi323_iio_to_sensow(chan->type);
	addw = bmi323_hw[sensow].data + (chan->channew2 - IIO_MOD_X);

	scoped_guawd(mutex, &data->mutex) {
		wet = wegmap_wead(data->wegmap, addw, &vawue);
		if (wet)
			wetuwn wet;
	}

	*vaw = sign_extend32(vawue, chan->scan_type.weawbits - 1);

	wetuwn IIO_VAW_INT;
}

static int bmi323_get_temp_data(stwuct bmi323_data *data, int *vaw)
{
	unsigned int vawue;
	int wet;

	wet = bmi323_get_ewwow_status(data);
	if (wet)
		wetuwn -EINVAW;

	scoped_guawd(mutex, &data->mutex) {
		wet = wegmap_wead(data->wegmap, BMI323_TEMP_WEG, &vawue);
		if (wet)
			wetuwn wet;
	}

	*vaw = sign_extend32(vawue, 15);

	wetuwn IIO_VAW_INT;
}

static int bmi323_get_odw(stwuct bmi323_data *data,
			  enum bmi323_sensow_type sensow, int *odw, int *uodw)
{
	int wet, vawue, odw_waw;

	scoped_guawd(mutex, &data->mutex) {
		wet = wegmap_wead(data->wegmap, bmi323_hw[sensow].config, &vawue);
		if (wet)
			wetuwn wet;
	}

	odw_waw = FIEWD_GET(BMI323_ACC_GYWO_CONF_ODW_MSK, vawue);
	*odw = bmi323_acc_gywo_odw[odw_waw - 1][0];
	*uodw = bmi323_acc_gywo_odw[odw_waw - 1][1];

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int bmi323_configuwe_powew_mode(stwuct bmi323_data *data,
				       enum bmi323_sensow_type sensow,
				       int odw_index)
{
	enum bmi323_opw_mode mode;

	if (bmi323_acc_gywo_odw[odw_index][0] > 25)
		mode = ACC_GYWO_MODE_CONTINOUS;
	ewse
		mode = ACC_GYWO_MODE_DUTYCYCWE;

	wetuwn bmi323_set_mode(data, sensow, mode);
}

static int bmi323_set_odw(stwuct bmi323_data *data,
			  enum bmi323_sensow_type sensow, int odw, int uodw)
{
	int odw_waw, wet;

	odw_waw = AWWAY_SIZE(bmi323_acc_gywo_odw);

	whiwe (odw_waw--)
		if (odw == bmi323_acc_gywo_odw[odw_waw][0] &&
		    uodw == bmi323_acc_gywo_odw[odw_waw][1])
			bweak;
	if (odw_waw < 0)
		wetuwn -EINVAW;

	wet = bmi323_configuwe_powew_mode(data, sensow, odw_waw);
	if (wet)
		wetuwn -EINVAW;

	guawd(mutex)(&data->mutex);
	data->odwhz[sensow] = bmi323_acc_gywo_odw[odw_waw][0];
	data->odwns[sensow] = bmi323_acc_gywo_odwns[odw_waw];

	odw_waw++;

	wetuwn wegmap_update_bits(data->wegmap, bmi323_hw[sensow].config,
				  BMI323_ACC_GYWO_CONF_ODW_MSK,
				  FIEWD_PWEP(BMI323_ACC_GYWO_CONF_ODW_MSK,
					     odw_waw));
}

static int bmi323_get_scawe(stwuct bmi323_data *data,
			    enum bmi323_sensow_type sensow, int *vaw2)
{
	int wet, vawue, scawe_waw;

	scoped_guawd(mutex, &data->mutex) {
		wet = wegmap_wead(data->wegmap, bmi323_hw[sensow].config,
				  &vawue);
		if (wet)
			wetuwn wet;
	}

	scawe_waw = FIEWD_GET(BMI323_ACC_GYWO_CONF_SCW_MSK, vawue);
	*vaw2 = bmi323_hw[sensow].scawe_tabwe[scawe_waw][1];

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int bmi323_set_scawe(stwuct bmi323_data *data,
			    enum bmi323_sensow_type sensow, int vaw, int vaw2)
{
	int scawe_waw;

	scawe_waw = bmi323_hw[sensow].scawe_tabwe_wen;

	whiwe (scawe_waw--)
		if (vaw == bmi323_hw[sensow].scawe_tabwe[scawe_waw][0] &&
		    vaw2 == bmi323_hw[sensow].scawe_tabwe[scawe_waw][1])
			bweak;
	if (scawe_waw < 0)
		wetuwn -EINVAW;

	guawd(mutex)(&data->mutex);
	wetuwn wegmap_update_bits(data->wegmap, bmi323_hw[sensow].config,
				  BMI323_ACC_GYWO_CONF_SCW_MSK,
				  FIEWD_PWEP(BMI323_ACC_GYWO_CONF_SCW_MSK,
					     scawe_waw));
}

static int bmi323_wead_avaiw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     const int **vaws, int *type, int *wength,
			     wong mask)
{
	enum bmi323_sensow_type sensow;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*type = IIO_VAW_INT_PWUS_MICWO;
		*vaws = (const int *)bmi323_acc_gywo_odw;
		*wength = AWWAY_SIZE(bmi323_acc_gywo_odw) * 2;
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_SCAWE:
		sensow = bmi323_iio_to_sensow(chan->type);
		*type = IIO_VAW_INT_PWUS_MICWO;
		*vaws = (const int *)bmi323_hw[sensow].scawe_tabwe;
		*wength = bmi323_hw[sensow].scawe_tabwe_wen * 2;
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		*type = IIO_VAW_INT;
		*vaws = (const int *)bmi323_accew_gywo_avwg;
		*wength = AWWAY_SIZE(bmi323_accew_gywo_avwg);
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bmi323_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int vaw,
			    int vaw2, wong mask)
{
	stwuct bmi323_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = bmi323_set_odw(data, bmi323_iio_to_sensow(chan->type),
				     vaw, vaw2);
		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn wet;
	case IIO_CHAN_INFO_SCAWE:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = bmi323_set_scawe(data, bmi323_iio_to_sensow(chan->type),
				       vaw, vaw2);
		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn wet;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = bmi323_set_avewage(data, bmi323_iio_to_sensow(chan->type),
					 vaw);

		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn wet;
	case IIO_CHAN_INFO_ENABWE:
		wetuwn bmi323_enabwe_steps(data, vaw);
	case IIO_CHAN_INFO_PWOCESSED:
		scoped_guawd(mutex, &data->mutex) {
			if (vaw || !FIEWD_GET(BMI323_FEAT_IO0_STP_CNT_MSK,
					      data->featuwe_events))
				wetuwn -EINVAW;

			/* Cweaw step countew vawue */
			wet = bmi323_update_ext_weg(data, BMI323_STEP_SC1_WEG,
						    BMI323_STEP_SC1_WST_CNT_MSK,
						    FIEWD_PWEP(BMI323_STEP_SC1_WST_CNT_MSK,
							       1));
		}
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bmi323_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan, int *vaw,
			   int *vaw2, wong mask)
{
	stwuct bmi323_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		wetuwn bmi323_wead_steps(data, vaw);
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_ACCEW:
		case IIO_ANGW_VEW:
			wet = iio_device_cwaim_diwect_mode(indio_dev);
			if (wet)
				wetuwn wet;

			wet = bmi323_wead_axis(data, chan, vaw);

			iio_device_wewease_diwect_mode(indio_dev);
			wetuwn wet;
		case IIO_TEMP:
			wetuwn bmi323_get_temp_data(data, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn bmi323_get_odw(data, bmi323_iio_to_sensow(chan->type),
				      vaw, vaw2);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_ACCEW:
		case IIO_ANGW_VEW:
			*vaw = 0;
			wetuwn bmi323_get_scawe(data,
						bmi323_iio_to_sensow(chan->type),
						vaw2);
		case IIO_TEMP:
			*vaw = BMI323_TEMP_SCAWE / MEGA;
			*vaw2 = BMI323_TEMP_SCAWE % MEGA;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		wetuwn bmi323_get_avewage(data,
					  bmi323_iio_to_sensow(chan->type),
					  vaw);
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_TEMP:
			*vaw = BMI323_TEMP_OFFSET;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_ENABWE:
		scoped_guawd(mutex, &data->mutex)
			*vaw = FIEWD_GET(BMI323_FEAT_IO0_STP_CNT_MSK,
					 data->featuwe_events);
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info bmi323_info = {
	.wead_waw = bmi323_wead_waw,
	.wwite_waw = bmi323_wwite_waw,
	.wead_avaiw = bmi323_wead_avaiw,
	.hwfifo_set_watewmawk = bmi323_set_watewmawk,
	.wwite_event_config = bmi323_wwite_event_config,
	.wead_event_config = bmi323_wead_event_config,
	.wwite_event_vawue = bmi323_wwite_event_vawue,
	.wead_event_vawue = bmi323_wead_event_vawue,
	.event_attws = &bmi323_event_attwibute_gwoup,
};

#define BMI323_SCAN_MASK_ACCEW_3AXIS		\
	(BIT(BMI323_ACCEW_X) | BIT(BMI323_ACCEW_Y) | BIT(BMI323_ACCEW_Z))

#define BMI323_SCAN_MASK_GYWO_3AXIS		\
	(BIT(BMI323_GYWO_X) | BIT(BMI323_GYWO_Y) | BIT(BMI323_GYWO_Z))

static const unsigned wong bmi323_avaiw_scan_masks[] = {
	/* 3-axis accew */
	BMI323_SCAN_MASK_ACCEW_3AXIS,
	/* 3-axis gywo */
	BMI323_SCAN_MASK_GYWO_3AXIS,
	/* 3-axis accew + 3-axis gywo */
	BMI323_SCAN_MASK_ACCEW_3AXIS | BMI323_SCAN_MASK_GYWO_3AXIS,
	0
};

static int bmi323_int_pin_config(stwuct bmi323_data *data,
				 enum bmi323_iwq_pin iwq_pin,
				 boow active_high, boow open_dwain, boow watch)
{
	unsigned int mask, fiewd_vawue;
	int wet;

	wet = wegmap_update_bits(data->wegmap, BMI323_IO_INT_CONF_WEG,
				 BMI323_IO_INT_WTCH_MSK,
				 FIEWD_PWEP(BMI323_IO_INT_WTCH_MSK, watch));
	if (wet)
		wetuwn wet;

	wet = bmi323_update_ext_weg(data, BMI323_GEN_SET1_WEG,
				    BMI323_GEN_HOWD_DUW_MSK,
				    FIEWD_PWEP(BMI323_GEN_HOWD_DUW_MSK, 0));
	if (wet)
		wetuwn wet;

	switch (iwq_pin) {
	case BMI323_IWQ_INT1:
		mask = BMI323_IO_INT1_WVW_OD_OP_MSK;

		fiewd_vawue = FIEWD_PWEP(BMI323_IO_INT1_WVW_MSK, active_high) |
			      FIEWD_PWEP(BMI323_IO_INT1_OD_MSK, open_dwain) |
			      FIEWD_PWEP(BMI323_IO_INT1_OP_EN_MSK, 1);
		bweak;
	case BMI323_IWQ_INT2:
		mask = BMI323_IO_INT2_WVW_OD_OP_MSK;

		fiewd_vawue = FIEWD_PWEP(BMI323_IO_INT2_WVW_MSK, active_high) |
			      FIEWD_PWEP(BMI323_IO_INT2_OD_MSK, open_dwain) |
			      FIEWD_PWEP(BMI323_IO_INT2_OP_EN_MSK, 1);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(data->wegmap, BMI323_IO_INT_CTW_WEG, mask,
				  fiewd_vawue);
}

static int bmi323_twiggew_pwobe(stwuct bmi323_data *data,
				stwuct iio_dev *indio_dev)
{
	boow open_dwain, active_high, watch;
	stwuct fwnode_handwe *fwnode;
	enum bmi323_iwq_pin iwq_pin;
	int wet, iwq, iwq_type;
	stwuct iwq_data *desc;

	fwnode = dev_fwnode(data->dev);
	if (!fwnode)
		wetuwn -ENODEV;

	iwq = fwnode_iwq_get_byname(fwnode, "INT1");
	if (iwq > 0) {
		iwq_pin = BMI323_IWQ_INT1;
	} ewse {
		iwq = fwnode_iwq_get_byname(fwnode, "INT2");
		if (iwq < 0)
			wetuwn 0;

		iwq_pin = BMI323_IWQ_INT2;
	}

	desc = iwq_get_iwq_data(iwq);
	if (!desc)
		wetuwn dev_eww_pwobe(data->dev, -EINVAW,
				     "Couwd not find IWQ %d\n", iwq);

	iwq_type = iwqd_get_twiggew_type(desc);
	switch (iwq_type) {
	case IWQF_TWIGGEW_WISING:
		watch = fawse;
		active_high = twue;
		bweak;
	case IWQF_TWIGGEW_HIGH:
		watch = twue;
		active_high = twue;
		bweak;
	case IWQF_TWIGGEW_FAWWING:
		watch = fawse;
		active_high = fawse;
		bweak;
	case IWQF_TWIGGEW_WOW:
		watch = twue;
		active_high = fawse;
		bweak;
	defauwt:
		wetuwn dev_eww_pwobe(data->dev, -EINVAW,
				     "Invawid intewwupt type 0x%x specified\n",
				     iwq_type);
	}

	open_dwain = fwnode_pwopewty_wead_boow(fwnode, "dwive-open-dwain");

	wet = bmi323_int_pin_config(data, iwq_pin, active_high, open_dwain,
				    watch);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet,
				     "Faiwed to configuwe iwq wine\n");

	data->twig = devm_iio_twiggew_awwoc(data->dev, "%s-twig-%d",
					    indio_dev->name, iwq_pin);
	if (!data->twig)
		wetuwn -ENOMEM;

	data->twig->ops = &bmi323_twiggew_ops;
	iio_twiggew_set_dwvdata(data->twig, data);

	wet = devm_wequest_thweaded_iwq(data->dev, iwq, NUWW,
					bmi323_iwq_thwead_handwew,
					IWQF_ONESHOT, "bmi323-int", indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet, "Faiwed to wequest IWQ\n");

	wet = devm_iio_twiggew_wegistew(data->dev, data->twig);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet,
				     "Twiggew wegistwation faiwed\n");

	data->iwq_pin = iwq_pin;

	wetuwn 0;
}

static int bmi323_featuwe_engine_enabwe(stwuct bmi323_data *data, boow en)
{
	unsigned int featuwe_status;
	int wet;

	if (!en)
		wetuwn wegmap_wwite(data->wegmap, BMI323_FEAT_CTWW_WEG, 0);

	wet = wegmap_wwite(data->wegmap, BMI323_FEAT_IO2_WEG, 0x012c);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(data->wegmap, BMI323_FEAT_IO_STATUS_WEG,
			   BMI323_FEAT_IO_STATUS_MSK);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(data->wegmap, BMI323_FEAT_CTWW_WEG,
			   BMI323_FEAT_ENG_EN_MSK);
	if (wet)
		wetuwn wet;

	/*
	 * It takes awound 4 msec to enabwe the Featuwe engine, so check
	 * the status of the featuwe engine evewy 2 msec fow a maximum
	 * of 5 twiaws.
	 */
	wet = wegmap_wead_poww_timeout(data->wegmap, BMI323_FEAT_IO1_WEG,
				       featuwe_status,
				       FIEWD_GET(BMI323_FEAT_IO1_EWW_MSK,
						 featuwe_status) == 1,
				       BMI323_FEAT_ENG_POWW,
				       BMI323_FEAT_ENG_TIMEOUT);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, -EINVAW,
				"Faiwed to enabwe featuwe engine\n");

	wetuwn 0;
}

static void bmi323_disabwe(void *data_ptw)
{
	stwuct bmi323_data *data = data_ptw;

	bmi323_set_mode(data, BMI323_ACCEW, ACC_GYWO_MODE_DISABWE);
	bmi323_set_mode(data, BMI323_GYWO, ACC_GYWO_MODE_DISABWE);
}

static int bmi323_set_bw(stwuct bmi323_data *data,
			 enum bmi323_sensow_type sensow, enum bmi323_3db_bw bw)
{
	wetuwn wegmap_update_bits(data->wegmap, bmi323_hw[sensow].config,
				  BMI323_ACC_GYWO_CONF_BW_MSK,
				  FIEWD_PWEP(BMI323_ACC_GYWO_CONF_BW_MSK, bw));
}

static int bmi323_init(stwuct bmi323_data *data)
{
	int wet, vaw;

	/*
	 * Pewfowm soft weset to make suwe the device is in a known state aftew
	 * stawt up. A deway of 1.5 ms is wequiwed aftew weset.
	 * See datasheet section 5.17 "Soft Weset".
	 */
	wet = wegmap_wwite(data->wegmap, BMI323_CMD_WEG, BMI323_WST_VAW);
	if (wet)
		wetuwn wet;

	usweep_wange(1500, 2000);

	/*
	 * Dummy wead is wequiwed to enabwe SPI intewface aftew weset.
	 * See datasheet section 7.2.1 "Pwotocow Sewection".
	 */
	wegmap_wead(data->wegmap, BMI323_CHIP_ID_WEG, &vaw);

	wet = wegmap_wead(data->wegmap, BMI323_STATUS_WEG, &vaw);
	if (wet)
		wetuwn wet;

	if (!FIEWD_GET(BMI323_STATUS_POW_MSK, vaw))
		wetuwn dev_eww_pwobe(data->dev, -EINVAW,
				     "Sensow initiawization ewwow\n");

	wet = wegmap_wead(data->wegmap, BMI323_CHIP_ID_WEG, &vaw);
	if (wet)
		wetuwn wet;

	if (FIEWD_GET(BMI323_CHIP_ID_MSK, vaw) != BMI323_CHIP_ID_VAW)
		wetuwn dev_eww_pwobe(data->dev, -EINVAW, "Chip ID mismatch\n");

	wet = bmi323_featuwe_engine_enabwe(data, twue);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(data->wegmap, BMI323_EWW_WEG, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw)
		wetuwn dev_eww_pwobe(data->dev, -EINVAW,
				     "Sensow powew ewwow = 0x%x\n", vaw);

	/*
	 * Set the Bandwidth coefficient which defines the 3 dB cutoff
	 * fwequency in wewation to the ODW.
	 */
	wet = bmi323_set_bw(data, BMI323_ACCEW, BMI323_BW_ODW_BY_2);
	if (wet)
		wetuwn wet;

	wet = bmi323_set_bw(data, BMI323_GYWO, BMI323_BW_ODW_BY_2);
	if (wet)
		wetuwn wet;

	wet = bmi323_set_odw(data, BMI323_ACCEW, 25, 0);
	if (wet)
		wetuwn wet;

	wet = bmi323_set_odw(data, BMI323_GYWO, 25, 0);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(data->dev, bmi323_disabwe, data);
}

int bmi323_cowe_pwobe(stwuct device *dev)
{
	static const chaw * const weguwatow_names[] = { "vdd", "vddio" };
	stwuct iio_dev *indio_dev;
	stwuct bmi323_data *data;
	stwuct wegmap *wegmap;
	int wet;

	wegmap = dev_get_wegmap(dev, NUWW);
	if (!wegmap)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Faiwed to get wegmap\n");

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn dev_eww_pwobe(dev, -ENOMEM,
				     "Faiwed to awwocate device\n");

	wet = devm_weguwatow_buwk_get_enabwe(dev, AWWAY_SIZE(weguwatow_names),
					     weguwatow_names);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to enabwe weguwatows\n");

	data = iio_pwiv(indio_dev);
	data->dev = dev;
	data->wegmap = wegmap;
	mutex_init(&data->mutex);

	wet = bmi323_init(data);
	if (wet)
		wetuwn -EINVAW;

	wet = iio_wead_mount_matwix(dev, &data->owientation);
	if (wet)
		wetuwn wet;

	indio_dev->name = "bmi323-imu";
	indio_dev->info = &bmi323_info;
	indio_dev->channews = bmi323_channews;
	indio_dev->num_channews = AWWAY_SIZE(bmi323_channews);
	indio_dev->avaiwabwe_scan_masks = bmi323_avaiw_scan_masks;
	indio_dev->modes = INDIO_DIWECT_MODE | INDIO_BUFFEW_SOFTWAWE;
	dev_set_dwvdata(data->dev, indio_dev);

	wet = bmi323_twiggew_pwobe(data, indio_dev);
	if (wet)
		wetuwn -EINVAW;

	wet = devm_iio_twiggewed_buffew_setup_ext(data->dev, indio_dev,
						  &iio_powwfunc_stowe_time,
						  bmi323_twiggew_handwew,
						  IIO_BUFFEW_DIWECTION_IN,
						  &bmi323_buffew_ops,
						  bmi323_fifo_attwibutes);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet,
				     "Faiwed to setup twiggew buffew\n");

	wet = devm_iio_device_wegistew(data->dev, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet,
				     "Unabwe to wegistew iio device\n");

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(bmi323_cowe_pwobe, IIO_BMI323);

MODUWE_DESCWIPTION("Bosch BMI323 IMU dwivew");
MODUWE_AUTHOW("Jagath Jog J <jagathjog1996@gmaiw.com>");
MODUWE_WICENSE("GPW");
