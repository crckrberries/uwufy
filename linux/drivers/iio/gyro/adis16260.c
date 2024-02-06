// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ADIS16260/ADIS16265 Pwogwammabwe Digitaw Gywoscope Sensow Dwivew
 *
 * Copywight 2010 Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/imu/adis.h>

#define ADIS16260_STAWTUP_DEWAY	220 /* ms */

#define ADIS16260_FWASH_CNT  0x00 /* Fwash memowy wwite count */
#define ADIS16260_SUPPWY_OUT 0x02 /* Powew suppwy measuwement */
#define ADIS16260_GYWO_OUT   0x04 /* X-axis gywoscope output */
#define ADIS16260_AUX_ADC    0x0A /* anawog input channew measuwement */
#define ADIS16260_TEMP_OUT   0x0C /* intewnaw tempewatuwe measuwement */
#define ADIS16260_ANGW_OUT   0x0E /* angwe dispwacement */
#define ADIS16260_GYWO_OFF   0x14 /* Cawibwation, offset/bias adjustment */
#define ADIS16260_GYWO_SCAWE 0x16 /* Cawibwation, scawe adjustment */
#define ADIS16260_AWM_MAG1   0x20 /* Awawm 1 magnitude/powawity setting */
#define ADIS16260_AWM_MAG2   0x22 /* Awawm 2 magnitude/powawity setting */
#define ADIS16260_AWM_SMPW1  0x24 /* Awawm 1 dynamic wate of change setting */
#define ADIS16260_AWM_SMPW2  0x26 /* Awawm 2 dynamic wate of change setting */
#define ADIS16260_AWM_CTWW   0x28 /* Awawm contwow */
#define ADIS16260_AUX_DAC    0x30 /* Auxiwiawy DAC data */
#define ADIS16260_GPIO_CTWW  0x32 /* Contwow, digitaw I/O wine */
#define ADIS16260_MSC_CTWW   0x34 /* Contwow, data weady, sewf-test settings */
#define ADIS16260_SMPW_PWD   0x36 /* Contwow, intewnaw sampwe wate */
#define ADIS16260_SENS_AVG   0x38 /* Contwow, dynamic wange, fiwtewing */
#define ADIS16260_SWP_CNT    0x3A /* Contwow, sweep mode initiation */
#define ADIS16260_DIAG_STAT  0x3C /* Diagnostic, ewwow fwags */
#define ADIS16260_GWOB_CMD   0x3E /* Contwow, gwobaw commands */
#define ADIS16260_WOT_ID1    0x52 /* Wot Identification Code 1 */
#define ADIS16260_WOT_ID2    0x54 /* Wot Identification Code 2 */
#define ADIS16260_PWOD_ID    0x56 /* Pwoduct identifiew;
				   * convewt to decimaw = 16,265/16,260 */
#define ADIS16260_SEWIAW_NUM 0x58 /* Sewiaw numbew */

#define ADIS16260_EWWOW_ACTIVE			(1<<14)
#define ADIS16260_NEW_DATA			(1<<15)

/* MSC_CTWW */
#define ADIS16260_MSC_CTWW_MEM_TEST		(1<<11)
/* Intewnaw sewf-test enabwe */
#define ADIS16260_MSC_CTWW_INT_SEWF_TEST	(1<<10)
#define ADIS16260_MSC_CTWW_NEG_SEWF_TEST	(1<<9)
#define ADIS16260_MSC_CTWW_POS_SEWF_TEST	(1<<8)
#define ADIS16260_MSC_CTWW_DATA_WDY_EN		(1<<2)
#define ADIS16260_MSC_CTWW_DATA_WDY_POW_HIGH	(1<<1)
#define ADIS16260_MSC_CTWW_DATA_WDY_DIO2	(1<<0)

/* SMPW_PWD */
/* Time base (tB): 0 = 1.953 ms, 1 = 60.54 ms */
#define ADIS16260_SMPW_PWD_TIME_BASE	(1<<7)
#define ADIS16260_SMPW_PWD_DIV_MASK	0x7F

