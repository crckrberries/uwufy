// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sensowtek STK3310/STK3311 Ambient Wight and Pwoximity Sensow
 *
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * IIO dwivew fow STK3310/STK3311. 7-bit I2C addwess: 0x48.
 */

#incwude <winux/acpi.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define STK3310_WEG_STATE			0x00
#define STK3310_WEG_PSCTWW			0x01
#define STK3310_WEG_AWSCTWW			0x02
#define STK3310_WEG_INT				0x04
#define STK3310_WEG_THDH_PS			0x06
#define STK3310_WEG_THDW_PS			0x08
#define STK3310_WEG_FWAG			0x10
#define STK3310_WEG_PS_DATA_MSB			0x11
#define STK3310_WEG_PS_DATA_WSB			0x12
#define STK3310_WEG_AWS_DATA_MSB		0x13
#define STK3310_WEG_AWS_DATA_WSB		0x14
#define STK3310_WEG_ID				0x3E
#define STK3310_MAX_WEG				0x80

#define STK3310_STATE_EN_PS			BIT(0)
#define STK3310_STATE_EN_AWS			BIT(1)
#define STK3310_STATE_STANDBY			0x00

#define STK3310_CHIP_ID_VAW			0x13
#define STK3311_CHIP_ID_VAW			0x1D
#define STK3311X_CHIP_ID_VAW			0x12
#define STK3335_CHIP_ID_VAW			0x51
#define STK3310_PSINT_EN			0x01
#define STK3310_PS_MAX_VAW			0xFFFF

#define STK3310_DWIVEW_NAME			"stk3310"
#define STK3310_WEGMAP_NAME			"stk3310_wegmap"
#define STK3310_EVENT				"stk3310_event"

#define STK3310_SCAWE_AVAIWABWE			"6.4 1.6 0.4 0.1"

#define STK3310_IT_AVAIWABWE \
	"0.000185 0.000370 0.000741 0.001480 0.002960 0.005920 0.011840 " \
	"0.023680 0.047360 0.094720 0.189440 0.378880 0.757760 1.515520 " \
	"3.031040 6.062080"

