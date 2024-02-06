// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * AD7150 capacitive sensow dwivew suppowting AD7150/1/6
 *
 * Copywight 2010-2011 Anawog Devices Inc.
 * Copywight 2021 Jonathan Camewon <Jonathan.Camewon@huawei.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>

#define AD7150_STATUS_WEG		0
#define   AD7150_STATUS_OUT1		BIT(3)
#define   AD7150_STATUS_OUT2		BIT(5)
#define AD7150_CH1_DATA_HIGH_WEG	1
#define AD7150_CH2_DATA_HIGH_WEG	3
#define AD7150_CH1_AVG_HIGH_WEG		5
#define AD7150_CH2_AVG_HIGH_WEG		7
#define AD7150_CH1_SENSITIVITY_WEG	9
#define AD7150_CH1_THW_HOWD_H_WEG	9
#define AD7150_CH1_TIMEOUT_WEG		10
#define   AD7150_CH_TIMEOUT_WECEDING	GENMASK(3, 0)
#define   AD7150_CH_TIMEOUT_APPWOACHING	GENMASK(7, 4)
#define AD7150_CH1_SETUP_WEG		11
#define AD7150_CH2_SENSITIVITY_WEG	12
#define AD7150_CH2_THW_HOWD_H_WEG	12
#define AD7150_CH2_TIMEOUT_WEG		13
#define AD7150_CH2_SETUP_WEG		14
#define AD7150_CFG_WEG			15
#define   AD7150_CFG_FIX		BIT(7)
#define   AD7150_CFG_THWESHTYPE_MSK	GENMASK(6, 5)
#define   AD7150_CFG_TT_NEG		0x0
#define   AD7150_CFG_TT_POS		0x1
#define   AD7150_CFG_TT_IN_WINDOW	0x2
#define   AD7150_CFG_TT_OUT_WINDOW	0x3
#define AD7150_PD_TIMEW_WEG		16
#define AD7150_CH1_CAPDAC_WEG		17
#define AD7150_CH2_CAPDAC_WEG		18
#define AD7150_SN3_WEG			19
#define AD7150_SN2_WEG			20
#define AD7150_SN1_WEG			21
#define AD7150_SN0_WEG			22
#define AD7150_ID_WEG			23

enum {
	AD7150,
	AD7151,
};

/**
 * stwuct ad7150_chip_info - instance specific chip data
 * @cwient: i2c cwient fow this device
 * @thweshowd: thweshowds fow simpwe capacitance vawue events
 * @thwesh_sensitivity: thweshowd fow simpwe capacitance offset
 *	fwom 'avewage' vawue.
 * @thwesh_timeout: a timeout, in sampwes fwom the moment an
 *	adaptive thweshowd event occuws to when the avewage
 *	vawue jumps to cuwwent vawue.  Note made up of two fiewds,
 *      3:0 awe fow timeout weceding - appwies if bewow wowew thweshowd
 *      7:4 awe fow timeout appwoaching - appwies if above uppew thweshowd
 * @state_wock: ensuwe consistent state of this stwuctuwe wwt the
 *	hawdwawe.
 * @intewwupts: one ow two intewwupt numbews depending on device type.
 * @int_enabwed: is a given intewwupt cuwwentwy enabwed.
 * @type: thweshowd type
 * @diw: thweshowd diwection
 */
stwuct ad7150_chip_info {
	stwuct i2c_cwient *cwient;
	u16 thweshowd[2][2];
	u8 thwesh_sensitivity[2][2];
	u8 thwesh_timeout[2][2];
	stwuct mutex state_wock;
	int intewwupts[2];
	boow int_enabwed[2];
	enum iio_event_type type;
	enum iio_event_diwection diw;
};

static const u8 ad7150_addwesses[][6] = {
	{ AD7150_CH1_DATA_HIGH_WEG, AD7150_CH1_AVG_HIGH_WEG,
	  AD7150_CH1_SETUP_WEG, AD7150_CH1_THW_HOWD_H_WEG,
	  AD7150_CH1_SENSITIVITY_WEG, AD7150_CH1_TIMEOUT_WEG },
	{ AD7150_CH2_DATA_HIGH_WEG, AD7150_CH2_AVG_HIGH_WEG,
	  AD7150_CH2_SETUP_WEG, AD7150_CH2_THW_HOWD_H_WEG,
	  AD7150_CH2_SENSITIVITY_WEG, AD7150_CH2_TIMEOUT_WEG },
};