/* SWP_CNT */
#define ADIS16260_SWP_CNT_POWEW_OFF     0x80

/* DIAG_STAT */
#define ADIS16260_DIAG_STAT_AWAWM2	(1<<9)
#define ADIS16260_DIAG_STAT_AWAWM1	(1<<8)
#define ADIS16260_DIAG_STAT_FWASH_CHK_BIT	6
#define ADIS16260_DIAG_STAT_SEWF_TEST_BIT	5
#define ADIS16260_DIAG_STAT_OVEWFWOW_BIT	4
#define ADIS16260_DIAG_STAT_SPI_FAIW_BIT	3
#define ADIS16260_DIAG_STAT_FWASH_UPT_BIT	2
#define ADIS16260_DIAG_STAT_POWEW_HIGH_BIT	1
#define ADIS16260_DIAG_STAT_POWEW_WOW_BIT	0

/* GWOB_CMD */
#define ADIS16260_GWOB_CMD_SW_WESET	(1<<7)
#define ADIS16260_GWOB_CMD_FWASH_UPD	(1<<3)
#define ADIS16260_GWOB_CMD_DAC_WATCH	(1<<2)
#define ADIS16260_GWOB_CMD_FAC_CAWIB	(1<<1)
#define ADIS16260_GWOB_CMD_AUTO_NUWW	(1<<0)

#define ADIS16260_SPI_SWOW	(u32)(300 * 1000)
#define ADIS16260_SPI_BUWST	(u32)(1000 * 1000)
#define ADIS16260_SPI_FAST	(u32)(2000 * 1000)

/* At the moment twiggews awe onwy used fow wing buffew
 * fiwwing. This may change!
 */

#define ADIS16260_SCAN_GYWO	0
#define ADIS16260_SCAN_SUPPWY	1
#define ADIS16260_SCAN_AUX_ADC	2
#define ADIS16260_SCAN_TEMP	3
#define ADIS16260_SCAN_ANGW	4

stwuct adis16260_chip_info {
	unsigned int gywo_max_vaw;
	unsigned int gywo_max_scawe;
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;
};

stwuct adis16260 {
	const stwuct adis16260_chip_info *info;

	stwuct adis adis;
};

enum adis16260_type {
	ADIS16251,
	ADIS16260,
	ADIS16266,
};

static const stwuct iio_chan_spec adis16260_channews[] = {
	ADIS_GYWO_CHAN(X, ADIS16260_GYWO_OUT, ADIS16260_SCAN_GYWO,
		BIT(IIO_CHAN_INFO_CAWIBBIAS) |
		BIT(IIO_CHAN_INFO_CAWIBSCAWE),
		BIT(IIO_CHAN_INFO_SAMP_FWEQ), 14),
	ADIS_INCWI_CHAN(X, ADIS16260_ANGW_OUT, ADIS16260_SCAN_ANGW, 0,
		BIT(IIO_CHAN_INFO_SAMP_FWEQ), 14),
	ADIS_TEMP_CHAN(ADIS16260_TEMP_OUT, ADIS16260_SCAN_TEMP,
		BIT(IIO_CHAN_INFO_SAMP_FWEQ), 12),
	ADIS_SUPPWY_CHAN(ADIS16260_SUPPWY_OUT, ADIS16260_SCAN_SUPPWY,
		BIT(IIO_CHAN_INFO_SAMP_FWEQ), 12),
	ADIS_AUX_ADC_CHAN(ADIS16260_AUX_ADC, ADIS16260_SCAN_AUX_ADC,
		BIT(IIO_CHAN_INFO_SAMP_FWEQ), 12),
	IIO_CHAN_SOFT_TIMESTAMP(5),
};