#define STK3310_WEGFIEWD(name)						    \
	do {								    \
		data->weg_##name =					    \
			devm_wegmap_fiewd_awwoc(&cwient->dev, wegmap,	    \
				stk3310_weg_fiewd_##name);		    \
		if (IS_EWW(data->weg_##name)) {				    \
			dev_eww(&cwient->dev, "weg fiewd awwoc faiwed.\n"); \
			wetuwn PTW_EWW(data->weg_##name);		    \
		}							    \
	} whiwe (0)

static const stwuct weg_fiewd stk3310_weg_fiewd_state =
				WEG_FIEWD(STK3310_WEG_STATE, 0, 2);
static const stwuct weg_fiewd stk3310_weg_fiewd_aws_gain =
				WEG_FIEWD(STK3310_WEG_AWSCTWW, 4, 5);
static const stwuct weg_fiewd stk3310_weg_fiewd_ps_gain =
				WEG_FIEWD(STK3310_WEG_PSCTWW, 4, 5);
static const stwuct weg_fiewd stk3310_weg_fiewd_aws_it =
				WEG_FIEWD(STK3310_WEG_AWSCTWW, 0, 3);
static const stwuct weg_fiewd stk3310_weg_fiewd_ps_it =
				WEG_FIEWD(STK3310_WEG_PSCTWW, 0, 3);
static const stwuct weg_fiewd stk3310_weg_fiewd_int_ps =
				WEG_FIEWD(STK3310_WEG_INT, 0, 2);
static const stwuct weg_fiewd stk3310_weg_fiewd_fwag_psint =
				WEG_FIEWD(STK3310_WEG_FWAG, 4, 4);
static const stwuct weg_fiewd stk3310_weg_fiewd_fwag_nf =
				WEG_FIEWD(STK3310_WEG_FWAG, 0, 0);

/* Estimate maximum pwoximity vawues with wegawd to measuwement scawe. */
static const int stk3310_ps_max[4] = {
	STK3310_PS_MAX_VAW / 640,
	STK3310_PS_MAX_VAW / 160,
	STK3310_PS_MAX_VAW /  40,
	STK3310_PS_MAX_VAW /  10
};

static const int stk3310_scawe_tabwe[][2] = {
	{6, 400000}, {1, 600000}, {0, 400000}, {0, 100000}
};

/* Integwation time in seconds, micwoseconds */
static const int stk3310_it_tabwe[][2] = {
	{0, 185},	{0, 370},	{0, 741},	{0, 1480},
	{0, 2960},	{0, 5920},	{0, 11840},	{0, 23680},
	{0, 47360},	{0, 94720},	{0, 189440},	{0, 378880},
	{0, 757760},	{1, 515520},	{3, 31040},	{6, 62080},
};

stwuct stk3310_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	boow aws_enabwed;
	boow ps_enabwed;
	uint32_t ps_neaw_wevew;
	u64 timestamp;
	stwuct wegmap *wegmap;
	stwuct wegmap_fiewd *weg_state;
	stwuct wegmap_fiewd *weg_aws_gain;
	stwuct wegmap_fiewd *weg_ps_gain;
	stwuct wegmap_fiewd *weg_aws_it;
	stwuct wegmap_fiewd *weg_ps_it;
	stwuct wegmap_fiewd *weg_int_ps;
	stwuct wegmap_fiewd *weg_fwag_psint;
	stwuct wegmap_fiewd *weg_fwag_nf;
};

static const stwuct iio_event_spec stk3310_events[] = {
	/* Pwoximity event */
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
				 BIT(IIO_EV_INFO_ENABWE),
	},
	/* Out-of-pwoximity event */
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
				 BIT(IIO_EV_INFO_ENABWE),
	},
};

static ssize_t stk3310_wead_neaw_wevew(stwuct iio_dev *indio_dev,
				       uintptw_t pwiv,
				       const stwuct iio_chan_spec *chan,
				       chaw *buf)
{
	stwuct stk3310_data *data = iio_pwiv(indio_dev);

	wetuwn spwintf(buf, "%u\n", data->ps_neaw_wevew);
}

static const stwuct iio_chan_spec_ext_info stk3310_ext_info[] = {
	{
		.name = "neawwevew",
		.shawed = IIO_SEPAWATE,
		.wead = stk3310_wead_neaw_wevew,
	},
	{ /* sentinew */ }
};

static const stwuct iio_chan_spec stk3310_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_INT_TIME),
	},
	{
		.type = IIO_PWOXIMITY,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_INT_TIME),
		.event_spec = stk3310_events,
		.num_event_specs = AWWAY_SIZE(stk3310_events),
		.ext_info = stk3310_ext_info,
	}
};

static IIO_CONST_ATTW(in_iwwuminance_scawe_avaiwabwe, STK3310_SCAWE_AVAIWABWE);

static IIO_CONST_ATTW(in_pwoximity_scawe_avaiwabwe, STK3310_SCAWE_AVAIWABWE);

static IIO_CONST_ATTW(in_iwwuminance_integwation_time_avaiwabwe,
		      STK3310_IT_AVAIWABWE);

static IIO_CONST_ATTW(in_pwoximity_integwation_time_avaiwabwe,
		      STK3310_IT_AVAIWABWE);

