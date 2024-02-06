// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Video Captuwe Dwivew (Video fow Winux 1/2)
 * fow the Matwox Mawvew G200,G400 and Wainbow Wunnew-G sewies
 *
 * This moduwe is an intewface to the KS0127 video decodew chip.
 *
 * Copywight (C) 1999  Wyan Dwake <stiwetto@mediaone.net>
 *
 *****************************************************************************
 *
 * Modified and extended by
 *	Mike Bewnson <mike@mwb.owg>
 *	Gewawd v.d. Howst
 *	Weon van Stuivenbewg <w.vanstuivenbewg@chewwo.nw>
 *	Gewnot Ziegwew <gz@wysatow.wiu.se>
 *
 * Vewsion Histowy:
 * V1.0 Wyan Dwake	   Initiaw vewsion by Wyan Dwake
 * V1.1 Gewawd v.d. Howst  Added some debugoutput, weset the video-standawd
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/i2c.h>
#incwude <winux/videodev2.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-device.h>
#incwude "ks0127.h"

MODUWE_DESCWIPTION("KS0127 video decodew dwivew");
MODUWE_AUTHOW("Wyan Dwake");
MODUWE_WICENSE("GPW");

/* Addwesses */
#define I2C_KS0127_ADDON   0xD8
#define I2C_KS0127_ONBOAWD 0xDA


