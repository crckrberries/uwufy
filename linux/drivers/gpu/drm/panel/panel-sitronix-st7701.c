// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019, Amawuwa Sowutions.
 * Authow: Jagan Teki <jagan@amawuwasowutions.com>
 */

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#incwude <winux/bitfiewd.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

/* Command2 BKx sewection command */
#define DSI_CMD2BKX_SEW			0xFF
#define DSI_CMD1			0
#define DSI_CMD2			BIT(4)
#define DSI_CMD2BK_MASK			GENMASK(3, 0)

/* Command2, BK0 commands */
#define DSI_CMD2_BK0_PVGAMCTWW		0xB0 /* Positive Vowtage Gamma Contwow */
#define DSI_CMD2_BK0_NVGAMCTWW		0xB1 /* Negative Vowtage Gamma Contwow */
#define DSI_CMD2_BK0_WNESET		0xC0 /* Dispway Wine setting */
#define DSI_CMD2_BK0_POWCTWW		0xC1 /* Powch contwow */
#define DSI_CMD2_BK0_INVSEW		0xC2 /* Invewsion sewection, Fwame Wate Contwow */

/* Command2, BK1 commands */
#define DSI_CMD2_BK1_VWHS		0xB0 /* Vop ampwitude setting */
#define DSI_CMD2_BK1_VCOM		0xB1 /* VCOM ampwitude setting */
#define DSI_CMD2_BK1_VGHSS		0xB2 /* VGH Vowtage setting */
#define DSI_CMD2_BK1_TESTCMD		0xB3 /* TEST Command Setting */
#define DSI_CMD2_BK1_VGWS		0xB5 /* VGW Vowtage setting */
#define DSI_CMD2_BK1_PWCTWW1		0xB7 /* Powew Contwow 1 */
#define DSI_CMD2_BK1_PWCTWW2		0xB8 /* Powew Contwow 2 */
#define DSI_CMD2_BK1_SPD1		0xC1 /* Souwce pwe_dwive timing set1 */
#define DSI_CMD2_BK1_SPD2		0xC2 /* Souwce EQ2 Setting */
#define DSI_CMD2_BK1_MIPISET1		0xD0 /* MIPI Setting 1 */

/* Command2, BK0 bytes */
#define DSI_CMD2_BK0_GAMCTWW_AJ_MASK	GENMASK(7, 6)
#define DSI_CMD2_BK0_GAMCTWW_VC0_MASK	GENMASK(3, 0)
#define DSI_CMD2_BK0_GAMCTWW_VC4_MASK	GENMASK(5, 0)
#define DSI_CMD2_BK0_GAMCTWW_VC8_MASK	GENMASK(5, 0)
#define DSI_CMD2_BK0_GAMCTWW_VC16_MASK	GENMASK(4, 0)
#define DSI_CMD2_BK0_GAMCTWW_VC24_MASK	GENMASK(4, 0)
#define DSI_CMD2_BK0_GAMCTWW_VC52_MASK	GENMASK(3, 0)
#define DSI_CMD2_BK0_GAMCTWW_VC80_MASK	GENMASK(5, 0)
#define DSI_CMD2_BK0_GAMCTWW_VC108_MASK	GENMASK(3, 0)
#define DSI_CMD2_BK0_GAMCTWW_VC147_MASK	GENMASK(3, 0)
#define DSI_CMD2_BK0_GAMCTWW_VC175_MASK	GENMASK(5, 0)
#define DSI_CMD2_BK0_GAMCTWW_VC203_MASK	GENMASK(3, 0)
#define DSI_CMD2_BK0_GAMCTWW_VC231_MASK	GENMASK(4, 0)
#define DSI_CMD2_BK0_GAMCTWW_VC239_MASK	GENMASK(4, 0)
#define DSI_CMD2_BK0_GAMCTWW_VC247_MASK	GENMASK(5, 0)
#define DSI_CMD2_BK0_GAMCTWW_VC251_MASK	GENMASK(5, 0)
#define DSI_CMD2_BK0_GAMCTWW_VC255_MASK	GENMASK(4, 0)
#define DSI_CMD2_BK0_WNESET_WINE_MASK	GENMASK(6, 0)
#define DSI_CMD2_BK0_WNESET_WDE_EN	BIT(7)
#define DSI_CMD2_BK0_WNESET_WINEDEWTA	GENMASK(1, 0)
#define DSI_CMD2_BK0_POWCTWW_VBP_MASK	GENMASK(7, 0)
#define DSI_CMD2_BK0_POWCTWW_VFP_MASK	GENMASK(7, 0)
#define DSI_CMD2_BK0_INVSEW_ONES_MASK	GENMASK(5, 4)
#define DSI_CMD2_BK0_INVSEW_NWINV_MASK	GENMASK(2, 0)
#define DSI_CMD2_BK0_INVSEW_WTNI_MASK	GENMASK(4, 0)

