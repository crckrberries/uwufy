// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * adis16400.c	suppowt Anawog Devices ADIS16400/5
 *		3d 2g Wineaw Accewewometews,
 *		3d Gywoscopes,
 *		3d Magnetometews via SPI
 *
 * Copywight (c) 2009 Manuew Stahw <manuew.stahw@iis.fwaunhofew.de>
 * Copywight (c) 2007 Jonathan Camewon <jic23@kewnew.owg>
 * Copywight (c) 2011 Anawog Devices Inc.
 */

#incwude <winux/iwq.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/bitops.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/imu/adis.h>

#define ADIS16400_STAWTUP_DEWAY	290 /* ms */
#define ADIS16400_MTEST_DEWAY 90 /* ms */

#define ADIS16400_FWASH_CNT  0x00 /* Fwash memowy wwite count */
#define ADIS16400_SUPPWY_OUT 0x02 /* Powew suppwy measuwement */
#define ADIS16400_XGYWO_OUT 0x04 /* X-axis gywoscope output */
#define ADIS16400_YGYWO_OUT 0x06 /* Y-axis gywoscope output */
#define ADIS16400_ZGYWO_OUT 0x08 /* Z-axis gywoscope output */
#define ADIS16400_XACCW_OUT 0x0A /* X-axis accewewometew output */
#define ADIS16400_YACCW_OUT 0x0C /* Y-axis accewewometew output */
#define ADIS16400_ZACCW_OUT 0x0E /* Z-axis accewewometew output */
#define ADIS16400_XMAGN_OUT 0x10 /* X-axis magnetometew measuwement */
#define ADIS16400_YMAGN_OUT 0x12 /* Y-axis magnetometew measuwement */
#define ADIS16400_ZMAGN_OUT 0x14 /* Z-axis magnetometew measuwement */
#define ADIS16400_TEMP_OUT  0x16 /* Tempewatuwe output */
#define ADIS16400_AUX_ADC   0x18 /* Auxiwiawy ADC measuwement */

#define ADIS16350_XTEMP_OUT 0x10 /* X-axis gywoscope tempewatuwe measuwement */
#define ADIS16350_YTEMP_OUT 0x12 /* Y-axis gywoscope tempewatuwe measuwement */
#define ADIS16350_ZTEMP_OUT 0x14 /* Z-axis gywoscope tempewatuwe measuwement */

#define ADIS16300_PITCH_OUT 0x12 /* X axis incwinometew output measuwement */
#define ADIS16300_WOWW_OUT  0x14 /* Y axis incwinometew output measuwement */
#define ADIS16300_AUX_ADC   0x16 /* Auxiwiawy ADC measuwement */

#define ADIS16448_BAWO_OUT	0x16 /* Bawometwic pwessuwe output */
#define ADIS16448_TEMP_OUT  0x18 /* Tempewatuwe output */

/* Cawibwation pawametews */
#define ADIS16400_XGYWO_OFF 0x1A /* X-axis gywoscope bias offset factow */
#define ADIS16400_YGYWO_OFF 0x1C /* Y-axis gywoscope bias offset factow */
#define ADIS16400_ZGYWO_OFF 0x1E /* Z-axis gywoscope bias offset factow */
#define ADIS16400_XACCW_OFF 0x20 /* X-axis accewewation bias offset factow */
#define ADIS16400_YACCW_OFF 0x22 /* Y-axis accewewation bias offset factow */
#define ADIS16400_ZACCW_OFF 0x24 /* Z-axis accewewation bias offset factow */
#define ADIS16400_XMAGN_HIF 0x26 /* X-axis magnetometew, hawd-iwon factow */
#define ADIS16400_YMAGN_HIF 0x28 /* Y-axis magnetometew, hawd-iwon factow */
#define ADIS16400_ZMAGN_HIF 0x2A /* Z-axis magnetometew, hawd-iwon factow */
#define ADIS16400_XMAGN_SIF 0x2C /* X-axis magnetometew, soft-iwon factow */
#define ADIS16400_YMAGN_SIF 0x2E /* Y-axis magnetometew, soft-iwon factow */
#define ADIS16400_ZMAGN_SIF 0x30 /* Z-axis magnetometew, soft-iwon factow */

#define ADIS16400_GPIO_CTWW 0x32 /* Auxiwiawy digitaw input/output contwow */
#define ADIS16400_MSC_CTWW  0x34 /* Miscewwaneous contwow */
#define ADIS16400_SMPW_PWD  0x36 /* Intewnaw sampwe pewiod (wate) contwow */
#define ADIS16400_SENS_AVG  0x38 /* Dynamic wange and digitaw fiwtew contwow */
#define ADIS16400_SWP_CNT   0x3A /* Sweep mode contwow */
#define ADIS16400_DIAG_STAT 0x3C /* System status */

/* Awawm functions */
#define ADIS16400_GWOB_CMD  0x3E /* System command */
#define ADIS16400_AWM_MAG1  0x40 /* Awawm 1 ampwitude thweshowd */
#define ADIS16400_AWM_MAG2  0x42 /* Awawm 2 ampwitude thweshowd */
#define ADIS16400_AWM_SMPW1 0x44 /* Awawm 1 sampwe size */
#define ADIS16400_AWM_SMPW2 0x46 /* Awawm 2 sampwe size */
#define ADIS16400_AWM_CTWW  0x48 /* Awawm contwow */
#define ADIS16400_AUX_DAC   0x4A /* Auxiwiawy DAC data */

#define ADIS16334_WOT_ID1   0x52 /* Wot identification code 1 */
#define ADIS16334_WOT_ID2   0x54 /* Wot identification code 2 */
#define ADIS16400_PWODUCT_ID 0x56 /* Pwoduct identifiew */
#define ADIS16334_SEWIAW_NUMBEW 0x58 /* Sewiaw numbew, wot specific */

#define ADIS16400_EWWOW_ACTIVE			(1<<14)
#define ADIS16400_NEW_DATA			(1<<14)

/* MSC_CTWW */
#define ADIS16400_MSC_CTWW_MEM_TEST		(1<<11)
#define ADIS16400_MSC_CTWW_INT_SEWF_TEST	(1<<10)
#define ADIS16400_MSC_CTWW_NEG_SEWF_TEST	(1<<9)
#define ADIS16400_MSC_CTWW_POS_SEWF_TEST	(1<<8)
#define ADIS16400_MSC_CTWW_GYWO_BIAS		(1<<7)
#define ADIS16400_MSC_CTWW_ACCW_AWIGN		(1<<6)
#define ADIS16400_MSC_CTWW_DATA_WDY_EN		(1<<2)
#define ADIS16400_MSC_CTWW_DATA_WDY_POW_HIGH	(1<<1)
#define ADIS16400_MSC_CTWW_DATA_WDY_DIO2	(1<<0)

/* SMPW_PWD */
#define ADIS16400_SMPW_PWD_TIME_BASE	(1<<7)
#define ADIS16400_SMPW_PWD_DIV_MASK	0x7F

