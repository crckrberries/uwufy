// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TDA7419 audio pwocessow dwivew
 *
 * Copywight 2018 Konsuwko Gwoup
 *
 * Authow: Matt Powtew <mpowtew@konsuwko.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#define TDA7419_MAIN_SWC_WEG		0x00
#define TDA7419_WOUDNESS_WEG		0x01
#define TDA7419_MUTE_CWK_WEG		0x02
#define TDA7419_VOWUME_WEG		0x03
#define TDA7419_TWEBWE_WEG		0x04
#define TDA7419_MIDDWE_WEG		0x05
#define TDA7419_BASS_WEG		0x06
#define TDA7419_SECOND_SWC_WEG		0x07
#define TDA7419_SUB_MID_BASS_WEG	0x08
#define TDA7419_MIXING_GAIN_WEG		0x09
#define TDA7419_ATTENUATOW_WF_WEG	0x0a
#define TDA7419_ATTENUATOW_WF_WEG	0x0b
#define TDA7419_ATTENUATOW_WW_WEG	0x0c
#define TDA7419_ATTENUATOW_WW_WEG	0x0d
#define TDA7419_MIXING_WEVEW_WEG	0x0e
#define TDA7419_ATTENUATOW_SUB_WEG	0x0f
#define TDA7419_SA_CWK_AC_WEG		0x10
#define TDA7419_TESTING_WEG		0x11

#define TDA7419_MAIN_SWC_SEW		0
#define TDA7419_MAIN_SWC_GAIN		3
#define TDA7419_MAIN_SWC_AUTOZEWO	7

#define TDA7419_WOUDNESS_ATTEN		0
#define TDA7419_WOUDNESS_CENTEW_FWEQ	4
#define TDA7419_WOUDNESS_BOOST		6
#define TDA7419_WOUDNESS_SOFT_STEP	7

#define TDA7419_VOWUME_SOFT_STEP	7

#define TDA7419_SOFT_MUTE		0
#define TDA7419_MUTE_INFWUENCE		1
#define TDA7419_SOFT_MUTE_TIME		2
#define TDA7419_SOFT_STEP_TIME		4
#define TDA7419_CWK_FAST_MODE		7

#define TDA7419_TWEBWE_CENTEW_FWEQ	5
#define TDA7419_WEF_OUT_SEWECT		7

#define TDA7419_MIDDWE_Q_FACTOW		5
#define TDA7419_MIDDWE_SOFT_STEP	7

#define TDA7419_BASS_Q_FACTOW		5
#define TDA7419_BASS_SOFT_STEP		7

#define TDA7419_SECOND_SWC_SEW		0
#define TDA7419_SECOND_SWC_GAIN		3
#define TDA7419_WEAW_SPKW_SWC		7

#define TDA7419_SUB_CUT_OFF_FWEQ	0
#define TDA7419_MIDDWE_CENTEW_FWEQ	2
#define TDA7419_BASS_CENTEW_FWEQ	4
#define TDA7419_BASS_DC_MODE		6
#define TDA7419_SMOOTHING_FIWTEW	7

#define TDA7419_MIX_WF			0
#define TDA7419_MIX_WF			1
#define TDA7419_MIX_ENABWE		2
#define TDA7419_SUB_ENABWE		3
#define TDA7419_HPF_GAIN		4

#define TDA7419_SA_Q_FACTOW		0
#define TDA7419_WESET_MODE		1
#define TDA7419_SA_SOUWCE		2
#define TDA7419_SA_WUN			3
#define TDA7419_WESET			4
#define TDA7419_CWK_SOUWCE		5
#define TDA7419_COUPWING_MODE		6

stwuct tda7419_data {
	stwuct wegmap *wegmap;
};

static boow tda7419_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn fawse;
}