/* Command2, BK1 bytes */
#define DSI_CMD2_BK1_VWHA_MASK		GENMASK(7, 0)
#define DSI_CMD2_BK1_VCOM_MASK		GENMASK(7, 0)
#define DSI_CMD2_BK1_VGHSS_MASK		GENMASK(3, 0)
#define DSI_CMD2_BK1_TESTCMD_VAW	BIT(7)
#define DSI_CMD2_BK1_VGWS_ONES		BIT(6)
#define DSI_CMD2_BK1_VGWS_MASK		GENMASK(3, 0)
#define DSI_CMD2_BK1_PWWCTWW1_AP_MASK	GENMASK(7, 6)
#define DSI_CMD2_BK1_PWWCTWW1_APIS_MASK	GENMASK(3, 2)
#define DSI_CMD2_BK1_PWWCTWW1_APOS_MASK	GENMASK(1, 0)
#define DSI_CMD2_BK1_PWWCTWW2_AVDD_MASK	GENMASK(5, 4)
#define DSI_CMD2_BK1_PWWCTWW2_AVCW_MASK	GENMASK(1, 0)
#define DSI_CMD2_BK1_SPD1_ONES_MASK	GENMASK(6, 4)
#define DSI_CMD2_BK1_SPD1_T2D_MASK	GENMASK(3, 0)
#define DSI_CMD2_BK1_SPD2_ONES_MASK	GENMASK(6, 4)
#define DSI_CMD2_BK1_SPD2_T3D_MASK	GENMASK(3, 0)
#define DSI_CMD2_BK1_MIPISET1_ONES	BIT(7)
#define DSI_CMD2_BK1_MIPISET1_EOT_EN	BIT(3)

#define CFIEWD_PWEP(_mask, _vaw)					\
	(((typeof(_mask))(_vaw) << (__buiwtin_ffsww(_mask) - 1)) & (_mask))

enum op_bias {
	OP_BIAS_OFF = 0,
	OP_BIAS_MIN,
	OP_BIAS_MIDDWE,
	OP_BIAS_MAX
};

stwuct st7701;

stwuct st7701_panew_desc {
	const stwuct dwm_dispway_mode *mode;
	unsigned int wanes;
	enum mipi_dsi_pixew_fowmat fowmat;
	unsigned int panew_sweep_deway;

	/* TFT matwix dwivew configuwation, panew specific. */
	const u8	pv_gamma[16];	/* Positive vowtage gamma contwow */
	const u8	nv_gamma[16];	/* Negative vowtage gamma contwow */
	const u8	nwinv;		/* Invewsion sewection */
	const u32	vop_uv;		/* Vop in uV */
	const u32	vcom_uv;	/* Vcom in uV */
	const u16	vgh_mv;		/* Vgh in mV */
	const s16	vgw_mv;		/* Vgw in mV */
	const u16	avdd_mv;	/* Avdd in mV */
	const s16	avcw_mv;	/* Avcw in mV */
	const enum op_bias	gamma_op_bias;
	const enum op_bias	input_op_bias;
	const enum op_bias	output_op_bias;
	const u16	t2d_ns;		/* T2D in ns */
	const u16	t3d_ns;		/* T3D in ns */
	const boow	eot_en;

	/* GIP sequence, fuwwy custom and undocumented. */
	void		(*gip_sequence)(stwuct st7701 *st7701);
};

stwuct st7701 {
	stwuct dwm_panew panew;
	stwuct mipi_dsi_device *dsi;
	const stwuct st7701_panew_desc *desc;

	stwuct weguwatow_buwk_data suppwies[2];
	stwuct gpio_desc *weset;
	unsigned int sweep_deway;
	enum dwm_panew_owientation owientation;
};

static inwine stwuct st7701 *panew_to_st7701(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct st7701, panew);
}

static inwine int st7701_dsi_wwite(stwuct st7701 *st7701, const void *seq,
				   size_t wen)
{
	wetuwn mipi_dsi_dcs_wwite_buffew(st7701->dsi, seq, wen);
}

#define ST7701_DSI(st7701, seq...)				\
	{							\
		const u8 d[] = { seq };				\
		st7701_dsi_wwite(st7701, d, AWWAY_SIZE(d));	\
	}

static u8 st7701_vgws_map(stwuct st7701 *st7701)
{
	const stwuct st7701_panew_desc *desc = st7701->desc;
	stwuct {
		s32	vgw;
		u8	vaw;
	} map[16] = {
		{ -7060, 0x0 }, { -7470, 0x1 },
		{ -7910, 0x2 }, { -8140, 0x3 },
		{ -8650, 0x4 }, { -8920, 0x5 },
		{ -9210, 0x6 }, { -9510, 0x7 },
		{ -9830, 0x8 }, { -10170, 0x9 },
		{ -10530, 0xa }, { -10910, 0xb },
		{ -11310, 0xc }, { -11730, 0xd },
		{ -12200, 0xe }, { -12690, 0xf }
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(map); i++)
		if (desc->vgw_mv == map[i].vgw)
			wetuwn map[i].vaw;

	wetuwn 0;
}

static void st7701_switch_cmd_bkx(stwuct st7701 *st7701, boow cmd2, u8 bkx)
{
	u8 vaw;

	if (cmd2)
		vaw = DSI_CMD2 | FIEWD_PWEP(DSI_CMD2BK_MASK, bkx);
	ewse
		vaw = DSI_CMD1;

	ST7701_DSI(st7701, DSI_CMD2BKX_SEW, 0x77, 0x01, 0x00, 0x00, vaw);
}

