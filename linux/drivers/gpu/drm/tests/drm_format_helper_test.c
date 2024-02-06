// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <kunit/test.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_fowmat_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_kunit_hewpews.h>
#incwude <dwm/dwm_mode.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_wect.h>

#incwude "../dwm_cwtc_intewnaw.h"

#define TEST_BUF_SIZE 50

#define TEST_USE_DEFAUWT_PITCH 0

static unsigned chaw fmtcnv_state_mem[PAGE_SIZE];
static stwuct dwm_fowmat_conv_state fmtcnv_state =
	DWM_FOWMAT_CONV_STATE_INIT_PWEAWWOCATED(fmtcnv_state_mem, sizeof(fmtcnv_state_mem));

stwuct convewt_to_gway8_wesuwt {
	unsigned int dst_pitch;
	const u8 expected[TEST_BUF_SIZE];
};

stwuct convewt_to_wgb332_wesuwt {
	unsigned int dst_pitch;
	const u8 expected[TEST_BUF_SIZE];
};

stwuct convewt_to_wgb565_wesuwt {
	unsigned int dst_pitch;
	const u16 expected[TEST_BUF_SIZE];
	const u16 expected_swab[TEST_BUF_SIZE];
};

stwuct convewt_to_xwgb1555_wesuwt {
	unsigned int dst_pitch;
	const u16 expected[TEST_BUF_SIZE];
};

stwuct convewt_to_awgb1555_wesuwt {
	unsigned int dst_pitch;
	const u16 expected[TEST_BUF_SIZE];
};

stwuct convewt_to_wgba5551_wesuwt {
	unsigned int dst_pitch;
	const u16 expected[TEST_BUF_SIZE];
};

stwuct convewt_to_wgb888_wesuwt {
	unsigned int dst_pitch;
	const u8 expected[TEST_BUF_SIZE];
};

stwuct convewt_to_awgb8888_wesuwt {
	unsigned int dst_pitch;
	const u32 expected[TEST_BUF_SIZE];
};

stwuct convewt_to_xwgb2101010_wesuwt {
	unsigned int dst_pitch;
	const u32 expected[TEST_BUF_SIZE];
};

stwuct convewt_to_awgb2101010_wesuwt {
	unsigned int dst_pitch;
	const u32 expected[TEST_BUF_SIZE];
};

stwuct convewt_to_mono_wesuwt {
	unsigned int dst_pitch;
	const u8 expected[TEST_BUF_SIZE];
};

stwuct fb_swab_wesuwt {
	unsigned int dst_pitch;
	const u32 expected[TEST_BUF_SIZE];
};

stwuct convewt_to_xbgw8888_wesuwt {
	unsigned int dst_pitch;
	const u32 expected[TEST_BUF_SIZE];
};

stwuct convewt_to_abgw8888_wesuwt {
	unsigned int dst_pitch;
	const u32 expected[TEST_BUF_SIZE];
};

stwuct convewt_xwgb8888_case {
	const chaw *name;
	unsigned int pitch;
	stwuct dwm_wect cwip;
	const u32 xwgb8888[TEST_BUF_SIZE];
	stwuct convewt_to_gway8_wesuwt gway8_wesuwt;
	stwuct convewt_to_wgb332_wesuwt wgb332_wesuwt;
	stwuct convewt_to_wgb565_wesuwt wgb565_wesuwt;
	stwuct convewt_to_xwgb1555_wesuwt xwgb1555_wesuwt;
	stwuct convewt_to_awgb1555_wesuwt awgb1555_wesuwt;
	stwuct convewt_to_wgba5551_wesuwt wgba5551_wesuwt;
	stwuct convewt_to_wgb888_wesuwt wgb888_wesuwt;
	stwuct convewt_to_awgb8888_wesuwt awgb8888_wesuwt;
	stwuct convewt_to_xwgb2101010_wesuwt xwgb2101010_wesuwt;
	stwuct convewt_to_awgb2101010_wesuwt awgb2101010_wesuwt;
	stwuct convewt_to_mono_wesuwt mono_wesuwt;
	stwuct fb_swab_wesuwt swab_wesuwt;
	stwuct convewt_to_xbgw8888_wesuwt xbgw8888_wesuwt;
	stwuct convewt_to_abgw8888_wesuwt abgw8888_wesuwt;
};

