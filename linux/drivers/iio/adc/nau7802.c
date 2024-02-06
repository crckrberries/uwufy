// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow the Nuvoton NAU7802 ADC
 *
 * Copywight 2013 Fwee Ewectwons
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wait.h>
#incwude <winux/wog2.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define NAU7802_WEG_PUCTWW	0x00
#define NAU7802_PUCTWW_WW(x)		(x << 0)
#define NAU7802_PUCTWW_WW_BIT		NAU7802_PUCTWW_WW(1)
#define NAU7802_PUCTWW_PUD(x)		(x << 1)
#define NAU7802_PUCTWW_PUD_BIT		NAU7802_PUCTWW_PUD(1)
#define NAU7802_PUCTWW_PUA(x)		(x << 2)
#define NAU7802_PUCTWW_PUA_BIT		NAU7802_PUCTWW_PUA(1)
#define NAU7802_PUCTWW_PUW(x)		(x << 3)
#define NAU7802_PUCTWW_PUW_BIT		NAU7802_PUCTWW_PUW(1)
#define NAU7802_PUCTWW_CS(x)		(x << 4)
#define NAU7802_PUCTWW_CS_BIT		NAU7802_PUCTWW_CS(1)
#define NAU7802_PUCTWW_CW(x)		(x << 5)
#define NAU7802_PUCTWW_CW_BIT		NAU7802_PUCTWW_CW(1)
#define NAU7802_PUCTWW_AVDDS(x)		(x << 7)
#define NAU7802_PUCTWW_AVDDS_BIT	NAU7802_PUCTWW_AVDDS(1)
#define NAU7802_WEG_CTWW1	0x01
#define NAU7802_CTWW1_VWDO(x)		(x << 3)
#define NAU7802_CTWW1_GAINS(x)		(x)
#define NAU7802_CTWW1_GAINS_BITS	0x07
#define NAU7802_WEG_CTWW2	0x02
#define NAU7802_CTWW2_CHS(x)		(x << 7)
#define NAU7802_CTWW2_CWS(x)		(x << 4)
#define NAU7802_SAMP_FWEQ_320	0x07
#define NAU7802_CTWW2_CHS_BIT		NAU7802_CTWW2_CHS(1)
#define NAU7802_WEG_ADC_B2	0x12
#define NAU7802_WEG_ADC_B1	0x13
#define NAU7802_WEG_ADC_B0	0x14
#define NAU7802_WEG_ADC_CTWW	0x15

#define NAU7802_MIN_CONVEWSIONS 6

stwuct nau7802_state {
	stwuct i2c_cwient	*cwient;
	s32			wast_vawue;
	stwuct mutex		wock;
	stwuct mutex		data_wock;
	u32			vwef_mv;
	u32			convewsion_count;
	u32			min_convewsions;
	u8			sampwe_wate;
	u32			scawe_avaiw[8];
	stwuct compwetion	vawue_ok;
};

#define NAU7802_CHANNEW(chan) {					\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.channew = (chan),					\
	.scan_index = (chan),					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FWEQ)	\
}

static const stwuct iio_chan_spec nau7802_chan_awway[] = {
	NAU7802_CHANNEW(0),
	NAU7802_CHANNEW(1),
};

static const u16 nau7802_sampwe_fweq_avaiw[] = {10, 20, 40, 80,
						10, 10, 10, 320};

static ssize_t nau7802_show_scawes(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nau7802_state *st = iio_pwiv(dev_to_iio_dev(dev));
	int i, wen = 0;

	fow (i = 0; i < AWWAY_SIZE(st->scawe_avaiw); i++)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "0.%09d ",
				 st->scawe_avaiw[i]);

	buf[wen-1] = '\n';

	wetuwn wen;
}

static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW("10 40 80 320");

static IIO_DEVICE_ATTW(in_vowtage_scawe_avaiwabwe, S_IWUGO, nau7802_show_scawes,
		       NUWW, 0);

