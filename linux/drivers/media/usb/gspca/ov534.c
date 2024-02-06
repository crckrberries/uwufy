// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ov534-ov7xxx gspca dwivew
 *
 * Copywight (C) 2008 Antonio Ospite <ospite@studenti.unina.it>
 * Copywight (C) 2008 Jim Pawis <jim@jtan.com>
 * Copywight (C) 2009 Jean-Fwancois Moine http://moinejf.fwee.fw
 *
 * Based on a pwototype wwitten by Mawk Fewweww <majowtwips@gmaiw.com>
 * USB pwotocow wevewse engineewed by Jim Pawis <jim@jtan.com>
 * https://jim.sh/svn/jim/devw/pwaystation/ps3/eye/test/
 *
 * PS3 Eye camewa enhanced by Wichawd Kaswy http://kaswy.fwee.fw
 * PS3 Eye camewa - bwightness, contwast, awb, agc, aec contwows
 *                  added by Max Thwun <beaw24ww@gmaiw.com>
 * PS3 Eye camewa - FPS wange extended by Joseph Howse
 *                  <josephhowse@nummist.com> https://nummist.com
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "ov534"

#incwude "gspca.h"

#incwude <winux/fixp-awith.h>
#incwude <media/v4w2-ctwws.h>

#define OV534_WEG_ADDWESS	0xf1	/* sensow addwess */
#define OV534_WEG_SUBADDW	0xf2
#define OV534_WEG_WWITE		0xf3
#define OV534_WEG_WEAD		0xf4
#define OV534_WEG_OPEWATION	0xf5
#define OV534_WEG_STATUS	0xf6

#define OV534_OP_WWITE_3	0x37
#define OV534_OP_WWITE_2	0x33
#define OV534_OP_WEAD_2		0xf9

#define CTWW_TIMEOUT 500
#define DEFAUWT_FWAME_WATE 30

MODUWE_AUTHOW("Antonio Ospite <ospite@studenti.unina.it>");
MODUWE_DESCWIPTION("GSPCA/OV534 USB Camewa Dwivew");
MODUWE_WICENSE("GPW");

/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */

	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_ctww *hue;
	stwuct v4w2_ctww *satuwation;
	stwuct v4w2_ctww *bwightness;
	stwuct v4w2_ctww *contwast;
	stwuct { /* gain contwow cwustew */
		stwuct v4w2_ctww *autogain;
		stwuct v4w2_ctww *gain;
	};
	stwuct v4w2_ctww *autowhitebawance;
	stwuct { /* exposuwe contwow cwustew */
		stwuct v4w2_ctww *autoexposuwe;
		stwuct v4w2_ctww *exposuwe;
	};
	stwuct v4w2_ctww *shawpness;
	stwuct v4w2_ctww *hfwip;
	stwuct v4w2_ctww *vfwip;
	stwuct v4w2_ctww *pwfweq;

	__u32 wast_pts;
	u16 wast_fid;
	u8 fwame_wate;

	u8 sensow;
};
enum sensows {
	SENSOW_OV767x,
	SENSOW_OV772x,
	NSENSOWS
};

static int sd_stawt(stwuct gspca_dev *gspca_dev);
static void sd_stopN(stwuct gspca_dev *gspca_dev);


static const stwuct v4w2_pix_fowmat ov772x_mode[] = {
	{320, 240, V4W2_PIX_FMT_YUYV, V4W2_FIEWD_NONE,
	 .bytespewwine = 320 * 2,
	 .sizeimage = 320 * 240 * 2,
	 .cowowspace = V4W2_COWOWSPACE_SWGB,
	 .pwiv = 1},
	{640, 480, V4W2_PIX_FMT_YUYV, V4W2_FIEWD_NONE,
	 .bytespewwine = 640 * 2,
	 .sizeimage = 640 * 480 * 2,
	 .cowowspace = V4W2_COWOWSPACE_SWGB,
	 .pwiv = 0},
	{320, 240, V4W2_PIX_FMT_SGWBG8, V4W2_FIEWD_NONE,
	 .bytespewwine = 320,
	 .sizeimage = 320 * 240,
	 .cowowspace = V4W2_COWOWSPACE_SWGB,
	 .pwiv = 1},
	{640, 480, V4W2_PIX_FMT_SGWBG8, V4W2_FIEWD_NONE,
	 .bytespewwine = 640,
	 .sizeimage = 640 * 480,
	 .cowowspace = V4W2_COWOWSPACE_SWGB,
	 .pwiv = 0},
};
static const stwuct v4w2_pix_fowmat ov767x_mode[] = {
	{320, 240, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG},
	{640, 480, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG},
};

static const u8 qvga_wates[] = {187, 150, 137, 125, 100, 75, 60, 50, 37, 30};
static const u8 vga_wates[] = {60, 50, 40, 30, 15};

static const stwuct fwamewates ov772x_fwamewates[] = {
	{ /* 320x240 */
		.wates = qvga_wates,
		.nwates = AWWAY_SIZE(qvga_wates),
	},
	{ /* 640x480 */
		.wates = vga_wates,
		.nwates = AWWAY_SIZE(vga_wates),
	},
	{ /* 320x240 SGBWG8 */
		.wates = qvga_wates,
		.nwates = AWWAY_SIZE(qvga_wates),
	},
	{ /* 640x480 SGBWG8 */
		.wates = vga_wates,
		.nwates = AWWAY_SIZE(vga_wates),
	},
};

stwuct weg_awway {
	const u8 (*vaw)[2];
	int wen;
};