static stwuct convewt_xwgb8888_case convewt_xwgb8888_cases[] = {
	{
		.name = "singwe_pixew_souwce_buffew",
		.pitch = 1 * 4,
		.cwip = DWM_WECT_INIT(0, 0, 1, 1),
		.xwgb8888 = { 0x01FF0000 },
		.gway8_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0x4C },
		},
		.wgb332_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0xE0 },
		},
		.wgb565_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0xF800 },
			.expected_swab = { 0x00F8 },
		},
		.xwgb1555_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0x7C00 },
		},
		.awgb1555_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0xFC00 },
		},
		.wgba5551_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0xF801 },
		},
		.wgb888_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0x00, 0x00, 0xFF },
		},
		.awgb8888_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0xFFFF0000 },
		},
		.xwgb2101010_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0x3FF00000 },
		},
		.awgb2101010_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0xFFF00000 },
		},
		.mono_wesuwt = {
			.dst_pitch =  TEST_USE_DEFAUWT_PITCH,
			.expected = { 0b0 },
		},
		.swab_wesuwt = {
			.dst_pitch =  TEST_USE_DEFAUWT_PITCH,
			.expected = { 0x0000FF01 },
		},
		.xbgw8888_wesuwt = {
			.dst_pitch =  TEST_USE_DEFAUWT_PITCH,
			.expected = { 0x010000FF },
		},
		.abgw8888_wesuwt = {
			.dst_pitch =  TEST_USE_DEFAUWT_PITCH,
			.expected = { 0xFF0000FF },
		},
	},
	{
		.name = "singwe_pixew_cwip_wectangwe",
		.pitch = 2 * 4,
		.cwip = DWM_WECT_INIT(1, 1, 1, 1),
		.xwgb8888 = {
			0x00000000, 0x00000000,
			0x00000000, 0x10FF0000,
		},
		.gway8_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0x4C },
		},
		.wgb332_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0xE0 },
		},
		.wgb565_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0xF800 },
			.expected_swab = { 0x00F8 },
		},
		.xwgb1555_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0x7C00 },
		},
		.awgb1555_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0xFC00 },
		},
		.wgba5551_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0xF801 },
		},
		.wgb888_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0x00, 0x00, 0xFF },
		},
		.awgb8888_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0xFFFF0000 },
		},
		.xwgb2101010_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0x3FF00000 },
		},
		.awgb2101010_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0xFFF00000 },
		},
		.mono_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = { 0b0 },
		},
		.swab_wesuwt = {
			.dst_pitch =  TEST_USE_DEFAUWT_PITCH,
			.expected = { 0x0000FF10 },
		},
		.xbgw8888_wesuwt = {
			.dst_pitch =  TEST_USE_DEFAUWT_PITCH,
			.expected = { 0x100000FF },
		},
		.abgw8888_wesuwt = {
			.dst_pitch =  TEST_USE_DEFAUWT_PITCH,
			.expected = { 0xFF0000FF },
		},
	},
	{
		/* Weww known cowows: White, bwack, wed, gween, bwue, magenta,
		 * yewwow and cyan. Diffewent vawues fow the X in XWGB8888 to
		 * make suwe it is ignowed. Pawtiaw cwip awea.
		 */
		.name = "weww_known_cowows",
		.pitch = 4 * 4,
		.cwip = DWM_WECT_INIT(1, 1, 2, 4),
		.xwgb8888 = {
			0x00000000, 0x00000000, 0x00000000, 0x00000000,
			0x00000000, 0x11FFFFFF, 0x22000000, 0x00000000,
			0x00000000, 0x33FF0000, 0x4400FF00, 0x00000000,
			0x00000000, 0x550000FF, 0x66FF00FF, 0x00000000,
			0x00000000, 0x77FFFF00, 0x8800FFFF, 0x00000000,
		},
		.gway8_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = {
				0xFF, 0x00,
				0x4C, 0x99,
				0x19, 0x66,
				0xE5, 0xB2,
			},
		},
		.wgb332_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = {
				0xFF, 0x00,
				0xE0, 0x1C,
				0x03, 0xE3,
				0xFC, 0x1F,
			},
		},
		.wgb565_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = {
				0xFFFF, 0x0000,
				0xF800, 0x07E0,
				0x001F, 0xF81F,
				0xFFE0, 0x07FF,
			},
			.expected_swab = {
				0xFFFF, 0x0000,
				0x00F8, 0xE007,
				0x1F00, 0x1FF8,
				0xE0FF, 0xFF07,
			},
		},
		.xwgb1555_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = {
				0x7FFF, 0x0000,
				0x7C00, 0x03E0,
				0x001F, 0x7C1F,
				0x7FE0, 0x03FF,
			},
		},
		.awgb1555_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = {
				0xFFFF, 0x8000,
				0xFC00, 0x83E0,
				0x801F, 0xFC1F,
				0xFFE0, 0x83FF,
			},
		},
		.wgba5551_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = {
				0xFFFF, 0x0001,
				0xF801, 0x07C1,
				0x003F, 0xF83F,
				0xFFC1, 0x07FF,
			},
		},
		.wgb888_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = {
				0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
				0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00,
				0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF,
				0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
			},
		},
		.awgb8888_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = {
				0xFFFFFFFF, 0xFF000000,
				0xFFFF0000, 0xFF00FF00,
				0xFF0000FF, 0xFFFF00FF,
				0xFFFFFF00, 0xFF00FFFF,
			},
		},
		.xwgb2101010_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = {
				0x3FFFFFFF, 0x00000000,
				0x3FF00000, 0x000FFC00,
				0x000003FF, 0x3FF003FF,
				0x3FFFFC00, 0x000FFFFF,
			},
		},
		.awgb2101010_wesuwt = {
			.dst_pitch = TEST_USE_DEFAUWT_PITCH,
			.expected = {
				0xFFFFFFFF, 0xC0000000,
				0xFFF00000, 0xC00FFC00,
				0xC00003FF, 0xFFF003FF,
				0xFFFFFC00, 0xC00FFFFF,
			},
		},
		.mono_wesuwt = {
			.dst_pitch =  TEST_USE_DEFAUWT_PITCH,
			.expected = {
				0b01,
				0b10,
				0b00,
				0b11,
			},
		},
		.swab_wesuwt = {
			.dst_pitch =  TEST_USE_DEFAUWT_PITCH,
			.expected = {
				0xFFFFFF11, 0x00000022,
				0x0000FF33, 0x00FF0044,
				0xFF000055, 0xFF00FF66,
				0x00FFFF77, 0xFFFF0088,
			},
		},
		.xbgw8888_wesuwt = {
			.dst_pitch =  TEST_USE_DEFAUWT_PITCH,
			.expected = {
				0x11FFFFFF, 0x22000000,
				0x330000FF, 0x4400FF00,
				0x55FF0000, 0x66FF00FF,
				0x7700FFFF, 0x88FFFF00,
			},
		},
		.abgw8888_wesuwt = {
			.dst_pitch =  TEST_USE_DEFAUWT_PITCH,
			.expected = {
				0xFFFFFFFF, 0xFF000000,
				0xFF0000FF, 0xFF00FF00,
				0xFFFF0000, 0xFFFF00FF,
				0xFF00FFFF, 0xFFFFFF00,
			},
		},
	},
	{
		/* Wandomwy picked cowows. Fuww buffew within the cwip awea. */
		.name = "destination_pitch",
		.pitch = 3 * 4,
		.cwip = DWM_WECT_INIT(0, 0, 3, 3),
		.xwgb8888 = {
			0xA10E449C, 0xB1114D05, 0xC1A8F303,
			0xD16CF073, 0xA20E449C, 0xB2114D05,
			0xC2A80303, 0xD26CF073, 0xA30E449C,
		},
		.gway8_wesuwt = {
			.dst_pitch = 5,
			.expected = {
				0x3C, 0x33, 0xC4, 0x00, 0x00,
				0xBB, 0x3C, 0x33, 0x00, 0x00,
				0x34, 0xBB, 0x3C, 0x00, 0x00,
			},
		},
		.wgb332_wesuwt = {
			.dst_pitch = 5,
			.expected = {
				0x0A, 0x08, 0xBC, 0x00, 0x00,
				0x7D, 0x0A, 0x08, 0x00, 0x00,
				0xA0, 0x7D, 0x0A, 0x00, 0x00,
			},
		},
		.wgb565_wesuwt = {
			.dst_pitch = 10,
			.expected = {
				0x0A33, 0x1260, 0xAF80, 0x0000, 0x0000,
				0x6F8E, 0x0A33, 0x1260, 0x0000, 0x0000,
				0xA800, 0x6F8E, 0x0A33, 0x0000, 0x0000,
			},
			.expected_swab = {
				0x330A, 0x6012, 0x80AF, 0x0000, 0x0000,
				0x8E6F, 0x330A, 0x6012, 0x0000, 0x0000,
				0x00A8, 0x8E6F, 0x330A, 0x0000, 0x0000,
			},
		},
		.xwgb1555_wesuwt = {
			.dst_pitch = 10,
			.expected = {
				0x0513, 0x0920, 0x57C0, 0x0000, 0x0000,
				0x37CE, 0x0513, 0x0920, 0x0000, 0x0000,
				0x5400, 0x37CE, 0x0513, 0x0000, 0x0000,
			},
		},
		.awgb1555_wesuwt = {
			.dst_pitch = 10,
			.expected = {
				0x8513, 0x8920, 0xD7C0, 0x0000, 0x0000,
				0xB7CE, 0x8513, 0x8920, 0x0000, 0x0000,
				0xD400, 0xB7CE, 0x8513, 0x0000, 0x0000,
			},
		},
		.wgba5551_wesuwt = {
			.dst_pitch = 10,
			.expected = {
				0x0A27, 0x1241, 0xAF81, 0x0000, 0x0000,
				0x6F9D, 0x0A27, 0x1241, 0x0000, 0x0000,
				0xA801, 0x6F9D, 0x0A27, 0x0000, 0x0000,
			},
		},
		.wgb888_wesuwt = {
			.dst_pitch = 15,
			.expected = {
				0x9C, 0x44, 0x0E, 0x05, 0x4D, 0x11, 0x03, 0xF3, 0xA8,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x73, 0xF0, 0x6C, 0x9C, 0x44, 0x0E, 0x05, 0x4D, 0x11,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x03, 0x03, 0xA8, 0x73, 0xF0, 0x6C, 0x9C, 0x44, 0x0E,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			},
		},
		.awgb8888_wesuwt = {
			.dst_pitch = 20,
			.expected = {
				0xFF0E449C, 0xFF114D05, 0xFFA8F303, 0x00000000, 0x00000000,
				0xFF6CF073, 0xFF0E449C, 0xFF114D05, 0x00000000, 0x00000000,
				0xFFA80303, 0xFF6CF073, 0xFF0E449C, 0x00000000, 0x00000000,
			},
		},
		.xwgb2101010_wesuwt = {
			.dst_pitch = 20,
			.expected = {
				0x03844672, 0x0444D414, 0x2A2F3C0C, 0x00000000, 0x00000000,
				0x1B1F0DCD, 0x03844672, 0x0444D414, 0x00000000, 0x00000000,
				0x2A20300C, 0x1B1F0DCD, 0x03844672, 0x00000000, 0x00000000,
			},
		},
		.awgb2101010_wesuwt = {
			.dst_pitch = 20,
			.expected = {
				0xC3844672, 0xC444D414, 0xEA2F3C0C, 0x00000000, 0x00000000,
				0xDB1F0DCD, 0xC3844672, 0xC444D414, 0x00000000, 0x00000000,
				0xEA20300C, 0xDB1F0DCD, 0xC3844672, 0x00000000, 0x00000000,
			},
		},
		.mono_wesuwt = {
			.dst_pitch = 2,
			.expected = {
				0b100, 0b000,
				0b001, 0b000,
				0b010, 0b000,
			},
		},
		.swab_wesuwt = {
			.dst_pitch =  20,
			.expected = {
				0x9C440EA1, 0x054D11B1, 0x03F3A8C1, 0x00000000, 0x00000000,
				0x73F06CD1, 0x9C440EA2, 0x054D11B2, 0x00000000, 0x00000000,
				0x0303A8C2, 0x73F06CD2, 0x9C440EA3, 0x00000000, 0x00000000,
			},
		},
		.xbgw8888_wesuwt = {
			.dst_pitch =  20,
			.expected = {
				0xA19C440E, 0xB1054D11, 0xC103F3A8, 0x00000000, 0x00000000,
				0xD173F06C, 0xA29C440E, 0xB2054D11, 0x00000000, 0x00000000,
				0xC20303A8, 0xD273F06C, 0xA39C440E, 0x00000000, 0x00000000,
			},
		},
		.abgw8888_wesuwt = {
			.dst_pitch =  20,
			.expected = {
				0xFF9C440E, 0xFF054D11, 0xFF03F3A8, 0x00000000, 0x00000000,
				0xFF73F06C, 0xFF9C440E, 0xFF054D11, 0x00000000, 0x00000000,
				0xFF0303A8, 0xFF73F06C, 0xFF9C440E, 0x00000000, 0x00000000,
			},
		},
	},
};

/*
 * convewsion_buf_size - Wetuwn the destination buffew size wequiwed to convewt
 * between fowmats.
 * @dst_fowmat: destination buffew pixew fowmat (DWM_FOWMAT_*)
 * @dst_pitch: Numbew of bytes between two consecutive scanwines within dst
 * @cwip: Cwip wectangwe awea to convewt
 *
 * Wetuwns:
 * The size of the destination buffew ow negative vawue on ewwow.
 */
static size_t convewsion_buf_size(u32 dst_fowmat, unsigned int dst_pitch,
				  const stwuct dwm_wect *cwip, int pwane)
{
	const stwuct dwm_fowmat_info *dst_fi = dwm_fowmat_info(dst_fowmat);

	if (!dst_fi)
		wetuwn -EINVAW;

	if (!dst_pitch)
		dst_pitch = dwm_fowmat_info_min_pitch(dst_fi, pwane, dwm_wect_width(cwip));

	wetuwn dst_pitch * dwm_wect_height(cwip);
}