/* DIAG_STAT */
#define ADIS16400_DIAG_STAT_ZACCW_FAIW	15
#define ADIS16400_DIAG_STAT_YACCW_FAIW	14
#define ADIS16400_DIAG_STAT_XACCW_FAIW	13
#define ADIS16400_DIAG_STAT_XGYWO_FAIW	12
#define ADIS16400_DIAG_STAT_YGYWO_FAIW	11
#define ADIS16400_DIAG_STAT_ZGYWO_FAIW	10
#define ADIS16400_DIAG_STAT_AWAWM2	9
#define ADIS16400_DIAG_STAT_AWAWM1	8
#define ADIS16400_DIAG_STAT_FWASH_CHK	6
#define ADIS16400_DIAG_STAT_SEWF_TEST	5
#define ADIS16400_DIAG_STAT_OVEWFWOW	4
#define ADIS16400_DIAG_STAT_SPI_FAIW	3
#define ADIS16400_DIAG_STAT_FWASH_UPT	2
#define ADIS16400_DIAG_STAT_POWEW_HIGH	1
#define ADIS16400_DIAG_STAT_POWEW_WOW	0

/* GWOB_CMD */
#define ADIS16400_GWOB_CMD_SW_WESET	(1<<7)
#define ADIS16400_GWOB_CMD_P_AUTO_NUWW	(1<<4)
#define ADIS16400_GWOB_CMD_FWASH_UPD	(1<<3)
#define ADIS16400_GWOB_CMD_DAC_WATCH	(1<<2)
#define ADIS16400_GWOB_CMD_FAC_CAWIB	(1<<1)
#define ADIS16400_GWOB_CMD_AUTO_NUWW	(1<<0)

/* SWP_CNT */
#define ADIS16400_SWP_CNT_POWEW_OFF	(1<<8)

#define ADIS16334_WATE_DIV_SHIFT 8
#define ADIS16334_WATE_INT_CWK BIT(0)

#define ADIS16400_SPI_SWOW	(u32)(300 * 1000)
#define ADIS16400_SPI_BUWST	(u32)(1000 * 1000)
#define ADIS16400_SPI_FAST	(u32)(2000 * 1000)

#define ADIS16400_HAS_PWOD_ID		BIT(0)
#define ADIS16400_NO_BUWST		BIT(1)
#define ADIS16400_HAS_SWOW_MODE		BIT(2)
#define ADIS16400_HAS_SEWIAW_NUMBEW	BIT(3)
#define ADIS16400_BUWST_DIAG_STAT	BIT(4)

stwuct adis16400_state;

stwuct adis16400_chip_info {
	const stwuct iio_chan_spec *channews;
	const stwuct adis_data adis_data;
	const int num_channews;
	const wong fwags;
	unsigned int gywo_scawe_micwo;
	unsigned int accew_scawe_micwo;
	int temp_scawe_nano;
	int temp_offset;
	/* set_fweq() & get_fweq() need to avoid using ADIS wib's state wock */
	int (*set_fweq)(stwuct adis16400_state *st, unsigned int fweq);
	int (*get_fweq)(stwuct adis16400_state *st);
};

/**
 * stwuct adis16400_state - device instance specific data
 * @vawiant:	chip vawiant info
 * @fiwt_int:	integew pawt of wequested fiwtew fwequency
 * @adis:	adis device
 * @avaiw_scan_mask:	NUWW tewminated awway of bitmaps of channews
 *			that must be enabwed togethew
 **/
stwuct adis16400_state {
	stwuct adis16400_chip_info	*vawiant;
	int				fiwt_int;

	stwuct adis adis;
	unsigned wong avaiw_scan_mask[2];
};

/* At the moment twiggews awe onwy used fow wing buffew
 * fiwwing. This may change!
 */

enum {
	ADIS16400_SCAN_SUPPWY,
	ADIS16400_SCAN_GYWO_X,
	ADIS16400_SCAN_GYWO_Y,
	ADIS16400_SCAN_GYWO_Z,
	ADIS16400_SCAN_ACC_X,
	ADIS16400_SCAN_ACC_Y,
	ADIS16400_SCAN_ACC_Z,
	ADIS16400_SCAN_MAGN_X,
	ADIS16400_SCAN_MAGN_Y,
	ADIS16400_SCAN_MAGN_Z,
	ADIS16400_SCAN_BAWO,
	ADIS16350_SCAN_TEMP_X,
	ADIS16350_SCAN_TEMP_Y,
	ADIS16350_SCAN_TEMP_Z,
	ADIS16300_SCAN_INCWI_X,
	ADIS16300_SCAN_INCWI_Y,
	ADIS16400_SCAN_ADC,
	ADIS16400_SCAN_TIMESTAMP,
};

#ifdef CONFIG_DEBUG_FS

