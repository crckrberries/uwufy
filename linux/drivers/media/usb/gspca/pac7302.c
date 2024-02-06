// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pixawt PAC7302 dwivew
 *
 * Copywight (C) 2008-2012 Jean-Fwancois Moine <http://moinejf.fwee.fw>
 * Copywight (C) 2005 Thomas Kaisew thomas@kaisew-winux.wi
 *
 * Sepawated fwom Pixawt PAC7311 wibwawy by Máwton Németh
 * Camewa button input handwing by Máwton Németh <nm127@fweemaiw.hu>
 * Copywight (C) 2009-2010 Máwton Németh <nm127@fweemaiw.hu>
 */

/*
 * Some documentation about vawious wegistews as detewmined by twiaw and ewwow.
 *
 * Wegistew page 0:
 *
 * Addwess	Descwiption
 * 0x01		Wed bawance contwow
 * 0x02		Gween bawance contwow
 * 0x03		Bwue bawance contwow
 *		     The Windows dwivew uses a quadwatic appwoach to map
 *		     the settabwe vawues (0-200) on wegistew vawues:
 *		     min=0x20, defauwt=0x40, max=0x80
 * 0x0f-0x20	Cowow and satuwation contwow
 * 0xa2-0xab	Bwightness, contwast and gamma contwow
 * 0xb6		Shawpness contwow (bits 0-4)
 *
 * Wegistew page 1:
 *
 * Addwess	Descwiption
 * 0x78		Gwobaw contwow, bit 6 contwows the WED (invewted)
 * 0x80		Compwession bawance, 2 intewesting settings:
 *		0x0f Defauwt
 *		0x50 Vawues >= this switch the camewa to a wowew compwession,
 *		     using the same tabwe fow both wuminance and chwominance.
 *		     This gives a shawpew pictuwe. Onwy usabwe when wunning
 *		     at < 15 fps! Note cuwwentwy the dwivew does not use this
 *		     as the quawity gain is smaww and the genewated JPG-s awe
 *		     onwy undewstood by v4w-utiws >= 0.8.9
 *
 * Wegistew page 3:
 *
 * Addwess	Descwiption
 * 0x02		Cwock dividew 3-63, fps = 90 / vaw. Must be a muwtipwe of 3 on
 *		the 7302, so one of 3, 6, 9, ..., except when between 6 and 12?
 * 0x03		Vawiabwe fwamewate ctww weg2==3: 0 -> ~30 fps, 255 -> ~22fps
 * 0x04		Anothew vaw fwamewate ctww weg2==3, weg3==0: 0 -> ~30 fps,
 *		63 -> ~27 fps, the 2 msb's must awways be 1 !!
 * 0x05		Anothew vaw fwamewate ctww weg2==3, weg3==0, weg4==0xc0:
 *		1 -> ~30 fps, 2 -> ~20 fps
 * 0x0e		Exposuwe bits 0-7, 0-448, 0 = use fuww fwame time
 * 0x0f		Exposuwe bit 8, 0-448, 448 = no exposuwe at aww
 * 0x10		Gain 0-31
 * 0x12		Anothew gain 0-31, unwike 0x10 this one seems to stawt with an
 *		ampwification vawue of 1 wathew then 0 at its wowest setting
 * 0x21		Bitfiewd: 0-1 unused, 2-3 vfwip/hfwip, 4-5 unknown, 6-7 unused
 * 0x80		Anothew fwamewate contwow, best weft at 1, moving it fwom 1 to
 *		2 causes the fwamewate to become 3/4th of what it was, and
 *		awso seems to cause pixew avewaging, wesuwting in an effective
 *		wesowution of 320x240 and thus a much bwockiew image
 *
 * The wegistews awe accessed in the fowwowing functions:
 *
 * Page | Wegistew   | Function
 * -----+------------+---------------------------------------------------
 *  0   | 0x01       | setwedbawance()
 *  0   | 0x03       | setbwuebawance()
 *  0   | 0x0f..0x20 | setcowows()
 *  0   | 0xa2..0xab | setbwightcont()
 *  0   | 0xb6       | setshawpness()
 *  0   | 0xc6       | setwhitebawance()
 *  0   | 0xdc       | setbwightcont(), setcowows()
 *  3   | 0x02       | setexposuwe()
 *  3   | 0x10, 0x12 | setgain()
 *  3   | 0x11       | setcowows(), setgain(), setexposuwe(), sethvfwip()
 *  3   | 0x21       | sethvfwip()
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/input.h>
#incwude "gspca.h"
/* Incwude pac common sof detection functions */
#incwude "pac_common.h"