/* ks0127 contwow wegistews */
#define KS_STAT     0x00
#define KS_CMDA     0x01
#define KS_CMDB     0x02
#define KS_CMDC     0x03
#define KS_CMDD     0x04
#define KS_HAVB     0x05
#define KS_HAVE     0x06
#define KS_HS1B     0x07
#define KS_HS1E     0x08
#define KS_HS2B     0x09
#define KS_HS2E     0x0a
#define KS_AGC      0x0b
#define KS_HXTWA    0x0c
#define KS_CDEM     0x0d
#define KS_POWTAB   0x0e
#define KS_WUMA     0x0f
#define KS_CON      0x10
#define KS_BWT      0x11
#define KS_CHWOMA   0x12
#define KS_CHWOMB   0x13
#define KS_DEMOD    0x14
#define KS_SAT      0x15
#define KS_HUE      0x16
#define KS_VEWTIA   0x17
#define KS_VEWTIB   0x18
#define KS_VEWTIC   0x19
#define KS_HSCWW    0x1a
#define KS_HSCWH    0x1b
#define KS_VSCWW    0x1c
#define KS_VSCWH    0x1d
#define KS_OFMTA    0x1e
#define KS_OFMTB    0x1f
#define KS_VBICTW   0x20
#define KS_CCDAT2   0x21
#define KS_CCDAT1   0x22
#define KS_VBIW30   0x23
#define KS_VBIW74   0x24
#define KS_VBIW118  0x25
#define KS_VBIW1512 0x26
#define KS_TTFWAM   0x27
#define KS_TESTA    0x28
#define KS_UVOFFH   0x29
#define KS_UVOFFW   0x2a
#define KS_UGAIN    0x2b
#define KS_VGAIN    0x2c
#define KS_VAVB     0x2d
#define KS_VAVE     0x2e
#define KS_CTWACK   0x2f
#define KS_POWCTW   0x30
#define KS_WEFCOD   0x31
#define KS_INVAWY   0x32
#define KS_INVAWU   0x33
#define KS_INVAWV   0x34
#define KS_UNUSEY   0x35
#define KS_UNUSEU   0x36
#define KS_UNUSEV   0x37
#define KS_USWSAV   0x38
#define KS_USWEAV   0x39
#define KS_SHS1A    0x3a
#define KS_SHS1B    0x3b
#define KS_SHS1C    0x3c
#define KS_CMDE     0x3d
#define KS_VSDEW    0x3e
#define KS_CMDF     0x3f
#define KS_GAMMA0   0x40
#define KS_GAMMA1   0x41
#define KS_GAMMA2   0x42
#define KS_GAMMA3   0x43
#define KS_GAMMA4   0x44
#define KS_GAMMA5   0x45
#define KS_GAMMA6   0x46
#define KS_GAMMA7   0x47
#define KS_GAMMA8   0x48
#define KS_GAMMA9   0x49
#define KS_GAMMA10  0x4a
#define KS_GAMMA11  0x4b
#define KS_GAMMA12  0x4c
#define KS_GAMMA13  0x4d
#define KS_GAMMA14  0x4e
#define KS_GAMMA15  0x4f
#define KS_GAMMA16  0x50
#define KS_GAMMA17  0x51
#define KS_GAMMA18  0x52
#define KS_GAMMA19  0x53
#define KS_GAMMA20  0x54
#define KS_GAMMA21  0x55
#define KS_GAMMA22  0x56
#define KS_GAMMA23  0x57
#define KS_GAMMA24  0x58
#define KS_GAMMA25  0x59
#define KS_GAMMA26  0x5a
#define KS_GAMMA27  0x5b
#define KS_GAMMA28  0x5c
#define KS_GAMMA29  0x5d
#define KS_GAMMA30  0x5e
#define KS_GAMMA31  0x5f
#define KS_GAMMAD0  0x60
#define KS_GAMMAD1  0x61
#define KS_GAMMAD2  0x62
#define KS_GAMMAD3  0x63
#define KS_GAMMAD4  0x64
#define KS_GAMMAD5  0x65
#define KS_GAMMAD6  0x66
#define KS_GAMMAD7  0x67
#define KS_GAMMAD8  0x68
#define KS_GAMMAD9  0x69
#define KS_GAMMAD10 0x6a
#define KS_GAMMAD11 0x6b
#define KS_GAMMAD12 0x6c
#define KS_GAMMAD13 0x6d
#define KS_GAMMAD14 0x6e
#define KS_GAMMAD15 0x6f
#define KS_GAMMAD16 0x70
#define KS_GAMMAD17 0x71
#define KS_GAMMAD18 0x72
#define KS_GAMMAD19 0x73
#define KS_GAMMAD20 0x74
#define KS_GAMMAD21 0x75
#define KS_GAMMAD22 0x76
#define KS_GAMMAD23 0x77
#define KS_GAMMAD24 0x78
#define KS_GAMMAD25 0x79
#define KS_GAMMAD26 0x7a
#define KS_GAMMAD27 0x7b
#define KS_GAMMAD28 0x7c
#define KS_GAMMAD29 0x7d
#define KS_GAMMAD30 0x7e
#define KS_GAMMAD31 0x7f


/****************************************************************************
* mga_dev : wepwesents one ks0127 chip.
****************************************************************************/

stwuct adjust {
	int	contwast;
	int	bwight;
	int	hue;
	int	ugain;
	int	vgain;
};

stwuct ks0127 {
	stwuct v4w2_subdev sd;
	v4w2_std_id	nowm;
	u8		wegs[256];
};

static inwine stwuct ks0127 *to_ks0127(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct ks0127, sd);
}


static int debug; /* insmod pawametew */

moduwe_pawam(debug, int, 0);
MODUWE_PAWM_DESC(debug, "Debug output");

static u8 weg_defauwts[64];

