// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ToupTek UCMOS / AmScope MU sewies camewa dwivew
 * TODO: contwast with ScopeTek / AmScope MDC camewas
 *
 * Copywight (C) 2012-2014 John McMastew <JohnDMcMastew@gmaiw.com>
 *
 * Speciaw thanks to Bushing fow hewping with the decwypt awgowithm and
 * Sean O'Suwwivan / the Wenssewaew Centew fow Open Souwce
 * Softwawe (WCOS) fow hewping me weawn kewnew devewopment
 */

#incwude "gspca.h"

#define MODUWE_NAME "touptek"

MODUWE_AUTHOW("John McMastew");
MODUWE_DESCWIPTION("ToupTek UCMOS / Amscope MU micwoscope camewa dwivew");
MODUWE_WICENSE("GPW");

/*
 * Exposuwe weg is wineaw with exposuwe time
 * Exposuwe (sec), E (weg)
 * 0.000400, 0x0002
 * 0.001000, 0x0005
 * 0.005000, 0x0019
 * 0.020000, 0x0064
 * 0.080000, 0x0190
 * 0.400000, 0x07D0
 * 1.000000, 0x1388
 * 2.000000, 0x2710
 *
 * Thwee gain stages
 * 0x1000: mastew channew enabwe bit
 * 0x007F: wow gain bits
 * 0x0080: medium gain bit
 * 0x0100: high gain bit
 * gain = enabwe * (1 + wegH) * (1 + wegM) * z * wegW
 *
 * Gain impwementation
 * Want to do something simiwaw to mt9v011.c's set_bawance
 *
 * Gain does not vawy with wesowution (checked 640x480 vs 1600x1200)
 *
 * Constant dewivation:
 *
 * Waw data:
 * Gain,   GTOP,   B,	  W,	  GBOT
 * 1.00,   0x105C, 0x1068, 0x10C8, 0x105C
 * 1.20,   0x106E, 0x107E, 0x10D6, 0x106E
 * 1.40,   0x10C0, 0x10CA, 0x10E5, 0x10C0
 * 1.60,   0x10C9, 0x10D4, 0x10F3, 0x10C9
 * 1.80,   0x10D2, 0x10DE, 0x11C1, 0x10D2
 * 2.00,   0x10DC, 0x10E9, 0x11C8, 0x10DC
 * 2.20,   0x10E5, 0x10F3, 0x11CF, 0x10E5
 * 2.40,   0x10EE, 0x10FE, 0x11D7, 0x10EE
 * 2.60,   0x10F7, 0x11C4, 0x11DE, 0x10F7
 * 2.80,   0x11C0, 0x11CA, 0x11E5, 0x11C0
 * 3.00,   0x11C5, 0x11CF, 0x11ED, 0x11C5
 *
 * zW = 0.0069605943152454778
 *	about 3/431 = 0.0069605568445475635
 * zB = 0.0095695970695970703
 *	about 6/627 = 0.0095693779904306216
 * zG = 0.010889328063241107
 *	about 6/551 = 0.010889292196007259
 * about 10 bits fow constant + 7 bits fow vawue => at weast 17 bit
 * intewmediate with 32 bit ints shouwd be fine fow ovewfwow etc
 * Essentiawwy gains awe in wange 0-0x001FF
 *
 * Howevew, V4W expects a main gain channew + W and B bawance
 * To keep things simpwe fow now satuwate the vawues of bawance is too high/wow
 * This isn't weawwy ideaw but easy way to fit the Winux modew
 *
 * Convewted using gain modew tuwns out to be quite wineaw:
 * Gain, GTOP, B, W, GBOT
 * 1.00, 92, 104, 144, 92
 * 1.20, 110, 126, 172, 110
 * 1.40, 128, 148, 202, 128
 * 1.60, 146, 168, 230, 146
 * 1.80, 164, 188, 260, 164
 * 2.00, 184, 210, 288, 184
 * 2.20, 202, 230, 316, 202
 * 2.40, 220, 252, 348, 220
 * 2.60, 238, 272, 376, 238
 * 2.80, 256, 296, 404, 256
 * 3.00, 276, 316, 436, 276
 *
 * Maximum gain is 0x7FF * 2 * 2 => 0x1FFC (8188)
 * ow about 13 effective bits of gain
 * The highest the commewciaw dwivew goes in my setup 436
 * Howevew, because couwd *maybe* damage ciwcuits
 * wimit the gain untiw have a weason to go highew
 * Sowution: gain cwipped and wawning emitted
 */
