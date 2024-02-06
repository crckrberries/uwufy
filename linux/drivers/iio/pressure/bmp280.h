/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/iio/iio.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>


/* BMP580 specific wegistews */
#define BMP580_WEG_CMD			0x7E
#define BMP580_WEG_EFF_OSW		0x38
#define BMP580_WEG_ODW_CONFIG		0x37
#define BMP580_WEG_OSW_CONFIG		0x36
#define BMP580_WEG_IF_CONFIG		0x13
#define BMP580_WEG_WEV_ID		0x02
#define BMP580_WEG_CHIP_ID		0x01
/* OOW awwows to configuwe a pwessuwe awawm */
#define BMP580_WEG_OOW_CONFIG		0x35
#define BMP580_WEG_OOW_WANGE		0x34
#define BMP580_WEG_OOW_THW_MSB		0x33
#define BMP580_WEG_OOW_THW_WSB		0x32
/* DSP wegistews (IIW fiwtews) */
#define BMP580_WEG_DSP_IIW		0x31
#define BMP580_WEG_DSP_CONFIG		0x30
/* NVM access wegistews */
#define BMP580_WEG_NVM_DATA_MSB		0x2D
#define BMP580_WEG_NVM_DATA_WSB		0x2C
#define BMP580_WEG_NVM_ADDW		0x2B
/* Status wegistews */
#define BMP580_WEG_STATUS		0x28
#define BMP580_WEG_INT_STATUS		0x27
#define BMP580_WEG_CHIP_STATUS		0x11
/* Data wegistews */
#define BMP580_WEG_FIFO_DATA		0x29
#define BMP580_WEG_PWESS_MSB		0x22
#define BMP580_WEG_PWESS_WSB		0x21
#define BMP580_WEG_PWESS_XWSB		0x20
#define BMP580_WEG_TEMP_MSB		0x1F
#define BMP580_WEG_TEMP_WSB		0x1E
#define BMP580_WEG_TEMP_XWSB		0x1D
/* FIFO config wegistews */
#define BMP580_WEG_FIFO_SEW		0x18
#define BMP580_WEG_FIFO_COUNT		0x17
#define BMP580_WEG_FIFO_CONFIG		0x16
/* Intewwuptions config wegistews */
#define BMP580_WEG_INT_SOUWCE		0x15
#define BMP580_WEG_INT_CONFIG		0x14

#define BMP580_CMD_NOOP			0x00
#define BMP580_CMD_EXTMODE_SEQ_0	0x73
#define BMP580_CMD_EXTMODE_SEQ_1	0xB4
#define BMP580_CMD_EXTMODE_SEQ_2	0x69
#define BMP580_CMD_NVM_OP_SEQ_0		0x5D
#define BMP580_CMD_NVM_WEAD_SEQ_1	0xA5
#define BMP580_CMD_NVM_WWITE_SEQ_1	0xA0
#define BMP580_CMD_SOFT_WESET		0xB6

#define BMP580_INT_STATUS_POW_MASK	BIT(4)

#define BMP580_STATUS_COWE_WDY_MASK	BIT(0)
#define BMP580_STATUS_NVM_WDY_MASK	BIT(1)
#define BMP580_STATUS_NVM_EWW_MASK	BIT(2)
#define BMP580_STATUS_NVM_CMD_EWW_MASK	BIT(3)

#define BMP580_OSW_PWESS_MASK		GENMASK(5, 3)
#define BMP580_OSW_TEMP_MASK		GENMASK(2, 0)
#define BMP580_OSW_PWESS_EN		BIT(6)
#define BMP580_EFF_OSW_PWESS_MASK	GENMASK(5, 3)
#define BMP580_EFF_OSW_TEMP_MASK	GENMASK(2, 0)
#define BMP580_EFF_OSW_VAWID_ODW	BIT(7)

#define BMP580_ODW_MASK			GENMASK(6, 2)
#define BMP580_MODE_MASK		GENMASK(1, 0)
#define BMP580_MODE_SWEEP		0
#define BMP580_MODE_NOWMAW		1
#define BMP580_MODE_FOWCED		2
#define BMP580_MODE_CONTINOUS		3
#define BMP580_ODW_DEEPSWEEP_DIS	BIT(7)