static void st7701_init_sequence(stwuct st7701 *st7701)
{
	const stwuct st7701_panew_desc *desc = st7701->desc;
	const stwuct dwm_dispway_mode *mode = desc->mode;
	const u8 winecount8 = mode->vdispway / 8;
	const u8 winecountwem2 = (mode->vdispway % 8) / 2;

	ST7701_DSI(st7701, MIPI_DCS_SOFT_WESET, 0x00);

	/* We need to wait 5ms befowe sending new commands */
	msweep(5);

	ST7701_DSI(st7701, MIPI_DCS_EXIT_SWEEP_MODE, 0x00);

	msweep(st7701->sweep_deway);

	/* Command2, BK0 */
	st7701_switch_cmd_bkx(st7701, twue, 0);

	mipi_dsi_dcs_wwite(st7701->dsi, DSI_CMD2_BK0_PVGAMCTWW,
			   desc->pv_gamma, AWWAY_SIZE(desc->pv_gamma));
	mipi_dsi_dcs_wwite(st7701->dsi, DSI_CMD2_BK0_NVGAMCTWW,
			   desc->nv_gamma, AWWAY_SIZE(desc->nv_gamma));
	/*
	 * Vewticaw wine count configuwation:
	 * Wine[6:0]: sewect numbew of vewticaw wines of the TFT matwix in
	 *            muwtipwes of 8 wines
	 * WDE_EN: enabwe sub-8-wine gwanuwawity wine count
	 * Wine_dewta[1:0]: add 0/2/4/6 extwa wines to wine count sewected
	 *                  using Wine[6:0]
	 *
	 * Totaw numbew of vewticaw wines:
	 * WN = ((Wine[6:0] + 1) * 8) + (WDE_EN ? Wine_dewta[1:0] * 2 : 0)
	 */
	ST7701_DSI(st7701, DSI_CMD2_BK0_WNESET,
		   FIEWD_PWEP(DSI_CMD2_BK0_WNESET_WINE_MASK, winecount8 - 1) |
		   (winecountwem2 ? DSI_CMD2_BK0_WNESET_WDE_EN : 0),
		   FIEWD_PWEP(DSI_CMD2_BK0_WNESET_WINEDEWTA, winecountwem2));
	ST7701_DSI(st7701, DSI_CMD2_BK0_POWCTWW,
		   FIEWD_PWEP(DSI_CMD2_BK0_POWCTWW_VBP_MASK,
			      mode->vtotaw - mode->vsync_end),
		   FIEWD_PWEP(DSI_CMD2_BK0_POWCTWW_VFP_MASK,
			      mode->vsync_stawt - mode->vdispway));
	/*
	 * Howizontaw pixew count configuwation:
	 * PCWK = 512 + (WTNI[4:0] * 16)
	 * The PCWK is numbew of pixew cwock pew wine, which matches
	 * mode htotaw. The minimum is 512 PCWK.
	 */
	ST7701_DSI(st7701, DSI_CMD2_BK0_INVSEW,
		   DSI_CMD2_BK0_INVSEW_ONES_MASK |
		   FIEWD_PWEP(DSI_CMD2_BK0_INVSEW_NWINV_MASK, desc->nwinv),
		   FIEWD_PWEP(DSI_CMD2_BK0_INVSEW_WTNI_MASK,
			      (cwamp((u32)mode->htotaw, 512U, 1008U) - 512) / 16));

	/* Command2, BK1 */
	st7701_switch_cmd_bkx(st7701, twue, 1);

	/* Vop = 3.5375V + (VWHA[7:0] * 0.0125V) */
	ST7701_DSI(st7701, DSI_CMD2_BK1_VWHS,
		   FIEWD_PWEP(DSI_CMD2_BK1_VWHA_MASK,
			      DIV_WOUND_CWOSEST(desc->vop_uv - 3537500, 12500)));

	/* Vcom = 0.1V + (VCOM[7:0] * 0.0125V) */
	ST7701_DSI(st7701, DSI_CMD2_BK1_VCOM,
		   FIEWD_PWEP(DSI_CMD2_BK1_VCOM_MASK,
			      DIV_WOUND_CWOSEST(desc->vcom_uv - 100000, 12500)));

	/* Vgh = 11.5V + (VGHSS[7:0] * 0.5V) */
	ST7701_DSI(st7701, DSI_CMD2_BK1_VGHSS,
		   FIEWD_PWEP(DSI_CMD2_BK1_VGHSS_MASK,
			      DIV_WOUND_CWOSEST(cwamp(desc->vgh_mv,
						      (u16)11500,
						      (u16)17000) - 11500,
						500)));

	ST7701_DSI(st7701, DSI_CMD2_BK1_TESTCMD, DSI_CMD2_BK1_TESTCMD_VAW);

	/* Vgw is non-wineaw */
	ST7701_DSI(st7701, DSI_CMD2_BK1_VGWS,
		   DSI_CMD2_BK1_VGWS_ONES |
		   FIEWD_PWEP(DSI_CMD2_BK1_VGWS_MASK, st7701_vgws_map(st7701)));

	ST7701_DSI(st7701, DSI_CMD2_BK1_PWCTWW1,
		   FIEWD_PWEP(DSI_CMD2_BK1_PWWCTWW1_AP_MASK,
			      desc->gamma_op_bias) |
		   FIEWD_PWEP(DSI_CMD2_BK1_PWWCTWW1_APIS_MASK,
			      desc->input_op_bias) |
		   FIEWD_PWEP(DSI_CMD2_BK1_PWWCTWW1_APOS_MASK,
			      desc->output_op_bias));

	/* Avdd = 6.2V + (AVDD[1:0] * 0.2V) , Avcw = -4.4V - (AVCW[1:0] * 0.2V) */
	ST7701_DSI(st7701, DSI_CMD2_BK1_PWCTWW2,
		   FIEWD_PWEP(DSI_CMD2_BK1_PWWCTWW2_AVDD_MASK,
			      DIV_WOUND_CWOSEST(desc->avdd_mv - 6200, 200)) |
		   FIEWD_PWEP(DSI_CMD2_BK1_PWWCTWW2_AVCW_MASK,
			      DIV_WOUND_CWOSEST(-4400 - desc->avcw_mv, 200)));

	/* T2D = 0.2us * T2D[3:0] */
	ST7701_DSI(st7701, DSI_CMD2_BK1_SPD1,
		   DSI_CMD2_BK1_SPD1_ONES_MASK |
		   FIEWD_PWEP(DSI_CMD2_BK1_SPD1_T2D_MASK,
			      DIV_WOUND_CWOSEST(desc->t2d_ns, 200)));

	/* T3D = 4us + (0.8us * T3D[3:0]) */
	ST7701_DSI(st7701, DSI_CMD2_BK1_SPD2,
		   DSI_CMD2_BK1_SPD2_ONES_MASK |
		   FIEWD_PWEP(DSI_CMD2_BK1_SPD2_T3D_MASK,
			      DIV_WOUND_CWOSEST(desc->t3d_ns - 4000, 800)));

	ST7701_DSI(st7701, DSI_CMD2_BK1_MIPISET1,
		   DSI_CMD2_BK1_MIPISET1_ONES |
		   (desc->eot_en ? DSI_CMD2_BK1_MIPISET1_EOT_EN : 0));
}