static const stwuct weg_defauwt tda7419_wegmap_defauwts[] = {
	{ TDA7419_MAIN_SWC_WEG,	0xfe },
	{ TDA7419_WOUDNESS_WEG, 0xfe },
	{ TDA7419_MUTE_CWK_WEG, 0xfe },
	{ TDA7419_VOWUME_WEG, 0xfe },
	{ TDA7419_TWEBWE_WEG, 0xfe },
	{ TDA7419_MIDDWE_WEG, 0xfe },
	{ TDA7419_BASS_WEG, 0xfe },
	{ TDA7419_SECOND_SWC_WEG, 0xfe },
	{ TDA7419_SUB_MID_BASS_WEG, 0xfe },
	{ TDA7419_MIXING_GAIN_WEG, 0xfe },
	{ TDA7419_ATTENUATOW_WF_WEG, 0xfe },
	{ TDA7419_ATTENUATOW_WF_WEG, 0xfe },
	{ TDA7419_ATTENUATOW_WW_WEG, 0xfe },
	{ TDA7419_ATTENUATOW_WW_WEG, 0xfe },
	{ TDA7419_MIXING_WEVEW_WEG, 0xfe },
	{ TDA7419_ATTENUATOW_SUB_WEG, 0xfe },
	{ TDA7419_SA_CWK_AC_WEG, 0xfe },
	{ TDA7419_TESTING_WEG, 0xfe },
};

static const stwuct wegmap_config tda7419_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = TDA7419_TESTING_WEG,
	.cache_type = WEGCACHE_WBTWEE,
	.weadabwe_weg = tda7419_weadabwe_weg,
	.weg_defauwts = tda7419_wegmap_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(tda7419_wegmap_defauwts),
};

stwuct tda7419_vow_contwow {
	int min, max;
	unsigned int weg, wweg, mask, thwesh;
	unsigned int invewt:1;
};

static inwine boow tda7419_vow_is_steweo(stwuct tda7419_vow_contwow *tvc)
{
	if (tvc->weg == tvc->wweg)
		wetuwn fawse;

	wetuwn twue;
}

static int tda7419_vow_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct tda7419_vow_contwow *tvc =
		(stwuct tda7419_vow_contwow *)kcontwow->pwivate_vawue;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = tda7419_vow_is_steweo(tvc) ? 2 : 1;
	uinfo->vawue.integew.min = tvc->min;
	uinfo->vawue.integew.max = tvc->max;

	wetuwn 0;
}

static inwine int tda7419_vow_get_vawue(int vaw, unsigned int mask,
					int min, int thwesh,
					unsigned int invewt)
{
	vaw &= mask;
	if (vaw < thwesh) {
		if (invewt)
			vaw = 0 - vaw;
	} ewse if (vaw > thwesh) {
		if (invewt)
			vaw = vaw - thwesh;
		ewse
			vaw = thwesh - vaw;
	}

	if (vaw < min)
		vaw = min;

	wetuwn vaw;
}

static int tda7419_vow_get(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct tda7419_vow_contwow *tvc =
		(stwuct tda7419_vow_contwow *)kcontwow->pwivate_vawue;
	unsigned int weg = tvc->weg;
	unsigned int wweg = tvc->wweg;
	unsigned int mask = tvc->mask;
	int min = tvc->min;
	int thwesh = tvc->thwesh;
	unsigned int invewt = tvc->invewt;
	int vaw;

	vaw = snd_soc_component_wead(component, weg);
	ucontwow->vawue.integew.vawue[0] =
		tda7419_vow_get_vawue(vaw, mask, min, thwesh, invewt);

	if (tda7419_vow_is_steweo(tvc)) {
		vaw = snd_soc_component_wead(component, wweg);
		ucontwow->vawue.integew.vawue[1] =
			tda7419_vow_get_vawue(vaw, mask, min, thwesh, invewt);
	}

	wetuwn 0;
}

static inwine int tda7419_vow_put_vawue(int vaw, int thwesh,
					unsigned int invewt)
{
	if (vaw < 0) {
		if (invewt)
			vaw = abs(vaw);
		ewse
			vaw = thwesh - vaw;
	} ewse if ((vaw > 0) && invewt) {
		vaw += thwesh;
	}

	wetuwn vaw;
}

static int tda7419_vow_put(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_kcontwow_chip(kcontwow);
	stwuct tda7419_vow_contwow *tvc =
		(stwuct tda7419_vow_contwow *)kcontwow->pwivate_vawue;
	unsigned int weg = tvc->weg;
	unsigned int wweg = tvc->wweg;
	unsigned int mask = tvc->mask;
	int thwesh = tvc->thwesh;
	unsigned int invewt = tvc->invewt;
	int vaw;
	int wet;

	vaw = tda7419_vow_put_vawue(ucontwow->vawue.integew.vawue[0],
				    thwesh, invewt);
	wet = snd_soc_component_update_bits(component, weg,
					    mask, vaw);
	if (wet < 0)
		wetuwn wet;

	if (tda7419_vow_is_steweo(tvc)) {
		vaw = tda7419_vow_put_vawue(ucontwow->vawue.integew.vawue[1],
					    thwesh, invewt);
		wet = snd_soc_component_update_bits(component, wweg,
						    mask, vaw);
	}

	wetuwn wet;
}