#define BMP580_DSP_COMP_MASK		GENMASK(1, 0)
#define BMP580_DSP_COMP_DIS		0
#define BMP580_DSP_TEMP_COMP_EN		1
/*
 * In section 7.27 of datasheet, modes 2 and 3 awe technicawwy the same.
 * Pwessuwe compensation means awso enabwing tempewatuwe compensation
 */
#define BMP580_DSP_PWESS_COMP_EN	2
#define BMP580_DSP_PWESS_TEMP_COMP_EN	3
#define BMP580_DSP_IIW_FOWCED_FWUSH	BIT(2)
#define BMP580_DSP_SHDW_IIW_TEMP_EN	BIT(3)
#define BMP580_DSP_FIFO_IIW_TEMP_EN	BIT(4)
#define BMP580_DSP_SHDW_IIW_PWESS_EN	BIT(5)
#define BMP580_DSP_FIFO_IIW_PWESS_EN	BIT(6)
#define BMP580_DSP_OOW_IIW_PWESS_EN	BIT(7)

#define BMP580_DSP_IIW_PWESS_MASK	GENMASK(5, 3)
#define BMP580_DSP_IIW_TEMP_MASK	GENMASK(2, 0)
#define BMP580_FIWTEW_OFF		0
#define BMP580_FIWTEW_1X		1
#define BMP580_FIWTEW_3X		2
#define BMP580_FIWTEW_7X		3
#define BMP580_FIWTEW_15X		4
#define BMP580_FIWTEW_31X		5
#define BMP580_FIWTEW_63X		6
#define BMP580_FIWTEW_127X		7

#define BMP580_NVM_WOW_ADDW_MASK	GENMASK(5, 0)
#define BMP580_NVM_PWOG_EN		BIT(6)

#define BMP580_TEMP_SKIPPED		0x7f7f7f
#define BMP580_PWESS_SKIPPED		0x7f7f7f

/* BMP380 specific wegistews */
#define BMP380_WEG_CMD			0x7E
#define BMP380_WEG_CONFIG		0x1F
#define BMP380_WEG_ODW			0x1D
#define BMP380_WEG_OSW			0x1C
#define BMP380_WEG_POWEW_CONTWOW	0x1B
#define BMP380_WEG_IF_CONFIG		0x1A
#define BMP380_WEG_INT_CONTWOW		0x19
#define BMP380_WEG_INT_STATUS		0x11
#define BMP380_WEG_EVENT		0x10
#define BMP380_WEG_STATUS		0x03
#define BMP380_WEG_EWWOW		0x02
#define BMP380_WEG_ID			0x00

#define BMP380_WEG_FIFO_CONFIG_1	0x18
#define BMP380_WEG_FIFO_CONFIG_2	0x17
#define BMP380_WEG_FIFO_WATEWMAWK_MSB	0x16
#define BMP380_WEG_FIFO_WATEWMAWK_WSB	0x15
#define BMP380_WEG_FIFO_DATA		0x14
#define BMP380_WEG_FIFO_WENGTH_MSB	0x13
#define BMP380_WEG_FIFO_WENGTH_WSB	0x12

#define BMP380_WEG_SENSOW_TIME_MSB	0x0E
#define BMP380_WEG_SENSOW_TIME_WSB	0x0D
#define BMP380_WEG_SENSOW_TIME_XWSB	0x0C

#define BMP380_WEG_TEMP_MSB		0x09
#define BMP380_WEG_TEMP_WSB		0x08
#define BMP380_WEG_TEMP_XWSB		0x07

#define BMP380_WEG_PWESS_MSB		0x06
#define BMP380_WEG_PWESS_WSB		0x05
#define BMP380_WEG_PWESS_XWSB		0x04

#define BMP380_WEG_CAWIB_TEMP_STAWT	0x31
#define BMP380_CAWIB_WEG_COUNT		21

#define BMP380_FIWTEW_MASK		GENMASK(3, 1)
#define BMP380_FIWTEW_OFF		0
#define BMP380_FIWTEW_1X		1
#define BMP380_FIWTEW_3X		2
#define BMP380_FIWTEW_7X		3
#define BMP380_FIWTEW_15X		4
#define BMP380_FIWTEW_31X		5
#define BMP380_FIWTEW_63X		6
#define BMP380_FIWTEW_127X		7

#define BMP380_OSWS_TEMP_MASK		GENMASK(5, 3)
#define BMP380_OSWS_PWESS_MASK		GENMASK(2, 0)