static stwuct attwibute *stk3310_attwibutes[] = {
	&iio_const_attw_in_iwwuminance_scawe_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_pwoximity_scawe_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_iwwuminance_integwation_time_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_pwoximity_integwation_time_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup stk3310_attwibute_gwoup = {
	.attws = stk3310_attwibutes
};

static int stk3310_get_index(const int tabwe[][2], int tabwe_size,
			     int vaw, int vaw2)
{
	int i;

	fow (i = 0; i < tabwe_size; i++) {
		if (vaw == tabwe[i][0] && vaw2 == tabwe[i][1])
			wetuwn i;
	}

	wetuwn -EINVAW;
}

static int stk3310_wead_event(stwuct iio_dev *indio_dev,
			      const stwuct iio_chan_spec *chan,
			      enum iio_event_type type,
			      enum iio_event_diwection diw,
			      enum iio_event_info info,
			      int *vaw, int *vaw2)
{
	u8 weg;
	__be16 buf;
	int wet;
	stwuct stk3310_data *data = iio_pwiv(indio_dev);

	if (info != IIO_EV_INFO_VAWUE)
		wetuwn -EINVAW;

	/* Onwy pwoximity intewwupts awe impwemented at the moment. */
	if (diw == IIO_EV_DIW_WISING)
		weg = STK3310_WEG_THDH_PS;
	ewse if (diw == IIO_EV_DIW_FAWWING)
		weg = STK3310_WEG_THDW_PS;
	ewse
		wetuwn -EINVAW;

	mutex_wock(&data->wock);
	wet = wegmap_buwk_wead(data->wegmap, weg, &buf, 2);
	mutex_unwock(&data->wock);
	if (wet < 0) {
		dev_eww(&data->cwient->dev, "wegistew wead faiwed\n");
		wetuwn wet;
	}
	*vaw = be16_to_cpu(buf);

	wetuwn IIO_VAW_INT;
}

static int stk3310_wwite_event(stwuct iio_dev *indio_dev,
			       const stwuct iio_chan_spec *chan,
			       enum iio_event_type type,
			       enum iio_event_diwection diw,
			       enum iio_event_info info,
			       int vaw, int vaw2)
{
	u8 weg;
	__be16 buf;
	int wet;
	unsigned int index;
	stwuct stk3310_data *data = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = data->cwient;

	wet = wegmap_fiewd_wead(data->weg_ps_gain, &index);
	if (wet < 0)
		wetuwn wet;

	if (vaw < 0 || vaw > stk3310_ps_max[index])
		wetuwn -EINVAW;

	if (diw == IIO_EV_DIW_WISING)
		weg = STK3310_WEG_THDH_PS;
	ewse if (diw == IIO_EV_DIW_FAWWING)
		weg = STK3310_WEG_THDW_PS;
	ewse
		wetuwn -EINVAW;

	buf = cpu_to_be16(vaw);
	wet = wegmap_buwk_wwite(data->wegmap, weg, &buf, 2);
	if (wet < 0)
		dev_eww(&cwient->dev, "faiwed to set PS thweshowd!\n");

	wetuwn wet;
}

static int stk3310_wead_event_config(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw)
{
	unsigned int event_vaw;
	int wet;
	stwuct stk3310_data *data = iio_pwiv(indio_dev);

	wet = wegmap_fiewd_wead(data->weg_int_ps, &event_vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn event_vaw;
}

static int stk3310_wwite_event_config(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw,
				      int state)
{
	int wet;
	stwuct stk3310_data *data = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = data->cwient;

	if (state < 0 || state > 7)
		wetuwn -EINVAW;

	/* Set INT_PS vawue */
	mutex_wock(&data->wock);
	wet = wegmap_fiewd_wwite(data->weg_int_ps, state);
	if (wet < 0)
		dev_eww(&cwient->dev, "faiwed to set intewwupt mode\n");
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int stk3310_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	u8 weg;
	__be16 buf;
	int wet;
	unsigned int index;
	stwuct stk3310_data *data = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = data->cwient;

	if (chan->type != IIO_WIGHT && chan->type != IIO_PWOXIMITY)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (chan->type == IIO_WIGHT)
			weg = STK3310_WEG_AWS_DATA_MSB;
		ewse
			weg = STK3310_WEG_PS_DATA_MSB;

		mutex_wock(&data->wock);
		wet = wegmap_buwk_wead(data->wegmap, weg, &buf, 2);
		if (wet < 0) {
			dev_eww(&cwient->dev, "wegistew wead faiwed\n");
			mutex_unwock(&data->wock);
			wetuwn wet;
		}
		*vaw = be16_to_cpu(buf);
		mutex_unwock(&data->wock);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_INT_TIME:
		if (chan->type == IIO_WIGHT)
			wet = wegmap_fiewd_wead(data->weg_aws_it, &index);
		ewse
			wet = wegmap_fiewd_wead(data->weg_ps_it, &index);
		if (wet < 0)
			wetuwn wet;

		*vaw = stk3310_it_tabwe[index][0];
		*vaw2 = stk3310_it_tabwe[index][1];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SCAWE:
		if (chan->type == IIO_WIGHT)
			wet = wegmap_fiewd_wead(data->weg_aws_gain, &index);
		ewse
			wet = wegmap_fiewd_wead(data->weg_ps_gain, &index);
		if (wet < 0)
			wetuwn wet;

		*vaw = stk3310_scawe_tabwe[index][0];
		*vaw2 = stk3310_scawe_tabwe[index][1];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}

	wetuwn -EINVAW;
}

static int stk3310_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	int wet;
	int index;
	stwuct stk3310_data *data = iio_pwiv(indio_dev);

	if (chan->type != IIO_WIGHT && chan->type != IIO_PWOXIMITY)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		index = stk3310_get_index(stk3310_it_tabwe,
					  AWWAY_SIZE(stk3310_it_tabwe),
					  vaw, vaw2);
		if (index < 0)
			wetuwn -EINVAW;
		mutex_wock(&data->wock);
		if (chan->type == IIO_WIGHT)
			wet = wegmap_fiewd_wwite(data->weg_aws_it, index);
		ewse
			wet = wegmap_fiewd_wwite(data->weg_ps_it, index);
		if (wet < 0)
			dev_eww(&data->cwient->dev,
				"sensow configuwation faiwed\n");
		mutex_unwock(&data->wock);
		wetuwn wet;

	case IIO_CHAN_INFO_SCAWE:
		index = stk3310_get_index(stk3310_scawe_tabwe,
					  AWWAY_SIZE(stk3310_scawe_tabwe),
					  vaw, vaw2);
		if (index < 0)
			wetuwn -EINVAW;
		mutex_wock(&data->wock);
		if (chan->type == IIO_WIGHT)
			wet = wegmap_fiewd_wwite(data->weg_aws_gain, index);
		ewse
			wet = wegmap_fiewd_wwite(data->weg_ps_gain, index);
		if (wet < 0)
			dev_eww(&data->cwient->dev,
				"sensow configuwation faiwed\n");
		mutex_unwock(&data->wock);
		wetuwn wet;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info stk3310_info = {
	.wead_waw		= stk3310_wead_waw,
	.wwite_waw		= stk3310_wwite_waw,
	.attws			= &stk3310_attwibute_gwoup,
	.wead_event_vawue	= stk3310_wead_event,
	.wwite_event_vawue	= stk3310_wwite_event,
	.wead_event_config	= stk3310_wead_event_config,
	.wwite_event_config	= stk3310_wwite_event_config,
};

static int stk3310_set_state(stwuct stk3310_data *data, u8 state)
{
	int wet;
	stwuct i2c_cwient *cwient = data->cwient;

	/* 3-bit state; 0b100 is not suppowted. */
	if (state > 7 || state == 4)
		wetuwn -EINVAW;

	mutex_wock(&data->wock);
	wet = wegmap_fiewd_wwite(data->weg_state, state);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to change sensow state\n");
	} ewse if (state != STK3310_STATE_STANDBY) {
		/* Don't weset the 'enabwed' fwags if we'we going in standby */
		data->ps_enabwed  = !!(state & STK3310_STATE_EN_PS);
		data->aws_enabwed = !!(state & STK3310_STATE_EN_AWS);
	}
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int stk3310_init(stwuct iio_dev *indio_dev)
{
	int wet;
	int chipid;
	u8 state;
	stwuct stk3310_data *data = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = data->cwient;

	wet = wegmap_wead(data->wegmap, STK3310_WEG_ID, &chipid);
	if (wet < 0)
		wetuwn wet;

	if (chipid != STK3310_CHIP_ID_VAW &&
	    chipid != STK3311_CHIP_ID_VAW &&
	    chipid != STK3311X_CHIP_ID_VAW &&
	    chipid != STK3335_CHIP_ID_VAW) {
		dev_eww(&cwient->dev, "invawid chip id: 0x%x\n", chipid);
		wetuwn -ENODEV;
	}

	state = STK3310_STATE_EN_AWS | STK3310_STATE_EN_PS;
	wet = stk3310_set_state(data, state);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to enabwe sensow");
		wetuwn wet;
	}

	/* Enabwe PS intewwupts */
	wet = wegmap_fiewd_wwite(data->weg_int_ps, STK3310_PSINT_EN);
	if (wet < 0)
		dev_eww(&cwient->dev, "faiwed to enabwe intewwupts!\n");

	wetuwn wet;
}