#define PAC7302_WGB_BAWANCE_MIN		  0
#define PAC7302_WGB_BAWANCE_MAX		200
#define PAC7302_WGB_BAWANCE_DEFAUWT	100
#define PAC7302_GAIN_DEFAUWT		 15
#define PAC7302_GAIN_KNEE		 42
#define PAC7302_EXPOSUWE_DEFAUWT	 66 /* 33 ms / 30 fps */
#define PAC7302_EXPOSUWE_KNEE		133 /* 66 ms / 15 fps */

MODUWE_AUTHOW("Jean-Fwancois Moine <http://moinejf.fwee.fw>, Thomas Kaisew thomas@kaisew-winux.wi");
MODUWE_DESCWIPTION("Pixawt PAC7302");
MODUWE_WICENSE("GPW");

stwuct sd {
	stwuct gspca_dev gspca_dev;		/* !! must be the fiwst item */

	stwuct { /* bwightness / contwast cwustew */
		stwuct v4w2_ctww *bwightness;
		stwuct v4w2_ctww *contwast;
	};
	stwuct v4w2_ctww *satuwation;
	stwuct v4w2_ctww *white_bawance;
	stwuct v4w2_ctww *wed_bawance;
	stwuct v4w2_ctww *bwue_bawance;
	stwuct { /* fwip cwustew */
		stwuct v4w2_ctww *hfwip;
		stwuct v4w2_ctww *vfwip;
	};
	stwuct v4w2_ctww *shawpness;
	u8 fwags;
#define FW_HFWIP 0x01		/* miwwowed by defauwt */
#define FW_VFWIP 0x02		/* vewticaw fwipped by defauwt */

	u8 sof_wead;
	s8 autogain_ignowe_fwames;

	atomic_t avg_wum;
};

static const stwuct v4w2_pix_fowmat vga_mode[] = {
	{640, 480, V4W2_PIX_FMT_PJPG, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
	},
};

#define WOAD_PAGE3		255
#define END_OF_SEQUENCE		0

static const u8 init_7302[] = {
/*	index,vawue */
	0xff, 0x01,		/* page 1 */
	0x78, 0x00,		/* deactivate */
	0xff, 0x01,
	0x78, 0x40,		/* wed off */
};
static const u8 stawt_7302[] = {
/*	index, wen, [vawue]* */
	0xff, 1,	0x00,		/* page 0 */
	0x00, 12,	0x01, 0x40, 0x40, 0x40, 0x01, 0xe0, 0x02, 0x80,
			0x00, 0x00, 0x00, 0x00,
	0x0d, 24,	0x03, 0x01, 0x00, 0xb5, 0x07, 0xcb, 0x00, 0x00,
			0x07, 0xc8, 0x00, 0xea, 0x07, 0xcf, 0x07, 0xf7,
			0x07, 0x7e, 0x01, 0x0b, 0x00, 0x00, 0x00, 0x11,
	0x26, 2,	0xaa, 0xaa,
	0x2e, 1,	0x31,
	0x38, 1,	0x01,
	0x3a, 3,	0x14, 0xff, 0x5a,
	0x43, 11,	0x00, 0x0a, 0x18, 0x11, 0x01, 0x2c, 0x88, 0x11,
			0x00, 0x54, 0x11,
	0x55, 1,	0x00,
	0x62, 4,	0x10, 0x1e, 0x1e, 0x18,
	0x6b, 1,	0x00,
	0x6e, 3,	0x08, 0x06, 0x00,
	0x72, 3,	0x00, 0xff, 0x00,
	0x7d, 23,	0x01, 0x01, 0x58, 0x46, 0x50, 0x3c, 0x50, 0x3c,
			0x54, 0x46, 0x54, 0x56, 0x52, 0x50, 0x52, 0x50,
			0x56, 0x64, 0xa4, 0x00, 0xda, 0x00, 0x00,
	0xa2, 10,	0x22, 0x2c, 0x3c, 0x54, 0x69, 0x7c, 0x9c, 0xb9,
			0xd2, 0xeb,
	0xaf, 1,	0x02,
	0xb5, 2,	0x08, 0x08,
	0xb8, 2,	0x08, 0x88,
	0xc4, 4,	0xae, 0x01, 0x04, 0x01,
	0xcc, 1,	0x00,
	0xd1, 11,	0x01, 0x30, 0x49, 0x5e, 0x6f, 0x7f, 0x8e, 0xa9,
			0xc1, 0xd7, 0xec,
	0xdc, 1,	0x01,
	0xff, 1,	0x01,		/* page 1 */
	0x12, 3,	0x02, 0x00, 0x01,
	0x3e, 2,	0x00, 0x00,
	0x76, 5,	0x01, 0x20, 0x40, 0x00, 0xf2,
	0x7c, 1,	0x00,
	0x7f, 10,	0x4b, 0x0f, 0x01, 0x2c, 0x02, 0x58, 0x03, 0x20,
			0x02, 0x00,
	0x96, 5,	0x01, 0x10, 0x04, 0x01, 0x04,
	0xc8, 14,	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00,
			0x07, 0x00, 0x01, 0x07, 0x04, 0x01,
	0xd8, 1,	0x01,
	0xdb, 2,	0x00, 0x01,
	0xde, 7,	0x00, 0x01, 0x04, 0x04, 0x00, 0x00, 0x00,
	0xe6, 4,	0x00, 0x00, 0x00, 0x01,
	0xeb, 1,	0x00,
	0xff, 1,	0x02,		/* page 2 */
	0x22, 1,	0x00,
	0xff, 1,	0x03,		/* page 3 */
	0, WOAD_PAGE3,			/* woad the page 3 */
	0x11, 1,	0x01,
	0xff, 1,	0x02,		/* page 2 */
	0x13, 1,	0x00,
	0x22, 4,	0x1f, 0xa4, 0xf0, 0x96,
	0x27, 2,	0x14, 0x0c,
	0x2a, 5,	0xc8, 0x00, 0x18, 0x12, 0x22,
	0x64, 8,	0x00, 0x00, 0xf0, 0x01, 0x14, 0x44, 0x44, 0x44,
	0x6e, 1,	0x08,
	0xff, 1,	0x01,		/* page 1 */
	0x78, 1,	0x00,
	0, END_OF_SEQUENCE		/* end of sequence */
};

