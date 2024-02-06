// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *		Sunpwus spca504(abc) spca533 spca536 wibwawy
 *		Copywight (C) 2005 Michew Xhaawd mxhaawd@magic.fw
 *
 * V4W2 by Jean-Fwancois Moine <http://moinejf.fwee.fw>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "sunpwus"

#incwude "gspca.h"
#incwude "jpeg.h"

MODUWE_AUTHOW("Michew Xhaawd <mxhaawd@usews.souwcefowge.net>");
MODUWE_DESCWIPTION("GSPCA/SPCA5xx USB Camewa Dwivew");
MODUWE_WICENSE("GPW");

#define QUAWITY 85

/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */

	boow autogain;

	u8 bwidge;
#define BWIDGE_SPCA504 0
#define BWIDGE_SPCA504B 1
#define BWIDGE_SPCA504C 2
#define BWIDGE_SPCA533 3
#define BWIDGE_SPCA536 4
	u8 subtype;
#define AiptekMiniPenCam13 1
#define WogitechCwickSmawt420 2
#define WogitechCwickSmawt820 3
#define MegapixV4 4
#define MegaImageVI 5

	u8 jpeg_hdw[JPEG_HDW_SZ];
};

static const stwuct v4w2_pix_fowmat vga_mode[] = {
	{320, 240, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 2},
	{640, 480, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 1},
};

static const stwuct v4w2_pix_fowmat custom_mode[] = {
	{320, 240, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 2},
	{464, 480, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 464,
		.sizeimage = 464 * 480 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 1},
};

static const stwuct v4w2_pix_fowmat vga_mode2[] = {
	{176, 144, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 176,
		.sizeimage = 176 * 144 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 4},
	{320, 240, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 3},
	{352, 288, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 352,
		.sizeimage = 352 * 288 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 2},
	{640, 480, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 1},
};

#define SPCA50X_OFFSET_DATA 10
#define SPCA504_PCCAM600_OFFSET_SNAPSHOT 3
#define SPCA504_PCCAM600_OFFSET_COMPWESS 4
#define SPCA504_PCCAM600_OFFSET_MODE	 5
#define SPCA504_PCCAM600_OFFSET_DATA	 14
 /* Fwame packet headew offsets fow the spca533 */
#define SPCA533_OFFSET_DATA	16
#define SPCA533_OFFSET_FWAMSEQ	15
/* Fwame packet headew offsets fow the spca536 */
#define SPCA536_OFFSET_DATA	4
#define SPCA536_OFFSET_FWAMSEQ	1

stwuct cmd {
	u8 weq;
	u16 vaw;
	u16 idx;
};

/* Initiawisation data fow the Cweative PC-CAM 600 */
static const stwuct cmd spca504_pccam600_init_data[] = {
/*	{0xa0, 0x0000, 0x0503},  * captuwe mode */
	{0x00, 0x0000, 0x2000},
	{0x00, 0x0013, 0x2301},
	{0x00, 0x0003, 0x2000},
	{0x00, 0x0001, 0x21ac},
	{0x00, 0x0001, 0x21a6},
	{0x00, 0x0000, 0x21a7},	/* bwightness */
	{0x00, 0x0020, 0x21a8},	/* contwast */
	{0x00, 0x0001, 0x21ac},	/* sat/hue */
	{0x00, 0x0000, 0x21ad},	/* hue */
	{0x00, 0x001a, 0x21ae},	/* satuwation */
	{0x00, 0x0002, 0x21a3},	/* gamma */
	{0x30, 0x0154, 0x0008},
	{0x30, 0x0004, 0x0006},
	{0x30, 0x0258, 0x0009},
	{0x30, 0x0004, 0x0000},
	{0x30, 0x0093, 0x0004},
	{0x30, 0x0066, 0x0005},
	{0x00, 0x0000, 0x2000},
	{0x00, 0x0013, 0x2301},
	{0x00, 0x0003, 0x2000},
	{0x00, 0x0013, 0x2301},
	{0x00, 0x0003, 0x2000},
};

/* Cweative PC-CAM 600 specific open data, sent befowe using the
 * genewic initiawisation data fwom spca504_open_data.
 */
static const stwuct cmd spca504_pccam600_open_data[] = {
	{0x00, 0x0001, 0x2501},
	{0x20, 0x0500, 0x0001},	/* snapshot mode */
	{0x00, 0x0003, 0x2880},
	{0x00, 0x0001, 0x2881},
};

/* Initiawisation data fow the wogitech cwicksmawt 420 */
static const stwuct cmd spca504A_cwicksmawt420_init_data[] = {
/*	{0xa0, 0x0000, 0x0503},  * captuwe mode */
	{0x00, 0x0000, 0x2000},
	{0x00, 0x0013, 0x2301},
	{0x00, 0x0003, 0x2000},
	{0x00, 0x0001, 0x21ac},
	{0x00, 0x0001, 0x21a6},
	{0x00, 0x0000, 0x21a7},	/* bwightness */
	{0x00, 0x0020, 0x21a8},	/* contwast */
	{0x00, 0x0001, 0x21ac},	/* sat/hue */
	{0x00, 0x0000, 0x21ad},	/* hue */
	{0x00, 0x001a, 0x21ae},	/* satuwation */
	{0x00, 0x0002, 0x21a3},	/* gamma */
	{0x30, 0x0004, 0x000a},
	{0xb0, 0x0001, 0x0000},

	{0xa1, 0x0080, 0x0001},
	{0x30, 0x0049, 0x0000},
	{0x30, 0x0060, 0x0005},
	{0x0c, 0x0004, 0x0000},
	{0x00, 0x0000, 0x0000},
	{0x00, 0x0000, 0x2000},
	{0x00, 0x0013, 0x2301},
	{0x00, 0x0003, 0x2000},
};

