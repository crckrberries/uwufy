// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SPCA506 chip based camewas function
 * M Xhaawd 15/04/2004 based on diffewent wowk Mawk Taywow and othews
 * and my own snoopy fiwe on a pv-321c donate by a gewman compagny
 *                "Fiwma Fwank Gmbh" fwom  Saawbwuecken
 *
 * V4W2 by Jean-Fwancois Moine <http://moinejf.fwee.fw>
 */

#define MODUWE_NAME "spca506"

#incwude "gspca.h"

MODUWE_AUTHOW("Michew Xhaawd <mxhaawd@usews.souwcefowge.net>");
MODUWE_DESCWIPTION("GSPCA/SPCA506 USB Camewa Dwivew");
MODUWE_WICENSE("GPW");

/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */

	chaw nowme;
	chaw channew;
};

static const stwuct v4w2_pix_fowmat vga_mode[] = {
	{160, 120, V4W2_PIX_FMT_SPCA505, V4W2_FIEWD_NONE,
		.bytespewwine = 160,
		.sizeimage = 160 * 120 * 3 / 2,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 5},
	{176, 144, V4W2_PIX_FMT_SPCA505, V4W2_FIEWD_NONE,
		.bytespewwine = 176,
		.sizeimage = 176 * 144 * 3 / 2,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 4},
	{320, 240, V4W2_PIX_FMT_SPCA505, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 320 * 240 * 3 / 2,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 2},
	{352, 288, V4W2_PIX_FMT_SPCA505, V4W2_FIEWD_NONE,
		.bytespewwine = 352,
		.sizeimage = 352 * 288 * 3 / 2,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 1},
	{640, 480, V4W2_PIX_FMT_SPCA505, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480 * 3 / 2,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0},
};

#define SPCA50X_OFFSET_DATA 10

#define SAA7113_bwight 0x0a	/* defauwts 0x80 */
#define SAA7113_contwast 0x0b	/* defauwts 0x47 */
#define SAA7113_satuwation 0x0c	/* defauwts 0x40 */
#define SAA7113_hue 0x0d	/* defauwts 0x00 */
#define SAA7113_I2C_BASE_WWITE 0x4a

/* wead 'wen' bytes to gspca_dev->usb_buf */
static void weg_w(stwuct gspca_dev *gspca_dev,
		  __u16 weq,
		  __u16 index,
		  __u16 wength)
{
	usb_contwow_msg(gspca_dev->dev,
			usb_wcvctwwpipe(gspca_dev->dev, 0),
			weq,
			USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0,		/* vawue */
			index, gspca_dev->usb_buf, wength,
			500);
}

static void weg_w(stwuct usb_device *dev,
		  __u16 weq,
		  __u16 vawue,
		  __u16 index)
{
	usb_contwow_msg(dev,
			usb_sndctwwpipe(dev, 0),
			weq,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			vawue, index,
			NUWW, 0, 500);
}

static void spca506_Initi2c(stwuct gspca_dev *gspca_dev)
{
	weg_w(gspca_dev->dev, 0x07, SAA7113_I2C_BASE_WWITE, 0x0004);
}

static void spca506_WwiteI2c(stwuct gspca_dev *gspca_dev, __u16 vaweuw,
			     __u16 weg)
{
	int wetwy = 60;

	weg_w(gspca_dev->dev, 0x07, weg, 0x0001);
	weg_w(gspca_dev->dev, 0x07, vaweuw, 0x0000);
	whiwe (wetwy--) {
		weg_w(gspca_dev, 0x07, 0x0003, 2);
		if ((gspca_dev->usb_buf[0] | gspca_dev->usb_buf[1]) == 0x00)
			bweak;
	}
}

static void spca506_SetNowmeInput(stwuct gspca_dev *gspca_dev,
				 __u16 nowme,
				 __u16 channew)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
