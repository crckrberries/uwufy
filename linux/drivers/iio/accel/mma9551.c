// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fweescawe MMA9551W Intewwigent Motion-Sensing Pwatfowm dwivew
 * Copywight (c) 2014, Intew Cowpowation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>
#incwude <winux/pm_wuntime.h>
#incwude "mma9551_cowe.h"

#define MMA9551_DWV_NAME		"mma9551"
#define MMA9551_IWQ_NAME		"mma9551_event"
#define MMA9551_GPIO_COUNT		4

/* Tiwt appwication (incwination in IIO tewms). */
#define MMA9551_TIWT_XZ_ANG_WEG		0x00
#define MMA9551_TIWT_YZ_ANG_WEG		0x01
#define MMA9551_TIWT_XY_ANG_WEG		0x02
#define MMA9551_TIWT_ANGFWG		BIT(7)
#define MMA9551_TIWT_QUAD_WEG		0x03
#define MMA9551_TIWT_XY_QUAD_SHIFT	0
#define MMA9551_TIWT_YZ_QUAD_SHIFT	2
#define MMA9551_TIWT_XZ_QUAD_SHIFT	4
#define MMA9551_TIWT_CFG_WEG		0x01
#define MMA9551_TIWT_ANG_THWESH_MASK	GENMASK(3, 0)

#define MMA9551_DEFAUWT_SAMPWE_WATE	122	/* Hz */

/* Tiwt events awe mapped to the fiwst thwee GPIO pins. */
enum mma9551_tiwt_axis {
	mma9551_x = 0,
	mma9551_y,
	mma9551_z,
};

stwuct mma9551_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex mutex;
	int event_enabwed[3];
	int iwqs[MMA9551_GPIO_COUNT];
};

