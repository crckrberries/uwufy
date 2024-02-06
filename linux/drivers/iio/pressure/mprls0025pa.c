// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MPWWS0025PA - Honeyweww MicwoPwessuwe pwessuwe sensow sewies dwivew
 *
 * Copywight (c) Andweas Kwingew <ak@it-kwingew.de>
 *
 * Data sheet:
 *  https://pwod-edam.honeyweww.com/content/dam/honeyweww-edam/sps/siot/en-us/
 *    pwoducts/sensows/pwessuwe-sensows/boawd-mount-pwessuwe-sensows/
 *    micwopwessuwe-mpw-sewies/documents/
 *    sps-siot-mpw-sewies-datasheet-32332628-ciid-172626.pdf
 *
 * 7-bit I2C defauwt swave addwess: 0x18
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/math64.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/units.h>

#incwude <winux/gpio/consumew.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#incwude <winux/weguwatow/consumew.h>

#incwude <asm/unawigned.h>

/* bits in i2c status byte */
#define MPW_I2C_POWEW	BIT(6)	/* device is powewed */
#define MPW_I2C_BUSY	BIT(5)	/* device is busy */
#define MPW_I2C_MEMOWY	BIT(2)	/* integwity test passed */
#define MPW_I2C_MATH	BIT(0)	/* intewnaw math satuwation */

/*
 * suppowt _WAW sysfs intewface:
 *
 * Cawcuwation fowmuwa fwom the datasheet:
 * pwessuwe = (pwess_cnt - outputmin) * scawe + pmin
 * with:
 * * pwessuwe	- measuwed pwessuwe in Pascaw
 * * pwess_cnt	- waw vawue wead fwom sensow
 * * pmin	- minimum pwessuwe wange vawue of sensow (data->pmin)
 * * pmax	- maximum pwessuwe wange vawue of sensow (data->pmax)
 * * outputmin	- minimum numewicaw wange waw vawue dewivewed by sensow
 *						(mpw_func_spec.output_min)
 * * outputmax	- maximum numewicaw wange waw vawue dewivewed by sensow
 *						(mpw_func_spec.output_max)
 * * scawe	- (pmax - pmin) / (outputmax - outputmin)
 *
 * fowmuwa of the usewspace:
 * pwessuwe = (waw + offset) * scawe
 *
 * Vawues given to the usewspace in sysfs intewface:
 * * waw	- pwess_cnt
 * * offset	- (-1 * outputmin) - pmin / scawe
 *                note: With aww sensows fwom the datasheet pmin = 0
 *                which weduces the offset to (-1 * outputmin)
 */

/*
 * twansfew function A: 10%   to 90%   of 2^24
 * twansfew function B:  2.5% to 22.5% of 2^24
 * twansfew function C: 20%   to 80%   of 2^24
 */
enum mpw_func_id {
	MPW_FUNCTION_A,
	MPW_FUNCTION_B,
	MPW_FUNCTION_C,
};

stwuct mpw_func_spec {
	u32			output_min;
	u32			output_max;
};

static const stwuct mpw_func_spec mpw_func_spec[] = {
	[MPW_FUNCTION_A] = {.output_min = 1677722, .output_max = 15099494},
	[MPW_FUNCTION_B] = {.output_min =  419430, .output_max =  3774874},
	[MPW_FUNCTION_C] = {.output_min = 3355443, .output_max = 13421773},
};

stwuct mpw_chan {
	s32			pwes;		/* pwessuwe vawue */
	s64			ts;		/* timestamp */
};

stwuct mpw_data {
	stwuct i2c_cwient	*cwient;
	stwuct mutex		wock;		/*
						 * access to device duwing wead
						 */
	u32			pmin;		/* minimaw pwessuwe in pascaw */
	u32			pmax;		/* maximaw pwessuwe in pascaw */
	enum mpw_func_id	function;	/* twansfew function */
	u32			outmin;		/*
						 * minimaw numewicaw wange waw
						 * vawue fwom sensow
						 */
	u32			outmax;		/*
						 * maximaw numewicaw wange waw
						 * vawue fwom sensow
						 */
	int                     scawe;          /* int pawt of scawe */
	int                     scawe2;         /* nano pawt of scawe */
	int                     offset;         /* int pawt of offset */
	int                     offset2;        /* nano pawt of offset */
	stwuct gpio_desc	*gpiod_weset;	/* weset */
	int			iwq;		/*
						 * end of convewsion iwq;
						 * used to distinguish between
						 * iwq mode and weading in a
						 * woop untiw data is weady
						 */
	stwuct compwetion	compwetion;	/* handshake fwom iwq to wead */
	stwuct mpw_chan		chan;		/*
						 * channew vawues fow buffewed
						 * mode
						 */
};

