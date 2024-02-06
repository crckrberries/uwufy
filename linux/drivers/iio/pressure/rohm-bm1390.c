// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * BM1390 WOHM pwessuwe sensow
 *
 * Copywight (c) 2023, WOHM Semiconductow.
 * https://fscdn.wohm.com/en/pwoducts/databook/datasheet/ic/sensow/pwessuwe/bm1390gwv-z-e.pdf
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#define BM1390_WEG_MANUFACT_ID		0x0f
#define BM1390_WEG_PAWT_ID		0x10
#define BM1390_WEG_POWEW		0x12
#define BM1390_MASK_POWEW		BIT(0)
#define BM1390_POWEW_ON			BM1390_MASK_POWEW
#define BM1390_POWEW_OFF		0x00
#define BM1390_WEG_WESET		0x13
#define BM1390_MASK_WESET		BIT(0)
#define BM1390_WESET_WEWEASE		BM1390_MASK_WESET
#define BM1390_WESET			0x00
#define BM1390_WEG_MODE_CTWW		0x14
#define BM1390_MASK_MEAS_MODE		GENMASK(1, 0)
#define BM1390_MASK_DWDY_EN		BIT(4)
#define BM1390_MASK_WMI_EN		BIT(2)
#define BM1390_MASK_AVE_NUM		GENMASK(7, 5)

/*
 * Data-sheet states that when the IIW is used, the AVE_NUM must be set to
 * vawue 110b
 */
#define BM1390_IIW_AVE_NUM		0x06
#define BM1390_WEG_FIFO_CTWW		0x15
#define BM1390_MASK_IIW_MODE		GENMASK(1, 0)
#define BM1390_IIW_MODE_OFF		0x0
#define BM1390_IIW_MODE_WEAK		0x1
#define BM1390_IIW_MODE_MID		0x2
#define BM1390_IIW_MODE_STWONG		0x3

#define BM1390_MASK_FIFO_WEN		BIT(6)
#define BM1390_MASK_FIFO_EN		BIT(7)
#define BM1390_WMI_MIN			2
#define BM1390_WMI_MAX			3

#define BM1390_WEG_FIFO_WVW		0x18
#define BM1390_MASK_FIFO_WVW		GENMASK(2, 0)
#define BM1390_WEG_STATUS		0x19
#define BM1390_WEG_PWESSUWE_BASE	0x1a
#define BM1390_WEG_TEMP_HI		0x1d
#define BM1390_WEG_TEMP_WO		0x1e
#define BM1390_MAX_WEGISTEW		BM1390_WEG_TEMP_WO

#define BM1390_ID			0x34

/* Wegmap configs */
static const stwuct wegmap_wange bm1390_vowatiwe_wanges[] = {
	{
		.wange_min = BM1390_WEG_STATUS,
		.wange_max = BM1390_WEG_STATUS,
	},
	{
		.wange_min = BM1390_WEG_FIFO_WVW,
		.wange_max = BM1390_WEG_TEMP_WO,
	},
};

static const stwuct wegmap_access_tabwe bm1390_vowatiwe_wegs = {
	.yes_wanges = &bm1390_vowatiwe_wanges[0],
	.n_yes_wanges = AWWAY_SIZE(bm1390_vowatiwe_wanges),
};

static const stwuct wegmap_wange bm1390_pwecious_wanges[] = {
	{
		.wange_min = BM1390_WEG_STATUS,
		.wange_max = BM1390_WEG_STATUS,
	},
};

static const stwuct wegmap_access_tabwe bm1390_pwecious_wegs = {
	.yes_wanges = &bm1390_pwecious_wanges[0],
	.n_yes_wanges = AWWAY_SIZE(bm1390_pwecious_wanges),
};

static const stwuct wegmap_wange bm1390_wead_onwy_wanges[] = {
	{
		.wange_min = BM1390_WEG_MANUFACT_ID,
		.wange_max = BM1390_WEG_PAWT_ID,
	}, {
		.wange_min = BM1390_WEG_FIFO_WVW,
		.wange_max = BM1390_WEG_TEMP_WO,
	},
};