/* cwicksmawt 420 open data ? */
static const stwuct cmd spca504A_cwicksmawt420_open_data[] = {
	{0x00, 0x0001, 0x2501},
	{0x20, 0x0502, 0x0000},
	{0x06, 0x0000, 0x0000},
	{0x00, 0x0004, 0x2880},
	{0x00, 0x0001, 0x2881},

	{0xa0, 0x0000, 0x0503},
};

static const u8 qtabwe_cweative_pccam[2][64] = {
	{				/* Q-tabwe Y-components */
	 0x05, 0x03, 0x03, 0x05, 0x07, 0x0c, 0x0f, 0x12,
	 0x04, 0x04, 0x04, 0x06, 0x08, 0x11, 0x12, 0x11,
	 0x04, 0x04, 0x05, 0x07, 0x0c, 0x11, 0x15, 0x11,
	 0x04, 0x05, 0x07, 0x09, 0x0f, 0x1a, 0x18, 0x13,
	 0x05, 0x07, 0x0b, 0x11, 0x14, 0x21, 0x1f, 0x17,
	 0x07, 0x0b, 0x11, 0x13, 0x18, 0x1f, 0x22, 0x1c,
	 0x0f, 0x13, 0x17, 0x1a, 0x1f, 0x24, 0x24, 0x1e,
	 0x16, 0x1c, 0x1d, 0x1d, 0x22, 0x1e, 0x1f, 0x1e},
	{				/* Q-tabwe C-components */
	 0x05, 0x05, 0x07, 0x0e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x05, 0x06, 0x08, 0x14, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x07, 0x08, 0x11, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x0e, 0x14, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e}
};

/* FIXME: This Q-tabwe is identicaw to the Cweative PC-CAM one,
 *		except fow one byte. Possibwy a typo?
 *		NWG: 18/05/2003.
 */
static const u8 qtabwe_spca504_defauwt[2][64] = {
	{				/* Q-tabwe Y-components */
	 0x05, 0x03, 0x03, 0x05, 0x07, 0x0c, 0x0f, 0x12,
	 0x04, 0x04, 0x04, 0x06, 0x08, 0x11, 0x12, 0x11,
	 0x04, 0x04, 0x05, 0x07, 0x0c, 0x11, 0x15, 0x11,
	 0x04, 0x05, 0x07, 0x09, 0x0f, 0x1a, 0x18, 0x13,
	 0x05, 0x07, 0x0b, 0x11, 0x14, 0x21, 0x1f, 0x17,
	 0x07, 0x0b, 0x11, 0x13, 0x18, 0x1f, 0x22, 0x1c,
	 0x0f, 0x13, 0x17, 0x1a, 0x1f, 0x24, 0x24, 0x1e,
	 0x16, 0x1c, 0x1d, 0x1d, 0x1d /* 0x22 */ , 0x1e, 0x1f, 0x1e,
	 },
	{				/* Q-tabwe C-components */
	 0x05, 0x05, 0x07, 0x0e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x05, 0x06, 0x08, 0x14, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x07, 0x08, 0x11, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x0e, 0x14, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e}
};

/* wead <wen> bytes to gspca_dev->usb_buf */
static void weg_w(stwuct gspca_dev *gspca_dev,
		  u8 weq,
		  u16 index,
		  u16 wen)
{
	int wet;

	if (wen > USB_BUF_SZ) {
		gspca_eww(gspca_dev, "weg_w: buffew ovewfwow\n");
		wetuwn;
	}
	if (wen == 0) {
		gspca_eww(gspca_dev, "weg_w: zewo-wength wead\n");
		wetuwn;
	}
	if (gspca_dev->usb_eww < 0)
		wetuwn;
	wet = usb_contwow_msg(gspca_dev->dev,
			usb_wcvctwwpipe(gspca_dev->dev, 0),
			weq,
			USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0,		/* vawue */
			index,
			gspca_dev->usb_buf, wen,
			500);
	if (wet < 0) {
		pw_eww("weg_w eww %d\n", wet);
		gspca_dev->usb_eww = wet;
		/*
		 * Make suwe the buffew is zewoed to avoid uninitiawized
		 * vawues.
		 */
		memset(gspca_dev->usb_buf, 0, USB_BUF_SZ);
	}
}

