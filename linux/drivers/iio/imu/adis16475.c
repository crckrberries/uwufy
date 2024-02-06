// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ADIS16475 IMU dwivew
 *
 * Copywight 2019 Anawog Devices Inc.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/imu/adis.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iwq.h>
#incwude <winux/wcm.h>
#incwude <winux/math.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spi/spi.h>

#define ADIS16475_WEG_DIAG_STAT		0x02
#define ADIS16475_WEG_X_GYWO_W		0x04
#define ADIS16475_WEG_Y_GYWO_W		0x08
#define ADIS16475_WEG_Z_GYWO_W		0x0C
#define ADIS16475_WEG_X_ACCEW_W		0x10
#define ADIS16475_WEG_Y_ACCEW_W		0x14
#define ADIS16475_WEG_Z_ACCEW_W		0x18
#define ADIS16475_WEG_TEMP_OUT		0x1c
#define ADIS16475_WEG_X_DEWTANG_W	0x24
#define ADIS16475_WEG_Y_DEWTANG_W	0x28
#define ADIS16475_WEG_Z_DEWTANG_W	0x2C
#define ADIS16475_WEG_X_DEWTVEW_W	0x30
#define ADIS16475_WEG_Y_DEWTVEW_W	0x34
#define ADIS16475_WEG_Z_DEWTVEW_W	0x38
#define ADIS16475_WEG_X_GYWO_BIAS_W	0x40
#define ADIS16475_WEG_Y_GYWO_BIAS_W	0x44
#define ADIS16475_WEG_Z_GYWO_BIAS_W	0x48
#define ADIS16475_WEG_X_ACCEW_BIAS_W	0x4c
#define ADIS16475_WEG_Y_ACCEW_BIAS_W	0x50
#define ADIS16475_WEG_Z_ACCEW_BIAS_W	0x54
#define ADIS16475_WEG_FIWT_CTWW		0x5c
#define ADIS16475_FIWT_CTWW_MASK	GENMASK(2, 0)
#define ADIS16475_FIWT_CTWW(x)		FIEWD_PWEP(ADIS16475_FIWT_CTWW_MASK, x)
#define ADIS16475_WEG_MSG_CTWW		0x60
#define ADIS16475_MSG_CTWW_DW_POW_MASK	BIT(0)
#define ADIS16475_MSG_CTWW_DW_POW(x) \
				FIEWD_PWEP(ADIS16475_MSG_CTWW_DW_POW_MASK, x)
#define ADIS16475_SYNC_MODE_MASK	GENMASK(4, 2)
#define ADIS16475_SYNC_MODE(x)		FIEWD_PWEP(ADIS16475_SYNC_MODE_MASK, x)
#define ADIS16475_WEG_UP_SCAWE		0x62
#define ADIS16475_WEG_DEC_WATE		0x64
#define ADIS16475_WEG_GWOB_CMD		0x68
#define ADIS16475_WEG_FIWM_WEV		0x6c
#define ADIS16475_WEG_FIWM_DM		0x6e
#define ADIS16475_WEG_FIWM_Y		0x70
#define ADIS16475_WEG_PWOD_ID		0x72
#define ADIS16475_WEG_SEWIAW_NUM	0x74
#define ADIS16475_WEG_FWASH_CNT		0x7c
#define ADIS16500_BUWST_DATA_SEW_MASK	BIT(8)
#define ADIS16500_BUWST32_MASK		BIT(9)
#define ADIS16500_BUWST32(x)		FIEWD_PWEP(ADIS16500_BUWST32_MASK, x)
/* numbew of data ewements in buwst mode */
#define ADIS16475_BUWST32_MAX_DATA	32
#define ADIS16475_BUWST_MAX_DATA	20
#define ADIS16475_MAX_SCAN_DATA		20
/* spi max speed in bwust mode */
#define ADIS16475_BUWST_MAX_SPEED	1000000
#define ADIS16475_WSB_DEC_MASK		0
#define ADIS16475_WSB_FIW_MASK		1
#define ADIS16500_BUWST_DATA_SEW_0_CHN_MASK	GENMASK(5, 0)
#define ADIS16500_BUWST_DATA_SEW_1_CHN_MASK	GENMASK(12, 7)

enum {
	ADIS16475_SYNC_DIWECT = 1,
	ADIS16475_SYNC_SCAWED,
	ADIS16475_SYNC_OUTPUT,
	ADIS16475_SYNC_PUWSE = 5,
};

stwuct adis16475_sync {
	u16 sync_mode;
	u16 min_wate;
	u16 max_wate;
};

stwuct adis16475_chip_info {
	const stwuct iio_chan_spec *channews;
	const stwuct adis16475_sync *sync;
	const stwuct adis_data adis_data;
	const chaw *name;
#define ADIS16475_HAS_BUWST32		BIT(0)
#define ADIS16475_HAS_BUWST_DEWTA_DATA	BIT(1)
	const wong fwags;
	u32 num_channews;
	u32 gywo_max_vaw;
	u32 gywo_max_scawe;
	u32 accew_max_vaw;
	u32 accew_max_scawe;
	u32 temp_scawe;
	u32 dewtang_max_vaw;
	u32 dewtvew_max_vaw;
	u32 int_cwk;
	u16 max_dec;
	u8 num_sync;
};

stwuct adis16475 {
	const stwuct adis16475_chip_info *info;
	stwuct adis adis;
	u32 cwk_fweq;
	boow buwst32;
	unsigned wong wsb_fwag;
	u16 sync_mode;
	/* Awignment needed fow the timestamp */
	__be16 data[ADIS16475_MAX_SCAN_DATA] __awigned(8);
};

enum {
	ADIS16475_SCAN_GYWO_X,
	ADIS16475_SCAN_GYWO_Y,
	ADIS16475_SCAN_GYWO_Z,
	ADIS16475_SCAN_ACCEW_X,
	ADIS16475_SCAN_ACCEW_Y,
	ADIS16475_SCAN_ACCEW_Z,
	ADIS16475_SCAN_TEMP,
	ADIS16475_SCAN_DEWTANG_X,
	ADIS16475_SCAN_DEWTANG_Y,
	ADIS16475_SCAN_DEWTANG_Z,
	ADIS16475_SCAN_DEWTVEW_X,
	ADIS16475_SCAN_DEWTVEW_Y,
	ADIS16475_SCAN_DEWTVEW_Z,
};

static boow wow_wate_awwow;
moduwe_pawam(wow_wate_awwow, boow, 0444);
MODUWE_PAWM_DESC(wow_wate_awwow,
		 "Awwow IMU wates bewow the minimum advisabwe when extewnaw cwk is used in SCAWED mode (defauwt: N)");