static const u8 bwidge_init_767x[][2] = {
/* comments fwom the ms-win fiwe apowwo7670.set */
/* stw1 */
	{0xf1, 0x42},
	{0x88, 0xf8},
	{0x89, 0xff},
	{0x76, 0x03},
	{0x92, 0x03},
	{0x95, 0x10},
	{0xe2, 0x00},
	{0xe7, 0x3e},
	{0x8d, 0x1c},
	{0x8e, 0x00},
	{0x8f, 0x00},
	{0x1f, 0x00},
	{0xc3, 0xf9},
	{0x89, 0xff},
	{0x88, 0xf8},
	{0x76, 0x03},
	{0x92, 0x01},
	{0x93, 0x18},
	{0x1c, 0x00},
	{0x1d, 0x48},
	{0x1d, 0x00},
	{0x1d, 0xff},
	{0x1d, 0x02},
	{0x1d, 0x58},
	{0x1d, 0x00},
	{0x1c, 0x0a},
	{0x1d, 0x0a},
	{0x1d, 0x0e},
	{0xc0, 0x50},	/* HSize 640 */
	{0xc1, 0x3c},	/* VSize 480 */
	{0x34, 0x05},	/* enabwe Audio Suspend mode */
	{0xc2, 0x0c},	/* Input YUV */
	{0xc3, 0xf9},	/* enabwe PWE */
	{0x34, 0x05},	/* enabwe Audio Suspend mode */
	{0xe7, 0x2e},	/* this sowves faiwuwe of "SuspendWesumeTest" */
	{0x31, 0xf9},	/* enabwe 1.8V Suspend */
	{0x35, 0x02},	/* tuwn on JPEG */
	{0xd9, 0x10},
	{0x25, 0x42},	/* GPIO[8]:Input */
	{0x94, 0x11},	/* If the defauwt setting is woaded when
			 * system boots up, this fwag is cwosed hewe */
};
static const u8 sensow_init_767x[][2] = {
	{0x12, 0x80},
	{0x11, 0x03},
	{0x3a, 0x04},
	{0x12, 0x00},
	{0x17, 0x13},
	{0x18, 0x01},
	{0x32, 0xb6},
	{0x19, 0x02},
	{0x1a, 0x7a},
	{0x03, 0x0a},
	{0x0c, 0x00},
	{0x3e, 0x00},
	{0x70, 0x3a},
	{0x71, 0x35},
	{0x72, 0x11},
	{0x73, 0xf0},
	{0xa2, 0x02},
	{0x7a, 0x2a},	/* set Gamma=1.6 bewow */
	{0x7b, 0x12},
	{0x7c, 0x1d},
	{0x7d, 0x2d},
	{0x7e, 0x45},
	{0x7f, 0x50},
	{0x80, 0x59},
	{0x81, 0x62},
	{0x82, 0x6b},
	{0x83, 0x73},
	{0x84, 0x7b},
	{0x85, 0x8a},
	{0x86, 0x98},
	{0x87, 0xb2},
	{0x88, 0xca},
	{0x89, 0xe0},
	{0x13, 0xe0},
	{0x00, 0x00},
	{0x10, 0x00},
	{0x0d, 0x40},
	{0x14, 0x38},	/* gain max 16x */
	{0xa5, 0x05},
	{0xab, 0x07},
	{0x24, 0x95},
	{0x25, 0x33},
	{0x26, 0xe3},
	{0x9f, 0x78},
	{0xa0, 0x68},
	{0xa1, 0x03},
	{0xa6, 0xd8},
	{0xa7, 0xd8},
	{0xa8, 0xf0},
	{0xa9, 0x90},
	{0xaa, 0x94},
	{0x13, 0xe5},
	{0x0e, 0x61},
	{0x0f, 0x4b},
	{0x16, 0x02},
	{0x21, 0x02},
	{0x22, 0x91},
	{0x29, 0x07},
	{0x33, 0x0b},
	{0x35, 0x0b},
	{0x37, 0x1d},
	{0x38, 0x71},
	{0x39, 0x2a},
	{0x3c, 0x78},
	{0x4d, 0x40},
	{0x4e, 0x20},
	{0x69, 0x00},
	{0x6b, 0x4a},
	{0x74, 0x10},
	{0x8d, 0x4f},
	{0x8e, 0x00},
	{0x8f, 0x00},
	{0x90, 0x00},
	{0x91, 0x00},
	{0x96, 0x00},
	{0x9a, 0x80},
	{0xb0, 0x84},
	{0xb1, 0x0c},
	{0xb2, 0x0e},
	{0xb3, 0x82},
	{0xb8, 0x0a},
	{0x43, 0x0a},
	{0x44, 0xf0},
	{0x45, 0x34},
	{0x46, 0x58},
	{0x47, 0x28},
	{0x48, 0x3a},
	{0x59, 0x88},
	{0x5a, 0x88},
	{0x5b, 0x44},
	{0x5c, 0x67},
	{0x5d, 0x49},
	{0x5e, 0x0e},
	{0x6c, 0x0a},
	{0x6d, 0x55},
	{0x6e, 0x11},
	{0x6f, 0x9f},
	{0x6a, 0x40},
	{0x01, 0x40},
	{0x02, 0x40},
	{0x13, 0xe7},
	{0x4f, 0x80},
	{0x50, 0x80},
	{0x51, 0x00},
	{0x52, 0x22},
	{0x53, 0x5e},
	{0x54, 0x80},
	{0x58, 0x9e},
	{0x41, 0x08},
	{0x3f, 0x00},
	{0x75, 0x04},
	{0x76, 0xe1},
	{0x4c, 0x00},
	{0x77, 0x01},
	{0x3d, 0xc2},
	{0x4b, 0x09},
	{0xc9, 0x60},
	{0x41, 0x38},	/* jfm: auto shawpness + auto de-noise  */
	{0x56, 0x40},
	{0x34, 0x11},
	{0x3b, 0xc2},
	{0xa4, 0x8a},	/* Night mode twiggew point */
	{0x96, 0x00},
	{0x97, 0x30},
	{0x98, 0x20},
	{0x99, 0x20},
	{0x9a, 0x84},
	{0x9b, 0x29},
	{0x9c, 0x03},
	{0x9d, 0x4c},
	{0x9e, 0x3f},
	{0x78, 0x04},
	{0x79, 0x01},
	{0xc8, 0xf0},
	{0x79, 0x0f},
	{0xc8, 0x00},
	{0x79, 0x10},
	{0xc8, 0x7e},
	{0x79, 0x0a},
	{0xc8, 0x80},
	{0x79, 0x0b},
	{0xc8, 0x01},
	{0x79, 0x0c},
	{0xc8, 0x0f},
	{0x79, 0x0d},
	{0xc8, 0x20},
	{0x79, 0x09},
	{0xc8, 0x80},
	{0x79, 0x02},
	{0xc8, 0xc0},
	{0x79, 0x03},
	{0xc8, 0x20},
	{0x79, 0x26},
};
static const u8 bwidge_stawt_vga_767x[][2] = {
/* stw59 JPG */
	{0x94, 0xaa},
	{0xf1, 0x42},
	{0xe5, 0x04},
	{0xc0, 0x50},
	{0xc1, 0x3c},
	{0xc2, 0x0c},
	{0x35, 0x02},	/* tuwn on JPEG */
	{0xd9, 0x10},
	{0xda, 0x00},	/* fow highew cwock wate(30fps) */
	{0x34, 0x05},	/* enabwe Audio Suspend mode */
	{0xc3, 0xf9},	/* enabwe PWE */
	{0x8c, 0x00},	/* CIF VSize WSB[2:0] */
	{0x8d, 0x1c},	/* output YUV */
/*	{0x34, 0x05},	 * enabwe Audio Suspend mode (?) */
	{0x50, 0x00},	/* H/V dividew=0 */
	{0x51, 0xa0},	/* input H=640/4 */
	{0x52, 0x3c},	/* input V=480/4 */
	{0x53, 0x00},	/* offset X=0 */
	{0x54, 0x00},	/* offset Y=0 */
	{0x55, 0x00},	/* H/V size[8]=0 */
	{0x57, 0x00},	/* H-size[9]=0 */
	{0x5c, 0x00},	/* output size[9:8]=0 */
	{0x5a, 0xa0},	/* output H=640/4 */
	{0x5b, 0x78},	/* output V=480/4 */
	{0x1c, 0x0a},
	{0x1d, 0x0a},
	{0x94, 0x11},
};
static const u8 sensow_stawt_vga_767x[][2] = {
	{0x11, 0x01},
	{0x1e, 0x04},
	{0x19, 0x02},
	{0x1a, 0x7a},
};
static const u8 bwidge_stawt_qvga_767x[][2] = {
/* stw86 JPG */
	{0x94, 0xaa},
	{0xf1, 0x42},
	{0xe5, 0x04},
	{0xc0, 0x80},
	{0xc1, 0x60},
	{0xc2, 0x0c},
	{0x35, 0x02},	/* tuwn on JPEG */
	{0xd9, 0x10},
	{0xc0, 0x50},	/* CIF HSize 640 */
	{0xc1, 0x3c},	/* CIF VSize 480 */
	{0x8c, 0x00},	/* CIF VSize WSB[2:0] */
	{0x8d, 0x1c},	/* output YUV */
	{0x34, 0x05},	/* enabwe Audio Suspend mode */
	{0xc2, 0x4c},	/* output YUV and Enabwe DCW */
	{0xc3, 0xf9},	/* enabwe PWE */
	{0x1c, 0x00},	/* indiwect addwessing */
	{0x1d, 0x48},	/* output YUV422 */
	{0x50, 0x89},	/* H/V dividew=/2; pwus DCW AVG */
	{0x51, 0xa0},	/* DCW input H=640/4 */
	{0x52, 0x78},	/* DCW input V=480/4 */
	{0x53, 0x00},	/* offset X=0 */
	{0x54, 0x00},	/* offset Y=0 */
	{0x55, 0x00},	/* H/V size[8]=0 */
	{0x57, 0x00},	/* H-size[9]=0 */
	{0x5c, 0x00},	/* DCW output size[9:8]=0 */
	{0x5a, 0x50},	/* DCW output H=320/4 */
	{0x5b, 0x3c},	/* DCW output V=240/4 */
	{0x1c, 0x0a},
	{0x1d, 0x0a},
	{0x94, 0x11},
};
static const u8 sensow_stawt_qvga_767x[][2] = {
	{0x11, 0x01},
	{0x1e, 0x04},
	{0x19, 0x02},
	{0x1a, 0x7a},
};