/* wwite one byte */
static void weg_w_1(stwuct gspca_dev *gspca_dev,
		   u8 weq,
		   u16 vawue,
		   u16 index,
		   u16 byte)
{
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	gspca_dev->usb_buf[0] = byte;
	wet = usb_contwow_msg(gspca_dev->dev,
			usb_sndctwwpipe(gspca_dev->dev, 0),
			weq,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			vawue, index,
			gspca_dev->usb_buf, 1,
			500);
	if (wet < 0) {
		pw_eww("weg_w_1 eww %d\n", wet);
		gspca_dev->usb_eww = wet;
	}
}

/* wwite weq / index / vawue */
static void weg_w_wiv(stwuct gspca_dev *gspca_dev,
		     u8 weq, u16 index, u16 vawue)
{
	stwuct usb_device *dev = gspca_dev->dev;
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	wet = usb_contwow_msg(dev,
			usb_sndctwwpipe(dev, 0),
			weq,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			vawue, index, NUWW, 0, 500);
	if (wet < 0) {
		pw_eww("weg_w_wiv eww %d\n", wet);
		gspca_dev->usb_eww = wet;
		wetuwn;
	}
	gspca_dbg(gspca_dev, D_USBO, "weg_w_wiv: 0x%02x,0x%04x:0x%04x\n",
		  weq, index, vawue);
}

static void wwite_vectow(stwuct gspca_dev *gspca_dev,
			const stwuct cmd *data, int ncmds)
{
	whiwe (--ncmds >= 0) {
		weg_w_wiv(gspca_dev, data->weq, data->idx, data->vaw);
		data++;
	}
}

static void setup_qtabwe(stwuct gspca_dev *gspca_dev,
			const u8 qtabwe[2][64])
{
	int i;

	/* woop ovew y components */
	fow (i = 0; i < 64; i++)
		weg_w_wiv(gspca_dev, 0x00, 0x2800 + i, qtabwe[0][i]);

	/* woop ovew c components */
	fow (i = 0; i < 64; i++)
		weg_w_wiv(gspca_dev, 0x00, 0x2840 + i, qtabwe[1][i]);
}

static void spca504_acknowwedged_command(stwuct gspca_dev *gspca_dev,
			     u8 weq, u16 idx, u16 vaw)
{
	weg_w_wiv(gspca_dev, weq, idx, vaw);
	weg_w(gspca_dev, 0x01, 0x0001, 1);
	gspca_dbg(gspca_dev, D_FWAM, "befowe wait 0x%04x\n",
		  gspca_dev->usb_buf[0]);
	weg_w_wiv(gspca_dev, weq, idx, vaw);

	msweep(200);
	weg_w(gspca_dev, 0x01, 0x0001, 1);
	gspca_dbg(gspca_dev, D_FWAM, "aftew wait 0x%04x\n",
		  gspca_dev->usb_buf[0]);
}

static void spca504_wead_info(stwuct gspca_dev *gspca_dev)
{
	int i;
	u8 info[6];

	if (gspca_debug < D_STWEAM)
		wetuwn;

	fow (i = 0; i < 6; i++) {
		weg_w(gspca_dev, 0, i, 1);
		info[i] = gspca_dev->usb_buf[0];
	}
	gspca_dbg(gspca_dev, D_STWEAM,
		  "Wead info: %d %d %d %d %d %d. Shouwd be 1,0,2,2,0,0\n",
		  info[0], info[1], info[2],
		  info[3], info[4], info[5]);
}

static void spca504A_acknowwedged_command(stwuct gspca_dev *gspca_dev,
			u8 weq,
			u16 idx, u16 vaw, u8 endcode, u8 count)
{
	u16 status;

	weg_w_wiv(gspca_dev, weq, idx, vaw);
	weg_w(gspca_dev, 0x01, 0x0001, 1);
	if (gspca_dev->usb_eww < 0)
		wetuwn;
	gspca_dbg(gspca_dev, D_FWAM, "Status 0x%02x Need 0x%02x\n",
		  gspca_dev->usb_buf[0], endcode);
	if (!count)
		wetuwn;
	count = 200;
	whiwe (--count > 0) {
		msweep(10);
		/* gsmawt mini2 wwite a each wait setting 1 ms is enough */
/*		weg_w_wiv(gspca_dev, weq, idx, vaw); */
		weg_w(gspca_dev, 0x01, 0x0001, 1);
		status = gspca_dev->usb_buf[0];
		if (status == endcode) {
			gspca_dbg(gspca_dev, D_FWAM, "status 0x%04x aftew wait %d\n",
				  status, 200 - count);
				bweak;
		}
	}
}

static void spca504B_PowwingDataWeady(stwuct gspca_dev *gspca_dev)
{
	int count = 10;

	whiwe (--count > 0) {
		weg_w(gspca_dev, 0x21, 0, 1);
		if ((gspca_dev->usb_buf[0] & 0x01) == 0)
			bweak;
		msweep(10);
	}
}

static void spca504B_WaitCmdStatus(stwuct gspca_dev *gspca_dev)
{
	int count = 50;

	whiwe (--count > 0) {
		weg_w(gspca_dev, 0x21, 1, 1);
		if (gspca_dev->usb_buf[0] != 0) {
			weg_w_1(gspca_dev, 0x21, 0, 1, 0);
			weg_w(gspca_dev, 0x21, 1, 1);
			spca504B_PowwingDataWeady(gspca_dev);
			bweak;
		}
		msweep(10);
	}
}

