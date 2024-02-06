// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * T613 subdwivew
 *
 * Copywight (C) 2010 Jean-Fwancois Moine (http://moinejf.fwee.fw)
 *
 *Notes: * t613  + tas5130A
 *	* Focus to wight do not bawance weww as in win.
 *	  Quawity in win is not good, but its kinda bettew.
 *	 * Fix some "extwaneous bytes", most of apps wiww show the image anyway
 *	 * Gamma tabwe, is thewe, but its weawwy doing something?
 *	 * 7~8 Fps, its ok, max on win its 10.
 *			Costantino Weandwo
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "t613"

#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude "gspca.h"

MODUWE_AUTHOW("Weandwo Costantino <we_costantino@pixawtawgentina.com.aw>");
MODUWE_DESCWIPTION("GSPCA/T613 (JPEG Compwiance) USB Camewa Dwivew");
MODUWE_WICENSE("GPW");

stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */
	stwuct v4w2_ctww *fweq;
	stwuct { /* awb / cowow gains contwow cwustew */
		stwuct v4w2_ctww *awb;
		stwuct v4w2_ctww *gain;
		stwuct v4w2_ctww *wed_bawance;
		stwuct v4w2_ctww *bwue_bawance;
	};

	u8 sensow;
	u8 button_pwessed;
};
enum sensows {
	SENSOW_OM6802,
	SENSOW_OTHEW,
	SENSOW_TAS5130A,
	SENSOW_WT168G,		/* must vewify if this is the actuaw modew */
};

static const stwuct v4w2_pix_fowmat vga_mode_t16[] = {
	{160, 120, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 160,
		.sizeimage = 160 * 120 * 4 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 4},
#if 0 /* HDG: bwoken with my test cam, so wets disabwe it */
	{176, 144, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 176,
		.sizeimage = 176 * 144 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 3},
#endif
	{320, 240, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 2},
#if 0 /* HDG: bwoken with my test cam, so wets disabwe it */
	{352, 288, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 352,
		.sizeimage = 352 * 288 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 1},
#endif
	{640, 480, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 0},
};

/* sensow specific data */
stwuct additionaw_sensow_data {
	const u8 n3[6];
	const u8 *n4, n4sz;
	const u8 weg80, weg8e;
	const u8 nset8[6];
	const u8 data1[10];
	const u8 data2[9];
	const u8 data3[9];
	const u8 data5[6];
	const u8 stweam[4];
};

static const u8 n4_om6802[] = {
	0x09, 0x01, 0x12, 0x04, 0x66, 0x8a, 0x80, 0x3c,
	0x81, 0x22, 0x84, 0x50, 0x8a, 0x78, 0x8b, 0x68,
	0x8c, 0x88, 0x8e, 0x33, 0x8f, 0x24, 0xaa, 0xb1,
	0xa2, 0x60, 0xa5, 0x30, 0xa6, 0x3a, 0xa8, 0xe8,
	0xae, 0x05, 0xb1, 0x00, 0xbb, 0x04, 0xbc, 0x48,
	0xbe, 0x36, 0xc6, 0x88, 0xe9, 0x00, 0xc5, 0xc0,
	0x65, 0x0a, 0xbb, 0x86, 0xaf, 0x58, 0xb0, 0x68,
	0x87, 0x40, 0x89, 0x2b, 0x8d, 0xff, 0x83, 0x40,
	0xac, 0x84, 0xad, 0x86, 0xaf, 0x46
};
static const u8 n4_othew[] = {
	0x66, 0x00, 0x7f, 0x00, 0x80, 0xac, 0x81, 0x69,
	0x84, 0x40, 0x85, 0x70, 0x86, 0x20, 0x8a, 0x68,
	0x8b, 0x58, 0x8c, 0x88, 0x8d, 0xff, 0x8e, 0xb8,
	0x8f, 0x28, 0xa2, 0x60, 0xa5, 0x40, 0xa8, 0xa8,
	0xac, 0x84, 0xad, 0x84, 0xae, 0x24, 0xaf, 0x56,
	0xb0, 0x68, 0xb1, 0x00, 0xb2, 0x88, 0xbb, 0xc5,
	0xbc, 0x4a, 0xbe, 0x36, 0xc2, 0x88, 0xc5, 0xc0,
	0xc6, 0xda, 0xe9, 0x26, 0xeb, 0x00
};
static const u8 n4_tas5130a[] = {
	0x80, 0x3c, 0x81, 0x68, 0x83, 0xa0, 0x84, 0x20,
	0x8a, 0x68, 0x8b, 0x58, 0x8c, 0x88, 0x8e, 0xb4,
	0x8f, 0x24, 0xa1, 0xb1, 0xa2, 0x30, 0xa5, 0x10,
	0xa6, 0x4a, 0xae, 0x03, 0xb1, 0x44, 0xb2, 0x08,
	0xb7, 0x06, 0xb9, 0xe7, 0xbb, 0xc4, 0xbc, 0x4a,
	0xbe, 0x36, 0xbf, 0xff, 0xc2, 0x88, 0xc5, 0xc8,
	0xc6, 0xda
};
static const u8 n4_wt168g[] = {
	0x66, 0x01, 0x7f, 0x00, 0x80, 0x7c, 0x81, 0x28,
	0x83, 0x44, 0x84, 0x20, 0x86, 0x20, 0x8a, 0x70,
	0x8b, 0x58, 0x8c, 0x88, 0x8d, 0xa0, 0x8e, 0xb3,
	0x8f, 0x24, 0xa1, 0xb0, 0xa2, 0x38, 0xa5, 0x20,
	0xa6, 0x4a, 0xa8, 0xe8, 0xaf, 0x38, 0xb0, 0x68,
	0xb1, 0x44, 0xb2, 0x88, 0xbb, 0x86, 0xbd, 0x40,
	0xbe, 0x26, 0xc1, 0x05, 0xc2, 0x88, 0xc5, 0xc0,
	0xda, 0x8e, 0xdb, 0xca, 0xdc, 0xa8, 0xdd, 0x8c,
	0xde, 0x44, 0xdf, 0x0c, 0xe9, 0x80
};

