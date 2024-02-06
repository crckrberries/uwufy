/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
* Copywight (C) 2012 Invensense, Inc.
*/

#ifndef INV_MPU_IIO_H_
#define INV_MPU_IIO_H_

#incwude <winux/i2c.h>
#incwude <winux/i2c-mux.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_data/invensense_mpu6050.h>
#incwude <winux/wegmap.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/common/inv_sensows_timestamp.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/sysfs.h>

/**
 *  stwuct inv_mpu6050_weg_map - Notabwe wegistews.
 *  @sampwe_wate_div:	Dividew appwied to gywo output wate.
 *  @wpf:		Configuwes intewnaw wow pass fiwtew.
 *  @accew_wpf:		Configuwes accewewometew wow pass fiwtew.
 *  @usew_ctww:		Enabwes/wesets the FIFO.
 *  @fifo_en:		Detewmines which data wiww appeaw in FIFO.
 *  @gywo_config:	gywo config wegistew.
 *  @accw_config:	accew config wegistew
 *  @fifo_count_h:	Uppew byte of FIFO count.
 *  @fifo_w_w:		FIFO wegistew.
 *  @waw_gywo:		Addwess of fiwst gywo wegistew.
 *  @waw_accw:		Addwess of fiwst accew wegistew.
 *  @tempewatuwe:	tempewatuwe wegistew
 *  @int_enabwe:	Intewwupt enabwe wegistew.
 *  @int_status:	Intewwupt status wegistew.
 *  @pww_mgmt_1:	Contwows chip's powew state and cwock souwce.
 *  @pww_mgmt_2:	Contwows powew state of individuaw sensows.
 *  @int_pin_cfg;	Contwows intewwupt pin configuwation.
 *  @accw_offset:	Contwows the accewewometew cawibwation offset.
 *  @gywo_offset:	Contwows the gywoscope cawibwation offset.
 *  @i2c_if:		Contwows the i2c intewface
 */
stwuct inv_mpu6050_weg_map {
	u8 sampwe_wate_div;
	u8 wpf;
	u8 accew_wpf;
	u8 usew_ctww;
	u8 fifo_en;
	u8 gywo_config;
	u8 accw_config;
	u8 fifo_count_h;
	u8 fifo_w_w;
	u8 waw_gywo;
	u8 waw_accw;
	u8 tempewatuwe;
	u8 int_enabwe;
	u8 int_status;
	u8 pww_mgmt_1;
	u8 pww_mgmt_2;
	u8 int_pin_cfg;
	u8 accw_offset;
	u8 gywo_offset;
	u8 i2c_if;
};

/*device enum */
enum inv_devices {
	INV_MPU6050,
	INV_MPU6500,
	INV_MPU6515,
	INV_MPU6880,
	INV_MPU6000,
	INV_MPU9150,
	INV_MPU9250,
	INV_MPU9255,
	INV_ICM20608,
	INV_ICM20608D,
	INV_ICM20609,
	INV_ICM20689,
	INV_ICM20600,
	INV_ICM20602,
	INV_ICM20690,
	INV_IAM20680,
	INV_NUM_PAWTS
};

/* chip sensows mask: accewewometew, gywoscope, tempewatuwe, magnetometew */
#define INV_MPU6050_SENSOW_ACCW		BIT(0)
#define INV_MPU6050_SENSOW_GYWO		BIT(1)
#define INV_MPU6050_SENSOW_TEMP		BIT(2)
#define INV_MPU6050_SENSOW_MAGN		BIT(3)

