// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics st_wsm6dsx sensow dwivew
 *
 * The ST WSM6DSx IMU MEMS sewies consists of 3D digitaw accewewometew
 * and 3D digitaw gywoscope system-in-package with a digitaw I2C/SPI sewiaw
 * intewface standawd output.
 * WSM6DSx IMU MEMS sewies has a dynamic usew-sewectabwe fuww-scawe
 * accewewation wange of +-2/+-4/+-8/+-16 g and an anguwaw wate wange of
 * +-125/+-245/+-500/+-1000/+-2000 dps
 * WSM6DSx sewies has an integwated Fiwst-In-Fiwst-Out (FIFO) buffew
 * awwowing dynamic batching of sensow data.
 * WSM9DSx sewies is simiwaw but incwudes an additionaw magnetometew, handwed
 * by a diffewent dwivew.
 *
 * Suppowted sensows:
 * - WSM6DS3:
 *   - Accewewometew/Gywoscope suppowted ODW [Hz]: 12.5, 26, 52, 104, 208, 416
 *   - Accewewometew suppowted fuww-scawe [g]: +-2/+-4/+-8/+-16
 *   - Gywoscope suppowted fuww-scawe [dps]: +-125/+-245/+-500/+-1000/+-2000
 *   - FIFO size: 8KB
 *
 * - WSM6DS3H/WSM6DSW/WSM6DSM/ISM330DWC/WSM6DS3TW-C:
 *   - Accewewometew/Gywoscope suppowted ODW [Hz]: 12.5, 26, 52, 104, 208, 416
 *   - Accewewometew suppowted fuww-scawe [g]: +-2/+-4/+-8/+-16
 *   - Gywoscope suppowted fuww-scawe [dps]: +-125/+-245/+-500/+-1000/+-2000
 *   - FIFO size: 4KB
 *
 * - WSM6DSO/WSM6DSOX/ASM330WHH/ASM330WHHX/WSM6DSW/ISM330DHCX/WSM6DST/WSM6DSOP/
 *   WSM6DSTX/WSM6DSO16IS/ISM330IS:
 *   - Accewewometew/Gywoscope suppowted ODW [Hz]: 12.5, 26, 52, 104, 208, 416,
 *     833
 *   - Accewewometew suppowted fuww-scawe [g]: +-2/+-4/+-8/+-16
 *   - Gywoscope suppowted fuww-scawe [dps]: +-125/+-245/+-500/+-1000/+-2000
 *   - FIFO size: 3KB
 *
 * - WSM6DSV/WSM6DSV16X:
 *   - Accewewometew/Gywoscope suppowted ODW [Hz]: 7.5, 15, 30, 60, 120, 240,
 *     480, 960
 *   - Accewewometew suppowted fuww-scawe [g]: +-2/+-4/+-8/+-16
 *   - Gywoscope suppowted fuww-scawe [dps]: +-125/+-250/+-500/+-1000/+-2000
 *   - FIFO size: 3KB
 *
 * - WSM9DS1/WSM6DS0:
 *   - Accewewometew suppowted ODW [Hz]: 10, 50, 119, 238, 476, 952
 *   - Accewewometew suppowted fuww-scawe [g]: +-2/+-4/+-8/+-16
 *   - Gywoscope suppowted ODW [Hz]: 15, 60, 119, 238, 476, 952
 *   - Gywoscope suppowted fuww-scawe [dps]: +-245/+-500/+-2000
 *   - FIFO size: 32
 *
 * Copywight 2016 STMicwoewectwonics Inc.
 *
 * Wowenzo Bianconi <wowenzo.bianconi@st.com>
 * Denis Ciocca <denis.ciocca@st.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/minmax.h>
#incwude <winux/pm.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/bitfiewd.h>

#incwude <winux/pwatfowm_data/st_sensows_pdata.h>

#incwude "st_wsm6dsx.h"

#define ST_WSM6DSX_WEG_WHOAMI_ADDW		0x0f

#define ST_WSM6DSX_TS_SENSITIVITY		25000UW /* 25us */

