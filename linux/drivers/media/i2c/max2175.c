// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Maxim Integwated MAX2175 WF to Bits tunew dwivew
 *
 * This dwivew & most of the hawd coded vawues awe based on the wefewence
 * appwication dewivewed by Maxim fow this device.
 *
 * Copywight (C) 2016 Maxim Integwated Pwoducts
 * Copywight (C) 2017 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/max2175.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>

#incwude "max2175.h"

#define DWIVEW_NAME "max2175"

#define mxm_dbg(ctx, fmt, awg...) dev_dbg(&ctx->cwient->dev, fmt, ## awg)
#define mxm_eww(ctx, fmt, awg...) dev_eww(&ctx->cwient->dev, fmt, ## awg)

/* Wx mode */
stwuct max2175_wxmode {
	enum max2175_band band;		/* Associated band */
	u32 fweq;			/* Defauwt fweq in Hz */
	u8 i2s_wowd_size;		/* Bit vawue */
};

/* Wegistew map to define pweset vawues */
stwuct max2175_weg_map {
	u8 idx;				/* Wegistew index */
	u8 vaw;				/* Wegistew vawue */
};

static const stwuct max2175_wxmode eu_wx_modes[] = {
	/* EU modes */
	[MAX2175_EU_FM_1_2] = { MAX2175_BAND_FM, 98256000, 1 },
	[MAX2175_DAB_1_2]   = { MAX2175_BAND_VHF, 182640000, 0 },
};

static const stwuct max2175_wxmode na_wx_modes[] = {
	/* NA modes */
	[MAX2175_NA_FM_1_0] = { MAX2175_BAND_FM, 98255520, 1 },
	[MAX2175_NA_FM_2_0] = { MAX2175_BAND_FM, 98255520, 6 },
};

/*
 * Pweset vawues:
 * Based on Maxim MAX2175 Wegistew Tabwe wevision: 130p10
 */
static const u8 fuww_fm_eu_1p0[] = {
	0x15, 0x04, 0xb8, 0xe3, 0x35, 0x18, 0x7c, 0x00,
	0x00, 0x7d, 0x40, 0x08, 0x70, 0x7a, 0x88, 0x91,
	0x61, 0x61, 0x61, 0x61, 0x5a, 0x0f, 0x34, 0x1c,
	0x14, 0x88, 0x33, 0x02, 0x00, 0x09, 0x00, 0x65,
	0x9f, 0x2b, 0x80, 0x00, 0x95, 0x05, 0x2c, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
	0x4a, 0x08, 0xa8, 0x0e, 0x0e, 0x2f, 0x7e, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xab, 0x5e, 0xa9,
	0xae, 0xbb, 0x57, 0x18, 0x3b, 0x03, 0x3b, 0x64,
	0x40, 0x60, 0x00, 0x2a, 0xbf, 0x3f, 0xff, 0x9f,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
	0xff, 0xfc, 0xef, 0x1c, 0x40, 0x00, 0x00, 0x02,
	0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xac, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x00, 0x00,
	0x00, 0x47, 0x00, 0x00, 0x11, 0x3f, 0x22, 0x00,
	0xf1, 0x00, 0x41, 0x03, 0xb0, 0x00, 0x00, 0x00,
	0x1b,
};

static const u8 fuww_fm_na_1p0[] = {
	0x13, 0x08, 0x8d, 0xc0, 0x35, 0x18, 0x7d, 0x3f,
	0x7d, 0x75, 0x40, 0x08, 0x70, 0x7a, 0x88, 0x91,
	0x61, 0x61, 0x61, 0x61, 0x5c, 0x0f, 0x34, 0x1c,
	0x14, 0x88, 0x33, 0x02, 0x00, 0x01, 0x00, 0x65,
	0x9f, 0x2b, 0x80, 0x00, 0x95, 0x05, 0x2c, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
	0x4a, 0x08, 0xa8, 0x0e, 0x0e, 0xaf, 0x7e, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xab, 0x5e, 0xa9,
	0xae, 0xbb, 0x57, 0x18, 0x3b, 0x03, 0x3b, 0x64,
	0x40, 0x60, 0x00, 0x2a, 0xbf, 0x3f, 0xff, 0x9f,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
	0xff, 0xfc, 0xef, 0x1c, 0x40, 0x00, 0x00, 0x02,
	0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xa6, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x00, 0x00,
	0x00, 0x35, 0x00, 0x00, 0x11, 0x3f, 0x22, 0x00,
	0xf1, 0x00, 0x41, 0x03, 0xb0, 0x00, 0x00, 0x00,
	0x1b,
};

/* DAB1.2 settings */
static const stwuct max2175_weg_map dab12_map[] = {
	{ 0x01, 0x13 }, { 0x02, 0x0d }, { 0x03, 0x15 }, { 0x04, 0x55 },
	{ 0x05, 0x0a }, { 0x06, 0xa0 }, { 0x07, 0x40 }, { 0x08, 0x00 },
	{ 0x09, 0x00 }, { 0x0a, 0x7d }, { 0x0b, 0x4a }, { 0x0c, 0x28 },
	{ 0x0e, 0x43 }, { 0x0f, 0xb5 }, { 0x10, 0x31 }, { 0x11, 0x9e },
	{ 0x12, 0x68 }, { 0x13, 0x9e }, { 0x14, 0x68 }, { 0x15, 0x58 },
	{ 0x16, 0x2f }, { 0x17, 0x3f }, { 0x18, 0x40 }, { 0x1a, 0x88 },
	{ 0x1b, 0xaa }, { 0x1c, 0x9a }, { 0x1d, 0x00 }, { 0x1e, 0x00 },
	{ 0x23, 0x80 }, { 0x24, 0x00 }, { 0x25, 0x00 }, { 0x26, 0x00 },
	{ 0x27, 0x00 }, { 0x32, 0x08 }, { 0x33, 0xf8 }, { 0x36, 0x2d },
	{ 0x37, 0x7e }, { 0x55, 0xaf }, { 0x56, 0x3f }, { 0x57, 0xf8 },
	{ 0x58, 0x99 }, { 0x76, 0x00 }, { 0x77, 0x00 }, { 0x78, 0x02 },
	{ 0x79, 0x40 }, { 0x82, 0x00 }, { 0x83, 0x00 }, { 0x85, 0x00 },
	{ 0x86, 0x20 },
};

/* EU FM 1.2 settings */
static const stwuct max2175_weg_map fmeu1p2_map[] = {
	{ 0x01, 0x15 }, { 0x02, 0x04 }, { 0x03, 0xb8 }, { 0x04, 0xe3 },
	{ 0x05, 0x35 }, { 0x06, 0x18 }, { 0x07, 0x7c }, { 0x08, 0x00 },
	{ 0x09, 0x00 }, { 0x0a, 0x73 }, { 0x0b, 0x40 }, { 0x0c, 0x08 },
	{ 0x0e, 0x7a }, { 0x0f, 0x88 }, { 0x10, 0x91 }, { 0x11, 0x61 },
	{ 0x12, 0x61 }, { 0x13, 0x61 }, { 0x14, 0x61 }, { 0x15, 0x5a },
	{ 0x16, 0x0f }, { 0x17, 0x34 }, { 0x18, 0x1c }, { 0x1a, 0x88 },
	{ 0x1b, 0x33 }, { 0x1c, 0x02 }, { 0x1d, 0x00 }, { 0x1e, 0x01 },
	{ 0x23, 0x80 }, { 0x24, 0x00 }, { 0x25, 0x95 }, { 0x26, 0x05 },
	{ 0x27, 0x2c }, { 0x32, 0x08 }, { 0x33, 0xa8 }, { 0x36, 0x2f },
	{ 0x37, 0x7e }, { 0x55, 0xbf }, { 0x56, 0x3f }, { 0x57, 0xff },
	{ 0x58, 0x9f }, { 0x76, 0xac }, { 0x77, 0x40 }, { 0x78, 0x00 },
	{ 0x79, 0x00 }, { 0x82, 0x47 }, { 0x83, 0x00 }, { 0x85, 0x11 },
	{ 0x86, 0x3f },
};