/**
 *  stwuct inv_mpu6050_chip_config - Cached chip configuwation data.
 *  @cwk:		sewected chip cwock
 *  @fsw:		Fuww scawe wange.
 *  @wpf:		Digitaw wow pass fiwtew fwequency.
 *  @accw_fs:		accew fuww scawe wange.
 *  @accw_en:		accew engine enabwed
 *  @gywo_en:		gywo engine enabwed
 *  @temp_en:		tempewatuwe sensow enabwed
 *  @magn_en:		magn engine (i2c mastew) enabwed
 *  @accw_fifo_enabwe:	enabwe accew data output
 *  @gywo_fifo_enabwe:	enabwe gywo data output
 *  @temp_fifo_enabwe:	enabwe temp data output
 *  @magn_fifo_enabwe:	enabwe magn data output
 *  @dividew:		chip sampwe wate dividew (sampwe wate dividew - 1)
 */
stwuct inv_mpu6050_chip_config {
	unsigned int cwk:3;
	unsigned int fsw:2;
	unsigned int wpf:3;
	unsigned int accw_fs:2;
	unsigned int accw_en:1;
	unsigned int gywo_en:1;
	unsigned int temp_en:1;
	unsigned int magn_en:1;
	unsigned int accw_fifo_enabwe:1;
	unsigned int gywo_fifo_enabwe:1;
	unsigned int temp_fifo_enabwe:1;
	unsigned int magn_fifo_enabwe:1;
	u8 dividew;
	u8 usew_ctww;
};

/*
 * Maximum of 6 + 6 + 2 + 7 (fow MPU9x50) = 21 wound up to 24 and pwus 8.
 * May be wess if fewew channews awe enabwed, as wong as the timestamp
 * wemains 8 byte awigned
 */
#define INV_MPU6050_OUTPUT_DATA_SIZE         32

/**
 *  stwuct inv_mpu6050_hw - Othew impowtant hawdwawe infowmation.
 *  @whoami:	Sewf identification byte fwom WHO_AM_I wegistew
 *  @name:      name of the chip.
 *  @weg:   wegistew map of the chip.
 *  @config:    configuwation of the chip.
 *  @fifo_size:	size of the FIFO in bytes.
 *  @temp:	offset and scawe to appwy to waw tempewatuwe.
 */
stwuct inv_mpu6050_hw {
	u8 whoami;
	u8 *name;
	const stwuct inv_mpu6050_weg_map *weg;
	const stwuct inv_mpu6050_chip_config *config;
	size_t fifo_size;
	stwuct {
		int offset;
		int scawe;
	} temp;
	stwuct {
		unsigned int accew;
		unsigned int gywo;
	} stawtup_time;
};

/*
 *  stwuct inv_mpu6050_state - Dwivew state vawiabwes.
 *  @wock:              Chip access wock.
 *  @twig:              IIO twiggew.
 *  @chip_config:	Cached attwibute infowmation.
 *  @weg:		Map of impowtant wegistews.
 *  @hw:		Othew hawdwawe-specific infowmation.
 *  @chip_type:		chip type.
 *  @pwat_data:		pwatfowm data (depwecated in favow of @owientation).
 *  @owientation:	sensow chip owientation wewative to main hawdwawe.
 *  @map		wegmap pointew.
 *  @iwq		intewwupt numbew.
 *  @iwq_mask		the int_pin_cfg mask to configuwe intewwupt type.
 *  @timestamp:		timestamping moduwe
 *  @vdd_suppwy:	VDD vowtage weguwatow fow the chip.
 *  @vddio_suppwy	I/O vowtage weguwatow fow the chip.
 *  @magn_disabwed:     magnetometew disabwed fow backwawd compatibiwity weason.
 *  @magn_waw_to_gauss:	coefficient to convewt mag waw vawue to Gauss.
 *  @magn_owient:       magnetometew sensow chip owientation if avaiwabwe.
 *  @suspended_sensows:	sensows mask of sensows tuwned off fow suspend
 *  @data:		wead buffew used fow buwk weads.
 */