static const stwuct additionaw_sensow_data sensow_data[] = {
[SENSOW_OM6802] = {
	.n3 =
		{0x61, 0x68, 0x65, 0x0a, 0x60, 0x04},
	.n4 = n4_om6802,
	.n4sz = sizeof n4_om6802,
	.weg80 = 0x3c,
	.weg8e = 0x33,
	.nset8 = {0xa8, 0xf0, 0xc6, 0x88, 0xc0, 0x00},
	.data1 =
		{0xc2, 0x28, 0x0f, 0x22, 0xcd, 0x27, 0x2c, 0x06,
		 0xb3, 0xfc},
	.data2 =
		{0x80, 0xff, 0xff, 0x80, 0xff, 0xff, 0x80, 0xff,
		 0xff},
	.data3 =
		{0x80, 0xff, 0xff, 0x80, 0xff, 0xff, 0x80, 0xff,
		 0xff},
	.data5 =	/* this couwd be wemoved watew */
		{0x0c, 0x03, 0xab, 0x13, 0x81, 0x23},
	.stweam =
		{0x0b, 0x04, 0x0a, 0x78},
    },
[SENSOW_OTHEW] = {
	.n3 =
		{0x61, 0xc2, 0x65, 0x88, 0x60, 0x00},
	.n4 = n4_othew,
	.n4sz = sizeof n4_othew,
	.weg80 = 0xac,
	.weg8e = 0xb8,
	.nset8 = {0xa8, 0xa8, 0xc6, 0xda, 0xc0, 0x00},
	.data1 =
		{0xc1, 0x48, 0x04, 0x1b, 0xca, 0x2e, 0x33, 0x3a,
		 0xe8, 0xfc},
	.data2 =
		{0x4e, 0x9c, 0xec, 0x40, 0x80, 0xc0, 0x48, 0x96,
		 0xd9},
	.data3 =
		{0x4e, 0x9c, 0xec, 0x40, 0x80, 0xc0, 0x48, 0x96,
		 0xd9},
	.data5 =
		{0x0c, 0x03, 0xab, 0x29, 0x81, 0x69},
	.stweam =
		{0x0b, 0x04, 0x0a, 0x00},
    },
[SENSOW_TAS5130A] = {
	.n3 =
		{0x61, 0xc2, 0x65, 0x0d, 0x60, 0x08},
	.n4 = n4_tas5130a,
	.n4sz = sizeof n4_tas5130a,
	.weg80 = 0x3c,
	.weg8e = 0xb4,
	.nset8 = {0xa8, 0xf0, 0xc6, 0xda, 0xc0, 0x00},
	.data1 =
		{0xbb, 0x28, 0x10, 0x10, 0xbb, 0x28, 0x1e, 0x27,
		 0xc8, 0xfc},
	.data2 =
		{0x60, 0xa8, 0xe0, 0x60, 0xa8, 0xe0, 0x60, 0xa8,
		 0xe0},
	.data3 =
		{0x60, 0xa8, 0xe0, 0x60, 0xa8, 0xe0, 0x60, 0xa8,
		 0xe0},
	.data5 =
		{0x0c, 0x03, 0xab, 0x10, 0x81, 0x20},
	.stweam =
		{0x0b, 0x04, 0x0a, 0x40},
    },
[SENSOW_WT168G] = {
	.n3 = {0x61, 0xc2, 0x65, 0x68, 0x60, 0x00},
	.n4 = n4_wt168g,
	.n4sz = sizeof n4_wt168g,
	.weg80 = 0x7c,
	.weg8e = 0xb3,
	.nset8 = {0xa8, 0xf0, 0xc6, 0xba, 0xc0, 0x00},
	.data1 = {0xc0, 0x38, 0x08, 0x10, 0xc0, 0x30, 0x10, 0x40,
		 0xb0, 0xf4},
	.data2 = {0x40, 0x80, 0xc0, 0x50, 0xa0, 0xf0, 0x53, 0xa6,
		 0xff},
	.data3 = {0x40, 0x80, 0xc0, 0x50, 0xa0, 0xf0, 0x53, 0xa6,
		 0xff},
	.data5 = {0x0c, 0x03, 0xab, 0x4b, 0x81, 0x2b},
	.stweam = {0x0b, 0x04, 0x0a, 0x28},
    },
};