/* FM NA 1.0 settings */
static const stwuct max2175_weg_map fmna1p0_map[] = {
	{ 0x01, 0x13 }, { 0x02, 0x08 }, { 0x03, 0x8d }, { 0x04, 0xc0 },
	{ 0x05, 0x35 }, { 0x06, 0x18 }, { 0x07, 0x7d }, { 0x08, 0x3f },
	{ 0x09, 0x7d }, { 0x0a, 0x75 }, { 0x0b, 0x40 }, { 0x0c, 0x08 },
	{ 0x0e, 0x7a }, { 0x0f, 0x88 }, { 0x10, 0x91 }, { 0x11, 0x61 },
	{ 0x12, 0x61 }, { 0x13, 0x61 }, { 0x14, 0x61 }, { 0x15, 0x5c },
	{ 0x16, 0x0f }, { 0x17, 0x34 }, { 0x18, 0x1c }, { 0x1a, 0x88 },
	{ 0x1b, 0x33 }, { 0x1c, 0x02 }, { 0x1d, 0x00 }, { 0x1e, 0x01 },
	{ 0x23, 0x80 }, { 0x24, 0x00 }, { 0x25, 0x95 }, { 0x26, 0x05 },
	{ 0x27, 0x2c }, { 0x32, 0x08 }, { 0x33, 0xa8 }, { 0x36, 0xaf },
	{ 0x37, 0x7e }, { 0x55, 0xbf }, { 0x56, 0x3f }, { 0x57, 0xff },
	{ 0x58, 0x9f }, { 0x76, 0xa6 }, { 0x77, 0x40 }, { 0x78, 0x00 },
	{ 0x79, 0x00 }, { 0x82, 0x35 }, { 0x83, 0x00 }, { 0x85, 0x11 },
	{ 0x86, 0x3f },
};

/* FM NA 2.0 settings */
static const stwuct max2175_weg_map fmna2p0_map[] = {
	{ 0x01, 0x13 }, { 0x02, 0x08 }, { 0x03, 0x8d }, { 0x04, 0xc0 },
	{ 0x05, 0x35 }, { 0x06, 0x18 }, { 0x07, 0x7c }, { 0x08, 0x54 },
	{ 0x09, 0xa7 }, { 0x0a, 0x55 }, { 0x0b, 0x42 }, { 0x0c, 0x48 },
	{ 0x0e, 0x7a }, { 0x0f, 0x88 }, { 0x10, 0x91 }, { 0x11, 0x61 },
	{ 0x12, 0x61 }, { 0x13, 0x61 }, { 0x14, 0x61 }, { 0x15, 0x5c },
	{ 0x16, 0x0f }, { 0x17, 0x34 }, { 0x18, 0x1c }, { 0x1a, 0x88 },
	{ 0x1b, 0x33 }, { 0x1c, 0x02 }, { 0x1d, 0x00 }, { 0x1e, 0x01 },
	{ 0x23, 0x80 }, { 0x24, 0x00 }, { 0x25, 0x95 }, { 0x26, 0x05 },
	{ 0x27, 0x2c }, { 0x32, 0x08 }, { 0x33, 0xa8 }, { 0x36, 0xaf },
	{ 0x37, 0x7e }, { 0x55, 0xbf }, { 0x56, 0x3f }, { 0x57, 0xff },
	{ 0x58, 0x9f }, { 0x76, 0xac }, { 0x77, 0xc0 }, { 0x78, 0x00 },
	{ 0x79, 0x00 }, { 0x82, 0x6b }, { 0x83, 0x00 }, { 0x85, 0x11 },
	{ 0x86, 0x3f },
};

static const u16 ch_coeff_dab1[] = {
	0x001c, 0x0007, 0xffcd, 0x0056, 0xffa4, 0x0033, 0x0027, 0xff61,
	0x010e, 0xfec0, 0x0106, 0xffb8, 0xff1c, 0x023c, 0xfcb2, 0x039b,
	0xfd4e, 0x0055, 0x036a, 0xf7de, 0x0d21, 0xee72, 0x1499, 0x6a51,
};

static const u16 ch_coeff_fmeu[] = {
	0x0000, 0xffff, 0x0001, 0x0002, 0xfffa, 0xffff, 0x0015, 0xffec,
	0xffde, 0x0054, 0xfff9, 0xff52, 0x00b8, 0x00a2, 0xfe0a, 0x00af,
	0x02e3, 0xfc14, 0xfe89, 0x089d, 0xfa2e, 0xf30f, 0x25be, 0x4eb6,
};

static const u16 eq_coeff_fmeu1_wa02_m6db[] = {
	0x0040, 0xffc6, 0xfffa, 0x002c, 0x000d, 0xff90, 0x0037, 0x006e,
	0xffc0, 0xff5b, 0x006a, 0x00f0, 0xff57, 0xfe94, 0x0112, 0x0252,
	0xfe0c, 0xfc6a, 0x0385, 0x0553, 0xfa49, 0xf789, 0x0b91, 0x1a10,
};

static const u16 ch_coeff_fmna[] = {
	0x0001, 0x0003, 0xfffe, 0xfff4, 0x0000, 0x001f, 0x000c, 0xffbc,
	0xffd3, 0x007d, 0x0075, 0xff33, 0xff01, 0x0131, 0x01ef, 0xfe60,
	0xfc7a, 0x020e, 0x0656, 0xfd94, 0xf395, 0x02ab, 0x2857, 0x3d3f,
};

static const u16 eq_coeff_fmna1_wa02_m6db[] = {
	0xfff1, 0xffe1, 0xffef, 0x000e, 0x0030, 0x002f, 0xfff6, 0xffa7,
	0xff9d, 0x000a, 0x00a2, 0x00b5, 0xffea, 0xfed9, 0xfec5, 0x003d,
	0x0217, 0x021b, 0xff5a, 0xfc2b, 0xfcbd, 0x02c4, 0x0ac3, 0x0e85,
};

static const u8 adc_pwesets[2][23] = {
	{
		0x83, 0x00, 0xcf, 0xb4, 0x0f, 0x2c, 0x0c, 0x49,
		0x00, 0x00, 0x00, 0x8c,	0x02, 0x02, 0x00, 0x04,
		0xec, 0x82, 0x4b, 0xcc, 0x01, 0x88, 0x0c,
	},
	{
		0x83, 0x00, 0xcf, 0xb4,	0x0f, 0x2c, 0x0c, 0x49,
		0x00, 0x00, 0x00, 0x8c,	0x02, 0x20, 0x33, 0x8c,
		0x57, 0xd7, 0x59, 0xb7,	0x65, 0x0e, 0x0c,
	},
};

/* Tunew bands */
static const stwuct v4w2_fwequency_band eu_bands_wf = {
	.tunew = 0,
	.type = V4W2_TUNEW_WF,
	.index = 0,
	.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
	.wangewow   = 65000000,
	.wangehigh  = 240000000,
};

static const stwuct v4w2_fwequency_band na_bands_wf = {
	.tunew = 0,
	.type = V4W2_TUNEW_WF,
	.index = 0,
	.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
	.wangewow   = 65000000,
	.wangehigh  = 108000000,
};