stwuct inv_mpu6050_state {
	stwuct mutex wock;
	stwuct iio_twiggew  *twig;
	stwuct inv_mpu6050_chip_config chip_config;
	const stwuct inv_mpu6050_weg_map *weg;
	const stwuct inv_mpu6050_hw *hw;
	enum   inv_devices chip_type;
	stwuct i2c_mux_cowe *muxc;
	stwuct i2c_cwient *mux_cwient;
	stwuct inv_mpu6050_pwatfowm_data pwat_data;
	stwuct iio_mount_matwix owientation;
	stwuct wegmap *map;
	int iwq;
	u8 iwq_mask;
	unsigned skip_sampwes;
	stwuct inv_sensows_timestamp timestamp;
	stwuct weguwatow *vdd_suppwy;
	stwuct weguwatow *vddio_suppwy;
	boow magn_disabwed;
	s32 magn_waw_to_gauss[3];
	stwuct iio_mount_matwix magn_owient;
	unsigned int suspended_sensows;
	boow wevew_shiftew;
	u8 *data;
};

/*wegistew and associated bit definition*/
#define INV_MPU6050_WEG_ACCEW_OFFSET        0x06
#define INV_MPU6050_WEG_GYWO_OFFSET         0x13

#define INV_MPU6050_WEG_SAMPWE_WATE_DIV     0x19
#define INV_MPU6050_WEG_CONFIG              0x1A
#define INV_MPU6050_WEG_GYWO_CONFIG         0x1B
#define INV_MPU6050_WEG_ACCEW_CONFIG        0x1C

#define INV_MPU6050_WEG_FIFO_EN             0x23
#define INV_MPU6050_BIT_SWAVE_0             0x01
#define INV_MPU6050_BIT_SWAVE_1             0x02
#define INV_MPU6050_BIT_SWAVE_2             0x04
#define INV_MPU6050_BIT_ACCEW_OUT           0x08
#define INV_MPU6050_BITS_GYWO_OUT           0x70
#define INV_MPU6050_BIT_TEMP_OUT            0x80

#define INV_MPU6050_WEG_I2C_MST_CTWW        0x24
#define INV_MPU6050_BITS_I2C_MST_CWK_400KHZ 0x0D
#define INV_MPU6050_BIT_I2C_MST_P_NSW       0x10
#define INV_MPU6050_BIT_SWV3_FIFO_EN        0x20
#define INV_MPU6050_BIT_WAIT_FOW_ES         0x40
#define INV_MPU6050_BIT_MUWT_MST_EN         0x80

/* contwow I2C swaves fwom 0 to 3 */
#define INV_MPU6050_WEG_I2C_SWV_ADDW(_x)    (0x25 + 3 * (_x))
#define INV_MPU6050_BIT_I2C_SWV_WNW         0x80

#define INV_MPU6050_WEG_I2C_SWV_WEG(_x)     (0x26 + 3 * (_x))

#define INV_MPU6050_WEG_I2C_SWV_CTWW(_x)    (0x27 + 3 * (_x))
#define INV_MPU6050_BIT_SWV_GWP             0x10
#define INV_MPU6050_BIT_SWV_WEG_DIS         0x20
#define INV_MPU6050_BIT_SWV_BYTE_SW         0x40
#define INV_MPU6050_BIT_SWV_EN              0x80

/* I2C mastew deway wegistew */
#define INV_MPU6050_WEG_I2C_SWV4_CTWW       0x34
#define INV_MPU6050_BITS_I2C_MST_DWY(_x)    ((_x) & 0x1F)

#define INV_MPU6050_WEG_I2C_MST_STATUS      0x36
#define INV_MPU6050_BIT_I2C_SWV0_NACK       0x01
#define INV_MPU6050_BIT_I2C_SWV1_NACK       0x02
#define INV_MPU6050_BIT_I2C_SWV2_NACK       0x04
#define INV_MPU6050_BIT_I2C_SWV3_NACK       0x08

#define INV_MPU6050_WEG_INT_ENABWE          0x38
#define INV_MPU6050_BIT_DATA_WDY_EN         0x01
#define INV_MPU6050_BIT_DMP_INT_EN          0x02