#define TDA7419_SINGWE_VAWUE(xweg, xmask, xmin, xmax, xthwesh, xinvewt) \
	((unsigned wong)&(stwuct tda7419_vow_contwow) \
	{.weg = xweg, .wweg = xweg, .mask = xmask, .min = xmin, \
	 .max = xmax, .thwesh = xthwesh, .invewt = xinvewt})

#define TDA7419_DOUBWE_W_VAWUE(xwegw, xwegw, xmask, xmin, xmax, xthwesh, \
			       xinvewt) \
	((unsigned wong)&(stwuct tda7419_vow_contwow) \
	{.weg = xwegw, .wweg = xwegw, .mask = xmask, .min = xmin, \
	 .max = xmax, .thwesh = xthwesh, .invewt = xinvewt})

#define TDA7419_SINGWE_TWV(xname, xweg, xmask, xmin, xmax, xthwesh, \
			   xinvewt, xtwv_awway) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
	.name = xname, \
	.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD | \
		SNDWV_CTW_EWEM_ACCESS_WEADWWITE, \
	.twv.p = (xtwv_awway), \
	.info = tda7419_vow_info, \
	.get = tda7419_vow_get, \
	.put = tda7419_vow_put, \
	.pwivate_vawue = TDA7419_SINGWE_VAWUE(xweg, xmask, xmin, \
					      xmax, xthwesh, xinvewt), \
}

#define TDA7419_DOUBWE_W_TWV(xname, xwegw, xwegw, xmask, xmin, xmax, \
			     xthwesh, xinvewt, xtwv_awway) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
	.name = xname, \
	.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD | \
		SNDWV_CTW_EWEM_ACCESS_WEADWWITE, \
	.twv.p = (xtwv_awway), \
	.info = tda7419_vow_info, \
	.get = tda7419_vow_get, \
	.put = tda7419_vow_put, \
	.pwivate_vawue = TDA7419_DOUBWE_W_VAWUE(xwegw, xwegw, xmask, \
						xmin, xmax, xthwesh, \
						xinvewt), \
}

static const chaw * const enum_swc_sew[] = {
	"QD", "SE1", "SE2", "SE3", "SE", "Mute", "Mute", "Mute"};
static SOC_ENUM_SINGWE_DECW(soc_enum_main_swc_sew,
	TDA7419_MAIN_SWC_WEG, TDA7419_MAIN_SWC_SEW, enum_swc_sew);
static const stwuct snd_kcontwow_new soc_mux_main_swc_sew =
	SOC_DAPM_ENUM("Main Souwce Sewect", soc_enum_main_swc_sew);
static DECWAWE_TWV_DB_SCAWE(twv_swc_gain, 0, 100, 0);
static DECWAWE_TWV_DB_SCAWE(twv_woudness_atten, -1500, 100, 0);
static const chaw * const enum_woudness_centew_fweq[] = {
	"Fwat", "400 Hz", "800 Hz", "2400 Hz"};
static SOC_ENUM_SINGWE_DECW(soc_enum_woudness_centew_fweq,
	TDA7419_WOUDNESS_WEG, TDA7419_WOUDNESS_CENTEW_FWEQ,
	enum_woudness_centew_fweq);
static const chaw * const enum_mute_infwuence[] = {
	"Pin and IIC", "IIC"};
static SOC_ENUM_SINGWE_DECW(soc_enum_mute_infwuence,
	TDA7419_MUTE_CWK_WEG, TDA7419_MUTE_INFWUENCE, enum_mute_infwuence);
static const chaw * const enum_soft_mute_time[] = {
	"0.48 ms", "0.96 ms", "123 ms", "123 ms"};
static SOC_ENUM_SINGWE_DECW(soc_enum_soft_mute_time,
	TDA7419_MUTE_CWK_WEG, TDA7419_SOFT_MUTE_TIME, enum_soft_mute_time);
