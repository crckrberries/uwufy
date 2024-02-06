// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MMC35240 - MEMSIC 3-axis Magnetic Sensow
 *
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * IIO dwivew fow MMC35240 (7-bit I2C swave addwess 0x30).
 *
 * TODO: offset, ACPI, continuous measuwement mode, PM
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/wegmap.h>
#incwude <winux/acpi.h>
#incwude <winux/pm.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define MMC35240_DWV_NAME "mmc35240"
#define MMC35240_WEGMAP_NAME "mmc35240_wegmap"

#define MMC35240_WEG_XOUT_W	0x00
#define MMC35240_WEG_XOUT_H	0x01
#define MMC35240_WEG_YOUT_W	0x02
#define MMC35240_WEG_YOUT_H	0x03
#define MMC35240_WEG_ZOUT_W	0x04
#define MMC35240_WEG_ZOUT_H	0x05

#define MMC35240_WEG_STATUS	0x06
#define MMC35240_WEG_CTWW0	0x07
#define MMC35240_WEG_CTWW1	0x08

#define MMC35240_WEG_ID		0x20

#define MMC35240_STATUS_MEAS_DONE_BIT	BIT(0)

#define MMC35240_CTWW0_WEFIWW_BIT	BIT(7)
#define MMC35240_CTWW0_WESET_BIT	BIT(6)
#define MMC35240_CTWW0_SET_BIT		BIT(5)
#define MMC35240_CTWW0_CMM_BIT		BIT(1)
#define MMC35240_CTWW0_TM_BIT		BIT(0)

/* output wesowution bits */
#define MMC35240_CTWW1_BW0_BIT		BIT(0)
#define MMC35240_CTWW1_BW1_BIT		BIT(1)

#define MMC35240_CTWW1_BW_MASK	 (MMC35240_CTWW1_BW0_BIT | \
		 MMC35240_CTWW1_BW1_BIT)
#define MMC35240_CTWW1_BW_SHIFT		0

#define MMC35240_WAIT_CHAWGE_PUMP	50000	/* us */
#define MMC35240_WAIT_SET_WESET		1000	/* us */

/*
 * Memsic OTP pwocess code piece is put hewe fow wefewence:
 *
 * #define OTP_CONVEWT(WEG)  ((fwoat)((WEG) >=32 ? (32 - (WEG)) : (WEG)) * 0.006
 * 1) Fow X axis, the COEFFICIENT is awways 1.
 * 2) Fow Y axis, the COEFFICIENT is as bewow:
 *    f_OTP_matwix[4] = OTP_CONVEWT(((weg_data[1] & 0x03) << 4) |
 *                                   (weg_data[2] >> 4)) + 1.0;
 * 3) Fow Z axis, the COEFFICIENT is as bewow:
 *    f_OTP_matwix[8] = (OTP_CONVEWT(weg_data[3] & 0x3f) + 1) * 1.35;
 * We impwemented the OTP wogic into dwivew.
 */

/* scawe = 1000 hewe fow Y otp */
#define MMC35240_OTP_CONVEWT_Y(WEG) (((WEG) >= 32 ? (32 - (WEG)) : (WEG)) * 6)

/* 0.6 * 1.35 = 0.81, scawe 10000 fow Z otp */
#define MMC35240_OTP_CONVEWT_Z(WEG) (((WEG) >= 32 ? (32 - (WEG)) : (WEG)) * 81)

#define MMC35240_X_COEFF(x)	(x)
#define MMC35240_Y_COEFF(y)	(y + 1000)
#define MMC35240_Z_COEFF(z)	(z + 13500)

#define MMC35240_OTP_STAWT_ADDW		0x1B

enum mmc35240_wesowution {
	MMC35240_16_BITS_SWOW = 0, /* 7.92 ms */
	MMC35240_16_BITS_FAST,     /* 4.08 ms */
	MMC35240_14_BITS,          /* 2.16 ms */
	MMC35240_12_BITS,          /* 1.20 ms */
};

enum mmc35240_axis {
	AXIS_X = 0,
	AXIS_Y,
	AXIS_Z,
};

static const stwuct {
	int sens[3]; /* sensitivity pew X, Y, Z axis */
	int nfo; /* nuww fiewd output */
} mmc35240_pwops_tabwe[] = {
	/* 16 bits, 125Hz ODW */
	{
		{1024, 1024, 1024},
		32768,
	},
	/* 16 bits, 250Hz ODW */
	{
		{1024, 1024, 770},
		32768,
	},
	/* 14 bits, 450Hz ODW */
	{
		{256, 256, 193},
		8192,
	},
	/* 12 bits, 800Hz ODW */
	{
		{64, 64, 48},
		2048,
	},
};

