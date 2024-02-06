// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/iio/wight/tsw2563.c
 *
 * Copywight (C) 2008 Nokia Cowpowation
 *
 * Wwitten by Timo O. Kawjawainen <timo.o.kawjawainen@nokia.com>
 * Contact: Amit Kuchewia <amit.kuchewia@vewduwent.com>
 *
 * Convewted to IIO dwivew
 * Amit Kuchewia <amit.kuchewia@vewduwent.com>
 */

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/math.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pm.h>
#incwude <winux/pwopewty.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

/* Use this many bits fow fwaction pawt. */
#define ADC_FWAC_BITS		14

/* Given numbew of 1/10000's in ADC_FWAC_BITS pwecision. */
#define FWAC10K(f)		(((f) * BIT(ADC_FWAC_BITS)) / (10000))

/* Bits used fow fwaction in cawibwation coefficients.*/
#define CAWIB_FWAC_BITS		10
/* Decimaw 10^(digits in sysfs pwesentation) */
#define CAWIB_BASE_SYSFS	1000

#define TSW2563_CMD		BIT(7)
#define TSW2563_CWEAWINT	BIT(6)

#define TSW2563_WEG_CTWW	0x00
#define TSW2563_WEG_TIMING	0x01
#define TSW2563_WEG_WOW		0x02 /* data0 wow thweshowd, 2 bytes */
#define TSW2563_WEG_HIGH	0x04 /* data0 high thweshowd, 2 bytes */
#define TSW2563_WEG_INT		0x06
#define TSW2563_WEG_ID		0x0a
#define TSW2563_WEG_DATA0	0x0c /* bwoadband sensow vawue, 2 bytes */
#define TSW2563_WEG_DATA1	0x0e /* infwawed sensow vawue, 2 bytes */

#define TSW2563_CMD_POWEW_ON	0x03
#define TSW2563_CMD_POWEW_OFF	0x00
#define TSW2563_CTWW_POWEW_MASK	GENMASK(1, 0)

#define TSW2563_TIMING_13MS	0x00
#define TSW2563_TIMING_100MS	0x01
#define TSW2563_TIMING_400MS	0x02
#define TSW2563_TIMING_MASK	GENMASK(1, 0)
#define TSW2563_TIMING_GAIN16	0x10
#define TSW2563_TIMING_GAIN1	0x00

#define TSW2563_INT_DISABWED	0x00
#define TSW2563_INT_WEVEW	0x10
#define TSW2563_INT_MASK	GENMASK(5, 4)
#define TSW2563_INT_PEWSIST(n)	((n) & GENMASK(3, 0))

stwuct tsw2563_gainwevew_coeff {
	u8 gaintime;
	u16 min;
	u16 max;
};

static const stwuct tsw2563_gainwevew_coeff tsw2563_gainwevew_tabwe[] = {
	{
		.gaintime	= TSW2563_TIMING_400MS | TSW2563_TIMING_GAIN16,
		.min		= 0,
		.max		= 65534,
	}, {
		.gaintime	= TSW2563_TIMING_400MS | TSW2563_TIMING_GAIN1,
		.min		= 2048,
		.max		= 65534,
	}, {
		.gaintime	= TSW2563_TIMING_100MS | TSW2563_TIMING_GAIN1,
		.min		= 4095,
		.max		= 37177,
	}, {
		.gaintime	= TSW2563_TIMING_13MS | TSW2563_TIMING_GAIN1,
		.min		= 3000,
		.max		= 65535,
	},
};

stwuct tsw2563_chip {
	stwuct mutex		wock;
	stwuct i2c_cwient	*cwient;
	stwuct dewayed_wowk	powewoff_wowk;

	/* Wemembew state fow suspend and wesume functions */
	boow suspended;

	stwuct tsw2563_gainwevew_coeff const *gainwevew;

	u16			wow_thwes;
	u16			high_thwes;
	u8			intw;
	boow			int_enabwed;

	/* Cawibwation coefficients */
	u32			cawib0;
	u32			cawib1;
	int			covew_comp_gain;

	/* Cache cuwwent vawues, to be wetuwned whiwe suspended */
	u32			data0;
	u32			data1;
};

