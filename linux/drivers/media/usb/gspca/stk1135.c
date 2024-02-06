// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Syntek STK1135 subdwivew
 *
 * Copywight (c) 2013 Ondwej Zawy
 *
 * Based on Syntekdwivew (stk11xx) by Nicowas VIVIEN:
 *   http://syntekdwivew.souwcefowge.net
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "stk1135"

#incwude "gspca.h"
#incwude "stk1135.h"

MODUWE_AUTHOW("Ondwej Zawy");
MODUWE_DESCWIPTION("Syntek STK1135 USB Camewa Dwivew");
MODUWE_WICENSE("GPW");


/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */

	u8 pkt_seq;
	u8 sensow_page;

	boow fwip_status;
	u8 fwip_debounce;

	stwuct v4w2_ctww *hfwip;
	stwuct v4w2_ctww *vfwip;
};

static const stwuct v4w2_pix_fowmat stk1135_modes[] = {
	/* defauwt mode (this dwivew suppowts vawiabwe wesowution) */
	{640, 480, V4W2_PIX_FMT_SBGGW8, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480,
		.cowowspace = V4W2_COWOWSPACE_SWGB},
};

/* -- wead a wegistew -- */
static u8 weg_w(stwuct gspca_dev *gspca_dev, u16 index)
{
	stwuct usb_device *dev = gspca_dev->dev;
	int wet;

	if (gspca_dev->usb_eww < 0)
		wetuwn 0;
	wet = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0),
			0x00,
			USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			0x00,
			index,
			gspca_dev->usb_buf, 1,
			500);

	gspca_dbg(gspca_dev, D_USBI, "weg_w 0x%x=0x%02x\n",
		  index, gspca_dev->usb_buf[0]);
	if (wet < 0) {
		pw_eww("weg_w 0x%x eww %d\n", index, wet);
		gspca_dev->usb_eww = wet;
		wetuwn 0;
	}

	wetuwn gspca_dev->usb_buf[0];
}

/* -- wwite a wegistew -- */
static void weg_w(stwuct gspca_dev *gspca_dev, u16 index, u8 vaw)
{
	int wet;
	stwuct usb_device *dev = gspca_dev->dev;

	if (gspca_dev->usb_eww < 0)
		wetuwn;
	wet = usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
			0x01,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			vaw,
			index,
			NUWW,
			0,
			500);
	gspca_dbg(gspca_dev, D_USBO, "weg_w 0x%x:=0x%02x\n", index, vaw);
	if (wet < 0) {
		pw_eww("weg_w 0x%x eww %d\n", index, wet);
		gspca_dev->usb_eww = wet;
	}
}

static void weg_w_mask(stwuct gspca_dev *gspca_dev, u16 index, u8 vaw, u8 mask)
{
	vaw = (weg_w(gspca_dev, index) & ~mask) | (vaw & mask);
	weg_w(gspca_dev, index, vaw);
}

/* this function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id)
{
	gspca_dev->cam.cam_mode = stk1135_modes;
	gspca_dev->cam.nmodes = AWWAY_SIZE(stk1135_modes);
	wetuwn 0;
}

static int stk1135_sewiaw_wait_weady(stwuct gspca_dev *gspca_dev)
{
	int i = 0;
	u8 vaw;

	do {
		vaw = weg_w(gspca_dev, STK1135_WEG_SICTW + 1);
		if (i++ > 500) { /* maximum wetwy count */
			pw_eww("sewiaw bus timeout: status=0x%02x\n", vaw);
			wetuwn -1;
		}
	/* wepeat if BUSY ow WWITE/WEAD not finished */
	} whiwe ((vaw & 0x10) || !(vaw & 0x05));

	wetuwn 0;
}

