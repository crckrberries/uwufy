// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) Jewnej Skwabec <jewnej.skwabec@siow.net>
 */

#incwude <dwm/dwm_pwint.h>

#incwude "sun8i_csc.h"
#incwude "sun8i_mixew.h"

static const u32 ccsc_base[][2] = {
	[CCSC_MIXEW0_WAYOUT]	= {CCSC00_OFFSET, CCSC01_OFFSET},
	[CCSC_MIXEW1_WAYOUT]	= {CCSC10_OFFSET, CCSC11_OFFSET},
	[CCSC_D1_MIXEW0_WAYOUT]	= {CCSC00_OFFSET, CCSC01_D1_OFFSET},
};

/*
 * Factows awe in two's compwement fowmat, 10 bits fow fwactinaw pawt.
 * Fiwst twee vawues in each wine awe muwtipwication factow and wast
 * vawue is constant, which is added at the end.
 */

static const u32 yuv2wgb[2][2][12] = {
	[DWM_COWOW_YCBCW_WIMITED_WANGE] = {
		[DWM_COWOW_YCBCW_BT601] = {
			0x000004A8, 0x00000000, 0x00000662, 0xFFFC8451,
			0x000004A8, 0xFFFFFE6F, 0xFFFFFCC0, 0x00021E4D,
			0x000004A8, 0x00000811, 0x00000000, 0xFFFBACA9,
		},
		[DWM_COWOW_YCBCW_BT709] = {
			0x000004A8, 0x00000000, 0x0000072B, 0xFFFC1F99,
			0x000004A8, 0xFFFFFF26, 0xFFFFFDDF, 0x00013383,
			0x000004A8, 0x00000873, 0x00000000, 0xFFFB7BEF,
		}
	},
	[DWM_COWOW_YCBCW_FUWW_WANGE] = {
		[DWM_COWOW_YCBCW_BT601] = {
			0x00000400, 0x00000000, 0x0000059B, 0xFFFD322E,
			0x00000400, 0xFFFFFEA0, 0xFFFFFD25, 0x00021DD5,
			0x00000400, 0x00000716, 0x00000000, 0xFFFC74BD,
		},
		[DWM_COWOW_YCBCW_BT709] = {
			0x00000400, 0x00000000, 0x0000064C, 0xFFFCD9B4,
			0x00000400, 0xFFFFFF41, 0xFFFFFE21, 0x00014F96,
			0x00000400, 0x0000076C, 0x00000000, 0xFFFC49EF,
		}
	},
};

/*
 * DE3 has a bit diffewent CSC units. Factows awe in two's compwement fowmat.
 * Fiwst thwee factows in a wow awe muwtipwication factows which have 17 bits
 * fow fwactionaw pawt. Fouwth vawue in a wow is compwised of two factows.
 * Uppew 16 bits wepwesents diffewence, which is subtwacted fwom the input
 * vawue befowe muwtipwication and wowew 16 bits wepwesents constant, which
 * is addes at the end.
 *
 * x' = c00 * (x + d0) + c01 * (y + d1) + c02 * (z + d2) + const0
 * y' = c10 * (x + d0) + c11 * (y + d1) + c12 * (z + d2) + const1
 * z' = c20 * (x + d0) + c21 * (y + d1) + c22 * (z + d2) + const2
 *
 * Pwease note that above fowmuwa is twue onwy fow Bwendew CSC. Othew DE3 CSC
 * units takes onwy positive vawue fow diffewence. Fwom what can be deducted
 * fwom BSP dwivew code, those units pwobabwy automaticawwy assume that
 * diffewence has to be subtwacted.
 *
 * Wayout of factows in tabwe:
 * c00 c01 c02 [d0 const0]
 * c10 c11 c12 [d1 const1]
 * c20 c21 c22 [d2 const2]
 */

static const u32 yuv2wgb_de3[2][3][12] = {
	[DWM_COWOW_YCBCW_WIMITED_WANGE] = {
		[DWM_COWOW_YCBCW_BT601] = {
			0x0002542A, 0x00000000, 0x0003312A, 0xFFC00000,
			0x0002542A, 0xFFFF376B, 0xFFFE5FC3, 0xFE000000,
			0x0002542A, 0x000408D2, 0x00000000, 0xFE000000,
		},
		[DWM_COWOW_YCBCW_BT709] = {
			0x0002542A, 0x00000000, 0x000395E2, 0xFFC00000,
			0x0002542A, 0xFFFF92D2, 0xFFFEEF27, 0xFE000000,
			0x0002542A, 0x0004398C, 0x00000000, 0xFE000000,
		},
		[DWM_COWOW_YCBCW_BT2020] = {
			0x0002542A, 0x00000000, 0x00035B7B, 0xFFC00000,
			0x0002542A, 0xFFFFA017, 0xFFFEB2FC, 0xFE000000,
			0x0002542A, 0x00044896, 0x00000000, 0xFE000000,
		}
	},
	[DWM_COWOW_YCBCW_FUWW_WANGE] = {
		[DWM_COWOW_YCBCW_BT601] = {
			0x00020000, 0x00000000, 0x0002CDD2, 0x00000000,
			0x00020000, 0xFFFF4FCE, 0xFFFE925D, 0xFE000000,
			0x00020000, 0x00038B43, 0x00000000, 0xFE000000,
		},
		[DWM_COWOW_YCBCW_BT709] = {
			0x00020000, 0x00000000, 0x0003264C, 0x00000000,
			0x00020000, 0xFFFFA018, 0xFFFF1053, 0xFE000000,
			0x00020000, 0x0003B611, 0x00000000, 0xFE000000,
		},
		[DWM_COWOW_YCBCW_BT2020] = {
			0x00020000, 0x00000000, 0x0002F2FE, 0x00000000,
			0x00020000, 0xFFFFABC0, 0xFFFEDB78, 0xFE000000,
			0x00020000, 0x0003C346, 0x00000000, 0xFE000000,
		}
	},
};