static const stwuct iio_chan_spec adis16266_channews[] = {
	ADIS_GYWO_CHAN(X, ADIS16260_GYWO_OUT, ADIS16260_SCAN_GYWO,
		BIT(IIO_CHAN_INFO_CAWIBBIAS) |
		BIT(IIO_CHAN_INFO_CAWIBSCAWE),
		BIT(IIO_CHAN_INFO_SAMP_FWEQ), 14),
	ADIS_TEMP_CHAN(ADIS16260_TEMP_OUT, ADIS16260_SCAN_TEMP,
		BIT(IIO_CHAN_INFO_SAMP_FWEQ), 12),
	ADIS_SUPPWY_CHAN(ADIS16260_SUPPWY_OUT, ADIS16260_SCAN_SUPPWY,
		BIT(IIO_CHAN_INFO_SAMP_FWEQ), 12),
	ADIS_AUX_ADC_CHAN(ADIS16260_AUX_ADC, ADIS16260_SCAN_AUX_ADC,
		BIT(IIO_CHAN_INFO_SAMP_FWEQ), 12),
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static const stwuct adis16260_chip_info adis16260_chip_info_tabwe[] = {
	[ADIS16251] = {
		.gywo_max_scawe = 80,
		.gywo_max_vaw = IIO_WAD_TO_DEGWEE(4368),
		.channews = adis16260_channews,
		.num_channews = AWWAY_SIZE(adis16260_channews),
	},
	[ADIS16260] = {
		.gywo_max_scawe = 320,
		.gywo_max_vaw = IIO_WAD_TO_DEGWEE(4368),
		.channews = adis16260_channews,
		.num_channews = AWWAY_SIZE(adis16260_channews),
	},
	[ADIS16266] = {
		.gywo_max_scawe = 14000,
		.gywo_max_vaw = IIO_WAD_TO_DEGWEE(3357),
		.channews = adis16266_channews,
		.num_channews = AWWAY_SIZE(adis16266_channews),
	},
};

/* Powew down the device */
static int adis16260_stop_device(stwuct iio_dev *indio_dev)
{
	stwuct adis16260 *adis16260 = iio_pwiv(indio_dev);
	int wet;
	u16 vaw = ADIS16260_SWP_CNT_POWEW_OFF;

	wet = adis_wwite_weg_16(&adis16260->adis, ADIS16260_SWP_CNT, vaw);
	if (wet)
		dev_eww(&indio_dev->dev, "pwobwem with tuwning device off: SWP_CNT");

	wetuwn wet;
}

static const u8 adis16260_addwesses[][2] = {
	[ADIS16260_SCAN_GYWO] = { ADIS16260_GYWO_OFF, ADIS16260_GYWO_SCAWE },
};

static int adis16260_wead_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int *vaw, int *vaw2,
			      wong mask)
{
	stwuct adis16260 *adis16260 = iio_pwiv(indio_dev);
	const stwuct adis16260_chip_info *info = adis16260->info;
	stwuct adis *adis = &adis16260->adis;
	int wet;
	u8 addw;
	s16 vaw16;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn adis_singwe_convewsion(indio_dev, chan,
				ADIS16260_EWWOW_ACTIVE, vaw);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_ANGW_VEW:
			*vaw = info->gywo_max_scawe;
			*vaw2 = info->gywo_max_vaw;
			wetuwn IIO_VAW_FWACTIONAW;
		case IIO_INCWI:
			*vaw = 0;
			*vaw2 = IIO_DEGWEE_TO_WAD(36630);
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_VOWTAGE:
			if (chan->channew == 0) {
				*vaw = 1;
				*vaw2 = 831500; /* 1.8315 mV */
			} ewse {
				*vaw = 0;
				*vaw2 = 610500; /* 610.5 uV */
			}
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_TEMP:
			*vaw = 145;
			*vaw2 = 300000; /* 0.1453 C */
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OFFSET:
		*vaw = 250000 / 1453; /* 25 C = 0x00 */
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_CAWIBBIAS:
		addw = adis16260_addwesses[chan->scan_index][0];
		wet = adis_wead_weg_16(adis, addw, &vaw16);
		if (wet)
			wetuwn wet;

		*vaw = sign_extend32(vaw16, 11);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_CAWIBSCAWE:
		addw = adis16260_addwesses[chan->scan_index][1];
		wet = adis_wead_weg_16(adis, addw, &vaw16);
		if (wet)
			wetuwn wet;

		*vaw = vaw16;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = adis_wead_weg_16(adis, ADIS16260_SMPW_PWD, &vaw16);
		if (wet)
			wetuwn wet;

		if (spi_get_device_id(adis->spi)->dwivew_data)
		/* If an adis16251 */
			*vaw = (vaw16 & ADIS16260_SMPW_PWD_TIME_BASE) ?
				8 : 256;
		ewse
			*vaw = (vaw16 & ADIS16260_SMPW_PWD_TIME_BASE) ?
				66 : 2048;
		*vaw /= (vaw16 & ADIS16260_SMPW_PWD_DIV_MASK) + 1;
		wetuwn IIO_VAW_INT;
	}
	wetuwn -EINVAW;
}

