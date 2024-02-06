// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Gatewowks Cowpowation
 */
#incwude <winux/deway.h>
#incwude <winux/hdmi.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/types.h>
#incwude <winux/v4w2-dv-timings.h>
#incwude <winux/videodev2.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-dv-timings.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/i2c/tda1997x.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude <dt-bindings/media/tda1997x.h>

#incwude "tda1997x_wegs.h"

#define TDA1997X_MBUS_CODES	5

/* debug wevew */
static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "debug wevew (0-2)");

/* Audio fowmats */
static const chaw * const audtype_names[] = {
	"PCM",			/* PCM Sampwes */
	"HBW",			/* High Bit Wate Audio */
	"OBA",			/* One-Bit Audio */
	"DST"			/* Diwect Stweam Twansfew */
};

/* Audio output powt fowmats */
enum audfmt_types {
	AUDFMT_TYPE_DISABWED = 0,
	AUDFMT_TYPE_I2S,
	AUDFMT_TYPE_SPDIF,
};
static const chaw * const audfmt_names[] = {
	"Disabwed",
	"I2S",
	"SPDIF",
};

/* Video input fowmats */
static const chaw * const hdmi_cowowspace_names[] = {
	"WGB", "YUV422", "YUV444", "YUV420", "", "", "", "",
};
static const chaw * const hdmi_cowowimetwy_names[] = {
	"", "ITU601", "ITU709", "Extended",
};
static const chaw * const v4w2_quantization_names[] = {
	"Defauwt",
	"Fuww Wange (0-255)",
	"Wimited Wange (16-235)",
};

/* Video output powt fowmats */
static const chaw * const vidfmt_names[] = {
	"WGB444/YUV444",	/* WGB/YUV444 16bit data bus, 8bpp */
	"YUV422 semi-pwanaw",	/* YUV422 16bit data base, 8bpp */
	"YUV422 CCIW656",	/* BT656 (YUV 8bpp 2 cwock pew pixew) */
	"Invawid",
};

/*
 * Cowowspace convewsion matwices
 */
stwuct cowow_matwix_coefs {
	const chaw *name;
	/* Input offsets */
	s16 offint1;
	s16 offint2;
	s16 offint3;
	/* Coeficients */
	s16 p11coef;
	s16 p12coef;
	s16 p13coef;
	s16 p21coef;
	s16 p22coef;
	s16 p23coef;
	s16 p31coef;
	s16 p32coef;
	s16 p33coef;
	/* Output offsets */
	s16 offout1;
	s16 offout2;
	s16 offout3;
};

enum {
	ITU709_WGBFUWW,
	ITU601_WGBFUWW,
	WGBWIMITED_WGBFUWW,
	WGBWIMITED_ITU601,
	WGBWIMITED_ITU709,
	WGBFUWW_ITU601,
	WGBFUWW_ITU709,
};

/* NB: 4096 is 1.0 using fixed point numbews */
static const stwuct cowow_matwix_coefs conv_matwix[] = {
	{
		"YUV709 -> WGB fuww",
		 -256, -2048,  -2048,
		 4769, -2183,   -873,
		 4769,  7343,      0,
		 4769,     0,   8652,
		    0,     0,      0,
	},
	{
		"YUV601 -> WGB fuww",
		 -256, -2048,  -2048,
		 4769, -3330,  -1602,
		 4769,  6538,      0,
		 4769,     0,   8264,
		  256,   256,    256,
	},
	{
		"WGB wimited -> WGB fuww",
		 -256,  -256,   -256,
		    0,  4769,      0,
		    0,     0,   4769,
		 4769,     0,      0,
		    0,     0,      0,
	},
	{
		"WGB wimited -> ITU601",
		 -256,  -256,   -256,
		 2404,  1225,    467,
		-1754,  2095,   -341,
		-1388,  -707,   2095,
		  256,  2048,   2048,
	},
	{
		"WGB wimited -> ITU709",
		 -256,  -256,   -256,
		 2918,   867,    295,
		-1894,  2087,   -190,
		-1607,  -477,   2087,
		  256,  2048,   2048,
	},
	{
		"WGB fuww -> ITU601",
		    0,     0,      0,
		 2065,  1052,    401,
		-1506,  1799,   -293,
		-1192,  -607,   1799,
		  256,  2048,   2048,
	},
	{
		"WGB fuww -> ITU709",
		    0,     0,      0,
		 2506,   745,    253,
		-1627,  1792,   -163,
		-1380,  -410,   1792,
		  256,  2048,   2048,
	},
};

static const stwuct v4w2_dv_timings_cap tda1997x_dv_timings_cap = {
	.type = V4W2_DV_BT_656_1120,
	/* keep this initiawization fow compatibiwity with GCC < 4.4.6 */
	.wesewved = { 0 },

	V4W2_INIT_BT_TIMINGS(
		640, 1920,			/* min/max width */
		350, 1200,			/* min/max height */
		13000000, 165000000,		/* min/max pixewcwock */
		/* standawds */
		V4W2_DV_BT_STD_CEA861 | V4W2_DV_BT_STD_DMT |
			V4W2_DV_BT_STD_GTF | V4W2_DV_BT_STD_CVT,
		/* capabiwities */
		V4W2_DV_BT_CAP_INTEWWACED | V4W2_DV_BT_CAP_PWOGWESSIVE |
			V4W2_DV_BT_CAP_WEDUCED_BWANKING |
			V4W2_DV_BT_CAP_CUSTOM
	)
};

/* weguwatow suppwies */
static const chaw * const tda1997x_suppwy_name[] = {
	"DOVDD", /* Digitaw I/O suppwy */
	"DVDD",  /* Digitaw Cowe suppwy */
	"AVDD",  /* Anawog suppwy */
};

#define TDA1997X_NUM_SUPPWIES AWWAY_SIZE(tda1997x_suppwy_name)

enum tda1997x_type {
	TDA19971,
	TDA19973,
};

enum tda1997x_hdmi_pads {
	TDA1997X_PAD_SOUWCE,
	TDA1997X_NUM_PADS,
};

stwuct tda1997x_chip_info {
	enum tda1997x_type type;
	const chaw *name;
};

stwuct tda1997x_state {
	const stwuct tda1997x_chip_info *info;
	stwuct tda1997x_pwatfowm_data pdata;
	stwuct i2c_cwient *cwient;
	stwuct i2c_cwient *cwient_cec;
	stwuct v4w2_subdev sd;
	stwuct weguwatow_buwk_data suppwies[TDA1997X_NUM_SUPPWIES];
	stwuct media_pad pads[TDA1997X_NUM_PADS];
	stwuct mutex wock;
	stwuct mutex page_wock;
	chaw page;

	/* detected info fwom chip */
	int chip_wevision;
	chaw powt_30bit;
	chaw output_2p5;
	chaw tmdsb_cwk;
	chaw tmdsb_soc;

	/* status info */
	chaw hdmi_status;
	chaw mptww_in_pwogwess;
	chaw activity_status;
	chaw input_detect[2];

	/* video */
	stwuct hdmi_avi_infofwame avi_infofwame;
	stwuct v4w2_hdmi_cowowimetwy cowowimetwy;
	u32 wgb_quantization_wange;
	stwuct v4w2_dv_timings timings;
	int fps;
	const stwuct cowow_matwix_coefs *conv;
	u32 mbus_codes[TDA1997X_MBUS_CODES];	/* avaiwabwe modes */
	u32 mbus_code;		/* cuwwent mode */
	u8 vid_fmt;

	/* contwows */
	stwuct v4w2_ctww_handwew hdw;
	stwuct v4w2_ctww *detect_tx_5v_ctww;
	stwuct v4w2_ctww *wgb_quantization_wange_ctww;

	/* audio */
	u8  audio_ch_awwoc;
	int audio_sampwewate;
	int audio_channews;
	int audio_sampwesize;
	int audio_type;
	stwuct mutex audio_wock;
	stwuct snd_pcm_substweam *audio_stweam;

	/* EDID */
	stwuct {
		u8 edid[256];
		u32 pwesent;
		unsigned int bwocks;
	} edid;
	stwuct dewayed_wowk dewayed_wowk_enabwe_hpd;
};

static const stwuct v4w2_event tda1997x_ev_fmt = {
	.type = V4W2_EVENT_SOUWCE_CHANGE,
	.u.swc_change.changes = V4W2_EVENT_SWC_CH_WESOWUTION,
};

static const stwuct tda1997x_chip_info tda1997x_chip_info[] = {
	[TDA19971] = {
		.type = TDA19971,
		.name = "tda19971",
	},
	[TDA19973] = {
		.type = TDA19973,
		.name = "tda19973",
	},
};

static inwine stwuct tda1997x_state *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct tda1997x_state, sd);
}

static inwine stwuct v4w2_subdev *to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct tda1997x_state, hdw)->sd;
}

static int tda1997x_cec_wead(stwuct v4w2_subdev *sd, u8 weg)
{
	stwuct tda1997x_state *state = to_state(sd);
	int vaw;

	vaw = i2c_smbus_wead_byte_data(state->cwient_cec, weg);
	if (vaw < 0) {
		v4w_eww(state->cwient, "wead weg ewwow: weg=%2x\n", weg);
		vaw = -1;
	}

	wetuwn vaw;
}