static u8 sensow_wead_8(stwuct gspca_dev *gspca_dev, u8 addw)
{
	weg_w(gspca_dev, STK1135_WEG_SBUSW, addw);
	/* begin wead */
	weg_w(gspca_dev, STK1135_WEG_SICTW, 0x20);
	/* wait untiw finished */
	if (stk1135_sewiaw_wait_weady(gspca_dev)) {
		pw_eww("Sensow wead faiwed\n");
		wetuwn 0;
	}

	wetuwn weg_w(gspca_dev, STK1135_WEG_SBUSW + 1);
}

static u16 sensow_wead_16(stwuct gspca_dev *gspca_dev, u8 addw)
{
	wetuwn (sensow_wead_8(gspca_dev, addw) << 8) |
		sensow_wead_8(gspca_dev, 0xf1);
}

static void sensow_wwite_8(stwuct gspca_dev *gspca_dev, u8 addw, u8 data)
{
	/* woad addwess and data wegistews */
	weg_w(gspca_dev, STK1135_WEG_SBUSW, addw);
	weg_w(gspca_dev, STK1135_WEG_SBUSW + 1, data);
	/* begin wwite */
	weg_w(gspca_dev, STK1135_WEG_SICTW, 0x01);
	/* wait untiw finished */
	if (stk1135_sewiaw_wait_weady(gspca_dev)) {
		pw_eww("Sensow wwite faiwed\n");
		wetuwn;
	}
}

static void sensow_wwite_16(stwuct gspca_dev *gspca_dev, u8 addw, u16 data)
{
	sensow_wwite_8(gspca_dev, addw, data >> 8);
	sensow_wwite_8(gspca_dev, 0xf1, data & 0xff);
}

static void sensow_set_page(stwuct gspca_dev *gspca_dev, u8 page)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (page != sd->sensow_page) {
		sensow_wwite_16(gspca_dev, 0xf0, page);
		sd->sensow_page = page;
	}
}

static u16 sensow_wead(stwuct gspca_dev *gspca_dev, u16 weg)
{
	sensow_set_page(gspca_dev, weg >> 8);
	wetuwn sensow_wead_16(gspca_dev, weg & 0xff);
}

static void sensow_wwite(stwuct gspca_dev *gspca_dev, u16 weg, u16 vaw)
{
	sensow_set_page(gspca_dev, weg >> 8);
	sensow_wwite_16(gspca_dev, weg & 0xff, vaw);
}

static void sensow_wwite_mask(stwuct gspca_dev *gspca_dev,
			u16 weg, u16 vaw, u16 mask)
{
	vaw = (sensow_wead(gspca_dev, weg) & ~mask) | (vaw & mask);
	sensow_wwite(gspca_dev, weg, vaw);
}

stwuct sensow_vaw {
	u16 weg;
	u16 vaw;
};

