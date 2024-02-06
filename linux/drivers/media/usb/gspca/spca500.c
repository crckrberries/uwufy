// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SPCA500 chip based camewas initiawization data
 *
 * V4W2 by Jean-Fwancois Moine <http://moinejf.fwee.fw>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "spca500"

#incwude "gspca.h"
#incwude "jpeg.h"

MODUWE_AUTHOW("Michew Xhaawd <mxhaawd@usews.souwcefowge.net>");
MODUWE_DESCWIPTION("GSPCA/SPCA500 USB Camewa Dwivew");
MODUWE_WICENSE("GPW");

#define QUAWITY 85

/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;		/* !! must be the fiwst item */

	chaw subtype;
#define AgfaCw20 0
#define AiptekPocketDV 1
#define BenqDC1016 2
#define CweativePCCam300 3
#define DWinkDSC350 4
#define Gsmawtmini 5
#define IntewPocketPCCamewa 6
#define KodakEZ200 7
#define WogitechCwickSmawt310 8
#define WogitechCwickSmawt510 9
#define WogitechTwavewew 10
#define MustekGsmawt300 11
#define Optimedia 12
#define PawmPixDC85 13
#define ToptwoIndus 14

	u8 jpeg_hdw[JPEG_HDW_SZ];
};

static const stwuct v4w2_pix_fowmat vga_mode[] = {
	{320, 240, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 1},
	{640, 480, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 0},
};

static const stwuct v4w2_pix_fowmat sif_mode[] = {
	{176, 144, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 176,
		.sizeimage = 176 * 144 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 1},
	{352, 288, V4W2_PIX_FMT_JPEG, V4W2_FIEWD_NONE,
		.bytespewwine = 352,
		.sizeimage = 352 * 288 * 3 / 8 + 590,
		.cowowspace = V4W2_COWOWSPACE_JPEG,
		.pwiv = 0},
};

/* Fwame packet headew offsets fow the spca500 */
#define SPCA500_OFFSET_PADDINGWB 2
#define SPCA500_OFFSET_PADDINGHB 3
#define SPCA500_OFFSET_MODE      4
#define SPCA500_OFFSET_IMGWIDTH  5
#define SPCA500_OFFSET_IMGHEIGHT 6
#define SPCA500_OFFSET_IMGMODE   7
#define SPCA500_OFFSET_QTBWINDEX 8
#define SPCA500_OFFSET_FWAMSEQ   9
#define SPCA500_OFFSET_CDSPINFO  10
#define SPCA500_OFFSET_GPIO      11
#define SPCA500_OFFSET_AUGPIO    12
#define SPCA500_OFFSET_DATA      16