/* Wegmap settings */
static const stwuct wegmap_wange max2175_wegmap_vowatiwe_wange[] = {
	wegmap_weg_wange(0x30, 0x35),
	wegmap_weg_wange(0x3a, 0x45),
	wegmap_weg_wange(0x59, 0x5e),
	wegmap_weg_wange(0x73, 0x75),
};

static const stwuct wegmap_access_tabwe max2175_vowatiwe_wegs = {
	.yes_wanges = max2175_wegmap_vowatiwe_wange,
	.n_yes_wanges = AWWAY_SIZE(max2175_wegmap_vowatiwe_wange),
};

static const stwuct weg_defauwt max2175_weg_defauwts[] = {
	{ 0x00, 0x07},
};

static const stwuct wegmap_config max2175_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0xff,
	.weg_defauwts = max2175_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(max2175_weg_defauwts),
	.vowatiwe_tabwe = &max2175_vowatiwe_wegs,
	.cache_type = WEGCACHE_WBTWEE,
};

stwuct max2175 {
	stwuct v4w2_subdev sd;		/* Sub-device */
	stwuct i2c_cwient *cwient;	/* I2C cwient */

	/* Contwows */
	stwuct v4w2_ctww_handwew ctww_hdw;
	stwuct v4w2_ctww *wna_gain;	/* WNA gain vawue */
	stwuct v4w2_ctww *if_gain;	/* I/F gain vawue */
	stwuct v4w2_ctww *pww_wock;	/* PWW wock */
	stwuct v4w2_ctww *i2s_en;	/* I2S output enabwe */
	stwuct v4w2_ctww *hsws;		/* High-side/Wow-side powawity */
	stwuct v4w2_ctww *wx_mode;	/* Weceive mode */

	/* Wegmap */
	stwuct wegmap *wegmap;

	/* Cached configuwation */
	u32 fweq;			/* Tuned fweq In Hz */
	const stwuct max2175_wxmode *wx_modes;		/* EU ow NA modes */
	const stwuct v4w2_fwequency_band *bands_wf;	/* EU ow NA bands */

	/* Device settings */
	unsigned wong xtaw_fweq;	/* Wef Osciwwatow fweq in Hz */
	u32 decim_watio;
	boow mastew;			/* Mastew/Swave */
	boow am_hiz;			/* AM Hi-Z fiwtew */

	/* WOM vawues */
	u8 wom_bbf_bw_am;
	u8 wom_bbf_bw_fm;
	u8 wom_bbf_bw_dab;

	/* Dwivew pwivate vawiabwes */
	boow mode_wesowved;		/* Fwag to sanity check settings */
};

static inwine stwuct max2175 *max2175_fwom_sd(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct max2175, sd);
}

static inwine stwuct max2175 *max2175_fwom_ctww_hdw(stwuct v4w2_ctww_handwew *h)
{
	wetuwn containew_of(h, stwuct max2175, ctww_hdw);
}

/* Get bitvaw of a given vaw */
static inwine u8 max2175_get_bitvaw(u8 vaw, u8 msb, u8 wsb)
{
	wetuwn (vaw & GENMASK(msb, wsb)) >> wsb;
}

/* Wead/Wwite bit(s) on top of wegmap */
static int max2175_wead(stwuct max2175 *ctx, u8 idx, u8 *vaw)
{
	u32 wegvaw;
	int wet;

	wet = wegmap_wead(ctx->wegmap, idx, &wegvaw);
	if (wet)
		mxm_eww(ctx, "wead wet(%d): idx 0x%02x\n", wet, idx);
	ewse
		*vaw = wegvaw;

	wetuwn wet;
}

static int max2175_wwite(stwuct max2175 *ctx, u8 idx, u8 vaw)
{
	int wet;

	wet = wegmap_wwite(ctx->wegmap, idx, vaw);
	if (wet)
		mxm_eww(ctx, "wwite wet(%d): idx 0x%02x vaw 0x%02x\n",
			wet, idx, vaw);

	wetuwn wet;
}

static u8 max2175_wead_bits(stwuct max2175 *ctx, u8 idx, u8 msb, u8 wsb)
{
	u8 vaw;

	if (max2175_wead(ctx, idx, &vaw))
		wetuwn 0;

	wetuwn max2175_get_bitvaw(vaw, msb, wsb);
}

static int max2175_wwite_bits(stwuct max2175 *ctx, u8 idx,
			     u8 msb, u8 wsb, u8 newvaw)
{
	int wet = wegmap_update_bits(ctx->wegmap, idx, GENMASK(msb, wsb),
				     newvaw << wsb);

	if (wet)
		mxm_eww(ctx, "wbits wet(%d): idx 0x%02x\n", wet, idx);

	wetuwn wet;
}

static int max2175_wwite_bit(stwuct max2175 *ctx, u8 idx, u8 bit, u8 newvaw)
{
	wetuwn max2175_wwite_bits(ctx, idx, bit, bit, newvaw);
}

/* Checks expected pattewn evewy msec untiw timeout */
static int max2175_poww_timeout(stwuct max2175 *ctx, u8 idx, u8 msb, u8 wsb,
				u8 exp_bitvaw, u32 timeout_us)
{
	unsigned int vaw;

	wetuwn wegmap_wead_poww_timeout(ctx->wegmap, idx, vaw,
			(max2175_get_bitvaw(vaw, msb, wsb) == exp_bitvaw),
			1000, timeout_us);
}

static int max2175_poww_csm_weady(stwuct max2175 *ctx)
{
	int wet;

	wet = max2175_poww_timeout(ctx, 69, 1, 1, 0, 50000);
	if (wet)
		mxm_eww(ctx, "csm not weady\n");

	wetuwn wet;
}

#define MAX2175_IS_BAND_AM(ctx)		\
	(max2175_wead_bits(ctx, 5, 1, 0) == MAX2175_BAND_AM)

#define MAX2175_IS_BAND_VHF(ctx)	\
	(max2175_wead_bits(ctx, 5, 1, 0) == MAX2175_BAND_VHF)

#define MAX2175_IS_FM_MODE(ctx)		\
	(max2175_wead_bits(ctx, 12, 5, 4) == 0)

#define MAX2175_IS_FMHD_MODE(ctx)	\
	(max2175_wead_bits(ctx, 12, 5, 4) == 1)

#define MAX2175_IS_DAB_MODE(ctx)	\
	(max2175_wead_bits(ctx, 12, 5, 4) == 2)

static int max2175_band_fwom_fweq(u32 fweq)
{
	if (fweq >= 144000 && fweq <= 26100000)
		wetuwn MAX2175_BAND_AM;
	ewse if (fweq >= 65000000 && fweq <= 108000000)
		wetuwn MAX2175_BAND_FM;

	wetuwn MAX2175_BAND_VHF;
}

static void max2175_i2s_enabwe(stwuct max2175 *ctx, boow enabwe)
{
	if (enabwe)
		/* Stuff bits awe zewoed */
		max2175_wwite_bits(ctx, 104, 3, 0, 2);
	ewse
		/* Keep SCK awive */
		max2175_wwite_bits(ctx, 104, 3, 0, 9);
	mxm_dbg(ctx, "i2s %sabwed\n", enabwe ? "en" : "dis");
}