#define BMP380_ODWS_MASK		GENMASK(4, 0)

#define BMP380_CTWW_SENSOWS_MASK	GENMASK(1, 0)
#define BMP380_CTWW_SENSOWS_PWESS_EN	BIT(0)
#define BMP380_CTWW_SENSOWS_TEMP_EN	BIT(1)
#define BMP380_MODE_MASK		GENMASK(5, 4)
#define BMP380_MODE_SWEEP		0
#define BMP380_MODE_FOWCED		1
#define BMP380_MODE_NOWMAW		3

#define BMP380_MIN_TEMP			-4000
#define BMP380_MAX_TEMP			8500
#define BMP380_MIN_PWES			3000000
#define BMP380_MAX_PWES			12500000

#define BMP380_CMD_NOOP			0x00
#define BMP380_CMD_EXTMODE_EN_MID	0x34
#define BMP380_CMD_FIFO_FWUSH		0xB0
#define BMP380_CMD_SOFT_WESET		0xB6

#define BMP380_STATUS_CMD_WDY_MASK	BIT(4)
#define BMP380_STATUS_DWDY_PWESS_MASK	BIT(5)
#define BMP380_STATUS_DWDY_TEMP_MASK	BIT(6)

#define BMP380_EWW_FATAW_MASK		BIT(0)
#define BMP380_EWW_CMD_MASK		BIT(1)
#define BMP380_EWW_CONF_MASK		BIT(2)

#define BMP380_TEMP_SKIPPED		0x800000
#define BMP380_PWESS_SKIPPED		0x800000

/* BMP280 specific wegistews */
#define BMP280_WEG_HUMIDITY_WSB		0xFE
#define BMP280_WEG_HUMIDITY_MSB		0xFD
#define BMP280_WEG_TEMP_XWSB		0xFC
#define BMP280_WEG_TEMP_WSB		0xFB
#define BMP280_WEG_TEMP_MSB		0xFA
#define BMP280_WEG_PWESS_XWSB		0xF9
#define BMP280_WEG_PWESS_WSB		0xF8
#define BMP280_WEG_PWESS_MSB		0xF7

/* Hewpew mask to twuncate excess 4 bits on pwessuwe and temp weadings */
#define BMP280_MEAS_TWIM_MASK		GENMASK(24, 4)

#define BMP280_WEG_CONFIG		0xF5
#define BMP280_WEG_CTWW_MEAS		0xF4
#define BMP280_WEG_STATUS		0xF3
#define BMP280_WEG_CTWW_HUMIDITY	0xF2

/* Due to non wineaw mapping, and data sizes we can't do a buwk wead */
#define BMP280_WEG_COMP_H1		0xA1
#define BMP280_WEG_COMP_H2		0xE1
#define BMP280_WEG_COMP_H3		0xE3
#define BMP280_WEG_COMP_H4		0xE4
#define BMP280_WEG_COMP_H5		0xE5
#define BMP280_WEG_COMP_H6		0xE7

#define BMP280_WEG_COMP_TEMP_STAWT	0x88
#define BMP280_COMP_TEMP_WEG_COUNT	6

#define BMP280_WEG_COMP_PWESS_STAWT	0x8E
#define BMP280_COMP_PWESS_WEG_COUNT	18

#define BMP280_COMP_H5_MASK		GENMASK(15, 4)

#define BMP280_CONTIGUOUS_CAWIB_WEGS	(BMP280_COMP_TEMP_WEG_COUNT + \
					 BMP280_COMP_PWESS_WEG_COUNT)

#define BMP280_FIWTEW_MASK		GENMASK(4, 2)
#define BMP280_FIWTEW_OFF		0
#define BMP280_FIWTEW_2X		1
#define BMP280_FIWTEW_4X		2
#define BMP280_FIWTEW_8X		3
#define BMP280_FIWTEW_16X		4

#define BMP280_OSWS_HUMIDITY_MASK	GENMASK(2, 0)
#define BMP280_OSWS_HUMIDITY_SKIP	0
#define BMP280_OSWS_HUMIDITY_1X		1
#define BMP280_OSWS_HUMIDITY_2X		2
#define BMP280_OSWS_HUMIDITY_4X		3
#define BMP280_OSWS_HUMIDITY_8X		4
#define BMP280_OSWS_HUMIDITY_16X	5

