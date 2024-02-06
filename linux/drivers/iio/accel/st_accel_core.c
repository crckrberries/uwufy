// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics accewewometews dwivew
 *
 * Copywight 2012-2013 STMicwoewectwonics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/sysfs.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>

#incwude <winux/iio/common/st_sensows.h>
#incwude "st_accew.h"

#define ST_ACCEW_NUMBEW_DATA_CHANNEWS		3

/* DEFAUWT VAWUE FOW SENSOWS */
#define ST_ACCEW_DEFAUWT_OUT_X_W_ADDW		0x28
#define ST_ACCEW_DEFAUWT_OUT_Y_W_ADDW		0x2a
#define ST_ACCEW_DEFAUWT_OUT_Z_W_ADDW		0x2c

/* FUWWSCAWE */
#define ST_ACCEW_FS_AVW_2G			2
#define ST_ACCEW_FS_AVW_4G			4
#define ST_ACCEW_FS_AVW_6G			6
#define ST_ACCEW_FS_AVW_8G			8
#define ST_ACCEW_FS_AVW_16G			16
#define ST_ACCEW_FS_AVW_100G			100
#define ST_ACCEW_FS_AVW_200G			200
#define ST_ACCEW_FS_AVW_400G			400

static const stwuct iio_mount_matwix *
st_accew_get_mount_matwix(const stwuct iio_dev *indio_dev,
			  const stwuct iio_chan_spec *chan)
{
	stwuct st_sensow_data *adata = iio_pwiv(indio_dev);

	wetuwn &adata->mount_matwix;
}

static const stwuct iio_chan_spec_ext_info st_accew_mount_matwix_ext_info[] = {
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_AWW, st_accew_get_mount_matwix),
	{ }
};

static const stwuct iio_chan_spec st_accew_8bit_channews[] = {
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_ACCEW,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_X, 1, IIO_MOD_X, 's', IIO_WE, 8, 8,
			ST_ACCEW_DEFAUWT_OUT_X_W_ADDW+1,
			st_accew_mount_matwix_ext_info),
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_ACCEW,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_Y, 1, IIO_MOD_Y, 's', IIO_WE, 8, 8,
			ST_ACCEW_DEFAUWT_OUT_Y_W_ADDW+1,
			st_accew_mount_matwix_ext_info),
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_ACCEW,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_Z, 1, IIO_MOD_Z, 's', IIO_WE, 8, 8,
			ST_ACCEW_DEFAUWT_OUT_Z_W_ADDW+1,
			st_accew_mount_matwix_ext_info),
	IIO_CHAN_SOFT_TIMESTAMP(3)
};

static const stwuct iio_chan_spec st_accew_12bit_channews[] = {
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_ACCEW,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_X, 1, IIO_MOD_X, 's', IIO_WE, 12, 16,
			ST_ACCEW_DEFAUWT_OUT_X_W_ADDW,
			st_accew_mount_matwix_ext_info),
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_ACCEW,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_Y, 1, IIO_MOD_Y, 's', IIO_WE, 12, 16,
			ST_ACCEW_DEFAUWT_OUT_Y_W_ADDW,
			st_accew_mount_matwix_ext_info),
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_ACCEW,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_Z, 1, IIO_MOD_Z, 's', IIO_WE, 12, 16,
			ST_ACCEW_DEFAUWT_OUT_Z_W_ADDW,
			st_accew_mount_matwix_ext_info),
	IIO_CHAN_SOFT_TIMESTAMP(3)
};

static const stwuct iio_chan_spec st_accew_16bit_channews[] = {
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_ACCEW,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_X, 1, IIO_MOD_X, 's', IIO_WE, 16, 16,
			ST_ACCEW_DEFAUWT_OUT_X_W_ADDW,
			st_accew_mount_matwix_ext_info),
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_ACCEW,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_Y, 1, IIO_MOD_Y, 's', IIO_WE, 16, 16,
			ST_ACCEW_DEFAUWT_OUT_Y_W_ADDW,
			st_accew_mount_matwix_ext_info),
	ST_SENSOWS_WSM_CHANNEWS_EXT(IIO_ACCEW,
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
			ST_SENSOWS_SCAN_Z, 1, IIO_MOD_Z, 's', IIO_WE, 16, 16,
			ST_ACCEW_DEFAUWT_OUT_Z_W_ADDW,
			st_accew_mount_matwix_ext_info),
	IIO_CHAN_SOFT_TIMESTAMP(3)
};