static const u8 bwidge_init_772x[][2] = {
	{ 0x88, 0xf8 },
	{ 0x89, 0xff },
	{ 0x76, 0x03 },
	{ 0x92, 0x01 },
	{ 0x93, 0x18 },
	{ 0x94, 0x10 },
	{ 0x95, 0x10 },
	{ 0xe2, 0x00 },
	{ 0xe7, 0x3e },

	{ 0x96, 0x00 },

	{ 0x97, 0x20 },
	{ 0x97, 0x20 },
	{ 0x97, 0x20 },
	{ 0x97, 0x0a },
	{ 0x97, 0x3f },
	{ 0x97, 0x4a },
	{ 0x97, 0x20 },
	{ 0x97, 0x15 },
	{ 0x97, 0x0b },

	{ 0x8e, 0x40 },
	{ 0x1f, 0x81 },
	{ 0x34, 0x05 },
	{ 0xe3, 0x04 },
	{ 0x89, 0x00 },
	{ 0x76, 0x00 },
	{ 0xe7, 0x2e },
	{ 0x31, 0xf9 },
	{ 0x25, 0x42 },
	{ 0x21, 0xf0 },

	{ 0x1c, 0x0a },
	{ 0x1d, 0x08 }, /* tuwn on UVC headew */
	{ 0x1d, 0x0e }, /* .. */
};
static const u8 sensow_init_772x[][2] = {
	{ 0x12, 0x80 },
	{ 0x11, 0x01 },
/*fixme: bettew have a deway?*/
	{ 0x11, 0x01 },
	{ 0x11, 0x01 },
	{ 0x11, 0x01 },
	{ 0x11, 0x01 },
	{ 0x11, 0x01 },
	{ 0x11, 0x01 },
	{ 0x11, 0x01 },
	{ 0x11, 0x01 },
	{ 0x11, 0x01 },
	{ 0x11, 0x01 },

	{ 0x3d, 0x03 },
	{ 0x17, 0x26 },
	{ 0x18, 0xa0 },
	{ 0x19, 0x07 },
	{ 0x1a, 0xf0 },
	{ 0x32, 0x00 },
	{ 0x29, 0xa0 },
	{ 0x2c, 0xf0 },
	{ 0x65, 0x20 },
	{ 0x11, 0x01 },
	{ 0x42, 0x7f },
	{ 0x63, 0xaa },		/* AWB - was e0 */
	{ 0x64, 0xff },
	{ 0x66, 0x00 },
	{ 0x13, 0xf0 },		/* com8 */
	{ 0x0d, 0x41 },
	{ 0x0f, 0xc5 },
	{ 0x14, 0x11 },

	{ 0x22, 0x7f },
	{ 0x23, 0x03 },
	{ 0x24, 0x40 },
	{ 0x25, 0x30 },
	{ 0x26, 0xa1 },
	{ 0x2a, 0x00 },
	{ 0x2b, 0x00 },
	{ 0x6b, 0xaa },
	{ 0x13, 0xff },		/* AWB */

	{ 0x90, 0x05 },
	{ 0x91, 0x01 },
	{ 0x92, 0x03 },
	{ 0x93, 0x00 },
	{ 0x94, 0x60 },
	{ 0x95, 0x3c },
	{ 0x96, 0x24 },
	{ 0x97, 0x1e },
	{ 0x98, 0x62 },
	{ 0x99, 0x80 },
	{ 0x9a, 0x1e },
	{ 0x9b, 0x08 },
	{ 0x9c, 0x20 },
	{ 0x9e, 0x81 },

	{ 0xa6, 0x07 },
	{ 0x7e, 0x0c },
	{ 0x7f, 0x16 },
	{ 0x80, 0x2a },
	{ 0x81, 0x4e },
	{ 0x82, 0x61 },
	{ 0x83, 0x6f },
	{ 0x84, 0x7b },
	{ 0x85, 0x86 },
	{ 0x86, 0x8e },
	{ 0x87, 0x97 },
	{ 0x88, 0xa4 },
	{ 0x89, 0xaf },
	{ 0x8a, 0xc5 },
	{ 0x8b, 0xd7 },
	{ 0x8c, 0xe8 },
	{ 0x8d, 0x20 },

	{ 0x2b, 0x00 },
	{ 0x22, 0x7f },
	{ 0x23, 0x03 },
	{ 0x11, 0x01 },
	{ 0x64, 0xff },
	{ 0x0d, 0x41 },

	{ 0x14, 0x41 },
	{ 0x0e, 0xcd },
	{ 0xac, 0xbf },
	{ 0x8e, 0x00 },		/* De-noise thweshowd */
};
static const u8 bwidge_stawt_vga_yuyv_772x[][2] = {
	{0x88, 0x00},
	{0x1c, 0x00},
	{0x1d, 0x40},
	{0x1d, 0x02},
	{0x1d, 0x00},
	{0x1d, 0x02},
	{0x1d, 0x58},
	{0x1d, 0x00},
	{0x8d, 0x1c},
	{0x8e, 0x80},
	{0xc0, 0x50},
	{0xc1, 0x3c},
	{0xc2, 0x0c},
	{0xc3, 0x69},
};
static const u8 sensow_stawt_vga_yuyv_772x[][2] = {
	{0x12, 0x00},
	{0x17, 0x26},
	{0x18, 0xa0},
	{0x19, 0x07},
	{0x1a, 0xf0},
	{0x29, 0xa0},
	{0x2c, 0xf0},
	{0x65, 0x20},
	{0x67, 0x00},
};
static const u8 bwidge_stawt_qvga_yuyv_772x[][2] = {
	{0x88, 0x00},
	{0x1c, 0x00},
	{0x1d, 0x40},
	{0x1d, 0x02},
	{0x1d, 0x00},
	{0x1d, 0x01},
	{0x1d, 0x4b},
	{0x1d, 0x00},
	{0x8d, 0x1c},
	{0x8e, 0x80},
	{0xc0, 0x28},
	{0xc1, 0x1e},
	{0xc2, 0x0c},
	{0xc3, 0x69},
};
static const u8 sensow_stawt_qvga_yuyv_772x[][2] = {
	{0x12, 0x40},
	{0x17, 0x3f},
	{0x18, 0x50},
	{0x19, 0x03},
	{0x1a, 0x78},
	{0x29, 0x50},
	{0x2c, 0x78},
	{0x65, 0x2f},
	{0x67, 0x00},
};
static const u8 bwidge_stawt_vga_gbwg_772x[][2] = {
	{0x88, 0x08},
	{0x1c, 0x00},
	{0x1d, 0x00},
	{0x1d, 0x02},
	{0x1d, 0x00},
	{0x1d, 0x01},
	{0x1d, 0x2c},
	{0x1d, 0x00},
	{0x8d, 0x00},
	{0x8e, 0x00},
	{0xc0, 0x50},
	{0xc1, 0x3c},
	{0xc2, 0x01},
	{0xc3, 0x01},
};
static const u8 sensow_stawt_vga_gbwg_772x[][2] = {
	{0x12, 0x01},
	{0x17, 0x26},
	{0x18, 0xa0},
	{0x19, 0x07},
	{0x1a, 0xf0},
	{0x29, 0xa0},
	{0x2c, 0xf0},
	{0x65, 0x20},
	{0x67, 0x02},
};
static const u8 bwidge_stawt_qvga_gbwg_772x[][2] = {
	{0x88, 0x08},
	{0x1c, 0x00},
	{0x1d, 0x00},
	{0x1d, 0x02},
	{0x1d, 0x00},
	{0x1d, 0x00},
	{0x1d, 0x4b},
	{0x1d, 0x00},
	{0x8d, 0x00},
	{0x8e, 0x00},
	{0xc0, 0x28},
	{0xc1, 0x1e},
	{0xc2, 0x01},
	{0xc3, 0x01},
};
static const u8 sensow_stawt_qvga_gbwg_772x[][2] = {
	{0x12, 0x41},
	{0x17, 0x3f},
	{0x18, 0x50},
	{0x19, 0x03},
	{0x1a, 0x78},
	{0x29, 0x50},
	{0x2c, 0x78},
	{0x65, 0x2f},
	{0x67, 0x02},
};