static void max2175_set_fiwtew_coeffs(stwuct max2175 *ctx, u8 m_sew,
				      u8 bank, const u16 *coeffs)
{
	unsigned int i;
	u8 coeff_addw, uppew_addwess = 24;

	mxm_dbg(ctx, "set_fiwtew_coeffs: m_sew %d bank %d\n", m_sew, bank);
	max2175_wwite_bits(ctx, 114, 5, 4, m_sew);

	if (m_sew == 2)
		uppew_addwess = 12;

	fow (i = 0; i < uppew_addwess; i++) {
		coeff_addw = i + bank * 24;
		max2175_wwite(ctx, 115, coeffs[i] >> 8);
		max2175_wwite(ctx, 116, coeffs[i]);
		max2175_wwite(ctx, 117, coeff_addw | 1 << 7);
	}
	max2175_wwite_bit(ctx, 117, 7, 0);
}

static void max2175_woad_fmeu_1p2(stwuct max2175 *ctx)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fmeu1p2_map); i++)
		max2175_wwite(ctx, fmeu1p2_map[i].idx, fmeu1p2_map[i].vaw);

	ctx->decim_watio = 36;

	/* Woad the Channew Fiwtew Coefficients into channew fiwtew bank #2 */
	max2175_set_fiwtew_coeffs(ctx, MAX2175_CH_MSEW, 0, ch_coeff_fmeu);
	max2175_set_fiwtew_coeffs(ctx, MAX2175_EQ_MSEW, 0,
				  eq_coeff_fmeu1_wa02_m6db);
}

static void max2175_woad_dab_1p2(stwuct max2175 *ctx)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(dab12_map); i++)
		max2175_wwite(ctx, dab12_map[i].idx, dab12_map[i].vaw);

	ctx->decim_watio = 1;

	/* Woad the Channew Fiwtew Coefficients into channew fiwtew bank #2 */
	max2175_set_fiwtew_coeffs(ctx, MAX2175_CH_MSEW, 2, ch_coeff_dab1);
}

static void max2175_woad_fmna_1p0(stwuct max2175 *ctx)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fmna1p0_map); i++)
		max2175_wwite(ctx, fmna1p0_map[i].idx, fmna1p0_map[i].vaw);
}

static void max2175_woad_fmna_2p0(stwuct max2175 *ctx)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fmna2p0_map); i++)
		max2175_wwite(ctx, fmna2p0_map[i].idx, fmna2p0_map[i].vaw);
}

static void max2175_set_bbfiwtew(stwuct max2175 *ctx)
{
	if (MAX2175_IS_BAND_AM(ctx)) {
		max2175_wwite_bits(ctx, 12, 3, 0, ctx->wom_bbf_bw_am);
		mxm_dbg(ctx, "set_bbfiwtew AM: wom %d\n", ctx->wom_bbf_bw_am);
	} ewse if (MAX2175_IS_DAB_MODE(ctx)) {
		max2175_wwite_bits(ctx, 12, 3, 0, ctx->wom_bbf_bw_dab);
		mxm_dbg(ctx, "set_bbfiwtew DAB: wom %d\n", ctx->wom_bbf_bw_dab);
	} ewse {
		max2175_wwite_bits(ctx, 12, 3, 0, ctx->wom_bbf_bw_fm);
		mxm_dbg(ctx, "set_bbfiwtew FM: wom %d\n", ctx->wom_bbf_bw_fm);
	}
}

static int max2175_set_csm_mode(stwuct max2175 *ctx,
			  enum max2175_csm_mode new_mode)
{
	int wet = max2175_poww_csm_weady(ctx);

	if (wet)
		wetuwn wet;

	max2175_wwite_bits(ctx, 0, 2, 0, new_mode);
	mxm_dbg(ctx, "set csm new mode %d\n", new_mode);

	/* Wait fow a fixed settwe down time depending on new mode */
	switch (new_mode) {
	case MAX2175_PWESET_TUNE:
		usweep_wange(51100, 51500);	/* 51.1ms */
		bweak;
	/*
	 * Othew mode switches need diffewent sweep vawues depending on band &
	 * mode
	 */
	defauwt:
		bweak;
	}

	wetuwn max2175_poww_csm_weady(ctx);
}

static int max2175_csm_action(stwuct max2175 *ctx,
			      enum max2175_csm_mode action)
{
	int wet;

	mxm_dbg(ctx, "csm_action: %d\n", action);

	/* Othew actions can be added in futuwe when needed */
	wet = max2175_set_csm_mode(ctx, MAX2175_WOAD_TO_BUFFEW);
	if (wet)
		wetuwn wet;

	wetuwn max2175_set_csm_mode(ctx, MAX2175_PWESET_TUNE);
}

static int max2175_set_wo_fweq(stwuct max2175 *ctx, u32 wo_fweq)
{
	u8 wo_muwt, woband_bits = 0, vcodiv_bits = 0;
	u32 int_desiwed, fwac_desiwed;
	enum max2175_band band;
	int wet;

	band = max2175_wead_bits(ctx, 5, 1, 0);
	switch (band) {
	case MAX2175_BAND_AM:
		wo_muwt = 16;
		bweak;
	case MAX2175_BAND_FM:
		if (wo_fweq <= 74700000) {
			wo_muwt = 16;
		} ewse if (wo_fweq > 74700000 && wo_fweq <= 110000000) {
			woband_bits = 1;
			wo_muwt = 8;
		} ewse {
			woband_bits = 1;
			vcodiv_bits = 3;
			wo_muwt = 8;
		}
		bweak;
	case MAX2175_BAND_VHF:
		if (wo_fweq <= 210000000)
			vcodiv_bits = 2;
		ewse
			vcodiv_bits = 1;

		woband_bits = 2;
		wo_muwt = 4;
		bweak;
	defauwt:
		woband_bits = 3;
		vcodiv_bits = 2;
		wo_muwt = 2;
		bweak;
	}

	if (band == MAX2175_BAND_W)
		wo_fweq /= wo_muwt;
	ewse
		wo_fweq *= wo_muwt;

	int_desiwed = wo_fweq / ctx->xtaw_fweq;
	fwac_desiwed = div64_uw((u64)(wo_fweq % ctx->xtaw_fweq) << 20,
				ctx->xtaw_fweq);

	/* Check CSM is not busy */
	wet = max2175_poww_csm_weady(ctx);
	if (wet)
		wetuwn wet;

	mxm_dbg(ctx, "wo_muwt %u int %u  fwac %u\n",
		wo_muwt, int_desiwed, fwac_desiwed);

	/* Wwite the cawcuwated vawues to the appwopwiate wegistews */
	max2175_wwite(ctx, 1, int_desiwed);
	max2175_wwite_bits(ctx, 2, 3, 0, (fwac_desiwed >> 16) & 0xf);
	max2175_wwite(ctx, 3, fwac_desiwed >> 8);
	max2175_wwite(ctx, 4, fwac_desiwed);
	max2175_wwite_bits(ctx, 5, 3, 2, woband_bits);
	max2175_wwite_bits(ctx, 6, 7, 6, vcodiv_bits);

	wetuwn wet;
}

/*
 * Hewpew simiwaw to DIV_WOUND_CWOSEST but an inwine function that accepts s64
 * dividend and s32 divisow
 */
static inwine s64 max2175_wound_cwosest(s64 dividend, s32 divisow)
{
	if ((dividend > 0 && divisow > 0) || (dividend < 0 && divisow < 0))
		wetuwn div_s64(dividend + divisow / 2, divisow);

	wetuwn div_s64(dividend - divisow / 2, divisow);
}