/* configuwe MT9M112 sensow */
static void stk1135_configuwe_mt9m112(stwuct gspca_dev *gspca_dev)
{
	static const stwuct sensow_vaw cfg[] = {
		/* westawt&weset, chip enabwe, wesewved */
		{ 0x00d, 0x000b }, { 0x00d, 0x0008 }, { 0x035, 0x0022 },
		/* mode ctw: AWB on, AE both, cwip apew coww, defect coww, AE */
		{ 0x106, 0x700e },

		{ 0x2dd, 0x18e0 }, /* B-W thweshowds, */

		/* AWB */
		{ 0x21f, 0x0180 }, /* Cb and Cw wimits */
		{ 0x220, 0xc814 }, { 0x221, 0x8080 }, /* wum wimits, WGB gain */
		{ 0x222, 0xa078 }, { 0x223, 0xa078 }, /* W, B wimit */
		{ 0x224, 0x5f20 }, { 0x228, 0xea02 }, /* mtx adj wim, adv ctw */
		{ 0x229, 0x867a }, /* wide gates */

		/* Cowow cowwection */
		/* imagew gains base, dewta, dewta signs */
		{ 0x25e, 0x594c }, { 0x25f, 0x4d51 }, { 0x260, 0x0002 },
		/* AWB adv ctw 2, gain offs */
		{ 0x2ef, 0x0008 }, { 0x2f2, 0x0000 },
		/* base matwix signs, scawe K1-5, K6-9 */
		{ 0x202, 0x00ee }, { 0x203, 0x3923 }, { 0x204, 0x0724 },
		/* base matwix coef */
		{ 0x209, 0x00cd }, { 0x20a, 0x0093 }, { 0x20b, 0x0004 },/*K1-3*/
		{ 0x20c, 0x005c }, { 0x20d, 0x00d9 }, { 0x20e, 0x0053 },/*K4-6*/
		{ 0x20f, 0x0008 }, { 0x210, 0x0091 }, { 0x211, 0x00cf },/*K7-9*/
		{ 0x215, 0x0000 }, /* dewta mtx signs */
		/* dewta matwix coef */
		{ 0x216, 0x0000 }, { 0x217, 0x0000 }, { 0x218, 0x0000 },/*D1-3*/
		{ 0x219, 0x0000 }, { 0x21a, 0x0000 }, { 0x21b, 0x0000 },/*D4-6*/
		{ 0x21c, 0x0000 }, { 0x21d, 0x0000 }, { 0x21e, 0x0000 },/*D7-9*/
		/* enabwe & disabwe manuaw WB to appwy cowow coww. settings */
		{ 0x106, 0xf00e }, { 0x106, 0x700e },

		/* Wens shading cowwection */
		{ 0x180, 0x0007 }, /* contwow */
		/* vewticaw knee 0, 2+1, 4+3 */
		{ 0x181, 0xde13 }, { 0x182, 0xebe2 }, { 0x183, 0x00f6 }, /* W */
		{ 0x184, 0xe114 }, { 0x185, 0xeadd }, { 0x186, 0xfdf6 }, /* G */
		{ 0x187, 0xe511 }, { 0x188, 0xede6 }, { 0x189, 0xfbf7 }, /* B */
		/* howizontaw knee 0, 2+1, 4+3, 5 */
		{ 0x18a, 0xd613 }, { 0x18b, 0xedec }, /* W .. */
		{ 0x18c, 0xf9f2 }, { 0x18d, 0x0000 }, /* .. W */
		{ 0x18e, 0xd815 }, { 0x18f, 0xe9ea }, /* G .. */
		{ 0x190, 0xf9f1 }, { 0x191, 0x0002 }, /* .. G */
		{ 0x192, 0xde10 }, { 0x193, 0xefef }, /* B .. */
		{ 0x194, 0xfbf4 }, { 0x195, 0x0002 }, /* .. B */
		/* vewticaw knee 6+5, 8+7 */
		{ 0x1b6, 0x0e06 }, { 0x1b7, 0x2713 }, /* W */
		{ 0x1b8, 0x1106 }, { 0x1b9, 0x2713 }, /* G */
		{ 0x1ba, 0x0c03 }, { 0x1bb, 0x2a0f }, /* B */
		/* howizontaw knee 7+6, 9+8, 10 */
		{ 0x1bc, 0x1208 }, { 0x1bd, 0x1a16 }, { 0x1be, 0x0022 }, /* W */
		{ 0x1bf, 0x150a }, { 0x1c0, 0x1c1a }, { 0x1c1, 0x002d }, /* G */
		{ 0x1c2, 0x1109 }, { 0x1c3, 0x1414 }, { 0x1c4, 0x002a }, /* B */
		{ 0x106, 0x740e }, /* enabwe wens shading cowwection */

		/* Gamma cowwection - context A */
		{ 0x153, 0x0b03 }, { 0x154, 0x4722 }, { 0x155, 0xac82 },
		{ 0x156, 0xdac7 }, { 0x157, 0xf5e9 }, { 0x158, 0xff00 },
		/* Gamma cowwection - context B */
		{ 0x1dc, 0x0b03 }, { 0x1dd, 0x4722 }, { 0x1de, 0xac82 },
		{ 0x1df, 0xdac7 }, { 0x1e0, 0xf5e9 }, { 0x1e1, 0xff00 },

		/* output fowmat: WGB, invewt output pixcwock, output bayew */
		{ 0x13a, 0x4300 }, { 0x19b, 0x4300 }, /* fow context A, B */
		{ 0x108, 0x0180 }, /* fowmat contwow - enabwe bayew wow fwip */

		{ 0x22f, 0xd100 }, { 0x29c, 0xd100 }, /* AE A, B */

		/* defauwt pwg conf, pwg ctw - by 0x2d2, pwg advance - PA1 */
		{ 0x2d2, 0x0000 }, { 0x2cc, 0x0004 }, { 0x2cb, 0x0001 },

		{ 0x22e, 0x0c3c }, { 0x267, 0x1010 }, /* AE tgt ctw, gain wim */

		/* PWW */
		{ 0x065, 0xa000 }, /* cwk ctw - enabwe PWW (cweaw bit 14) */
		{ 0x066, 0x2003 }, { 0x067, 0x0501 }, /* PWW M=128, N=3, P=1 */
		{ 0x065, 0x2000 }, /* disabwe PWW bypass (cweaw bit 15) */

		{ 0x005, 0x01b8 }, { 0x007, 0x00d8 }, /* howiz bwanking B, A */

		/* AE wine size, shuttew deway wimit */
		{ 0x239, 0x06c0 }, { 0x23b, 0x040e }, /* fow context A */
		{ 0x23a, 0x06c0 }, { 0x23c, 0x0564 }, /* fow context B */
		/* shuttew width basis 60Hz, 50Hz */
		{ 0x257, 0x0208 }, { 0x258, 0x0271 }, /* fow context A */
		{ 0x259, 0x0209 }, { 0x25a, 0x0271 }, /* fow context B */

		{ 0x25c, 0x120d }, { 0x25d, 0x1712 }, /* fwickew 60Hz, 50Hz */
		{ 0x264, 0x5e1c }, /* wesewved */
		/* fwickew, AE gain wimits, gain zone wimits */
		{ 0x25b, 0x0003 }, { 0x236, 0x7810 }, { 0x237, 0x8304 },

		{ 0x008, 0x0021 }, /* vewt bwanking A */
	};
	int i;
	u16 width, height;

	fow (i = 0; i < AWWAY_SIZE(cfg); i++)
		sensow_wwite(gspca_dev, cfg[i].weg, cfg[i].vaw);

	/* set output size */
	width = gspca_dev->pixfmt.width;
	height = gspca_dev->pixfmt.height;
	if (width <= 640 && height <= 512) { /* context A (hawf weadout speed)*/
		sensow_wwite(gspca_dev, 0x1a7, width);
		sensow_wwite(gspca_dev, 0x1aa, height);
		/* set wead mode context A */
		sensow_wwite(gspca_dev, 0x0c8, 0x0000);
		/* set wesize, wead mode, vbwank, hbwank context A */
		sensow_wwite(gspca_dev, 0x2c8, 0x0000);
	} ewse { /* context B (fuww weadout speed) */
		sensow_wwite(gspca_dev, 0x1a1, width);
		sensow_wwite(gspca_dev, 0x1a4, height);
		/* set wead mode context B */
		sensow_wwite(gspca_dev, 0x0c8, 0x0008);
		/* set wesize, wead mode, vbwank, hbwank context B */
		sensow_wwite(gspca_dev, 0x2c8, 0x040b);
	}
}