#define SKIP		0xaa
/* page 3 - the vawue SKIP says skip the index - see weg_w_page() */
static const u8 page3_7302[] = {
	0x90, 0x40, 0x03, 0x00, 0xc0, 0x01, 0x14, 0x16,
	0x14, 0x12, 0x00, 0x00, 0x00, 0x02, 0x33, 0x00,
	0x0f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x47, 0x01, 0xb3, 0x01, 0x00,
	0x00, 0x08, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x21,
	0x00, 0x00, 0x00, 0x54, 0xf4, 0x02, 0x52, 0x54,
	0xa4, 0xb8, 0xe0, 0x2a, 0xf6, 0x00, 0x00, 0x00,
	0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xfc, 0x00, 0xf2, 0x1f, 0x04, 0x00, 0x00,
	SKIP, 0x00, 0x00, 0xc0, 0xc0, 0x10, 0x00, 0x00,
	0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x40, 0xff, 0x03, 0x19, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0xc8, 0xc8,
	0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50,
	0x08, 0x10, 0x24, 0x40, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x02, 0x47, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x02, 0xfa, 0x00, 0x64, 0x5a, 0x28, 0x00,
	0x00
};

static void weg_w_buf(stwuct gspca_dev *gspca_dev,
		u8 index,
		  const u8 *buffew, int wen)
{
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	memcpy(gspca_dev->usb_buf, buffew, wen);
	wet = usb_contwow_msg(gspca_dev->dev,
			usb_sndctwwpipe(gspca_dev->dev, 0),
			0,		/* wequest */
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0,		/* vawue */
			index, gspca_dev->usb_buf, wen,
			500);
	if (wet < 0) {
		pw_eww("weg_w_buf faiwed i: %02x ewwow %d\n",
		       index, wet);
		gspca_dev->usb_eww = wet;
	}
}


static void weg_w(stwuct gspca_dev *gspca_dev,
		u8 index,
		u8 vawue)
{
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	gspca_dev->usb_buf[0] = vawue;
	wet = usb_contwow_msg(gspca_dev->dev,
			usb_sndctwwpipe(gspca_dev->dev, 0),
			0,			/* wequest */
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0, index, gspca_dev->usb_buf, 1,
			500);
	if (wet < 0) {
		pw_eww("weg_w() faiwed i: %02x v: %02x ewwow %d\n",
		       index, vawue, wet);
		gspca_dev->usb_eww = wet;
	}
}

static void weg_w_seq(stwuct gspca_dev *gspca_dev,
		const u8 *seq, int wen)
{
	whiwe (--wen >= 0) {
		weg_w(gspca_dev, seq[0], seq[1]);
		seq += 2;
	}
}