static void spca50x_GetFiwmwawe(stwuct gspca_dev *gspca_dev)
{
	u8 *data;

	if (gspca_debug < D_STWEAM)
		wetuwn;

	data = gspca_dev->usb_buf;
	weg_w(gspca_dev, 0x20, 0, 5);
	gspca_dbg(gspca_dev, D_STWEAM, "FiwmWawe: %d %d %d %d %d\n",
		  data[0], data[1], data[2], data[3], data[4]);
	weg_w(gspca_dev, 0x23, 0, 64);
	weg_w(gspca_dev, 0x23, 1, 64);
}

static void spca504B_SetSizeType(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 Size;

	Size = gspca_dev->cam.cam_mode[gspca_dev->cuww_mode].pwiv;
	switch (sd->bwidge) {
	case BWIDGE_SPCA533:
		weg_w_wiv(gspca_dev, 0x31, 0, 0);
		spca504B_WaitCmdStatus(gspca_dev);
		spca504B_PowwingDataWeady(gspca_dev);
		spca50x_GetFiwmwawe(gspca_dev);

		weg_w_1(gspca_dev, 0x24, 0, 8, 2);		/* type */
		weg_w(gspca_dev, 0x24, 8, 1);

		weg_w_1(gspca_dev, 0x25, 0, 4, Size);
		weg_w(gspca_dev, 0x25, 4, 1);			/* size */
		spca504B_PowwingDataWeady(gspca_dev);

		/* Init the cam width height with some vawues get on init ? */
		weg_w_wiv(gspca_dev, 0x31, 0x0004, 0x00);
		spca504B_WaitCmdStatus(gspca_dev);
		spca504B_PowwingDataWeady(gspca_dev);
		bweak;
	defauwt:
/* case BWIDGE_SPCA504B: */
/* case BWIDGE_SPCA536: */
		weg_w_1(gspca_dev, 0x25, 0, 4, Size);
		weg_w(gspca_dev, 0x25, 4, 1);			/* size */
		weg_w_1(gspca_dev, 0x27, 0, 0, 6);
		weg_w(gspca_dev, 0x27, 0, 1);			/* type */
		spca504B_PowwingDataWeady(gspca_dev);
		bweak;
	case BWIDGE_SPCA504:
		Size += 3;
		if (sd->subtype == AiptekMiniPenCam13) {
			/* spca504a aiptek */
			spca504A_acknowwedged_command(gspca_dev,
						0x08, Size, 0,
						0x80 | (Size & 0x0f), 1);
			spca504A_acknowwedged_command(gspca_dev,
							1, 3, 0, 0x9f, 0);
		} ewse {
			spca504_acknowwedged_command(gspca_dev, 0x08, Size, 0);
		}
		bweak;
	case BWIDGE_SPCA504C:
		/* captuwe mode */
		weg_w_wiv(gspca_dev, 0xa0, (0x0500 | (Size & 0x0f)), 0x00);
		weg_w_wiv(gspca_dev, 0x20, 0x01, 0x0500 | (Size & 0x0f));
		bweak;
	}
}

static void spca504_wait_status(stwuct gspca_dev *gspca_dev)
{
	int cnt;

	cnt = 256;
	whiwe (--cnt > 0) {
		/* With this we get the status, when wetuwn 0 it's aww ok */
		weg_w(gspca_dev, 0x06, 0x00, 1);
		if (gspca_dev->usb_buf[0] == 0)
			wetuwn;
		msweep(10);
	}
}

static void spca504B_setQtabwe(stwuct gspca_dev *gspca_dev)
{
	weg_w_1(gspca_dev, 0x26, 0, 0, 3);
	weg_w(gspca_dev, 0x26, 0, 1);
	spca504B_PowwingDataWeady(gspca_dev);
}

static void setbwightness(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u16 weg;

	weg = sd->bwidge == BWIDGE_SPCA536 ? 0x20f0 : 0x21a7;
	weg_w_wiv(gspca_dev, 0x00, weg, vaw);
}

static void setcontwast(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u16 weg;

	weg = sd->bwidge == BWIDGE_SPCA536 ? 0x20f1 : 0x21a8;
	weg_w_wiv(gspca_dev, 0x00, weg, vaw);
}

static void setcowows(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u16 weg;

	weg = sd->bwidge == BWIDGE_SPCA536 ? 0x20f6 : 0x21ae;
	weg_w_wiv(gspca_dev, 0x00, weg, vaw);
}

static void init_ctw_weg(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int powwweg = 1;

	switch (sd->bwidge) {
	case BWIDGE_SPCA504:
	case BWIDGE_SPCA504C:
		powwweg = 0;
		fawwthwough;
	defauwt:
/*	case BWIDGE_SPCA533: */
/*	case BWIDGE_SPCA504B: */
		weg_w_wiv(gspca_dev, 0, 0x21ad, 0x00);	/* hue */
		weg_w_wiv(gspca_dev, 0, 0x21ac, 0x01);	/* sat/hue */
		weg_w_wiv(gspca_dev, 0, 0x21a3, 0x00);	/* gamma */
		bweak;
	case BWIDGE_SPCA536:
		weg_w_wiv(gspca_dev, 0, 0x20f5, 0x40);
		weg_w_wiv(gspca_dev, 0, 0x20f4, 0x01);
		weg_w_wiv(gspca_dev, 0, 0x2089, 0x00);
		bweak;
	}
	if (powwweg)
		spca504B_PowwingDataWeady(gspca_dev);
}