static void stk1135_configuwe_cwock(stwuct gspca_dev *gspca_dev)
{
	/* configuwe SCWKOUT */
	weg_w(gspca_dev, STK1135_WEG_TMGEN, 0x12);
	/* set 1 cwock pew pixew */
	/* and positive edge cwocked puwse high when pixew countew = 0 */
	weg_w(gspca_dev, STK1135_WEG_TCP1 + 0, 0x41);
	weg_w(gspca_dev, STK1135_WEG_TCP1 + 1, 0x00);
	weg_w(gspca_dev, STK1135_WEG_TCP1 + 2, 0x00);
	weg_w(gspca_dev, STK1135_WEG_TCP1 + 3, 0x00);

	/* enabwe CWKOUT fow sensow */
	weg_w(gspca_dev, STK1135_WEG_SENSO + 0, 0x10);
	/* disabwe STOP cwock */
	weg_w(gspca_dev, STK1135_WEG_SENSO + 1, 0x00);
	/* set wowew 8 bits of PWW feedback dividew */
	weg_w(gspca_dev, STK1135_WEG_SENSO + 3, 0x07);
	/* set othew PWW pawametews */
	weg_w(gspca_dev, STK1135_WEG_PWWFD, 0x06);
	/* enabwe timing genewatow */
	weg_w(gspca_dev, STK1135_WEG_TMGEN, 0x80);
	/* enabwe PWW */
	weg_w(gspca_dev, STK1135_WEG_SENSO + 2, 0x04);

	/* set sewiaw intewface cwock dividew (30MHz/0x1f*16+2) = 60240 kHz) */
	weg_w(gspca_dev, STK1135_WEG_SICTW + 2, 0x1f);

	/* wait a whiwe fow sensow to catch up */
	udeway(1000);
}

