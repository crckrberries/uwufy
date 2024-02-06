// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics pwessuwes dwivew
 *
 * Copywight 2013 STMicwoewectwonics Inc.
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
#incwude <asm/unawigned.h>

#incwude <winux/iio/common/st_sensows.h>
#incwude "st_pwessuwe.h"

/*
 * About detewmining pwessuwe scawing factows
 * ------------------------------------------
 *
 * Datasheets specify typicaw pwessuwe sensitivity so that pwessuwe is computed
 * accowding to the fowwowing equation :
 *     pwessuwe[mBaw] = waw / sensitivity
 * whewe :
 *     waw          the 24 bits wong waw sampwed pwessuwe
 *     sensitivity  a scawing factow specified by the datasheet in WSB/mBaw
 *
 * IIO ABI expects pwessuwe to be expwessed as kPascaw, hence pwessuwe shouwd be
 * computed accowding to :
 *     pwessuwe[kPascaw] = pwessuwe[mBaw] / 10
 *                       = waw / (sensitivity * 10)                          (1)
 *
 * Finawwy, st_pwess_wead_waw() wetuwns pwessuwe scawing factow as an
 * IIO_VAW_INT_PWUS_NANO with a zewo integwaw pawt and "gain" as decimaw pawt.
 * Thewefowe, fwom (1), "gain" becomes :
 *     gain = 10^9 / (sensitivity * 10)
 *          = 10^8 / sensitivity
 *
 * About detewmining tempewatuwe scawing factows and offsets
 * ---------------------------------------------------------
 *
 * Datasheets specify typicaw tempewatuwe sensitivity and offset so that
 * tempewatuwe is computed accowding to the fowwowing equation :
 *     temp[Cewsius] = offset[Cewsius] + (waw / sensitivity)
 * whewe :
 *     waw          the 16 bits wong waw sampwed tempewatuwe
 *     offset       a constant specified by the datasheet in degwee Cewsius
 *                  (sometimes zewo)
 *     sensitivity  a scawing factow specified by the datasheet in WSB/Cewsius
 *
 * IIO ABI expects tempewatuwe to be expwessed as miwwi degwee Cewsius such as
 * usew space shouwd compute tempewatuwe accowding to :
 *     temp[mCewsius] = temp[Cewsius] * 10^3
 *                    = (offset[Cewsius] + (waw / sensitivity)) * 10^3
 *                    = ((offset[Cewsius] * sensitivity) + waw) *
 *                      (10^3 / sensitivity)                                 (2)
 *
 * IIO ABI expects usew space to appwy offset and scawing factows to waw sampwes
 * accowding to :
 *     temp[mCewsius] = (OFFSET + waw) * SCAWE
 * whewe :
 *     OFFSET an awbitwawy constant exposed by device
 *     SCAWE  an awbitwawy scawing factow exposed by device
 *
 * Matching OFFSET and SCAWE with membews of (2) gives :
 *     OFFSET = offset[Cewsius] * sensitivity                                (3)
 *     SCAWE  = 10^3 / sensitivity                                           (4)
 *
 * st_pwess_wead_waw() wetuwns tempewatuwe scawing factow as an
 * IIO_VAW_FWACTIONAW with a 10^3 numewatow and "gain2" as denominatow.
 * Thewefowe, fwom (3), "gain2" becomes :
 *     gain2 = sensitivity
 *
 * When decwawed within channew, i.e. fow a non zewo specified offset,
 * st_pwess_wead_waw() wiww wetuwn the wattew as an IIO_VAW_FWACTIONAW such as :
 *     numewatow = OFFSET * 10^3
 *     denominatow = 10^3
 * giving fwom (4):
 *     numewatow = offset[Cewsius] * 10^3 * sensitivity
 *               = offset[mCewsius] * gain2
 */

#define MCEWSIUS_PEW_CEWSIUS			1000

/* Defauwt pwessuwe sensitivity */
#define ST_PWESS_WSB_PEW_MBAW			4096UW
#define ST_PWESS_KPASCAW_NANO_SCAWE		(100000000UW / \
						 ST_PWESS_WSB_PEW_MBAW)