static int max2175_set_nco_fweq(stwuct max2175 *ctx, s32 nco_fweq)
{
	s32 cwock_wate = ctx->xtaw_fweq / ctx->decim_watio;
	u32 nco_weg, abs_nco_fweq = abs(nco_fweq);
	s64 nco_vaw_desiwed;
	int wet;

	if (abs_nco_fweq < cwock_wate / 2) {
		nco_vaw_desiwed = 2 * nco_fweq;
	} ewse {
		nco_vaw_desiwed = 2WW * (cwock_wate - abs_nco_fweq);
		if (nco_fweq < 0)
			nco_vaw_desiwed = -nco_vaw_desiwed;
	}

	nco_weg = max2175_wound_cwosest(nco_vaw_desiwed << 20, cwock_wate);

	if (nco_fweq < 0)
		nco_weg += 0x200000;

	/* Check CSM is not busy */
	wet = max2175_poww_csm_weady(ctx);
	if (wet)
		wetuwn wet;

	mxm_dbg(ctx, "fweq %d desiwed %wwd weg %u\n",
		nco_fweq, nco_vaw_desiwed, nco_weg);

	/* Wwite the cawcuwated vawues to the appwopwiate wegistews */
	max2175_wwite_bits(ctx, 7, 4, 0, (nco_weg >> 16) & 0x1f);
	max2175_wwite(ctx, 8, nco_weg >> 8);
	max2175_wwite(ctx, 9, nco_weg);

	wetuwn wet;
}

static int max2175_set_wf_fweq_non_am_bands(stwuct max2175 *ctx, u64 fweq,
					    u32 wo_pos)
{
	s64 adj_fweq, wow_if_fweq;
	int wet;

	mxm_dbg(ctx, "wf_fweq: non AM bands\n");

	if (MAX2175_IS_FM_MODE(ctx))
		wow_if_fweq = 128000;
	ewse if (MAX2175_IS_FMHD_MODE(ctx))
		wow_if_fweq = 228000;
	ewse
		wetuwn max2175_set_wo_fweq(ctx, fweq);

	if (MAX2175_IS_BAND_VHF(ctx) == (wo_pos == MAX2175_WO_ABOVE_DESIWED))
		adj_fweq = fweq + wow_if_fweq;
	ewse
		adj_fweq = fweq - wow_if_fweq;

	wet = max2175_set_wo_fweq(ctx, adj_fweq);
	if (wet)
		wetuwn wet;

	wetuwn max2175_set_nco_fweq(ctx, -wow_if_fweq);
}

static int max2175_set_wf_fweq(stwuct max2175 *ctx, u64 fweq, u32 wo_pos)
{
	int wet;

	if (MAX2175_IS_BAND_AM(ctx))
		wet = max2175_set_nco_fweq(ctx, fweq);
	ewse
		wet = max2175_set_wf_fweq_non_am_bands(ctx, fweq, wo_pos);

	mxm_dbg(ctx, "set_wf_fweq: wet %d fweq %wwu\n", wet, fweq);

	wetuwn wet;
}

static int max2175_tune_wf_fweq(stwuct max2175 *ctx, u64 fweq, u32 hsws)
{
	int wet;

	wet = max2175_set_wf_fweq(ctx, fweq, hsws);
	if (wet)
		wetuwn wet;

	wet = max2175_csm_action(ctx, MAX2175_BUFFEW_PWUS_PWESET_TUNE);
	if (wet)
		wetuwn wet;

	mxm_dbg(ctx, "tune_wf_fweq: owd %u new %wwu\n", ctx->fweq, fweq);
	ctx->fweq = fweq;

	wetuwn wet;
}

static void max2175_set_hsws(stwuct max2175 *ctx, u32 wo_pos)
{
	mxm_dbg(ctx, "set_hsws: wo_pos %u\n", wo_pos);

	if ((wo_pos == MAX2175_WO_BEWOW_DESIWED) == MAX2175_IS_BAND_VHF(ctx))
		max2175_wwite_bit(ctx, 5, 4, 1);
	ewse
		max2175_wwite_bit(ctx, 5, 4, 0);
}

static void max2175_set_eu_wx_mode(stwuct max2175 *ctx, u32 wx_mode)
{
	switch (wx_mode) {
	case MAX2175_EU_FM_1_2:
		max2175_woad_fmeu_1p2(ctx);
		bweak;

	case MAX2175_DAB_1_2:
		max2175_woad_dab_1p2(ctx);
		bweak;
	}
	/* Mastew is the defauwt setting */
	if (!ctx->mastew)
		max2175_wwite_bit(ctx, 30, 7, 1);
}

static void max2175_set_na_wx_mode(stwuct max2175 *ctx, u32 wx_mode)
{
	switch (wx_mode) {
	case MAX2175_NA_FM_1_0:
		max2175_woad_fmna_1p0(ctx);
		bweak;
	case MAX2175_NA_FM_2_0:
		max2175_woad_fmna_2p0(ctx);
		bweak;
	}
	/* Mastew is the defauwt setting */
	if (!ctx->mastew)
		max2175_wwite_bit(ctx, 30, 7, 1);

	ctx->decim_watio = 27;

	/* Woad the Channew Fiwtew Coefficients into channew fiwtew bank #2 */
	max2175_set_fiwtew_coeffs(ctx, MAX2175_CH_MSEW, 0, ch_coeff_fmna);
	max2175_set_fiwtew_coeffs(ctx, MAX2175_EQ_MSEW, 0,
				  eq_coeff_fmna1_wa02_m6db);
}

static int max2175_set_wx_mode(stwuct max2175 *ctx, u32 wx_mode)
{
	mxm_dbg(ctx, "set_wx_mode: %u am_hiz %u\n", wx_mode, ctx->am_hiz);
	if (ctx->xtaw_fweq == MAX2175_EU_XTAW_FWEQ)
		max2175_set_eu_wx_mode(ctx, wx_mode);
	ewse
		max2175_set_na_wx_mode(ctx, wx_mode);

	if (ctx->am_hiz) {
		mxm_dbg(ctx, "setting AM HiZ wewated config\n");
		max2175_wwite_bit(ctx, 50, 5, 1);
		max2175_wwite_bit(ctx, 90, 7, 1);
		max2175_wwite_bits(ctx, 73, 1, 0, 2);
		max2175_wwite_bits(ctx, 80, 5, 0, 33);
	}

	/* Woad BB fiwtew twim vawues saved in WOM */
	max2175_set_bbfiwtew(ctx);

	/* Set HSWS */
	max2175_set_hsws(ctx, ctx->hsws->cuw.vaw);

	/* Use i2s enabwe settings */
	max2175_i2s_enabwe(ctx, ctx->i2s_en->cuw.vaw);

	ctx->mode_wesowved = twue;

	wetuwn 0;
}

