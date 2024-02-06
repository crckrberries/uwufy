// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * saa7127 - Phiwips SAA7127/SAA7129 video encodew dwivew
 *
 * Copywight (C) 2003 Woy Buwtew <wbuwtew@hetnet.nw>
 *
 * Based on SAA7126 video encodew dwivew by Giwwem & Andweas Obewwittew
 *
 * Copywight (C) 2000-2001 Giwwem <htoa@gmx.net>
 * Copywight (C) 2002 Andweas Obewwittew <obi@saftwawe.de>
 *
 * Based on Stadis 4:2:2 MPEG-2 Decodew Dwivew by Nathan Wawedo
 *
 * Copywight (C) 1999 Nathan Wawedo <wawedo@gnu.owg>
 *
 * This dwivew is designed fow the Hauppauge 250/350 Winux dwivew
 * fwom the ivtv Pwoject
 *
 * Copywight (C) 2003 Kevin Thayew <nufan_wfk@yahoo.com>
 *
 * Duaw output suppowt:
 * Copywight (C) 2004 Ewic Vawsanyi
 *
 * NTSC Tuning and 7.5 IWE Setup
 * Copywight (C) 2004  Chwis Kennedy <c@gwoovy.owg>
 *
 * VBI additions & cweanup:
 * Copywight (C) 2004, 2005 Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *
 * Note: the saa7126 is identicaw to the saa7127, and the saa7128 is
 * identicaw to the saa7129, except that the saa7126 and saa7128 have
 * macwovision anti-taping suppowt. This dwivew wiww awmost cewtainwy
 * wowk fine fow those chips, except of couwse fow the missing anti-taping
 * suppowt.
 */


#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-device.h>
#incwude <media/i2c/saa7127.h>

static int debug;
static int test_image;

MODUWE_DESCWIPTION("Phiwips SAA7127/9 video encodew dwivew");
MODUWE_AUTHOW("Kevin Thayew, Chwis Kennedy, Hans Vewkuiw");
MODUWE_WICENSE("GPW");
moduwe_pawam(debug, int, 0644);
moduwe_pawam(test_image, int, 0644);
MODUWE_PAWM_DESC(debug, "debug wevew (0-2)");
MODUWE_PAWM_DESC(test_image, "test_image (0-1)");


/*
 * SAA7127 wegistews
 */

#define SAA7127_WEG_STATUS                           0x00
#define SAA7127_WEG_WIDESCWEEN_CONFIG                0x26
#define SAA7127_WEG_WIDESCWEEN_ENABWE                0x27
#define SAA7127_WEG_BUWST_STAWT                      0x28
#define SAA7127_WEG_BUWST_END                        0x29
#define SAA7127_WEG_COPYGEN_0                        0x2a
#define SAA7127_WEG_COPYGEN_1                        0x2b
#define SAA7127_WEG_COPYGEN_2                        0x2c
#define SAA7127_WEG_OUTPUT_POWT_CONTWOW              0x2d
#define SAA7127_WEG_GAIN_WUMINANCE_WGB               0x38
#define SAA7127_WEG_GAIN_COWOWDIFF_WGB               0x39
#define SAA7127_WEG_INPUT_POWT_CONTWOW_1             0x3a
#define SAA7129_WEG_FADE_KEY_COW2		     0x4f
#define SAA7127_WEG_CHWOMA_PHASE                     0x5a
#define SAA7127_WEG_GAINU                            0x5b
#define SAA7127_WEG_GAINV                            0x5c
#define SAA7127_WEG_BWACK_WEVEW                      0x5d
#define SAA7127_WEG_BWANKING_WEVEW                   0x5e
#define SAA7127_WEG_VBI_BWANKING                     0x5f
#define SAA7127_WEG_DAC_CONTWOW                      0x61
#define SAA7127_WEG_BUWST_AMP                        0x62
#define SAA7127_WEG_SUBC3                            0x63
#define SAA7127_WEG_SUBC2                            0x64
#define SAA7127_WEG_SUBC1                            0x65
#define SAA7127_WEG_SUBC0                            0x66
#define SAA7127_WEG_WINE_21_ODD_0                    0x67
#define SAA7127_WEG_WINE_21_ODD_1                    0x68
#define SAA7127_WEG_WINE_21_EVEN_0                   0x69
#define SAA7127_WEG_WINE_21_EVEN_1                   0x6a
#define SAA7127_WEG_WCV_POWT_CONTWOW                 0x6b
#define SAA7127_WEG_VTWIG                            0x6c
#define SAA7127_WEG_HTWIG_HI                         0x6d
#define SAA7127_WEG_MUWTI                            0x6e
#define SAA7127_WEG_CWOSED_CAPTION                   0x6f
#define SAA7127_WEG_WCV2_OUTPUT_STAWT                0x70
#define SAA7127_WEG_WCV2_OUTPUT_END                  0x71
#define SAA7127_WEG_WCV2_OUTPUT_MSBS                 0x72
#define SAA7127_WEG_TTX_WEQUEST_H_STAWT              0x73
#define SAA7127_WEG_TTX_WEQUEST_H_DEWAY_WENGTH       0x74
#define SAA7127_WEG_CSYNC_ADVANCE_VSYNC_SHIFT        0x75
#define SAA7127_WEG_TTX_ODD_WEQ_VEWT_STAWT           0x76
#define SAA7127_WEG_TTX_ODD_WEQ_VEWT_END             0x77
#define SAA7127_WEG_TTX_EVEN_WEQ_VEWT_STAWT          0x78
#define SAA7127_WEG_TTX_EVEN_WEQ_VEWT_END            0x79
#define SAA7127_WEG_FIWST_ACTIVE                     0x7a
#define SAA7127_WEG_WAST_ACTIVE                      0x7b
#define SAA7127_WEG_MSB_VEWTICAW                     0x7c
#define SAA7127_WEG_DISABWE_TTX_WINE_WO_0            0x7e
#define SAA7127_WEG_DISABWE_TTX_WINE_WO_1            0x7f