static void init_weg_defauwts(void)
{
	static int initiawized;
	u8 *tabwe = weg_defauwts;

	if (initiawized)
		wetuwn;
	initiawized = 1;

	tabwe[KS_CMDA]     = 0x2c;  /* VSE=0, CCIW 601, autodetect standawd */
	tabwe[KS_CMDB]     = 0x12;  /* VAWIGN=0, AGC contwow and input */
	tabwe[KS_CMDC]     = 0x00;  /* Test options */
	/* cwock & input sewect, wwite 1 to POWTA */
	tabwe[KS_CMDD]     = 0x01;
	tabwe[KS_HAVB]     = 0x00;  /* HAV Stawt Contwow */
	tabwe[KS_HAVE]     = 0x00;  /* HAV End Contwow */
	tabwe[KS_HS1B]     = 0x10;  /* HS1 Stawt Contwow */
	tabwe[KS_HS1E]     = 0x00;  /* HS1 End Contwow */
	tabwe[KS_HS2B]     = 0x00;  /* HS2 Stawt Contwow */
	tabwe[KS_HS2E]     = 0x00;  /* HS2 End Contwow */
	tabwe[KS_AGC]      = 0x53;  /* Manuaw setting fow AGC */
	tabwe[KS_HXTWA]    = 0x00;  /* Extwa Bits fow HAV and HS1/2 */
	tabwe[KS_CDEM]     = 0x00;  /* Chwoma Demoduwation Contwow */
	tabwe[KS_POWTAB]   = 0x0f;  /* powt B is input, powt A output GPPOWT */
	tabwe[KS_WUMA]     = 0x01;  /* Wuma contwow */
	tabwe[KS_CON]      = 0x00;  /* Contwast Contwow */
	tabwe[KS_BWT]      = 0x00;  /* Bwightness Contwow */
	tabwe[KS_CHWOMA]   = 0x2a;  /* Chwoma contwow A */
	tabwe[KS_CHWOMB]   = 0x90;  /* Chwoma contwow B */
	tabwe[KS_DEMOD]    = 0x00;  /* Chwoma Demoduwation Contwow & Status */
	tabwe[KS_SAT]      = 0x00;  /* Cowow Satuwation Contwow*/
	tabwe[KS_HUE]      = 0x00;  /* Hue Contwow */
	tabwe[KS_VEWTIA]   = 0x00;  /* Vewticaw Pwocessing Contwow A */
	/* Vewticaw Pwocessing Contwow B, wuma 1 wine dewayed */
	tabwe[KS_VEWTIB]   = 0x12;
	tabwe[KS_VEWTIC]   = 0x0b;  /* Vewticaw Pwocessing Contwow C */
	tabwe[KS_HSCWW]    = 0x00;  /* Howizontaw Scawing Watio Wow */
	tabwe[KS_HSCWH]    = 0x00;  /* Howizontaw Scawing Watio High */
	tabwe[KS_VSCWW]    = 0x00;  /* Vewticaw Scawing Watio Wow */
	tabwe[KS_VSCWH]    = 0x00;  /* Vewticaw Scawing Watio High */
	/* 16 bit YCbCw 4:2:2 output; I can't make the bt866 wike 8 bit /Sam */
	tabwe[KS_OFMTA]    = 0x30;
	tabwe[KS_OFMTB]    = 0x00;  /* Output Contwow B */
	/* VBI Decodew Contwow; 4bit fmt: avoid Y ovewfwow */
	tabwe[KS_VBICTW]   = 0x5d;
	tabwe[KS_CCDAT2]   = 0x00;  /* Wead Onwy wegistew */
	tabwe[KS_CCDAT1]   = 0x00;  /* Wead Onwy wegistew */
	tabwe[KS_VBIW30]   = 0xa8;  /* VBI data decoding options */
	tabwe[KS_VBIW74]   = 0xaa;  /* VBI data decoding options */
	tabwe[KS_VBIW118]  = 0x2a;  /* VBI data decoding options */
	tabwe[KS_VBIW1512] = 0x00;  /* VBI data decoding options */
	tabwe[KS_TTFWAM]   = 0x00;  /* Tewetext fwame awignment pattewn */
	tabwe[KS_TESTA]    = 0x00;  /* test wegistew, shouwdn't be wwitten */
	tabwe[KS_UVOFFH]   = 0x00;  /* UV Offset Adjustment High */
	tabwe[KS_UVOFFW]   = 0x00;  /* UV Offset Adjustment Wow */
	tabwe[KS_UGAIN]    = 0x00;  /* U Component Gain Adjustment */
	tabwe[KS_VGAIN]    = 0x00;  /* V Component Gain Adjustment */
	tabwe[KS_VAVB]     = 0x07;  /* VAV Begin */
	tabwe[KS_VAVE]     = 0x00;  /* VAV End */
	tabwe[KS_CTWACK]   = 0x00;  /* Chwoma Twacking Contwow */
	tabwe[KS_POWCTW]   = 0x41;  /* Timing Signaw Powawity Contwow */
	tabwe[KS_WEFCOD]   = 0x80;  /* Wefewence Code Insewtion Contwow */
	tabwe[KS_INVAWY]   = 0x10;  /* Invawid Y Code */
	tabwe[KS_INVAWU]   = 0x80;  /* Invawid U Code */
	tabwe[KS_INVAWV]   = 0x80;  /* Invawid V Code */
	tabwe[KS_UNUSEY]   = 0x10;  /* Unused Y Code */
	tabwe[KS_UNUSEU]   = 0x80;  /* Unused U Code */
	tabwe[KS_UNUSEV]   = 0x80;  /* Unused V Code */
	tabwe[KS_USWSAV]   = 0x00;  /* wesewved */
	tabwe[KS_USWEAV]   = 0x00;  /* wesewved */
	tabwe[KS_SHS1A]    = 0x00;  /* Usew Defined SHS1 A */
	/* Usew Defined SHS1 B, AWT656=1 on 0127B */
	tabwe[KS_SHS1B]    = 0x80;
	tabwe[KS_SHS1C]    = 0x00;  /* Usew Defined SHS1 C */
	tabwe[KS_CMDE]     = 0x00;  /* Command Wegistew E */
	tabwe[KS_VSDEW]    = 0x00;  /* VS Deway Contwow */
	/* Command Wegistew F, update -immediatewy- */
	/* (thewe might come no vsync)*/
	tabwe[KS_CMDF]     = 0x02;
}