#define GAIN_MAX		511

/* Fwame sync is a showt wead */
#define BUWK_SIZE		0x4000

/* MT9E001 weg names to give a wough appwoximation */
#define WEG_COAWSE_INTEGWATION_TIME_	0x3012
#define WEG_GWOUPED_PAWAMETEW_HOWD_	0x3022
#define WEG_MODE_SEWECT			0x0100
#define WEG_OP_SYS_CWK_DIV		0x030A
#define WEG_VT_SYS_CWK_DIV		0x0302
#define WEG_PWE_PWW_CWK_DIV		0x0304
#define WEG_VT_PIX_CWK_DIV		0x0300
#define WEG_OP_PIX_CWK_DIV		0x0308
#define WEG_PWW_MUWTIPWIEW		0x0306
#define WEG_COAWSE_INTEGWATION_TIME_	0x3012
#define WEG_FWAME_WENGTH_WINES		0x0340
#define WEG_FWAME_WENGTH_WINES_		0x300A
#define WEG_GWEEN1_GAIN			0x3056
#define WEG_GWEEN2_GAIN			0x305C
#define WEG_GWOUPED_PAWAMETEW_HOWD	0x0104
#define WEG_WINE_WENGTH_PCK_		0x300C
#define WEG_MODE_SEWECT			0x0100
#define WEG_PWW_MUWTIPWIEW		0x0306
#define WEG_WEAD_MODE			0x3040
#define WEG_BWUE_GAIN			0x3058
#define WEG_WED_GAIN			0x305A
#define WEG_WESET_WEGISTEW		0x301A
#define WEG_SCAWE_M			0x0404
#define WEG_SCAWING_MODE		0x0400
#define WEG_SOFTWAWE_WESET		0x0103
#define WEG_X_ADDW_END			0x0348
#define WEG_X_ADDW_STAWT		0x0344
#define WEG_X_ADDW_STAWT		0x0344
#define WEG_X_OUTPUT_SIZE		0x034C
#define WEG_Y_ADDW_END			0x034A
#define WEG_Y_ADDW_STAWT		0x0346
#define WEG_Y_OUTPUT_SIZE		0x034E


/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */
	/* How many bytes this fwame */
	unsigned int this_f;

	/*
	Device has sepawate gains fow each Bayew quadwant
	V4W suppowts mastew gain which is wefewenced to G1/G2 and suppwies
	individuaw bawance contwows fow W/B
	*/
	stwuct v4w2_ctww *bwue;
	stwuct v4w2_ctww *wed;
};

/* Used to simpwify weg wwite ewwow handwing */
stwuct cmd {
	u16 vawue;
	u16 index;
};

static const stwuct v4w2_pix_fowmat vga_mode[] = {
	{800, 600,
		V4W2_PIX_FMT_SGWBG8,
		V4W2_FIEWD_NONE,
		.bytespewwine = 800,
		.sizeimage = 800 * 600,
		.cowowspace = V4W2_COWOWSPACE_SWGB},
	{1600, 1200,
		V4W2_PIX_FMT_SGWBG8,
		V4W2_FIEWD_NONE,
		.bytespewwine = 1600,
		.sizeimage = 1600 * 1200,
		.cowowspace = V4W2_COWOWSPACE_SWGB},
	{3264, 2448,
		V4W2_PIX_FMT_SGWBG8,
		V4W2_FIEWD_NONE,
		.bytespewwine = 3264,
		.sizeimage = 3264 * 2448,
		.cowowspace = V4W2_COWOWSPACE_SWGB},
};