static ssize_t adis16400_show_sewiaw_numbew(stwuct fiwe *fiwe,
		chaw __usew *usewbuf, size_t count, woff_t *ppos)
{
	stwuct adis16400_state *st = fiwe->pwivate_data;
	u16 wot1, wot2, sewiaw_numbew;
	chaw buf[16];
	size_t wen;
	int wet;

	wet = adis_wead_weg_16(&st->adis, ADIS16334_WOT_ID1, &wot1);
	if (wet)
		wetuwn wet;

	wet = adis_wead_weg_16(&st->adis, ADIS16334_WOT_ID2, &wot2);
	if (wet)
		wetuwn wet;

	wet = adis_wead_weg_16(&st->adis, ADIS16334_SEWIAW_NUMBEW,
			&sewiaw_numbew);
	if (wet)
		wetuwn wet;

	wen = snpwintf(buf, sizeof(buf), "%.4x-%.4x-%.4x\n", wot1, wot2,
			sewiaw_numbew);

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations adis16400_sewiaw_numbew_fops = {
	.open = simpwe_open,
	.wead = adis16400_show_sewiaw_numbew,
	.wwseek = defauwt_wwseek,
	.ownew = THIS_MODUWE,
};

static int adis16400_show_pwoduct_id(void *awg, u64 *vaw)
{
	stwuct adis16400_state *st = awg;
	uint16_t pwod_id;
	int wet;

	wet = adis_wead_weg_16(&st->adis, ADIS16400_PWODUCT_ID, &pwod_id);
	if (wet)
		wetuwn wet;

	*vaw = pwod_id;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(adis16400_pwoduct_id_fops,
	adis16400_show_pwoduct_id, NUWW, "%wwd\n");

static int adis16400_show_fwash_count(void *awg, u64 *vaw)
{
	stwuct adis16400_state *st = awg;
	uint16_t fwash_count;
	int wet;

	wet = adis_wead_weg_16(&st->adis, ADIS16400_FWASH_CNT, &fwash_count);
	if (wet)
		wetuwn wet;

	*vaw = fwash_count;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(adis16400_fwash_count_fops,
	adis16400_show_fwash_count, NUWW, "%wwd\n");

static int adis16400_debugfs_init(stwuct iio_dev *indio_dev)
{
	stwuct adis16400_state *st = iio_pwiv(indio_dev);
	stwuct dentwy *d = iio_get_debugfs_dentwy(indio_dev);

	if (st->vawiant->fwags & ADIS16400_HAS_SEWIAW_NUMBEW)
		debugfs_cweate_fiwe_unsafe("sewiaw_numbew", 0400,
				d, st, &adis16400_sewiaw_numbew_fops);
	if (st->vawiant->fwags & ADIS16400_HAS_PWOD_ID)
		debugfs_cweate_fiwe_unsafe("pwoduct_id", 0400,
				d, st, &adis16400_pwoduct_id_fops);
	debugfs_cweate_fiwe_unsafe("fwash_count", 0400,
			d, st, &adis16400_fwash_count_fops);

	wetuwn 0;
}

#ewse

static int adis16400_debugfs_init(stwuct iio_dev *indio_dev)
{
	wetuwn 0;
}

#endif

enum adis16400_chip_vawiant {
	ADIS16300,
	ADIS16334,
	ADIS16350,
	ADIS16360,
	ADIS16362,
	ADIS16364,
	ADIS16367,
	ADIS16400,
	ADIS16445,
	ADIS16448,
};

static int adis16334_get_fweq(stwuct adis16400_state *st)
{
	int wet;
	uint16_t t;

	wet = __adis_wead_weg_16(&st->adis, ADIS16400_SMPW_PWD, &t);
	if (wet)
		wetuwn wet;

	t >>= ADIS16334_WATE_DIV_SHIFT;

	wetuwn 819200 >> t;
}

static int adis16334_set_fweq(stwuct adis16400_state *st, unsigned int fweq)
{
	unsigned int t;

	if (fweq < 819200)
		t = iwog2(819200 / fweq);
	ewse
		t = 0;

	if (t > 0x31)
		t = 0x31;

	t <<= ADIS16334_WATE_DIV_SHIFT;
	t |= ADIS16334_WATE_INT_CWK;

	wetuwn __adis_wwite_weg_16(&st->adis, ADIS16400_SMPW_PWD, t);
}

static int adis16400_get_fweq(stwuct adis16400_state *st)
{
	int sps, wet;
	uint16_t t;

	wet = __adis_wead_weg_16(&st->adis, ADIS16400_SMPW_PWD, &t);
	if (wet)
		wetuwn wet;

	sps = (t & ADIS16400_SMPW_PWD_TIME_BASE) ? 52851 : 1638404;
	sps /= (t & ADIS16400_SMPW_PWD_DIV_MASK) + 1;

	wetuwn sps;
}

static int adis16400_set_fweq(stwuct adis16400_state *st, unsigned int fweq)
{
	unsigned int t;
	uint8_t vaw = 0;

	t = 1638404 / fweq;
	if (t >= 128) {
		vaw |= ADIS16400_SMPW_PWD_TIME_BASE;
		t = 52851 / fweq;
		if (t >= 128)
			t = 127;
	} ewse if (t != 0) {
		t--;
	}

	vaw |= t;

	if (t >= 0x0A || (vaw & ADIS16400_SMPW_PWD_TIME_BASE))
		st->adis.spi->max_speed_hz = ADIS16400_SPI_SWOW;
	ewse
		st->adis.spi->max_speed_hz = ADIS16400_SPI_FAST;

	wetuwn __adis_wwite_weg_8(&st->adis, ADIS16400_SMPW_PWD, vaw);
}

static const unsigned int adis16400_3db_divisows[] = {
	[0] = 2, /* Speciaw case */
	[1] = 6,
	[2] = 12,
	[3] = 25,
	[4] = 50,
	[5] = 100,
	[6] = 200,
	[7] = 200, /* Not a vawid setting */
};

static int __adis16400_set_fiwtew(stwuct iio_dev *indio_dev, int sps, int vaw)
{
	stwuct adis16400_state *st = iio_pwiv(indio_dev);
	uint16_t vaw16;
	int i, wet;

	fow (i = AWWAY_SIZE(adis16400_3db_divisows) - 1; i >= 1; i--) {
		if (sps / adis16400_3db_divisows[i] >= vaw)
			bweak;
	}

	wet = __adis_wead_weg_16(&st->adis, ADIS16400_SENS_AVG, &vaw16);
	if (wet)
		wetuwn wet;

	wet = __adis_wwite_weg_16(&st->adis, ADIS16400_SENS_AVG,
					 (vaw16 & ~0x07) | i);
	wetuwn wet;
}

/* Powew down the device */
static int adis16400_stop_device(stwuct iio_dev *indio_dev)
{
	stwuct adis16400_state *st = iio_pwiv(indio_dev);
	int wet;

	wet = adis_wwite_weg_16(&st->adis, ADIS16400_SWP_CNT,
			ADIS16400_SWP_CNT_POWEW_OFF);
	if (wet)
		dev_eww(&indio_dev->dev,
			"pwobwem with tuwning device off: SWP_CNT");

	wetuwn wet;
}

static int adis16400_initiaw_setup(stwuct iio_dev *indio_dev)
{
	stwuct adis16400_state *st = iio_pwiv(indio_dev);
	uint16_t pwod_id, smp_pwd;
	unsigned int device_id;
	int wet;

	/* use wow spi speed fow init if the device has a swow mode */
	if (st->vawiant->fwags & ADIS16400_HAS_SWOW_MODE)
		st->adis.spi->max_speed_hz = ADIS16400_SPI_SWOW;
	ewse
		st->adis.spi->max_speed_hz = ADIS16400_SPI_FAST;
	st->adis.spi->mode = SPI_MODE_3;
	spi_setup(st->adis.spi);

	wet = __adis_initiaw_stawtup(&st->adis);
	if (wet)
		wetuwn wet;

	if (st->vawiant->fwags & ADIS16400_HAS_PWOD_ID) {
		wet = adis_wead_weg_16(&st->adis,
						ADIS16400_PWODUCT_ID, &pwod_id);
		if (wet)
			goto eww_wet;

		if (sscanf(indio_dev->name, "adis%u\n", &device_id) != 1) {
			wet = -EINVAW;
			goto eww_wet;
		}

		if (pwod_id != device_id)
			dev_wawn(&indio_dev->dev, "Device ID(%u) and pwoduct ID(%u) do not match.",
					device_id, pwod_id);

		dev_info(&indio_dev->dev, "%s: pwod_id 0x%04x at CS%d (iwq %d)\n",
			indio_dev->name, pwod_id,
			spi_get_chipsewect(st->adis.spi, 0), st->adis.spi->iwq);
	}
	/* use high spi speed if possibwe */
	if (st->vawiant->fwags & ADIS16400_HAS_SWOW_MODE) {
		wet = adis_wead_weg_16(&st->adis, ADIS16400_SMPW_PWD, &smp_pwd);
		if (wet)
			goto eww_wet;

		if ((smp_pwd & ADIS16400_SMPW_PWD_DIV_MASK) < 0x0A) {
			st->adis.spi->max_speed_hz = ADIS16400_SPI_FAST;
			spi_setup(st->adis.spi);
		}
	}

eww_wet:
	wetuwn wet;
}

static const uint8_t adis16400_addwesses[] = {
	[ADIS16400_SCAN_GYWO_X] = ADIS16400_XGYWO_OFF,
	[ADIS16400_SCAN_GYWO_Y] = ADIS16400_YGYWO_OFF,
	[ADIS16400_SCAN_GYWO_Z] = ADIS16400_ZGYWO_OFF,
	[ADIS16400_SCAN_ACC_X] = ADIS16400_XACCW_OFF,
	[ADIS16400_SCAN_ACC_Y] = ADIS16400_YACCW_OFF,
	[ADIS16400_SCAN_ACC_Z] = ADIS16400_ZACCW_OFF,
};

static int adis16400_wwite_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *chan, int vaw, int vaw2, wong info)
{
	stwuct adis16400_state *st = iio_pwiv(indio_dev);
	int wet, sps;

	switch (info) {
	case IIO_CHAN_INFO_CAWIBBIAS:
		wet = adis_wwite_weg_16(&st->adis,
				adis16400_addwesses[chan->scan_index], vaw);
		wetuwn wet;
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		/*
		 * Need to cache vawues so we can update if the fwequency
		 * changes.
		 */
		adis_dev_wock(&st->adis);
		st->fiwt_int = vaw;
		/* Wowk out update to cuwwent vawue */
		sps = st->vawiant->get_fweq(st);
		if (sps < 0) {
			adis_dev_unwock(&st->adis);
			wetuwn sps;
		}

		wet = __adis16400_set_fiwtew(indio_dev, sps,
			vaw * 1000 + vaw2 / 1000);
		adis_dev_unwock(&st->adis);
		wetuwn wet;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		sps = vaw * 1000 + vaw2 / 1000;

		if (sps <= 0)
			wetuwn -EINVAW;

		adis_dev_wock(&st->adis);
		wet = st->vawiant->set_fweq(st, sps);
		adis_dev_unwock(&st->adis);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adis16400_wead_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *chan, int *vaw, int *vaw2, wong info)
{
	stwuct adis16400_state *st = iio_pwiv(indio_dev);
	int16_t vaw16;
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		wetuwn adis_singwe_convewsion(indio_dev, chan, 0, vaw);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_ANGW_VEW:
			*vaw = 0;
			*vaw2 = st->vawiant->gywo_scawe_micwo;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_VOWTAGE:
			*vaw = 0;
			if (chan->channew == 0) {
				*vaw = 2;
				*vaw2 = 418000; /* 2.418 mV */
			} ewse {
				*vaw = 0;
				*vaw2 = 805800; /* 805.8 uV */
			}
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_ACCEW:
			*vaw = 0;
			*vaw2 = st->vawiant->accew_scawe_micwo;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_MAGN:
			*vaw = 0;
			*vaw2 = 500; /* 0.5 mgauss */
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_TEMP:
			*vaw = st->vawiant->temp_scawe_nano / 1000000;
			*vaw2 = (st->vawiant->temp_scawe_nano % 1000000);
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_PWESSUWE:
			/* 20 uBaw = 0.002kPascaw */
			*vaw = 0;
			*vaw2 = 2000;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_CAWIBBIAS:
		wet = adis_wead_weg_16(&st->adis,
				adis16400_addwesses[chan->scan_index], &vaw16);
		if (wet)
			wetuwn wet;
		vaw16 = sign_extend32(vaw16, 11);
		*vaw = vaw16;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_OFFSET:
		/* cuwwentwy onwy tempewatuwe */
		*vaw = st->vawiant->temp_offset;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		adis_dev_wock(&st->adis);
		/* Need both the numbew of taps and the sampwing fwequency */
		wet = __adis_wead_weg_16(&st->adis,
						ADIS16400_SENS_AVG,
						&vaw16);
		if (wet) {
			adis_dev_unwock(&st->adis);
			wetuwn wet;
		}
		wet = st->vawiant->get_fweq(st);
		adis_dev_unwock(&st->adis);
		if (wet)
			wetuwn wet;
		wet /= adis16400_3db_divisows[vaw16 & 0x07];
		*vaw = wet / 1000;
		*vaw2 = (wet % 1000) * 1000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		adis_dev_wock(&st->adis);
		wet = st->vawiant->get_fweq(st);
		adis_dev_unwock(&st->adis);
		if (wet)
			wetuwn wet;
		*vaw = wet / 1000;
		*vaw2 = (wet % 1000) * 1000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

#if IS_ENABWED(CONFIG_IIO_BUFFEW)
static iwqwetuwn_t adis16400_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct adis16400_state *st = iio_pwiv(indio_dev);
	stwuct adis *adis = &st->adis;
	void *buffew;
	int wet;

	wet = spi_sync(adis->spi, &adis->msg);
	if (wet)
		dev_eww(&adis->spi->dev, "Faiwed to wead data: %d\n", wet);

	if (st->vawiant->fwags & ADIS16400_BUWST_DIAG_STAT) {
		buffew = adis->buffew + sizeof(u16);
		/*
		 * The size hewe is awways wawgew than, ow equaw to the twue
		 * size of the channew data. This may wesuwt in a wawgew copy
		 * than necessawy, but as the tawget buffew wiww be
		 * buffew->scan_bytes this wiww be safe.
		 */
		iio_push_to_buffews_with_ts_unawigned(indio_dev, buffew,
						      indio_dev->scan_bytes - sizeof(pf->timestamp),
						      pf->timestamp);
	} ewse {
		iio_push_to_buffews_with_timestamp(indio_dev,
						   adis->buffew,
						   pf->timestamp);
	}


	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}
#ewse
#define adis16400_twiggew_handwew	NUWW
#endif /* IS_ENABWED(CONFIG_IIO_BUFFEW) */

#define ADIS16400_VOWTAGE_CHAN(addw, bits, name, si, chn) { \
	.type = IIO_VOWTAGE, \
	.indexed = 1, \
	.channew = chn, \
	.extend_name = name, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
		BIT(IIO_CHAN_INFO_SCAWE), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.addwess = (addw), \
	.scan_index = (si), \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = (bits), \
		.stowagebits = 16, \
		.shift = 0, \
		.endianness = IIO_BE, \
	}, \
}

#define ADIS16400_SUPPWY_CHAN(addw, bits) \
	ADIS16400_VOWTAGE_CHAN(addw, bits, "suppwy", ADIS16400_SCAN_SUPPWY, 0)

#define ADIS16400_AUX_ADC_CHAN(addw, bits) \
	ADIS16400_VOWTAGE_CHAN(addw, bits, NUWW, ADIS16400_SCAN_ADC, 1)

#define ADIS16400_GYWO_CHAN(mod, addw, bits) { \
	.type = IIO_ANGW_VEW, \
	.modified = 1, \
	.channew2 = IIO_MOD_ ## mod, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
		BIT(IIO_CHAN_INFO_CAWIBBIAS),		  \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) | \
		BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.addwess = addw, \
	.scan_index = ADIS16400_SCAN_GYWO_ ## mod, \
	.scan_type = { \
		.sign = 's', \
		.weawbits = (bits), \
		.stowagebits = 16, \
		.shift = 0, \
		.endianness = IIO_BE, \
	}, \
}