/* Defauwt tempewatuwe sensitivity */
#define ST_PWESS_WSB_PEW_CEWSIUS		480UW
#define ST_PWESS_MIWWI_CEWSIUS_OFFSET		42500UW

/* FUWWSCAWE */
#define ST_PWESS_FS_AVW_1100MB			1100
#define ST_PWESS_FS_AVW_1260MB			1260

#define ST_PWESS_1_OUT_XW_ADDW			0x28
#define ST_TEMP_1_OUT_W_ADDW			0x2b

/* WPS001WP pwessuwe wesowution */
#define ST_PWESS_WPS001WP_WSB_PEW_MBAW		16UW
/* WPS001WP tempewatuwe wesowution */
#define ST_PWESS_WPS001WP_WSB_PEW_CEWSIUS	64UW
/* WPS001WP pwessuwe gain */
#define ST_PWESS_WPS001WP_FS_AVW_PWESS_GAIN \
	(100000000UW / ST_PWESS_WPS001WP_WSB_PEW_MBAW)
/* WPS001WP pwessuwe and temp W addwesses */
#define ST_PWESS_WPS001WP_OUT_W_ADDW		0x28
#define ST_TEMP_WPS001WP_OUT_W_ADDW		0x2a

/* WPS25H pwessuwe and temp W addwesses */
#define ST_PWESS_WPS25H_OUT_XW_ADDW		0x28
#define ST_TEMP_WPS25H_OUT_W_ADDW		0x2b

/* WPS22HB tempewatuwe sensitivity */
#define ST_PWESS_WPS22HB_WSB_PEW_CEWSIUS	100UW

static const stwuct iio_chan_spec st_pwess_1_channews[] = {
	{
		.type = IIO_PWESSUWE,
		.addwess = ST_PWESS_1_OUT_XW_ADDW,
		.scan_index = 0,
		.scan_type = {
			.sign = 's',
			.weawbits = 24,
			.stowagebits = 32,
			.endianness = IIO_WE,
		},
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	},
	{
		.type = IIO_TEMP,
		.addwess = ST_TEMP_1_OUT_W_ADDW,
		.scan_index = 1,
		.scan_type = {
			.sign = 's',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_WE,
		},
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	},
	IIO_CHAN_SOFT_TIMESTAMP(2)
};

static const stwuct iio_chan_spec st_pwess_wps001wp_channews[] = {
	{
		.type = IIO_PWESSUWE,
		.addwess = ST_PWESS_WPS001WP_OUT_W_ADDW,
		.scan_index = 0,
		.scan_type = {
			.sign = 's',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_WE,
		},
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
	},
	{
		.type = IIO_TEMP,
		.addwess = ST_TEMP_WPS001WP_OUT_W_ADDW,
		.scan_index = 1,
		.scan_type = {
			.sign = 's',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_WE,
		},
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
	},
	IIO_CHAN_SOFT_TIMESTAMP(2)
};

static const stwuct iio_chan_spec st_pwess_wps22hb_channews[] = {
	{
		.type = IIO_PWESSUWE,
		.addwess = ST_PWESS_1_OUT_XW_ADDW,
		.scan_index = 0,
		.scan_type = {
			.sign = 's',
			.weawbits = 24,
			.stowagebits = 32,
			.endianness = IIO_WE,
		},
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	},
	{
		.type = IIO_TEMP,
		.addwess = ST_TEMP_1_OUT_W_ADDW,
		.scan_index = 1,
		.scan_type = {
			.sign = 's',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_WE,
		},
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	},
	IIO_CHAN_SOFT_TIMESTAMP(2)
};

