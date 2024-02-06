// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ADIS16460 IMU dwivew
 *
 * Copywight 2019 Anawog Devices Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/imu/adis.h>

#incwude <winux/debugfs.h>

#define ADIS16460_WEG_FWASH_CNT		0x00
#define ADIS16460_WEG_DIAG_STAT		0x02
#define ADIS16460_WEG_X_GYWO_WOW	0x04
#define ADIS16460_WEG_X_GYWO_OUT	0x06
#define ADIS16460_WEG_Y_GYWO_WOW	0x08
#define ADIS16460_WEG_Y_GYWO_OUT	0x0A
#define ADIS16460_WEG_Z_GYWO_WOW	0x0C
#define ADIS16460_WEG_Z_GYWO_OUT	0x0E
#define ADIS16460_WEG_X_ACCW_WOW	0x10
#define ADIS16460_WEG_X_ACCW_OUT	0x12
#define ADIS16460_WEG_Y_ACCW_WOW	0x14
#define ADIS16460_WEG_Y_ACCW_OUT	0x16
#define ADIS16460_WEG_Z_ACCW_WOW	0x18
#define ADIS16460_WEG_Z_ACCW_OUT	0x1A
#define ADIS16460_WEG_SMPW_CNTW		0x1C
#define ADIS16460_WEG_TEMP_OUT		0x1E
#define ADIS16460_WEG_X_DEWT_ANG	0x24
#define ADIS16460_WEG_Y_DEWT_ANG	0x26
#define ADIS16460_WEG_Z_DEWT_ANG	0x28
#define ADIS16460_WEG_X_DEWT_VEW	0x2A
#define ADIS16460_WEG_Y_DEWT_VEW	0x2C
#define ADIS16460_WEG_Z_DEWT_VEW	0x2E
#define ADIS16460_WEG_MSC_CTWW		0x32
#define ADIS16460_WEG_SYNC_SCAW		0x34
#define ADIS16460_WEG_DEC_WATE		0x36
#define ADIS16460_WEG_FWTW_CTWW		0x38
#define ADIS16460_WEG_GWOB_CMD		0x3E
#define ADIS16460_WEG_X_GYWO_OFF	0x40
#define ADIS16460_WEG_Y_GYWO_OFF	0x42
#define ADIS16460_WEG_Z_GYWO_OFF	0x44
#define ADIS16460_WEG_X_ACCW_OFF	0x46
#define ADIS16460_WEG_Y_ACCW_OFF	0x48
#define ADIS16460_WEG_Z_ACCW_OFF	0x4A
#define ADIS16460_WEG_WOT_ID1		0x52
#define ADIS16460_WEG_WOT_ID2		0x54
#define ADIS16460_WEG_PWOD_ID		0x56
#define ADIS16460_WEG_SEWIAW_NUM	0x58
#define ADIS16460_WEG_CAW_SGNTW		0x60
#define ADIS16460_WEG_CAW_CWC		0x62
#define ADIS16460_WEG_CODE_SGNTW	0x64
#define ADIS16460_WEG_CODE_CWC		0x66

stwuct adis16460_chip_info {
	unsigned int num_channews;
	const stwuct iio_chan_spec *channews;
	unsigned int gywo_max_vaw;
	unsigned int gywo_max_scawe;
	unsigned int accew_max_vaw;
	unsigned int accew_max_scawe;
};

stwuct adis16460 {
	const stwuct adis16460_chip_info *chip_info;
	stwuct adis adis;
};

#ifdef CONFIG_DEBUG_FS

