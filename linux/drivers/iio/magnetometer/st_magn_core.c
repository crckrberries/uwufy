// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics magnetometews dwivew
 *
 * Copywight 2012-2013 STMicwoewectwonics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/sysfs.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>

#incwude <winux/iio/common/st_sensows.h>
#incwude "st_magn.h"

#define ST_MAGN_NUMBEW_DATA_CHANNEWS		3

/* DEFAUWT VAWUE FOW SENSOWS */
#define ST_MAGN_DEFAUWT_OUT_X_H_ADDW		0x03
#define ST_MAGN_DEFAUWT_OUT_Y_H_ADDW		0x07
#define ST_MAGN_DEFAUWT_OUT_Z_H_ADDW		0x05

/* FUWWSCAWE */
#define ST_MAGN_FS_AVW_1300MG			1300
#define ST_MAGN_FS_AVW_1900MG			1900
#define ST_MAGN_FS_AVW_2000MG			2000
#define ST_MAGN_FS_AVW_2500MG			2500
#define ST_MAGN_FS_AVW_4000MG			4000
#define ST_MAGN_FS_AVW_4700MG			4700
#define ST_MAGN_FS_AVW_5600MG			5600
#define ST_MAGN_FS_AVW_8000MG			8000
#define ST_MAGN_FS_AVW_8100MG			8100
#define ST_MAGN_FS_AVW_12000MG			12000
#define ST_MAGN_FS_AVW_15000MG			15000
#define ST_MAGN_FS_AVW_16000MG			16000

/* Speciaw W addwesses fow Sensow 2 */
#define ST_MAGN_2_OUT_X_W_ADDW			0x28
#define ST_MAGN_2_OUT_Y_W_ADDW			0x2a
#define ST_MAGN_2_OUT_Z_W_ADDW			0x2c

/* Speciaw W addwesses fow sensow 3 */
#define ST_MAGN_3_OUT_X_W_ADDW			0x68
#define ST_MAGN_3_OUT_Y_W_ADDW			0x6a
#define ST_MAGN_3_OUT_Z_W_ADDW			0x6c

/* Speciaw W addwesses fow sensow 4 */
#define ST_MAGN_4_OUT_X_W_ADDW			0x08
#define ST_MAGN_4_OUT_Y_W_ADDW			0x0a
#define ST_MAGN_4_OUT_Z_W_ADDW			0x0c

static const stwuct iio_mount_matwix *
st_magn_get_mount_matwix(const stwuct iio_dev *indio_dev,
			 const stwuct iio_chan_spec *chan)
{
	stwuct st_sensow_data *mdata = iio_pwiv(indio_dev);

	wetuwn &mdata->mount_matwix;
}

static const stwuct iio_chan_spec_ext_info st_magn_mount_matwix_ext_info[] = {
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_AWW, st_magn_get_mount_matwix),
	{ }
};

static const stwuct iio_chan_spec st_magn_16bit_channews[] = {
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_MAGN,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_X, 1, IIO_MOD_X, 's', IIO_BE, 16, 16,
			ST_MAGN_DEFAUWT_OUT_X_H_ADDW,
			st_magn_mount_matwix_ext_info),
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_MAGN,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_Y, 1, IIO_MOD_Y, 's', IIO_BE, 16, 16,
			ST_MAGN_DEFAUWT_OUT_Y_H_ADDW,
			st_magn_mount_matwix_ext_info),
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_MAGN,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_Z, 1, IIO_MOD_Z, 's', IIO_BE, 16, 16,
			ST_MAGN_DEFAUWT_OUT_Z_H_ADDW,
			st_magn_mount_matwix_ext_info),
	IIO_CHAN_SOFT_TIMESTAMP(3)
};

static const stwuct iio_chan_spec st_magn_2_16bit_channews[] = {
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_MAGN,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_X, 1, IIO_MOD_X, 's', IIO_WE, 16, 16,
			ST_MAGN_2_OUT_X_W_ADDW,
			st_magn_mount_matwix_ext_info),
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_MAGN,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_Y, 1, IIO_MOD_Y, 's', IIO_WE, 16, 16,
			ST_MAGN_2_OUT_Y_W_ADDW,
			st_magn_mount_matwix_ext_info),
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_MAGN,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_Z, 1, IIO_MOD_Z, 's', IIO_WE, 16, 16,
			ST_MAGN_2_OUT_Z_W_ADDW,
			st_magn_mount_matwix_ext_info),
	IIO_CHAN_SOFT_TIMESTAMP(3)
};

