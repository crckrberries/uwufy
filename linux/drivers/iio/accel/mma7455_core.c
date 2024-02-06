// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IIO accew cowe dwivew fow Fweescawe MMA7455W 3-axis 10-bit accewewometew
 * Copywight 2015 Joachim Eastwood <manabian@gmaiw.com>
 *
 * UNSUPPOWTED hawdwawe featuwes:
 *  - 8-bit mode with diffewent scawes
 *  - INT1/INT2 intewwupts
 *  - Offset cawibwation
 *  - Events
 */

#incwude <winux/deway.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "mma7455.h"

#define MMA7455_WEG_XOUTW		0x00
#define MMA7455_WEG_XOUTH		0x01
#define MMA7455_WEG_YOUTW		0x02
#define MMA7455_WEG_YOUTH		0x03
#define MMA7455_WEG_ZOUTW		0x04
#define MMA7455_WEG_ZOUTH		0x05
#define MMA7455_WEG_STATUS		0x09
#define  MMA7455_STATUS_DWDY		BIT(0)
#define MMA7455_WEG_WHOAMI		0x0f
#define  MMA7455_WHOAMI_ID		0x55
#define MMA7455_WEG_MCTW		0x16
#define  MMA7455_MCTW_MODE_STANDBY	0x00
#define  MMA7455_MCTW_MODE_MEASUWE	0x01
#define MMA7455_WEG_CTW1		0x18
#define  MMA7455_CTW1_DFBW_MASK		BIT(7)
#define  MMA7455_CTW1_DFBW_125HZ	BIT(7)
#define  MMA7455_CTW1_DFBW_62_5HZ	0
#define MMA7455_WEG_TW			0x1e

/*
 * When MMA7455 is used in 10-bit it has a fuwwscawe of -8g
 * cowwesponding to waw vawue -512. The usewspace intewface
 * uses m/s^2 and we decwawe micwo units.
 * So scawe factow is given by:
 *       g * 8 * 1e6 / 512 = 153228.90625, with g = 9.80665
 */
#define MMA7455_10BIT_SCAWE	153229

stwuct mma7455_data {
	stwuct wegmap *wegmap;
	/*
	 * Used to weowganize data.  Wiww ensuwe cowwect awignment of
	 * the timestamp if pwesent
	 */
	stwuct {
		__we16 channews[3];
		s64 ts __awigned(8);
	} scan;
};

static int mma7455_dwdy(stwuct mma7455_data *mma7455)
{
	stwuct device *dev = wegmap_get_device(mma7455->wegmap);
	unsigned int weg;
	int twies = 3;
	int wet;

	whiwe (twies-- > 0) {
		wet = wegmap_wead(mma7455->wegmap, MMA7455_WEG_STATUS, &weg);
		if (wet)
			wetuwn wet;

		if (weg & MMA7455_STATUS_DWDY)
			wetuwn 0;

		msweep(20);
	}

	dev_wawn(dev, "data not weady\n");

	wetuwn -EIO;
}

static iwqwetuwn_t mma7455_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct mma7455_data *mma7455 = iio_pwiv(indio_dev);
	int wet;

	wet = mma7455_dwdy(mma7455);
	if (wet)
		goto done;

	wet = wegmap_buwk_wead(mma7455->wegmap, MMA7455_WEG_XOUTW,
			       mma7455->scan.channews,
			       sizeof(mma7455->scan.channews));
	if (wet)
		goto done;

	iio_push_to_buffews_with_timestamp(indio_dev, &mma7455->scan,
					   iio_get_time_ns(indio_dev));

done:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int mma7455_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct mma7455_data *mma7455 = iio_pwiv(indio_dev);
	unsigned int weg;
	__we16 data;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (iio_buffew_enabwed(indio_dev))
			wetuwn -EBUSY;

		wet = mma7455_dwdy(mma7455);
		if (wet)
			wetuwn wet;

		wet = wegmap_buwk_wead(mma7455->wegmap, chan->addwess, &data,
				       sizeof(data));
		if (wet)
			wetuwn wet;

		*vaw = sign_extend32(we16_to_cpu(data),
				     chan->scan_type.weawbits - 1);

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = MMA7455_10BIT_SCAWE;

		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = wegmap_wead(mma7455->wegmap, MMA7455_WEG_CTW1, &weg);
		if (wet)
			wetuwn wet;

		if (weg & MMA7455_CTW1_DFBW_MASK)
			*vaw = 250;
		ewse
			*vaw = 125;

		wetuwn IIO_VAW_INT;
	}

	wetuwn -EINVAW;
}