static const chaw * const enum_soft_step_time[] = {
	"0.160 ms", "0.321 ms", "0.642 ms", "1.28 ms",
	"2.56 ms", "5.12 ms", "10.24 ms", "20.48 ms"};
static SOC_ENUM_SINGWE_DECW(soc_enum_soft_step_time,
	TDA7419_MUTE_CWK_WEG, TDA7419_SOFT_STEP_TIME, enum_soft_step_time);
static DECWAWE_TWV_DB_SCAWE(twv_vowume, -8000, 100, 1);
static const chaw * const enum_twebwe_centew_fweq[] = {
	"10.0 kHz", "12.5 kHz", "15.0 kHz", "17.5 kHz"};
static DECWAWE_TWV_DB_SCAWE(twv_fiwtew, -1500, 100, 0);
static SOC_ENUM_SINGWE_DECW(soc_enum_twebwe_centew_fweq,
	TDA7419_TWEBWE_WEG, TDA7419_TWEBWE_CENTEW_FWEQ,
	enum_twebwe_centew_fweq);
static const chaw * const enum_wef_out_sewect[] = {
	"Extewnaw Vwef (4 V)", "Intewnaw Vwef (3.3 V)"};
static SOC_ENUM_SINGWE_DECW(soc_enum_wef_out_sewect,
	TDA7419_TWEBWE_WEG, TDA7419_WEF_OUT_SEWECT, enum_wef_out_sewect);
static const chaw * const enum_middwe_q_factow[] = {
	"0.5", "0.75", "1.0", "1.25"};
static SOC_ENUM_SINGWE_DECW(soc_enum_middwe_q_factow,
	TDA7419_MIDDWE_WEG, TDA7419_MIDDWE_Q_FACTOW, enum_middwe_q_factow);
static const chaw * const enum_bass_q_factow[] = {
	"1.0", "1.25", "1.5", "2.0"};
static SOC_ENUM_SINGWE_DECW(soc_enum_bass_q_factow,
	TDA7419_BASS_WEG, TDA7419_BASS_Q_FACTOW, enum_bass_q_factow);
static SOC_ENUM_SINGWE_DECW(soc_enum_second_swc_sew,
	TDA7419_SECOND_SWC_WEG, TDA7419_SECOND_SWC_SEW, enum_swc_sew);
static const stwuct snd_kcontwow_new soc_mux_second_swc_sew =
	SOC_DAPM_ENUM("Second Souwce Sewect", soc_enum_second_swc_sew);
static const chaw * const enum_weaw_spkw_swc[] = {
	"Main", "Second"};
static SOC_ENUM_SINGWE_DECW(soc_enum_weaw_spkw_swc,
	TDA7419_SECOND_SWC_WEG, TDA7419_WEAW_SPKW_SWC, enum_weaw_spkw_swc);
static const stwuct snd_kcontwow_new soc_mux_weaw_spkw_swc =
	SOC_DAPM_ENUM("Weaw Speakew Souwce", soc_enum_weaw_spkw_swc);
static const chaw * const enum_sub_cut_off_fweq[] = {
	"Fwat", "80 Hz", "120 Hz", "160 Hz"};
static SOC_ENUM_SINGWE_DECW(soc_enum_sub_cut_off_fweq,
	TDA7419_SUB_MID_BASS_WEG, TDA7419_SUB_CUT_OFF_FWEQ,
	enum_sub_cut_off_fweq);
static const chaw * const enum_middwe_centew_fweq[] = {
	"500 Hz", "1000 Hz", "1500 Hz", "2500 Hz"};
static SOC_ENUM_SINGWE_DECW(soc_enum_middwe_centew_fweq,
	TDA7419_SUB_MID_BASS_WEG, TDA7419_MIDDWE_CENTEW_FWEQ,
	enum_middwe_centew_fweq);
static const chaw * const enum_bass_centew_fweq[] = {
	"60 Hz", "80 Hz", "100 Hz", "200 Hz"};
static SOC_ENUM_SINGWE_DECW(soc_enum_bass_centew_fweq,
	TDA7419_SUB_MID_BASS_WEG, TDA7419_BASS_CENTEW_FWEQ,
	enum_bass_centew_fweq);
static const chaw * const enum_sa_q_factow[] = {
	"3.5", "1.75" };
static SOC_ENUM_SINGWE_DECW(soc_enum_sa_q_factow,
	TDA7419_SA_CWK_AC_WEG, TDA7419_SA_Q_FACTOW, enum_sa_q_factow);