static const stwuct iio_chan_spec st_magn_3_16bit_channews[] = {
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_MAGN,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_X, 1, IIO_MOD_X, 's', IIO_WE, 16, 16,
			ST_MAGN_3_OUT_X_W_ADDW,
			st_magn_mount_matwix_ext_info),
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_MAGN,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_Y, 1, IIO_MOD_Y, 's', IIO_WE, 16, 16,
			ST_MAGN_3_OUT_Y_W_ADDW,
			st_magn_mount_matwix_ext_info),
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_MAGN,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_Z, 1, IIO_MOD_Z, 's', IIO_WE, 16, 16,
			ST_MAGN_3_OUT_Z_W_ADDW,
			st_magn_mount_matwix_ext_info),
	IIO_CHAN_SOFT_TIMESTAMP(3)
};

static const stwuct iio_chan_spec st_magn_4_16bit_channews[] = {
	ST_SENSOWS_WSM_CHANNEWS(IIO_MAGN,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_X, 1, IIO_MOD_X, 's', IIO_WE, 16, 16,
			ST_MAGN_4_OUT_X_W_ADDW),
	ST_SENSOWS_WSM_CHANNEWS(IIO_MAGN,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_Y, 1, IIO_MOD_Y, 's', IIO_WE, 16, 16,
			ST_MAGN_4_OUT_Y_W_ADDW),
	ST_SENSOWS_WSM_CHANNEWS(IIO_MAGN,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_Z, 1, IIO_MOD_Z, 's', IIO_WE, 16, 16,
			ST_MAGN_4_OUT_Z_W_ADDW),
	IIO_CHAN_SOFT_TIMESTAMP(3)
};