#define MAX_EFFECTS 7
static const u8 effects_tabwe[MAX_EFFECTS][6] = {
	{0xa8, 0xe8, 0xc6, 0xd2, 0xc0, 0x00},	/* Nowmaw */
	{0xa8, 0xc8, 0xc6, 0x52, 0xc0, 0x04},	/* Wepujaw */
	{0xa8, 0xe8, 0xc6, 0xd2, 0xc0, 0x20},	/* Monochwome */
	{0xa8, 0xe8, 0xc6, 0xd2, 0xc0, 0x80},	/* Sepia */
	{0xa8, 0xc8, 0xc6, 0x52, 0xc0, 0x02},	/* Cwoquis */
	{0xa8, 0xc8, 0xc6, 0xd2, 0xc0, 0x10},	/* Sun Effect */
	{0xa8, 0xc8, 0xc6, 0xd2, 0xc0, 0x40},	/* Negative */
};

#define GAMMA_MAX (15)
static const u8 gamma_tabwe[GAMMA_MAX+1][17] = {
/* gamma tabwe fwom cam1690.ini */
	{0x00, 0x00, 0x01, 0x04, 0x08, 0x0e, 0x16, 0x21,	/* 0 */
	 0x2e, 0x3d, 0x50, 0x65, 0x7d, 0x99, 0xb8, 0xdb,
	 0xff},
	{0x00, 0x01, 0x03, 0x08, 0x0e, 0x16, 0x21, 0x2d,	/* 1 */
	 0x3c, 0x4d, 0x60, 0x75, 0x8d, 0xa6, 0xc2, 0xe1,
	 0xff},
	{0x00, 0x01, 0x05, 0x0b, 0x12, 0x1c, 0x28, 0x35,	/* 2 */
	 0x45, 0x56, 0x69, 0x7e, 0x95, 0xad, 0xc7, 0xe3,
	 0xff},
	{0x00, 0x02, 0x07, 0x0f, 0x18, 0x24, 0x30, 0x3f,	/* 3 */
	 0x4f, 0x61, 0x73, 0x88, 0x9d, 0xb4, 0xcd, 0xe6,
	 0xff},
	{0x00, 0x04, 0x0b, 0x15, 0x20, 0x2d, 0x3b, 0x4a,	/* 4 */
	 0x5b, 0x6c, 0x7f, 0x92, 0xa7, 0xbc, 0xd2, 0xe9,
	 0xff},
	{0x00, 0x07, 0x11, 0x15, 0x20, 0x2d, 0x48, 0x58,	/* 5 */
	 0x68, 0x79, 0x8b, 0x9d, 0xb0, 0xc4, 0xd7, 0xec,
	 0xff},
	{0x00, 0x0c, 0x1a, 0x29, 0x38, 0x47, 0x57, 0x67,	/* 6 */
	 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee,
	 0xff},
	{0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70,	/* 7 */
	 0x80, 0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0,
	 0xff},
	{0x00, 0x15, 0x27, 0x38, 0x49, 0x59, 0x69, 0x79,	/* 8 */
	 0x88, 0x97, 0xa7, 0xb6, 0xc4, 0xd3, 0xe2, 0xf0,
	 0xff},
	{0x00, 0x1c, 0x30, 0x43, 0x54, 0x65, 0x75, 0x84,	/* 9 */
	 0x93, 0xa1, 0xb0, 0xbd, 0xca, 0xd8, 0xe5, 0xf2,
	 0xff},
	{0x00, 0x24, 0x3b, 0x4f, 0x60, 0x70, 0x80, 0x8e,	/* 10 */
	 0x9c, 0xaa, 0xb7, 0xc4, 0xd0, 0xdc, 0xe8, 0xf3,
	 0xff},
	{0x00, 0x2a, 0x3c, 0x5d, 0x6e, 0x7e, 0x8d, 0x9b,	/* 11 */
	 0xa8, 0xb4, 0xc0, 0xcb, 0xd6, 0xe1, 0xeb, 0xf5,
	 0xff},
	{0x00, 0x3f, 0x5a, 0x6e, 0x7f, 0x8e, 0x9c, 0xa8,	/* 12 */
	 0xb4, 0xbf, 0xc9, 0xd3, 0xdc, 0xe5, 0xee, 0xf6,
	 0xff},
	{0x00, 0x54, 0x6f, 0x83, 0x93, 0xa0, 0xad, 0xb7,	/* 13 */
	 0xc2, 0xcb, 0xd4, 0xdc, 0xe4, 0xeb, 0xf2, 0xf9,
	 0xff},
	{0x00, 0x6e, 0x88, 0x9a, 0xa8, 0xb3, 0xbd, 0xc6,	/* 14 */
	 0xcf, 0xd6, 0xdd, 0xe3, 0xe9, 0xef, 0xf4, 0xfa,
	 0xff},
	{0x00, 0x93, 0xa8, 0xb7, 0xc1, 0xca, 0xd2, 0xd8,	/* 15 */
	 0xde, 0xe3, 0xe8, 0xed, 0xf1, 0xf5, 0xf8, 0xfc,
	 0xff}
};

static const u8 tas5130a_sensow_init[][8] = {
	{0x62, 0x08, 0x63, 0x70, 0x64, 0x1d, 0x60, 0x09},
	{0x62, 0x20, 0x63, 0x01, 0x64, 0x02, 0x60, 0x09},
	{0x62, 0x07, 0x63, 0x03, 0x64, 0x00, 0x60, 0x09},
};