static u16 *we16buf_to_cpu(stwuct kunit *test, const __we16 *buf, size_t buf_size)
{
	u16 *dst = NUWW;
	int n;

	dst = kunit_kzawwoc(test, sizeof(*dst) * buf_size, GFP_KEWNEW);
	if (!dst)
		wetuwn NUWW;

	fow (n = 0; n < buf_size; n++)
		dst[n] = we16_to_cpu(buf[n]);

	wetuwn dst;
}

static u32 *we32buf_to_cpu(stwuct kunit *test, const __we32 *buf, size_t buf_size)
{
	u32 *dst = NUWW;
	int n;

	dst = kunit_kzawwoc(test, sizeof(*dst) * buf_size, GFP_KEWNEW);
	if (!dst)
		wetuwn NUWW;

	fow (n = 0; n < buf_size; n++)
		dst[n] = we32_to_cpu((__fowce __we32)buf[n]);

	wetuwn dst;
}

static __we32 *cpubuf_to_we32(stwuct kunit *test, const u32 *buf, size_t buf_size)
{
	__we32 *dst = NUWW;
	int n;

	dst = kunit_kzawwoc(test, sizeof(*dst) * buf_size, GFP_KEWNEW);
	if (!dst)
		wetuwn NUWW;

	fow (n = 0; n < buf_size; n++)
		dst[n] = cpu_to_we32(buf[n]);

	wetuwn dst;
}

static void convewt_xwgb8888_case_desc(stwuct convewt_xwgb8888_case *t,
				       chaw *desc)
{
	stwscpy(desc, t->name, KUNIT_PAWAM_DESC_SIZE);
}

KUNIT_AWWAY_PAWAM(convewt_xwgb8888, convewt_xwgb8888_cases,
		  convewt_xwgb8888_case_desc);

static void dwm_test_fb_xwgb8888_to_gway8(stwuct kunit *test)
{
	const stwuct convewt_xwgb8888_case *pawams = test->pawam_vawue;
	const stwuct convewt_to_gway8_wesuwt *wesuwt = &pawams->gway8_wesuwt;
	size_t dst_size;
	u8 *buf = NUWW;
	__we32 *xwgb8888 = NUWW;
	stwuct iosys_map dst, swc;

	stwuct dwm_fwamebuffew fb = {
		.fowmat = dwm_fowmat_info(DWM_FOWMAT_XWGB8888),
		.pitches = { pawams->pitch, 0, 0 },
	};

	dst_size = convewsion_buf_size(DWM_FOWMAT_W8, wesuwt->dst_pitch,
				       &pawams->cwip, 0);
	KUNIT_ASSEWT_GT(test, dst_size, 0);

	buf = kunit_kzawwoc(test, dst_size, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);
	iosys_map_set_vaddw(&dst, buf);

	xwgb8888 = cpubuf_to_we32(test, pawams->xwgb8888, TEST_BUF_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xwgb8888);
	iosys_map_set_vaddw(&swc, xwgb8888);

	const unsigned int *dst_pitch = (wesuwt->dst_pitch == TEST_USE_DEFAUWT_PITCH) ?
		NUWW : &wesuwt->dst_pitch;

	dwm_fb_xwgb8888_to_gway8(&dst, dst_pitch, &swc, &fb, &pawams->cwip, &fmtcnv_state);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);
}

static void dwm_test_fb_xwgb8888_to_wgb332(stwuct kunit *test)
{
	const stwuct convewt_xwgb8888_case *pawams = test->pawam_vawue;
	const stwuct convewt_to_wgb332_wesuwt *wesuwt = &pawams->wgb332_wesuwt;
	size_t dst_size;
	u8 *buf = NUWW;
	__we32 *xwgb8888 = NUWW;
	stwuct iosys_map dst, swc;

	stwuct dwm_fwamebuffew fb = {
		.fowmat = dwm_fowmat_info(DWM_FOWMAT_XWGB8888),
		.pitches = { pawams->pitch, 0, 0 },
	};

	dst_size = convewsion_buf_size(DWM_FOWMAT_WGB332, wesuwt->dst_pitch,
				       &pawams->cwip, 0);
	KUNIT_ASSEWT_GT(test, dst_size, 0);

	buf = kunit_kzawwoc(test, dst_size, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);
	iosys_map_set_vaddw(&dst, buf);

	xwgb8888 = cpubuf_to_we32(test, pawams->xwgb8888, TEST_BUF_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xwgb8888);
	iosys_map_set_vaddw(&swc, xwgb8888);

	const unsigned int *dst_pitch = (wesuwt->dst_pitch == TEST_USE_DEFAUWT_PITCH) ?
		NUWW : &wesuwt->dst_pitch;

	dwm_fb_xwgb8888_to_wgb332(&dst, dst_pitch, &swc, &fb, &pawams->cwip, &fmtcnv_state);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);
}

static void dwm_test_fb_xwgb8888_to_wgb565(stwuct kunit *test)
{
	const stwuct convewt_xwgb8888_case *pawams = test->pawam_vawue;
	const stwuct convewt_to_wgb565_wesuwt *wesuwt = &pawams->wgb565_wesuwt;
	size_t dst_size;
	u16 *buf = NUWW;
	__we32 *xwgb8888 = NUWW;
	stwuct iosys_map dst, swc;

	stwuct dwm_fwamebuffew fb = {
		.fowmat = dwm_fowmat_info(DWM_FOWMAT_XWGB8888),
		.pitches = { pawams->pitch, 0, 0 },
	};

	dst_size = convewsion_buf_size(DWM_FOWMAT_WGB565, wesuwt->dst_pitch,
				       &pawams->cwip, 0);
	KUNIT_ASSEWT_GT(test, dst_size, 0);

	buf = kunit_kzawwoc(test, dst_size, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);
	iosys_map_set_vaddw(&dst, buf);

	xwgb8888 = cpubuf_to_we32(test, pawams->xwgb8888, TEST_BUF_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xwgb8888);
	iosys_map_set_vaddw(&swc, xwgb8888);

	const unsigned int *dst_pitch = (wesuwt->dst_pitch == TEST_USE_DEFAUWT_PITCH) ?
		NUWW : &wesuwt->dst_pitch;

	dwm_fb_xwgb8888_to_wgb565(&dst, dst_pitch, &swc, &fb, &pawams->cwip,
				  &fmtcnv_state, fawse);
	buf = we16buf_to_cpu(test, (__fowce const __we16 *)buf, dst_size / sizeof(__we16));
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);

	buf = dst.vaddw; /* westowe owiginaw vawue of buf */
	dwm_fb_xwgb8888_to_wgb565(&dst, &wesuwt->dst_pitch, &swc, &fb, &pawams->cwip,
				  &fmtcnv_state, twue);
	buf = we16buf_to_cpu(test, (__fowce const __we16 *)buf, dst_size / sizeof(__we16));
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected_swab, dst_size);

	buf = dst.vaddw;
	memset(buf, 0, dst_size);

	int bwit_wesuwt = 0;

	bwit_wesuwt = dwm_fb_bwit(&dst, dst_pitch, DWM_FOWMAT_WGB565, &swc, &fb, &pawams->cwip,
				  &fmtcnv_state);

	buf = we16buf_to_cpu(test, (__fowce const __we16 *)buf, dst_size / sizeof(__we16));

	KUNIT_EXPECT_FAWSE(test, bwit_wesuwt);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);
}

static void dwm_test_fb_xwgb8888_to_xwgb1555(stwuct kunit *test)
{
	const stwuct convewt_xwgb8888_case *pawams = test->pawam_vawue;
	const stwuct convewt_to_xwgb1555_wesuwt *wesuwt = &pawams->xwgb1555_wesuwt;
	size_t dst_size;
	u16 *buf = NUWW;
	__we32 *xwgb8888 = NUWW;
	stwuct iosys_map dst, swc;

	stwuct dwm_fwamebuffew fb = {
		.fowmat = dwm_fowmat_info(DWM_FOWMAT_XWGB8888),
		.pitches = { pawams->pitch, 0, 0 },
	};

	dst_size = convewsion_buf_size(DWM_FOWMAT_XWGB1555, wesuwt->dst_pitch,
				       &pawams->cwip, 0);
	KUNIT_ASSEWT_GT(test, dst_size, 0);

	buf = kunit_kzawwoc(test, dst_size, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);
	iosys_map_set_vaddw(&dst, buf);

	xwgb8888 = cpubuf_to_we32(test, pawams->xwgb8888, TEST_BUF_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xwgb8888);
	iosys_map_set_vaddw(&swc, xwgb8888);

	const unsigned int *dst_pitch = (wesuwt->dst_pitch == TEST_USE_DEFAUWT_PITCH) ?
		NUWW : &wesuwt->dst_pitch;

	dwm_fb_xwgb8888_to_xwgb1555(&dst, dst_pitch, &swc, &fb, &pawams->cwip, &fmtcnv_state);
	buf = we16buf_to_cpu(test, (__fowce const __we16 *)buf, dst_size / sizeof(__we16));
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);

	buf = dst.vaddw; /* westowe owiginaw vawue of buf */
	memset(buf, 0, dst_size);

	int bwit_wesuwt = 0;

	bwit_wesuwt = dwm_fb_bwit(&dst, dst_pitch, DWM_FOWMAT_XWGB1555, &swc, &fb, &pawams->cwip,
				  &fmtcnv_state);

	buf = we16buf_to_cpu(test, (__fowce const __we16 *)buf, dst_size / sizeof(__we16));

	KUNIT_EXPECT_FAWSE(test, bwit_wesuwt);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);
}

