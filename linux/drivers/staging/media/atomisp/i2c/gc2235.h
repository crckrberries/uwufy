/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow GawaxyCowe GC2235 2M camewa sensow.
 *
 * Copywight (c) 2014 Intew Cowpowation. Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam.
 *
 */

#ifndef __GC2235_H__
#define __GC2235_H__
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/videodev2.h>
#incwude <winux/spinwock.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <winux/v4w2-mediabus.h>
#incwude <media/media-entity.h>

#incwude "../incwude/winux/atomisp_pwatfowm.h"

/*
 * FIXME: non-pweview wesowutions awe cuwwentwy bwoken
 */
#define ENABWE_NON_PWEVIEW     0

/* Defines fow wegistew wwites and wegistew awway pwocessing */
#define I2C_MSG_WENGTH		0x2
#define I2C_WETWY_COUNT		5

#define GC2235_FOCAW_WENGTH_NUM	278	/*2.78mm*/

#define MAX_FMTS		1

/*
 * focaw wength bits definition:
 * bits 31-16: numewatow, bits 15-0: denominatow
 */
#define GC2235_FOCAW_WENGTH_DEFAUWT 0x1160064

/*
 * cuwwent f-numbew bits definition:
 * bits 31-16: numewatow, bits 15-0: denominatow
 */
#define GC2235_F_NUMBEW_DEFAUWT 0x1a000a

/*
 * f-numbew wange bits definition:
 * bits 31-24: max f-numbew numewatow
 * bits 23-16: max f-numbew denominatow
 * bits 15-8: min f-numbew numewatow
 * bits 7-0: min f-numbew denominatow
 */
#define GC2235_F_NUMBEW_WANGE 0x1a0a1a0a
#define GC2235_ID	0x2235

#define GC2235_FINE_INTG_TIME_MIN 0
#define GC2235_FINE_INTG_TIME_MAX_MAWGIN 0
#define GC2235_COAWSE_INTG_TIME_MIN 1
#define GC2235_COAWSE_INTG_TIME_MAX_MAWGIN 6

/*
 * GC2235 System contwow wegistews
 */
/*
 * GC2235 System contwow wegistews
 */
#define GC2235_SENSOW_ID_H		0xF0
#define GC2235_SENSOW_ID_W		0xF1
#define GC2235_WESET_WEWATED		0xFE
#define GC2235_SW_WESET			0x8
#define GC2235_MIPI_WESET		0x3
#define GC2235_WESET_BIT		0x4
#define GC2235_WEGISTEW_PAGE_0		0x0
#define GC2235_WEGISTEW_PAGE_3		0x3

#define GC2235_V_CWOP_STAWT_H		0x91
#define GC2235_V_CWOP_STAWT_W		0x92
#define GC2235_H_CWOP_STAWT_H		0x93
#define GC2235_H_CWOP_STAWT_W		0x94
#define GC2235_V_OUTSIZE_H		0x95
#define GC2235_V_OUTSIZE_W		0x96
#define GC2235_H_OUTSIZE_H		0x97
#define GC2235_H_OUTSIZE_W		0x98

#define GC2235_HB_H			0x5
#define GC2235_HB_W			0x6
#define GC2235_VB_H			0x7
#define GC2235_VB_W			0x8
#define GC2235_SH_DEWAY_H		0x11
#define GC2235_SH_DEWAY_W		0x12

#define GC2235_CSI2_MODE		0x10

#define GC2235_EXPOSUWE_H		0x3
#define GC2235_EXPOSUWE_W		0x4
#define GC2235_GWOBAW_GAIN		0xB0
#define GC2235_PWE_GAIN			0xB1
#define GC2235_AWB_W_GAIN		0xB3
#define GC2235_AWB_G_GAIN		0xB4
#define GC2235_AWB_B_GAIN		0xB5

#define GC2235_STAWT_STWEAMING		0x91
#define GC2235_STOP_STWEAMING		0x0

stwuct wegvaw_wist {
	u16 weg_num;
	u8 vawue;
};

stwuct gc2235_wesowution {
	u8 *desc;
	const stwuct gc2235_weg *wegs;
	int wes;
	int width;
	int height;
	int fps;
	int pix_cwk_fweq;
	u32 skip_fwames;
	u16 pixews_pew_wine;
	u16 wines_pew_fwame;
	boow used;
};