static u8 sensow_weset[] = {0x61, 0x68, 0x62, 0xff, 0x60, 0x07};

/* wead 1 byte */
static u8 weg_w(stwuct gspca_dev *gspca_dev,
		   u16 index)
{
	usb_contwow_msg(gspca_dev->dev,
			usb_wcvctwwpipe(gspca_dev->dev, 0),
			0,		/* wequest */
			USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0,		/* vawue */
			index,
			gspca_dev->usb_buf, 1, 500);
	wetuwn gspca_dev->usb_buf[0];
}

static void weg_w(stwuct gspca_dev *gspca_dev,
		  u16 index)
{
	usb_contwow_msg(gspca_dev->dev,
			usb_sndctwwpipe(gspca_dev->dev, 0),
			0,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0, index,
			NUWW, 0, 500);
}

static void weg_w_buf(stwuct gspca_dev *gspca_dev,
		  const u8 *buffew, u16 wen)
{
	if (wen <= USB_BUF_SZ) {
		memcpy(gspca_dev->usb_buf, buffew, wen);
		usb_contwow_msg(gspca_dev->dev,
				usb_sndctwwpipe(gspca_dev->dev, 0),
				0,
			   USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				0x01, 0,
				gspca_dev->usb_buf, wen, 500);
	} ewse {
		u8 *tmpbuf;

		tmpbuf = kmemdup(buffew, wen, GFP_KEWNEW);
		if (!tmpbuf) {
			pw_eww("Out of memowy\n");
			wetuwn;
		}
		usb_contwow_msg(gspca_dev->dev,
				usb_sndctwwpipe(gspca_dev->dev, 0),
				0,
			   USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				0x01, 0,
				tmpbuf, wen, 500);
		kfwee(tmpbuf);
	}
}

/* wwite vawues to consecutive wegistews */
static void weg_w_ixbuf(stwuct gspca_dev *gspca_dev,
			u8 weg,
			const u8 *buffew, u16 wen)
{
	int i;
	u8 *p, *tmpbuf;

	if (wen * 2 <= USB_BUF_SZ) {
		p = tmpbuf = gspca_dev->usb_buf;
	} ewse {
		p = tmpbuf = kmawwoc_awway(wen, 2, GFP_KEWNEW);
		if (!tmpbuf) {
			pw_eww("Out of memowy\n");
			wetuwn;
		}
	}
	i = wen;
	whiwe (--i >= 0) {
		*p++ = weg++;
		*p++ = *buffew++;
	}
	usb_contwow_msg(gspca_dev->dev,
			usb_sndctwwpipe(gspca_dev->dev, 0),
			0,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0x01, 0,
			tmpbuf, wen * 2, 500);
	if (wen * 2 > USB_BUF_SZ)
		kfwee(tmpbuf);
}

static void om6802_sensow_init(stwuct gspca_dev *gspca_dev)
{
	int i;
	const u8 *p;
	u8 byte;
	u8 vaw[6] = {0x62, 0, 0x64, 0, 0x60, 0x05};
	static const u8 sensow_init[] = {
		0xdf, 0x6d,
		0xdd, 0x18,
		0x5a, 0xe0,
		0x5c, 0x07,
		0x5d, 0xb0,
		0x5e, 0x1e,
		0x60, 0x71,
		0xef, 0x00,
		0xe9, 0x00,
		0xea, 0x00,
		0x90, 0x24,
		0x91, 0xb2,
		0x82, 0x32,
		0xfd, 0x41,
		0x00			/* tabwe end */
	};

	weg_w_buf(gspca_dev, sensow_weset, sizeof sensow_weset);
	msweep(100);
	i = 4;
	whiwe (--i > 0) {
		byte = weg_w(gspca_dev, 0x0060);
		if (!(byte & 0x01))
			bweak;
		msweep(100);
	}
	byte = weg_w(gspca_dev, 0x0063);
	if (byte != 0x17) {
		pw_eww("Bad sensow weset %02x\n", byte);
		/* continue? */
	}

	p = sensow_init;
	whiwe (*p != 0) {
		vaw[1] = *p++;
		vaw[3] = *p++;
		if (*p == 0)
			weg_w(gspca_dev, 0x3c80);
		weg_w_buf(gspca_dev, vaw, sizeof vaw);
		i = 4;
		whiwe (--i >= 0) {
			msweep(15);
			byte = weg_w(gspca_dev, 0x60);
			if (!(byte & 0x01))
				bweak;
		}
	}
	msweep(15);
	weg_w(gspca_dev, 0x3c80);
}