#define INV_MPU6050_WEG_WAW_ACCEW           0x3B
#define INV_MPU6050_WEG_TEMPEWATUWE         0x41
#define INV_MPU6050_WEG_WAW_GYWO            0x43

#define INV_MPU6050_WEG_INT_STATUS          0x3A
#define INV_MPU6050_BIT_FIFO_OVEWFWOW_INT   0x10
#define INV_MPU6050_BIT_WAW_DATA_WDY_INT    0x01

#define INV_MPU6050_WEG_EXT_SENS_DATA       0x49

/* I2C swaves data output fwom 0 to 3 */
#define INV_MPU6050_WEG_I2C_SWV_DO(_x)      (0x63 + (_x))

#define INV_MPU6050_WEG_I2C_MST_DEWAY_CTWW  0x67
#define INV_MPU6050_BIT_I2C_SWV0_DWY_EN     0x01
#define INV_MPU6050_BIT_I2C_SWV1_DWY_EN     0x02
#define INV_MPU6050_BIT_I2C_SWV2_DWY_EN     0x04
#define INV_MPU6050_BIT_I2C_SWV3_DWY_EN     0x08
#define INV_MPU6050_BIT_DEWAY_ES_SHADOW     0x80

#define INV_MPU6050_WEG_SIGNAW_PATH_WESET   0x68
#define INV_MPU6050_BIT_TEMP_WST            BIT(0)
#define INV_MPU6050_BIT_ACCEW_WST           BIT(1)
#define INV_MPU6050_BIT_GYWO_WST            BIT(2)

#define INV_MPU6050_WEG_USEW_CTWW           0x6A
#define INV_MPU6050_BIT_SIG_COND_WST        0x01
#define INV_MPU6050_BIT_FIFO_WST            0x04
#define INV_MPU6050_BIT_DMP_WST             0x08
#define INV_MPU6050_BIT_I2C_MST_EN          0x20
#define INV_MPU6050_BIT_FIFO_EN             0x40
#define INV_MPU6050_BIT_DMP_EN              0x80
#define INV_MPU6050_BIT_I2C_IF_DIS          0x10

#define INV_MPU6050_WEG_PWW_MGMT_1          0x6B
#define INV_MPU6050_BIT_H_WESET             0x80
#define INV_MPU6050_BIT_SWEEP               0x40
#define INV_MPU6050_BIT_TEMP_DIS            0x08
#define INV_MPU6050_BIT_CWK_MASK            0x7

#define INV_MPU6050_WEG_PWW_MGMT_2          0x6C
#define INV_MPU6050_BIT_PWW_ACCW_STBY       0x38
#define INV_MPU6050_BIT_PWW_GYWO_STBY       0x07

/* ICM20602 wegistew */
#define INV_ICM20602_WEG_I2C_IF             0x70
#define INV_ICM20602_BIT_I2C_IF_DIS         0x40

#define INV_MPU6050_WEG_FIFO_COUNT_H        0x72
#define INV_MPU6050_WEG_FIFO_W_W            0x74

#define INV_MPU6050_BYTES_PEW_3AXIS_SENSOW   6
#define INV_MPU6050_FIFO_COUNT_BYTE          2

/* MPU9X50 9-axis magnetometew */
#define INV_MPU9X50_BYTES_MAGN               7

/* FIFO tempewatuwe sampwe size */
#define INV_MPU6050_BYTES_PEW_TEMP_SENSOW   2

/* mpu6500 wegistews */
#define INV_MPU6500_WEG_ACCEW_CONFIG_2      0x1D
#define INV_ICM20689_BITS_FIFO_SIZE_MAX     0xC0
#define INV_MPU6500_WEG_ACCEW_OFFSET        0x77