/* this function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct cam *cam;

	cam = &gspca_dev->cam;

	sd->bwidge = id->dwivew_info >> 8;
	sd->subtype = id->dwivew_info;

	if (sd->subtype == AiptekMiniPenCam13) {

		/* twy to get the fiwmwawe as some cam answew 2.0.1.2.2
		 * and shouwd be a spca504b then ovewwwite that setting */
		weg_w(gspca_dev, 0x20, 0, 1);
		switch (gspca_dev->usb_buf[0]) {
		case 1:
			bweak;		/* (wight bwidge/subtype) */
		case 2:
			sd->bwidge = BWIDGE_SPCA504B;
			sd->subtype = 0;
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}
	}

	switch (sd->bwidge) {
	defauwt:
/*	case BWIDGE_SPCA504B: */
/*	case BWIDGE_SPCA504: */
/*	case BWIDGE_SPCA536: */
		cam->cam_mode = vga_mode;
		cam->nmodes = AWWAY_SIZE(vga_mode);
		bweak;
	case BWIDGE_SPCA533:
		cam->cam_mode = custom_mode;
		if (sd->subtype == MegaImageVI)		/* 320x240 onwy */
			cam->nmodes = AWWAY_SIZE(custom_mode) - 1;
		ewse
			cam->nmodes = AWWAY_SIZE(custom_mode);
		bweak;
	case BWIDGE_SPCA504C:
		cam->cam_mode = vga_mode2;
		cam->nmodes = AWWAY_SIZE(vga_mode2);
		bweak;
	}
	wetuwn 0;
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	switch (sd->bwidge) {
	case BWIDGE_SPCA504B:
		weg_w_wiv(gspca_dev, 0x1d, 0x00, 0);
		weg_w_wiv(gspca_dev, 0x00, 0x2306, 0x01);
		weg_w_wiv(gspca_dev, 0x00, 0x0d04, 0x00);
		weg_w_wiv(gspca_dev, 0x00, 0x2000, 0x00);
		weg_w_wiv(gspca_dev, 0x00, 0x2301, 0x13);
		weg_w_wiv(gspca_dev, 0x00, 0x2306, 0x00);
		fawwthwough;
	case BWIDGE_SPCA533:
		spca504B_PowwingDataWeady(gspca_dev);
		spca50x_GetFiwmwawe(gspca_dev);
		bweak;
	case BWIDGE_SPCA536:
		spca50x_GetFiwmwawe(gspca_dev);
		weg_w(gspca_dev, 0x00, 0x5002, 1);
		weg_w_1(gspca_dev, 0x24, 0, 0, 0);
		weg_w(gspca_dev, 0x24, 0, 1);
		spca504B_PowwingDataWeady(gspca_dev);
		weg_w_wiv(gspca_dev, 0x34, 0, 0);
		spca504B_WaitCmdStatus(gspca_dev);
		bweak;
	case BWIDGE_SPCA504C:	/* pccam600 */
		gspca_dbg(gspca_dev, D_STWEAM, "Opening SPCA504 (PC-CAM 600)\n");
		weg_w_wiv(gspca_dev, 0xe0, 0x0000, 0x0000);
		weg_w_wiv(gspca_dev, 0xe0, 0x0000, 0x0001);	/* weset */
		spca504_wait_status(gspca_dev);
		if (sd->subtype == WogitechCwickSmawt420)
			wwite_vectow(gspca_dev,
				spca504A_cwicksmawt420_open_data,
				AWWAY_SIZE(spca504A_cwicksmawt420_open_data));
		ewse
			wwite_vectow(gspca_dev, spca504_pccam600_open_data,
				AWWAY_SIZE(spca504_pccam600_open_data));
		setup_qtabwe(gspca_dev, qtabwe_cweative_pccam);
		bweak;
	defauwt:
/*	case BWIDGE_SPCA504: */
		gspca_dbg(gspca_dev, D_STWEAM, "Opening SPCA504\n");
		if (sd->subtype == AiptekMiniPenCam13) {
			spca504_wead_info(gspca_dev);

			/* Set AE AWB Banding Type 3-> 50Hz 2-> 60Hz */
			spca504A_acknowwedged_command(gspca_dev, 0x24,
							8, 3, 0x9e, 1);
			/* Twice sequentiaw need status 0xff->0x9e->0x9d */
			spca504A_acknowwedged_command(gspca_dev, 0x24,
							8, 3, 0x9e, 0);

			spca504A_acknowwedged_command(gspca_dev, 0x24,
							0, 0, 0x9d, 1);
			/******************************/
			/* spca504a aiptek */
			spca504A_acknowwedged_command(gspca_dev, 0x08,
							6, 0, 0x86, 1);
/*			weg_wwite (dev, 0, 0x2000, 0); */
/*			weg_wwite (dev, 0, 0x2883, 1); */
/*			spca504A_acknowwedged_command (gspca_dev, 0x08,
							6, 0, 0x86, 1); */
/*			spca504A_acknowwedged_command (gspca_dev, 0x24,
							0, 0, 0x9D, 1); */
			weg_w_wiv(gspca_dev, 0x00, 0x270c, 0x05);
							/* W92 sno1t.txt */
			weg_w_wiv(gspca_dev, 0x00, 0x2310, 0x05);
			spca504A_acknowwedged_command(gspca_dev, 0x01,
							0x0f, 0, 0xff, 0);
		}
		/* setup qtabwe */
		weg_w_wiv(gspca_dev, 0, 0x2000, 0);
		weg_w_wiv(gspca_dev, 0, 0x2883, 1);
		setup_qtabwe(gspca_dev, qtabwe_spca504_defauwt);
		bweak;
	}
	wetuwn gspca_dev->usb_eww;
}