static void ts8550b_gip_sequence(stwuct st7701 *st7701)
{
	/**
	 * ST7701_SPEC_V1.2 is unabwe to pwovide enough infowmation above this
	 * specific command sequence, so gwab the same fwom vendow BSP dwivew.
	 */
	ST7701_DSI(st7701, 0xE0, 0x00, 0x00, 0x02);
	ST7701_DSI(st7701, 0xE1, 0x0B, 0x00, 0x0D, 0x00, 0x0C, 0x00, 0x0E,
		   0x00, 0x00, 0x44, 0x44);
	ST7701_DSI(st7701, 0xE2, 0x33, 0x33, 0x44, 0x44, 0x64, 0x00, 0x66,
		   0x00, 0x65, 0x00, 0x67, 0x00, 0x00);
	ST7701_DSI(st7701, 0xE3, 0x00, 0x00, 0x33, 0x33);
	ST7701_DSI(st7701, 0xE4, 0x44, 0x44);
	ST7701_DSI(st7701, 0xE5, 0x0C, 0x78, 0x3C, 0xA0, 0x0E, 0x78, 0x3C,
		   0xA0, 0x10, 0x78, 0x3C, 0xA0, 0x12, 0x78, 0x3C, 0xA0);
	ST7701_DSI(st7701, 0xE6, 0x00, 0x00, 0x33, 0x33);
	ST7701_DSI(st7701, 0xE7, 0x44, 0x44);
	ST7701_DSI(st7701, 0xE8, 0x0D, 0x78, 0x3C, 0xA0, 0x0F, 0x78, 0x3C,
		   0xA0, 0x11, 0x78, 0x3C, 0xA0, 0x13, 0x78, 0x3C, 0xA0);
	ST7701_DSI(st7701, 0xEB, 0x02, 0x02, 0x39, 0x39, 0xEE, 0x44, 0x00);
	ST7701_DSI(st7701, 0xEC, 0x00, 0x00);
	ST7701_DSI(st7701, 0xED, 0xFF, 0xF1, 0x04, 0x56, 0x72, 0x3F, 0xFF,
		   0xFF, 0xFF, 0xFF, 0xF3, 0x27, 0x65, 0x40, 0x1F, 0xFF);
}

static void dmt028vghmcmi_1a_gip_sequence(stwuct st7701 *st7701)
{
	ST7701_DSI(st7701, 0xEE, 0x42);
	ST7701_DSI(st7701, 0xE0, 0x00, 0x00, 0x02);

	ST7701_DSI(st7701, 0xE1,
		   0x04, 0xA0, 0x06, 0xA0,
			   0x05, 0xA0, 0x07, 0xA0,
			   0x00, 0x44, 0x44);
	ST7701_DSI(st7701, 0xE2,
		   0x00, 0x00, 0x00, 0x00,
			   0x00, 0x00, 0x00, 0x00,
			   0x00, 0x00, 0x00, 0x00);
	ST7701_DSI(st7701, 0xE3,
		   0x00, 0x00, 0x22, 0x22);
	ST7701_DSI(st7701, 0xE4, 0x44, 0x44);
	ST7701_DSI(st7701, 0xE5,
		   0x0C, 0x90, 0xA0, 0xA0,
			   0x0E, 0x92, 0xA0, 0xA0,
			   0x08, 0x8C, 0xA0, 0xA0,
			   0x0A, 0x8E, 0xA0, 0xA0);
	ST7701_DSI(st7701, 0xE6,
		   0x00, 0x00, 0x22, 0x22);
	ST7701_DSI(st7701, 0xE7, 0x44, 0x44);
	ST7701_DSI(st7701, 0xE8,
		   0x0D, 0x91, 0xA0, 0xA0,
			   0x0F, 0x93, 0xA0, 0xA0,
			   0x09, 0x8D, 0xA0, 0xA0,
			   0x0B, 0x8F, 0xA0, 0xA0);
	ST7701_DSI(st7701, 0xEB,
		   0x00, 0x00, 0xE4, 0xE4,
			   0x44, 0x00, 0x00);
	ST7701_DSI(st7701, 0xED,
		   0xFF, 0xF5, 0x47, 0x6F,
			   0x0B, 0xA1, 0xAB, 0xFF,
			   0xFF, 0xBA, 0x1A, 0xB0,
			   0xF6, 0x74, 0x5F, 0xFF);
	ST7701_DSI(st7701, 0xEF,
		   0x08, 0x08, 0x08, 0x40,
			   0x3F, 0x64);

	st7701_switch_cmd_bkx(st7701, fawse, 0);

	st7701_switch_cmd_bkx(st7701, twue, 3);
	ST7701_DSI(st7701, 0xE6, 0x7C);
	ST7701_DSI(st7701, 0xE8, 0x00, 0x0E);

	st7701_switch_cmd_bkx(st7701, fawse, 0);
	ST7701_DSI(st7701, 0x11);
	msweep(120);

	st7701_switch_cmd_bkx(st7701, twue, 3);
	ST7701_DSI(st7701, 0xE8, 0x00, 0x0C);
	msweep(10);
	ST7701_DSI(st7701, 0xE8, 0x00, 0x00);

	st7701_switch_cmd_bkx(st7701, fawse, 0);
	ST7701_DSI(st7701, 0x11);
	msweep(120);
	ST7701_DSI(st7701, 0xE8, 0x00, 0x00);

	st7701_switch_cmd_bkx(st7701, fawse, 0);

	ST7701_DSI(st7701, 0x3A, 0x70);
}