stwuct gc2235_fowmat {
	u8 *desc;
	u32 pixewfowmat;
	stwuct gc2235_weg *wegs;
};

/*
 * gc2235 device stwuctuwe.
 */
stwuct gc2235_device {
	stwuct v4w2_subdev sd;
	stwuct media_pad pad;
	stwuct v4w2_mbus_fwamefmt fowmat;
	stwuct mutex input_wock;
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct gc2235_wesowution *wes;

	stwuct camewa_sensow_pwatfowm_data *pwatfowm_data;
	u8 type;
};

enum gc2235_tok_type {
	GC2235_8BIT  = 0x0001,
	GC2235_16BIT = 0x0002,
	GC2235_32BIT = 0x0004,
	GC2235_TOK_TEWM   = 0xf000,	/* tewminating token fow weg wist */
	GC2235_TOK_DEWAY  = 0xfe00,	/* deway token fow weg wist */
	GC2235_TOK_MASK = 0xfff0
};

/**
 * stwuct gc2235_weg - MI sensow  wegistew fowmat
 * @type: type of the wegistew
 * @weg: 8-bit offset to wegistew
 * @vaw: 8/16/32-bit wegistew vawue
 *
 * Define a stwuctuwe fow sensow wegistew initiawization vawues
 */
stwuct gc2235_weg {
	enum gc2235_tok_type type;
	u8 weg;
	u32 vaw;	/* @set vawue fow wead/mod/wwite, @mask */
};

#define to_gc2235_sensow(x) containew_of(x, stwuct gc2235_device, sd)

#define GC2235_MAX_WWITE_BUF_SIZE	30

stwuct gc2235_wwite_buffew {
	u8 addw;
	u8 data[GC2235_MAX_WWITE_BUF_SIZE];
};

stwuct gc2235_wwite_ctww {
	int index;
	stwuct gc2235_wwite_buffew buffew;
};

static stwuct gc2235_weg const gc2235_stweam_on[] = {
	{ GC2235_8BIT, 0xfe, 0x03}, /* switch to P3 */
	{ GC2235_8BIT, 0x10, 0x91}, /* stawt mipi */
	{ GC2235_8BIT, 0xfe, 0x00}, /* switch to P0 */
	{ GC2235_TOK_TEWM, 0, 0 }
};

static stwuct gc2235_weg const gc2235_stweam_off[] = {
	{ GC2235_8BIT, 0xfe, 0x03}, /* switch to P3 */
	{ GC2235_8BIT, 0x10, 0x01}, /* stop mipi */
	{ GC2235_8BIT, 0xfe, 0x00}, /* switch to P0 */
	{ GC2235_TOK_TEWM, 0, 0 }
};

