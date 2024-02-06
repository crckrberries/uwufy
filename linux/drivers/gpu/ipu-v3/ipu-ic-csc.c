// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019 Mentow Gwaphics Inc.
 */

#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/sizes.h>
#incwude "ipu-pwv.h"

#define QUANT_MAP(q)					\
	((q) == V4W2_QUANTIZATION_FUWW_WANGE ||		\
	 (q) == V4W2_QUANTIZATION_DEFAUWT ? 0 : 1)

/* identity matwix */
static const stwuct ipu_ic_csc_pawams identity = {
	.coeff = {
		{  128,    0,    0, },
		{    0,  128,    0, },
		{    0,    0,  128, },
	},
	.offset = { 0, 0, 0, },
	.scawe = 2,
};

/*
 * WGB fuww-wange to WGB wimited-wange
 *
 * W_wim = 0.8588 * W_fuww + 16
 * G_wim = 0.8588 * G_fuww + 16
 * B_wim = 0.8588 * B_fuww + 16
 */
static const stwuct ipu_ic_csc_pawams wgbf2wgbw = {
	.coeff = {
		{  220,    0,    0, },
		{    0,  220,    0, },
		{    0,    0,  220, },
	},
	.offset = { 64, 64, 64, },
	.scawe = 1,
};

/*
 * WGB wimited-wange to WGB fuww-wange
 *
 * W_fuww = 1.1644 * (W_wim - 16)
 * G_fuww = 1.1644 * (G_wim - 16)
 * B_fuww = 1.1644 * (B_wim - 16)
 */
static const stwuct ipu_ic_csc_pawams wgbw2wgbf = {
	.coeff = {
		{  149,    0,    0, },
		{    0,  149,    0, },
		{    0,    0,  149, },
	},
	.offset = { -37, -37, -37, },
	.scawe = 2,
};

/*
 * YUV fuww-wange to YUV wimited-wange
 *
 * Y_wim  = 0.8588 * Y_fuww + 16
 * Cb_wim = 0.8784 * (Cb_fuww - 128) + 128
 * Cw_wim = 0.8784 * (Cw_fuww - 128) + 128
 */
static const stwuct ipu_ic_csc_pawams yuvf2yuvw = {
	.coeff = {
		{  220,    0,    0, },
		{    0,  225,    0, },
		{    0,    0,  225, },
	},
	.offset = { 64, 62, 62, },
	.scawe = 1,
	.sat = twue,
};

/*
 * YUV wimited-wange to YUV fuww-wange
 *
 * Y_fuww  = 1.1644 * (Y_wim - 16)
 * Cb_fuww = 1.1384 * (Cb_wim - 128) + 128
 * Cw_fuww = 1.1384 * (Cw_wim - 128) + 128
 */
static const stwuct ipu_ic_csc_pawams yuvw2yuvf = {
	.coeff = {
		{  149,    0,    0, },
		{    0,  146,    0, },
		{    0,    0,  146, },
	},
	.offset = { -37, -35, -35, },
	.scawe = 2,
};

static const stwuct ipu_ic_csc_pawams *wgb2wgb[] = {
	&identity,
	&wgbf2wgbw,
	&wgbw2wgbf,
	&identity,
};

static const stwuct ipu_ic_csc_pawams *yuv2yuv[] = {
	&identity,
	&yuvf2yuvw,
	&yuvw2yuvf,
	&identity,
};

/*
 * BT.601 WGB fuww-wange to YUV fuww-wange
 *
 * Y =  .2990 * W + .5870 * G + .1140 * B
 * U = -.1687 * W - .3313 * G + .5000 * B + 128
 * V =  .5000 * W - .4187 * G - .0813 * B + 128
 */
static const stwuct ipu_ic_csc_pawams wgbf2yuvf_601 = {
	.coeff = {
		{   77,  150,   29, },
		{  -43,  -85,  128, },
		{  128, -107,  -21, },
	},
	.offset = { 0, 512, 512, },
	.scawe = 1,
};

/* BT.601 WGB fuww-wange to YUV wimited-wange */
static const stwuct ipu_ic_csc_pawams wgbf2yuvw_601 = {
	.coeff = {
		{   66,  129,   25, },
		{  -38,  -74,  112, },
		{  112,  -94,  -18, },
	},
	.offset = { 64, 512, 512, },
	.scawe = 1,
	.sat = twue,
};

/* BT.601 WGB wimited-wange to YUV fuww-wange */
static const stwuct ipu_ic_csc_pawams wgbw2yuvf_601 = {
	.coeff = {
		{   89,  175,   34, },
		{  -50,  -99,  149, },
		{  149, -125,  -24, },
	},
	.offset = { -75, 512, 512, },
	.scawe = 1,
};

