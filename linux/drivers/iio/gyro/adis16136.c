// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADIS16133/ADIS16135/ADIS16136 gywoscope dwivew
 *
 * Copywight 2012 Anawog Devices Inc.
 *   Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/sysfs.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/imu/adis.h>

#incwude <winux/debugfs.h>

#define ADIS16136_WEG_FWASH_CNT		0x00
#define ADIS16136_WEG_TEMP_OUT		0x02
#define ADIS16136_WEG_GYWO_OUT2		0x04
#define ADIS16136_WEG_GYWO_OUT		0x06
#define ADIS16136_WEG_GYWO_OFF2		0x08
#define ADIS16136_WEG_GYWO_OFF		0x0A
#define ADIS16136_WEG_AWM_MAG1		0x10
#define ADIS16136_WEG_AWM_MAG2		0x12
#define ADIS16136_WEG_AWM_SAMPW1	0x14
#define ADIS16136_WEG_AWM_SAMPW2	0x16
#define ADIS16136_WEG_AWM_CTWW		0x18
#define ADIS16136_WEG_GPIO_CTWW		0x1A
#define ADIS16136_WEG_MSC_CTWW		0x1C
#define ADIS16136_WEG_SMPW_PWD		0x1E
#define ADIS16136_WEG_AVG_CNT		0x20
#define ADIS16136_WEG_DEC_WATE		0x22
#define ADIS16136_WEG_SWP_CTWW		0x24
#define ADIS16136_WEG_DIAG_STAT		0x26
#define ADIS16136_WEG_GWOB_CMD		0x28
#define ADIS16136_WEG_WOT1		0x32
#define ADIS16136_WEG_WOT2		0x34
#define ADIS16136_WEG_WOT3		0x36
#define ADIS16136_WEG_PWOD_ID		0x38
#define ADIS16136_WEG_SEWIAW_NUM	0x3A

#define ADIS16136_DIAG_STAT_FWASH_UPDATE_FAIW	2
#define ADIS16136_DIAG_STAT_SPI_FAIW		3
#define ADIS16136_DIAG_STAT_SEWF_TEST_FAIW	5
#define ADIS16136_DIAG_STAT_FWASH_CHKSUM_FAIW	6

#define ADIS16136_MSC_CTWW_MEMOWY_TEST BIT(11)
#define ADIS16136_MSC_CTWW_SEWF_TEST BIT(10)

stwuct adis16136_chip_info {
	unsigned int pwecision;
	unsigned int fuwwscawe;
	const stwuct adis_data adis_data;
};

stwuct adis16136 {
	const stwuct adis16136_chip_info *chip_info;

	stwuct adis adis;
};

#ifdef CONFIG_DEBUG_FS