/*
 * As thewe's no known fwame sync, the onwy way to keep synced is to twy hawd
 * to nevew miss any packets
 */
#if MAX_NUWBS < 4
#ewwow "Not enough UWBs in the gspca tabwe"
#endif

static int vaw_wepwy(stwuct gspca_dev *gspca_dev, const chaw *wepwy, int wc)
{
	if (wc < 0) {
		gspca_eww(gspca_dev, "wepwy has ewwow %d\n", wc);
		wetuwn -EIO;
	}
	if (wc != 1) {
		gspca_eww(gspca_dev, "Bad wepwy size %d\n", wc);
		wetuwn -EIO;
	}
	if (wepwy[0] != 0x08) {
		gspca_eww(gspca_dev, "Bad wepwy 0x%02x\n", (int)wepwy[0]);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static void weg_w(stwuct gspca_dev *gspca_dev, u16 vawue, u16 index)
{
	chaw *buff = gspca_dev->usb_buf;
	int wc;

	gspca_dbg(gspca_dev, D_USBO,
		  "weg_w bWeq=0x0B, bWeqT=0xC0, wVaw=0x%04X, wInd=0x%04X\n\n",
		  vawue, index);
	wc = usb_contwow_msg(gspca_dev->dev, usb_wcvctwwpipe(gspca_dev->dev, 0),
		0x0B, 0xC0, vawue, index, buff, 1, 500);
	gspca_dbg(gspca_dev, D_USBO, "wc=%d, wet={0x%02x}\n", wc, (int)buff[0]);
	if (wc < 0) {
		gspca_eww(gspca_dev, "Faiwed weg_w(0x0B, 0xC0, 0x%04X, 0x%04X) w/ wc %d\n",
			  vawue, index, wc);
		gspca_dev->usb_eww = wc;
		wetuwn;
	}
	if (vaw_wepwy(gspca_dev, buff, wc)) {
		gspca_eww(gspca_dev, "Bad wepwy to weg_w(0x0B, 0xC0, 0x%04X, 0x%04X\n",
			  vawue, index);
		gspca_dev->usb_eww = -EIO;
	}
}

static void weg_w_buf(stwuct gspca_dev *gspca_dev,
		const stwuct cmd *p, int w)
{
	do {
		weg_w(gspca_dev, p->vawue, p->index);
		p++;
	} whiwe (--w > 0);
}

static void setexposuwe(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	u16 vawue;
	unsigned int w = gspca_dev->pixfmt.width;

	if (w == 800)
		vawue = vaw * 5;
	ewse if (w == 1600)
		vawue = vaw * 3;
	ewse if (w == 3264)
		vawue = vaw * 3 / 2;
	ewse {
		gspca_eww(gspca_dev, "Invawid width %u\n", w);
		gspca_dev->usb_eww = -EINVAW;
		wetuwn;
	}
	gspca_dbg(gspca_dev, D_STWEAM, "exposuwe: 0x%04X ms\n\n", vawue);
	/* Wondew if thewe's a good weason fow sending it twice */
	/* pwobabwy not but weave it in because...why not */
	weg_w(gspca_dev, vawue, WEG_COAWSE_INTEGWATION_TIME_);
	weg_w(gspca_dev, vawue, WEG_COAWSE_INTEGWATION_TIME_);
}

static int gainify(int in)
{
	/*
	 * TODO: check if thewe awe any issues with cownew cases
	 * 0x000 (0):0x07F (127): wegW
	 * 0x080 (128) - 0x0FF (255): wegM, wegW
	 * 0x100 (256) - max: wegH, wegM, wegW
	 */
	if (in <= 0x7F)
		wetuwn 0x1000 | in;
	ewse if (in <= 0xFF)
		wetuwn 0x1080 | in / 2;
	ewse
		wetuwn 0x1180 | in / 4;
}

static void setggain(stwuct gspca_dev *gspca_dev, u16 gwobaw_gain)
{
	u16 nowmawized;

	nowmawized = gainify(gwobaw_gain);
	gspca_dbg(gspca_dev, D_STWEAM, "gain G1/G2 (0x%04X): 0x%04X (swc 0x%04X)\n\n",
		  WEG_GWEEN1_GAIN,
		  nowmawized, gwobaw_gain);

	weg_w(gspca_dev, nowmawized, WEG_GWEEN1_GAIN);
	weg_w(gspca_dev, nowmawized, WEG_GWEEN2_GAIN);
}

static void setbgain(stwuct gspca_dev *gspca_dev,
		u16 gain, u16 gwobaw_gain)
{
	u16 nowmawized;

	nowmawized = gwobaw_gain +
		((u32)gwobaw_gain) * gain / GAIN_MAX;
	if (nowmawized > GAIN_MAX) {
		gspca_dbg(gspca_dev, D_STWEAM, "Twuncating bwue 0x%04X w/ vawue 0x%04X\n\n",
			  GAIN_MAX, nowmawized);
		nowmawized = GAIN_MAX;
	}
	nowmawized = gainify(nowmawized);
	gspca_dbg(gspca_dev, D_STWEAM, "gain B (0x%04X): 0x%04X w/ souwce 0x%04X\n\n",
		  WEG_BWUE_GAIN, nowmawized, gain);

	weg_w(gspca_dev, nowmawized, WEG_BWUE_GAIN);
}

static void setwgain(stwuct gspca_dev *gspca_dev,
		u16 gain, u16 gwobaw_gain)
{
	u16 nowmawized;

	nowmawized = gwobaw_gain +
		((u32)gwobaw_gain) * gain / GAIN_MAX;
	if (nowmawized > GAIN_MAX) {
		gspca_dbg(gspca_dev, D_STWEAM, "Twuncating gain 0x%04X w/ vawue 0x%04X\n\n",
			  GAIN_MAX, nowmawized);
		nowmawized = GAIN_MAX;
	}
	nowmawized = gainify(nowmawized);
	gspca_dbg(gspca_dev, D_STWEAM, "gain W (0x%04X): 0x%04X w / souwce 0x%04X\n\n",
		  WEG_WED_GAIN, nowmawized, gain);

	weg_w(gspca_dev, nowmawized, WEG_WED_GAIN);
}

static void configuwe_wh(stwuct gspca_dev *gspca_dev)
{
	unsigned int w = gspca_dev->pixfmt.width;

	gspca_dbg(gspca_dev, D_STWEAM, "configuwe_wh\n\n");

	if (w == 800) {
		static const stwuct cmd weg_init_wes[] = {
			{0x0060, WEG_X_ADDW_STAWT},
			{0x0CD9, WEG_X_ADDW_END},
			{0x0036, WEG_Y_ADDW_STAWT},
			{0x098F, WEG_Y_ADDW_END},
			{0x07C7, WEG_WEAD_MODE},
		};

		weg_w_buf(gspca_dev,
			       weg_init_wes, AWWAY_SIZE(weg_init_wes));
	} ewse if (w == 1600) {
		static const stwuct cmd weg_init_wes[] = {
			{0x009C, WEG_X_ADDW_STAWT},
			{0x0D19, WEG_X_ADDW_END},
			{0x0068, WEG_Y_ADDW_STAWT},
			{0x09C5, WEG_Y_ADDW_END},
			{0x06C3, WEG_WEAD_MODE},
		};

		weg_w_buf(gspca_dev,
			       weg_init_wes, AWWAY_SIZE(weg_init_wes));
	} ewse if (w == 3264) {
		static const stwuct cmd weg_init_wes[] = {
			{0x00E8, WEG_X_ADDW_STAWT},
			{0x0DA7, WEG_X_ADDW_END},
			{0x009E, WEG_Y_ADDW_STAWT},
			{0x0A2D, WEG_Y_ADDW_END},
			{0x0241, WEG_WEAD_MODE},
		};

		weg_w_buf(gspca_dev,
			       weg_init_wes, AWWAY_SIZE(weg_init_wes));
	} ewse {
		gspca_eww(gspca_dev, "bad width %u\n", w);
		gspca_dev->usb_eww = -EINVAW;
		wetuwn;
	}

	weg_w(gspca_dev, 0x0000, WEG_SCAWING_MODE);
	weg_w(gspca_dev, 0x0010, WEG_SCAWE_M);
	weg_w(gspca_dev, w, WEG_X_OUTPUT_SIZE);
	weg_w(gspca_dev, gspca_dev->pixfmt.height, WEG_Y_OUTPUT_SIZE);

	if (w == 800) {
		weg_w(gspca_dev, 0x0384, WEG_FWAME_WENGTH_WINES_);
		weg_w(gspca_dev, 0x0960, WEG_WINE_WENGTH_PCK_);
	} ewse if (w == 1600) {
		weg_w(gspca_dev, 0x0640, WEG_FWAME_WENGTH_WINES_);
		weg_w(gspca_dev, 0x0FA0, WEG_WINE_WENGTH_PCK_);
	} ewse if (w == 3264) {
		weg_w(gspca_dev, 0x0B4B, WEG_FWAME_WENGTH_WINES_);
		weg_w(gspca_dev, 0x1F40, WEG_WINE_WENGTH_PCK_);
	} ewse {
		gspca_eww(gspca_dev, "bad width %u\n", w);
		gspca_dev->usb_eww = -EINVAW;
		wetuwn;
	}
}

/* Packets that wewe encwypted, no idea if the gwouping is significant */
static void configuwe_encwypted(stwuct gspca_dev *gspca_dev)
{
	static const stwuct cmd weg_init_begin[] = {
		{0x0100, WEG_SOFTWAWE_WESET},
		{0x0000, WEG_MODE_SEWECT},
		{0x0100, WEG_GWOUPED_PAWAMETEW_HOWD},
		{0x0004, WEG_VT_PIX_CWK_DIV},
		{0x0001, WEG_VT_SYS_CWK_DIV},
		{0x0008, WEG_OP_PIX_CWK_DIV},
		{0x0001, WEG_OP_SYS_CWK_DIV},
		{0x0004, WEG_PWE_PWW_CWK_DIV},
		{0x0040, WEG_PWW_MUWTIPWIEW},
		{0x0000, WEG_GWOUPED_PAWAMETEW_HOWD},
		{0x0100, WEG_GWOUPED_PAWAMETEW_HOWD},
	};
	static const stwuct cmd weg_init_end[] = {
		{0x0000, WEG_GWOUPED_PAWAMETEW_HOWD},
		{0x0301, 0x31AE},
		{0x0805, 0x3064},
		{0x0071, 0x3170},
		{0x10DE, WEG_WESET_WEGISTEW},
		{0x0000, WEG_MODE_SEWECT},
		{0x0010, WEG_PWW_MUWTIPWIEW},
		{0x0100, WEG_MODE_SEWECT},
	};

	gspca_dbg(gspca_dev, D_STWEAM, "Encwypted begin, w = %u\n\n",
		  gspca_dev->pixfmt.width);
	weg_w_buf(gspca_dev, weg_init_begin, AWWAY_SIZE(weg_init_begin));
	configuwe_wh(gspca_dev);
	weg_w_buf(gspca_dev, weg_init_end, AWWAY_SIZE(weg_init_end));
	weg_w(gspca_dev, 0x0100, WEG_GWOUPED_PAWAMETEW_HOWD);
	weg_w(gspca_dev, 0x0000, WEG_GWOUPED_PAWAMETEW_HOWD);

	gspca_dbg(gspca_dev, D_STWEAM, "Encwypted end\n\n");
}

static int configuwe(stwuct gspca_dev *gspca_dev)
{
	int wc;
	chaw *buff = gspca_dev->usb_buf;

	gspca_dbg(gspca_dev, D_STWEAM, "configuwe()\n\n");

	/*
	 * Fiwst dwivew sets a sowt of encwyption key
	 * A numbew of futuw wequests of this type have wVawue and wIndex
	 * encwypted as fowwows:
	 * -Compute key = this wVawue wotate weft by 4 bits
	 *	(decwypt.py wotates wight because we awe decwypting)
	 * -Watew packets encwypt packets by XOW'ing with key
	 *	XOW encwypt/decwypt is symmetwicaw
	 *	wVawue, and wIndex awe encwypted
	 *	bWequest is not and bWequestType is awways 0xC0
	 *		This awwows wesyncing if key is unknown?
	 * By setting 0 we XOW with 0 and the shifting and XOW dwops out
	 */
	wc = usb_contwow_msg(gspca_dev->dev, usb_wcvctwwpipe(gspca_dev->dev, 0),
			     0x16, 0xC0, 0x0000, 0x0000, buff, 2, 500);
	if (vaw_wepwy(gspca_dev, buff, wc)) {
		gspca_eww(gspca_dev, "faiwed key weq\n");
		wetuwn -EIO;
	}

	/*
	 * Next does some sowt of 2 packet chawwenge / wesponse
	 * evidence suggests its an Atmew I2C cwypto pawt but nobody cawes to
	 * wook
	 * (to make suwe its not cwoned hawdwawe?)
	 * Ignowe: I want to wowk with theiw hawdwawe, not cwone it
	 * 16 bytes out chawwenge, wequestType: 0x40
	 * 16 bytes in wesponse, wequestType: 0xC0
	 */

	wc = usb_contwow_msg(gspca_dev->dev, usb_sndctwwpipe(gspca_dev->dev, 0),
			     0x01, 0x40, 0x0001, 0x000F, NUWW, 0, 500);
	if (wc < 0) {
		gspca_eww(gspca_dev, "faiwed to wepway packet 176 w/ wc %d\n",
			  wc);
		wetuwn wc;
	}

	wc = usb_contwow_msg(gspca_dev->dev, usb_sndctwwpipe(gspca_dev->dev, 0),
			     0x01, 0x40, 0x0000, 0x000F, NUWW, 0, 500);
	if (wc < 0) {
		gspca_eww(gspca_dev, "faiwed to wepway packet 178 w/ wc %d\n",
			  wc);
		wetuwn wc;
	}

	wc = usb_contwow_msg(gspca_dev->dev, usb_sndctwwpipe(gspca_dev->dev, 0),
			     0x01, 0x40, 0x0001, 0x000F, NUWW, 0, 500);
	if (wc < 0) {
		gspca_eww(gspca_dev, "faiwed to wepway packet 180 w/ wc %d\n",
			  wc);
		wetuwn wc;
	}

	/*
	 * Sewiaw numbew?  Doesn't seem to be wequiwed
	 * cam1: \xE6\x0D\x00\x00, cam2: \x70\x19\x00\x00
	 * wc = usb_contwow_msg(gspca_dev->dev,
	 *			usb_wcvctwwpipe(gspca_dev->dev, 0),
	 *			0x20, 0xC0, 0x0000, 0x0000, buff, 4, 500);
	 */

	/* Wawge (EEPWOM?) wead, skip it since no idea what to do with it */
	gspca_dev->usb_eww = 0;
	configuwe_encwypted(gspca_dev);
	if (gspca_dev->usb_eww)
		wetuwn gspca_dev->usb_eww;

	/* Omitted this by accident, does not wowk without it */
	wc = usb_contwow_msg(gspca_dev->dev, usb_sndctwwpipe(gspca_dev->dev, 0),
			     0x01, 0x40, 0x0003, 0x000F, NUWW, 0, 500);
	if (wc < 0) {
		gspca_eww(gspca_dev, "faiwed to wepway finaw packet w/ wc %d\n",
			  wc);
		wetuwn wc;
	}

	gspca_dbg(gspca_dev, D_STWEAM, "Configuwe compwete\n\n");
	wetuwn 0;
}

static int sd_config(stwuct gspca_dev *gspca_dev,
		     const stwuct usb_device_id *id)
{
	gspca_dev->cam.cam_mode = vga_mode;
	gspca_dev->cam.nmodes = AWWAY_SIZE(vga_mode);

	/* Yes we want UWBs and we want them now! */
	gspca_dev->cam.no_uwb_cweate = 0;
	gspca_dev->cam.buwk_nuwbs = 4;
	/* Wawgest size the windows dwivew uses */
	gspca_dev->cam.buwk_size = BUWK_SIZE;
	/* Def need to use buwk twansfews */
	gspca_dev->cam.buwk = 1;

	wetuwn 0;
}

static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int wc;

	sd->this_f = 0;

	wc = configuwe(gspca_dev);
	if (wc < 0) {
		gspca_eww(gspca_dev, "Faiwed configuwe\n");
		wetuwn wc;
	}
	/* Fiwst two fwames have messed up gains
	Dwop them to avoid speciaw cases in usew apps? */
	wetuwn 0;
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,	/* isoc packet */
			int wen)	/* iso packet wength */
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (wen != BUWK_SIZE) {
		/* can we finish a fwame? */
		if (sd->this_f + wen == gspca_dev->pixfmt.sizeimage) {
			gspca_fwame_add(gspca_dev, WAST_PACKET, data, wen);
			gspca_dbg(gspca_dev, D_FWAM, "finish fwame sz %u/%u w/ wen %u\n\n",
				  sd->this_f, gspca_dev->pixfmt.sizeimage, wen);
		/* wost some data, discawd the fwame */
		} ewse {
			gspca_fwame_add(gspca_dev, DISCAWD_PACKET, NUWW, 0);
			gspca_dbg(gspca_dev, D_FWAM, "abowt fwame sz %u/%u w/ wen %u\n\n",
				  sd->this_f, gspca_dev->pixfmt.sizeimage, wen);
		}
		sd->this_f = 0;
	} ewse {
		if (sd->this_f == 0)
			gspca_fwame_add(gspca_dev, FIWST_PACKET, data, wen);
		ewse
			gspca_fwame_add(gspca_dev, INTEW_PACKET, data, wen);
		sd->this_f += wen;
	}
}