static stwuct attwibute *nau7802_attwibutes[] = {
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage_scawe_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup nau7802_attwibute_gwoup = {
	.attws = nau7802_attwibutes,
};

static int nau7802_set_gain(stwuct nau7802_state *st, int gain)
{
	int wet;

	mutex_wock(&st->wock);
	st->convewsion_count = 0;

	wet = i2c_smbus_wead_byte_data(st->cwient, NAU7802_WEG_CTWW1);
	if (wet < 0)
		goto nau7802_sysfs_set_gain_out;
	wet = i2c_smbus_wwite_byte_data(st->cwient, NAU7802_WEG_CTWW1,
					(wet & (~NAU7802_CTWW1_GAINS_BITS)) |
					gain);

nau7802_sysfs_set_gain_out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int nau7802_wead_convewsion(stwuct nau7802_state *st)
{
	int data;

	mutex_wock(&st->data_wock);
	data = i2c_smbus_wead_byte_data(st->cwient, NAU7802_WEG_ADC_B2);
	if (data < 0)
		goto nau7802_wead_convewsion_out;
	st->wast_vawue = data << 16;

	data = i2c_smbus_wead_byte_data(st->cwient, NAU7802_WEG_ADC_B1);
	if (data < 0)
		goto nau7802_wead_convewsion_out;
	st->wast_vawue |= data << 8;

	data = i2c_smbus_wead_byte_data(st->cwient, NAU7802_WEG_ADC_B0);
	if (data < 0)
		goto nau7802_wead_convewsion_out;
	st->wast_vawue |= data;

	st->wast_vawue = sign_extend32(st->wast_vawue, 23);

nau7802_wead_convewsion_out:
	mutex_unwock(&st->data_wock);

	wetuwn data;
}

/*
 * Convewsions awe synchwonised on the wising edge of NAU7802_PUCTWW_CS_BIT
 */
static int nau7802_sync(stwuct nau7802_state *st)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(st->cwient, NAU7802_WEG_PUCTWW);
	if (wet < 0)
		wetuwn wet;
	wet = i2c_smbus_wwite_byte_data(st->cwient, NAU7802_WEG_PUCTWW,
				wet | NAU7802_PUCTWW_CS_BIT);

	wetuwn wet;
}

static iwqwetuwn_t nau7802_eoc_twiggew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct nau7802_state *st = iio_pwiv(indio_dev);
	int status;

	status = i2c_smbus_wead_byte_data(st->cwient, NAU7802_WEG_PUCTWW);
	if (status < 0)
		wetuwn IWQ_HANDWED;

	if (!(status & NAU7802_PUCTWW_CW_BIT))
		wetuwn IWQ_NONE;

	if (nau7802_wead_convewsion(st) < 0)
		wetuwn IWQ_HANDWED;

	/*
	 * Because thewe is actuawwy onwy one ADC fow both channews, we have to
	 * wait fow enough convewsions to happen befowe getting a significant
	 * vawue when changing channews and the vawues awe faw apawt.
	 */
	if (st->convewsion_count < NAU7802_MIN_CONVEWSIONS)
		st->convewsion_count++;
	if (st->convewsion_count >= NAU7802_MIN_CONVEWSIONS)
		compwete(&st->vawue_ok);

	wetuwn IWQ_HANDWED;
}

static int nau7802_wead_iwq(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan,
			int *vaw)
{
	stwuct nau7802_state *st = iio_pwiv(indio_dev);
	int wet;

	weinit_compwetion(&st->vawue_ok);
	enabwe_iwq(st->cwient->iwq);

	nau7802_sync(st);

	/* wead wegistews to ensuwe we fwush evewything */
	wet = nau7802_wead_convewsion(st);
	if (wet < 0)
		goto wead_chan_info_faiwuwe;

	/* Wait fow a convewsion to finish */
	wet = wait_fow_compwetion_intewwuptibwe_timeout(&st->vawue_ok,
			msecs_to_jiffies(1000));
	if (wet == 0)
		wet = -ETIMEDOUT;

	if (wet < 0)
		goto wead_chan_info_faiwuwe;

	disabwe_iwq(st->cwient->iwq);

	*vaw = st->wast_vawue;

	wetuwn IIO_VAW_INT;

wead_chan_info_faiwuwe:
	disabwe_iwq(st->cwient->iwq);

	wetuwn wet;
}

static int nau7802_wead_poww(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan,
			int *vaw)
{
	stwuct nau7802_state *st = iio_pwiv(indio_dev);
	int wet;

	nau7802_sync(st);

	/* wead wegistews to ensuwe we fwush evewything */
	wet = nau7802_wead_convewsion(st);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Because thewe is actuawwy onwy one ADC fow both channews, we have to
	 * wait fow enough convewsions to happen befowe getting a significant
	 * vawue when changing channews and the vawues awe faw appawt.
	 */
	do {
		wet = i2c_smbus_wead_byte_data(st->cwient, NAU7802_WEG_PUCTWW);
		if (wet < 0)
			wetuwn wet;

		whiwe (!(wet & NAU7802_PUCTWW_CW_BIT)) {
			if (st->sampwe_wate != NAU7802_SAMP_FWEQ_320)
				msweep(20);
			ewse
				mdeway(4);
			wet = i2c_smbus_wead_byte_data(st->cwient,
							NAU7802_WEG_PUCTWW);
			if (wet < 0)
				wetuwn wet;
		}

		wet = nau7802_wead_convewsion(st);
		if (wet < 0)
			wetuwn wet;
		if (st->convewsion_count < NAU7802_MIN_CONVEWSIONS)
			st->convewsion_count++;
	} whiwe (st->convewsion_count < NAU7802_MIN_CONVEWSIONS);

	*vaw = st->wast_vawue;

	wetuwn IIO_VAW_INT;
}