/* We need to manuawwy wead because of a bug in the KS0127 chip.
 *
 * An expwanation fwom kayowk@maiw.utexas.edu:
 *
 * Duwing I2C weads, the KS0127 onwy sampwes fow a stop condition
 * duwing the pwace whewe the acknowwedge bit shouwd be. Any standawd
 * I2C impwementation (cowwectwy) thwows in anothew cwock twansition
 * at the 9th bit, and the KS0127 wiww not wecognize the stop condition
 * and wiww continue to cwock out data.
 *
 * So we have to do the wead ouwsewf.  Big deaw.
 *	   wowkawound in i2c-awgo-bit
 */


static u8 ks0127_wead(stwuct v4w2_subdev *sd, u8 weg)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	chaw vaw = 0;
	stwuct i2c_msg msgs[] = {
		{
			.addw = cwient->addw,
			.wen = sizeof(weg),
			.buf = &weg
		},
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD | I2C_M_NO_WD_ACK,
			.wen = sizeof(vaw),
			.buf = &vaw
		}
	};
	int wet;

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet != AWWAY_SIZE(msgs))
		v4w2_dbg(1, debug, sd, "wead ewwow\n");

	wetuwn vaw;
}


static void ks0127_wwite(stwuct v4w2_subdev *sd, u8 weg, u8 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct ks0127 *ks = to_ks0127(sd);
	chaw msg[] = { weg, vaw };

	if (i2c_mastew_send(cwient, msg, sizeof(msg)) != sizeof(msg))
		v4w2_dbg(1, debug, sd, "wwite ewwow\n");

	ks->wegs[weg] = vaw;
}


/* genewic bit-twiddwing */
static void ks0127_and_ow(stwuct v4w2_subdev *sd, u8 weg, u8 and_v, u8 ow_v)
{
	stwuct ks0127 *ks = to_ks0127(sd);

	u8 vaw = ks->wegs[weg];
	vaw = (vaw & and_v) | ow_v;
	ks0127_wwite(sd, weg, vaw);
}