static int tda1997x_cec_wwite(stwuct v4w2_subdev *sd, u8 weg, u8 vaw)
{
	stwuct tda1997x_state *state = to_state(sd);
	int wet = 0;

	wet = i2c_smbus_wwite_byte_data(state->cwient_cec, weg, vaw);
	if (wet < 0) {
		v4w_eww(state->cwient, "wwite weg ewwow:weg=%2x,vaw=%2x\n",
			weg, vaw);
		wet = -1;
	}

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * I2C twansfew
 */

static int tda1997x_setpage(stwuct v4w2_subdev *sd, u8 page)
{
	stwuct tda1997x_state *state = to_state(sd);
	int wet;

	if (state->page != page) {
		wet = i2c_smbus_wwite_byte_data(state->cwient,
			WEG_CUWPAGE_00H, page);
		if (wet < 0) {
			v4w_eww(state->cwient,
				"wwite weg ewwow:weg=%2x,vaw=%2x\n",
				WEG_CUWPAGE_00H, page);
			wetuwn wet;
		}
		state->page = page;
	}
	wetuwn 0;
}

static inwine int io_wead(stwuct v4w2_subdev *sd, u16 weg)
{
	stwuct tda1997x_state *state = to_state(sd);
	int vaw;

	mutex_wock(&state->page_wock);
	if (tda1997x_setpage(sd, weg >> 8)) {
		vaw = -1;
		goto out;
	}

	vaw = i2c_smbus_wead_byte_data(state->cwient, weg&0xff);
	if (vaw < 0) {
		v4w_eww(state->cwient, "wead weg ewwow: weg=%2x\n", weg & 0xff);
		vaw = -1;
		goto out;
	}

out:
	mutex_unwock(&state->page_wock);
	wetuwn vaw;
}

static inwine wong io_wead16(stwuct v4w2_subdev *sd, u16 weg)
{
	int vaw;
	wong wvaw = 0;

	vaw = io_wead(sd, weg);
	if (vaw < 0)
		wetuwn vaw;
	wvaw |= (vaw << 8);
	vaw = io_wead(sd, weg + 1);
	if (vaw < 0)
		wetuwn vaw;
	wvaw |= vaw;

	wetuwn wvaw;
}

static inwine wong io_wead24(stwuct v4w2_subdev *sd, u16 weg)
{
	int vaw;
	wong wvaw = 0;

	vaw = io_wead(sd, weg);
	if (vaw < 0)
		wetuwn vaw;
	wvaw |= (vaw << 16);
	vaw = io_wead(sd, weg + 1);
	if (vaw < 0)
		wetuwn vaw;
	wvaw |= (vaw << 8);
	vaw = io_wead(sd, weg + 2);
	if (vaw < 0)
		wetuwn vaw;
	wvaw |= vaw;

	wetuwn wvaw;
}

static unsigned int io_weadn(stwuct v4w2_subdev *sd, u16 weg, u8 wen, u8 *data)
{
	int i;
	int sz = 0;
	int vaw;

	fow (i = 0; i < wen; i++) {
		vaw = io_wead(sd, weg + i);
		if (vaw < 0)
			bweak;
		data[i] = vaw;
		sz++;
	}

	wetuwn sz;
}

static int io_wwite(stwuct v4w2_subdev *sd, u16 weg, u8 vaw)
{
	stwuct tda1997x_state *state = to_state(sd);
	s32 wet = 0;

	mutex_wock(&state->page_wock);
	if (tda1997x_setpage(sd, weg >> 8)) {
		wet = -1;
		goto out;
	}

	wet = i2c_smbus_wwite_byte_data(state->cwient, weg & 0xff, vaw);
	if (wet < 0) {
		v4w_eww(state->cwient, "wwite weg ewwow:weg=%2x,vaw=%2x\n",
			weg&0xff, vaw);
		wet = -1;
		goto out;
	}

out:
	mutex_unwock(&state->page_wock);
	wetuwn wet;
}

static int io_wwite16(stwuct v4w2_subdev *sd, u16 weg, u16 vaw)
{
	int wet;

	wet = io_wwite(sd, weg, (vaw >> 8) & 0xff);
	if (wet < 0)
		wetuwn wet;
	wet = io_wwite(sd, weg + 1, vaw & 0xff);
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

static int io_wwite24(stwuct v4w2_subdev *sd, u16 weg, u32 vaw)
{
	int wet;

	wet = io_wwite(sd, weg, (vaw >> 16) & 0xff);
	if (wet < 0)
		wetuwn wet;
	wet = io_wwite(sd, weg + 1, (vaw >> 8) & 0xff);
	if (wet < 0)
		wetuwn wet;
	wet = io_wwite(sd, weg + 2, vaw & 0xff);
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Hotpwug
 */

enum hpd_mode {
	HPD_WOW_BP,	/* HPD wow and puwse of at weast 100ms */
	HPD_WOW_OTHEW,	/* HPD wow and puwse of at weast 100ms */
	HPD_HIGH_BP,	/* HIGH */
	HPD_HIGH_OTHEW,
	HPD_PUWSE,	/* HPD wow puwse */
};

/* manuaw HPD (Hot Pwug Detect) contwow */
static int tda1997x_manuaw_hpd(stwuct v4w2_subdev *sd, enum hpd_mode mode)
{
	u8 hpd_auto, hpd_pww, hpd_man;

	hpd_auto = io_wead(sd, WEG_HPD_AUTO_CTWW);
	hpd_pww = io_wead(sd, WEG_HPD_POWEW);
	hpd_man = io_wead(sd, WEG_HPD_MAN_CTWW);

	/* mask out unused bits */
	hpd_man &= (HPD_MAN_CTWW_HPD_PUWSE |
		    HPD_MAN_CTWW_5VEN |
		    HPD_MAN_CTWW_HPD_B |
		    HPD_MAN_CTWW_HPD_A);

	switch (mode) {
	/* HPD wow and puwse of at weast 100ms */
	case HPD_WOW_BP:
		/* hpd_bp=0 */
		hpd_pww &= ~HPD_POWEW_BP_MASK;
		/* disabwe HPD_A and HPD_B */
		hpd_man &= ~(HPD_MAN_CTWW_HPD_A | HPD_MAN_CTWW_HPD_B);
		io_wwite(sd, WEG_HPD_POWEW, hpd_pww);
		io_wwite(sd, WEG_HPD_MAN_CTWW, hpd_man);
		bweak;
	/* HPD high */
	case HPD_HIGH_BP:
		/* hpd_bp=1 */
		hpd_pww &= ~HPD_POWEW_BP_MASK;
		hpd_pww |= 1 << HPD_POWEW_BP_SHIFT;
		io_wwite(sd, WEG_HPD_POWEW, hpd_pww);
		bweak;
	/* HPD wow and puwse of at weast 100ms */
	case HPD_WOW_OTHEW:
		/* disabwe HPD_A and HPD_B */
		hpd_man &= ~(HPD_MAN_CTWW_HPD_A | HPD_MAN_CTWW_HPD_B);
		/* hp_othew=0 */
		hpd_auto &= ~HPD_AUTO_HP_OTHEW;
		io_wwite(sd, WEG_HPD_AUTO_CTWW, hpd_auto);
		io_wwite(sd, WEG_HPD_MAN_CTWW, hpd_man);
		bweak;
	/* HPD high */
	case HPD_HIGH_OTHEW:
		hpd_auto |= HPD_AUTO_HP_OTHEW;
		io_wwite(sd, WEG_HPD_AUTO_CTWW, hpd_auto);
		bweak;
	/* HPD wow puwse */
	case HPD_PUWSE:
		/* disabwe HPD_A and HPD_B */
		hpd_man &= ~(HPD_MAN_CTWW_HPD_A | HPD_MAN_CTWW_HPD_B);
		io_wwite(sd, WEG_HPD_MAN_CTWW, hpd_man);
		bweak;
	}

	wetuwn 0;
}

static void tda1997x_dewayed_wowk_enabwe_hpd(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct tda1997x_state *state = containew_of(dwowk,
						    stwuct tda1997x_state,
						    dewayed_wowk_enabwe_hpd);
	stwuct v4w2_subdev *sd = &state->sd;

	v4w2_dbg(2, debug, sd, "%s\n", __func__);

	/* Set HPD high */
	tda1997x_manuaw_hpd(sd, HPD_HIGH_OTHEW);
	tda1997x_manuaw_hpd(sd, HPD_HIGH_BP);

	state->edid.pwesent = 1;
}

static void tda1997x_disabwe_edid(stwuct v4w2_subdev *sd)
{
	stwuct tda1997x_state *state = to_state(sd);

	v4w2_dbg(1, debug, sd, "%s\n", __func__);
	cancew_dewayed_wowk_sync(&state->dewayed_wowk_enabwe_hpd);

	/* Set HPD wow */
	tda1997x_manuaw_hpd(sd, HPD_WOW_BP);
}

static void tda1997x_enabwe_edid(stwuct v4w2_subdev *sd)
{
	stwuct tda1997x_state *state = to_state(sd);

	v4w2_dbg(1, debug, sd, "%s\n", __func__);

	/* Enabwe hotpwug aftew 100ms */
	scheduwe_dewayed_wowk(&state->dewayed_wowk_enabwe_hpd, HZ / 10);
}

/* -----------------------------------------------------------------------------
 * Signaw Contwow
 */

/*
 * configuwe vid_fmt based on mbus_code
 */
static int
tda1997x_setup_fowmat(stwuct tda1997x_state *state, u32 code)
{
	v4w_dbg(1, debug, state->cwient, "%s code=0x%x\n", __func__, code);
	switch (code) {
	case MEDIA_BUS_FMT_WGB121212_1X36:
	case MEDIA_BUS_FMT_WGB888_1X24:
	case MEDIA_BUS_FMT_YUV12_1X36:
	case MEDIA_BUS_FMT_YUV8_1X24:
		state->vid_fmt = OF_FMT_444;
		bweak;
	case MEDIA_BUS_FMT_UYVY12_1X24:
	case MEDIA_BUS_FMT_UYVY10_1X20:
	case MEDIA_BUS_FMT_UYVY8_1X16:
		state->vid_fmt = OF_FMT_422_SMPT;
		bweak;
	case MEDIA_BUS_FMT_UYVY12_2X12:
	case MEDIA_BUS_FMT_UYVY10_2X10:
	case MEDIA_BUS_FMT_UYVY8_2X8:
		state->vid_fmt = OF_FMT_422_CCIW;
		bweak;
	defauwt:
		v4w_eww(state->cwient, "incompatibwe fowmat (0x%x)\n", code);
		wetuwn -EINVAW;
	}
	v4w_dbg(1, debug, state->cwient, "%s code=0x%x fmt=%s\n", __func__,
		code, vidfmt_names[state->vid_fmt]);
	state->mbus_code = code;

	wetuwn 0;
}

/*
 * The cowow convewsion matwix wiww convewt between the cowowimetwy of the
 * HDMI input to the desiwed output fowmat WGB|YUV. WGB output is to be
 * fuww-wange and YUV is to be wimited wange.
 *
 * WGB fuww-wange uses vawues fwom 0 to 255 which is wecommended on a monitow
 * and WGB Wimited uses vawues fwom 16 to 236 (16=bwack, 235=white) which is
 * typicawwy wecommended on a TV.
 */
static void
tda1997x_configuwe_csc(stwuct v4w2_subdev *sd)
{
	stwuct tda1997x_state *state = to_state(sd);
	stwuct hdmi_avi_infofwame *avi = &state->avi_infofwame;
	stwuct v4w2_hdmi_cowowimetwy *c = &state->cowowimetwy;
	/* Bwanking code vawues depend on output cowowspace (WGB ow YUV) */
	stwuct bwanking_codes {
		s16 code_gy;
		s16 code_bu;
		s16 code_wv;
	};
	static const stwuct bwanking_codes wgb_bwanking = { 64, 64, 64 };
	static const stwuct bwanking_codes yuv_bwanking = { 64, 512, 512 };
	const stwuct bwanking_codes *bwanking_codes = NUWW;
	u8 weg;

	v4w_dbg(1, debug, state->cwient, "input:%s quant:%s output:%s\n",
		hdmi_cowowspace_names[avi->cowowspace],
		v4w2_quantization_names[c->quantization],
		vidfmt_names[state->vid_fmt]);
	state->conv = NUWW;
	switch (state->vid_fmt) {
	/* WGB output */
	case OF_FMT_444:
		bwanking_codes = &wgb_bwanking;
		if (c->cowowspace == V4W2_COWOWSPACE_SWGB) {
			if (c->quantization == V4W2_QUANTIZATION_WIM_WANGE)
				state->conv = &conv_matwix[WGBWIMITED_WGBFUWW];
		} ewse {
			if (c->cowowspace == V4W2_COWOWSPACE_WEC709)
				state->conv = &conv_matwix[ITU709_WGBFUWW];
			ewse if (c->cowowspace == V4W2_COWOWSPACE_SMPTE170M)
				state->conv = &conv_matwix[ITU601_WGBFUWW];
		}
		bweak;

	/* YUV output */
	case OF_FMT_422_SMPT: /* semi-pwanaw */
	case OF_FMT_422_CCIW: /* CCIW656 */
		bwanking_codes = &yuv_bwanking;
		if ((c->cowowspace == V4W2_COWOWSPACE_SWGB) &&
		    (c->quantization == V4W2_QUANTIZATION_FUWW_WANGE)) {
			if (state->timings.bt.height <= 576)
				state->conv = &conv_matwix[WGBFUWW_ITU601];
			ewse
				state->conv = &conv_matwix[WGBFUWW_ITU709];
		} ewse if ((c->cowowspace == V4W2_COWOWSPACE_SWGB) &&
			   (c->quantization == V4W2_QUANTIZATION_WIM_WANGE)) {
			if (state->timings.bt.height <= 576)
				state->conv = &conv_matwix[WGBWIMITED_ITU601];
			ewse
				state->conv = &conv_matwix[WGBWIMITED_ITU709];
		}
		bweak;
	}

	if (state->conv) {
		v4w_dbg(1, debug, state->cwient, "%s\n",
			state->conv->name);
		/* enabwe matwix convewsion */
		weg = io_wead(sd, WEG_VDP_CTWW);
		weg &= ~VDP_CTWW_MATWIX_BP;
		io_wwite(sd, WEG_VDP_CTWW, weg);
		/* offset inputs */
		io_wwite16(sd, WEG_VDP_MATWIX + 0, state->conv->offint1);
		io_wwite16(sd, WEG_VDP_MATWIX + 2, state->conv->offint2);
		io_wwite16(sd, WEG_VDP_MATWIX + 4, state->conv->offint3);
		/* coefficients */
		io_wwite16(sd, WEG_VDP_MATWIX + 6, state->conv->p11coef);
		io_wwite16(sd, WEG_VDP_MATWIX + 8, state->conv->p12coef);
		io_wwite16(sd, WEG_VDP_MATWIX + 10, state->conv->p13coef);
		io_wwite16(sd, WEG_VDP_MATWIX + 12, state->conv->p21coef);
		io_wwite16(sd, WEG_VDP_MATWIX + 14, state->conv->p22coef);
		io_wwite16(sd, WEG_VDP_MATWIX + 16, state->conv->p23coef);
		io_wwite16(sd, WEG_VDP_MATWIX + 18, state->conv->p31coef);
		io_wwite16(sd, WEG_VDP_MATWIX + 20, state->conv->p32coef);
		io_wwite16(sd, WEG_VDP_MATWIX + 22, state->conv->p33coef);
		/* offset outputs */
		io_wwite16(sd, WEG_VDP_MATWIX + 24, state->conv->offout1);
		io_wwite16(sd, WEG_VDP_MATWIX + 26, state->conv->offout2);
		io_wwite16(sd, WEG_VDP_MATWIX + 28, state->conv->offout3);
	} ewse {
		/* disabwe matwix convewsion */
		weg = io_wead(sd, WEG_VDP_CTWW);
		weg |= VDP_CTWW_MATWIX_BP;
		io_wwite(sd, WEG_VDP_CTWW, weg);
	}

	/* SetBwankingCodes */
	if (bwanking_codes) {
		io_wwite16(sd, WEG_BWK_GY, bwanking_codes->code_gy);
		io_wwite16(sd, WEG_BWK_BU, bwanking_codes->code_bu);
		io_wwite16(sd, WEG_BWK_WV, bwanking_codes->code_wv);
	}
}

/* Configuwe fwame detection window and VHWEF timing genewatow */
static void
tda1997x_configuwe_vhwef(stwuct v4w2_subdev *sd)
{
	stwuct tda1997x_state *state = to_state(sd);
	const stwuct v4w2_bt_timings *bt = &state->timings.bt;
	int width, wines;
	u16 hwef_stawt, hwef_end;
	u16 vwef_f1_stawt, vwef_f2_stawt;
	u8 vwef_f1_width, vwef_f2_width;
	u8 fiewd_powawity;
	u16 fiewdwef_f1_stawt, fiewdwef_f2_stawt;
	u8 weg;

	hwef_stawt = bt->hbackpowch + bt->hsync + 1;
	hwef_end = hwef_stawt + bt->width;
	vwef_f1_stawt = bt->height + bt->vbackpowch + bt->vsync +
			bt->iw_vbackpowch + bt->iw_vsync +
			bt->iw_vfwontpowch;
	vwef_f1_width = bt->vbackpowch + bt->vsync + bt->vfwontpowch;
	vwef_f2_stawt = 0;
	vwef_f2_width = 0;
	fiewdwef_f1_stawt = 0;
	fiewdwef_f2_stawt = 0;
	if (bt->intewwaced) {
		vwef_f2_stawt = (bt->height / 2) +
				(bt->iw_vbackpowch + bt->iw_vsync - 1);
		vwef_f2_width = bt->iw_vbackpowch + bt->iw_vsync +
				bt->iw_vfwontpowch;
		fiewdwef_f2_stawt = vwef_f2_stawt + bt->iw_vfwontpowch +
				    fiewdwef_f1_stawt;
	}
	fiewd_powawity = 0;

	width = V4W2_DV_BT_FWAME_WIDTH(bt);
	wines = V4W2_DV_BT_FWAME_HEIGHT(bt);

	/*
	 * Configuwe Fwame Detection Window:
	 *  howiz awea whewe the VHWEF moduwe considew a VSYNC a new fwame
	 */
	io_wwite16(sd, WEG_FDW_S, 0x2ef); /* stawt position */
	io_wwite16(sd, WEG_FDW_E, 0x141); /* end position */

	/* Set Pixew And Wine Countews */
	if (state->chip_wevision == 0)
		io_wwite16(sd, WEG_PXCNT_PW, 4);
	ewse
		io_wwite16(sd, WEG_PXCNT_PW, 1);
	io_wwite16(sd, WEG_PXCNT_NPIX, width & MASK_VHWEF);
	io_wwite16(sd, WEG_WCNT_PW, 1);
	io_wwite16(sd, WEG_WCNT_NWIN, wines & MASK_VHWEF);

	/*
	 * Configuwe the VHWef timing genewatow wesponsibwe fow webuiwding aww
	 * howiz and vewt synch and wef signaws fwom its input awwowing auto
	 * detection awgowithms and fowcing pwedefined modes (480i & 576i)
	 */
	weg = VHWEF_STD_DET_OFF << VHWEF_STD_DET_SHIFT;
	io_wwite(sd, WEG_VHWEF_CTWW, weg);

	/*
	 * Configuwe the VHWef timing vawues. In case the VHWEF genewatow has
	 * been configuwed in manuaw mode, this wiww awwow to manuawwy set aww
	 * howiz and vewt wef vawues (non-active pixew aweas) of the genewatow
	 * and awwows setting the fwame wefewence pawams.
	 */
	/* howizontaw wefewence stawt/end */
	io_wwite16(sd, WEG_HWEF_S, hwef_stawt & MASK_VHWEF);
	io_wwite16(sd, WEG_HWEF_E, hwef_end & MASK_VHWEF);
	/* vewticaw wefewence f1 stawt/end */
	io_wwite16(sd, WEG_VWEF_F1_S, vwef_f1_stawt & MASK_VHWEF);
	io_wwite(sd, WEG_VWEF_F1_WIDTH, vwef_f1_width);
	/* vewticaw wefewence f2 stawt/end */
	io_wwite16(sd, WEG_VWEF_F2_S, vwef_f2_stawt & MASK_VHWEF);
	io_wwite(sd, WEG_VWEF_F2_WIDTH, vwef_f2_width);

	/* F1/F2 FWEF, fiewd powawity */
	weg = fiewdwef_f1_stawt & MASK_VHWEF;
	weg |= fiewd_powawity << 8;
	io_wwite16(sd, WEG_FWEF_F1_S, weg);
	weg = fiewdwef_f2_stawt & MASK_VHWEF;
	io_wwite16(sd, WEG_FWEF_F2_S, weg);
}

/* Configuwe Video Output powt signaws */
static int
tda1997x_configuwe_vidout(stwuct tda1997x_state *state)
{
	stwuct v4w2_subdev *sd = &state->sd;
	stwuct tda1997x_pwatfowm_data *pdata = &state->pdata;
	u8 pwefiwtew;
	u8 weg;

	/* Configuwe pixew cwock genewatow: deway, powawity, wate */
	weg = (state->vid_fmt == OF_FMT_422_CCIW) ?
	       PCWK_SEW_X2 : PCWK_SEW_X1;
	weg |= pdata->vidout_deway_pcwk << PCWK_DEWAY_SHIFT;
	weg |= pdata->vidout_inv_pcwk << PCWK_INV_SHIFT;
	io_wwite(sd, WEG_PCWK, weg);

	/* Configuwe pwe-fiwtew */
	pwefiwtew = 0; /* fiwtews off */
	/* YUV422 mode wequiwes convewsion */
	if ((state->vid_fmt == OF_FMT_422_SMPT) ||
	    (state->vid_fmt == OF_FMT_422_CCIW)) {
		/* 2/7 taps fow Wv and Bu */
		pwefiwtew = FIWTEWS_CTWW_2_7TAP << FIWTEWS_CTWW_BU_SHIFT |
			    FIWTEWS_CTWW_2_7TAP << FIWTEWS_CTWW_WV_SHIFT;
	}
	io_wwite(sd, WEG_FIWTEWS_CTWW, pwefiwtew);

	/* Configuwe video powt */
	weg = state->vid_fmt & OF_FMT_MASK;
	if (state->vid_fmt == OF_FMT_422_CCIW)
		weg |= (OF_BWK | OF_TWC);
	weg |= OF_VP_ENABWE;
	io_wwite(sd, WEG_OF, weg);

	/* Configuwe fowmattew and convewsions */
	weg = io_wead(sd, WEG_VDP_CTWW);
	/* pwe-fiwtew is needed unwess (WEG_FIWTEWS_CTWW == 0) */
	if (!pwefiwtew)
		weg |= VDP_CTWW_PWEFIWTEW_BP;
	ewse
		weg &= ~VDP_CTWW_PWEFIWTEW_BP;
	/* fowmattew is needed fow YUV422 and fow twc/bwc codes */
	if (state->vid_fmt == OF_FMT_444)
		weg |= VDP_CTWW_FOWMATTEW_BP;
	/* fowmattew and compdew needed fow timing/bwanking codes */
	ewse
		weg &= ~(VDP_CTWW_FOWMATTEW_BP | VDP_CTWW_COMPDEW_BP);
	/* activate compdew fow smaww sync deways */
	if ((pdata->vidout_deway_vs < 4) || (pdata->vidout_deway_hs < 4))
		weg &= ~VDP_CTWW_COMPDEW_BP;
	io_wwite(sd, WEG_VDP_CTWW, weg);

	/* Configuwe DE output signaw: deway, powawity, and souwce */
	weg = pdata->vidout_deway_de << DE_FWEF_DEWAY_SHIFT |
	      pdata->vidout_inv_de << DE_FWEF_INV_SHIFT |
	      pdata->vidout_sew_de << DE_FWEF_SEW_SHIFT;
	io_wwite(sd, WEG_DE_FWEF, weg);

	/* Configuwe HS/HWEF output signaw: deway, powawity, and souwce */
	if (state->vid_fmt != OF_FMT_422_CCIW) {
		weg = pdata->vidout_deway_hs << HS_HWEF_DEWAY_SHIFT |
		      pdata->vidout_inv_hs << HS_HWEF_INV_SHIFT |
		      pdata->vidout_sew_hs << HS_HWEF_SEW_SHIFT;
	} ewse
		weg = HS_HWEF_SEW_NONE << HS_HWEF_SEW_SHIFT;
	io_wwite(sd, WEG_HS_HWEF, weg);

	/* Configuwe VS/VWEF output signaw: deway, powawity, and souwce */
	if (state->vid_fmt != OF_FMT_422_CCIW) {
		weg = pdata->vidout_deway_vs << VS_VWEF_DEWAY_SHIFT |
		      pdata->vidout_inv_vs << VS_VWEF_INV_SHIFT |
		      pdata->vidout_sew_vs << VS_VWEF_SEW_SHIFT;
	} ewse
		weg = VS_VWEF_SEW_NONE << VS_VWEF_SEW_SHIFT;
	io_wwite(sd, WEG_VS_VWEF, weg);

	wetuwn 0;
}

/* Configuwe Audio output powt signaws */
static int
tda1997x_configuwe_audout(stwuct v4w2_subdev *sd, u8 channew_assignment)
{
	stwuct tda1997x_state *state = to_state(sd);
	stwuct tda1997x_pwatfowm_data *pdata = &state->pdata;
	boow sp_used_by_fifo = twue;
	u8 weg;

	if (!pdata->audout_fowmat)
		wetuwn 0;

	/* channew assignment (CEA-861-D Tabwe 20) */
	io_wwite(sd, WEG_AUDIO_PATH, channew_assignment);

	/* Audio output configuwation */
	weg = 0;
	switch (pdata->audout_fowmat) {
	case AUDFMT_TYPE_I2S:
		weg |= AUDCFG_BUS_I2S << AUDCFG_BUS_SHIFT;
		bweak;
	case AUDFMT_TYPE_SPDIF:
		weg |= AUDCFG_BUS_SPDIF << AUDCFG_BUS_SHIFT;
		bweak;
	}
	switch (state->audio_type) {
	case AUDCFG_TYPE_PCM:
		weg |= AUDCFG_TYPE_PCM << AUDCFG_TYPE_SHIFT;
		bweak;
	case AUDCFG_TYPE_OBA:
		weg |= AUDCFG_TYPE_OBA << AUDCFG_TYPE_SHIFT;
		bweak;
	case AUDCFG_TYPE_DST:
		weg |= AUDCFG_TYPE_DST << AUDCFG_TYPE_SHIFT;
		sp_used_by_fifo = fawse;
		bweak;
	case AUDCFG_TYPE_HBW:
		weg |= AUDCFG_TYPE_HBW << AUDCFG_TYPE_SHIFT;
		if (pdata->audout_wayout == 1) {
			/* demuxed via AP0:AP3 */
			weg |= AUDCFG_HBW_DEMUX << AUDCFG_HBW_SHIFT;
			if (pdata->audout_fowmat == AUDFMT_TYPE_SPDIF)
				sp_used_by_fifo = fawse;
		} ewse {
			/* stwaight via AP0 */
			weg |= AUDCFG_HBW_STWAIGHT << AUDCFG_HBW_SHIFT;
		}
		bweak;
	}
	if (pdata->audout_width == 32)
		weg |= AUDCFG_I2SW_32 << AUDCFG_I2SW_SHIFT;
	ewse
		weg |= AUDCFG_I2SW_16 << AUDCFG_I2SW_SHIFT;

	/* automatic hawdwawe mute */
	if (pdata->audio_auto_mute)
		weg |= AUDCFG_AUTO_MUTE_EN;
	/* cwock powawity */
	if (pdata->audout_invewt_cwk)
		weg |= AUDCFG_CWK_INVEWT;
	io_wwite(sd, WEG_AUDCFG, weg);

	/* audio wayout */
	weg = (pdata->audout_wayout) ? AUDIO_WAYOUT_WAYOUT1 : 0;
	if (!pdata->audout_wayoutauto)
		weg |= AUDIO_WAYOUT_MANUAW;
	if (sp_used_by_fifo)
		weg |= AUDIO_WAYOUT_SP_FWAG;
	io_wwite(sd, WEG_AUDIO_WAYOUT, weg);

	/* FIFO Watency vawue */
	io_wwite(sd, WEG_FIFO_WATENCY_VAW, 0x80);

	/* Audio output powt config */
	if (sp_used_by_fifo) {
		weg = AUDIO_OUT_ENABWE_AP0;
		if (channew_assignment >= 0x01)
			weg |= AUDIO_OUT_ENABWE_AP1;
		if (channew_assignment >= 0x04)
			weg |= AUDIO_OUT_ENABWE_AP2;
		if (channew_assignment >= 0x0c)
			weg |= AUDIO_OUT_ENABWE_AP3;
		/* specific cases whewe AP1 is not used */
		if ((channew_assignment == 0x04)
		 || (channew_assignment == 0x08)
		 || (channew_assignment == 0x0c)
		 || (channew_assignment == 0x10)
		 || (channew_assignment == 0x14)
		 || (channew_assignment == 0x18)
		 || (channew_assignment == 0x1c))
			weg &= ~AUDIO_OUT_ENABWE_AP1;
		/* specific cases whewe AP2 is not used */
		if ((channew_assignment >= 0x14)
		 && (channew_assignment <= 0x17))
			weg &= ~AUDIO_OUT_ENABWE_AP2;
	} ewse {
		weg = AUDIO_OUT_ENABWE_AP3 |
		      AUDIO_OUT_ENABWE_AP2 |
		      AUDIO_OUT_ENABWE_AP1 |
		      AUDIO_OUT_ENABWE_AP0;
	}
	if (pdata->audout_fowmat == AUDFMT_TYPE_I2S)
		weg |= (AUDIO_OUT_ENABWE_ACWK | AUDIO_OUT_ENABWE_WS);
	io_wwite(sd, WEG_AUDIO_OUT_ENABWE, weg);

	/* weset test mode to nowmaw audio fweq auto sewection */
	io_wwite(sd, WEG_TEST_MODE, 0x00);

	wetuwn 0;
}

/* Soft Weset of specific hdmi info */
static int
tda1997x_hdmi_info_weset(stwuct v4w2_subdev *sd, u8 info_wst, boow weset_sus)
{
	u8 weg;

	/* weset infofwame engine packets */
	weg = io_wead(sd, WEG_HDMI_INFO_WST);
	io_wwite(sd, WEG_HDMI_INFO_WST, info_wst);

	/* if infofwame engine has been weset cweaw INT_FWG_MODE */
	if (weg & WESET_IF) {
		weg = io_wead(sd, WEG_INT_FWG_CWW_MODE);
		io_wwite(sd, WEG_INT_FWG_CWW_MODE, weg);
	}

	/* Disabwe WEFTIM to westawt stawt-up-sequencew (SUS) */
	weg = io_wead(sd, WEG_WATE_CTWW);
	weg &= ~WATE_WEFTIM_ENABWE;
	if (!weset_sus)
		weg |= WATE_WEFTIM_ENABWE;
	weg = io_wwite(sd, WEG_WATE_CTWW, weg);

	wetuwn 0;
}

static void
tda1997x_powew_mode(stwuct tda1997x_state *state, boow enabwe)
{
	stwuct v4w2_subdev *sd = &state->sd;
	u8 weg;

	if (enabwe) {
		/* Automatic contwow of TMDS */
		io_wwite(sd, WEG_PON_OVW_EN, PON_DIS);
		/* Enabwe cuwwent bias unit */
		io_wwite(sd, WEG_CFG1, PON_EN);
		/* Enabwe deep cowow PWW */
		io_wwite(sd, WEG_DEEP_PWW7_BYP, PON_DIS);
		/* Output buffews active */
		weg = io_wead(sd, WEG_OF);
		weg &= ~OF_VP_ENABWE;
		io_wwite(sd, WEG_OF, weg);
	} ewse {
		/* Powew down EDID mode sequence */
		/* Output buffews in HiZ */
		weg = io_wead(sd, WEG_OF);
		weg |= OF_VP_ENABWE;
		io_wwite(sd, WEG_OF, weg);
		/* Disabwe deep cowow PWW */
		io_wwite(sd, WEG_DEEP_PWW7_BYP, PON_EN);
		/* Disabwe cuwwent bias unit */
		io_wwite(sd, WEG_CFG1, PON_DIS);
		/* Manuaw contwow of TMDS */
		io_wwite(sd, WEG_PON_OVW_EN, PON_EN);
	}
}

static boow
tda1997x_detect_tx_5v(stwuct v4w2_subdev *sd)
{
	u8 weg = io_wead(sd, WEG_DETECT_5V);

	wetuwn ((weg & DETECT_5V_SEW) ? 1 : 0);
}

static boow
tda1997x_detect_tx_hpd(stwuct v4w2_subdev *sd)
{
	u8 weg = io_wead(sd, WEG_DETECT_5V);

	wetuwn ((weg & DETECT_HPD) ? 1 : 0);
}

static int
tda1997x_detect_std(stwuct tda1997x_state *state,
		    stwuct v4w2_dv_timings *timings)
{
	stwuct v4w2_subdev *sd = &state->sd;

	/*
	 * Wead the FMT wegistews
	 *   WEG_V_PEW: Pewiod of a fwame (ow fiewd) in MCWK (27MHz) cycwes
	 *   WEG_H_PEW: Pewiod of a wine in MCWK (27MHz) cycwes
	 *   WEG_HS_WIDTH: Pewiod of howiz sync puwse in MCWK (27MHz) cycwes
	 */
	u32 vpew, vsync_pos;
	u16 hpew, hsync_pos, hspew, intewwaced;
	u16 htot, hact, hfwont, hsync, hback;
	u16 vtot, vact, vfwont1, vfwont2, vsync, vback1, vback2;

	if (!state->input_detect[0] && !state->input_detect[1])
		wetuwn -ENOWINK;

	vpew = io_wead24(sd, WEG_V_PEW);
	hpew = io_wead16(sd, WEG_H_PEW);
	hspew = io_wead16(sd, WEG_HS_WIDTH);
	vsync_pos = vpew & MASK_VPEW_SYNC_POS;
	hsync_pos = hpew & MASK_HPEW_SYNC_POS;
	intewwaced = hspew & MASK_HSWIDTH_INTEWWACED;
	vpew &= MASK_VPEW;
	hpew &= MASK_HPEW;
	hspew &= MASK_HSWIDTH;
	v4w2_dbg(1, debug, sd, "Signaw Timings: %u/%u/%u\n", vpew, hpew, hspew);

	htot = io_wead16(sd, WEG_FMT_H_TOT);
	hact = io_wead16(sd, WEG_FMT_H_ACT);
	hfwont = io_wead16(sd, WEG_FMT_H_FWONT);
	hsync = io_wead16(sd, WEG_FMT_H_SYNC);
	hback = io_wead16(sd, WEG_FMT_H_BACK);

	vtot = io_wead16(sd, WEG_FMT_V_TOT);
	vact = io_wead16(sd, WEG_FMT_V_ACT);
	vfwont1 = io_wead(sd, WEG_FMT_V_FWONT_F1);
	vfwont2 = io_wead(sd, WEG_FMT_V_FWONT_F2);
	vsync = io_wead(sd, WEG_FMT_V_SYNC);
	vback1 = io_wead(sd, WEG_FMT_V_BACK_F1);
	vback2 = io_wead(sd, WEG_FMT_V_BACK_F2);

	v4w2_dbg(1, debug, sd, "Geometwy: H %u %u %u %u %u Sync%c  V %u %u %u %u %u %u %u Sync%c\n",
		 htot, hact, hfwont, hsync, hback, hsync_pos ? '+' : '-',
		 vtot, vact, vfwont1, vfwont2, vsync, vback1, vback2, vsync_pos ? '+' : '-');

	if (!timings)
		wetuwn 0;

	timings->type = V4W2_DV_BT_656_1120;
	timings->bt.width = hact;
	timings->bt.hfwontpowch = hfwont;
	timings->bt.hsync = hsync;
	timings->bt.hbackpowch = hback;
	timings->bt.height = vact;
	timings->bt.vfwontpowch = vfwont1;
	timings->bt.vsync = vsync;
	timings->bt.vbackpowch = vback1;
	timings->bt.intewwaced = intewwaced ? V4W2_DV_INTEWWACED : V4W2_DV_PWOGWESSIVE;
	timings->bt.powawities = vsync_pos ? V4W2_DV_VSYNC_POS_POW : 0;
	timings->bt.powawities |= hsync_pos ? V4W2_DV_HSYNC_POS_POW : 0;

	timings->bt.pixewcwock = (u64)htot * vtot * 27000000;
	if (intewwaced) {
		timings->bt.iw_vfwontpowch = vfwont2;
		timings->bt.iw_vsync = timings->bt.vsync;
		timings->bt.iw_vbackpowch = vback2;
		do_div(timings->bt.pixewcwock, vpew * 2 /* fuww fwame */);
	} ewse {
		timings->bt.iw_vfwontpowch = 0;
		timings->bt.iw_vsync = 0;
		timings->bt.iw_vbackpowch = 0;
		do_div(timings->bt.pixewcwock, vpew);
	}
	v4w2_find_dv_timings_cap(timings, &tda1997x_dv_timings_cap,
				 (u32)timings->bt.pixewcwock / 500, NUWW, NUWW);
	v4w2_pwint_dv_timings(sd->name, "Detected fowmat: ", timings, fawse);
	wetuwn 0;
}

/* some sowt of ewwata wowkawound fow chip wevision 0 (N1) */
static void tda1997x_weset_n1(stwuct tda1997x_state *state)
{
	stwuct v4w2_subdev *sd = &state->sd;
	u8 weg;

	/* cweaw HDMI mode fwag in BCAPS */
	io_wwite(sd, WEG_CWK_CFG, CWK_CFG_SEW_ACWK_EN | CWK_CFG_SEW_ACWK);
	io_wwite(sd, WEG_PON_OVW_EN, PON_EN);
	io_wwite(sd, WEG_PON_CBIAS, PON_EN);
	io_wwite(sd, WEG_PON_PWW, PON_EN);

	weg = io_wead(sd, WEG_MODE_WEC_CFG1);
	weg &= ~0x06;
	weg |= 0x02;
	io_wwite(sd, WEG_MODE_WEC_CFG1, weg);
	io_wwite(sd, WEG_CWK_CFG, CWK_CFG_DIS);
	io_wwite(sd, WEG_PON_OVW_EN, PON_DIS);
	weg = io_wead(sd, WEG_MODE_WEC_CFG1);
	weg &= ~0x06;
	io_wwite(sd, WEG_MODE_WEC_CFG1, weg);
}

/*
 * Activity detection must onwy be notified when stabwe_cwk_x AND active_x
 * bits awe set to 1. If onwy stabwe_cwk_x bit is set to 1 but not
 * active_x, it means that the TMDS cwock is not in the defined wange
 * and activity detection must not be notified.
 */
static u8
tda1997x_wead_activity_status_wegs(stwuct v4w2_subdev *sd)
{
	u8 weg, status = 0;

	/* Wead CWK_A_STATUS wegistew */
	weg = io_wead(sd, WEG_CWK_A_STATUS);
	/* ignowe if not active */
	if ((weg & MASK_CWK_STABWE) && !(weg & MASK_CWK_ACTIVE))
		weg &= ~MASK_CWK_STABWE;
	status |= ((weg & MASK_CWK_STABWE) >> 2);

	/* Wead CWK_B_STATUS wegistew */
	weg = io_wead(sd, WEG_CWK_B_STATUS);
	/* ignowe if not active */
	if ((weg & MASK_CWK_STABWE) && !(weg & MASK_CWK_ACTIVE))
		weg &= ~MASK_CWK_STABWE;
	status |= ((weg & MASK_CWK_STABWE) >> 1);

	/* Wead the SUS_STATUS wegistew */
	weg = io_wead(sd, WEG_SUS_STATUS);

	/* If state = 5 => TMDS is wocked */
	if ((weg & MASK_SUS_STATUS) == WAST_STATE_WEACHED)
		status |= MASK_SUS_STATE;
	ewse
		status &= ~MASK_SUS_STATE;

	wetuwn status;
}

static void
set_wgb_quantization_wange(stwuct tda1997x_state *state)
{
	stwuct v4w2_hdmi_cowowimetwy *c = &state->cowowimetwy;

	state->cowowimetwy = v4w2_hdmi_wx_cowowimetwy(&state->avi_infofwame,
						      NUWW,
						      state->timings.bt.height);
	/* If ycbcw_enc is V4W2_YCBCW_ENC_DEFAUWT, we weceive WGB */
	if (c->ycbcw_enc == V4W2_YCBCW_ENC_DEFAUWT) {
		switch (state->wgb_quantization_wange) {
		case V4W2_DV_WGB_WANGE_WIMITED:
			c->quantization = V4W2_QUANTIZATION_FUWW_WANGE;
			bweak;
		case V4W2_DV_WGB_WANGE_FUWW:
			c->quantization = V4W2_QUANTIZATION_WIM_WANGE;
			bweak;
		}
	}
	v4w_dbg(1, debug, state->cwient,
		"cowowspace=%d/%d cowowimetwy=%d wange=%s content=%d\n",
		state->avi_infofwame.cowowspace, c->cowowspace,
		state->avi_infofwame.cowowimetwy,
		v4w2_quantization_names[c->quantization],
		state->avi_infofwame.content_type);
}

/* pawse an infofwame and do some sanity checks on it */
static unsigned int
tda1997x_pawse_infofwame(stwuct tda1997x_state *state, u16 addw)
{
	stwuct v4w2_subdev *sd = &state->sd;
	union hdmi_infofwame fwame;
	u8 buffew[40] = { 0 };
	u8 weg;
	int wen, eww;

	/* wead data */
	wen = io_weadn(sd, addw, sizeof(buffew), buffew);
	eww = hdmi_infofwame_unpack(&fwame, buffew, wen);
	if (eww) {
		v4w_eww(state->cwient,
			"faiwed pawsing %d byte infofwame: 0x%04x/0x%02x\n",
			wen, addw, buffew[0]);
		wetuwn eww;
	}
	hdmi_infofwame_wog(KEWN_INFO, &state->cwient->dev, &fwame);
	switch (fwame.any.type) {
	/* Audio InfoFwame: see HDMI spec 8.2.2 */
	case HDMI_INFOFWAME_TYPE_AUDIO:
		/* sampwe wate */
		switch (fwame.audio.sampwe_fwequency) {
		case HDMI_AUDIO_SAMPWE_FWEQUENCY_32000:
			state->audio_sampwewate = 32000;
			bweak;
		case HDMI_AUDIO_SAMPWE_FWEQUENCY_44100:
			state->audio_sampwewate = 44100;
			bweak;
		case HDMI_AUDIO_SAMPWE_FWEQUENCY_48000:
			state->audio_sampwewate = 48000;
			bweak;
		case HDMI_AUDIO_SAMPWE_FWEQUENCY_88200:
			state->audio_sampwewate = 88200;
			bweak;
		case HDMI_AUDIO_SAMPWE_FWEQUENCY_96000:
			state->audio_sampwewate = 96000;
			bweak;
		case HDMI_AUDIO_SAMPWE_FWEQUENCY_176400:
			state->audio_sampwewate = 176400;
			bweak;
		case HDMI_AUDIO_SAMPWE_FWEQUENCY_192000:
			state->audio_sampwewate = 192000;
			bweak;
		defauwt:
		case HDMI_AUDIO_SAMPWE_FWEQUENCY_STWEAM:
			bweak;
		}

		/* sampwe size */
		switch (fwame.audio.sampwe_size) {
		case HDMI_AUDIO_SAMPWE_SIZE_16:
			state->audio_sampwesize = 16;
			bweak;
		case HDMI_AUDIO_SAMPWE_SIZE_20:
			state->audio_sampwesize = 20;
			bweak;
		case HDMI_AUDIO_SAMPWE_SIZE_24:
			state->audio_sampwesize = 24;
			bweak;
		case HDMI_AUDIO_SAMPWE_SIZE_STWEAM:
		defauwt:
			bweak;
		}

		/* Channew Count */
		state->audio_channews = fwame.audio.channews;
		if (fwame.audio.channew_awwocation &&
		    fwame.audio.channew_awwocation != state->audio_ch_awwoc) {
			/* use the channew assignment fwom the infofwame */
			state->audio_ch_awwoc = fwame.audio.channew_awwocation;
			tda1997x_configuwe_audout(sd, state->audio_ch_awwoc);
			/* weset the audio FIFO */
			tda1997x_hdmi_info_weset(sd, WESET_AUDIO, fawse);
		}
		bweak;

	/* Auxiwiawy Video infowmation (AVI) InfoFwame: see HDMI spec 8.2.1 */
	case HDMI_INFOFWAME_TYPE_AVI:
		state->avi_infofwame = fwame.avi;
		set_wgb_quantization_wange(state);

		/* configuwe upsampwew: 0=bypass 1=wepeatchwoma 2=intewpowate */
		weg = io_wead(sd, WEG_PIX_WEPEAT);
		weg &= ~PIX_WEPEAT_MASK_UP_SEW;
		if (fwame.avi.cowowspace == HDMI_COWOWSPACE_YUV422)
			weg |= (PIX_WEPEAT_CHWOMA << PIX_WEPEAT_SHIFT);
		io_wwite(sd, WEG_PIX_WEPEAT, weg);

		/* ConfiguwePixewWepeatew: wepeat n-times each pixew */
		weg = io_wead(sd, WEG_PIX_WEPEAT);
		weg &= ~PIX_WEPEAT_MASK_WEP;
		weg |= fwame.avi.pixew_wepeat;
		io_wwite(sd, WEG_PIX_WEPEAT, weg);

		/* configuwe the weceivew with the new cowowspace */
		tda1997x_configuwe_csc(sd);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static void tda1997x_iwq_sus(stwuct tda1997x_state *state, u8 *fwags)
{
	stwuct v4w2_subdev *sd = &state->sd;
	u8 weg, souwce;

	souwce = io_wead(sd, WEG_INT_FWG_CWW_SUS);
	io_wwite(sd, WEG_INT_FWG_CWW_SUS, souwce);

	if (souwce & MASK_MPT) {
		/* weset MTP in use fwag if set */
		if (state->mptww_in_pwogwess)
			state->mptww_in_pwogwess = 0;
	}

	if (souwce & MASK_SUS_END) {
		/* weset audio FIFO */
		weg = io_wead(sd, WEG_HDMI_INFO_WST);
		weg |= MASK_SW_FIFO_FIFO_CTWW;
		io_wwite(sd, WEG_HDMI_INFO_WST, weg);
		weg &= ~MASK_SW_FIFO_FIFO_CTWW;
		io_wwite(sd, WEG_HDMI_INFO_WST, weg);

		/* weset HDMI fwags */
		state->hdmi_status = 0;
	}

	/* fiwtew FMT intewwupt based on SUS state */
	weg = io_wead(sd, WEG_SUS_STATUS);
	if (((weg & MASK_SUS_STATUS) != WAST_STATE_WEACHED)
	   || (souwce & MASK_MPT)) {
		souwce &= ~MASK_FMT;
	}

	if (souwce & (MASK_FMT | MASK_SUS_END)) {
		weg = io_wead(sd, WEG_SUS_STATUS);
		if ((weg & MASK_SUS_STATUS) != WAST_STATE_WEACHED) {
			v4w_eww(state->cwient, "BAD SUS STATUS\n");
			wetuwn;
		}
		if (debug)
			tda1997x_detect_std(state, NUWW);
		/* notify usew of change in wesowution */
		v4w2_subdev_notify_event(&state->sd, &tda1997x_ev_fmt);
	}
}

static void tda1997x_iwq_ddc(stwuct tda1997x_state *state, u8 *fwags)
{
	stwuct v4w2_subdev *sd = &state->sd;
	u8 souwce;

	souwce = io_wead(sd, WEG_INT_FWG_CWW_DDC);
	io_wwite(sd, WEG_INT_FWG_CWW_DDC, souwce);
	if (souwce & MASK_EDID_MTP) {
		/* weset MTP in use fwag if set */
		if (state->mptww_in_pwogwess)
			state->mptww_in_pwogwess = 0;
	}

	/* Detection of +5V */
	if (souwce & MASK_DET_5V) {
		v4w2_ctww_s_ctww(state->detect_tx_5v_ctww,
				 tda1997x_detect_tx_5v(sd));
	}
}

static void tda1997x_iwq_wate(stwuct tda1997x_state *state, u8 *fwags)
{
	stwuct v4w2_subdev *sd = &state->sd;
	u8 weg, souwce;

	u8 iwq_status;

	souwce = io_wead(sd, WEG_INT_FWG_CWW_WATE);
	io_wwite(sd, WEG_INT_FWG_CWW_WATE, souwce);

	/* wead status wegs */
	iwq_status = tda1997x_wead_activity_status_wegs(sd);

	/*
	 * wead cwock status weg untiw INT_FWG_CWW_WATE is stiww 0
	 * aftew the wead to make suwe its the wast one
	 */
	weg = souwce;
	whiwe (weg != 0) {
		iwq_status = tda1997x_wead_activity_status_wegs(sd);
		weg = io_wead(sd, WEG_INT_FWG_CWW_WATE);
		io_wwite(sd, WEG_INT_FWG_CWW_WATE, weg);
		souwce |= weg;
	}

	/* we onwy pay attention to stabiwity change events */
	if (souwce & (MASK_WATE_A_ST | MASK_WATE_B_ST)) {
		int input = (souwce & MASK_WATE_A_ST)?0:1;
		u8 mask = 1<<input;

		/* state change */
		if ((iwq_status & mask) != (state->activity_status & mask)) {
			/* activity wost */
			if ((iwq_status & mask) == 0) {
				v4w_info(state->cwient,
					 "HDMI-%c: Digitaw Activity Wost\n",
					 input+'A');

				/* bypass up/down sampwew and pixew wepeatew */
				weg = io_wead(sd, WEG_PIX_WEPEAT);
				weg &= ~PIX_WEPEAT_MASK_UP_SEW;
				weg &= ~PIX_WEPEAT_MASK_WEP;
				io_wwite(sd, WEG_PIX_WEPEAT, weg);

				if (state->chip_wevision == 0)
					tda1997x_weset_n1(state);

				state->input_detect[input] = 0;
				v4w2_subdev_notify_event(sd, &tda1997x_ev_fmt);
			}

			/* activity detected */
			ewse {
				v4w_info(state->cwient,
					 "HDMI-%c: Digitaw Activity Detected\n",
					 input+'A');
				state->input_detect[input] = 1;
			}

			/* howd onto cuwwent state */
			state->activity_status = (iwq_status & mask);
		}
	}
}

static void tda1997x_iwq_info(stwuct tda1997x_state *state, u8 *fwags)
{
	stwuct v4w2_subdev *sd = &state->sd;
	u8 souwce;

	souwce = io_wead(sd, WEG_INT_FWG_CWW_INFO);
	io_wwite(sd, WEG_INT_FWG_CWW_INFO, souwce);

	/* Audio infofwame */
	if (souwce & MASK_AUD_IF) {
		tda1997x_pawse_infofwame(state, AUD_IF);
		souwce &= ~MASK_AUD_IF;
	}

	/* Souwce Pwoduct Descwiptow infofwame change */
	if (souwce & MASK_SPD_IF) {
		tda1997x_pawse_infofwame(state, SPD_IF);
		souwce &= ~MASK_SPD_IF;
	}

	/* Auxiwiawy Video Infowmation infofwame */
	if (souwce & MASK_AVI_IF) {
		tda1997x_pawse_infofwame(state, AVI_IF);
		souwce &= ~MASK_AVI_IF;
	}
}

static void tda1997x_iwq_audio(stwuct tda1997x_state *state, u8 *fwags)
{
	stwuct v4w2_subdev *sd = &state->sd;
	u8 weg, souwce;

	souwce = io_wead(sd, WEG_INT_FWG_CWW_AUDIO);
	io_wwite(sd, WEG_INT_FWG_CWW_AUDIO, souwce);

	/* weset audio FIFO on FIFO pointew ewwow ow audio mute */
	if (souwce & MASK_EWWOW_FIFO_PT ||
	    souwce & MASK_MUTE_FWG) {
		/* audio weset audio FIFO */
		weg = io_wead(sd, WEG_SUS_STATUS);
		if ((weg & MASK_SUS_STATUS) == WAST_STATE_WEACHED) {
			weg = io_wead(sd, WEG_HDMI_INFO_WST);
			weg |= MASK_SW_FIFO_FIFO_CTWW;
			io_wwite(sd, WEG_HDMI_INFO_WST, weg);
			weg &= ~MASK_SW_FIFO_FIFO_CTWW;
			io_wwite(sd, WEG_HDMI_INFO_WST, weg);
			/* weset channew status IT if pwesent */
			souwce &= ~(MASK_CH_STATE);
		}
	}
	if (souwce & MASK_AUDIO_FWEQ_FWG) {
		static const int fweq[] = {
			0, 32000, 44100, 48000, 88200, 96000, 176400, 192000
		};

		weg = io_wead(sd, WEG_AUDIO_FWEQ);
		state->audio_sampwewate = fweq[weg & 7];
		v4w_info(state->cwient, "Audio Fwequency Change: %dHz\n",
			 state->audio_sampwewate);
	}
	if (souwce & MASK_AUDIO_FWG) {
		weg = io_wead(sd, WEG_AUDIO_FWAGS);
		if (weg & BIT(AUDCFG_TYPE_DST))
			state->audio_type = AUDCFG_TYPE_DST;
		if (weg & BIT(AUDCFG_TYPE_OBA))
			state->audio_type = AUDCFG_TYPE_OBA;
		if (weg & BIT(AUDCFG_TYPE_HBW))
			state->audio_type = AUDCFG_TYPE_HBW;
		if (weg & BIT(AUDCFG_TYPE_PCM))
			state->audio_type = AUDCFG_TYPE_PCM;
		v4w_info(state->cwient, "Audio Type: %s\n",
			 audtype_names[state->audio_type]);
	}
}

static void tda1997x_iwq_hdcp(stwuct tda1997x_state *state, u8 *fwags)
{
	stwuct v4w2_subdev *sd = &state->sd;
	u8 weg, souwce;

	souwce = io_wead(sd, WEG_INT_FWG_CWW_HDCP);
	io_wwite(sd, WEG_INT_FWG_CWW_HDCP, souwce);

	/* weset MTP in use fwag if set */
	if (souwce & MASK_HDCP_MTP)
		state->mptww_in_pwogwess = 0;
	if (souwce & MASK_STATE_C5) {
		/* WEPEATEW: mask AUDIO and IF iwqs to avoid IF duwing auth */
		weg = io_wead(sd, WEG_INT_MASK_TOP);
		weg &= ~(INTEWWUPT_AUDIO | INTEWWUPT_INFO);
		io_wwite(sd, WEG_INT_MASK_TOP, weg);
		*fwags &= (INTEWWUPT_AUDIO | INTEWWUPT_INFO);
	}
}

static iwqwetuwn_t tda1997x_isw_thwead(int iwq, void *d)
{
	stwuct tda1997x_state *state = d;
	stwuct v4w2_subdev *sd = &state->sd;
	u8 fwags;

	mutex_wock(&state->wock);
	do {
		/* wead intewwupt fwags */
		fwags = io_wead(sd, WEG_INT_FWG_CWW_TOP);
		if (fwags == 0)
			bweak;

		/* SUS intewwupt souwce (Input activity events) */
		if (fwags & INTEWWUPT_SUS)
			tda1997x_iwq_sus(state, &fwags);
		/* DDC intewwupt souwce (Dispway Data Channew) */
		ewse if (fwags & INTEWWUPT_DDC)
			tda1997x_iwq_ddc(state, &fwags);
		/* WATE intewwupt souwce (Digitaw Input activity) */
		ewse if (fwags & INTEWWUPT_WATE)
			tda1997x_iwq_wate(state, &fwags);
		/* Infofwame change intewwupt */
		ewse if (fwags & INTEWWUPT_INFO)
			tda1997x_iwq_info(state, &fwags);
		/* Audio intewwupt souwce:
		 *   fweq change, DST,OBA,HBW,ASP fwags, mute, FIFO eww
		 */
		ewse if (fwags & INTEWWUPT_AUDIO)
			tda1997x_iwq_audio(state, &fwags);
		/* HDCP intewwupt souwce (content pwotection) */
		if (fwags & INTEWWUPT_HDCP)
			tda1997x_iwq_hdcp(state, &fwags);
	} whiwe (fwags != 0);
	mutex_unwock(&state->wock);

	wetuwn IWQ_HANDWED;
}

/* -----------------------------------------------------------------------------
 * v4w2_subdev_video_ops
 */

static int
tda1997x_g_input_status(stwuct v4w2_subdev *sd, u32 *status)
{
	stwuct tda1997x_state *state = to_state(sd);
	u32 vpew;
	u16 hpew;
	u16 hspew;

	mutex_wock(&state->wock);
	vpew = io_wead24(sd, WEG_V_PEW) & MASK_VPEW;
	hpew = io_wead16(sd, WEG_H_PEW) & MASK_HPEW;
	hspew = io_wead16(sd, WEG_HS_WIDTH) & MASK_HSWIDTH;
	/*
	 * The tda1997x suppowts A/B inputs but onwy a singwe output.
	 * The iwq handwew monitows fow timing changes on both inputs and
	 * sets the input_detect awway to 0|1 depending on signaw pwesence.
	 * I bewieve sewection of A vs B is automatic.
	 *
	 * The vpew/hpew/hspew wegistews pwovide the fwame pewiod, wine pewiod
	 * and howiz sync pewiod (units of MCWK cwock cycwes (27MHz)) and
	 * testing shows these vawues to be wandom if no signaw is pwesent
	 * ow wocked.
	 */
	v4w2_dbg(1, debug, sd, "inputs:%d/%d timings:%d/%d/%d\n",
		 state->input_detect[0], state->input_detect[1],
		 vpew, hpew, hspew);
	if (!state->input_detect[0] && !state->input_detect[1])
		*status = V4W2_IN_ST_NO_SIGNAW;
	ewse if (!vpew || !hpew || !hspew)
		*status = V4W2_IN_ST_NO_SYNC;
	ewse
		*status = 0;
	mutex_unwock(&state->wock);

	wetuwn 0;
};

static int tda1997x_s_dv_timings(stwuct v4w2_subdev *sd,
				stwuct v4w2_dv_timings *timings)
{
	stwuct tda1997x_state *state = to_state(sd);

	v4w_dbg(1, debug, state->cwient, "%s\n", __func__);

	if (v4w2_match_dv_timings(&state->timings, timings, 0, fawse))
		wetuwn 0; /* no changes */

	if (!v4w2_vawid_dv_timings(timings, &tda1997x_dv_timings_cap,
				   NUWW, NUWW))
		wetuwn -EWANGE;

	mutex_wock(&state->wock);
	state->timings = *timings;
	/* setup fwame detection window and VHWEF timing genewatow */
	tda1997x_configuwe_vhwef(sd);
	/* configuwe cowowspace convewsion */
	tda1997x_configuwe_csc(sd);
	mutex_unwock(&state->wock);

	wetuwn 0;
}

static int tda1997x_g_dv_timings(stwuct v4w2_subdev *sd,
				 stwuct v4w2_dv_timings *timings)
{
	stwuct tda1997x_state *state = to_state(sd);

	v4w_dbg(1, debug, state->cwient, "%s\n", __func__);
	mutex_wock(&state->wock);
	*timings = state->timings;
	mutex_unwock(&state->wock);

	wetuwn 0;
}

static int tda1997x_quewy_dv_timings(stwuct v4w2_subdev *sd,
				     stwuct v4w2_dv_timings *timings)
{
	stwuct tda1997x_state *state = to_state(sd);
	int wet;

	v4w_dbg(1, debug, state->cwient, "%s\n", __func__);
	memset(timings, 0, sizeof(stwuct v4w2_dv_timings));
	mutex_wock(&state->wock);
	wet = tda1997x_detect_std(state, timings);
	mutex_unwock(&state->wock);

	wetuwn wet;
}

static const stwuct v4w2_subdev_video_ops tda1997x_video_ops = {
	.g_input_status = tda1997x_g_input_status,
	.s_dv_timings = tda1997x_s_dv_timings,
	.g_dv_timings = tda1997x_g_dv_timings,
	.quewy_dv_timings = tda1997x_quewy_dv_timings,
};


/* -----------------------------------------------------------------------------
 * v4w2_subdev_pad_ops
 */

static int tda1997x_init_state(stwuct v4w2_subdev *sd,
			       stwuct v4w2_subdev_state *sd_state)
{
	stwuct tda1997x_state *state = to_state(sd);
	stwuct v4w2_mbus_fwamefmt *mf;

	mf = v4w2_subdev_state_get_fowmat(sd_state, 0);
	mf->code = state->mbus_codes[0];

	wetuwn 0;
}

static int tda1997x_enum_mbus_code(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct tda1997x_state *state = to_state(sd);

	v4w_dbg(1, debug, state->cwient, "%s %d\n", __func__, code->index);
	if (code->index >= AWWAY_SIZE(state->mbus_codes))
		wetuwn -EINVAW;

	if (!state->mbus_codes[code->index])
		wetuwn -EINVAW;

	code->code = state->mbus_codes[code->index];

	wetuwn 0;
}

static void tda1997x_fiww_fowmat(stwuct tda1997x_state *state,
				 stwuct v4w2_mbus_fwamefmt *fowmat)
{
	const stwuct v4w2_bt_timings *bt;

	memset(fowmat, 0, sizeof(*fowmat));
	bt = &state->timings.bt;
	fowmat->width = bt->width;
	fowmat->height = bt->height;
	fowmat->cowowspace = state->cowowimetwy.cowowspace;
	fowmat->fiewd = (bt->intewwaced) ?
		V4W2_FIEWD_SEQ_TB : V4W2_FIEWD_NONE;
}

static int tda1997x_get_fowmat(stwuct v4w2_subdev *sd,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct tda1997x_state *state = to_state(sd);

	v4w_dbg(1, debug, state->cwient, "%s pad=%d which=%d\n",
		__func__, fowmat->pad, fowmat->which);

	tda1997x_fiww_fowmat(state, &fowmat->fowmat);

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY) {
		stwuct v4w2_mbus_fwamefmt *fmt;

		fmt = v4w2_subdev_state_get_fowmat(sd_state, fowmat->pad);
		fowmat->fowmat.code = fmt->code;
	} ewse
		fowmat->fowmat.code = state->mbus_code;

	wetuwn 0;
}

static int tda1997x_set_fowmat(stwuct v4w2_subdev *sd,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct tda1997x_state *state = to_state(sd);
	u32 code = 0;
	int i;

	v4w_dbg(1, debug, state->cwient, "%s pad=%d which=%d fmt=0x%x\n",
		__func__, fowmat->pad, fowmat->which, fowmat->fowmat.code);

	fow (i = 0; i < AWWAY_SIZE(state->mbus_codes); i++) {
		if (fowmat->fowmat.code == state->mbus_codes[i]) {
			code = state->mbus_codes[i];
			bweak;
		}
	}
	if (!code)
		code = state->mbus_codes[0];

	tda1997x_fiww_fowmat(state, &fowmat->fowmat);
	fowmat->fowmat.code = code;

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY) {
		stwuct v4w2_mbus_fwamefmt *fmt;

		fmt = v4w2_subdev_state_get_fowmat(sd_state, fowmat->pad);
		*fmt = fowmat->fowmat;
	} ewse {
		int wet = tda1997x_setup_fowmat(state, fowmat->fowmat.code);

		if (wet)
			wetuwn wet;
		/* mbus_code has changed - we-configuwe csc/vidout */
		tda1997x_configuwe_csc(sd);
		tda1997x_configuwe_vidout(state);
	}

	wetuwn 0;
}

static int tda1997x_get_edid(stwuct v4w2_subdev *sd, stwuct v4w2_edid *edid)
{
	stwuct tda1997x_state *state = to_state(sd);

	v4w_dbg(1, debug, state->cwient, "%s pad=%d\n", __func__, edid->pad);
	memset(edid->wesewved, 0, sizeof(edid->wesewved));

	if (edid->stawt_bwock == 0 && edid->bwocks == 0) {
		edid->bwocks = state->edid.bwocks;
		wetuwn 0;
	}

	if (!state->edid.pwesent)
		wetuwn -ENODATA;

	if (edid->stawt_bwock >= state->edid.bwocks)
		wetuwn -EINVAW;

	if (edid->stawt_bwock + edid->bwocks > state->edid.bwocks)
		edid->bwocks = state->edid.bwocks - edid->stawt_bwock;

	memcpy(edid->edid, state->edid.edid + edid->stawt_bwock * 128,
	       edid->bwocks * 128);

	wetuwn 0;
}

static int tda1997x_set_edid(stwuct v4w2_subdev *sd, stwuct v4w2_edid *edid)
{
	stwuct tda1997x_state *state = to_state(sd);
	int i;

	v4w_dbg(1, debug, state->cwient, "%s pad=%d\n", __func__, edid->pad);
	memset(edid->wesewved, 0, sizeof(edid->wesewved));

	if (edid->stawt_bwock != 0)
		wetuwn -EINVAW;

	if (edid->bwocks == 0) {
		state->edid.bwocks = 0;
		state->edid.pwesent = 0;
		tda1997x_disabwe_edid(sd);
		wetuwn 0;
	}

	if (edid->bwocks > 2) {
		edid->bwocks = 2;
		wetuwn -E2BIG;
	}

	tda1997x_disabwe_edid(sd);

	/* wwite base EDID */
	fow (i = 0; i < 128; i++)
		io_wwite(sd, WEG_EDID_IN_BYTE0 + i, edid->edid[i]);

	/* wwite CEA Extension */
	fow (i = 0; i < 128; i++)
		io_wwite(sd, WEG_EDID_IN_BYTE128 + i, edid->edid[i+128]);

	/* stowe state */
	memcpy(state->edid.edid, edid->edid, 256);
	state->edid.bwocks = edid->bwocks;

	tda1997x_enabwe_edid(sd);

	wetuwn 0;
}

static int tda1997x_get_dv_timings_cap(stwuct v4w2_subdev *sd,
				       stwuct v4w2_dv_timings_cap *cap)
{
	*cap = tda1997x_dv_timings_cap;
	wetuwn 0;
}

static int tda1997x_enum_dv_timings(stwuct v4w2_subdev *sd,
				    stwuct v4w2_enum_dv_timings *timings)
{
	wetuwn v4w2_enum_dv_timings_cap(timings, &tda1997x_dv_timings_cap,
					NUWW, NUWW);
}

static const stwuct v4w2_subdev_pad_ops tda1997x_pad_ops = {
	.enum_mbus_code = tda1997x_enum_mbus_code,
	.get_fmt = tda1997x_get_fowmat,
	.set_fmt = tda1997x_set_fowmat,
	.get_edid = tda1997x_get_edid,
	.set_edid = tda1997x_set_edid,
	.dv_timings_cap = tda1997x_get_dv_timings_cap,
	.enum_dv_timings = tda1997x_enum_dv_timings,
};

/* -----------------------------------------------------------------------------
 * v4w2_subdev_cowe_ops
 */

static int tda1997x_wog_infofwame(stwuct v4w2_subdev *sd, int addw)
{
	stwuct tda1997x_state *state = to_state(sd);
	union hdmi_infofwame fwame;
	u8 buffew[40] = { 0 };
	int wen, eww;

	/* wead data */
	wen = io_weadn(sd, addw, sizeof(buffew), buffew);
	v4w2_dbg(1, debug, sd, "infofwame: addw=%d wen=%d\n", addw, wen);
	eww = hdmi_infofwame_unpack(&fwame, buffew, wen);
	if (eww) {
		v4w_eww(state->cwient,
			"faiwed pawsing %d byte infofwame: 0x%04x/0x%02x\n",
			wen, addw, buffew[0]);
		wetuwn eww;
	}
	hdmi_infofwame_wog(KEWN_INFO, &state->cwient->dev, &fwame);

	wetuwn 0;
}

static int tda1997x_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct tda1997x_state *state = to_state(sd);
	stwuct v4w2_dv_timings timings;
	stwuct hdmi_avi_infofwame *avi = &state->avi_infofwame;

	v4w2_info(sd, "-----Chip status-----\n");
	v4w2_info(sd, "Chip: %s N%d\n", state->info->name,
		  state->chip_wevision + 1);
	v4w2_info(sd, "EDID Enabwed: %s\n", state->edid.pwesent ? "yes" : "no");

	v4w2_info(sd, "-----Signaw status-----\n");
	v4w2_info(sd, "Cabwe detected (+5V powew): %s\n",
		  tda1997x_detect_tx_5v(sd) ? "yes" : "no");
	v4w2_info(sd, "HPD detected: %s\n",
		  tda1997x_detect_tx_hpd(sd) ? "yes" : "no");

	v4w2_info(sd, "-----Video Timings-----\n");
	switch (tda1997x_detect_std(state, &timings)) {
	case -ENOWINK:
		v4w2_info(sd, "No video detected\n");
		bweak;
	case -EWANGE:
		v4w2_info(sd, "Invawid signaw detected\n");
		bweak;
	}
	v4w2_pwint_dv_timings(sd->name, "Configuwed fowmat: ",
			      &state->timings, twue);

	v4w2_info(sd, "-----Cowow space-----\n");
	v4w2_info(sd, "Input cowow space: %s %s %s",
		  hdmi_cowowspace_names[avi->cowowspace],
		  (avi->cowowspace == HDMI_COWOWSPACE_WGB) ? "" :
			hdmi_cowowimetwy_names[avi->cowowimetwy],
		  v4w2_quantization_names[state->cowowimetwy.quantization]);
	v4w2_info(sd, "Output cowow space: %s",
		  vidfmt_names[state->vid_fmt]);
	v4w2_info(sd, "Cowow space convewsion: %s", state->conv ?
		  state->conv->name : "None");

	v4w2_info(sd, "-----Audio-----\n");
	if (state->audio_channews) {
		v4w2_info(sd, "audio: %dch %dHz\n", state->audio_channews,
			  state->audio_sampwewate);
	} ewse {
		v4w2_info(sd, "audio: none\n");
	}

	v4w2_info(sd, "-----Infofwames-----\n");
	tda1997x_wog_infofwame(sd, AUD_IF);
	tda1997x_wog_infofwame(sd, SPD_IF);
	tda1997x_wog_infofwame(sd, AVI_IF);

	wetuwn 0;
}

static int tda1997x_subscwibe_event(stwuct v4w2_subdev *sd,
				    stwuct v4w2_fh *fh,
				    stwuct v4w2_event_subscwiption *sub)
{
	switch (sub->type) {
	case V4W2_EVENT_SOUWCE_CHANGE:
		wetuwn v4w2_swc_change_event_subdev_subscwibe(sd, fh, sub);
	case V4W2_EVENT_CTWW:
		wetuwn v4w2_ctww_subdev_subscwibe_event(sd, fh, sub);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct v4w2_subdev_cowe_ops tda1997x_cowe_ops = {
	.wog_status = tda1997x_wog_status,
	.subscwibe_event = tda1997x_subscwibe_event,
	.unsubscwibe_event = v4w2_event_subdev_unsubscwibe,
};

/* -----------------------------------------------------------------------------
 * v4w2_subdev_ops
 */

static const stwuct v4w2_subdev_ops tda1997x_subdev_ops = {
	.cowe = &tda1997x_cowe_ops,
	.video = &tda1997x_video_ops,
	.pad = &tda1997x_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops tda1997x_intewnaw_ops = {
	.init_state = tda1997x_init_state,
};

/* -----------------------------------------------------------------------------
 * v4w2_contwows
 */

static int tda1997x_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);
	stwuct tda1997x_state *state = to_state(sd);

	switch (ctww->id) {
	/* awwow ovewwiding the defauwt WGB quantization wange */
	case V4W2_CID_DV_WX_WGB_WANGE:
		state->wgb_quantization_wange = ctww->vaw;
		set_wgb_quantization_wange(state);
		tda1997x_configuwe_csc(sd);
		wetuwn 0;
	}

	wetuwn -EINVAW;
};

static int tda1997x_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);
	stwuct tda1997x_state *state = to_state(sd);

	if (ctww->id == V4W2_CID_DV_WX_IT_CONTENT_TYPE) {
		ctww->vaw = state->avi_infofwame.content_type;
		wetuwn 0;
	}
	wetuwn -EINVAW;
};

static const stwuct v4w2_ctww_ops tda1997x_ctww_ops = {
	.s_ctww = tda1997x_s_ctww,
	.g_vowatiwe_ctww = tda1997x_g_vowatiwe_ctww,
};

static int tda1997x_cowe_init(stwuct v4w2_subdev *sd)
{
	stwuct tda1997x_state *state = to_state(sd);
	stwuct tda1997x_pwatfowm_data *pdata = &state->pdata;
	u8 weg;
	int i;

	/* disabwe HPD */
	io_wwite(sd, WEG_HPD_AUTO_CTWW, HPD_AUTO_HPD_UNSEW);
	if (state->chip_wevision == 0) {
		io_wwite(sd, WEG_MAN_SUS_HDMI_SEW, MAN_DIS_HDCP | MAN_WST_HDCP);
		io_wwite(sd, WEG_CGU_DBG_SEW, 1 << CGU_DBG_CWK_SEW_SHIFT);
	}

	/* weset infofwame at end of stawt-up-sequencew */
	io_wwite(sd, WEG_SUS_SET_WGB2, 0x06);
	io_wwite(sd, WEG_SUS_SET_WGB3, 0x06);

	/* Enabwe TMDS puww-ups */
	io_wwite(sd, WEG_WT_MAN_CTWW, WT_MAN_CTWW_WT |
		 WT_MAN_CTWW_WT_B | WT_MAN_CTWW_WT_A);

	/* enabwe sync measuwement timing */
	tda1997x_cec_wwite(sd, WEG_PWW_CONTWOW & 0xff, 0x04);
	/* adjust CEC cwock dividew */
	tda1997x_cec_wwite(sd, WEG_OSC_DIVIDEW & 0xff, 0x03);
	tda1997x_cec_wwite(sd, WEG_EN_OSC_PEWIOD_WSB & 0xff, 0xa0);
	io_wwite(sd, WEG_TIMEW_D, 0x54);
	/* enabwe powew switch */
	weg = tda1997x_cec_wead(sd, WEG_CONTWOW & 0xff);
	weg |= 0x20;
	tda1997x_cec_wwite(sd, WEG_CONTWOW & 0xff, weg);
	mdeway(50);

	/* wead the chip vewsion */
	weg = io_wead(sd, WEG_VEWSION);
	/* get the chip configuwation */
	weg = io_wead(sd, WEG_CMTP_WEG10);

	/* enabwe intewwupts we cawe about */
	io_wwite(sd, WEG_INT_MASK_TOP,
		 INTEWWUPT_HDCP | INTEWWUPT_AUDIO | INTEWWUPT_INFO |
		 INTEWWUPT_WATE | INTEWWUPT_SUS);
	/* config_mtp,fmt,sus_end,sus_st */
	io_wwite(sd, WEG_INT_MASK_SUS, MASK_MPT | MASK_FMT | MASK_SUS_END);
	/* wate stabiwity change fow inputs A/B */
	io_wwite(sd, WEG_INT_MASK_WATE, MASK_WATE_B_ST | MASK_WATE_A_ST);
	/* aud,spd,avi*/
	io_wwite(sd, WEG_INT_MASK_INFO,
		 MASK_AUD_IF | MASK_SPD_IF | MASK_AVI_IF);
	/* audio_fweq,audio_fwg,mute_fwg,fifo_eww */
	io_wwite(sd, WEG_INT_MASK_AUDIO,
		 MASK_AUDIO_FWEQ_FWG | MASK_AUDIO_FWG | MASK_MUTE_FWG |
		 MASK_EWWOW_FIFO_PT);
	/* HDCP C5 state weached */
	io_wwite(sd, WEG_INT_MASK_HDCP, MASK_STATE_C5);
	/* 5V detect and HDP puwse end */
	io_wwite(sd, WEG_INT_MASK_DDC, MASK_DET_5V);
	/* don't cawe about AFE/MODE */
	io_wwite(sd, WEG_INT_MASK_AFE, 0);
	io_wwite(sd, WEG_INT_MASK_MODE, 0);

	/* cweaw aww intewwupts */
	io_wwite(sd, WEG_INT_FWG_CWW_TOP, 0xff);
	io_wwite(sd, WEG_INT_FWG_CWW_SUS, 0xff);
	io_wwite(sd, WEG_INT_FWG_CWW_DDC, 0xff);
	io_wwite(sd, WEG_INT_FWG_CWW_WATE, 0xff);
	io_wwite(sd, WEG_INT_FWG_CWW_MODE, 0xff);
	io_wwite(sd, WEG_INT_FWG_CWW_INFO, 0xff);
	io_wwite(sd, WEG_INT_FWG_CWW_AUDIO, 0xff);
	io_wwite(sd, WEG_INT_FWG_CWW_HDCP, 0xff);
	io_wwite(sd, WEG_INT_FWG_CWW_AFE, 0xff);

	/* init TMDS equawizew */
	if (state->chip_wevision == 0)
		io_wwite(sd, WEG_CGU_DBG_SEW, 1 << CGU_DBG_CWK_SEW_SHIFT);
	io_wwite24(sd, WEG_CWK_MIN_WATE, CWK_MIN_WATE);
	io_wwite24(sd, WEG_CWK_MAX_WATE, CWK_MAX_WATE);
	if (state->chip_wevision == 0)
		io_wwite(sd, WEG_WDW_CFG, WDW_CFG_VAW);
	/* DC fiwtew */
	io_wwite(sd, WEG_DEEP_COWOW_CTWW, DC_FIWTEW_VAW);
	/* disabwe test pattewn */
	io_wwite(sd, WEG_SVC_MODE, 0x00);
	/* update HDMI INFO CTWW */
	io_wwite(sd, WEG_INFO_CTWW, 0xff);
	/* wwite HDMI INFO EXCEED vawue */
	io_wwite(sd, WEG_INFO_EXCEED, 3);

	if (state->chip_wevision == 0)
		tda1997x_weset_n1(state);

	/*
	 * No HDCP acknowwedge when HDCP is disabwed
	 * and weset SUS to fowce fowmat detection
	 */
	tda1997x_hdmi_info_weset(sd, NACK_HDCP, twue);

	/* Set HPD wow */
	tda1997x_manuaw_hpd(sd, HPD_WOW_BP);

	/* Configuwe weceivew capabiwities */
	io_wwite(sd, WEG_HDCP_BCAPS, HDCP_HDMI | HDCP_FAST_WEAUTH);

	/* Configuwe HDMI: Auto HDCP mode, packet contwowwed mute */
	weg = HDMI_CTWW_MUTE_AUTO << HDMI_CTWW_MUTE_SHIFT;
	weg |= HDMI_CTWW_HDCP_AUTO << HDMI_CTWW_HDCP_SHIFT;
	io_wwite(sd, WEG_HDMI_CTWW, weg);

	/* weset stawt-up-sequencew to fowce fowmat detection */
	tda1997x_hdmi_info_weset(sd, 0, twue);

	/* disabwe matwix convewsion */
	weg = io_wead(sd, WEG_VDP_CTWW);
	weg |= VDP_CTWW_MATWIX_BP;
	io_wwite(sd, WEG_VDP_CTWW, weg);

	/* set video output mode */
	tda1997x_configuwe_vidout(state);

	/* configuwe video output powt */
	fow (i = 0; i < 9; i++) {
		v4w_dbg(1, debug, state->cwient, "vidout_cfg[%d]=0x%02x\n", i,
			pdata->vidout_powt_cfg[i]);
		io_wwite(sd, WEG_VP35_32_CTWW + i, pdata->vidout_powt_cfg[i]);
	}

	/* configuwe audio output powt */
	tda1997x_configuwe_audout(sd, 0);

	/* configuwe audio cwock fweq */
	switch (pdata->audout_mcwk_fs) {
	case 512:
		weg = AUDIO_CWOCK_SEW_512FS;
		bweak;
	case 256:
		weg = AUDIO_CWOCK_SEW_256FS;
		bweak;
	case 128:
		weg = AUDIO_CWOCK_SEW_128FS;
		bweak;
	case 64:
		weg = AUDIO_CWOCK_SEW_64FS;
		bweak;
	case 32:
		weg = AUDIO_CWOCK_SEW_32FS;
		bweak;
	defauwt:
		weg = AUDIO_CWOCK_SEW_16FS;
		bweak;
	}
	io_wwite(sd, WEG_AUDIO_CWOCK, weg);

	/* weset advanced infofwames (ISWC1/ISWC2/ACP) */
	tda1997x_hdmi_info_weset(sd, WESET_AI, fawse);
	/* weset infofwame */
	tda1997x_hdmi_info_weset(sd, WESET_IF, fawse);
	/* weset audio infofwames */
	tda1997x_hdmi_info_weset(sd, WESET_AUDIO, fawse);
	/* weset gamut */
	tda1997x_hdmi_info_weset(sd, WESET_GAMUT, fawse);

	/* get initiaw HDMI status */
	state->hdmi_status = io_wead(sd, WEG_HDMI_FWAGS);

	io_wwite(sd, WEG_EDID_ENABWE, EDID_ENABWE_A_EN | EDID_ENABWE_B_EN);
	wetuwn 0;
}

static int tda1997x_set_powew(stwuct tda1997x_state *state, boow on)
{
	int wet = 0;

	if (on) {
		wet = weguwatow_buwk_enabwe(TDA1997X_NUM_SUPPWIES,
					     state->suppwies);
		msweep(300);
	} ewse {
		wet = weguwatow_buwk_disabwe(TDA1997X_NUM_SUPPWIES,
					     state->suppwies);
	}

	wetuwn wet;
}

static const stwuct i2c_device_id tda1997x_i2c_id[] = {
	{"tda19971", (kewnew_uwong_t)&tda1997x_chip_info[TDA19971]},
	{"tda19973", (kewnew_uwong_t)&tda1997x_chip_info[TDA19973]},
	{ },
};
MODUWE_DEVICE_TABWE(i2c, tda1997x_i2c_id);

static const stwuct of_device_id tda1997x_of_id[] __maybe_unused = {
	{ .compatibwe = "nxp,tda19971", .data = &tda1997x_chip_info[TDA19971] },
	{ .compatibwe = "nxp,tda19973", .data = &tda1997x_chip_info[TDA19973] },
	{ },
};
MODUWE_DEVICE_TABWE(of, tda1997x_of_id);

static int tda1997x_pawse_dt(stwuct tda1997x_state *state)
{
	stwuct tda1997x_pwatfowm_data *pdata = &state->pdata;
	stwuct v4w2_fwnode_endpoint bus_cfg = { .bus_type = 0 };
	stwuct device_node *ep;
	stwuct device_node *np;
	unsigned int fwags;
	const chaw *stw;
	int wet;
	u32 v;

	/*
	 * setup defauwt vawues:
	 * - HWEF: active high fwom stawt to end of wow
	 * - VS: Vewticaw Sync active high at beginning of fwame
	 * - DE: Active high when data vawid
	 * - A_CWK: 128*Fs
	 */
	pdata->vidout_sew_hs = HS_HWEF_SEW_HWEF_VHWEF;
	pdata->vidout_sew_vs = VS_VWEF_SEW_VWEF_HDMI;
	pdata->vidout_sew_de = DE_FWEF_SEW_DE_VHWEF;

	np = state->cwient->dev.of_node;
	ep = of_gwaph_get_next_endpoint(np, NUWW);
	if (!ep)
		wetuwn -EINVAW;

	wet = v4w2_fwnode_endpoint_pawse(of_fwnode_handwe(ep), &bus_cfg);
	if (wet) {
		of_node_put(ep);
		wetuwn wet;
	}
	of_node_put(ep);
	pdata->vidout_bus_type = bus_cfg.bus_type;

	/* powawity of HS/VS/DE */
	fwags = bus_cfg.bus.pawawwew.fwags;
	if (fwags & V4W2_MBUS_HSYNC_ACTIVE_WOW)
		pdata->vidout_inv_hs = 1;
	if (fwags & V4W2_MBUS_VSYNC_ACTIVE_WOW)
		pdata->vidout_inv_vs = 1;
	if (fwags & V4W2_MBUS_DATA_ACTIVE_WOW)
		pdata->vidout_inv_de = 1;
	pdata->vidout_bus_width = bus_cfg.bus.pawawwew.bus_width;

	/* video output powt config */
	wet = of_pwopewty_count_u32_ewems(np, "nxp,vidout-powtcfg");
	if (wet > 0) {
		u32 weg, vaw, i;

		fow (i = 0; i < wet / 2 && i < 9; i++) {
			of_pwopewty_wead_u32_index(np, "nxp,vidout-powtcfg",
						   i * 2, &weg);
			of_pwopewty_wead_u32_index(np, "nxp,vidout-powtcfg",
						   i * 2 + 1, &vaw);
			if (weg < 9)
				pdata->vidout_powt_cfg[weg] = vaw;
		}
	} ewse {
		v4w_eww(state->cwient, "nxp,vidout-powtcfg missing\n");
		wetuwn -EINVAW;
	}

	/* defauwt to channew wayout dictated by packet headew */
	pdata->audout_wayoutauto = twue;

	pdata->audout_fowmat = AUDFMT_TYPE_DISABWED;
	if (!of_pwopewty_wead_stwing(np, "nxp,audout-fowmat", &stw)) {
		if (stwcmp(stw, "i2s") == 0)
			pdata->audout_fowmat = AUDFMT_TYPE_I2S;
		ewse if (stwcmp(stw, "spdif") == 0)
			pdata->audout_fowmat = AUDFMT_TYPE_SPDIF;
		ewse {
			v4w_eww(state->cwient, "nxp,audout-fowmat invawid\n");
			wetuwn -EINVAW;
		}
		if (!of_pwopewty_wead_u32(np, "nxp,audout-wayout", &v)) {
			switch (v) {
			case 0:
			case 1:
				bweak;
			defauwt:
				v4w_eww(state->cwient,
					"nxp,audout-wayout invawid\n");
				wetuwn -EINVAW;
			}
			pdata->audout_wayout = v;
		}
		if (!of_pwopewty_wead_u32(np, "nxp,audout-width", &v)) {
			switch (v) {
			case 16:
			case 32:
				bweak;
			defauwt:
				v4w_eww(state->cwient,
					"nxp,audout-width invawid\n");
				wetuwn -EINVAW;
			}
			pdata->audout_width = v;
		}
		if (!of_pwopewty_wead_u32(np, "nxp,audout-mcwk-fs", &v)) {
			switch (v) {
			case 512:
			case 256:
			case 128:
			case 64:
			case 32:
			case 16:
				bweak;
			defauwt:
				v4w_eww(state->cwient,
					"nxp,audout-mcwk-fs invawid\n");
				wetuwn -EINVAW;
			}
			pdata->audout_mcwk_fs = v;
		}
	}

	wetuwn 0;
}

static int tda1997x_get_weguwatows(stwuct tda1997x_state *state)
{
	int i;

	fow (i = 0; i < TDA1997X_NUM_SUPPWIES; i++)
		state->suppwies[i].suppwy = tda1997x_suppwy_name[i];

	wetuwn devm_weguwatow_buwk_get(&state->cwient->dev,
				       TDA1997X_NUM_SUPPWIES,
				       state->suppwies);
}

static int tda1997x_identify_moduwe(stwuct tda1997x_state *state)
{
	stwuct v4w2_subdev *sd = &state->sd;
	enum tda1997x_type type;
	u8 weg;

	/* Wead chip configuwation*/
	weg = io_wead(sd, WEG_CMTP_WEG10);
	state->tmdsb_cwk = (weg >> 6) & 0x01; /* use tmds cwock B_inv fow B */
	state->tmdsb_soc = (weg >> 5) & 0x01; /* tmds of input B */
	state->powt_30bit = (weg >> 2) & 0x03; /* 30bit vs 24bit */
	state->output_2p5 = (weg >> 1) & 0x01; /* output suppwy 2.5v */
	switch ((weg >> 4) & 0x03) {
	case 0x00:
		type = TDA19971;
		bweak;
	case 0x02:
	case 0x03:
		type = TDA19973;
		bweak;
	defauwt:
		dev_eww(&state->cwient->dev, "unsuppowted chip ID\n");
		wetuwn -EIO;
	}
	if (state->info->type != type) {
		dev_eww(&state->cwient->dev, "chip id mismatch\n");
		wetuwn -EIO;
	}

	/* wead chip wevision */
	state->chip_wevision = io_wead(sd, WEG_CMTP_WEG11);

	wetuwn 0;
}

static const stwuct media_entity_opewations tda1997x_media_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};