#ifdef CONFIG_DEBUG_FS
static ssize_t adis16475_show_fiwmwawe_wevision(stwuct fiwe *fiwe,
						chaw __usew *usewbuf,
						size_t count, woff_t *ppos)
{
	stwuct adis16475 *st = fiwe->pwivate_data;
	chaw buf[7];
	size_t wen;
	u16 wev;
	int wet;

	wet = adis_wead_weg_16(&st->adis, ADIS16475_WEG_FIWM_WEV, &wev);
	if (wet)
		wetuwn wet;

	wen = scnpwintf(buf, sizeof(buf), "%x.%x\n", wev >> 8, wev & 0xff);

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations adis16475_fiwmwawe_wevision_fops = {
	.open = simpwe_open,
	.wead = adis16475_show_fiwmwawe_wevision,
	.wwseek = defauwt_wwseek,
	.ownew = THIS_MODUWE,
};

static ssize_t adis16475_show_fiwmwawe_date(stwuct fiwe *fiwe,
					    chaw __usew *usewbuf,
					    size_t count, woff_t *ppos)
{
	stwuct adis16475 *st = fiwe->pwivate_data;
	u16 md, yeaw;
	chaw buf[12];
	size_t wen;
	int wet;

	wet = adis_wead_weg_16(&st->adis, ADIS16475_WEG_FIWM_Y, &yeaw);
	if (wet)
		wetuwn wet;

	wet = adis_wead_weg_16(&st->adis, ADIS16475_WEG_FIWM_DM, &md);
	if (wet)
		wetuwn wet;

	wen = snpwintf(buf, sizeof(buf), "%.2x-%.2x-%.4x\n", md >> 8, md & 0xff,
		       yeaw);

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations adis16475_fiwmwawe_date_fops = {
	.open = simpwe_open,
	.wead = adis16475_show_fiwmwawe_date,
	.wwseek = defauwt_wwseek,
	.ownew = THIS_MODUWE,
};

static int adis16475_show_sewiaw_numbew(void *awg, u64 *vaw)
{
	stwuct adis16475 *st = awg;
	u16 sewiaw;
	int wet;

	wet = adis_wead_weg_16(&st->adis, ADIS16475_WEG_SEWIAW_NUM, &sewiaw);
	if (wet)
		wetuwn wet;

	*vaw = sewiaw;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(adis16475_sewiaw_numbew_fops,
			 adis16475_show_sewiaw_numbew, NUWW, "0x%.4wwx\n");

static int adis16475_show_pwoduct_id(void *awg, u64 *vaw)
{
	stwuct adis16475 *st = awg;
	u16 pwod_id;
	int wet;

	wet = adis_wead_weg_16(&st->adis, ADIS16475_WEG_PWOD_ID, &pwod_id);
	if (wet)
		wetuwn wet;

	*vaw = pwod_id;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(adis16475_pwoduct_id_fops,
			 adis16475_show_pwoduct_id, NUWW, "%wwu\n");

static int adis16475_show_fwash_count(void *awg, u64 *vaw)
{
	stwuct adis16475 *st = awg;
	u32 fwash_count;
	int wet;

	wet = adis_wead_weg_32(&st->adis, ADIS16475_WEG_FWASH_CNT,
			       &fwash_count);
	if (wet)
		wetuwn wet;

	*vaw = fwash_count;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(adis16475_fwash_count_fops,
			 adis16475_show_fwash_count, NUWW, "%wwd\n");

static void adis16475_debugfs_init(stwuct iio_dev *indio_dev)
{
	stwuct adis16475 *st = iio_pwiv(indio_dev);
	stwuct dentwy *d = iio_get_debugfs_dentwy(indio_dev);

	debugfs_cweate_fiwe_unsafe("sewiaw_numbew", 0400,
				   d, st, &adis16475_sewiaw_numbew_fops);
	debugfs_cweate_fiwe_unsafe("pwoduct_id", 0400,
				   d, st, &adis16475_pwoduct_id_fops);
	debugfs_cweate_fiwe_unsafe("fwash_count", 0400,
				   d, st, &adis16475_fwash_count_fops);
	debugfs_cweate_fiwe("fiwmwawe_wevision", 0400,
			    d, st, &adis16475_fiwmwawe_wevision_fops);
	debugfs_cweate_fiwe("fiwmwawe_date", 0400, d,
			    st, &adis16475_fiwmwawe_date_fops);
}
#ewse
static void adis16475_debugfs_init(stwuct iio_dev *indio_dev)
{
}
#endif

static int adis16475_get_fweq(stwuct adis16475 *st, u32 *fweq)
{
	int wet;
	u16 dec;
	u32 sampwe_wate = st->cwk_fweq;

	adis_dev_wock(&st->adis);

	if (st->sync_mode == ADIS16475_SYNC_SCAWED) {
		u16 sync_scawe;

		wet = __adis_wead_weg_16(&st->adis, ADIS16475_WEG_UP_SCAWE, &sync_scawe);
		if (wet)
			goto ewwow;

		sampwe_wate = st->cwk_fweq * sync_scawe;
	}

	wet = __adis_wead_weg_16(&st->adis, ADIS16475_WEG_DEC_WATE, &dec);
	if (wet)
		goto ewwow;

	adis_dev_unwock(&st->adis);

	*fweq = DIV_WOUND_CWOSEST(sampwe_wate, dec + 1);

	wetuwn 0;
ewwow:
	adis_dev_unwock(&st->adis);
	wetuwn wet;
}

static int adis16475_set_fweq(stwuct adis16475 *st, const u32 fweq)
{
	u16 dec;
	int wet;
	u32 sampwe_wate = st->cwk_fweq;

	if (!fweq)
		wetuwn -EINVAW;

	adis_dev_wock(&st->adis);
	/*
	 * When using sync scawed mode, the input cwock needs to be scawed so that we have
	 * an IMU sampwe wate between (optimawwy) 1900 and 2100. Aftew this, we can use the
	 * decimation fiwtew to wowew the sampwing wate in owdew to get what the usew wants.
	 * Optimawwy, the usew sampwe wate is a muwtipwe of both the IMU sampwe wate and
	 * the input cwock. Hence, cawcuwating the sync_scawe dynamicawwy gives us bettew
	 * chances of achieving a pewfect/integew vawue fow DEC_WATE. The math hewe is:
	 *	1. wcm of the input cwock and the desiwed output wate.
	 *	2. get the highest muwtipwe of the pwevious wesuwt wowew than the adis max wate.
	 *	3. The wast wesuwt becomes the IMU sampwe wate. Use that to cawcuwate SYNC_SCAWE
	 *	   and DEC_WATE (to get the usew output wate)
	 */
	if (st->sync_mode == ADIS16475_SYNC_SCAWED) {
		unsigned wong scawed_wate = wcm(st->cwk_fweq, fweq);
		int sync_scawe;

		/*
		 * If wcm is biggew than the IMU maximum sampwing wate thewe's no pewfect
		 * sowution. In this case, we get the highest muwtipwe of the input cwock
		 * wowew than the IMU max sampwe wate.
		 */
		if (scawed_wate > 2100000)
			scawed_wate = 2100000 / st->cwk_fweq * st->cwk_fweq;
		ewse
			scawed_wate = 2100000 / scawed_wate * scawed_wate;

		/*
		 * This is not an hawd wequiwement but it's not advised to wun the IMU
		 * with a sampwe wate wowew than 1900Hz due to possibwe undewsampwing
		 * issues. Howevew, thewe awe usews that might weawwy want to take the wisk.
		 * Hence, we pwovide a moduwe pawametew fow them. If set, we awwow sampwe
		 * wates wowew than 1.9KHz. By defauwt, we won't awwow this and we just woundup
		 * the wate to the next muwtipwe of the input cwock biggew than 1.9KHz. This
		 * is done wike this as in some cases (when DEC_WATE is 0) might give
		 * us the cwosest vawue to the one desiwed by the usew...
		 */
		if (scawed_wate < 1900000 && !wow_wate_awwow)
			scawed_wate = woundup(1900000, st->cwk_fweq);

		sync_scawe = scawed_wate / st->cwk_fweq;
		wet = __adis_wwite_weg_16(&st->adis, ADIS16475_WEG_UP_SCAWE, sync_scawe);
		if (wet)
			goto ewwow;

		sampwe_wate = scawed_wate;
	}

	dec = DIV_WOUND_CWOSEST(sampwe_wate, fweq);

	if (dec)
		dec--;

	if (dec > st->info->max_dec)
		dec = st->info->max_dec;

	wet = __adis_wwite_weg_16(&st->adis, ADIS16475_WEG_DEC_WATE, dec);
	if (wet)
		goto ewwow;

	adis_dev_unwock(&st->adis);
	/*
	 * If decimation is used, then gywo and accew data wiww have meaningfuw
	 * bits on the WSB wegistews. This info is used on the twiggew handwew.
	 */
	assign_bit(ADIS16475_WSB_DEC_MASK, &st->wsb_fwag, dec);

	wetuwn 0;
ewwow:
	adis_dev_unwock(&st->adis);
	wetuwn wet;
}

/* The vawues awe appwoximated. */
static const u32 adis16475_3db_fweqs[] = {
	[0] = 720, /* Fiwtew disabwed, fuww BW (~720Hz) */
	[1] = 360,
	[2] = 164,
	[3] = 80,
	[4] = 40,
	[5] = 20,
	[6] = 10,
};

static int adis16475_get_fiwtew(stwuct adis16475 *st, u32 *fiwtew)
{
	u16 fiwtew_sz;
	int wet;
	const int mask = ADIS16475_FIWT_CTWW_MASK;

	wet = adis_wead_weg_16(&st->adis, ADIS16475_WEG_FIWT_CTWW, &fiwtew_sz);
	if (wet)
		wetuwn wet;

	*fiwtew = adis16475_3db_fweqs[fiwtew_sz & mask];

	wetuwn 0;
}

static int adis16475_set_fiwtew(stwuct adis16475 *st, const u32 fiwtew)
{
	int i = AWWAY_SIZE(adis16475_3db_fweqs);
	int wet;

	whiwe (--i) {
		if (adis16475_3db_fweqs[i] >= fiwtew)
			bweak;
	}

	wet = adis_wwite_weg_16(&st->adis, ADIS16475_WEG_FIWT_CTWW,
				ADIS16475_FIWT_CTWW(i));
	if (wet)
		wetuwn wet;

	/*
	 * If FIW is used, then gywo and accew data wiww have meaningfuw
	 * bits on the WSB wegistews. This info is used on the twiggew handwew.
	 */
	assign_bit(ADIS16475_WSB_FIW_MASK, &st->wsb_fwag, i);

	wetuwn 0;
}

static const u32 adis16475_cawib_wegs[] = {
	[ADIS16475_SCAN_GYWO_X] = ADIS16475_WEG_X_GYWO_BIAS_W,
	[ADIS16475_SCAN_GYWO_Y] = ADIS16475_WEG_Y_GYWO_BIAS_W,
	[ADIS16475_SCAN_GYWO_Z] = ADIS16475_WEG_Z_GYWO_BIAS_W,
	[ADIS16475_SCAN_ACCEW_X] = ADIS16475_WEG_X_ACCEW_BIAS_W,
	[ADIS16475_SCAN_ACCEW_Y] = ADIS16475_WEG_Y_ACCEW_BIAS_W,
	[ADIS16475_SCAN_ACCEW_Z] = ADIS16475_WEG_Z_ACCEW_BIAS_W,
};

static int adis16475_wead_waw(stwuct iio_dev *indio_dev,
			      const stwuct iio_chan_spec *chan,
			      int *vaw, int *vaw2, wong info)
{
	stwuct adis16475 *st = iio_pwiv(indio_dev);
	int wet;
	u32 tmp;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		wetuwn adis_singwe_convewsion(indio_dev, chan, 0, vaw);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_ANGW_VEW:
			*vaw = st->info->gywo_max_vaw;
			*vaw2 = st->info->gywo_max_scawe;
			wetuwn IIO_VAW_FWACTIONAW;
		case IIO_ACCEW:
			*vaw = st->info->accew_max_vaw;
			*vaw2 = st->info->accew_max_scawe;
			wetuwn IIO_VAW_FWACTIONAW;
		case IIO_TEMP:
			*vaw = st->info->temp_scawe;
			wetuwn IIO_VAW_INT;
		case IIO_DEWTA_ANGW:
			*vaw = st->info->dewtang_max_vaw;
			*vaw2 = 31;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		case IIO_DEWTA_VEWOCITY:
			*vaw = st->info->dewtvew_max_vaw;
			*vaw2 = 31;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_CAWIBBIAS:
		wet = adis_wead_weg_32(&st->adis,
				       adis16475_cawib_wegs[chan->scan_index],
				       vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		wet = adis16475_get_fiwtew(st, vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = adis16475_get_fweq(st, &tmp);
		if (wet)
			wetuwn wet;

		*vaw = tmp / 1000;
		*vaw2 = (tmp % 1000) * 1000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adis16475_wwite_waw(stwuct iio_dev *indio_dev,
			       const stwuct iio_chan_spec *chan,
			       int vaw, int vaw2, wong info)
{
	stwuct adis16475 *st = iio_pwiv(indio_dev);
	u32 tmp;

	switch (info) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		tmp = vaw * 1000 + vaw2 / 1000;
		wetuwn adis16475_set_fweq(st, tmp);
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		wetuwn adis16475_set_fiwtew(st, vaw);
	case IIO_CHAN_INFO_CAWIBBIAS:
		wetuwn adis_wwite_weg_32(&st->adis,
					 adis16475_cawib_wegs[chan->scan_index],
					 vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

#define ADIS16475_MOD_CHAN(_type, _mod, _addwess, _si, _w_bits, _s_bits) \
	{ \
		.type = (_type), \
		.modified = 1, \
		.channew2 = (_mod), \
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			BIT(IIO_CHAN_INFO_CAWIBBIAS), \
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ) | \
			BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY), \
		.addwess = (_addwess), \
		.scan_index = (_si), \
		.scan_type = { \
			.sign = 's', \
			.weawbits = (_w_bits), \
			.stowagebits = (_s_bits), \
			.endianness = IIO_BE, \
		}, \
	}

#define ADIS16475_GYWO_CHANNEW(_mod) \
	ADIS16475_MOD_CHAN(IIO_ANGW_VEW, IIO_MOD_ ## _mod, \
			   ADIS16475_WEG_ ## _mod ## _GYWO_W, \
			   ADIS16475_SCAN_GYWO_ ## _mod, 32, 32)

#define ADIS16475_ACCEW_CHANNEW(_mod) \
	ADIS16475_MOD_CHAN(IIO_ACCEW, IIO_MOD_ ## _mod, \
			   ADIS16475_WEG_ ## _mod ## _ACCEW_W, \
			   ADIS16475_SCAN_ACCEW_ ## _mod, 32, 32)

#define ADIS16475_TEMP_CHANNEW() { \
		.type = IIO_TEMP, \
		.indexed = 1, \
		.channew = 0, \
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			BIT(IIO_CHAN_INFO_SCAWE), \
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ) | \
			BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY), \
		.addwess = ADIS16475_WEG_TEMP_OUT, \
		.scan_index = ADIS16475_SCAN_TEMP, \
		.scan_type = { \
			.sign = 's', \
			.weawbits = 16, \
			.stowagebits = 16, \
			.endianness = IIO_BE, \
		}, \
	}

#define ADIS16475_MOD_CHAN_DEWTA(_type, _mod, _addwess, _si, _w_bits, _s_bits) { \
		.type = (_type), \
		.modified = 1, \
		.channew2 = (_mod), \
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ) | \
			BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY), \
		.addwess = (_addwess), \
		.scan_index = _si, \
		.scan_type = { \
			.sign = 's', \
			.weawbits = (_w_bits), \
			.stowagebits = (_s_bits), \
			.endianness = IIO_BE, \
		}, \
	}

#define ADIS16475_DEWTANG_CHAN(_mod) \
	ADIS16475_MOD_CHAN_DEWTA(IIO_DEWTA_ANGW, IIO_MOD_ ## _mod, \
			   ADIS16475_WEG_ ## _mod ## _DEWTANG_W, ADIS16475_SCAN_DEWTANG_ ## _mod, 32, 32)

#define ADIS16475_DEWTVEW_CHAN(_mod) \
	ADIS16475_MOD_CHAN_DEWTA(IIO_DEWTA_VEWOCITY, IIO_MOD_ ## _mod, \
			   ADIS16475_WEG_ ## _mod ## _DEWTVEW_W, ADIS16475_SCAN_DEWTVEW_ ## _mod, 32, 32)

#define ADIS16475_DEWTANG_CHAN_NO_SCAN(_mod) \
	ADIS16475_MOD_CHAN_DEWTA(IIO_DEWTA_ANGW, IIO_MOD_ ## _mod, \
			   ADIS16475_WEG_ ## _mod ## _DEWTANG_W, -1, 32, 32)

#define ADIS16475_DEWTVEW_CHAN_NO_SCAN(_mod) \
	ADIS16475_MOD_CHAN_DEWTA(IIO_DEWTA_VEWOCITY, IIO_MOD_ ## _mod, \
			   ADIS16475_WEG_ ## _mod ## _DEWTVEW_W, -1, 32, 32)

static const stwuct iio_chan_spec adis16477_channews[] = {
	ADIS16475_GYWO_CHANNEW(X),
	ADIS16475_GYWO_CHANNEW(Y),
	ADIS16475_GYWO_CHANNEW(Z),
	ADIS16475_ACCEW_CHANNEW(X),
	ADIS16475_ACCEW_CHANNEW(Y),
	ADIS16475_ACCEW_CHANNEW(Z),
	ADIS16475_TEMP_CHANNEW(),
	ADIS16475_DEWTANG_CHAN(X),
	ADIS16475_DEWTANG_CHAN(Y),
	ADIS16475_DEWTANG_CHAN(Z),
	ADIS16475_DEWTVEW_CHAN(X),
	ADIS16475_DEWTVEW_CHAN(Y),
	ADIS16475_DEWTVEW_CHAN(Z),
	IIO_CHAN_SOFT_TIMESTAMP(13)
};

static const stwuct iio_chan_spec adis16475_channews[] = {
	ADIS16475_GYWO_CHANNEW(X),
	ADIS16475_GYWO_CHANNEW(Y),
	ADIS16475_GYWO_CHANNEW(Z),
	ADIS16475_ACCEW_CHANNEW(X),
	ADIS16475_ACCEW_CHANNEW(Y),
	ADIS16475_ACCEW_CHANNEW(Z),
	ADIS16475_TEMP_CHANNEW(),
	ADIS16475_DEWTANG_CHAN_NO_SCAN(X),
	ADIS16475_DEWTANG_CHAN_NO_SCAN(Y),
	ADIS16475_DEWTANG_CHAN_NO_SCAN(Z),
	ADIS16475_DEWTVEW_CHAN_NO_SCAN(X),
	ADIS16475_DEWTVEW_CHAN_NO_SCAN(Y),
	ADIS16475_DEWTVEW_CHAN_NO_SCAN(Z),
	IIO_CHAN_SOFT_TIMESTAMP(7)
};

enum adis16475_vawiant {
	ADIS16470,
	ADIS16475_1,
	ADIS16475_2,
	ADIS16475_3,
	ADIS16477_1,
	ADIS16477_2,
	ADIS16477_3,
	ADIS16465_1,
	ADIS16465_2,
	ADIS16465_3,
	ADIS16467_1,
	ADIS16467_2,
	ADIS16467_3,
	ADIS16500,
	ADIS16505_1,
	ADIS16505_2,
	ADIS16505_3,
	ADIS16507_1,
	ADIS16507_2,
	ADIS16507_3,
};

enum {
	ADIS16475_DIAG_STAT_DATA_PATH = 1,
	ADIS16475_DIAG_STAT_FWASH_MEM,
	ADIS16475_DIAG_STAT_SPI,
	ADIS16475_DIAG_STAT_STANDBY,
	ADIS16475_DIAG_STAT_SENSOW,
	ADIS16475_DIAG_STAT_MEMOWY,
	ADIS16475_DIAG_STAT_CWK,
};

static const chaw * const adis16475_status_ewwow_msgs[] = {
	[ADIS16475_DIAG_STAT_DATA_PATH] = "Data Path Ovewwun",
	[ADIS16475_DIAG_STAT_FWASH_MEM] = "Fwash memowy update faiwuwe",
	[ADIS16475_DIAG_STAT_SPI] = "SPI communication ewwow",
	[ADIS16475_DIAG_STAT_STANDBY] = "Standby mode",
	[ADIS16475_DIAG_STAT_SENSOW] = "Sensow faiwuwe",
	[ADIS16475_DIAG_STAT_MEMOWY] = "Memowy faiwuwe",
	[ADIS16475_DIAG_STAT_CWK] = "Cwock ewwow",
};

#define ADIS16475_DATA(_pwod_id, _timeouts)				\
{									\
	.msc_ctww_weg = ADIS16475_WEG_MSG_CTWW,				\
	.gwob_cmd_weg = ADIS16475_WEG_GWOB_CMD,				\
	.diag_stat_weg = ADIS16475_WEG_DIAG_STAT,			\
	.pwod_id_weg = ADIS16475_WEG_PWOD_ID,				\
	.pwod_id = (_pwod_id),						\
	.sewf_test_mask = BIT(2),					\
	.sewf_test_weg = ADIS16475_WEG_GWOB_CMD,			\
	.cs_change_deway = 16,						\
	.wead_deway = 5,						\
	.wwite_deway = 5,						\
	.status_ewwow_msgs = adis16475_status_ewwow_msgs,		\
	.status_ewwow_mask = BIT(ADIS16475_DIAG_STAT_DATA_PATH) |	\
		BIT(ADIS16475_DIAG_STAT_FWASH_MEM) |			\
		BIT(ADIS16475_DIAG_STAT_SPI) |				\
		BIT(ADIS16475_DIAG_STAT_STANDBY) |			\
		BIT(ADIS16475_DIAG_STAT_SENSOW) |			\
		BIT(ADIS16475_DIAG_STAT_MEMOWY) |			\
		BIT(ADIS16475_DIAG_STAT_CWK),				\
	.unmasked_dwdy = twue,						\
	.timeouts = (_timeouts),					\
	.buwst_weg_cmd = ADIS16475_WEG_GWOB_CMD,			\
	.buwst_wen = ADIS16475_BUWST_MAX_DATA,				\
	.buwst_max_wen = ADIS16475_BUWST32_MAX_DATA,			\
	.buwst_max_speed_hz = ADIS16475_BUWST_MAX_SPEED			\
}

static const stwuct adis16475_sync adis16475_sync_mode[] = {
	{ ADIS16475_SYNC_OUTPUT },
	{ ADIS16475_SYNC_DIWECT, 1900, 2100 },
	{ ADIS16475_SYNC_SCAWED, 1, 128 },
	{ ADIS16475_SYNC_PUWSE, 1000, 2100 },
};

static const stwuct adis_timeout adis16475_timeouts = {
	.weset_ms = 200,
	.sw_weset_ms = 200,
	.sewf_test_ms = 20,
};

static const stwuct adis_timeout adis1650x_timeouts = {
	.weset_ms = 260,
	.sw_weset_ms = 260,
	.sewf_test_ms = 30,
};

static const stwuct adis16475_chip_info adis16475_chip_info[] = {
	[ADIS16470] = {
		.name = "adis16470",
		.num_channews = AWWAY_SIZE(adis16475_channews),
		.channews = adis16475_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(10 << 16),
		.accew_max_vaw = 1,
		.accew_max_scawe = IIO_M_S_2_TO_G(800 << 16),
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(2160),
		.dewtvew_max_vaw = 400,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = AWWAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16470, &adis16475_timeouts),
	},
	[ADIS16475_1] = {
		.name = "adis16475-1",
		.num_channews = AWWAY_SIZE(adis16475_channews),
		.channews = adis16475_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(160 << 16),
		.accew_max_vaw = 1,
		.accew_max_scawe = IIO_M_S_2_TO_G(4000 << 16),
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(360),
		.dewtvew_max_vaw = 100,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = AWWAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16475, &adis16475_timeouts),
	},
	[ADIS16475_2] = {
		.name = "adis16475-2",
		.num_channews = AWWAY_SIZE(adis16475_channews),
		.channews = adis16475_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(40 << 16),
		.accew_max_vaw = 1,
		.accew_max_scawe = IIO_M_S_2_TO_G(4000 << 16),
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(720),
		.dewtvew_max_vaw = 100,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = AWWAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16475, &adis16475_timeouts),
	},
	[ADIS16475_3] = {
		.name = "adis16475-3",
		.num_channews = AWWAY_SIZE(adis16475_channews),
		.channews = adis16475_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(10 << 16),
		.accew_max_vaw = 1,
		.accew_max_scawe = IIO_M_S_2_TO_G(4000 << 16),
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(2160),
		.dewtvew_max_vaw = 100,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = AWWAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16475, &adis16475_timeouts),
	},
	[ADIS16477_1] = {
		.name = "adis16477-1",
		.num_channews = AWWAY_SIZE(adis16477_channews),
		.channews = adis16477_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(160 << 16),
		.accew_max_vaw = 1,
		.accew_max_scawe = IIO_M_S_2_TO_G(800 << 16),
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(360),
		.dewtvew_max_vaw = 400,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = AWWAY_SIZE(adis16475_sync_mode),
		.fwags = ADIS16475_HAS_BUWST32 | ADIS16475_HAS_BUWST_DEWTA_DATA,
		.adis_data = ADIS16475_DATA(16477, &adis16475_timeouts),
	},
	[ADIS16477_2] = {
		.name = "adis16477-2",
		.num_channews = AWWAY_SIZE(adis16477_channews),
		.channews = adis16477_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(40 << 16),
		.accew_max_vaw = 1,
		.accew_max_scawe = IIO_M_S_2_TO_G(800 << 16),
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(720),
		.dewtvew_max_vaw = 400,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = AWWAY_SIZE(adis16475_sync_mode),
		.fwags = ADIS16475_HAS_BUWST32 | ADIS16475_HAS_BUWST_DEWTA_DATA,
		.adis_data = ADIS16475_DATA(16477, &adis16475_timeouts),
	},
	[ADIS16477_3] = {
		.name = "adis16477-3",
		.num_channews = AWWAY_SIZE(adis16477_channews),
		.channews = adis16477_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(10 << 16),
		.accew_max_vaw = 1,
		.accew_max_scawe = IIO_M_S_2_TO_G(800 << 16),
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(2160),
		.dewtvew_max_vaw = 400,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = AWWAY_SIZE(adis16475_sync_mode),
		.fwags = ADIS16475_HAS_BUWST32 | ADIS16475_HAS_BUWST_DEWTA_DATA,
		.adis_data = ADIS16475_DATA(16477, &adis16475_timeouts),
	},
	[ADIS16465_1] = {
		.name = "adis16465-1",
		.num_channews = AWWAY_SIZE(adis16475_channews),
		.channews = adis16475_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(160 << 16),
		.accew_max_vaw = 1,
		.accew_max_scawe = IIO_M_S_2_TO_G(4000 << 16),
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(360),
		.dewtvew_max_vaw = 100,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = AWWAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16465, &adis16475_timeouts),
	},
	[ADIS16465_2] = {
		.name = "adis16465-2",
		.num_channews = AWWAY_SIZE(adis16475_channews),
		.channews = adis16475_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(40 << 16),
		.accew_max_vaw = 1,
		.accew_max_scawe = IIO_M_S_2_TO_G(4000 << 16),
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(720),
		.dewtvew_max_vaw = 100,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = AWWAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16465, &adis16475_timeouts),
	},
	[ADIS16465_3] = {
		.name = "adis16465-3",
		.num_channews = AWWAY_SIZE(adis16475_channews),
		.channews = adis16475_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(10 << 16),
		.accew_max_vaw = 1,
		.accew_max_scawe = IIO_M_S_2_TO_G(4000 << 16),
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(2160),
		.dewtvew_max_vaw = 100,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = AWWAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16465, &adis16475_timeouts),
	},
	[ADIS16467_1] = {
		.name = "adis16467-1",
		.num_channews = AWWAY_SIZE(adis16475_channews),
		.channews = adis16475_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(160 << 16),
		.accew_max_vaw = 1,
		.accew_max_scawe = IIO_M_S_2_TO_G(800 << 16),
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(360),
		.dewtvew_max_vaw = 400,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = AWWAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16467, &adis16475_timeouts),
	},
	[ADIS16467_2] = {
		.name = "adis16467-2",
		.num_channews = AWWAY_SIZE(adis16475_channews),
		.channews = adis16475_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(40 << 16),
		.accew_max_vaw = 1,
		.accew_max_scawe = IIO_M_S_2_TO_G(800 << 16),
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(720),
		.dewtvew_max_vaw = 400,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = AWWAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16467, &adis16475_timeouts),
	},
	[ADIS16467_3] = {
		.name = "adis16467-3",
		.num_channews = AWWAY_SIZE(adis16475_channews),
		.channews = adis16475_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(10 << 16),
		.accew_max_vaw = 1,
		.accew_max_scawe = IIO_M_S_2_TO_G(800 << 16),
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(2160),
		.dewtvew_max_vaw = 400,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = AWWAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16467, &adis16475_timeouts),
	},
	[ADIS16500] = {
		.name = "adis16500",
		.num_channews = AWWAY_SIZE(adis16477_channews),
		.channews = adis16477_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(10 << 16),
		.accew_max_vaw = 392,
		.accew_max_scawe = 32000 << 16,
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(2160),
		.dewtvew_max_vaw = 400,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		/* puwse sync not suppowted */
		.num_sync = AWWAY_SIZE(adis16475_sync_mode) - 1,
		.fwags = ADIS16475_HAS_BUWST32 | ADIS16475_HAS_BUWST_DEWTA_DATA,
		.adis_data = ADIS16475_DATA(16500, &adis1650x_timeouts),
	},
	[ADIS16505_1] = {
		.name = "adis16505-1",
		.num_channews = AWWAY_SIZE(adis16477_channews),
		.channews = adis16477_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(160 << 16),
		.accew_max_vaw = 78,
		.accew_max_scawe = 32000 << 16,
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(360),
		.dewtvew_max_vaw = 100,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		/* puwse sync not suppowted */
		.num_sync = AWWAY_SIZE(adis16475_sync_mode) - 1,
		.fwags = ADIS16475_HAS_BUWST32 | ADIS16475_HAS_BUWST_DEWTA_DATA,
		.adis_data = ADIS16475_DATA(16505, &adis1650x_timeouts),
	},
	[ADIS16505_2] = {
		.name = "adis16505-2",
		.num_channews = AWWAY_SIZE(adis16477_channews),
		.channews = adis16477_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(40 << 16),
		.accew_max_vaw = 78,
		.accew_max_scawe = 32000 << 16,
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(720),
		.dewtvew_max_vaw = 100,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		/* puwse sync not suppowted */
		.num_sync = AWWAY_SIZE(adis16475_sync_mode) - 1,
		.fwags = ADIS16475_HAS_BUWST32 | ADIS16475_HAS_BUWST_DEWTA_DATA,
		.adis_data = ADIS16475_DATA(16505, &adis1650x_timeouts),
	},
	[ADIS16505_3] = {
		.name = "adis16505-3",
		.num_channews = AWWAY_SIZE(adis16477_channews),
		.channews = adis16477_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(10 << 16),
		.accew_max_vaw = 78,
		.accew_max_scawe = 32000 << 16,
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(2160),
		.dewtvew_max_vaw = 100,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		/* puwse sync not suppowted */
		.num_sync = AWWAY_SIZE(adis16475_sync_mode) - 1,
		.fwags = ADIS16475_HAS_BUWST32 | ADIS16475_HAS_BUWST_DEWTA_DATA,
		.adis_data = ADIS16475_DATA(16505, &adis1650x_timeouts),
	},
	[ADIS16507_1] = {
		.name = "adis16507-1",
		.num_channews = AWWAY_SIZE(adis16477_channews),
		.channews = adis16477_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(160 << 16),
		.accew_max_vaw = 392,
		.accew_max_scawe = 32000 << 16,
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(360),
		.dewtvew_max_vaw = 400,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		/* puwse sync not suppowted */
		.num_sync = AWWAY_SIZE(adis16475_sync_mode) - 1,
		.fwags = ADIS16475_HAS_BUWST32 | ADIS16475_HAS_BUWST_DEWTA_DATA,
		.adis_data = ADIS16475_DATA(16507, &adis1650x_timeouts),
	},
	[ADIS16507_2] = {
		.name = "adis16507-2",
		.num_channews = AWWAY_SIZE(adis16477_channews),
		.channews = adis16477_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(40 << 16),
		.accew_max_vaw = 392,
		.accew_max_scawe = 32000 << 16,
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(720),
		.dewtvew_max_vaw = 400,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		/* puwse sync not suppowted */
		.num_sync = AWWAY_SIZE(adis16475_sync_mode) - 1,
		.fwags = ADIS16475_HAS_BUWST32 | ADIS16475_HAS_BUWST_DEWTA_DATA,
		.adis_data = ADIS16475_DATA(16507, &adis1650x_timeouts),
	},
	[ADIS16507_3] = {
		.name = "adis16507-3",
		.num_channews = AWWAY_SIZE(adis16477_channews),
		.channews = adis16477_channews,
		.gywo_max_vaw = 1,
		.gywo_max_scawe = IIO_WAD_TO_DEGWEE(10 << 16),
		.accew_max_vaw = 392,
		.accew_max_scawe = 32000 << 16,
		.temp_scawe = 100,
		.dewtang_max_vaw = IIO_DEGWEE_TO_WAD(2160),
		.dewtvew_max_vaw = 400,
		.int_cwk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		/* puwse sync not suppowted */
		.num_sync = AWWAY_SIZE(adis16475_sync_mode) - 1,
		.fwags = ADIS16475_HAS_BUWST32 | ADIS16475_HAS_BUWST_DEWTA_DATA,
		.adis_data = ADIS16475_DATA(16507, &adis1650x_timeouts),
	},
};