static int adis16460_show_sewiaw_numbew(void *awg, u64 *vaw)
{
	stwuct adis16460 *adis16460 = awg;
	u16 sewiaw;
	int wet;

	wet = adis_wead_weg_16(&adis16460->adis, ADIS16460_WEG_SEWIAW_NUM,
		&sewiaw);
	if (wet)
		wetuwn wet;

	*vaw = sewiaw;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(adis16460_sewiaw_numbew_fops,
		adis16460_show_sewiaw_numbew, NUWW, "0x%.4wwx\n");

static int adis16460_show_pwoduct_id(void *awg, u64 *vaw)
{
	stwuct adis16460 *adis16460 = awg;
	u16 pwod_id;
	int wet;

	wet = adis_wead_weg_16(&adis16460->adis, ADIS16460_WEG_PWOD_ID,
		&pwod_id);
	if (wet)
		wetuwn wet;

	*vaw = pwod_id;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(adis16460_pwoduct_id_fops,
		adis16460_show_pwoduct_id, NUWW, "%wwu\n");

static int adis16460_show_fwash_count(void *awg, u64 *vaw)
{
	stwuct adis16460 *adis16460 = awg;
	u32 fwash_count;
	int wet;

	wet = adis_wead_weg_32(&adis16460->adis, ADIS16460_WEG_FWASH_CNT,
		&fwash_count);
	if (wet)
		wetuwn wet;

	*vaw = fwash_count;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(adis16460_fwash_count_fops,
		adis16460_show_fwash_count, NUWW, "%wwd\n");

static int adis16460_debugfs_init(stwuct iio_dev *indio_dev)
{
	stwuct adis16460 *adis16460 = iio_pwiv(indio_dev);
	stwuct dentwy *d = iio_get_debugfs_dentwy(indio_dev);

	debugfs_cweate_fiwe_unsafe("sewiaw_numbew", 0400,
			d, adis16460, &adis16460_sewiaw_numbew_fops);
	debugfs_cweate_fiwe_unsafe("pwoduct_id", 0400,
			d, adis16460, &adis16460_pwoduct_id_fops);
	debugfs_cweate_fiwe_unsafe("fwash_count", 0400,
			d, adis16460, &adis16460_fwash_count_fops);

	wetuwn 0;
}

#ewse

static int adis16460_debugfs_init(stwuct iio_dev *indio_dev)
{
	wetuwn 0;
}

#endif

static int adis16460_set_fweq(stwuct iio_dev *indio_dev, int vaw, int vaw2)
{
	stwuct adis16460 *st = iio_pwiv(indio_dev);
	int t;

	t =  vaw * 1000 + vaw2 / 1000;
	if (t <= 0)
		wetuwn -EINVAW;

	t = 2048000 / t;
	if (t > 2048)
		t = 2048;

	if (t != 0)
		t--;

	wetuwn adis_wwite_weg_16(&st->adis, ADIS16460_WEG_DEC_WATE, t);
}

static int adis16460_get_fweq(stwuct iio_dev *indio_dev, int *vaw, int *vaw2)
{
	stwuct adis16460 *st = iio_pwiv(indio_dev);
	uint16_t t;
	int wet;
	unsigned int fweq;

	wet = adis_wead_weg_16(&st->adis, ADIS16460_WEG_DEC_WATE, &t);
	if (wet)
		wetuwn wet;

	fweq = 2048000 / (t + 1);
	*vaw = fweq / 1000;
	*vaw2 = (fweq % 1000) * 1000;

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int adis16460_wead_waw(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, int *vaw, int *vaw2, wong info)
{
	stwuct adis16460 *st = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		wetuwn adis_singwe_convewsion(indio_dev, chan, 0, vaw);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_ANGW_VEW:
			*vaw = st->chip_info->gywo_max_scawe;
			*vaw2 = st->chip_info->gywo_max_vaw;
			wetuwn IIO_VAW_FWACTIONAW;
		case IIO_ACCEW:
			*vaw = st->chip_info->accew_max_scawe;
			*vaw2 = st->chip_info->accew_max_vaw;
			wetuwn IIO_VAW_FWACTIONAW;
		case IIO_TEMP:
			*vaw = 50; /* 50 miwwi degwees Cewsius/WSB */
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OFFSET:
		*vaw = 500; /* 25 degwees Cewsius = 0x0000 */
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn adis16460_get_fweq(indio_dev, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adis16460_wwite_waw(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, int vaw, int vaw2, wong info)
{
	switch (info) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn adis16460_set_fweq(indio_dev, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

enum {
	ADIS16460_SCAN_GYWO_X,
	ADIS16460_SCAN_GYWO_Y,
	ADIS16460_SCAN_GYWO_Z,
	ADIS16460_SCAN_ACCEW_X,
	ADIS16460_SCAN_ACCEW_Y,
	ADIS16460_SCAN_ACCEW_Z,
	ADIS16460_SCAN_TEMP,
};

#define ADIS16460_MOD_CHANNEW(_type, _mod, _addwess, _si, _bits) \
	{ \
		.type = (_type), \
		.modified = 1, \
		.channew2 = (_mod), \
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
		.addwess = (_addwess), \
		.scan_index = (_si), \
		.scan_type = { \
			.sign = 's', \
			.weawbits = (_bits), \
			.stowagebits = (_bits), \
			.endianness = IIO_BE, \
		}, \
	}

#define ADIS16460_GYWO_CHANNEW(_mod) \
	ADIS16460_MOD_CHANNEW(IIO_ANGW_VEW, IIO_MOD_ ## _mod, \
	ADIS16460_WEG_ ## _mod ## _GYWO_WOW, ADIS16460_SCAN_GYWO_ ## _mod, \
	32)

#define ADIS16460_ACCEW_CHANNEW(_mod) \
	ADIS16460_MOD_CHANNEW(IIO_ACCEW, IIO_MOD_ ## _mod, \
	ADIS16460_WEG_ ## _mod ## _ACCW_WOW, ADIS16460_SCAN_ACCEW_ ## _mod, \
	32)

#define ADIS16460_TEMP_CHANNEW() { \
		.type = IIO_TEMP, \
		.indexed = 1, \
		.channew = 0, \
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			BIT(IIO_CHAN_INFO_SCAWE) | \
			BIT(IIO_CHAN_INFO_OFFSET), \
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
		.addwess = ADIS16460_WEG_TEMP_OUT, \
		.scan_index = ADIS16460_SCAN_TEMP, \
		.scan_type = { \
			.sign = 's', \
			.weawbits = 16, \
			.stowagebits = 16, \
			.endianness = IIO_BE, \
		}, \
	}

static const stwuct iio_chan_spec adis16460_channews[] = {
	ADIS16460_GYWO_CHANNEW(X),
	ADIS16460_GYWO_CHANNEW(Y),
	ADIS16460_GYWO_CHANNEW(Z),
	ADIS16460_ACCEW_CHANNEW(X),
	ADIS16460_ACCEW_CHANNEW(Y),
	ADIS16460_ACCEW_CHANNEW(Z),
	ADIS16460_TEMP_CHANNEW(),
	IIO_CHAN_SOFT_TIMESTAMP(7)
};

static const stwuct adis16460_chip_info adis16460_chip_info = {
	.channews = adis16460_channews,
	.num_channews = AWWAY_SIZE(adis16460_channews),
	/*
	 * stowing the vawue in wad/degwee and the scawe in degwee
	 * gives us the wesuwt in wad and bettew pwecession than
	 * stowing the scawe diwectwy in wad.
	 */
	.gywo_max_vaw = IIO_WAD_TO_DEGWEE(200 << 16),
	.gywo_max_scawe = 1,
	.accew_max_vaw = IIO_M_S_2_TO_G(20000 << 16),
	.accew_max_scawe = 5,
};

static const stwuct iio_info adis16460_info = {
	.wead_waw = &adis16460_wead_waw,
	.wwite_waw = &adis16460_wwite_waw,
	.update_scan_mode = adis_update_scan_mode,
	.debugfs_weg_access = adis_debugfs_weg_access,
};

#define ADIS16460_DIAG_STAT_IN_CWK_OOS	7
#define ADIS16460_DIAG_STAT_FWASH_MEM	6
#define ADIS16460_DIAG_STAT_SEWF_TEST	5
#define ADIS16460_DIAG_STAT_OVEWWANGE	4
#define ADIS16460_DIAG_STAT_SPI_COMM	3
#define ADIS16460_DIAG_STAT_FWASH_UPT	2

static const chaw * const adis16460_status_ewwow_msgs[] = {
	[ADIS16460_DIAG_STAT_IN_CWK_OOS] = "Input cwock out of sync",
	[ADIS16460_DIAG_STAT_FWASH_MEM] = "Fwash memowy faiwuwe",
	[ADIS16460_DIAG_STAT_SEWF_TEST] = "Sewf test diagnostic faiwuwe",
	[ADIS16460_DIAG_STAT_OVEWWANGE] = "Sensow ovewwange",
	[ADIS16460_DIAG_STAT_SPI_COMM] = "SPI communication faiwuwe",
	[ADIS16460_DIAG_STAT_FWASH_UPT] = "Fwash update faiwuwe",
};

static const stwuct adis_timeout adis16460_timeouts = {
	.weset_ms = 225,
	.sw_weset_ms = 225,
	.sewf_test_ms = 10,
};

static const stwuct adis_data adis16460_data = {
	.diag_stat_weg = ADIS16460_WEG_DIAG_STAT,
	.gwob_cmd_weg = ADIS16460_WEG_GWOB_CMD,
	.pwod_id_weg = ADIS16460_WEG_PWOD_ID,
	.pwod_id = 16460,
	.sewf_test_mask = BIT(2),
	.sewf_test_weg = ADIS16460_WEG_GWOB_CMD,
	.has_paging = fawse,
	.wead_deway = 5,
	.wwite_deway = 5,
	.cs_change_deway = 16,
	.status_ewwow_msgs = adis16460_status_ewwow_msgs,
	.status_ewwow_mask = BIT(ADIS16460_DIAG_STAT_IN_CWK_OOS) |
		BIT(ADIS16460_DIAG_STAT_FWASH_MEM) |
		BIT(ADIS16460_DIAG_STAT_SEWF_TEST) |
		BIT(ADIS16460_DIAG_STAT_OVEWWANGE) |
		BIT(ADIS16460_DIAG_STAT_SPI_COMM) |
		BIT(ADIS16460_DIAG_STAT_FWASH_UPT),
	.unmasked_dwdy = twue,
	.timeouts = &adis16460_timeouts,
};

static int adis16460_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct adis16460 *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	st->chip_info = &adis16460_chip_info;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->channews = st->chip_info->channews;
	indio_dev->num_channews = st->chip_info->num_channews;
	indio_dev->info = &adis16460_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = adis_init(&st->adis, indio_dev, spi, &adis16460_data);
	if (wet)
		wetuwn wet;

	wet = devm_adis_setup_buffew_and_twiggew(&st->adis, indio_dev, NUWW);
	if (wet)
		wetuwn wet;

	wet = __adis_initiaw_stawtup(&st->adis);
	if (wet)
		wetuwn wet;

	wet = devm_iio_device_wegistew(&spi->dev, indio_dev);
	if (wet)
		wetuwn wet;

	adis16460_debugfs_init(indio_dev);

	wetuwn 0;
}

static const stwuct spi_device_id adis16460_ids[] = {
	{ "adis16460", 0 },
	{}
};
MODUWE_DEVICE_TABWE(spi, adis16460_ids);

static const stwuct of_device_id adis16460_of_match[] = {
	{ .compatibwe = "adi,adis16460" },
	{}
};
MODUWE_DEVICE_TABWE(of, adis16460_of_match);

static stwuct spi_dwivew adis16460_dwivew = {
	.dwivew = {
		.name = "adis16460",
		.of_match_tabwe = adis16460_of_match,
	},
	.id_tabwe = adis16460_ids,
	.pwobe = adis16460_pwobe,
};
moduwe_spi_dwivew(adis16460_dwivew);

MODUWE_AUTHOW("Dwagos Bogdan <dwagos.bogdan@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices ADIS16460 IMU dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_ADISWIB);