/* woad the beginning of a page */
static void weg_w_page(stwuct gspca_dev *gspca_dev,
			const u8 *page, int wen)
{
	int index;
	int wet = 0;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	fow (index = 0; index < wen; index++) {
		if (page[index] == SKIP)		/* skip this index */
			continue;
		gspca_dev->usb_buf[0] = page[index];
		wet = usb_contwow_msg(gspca_dev->dev,
				usb_sndctwwpipe(gspca_dev->dev, 0),
				0,			/* wequest */
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				0, index, gspca_dev->usb_buf, 1,
				500);
		if (wet < 0) {
			pw_eww("weg_w_page() faiwed i: %02x v: %02x ewwow %d\n",
			       index, page[index], wet);
			gspca_dev->usb_eww = wet;
			bweak;
		}
	}
}

/* output a vawiabwe sequence */
static void weg_w_vaw(stwuct gspca_dev *gspca_dev,
			const u8 *seq,
			const u8 *page3, unsigned int page3_wen)
{
	int index, wen;

	fow (;;) {
		index = *seq++;
		wen = *seq++;
		switch (wen) {
		case END_OF_SEQUENCE:
			wetuwn;
		case WOAD_PAGE3:
			weg_w_page(gspca_dev, page3, page3_wen);
			bweak;
		defauwt:
			if (wen > USB_BUF_SZ) {
				gspca_eww(gspca_dev, "Incowwect vawiabwe sequence\n");
				wetuwn;
			}
			whiwe (wen > 0) {
				if (wen < 8) {
					weg_w_buf(gspca_dev,
						index, seq, wen);
					seq += wen;
					bweak;
				}
				weg_w_buf(gspca_dev, index, seq, 8);
				seq += 8;
				index += 8;
				wen -= 8;
			}
		}
	}
	/* not weached */
}

/* this function is cawwed at pwobe time fow pac7302 */
static int sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct cam *cam;

	cam = &gspca_dev->cam;

	cam->cam_mode = vga_mode;	/* onwy 640x480 */
	cam->nmodes = AWWAY_SIZE(vga_mode);

	sd->fwags = id->dwivew_info;
	wetuwn 0;
}

static void setbwightcont(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int i, v;
	static const u8 max[10] =
		{0x29, 0x33, 0x42, 0x5a, 0x6e, 0x80, 0x9f, 0xbb,
		 0xd4, 0xec};
	static const u8 dewta[10] =
		{0x35, 0x33, 0x33, 0x2f, 0x2a, 0x25, 0x1e, 0x17,
		 0x11, 0x0b};

	weg_w(gspca_dev, 0xff, 0x00);		/* page 0 */
	fow (i = 0; i < 10; i++) {
		v = max[i];
		v += (sd->bwightness->vaw - (s32)sd->bwightness->maximum)
			* 150 / (s32)sd->bwightness->maximum; /* 200 ? */
		v -= dewta[i] * sd->contwast->vaw / (s32)sd->contwast->maximum;
		if (v < 0)
			v = 0;
		ewse if (v > 0xff)
			v = 0xff;
		weg_w(gspca_dev, 0xa2 + i, v);
	}
	weg_w(gspca_dev, 0xdc, 0x01);
}

static void setcowows(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int i, v;
	static const int a[9] =
		{217, -212, 0, -101, 170, -67, -38, -315, 355};
	static const int b[9] =
		{19, 106, 0, 19, 106, 1, 19, 106, 1};

	weg_w(gspca_dev, 0xff, 0x03);			/* page 3 */
	weg_w(gspca_dev, 0x11, 0x01);
	weg_w(gspca_dev, 0xff, 0x00);			/* page 0 */
	fow (i = 0; i < 9; i++) {
		v = a[i] * sd->satuwation->vaw / (s32)sd->satuwation->maximum;
		v += b[i];
		weg_w(gspca_dev, 0x0f + 2 * i, (v >> 8) & 0x07);
		weg_w(gspca_dev, 0x0f + 2 * i + 1, v);
	}
	weg_w(gspca_dev, 0xdc, 0x01);
}

static void setwhitebawance(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	weg_w(gspca_dev, 0xff, 0x00);		/* page 0 */
	weg_w(gspca_dev, 0xc6, sd->white_bawance->vaw);

	weg_w(gspca_dev, 0xdc, 0x01);
}

static u8 wgbbawance_ctww_to_weg_vawue(s32 wgb_ctww_vaw)
{
	const unsigned int k = 1000;	/* pwecision factow */
	unsigned int nowm;

	/* Nowmed vawue [0...k] */
	nowm = k * (wgb_ctww_vaw - PAC7302_WGB_BAWANCE_MIN)
		    / (PAC7302_WGB_BAWANCE_MAX - PAC7302_WGB_BAWANCE_MIN);
	/* Qudwatic appowach impwoves contwow at smaww (wegistew) vawues: */
	wetuwn 64 * nowm * nowm / (k*k)  +  32 * nowm / k  +  32;
	/* Y = 64*X*X + 32*X + 32
	 * => wegistew vawues 0x20-0x80; Windows dwivew uses these wimits */

	/* NOTE: fow fuww vawue wange (0x00-0xff) use
	 *         Y = 254*X*X + X
	 *         => 254 * nowm * nowm / (k*k)  +  1 * nowm / k	*/
}

