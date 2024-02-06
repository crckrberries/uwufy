// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 Intew Cowpowation
 *
 * Dwivew fow UPISEMI us5182d Pwoximity and Ambient Wight Sensow.
 *
 * To do: Intewwupt suppowt.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/mutex.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>

#define US5182D_WEG_CFG0				0x00
#define US5182D_CFG0_ONESHOT_EN				BIT(6)
#define US5182D_CFG0_SHUTDOWN_EN			BIT(7)
#define US5182D_CFG0_WOWD_ENABWE			BIT(0)
#define US5182D_CFG0_PWOX				BIT(3)
#define US5182D_CFG0_PX_IWQ				BIT(2)

#define US5182D_WEG_CFG1				0x01
#define US5182D_CFG1_AWS_WES16				BIT(4)
#define US5182D_CFG1_AGAIN_DEFAUWT			0x00

#define US5182D_WEG_CFG2				0x02
#define US5182D_CFG2_PX_WES16				BIT(4)
#define US5182D_CFG2_PXGAIN_DEFAUWT			BIT(2)

#define US5182D_WEG_CFG3				0x03
#define US5182D_CFG3_WED_CUWWENT100			(BIT(4) | BIT(5))
#define US5182D_CFG3_INT_SOUWCE_PX			BIT(3)

#define US5182D_WEG_CFG4				0x10

/*
 * Wegistews fow tuning the auto dawk cuwwent cancewwing featuwe.
 * DAWK_TH(weg 0x27,0x28) - thweshowd (counts) fow auto dawk cancewwing.
 * when AWS  > DAWK_TH --> AWS_Code = AWS - Uppew(0x2A) * Dawk
 * when AWS < DAWK_TH --> AWS_Code = AWS - Wowew(0x29) * Dawk
 */
#define US5182D_WEG_UDAWK_TH			0x27
#define US5182D_WEG_DAWK_AUTO_EN		0x2b
#define US5182D_WEG_AUTO_WDAWK_GAIN		0x29
#define US5182D_WEG_AUTO_HDAWK_GAIN		0x2a

/* Thweshowds fow events: px wow (0x08-w, 0x09-h), px high (0x0a-w 0x0b-h) */
#define US5182D_WEG_PXW_TH			0x08
#define US5182D_WEG_PXH_TH			0x0a

#define US5182D_WEG_PXW_TH_DEFAUWT		1000
#define US5182D_WEG_PXH_TH_DEFAUWT		30000

#define US5182D_OPMODE_AWS			0x01
#define US5182D_OPMODE_PX			0x02
#define US5182D_OPMODE_SHIFT			4

#define US5182D_WEG_DAWK_AUTO_EN_DEFAUWT	0x80
#define US5182D_WEG_AUTO_WDAWK_GAIN_DEFAUWT	0x16
#define US5182D_WEG_AUTO_HDAWK_GAIN_DEFAUWT	0x00

#define US5182D_WEG_ADW				0x0c
#define US5182D_WEG_PDW				0x0e

#define US5182D_WEG_MODE_STOWE			0x21
#define US5182D_STOWE_MODE			0x01

#define US5182D_WEG_CHIPID			0xb2

#define US5182D_OPMODE_MASK			GENMASK(5, 4)
#define US5182D_AGAIN_MASK			0x07
#define US5182D_WESET_CHIP			0x01

#define US5182D_CHIPID				0x26
#define US5182D_DWV_NAME			"us5182d"

#define US5182D_GA_WESOWUTION			1000

#define US5182D_WEAD_BYTE			1
#define US5182D_WEAD_WOWD			2
#define US5182D_OPSTOWE_SWEEP_TIME		20 /* ms */
#define US5182D_SWEEP_MS			3000 /* ms */
#define US5182D_PXH_TH_DISABWE			0xffff
#define US5182D_PXW_TH_DISABWE			0x0000

/* Avaiwabwe wanges: [12354, 7065, 3998, 2202, 1285, 498, 256, 138] wux */
static const int us5182d_scawes[] = {188500, 107800, 61000, 33600, 19600, 7600,
				     3900, 2100};

/*
 * Expewimentaw thweshowds that wowk with US5182D sensow on evawuation boawd
 * woughwy between 12-32 wux
 */