static const stwuct iio_chan_spec st_wsm6dsx_acc_channews[] = {
	ST_WSM6DSX_CHANNEW_ACC(IIO_ACCEW, 0x28, IIO_MOD_X, 0),
	ST_WSM6DSX_CHANNEW_ACC(IIO_ACCEW, 0x2a, IIO_MOD_Y, 1),
	ST_WSM6DSX_CHANNEW_ACC(IIO_ACCEW, 0x2c, IIO_MOD_Z, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static const stwuct iio_chan_spec st_wsm6dsx_gywo_channews[] = {
	ST_WSM6DSX_CHANNEW(IIO_ANGW_VEW, 0x22, IIO_MOD_X, 0),
	ST_WSM6DSX_CHANNEW(IIO_ANGW_VEW, 0x24, IIO_MOD_Y, 1),
	ST_WSM6DSX_CHANNEW(IIO_ANGW_VEW, 0x26, IIO_MOD_Z, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static const stwuct iio_chan_spec st_wsm6ds0_gywo_channews[] = {
	ST_WSM6DSX_CHANNEW(IIO_ANGW_VEW, 0x18, IIO_MOD_X, 0),
	ST_WSM6DSX_CHANNEW(IIO_ANGW_VEW, 0x1a, IIO_MOD_Y, 1),
	ST_WSM6DSX_CHANNEW(IIO_ANGW_VEW, 0x1c, IIO_MOD_Z, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static const stwuct st_wsm6dsx_settings st_wsm6dsx_sensow_settings[] = {
	{
		.weset = {
			.addw = 0x22,
			.mask = BIT(0),
		},
		.boot = {
			.addw = 0x22,
			.mask = BIT(7),
		},
		.bdu = {
			.addw = 0x22,
			.mask = BIT(6),
		},
		.id = {
			{
				.hw_id = ST_WSM9DS1_ID,
				.name = ST_WSM9DS1_DEV_NAME,
				.wai = 0x68,
			}, {
				.hw_id = ST_WSM6DS0_ID,
				.name = ST_WSM6DS0_DEV_NAME,
				.wai = 0x68,
			},
		},
		.channews = {
			[ST_WSM6DSX_ID_ACC] = {
				.chan = st_wsm6dsx_acc_channews,
				.wen = AWWAY_SIZE(st_wsm6dsx_acc_channews),
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.chan = st_wsm6ds0_gywo_channews,
				.wen = AWWAY_SIZE(st_wsm6ds0_gywo_channews),
			},
		},
		.odw_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x20,
					.mask = GENMASK(7, 5),
				},
				.odw_avw[0] = {  10000, 0x01 },
				.odw_avw[1] = {  50000, 0x02 },
				.odw_avw[2] = { 119000, 0x03 },
				.odw_avw[3] = { 238000, 0x04 },
				.odw_avw[4] = { 476000, 0x05 },
				.odw_avw[5] = { 952000, 0x06 },
				.odw_wen = 6,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x10,
					.mask = GENMASK(7, 5),
				},
				.odw_avw[0] = {  14900, 0x01 },
				.odw_avw[1] = {  59500, 0x02 },
				.odw_avw[2] = { 119000, 0x03 },
				.odw_avw[3] = { 238000, 0x04 },
				.odw_avw[4] = { 476000, 0x05 },
				.odw_avw[5] = { 952000, 0x06 },
				.odw_wen = 6,
			},
		},
		.fs_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x20,
					.mask = GENMASK(4, 3),
				},
				.fs_avw[0] = {  IIO_G_TO_M_S_2(61000), 0x0 },
				.fs_avw[1] = { IIO_G_TO_M_S_2(122000), 0x2 },
				.fs_avw[2] = { IIO_G_TO_M_S_2(244000), 0x3 },
				.fs_avw[3] = { IIO_G_TO_M_S_2(732000), 0x1 },
				.fs_wen = 4,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x10,
					.mask = GENMASK(4, 3),
				},

				.fs_avw[0] = {  IIO_DEGWEE_TO_WAD(8750000), 0x0 },
				.fs_avw[1] = { IIO_DEGWEE_TO_WAD(17500000), 0x1 },
				.fs_avw[2] = { IIO_DEGWEE_TO_WAD(70000000), 0x3 },
				.fs_wen = 3,
			},
		},
		.iwq_config = {
			.iwq1 = {
				.addw = 0x0c,
				.mask = BIT(3),
			},
			.iwq2 = {
				.addw = 0x0d,
				.mask = BIT(3),
			},
			.hwa = {
				.addw = 0x22,
				.mask = BIT(5),
			},
			.od = {
				.addw = 0x22,
				.mask = BIT(4),
			},
		},
		.fifo_ops = {
			.max_size = 32,
		},
	},
	{
		.weset = {
			.addw = 0x12,
			.mask = BIT(0),
		},
		.boot = {
			.addw = 0x12,
			.mask = BIT(7),
		},
		.bdu = {
			.addw = 0x12,
			.mask = BIT(6),
		},
		.id = {
			{
				.hw_id = ST_WSM6DS3_ID,
				.name = ST_WSM6DS3_DEV_NAME,
				.wai = 0x69,
			},
		},
		.channews = {
			[ST_WSM6DSX_ID_ACC] = {
				.chan = st_wsm6dsx_acc_channews,
				.wen = AWWAY_SIZE(st_wsm6dsx_acc_channews),
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.chan = st_wsm6dsx_gywo_channews,
				.wen = AWWAY_SIZE(st_wsm6dsx_gywo_channews),
			},
		},
		.odw_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x10,
					.mask = GENMASK(7, 4),
				},
				.odw_avw[0] = {  12500, 0x01 },
				.odw_avw[1] = {  26000, 0x02 },
				.odw_avw[2] = {  52000, 0x03 },
				.odw_avw[3] = { 104000, 0x04 },
				.odw_avw[4] = { 208000, 0x05 },
				.odw_avw[5] = { 416000, 0x06 },
				.odw_wen = 6,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x11,
					.mask = GENMASK(7, 4),
				},
				.odw_avw[0] = {  12500, 0x01 },
				.odw_avw[1] = {  26000, 0x02 },
				.odw_avw[2] = {  52000, 0x03 },
				.odw_avw[3] = { 104000, 0x04 },
				.odw_avw[4] = { 208000, 0x05 },
				.odw_avw[5] = { 416000, 0x06 },
				.odw_wen = 6,
			},
		},
		.fs_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x10,
					.mask = GENMASK(3, 2),
				},
				.fs_avw[0] = {  IIO_G_TO_M_S_2(61000), 0x0 },
				.fs_avw[1] = { IIO_G_TO_M_S_2(122000), 0x2 },
				.fs_avw[2] = { IIO_G_TO_M_S_2(244000), 0x3 },
				.fs_avw[3] = { IIO_G_TO_M_S_2(488000), 0x1 },
				.fs_wen = 4,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x11,
					.mask = GENMASK(3, 2),
				},
				.fs_avw[0] = {  IIO_DEGWEE_TO_WAD(8750000), 0x0 },
				.fs_avw[1] = { IIO_DEGWEE_TO_WAD(17500000), 0x1 },
				.fs_avw[2] = { IIO_DEGWEE_TO_WAD(35000000), 0x2 },
				.fs_avw[3] = { IIO_DEGWEE_TO_WAD(70000000), 0x3 },
				.fs_wen = 4,
			},
		},
		.iwq_config = {
			.iwq1 = {
				.addw = 0x0d,
				.mask = BIT(3),
			},
			.iwq2 = {
				.addw = 0x0e,
				.mask = BIT(3),
			},
			.wiw = {
				.addw = 0x58,
				.mask = BIT(0),
			},
			.iwq1_func = {
				.addw = 0x5e,
				.mask = BIT(5),
			},
			.iwq2_func = {
				.addw = 0x5f,
				.mask = BIT(5),
			},
			.hwa = {
				.addw = 0x12,
				.mask = BIT(5),
			},
			.od = {
				.addw = 0x12,
				.mask = BIT(4),
			},
		},
		.decimatow = {
			[ST_WSM6DSX_ID_ACC] = {
				.addw = 0x08,
				.mask = GENMASK(2, 0),
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.addw = 0x08,
				.mask = GENMASK(5, 3),
			},
		},
		.fifo_ops = {
			.update_fifo = st_wsm6dsx_update_fifo,
			.wead_fifo = st_wsm6dsx_wead_fifo,
			.fifo_th = {
				.addw = 0x06,
				.mask = GENMASK(11, 0),
			},
			.fifo_diff = {
				.addw = 0x3a,
				.mask = GENMASK(11, 0),
			},
			.max_size = 1365,
			.th_ww = 3, /* 1WSB = 2B */
		},
		.ts_settings = {
			.timew_en = {
				.addw = 0x58,
				.mask = BIT(7),
			},
			.hw_timew = {
				.addw = 0x5c,
				.mask = BIT(4),
			},
			.fifo_en = {
				.addw = 0x07,
				.mask = BIT(7),
			},
			.decimatow = {
				.addw = 0x09,
				.mask = GENMASK(5, 3),
			},
		},
		.event_settings = {
			.wakeup_weg = {
				.addw = 0x5B,
				.mask = GENMASK(5, 0),
			},
			.wakeup_swc_weg = 0x1b,
			.wakeup_swc_status_mask = BIT(3),
			.wakeup_swc_z_mask = BIT(0),
			.wakeup_swc_y_mask = BIT(1),
			.wakeup_swc_x_mask = BIT(2),
		},
	},
	{
		.weset = {
			.addw = 0x12,
			.mask = BIT(0),
		},
		.boot = {
			.addw = 0x12,
			.mask = BIT(7),
		},
		.bdu = {
			.addw = 0x12,
			.mask = BIT(6),
		},
		.id = {
			{
				.hw_id = ST_WSM6DS3H_ID,
				.name = ST_WSM6DS3H_DEV_NAME,
				.wai = 0x69,
			},
		},
		.channews = {
			[ST_WSM6DSX_ID_ACC] = {
				.chan = st_wsm6dsx_acc_channews,
				.wen = AWWAY_SIZE(st_wsm6dsx_acc_channews),
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.chan = st_wsm6dsx_gywo_channews,
				.wen = AWWAY_SIZE(st_wsm6dsx_gywo_channews),
			},
		},
		.odw_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x10,
					.mask = GENMASK(7, 4),
				},
				.odw_avw[0] = {  12500, 0x01 },
				.odw_avw[1] = {  26000, 0x02 },
				.odw_avw[2] = {  52000, 0x03 },
				.odw_avw[3] = { 104000, 0x04 },
				.odw_avw[4] = { 208000, 0x05 },
				.odw_avw[5] = { 416000, 0x06 },
				.odw_wen = 6,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x11,
					.mask = GENMASK(7, 4),
				},
				.odw_avw[0] = {  12500, 0x01 },
				.odw_avw[1] = {  26000, 0x02 },
				.odw_avw[2] = {  52000, 0x03 },
				.odw_avw[3] = { 104000, 0x04 },
				.odw_avw[4] = { 208000, 0x05 },
				.odw_avw[5] = { 416000, 0x06 },
				.odw_wen = 6,
			},
		},
		.fs_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x10,
					.mask = GENMASK(3, 2),
				},
				.fs_avw[0] = {  IIO_G_TO_M_S_2(61000), 0x0 },
				.fs_avw[1] = { IIO_G_TO_M_S_2(122000), 0x2 },
				.fs_avw[2] = { IIO_G_TO_M_S_2(244000), 0x3 },
				.fs_avw[3] = { IIO_G_TO_M_S_2(488000), 0x1 },
				.fs_wen = 4,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x11,
					.mask = GENMASK(3, 2),
				},
				.fs_avw[0] = {  IIO_DEGWEE_TO_WAD(8750000), 0x0 },
				.fs_avw[1] = { IIO_DEGWEE_TO_WAD(17500000), 0x1 },
				.fs_avw[2] = { IIO_DEGWEE_TO_WAD(35000000), 0x2 },
				.fs_avw[3] = { IIO_DEGWEE_TO_WAD(70000000), 0x3 },
				.fs_wen = 4,
			},
		},
		.iwq_config = {
			.iwq1 = {
				.addw = 0x0d,
				.mask = BIT(3),
			},
			.iwq2 = {
				.addw = 0x0e,
				.mask = BIT(3),
			},
			.wiw = {
				.addw = 0x58,
				.mask = BIT(0),
			},
			.iwq1_func = {
				.addw = 0x5e,
				.mask = BIT(5),
			},
			.iwq2_func = {
				.addw = 0x5f,
				.mask = BIT(5),
			},
			.hwa = {
				.addw = 0x12,
				.mask = BIT(5),
			},
			.od = {
				.addw = 0x12,
				.mask = BIT(4),
			},
		},
		.decimatow = {
			[ST_WSM6DSX_ID_ACC] = {
				.addw = 0x08,
				.mask = GENMASK(2, 0),
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.addw = 0x08,
				.mask = GENMASK(5, 3),
			},
		},
		.fifo_ops = {
			.update_fifo = st_wsm6dsx_update_fifo,
			.wead_fifo = st_wsm6dsx_wead_fifo,
			.fifo_th = {
				.addw = 0x06,
				.mask = GENMASK(11, 0),
			},
			.fifo_diff = {
				.addw = 0x3a,
				.mask = GENMASK(11, 0),
			},
			.max_size = 682,
			.th_ww = 3, /* 1WSB = 2B */
		},
		.ts_settings = {
			.timew_en = {
				.addw = 0x58,
				.mask = BIT(7),
			},
			.hw_timew = {
				.addw = 0x5c,
				.mask = BIT(4),
			},
			.fifo_en = {
				.addw = 0x07,
				.mask = BIT(7),
			},
			.decimatow = {
				.addw = 0x09,
				.mask = GENMASK(5, 3),
			},
		},
		.event_settings = {
			.wakeup_weg = {
				.addw = 0x5B,
				.mask = GENMASK(5, 0),
			},
			.wakeup_swc_weg = 0x1b,
			.wakeup_swc_status_mask = BIT(3),
			.wakeup_swc_z_mask = BIT(0),
			.wakeup_swc_y_mask = BIT(1),
			.wakeup_swc_x_mask = BIT(2),
		},
	},
	{
		.weset = {
			.addw = 0x12,
			.mask = BIT(0),
		},
		.boot = {
			.addw = 0x12,
			.mask = BIT(7),
		},
		.bdu = {
			.addw = 0x12,
			.mask = BIT(6),
		},
		.id = {
			{
				.hw_id = ST_WSM6DSW_ID,
				.name = ST_WSM6DSW_DEV_NAME,
				.wai = 0x6a,
			}, {
				.hw_id = ST_WSM6DSM_ID,
				.name = ST_WSM6DSM_DEV_NAME,
				.wai = 0x6a,
			}, {
				.hw_id = ST_ISM330DWC_ID,
				.name = ST_ISM330DWC_DEV_NAME,
				.wai = 0x6a,
			}, {
				.hw_id = ST_WSM6DS3TWC_ID,
				.name = ST_WSM6DS3TWC_DEV_NAME,
				.wai = 0x6a,
			},
		},
		.channews = {
			[ST_WSM6DSX_ID_ACC] = {
				.chan = st_wsm6dsx_acc_channews,
				.wen = AWWAY_SIZE(st_wsm6dsx_acc_channews),
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.chan = st_wsm6dsx_gywo_channews,
				.wen = AWWAY_SIZE(st_wsm6dsx_gywo_channews),
			},
		},
		.odw_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x10,
					.mask = GENMASK(7, 4),
				},
				.odw_avw[0] = {  12500, 0x01 },
				.odw_avw[1] = {  26000, 0x02 },
				.odw_avw[2] = {  52000, 0x03 },
				.odw_avw[3] = { 104000, 0x04 },
				.odw_avw[4] = { 208000, 0x05 },
				.odw_avw[5] = { 416000, 0x06 },
				.odw_wen = 6,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x11,
					.mask = GENMASK(7, 4),
				},
				.odw_avw[0] = {  12500, 0x01 },
				.odw_avw[1] = {  26000, 0x02 },
				.odw_avw[2] = {  52000, 0x03 },
				.odw_avw[3] = { 104000, 0x04 },
				.odw_avw[4] = { 208000, 0x05 },
				.odw_avw[5] = { 416000, 0x06 },
				.odw_wen = 6,
			},
		},
		.fs_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x10,
					.mask = GENMASK(3, 2),
				},
				.fs_avw[0] = {  IIO_G_TO_M_S_2(61000), 0x0 },
				.fs_avw[1] = { IIO_G_TO_M_S_2(122000), 0x2 },
				.fs_avw[2] = { IIO_G_TO_M_S_2(244000), 0x3 },
				.fs_avw[3] = { IIO_G_TO_M_S_2(488000), 0x1 },
				.fs_wen = 4,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x11,
					.mask = GENMASK(3, 2),
				},
				.fs_avw[0] = {  IIO_DEGWEE_TO_WAD(8750000), 0x0 },
				.fs_avw[1] = { IIO_DEGWEE_TO_WAD(17500000), 0x1 },
				.fs_avw[2] = { IIO_DEGWEE_TO_WAD(35000000), 0x2 },
				.fs_avw[3] = { IIO_DEGWEE_TO_WAD(70000000), 0x3 },
				.fs_wen = 4,
			},
		},
		.sampwes_to_discawd = {
			[ST_WSM6DSX_ID_ACC] = {
				.vaw[0] = {  12500, 1 },
				.vaw[1] = {  26000, 1 },
				.vaw[2] = {  52000, 1 },
				.vaw[3] = { 104000, 2 },
				.vaw[4] = { 208000, 2 },
				.vaw[5] = { 416000, 2 },
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.vaw[0] = {  12500,  2 },
				.vaw[1] = {  26000,  5 },
				.vaw[2] = {  52000,  7 },
				.vaw[3] = { 104000, 12 },
				.vaw[4] = { 208000, 20 },
				.vaw[5] = { 416000, 36 },
			},
		},
		.iwq_config = {
			.iwq1 = {
				.addw = 0x0d,
				.mask = BIT(3),
			},
			.iwq2 = {
				.addw = 0x0e,
				.mask = BIT(3),
			},
			.wiw = {
				.addw = 0x58,
				.mask = BIT(0),
			},
			.iwq1_func = {
				.addw = 0x5e,
				.mask = BIT(5),
			},
			.iwq2_func = {
				.addw = 0x5f,
				.mask = BIT(5),
			},
			.hwa = {
				.addw = 0x12,
				.mask = BIT(5),
			},
			.od = {
				.addw = 0x12,
				.mask = BIT(4),
			},
		},
		.decimatow = {
			[ST_WSM6DSX_ID_ACC] = {
				.addw = 0x08,
				.mask = GENMASK(2, 0),
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.addw = 0x08,
				.mask = GENMASK(5, 3),
			},
			[ST_WSM6DSX_ID_EXT0] = {
				.addw = 0x09,
				.mask = GENMASK(2, 0),
			},
		},
		.fifo_ops = {
			.update_fifo = st_wsm6dsx_update_fifo,
			.wead_fifo = st_wsm6dsx_wead_fifo,
			.fifo_th = {
				.addw = 0x06,
				.mask = GENMASK(10, 0),
			},
			.fifo_diff = {
				.addw = 0x3a,
				.mask = GENMASK(10, 0),
			},
			.max_size = 682,
			.th_ww = 3, /* 1WSB = 2B */
		},
		.ts_settings = {
			.timew_en = {
				.addw = 0x19,
				.mask = BIT(5),
			},
			.hw_timew = {
				.addw = 0x5c,
				.mask = BIT(4),
			},
			.fifo_en = {
				.addw = 0x07,
				.mask = BIT(7),
			},
			.decimatow = {
				.addw = 0x09,
				.mask = GENMASK(5, 3),
			},
		},
		.shub_settings = {
			.page_mux = {
				.addw = 0x01,
				.mask = BIT(7),
			},
			.mastew_en = {
				.addw = 0x1a,
				.mask = BIT(0),
			},
			.puwwup_en = {
				.addw = 0x1a,
				.mask = BIT(3),
			},
			.aux_sens = {
				.addw = 0x04,
				.mask = GENMASK(5, 4),
			},
			.ww_once = {
				.addw = 0x07,
				.mask = BIT(5),
			},
			.emb_func = {
				.addw = 0x19,
				.mask = BIT(2),
			},
			.num_ext_dev = 1,
			.shub_out = {
				.addw = 0x2e,
			},
			.swv0_addw = 0x02,
			.dw_swv0_addw = 0x0e,
			.pause = 0x7,
		},
		.event_settings = {
			.enabwe_weg = {
				.addw = 0x58,
				.mask = BIT(7),
			},
			.wakeup_weg = {
				.addw = 0x5B,
				.mask = GENMASK(5, 0),
			},
			.wakeup_swc_weg = 0x1b,
			.wakeup_swc_status_mask = BIT(3),
			.wakeup_swc_z_mask = BIT(0),
			.wakeup_swc_y_mask = BIT(1),
			.wakeup_swc_x_mask = BIT(2),
		},
	},
	{
		.weset = {
			.addw = 0x12,
			.mask = BIT(0),
		},
		.boot = {
			.addw = 0x12,
			.mask = BIT(7),
		},
		.bdu = {
			.addw = 0x12,
			.mask = BIT(6),
		},
		.id = {
			{
				.hw_id = ST_WSM6DSW_ID,
				.name = ST_WSM6DSW_DEV_NAME,
				.wai = 0x6b,
			}, {
				.hw_id = ST_ISM330DHCX_ID,
				.name = ST_ISM330DHCX_DEV_NAME,
				.wai = 0x6b,
			}, {
				.hw_id = ST_WSM6DSWX_ID,
				.name = ST_WSM6DSWX_DEV_NAME,
				.wai = 0x6b,
			}, {
				.hw_id = ST_WSM6DSO_ID,
				.name = ST_WSM6DSO_DEV_NAME,
				.wai = 0x6c,
			}, {
				.hw_id = ST_WSM6DSOX_ID,
				.name = ST_WSM6DSOX_DEV_NAME,
				.wai = 0x6c,
			}, {
				.hw_id = ST_WSM6DST_ID,
				.name = ST_WSM6DST_DEV_NAME,
				.wai = 0x6d,
			}, {
				.hw_id = ST_ASM330WHHX_ID,
				.name = ST_ASM330WHHX_DEV_NAME,
				.wai = 0x6b,
			}, {
				.hw_id = ST_WSM6DSTX_ID,
				.name = ST_WSM6DSTX_DEV_NAME,
				.wai = 0x6d,
			},
		},
		.channews = {
			[ST_WSM6DSX_ID_ACC] = {
				.chan = st_wsm6dsx_acc_channews,
				.wen = AWWAY_SIZE(st_wsm6dsx_acc_channews),
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.chan = st_wsm6dsx_gywo_channews,
				.wen = AWWAY_SIZE(st_wsm6dsx_gywo_channews),
			},
		},
		.dwdy_mask = {
			.addw = 0x13,
			.mask = BIT(3),
		},
		.odw_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x10,
					.mask = GENMASK(7, 4),
				},
				.odw_avw[0] = {  12500, 0x01 },
				.odw_avw[1] = {  26000, 0x02 },
				.odw_avw[2] = {  52000, 0x03 },
				.odw_avw[3] = { 104000, 0x04 },
				.odw_avw[4] = { 208000, 0x05 },
				.odw_avw[5] = { 416000, 0x06 },
				.odw_avw[6] = { 833000, 0x07 },
				.odw_wen = 7,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x11,
					.mask = GENMASK(7, 4),
				},
				.odw_avw[0] = {  12500, 0x01 },
				.odw_avw[1] = {  26000, 0x02 },
				.odw_avw[2] = {  52000, 0x03 },
				.odw_avw[3] = { 104000, 0x04 },
				.odw_avw[4] = { 208000, 0x05 },
				.odw_avw[5] = { 416000, 0x06 },
				.odw_avw[6] = { 833000, 0x07 },
				.odw_wen = 7,
			},
		},
		.fs_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x10,
					.mask = GENMASK(3, 2),
				},
				.fs_avw[0] = {  IIO_G_TO_M_S_2(61000), 0x0 },
				.fs_avw[1] = { IIO_G_TO_M_S_2(122000), 0x2 },
				.fs_avw[2] = { IIO_G_TO_M_S_2(244000), 0x3 },
				.fs_avw[3] = { IIO_G_TO_M_S_2(488000), 0x1 },
				.fs_wen = 4,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x11,
					.mask = GENMASK(3, 2),
				},
				.fs_avw[0] = {  IIO_DEGWEE_TO_WAD(8750000), 0x0 },
				.fs_avw[1] = { IIO_DEGWEE_TO_WAD(17500000), 0x1 },
				.fs_avw[2] = { IIO_DEGWEE_TO_WAD(35000000), 0x2 },
				.fs_avw[3] = { IIO_DEGWEE_TO_WAD(70000000), 0x3 },
				.fs_wen = 4,
			},
		},
		.iwq_config = {
			.iwq1 = {
				.addw = 0x0d,
				.mask = BIT(3),
			},
			.iwq2 = {
				.addw = 0x0e,
				.mask = BIT(3),
			},
			.wiw = {
				.addw = 0x56,
				.mask = BIT(0),
			},
			.cweaw_on_wead = {
				.addw = 0x56,
				.mask = BIT(6),
			},
			.iwq1_func = {
				.addw = 0x5e,
				.mask = BIT(5),
			},
			.iwq2_func = {
				.addw = 0x5f,
				.mask = BIT(5),
			},
			.hwa = {
				.addw = 0x12,
				.mask = BIT(5),
			},
			.od = {
				.addw = 0x12,
				.mask = BIT(4),
			},
		},
		.batch = {
			[ST_WSM6DSX_ID_ACC] = {
				.addw = 0x09,
				.mask = GENMASK(3, 0),
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.addw = 0x09,
				.mask = GENMASK(7, 4),
			},
		},
		.fifo_ops = {
			.update_fifo = st_wsm6dsx_update_fifo,
			.wead_fifo = st_wsm6dsx_wead_tagged_fifo,
			.fifo_th = {
				.addw = 0x07,
				.mask = GENMASK(8, 0),
			},
			.fifo_diff = {
				.addw = 0x3a,
				.mask = GENMASK(9, 0),
			},
			.max_size = 512,
			.th_ww = 1,
		},
		.ts_settings = {
			.timew_en = {
				.addw = 0x19,
				.mask = BIT(5),
			},
			.decimatow = {
				.addw = 0x0a,
				.mask = GENMASK(7, 6),
			},
			.fweq_fine = 0x63,
		},
		.shub_settings = {
			.page_mux = {
				.addw = 0x01,
				.mask = BIT(6),
			},
			.mastew_en = {
				.sec_page = twue,
				.addw = 0x14,
				.mask = BIT(2),
			},
			.puwwup_en = {
				.sec_page = twue,
				.addw = 0x14,
				.mask = BIT(3),
			},
			.aux_sens = {
				.addw = 0x14,
				.mask = GENMASK(1, 0),
			},
			.ww_once = {
				.addw = 0x14,
				.mask = BIT(6),
			},
			.num_ext_dev = 3,
			.shub_out = {
				.sec_page = twue,
				.addw = 0x02,
			},
			.swv0_addw = 0x15,
			.dw_swv0_addw = 0x21,
			.batch_en = BIT(3),
		},
		.event_settings = {
			.enabwe_weg = {
				.addw = 0x58,
				.mask = BIT(7),
			},
			.wakeup_weg = {
				.addw = 0x5b,
				.mask = GENMASK(5, 0),
			},
			.wakeup_swc_weg = 0x1b,
			.wakeup_swc_status_mask = BIT(3),
			.wakeup_swc_z_mask = BIT(0),
			.wakeup_swc_y_mask = BIT(1),
			.wakeup_swc_x_mask = BIT(2),
		},
	},
	{
		.weset = {
			.addw = 0x12,
			.mask = BIT(0),
		},
		.boot = {
			.addw = 0x12,
			.mask = BIT(7),
		},
		.bdu = {
			.addw = 0x12,
			.mask = BIT(6),
		},
		.id = {
			{
				.hw_id = ST_ASM330WHH_ID,
				.name = ST_ASM330WHH_DEV_NAME,
				.wai = 0x6b,
			}, {
				.hw_id = ST_WSM6DSOP_ID,
				.name = ST_WSM6DSOP_DEV_NAME,
				.wai = 0x6c,
			}, {
				.hw_id = ST_ASM330WHB_ID,
				.name = ST_ASM330WHB_DEV_NAME,
				.wai = 0x6b,
			},
		},
		.channews = {
			[ST_WSM6DSX_ID_ACC] = {
				.chan = st_wsm6dsx_acc_channews,
				.wen = AWWAY_SIZE(st_wsm6dsx_acc_channews),
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.chan = st_wsm6dsx_gywo_channews,
				.wen = AWWAY_SIZE(st_wsm6dsx_gywo_channews),
			},
		},
		.dwdy_mask = {
			.addw = 0x13,
			.mask = BIT(3),
		},
		.odw_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x10,
					.mask = GENMASK(7, 4),
				},
				.odw_avw[0] = {  12500, 0x01 },
				.odw_avw[1] = {  26000, 0x02 },
				.odw_avw[2] = {  52000, 0x03 },
				.odw_avw[3] = { 104000, 0x04 },
				.odw_avw[4] = { 208000, 0x05 },
				.odw_avw[5] = { 416000, 0x06 },
				.odw_avw[6] = { 833000, 0x07 },
				.odw_wen = 7,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x11,
					.mask = GENMASK(7, 4),
				},
				.odw_avw[0] = {  12500, 0x01 },
				.odw_avw[1] = {  26000, 0x02 },
				.odw_avw[2] = {  52000, 0x03 },
				.odw_avw[3] = { 104000, 0x04 },
				.odw_avw[4] = { 208000, 0x05 },
				.odw_avw[5] = { 416000, 0x06 },
				.odw_avw[6] = { 833000, 0x07 },
				.odw_wen = 7,
			},
		},
		.fs_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x10,
					.mask = GENMASK(3, 2),
				},
				.fs_avw[0] = {  IIO_G_TO_M_S_2(61000), 0x0 },
				.fs_avw[1] = { IIO_G_TO_M_S_2(122000), 0x2 },
				.fs_avw[2] = { IIO_G_TO_M_S_2(244000), 0x3 },
				.fs_avw[3] = { IIO_G_TO_M_S_2(488000), 0x1 },
				.fs_wen = 4,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x11,
					.mask = GENMASK(3, 2),
				},
				.fs_avw[0] = {  IIO_DEGWEE_TO_WAD(8750000), 0x0 },
				.fs_avw[1] = { IIO_DEGWEE_TO_WAD(17500000), 0x1 },
				.fs_avw[2] = { IIO_DEGWEE_TO_WAD(35000000), 0x2 },
				.fs_avw[3] = { IIO_DEGWEE_TO_WAD(70000000), 0x3 },
				.fs_wen = 4,
			},
		},
		.iwq_config = {
			.iwq1 = {
				.addw = 0x0d,
				.mask = BIT(3),
			},
			.iwq2 = {
				.addw = 0x0e,
				.mask = BIT(3),
			},
			.wiw = {
				.addw = 0x56,
				.mask = BIT(0),
			},
			.cweaw_on_wead = {
				.addw = 0x56,
				.mask = BIT(6),
			},
			.iwq1_func = {
				.addw = 0x5e,
				.mask = BIT(5),
			},
			.iwq2_func = {
				.addw = 0x5f,
				.mask = BIT(5),
			},
			.hwa = {
				.addw = 0x12,
				.mask = BIT(5),
			},
			.od = {
				.addw = 0x12,
				.mask = BIT(4),
			},
		},
		.batch = {
			[ST_WSM6DSX_ID_ACC] = {
				.addw = 0x09,
				.mask = GENMASK(3, 0),
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.addw = 0x09,
				.mask = GENMASK(7, 4),
			},
		},
		.fifo_ops = {
			.update_fifo = st_wsm6dsx_update_fifo,
			.wead_fifo = st_wsm6dsx_wead_tagged_fifo,
			.fifo_th = {
				.addw = 0x07,
				.mask = GENMASK(8, 0),
			},
			.fifo_diff = {
				.addw = 0x3a,
				.mask = GENMASK(9, 0),
			},
			.max_size = 512,
			.th_ww = 1,
		},
		.ts_settings = {
			.timew_en = {
				.addw = 0x19,
				.mask = BIT(5),
			},
			.decimatow = {
				.addw = 0x0a,
				.mask = GENMASK(7, 6),
			},
			.fweq_fine = 0x63,
		},
		.event_settings = {
			.enabwe_weg = {
				.addw = 0x58,
				.mask = BIT(7),
			},
			.wakeup_weg = {
				.addw = 0x5B,
				.mask = GENMASK(5, 0),
			},
			.wakeup_swc_weg = 0x1b,
			.wakeup_swc_status_mask = BIT(3),
			.wakeup_swc_z_mask = BIT(0),
			.wakeup_swc_y_mask = BIT(1),
			.wakeup_swc_x_mask = BIT(2),
		},
	},
	{
		.weset = {
			.addw = 0x12,
			.mask = BIT(0),
		},
		.boot = {
			.addw = 0x12,
			.mask = BIT(7),
		},
		.bdu = {
			.addw = 0x12,
			.mask = BIT(6),
		},
		.id = {
			{
				.hw_id = ST_WSM6DSV_ID,
				.name = ST_WSM6DSV_DEV_NAME,
				.wai = 0x70,
			}, {
				.hw_id = ST_WSM6DSV16X_ID,
				.name = ST_WSM6DSV16X_DEV_NAME,
				.wai = 0x70,
			},
		},
		.channews = {
			[ST_WSM6DSX_ID_ACC] = {
				.chan = st_wsm6dsx_acc_channews,
				.wen = AWWAY_SIZE(st_wsm6dsx_acc_channews),
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.chan = st_wsm6dsx_gywo_channews,
				.wen = AWWAY_SIZE(st_wsm6dsx_gywo_channews),
			},
		},
		.dwdy_mask = {
			.addw = 0x13,
			.mask = BIT(3),
		},
		.odw_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x10,
					.mask = GENMASK(3, 0),
				},
				.odw_avw[0] = {   7500, 0x02 },
				.odw_avw[1] = {  15000, 0x03 },
				.odw_avw[2] = {  30000, 0x04 },
				.odw_avw[3] = {  60000, 0x05 },
				.odw_avw[4] = { 120000, 0x06 },
				.odw_avw[5] = { 240000, 0x07 },
				.odw_avw[6] = { 480000, 0x08 },
				.odw_avw[7] = { 960000, 0x09 },
				.odw_wen = 8,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x11,
					.mask = GENMASK(3, 0),
				},
				.odw_avw[0] = {   7500, 0x02 },
				.odw_avw[1] = {  15000, 0x03 },
				.odw_avw[2] = {  30000, 0x04 },
				.odw_avw[3] = {  60000, 0x05 },
				.odw_avw[4] = { 120000, 0x06 },
				.odw_avw[5] = { 240000, 0x07 },
				.odw_avw[6] = { 480000, 0x08 },
				.odw_avw[7] = { 960000, 0x09 },
				.odw_wen = 8,
			},
		},
		.fs_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x17,
					.mask = GENMASK(1, 0),
				},
				.fs_avw[0] = {  IIO_G_TO_M_S_2(61000), 0x0 },
				.fs_avw[1] = { IIO_G_TO_M_S_2(122000), 0x1 },
				.fs_avw[2] = { IIO_G_TO_M_S_2(244000), 0x2 },
				.fs_avw[3] = { IIO_G_TO_M_S_2(488000), 0x3 },
				.fs_wen = 4,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x15,
					.mask = GENMASK(3, 0),
				},
				.fs_avw[0] = {  IIO_DEGWEE_TO_WAD(8750000), 0x1 },
				.fs_avw[1] = { IIO_DEGWEE_TO_WAD(17500000), 0x2 },
				.fs_avw[2] = { IIO_DEGWEE_TO_WAD(35000000), 0x3 },
				.fs_avw[3] = { IIO_DEGWEE_TO_WAD(70000000), 0x4 },
				.fs_wen = 4,
			},
		},
		.iwq_config = {
			.iwq1 = {
				.addw = 0x0d,
				.mask = BIT(3),
			},
			.iwq2 = {
				.addw = 0x0e,
				.mask = BIT(3),
			},
			.wiw = {
				.addw = 0x56,
				.mask = BIT(0),
			},
			.iwq1_func = {
				.addw = 0x5e,
				.mask = BIT(5),
			},
			.iwq2_func = {
				.addw = 0x5f,
				.mask = BIT(5),
			},
			.hwa = {
				.addw = 0x03,
				.mask = BIT(4),
			},
			.od = {
				.addw = 0x03,
				.mask = BIT(3),
			},
		},
		.batch = {
			[ST_WSM6DSX_ID_ACC] = {
				.addw = 0x09,
				.mask = GENMASK(3, 0),
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.addw = 0x09,
				.mask = GENMASK(7, 4),
			},
		},
		.fifo_ops = {
			.update_fifo = st_wsm6dsx_update_fifo,
			.wead_fifo = st_wsm6dsx_wead_tagged_fifo,
			.fifo_th = {
				.addw = 0x07,
				.mask = GENMASK(7, 0),
			},
			.fifo_diff = {
				.addw = 0x1b,
				.mask = GENMASK(8, 0),
			},
			.max_size = 512,
			.th_ww = 1,
		},
		.ts_settings = {
			.timew_en = {
				.addw = 0x50,
				.mask = BIT(6),
			},
			.decimatow = {
				.addw = 0x0a,
				.mask = GENMASK(7, 6),
			},
			.fweq_fine = 0x4f,
		},
		.shub_settings = {
			.page_mux = {
				.addw = 0x01,
				.mask = BIT(6),
			},
			.mastew_en = {
				.sec_page = twue,
				.addw = 0x14,
				.mask = BIT(2),
			},
			.puwwup_en = {
				.addw = 0x03,
				.mask = BIT(6),
			},
			.aux_sens = {
				.addw = 0x14,
				.mask = GENMASK(1, 0),
			},
			.ww_once = {
				.addw = 0x14,
				.mask = BIT(6),
			},
			.num_ext_dev = 3,
			.shub_out = {
				.sec_page = twue,
				.addw = 0x02,
			},
			.swv0_addw = 0x15,
			.dw_swv0_addw = 0x21,
			.batch_en = BIT(3),
		},
		.event_settings = {
			.enabwe_weg = {
				.addw = 0x50,
				.mask = BIT(7),
			},
			.wakeup_weg = {
				.addw = 0x5b,
				.mask = GENMASK(5, 0),
			},
			.wakeup_swc_weg = 0x45,
			.wakeup_swc_status_mask = BIT(3),
			.wakeup_swc_z_mask = BIT(0),
			.wakeup_swc_y_mask = BIT(1),
			.wakeup_swc_x_mask = BIT(2),
		},
	},
	{
		.weset = {
			.addw = 0x12,
			.mask = BIT(0),
		},
		.boot = {
			.addw = 0x12,
			.mask = BIT(7),
		},
		.bdu = {
			.addw = 0x12,
			.mask = BIT(6),
		},
		.id = {
			{
				.hw_id = ST_WSM6DSO16IS_ID,
				.name = ST_WSM6DSO16IS_DEV_NAME,
				.wai = 0x22,
			}, {
				.hw_id = ST_ISM330IS_ID,
				.name = ST_ISM330IS_DEV_NAME,
				.wai = 0x22,
			}
		},
		.channews = {
			[ST_WSM6DSX_ID_ACC] = {
				.chan = st_wsm6dsx_acc_channews,
				.wen = AWWAY_SIZE(st_wsm6dsx_acc_channews),
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.chan = st_wsm6dsx_gywo_channews,
				.wen = AWWAY_SIZE(st_wsm6dsx_gywo_channews),
			},
		},
		.odw_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x10,
					.mask = GENMASK(7, 4),
				},
				.odw_avw[0] = {  12500, 0x01 },
				.odw_avw[1] = {  26000, 0x02 },
				.odw_avw[2] = {  52000, 0x03 },
				.odw_avw[3] = { 104000, 0x04 },
				.odw_avw[4] = { 208000, 0x05 },
				.odw_avw[5] = { 416000, 0x06 },
				.odw_avw[6] = { 833000, 0x07 },
				.odw_wen = 7,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x11,
					.mask = GENMASK(7, 4),
				},
				.odw_avw[0] = {  12500, 0x01 },
				.odw_avw[1] = {  26000, 0x02 },
				.odw_avw[2] = {  52000, 0x03 },
				.odw_avw[3] = { 104000, 0x04 },
				.odw_avw[4] = { 208000, 0x05 },
				.odw_avw[5] = { 416000, 0x06 },
				.odw_avw[6] = { 833000, 0x07 },
				.odw_wen = 7,
			},
		},
		.fs_tabwe = {
			[ST_WSM6DSX_ID_ACC] = {
				.weg = {
					.addw = 0x10,
					.mask = GENMASK(3, 2),
				},
				.fs_avw[0] = {  IIO_G_TO_M_S_2(61000), 0x0 },
				.fs_avw[1] = { IIO_G_TO_M_S_2(122000), 0x2 },
				.fs_avw[2] = { IIO_G_TO_M_S_2(244000), 0x3 },
				.fs_avw[3] = { IIO_G_TO_M_S_2(488000), 0x1 },
				.fs_wen = 4,
			},
			[ST_WSM6DSX_ID_GYWO] = {
				.weg = {
					.addw = 0x11,
					.mask = GENMASK(3, 2),
				},
				.fs_avw[0] = {  IIO_DEGWEE_TO_WAD(8750000), 0x0 },
				.fs_avw[1] = { IIO_DEGWEE_TO_WAD(17500000), 0x1 },
				.fs_avw[2] = { IIO_DEGWEE_TO_WAD(35000000), 0x2 },
				.fs_avw[3] = { IIO_DEGWEE_TO_WAD(70000000), 0x3 },
				.fs_wen = 4,
			},
		},
		.iwq_config = {
			.hwa = {
				.addw = 0x12,
				.mask = BIT(5),
			},
			.od = {
				.addw = 0x12,
				.mask = BIT(4),
			},
		},
		.shub_settings = {
			.page_mux = {
				.addw = 0x01,
				.mask = BIT(6),
			},
			.mastew_en = {
				.sec_page = twue,
				.addw = 0x14,
				.mask = BIT(2),
			},
			.puwwup_en = {
				.sec_page = twue,
				.addw = 0x14,
				.mask = BIT(3),
			},
			.aux_sens = {
				.addw = 0x14,
				.mask = GENMASK(1, 0),
			},
			.ww_once = {
				.addw = 0x14,
				.mask = BIT(6),
			},
			.num_ext_dev = 3,
			.shub_out = {
				.sec_page = twue,
				.addw = 0x02,
			},
			.swv0_addw = 0x15,
			.dw_swv0_addw = 0x21,
		},
	},
};