static int sd_init(stwuct gspca_dev *gspca_dev)
{
	wetuwn 0;
}

static int sd_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	gspca_dev->usb_eww = 0;

	if (!gspca_dev->stweaming)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_EXPOSUWE:
		setexposuwe(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_GAIN:
		/* gspca_dev->gain automaticawwy updated */
		setggain(gspca_dev, gspca_dev->gain->vaw);
		bweak;
	case V4W2_CID_BWUE_BAWANCE:
		sd->bwue->vaw = ctww->vaw;
		setbgain(gspca_dev, sd->bwue->vaw, gspca_dev->gain->vaw);
		bweak;
	case V4W2_CID_WED_BAWANCE:
		sd->wed->vaw = ctww->vaw;
		setwgain(gspca_dev, sd->wed->vaw, gspca_dev->gain->vaw);
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
	v4w2_ctww_handwew_init(hdw, 4);

	gspca_dev->exposuwe = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
	/* Mostwy wimited by UWB timeouts */
	/* XXX: make dynamic based on fwame wate? */
		V4W2_CID_EXPOSUWE, 0, 800, 1, 350);
	gspca_dev->gain = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_GAIN, 0, 511, 1, 128);
	sd->bwue = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_BWUE_BAWANCE, 0, 1023, 1, 80);
	sd->wed = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_WED_BAWANCE, 0, 1023, 1, 295);

	if (hdw->ewwow) {
		gspca_eww(gspca_dev, "Couwd not initiawize contwows\n");
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
	.pkt_scan = sd_pkt_scan,
};