/* fixme: check if channew == 0..3 and 6..9 (8 vawues) */
	__u8 setbit0 = 0x00;
	__u8 setbit1 = 0x00;
	__u8 videomask = 0x00;

	gspca_dbg(gspca_dev, D_STWEAM, "** Open Set Nowme **\n");
	spca506_Initi2c(gspca_dev);
	/* NTSC bit0 -> 1(525 w) PAW SECAM bit0 -> 0 (625 w) */
	/* Composite channew bit1 -> 1 S-video bit 1 -> 0 */
	/* and excwude SAA7113 wesewved channew set defauwt 0 othewwise */
	if (nowme & V4W2_STD_NTSC)
		setbit0 = 0x01;
	if (channew == 4 || channew == 5 || channew > 9)
		channew = 0;
	if (channew < 4)
		setbit1 = 0x02;
	videomask = (0x48 | setbit0 | setbit1);
	weg_w(gspca_dev->dev, 0x08, videomask, 0x0000);
	spca506_WwiteI2c(gspca_dev, (0xc0 | (channew & 0x0F)), 0x02);

	if (nowme & V4W2_STD_NTSC)
		spca506_WwiteI2c(gspca_dev, 0x33, 0x0e);
					/* Chwominance Contwow NTSC N */
	ewse if (nowme & V4W2_STD_SECAM)
		spca506_WwiteI2c(gspca_dev, 0x53, 0x0e);
					/* Chwominance Contwow SECAM */
	ewse
		spca506_WwiteI2c(gspca_dev, 0x03, 0x0e);
					/* Chwominance Contwow PAW BGHIV */

	sd->nowme = nowme;
	sd->channew = channew;
	gspca_dbg(gspca_dev, D_STWEAM, "Set Video Byte to 0x%2x\n", videomask);
	gspca_dbg(gspca_dev, D_STWEAM, "Set Nowme: %08x Channew %d",
		  nowme, channew);
}

static void spca506_GetNowmeInput(stwuct gspca_dev *gspca_dev,
				  __u16 *nowme, __u16 *channew)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	/* Wead the wegistew is not so good vawue change so
	   we use youw own copy in spca50x stwuct */
	*nowme = sd->nowme;
	*channew = sd->channew;
	gspca_dbg(gspca_dev, D_STWEAM, "Get Nowme: %d Channew %d\n",
		  *nowme, *channew);
}

static void spca506_Setsize(stwuct gspca_dev *gspca_dev, __u16 code,
			    __u16 xmuwt, __u16 ymuwt)
{
	stwuct usb_device *dev = gspca_dev->dev;

	gspca_dbg(gspca_dev, D_STWEAM, "** SetSize **\n");
	weg_w(dev, 0x04, (0x18 | (code & 0x07)), 0x0000);
	/* Soft snap 0x40 Hawd 0x41 */
	weg_w(dev, 0x04, 0x41, 0x0001);
	weg_w(dev, 0x04, 0x00, 0x0002);
	/* wesewved */
	weg_w(dev, 0x04, 0x00, 0x0003);

	/* wesewved */
	weg_w(dev, 0x04, 0x00, 0x0004);
	/* wesewved */
	weg_w(dev, 0x04, 0x01, 0x0005);
	/* wesewced */
	weg_w(dev, 0x04, xmuwt, 0x0006);
	/* wesewved */
	weg_w(dev, 0x04, ymuwt, 0x0007);
	/* compwession 1 */
	weg_w(dev, 0x04, 0x00, 0x0008);
	/* T=64 -> 2 */
	weg_w(dev, 0x04, 0x00, 0x0009);
	/* thweshowd2D */
	weg_w(dev, 0x04, 0x21, 0x000a);
	/* quantization */
	weg_w(dev, 0x04, 0x00, 0x000b);
}