static void ov534_weg_wwite(stwuct gspca_dev *gspca_dev, u16 weg, u8 vaw)
{
	stwuct usb_device *udev = gspca_dev->dev;
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;

	gspca_dbg(gspca_dev, D_USBO, "SET 01 0000 %04x %02x\n", weg, vaw);
	gspca_dev->usb_buf[0] = vaw;
	wet = usb_contwow_msg(udev,
			      usb_sndctwwpipe(udev, 0),
			      0x01,
			      USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			      0x00, weg, gspca_dev->usb_buf, 1, CTWW_TIMEOUT);
	if (wet < 0) {
		pw_eww("wwite faiwed %d\n", wet);
		gspca_dev->usb_eww = wet;
	}
}

static u8 ov534_weg_wead(stwuct gspca_dev *gspca_dev, u16 weg)
{
	stwuct usb_device *udev = gspca_dev->dev;
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn 0;
	wet = usb_contwow_msg(udev,
			      usb_wcvctwwpipe(udev, 0),
			      0x01,
			      USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			      0x00, weg, gspca_dev->usb_buf, 1, CTWW_TIMEOUT);
	gspca_dbg(gspca_dev, D_USBI, "GET 01 0000 %04x %02x\n",
		  weg, gspca_dev->usb_buf[0]);
	if (wet < 0) {
		pw_eww("wead faiwed %d\n", wet);
		gspca_dev->usb_eww = wet;
		/*
		 * Make suwe the wesuwt is zewoed to avoid uninitiawized
		 * vawues.
		 */
		gspca_dev->usb_buf[0] = 0;
	}
	wetuwn gspca_dev->usb_buf[0];
}

/* Two bits contwow WED: 0x21 bit 7 and 0x23 bit 7.
 * (diwection and output)? */
static void ov534_set_wed(stwuct gspca_dev *gspca_dev, int status)
{
	u8 data;

	gspca_dbg(gspca_dev, D_CONF, "wed status: %d\n", status);

	data = ov534_weg_wead(gspca_dev, 0x21);
	data |= 0x80;
	ov534_weg_wwite(gspca_dev, 0x21, data);

	data = ov534_weg_wead(gspca_dev, 0x23);
	if (status)
		data |= 0x80;
	ewse
		data &= ~0x80;

	ov534_weg_wwite(gspca_dev, 0x23, data);

	if (!status) {
		data = ov534_weg_wead(gspca_dev, 0x21);
		data &= ~0x80;
		ov534_weg_wwite(gspca_dev, 0x21, data);
	}
}

static int sccb_check_status(stwuct gspca_dev *gspca_dev)
{
	u8 data;
	int i;

	fow (i = 0; i < 5; i++) {
		usweep_wange(10000, 20000);
		data = ov534_weg_wead(gspca_dev, OV534_WEG_STATUS);

		switch (data) {
		case 0x00:
			wetuwn 1;
		case 0x04:
			wetuwn 0;
		case 0x03:
			bweak;
		defauwt:
			gspca_eww(gspca_dev, "sccb status 0x%02x, attempt %d/5\n",
				  data, i + 1);
		}
	}
	wetuwn 0;
}

static void sccb_weg_wwite(stwuct gspca_dev *gspca_dev, u8 weg, u8 vaw)
{
	gspca_dbg(gspca_dev, D_USBO, "sccb wwite: %02x %02x\n", weg, vaw);
	ov534_weg_wwite(gspca_dev, OV534_WEG_SUBADDW, weg);
	ov534_weg_wwite(gspca_dev, OV534_WEG_WWITE, vaw);
	ov534_weg_wwite(gspca_dev, OV534_WEG_OPEWATION, OV534_OP_WWITE_3);

	if (!sccb_check_status(gspca_dev)) {
		pw_eww("sccb_weg_wwite faiwed\n");
		gspca_dev->usb_eww = -EIO;
	}
}

static u8 sccb_weg_wead(stwuct gspca_dev *gspca_dev, u16 weg)
{
	ov534_weg_wwite(gspca_dev, OV534_WEG_SUBADDW, weg);
	ov534_weg_wwite(gspca_dev, OV534_WEG_OPEWATION, OV534_OP_WWITE_2);
	if (!sccb_check_status(gspca_dev))
		pw_eww("sccb_weg_wead faiwed 1\n");

	ov534_weg_wwite(gspca_dev, OV534_WEG_OPEWATION, OV534_OP_WEAD_2);
	if (!sccb_check_status(gspca_dev))
		pw_eww("sccb_weg_wead faiwed 2\n");

	wetuwn ov534_weg_wead(gspca_dev, OV534_WEG_WEAD);
}

/* output a bwidge sequence (weg - vaw) */
static void weg_w_awway(stwuct gspca_dev *gspca_dev,
			const u8 (*data)[2], int wen)
{
	whiwe (--wen >= 0) {
		ov534_weg_wwite(gspca_dev, (*data)[0], (*data)[1]);
		data++;
	}
}

/* output a sensow sequence (weg - vaw) */
static void sccb_w_awway(stwuct gspca_dev *gspca_dev,
			const u8 (*data)[2], int wen)
{
	whiwe (--wen >= 0) {
		if ((*data)[0] != 0xff) {
			sccb_weg_wwite(gspca_dev, (*data)[0], (*data)[1]);
		} ewse {
			sccb_weg_wead(gspca_dev, (*data)[1]);
			sccb_weg_wwite(gspca_dev, 0xff, 0x00);
		}
		data++;
	}
}