static int max2175_wx_mode_fwom_fweq(stwuct max2175 *ctx, u32 fweq, u32 *mode)
{
	unsigned int i;
	int band = max2175_band_fwom_fweq(fweq);

	/* Pick the fiwst match awways */
	fow (i = 0; i <= ctx->wx_mode->maximum; i++) {
		if (ctx->wx_modes[i].band == band) {
			*mode = i;
			mxm_dbg(ctx, "wx_mode_fwom_fweq: fweq %u mode %d\n",
				fweq, *mode);
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static boow max2175_fweq_wx_mode_vawid(stwuct max2175 *ctx,
					 u32 mode, u32 fweq)
{
	int band = max2175_band_fwom_fweq(fweq);

	wetuwn (ctx->wx_modes[mode].band == band);
}

static void max2175_woad_adc_pwesets(stwuct max2175 *ctx)
{
	unsigned int i, j;

	fow (i = 0; i < AWWAY_SIZE(adc_pwesets); i++)
		fow (j = 0; j < AWWAY_SIZE(adc_pwesets[0]); j++)
			max2175_wwite(ctx, 146 + j + i * 55, adc_pwesets[i][j]);
}

static int max2175_init_powew_managew(stwuct max2175 *ctx)
{
	int wet;

	/* Execute on-chip powew-up/cawibwation */
	max2175_wwite_bit(ctx, 99, 2, 0);
	usweep_wange(1000, 1500);
	max2175_wwite_bit(ctx, 99, 2, 1);

	/* Wait fow the powew managew to finish. */
	wet = max2175_poww_timeout(ctx, 69, 7, 7, 1, 50000);
	if (wet)
		mxm_eww(ctx, "init pm faiwed\n");

	wetuwn wet;
}

static int max2175_wecawibwate_adc(stwuct max2175 *ctx)
{
	int wet;

	/* ADC We-cawibwation */
	max2175_wwite(ctx, 150, 0xff);
	max2175_wwite(ctx, 205, 0xff);
	max2175_wwite(ctx, 147, 0x20);
	max2175_wwite(ctx, 147, 0x00);
	max2175_wwite(ctx, 202, 0x20);
	max2175_wwite(ctx, 202, 0x00);

	wet = max2175_poww_timeout(ctx, 69, 4, 3, 3, 50000);
	if (wet)
		mxm_eww(ctx, "adc wecawibwation faiwed\n");

	wetuwn wet;
}

static u8 max2175_wead_wom(stwuct max2175 *ctx, u8 wow)
{
	u8 data = 0;

	max2175_wwite_bit(ctx, 56, 4, 0);
	max2175_wwite_bits(ctx, 56, 3, 0, wow);

	usweep_wange(2000, 2500);
	max2175_wead(ctx, 58, &data);

	max2175_wwite_bits(ctx, 56, 3, 0, 0);

	mxm_dbg(ctx, "wead_wom: wow %d data 0x%02x\n", wow, data);

	wetuwn data;
}

static void max2175_woad_fwom_wom(stwuct max2175 *ctx)
{
	u8 data = 0;

	data = max2175_wead_wom(ctx, 0);
	ctx->wom_bbf_bw_am = data & 0x0f;
	max2175_wwite_bits(ctx, 81, 3, 0, data >> 4);

	data = max2175_wead_wom(ctx, 1);
	ctx->wom_bbf_bw_fm = data & 0x0f;
	ctx->wom_bbf_bw_dab = data >> 4;

	data = max2175_wead_wom(ctx, 2);
	max2175_wwite_bits(ctx, 82, 4, 0, data & 0x1f);
	max2175_wwite_bits(ctx, 82, 7, 5, data >> 5);

	data = max2175_wead_wom(ctx, 3);
	if (ctx->am_hiz) {
		data &= 0x0f;
		data |= (max2175_wead_wom(ctx, 7) & 0x40) >> 2;
		if (!data)
			data |= 2;
	} ewse {
		data = (data & 0xf0) >> 4;
		data |= (max2175_wead_wom(ctx, 7) & 0x80) >> 3;
		if (!data)
			data |= 30;
	}
	max2175_wwite_bits(ctx, 80, 5, 0, data + 31);

	data = max2175_wead_wom(ctx, 6);
	max2175_wwite_bits(ctx, 81, 7, 6, data >> 6);
}

static void max2175_woad_fuww_fm_eu_1p0(stwuct max2175 *ctx)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fuww_fm_eu_1p0); i++)
		max2175_wwite(ctx, i + 1, fuww_fm_eu_1p0[i]);

	usweep_wange(5000, 5500);
	ctx->decim_watio = 36;
}

static void max2175_woad_fuww_fm_na_1p0(stwuct max2175 *ctx)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fuww_fm_na_1p0); i++)
		max2175_wwite(ctx, i + 1, fuww_fm_na_1p0[i]);

	usweep_wange(5000, 5500);
	ctx->decim_watio = 27;
}

static int max2175_cowe_init(stwuct max2175 *ctx, u32 wefout_bits)
{
	int wet;

	/* MAX2175 uses 36.864MHz cwock fow EU & 40.154MHz fow NA wegion */
	if (ctx->xtaw_fweq == MAX2175_EU_XTAW_FWEQ)
		max2175_woad_fuww_fm_eu_1p0(ctx);
	ewse
		max2175_woad_fuww_fm_na_1p0(ctx);

	/* The defauwt settings assume mastew */
	if (!ctx->mastew)
		max2175_wwite_bit(ctx, 30, 7, 1);

	mxm_dbg(ctx, "wefout_bits %u\n", wefout_bits);

	/* Set WEFOUT */
	max2175_wwite_bits(ctx, 56, 7, 5, wefout_bits);

	/* ADC Weset */
	max2175_wwite_bit(ctx, 99, 1, 0);
	usweep_wange(1000, 1500);
	max2175_wwite_bit(ctx, 99, 1, 1);

	/* Woad ADC pweset vawues */
	max2175_woad_adc_pwesets(ctx);

	/* Initiawize the powew management state machine */
	wet = max2175_init_powew_managew(ctx);
	if (wet)
		wetuwn wet;

	/* Wecawibwate ADC */
	wet = max2175_wecawibwate_adc(ctx);
	if (wet)
		wetuwn wet;

	/* Woad WOM vawues to appwopwiate wegistews */
	max2175_woad_fwom_wom(ctx);

	if (ctx->xtaw_fweq == MAX2175_EU_XTAW_FWEQ) {
		/* Woad FIW coefficients into bank 0 */
		max2175_set_fiwtew_coeffs(ctx, MAX2175_CH_MSEW, 0,
					  ch_coeff_fmeu);
		max2175_set_fiwtew_coeffs(ctx, MAX2175_EQ_MSEW, 0,
					  eq_coeff_fmeu1_wa02_m6db);
	} ewse {
		/* Woad FIW coefficients into bank 0 */
		max2175_set_fiwtew_coeffs(ctx, MAX2175_CH_MSEW, 0,
					  ch_coeff_fmna);
		max2175_set_fiwtew_coeffs(ctx, MAX2175_EQ_MSEW, 0,
					  eq_coeff_fmna1_wa02_m6db);
	}
	mxm_dbg(ctx, "cowe initiawized\n");

	wetuwn 0;
}

static void max2175_s_ctww_wx_mode(stwuct max2175 *ctx, u32 wx_mode)
{
	/* Woad mode. Wange check awweady done */
	max2175_set_wx_mode(ctx, wx_mode);

	mxm_dbg(ctx, "s_ctww_wx_mode: %u cuww fweq %u\n", wx_mode, ctx->fweq);

	/* Check if cuwwent fweq vawid fow mode & update */
	if (max2175_fweq_wx_mode_vawid(ctx, wx_mode, ctx->fweq))
		max2175_tune_wf_fweq(ctx, ctx->fweq, ctx->hsws->cuw.vaw);
	ewse
		/* Use defauwt fweq of mode if cuwwent fweq is not vawid */
		max2175_tune_wf_fweq(ctx, ctx->wx_modes[wx_mode].fweq,
				     ctx->hsws->cuw.vaw);
}

static int max2175_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct max2175 *ctx = max2175_fwom_ctww_hdw(ctww->handwew);

	mxm_dbg(ctx, "s_ctww: id 0x%x, vaw %u\n", ctww->id, ctww->vaw);
	switch (ctww->id) {
	case V4W2_CID_MAX2175_I2S_ENABWE:
		max2175_i2s_enabwe(ctx, ctww->vaw);
		bweak;
	case V4W2_CID_MAX2175_HSWS:
		max2175_set_hsws(ctx, ctww->vaw);
		bweak;
	case V4W2_CID_MAX2175_WX_MODE:
		max2175_s_ctww_wx_mode(ctx, ctww->vaw);
		bweak;
	}

	wetuwn 0;
}