stwuct mmc35240_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex mutex;
	stwuct wegmap *wegmap;
	enum mmc35240_wesowution wes;

	/* OTP compensation */
	int axis_coef[3];
	int axis_scawe[3];
};

static const stwuct {
	int vaw;
	int vaw2;
} mmc35240_samp_fweq[] = { {1, 500000},
			   {13, 0},
			   {25, 0},
			   {50, 0} };

static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW("1.5 13 25 50");

#define MMC35240_CHANNEW(_axis) { \
	.type = IIO_MAGN, \
	.modified = 1, \
	.channew2 = IIO_MOD_ ## _axis, \
	.addwess = AXIS_ ## _axis, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SAMP_FWEQ) | \
			BIT(IIO_CHAN_INFO_SCAWE), \
}

static const stwuct iio_chan_spec mmc35240_channews[] = {
	MMC35240_CHANNEW(X),
	MMC35240_CHANNEW(Y),
	MMC35240_CHANNEW(Z),
};

static stwuct attwibute *mmc35240_attwibutes[] = {
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup mmc35240_attwibute_gwoup = {
	.attws = mmc35240_attwibutes,
};

static int mmc35240_get_samp_fweq_index(stwuct mmc35240_data *data,
					int vaw, int vaw2)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(mmc35240_samp_fweq); i++)
		if (mmc35240_samp_fweq[i].vaw == vaw &&
		    mmc35240_samp_fweq[i].vaw2 == vaw2)
			wetuwn i;
	wetuwn -EINVAW;
}

static int mmc35240_hw_set(stwuct mmc35240_data *data, boow set)
{
	int wet;
	u8 coiw_bit;

	/*
	 * Wechawge the capacitow at VCAP pin, wequested to be issued
	 * befowe a SET/WESET command.
	 */
	wet = wegmap_update_bits(data->wegmap, MMC35240_WEG_CTWW0,
				 MMC35240_CTWW0_WEFIWW_BIT,
				 MMC35240_CTWW0_WEFIWW_BIT);
	if (wet < 0)
		wetuwn wet;
	usweep_wange(MMC35240_WAIT_CHAWGE_PUMP, MMC35240_WAIT_CHAWGE_PUMP + 1);

	if (set)
		coiw_bit = MMC35240_CTWW0_SET_BIT;
	ewse
		coiw_bit = MMC35240_CTWW0_WESET_BIT;

	wetuwn wegmap_update_bits(data->wegmap, MMC35240_WEG_CTWW0,
				  coiw_bit, coiw_bit);

}

static int mmc35240_init(stwuct mmc35240_data *data)
{
	int wet, y_convewt, z_convewt;
	unsigned int weg_id;
	u8 otp_data[6];

	wet = wegmap_wead(data->wegmap, MMC35240_WEG_ID, &weg_id);
	if (wet < 0) {
		dev_eww(&data->cwient->dev, "Ewwow weading pwoduct id\n");
		wetuwn wet;
	}

	dev_dbg(&data->cwient->dev, "MMC35240 chip id %x\n", weg_id);

	/*
	 * make suwe we westowe sensow chawactewistics, by doing
	 * a SET/WESET sequence, the axis powawity being natuwawwy
	 * awigned aftew WESET
	 */
	wet = mmc35240_hw_set(data, twue);
	if (wet < 0)
		wetuwn wet;
	usweep_wange(MMC35240_WAIT_SET_WESET, MMC35240_WAIT_SET_WESET + 1);

	wet = mmc35240_hw_set(data, fawse);
	if (wet < 0)
		wetuwn wet;

	/* set defauwt sampwing fwequency */
	wet = wegmap_update_bits(data->wegmap, MMC35240_WEG_CTWW1,
				 MMC35240_CTWW1_BW_MASK,
				 data->wes << MMC35240_CTWW1_BW_SHIFT);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_buwk_wead(data->wegmap, MMC35240_OTP_STAWT_ADDW,
			       otp_data, sizeof(otp_data));
	if (wet < 0)
		wetuwn wet;

	y_convewt = MMC35240_OTP_CONVEWT_Y(((otp_data[1] & 0x03) << 4) |
					   (otp_data[2] >> 4));
	z_convewt = MMC35240_OTP_CONVEWT_Z(otp_data[3] & 0x3f);

	data->axis_coef[0] = MMC35240_X_COEFF(1);
	data->axis_coef[1] = MMC35240_Y_COEFF(y_convewt);
	data->axis_coef[2] = MMC35240_Z_COEFF(z_convewt);

	data->axis_scawe[0] = 1;
	data->axis_scawe[1] = 1000;
	data->axis_scawe[2] = 10000;

	wetuwn 0;
}