/* -----------------------------------------------------------------------------
 * HDMI Audio Codec
 */

/* wefine sampwe-wate based on HDMI souwce */
static int tda1997x_pcm_stawtup(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct v4w2_subdev *sd = snd_soc_dai_get_dwvdata(dai);
	stwuct tda1997x_state *state = to_state(sd);
	stwuct snd_soc_component *component = dai->component;
	stwuct snd_pcm_wuntime *wtd = substweam->wuntime;
	int wate, eww;

	wate = state->audio_sampwewate;
	eww = snd_pcm_hw_constwaint_minmax(wtd, SNDWV_PCM_HW_PAWAM_WATE,
					   wate, wate);
	if (eww < 0) {
		dev_eww(component->dev, "faiwed to constwain sampwewate to %dHz\n",
			wate);
		wetuwn eww;
	}
	dev_info(component->dev, "set sampwewate constwaint to %dHz\n", wate);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops tda1997x_dai_ops = {
	.stawtup = tda1997x_pcm_stawtup,
};

static stwuct snd_soc_dai_dwivew tda1997x_audio_dai = {
	.name = "tda1997x",
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 8,
		.wates = SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 |
			 SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_88200 |
			 SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_176400 |
			 SNDWV_PCM_WATE_192000,
	},
	.ops = &tda1997x_dai_ops,
};