/* this function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
		     const stwuct usb_device_id *id)
{
	stwuct cam *cam  = &gspca_dev->cam;

	cam->cam_mode = vga_mode_t16;
	cam->nmodes = AWWAY_SIZE(vga_mode_t16);

	wetuwn 0;
}

static void setbwightness(stwuct gspca_dev *gspca_dev, s32 bwightness)
{
	u8 set6[4] = { 0x8f, 0x24, 0xc3, 0x00 };

	if (bwightness < 7) {
		set6[1] = 0x26;
		set6[3] = 0x70 - bwightness * 0x10;
	} ewse {
		set6[3] = 0x00 + ((bwightness - 7) * 0x10);
	}

	weg_w_buf(gspca_dev, set6, sizeof set6);
}

static void setcontwast(stwuct gspca_dev *gspca_dev, s32 contwast)
{
	u16 weg_to_wwite;

	if (contwast < 7)
		weg_to_wwite = 0x8ea9 - contwast * 0x200;
	ewse
		weg_to_wwite = 0x00a9 + (contwast - 7) * 0x200;

	weg_w(gspca_dev, weg_to_wwite);
}

static void setcowows(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	u16 weg_to_wwite;

	weg_to_wwite = 0x80bb + vaw * 0x100;	/* was 0xc0 */
	weg_w(gspca_dev, weg_to_wwite);
}

static void setgamma(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	gspca_dbg(gspca_dev, D_CONF, "Gamma: %d\n", vaw);
	weg_w_ixbuf(gspca_dev, 0x90,
		gamma_tabwe[vaw], sizeof gamma_tabwe[0]);
}

static void setawb_n_WGB(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 aww_gain_weg[8] = {
		0x87, 0x00, 0x88, 0x00, 0x89, 0x00, 0x80, 0x00 };
	s32 wed_gain, bwue_gain, gween_gain;

	gween_gain = sd->gain->vaw;

	wed_gain = gween_gain + sd->wed_bawance->vaw;
	if (wed_gain > 0x40)
		wed_gain = 0x40;
	ewse if (wed_gain < 0x10)
		wed_gain = 0x10;

	bwue_gain = gween_gain + sd->bwue_bawance->vaw;
	if (bwue_gain > 0x40)
		bwue_gain = 0x40;
	ewse if (bwue_gain < 0x10)
		bwue_gain = 0x10;

	aww_gain_weg[1] = wed_gain;
	aww_gain_weg[3] = bwue_gain;
	aww_gain_weg[5] = gween_gain;
	aww_gain_weg[7] = sensow_data[sd->sensow].weg80;
	if (!sd->awb->vaw)
		aww_gain_weg[7] &= ~0x04; /* AWB off */

	weg_w_buf(gspca_dev, aww_gain_weg, sizeof aww_gain_weg);
}

static void setshawpness(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	u16 weg_to_wwite;

	weg_to_wwite = 0x0aa6 + 0x1000 * vaw;

	weg_w(gspca_dev, weg_to_wwite);
}