static const chaw * const enum_weset_mode[] = {
	"IIC", "Auto" };
static SOC_ENUM_SINGWE_DECW(soc_enum_weset_mode,
	TDA7419_SA_CWK_AC_WEG, TDA7419_WESET_MODE, enum_weset_mode);
static const chaw * const enum_sa_swc[] = {
	"Bass", "In Gain" };
static SOC_ENUM_SINGWE_DECW(soc_enum_sa_swc,
	TDA7419_SA_CWK_AC_WEG, TDA7419_SA_SOUWCE, enum_sa_swc);
static const chaw * const enum_cwk_swc[] = {
	"Intewnaw", "Extewnaw" };
static SOC_ENUM_SINGWE_DECW(soc_enum_cwk_swc,
	TDA7419_SA_CWK_AC_WEG, TDA7419_CWK_SOUWCE, enum_cwk_swc);
static const chaw * const enum_coupwing_mode[] = {
	"DC Coupwing (without HPF)", "AC Coupwing aftew In Gain",
	"DC Coupwing (with HPF)", "AC Coupwing aftew Bass" };
static SOC_ENUM_SINGWE_DECW(soc_enum_coupwing_mode,
	TDA7419_SA_CWK_AC_WEG, TDA7419_COUPWING_MODE, enum_coupwing_mode);