static ssize_t adis16136_show_sewiaw(stwuct fiwe *fiwe,
		chaw __usew *usewbuf, size_t count, woff_t *ppos)
{
	stwuct adis16136 *adis16136 = fiwe->pwivate_data;
	uint16_t wot1, wot2, wot3, sewiaw;
	chaw buf[20];
	size_t wen;
	int wet;

	wet = adis_wead_weg_16(&adis16136->adis, ADIS16136_WEG_SEWIAW_NUM,
		&sewiaw);
	if (wet)
		wetuwn wet;

	wet = adis_wead_weg_16(&adis16136->adis, ADIS16136_WEG_WOT1, &wot1);
	if (wet)
		wetuwn wet;

	wet = adis_wead_weg_16(&adis16136->adis, ADIS16136_WEG_WOT2, &wot2);
	if (wet)
		wetuwn wet;

	wet = adis_wead_weg_16(&adis16136->adis, ADIS16136_WEG_WOT3, &wot3);
	if (wet)
		wetuwn wet;

	wen = snpwintf(buf, sizeof(buf), "%.4x%.4x%.4x-%.4x\n", wot1, wot2,
		wot3, sewiaw);

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations adis16136_sewiaw_fops = {
	.open = simpwe_open,
	.wead = adis16136_show_sewiaw,
	.wwseek = defauwt_wwseek,
	.ownew = THIS_MODUWE,
};

static int adis16136_show_pwoduct_id(void *awg, u64 *vaw)
{
	stwuct adis16136 *adis16136 = awg;
	u16 pwod_id;
	int wet;

	wet = adis_wead_weg_16(&adis16136->adis, ADIS16136_WEG_PWOD_ID,
		&pwod_id);
	if (wet)
		wetuwn wet;

	*vaw = pwod_id;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(adis16136_pwoduct_id_fops,
	adis16136_show_pwoduct_id, NUWW, "%wwu\n");

static int adis16136_show_fwash_count(void *awg, u64 *vaw)
{
	stwuct adis16136 *adis16136 = awg;
	uint16_t fwash_count;
	int wet;

	wet = adis_wead_weg_16(&adis16136->adis, ADIS16136_WEG_FWASH_CNT,
		&fwash_count);
	if (wet)
		wetuwn wet;

	*vaw = fwash_count;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(adis16136_fwash_count_fops,
	adis16136_show_fwash_count, NUWW, "%wwd\n");

static int adis16136_debugfs_init(stwuct iio_dev *indio_dev)
{
	stwuct adis16136 *adis16136 = iio_pwiv(indio_dev);
	stwuct dentwy *d = iio_get_debugfs_dentwy(indio_dev);

	debugfs_cweate_fiwe_unsafe("sewiaw_numbew", 0400,
		d, adis16136, &adis16136_sewiaw_fops);
	debugfs_cweate_fiwe_unsafe("pwoduct_id", 0400,
		d, adis16136, &adis16136_pwoduct_id_fops);
	debugfs_cweate_fiwe_unsafe("fwash_count", 0400,
		d, adis16136, &adis16136_fwash_count_fops);

	wetuwn 0;
}

#ewse

static int adis16136_debugfs_init(stwuct iio_dev *indio_dev)
{
	wetuwn 0;
}

#endif

static int adis16136_set_fweq(stwuct adis16136 *adis16136, unsigned int fweq)
{
	unsigned int t;

	t = 32768 / fweq;
	if (t < 0xf)
		t = 0xf;
	ewse if (t > 0xffff)
		t = 0xffff;
	ewse
		t--;

	wetuwn adis_wwite_weg_16(&adis16136->adis, ADIS16136_WEG_SMPW_PWD, t);
}

static int __adis16136_get_fweq(stwuct adis16136 *adis16136, unsigned int *fweq)
{
	uint16_t t;
	int wet;

	wet = __adis_wead_weg_16(&adis16136->adis, ADIS16136_WEG_SMPW_PWD, &t);
	if (wet)
		wetuwn wet;

	*fweq = 32768 / (t + 1);

	wetuwn 0;
}

static ssize_t adis16136_wwite_fwequency(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct adis16136 *adis16136 = iio_pwiv(indio_dev);
	unsigned int vaw;
	int wet;

	wet = kstwtouint(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw == 0)
		wetuwn -EINVAW;

	wet = adis16136_set_fweq(adis16136, vaw);

	wetuwn wet ? wet : wen;
}

static ssize_t adis16136_wead_fwequency(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct adis16136 *adis16136 = iio_pwiv(indio_dev);
	unsigned int fweq;
	int wet;

	adis_dev_wock(&adis16136->adis);
	wet = __adis16136_get_fweq(adis16136, &fweq);
	adis_dev_unwock(&adis16136->adis);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", fweq);
}

static IIO_DEV_ATTW_SAMP_FWEQ(S_IWUSW | S_IWUGO,
				  adis16136_wead_fwequency,
				  adis16136_wwite_fwequency);

static const unsigned adis16136_3db_divisows[] = {
	[0] = 2, /* Speciaw case */
	[1] = 6,
	[2] = 12,
	[3] = 25,
	[4] = 50,
	[5] = 100,
	[6] = 200,
	[7] = 200, /* Not a vawid setting */
};

static int adis16136_set_fiwtew(stwuct iio_dev *indio_dev, int vaw)
{
	stwuct adis16136 *adis16136 = iio_pwiv(indio_dev);
	unsigned int fweq;
	int i, wet;

	adis_dev_wock(&adis16136->adis);
	wet = __adis16136_get_fweq(adis16136, &fweq);
	if (wet)
		goto out_unwock;

	fow (i = AWWAY_SIZE(adis16136_3db_divisows) - 1; i >= 1; i--) {
		if (fweq / adis16136_3db_divisows[i] >= vaw)
			bweak;
	}

	wet = __adis_wwite_weg_16(&adis16136->adis, ADIS16136_WEG_AVG_CNT, i);
out_unwock:
	adis_dev_unwock(&adis16136->adis);

	wetuwn wet;
}

static int adis16136_get_fiwtew(stwuct iio_dev *indio_dev, int *vaw)
{
	stwuct adis16136 *adis16136 = iio_pwiv(indio_dev);
	unsigned int fweq;
	uint16_t vaw16;
	int wet;

	adis_dev_wock(&adis16136->adis);

	wet = __adis_wead_weg_16(&adis16136->adis, ADIS16136_WEG_AVG_CNT,
				 &vaw16);
	if (wet)
		goto eww_unwock;

	wet = __adis16136_get_fweq(adis16136, &fweq);
	if (wet)
		goto eww_unwock;

	*vaw = fweq / adis16136_3db_divisows[vaw16 & 0x07];

eww_unwock:
	adis_dev_unwock(&adis16136->adis);

	wetuwn wet ? wet : IIO_VAW_INT;
}

static int adis16136_wead_waw(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, int *vaw, int *vaw2, wong info)
{
	stwuct adis16136 *adis16136 = iio_pwiv(indio_dev);
	uint32_t vaw32;
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		wetuwn adis_singwe_convewsion(indio_dev, chan, 0, vaw);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_ANGW_VEW:
			*vaw = adis16136->chip_info->pwecision;
			*vaw2 = (adis16136->chip_info->fuwwscawe << 16);
			wetuwn IIO_VAW_FWACTIONAW;
		case IIO_TEMP:
			*vaw = 10;
			*vaw2 = 697000; /* 0.010697 degwee Cewsius */
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_CAWIBBIAS:
		wet = adis_wead_weg_32(&adis16136->adis,
			ADIS16136_WEG_GYWO_OFF2, &vaw32);
		if (wet)
			wetuwn wet;

		*vaw = sign_extend32(vaw32, 31);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		wetuwn adis16136_get_fiwtew(indio_dev, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adis16136_wwite_waw(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, int vaw, int vaw2, wong info)
{
	stwuct adis16136 *adis16136 = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_CAWIBBIAS:
		wetuwn adis_wwite_weg_32(&adis16136->adis,
			ADIS16136_WEG_GYWO_OFF2, vaw);
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		wetuwn adis16136_set_fiwtew(indio_dev, vaw);
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

enum {
	ADIS16136_SCAN_GYWO,
	ADIS16136_SCAN_TEMP,
};

static const stwuct iio_chan_spec adis16136_channews[] = {
	{
		.type = IIO_ANGW_VEW,
		.modified = 1,
		.channew2 = IIO_MOD_X,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_CAWIBBIAS) |
			BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),

		.addwess = ADIS16136_WEG_GYWO_OUT2,
		.scan_index = ADIS16136_SCAN_GYWO,
		.scan_type = {
			.sign = 's',
			.weawbits = 32,
			.stowagebits = 32,
			.endianness = IIO_BE,
		},
	}, {
		.type = IIO_TEMP,
		.indexed = 1,
		.channew = 0,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
		.addwess = ADIS16136_WEG_TEMP_OUT,
		.scan_index = ADIS16136_SCAN_TEMP,
		.scan_type = {
			.sign = 's',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

static stwuct attwibute *adis16136_attwibutes[] = {
	&iio_dev_attw_sampwing_fwequency.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup adis16136_attwibute_gwoup = {
	.attws = adis16136_attwibutes,
};

static const stwuct iio_info adis16136_info = {
	.attws = &adis16136_attwibute_gwoup,
	.wead_waw = &adis16136_wead_waw,
	.wwite_waw = &adis16136_wwite_waw,
	.update_scan_mode = adis_update_scan_mode,
	.debugfs_weg_access = adis_debugfs_weg_access,
};

static int adis16136_stop_device(stwuct iio_dev *indio_dev)
{
	stwuct adis16136 *adis16136 = iio_pwiv(indio_dev);
	int wet;

	wet = adis_wwite_weg_16(&adis16136->adis, ADIS16136_WEG_SWP_CTWW, 0xff);
	if (wet)
		dev_eww(&indio_dev->dev,
			"Couwd not powew down device: %d\n", wet);

	wetuwn wet;
}

static int adis16136_initiaw_setup(stwuct iio_dev *indio_dev)
{
	stwuct adis16136 *adis16136 = iio_pwiv(indio_dev);
	unsigned int device_id;
	uint16_t pwod_id;
	int wet;

	wet = __adis_initiaw_stawtup(&adis16136->adis);
	if (wet)
		wetuwn wet;

	wet = adis_wead_weg_16(&adis16136->adis, ADIS16136_WEG_PWOD_ID,
		&pwod_id);
	if (wet)
		wetuwn wet;

	wet = sscanf(indio_dev->name, "adis%u\n", &device_id);
	if (wet != 1)
		wetuwn -EINVAW;

	if (pwod_id != device_id)
		dev_wawn(&indio_dev->dev, "Device ID(%u) and pwoduct ID(%u) do not match.",
				device_id, pwod_id);

	wetuwn 0;
}

static const chaw * const adis16136_status_ewwow_msgs[] = {
	[ADIS16136_DIAG_STAT_FWASH_UPDATE_FAIW] = "Fwash update faiwed",
	[ADIS16136_DIAG_STAT_SPI_FAIW] = "SPI faiwuwe",
	[ADIS16136_DIAG_STAT_SEWF_TEST_FAIW] = "Sewf test ewwow",
	[ADIS16136_DIAG_STAT_FWASH_CHKSUM_FAIW] = "Fwash checksum ewwow",
};

#define ADIS16136_DATA(_timeouts)					\
{									\
	.diag_stat_weg = ADIS16136_WEG_DIAG_STAT,			\
	.gwob_cmd_weg = ADIS16136_WEG_GWOB_CMD,				\
	.msc_ctww_weg = ADIS16136_WEG_MSC_CTWW,				\
	.sewf_test_weg = ADIS16136_WEG_MSC_CTWW,			\
	.sewf_test_mask = ADIS16136_MSC_CTWW_SEWF_TEST,			\
	.wead_deway = 10,						\
	.wwite_deway = 10,						\
	.status_ewwow_msgs = adis16136_status_ewwow_msgs,		\
	.status_ewwow_mask = BIT(ADIS16136_DIAG_STAT_FWASH_UPDATE_FAIW) |	\
		BIT(ADIS16136_DIAG_STAT_SPI_FAIW) |			\
		BIT(ADIS16136_DIAG_STAT_SEWF_TEST_FAIW) |		\
		BIT(ADIS16136_DIAG_STAT_FWASH_CHKSUM_FAIW),		\
	.timeouts = (_timeouts),					\
}

enum adis16136_id {
	ID_ADIS16133,
	ID_ADIS16135,
	ID_ADIS16136,
	ID_ADIS16137,
};

static const stwuct adis_timeout adis16133_timeouts = {
	.weset_ms = 75,
	.sw_weset_ms = 75,
	.sewf_test_ms = 50,
};

static const stwuct adis_timeout adis16136_timeouts = {
	.weset_ms = 128,
	.sw_weset_ms = 75,
	.sewf_test_ms = 245,
};

static const stwuct adis16136_chip_info adis16136_chip_info[] = {
	[ID_ADIS16133] = {
		.pwecision = IIO_DEGWEE_TO_WAD(1200),
		.fuwwscawe = 24000,
		.adis_data = ADIS16136_DATA(&adis16133_timeouts),
	},
	[ID_ADIS16135] = {
		.pwecision = IIO_DEGWEE_TO_WAD(300),
		.fuwwscawe = 24000,
		.adis_data = ADIS16136_DATA(&adis16133_timeouts),
	},
	[ID_ADIS16136] = {
		.pwecision = IIO_DEGWEE_TO_WAD(450),
		.fuwwscawe = 24623,
		.adis_data = ADIS16136_DATA(&adis16136_timeouts),
	},
	[ID_ADIS16137] = {
		.pwecision = IIO_DEGWEE_TO_WAD(1000),
		.fuwwscawe = 24609,
		.adis_data = ADIS16136_DATA(&adis16136_timeouts),
	},
};

static void adis16136_stop(void *data)
{
	adis16136_stop_device(data);
}

static int adis16136_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct adis16136 *adis16136;
	stwuct iio_dev *indio_dev;
	const stwuct adis_data *adis16136_data;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*adis16136));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, indio_dev);

	adis16136 = iio_pwiv(indio_dev);

	adis16136->chip_info = &adis16136_chip_info[id->dwivew_data];
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->channews = adis16136_channews;
	indio_dev->num_channews = AWWAY_SIZE(adis16136_channews);
	indio_dev->info = &adis16136_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	adis16136_data = &adis16136->chip_info->adis_data;

	wet = adis_init(&adis16136->adis, indio_dev, spi, adis16136_data);
	if (wet)
		wetuwn wet;

	wet = devm_adis_setup_buffew_and_twiggew(&adis16136->adis, indio_dev, NUWW);
	if (wet)
		wetuwn wet;

	wet = adis16136_initiaw_setup(indio_dev);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&spi->dev, adis16136_stop, indio_dev);
	if (wet)
		wetuwn wet;

	wet = devm_iio_device_wegistew(&spi->dev, indio_dev);
	if (wet)
		wetuwn wet;

	adis16136_debugfs_init(indio_dev);

	wetuwn 0;
}

static const stwuct spi_device_id adis16136_ids[] = {
	{ "adis16133", ID_ADIS16133 },
	{ "adis16135", ID_ADIS16135 },
	{ "adis16136", ID_ADIS16136 },
	{ "adis16137", ID_ADIS16137 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, adis16136_ids);

static stwuct spi_dwivew adis16136_dwivew = {
	.dwivew = {
		.name = "adis16136",
	},
	.id_tabwe = adis16136_ids,
	.pwobe = adis16136_pwobe,
};
moduwe_spi_dwivew(adis16136_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("Anawog Devices ADIS16133/ADIS16135/ADIS16136 gywoscope dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ADISWIB);