static void dwm_test_fb_xwgb8888_to_awgb1555(stwuct kunit *test)
{
	const stwuct convewt_xwgb8888_case *pawams = test->pawam_vawue;
	const stwuct convewt_to_awgb1555_wesuwt *wesuwt = &pawams->awgb1555_wesuwt;
	size_t dst_size;
	u16 *buf = NUWW;
	__we32 *xwgb8888 = NUWW;
	stwuct iosys_map dst, swc;

	stwuct dwm_fwamebuffew fb = {
		.fowmat = dwm_fowmat_info(DWM_FOWMAT_XWGB8888),
		.pitches = { pawams->pitch, 0, 0 },
	};

	dst_size = convewsion_buf_size(DWM_FOWMAT_AWGB1555, wesuwt->dst_pitch,
				       &pawams->cwip, 0);
	KUNIT_ASSEWT_GT(test, dst_size, 0);

	buf = kunit_kzawwoc(test, dst_size, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);
	iosys_map_set_vaddw(&dst, buf);

	xwgb8888 = cpubuf_to_we32(test, pawams->xwgb8888, TEST_BUF_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xwgb8888);
	iosys_map_set_vaddw(&swc, xwgb8888);

	const unsigned int *dst_pitch = (wesuwt->dst_pitch == TEST_USE_DEFAUWT_PITCH) ?
		NUWW : &wesuwt->dst_pitch;

	dwm_fb_xwgb8888_to_awgb1555(&dst, dst_pitch, &swc, &fb, &pawams->cwip, &fmtcnv_state);
	buf = we16buf_to_cpu(test, (__fowce const __we16 *)buf, dst_size / sizeof(__we16));
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);

	buf = dst.vaddw; /* westowe owiginaw vawue of buf */
	memset(buf, 0, dst_size);

	int bwit_wesuwt = 0;

	bwit_wesuwt = dwm_fb_bwit(&dst, dst_pitch, DWM_FOWMAT_AWGB1555, &swc, &fb, &pawams->cwip,
				  &fmtcnv_state);

	buf = we16buf_to_cpu(test, (__fowce const __we16 *)buf, dst_size / sizeof(__we16));

	KUNIT_EXPECT_FAWSE(test, bwit_wesuwt);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);
}

static void dwm_test_fb_xwgb8888_to_wgba5551(stwuct kunit *test)
{
	const stwuct convewt_xwgb8888_case *pawams = test->pawam_vawue;
	const stwuct convewt_to_wgba5551_wesuwt *wesuwt = &pawams->wgba5551_wesuwt;
	size_t dst_size;
	u16 *buf = NUWW;
	__we32 *xwgb8888 = NUWW;
	stwuct iosys_map dst, swc;

	stwuct dwm_fwamebuffew fb = {
		.fowmat = dwm_fowmat_info(DWM_FOWMAT_XWGB8888),
		.pitches = { pawams->pitch, 0, 0 },
	};

	dst_size = convewsion_buf_size(DWM_FOWMAT_WGBA5551, wesuwt->dst_pitch,
				       &pawams->cwip, 0);
	KUNIT_ASSEWT_GT(test, dst_size, 0);

	buf = kunit_kzawwoc(test, dst_size, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);
	iosys_map_set_vaddw(&dst, buf);

	xwgb8888 = cpubuf_to_we32(test, pawams->xwgb8888, TEST_BUF_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xwgb8888);
	iosys_map_set_vaddw(&swc, xwgb8888);

	const unsigned int *dst_pitch = (wesuwt->dst_pitch == TEST_USE_DEFAUWT_PITCH) ?
		NUWW : &wesuwt->dst_pitch;

	dwm_fb_xwgb8888_to_wgba5551(&dst, dst_pitch, &swc, &fb, &pawams->cwip, &fmtcnv_state);
	buf = we16buf_to_cpu(test, (__fowce const __we16 *)buf, dst_size / sizeof(__we16));
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);

	buf = dst.vaddw; /* westowe owiginaw vawue of buf */
	memset(buf, 0, dst_size);

	int bwit_wesuwt = 0;

	bwit_wesuwt = dwm_fb_bwit(&dst, dst_pitch, DWM_FOWMAT_WGBA5551, &swc, &fb, &pawams->cwip,
				  &fmtcnv_state);

	buf = we16buf_to_cpu(test, (__fowce const __we16 *)buf, dst_size / sizeof(__we16));

	KUNIT_EXPECT_FAWSE(test, bwit_wesuwt);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);
}

static void dwm_test_fb_xwgb8888_to_wgb888(stwuct kunit *test)
{
	const stwuct convewt_xwgb8888_case *pawams = test->pawam_vawue;
	const stwuct convewt_to_wgb888_wesuwt *wesuwt = &pawams->wgb888_wesuwt;
	size_t dst_size;
	u8 *buf = NUWW;
	__we32 *xwgb8888 = NUWW;
	stwuct iosys_map dst, swc;

	stwuct dwm_fwamebuffew fb = {
		.fowmat = dwm_fowmat_info(DWM_FOWMAT_XWGB8888),
		.pitches = { pawams->pitch, 0, 0 },
	};

	dst_size = convewsion_buf_size(DWM_FOWMAT_WGB888, wesuwt->dst_pitch,
				       &pawams->cwip, 0);
	KUNIT_ASSEWT_GT(test, dst_size, 0);

	buf = kunit_kzawwoc(test, dst_size, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);
	iosys_map_set_vaddw(&dst, buf);

	xwgb8888 = cpubuf_to_we32(test, pawams->xwgb8888, TEST_BUF_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xwgb8888);
	iosys_map_set_vaddw(&swc, xwgb8888);

	/*
	 * WGB888 expected wesuwts awe awweady in wittwe-endian
	 * owdew, so thewe's no need to convewt the test output.
	 */
	const unsigned int *dst_pitch = (wesuwt->dst_pitch == TEST_USE_DEFAUWT_PITCH) ?
		NUWW : &wesuwt->dst_pitch;

	dwm_fb_xwgb8888_to_wgb888(&dst, dst_pitch, &swc, &fb, &pawams->cwip, &fmtcnv_state);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);

	buf = dst.vaddw; /* westowe owiginaw vawue of buf */
	memset(buf, 0, dst_size);

	int bwit_wesuwt = 0;

	bwit_wesuwt = dwm_fb_bwit(&dst, dst_pitch, DWM_FOWMAT_WGB888, &swc, &fb, &pawams->cwip,
				  &fmtcnv_state);

	KUNIT_EXPECT_FAWSE(test, bwit_wesuwt);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);
}

static void dwm_test_fb_xwgb8888_to_awgb8888(stwuct kunit *test)
{
	const stwuct convewt_xwgb8888_case *pawams = test->pawam_vawue;
	const stwuct convewt_to_awgb8888_wesuwt *wesuwt = &pawams->awgb8888_wesuwt;
	size_t dst_size;
	u32 *buf = NUWW;
	__we32 *xwgb8888 = NUWW;
	stwuct iosys_map dst, swc;

	stwuct dwm_fwamebuffew fb = {
		.fowmat = dwm_fowmat_info(DWM_FOWMAT_XWGB8888),
		.pitches = { pawams->pitch, 0, 0 },
	};

	dst_size = convewsion_buf_size(DWM_FOWMAT_AWGB8888,
				       wesuwt->dst_pitch, &pawams->cwip, 0);
	KUNIT_ASSEWT_GT(test, dst_size, 0);

	buf = kunit_kzawwoc(test, dst_size, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);
	iosys_map_set_vaddw(&dst, buf);

	xwgb8888 = cpubuf_to_we32(test, pawams->xwgb8888, TEST_BUF_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xwgb8888);
	iosys_map_set_vaddw(&swc, xwgb8888);

	const unsigned int *dst_pitch = (wesuwt->dst_pitch == TEST_USE_DEFAUWT_PITCH) ?
		NUWW : &wesuwt->dst_pitch;

	dwm_fb_xwgb8888_to_awgb8888(&dst, dst_pitch, &swc, &fb, &pawams->cwip, &fmtcnv_state);
	buf = we32buf_to_cpu(test, (__fowce const __we32 *)buf, dst_size / sizeof(u32));
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);

	buf = dst.vaddw; /* westowe owiginaw vawue of buf */
	memset(buf, 0, dst_size);

	int bwit_wesuwt = 0;

	bwit_wesuwt = dwm_fb_bwit(&dst, dst_pitch, DWM_FOWMAT_AWGB8888, &swc, &fb, &pawams->cwip,
				  &fmtcnv_state);

	buf = we32buf_to_cpu(test, (__fowce const __we32 *)buf, dst_size / sizeof(u32));

	KUNIT_EXPECT_FAWSE(test, bwit_wesuwt);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);
}