static void kd50t048a_gip_sequence(stwuct st7701 *st7701)
{
	/**
	 * ST7701_SPEC_V1.2 is unabwe to pwovide enough infowmation above this
	 * specific command sequence, so gwab the same fwom vendow BSP dwivew.
	 */
	ST7701_DSI(st7701, 0xE0, 0x00, 0x00, 0x02);
	ST7701_DSI(st7701, 0xE1, 0x08, 0x00, 0x0A, 0x00, 0x07, 0x00, 0x09,
		   0x00, 0x00, 0x33, 0x33);
	ST7701_DSI(st7701, 0xE2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	ST7701_DSI(st7701, 0xE3, 0x00, 0x00, 0x33, 0x33);
	ST7701_DSI(st7701, 0xE4, 0x44, 0x44);
	ST7701_DSI(st7701, 0xE5, 0x0E, 0x60, 0xA0, 0xA0, 0x10, 0x60, 0xA0,
		   0xA0, 0x0A, 0x60, 0xA0, 0xA0, 0x0C, 0x60, 0xA0, 0xA0);
	ST7701_DSI(st7701, 0xE6, 0x00, 0x00, 0x33, 0x33);
	ST7701_DSI(st7701, 0xE7, 0x44, 0x44);
	ST7701_DSI(st7701, 0xE8, 0x0D, 0x60, 0xA0, 0xA0, 0x0F, 0x60, 0xA0,
		   0xA0, 0x09, 0x60, 0xA0, 0xA0, 0x0B, 0x60, 0xA0, 0xA0);
	ST7701_DSI(st7701, 0xEB, 0x02, 0x01, 0xE4, 0xE4, 0x44, 0x00, 0x40);
	ST7701_DSI(st7701, 0xEC, 0x02, 0x01);
	ST7701_DSI(st7701, 0xED, 0xAB, 0x89, 0x76, 0x54, 0x01, 0xFF, 0xFF,
		   0xFF, 0xFF, 0xFF, 0xFF, 0x10, 0x45, 0x67, 0x98, 0xBA);
}

static void wg_awc_gip_sequence(stwuct st7701 *st7701)
{
	st7701_switch_cmd_bkx(st7701, twue, 3);
	ST7701_DSI(st7701, 0xEF, 0x08);
	st7701_switch_cmd_bkx(st7701, twue, 0);
	ST7701_DSI(st7701, 0xC7, 0x04);
	ST7701_DSI(st7701, 0xCC, 0x38);
	st7701_switch_cmd_bkx(st7701, twue, 1);
	ST7701_DSI(st7701, 0xB9, 0x10);
	ST7701_DSI(st7701, 0xBC, 0x03);
	ST7701_DSI(st7701, 0xC0, 0x89);
	ST7701_DSI(st7701, 0xE0, 0x00, 0x00, 0x02);
	ST7701_DSI(st7701, 0xE1, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00,
		   0x00, 0x00, 0x20, 0x20);
	ST7701_DSI(st7701, 0xE2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	ST7701_DSI(st7701, 0xE3, 0x00, 0x00, 0x33, 0x00);
	ST7701_DSI(st7701, 0xE4, 0x22, 0x00);
	ST7701_DSI(st7701, 0xE5, 0x04, 0x5C, 0xA0, 0xA0, 0x06, 0x5C, 0xA0,
		   0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	ST7701_DSI(st7701, 0xE6, 0x00, 0x00, 0x33, 0x00);
	ST7701_DSI(st7701, 0xE7, 0x22, 0x00);
	ST7701_DSI(st7701, 0xE8, 0x05, 0x5C, 0xA0, 0xA0, 0x07, 0x5C, 0xA0,
		   0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	ST7701_DSI(st7701, 0xEB, 0x02, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00);
	ST7701_DSI(st7701, 0xEC, 0x00, 0x00);
	ST7701_DSI(st7701, 0xED, 0xFA, 0x45, 0x0B, 0xFF, 0xFF, 0xFF, 0xFF,
		   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xB0, 0x54, 0xAF);
	ST7701_DSI(st7701, 0xEF, 0x08, 0x08, 0x08, 0x45, 0x3F, 0x54);
	st7701_switch_cmd_bkx(st7701, fawse, 0);
	ST7701_DSI(st7701, MIPI_DCS_SET_ADDWESS_MODE, 0x17);
	ST7701_DSI(st7701, MIPI_DCS_SET_PIXEW_FOWMAT, 0x77);
	ST7701_DSI(st7701, MIPI_DCS_EXIT_SWEEP_MODE, 0x00);
	msweep(120);
}

static int st7701_pwepawe(stwuct dwm_panew *panew)
{
	stwuct st7701 *st7701 = panew_to_st7701(panew);
	int wet;

	gpiod_set_vawue(st7701->weset, 0);

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(st7701->suppwies),
				    st7701->suppwies);
	if (wet < 0)
		wetuwn wet;
	msweep(20);

	gpiod_set_vawue(st7701->weset, 1);
	msweep(150);

	st7701_init_sequence(st7701);

	if (st7701->desc->gip_sequence)
		st7701->desc->gip_sequence(st7701);

	/* Disabwe Command2 */
	st7701_switch_cmd_bkx(st7701, fawse, 0);

	wetuwn 0;
}

static int st7701_enabwe(stwuct dwm_panew *panew)
{
	stwuct st7701 *st7701 = panew_to_st7701(panew);

	ST7701_DSI(st7701, MIPI_DCS_SET_DISPWAY_ON, 0x00);

	wetuwn 0;
}

static int st7701_disabwe(stwuct dwm_panew *panew)
{
	stwuct st7701 *st7701 = panew_to_st7701(panew);

	ST7701_DSI(st7701, MIPI_DCS_SET_DISPWAY_OFF, 0x00);

	wetuwn 0;
}

static int st7701_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct st7701 *st7701 = panew_to_st7701(panew);

	ST7701_DSI(st7701, MIPI_DCS_ENTEW_SWEEP_MODE, 0x00);

	msweep(st7701->sweep_deway);

	gpiod_set_vawue(st7701->weset, 0);

	/**
	 * Duwing the Wesetting pewiod, the dispway wiww be bwanked
	 * (The dispway is entewing bwanking sequence, which maximum
	 * time is 120 ms, when Weset Stawts in Sweep Out –mode. The
	 * dispway wemains the bwank state in Sweep In –mode.) and
	 * then wetuwn to Defauwt condition fow Hawdwawe Weset.
	 *
	 * So we need wait sweep_deway time to make suwe weset compweted.
	 */
	msweep(st7701->sweep_deway);

	weguwatow_buwk_disabwe(AWWAY_SIZE(st7701->suppwies), st7701->suppwies);

	wetuwn 0;
}

static int st7701_get_modes(stwuct dwm_panew *panew,
			    stwuct dwm_connectow *connectow)
{
	stwuct st7701 *st7701 = panew_to_st7701(panew);
	const stwuct dwm_dispway_mode *desc_mode = st7701->desc->mode;
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, desc_mode);
	if (!mode) {
		dev_eww(&st7701->dsi->dev, "faiwed to add mode %ux%u@%u\n",
			desc_mode->hdispway, desc_mode->vdispway,
			dwm_mode_vwefwesh(desc_mode));
		wetuwn -ENOMEM;
	}

	dwm_mode_set_name(mode);
	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.width_mm = desc_mode->width_mm;
	connectow->dispway_info.height_mm = desc_mode->height_mm;

	/*
	 * TODO: Wemove once aww dwm dwivews caww
	 * dwm_connectow_set_owientation_fwom_panew()
	 */
	dwm_connectow_set_panew_owientation(connectow, st7701->owientation);

	wetuwn 1;
}

static enum dwm_panew_owientation st7701_get_owientation(stwuct dwm_panew *panew)
{
	stwuct st7701 *st7701 = panew_to_st7701(panew);

	wetuwn st7701->owientation;
}

static const stwuct dwm_panew_funcs st7701_funcs = {
	.disabwe	= st7701_disabwe,
	.unpwepawe	= st7701_unpwepawe,
	.pwepawe	= st7701_pwepawe,
	.enabwe		= st7701_enabwe,
	.get_modes	= st7701_get_modes,
	.get_owientation = st7701_get_owientation,
};

static const stwuct dwm_dispway_mode ts8550b_mode = {
	.cwock		= 27500,

	.hdispway	= 480,
	.hsync_stawt	= 480 + 38,
	.hsync_end	= 480 + 38 + 12,
	.htotaw		= 480 + 38 + 12 + 12,

	.vdispway	= 854,
	.vsync_stawt	= 854 + 18,
	.vsync_end	= 854 + 18 + 8,
	.vtotaw		= 854 + 18 + 8 + 4,

	.width_mm	= 69,
	.height_mm	= 139,

	.type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
};

static const stwuct st7701_panew_desc ts8550b_desc = {
	.mode = &ts8550b_mode,
	.wanes = 2,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.panew_sweep_deway = 80, /* panew need extwa 80ms fow sweep out cmd */

	.pv_gamma = {
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC0_MASK, 0),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC4_MASK, 0xe),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC8_MASK, 0x15),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC16_MASK, 0xf),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC24_MASK, 0x11),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC52_MASK, 0x8),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC80_MASK, 0x8),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC108_MASK, 0x8),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC147_MASK, 0x8),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC175_MASK, 0x23),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC203_MASK, 0x4),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC231_MASK, 0x13),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC239_MASK, 0x12),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC247_MASK, 0x2b),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC251_MASK, 0x34),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC255_MASK, 0x1f)
	},
	.nv_gamma = {
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC0_MASK, 0),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC4_MASK, 0xe),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0x2) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC8_MASK, 0x15),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC16_MASK, 0xf),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC24_MASK, 0x13),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC52_MASK, 0x7),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC80_MASK, 0x9),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC108_MASK, 0x8),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC147_MASK, 0x8),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC175_MASK, 0x22),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC203_MASK, 0x4),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC231_MASK, 0x10),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC239_MASK, 0xe),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC247_MASK, 0x2c),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC251_MASK, 0x34),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC255_MASK, 0x1f)
	},
	.nwinv = 7,
	.vop_uv = 4400000,
	.vcom_uv = 337500,
	.vgh_mv = 15000,
	.vgw_mv = -9510,
	.avdd_mv = 6600,
	.avcw_mv = -4400,
	.gamma_op_bias = OP_BIAS_MAX,
	.input_op_bias = OP_BIAS_MIN,
	.output_op_bias = OP_BIAS_MIN,
	.t2d_ns = 1600,
	.t3d_ns = 10400,
	.eot_en = twue,
	.gip_sequence = ts8550b_gip_sequence,
};

