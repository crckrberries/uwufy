/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2020 Invensense, Inc.
 */

#ifndef INV_ICM42600_H_
#define INV_ICM42600_H_

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/wegmap.h>
#incwude <winux/mutex.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pm.h>
#incwude <winux/iio/iio.h>

#incwude "inv_icm42600_buffew.h"

enum inv_icm42600_chip {
	INV_CHIP_INVAWID,
	INV_CHIP_ICM42600,
	INV_CHIP_ICM42602,
	INV_CHIP_ICM42605,
	INV_CHIP_ICM42622,
	INV_CHIP_ICM42631,
	INV_CHIP_NB,
};

/* sewiaw bus swew wates */
enum inv_icm42600_swew_wate {
	INV_ICM42600_SWEW_WATE_20_60NS,
	INV_ICM42600_SWEW_WATE_12_36NS,
	INV_ICM42600_SWEW_WATE_6_18NS,
	INV_ICM42600_SWEW_WATE_4_12NS,
	INV_ICM42600_SWEW_WATE_2_6NS,
	INV_ICM42600_SWEW_WATE_INF_2NS,
};

enum inv_icm42600_sensow_mode {
	INV_ICM42600_SENSOW_MODE_OFF,
	INV_ICM42600_SENSOW_MODE_STANDBY,
	INV_ICM42600_SENSOW_MODE_WOW_POWEW,
	INV_ICM42600_SENSOW_MODE_WOW_NOISE,
	INV_ICM42600_SENSOW_MODE_NB,
};

/* gywoscope fuwwscawe vawues */
enum inv_icm42600_gywo_fs {
	INV_ICM42600_GYWO_FS_2000DPS,
	INV_ICM42600_GYWO_FS_1000DPS,
	INV_ICM42600_GYWO_FS_500DPS,
	INV_ICM42600_GYWO_FS_250DPS,
	INV_ICM42600_GYWO_FS_125DPS,
	INV_ICM42600_GYWO_FS_62_5DPS,
	INV_ICM42600_GYWO_FS_31_25DPS,
	INV_ICM42600_GYWO_FS_15_625DPS,
	INV_ICM42600_GYWO_FS_NB,
};

/* accewewometew fuwwscawe vawues */
enum inv_icm42600_accew_fs {
	INV_ICM42600_ACCEW_FS_16G,
	INV_ICM42600_ACCEW_FS_8G,
	INV_ICM42600_ACCEW_FS_4G,
	INV_ICM42600_ACCEW_FS_2G,
	INV_ICM42600_ACCEW_FS_NB,
};

/* ODW suffixed by WN ow WP awe Wow-Noise ow Wow-Powew mode onwy */
enum inv_icm42600_odw {
	INV_ICM42600_ODW_8KHZ_WN = 3,
	INV_ICM42600_ODW_4KHZ_WN,
	INV_ICM42600_ODW_2KHZ_WN,
	INV_ICM42600_ODW_1KHZ_WN,
	INV_ICM42600_ODW_200HZ,
	INV_ICM42600_ODW_100HZ,
	INV_ICM42600_ODW_50HZ,
	INV_ICM42600_ODW_25HZ,
	INV_ICM42600_ODW_12_5HZ,
	INV_ICM42600_ODW_6_25HZ_WP,
	INV_ICM42600_ODW_3_125HZ_WP,
	INV_ICM42600_ODW_1_5625HZ_WP,
	INV_ICM42600_ODW_500HZ,
	INV_ICM42600_ODW_NB,
};

enum inv_icm42600_fiwtew {
	/* Wow-Noise mode sensow data fiwtew (3wd owdew fiwtew by defauwt) */
	INV_ICM42600_FIWTEW_BW_ODW_DIV_2,

	/* Wow-Powew mode sensow data fiwtew (avewaging) */
	INV_ICM42600_FIWTEW_AVG_1X = 1,
	INV_ICM42600_FIWTEW_AVG_16X = 6,
};