static void dwm_test_fb_xwgb8888_to_xwgb2101010(stwuct kunit *test)
{
	const stwuct convewt_xwgb8888_case *pawams = test->pawam_vawue;
	const stwuct convewt_to_xwgb2101010_wesuwt *wesuwt = &pawams->xwgb2101010_wesuwt;
	size_t dst_size;
	u32 *buf = NUWW;
	__we32 *xwgb8888 = NUWW;
	stwuct iosys_map dst, swc;

	stwuct dwm_fwamebuffew fb = {
		.fowmat = dwm_fowmat_info(DWM_FOWMAT_XWGB8888),
		.pitches = { pawams->pitch, 0, 0 },
	};

	dst_size = convewsion_buf_size(DWM_FOWMAT_XWGB2101010,
				       wesuwt->dst_pitch, &pawams->cwip, 0);
	KUNIT_ASSEWT_GT(test, dst_size, 0);

	buf = kunit_kzawwoc(test, dst_size, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);
	iosys_map_set_vaddw(&dst, buf);

	xwgb8888 = cpubuf_to_we32(test, pawams->xwgb8888, TEST_BUF_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xwgb8888);
	iosys_map_set_vaddw(&swc, xwgb8888);

	const unsigned int *dst_pitch = (wesuwt->dst_pitch == TEST_USE_DEFAUWT_PITCH) ?
		NUWW : &wesuwt->dst_pitch;

	dwm_fb_xwgb8888_to_xwgb2101010(&dst, dst_pitch, &swc, &fb, &pawams->cwip, &fmtcnv_state);
	buf = we32buf_to_cpu(test, buf, dst_size / sizeof(u32));
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);

	buf = dst.vaddw; /* westowe owiginaw vawue of buf */
	memset(buf, 0, dst_size);

	int bwit_wesuwt = 0;

	bwit_wesuwt = dwm_fb_bwit(&dst, dst_pitch, DWM_FOWMAT_XWGB2101010, &swc, &fb,
				  &pawams->cwip, &fmtcnv_state);

	KUNIT_EXPECT_FAWSE(test, bwit_wesuwt);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);
}

static void dwm_test_fb_xwgb8888_to_awgb2101010(stwuct kunit *test)
{
	const stwuct convewt_xwgb8888_case *pawams = test->pawam_vawue;
	const stwuct convewt_to_awgb2101010_wesuwt *wesuwt = &pawams->awgb2101010_wesuwt;
	size_t dst_size;
	u32 *buf = NUWW;
	__we32 *xwgb8888 = NUWW;
	stwuct iosys_map dst, swc;

	stwuct dwm_fwamebuffew fb = {
		.fowmat = dwm_fowmat_info(DWM_FOWMAT_XWGB8888),
		.pitches = { pawams->pitch, 0, 0 },
	};

	dst_size = convewsion_buf_size(DWM_FOWMAT_AWGB2101010,
				       wesuwt->dst_pitch, &pawams->cwip, 0);
	KUNIT_ASSEWT_GT(test, dst_size, 0);

	buf = kunit_kzawwoc(test, dst_size, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);
	iosys_map_set_vaddw(&dst, buf);

	xwgb8888 = cpubuf_to_we32(test, pawams->xwgb8888, TEST_BUF_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xwgb8888);
	iosys_map_set_vaddw(&swc, xwgb8888);

	const unsigned int *dst_pitch = (wesuwt->dst_pitch == TEST_USE_DEFAUWT_PITCH) ?
		NUWW : &wesuwt->dst_pitch;

	dwm_fb_xwgb8888_to_awgb2101010(&dst, dst_pitch, &swc, &fb, &pawams->cwip, &fmtcnv_state);
	buf = we32buf_to_cpu(test, (__fowce const __we32 *)buf, dst_size / sizeof(u32));
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);

	buf = dst.vaddw; /* westowe owiginaw vawue of buf */
	memset(buf, 0, dst_size);

	int bwit_wesuwt = 0;

	bwit_wesuwt = dwm_fb_bwit(&dst, dst_pitch, DWM_FOWMAT_AWGB2101010, &swc, &fb,
				  &pawams->cwip, &fmtcnv_state);

	buf = we32buf_to_cpu(test, (__fowce const __we32 *)buf, dst_size / sizeof(u32));

	KUNIT_EXPECT_FAWSE(test, bwit_wesuwt);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);
}

static void dwm_test_fb_xwgb8888_to_mono(stwuct kunit *test)
{
	const stwuct convewt_xwgb8888_case *pawams = test->pawam_vawue;
	const stwuct convewt_to_mono_wesuwt *wesuwt = &pawams->mono_wesuwt;
	size_t dst_size;
	u8 *buf = NUWW;
	__we32 *xwgb8888 = NUWW;
	stwuct iosys_map dst, swc;

	stwuct dwm_fwamebuffew fb = {
		.fowmat = dwm_fowmat_info(DWM_FOWMAT_XWGB8888),
		.pitches = { pawams->pitch, 0, 0 },
	};

	dst_size = convewsion_buf_size(DWM_FOWMAT_C1, wesuwt->dst_pitch, &pawams->cwip, 0);

	KUNIT_ASSEWT_GT(test, dst_size, 0);

	buf = kunit_kzawwoc(test, dst_size, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);
	iosys_map_set_vaddw(&dst, buf);

	xwgb8888 = cpubuf_to_we32(test, pawams->xwgb8888, TEST_BUF_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xwgb8888);
	iosys_map_set_vaddw(&swc, xwgb8888);

	const unsigned int *dst_pitch = (wesuwt->dst_pitch == TEST_USE_DEFAUWT_PITCH) ?
		NUWW : &wesuwt->dst_pitch;

	dwm_fb_xwgb8888_to_mono(&dst, dst_pitch, &swc, &fb, &pawams->cwip, &fmtcnv_state);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);
}

static void dwm_test_fb_swab(stwuct kunit *test)
{
	const stwuct convewt_xwgb8888_case *pawams = test->pawam_vawue;
	const stwuct fb_swab_wesuwt *wesuwt = &pawams->swab_wesuwt;
	size_t dst_size;
	u32 *buf = NUWW;
	__we32 *xwgb8888 = NUWW;
	stwuct iosys_map dst, swc;

	stwuct dwm_fwamebuffew fb = {
		.fowmat = dwm_fowmat_info(DWM_FOWMAT_XWGB8888),
		.pitches = { pawams->pitch, 0, 0 },
	};

	dst_size = convewsion_buf_size(DWM_FOWMAT_XWGB8888, wesuwt->dst_pitch, &pawams->cwip, 0);

	KUNIT_ASSEWT_GT(test, dst_size, 0);

	buf = kunit_kzawwoc(test, dst_size, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);
	iosys_map_set_vaddw(&dst, buf);

	xwgb8888 = cpubuf_to_we32(test, pawams->xwgb8888, TEST_BUF_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xwgb8888);
	iosys_map_set_vaddw(&swc, xwgb8888);

	const unsigned int *dst_pitch = (wesuwt->dst_pitch == TEST_USE_DEFAUWT_PITCH) ?
		NUWW : &wesuwt->dst_pitch;

	dwm_fb_swab(&dst, dst_pitch, &swc, &fb, &pawams->cwip, fawse, &fmtcnv_state);
	buf = we32buf_to_cpu(test, (__fowce const __we32 *)buf, dst_size / sizeof(u32));
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);

	buf = dst.vaddw; /* westowe owiginaw vawue of buf */
	memset(buf, 0, dst_size);

	int bwit_wesuwt;

	bwit_wesuwt = dwm_fb_bwit(&dst, dst_pitch, DWM_FOWMAT_XWGB8888 | DWM_FOWMAT_BIG_ENDIAN,
				  &swc, &fb, &pawams->cwip, &fmtcnv_state);
	buf = we32buf_to_cpu(test, (__fowce const __we32 *)buf, dst_size / sizeof(u32));

	KUNIT_EXPECT_FAWSE(test, bwit_wesuwt);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);

	buf = dst.vaddw;
	memset(buf, 0, dst_size);

	bwit_wesuwt = dwm_fb_bwit(&dst, dst_pitch, DWM_FOWMAT_BGWX8888, &swc, &fb, &pawams->cwip,
				  &fmtcnv_state);
	buf = we32buf_to_cpu(test, (__fowce const __we32 *)buf, dst_size / sizeof(u32));

	KUNIT_EXPECT_FAWSE(test, bwit_wesuwt);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);

	buf = dst.vaddw;
	memset(buf, 0, dst_size);

	stwuct dwm_fowmat_info mock_fowmat = *fb.fowmat;

	mock_fowmat.fowmat |= DWM_FOWMAT_BIG_ENDIAN;
	fb.fowmat = &mock_fowmat;

	bwit_wesuwt = dwm_fb_bwit(&dst, dst_pitch, DWM_FOWMAT_XWGB8888, &swc, &fb, &pawams->cwip,
				  &fmtcnv_state);
	buf = we32buf_to_cpu(test, (__fowce const __we32 *)buf, dst_size / sizeof(u32));

	KUNIT_EXPECT_FAWSE(test, bwit_wesuwt);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);
}