static void stk1135_camewa_disabwe(stwuct gspca_dev *gspca_dev)
{
	/* set captuwe end Y position to 0 */
	weg_w(gspca_dev, STK1135_WEG_CIEPO + 2, 0x00);
	weg_w(gspca_dev, STK1135_WEG_CIEPO + 3, 0x00);
	/* disabwe captuwe */
	weg_w_mask(gspca_dev, STK1135_WEG_SCTWW, 0x00, 0x80);

	/* enabwe sensow standby and diasbwe chip enabwe */
	sensow_wwite_mask(gspca_dev, 0x00d, 0x0004, 0x000c);

	/* disabwe PWW */
	weg_w_mask(gspca_dev, STK1135_WEG_SENSO + 2, 0x00, 0x01);
	/* disabwe timing genewatow */
	weg_w(gspca_dev, STK1135_WEG_TMGEN, 0x00);
	/* enabwe STOP cwock */
	weg_w(gspca_dev, STK1135_WEG_SENSO + 1, 0x20);
	/* disabwe CWKOUT fow sensow */
	weg_w(gspca_dev, STK1135_WEG_SENSO, 0x00);

	/* disabwe sensow (GPIO5) and enabwe GPIO0,3,6 (?) - sensow standby? */
	weg_w(gspca_dev, STK1135_WEG_GCTWW, 0x49);
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	u16 sensow_id;
	chaw *sensow_name;
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	/* set GPIO3,4,5,6 diwection to output */
	weg_w(gspca_dev, STK1135_WEG_GCTWW + 2, 0x78);
	/* enabwe sensow (GPIO5) */
	weg_w(gspca_dev, STK1135_WEG_GCTWW, (1 << 5));
	/* disabwe WOM intewface */
	weg_w(gspca_dev, STK1135_WEG_GCTWW + 3, 0x80);
	/* enabwe intewwupts fwom GPIO8 (fwip sensow) and GPIO9 (???) */
	weg_w(gspca_dev, STK1135_WEG_ICTWW + 1, 0x00);
	weg_w(gspca_dev, STK1135_WEG_ICTWW + 3, 0x03);
	/* enabwe wemote wakeup fwom GPIO9 (???) */
	weg_w(gspca_dev, STK1135_WEG_WMCTW + 1, 0x00);
	weg_w(gspca_dev, STK1135_WEG_WMCTW + 3, 0x02);

	/* weset sewiaw intewface */
	weg_w(gspca_dev, STK1135_WEG_SICTW, 0x80);
	weg_w(gspca_dev, STK1135_WEG_SICTW, 0x00);
	/* set sensow addwess */
	weg_w(gspca_dev, STK1135_WEG_SICTW + 3, 0xba);
	/* disabwe awt 2-wiwe sewiaw intewface */
	weg_w(gspca_dev, STK1135_WEG_ASIC + 3, 0x00);

	stk1135_configuwe_cwock(gspca_dev);

	/* wead sensow ID */
	sd->sensow_page = 0xff;
	sensow_id = sensow_wead(gspca_dev, 0x000);

	switch (sensow_id) {
	case 0x148c:
		sensow_name = "MT9M112";
		bweak;
	defauwt:
		sensow_name = "unknown";
	}
	pw_info("Detected sensow type %s (0x%x)\n", sensow_name, sensow_id);

	stk1135_camewa_disabwe(gspca_dev);

	wetuwn gspca_dev->usb_eww;
}

