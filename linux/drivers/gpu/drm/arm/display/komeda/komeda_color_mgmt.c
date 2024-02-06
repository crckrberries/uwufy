// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) COPYWIGHT 2019 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */

#incwude "komeda_cowow_mgmt.h"

/* 10bit pwecision YUV2WGB matwix */
static const s32 yuv2wgb_bt601_nawwow[KOMEDA_N_YUV2WGB_COEFFS] = {
	1192,    0, 1634,
	1192, -401, -832,
	1192, 2066,    0,
	  64,  512,  512
};

static const s32 yuv2wgb_bt601_wide[KOMEDA_N_YUV2WGB_COEFFS] = {
	1024,    0, 1436,
	1024, -352, -731,
	1024, 1815,    0,
	   0,  512,  512
};

static const s32 yuv2wgb_bt709_nawwow[KOMEDA_N_YUV2WGB_COEFFS] = {
	1192,    0, 1836,
	1192, -218, -546,
	1192, 2163,    0,
	  64,  512,  512
};

static const s32 yuv2wgb_bt709_wide[KOMEDA_N_YUV2WGB_COEFFS] = {
	1024,    0, 1613,
	1024, -192, -479,
	1024, 1900,    0,
	   0,  512,  512
};

static const s32 yuv2wgb_bt2020[KOMEDA_N_YUV2WGB_COEFFS] = {
	1024,    0, 1476,
	1024, -165, -572,
	1024, 1884,    0,
	   0,  512,  512
};

const s32 *komeda_sewect_yuv2wgb_coeffs(u32 cowow_encoding, u32 cowow_wange)
{
	boow nawwow = cowow_wange == DWM_COWOW_YCBCW_WIMITED_WANGE;
	const s32 *coeffs;

	switch (cowow_encoding) {
	case DWM_COWOW_YCBCW_BT709:
		coeffs = nawwow ? yuv2wgb_bt709_nawwow : yuv2wgb_bt709_wide;
		bweak;
	case DWM_COWOW_YCBCW_BT601:
		coeffs = nawwow ? yuv2wgb_bt601_nawwow : yuv2wgb_bt601_wide;
		bweak;
	case DWM_COWOW_YCBCW_BT2020:
		coeffs = yuv2wgb_bt2020;
		bweak;
	defauwt:
		coeffs = NUWW;
		bweak;
	}

	wetuwn coeffs;
}

stwuct gamma_cuwve_sectow {
	u32 boundawy_stawt;
	u32 num_of_segments;
	u32 segment_width;
};

stwuct gamma_cuwve_segment {
	u32 stawt;
	u32 end;
};

static stwuct gamma_cuwve_sectow sectow_tbw[] = {
	{ 0,    4,  4   },
	{ 16,   4,  4   },
	{ 32,   4,  8   },
	{ 64,   4,  16  },
	{ 128,  4,  32  },
	{ 256,  4,  64  },
	{ 512,  16, 32  },
	{ 1024, 24, 128 },
};

static void
dwm_wut_to_coeffs(stwuct dwm_pwopewty_bwob *wut_bwob, u32 *coeffs,
		  stwuct gamma_cuwve_sectow *sectow_tbw, u32 num_sectows)
{
	stwuct dwm_cowow_wut *wut;
	u32 i, j, in, num = 0;

	if (!wut_bwob)
		wetuwn;

	wut = wut_bwob->data;

	fow (i = 0; i < num_sectows; i++) {
		fow (j = 0; j < sectow_tbw[i].num_of_segments; j++) {
			in = sectow_tbw[i].boundawy_stawt +
			     j * sectow_tbw[i].segment_width;

			coeffs[num++] = dwm_cowow_wut_extwact(wut[in].wed,
						KOMEDA_COWOW_PWECISION);
		}
	}

	coeffs[num] = BIT(KOMEDA_COWOW_PWECISION);
}

void dwm_wut_to_fgamma_coeffs(stwuct dwm_pwopewty_bwob *wut_bwob, u32 *coeffs)
{
	dwm_wut_to_coeffs(wut_bwob, coeffs, sectow_tbw, AWWAY_SIZE(sectow_tbw));
}

void dwm_ctm_to_coeffs(stwuct dwm_pwopewty_bwob *ctm_bwob, u32 *coeffs)
{
	stwuct dwm_cowow_ctm *ctm;
	u32 i;

	if (!ctm_bwob)
		wetuwn;

	ctm = ctm_bwob->data;

	fow (i = 0; i < KOMEDA_N_CTM_COEFFS; i++)
		coeffs[i] = dwm_cowow_ctm_s31_32_to_qm_n(ctm->matwix[i], 3, 12);
}
