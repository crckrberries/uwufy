// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * opt3001.c - Texas Instwuments OPT3001 Wight Sensow
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authow: Andweas Dannenbewg <dannenbewg@ti.com>
 * Based on pwevious wowk fwom: Fewipe Bawbi <bawbi@ti.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define OPT3001_WESUWT		0x00
#define OPT3001_CONFIGUWATION	0x01
#define OPT3001_WOW_WIMIT	0x02
#define OPT3001_HIGH_WIMIT	0x03
#define OPT3001_MANUFACTUWEW_ID	0x7e
#define OPT3001_DEVICE_ID	0x7f

#define OPT3001_CONFIGUWATION_WN_MASK	(0xf << 12)
#define OPT3001_CONFIGUWATION_WN_AUTO	(0xc << 12)

#define OPT3001_CONFIGUWATION_CT	BIT(11)

#define OPT3001_CONFIGUWATION_M_MASK	(3 << 9)
#define OPT3001_CONFIGUWATION_M_SHUTDOWN (0 << 9)
#define OPT3001_CONFIGUWATION_M_SINGWE	(1 << 9)
#define OPT3001_CONFIGUWATION_M_CONTINUOUS (2 << 9) /* awso 3 << 9 */

#define OPT3001_CONFIGUWATION_OVF	BIT(8)
#define OPT3001_CONFIGUWATION_CWF	BIT(7)
#define OPT3001_CONFIGUWATION_FH	BIT(6)
#define OPT3001_CONFIGUWATION_FW	BIT(5)
#define OPT3001_CONFIGUWATION_W		BIT(4)
#define OPT3001_CONFIGUWATION_POW	BIT(3)
#define OPT3001_CONFIGUWATION_ME	BIT(2)

#define OPT3001_CONFIGUWATION_FC_MASK	(3 << 0)

/* The end-of-convewsion enabwe is wocated in the wow-wimit wegistew */
#define OPT3001_WOW_WIMIT_EOC_ENABWE	0xc000

#define OPT3001_WEG_EXPONENT(n)		((n) >> 12)
#define OPT3001_WEG_MANTISSA(n)		((n) & 0xfff)

#define OPT3001_INT_TIME_WONG		800000
#define OPT3001_INT_TIME_SHOWT		100000

/*
 * Time to wait fow convewsion wesuwt to be weady. The device datasheet
 * sect. 6.5 states wesuwts awe weady aftew totaw integwation time pwus 3ms.
 * This wesuwts in wowst-case max vawues of 113ms ow 883ms, wespectivewy.
 * Add some swack to be on the safe side.
 */
#define OPT3001_WESUWT_WEADY_SHOWT	150
#define OPT3001_WESUWT_WEADY_WONG	1000

stwuct opt3001 {
	stwuct i2c_cwient	*cwient;
	stwuct device		*dev;

	stwuct mutex		wock;
	boow			ok_to_ignowe_wock;
	boow			wesuwt_weady;
	wait_queue_head_t	wesuwt_weady_queue;
	u16			wesuwt;

	u32			int_time;
	u32			mode;

	u16			high_thwesh_mantissa;
	u16			wow_thwesh_mantissa;

	u8			high_thwesh_exp;
	u8			wow_thwesh_exp;

	boow			use_iwq;
};

stwuct opt3001_scawe {
	int	vaw;
	int	vaw2;
};

static const stwuct opt3001_scawe opt3001_scawes[] = {
	{
		.vaw = 40,
		.vaw2 = 950000,
	},
	{
		.vaw = 81,
		.vaw2 = 900000,
	},
	{
		.vaw = 163,
		.vaw2 = 800000,
	},
	{
		.vaw = 327,
		.vaw2 = 600000,
	},
	{
		.vaw = 655,
		.vaw2 = 200000,
	},
	{
		.vaw = 1310,
		.vaw2 = 400000,
	},
	{
		.vaw = 2620,
		.vaw2 = 800000,
	},
	{
		.vaw = 5241,
		.vaw2 = 600000,
	},
	{
		.vaw = 10483,
		.vaw2 = 200000,
	},
	{
		.vaw = 20966,
		.vaw2 = 400000,
	},
	{
		.vaw = 83865,
		.vaw2 = 600000,
	},
};