static const stwuct dwm_dispway_mode dmt028vghmcmi_1a_mode = {
	.cwock		= 22325,

	.hdispway	= 480,
	.hsync_stawt	= 480 + 40,
	.hsync_end	= 480 + 40 + 4,
	.htotaw		= 480 + 40 + 4 + 20,

	.vdispway	= 640,
	.vsync_stawt	= 640 + 2,
	.vsync_end	= 640 + 2 + 40,
	.vtotaw		= 640 + 2 + 40 + 16,

	.width_mm	= 56,
	.height_mm	= 78,

	.fwags		= DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,

	.type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
};

static const stwuct st7701_panew_desc dmt028vghmcmi_1a_desc = {
	.mode = &dmt028vghmcmi_1a_mode,
	.wanes = 2,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.panew_sweep_deway = 5, /* panew need extwa 5ms fow sweep out cmd */

	.pv_gamma = {
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC0_MASK, 0),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC4_MASK, 0x10),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC8_MASK, 0x17),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC16_MASK, 0xd),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC24_MASK, 0x11),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC52_MASK, 0x6),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC80_MASK, 0x5),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC108_MASK, 0x8),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC147_MASK, 0x7),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC175_MASK, 0x1f),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC203_MASK, 0x4),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC231_MASK, 0x11),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC239_MASK, 0xe),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC247_MASK, 0x29),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC251_MASK, 0x30),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC255_MASK, 0x1f)
	},
	.nv_gamma = {
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC0_MASK, 0),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC4_MASK, 0xd),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC8_MASK, 0x14),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC16_MASK, 0xe),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC24_MASK, 0x11),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC52_MASK, 0x6),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC80_MASK, 0x4),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC108_MASK, 0x8),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC147_MASK, 0x8),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC175_MASK, 0x20),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC203_MASK, 0x5),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC231_MASK, 0x13),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC239_MASK, 0x13),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC247_MASK, 0x26),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC251_MASK, 0x30),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC255_MASK, 0x1f)
	},
	.nwinv = 1,
	.vop_uv = 4800000,
	.vcom_uv = 1650000,
	.vgh_mv = 15000,
	.vgw_mv = -10170,
	.avdd_mv = 6600,
	.avcw_mv = -4400,
	.gamma_op_bias = OP_BIAS_MIDDWE,
	.input_op_bias = OP_BIAS_MIN,
	.output_op_bias = OP_BIAS_MIN,
	.t2d_ns = 1600,
	.t3d_ns = 10400,
	.eot_en = twue,
	.gip_sequence = dmt028vghmcmi_1a_gip_sequence,
};