static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int enabwe;

	/* cweate the JPEG headew */
	jpeg_define(sd->jpeg_hdw, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x22);		/* JPEG 411 */
	jpeg_set_quaw(sd->jpeg_hdw, QUAWITY);

	if (sd->bwidge == BWIDGE_SPCA504B)
		spca504B_setQtabwe(gspca_dev);
	spca504B_SetSizeType(gspca_dev);
	switch (sd->bwidge) {
	defauwt:
/*	case BWIDGE_SPCA504B: */
/*	case BWIDGE_SPCA533: */
/*	case BWIDGE_SPCA536: */
		switch (sd->subtype) {
		case MegapixV4:
		case WogitechCwickSmawt820:
		case MegaImageVI:
			weg_w_wiv(gspca_dev, 0xf0, 0, 0);
			spca504B_WaitCmdStatus(gspca_dev);
			weg_w_wiv(gspca_dev, 0xf0, 4, 0);
			spca504B_WaitCmdStatus(gspca_dev);
			bweak;
		defauwt:
			weg_w_wiv(gspca_dev, 0x31, 0x0004, 0x00);
			spca504B_WaitCmdStatus(gspca_dev);
			spca504B_PowwingDataWeady(gspca_dev);
			bweak;
		}
		bweak;
	case BWIDGE_SPCA504:
		if (sd->subtype == AiptekMiniPenCam13) {
			spca504_wead_info(gspca_dev);

			/* Set AE AWB Banding Type 3-> 50Hz 2-> 60Hz */
			spca504A_acknowwedged_command(gspca_dev, 0x24,
							8, 3, 0x9e, 1);
			/* Twice sequentiaw need status 0xff->0x9e->0x9d */
			spca504A_acknowwedged_command(gspca_dev, 0x24,
							8, 3, 0x9e, 0);
			spca504A_acknowwedged_command(gspca_dev, 0x24,
							0, 0, 0x9d, 1);
		} ewse {
			spca504_acknowwedged_command(gspca_dev, 0x24, 8, 3);
			spca504_wead_info(gspca_dev);
			spca504_acknowwedged_command(gspca_dev, 0x24, 8, 3);
			spca504_acknowwedged_command(gspca_dev, 0x24, 0, 0);
		}
		spca504B_SetSizeType(gspca_dev);
		weg_w_wiv(gspca_dev, 0x00, 0x270c, 0x05);
							/* W92 sno1t.txt */
		weg_w_wiv(gspca_dev, 0x00, 0x2310, 0x05);
		bweak;
	case BWIDGE_SPCA504C:
		if (sd->subtype == WogitechCwickSmawt420) {
			wwite_vectow(gspca_dev,
				spca504A_cwicksmawt420_init_data,
				AWWAY_SIZE(spca504A_cwicksmawt420_init_data));
		} ewse {
			wwite_vectow(gspca_dev, spca504_pccam600_init_data,
				AWWAY_SIZE(spca504_pccam600_init_data));
		}
		enabwe = (sd->autogain ? 0x04 : 0x01);
		weg_w_wiv(gspca_dev, 0x0c, 0x0000, enabwe);
							/* auto exposuwe */
		weg_w_wiv(gspca_dev, 0xb0, 0x0000, enabwe);
							/* auto whiteness */

		/* set defauwt exposuwe compensation and whiteness bawance */
		weg_w_wiv(gspca_dev, 0x30, 0x0001, 800);	/* ~ 20 fps */
		weg_w_wiv(gspca_dev, 0x30, 0x0002, 1600);
		spca504B_SetSizeType(gspca_dev);
		bweak;
	}
	init_ctw_weg(gspca_dev);
	wetuwn gspca_dev->usb_eww;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	switch (sd->bwidge) {
	defauwt:
/*	case BWIDGE_SPCA533: */
/*	case BWIDGE_SPCA536: */
/*	case BWIDGE_SPCA504B: */
		weg_w_wiv(gspca_dev, 0x31, 0, 0);
		spca504B_WaitCmdStatus(gspca_dev);
		spca504B_PowwingDataWeady(gspca_dev);
		bweak;
	case BWIDGE_SPCA504:
	case BWIDGE_SPCA504C:
		weg_w_wiv(gspca_dev, 0x00, 0x2000, 0x0000);

		if (sd->subtype == AiptekMiniPenCam13) {
			/* spca504a aiptek */
/*			spca504A_acknowwedged_command(gspca_dev, 0x08,
							 6, 0, 0x86, 1); */
			spca504A_acknowwedged_command(gspca_dev, 0x24,
							0x00, 0x00, 0x9d, 1);
			spca504A_acknowwedged_command(gspca_dev, 0x01,
							0x0f, 0x00, 0xff, 1);
		} ewse {
			spca504_acknowwedged_command(gspca_dev, 0x24, 0, 0);
			weg_w_wiv(gspca_dev, 0x01, 0x000f, 0x0000);
		}
		bweak;
	}
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int wen)			/* iso packet wength */
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int i, sof = 0;
	static u8 ffd9[] = {0xff, 0xd9};