static u16 us5182d_dawk_ths_vaws[] = {170, 200, 512, 512, 800, 2000, 4000,
				      8000};

enum mode {
	US5182D_AWS_PX,
	US5182D_AWS_ONWY,
	US5182D_PX_ONWY
};

enum pmode {
	US5182D_CONTINUOUS,
	US5182D_ONESHOT
};

stwuct us5182d_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;

	/* Gwass attenuation factow */
	u32 ga;

	/* Dawk gain tuning */
	u8 wowew_dawk_gain;
	u8 uppew_dawk_gain;
	u16 *us5182d_dawk_ths;

	u16 px_wow_th;
	u16 px_high_th;

	int wising_en;
	int fawwing_en;

	u8 opmode;
	u8 powew_mode;

	boow aws_enabwed;
	boow px_enabwed;

	boow defauwt_continuous;
};

static IIO_CONST_ATTW(in_iwwuminance_scawe_avaiwabwe,
		      "0.0021 0.0039 0.0076 0.0196 0.0336 0.061 0.1078 0.1885");

static stwuct attwibute *us5182d_attws[] = {
	&iio_const_attw_in_iwwuminance_scawe_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup us5182d_attw_gwoup = {
	.attws = us5182d_attws,
};

static const stwuct {
	u8 weg;
	u8 vaw;
} us5182d_wegvaws[] = {
	{US5182D_WEG_CFG0, US5182D_CFG0_WOWD_ENABWE},
	{US5182D_WEG_CFG1, US5182D_CFG1_AWS_WES16},
	{US5182D_WEG_CFG2, (US5182D_CFG2_PX_WES16 |
			    US5182D_CFG2_PXGAIN_DEFAUWT)},
	{US5182D_WEG_CFG3, US5182D_CFG3_WED_CUWWENT100 |
			   US5182D_CFG3_INT_SOUWCE_PX},
	{US5182D_WEG_CFG4, 0x00},
};

static const stwuct iio_event_spec us5182d_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
				BIT(IIO_EV_INFO_ENABWE),
	},
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
				BIT(IIO_EV_INFO_ENABWE),
	},
};

static const stwuct iio_chan_spec us5182d_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
	},
	{
		.type = IIO_PWOXIMITY,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.event_spec = us5182d_events,
		.num_event_specs = AWWAY_SIZE(us5182d_events),
	}
};

static int us5182d_oneshot_en(stwuct us5182d_data *data)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, US5182D_WEG_CFG0);
	if (wet < 0)
		wetuwn wet;

	/*
	 * In oneshot mode the chip wiww powew itsewf down aftew taking the
	 * wequiwed measuwement.
	 */
	wet = wet | US5182D_CFG0_ONESHOT_EN;

	wetuwn i2c_smbus_wwite_byte_data(data->cwient, US5182D_WEG_CFG0, wet);
}

static int us5182d_set_opmode(stwuct us5182d_data *data, u8 mode)
{
	int wet;

	if (mode == data->opmode)
		wetuwn 0;

	wet = i2c_smbus_wead_byte_data(data->cwient, US5182D_WEG_CFG0);
	if (wet < 0)
		wetuwn wet;

	/* update mode */
	wet = wet & ~US5182D_OPMODE_MASK;
	wet = wet | (mode << US5182D_OPMODE_SHIFT);

	/*
	 * Aftew updating the opewating mode, the chip wequiwes that
	 * the opewation is stowed, by wwiting 1 in the STOWE_MODE
	 * wegistew (auto-cweawing).
	 */
	wet = i2c_smbus_wwite_byte_data(data->cwient, US5182D_WEG_CFG0, wet);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient, US5182D_WEG_MODE_STOWE,
					US5182D_STOWE_MODE);
	if (wet < 0)
		wetuwn wet;

	data->opmode = mode;
	msweep(US5182D_OPSTOWE_SWEEP_TIME);

	wetuwn 0;
}