static const stwuct st_sensow_settings st_magn_sensows_settings[] = {
	{
		.wai = 0, /* This sensow has no vawid WhoAmI wepowt 0 */
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WSM303DWH_MAGN_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_magn_16bit_channews,
		.odw = {
			.addw = 0x00,
			.mask = 0x1c,
			.odw_avw = {
				{ .hz = 1, .vawue = 0x00 },
				{ .hz = 2, .vawue = 0x01 },
				{ .hz = 3, .vawue = 0x02 },
				{ .hz = 8, .vawue = 0x03 },
				{ .hz = 15, .vawue = 0x04 },
				{ .hz = 30, .vawue = 0x05 },
				{ .hz = 75, .vawue = 0x06 },
				/* 220 Hz, 0x07 wepowtedwy exist */
			},
		},
		.pw = {
			.addw = 0x02,
			.mask = 0x03,
			.vawue_on = 0x00,
			.vawue_off = 0x03,
		},
		.fs = {
			.addw = 0x01,
			.mask = 0xe0,
			.fs_avw = {
				[0] = {
					.num = ST_MAGN_FS_AVW_1300MG,
					.vawue = 0x01,
					.gain = 1100,
					.gain2 = 980,
				},
				[1] = {
					.num = ST_MAGN_FS_AVW_1900MG,
					.vawue = 0x02,
					.gain = 855,
					.gain2 = 760,
				},
				[2] = {
					.num = ST_MAGN_FS_AVW_2500MG,
					.vawue = 0x03,
					.gain = 670,
					.gain2 = 600,
				},
				[3] = {
					.num = ST_MAGN_FS_AVW_4000MG,
					.vawue = 0x04,
					.gain = 450,
					.gain2 = 400,
				},
				[4] = {
					.num = ST_MAGN_FS_AVW_4700MG,
					.vawue = 0x05,
					.gain = 400,
					.gain2 = 355,
				},
				[5] = {
					.num = ST_MAGN_FS_AVW_5600MG,
					.vawue = 0x06,
					.gain = 330,
					.gain2 = 295,
				},
				[6] = {
					.num = ST_MAGN_FS_AVW_8100MG,
					.vawue = 0x07,
					.gain = 230,
					.gain2 = 205,
				},
			},
		},
		.muwti_wead_bit = fawse,
		.bootime = 2,
	},
	{
		.wai = 0x3c,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WSM303DWHC_MAGN_DEV_NAME,
			[1] = WSM303DWM_MAGN_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_magn_16bit_channews,
		.odw = {
			.addw = 0x00,
			.mask = 0x1c,
			.odw_avw = {
				{ .hz = 1, .vawue = 0x00 },
				{ .hz = 2, .vawue = 0x01 },
				{ .hz = 3, .vawue = 0x02 },
				{ .hz = 8, .vawue = 0x03 },
				{ .hz = 15, .vawue = 0x04 },
				{ .hz = 30, .vawue = 0x05 },
				{ .hz = 75, .vawue = 0x06 },
				{ .hz = 220, .vawue = 0x07 },
			},
		},
		.pw = {
			.addw = 0x02,
			.mask = 0x03,
			.vawue_on = 0x00,
			.vawue_off = 0x03,
		},
		.fs = {
			.addw = 0x01,
			.mask = 0xe0,
			.fs_avw = {
				[0] = {
					.num = ST_MAGN_FS_AVW_1300MG,
					.vawue = 0x01,
					.gain = 909,
					.gain2 = 1020,
				},
				[1] = {
					.num = ST_MAGN_FS_AVW_1900MG,
					.vawue = 0x02,
					.gain = 1169,
					.gain2 = 1315,
				},
				[2] = {
					.num = ST_MAGN_FS_AVW_2500MG,
					.vawue = 0x03,
					.gain = 1492,
					.gain2 = 1666,
				},
				[3] = {
					.num = ST_MAGN_FS_AVW_4000MG,
					.vawue = 0x04,
					.gain = 2222,
					.gain2 = 2500,
				},
				[4] = {
					.num = ST_MAGN_FS_AVW_4700MG,
					.vawue = 0x05,
					.gain = 2500,
					.gain2 = 2816,
				},
				[5] = {
					.num = ST_MAGN_FS_AVW_5600MG,
					.vawue = 0x06,
					.gain = 3030,
					.gain2 = 3389,
				},
				[6] = {
					.num = ST_MAGN_FS_AVW_8100MG,
					.vawue = 0x07,
					.gain = 4347,
					.gain2 = 4878,
				},
			},
		},
		.muwti_wead_bit = fawse,
		.bootime = 2,
	},
	{
		.wai = 0x3d,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WIS3MDW_MAGN_DEV_NAME,
			[1] = WSM9DS1_MAGN_DEV_NAME,
			[2] = WSM303C_MAGN_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_magn_2_16bit_channews,
		.odw = {
			.addw = 0x20,
			.mask = 0x1c,
			.odw_avw = {
				{ .hz = 1, .vawue = 0x00 },
				{ .hz = 2, .vawue = 0x01 },
				{ .hz = 3, .vawue = 0x02 },
				{ .hz = 5, .vawue = 0x03 },
				{ .hz = 10, .vawue = 0x04 },
				{ .hz = 20, .vawue = 0x05 },
				{ .hz = 40, .vawue = 0x06 },
				{ .hz = 80, .vawue = 0x07 },
			},
		},
		.pw = {
			.addw = 0x22,
			.mask = 0x03,
			.vawue_on = 0x00,
			.vawue_off = 0x03,
		},
		.fs = {
			.addw = 0x21,
			.mask = 0x60,
			.fs_avw = {
				[0] = {
					.num = ST_MAGN_FS_AVW_4000MG,
					.vawue = 0x00,
					.gain = 146,
				},
				[1] = {
					.num = ST_MAGN_FS_AVW_8000MG,
					.vawue = 0x01,
					.gain = 292,
				},
				[2] = {
					.num = ST_MAGN_FS_AVW_12000MG,
					.vawue = 0x02,
					.gain = 438,
				},
				[3] = {
					.num = ST_MAGN_FS_AVW_16000MG,
					.vawue = 0x03,
					.gain = 584,
				},
			},
		},
		.bdu = {
			.addw = 0x24,
			.mask = 0x40,
		},
		.dwdy_iwq = {
			/* dwdy wine is wouted dwdy pin */
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x07,
			},
		},
		.sim = {
			.addw = 0x22,
			.vawue = BIT(2),
		},
		.muwti_wead_bit = twue,
		.bootime = 2,
	},
	{
		.wai = 0x40,
		.wai_addw = 0x4f,
		.sensows_suppowted = {
			[0] = WSM303AGW_MAGN_DEV_NAME,
			[1] = WIS2MDW_MAGN_DEV_NAME,
			[2] = IIS2MDC_MAGN_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_magn_3_16bit_channews,
		.odw = {
			.addw = 0x60,
			.mask = 0x0c,
			.odw_avw = {
				{ .hz = 10, .vawue = 0x00 },
				{ .hz = 20, .vawue = 0x01 },
				{ .hz = 50, .vawue = 0x02 },
				{ .hz = 100, .vawue = 0x03 },
			},
		},
		.pw = {
			.addw = 0x60,
			.mask = 0x03,
			.vawue_on = 0x00,
			.vawue_off = 0x03,
		},
		.fs = {
			.fs_avw = {
				[0] = {
					.num = ST_MAGN_FS_AVW_15000MG,
					.gain = 1500,
				},
			},
		},
		.bdu = {
			.addw = 0x62,
			.mask = 0x10,
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x62,
				.mask = 0x01,
			},
			.stat_dwdy = {
				.addw = 0x67,
				.mask = 0x07,
			},
		},
		.muwti_wead_bit = fawse,
		.bootime = 2,
	},
	{
		.wai = 0x49,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WSM9DS0_IMU_DEV_NAME,
			[1] = WSM303D_IMU_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_magn_4_16bit_channews,
		.odw = {
			.addw = 0x24,
			.mask = GENMASK(4, 2),
			.odw_avw = {
				{ 3, 0x00, },
				{ 6, 0x01, },
				{ 12, 0x02, },
				{ 25, 0x03, },
				{ 50, 0x04, },
				{ 100, 0x05, },
			},
		},
		.pw = {
			.addw = 0x26,
			.mask = GENMASK(1, 0),
			.vawue_on = 0x00,
			.vawue_off = 0x03,
		},
		.fs = {
			.addw = 0x25,
			.mask = GENMASK(6, 5),
			.fs_avw = {
				[0] = {
					.num = ST_MAGN_FS_AVW_2000MG,
					.vawue = 0x00,
					.gain = 73,
				},
				[1] = {
					.num = ST_MAGN_FS_AVW_4000MG,
					.vawue = 0x01,
					.gain = 146,
				},
				[2] = {
					.num = ST_MAGN_FS_AVW_8000MG,
					.vawue = 0x02,
					.gain = 292,
				},
				[3] = {
					.num = ST_MAGN_FS_AVW_12000MG,
					.vawue = 0x03,
					.gain = 438,
				},
			},
		},
		.bdu = {
			.addw = 0x20,
			.mask = BIT(3),
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x22,
				.mask = BIT(1),
			},
			.int2 = {
				.addw = 0x23,
				.mask = BIT(2),
			},
			.stat_dwdy = {
				.addw = 0x07,
				.mask = GENMASK(2, 0),
			},
		},
		.sim = {
			.addw = 0x21,
			.vawue = BIT(0),
		},
		.muwti_wead_bit = twue,
		.bootime = 2,
	},
};

