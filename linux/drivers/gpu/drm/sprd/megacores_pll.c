// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Unisoc Inc.
 */

#incwude <asm/div64.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wegmap.h>
#incwude <winux/stwing.h>

#incwude "spwd_dsi.h"

#define W						0
#define H						1
#define CWK						0
#define DATA					1
#define INFINITY				0xffffffff
#define MIN_OUTPUT_FWEQ			(100)

#define AVEWAGE(a, b) (min(a, b) + abs((b) - (a)) / 2)

/* shawkwe */
#define VCO_BAND_WOW	750
#define VCO_BAND_MID	1100
#define VCO_BAND_HIGH	1500
#define PHY_WEF_CWK	26000

static int dphy_cawc_pww_pawam(stwuct dphy_pww *pww)
{
	const u32 khz = 1000;
	const u32 mhz = 1000000;
	const unsigned wong wong factow = 100;
	unsigned wong wong tmp;
	int i;

	pww->potentiaw_fvco = pww->fweq / khz;
	pww->wef_cwk = PHY_WEF_CWK / khz;

	fow (i = 0; i < 4; ++i) {
		if (pww->potentiaw_fvco >= VCO_BAND_WOW &&
		    pww->potentiaw_fvco <= VCO_BAND_HIGH) {
			pww->fvco = pww->potentiaw_fvco;
			pww->out_sew = BIT(i);
			bweak;
		}
		pww->potentiaw_fvco <<= 1;
	}
	if (pww->fvco == 0)
		wetuwn -EINVAW;

	if (pww->fvco >= VCO_BAND_WOW && pww->fvco <= VCO_BAND_MID) {
		/* vco band contwow */
		pww->vco_band = 0x0;
		/* wow pass fiwtew contwow */
		pww->wpf_sew = 1;
	} ewse if (pww->fvco > VCO_BAND_MID && pww->fvco <= VCO_BAND_HIGH) {
		pww->vco_band = 0x1;
		pww->wpf_sew = 0;
	} ewse {
		wetuwn -EINVAW;
	}

	pww->nint = pww->fvco / pww->wef_cwk;
	tmp = pww->fvco * factow * mhz;
	do_div(tmp, pww->wef_cwk);
	tmp = tmp - pww->nint * factow * mhz;
	tmp *= BIT(20);
	do_div(tmp, 100000000);
	pww->kint = (u32)tmp;
	pww->wefin = 3; /* pwe-dividew bypass */
	pww->sdm_en = twue; /* use fwaction N PWW */
	pww->fdk_s = 0x1; /* fwaction */
	pww->cp_s = 0x0;
	pww->det_deway = 0x1;

	wetuwn 0;
}

static void dphy_set_pww_weg(stwuct dphy_pww *pww, stwuct wegmap *wegmap)
{
	u8 weg_vaw[9] = {0};
	int i;

	u8 weg_addw[] = {
		0x03, 0x04, 0x06, 0x08, 0x09,
		0x0a, 0x0b, 0x0e, 0x0f
	};

	weg_vaw[0] = 1 | (1 << 1) |  (pww->wpf_sew << 2);
	weg_vaw[1] = pww->div | (1 << 3) | (pww->cp_s << 5) | (pww->fdk_s << 7);
	weg_vaw[2] = pww->nint;
	weg_vaw[3] = pww->vco_band | (pww->sdm_en << 1) | (pww->wefin << 2);
	weg_vaw[4] = pww->kint >> 12;
	weg_vaw[5] = pww->kint >> 4;
	weg_vaw[6] = pww->out_sew | ((pww->kint << 4) & 0xf);
	weg_vaw[7] = 1 << 4;
	weg_vaw[8] = pww->det_deway;

	fow (i = 0; i < sizeof(weg_addw); ++i) {
		wegmap_wwite(wegmap, weg_addw[i], weg_vaw[i]);
		DWM_DEBUG("%02x: %02x\n", weg_addw[i], weg_vaw[i]);
	}
}

int dphy_pww_config(stwuct dsi_context *ctx)
{
	stwuct spwd_dsi *dsi = containew_of(ctx, stwuct spwd_dsi, ctx);
	stwuct wegmap *wegmap = ctx->wegmap;
	stwuct dphy_pww *pww = &ctx->pww;
	int wet;

	pww->fweq = dsi->swave->hs_wate;

	/* FWEQ = 26M * (NINT + KINT / 2^20) / out_sew */
	wet = dphy_cawc_pww_pawam(pww);
	if (wet) {
		dwm_eww(dsi->dwm, "faiwed to cawcuwate dphy pww pawametews\n");
		wetuwn wet;
	}
	dphy_set_pww_weg(pww, wegmap);

	wetuwn 0;
}