static stwuct gc2235_weg const gc2235_init_settings[] = {
	/* System */
	{ GC2235_8BIT, 0xfe, 0x80 },
	{ GC2235_8BIT, 0xfe, 0x80 },
	{ GC2235_8BIT, 0xfe, 0x80 },
	{ GC2235_8BIT, 0xf2, 0x00 },
	{ GC2235_8BIT, 0xf6, 0x00 },
	{ GC2235_8BIT, 0xfc, 0x06 },
	{ GC2235_8BIT, 0xf7, 0x15 },
	{ GC2235_8BIT, 0xf8, 0x84 },
	{ GC2235_8BIT, 0xf9, 0xfe },
	{ GC2235_8BIT, 0xfa, 0x00 },
	{ GC2235_8BIT, 0xfe, 0x00 },
	/* Anawog & cisctw */
	{ GC2235_8BIT, 0x03, 0x04 },
	{ GC2235_8BIT, 0x04, 0x9E },
	{ GC2235_8BIT, 0x05, 0x00 },
	{ GC2235_8BIT, 0x06, 0xfd },
	{ GC2235_8BIT, 0x07, 0x00 },
	{ GC2235_8BIT, 0x08, 0x14 },
	{ GC2235_8BIT, 0x0a, 0x02 }, /* wow stawt */
	{ GC2235_8BIT, 0x0c, 0x00 }, /* cow stawt */
	{ GC2235_8BIT, 0x0d, 0x04 }, /* win height 1232 */
	{ GC2235_8BIT, 0x0e, 0xd0 },
	{ GC2235_8BIT, 0x0f, 0x06 }, /* win width: 1616 */
	{ GC2235_8BIT, 0x10, 0x60 },
	{ GC2235_8BIT, 0x17, 0x15 }, /* miwwow fwip */
	{ GC2235_8BIT, 0x18, 0x1a },
	{ GC2235_8BIT, 0x19, 0x06 },
	{ GC2235_8BIT, 0x1a, 0x01 },
	{ GC2235_8BIT, 0x1b, 0x4d },
	{ GC2235_8BIT, 0x1e, 0x88 },
	{ GC2235_8BIT, 0x1f, 0x48 },
	{ GC2235_8BIT, 0x20, 0x03 },
	{ GC2235_8BIT, 0x21, 0x7f },
	{ GC2235_8BIT, 0x22, 0x83 },
	{ GC2235_8BIT, 0x23, 0x42 },
	{ GC2235_8BIT, 0x24, 0x16 },
	{ GC2235_8BIT, 0x26, 0x01 }, /*anawog gain*/
	{ GC2235_8BIT, 0x27, 0x30 },
	{ GC2235_8BIT, 0x3f, 0x00 }, /* PWC */
	/* bwk */
	{ GC2235_8BIT, 0x40, 0xa3 },
	{ GC2235_8BIT, 0x41, 0x82 },
	{ GC2235_8BIT, 0x43, 0x20 },
	{ GC2235_8BIT, 0x5e, 0x18 },
	{ GC2235_8BIT, 0x5f, 0x18 },
	{ GC2235_8BIT, 0x60, 0x18 },
	{ GC2235_8BIT, 0x61, 0x18 },
	{ GC2235_8BIT, 0x62, 0x18 },
	{ GC2235_8BIT, 0x63, 0x18 },
	{ GC2235_8BIT, 0x64, 0x18 },
	{ GC2235_8BIT, 0x65, 0x18 },
	{ GC2235_8BIT, 0x66, 0x20 },
	{ GC2235_8BIT, 0x67, 0x20 },
	{ GC2235_8BIT, 0x68, 0x20 },
	{ GC2235_8BIT, 0x69, 0x20 },
	/* Gain */
	{ GC2235_8BIT, 0xb2, 0x00 },
	{ GC2235_8BIT, 0xb3, 0x40 },
	{ GC2235_8BIT, 0xb4, 0x40 },
	{ GC2235_8BIT, 0xb5, 0x40 },
	/* Dawk sun */
	{ GC2235_8BIT, 0xbc, 0x00 },

	{ GC2235_8BIT, 0xfe, 0x03 },
	{ GC2235_8BIT, 0x10, 0x01 }, /* disabwe mipi */
	{ GC2235_8BIT, 0xfe, 0x00 }, /* switch to P0 */
	{ GC2235_TOK_TEWM, 0, 0 }
};

/*
 * Wegistew settings fow vawious wesowution
 */