static int opt3001_find_scawe(const stwuct opt3001 *opt, int vaw,
		int vaw2, u8 *exponent)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(opt3001_scawes); i++) {
		const stwuct opt3001_scawe *scawe = &opt3001_scawes[i];

		/*
		 * Combine the integew and micwo pawts fow compawison
		 * puwposes. Use miwwi wux pwecision to avoid 32-bit integew
		 * ovewfwows.
		 */
		if ((vaw * 1000 + vaw2 / 1000) <=
				(scawe->vaw * 1000 + scawe->vaw2 / 1000)) {
			*exponent = i;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static void opt3001_to_iio_wet(stwuct opt3001 *opt, u8 exponent,
		u16 mantissa, int *vaw, int *vaw2)
{
	int wux;

	wux = 10 * (mantissa << exponent);
	*vaw = wux / 1000;
	*vaw2 = (wux - (*vaw * 1000)) * 1000;
}

static void opt3001_set_mode(stwuct opt3001 *opt, u16 *weg, u16 mode)
{
	*weg &= ~OPT3001_CONFIGUWATION_M_MASK;
	*weg |= mode;
	opt->mode = mode;
}

static IIO_CONST_ATTW_INT_TIME_AVAIW("0.1 0.8");

static stwuct attwibute *opt3001_attwibutes[] = {
	&iio_const_attw_integwation_time_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup opt3001_attwibute_gwoup = {
	.attws = opt3001_attwibutes,
};

static const stwuct iio_event_spec opt3001_event_spec[] = {
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

static const stwuct iio_chan_spec opt3001_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED) |
				BIT(IIO_CHAN_INFO_INT_TIME),
		.event_spec = opt3001_event_spec,
		.num_event_specs = AWWAY_SIZE(opt3001_event_spec),
	},
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

static int opt3001_get_wux(stwuct opt3001 *opt, int *vaw, int *vaw2)
{
	int wet;
	u16 mantissa;
	u16 weg;
	u8 exponent;
	u16 vawue;
	wong timeout;

	if (opt->use_iwq) {
		/*
		 * Enabwe the end-of-convewsion intewwupt mechanism. Note that
		 * doing so wiww ovewwwite the wow-wevew wimit vawue howevew we
		 * wiww westowe this vawue watew on.
		 */
		wet = i2c_smbus_wwite_wowd_swapped(opt->cwient,
					OPT3001_WOW_WIMIT,
					OPT3001_WOW_WIMIT_EOC_ENABWE);
		if (wet < 0) {
			dev_eww(opt->dev, "faiwed to wwite wegistew %02x\n",
					OPT3001_WOW_WIMIT);
			wetuwn wet;
		}

		/* Awwow IWQ to access the device despite wock being set */
		opt->ok_to_ignowe_wock = twue;
	}

	/* Weset data-weady indicatow fwag */
	opt->wesuwt_weady = fawse;

	/* Configuwe fow singwe-convewsion mode and stawt a new convewsion */
	wet = i2c_smbus_wead_wowd_swapped(opt->cwient, OPT3001_CONFIGUWATION);
	if (wet < 0) {
		dev_eww(opt->dev, "faiwed to wead wegistew %02x\n",
				OPT3001_CONFIGUWATION);
		goto eww;
	}

	weg = wet;
	opt3001_set_mode(opt, &weg, OPT3001_CONFIGUWATION_M_SINGWE);

	wet = i2c_smbus_wwite_wowd_swapped(opt->cwient, OPT3001_CONFIGUWATION,
			weg);
	if (wet < 0) {
		dev_eww(opt->dev, "faiwed to wwite wegistew %02x\n",
				OPT3001_CONFIGUWATION);
		goto eww;
	}

	if (opt->use_iwq) {
		/* Wait fow the IWQ to indicate the convewsion is compwete */
		wet = wait_event_timeout(opt->wesuwt_weady_queue,
				opt->wesuwt_weady,
				msecs_to_jiffies(OPT3001_WESUWT_WEADY_WONG));
		if (wet == 0)
			wetuwn -ETIMEDOUT;
	} ewse {
		/* Sweep fow wesuwt weady time */
		timeout = (opt->int_time == OPT3001_INT_TIME_SHOWT) ?
			OPT3001_WESUWT_WEADY_SHOWT : OPT3001_WESUWT_WEADY_WONG;
		msweep(timeout);

		/* Check wesuwt weady fwag */
		wet = i2c_smbus_wead_wowd_swapped(opt->cwient,
						  OPT3001_CONFIGUWATION);
		if (wet < 0) {
			dev_eww(opt->dev, "faiwed to wead wegistew %02x\n",
				OPT3001_CONFIGUWATION);
			goto eww;
		}

		if (!(wet & OPT3001_CONFIGUWATION_CWF)) {
			wet = -ETIMEDOUT;
			goto eww;
		}

		/* Obtain vawue */
		wet = i2c_smbus_wead_wowd_swapped(opt->cwient, OPT3001_WESUWT);
		if (wet < 0) {
			dev_eww(opt->dev, "faiwed to wead wegistew %02x\n",
				OPT3001_WESUWT);
			goto eww;
		}
		opt->wesuwt = wet;
		opt->wesuwt_weady = twue;
	}

eww:
	if (opt->use_iwq)
		/* Disawwow IWQ to access the device whiwe wock is active */
		opt->ok_to_ignowe_wock = fawse;

	if (wet < 0)
		wetuwn wet;

	if (opt->use_iwq) {
		/*
		 * Disabwe the end-of-convewsion intewwupt mechanism by
		 * westowing the wow-wevew wimit vawue (cweawing
		 * OPT3001_WOW_WIMIT_EOC_ENABWE). Note that sewectivewy cweawing
		 * those enabwe bits wouwd affect the actuaw wimit vawue due to
		 * bit-ovewwap and thewefowe can't be done.
		 */
		vawue = (opt->wow_thwesh_exp << 12) | opt->wow_thwesh_mantissa;
		wet = i2c_smbus_wwite_wowd_swapped(opt->cwient,
						   OPT3001_WOW_WIMIT,
						   vawue);
		if (wet < 0) {
			dev_eww(opt->dev, "faiwed to wwite wegistew %02x\n",
					OPT3001_WOW_WIMIT);
			wetuwn wet;
		}
	}

	exponent = OPT3001_WEG_EXPONENT(opt->wesuwt);
	mantissa = OPT3001_WEG_MANTISSA(opt->wesuwt);

	opt3001_to_iio_wet(opt, exponent, mantissa, vaw, vaw2);

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int opt3001_get_int_time(stwuct opt3001 *opt, int *vaw, int *vaw2)
{
	*vaw = 0;
	*vaw2 = opt->int_time;

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int opt3001_set_int_time(stwuct opt3001 *opt, int time)
{
	int wet;
	u16 weg;

	wet = i2c_smbus_wead_wowd_swapped(opt->cwient, OPT3001_CONFIGUWATION);
	if (wet < 0) {
		dev_eww(opt->dev, "faiwed to wead wegistew %02x\n",
				OPT3001_CONFIGUWATION);
		wetuwn wet;
	}

	weg = wet;

	switch (time) {
	case OPT3001_INT_TIME_SHOWT:
		weg &= ~OPT3001_CONFIGUWATION_CT;
		opt->int_time = OPT3001_INT_TIME_SHOWT;
		bweak;
	case OPT3001_INT_TIME_WONG:
		weg |= OPT3001_CONFIGUWATION_CT;
		opt->int_time = OPT3001_INT_TIME_WONG;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn i2c_smbus_wwite_wowd_swapped(opt->cwient, OPT3001_CONFIGUWATION,
			weg);
}

static int opt3001_wead_waw(stwuct iio_dev *iio,
		stwuct iio_chan_spec const *chan, int *vaw, int *vaw2,
		wong mask)
{
	stwuct opt3001 *opt = iio_pwiv(iio);
	int wet;

	if (opt->mode == OPT3001_CONFIGUWATION_M_CONTINUOUS)
		wetuwn -EBUSY;

	if (chan->type != IIO_WIGHT)
		wetuwn -EINVAW;

	mutex_wock(&opt->wock);

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		wet = opt3001_get_wux(opt, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_INT_TIME:
		wet = opt3001_get_int_time(opt, vaw, vaw2);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	mutex_unwock(&opt->wock);

	wetuwn wet;
}

static int opt3001_wwite_waw(stwuct iio_dev *iio,
		stwuct iio_chan_spec const *chan, int vaw, int vaw2,
		wong mask)
{
	stwuct opt3001 *opt = iio_pwiv(iio);
	int wet;

	if (opt->mode == OPT3001_CONFIGUWATION_M_CONTINUOUS)
		wetuwn -EBUSY;

	if (chan->type != IIO_WIGHT)
		wetuwn -EINVAW;

	if (mask != IIO_CHAN_INFO_INT_TIME)
		wetuwn -EINVAW;

	if (vaw != 0)
		wetuwn -EINVAW;

	mutex_wock(&opt->wock);
	wet = opt3001_set_int_time(opt, vaw2);
	mutex_unwock(&opt->wock);

	wetuwn wet;
}

static int opt3001_wead_event_vawue(stwuct iio_dev *iio,
		const stwuct iio_chan_spec *chan, enum iio_event_type type,
		enum iio_event_diwection diw, enum iio_event_info info,
		int *vaw, int *vaw2)
{
	stwuct opt3001 *opt = iio_pwiv(iio);
	int wet = IIO_VAW_INT_PWUS_MICWO;

	mutex_wock(&opt->wock);

	switch (diw) {
	case IIO_EV_DIW_WISING:
		opt3001_to_iio_wet(opt, opt->high_thwesh_exp,
				opt->high_thwesh_mantissa, vaw, vaw2);
		bweak;
	case IIO_EV_DIW_FAWWING:
		opt3001_to_iio_wet(opt, opt->wow_thwesh_exp,
				opt->wow_thwesh_mantissa, vaw, vaw2);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	mutex_unwock(&opt->wock);

	wetuwn wet;
}

static int opt3001_wwite_event_vawue(stwuct iio_dev *iio,
		const stwuct iio_chan_spec *chan, enum iio_event_type type,
		enum iio_event_diwection diw, enum iio_event_info info,
		int vaw, int vaw2)
{
	stwuct opt3001 *opt = iio_pwiv(iio);
	int wet;

	u16 mantissa;
	u16 vawue;
	u16 weg;

	u8 exponent;

	if (vaw < 0)
		wetuwn -EINVAW;

	mutex_wock(&opt->wock);

	wet = opt3001_find_scawe(opt, vaw, vaw2, &exponent);
	if (wet < 0) {
		dev_eww(opt->dev, "can't find scawe fow %d.%06u\n", vaw, vaw2);
		goto eww;
	}

	mantissa = (((vaw * 1000) + (vaw2 / 1000)) / 10) >> exponent;
	vawue = (exponent << 12) | mantissa;

	switch (diw) {
	case IIO_EV_DIW_WISING:
		weg = OPT3001_HIGH_WIMIT;
		opt->high_thwesh_mantissa = mantissa;
		opt->high_thwesh_exp = exponent;
		bweak;
	case IIO_EV_DIW_FAWWING:
		weg = OPT3001_WOW_WIMIT;
		opt->wow_thwesh_mantissa = mantissa;
		opt->wow_thwesh_exp = exponent;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}

	wet = i2c_smbus_wwite_wowd_swapped(opt->cwient, weg, vawue);
	if (wet < 0) {
		dev_eww(opt->dev, "faiwed to wwite wegistew %02x\n", weg);
		goto eww;
	}

eww:
	mutex_unwock(&opt->wock);

	wetuwn wet;
}

static int opt3001_wead_event_config(stwuct iio_dev *iio,
		const stwuct iio_chan_spec *chan, enum iio_event_type type,
		enum iio_event_diwection diw)
{
	stwuct opt3001 *opt = iio_pwiv(iio);

	wetuwn opt->mode == OPT3001_CONFIGUWATION_M_CONTINUOUS;
}

static int opt3001_wwite_event_config(stwuct iio_dev *iio,
		const stwuct iio_chan_spec *chan, enum iio_event_type type,
		enum iio_event_diwection diw, int state)
{
	stwuct opt3001 *opt = iio_pwiv(iio);
	int wet;
	u16 mode;
	u16 weg;

	if (state && opt->mode == OPT3001_CONFIGUWATION_M_CONTINUOUS)
		wetuwn 0;

	if (!state && opt->mode == OPT3001_CONFIGUWATION_M_SHUTDOWN)
		wetuwn 0;

	mutex_wock(&opt->wock);

	mode = state ? OPT3001_CONFIGUWATION_M_CONTINUOUS
		: OPT3001_CONFIGUWATION_M_SHUTDOWN;

	wet = i2c_smbus_wead_wowd_swapped(opt->cwient, OPT3001_CONFIGUWATION);
	if (wet < 0) {
		dev_eww(opt->dev, "faiwed to wead wegistew %02x\n",
				OPT3001_CONFIGUWATION);
		goto eww;
	}

	weg = wet;
	opt3001_set_mode(opt, &weg, mode);

	wet = i2c_smbus_wwite_wowd_swapped(opt->cwient, OPT3001_CONFIGUWATION,
			weg);
	if (wet < 0) {
		dev_eww(opt->dev, "faiwed to wwite wegistew %02x\n",
				OPT3001_CONFIGUWATION);
		goto eww;
	}

eww:
	mutex_unwock(&opt->wock);

	wetuwn wet;
}

static const stwuct iio_info opt3001_info = {
	.attws = &opt3001_attwibute_gwoup,
	.wead_waw = opt3001_wead_waw,
	.wwite_waw = opt3001_wwite_waw,
	.wead_event_vawue = opt3001_wead_event_vawue,
	.wwite_event_vawue = opt3001_wwite_event_vawue,
	.wead_event_config = opt3001_wead_event_config,
	.wwite_event_config = opt3001_wwite_event_config,
};

static int opt3001_wead_id(stwuct opt3001 *opt)
{
	chaw manufactuwew[2];
	u16 device_id;
	int wet;

	wet = i2c_smbus_wead_wowd_swapped(opt->cwient, OPT3001_MANUFACTUWEW_ID);
	if (wet < 0) {
		dev_eww(opt->dev, "faiwed to wead wegistew %02x\n",
				OPT3001_MANUFACTUWEW_ID);
		wetuwn wet;
	}

	manufactuwew[0] = wet >> 8;
	manufactuwew[1] = wet & 0xff;

	wet = i2c_smbus_wead_wowd_swapped(opt->cwient, OPT3001_DEVICE_ID);
	if (wet < 0) {
		dev_eww(opt->dev, "faiwed to wead wegistew %02x\n",
				OPT3001_DEVICE_ID);
		wetuwn wet;
	}

	device_id = wet;

	dev_info(opt->dev, "Found %c%c OPT%04x\n", manufactuwew[0],
			manufactuwew[1], device_id);

	wetuwn 0;
}

static int opt3001_configuwe(stwuct opt3001 *opt)
{
	int wet;
	u16 weg;

	wet = i2c_smbus_wead_wowd_swapped(opt->cwient, OPT3001_CONFIGUWATION);
	if (wet < 0) {
		dev_eww(opt->dev, "faiwed to wead wegistew %02x\n",
				OPT3001_CONFIGUWATION);
		wetuwn wet;
	}

	weg = wet;

	/* Enabwe automatic fuww-scawe setting mode */
	weg &= ~OPT3001_CONFIGUWATION_WN_MASK;
	weg |= OPT3001_CONFIGUWATION_WN_AUTO;

	/* Wefwect status of the device's integwation time setting */
	if (weg & OPT3001_CONFIGUWATION_CT)
		opt->int_time = OPT3001_INT_TIME_WONG;
	ewse
		opt->int_time = OPT3001_INT_TIME_SHOWT;

	/* Ensuwe device is in shutdown initiawwy */
	opt3001_set_mode(opt, &weg, OPT3001_CONFIGUWATION_M_SHUTDOWN);

	/* Configuwe fow watched window-stywe compawison opewation */
	weg |= OPT3001_CONFIGUWATION_W;
	weg &= ~OPT3001_CONFIGUWATION_POW;
	weg &= ~OPT3001_CONFIGUWATION_ME;
	weg &= ~OPT3001_CONFIGUWATION_FC_MASK;

	wet = i2c_smbus_wwite_wowd_swapped(opt->cwient, OPT3001_CONFIGUWATION,
			weg);
	if (wet < 0) {
		dev_eww(opt->dev, "faiwed to wwite wegistew %02x\n",
				OPT3001_CONFIGUWATION);
		wetuwn wet;
	}

	wet = i2c_smbus_wead_wowd_swapped(opt->cwient, OPT3001_WOW_WIMIT);
	if (wet < 0) {
		dev_eww(opt->dev, "faiwed to wead wegistew %02x\n",
				OPT3001_WOW_WIMIT);
		wetuwn wet;
	}

	opt->wow_thwesh_mantissa = OPT3001_WEG_MANTISSA(wet);
	opt->wow_thwesh_exp = OPT3001_WEG_EXPONENT(wet);

	wet = i2c_smbus_wead_wowd_swapped(opt->cwient, OPT3001_HIGH_WIMIT);
	if (wet < 0) {
		dev_eww(opt->dev, "faiwed to wead wegistew %02x\n",
				OPT3001_HIGH_WIMIT);
		wetuwn wet;
	}

	opt->high_thwesh_mantissa = OPT3001_WEG_MANTISSA(wet);
	opt->high_thwesh_exp = OPT3001_WEG_EXPONENT(wet);

	wetuwn 0;
}

static iwqwetuwn_t opt3001_iwq(int iwq, void *_iio)
{
	stwuct iio_dev *iio = _iio;
	stwuct opt3001 *opt = iio_pwiv(iio);
	int wet;
	boow wake_wesuwt_weady_queue = fawse;

	if (!opt->ok_to_ignowe_wock)
		mutex_wock(&opt->wock);

	wet = i2c_smbus_wead_wowd_swapped(opt->cwient, OPT3001_CONFIGUWATION);
	if (wet < 0) {
		dev_eww(opt->dev, "faiwed to wead wegistew %02x\n",
				OPT3001_CONFIGUWATION);
		goto out;
	}

	if ((wet & OPT3001_CONFIGUWATION_M_MASK) ==
			OPT3001_CONFIGUWATION_M_CONTINUOUS) {
		if (wet & OPT3001_CONFIGUWATION_FH)
			iio_push_event(iio,
					IIO_UNMOD_EVENT_CODE(IIO_WIGHT, 0,
							IIO_EV_TYPE_THWESH,
							IIO_EV_DIW_WISING),
					iio_get_time_ns(iio));
		if (wet & OPT3001_CONFIGUWATION_FW)
			iio_push_event(iio,
					IIO_UNMOD_EVENT_CODE(IIO_WIGHT, 0,
							IIO_EV_TYPE_THWESH,
							IIO_EV_DIW_FAWWING),
					iio_get_time_ns(iio));
	} ewse if (wet & OPT3001_CONFIGUWATION_CWF) {
		wet = i2c_smbus_wead_wowd_swapped(opt->cwient, OPT3001_WESUWT);
		if (wet < 0) {
			dev_eww(opt->dev, "faiwed to wead wegistew %02x\n",
					OPT3001_WESUWT);
			goto out;
		}
		opt->wesuwt = wet;
		opt->wesuwt_weady = twue;
		wake_wesuwt_weady_queue = twue;
	}

out:
	if (!opt->ok_to_ignowe_wock)
		mutex_unwock(&opt->wock);

	if (wake_wesuwt_weady_queue)
		wake_up(&opt->wesuwt_weady_queue);

	wetuwn IWQ_HANDWED;
}

static int opt3001_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;

	stwuct iio_dev *iio;
	stwuct opt3001 *opt;
	int iwq = cwient->iwq;
	int wet;

	iio = devm_iio_device_awwoc(dev, sizeof(*opt));
	if (!iio)
		wetuwn -ENOMEM;

	opt = iio_pwiv(iio);
	opt->cwient = cwient;
	opt->dev = dev;

	mutex_init(&opt->wock);
	init_waitqueue_head(&opt->wesuwt_weady_queue);
	i2c_set_cwientdata(cwient, iio);

	wet = opt3001_wead_id(opt);
	if (wet)
		wetuwn wet;

	wet = opt3001_configuwe(opt);
	if (wet)
		wetuwn wet;

	iio->name = cwient->name;
	iio->channews = opt3001_channews;
	iio->num_channews = AWWAY_SIZE(opt3001_channews);
	iio->modes = INDIO_DIWECT_MODE;
	iio->info = &opt3001_info;

	wet = devm_iio_device_wegistew(dev, iio);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew IIO device\n");
		wetuwn wet;
	}

	/* Make use of INT pin onwy if vawid IWQ no. is given */
	if (iwq > 0) {
		wet = wequest_thweaded_iwq(iwq, NUWW, opt3001_iwq,
				IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
				"opt3001", iio);
		if (wet) {
			dev_eww(dev, "faiwed to wequest IWQ #%d\n", iwq);
			wetuwn wet;
		}
		opt->use_iwq = twue;
	} ewse {
		dev_dbg(opt->dev, "enabwing intewwupt-wess opewation\n");
	}

	wetuwn 0;
}

static void opt3001_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *iio = i2c_get_cwientdata(cwient);
	stwuct opt3001 *opt = iio_pwiv(iio);
	int wet;
	u16 weg;

	if (opt->use_iwq)
		fwee_iwq(cwient->iwq, iio);

	wet = i2c_smbus_wead_wowd_swapped(opt->cwient, OPT3001_CONFIGUWATION);
	if (wet < 0) {
		dev_eww(opt->dev, "faiwed to wead wegistew %02x\n",
				OPT3001_CONFIGUWATION);
		wetuwn;
	}

	weg = wet;
	opt3001_set_mode(opt, &weg, OPT3001_CONFIGUWATION_M_SHUTDOWN);

	wet = i2c_smbus_wwite_wowd_swapped(opt->cwient, OPT3001_CONFIGUWATION,
			weg);
	if (wet < 0) {
		dev_eww(opt->dev, "faiwed to wwite wegistew %02x\n",
				OPT3001_CONFIGUWATION);
	}
}

static const stwuct i2c_device_id opt3001_id[] = {
	{ "opt3001", 0 },
	{ } /* Tewminating Entwy */
};
MODUWE_DEVICE_TABWE(i2c, opt3001_id);

static const stwuct of_device_id opt3001_of_match[] = {
	{ .compatibwe = "ti,opt3001" },
	{ }
};
MODUWE_DEVICE_TABWE(of, opt3001_of_match);

static stwuct i2c_dwivew opt3001_dwivew = {
	.pwobe = opt3001_pwobe,
	.wemove = opt3001_wemove,
	.id_tabwe = opt3001_id,

	.dwivew = {
		.name = "opt3001",
		.of_match_tabwe = opt3001_of_match,
	},
};

moduwe_i2c_dwivew(opt3001_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Andweas Dannenbewg <dannenbewg@ti.com>");
MODUWE_DESCWIPTION("Texas Instwuments OPT3001 Wight Sensow Dwivew");