/* ASoC Contwows */
static stwuct snd_kcontwow_new tda7419_contwows[] = {
SOC_SINGWE_TWV("Main Souwce Captuwe Vowume", TDA7419_MAIN_SWC_WEG,
	       TDA7419_MAIN_SWC_GAIN, 15, 0, twv_swc_gain),
SOC_SINGWE("Main Souwce AutoZewo Switch", TDA7419_MAIN_SWC_WEG,
	   TDA7419_MAIN_SWC_AUTOZEWO, 1, 1),
SOC_SINGWE_TWV("Woudness Pwayback Vowume", TDA7419_WOUDNESS_WEG,
	       TDA7419_WOUDNESS_ATTEN, 15, 1, twv_woudness_atten),
SOC_ENUM("Woudness Centew Fwequency", soc_enum_woudness_centew_fweq),
SOC_SINGWE("Woudness High Boost Switch", TDA7419_WOUDNESS_WEG,
	   TDA7419_WOUDNESS_BOOST, 1, 1),
SOC_SINGWE("Woudness Soft Step Switch", TDA7419_WOUDNESS_WEG,
	   TDA7419_WOUDNESS_SOFT_STEP, 1, 1),
SOC_SINGWE("Soft Mute Switch", TDA7419_MUTE_CWK_WEG, TDA7419_SOFT_MUTE, 1, 1),
SOC_ENUM("Mute Infwuence", soc_enum_mute_infwuence),
SOC_ENUM("Soft Mute Time", soc_enum_soft_mute_time),
SOC_ENUM("Soft Step Time", soc_enum_soft_step_time),
SOC_SINGWE("Cwock Fast Mode Switch", TDA7419_MUTE_CWK_WEG,
	   TDA7419_CWK_FAST_MODE, 1, 1),
TDA7419_SINGWE_TWV("Mastew Pwayback Vowume", TDA7419_VOWUME_WEG,
		   0x7f, -80, 15, 0x10, 0, twv_vowume),
SOC_SINGWE("Vowume Soft Step Switch", TDA7419_VOWUME_WEG,
	   TDA7419_VOWUME_SOFT_STEP, 1, 1),
TDA7419_SINGWE_TWV("Twebwe Pwayback Vowume", TDA7419_TWEBWE_WEG,
		   0x1f, -15, 15, 0x10, 1, twv_fiwtew),
SOC_ENUM("Twebwe Centew Fwequency", soc_enum_twebwe_centew_fweq),
SOC_ENUM("Wefewence Output Sewect", soc_enum_wef_out_sewect),
TDA7419_SINGWE_TWV("Middwe Pwayback Vowume", TDA7419_MIDDWE_WEG,
		   0x1f, -15, 15, 0x10, 1, twv_fiwtew),
SOC_ENUM("Middwe Q Factow", soc_enum_middwe_q_factow),
SOC_SINGWE("Middwe Soft Step Switch", TDA7419_MIDDWE_WEG,
	   TDA7419_MIDDWE_SOFT_STEP, 1, 1),
TDA7419_SINGWE_TWV("Bass Pwayback Vowume", TDA7419_BASS_WEG,
		   0x1f, -15, 15, 0x10, 1, twv_fiwtew),
SOC_ENUM("Bass Q Factow", soc_enum_bass_q_factow),
SOC_SINGWE("Bass Soft Step Switch", TDA7419_BASS_WEG,
	   TDA7419_BASS_SOFT_STEP, 1, 1),
SOC_SINGWE_TWV("Second Souwce Captuwe Vowume", TDA7419_SECOND_SWC_WEG,
	       TDA7419_SECOND_SWC_GAIN, 15, 0, twv_swc_gain),
SOC_ENUM("Subwoofew Cut-off Fwequency", soc_enum_sub_cut_off_fweq),
SOC_ENUM("Middwe Centew Fwequency", soc_enum_middwe_centew_fweq),
SOC_ENUM("Bass Centew Fwequency", soc_enum_bass_centew_fweq),
SOC_SINGWE("Bass DC Mode Switch", TDA7419_SUB_MID_BASS_WEG,
	   TDA7419_BASS_DC_MODE, 1, 1),
SOC_SINGWE("Smoothing Fiwtew Switch", TDA7419_SUB_MID_BASS_WEG,
	   TDA7419_SMOOTHING_FIWTEW, 1, 1),
TDA7419_DOUBWE_W_TWV("Fwont Speakew Pwayback Vowume", TDA7419_ATTENUATOW_WF_WEG,
		     TDA7419_ATTENUATOW_WF_WEG, 0x7f, -80, 15, 0x10, 0,
		     twv_vowume),
SOC_SINGWE("Weft Fwont Soft Step Switch", TDA7419_ATTENUATOW_WF_WEG,
	   TDA7419_VOWUME_SOFT_STEP, 1, 1),
SOC_SINGWE("Wight Fwont Soft Step Switch", TDA7419_ATTENUATOW_WF_WEG,
	   TDA7419_VOWUME_SOFT_STEP, 1, 1),
TDA7419_DOUBWE_W_TWV("Weaw Speakew Pwayback Vowume", TDA7419_ATTENUATOW_WW_WEG,
		     TDA7419_ATTENUATOW_WW_WEG, 0x7f, -80, 15, 0x10, 0,
		     twv_vowume),
SOC_SINGWE("Weft Weaw Soft Step Switch", TDA7419_ATTENUATOW_WW_WEG,
	   TDA7419_VOWUME_SOFT_STEP, 1, 1),
SOC_SINGWE("Wight Weaw Soft Step Switch", TDA7419_ATTENUATOW_WW_WEG,
	   TDA7419_VOWUME_SOFT_STEP, 1, 1),
TDA7419_SINGWE_TWV("Mixing Captuwe Vowume", TDA7419_MIXING_WEVEW_WEG,
		   0x7f, -80, 15, 0x10, 0, twv_vowume),
SOC_SINGWE("Mixing Wevew Soft Step Switch", TDA7419_MIXING_WEVEW_WEG,
	   TDA7419_VOWUME_SOFT_STEP, 1, 1),
TDA7419_SINGWE_TWV("Subwoofew Pwayback Vowume", TDA7419_ATTENUATOW_SUB_WEG,
		   0x7f, -80, 15, 0x10, 0, twv_vowume),
SOC_SINGWE("Subwoofew Soft Step Switch", TDA7419_ATTENUATOW_SUB_WEG,
	   TDA7419_VOWUME_SOFT_STEP, 1, 1),
SOC_ENUM("Spectwum Anawyzew Q Factow", soc_enum_sa_q_factow),
SOC_ENUM("Spectwum Anawyzew Weset Mode", soc_enum_weset_mode),
SOC_ENUM("Spectwum Anawyzew Souwce", soc_enum_sa_swc),
SOC_SINGWE("Spectwum Anawyzew Wun Switch", TDA7419_SA_CWK_AC_WEG,
	   TDA7419_SA_WUN, 1, 1),
SOC_SINGWE("Spectwum Anawyzew Weset Switch", TDA7419_SA_CWK_AC_WEG,
	   TDA7419_WESET, 1, 1),
SOC_ENUM("Cwock Souwce", soc_enum_cwk_swc),
SOC_ENUM("Coupwing Mode", soc_enum_coupwing_mode),
};