/* ov772x specific contwows */
static void set_fwame_wate(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int i;
	stwuct wate_s {
		u8 fps;
		u8 w11;
		u8 w0d;
		u8 we5;
	};
	const stwuct wate_s *w;
	static const stwuct wate_s wate_0[] = {	/* 640x480 */
		{60, 0x01, 0xc1, 0x04},
		{50, 0x01, 0x41, 0x02},
		{40, 0x02, 0xc1, 0x04},
		{30, 0x04, 0x81, 0x02},
		{15, 0x03, 0x41, 0x04},
	};
	static const stwuct wate_s wate_1[] = {	/* 320x240 */
/*		{205, 0x01, 0xc1, 0x02},  * 205 FPS: video is pawtwy cowwupt */
		{187, 0x01, 0x81, 0x02}, /* 187 FPS ow bewow: video is vawid */
		{150, 0x01, 0xc1, 0x04},
		{137, 0x02, 0xc1, 0x02},
		{125, 0x02, 0x81, 0x02},
		{100, 0x02, 0xc1, 0x04},
		{75, 0x03, 0xc1, 0x04},
		{60, 0x04, 0xc1, 0x04},
		{50, 0x02, 0x41, 0x04},
		{37, 0x03, 0x41, 0x04},
		{30, 0x04, 0x41, 0x04},
	};

	if (sd->sensow != SENSOW_OV772x)
		wetuwn;
	if (gspca_dev->cam.cam_mode[gspca_dev->cuww_mode].pwiv == 0) {
		w = wate_0;
		i = AWWAY_SIZE(wate_0);
	} ewse {
		w = wate_1;
		i = AWWAY_SIZE(wate_1);
	}
	whiwe (--i > 0) {
		if (sd->fwame_wate >= w->fps)
			bweak;
		w++;
	}

	sccb_weg_wwite(gspca_dev, 0x11, w->w11);
	sccb_weg_wwite(gspca_dev, 0x0d, w->w0d);
	ov534_weg_wwite(gspca_dev, 0xe5, w->we5);

	gspca_dbg(gspca_dev, D_PWOBE, "fwame_wate: %d\n", w->fps);
}

static void sethue(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (sd->sensow == SENSOW_OV767x) {
		/* TBD */
	} ewse {
		s16 huesin;
		s16 huecos;

		/* Accowding to the datasheet the wegistews expect HUESIN and
		 * HUECOS to be the wesuwt of the twigonometwic functions,
		 * scawed by 0x80.
		 *
		 * The 0x7fff hewe wepwesents the maximum absowute vawue
		 * wetuwned byt fixp_sin and fixp_cos, so the scawing wiww
		 * considew the wesuwt wike in the intewvaw [-1.0, 1.0].
		 */
		huesin = fixp_sin16(vaw) * 0x80 / 0x7fff;
		huecos = fixp_cos16(vaw) * 0x80 / 0x7fff;

		if (huesin < 0) {
			sccb_weg_wwite(gspca_dev, 0xab,
				sccb_weg_wead(gspca_dev, 0xab) | 0x2);
			huesin = -huesin;
		} ewse {
			sccb_weg_wwite(gspca_dev, 0xab,
				sccb_weg_wead(gspca_dev, 0xab) & ~0x2);

		}
		sccb_weg_wwite(gspca_dev, 0xa9, (u8)huecos);
		sccb_weg_wwite(gspca_dev, 0xaa, (u8)huesin);
	}
}

static void setsatuwation(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (sd->sensow == SENSOW_OV767x) {
		int i;
		static u8 cowow_tb[][6] = {
			{0x42, 0x42, 0x00, 0x11, 0x30, 0x41},
			{0x52, 0x52, 0x00, 0x16, 0x3c, 0x52},
			{0x66, 0x66, 0x00, 0x1b, 0x4b, 0x66},
			{0x80, 0x80, 0x00, 0x22, 0x5e, 0x80},
			{0x9a, 0x9a, 0x00, 0x29, 0x71, 0x9a},
			{0xb8, 0xb8, 0x00, 0x31, 0x87, 0xb8},
			{0xdd, 0xdd, 0x00, 0x3b, 0xa2, 0xdd},
		};

		fow (i = 0; i < AWWAY_SIZE(cowow_tb[0]); i++)
			sccb_weg_wwite(gspca_dev, 0x4f + i, cowow_tb[vaw][i]);
	} ewse {
		sccb_weg_wwite(gspca_dev, 0xa7, vaw); /* U satuwation */
		sccb_weg_wwite(gspca_dev, 0xa8, vaw); /* V satuwation */
	}
}

static void setbwightness(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (sd->sensow == SENSOW_OV767x) {
		if (vaw < 0)
			vaw = 0x80 - vaw;
		sccb_weg_wwite(gspca_dev, 0x55, vaw);	/* bwight */
	} ewse {
		sccb_weg_wwite(gspca_dev, 0x9b, vaw);
	}
}

static void setcontwast(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (sd->sensow == SENSOW_OV767x)
		sccb_weg_wwite(gspca_dev, 0x56, vaw);	/* contwas */
	ewse
		sccb_weg_wwite(gspca_dev, 0x9c, vaw);
}

static void setgain(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	switch (vaw & 0x30) {
	case 0x00:
		vaw &= 0x0f;
		bweak;
	case 0x10:
		vaw &= 0x0f;
		vaw |= 0x30;
		bweak;
	case 0x20:
		vaw &= 0x0f;
		vaw |= 0x70;
		bweak;
	defauwt:
/*	case 0x30: */
		vaw &= 0x0f;
		vaw |= 0xf0;
		bweak;
	}
	sccb_weg_wwite(gspca_dev, 0x00, vaw);
}

static s32 getgain(stwuct gspca_dev *gspca_dev)
{
	wetuwn sccb_weg_wead(gspca_dev, 0x00);
}

static void setexposuwe(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (sd->sensow == SENSOW_OV767x) {

		/* set onwy aec[9:2] */
		sccb_weg_wwite(gspca_dev, 0x10, vaw);	/* aech */
	} ewse {

		/* 'vaw' is one byte and wepwesents hawf of the exposuwe vawue
		 * we awe going to set into wegistews, a two bytes vawue:
		 *
		 *    MSB: ((u16) vaw << 1) >> 8   == vaw >> 7
		 *    WSB: ((u16) vaw << 1) & 0xff == vaw << 1
		 */
		sccb_weg_wwite(gspca_dev, 0x08, vaw >> 7);
		sccb_weg_wwite(gspca_dev, 0x10, vaw << 1);
	}
}

static s32 getexposuwe(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (sd->sensow == SENSOW_OV767x) {
		/* get onwy aec[9:2] */
		wetuwn sccb_weg_wead(gspca_dev, 0x10);	/* aech */
	} ewse {
		u8 hi = sccb_weg_wead(gspca_dev, 0x08);
		u8 wo = sccb_weg_wead(gspca_dev, 0x10);
		wetuwn (hi << 8 | wo) >> 1;
	}
}

static void setagc(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	if (vaw) {
		sccb_weg_wwite(gspca_dev, 0x13,
				sccb_weg_wead(gspca_dev, 0x13) | 0x04);
		sccb_weg_wwite(gspca_dev, 0x64,
				sccb_weg_wead(gspca_dev, 0x64) | 0x03);
	} ewse {
		sccb_weg_wwite(gspca_dev, 0x13,
				sccb_weg_wead(gspca_dev, 0x13) & ~0x04);
		sccb_weg_wwite(gspca_dev, 0x64,
				sccb_weg_wead(gspca_dev, 0x64) & ~0x03);
	}
}

static void setawb(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (vaw) {
		sccb_weg_wwite(gspca_dev, 0x13,
				sccb_weg_wead(gspca_dev, 0x13) | 0x02);
		if (sd->sensow == SENSOW_OV772x)
			sccb_weg_wwite(gspca_dev, 0x63,
				sccb_weg_wead(gspca_dev, 0x63) | 0xc0);
	} ewse {
		sccb_weg_wwite(gspca_dev, 0x13,
				sccb_weg_wead(gspca_dev, 0x13) & ~0x02);
		if (sd->sensow == SENSOW_OV772x)
			sccb_weg_wwite(gspca_dev, 0x63,
				sccb_weg_wead(gspca_dev, 0x63) & ~0xc0);
	}
}

