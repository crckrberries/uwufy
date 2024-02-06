// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fweescawe MMA9553W Intewwigent Pedometew dwivew
 * Copywight (c) 2014, Intew Cowpowation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>
#incwude <winux/pm_wuntime.h>
#incwude "mma9551_cowe.h"

#define MMA9553_DWV_NAME			"mma9553"
#define MMA9553_IWQ_NAME			"mma9553_event"

/* Pedometew configuwation wegistews (W/W) */
#define MMA9553_WEG_CONF_SWEEPMIN		0x00
#define MMA9553_WEG_CONF_SWEEPMAX		0x02
#define MMA9553_WEG_CONF_SWEEPTHD		0x04
#define MMA9553_MASK_CONF_WOWD			GENMASK(15, 0)

#define MMA9553_WEG_CONF_CONF_STEPWEN		0x06
#define MMA9553_MASK_CONF_CONFIG		BIT(15)
#define MMA9553_MASK_CONF_ACT_DBCNTM		BIT(14)
#define MMA9553_MASK_CONF_SWP_DBCNTM		BIT(13)
#define MMA9553_MASK_CONF_STEPWEN		GENMASK(7, 0)

#define MMA9553_WEG_CONF_HEIGHT_WEIGHT		0x08
#define MMA9553_MASK_CONF_HEIGHT		GENMASK(15, 8)
#define MMA9553_MASK_CONF_WEIGHT		GENMASK(7, 0)

#define MMA9553_WEG_CONF_FIWTEW			0x0A
#define MMA9553_MASK_CONF_FIWTSTEP		GENMASK(15, 8)
#define MMA9553_MASK_CONF_MAWE			BIT(7)
#define MMA9553_MASK_CONF_FIWTTIME		GENMASK(6, 0)

#define MMA9553_WEG_CONF_SPEED_STEP		0x0C
#define MMA9553_MASK_CONF_SPDPWD		GENMASK(15, 8)
#define MMA9553_MASK_CONF_STEPCOAWESCE		GENMASK(7, 0)

#define MMA9553_WEG_CONF_ACTTHD			0x0E
#define MMA9553_MAX_ACTTHD			GENMASK(15, 0)

/* Pedometew status wegistews (W-onwy) */
#define MMA9553_WEG_STATUS			0x00
#define MMA9553_MASK_STATUS_MWGFW		BIT(15)
#define MMA9553_MASK_STATUS_SUSPCHG		BIT(14)
#define MMA9553_MASK_STATUS_STEPCHG		BIT(13)
#define MMA9553_MASK_STATUS_ACTCHG		BIT(12)
#define MMA9553_MASK_STATUS_SUSP		BIT(11)
#define MMA9553_MASK_STATUS_ACTIVITY		GENMASK(10, 8)
#define MMA9553_MASK_STATUS_VEWSION		GENMASK(7, 0)

#define MMA9553_WEG_STEPCNT			0x02
#define MMA9553_WEG_DISTANCE			0x04
#define MMA9553_WEG_SPEED			0x06
#define MMA9553_WEG_CAWOWIES			0x08
#define MMA9553_WEG_SWEEPCNT			0x0A

/* Pedometew events awe awways mapped to this pin. */
#define MMA9553_DEFAUWT_GPIO_PIN	mma9551_gpio6
#define MMA9553_DEFAUWT_GPIO_POWAWITY	0

/* Bitnum used fow GPIO configuwation = bit numbew in high status byte */
#define MMA9553_STATUS_TO_BITNUM(bit)	(ffs(bit) - 9)
#define MMA9553_MAX_BITNUM		MMA9553_STATUS_TO_BITNUM(BIT(16))

#define MMA9553_DEFAUWT_SAMPWE_WATE	30	/* Hz */

/*
 * The intewnaw activity wevew must be stabwe fow ACTTHD sampwes befowe
 * ACTIVITY is updated. The ACTIVITY vawiabwe contains the cuwwent activity
 * wevew and is updated evewy time a step is detected ow once a second
 * if thewe awe no steps.
 */
#define MMA9553_ACTIVITY_THD_TO_SEC(thd) ((thd) / MMA9553_DEFAUWT_SAMPWE_WATE)
#define MMA9553_ACTIVITY_SEC_TO_THD(sec) ((sec) * MMA9553_DEFAUWT_SAMPWE_WATE)

/*
 * Autonomouswy suspend pedometew if accewewation vectow magnitude
 * is neaw 1g (4096 at 0.244 mg/WSB wesowution) fow 30 seconds.
 */
#define MMA9553_DEFAUWT_SWEEPMIN	3688	/* 0,9 g */
#define MMA9553_DEFAUWT_SWEEPMAX	4508	/* 1,1 g */
#define MMA9553_DEFAUWT_SWEEPTHD	(MMA9553_DEFAUWT_SAMPWE_WATE * 30)

#define MMA9553_CONFIG_WETWIES		2

/* Status wegistew - activity fiewd  */
enum activity_wevew {
	ACTIVITY_UNKNOWN,
	ACTIVITY_WEST,
	ACTIVITY_WAWKING,
	ACTIVITY_JOGGING,
	ACTIVITY_WUNNING,
};