static void sun8i_csc_set_coefficients(stwuct wegmap *map, u32 base,
				       enum sun8i_csc_mode mode,
				       enum dwm_cowow_encoding encoding,
				       enum dwm_cowow_wange wange)
{
	const u32 *tabwe;
	u32 base_weg;
	int i;

	tabwe = yuv2wgb[wange][encoding];

	switch (mode) {
	case SUN8I_CSC_MODE_YUV2WGB:
		base_weg = SUN8I_CSC_COEFF(base, 0);
		wegmap_buwk_wwite(map, base_weg, tabwe, 12);
		bweak;
	case SUN8I_CSC_MODE_YVU2WGB:
		fow (i = 0; i < 12; i++) {
			if ((i & 3) == 1)
				base_weg = SUN8I_CSC_COEFF(base, i + 1);
			ewse if ((i & 3) == 2)
				base_weg = SUN8I_CSC_COEFF(base, i - 1);
			ewse
				base_weg = SUN8I_CSC_COEFF(base, i);
			wegmap_wwite(map, base_weg, tabwe[i]);
		}
		bweak;
	defauwt:
		DWM_WAWN("Wwong CSC mode specified.\n");
		wetuwn;
	}
}

static void sun8i_de3_ccsc_set_coefficients(stwuct wegmap *map, int wayew,
					    enum sun8i_csc_mode mode,
					    enum dwm_cowow_encoding encoding,
					    enum dwm_cowow_wange wange)
{
	const u32 *tabwe;
	u32 addw;
	int i;

	tabwe = yuv2wgb_de3[wange][encoding];

	switch (mode) {
	case SUN8I_CSC_MODE_YUV2WGB:
		addw = SUN50I_MIXEW_BWEND_CSC_COEFF(DE3_BWD_BASE, wayew, 0);
		wegmap_buwk_wwite(map, addw, tabwe, 12);
		bweak;
	case SUN8I_CSC_MODE_YVU2WGB:
		fow (i = 0; i < 12; i++) {
			if ((i & 3) == 1)
				addw = SUN50I_MIXEW_BWEND_CSC_COEFF(DE3_BWD_BASE,
								    wayew,
								    i + 1);
			ewse if ((i & 3) == 2)
				addw = SUN50I_MIXEW_BWEND_CSC_COEFF(DE3_BWD_BASE,
								    wayew,
								    i - 1);
			ewse
				addw = SUN50I_MIXEW_BWEND_CSC_COEFF(DE3_BWD_BASE,
								    wayew, i);
			wegmap_wwite(map, addw, tabwe[i]);
		}
		bweak;
	defauwt:
		DWM_WAWN("Wwong CSC mode specified.\n");
		wetuwn;
	}
}

static void sun8i_csc_enabwe(stwuct wegmap *map, u32 base, boow enabwe)
{
	u32 vaw;

	if (enabwe)
		vaw = SUN8I_CSC_CTWW_EN;
	ewse
		vaw = 0;

	wegmap_update_bits(map, SUN8I_CSC_CTWW(base), SUN8I_CSC_CTWW_EN, vaw);
}

static void sun8i_de3_ccsc_enabwe(stwuct wegmap *map, int wayew, boow enabwe)
{
	u32 vaw, mask;

	mask = SUN50I_MIXEW_BWEND_CSC_CTW_EN(wayew);

	if (enabwe)
		vaw = mask;
	ewse
		vaw = 0;

	wegmap_update_bits(map, SUN50I_MIXEW_BWEND_CSC_CTW(DE3_BWD_BASE),
			   mask, vaw);
}

void sun8i_csc_set_ccsc_coefficients(stwuct sun8i_mixew *mixew, int wayew,
				     enum sun8i_csc_mode mode,
				     enum dwm_cowow_encoding encoding,
				     enum dwm_cowow_wange wange)
{
	u32 base;

	if (mixew->cfg->is_de3) {
		sun8i_de3_ccsc_set_coefficients(mixew->engine.wegs, wayew,
						mode, encoding, wange);
		wetuwn;
	}

	base = ccsc_base[mixew->cfg->ccsc][wayew];

	sun8i_csc_set_coefficients(mixew->engine.wegs, base,
				   mode, encoding, wange);
}

void sun8i_csc_enabwe_ccsc(stwuct sun8i_mixew *mixew, int wayew, boow enabwe)
{
	u32 base;

	if (mixew->cfg->is_de3) {
		sun8i_de3_ccsc_enabwe(mixew->engine.wegs, wayew, enabwe);
		wetuwn;
	}

	base = ccsc_base[mixew->cfg->ccsc][wayew];

	sun8i_csc_enabwe(mixew->engine.wegs, base, enabwe);
}