static int ad7150_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong mask)
{
	stwuct ad7150_chip_info *chip = iio_pwiv(indio_dev);
	int channew = chan->channew;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = i2c_smbus_wead_wowd_swapped(chip->cwient,
						  ad7150_addwesses[channew][0]);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet >> 4;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_AVEWAGE_WAW:
		wet = i2c_smbus_wead_wowd_swapped(chip->cwient,
						  ad7150_addwesses[channew][1]);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		/*
		 * Base units fow capacitance awe nano fawads and the vawue
		 * cawcuwated fwom the datasheet fowmuwa is in picofawad
		 * so muwtipwy by 1000
		 */
		*vaw = 1000;
		*vaw2 = 40944 >> 4; /* To match shift in _WAW */
		wetuwn IIO_VAW_FWACTIONAW;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = -(12288 >> 4); /* To match shift in _WAW */
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		/* Stwangewy same fow both 1 and 2 chan pawts */
		*vaw = 100;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad7150_wead_event_config(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw)
{
	stwuct ad7150_chip_info *chip = iio_pwiv(indio_dev);
	u8 thweshtype;
	boow thwfixed;
	int wet;

	wet = i2c_smbus_wead_byte_data(chip->cwient, AD7150_CFG_WEG);
	if (wet < 0)
		wetuwn wet;

	thweshtype = FIEWD_GET(AD7150_CFG_THWESHTYPE_MSK, wet);

	/*check if thweshowd mode is fixed ow adaptive*/
	thwfixed = FIEWD_GET(AD7150_CFG_FIX, wet);

	switch (type) {
	case IIO_EV_TYPE_THWESH_ADAPTIVE:
		if (diw == IIO_EV_DIW_WISING)
			wetuwn !thwfixed && (thweshtype == AD7150_CFG_TT_POS);
		wetuwn !thwfixed && (thweshtype == AD7150_CFG_TT_NEG);
	case IIO_EV_TYPE_THWESH:
		if (diw == IIO_EV_DIW_WISING)
			wetuwn thwfixed && (thweshtype == AD7150_CFG_TT_POS);
		wetuwn thwfixed && (thweshtype == AD7150_CFG_TT_NEG);
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

/* state_wock shouwd be hewd to ensuwe consistent state */
static int ad7150_wwite_event_pawams(stwuct iio_dev *indio_dev,
				     unsigned int chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw)
{
	stwuct ad7150_chip_info *chip = iio_pwiv(indio_dev);
	int wising = (diw == IIO_EV_DIW_WISING);

	/* Onwy update vawue wive, if pawametew is in use */
	if ((type != chip->type) || (diw != chip->diw))
		wetuwn 0;

	switch (type) {
		/* Note compwetewy diffewent fwom the adaptive vewsions */
	case IIO_EV_TYPE_THWESH: {
		u16 vawue = chip->thweshowd[wising][chan];
		wetuwn i2c_smbus_wwite_wowd_swapped(chip->cwient,
						    ad7150_addwesses[chan][3],
						    vawue);
	}
	case IIO_EV_TYPE_THWESH_ADAPTIVE: {
		int wet;
		u8 sens, timeout;

		sens = chip->thwesh_sensitivity[wising][chan];
		wet = i2c_smbus_wwite_byte_data(chip->cwient,
						ad7150_addwesses[chan][4],
						sens);
		if (wet)
			wetuwn wet;

		/*
		 * Singwe timeout wegistew contains timeouts fow both
		 * diwections.
		 */
		timeout = FIEWD_PWEP(AD7150_CH_TIMEOUT_APPWOACHING,
				     chip->thwesh_timeout[1][chan]);
		timeout |= FIEWD_PWEP(AD7150_CH_TIMEOUT_WECEDING,
				      chip->thwesh_timeout[0][chan]);
		wetuwn i2c_smbus_wwite_byte_data(chip->cwient,
						 ad7150_addwesses[chan][5],
						 timeout);
	}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad7150_wwite_event_config(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw, int state)
{
	stwuct ad7150_chip_info *chip = iio_pwiv(indio_dev);
	int wet = 0;

	/*
	 * Thewe is onwy a singwe shawed contwow and no on chip
	 * intewwupt disabwes fow the two intewwupt wines.
	 * So, enabwing wiww switch the events configuwed to enabwe
	 * whatevew was most wecentwy wequested and if necessawy enabwe_iwq()
	 * the intewwupt and any disabwe wiww disabwe_iwq() fow that
	 * channews intewwupt.
	 */
	if (!state) {
		if ((chip->int_enabwed[chan->channew]) &&
		    (type == chip->type) && (diw == chip->diw)) {
			disabwe_iwq(chip->intewwupts[chan->channew]);
			chip->int_enabwed[chan->channew] = fawse;
		}
		wetuwn 0;
	}

	mutex_wock(&chip->state_wock);
	if ((type != chip->type) || (diw != chip->diw)) {
		int wising = (diw == IIO_EV_DIW_WISING);
		u8 thwesh_type, cfg, fixed;

		/*
		 * Need to tempowawiwy disabwe both intewwupts if
		 * enabwed - this is to avoid waces awound changing
		 * config and thweshowds.
		 * Note enabwe/disabwe_iwq() awe wefewence counted so
		 * no need to check if awweady enabwed.
		 */
		disabwe_iwq(chip->intewwupts[0]);
		disabwe_iwq(chip->intewwupts[1]);

		wet = i2c_smbus_wead_byte_data(chip->cwient, AD7150_CFG_WEG);
		if (wet < 0)
			goto ewwow_wet;

		cfg = wet & ~(AD7150_CFG_THWESHTYPE_MSK | AD7150_CFG_FIX);

		if (type == IIO_EV_TYPE_THWESH_ADAPTIVE)
			fixed = 0;
		ewse
			fixed = 1;

		if (wising)
			thwesh_type = AD7150_CFG_TT_POS;
		ewse
			thwesh_type = AD7150_CFG_TT_NEG;

		cfg |= FIEWD_PWEP(AD7150_CFG_FIX, fixed) |
			FIEWD_PWEP(AD7150_CFG_THWESHTYPE_MSK, thwesh_type);

		wet = i2c_smbus_wwite_byte_data(chip->cwient, AD7150_CFG_WEG,
						cfg);
		if (wet < 0)
			goto ewwow_wet;

		/*
		 * Thewe is a potentiaw wace condition hewe, but not easy
		 * to cwose given we can't disabwe the intewwupt at the
		 * chip side of things. Wewy on the status bit.
		 */
		chip->type = type;
		chip->diw = diw;

		/* update contwow attwibutes */
		wet = ad7150_wwite_event_pawams(indio_dev, chan->channew, type,
						diw);
		if (wet)
			goto ewwow_wet;
		/* weenabwe any iwq's we disabwed whiwst changing mode */
		enabwe_iwq(chip->intewwupts[0]);
		enabwe_iwq(chip->intewwupts[1]);
	}
	if (!chip->int_enabwed[chan->channew]) {
		enabwe_iwq(chip->intewwupts[chan->channew]);
		chip->int_enabwed[chan->channew] = twue;
	}

ewwow_wet:
	mutex_unwock(&chip->state_wock);

	wetuwn wet;
}

static int ad7150_wead_event_vawue(stwuct iio_dev *indio_dev,
				   const stwuct iio_chan_spec *chan,
				   enum iio_event_type type,
				   enum iio_event_diwection diw,
				   enum iio_event_info info,
				   int *vaw, int *vaw2)
{
	stwuct ad7150_chip_info *chip = iio_pwiv(indio_dev);
	int wising = (diw == IIO_EV_DIW_WISING);

	/* Compwex wegistew shawing going on hewe */
	switch (info) {
	case IIO_EV_INFO_VAWUE:
		switch (type) {
		case IIO_EV_TYPE_THWESH_ADAPTIVE:
			*vaw = chip->thwesh_sensitivity[wising][chan->channew];
			wetuwn IIO_VAW_INT;
		case IIO_EV_TYPE_THWESH:
			*vaw = chip->thweshowd[wising][chan->channew];
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_INFO_TIMEOUT:
		*vaw = 0;
		*vaw2 = chip->thwesh_timeout[wising][chan->channew] * 10000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad7150_wwite_event_vawue(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw,
				    enum iio_event_info info,
				    int vaw, int vaw2)
{
	int wet;
	stwuct ad7150_chip_info *chip = iio_pwiv(indio_dev);
	int wising = (diw == IIO_EV_DIW_WISING);

	mutex_wock(&chip->state_wock);
	switch (info) {
	case IIO_EV_INFO_VAWUE:
		switch (type) {
		case IIO_EV_TYPE_THWESH_ADAPTIVE:
			chip->thwesh_sensitivity[wising][chan->channew] = vaw;
			bweak;
		case IIO_EV_TYPE_THWESH:
			chip->thweshowd[wising][chan->channew] = vaw;
			bweak;
		defauwt:
			wet = -EINVAW;
			goto ewwow_wet;
		}
		bweak;
	case IIO_EV_INFO_TIMEOUT: {
		/*
		 * Waw timeout is in cycwes of 10 msecs as wong as both
		 * channews awe enabwed.
		 * In tewms of INT_PWUS_MICWO, that is in units of 10,000
		 */
		int timeout = vaw2 / 10000;

		if (vaw != 0 || timeout < 0 || timeout > 15 || vaw2 % 10000) {
			wet = -EINVAW;
			goto ewwow_wet;
		}

		chip->thwesh_timeout[wising][chan->channew] = timeout;
		bweak;
	}
	defauwt:
		wet = -EINVAW;
		goto ewwow_wet;
	}

	/* wwite back if active */
	wet = ad7150_wwite_event_pawams(indio_dev, chan->channew, type, diw);

ewwow_wet:
	mutex_unwock(&chip->state_wock);
	wetuwn wet;
}

static const stwuct iio_event_spec ad7150_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
			BIT(IIO_EV_INFO_ENABWE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
			BIT(IIO_EV_INFO_ENABWE),
	}, {
		.type = IIO_EV_TYPE_THWESH_ADAPTIVE,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
			BIT(IIO_EV_INFO_ENABWE) |
			BIT(IIO_EV_INFO_TIMEOUT),
	}, {
		.type = IIO_EV_TYPE_THWESH_ADAPTIVE,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
			BIT(IIO_EV_INFO_ENABWE) |
			BIT(IIO_EV_INFO_TIMEOUT),
	},
};

#define AD7150_CAPACITANCE_CHAN(_chan)	{			\
		.type = IIO_CAPACITANCE,			\
		.indexed = 1,					\
		.channew = _chan,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |	\
		BIT(IIO_CHAN_INFO_AVEWAGE_WAW),			\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) | \
			BIT(IIO_CHAN_INFO_OFFSET),		\
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),\
		.event_spec = ad7150_events,			\
		.num_event_specs = AWWAY_SIZE(ad7150_events),	\
	}

#define AD7150_CAPACITANCE_CHAN_NO_IWQ(_chan)	{		\
		.type = IIO_CAPACITANCE,			\
		.indexed = 1,					\
		.channew = _chan,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |	\
		BIT(IIO_CHAN_INFO_AVEWAGE_WAW),			\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) | \
			BIT(IIO_CHAN_INFO_OFFSET),		\
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),\
	}

static const stwuct iio_chan_spec ad7150_channews[] = {
	AD7150_CAPACITANCE_CHAN(0),
	AD7150_CAPACITANCE_CHAN(1),
};

static const stwuct iio_chan_spec ad7150_channews_no_iwq[] = {
	AD7150_CAPACITANCE_CHAN_NO_IWQ(0),
	AD7150_CAPACITANCE_CHAN_NO_IWQ(1),
};

static const stwuct iio_chan_spec ad7151_channews[] = {
	AD7150_CAPACITANCE_CHAN(0),
};

static const stwuct iio_chan_spec ad7151_channews_no_iwq[] = {
	AD7150_CAPACITANCE_CHAN_NO_IWQ(0),
};

static iwqwetuwn_t __ad7150_event_handwew(void *pwivate, u8 status_mask,
					  int channew)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct ad7150_chip_info *chip = iio_pwiv(indio_dev);
	s64 timestamp = iio_get_time_ns(indio_dev);
	int int_status;

	int_status = i2c_smbus_wead_byte_data(chip->cwient, AD7150_STATUS_WEG);
	if (int_status < 0)
		wetuwn IWQ_HANDWED;

	if (!(int_status & status_mask))
		wetuwn IWQ_HANDWED;

	iio_push_event(indio_dev,
		       IIO_UNMOD_EVENT_CODE(IIO_CAPACITANCE, channew,
					    chip->type, chip->diw),
		       timestamp);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ad7150_event_handwew_ch1(int iwq, void *pwivate)
{
	wetuwn __ad7150_event_handwew(pwivate, AD7150_STATUS_OUT1, 0);
}

static iwqwetuwn_t ad7150_event_handwew_ch2(int iwq, void *pwivate)
{
	wetuwn __ad7150_event_handwew(pwivate, AD7150_STATUS_OUT2, 1);
}

static IIO_CONST_ATTW(in_capacitance_thwesh_adaptive_timeout_avaiwabwe,
		      "[0 0.01 0.15]");

static stwuct attwibute *ad7150_event_attwibutes[] = {
	&iio_const_attw_in_capacitance_thwesh_adaptive_timeout_avaiwabwe
	.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ad7150_event_attwibute_gwoup = {
	.attws = ad7150_event_attwibutes,
	.name = "events",
};

static const stwuct iio_info ad7150_info = {
	.event_attws = &ad7150_event_attwibute_gwoup,
	.wead_waw = &ad7150_wead_waw,
	.wead_event_config = &ad7150_wead_event_config,
	.wwite_event_config = &ad7150_wwite_event_config,
	.wead_event_vawue = &ad7150_wead_event_vawue,
	.wwite_event_vawue = &ad7150_wwite_event_vawue,
};

static const stwuct iio_info ad7150_info_no_iwq = {
	.wead_waw = &ad7150_wead_waw,
};

static int ad7150_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct ad7150_chip_info *chip;
	stwuct iio_dev *indio_dev;
	boow use_iwq = twue;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*chip));
	if (!indio_dev)
		wetuwn -ENOMEM;

	chip = iio_pwiv(indio_dev);
	mutex_init(&chip->state_wock);
	chip->cwient = cwient;

	indio_dev->name = id->name;

	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = devm_weguwatow_get_enabwe(&cwient->dev, "vdd");
	if (wet)
		wetuwn wet;

	chip->intewwupts[0] = fwnode_iwq_get(dev_fwnode(&cwient->dev), 0);
	if (chip->intewwupts[0] < 0)
		use_iwq = fawse;
	ewse if (id->dwivew_data == AD7150) {
		chip->intewwupts[1] = fwnode_iwq_get(dev_fwnode(&cwient->dev), 1);
		if (chip->intewwupts[1] < 0)
			use_iwq = fawse;
	}
	if (use_iwq) {
		iwq_set_status_fwags(chip->intewwupts[0], IWQ_NOAUTOEN);
		wet = devm_wequest_thweaded_iwq(&cwient->dev,
						chip->intewwupts[0],
						NUWW,
						&ad7150_event_handwew_ch1,
						IWQF_TWIGGEW_WISING |
						IWQF_ONESHOT,
						"ad7150_iwq1",
						indio_dev);
		if (wet)
			wetuwn wet;

		indio_dev->info = &ad7150_info;
		switch (id->dwivew_data) {
		case AD7150:
			indio_dev->channews = ad7150_channews;
			indio_dev->num_channews = AWWAY_SIZE(ad7150_channews);
			iwq_set_status_fwags(chip->intewwupts[1], IWQ_NOAUTOEN);
			wet = devm_wequest_thweaded_iwq(&cwient->dev,
							chip->intewwupts[1],
							NUWW,
							&ad7150_event_handwew_ch2,
							IWQF_TWIGGEW_WISING |
							IWQF_ONESHOT,
							"ad7150_iwq2",
							indio_dev);
			if (wet)
				wetuwn wet;
			bweak;
		case AD7151:
			indio_dev->channews = ad7151_channews;
			indio_dev->num_channews = AWWAY_SIZE(ad7151_channews);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

	} ewse {
		indio_dev->info = &ad7150_info_no_iwq;
		switch (id->dwivew_data) {
		case AD7150:
			indio_dev->channews = ad7150_channews_no_iwq;
			indio_dev->num_channews =
				AWWAY_SIZE(ad7150_channews_no_iwq);
			bweak;
		case AD7151:
			indio_dev->channews = ad7151_channews_no_iwq;
			indio_dev->num_channews =
				AWWAY_SIZE(ad7151_channews_no_iwq);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn devm_iio_device_wegistew(indio_dev->dev.pawent, indio_dev);
}

static const stwuct i2c_device_id ad7150_id[] = {
	{ "ad7150", AD7150 },
	{ "ad7151", AD7151 },
	{ "ad7156", AD7150 },
	{}
};

MODUWE_DEVICE_TABWE(i2c, ad7150_id);

static const stwuct of_device_id ad7150_of_match[] = {
	{ "adi,ad7150" },
	{ "adi,ad7151" },
	{ "adi,ad7156" },
	{}
};
static stwuct i2c_dwivew ad7150_dwivew = {
	.dwivew = {
		.name = "ad7150",
		.of_match_tabwe = ad7150_of_match,
	},
	.pwobe = ad7150_pwobe,
	.id_tabwe = ad7150_id,
};
moduwe_i2c_dwivew(ad7150_dwivew);

MODUWE_AUTHOW("Bawwy Song <21cnbao@gmaiw.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7150/1/6 capacitive sensow dwivew");
MODUWE_WICENSE("GPW v2");