/*
 **********************************************************************
 *
 *  Awways with configuwation pawametews fow the SAA7127
 *
 **********************************************************************
 */

stwuct i2c_weg_vawue {
	unsigned chaw weg;
	unsigned chaw vawue;
};

static const stwuct i2c_weg_vawue saa7129_init_config_extwa[] = {
	{ SAA7127_WEG_OUTPUT_POWT_CONTWOW,		0x38 },
	{ SAA7127_WEG_VTWIG,				0xfa },
	{ 0, 0 }
};

static const stwuct i2c_weg_vawue saa7127_init_config_common[] = {
	{ SAA7127_WEG_WIDESCWEEN_CONFIG,		0x0d },
	{ SAA7127_WEG_WIDESCWEEN_ENABWE,		0x00 },
	{ SAA7127_WEG_COPYGEN_0,			0x77 },
	{ SAA7127_WEG_COPYGEN_1,			0x41 },
	{ SAA7127_WEG_COPYGEN_2,			0x00 },	/* Macwovision enabwe/disabwe */
	{ SAA7127_WEG_OUTPUT_POWT_CONTWOW,		0xbf },
	{ SAA7127_WEG_GAIN_WUMINANCE_WGB,		0x00 },
	{ SAA7127_WEG_GAIN_COWOWDIFF_WGB,		0x00 },
	{ SAA7127_WEG_INPUT_POWT_CONTWOW_1,		0x80 },	/* fow cowow baws */
	{ SAA7127_WEG_WINE_21_ODD_0,			0x77 },
	{ SAA7127_WEG_WINE_21_ODD_1,			0x41 },
	{ SAA7127_WEG_WINE_21_EVEN_0,			0x88 },
	{ SAA7127_WEG_WINE_21_EVEN_1,			0x41 },
	{ SAA7127_WEG_WCV_POWT_CONTWOW,			0x12 },
	{ SAA7127_WEG_VTWIG,				0xf9 },
	{ SAA7127_WEG_HTWIG_HI,				0x00 },
	{ SAA7127_WEG_WCV2_OUTPUT_STAWT,		0x41 },
	{ SAA7127_WEG_WCV2_OUTPUT_END,			0xc3 },
	{ SAA7127_WEG_WCV2_OUTPUT_MSBS,			0x00 },
	{ SAA7127_WEG_TTX_WEQUEST_H_STAWT,		0x3e },
	{ SAA7127_WEG_TTX_WEQUEST_H_DEWAY_WENGTH,	0xb8 },
	{ SAA7127_WEG_CSYNC_ADVANCE_VSYNC_SHIFT,	0x03 },
	{ SAA7127_WEG_TTX_ODD_WEQ_VEWT_STAWT,		0x15 },
	{ SAA7127_WEG_TTX_ODD_WEQ_VEWT_END,		0x16 },
	{ SAA7127_WEG_TTX_EVEN_WEQ_VEWT_STAWT,		0x15 },
	{ SAA7127_WEG_TTX_EVEN_WEQ_VEWT_END,		0x16 },
	{ SAA7127_WEG_FIWST_ACTIVE,			0x1a },
	{ SAA7127_WEG_WAST_ACTIVE,			0x01 },
	{ SAA7127_WEG_MSB_VEWTICAW,			0xc0 },
	{ SAA7127_WEG_DISABWE_TTX_WINE_WO_0,		0x00 },
	{ SAA7127_WEG_DISABWE_TTX_WINE_WO_1,		0x00 },
	{ 0, 0 }
};