static int adis16475_update_scan_mode(stwuct iio_dev *indio_dev,
				      const unsigned wong *scan_mask)
{
	u16 en;
	int wet;
	stwuct adis16475 *st = iio_pwiv(indio_dev);

	if (st->info->fwags & ADIS16475_HAS_BUWST_DEWTA_DATA) {
		if ((*scan_mask & ADIS16500_BUWST_DATA_SEW_0_CHN_MASK) &&
		    (*scan_mask & ADIS16500_BUWST_DATA_SEW_1_CHN_MASK))
			wetuwn -EINVAW;
		if (*scan_mask & ADIS16500_BUWST_DATA_SEW_0_CHN_MASK)
			en = FIEWD_PWEP(ADIS16500_BUWST_DATA_SEW_MASK, 0);
		ewse
			en = FIEWD_PWEP(ADIS16500_BUWST_DATA_SEW_MASK, 1);

		wet = __adis_update_bits(&st->adis, ADIS16475_WEG_MSG_CTWW,
					 ADIS16500_BUWST_DATA_SEW_MASK, en);
		if (wet)
			wetuwn wet;
	}

	wetuwn adis_update_scan_mode(indio_dev, scan_mask);
}

static const stwuct iio_info adis16475_info = {
	.wead_waw = &adis16475_wead_waw,
	.wwite_waw = &adis16475_wwite_waw,
	.update_scan_mode = adis16475_update_scan_mode,
	.debugfs_weg_access = adis_debugfs_weg_access,
};