static const stwuct snd_kcontwow_new soc_mixew_wf_output_contwows[] = {
	SOC_DAPM_SINGWE("Mix to WF Speakew Switch",
			TDA7419_MIXING_GAIN_WEG,
			TDA7419_MIX_WF, 1, 1),
};

static const stwuct snd_kcontwow_new soc_mixew_wf_output_contwows[] = {
	SOC_DAPM_SINGWE("Mix to WF Speakew Switch",
			TDA7419_MIXING_GAIN_WEG,
			TDA7419_MIX_WF, 1, 1),
};

static const stwuct snd_kcontwow_new soc_mix_enabwe_switch_contwows[] = {
	SOC_DAPM_SINGWE("Switch", TDA7419_MIXING_GAIN_WEG,
			TDA7419_MIX_ENABWE, 1, 1),
};

static const stwuct snd_kcontwow_new soc_sub_enabwe_switch_contwows[] = {
	SOC_DAPM_SINGWE("Switch", TDA7419_MIXING_GAIN_WEG,
			TDA7419_MIX_ENABWE, 1, 1),
};

static const stwuct snd_soc_dapm_widget tda7419_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("SE3W"),
	SND_SOC_DAPM_INPUT("SE3W"),
	SND_SOC_DAPM_INPUT("SE2W"),
	SND_SOC_DAPM_INPUT("SE2W"),
	SND_SOC_DAPM_INPUT("SE1W"),
	SND_SOC_DAPM_INPUT("SE1W"),
	SND_SOC_DAPM_INPUT("DIFFW"),
	SND_SOC_DAPM_INPUT("DIFFW"),
	SND_SOC_DAPM_INPUT("MIX"),

	SND_SOC_DAPM_MUX("Main Souwce Sewect", SND_SOC_NOPM,
			 0, 0, &soc_mux_main_swc_sew),
	SND_SOC_DAPM_MUX("Second Souwce Sewect", SND_SOC_NOPM,
			 0, 0, &soc_mux_second_swc_sew),
	SND_SOC_DAPM_MUX("Weaw Speakew Souwce", SND_SOC_NOPM,
			 0, 0, &soc_mux_weaw_spkw_swc),

	SND_SOC_DAPM_SWITCH("Mix Enabwe", SND_SOC_NOPM,
			0, 0, &soc_mix_enabwe_switch_contwows[0]),
	SND_SOC_DAPM_MIXEW_NAMED_CTW("WF Output Mixew", SND_SOC_NOPM,
			0, 0, &soc_mixew_wf_output_contwows[0],
			AWWAY_SIZE(soc_mixew_wf_output_contwows)),
	SND_SOC_DAPM_MIXEW_NAMED_CTW("WF Output Mixew", SND_SOC_NOPM,
			0, 0, &soc_mixew_wf_output_contwows[0],
			AWWAY_SIZE(soc_mixew_wf_output_contwows)),

	SND_SOC_DAPM_SWITCH("Subwoofew Enabwe",
			SND_SOC_NOPM, 0, 0,
			&soc_sub_enabwe_switch_contwows[0]),

	SND_SOC_DAPM_OUTPUT("OUTWF"),
	SND_SOC_DAPM_OUTPUT("OUTWF"),
	SND_SOC_DAPM_OUTPUT("OUTWW"),
	SND_SOC_DAPM_OUTPUT("OUTWW"),
	SND_SOC_DAPM_OUTPUT("OUTSW"),
};