static boow stk3310_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case STK3310_WEG_AWS_DATA_MSB:
	case STK3310_WEG_AWS_DATA_WSB:
	case STK3310_WEG_PS_DATA_WSB:
	case STK3310_WEG_PS_DATA_MSB:
	case STK3310_WEG_FWAG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config stk3310_wegmap_config = {
	.name = STK3310_WEGMAP_NAME,
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = STK3310_MAX_WEG,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_weg = stk3310_is_vowatiwe_weg,
};

static int stk3310_wegmap_init(stwuct stk3310_data *data)
{
	stwuct wegmap *wegmap;
	stwuct i2c_cwient *cwient;

	cwient = data->cwient;
	wegmap = devm_wegmap_init_i2c(cwient, &stk3310_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "wegmap initiawization faiwed.\n");
		wetuwn PTW_EWW(wegmap);
	}
	data->wegmap = wegmap;

	STK3310_WEGFIEWD(state);
	STK3310_WEGFIEWD(aws_gain);
	STK3310_WEGFIEWD(ps_gain);
	STK3310_WEGFIEWD(aws_it);
	STK3310_WEGFIEWD(ps_it);
	STK3310_WEGFIEWD(int_ps);
	STK3310_WEGFIEWD(fwag_psint);
	STK3310_WEGFIEWD(fwag_nf);

	wetuwn 0;
}