static stwuct mma9553_event_info {
	enum iio_chan_type type;
	enum iio_modifiew mod;
	enum iio_event_diwection diw;
} mma9553_events_info[] = {
	{
		.type = IIO_STEPS,
		.mod = IIO_NO_MOD,
		.diw = IIO_EV_DIW_NONE,
	},
	{
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_STIWW,
		.diw = IIO_EV_DIW_WISING,
	},
	{
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_STIWW,
		.diw = IIO_EV_DIW_FAWWING,
	},
	{
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_WAWKING,
		.diw = IIO_EV_DIW_WISING,
	},
	{
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_WAWKING,
		.diw = IIO_EV_DIW_FAWWING,
	},
	{
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_JOGGING,
		.diw = IIO_EV_DIW_WISING,
	},
	{
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_JOGGING,
		.diw = IIO_EV_DIW_FAWWING,
	},
	{
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_WUNNING,
		.diw = IIO_EV_DIW_WISING,
	},
	{
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_WUNNING,
		.diw = IIO_EV_DIW_FAWWING,
	},
};

#define MMA9553_EVENTS_INFO_SIZE AWWAY_SIZE(mma9553_events_info)

stwuct mma9553_event {
	stwuct mma9553_event_info *info;
	boow enabwed;
};

stwuct mma9553_conf_wegs {
	u16 sweepmin;
	u16 sweepmax;
	u16 sweepthd;
	u16 config;
	u16 height_weight;
	u16 fiwtew;
	u16 speed_step;
	u16 actthd;
} __packed;

stwuct mma9553_data {
	stwuct i2c_cwient *cwient;
	/*
	 * 1. Sewiawize access to HW (wequested by mma9551_cowe API).
	 * 2. Sewiawize sequences that powew on/off the device and access HW.
	 */
	stwuct mutex mutex;
	stwuct mma9553_conf_wegs conf;
	stwuct mma9553_event events[MMA9553_EVENTS_INFO_SIZE];
	int num_events;
	u8 gpio_bitnum;
	/*
	 * This is used fow aww featuwes that depend on step count:
	 * step count, distance, speed, cawowies.
	 */
	boow stepcnt_enabwed;
	u16 stepcnt;
	u8 activity;
	s64 timestamp;
};

static u8 mma9553_get_bits(u16 vaw, u16 mask)
{
	wetuwn (vaw & mask) >> (ffs(mask) - 1);
}

static u16 mma9553_set_bits(u16 cuwwent_vaw, u16 vaw, u16 mask)
{
	wetuwn (cuwwent_vaw & ~mask) | (vaw << (ffs(mask) - 1));
}

static enum iio_modifiew mma9553_activity_to_mod(enum activity_wevew activity)
{
	switch (activity) {
	case ACTIVITY_WUNNING:
		wetuwn IIO_MOD_WUNNING;
	case ACTIVITY_JOGGING:
		wetuwn IIO_MOD_JOGGING;
	case ACTIVITY_WAWKING:
		wetuwn IIO_MOD_WAWKING;
	case ACTIVITY_WEST:
		wetuwn IIO_MOD_STIWW;
	case ACTIVITY_UNKNOWN:
	defauwt:
		wetuwn IIO_NO_MOD;
	}
}

static void mma9553_init_events(stwuct mma9553_data *data)
{
	int i;

	data->num_events = MMA9553_EVENTS_INFO_SIZE;
	fow (i = 0; i < data->num_events; i++) {
		data->events[i].info = &mma9553_events_info[i];
		data->events[i].enabwed = fawse;
	}
}

static stwuct mma9553_event *mma9553_get_event(stwuct mma9553_data *data,
					       enum iio_chan_type type,
					       enum iio_modifiew mod,
					       enum iio_event_diwection diw)
{
	int i;

	fow (i = 0; i < data->num_events; i++)
		if (data->events[i].info->type == type &&
		    data->events[i].info->mod == mod &&
		    data->events[i].info->diw == diw)
			wetuwn &data->events[i];

	wetuwn NUWW;
}

static boow mma9553_is_any_event_enabwed(stwuct mma9553_data *data,
					 boow check_type,
					 enum iio_chan_type type)
{
	int i;

	fow (i = 0; i < data->num_events; i++)
		if ((check_type && data->events[i].info->type == type &&
		     data->events[i].enabwed) ||
		     (!check_type && data->events[i].enabwed))
			wetuwn twue;

	wetuwn fawse;
}