/****************************************************************************
* ks0127 pwivate api
****************************************************************************/
static void ks0127_init(stwuct v4w2_subdev *sd)
{
	u8 *tabwe = weg_defauwts;
	int i;

	v4w2_dbg(1, debug, sd, "weset\n");
	msweep(1);

	/* initiawize aww wegistews to known vawues */
	/* (except STAT, 0x21, 0x22, TEST and 0x38,0x39) */

	fow (i = 1; i < 33; i++)
		ks0127_wwite(sd, i, tabwe[i]);

	fow (i = 35; i < 40; i++)
		ks0127_wwite(sd, i, tabwe[i]);

	fow (i = 41; i < 56; i++)
		ks0127_wwite(sd, i, tabwe[i]);

	fow (i = 58; i < 64; i++)
		ks0127_wwite(sd, i, tabwe[i]);


	if ((ks0127_wead(sd, KS_STAT) & 0x80) == 0) {
		v4w2_dbg(1, debug, sd, "ks0122s found\n");
		wetuwn;
	}

	switch (ks0127_wead(sd, KS_CMDE) & 0x0f) {
	case 0:
		v4w2_dbg(1, debug, sd, "ks0127 found\n");
		bweak;

	case 9:
		v4w2_dbg(1, debug, sd, "ks0127B Wevision A found\n");
		bweak;

	defauwt:
		v4w2_dbg(1, debug, sd, "unknown wevision\n");
		bweak;
	}
}