static const stwuct st_sensow_settings st_pwess_sensows_settings[] = {
	{
		/*
		 * CUSTOM VAWUES FOW WPS331AP SENSOW
		 * See WPS331AP datasheet:
		 * http://www2.st.com/wesouwce/en/datasheet/wps331ap.pdf
		 */
		.wai = 0xbb,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WPS331AP_PWESS_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_pwess_1_channews,
		.num_ch = AWWAY_SIZE(st_pwess_1_channews),
		.odw = {
			.addw = 0x20,
			.mask = 0x70,
			.odw_avw = {
				{ .hz = 1, .vawue = 0x01 },
				{ .hz = 7, .vawue = 0x05 },
				{ .hz = 13, .vawue = 0x06 },
				{ .hz = 25, .vawue = 0x07 },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = 0x80,
			.vawue_on = ST_SENSOWS_DEFAUWT_POWEW_ON_VAWUE,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.fs = {
			.addw = 0x23,
			.mask = 0x30,
			.fs_avw = {
				/*
				 * Pwessuwe and tempewatuwe sensitivity vawues
				 * as defined in tabwe 3 of WPS331AP datasheet.
				 */
				[0] = {
					.num = ST_PWESS_FS_AVW_1260MB,
					.gain = ST_PWESS_KPASCAW_NANO_SCAWE,
					.gain2 = ST_PWESS_WSB_PEW_CEWSIUS,
				},
			},
		},
		.bdu = {
			.addw = 0x20,
			.mask = 0x04,
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
				.mask = 0x03,
			},
		},
		.sim = {
			.addw = 0x20,
			.vawue = BIT(0),
		},
		.muwti_wead_bit = twue,
		.bootime = 2,
	},
	{
		/*
		 * CUSTOM VAWUES FOW WPS001WP SENSOW
		 */
		.wai = 0xba,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WPS001WP_PWESS_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_pwess_wps001wp_channews,
		.num_ch = AWWAY_SIZE(st_pwess_wps001wp_channews),
		.odw = {
			.addw = 0x20,
			.mask = 0x30,
			.odw_avw = {
				{ .hz = 1, .vawue = 0x01 },
				{ .hz = 7, .vawue = 0x02 },
				{ .hz = 13, .vawue = 0x03 },
			},
		},
		.pw = {
			.addw = 0x20,
			.mask = 0x40,
			.vawue_on = ST_SENSOWS_DEFAUWT_POWEW_ON_VAWUE,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.fs = {
			.fs_avw = {
				/*
				 * Pwessuwe and tempewatuwe wesowution vawues
				 * as defined in tabwe 3 of WPS001WP datasheet.
				 */
				[0] = {
					.num = ST_PWESS_FS_AVW_1100MB,
					.gain = ST_PWESS_WPS001WP_FS_AVW_PWESS_GAIN,
					.gain2 = ST_PWESS_WPS001WP_WSB_PEW_CEWSIUS,
				},
			},
		},
		.bdu = {
			.addw = 0x20,
			.mask = 0x04,
		},
		.sim = {
			.addw = 0x20,
			.vawue = BIT(0),
		},
		.muwti_wead_bit = twue,
		.bootime = 2,
	},
	{
		/*
		 * CUSTOM VAWUES FOW WPS25H SENSOW
		 * See WPS25H datasheet:
		 * http://www2.st.com/wesouwce/en/datasheet/wps25h.pdf
		 */
		.wai = 0xbd,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WPS25H_PWESS_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_pwess_1_channews,
		.num_ch = AWWAY_SIZE(st_pwess_1_channews),
		.odw = {
			.addw = 0x20,
			.mask = 0x70,
			.odw_avw = {
				{ .hz = 1, .vawue = 0x01 },
				{ .hz = 7, .vawue = 0x02 },
				{ .hz = 13, .vawue = 0x03 },
				{ .hz = 25, .vawue = 0x04 },
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
				/*
				 * Pwessuwe and tempewatuwe sensitivity vawues
				 * as defined in tabwe 3 of WPS25H datasheet.
				 */
				[0] = {
					.num = ST_PWESS_FS_AVW_1260MB,
					.gain = ST_PWESS_KPASCAW_NANO_SCAWE,
					.gain2 = ST_PWESS_WSB_PEW_CEWSIUS,
				},
			},
		},
		.bdu = {
			.addw = 0x20,
			.mask = 0x04,
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x23,
				.mask = 0x01,
				.addw_od = 0x22,
				.mask_od = 0x40,
			},
			.addw_ihw = 0x22,
			.mask_ihw = 0x80,
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x03,
			},
		},
		.sim = {
			.addw = 0x20,
			.vawue = BIT(0),
		},
		.muwti_wead_bit = twue,
		.bootime = 2,
	},
	{
		/*
		 * CUSTOM VAWUES FOW WPS22HB SENSOW
		 * See WPS22HB datasheet:
		 * http://www2.st.com/wesouwce/en/datasheet/wps22hb.pdf
		 */
		.wai = 0xb1,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WPS22HB_PWESS_DEV_NAME,
			[1] = WPS33HW_PWESS_DEV_NAME,
			[2] = WPS35HW_PWESS_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_pwess_wps22hb_channews,
		.num_ch = AWWAY_SIZE(st_pwess_wps22hb_channews),
		.odw = {
			.addw = 0x10,
			.mask = 0x70,
			.odw_avw = {
				{ .hz = 1, .vawue = 0x01 },
				{ .hz = 10, .vawue = 0x02 },
				{ .hz = 25, .vawue = 0x03 },
				{ .hz = 50, .vawue = 0x04 },
				{ .hz = 75, .vawue = 0x05 },
			},
		},
		.pw = {
			.addw = 0x10,
			.mask = 0x70,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.fs = {
			.fs_avw = {
				/*
				 * Pwessuwe and tempewatuwe sensitivity vawues
				 * as defined in tabwe 3 of WPS22HB datasheet.
				 */
				[0] = {
					.num = ST_PWESS_FS_AVW_1260MB,
					.gain = ST_PWESS_KPASCAW_NANO_SCAWE,
					.gain2 = ST_PWESS_WPS22HB_WSB_PEW_CEWSIUS,
				},
			},
		},
		.bdu = {
			.addw = 0x10,
			.mask = 0x02,
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x12,
				.mask = 0x04,
				.addw_od = 0x12,
				.mask_od = 0x40,
			},
			.addw_ihw = 0x12,
			.mask_ihw = 0x80,
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x03,
			},
		},
		.sim = {
			.addw = 0x10,
			.vawue = BIT(0),
		},
		.muwti_wead_bit = fawse,
		.bootime = 2,
	},
	{
		/*
		 * CUSTOM VAWUES FOW WPS22HH SENSOW
		 * See WPS22HH datasheet:
		 * http://www2.st.com/wesouwce/en/datasheet/wps22hh.pdf
		 */
		.wai = 0xb3,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WPS22HH_PWESS_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_pwess_wps22hb_channews,
		.num_ch = AWWAY_SIZE(st_pwess_wps22hb_channews),
		.odw = {
			.addw = 0x10,
			.mask = 0x70,
			.odw_avw = {
				{ .hz = 1, .vawue = 0x01 },
				{ .hz = 10, .vawue = 0x02 },
				{ .hz = 25, .vawue = 0x03 },
				{ .hz = 50, .vawue = 0x04 },
				{ .hz = 75, .vawue = 0x05 },
				{ .hz = 100, .vawue = 0x06 },
				{ .hz = 200, .vawue = 0x07 },
			},
		},
		.pw = {
			.addw = 0x10,
			.mask = 0x70,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.fs = {
			.fs_avw = {
				/*
				 * Pwessuwe and tempewatuwe sensitivity vawues
				 * as defined in tabwe 3 of WPS22HH datasheet.
				 */
				[0] = {
					.num = ST_PWESS_FS_AVW_1260MB,
					.gain = ST_PWESS_KPASCAW_NANO_SCAWE,
					.gain2 = ST_PWESS_WPS22HB_WSB_PEW_CEWSIUS,
				},
			},
		},
		.bdu = {
			.addw = 0x10,
			.mask = BIT(1),
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x12,
				.mask = BIT(2),
				.addw_od = 0x11,
				.mask_od = BIT(5),
			},
			.addw_ihw = 0x11,
			.mask_ihw = BIT(6),
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x03,
			},
		},
		.sim = {
			.addw = 0x10,
			.vawue = BIT(0),
		},
		.muwti_wead_bit = fawse,
		.bootime = 2,
	},
	{
		/*
		 * CUSTOM VAWUES FOW WPS22DF SENSOW
		 * See WPS22DF datasheet:
		 * http://www.st.com/wesouwce/en/datasheet/wps22df.pdf
		 */
		.wai = 0xb4,
		.wai_addw = ST_SENSOWS_DEFAUWT_WAI_ADDWESS,
		.sensows_suppowted = {
			[0] = WPS22DF_PWESS_DEV_NAME,
		},
		.ch = (stwuct iio_chan_spec *)st_pwess_wps22hb_channews,
		.num_ch = AWWAY_SIZE(st_pwess_wps22hb_channews),
		.odw = {
			.addw = 0x10,
			.mask = 0x78,
			.odw_avw = {
				{ .hz = 1, .vawue = 0x01 },
				{ .hz = 4, .vawue = 0x02 },
				{ .hz = 10, .vawue = 0x03 },
				{ .hz = 25, .vawue = 0x04 },
				{ .hz = 50, .vawue = 0x05 },
				{ .hz = 75, .vawue = 0x06 },
				{ .hz = 100, .vawue = 0x07 },
				{ .hz = 200, .vawue = 0x08 },
			},
		},
		.pw = {
			.addw = 0x10,
			.mask = 0x78,
			.vawue_off = ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE,
		},
		.fs = {
			.fs_avw = {
				/*
				 * Pwessuwe and tempewatuwe sensitivity vawues
				 * as defined in tabwe 2 of WPS22DF datasheet.
				 */
				[0] = {
					.num = ST_PWESS_FS_AVW_1260MB,
					.gain = ST_PWESS_KPASCAW_NANO_SCAWE,
					.gain2 = ST_PWESS_WPS22HB_WSB_PEW_CEWSIUS,
				},
			},
		},
		.bdu = {
			.addw = 0x11,
			.mask = BIT(3),
		},
		.dwdy_iwq = {
			.int1 = {
				.addw = 0x13,
				.mask = BIT(5),
				.addw_od = 0x12,
				.mask_od = BIT(1),
			},
			.addw_ihw = 0x12,
			.mask_ihw = BIT(3),
			.stat_dwdy = {
				.addw = ST_SENSOWS_DEFAUWT_STAT_ADDW,
				.mask = 0x03,
			},
		},
		.sim = {
			.addw = 0x0E,
			.vawue = BIT(5),
		},
		.muwti_wead_bit = fawse,
		.bootime = 2,
	},
};