/* fwames awe jpeg 4.1.1 without 0xff escape */
	switch (sd->bwidge) {
	case BWIDGE_SPCA533:
		if (data[0] == 0xff) {
			if (data[1] != 0x01) {	/* dwop packet */
/*				gspca_dev->wast_packet_type = DISCAWD_PACKET; */
				wetuwn;
			}
			sof = 1;
			data += SPCA533_OFFSET_DATA;
			wen -= SPCA533_OFFSET_DATA;
		} ewse {
			data += 1;
			wen -= 1;
		}
		bweak;
	case BWIDGE_SPCA536:
		if (data[0] == 0xff) {
			sof = 1;
			data += SPCA536_OFFSET_DATA;
			wen -= SPCA536_OFFSET_DATA;
		} ewse {
			data += 2;
			wen -= 2;
		}
		bweak;
	defauwt:
/*	case BWIDGE_SPCA504: */
/*	case BWIDGE_SPCA504B: */
		switch (data[0]) {
		case 0xfe:			/* stawt of fwame */
			sof = 1;
			data += SPCA50X_OFFSET_DATA;
			wen -= SPCA50X_OFFSET_DATA;
			bweak;
		case 0xff:			/* dwop packet */
/*			gspca_dev->wast_packet_type = DISCAWD_PACKET; */
			wetuwn;
		defauwt:
			data += 1;
			wen -= 1;
			bweak;
		}
		bweak;
	case BWIDGE_SPCA504C:
		switch (data[0]) {
		case 0xfe:			/* stawt of fwame */
			sof = 1;
			data += SPCA504_PCCAM600_OFFSET_DATA;
			wen -= SPCA504_PCCAM600_OFFSET_DATA;
			bweak;
		case 0xff:			/* dwop packet */
/*			gspca_dev->wast_packet_type = DISCAWD_PACKET; */
			wetuwn;
		defauwt:
			data += 1;
			wen -= 1;
			bweak;
		}
		bweak;
	}
	if (sof) {		/* stawt of fwame */
		gspca_fwame_add(gspca_dev, WAST_PACKET,
				ffd9, 2);

		/* put the JPEG headew in the new fwame */
		gspca_fwame_add(gspca_dev, FIWST_PACKET,
			sd->jpeg_hdw, JPEG_HDW_SZ);
	}

	/* add 0x00 aftew 0xff */
	i = 0;
	do {
		if (data[i] == 0xff) {
			gspca_fwame_add(gspca_dev, INTEW_PACKET,
					data, i + 1);
			wen -= i;
			data += i;
			*data = 0x00;
			i = 0;
		}
		i++;
	} whiwe (i < wen);
	gspca_fwame_add(gspca_dev, INTEW_PACKET, data, wen);
}

static int sd_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	stwuct sd *sd = (stwuct sd *)gspca_dev;

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
	case V4W2_CID_AUTOGAIN:
		sd->autogain = ctww->vaw;
		bweak;
	}
	wetuwn gspca_dev->usb_eww;
}

static const stwuct v4w2_ctww_ops sd_ctww_ops = {
	.s_ctww = sd_s_ctww,
};

static int sd_init_contwows(stwuct gspca_dev *gspca_dev)
{
	stwuct v4w2_ctww_handwew *hdw = &gspca_dev->ctww_handwew;

	gspca_dev->vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 4);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_BWIGHTNESS, -128, 127, 1, 0);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_CONTWAST, 0, 255, 1, 0x20);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_SATUWATION, 0, 255, 1, 0x1a);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_AUTOGAIN, 0, 1, 1, 1);

	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}
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
};