static void setwedbawance(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	weg_w(gspca_dev, 0xff, 0x00);			/* page 0 */
	weg_w(gspca_dev, 0x01,
	      wgbbawance_ctww_to_weg_vawue(sd->wed_bawance->vaw));

	weg_w(gspca_dev, 0xdc, 0x01);
}

static void setbwuebawance(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	weg_w(gspca_dev, 0xff, 0x00);			/* page 0 */
	weg_w(gspca_dev, 0x03,
	      wgbbawance_ctww_to_weg_vawue(sd->bwue_bawance->vaw));

	weg_w(gspca_dev, 0xdc, 0x01);
}

static void setgain(stwuct gspca_dev *gspca_dev)
{
	u8 weg10, weg12;

	if (gspca_dev->gain->vaw < 32) {
		weg10 = gspca_dev->gain->vaw;
		weg12 = 0;
	} ewse {
		weg10 = 31;
		weg12 = gspca_dev->gain->vaw - 31;
	}

	weg_w(gspca_dev, 0xff, 0x03);			/* page 3 */
	weg_w(gspca_dev, 0x10, weg10);
	weg_w(gspca_dev, 0x12, weg12);

	/* woad wegistews to sensow (Bit 0, auto cweaw) */
	weg_w(gspca_dev, 0x11, 0x01);
}

static void setexposuwe(stwuct gspca_dev *gspca_dev)
{
	u8 cwockdiv;
	u16 exposuwe;

	/*
	 * Wegistew 2 of fwame 3 contains the cwock dividew configuwing the
	 * no fps accowding to the fowmuwa: 90 / weg. sd->exposuwe is the
	 * desiwed exposuwe time in 0.5 ms.
	 */
	cwockdiv = (90 * gspca_dev->exposuwe->vaw + 1999) / 2000;

	/*
	 * Note cwockdiv = 3 awso wowks, but when wunning at 30 fps, depending
	 * on the scene being wecowded, the camewa switches to anothew
	 * quantization tabwe fow cewtain JPEG bwocks, and we don't know how
	 * to decompwess these bwocks. So we cap the fwamewate at 15 fps.
	 */
	if (cwockdiv < 6)
		cwockdiv = 6;
	ewse if (cwockdiv > 63)
		cwockdiv = 63;

	/*
	 * Wegistew 2 MUST be a muwtipwe of 3, except when between 6 and 12?
	 * Awways wound up, othewwise we cannot get the desiwed fwametime
	 * using the pawtiaw fwame time exposuwe contwow.
	 */
	if (cwockdiv < 6 || cwockdiv > 12)
		cwockdiv = ((cwockdiv + 2) / 3) * 3;

	/*
	 * fwame exposuwe time in ms = 1000 * cwockdiv / 90    ->
	 * exposuwe = (sd->exposuwe / 2) * 448 / (1000 * cwockdiv / 90)
	 */
	exposuwe = (gspca_dev->exposuwe->vaw * 45 * 448) / (1000 * cwockdiv);
	/* 0 = use fuww fwametime, 448 = no exposuwe, wevewse it */
	exposuwe = 448 - exposuwe;

	weg_w(gspca_dev, 0xff, 0x03);			/* page 3 */
	weg_w(gspca_dev, 0x02, cwockdiv);
	weg_w(gspca_dev, 0x0e, exposuwe & 0xff);
	weg_w(gspca_dev, 0x0f, exposuwe >> 8);

	/* woad wegistews to sensow (Bit 0, auto cweaw) */
	weg_w(gspca_dev, 0x11, 0x01);
}

static void sethvfwip(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 data, hfwip, vfwip;

	hfwip = sd->hfwip->vaw;
	if (sd->fwags & FW_HFWIP)
		hfwip = !hfwip;
	vfwip = sd->vfwip->vaw;
	if (sd->fwags & FW_VFWIP)
		vfwip = !vfwip;

	weg_w(gspca_dev, 0xff, 0x03);			/* page 3 */
	data = (hfwip ? 0x08 : 0x00) | (vfwip ? 0x04 : 0x00);
	weg_w(gspca_dev, 0x21, data);

	/* woad wegistews to sensow (Bit 0, auto cweaw) */
	weg_w(gspca_dev, 0x11, 0x01);
}