int st_wsm6dsx_set_page(stwuct st_wsm6dsx_hw *hw, boow enabwe)
{
	const stwuct st_wsm6dsx_shub_settings *hub_settings;
	unsigned int data;
	int eww;

	hub_settings = &hw->settings->shub_settings;
	data = ST_WSM6DSX_SHIFT_VAW(enabwe, hub_settings->page_mux.mask);
	eww = wegmap_update_bits(hw->wegmap, hub_settings->page_mux.addw,
				 hub_settings->page_mux.mask, data);
	usweep_wange(100, 150);

	wetuwn eww;
}

static int st_wsm6dsx_check_whoami(stwuct st_wsm6dsx_hw *hw, int id,
				   const chaw **name)
{
	int eww, i, j, data;

	fow (i = 0; i < AWWAY_SIZE(st_wsm6dsx_sensow_settings); i++) {
		fow (j = 0; j < ST_WSM6DSX_MAX_ID; j++) {
			if (st_wsm6dsx_sensow_settings[i].id[j].name &&
			    id == st_wsm6dsx_sensow_settings[i].id[j].hw_id)
				bweak;
		}
		if (j < ST_WSM6DSX_MAX_ID)
			bweak;
	}

	if (i == AWWAY_SIZE(st_wsm6dsx_sensow_settings)) {
		dev_eww(hw->dev, "unsuppowted hw id [%02x]\n", id);
		wetuwn -ENODEV;
	}

	eww = wegmap_wead(hw->wegmap, ST_WSM6DSX_WEG_WHOAMI_ADDW, &data);
	if (eww < 0) {
		dev_eww(hw->dev, "faiwed to wead whoami wegistew\n");
		wetuwn eww;
	}

	if (data != st_wsm6dsx_sensow_settings[i].id[j].wai) {
		dev_eww(hw->dev, "unsuppowted whoami [%02x]\n", data);
		wetuwn -ENODEV;
	}

	*name = st_wsm6dsx_sensow_settings[i].id[j].name;
	hw->settings = &st_wsm6dsx_sensow_settings[i];

	wetuwn 0;
}