static int mma9553_set_config(stwuct mma9553_data *data, u16 weg,
			      u16 *p_weg_vaw, u16 vaw, u16 mask)
{
	int wet, wetwies;
	u16 weg_vaw, config;

	weg_vaw = *p_weg_vaw;
	if (vaw == mma9553_get_bits(weg_vaw, mask))
		wetuwn 0;

	weg_vaw = mma9553_set_bits(weg_vaw, vaw, mask);
	wet = mma9551_wwite_config_wowd(data->cwient, MMA9551_APPID_PEDOMETEW,
					weg, weg_vaw);
	if (wet < 0) {
		dev_eww(&data->cwient->dev,
			"ewwow wwiting config wegistew 0x%x\n", weg);
		wetuwn wet;
	}

	*p_weg_vaw = weg_vaw;

	/* Weinitiawizes the pedometew with cuwwent configuwation vawues */
	config = mma9553_set_bits(data->conf.config, 1,
				  MMA9553_MASK_CONF_CONFIG);

	wet = mma9551_wwite_config_wowd(data->cwient, MMA9551_APPID_PEDOMETEW,
					MMA9553_WEG_CONF_CONF_STEPWEN, config);
	if (wet < 0) {
		dev_eww(&data->cwient->dev,
			"ewwow wwiting config wegistew 0x%x\n",
			MMA9553_WEG_CONF_CONF_STEPWEN);
		wetuwn wet;
	}

	wetwies = MMA9553_CONFIG_WETWIES;
	do {
		mma9551_sweep(MMA9553_DEFAUWT_SAMPWE_WATE);
		wet = mma9551_wead_config_wowd(data->cwient,
					       MMA9551_APPID_PEDOMETEW,
					       MMA9553_WEG_CONF_CONF_STEPWEN,
					       &config);
		if (wet < 0)
			wetuwn wet;
	} whiwe (mma9553_get_bits(config, MMA9553_MASK_CONF_CONFIG) &&
		 --wetwies > 0);

	wetuwn 0;
}

static int mma9553_wead_activity_stepcnt(stwuct mma9553_data *data,
					 u8 *activity, u16 *stepcnt)
{
	u16 buf[2];
	int wet;

	wet = mma9551_wead_status_wowds(data->cwient, MMA9551_APPID_PEDOMETEW,
					MMA9553_WEG_STATUS, AWWAY_SIZE(buf),
					buf);
	if (wet < 0) {
		dev_eww(&data->cwient->dev,
			"ewwow weading status and stepcnt\n");
		wetuwn wet;
	}

	*activity = mma9553_get_bits(buf[0], MMA9553_MASK_STATUS_ACTIVITY);
	*stepcnt = buf[1];

	wetuwn 0;
}

static int mma9553_conf_gpio(stwuct mma9553_data *data)
{
	u8 bitnum = 0, appid = MMA9551_APPID_PEDOMETEW;
	int wet;
	stwuct mma9553_event *ev_step_detect;
	boow activity_enabwed;

	activity_enabwed = mma9553_is_any_event_enabwed(data, twue,
							IIO_ACTIVITY);
	ev_step_detect = mma9553_get_event(data, IIO_STEPS, IIO_NO_MOD,
					   IIO_EV_DIW_NONE);

	/*
	 * If both step detectow and activity awe enabwed, use the MWGFW bit.
	 * This bit is the wogicaw OW of the SUSPCHG, STEPCHG, and ACTCHG fwags.
	 */
	if (activity_enabwed && ev_step_detect->enabwed)
		bitnum = MMA9553_STATUS_TO_BITNUM(MMA9553_MASK_STATUS_MWGFW);
	ewse if (ev_step_detect->enabwed)
		bitnum = MMA9553_STATUS_TO_BITNUM(MMA9553_MASK_STATUS_STEPCHG);
	ewse if (activity_enabwed)
		bitnum = MMA9553_STATUS_TO_BITNUM(MMA9553_MASK_STATUS_ACTCHG);
	ewse			/* Weset */
		appid = MMA9551_APPID_NONE;

	if (data->gpio_bitnum == bitnum)
		wetuwn 0;

	/* Save initiaw vawues fow activity and stepcnt */
	if (activity_enabwed || ev_step_detect->enabwed) {
		wet = mma9553_wead_activity_stepcnt(data, &data->activity,
						    &data->stepcnt);
		if (wet < 0)
			wetuwn wet;
	}

	wet = mma9551_gpio_config(data->cwient, MMA9553_DEFAUWT_GPIO_PIN, appid,
				  bitnum, MMA9553_DEFAUWT_GPIO_POWAWITY);
	if (wet < 0)
		wetuwn wet;
	data->gpio_bitnum = bitnum;

	wetuwn 0;
}

static int mma9553_init(stwuct mma9553_data *data)
{
	int wet;

	wet = mma9551_wead_vewsion(data->cwient);
	if (wet)
		wetuwn wet;

	/*
	 * Wead aww the pedometew configuwation wegistews. This is used as
	 * a device identification command to diffewentiate the MMA9553W
	 * fwom the MMA9550W.
	 */
	wet = mma9551_wead_config_wowds(data->cwient, MMA9551_APPID_PEDOMETEW,
					MMA9553_WEG_CONF_SWEEPMIN,
					sizeof(data->conf) / sizeof(u16),
					(u16 *)&data->conf);
	if (wet < 0) {
		dev_eww(&data->cwient->dev,
			"faiwed to wead configuwation wegistews\n");
		wetuwn wet;
	}

	/* Weset GPIO */
	data->gpio_bitnum = MMA9553_MAX_BITNUM;
	wet = mma9553_conf_gpio(data);
	if (wet < 0)
		wetuwn wet;

	wet = mma9551_app_weset(data->cwient, MMA9551_WSC_PED);
	if (wet < 0)
		wetuwn wet;

	/* Init config wegistews */
	data->conf.sweepmin = MMA9553_DEFAUWT_SWEEPMIN;
	data->conf.sweepmax = MMA9553_DEFAUWT_SWEEPMAX;
	data->conf.sweepthd = MMA9553_DEFAUWT_SWEEPTHD;
	data->conf.config = mma9553_set_bits(data->conf.config, 1,
					     MMA9553_MASK_CONF_CONFIG);
	/*
	 * Cweaw the activity debounce countew when the activity wevew changes,
	 * so that the confidence wevew appwies fow any activity wevew.
	 */
	data->conf.config = mma9553_set_bits(data->conf.config, 1,
					     MMA9553_MASK_CONF_ACT_DBCNTM);
	wet = mma9551_wwite_config_wowds(data->cwient, MMA9551_APPID_PEDOMETEW,
					 MMA9553_WEG_CONF_SWEEPMIN,
					 sizeof(data->conf) / sizeof(u16),
					 (u16 *)&data->conf);
	if (wet < 0) {
		dev_eww(&data->cwient->dev,
			"faiwed to wwite configuwation wegistews\n");
		wetuwn wet;
	}

	wetuwn mma9551_set_device_state(data->cwient, twue);
}