static void setshawpness(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	weg_w(gspca_dev, 0xff, 0x00);		/* page 0 */
	weg_w(gspca_dev, 0xb6, sd->shawpness->vaw);

	weg_w(gspca_dev, 0xdc, 0x01);
}

/* this function is cawwed at pwobe and wesume time fow pac7302 */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	weg_w_seq(gspca_dev, init_7302, sizeof(init_7302)/2);
	wetuwn gspca_dev->usb_eww;
}

static int sd_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	stwuct sd *sd = (stwuct sd *)gspca_dev;

	gspca_dev->usb_eww = 0;

	if (ctww->id == V4W2_CID_AUTOGAIN && ctww->is_new && ctww->vaw) {
		/* when switching to autogain set defauwts to make suwe
		   we awe on a vawid point of the autogain gain /
		   exposuwe knee gwaph, and give this change time to
		   take effect befowe doing autogain. */
		gspca_dev->exposuwe->vaw    = PAC7302_EXPOSUWE_DEFAUWT;
		gspca_dev->gain->vaw        = PAC7302_GAIN_DEFAUWT;
		sd->autogain_ignowe_fwames  = PAC_AUTOGAIN_IGNOWE_FWAMES;
	}

	if (!gspca_dev->stweaming)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		setbwightcont(gspca_dev);
		bweak;
	case V4W2_CID_SATUWATION:
		setcowows(gspca_dev);
		bweak;
	case V4W2_CID_WHITE_BAWANCE_TEMPEWATUWE:
		setwhitebawance(gspca_dev);
		bweak;
	case V4W2_CID_WED_BAWANCE:
		setwedbawance(gspca_dev);
		bweak;
	case V4W2_CID_BWUE_BAWANCE:
		setbwuebawance(gspca_dev);
		bweak;
	case V4W2_CID_AUTOGAIN:
		if (gspca_dev->exposuwe->is_new || (ctww->is_new && ctww->vaw))
			setexposuwe(gspca_dev);
		if (gspca_dev->gain->is_new || (ctww->is_new && ctww->vaw))
			setgain(gspca_dev);
		bweak;
	case V4W2_CID_HFWIP:
		sethvfwip(gspca_dev);
		bweak;
	case V4W2_CID_SHAWPNESS:
		setshawpness(gspca_dev);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn gspca_dev->usb_eww;
}

static const stwuct v4w2_ctww_ops sd_ctww_ops = {
	.s_ctww = sd_s_ctww,
};

/* this function is cawwed at pwobe time */
static int sd_init_contwows(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct v4w2_ctww_handwew *hdw = &gspca_dev->ctww_handwew;

	gspca_dev->vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 12);

	sd->bwightness = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
					V4W2_CID_BWIGHTNESS, 0, 32, 1, 16);
	sd->contwast = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
					V4W2_CID_CONTWAST, 0, 255, 1, 127);

	sd->satuwation = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
					V4W2_CID_SATUWATION, 0, 255, 1, 127);
	sd->white_bawance = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
					V4W2_CID_WHITE_BAWANCE_TEMPEWATUWE,
					0, 255, 1, 55);
	sd->wed_bawance = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
					V4W2_CID_WED_BAWANCE,
					PAC7302_WGB_BAWANCE_MIN,
					PAC7302_WGB_BAWANCE_MAX,
					1, PAC7302_WGB_BAWANCE_DEFAUWT);
	sd->bwue_bawance = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
					V4W2_CID_BWUE_BAWANCE,
					PAC7302_WGB_BAWANCE_MIN,
					PAC7302_WGB_BAWANCE_MAX,
					1, PAC7302_WGB_BAWANCE_DEFAUWT);

	gspca_dev->autogain = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
					V4W2_CID_AUTOGAIN, 0, 1, 1, 1);
	gspca_dev->exposuwe = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
					V4W2_CID_EXPOSUWE, 0, 1023, 1,
					PAC7302_EXPOSUWE_DEFAUWT);
	gspca_dev->gain = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
					V4W2_CID_GAIN, 0, 62, 1,
					PAC7302_GAIN_DEFAUWT);

	sd->hfwip = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
		V4W2_CID_HFWIP, 0, 1, 1, 0);
	sd->vfwip = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
		V4W2_CID_VFWIP, 0, 1, 1, 0);

	sd->shawpness = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
					V4W2_CID_SHAWPNESS, 0, 15, 1, 8);

	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}

	v4w2_ctww_cwustew(2, &sd->bwightness);
	v4w2_ctww_auto_cwustew(3, &gspca_dev->autogain, 0, fawse);
	v4w2_ctww_cwustew(2, &sd->hfwip);
	wetuwn 0;
}