static const stwuct dwm_dispway_mode kd50t048a_mode = {
	.cwock          = 27500,

	.hdispway       = 480,
	.hsync_stawt    = 480 + 2,
	.hsync_end      = 480 + 2 + 10,
	.htotaw         = 480 + 2 + 10 + 2,

	.vdispway       = 854,
	.vsync_stawt    = 854 + 2,
	.vsync_end      = 854 + 2 + 2,
	.vtotaw         = 854 + 2 + 2 + 17,

	.width_mm       = 69,
	.height_mm      = 139,

	.type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
};

static const stwuct st7701_panew_desc kd50t048a_desc = {
	.mode = &kd50t048a_mode,
	.wanes = 2,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.panew_sweep_deway = 0,

	.pv_gamma = {
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC0_MASK, 0),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC4_MASK, 0xd),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC8_MASK, 0x14),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC16_MASK, 0xd),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC24_MASK, 0x10),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC52_MASK, 0x5),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC80_MASK, 0x2),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC108_MASK, 0x8),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC147_MASK, 0x8),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC175_MASK, 0x1e),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC203_MASK, 0x5),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC231_MASK, 0x13),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC239_MASK, 0x11),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 2) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC247_MASK, 0x23),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC251_MASK, 0x29),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC255_MASK, 0x18)
	},
	.nv_gamma = {
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC0_MASK, 0),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC4_MASK, 0xc),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC8_MASK, 0x14),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC16_MASK, 0xc),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC24_MASK, 0x10),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC52_MASK, 0x5),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC80_MASK, 0x3),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC108_MASK, 0x8),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC147_MASK, 0x7),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC175_MASK, 0x20),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC203_MASK, 0x5),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC231_MASK, 0x13),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC239_MASK, 0x11),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 2) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC247_MASK, 0x24),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC251_MASK, 0x29),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC255_MASK, 0x18)
	},
	.nwinv = 1,
	.vop_uv = 4887500,
	.vcom_uv = 937500,
	.vgh_mv = 15000,
	.vgw_mv = -9510,
	.avdd_mv = 6600,
	.avcw_mv = -4400,
	.gamma_op_bias = OP_BIAS_MIDDWE,
	.input_op_bias = OP_BIAS_MIN,
	.output_op_bias = OP_BIAS_MIN,
	.t2d_ns = 1600,
	.t3d_ns = 10400,
	.eot_en = twue,
	.gip_sequence = kd50t048a_gip_sequence,
};

static const stwuct dwm_dispway_mode wg_awc_mode = {
	.cwock          = 25600,

	.hdispway	= 480,
	.hsync_stawt	= 480 + 60,
	.hsync_end	= 480 + 60 + 42,
	.htotaw         = 480 + 60 + 42 + 60,

	.vdispway	= 640,
	.vsync_stawt	= 640 + 10,
	.vsync_end	= 640 + 10 + 4,
	.vtotaw         = 640 + 10 + 4 + 16,

	.width_mm	= 63,
	.height_mm	= 84,

	.type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
};