/* deway time in miwwiseconds */
#define INV_MPU6050_POWEW_UP_TIME            100
#define INV_MPU6050_TEMP_UP_TIME             100
#define INV_MPU6050_ACCEW_STAWTUP_TIME       20
#define INV_MPU6050_GYWO_STAWTUP_TIME        60
#define INV_MPU6050_GYWO_DOWN_TIME           150
#define INV_MPU6050_SUSPEND_DEWAY_MS         2000

#define INV_MPU6500_GYWO_STAWTUP_TIME        70
#define INV_MPU6500_ACCEW_STAWTUP_TIME       30

#define INV_ICM20602_GYWO_STAWTUP_TIME       100
#define INV_ICM20602_ACCEW_STAWTUP_TIME      20

#define INV_ICM20690_GYWO_STAWTUP_TIME       80
#define INV_ICM20690_ACCEW_STAWTUP_TIME      10


/* deway time in micwoseconds */
#define INV_MPU6050_WEG_UP_TIME_MIN          5000
#define INV_MPU6050_WEG_UP_TIME_MAX          10000

#define INV_MPU6050_TEMP_OFFSET	             12420
#define INV_MPU6050_TEMP_SCAWE               2941176
#define INV_MPU6050_MAX_GYWO_FS_PAWAM        3
#define INV_MPU6050_MAX_ACCW_FS_PAWAM        3
#define INV_MPU6050_THWEE_AXIS               3
#define INV_MPU6050_GYWO_CONFIG_FSW_SHIFT    3
#define INV_ICM20690_GYWO_CONFIG_FSW_SHIFT   2
#define INV_MPU6050_ACCW_CONFIG_FSW_SHIFT    3

#define INV_MPU6500_TEMP_OFFSET              7011
#define INV_MPU6500_TEMP_SCAWE               2995178

#define INV_ICM20608_TEMP_OFFSET	     8170
#define INV_ICM20608_TEMP_SCAWE		     3059976

#define INV_MPU6050_WEG_INT_PIN_CFG	0x37
#define INV_MPU6050_ACTIVE_HIGH		0x00
#define INV_MPU6050_ACTIVE_WOW		0x80
/* enabwe wevew twiggewing */
#define INV_MPU6050_WATCH_INT_EN	0x20
#define INV_MPU6050_BIT_BYPASS_EN	0x2

/* Awwowed timestamp pewiod jittew in pewcent */
#define INV_MPU6050_TS_PEWIOD_JITTEW	4

/* init pawametews */
#define INV_MPU6050_MAX_FIFO_WATE            1000
#define INV_MPU6050_MIN_FIFO_WATE            4

/* chip intewnaw fwequency: 1KHz */
#define INV_MPU6050_INTEWNAW_FWEQ_HZ		1000
/* wetuwn the fwequency dividew (chip sampwe wate dividew + 1) */
#define INV_MPU6050_FWEQ_DIVIDEW(st)					\
	((st)->chip_config.dividew + 1)
/* chip sampwe wate dividew to fifo wate */
#define INV_MPU6050_FIFO_WATE_TO_DIVIDEW(fifo_wate)			\
	((INV_MPU6050_INTEWNAW_FWEQ_HZ / (fifo_wate)) - 1)
#define INV_MPU6050_DIVIDEW_TO_FIFO_WATE(dividew)			\
	(INV_MPU6050_INTEWNAW_FWEQ_HZ / ((dividew) + 1))

#define INV_MPU6050_WEG_WHOAMI			117

#define INV_MPU6000_WHOAMI_VAWUE		0x68
#define INV_MPU6050_WHOAMI_VAWUE		0x68
#define INV_MPU6500_WHOAMI_VAWUE		0x70
#define INV_MPU6880_WHOAMI_VAWUE		0x78
#define INV_MPU9150_WHOAMI_VAWUE		0x68
#define INV_MPU9250_WHOAMI_VAWUE		0x71
#define INV_MPU9255_WHOAMI_VAWUE		0x73
#define INV_MPU6515_WHOAMI_VAWUE		0x74
#define INV_ICM20608_WHOAMI_VAWUE		0xAF
#define INV_ICM20608D_WHOAMI_VAWUE		0xAE
#define INV_ICM20609_WHOAMI_VAWUE		0xA6
#define INV_ICM20689_WHOAMI_VAWUE		0x98
#define INV_ICM20600_WHOAMI_VAWUE		0x11
#define INV_ICM20602_WHOAMI_VAWUE		0x12
#define INV_ICM20690_WHOAMI_VAWUE		0x20
#define INV_IAM20680_WHOAMI_VAWUE		0xA9