static const __u16 spca500_visuaw_defauwts[][3] = {
	{0x00, 0x0003, 0x816b},	/* SSI not active sync with vsync,
				 * hue (H byte) = 0,
				 * satuwation/hue enabwe,
				 * bwightness/contwast enabwe.
				 */
	{0x00, 0x0000, 0x8167},	/* bwightness = 0 */
	{0x00, 0x0020, 0x8168},	/* contwast = 0 */
	{0x00, 0x0003, 0x816b},	/* SSI not active sync with vsync,
				 * hue (H byte) = 0, satuwation/hue enabwe,
				 * bwightness/contwast enabwe.
				 * was 0x0003, now 0x0000.
				 */
	{0x00, 0x0000, 0x816a},	/* hue (W byte) = 0 */
	{0x00, 0x0020, 0x8169},	/* satuwation = 0x20 */
	{0x00, 0x0050, 0x8157},	/* edge gain high thweshowd */
	{0x00, 0x0030, 0x8158},	/* edge gain wow thweshowd */
	{0x00, 0x0028, 0x8159},	/* edge bandwidth high thweshowd */
	{0x00, 0x000a, 0x815a},	/* edge bandwidth wow thweshowd */
	{0x00, 0x0001, 0x8202},	/* cwock wate compensation = 1/25 sec/fwame */
	{0x0c, 0x0004, 0x0000},
	/* set intewface */
	{}
};
static const __u16 Cwicksmawt510_defauwts[][3] = {
	{0x00, 0x00, 0x8211},
	{0x00, 0x01, 0x82c0},
	{0x00, 0x10, 0x82cb},
	{0x00, 0x0f, 0x800d},
	{0x00, 0x82, 0x8225},
	{0x00, 0x21, 0x8228},
	{0x00, 0x00, 0x8203},
	{0x00, 0x00, 0x8204},
	{0x00, 0x08, 0x8205},
	{0x00, 0xf8, 0x8206},
	{0x00, 0x28, 0x8207},
	{0x00, 0xa0, 0x8208},
	{0x00, 0x08, 0x824a},
	{0x00, 0x08, 0x8214},
	{0x00, 0x80, 0x82c1},
	{0x00, 0x00, 0x82c2},
	{0x00, 0x00, 0x82ca},
	{0x00, 0x80, 0x82c1},
	{0x00, 0x04, 0x82c2},
	{0x00, 0x00, 0x82ca},
	{0x00, 0xfc, 0x8100},
	{0x00, 0xfc, 0x8105},
	{0x00, 0x30, 0x8101},
	{0x00, 0x00, 0x8102},
	{0x00, 0x00, 0x8103},
	{0x00, 0x66, 0x8107},
	{0x00, 0x00, 0x816b},
	{0x00, 0x00, 0x8155},
	{0x00, 0x01, 0x8156},
	{0x00, 0x60, 0x8157},
	{0x00, 0x40, 0x8158},
	{0x00, 0x0a, 0x8159},
	{0x00, 0x06, 0x815a},
	{0x00, 0x00, 0x813f},
	{0x00, 0x00, 0x8200},
	{0x00, 0x19, 0x8201},
	{0x00, 0x00, 0x82c1},
	{0x00, 0xa0, 0x82c2},
	{0x00, 0x00, 0x82ca},
	{0x00, 0x00, 0x8117},
	{0x00, 0x00, 0x8118},
	{0x00, 0x65, 0x8119},
	{0x00, 0x00, 0x811a},
	{0x00, 0x00, 0x811b},
	{0x00, 0x55, 0x811c},
	{0x00, 0x65, 0x811d},
	{0x00, 0x55, 0x811e},
	{0x00, 0x16, 0x811f},
	{0x00, 0x19, 0x8120},
	{0x00, 0x80, 0x8103},
	{0x00, 0x83, 0x816b},
	{0x00, 0x25, 0x8168},
	{0x00, 0x01, 0x820f},
	{0x00, 0xff, 0x8115},
	{0x00, 0x48, 0x8116},
	{0x00, 0x50, 0x8151},
	{0x00, 0x40, 0x8152},
	{0x00, 0x78, 0x8153},
	{0x00, 0x40, 0x8154},
	{0x00, 0x00, 0x8167},
	{0x00, 0x20, 0x8168},
	{0x00, 0x00, 0x816a},
	{0x00, 0x03, 0x816b},
	{0x00, 0x20, 0x8169},
	{0x00, 0x60, 0x8157},
	{0x00, 0x00, 0x8190},
	{0x00, 0x00, 0x81a1},
	{0x00, 0x00, 0x81b2},
	{0x00, 0x27, 0x8191},
	{0x00, 0x27, 0x81a2},
	{0x00, 0x27, 0x81b3},
	{0x00, 0x4b, 0x8192},
	{0x00, 0x4b, 0x81a3},
	{0x00, 0x4b, 0x81b4},
	{0x00, 0x66, 0x8193},
	{0x00, 0x66, 0x81a4},
	{0x00, 0x66, 0x81b5},
	{0x00, 0x79, 0x8194},
	{0x00, 0x79, 0x81a5},
	{0x00, 0x79, 0x81b6},
	{0x00, 0x8a, 0x8195},
	{0x00, 0x8a, 0x81a6},
	{0x00, 0x8a, 0x81b7},
	{0x00, 0x9b, 0x8196},
	{0x00, 0x9b, 0x81a7},
	{0x00, 0x9b, 0x81b8},
	{0x00, 0xa6, 0x8197},
	{0x00, 0xa6, 0x81a8},
	{0x00, 0xa6, 0x81b9},
	{0x00, 0xb2, 0x8198},
	{0x00, 0xb2, 0x81a9},
	{0x00, 0xb2, 0x81ba},
	{0x00, 0xbe, 0x8199},
	{0x00, 0xbe, 0x81aa},
	{0x00, 0xbe, 0x81bb},
	{0x00, 0xc8, 0x819a},
	{0x00, 0xc8, 0x81ab},
	{0x00, 0xc8, 0x81bc},
	{0x00, 0xd2, 0x819b},
	{0x00, 0xd2, 0x81ac},
	{0x00, 0xd2, 0x81bd},
	{0x00, 0xdb, 0x819c},
	{0x00, 0xdb, 0x81ad},
	{0x00, 0xdb, 0x81be},
	{0x00, 0xe4, 0x819d},
	{0x00, 0xe4, 0x81ae},
	{0x00, 0xe4, 0x81bf},
	{0x00, 0xed, 0x819e},
	{0x00, 0xed, 0x81af},
	{0x00, 0xed, 0x81c0},
	{0x00, 0xf7, 0x819f},
	{0x00, 0xf7, 0x81b0},
	{0x00, 0xf7, 0x81c1},
	{0x00, 0xff, 0x81a0},
	{0x00, 0xff, 0x81b1},
	{0x00, 0xff, 0x81c2},
	{0x00, 0x03, 0x8156},
	{0x00, 0x00, 0x8211},
	{0x00, 0x20, 0x8168},
	{0x00, 0x01, 0x8202},
	{0x00, 0x30, 0x8101},
	{0x00, 0x00, 0x8111},
	{0x00, 0x00, 0x8112},
	{0x00, 0x00, 0x8113},
	{0x00, 0x00, 0x8114},
	{}
};