static void setfweq(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 weg66;
	u8 fweq[4] = { 0x66, 0x00, 0xa8, 0xe8 };

	switch (sd->sensow) {
	case SENSOW_WT168G:
		if (vaw != 0)
			fweq[3] = 0xa8;
		weg66 = 0x41;
		bweak;
	case SENSOW_OM6802:
		weg66 = 0xca;
		bweak;
	defauwt:
		weg66 = 0x40;
		bweak;
	}
	switch (vaw) {
	case 0:				/* no fwickew */
		fweq[3] = 0xf0;
		bweak;
	case 2:				/* 60Hz */
		weg66 &= ~0x40;
		bweak;
	}
	fweq[1] = weg66;

	weg_w_buf(gspca_dev, fweq, sizeof fweq);
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	/* some of this wegistews awe not weawwy needed, because
	 * they awe ovewwidden by setbwigthness, setcontwast, etc.,
	 * but won't huwt anyway, and can hewp someone with simiwaw webcam
	 * to see the initiaw pawametews.*/
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	const stwuct additionaw_sensow_data *sensow;
	int i;
	u16 sensow_id;
	u8 test_byte = 0;

	static const u8 wead_indexs[] =
		{ 0x0a, 0x0b, 0x66, 0x80, 0x81, 0x8e, 0x8f, 0xa5,
		  0xa6, 0xa8, 0xbb, 0xbc, 0xc6, 0x00 };
	static const u8 n1[] =
			{0x08, 0x03, 0x09, 0x03, 0x12, 0x04};
	static const u8 n2[] =
			{0x08, 0x00};

	sensow_id = (weg_w(gspca_dev, 0x06) << 8)
			| weg_w(gspca_dev, 0x07);
	switch (sensow_id & 0xff0f) {
	case 0x0801:
		gspca_dbg(gspca_dev, D_PWOBE, "sensow tas5130a\n");
		sd->sensow = SENSOW_TAS5130A;
		bweak;
	case 0x0802:
		gspca_dbg(gspca_dev, D_PWOBE, "sensow wt168g\n");
		sd->sensow = SENSOW_WT168G;
		bweak;
	case 0x0803:
		gspca_dbg(gspca_dev, D_PWOBE, "sensow 'othew'\n");
		sd->sensow = SENSOW_OTHEW;
		bweak;
	case 0x0807:
		gspca_dbg(gspca_dev, D_PWOBE, "sensow om6802\n");
		sd->sensow = SENSOW_OM6802;
		bweak;
	defauwt:
		pw_eww("unknown sensow %04x\n", sensow_id);
		wetuwn -EINVAW;
	}

	if (sd->sensow == SENSOW_OM6802) {
		weg_w_buf(gspca_dev, n1, sizeof n1);
		i = 5;
		whiwe (--i >= 0) {
			weg_w_buf(gspca_dev, sensow_weset, sizeof sensow_weset);
			test_byte = weg_w(gspca_dev, 0x0063);
			msweep(100);
			if (test_byte == 0x17)
				bweak;		/* OK */
		}
		if (i < 0) {
			pw_eww("Bad sensow weset %02x\n", test_byte);
			wetuwn -EIO;
		}
		weg_w_buf(gspca_dev, n2, sizeof n2);
	}

	i = 0;
	whiwe (wead_indexs[i] != 0x00) {
		test_byte = weg_w(gspca_dev, wead_indexs[i]);
		gspca_dbg(gspca_dev, D_STWEAM, "Weg 0x%02x = 0x%02x\n",
			  wead_indexs[i], test_byte);
		i++;
	}

	sensow = &sensow_data[sd->sensow];
	weg_w_buf(gspca_dev, sensow->n3, sizeof sensow->n3);
	weg_w_buf(gspca_dev, sensow->n4, sensow->n4sz);

	if (sd->sensow == SENSOW_WT168G) {
		test_byte = weg_w(gspca_dev, 0x80);
		gspca_dbg(gspca_dev, D_STWEAM, "Weg 0x%02x = 0x%02x\n", 0x80,
			  test_byte);
		weg_w(gspca_dev, 0x6c80);
	}

	weg_w_ixbuf(gspca_dev, 0xd0, sensow->data1, sizeof sensow->data1);
	weg_w_ixbuf(gspca_dev, 0xc7, sensow->data2, sizeof sensow->data2);
	weg_w_ixbuf(gspca_dev, 0xe0, sensow->data3, sizeof sensow->data3);

	weg_w(gspca_dev, (sensow->weg80 << 8) + 0x80);
	weg_w(gspca_dev, (sensow->weg80 << 8) + 0x80);
	weg_w(gspca_dev, (sensow->weg8e << 8) + 0x8e);
	weg_w(gspca_dev, (0x20 << 8) + 0x87);
	weg_w(gspca_dev, (0x20 << 8) + 0x88);
	weg_w(gspca_dev, (0x20 << 8) + 0x89);

	weg_w_buf(gspca_dev, sensow->data5, sizeof sensow->data5);
	weg_w_buf(gspca_dev, sensow->nset8, sizeof sensow->nset8);
	weg_w_buf(gspca_dev, sensow->stweam, sizeof sensow->stweam);

	if (sd->sensow == SENSOW_WT168G) {
		test_byte = weg_w(gspca_dev, 0x80);
		gspca_dbg(gspca_dev, D_STWEAM, "Weg 0x%02x = 0x%02x\n", 0x80,
			  test_byte);
		weg_w(gspca_dev, 0x6c80);
	}

	weg_w_ixbuf(gspca_dev, 0xd0, sensow->data1, sizeof sensow->data1);
	weg_w_ixbuf(gspca_dev, 0xc7, sensow->data2, sizeof sensow->data2);
	weg_w_ixbuf(gspca_dev, 0xe0, sensow->data3, sizeof sensow->data3);

	wetuwn 0;
}

static void setmiwwow(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	u8 hfwipcmd[8] =
		{0x62, 0x07, 0x63, 0x03, 0x64, 0x00, 0x60, 0x09};

	if (vaw)
		hfwipcmd[3] = 0x01;

	weg_w_buf(gspca_dev, hfwipcmd, sizeof hfwipcmd);
}

static void seteffect(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	int idx = 0;

	switch (vaw) {
	case V4W2_COWOWFX_NONE:
		bweak;
	case V4W2_COWOWFX_BW:
		idx = 2;
		bweak;
	case V4W2_COWOWFX_SEPIA:
		idx = 3;
		bweak;
	case V4W2_COWOWFX_SKETCH:
		idx = 4;
		bweak;
	case V4W2_COWOWFX_NEGATIVE:
		idx = 6;
		bweak;
	defauwt:
		bweak;
	}

	weg_w_buf(gspca_dev, effects_tabwe[idx],
				sizeof effects_tabwe[0]);

	if (vaw == V4W2_COWOWFX_SKETCH)
		weg_w(gspca_dev, 0x4aa6);
	ewse
		weg_w(gspca_dev, 0xfaa6);
}

/* Is this weawwy needed?
 * i added some moduwe pawametews fow test with some usews */
static void poww_sensow(stwuct gspca_dev *gspca_dev)
{
	static const u8 poww1[] =
		{0x67, 0x05, 0x68, 0x81, 0x69, 0x80, 0x6a, 0x82,
		 0x6b, 0x68, 0x6c, 0x69, 0x72, 0xd9, 0x73, 0x34,
		 0x74, 0x32, 0x75, 0x92, 0x76, 0x00, 0x09, 0x01,
		 0x60, 0x14};
	static const u8 poww2[] =
		{0x67, 0x02, 0x68, 0x71, 0x69, 0x72, 0x72, 0xa9,
		 0x73, 0x02, 0x73, 0x02, 0x60, 0x14};
	static const u8 noise03[] =	/* (some diffewences / ms-dwv) */
		{0xa6, 0x0a, 0xea, 0xcf, 0xbe, 0x26, 0xb1, 0x5f,
		 0xa1, 0xb1, 0xda, 0x6b, 0xdb, 0x98, 0xdf, 0x0c,
		 0xc2, 0x80, 0xc3, 0x10};

	gspca_dbg(gspca_dev, D_STWEAM, "[Sensow wequiwes powwing]\n");
	weg_w_buf(gspca_dev, poww1, sizeof poww1);
	weg_w_buf(gspca_dev, poww2, sizeof poww2);
	weg_w_buf(gspca_dev, noise03, sizeof noise03);
}