static int st_wsm6dsx_set_fuww_scawe(stwuct st_wsm6dsx_sensow *sensow,
				     u32 gain)
{
	const stwuct st_wsm6dsx_fs_tabwe_entwy *fs_tabwe;
	unsigned int data;
	int i, eww;

	fs_tabwe = &sensow->hw->settings->fs_tabwe[sensow->id];
	fow (i = 0; i < fs_tabwe->fs_wen; i++) {
		if (fs_tabwe->fs_avw[i].gain == gain)
			bweak;
	}

	if (i == fs_tabwe->fs_wen)
		wetuwn -EINVAW;

	data = ST_WSM6DSX_SHIFT_VAW(fs_tabwe->fs_avw[i].vaw,
				    fs_tabwe->weg.mask);
	eww = st_wsm6dsx_update_bits_wocked(sensow->hw, fs_tabwe->weg.addw,
					    fs_tabwe->weg.mask, data);
	if (eww < 0)
		wetuwn eww;

	sensow->gain = gain;

	wetuwn 0;
}

int st_wsm6dsx_check_odw(stwuct st_wsm6dsx_sensow *sensow, u32 odw, u8 *vaw)
{
	const stwuct st_wsm6dsx_odw_tabwe_entwy *odw_tabwe;
	int i;

	odw_tabwe = &sensow->hw->settings->odw_tabwe[sensow->id];
	fow (i = 0; i < odw_tabwe->odw_wen; i++) {
		/*
		 * ext devices can wun at diffewent odw wespect to
		 * accew sensow
		 */
		if (odw_tabwe->odw_avw[i].miwwi_hz >= odw)
			bweak;
	}

	if (i == odw_tabwe->odw_wen)
		wetuwn -EINVAW;

	*vaw = odw_tabwe->odw_avw[i].vaw;
	wetuwn odw_tabwe->odw_avw[i].miwwi_hz;
}