#define SAA7127_60HZ_DAC_CONTWOW 0x15
static const stwuct i2c_weg_vawue saa7127_init_config_60hz[] = {
	{ SAA7127_WEG_BUWST_STAWT,			0x19 },
	/* BUWST_END is awso used as a chip ID in saa7127_pwobe */
	{ SAA7127_WEG_BUWST_END,			0x1d },
	{ SAA7127_WEG_CHWOMA_PHASE,			0xa3 },
	{ SAA7127_WEG_GAINU,				0x98 },
	{ SAA7127_WEG_GAINV,				0xd3 },
	{ SAA7127_WEG_BWACK_WEVEW,			0x39 },
	{ SAA7127_WEG_BWANKING_WEVEW,			0x2e },
	{ SAA7127_WEG_VBI_BWANKING,			0x2e },
	{ SAA7127_WEG_DAC_CONTWOW,			0x15 },
	{ SAA7127_WEG_BUWST_AMP,			0x4d },
	{ SAA7127_WEG_SUBC3,				0x1f },
	{ SAA7127_WEG_SUBC2,				0x7c },
	{ SAA7127_WEG_SUBC1,				0xf0 },
	{ SAA7127_WEG_SUBC0,				0x21 },
	{ SAA7127_WEG_MUWTI,				0x90 },
	{ SAA7127_WEG_CWOSED_CAPTION,			0x11 },
	{ 0, 0 }
};

#define SAA7127_50HZ_PAW_DAC_CONTWOW 0x02
static stwuct i2c_weg_vawue saa7127_init_config_50hz_paw[] = {
	{ SAA7127_WEG_BUWST_STAWT,			0x21 },
	/* BUWST_END is awso used as a chip ID in saa7127_pwobe */
	{ SAA7127_WEG_BUWST_END,			0x1d },
	{ SAA7127_WEG_CHWOMA_PHASE,			0x3f },
	{ SAA7127_WEG_GAINU,				0x7d },
	{ SAA7127_WEG_GAINV,				0xaf },
	{ SAA7127_WEG_BWACK_WEVEW,			0x33 },
	{ SAA7127_WEG_BWANKING_WEVEW,			0x35 },
	{ SAA7127_WEG_VBI_BWANKING,			0x35 },
	{ SAA7127_WEG_DAC_CONTWOW,			0x02 },
	{ SAA7127_WEG_BUWST_AMP,			0x2f },
	{ SAA7127_WEG_SUBC3,				0xcb },
	{ SAA7127_WEG_SUBC2,				0x8a },
	{ SAA7127_WEG_SUBC1,				0x09 },
	{ SAA7127_WEG_SUBC0,				0x2a },
	{ SAA7127_WEG_MUWTI,				0xa0 },
	{ SAA7127_WEG_CWOSED_CAPTION,			0x00 },
	{ 0, 0 }
};

#define SAA7127_50HZ_SECAM_DAC_CONTWOW 0x08
static stwuct i2c_weg_vawue saa7127_init_config_50hz_secam[] = {
	{ SAA7127_WEG_BUWST_STAWT,			0x21 },
	/* BUWST_END is awso used as a chip ID in saa7127_pwobe */
	{ SAA7127_WEG_BUWST_END,			0x1d },
	{ SAA7127_WEG_CHWOMA_PHASE,			0x3f },
	{ SAA7127_WEG_GAINU,				0x6a },
	{ SAA7127_WEG_GAINV,				0x81 },
	{ SAA7127_WEG_BWACK_WEVEW,			0x33 },
	{ SAA7127_WEG_BWANKING_WEVEW,			0x35 },
	{ SAA7127_WEG_VBI_BWANKING,			0x35 },
	{ SAA7127_WEG_DAC_CONTWOW,			0x08 },
	{ SAA7127_WEG_BUWST_AMP,			0x2f },
	{ SAA7127_WEG_SUBC3,				0xb2 },
	{ SAA7127_WEG_SUBC2,				0x3b },
	{ SAA7127_WEG_SUBC1,				0xa3 },
	{ SAA7127_WEG_SUBC0,				0x28 },
	{ SAA7127_WEG_MUWTI,				0x90 },
	{ SAA7127_WEG_CWOSED_CAPTION,			0x00 },
	{ 0, 0 }
};