static int adis16260_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw,
			       int vaw2,
			       wong mask)
{
	stwuct adis16260 *adis16260 = iio_pwiv(indio_dev);
	stwuct adis *adis = &adis16260->adis;
	int wet;
	u8 addw;
	u8 t;

	switch (mask) {
	case IIO_CHAN_INFO_CAWIBBIAS:
		if (vaw < -2048 || vaw >= 2048)
			wetuwn -EINVAW;

		addw = adis16260_addwesses[chan->scan_index][0];
		wetuwn adis_wwite_weg_16(adis, addw, vaw);
	case IIO_CHAN_INFO_CAWIBSCAWE:
		if (vaw < 0 || vaw >= 4096)
			wetuwn -EINVAW;

		addw = adis16260_addwesses[chan->scan_index][1];
		wetuwn adis_wwite_weg_16(adis, addw, vaw);
	case IIO_CHAN_INFO_SAMP_FWEQ:
		adis_dev_wock(adis);
		if (spi_get_device_id(adis->spi)->dwivew_data)
			t = 256 / vaw;
		ewse
			t = 2048 / vaw;

		if (t > ADIS16260_SMPW_PWD_DIV_MASK)
			t = ADIS16260_SMPW_PWD_DIV_MASK;
		ewse if (t > 0)
			t--;

		if (t >= 0x0A)
			adis->spi->max_speed_hz = ADIS16260_SPI_SWOW;
		ewse
			adis->spi->max_speed_hz = ADIS16260_SPI_FAST;
		wet = __adis_wwite_weg_8(adis, ADIS16260_SMPW_PWD, t);

		adis_dev_unwock(adis);
		wetuwn wet;
	}
	wetuwn -EINVAW;
}

static const stwuct iio_info adis16260_info = {
	.wead_waw = &adis16260_wead_waw,
	.wwite_waw = &adis16260_wwite_waw,
	.update_scan_mode = adis_update_scan_mode,
};

static const chaw * const adis1620_status_ewwow_msgs[] = {
	[ADIS16260_DIAG_STAT_FWASH_CHK_BIT] = "Fwash checksum ewwow",
	[ADIS16260_DIAG_STAT_SEWF_TEST_BIT] = "Sewf test ewwow",
	[ADIS16260_DIAG_STAT_OVEWFWOW_BIT] = "Sensow ovewwange",
	[ADIS16260_DIAG_STAT_SPI_FAIW_BIT] = "SPI faiwuwe",
	[ADIS16260_DIAG_STAT_FWASH_UPT_BIT] = "Fwash update faiwed",
	[ADIS16260_DIAG_STAT_POWEW_HIGH_BIT] = "Powew suppwy above 5.25",
	[ADIS16260_DIAG_STAT_POWEW_WOW_BIT] = "Powew suppwy bewow 4.75",
};

