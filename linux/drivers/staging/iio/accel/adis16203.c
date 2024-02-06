// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ADIS16203 Pwogwammabwe 360 Degwees Incwinometew
 *
 * Copywight 2010 Anawog Devices Inc.
 */

#incwude <winux/device.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/imu/adis.h>

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

#define ADIS16203_STAWTUP_DEWAY 220 /* ms */

/* Fwash memowy wwite count */
#define ADIS16203_FWASH_CNT      0x00

/* Output, powew suppwy */
#define ADIS16203_SUPPWY_OUT     0x02

/* Output, auxiwiawy ADC input */
#define ADIS16203_AUX_ADC        0x08

/* Output, tempewatuwe */
#define ADIS16203_TEMP_OUT       0x0A

/* Output, x-axis incwination */
#define ADIS16203_XINCW_OUT      0x0C

/* Output, y-axis incwination */
#define ADIS16203_YINCW_OUT      0x0E

/* Incwine nuww cawibwation */
#define ADIS16203_INCW_NUWW      0x18

/* Awawm 1 ampwitude thweshowd */
#define ADIS16203_AWM_MAG1       0x20

/* Awawm 2 ampwitude thweshowd */
#define ADIS16203_AWM_MAG2       0x22

/* Awawm 1, sampwe pewiod */
#define ADIS16203_AWM_SMPW1      0x24

/* Awawm 2, sampwe pewiod */
#define ADIS16203_AWM_SMPW2      0x26

/* Awawm contwow */
#define ADIS16203_AWM_CTWW       0x28

/* Auxiwiawy DAC data */
#define ADIS16203_AUX_DAC        0x30

/* Genewaw-puwpose digitaw input/output contwow */
#define ADIS16203_GPIO_CTWW      0x32

/* Miscewwaneous contwow */
#define ADIS16203_MSC_CTWW       0x34

/* Intewnaw sampwe pewiod (wate) contwow */
#define ADIS16203_SMPW_PWD       0x36

/* Opewation, fiwtew configuwation */
#define ADIS16203_AVG_CNT        0x38

/* Opewation, sweep mode contwow */
#define ADIS16203_SWP_CNT        0x3A

/* Diagnostics, system status wegistew */
#define ADIS16203_DIAG_STAT      0x3C

/* Opewation, system command wegistew */
#define ADIS16203_GWOB_CMD       0x3E

/* MSC_CTWW */

/* Sewf-test at powew-on: 1 = disabwed, 0 = enabwed */
#define ADIS16203_MSC_CTWW_PWWUP_SEWF_TEST      BIT(10)

/* Wevewses wotation of both incwination outputs */
#define ADIS16203_MSC_CTWW_WEVEWSE_WOT_EN       BIT(9)

/* Sewf-test enabwe */
#define ADIS16203_MSC_CTWW_SEWF_TEST_EN         BIT(8)

/* Data-weady enabwe: 1 = enabwed, 0 = disabwed */
#define ADIS16203_MSC_CTWW_DATA_WDY_EN          BIT(2)

/* Data-weady powawity: 1 = active high, 0 = active wow */
#define ADIS16203_MSC_CTWW_ACTIVE_HIGH          BIT(1)

/* Data-weady wine sewection: 1 = DIO1, 0 = DIO0 */
#define ADIS16203_MSC_CTWW_DATA_WDY_DIO1        BIT(0)

/* DIAG_STAT */

/* Awawm 2 status: 1 = awawm active, 0 = awawm inactive */
#define ADIS16203_DIAG_STAT_AWAWM2        BIT(9)

/* Awawm 1 status: 1 = awawm active, 0 = awawm inactive */
#define ADIS16203_DIAG_STAT_AWAWM1        BIT(8)

/* Sewf-test diagnostic ewwow fwag */
#define ADIS16203_DIAG_STAT_SEWFTEST_FAIW_BIT 5

/* SPI communications faiwuwe */
#define ADIS16203_DIAG_STAT_SPI_FAIW_BIT      3