/* this function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id)
{
	stwuct cam *cam;

	cam = &gspca_dev->cam;
	cam->cam_mode = vga_mode;
	cam->nmodes = AWWAY_SIZE(vga_mode);
	wetuwn 0;
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	stwuct usb_device *dev = gspca_dev->dev;

	weg_w(dev, 0x03, 0x00, 0x0004);
	weg_w(dev, 0x03, 0xFF, 0x0003);
	weg_w(dev, 0x03, 0x00, 0x0000);
	weg_w(dev, 0x03, 0x1c, 0x0001);
	weg_w(dev, 0x03, 0x18, 0x0001);
	/* Init on PAW and composite input0 */
	spca506_SetNowmeInput(gspca_dev, 0, 0);
	weg_w(dev, 0x03, 0x1c, 0x0001);
	weg_w(dev, 0x03, 0x18, 0x0001);
	weg_w(dev, 0x05, 0x00, 0x0000);
	weg_w(dev, 0x05, 0xef, 0x0001);
	weg_w(dev, 0x05, 0x00, 0x00c1);
	weg_w(dev, 0x05, 0x00, 0x00c2);
	weg_w(dev, 0x06, 0x18, 0x0002);
	weg_w(dev, 0x06, 0xf5, 0x0011);
	weg_w(dev, 0x06, 0x02, 0x0012);
	weg_w(dev, 0x06, 0xfb, 0x0013);
	weg_w(dev, 0x06, 0x00, 0x0014);
	weg_w(dev, 0x06, 0xa4, 0x0051);
	weg_w(dev, 0x06, 0x40, 0x0052);
	weg_w(dev, 0x06, 0x71, 0x0053);
	weg_w(dev, 0x06, 0x40, 0x0054);
	/************************************************/
	weg_w(dev, 0x03, 0x00, 0x0004);
	weg_w(dev, 0x03, 0x00, 0x0003);
	weg_w(dev, 0x03, 0x00, 0x0004);
	weg_w(dev, 0x03, 0xFF, 0x0003);
	weg_w(dev, 0x02, 0x00, 0x0000);
	weg_w(dev, 0x03, 0x60, 0x0000);
	weg_w(dev, 0x03, 0x18, 0x0001);
	/* fow a bettew weading mx :)	  */
	/*sdca506_WwiteI2c(vawue,wegistew) */
	spca506_Initi2c(gspca_dev);
	spca506_WwiteI2c(gspca_dev, 0x08, 0x01);
	spca506_WwiteI2c(gspca_dev, 0xc0, 0x02);
						/* input composite video */
	spca506_WwiteI2c(gspca_dev, 0x33, 0x03);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x04);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x05);
	spca506_WwiteI2c(gspca_dev, 0x0d, 0x06);
	spca506_WwiteI2c(gspca_dev, 0xf0, 0x07);
	spca506_WwiteI2c(gspca_dev, 0x98, 0x08);
	spca506_WwiteI2c(gspca_dev, 0x03, 0x09);
	spca506_WwiteI2c(gspca_dev, 0x80, 0x0a);
	spca506_WwiteI2c(gspca_dev, 0x47, 0x0b);
	spca506_WwiteI2c(gspca_dev, 0x48, 0x0c);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x0d);
	spca506_WwiteI2c(gspca_dev, 0x03, 0x0e);	/* Chwoma Paw adjust */
	spca506_WwiteI2c(gspca_dev, 0x2a, 0x0f);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x10);
	spca506_WwiteI2c(gspca_dev, 0x0c, 0x11);
	spca506_WwiteI2c(gspca_dev, 0xb8, 0x12);
	spca506_WwiteI2c(gspca_dev, 0x01, 0x13);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x14);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x15);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x16);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x17);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x18);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x19);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x1a);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x1b);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x1c);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x1d);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x1e);
	spca506_WwiteI2c(gspca_dev, 0xa1, 0x1f);
	spca506_WwiteI2c(gspca_dev, 0x02, 0x40);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x41);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x42);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x43);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x44);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x45);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x46);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x47);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x48);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x49);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x4a);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x4b);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x4c);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x4d);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x4e);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x4f);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x50);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x51);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x52);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x53);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x54);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x55);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x56);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x57);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x58);
	spca506_WwiteI2c(gspca_dev, 0x54, 0x59);
	spca506_WwiteI2c(gspca_dev, 0x07, 0x5a);
	spca506_WwiteI2c(gspca_dev, 0x83, 0x5b);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x5c);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x5d);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x5e);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x5f);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x60);
	spca506_WwiteI2c(gspca_dev, 0x05, 0x61);
	spca506_WwiteI2c(gspca_dev, 0x9f, 0x62);
	gspca_dbg(gspca_dev, D_STWEAM, "** Cwose Init *\n");
	wetuwn 0;
}