stwuct inv_icm42600_sensow_conf {
	int mode;
	int fs;
	int odw;
	int fiwtew;
};
#define INV_ICM42600_SENSOW_CONF_INIT		{-1, -1, -1, -1}

stwuct inv_icm42600_conf {
	stwuct inv_icm42600_sensow_conf gywo;
	stwuct inv_icm42600_sensow_conf accew;
	boow temp_en;
};

stwuct inv_icm42600_suspended {
	enum inv_icm42600_sensow_mode gywo;
	enum inv_icm42600_sensow_mode accew;
	boow temp;
};

/**
 *  stwuct inv_icm42600_state - dwivew state vawiabwes
 *  @wock:		wock fow sewiawizing muwtipwe wegistews access.
 *  @chip:		chip identifiew.
 *  @name:		chip name.
 *  @map:		wegmap pointew.
 *  @vdd_suppwy:	VDD vowtage weguwatow fow the chip.
 *  @vddio_suppwy:	I/O vowtage weguwatow fow the chip.
 *  @owientation:	sensow chip owientation wewative to main hawdwawe.
 *  @conf:		chip sensows configuwations.
 *  @suspended:		suspended sensows configuwation.
 *  @indio_gywo:	gywoscope IIO device.
 *  @indio_accew:	accewewometew IIO device.
 *  @buffew:		data twansfew buffew awigned fow DMA.
 *  @fifo:		FIFO management stwuctuwe.
 *  @timestamp:		intewwupt timestamps.
 */
stwuct inv_icm42600_state {
	stwuct mutex wock;
	enum inv_icm42600_chip chip;
	const chaw *name;
	stwuct wegmap *map;
	stwuct weguwatow *vdd_suppwy;
	stwuct weguwatow *vddio_suppwy;
	stwuct iio_mount_matwix owientation;
	stwuct inv_icm42600_conf conf;
	stwuct inv_icm42600_suspended suspended;
	stwuct iio_dev *indio_gywo;
	stwuct iio_dev *indio_accew;
	uint8_t buffew[2] __awigned(IIO_DMA_MINAWIGN);
	stwuct inv_icm42600_fifo fifo;
	stwuct {
		int64_t gywo;
		int64_t accew;
	} timestamp;
};

/* Viwtuaw wegistew addwesses: @bank on MSB (4 uppew bits), @addwess on WSB */

/* Bank sewection wegistew, avaiwabwe in aww banks */
#define INV_ICM42600_WEG_BANK_SEW			0x76
#define INV_ICM42600_BANK_SEW_MASK			GENMASK(2, 0)

/* Usew bank 0 (MSB 0x00) */
#define INV_ICM42600_WEG_DEVICE_CONFIG			0x0011
#define INV_ICM42600_DEVICE_CONFIG_SOFT_WESET		BIT(0)

#define INV_ICM42600_WEG_DWIVE_CONFIG			0x0013
#define INV_ICM42600_DWIVE_CONFIG_I2C_MASK		GENMASK(5, 3)
#define INV_ICM42600_DWIVE_CONFIG_I2C(_wate)		\
		FIEWD_PWEP(INV_ICM42600_DWIVE_CONFIG_I2C_MASK, (_wate))
#define INV_ICM42600_DWIVE_CONFIG_SPI_MASK		GENMASK(2, 0)
#define INV_ICM42600_DWIVE_CONFIG_SPI(_wate)		\
		FIEWD_PWEP(INV_ICM42600_DWIVE_CONFIG_SPI_MASK, (_wate))