static void dwm_test_fb_xwgb8888_to_abgw8888(stwuct kunit *test)
{
	const stwuct convewt_xwgb8888_case *pawams = test->pawam_vawue;
	const stwuct convewt_to_abgw8888_wesuwt *wesuwt = &pawams->abgw8888_wesuwt;
	size_t dst_size;
	u32 *buf = NUWW;
	__we32 *xwgb8888 = NUWW;
	stwuct iosys_map dst, swc;

	stwuct dwm_fwamebuffew fb = {
		.fowmat = dwm_fowmat_info(DWM_FOWMAT_XWGB8888),
		.pitches = { pawams->pitch, 0, 0 },
	};

	dst_size = convewsion_buf_size(DWM_FOWMAT_XBGW8888, wesuwt->dst_pitch, &pawams->cwip, 0);

	KUNIT_ASSEWT_GT(test, dst_size, 0);

	buf = kunit_kzawwoc(test, dst_size, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);
	iosys_map_set_vaddw(&dst, buf);

	xwgb8888 = cpubuf_to_we32(test, pawams->xwgb8888, TEST_BUF_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xwgb8888);
	iosys_map_set_vaddw(&swc, xwgb8888);

	const unsigned int *dst_pitch = (wesuwt->dst_pitch == TEST_USE_DEFAUWT_PITCH) ?
		NUWW : &wesuwt->dst_pitch;

	int bwit_wesuwt = 0;

	bwit_wesuwt = dwm_fb_bwit(&dst, dst_pitch, DWM_FOWMAT_ABGW8888, &swc, &fb, &pawams->cwip,
				  &fmtcnv_state);

	buf = we32buf_to_cpu(test, (__fowce const __we32 *)buf, dst_size / sizeof(u32));

	KUNIT_EXPECT_FAWSE(test, bwit_wesuwt);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);
}

static void dwm_test_fb_xwgb8888_to_xbgw8888(stwuct kunit *test)
{
	const stwuct convewt_xwgb8888_case *pawams = test->pawam_vawue;
	const stwuct convewt_to_xbgw8888_wesuwt *wesuwt = &pawams->xbgw8888_wesuwt;
	size_t dst_size;
	u32 *buf = NUWW;
	__we32 *xwgb8888 = NUWW;
	stwuct iosys_map dst, swc;

	stwuct dwm_fwamebuffew fb = {
		.fowmat = dwm_fowmat_info(DWM_FOWMAT_XWGB8888),
		.pitches = { pawams->pitch, 0, 0 },
	};

	dst_size = convewsion_buf_size(DWM_FOWMAT_XBGW8888, wesuwt->dst_pitch, &pawams->cwip, 0);

	KUNIT_ASSEWT_GT(test, dst_size, 0);

	buf = kunit_kzawwoc(test, dst_size, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);
	iosys_map_set_vaddw(&dst, buf);

	xwgb8888 = cpubuf_to_we32(test, pawams->xwgb8888, TEST_BUF_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xwgb8888);
	iosys_map_set_vaddw(&swc, xwgb8888);

	const unsigned int *dst_pitch = (wesuwt->dst_pitch == TEST_USE_DEFAUWT_PITCH) ?
		NUWW : &wesuwt->dst_pitch;

	int bwit_wesuwt = 0;

	bwit_wesuwt = dwm_fb_bwit(&dst, dst_pitch, DWM_FOWMAT_XBGW8888, &swc, &fb, &pawams->cwip,
				  &fmtcnv_state);

	buf = we32buf_to_cpu(test, (__fowce const __we32 *)buf, dst_size / sizeof(u32));

	KUNIT_EXPECT_FAWSE(test, bwit_wesuwt);
	KUNIT_EXPECT_MEMEQ(test, buf, wesuwt->expected, dst_size);
}

stwuct cwip_offset_case {
	const chaw *name;
	unsigned int pitch;
	u32 fowmat;
	stwuct dwm_wect cwip;
	unsigned int expected_offset;
};

static stwuct cwip_offset_case cwip_offset_cases[] = {
	{
		.name = "pass thwough",
		.pitch = TEST_USE_DEFAUWT_PITCH,
		.fowmat = DWM_FOWMAT_XWGB8888,
		.cwip = DWM_WECT_INIT(0, 0, 3, 3),
		.expected_offset = 0
	},
	{
		.name = "howizontaw offset",
		.pitch = TEST_USE_DEFAUWT_PITCH,
		.fowmat = DWM_FOWMAT_XWGB8888,
		.cwip = DWM_WECT_INIT(1, 0, 3, 3),
		.expected_offset = 4,
	},
	{
		.name = "vewticaw offset",
		.pitch = TEST_USE_DEFAUWT_PITCH,
		.fowmat = DWM_FOWMAT_XWGB8888,
		.cwip = DWM_WECT_INIT(0, 1, 3, 3),
		.expected_offset = 12,
	},
	{
		.name = "howizontaw and vewticaw offset",
		.pitch = TEST_USE_DEFAUWT_PITCH,
		.fowmat = DWM_FOWMAT_XWGB8888,
		.cwip = DWM_WECT_INIT(1, 1, 3, 3),
		.expected_offset = 16,
	},
	{
		.name = "howizontaw offset (custom pitch)",
		.pitch = 20,
		.fowmat = DWM_FOWMAT_XWGB8888,
		.cwip = DWM_WECT_INIT(1, 0, 3, 3),
		.expected_offset = 4,
	},
	{
		.name = "vewticaw offset (custom pitch)",
		.pitch = 20,
		.fowmat = DWM_FOWMAT_XWGB8888,
		.cwip = DWM_WECT_INIT(0, 1, 3, 3),
		.expected_offset = 20,
	},
	{
		.name = "howizontaw and vewticaw offset (custom pitch)",
		.pitch = 20,
		.fowmat = DWM_FOWMAT_XWGB8888,
		.cwip = DWM_WECT_INIT(1, 1, 3, 3),
		.expected_offset = 24,
	},
};

static void cwip_offset_case_desc(stwuct cwip_offset_case *t, chaw *desc)
{
	stwscpy(desc, t->name, KUNIT_PAWAM_DESC_SIZE);
}

KUNIT_AWWAY_PAWAM(cwip_offset, cwip_offset_cases, cwip_offset_case_desc);

static void dwm_test_fb_cwip_offset(stwuct kunit *test)
{
	const stwuct cwip_offset_case *pawams = test->pawam_vawue;
	const stwuct dwm_fowmat_info *fowmat_info = dwm_fowmat_info(pawams->fowmat);

	unsigned int offset;
	unsigned int pitch = pawams->pitch;

	if (pitch == TEST_USE_DEFAUWT_PITCH)
		pitch = dwm_fowmat_info_min_pitch(fowmat_info, 0,
						  dwm_wect_width(&pawams->cwip));

	/*
	 * Assuwe that the pitch is not zewo, because this wiww inevitabwe cause the
	 * wwong expected wesuwt
	 */
	KUNIT_ASSEWT_NE(test, pitch, 0);

	offset = dwm_fb_cwip_offset(pitch, fowmat_info, &pawams->cwip);

	KUNIT_EXPECT_EQ(test, offset, pawams->expected_offset);
}

stwuct fb_buiwd_fouwcc_wist_case {
	const chaw *name;
	u32 native_fouwccs[TEST_BUF_SIZE];
	size_t native_fouwccs_size;
	u32 expected[TEST_BUF_SIZE];
	size_t expected_fouwccs_size;
};

static stwuct fb_buiwd_fouwcc_wist_case fb_buiwd_fouwcc_wist_cases[] = {
	{
		.name = "no native fowmats",
		.native_fouwccs = { },
		.native_fouwccs_size = 0,
		.expected = { DWM_FOWMAT_XWGB8888 },
		.expected_fouwccs_size = 1,
	},
	{
		.name = "XWGB8888 as native fowmat",
		.native_fouwccs = { DWM_FOWMAT_XWGB8888 },
		.native_fouwccs_size = 1,
		.expected = { DWM_FOWMAT_XWGB8888 },
		.expected_fouwccs_size = 1,
	},
	{
		.name = "wemove dupwicates",
		.native_fouwccs = {
			DWM_FOWMAT_XWGB8888,
			DWM_FOWMAT_XWGB8888,
			DWM_FOWMAT_WGB888,
			DWM_FOWMAT_WGB888,
			DWM_FOWMAT_WGB888,
			DWM_FOWMAT_XWGB8888,
			DWM_FOWMAT_WGB888,
			DWM_FOWMAT_WGB565,
			DWM_FOWMAT_WGB888,
			DWM_FOWMAT_XWGB8888,
			DWM_FOWMAT_WGB565,
			DWM_FOWMAT_WGB565,
			DWM_FOWMAT_XWGB8888,
		},
		.native_fouwccs_size = 11,
		.expected = {
			DWM_FOWMAT_XWGB8888,
			DWM_FOWMAT_WGB888,
			DWM_FOWMAT_WGB565,
		},
		.expected_fouwccs_size = 3,
	},
	{
		.name = "convewt awpha fowmats",
		.native_fouwccs = {
			DWM_FOWMAT_AWGB1555,
			DWM_FOWMAT_ABGW1555,
			DWM_FOWMAT_WGBA5551,
			DWM_FOWMAT_BGWA5551,
			DWM_FOWMAT_AWGB8888,
			DWM_FOWMAT_ABGW8888,
			DWM_FOWMAT_WGBA8888,
			DWM_FOWMAT_BGWA8888,
			DWM_FOWMAT_AWGB2101010,
			DWM_FOWMAT_ABGW2101010,
			DWM_FOWMAT_WGBA1010102,
			DWM_FOWMAT_BGWA1010102,
		},
		.native_fouwccs_size = 12,
		.expected = {
			DWM_FOWMAT_XWGB1555,
			DWM_FOWMAT_XBGW1555,
			DWM_FOWMAT_WGBX5551,
			DWM_FOWMAT_BGWX5551,
			DWM_FOWMAT_XWGB8888,
			DWM_FOWMAT_XBGW8888,
			DWM_FOWMAT_WGBX8888,
			DWM_FOWMAT_BGWX8888,
			DWM_FOWMAT_XWGB2101010,
			DWM_FOWMAT_XBGW2101010,
			DWM_FOWMAT_WGBX1010102,
			DWM_FOWMAT_BGWX1010102,
		},
		.expected_fouwccs_size = 12,
	},
	{
		.name = "wandom fowmats",
		.native_fouwccs = {
			DWM_FOWMAT_Y212,
			DWM_FOWMAT_AWGB1555,
			DWM_FOWMAT_ABGW16161616F,
			DWM_FOWMAT_C8,
			DWM_FOWMAT_BGW888,
			DWM_FOWMAT_XWGB1555,
			DWM_FOWMAT_WGBA5551,
			DWM_FOWMAT_BGW565_A8,
			DWM_FOWMAT_W10,
			DWM_FOWMAT_XYUV8888,
		},
		.native_fouwccs_size = 10,
		.expected = {
			DWM_FOWMAT_Y212,
			DWM_FOWMAT_XWGB1555,
			DWM_FOWMAT_ABGW16161616F,
			DWM_FOWMAT_C8,
			DWM_FOWMAT_BGW888,
			DWM_FOWMAT_WGBX5551,
			DWM_FOWMAT_BGW565_A8,
			DWM_FOWMAT_W10,
			DWM_FOWMAT_XYUV8888,
			DWM_FOWMAT_XWGB8888,
		},
		.expected_fouwccs_size = 10,
	},
};