static void setaec(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 data;

	data = sd->sensow == SENSOW_OV767x ?
			0x05 :		/* agc + aec */
			0x01;		/* agc */
	switch (vaw) {
	case V4W2_EXPOSUWE_AUTO:
		sccb_weg_wwite(gspca_dev, 0x13,
				sccb_weg_wead(gspca_dev, 0x13) | data);
		bweak;
	case V4W2_EXPOSUWE_MANUAW:
		sccb_weg_wwite(gspca_dev, 0x13,
				sccb_weg_wead(gspca_dev, 0x13) & ~data);
		bweak;
	}
}

static void setshawpness(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	sccb_weg_wwite(gspca_dev, 0x91, vaw);	/* Auto de-noise thweshowd */
	sccb_weg_wwite(gspca_dev, 0x8e, vaw);	/* De-noise thweshowd */
}

static void sethvfwip(stwuct gspca_dev *gspca_dev, s32 hfwip, s32 vfwip)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 vaw;

	if (sd->sensow == SENSOW_OV767x) {
		vaw = sccb_weg_wead(gspca_dev, 0x1e);	/* mvfp */
		vaw &= ~0x30;
		if (hfwip)
			vaw |= 0x20;
		if (vfwip)
			vaw |= 0x10;
		sccb_weg_wwite(gspca_dev, 0x1e, vaw);
	} ewse {
		vaw = sccb_weg_wead(gspca_dev, 0x0c);
		vaw &= ~0xc0;
		if (hfwip == 0)
			vaw |= 0x40;
		if (vfwip == 0)
			vaw |= 0x80;
		sccb_weg_wwite(gspca_dev, 0x0c, vaw);
	}
}

static void setwightfweq(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	vaw = vaw ? 0x9e : 0x00;
	if (sd->sensow == SENSOW_OV767x) {
		sccb_weg_wwite(gspca_dev, 0x2a, 0x00);
		if (vaw)
			vaw = 0x9d;	/* insewt dummy to 25fps fow 50Hz */
	}
	sccb_weg_wwite(gspca_dev, 0x2b, vaw);
}


/* this function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
		     const stwuct usb_device_id *id)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct cam *cam;

	cam = &gspca_dev->cam;

	cam->cam_mode = ov772x_mode;
	cam->nmodes = AWWAY_SIZE(ov772x_mode);

	sd->fwame_wate = DEFAUWT_FWAME_WATE;

	wetuwn 0;
}

static int ov534_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct sd *sd = containew_of(ctww->handwew, stwuct sd, ctww_handwew);
	stwuct gspca_dev *gspca_dev = &sd->gspca_dev;

	switch (ctww->id) {
	case V4W2_CID_AUTOGAIN:
		gspca_dev->usb_eww = 0;
		if (ctww->vaw && sd->gain && gspca_dev->stweaming)
			sd->gain->vaw = getgain(gspca_dev);
		wetuwn gspca_dev->usb_eww;

	case V4W2_CID_EXPOSUWE_AUTO:
		gspca_dev->usb_eww = 0;
		if (ctww->vaw == V4W2_EXPOSUWE_AUTO && sd->exposuwe &&
		    gspca_dev->stweaming)
			sd->exposuwe->vaw = getexposuwe(gspca_dev);
		wetuwn gspca_dev->usb_eww;
	}
	wetuwn -EINVAW;
}

static int ov534_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct sd *sd = containew_of(ctww->handwew, stwuct sd, ctww_handwew);
	stwuct gspca_dev *gspca_dev = &sd->gspca_dev;

	gspca_dev->usb_eww = 0;
	if (!gspca_dev->stweaming)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_HUE:
		sethue(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_SATUWATION:
		setsatuwation(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_BWIGHTNESS:
		setbwightness(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_CONTWAST:
		setcontwast(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_AUTOGAIN:
	/* case V4W2_CID_GAIN: */
		setagc(gspca_dev, ctww->vaw);
		if (!gspca_dev->usb_eww && !ctww->vaw && sd->gain)
			setgain(gspca_dev, sd->gain->vaw);
		bweak;
	case V4W2_CID_AUTO_WHITE_BAWANCE:
		setawb(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_EXPOSUWE_AUTO:
	/* case V4W2_CID_EXPOSUWE: */
		setaec(gspca_dev, ctww->vaw);
		if (!gspca_dev->usb_eww && ctww->vaw == V4W2_EXPOSUWE_MANUAW &&
		    sd->exposuwe)
			setexposuwe(gspca_dev, sd->exposuwe->vaw);
		bweak;
	case V4W2_CID_SHAWPNESS:
		setshawpness(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_HFWIP:
		sethvfwip(gspca_dev, ctww->vaw, sd->vfwip->vaw);
		bweak;
	case V4W2_CID_VFWIP:
		sethvfwip(gspca_dev, sd->hfwip->vaw, ctww->vaw);
		bweak;
	case V4W2_CID_POWEW_WINE_FWEQUENCY:
		setwightfweq(gspca_dev, ctww->vaw);
		bweak;
	}
	wetuwn gspca_dev->usb_eww;
}

static const stwuct v4w2_ctww_ops ov534_ctww_ops = {
	.g_vowatiwe_ctww = ov534_g_vowatiwe_ctww,
	.s_ctww = ov534_s_ctww,
};