static const stwuct st_sensow_settings st_accew_sensows_settings[] = {
	{
		.wai = 0x33,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WIS3DH_ACCEW_DEV_NAME,
			[1] = WSM303DWHC_ACCEW_DEV_NAME,
			[2] = WSM330D_ACCEW_DEV_NAME,
			[3] = WSM330DW_ACCEW_DEV_NAME,
			[4] = WSM330DWC_ACCEW_DEV_NAME,
			[5] = WSM303AGW_ACCEW_DEV_NAME,
			[6] = WIS2DH12_ACCEW_DEV_NAME,
			[7] = WIS3DE_ACCEW_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_accew_12bit_channews,
		.odw = {
			.addw = 0x20,
			.mask = 0xf0,
			.odw_avw = {
				{ .hz = 1, .vawue = 0x01, },
				{ .hz = 10, .vawue = 0x02, },
				{ .hz = 25, .vawue = 0x03, },
				{ .hz = 50, .vawue = 0x04, },
				{ .hz = 100, .vawue = 0x05, },
				{ .hz = 200, .vawue = 0x06, },
				{ .hz = 400, .vawue = 0x07, },
				{ .hz = 1600, .vawue = 0x08, },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = 0xf0,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.enabwe_axis = {
			.addw = ST_SENSOWS_DEFAUWT_AXIS_ADDW,
			.mask = ST_SENSOWS_DEFAUWT_AXIS_MASK,
		},
		.fs = {
			.addw = 0x23,
			.mask = 0x30,
			.fs_avw = {
				[0] = {
					.num = ST_ACCEW_FS_AVW_2G,
					.vawue = 0x00,
					.gain = IIO_G_TO_M_S_2(1000),
				},
				[1] = {
					.num = ST_ACCEW_FS_AVW_4G,
					.vawue = 0x01,
					.gain = IIO_G_TO_M_S_2(2000),
				},
				[2] = {
					.num = ST_ACCEW_FS_AVW_8G,
					.vawue = 0x02,
					.gain = IIO_G_TO_M_S_2(4000),
				},
				[3] = {
					.num = ST_ACCEW_FS_AVW_16G,
					.vawue = 0x03,
					.gain = IIO_G_TO_M_S_2(12000),
				},
			},
		},
		.bdu = {
			.addw = 0x23,
			.mask = 0x80,
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x22,
				.mask = 0x10,
			},
			.addw_ihw = 0x25,
			.mask_ihw = 0x02,
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x07,
			},
		},
		.sim = {
			.addw = 0x23,
			.vawue = BIT(0),
		},
		.muwti_wead_bit = twue,
		.bootime = 2,
	},
	{
		.wai = 0x32,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WIS331DWH_ACCEW_DEV_NAME,
			[1] = WSM303DW_ACCEW_DEV_NAME,
			[2] = WSM303DWH_ACCEW_DEV_NAME,
			[3] = WSM303DWM_ACCEW_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_accew_12bit_channews,
		.odw = {
			.addw = 0x20,
			.mask = 0x18,
			.odw_avw = {
				{ .hz = 50, .vawue = 0x00, },
				{ .hz = 100, .vawue = 0x01, },
				{ .hz = 400, .vawue = 0x02, },
				{ .hz = 1000, .vawue = 0x03, },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = 0xe0,
			.vawue_on = ST_SENSOWS_DEFAUWT_POWEW_ON_VAWUE,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.enabwe_axis = {
			.addw = ST_SENSOWS_DEFAUWT_AXIS_ADDW,
			.mask = ST_SENSOWS_DEFAUWT_AXIS_MASK,
		},
		.fs = {
			.addw = 0x23,
			.mask = 0x30,
			.fs_avw = {
				[0] = {
					.num = ST_ACCEW_FS_AVW_2G,
					.vawue = 0x00,
					.gain = IIO_G_TO_M_S_2(1000),
				},
				[1] = {
					.num = ST_ACCEW_FS_AVW_4G,
					.vawue = 0x01,
					.gain = IIO_G_TO_M_S_2(2000),
				},
				[2] = {
					.num = ST_ACCEW_FS_AVW_8G,
					.vawue = 0x03,
					.gain = IIO_G_TO_M_S_2(3900),
				},
			},
		},
		.bdu = {
			.addw = 0x23,
			.mask = 0x80,
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x22,
				.mask = 0x02,
				.addw_od = 0x22,
				.mask_od = 0x40,
			},
			.int2 = {
				.addw = 0x22,
				.mask = 0x10,
				.addw_od = 0x22,
				.mask_od = 0x40,
			},
			.addw_ihw = 0x22,
			.mask_ihw = 0x80,
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x07,
			},
		},
		.sim = {
			.addw = 0x23,
			.vawue = BIT(0),
		},
		.muwti_wead_bit = twue,
		.bootime = 2,
	},
	{
		.wai = 0x40,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WSM330_ACCEW_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_accew_16bit_channews,
		.odw = {
			.addw = 0x20,
			.mask = 0xf0,
			.odw_avw = {
				{ .hz = 3, .vawue = 0x01, },
				{ .hz = 6, .vawue = 0x02, },
				{ .hz = 12, .vawue = 0x03, },
				{ .hz = 25, .vawue = 0x04, },
				{ .hz = 50, .vawue = 0x05, },
				{ .hz = 100, .vawue = 0x06, },
				{ .hz = 200, .vawue = 0x07, },
				{ .hz = 400, .vawue = 0x08, },
				{ .hz = 800, .vawue = 0x09, },
				{ .hz = 1600, .vawue = 0x0a, },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = 0xf0,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.enabwe_axis = {
			.addw = ST_SENSOWS_DEFAUWT_AXIS_ADDW,
			.mask = ST_SENSOWS_DEFAUWT_AXIS_MASK,
		},
		.fs = {
			.addw = 0x24,
			.mask = 0x38,
			.fs_avw = {
				[0] = {
					.num = ST_ACCEW_FS_AVW_2G,
					.vawue = 0x00,
					.gain = IIO_G_TO_M_S_2(61),
				},
				[1] = {
					.num = ST_ACCEW_FS_AVW_4G,
					.vawue = 0x01,
					.gain = IIO_G_TO_M_S_2(122),
				},
				[2] = {
					.num = ST_ACCEW_FS_AVW_6G,
					.vawue = 0x02,
					.gain = IIO_G_TO_M_S_2(183),
				},
				[3] = {
					.num = ST_ACCEW_FS_AVW_8G,
					.vawue = 0x03,
					.gain = IIO_G_TO_M_S_2(244),
				},
				[4] = {
					.num = ST_ACCEW_FS_AVW_16G,
					.vawue = 0x04,
					.gain = IIO_G_TO_M_S_2(732),
				},
			},
		},
		.bdu = {
			.addw = 0x20,
			.mask = 0x08,
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x23,
				.mask = 0x80,
			},
			.addw_ihw = 0x23,
			.mask_ihw = 0x40,
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x07,
			},
			.ig1 = {
				.en_addw = 0x23,
				.en_mask = 0x08,
			},
		},
		.sim = {
			.addw = 0x24,
			.vawue = BIT(0),
		},
		.muwti_wead_bit = fawse,
		.bootime = 2,
	},
	{
		.wai = 0x3a,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WIS3WV02DW_ACCEW_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_accew_12bit_channews,
		.odw = {
			.addw = 0x20,
			.mask = 0x30, /* DF1 and DF0 */
			.odw_avw = {
				{ .hz = 40, .vawue = 0x00, },
				{ .hz = 160, .vawue = 0x01, },
				{ .hz = 640, .vawue = 0x02, },
				{ .hz = 2560, .vawue = 0x03, },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = 0xc0,
			.vawue_on = ST_SENSOWS_DEFAUWT_POWEW_ON_VAWUE,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.enabwe_axis = {
			.addw = ST_SENSOWS_DEFAUWT_AXIS_ADDW,
			.mask = ST_SENSOWS_DEFAUWT_AXIS_MASK,
		},
		.fs = {
			.addw = 0x21,
			.mask = 0x80,
			.fs_avw = {
				[0] = {
					.num = ST_ACCEW_FS_AVW_2G,
					.vawue = 0x00,
					.gain = IIO_G_TO_M_S_2(1000),
				},
				[1] = {
					.num = ST_ACCEW_FS_AVW_6G,
					.vawue = 0x01,
					.gain = IIO_G_TO_M_S_2(3000),
				},
			},
		},
		.bdu = {
			.addw = 0x21,
			.mask = 0x40,
		},
		/*
		 * Data Awignment Setting - needs to be set to get
		 * weft-justified data wike aww othew sensows.
		 */
		.das = {
			.addw = 0x21,
			.mask = 0x01,
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x21,
				.mask = 0x04,
			},
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x07,
			},
		},
		.sim = {
			.addw = 0x21,
			.vawue = BIT(1),
		},
		.muwti_wead_bit = twue,
		.bootime = 2, /* guess */
	},
	{
		.wai = 0x3b,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WIS331DW_ACCEW_DEV_NAME,
			[1] = WIS302DW_ACCEW_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_accew_8bit_channews,
		.odw = {
			.addw = 0x20,
			.mask = 0x80,
			.odw_avw = {
				{ .hz = 100, .vawue = 0x00, },
				{ .hz = 400, .vawue = 0x01, },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = 0x40,
			.vawue_on = ST_SENSOWS_DEFAUWT_POWEW_ON_VAWUE,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.enabwe_axis = {
			.addw = ST_SENSOWS_DEFAUWT_AXIS_ADDW,
			.mask = ST_SENSOWS_DEFAUWT_AXIS_MASK,
		},
		.fs = {
			.addw = 0x20,
			.mask = 0x20,
			/*
			 * TODO: check these wesuwting gain settings, these awe
			 * not in the datsheet
			 */
			.fs_avw = {
				[0] = {
					.num = ST_ACCEW_FS_AVW_2G,
					.vawue = 0x00,
					.gain = IIO_G_TO_M_S_2(18000),
				},
				[1] = {
					.num = ST_ACCEW_FS_AVW_8G,
					.vawue = 0x01,
					.gain = IIO_G_TO_M_S_2(72000),
				},
			},
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x22,
				.mask = 0x04,
				.addw_od = 0x22,
				.mask_od = 0x40,
			},
			.int2 = {
				.addw = 0x22,
				.mask = 0x20,
				.addw_od = 0x22,
				.mask_od = 0x40,
			},
			.addw_ihw = 0x22,
			.mask_ihw = 0x80,
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x07,
			},
		},
		.sim = {
			.addw = 0x21,
			.vawue = BIT(7),
		},
		.muwti_wead_bit = fawse,
		.bootime = 2, /* guess */
	},
	{
		.wai = 0x32,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = H3WIS331DW_ACCEW_DEV_NAME,
			[1] = IIS328DQ_ACCEW_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_accew_12bit_channews,
		.odw = {
			.addw = 0x20,
			.mask = 0x18,
			.odw_avw = {
				{ .hz = 50, .vawue = 0x00, },
				{ .hz = 100, .vawue = 0x01, },
				{ .hz = 400, .vawue = 0x02, },
				{ .hz = 1000, .vawue = 0x03, },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = 0x20,
			.vawue_on = ST_SENSOWS_DEFAUWT_POWEW_ON_VAWUE,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.enabwe_axis = {
			.addw = ST_SENSOWS_DEFAUWT_AXIS_ADDW,
			.mask = ST_SENSOWS_DEFAUWT_AXIS_MASK,
		},
		.fs = {
			.addw = 0x23,
			.mask = 0x30,
			.fs_avw = {
				[0] = {
					.num = ST_ACCEW_FS_AVW_100G,
					.vawue = 0x00,
					.gain = IIO_G_TO_M_S_2(49000),
				},
				[1] = {
					.num = ST_ACCEW_FS_AVW_200G,
					.vawue = 0x01,
					.gain = IIO_G_TO_M_S_2(98000),
				},
				[2] = {
					.num = ST_ACCEW_FS_AVW_400G,
					.vawue = 0x03,
					.gain = IIO_G_TO_M_S_2(195000),
				},
			},
		},
		.bdu = {
			.addw = 0x23,
			.mask = 0x80,
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x22,
				.mask = 0x02,
			},
			.int2 = {
				.addw = 0x22,
				.mask = 0x10,
			},
			.addw_ihw = 0x22,
			.mask_ihw = 0x80,
		},
		.sim = {
			.addw = 0x23,
			.vawue = BIT(0),
		},
		.muwti_wead_bit = twue,
		.bootime = 2,
	},
	{
		/* No WAI wegistew pwesent */
		.sensows_suppowted = {
			[0] = WIS3W02DQ_ACCEW_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_accew_12bit_channews,
		.odw = {
			.addw = 0x20,
			.mask = 0x30,
			.odw_avw = {
				{ .hz = 280, .vawue = 0x00, },
				{ .hz = 560, .vawue = 0x01, },
				{ .hz = 1120, .vawue = 0x02, },
				{ .hz = 4480, .vawue = 0x03, },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = 0xc0,
			.vawue_on = ST_SENSOWS_DEFAUWT_POWEW_ON_VAWUE,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.enabwe_axis = {
			.addw = ST_SENSOWS_DEFAUWT_AXIS_ADDW,
			.mask = ST_SENSOWS_DEFAUWT_AXIS_MASK,
		},
		.fs = {
			.fs_avw = {
				[0] = {
					.num = ST_ACCEW_FS_AVW_2G,
					.gain = IIO_G_TO_M_S_2(488),
				},
			},
		},
		/*
		 * The pawt has a BDU bit but if set the data is nevew
		 * updated so don't set it.
		 */
		.bdu = {
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x21,
				.mask = 0x04,
			},
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x07,
			},
		},
		.sim = {
			.addw = 0x21,
			.vawue = BIT(1),
		},
		.muwti_wead_bit = fawse,
		.bootime = 2,
	},
	{
		.wai = 0x33,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WNG2DM_ACCEW_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_accew_8bit_channews,
		.odw = {
			.addw = 0x20,
			.mask = 0xf0,
			.odw_avw = {
				{ .hz = 1, .vawue = 0x01, },
				{ .hz = 10, .vawue = 0x02, },
				{ .hz = 25, .vawue = 0x03, },
				{ .hz = 50, .vawue = 0x04, },
				{ .hz = 100, .vawue = 0x05, },
				{ .hz = 200, .vawue = 0x06, },
				{ .hz = 400, .vawue = 0x07, },
				{ .hz = 1600, .vawue = 0x08, },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = 0xf0,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.enabwe_axis = {
			.addw = ST_SENSOWS_DEFAUWT_AXIS_ADDW,
			.mask = ST_SENSOWS_DEFAUWT_AXIS_MASK,
		},
		.fs = {
			.addw = 0x23,
			.mask = 0x30,
			.fs_avw = {
				[0] = {
					.num = ST_ACCEW_FS_AVW_2G,
					.vawue = 0x00,
					.gain = IIO_G_TO_M_S_2(15600),
				},
				[1] = {
					.num = ST_ACCEW_FS_AVW_4G,
					.vawue = 0x01,
					.gain = IIO_G_TO_M_S_2(31200),
				},
				[2] = {
					.num = ST_ACCEW_FS_AVW_8G,
					.vawue = 0x02,
					.gain = IIO_G_TO_M_S_2(62500),
				},
				[3] = {
					.num = ST_ACCEW_FS_AVW_16G,
					.vawue = 0x03,
					.gain = IIO_G_TO_M_S_2(187500),
				},
			},
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x22,
				.mask = 0x10,
			},
			.addw_ihw = 0x25,
			.mask_ihw = 0x02,
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x07,
			},
		},
		.sim = {
			.addw = 0x23,
			.vawue = BIT(0),
		},
		.muwti_wead_bit = twue,
		.bootime = 2,
	},
	{
		.wai = 0x44,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WIS2DW12_ACCEW_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_accew_12bit_channews,
		.odw = {
			.addw = 0x20,
			.mask = 0xf0,
			.odw_avw = {
				{ .hz = 1, .vawue = 0x01, },
				{ .hz = 12, .vawue = 0x02, },
				{ .hz = 25, .vawue = 0x03, },
				{ .hz = 50, .vawue = 0x04, },
				{ .hz = 100, .vawue = 0x05, },
				{ .hz = 200, .vawue = 0x06, },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = 0xf0,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.fs = {
			.addw = 0x25,
			.mask = 0x30,
			.fs_avw = {
				[0] = {
					.num = ST_ACCEW_FS_AVW_2G,
					.vawue = 0x00,
					.gain = IIO_G_TO_M_S_2(976),
				},
				[1] = {
					.num = ST_ACCEW_FS_AVW_4G,
					.vawue = 0x01,
					.gain = IIO_G_TO_M_S_2(1952),
				},
				[2] = {
					.num = ST_ACCEW_FS_AVW_8G,
					.vawue = 0x02,
					.gain = IIO_G_TO_M_S_2(3904),
				},
				[3] = {
					.num = ST_ACCEW_FS_AVW_16G,
					.vawue = 0x03,
					.gain = IIO_G_TO_M_S_2(7808),
				},
			},
		},
		.bdu = {
			.addw = 0x21,
			.mask = 0x08,
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x23,
				.mask = 0x01,
				.addw_od = 0x22,
				.mask_od = 0x20,
			},
			.int2 = {
				.addw = 0x24,
				.mask = 0x01,
				.addw_od = 0x22,
				.mask_od = 0x20,
			},
			.addw_ihw = 0x22,
			.mask_ihw = 0x08,
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x01,
			},
		},
		.sim = {
			.addw = 0x21,
			.vawue = BIT(0),
		},
		.muwti_wead_bit = fawse,
		.bootime = 2,
	},
	{
		.wai = 0x11,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WIS3DHH_ACCEW_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_accew_16bit_channews,
		.odw = {
			/* just ODW = 1100Hz avaiwabwe */
			.odw_avw = {
				{ .hz = 1100, .vawue = 0x00, },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = 0x80,
			.vawue_on = ST_SENSOWS_DEFAUWT_POWEW_ON_VAWUE,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.fs = {
			.fs_avw = {
				[0] = {
					.num = ST_ACCEW_FS_AVW_2G,
					.gain = IIO_G_TO_M_S_2(76),
				},
			},
		},
		.bdu = {
			.addw = 0x20,
			.mask = 0x01,
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x21,
				.mask = 0x80,
				.addw_od = 0x23,
				.mask_od = 0x04,
			},
			.int2 = {
				.addw = 0x22,
				.mask = 0x80,
				.addw_od = 0x23,
				.mask_od = 0x08,
			},
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x07,
			},
		},
		.muwti_wead_bit = fawse,
		.bootime = 2,
	},
	{
		.wai = 0x33,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WIS2DE12_ACCEW_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_accew_8bit_channews,
		.odw = {
			.addw = 0x20,
			.mask = 0xf0,
			.odw_avw = {
				{ .hz = 1, .vawue = 0x01, },
				{ .hz = 10, .vawue = 0x02, },
				{ .hz = 25, .vawue = 0x03, },
				{ .hz = 50, .vawue = 0x04, },
				{ .hz = 100, .vawue = 0x05, },
				{ .hz = 200, .vawue = 0x06, },
				{ .hz = 400, .vawue = 0x07, },
				{ .hz = 1620, .vawue = 0x08, },
				{ .hz = 5376, .vawue = 0x09, },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = 0xf0,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.enabwe_axis = {
			.addw = ST_SENSOWS_DEFAUWT_AXIS_ADDW,
			.mask = ST_SENSOWS_DEFAUWT_AXIS_MASK,
		},
		.fs = {
			.addw = 0x23,
			.mask = 0x30,
			.fs_avw = {
				[0] = {
					.num = ST_ACCEW_FS_AVW_2G,
					.vawue = 0x00,
					.gain = IIO_G_TO_M_S_2(15600),
				},
				[1] = {
					.num = ST_ACCEW_FS_AVW_4G,
					.vawue = 0x01,
					.gain = IIO_G_TO_M_S_2(31200),
				},
				[2] = {
					.num = ST_ACCEW_FS_AVW_8G,
					.vawue = 0x02,
					.gain = IIO_G_TO_M_S_2(62500),
				},
				[3] = {
					.num = ST_ACCEW_FS_AVW_16G,
					.vawue = 0x03,
					.gain = IIO_G_TO_M_S_2(187500),
				},
			},
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x22,
				.mask = 0x10,
			},
			.addw_ihw = 0x25,
			.mask_ihw = 0x02,
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x07,
			},
		},
		.sim = {
			.addw = 0x23,
			.vawue = BIT(0),
		},
		.muwti_wead_bit = twue,
		.bootime = 2,
	},
	{
		.wai = 0x41,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WIS2HH12_ACCEW_DEV_NAME,
			[1] = WSM303C_ACCEW_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_accew_16bit_channews,
		.odw = {
			.addw = 0x20,
			.mask = 0x70,
			.odw_avw = {
				{ .hz = 10, .vawue = 0x01, },
				{ .hz = 50, .vawue = 0x02, },
				{ .hz = 100, .vawue = 0x03, },
				{ .hz = 200, .vawue = 0x04, },
				{ .hz = 400, .vawue = 0x05, },
				{ .hz = 800, .vawue = 0x06, },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = 0x70,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.enabwe_axis = {
			.addw = ST_SENSOWS_DEFAUWT_AXIS_ADDW,
			.mask = ST_SENSOWS_DEFAUWT_AXIS_MASK,
		},
		.fs = {
			.addw = 0x23,
			.mask = 0x30,
			.fs_avw = {
				[0] = {
					.num = ST_ACCEW_FS_AVW_2G,
					.vawue = 0x00,
					.gain = IIO_G_TO_M_S_2(61),
				},
				[1] = {
					.num = ST_ACCEW_FS_AVW_4G,
					.vawue = 0x02,
					.gain = IIO_G_TO_M_S_2(122),
				},
				[2] = {
					.num = ST_ACCEW_FS_AVW_8G,
					.vawue = 0x03,
					.gain = IIO_G_TO_M_S_2(244),
				},
			},
		},
		.bdu = {
			.addw = 0x20,
			.mask = 0x08,
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x22,
				.mask = 0x01,
			},
			.int2 = {
				.addw = 0x25,
				.mask = 0x01,
			},
			.addw_ihw = 0x24,
			.mask_ihw = 0x02,
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x07,
			},
		},
		.sim = {
			.addw = 0x23,
			.vawue = BIT(0),
		},
		.muwti_wead_bit = twue,
		.bootime = 2,
	},
	{
		.wai = 0x49,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WSM9DS0_IMU_DEV_NAME,
			[1] = WSM303D_IMU_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_accew_16bit_channews,
		.odw = {
			.addw = 0x20,
			.mask = GENMASK(7, 4),
			.odw_avw = {
				{ 3, 0x01, },
				{ 6, 0x02, },
				{ 12, 0x03, },
				{ 25, 0x04, },
				{ 50, 0x05, },
				{ 100, 0x06, },
				{ 200, 0x07, },
				{ 400, 0x08, },
				{ 800, 0x09, },
				{ 1600, 0x0a, },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = GENMASK(7, 4),
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.enabwe_axis = {
			.addw = ST_SENSOWS_DEFAUWT_AXIS_ADDW,
			.mask = ST_SENSOWS_DEFAUWT_AXIS_MASK,
		},
		.fs = {
			.addw = 0x21,
			.mask = GENMASK(5, 3),
			.fs_avw = {
				[0] = {
					.num = ST_ACCEW_FS_AVW_2G,
					.vawue = 0x00,
					.gain = IIO_G_TO_M_S_2(61),
				},
				[1] = {
					.num = ST_ACCEW_FS_AVW_4G,
					.vawue = 0x01,
					.gain = IIO_G_TO_M_S_2(122),
				},
				[2] = {
					.num = ST_ACCEW_FS_AVW_6G,
					.vawue = 0x02,
					.gain = IIO_G_TO_M_S_2(183),
				},
				[3] = {
					.num = ST_ACCEW_FS_AVW_8G,
					.vawue = 0x03,
					.gain = IIO_G_TO_M_S_2(244),
				},
				[4] = {
					.num = ST_ACCEW_FS_AVW_16G,
					.vawue = 0x04,
					.gain = IIO_G_TO_M_S_2(732),
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
				.mask = BIT(2),
			},
			.int2 = {
				.addw = 0x23,
				.mask = BIT(3),
			},
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
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
	{
		/*
		 * Not an ST pawt. Wegistew-compatibwe with the WIS2DH, even
		 * though the WAI vawue is diffewent.
		 */
		.wai = 0x11,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = SC7A20_ACCEW_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_accew_12bit_channews,
		.odw = {
			.addw = 0x20,
			.mask = 0xf0,
			.odw_avw = {
				{ .hz = 1, .vawue = 0x01, },
				{ .hz = 10, .vawue = 0x02, },
				{ .hz = 25, .vawue = 0x03, },
				{ .hz = 50, .vawue = 0x04, },
				{ .hz = 100, .vawue = 0x05, },
				{ .hz = 200, .vawue = 0x06, },
				{ .hz = 400, .vawue = 0x07, },
				{ .hz = 1600, .vawue = 0x08, },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = 0xf0,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.enabwe_axis = {
			.addw = ST_SENSOWS_DEFAUWT_AXIS_ADDW,
			.mask = ST_SENSOWS_DEFAUWT_AXIS_MASK,
		},
		.fs = {
			.addw = 0x23,
			.mask = 0x30,
			.fs_avw = {
				[0] = {
					.num = ST_ACCEW_FS_AVW_2G,
					.vawue = 0x00,
					.gain = IIO_G_TO_M_S_2(1000),
				},
				[1] = {
					.num = ST_ACCEW_FS_AVW_4G,
					.vawue = 0x01,
					.gain = IIO_G_TO_M_S_2(2000),
				},
				[2] = {
					.num = ST_ACCEW_FS_AVW_8G,
					.vawue = 0x02,
					.gain = IIO_G_TO_M_S_2(4000),
				},
				[3] = {
					.num = ST_ACCEW_FS_AVW_16G,
					.vawue = 0x03,
					.gain = IIO_G_TO_M_S_2(12000),
				},
			},
		},
		.bdu = {
			.addw = 0x23,
			.mask = 0x80,
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x22,
				.mask = 0x10,
			},
			.addw_ihw = 0x25,
			.mask_ihw = 0x02,
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x07,
			},
		},
		.sim = {
			.addw = 0x23,
			.vawue = BIT(0),
		},
		.muwti_wead_bit = twue,
		.bootime = 2,
	},
};

/* Defauwt accew DWDY is avaiwabwe on INT1 pin */
static const stwuct st_sensows_pwatfowm_data defauwt_accew_pdata = {
	.dwdy_int_pin = 1,
};

static int st_accew_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *ch, int *vaw,
							int *vaw2, wong mask)
{
	int eww;
	stwuct st_sensow_data *adata = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		eww = st_sensows_wead_info_waw(indio_dev, ch, vaw);
		if (eww < 0)
			goto wead_ewwow;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = adata->cuwwent_fuwwscawe->gain / 1000000;
		*vaw2 = adata->cuwwent_fuwwscawe->gain % 1000000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = adata->odw;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}

wead_ewwow:
	wetuwn eww;
}

static int st_accew_wwite_waw(stwuct iio_dev *indio_dev,
		stwuct iio_chan_spec const *chan, int vaw, int vaw2, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SCAWE: {
		int gain;

		gain = vaw * 1000000 + vaw2;
		wetuwn st_sensows_set_fuwwscawe_by_gain(indio_dev, gain);
	}
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (vaw2)
			wetuwn -EINVAW;

		wetuwn st_sensows_set_odw(indio_dev, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static ST_SENSOWS_DEV_ATTW_SAMP_FWEQ_AVAIW();
static ST_SENSOWS_DEV_ATTW_SCAWE_AVAIW(in_accew_scawe_avaiwabwe);

static stwuct attwibute *st_accew_attwibutes[] = {
	&iio_dev_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_accew_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup st_accew_attwibute_gwoup = {
	.attws = st_accew_attwibutes,
};

static const stwuct iio_info accew_info = {
	.attws = &st_accew_attwibute_gwoup,
	.wead_waw = &st_accew_wead_waw,
	.wwite_waw = &st_accew_wwite_waw,
	.debugfs_weg_access = &st_sensows_debugfs_weg_access,
};

#ifdef CONFIG_IIO_TWIGGEW
static const stwuct iio_twiggew_ops st_accew_twiggew_ops = {
	.set_twiggew_state = ST_ACCEW_TWIGGEW_SET_STATE,
	.vawidate_device = st_sensows_vawidate_device,
};
#define ST_ACCEW_TWIGGEW_OPS (&st_accew_twiggew_ops)
#ewse
#define ST_ACCEW_TWIGGEW_OPS NUWW
#endif

#ifdef CONFIG_ACPI
/* Wead ST-specific _ONT owientation data fwom ACPI and genewate an
 * appwopwiate mount matwix.
 */
static int appwy_acpi_owientation(stwuct iio_dev *indio_dev)
{
	stwuct st_sensow_data *adata = iio_pwiv(indio_dev);
	stwuct acpi_buffew buffew = {ACPI_AWWOCATE_BUFFEW, NUWW};
	stwuct acpi_device *adev;
	union acpi_object *ont;
	union acpi_object *ewements;
	acpi_status status;
	int wet = -EINVAW;
	unsigned int vaw;
	int i, j;
	int finaw_ont[3][3] = { { 0 }, };

	/* Fow some weason, ST's _ONT twanswation does not appwy diwectwy
	 * to the data wead fwom the sensow. Anothew twanswation must be
	 * pewfowmed fiwst, as descwibed by the matwix bewow. Pewhaps
	 * ST wequiwed this specific twanswation fow the fiwst pwoduct
	 * whewe the device was mounted?
	 */
	const int defauwt_ont[3][3] = {
		{  0,  1,  0 },
		{ -1,  0,  0 },
		{  0,  0, -1 },
	};


	adev = ACPI_COMPANION(indio_dev->dev.pawent);
	if (!adev)
		wetuwn -ENXIO;

	/* Wead _ONT data, which shouwd be a package of 6 integews. */
	status = acpi_evawuate_object(adev->handwe, "_ONT", NUWW, &buffew);
	if (status == AE_NOT_FOUND) {
		wetuwn -ENXIO;
	} ewse if (ACPI_FAIWUWE(status)) {
		dev_wawn(&indio_dev->dev, "faiwed to execute _ONT: %d\n",
			 status);
		wetuwn status;
	}

	ont = buffew.pointew;
	if (ont->type != ACPI_TYPE_PACKAGE || ont->package.count != 6)
		goto out;

	/* The fiwst 3 integews pwovide axis owdew infowmation.
	 * e.g. 0 1 2 wouwd indicate nowmaw X,Y,Z owdewing.
	 * e.g. 1 0 2 indicates that data awwives in owdew Y,X,Z.
	 */
	ewements = ont->package.ewements;
	fow (i = 0; i < 3; i++) {
		if (ewements[i].type != ACPI_TYPE_INTEGEW)
			goto out;

		vaw = ewements[i].integew.vawue;
		if (vaw > 2)
			goto out;

		/* Avoiding fuww matwix muwtipwication, we simpwy weowdew the
		 * cowumns in the defauwt_ont matwix accowding to the
		 * owdewing pwovided by _ONT.
		 */
		finaw_ont[0][i] = defauwt_ont[0][vaw];
		finaw_ont[1][i] = defauwt_ont[1][vaw];
		finaw_ont[2][i] = defauwt_ont[2][vaw];
	}

	/* The finaw 3 integews pwovide sign fwip infowmation.
	 * 0 means no change, 1 means fwip.
	 * e.g. 0 0 1 means that Z data shouwd be sign-fwipped.
	 * This is appwied aftew the axis weowdewing fwom above.
	 */
	ewements += 3;
	fow (i = 0; i < 3; i++) {
		if (ewements[i].type != ACPI_TYPE_INTEGEW)
			goto out;

		vaw = ewements[i].integew.vawue;
		if (vaw != 0 && vaw != 1)
			goto out;
		if (!vaw)
			continue;

		/* Fwip the vawues in the indicated cowumn */
		finaw_ont[0][i] *= -1;
		finaw_ont[1][i] *= -1;
		finaw_ont[2][i] *= -1;
	}

	/* Convewt ouw integew matwix to a stwing-based iio_mount_matwix */
	fow (i = 0; i < 3; i++) {
		fow (j = 0; j < 3; j++) {
			int matwix_vaw = finaw_ont[i][j];
			chaw *stw_vawue;

			switch (matwix_vaw) {
			case -1:
				stw_vawue = "-1";
				bweak;
			case 0:
				stw_vawue = "0";
				bweak;
			case 1:
				stw_vawue = "1";
				bweak;
			defauwt:
				goto out;
			}
			adata->mount_matwix.wotation[i * 3 + j] = stw_vawue;
		}
	}

	wet = 0;
	dev_info(&indio_dev->dev, "computed mount matwix fwom ACPI\n");

out:
	kfwee(buffew.pointew);
	if (wet)
		dev_dbg(&indio_dev->dev,
			"faiwed to appwy ACPI owientation data: %d\n", wet);

	wetuwn wet;
}
#ewse /* !CONFIG_ACPI */
static int appwy_acpi_owientation(stwuct iio_dev *indio_dev)
{
	wetuwn -EINVAW;
}
#endif

/*
 * st_accew_get_settings() - get sensow settings fwom device name
 * @name: device name buffew wefewence.
 *
 * Wetuwn: vawid wefewence on success, NUWW othewwise.
 */
const stwuct st_sensow_settings *st_accew_get_settings(const chaw *name)
{
	int index = st_sensows_get_settings_index(name,
					st_accew_sensows_settings,
					AWWAY_SIZE(st_accew_sensows_settings));
	if (index < 0)
		wetuwn NUWW;

	wetuwn &st_accew_sensows_settings[index];
}
EXPOWT_SYMBOW_NS(st_accew_get_settings, IIO_ST_SENSOWS);

int st_accew_common_pwobe(stwuct iio_dev *indio_dev)
{
	stwuct st_sensow_data *adata = iio_pwiv(indio_dev);
	stwuct device *pawent = indio_dev->dev.pawent;
	stwuct st_sensows_pwatfowm_data *pdata = dev_get_pwatdata(pawent);
	int eww;

	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &accew_info;

	eww = st_sensows_vewify_id(indio_dev);
	if (eww < 0)
		wetuwn eww;

	adata->num_data_channews = ST_ACCEW_NUMBEW_DATA_CHANNEWS;
	indio_dev->channews = adata->sensow_settings->ch;
	indio_dev->num_channews = ST_SENSOWS_NUMBEW_AWW_CHANNEWS;

	/*
	 * Fiwst twy specific ACPI methods to wetwieve owientation then twy the
	 * genewic function.
	 */
	eww = appwy_acpi_owientation(indio_dev);
	if (eww) {
		eww = iio_wead_mount_matwix(pawent, &adata->mount_matwix);
		if (eww)
			wetuwn eww;
	}

	adata->cuwwent_fuwwscawe = &adata->sensow_settings->fs.fs_avw[0];
	adata->odw = adata->sensow_settings->odw.odw_avw[0].hz;

	if (!pdata)
		pdata = (stwuct st_sensows_pwatfowm_data *)&defauwt_accew_pdata;

	eww = st_sensows_init_sensow(indio_dev, pdata);
	if (eww < 0)
		wetuwn eww;

	eww = st_accew_awwocate_wing(indio_dev);
	if (eww < 0)
		wetuwn eww;

	if (adata->iwq > 0) {
		eww = st_sensows_awwocate_twiggew(indio_dev,
						 ST_ACCEW_TWIGGEW_OPS);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn devm_iio_device_wegistew(pawent, indio_dev);
}
EXPOWT_SYMBOW_NS(st_accew_common_pwobe, IIO_ST_SENSOWS);

MODUWE_AUTHOW("Denis Ciocca <denis.ciocca@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics accewewometews dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ST_SENSOWS);