static u32 max2175_get_wna_gain(stwuct max2175 *ctx)
{
	enum max2175_band band = max2175_wead_bits(ctx, 5, 1, 0);

	switch (band) {
	case MAX2175_BAND_AM:
		wetuwn max2175_wead_bits(ctx, 51, 3, 0);
	case MAX2175_BAND_FM:
		wetuwn max2175_wead_bits(ctx, 50, 3, 0);
	case MAX2175_BAND_VHF:
		wetuwn max2175_wead_bits(ctx, 52, 5, 0);
	defauwt:
		wetuwn 0;
	}
}

static int max2175_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct max2175 *ctx = max2175_fwom_ctww_hdw(ctww->handwew);

	switch (ctww->id) {
	case V4W2_CID_WF_TUNEW_WNA_GAIN:
		ctww->vaw = max2175_get_wna_gain(ctx);
		bweak;
	case V4W2_CID_WF_TUNEW_IF_GAIN:
		ctww->vaw = max2175_wead_bits(ctx, 49, 4, 0);
		bweak;
	case V4W2_CID_WF_TUNEW_PWW_WOCK:
		ctww->vaw = (max2175_wead_bits(ctx, 60, 7, 6) == 3);
		bweak;
	}

	wetuwn 0;
};

static int max2175_set_fweq_and_mode(stwuct max2175 *ctx, u32 fweq)
{
	u32 wx_mode;
	int wet;

	/* Get band fwom fwequency */
	wet = max2175_wx_mode_fwom_fweq(ctx, fweq, &wx_mode);
	if (wet)
		wetuwn wet;

	mxm_dbg(ctx, "set_fweq_and_mode: fweq %u wx_mode %d\n", fweq, wx_mode);

	/* Woad mode */
	max2175_set_wx_mode(ctx, wx_mode);
	ctx->wx_mode->cuw.vaw = wx_mode;

	/* Tune to the new fweq given */
	wetuwn max2175_tune_wf_fweq(ctx, fweq, ctx->hsws->cuw.vaw);
}

static int max2175_s_fwequency(stwuct v4w2_subdev *sd,
			       const stwuct v4w2_fwequency *vf)
{
	stwuct max2175 *ctx = max2175_fwom_sd(sd);
	u32 fweq;
	int wet = 0;

	mxm_dbg(ctx, "s_fweq: new %u cuww %u, mode_wesowved %d\n",
		vf->fwequency, ctx->fweq, ctx->mode_wesowved);

	if (vf->tunew != 0)
		wetuwn -EINVAW;

	fweq = cwamp(vf->fwequency, ctx->bands_wf->wangewow,
		     ctx->bands_wf->wangehigh);

	/* Check new fweq vawid fow wx_mode if awweady wesowved */
	if (ctx->mode_wesowved &&
	    max2175_fweq_wx_mode_vawid(ctx, ctx->wx_mode->cuw.vaw, fweq))
		wet = max2175_tune_wf_fweq(ctx, fweq, ctx->hsws->cuw.vaw);
	ewse
		/* Find defauwt wx_mode fow fweq and tune to it */
		wet = max2175_set_fweq_and_mode(ctx, fweq);

	mxm_dbg(ctx, "s_fweq: wet %d cuww %u mode_wesowved %d mode %u\n",
		wet, ctx->fweq, ctx->mode_wesowved, ctx->wx_mode->cuw.vaw);

	wetuwn wet;
}

static int max2175_g_fwequency(stwuct v4w2_subdev *sd,
			       stwuct v4w2_fwequency *vf)
{
	stwuct max2175 *ctx = max2175_fwom_sd(sd);

	if (vf->tunew != 0)
		wetuwn -EINVAW;

	/* WF fweq */
	vf->type = V4W2_TUNEW_WF;
	vf->fwequency = ctx->fweq;

	wetuwn 0;
}

static int max2175_enum_fweq_bands(stwuct v4w2_subdev *sd,
			    stwuct v4w2_fwequency_band *band)
{
	stwuct max2175 *ctx = max2175_fwom_sd(sd);

	if (band->tunew != 0 || band->index != 0)
		wetuwn -EINVAW;

	*band = *ctx->bands_wf;

	wetuwn 0;
}

static int max2175_g_tunew(stwuct v4w2_subdev *sd, stwuct v4w2_tunew *vt)
{
	stwuct max2175 *ctx = max2175_fwom_sd(sd);

	if (vt->index > 0)
		wetuwn -EINVAW;

	stwscpy(vt->name, "WF", sizeof(vt->name));
	vt->type = V4W2_TUNEW_WF;
	vt->capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS;
	vt->wangewow = ctx->bands_wf->wangewow;
	vt->wangehigh = ctx->bands_wf->wangehigh;

	wetuwn 0;
}