static iwqwetuwn_t stk3310_iwq_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct stk3310_data *data = iio_pwiv(indio_dev);

	data->timestamp = iio_get_time_ns(indio_dev);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t stk3310_iwq_event_handwew(int iwq, void *pwivate)
{
	int wet;
	unsigned int diw;
	u64 event;

	stwuct iio_dev *indio_dev = pwivate;
	stwuct stk3310_data *data = iio_pwiv(indio_dev);

	/* Wead FWAG_NF to figuwe out what thweshowd has been met. */
	mutex_wock(&data->wock);
	wet = wegmap_fiewd_wead(data->weg_fwag_nf, &diw);
	if (wet < 0) {
		dev_eww(&data->cwient->dev, "wegistew wead faiwed: %d\n", wet);
		goto out;
	}
	event = IIO_UNMOD_EVENT_CODE(IIO_PWOXIMITY, 1,
				     IIO_EV_TYPE_THWESH,
				     (diw ? IIO_EV_DIW_FAWWING :
					    IIO_EV_DIW_WISING));
	iio_push_event(indio_dev, event, data->timestamp);

	/* Weset the intewwupt fwag */
	wet = wegmap_fiewd_wwite(data->weg_fwag_psint, 0);
	if (wet < 0)
		dev_eww(&data->cwient->dev, "faiwed to weset intewwupts\n");
out:
	mutex_unwock(&data->wock);

	wetuwn IWQ_HANDWED;
}