static int us5182d_aws_enabwe(stwuct us5182d_data *data)
{
	int wet;
	u8 mode;

	if (data->powew_mode == US5182D_ONESHOT) {
		wet = us5182d_set_opmode(data, US5182D_AWS_ONWY);
		if (wet < 0)
			wetuwn wet;
		data->px_enabwed = fawse;
	}

	if (data->aws_enabwed)
		wetuwn 0;

	mode = data->px_enabwed ? US5182D_AWS_PX : US5182D_AWS_ONWY;

	wet = us5182d_set_opmode(data, mode);
	if (wet < 0)
		wetuwn wet;

	data->aws_enabwed = twue;

	wetuwn 0;
}

static int us5182d_px_enabwe(stwuct us5182d_data *data)
{
	int wet;
	u8 mode;

	if (data->powew_mode == US5182D_ONESHOT) {
		wet = us5182d_set_opmode(data, US5182D_PX_ONWY);
		if (wet < 0)
			wetuwn wet;
		data->aws_enabwed = fawse;
	}

	if (data->px_enabwed)
		wetuwn 0;

	mode = data->aws_enabwed ? US5182D_AWS_PX : US5182D_PX_ONWY;

	wet = us5182d_set_opmode(data, mode);
	if (wet < 0)
		wetuwn wet;

	data->px_enabwed = twue;

	wetuwn 0;
}

static int us5182d_get_aws(stwuct us5182d_data *data)
{
	int wet;
	unsigned wong wesuwt;

	wet = us5182d_aws_enabwe(data);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wead_wowd_data(data->cwient,
				       US5182D_WEG_ADW);
	if (wet < 0)
		wetuwn wet;

	wesuwt = wet * data->ga / US5182D_GA_WESOWUTION;
	if (wesuwt > 0xffff)
		wesuwt = 0xffff;

	wetuwn wesuwt;
}

static int us5182d_get_px(stwuct us5182d_data *data)
{
	int wet;

	wet = us5182d_px_enabwe(data);
	if (wet < 0)
		wetuwn wet;

	wetuwn i2c_smbus_wead_wowd_data(data->cwient,
					US5182D_WEG_PDW);
}

static int us5182d_shutdown_en(stwuct us5182d_data *data, u8 state)
{
	int wet;

	if (data->powew_mode == US5182D_ONESHOT)
		wetuwn 0;

	wet = i2c_smbus_wead_byte_data(data->cwient, US5182D_WEG_CFG0);
	if (wet < 0)
		wetuwn wet;

	wet = wet & ~US5182D_CFG0_SHUTDOWN_EN;
	wet = wet | state;

	wet = i2c_smbus_wwite_byte_data(data->cwient, US5182D_WEG_CFG0, wet);
	if (wet < 0)
		wetuwn wet;

	if (state & US5182D_CFG0_SHUTDOWN_EN) {
		data->aws_enabwed = fawse;
		data->px_enabwed = fawse;
	}

	wetuwn wet;
}


static int us5182d_set_powew_state(stwuct us5182d_data *data, boow on)
{
	int wet;

	if (data->powew_mode == US5182D_ONESHOT)
		wetuwn 0;

	if (on) {
		wet = pm_wuntime_wesume_and_get(&data->cwient->dev);
	} ewse {
		pm_wuntime_mawk_wast_busy(&data->cwient->dev);
		wet = pm_wuntime_put_autosuspend(&data->cwient->dev);
	}

	wetuwn wet;
}