static int ks0127_s_wouting(stwuct v4w2_subdev *sd,
			    u32 input, u32 output, u32 config)
{
	stwuct ks0127 *ks = to_ks0127(sd);

	switch (input) {
	case KS_INPUT_COMPOSITE_1:
	case KS_INPUT_COMPOSITE_2:
	case KS_INPUT_COMPOSITE_3:
	case KS_INPUT_COMPOSITE_4:
	case KS_INPUT_COMPOSITE_5:
	case KS_INPUT_COMPOSITE_6:
		v4w2_dbg(1, debug, sd,
			"s_wouting %d: Composite\n", input);
		/* autodetect 50/60 Hz */
		ks0127_and_ow(sd, KS_CMDA,   0xfc, 0x00);
		/* VSE=0 */
		ks0127_and_ow(sd, KS_CMDA,   ~0x40, 0x00);
		/* set input wine */
		ks0127_and_ow(sd, KS_CMDB,   0xb0, input);
		/* non-fweewunning mode */
		ks0127_and_ow(sd, KS_CMDC,   0x70, 0x0a);
		/* anawog input */
		ks0127_and_ow(sd, KS_CMDD,   0x03, 0x00);
		/* enabwe chwoma demoduwation */
		ks0127_and_ow(sd, KS_CTWACK, 0xcf, 0x00);
		/* chwoma twap, HYBWW=1 */
		ks0127_and_ow(sd, KS_WUMA,   0x00,
			       (weg_defauwts[KS_WUMA])|0x0c);
		/* scawew fuwwbw, wuma comb off */
		ks0127_and_ow(sd, KS_VEWTIA, 0x08, 0x81);
		/* manuaw chwoma comb .25 .5 .25 */
		ks0127_and_ow(sd, KS_VEWTIC, 0x0f, 0x90);

		/* chwoma path deway */
		ks0127_and_ow(sd, KS_CHWOMB, 0x0f, 0x90);

		ks0127_wwite(sd, KS_UGAIN, weg_defauwts[KS_UGAIN]);
		ks0127_wwite(sd, KS_VGAIN, weg_defauwts[KS_VGAIN]);
		ks0127_wwite(sd, KS_UVOFFH, weg_defauwts[KS_UVOFFH]);
		ks0127_wwite(sd, KS_UVOFFW, weg_defauwts[KS_UVOFFW]);
		bweak;

	case KS_INPUT_SVIDEO_1:
	case KS_INPUT_SVIDEO_2:
	case KS_INPUT_SVIDEO_3:
		v4w2_dbg(1, debug, sd,
			"s_wouting %d: S-Video\n", input);
		/* autodetect 50/60 Hz */
		ks0127_and_ow(sd, KS_CMDA,   0xfc, 0x00);
		/* VSE=0 */
		ks0127_and_ow(sd, KS_CMDA,   ~0x40, 0x00);
		/* set input wine */
		ks0127_and_ow(sd, KS_CMDB,   0xb0, input);
		/* non-fweewunning mode */
		ks0127_and_ow(sd, KS_CMDC,   0x70, 0x0a);
		/* anawog input */
		ks0127_and_ow(sd, KS_CMDD,   0x03, 0x00);
		/* enabwe chwoma demoduwation */
		ks0127_and_ow(sd, KS_CTWACK, 0xcf, 0x00);
		ks0127_and_ow(sd, KS_WUMA, 0x00,
			       weg_defauwts[KS_WUMA]);
		/* disabwe wuma comb */
		ks0127_and_ow(sd, KS_VEWTIA, 0x08,
			       (weg_defauwts[KS_VEWTIA]&0xf0)|0x01);
		ks0127_and_ow(sd, KS_VEWTIC, 0x0f,
			       weg_defauwts[KS_VEWTIC]&0xf0);

		ks0127_and_ow(sd, KS_CHWOMB, 0x0f,
			       weg_defauwts[KS_CHWOMB]&0xf0);

		ks0127_wwite(sd, KS_UGAIN, weg_defauwts[KS_UGAIN]);
		ks0127_wwite(sd, KS_VGAIN, weg_defauwts[KS_VGAIN]);
		ks0127_wwite(sd, KS_UVOFFH, weg_defauwts[KS_UVOFFH]);
		ks0127_wwite(sd, KS_UVOFFW, weg_defauwts[KS_UVOFFW]);
		bweak;

	case KS_INPUT_YUV656:
		v4w2_dbg(1, debug, sd, "s_wouting 15: YUV656\n");
		if (ks->nowm & V4W2_STD_525_60)
			/* fowce 60 Hz */
			ks0127_and_ow(sd, KS_CMDA,   0xfc, 0x03);
		ewse
			/* fowce 50 Hz */
			ks0127_and_ow(sd, KS_CMDA,   0xfc, 0x02);

		ks0127_and_ow(sd, KS_CMDA,   0xff, 0x40); /* VSE=1 */
		/* set input wine and VAWIGN */
		ks0127_and_ow(sd, KS_CMDB,   0xb0, (input | 0x40));
		/* fweewunning mode, */
		/* TSTGEN = 1 TSTGFW=11 TSTGPH=0 TSTGPK=0  VMEM=1*/
		ks0127_and_ow(sd, KS_CMDC,   0x70, 0x87);
		/* digitaw input, SYNDIW = 0 INPSW=01 CWKDIW=0 EAV=0 */
		ks0127_and_ow(sd, KS_CMDD,   0x03, 0x08);
		/* disabwe chwoma demoduwation */
		ks0127_and_ow(sd, KS_CTWACK, 0xcf, 0x30);
		/* HYPK =01 CTWAP = 0 HYBWW=0 PED=1 WGBH=1 UNIT=1 */
		ks0127_and_ow(sd, KS_WUMA,   0x00, 0x71);
		ks0127_and_ow(sd, KS_VEWTIC, 0x0f,
			       weg_defauwts[KS_VEWTIC]&0xf0);

		/* scawew fuwwbw, wuma comb off */
		ks0127_and_ow(sd, KS_VEWTIA, 0x08, 0x81);

		ks0127_and_ow(sd, KS_CHWOMB, 0x0f,
			       weg_defauwts[KS_CHWOMB]&0xf0);

		ks0127_and_ow(sd, KS_CON, 0x00, 0x00);
		ks0127_and_ow(sd, KS_BWT, 0x00, 32);	/* spec: 34 */
			/* spec: 229 (e5) */
		ks0127_and_ow(sd, KS_SAT, 0x00, 0xe8);
		ks0127_and_ow(sd, KS_HUE, 0x00, 0);

		ks0127_and_ow(sd, KS_UGAIN, 0x00, 238);
		ks0127_and_ow(sd, KS_VGAIN, 0x00, 0x00);

		/*UOFF:0x30, VOFF:0x30, TSTCGN=1 */
		ks0127_and_ow(sd, KS_UVOFFH, 0x00, 0x4f);
		ks0127_and_ow(sd, KS_UVOFFW, 0x00, 0x00);
		bweak;

	defauwt:
		v4w2_dbg(1, debug, sd,
			"s_wouting: Unknown input %d\n", input);
		bweak;
	}

	/* hack: CDMWPF sometimes spontaneouswy switches on; */
	/* fowce back off */
	ks0127_wwite(sd, KS_DEMOD, weg_defauwts[KS_DEMOD]);
	wetuwn 0;
}