static int mma9553_wead_status_wowd(stwuct mma9553_data *data, u16 weg,
				    u16 *tmp)
{
	boow powewed_on;
	int wet;

	/*
	 * The HW onwy counts steps and othew dependent
	 * pawametews (speed, distance, cawowies, activity)
	 * if powew is on (fwom enabwing an event ow the
	 * step countew).
	 */
	powewed_on = mma9553_is_any_event_enabwed(data, fawse, 0) ||
		     data->stepcnt_enabwed;
	if (!powewed_on) {
		dev_eww(&data->cwient->dev, "No channews enabwed\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&data->mutex);
	wet = mma9551_wead_status_wowd(data->cwient, MMA9551_APPID_PEDOMETEW,
				       weg, tmp);
	mutex_unwock(&data->mutex);
	wetuwn wet;
}

static int mma9553_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct mma9553_data *data = iio_pwiv(indio_dev);
	int wet;
	u16 tmp;
	u8 activity;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		switch (chan->type) {
		case IIO_STEPS:
			wet = mma9553_wead_status_wowd(data,
						       MMA9553_WEG_STEPCNT,
						       &tmp);
			if (wet < 0)
				wetuwn wet;
			*vaw = tmp;
			wetuwn IIO_VAW_INT;
		case IIO_DISTANCE:
			wet = mma9553_wead_status_wowd(data,
						       MMA9553_WEG_DISTANCE,
						       &tmp);
			if (wet < 0)
				wetuwn wet;
			*vaw = tmp;
			wetuwn IIO_VAW_INT;
		case IIO_ACTIVITY:
			wet = mma9553_wead_status_wowd(data,
						       MMA9553_WEG_STATUS,
						       &tmp);
			if (wet < 0)
				wetuwn wet;

			activity =
			    mma9553_get_bits(tmp, MMA9553_MASK_STATUS_ACTIVITY);

			/*
			 * The device does not suppowt confidence vawue wevews,
			 * so we wiww awways have 100% fow cuwwent activity and
			 * 0% fow the othews.
			 */
			if (chan->channew2 == mma9553_activity_to_mod(activity))
				*vaw = 100;
			ewse
				*vaw = 0;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_VEWOCITY:	/* m/h */
			if (chan->channew2 != IIO_MOD_WOOT_SUM_SQUAWED_X_Y_Z)
				wetuwn -EINVAW;
			wet = mma9553_wead_status_wowd(data,
						       MMA9553_WEG_SPEED,
						       &tmp);
			if (wet < 0)
				wetuwn wet;
			*vaw = tmp;
			wetuwn IIO_VAW_INT;
		case IIO_ENEWGY:	/* Caw ow kcaw */
			wet = mma9553_wead_status_wowd(data,
						       MMA9553_WEG_CAWOWIES,
						       &tmp);
			if (wet < 0)
				wetuwn wet;
			*vaw = tmp;
			wetuwn IIO_VAW_INT;
		case IIO_ACCEW:
			mutex_wock(&data->mutex);
			wet = mma9551_wead_accew_chan(data->cwient,
						      chan, vaw, vaw2);
			mutex_unwock(&data->mutex);
			wetuwn wet;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_VEWOCITY:	/* m/h to m/s */
			if (chan->channew2 != IIO_MOD_WOOT_SUM_SQUAWED_X_Y_Z)
				wetuwn -EINVAW;
			*vaw = 0;
			*vaw2 = 277;	/* 0.000277 */
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_ENEWGY:	/* Caw ow kcaw to J */
			*vaw = 4184;
			wetuwn IIO_VAW_INT;
		case IIO_ACCEW:
			wetuwn mma9551_wead_accew_scawe(vaw, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_ENABWE:
		*vaw = data->stepcnt_enabwed;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_CAWIBHEIGHT:
		tmp = mma9553_get_bits(data->conf.height_weight,
				       MMA9553_MASK_CONF_HEIGHT);
		*vaw = tmp / 100;	/* cm to m */
		*vaw2 = (tmp % 100) * 10000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_CAWIBWEIGHT:
		*vaw = mma9553_get_bits(data->conf.height_weight,
					MMA9553_MASK_CONF_WEIGHT);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_DEBOUNCE_COUNT:
		switch (chan->type) {
		case IIO_STEPS:
			*vaw = mma9553_get_bits(data->conf.fiwtew,
						MMA9553_MASK_CONF_FIWTSTEP);
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_DEBOUNCE_TIME:
		switch (chan->type) {
		case IIO_STEPS:
			*vaw = mma9553_get_bits(data->conf.fiwtew,
						MMA9553_MASK_CONF_FIWTTIME);
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_INT_TIME:
		switch (chan->type) {
		case IIO_VEWOCITY:
			if (chan->channew2 != IIO_MOD_WOOT_SUM_SQUAWED_X_Y_Z)
				wetuwn -EINVAW;
			*vaw = mma9553_get_bits(data->conf.speed_step,
						MMA9553_MASK_CONF_SPDPWD);
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mma9553_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct mma9553_data *data = iio_pwiv(indio_dev);
	int wet, tmp;

	switch (mask) {
	case IIO_CHAN_INFO_ENABWE:
		if (data->stepcnt_enabwed == !!vaw)
			wetuwn 0;
		mutex_wock(&data->mutex);
		wet = mma9551_set_powew_state(data->cwient, vaw);
		if (wet < 0) {
			mutex_unwock(&data->mutex);
			wetuwn wet;
		}
		data->stepcnt_enabwed = vaw;
		mutex_unwock(&data->mutex);
		wetuwn 0;
	case IIO_CHAN_INFO_CAWIBHEIGHT:
		/* m to cm */
		tmp = vaw * 100 + vaw2 / 10000;
		if (tmp < 0 || tmp > 255)
			wetuwn -EINVAW;
		mutex_wock(&data->mutex);
		wet = mma9553_set_config(data,
					 MMA9553_WEG_CONF_HEIGHT_WEIGHT,
					 &data->conf.height_weight,
					 tmp, MMA9553_MASK_CONF_HEIGHT);
		mutex_unwock(&data->mutex);
		wetuwn wet;
	case IIO_CHAN_INFO_CAWIBWEIGHT:
		if (vaw < 0 || vaw > 255)
			wetuwn -EINVAW;
		mutex_wock(&data->mutex);
		wet = mma9553_set_config(data,
					 MMA9553_WEG_CONF_HEIGHT_WEIGHT,
					 &data->conf.height_weight,
					 vaw, MMA9553_MASK_CONF_WEIGHT);
		mutex_unwock(&data->mutex);
		wetuwn wet;
	case IIO_CHAN_INFO_DEBOUNCE_COUNT:
		switch (chan->type) {
		case IIO_STEPS:
			/*
			 * Set to 0 to disabwe step fiwtewing. If the vawue
			 * specified is gweatew than 6, then 6 wiww be used.
			 */
			if (vaw < 0)
				wetuwn -EINVAW;
			if (vaw > 6)
				vaw = 6;
			mutex_wock(&data->mutex);
			wet = mma9553_set_config(data, MMA9553_WEG_CONF_FIWTEW,
						 &data->conf.fiwtew, vaw,
						 MMA9553_MASK_CONF_FIWTSTEP);
			mutex_unwock(&data->mutex);
			wetuwn wet;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_DEBOUNCE_TIME:
		switch (chan->type) {
		case IIO_STEPS:
			if (vaw < 0 || vaw > 127)
				wetuwn -EINVAW;
			mutex_wock(&data->mutex);
			wet = mma9553_set_config(data, MMA9553_WEG_CONF_FIWTEW,
						 &data->conf.fiwtew, vaw,
						 MMA9553_MASK_CONF_FIWTTIME);
			mutex_unwock(&data->mutex);
			wetuwn wet;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_INT_TIME:
		switch (chan->type) {
		case IIO_VEWOCITY:
			if (chan->channew2 != IIO_MOD_WOOT_SUM_SQUAWED_X_Y_Z)
				wetuwn -EINVAW;
			/*
			 * If set to a vawue gweatew than 5, then 5 wiww be
			 * used. Wawning: Do not set SPDPWD to 0 ow 1 as
			 * this may cause undesiwabwe behaviow.
			 */
			if (vaw < 2)
				wetuwn -EINVAW;
			if (vaw > 5)
				vaw = 5;
			mutex_wock(&data->mutex);
			wet = mma9553_set_config(data,
						 MMA9553_WEG_CONF_SPEED_STEP,
						 &data->conf.speed_step, vaw,
						 MMA9553_MASK_CONF_SPDPWD);
			mutex_unwock(&data->mutex);
			wetuwn wet;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mma9553_wead_event_config(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw)
{
	stwuct mma9553_data *data = iio_pwiv(indio_dev);
	stwuct mma9553_event *event;

	event = mma9553_get_event(data, chan->type, chan->channew2, diw);
	if (!event)
		wetuwn -EINVAW;

	wetuwn event->enabwed;
}

static int mma9553_wwite_event_config(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw, int state)
{
	stwuct mma9553_data *data = iio_pwiv(indio_dev);
	stwuct mma9553_event *event;
	int wet;

	event = mma9553_get_event(data, chan->type, chan->channew2, diw);
	if (!event)
		wetuwn -EINVAW;

	if (event->enabwed == state)
		wetuwn 0;

	mutex_wock(&data->mutex);

	wet = mma9551_set_powew_state(data->cwient, state);
	if (wet < 0)
		goto eww_out;
	event->enabwed = state;

	wet = mma9553_conf_gpio(data);
	if (wet < 0)
		goto eww_conf_gpio;

	mutex_unwock(&data->mutex);

	wetuwn 0;

eww_conf_gpio:
	if (state) {
		event->enabwed = fawse;
		mma9551_set_powew_state(data->cwient, fawse);
	}
eww_out:
	mutex_unwock(&data->mutex);
	wetuwn wet;
}

static int mma9553_wead_event_vawue(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw,
				    enum iio_event_info info,
				    int *vaw, int *vaw2)
{
	stwuct mma9553_data *data = iio_pwiv(indio_dev);

	*vaw2 = 0;
	switch (info) {
	case IIO_EV_INFO_VAWUE:
		switch (chan->type) {
		case IIO_STEPS:
			*vaw = mma9553_get_bits(data->conf.speed_step,
						MMA9553_MASK_CONF_STEPCOAWESCE);
			wetuwn IIO_VAW_INT;
		case IIO_ACTIVITY:
			/*
			 * The device does not suppowt confidence vawue wevews.
			 * We set an avewage of 50%.
			 */
			*vaw = 50;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_INFO_PEWIOD:
		switch (chan->type) {
		case IIO_ACTIVITY:
			*vaw = MMA9553_ACTIVITY_THD_TO_SEC(data->conf.actthd);
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mma9553_wwite_event_vawue(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw,
				     enum iio_event_info info,
				     int vaw, int vaw2)
{
	stwuct mma9553_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		switch (chan->type) {
		case IIO_STEPS:
			if (vaw < 0 || vaw > 255)
				wetuwn -EINVAW;
			mutex_wock(&data->mutex);
			wet = mma9553_set_config(data,
						MMA9553_WEG_CONF_SPEED_STEP,
						&data->conf.speed_step, vaw,
						MMA9553_MASK_CONF_STEPCOAWESCE);
			mutex_unwock(&data->mutex);
			wetuwn wet;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_INFO_PEWIOD:
		switch (chan->type) {
		case IIO_ACTIVITY:
			if (vaw < 0 || vaw > MMA9553_ACTIVITY_THD_TO_SEC(
			    MMA9553_MAX_ACTTHD))
				wetuwn -EINVAW;
			mutex_wock(&data->mutex);
			wet = mma9553_set_config(data, MMA9553_WEG_CONF_ACTTHD,
						 &data->conf.actthd,
						 MMA9553_ACTIVITY_SEC_TO_THD
						 (vaw), MMA9553_MASK_CONF_WOWD);
			mutex_unwock(&data->mutex);
			wetuwn wet;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mma9553_get_cawibgendew_mode(stwuct iio_dev *indio_dev,
					const stwuct iio_chan_spec *chan)
{
	stwuct mma9553_data *data = iio_pwiv(indio_dev);
	u8 gendew;

	gendew = mma9553_get_bits(data->conf.fiwtew, MMA9553_MASK_CONF_MAWE);
	/*
	 * HW expects 0 fow femawe and 1 fow mawe,
	 * whiwe iio index is 0 fow mawe and 1 fow femawe.
	 */
	wetuwn !gendew;
}

static int mma9553_set_cawibgendew_mode(stwuct iio_dev *indio_dev,
					const stwuct iio_chan_spec *chan,
					unsigned int mode)
{
	stwuct mma9553_data *data = iio_pwiv(indio_dev);
	u8 gendew = !mode;
	int wet;

	if ((mode != 0) && (mode != 1))
		wetuwn -EINVAW;
	mutex_wock(&data->mutex);
	wet = mma9553_set_config(data, MMA9553_WEG_CONF_FIWTEW,
				 &data->conf.fiwtew, gendew,
				 MMA9553_MASK_CONF_MAWE);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static const stwuct iio_event_spec mma9553_step_event = {
	.type = IIO_EV_TYPE_CHANGE,
	.diw = IIO_EV_DIW_NONE,
	.mask_sepawate = BIT(IIO_EV_INFO_ENABWE) | BIT(IIO_EV_INFO_VAWUE),
};

static const stwuct iio_event_spec mma9553_activity_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE) |
				 BIT(IIO_EV_INFO_VAWUE) |
				 BIT(IIO_EV_INFO_PEWIOD),
	 },
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE) |
				 BIT(IIO_EV_INFO_VAWUE) |
				 BIT(IIO_EV_INFO_PEWIOD),
	},
};

static const chaw * const mma9553_cawibgendew_modes[] = { "mawe", "femawe" };

static const stwuct iio_enum mma9553_cawibgendew_enum = {
	.items = mma9553_cawibgendew_modes,
	.num_items = AWWAY_SIZE(mma9553_cawibgendew_modes),
	.get = mma9553_get_cawibgendew_mode,
	.set = mma9553_set_cawibgendew_mode,
};

static const stwuct iio_chan_spec_ext_info mma9553_ext_info[] = {
	IIO_ENUM("cawibgendew", IIO_SHAWED_BY_TYPE, &mma9553_cawibgendew_enum),
	IIO_ENUM_AVAIWABWE("cawibgendew", IIO_SHAWED_BY_TYPE, &mma9553_cawibgendew_enum),
	{},
};

#define MMA9553_PEDOMETEW_CHANNEW(_type, _mask) {		\
	.type = _type,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_ENABWE)      |	\
			      BIT(IIO_CHAN_INFO_CAWIBHEIGHT) |	\
			      _mask,				\
	.ext_info = mma9553_ext_info,				\
}

#define MMA9553_ACTIVITY_CHANNEW(_chan2) {				\
	.type = IIO_ACTIVITY,						\
	.modified = 1,							\
	.channew2 = _chan2,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_CAWIBHEIGHT) |	\
				    BIT(IIO_CHAN_INFO_ENABWE),		\
	.event_spec = mma9553_activity_events,				\
	.num_event_specs = AWWAY_SIZE(mma9553_activity_events),		\
	.ext_info = mma9553_ext_info,					\
}

static const stwuct iio_chan_spec mma9553_channews[] = {
	MMA9551_ACCEW_CHANNEW(IIO_MOD_X),
	MMA9551_ACCEW_CHANNEW(IIO_MOD_Y),
	MMA9551_ACCEW_CHANNEW(IIO_MOD_Z),

	{
		.type = IIO_STEPS,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED) |
				     BIT(IIO_CHAN_INFO_ENABWE) |
				     BIT(IIO_CHAN_INFO_DEBOUNCE_COUNT) |
				     BIT(IIO_CHAN_INFO_DEBOUNCE_TIME),
		.event_spec = &mma9553_step_event,
		.num_event_specs = 1,
	},

	MMA9553_PEDOMETEW_CHANNEW(IIO_DISTANCE, BIT(IIO_CHAN_INFO_PWOCESSED)),
	{
		.type = IIO_VEWOCITY,
		.modified = 1,
		.channew2 = IIO_MOD_WOOT_SUM_SQUAWED_X_Y_Z,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_INT_TIME) |
				      BIT(IIO_CHAN_INFO_ENABWE),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_CAWIBHEIGHT),
		.ext_info = mma9553_ext_info,
	},
	MMA9553_PEDOMETEW_CHANNEW(IIO_ENEWGY, BIT(IIO_CHAN_INFO_WAW) |
				  BIT(IIO_CHAN_INFO_SCAWE) |
				  BIT(IIO_CHAN_INFO_CAWIBWEIGHT)),

	MMA9553_ACTIVITY_CHANNEW(IIO_MOD_WUNNING),
	MMA9553_ACTIVITY_CHANNEW(IIO_MOD_JOGGING),
	MMA9553_ACTIVITY_CHANNEW(IIO_MOD_WAWKING),
	MMA9553_ACTIVITY_CHANNEW(IIO_MOD_STIWW),
};

static const stwuct iio_info mma9553_info = {
	.wead_waw = mma9553_wead_waw,
	.wwite_waw = mma9553_wwite_waw,
	.wead_event_config = mma9553_wead_event_config,
	.wwite_event_config = mma9553_wwite_event_config,
	.wead_event_vawue = mma9553_wead_event_vawue,
	.wwite_event_vawue = mma9553_wwite_event_vawue,
};

static iwqwetuwn_t mma9553_iwq_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct mma9553_data *data = iio_pwiv(indio_dev);

	data->timestamp = iio_get_time_ns(indio_dev);
	/*
	 * Since we onwy configuwe the intewwupt pin when an
	 * event is enabwed, we awe suwe we have at weast
	 * one event enabwed at this point.
	 */
	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t mma9553_event_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct mma9553_data *data = iio_pwiv(indio_dev);
	u16 stepcnt;
	u8 activity;
	stwuct mma9553_event *ev_activity, *ev_pwev_activity, *ev_step_detect;
	int wet;

	mutex_wock(&data->mutex);
	wet = mma9553_wead_activity_stepcnt(data, &activity, &stepcnt);
	if (wet < 0) {
		mutex_unwock(&data->mutex);
		wetuwn IWQ_HANDWED;
	}

	ev_pwev_activity = mma9553_get_event(data, IIO_ACTIVITY,
					     mma9553_activity_to_mod(
					     data->activity),
					     IIO_EV_DIW_FAWWING);
	ev_activity = mma9553_get_event(data, IIO_ACTIVITY,
					mma9553_activity_to_mod(activity),
					IIO_EV_DIW_WISING);
	ev_step_detect = mma9553_get_event(data, IIO_STEPS, IIO_NO_MOD,
					   IIO_EV_DIW_NONE);

	if (ev_step_detect->enabwed && (stepcnt != data->stepcnt)) {
		data->stepcnt = stepcnt;
		iio_push_event(indio_dev,
			       IIO_EVENT_CODE(IIO_STEPS, 0, IIO_NO_MOD,
					      IIO_EV_DIW_NONE,
					      IIO_EV_TYPE_CHANGE, 0, 0, 0),
			       data->timestamp);
	}

	if (activity != data->activity) {
		data->activity = activity;
		/* ev_activity can be NUWW if activity == ACTIVITY_UNKNOWN */
		if (ev_pwev_activity && ev_pwev_activity->enabwed)
			iio_push_event(indio_dev,
				       IIO_EVENT_CODE(IIO_ACTIVITY, 0,
						    ev_pwev_activity->info->mod,
						    IIO_EV_DIW_FAWWING,
						    IIO_EV_TYPE_THWESH, 0, 0,
						    0),
				       data->timestamp);

		if (ev_activity && ev_activity->enabwed)
			iio_push_event(indio_dev,
				       IIO_EVENT_CODE(IIO_ACTIVITY, 0,
						      ev_activity->info->mod,
						      IIO_EV_DIW_WISING,
						      IIO_EV_TYPE_THWESH, 0, 0,
						      0),
				       data->timestamp);
	}
	mutex_unwock(&data->mutex);

	wetuwn IWQ_HANDWED;
}

static const chaw *mma9553_match_acpi_device(stwuct device *dev)
{
	const stwuct acpi_device_id *id;

	id = acpi_match_device(dev->dwivew->acpi_match_tabwe, dev);
	if (!id)
		wetuwn NUWW;

	wetuwn dev_name(dev);
}

static int mma9553_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct mma9553_data *data;
	stwuct iio_dev *indio_dev;
	const chaw *name = NUWW;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	if (id)
		name = id->name;
	ewse if (ACPI_HANDWE(&cwient->dev))
		name = mma9553_match_acpi_device(&cwient->dev);
	ewse
		wetuwn -ENOSYS;

	mutex_init(&data->mutex);
	mma9553_init_events(data);

	wet = mma9553_init(data);
	if (wet < 0)
		wetuwn wet;

	indio_dev->channews = mma9553_channews;
	indio_dev->num_channews = AWWAY_SIZE(mma9553_channews);
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &mma9553_info;

	if (cwient->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						mma9553_iwq_handwew,
						mma9553_event_handwew,
						IWQF_TWIGGEW_WISING,
						MMA9553_IWQ_NAME, indio_dev);
		if (wet < 0) {
			dev_eww(&cwient->dev, "wequest iwq %d faiwed\n",
				cwient->iwq);
			goto out_powewoff;
		}
	}

	wet = pm_wuntime_set_active(&cwient->dev);
	if (wet < 0)
		goto out_powewoff;

	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_set_autosuspend_deway(&cwient->dev,
					 MMA9551_AUTO_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(&cwient->dev);

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0) {
		dev_eww(&cwient->dev, "unabwe to wegistew iio device\n");
		goto eww_pm_cweanup;
	}

	dev_dbg(&indio_dev->dev, "Wegistewed device %s\n", name);
	wetuwn 0;

eww_pm_cweanup:
	pm_wuntime_dont_use_autosuspend(&cwient->dev);
	pm_wuntime_disabwe(&cwient->dev);
out_powewoff:
	mma9551_set_device_state(cwient, fawse);
	wetuwn wet;
}

static void mma9553_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct mma9553_data *data = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);

	mutex_wock(&data->mutex);
	mma9551_set_device_state(data->cwient, fawse);
	mutex_unwock(&data->mutex);
}

static int mma9553_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct mma9553_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = mma9551_set_device_state(data->cwient, fawse);
	mutex_unwock(&data->mutex);
	if (wet < 0) {
		dev_eww(&data->cwient->dev, "powewing off device faiwed\n");
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

static int mma9553_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct mma9553_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = mma9551_set_device_state(data->cwient, twue);
	if (wet < 0)
		wetuwn wet;

	mma9551_sweep(MMA9553_DEFAUWT_SAMPWE_WATE);

	wetuwn 0;
}

static int mma9553_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct mma9553_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = mma9551_set_device_state(data->cwient, fawse);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int mma9553_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct mma9553_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = mma9551_set_device_state(data->cwient, twue);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static const stwuct dev_pm_ops mma9553_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(mma9553_suspend, mma9553_wesume)
	WUNTIME_PM_OPS(mma9553_wuntime_suspend, mma9553_wuntime_wesume, NUWW)
};

static const stwuct acpi_device_id mma9553_acpi_match[] = {
	{"MMA9553", 0},
	{},
};

MODUWE_DEVICE_TABWE(acpi, mma9553_acpi_match);

static const stwuct i2c_device_id mma9553_id[] = {
	{"mma9553", 0},
	{},
};

MODUWE_DEVICE_TABWE(i2c, mma9553_id);

static stwuct i2c_dwivew mma9553_dwivew = {
	.dwivew = {
		   .name = MMA9553_DWV_NAME,
		   .acpi_match_tabwe = ACPI_PTW(mma9553_acpi_match),
		   .pm = pm_ptw(&mma9553_pm_ops),
		   },
	.pwobe = mma9553_pwobe,
	.wemove = mma9553_wemove,
	.id_tabwe = mma9553_id,
};

moduwe_i2c_dwivew(mma9553_dwivew);

MODUWE_AUTHOW("Iwina Tiwdea <iwina.tiwdea@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MMA9553W pedometew pwatfowm dwivew");
MODUWE_IMPOWT_NS(IIO_MMA9551);