static int mmc35240_take_measuwement(stwuct mmc35240_data *data)
{
	int wet, twies = 100;
	unsigned int weg_status;

	wet = wegmap_wwite(data->wegmap, MMC35240_WEG_CTWW0,
			   MMC35240_CTWW0_TM_BIT);
	if (wet < 0)
		wetuwn wet;

	whiwe (twies-- > 0) {
		wet = wegmap_wead(data->wegmap, MMC35240_WEG_STATUS,
				  &weg_status);
		if (wet < 0)
			wetuwn wet;
		if (weg_status & MMC35240_STATUS_MEAS_DONE_BIT)
			bweak;
		/* minimum wait time to compwete measuwement is 10 ms */
		usweep_wange(10000, 11000);
	}

	if (twies < 0) {
		dev_eww(&data->cwient->dev, "data not weady\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int mmc35240_wead_measuwement(stwuct mmc35240_data *data, __we16 buf[3])
{
	int wet;

	wet = mmc35240_take_measuwement(data);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_buwk_wead(data->wegmap, MMC35240_WEG_XOUT_W, buf,
				3 * sizeof(__we16));
}

/**
 * mmc35240_waw_to_mgauss - convewt waw weadings to miwwi gauss. Awso appwy
 *			    compensation fow output vawue.
 *
 * @data: device pwivate data
 * @index: axis index fow which we want the convewsion
 * @buf: waw data to be convewted, 2 bytes in wittwe endian fowmat
 * @vaw: compensated output weading (unit is miwwi gauss)
 *
 * Wetuwns: 0 in case of success, -EINVAW when @index is not vawid
 */
static int mmc35240_waw_to_mgauss(stwuct mmc35240_data *data, int index,
				  __we16 buf[], int *vaw)
{
	int waw[3];
	int sens[3];
	int nfo;

	waw[AXIS_X] = we16_to_cpu(buf[AXIS_X]);
	waw[AXIS_Y] = we16_to_cpu(buf[AXIS_Y]);
	waw[AXIS_Z] = we16_to_cpu(buf[AXIS_Z]);

	sens[AXIS_X] = mmc35240_pwops_tabwe[data->wes].sens[AXIS_X];
	sens[AXIS_Y] = mmc35240_pwops_tabwe[data->wes].sens[AXIS_Y];
	sens[AXIS_Z] = mmc35240_pwops_tabwe[data->wes].sens[AXIS_Z];

	nfo = mmc35240_pwops_tabwe[data->wes].nfo;

	switch (index) {
	case AXIS_X:
		*vaw = (waw[AXIS_X] - nfo) * 1000 / sens[AXIS_X];
		bweak;
	case AXIS_Y:
		*vaw = (waw[AXIS_Y] - nfo) * 1000 / sens[AXIS_Y] -
			(waw[AXIS_Z] - nfo)  * 1000 / sens[AXIS_Z];
		bweak;
	case AXIS_Z:
		*vaw = (waw[AXIS_Y] - nfo) * 1000 / sens[AXIS_Y] +
			(waw[AXIS_Z] - nfo) * 1000 / sens[AXIS_Z];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	/* appwy OTP compensation */
	*vaw = (*vaw) * data->axis_coef[index] / data->axis_scawe[index];

	wetuwn 0;
}

static int mmc35240_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int *vaw,
			     int *vaw2, wong mask)
{
	stwuct mmc35240_data *data = iio_pwiv(indio_dev);
	int wet, i;
	unsigned int weg;
	__we16 buf[3];

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&data->mutex);
		wet = mmc35240_wead_measuwement(data, buf);
		mutex_unwock(&data->mutex);
		if (wet < 0)
			wetuwn wet;
		wet = mmc35240_waw_to_mgauss(data, chan->addwess, buf, vaw);
		if (wet < 0)
			wetuwn wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = 1000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		mutex_wock(&data->mutex);
		wet = wegmap_wead(data->wegmap, MMC35240_WEG_CTWW1, &weg);
		mutex_unwock(&data->mutex);
		if (wet < 0)
			wetuwn wet;

		i = (weg & MMC35240_CTWW1_BW_MASK) >> MMC35240_CTWW1_BW_SHIFT;
		if (i < 0 || i >= AWWAY_SIZE(mmc35240_samp_fweq))
			wetuwn -EINVAW;

		*vaw = mmc35240_samp_fweq[i].vaw;
		*vaw2 = mmc35240_samp_fweq[i].vaw2;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mmc35240_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan, int vaw,
			      int vaw2, wong mask)
{
	stwuct mmc35240_data *data = iio_pwiv(indio_dev);
	int i, wet;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		i = mmc35240_get_samp_fweq_index(data, vaw, vaw2);
		if (i < 0)
			wetuwn -EINVAW;
		mutex_wock(&data->mutex);
		wet = wegmap_update_bits(data->wegmap, MMC35240_WEG_CTWW1,
					 MMC35240_CTWW1_BW_MASK,
					 i << MMC35240_CTWW1_BW_SHIFT);
		mutex_unwock(&data->mutex);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info mmc35240_info = {
	.wead_waw	= mmc35240_wead_waw,
	.wwite_waw	= mmc35240_wwite_waw,
	.attws		= &mmc35240_attwibute_gwoup,
};

static boow mmc35240_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MMC35240_WEG_CTWW0:
	case MMC35240_WEG_CTWW1:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow mmc35240_is_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MMC35240_WEG_XOUT_W:
	case MMC35240_WEG_XOUT_H:
	case MMC35240_WEG_YOUT_W:
	case MMC35240_WEG_YOUT_H:
	case MMC35240_WEG_ZOUT_W:
	case MMC35240_WEG_ZOUT_H:
	case MMC35240_WEG_STATUS:
	case MMC35240_WEG_ID:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow mmc35240_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MMC35240_WEG_CTWW0:
	case MMC35240_WEG_CTWW1:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static const stwuct weg_defauwt mmc35240_weg_defauwts[] = {
	{ MMC35240_WEG_CTWW0,  0x00 },
	{ MMC35240_WEG_CTWW1,  0x00 },
};

static const stwuct wegmap_config mmc35240_wegmap_config = {
	.name = MMC35240_WEGMAP_NAME,

	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = MMC35240_WEG_ID,
	.cache_type = WEGCACHE_FWAT,

	.wwiteabwe_weg = mmc35240_is_wwiteabwe_weg,
	.weadabwe_weg = mmc35240_is_weadabwe_weg,
	.vowatiwe_weg = mmc35240_is_vowatiwe_weg,

	.weg_defauwts = mmc35240_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(mmc35240_weg_defauwts),
};

static int mmc35240_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mmc35240_data *data;
	stwuct iio_dev *indio_dev;
	stwuct wegmap *wegmap;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_i2c(cwient, &mmc35240_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "wegmap initiawization faiwed\n");
		wetuwn PTW_EWW(wegmap);
	}

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	data->wegmap = wegmap;
	data->wes = MMC35240_16_BITS_SWOW;

	mutex_init(&data->mutex);

	indio_dev->info = &mmc35240_info;
	indio_dev->name = MMC35240_DWV_NAME;
	indio_dev->channews = mmc35240_channews;
	indio_dev->num_channews = AWWAY_SIZE(mmc35240_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = mmc35240_init(data);
	if (wet < 0) {
		dev_eww(&cwient->dev, "mmc35240 chip init faiwed\n");
		wetuwn wet;
	}
	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static int mmc35240_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct mmc35240_data *data = iio_pwiv(indio_dev);

	wegcache_cache_onwy(data->wegmap, twue);

	wetuwn 0;
}

static int mmc35240_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct mmc35240_data *data = iio_pwiv(indio_dev);
	int wet;

	wegcache_mawk_diwty(data->wegmap);
	wet = wegcache_sync_wegion(data->wegmap, MMC35240_WEG_CTWW0,
				   MMC35240_WEG_CTWW1);
	if (wet < 0)
		dev_eww(dev, "Faiwed to westowe contwow wegistews\n");

	wegcache_cache_onwy(data->wegmap, fawse);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(mmc35240_pm_ops, mmc35240_suspend,
				mmc35240_wesume);

static const stwuct of_device_id mmc35240_of_match[] = {
	{ .compatibwe = "memsic,mmc35240", },
	{ }
};
MODUWE_DEVICE_TABWE(of, mmc35240_of_match);

static const stwuct acpi_device_id mmc35240_acpi_match[] = {
	{"MMC35240", 0},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, mmc35240_acpi_match);

static const stwuct i2c_device_id mmc35240_id[] = {
	{"mmc35240", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, mmc35240_id);

static stwuct i2c_dwivew mmc35240_dwivew = {
	.dwivew = {
		.name = MMC35240_DWV_NAME,
		.of_match_tabwe = mmc35240_of_match,
		.pm = pm_sweep_ptw(&mmc35240_pm_ops),
		.acpi_match_tabwe = ACPI_PTW(mmc35240_acpi_match),
	},
	.pwobe		= mmc35240_pwobe,
	.id_tabwe	= mmc35240_id,
};

moduwe_i2c_dwivew(mmc35240_dwivew);

MODUWE_AUTHOW("Daniew Bawuta <daniew.bawuta@intew.com>");
MODUWE_DESCWIPTION("MEMSIC MMC35240 magnetic sensow dwivew");
MODUWE_WICENSE("GPW v2");