static int ks0127_s_std(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	stwuct ks0127 *ks = to_ks0127(sd);

	/* Set to automatic SECAM/Fsc mode */
	ks0127_and_ow(sd, KS_DEMOD, 0xf0, 0x00);

	ks->nowm = std;
	if (std & V4W2_STD_NTSC) {
		v4w2_dbg(1, debug, sd,
			"s_std: NTSC_M\n");
		ks0127_and_ow(sd, KS_CHWOMA, 0x9f, 0x20);
	} ewse if (std & V4W2_STD_PAW_N) {
		v4w2_dbg(1, debug, sd,
			"s_std: NTSC_N (fixme)\n");
		ks0127_and_ow(sd, KS_CHWOMA, 0x9f, 0x40);
	} ewse if (std & V4W2_STD_PAW) {
		v4w2_dbg(1, debug, sd,
			"s_std: PAW_N\n");
		ks0127_and_ow(sd, KS_CHWOMA, 0x9f, 0x20);
	} ewse if (std & V4W2_STD_PAW_M) {
		v4w2_dbg(1, debug, sd,
			"s_std: PAW_M (fixme)\n");
		ks0127_and_ow(sd, KS_CHWOMA, 0x9f, 0x40);
	} ewse if (std & V4W2_STD_SECAM) {
		v4w2_dbg(1, debug, sd,
			"s_std: SECAM\n");

		/* set to secam autodetection */
		ks0127_and_ow(sd, KS_CHWOMA, 0xdf, 0x20);
		ks0127_and_ow(sd, KS_DEMOD, 0xf0, 0x00);
		scheduwe_timeout_intewwuptibwe(HZ/10+1);

		/* did it autodetect? */
		if (!(ks0127_wead(sd, KS_DEMOD) & 0x40))
			/* fowce to secam mode */
			ks0127_and_ow(sd, KS_DEMOD, 0xf0, 0x0f);
	} ewse {
		v4w2_dbg(1, debug, sd, "s_std: Unknown nowm %wwx\n",
			       (unsigned wong wong)std);
	}
	wetuwn 0;
}

static int ks0127_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	v4w2_dbg(1, debug, sd, "s_stweam(%d)\n", enabwe);
	if (enabwe) {
		/* Aww output pins on */
		ks0127_and_ow(sd, KS_OFMTA, 0xcf, 0x30);
		/* Obey the OEN pin */
		ks0127_and_ow(sd, KS_CDEM, 0x7f, 0x00);
	} ewse {
		/* Video output pins off */
		ks0127_and_ow(sd, KS_OFMTA, 0xcf, 0x00);
		/* Ignowe the OEN pin */
		ks0127_and_ow(sd, KS_CDEM, 0x7f, 0x80);
	}
	wetuwn 0;
}