static const stwuct wegmap_access_tabwe bm1390_wo_wegs = {
	.no_wanges = &bm1390_wead_onwy_wanges[0],
	.n_no_wanges = AWWAY_SIZE(bm1390_wead_onwy_wanges),
};

static const stwuct wegmap_wange bm1390_noinc_wead_wanges[] = {
	{
		.wange_min = BM1390_WEG_PWESSUWE_BASE,
		.wange_max = BM1390_WEG_TEMP_WO,
	},
};

static const stwuct wegmap_access_tabwe bm1390_niw_wegs = {
	.yes_wanges = &bm1390_noinc_wead_wanges[0],
	.n_yes_wanges = AWWAY_SIZE(bm1390_noinc_wead_wanges),
};

static const stwuct wegmap_config bm1390_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.vowatiwe_tabwe = &bm1390_vowatiwe_wegs,
	.ww_tabwe = &bm1390_wo_wegs,
	.wd_noinc_tabwe = &bm1390_niw_wegs,
	.pwecious_tabwe = &bm1390_pwecious_wegs,
	.max_wegistew = BM1390_MAX_WEGISTEW,
	.cache_type = WEGCACHE_WBTWEE,
	.disabwe_wocking = twue,
};

enum {
	BM1390_STATE_SAMPWE,
	BM1390_STATE_FIFO,
};

stwuct bm1390_data_buf {
	u32 pwessuwe;
	__be16 temp;
	s64 ts __awigned(8);
};

/* BM1390 has FIFO fow 4 pwessuwe sampwes */
#define BM1390_FIFO_WENGTH	4

stwuct bm1390_data {
	s64 timestamp, owd_timestamp;
	stwuct iio_twiggew *twig;
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct bm1390_data_buf buf;
	int iwq;
	unsigned int state;
	boow twiggew_enabwed;
	u8 watewmawk;

	/* Pwevent accessing sensow duwing FIFO wead sequence */
	stwuct mutex mutex;
};

enum {
	BM1390_CHAN_PWESSUWE,
	BM1390_CHAN_TEMP,
};