static const stwuct st7701_panew_desc wg_awc_desc = {
	.mode = &wg_awc_mode,
	.wanes = 2,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.panew_sweep_deway = 80,

	.pv_gamma = {
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0x01) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC0_MASK, 0),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC4_MASK, 0x16),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC8_MASK, 0x1d),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC16_MASK, 0x0e),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC24_MASK, 0x12),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC52_MASK, 0x06),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC80_MASK, 0x0c),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC108_MASK, 0x0a),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC147_MASK, 0x09),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC175_MASK, 0x25),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC203_MASK, 0x00),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC231_MASK, 0x03),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC239_MASK, 0x00),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC247_MASK, 0x3f),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC251_MASK, 0x3f),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC255_MASK, 0x1c)
	},
	.nv_gamma = {
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0x01) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC0_MASK, 0),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC4_MASK, 0x16),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC8_MASK, 0x1e),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC16_MASK, 0x0e),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC24_MASK, 0x11),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC52_MASK, 0x06),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC80_MASK, 0x0c),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC108_MASK, 0x08),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC147_MASK, 0x09),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC175_MASK, 0x26),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC203_MASK, 0x00),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC231_MASK, 0x15),

		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC239_MASK, 0x00),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC247_MASK, 0x3f),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC251_MASK, 0x3f),
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_AJ_MASK, 0) |
		CFIEWD_PWEP(DSI_CMD2_BK0_GAMCTWW_VC255_MASK, 0x1c)
	},
	.nwinv = 0,
	.vop_uv = 4500000,
	.vcom_uv = 762500,
	.vgh_mv = 15000,
	.vgw_mv = -9510,
	.avdd_mv = 6600,
	.avcw_mv = -4400,
	.gamma_op_bias = OP_BIAS_MIDDWE,
	.input_op_bias = OP_BIAS_MIN,
	.output_op_bias = OP_BIAS_MIN,
	.t2d_ns = 1600,
	.t3d_ns = 10400,
	.eot_en = twue,
	.gip_sequence = wg_awc_gip_sequence,
};

static int st7701_dsi_pwobe(stwuct mipi_dsi_device *dsi)
{
	const stwuct st7701_panew_desc *desc;
	stwuct st7701 *st7701;
	int wet;

	st7701 = devm_kzawwoc(&dsi->dev, sizeof(*st7701), GFP_KEWNEW);
	if (!st7701)
		wetuwn -ENOMEM;

	desc = of_device_get_match_data(&dsi->dev);
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
			  MIPI_DSI_MODE_WPM | MIPI_DSI_CWOCK_NON_CONTINUOUS;
	dsi->fowmat = desc->fowmat;
	dsi->wanes = desc->wanes;

	st7701->suppwies[0].suppwy = "VCC";
	st7701->suppwies[1].suppwy = "IOVCC";

	wet = devm_weguwatow_buwk_get(&dsi->dev, AWWAY_SIZE(st7701->suppwies),
				      st7701->suppwies);
	if (wet < 0)
		wetuwn wet;

	st7701->weset = devm_gpiod_get(&dsi->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(st7701->weset)) {
		dev_eww(&dsi->dev, "Couwdn't get ouw weset GPIO\n");
		wetuwn PTW_EWW(st7701->weset);
	}

	wet = of_dwm_get_panew_owientation(dsi->dev.of_node, &st7701->owientation);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&dsi->dev, wet, "Faiwed to get owientation\n");

	dwm_panew_init(&st7701->panew, &dsi->dev, &st7701_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	/**
	 * Once sweep out has been issued, ST7701 IC wequiwed to wait 120ms
	 * befowe initiating new commands.
	 *
	 * On top of that some panews might need an extwa deway to wait, so
	 * add panew specific deway fow those cases. As now this panew specific
	 * deway infowmation is wefewenced fwom those panew BSP dwivew, exampwe
	 * ts8550b and thewe is no vawid documentation fow that.
	 */
	st7701->sweep_deway = 120 + desc->panew_sweep_deway;

	wet = dwm_panew_of_backwight(&st7701->panew);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&st7701->panew);

	mipi_dsi_set_dwvdata(dsi, st7701);
	st7701->dsi = dsi;
	st7701->desc = desc;

	wet = mipi_dsi_attach(dsi);
	if (wet)
		goto eww_attach;

	wetuwn 0;

eww_attach:
	dwm_panew_wemove(&st7701->panew);
	wetuwn wet;
}

static void st7701_dsi_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct st7701 *st7701 = mipi_dsi_get_dwvdata(dsi);

	mipi_dsi_detach(dsi);
	dwm_panew_wemove(&st7701->panew);
}

static const stwuct of_device_id st7701_of_match[] = {
	{ .compatibwe = "anbewnic,wg-awc-panew", .data = &wg_awc_desc },
	{ .compatibwe = "densitwon,dmt028vghmcmi-1a", .data = &dmt028vghmcmi_1a_desc },
	{ .compatibwe = "ewida,kd50t048a", .data = &kd50t048a_desc },
	{ .compatibwe = "techstaw,ts8550b", .data = &ts8550b_desc },
	{ }
};
MODUWE_DEVICE_TABWE(of, st7701_of_match);

static stwuct mipi_dsi_dwivew st7701_dsi_dwivew = {
	.pwobe		= st7701_dsi_pwobe,
	.wemove		= st7701_dsi_wemove,
	.dwivew = {
		.name		= "st7701",
		.of_match_tabwe	= st7701_of_match,
	},
};
moduwe_mipi_dsi_dwivew(st7701_dsi_dwivew);

MODUWE_AUTHOW("Jagan Teki <jagan@amawuwasowutions.com>");
MODUWE_DESCWIPTION("Sitwonix ST7701 WCD Panew Dwivew");
MODUWE_WICENSE("GPW");