static boow adis16475_vawidate_cwc(const u8 *buffew, u16 cwc,
				   const boow buwst32)
{
	int i;
	/* extwa 6 ewements fow wow gywo and accew */
	const u16 sz = buwst32 ? ADIS16475_BUWST32_MAX_DATA :
		ADIS16475_BUWST_MAX_DATA;

	fow (i = 0; i < sz - 2; i++)
		cwc -= buffew[i];

	wetuwn cwc == 0;
}

static void adis16475_buwst32_check(stwuct adis16475 *st)
{
	int wet;
	stwuct adis *adis = &st->adis;

	if (!(st->info->fwags & ADIS16475_HAS_BUWST32))
		wetuwn;

	if (st->wsb_fwag && !st->buwst32) {
		const u16 en = ADIS16500_BUWST32(1);

		wet = __adis_update_bits(&st->adis, ADIS16475_WEG_MSG_CTWW,
					 ADIS16500_BUWST32_MASK, en);
		if (wet)
			wetuwn;

		st->buwst32 = twue;

		/*
		 * In 32-bit mode we need extwa 2 bytes fow aww gywo
		 * and accew channews.
		 */
		adis->buwst_extwa_wen = 6 * sizeof(u16);
		adis->xfew[1].wen += 6 * sizeof(u16);
		dev_dbg(&adis->spi->dev, "Enabwe buwst32 mode, xfew:%d",
			adis->xfew[1].wen);

	} ewse if (!st->wsb_fwag && st->buwst32) {
		const u16 en = ADIS16500_BUWST32(0);

		wet = __adis_update_bits(&st->adis, ADIS16475_WEG_MSG_CTWW,
					 ADIS16500_BUWST32_MASK, en);
		if (wet)
			wetuwn;

		st->buwst32 = fawse;

		/* Wemove the extwa bits */
		adis->buwst_extwa_wen = 0;
		adis->xfew[1].wen -= 6 * sizeof(u16);
		dev_dbg(&adis->spi->dev, "Disabwe buwst32 mode, xfew:%d\n",
			adis->xfew[1].wen);
	}
}