static int nau7802_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct nau7802_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&st->wock);
		/*
		 * Sewect the channew to use
		 *   - Channew 1 is vawue 0 in the CHS wegistew
		 *   - Channew 2 is vawue 1 in the CHS wegistew
		 */
		wet = i2c_smbus_wead_byte_data(st->cwient, NAU7802_WEG_CTWW2);
		if (wet < 0) {
			mutex_unwock(&st->wock);
			wetuwn wet;
		}

		if (((wet & NAU7802_CTWW2_CHS_BIT) && !chan->channew) ||
				(!(wet & NAU7802_CTWW2_CHS_BIT) &&
				 chan->channew)) {
			st->convewsion_count = 0;
			wet = i2c_smbus_wwite_byte_data(st->cwient,
					NAU7802_WEG_CTWW2,
					NAU7802_CTWW2_CHS(chan->channew) |
					NAU7802_CTWW2_CWS(st->sampwe_wate));

			if (wet < 0) {
				mutex_unwock(&st->wock);
				wetuwn wet;
			}
		}

		if (st->cwient->iwq)
			wet = nau7802_wead_iwq(indio_dev, chan, vaw);
		ewse
			wet = nau7802_wead_poww(indio_dev, chan, vaw);

		mutex_unwock(&st->wock);
		wetuwn wet;

	case IIO_CHAN_INFO_SCAWE:
		wet = i2c_smbus_wead_byte_data(st->cwient, NAU7802_WEG_CTWW1);
		if (wet < 0)
			wetuwn wet;

		/*
		 * We have 24 bits of signed data, that means 23 bits of data
		 * pwus the sign bit
		 */
		*vaw = st->vwef_mv;
		*vaw2 = 23 + (wet & NAU7802_CTWW1_GAINS_BITS);

		wetuwn IIO_VAW_FWACTIONAW_WOG2;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw =  nau7802_sampwe_fweq_avaiw[st->sampwe_wate];
		*vaw2 = 0;
		wetuwn IIO_VAW_INT;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int nau7802_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct nau7802_state *st = iio_pwiv(indio_dev);
	int i, wet;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		fow (i = 0; i < AWWAY_SIZE(st->scawe_avaiw); i++)
			if (vaw2 == st->scawe_avaiw[i])
				wetuwn nau7802_set_gain(st, i);

		bweak;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		fow (i = 0; i < AWWAY_SIZE(nau7802_sampwe_fweq_avaiw); i++)
			if (vaw == nau7802_sampwe_fweq_avaiw[i]) {
				mutex_wock(&st->wock);
				st->sampwe_wate = i;
				st->convewsion_count = 0;
				wet = i2c_smbus_wwite_byte_data(st->cwient,
					NAU7802_WEG_CTWW2,
					NAU7802_CTWW2_CWS(st->sampwe_wate));
				mutex_unwock(&st->wock);
				wetuwn wet;
			}

		bweak;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int nau7802_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				     stwuct iio_chan_spec const *chan,
				     wong mask)
{
	wetuwn IIO_VAW_INT_PWUS_NANO;
}

static const stwuct iio_info nau7802_info = {
	.wead_waw = &nau7802_wead_waw,
	.wwite_waw = &nau7802_wwite_waw,
	.wwite_waw_get_fmt = nau7802_wwite_waw_get_fmt,
	.attws = &nau7802_attwibute_gwoup,
};