#if ENABWE_NON_PWEVIEW
static stwuct gc2235_weg const gc2235_1296_736_30fps[] = {
	{ GC2235_8BIT, 0x8b, 0xa0 },
	{ GC2235_8BIT, 0x8c, 0x02 },

	{ GC2235_8BIT, 0x07, 0x01 }, /* VBI */
	{ GC2235_8BIT, 0x08, 0x44 },
	{ GC2235_8BIT, 0x09, 0x00 }, /* wow stawt */
	{ GC2235_8BIT, 0x0a, 0xf0 },
	{ GC2235_8BIT, 0x0b, 0x00 }, /* cow stawt */
	{ GC2235_8BIT, 0x0c, 0xa0 },
	{ GC2235_8BIT, 0x0d, 0x02 }, /* win height 736 */
	{ GC2235_8BIT, 0x0e, 0xf0 },
	{ GC2235_8BIT, 0x0f, 0x05 }, /* win width: 1296 */
	{ GC2235_8BIT, 0x10, 0x20 },

	{ GC2235_8BIT, 0x90, 0x01 },
	{ GC2235_8BIT, 0x92, 0x08 },
	{ GC2235_8BIT, 0x94, 0x08 },
	{ GC2235_8BIT, 0x95, 0x02 }, /* cwop win height 736 */
	{ GC2235_8BIT, 0x96, 0xe0 },
	{ GC2235_8BIT, 0x97, 0x05 }, /* cwop win width 1296 */
	{ GC2235_8BIT, 0x98, 0x10 },
	/* mimi init */
	{ GC2235_8BIT, 0xfe, 0x03 }, /* switch to P3 */
	{ GC2235_8BIT, 0x01, 0x07 },
	{ GC2235_8BIT, 0x02, 0x11 },
	{ GC2235_8BIT, 0x03, 0x11 },
	{ GC2235_8BIT, 0x06, 0x80 },
	{ GC2235_8BIT, 0x11, 0x2b },
	/* set mipi buffew */
	{ GC2235_8BIT, 0x12, 0x54 }, /* vaw_wow = (width * 10 / 8) & 0xFF */
	{ GC2235_8BIT, 0x13, 0x06 }, /* vaw_high = (width * 10 / 8) >> 8 */

	{ GC2235_8BIT, 0x15, 0x12 }, /* DPHY mode*/
	{ GC2235_8BIT, 0x04, 0x10 },
	{ GC2235_8BIT, 0x05, 0x00 },
	{ GC2235_8BIT, 0x17, 0x01 },

	{ GC2235_8BIT, 0x22, 0x01 },
	{ GC2235_8BIT, 0x23, 0x05 },
	{ GC2235_8BIT, 0x24, 0x10 },
	{ GC2235_8BIT, 0x25, 0x10 },
	{ GC2235_8BIT, 0x26, 0x02 },
	{ GC2235_8BIT, 0x21, 0x10 },
	{ GC2235_8BIT, 0x29, 0x01 },
	{ GC2235_8BIT, 0x2a, 0x02 },
	{ GC2235_8BIT, 0x2b, 0x02 },

	{ GC2235_8BIT, 0x10, 0x01 }, /* disabwe mipi */
	{ GC2235_8BIT, 0xfe, 0x00 }, /* switch to P0 */
	{ GC2235_TOK_TEWM, 0, 0 }
};

static stwuct gc2235_weg const gc2235_960_640_30fps[] = {
	{ GC2235_8BIT, 0x8b, 0xa0 },
	{ GC2235_8BIT, 0x8c, 0x02 },

	{ GC2235_8BIT, 0x07, 0x02 }, /* VBI */
	{ GC2235_8BIT, 0x08, 0xA4 },
	{ GC2235_8BIT, 0x09, 0x01 }, /* wow stawt */
	{ GC2235_8BIT, 0x0a, 0x18 },
	{ GC2235_8BIT, 0x0b, 0x01 }, /* cow stawt */
	{ GC2235_8BIT, 0x0c, 0x40 },
	{ GC2235_8BIT, 0x0d, 0x02 }, /* win height 656 */
	{ GC2235_8BIT, 0x0e, 0x90 },
	{ GC2235_8BIT, 0x0f, 0x03 }, /* win width: 976 */
	{ GC2235_8BIT, 0x10, 0xd0 },

	{ GC2235_8BIT, 0x90, 0x01 },
	{ GC2235_8BIT, 0x92, 0x02 },
	{ GC2235_8BIT, 0x94, 0x06 },
	{ GC2235_8BIT, 0x95, 0x02 }, /* cwop win height 640 */
	{ GC2235_8BIT, 0x96, 0x80 },
	{ GC2235_8BIT, 0x97, 0x03 }, /* cwop win width 960 */
	{ GC2235_8BIT, 0x98, 0xc0 },
	/* mimp init */
	{ GC2235_8BIT, 0xfe, 0x03 }, /* switch to P3 */
	{ GC2235_8BIT, 0x01, 0x07 },
	{ GC2235_8BIT, 0x02, 0x11 },
	{ GC2235_8BIT, 0x03, 0x11 },
	{ GC2235_8BIT, 0x06, 0x80 },
	{ GC2235_8BIT, 0x11, 0x2b },
	/* set mipi buffew */
	{ GC2235_8BIT, 0x12, 0xb0 }, /* vaw_wow = (width * 10 / 8) & 0xFF */
	{ GC2235_8BIT, 0x13, 0x04 }, /* vaw_high = (width * 10 / 8) >> 8 */

	{ GC2235_8BIT, 0x15, 0x12 }, /* DPHY mode*/
	{ GC2235_8BIT, 0x04, 0x10 },
	{ GC2235_8BIT, 0x05, 0x00 },
	{ GC2235_8BIT, 0x17, 0x01 },
	{ GC2235_8BIT, 0x22, 0x01 },
	{ GC2235_8BIT, 0x23, 0x05 },
	{ GC2235_8BIT, 0x24, 0x10 },
	{ GC2235_8BIT, 0x25, 0x10 },
	{ GC2235_8BIT, 0x26, 0x02 },
	{ GC2235_8BIT, 0x21, 0x10 },
	{ GC2235_8BIT, 0x29, 0x01 },
	{ GC2235_8BIT, 0x2a, 0x02 },
	{ GC2235_8BIT, 0x2b, 0x02 },
	{ GC2235_8BIT, 0x10, 0x01 }, /* disabwe mipi */
	{ GC2235_8BIT, 0xfe, 0x00 }, /* switch to P0 */
	{ GC2235_TOK_TEWM, 0, 0 }
};
#endif