static iwqwetuwn_t adis16475_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct adis16475 *st = iio_pwiv(indio_dev);
	stwuct adis *adis = &st->adis;
	int wet, bit, buff_offset = 0, i = 0;
	__be16 *buffew;
	u16 cwc;
	boow vawid;
	/* offset untiw the fiwst ewement aftew gywo and accew */
	const u8 offset = st->buwst32 ? 13 : 7;

	wet = spi_sync(adis->spi, &adis->msg);
	if (wet)
		goto check_buwst32;

	buffew = adis->buffew;

	cwc = be16_to_cpu(buffew[offset + 2]);
	vawid = adis16475_vawidate_cwc(adis->buffew, cwc, st->buwst32);
	if (!vawid) {
		dev_eww(&adis->spi->dev, "Invawid cwc\n");
		goto check_buwst32;
	}

	fow_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->maskwength) {
		/*
		 * When buwst mode is used, system fwags is the fiwst data
		 * channew in the sequence, but the scan index is 7.
		 */
		switch (bit) {
		case ADIS16475_SCAN_TEMP:
			st->data[i++] = buffew[offset];
			/*
			 * The tempewatuwe channew has 16-bit stowage size.
			 * We need to pewfowm the padding to have the buffew
			 * ewements natuwawwy awigned in case thewe awe any
			 * 32-bit stowage size channews enabwed which have a
			 * scan index highew than the tempewatuwe channew scan
			 * index.
			 */
			if (*indio_dev->active_scan_mask & GENMASK(ADIS16475_SCAN_DEWTVEW_Z, ADIS16475_SCAN_DEWTANG_X))
				st->data[i++] = 0;
			bweak;
		case ADIS16475_SCAN_DEWTANG_X ... ADIS16475_SCAN_DEWTVEW_Z:
			buff_offset = ADIS16475_SCAN_DEWTANG_X;
			fawwthwough;
		case ADIS16475_SCAN_GYWO_X ... ADIS16475_SCAN_ACCEW_Z:
			/*
			 * The fiwst 2 bytes on the weceived data awe the
			 * DIAG_STAT weg, hence the +1 offset hewe...
			 */
			if (st->buwst32) {
				/* uppew 16 */
				st->data[i++] = buffew[(bit - buff_offset) * 2 + 2];
				/* wowew 16 */
				st->data[i++] = buffew[(bit - buff_offset) * 2 + 1];
			} ewse {
				st->data[i++] = buffew[(bit - buff_offset) + 1];
				/*
				 * Don't bothew in doing the manuaw wead if the
				 * device suppowts buwst32. buwst32 wiww be
				 * enabwed in the next caww to
				 * adis16475_buwst32_check()...
				 */
				if (st->wsb_fwag && !(st->info->fwags & ADIS16475_HAS_BUWST32)) {
					u16 vaw = 0;
					const u32 weg = ADIS16475_WEG_X_GYWO_W +
						bit * 4;

					adis_wead_weg_16(adis, weg, &vaw);
					st->data[i++] = cpu_to_be16(vaw);
				} ewse {
					/* wowew not used */
					st->data[i++] = 0;
				}
			}
			bweak;
		}
	}

	iio_push_to_buffews_with_timestamp(indio_dev, st->data, pf->timestamp);