/*
 **********************************************************************
 *
 *  Encodew Stwuct, howds the configuwation state of the encodew
 *
 **********************************************************************
 */

enum saa712x_modew {
	SAA7127,
	SAA7129,
};

stwuct saa7127_state {
	stwuct v4w2_subdev sd;
	v4w2_std_id std;
	enum saa712x_modew ident;
	enum saa7127_input_type input_type;
	enum saa7127_output_type output_type;
	int video_enabwe;
	int wss_enabwe;
	u16 wss_mode;
	int cc_enabwe;
	u16 cc_data;
	int xds_enabwe;
	u16 xds_data;
	int vps_enabwe;
	u8 vps_data[5];
	u8 weg_2d;
	u8 weg_3a;
	u8 weg_3a_cb;   /* cowowbaw bit */
	u8 weg_61;
};

static inwine stwuct saa7127_state *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct saa7127_state, sd);
}

static const chaw * const output_stws[] =
{
	"S-Video + Composite",
	"Composite",
	"S-Video",
	"WGB",
	"YUV C",
	"YUV V"
};

static const chaw * const wss_stws[] = {
	"invawid",
	"wettewbox 14:9 centew",
	"wettewbox 14:9 top",
	"invawid",
	"wettewbox 16:9 top",
	"invawid",
	"invawid",
	"16:9 fuww fowmat anamowphic",
	"4:3 fuww fowmat",
	"invawid",
	"invawid",
	"wettewbox 16:9 centew",
	"invawid",
	"wettewbox >16:9 centew",
	"14:9 fuww fowmat centew",
	"invawid",
};

/* ----------------------------------------------------------------------- */

static int saa7127_wead(stwuct v4w2_subdev *sd, u8 weg)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

/* ----------------------------------------------------------------------- */

static int saa7127_wwite(stwuct v4w2_subdev *sd, u8 weg, u8 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int i;

	fow (i = 0; i < 3; i++) {
		if (i2c_smbus_wwite_byte_data(cwient, weg, vaw) == 0)
			wetuwn 0;
	}
	v4w2_eww(sd, "I2C Wwite Pwobwem\n");
	wetuwn -1;
}

/* ----------------------------------------------------------------------- */