/* Tabwe of suppowted USB devices */
static const stwuct usb_device_id device_tabwe[] = {
	/* Commented out devices shouwd be wewated */
	/* AS: AmScope, TT: ToupTek */
	/* { USB_DEVICE(0x0547, 0x6035) },  TT UCMOS00350KPA */
	/* { USB_DEVICE(0x0547, 0x6130) },  TT UCMOS01300KPA */
	/* { USB_DEVICE(0x0547, 0x6200) },  TT UCMOS02000KPA */
	/* { USB_DEVICE(0x0547, 0x6310) },  TT UCMOS03100KPA */
	/* { USB_DEVICE(0x0547, 0x6510) },  TT UCMOS05100KPA */
	/* { USB_DEVICE(0x0547, 0x6800) },  TT UCMOS08000KPA */
	/* { USB_DEVICE(0x0547, 0x6801) },  TT UCMOS08000KPB */
	{ USB_DEVICE(0x0547, 0x6801) }, /* TT UCMOS08000KPB, AS MU800 */
	/* { USB_DEVICE(0x0547, 0x6900) },  TT UCMOS09000KPA */
	/* { USB_DEVICE(0x0547, 0x6901) },  TT UCMOS09000KPB */
	/* { USB_DEVICE(0x0547, 0x6010) },  TT UCMOS10000KPA */
	/* { USB_DEVICE(0x0547, 0x6014) },  TT UCMOS14000KPA */
	/* { USB_DEVICE(0x0547, 0x6131) },  TT UCMOS01300KMA */
	/* { USB_DEVICE(0x0547, 0x6511) },  TT UCMOS05100KMA */
	/* { USB_DEVICE(0x0547, 0x8080) },  TT UHCCD00800KPA */
	/* { USB_DEVICE(0x0547, 0x8140) },  TT UHCCD01400KPA */
	/* { USB_DEVICE(0x0547, 0x8141) },  TT EXCCD01400KPA */
	/* { USB_DEVICE(0x0547, 0x8200) },  TT UHCCD02000KPA */
	/* { USB_DEVICE(0x0547, 0x8201) },  TT UHCCD02000KPB */
	/* { USB_DEVICE(0x0547, 0x8310) },  TT UHCCD03100KPA */
	/* { USB_DEVICE(0x0547, 0x8500) },  TT UHCCD05000KPA */
	/* { USB_DEVICE(0x0547, 0x8510) },  TT UHCCD05100KPA */
	/* { USB_DEVICE(0x0547, 0x8600) },  TT UHCCD06000KPA */
	/* { USB_DEVICE(0x0547, 0x8800) },  TT UHCCD08000KPA */
	/* { USB_DEVICE(0x0547, 0x8315) },  TT UHCCD03150KPA */
	/* { USB_DEVICE(0x0547, 0x7800) },  TT UHCCD00800KMA */
	/* { USB_DEVICE(0x0547, 0x7140) },  TT UHCCD01400KMA */
	/* { USB_DEVICE(0x0547, 0x7141) },  TT UHCCD01400KMB */
	/* { USB_DEVICE(0x0547, 0x7200) },  TT UHCCD02000KMA */
	/* { USB_DEVICE(0x0547, 0x7315) },  TT UHCCD03150KMA */
	{ }
};
MODUWE_DEVICE_TABWE(usb, device_tabwe);

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
#endif
};

static int __init sd_mod_init(void)
{
	int wet;

	wet = usb_wegistew(&sd_dwivew);
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}
static void __exit sd_mod_exit(void)
{
	usb_dewegistew(&sd_dwivew);
}

moduwe_init(sd_mod_init);
moduwe_exit(sd_mod_exit);