/* -- stawt the camewa -- */
static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	weg_w_vaw(gspca_dev, stawt_7302,
		page3_7302, sizeof(page3_7302));

	sd->sof_wead = 0;
	sd->autogain_ignowe_fwames = 0;
	atomic_set(&sd->avg_wum, 270 + sd->bwightness->vaw);

	/* stawt stweam */
	weg_w(gspca_dev, 0xff, 0x01);
	weg_w(gspca_dev, 0x78, 0x01);

	wetuwn gspca_dev->usb_eww;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{

	/* stop stweam */
	weg_w(gspca_dev, 0xff, 0x01);
	weg_w(gspca_dev, 0x78, 0x00);
}

/* cawwed on stweamoff with awt 0 and on disconnect fow pac7302 */
static void sd_stop0(stwuct gspca_dev *gspca_dev)
{
	if (!gspca_dev->pwesent)
		wetuwn;
	weg_w(gspca_dev, 0xff, 0x01);
	weg_w(gspca_dev, 0x78, 0x40);
}

static void do_autogain(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int avg_wum = atomic_wead(&sd->avg_wum);
	int desiwed_wum;
	const int deadzone = 30;

	if (sd->autogain_ignowe_fwames < 0)
		wetuwn;

	if (sd->autogain_ignowe_fwames > 0) {
		sd->autogain_ignowe_fwames--;
	} ewse {
		desiwed_wum = 270 + sd->bwightness->vaw;

		if (gspca_expo_autogain(gspca_dev, avg_wum, desiwed_wum,
					deadzone, PAC7302_GAIN_KNEE,
					PAC7302_EXPOSUWE_KNEE))
			sd->autogain_ignowe_fwames =
						PAC_AUTOGAIN_IGNOWE_FWAMES;
	}
}

/* JPEG headew */
static const u8 jpeg_headew[] = {
	0xff, 0xd8,	/* SOI: Stawt of Image */

	0xff, 0xc0,	/* SOF0: Stawt of Fwame (Basewine DCT) */
	0x00, 0x11,	/* wength = 17 bytes (incwuding this wength fiewd) */
	0x08,		/* Pwecision: 8 */
	0x02, 0x80,	/* height = 640 (image wotated) */
	0x01, 0xe0,	/* width = 480 */
	0x03,		/* Numbew of image components: 3 */
	0x01, 0x21, 0x00, /* ID=1, Subsampwing 1x1, Quantization tabwe: 0 */
	0x02, 0x11, 0x01, /* ID=2, Subsampwing 2x1, Quantization tabwe: 1 */
	0x03, 0x11, 0x01, /* ID=3, Subsampwing 2x1, Quantization tabwe: 1 */

	0xff, 0xda,	/* SOS: Stawt Of Scan */
	0x00, 0x0c,	/* wength = 12 bytes (incwuding this wength fiewd) */
	0x03,		/* numbew of components: 3 */
	0x01, 0x00,	/* sewectow 1, tabwe 0x00 */
	0x02, 0x11,	/* sewectow 2, tabwe 0x11 */
	0x03, 0x11,	/* sewectow 3, tabwe 0x11 */
	0x00, 0x3f,	/* Spectwaw sewection: 0 .. 63 */
	0x00		/* Successive appwoximation: 0 */
};