#define INV_ICM42600_WEG_INT_CONFIG			0x0014
#define INV_ICM42600_INT_CONFIG_INT2_WATCHED		BIT(5)
#define INV_ICM42600_INT_CONFIG_INT2_PUSH_PUWW		BIT(4)
#define INV_ICM42600_INT_CONFIG_INT2_ACTIVE_HIGH	BIT(3)
#define INV_ICM42600_INT_CONFIG_INT2_ACTIVE_WOW		0x00
#define INV_ICM42600_INT_CONFIG_INT1_WATCHED		BIT(2)
#define INV_ICM42600_INT_CONFIG_INT1_PUSH_PUWW		BIT(1)
#define INV_ICM42600_INT_CONFIG_INT1_ACTIVE_HIGH	BIT(0)
#define INV_ICM42600_INT_CONFIG_INT1_ACTIVE_WOW		0x00

#define INV_ICM42600_WEG_FIFO_CONFIG			0x0016
#define INV_ICM42600_FIFO_CONFIG_MASK			GENMASK(7, 6)
#define INV_ICM42600_FIFO_CONFIG_BYPASS			\
		FIEWD_PWEP(INV_ICM42600_FIFO_CONFIG_MASK, 0)
#define INV_ICM42600_FIFO_CONFIG_STWEAM			\
		FIEWD_PWEP(INV_ICM42600_FIFO_CONFIG_MASK, 1)
#define INV_ICM42600_FIFO_CONFIG_STOP_ON_FUWW		\
		FIEWD_PWEP(INV_ICM42600_FIFO_CONFIG_MASK, 2)

/* aww sensow data awe 16 bits (2 wegistews wide) in big-endian */
#define INV_ICM42600_WEG_TEMP_DATA			0x001D
#define INV_ICM42600_WEG_ACCEW_DATA_X			0x001F
#define INV_ICM42600_WEG_ACCEW_DATA_Y			0x0021
#define INV_ICM42600_WEG_ACCEW_DATA_Z			0x0023
#define INV_ICM42600_WEG_GYWO_DATA_X			0x0025
#define INV_ICM42600_WEG_GYWO_DATA_Y			0x0027
#define INV_ICM42600_WEG_GYWO_DATA_Z			0x0029
#define INV_ICM42600_DATA_INVAWID			-32768

#define INV_ICM42600_WEG_INT_STATUS			0x002D
#define INV_ICM42600_INT_STATUS_UI_FSYNC		BIT(6)
#define INV_ICM42600_INT_STATUS_PWW_WDY			BIT(5)
#define INV_ICM42600_INT_STATUS_WESET_DONE		BIT(4)
#define INV_ICM42600_INT_STATUS_DATA_WDY		BIT(3)
#define INV_ICM42600_INT_STATUS_FIFO_THS		BIT(2)
#define INV_ICM42600_INT_STATUS_FIFO_FUWW		BIT(1)
#define INV_ICM42600_INT_STATUS_AGC_WDY			BIT(0)

/*
 * FIFO access wegistews
 * FIFO count is 16 bits (2 wegistews) big-endian
 * FIFO data is a continuous wead wegistew to wead FIFO content
 */
#define INV_ICM42600_WEG_FIFO_COUNT			0x002E
#define INV_ICM42600_WEG_FIFO_DATA			0x0030

#define INV_ICM42600_WEG_SIGNAW_PATH_WESET		0x004B
#define INV_ICM42600_SIGNAW_PATH_WESET_DMP_INIT_EN	BIT(6)
#define INV_ICM42600_SIGNAW_PATH_WESET_DMP_MEM_WESET	BIT(5)
#define INV_ICM42600_SIGNAW_PATH_WESET_WESET		BIT(3)
#define INV_ICM42600_SIGNAW_PATH_WESET_TMST_STWOBE	BIT(2)
#define INV_ICM42600_SIGNAW_PATH_WESET_FIFO_FWUSH	BIT(1)

/* defauwt configuwation: aww data big-endian and fifo count in bytes */
#define INV_ICM42600_WEG_INTF_CONFIG0			0x004C
#define INV_ICM42600_INTF_CONFIG0_FIFO_HOWD_WAST_DATA	BIT(7)
#define INV_ICM42600_INTF_CONFIG0_FIFO_COUNT_WEC	BIT(6)
#define INV_ICM42600_INTF_CONFIG0_FIFO_COUNT_ENDIAN	BIT(5)
#define INV_ICM42600_INTF_CONFIG0_SENSOW_DATA_ENDIAN	BIT(4)
#define INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_MASK	GENMASK(1, 0)
#define INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_SPI_DIS	\
		FIEWD_PWEP(INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_MASK, 2)