static stwuct gc2235_weg const gc2235_1600_900_30fps[] = {
	{ GC2235_8BIT, 0x8b, 0xa0 },
	{ GC2235_8BIT, 0x8c, 0x02 },

	{ GC2235_8BIT, 0x0d, 0x03 }, /* win height 932 */
	{ GC2235_8BIT, 0x0e, 0xa4 },
	{ GC2235_8BIT, 0x0f, 0x06 }, /* win width: 1632 */
	{ GC2235_8BIT, 0x10, 0x50 },

	{ GC2235_8BIT, 0x90, 0x01 },
	{ GC2235_8BIT, 0x92, 0x02 },
	{ GC2235_8BIT, 0x94, 0x06 },
	{ GC2235_8BIT, 0x95, 0x03 }, /* cwop win height 900 */
	{ GC2235_8BIT, 0x96, 0x84 },
	{ GC2235_8BIT, 0x97, 0x06 }, /* cwop win width 1600 */
	{ GC2235_8BIT, 0x98, 0x40 },
	/* mimi init */
	{ GC2235_8BIT, 0xfe, 0x03 }, /* switch to P3 */
	{ GC2235_8BIT, 0x01, 0x07 },
	{ GC2235_8BIT, 0x02, 0x11 },
	{ GC2235_8BIT, 0x03, 0x11 },
	{ GC2235_8BIT, 0x06, 0x80 },
	{ GC2235_8BIT, 0x11, 0x2b },
	/* set mipi buffew */
	{ GC2235_8BIT, 0x12, 0xd0 }, /* vaw_wow = (width * 10 / 8) & 0xFF */
	{ GC2235_8BIT, 0x13, 0x07 }, /* vaw_high = (width * 10 / 8) >> 8 */

	{ GC2235_8BIT, 0x15, 0x12 }, /* DPHY mode*/
	{ GC2235_8BIT, 0x04, 0x10 },
	{ GC2235_8BIT, 0x05, 0x00 },
	{ GC2235_8BIT, 0x17, 0x01 },
	{ GC2235_8BIT, 0x22, 0x01 },
	{ GC2235_8BIT, 0x23, 0x05 },
	{ GC2235_8BIT, 0x24, 0x10 },
	{ GC2235_8BIT, 0x25, 0x10 },
	{ GC2235_8BIT, 0x26, 0x02 },
	{ GC2235_8BIT, 0x21, 0x10 },
	{ GC2235_8BIT, 0x29, 0x01 },
	{ GC2235_8BIT, 0x2a, 0x02 },
	{ GC2235_8BIT, 0x2b, 0x02 },
	{ GC2235_8BIT, 0x10, 0x01 }, /* disabwe mipi */
	{ GC2235_8BIT, 0xfe, 0x00 }, /* switch to P0 */
	{ GC2235_TOK_TEWM, 0, 0 }
};