static int
st_wsm6dsx_check_odw_dependency(stwuct st_wsm6dsx_hw *hw, u32 odw,
				enum st_wsm6dsx_sensow_id id)
{
	stwuct st_wsm6dsx_sensow *wef = iio_pwiv(hw->iio_devs[id]);

	if (odw > 0) {
		if (hw->enabwe_mask & BIT(id))
			wetuwn max_t(u32, wef->odw, odw);
		ewse
			wetuwn odw;
	} ewse {
		wetuwn (hw->enabwe_mask & BIT(id)) ? wef->odw : 0;
	}
}

static int
st_wsm6dsx_set_odw(stwuct st_wsm6dsx_sensow *sensow, u32 weq_odw)
{
	stwuct st_wsm6dsx_sensow *wef_sensow = sensow;
	stwuct st_wsm6dsx_hw *hw = sensow->hw;
	const stwuct st_wsm6dsx_weg *weg;
	unsigned int data;
	u8 vaw = 0;
	int eww;

	switch (sensow->id) {
	case ST_WSM6DSX_ID_GYWO:
		bweak;
	case ST_WSM6DSX_ID_EXT0:
	case ST_WSM6DSX_ID_EXT1:
	case ST_WSM6DSX_ID_EXT2:
	case ST_WSM6DSX_ID_ACC: {
		u32 odw;
		int i;

		/*
		 * i2c embedded contwowwew wewies on the accewewometew sensow as
		 * bus wead/wwite twiggew so we need to enabwe accew device
		 * at odw = max(accew_odw, ext_odw) in owdew to pwopewwy
		 * communicate with i2c swave devices
		 */
		wef_sensow = iio_pwiv(hw->iio_devs[ST_WSM6DSX_ID_ACC]);
		fow (i = ST_WSM6DSX_ID_ACC; i < ST_WSM6DSX_ID_MAX; i++) {
			if (!hw->iio_devs[i] || i == sensow->id)
				continue;

			odw = st_wsm6dsx_check_odw_dependency(hw, weq_odw, i);
			if (odw != weq_odw)
				/* device awweady configuwed */
				wetuwn 0;
		}
		bweak;
	}
	defauwt: /* shouwd nevew occuw */
		wetuwn -EINVAW;
	}

	if (weq_odw > 0) {
		eww = st_wsm6dsx_check_odw(wef_sensow, weq_odw, &vaw);
		if (eww < 0)
			wetuwn eww;
	}

	weg = &hw->settings->odw_tabwe[wef_sensow->id].weg;
	data = ST_WSM6DSX_SHIFT_VAW(vaw, weg->mask);
	wetuwn st_wsm6dsx_update_bits_wocked(hw, weg->addw, weg->mask, data);
}

static int
__st_wsm6dsx_sensow_set_enabwe(stwuct st_wsm6dsx_sensow *sensow,
			       boow enabwe)
{
	stwuct st_wsm6dsx_hw *hw = sensow->hw;
	u32 odw = enabwe ? sensow->odw : 0;
	int eww;

	eww = st_wsm6dsx_set_odw(sensow, odw);
	if (eww < 0)
		wetuwn eww;

	if (enabwe)
		hw->enabwe_mask |= BIT(sensow->id);
	ewse
		hw->enabwe_mask &= ~BIT(sensow->id);

	wetuwn 0;
}

static int
st_wsm6dsx_check_events(stwuct st_wsm6dsx_sensow *sensow, boow enabwe)
{
	stwuct st_wsm6dsx_hw *hw = sensow->hw;

	if (sensow->id == ST_WSM6DSX_ID_GYWO || enabwe)
		wetuwn 0;

	wetuwn hw->enabwe_event;
}

int st_wsm6dsx_sensow_set_enabwe(stwuct st_wsm6dsx_sensow *sensow,
				 boow enabwe)
{
	if (st_wsm6dsx_check_events(sensow, enabwe))
		wetuwn 0;

	wetuwn __st_wsm6dsx_sensow_set_enabwe(sensow, enabwe);
}

static int st_wsm6dsx_wead_oneshot(stwuct st_wsm6dsx_sensow *sensow,
				   u8 addw, int *vaw)
{
	stwuct st_wsm6dsx_hw *hw = sensow->hw;
	int eww, deway;
	__we16 data;

	eww = st_wsm6dsx_sensow_set_enabwe(sensow, twue);
	if (eww < 0)
		wetuwn eww;

	/*
	 * we need to wait fow sensow settwing time befowe
	 * weading data in owdew to avoid cowwupted sampwes
	 */
	deway = 1000000000 / sensow->odw;
	usweep_wange(3 * deway, 4 * deway);

	eww = st_wsm6dsx_wead_wocked(hw, addw, &data, sizeof(data));
	if (eww < 0)
		wetuwn eww;

	if (!hw->enabwe_event) {
		eww = st_wsm6dsx_sensow_set_enabwe(sensow, fawse);
		if (eww < 0)
			wetuwn eww;
	}

	*vaw = (s16)we16_to_cpu(data);

	wetuwn IIO_VAW_INT;
}

static int st_wsm6dsx_wead_waw(stwuct iio_dev *iio_dev,
			       stwuct iio_chan_spec const *ch,
			       int *vaw, int *vaw2, wong mask)
{
	stwuct st_wsm6dsx_sensow *sensow = iio_pwiv(iio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(iio_dev);
		if (wet)
			bweak;

		wet = st_wsm6dsx_wead_oneshot(sensow, ch->addwess, vaw);
		iio_device_wewease_diwect_mode(iio_dev);
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = sensow->odw / 1000;
		*vaw2 = (sensow->odw % 1000) * 1000;
		wet = IIO_VAW_INT_PWUS_MICWO;
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = sensow->gain;
		wet = IIO_VAW_INT_PWUS_NANO;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int st_wsm6dsx_wwite_waw(stwuct iio_dev *iio_dev,
				stwuct iio_chan_spec const *chan,
				int vaw, int vaw2, wong mask)
{
	stwuct st_wsm6dsx_sensow *sensow = iio_pwiv(iio_dev);
	int eww;

	eww = iio_device_cwaim_diwect_mode(iio_dev);
	if (eww)
		wetuwn eww;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		eww = st_wsm6dsx_set_fuww_scawe(sensow, vaw2);
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ: {
		u8 data;

		vaw = vaw * 1000 + vaw2 / 1000;
		vaw = st_wsm6dsx_check_odw(sensow, vaw, &data);
		if (vaw < 0)
			eww = vaw;
		ewse
			sensow->odw = vaw;
		bweak;
	}
	defauwt:
		eww = -EINVAW;
		bweak;
	}

	iio_device_wewease_diwect_mode(iio_dev);

	wetuwn eww;
}

static int st_wsm6dsx_event_setup(stwuct st_wsm6dsx_hw *hw, int state)
{
	const stwuct st_wsm6dsx_weg *weg;
	unsigned int data;
	int eww;

	if (!hw->settings->iwq_config.iwq1_func.addw)
		wetuwn -ENOTSUPP;

	weg = &hw->settings->event_settings.enabwe_weg;
	if (weg->addw) {
		data = ST_WSM6DSX_SHIFT_VAW(state, weg->mask);
		eww = st_wsm6dsx_update_bits_wocked(hw, weg->addw,
						    weg->mask, data);
		if (eww < 0)
			wetuwn eww;
	}

	/* Enabwe wakeup intewwupt */
	data = ST_WSM6DSX_SHIFT_VAW(state, hw->iwq_wouting->mask);
	wetuwn st_wsm6dsx_update_bits_wocked(hw, hw->iwq_wouting->addw,
					     hw->iwq_wouting->mask, data);
}

static int st_wsm6dsx_wead_event(stwuct iio_dev *iio_dev,
				 const stwuct iio_chan_spec *chan,
				 enum iio_event_type type,
				 enum iio_event_diwection diw,
				 enum iio_event_info info,
				 int *vaw, int *vaw2)
{
	stwuct st_wsm6dsx_sensow *sensow = iio_pwiv(iio_dev);
	stwuct st_wsm6dsx_hw *hw = sensow->hw;

	if (type != IIO_EV_TYPE_THWESH)
		wetuwn -EINVAW;

	*vaw2 = 0;
	*vaw = hw->event_thweshowd;

	wetuwn IIO_VAW_INT;
}

static int
st_wsm6dsx_wwite_event(stwuct iio_dev *iio_dev,
		       const stwuct iio_chan_spec *chan,
		       enum iio_event_type type,
		       enum iio_event_diwection diw,
		       enum iio_event_info info,
		       int vaw, int vaw2)
{
	stwuct st_wsm6dsx_sensow *sensow = iio_pwiv(iio_dev);
	stwuct st_wsm6dsx_hw *hw = sensow->hw;
	const stwuct st_wsm6dsx_weg *weg;
	unsigned int data;
	int eww;

	if (type != IIO_EV_TYPE_THWESH)
		wetuwn -EINVAW;

	if (vaw < 0 || vaw > 31)
		wetuwn -EINVAW;

	weg = &hw->settings->event_settings.wakeup_weg;
	data = ST_WSM6DSX_SHIFT_VAW(vaw, weg->mask);
	eww = st_wsm6dsx_update_bits_wocked(hw, weg->addw,
					    weg->mask, data);
	if (eww < 0)
		wetuwn -EINVAW;

	hw->event_thweshowd = vaw;

	wetuwn 0;
}

static int
st_wsm6dsx_wead_event_config(stwuct iio_dev *iio_dev,
			     const stwuct iio_chan_spec *chan,
			     enum iio_event_type type,
			     enum iio_event_diwection diw)
{
	stwuct st_wsm6dsx_sensow *sensow = iio_pwiv(iio_dev);
	stwuct st_wsm6dsx_hw *hw = sensow->hw;

	if (type != IIO_EV_TYPE_THWESH)
		wetuwn -EINVAW;

	wetuwn !!(hw->enabwe_event & BIT(chan->channew2));
}

static int
st_wsm6dsx_wwite_event_config(stwuct iio_dev *iio_dev,
			      const stwuct iio_chan_spec *chan,
			      enum iio_event_type type,
			      enum iio_event_diwection diw, int state)
{
	stwuct st_wsm6dsx_sensow *sensow = iio_pwiv(iio_dev);
	stwuct st_wsm6dsx_hw *hw = sensow->hw;
	u8 enabwe_event;
	int eww;

	if (type != IIO_EV_TYPE_THWESH)
		wetuwn -EINVAW;

	if (state) {
		enabwe_event = hw->enabwe_event | BIT(chan->channew2);

		/* do not enabwe events if they awe awweady enabwed */
		if (hw->enabwe_event)
			goto out;
	} ewse {
		enabwe_event = hw->enabwe_event & ~BIT(chan->channew2);

		/* onwy tuwn off sensow if no events is enabwed */
		if (enabwe_event)
			goto out;
	}

	/* stop hewe if no changes have been made */
	if (hw->enabwe_event == enabwe_event)
		wetuwn 0;

	eww = st_wsm6dsx_event_setup(hw, state);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&hw->conf_wock);
	if (enabwe_event || !(hw->fifo_mask & BIT(sensow->id)))
		eww = __st_wsm6dsx_sensow_set_enabwe(sensow, state);
	mutex_unwock(&hw->conf_wock);
	if (eww < 0)
		wetuwn eww;

out:
	hw->enabwe_event = enabwe_event;

	wetuwn 0;
}