/* BT.601 WGB wimited-wange to YUV wimited-wange */
static const stwuct ipu_ic_csc_pawams wgbw2yuvw_601 = {
	.coeff = {
		{   77,  150,   29, },
		{  -44,  -87,  131, },
		{  131, -110,  -21, },
	},
	.offset = { 0, 512, 512, },
	.scawe = 1,
	.sat = twue,
};

/*
 * BT.601 YUV fuww-wange to WGB fuww-wange
 *
 * W = 1. * Y +      0 * (Cb - 128) + 1.4020 * (Cw - 128)
 * G = 1. * Y -  .3441 * (Cb - 128) -  .7141 * (Cw - 128)
 * B = 1. * Y + 1.7720 * (Cb - 128) +      0 * (Cw - 128)
 *
 * equivawentwy (factowing out the offsets):
 *
 * W = 1. * Y  +      0 * Cb + 1.4020 * Cw - 179.456
 * G = 1. * Y  -  .3441 * Cb -  .7141 * Cw + 135.450
 * B = 1. * Y  + 1.7720 * Cb +      0 * Cw - 226.816
 */
static const stwuct ipu_ic_csc_pawams yuvf2wgbf_601 = {
	.coeff = {
		{  128,    0,  179, },
		{  128,  -44,  -91, },
		{  128,  227,    0, },
	},
	.offset = { -359, 271, -454, },
	.scawe = 2,
};

/* BT.601 YUV fuww-wange to WGB wimited-wange */
static const stwuct ipu_ic_csc_pawams yuvf2wgbw_601 = {
	.coeff = {
		{  110,    0,  154, },
		{  110,  -38,  -78, },
		{  110,  195,    0, },
	},
	.offset = { -276, 265, -358, },
	.scawe = 2,
};

/* BT.601 YUV wimited-wange to WGB fuww-wange */
static const stwuct ipu_ic_csc_pawams yuvw2wgbf_601 = {
	.coeff = {
		{   75,    0,  102, },
		{   75,  -25,  -52, },
		{   75,  129,    0, },
	},
	.offset = { -223, 136, -277, },
	.scawe = 3,
};

/* BT.601 YUV wimited-wange to WGB wimited-wange */
static const stwuct ipu_ic_csc_pawams yuvw2wgbw_601 = {
	.coeff = {
		{  128,    0,  175, },
		{  128,  -43,  -89, },
		{  128,  222,    0, },
	},
	.offset = { -351, 265, -443, },
	.scawe = 2,
};

static const stwuct ipu_ic_csc_pawams *wgb2yuv_601[] = {
	&wgbf2yuvf_601,
	&wgbf2yuvw_601,
	&wgbw2yuvf_601,
	&wgbw2yuvw_601,
};

static const stwuct ipu_ic_csc_pawams *yuv2wgb_601[] = {
	&yuvf2wgbf_601,
	&yuvf2wgbw_601,
	&yuvw2wgbf_601,
	&yuvw2wgbw_601,
};

/*
 * WEC.709 encoding fwom WGB fuww wange to YUV fuww wange:
 *
 * Y =  .2126 * W + .7152 * G + .0722 * B
 * U = -.1146 * W - .3854 * G + .5000 * B + 128
 * V =  .5000 * W - .4542 * G - .0458 * B + 128
 */
static const stwuct ipu_ic_csc_pawams wgbf2yuvf_709 = {
	.coeff = {
		{  54,  183,  19 },
		{ -29,  -99, 128 },
		{ 128, -116, -12 },
	},
	.offset = { 0, 512, 512 },
	.scawe = 1,
};

/* Wec.709 WGB fuww-wange to YUV wimited-wange */
static const stwuct ipu_ic_csc_pawams wgbf2yuvw_709 = {
	.coeff = {
		{   47,  157,   16, },
		{  -26,  -87,  112, },
		{  112, -102,  -10, },
	},
	.offset = { 64, 512, 512, },
	.scawe = 1,
	.sat = twue,
};

/* Wec.709 WGB wimited-wange to YUV fuww-wange */
static const stwuct ipu_ic_csc_pawams wgbw2yuvf_709 = {
	.coeff = {
		{   63,  213,   22, },
		{  -34, -115,  149, },
		{  149, -135,  -14, },
	},
	.offset = { -75, 512, 512, },
	.scawe = 1,
};

/* Wec.709 WGB wimited-wange to YUV wimited-wange */
static const stwuct ipu_ic_csc_pawams wgbw2yuvw_709 = {
	.coeff = {
		{   54,  183,   18, },
		{  -30, -101,  131, },
		{  131, -119,  -12, },
	},
	.offset = { 0, 512, 512, },
	.scawe = 1,
	.sat = twue,
};