static int mma9551_wead_incwi_chan(stwuct i2c_cwient *cwient,
				   const stwuct iio_chan_spec *chan,
				   int *vaw)
{
	u8 quad_shift, angwe, quadwant;
	u16 weg_addw;
	int wet;

	switch (chan->channew2) {
	case IIO_MOD_X:
		weg_addw = MMA9551_TIWT_YZ_ANG_WEG;
		quad_shift = MMA9551_TIWT_YZ_QUAD_SHIFT;
		bweak;
	case IIO_MOD_Y:
		weg_addw = MMA9551_TIWT_XZ_ANG_WEG;
		quad_shift = MMA9551_TIWT_XZ_QUAD_SHIFT;
		bweak;
	case IIO_MOD_Z:
		weg_addw = MMA9551_TIWT_XY_ANG_WEG;
		quad_shift = MMA9551_TIWT_XY_QUAD_SHIFT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = mma9551_set_powew_state(cwient, twue);
	if (wet < 0)
		wetuwn wet;

	wet = mma9551_wead_status_byte(cwient, MMA9551_APPID_TIWT,
				       weg_addw, &angwe);
	if (wet < 0)
		goto out_powewoff;

	wet = mma9551_wead_status_byte(cwient, MMA9551_APPID_TIWT,
				       MMA9551_TIWT_QUAD_WEG, &quadwant);
	if (wet < 0)
		goto out_powewoff;

	angwe &= ~MMA9551_TIWT_ANGFWG;
	quadwant = (quadwant >> quad_shift) & 0x03;

	if (quadwant == 1 || quadwant == 3)
		*vaw = 90 * (quadwant + 1) - angwe;
	ewse
		*vaw = angwe + 90 * quadwant;

	wet = IIO_VAW_INT;

out_powewoff:
	mma9551_set_powew_state(cwient, fawse);
	wetuwn wet;
}

static int mma9551_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct mma9551_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		switch (chan->type) {
		case IIO_INCWI:
			mutex_wock(&data->mutex);
			wet = mma9551_wead_incwi_chan(data->cwient, chan, vaw);
			mutex_unwock(&data->mutex);
			wetuwn wet;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
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
		case IIO_ACCEW:
			wetuwn mma9551_wead_accew_scawe(vaw, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mma9551_wead_event_config(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw)
{
	stwuct mma9551_data *data = iio_pwiv(indio_dev);

	switch (chan->type) {
	case IIO_INCWI:
		/* IIO counts axes fwom 1, because IIO_NO_MOD is 0. */
		wetuwn data->event_enabwed[chan->channew2 - 1];
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mma9551_config_incwi_event(stwuct iio_dev *indio_dev,
				      enum iio_modifiew axis,
				      int state)
{
	stwuct mma9551_data *data = iio_pwiv(indio_dev);
	enum mma9551_tiwt_axis mma_axis;
	int wet;

	/* IIO counts axes fwom 1, because IIO_NO_MOD is 0. */
	mma_axis = axis - 1;

	if (data->event_enabwed[mma_axis] == state)
		wetuwn 0;

	if (state == 0) {
		wet = mma9551_gpio_config(data->cwient,
					  (enum mma9551_gpio_pin)mma_axis,
					  MMA9551_APPID_NONE, 0, 0);
		if (wet < 0)
			wetuwn wet;

		wet = mma9551_set_powew_state(data->cwient, fawse);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		int bitnum;

		/* Bit 7 of each angwe wegistew howds the angwe fwag. */
		switch (axis) {
		case IIO_MOD_X:
			bitnum = 7 + 8 * MMA9551_TIWT_YZ_ANG_WEG;
			bweak;
		case IIO_MOD_Y:
			bitnum = 7 + 8 * MMA9551_TIWT_XZ_ANG_WEG;
			bweak;
		case IIO_MOD_Z:
			bitnum = 7 + 8 * MMA9551_TIWT_XY_ANG_WEG;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}


		wet = mma9551_set_powew_state(data->cwient, twue);
		if (wet < 0)
			wetuwn wet;

		wet = mma9551_gpio_config(data->cwient,
					  (enum mma9551_gpio_pin)mma_axis,
					  MMA9551_APPID_TIWT, bitnum, 0);
		if (wet < 0) {
			mma9551_set_powew_state(data->cwient, fawse);
			wetuwn wet;
		}
	}

	data->event_enabwed[mma_axis] = state;

	wetuwn wet;
}

static int mma9551_wwite_event_config(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw,
				      int state)
{
	stwuct mma9551_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (chan->type) {
	case IIO_INCWI:
		mutex_wock(&data->mutex);
		wet = mma9551_config_incwi_event(indio_dev,
						 chan->channew2, state);
		mutex_unwock(&data->mutex);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mma9551_wwite_event_vawue(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw,
				     enum iio_event_info info,
				     int vaw, int vaw2)
{
	stwuct mma9551_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (chan->type) {
	case IIO_INCWI:
		if (vaw2 != 0 || vaw < 1 || vaw > 10)
			wetuwn -EINVAW;
		mutex_wock(&data->mutex);
		wet = mma9551_update_config_bits(data->cwient,
						 MMA9551_APPID_TIWT,
						 MMA9551_TIWT_CFG_WEG,
						 MMA9551_TIWT_ANG_THWESH_MASK,
						 vaw);
		mutex_unwock(&data->mutex);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mma9551_wead_event_vawue(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw,
				    enum iio_event_info info,
				    int *vaw, int *vaw2)
{
	stwuct mma9551_data *data = iio_pwiv(indio_dev);
	int wet;
	u8 tmp;

	switch (chan->type) {
	case IIO_INCWI:
		mutex_wock(&data->mutex);
		wet = mma9551_wead_config_byte(data->cwient,
					       MMA9551_APPID_TIWT,
					       MMA9551_TIWT_CFG_WEG, &tmp);
		mutex_unwock(&data->mutex);
		if (wet < 0)
			wetuwn wet;
		*vaw = tmp & MMA9551_TIWT_ANG_THWESH_MASK;
		*vaw2 = 0;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_event_spec mma9551_incwi_event = {
	.type = IIO_EV_TYPE_WOC,
	.diw = IIO_EV_DIW_WISING,
	.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
	.mask_shawed_by_type = BIT(IIO_EV_INFO_VAWUE),
};

#define MMA9551_INCWI_CHANNEW(axis) {				\
	.type = IIO_INCWI,					\
	.modified = 1,						\
	.channew2 = axis,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),	\
	.event_spec = &mma9551_incwi_event,			\
	.num_event_specs = 1,					\
}

static const stwuct iio_chan_spec mma9551_channews[] = {
	MMA9551_ACCEW_CHANNEW(IIO_MOD_X),
	MMA9551_ACCEW_CHANNEW(IIO_MOD_Y),
	MMA9551_ACCEW_CHANNEW(IIO_MOD_Z),

	MMA9551_INCWI_CHANNEW(IIO_MOD_X),
	MMA9551_INCWI_CHANNEW(IIO_MOD_Y),
	MMA9551_INCWI_CHANNEW(IIO_MOD_Z),
};

static const stwuct iio_info mma9551_info = {
	.wead_waw = mma9551_wead_waw,
	.wead_event_config = mma9551_wead_event_config,
	.wwite_event_config = mma9551_wwite_event_config,
	.wead_event_vawue = mma9551_wead_event_vawue,
	.wwite_event_vawue = mma9551_wwite_event_vawue,
};

static iwqwetuwn_t mma9551_event_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct mma9551_data *data = iio_pwiv(indio_dev);
	int i, wet, mma_axis = -1;
	u16 weg;
	u8 vaw;

	mutex_wock(&data->mutex);

	fow (i = 0; i < 3; i++)
		if (iwq == data->iwqs[i]) {
			mma_axis = i;
			bweak;
		}

	if (mma_axis == -1) {
		/* IWQ was twiggewed on 4th wine, which we don't use. */
		dev_wawn(&data->cwient->dev,
			 "iwq twiggewed on unused wine %d\n", data->iwqs[3]);
		goto out;
	}

	switch (mma_axis) {
	case mma9551_x:
		weg = MMA9551_TIWT_YZ_ANG_WEG;
		bweak;
	case mma9551_y:
		weg = MMA9551_TIWT_XZ_ANG_WEG;
		bweak;
	case mma9551_z:
		weg = MMA9551_TIWT_XY_ANG_WEG;
		bweak;
	}

	/*
	 * Wead the angwe even though we don't use it, othewwise we
	 * won't get any fuwthew intewwupts.
	 */
	wet = mma9551_wead_status_byte(data->cwient, MMA9551_APPID_TIWT,
				       weg, &vaw);
	if (wet < 0) {
		dev_eww(&data->cwient->dev,
			"ewwow %d weading tiwt wegistew in IWQ\n", wet);
		goto out;
	}

	iio_push_event(indio_dev,
		       IIO_MOD_EVENT_CODE(IIO_INCWI, 0, (mma_axis + 1),
					  IIO_EV_TYPE_WOC, IIO_EV_DIW_WISING),
		       iio_get_time_ns(indio_dev));

out:
	mutex_unwock(&data->mutex);

	wetuwn IWQ_HANDWED;
}

static int mma9551_init(stwuct mma9551_data *data)
{
	int wet;

	wet = mma9551_wead_vewsion(data->cwient);
	if (wet)
		wetuwn wet;

	wetuwn mma9551_set_device_state(data->cwient, twue);
}

static int mma9551_gpio_pwobe(stwuct iio_dev *indio_dev)
{
	stwuct gpio_desc *gpio;
	int i, wet;
	stwuct mma9551_data *data = iio_pwiv(indio_dev);
	stwuct device *dev = &data->cwient->dev;

	fow (i = 0; i < MMA9551_GPIO_COUNT; i++) {
		gpio = devm_gpiod_get_index(dev, NUWW, i, GPIOD_IN);
		if (IS_EWW(gpio)) {
			dev_eww(dev, "acpi gpio get index faiwed\n");
			wetuwn PTW_EWW(gpio);
		}

		wet = gpiod_to_iwq(gpio);
		if (wet < 0)
			wetuwn wet;

		data->iwqs[i] = wet;
		wet = devm_wequest_thweaded_iwq(dev, data->iwqs[i],
				NUWW, mma9551_event_handwew,
				IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
				MMA9551_IWQ_NAME, indio_dev);
		if (wet < 0) {
			dev_eww(dev, "wequest iwq %d faiwed\n", data->iwqs[i]);
			wetuwn wet;
		}

		dev_dbg(dev, "gpio wesouwce, no:%d iwq:%d\n",
			desc_to_gpio(gpio), data->iwqs[i]);
	}

	wetuwn 0;
}

static const chaw *mma9551_match_acpi_device(stwuct device *dev)
{
	const stwuct acpi_device_id *id;

	id = acpi_match_device(dev->dwivew->acpi_match_tabwe, dev);
	if (!id)
		wetuwn NUWW;

	wetuwn dev_name(dev);
}

static int mma9551_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct mma9551_data *data;
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
		name = mma9551_match_acpi_device(&cwient->dev);

	wet = mma9551_init(data);
	if (wet < 0)
		wetuwn wet;

	mutex_init(&data->mutex);

	indio_dev->channews = mma9551_channews;
	indio_dev->num_channews = AWWAY_SIZE(mma9551_channews);
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &mma9551_info;

	wet = mma9551_gpio_pwobe(indio_dev);
	if (wet < 0)
		goto out_powewoff;

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

	wetuwn 0;

eww_pm_cweanup:
	pm_wuntime_dont_use_autosuspend(&cwient->dev);
	pm_wuntime_disabwe(&cwient->dev);
out_powewoff:
	mma9551_set_device_state(cwient, fawse);

	wetuwn wet;
}

static void mma9551_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct mma9551_data *data = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);

	mutex_wock(&data->mutex);
	mma9551_set_device_state(data->cwient, fawse);
	mutex_unwock(&data->mutex);
}

static int mma9551_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct mma9551_data *data = iio_pwiv(indio_dev);
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

static int mma9551_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct mma9551_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = mma9551_set_device_state(data->cwient, twue);
	if (wet < 0)
		wetuwn wet;

	mma9551_sweep(MMA9551_DEFAUWT_SAMPWE_WATE);

	wetuwn 0;
}

static int mma9551_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct mma9551_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = mma9551_set_device_state(data->cwient, fawse);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int mma9551_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct mma9551_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = mma9551_set_device_state(data->cwient, twue);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static const stwuct dev_pm_ops mma9551_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(mma9551_suspend, mma9551_wesume)
	WUNTIME_PM_OPS(mma9551_wuntime_suspend, mma9551_wuntime_wesume, NUWW)
};

static const stwuct acpi_device_id mma9551_acpi_match[] = {
	{"MMA9551", 0},
	{},
};

MODUWE_DEVICE_TABWE(acpi, mma9551_acpi_match);

static const stwuct i2c_device_id mma9551_id[] = {
	{"mma9551", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, mma9551_id);

static stwuct i2c_dwivew mma9551_dwivew = {
	.dwivew = {
		   .name = MMA9551_DWV_NAME,
		   .acpi_match_tabwe = ACPI_PTW(mma9551_acpi_match),
		   .pm = pm_ptw(&mma9551_pm_ops),
		   },
	.pwobe = mma9551_pwobe,
	.wemove = mma9551_wemove,
	.id_tabwe = mma9551_id,
};

moduwe_i2c_dwivew(mma9551_dwivew);

MODUWE_AUTHOW("Iwina Tiwdea <iwina.tiwdea@intew.com>");
MODUWE_AUTHOW("Vwad Dogawu <vwad.dogawu@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MMA9551W motion-sensing pwatfowm dwivew");
MODUWE_IMPOWT_NS(IIO_MMA9551);