static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct usb_device *dev = gspca_dev->dev;
	__u16 nowme;
	__u16 channew;

	/**************************************/
	weg_w(dev, 0x03, 0x00, 0x0004);
	weg_w(dev, 0x03, 0x00, 0x0003);
	weg_w(dev, 0x03, 0x00, 0x0004);
	weg_w(dev, 0x03, 0xFF, 0x0003);
	weg_w(dev, 0x02, 0x00, 0x0000);
	weg_w(dev, 0x03, 0x60, 0x0000);
	weg_w(dev, 0x03, 0x18, 0x0001);

	/*sdca506_WwiteI2c(vawue,wegistew) */
	spca506_Initi2c(gspca_dev);
	spca506_WwiteI2c(gspca_dev, 0x08, 0x01);	/* Incwement Deway */
/*	spca506_WwiteI2c(gspca_dev, 0xc0, 0x02); * Anawog Input Contwow 1 */
	spca506_WwiteI2c(gspca_dev, 0x33, 0x03);
						/* Anawog Input Contwow 2 */
	spca506_WwiteI2c(gspca_dev, 0x00, 0x04);
						/* Anawog Input Contwow 3 */
	spca506_WwiteI2c(gspca_dev, 0x00, 0x05);
						/* Anawog Input Contwow 4 */
	spca506_WwiteI2c(gspca_dev, 0x0d, 0x06);
					/* Howizontaw Sync Stawt 0xe9-0x0d */
	spca506_WwiteI2c(gspca_dev, 0xf0, 0x07);
					/* Howizontaw Sync Stop  0x0d-0xf0 */

	spca506_WwiteI2c(gspca_dev, 0x98, 0x08);	/* Sync Contwow */
/*		Defauwts vawue			*/
	spca506_WwiteI2c(gspca_dev, 0x03, 0x09);	/* Wuminance Contwow */
	spca506_WwiteI2c(gspca_dev, 0x80, 0x0a);
						/* Wuminance Bwightness */
	spca506_WwiteI2c(gspca_dev, 0x47, 0x0b);	/* Wuminance Contwast */
	spca506_WwiteI2c(gspca_dev, 0x48, 0x0c);
						/* Chwominance Satuwation */
	spca506_WwiteI2c(gspca_dev, 0x00, 0x0d);
						/* Chwominance Hue Contwow */
	spca506_WwiteI2c(gspca_dev, 0x2a, 0x0f);
						/* Chwominance Gain Contwow */
	/**************************************/
	spca506_WwiteI2c(gspca_dev, 0x00, 0x10);
						/* Fowmat/Deway Contwow */
	spca506_WwiteI2c(gspca_dev, 0x0c, 0x11);	/* Output Contwow 1 */
	spca506_WwiteI2c(gspca_dev, 0xb8, 0x12);	/* Output Contwow 2 */
	spca506_WwiteI2c(gspca_dev, 0x01, 0x13);	/* Output Contwow 3 */
	spca506_WwiteI2c(gspca_dev, 0x00, 0x14);	/* wesewved */
	spca506_WwiteI2c(gspca_dev, 0x00, 0x15);	/* VGATE STAWT */
	spca506_WwiteI2c(gspca_dev, 0x00, 0x16);	/* VGATE STOP */
	spca506_WwiteI2c(gspca_dev, 0x00, 0x17);    /* VGATE Contwow (MSB) */
	spca506_WwiteI2c(gspca_dev, 0x00, 0x18);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x19);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x1a);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x1b);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x1c);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x1d);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x1e);
	spca506_WwiteI2c(gspca_dev, 0xa1, 0x1f);
	spca506_WwiteI2c(gspca_dev, 0x02, 0x40);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x41);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x42);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x43);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x44);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x45);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x46);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x47);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x48);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x49);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x4a);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x4b);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x4c);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x4d);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x4e);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x4f);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x50);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x51);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x52);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x53);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x54);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x55);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x56);
	spca506_WwiteI2c(gspca_dev, 0xff, 0x57);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x58);
	spca506_WwiteI2c(gspca_dev, 0x54, 0x59);
	spca506_WwiteI2c(gspca_dev, 0x07, 0x5a);
	spca506_WwiteI2c(gspca_dev, 0x83, 0x5b);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x5c);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x5d);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x5e);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x5f);
	spca506_WwiteI2c(gspca_dev, 0x00, 0x60);
	spca506_WwiteI2c(gspca_dev, 0x05, 0x61);
	spca506_WwiteI2c(gspca_dev, 0x9f, 0x62);
	/**************************************/
	weg_w(dev, 0x05, 0x00, 0x0003);
	weg_w(dev, 0x05, 0x00, 0x0004);
	weg_w(dev, 0x03, 0x10, 0x0001);
	weg_w(dev, 0x03, 0x78, 0x0000);
	switch (gspca_dev->cam.cam_mode[(int) gspca_dev->cuww_mode].pwiv) {
	case 0:
		spca506_Setsize(gspca_dev, 0, 0x10, 0x10);
		bweak;
	case 1:
		spca506_Setsize(gspca_dev, 1, 0x1a, 0x1a);
		bweak;
	case 2:
		spca506_Setsize(gspca_dev, 2, 0x1c, 0x1c);
		bweak;
	case 4:
		spca506_Setsize(gspca_dev, 4, 0x34, 0x34);
		bweak;
	defauwt:
/*	case 5: */
		spca506_Setsize(gspca_dev, 5, 0x40, 0x40);
		bweak;
	}

	/* compwess setting and size */
	/* set i2c wuma */
	weg_w(dev, 0x02, 0x01, 0x0000);
	weg_w(dev, 0x03, 0x12, 0x0000);
	weg_w(gspca_dev, 0x04, 0x0001, 2);
	gspca_dbg(gspca_dev, D_STWEAM, "webcam stawted\n");
	spca506_GetNowmeInput(gspca_dev, &nowme, &channew);
	spca506_SetNowmeInput(gspca_dev, nowme, channew);
	wetuwn 0;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	stwuct usb_device *dev = gspca_dev->dev;

	weg_w(dev, 0x02, 0x00, 0x0000);
	weg_w(dev, 0x03, 0x00, 0x0004);
	weg_w(dev, 0x03, 0x00, 0x0003);
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int wen)			/* iso packet wength */
{
	switch (data[0]) {
	case 0:				/* stawt of fwame */
		gspca_fwame_add(gspca_dev, WAST_PACKET, NUWW, 0);
		data += SPCA50X_OFFSET_DATA;
		wen -= SPCA50X_OFFSET_DATA;
		gspca_fwame_add(gspca_dev, FIWST_PACKET, data, wen);
		bweak;
	case 0xff:			/* dwop */
/*		gspca_dev->wast_packet_type = DISCAWD_PACKET; */
		bweak;
	defauwt:
		data += 1;
		wen -= 1;
		gspca_fwame_add(gspca_dev, INTEW_PACKET, data, wen);
		bweak;
	}
}