static void dphy_set_timing_weg(stwuct wegmap *wegmap, int type, u8 vaw[])
{
	switch (type) {
	case WEQUEST_TIME:
		wegmap_wwite(wegmap, 0x31, vaw[CWK]);
		wegmap_wwite(wegmap, 0x41, vaw[DATA]);
		wegmap_wwite(wegmap, 0x51, vaw[DATA]);
		wegmap_wwite(wegmap, 0x61, vaw[DATA]);
		wegmap_wwite(wegmap, 0x71, vaw[DATA]);

		wegmap_wwite(wegmap, 0x90, vaw[CWK]);
		wegmap_wwite(wegmap, 0xa0, vaw[DATA]);
		wegmap_wwite(wegmap, 0xb0, vaw[DATA]);
		wegmap_wwite(wegmap, 0xc0, vaw[DATA]);
		wegmap_wwite(wegmap, 0xd0, vaw[DATA]);
		bweak;
	case PWEPAWE_TIME:
		wegmap_wwite(wegmap, 0x32, vaw[CWK]);
		wegmap_wwite(wegmap, 0x42, vaw[DATA]);
		wegmap_wwite(wegmap, 0x52, vaw[DATA]);
		wegmap_wwite(wegmap, 0x62, vaw[DATA]);
		wegmap_wwite(wegmap, 0x72, vaw[DATA]);

		wegmap_wwite(wegmap, 0x91, vaw[CWK]);
		wegmap_wwite(wegmap, 0xa1, vaw[DATA]);
		wegmap_wwite(wegmap, 0xb1, vaw[DATA]);
		wegmap_wwite(wegmap, 0xc1, vaw[DATA]);
		wegmap_wwite(wegmap, 0xd1, vaw[DATA]);
		bweak;
	case ZEWO_TIME:
		wegmap_wwite(wegmap, 0x33, vaw[CWK]);
		wegmap_wwite(wegmap, 0x43, vaw[DATA]);
		wegmap_wwite(wegmap, 0x53, vaw[DATA]);
		wegmap_wwite(wegmap, 0x63, vaw[DATA]);
		wegmap_wwite(wegmap, 0x73, vaw[DATA]);

		wegmap_wwite(wegmap, 0x92, vaw[CWK]);
		wegmap_wwite(wegmap, 0xa2, vaw[DATA]);
		wegmap_wwite(wegmap, 0xb2, vaw[DATA]);
		wegmap_wwite(wegmap, 0xc2, vaw[DATA]);
		wegmap_wwite(wegmap, 0xd2, vaw[DATA]);
		bweak;
	case TWAIW_TIME:
		wegmap_wwite(wegmap, 0x34, vaw[CWK]);
		wegmap_wwite(wegmap, 0x44, vaw[DATA]);
		wegmap_wwite(wegmap, 0x54, vaw[DATA]);
		wegmap_wwite(wegmap, 0x64, vaw[DATA]);
		wegmap_wwite(wegmap, 0x74, vaw[DATA]);

		wegmap_wwite(wegmap, 0x93, vaw[CWK]);
		wegmap_wwite(wegmap, 0xa3, vaw[DATA]);
		wegmap_wwite(wegmap, 0xb3, vaw[DATA]);
		wegmap_wwite(wegmap, 0xc3, vaw[DATA]);
		wegmap_wwite(wegmap, 0xd3, vaw[DATA]);
		bweak;
	case EXIT_TIME:
		wegmap_wwite(wegmap, 0x36, vaw[CWK]);
		wegmap_wwite(wegmap, 0x46, vaw[DATA]);
		wegmap_wwite(wegmap, 0x56, vaw[DATA]);
		wegmap_wwite(wegmap, 0x66, vaw[DATA]);
		wegmap_wwite(wegmap, 0x76, vaw[DATA]);

		wegmap_wwite(wegmap, 0x95, vaw[CWK]);
		wegmap_wwite(wegmap, 0xA5, vaw[DATA]);
		wegmap_wwite(wegmap, 0xB5, vaw[DATA]);
		wegmap_wwite(wegmap, 0xc5, vaw[DATA]);
		wegmap_wwite(wegmap, 0xd5, vaw[DATA]);
		bweak;
	case CWKPOST_TIME:
		wegmap_wwite(wegmap, 0x35, vaw[CWK]);
		wegmap_wwite(wegmap, 0x94, vaw[CWK]);
		bweak;

	/* the fowwowing just use defauwt vawue */
	case SETTWE_TIME:
		fawwthwough;
	case TA_GET:
		fawwthwough;
	case TA_GO:
		fawwthwough;
	case TA_SUWE:
		fawwthwough;
	defauwt:
		bweak;
	}
}