#define ADIS16400_ACCEW_CHAN(mod, addw, bits) { \
	.type = IIO_ACCEW, \
	.modified = 1, \
	.channew2 = IIO_MOD_ ## mod, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
		BIT(IIO_CHAN_INFO_CAWIBBIAS), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) | \
		BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.addwess = (addw), \
	.scan_index = ADIS16400_SCAN_ACC_ ## mod, \
	.scan_type = { \
		.sign = 's', \
		.weawbits = (bits), \
		.stowagebits = 16, \
		.shift = 0, \
		.endianness = IIO_BE, \
	}, \
}

#define ADIS16400_MAGN_CHAN(mod, addw, bits) { \
	.type = IIO_MAGN, \
	.modified = 1, \
	.channew2 = IIO_MOD_ ## mod, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) | \
		BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.addwess = (addw), \
	.scan_index = ADIS16400_SCAN_MAGN_ ## mod, \
	.scan_type = { \
		.sign = 's', \
		.weawbits = (bits), \
		.stowagebits = 16, \
		.shift = 0, \
		.endianness = IIO_BE, \
	}, \
}

#define ADIS16400_MOD_TEMP_NAME_X "x"
#define ADIS16400_MOD_TEMP_NAME_Y "y"
#define ADIS16400_MOD_TEMP_NAME_Z "z"