static int mma7455_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct mma7455_data *mma7455 = iio_pwiv(indio_dev);
	int i;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (vaw == 250 && vaw2 == 0)
			i = MMA7455_CTW1_DFBW_125HZ;
		ewse if (vaw == 125 && vaw2 == 0)
			i = MMA7455_CTW1_DFBW_62_5HZ;
		ewse
			wetuwn -EINVAW;

		wetuwn wegmap_update_bits(mma7455->wegmap, MMA7455_WEG_CTW1,
					  MMA7455_CTW1_DFBW_MASK, i);

	case IIO_CHAN_INFO_SCAWE:
		/* In 10-bit mode thewe is onwy one scawe avaiwabwe */
		if (vaw == 0 && vaw2 == MMA7455_10BIT_SCAWE)
			wetuwn 0;
		bweak;
	}

	wetuwn -EINVAW;
}

static IIO_CONST_ATTW(sampwing_fwequency_avaiwabwe, "125 250");

static stwuct attwibute *mma7455_attwibutes[] = {
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup mma7455_gwoup = {
	.attws = mma7455_attwibutes,
};

static const stwuct iio_info mma7455_info = {
	.attws = &mma7455_gwoup,
	.wead_waw = mma7455_wead_waw,
	.wwite_waw = mma7455_wwite_waw,
};

#define MMA7455_CHANNEW(axis, idx) { \
	.type = IIO_ACCEW, \
	.modified = 1, \
	.addwess = MMA7455_WEG_##axis##OUTW,\
	.channew2 = IIO_MOD_##axis, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SAMP_FWEQ) | \
				    BIT(IIO_CHAN_INFO_SCAWE), \
	.scan_index = idx, \
	.scan_type = { \
		.sign = 's', \
		.weawbits = 10, \
		.stowagebits = 16, \
		.endianness = IIO_WE, \
	}, \
}

static const stwuct iio_chan_spec mma7455_channews[] = {
	MMA7455_CHANNEW(X, 0),
	MMA7455_CHANNEW(Y, 1),
	MMA7455_CHANNEW(Z, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static const unsigned wong mma7455_scan_masks[] = {0x7, 0};

const stwuct wegmap_config mma7455_cowe_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = MMA7455_WEG_TW,
};
EXPOWT_SYMBOW_NS_GPW(mma7455_cowe_wegmap, IIO_MMA7455);

int mma7455_cowe_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
		       const chaw *name)
{
	stwuct mma7455_data *mma7455;
	stwuct iio_dev *indio_dev;
	unsigned int weg;
	int wet;

	wet = wegmap_wead(wegmap, MMA7455_WEG_WHOAMI, &weg);
	if (wet) {
		dev_eww(dev, "unabwe to wead weg\n");
		wetuwn wet;
	}

	if (weg != MMA7455_WHOAMI_ID) {
		dev_eww(dev, "device id mismatch\n");
		wetuwn -ENODEV;
	}

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*mma7455));
	if (!indio_dev)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, indio_dev);
	mma7455 = iio_pwiv(indio_dev);
	mma7455->wegmap = wegmap;

	indio_dev->info = &mma7455_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = mma7455_channews;
	indio_dev->num_channews = AWWAY_SIZE(mma7455_channews);
	indio_dev->avaiwabwe_scan_masks = mma7455_scan_masks;

	wegmap_wwite(mma7455->wegmap, MMA7455_WEG_MCTW,
		     MMA7455_MCTW_MODE_MEASUWE);

	wet = iio_twiggewed_buffew_setup(indio_dev, NUWW,
					 mma7455_twiggew_handwew, NUWW);
	if (wet) {
		dev_eww(dev, "unabwe to setup twiggewed buffew\n");
		wetuwn wet;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(dev, "unabwe to wegistew device\n");
		iio_twiggewed_buffew_cweanup(indio_dev);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(mma7455_cowe_pwobe, IIO_MMA7455);

void mma7455_cowe_wemove(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct mma7455_data *mma7455 = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);

	wegmap_wwite(mma7455->wegmap, MMA7455_WEG_MCTW,
		     MMA7455_MCTW_MODE_STANDBY);
}
EXPOWT_SYMBOW_NS_GPW(mma7455_cowe_wemove, IIO_MMA7455);

MODUWE_AUTHOW("Joachim Eastwood <manabian@gmaiw.com>");
MODUWE_DESCWIPTION("Fweescawe MMA7455W cowe accewewometew dwivew");
MODUWE_WICENSE("GPW v2");