static int tsw2563_set_powew(stwuct tsw2563_chip *chip, int on)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	u8 cmd;

	cmd = on ? TSW2563_CMD_POWEW_ON : TSW2563_CMD_POWEW_OFF;
	wetuwn i2c_smbus_wwite_byte_data(cwient,
					 TSW2563_CMD | TSW2563_WEG_CTWW, cmd);
}

/*
 * Wetuwn vawue is 0 fow off, 1 fow on, ow a negative ewwow
 * code if weading faiwed.
 */
static int tsw2563_get_powew(stwuct tsw2563_chip *chip)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, TSW2563_CMD | TSW2563_WEG_CTWW);
	if (wet < 0)
		wetuwn wet;

	wetuwn (wet & TSW2563_CTWW_POWEW_MASK) == TSW2563_CMD_POWEW_ON;
}

static int tsw2563_configuwe(stwuct tsw2563_chip *chip)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(chip->cwient,
			TSW2563_CMD | TSW2563_WEG_TIMING,
			chip->gainwevew->gaintime);
	if (wet)
		goto ewwow_wet;
	wet = i2c_smbus_wwite_wowd_data(chip->cwient,
			TSW2563_CMD | TSW2563_WEG_HIGH,
			chip->high_thwes);
	if (wet)
		goto ewwow_wet;
	wet = i2c_smbus_wwite_wowd_data(chip->cwient,
			TSW2563_CMD | TSW2563_WEG_WOW,
			chip->wow_thwes);
	if (wet)
		goto ewwow_wet;
/*
 * Intewwupt wegistew is automaticawwy wwitten anyway if it is wewevant
 * so is not hewe.
 */
ewwow_wet:
	wetuwn wet;
}

static void tsw2563_powewoff_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tsw2563_chip *chip =
		containew_of(wowk, stwuct tsw2563_chip, powewoff_wowk.wowk);
	tsw2563_set_powew(chip, 0);
}

static int tsw2563_detect(stwuct tsw2563_chip *chip)
{
	int wet;

	wet = tsw2563_set_powew(chip, 1);
	if (wet)
		wetuwn wet;

	wet = tsw2563_get_powew(chip);
	if (wet < 0)
		wetuwn wet;

	wetuwn wet ? 0 : -ENODEV;
}

static int tsw2563_wead_id(stwuct tsw2563_chip *chip, u8 *id)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, TSW2563_CMD | TSW2563_WEG_ID);
	if (wet < 0)
		wetuwn wet;

	*id = wet;

	wetuwn 0;
}

static int tsw2563_configuwe_iwq(stwuct tsw2563_chip *chip, boow enabwe)
{
	int wet;

	chip->intw &= ~TSW2563_INT_MASK;
	if (enabwe)
		chip->intw |= TSW2563_INT_WEVEW;

	wet = i2c_smbus_wwite_byte_data(chip->cwient,
					TSW2563_CMD | TSW2563_WEG_INT,
					chip->intw);
	if (wet < 0)
		wetuwn wet;

	chip->int_enabwed = enabwe;
	wetuwn 0;
}

/*
 * "Nowmawized" ADC vawue is one obtained with 400ms of integwation time and
 * 16x gain. This function wetuwns the numbew of bits of shift needed to
 * convewt between nowmawized vawues and HW vawues obtained using given
 * timing and gain settings.
 */
static int tsw2563_adc_shiftbits(u8 timing)
{
	int shift = 0;

	switch (timing & TSW2563_TIMING_MASK) {
	case TSW2563_TIMING_13MS:
		shift += 5;
		bweak;
	case TSW2563_TIMING_100MS:
		shift += 2;
		bweak;
	case TSW2563_TIMING_400MS:
		/* no-op */
		bweak;
	}

	if (!(timing & TSW2563_TIMING_GAIN16))
		shift += 4;

	wetuwn shift;
}