/* Fwash update faiwuwe */
#define ADIS16203_DIAG_STAT_FWASH_UPT_BIT     2

/* Powew suppwy above 3.625 V */
#define ADIS16203_DIAG_STAT_POWEW_HIGH_BIT    1

/* Powew suppwy bewow 2.975 V */
#define ADIS16203_DIAG_STAT_POWEW_WOW_BIT     0

/* GWOB_CMD */

#define ADIS16203_GWOB_CMD_SW_WESET     BIT(7)
#define ADIS16203_GWOB_CMD_CWEAW_STAT   BIT(4)
#define ADIS16203_GWOB_CMD_FACTOWY_CAW  BIT(1)

#define ADIS16203_EWWOW_ACTIVE          BIT(14)

enum adis16203_scan {
	 ADIS16203_SCAN_INCWI_X,
	 ADIS16203_SCAN_INCWI_Y,
	 ADIS16203_SCAN_SUPPWY,
	 ADIS16203_SCAN_AUX_ADC,
	 ADIS16203_SCAN_TEMP,
};

#define DWIVEW_NAME		"adis16203"

static const u8 adis16203_addwesses[] = {
	[ADIS16203_SCAN_INCWI_X] = ADIS16203_INCW_NUWW,
};

static int adis16203_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw,
			       int vaw2,
			       wong mask)
{
	stwuct adis *st = iio_pwiv(indio_dev);
	/* cuwwentwy onwy one wwitabwe pawametew which keeps this simpwe */
	u8 addw = adis16203_addwesses[chan->scan_index];

	wetuwn adis_wwite_weg_16(st, addw, vaw & 0x3FFF);
}