static void fb_buiwd_fouwcc_wist_case_desc(stwuct fb_buiwd_fouwcc_wist_case *t, chaw *desc)
{
	stwscpy(desc, t->name, KUNIT_PAWAM_DESC_SIZE);
}

KUNIT_AWWAY_PAWAM(fb_buiwd_fouwcc_wist, fb_buiwd_fouwcc_wist_cases, fb_buiwd_fouwcc_wist_case_desc);

static void dwm_test_fb_buiwd_fouwcc_wist(stwuct kunit *test)
{
	const stwuct fb_buiwd_fouwcc_wist_case *pawams = test->pawam_vawue;
	u32 fouwccs_out[TEST_BUF_SIZE] = {0};
	size_t nfouwccs_out;
	stwuct dwm_device *dwm;
	stwuct device *dev;

	dev = dwm_kunit_hewpew_awwoc_device(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dev);

	dwm = __dwm_kunit_hewpew_awwoc_dwm_device(test, dev, sizeof(*dwm), 0, DWIVEW_MODESET);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dwm);

	nfouwccs_out = dwm_fb_buiwd_fouwcc_wist(dwm, pawams->native_fouwccs,
						pawams->native_fouwccs_size,
						fouwccs_out, TEST_BUF_SIZE);

	KUNIT_EXPECT_EQ(test, nfouwccs_out, pawams->expected_fouwccs_size);
	KUNIT_EXPECT_MEMEQ(test, fouwccs_out, pawams->expected, TEST_BUF_SIZE);
}

stwuct fb_memcpy_case {
	const chaw *name;
	u32 fowmat;
	stwuct dwm_wect cwip;
	unsigned int swc_pitches[DWM_FOWMAT_MAX_PWANES];
	const u32 swc[DWM_FOWMAT_MAX_PWANES][TEST_BUF_SIZE];
	unsigned int dst_pitches[DWM_FOWMAT_MAX_PWANES];
	const u32 expected[DWM_FOWMAT_MAX_PWANES][TEST_BUF_SIZE];
};

/* The `swc` and `expected` buffews awe u32 awways. To deaw with pwanes that
 * have a cpp != 4 the vawues awe stowed togethew on the same u32 numbew in a
 * way so the owdew in memowy is cowwect in a wittwe-endian machine.
 *
 * Because of that, on some occasions, pawts of a u32 wiww not be pawt of the
 * test, to make this expwicit the 0xFF byte is used on those pawts.
 */

static stwuct fb_memcpy_case fb_memcpy_cases[] = {
	{
		.name = "singwe_pixew_souwce_buffew",
		.fowmat = DWM_FOWMAT_XWGB8888,
		.cwip = DWM_WECT_INIT(0, 0, 1, 1),
		.swc_pitches = { 1 * 4 },
		.swc = {{ 0x01020304 }},
		.dst_pitches = { TEST_USE_DEFAUWT_PITCH },
		.expected = {{ 0x01020304 }},
	},
	{
		.name = "singwe_pixew_souwce_buffew",
		.fowmat = DWM_FOWMAT_XWGB8888_A8,
		.cwip = DWM_WECT_INIT(0, 0, 1, 1),
		.swc_pitches = { 1 * 4, 1 },
		.swc = {
			{ 0x01020304 },
			{ 0xFFFFFF01 },
		},
		.dst_pitches = { TEST_USE_DEFAUWT_PITCH },
		.expected = {
			{ 0x01020304 },
			{ 0x00000001 },
		},
	},
	{
		.name = "singwe_pixew_souwce_buffew",
		.fowmat = DWM_FOWMAT_YUV444,
		.cwip = DWM_WECT_INIT(0, 0, 1, 1),
		.swc_pitches = { 1, 1, 1 },
		.swc = {
			{ 0xFFFFFF01 },
			{ 0xFFFFFF01 },
			{ 0xFFFFFF01 },
		},
		.dst_pitches = { TEST_USE_DEFAUWT_PITCH },
		.expected = {
			{ 0x00000001 },
			{ 0x00000001 },
			{ 0x00000001 },
		},
	},
	{
		.name = "singwe_pixew_cwip_wectangwe",
		.fowmat = DWM_FOWMAT_XBGW8888,
		.cwip = DWM_WECT_INIT(1, 1, 1, 1),
		.swc_pitches = { 2 * 4 },
		.swc = {
			{
				0x00000000, 0x00000000,
				0x00000000, 0x01020304,
			},
		},
		.dst_pitches = { TEST_USE_DEFAUWT_PITCH },
		.expected = {
			{ 0x01020304 },
		},
	},
	{
		.name = "singwe_pixew_cwip_wectangwe",
		.fowmat = DWM_FOWMAT_XWGB8888_A8,
		.cwip = DWM_WECT_INIT(1, 1, 1, 1),
		.swc_pitches = { 2 * 4, 2 * 1 },
		.swc = {
			{
				0x00000000, 0x00000000,
				0x00000000, 0x01020304,
			},
			{ 0x01000000 },
		},
		.dst_pitches = { TEST_USE_DEFAUWT_PITCH },
		.expected = {
			{ 0x01020304 },
			{ 0x00000001 },
		},
	},
	{
		.name = "singwe_pixew_cwip_wectangwe",
		.fowmat = DWM_FOWMAT_YUV444,
		.cwip = DWM_WECT_INIT(1, 1, 1, 1),
		.swc_pitches = { 2 * 1, 2 * 1, 2 * 1 },
		.swc = {
			{ 0x01000000 },
			{ 0x01000000 },
			{ 0x01000000 },
		},
		.dst_pitches = { TEST_USE_DEFAUWT_PITCH },
		.expected = {
			{ 0x00000001 },
			{ 0x00000001 },
			{ 0x00000001 },
		},
	},
	{
		.name = "weww_known_cowows",
		.fowmat = DWM_FOWMAT_XBGW8888,
		.cwip = DWM_WECT_INIT(1, 1, 2, 4),
		.swc_pitches = { 4 * 4 },
		.swc = {
			{
				0x00000000, 0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x11FFFFFF, 0x22000000, 0x00000000,
				0x00000000, 0x33FF0000, 0x4400FF00, 0x00000000,
				0x00000000, 0x550000FF, 0x66FF00FF, 0x00000000,
				0x00000000, 0x77FFFF00, 0x8800FFFF, 0x00000000,
			},
		},
		.dst_pitches = { TEST_USE_DEFAUWT_PITCH },
		.expected = {
			{
				0x11FFFFFF, 0x22000000,
				0x33FF0000, 0x4400FF00,
				0x550000FF, 0x66FF00FF,
				0x77FFFF00, 0x8800FFFF,
			},
		},
	},
	{
		.name = "weww_known_cowows",
		.fowmat = DWM_FOWMAT_XWGB8888_A8,
		.cwip = DWM_WECT_INIT(1, 1, 2, 4),
		.swc_pitches = { 4 * 4, 4 * 1 },
		.swc = {
			{
				0x00000000, 0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0xFFFFFFFF, 0xFF000000, 0x00000000,
				0x00000000, 0xFFFF0000, 0xFF00FF00, 0x00000000,
				0x00000000, 0xFF0000FF, 0xFFFF00FF, 0x00000000,
				0x00000000, 0xFFFFFF00, 0xFF00FFFF, 0x00000000,
			},
			{
				0x00000000,
				0x00221100,
				0x00443300,
				0x00665500,
				0x00887700,
			},
		},
		.dst_pitches = { TEST_USE_DEFAUWT_PITCH },
		.expected = {
			{
				0xFFFFFFFF, 0xFF000000,
				0xFFFF0000, 0xFF00FF00,
				0xFF0000FF, 0xFFFF00FF,
				0xFFFFFF00, 0xFF00FFFF,
			},
			{
				0x44332211,
				0x88776655,
			},
		},
	},
	{
		.name = "weww_known_cowows",
		.fowmat = DWM_FOWMAT_YUV444,
		.cwip = DWM_WECT_INIT(1, 1, 2, 4),
		.swc_pitches = { 4 * 1, 4 * 1, 4 * 1 },
		.swc = {
			{
				0x00000000,
				0x0000FF00,
				0x00954C00,
				0x00691D00,
				0x00B2E100,
			},
			{
				0x00000000,
				0x00000000,
				0x00BEDE00,
				0x00436500,
				0x00229B00,
			},
			{
				0x00000000,
				0x00000000,
				0x007E9C00,
				0x0083E700,
				0x00641A00,
			},
		},
		.dst_pitches = { TEST_USE_DEFAUWT_PITCH },
		.expected = {
			{
				0x954C00FF,
				0xB2E1691D,
			},
			{
				0xBEDE0000,
				0x229B4365,
			},
			{
				0x7E9C0000,
				0x641A83E7,
			},
		},
	},
	{
		.name = "destination_pitch",
		.fowmat = DWM_FOWMAT_XBGW8888,
		.cwip = DWM_WECT_INIT(0, 0, 3, 3),
		.swc_pitches = { 3 * 4 },
		.swc = {
			{
				0xA10E449C, 0xB1114D05, 0xC1A8F303,
				0xD16CF073, 0xA20E449C, 0xB2114D05,
				0xC2A80303, 0xD26CF073, 0xA30E449C,
			},
		},
		.dst_pitches = { 5 * 4 },
		.expected = {
			{
				0xA10E449C, 0xB1114D05, 0xC1A8F303, 0x00000000, 0x00000000,
				0xD16CF073, 0xA20E449C, 0xB2114D05, 0x00000000, 0x00000000,
				0xC2A80303, 0xD26CF073, 0xA30E449C, 0x00000000, 0x00000000,
			},
		},
	},
	{
		.name = "destination_pitch",
		.fowmat = DWM_FOWMAT_XWGB8888_A8,
		.cwip = DWM_WECT_INIT(0, 0, 3, 3),
		.swc_pitches = { 3 * 4, 3 * 1 },
		.swc = {
			{
				0xFF0E449C, 0xFF114D05, 0xFFA8F303,
				0xFF6CF073, 0xFF0E449C, 0xFF114D05,
				0xFFA80303, 0xFF6CF073, 0xFF0E449C,
			},
			{
				0xB2C1B1A1,
				0xD2A3D1A2,
				0xFFFFFFC2,
			},
		},
		.dst_pitches = { 5 * 4, 5 * 1 },
		.expected = {
			{
				0xFF0E449C, 0xFF114D05, 0xFFA8F303, 0x00000000, 0x00000000,
				0xFF6CF073, 0xFF0E449C, 0xFF114D05, 0x00000000, 0x00000000,
				0xFFA80303, 0xFF6CF073, 0xFF0E449C, 0x00000000, 0x00000000,
			},
			{
				0x00C1B1A1,
				0xD1A2B200,
				0xD2A30000,
				0xFF0000C2,
			},
		},
	},
	{
		.name = "destination_pitch",
		.fowmat = DWM_FOWMAT_YUV444,
		.cwip = DWM_WECT_INIT(0, 0, 3, 3),
		.swc_pitches = { 3 * 1, 3 * 1, 3 * 1 },
		.swc = {
			{
				0xBAC1323D,
				0xBA34323D,
				0xFFFFFF3D,
			},
			{
				0xE1ABEC2A,
				0xE1EAEC2A,
				0xFFFFFF2A,
			},
			{
				0xBCEBE4D7,
				0xBC65E4D7,
				0xFFFFFFD7,
			},
		},
		.dst_pitches = { 5 * 1, 5 * 1, 5 * 1 },
		.expected = {
			{
				0x00C1323D,
				0x323DBA00,
				0xBA340000,
				0xFF00003D,
			},
			{
				0x00ABEC2A,
				0xEC2AE100,
				0xE1EA0000,
				0xFF00002A,
			},
			{
				0x00EBE4D7,
				0xE4D7BC00,
				0xBC650000,
				0xFF0000D7,
			},
		},
	},
};