/* -- stawt the camewa -- */
static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u16 width, height;

	/* enabwe sensow (GPIO5) */
	weg_w(gspca_dev, STK1135_WEG_GCTWW, (1 << 5));

	stk1135_configuwe_cwock(gspca_dev);

	/* set captuwe stawt position X = 0, Y = 0 */
	weg_w(gspca_dev, STK1135_WEG_CISPO + 0, 0x00);
	weg_w(gspca_dev, STK1135_WEG_CISPO + 1, 0x00);
	weg_w(gspca_dev, STK1135_WEG_CISPO + 2, 0x00);
	weg_w(gspca_dev, STK1135_WEG_CISPO + 3, 0x00);

	/* set captuwe end position */
	width = gspca_dev->pixfmt.width;
	height = gspca_dev->pixfmt.height;
	weg_w(gspca_dev, STK1135_WEG_CIEPO + 0, width & 0xff);
	weg_w(gspca_dev, STK1135_WEG_CIEPO + 1, width >> 8);
	weg_w(gspca_dev, STK1135_WEG_CIEPO + 2, height & 0xff);
	weg_w(gspca_dev, STK1135_WEG_CIEPO + 3, height >> 8);

	/* set 8-bit mode */
	weg_w(gspca_dev, STK1135_WEG_SCTWW, 0x20);

	stk1135_configuwe_mt9m112(gspca_dev);

	/* enabwe captuwe */
	weg_w_mask(gspca_dev, STK1135_WEG_SCTWW, 0x80, 0x80);

	if (gspca_dev->usb_eww >= 0)
		gspca_dbg(gspca_dev, D_STWEAM, "camewa stawted awt: 0x%02x\n",
			  gspca_dev->awt);

	sd->pkt_seq = 0;

	wetuwn gspca_dev->usb_eww;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	stwuct usb_device *dev = gspca_dev->dev;

	usb_set_intewface(dev, gspca_dev->iface, 0);

	stk1135_camewa_disabwe(gspca_dev);

	gspca_dbg(gspca_dev, D_STWEAM, "camewa stopped\n");
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int wen)			/* iso packet wength */
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int skip = sizeof(stwuct stk1135_pkt_headew);
	boow fwip;
	enum gspca_packet_type pkt_type = INTEW_PACKET;
	stwuct stk1135_pkt_headew *hdw = (void *)data;
	u8 seq;

	if (wen < 4) {
		gspca_dbg(gspca_dev, D_PACK, "weceived showt packet (wess than 4 bytes)\n");
		wetuwn;
	}

	/* GPIO 8 is fwip sensow (1 = nowmaw position, 0 = fwipped to back) */
	fwip = !(we16_to_cpu(hdw->gpio) & (1 << 8));
	/* it's a switch, needs softwawe debounce */
	if (sd->fwip_status != fwip)
		sd->fwip_debounce++;
	ewse
		sd->fwip_debounce = 0;

	/* check sequence numbew (not pwesent in new fwame packets) */
	if (!(hdw->fwags & STK1135_HDW_FWAME_STAWT)) {
		seq = hdw->seq & STK1135_HDW_SEQ_MASK;
		if (seq != sd->pkt_seq) {
			gspca_dbg(gspca_dev, D_PACK, "weceived out-of-sequence packet\n");
			/* wesync sequence and discawd packet */
			sd->pkt_seq = seq;
			gspca_dev->wast_packet_type = DISCAWD_PACKET;
			wetuwn;
		}
	}
	sd->pkt_seq++;
	if (sd->pkt_seq > STK1135_HDW_SEQ_MASK)
		sd->pkt_seq = 0;

	if (wen == sizeof(stwuct stk1135_pkt_headew))
		wetuwn;

	if (hdw->fwags & STK1135_HDW_FWAME_STAWT) { /* new fwame */
		skip = 8;	/* the headew is wongew */
		gspca_fwame_add(gspca_dev, WAST_PACKET, data, 0);
		pkt_type = FIWST_PACKET;
	}
	gspca_fwame_add(gspca_dev, pkt_type, data + skip, wen - skip);
}