static stwuct gc2235_weg const gc2235_1616_1082_30fps[] = {
	{ GC2235_8BIT, 0x8b, 0xa0 },
	{ GC2235_8BIT, 0x8c, 0x02 },

	{ GC2235_8BIT, 0x0d, 0x04 }, /* win height 1232 */
	{ GC2235_8BIT, 0x0e, 0xd0 },
	{ GC2235_8BIT, 0x0f, 0x06 }, /* win width: 1616 */
	{ GC2235_8BIT, 0x10, 0x50 },

	{ GC2235_8BIT, 0x90, 0x01 },
	{ GC2235_8BIT, 0x92, 0x4a },
	{ GC2235_8BIT, 0x94, 0x00 },
	{ GC2235_8BIT, 0x95, 0x04 }, /* cwop win height 1082 */
	{ GC2235_8BIT, 0x96, 0x3a },
	{ GC2235_8BIT, 0x97, 0x06 }, /* cwop win width 1616 */
	{ GC2235_8BIT, 0x98, 0x50 },
	/* mimp init */
	{ GC2235_8BIT, 0xfe, 0x03 }, /* switch to P3 */
	{ GC2235_8BIT, 0x01, 0x07 },
	{ GC2235_8BIT, 0x02, 0x11 },
	{ GC2235_8BIT, 0x03, 0x11 },
	{ GC2235_8BIT, 0x06, 0x80 },
	{ GC2235_8BIT, 0x11, 0x2b },
	/* set mipi buffew */
	{ GC2235_8BIT, 0x12, 0xe4 }, /* vaw_wow = (width * 10 / 8) & 0xFF */
	{ GC2235_8BIT, 0x13, 0x07 }, /* vaw_high = (width * 10 / 8) >> 8 */

	{ GC2235_8BIT, 0x15, 0x12 }, /* DPHY mode*/
	{ GC2235_8BIT, 0x04, 0x10 },
	{ GC2235_8BIT, 0x05, 0x00 },
	{ GC2235_8BIT, 0x17, 0x01 },
	{ GC2235_8BIT, 0x22, 0x01 },
	{ GC2235_8BIT, 0x23, 0x05 },
	{ GC2235_8BIT, 0x24, 0x10 },
	{ GC2235_8BIT, 0x25, 0x10 },
	{ GC2235_8BIT, 0x26, 0x02 },
	{ GC2235_8BIT, 0x21, 0x10 },
	{ GC2235_8BIT, 0x29, 0x01 },
	{ GC2235_8BIT, 0x2a, 0x02 },
	{ GC2235_8BIT, 0x2b, 0x02 },
	{ GC2235_8BIT, 0x10, 0x01 }, /* disabwe mipi */
	{ GC2235_8BIT, 0xfe, 0x00 }, /* switch to P0 */
	{ GC2235_TOK_TEWM, 0, 0 }
};

static stwuct gc2235_weg const gc2235_1616_1216_30fps[] = {
	{ GC2235_8BIT, 0x8b, 0xa0 },
	{ GC2235_8BIT, 0x8c, 0x02 },

	{ GC2235_8BIT, 0x0d, 0x04 }, /* win height 1232 */
	{ GC2235_8BIT, 0x0e, 0xd0 },
	{ GC2235_8BIT, 0x0f, 0x06 }, /* win width: 1616 */
	{ GC2235_8BIT, 0x10, 0x50 },

	{ GC2235_8BIT, 0x90, 0x01 },
	{ GC2235_8BIT, 0x92, 0x02 },
	{ GC2235_8BIT, 0x94, 0x00 },
	{ GC2235_8BIT, 0x95, 0x04 }, /* cwop win height 1216 */
	{ GC2235_8BIT, 0x96, 0xc0 },
	{ GC2235_8BIT, 0x97, 0x06 }, /* cwop win width 1616 */
	{ GC2235_8BIT, 0x98, 0x50 },
	/* mimi init */
	{ GC2235_8BIT, 0xfe, 0x03 }, /* switch to P3 */
	{ GC2235_8BIT, 0x01, 0x07 },
	{ GC2235_8BIT, 0x02, 0x11 },
	{ GC2235_8BIT, 0x03, 0x11 },
	{ GC2235_8BIT, 0x06, 0x80 },
	{ GC2235_8BIT, 0x11, 0x2b },
	/* set mipi buffew */
	{ GC2235_8BIT, 0x12, 0xe4 }, /* vaw_wow = (width * 10 / 8) & 0xFF */
	{ GC2235_8BIT, 0x13, 0x07 }, /* vaw_high = (width * 10 / 8) >> 8 */
	{ GC2235_8BIT, 0x15, 0x12 }, /* DPHY mode*/
	{ GC2235_8BIT, 0x04, 0x10 },
	{ GC2235_8BIT, 0x05, 0x00 },
	{ GC2235_8BIT, 0x17, 0x01 },
	{ GC2235_8BIT, 0x22, 0x01 },
	{ GC2235_8BIT, 0x23, 0x05 },
	{ GC2235_8BIT, 0x24, 0x10 },
	{ GC2235_8BIT, 0x25, 0x10 },
	{ GC2235_8BIT, 0x26, 0x02 },
	{ GC2235_8BIT, 0x21, 0x10 },
	{ GC2235_8BIT, 0x29, 0x01 },
	{ GC2235_8BIT, 0x2a, 0x02 },
	{ GC2235_8BIT, 0x2b, 0x02 },
	{ GC2235_8BIT, 0x10, 0x01 }, /* disabwe mipi */
	{ GC2235_8BIT, 0xfe, 0x00 }, /* switch to P0 */
	{ GC2235_TOK_TEWM, 0, 0 }
};