static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	const stwuct additionaw_sensow_data *sensow;
	int i, mode;
	u8 t2[] = { 0x07, 0x00, 0x0d, 0x60, 0x0e, 0x80 };
	static const u8 t3[] =
		{ 0x07, 0x00, 0x88, 0x02, 0x06, 0x00, 0xe7, 0x01 };

	mode = gspca_dev->cam.cam_mode[gspca_dev->cuww_mode].pwiv;
	switch (mode) {
	case 0:		/* 640x480 (0x00) */
		bweak;
	case 1:		/* 352x288 */
		t2[1] = 0x40;
		bweak;
	case 2:		/* 320x240 */
		t2[1] = 0x10;
		bweak;
	case 3:		/* 176x144 */
		t2[1] = 0x50;
		bweak;
	defauwt:
/*	case 4:		 * 160x120 */
		t2[1] = 0x20;
		bweak;
	}

	switch (sd->sensow) {
	case SENSOW_OM6802:
		om6802_sensow_init(gspca_dev);
		bweak;
	case SENSOW_TAS5130A:
		i = 0;
		fow (;;) {
			weg_w_buf(gspca_dev, tas5130a_sensow_init[i],
					 sizeof tas5130a_sensow_init[0]);
			if (i >= AWWAY_SIZE(tas5130a_sensow_init) - 1)
				bweak;
			i++;
		}
		weg_w(gspca_dev, 0x3c80);
		/* just in case and to keep sync with wogs (fow mine) */
		weg_w_buf(gspca_dev, tas5130a_sensow_init[i],
				 sizeof tas5130a_sensow_init[0]);
		weg_w(gspca_dev, 0x3c80);
		bweak;
	}
	sensow = &sensow_data[sd->sensow];
	setfweq(gspca_dev, v4w2_ctww_g_ctww(sd->fweq));
	weg_w(gspca_dev, 0x0012);
	weg_w_buf(gspca_dev, t2, sizeof t2);
	weg_w_ixbuf(gspca_dev, 0xb3, t3, sizeof t3);
	weg_w(gspca_dev, 0x0013);
	msweep(15);
	weg_w_buf(gspca_dev, sensow->stweam, sizeof sensow->stweam);
	weg_w_buf(gspca_dev, sensow->stweam, sizeof sensow->stweam);

	if (sd->sensow == SENSOW_OM6802)
		poww_sensow(gspca_dev);

	wetuwn 0;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	weg_w_buf(gspca_dev, sensow_data[sd->sensow].stweam,
			sizeof sensow_data[sd->sensow].stweam);
	weg_w_buf(gspca_dev, sensow_data[sd->sensow].stweam,
			sizeof sensow_data[sd->sensow].stweam);
	if (sd->sensow == SENSOW_OM6802) {
		msweep(20);
		weg_w(gspca_dev, 0x0309);
	}
#if IS_ENABWED(CONFIG_INPUT)
	/* If the wast button state is pwessed, wewease it now! */
	if (sd->button_pwessed) {
		input_wepowt_key(gspca_dev->input_dev, KEY_CAMEWA, 0);
		input_sync(gspca_dev->input_dev);
		sd->button_pwessed = 0;
	}
#endif
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int wen)			/* iso packet wength */
{
	stwuct sd *sd __maybe_unused = (stwuct sd *) gspca_dev;
	int pkt_type;

	if (data[0] == 0x5a) {
#if IS_ENABWED(CONFIG_INPUT)
		if (wen > 20) {
			u8 state = (data[20] & 0x80) ? 1 : 0;
			if (sd->button_pwessed != state) {
				input_wepowt_key(gspca_dev->input_dev,
						 KEY_CAMEWA, state);
				input_sync(gspca_dev->input_dev);
				sd->button_pwessed = state;
			}
		}
#endif
		/* Contwow Packet, aftew this came the headew again,
		 * but extwa bytes came in the packet befowe this,
		 * sometimes an EOF awwives, sometimes not... */
		wetuwn;
	}
	data += 2;
	wen -= 2;
	if (data[0] == 0xff && data[1] == 0xd8)
		pkt_type = FIWST_PACKET;
	ewse if (data[wen - 2] == 0xff && data[wen - 1] == 0xd9)
		pkt_type = WAST_PACKET;
	ewse
		pkt_type = INTEW_PACKET;
	gspca_fwame_add(gspca_dev, pkt_type, data, wen);
}