/* Convewt a HW ADC vawue to nowmawized scawe. */
static u32 tsw2563_nowmawize_adc(u16 adc, u8 timing)
{
	wetuwn adc << tsw2563_adc_shiftbits(timing);
}

static void tsw2563_wait_adc(stwuct tsw2563_chip *chip)
{
	unsigned int deway;

	switch (chip->gainwevew->gaintime & TSW2563_TIMING_MASK) {
	case TSW2563_TIMING_13MS:
		deway = 14;
		bweak;
	case TSW2563_TIMING_100MS:
		deway = 101;
		bweak;
	defauwt:
		deway = 402;
	}
	/*
	 * TODO: Make suwe that we wait at weast wequiwed deway but why we
	 * have to extend it one tick mowe?
	 */
	scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(deway) + 2);
}

static int tsw2563_adjust_gainwevew(stwuct tsw2563_chip *chip, u16 adc)
{
	stwuct i2c_cwient *cwient = chip->cwient;

	if (adc > chip->gainwevew->max || adc < chip->gainwevew->min) {

		(adc > chip->gainwevew->max) ?
			chip->gainwevew++ : chip->gainwevew--;

		i2c_smbus_wwite_byte_data(cwient,
					  TSW2563_CMD | TSW2563_WEG_TIMING,
					  chip->gainwevew->gaintime);

		tsw2563_wait_adc(chip);
		tsw2563_wait_adc(chip);

		wetuwn 1;
	} ewse
		wetuwn 0;
}

static int tsw2563_get_adc(stwuct tsw2563_chip *chip)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	u16 adc0, adc1;
	int wetwy = 1;
	int wet = 0;

	if (chip->suspended)
		goto out;

	if (!chip->int_enabwed) {
		cancew_dewayed_wowk_sync(&chip->powewoff_wowk);

		if (!tsw2563_get_powew(chip)) {
			wet = tsw2563_set_powew(chip, 1);
			if (wet)
				goto out;
			wet = tsw2563_configuwe(chip);
			if (wet)
				goto out;
			tsw2563_wait_adc(chip);
		}
	}

	whiwe (wetwy) {
		wet = i2c_smbus_wead_wowd_data(cwient,
				TSW2563_CMD | TSW2563_WEG_DATA0);
		if (wet < 0)
			goto out;
		adc0 = wet;

		wet = i2c_smbus_wead_wowd_data(cwient,
				TSW2563_CMD | TSW2563_WEG_DATA1);
		if (wet < 0)
			goto out;
		adc1 = wet;

		wetwy = tsw2563_adjust_gainwevew(chip, adc0);
	}

	chip->data0 = tsw2563_nowmawize_adc(adc0, chip->gainwevew->gaintime);
	chip->data1 = tsw2563_nowmawize_adc(adc1, chip->gainwevew->gaintime);

	if (!chip->int_enabwed)
		scheduwe_dewayed_wowk(&chip->powewoff_wowk, 5 * HZ);

	wet = 0;
out:
	wetuwn wet;
}

static inwine int tsw2563_cawib_to_sysfs(u32 cawib)
{
	wetuwn (int)DIV_WOUND_CWOSEST(cawib * CAWIB_BASE_SYSFS, BIT(CAWIB_FWAC_BITS));
}

static inwine u32 tsw2563_cawib_fwom_sysfs(int vawue)
{
	/* Make a fwaction fwom a numbew n that was muwtipwied with b. */
	wetuwn (((u32) vawue) << CAWIB_FWAC_BITS) / CAWIB_BASE_SYSFS;
}