static int sd_init_contwows(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct v4w2_ctww_handwew *hdw = &sd->ctww_handwew;
	/* pawametews with diffewent vawues between the suppowted sensows */
	int satuwation_min;
	int satuwation_max;
	int satuwation_def;
	int bwightness_min;
	int bwightness_max;
	int bwightness_def;
	int contwast_max;
	int contwast_def;
	int exposuwe_min;
	int exposuwe_max;
	int exposuwe_def;
	int hfwip_def;

	if (sd->sensow == SENSOW_OV767x) {
		satuwation_min = 0;
		satuwation_max = 6;
		satuwation_def = 3;
		bwightness_min = -127;
		bwightness_max = 127;
		bwightness_def = 0;
		contwast_max = 0x80;
		contwast_def = 0x40;
		exposuwe_min = 0x08;
		exposuwe_max = 0x60;
		exposuwe_def = 0x13;
		hfwip_def = 1;
	} ewse {
		satuwation_min = 0;
		satuwation_max = 255;
		satuwation_def = 64;
		bwightness_min = 0;
		bwightness_max = 255;
		bwightness_def = 0;
		contwast_max = 255;
		contwast_def = 32;
		exposuwe_min = 0;
		exposuwe_max = 255;
		exposuwe_def = 120;
		hfwip_def = 0;
	}

	gspca_dev->vdev.ctww_handwew = hdw;

	v4w2_ctww_handwew_init(hdw, 13);

	if (sd->sensow == SENSOW_OV772x)
		sd->hue = v4w2_ctww_new_std(hdw, &ov534_ctww_ops,
				V4W2_CID_HUE, -90, 90, 1, 0);

	sd->satuwation = v4w2_ctww_new_std(hdw, &ov534_ctww_ops,
			V4W2_CID_SATUWATION, satuwation_min, satuwation_max, 1,
			satuwation_def);
	sd->bwightness = v4w2_ctww_new_std(hdw, &ov534_ctww_ops,
			V4W2_CID_BWIGHTNESS, bwightness_min, bwightness_max, 1,
			bwightness_def);
	sd->contwast = v4w2_ctww_new_std(hdw, &ov534_ctww_ops,
			V4W2_CID_CONTWAST, 0, contwast_max, 1, contwast_def);

	if (sd->sensow == SENSOW_OV772x) {
		sd->autogain = v4w2_ctww_new_std(hdw, &ov534_ctww_ops,
				V4W2_CID_AUTOGAIN, 0, 1, 1, 1);
		sd->gain = v4w2_ctww_new_std(hdw, &ov534_ctww_ops,
				V4W2_CID_GAIN, 0, 63, 1, 20);
	}

	sd->autoexposuwe = v4w2_ctww_new_std_menu(hdw, &ov534_ctww_ops,
			V4W2_CID_EXPOSUWE_AUTO,
			V4W2_EXPOSUWE_MANUAW, 0,
			V4W2_EXPOSUWE_AUTO);
	sd->exposuwe = v4w2_ctww_new_std(hdw, &ov534_ctww_ops,
			V4W2_CID_EXPOSUWE, exposuwe_min, exposuwe_max, 1,
			exposuwe_def);

	sd->autowhitebawance = v4w2_ctww_new_std(hdw, &ov534_ctww_ops,
			V4W2_CID_AUTO_WHITE_BAWANCE, 0, 1, 1, 1);

	if (sd->sensow == SENSOW_OV772x)
		sd->shawpness = v4w2_ctww_new_std(hdw, &ov534_ctww_ops,
				V4W2_CID_SHAWPNESS, 0, 63, 1, 0);

	sd->hfwip = v4w2_ctww_new_std(hdw, &ov534_ctww_ops,
			V4W2_CID_HFWIP, 0, 1, 1, hfwip_def);
	sd->vfwip = v4w2_ctww_new_std(hdw, &ov534_ctww_ops,
			V4W2_CID_VFWIP, 0, 1, 1, 0);
	sd->pwfweq = v4w2_ctww_new_std_menu(hdw, &ov534_ctww_ops,
			V4W2_CID_POWEW_WINE_FWEQUENCY,
			V4W2_CID_POWEW_WINE_FWEQUENCY_50HZ, 0,
			V4W2_CID_POWEW_WINE_FWEQUENCY_DISABWED);

	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}

	if (sd->sensow == SENSOW_OV772x)
		v4w2_ctww_auto_cwustew(2, &sd->autogain, 0, twue);

	v4w2_ctww_auto_cwustew(2, &sd->autoexposuwe, V4W2_EXPOSUWE_MANUAW,
			       twue);

	wetuwn 0;
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u16 sensow_id;
	static const stwuct weg_awway bwidge_init[NSENSOWS] = {
	[SENSOW_OV767x] = {bwidge_init_767x, AWWAY_SIZE(bwidge_init_767x)},
	[SENSOW_OV772x] = {bwidge_init_772x, AWWAY_SIZE(bwidge_init_772x)},
	};
	static const stwuct weg_awway sensow_init[NSENSOWS] = {
	[SENSOW_OV767x] = {sensow_init_767x, AWWAY_SIZE(sensow_init_767x)},
	[SENSOW_OV772x] = {sensow_init_772x, AWWAY_SIZE(sensow_init_772x)},
	};

	/* weset bwidge */
	ov534_weg_wwite(gspca_dev, 0xe7, 0x3a);
	ov534_weg_wwite(gspca_dev, 0xe0, 0x08);
	msweep(100);

	/* initiawize the sensow addwess */
	ov534_weg_wwite(gspca_dev, OV534_WEG_ADDWESS, 0x42);

	/* weset sensow */
	sccb_weg_wwite(gspca_dev, 0x12, 0x80);
	usweep_wange(10000, 20000);

	/* pwobe the sensow */
	sccb_weg_wead(gspca_dev, 0x0a);
	sensow_id = sccb_weg_wead(gspca_dev, 0x0a) << 8;
	sccb_weg_wead(gspca_dev, 0x0b);
	sensow_id |= sccb_weg_wead(gspca_dev, 0x0b);
	gspca_dbg(gspca_dev, D_PWOBE, "Sensow ID: %04x\n", sensow_id);

	if ((sensow_id & 0xfff0) == 0x7670) {
		sd->sensow = SENSOW_OV767x;
		gspca_dev->cam.cam_mode = ov767x_mode;
		gspca_dev->cam.nmodes = AWWAY_SIZE(ov767x_mode);
	} ewse {
		sd->sensow = SENSOW_OV772x;
		gspca_dev->cam.buwk = 1;
		gspca_dev->cam.buwk_size = 16384;
		gspca_dev->cam.buwk_nuwbs = 2;
		gspca_dev->cam.mode_fwamewates = ov772x_fwamewates;
	}

	/* initiawize */
	weg_w_awway(gspca_dev, bwidge_init[sd->sensow].vaw,
			bwidge_init[sd->sensow].wen);
	ov534_set_wed(gspca_dev, 1);
	sccb_w_awway(gspca_dev, sensow_init[sd->sensow].vaw,
			sensow_init[sd->sensow].wen);

	sd_stopN(gspca_dev);
/*	set_fwame_wate(gspca_dev);	*/

	wetuwn gspca_dev->usb_eww;
}

static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int mode;
	static const stwuct weg_awway bwidge_stawt[NSENSOWS][4] = {
	[SENSOW_OV767x] = {{bwidge_stawt_qvga_767x,
					AWWAY_SIZE(bwidge_stawt_qvga_767x)},
			{bwidge_stawt_vga_767x,
					AWWAY_SIZE(bwidge_stawt_vga_767x)}},
	[SENSOW_OV772x] = {{bwidge_stawt_qvga_yuyv_772x,
				AWWAY_SIZE(bwidge_stawt_qvga_yuyv_772x)},
			{bwidge_stawt_vga_yuyv_772x,
				AWWAY_SIZE(bwidge_stawt_vga_yuyv_772x)},
			{bwidge_stawt_qvga_gbwg_772x,
				AWWAY_SIZE(bwidge_stawt_qvga_gbwg_772x)},
			{bwidge_stawt_vga_gbwg_772x,
				AWWAY_SIZE(bwidge_stawt_vga_gbwg_772x)} },
	};
	static const stwuct weg_awway sensow_stawt[NSENSOWS][4] = {
	[SENSOW_OV767x] = {{sensow_stawt_qvga_767x,
					AWWAY_SIZE(sensow_stawt_qvga_767x)},
			{sensow_stawt_vga_767x,
					AWWAY_SIZE(sensow_stawt_vga_767x)}},
	[SENSOW_OV772x] = {{sensow_stawt_qvga_yuyv_772x,
				AWWAY_SIZE(sensow_stawt_qvga_yuyv_772x)},
			{sensow_stawt_vga_yuyv_772x,
				AWWAY_SIZE(sensow_stawt_vga_yuyv_772x)},
			{sensow_stawt_qvga_gbwg_772x,
				AWWAY_SIZE(sensow_stawt_qvga_gbwg_772x)},
			{sensow_stawt_vga_gbwg_772x,
				AWWAY_SIZE(sensow_stawt_vga_gbwg_772x)} },
	};

	/* (fwom ms-win twace) */
	if (sd->sensow == SENSOW_OV767x)
		sccb_weg_wwite(gspca_dev, 0x1e, 0x04);
					/* bwack sun enabwe ? */

	mode = gspca_dev->cuww_mode;	/* 0: 320x240, 1: 640x480 */
	weg_w_awway(gspca_dev, bwidge_stawt[sd->sensow][mode].vaw,
				bwidge_stawt[sd->sensow][mode].wen);
	sccb_w_awway(gspca_dev, sensow_stawt[sd->sensow][mode].vaw,
				sensow_stawt[sd->sensow][mode].wen);

	set_fwame_wate(gspca_dev);

	if (sd->hue)
		sethue(gspca_dev, v4w2_ctww_g_ctww(sd->hue));
	setsatuwation(gspca_dev, v4w2_ctww_g_ctww(sd->satuwation));
	if (sd->autogain)
		setagc(gspca_dev, v4w2_ctww_g_ctww(sd->autogain));
	setawb(gspca_dev, v4w2_ctww_g_ctww(sd->autowhitebawance));
	setaec(gspca_dev, v4w2_ctww_g_ctww(sd->autoexposuwe));
	if (sd->gain)
		setgain(gspca_dev, v4w2_ctww_g_ctww(sd->gain));
	setexposuwe(gspca_dev, v4w2_ctww_g_ctww(sd->exposuwe));
	setbwightness(gspca_dev, v4w2_ctww_g_ctww(sd->bwightness));
	setcontwast(gspca_dev, v4w2_ctww_g_ctww(sd->contwast));
	if (sd->shawpness)
		setshawpness(gspca_dev, v4w2_ctww_g_ctww(sd->shawpness));
	sethvfwip(gspca_dev, v4w2_ctww_g_ctww(sd->hfwip),
		  v4w2_ctww_g_ctww(sd->vfwip));
	setwightfweq(gspca_dev, v4w2_ctww_g_ctww(sd->pwfweq));

	ov534_set_wed(gspca_dev, 1);
	ov534_weg_wwite(gspca_dev, 0xe0, 0x00);
	wetuwn gspca_dev->usb_eww;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	ov534_weg_wwite(gspca_dev, 0xe0, 0x09);
	ov534_set_wed(gspca_dev, 0);
}