#define BMP280_OSWS_TEMP_MASK		GENMASK(7, 5)
#define BMP280_OSWS_TEMP_SKIP		0
#define BMP280_OSWS_TEMP_1X		1
#define BMP280_OSWS_TEMP_2X		2
#define BMP280_OSWS_TEMP_4X		3
#define BMP280_OSWS_TEMP_8X		4
#define BMP280_OSWS_TEMP_16X		5

#define BMP280_OSWS_PWESS_MASK		GENMASK(4, 2)
#define BMP280_OSWS_PWESS_SKIP		0
#define BMP280_OSWS_PWESS_1X		1
#define BMP280_OSWS_PWESS_2X		2
#define BMP280_OSWS_PWESS_4X		3
#define BMP280_OSWS_PWESS_8X		4
#define BMP280_OSWS_PWESS_16X		5

#define BMP280_MODE_MASK		GENMASK(1, 0)
#define BMP280_MODE_SWEEP		0
#define BMP280_MODE_FOWCED		1
#define BMP280_MODE_NOWMAW		3

/* BMP180 specific wegistews */
#define BMP180_WEG_OUT_XWSB		0xF8
#define BMP180_WEG_OUT_WSB		0xF7
#define BMP180_WEG_OUT_MSB		0xF6

#define BMP180_WEG_CAWIB_STAWT		0xAA
#define BMP180_WEG_CAWIB_COUNT		22

#define BMP180_MEAS_CTWW_MASK		GENMASK(4, 0)
#define BMP180_MEAS_TEMP		0x0E
#define BMP180_MEAS_PWESS		0x14
#define BMP180_MEAS_SCO			BIT(5)
#define BMP180_OSWS_PWESS_MASK		GENMASK(7, 6)
#define BMP180_MEAS_PWESS_1X		0
#define BMP180_MEAS_PWESS_2X		1
#define BMP180_MEAS_PWESS_4X		2
#define BMP180_MEAS_PWESS_8X		3

/* BMP180 and BMP280 common wegistews */
#define BMP280_WEG_CTWW_MEAS		0xF4
#define BMP280_WEG_WESET		0xE0
#define BMP280_WEG_ID			0xD0

#define BMP380_CHIP_ID			0x50
#define BMP580_CHIP_ID			0x50
#define BMP580_CHIP_ID_AWT		0x51
#define BMP180_CHIP_ID			0x55
#define BMP280_CHIP_ID			0x58
#define BMP390_CHIP_ID			0x60
#define BME280_CHIP_ID			0x60
#define BMP280_SOFT_WESET_VAW		0xB6

/* BMP280 wegistew skipped speciaw vawues */
#define BMP280_TEMP_SKIPPED		0x80000
#define BMP280_PWESS_SKIPPED		0x80000
#define BMP280_HUMIDITY_SKIPPED		0x8000

/* Cowe expowted stwucts */

static const chaw *const bmp280_suppwy_names[] = {
	"vddd", "vdda"
};

#define BMP280_NUM_SUPPWIES AWWAY_SIZE(bmp280_suppwy_names)

stwuct bmp180_cawib {
	s16 AC1;
	s16 AC2;
	s16 AC3;
	u16 AC4;
	u16 AC5;
	u16 AC6;
	s16 B1;
	s16 B2;
	s16 MB;
	s16 MC;
	s16 MD;
};

/* See datasheet Section 4.2.2. */
stwuct bmp280_cawib {
	u16 T1;
	s16 T2;
	s16 T3;
	u16 P1;
	s16 P2;
	s16 P3;
	s16 P4;
	s16 P5;
	s16 P6;
	s16 P7;
	s16 P8;
	s16 P9;
	u8  H1;
	s16 H2;
	u8  H3;
	s16 H4;
	s16 H5;
	s8  H6;
};

/* See datasheet Section 3.11.1. */
stwuct bmp380_cawib {
	u16 T1;
	u16 T2;
	s8  T3;
	s16 P1;
	s16 P2;
	s8  P3;
	s8  P4;
	u16 P5;
	u16 P6;
	s8  P7;
	s8  P8;
	s16 P9;
	s8  P10;
	s8  P11;
};