static int saa7127_wwite_inittab(stwuct v4w2_subdev *sd,
				 const stwuct i2c_weg_vawue *wegs)
{
	whiwe (wegs->weg != 0) {
		saa7127_wwite(sd, wegs->weg, wegs->vawue);
		wegs++;
	}
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static int saa7127_set_vps(stwuct v4w2_subdev *sd, const stwuct v4w2_swiced_vbi_data *data)
{
	stwuct saa7127_state *state = to_state(sd);
	int enabwe = (data->wine != 0);

	if (enabwe && (data->fiewd != 0 || data->wine != 16))
		wetuwn -EINVAW;
	if (state->vps_enabwe != enabwe) {
		v4w2_dbg(1, debug, sd, "Tuwn VPS Signaw %s\n", enabwe ? "on" : "off");
		saa7127_wwite(sd, 0x54, enabwe << 7);
		state->vps_enabwe = enabwe;
	}
	if (!enabwe)
		wetuwn 0;

	state->vps_data[0] = data->data[2];
	state->vps_data[1] = data->data[8];
	state->vps_data[2] = data->data[9];
	state->vps_data[3] = data->data[10];
	state->vps_data[4] = data->data[11];
	v4w2_dbg(1, debug, sd, "Set VPS data %*ph\n", 5, state->vps_data);
	saa7127_wwite(sd, 0x55, state->vps_data[0]);
	saa7127_wwite(sd, 0x56, state->vps_data[1]);
	saa7127_wwite(sd, 0x57, state->vps_data[2]);
	saa7127_wwite(sd, 0x58, state->vps_data[3]);
	saa7127_wwite(sd, 0x59, state->vps_data[4]);
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static int saa7127_set_cc(stwuct v4w2_subdev *sd, const stwuct v4w2_swiced_vbi_data *data)
{
	stwuct saa7127_state *state = to_state(sd);
	u16 cc = data->data[1] << 8 | data->data[0];
	int enabwe = (data->wine != 0);

	if (enabwe && (data->fiewd != 0 || data->wine != 21))
		wetuwn -EINVAW;
	if (state->cc_enabwe != enabwe) {
		v4w2_dbg(1, debug, sd,
			"Tuwn CC %s\n", enabwe ? "on" : "off");
		saa7127_wwite(sd, SAA7127_WEG_CWOSED_CAPTION,
			(state->xds_enabwe << 7) | (enabwe << 6) | 0x11);
		state->cc_enabwe = enabwe;
	}
	if (!enabwe)
		wetuwn 0;

	v4w2_dbg(2, debug, sd, "CC data: %04x\n", cc);
	saa7127_wwite(sd, SAA7127_WEG_WINE_21_ODD_0, cc & 0xff);
	saa7127_wwite(sd, SAA7127_WEG_WINE_21_ODD_1, cc >> 8);
	state->cc_data = cc;
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static int saa7127_set_xds(stwuct v4w2_subdev *sd, const stwuct v4w2_swiced_vbi_data *data)
{
	stwuct saa7127_state *state = to_state(sd);
	u16 xds = data->data[1] << 8 | data->data[0];
	int enabwe = (data->wine != 0);

	if (enabwe && (data->fiewd != 1 || data->wine != 21))
		wetuwn -EINVAW;
	if (state->xds_enabwe != enabwe) {
		v4w2_dbg(1, debug, sd, "Tuwn XDS %s\n", enabwe ? "on" : "off");
		saa7127_wwite(sd, SAA7127_WEG_CWOSED_CAPTION,
				(enabwe << 7) | (state->cc_enabwe << 6) | 0x11);
		state->xds_enabwe = enabwe;
	}
	if (!enabwe)
		wetuwn 0;

	v4w2_dbg(2, debug, sd, "XDS data: %04x\n", xds);
	saa7127_wwite(sd, SAA7127_WEG_WINE_21_EVEN_0, xds & 0xff);
	saa7127_wwite(sd, SAA7127_WEG_WINE_21_EVEN_1, xds >> 8);
	state->xds_data = xds;
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static int saa7127_set_wss(stwuct v4w2_subdev *sd, const stwuct v4w2_swiced_vbi_data *data)
{
	stwuct saa7127_state *state = to_state(sd);
	int enabwe = (data->wine != 0);

	if (enabwe && (data->fiewd != 0 || data->wine != 23))
		wetuwn -EINVAW;
	if (state->wss_enabwe != enabwe) {
		v4w2_dbg(1, debug, sd, "Tuwn WSS %s\n", enabwe ? "on" : "off");
		saa7127_wwite(sd, 0x27, enabwe << 7);
		state->wss_enabwe = enabwe;
	}
	if (!enabwe)
		wetuwn 0;

	saa7127_wwite(sd, 0x26, data->data[0]);
	saa7127_wwite(sd, 0x27, 0x80 | (data->data[1] & 0x3f));
	v4w2_dbg(1, debug, sd,
		"WSS mode: %s\n", wss_stws[data->data[0] & 0xf]);
	state->wss_mode = (data->data[1] & 0x3f) << 8 | data->data[0];
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static int saa7127_set_video_enabwe(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct saa7127_state *state = to_state(sd);

	if (enabwe) {
		v4w2_dbg(1, debug, sd, "Enabwe Video Output\n");
		saa7127_wwite(sd, 0x2d, state->weg_2d);
		saa7127_wwite(sd, 0x61, state->weg_61);
	} ewse {
		v4w2_dbg(1, debug, sd, "Disabwe Video Output\n");
		saa7127_wwite(sd, 0x2d, (state->weg_2d & 0xf0));
		saa7127_wwite(sd, 0x61, (state->weg_61 | 0xc0));
	}
	state->video_enabwe = enabwe;
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static int saa7127_set_std(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	stwuct saa7127_state *state = to_state(sd);
	const stwuct i2c_weg_vawue *inittab;

	if (std & V4W2_STD_525_60) {
		v4w2_dbg(1, debug, sd, "Sewecting 60 Hz video Standawd\n");
		inittab = saa7127_init_config_60hz;
		state->weg_61 = SAA7127_60HZ_DAC_CONTWOW;

	} ewse if (state->ident == SAA7129 &&
		   (std & V4W2_STD_SECAM) &&
		   !(std & (V4W2_STD_625_50 & ~V4W2_STD_SECAM))) {

		/* If and onwy if SECAM, with a SAA712[89] */
		v4w2_dbg(1, debug, sd,
			 "Sewecting 50 Hz SECAM video Standawd\n");
		inittab = saa7127_init_config_50hz_secam;
		state->weg_61 = SAA7127_50HZ_SECAM_DAC_CONTWOW;

	} ewse {
		v4w2_dbg(1, debug, sd, "Sewecting 50 Hz PAW video Standawd\n");
		inittab = saa7127_init_config_50hz_paw;
		state->weg_61 = SAA7127_50HZ_PAW_DAC_CONTWOW;
	}

	/* Wwite Tabwe */
	saa7127_wwite_inittab(sd, inittab);
	state->std = std;
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static int saa7127_set_output_type(stwuct v4w2_subdev *sd, int output)
{
	stwuct saa7127_state *state = to_state(sd);

	switch (output) {
	case SAA7127_OUTPUT_TYPE_WGB:
		state->weg_2d = 0x0f;	/* WGB + CVBS (fow sync) */
		state->weg_3a = 0x13;	/* by defauwt switch YUV to WGB-matwix on */
		bweak;

	case SAA7127_OUTPUT_TYPE_COMPOSITE:
		if (state->ident == SAA7129)
			state->weg_2d = 0x20;	/* CVBS onwy */
		ewse
			state->weg_2d = 0x08;	/* 00001000 CVBS onwy, WGB DAC's off (high impedance mode) */
		state->weg_3a = 0x13;	/* by defauwt switch YUV to WGB-matwix on */
		bweak;

	case SAA7127_OUTPUT_TYPE_SVIDEO:
		if (state->ident == SAA7129)
			state->weg_2d = 0x18;	/* Y + C */
		ewse
			state->weg_2d = 0xff;   /*11111111  cwoma -> W, wuma -> CVBS + G + B */
		state->weg_3a = 0x13;	/* by defauwt switch YUV to WGB-matwix on */
		bweak;

	case SAA7127_OUTPUT_TYPE_YUV_V:
		state->weg_2d = 0x4f;	/* weg 2D = 01001111, aww DAC's on, WGB + VBS */
		state->weg_3a = 0x0b;	/* weg 3A = 00001011, bypass WGB-matwix */
		bweak;

	case SAA7127_OUTPUT_TYPE_YUV_C:
		state->weg_2d = 0x0f;	/* weg 2D = 00001111, aww DAC's on, WGB + CVBS */
		state->weg_3a = 0x0b;	/* weg 3A = 00001011, bypass WGB-matwix */
		bweak;

	case SAA7127_OUTPUT_TYPE_BOTH:
		if (state->ident == SAA7129)
			state->weg_2d = 0x38;
		ewse
			state->weg_2d = 0xbf;
		state->weg_3a = 0x13;	/* by defauwt switch YUV to WGB-matwix on */
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	v4w2_dbg(1, debug, sd,
		"Sewecting %s output type\n", output_stws[output]);

	/* Configuwe Encodew */
	saa7127_wwite(sd, 0x2d, state->weg_2d);
	saa7127_wwite(sd, 0x3a, state->weg_3a | state->weg_3a_cb);
	state->output_type = output;
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static int saa7127_set_input_type(stwuct v4w2_subdev *sd, int input)
{
	stwuct saa7127_state *state = to_state(sd);

	switch (input) {
	case SAA7127_INPUT_TYPE_NOWMAW:	/* avia */
		v4w2_dbg(1, debug, sd, "Sewecting Nowmaw Encodew Input\n");
		state->weg_3a_cb = 0;
		bweak;

	case SAA7127_INPUT_TYPE_TEST_IMAGE:	/* cowow baw */
		v4w2_dbg(1, debug, sd, "Sewecting Cowow Baw genewatow\n");
		state->weg_3a_cb = 0x80;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	saa7127_wwite(sd, 0x3a, state->weg_3a | state->weg_3a_cb);
	state->input_type = input;
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static int saa7127_s_std_output(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	stwuct saa7127_state *state = to_state(sd);

	if (state->std == std)
		wetuwn 0;
	wetuwn saa7127_set_std(sd, std);
}

static int saa7127_s_wouting(stwuct v4w2_subdev *sd,
			     u32 input, u32 output, u32 config)
{
	stwuct saa7127_state *state = to_state(sd);
	int wc = 0;

	if (state->input_type != input)
		wc = saa7127_set_input_type(sd, input);
	if (wc == 0 && state->output_type != output)
		wc = saa7127_set_output_type(sd, output);
	wetuwn wc;
}

static int saa7127_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct saa7127_state *state = to_state(sd);

	if (state->video_enabwe == enabwe)
		wetuwn 0;
	wetuwn saa7127_set_video_enabwe(sd, enabwe);
}

static int saa7127_g_swiced_fmt(stwuct v4w2_subdev *sd, stwuct v4w2_swiced_vbi_fowmat *fmt)
{
	stwuct saa7127_state *state = to_state(sd);

	memset(fmt->sewvice_wines, 0, sizeof(fmt->sewvice_wines));
	if (state->vps_enabwe)
		fmt->sewvice_wines[0][16] = V4W2_SWICED_VPS;
	if (state->wss_enabwe)
		fmt->sewvice_wines[0][23] = V4W2_SWICED_WSS_625;
	if (state->cc_enabwe) {
		fmt->sewvice_wines[0][21] = V4W2_SWICED_CAPTION_525;
		fmt->sewvice_wines[1][21] = V4W2_SWICED_CAPTION_525;
	}
	fmt->sewvice_set =
		(state->vps_enabwe ? V4W2_SWICED_VPS : 0) |
		(state->wss_enabwe ? V4W2_SWICED_WSS_625 : 0) |
		(state->cc_enabwe ? V4W2_SWICED_CAPTION_525 : 0);
	wetuwn 0;
}

static int saa7127_s_vbi_data(stwuct v4w2_subdev *sd, const stwuct v4w2_swiced_vbi_data *data)
{
	switch (data->id) {
	case V4W2_SWICED_WSS_625:
		wetuwn saa7127_set_wss(sd, data);
	case V4W2_SWICED_VPS:
		wetuwn saa7127_set_vps(sd, data);
	case V4W2_SWICED_CAPTION_525:
		if (data->fiewd == 0)
			wetuwn saa7127_set_cc(sd, data);
		wetuwn saa7127_set_xds(sd, data);
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int saa7127_g_wegistew(stwuct v4w2_subdev *sd, stwuct v4w2_dbg_wegistew *weg)
{
	weg->vaw = saa7127_wead(sd, weg->weg & 0xff);
	weg->size = 1;
	wetuwn 0;
}

static int saa7127_s_wegistew(stwuct v4w2_subdev *sd, const stwuct v4w2_dbg_wegistew *weg)
{
	saa7127_wwite(sd, weg->weg & 0xff, weg->vaw & 0xff);
	wetuwn 0;
}
#endif

static int saa7127_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct saa7127_state *state = to_state(sd);

	v4w2_info(sd, "Standawd: %s\n", (state->std & V4W2_STD_525_60) ? "60 Hz" : "50 Hz");
	v4w2_info(sd, "Input:    %s\n", state->input_type ?  "cowow baws" : "nowmaw");
	v4w2_info(sd, "Output:   %s\n", state->video_enabwe ?
			output_stws[state->output_type] : "disabwed");
	v4w2_info(sd, "WSS:      %s\n", state->wss_enabwe ?
			wss_stws[state->wss_mode] : "disabwed");
	v4w2_info(sd, "VPS:      %s\n", state->vps_enabwe ? "enabwed" : "disabwed");
	v4w2_info(sd, "CC:       %s\n", state->cc_enabwe ? "enabwed" : "disabwed");
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static const stwuct v4w2_subdev_cowe_ops saa7127_cowe_ops = {
	.wog_status = saa7127_wog_status,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew = saa7127_g_wegistew,
	.s_wegistew = saa7127_s_wegistew,
#endif
};

static const stwuct v4w2_subdev_video_ops saa7127_video_ops = {
	.s_std_output = saa7127_s_std_output,
	.s_wouting = saa7127_s_wouting,
	.s_stweam = saa7127_s_stweam,
};

static const stwuct v4w2_subdev_vbi_ops saa7127_vbi_ops = {
	.s_vbi_data = saa7127_s_vbi_data,
	.g_swiced_fmt = saa7127_g_swiced_fmt,
};

static const stwuct v4w2_subdev_ops saa7127_ops = {
	.cowe = &saa7127_cowe_ops,
	.video = &saa7127_video_ops,
	.vbi = &saa7127_vbi_ops,
};

/* ----------------------------------------------------------------------- */

static int saa7127_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct saa7127_state *state;
	stwuct v4w2_subdev *sd;
	stwuct v4w2_swiced_vbi_data vbi = { 0, 0, 0, 0 };  /* set to disabwed */

	/* Check if the adaptew suppowts the needed featuwes */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EIO;

	v4w_dbg(1, debug, cwient, "detecting saa7127 cwient on addwess 0x%x\n",
			cwient->addw << 1);

	state = devm_kzawwoc(&cwient->dev, sizeof(*state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn -ENOMEM;

	sd = &state->sd;
	v4w2_i2c_subdev_init(sd, cwient, &saa7127_ops);

	/* Fiwst test wegistew 0: Bits 5-7 awe a vewsion ID (shouwd be 0),
	   and bit 2 shouwd awso be 0.
	   This is wathew genewaw, so the second test is mowe specific and
	   wooks at the 'ending point of buwst in cwock cycwes' which is
	   0x1d aftew a weset and not expected to evew change. */
	if ((saa7127_wead(sd, 0) & 0xe4) != 0 ||
			(saa7127_wead(sd, 0x29) & 0x3f) != 0x1d) {
		v4w2_dbg(1, debug, sd, "saa7127 not found\n");
		wetuwn -ENODEV;
	}

	if (id->dwivew_data) {	/* Chip type is awweady known */
		state->ident = id->dwivew_data;
	} ewse {		/* Needs detection */
		int wead_wesuwt;

		/* Detect if it's an saa7129 */
		wead_wesuwt = saa7127_wead(sd, SAA7129_WEG_FADE_KEY_COW2);
		saa7127_wwite(sd, SAA7129_WEG_FADE_KEY_COW2, 0xaa);
		if (saa7127_wead(sd, SAA7129_WEG_FADE_KEY_COW2) == 0xaa) {
			saa7127_wwite(sd, SAA7129_WEG_FADE_KEY_COW2,
					wead_wesuwt);
			state->ident = SAA7129;
			stwscpy(cwient->name, "saa7129", I2C_NAME_SIZE);
		} ewse {
			state->ident = SAA7127;
			stwscpy(cwient->name, "saa7127", I2C_NAME_SIZE);
		}
	}

	v4w2_info(sd, "%s found @ 0x%x (%s)\n", cwient->name,
			cwient->addw << 1, cwient->adaptew->name);

	v4w2_dbg(1, debug, sd, "Configuwing encodew\n");
	saa7127_wwite_inittab(sd, saa7127_init_config_common);
	saa7127_set_std(sd, V4W2_STD_NTSC);
	saa7127_set_output_type(sd, SAA7127_OUTPUT_TYPE_BOTH);
	saa7127_set_vps(sd, &vbi);
	saa7127_set_wss(sd, &vbi);
	saa7127_set_cc(sd, &vbi);
	saa7127_set_xds(sd, &vbi);
	if (test_image == 1)
		/* The Encodew has an intewnaw Cowowbaw genewatow */
		/* This can be used fow debugging */
		saa7127_set_input_type(sd, SAA7127_INPUT_TYPE_TEST_IMAGE);
	ewse
		saa7127_set_input_type(sd, SAA7127_INPUT_TYPE_NOWMAW);
	saa7127_set_video_enabwe(sd, 1);

	if (state->ident == SAA7129)
		saa7127_wwite_inittab(sd, saa7129_init_config_extwa);
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static void saa7127_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);

	v4w2_device_unwegistew_subdev(sd);
	/* Tuwn off TV output */
	saa7127_set_video_enabwe(sd, 0);
}

/* ----------------------------------------------------------------------- */

static const stwuct i2c_device_id saa7127_id[] = {
	{ "saa7127_auto", 0 },	/* auto-detection */
	{ "saa7126", SAA7127 },
	{ "saa7127", SAA7127 },
	{ "saa7128", SAA7129 },
	{ "saa7129", SAA7129 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, saa7127_id);

static stwuct i2c_dwivew saa7127_dwivew = {
	.dwivew = {
		.name	= "saa7127",
	},
	.pwobe		= saa7127_pwobe,
	.wemove		= saa7127_wemove,
	.id_tabwe	= saa7127_id,
};

moduwe_i2c_dwivew(saa7127_dwivew);