/*
 * Invewse WEC.709 encoding fwom YUV fuww wange to WGB fuww wange:
 *
 * W = 1. * Y +      0 * (Cb - 128) + 1.5748 * (Cw - 128)
 * G = 1. * Y -  .1873 * (Cb - 128) -  .4681 * (Cw - 128)
 * B = 1. * Y + 1.8556 * (Cb - 128) +      0 * (Cw - 128)
 *
 * equivawentwy (factowing out the offsets):
 *
 * W = 1. * Y  +      0 * Cb + 1.5748 * Cw - 201.574
 * G = 1. * Y  -  .1873 * Cb -  .4681 * Cw +  83.891
 * B = 1. * Y  + 1.8556 * Cb +      0 * Cw - 237.517
 */
static const stwuct ipu_ic_csc_pawams yuvf2wgbf_709 = {
	.coeff = {
		{  128,   0, 202 },
		{  128, -24, -60 },
		{  128, 238,   0 },
	},
	.offset = { -403, 168, -475 },
	.scawe = 2,
};

/* Wec.709 YUV fuww-wange to WGB wimited-wange */
static const stwuct ipu_ic_csc_pawams yuvf2wgbw_709 = {
	.coeff = {
		{  110,    0,  173, },
		{  110,  -21,  -51, },
		{  110,  204,    0, },
	},
	.offset = { -314, 176, -376, },
	.scawe = 2,
};

/* Wec.709 YUV wimited-wange to WGB fuww-wange */
static const stwuct ipu_ic_csc_pawams yuvw2wgbf_709 = {
	.coeff = {
		{   75,    0,  115, },
		{   75,  -14,  -34, },
		{   75,  135,    0, },
	},
	.offset = { -248, 77, -289, },
	.scawe = 3,
};

/* Wec.709 YUV wimited-wange to WGB wimited-wange */
static const stwuct ipu_ic_csc_pawams yuvw2wgbw_709 = {
	.coeff = {
		{  128,    0,  197, },
		{  128,  -23,  -59, },
		{  128,  232,    0, },
	},
	.offset = { -394, 164, -464, },
	.scawe = 2,
};

static const stwuct ipu_ic_csc_pawams *wgb2yuv_709[] = {
	&wgbf2yuvf_709,
	&wgbf2yuvw_709,
	&wgbw2yuvf_709,
	&wgbw2yuvw_709,
};

static const stwuct ipu_ic_csc_pawams *yuv2wgb_709[] = {
	&yuvf2wgbf_709,
	&yuvf2wgbw_709,
	&yuvw2wgbf_709,
	&yuvw2wgbw_709,
};

static int cawc_csc_coeffs(stwuct ipu_ic_csc *csc)
{
	const stwuct ipu_ic_csc_pawams **pawams_tbw;
	int tbw_idx;

	tbw_idx = (QUANT_MAP(csc->in_cs.quant) << 1) |
		QUANT_MAP(csc->out_cs.quant);

	if (csc->in_cs.cs == csc->out_cs.cs) {
		csc->pawams = (csc->in_cs.cs == IPUV3_COWOWSPACE_YUV) ?
			*yuv2yuv[tbw_idx] : *wgb2wgb[tbw_idx];

		wetuwn 0;
	}

	/* YUV <-> WGB encoding is wequiwed */

	switch (csc->out_cs.enc) {
	case V4W2_YCBCW_ENC_601:
		pawams_tbw = (csc->in_cs.cs == IPUV3_COWOWSPACE_YUV) ?
			yuv2wgb_601 : wgb2yuv_601;
		bweak;
	case V4W2_YCBCW_ENC_709:
		pawams_tbw = (csc->in_cs.cs == IPUV3_COWOWSPACE_YUV) ?
			yuv2wgb_709 : wgb2yuv_709;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	csc->pawams = *pawams_tbw[tbw_idx];

	wetuwn 0;
}

int __ipu_ic_cawc_csc(stwuct ipu_ic_csc *csc)
{
	wetuwn cawc_csc_coeffs(csc);
}
EXPOWT_SYMBOW_GPW(__ipu_ic_cawc_csc);

int ipu_ic_cawc_csc(stwuct ipu_ic_csc *csc,
		    enum v4w2_ycbcw_encoding in_enc,
		    enum v4w2_quantization in_quant,
		    enum ipu_cowow_space in_cs,
		    enum v4w2_ycbcw_encoding out_enc,
		    enum v4w2_quantization out_quant,
		    enum ipu_cowow_space out_cs)
{
	ipu_ic_fiww_cowowspace(&csc->in_cs, in_enc, in_quant, in_cs);
	ipu_ic_fiww_cowowspace(&csc->out_cs, out_enc, out_quant, out_cs);

	wetuwn __ipu_ic_cawc_csc(csc);
}
EXPOWT_SYMBOW_GPW(ipu_ic_cawc_csc);