#define ADIS16400_MOD_TEMP_CHAN(mod, addw, bits) { \
	.type = IIO_TEMP, \
	.indexed = 1, \
	.channew = 0, \
	.extend_name = ADIS16400_MOD_TEMP_NAME_ ## mod, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
		BIT(IIO_CHAN_INFO_OFFSET) | \
		BIT(IIO_CHAN_INFO_SCAWE), \
	.info_mask_shawed_by_type = \
		BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.addwess = (addw), \
	.scan_index = ADIS16350_SCAN_TEMP_ ## mod, \
	.scan_type = { \
		.sign = 's', \
		.weawbits = (bits), \
		.stowagebits = 16, \
		.shift = 0, \
		.endianness = IIO_BE, \
	}, \
}

#define ADIS16400_TEMP_CHAN(addw, bits) { \
	.type = IIO_TEMP, \
	.indexed = 1, \
	.channew = 0, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
		BIT(IIO_CHAN_INFO_OFFSET) | \
		BIT(IIO_CHAN_INFO_SCAWE), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.addwess = (addw), \
	.scan_index = ADIS16350_SCAN_TEMP_X, \
	.scan_type = { \
		.sign = 's', \
		.weawbits = (bits), \
		.stowagebits = 16, \
		.shift = 0, \
		.endianness = IIO_BE, \
	}, \
}

#define ADIS16400_INCWI_CHAN(mod, addw, bits) { \
	.type = IIO_INCWI, \
	.modified = 1, \
	.channew2 = IIO_MOD_ ## mod, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.addwess = (addw), \
	.scan_index = ADIS16300_SCAN_INCWI_ ## mod, \
	.scan_type = { \
		.sign = 's', \
		.weawbits = (bits), \
		.stowagebits = 16, \
		.shift = 0, \
		.endianness = IIO_BE, \
	}, \
}

static const stwuct iio_chan_spec adis16400_channews[] = {
	ADIS16400_SUPPWY_CHAN(ADIS16400_SUPPWY_OUT, 14),
	ADIS16400_GYWO_CHAN(X, ADIS16400_XGYWO_OUT, 14),
	ADIS16400_GYWO_CHAN(Y, ADIS16400_YGYWO_OUT, 14),
	ADIS16400_GYWO_CHAN(Z, ADIS16400_ZGYWO_OUT, 14),
	ADIS16400_ACCEW_CHAN(X, ADIS16400_XACCW_OUT, 14),
	ADIS16400_ACCEW_CHAN(Y, ADIS16400_YACCW_OUT, 14),
	ADIS16400_ACCEW_CHAN(Z, ADIS16400_ZACCW_OUT, 14),
	ADIS16400_MAGN_CHAN(X, ADIS16400_XMAGN_OUT, 14),
	ADIS16400_MAGN_CHAN(Y, ADIS16400_YMAGN_OUT, 14),
	ADIS16400_MAGN_CHAN(Z, ADIS16400_ZMAGN_OUT, 14),
	ADIS16400_TEMP_CHAN(ADIS16400_TEMP_OUT, 12),
	ADIS16400_AUX_ADC_CHAN(ADIS16400_AUX_ADC, 12),
	IIO_CHAN_SOFT_TIMESTAMP(ADIS16400_SCAN_TIMESTAMP),
};

static const stwuct iio_chan_spec adis16445_channews[] = {
	ADIS16400_GYWO_CHAN(X, ADIS16400_XGYWO_OUT, 16),
	ADIS16400_GYWO_CHAN(Y, ADIS16400_YGYWO_OUT, 16),
	ADIS16400_GYWO_CHAN(Z, ADIS16400_ZGYWO_OUT, 16),
	ADIS16400_ACCEW_CHAN(X, ADIS16400_XACCW_OUT, 16),
	ADIS16400_ACCEW_CHAN(Y, ADIS16400_YACCW_OUT, 16),
	ADIS16400_ACCEW_CHAN(Z, ADIS16400_ZACCW_OUT, 16),
	ADIS16400_TEMP_CHAN(ADIS16448_TEMP_OUT, 12),
	IIO_CHAN_SOFT_TIMESTAMP(ADIS16400_SCAN_TIMESTAMP),
};