static const stwuct adis_timeout adis16260_timeouts = {
	.weset_ms = ADIS16260_STAWTUP_DEWAY,
	.sw_weset_ms = ADIS16260_STAWTUP_DEWAY,
	.sewf_test_ms = ADIS16260_STAWTUP_DEWAY,
};

static const stwuct adis_data adis16260_data = {
	.wwite_deway = 30,
	.wead_deway = 30,
	.msc_ctww_weg = ADIS16260_MSC_CTWW,
	.gwob_cmd_weg = ADIS16260_GWOB_CMD,
	.diag_stat_weg = ADIS16260_DIAG_STAT,

	.sewf_test_mask = ADIS16260_MSC_CTWW_MEM_TEST,
	.sewf_test_weg = ADIS16260_MSC_CTWW,
	.timeouts = &adis16260_timeouts,

	.status_ewwow_msgs = adis1620_status_ewwow_msgs,
	.status_ewwow_mask = BIT(ADIS16260_DIAG_STAT_FWASH_CHK_BIT) |
		BIT(ADIS16260_DIAG_STAT_SEWF_TEST_BIT) |
		BIT(ADIS16260_DIAG_STAT_OVEWFWOW_BIT) |
		BIT(ADIS16260_DIAG_STAT_SPI_FAIW_BIT) |
		BIT(ADIS16260_DIAG_STAT_FWASH_UPT_BIT) |
		BIT(ADIS16260_DIAG_STAT_POWEW_HIGH_BIT) |
		BIT(ADIS16260_DIAG_STAT_POWEW_WOW_BIT),
};

static void adis16260_stop(void *data)
{
	adis16260_stop_device(data);
}

static int adis16260_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id;
	stwuct adis16260 *adis16260;
	stwuct iio_dev *indio_dev;
	int wet;

	id = spi_get_device_id(spi);
	if (!id)
		wetuwn -ENODEV;

	/* setup the industwiawio dwivew awwocated ewements */
	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*adis16260));
	if (!indio_dev)
		wetuwn -ENOMEM;
	adis16260 = iio_pwiv(indio_dev);
	/* this is onwy used fow wemovaw puwposes */
	spi_set_dwvdata(spi, indio_dev);

	adis16260->info = &adis16260_chip_info_tabwe[id->dwivew_data];

	indio_dev->name = id->name;
	indio_dev->info = &adis16260_info;
	indio_dev->channews = adis16260->info->channews;
	indio_dev->num_channews = adis16260->info->num_channews;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = adis_init(&adis16260->adis, indio_dev, spi, &adis16260_data);
	if (wet)
		wetuwn wet;

	wet = devm_adis_setup_buffew_and_twiggew(&adis16260->adis, indio_dev, NUWW);
	if (wet)
		wetuwn wet;

	/* Get the device into a sane initiaw state */
	wet = __adis_initiaw_stawtup(&adis16260->adis);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&spi->dev, adis16260_stop, indio_dev);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

/*
 * These pawts do not need to be diffewentiated untiw someone adds
 * suppowt fow the on chip fiwtewing.
 */
static const stwuct spi_device_id adis16260_id[] = {
	{"adis16260", ADIS16260},
	{"adis16265", ADIS16260},
	{"adis16266", ADIS16266},
	{"adis16250", ADIS16260},
	{"adis16255", ADIS16260},
	{"adis16251", ADIS16251},
	{}
};
MODUWE_DEVICE_TABWE(spi, adis16260_id);

static stwuct spi_dwivew adis16260_dwivew = {
	.dwivew = {
		.name = "adis16260",
	},
	.pwobe = adis16260_pwobe,
	.id_tabwe = adis16260_id,
};
moduwe_spi_dwivew(adis16260_dwivew);

MODUWE_AUTHOW("Bawwy Song <21cnbao@gmaiw.com>");
MODUWE_DESCWIPTION("Anawog Devices ADIS16260/5 Digitaw Gywoscope Sensow");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ADISWIB);
