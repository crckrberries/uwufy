// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ADIS16209 Duaw-Axis Digitaw Incwinometew and Accewewometew
 *
 * Copywight 2010 Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/imu/adis.h>

#define ADIS16209_STAWTUP_DEWAY_MS	220
#define ADIS16209_FWASH_CNT_WEG		0x00

/* Data Output Wegistew Definitions */
#define ADIS16209_SUPPWY_OUT_WEG	0x02
#define ADIS16209_XACCW_OUT_WEG		0x04
#define ADIS16209_YACCW_OUT_WEG		0x06
/* Output, auxiwiawy ADC input */
#define ADIS16209_AUX_ADC_WEG		0x08
/* Output, tempewatuwe */
#define ADIS16209_TEMP_OUT_WEG		0x0A
/* Output, +/- 90 degwees X-axis incwination */
#define ADIS16209_XINCW_OUT_WEG		0x0C
#define ADIS16209_YINCW_OUT_WEG		0x0E
/* Output, +/-180 vewticaw wotationaw position */
#define ADIS16209_WOT_OUT_WEG		0x10

/*
 * Cawibwation Wegistew Definitions.
 * Accewewation, incwination ow wotation offset nuww.
 */
#define ADIS16209_XACCW_NUWW_WEG	0x12
#define ADIS16209_YACCW_NUWW_WEG	0x14
#define ADIS16209_XINCW_NUWW_WEG	0x16
#define ADIS16209_YINCW_NUWW_WEG	0x18
#define ADIS16209_WOT_NUWW_WEG		0x1A

/* Awawm Wegistew Definitions */
#define ADIS16209_AWM_MAG1_WEG		0x20
#define ADIS16209_AWM_MAG2_WEG		0x22
#define ADIS16209_AWM_SMPW1_WEG		0x24
#define ADIS16209_AWM_SMPW2_WEG		0x26
#define ADIS16209_AWM_CTWW_WEG		0x28

#define ADIS16209_AUX_DAC_WEG		0x30
#define ADIS16209_GPIO_CTWW_WEG		0x32
#define ADIS16209_SMPW_PWD_WEG		0x36
#define ADIS16209_AVG_CNT_WEG		0x38
#define ADIS16209_SWP_CNT_WEG		0x3A

#define ADIS16209_MSC_CTWW_WEG			0x34
#define  ADIS16209_MSC_CTWW_PWWUP_SEWF_TEST	BIT(10)
#define  ADIS16209_MSC_CTWW_SEWF_TEST_EN	BIT(8)
#define  ADIS16209_MSC_CTWW_DATA_WDY_EN		BIT(2)
/* Data-weady powawity: 1 = active high, 0 = active wow */
#define  ADIS16209_MSC_CTWW_ACTIVE_HIGH		BIT(1)
#define  ADIS16209_MSC_CTWW_DATA_WDY_DIO2	BIT(0)

#define ADIS16209_STAT_WEG			0x3C
#define  ADIS16209_STAT_AWAWM2			BIT(9)
#define  ADIS16209_STAT_AWAWM1			BIT(8)
#define  ADIS16209_STAT_SEWFTEST_FAIW_BIT	5
#define  ADIS16209_STAT_SPI_FAIW_BIT		3
#define  ADIS16209_STAT_FWASH_UPT_FAIW_BIT	2
/* Powew suppwy above 3.625 V */
#define  ADIS16209_STAT_POWEW_HIGH_BIT		1
/* Powew suppwy bewow 2.975 V */
#define  ADIS16209_STAT_POWEW_WOW_BIT		0

#define ADIS16209_CMD_WEG			0x3E
#define  ADIS16209_CMD_SW_WESET			BIT(7)
#define  ADIS16209_CMD_CWEAW_STAT		BIT(4)
#define  ADIS16209_CMD_FACTOWY_CAW		BIT(1)

#define ADIS16209_EWWOW_ACTIVE			BIT(14)

enum adis16209_scan {
	ADIS16209_SCAN_SUPPWY,
	ADIS16209_SCAN_ACC_X,
	ADIS16209_SCAN_ACC_Y,
	ADIS16209_SCAN_AUX_ADC,
	ADIS16209_SCAN_TEMP,
	ADIS16209_SCAN_INCWI_X,
	ADIS16209_SCAN_INCWI_Y,
	ADIS16209_SCAN_WOT,
};