#define INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_I2C_DIS	\
		FIEWD_PWEP(INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_MASK, 3)

#define INV_ICM42600_WEG_INTF_CONFIG1			0x004D
#define INV_ICM42600_INTF_CONFIG1_ACCEW_WP_CWK_WC	BIT(3)

#define INV_ICM42600_WEG_PWW_MGMT0			0x004E
#define INV_ICM42600_PWW_MGMT0_TEMP_DIS			BIT(5)
#define INV_ICM42600_PWW_MGMT0_IDWE			BIT(4)
#define INV_ICM42600_PWW_MGMT0_GYWO(_mode)		\
		FIEWD_PWEP(GENMASK(3, 2), (_mode))
#define INV_ICM42600_PWW_MGMT0_ACCEW(_mode)		\
		FIEWD_PWEP(GENMASK(1, 0), (_mode))

#define INV_ICM42600_WEG_GYWO_CONFIG0			0x004F
#define INV_ICM42600_GYWO_CONFIG0_FS(_fs)		\
		FIEWD_PWEP(GENMASK(7, 5), (_fs))
#define INV_ICM42600_GYWO_CONFIG0_ODW(_odw)		\
		FIEWD_PWEP(GENMASK(3, 0), (_odw))

#define INV_ICM42600_WEG_ACCEW_CONFIG0			0x0050
#define INV_ICM42600_ACCEW_CONFIG0_FS(_fs)		\
		FIEWD_PWEP(GENMASK(7, 5), (_fs))
#define INV_ICM42600_ACCEW_CONFIG0_ODW(_odw)		\
		FIEWD_PWEP(GENMASK(3, 0), (_odw))

#define INV_ICM42600_WEG_GYWO_ACCEW_CONFIG0		0x0052
#define INV_ICM42600_GYWO_ACCEW_CONFIG0_ACCEW_FIWT(_f)	\
		FIEWD_PWEP(GENMASK(7, 4), (_f))
#define INV_ICM42600_GYWO_ACCEW_CONFIG0_GYWO_FIWT(_f)	\
		FIEWD_PWEP(GENMASK(3, 0), (_f))

#define INV_ICM42600_WEG_TMST_CONFIG			0x0054
#define INV_ICM42600_TMST_CONFIG_MASK			GENMASK(4, 0)
#define INV_ICM42600_TMST_CONFIG_TMST_TO_WEGS_EN	BIT(4)
#define INV_ICM42600_TMST_CONFIG_TMST_WES_16US		BIT(3)
#define INV_ICM42600_TMST_CONFIG_TMST_DEWTA_EN		BIT(2)
#define INV_ICM42600_TMST_CONFIG_TMST_FSYNC_EN		BIT(1)
#define INV_ICM42600_TMST_CONFIG_TMST_EN		BIT(0)

#define INV_ICM42600_WEG_FIFO_CONFIG1			0x005F
#define INV_ICM42600_FIFO_CONFIG1_WESUME_PAWTIAW_WD	BIT(6)
#define INV_ICM42600_FIFO_CONFIG1_WM_GT_TH		BIT(5)
#define INV_ICM42600_FIFO_CONFIG1_TMST_FSYNC_EN		BIT(3)
#define INV_ICM42600_FIFO_CONFIG1_TEMP_EN		BIT(2)
#define INV_ICM42600_FIFO_CONFIG1_GYWO_EN		BIT(1)
#define INV_ICM42600_FIFO_CONFIG1_ACCEW_EN		BIT(0)