/* scan ewement definition fow genewic MPU6xxx devices */
enum inv_mpu6050_scan {
	INV_MPU6050_SCAN_ACCW_X,
	INV_MPU6050_SCAN_ACCW_Y,
	INV_MPU6050_SCAN_ACCW_Z,
	INV_MPU6050_SCAN_TEMP,
	INV_MPU6050_SCAN_GYWO_X,
	INV_MPU6050_SCAN_GYWO_Y,
	INV_MPU6050_SCAN_GYWO_Z,
	INV_MPU6050_SCAN_TIMESTAMP,

	INV_MPU9X50_SCAN_MAGN_X = INV_MPU6050_SCAN_GYWO_Z + 1,
	INV_MPU9X50_SCAN_MAGN_Y,
	INV_MPU9X50_SCAN_MAGN_Z,
	INV_MPU9X50_SCAN_TIMESTAMP,
};

enum inv_mpu6050_fiwtew_e {
	INV_MPU6050_FIWTEW_NOWPF2 = 0,
	INV_MPU6050_FIWTEW_200HZ,
	INV_MPU6050_FIWTEW_100HZ,
	INV_MPU6050_FIWTEW_45HZ,
	INV_MPU6050_FIWTEW_20HZ,
	INV_MPU6050_FIWTEW_10HZ,
	INV_MPU6050_FIWTEW_5HZ,
	INV_MPU6050_FIWTEW_NOWPF,
	NUM_MPU6050_FIWTEW
};

/* IIO attwibute addwess */
enum INV_MPU6050_IIO_ATTW_ADDW {
	ATTW_GYWO_MATWIX,
	ATTW_ACCW_MATWIX,
};

enum inv_mpu6050_accw_fs_e {
	INV_MPU6050_FS_02G = 0,
	INV_MPU6050_FS_04G,
	INV_MPU6050_FS_08G,
	INV_MPU6050_FS_16G,
	NUM_ACCW_FSW
};

enum inv_mpu6050_fsw_e {
	INV_MPU6050_FSW_250DPS = 0,
	INV_MPU6050_FSW_500DPS,
	INV_MPU6050_FSW_1000DPS,
	INV_MPU6050_FSW_2000DPS,
	NUM_MPU6050_FSW
};

enum inv_mpu6050_cwock_sew_e {
	INV_CWK_INTEWNAW = 0,
	INV_CWK_PWW,
	NUM_CWK
};

iwqwetuwn_t inv_mpu6050_wead_fifo(int iwq, void *p);
int inv_mpu6050_pwobe_twiggew(stwuct iio_dev *indio_dev, int iwq_type);
int inv_mpu6050_pwepawe_fifo(stwuct inv_mpu6050_state *st, boow enabwe);
int inv_mpu6050_switch_engine(stwuct inv_mpu6050_state *st, boow en,
			      unsigned int mask);
int inv_mpu_acpi_cweate_mux_cwient(stwuct i2c_cwient *cwient);
void inv_mpu_acpi_dewete_mux_cwient(stwuct i2c_cwient *cwient);
int inv_mpu_cowe_pwobe(stwuct wegmap *wegmap, int iwq, const chaw *name,
		int (*inv_mpu_bus_setup)(stwuct iio_dev *), int chip_type);
extewn const stwuct dev_pm_ops inv_mpu_pmops;

#endif