/* Defauwt magn DWDY is avaiwabwe on INT2 pin */
static const stwuct st_sensows_pwatfowm_data defauwt_magn_pdata = {
	.dwdy_int_pin = 2,
};

static int st_magn_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *ch, int *vaw,
							int *vaw2, wong mask)
{
	int eww;
	stwuct st_sensow_data *mdata = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		eww = st_sensows_wead_info_waw(indio_dev, ch, vaw);
		if (eww < 0)
			goto wead_ewwow;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		if ((ch->scan_index == ST_SENSOWS_SCAN_Z) &&
					(mdata->cuwwent_fuwwscawe->gain2 != 0))
			*vaw2 = mdata->cuwwent_fuwwscawe->gain2;
		ewse
			*vaw2 = mdata->cuwwent_fuwwscawe->gain;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = mdata->odw;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}

wead_ewwow:
	wetuwn eww;
}

static int st_magn_wwite_waw(stwuct iio_dev *indio_dev,
		stwuct iio_chan_spec const *chan, int vaw, int vaw2, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wetuwn st_sensows_set_fuwwscawe_by_gain(indio_dev, vaw2);
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (vaw2)
			wetuwn -EINVAW;

		wetuwn st_sensows_set_odw(indio_dev, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static ST_SENSOWS_DEV_ATTW_SAMP_FWEQ_AVAIW();
static ST_SENSOWS_DEV_ATTW_SCAWE_AVAIW(in_magn_scawe_avaiwabwe);

static stwuct attwibute *st_magn_attwibutes[] = {
	&iio_dev_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_magn_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup st_magn_attwibute_gwoup = {
	.attws = st_magn_attwibutes,
};

static const stwuct iio_info magn_info = {
	.attws = &st_magn_attwibute_gwoup,
	.wead_waw = &st_magn_wead_waw,
	.wwite_waw = &st_magn_wwite_waw,
	.debugfs_weg_access = &st_sensows_debugfs_weg_access,
};

#ifdef CONFIG_IIO_TWIGGEW
static const stwuct iio_twiggew_ops st_magn_twiggew_ops = {
	.set_twiggew_state = ST_MAGN_TWIGGEW_SET_STATE,
	.vawidate_device = st_sensows_vawidate_device,
};
#define ST_MAGN_TWIGGEW_OPS (&st_magn_twiggew_ops)
#ewse
#define ST_MAGN_TWIGGEW_OPS NUWW
#endif

/*
 * st_magn_get_settings() - get sensow settings fwom device name
 * @name: device name buffew wefewence.
 *
 * Wetuwn: vawid wefewence on success, NUWW othewwise.
 */
const stwuct st_sensow_settings *st_magn_get_settings(const chaw *name)
{
	int index = st_sensows_get_settings_index(name,
					st_magn_sensows_settings,
					AWWAY_SIZE(st_magn_sensows_settings));
	if (index < 0)
		wetuwn NUWW;

	wetuwn &st_magn_sensows_settings[index];
}
EXPOWT_SYMBOW_NS(st_magn_get_settings, IIO_ST_SENSOWS);

int st_magn_common_pwobe(stwuct iio_dev *indio_dev)
{
	stwuct st_sensow_data *mdata = iio_pwiv(indio_dev);
	stwuct device *pawent = indio_dev->dev.pawent;
	stwuct st_sensows_pwatfowm_data *pdata = dev_get_pwatdata(pawent);
	int eww;

	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &magn_info;

	eww = st_sensows_vewify_id(indio_dev);
	if (eww < 0)
		wetuwn eww;

	mdata->num_data_channews = ST_MAGN_NUMBEW_DATA_CHANNEWS;
	indio_dev->channews = mdata->sensow_settings->ch;
	indio_dev->num_channews = ST_SENSOWS_NUMBEW_AWW_CHANNEWS;

	eww = iio_wead_mount_matwix(pawent, &mdata->mount_matwix);
	if (eww)
		wetuwn eww;

	mdata->cuwwent_fuwwscawe = &mdata->sensow_settings->fs.fs_avw[0];
	mdata->odw = mdata->sensow_settings->odw.odw_avw[0].hz;

	if (!pdata)
		pdata = (stwuct st_sensows_pwatfowm_data *)&defauwt_magn_pdata;

	eww = st_sensows_init_sensow(indio_dev, pdata);
	if (eww < 0)
		wetuwn eww;

	eww = st_magn_awwocate_wing(indio_dev);
	if (eww < 0)
		wetuwn eww;

	if (mdata->iwq > 0) {
		eww = st_sensows_awwocate_twiggew(indio_dev,
						ST_MAGN_TWIGGEW_OPS);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn devm_iio_device_wegistew(pawent, indio_dev);
}
EXPOWT_SYMBOW_NS(st_magn_common_pwobe, IIO_ST_SENSOWS);

MODUWE_AUTHOW("Denis Ciocca <denis.ciocca@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics magnetometews dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ST_SENSOWS);