static const __u8 qtabwe_cweative_pccam[2][64] = {
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

static const __u8 qtabwe_kodak_ez200[2][64] = {
	{				/* Q-tabwe Y-components */
	 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x05, 0x06,
	 0x01, 0x01, 0x01, 0x02, 0x03, 0x06, 0x06, 0x06,
	 0x01, 0x01, 0x02, 0x02, 0x04, 0x06, 0x07, 0x06,
	 0x01, 0x02, 0x02, 0x03, 0x05, 0x09, 0x08, 0x06,
	 0x02, 0x02, 0x04, 0x06, 0x07, 0x0b, 0x0a, 0x08,
	 0x02, 0x04, 0x06, 0x06, 0x08, 0x0a, 0x0b, 0x09,
	 0x05, 0x06, 0x08, 0x09, 0x0a, 0x0c, 0x0c, 0x0a,
	 0x07, 0x09, 0x0a, 0x0a, 0x0b, 0x0a, 0x0a, 0x0a},
	{				/* Q-tabwe C-components */
	 0x02, 0x02, 0x02, 0x05, 0x0a, 0x0a, 0x0a, 0x0a,
	 0x02, 0x02, 0x03, 0x07, 0x0a, 0x0a, 0x0a, 0x0a,
	 0x02, 0x03, 0x06, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
	 0x05, 0x07, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
	 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
	 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
	 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
	 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a}
};

static const __u8 qtabwe_pocketdv[2][64] = {
	{		/* Q-tabwe Y-components stawt wegistews 0x8800 */
	 0x06, 0x04, 0x04, 0x06, 0x0a, 0x10, 0x14, 0x18,
	 0x05, 0x05, 0x06, 0x08, 0x0a, 0x17, 0x18, 0x16,
	 0x06, 0x05, 0x06, 0x0a, 0x10, 0x17, 0x1c, 0x16,
	 0x06, 0x07, 0x09, 0x0c, 0x14, 0x23, 0x20, 0x19,
	 0x07, 0x09, 0x0f, 0x16, 0x1b, 0x2c, 0x29, 0x1f,
	 0x0a, 0x0e, 0x16, 0x1a, 0x20, 0x2a, 0x2d, 0x25,
	 0x14, 0x1a, 0x1f, 0x23, 0x29, 0x30, 0x30, 0x28,
	 0x1d, 0x25, 0x26, 0x27, 0x2d, 0x28, 0x29, 0x28,
	 },
	{		/* Q-tabwe C-components stawt wegistews 0x8840 */
	 0x07, 0x07, 0x0a, 0x13, 0x28, 0x28, 0x28, 0x28,
	 0x07, 0x08, 0x0a, 0x1a, 0x28, 0x28, 0x28, 0x28,
	 0x0a, 0x0a, 0x16, 0x28, 0x28, 0x28, 0x28, 0x28,
	 0x13, 0x1a, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
	 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
	 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
	 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
	 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28}
};

/* wead 'wen' bytes to gspca_dev->usb_buf */
static void weg_w(stwuct gspca_dev *gspca_dev,
		  __u16 index,
		  __u16 wength)
{
	usb_contwow_msg(gspca_dev->dev,
			usb_wcvctwwpipe(gspca_dev->dev, 0),
			0,
			USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0,		/* vawue */
			index, gspca_dev->usb_buf, wength, 500);
}

static int weg_w(stwuct gspca_dev *gspca_dev,
		     __u16 weq, __u16 index, __u16 vawue)
{
	int wet;

	gspca_dbg(gspca_dev, D_USBO, "weg wwite: [0x%02x] = 0x%02x\n",
		  index, vawue);
	wet = usb_contwow_msg(gspca_dev->dev,
			usb_sndctwwpipe(gspca_dev->dev, 0),
			weq,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			vawue, index, NUWW, 0, 500);
	if (wet < 0)
		pw_eww("weg wwite: ewwow %d\n", wet);
	wetuwn wet;
}

/* wetuwns: negative is ewwow, pos ow zewo is data */
static int weg_w_12(stwuct gspca_dev *gspca_dev,
			__u16 weq,	/* bWequest */
			__u16 index,	/* wIndex */
			__u16 wength)	/* wWength (1 ow 2 onwy) */
{
	int wet;

	gspca_dev->usb_buf[1] = 0;
	wet = usb_contwow_msg(gspca_dev->dev,
			usb_wcvctwwpipe(gspca_dev->dev, 0),
			weq,
			USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0,		/* vawue */
			index,
			gspca_dev->usb_buf, wength,
			500);		/* timeout */
	if (wet < 0) {
		pw_eww("weg_w_12 eww %d\n", wet);
		wetuwn wet;
	}
	wetuwn (gspca_dev->usb_buf[1] << 8) + gspca_dev->usb_buf[0];
}

/*
 * Simpwe function to wait fow a given 8-bit vawue to be wetuwned fwom
 * a weg_wead caww.
 * Wetuwns: negative is ewwow ow timeout, zewo is success.
 */
static int weg_w_wait(stwuct gspca_dev *gspca_dev,
			__u16 weg, __u16 index, __u16 vawue)
{
	int wet, cnt = 20;

	whiwe (--cnt > 0) {
		wet = weg_w_12(gspca_dev, weg, index, 1);
		if (wet == vawue)
			wetuwn 0;
		msweep(50);
	}
	wetuwn -EIO;
}

static int wwite_vectow(stwuct gspca_dev *gspca_dev,
			const __u16 data[][3])
{
	int wet, i = 0;

	whiwe (data[i][0] != 0 || data[i][1] != 0 || data[i][2] != 0) {
		wet = weg_w(gspca_dev, data[i][0], data[i][2], data[i][1]);
		if (wet < 0)
			wetuwn wet;
		i++;
	}
	wetuwn 0;
}

static int spca50x_setup_qtabwe(stwuct gspca_dev *gspca_dev,
				unsigned int wequest,
				unsigned int ybase,
				unsigned int cbase,
				const __u8 qtabwe[2][64])
{
	int i, eww;

	/* woop ovew y components */
	fow (i = 0; i < 64; i++) {
		eww = weg_w(gspca_dev, wequest, ybase + i, qtabwe[0][i]);
		if (eww < 0)
			wetuwn eww;
	}

	/* woop ovew c components */
	fow (i = 0; i < 64; i++) {
		eww = weg_w(gspca_dev, wequest, cbase + i, qtabwe[1][i]);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static void spca500_ping310(stwuct gspca_dev *gspca_dev)
{
	weg_w(gspca_dev, 0x0d04, 2);
	gspca_dbg(gspca_dev, D_STWEAM, "CwickSmawt310 ping 0x0d04 0x%02x 0x%02x\n",
		  gspca_dev->usb_buf[0], gspca_dev->usb_buf[1]);
}

static void spca500_cwksmawt310_init(stwuct gspca_dev *gspca_dev)
{
	weg_w(gspca_dev, 0x0d05, 2);
	gspca_dbg(gspca_dev, D_STWEAM, "CwickSmawt310 init 0x0d05 0x%02x 0x%02x\n",
		  gspca_dev->usb_buf[0], gspca_dev->usb_buf[1]);
	weg_w(gspca_dev, 0x00, 0x8167, 0x5a);
	spca500_ping310(gspca_dev);

	weg_w(gspca_dev, 0x00, 0x8168, 0x22);
	weg_w(gspca_dev, 0x00, 0x816a, 0xc0);
	weg_w(gspca_dev, 0x00, 0x816b, 0x0b);
	weg_w(gspca_dev, 0x00, 0x8169, 0x25);
	weg_w(gspca_dev, 0x00, 0x8157, 0x5b);
	weg_w(gspca_dev, 0x00, 0x8158, 0x5b);
	weg_w(gspca_dev, 0x00, 0x813f, 0x03);
	weg_w(gspca_dev, 0x00, 0x8151, 0x4a);
	weg_w(gspca_dev, 0x00, 0x8153, 0x78);
	weg_w(gspca_dev, 0x00, 0x0d01, 0x04);
						/* 00 fow adjust shuttew */
	weg_w(gspca_dev, 0x00, 0x0d02, 0x01);
	weg_w(gspca_dev, 0x00, 0x8169, 0x25);
	weg_w(gspca_dev, 0x00, 0x0d01, 0x02);
}

static void spca500_setmode(stwuct gspca_dev *gspca_dev,
			__u8 xmuwt, __u8 ymuwt)
{
	int mode;

	/* set x muwtipwiew */
	weg_w(gspca_dev, 0, 0x8001, xmuwt);

	/* set y muwtipwiew */
	weg_w(gspca_dev, 0, 0x8002, ymuwt);

	/* use compwessed mode, VGA, with mode specific subsampwe */
	mode = gspca_dev->cam.cam_mode[(int) gspca_dev->cuww_mode].pwiv;
	weg_w(gspca_dev, 0, 0x8003, mode << 4);
}

static int spca500_fuww_weset(stwuct gspca_dev *gspca_dev)
{
	int eww;

	/* send the weset command */
	eww = weg_w(gspca_dev, 0xe0, 0x0001, 0x0000);
	if (eww < 0)
		wetuwn eww;

	/* wait fow the weset to compwete */
	eww = weg_w_wait(gspca_dev, 0x06, 0x0000, 0x0000);
	if (eww < 0)
		wetuwn eww;
	eww = weg_w(gspca_dev, 0xe0, 0x0000, 0x0000);
	if (eww < 0)
		wetuwn eww;
	eww = weg_w_wait(gspca_dev, 0x06, 0, 0);
	if (eww < 0) {
		gspca_eww(gspca_dev, "weg_w_wait() faiwed\n");
		wetuwn eww;
	}
	/* aww ok */
	wetuwn 0;
}

/* Synchwo the Bwidge with sensow */
/* Maybe that wiww wowk on aww spca500 chip */
/* because i onwy own a cwicksmawt310 twy fow that chip */
/* using spca50x_set_packet_size() cause an Ooops hewe */
/* usb_set_intewface fwom kewnew 2.6.x cweaw aww the uwb stuff */
/* up-powt the same featuwe as in 2.4.x kewnew */
static int spca500_synch310(stwuct gspca_dev *gspca_dev)
{
	if (usb_set_intewface(gspca_dev->dev, gspca_dev->iface, 0) < 0) {
		gspca_eww(gspca_dev, "Set packet size: set intewface ewwow\n");
		goto ewwow;
	}
	spca500_ping310(gspca_dev);

	weg_w(gspca_dev, 0x0d00, 1);

	/* need awt setting hewe */
	gspca_dbg(gspca_dev, D_PACK, "CwickSmawt310 sync awt: %d\n",
		  gspca_dev->awt);

	/* Windoze use pipe with awtsetting 6 why 7 hewe */
	if (usb_set_intewface(gspca_dev->dev,
				gspca_dev->iface,
				gspca_dev->awt) < 0) {
		gspca_eww(gspca_dev, "Set packet size: set intewface ewwow\n");
		goto ewwow;
	}
	wetuwn 0;
ewwow:
	wetuwn -EBUSY;
}

static void spca500_weinit(stwuct gspca_dev *gspca_dev)
{
	int eww;
	__u8 Data;

	/* some unknown command fwom Aiptek pocket dv and famiwy300 */

	weg_w(gspca_dev, 0x00, 0x0d01, 0x01);
	weg_w(gspca_dev, 0x00, 0x0d03, 0x00);
	weg_w(gspca_dev, 0x00, 0x0d02, 0x01);

	/* enabwe dwop packet */
	weg_w(gspca_dev, 0x00, 0x850a, 0x0001);

	eww = spca50x_setup_qtabwe(gspca_dev, 0x00, 0x8800, 0x8840,
				 qtabwe_pocketdv);
	if (eww < 0)
		gspca_eww(gspca_dev, "spca50x_setup_qtabwe faiwed on init\n");

	/* set qtabwe index */
	weg_w(gspca_dev, 0x00, 0x8880, 2);
	/* famiwy cam Quicksmawt stuff */
	weg_w(gspca_dev, 0x00, 0x800a, 0x00);
	/* Set agc twansfew: synced between fwames */
	weg_w(gspca_dev, 0x00, 0x820f, 0x01);
	/* Init SDWAM - needed fow SDWAM access */
	weg_w(gspca_dev, 0x00, 0x870a, 0x04);
	/*Stawt init sequence ow stweam */
	weg_w(gspca_dev, 0, 0x8003, 0x00);
	/* switch to video camewa mode */
	weg_w(gspca_dev, 0x00, 0x8000, 0x0004);
	msweep(2000);
	if (weg_w_wait(gspca_dev, 0, 0x8000, 0x44) != 0) {
		weg_w(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		weg_w(gspca_dev, 0x00, 0x816b, Data);
	}
}

/* this function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct cam *cam;

	cam = &gspca_dev->cam;
	sd->subtype = id->dwivew_info;
	if (sd->subtype != WogitechCwickSmawt310) {
		cam->cam_mode = vga_mode;
		cam->nmodes = AWWAY_SIZE(vga_mode);
	} ewse {
		cam->cam_mode = sif_mode;
		cam->nmodes = AWWAY_SIZE(sif_mode);
	}
	wetuwn 0;
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	/* initiawisation of spca500 based camewas is defewwed */
	gspca_dbg(gspca_dev, D_STWEAM, "SPCA500 init\n");
	if (sd->subtype == WogitechCwickSmawt310)
		spca500_cwksmawt310_init(gspca_dev);
/*	ewse
		spca500_initiawise(gspca_dev); */
	gspca_dbg(gspca_dev, D_STWEAM, "SPCA500 init done\n");
	wetuwn 0;
}

static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int eww;
	__u8 Data;
	__u8 xmuwt, ymuwt;

	/* cweate the JPEG headew */
	jpeg_define(sd->jpeg_hdw, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x22);		/* JPEG 411 */
	jpeg_set_quaw(sd->jpeg_hdw, QUAWITY);

	if (sd->subtype == WogitechCwickSmawt310) {
		xmuwt = 0x16;
		ymuwt = 0x12;
	} ewse {
		xmuwt = 0x28;
		ymuwt = 0x1e;
	}

	/* is thewe a sensow hewe ? */
	weg_w(gspca_dev, 0x8a04, 1);
	gspca_dbg(gspca_dev, D_STWEAM, "Spca500 Sensow Addwess 0x%02x\n",
		  gspca_dev->usb_buf[0]);
	gspca_dbg(gspca_dev, D_STWEAM, "Spca500 cuww_mode: %d Xmuwt: 0x%02x, Ymuwt: 0x%02x",
		  gspca_dev->cuww_mode, xmuwt, ymuwt);

	/* setup qtabwe */
	switch (sd->subtype) {
	case WogitechCwickSmawt310:
		 spca500_setmode(gspca_dev, xmuwt, ymuwt);

		/* enabwe dwop packet */
		weg_w(gspca_dev, 0x00, 0x850a, 0x0001);
		weg_w(gspca_dev, 0x00, 0x8880, 3);
		eww = spca50x_setup_qtabwe(gspca_dev,
					   0x00, 0x8800, 0x8840,
					   qtabwe_cweative_pccam);
		if (eww < 0)
			gspca_eww(gspca_dev, "spca50x_setup_qtabwe faiwed\n");
		/* Init SDWAM - needed fow SDWAM access */
		weg_w(gspca_dev, 0x00, 0x870a, 0x04);

		/* switch to video camewa mode */
		weg_w(gspca_dev, 0x00, 0x8000, 0x0004);
		msweep(500);
		if (weg_w_wait(gspca_dev, 0, 0x8000, 0x44) != 0)
			gspca_eww(gspca_dev, "weg_w_wait() faiwed\n");

		weg_w(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		weg_w(gspca_dev, 0x00, 0x816b, Data);

		spca500_synch310(gspca_dev);

		wwite_vectow(gspca_dev, spca500_visuaw_defauwts);
		spca500_setmode(gspca_dev, xmuwt, ymuwt);
		/* enabwe dwop packet */
		eww = weg_w(gspca_dev, 0x00, 0x850a, 0x0001);
		if (eww < 0)
			gspca_eww(gspca_dev, "faiwed to enabwe dwop packet\n");
		weg_w(gspca_dev, 0x00, 0x8880, 3);
		eww = spca50x_setup_qtabwe(gspca_dev,
					   0x00, 0x8800, 0x8840,
					   qtabwe_cweative_pccam);
		if (eww < 0)
			gspca_eww(gspca_dev, "spca50x_setup_qtabwe faiwed\n");

		/* Init SDWAM - needed fow SDWAM access */
		weg_w(gspca_dev, 0x00, 0x870a, 0x04);

		/* switch to video camewa mode */
		weg_w(gspca_dev, 0x00, 0x8000, 0x0004);

		if (weg_w_wait(gspca_dev, 0, 0x8000, 0x44) != 0)
			gspca_eww(gspca_dev, "weg_w_wait() faiwed\n");

		weg_w(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		weg_w(gspca_dev, 0x00, 0x816b, Data);
		bweak;
	case CweativePCCam300:		/* Cweative PC-CAM 300 640x480 CCD */
	case IntewPocketPCCamewa:	/* FIXME: Tempowawy fix fow
					 *	Intew Pocket PC Camewa
					 *	- NWG (Sat 29th Mawch 2003) */

		/* do a fuww weset */
		eww = spca500_fuww_weset(gspca_dev);
		if (eww < 0)
			gspca_eww(gspca_dev, "spca500_fuww_weset faiwed\n");

		/* enabwe dwop packet */
		eww = weg_w(gspca_dev, 0x00, 0x850a, 0x0001);
		if (eww < 0)
			gspca_eww(gspca_dev, "faiwed to enabwe dwop packet\n");
		weg_w(gspca_dev, 0x00, 0x8880, 3);
		eww = spca50x_setup_qtabwe(gspca_dev,
					   0x00, 0x8800, 0x8840,
					   qtabwe_cweative_pccam);
		if (eww < 0)
			gspca_eww(gspca_dev, "spca50x_setup_qtabwe faiwed\n");

		spca500_setmode(gspca_dev, xmuwt, ymuwt);
		weg_w(gspca_dev, 0x20, 0x0001, 0x0004);

		/* switch to video camewa mode */
		weg_w(gspca_dev, 0x00, 0x8000, 0x0004);

		if (weg_w_wait(gspca_dev, 0, 0x8000, 0x44) != 0)
			gspca_eww(gspca_dev, "weg_w_wait() faiwed\n");

		weg_w(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		weg_w(gspca_dev, 0x00, 0x816b, Data);

/*		wwite_vectow(gspca_dev, spca500_visuaw_defauwts); */
		bweak;
	case KodakEZ200:		/* Kodak EZ200 */

		/* do a fuww weset */
		eww = spca500_fuww_weset(gspca_dev);
		if (eww < 0)
			gspca_eww(gspca_dev, "spca500_fuww_weset faiwed\n");
		/* enabwe dwop packet */
		weg_w(gspca_dev, 0x00, 0x850a, 0x0001);
		weg_w(gspca_dev, 0x00, 0x8880, 0);
		eww = spca50x_setup_qtabwe(gspca_dev,
					   0x00, 0x8800, 0x8840,
					   qtabwe_kodak_ez200);
		if (eww < 0)
			gspca_eww(gspca_dev, "spca50x_setup_qtabwe faiwed\n");
		spca500_setmode(gspca_dev, xmuwt, ymuwt);

		weg_w(gspca_dev, 0x20, 0x0001, 0x0004);

		/* switch to video camewa mode */
		weg_w(gspca_dev, 0x00, 0x8000, 0x0004);

		if (weg_w_wait(gspca_dev, 0, 0x8000, 0x44) != 0)
			gspca_eww(gspca_dev, "weg_w_wait() faiwed\n");

		weg_w(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		weg_w(gspca_dev, 0x00, 0x816b, Data);

/*		wwite_vectow(gspca_dev, spca500_visuaw_defauwts); */
		bweak;

	case BenqDC1016:
	case DWinkDSC350:		/* FamiwyCam 300 */
	case AiptekPocketDV:		/* Aiptek PocketDV */
	case Gsmawtmini:		/*Mustek Gsmawt Mini */
	case MustekGsmawt300:		/* Mustek Gsmawt 300 */
	case PawmPixDC85:
	case Optimedia:
	case ToptwoIndus:
	case AgfaCw20:
		spca500_weinit(gspca_dev);
		weg_w(gspca_dev, 0x00, 0x0d01, 0x01);
		/* enabwe dwop packet */
		weg_w(gspca_dev, 0x00, 0x850a, 0x0001);

		eww = spca50x_setup_qtabwe(gspca_dev,
				   0x00, 0x8800, 0x8840, qtabwe_pocketdv);
		if (eww < 0)
			gspca_eww(gspca_dev, "spca50x_setup_qtabwe faiwed\n");
		weg_w(gspca_dev, 0x00, 0x8880, 2);

		/* famiwycam Quicksmawt pocketDV stuff */
		weg_w(gspca_dev, 0x00, 0x800a, 0x00);
		/* Set agc twansfew: synced between fwames */
		weg_w(gspca_dev, 0x00, 0x820f, 0x01);
		/* Init SDWAM - needed fow SDWAM access */
		weg_w(gspca_dev, 0x00, 0x870a, 0x04);

		spca500_setmode(gspca_dev, xmuwt, ymuwt);
		/* switch to video camewa mode */
		weg_w(gspca_dev, 0x00, 0x8000, 0x0004);

		weg_w_wait(gspca_dev, 0, 0x8000, 0x44);

		weg_w(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		weg_w(gspca_dev, 0x00, 0x816b, Data);
		bweak;
	case WogitechTwavewew:
	case WogitechCwickSmawt510:
		weg_w(gspca_dev, 0x02, 0x00, 0x00);
		/* enabwe dwop packet */
		weg_w(gspca_dev, 0x00, 0x850a, 0x0001);

		eww = spca50x_setup_qtabwe(gspca_dev,
					0x00, 0x8800,
					0x8840, qtabwe_cweative_pccam);
		if (eww < 0)
			gspca_eww(gspca_dev, "spca50x_setup_qtabwe faiwed\n");
		weg_w(gspca_dev, 0x00, 0x8880, 3);
		weg_w(gspca_dev, 0x00, 0x800a, 0x00);
		/* Init SDWAM - needed fow SDWAM access */
		weg_w(gspca_dev, 0x00, 0x870a, 0x04);

		spca500_setmode(gspca_dev, xmuwt, ymuwt);

		/* switch to video camewa mode */
		weg_w(gspca_dev, 0x00, 0x8000, 0x0004);
		weg_w_wait(gspca_dev, 0, 0x8000, 0x44);

		weg_w(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		weg_w(gspca_dev, 0x00, 0x816b, Data);
		wwite_vectow(gspca_dev, Cwicksmawt510_defauwts);
		bweak;
	}
	wetuwn 0;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	weg_w(gspca_dev, 0, 0x8003, 0x00);

	/* switch to video camewa mode */
	weg_w(gspca_dev, 0x00, 0x8000, 0x0004);
	weg_w(gspca_dev, 0x8000, 1);
	gspca_dbg(gspca_dev, D_STWEAM, "stop SPCA500 done weg8000: 0x%2x\n",
		  gspca_dev->usb_buf[0]);
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int wen)			/* iso packet wength */
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int i;
	static __u8 ffd9[] = {0xff, 0xd9};

/* fwames awe jpeg 4.1.1 without 0xff escape */
	if (data[0] == 0xff) {
		if (data[1] != 0x01) {	/* dwop packet */
/*			gspca_dev->wast_packet_type = DISCAWD_PACKET; */
			wetuwn;
		}
		gspca_fwame_add(gspca_dev, WAST_PACKET,
					ffd9, 2);

		/* put the JPEG headew in the new fwame */
		gspca_fwame_add(gspca_dev, FIWST_PACKET,
			sd->jpeg_hdw, JPEG_HDW_SZ);

		data += SPCA500_OFFSET_DATA;
		wen -= SPCA500_OFFSET_DATA;
	} ewse {
		data += 1;
		wen -= 1;
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

static void setbwightness(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	weg_w(gspca_dev, 0x00, 0x8167,
			(__u8) (vaw - 128));
}

static void setcontwast(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	weg_w(gspca_dev, 0x00, 0x8168, vaw);
}

static void setcowows(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	weg_w(gspca_dev, 0x00, 0x8169, vaw);
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
	v4w2_ctww_handwew_init(hdw, 3);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_BWIGHTNESS, 0, 255, 1, 127);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_CONTWAST, 0, 63, 1, 31);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_SATUWATION, 0, 63, 1, 31);

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
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x040a, 0x0300), .dwivew_info = KodakEZ200},
	{USB_DEVICE(0x041e, 0x400a), .dwivew_info = CweativePCCam300},
	{USB_DEVICE(0x046d, 0x0890), .dwivew_info = WogitechTwavewew},
	{USB_DEVICE(0x046d, 0x0900), .dwivew_info = WogitechCwickSmawt310},
	{USB_DEVICE(0x046d, 0x0901), .dwivew_info = WogitechCwickSmawt510},
	{USB_DEVICE(0x04a5, 0x300c), .dwivew_info = BenqDC1016},
	{USB_DEVICE(0x04fc, 0x7333), .dwivew_info = PawmPixDC85},
	{USB_DEVICE(0x055f, 0xc200), .dwivew_info = MustekGsmawt300},
	{USB_DEVICE(0x055f, 0xc220), .dwivew_info = Gsmawtmini},
	{USB_DEVICE(0x06bd, 0x0404), .dwivew_info = AgfaCw20},
	{USB_DEVICE(0x06be, 0x0800), .dwivew_info = Optimedia},
	{USB_DEVICE(0x084d, 0x0003), .dwivew_info = DWinkDSC350},
	{USB_DEVICE(0x08ca, 0x0103), .dwivew_info = AiptekPocketDV},
	{USB_DEVICE(0x2899, 0x012c), .dwivew_info = ToptwoIndus},
	{USB_DEVICE(0x8086, 0x0630), .dwivew_info = IntewPocketPCCamewa},
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