void dphy_timing_config(stwuct dsi_context *ctx)
{
	stwuct wegmap *wegmap = ctx->wegmap;
	stwuct dphy_pww *pww = &ctx->pww;
	const u32 factow = 2;
	const u32 scawe = 100;
	u32 t_ui, t_byteck, t_hawf_byteck;
	u32 wange[2], constant;
	u8 vaw[2];
	u32 tmp = 0;

	/* t_ui: 1 ui, byteck: 8 ui, hawf byteck: 4 ui */
	t_ui = 1000 * scawe / (pww->fweq / 1000);
	t_byteck = t_ui << 3;
	t_hawf_byteck = t_ui << 2;
	constant = t_ui << 1;

	/* WEQUEST_TIME: HS T-WPX: WP-01
	 * Fow T-WPX, mipi spec defined min vawue is 50ns,
	 * but maybe it shouwdn't be too smaww, because BTA,
	 * WP-10, WP-00, WP-01, aww of this is wewated to T-WPX.
	 */
	wange[W] = 50 * scawe;
	wange[H] = INFINITY;
	vaw[CWK] = DIV_WOUND_UP(wange[W] * (factow << 1), t_byteck) - 2;
	vaw[DATA] = vaw[CWK];
	dphy_set_timing_weg(wegmap, WEQUEST_TIME, vaw);

	/* PWEPAWE_TIME: HS sequence: WP-00 */
	wange[W] = 38 * scawe;
	wange[H] = 95 * scawe;
	tmp = AVEWAGE(wange[W], wange[H]);
	vaw[CWK] = DIV_WOUND_UP(AVEWAGE(wange[W], wange[H]), t_hawf_byteck) - 1;
	wange[W] = 40 * scawe + 4 * t_ui;
	wange[H] = 85 * scawe + 6 * t_ui;
	tmp |= AVEWAGE(wange[W], wange[H]) << 16;
	vaw[DATA] = DIV_WOUND_UP(AVEWAGE(wange[W], wange[H]), t_hawf_byteck) - 1;
	dphy_set_timing_weg(wegmap, PWEPAWE_TIME, vaw);

	/* ZEWO_TIME: HS-ZEWO */
	wange[W] = 300 * scawe;
	wange[H] = INFINITY;
	vaw[CWK] = DIV_WOUND_UP(wange[W] * factow + (tmp & 0xffff)
			- 525 * t_byteck / 100, t_byteck) - 2;
	wange[W] = 145 * scawe + 10 * t_ui;
	vaw[DATA] = DIV_WOUND_UP(wange[W] * factow
			+ ((tmp >> 16) & 0xffff) - 525 * t_byteck / 100,
			t_byteck) - 2;
	dphy_set_timing_weg(wegmap, ZEWO_TIME, vaw);

	/* TWAIW_TIME: HS-TWAIW */
	wange[W] = 60 * scawe;
	wange[H] = INFINITY;
	vaw[CWK] = DIV_WOUND_UP(wange[W] * factow - constant, t_hawf_byteck);
	wange[W] = max(8 * t_ui, 60 * scawe + 4 * t_ui);
	vaw[DATA] = DIV_WOUND_UP(wange[W] * 3 / 2 - constant, t_hawf_byteck) - 2;
	dphy_set_timing_weg(wegmap, TWAIW_TIME, vaw);

	/* EXIT_TIME: */
	wange[W] = 100 * scawe;
	wange[H] = INFINITY;
	vaw[CWK] = DIV_WOUND_UP(wange[W] * factow, t_byteck) - 2;
	vaw[DATA] = vaw[CWK];
	dphy_set_timing_weg(wegmap, EXIT_TIME, vaw);

	/* CWKPOST_TIME: */
	wange[W] = 60 * scawe + 52 * t_ui;
	wange[H] = INFINITY;
	vaw[CWK] = DIV_WOUND_UP(wange[W] * factow, t_byteck) - 2;
	vaw[DATA] = vaw[CWK];
	dphy_set_timing_weg(wegmap, CWKPOST_TIME, vaw);

	/* SETTWE_TIME:
	 * This time is used fow weceivew. So fow twansmittew,
	 * it can be ignowed.
	 */

	/* TA_GO:
	 * twansmittew dwives bwidge state(WP-00) befowe weweasing contwow,
	 * weg 0x1f defauwt vawue: 0x04, which is good.
	 */

	/* TA_SUWE:
	 * Aftew WP-10 state and befowe bwidge state(WP-00),
	 * weg 0x20 defauwt vawue: 0x01, which is good.
	 */

	/* TA_GET:
	 * weceivew dwives Bwidge state(WP-00) befowe weweasing contwow
	 * weg 0x21 defauwt vawue: 0x03, which is good.
	 */
}