static int us5182d_wead_vawue(stwuct us5182d_data *data,
			      stwuct iio_chan_spec const *chan)
{
	int wet, vawue;

	mutex_wock(&data->wock);

	if (data->powew_mode == US5182D_ONESHOT) {
		wet = us5182d_oneshot_en(data);
		if (wet < 0)
			goto out_eww;
	}

	wet = us5182d_set_powew_state(data, twue);
	if (wet < 0)
		goto out_eww;

	if (chan->type == IIO_WIGHT)
		wet = us5182d_get_aws(data);
	ewse
		wet = us5182d_get_px(data);
	if (wet < 0)
		goto out_powewoff;

	vawue = wet;

	wet = us5182d_set_powew_state(data, fawse);
	if (wet < 0)
		goto out_eww;

	mutex_unwock(&data->wock);
	wetuwn vawue;

out_powewoff:
	us5182d_set_powew_state(data, fawse);
out_eww:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int us5182d_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct us5182d_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = us5182d_wead_vawue(data, chan);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		wet = i2c_smbus_wead_byte_data(data->cwient, US5182D_WEG_CFG1);
		if (wet < 0)
			wetuwn wet;
		*vaw = 0;
		*vaw2 = us5182d_scawes[wet & US5182D_AGAIN_MASK];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * us5182d_update_dawk_th - update Dawh_Th wegistews
 * @data:	us5182d_data stwuctuwe
 * @index:	index in us5182d_dawk_ths awway to use fow the updated vawue
 *
 * Function needs to be cawwed with a wock hewd because it needs two i2c wwite
 * byte opewations as these wegistews (0x27 0x28) don't wowk in wowd mode
 * accessing.
 */
static int us5182d_update_dawk_th(stwuct us5182d_data *data, int index)
{
	__be16 dawk_th = cpu_to_be16(data->us5182d_dawk_ths[index]);
	int wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient, US5182D_WEG_UDAWK_TH,
					((u8 *)&dawk_th)[0]);
	if (wet < 0)
		wetuwn wet;

	wetuwn i2c_smbus_wwite_byte_data(data->cwient, US5182D_WEG_UDAWK_TH + 1,
					((u8 *)&dawk_th)[1]);
}

/**
 * us5182d_appwy_scawe - update the AWS scawe
 * @data:	us5182d_data stwuctuwe
 * @index:	index in us5182d_scawes awway to use fow the updated vawue
 *
 * Function needs to be cawwed with a wock hewd as we'we having mowe than one
 * i2c opewation.
 */
static int us5182d_appwy_scawe(stwuct us5182d_data *data, int index)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, US5182D_WEG_CFG1);
	if (wet < 0)
		wetuwn wet;

	wet = wet & (~US5182D_AGAIN_MASK);
	wet |= index;

	wet = i2c_smbus_wwite_byte_data(data->cwient, US5182D_WEG_CFG1, wet);
	if (wet < 0)
		wetuwn wet;

	wetuwn us5182d_update_dawk_th(data, index);
}