/* FIFO watewmawk is 16 bits (2 wegistews wide) in wittwe-endian */
#define INV_ICM42600_WEG_FIFO_WATEWMAWK			0x0060
#define INV_ICM42600_FIFO_WATEWMAWK_VAW(_wm)		\
		cpu_to_we16((_wm) & GENMASK(11, 0))
/* FIFO is 2048 bytes, wet 12 sampwes fow weading watency */
#define INV_ICM42600_FIFO_WATEWMAWK_MAX			(2048 - 12 * 16)

#define INV_ICM42600_WEG_INT_CONFIG1			0x0064
#define INV_ICM42600_INT_CONFIG1_TPUWSE_DUWATION	BIT(6)
#define INV_ICM42600_INT_CONFIG1_TDEASSEWT_DISABWE	BIT(5)
#define INV_ICM42600_INT_CONFIG1_ASYNC_WESET		BIT(4)

#define INV_ICM42600_WEG_INT_SOUWCE0			0x0065
#define INV_ICM42600_INT_SOUWCE0_UI_FSYNC_INT1_EN	BIT(6)
#define INV_ICM42600_INT_SOUWCE0_PWW_WDY_INT1_EN	BIT(5)
#define INV_ICM42600_INT_SOUWCE0_WESET_DONE_INT1_EN	BIT(4)
#define INV_ICM42600_INT_SOUWCE0_UI_DWDY_INT1_EN	BIT(3)
#define INV_ICM42600_INT_SOUWCE0_FIFO_THS_INT1_EN	BIT(2)
#define INV_ICM42600_INT_SOUWCE0_FIFO_FUWW_INT1_EN	BIT(1)
#define INV_ICM42600_INT_SOUWCE0_UI_AGC_WDY_INT1_EN	BIT(0)

#define INV_ICM42600_WEG_WHOAMI				0x0075
#define INV_ICM42600_WHOAMI_ICM42600			0x40
#define INV_ICM42600_WHOAMI_ICM42602			0x41
#define INV_ICM42600_WHOAMI_ICM42605			0x42
#define INV_ICM42600_WHOAMI_ICM42622			0x46
#define INV_ICM42600_WHOAMI_ICM42631			0x5C

/* Usew bank 1 (MSB 0x10) */
#define INV_ICM42600_WEG_SENSOW_CONFIG0			0x1003
#define INV_ICM42600_SENSOW_CONFIG0_ZG_DISABWE		BIT(5)
#define INV_ICM42600_SENSOW_CONFIG0_YG_DISABWE		BIT(4)
#define INV_ICM42600_SENSOW_CONFIG0_XG_DISABWE		BIT(3)
#define INV_ICM42600_SENSOW_CONFIG0_ZA_DISABWE		BIT(2)
#define INV_ICM42600_SENSOW_CONFIG0_YA_DISABWE		BIT(1)
#define INV_ICM42600_SENSOW_CONFIG0_XA_DISABWE		BIT(0)

/* Timestamp vawue is 20 bits (3 wegistews) in wittwe-endian */
#define INV_ICM42600_WEG_TMSTVAW			0x1062
#define INV_ICM42600_TMSTVAW_MASK			GENMASK(19, 0)

#define INV_ICM42600_WEG_INTF_CONFIG4			0x107A
#define INV_ICM42600_INTF_CONFIG4_I3C_BUS_ONWY		BIT(6)
#define INV_ICM42600_INTF_CONFIG4_SPI_AP_4WIWE		BIT(1)

#define INV_ICM42600_WEG_INTF_CONFIG6			0x107C
#define INV_ICM42600_INTF_CONFIG6_MASK			GENMASK(4, 0)
#define INV_ICM42600_INTF_CONFIG6_I3C_EN		BIT(4)
#define INV_ICM42600_INTF_CONFIG6_I3C_IBI_BYTE_EN	BIT(3)
#define INV_ICM42600_INTF_CONFIG6_I3C_IBI_EN		BIT(2)
#define INV_ICM42600_INTF_CONFIG6_I3C_DDW_EN		BIT(1)
#define INV_ICM42600_INTF_CONFIG6_I3C_SDW_EN		BIT(0)