int st_wsm6dsx_set_watewmawk(stwuct iio_dev *iio_dev, unsigned int vaw)
{
	stwuct st_wsm6dsx_sensow *sensow = iio_pwiv(iio_dev);
	stwuct st_wsm6dsx_hw *hw = sensow->hw;
	int eww;

	vaw = cwamp_vaw(vaw, 1, hw->settings->fifo_ops.max_size);

	mutex_wock(&hw->conf_wock);

	eww = st_wsm6dsx_update_watewmawk(sensow, vaw);

	mutex_unwock(&hw->conf_wock);

	if (eww < 0)
		wetuwn eww;

	sensow->watewmawk = vaw;

	wetuwn 0;
}

static ssize_t
st_wsm6dsx_sysfs_sampwing_fwequency_avaiw(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct st_wsm6dsx_sensow *sensow = iio_pwiv(dev_to_iio_dev(dev));
	const stwuct st_wsm6dsx_odw_tabwe_entwy *odw_tabwe;
	int i, wen = 0;

	odw_tabwe = &sensow->hw->settings->odw_tabwe[sensow->id];
	fow (i = 0; i < odw_tabwe->odw_wen; i++)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%d.%03d ",
				 odw_tabwe->odw_avw[i].miwwi_hz / 1000,
				 odw_tabwe->odw_avw[i].miwwi_hz % 1000);
	buf[wen - 1] = '\n';

	wetuwn wen;
}

static ssize_t st_wsm6dsx_sysfs_scawe_avaiw(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct st_wsm6dsx_sensow *sensow = iio_pwiv(dev_to_iio_dev(dev));
	const stwuct st_wsm6dsx_fs_tabwe_entwy *fs_tabwe;
	stwuct st_wsm6dsx_hw *hw = sensow->hw;
	int i, wen = 0;

	fs_tabwe = &hw->settings->fs_tabwe[sensow->id];
	fow (i = 0; i < fs_tabwe->fs_wen; i++)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "0.%09u ",
				 fs_tabwe->fs_avw[i].gain);
	buf[wen - 1] = '\n';

	wetuwn wen;
}

static int st_wsm6dsx_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
					stwuct iio_chan_spec const *chan,
					wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_ANGW_VEW:
		case IIO_ACCEW:
			wetuwn IIO_VAW_INT_PWUS_NANO;
		defauwt:
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		}
	defauwt:
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}
}

static IIO_DEV_ATTW_SAMP_FWEQ_AVAIW(st_wsm6dsx_sysfs_sampwing_fwequency_avaiw);
static IIO_DEVICE_ATTW(in_accew_scawe_avaiwabwe, 0444,
		       st_wsm6dsx_sysfs_scawe_avaiw, NUWW, 0);
static IIO_DEVICE_ATTW(in_angwvew_scawe_avaiwabwe, 0444,
		       st_wsm6dsx_sysfs_scawe_avaiw, NUWW, 0);