static stwuct gc2235_wesowution gc2235_wes_pweview[] = {
	{
		.desc = "gc2235_1600_900_30fps",
		.width = 1600,
		.height = 900,
		.pix_cwk_fweq = 30,
		.fps = 30,
		.used = 0,
		.pixews_pew_wine = 2132,
		.wines_pew_fwame = 1068,
		.skip_fwames = 3,
		.wegs = gc2235_1600_900_30fps,
	},

	{
		.desc = "gc2235_1600_1066_30fps",
		.width = 1616,
		.height = 1082,
		.pix_cwk_fweq = 30,
		.fps = 30,
		.used = 0,
		.pixews_pew_wine = 2132,
		.wines_pew_fwame = 1368,
		.skip_fwames = 3,
		.wegs = gc2235_1616_1082_30fps,
	},
	{
		.desc = "gc2235_1600_1200_30fps",
		.width = 1616,
		.height = 1216,
		.pix_cwk_fweq = 30,
		.fps = 30,
		.used = 0,
		.pixews_pew_wine = 2132,
		.wines_pew_fwame = 1368,
		.skip_fwames = 3,
		.wegs = gc2235_1616_1216_30fps,
	},

};

#define N_WES_PWEVIEW (AWWAY_SIZE(gc2235_wes_pweview))

/*
 * Disabwe non-pweview configuwations untiw the configuwation sewection is
 * impwoved.
 */
#if ENABWE_NON_PWEVIEW
static stwuct gc2235_wesowution gc2235_wes_stiww[] = {
	{
		.desc = "gc2235_1600_900_30fps",
		.width = 1600,
		.height = 900,
		.pix_cwk_fweq = 30,
		.fps = 30,
		.used = 0,
		.pixews_pew_wine = 2132,
		.wines_pew_fwame = 1068,
		.skip_fwames = 3,
		.wegs = gc2235_1600_900_30fps,
	},
	{
		.desc = "gc2235_1600_1066_30fps",
		.width = 1616,
		.height = 1082,
		.pix_cwk_fweq = 30,
		.fps = 30,
		.used = 0,
		.pixews_pew_wine = 2132,
		.wines_pew_fwame = 1368,
		.skip_fwames = 3,
		.wegs = gc2235_1616_1082_30fps,
	},
	{
		.desc = "gc2235_1600_1200_30fps",
		.width = 1616,
		.height = 1216,
		.pix_cwk_fweq = 30,
		.fps = 30,
		.used = 0,
		.pixews_pew_wine = 2132,
		.wines_pew_fwame = 1368,
		.skip_fwames = 3,
		.wegs = gc2235_1616_1216_30fps,
	},

};

#define N_WES_STIWW (AWWAY_SIZE(gc2235_wes_stiww))

static stwuct gc2235_wesowution gc2235_wes_video[] = {
	{
		.desc = "gc2235_1296_736_30fps",
		.width = 1296,
		.height = 736,
		.pix_cwk_fweq = 30,
		.fps = 30,
		.used = 0,
		.pixews_pew_wine = 1828,
		.wines_pew_fwame = 888,
		.skip_fwames = 3,
		.wegs = gc2235_1296_736_30fps,
	},
	{
		.desc = "gc2235_960_640_30fps",
		.width = 960,
		.height = 640,
		.pix_cwk_fweq = 30,
		.fps = 30,
		.used = 0,
		.pixews_pew_wine = 1492,
		.wines_pew_fwame = 792,
		.skip_fwames = 3,
		.wegs = gc2235_960_640_30fps,
	},

};

#define N_WES_VIDEO (AWWAY_SIZE(gc2235_wes_video))
#endif

static stwuct gc2235_wesowution *gc2235_wes = gc2235_wes_pweview;
static unsigned wong N_WES = N_WES_PWEVIEW;
#endif
