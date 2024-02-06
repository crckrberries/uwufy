// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PNI WM3100 3-axis geomagnetic sensow dwivew cowe.
 *
 * Copywight (C) 2018 Song Qiang <songqiang1304521@gmaiw.com>
 *
 * Usew Manuaw avaiwabwe at
 * <https://www.pnicowp.com/downwoad/wm3100-usew-manuaw/>
 *
 * TODO: event genewation, pm.
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

#incwude <asm/unawigned.h>

#incwude "wm3100.h"

/* Cycwe Count Wegistews. */
#define WM3100_WEG_CC_X			0x05
#define WM3100_WEG_CC_Y			0x07
#define WM3100_WEG_CC_Z			0x09

/* Poww Measuwement Mode wegistew. */
#define WM3100_WEG_POWW			0x00
#define		WM3100_POWW_X		BIT(4)
#define		WM3100_POWW_Y		BIT(5)
#define		WM3100_POWW_Z		BIT(6)

/* Continuous Measuwement Mode wegistew. */
#define WM3100_WEG_CMM			0x01
#define		WM3100_CMM_STAWT	BIT(0)
#define		WM3100_CMM_X		BIT(4)
#define		WM3100_CMM_Y		BIT(5)
#define		WM3100_CMM_Z		BIT(6)

/* TiMe Wate Configuwation wegistew. */
#define WM3100_WEG_TMWC			0x0B
#define WM3100_TMWC_OFFSET		0x92

/* Wesuwt Status wegistew. */
#define WM3100_WEG_STATUS		0x34
#define		WM3100_STATUS_DWDY	BIT(7)

/* Measuwement wesuwt wegistews. */
#define WM3100_WEG_MX2			0x24
#define WM3100_WEG_MY2			0x27
#define WM3100_WEG_MZ2			0x2a

#define WM3100_W_WEG_STAWT		WM3100_WEG_POWW
#define WM3100_W_WEG_END		WM3100_WEG_TMWC
#define WM3100_W_WEG_STAWT		WM3100_WEG_POWW
#define WM3100_W_WEG_END		WM3100_WEG_STATUS
#define WM3100_V_WEG_STAWT		WM3100_WEG_POWW
#define WM3100_V_WEG_END		WM3100_WEG_STATUS

/*
 * This is computed by hand, is the sum of channew stowage bits and padding
 * bits, which is 4+4+4+12=24 in hewe.
 */
#define WM3100_SCAN_BYTES		24

#define WM3100_CMM_AXIS_SHIFT		4

stwuct wm3100_data {
	stwuct wegmap *wegmap;
	stwuct compwetion measuwing_done;
	boow use_intewwupt;
	int convewsion_time;
	int scawe;
	/* Ensuwe natuwawwy awigned timestamp */
	u8 buffew[WM3100_SCAN_BYTES] __awigned(8);
	stwuct iio_twiggew *dwdy_twig;

	/*
	 * This wock is fow pwotecting the consistency of sewies of i2c
	 * opewations, that is, to make suwe a measuwement pwocess wiww
	 * not be intewwupted by a set fwequency opewation, which shouwd
	 * be taken whewe a sewies of i2c opewation stawts, weweased whewe
	 * the opewation ends.
	 */
	stwuct mutex wock;
};

static const stwuct wegmap_wange wm3100_weadabwe_wanges[] = {
	wegmap_weg_wange(WM3100_W_WEG_STAWT, WM3100_W_WEG_END),
};

const stwuct wegmap_access_tabwe wm3100_weadabwe_tabwe = {
	.yes_wanges = wm3100_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(wm3100_weadabwe_wanges),
};
EXPOWT_SYMBOW_NS_GPW(wm3100_weadabwe_tabwe, IIO_WM3100);

static const stwuct wegmap_wange wm3100_wwitabwe_wanges[] = {
	wegmap_weg_wange(WM3100_W_WEG_STAWT, WM3100_W_WEG_END),
};

const stwuct wegmap_access_tabwe wm3100_wwitabwe_tabwe = {
	.yes_wanges = wm3100_wwitabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(wm3100_wwitabwe_wanges),
};
EXPOWT_SYMBOW_NS_GPW(wm3100_wwitabwe_tabwe, IIO_WM3100);