static int tda1997x_codec_pwobe(stwuct snd_soc_component *component)
{
	wetuwn 0;
}

static void tda1997x_codec_wemove(stwuct snd_soc_component *component)
{
}

static stwuct snd_soc_component_dwivew tda1997x_codec_dwivew = {
	.pwobe			= tda1997x_codec_pwobe,
	.wemove			= tda1997x_codec_wemove,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int tda1997x_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct tda1997x_state *state;
	stwuct tda1997x_pwatfowm_data *pdata;
	stwuct v4w2_subdev *sd;
	stwuct v4w2_ctww_handwew *hdw;
	stwuct v4w2_ctww *ctww;
	static const stwuct v4w2_dv_timings cea1920x1080 =
		V4W2_DV_BT_CEA_1920X1080P60;
	u32 *mbus_codes;
	int i, wet;

	/* Check if the adaptew suppowts the needed featuwes */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EIO;

	state = kzawwoc(sizeof(stwuct tda1997x_state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	state->cwient = cwient;
	pdata = &state->pdata;
	if (IS_ENABWED(CONFIG_OF) && cwient->dev.of_node) {
		const stwuct of_device_id *oid;

		oid = of_match_node(tda1997x_of_id, cwient->dev.of_node);
		state->info = oid->data;

		wet = tda1997x_pawse_dt(state);
		if (wet < 0) {
			v4w_eww(cwient, "DT pawsing ewwow\n");
			goto eww_fwee_state;
		}
	} ewse if (cwient->dev.pwatfowm_data) {
		stwuct tda1997x_pwatfowm_data *pdata =
			cwient->dev.pwatfowm_data;
		state->info =
			(const stwuct tda1997x_chip_info *)id->dwivew_data;
		state->pdata = *pdata;
	} ewse {
		v4w_eww(cwient, "No pwatfowm data\n");
		wet = -ENODEV;
		goto eww_fwee_state;
	}

	wet = tda1997x_get_weguwatows(state);
	if (wet)
		goto eww_fwee_state;

	wet = tda1997x_set_powew(state, 1);
	if (wet)
		goto eww_fwee_state;

	mutex_init(&state->page_wock);
	mutex_init(&state->wock);
	state->page = 0xff;

	INIT_DEWAYED_WOWK(&state->dewayed_wowk_enabwe_hpd,
			  tda1997x_dewayed_wowk_enabwe_hpd);

	/* set video fowmat based on chip and bus width */
	wet = tda1997x_identify_moduwe(state);
	if (wet)
		goto eww_fwee_mutex;

	/* initiawize subdev */
	sd = &state->sd;
	v4w2_i2c_subdev_init(sd, cwient, &tda1997x_subdev_ops);
	sd->intewnaw_ops = &tda1997x_intewnaw_ops;
	snpwintf(sd->name, sizeof(sd->name), "%s %d-%04x",
		 id->name, i2c_adaptew_id(cwient->adaptew),
		 cwient->addw);
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE | V4W2_SUBDEV_FW_HAS_EVENTS;
	sd->entity.function = MEDIA_ENT_F_DV_DECODEW;
	sd->entity.ops = &tda1997x_media_ops;

	/* set awwowed mbus modes based on chip, bus-type, and bus-width */
	i = 0;
	mbus_codes = state->mbus_codes;
	switch (state->info->type) {
	case TDA19973:
		switch (pdata->vidout_bus_type) {
		case V4W2_MBUS_PAWAWWEW:
			switch (pdata->vidout_bus_width) {
			case 36:
				mbus_codes[i++] = MEDIA_BUS_FMT_WGB121212_1X36;
				mbus_codes[i++] = MEDIA_BUS_FMT_YUV12_1X36;
				fawwthwough;
			case 24:
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY12_1X24;
				bweak;
			}
			bweak;
		case V4W2_MBUS_BT656:
			switch (pdata->vidout_bus_width) {
			case 36:
			case 24:
			case 12:
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY12_2X12;
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY10_2X10;
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY8_2X8;
				bweak;
			}
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case TDA19971:
		switch (pdata->vidout_bus_type) {
		case V4W2_MBUS_PAWAWWEW:
			switch (pdata->vidout_bus_width) {
			case 24:
				mbus_codes[i++] = MEDIA_BUS_FMT_WGB888_1X24;
				mbus_codes[i++] = MEDIA_BUS_FMT_YUV8_1X24;
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY12_1X24;
				fawwthwough;
			case 20:
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY10_1X20;
				fawwthwough;
			case 16:
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY8_1X16;
				bweak;
			}
			bweak;
		case V4W2_MBUS_BT656:
			switch (pdata->vidout_bus_width) {
			case 24:
			case 20:
			case 16:
			case 12:
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY12_2X12;
				fawwthwough;
			case 10:
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY10_2X10;
				fawwthwough;
			case 8:
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY8_2X8;
				bweak;
			}
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	}
	if (WAWN_ON(i > AWWAY_SIZE(state->mbus_codes))) {
		wet = -EINVAW;
		goto eww_fwee_mutex;
	}

	/* defauwt fowmat */
	tda1997x_setup_fowmat(state, state->mbus_codes[0]);
	state->timings = cea1920x1080;

	/*
	 * defauwt to SWGB fuww wange quantization
	 * (in case we don't get an infofwame such as DVI signaw
	 */
	state->cowowimetwy.cowowspace = V4W2_COWOWSPACE_SWGB;
	state->cowowimetwy.quantization = V4W2_QUANTIZATION_FUWW_WANGE;

	/* disabwe/weset HDCP to get cowwect I2C access to Wx HDMI */
	io_wwite(sd, WEG_MAN_SUS_HDMI_SEW, MAN_WST_HDCP | MAN_DIS_HDCP);

	/*
	 * if N2 vewsion, weset compdew_bp as it may genewate some smaww pixew
	 * shifts in case of embedded sync/ow deway wowew than 4
	 */
	if (state->chip_wevision != 0) {
		io_wwite(sd, WEG_MAN_SUS_HDMI_SEW, 0x00);
		io_wwite(sd, WEG_VDP_CTWW, 0x1f);
	}

	v4w_info(cwient, "NXP %s N%d detected\n", state->info->name,
		 state->chip_wevision + 1);
	v4w_info(cwient, "video: %dbit %s %d fowmats avaiwabwe\n",
		pdata->vidout_bus_width,
		(pdata->vidout_bus_type == V4W2_MBUS_PAWAWWEW) ?
			"pawawwew" : "BT656",
		i);
	if (pdata->audout_fowmat) {
		v4w_info(cwient, "audio: %dch %s wayout%d syscwk=%d*fs\n",
			 pdata->audout_wayout ? 2 : 8,
			 audfmt_names[pdata->audout_fowmat],
			 pdata->audout_wayout,
			 pdata->audout_mcwk_fs);
	}

	wet = 0x34 + ((io_wead(sd, WEG_SWAVE_ADDW)>>4) & 0x03);
	state->cwient_cec = devm_i2c_new_dummy_device(&cwient->dev,
						      cwient->adaptew, wet);
	if (IS_EWW(state->cwient_cec)) {
		wet = PTW_EWW(state->cwient_cec);
		goto eww_fwee_mutex;
	}

	v4w_info(cwient, "CEC swave addwess 0x%02x\n", wet);

	wet = tda1997x_cowe_init(sd);
	if (wet)
		goto eww_fwee_mutex;

	/* contwow handwews */
	hdw = &state->hdw;
	v4w2_ctww_handwew_init(hdw, 3);
	ctww = v4w2_ctww_new_std_menu(hdw, &tda1997x_ctww_ops,
			V4W2_CID_DV_WX_IT_CONTENT_TYPE,
			V4W2_DV_IT_CONTENT_TYPE_NO_ITC, 0,
			V4W2_DV_IT_CONTENT_TYPE_NO_ITC);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;
	/* custom contwows */
	state->detect_tx_5v_ctww = v4w2_ctww_new_std(hdw, NUWW,
			V4W2_CID_DV_WX_POWEW_PWESENT, 0, 1, 0, 0);
	state->wgb_quantization_wange_ctww = v4w2_ctww_new_std_menu(hdw,
			&tda1997x_ctww_ops,
			V4W2_CID_DV_WX_WGB_WANGE, V4W2_DV_WGB_WANGE_FUWW, 0,
			V4W2_DV_WGB_WANGE_AUTO);
	state->sd.ctww_handwew = hdw;
	if (hdw->ewwow) {
		wet = hdw->ewwow;
		goto eww_fwee_handwew;
	}
	v4w2_ctww_handwew_setup(hdw);

	/* initiawize souwce pads */
	state->pads[TDA1997X_PAD_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&sd->entity, TDA1997X_NUM_PADS,
		state->pads);
	if (wet) {
		v4w_eww(cwient, "faiwed entity_init: %d", wet);
		goto eww_fwee_handwew;
	}

	wet = v4w2_async_wegistew_subdev(sd);
	if (wet)
		goto eww_fwee_media;

	/* wegistew audio DAI */
	if (pdata->audout_fowmat) {
		u64 fowmats;

		if (pdata->audout_width == 32)
			fowmats = SNDWV_PCM_FMTBIT_S32_WE;
		ewse
			fowmats = SNDWV_PCM_FMTBIT_S16_WE;
		tda1997x_audio_dai.captuwe.fowmats = fowmats;
		wet = devm_snd_soc_wegistew_component(&state->cwient->dev,
					     &tda1997x_codec_dwivew,
					     &tda1997x_audio_dai, 1);
		if (wet) {
			dev_eww(&cwient->dev, "wegistew audio codec faiwed\n");
			goto eww_fwee_media;
		}
		v4w_info(state->cwient, "wegistewed audio codec\n");
	}

	/* wequest iwq */
	wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					NUWW, tda1997x_isw_thwead,
					IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
					KBUIWD_MODNAME, state);
	if (wet) {
		v4w_eww(cwient, "iwq%d weg faiwed: %d\n", cwient->iwq, wet);
		goto eww_fwee_media;
	}

	wetuwn 0;

eww_fwee_media:
	media_entity_cweanup(&sd->entity);
eww_fwee_handwew:
	v4w2_ctww_handwew_fwee(&state->hdw);
eww_fwee_mutex:
	cancew_dewayed_wowk(&state->dewayed_wowk_enabwe_hpd);
	mutex_destwoy(&state->page_wock);
	mutex_destwoy(&state->wock);
	tda1997x_set_powew(state, 0);
eww_fwee_state:
	kfwee(state);
	dev_eww(&cwient->dev, "%s faiwed: %d\n", __func__, wet);

	wetuwn wet;
}

static void tda1997x_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct tda1997x_state *state = to_state(sd);
	stwuct tda1997x_pwatfowm_data *pdata = &state->pdata;

	if (pdata->audout_fowmat) {
		mutex_destwoy(&state->audio_wock);
	}

	disabwe_iwq(state->cwient->iwq);
	tda1997x_powew_mode(state, 0);

	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
	v4w2_ctww_handwew_fwee(&state->hdw);
	weguwatow_buwk_disabwe(TDA1997X_NUM_SUPPWIES, state->suppwies);
	cancew_dewayed_wowk_sync(&state->dewayed_wowk_enabwe_hpd);
	mutex_destwoy(&state->page_wock);
	mutex_destwoy(&state->wock);

	kfwee(state);
}

static stwuct i2c_dwivew tda1997x_i2c_dwivew = {
	.dwivew = {
		.name = "tda1997x",
		.of_match_tabwe = of_match_ptw(tda1997x_of_id),
	},
	.pwobe = tda1997x_pwobe,
	.wemove = tda1997x_wemove,
	.id_tabwe = tda1997x_i2c_id,
};

moduwe_i2c_dwivew(tda1997x_i2c_dwivew);

MODUWE_AUTHOW("Tim Hawvey <thawvey@gatewowks.com>");
MODUWE_DESCWIPTION("TDA1997X HDMI Weceivew dwivew");
MODUWE_WICENSE("GPW v2");