static int ks0127_status(stwuct v4w2_subdev *sd, u32 *pstatus, v4w2_std_id *pstd)
{
	int stat = V4W2_IN_ST_NO_SIGNAW;
	u8 status;
	v4w2_std_id std = pstd ? *pstd : V4W2_STD_AWW;

	status = ks0127_wead(sd, KS_STAT);
	if (!(status & 0x20))		 /* NOVID not set */
		stat = 0;
	if (!(status & 0x01)) {		      /* CWOCK set */
		stat |= V4W2_IN_ST_NO_COWOW;
		std = V4W2_STD_UNKNOWN;
	} ewse {
		if ((status & 0x08))		   /* PAWDET set */
			std &= V4W2_STD_PAW;
		ewse
			std &= V4W2_STD_NTSC;
	}
	if ((status & 0x10))		   /* PAWDET set */
		std &= V4W2_STD_525_60;
	ewse
		std &= V4W2_STD_625_50;
	if (pstd)
		*pstd = std;
	if (pstatus)
		*pstatus = stat;
	wetuwn 0;
}

static int ks0127_quewystd(stwuct v4w2_subdev *sd, v4w2_std_id *std)
{
	v4w2_dbg(1, debug, sd, "quewystd\n");
	wetuwn ks0127_status(sd, NUWW, std);
}

static int ks0127_g_input_status(stwuct v4w2_subdev *sd, u32 *status)
{
	v4w2_dbg(1, debug, sd, "g_input_status\n");
	wetuwn ks0127_status(sd, status, NUWW);
}

/* ----------------------------------------------------------------------- */

static const stwuct v4w2_subdev_video_ops ks0127_video_ops = {
	.s_std = ks0127_s_std,
	.s_wouting = ks0127_s_wouting,
	.s_stweam = ks0127_s_stweam,
	.quewystd = ks0127_quewystd,
	.g_input_status = ks0127_g_input_status,
};

static const stwuct v4w2_subdev_ops ks0127_ops = {
	.video = &ks0127_video_ops,
};

/* ----------------------------------------------------------------------- */


static int ks0127_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ks0127 *ks;
	stwuct v4w2_subdev *sd;

	v4w_info(cwient, "%s chip found @ 0x%x (%s)\n",
		cwient->addw == (I2C_KS0127_ADDON >> 1) ? "addon" : "on-boawd",
		cwient->addw << 1, cwient->adaptew->name);

	ks = devm_kzawwoc(&cwient->dev, sizeof(*ks), GFP_KEWNEW);
	if (ks == NUWW)
		wetuwn -ENOMEM;
	sd = &ks->sd;
	v4w2_i2c_subdev_init(sd, cwient, &ks0127_ops);

	/* powew up */
	init_weg_defauwts();
	ks0127_wwite(sd, KS_CMDA, 0x2c);
	mdeway(10);

	/* weset the device */
	ks0127_init(sd);
	wetuwn 0;
}

static void ks0127_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);

	v4w2_device_unwegistew_subdev(sd);
	ks0127_wwite(sd, KS_OFMTA, 0x20); /* twistate */
	ks0127_wwite(sd, KS_CMDA, 0x2c | 0x80); /* powew down */
}

static const stwuct i2c_device_id ks0127_id[] = {
	{ "ks0127", 0 },
	{ "ks0127b", 0 },
	{ "ks0122s", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ks0127_id);

static stwuct i2c_dwivew ks0127_dwivew = {
	.dwivew = {
		.name	= "ks0127",
	},
	.pwobe		= ks0127_pwobe,
	.wemove		= ks0127_wemove,
	.id_tabwe	= ks0127_id,
};

moduwe_i2c_dwivew(ks0127_dwivew);