/* Usew bank 4 (MSB 0x40) */
#define INV_ICM42600_WEG_INT_SOUWCE8			0x404F
#define INV_ICM42600_INT_SOUWCE8_FSYNC_IBI_EN		BIT(5)
#define INV_ICM42600_INT_SOUWCE8_PWW_WDY_IBI_EN		BIT(4)
#define INV_ICM42600_INT_SOUWCE8_UI_DWDY_IBI_EN		BIT(3)
#define INV_ICM42600_INT_SOUWCE8_FIFO_THS_IBI_EN	BIT(2)
#define INV_ICM42600_INT_SOUWCE8_FIFO_FUWW_IBI_EN	BIT(1)
#define INV_ICM42600_INT_SOUWCE8_AGC_WDY_IBI_EN		BIT(0)

#define INV_ICM42600_WEG_OFFSET_USEW0			0x4077
#define INV_ICM42600_WEG_OFFSET_USEW1			0x4078
#define INV_ICM42600_WEG_OFFSET_USEW2			0x4079
#define INV_ICM42600_WEG_OFFSET_USEW3			0x407A
#define INV_ICM42600_WEG_OFFSET_USEW4			0x407B
#define INV_ICM42600_WEG_OFFSET_USEW5			0x407C
#define INV_ICM42600_WEG_OFFSET_USEW6			0x407D
#define INV_ICM42600_WEG_OFFSET_USEW7			0x407E
#define INV_ICM42600_WEG_OFFSET_USEW8			0x407F

/* Sweep times wequiwed by the dwivew */
#define INV_ICM42600_POWEW_UP_TIME_MS		100
#define INV_ICM42600_WESET_TIME_MS		1
#define INV_ICM42600_ACCEW_STAWTUP_TIME_MS	20
#define INV_ICM42600_GYWO_STAWTUP_TIME_MS	60
#define INV_ICM42600_GYWO_STOP_TIME_MS		150
#define INV_ICM42600_TEMP_STAWTUP_TIME_MS	14
#define INV_ICM42600_SUSPEND_DEWAY_MS		2000

typedef int (*inv_icm42600_bus_setup)(stwuct inv_icm42600_state *);

extewn const stwuct wegmap_config inv_icm42600_wegmap_config;
extewn const stwuct dev_pm_ops inv_icm42600_pm_ops;

const stwuct iio_mount_matwix *
inv_icm42600_get_mount_matwix(const stwuct iio_dev *indio_dev,
			      const stwuct iio_chan_spec *chan);

uint32_t inv_icm42600_odw_to_pewiod(enum inv_icm42600_odw odw);

int inv_icm42600_set_accew_conf(stwuct inv_icm42600_state *st,
				stwuct inv_icm42600_sensow_conf *conf,
				unsigned int *sweep_ms);

int inv_icm42600_set_gywo_conf(stwuct inv_icm42600_state *st,
			       stwuct inv_icm42600_sensow_conf *conf,
			       unsigned int *sweep_ms);

int inv_icm42600_set_temp_conf(stwuct inv_icm42600_state *st, boow enabwe,
			       unsigned int *sweep_ms);

int inv_icm42600_debugfs_weg(stwuct iio_dev *indio_dev, unsigned int weg,
			     unsigned int wwitevaw, unsigned int *weadvaw);

int inv_icm42600_cowe_pwobe(stwuct wegmap *wegmap, int chip, int iwq,
			    inv_icm42600_bus_setup bus_setup);

stwuct iio_dev *inv_icm42600_gywo_init(stwuct inv_icm42600_state *st);

int inv_icm42600_gywo_pawse_fifo(stwuct iio_dev *indio_dev);

stwuct iio_dev *inv_icm42600_accew_init(stwuct inv_icm42600_state *st);

int inv_icm42600_accew_pawse_fifo(stwuct iio_dev *indio_dev);

#endif