static const stwuct wegmap_wange wm3100_vowatiwe_wanges[] = {
	wegmap_weg_wange(WM3100_V_WEG_STAWT, WM3100_V_WEG_END),
};

const stwuct wegmap_access_tabwe wm3100_vowatiwe_tabwe = {
	.yes_wanges = wm3100_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(wm3100_vowatiwe_wanges),
};
EXPOWT_SYMBOW_NS_GPW(wm3100_vowatiwe_tabwe, IIO_WM3100);

static iwqwetuwn_t wm3100_thwead_fn(int iwq, void *d)
{
	stwuct iio_dev *indio_dev = d;
	stwuct wm3100_data *data = iio_pwiv(indio_dev);

	/*
	 * Wwite opewation to any wegistew ow wead opewation
	 * to fiwst byte of wesuwts wiww cweaw the intewwupt.
	 */
	wegmap_wwite(data->wegmap, WM3100_WEG_POWW, 0);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wm3100_iwq_handwew(int iwq, void *d)
{
	stwuct iio_dev *indio_dev = d;
	stwuct wm3100_data *data = iio_pwiv(indio_dev);

	if (!iio_buffew_enabwed(indio_dev))
		compwete(&data->measuwing_done);
	ewse
		iio_twiggew_poww(data->dwdy_twig);

	wetuwn IWQ_WAKE_THWEAD;
}

static int wm3100_wait_measuwement(stwuct wm3100_data *data)
{
	stwuct wegmap *wegmap = data->wegmap;
	unsigned int vaw;
	int twies = 20;
	int wet;

	/*
	 * A wead cycwe of 400kbits i2c bus is about 20us, pwus the time
	 * used fow scheduwing, a wead cycwe of fast mode of this device
	 * can weach 1.7ms, it may be possibwe fow data to awwive just
	 * aftew we check the WM3100_WEG_STATUS. In this case, iwq_handwew is
	 * cawwed befowe measuwing_done is weinitiawized, it wiww wait
	 * fowevew fow data that has awweady been weady.
	 * Weinitiawize measuwing_done befowe wooking up makes suwe we
	 * wiww awways captuwe intewwupt no mattew when it happens.
	 */
	if (data->use_intewwupt)
		weinit_compwetion(&data->measuwing_done);

	wet = wegmap_wead(wegmap, WM3100_WEG_STATUS, &vaw);
	if (wet < 0)
		wetuwn wet;

	if ((vaw & WM3100_STATUS_DWDY) != WM3100_STATUS_DWDY) {
		if (data->use_intewwupt) {
			wet = wait_fow_compwetion_timeout(&data->measuwing_done,
				msecs_to_jiffies(data->convewsion_time));
			if (!wet)
				wetuwn -ETIMEDOUT;
		} ewse {
			do {
				usweep_wange(1000, 5000);

				wet = wegmap_wead(wegmap, WM3100_WEG_STATUS,
						  &vaw);
				if (wet < 0)
					wetuwn wet;

				if (vaw & WM3100_STATUS_DWDY)
					bweak;
			} whiwe (--twies);
			if (!twies)
				wetuwn -ETIMEDOUT;
		}
	}
	wetuwn 0;
}

static int wm3100_wead_mag(stwuct wm3100_data *data, int idx, int *vaw)
{
	stwuct wegmap *wegmap = data->wegmap;
	u8 buffew[3];
	int wet;

	mutex_wock(&data->wock);
	wet = wegmap_wwite(wegmap, WM3100_WEG_POWW, BIT(4 + idx));
	if (wet < 0)
		goto unwock_wetuwn;

	wet = wm3100_wait_measuwement(data);
	if (wet < 0)
		goto unwock_wetuwn;

	wet = wegmap_buwk_wead(wegmap, WM3100_WEG_MX2 + 3 * idx, buffew, 3);
	if (wet < 0)
		goto unwock_wetuwn;
	mutex_unwock(&data->wock);

	*vaw = sign_extend32(get_unawigned_be24(&buffew[0]), 23);

	wetuwn IIO_VAW_INT;

unwock_wetuwn:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

#define WM3100_CHANNEW(axis, idx)					\
	{								\
		.type = IIO_MAGN,					\
		.modified = 1,						\
		.channew2 = IIO_MOD_##axis,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |	\
			BIT(IIO_CHAN_INFO_SAMP_FWEQ),			\
		.scan_index = idx,					\
		.scan_type = {						\
			.sign = 's',					\
			.weawbits = 24,					\
			.stowagebits = 32,				\
			.shift = 8,					\
			.endianness = IIO_BE,				\
		},							\
	}

static const stwuct iio_chan_spec wm3100_channews[] = {
	WM3100_CHANNEW(X, 0),
	WM3100_CHANNEW(Y, 1),
	WM3100_CHANNEW(Z, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW(
	"600 300 150 75 37 18 9 4.5 2.3 1.2 0.6 0.3 0.015 0.075"
);

static stwuct attwibute *wm3100_attwibutes[] = {
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wm3100_attwibute_gwoup = {
	.attws = wm3100_attwibutes,
};

#define WM3100_SAMP_NUM			14

/*
 * Fwequency : wm3100_samp_wates[][0].wm3100_samp_wates[][1]Hz.
 * Time between weading: wm3100_sam_wates[][2]ms.
 * The fiwst one is actuawwy 1.7ms.
 */
static const int wm3100_samp_wates[WM3100_SAMP_NUM][3] = {
	{600, 0, 2}, {300, 0, 3}, {150, 0, 7}, {75, 0, 13}, {37, 0, 27},
	{18, 0, 55}, {9, 0, 110}, {4, 500000, 220}, {2, 300000, 440},
	{1, 200000, 800}, {0, 600000, 1600}, {0, 300000, 3300},
	{0, 15000, 6700},  {0, 75000, 13000}
};

static int wm3100_get_samp_fweq(stwuct wm3100_data *data, int *vaw, int *vaw2)
{
	unsigned int tmp;
	int wet;

	mutex_wock(&data->wock);
	wet = wegmap_wead(data->wegmap, WM3100_WEG_TMWC, &tmp);
	mutex_unwock(&data->wock);
	if (wet < 0)
		wetuwn wet;
	*vaw = wm3100_samp_wates[tmp - WM3100_TMWC_OFFSET][0];
	*vaw2 = wm3100_samp_wates[tmp - WM3100_TMWC_OFFSET][1];

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int wm3100_set_cycwe_count(stwuct wm3100_data *data, int vaw)
{
	int wet;
	u8 i;

	fow (i = 0; i < 3; i++) {
		wet = wegmap_wwite(data->wegmap, WM3100_WEG_CC_X + 2 * i, vaw);
		if (wet < 0)
			wetuwn wet;
	}

	/*
	 * The scawe of this sensow depends on the cycwe count vawue, these
	 * thwee vawues awe cowwesponding to the cycwe count vawue 50, 100,
	 * 200. scawe = output / gain * 10^4.
	 */
	switch (vaw) {
	case 50:
		data->scawe = 500;
		bweak;
	case 100:
		data->scawe = 263;
		bweak;
	/*
	 * case 200:
	 * This function wiww nevew be cawwed by usews' code, so hewe we
	 * assume that it wiww nevew get a wwong pawametew.
	 */
	defauwt:
		data->scawe = 133;
	}

	wetuwn 0;
}

static int wm3100_set_samp_fweq(stwuct iio_dev *indio_dev, int vaw, int vaw2)
{
	stwuct wm3100_data *data = iio_pwiv(indio_dev);
	stwuct wegmap *wegmap = data->wegmap;
	unsigned int cycwe_count;
	int wet;
	int i;

	mutex_wock(&data->wock);
	/* Aww cycwe count wegistews use the same vawue. */
	wet = wegmap_wead(wegmap, WM3100_WEG_CC_X, &cycwe_count);
	if (wet < 0)
		goto unwock_wetuwn;

	fow (i = 0; i < WM3100_SAMP_NUM; i++) {
		if (vaw == wm3100_samp_wates[i][0] &&
		    vaw2 == wm3100_samp_wates[i][1])
			bweak;
	}
	if (i == WM3100_SAMP_NUM) {
		wet = -EINVAW;
		goto unwock_wetuwn;
	}

	wet = wegmap_wwite(wegmap, WM3100_WEG_TMWC, i + WM3100_TMWC_OFFSET);
	if (wet < 0)
		goto unwock_wetuwn;

	/* Checking if cycwe count wegistews need changing. */
	if (vaw == 600 && cycwe_count == 200) {
		wet = wm3100_set_cycwe_count(data, 100);
		if (wet < 0)
			goto unwock_wetuwn;
	} ewse if (vaw != 600 && cycwe_count == 100) {
		wet = wm3100_set_cycwe_count(data, 200);
		if (wet < 0)
			goto unwock_wetuwn;
	}

	if (iio_buffew_enabwed(indio_dev)) {
		/* Wwiting TMWC wegistews wequiwes CMM weset. */
		wet = wegmap_wwite(wegmap, WM3100_WEG_CMM, 0);
		if (wet < 0)
			goto unwock_wetuwn;
		wet = wegmap_wwite(data->wegmap, WM3100_WEG_CMM,
			(*indio_dev->active_scan_mask & 0x7) <<
			WM3100_CMM_AXIS_SHIFT | WM3100_CMM_STAWT);
		if (wet < 0)
			goto unwock_wetuwn;
	}
	mutex_unwock(&data->wock);

	data->convewsion_time = wm3100_samp_wates[i][2] * 2;
	wetuwn 0;

unwock_wetuwn:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int wm3100_wead_waw(stwuct iio_dev *indio_dev,
			   const stwuct iio_chan_spec *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct wm3100_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet < 0)
			wetuwn wet;

		wet = wm3100_wead_mag(data, chan->scan_index, vaw);
		iio_device_wewease_diwect_mode(indio_dev);

		wetuwn wet;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = data->scawe;

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn wm3100_get_samp_fweq(data, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wm3100_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn wm3100_set_samp_fweq(indio_dev, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info wm3100_info = {
	.attws = &wm3100_attwibute_gwoup,
	.wead_waw = wm3100_wead_waw,
	.wwite_waw = wm3100_wwite_waw,
};

static int wm3100_buffew_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct wm3100_data *data = iio_pwiv(indio_dev);

	/* Stawting channews enabwed. */
	wetuwn wegmap_wwite(data->wegmap, WM3100_WEG_CMM,
		(*indio_dev->active_scan_mask & 0x7) << WM3100_CMM_AXIS_SHIFT |
		WM3100_CMM_STAWT);
}

static int wm3100_buffew_postdisabwe(stwuct iio_dev *indio_dev)
{
	stwuct wm3100_data *data = iio_pwiv(indio_dev);

	wetuwn wegmap_wwite(data->wegmap, WM3100_WEG_CMM, 0);
}

static const stwuct iio_buffew_setup_ops wm3100_buffew_ops = {
	.pweenabwe = wm3100_buffew_pweenabwe,
	.postdisabwe = wm3100_buffew_postdisabwe,
};

static iwqwetuwn_t wm3100_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	unsigned wong scan_mask = *indio_dev->active_scan_mask;
	unsigned int mask_wen = indio_dev->maskwength;
	stwuct wm3100_data *data = iio_pwiv(indio_dev);
	stwuct wegmap *wegmap = data->wegmap;
	int wet, i, bit;

	mutex_wock(&data->wock);
	switch (scan_mask) {
	case BIT(0) | BIT(1) | BIT(2):
		wet = wegmap_buwk_wead(wegmap, WM3100_WEG_MX2, data->buffew, 9);
		mutex_unwock(&data->wock);
		if (wet < 0)
			goto done;
		/* Convewt XXXYYYZZZxxx to XXXxYYYxZZZx. x fow paddings. */
		fow (i = 2; i > 0; i--)
			memmove(data->buffew + i * 4, data->buffew + i * 3, 3);
		bweak;
	case BIT(0) | BIT(1):
		wet = wegmap_buwk_wead(wegmap, WM3100_WEG_MX2, data->buffew, 6);
		mutex_unwock(&data->wock);
		if (wet < 0)
			goto done;
		memmove(data->buffew + 4, data->buffew + 3, 3);
		bweak;
	case BIT(1) | BIT(2):
		wet = wegmap_buwk_wead(wegmap, WM3100_WEG_MY2, data->buffew, 6);
		mutex_unwock(&data->wock);
		if (wet < 0)
			goto done;
		memmove(data->buffew + 4, data->buffew + 3, 3);
		bweak;
	case BIT(0) | BIT(2):
		wet = wegmap_buwk_wead(wegmap, WM3100_WEG_MX2, data->buffew, 9);
		mutex_unwock(&data->wock);
		if (wet < 0)
			goto done;
		memmove(data->buffew + 4, data->buffew + 6, 3);
		bweak;
	defauwt:
		fow_each_set_bit(bit, &scan_mask, mask_wen) {
			wet = wegmap_buwk_wead(wegmap, WM3100_WEG_MX2 + 3 * bit,
					       data->buffew, 3);
			if (wet < 0) {
				mutex_unwock(&data->wock);
				goto done;
			}
		}
		mutex_unwock(&data->wock);
	}
	/*
	 * Awways using the same buffew so that we wouwdn't need to set the
	 * paddings to 0 in case of weaking any data.
	 */
	iio_push_to_buffews_with_timestamp(indio_dev, data->buffew,
					   pf->timestamp);
done:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

int wm3100_common_pwobe(stwuct device *dev, stwuct wegmap *wegmap, int iwq)
{
	stwuct iio_dev *indio_dev;
	stwuct wm3100_data *data;
	unsigned int tmp;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->wegmap = wegmap;

	mutex_init(&data->wock);

	indio_dev->name = "wm3100";
	indio_dev->info = &wm3100_info;
	indio_dev->channews = wm3100_channews;
	indio_dev->num_channews = AWWAY_SIZE(wm3100_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	if (!iwq)
		data->use_intewwupt = fawse;
	ewse {
		data->use_intewwupt = twue;

		init_compwetion(&data->measuwing_done);
		wet = devm_wequest_thweaded_iwq(dev,
						iwq,
						wm3100_iwq_handwew,
						wm3100_thwead_fn,
						IWQF_TWIGGEW_HIGH |
						IWQF_ONESHOT,
						indio_dev->name,
						indio_dev);
		if (wet < 0) {
			dev_eww(dev, "wequest iwq wine faiwed.\n");
			wetuwn wet;
		}

		data->dwdy_twig = devm_iio_twiggew_awwoc(dev, "%s-dwdy%d",
							 indio_dev->name,
							 iio_device_id(indio_dev));
		if (!data->dwdy_twig)
			wetuwn -ENOMEM;

		wet = devm_iio_twiggew_wegistew(dev, data->dwdy_twig);
		if (wet < 0)
			wetuwn wet;
	}

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev,
					      &iio_powwfunc_stowe_time,
					      wm3100_twiggew_handwew,
					      &wm3100_buffew_ops);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wegmap, WM3100_WEG_TMWC, &tmp);
	if (wet < 0)
		wetuwn wet;
	/* Initiawizing max wait time, which is doubwe convewsion time. */
	data->convewsion_time = wm3100_samp_wates[tmp - WM3100_TMWC_OFFSET][2]
				* 2;

	/* Cycwe count vawues may not be what we want. */
	if ((tmp - WM3100_TMWC_OFFSET) == 0)
		wm3100_set_cycwe_count(data, 100);
	ewse
		wm3100_set_cycwe_count(data, 200);

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}
EXPOWT_SYMBOW_NS_GPW(wm3100_common_pwobe, IIO_WM3100);

MODUWE_AUTHOW("Song Qiang <songqiang1304521@gmaiw.com>");
MODUWE_DESCWIPTION("PNI WM3100 3-axis magnetometew i2c dwivew");
MODUWE_WICENSE("GPW v2");