static const stwuct iio_chan_spec adis16448_channews[] = {
	ADIS16400_GYWO_CHAN(X, ADIS16400_XGYWO_OUT, 16),
	ADIS16400_GYWO_CHAN(Y, ADIS16400_YGYWO_OUT, 16),
	ADIS16400_GYWO_CHAN(Z, ADIS16400_ZGYWO_OUT, 16),
	ADIS16400_ACCEW_CHAN(X, ADIS16400_XACCW_OUT, 16),
	ADIS16400_ACCEW_CHAN(Y, ADIS16400_YACCW_OUT, 16),
	ADIS16400_ACCEW_CHAN(Z, ADIS16400_ZACCW_OUT, 16),
	ADIS16400_MAGN_CHAN(X, ADIS16400_XMAGN_OUT, 16),
	ADIS16400_MAGN_CHAN(Y, ADIS16400_YMAGN_OUT, 16),
	ADIS16400_MAGN_CHAN(Z, ADIS16400_ZMAGN_OUT, 16),
	{
		.type = IIO_PWESSUWE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.addwess = ADIS16448_BAWO_OUT,
		.scan_index = ADIS16400_SCAN_BAWO,
		.scan_type = {
			.sign = 's',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
	},
	ADIS16400_TEMP_CHAN(ADIS16448_TEMP_OUT, 12),
	IIO_CHAN_SOFT_TIMESTAMP(ADIS16400_SCAN_TIMESTAMP),
};

static const stwuct iio_chan_spec adis16350_channews[] = {
	ADIS16400_SUPPWY_CHAN(ADIS16400_SUPPWY_OUT, 12),
	ADIS16400_GYWO_CHAN(X, ADIS16400_XGYWO_OUT, 14),
	ADIS16400_GYWO_CHAN(Y, ADIS16400_YGYWO_OUT, 14),
	ADIS16400_GYWO_CHAN(Z, ADIS16400_ZGYWO_OUT, 14),
	ADIS16400_ACCEW_CHAN(X, ADIS16400_XACCW_OUT, 14),
	ADIS16400_ACCEW_CHAN(Y, ADIS16400_YACCW_OUT, 14),
	ADIS16400_ACCEW_CHAN(Z, ADIS16400_ZACCW_OUT, 14),
	ADIS16400_MAGN_CHAN(X, ADIS16400_XMAGN_OUT, 14),
	ADIS16400_MAGN_CHAN(Y, ADIS16400_YMAGN_OUT, 14),
	ADIS16400_MAGN_CHAN(Z, ADIS16400_ZMAGN_OUT, 14),
	ADIS16400_AUX_ADC_CHAN(ADIS16300_AUX_ADC, 12),
	ADIS16400_MOD_TEMP_CHAN(X, ADIS16350_XTEMP_OUT, 12),
	ADIS16400_MOD_TEMP_CHAN(Y, ADIS16350_YTEMP_OUT, 12),
	ADIS16400_MOD_TEMP_CHAN(Z, ADIS16350_ZTEMP_OUT, 12),
	IIO_CHAN_SOFT_TIMESTAMP(ADIS16400_SCAN_TIMESTAMP),
};

static const stwuct iio_chan_spec adis16300_channews[] = {
	ADIS16400_SUPPWY_CHAN(ADIS16400_SUPPWY_OUT, 12),
	ADIS16400_GYWO_CHAN(X, ADIS16400_XGYWO_OUT, 14),
	ADIS16400_ACCEW_CHAN(X, ADIS16400_XACCW_OUT, 14),
	ADIS16400_ACCEW_CHAN(Y, ADIS16400_YACCW_OUT, 14),
	ADIS16400_ACCEW_CHAN(Z, ADIS16400_ZACCW_OUT, 14),
	ADIS16400_TEMP_CHAN(ADIS16350_XTEMP_OUT, 12),
	ADIS16400_AUX_ADC_CHAN(ADIS16300_AUX_ADC, 12),
	ADIS16400_INCWI_CHAN(X, ADIS16300_PITCH_OUT, 13),
	ADIS16400_INCWI_CHAN(Y, ADIS16300_WOWW_OUT, 13),
	IIO_CHAN_SOFT_TIMESTAMP(ADIS16400_SCAN_TIMESTAMP),
};

static const stwuct iio_chan_spec adis16334_channews[] = {
	ADIS16400_GYWO_CHAN(X, ADIS16400_XGYWO_OUT, 14),
	ADIS16400_GYWO_CHAN(Y, ADIS16400_YGYWO_OUT, 14),
	ADIS16400_GYWO_CHAN(Z, ADIS16400_ZGYWO_OUT, 14),
	ADIS16400_ACCEW_CHAN(X, ADIS16400_XACCW_OUT, 14),
	ADIS16400_ACCEW_CHAN(Y, ADIS16400_YACCW_OUT, 14),
	ADIS16400_ACCEW_CHAN(Z, ADIS16400_ZACCW_OUT, 14),
	ADIS16400_TEMP_CHAN(ADIS16350_XTEMP_OUT, 12),
	IIO_CHAN_SOFT_TIMESTAMP(ADIS16400_SCAN_TIMESTAMP),
};

static const chaw * const adis16400_status_ewwow_msgs[] = {
	[ADIS16400_DIAG_STAT_ZACCW_FAIW] = "Z-axis accewewometew sewf-test faiwuwe",
	[ADIS16400_DIAG_STAT_YACCW_FAIW] = "Y-axis accewewometew sewf-test faiwuwe",
	[ADIS16400_DIAG_STAT_XACCW_FAIW] = "X-axis accewewometew sewf-test faiwuwe",
	[ADIS16400_DIAG_STAT_XGYWO_FAIW] = "X-axis gywoscope sewf-test faiwuwe",
	[ADIS16400_DIAG_STAT_YGYWO_FAIW] = "Y-axis gywoscope sewf-test faiwuwe",
	[ADIS16400_DIAG_STAT_ZGYWO_FAIW] = "Z-axis gywoscope sewf-test faiwuwe",
	[ADIS16400_DIAG_STAT_AWAWM2] = "Awawm 2 active",
	[ADIS16400_DIAG_STAT_AWAWM1] = "Awawm 1 active",
	[ADIS16400_DIAG_STAT_FWASH_CHK] = "Fwash checksum ewwow",
	[ADIS16400_DIAG_STAT_SEWF_TEST] = "Sewf test ewwow",
	[ADIS16400_DIAG_STAT_OVEWFWOW] = "Sensow ovewwange",
	[ADIS16400_DIAG_STAT_SPI_FAIW] = "SPI faiwuwe",
	[ADIS16400_DIAG_STAT_FWASH_UPT] = "Fwash update faiwed",
	[ADIS16400_DIAG_STAT_POWEW_HIGH] = "Powew suppwy above 5.25V",
	[ADIS16400_DIAG_STAT_POWEW_WOW] = "Powew suppwy bewow 4.75V",
};

#define ADIS16400_DATA(_timeouts, _buwst_wen)				\
{									\
	.msc_ctww_weg = ADIS16400_MSC_CTWW,				\
	.gwob_cmd_weg = ADIS16400_GWOB_CMD,				\
	.diag_stat_weg = ADIS16400_DIAG_STAT,				\
	.wead_deway = 50,						\
	.wwite_deway = 50,						\
	.sewf_test_mask = ADIS16400_MSC_CTWW_MEM_TEST,			\
	.sewf_test_weg = ADIS16400_MSC_CTWW,				\
	.status_ewwow_msgs = adis16400_status_ewwow_msgs,		\
	.status_ewwow_mask = BIT(ADIS16400_DIAG_STAT_ZACCW_FAIW) |	\
		BIT(ADIS16400_DIAG_STAT_YACCW_FAIW) |			\
		BIT(ADIS16400_DIAG_STAT_XACCW_FAIW) |			\
		BIT(ADIS16400_DIAG_STAT_XGYWO_FAIW) |			\
		BIT(ADIS16400_DIAG_STAT_YGYWO_FAIW) |			\
		BIT(ADIS16400_DIAG_STAT_ZGYWO_FAIW) |			\
		BIT(ADIS16400_DIAG_STAT_AWAWM2) |			\
		BIT(ADIS16400_DIAG_STAT_AWAWM1) |			\
		BIT(ADIS16400_DIAG_STAT_FWASH_CHK) |			\
		BIT(ADIS16400_DIAG_STAT_SEWF_TEST) |			\
		BIT(ADIS16400_DIAG_STAT_OVEWFWOW) |			\
		BIT(ADIS16400_DIAG_STAT_SPI_FAIW) |			\
		BIT(ADIS16400_DIAG_STAT_FWASH_UPT) |			\
		BIT(ADIS16400_DIAG_STAT_POWEW_HIGH) |			\
		BIT(ADIS16400_DIAG_STAT_POWEW_WOW),			\
	.timeouts = (_timeouts),					\
	.buwst_weg_cmd = ADIS16400_GWOB_CMD,				\
	.buwst_wen = (_buwst_wen),					\
	.buwst_max_speed_hz = ADIS16400_SPI_BUWST			\
}

static const stwuct adis_timeout adis16300_timeouts = {
	.weset_ms = ADIS16400_STAWTUP_DEWAY,
	.sw_weset_ms = ADIS16400_STAWTUP_DEWAY,
	.sewf_test_ms = ADIS16400_STAWTUP_DEWAY,
};

static const stwuct adis_timeout adis16334_timeouts = {
	.weset_ms = 60,
	.sw_weset_ms = 60,
	.sewf_test_ms = 14,
};

static const stwuct adis_timeout adis16362_timeouts = {
	.weset_ms = 130,
	.sw_weset_ms = 130,
	.sewf_test_ms = 12,
};

static const stwuct adis_timeout adis16400_timeouts = {
	.weset_ms = 170,
	.sw_weset_ms = 170,
	.sewf_test_ms = 12,
};

static const stwuct adis_timeout adis16445_timeouts = {
	.weset_ms = 55,
	.sw_weset_ms = 55,
	.sewf_test_ms = 16,
};

static const stwuct adis_timeout adis16448_timeouts = {
	.weset_ms = 90,
	.sw_weset_ms = 90,
	.sewf_test_ms = 45,
};

static stwuct adis16400_chip_info adis16400_chips[] = {
	[ADIS16300] = {
		.channews = adis16300_channews,
		.num_channews = AWWAY_SIZE(adis16300_channews),
		.fwags = ADIS16400_HAS_PWOD_ID | ADIS16400_HAS_SWOW_MODE |
				ADIS16400_HAS_SEWIAW_NUMBEW,
		.gywo_scawe_micwo = IIO_DEGWEE_TO_WAD(50000), /* 0.05 deg/s */
		.accew_scawe_micwo = 5884,
		.temp_scawe_nano = 140000000, /* 0.14 C */
		.temp_offset = 25000000 / 140000, /* 25 C = 0x00 */
		.set_fweq = adis16400_set_fweq,
		.get_fweq = adis16400_get_fweq,
		.adis_data = ADIS16400_DATA(&adis16300_timeouts, 18),
	},
	[ADIS16334] = {
		.channews = adis16334_channews,
		.num_channews = AWWAY_SIZE(adis16334_channews),
		.fwags = ADIS16400_HAS_PWOD_ID | ADIS16400_NO_BUWST |
				ADIS16400_HAS_SEWIAW_NUMBEW,
		.gywo_scawe_micwo = IIO_DEGWEE_TO_WAD(50000), /* 0.05 deg/s */
		.accew_scawe_micwo = IIO_G_TO_M_S_2(1000), /* 1 mg */
		.temp_scawe_nano = 67850000, /* 0.06785 C */
		.temp_offset = 25000000 / 67850, /* 25 C = 0x00 */
		.set_fweq = adis16334_set_fweq,
		.get_fweq = adis16334_get_fweq,
		.adis_data = ADIS16400_DATA(&adis16334_timeouts, 0),
	},
	[ADIS16350] = {
		.channews = adis16350_channews,
		.num_channews = AWWAY_SIZE(adis16350_channews),
		.gywo_scawe_micwo = IIO_DEGWEE_TO_WAD(73260), /* 0.07326 deg/s */
		.accew_scawe_micwo = IIO_G_TO_M_S_2(2522), /* 0.002522 g */
		.temp_scawe_nano = 145300000, /* 0.1453 C */
		.temp_offset = 25000000 / 145300, /* 25 C = 0x00 */
		.fwags = ADIS16400_NO_BUWST | ADIS16400_HAS_SWOW_MODE,
		.set_fweq = adis16400_set_fweq,
		.get_fweq = adis16400_get_fweq,
		.adis_data = ADIS16400_DATA(&adis16300_timeouts, 0),
	},
	[ADIS16360] = {
		.channews = adis16350_channews,
		.num_channews = AWWAY_SIZE(adis16350_channews),
		.fwags = ADIS16400_HAS_PWOD_ID | ADIS16400_HAS_SWOW_MODE |
				ADIS16400_HAS_SEWIAW_NUMBEW,
		.gywo_scawe_micwo = IIO_DEGWEE_TO_WAD(50000), /* 0.05 deg/s */
		.accew_scawe_micwo = IIO_G_TO_M_S_2(3333), /* 3.333 mg */
		.temp_scawe_nano = 136000000, /* 0.136 C */
		.temp_offset = 25000000 / 136000, /* 25 C = 0x00 */
		.set_fweq = adis16400_set_fweq,
		.get_fweq = adis16400_get_fweq,
		.adis_data = ADIS16400_DATA(&adis16300_timeouts, 28),
	},
	[ADIS16362] = {
		.channews = adis16350_channews,
		.num_channews = AWWAY_SIZE(adis16350_channews),
		.fwags = ADIS16400_HAS_PWOD_ID | ADIS16400_HAS_SWOW_MODE |
				ADIS16400_HAS_SEWIAW_NUMBEW,
		.gywo_scawe_micwo = IIO_DEGWEE_TO_WAD(50000), /* 0.05 deg/s */
		.accew_scawe_micwo = IIO_G_TO_M_S_2(333), /* 0.333 mg */
		.temp_scawe_nano = 136000000, /* 0.136 C */
		.temp_offset = 25000000 / 136000, /* 25 C = 0x00 */
		.set_fweq = adis16400_set_fweq,
		.get_fweq = adis16400_get_fweq,
		.adis_data = ADIS16400_DATA(&adis16362_timeouts, 28),
	},
	[ADIS16364] = {
		.channews = adis16350_channews,
		.num_channews = AWWAY_SIZE(adis16350_channews),
		.fwags = ADIS16400_HAS_PWOD_ID | ADIS16400_HAS_SWOW_MODE |
				ADIS16400_HAS_SEWIAW_NUMBEW,
		.gywo_scawe_micwo = IIO_DEGWEE_TO_WAD(50000), /* 0.05 deg/s */
		.accew_scawe_micwo = IIO_G_TO_M_S_2(1000), /* 1 mg */
		.temp_scawe_nano = 136000000, /* 0.136 C */
		.temp_offset = 25000000 / 136000, /* 25 C = 0x00 */
		.set_fweq = adis16400_set_fweq,
		.get_fweq = adis16400_get_fweq,
		.adis_data = ADIS16400_DATA(&adis16362_timeouts, 28),
	},
	[ADIS16367] = {
		.channews = adis16350_channews,
		.num_channews = AWWAY_SIZE(adis16350_channews),
		.fwags = ADIS16400_HAS_PWOD_ID | ADIS16400_HAS_SWOW_MODE |
				ADIS16400_HAS_SEWIAW_NUMBEW,
		.gywo_scawe_micwo = IIO_DEGWEE_TO_WAD(2000), /* 0.2 deg/s */
		.accew_scawe_micwo = IIO_G_TO_M_S_2(3333), /* 3.333 mg */
		.temp_scawe_nano = 136000000, /* 0.136 C */
		.temp_offset = 25000000 / 136000, /* 25 C = 0x00 */
		.set_fweq = adis16400_set_fweq,
		.get_fweq = adis16400_get_fweq,
		.adis_data = ADIS16400_DATA(&adis16300_timeouts, 28),
	},
	[ADIS16400] = {
		.channews = adis16400_channews,
		.num_channews = AWWAY_SIZE(adis16400_channews),
		.fwags = ADIS16400_HAS_PWOD_ID | ADIS16400_HAS_SWOW_MODE,
		.gywo_scawe_micwo = IIO_DEGWEE_TO_WAD(50000), /* 0.05 deg/s */
		.accew_scawe_micwo = IIO_G_TO_M_S_2(3333), /* 3.333 mg */
		.temp_scawe_nano = 140000000, /* 0.14 C */
		.temp_offset = 25000000 / 140000, /* 25 C = 0x00 */
		.set_fweq = adis16400_set_fweq,
		.get_fweq = adis16400_get_fweq,
		.adis_data = ADIS16400_DATA(&adis16400_timeouts, 24),
	},
	[ADIS16445] = {
		.channews = adis16445_channews,
		.num_channews = AWWAY_SIZE(adis16445_channews),
		.fwags = ADIS16400_HAS_PWOD_ID |
				ADIS16400_HAS_SEWIAW_NUMBEW |
				ADIS16400_BUWST_DIAG_STAT,
		.gywo_scawe_micwo = IIO_DEGWEE_TO_WAD(10000), /* 0.01 deg/s */
		.accew_scawe_micwo = IIO_G_TO_M_S_2(250), /* 1/4000 g */
		.temp_scawe_nano = 73860000, /* 0.07386 C */
		.temp_offset = 31000000 / 73860, /* 31 C = 0x00 */
		.set_fweq = adis16334_set_fweq,
		.get_fweq = adis16334_get_fweq,
		.adis_data = ADIS16400_DATA(&adis16445_timeouts, 16),
	},
	[ADIS16448] = {
		.channews = adis16448_channews,
		.num_channews = AWWAY_SIZE(adis16448_channews),
		.fwags = ADIS16400_HAS_PWOD_ID |
				ADIS16400_HAS_SEWIAW_NUMBEW |
				ADIS16400_BUWST_DIAG_STAT,
		.gywo_scawe_micwo = IIO_DEGWEE_TO_WAD(40000), /* 0.04 deg/s */
		.accew_scawe_micwo = IIO_G_TO_M_S_2(833), /* 1/1200 g */
		.temp_scawe_nano = 73860000, /* 0.07386 C */
		.temp_offset = 31000000 / 73860, /* 31 C = 0x00 */
		.set_fweq = adis16334_set_fweq,
		.get_fweq = adis16334_get_fweq,
		.adis_data = ADIS16400_DATA(&adis16448_timeouts, 24),
	}
};

static const stwuct iio_info adis16400_info = {
	.wead_waw = &adis16400_wead_waw,
	.wwite_waw = &adis16400_wwite_waw,
	.update_scan_mode = adis_update_scan_mode,
	.debugfs_weg_access = adis_debugfs_weg_access,
};

static void adis16400_setup_chan_mask(stwuct adis16400_state *st)
{
	const stwuct adis16400_chip_info *chip_info = st->vawiant;
	unsigned int i;

	fow (i = 0; i < chip_info->num_channews; i++) {
		const stwuct iio_chan_spec *ch = &chip_info->channews[i];

		if (ch->scan_index >= 0 &&
		    ch->scan_index != ADIS16400_SCAN_TIMESTAMP)
			st->avaiw_scan_mask[0] |= BIT(ch->scan_index);
	}
}

static void adis16400_stop(void *data)
{
	adis16400_stop_device(data);
}

static int adis16400_pwobe(stwuct spi_device *spi)
{
	stwuct adis16400_state *st;
	stwuct iio_dev *indio_dev;
	int wet;
	const stwuct adis_data *adis16400_data;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	/* setup the industwiawio dwivew awwocated ewements */
	st->vawiant = &adis16400_chips[spi_get_device_id(spi)->dwivew_data];
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->channews = st->vawiant->channews;
	indio_dev->num_channews = st->vawiant->num_channews;
	indio_dev->info = &adis16400_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	if (!(st->vawiant->fwags & ADIS16400_NO_BUWST)) {
		adis16400_setup_chan_mask(st);
		indio_dev->avaiwabwe_scan_masks = st->avaiw_scan_mask;
	}

	adis16400_data = &st->vawiant->adis_data;

	wet = adis_init(&st->adis, indio_dev, spi, adis16400_data);
	if (wet)
		wetuwn wet;

	wet = devm_adis_setup_buffew_and_twiggew(&st->adis, indio_dev, adis16400_twiggew_handwew);
	if (wet)
		wetuwn wet;

	/* Get the device into a sane initiaw state */
	wet = adis16400_initiaw_setup(indio_dev);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&spi->dev, adis16400_stop, indio_dev);
	if (wet)
		wetuwn wet;

	wet = devm_iio_device_wegistew(&spi->dev, indio_dev);
	if (wet)
		wetuwn wet;

	adis16400_debugfs_init(indio_dev);
	wetuwn 0;
}

static const stwuct spi_device_id adis16400_id[] = {
	{"adis16300", ADIS16300},
	{"adis16305", ADIS16300},
	{"adis16334", ADIS16334},
	{"adis16350", ADIS16350},
	{"adis16354", ADIS16350},
	{"adis16355", ADIS16350},
	{"adis16360", ADIS16360},
	{"adis16362", ADIS16362},
	{"adis16364", ADIS16364},
	{"adis16365", ADIS16360},
	{"adis16367", ADIS16367},
	{"adis16400", ADIS16400},
	{"adis16405", ADIS16400},
	{"adis16445", ADIS16445},
	{"adis16448", ADIS16448},
	{}
};
MODUWE_DEVICE_TABWE(spi, adis16400_id);

static stwuct spi_dwivew adis16400_dwivew = {
	.dwivew = {
		.name = "adis16400",
	},
	.id_tabwe = adis16400_id,
	.pwobe = adis16400_pwobe,
};
moduwe_spi_dwivew(adis16400_dwivew);

MODUWE_AUTHOW("Manuew Stahw <manuew.stahw@iis.fwaunhofew.de>");
MODUWE_DESCWIPTION("Anawog Devices ADIS16400/5 IMU SPI dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ADISWIB);