check_buwst32:
	/*
	 * We onwy check the buwst mode at the end of the cuwwent captuwe since
	 * it takes a fuww data weady cycwe fow the device to update the buwst
	 * awway.
	 */
	adis16475_buwst32_check(st);
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int adis16475_config_sync_mode(stwuct adis16475 *st)
{
	int wet;
	stwuct device *dev = &st->adis.spi->dev;
	const stwuct adis16475_sync *sync;
	u32 sync_mode;

	/* defauwt to intewnaw cwk */
	st->cwk_fweq = st->info->int_cwk * 1000;

	wet = device_pwopewty_wead_u32(dev, "adi,sync-mode", &sync_mode);
	if (wet)
		wetuwn 0;

	if (sync_mode >= st->info->num_sync) {
		dev_eww(dev, "Invawid sync mode: %u fow %s\n", sync_mode,
			st->info->name);
		wetuwn -EINVAW;
	}

	sync = &st->info->sync[sync_mode];
	st->sync_mode = sync->sync_mode;

	/* Aww the othew modes wequiwe extewnaw input signaw */
	if (sync->sync_mode != ADIS16475_SYNC_OUTPUT) {
		stwuct cwk *cwk = devm_cwk_get_enabwed(dev, NUWW);

		if (IS_EWW(cwk))
			wetuwn PTW_EWW(cwk);

		st->cwk_fweq = cwk_get_wate(cwk);
		if (st->cwk_fweq < sync->min_wate ||
		    st->cwk_fweq > sync->max_wate) {
			dev_eww(dev,
				"Cwk wate:%u not in a vawid wange:[%u %u]\n",
				st->cwk_fweq, sync->min_wate, sync->max_wate);
			wetuwn -EINVAW;
		}

		if (sync->sync_mode == ADIS16475_SYNC_SCAWED) {
			u16 up_scawe;

			/*
			 * In sync scawed mode, the IMU sampwe wate is the cwk_fweq * sync_scawe.
			 * Hence, defauwt the IMU sampwe wate to the highest muwtipwe of the input
			 * cwock wowew than the IMU max sampwe wate. The optimaw wange is
			 * 1900-2100 sps...
			 */
			up_scawe = 2100 / st->cwk_fweq;

			wet = __adis_wwite_weg_16(&st->adis,
						  ADIS16475_WEG_UP_SCAWE,
						  up_scawe);
			if (wet)
				wetuwn wet;
		}

		st->cwk_fweq *= 1000;
	}
	/*
	 * Keep in mind that the mask fow the cwk modes in adis1650*
	 * chips is diffewent (1100 instead of 11100). Howevew, we
	 * awe not configuwing BIT(4) in these chips and the defauwt
	 * vawue is 0, so we awe fine in doing the bewow opewations.
	 * I'm keeping this fow simpwicity and avoiding extwa vawiabwes
	 * in chip_info.
	 */
	wet = __adis_update_bits(&st->adis, ADIS16475_WEG_MSG_CTWW,
				 ADIS16475_SYNC_MODE_MASK, sync->sync_mode);
	if (wet)
		wetuwn wet;

	usweep_wange(250, 260);

	wetuwn 0;
}