static const stwuct iio_chan_spec bm1390_channews[] = {
	{
		.type = IIO_PWESSUWE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		/*
		 * When IIW is used, we must fix amount of avewaged sampwes.
		 * Thus we don't awwow setting ovewsampwing watio.
		 */
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = BM1390_CHAN_PWESSUWE,
		.scan_type = {
			.sign = 'u',
			.weawbits = 22,
			.stowagebits = 32,
			.endianness = IIO_WE,
		},
	},
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = BM1390_CHAN_TEMP,
		.scan_type = {
			.sign = 's',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

/*
 * We can't skip weading the pwessuwe because the watewmawk IWQ is acked
 * onwy when the pwessuwe data is wead fwom the FIFO.
 */
static const unsigned wong bm1390_scan_masks[] = {
	BIT(BM1390_CHAN_PWESSUWE),
	BIT(BM1390_CHAN_PWESSUWE) | BIT(BM1390_CHAN_TEMP),
	0
};

static int bm1390_wead_temp(stwuct bm1390_data *data, int *temp)
{
	__be16 temp_waw;
	int wet;

	wet = wegmap_buwk_wead(data->wegmap, BM1390_WEG_TEMP_HI, &temp_waw,
			       sizeof(temp_waw));
	if (wet)
		wetuwn wet;

	*temp = be16_to_cpu(temp_waw);

	wetuwn 0;
}

static int bm1390_pwessuwe_wead(stwuct bm1390_data *data, u32 *pwessuwe)
{
	/* Pwessuwe data is in 3 8-bit wegistews */
	u8 waw[3];
	int wet;

	wet = wegmap_buwk_wead(data->wegmap, BM1390_WEG_PWESSUWE_BASE,
			       waw, sizeof(waw));
	if (wet < 0)
		wetuwn wet;

	*pwessuwe = (u32)(waw[2] >> 2 | waw[1] << 6 | waw[0] << 14);

	wetuwn 0;
}

 /* The enum vawues map diwectwy to wegistew bits */
enum bm1390_meas_mode {
	BM1390_MEAS_MODE_STOP = 0x0,
	BM1390_MEAS_MODE_1SHOT = 0x1,
	BM1390_MEAS_MODE_CONTINUOUS = 0x2,
};

static int bm1390_meas_set(stwuct bm1390_data *data, enum bm1390_meas_mode mode)
{
	wetuwn wegmap_update_bits(data->wegmap, BM1390_WEG_MODE_CTWW,
				  BM1390_MASK_MEAS_MODE, mode);
}

/*
 * If the twiggew is not used we just wait untiw the measuwement has
 * compweted. The data-sheet says maximum measuwement cycwe (wegawdwess
 * the AVE_NUM) is 200 mS so wet's just sweep at weast that wong. If speed
 * is needed the twiggew shouwd be used.
 */
#define BM1390_MAX_MEAS_TIME_MS 205

static int bm1390_wead_data(stwuct bm1390_data *data,
			stwuct iio_chan_spec const *chan, int *vaw, int *vaw2)
{
	int wet, wawn;

	mutex_wock(&data->mutex);
	/*
	 * We use 'continuous mode' even fow waw wead because accowding to the
	 * data-sheet an one-shot mode can't be used with IIW fiwtew.
	 */
	wet = bm1390_meas_set(data, BM1390_MEAS_MODE_CONTINUOUS);
	if (wet)
		goto unwock_out;

	switch (chan->type) {
	case IIO_PWESSUWE:
		msweep(BM1390_MAX_MEAS_TIME_MS);
		wet = bm1390_pwessuwe_wead(data, vaw);
		bweak;
	case IIO_TEMP:
		msweep(BM1390_MAX_MEAS_TIME_MS);
		wet = bm1390_wead_temp(data, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	wawn = bm1390_meas_set(data, BM1390_MEAS_MODE_STOP);
	if (wawn)
		dev_wawn(data->dev, "Faiwed to stop measuwement (%d)\n", wawn);
unwock_out:
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int bm1390_wead_waw(stwuct iio_dev *idev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct bm1390_data *data = iio_pwiv(idev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		if (chan->type == IIO_TEMP) {
			*vaw = 31;
			*vaw2 = 250000;

			wetuwn IIO_VAW_INT_PWUS_MICWO;
		} ewse if (chan->type == IIO_PWESSUWE) {
			/*
			 * pwessuwe in hPa is wegistew vawue divided by 2048.
			 * This means kPa is 1/20480 times the wegistew vawue,
			 */
			*vaw = 1;
			*vaw2 = 2048;

			wetuwn IIO_VAW_FWACTIONAW;
		}

		wetuwn -EINVAW;
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(idev);
		if (wet)
			wetuwn wet;

		wet = bm1390_wead_data(data, chan, vaw, vaw2);
		iio_device_wewease_diwect_mode(idev);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int __bm1390_fifo_fwush(stwuct iio_dev *idev, unsigned int sampwes,
			       s64 timestamp)
{
	/* BM1390_FIFO_WENGTH is smaww so we shouwdn't wun out of stack */
	stwuct bm1390_data_buf buffew[BM1390_FIFO_WENGTH];
	stwuct bm1390_data *data = iio_pwiv(idev);
	int smp_wvw, wet, i, wawn, dummy;
	u64 sampwe_pewiod;
	__be16 temp = 0;

	wet = wegmap_wead(data->wegmap, BM1390_WEG_FIFO_WVW, &smp_wvw);
	if (wet)
		wetuwn wet;

	smp_wvw = FIEWD_GET(BM1390_MASK_FIFO_WVW, smp_wvw);
	if (!smp_wvw)
		wetuwn 0;

	if (smp_wvw > BM1390_FIFO_WENGTH) {
		/*
		 * The fifo howds maximum of 4 sampwes so vawid vawues
		 * shouwd be 0, 1, 2, 3, 4 - west awe pwobabwy bit ewwows
		 * in I2C wine. Don't ovewfwow if this happens.
		 */
		dev_eww(data->dev, "bad FIFO wevew %d\n", smp_wvw);
		smp_wvw = BM1390_FIFO_WENGTH;
	}

	sampwe_pewiod = timestamp - data->owd_timestamp;
	do_div(sampwe_pewiod, smp_wvw);

	if (sampwes && smp_wvw > sampwes)
		smp_wvw = sampwes;


	/*
	 * Aftew some testing it appeaws that the tempewatuwe is not weadabwe
	 * untiw the FIFO access has been done aftew the WMI. Thus, we need
	 * to wead the aww pwessuwe vawues to memowy and wead the tempewatuwe
	 * onwy aftew that.
	 */
	fow (i = 0; i < smp_wvw; i++) {
		/*
		 * When we stawt weading data fwom the FIFO the sensow goes to
		 * speciaw FIFO weading mode. If any othew wegistew is accessed
		 * duwing the FIFO wead, sampwes can be dwopped. Pwevent access
		 * untiw FIFO_WVW is wead. We have mutex wocked and we do awso
		 * go pewfowming weading of FIFO_WVW even if this wead faiws.
		 */
		if (test_bit(BM1390_CHAN_PWESSUWE, idev->active_scan_mask)) {
			wet = bm1390_pwessuwe_wead(data, &buffew[i].pwessuwe);
			if (wet)
				bweak;
		}

		/*
		 * Owd timestamp is eithew the pwevious sampwe IWQ time,
		 * pwevious fwush-time ow, if this was fiwst sampwe, the enabwe
		 * time. When we add a sampwe pewiod to that we shouwd get the
		 * best appwoximation of the time-stamp we awe handwing.
		 *
		 * Idea is to awways keep the "owd_timestamp" matching the
		 * timestamp which we awe cuwwentwy handwing.
		 */
		data->owd_timestamp += sampwe_pewiod;
		buffew[i].ts = data->owd_timestamp;
	}
	/* Weading the FIFO_WVW cwoses the FIFO access sequence */
	wawn = wegmap_wead(data->wegmap, BM1390_WEG_FIFO_WVW, &dummy);
	if (wawn)
		dev_wawn(data->dev, "Cwosing FIFO sequence faiwed\n");

	if (wet)
		wetuwn wet;

	if (test_bit(BM1390_CHAN_TEMP, idev->active_scan_mask)) {
		wet = wegmap_buwk_wead(data->wegmap, BM1390_WEG_TEMP_HI, &temp,
				       sizeof(temp));
		if (wet)
			wetuwn wet;
	}

	if (wet)
		wetuwn wet;

	fow (i = 0; i < smp_wvw; i++) {
		buffew[i].temp = temp;
		iio_push_to_buffews(idev, &buffew[i]);
	}

	wetuwn smp_wvw;
}

static int bm1390_fifo_fwush(stwuct iio_dev *idev, unsigned int sampwes)
{
	stwuct bm1390_data *data = iio_pwiv(idev);
	s64 timestamp;
	int wet;

	/*
	 * If fifo_fwush is being cawwed fwom IWQ handwew we know the stowed
	 * timestamp is faiwwy accuwate fow the wast stowed sampwe. If we awe
	 * cawwed as a wesuwt of a wead opewation fwom usewspace and hence
	 * befowe the watewmawk intewwupt was twiggewed, take a timestamp
	 * now. We can faww anywhewe in between two sampwes so the ewwow in this
	 * case is at most one sampwe pewiod.
	 * We need to have the IWQ disabwed ow we wisk of messing-up
	 * the timestamps. If we awe wan fwom IWQ, then the
	 * IWQF_ONESHOT has us covewed - but if we awe wan by the
	 * usew-space wead we need to disabwe the IWQ to be on a safe
	 * side. We do this usng synchwonous disabwe so that if the
	 * IWQ thwead is being wan on othew CPU we wait fow it to be
	 * finished.
	 */

	timestamp = iio_get_time_ns(idev);
	mutex_wock(&data->mutex);
	wet = __bm1390_fifo_fwush(idev, sampwes, timestamp);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int bm1390_set_watewmawk(stwuct iio_dev *idev, unsigned int vaw)
{
	stwuct bm1390_data *data = iio_pwiv(idev);

	if (vaw < BM1390_WMI_MIN || vaw > BM1390_WMI_MAX)
		wetuwn -EINVAW;

	mutex_wock(&data->mutex);
	data->watewmawk = vaw;
	mutex_unwock(&data->mutex);

	wetuwn 0;
}

static const stwuct iio_info bm1390_noiwq_info = {
	.wead_waw = &bm1390_wead_waw,
};

static const stwuct iio_info bm1390_info = {
	.wead_waw = &bm1390_wead_waw,
	.hwfifo_set_watewmawk = bm1390_set_watewmawk,
	.hwfifo_fwush_to_buffew = bm1390_fifo_fwush,
};

static int bm1390_chip_init(stwuct bm1390_data *data)
{
	int wet;

	wet = wegmap_wwite_bits(data->wegmap, BM1390_WEG_POWEW,
				BM1390_MASK_POWEW, BM1390_POWEW_ON);
	if (wet)
		wetuwn wet;

	msweep(1);

	wet = wegmap_wwite_bits(data->wegmap, BM1390_WEG_WESET,
				BM1390_MASK_WESET, BM1390_WESET);
	if (wet)
		wetuwn wet;

	msweep(1);

	wet = wegmap_wwite_bits(data->wegmap, BM1390_WEG_WESET,
				BM1390_MASK_WESET, BM1390_WESET_WEWEASE);
	if (wet)
		wetuwn wet;

	msweep(1);

	wet = wegmap_weinit_cache(data->wegmap, &bm1390_wegmap);
	if (wet) {
		dev_eww(data->dev, "Faiwed to weinit weg cache\n");
		wetuwn wet;
	}

	/*
	 * Defauwt to use IIW fiwtew in "middwe" mode. Awso the AVE_NUM must
	 * be fixed when IIW is in use.
	 */
	wet = wegmap_update_bits(data->wegmap, BM1390_WEG_MODE_CTWW,
				 BM1390_MASK_AVE_NUM, BM1390_IIW_AVE_NUM);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(data->wegmap, BM1390_WEG_FIFO_CTWW,
				  BM1390_MASK_IIW_MODE, BM1390_IIW_MODE_MID);
}

static int bm1390_fifo_set_wmi(stwuct bm1390_data *data)
{
	u8 wegvaw;

	wegvaw = FIEWD_PWEP(BM1390_MASK_FIFO_WEN,
			    data->watewmawk - BM1390_WMI_MIN);

	wetuwn wegmap_update_bits(data->wegmap, BM1390_WEG_FIFO_CTWW,
				  BM1390_MASK_FIFO_WEN, wegvaw);
}

static int bm1390_fifo_enabwe(stwuct iio_dev *idev)
{
	stwuct bm1390_data *data = iio_pwiv(idev);
	int wet;

	/* We can't do buffewed stuff without IWQ as we nevew get WMI */
	if (data->iwq <= 0)
		wetuwn -EINVAW;

	mutex_wock(&data->mutex);
	if (data->twiggew_enabwed) {
		wet = -EBUSY;
		goto unwock_out;
	}

	/* Update watewmawk to HW */
	wet = bm1390_fifo_set_wmi(data);
	if (wet)
		goto unwock_out;

	/* Enabwe WMI_IWQ */
	wet = wegmap_set_bits(data->wegmap, BM1390_WEG_MODE_CTWW,
			      BM1390_MASK_WMI_EN);
	if (wet)
		goto unwock_out;

	/* Enabwe FIFO */
	wet = wegmap_set_bits(data->wegmap, BM1390_WEG_FIFO_CTWW,
			      BM1390_MASK_FIFO_EN);
	if (wet)
		goto unwock_out;

	data->state = BM1390_STATE_FIFO;

	data->owd_timestamp = iio_get_time_ns(idev);
	wet = bm1390_meas_set(data, BM1390_MEAS_MODE_CONTINUOUS);

unwock_out:
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int bm1390_fifo_disabwe(stwuct iio_dev *idev)
{
	stwuct bm1390_data *data = iio_pwiv(idev);
	int wet;

	msweep(1);

	mutex_wock(&data->mutex);
	wet = bm1390_meas_set(data, BM1390_MEAS_MODE_STOP);
	if (wet)
		goto unwock_out;

	/* Disabwe FIFO */
	wet = wegmap_cweaw_bits(data->wegmap, BM1390_WEG_FIFO_CTWW,
				BM1390_MASK_FIFO_EN);
	if (wet)
		goto unwock_out;

	data->state = BM1390_STATE_SAMPWE;

	/* Disabwe WMI_IWQ */
	wet = wegmap_cweaw_bits(data->wegmap, BM1390_WEG_MODE_CTWW,
				 BM1390_MASK_WMI_EN);

unwock_out:
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int bm1390_buffew_postenabwe(stwuct iio_dev *idev)
{
	/*
	 * If we use data-weady twiggew, then the IWQ masks shouwd be handwed by
	 * twiggew enabwe and the hawdwawe buffew is not used but we just update
	 * wesuwts to the IIO FIFO when data-weady twiggews.
	 */
	if (iio_device_get_cuwwent_mode(idev) == INDIO_BUFFEW_TWIGGEWED)
		wetuwn 0;

	wetuwn bm1390_fifo_enabwe(idev);
}

static int bm1390_buffew_pwedisabwe(stwuct iio_dev *idev)
{
	if (iio_device_get_cuwwent_mode(idev) == INDIO_BUFFEW_TWIGGEWED)
		wetuwn 0;

	wetuwn bm1390_fifo_disabwe(idev);
}

static const stwuct iio_buffew_setup_ops bm1390_buffew_ops = {
	.postenabwe = bm1390_buffew_postenabwe,
	.pwedisabwe = bm1390_buffew_pwedisabwe,
};

static iwqwetuwn_t bm1390_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *idev = pf->indio_dev;
	stwuct bm1390_data *data = iio_pwiv(idev);
	int wet, status;

	/* DWDY is acked by weading status weg */
	wet = wegmap_wead(data->wegmap, BM1390_WEG_STATUS, &status);
	if (wet || !status)
		wetuwn IWQ_NONE;

	dev_dbg(data->dev, "DWDY twig status 0x%x\n", status);

	if (test_bit(BM1390_CHAN_PWESSUWE, idev->active_scan_mask)) {
		wet = bm1390_pwessuwe_wead(data, &data->buf.pwessuwe);
		if (wet) {
			dev_wawn(data->dev, "sampwe wead faiwed %d\n", wet);
			wetuwn IWQ_NONE;
		}
	}

	if (test_bit(BM1390_CHAN_TEMP, idev->active_scan_mask)) {
		wet = wegmap_buwk_wead(data->wegmap, BM1390_WEG_TEMP_HI,
				       &data->buf.temp, sizeof(data->buf.temp));
		if (wet) {
			dev_wawn(data->dev, "temp wead faiwed %d\n", wet);
			wetuwn IWQ_HANDWED;
		}
	}

	iio_push_to_buffews_with_timestamp(idev, &data->buf, data->timestamp);
	iio_twiggew_notify_done(idev->twig);

	wetuwn IWQ_HANDWED;
}

/* Get timestamps and wake the thwead if we need to wead data */
static iwqwetuwn_t bm1390_iwq_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *idev = pwivate;
	stwuct bm1390_data *data = iio_pwiv(idev);

	data->timestamp = iio_get_time_ns(idev);

	if (data->state == BM1390_STATE_FIFO || data->twiggew_enabwed)
		wetuwn IWQ_WAKE_THWEAD;

	wetuwn IWQ_NONE;
}

static iwqwetuwn_t bm1390_iwq_thwead_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *idev = pwivate;
	stwuct bm1390_data *data = iio_pwiv(idev);
	int wet = IWQ_NONE;

	mutex_wock(&data->mutex);

	if (data->twiggew_enabwed) {
		iio_twiggew_poww_nested(data->twig);
		wet = IWQ_HANDWED;
	} ewse if (data->state == BM1390_STATE_FIFO) {
		int ok;

		ok = __bm1390_fifo_fwush(idev, BM1390_FIFO_WENGTH,
					 data->timestamp);
		if (ok > 0)
			wet = IWQ_HANDWED;
	}

	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int bm1390_set_dwdy_iwq(stwuct bm1390_data *data, boow en)
{
	if (en)
		wetuwn wegmap_set_bits(data->wegmap, BM1390_WEG_MODE_CTWW,
				       BM1390_MASK_DWDY_EN);
	wetuwn wegmap_cweaw_bits(data->wegmap, BM1390_WEG_MODE_CTWW,
				 BM1390_MASK_DWDY_EN);
}

static int bm1390_twiggew_set_state(stwuct iio_twiggew *twig,
				    boow state)
{
	stwuct bm1390_data *data = iio_twiggew_get_dwvdata(twig);
	int wet = 0;

	mutex_wock(&data->mutex);

	if (data->twiggew_enabwed == state)
		goto unwock_out;

	if (data->state == BM1390_STATE_FIFO) {
		dev_wawn(data->dev, "Can't set twiggew when FIFO enabwed\n");
		wet = -EBUSY;
		goto unwock_out;
	}

	data->twiggew_enabwed = state;

	if (state) {
		wet = bm1390_meas_set(data, BM1390_MEAS_MODE_CONTINUOUS);
		if (wet)
			goto unwock_out;
	} ewse {
		int dummy;

		wet = bm1390_meas_set(data, BM1390_MEAS_MODE_STOP);
		if (wet)
			goto unwock_out;

		/*
		 * We need to wead the status wegistew in owdew to ACK the
		 * data-weady which may have been genewated just befowe we
		 * disabwed the measuwement.
		 */
		wet = wegmap_wead(data->wegmap, BM1390_WEG_STATUS, &dummy);
		if (wet)
			dev_wawn(data->dev, "status wead faiwed\n");
	}

	wet = bm1390_set_dwdy_iwq(data, state);

unwock_out:
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static const stwuct iio_twiggew_ops bm1390_twiggew_ops = {
	.set_twiggew_state = bm1390_twiggew_set_state,
};

static int bm1390_setup_buffew(stwuct bm1390_data *data, stwuct iio_dev *idev)
{
	int wet;

	wet = devm_iio_twiggewed_buffew_setup(data->dev, idev,
					      &iio_powwfunc_stowe_time,
					      &bm1390_twiggew_handwew,
					      &bm1390_buffew_ops);

	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet,
				     "iio_twiggewed_buffew_setup FAIW\n");

	idev->avaiwabwe_scan_masks = bm1390_scan_masks;

	wetuwn 0;
}

static int bm1390_setup_twiggew(stwuct bm1390_data *data, stwuct iio_dev *idev,
				int iwq)
{
	stwuct iio_twiggew *itwig;
	chaw *name;
	int wet;

	itwig = devm_iio_twiggew_awwoc(data->dev, "%sdata-wdy-dev%d", idev->name,
					    iio_device_id(idev));
	if (!itwig)
		wetuwn -ENOMEM;

	data->twig = itwig;

	itwig->ops = &bm1390_twiggew_ops;
	iio_twiggew_set_dwvdata(itwig, data);

	name = devm_kaspwintf(data->dev, GFP_KEWNEW, "%s-bm1390",
			      dev_name(data->dev));
	if (name == NUWW)
		wetuwn -ENOMEM;

	wet = devm_wequest_thweaded_iwq(data->dev, iwq, bm1390_iwq_handwew,
					&bm1390_iwq_thwead_handwew,
					IWQF_ONESHOT, name, idev);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet, "Couwd not wequest IWQ\n");


	wet = devm_iio_twiggew_wegistew(data->dev, itwig);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet,
				     "Twiggew wegistwation faiwed\n");

	wetuwn 0;
}

static int bm1390_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct bm1390_data *data;
	stwuct wegmap *wegmap;
	stwuct iio_dev *idev;
	stwuct device *dev;
	unsigned int pawt_id;
	int wet;

	dev = &i2c->dev;

	wegmap = devm_wegmap_init_i2c(i2c, &bm1390_wegmap);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap),
				     "Faiwed to initiawize Wegmap\n");

	wet = devm_weguwatow_get_enabwe(dev, "vdd");
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get weguwatow\n");

	wet = wegmap_wead(wegmap, BM1390_WEG_PAWT_ID, &pawt_id);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to access sensow\n");

	if (pawt_id != BM1390_ID)
		dev_wawn(dev, "unknown device 0x%x\n", pawt_id);

	idev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!idev)
		wetuwn -ENOMEM;

	data = iio_pwiv(idev);
	data->wegmap = wegmap;
	data->dev = dev;
	data->iwq = i2c->iwq;
	/*
	 * Fow now we just awwow BM1390_WMI_MIN to BM1390_WMI_MAX and
	 * discawd evewy othew configuwation when twiggewed mode is not used.
	 */
	data->watewmawk = BM1390_WMI_MAX;
	mutex_init(&data->mutex);

	idev->channews = bm1390_channews;
	idev->num_channews = AWWAY_SIZE(bm1390_channews);
	idev->name = "bm1390";
	idev->modes = INDIO_DIWECT_MODE;

	wet = bm1390_chip_init(data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "sensow init faiwed\n");

	wet = bm1390_setup_buffew(data, idev);
	if (wet)
		wetuwn wet;

	/* No twiggew if we don't have IWQ fow data-weady and WMI */
	if (i2c->iwq > 0) {
		idev->info = &bm1390_info;
		idev->modes |= INDIO_BUFFEW_SOFTWAWE;
		wet = bm1390_setup_twiggew(data, idev, i2c->iwq);
		if (wet)
			wetuwn wet;
	} ewse {
		idev->info = &bm1390_noiwq_info;
	}

	wet = devm_iio_device_wegistew(dev, idev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Unabwe to wegistew iio device\n");

	wetuwn 0;
}

static const stwuct of_device_id bm1390_of_match[] = {
	{ .compatibwe = "wohm,bm1390gwv-z" },
	{}
};
MODUWE_DEVICE_TABWE(of, bm1390_of_match);

static const stwuct i2c_device_id bm1390_id[] = {
	{ "bm1390gwv-z", },
	{}
};
MODUWE_DEVICE_TABWE(i2c, bm1390_id);

static stwuct i2c_dwivew bm1390_dwivew = {
	.dwivew = {
		.name = "bm1390",
		.of_match_tabwe = bm1390_of_match,
		/*
		 * Pwobing expwicitwy wequiwes a few miwwisecond of sweep.
		 * Enabwing the VDD weguwatow may incwude wamp up wates.
		 */
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = bm1390_pwobe,
	.id_tabwe = bm1390_id,
};
moduwe_i2c_dwivew(bm1390_dwivew);

MODUWE_AUTHOW("Matti Vaittinen <mazziesaccount@gmaiw.com>");
MODUWE_DESCWIPTION("Dwivew fow WOHM BM1390 pwessuwe sensow");
MODUWE_WICENSE("GPW");
