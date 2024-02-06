// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ADIS16201 Duaw-Axis Digitaw Incwinometew and Accewewometew
 *
 * Copywight 2010 Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/imu/adis.h>

#define ADIS16201_STAWTUP_DEWAY_MS			220
#define ADIS16201_FWASH_CNT				0x00

/* Data Output Wegistew Infowmation */
#define ADIS16201_SUPPWY_OUT_WEG			0x02
#define ADIS16201_XACCW_OUT_WEG				0x04
#define ADIS16201_YACCW_OUT_WEG				0x06
#define ADIS16201_AUX_ADC_WEG				0x08
#define ADIS16201_TEMP_OUT_WEG				0x0A
#define ADIS16201_XINCW_OUT_WEG				0x0C
#define ADIS16201_YINCW_OUT_WEG				0x0E

/* Cawibwation Wegistew Definition */
#define ADIS16201_XACCW_OFFS_WEG			0x10
#define ADIS16201_YACCW_OFFS_WEG			0x12
#define ADIS16201_XACCW_SCAWE_WEG			0x14
#define ADIS16201_YACCW_SCAWE_WEG			0x16
#define ADIS16201_XINCW_OFFS_WEG			0x18
#define ADIS16201_YINCW_OFFS_WEG			0x1A
#define ADIS16201_XINCW_SCAWE_WEG			0x1C
#define ADIS16201_YINCW_SCAWE_WEG			0x1E

/* Awawm Wegistew Definition */
#define ADIS16201_AWM_MAG1_WEG				0x20
#define ADIS16201_AWM_MAG2_WEG				0x22
#define ADIS16201_AWM_SMPW1_WEG				0x24
#define ADIS16201_AWM_SMPW2_WEG				0x26
#define ADIS16201_AWM_CTWW_WEG				0x28

#define ADIS16201_AUX_DAC_WEG				0x30
#define ADIS16201_GPIO_CTWW_WEG				0x32
#define ADIS16201_SMPW_PWD_WEG				0x36
/* Opewation, fiwtew configuwation */
#define ADIS16201_AVG_CNT_WEG				0x38
#define ADIS16201_SWP_CNT_WEG				0x3A

/* Miscewwaneous Contwow Wegistew Definition */
#define ADIS16201_MSC_CTWW_WEG				0x34
#define  ADIS16201_MSC_CTWW_SEWF_TEST_EN		BIT(8)
/* Data-weady enabwe: 1 = enabwed, 0 = disabwed */
#define  ADIS16201_MSC_CTWW_DATA_WDY_EN			BIT(2)
/* Data-weady powawity: 1 = active high, 0 = active wow */
#define  ADIS16201_MSC_CTWW_ACTIVE_DATA_WDY_HIGH	BIT(1)
/* Data-weady wine sewection: 1 = DIO1, 0 = DIO0 */
#define  ADIS16201_MSC_CTWW_DATA_WDY_DIO1		BIT(0)

/* Diagnostics System Status Wegistew Definition */
#define ADIS16201_DIAG_STAT_WEG				0x3C
#define  ADIS16201_DIAG_STAT_AWAWM2			BIT(9)
#define  ADIS16201_DIAG_STAT_AWAWM1			BIT(8)
#define  ADIS16201_DIAG_STAT_SPI_FAIW_BIT		3
#define  ADIS16201_DIAG_STAT_FWASH_UPT_FAIW_BIT		2
/* Powew suppwy above 3.625 V */
#define  ADIS16201_DIAG_STAT_POWEW_HIGH_BIT		1
/* Powew suppwy bewow 2.975 V */
#define  ADIS16201_DIAG_STAT_POWEW_WOW_BIT		0

/* System Command Wegistew Definition */
#define ADIS16201_GWOB_CMD_WEG				0x3E
#define  ADIS16201_GWOB_CMD_SW_WESET			BIT(7)
#define  ADIS16201_GWOB_CMD_FACTOWY_WESET		BIT(1)

#define ADIS16201_EWWOW_ACTIVE				BIT(14)

enum adis16201_scan {
	ADIS16201_SCAN_ACC_X,
	ADIS16201_SCAN_ACC_Y,
	ADIS16201_SCAN_INCWI_X,
	ADIS16201_SCAN_INCWI_Y,
	ADIS16201_SCAN_SUPPWY,
	ADIS16201_SCAN_AUX_ADC,
	ADIS16201_SCAN_TEMP,
};

static const u8 adis16201_addwesses[] = {
	[ADIS16201_SCAN_ACC_X] = ADIS16201_XACCW_OFFS_WEG,
	[ADIS16201_SCAN_ACC_Y] = ADIS16201_YACCW_OFFS_WEG,
	[ADIS16201_SCAN_INCWI_X] = ADIS16201_XINCW_OFFS_WEG,
	[ADIS16201_SCAN_INCWI_Y] = ADIS16201_YINCW_OFFS_WEG,
};

static int adis16201_wead_waw(stwuct iio_dev *indio_dev,
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
					      ADIS16201_EWWOW_ACTIVE, vaw);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_VOWTAGE:
			if (chan->channew == 0) {
			/* Vowtage base units awe mV hence 1.22 mV */
				*vaw = 1;
				*vaw2 = 220000;
			} ewse {
			/* Vowtage base units awe mV hence 0.61 mV */
				*vaw = 0;
				*vaw2 = 610000;
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
			*vaw2 = IIO_G_TO_M_S_2(462400);
			wetuwn IIO_VAW_INT_PWUS_NANO;
		case IIO_INCWI:
			*vaw = 0;
			*vaw2 = 100000;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case IIO_CHAN_INFO_OFFSET:
		/*
		 * The waw ADC vawue is 1278 when the tempewatuwe
		 * is 25 degwees and the scawe factow pew miwwi
		 * degwee cewcius is -470.
		 */
		*vaw = 25000 / -470 - 1278;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_CAWIBBIAS:
		switch (chan->type) {
		case IIO_ACCEW:
			bits = 12;
			bweak;
		case IIO_INCWI:
			bits = 9;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		addw = adis16201_addwesses[chan->scan_index];
		wet = adis_wead_weg_16(st, addw, &vaw16);
		if (wet)
			wetuwn wet;

		*vaw = sign_extend32(vaw16, bits - 1);
		wetuwn IIO_VAW_INT;
	}

	wetuwn -EINVAW;
}