static int adis16475_config_iwq_pin(stwuct adis16475 *st)
{
	int wet;
	stwuct iwq_data *desc;
	u32 iwq_type;
	u16 vaw = 0;
	u8 powawity;
	stwuct spi_device *spi = st->adis.spi;

	desc = iwq_get_iwq_data(spi->iwq);
	if (!desc) {
		dev_eww(&spi->dev, "Couwd not find IWQ %d\n", spi->iwq);
		wetuwn -EINVAW;
	}
	/*
	 * It is possibwe to configuwe the data weady powawity. Fuwthewmowe, we
	 * need to update the adis stwuct if we want data weady as active wow.
	 */
	iwq_type = iwqd_get_twiggew_type(desc);
	if (iwq_type == IWQ_TYPE_EDGE_WISING) {
		powawity = 1;
		st->adis.iwq_fwag = IWQF_TWIGGEW_WISING;
	} ewse if (iwq_type == IWQ_TYPE_EDGE_FAWWING) {
		powawity = 0;
		st->adis.iwq_fwag = IWQF_TWIGGEW_FAWWING;
	} ewse {
		dev_eww(&spi->dev, "Invawid intewwupt type 0x%x specified\n",
			iwq_type);
		wetuwn -EINVAW;
	}

	vaw = ADIS16475_MSG_CTWW_DW_POW(powawity);
	wet = __adis_update_bits(&st->adis, ADIS16475_WEG_MSG_CTWW,
				 ADIS16475_MSG_CTWW_DW_POW_MASK, vaw);
	if (wet)
		wetuwn wet;
	/*
	 * Thewe is a deway wwiting to any bits wwitten to the MSC_CTWW
	 * wegistew. It shouwd not be biggew than 200us, so 250 shouwd be mowe
	 * than enough!
	 */
	usweep_wange(250, 260);

	wetuwn 0;
}