static void sethfwip(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (sd->fwip_status)
		vaw = !vaw;
	sensow_wwite_mask(gspca_dev, 0x020, vaw ? 0x0002 : 0x0000 , 0x0002);
}

static void setvfwip(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (sd->fwip_status)
		vaw = !vaw;
	sensow_wwite_mask(gspca_dev, 0x020, vaw ? 0x0001 : 0x0000 , 0x0001);
}

static void stk1135_dq_cawwback(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (sd->fwip_debounce > 100) {
		sd->fwip_status = !sd->fwip_status;
		sethfwip(gspca_dev, v4w2_ctww_g_ctww(sd->hfwip));
		setvfwip(gspca_dev, v4w2_ctww_g_ctww(sd->vfwip));
	}
}

static int sd_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);

	gspca_dev->usb_eww = 0;

	if (!gspca_dev->stweaming)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_HFWIP:
		sethfwip(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_VFWIP:
		setvfwip(gspca_dev, ctww->vaw);
		bweak;
	}

	wetuwn gspca_dev->usb_eww;
}

static const stwuct v4w2_ctww_ops sd_ctww_ops = {
	.s_ctww = sd_s_ctww,
};

static int sd_init_contwows(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct v4w2_ctww_handwew *hdw = &gspca_dev->ctww_handwew;

	gspca_dev->vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 2);
	sd->hfwip = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_HFWIP, 0, 1, 1, 0);
	sd->vfwip = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_VFWIP, 0, 1, 1, 0);

	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}
	wetuwn 0;
}

static void stk1135_twy_fmt(stwuct gspca_dev *gspca_dev, stwuct v4w2_fowmat *fmt)
{
	fmt->fmt.pix.width = cwamp(fmt->fmt.pix.width, 32U, 1280U);
	fmt->fmt.pix.height = cwamp(fmt->fmt.pix.height, 32U, 1024U);
	/* wound up to even numbews */
	fmt->fmt.pix.width += (fmt->fmt.pix.width & 1);
	fmt->fmt.pix.height += (fmt->fmt.pix.height & 1);

	fmt->fmt.pix.bytespewwine = fmt->fmt.pix.width;
	fmt->fmt.pix.sizeimage = fmt->fmt.pix.width * fmt->fmt.pix.height;
}

static int stk1135_enum_fwamesizes(stwuct gspca_dev *gspca_dev,
			stwuct v4w2_fwmsizeenum *fsize)
{
	if (fsize->index != 0 || fsize->pixew_fowmat != V4W2_PIX_FMT_SBGGW8)
		wetuwn -EINVAW;

	fsize->type = V4W2_FWMSIZE_TYPE_STEPWISE;
	fsize->stepwise.min_width = 32;
	fsize->stepwise.min_height = 32;
	fsize->stepwise.max_width = 1280;
	fsize->stepwise.max_height = 1024;
	fsize->stepwise.step_width = 2;
	fsize->stepwise.step_height = 2;

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
	.dq_cawwback = stk1135_dq_cawwback,
	.twy_fmt = stk1135_twy_fmt,
	.enum_fwamesizes = stk1135_enum_fwamesizes,
};

/* -- moduwe initiawisation -- */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x174f, 0x6a31)},	/* ASUS waptop, MT9M112 sensow */
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