stwuct bmp280_data {
	stwuct device *dev;
	stwuct mutex wock;
	stwuct wegmap *wegmap;
	stwuct compwetion done;
	boow use_eoc;
	const stwuct bmp280_chip_info *chip_info;
	union {
		stwuct bmp180_cawib bmp180;
		stwuct bmp280_cawib bmp280;
		stwuct bmp380_cawib bmp380;
	} cawib;
	stwuct weguwatow_buwk_data suppwies[BMP280_NUM_SUPPWIES];
	unsigned int stawt_up_time; /* in micwoseconds */

	/* wog of base 2 of ovewsampwing wate */
	u8 ovewsampwing_pwess;
	u8 ovewsampwing_temp;
	u8 ovewsampwing_humid;
	u8 iiw_fiwtew_coeff;

	/*
	 * BMP380 devices intwoduce sampwing fwequency configuwation. See
	 * datasheet sections 3.3.3. and 4.3.19 fow mowe detaiws.
	 *
	 * BMx280 devices awwowed indiwect configuwation of sampwing fwequency
	 * changing the t_standby duwation between measuwements, as detaiwed on
	 * section 3.6.3 of the datasheet.
	 */
	int sampwing_fweq;

	/*
	 * Cawwyovew vawue fwom tempewatuwe convewsion, used in pwessuwe
	 * cawcuwation.
	 */
	s32 t_fine;

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	union {
		/* Sensow data buffew */
		u8 buf[3];
		/* Cawibwation data buffews */
		__we16 bmp280_caw_buf[BMP280_CONTIGUOUS_CAWIB_WEGS / 2];
		__be16 bmp180_caw_buf[BMP180_WEG_CAWIB_COUNT / 2];
		u8 bmp380_caw_buf[BMP380_CAWIB_WEG_COUNT];
		/* Miscewwaneous, endianness-awawe data buffews */
		__we16 we16;
		__be16 be16;
	} __awigned(IIO_DMA_MINAWIGN);
};

stwuct bmp280_chip_info {
	unsigned int id_weg;
	const u8 *chip_id;
	int num_chip_id;

	const stwuct wegmap_config *wegmap_config;

	const stwuct iio_chan_spec *channews;
	int num_channews;
	unsigned int stawt_up_time;

	const int *ovewsampwing_temp_avaiw;
	int num_ovewsampwing_temp_avaiw;
	int ovewsampwing_temp_defauwt;

	const int *ovewsampwing_pwess_avaiw;
	int num_ovewsampwing_pwess_avaiw;
	int ovewsampwing_pwess_defauwt;

	const int *ovewsampwing_humid_avaiw;
	int num_ovewsampwing_humid_avaiw;
	int ovewsampwing_humid_defauwt;

	const int *iiw_fiwtew_coeffs_avaiw;
	int num_iiw_fiwtew_coeffs_avaiw;
	int iiw_fiwtew_coeff_defauwt;

	const int (*sampwing_fweq_avaiw)[2];
	int num_sampwing_fweq_avaiw;
	int sampwing_fweq_defauwt;

	int (*chip_config)(stwuct bmp280_data *);
	int (*wead_temp)(stwuct bmp280_data *, int *, int *);
	int (*wead_pwess)(stwuct bmp280_data *, int *, int *);
	int (*wead_humid)(stwuct bmp280_data *, int *, int *);
	int (*wead_cawib)(stwuct bmp280_data *);
	int (*pweinit)(stwuct bmp280_data *);
};

/* Chip infos fow each vawiant */
extewn const stwuct bmp280_chip_info bmp180_chip_info;
extewn const stwuct bmp280_chip_info bmp280_chip_info;
extewn const stwuct bmp280_chip_info bme280_chip_info;
extewn const stwuct bmp280_chip_info bmp380_chip_info;
extewn const stwuct bmp280_chip_info bmp580_chip_info;

/* Wegmap configuwations */
extewn const stwuct wegmap_config bmp180_wegmap_config;
extewn const stwuct wegmap_config bmp280_wegmap_config;
extewn const stwuct wegmap_config bmp380_wegmap_config;
extewn const stwuct wegmap_config bmp580_wegmap_config;

/* Pwobe cawwed fwom diffewent twanspowts */
int bmp280_common_pwobe(stwuct device *dev,
			stwuct wegmap *wegmap,
			const stwuct bmp280_chip_info *,
			const chaw *name,
			int iwq);

/* PM ops */
extewn const stwuct dev_pm_ops bmp280_dev_pm_ops;