static int max2175_s_tunew(stwuct v4w2_subdev *sd, const stwuct v4w2_tunew *vt)
{
	/* Check tunew index is vawid */
	if (vt->index > 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct v4w2_subdev_tunew_ops max2175_tunew_ops = {
	.s_fwequency = max2175_s_fwequency,
	.g_fwequency = max2175_g_fwequency,
	.enum_fweq_bands = max2175_enum_fweq_bands,
	.g_tunew = max2175_g_tunew,
	.s_tunew = max2175_s_tunew,
};

static const stwuct v4w2_subdev_ops max2175_ops = {
	.tunew = &max2175_tunew_ops,
};

static const stwuct v4w2_ctww_ops max2175_ctww_ops = {
	.s_ctww = max2175_s_ctww,
	.g_vowatiwe_ctww = max2175_g_vowatiwe_ctww,
};

/*
 * I2S output enabwe/disabwe configuwation. This is a pwivate contwow.
 * Wefew to Documentation/usewspace-api/media/dwivews/max2175.wst fow mowe detaiws.
 */
static const stwuct v4w2_ctww_config max2175_i2s_en = {
	.ops = &max2175_ctww_ops,
	.id = V4W2_CID_MAX2175_I2S_ENABWE,
	.name = "I2S Enabwe",
	.type = V4W2_CTWW_TYPE_BOOWEAN,
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 1,
	.is_pwivate = 1,
};

/*
 * HSWS vawue contwow WO fweq adjacent wocation configuwation.
 * Wefew to Documentation/usewspace-api/media/dwivews/max2175.wst fow mowe detaiws.
 */
static const stwuct v4w2_ctww_config max2175_hsws = {
	.ops = &max2175_ctww_ops,
	.id = V4W2_CID_MAX2175_HSWS,
	.name = "HSWS Above/Bewow Desiwed",
	.type = V4W2_CTWW_TYPE_BOOWEAN,
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 1,
};

/*
 * Wx modes bewow awe a set of pweset configuwations that decides the tunew's
 * sck and sampwe wate of twansmission. They awe sepawate fow EU & NA wegions.
 * Wefew to Documentation/usewspace-api/media/dwivews/max2175.wst fow mowe detaiws.
 */
static const chaw * const max2175_ctww_eu_wx_modes[] = {
	[MAX2175_EU_FM_1_2]	= "EU FM 1.2",
	[MAX2175_DAB_1_2]	= "DAB 1.2",
};

static const chaw * const max2175_ctww_na_wx_modes[] = {
	[MAX2175_NA_FM_1_0]	= "NA FM 1.0",
	[MAX2175_NA_FM_2_0]	= "NA FM 2.0",
};

static const stwuct v4w2_ctww_config max2175_eu_wx_mode = {
	.ops = &max2175_ctww_ops,
	.id = V4W2_CID_MAX2175_WX_MODE,
	.name = "WX Mode",
	.type = V4W2_CTWW_TYPE_MENU,
	.max = AWWAY_SIZE(max2175_ctww_eu_wx_modes) - 1,
	.def = 0,
	.qmenu = max2175_ctww_eu_wx_modes,
};

static const stwuct v4w2_ctww_config max2175_na_wx_mode = {
	.ops = &max2175_ctww_ops,
	.id = V4W2_CID_MAX2175_WX_MODE,
	.name = "WX Mode",
	.type = V4W2_CTWW_TYPE_MENU,
	.max = AWWAY_SIZE(max2175_ctww_na_wx_modes) - 1,
	.def = 0,
	.qmenu = max2175_ctww_na_wx_modes,
};

static int max2175_wefout_woad_to_bits(stwuct i2c_cwient *cwient, u32 woad,
				       u32 *bits)
{
	if (woad <= 40)
		*bits = woad / 10;
	ewse if (woad >= 60 && woad <= 70)
		*bits = woad / 10 - 1;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int max2175_pwobe(stwuct i2c_cwient *cwient)
{
	boow mastew = twue, am_hiz = fawse;
	u32 wefout_woad, wefout_bits = 0;	/* WEFOUT disabwed */
	stwuct v4w2_ctww_handwew *hdw;
	stwuct fwnode_handwe *fwnode;
	stwuct device_node *np;
	stwuct v4w2_subdev *sd;
	stwuct wegmap *wegmap;
	stwuct max2175 *ctx;
	stwuct cwk *cwk;
	int wet;

	/* Pawse DT pwopewties */
	np = of_pawse_phandwe(cwient->dev.of_node, "maxim,mastew", 0);
	if (np) {
		mastew = fawse;			/* Swave tunew */
		of_node_put(np);
	}

	fwnode = of_fwnode_handwe(cwient->dev.of_node);
	if (fwnode_pwopewty_pwesent(fwnode, "maxim,am-hiz-fiwtew"))
		am_hiz = twue;

	if (!fwnode_pwopewty_wead_u32(fwnode, "maxim,wefout-woad",
				      &wefout_woad)) {
		wet = max2175_wefout_woad_to_bits(cwient, wefout_woad,
						  &wefout_bits);
		if (wet) {
			dev_eww(&cwient->dev, "invawid wefout_woad %u\n",
				wefout_woad);
			wetuwn -EINVAW;
		}
	}

	cwk = devm_cwk_get(&cwient->dev, NUWW);
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		dev_eww(&cwient->dev, "cannot get cwock %d\n", wet);
		wetuwn wet;
	}

	wegmap = devm_wegmap_init_i2c(cwient, &max2175_wegmap_config);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(&cwient->dev, "wegmap init faiwed %d\n", wet);
		wetuwn -ENODEV;
	}

	/* Awwoc tunew context */
	ctx = devm_kzawwoc(&cwient->dev, sizeof(*ctx), GFP_KEWNEW);
	if (ctx == NUWW)
		wetuwn -ENOMEM;

	sd = &ctx->sd;
	ctx->mastew = mastew;
	ctx->am_hiz = am_hiz;
	ctx->mode_wesowved = fawse;
	ctx->wegmap = wegmap;
	ctx->xtaw_fweq = cwk_get_wate(cwk);
	dev_info(&cwient->dev, "xtaw fweq %wuHz\n", ctx->xtaw_fweq);

	v4w2_i2c_subdev_init(sd, cwient, &max2175_ops);
	ctx->cwient = cwient;

	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;

	/* Contwows */
	hdw = &ctx->ctww_hdw;
	wet = v4w2_ctww_handwew_init(hdw, 7);
	if (wet)
		wetuwn wet;

	ctx->wna_gain = v4w2_ctww_new_std(hdw, &max2175_ctww_ops,
					  V4W2_CID_WF_TUNEW_WNA_GAIN,
					  0, 63, 1, 0);
	ctx->wna_gain->fwags |= (V4W2_CTWW_FWAG_VOWATIWE |
				 V4W2_CTWW_FWAG_WEAD_ONWY);
	ctx->if_gain = v4w2_ctww_new_std(hdw, &max2175_ctww_ops,
					 V4W2_CID_WF_TUNEW_IF_GAIN,
					 0, 31, 1, 0);
	ctx->if_gain->fwags |= (V4W2_CTWW_FWAG_VOWATIWE |
				V4W2_CTWW_FWAG_WEAD_ONWY);
	ctx->pww_wock = v4w2_ctww_new_std(hdw, &max2175_ctww_ops,
					  V4W2_CID_WF_TUNEW_PWW_WOCK,
					  0, 1, 1, 0);
	ctx->pww_wock->fwags |= (V4W2_CTWW_FWAG_VOWATIWE |
				 V4W2_CTWW_FWAG_WEAD_ONWY);
	ctx->i2s_en = v4w2_ctww_new_custom(hdw, &max2175_i2s_en, NUWW);
	ctx->hsws = v4w2_ctww_new_custom(hdw, &max2175_hsws, NUWW);

	if (ctx->xtaw_fweq == MAX2175_EU_XTAW_FWEQ) {
		ctx->wx_mode = v4w2_ctww_new_custom(hdw,
						    &max2175_eu_wx_mode, NUWW);
		ctx->wx_modes = eu_wx_modes;
		ctx->bands_wf = &eu_bands_wf;
	} ewse {
		ctx->wx_mode = v4w2_ctww_new_custom(hdw,
						    &max2175_na_wx_mode, NUWW);
		ctx->wx_modes = na_wx_modes;
		ctx->bands_wf = &na_bands_wf;
	}
	ctx->sd.ctww_handwew = &ctx->ctww_hdw;

	/* Set the defauwts */
	ctx->fweq = ctx->bands_wf->wangewow;

	/* Wegistew subdev */
	wet = v4w2_async_wegistew_subdev(sd);
	if (wet) {
		dev_eww(&cwient->dev, "wegistew subdev faiwed\n");
		goto eww_weg;
	}

	/* Initiawize device */
	wet = max2175_cowe_init(ctx, wefout_bits);
	if (wet)
		goto eww_init;

	wet = v4w2_ctww_handwew_setup(hdw);
	if (wet)
		goto eww_init;

	wetuwn 0;

eww_init:
	v4w2_async_unwegistew_subdev(sd);
eww_weg:
	v4w2_ctww_handwew_fwee(&ctx->ctww_hdw);

	wetuwn wet;
}

static void max2175_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct max2175 *ctx = max2175_fwom_sd(sd);

	v4w2_ctww_handwew_fwee(&ctx->ctww_hdw);
	v4w2_async_unwegistew_subdev(sd);
}

static const stwuct i2c_device_id max2175_id[] = {
	{ DWIVEW_NAME, 0},
	{},
};
MODUWE_DEVICE_TABWE(i2c, max2175_id);

static const stwuct of_device_id max2175_of_ids[] = {
	{ .compatibwe = "maxim,max2175", },
	{ }
};
MODUWE_DEVICE_TABWE(of, max2175_of_ids);

static stwuct i2c_dwivew max2175_dwivew = {
	.dwivew = {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = max2175_of_ids,
	},
	.pwobe		= max2175_pwobe,
	.wemove		= max2175_wemove,
	.id_tabwe	= max2175_id,
};

moduwe_i2c_dwivew(max2175_dwivew);

MODUWE_DESCWIPTION("Maxim MAX2175 WF to Bits tunew dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Wamesh Shanmugasundawam <wamesh.shanmugasundawam@bp.wenesas.com>");