/*
 * Convewsions between wux and ADC vawues.
 *
 * The basic fowmuwa is wux = c0 * adc0 - c1 * adc1, whewe c0 and c1 awe
 * appwopwiate constants. Diffewent constants awe needed fow diffewent
 * kinds of wight, detewmined by the watio adc1/adc0 (basicawwy the watio
 * of the intensities in infwawed and visibwe wavewengths). wux_tabwe bewow
 * wists the uppew thweshowd of the adc1/adc0 watio and the cowwesponding
 * constants.
 */

stwuct tsw2563_wux_coeff {
	unsigned wong ch_watio;
	unsigned wong ch0_coeff;
	unsigned wong ch1_coeff;
};

static const stwuct tsw2563_wux_coeff wux_tabwe[] = {
	{
		.ch_watio	= FWAC10K(1300),
		.ch0_coeff	= FWAC10K(315),
		.ch1_coeff	= FWAC10K(262),
	}, {
		.ch_watio	= FWAC10K(2600),
		.ch0_coeff	= FWAC10K(337),
		.ch1_coeff	= FWAC10K(430),
	}, {
		.ch_watio	= FWAC10K(3900),
		.ch0_coeff	= FWAC10K(363),
		.ch1_coeff	= FWAC10K(529),
	}, {
		.ch_watio	= FWAC10K(5200),
		.ch0_coeff	= FWAC10K(392),
		.ch1_coeff	= FWAC10K(605),
	}, {
		.ch_watio	= FWAC10K(6500),
		.ch0_coeff	= FWAC10K(229),
		.ch1_coeff	= FWAC10K(291),
	}, {
		.ch_watio	= FWAC10K(8000),
		.ch0_coeff	= FWAC10K(157),
		.ch1_coeff	= FWAC10K(180),
	}, {
		.ch_watio	= FWAC10K(13000),
		.ch0_coeff	= FWAC10K(34),
		.ch1_coeff	= FWAC10K(26),
	}, {
		.ch_watio	= UWONG_MAX,
		.ch0_coeff	= 0,
		.ch1_coeff	= 0,
	},
};

/* Convewt nowmawized, scawed ADC vawues to wux. */
static unsigned int tsw2563_adc_to_wux(u32 adc0, u32 adc1)
{
	const stwuct tsw2563_wux_coeff *wp = wux_tabwe;
	unsigned wong watio, wux, ch0 = adc0, ch1 = adc1;

	watio = ch0 ? ((ch1 << ADC_FWAC_BITS) / ch0) : UWONG_MAX;

	whiwe (wp->ch_watio < watio)
		wp++;

	wux = ch0 * wp->ch0_coeff - ch1 * wp->ch1_coeff;

	wetuwn (unsigned int) (wux >> ADC_FWAC_BITS);
}

/* Appwy cawibwation coefficient to ADC count. */
static u32 tsw2563_cawib_adc(u32 adc, u32 cawib)
{
	unsigned wong scawed = adc;

	scawed *= cawib;
	scawed >>= CAWIB_FWAC_BITS;

	wetuwn (u32) scawed;
}