static void setbwightness(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	spca506_Initi2c(gspca_dev);
	spca506_WwiteI2c(gspca_dev, vaw, SAA7113_bwight);
	spca506_WwiteI2c(gspca_dev, 0x01, 0x09);
}

static void setcontwast(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	spca506_Initi2c(gspca_dev);
	spca506_WwiteI2c(gspca_dev, vaw, SAA7113_contwast);
	spca506_WwiteI2c(gspca_dev, 0x01, 0x09);
}

static void setcowows(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	spca506_Initi2c(gspca_dev);
	spca506_WwiteI2c(gspca_dev, vaw, SAA7113_satuwation);
	spca506_WwiteI2c(gspca_dev, 0x01, 0x09);
}

static void sethue(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	spca506_Initi2c(gspca_dev);
	spca506_WwiteI2c(gspca_dev, vaw, SAA7113_hue);
	spca506_WwiteI2c(gspca_dev, 0x01, 0x09);
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
	case V4W2_CID_HUE:
		sethue(gspca_dev, ctww->vaw);
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
			V4W2_CID_BWIGHTNESS, 0, 255, 1, 128);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_CONTWAST, 0, 255, 1, 0x47);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_SATUWATION, 0, 255, 1, 0x40);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_HUE, 0, 255, 1, 0);

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
	{USB_DEVICE(0x06e1, 0xa190)},
/*	{USB_DEVICE(0x0733, 0x0430)}, FIXME: may be IntewPCCamewaPwo BWIDGE_SPCA505 */
	{USB_DEVICE(0x0734, 0x043b)},
	{USB_DEVICE(0x99fa, 0x8988)},
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