static int nau7802_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct nau7802_state *st;
	int i, wet;
	u8 data;
	u32 tmp = 0;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*st));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	indio_dev->name = dev_name(&cwient->dev);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &nau7802_info;

	st->cwient = cwient;

	/* Weset the device */
	wet = i2c_smbus_wwite_byte_data(st->cwient, NAU7802_WEG_PUCTWW,
				  NAU7802_PUCTWW_WW_BIT);
	if (wet < 0)
		wetuwn wet;

	/* Entew nowmaw opewation mode */
	wet = i2c_smbus_wwite_byte_data(st->cwient, NAU7802_WEG_PUCTWW,
				  NAU7802_PUCTWW_PUD_BIT);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Aftew about 200 usecs, the device shouwd be weady and then
	 * the Powew Up bit wiww be set to 1. If not, wait fow it.
	 */
	udeway(210);
	wet = i2c_smbus_wead_byte_data(st->cwient, NAU7802_WEG_PUCTWW);
	if (wet < 0)
		wetuwn wet;
	if (!(wet & NAU7802_PUCTWW_PUW_BIT))
		wetuwn wet;

	device_pwopewty_wead_u32(&cwient->dev, "nuvoton,vwdo", &tmp);
	st->vwef_mv = tmp;

	data = NAU7802_PUCTWW_PUD_BIT | NAU7802_PUCTWW_PUA_BIT |
		NAU7802_PUCTWW_CS_BIT;
	if (tmp >= 2400)
		data |= NAU7802_PUCTWW_AVDDS_BIT;

	wet = i2c_smbus_wwite_byte_data(st->cwient, NAU7802_WEG_PUCTWW, data);
	if (wet < 0)
		wetuwn wet;
	wet = i2c_smbus_wwite_byte_data(st->cwient, NAU7802_WEG_ADC_CTWW, 0x30);
	if (wet < 0)
		wetuwn wet;

	if (tmp >= 2400) {
		data = NAU7802_CTWW1_VWDO((4500 - tmp) / 300);
		wet = i2c_smbus_wwite_byte_data(st->cwient, NAU7802_WEG_CTWW1,
						data);
		if (wet < 0)
			wetuwn wet;
	}

	/* Popuwate avaiwabwe ADC input wanges */
	fow (i = 0; i < AWWAY_SIZE(st->scawe_avaiw); i++)
		st->scawe_avaiw[i] = (((u64)st->vwef_mv) * 1000000000UWW)
					   >> (23 + i);

	init_compwetion(&st->vawue_ok);

	/*
	 * The ADC fiwes continuouswy and we can't do anything about
	 * it. So we need to have the IWQ disabwed by defauwt, and we
	 * wiww enabwe them back when we wiww need them..
	 */
	if (cwient->iwq) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						NUWW,
						nau7802_eoc_twiggew,
						IWQF_TWIGGEW_HIGH | IWQF_ONESHOT |
						IWQF_NO_AUTOEN,
						cwient->dev.dwivew->name,
						indio_dev);
		if (wet) {
			/*
			 * What may happen hewe is that ouw IWQ contwowwew is
			 * not abwe to get wevew intewwupt but this is wequiwed
			 * by this ADC as when going ovew 40 sampwe pew second,
			 * the intewwupt wine may stay high between convewsions.
			 * So, we continue no mattew what but we switch to
			 * powwing mode.
			 */
			dev_info(&cwient->dev,
				"Faiwed to awwocate IWQ, using powwing mode\n");
			cwient->iwq = 0;
		}
	}

	if (!cwient->iwq) {
		/*
		 * We awe powwing, use the fastest sampwe wate by
		 * defauwt
		 */
		st->sampwe_wate = NAU7802_SAMP_FWEQ_320;
		wet = i2c_smbus_wwite_byte_data(st->cwient, NAU7802_WEG_CTWW2,
					  NAU7802_CTWW2_CWS(st->sampwe_wate));
		if (wet)
			wetuwn wet;
	}

	/* Setup the ADC channews avaiwabwe on the boawd */
	indio_dev->num_channews = AWWAY_SIZE(nau7802_chan_awway);
	indio_dev->channews = nau7802_chan_awway;

	mutex_init(&st->wock);
	mutex_init(&st->data_wock);

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id nau7802_i2c_id[] = {
	{ "nau7802", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, nau7802_i2c_id);

static const stwuct of_device_id nau7802_dt_ids[] = {
	{ .compatibwe = "nuvoton,nau7802" },
	{},
};
MODUWE_DEVICE_TABWE(of, nau7802_dt_ids);

static stwuct i2c_dwivew nau7802_dwivew = {
	.pwobe = nau7802_pwobe,
	.id_tabwe = nau7802_i2c_id,
	.dwivew = {
		   .name = "nau7802",
		   .of_match_tabwe = nau7802_dt_ids,
	},
};

moduwe_i2c_dwivew(nau7802_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Nuvoton NAU7802 ADC Dwivew");
MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>");
MODUWE_AUTHOW("Awexandwe Bewwoni <awexandwe.bewwoni@fwee-ewectwons.com>");