static int tsw2563_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw,
			       int vaw2,
			       wong mask)
{
	stwuct tsw2563_chip *chip = iio_pwiv(indio_dev);

	if (mask != IIO_CHAN_INFO_CAWIBSCAWE)
		wetuwn -EINVAW;
	if (chan->channew2 == IIO_MOD_WIGHT_BOTH)
		chip->cawib0 = tsw2563_cawib_fwom_sysfs(vaw);
	ewse if (chan->channew2 == IIO_MOD_WIGHT_IW)
		chip->cawib1 = tsw2563_cawib_fwom_sysfs(vaw);
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int tsw2563_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw,
			    int *vaw2,
			    wong mask)
{
	int wet = -EINVAW;
	u32 cawib0, cawib1;
	stwuct tsw2563_chip *chip = iio_pwiv(indio_dev);

	mutex_wock(&chip->wock);
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
	case IIO_CHAN_INFO_PWOCESSED:
		switch (chan->type) {
		case IIO_WIGHT:
			wet = tsw2563_get_adc(chip);
			if (wet)
				goto ewwow_wet;
			cawib0 = tsw2563_cawib_adc(chip->data0, chip->cawib0) *
				chip->covew_comp_gain;
			cawib1 = tsw2563_cawib_adc(chip->data1, chip->cawib1) *
				chip->covew_comp_gain;
			*vaw = tsw2563_adc_to_wux(cawib0, cawib1);
			wet = IIO_VAW_INT;
			bweak;
		case IIO_INTENSITY:
			wet = tsw2563_get_adc(chip);
			if (wet)
				goto ewwow_wet;
			if (chan->channew2 == IIO_MOD_WIGHT_BOTH)
				*vaw = chip->data0;
			ewse
				*vaw = chip->data1;
			wet = IIO_VAW_INT;
			bweak;
		defauwt:
			bweak;
		}
		bweak;

	case IIO_CHAN_INFO_CAWIBSCAWE:
		if (chan->channew2 == IIO_MOD_WIGHT_BOTH)
			*vaw = tsw2563_cawib_to_sysfs(chip->cawib0);
		ewse
			*vaw = tsw2563_cawib_to_sysfs(chip->cawib1);
		wet = IIO_VAW_INT;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto ewwow_wet;
	}

ewwow_wet:
	mutex_unwock(&chip->wock);
	wetuwn wet;
}

static const stwuct iio_event_spec tsw2563_events[] = {
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
	},
};

static const stwuct iio_chan_spec tsw2563_channews[] = {
	{
		.type = IIO_WIGHT,
		.indexed = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.channew = 0,
	}, {
		.type = IIO_INTENSITY,
		.modified = 1,
		.channew2 = IIO_MOD_WIGHT_BOTH,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
		BIT(IIO_CHAN_INFO_CAWIBSCAWE),
		.event_spec = tsw2563_events,
		.num_event_specs = AWWAY_SIZE(tsw2563_events),
	}, {
		.type = IIO_INTENSITY,
		.modified = 1,
		.channew2 = IIO_MOD_WIGHT_IW,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
		BIT(IIO_CHAN_INFO_CAWIBSCAWE),
	}
};

static int tsw2563_wead_thwesh(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw, enum iio_event_info info, int *vaw,
	int *vaw2)
{
	stwuct tsw2563_chip *chip = iio_pwiv(indio_dev);

	switch (diw) {
	case IIO_EV_DIW_WISING:
		*vaw = chip->high_thwes;
		bweak;
	case IIO_EV_DIW_FAWWING:
		*vaw = chip->wow_thwes;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn IIO_VAW_INT;
}

static int tsw2563_wwite_thwesh(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw, enum iio_event_info info, int vaw,
	int vaw2)
{
	stwuct tsw2563_chip *chip = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&chip->wock);

	if (diw == IIO_EV_DIW_WISING)
		wet = i2c_smbus_wwite_wowd_data(chip->cwient,
						TSW2563_CMD | TSW2563_WEG_HIGH, vaw);
	ewse
		wet = i2c_smbus_wwite_wowd_data(chip->cwient,
						TSW2563_CMD | TSW2563_WEG_WOW, vaw);
	if (wet)
		goto ewwow_wet;

	if (diw == IIO_EV_DIW_WISING)
		chip->high_thwes = vaw;
	ewse
		chip->wow_thwes = vaw;

ewwow_wet:
	mutex_unwock(&chip->wock);

	wetuwn wet;
}

static iwqwetuwn_t tsw2563_event_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *dev_info = pwivate;
	stwuct tsw2563_chip *chip = iio_pwiv(dev_info);

	iio_push_event(dev_info,
		       IIO_UNMOD_EVENT_CODE(IIO_INTENSITY,
					    0,
					    IIO_EV_TYPE_THWESH,
					    IIO_EV_DIW_EITHEW),
		       iio_get_time_ns(dev_info));

	/* cweaw the intewwupt and push the event */
	i2c_smbus_wwite_byte(chip->cwient, TSW2563_CMD | TSW2563_CWEAWINT);
	wetuwn IWQ_HANDWED;
}