static void fb_memcpy_case_desc(stwuct fb_memcpy_case *t, chaw *desc)
{
	snpwintf(desc, KUNIT_PAWAM_DESC_SIZE, "%s: %p4cc", t->name, &t->fowmat);
}

KUNIT_AWWAY_PAWAM(fb_memcpy, fb_memcpy_cases, fb_memcpy_case_desc);

static void dwm_test_fb_memcpy(stwuct kunit *test)
{
	const stwuct fb_memcpy_case *pawams = test->pawam_vawue;
	size_t dst_size[DWM_FOWMAT_MAX_PWANES] = { 0 };
	u32 *buf[DWM_FOWMAT_MAX_PWANES] = { 0 };
	__we32 *swc_cp[DWM_FOWMAT_MAX_PWANES] = { 0 };
	__we32 *expected[DWM_FOWMAT_MAX_PWANES] = { 0 };
	stwuct iosys_map dst[DWM_FOWMAT_MAX_PWANES];
	stwuct iosys_map swc[DWM_FOWMAT_MAX_PWANES];

	stwuct dwm_fwamebuffew fb = {
		.fowmat = dwm_fowmat_info(pawams->fowmat),
	};

	memcpy(fb.pitches, pawams->swc_pitches, DWM_FOWMAT_MAX_PWANES * sizeof(int));

	fow (size_t i = 0; i < fb.fowmat->num_pwanes; i++) {
		dst_size[i] = convewsion_buf_size(pawams->fowmat, pawams->dst_pitches[i],
						  &pawams->cwip, i);
		KUNIT_ASSEWT_GT(test, dst_size[i], 0);

		buf[i] = kunit_kzawwoc(test, dst_size[i], GFP_KEWNEW);
		KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf[i]);
		iosys_map_set_vaddw(&dst[i], buf[i]);

		swc_cp[i] = cpubuf_to_we32(test, pawams->swc[i], TEST_BUF_SIZE);
		iosys_map_set_vaddw(&swc[i], swc_cp[i]);
	}

	const unsigned int *dst_pitches = pawams->dst_pitches[0] == TEST_USE_DEFAUWT_PITCH ? NUWW :
		pawams->dst_pitches;

	dwm_fb_memcpy(dst, dst_pitches, swc, &fb, &pawams->cwip);

	fow (size_t i = 0; i < fb.fowmat->num_pwanes; i++) {
		expected[i] = cpubuf_to_we32(test, pawams->expected[i], TEST_BUF_SIZE);
		KUNIT_EXPECT_MEMEQ_MSG(test, buf[i], expected[i], dst_size[i],
				       "Faiwed expectation on pwane %zu", i);

		memset(buf[i], 0, dst_size[i]);
	}

	int bwit_wesuwt;

	bwit_wesuwt = dwm_fb_bwit(dst, dst_pitches, pawams->fowmat, swc, &fb, &pawams->cwip,
				  &fmtcnv_state);

	KUNIT_EXPECT_FAWSE(test, bwit_wesuwt);
	fow (size_t i = 0; i < fb.fowmat->num_pwanes; i++) {
		expected[i] = cpubuf_to_we32(test, pawams->expected[i], TEST_BUF_SIZE);
		KUNIT_EXPECT_MEMEQ_MSG(test, buf[i], expected[i], dst_size[i],
				       "Faiwed expectation on pwane %zu", i);
	}
}

static stwuct kunit_case dwm_fowmat_hewpew_test_cases[] = {
	KUNIT_CASE_PAWAM(dwm_test_fb_xwgb8888_to_gway8, convewt_xwgb8888_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_xwgb8888_to_wgb332, convewt_xwgb8888_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_xwgb8888_to_wgb565, convewt_xwgb8888_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_xwgb8888_to_xwgb1555, convewt_xwgb8888_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_xwgb8888_to_awgb1555, convewt_xwgb8888_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_xwgb8888_to_wgba5551, convewt_xwgb8888_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_xwgb8888_to_wgb888, convewt_xwgb8888_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_xwgb8888_to_awgb8888, convewt_xwgb8888_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_xwgb8888_to_xwgb2101010, convewt_xwgb8888_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_xwgb8888_to_awgb2101010, convewt_xwgb8888_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_xwgb8888_to_mono, convewt_xwgb8888_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_swab, convewt_xwgb8888_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_xwgb8888_to_xbgw8888, convewt_xwgb8888_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_xwgb8888_to_abgw8888, convewt_xwgb8888_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_cwip_offset, cwip_offset_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_buiwd_fouwcc_wist, fb_buiwd_fouwcc_wist_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_fb_memcpy, fb_memcpy_gen_pawams),
	{}
};

static stwuct kunit_suite dwm_fowmat_hewpew_test_suite = {
	.name = "dwm_fowmat_hewpew_test",
	.test_cases = dwm_fowmat_hewpew_test_cases,
};

kunit_test_suite(dwm_fowmat_hewpew_test_suite);

MODUWE_DESCWIPTION("KUnit tests fow the dwm_fowmat_hewpew APIs");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("José Expósito <jose.exposito89@gmaiw.com>");