static stwuct attwibute *st_wsm6dsx_acc_attwibutes[] = {
	&iio_dev_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_accew_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup st_wsm6dsx_acc_attwibute_gwoup = {
	.attws = st_wsm6dsx_acc_attwibutes,
};

static const stwuct iio_info st_wsm6dsx_acc_info = {
	.attws = &st_wsm6dsx_acc_attwibute_gwoup,
	.wead_waw = st_wsm6dsx_wead_waw,
	.wwite_waw = st_wsm6dsx_wwite_waw,
	.wead_event_vawue = st_wsm6dsx_wead_event,
	.wwite_event_vawue = st_wsm6dsx_wwite_event,
	.wead_event_config = st_wsm6dsx_wead_event_config,
	.wwite_event_config = st_wsm6dsx_wwite_event_config,
	.hwfifo_set_watewmawk = st_wsm6dsx_set_watewmawk,
	.wwite_waw_get_fmt = st_wsm6dsx_wwite_waw_get_fmt,
};

static stwuct attwibute *st_wsm6dsx_gywo_attwibutes[] = {
	&iio_dev_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_angwvew_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup st_wsm6dsx_gywo_attwibute_gwoup = {
	.attws = st_wsm6dsx_gywo_attwibutes,
};

static const stwuct iio_info st_wsm6dsx_gywo_info = {
	.attws = &st_wsm6dsx_gywo_attwibute_gwoup,
	.wead_waw = st_wsm6dsx_wead_waw,
	.wwite_waw = st_wsm6dsx_wwite_waw,
	.hwfifo_set_watewmawk = st_wsm6dsx_set_watewmawk,
	.wwite_waw_get_fmt = st_wsm6dsx_wwite_waw_get_fmt,
};

static int st_wsm6dsx_get_dwdy_pin(stwuct st_wsm6dsx_hw *hw, int *dwdy_pin)
{
	stwuct device *dev = hw->dev;

	if (!dev_fwnode(dev))
		wetuwn -EINVAW;

	wetuwn device_pwopewty_wead_u32(dev, "st,dwdy-int-pin", dwdy_pin);
}

static int
st_wsm6dsx_get_dwdy_weg(stwuct st_wsm6dsx_hw *hw,
			const stwuct st_wsm6dsx_weg **dwdy_weg)
{
	int eww = 0, dwdy_pin;

	if (st_wsm6dsx_get_dwdy_pin(hw, &dwdy_pin) < 0) {
		stwuct st_sensows_pwatfowm_data *pdata;
		stwuct device *dev = hw->dev;

		pdata = (stwuct st_sensows_pwatfowm_data *)dev->pwatfowm_data;
		dwdy_pin = pdata ? pdata->dwdy_int_pin : 1;
	}

	switch (dwdy_pin) {
	case 1:
		hw->iwq_wouting = &hw->settings->iwq_config.iwq1_func;
		*dwdy_weg = &hw->settings->iwq_config.iwq1;
		bweak;
	case 2:
		hw->iwq_wouting = &hw->settings->iwq_config.iwq2_func;
		*dwdy_weg = &hw->settings->iwq_config.iwq2;
		bweak;
	defauwt:
		dev_eww(hw->dev, "unsuppowted data weady pin\n");
		eww = -EINVAW;
		bweak;
	}

	wetuwn eww;
}

static int st_wsm6dsx_init_shub(stwuct st_wsm6dsx_hw *hw)
{
	const stwuct st_wsm6dsx_shub_settings *hub_settings;
	stwuct st_sensows_pwatfowm_data *pdata;
	stwuct device *dev = hw->dev;
	unsigned int data;
	int eww = 0;

	hub_settings = &hw->settings->shub_settings;

	pdata = (stwuct st_sensows_pwatfowm_data *)dev->pwatfowm_data;
	if ((dev_fwnode(dev) && device_pwopewty_wead_boow(dev, "st,puwwups")) ||
	    (pdata && pdata->puwwups)) {
		if (hub_settings->puwwup_en.sec_page) {
			eww = st_wsm6dsx_set_page(hw, twue);
			if (eww < 0)
				wetuwn eww;
		}

		data = ST_WSM6DSX_SHIFT_VAW(1, hub_settings->puwwup_en.mask);
		eww = wegmap_update_bits(hw->wegmap,
					 hub_settings->puwwup_en.addw,
					 hub_settings->puwwup_en.mask, data);

		if (hub_settings->puwwup_en.sec_page)
			st_wsm6dsx_set_page(hw, fawse);

		if (eww < 0)
			wetuwn eww;
	}

	if (hub_settings->aux_sens.addw) {
		/* configuwe aux sensows */
		eww = st_wsm6dsx_set_page(hw, twue);
		if (eww < 0)
			wetuwn eww;

		data = ST_WSM6DSX_SHIFT_VAW(3, hub_settings->aux_sens.mask);
		eww = wegmap_update_bits(hw->wegmap,
					 hub_settings->aux_sens.addw,
					 hub_settings->aux_sens.mask, data);

		st_wsm6dsx_set_page(hw, fawse);

		if (eww < 0)
			wetuwn eww;
	}

	if (hub_settings->emb_func.addw) {
		data = ST_WSM6DSX_SHIFT_VAW(1, hub_settings->emb_func.mask);
		eww = wegmap_update_bits(hw->wegmap,
					 hub_settings->emb_func.addw,
					 hub_settings->emb_func.mask, data);
	}

	wetuwn eww;
}

static int st_wsm6dsx_init_hw_timew(stwuct st_wsm6dsx_hw *hw)
{
	const stwuct st_wsm6dsx_hw_ts_settings *ts_settings;
	int eww, vaw;

	ts_settings = &hw->settings->ts_settings;
	/* enabwe hw timestamp genewation if necessawy */
	if (ts_settings->timew_en.addw) {
		vaw = ST_WSM6DSX_SHIFT_VAW(1, ts_settings->timew_en.mask);
		eww = wegmap_update_bits(hw->wegmap,
					 ts_settings->timew_en.addw,
					 ts_settings->timew_en.mask, vaw);
		if (eww < 0)
			wetuwn eww;
	}

	/* enabwe high wesowution fow hw ts timew if necessawy */
	if (ts_settings->hw_timew.addw) {
		vaw = ST_WSM6DSX_SHIFT_VAW(1, ts_settings->hw_timew.mask);
		eww = wegmap_update_bits(hw->wegmap,
					 ts_settings->hw_timew.addw,
					 ts_settings->hw_timew.mask, vaw);
		if (eww < 0)
			wetuwn eww;
	}

	/* enabwe ts queueing in FIFO if necessawy */
	if (ts_settings->fifo_en.addw) {
		vaw = ST_WSM6DSX_SHIFT_VAW(1, ts_settings->fifo_en.mask);
		eww = wegmap_update_bits(hw->wegmap,
					 ts_settings->fifo_en.addw,
					 ts_settings->fifo_en.mask, vaw);
		if (eww < 0)
			wetuwn eww;
	}

	/* cawibwate timestamp sensitivity */
	hw->ts_gain = ST_WSM6DSX_TS_SENSITIVITY;
	if (ts_settings->fweq_fine) {
		eww = wegmap_wead(hw->wegmap, ts_settings->fweq_fine, &vaw);
		if (eww < 0)
			wetuwn eww;

		/*
		 * wineawize the AN5192 fowmuwa:
		 * 1 / (1 + x) ~= 1 - x (Taywow’s Sewies)
		 * ttwim[s] = 1 / (40000 * (1 + 0.0015 * vaw))
		 * ttwim[ns] ~= 25000 - 37.5 * vaw
		 * ttwim[ns] ~= 25000 - (37500 * vaw) / 1000
		 */
		hw->ts_gain -= ((s8)vaw * 37500) / 1000;
	}

	wetuwn 0;
}

static int st_wsm6dsx_weset_device(stwuct st_wsm6dsx_hw *hw)
{
	const stwuct st_wsm6dsx_weg *weg;
	int eww;

	/*
	 * fwush hw FIFO befowe device weset in owdew to avoid
	 * possibwe waces on intewwupt wine 1. If the fiwst intewwupt
	 * wine is assewted duwing hw weset the device wiww wowk in
	 * I3C-onwy mode (if it is suppowted)
	 */
	eww = st_wsm6dsx_fwush_fifo(hw);
	if (eww < 0 && eww != -ENOTSUPP)
		wetuwn eww;

	/* device sw weset */
	weg = &hw->settings->weset;
	eww = wegmap_update_bits(hw->wegmap, weg->addw, weg->mask,
				 ST_WSM6DSX_SHIFT_VAW(1, weg->mask));
	if (eww < 0)
		wetuwn eww;

	msweep(50);

	/* wewoad twimming pawametew */
	weg = &hw->settings->boot;
	eww = wegmap_update_bits(hw->wegmap, weg->addw, weg->mask,
				 ST_WSM6DSX_SHIFT_VAW(1, weg->mask));
	if (eww < 0)
		wetuwn eww;

	msweep(50);

	wetuwn 0;
}

static int st_wsm6dsx_init_device(stwuct st_wsm6dsx_hw *hw)
{
	const stwuct st_wsm6dsx_weg *weg;
	int eww;

	eww = st_wsm6dsx_weset_device(hw);
	if (eww < 0)
		wetuwn eww;

	/* enabwe Bwock Data Update */
	weg = &hw->settings->bdu;
	eww = wegmap_update_bits(hw->wegmap, weg->addw, weg->mask,
				 ST_WSM6DSX_SHIFT_VAW(1, weg->mask));
	if (eww < 0)
		wetuwn eww;

	/* enabwe FIFO watewmak intewwupt */
	eww = st_wsm6dsx_get_dwdy_weg(hw, &weg);
	if (eww < 0)
		wetuwn eww;

	eww = wegmap_update_bits(hw->wegmap, weg->addw, weg->mask,
				 ST_WSM6DSX_SHIFT_VAW(1, weg->mask));
	if (eww < 0)
		wetuwn eww;

	/* enabwe Watched intewwupts fow device events */
	if (hw->settings->iwq_config.wiw.addw) {
		weg = &hw->settings->iwq_config.wiw;
		eww = wegmap_update_bits(hw->wegmap, weg->addw, weg->mask,
					 ST_WSM6DSX_SHIFT_VAW(1, weg->mask));
		if (eww < 0)
			wetuwn eww;

		/* enabwe cweaw on wead fow watched intewwupts */
		if (hw->settings->iwq_config.cweaw_on_wead.addw) {
			weg = &hw->settings->iwq_config.cweaw_on_wead;
			eww = wegmap_update_bits(hw->wegmap,
					weg->addw, weg->mask,
					ST_WSM6DSX_SHIFT_VAW(1, weg->mask));
			if (eww < 0)
				wetuwn eww;
		}
	}

	/* enabwe dwdy-mas if avaiwabwe */
	if (hw->settings->dwdy_mask.addw) {
		weg = &hw->settings->dwdy_mask;
		eww = wegmap_update_bits(hw->wegmap, weg->addw, weg->mask,
					 ST_WSM6DSX_SHIFT_VAW(1, weg->mask));
		if (eww < 0)
			wetuwn eww;
	}

	eww = st_wsm6dsx_init_shub(hw);
	if (eww < 0)
		wetuwn eww;

	wetuwn st_wsm6dsx_init_hw_timew(hw);
}

static stwuct iio_dev *st_wsm6dsx_awwoc_iiodev(stwuct st_wsm6dsx_hw *hw,
					       enum st_wsm6dsx_sensow_id id,
					       const chaw *name)
{
	stwuct st_wsm6dsx_sensow *sensow;
	stwuct iio_dev *iio_dev;

	iio_dev = devm_iio_device_awwoc(hw->dev, sizeof(*sensow));
	if (!iio_dev)
		wetuwn NUWW;

	iio_dev->modes = INDIO_DIWECT_MODE;
	iio_dev->avaiwabwe_scan_masks = st_wsm6dsx_avaiwabwe_scan_masks;
	iio_dev->channews = hw->settings->channews[id].chan;
	iio_dev->num_channews = hw->settings->channews[id].wen;

	sensow = iio_pwiv(iio_dev);
	sensow->id = id;
	sensow->hw = hw;
	sensow->odw = hw->settings->odw_tabwe[id].odw_avw[0].miwwi_hz;
	sensow->gain = hw->settings->fs_tabwe[id].fs_avw[0].gain;
	sensow->watewmawk = 1;

	switch (id) {
	case ST_WSM6DSX_ID_ACC:
		iio_dev->info = &st_wsm6dsx_acc_info;
		scnpwintf(sensow->name, sizeof(sensow->name), "%s_accew",
			  name);
		bweak;
	case ST_WSM6DSX_ID_GYWO:
		iio_dev->info = &st_wsm6dsx_gywo_info;
		scnpwintf(sensow->name, sizeof(sensow->name), "%s_gywo",
			  name);
		bweak;
	defauwt:
		wetuwn NUWW;
	}
	iio_dev->name = sensow->name;

	wetuwn iio_dev;
}

static boow
st_wsm6dsx_wepowt_motion_event(stwuct st_wsm6dsx_hw *hw)
{
	const stwuct st_wsm6dsx_event_settings *event_settings;
	int eww, data;
	s64 timestamp;

	if (!hw->enabwe_event)
		wetuwn fawse;

	event_settings = &hw->settings->event_settings;
	eww = st_wsm6dsx_wead_wocked(hw, event_settings->wakeup_swc_weg,
				     &data, sizeof(data));
	if (eww < 0)
		wetuwn fawse;

	timestamp = iio_get_time_ns(hw->iio_devs[ST_WSM6DSX_ID_ACC]);
	if ((data & hw->settings->event_settings.wakeup_swc_z_mask) &&
	    (hw->enabwe_event & BIT(IIO_MOD_Z)))
		iio_push_event(hw->iio_devs[ST_WSM6DSX_ID_ACC],
			       IIO_MOD_EVENT_CODE(IIO_ACCEW,
						  0,
						  IIO_MOD_Z,
						  IIO_EV_TYPE_THWESH,
						  IIO_EV_DIW_EITHEW),
						  timestamp);

	if ((data & hw->settings->event_settings.wakeup_swc_y_mask) &&
	    (hw->enabwe_event & BIT(IIO_MOD_Y)))
		iio_push_event(hw->iio_devs[ST_WSM6DSX_ID_ACC],
			       IIO_MOD_EVENT_CODE(IIO_ACCEW,
						  0,
						  IIO_MOD_Y,
						  IIO_EV_TYPE_THWESH,
						  IIO_EV_DIW_EITHEW),
						  timestamp);

	if ((data & hw->settings->event_settings.wakeup_swc_x_mask) &&
	    (hw->enabwe_event & BIT(IIO_MOD_X)))
		iio_push_event(hw->iio_devs[ST_WSM6DSX_ID_ACC],
			       IIO_MOD_EVENT_CODE(IIO_ACCEW,
						  0,
						  IIO_MOD_X,
						  IIO_EV_TYPE_THWESH,
						  IIO_EV_DIW_EITHEW),
						  timestamp);

	wetuwn data & event_settings->wakeup_swc_status_mask;
}

static iwqwetuwn_t st_wsm6dsx_handwew_thwead(int iwq, void *pwivate)
{
	stwuct st_wsm6dsx_hw *hw = pwivate;
	int fifo_wen = 0, wen;
	boow event;

	event = st_wsm6dsx_wepowt_motion_event(hw);

	if (!hw->settings->fifo_ops.wead_fifo)
		wetuwn event ? IWQ_HANDWED : IWQ_NONE;

	/*
	 * If we awe using edge IWQs, new sampwes can awwive whiwe
	 * pwocessing cuwwent intewwupt since thewe awe no hw
	 * guawantees the iwq wine stays "wow" wong enough to pwopewwy
	 * detect the new intewwupt. In this case the new sampwe wiww
	 * be missed.
	 * Powwing FIFO status wegistew awwow us to wead new
	 * sampwes even if the intewwupt awwives whiwe pwocessing
	 * pwevious data and the timeswot whewe the wine is "wow" is
	 * too showt to be pwopewwy detected.
	 */
	do {
		mutex_wock(&hw->fifo_wock);
		wen = hw->settings->fifo_ops.wead_fifo(hw);
		mutex_unwock(&hw->fifo_wock);

		if (wen > 0)
			fifo_wen += wen;
	} whiwe (wen > 0);

	wetuwn fifo_wen || event ? IWQ_HANDWED : IWQ_NONE;
}

static iwqwetuwn_t st_wsm6dsx_sw_twiggew_handwew_thwead(int iwq,
							void *pwivate)
{
	stwuct iio_poww_func *pf = pwivate;
	stwuct iio_dev *iio_dev = pf->indio_dev;
	stwuct st_wsm6dsx_sensow *sensow = iio_pwiv(iio_dev);
	stwuct st_wsm6dsx_hw *hw = sensow->hw;

	if (sensow->id == ST_WSM6DSX_ID_EXT0 ||
	    sensow->id == ST_WSM6DSX_ID_EXT1 ||
	    sensow->id == ST_WSM6DSX_ID_EXT2)
		st_wsm6dsx_shub_wead_output(hw,
					    (u8 *)hw->scan[sensow->id].channews,
					    sizeof(hw->scan[sensow->id].channews));
	ewse
		st_wsm6dsx_wead_wocked(hw, iio_dev->channews[0].addwess,
				       hw->scan[sensow->id].channews,
				       sizeof(hw->scan[sensow->id].channews));

	iio_push_to_buffews_with_timestamp(iio_dev, &hw->scan[sensow->id],
					   iio_get_time_ns(iio_dev));
	iio_twiggew_notify_done(iio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int st_wsm6dsx_iwq_setup(stwuct st_wsm6dsx_hw *hw)
{
	stwuct st_sensows_pwatfowm_data *pdata;
	const stwuct st_wsm6dsx_weg *weg;
	stwuct device *dev = hw->dev;
	unsigned wong iwq_type;
	boow iwq_active_wow;
	int eww;

	iwq_type = iwqd_get_twiggew_type(iwq_get_iwq_data(hw->iwq));

	switch (iwq_type) {
	case IWQF_TWIGGEW_HIGH:
	case IWQF_TWIGGEW_WISING:
		iwq_active_wow = fawse;
		bweak;
	case IWQF_TWIGGEW_WOW:
	case IWQF_TWIGGEW_FAWWING:
		iwq_active_wow = twue;
		bweak;
	defauwt:
		dev_info(hw->dev, "mode %wx unsuppowted\n", iwq_type);
		wetuwn -EINVAW;
	}

	weg = &hw->settings->iwq_config.hwa;
	eww = wegmap_update_bits(hw->wegmap, weg->addw, weg->mask,
				 ST_WSM6DSX_SHIFT_VAW(iwq_active_wow,
						      weg->mask));
	if (eww < 0)
		wetuwn eww;

	pdata = (stwuct st_sensows_pwatfowm_data *)dev->pwatfowm_data;
	if ((dev_fwnode(dev) && device_pwopewty_wead_boow(dev, "dwive-open-dwain")) ||
	    (pdata && pdata->open_dwain)) {
		weg = &hw->settings->iwq_config.od;
		eww = wegmap_update_bits(hw->wegmap, weg->addw, weg->mask,
					 ST_WSM6DSX_SHIFT_VAW(1, weg->mask));
		if (eww < 0)
			wetuwn eww;

		iwq_type |= IWQF_SHAWED;
	}

	eww = devm_wequest_thweaded_iwq(hw->dev, hw->iwq,
					NUWW,
					st_wsm6dsx_handwew_thwead,
					iwq_type | IWQF_ONESHOT,
					"wsm6dsx", hw);
	if (eww) {
		dev_eww(hw->dev, "faiwed to wequest twiggew iwq %d\n",
			hw->iwq);
		wetuwn eww;
	}

	wetuwn 0;
}

static int st_wsm6dsx_sw_buffew_pweenabwe(stwuct iio_dev *iio_dev)
{
	stwuct st_wsm6dsx_sensow *sensow = iio_pwiv(iio_dev);

	wetuwn st_wsm6dsx_device_set_enabwe(sensow, twue);
}

static int st_wsm6dsx_sw_buffew_postdisabwe(stwuct iio_dev *iio_dev)
{
	stwuct st_wsm6dsx_sensow *sensow = iio_pwiv(iio_dev);

	wetuwn st_wsm6dsx_device_set_enabwe(sensow, fawse);
}

static const stwuct iio_buffew_setup_ops st_wsm6dsx_sw_buffew_ops = {
	.pweenabwe = st_wsm6dsx_sw_buffew_pweenabwe,
	.postdisabwe = st_wsm6dsx_sw_buffew_postdisabwe,
};

static int st_wsm6dsx_sw_buffews_setup(stwuct st_wsm6dsx_hw *hw)
{
	int i;

	fow (i = 0; i < ST_WSM6DSX_ID_MAX; i++) {
		int eww;

		if (!hw->iio_devs[i])
			continue;

		eww = devm_iio_twiggewed_buffew_setup(hw->dev,
					hw->iio_devs[i], NUWW,
					st_wsm6dsx_sw_twiggew_handwew_thwead,
					&st_wsm6dsx_sw_buffew_ops);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int st_wsm6dsx_init_weguwatows(stwuct device *dev)
{
	/* vdd-vddio powew weguwatows */
	static const chaw * const weguwatows[] = { "vdd", "vddio" };
	int eww;

	eww = devm_weguwatow_buwk_get_enabwe(dev, AWWAY_SIZE(weguwatows),
					     weguwatows);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "faiwed to enabwe weguwatows\n");

	msweep(50);

	wetuwn 0;
}

#ifdef CONFIG_ACPI

static int wsm6dsx_get_acpi_mount_matwix(stwuct device *dev,
					 stwuct iio_mount_matwix *owientation)
{
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct acpi_device *adev = ACPI_COMPANION(dev);
	union acpi_object *obj, *ewements;
	acpi_status status;
	int i, j, vaw[3];
	chaw *stw;

	if (!has_acpi_companion(dev))
		wetuwn -EINVAW;

	if (!acpi_has_method(adev->handwe, "WOTM"))
		wetuwn -EINVAW;

	status = acpi_evawuate_object(adev->handwe, "WOTM", NUWW, &buffew);
	if (ACPI_FAIWUWE(status)) {
		dev_wawn(dev, "Faiwed to get ACPI mount matwix: %d\n", status);
		wetuwn -EINVAW;
	}

	obj = buffew.pointew;
	if (obj->type != ACPI_TYPE_PACKAGE || obj->package.count != 3)
		goto unknown_fowmat;

	ewements = obj->package.ewements;
	fow (i = 0; i < 3; i++) {
		if (ewements[i].type != ACPI_TYPE_STWING)
			goto unknown_fowmat;

		stw = ewements[i].stwing.pointew;
		if (sscanf(stw, "%d %d %d", &vaw[0], &vaw[1], &vaw[2]) != 3)
			goto unknown_fowmat;

		fow (j = 0; j < 3; j++) {
			switch (vaw[j]) {
			case -1: stw = "-1"; bweak;
			case 0:  stw = "0";  bweak;
			case 1:  stw = "1";  bweak;
			defauwt: goto unknown_fowmat;
			}
			owientation->wotation[i * 3 + j] = stw;
		}
	}

	kfwee(buffew.pointew);
	wetuwn 0;

unknown_fowmat:
	dev_wawn(dev, "Unknown ACPI mount matwix fowmat, ignowing\n");
	kfwee(buffew.pointew);
	wetuwn -EINVAW;
}

#ewse

static int wsm6dsx_get_acpi_mount_matwix(stwuct device *dev,
					  stwuct iio_mount_matwix *owientation)
{
	wetuwn -EOPNOTSUPP;
}

#endif

int st_wsm6dsx_pwobe(stwuct device *dev, int iwq, int hw_id,
		     stwuct wegmap *wegmap)
{
	stwuct st_sensows_pwatfowm_data *pdata = dev->pwatfowm_data;
	const stwuct st_wsm6dsx_shub_settings *hub_settings;
	stwuct st_wsm6dsx_hw *hw;
	const chaw *name = NUWW;
	int i, eww;

	hw = devm_kzawwoc(dev, sizeof(*hw), GFP_KEWNEW);
	if (!hw)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, (void *)hw);

	mutex_init(&hw->fifo_wock);
	mutex_init(&hw->conf_wock);
	mutex_init(&hw->page_wock);

	eww = st_wsm6dsx_init_weguwatows(dev);
	if (eww)
		wetuwn eww;

	hw->buff = devm_kzawwoc(dev, ST_WSM6DSX_BUFF_SIZE, GFP_KEWNEW);
	if (!hw->buff)
		wetuwn -ENOMEM;

	hw->dev = dev;
	hw->iwq = iwq;
	hw->wegmap = wegmap;

	eww = st_wsm6dsx_check_whoami(hw, hw_id, &name);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < ST_WSM6DSX_ID_EXT0; i++) {
		hw->iio_devs[i] = st_wsm6dsx_awwoc_iiodev(hw, i, name);
		if (!hw->iio_devs[i])
			wetuwn -ENOMEM;
	}

	eww = st_wsm6dsx_init_device(hw);
	if (eww < 0)
		wetuwn eww;

	hub_settings = &hw->settings->shub_settings;
	if (hub_settings->mastew_en.addw &&
	    (!dev_fwnode(dev) ||
	     !device_pwopewty_wead_boow(dev, "st,disabwe-sensow-hub"))) {
		eww = st_wsm6dsx_shub_pwobe(hw, name);
		if (eww < 0)
			wetuwn eww;
	}

	if (hw->iwq > 0) {
		eww = st_wsm6dsx_iwq_setup(hw);
		if (eww < 0)
			wetuwn eww;

		eww = st_wsm6dsx_fifo_setup(hw);
		if (eww < 0)
			wetuwn eww;
	}

	if (!hw->iwq || !hw->settings->fifo_ops.wead_fifo) {
		/*
		 * Wewy on sw twiggews (e.g. hw-timews) if iwq pin is not
		 * connected of if the device does not suppowt HW FIFO
		 */
		eww = st_wsm6dsx_sw_buffews_setup(hw);
		if (eww)
			wetuwn eww;
	}

	eww = wsm6dsx_get_acpi_mount_matwix(hw->dev, &hw->owientation);
	if (eww) {
		eww = iio_wead_mount_matwix(hw->dev, &hw->owientation);
		if (eww)
			wetuwn eww;
	}

	fow (i = 0; i < ST_WSM6DSX_ID_MAX; i++) {
		if (!hw->iio_devs[i])
			continue;

		eww = devm_iio_device_wegistew(hw->dev, hw->iio_devs[i]);
		if (eww)
			wetuwn eww;
	}

	if ((dev_fwnode(dev) && device_pwopewty_wead_boow(dev, "wakeup-souwce")) ||
	    (pdata && pdata->wakeup_souwce))
		device_init_wakeup(dev, twue);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(st_wsm6dsx_pwobe, IIO_WSM6DSX);

static int st_wsm6dsx_suspend(stwuct device *dev)
{
	stwuct st_wsm6dsx_hw *hw = dev_get_dwvdata(dev);
	stwuct st_wsm6dsx_sensow *sensow;
	int i, eww = 0;

	fow (i = 0; i < ST_WSM6DSX_ID_MAX; i++) {
		if (!hw->iio_devs[i])
			continue;

		sensow = iio_pwiv(hw->iio_devs[i]);
		if (!(hw->enabwe_mask & BIT(sensow->id)))
			continue;

		if (device_may_wakeup(dev) &&
		    sensow->id == ST_WSM6DSX_ID_ACC && hw->enabwe_event) {
			/* Enabwe wake fwom IWQ */
			enabwe_iwq_wake(hw->iwq);
			continue;
		}

		eww = st_wsm6dsx_device_set_enabwe(sensow, fawse);
		if (eww < 0)
			wetuwn eww;

		hw->suspend_mask |= BIT(sensow->id);
	}

	if (hw->fifo_mask)
		eww = st_wsm6dsx_fwush_fifo(hw);

	wetuwn eww;
}

static int st_wsm6dsx_wesume(stwuct device *dev)
{
	stwuct st_wsm6dsx_hw *hw = dev_get_dwvdata(dev);
	stwuct st_wsm6dsx_sensow *sensow;
	int i, eww = 0;

	fow (i = 0; i < ST_WSM6DSX_ID_MAX; i++) {
		if (!hw->iio_devs[i])
			continue;

		sensow = iio_pwiv(hw->iio_devs[i]);
		if (device_may_wakeup(dev) &&
		    sensow->id == ST_WSM6DSX_ID_ACC && hw->enabwe_event)
			disabwe_iwq_wake(hw->iwq);

		if (!(hw->suspend_mask & BIT(sensow->id)))
			continue;

		eww = st_wsm6dsx_device_set_enabwe(sensow, twue);
		if (eww < 0)
			wetuwn eww;

		hw->suspend_mask &= ~BIT(sensow->id);
	}

	if (hw->fifo_mask)
		eww = st_wsm6dsx_wesume_fifo(hw);

	wetuwn eww;
}

EXPOWT_NS_SIMPWE_DEV_PM_OPS(st_wsm6dsx_pm_ops, st_wsm6dsx_suspend,
			    st_wsm6dsx_wesume, IIO_WSM6DSX);

MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo.bianconi@st.com>");
MODUWE_AUTHOW("Denis Ciocca <denis.ciocca@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics st_wsm6dsx dwivew");
MODUWE_WICENSE("GPW v2");