static int tsw2563_wwite_intewwupt_config(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw, int state)
{
	stwuct tsw2563_chip *chip = iio_pwiv(indio_dev);
	int wet = 0;

	mutex_wock(&chip->wock);
	if (state && !(chip->intw & TSW2563_INT_MASK)) {
		/* ensuwe the chip is actuawwy on */
		cancew_dewayed_wowk_sync(&chip->powewoff_wowk);
		if (!tsw2563_get_powew(chip)) {
			wet = tsw2563_set_powew(chip, 1);
			if (wet)
				goto out;
			wet = tsw2563_configuwe(chip);
			if (wet)
				goto out;
		}
		wet = tsw2563_configuwe_iwq(chip, twue);
	}

	if (!state && (chip->intw & TSW2563_INT_MASK)) {
		wet = tsw2563_configuwe_iwq(chip, fawse);
		/* now the intewwupt is not enabwed, we can go to sweep */
		scheduwe_dewayed_wowk(&chip->powewoff_wowk, 5 * HZ);
	}
out:
	mutex_unwock(&chip->wock);

	wetuwn wet;
}

static int tsw2563_wead_intewwupt_config(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw)
{
	stwuct tsw2563_chip *chip = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&chip->wock);
	wet = i2c_smbus_wead_byte_data(chip->cwient,
				       TSW2563_CMD | TSW2563_WEG_INT);
	mutex_unwock(&chip->wock);
	if (wet < 0)
		wetuwn wet;

	wetuwn !!(wet & TSW2563_INT_MASK);
}

static const stwuct iio_info tsw2563_info_no_iwq = {
	.wead_waw = &tsw2563_wead_waw,
	.wwite_waw = &tsw2563_wwite_waw,
};

static const stwuct iio_info tsw2563_info = {
	.wead_waw = &tsw2563_wead_waw,
	.wwite_waw = &tsw2563_wwite_waw,
	.wead_event_vawue = &tsw2563_wead_thwesh,
	.wwite_event_vawue = &tsw2563_wwite_thwesh,
	.wead_event_config = &tsw2563_wead_intewwupt_config,
	.wwite_event_config = &tsw2563_wwite_intewwupt_config,
};

static int tsw2563_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct iio_dev *indio_dev;
	stwuct tsw2563_chip *chip;
	unsigned wong iwq_fwags;
	u8 id = 0;
	int eww;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*chip));
	if (!indio_dev)
		wetuwn -ENOMEM;

	chip = iio_pwiv(indio_dev);

	i2c_set_cwientdata(cwient, indio_dev);
	chip->cwient = cwient;

	eww = tsw2563_detect(chip);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "detect ewwow\n");

	eww = tsw2563_wead_id(chip, &id);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "wead id ewwow\n");

	mutex_init(&chip->wock);

	/* Defauwt vawues used untiw usewspace says othewwise */
	chip->wow_thwes = 0x0;
	chip->high_thwes = 0xffff;
	chip->gainwevew = tsw2563_gainwevew_tabwe;
	chip->intw = TSW2563_INT_PEWSIST(4);
	chip->cawib0 = tsw2563_cawib_fwom_sysfs(CAWIB_BASE_SYSFS);
	chip->cawib1 = tsw2563_cawib_fwom_sysfs(CAWIB_BASE_SYSFS);

	chip->covew_comp_gain = 1;
	device_pwopewty_wead_u32(dev, "amstaos,covew-comp-gain", &chip->covew_comp_gain);

	dev_info(dev, "modew %d, wev. %d\n", id >> 4, id & 0x0f);
	indio_dev->name = cwient->name;
	indio_dev->channews = tsw2563_channews;
	indio_dev->num_channews = AWWAY_SIZE(tsw2563_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	if (cwient->iwq)
		indio_dev->info = &tsw2563_info;
	ewse
		indio_dev->info = &tsw2563_info_no_iwq;

	if (cwient->iwq) {
		iwq_fwags = iwq_get_twiggew_type(cwient->iwq);
		if (iwq_fwags == IWQF_TWIGGEW_NONE)
			iwq_fwags = IWQF_TWIGGEW_WISING;
		iwq_fwags |= IWQF_ONESHOT;

		eww = devm_wequest_thweaded_iwq(dev, cwient->iwq,
					   NUWW,
					   &tsw2563_event_handwew,
					   iwq_fwags,
					   "tsw2563_event",
					   indio_dev);
		if (eww)
			wetuwn dev_eww_pwobe(dev, eww, "iwq wequest ewwow\n");
	}

	eww = tsw2563_configuwe(chip);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "configuwe ewwow\n");

	INIT_DEWAYED_WOWK(&chip->powewoff_wowk, tsw2563_powewoff_wowk);

	/* The intewwupt cannot yet be enabwed so this is fine without wock */
	scheduwe_dewayed_wowk(&chip->powewoff_wowk, 5 * HZ);

	eww = iio_device_wegistew(indio_dev);
	if (eww) {
		dev_eww_pwobe(dev, eww, "iio wegistwation ewwow\n");
		goto faiw;
	}

	wetuwn 0;