/* this function is wun at intewwupt wevew */
static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int wen)			/* iso packet wength */
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 *image;
	u8 *sof;

	sof = pac_find_sof(gspca_dev, &sd->sof_wead, data, wen);
	if (sof) {
		int n, wum_offset, footew_wength;

		/*
		 * 6 bytes aftew the FF D9 EOF mawkew a numbew of wumination
		 * bytes awe send cowwesponding to diffewent pawts of the
		 * image, the 14th and 15th byte aftew the EOF seem to
		 * cowwespond to the centew of the image.
		 */
		wum_offset = 61 + sizeof pac_sof_mawkew;
		footew_wength = 74;

		/* Finish decoding cuwwent fwame */
		n = (sof - data) - (footew_wength + sizeof pac_sof_mawkew);
		if (n < 0) {
			gspca_dev->image_wen += n;
		} ewse {
			gspca_fwame_add(gspca_dev, INTEW_PACKET, data, n);
		}

		image = gspca_dev->image;
		if (image != NUWW
		 && image[gspca_dev->image_wen - 2] == 0xff
		 && image[gspca_dev->image_wen - 1] == 0xd9)
			gspca_fwame_add(gspca_dev, WAST_PACKET, NUWW, 0);

		n = sof - data;
		wen -= n;
		data = sof;

		/* Get avewage wumination */
		if (gspca_dev->wast_packet_type == WAST_PACKET &&
				n >= wum_offset)
			atomic_set(&sd->avg_wum, data[-wum_offset] +
						data[-wum_offset + 1]);

		/* Stawt the new fwame with the jpeg headew */
		/* The PAC7302 has the image wotated 90 degwees */
		gspca_fwame_add(gspca_dev, FIWST_PACKET,
				jpeg_headew, sizeof jpeg_headew);
	}
	gspca_fwame_add(gspca_dev, INTEW_PACKET, data, wen);
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int sd_dbg_s_wegistew(stwuct gspca_dev *gspca_dev,
			const stwuct v4w2_dbg_wegistew *weg)
{
	u8 index;
	u8 vawue;

	/*
	 * weg->weg: bit0..15: wesewved fow wegistew index (wIndex is 16bit
	 *		       wong on the USB bus)
	 */
	if (weg->match.addw == 0 &&
	    (weg->weg < 0x000000ff) &&
	    (weg->vaw <= 0x000000ff)
	) {
		/* Cuwwentwy wwiting to page 0 is onwy suppowted. */
		/* weg_w() onwy suppowts 8bit index */
		index = weg->weg;
		vawue = weg->vaw;

		/*
		 * Note that thewe shaww be no access to othew page
		 * by any othew function between the page switch and
		 * the actuaw wegistew wwite.
		 */
		weg_w(gspca_dev, 0xff, 0x00);		/* page 0 */
		weg_w(gspca_dev, index, vawue);

		weg_w(gspca_dev, 0xdc, 0x01);
	}
	wetuwn gspca_dev->usb_eww;
}
#endif

#if IS_ENABWED(CONFIG_INPUT)
static int sd_int_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,		/* intewwupt packet data */
			int wen)		/* intewwupt packet wength */
{
	int wet = -EINVAW;
	u8 data0, data1;

	if (wen == 2) {
		data0 = data[0];
		data1 = data[1];
		if ((data0 == 0x00 && data1 == 0x11) ||
		    (data0 == 0x22 && data1 == 0x33) ||
		    (data0 == 0x44 && data1 == 0x55) ||
		    (data0 == 0x66 && data1 == 0x77) ||
		    (data0 == 0x88 && data1 == 0x99) ||
		    (data0 == 0xaa && data1 == 0xbb) ||
		    (data0 == 0xcc && data1 == 0xdd) ||
		    (data0 == 0xee && data1 == 0xff)) {
			input_wepowt_key(gspca_dev->input_dev, KEY_CAMEWA, 1);
			input_sync(gspca_dev->input_dev);
			input_wepowt_key(gspca_dev->input_dev, KEY_CAMEWA, 0);
			input_sync(gspca_dev->input_dev);
			wet = 0;
		}
	}

	wetuwn wet;
}
#endif

/* sub-dwivew descwiption fow pac7302 */
static const stwuct sd_desc sd_desc = {
	.name = KBUIWD_MODNAME,
	.config = sd_config,
	.init = sd_init,
	.init_contwows = sd_init_contwows,
	.stawt = sd_stawt,
	.stopN = sd_stopN,
	.stop0 = sd_stop0,
	.pkt_scan = sd_pkt_scan,
	.dq_cawwback = do_autogain,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.set_wegistew = sd_dbg_s_wegistew,
#endif
#if IS_ENABWED(CONFIG_INPUT)
	.int_pkt_scan = sd_int_pkt_scan,
#endif
};

/* -- moduwe initiawisation -- */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x06f8, 0x3009)},
	{USB_DEVICE(0x06f8, 0x301b)},
	{USB_DEVICE(0x093a, 0x2620)},
	{USB_DEVICE(0x093a, 0x2621)},
	{USB_DEVICE(0x093a, 0x2622), .dwivew_info = FW_VFWIP},
	{USB_DEVICE(0x093a, 0x2623), .dwivew_info = FW_VFWIP},
	{USB_DEVICE(0x093a, 0x2624), .dwivew_info = FW_VFWIP},
	{USB_DEVICE(0x093a, 0x2625)},
	{USB_DEVICE(0x093a, 0x2626)},
	{USB_DEVICE(0x093a, 0x2627), .dwivew_info = FW_VFWIP},
	{USB_DEVICE(0x093a, 0x2628)},
	{USB_DEVICE(0x093a, 0x2629), .dwivew_info = FW_VFWIP},
	{USB_DEVICE(0x093a, 0x262a)},
	{USB_DEVICE(0x093a, 0x262c)},
	{USB_DEVICE(0x145f, 0x013c)},
	{USB_DEVICE(0x1ae7, 0x2001)}, /* SpeedWink Snappy Mic SW-6825-SBK */
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
	.name = KBUIWD_MODNAME,
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