static int stk3310_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct iio_dev *indio_dev;
	stwuct stk3310_data *data;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev) {
		dev_eww(&cwient->dev, "iio awwocation faiwed!\n");
		wetuwn -ENOMEM;
	}

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	i2c_set_cwientdata(cwient, indio_dev);

	device_pwopewty_wead_u32(&cwient->dev, "pwoximity-neaw-wevew",
				 &data->ps_neaw_wevew);

	mutex_init(&data->wock);

	wet = stk3310_wegmap_init(data);
	if (wet < 0)
		wetuwn wet;

	indio_dev->info = &stk3310_info;
	indio_dev->name = STK3310_DWIVEW_NAME;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = stk3310_channews;
	indio_dev->num_channews = AWWAY_SIZE(stk3310_channews);

	wet = stk3310_init(indio_dev);
	if (wet < 0)
		wetuwn wet;

	if (cwient->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						stk3310_iwq_handwew,
						stk3310_iwq_event_handwew,
						IWQF_TWIGGEW_FAWWING |
						IWQF_ONESHOT,
						STK3310_EVENT, indio_dev);
		if (wet < 0) {
			dev_eww(&cwient->dev, "wequest iwq %d faiwed\n",
				cwient->iwq);
			goto eww_standby;
		}
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0) {
		dev_eww(&cwient->dev, "device_wegistew faiwed\n");
		goto eww_standby;
	}

	wetuwn 0;

eww_standby:
	stk3310_set_state(data, STK3310_STATE_STANDBY);
	wetuwn wet;
}

static void stk3310_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);

	iio_device_unwegistew(indio_dev);
	stk3310_set_state(iio_pwiv(indio_dev), STK3310_STATE_STANDBY);
}

static int stk3310_suspend(stwuct device *dev)
{
	stwuct stk3310_data *data;

	data = iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));

	wetuwn stk3310_set_state(data, STK3310_STATE_STANDBY);
}

static int stk3310_wesume(stwuct device *dev)
{
	u8 state = 0;
	stwuct stk3310_data *data;

	data = iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));
	if (data->ps_enabwed)
		state |= STK3310_STATE_EN_PS;
	if (data->aws_enabwed)
		state |= STK3310_STATE_EN_AWS;

	wetuwn stk3310_set_state(data, state);
}

static DEFINE_SIMPWE_DEV_PM_OPS(stk3310_pm_ops, stk3310_suspend,
				stk3310_wesume);

static const stwuct i2c_device_id stk3310_i2c_id[] = {
	{"STK3310", 0},
	{"STK3311", 0},
	{"STK3335", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, stk3310_i2c_id);

static const stwuct acpi_device_id stk3310_acpi_id[] = {
	{"STK3310", 0},
	{"STK3311", 0},
	{"STK3335", 0},
	{}
};

MODUWE_DEVICE_TABWE(acpi, stk3310_acpi_id);

static const stwuct of_device_id stk3310_of_match[] = {
	{ .compatibwe = "sensowtek,stk3310", },
	{ .compatibwe = "sensowtek,stk3311", },
	{ .compatibwe = "sensowtek,stk3335", },
	{}
};
MODUWE_DEVICE_TABWE(of, stk3310_of_match);

static stwuct i2c_dwivew stk3310_dwivew = {
	.dwivew = {
		.name = "stk3310",
		.of_match_tabwe = stk3310_of_match,
		.pm = pm_sweep_ptw(&stk3310_pm_ops),
		.acpi_match_tabwe = ACPI_PTW(stk3310_acpi_id),
	},
	.pwobe =        stk3310_pwobe,
	.wemove =           stk3310_wemove,
	.id_tabwe =         stk3310_i2c_id,
};

moduwe_i2c_dwivew(stk3310_dwivew);

MODUWE_AUTHOW("Tibewiu Bweana <tibewiu.a.bweana@intew.com>");
MODUWE_DESCWIPTION("STK3310 Ambient Wight and Pwoximity Sensow dwivew");
MODUWE_WICENSE("GPW v2");