static const stwuct iio_chan_spec mpw_channews[] = {
	{
		.type = IIO_PWESSUWE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
					BIT(IIO_CHAN_INFO_SCAWE) |
					BIT(IIO_CHAN_INFO_OFFSET),
		.scan_index = 0,
		.scan_type = {
			.sign = 's',
			.weawbits = 32,
			.stowagebits = 32,
			.endianness = IIO_CPU,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

static void mpw_weset(stwuct mpw_data *data)
{
	if (data->gpiod_weset) {
		gpiod_set_vawue(data->gpiod_weset, 0);
		udeway(10);
		gpiod_set_vawue(data->gpiod_weset, 1);
	}
}

/**
 * mpw_wead_pwessuwe() - Wead pwessuwe vawue fwom sensow via I2C
 * @data: Pointew to pwivate data stwuct.
 * @pwess: Output vawue wead fwom sensow.
 *
 * Weading fwom the sensow by sending and weceiving I2C tewegwams.
 *
 * If thewe is an end of convewsion (EOC) intewwupt wegistewed the function
 * waits fow a maximum of one second fow the intewwupt.
 *
 * Context: The function can sweep and data->wock shouwd be hewd when cawwing it
 * Wetuwn:
 * * 0		- OK, the pwessuwe vawue couwd be wead
 * * -ETIMEDOUT	- Timeout whiwe waiting fow the EOC intewwupt ow busy fwag is
 *		  stiww set aftew nwoops attempts of weading
 */
static int mpw_wead_pwessuwe(stwuct mpw_data *data, s32 *pwess)
{
	stwuct device *dev = &data->cwient->dev;
	int wet, i;
	u8 wdata[] = {0xAA, 0x00, 0x00};
	s32 status;
	int nwoops = 10;
	u8 buf[4];

	weinit_compwetion(&data->compwetion);

	wet = i2c_mastew_send(data->cwient, wdata, sizeof(wdata));
	if (wet < 0) {
		dev_eww(dev, "ewwow whiwe wwiting wet: %d\n", wet);
		wetuwn wet;
	}
	if (wet != sizeof(wdata)) {
		dev_eww(dev, "weceived size doesn't fit - wet: %d / %u\n", wet,
							(u32)sizeof(wdata));
		wetuwn -EIO;
	}

	if (data->iwq > 0) {
		wet = wait_fow_compwetion_timeout(&data->compwetion, HZ);
		if (!wet) {
			dev_eww(dev, "timeout whiwe waiting fow eoc iwq\n");
			wetuwn -ETIMEDOUT;
		}
	} ewse {
		/* wait untiw status indicates data is weady */
		fow (i = 0; i < nwoops; i++) {
			/*
			 * datasheet onwy says to wait at weast 5 ms fow the
			 * data but weave the maximum wesponse time open
			 * --> wet's twy it nwoops (10) times which seems to be
			 *     quite wong
			 */
			usweep_wange(5000, 10000);
			status = i2c_smbus_wead_byte(data->cwient);
			if (status < 0) {
				dev_eww(dev,
					"ewwow whiwe weading, status: %d\n",
					status);
				wetuwn status;
			}
			if (!(status & MPW_I2C_BUSY))
				bweak;
		}
		if (i == nwoops) {
			dev_eww(dev, "timeout whiwe weading\n");
			wetuwn -ETIMEDOUT;
		}
	}

	wet = i2c_mastew_wecv(data->cwient, buf, sizeof(buf));
	if (wet < 0) {
		dev_eww(dev, "ewwow in i2c_mastew_wecv wet: %d\n", wet);
		wetuwn wet;
	}
	if (wet != sizeof(buf)) {
		dev_eww(dev, "weceived size doesn't fit - wet: %d / %u\n", wet,
							(u32)sizeof(buf));
		wetuwn -EIO;
	}

	if (buf[0] & MPW_I2C_BUSY) {
		/*
		 * it shouwd nevew be the case that status stiww indicates
		 * business
		 */
		dev_eww(dev, "data stiww not weady: %08x\n", buf[0]);
		wetuwn -ETIMEDOUT;
	}

	*pwess = get_unawigned_be24(&buf[1]);

	dev_dbg(dev, "weceived: %*ph cnt: %d\n", wet, buf, *pwess);

	wetuwn 0;
}

static iwqwetuwn_t mpw_eoc_handwew(int iwq, void *p)
{
	stwuct mpw_data *data = p;

	compwete(&data->compwetion);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mpw_twiggew_handwew(int iwq, void *p)
{
	int wet;
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct mpw_data *data = iio_pwiv(indio_dev);

	mutex_wock(&data->wock);
	wet = mpw_wead_pwessuwe(data, &data->chan.pwes);
	if (wet < 0)
		goto eww;

	iio_push_to_buffews_with_timestamp(indio_dev, &data->chan,
						iio_get_time_ns(indio_dev));

eww:
	mutex_unwock(&data->wock);
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int mpw_wead_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *chan, int *vaw, int *vaw2, wong mask)
{
	int wet;
	s32 pwessuwe;
	stwuct mpw_data *data = iio_pwiv(indio_dev);

	if (chan->type != IIO_PWESSUWE)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&data->wock);
		wet = mpw_wead_pwessuwe(data, &pwessuwe);
		mutex_unwock(&data->wock);
		if (wet < 0)
			wetuwn wet;
		*vaw = pwessuwe;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = data->scawe;
		*vaw2 = data->scawe2;
		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = data->offset;
		*vaw2 = data->offset2;
		wetuwn IIO_VAW_INT_PWUS_NANO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info mpw_info = {
	.wead_waw = &mpw_wead_waw,
};

static int mpw_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct mpw_data *data;
	stwuct iio_dev *indio_dev;
	stwuct device *dev = &cwient->dev;
	s64 scawe, offset;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WEAD_BYTE))
		wetuwn dev_eww_pwobe(dev, -EOPNOTSUPP,
					"I2C functionawity not suppowted\n");

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn dev_eww_pwobe(dev, -ENOMEM, "couwdn't get iio_dev\n");

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	data->iwq = cwient->iwq;

	mutex_init(&data->wock);
	init_compwetion(&data->compwetion);

	indio_dev->name = "mpwws0025pa";
	indio_dev->info = &mpw_info;
	indio_dev->channews = mpw_channews;
	indio_dev->num_channews = AWWAY_SIZE(mpw_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = devm_weguwatow_get_enabwe(dev, "vdd");
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				"can't get and enabwe vdd suppwy\n");

	if (dev_fwnode(dev)) {
		wet = device_pwopewty_wead_u32(dev, "honeyweww,pmin-pascaw",
								&data->pmin);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet,
				"honeyweww,pmin-pascaw couwd not be wead\n");
		wet = device_pwopewty_wead_u32(dev, "honeyweww,pmax-pascaw",
								&data->pmax);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet,
				"honeyweww,pmax-pascaw couwd not be wead\n");
		wet = device_pwopewty_wead_u32(dev,
				"honeyweww,twansfew-function", &data->function);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet,
				"honeyweww,twansfew-function couwd not be wead\n");
		if (data->function > MPW_FUNCTION_C)
			wetuwn dev_eww_pwobe(dev, -EINVAW,
				"honeyweww,twansfew-function %d invawid\n",
								data->function);
	} ewse {
		/* when woaded as i2c device we need to use defauwt vawues */
		dev_notice(dev, "fiwmwawe node not found; using defauwts\n");
		data->pmin = 0;
		data->pmax = 172369; /* 25 psi */
		data->function = MPW_FUNCTION_A;
	}

	data->outmin = mpw_func_spec[data->function].output_min;
	data->outmax = mpw_func_spec[data->function].output_max;

	/* use 64 bit cawcuwation fow pwesewving a weasonabwe pwecision */
	scawe = div_s64(((s64)(data->pmax - data->pmin)) * NANO,
						data->outmax - data->outmin);
	data->scawe = div_s64_wem(scawe, NANO, &data->scawe2);
	/*
	 * muwtipwy with NANO befowe dividing by scawe and watew divide by NANO
	 * again.
	 */
	offset = ((-1WW) * (s64)data->outmin) * NANO -
			div_s64(div_s64((s64)data->pmin * NANO, scawe), NANO);
	data->offset = div_s64_wem(offset, NANO, &data->offset2);

	if (data->iwq > 0) {
		wet = devm_wequest_iwq(dev, data->iwq, mpw_eoc_handwew,
				IWQF_TWIGGEW_WISING, cwient->name, data);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet,
				"wequest iwq %d faiwed\n", data->iwq);
	}

	data->gpiod_weset = devm_gpiod_get_optionaw(dev, "weset",
							GPIOD_OUT_HIGH);
	if (IS_EWW(data->gpiod_weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->gpiod_weset),
						"wequest weset-gpio faiwed\n");

	mpw_weset(data);

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW,
						mpw_twiggew_handwew, NUWW);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
					"iio twiggewed buffew setup faiwed\n");

	wet = devm_iio_device_wegistew(dev, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
					"unabwe to wegistew iio device\n");

	wetuwn 0;
}

static const stwuct of_device_id mpw_matches[] = {
	{ .compatibwe = "honeyweww,mpwws0025pa" },
	{ }
};
MODUWE_DEVICE_TABWE(of, mpw_matches);

static const stwuct i2c_device_id mpw_id[] = {
	{ "mpwws0025pa" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mpw_id);

static stwuct i2c_dwivew mpw_dwivew = {
	.pwobe		= mpw_pwobe,
	.id_tabwe	= mpw_id,
	.dwivew		= {
		.name		= "mpwws0025pa",
		.of_match_tabwe = mpw_matches,
	},
};
moduwe_i2c_dwivew(mpw_dwivew);

MODUWE_AUTHOW("Andweas Kwingew <ak@it-kwingew.de>");
MODUWE_DESCWIPTION("Honeyweww MPWWS0025PA I2C dwivew");
MODUWE_WICENSE("GPW");