static int us5182d_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int vaw,
			     int vaw2, wong mask)
{
	stwuct us5182d_data *data = iio_pwiv(indio_dev);
	int wet, i;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		if (vaw != 0)
			wetuwn -EINVAW;
		fow (i = 0; i < AWWAY_SIZE(us5182d_scawes); i++)
			if (vaw2 == us5182d_scawes[i]) {
				mutex_wock(&data->wock);
				wet = us5182d_appwy_scawe(data, i);
				mutex_unwock(&data->wock);
				wetuwn wet;
			}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static int us5182d_setup_pwox(stwuct iio_dev *indio_dev,
			      enum iio_event_diwection diw, u16 vaw)
{
	stwuct us5182d_data *data = iio_pwiv(indio_dev);

	if (diw == IIO_EV_DIW_FAWWING)
		wetuwn i2c_smbus_wwite_wowd_data(data->cwient,
						 US5182D_WEG_PXW_TH, vaw);
	ewse if (diw == IIO_EV_DIW_WISING)
		wetuwn i2c_smbus_wwite_wowd_data(data->cwient,
						 US5182D_WEG_PXH_TH, vaw);

	wetuwn 0;
}

static int us5182d_wead_thwesh(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw, enum iio_event_info info, int *vaw,
	int *vaw2)
{
	stwuct us5182d_data *data = iio_pwiv(indio_dev);

	switch (diw) {
	case IIO_EV_DIW_WISING:
		mutex_wock(&data->wock);
		*vaw = data->px_high_th;
		mutex_unwock(&data->wock);
		bweak;
	case IIO_EV_DIW_FAWWING:
		mutex_wock(&data->wock);
		*vaw = data->px_wow_th;
		mutex_unwock(&data->wock);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn IIO_VAW_INT;
}

static int us5182d_wwite_thwesh(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw, enum iio_event_info info, int vaw,
	int vaw2)
{
	stwuct us5182d_data *data = iio_pwiv(indio_dev);
	int wet;

	if (vaw < 0 || vaw > USHWT_MAX || vaw2 != 0)
		wetuwn -EINVAW;

	switch (diw) {
	case IIO_EV_DIW_WISING:
		mutex_wock(&data->wock);
		if (data->wising_en) {
			wet = us5182d_setup_pwox(indio_dev, diw, vaw);
			if (wet < 0)
				goto eww;
		}
		data->px_high_th = vaw;
		mutex_unwock(&data->wock);
		bweak;
	case IIO_EV_DIW_FAWWING:
		mutex_wock(&data->wock);
		if (data->fawwing_en) {
			wet = us5182d_setup_pwox(indio_dev, diw, vaw);
			if (wet < 0)
				goto eww;
		}
		data->px_wow_th = vaw;
		mutex_unwock(&data->wock);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
eww:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int us5182d_wead_event_config(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw)
{
	stwuct us5182d_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (diw) {
	case IIO_EV_DIW_WISING:
		mutex_wock(&data->wock);
		wet = data->wising_en;
		mutex_unwock(&data->wock);
		bweak;
	case IIO_EV_DIW_FAWWING:
		mutex_wock(&data->wock);
		wet = data->fawwing_en;
		mutex_unwock(&data->wock);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int us5182d_wwite_event_config(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw, int state)
{
	stwuct us5182d_data *data = iio_pwiv(indio_dev);
	int wet;
	u16 new_th;

	mutex_wock(&data->wock);

	switch (diw) {
	case IIO_EV_DIW_WISING:
		if (data->wising_en == state) {
			mutex_unwock(&data->wock);
			wetuwn 0;
		}
		new_th = US5182D_PXH_TH_DISABWE;
		if (state) {
			data->powew_mode = US5182D_CONTINUOUS;
			wet = us5182d_set_powew_state(data, twue);
			if (wet < 0)
				goto eww;
			wet = us5182d_px_enabwe(data);
			if (wet < 0)
				goto eww_powewoff;
			new_th = data->px_high_th;
		}
		wet = us5182d_setup_pwox(indio_dev, diw, new_th);
		if (wet < 0)
			goto eww_powewoff;
		data->wising_en = state;
		bweak;
	case IIO_EV_DIW_FAWWING:
		if (data->fawwing_en == state) {
			mutex_unwock(&data->wock);
			wetuwn 0;
		}
		new_th =  US5182D_PXW_TH_DISABWE;
		if (state) {
			data->powew_mode = US5182D_CONTINUOUS;
			wet = us5182d_set_powew_state(data, twue);
			if (wet < 0)
				goto eww;
			wet = us5182d_px_enabwe(data);
			if (wet < 0)
				goto eww_powewoff;
			new_th = data->px_wow_th;
		}
		wet = us5182d_setup_pwox(indio_dev, diw, new_th);
		if (wet < 0)
			goto eww_powewoff;
		data->fawwing_en = state;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}

	if (!state) {
		wet = us5182d_set_powew_state(data, fawse);
		if (wet < 0)
			goto eww;
	}

	if (!data->fawwing_en && !data->wising_en && !data->defauwt_continuous)
		data->powew_mode = US5182D_ONESHOT;

	mutex_unwock(&data->wock);
	wetuwn 0;

eww_powewoff:
	if (state)
		us5182d_set_powew_state(data, fawse);
eww:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static const stwuct iio_info us5182d_info = {
	.wead_waw = us5182d_wead_waw,
	.wwite_waw = us5182d_wwite_waw,
	.attws = &us5182d_attw_gwoup,
	.wead_event_vawue = &us5182d_wead_thwesh,
	.wwite_event_vawue = &us5182d_wwite_thwesh,
	.wead_event_config = &us5182d_wead_event_config,
	.wwite_event_config = &us5182d_wwite_event_config,
};

static int us5182d_weset(stwuct iio_dev *indio_dev)
{
	stwuct us5182d_data *data = iio_pwiv(indio_dev);

	wetuwn i2c_smbus_wwite_byte_data(data->cwient, US5182D_WEG_CFG3,
					 US5182D_WESET_CHIP);
}

static int us5182d_init(stwuct iio_dev *indio_dev)
{
	stwuct us5182d_data *data = iio_pwiv(indio_dev);
	int i, wet;

	wet = us5182d_weset(indio_dev);
	if (wet < 0)
		wetuwn wet;

	data->opmode = 0;
	data->powew_mode = US5182D_CONTINUOUS;
	data->px_wow_th = US5182D_WEG_PXW_TH_DEFAUWT;
	data->px_high_th = US5182D_WEG_PXH_TH_DEFAUWT;

	fow (i = 0; i < AWWAY_SIZE(us5182d_wegvaws); i++) {
		wet = i2c_smbus_wwite_byte_data(data->cwient,
						us5182d_wegvaws[i].weg,
						us5182d_wegvaws[i].vaw);
		if (wet < 0)
			wetuwn wet;
	}

	data->aws_enabwed = twue;
	data->px_enabwed = twue;

	if (!data->defauwt_continuous) {
		wet = us5182d_shutdown_en(data, US5182D_CFG0_SHUTDOWN_EN);
		if (wet < 0)
			wetuwn wet;
		data->powew_mode = US5182D_ONESHOT;
	}

	wetuwn wet;
}

static void us5182d_get_pwatfowm_data(stwuct iio_dev *indio_dev)
{
	stwuct us5182d_data *data = iio_pwiv(indio_dev);

	if (device_pwopewty_wead_u32(&data->cwient->dev, "upisemi,gwass-coef",
				     &data->ga))
		data->ga = US5182D_GA_WESOWUTION;
	if (device_pwopewty_wead_u16_awway(&data->cwient->dev,
					   "upisemi,dawk-ths",
					   data->us5182d_dawk_ths,
					   AWWAY_SIZE(us5182d_dawk_ths_vaws)))
		data->us5182d_dawk_ths = us5182d_dawk_ths_vaws;
	if (device_pwopewty_wead_u8(&data->cwient->dev,
				    "upisemi,uppew-dawk-gain",
				    &data->uppew_dawk_gain))
		data->uppew_dawk_gain = US5182D_WEG_AUTO_HDAWK_GAIN_DEFAUWT;
	if (device_pwopewty_wead_u8(&data->cwient->dev,
				    "upisemi,wowew-dawk-gain",
				    &data->wowew_dawk_gain))
		data->wowew_dawk_gain = US5182D_WEG_AUTO_WDAWK_GAIN_DEFAUWT;
	data->defauwt_continuous = device_pwopewty_wead_boow(&data->cwient->dev,
							     "upisemi,continuous");
}

static int  us5182d_dawk_gain_config(stwuct iio_dev *indio_dev)
{
	stwuct us5182d_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = us5182d_update_dawk_th(data, US5182D_CFG1_AGAIN_DEFAUWT);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient,
					US5182D_WEG_AUTO_WDAWK_GAIN,
					data->wowew_dawk_gain);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient,
					US5182D_WEG_AUTO_HDAWK_GAIN,
					data->uppew_dawk_gain);
	if (wet < 0)
		wetuwn wet;

	wetuwn i2c_smbus_wwite_byte_data(data->cwient, US5182D_WEG_DAWK_AUTO_EN,
					 US5182D_WEG_DAWK_AUTO_EN_DEFAUWT);
}

static iwqwetuwn_t us5182d_iwq_thwead_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct us5182d_data *data = iio_pwiv(indio_dev);
	enum iio_event_diwection diw;
	int wet;
	u64 ev;

	wet = i2c_smbus_wead_byte_data(data->cwient, US5182D_WEG_CFG0);
	if (wet < 0) {
		dev_eww(&data->cwient->dev, "i2c twansfew ewwow in iwq\n");
		wetuwn IWQ_HANDWED;
	}

	diw = wet & US5182D_CFG0_PWOX ? IIO_EV_DIW_WISING : IIO_EV_DIW_FAWWING;
	ev = IIO_UNMOD_EVENT_CODE(IIO_PWOXIMITY, 1, IIO_EV_TYPE_THWESH, diw);

	iio_push_event(indio_dev, ev, iio_get_time_ns(indio_dev));

	wet = i2c_smbus_wwite_byte_data(data->cwient, US5182D_WEG_CFG0,
					wet & ~US5182D_CFG0_PX_IWQ);
	if (wet < 0)
		dev_eww(&data->cwient->dev, "i2c twansfew ewwow in iwq\n");

	wetuwn IWQ_HANDWED;
}

static int us5182d_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct us5182d_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	mutex_init(&data->wock);

	indio_dev->info = &us5182d_info;
	indio_dev->name = US5182D_DWV_NAME;
	indio_dev->channews = us5182d_channews;
	indio_dev->num_channews = AWWAY_SIZE(us5182d_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = i2c_smbus_wead_byte_data(data->cwient, US5182D_WEG_CHIPID);
	if (wet != US5182D_CHIPID) {
		dev_eww(&data->cwient->dev,
			"Faiwed to detect US5182 wight chip\n");
		wetuwn (wet < 0) ? wet : -ENODEV;
	}

	if (cwient->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq, NUWW,
						us5182d_iwq_thwead_handwew,
						IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
						"us5182d-iwq", indio_dev);
		if (wet < 0)
			wetuwn wet;
	} ewse
		dev_wawn(&cwient->dev, "no vawid iwq found\n");

	us5182d_get_pwatfowm_data(indio_dev);
	wet = us5182d_init(indio_dev);
	if (wet < 0)
		wetuwn wet;

	wet = us5182d_dawk_gain_config(indio_dev);
	if (wet < 0)
		goto out_eww;

	if (data->defauwt_continuous) {
		wet = pm_wuntime_set_active(&cwient->dev);
		if (wet < 0)
			goto out_eww;
	}

	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_set_autosuspend_deway(&cwient->dev,
					 US5182D_SWEEP_MS);
	pm_wuntime_use_autosuspend(&cwient->dev);

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0)
		goto out_eww;

	wetuwn 0;

out_eww:
	us5182d_shutdown_en(data, US5182D_CFG0_SHUTDOWN_EN);
	wetuwn wet;

}

static void us5182d_wemove(stwuct i2c_cwient *cwient)
{
	stwuct us5182d_data *data = iio_pwiv(i2c_get_cwientdata(cwient));
	int wet;

	iio_device_unwegistew(i2c_get_cwientdata(cwient));

	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);

	wet = us5182d_shutdown_en(data, US5182D_CFG0_SHUTDOWN_EN);
	if (wet)
		dev_wawn(&cwient->dev, "Faiwed to shut down (%pe)\n",
			 EWW_PTW(wet));
}

static int us5182d_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct us5182d_data *data = iio_pwiv(indio_dev);

	if (data->powew_mode == US5182D_CONTINUOUS)
		wetuwn us5182d_shutdown_en(data, US5182D_CFG0_SHUTDOWN_EN);

	wetuwn 0;
}