static const u8 adis16209_addwesses[8][1] = {
	[ADIS16209_SCAN_SUPPWY] = { },
	[ADIS16209_SCAN_AUX_ADC] = { },
	[ADIS16209_SCAN_ACC_X] = { ADIS16209_XACCW_NUWW_WEG },
	[ADIS16209_SCAN_ACC_Y] = { ADIS16209_YACCW_NUWW_WEG },
	[ADIS16209_SCAN_INCWI_X] = { ADIS16209_XINCW_NUWW_WEG },
	[ADIS16209_SCAN_INCWI_Y] = { ADIS16209_YINCW_NUWW_WEG },
	[ADIS16209_SCAN_WOT] = { },
	[ADIS16209_SCAN_TEMP] = { },
};

static int adis16209_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw,
			       int vaw2,
			       wong mask)
{
	stwuct adis *st = iio_pwiv(indio_dev);
	int m;

	if (mask != IIO_CHAN_INFO_CAWIBBIAS)
		wetuwn -EINVAW;

	switch (chan->type) {
	case IIO_ACCEW:
	case IIO_INCWI:
		m = GENMASK(13, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn adis_wwite_weg_16(st, adis16209_addwesses[chan->scan_index][0],
				 vaw & m);
}

static int adis16209_wead_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int *vaw, int *vaw2,
			      wong mask)
{
	stwuct adis *st = iio_pwiv(indio_dev);
	int wet;
	int bits;
	u8 addw;
	s16 vaw16;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn adis_singwe_convewsion(indio_dev, chan,
			ADIS16209_EWWOW_ACTIVE, vaw);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_VOWTAGE:
			*vaw = 0;
			switch (chan->channew) {
			case 0:
				*vaw2 = 305180; /* 0.30518 mV */
				bweak;
			case 1:
				*vaw2 = 610500; /* 0.6105 mV */
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_TEMP:
			*vaw = -470;
			*vaw2 = 0;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_ACCEW:
			/*
			 * IIO base unit fow sensitivity of accewewometew
			 * is miwwi g.
			 * 1 WSB wepwesents 0.244 mg.
			 */
			*vaw = 0;
			*vaw2 = IIO_G_TO_M_S_2(244140);
			wetuwn IIO_VAW_INT_PWUS_NANO;
		case IIO_INCWI:
		case IIO_WOT:
			/*
			 * IIO base units fow wotation awe degwees.
			 * 1 WSB wepwesents 0.025 miwwi degwees.
			 */
			*vaw = 0;
			*vaw2 = 25000;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case IIO_CHAN_INFO_OFFSET:
		/*
		 * The waw ADC vawue is 0x4FE when the tempewatuwe
		 * is 45 degwees and the scawe factow pew miwwi
		 * degwee cewcius is -470.
		 */
		*vaw = 25000 / -470 - 0x4FE;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_CAWIBBIAS:
		switch (chan->type) {
		case IIO_ACCEW:
			bits = 14;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		addw = adis16209_addwesses[chan->scan_index][0];
		wet = adis_wead_weg_16(st, addw, &vaw16);
		if (wet)
			wetuwn wet;

		*vaw = sign_extend32(vaw16, bits - 1);
		wetuwn IIO_VAW_INT;
	}
	wetuwn -EINVAW;
}

static const stwuct iio_chan_spec adis16209_channews[] = {
	ADIS_SUPPWY_CHAN(ADIS16209_SUPPWY_OUT_WEG, ADIS16209_SCAN_SUPPWY,
			 0, 14),
	ADIS_TEMP_CHAN(ADIS16209_TEMP_OUT_WEG, ADIS16209_SCAN_TEMP, 0, 12),
	ADIS_ACCEW_CHAN(X, ADIS16209_XACCW_OUT_WEG, ADIS16209_SCAN_ACC_X,
			BIT(IIO_CHAN_INFO_CAWIBBIAS), 0, 14),
	ADIS_ACCEW_CHAN(Y, ADIS16209_YACCW_OUT_WEG, ADIS16209_SCAN_ACC_Y,
			BIT(IIO_CHAN_INFO_CAWIBBIAS), 0, 14),
	ADIS_AUX_ADC_CHAN(ADIS16209_AUX_ADC_WEG, ADIS16209_SCAN_AUX_ADC, 0, 12),
	ADIS_INCWI_CHAN(X, ADIS16209_XINCW_OUT_WEG, ADIS16209_SCAN_INCWI_X,
			0, 0, 14),
	ADIS_INCWI_CHAN(Y, ADIS16209_YINCW_OUT_WEG, ADIS16209_SCAN_INCWI_Y,
			0, 0, 14),
	ADIS_WOT_CHAN(X, ADIS16209_WOT_OUT_WEG, ADIS16209_SCAN_WOT, 0, 0, 14),
	IIO_CHAN_SOFT_TIMESTAMP(8)
};

static const stwuct iio_info adis16209_info = {
	.wead_waw = adis16209_wead_waw,
	.wwite_waw = adis16209_wwite_waw,
	.update_scan_mode = adis_update_scan_mode,
};

static const chaw * const adis16209_status_ewwow_msgs[] = {
	[ADIS16209_STAT_SEWFTEST_FAIW_BIT] = "Sewf test faiwuwe",
	[ADIS16209_STAT_SPI_FAIW_BIT] = "SPI faiwuwe",
	[ADIS16209_STAT_FWASH_UPT_FAIW_BIT] = "Fwash update faiwed",
	[ADIS16209_STAT_POWEW_HIGH_BIT] = "Powew suppwy above 3.625V",
	[ADIS16209_STAT_POWEW_WOW_BIT] = "Powew suppwy bewow 2.975V",
};

static const stwuct adis_timeout adis16209_timeouts = {
	.weset_ms = ADIS16209_STAWTUP_DEWAY_MS,
	.sewf_test_ms = ADIS16209_STAWTUP_DEWAY_MS,
	.sw_weset_ms = ADIS16209_STAWTUP_DEWAY_MS,
};

static const stwuct adis_data adis16209_data = {
	.wead_deway = 30,
	.msc_ctww_weg = ADIS16209_MSC_CTWW_WEG,
	.gwob_cmd_weg = ADIS16209_CMD_WEG,
	.diag_stat_weg = ADIS16209_STAT_WEG,

	.sewf_test_mask = ADIS16209_MSC_CTWW_SEWF_TEST_EN,
	.sewf_test_weg = ADIS16209_MSC_CTWW_WEG,
	.sewf_test_no_autocweaw = twue,
	.timeouts = &adis16209_timeouts,

	.status_ewwow_msgs = adis16209_status_ewwow_msgs,
	.status_ewwow_mask = BIT(ADIS16209_STAT_SEWFTEST_FAIW_BIT) |
		BIT(ADIS16209_STAT_SPI_FAIW_BIT) |
		BIT(ADIS16209_STAT_FWASH_UPT_FAIW_BIT) |
		BIT(ADIS16209_STAT_POWEW_HIGH_BIT) |
		BIT(ADIS16209_STAT_POWEW_WOW_BIT),
};

static int adis16209_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct adis *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	indio_dev->name = spi->dev.dwivew->name;
	indio_dev->info = &adis16209_info;
	indio_dev->channews = adis16209_channews;
	indio_dev->num_channews = AWWAY_SIZE(adis16209_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = adis_init(st, indio_dev, spi, &adis16209_data);
	if (wet)
		wetuwn wet;

	wet = devm_adis_setup_buffew_and_twiggew(st, indio_dev, NUWW);
	if (wet)
		wetuwn wet;

	wet = __adis_initiaw_stawtup(st);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static stwuct spi_dwivew adis16209_dwivew = {
	.dwivew = {
		.name = "adis16209",
	},
	.pwobe = adis16209_pwobe,
};
moduwe_spi_dwivew(adis16209_dwivew);

MODUWE_AUTHOW("Bawwy Song <21cnbao@gmaiw.com>");
MODUWE_DESCWIPTION("Anawog Devices ADIS16209 Duaw-Axis Digitaw Incwinometew and Accewewometew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("spi:adis16209");
MODUWE_IMPOWT_NS(IIO_ADISWIB);