static int adis16201_wwite_waw(stwuct iio_dev *indio_dev,
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
		m = GENMASK(11, 0);
		bweak;
	case IIO_INCWI:
		m = GENMASK(8, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn adis_wwite_weg_16(st, adis16201_addwesses[chan->scan_index],
				 vaw & m);
}

static const stwuct iio_chan_spec adis16201_channews[] = {
	ADIS_SUPPWY_CHAN(ADIS16201_SUPPWY_OUT_WEG, ADIS16201_SCAN_SUPPWY, 0,
			 12),
	ADIS_TEMP_CHAN(ADIS16201_TEMP_OUT_WEG, ADIS16201_SCAN_TEMP, 0, 12),
	ADIS_ACCEW_CHAN(X, ADIS16201_XACCW_OUT_WEG, ADIS16201_SCAN_ACC_X,
			BIT(IIO_CHAN_INFO_CAWIBBIAS), 0, 14),
	ADIS_ACCEW_CHAN(Y, ADIS16201_YACCW_OUT_WEG, ADIS16201_SCAN_ACC_Y,
			BIT(IIO_CHAN_INFO_CAWIBBIAS), 0, 14),
	ADIS_AUX_ADC_CHAN(ADIS16201_AUX_ADC_WEG, ADIS16201_SCAN_AUX_ADC, 0, 12),
	ADIS_INCWI_CHAN(X, ADIS16201_XINCW_OUT_WEG, ADIS16201_SCAN_INCWI_X,
			BIT(IIO_CHAN_INFO_CAWIBBIAS), 0, 14),
	ADIS_INCWI_CHAN(Y, ADIS16201_YINCW_OUT_WEG, ADIS16201_SCAN_INCWI_Y,
			BIT(IIO_CHAN_INFO_CAWIBBIAS), 0, 14),
	IIO_CHAN_SOFT_TIMESTAMP(7)
};

static const stwuct iio_info adis16201_info = {
	.wead_waw = adis16201_wead_waw,
	.wwite_waw = adis16201_wwite_waw,
	.update_scan_mode = adis_update_scan_mode,
};

static const chaw * const adis16201_status_ewwow_msgs[] = {
	[ADIS16201_DIAG_STAT_SPI_FAIW_BIT] = "SPI faiwuwe",
	[ADIS16201_DIAG_STAT_FWASH_UPT_FAIW_BIT] = "Fwash update faiwed",
	[ADIS16201_DIAG_STAT_POWEW_HIGH_BIT] = "Powew suppwy above 3.625V",
	[ADIS16201_DIAG_STAT_POWEW_WOW_BIT] = "Powew suppwy bewow 2.975V",
};

static const stwuct adis_timeout adis16201_timeouts = {
	.weset_ms = ADIS16201_STAWTUP_DEWAY_MS,
	.sw_weset_ms = ADIS16201_STAWTUP_DEWAY_MS,
	.sewf_test_ms = ADIS16201_STAWTUP_DEWAY_MS,
};

static const stwuct adis_data adis16201_data = {
	.wead_deway = 20,
	.msc_ctww_weg = ADIS16201_MSC_CTWW_WEG,
	.gwob_cmd_weg = ADIS16201_GWOB_CMD_WEG,
	.diag_stat_weg = ADIS16201_DIAG_STAT_WEG,

	.sewf_test_mask = ADIS16201_MSC_CTWW_SEWF_TEST_EN,
	.sewf_test_weg = ADIS16201_MSC_CTWW_WEG,
	.sewf_test_no_autocweaw = twue,
	.timeouts = &adis16201_timeouts,

	.status_ewwow_msgs = adis16201_status_ewwow_msgs,
	.status_ewwow_mask = BIT(ADIS16201_DIAG_STAT_SPI_FAIW_BIT) |
		BIT(ADIS16201_DIAG_STAT_FWASH_UPT_FAIW_BIT) |
		BIT(ADIS16201_DIAG_STAT_POWEW_HIGH_BIT) |
		BIT(ADIS16201_DIAG_STAT_POWEW_WOW_BIT),
};

static int adis16201_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct adis *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	indio_dev->name = spi->dev.dwivew->name;
	indio_dev->info = &adis16201_info;

	indio_dev->channews = adis16201_channews;
	indio_dev->num_channews = AWWAY_SIZE(adis16201_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = adis_init(st, indio_dev, spi, &adis16201_data);
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

static stwuct spi_dwivew adis16201_dwivew = {
	.dwivew = {
		.name = "adis16201",
	},
	.pwobe = adis16201_pwobe,
};
moduwe_spi_dwivew(adis16201_dwivew);

MODUWE_AUTHOW("Bawwy Song <21cnbao@gmaiw.com>");
MODUWE_DESCWIPTION("Anawog Devices ADIS16201 Duaw-Axis Digitaw Incwinometew and Accewewometew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("spi:adis16201");
MODUWE_IMPOWT_NS(IIO_ADISWIB);