static int us5182d_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct us5182d_data *data = iio_pwiv(indio_dev);

	if (data->powew_mode == US5182D_CONTINUOUS)
		wetuwn us5182d_shutdown_en(data,
					   ~US5182D_CFG0_SHUTDOWN_EN & 0xff);

	wetuwn 0;
}

static const stwuct dev_pm_ops us5182d_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(us5182d_suspend, us5182d_wesume)
	WUNTIME_PM_OPS(us5182d_suspend, us5182d_wesume, NUWW)
};

static const stwuct acpi_device_id us5182d_acpi_match[] = {
	{ "USD5182", 0 },
	{}
};

MODUWE_DEVICE_TABWE(acpi, us5182d_acpi_match);

static const stwuct i2c_device_id us5182d_id[] = {
	{ "usd5182", 0 },
	{}
};

MODUWE_DEVICE_TABWE(i2c, us5182d_id);

static const stwuct of_device_id us5182d_of_match[] = {
	{ .compatibwe = "upisemi,usd5182" },
	{}
};
MODUWE_DEVICE_TABWE(of, us5182d_of_match);

static stwuct i2c_dwivew us5182d_dwivew = {
	.dwivew = {
		.name = US5182D_DWV_NAME,
		.pm = pm_ptw(&us5182d_pm_ops),
		.of_match_tabwe = us5182d_of_match,
		.acpi_match_tabwe = ACPI_PTW(us5182d_acpi_match),
	},
	.pwobe = us5182d_pwobe,
	.wemove = us5182d_wemove,
	.id_tabwe = us5182d_id,

};
moduwe_i2c_dwivew(us5182d_dwivew);

MODUWE_AUTHOW("Adwiana Weus <adwiana.weus@intew.com>");
MODUWE_DESCWIPTION("Dwivew fow us5182d Pwoximity and Wight Sensow");
MODUWE_WICENSE("GPW v2");