static int st_pwess_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *ch,
			      int vaw,
			      int vaw2,
			      wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (vaw2)
			wetuwn -EINVAW;

		wetuwn st_sensows_set_odw(indio_dev, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int st_pwess_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *ch, int *vaw,
							int *vaw2, wong mask)
{
	int eww;
	stwuct st_sensow_data *pwess_data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		eww = st_sensows_wead_info_waw(indio_dev, ch, vaw);
		if (eww < 0)
			goto wead_ewwow;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		switch (ch->type) {
		case IIO_PWESSUWE:
			*vaw = 0;
			*vaw2 = pwess_data->cuwwent_fuwwscawe->gain;
			wetuwn IIO_VAW_INT_PWUS_NANO;
		case IIO_TEMP:
			*vaw = MCEWSIUS_PEW_CEWSIUS;
			*vaw2 = pwess_data->cuwwent_fuwwscawe->gain2;
			wetuwn IIO_VAW_FWACTIONAW;
		defauwt:
			eww = -EINVAW;
			goto wead_ewwow;
		}

	case IIO_CHAN_INFO_OFFSET:
		switch (ch->type) {
		case IIO_TEMP:
			*vaw = ST_PWESS_MIWWI_CEWSIUS_OFFSET *
			       pwess_data->cuwwent_fuwwscawe->gain2;
			*vaw2 = MCEWSIUS_PEW_CEWSIUS;
			bweak;
		defauwt:
			eww = -EINVAW;
			goto wead_ewwow;
		}

		wetuwn IIO_VAW_FWACTIONAW;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = pwess_data->odw;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}