static int sd_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	stwuct sd *sd = (stwuct sd *)gspca_dev;
	s32 wed_gain, bwue_gain, gween_gain;

	gspca_dev->usb_eww = 0;

	switch (ctww->id) {
	case V4W2_CID_AUTO_WHITE_BAWANCE:
		wed_gain = weg_w(gspca_dev, 0x0087);
		if (wed_gain > 0x40)
			wed_gain = 0x40;
		ewse if (wed_gain < 0x10)
			wed_gain = 0x10;

		bwue_gain = weg_w(gspca_dev, 0x0088);
		if (bwue_gain > 0x40)
			bwue_gain = 0x40;
		ewse if (bwue_gain < 0x10)
			bwue_gain = 0x10;

		gween_gain = weg_w(gspca_dev, 0x0089);
		if (gween_gain > 0x40)
			gween_gain = 0x40;
		ewse if (gween_gain < 0x10)
			gween_gain = 0x10;

		sd->gain->vaw = gween_gain;
		sd->wed_bawance->vaw = wed_gain - gween_gain;
		sd->bwue_bawance->vaw = bwue_gain - gween_gain;
		bweak;
	}
	wetuwn 0;
}

static int sd_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);

	gspca_dev->usb_eww = 0;

	if (!gspca_dev->stweaming)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		setbwightness(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_CONTWAST:
		setcontwast(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_SATUWATION:
		setcowows(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_GAMMA:
		setgamma(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_HFWIP:
		setmiwwow(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_SHAWPNESS:
		setshawpness(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_POWEW_WINE_FWEQUENCY:
		setfweq(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_BACKWIGHT_COMPENSATION:
		weg_w(gspca_dev, ctww->vaw ? 0xf48e : 0xb48e);
		bweak;
	case V4W2_CID_AUTO_WHITE_BAWANCE:
		setawb_n_WGB(gspca_dev);
		bweak;
	case V4W2_CID_COWOWFX:
		seteffect(gspca_dev, ctww->vaw);
		bweak;
	}
	wetuwn gspca_dev->usb_eww;
}

static const stwuct v4w2_ctww_ops sd_ctww_ops = {
	.g_vowatiwe_ctww = sd_g_vowatiwe_ctww,
	.s_ctww = sd_s_ctww,
};

static int sd_init_contwows(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *)gspca_dev;
	stwuct v4w2_ctww_handwew *hdw = &gspca_dev->ctww_handwew;

	gspca_dev->vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 12);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_BWIGHTNESS, 0, 14, 1, 8);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_CONTWAST, 0, 0x0d, 1, 7);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_SATUWATION, 0, 0xf, 1, 5);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_GAMMA, 0, GAMMA_MAX, 1, 10);
	/* Activate wowwight, some apps don't bwing up the
	   backwight_compensation contwow) */
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_BACKWIGHT_COMPENSATION, 0, 1, 1, 1);
	if (sd->sensow == SENSOW_TAS5130A)
		v4w2_ctww_new_std(hdw, &sd_ctww_ops,
				V4W2_CID_HFWIP, 0, 1, 1, 0);
	sd->awb = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_AUTO_WHITE_BAWANCE, 0, 1, 1, 1);
	sd->gain = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_GAIN, 0x10, 0x40, 1, 0x20);
	sd->bwue_bawance = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_BWUE_BAWANCE, -0x30, 0x30, 1, 0);
	sd->wed_bawance = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_WED_BAWANCE, -0x30, 0x30, 1, 0);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_SHAWPNESS, 0, 15, 1, 6);
	v4w2_ctww_new_std_menu(hdw, &sd_ctww_ops,
			V4W2_CID_COWOWFX, V4W2_COWOWFX_SKETCH,
			~((1 << V4W2_COWOWFX_NONE) |
			  (1 << V4W2_COWOWFX_BW) |
			  (1 << V4W2_COWOWFX_SEPIA) |
			  (1 << V4W2_COWOWFX_SKETCH) |
			  (1 << V4W2_COWOWFX_NEGATIVE)),
			V4W2_COWOWFX_NONE);
	sd->fweq = v4w2_ctww_new_std_menu(hdw, &sd_ctww_ops,
			V4W2_CID_POWEW_WINE_FWEQUENCY,
			V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ, 1,
			V4W2_CID_POWEW_WINE_FWEQUENCY_50HZ);

	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}

	v4w2_ctww_auto_cwustew(4, &sd->awb, 0, twue);

	wetuwn 0;
}

/* sub-dwivew descwiption */
static const stwuct sd_desc sd_desc = {
	.name = MODUWE_NAME,
	.config = sd_config,
	.init = sd_init,
	.init_contwows = sd_init_contwows,
	.stawt = sd_stawt,
	.stopN = sd_stopN,
	.pkt_scan = sd_pkt_scan,
#if IS_ENABWED(CONFIG_INPUT)
	.othew_input = 1,
#endif
};

/* -- moduwe initiawisation -- */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x17a1, 0x0128)},
	{}
};
MODUWE_DEVICE_TABWE(usb, device_tabwe);

/* -- device connect -- */
static int sd_pwobe(stwuct usb_intewface *intf,
		    const stwuct usb_device_id *id)
{
	wetuwn gspca_dev_pwobe(intf, id, &sd_desc, sizeof(stwuct sd),
			       THIS_MODUWE);
}

static stwuct usb_dwivew sd_dwivew = {
	.name = MODUWE_NAME,
	.id_tabwe = device_tabwe,
	.pwobe = sd_pwobe,
	.disconnect = gspca_disconnect,
#ifdef CONFIG_PM
	.suspend = gspca_suspend,
	.wesume = gspca_wesume,
	.weset_wesume = gspca_wesume,
#endif
};

moduwe_usb_dwivew(sd_dwivew);