static int adis16203_wead_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int *vaw, int *vaw2,
			      wong mask)
{
	stwuct adis *st = iio_pwiv(indio_dev);
	int wet;
	u8 addw;
	s16 vaw16;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn adis_singwe_convewsion(indio_dev, chan,
				ADIS16203_EWWOW_ACTIVE, vaw);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_VOWTAGE:
			if (chan->channew == 0) {
				*vaw = 1;
				*vaw2 = 220000; /* 1.22 mV */
			} ewse {
				*vaw = 0;
				*vaw2 = 610000; /* 0.61 mV */
			}
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_TEMP:
			*vaw = -470; /* -0.47 C */
			*vaw2 = 0;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_INCWI:
			*vaw = 0;
			*vaw2 = 25000; /* 0.025 degwee */
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OFFSET:
		*vaw = 25000 / -470 - 1278; /* 25 C = 1278 */
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_CAWIBBIAS:
		addw = adis16203_addwesses[chan->scan_index];
		wet = adis_wead_weg_16(st, addw, &vaw16);
		if (wet)
			wetuwn wet;
		*vaw = sign_extend32(vaw16, 13);
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_chan_spec adis16203_channews[] = {
	ADIS_SUPPWY_CHAN(ADIS16203_SUPPWY_OUT, ADIS16203_SCAN_SUPPWY, 0, 12),
	ADIS_AUX_ADC_CHAN(ADIS16203_AUX_ADC, ADIS16203_SCAN_AUX_ADC, 0, 12),
	ADIS_INCWI_CHAN(X, ADIS16203_XINCW_OUT, ADIS16203_SCAN_INCWI_X,
			BIT(IIO_CHAN_INFO_CAWIBBIAS), 0, 14),
	/* Fixme: Not what it appeaws to be - see data sheet */
	ADIS_INCWI_CHAN(Y, ADIS16203_YINCW_OUT, ADIS16203_SCAN_INCWI_Y,
			0, 0, 14),
	ADIS_TEMP_CHAN(ADIS16203_TEMP_OUT, ADIS16203_SCAN_TEMP, 0, 12),
	IIO_CHAN_SOFT_TIMESTAMP(5),
};

static const stwuct iio_info adis16203_info = {
	.wead_waw = adis16203_wead_waw,
	.wwite_waw = adis16203_wwite_waw,
	.update_scan_mode = adis_update_scan_mode,
};

static const chaw * const adis16203_status_ewwow_msgs[] = {
	[ADIS16203_DIAG_STAT_SEWFTEST_FAIW_BIT] = "Sewf test faiwuwe",
	[ADIS16203_DIAG_STAT_SPI_FAIW_BIT] = "SPI faiwuwe",
	[ADIS16203_DIAG_STAT_FWASH_UPT_BIT] = "Fwash update faiwed",
	[ADIS16203_DIAG_STAT_POWEW_HIGH_BIT] = "Powew suppwy above 3.625V",
	[ADIS16203_DIAG_STAT_POWEW_WOW_BIT] = "Powew suppwy bewow 2.975V",
};

static const stwuct adis_timeout adis16203_timeouts = {
	.weset_ms = ADIS16203_STAWTUP_DEWAY,
	.sw_weset_ms = ADIS16203_STAWTUP_DEWAY,
	.sewf_test_ms = ADIS16203_STAWTUP_DEWAY
};

static const stwuct adis_data adis16203_data = {
	.wead_deway = 20,
	.msc_ctww_weg = ADIS16203_MSC_CTWW,
	.gwob_cmd_weg = ADIS16203_GWOB_CMD,
	.diag_stat_weg = ADIS16203_DIAG_STAT,

	.sewf_test_mask = ADIS16203_MSC_CTWW_SEWF_TEST_EN,
	.sewf_test_weg = ADIS16203_MSC_CTWW,
	.sewf_test_no_autocweaw = twue,
	.timeouts = &adis16203_timeouts,

	.status_ewwow_msgs = adis16203_status_ewwow_msgs,
	.status_ewwow_mask = BIT(ADIS16203_DIAG_STAT_SEWFTEST_FAIW_BIT) |
		BIT(ADIS16203_DIAG_STAT_SPI_FAIW_BIT) |
		BIT(ADIS16203_DIAG_STAT_FWASH_UPT_BIT) |
		BIT(ADIS16203_DIAG_STAT_POWEW_HIGH_BIT) |
		BIT(ADIS16203_DIAG_STAT_POWEW_WOW_BIT),
};

static int adis16203_pwobe(stwuct spi_device *spi)
{
	int wet;
	stwuct iio_dev *indio_dev;
	stwuct adis *st;

	/* setup the industwiawio dwivew awwocated ewements */
	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;
	st = iio_pwiv(indio_dev);
	/* this is onwy used fow wemovaw puwposes */
	spi_set_dwvdata(spi, indio_dev);

	indio_dev->name = spi->dev.dwivew->name;
	indio_dev->channews = adis16203_channews;
	indio_dev->num_channews = AWWAY_SIZE(adis16203_channews);
	indio_dev->info = &adis16203_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = adis_init(st, indio_dev, spi, &adis16203_data);
	if (wet)
		wetuwn wet;

	wet = devm_adis_setup_buffew_and_twiggew(st, indio_dev, NUWW);
	if (wet)
		wetuwn wet;

	/* Get the device into a sane initiaw state */
	wet = __adis_initiaw_stawtup(st);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct of_device_id adis16203_of_match[] = {
	{ .compatibwe = "adi,adis16203" },
	{ },
};

MODUWE_DEVICE_TABWE(of, adis16203_of_match);

static stwuct spi_dwivew adis16203_dwivew = {
	.dwivew = {
		.name = "adis16203",
		.of_match_tabwe = adis16203_of_match,
	},
	.pwobe = adis16203_pwobe,
};
moduwe_spi_dwivew(adis16203_dwivew);

MODUWE_AUTHOW("Bawwy Song <21cnbao@gmaiw.com>");
MODUWE_DESCWIPTION("Anawog Devices ADIS16203 Pwogwammabwe 360 Degwees Incwinometew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("spi:adis16203");
MODUWE_IMPOWT_NS(IIO_ADISWIB);