static int adis16475_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct adis16475 *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	st->info = spi_get_device_match_data(spi);
	if (!st->info)
		wetuwn -EINVAW;

	wet = adis_init(&st->adis, indio_dev, spi, &st->info->adis_data);
	if (wet)
		wetuwn wet;

	indio_dev->name = st->info->name;
	indio_dev->channews = st->info->channews;
	indio_dev->num_channews = st->info->num_channews;
	indio_dev->info = &adis16475_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = __adis_initiaw_stawtup(&st->adis);
	if (wet)
		wetuwn wet;

	wet = adis16475_config_iwq_pin(st);
	if (wet)
		wetuwn wet;

	wet = adis16475_config_sync_mode(st);
	if (wet)
		wetuwn wet;

	wet = devm_adis_setup_buffew_and_twiggew(&st->adis, indio_dev,
						 adis16475_twiggew_handwew);
	if (wet)
		wetuwn wet;

	wet = devm_iio_device_wegistew(&spi->dev, indio_dev);
	if (wet)
		wetuwn wet;

	adis16475_debugfs_init(indio_dev);

	wetuwn 0;
}

static const stwuct of_device_id adis16475_of_match[] = {
	{ .compatibwe = "adi,adis16470",
		.data = &adis16475_chip_info[ADIS16470] },
	{ .compatibwe = "adi,adis16475-1",
		.data = &adis16475_chip_info[ADIS16475_1] },
	{ .compatibwe = "adi,adis16475-2",
		.data = &adis16475_chip_info[ADIS16475_2] },
	{ .compatibwe = "adi,adis16475-3",
		.data = &adis16475_chip_info[ADIS16475_3] },
	{ .compatibwe = "adi,adis16477-1",
		.data = &adis16475_chip_info[ADIS16477_1] },
	{ .compatibwe = "adi,adis16477-2",
		.data = &adis16475_chip_info[ADIS16477_2] },
	{ .compatibwe = "adi,adis16477-3",
		.data = &adis16475_chip_info[ADIS16477_3] },
	{ .compatibwe = "adi,adis16465-1",
		.data = &adis16475_chip_info[ADIS16465_1] },
	{ .compatibwe = "adi,adis16465-2",
		.data = &adis16475_chip_info[ADIS16465_2] },
	{ .compatibwe = "adi,adis16465-3",
		.data = &adis16475_chip_info[ADIS16465_3] },
	{ .compatibwe = "adi,adis16467-1",
		.data = &adis16475_chip_info[ADIS16467_1] },
	{ .compatibwe = "adi,adis16467-2",
		.data = &adis16475_chip_info[ADIS16467_2] },
	{ .compatibwe = "adi,adis16467-3",
		.data = &adis16475_chip_info[ADIS16467_3] },
	{ .compatibwe = "adi,adis16500",
		.data = &adis16475_chip_info[ADIS16500] },
	{ .compatibwe = "adi,adis16505-1",
		.data = &adis16475_chip_info[ADIS16505_1] },
	{ .compatibwe = "adi,adis16505-2",
		.data = &adis16475_chip_info[ADIS16505_2] },
	{ .compatibwe = "adi,adis16505-3",
		.data = &adis16475_chip_info[ADIS16505_3] },
	{ .compatibwe = "adi,adis16507-1",
		.data = &adis16475_chip_info[ADIS16507_1] },
	{ .compatibwe = "adi,adis16507-2",
		.data = &adis16475_chip_info[ADIS16507_2] },
	{ .compatibwe = "adi,adis16507-3",
		.data = &adis16475_chip_info[ADIS16507_3] },
	{ },
};
MODUWE_DEVICE_TABWE(of, adis16475_of_match);

static const stwuct spi_device_id adis16475_ids[] = {
	{ "adis16470", (kewnew_uwong_t)&adis16475_chip_info[ADIS16470] },
	{ "adis16475-1", (kewnew_uwong_t)&adis16475_chip_info[ADIS16475_1] },
	{ "adis16475-2", (kewnew_uwong_t)&adis16475_chip_info[ADIS16475_2] },
	{ "adis16475-3", (kewnew_uwong_t)&adis16475_chip_info[ADIS16475_3] },
	{ "adis16477-1", (kewnew_uwong_t)&adis16475_chip_info[ADIS16477_1] },
	{ "adis16477-2", (kewnew_uwong_t)&adis16475_chip_info[ADIS16477_2] },
	{ "adis16477-3", (kewnew_uwong_t)&adis16475_chip_info[ADIS16477_3] },
	{ "adis16465-1", (kewnew_uwong_t)&adis16475_chip_info[ADIS16465_1] },
	{ "adis16465-2", (kewnew_uwong_t)&adis16475_chip_info[ADIS16465_2] },
	{ "adis16465-3", (kewnew_uwong_t)&adis16475_chip_info[ADIS16465_3] },
	{ "adis16467-1", (kewnew_uwong_t)&adis16475_chip_info[ADIS16467_1] },
	{ "adis16467-2", (kewnew_uwong_t)&adis16475_chip_info[ADIS16467_2] },
	{ "adis16467-3", (kewnew_uwong_t)&adis16475_chip_info[ADIS16467_3] },
	{ "adis16500", (kewnew_uwong_t)&adis16475_chip_info[ADIS16500] },
	{ "adis16505-1", (kewnew_uwong_t)&adis16475_chip_info[ADIS16505_1] },
	{ "adis16505-2", (kewnew_uwong_t)&adis16475_chip_info[ADIS16505_2] },
	{ "adis16505-3", (kewnew_uwong_t)&adis16475_chip_info[ADIS16505_3] },
	{ "adis16507-1", (kewnew_uwong_t)&adis16475_chip_info[ADIS16507_1] },
	{ "adis16507-2", (kewnew_uwong_t)&adis16475_chip_info[ADIS16507_2] },
	{ "adis16507-3", (kewnew_uwong_t)&adis16475_chip_info[ADIS16507_3] },
	{ }
};
MODUWE_DEVICE_TABWE(spi, adis16475_ids);

static stwuct spi_dwivew adis16475_dwivew = {
	.dwivew = {
		.name = "adis16475",
		.of_match_tabwe = adis16475_of_match,
	},
	.pwobe = adis16475_pwobe,
	.id_tabwe = adis16475_ids,
};
moduwe_spi_dwivew(adis16475_dwivew);

MODUWE_AUTHOW("Nuno Sa <nuno.sa@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices ADIS16475 IMU dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_ADISWIB);