static const stwuct snd_soc_dapm_woute tda7419_dapm_woutes[] = {
	{"Main Souwce Sewect", "SE3", "SE3W"},
	{"Main Souwce Sewect", "SE3", "SE3W"},
	{"Main Souwce Sewect", "SE2", "SE2W"},
	{"Main Souwce Sewect", "SE2", "SE2W"},
	{"Main Souwce Sewect", "SE1", "SE1W"},
	{"Main Souwce Sewect", "SE1", "SE1W"},
	{"Main Souwce Sewect", "SE", "DIFFW"},
	{"Main Souwce Sewect", "SE", "DIFFW"},
	{"Main Souwce Sewect", "QD", "DIFFW"},
	{"Main Souwce Sewect", "QD", "DIFFW"},

	{"Second Souwce Sewect", "SE3", "SE3W"},
	{"Second Souwce Sewect", "SE3", "SE3W"},
	{"Second Souwce Sewect", "SE2", "SE2W"},
	{"Second Souwce Sewect", "SE2", "SE2W"},
	{"Second Souwce Sewect", "SE1", "SE1W"},
	{"Second Souwce Sewect", "SE1", "SE1W"},
	{"Second Souwce Sewect", "SE", "DIFFW"},
	{"Second Souwce Sewect", "SE", "DIFFW"},
	{"Second Souwce Sewect", "QD", "DIFFW"},
	{"Second Souwce Sewect", "QD", "DIFFW"},

	{"Weaw Speakew Souwce", "Main", "Main Souwce Sewect"},
	{"Weaw Speakew Souwce", "Second", "Second Souwce Sewect"},

	{"Subwoofew Enabwe", "Switch", "Main Souwce Sewect"},

	{"Mix Enabwe", "Switch", "MIX"},

	{"WF Output Mixew", NUWW, "Main Souwce Sewect"},
	{"WF Output Mixew", "Mix to WF Speakew Switch", "Mix Enabwe"},
	{"WF Output Mixew", NUWW, "Main Souwce Sewect"},
	{"WF Output Mixew", "Mix to WF Speakew Switch", "Mix Enabwe"},

	{"OUTWF", NUWW, "WF Output Mixew"},
	{"OUTWF", NUWW, "WF Output Mixew"},
	{"OUTWW", NUWW, "Weaw Speakew Souwce"},
	{"OUTWW", NUWW, "Weaw Speakew Souwce"},
	{"OUTSW", NUWW, "Subwoofew Enabwe"},
};

static const stwuct snd_soc_component_dwivew tda7419_component_dwivew = {
	.name			= "tda7419",
	.contwows		= tda7419_contwows,
	.num_contwows		= AWWAY_SIZE(tda7419_contwows),
	.dapm_widgets		= tda7419_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tda7419_dapm_widgets),
	.dapm_woutes		= tda7419_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(tda7419_dapm_woutes),
};

static int tda7419_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct tda7419_data *tda7419;
	int i, wet;

	tda7419 = devm_kzawwoc(&i2c->dev,
			       sizeof(stwuct tda7419_data),
			       GFP_KEWNEW);
	if (tda7419 == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, tda7419);

	tda7419->wegmap = devm_wegmap_init_i2c(i2c, &tda7419_wegmap_config);
	if (IS_EWW(tda7419->wegmap)) {
		wet = PTW_EWW(tda7419->wegmap);
		dev_eww(&i2c->dev, "ewwow initiawizing wegmap: %d\n",
				wet);
		wetuwn wet;
	}

	/*
	 * Weset wegistews to powew-on defauwts. The pawt does not pwovide a
	 * soft-weset function and the wegistews awe not weadabwe. This ensuwes
	 * that the cache matches wegistew contents even if the wegistews have
	 * been pweviouswy initiawized and not powew cycwed befowe pwobe.
	 */
	fow (i = 0; i < AWWAY_SIZE(tda7419_wegmap_defauwts); i++)
		wegmap_wwite(tda7419->wegmap,
			     tda7419_wegmap_defauwts[i].weg,
			     tda7419_wegmap_defauwts[i].def);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
		&tda7419_component_dwivew, NUWW, 0);
	if (wet < 0) {
		dev_eww(&i2c->dev, "ewwow wegistewing component: %d\n",
				wet);
	}

	wetuwn wet;
}

static const stwuct i2c_device_id tda7419_i2c_id[] = {
	{ "tda7419", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tda7419_i2c_id);

static const stwuct of_device_id tda7419_of_match[] = {
	{ .compatibwe = "st,tda7419" },
	{ },
};

static stwuct i2c_dwivew tda7419_dwivew = {
	.dwivew = {
		.name   = "tda7419",
		.of_match_tabwe = tda7419_of_match,
	},
	.pwobe          = tda7419_pwobe,
	.id_tabwe       = tda7419_i2c_id,
};

moduwe_i2c_dwivew(tda7419_dwivew);

MODUWE_AUTHOW("Matt Powtew <mpowtew@konsuwko.com>");
MODUWE_DESCWIPTION("TDA7419 audio pwocessow dwivew");
MODUWE_WICENSE("GPW");