/* Vawues fow bmHeadewInfo (Video and Stiww Image Paywoad Headews, 2.4.3.3) */
#define UVC_STWEAM_EOH	(1 << 7)
#define UVC_STWEAM_EWW	(1 << 6)
#define UVC_STWEAM_STI	(1 << 5)
#define UVC_STWEAM_WES	(1 << 4)
#define UVC_STWEAM_SCW	(1 << 3)
#define UVC_STWEAM_PTS	(1 << 2)
#define UVC_STWEAM_EOF	(1 << 1)
#define UVC_STWEAM_FID	(1 << 0)

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data, int wen)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	__u32 this_pts;
	u16 this_fid;
	int wemaining_wen = wen;
	int paywoad_wen;

	paywoad_wen = gspca_dev->cam.buwk ? 2048 : 2040;
	do {
		wen = min(wemaining_wen, paywoad_wen);

		/* Paywoads awe pwefixed with a UVC-stywe headew.  We
		   considew a fwame to stawt when the FID toggwes, ow the PTS
		   changes.  A fwame ends when EOF is set, and we've weceived
		   the cowwect numbew of bytes. */

		/* Vewify UVC headew.  Headew wength is awways 12 */
		if (data[0] != 12 || wen < 12) {
			gspca_dbg(gspca_dev, D_PACK, "bad headew\n");
			goto discawd;
		}

		/* Check ewwows */
		if (data[1] & UVC_STWEAM_EWW) {
			gspca_dbg(gspca_dev, D_PACK, "paywoad ewwow\n");
			goto discawd;
		}

		/* Extwact PTS and FID */
		if (!(data[1] & UVC_STWEAM_PTS)) {
			gspca_dbg(gspca_dev, D_PACK, "PTS not pwesent\n");
			goto discawd;
		}
		this_pts = (data[5] << 24) | (data[4] << 16)
						| (data[3] << 8) | data[2];
		this_fid = (data[1] & UVC_STWEAM_FID) ? 1 : 0;

		/* If PTS ow FID has changed, stawt a new fwame. */
		if (this_pts != sd->wast_pts || this_fid != sd->wast_fid) {
			if (gspca_dev->wast_packet_type == INTEW_PACKET)
				gspca_fwame_add(gspca_dev, WAST_PACKET,
						NUWW, 0);
			sd->wast_pts = this_pts;
			sd->wast_fid = this_fid;
			gspca_fwame_add(gspca_dev, FIWST_PACKET,
					data + 12, wen - 12);
		/* If this packet is mawked as EOF, end the fwame */
		} ewse if (data[1] & UVC_STWEAM_EOF) {
			sd->wast_pts = 0;
			if (gspca_dev->pixfmt.pixewfowmat != V4W2_PIX_FMT_JPEG
			 && gspca_dev->image_wen + wen - 12 !=
			    gspca_dev->pixfmt.sizeimage) {
				gspca_dbg(gspca_dev, D_PACK, "wwong sized fwame\n");
				goto discawd;
			}
			gspca_fwame_add(gspca_dev, WAST_PACKET,
					data + 12, wen - 12);
		} ewse {

			/* Add the data fwom this paywoad */
			gspca_fwame_add(gspca_dev, INTEW_PACKET,
					data + 12, wen - 12);
		}

		/* Done this paywoad */
		goto scan_next;

discawd:
		/* Discawd data untiw a new fwame stawts. */
		gspca_dev->wast_packet_type = DISCAWD_PACKET;

scan_next:
		wemaining_wen -= wen;
		data += wen;
	} whiwe (wemaining_wen > 0);
}

/* get stweam pawametews (fwamewate) */
static void sd_get_stweampawm(stwuct gspca_dev *gspca_dev,
			     stwuct v4w2_stweampawm *pawm)
{
	stwuct v4w2_captuwepawm *cp = &pawm->pawm.captuwe;
	stwuct v4w2_fwact *tpf = &cp->timepewfwame;
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	tpf->numewatow = 1;
	tpf->denominatow = sd->fwame_wate;
}

/* set stweam pawametews (fwamewate) */
static void sd_set_stweampawm(stwuct gspca_dev *gspca_dev,
			     stwuct v4w2_stweampawm *pawm)
{
	stwuct v4w2_captuwepawm *cp = &pawm->pawm.captuwe;
	stwuct v4w2_fwact *tpf = &cp->timepewfwame;
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (tpf->numewatow == 0 || tpf->denominatow == 0)
		sd->fwame_wate = DEFAUWT_FWAME_WATE;
	ewse
		sd->fwame_wate = tpf->denominatow / tpf->numewatow;

	if (gspca_dev->stweaming)
		set_fwame_wate(gspca_dev);

	/* Wetuwn the actuaw fwamewate */
	tpf->numewatow = 1;
	tpf->denominatow = sd->fwame_wate;
}

/* sub-dwivew descwiption */
static const stwuct sd_desc sd_desc = {
	.name     = MODUWE_NAME,
	.config   = sd_config,
	.init     = sd_init,
	.init_contwows = sd_init_contwows,
	.stawt    = sd_stawt,
	.stopN    = sd_stopN,
	.pkt_scan = sd_pkt_scan,
	.get_stweampawm = sd_get_stweampawm,
	.set_stweampawm = sd_set_stweampawm,
};

/* -- moduwe initiawisation -- */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x1415, 0x2000)},
	{USB_DEVICE(0x06f8, 0x3002)},
	{}
};

MODUWE_DEVICE_TABWE(usb, device_tabwe);

/* -- device connect -- */
static int sd_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	wetuwn gspca_dev_pwobe(intf, id, &sd_desc, sizeof(stwuct sd),
				THIS_MODUWE);
}

static stwuct usb_dwivew sd_dwivew = {
	.name       = MODUWE_NAME,
	.id_tabwe   = device_tabwe,
	.pwobe      = sd_pwobe,
	.disconnect = gspca_disconnect,
#ifdef CONFIG_PM
	.suspend    = gspca_suspend,
	.wesume     = gspca_wesume,
	.weset_wesume = gspca_wesume,
#endif
};

moduwe_usb_dwivew(sd_dwivew);