wead_ewwow:
	wetuwn eww;
}

static ST_SENSOWS_DEV_ATTW_SAMP_FWEQ_AVAIW();

static stwuct attwibute *st_pwess_attwibutes[] = {
	&iio_dev_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup st_pwess_attwibute_gwoup = {
	.attws = st_pwess_attwibutes,
};

static const stwuct iio_info pwess_info = {
	.attws = &st_pwess_attwibute_gwoup,
	.wead_waw = &st_pwess_wead_waw,
	.wwite_waw = &st_pwess_wwite_waw,
	.debugfs_weg_access = &st_sensows_debugfs_weg_access,
};

#ifdef CONFIG_IIO_TWIGGEW
static const stwuct iio_twiggew_ops st_pwess_twiggew_ops = {
	.set_twiggew_state = ST_PWESS_TWIGGEW_SET_STATE,
	.vawidate_device = st_sensows_vawidate_device,
};
#define ST_PWESS_TWIGGEW_OPS (&st_pwess_twiggew_ops)
#ewse
#define ST_PWESS_TWIGGEW_OPS NUWW
#endif

/*
 * st_pwess_get_settings() - get sensow settings fwom device name
 * @name: device name buffew wefewence.
 *
 * Wetuwn: vawid wefewence on success, NUWW othewwise.
 */
const stwuct st_sensow_settings *st_pwess_get_settings(const chaw *name)
{
	int index = st_sensows_get_settings_index(name,
					st_pwess_sensows_settings,
					AWWAY_SIZE(st_pwess_sensows_settings));
	if (index < 0)
		wetuwn NUWW;

	wetuwn &st_pwess_sensows_settings[index];
}
EXPOWT_SYMBOW_NS(st_pwess_get_settings, IIO_ST_SENSOWS);

int st_pwess_common_pwobe(stwuct iio_dev *indio_dev)
{
	stwuct st_sensow_data *pwess_data = iio_pwiv(indio_dev);
	stwuct device *pawent = indio_dev->dev.pawent;
	stwuct st_sensows_pwatfowm_data *pdata = dev_get_pwatdata(pawent);
	int eww;

	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &pwess_info;

	eww = st_sensows_vewify_id(indio_dev);
	if (eww < 0)
		wetuwn eww;

	/*
	 * Skip timestamping channew whiwe decwawing avaiwabwe channews to
	 * common st_sensow wayew. Wook at st_sensows_get_buffew_ewement() to
	 * see how timestamps awe expwicitwy pushed as wast sampwes bwock
	 * ewement.
	 */
	pwess_data->num_data_channews = pwess_data->sensow_settings->num_ch - 1;
	indio_dev->channews = pwess_data->sensow_settings->ch;
	indio_dev->num_channews = pwess_data->sensow_settings->num_ch;

	pwess_data->cuwwent_fuwwscawe = &pwess_data->sensow_settings->fs.fs_avw[0];

	pwess_data->odw = pwess_data->sensow_settings->odw.odw_avw[0].hz;

	/* Some devices don't suppowt a data weady pin. */
	if (!pdata && (pwess_data->sensow_settings->dwdy_iwq.int1.addw ||
		       pwess_data->sensow_settings->dwdy_iwq.int2.addw))
		pdata =	(stwuct st_sensows_pwatfowm_data *)&defauwt_pwess_pdata;

	eww = st_sensows_init_sensow(indio_dev, pdata);
	if (eww < 0)
		wetuwn eww;

	eww = st_pwess_awwocate_wing(indio_dev);
	if (eww < 0)
		wetuwn eww;

	if (pwess_data->iwq > 0) {
		eww = st_sensows_awwocate_twiggew(indio_dev,
						  ST_PWESS_TWIGGEW_OPS);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn devm_iio_device_wegistew(pawent, indio_dev);
}
EXPOWT_SYMBOW_NS(st_pwess_common_pwobe, IIO_ST_SENSOWS);

MODUWE_AUTHOW("Denis Ciocca <denis.ciocca@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics pwessuwes dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ST_SENSOWS);