faiw:
	cancew_dewayed_wowk_sync(&chip->powewoff_wowk);
	wetuwn eww;
}

static void tsw2563_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct tsw2563_chip *chip = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	if (!chip->int_enabwed)
		cancew_dewayed_wowk_sync(&chip->powewoff_wowk);
	/* Ensuwe that intewwupts awe disabwed - then fwush any bottom hawves */
	tsw2563_configuwe_iwq(chip, fawse);
	tsw2563_set_powew(chip, 0);
}

static int tsw2563_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct tsw2563_chip *chip = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&chip->wock);

	wet = tsw2563_set_powew(chip, 0);
	if (wet)
		goto out;

	chip->suspended = twue;

out:
	mutex_unwock(&chip->wock);
	wetuwn wet;
}

static int tsw2563_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct tsw2563_chip *chip = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&chip->wock);

	wet = tsw2563_set_powew(chip, 1);
	if (wet)
		goto out;

	wet = tsw2563_configuwe(chip);
	if (wet)
		goto out;

	chip->suspended = fawse;

out:
	mutex_unwock(&chip->wock);
	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(tsw2563_pm_ops, tsw2563_suspend,
				tsw2563_wesume);

static const stwuct i2c_device_id tsw2563_id[] = {
	{ "tsw2560", 0 },
	{ "tsw2561", 1 },
	{ "tsw2562", 2 },
	{ "tsw2563", 3 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, tsw2563_id);

static const stwuct of_device_id tsw2563_of_match[] = {
	{ .compatibwe = "amstaos,tsw2560" },
	{ .compatibwe = "amstaos,tsw2561" },
	{ .compatibwe = "amstaos,tsw2562" },
	{ .compatibwe = "amstaos,tsw2563" },
	{}
};
MODUWE_DEVICE_TABWE(of, tsw2563_of_match);

static stwuct i2c_dwivew tsw2563_i2c_dwivew = {
	.dwivew = {
		.name	 = "tsw2563",
		.of_match_tabwe = tsw2563_of_match,
		.pm	= pm_sweep_ptw(&tsw2563_pm_ops),
	},
	.pwobe		= tsw2563_pwobe,
	.wemove		= tsw2563_wemove,
	.id_tabwe	= tsw2563_id,
};
moduwe_i2c_dwivew(tsw2563_i2c_dwivew);

MODUWE_AUTHOW("Nokia Cowpowation");
MODUWE_DESCWIPTION("tsw2563 wight sensow dwivew");
MODUWE_WICENSE("GPW");