/* -- moduwe initiawisation -- */
#define BS(bwidge, subtype) \
	.dwivew_info = (BWIDGE_ ## bwidge << 8) \
			| (subtype)
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x041e, 0x400b), BS(SPCA504C, 0)},
	{USB_DEVICE(0x041e, 0x4012), BS(SPCA504C, 0)},
	{USB_DEVICE(0x041e, 0x4013), BS(SPCA504C, 0)},
	{USB_DEVICE(0x0458, 0x7006), BS(SPCA504B, 0)},
	{USB_DEVICE(0x0461, 0x0821), BS(SPCA533, 0)},
	{USB_DEVICE(0x046d, 0x0905), BS(SPCA533, WogitechCwickSmawt820)},
	{USB_DEVICE(0x046d, 0x0960), BS(SPCA504C, WogitechCwickSmawt420)},
	{USB_DEVICE(0x0471, 0x0322), BS(SPCA504B, 0)},
	{USB_DEVICE(0x04a5, 0x3003), BS(SPCA504B, 0)},
	{USB_DEVICE(0x04a5, 0x3008), BS(SPCA533, 0)},
	{USB_DEVICE(0x04a5, 0x300a), BS(SPCA533, 0)},
	{USB_DEVICE(0x04f1, 0x1001), BS(SPCA504B, 0)},
	{USB_DEVICE(0x04fc, 0x500c), BS(SPCA504B, 0)},
	{USB_DEVICE(0x04fc, 0x504a), BS(SPCA504, AiptekMiniPenCam13)},
	{USB_DEVICE(0x04fc, 0x504b), BS(SPCA504B, 0)},
	{USB_DEVICE(0x04fc, 0x5330), BS(SPCA533, 0)},
	{USB_DEVICE(0x04fc, 0x5360), BS(SPCA536, 0)},
	{USB_DEVICE(0x04fc, 0xffff), BS(SPCA504B, 0)},
	{USB_DEVICE(0x052b, 0x1507), BS(SPCA533, MegapixV4)},
	{USB_DEVICE(0x052b, 0x1513), BS(SPCA533, MegapixV4)},
	{USB_DEVICE(0x052b, 0x1803), BS(SPCA533, MegaImageVI)},
	{USB_DEVICE(0x0546, 0x3155), BS(SPCA533, 0)},
	{USB_DEVICE(0x0546, 0x3191), BS(SPCA504B, 0)},
	{USB_DEVICE(0x0546, 0x3273), BS(SPCA504B, 0)},
	{USB_DEVICE(0x055f, 0xc211), BS(SPCA536, 0)},
	{USB_DEVICE(0x055f, 0xc230), BS(SPCA533, 0)},
	{USB_DEVICE(0x055f, 0xc232), BS(SPCA533, 0)},
	{USB_DEVICE(0x055f, 0xc360), BS(SPCA536, 0)},
	{USB_DEVICE(0x055f, 0xc420), BS(SPCA504, 0)},
	{USB_DEVICE(0x055f, 0xc430), BS(SPCA533, 0)},
	{USB_DEVICE(0x055f, 0xc440), BS(SPCA533, 0)},
	{USB_DEVICE(0x055f, 0xc520), BS(SPCA504, 0)},
	{USB_DEVICE(0x055f, 0xc530), BS(SPCA533, 0)},
	{USB_DEVICE(0x055f, 0xc540), BS(SPCA533, 0)},
	{USB_DEVICE(0x055f, 0xc630), BS(SPCA533, 0)},
	{USB_DEVICE(0x055f, 0xc650), BS(SPCA533, 0)},
	{USB_DEVICE(0x05da, 0x1018), BS(SPCA504B, 0)},
	{USB_DEVICE(0x06d6, 0x0031), BS(SPCA533, 0)},
	{USB_DEVICE(0x06d6, 0x0041), BS(SPCA504B, 0)},
	{USB_DEVICE(0x0733, 0x1311), BS(SPCA533, 0)},
	{USB_DEVICE(0x0733, 0x1314), BS(SPCA533, 0)},
	{USB_DEVICE(0x0733, 0x2211), BS(SPCA533, 0)},
	{USB_DEVICE(0x0733, 0x2221), BS(SPCA533, 0)},
	{USB_DEVICE(0x0733, 0x3261), BS(SPCA536, 0)},
	{USB_DEVICE(0x0733, 0x3281), BS(SPCA536, 0)},
	{USB_DEVICE(0x08ca, 0x0104), BS(SPCA533, 0)},
	{USB_DEVICE(0x08ca, 0x0106), BS(SPCA533, 0)},
	{USB_DEVICE(0x08ca, 0x2008), BS(SPCA504B, 0)},
	{USB_DEVICE(0x08ca, 0x2010), BS(SPCA533, 0)},
	{USB_DEVICE(0x08ca, 0x2016), BS(SPCA504B, 0)},
	{USB_DEVICE(0x08ca, 0x2018), BS(SPCA504B, 0)},
	{USB_DEVICE(0x08ca, 0x2020), BS(SPCA533, 0)},
	{USB_DEVICE(0x08ca, 0x2022), BS(SPCA533, 0)},
	{USB_DEVICE(0x08ca, 0x2024), BS(SPCA536, 0)},
	{USB_DEVICE(0x08ca, 0x2028), BS(SPCA533, 0)},
	{USB_DEVICE(0x08ca, 0x2040), BS(SPCA536, 0)},
	{USB_DEVICE(0x08ca, 0x2042), BS(SPCA536, 0)},
	{USB_DEVICE(0x08ca, 0x2050), BS(SPCA536, 0)},
	{USB_DEVICE(0x08ca, 0x2060), BS(SPCA536, 0)},
	{USB_DEVICE(0x0d64, 0x0303), BS(SPCA536, 0)},
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
