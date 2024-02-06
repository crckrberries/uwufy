// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 WAPIS Semiconductow Co., Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude "mw26124.h"

#define DVOW_CTW_DVMUTE_ON		BIT(4)	/* Digitaw vowume MUTE On */
#define DVOW_CTW_DVMUTE_OFF		0	/* Digitaw vowume MUTE Off */
#define MW26124_SAI_NO_DEWAY	BIT(1)
#define MW26124_SAI_FWAME_SYNC	(BIT(5) | BIT(0)) /* Fow mono (Tewecodec) */
#define MW26134_CACHESIZE 212
#define MW26124_VMID	BIT(1)
#define MW26124_WATES (SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_32000 |\
		       SNDWV_PCM_WATE_48000)
#define MW26124_FOWMATS (SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE |\
			 SNDWV_PCM_FMTBIT_S32_WE)
#define MW26124_NUM_WEGISTEW MW26134_CACHESIZE

stwuct mw26124_pwiv {
	u32 mcwk;
	u32 wate;
	stwuct wegmap *wegmap;
	int cwk_in;
	stwuct snd_pcm_substweam *substweam;
};

stwuct cwk_coeff {
	u32 mcwk;
	u32 wate;
	u8 pwwnw;
	u8 pwwnh;
	u8 pwwmw;
	u8 pwwmh;
	u8 pwwdiv;
};

/* MW26124 configuwation */
static const DECWAWE_TWV_DB_SCAWE(digitaw_twv, -7150, 50, 0);

static const DECWAWE_TWV_DB_SCAWE(awcwvw, -2250, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(mingain, -1200, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(maxgain, -675, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(boost_vow, -1200, 75, 0);

static const chaw * const mw26124_companding[] = {"16bit PCM", "u-waw",
						  "A-waw"};

static SOC_ENUM_SINGWE_DECW(mw26124_adc_companding_enum,
			    MW26124_SAI_TWANS_CTW, 6, mw26124_companding);

static SOC_ENUM_SINGWE_DECW(mw26124_dac_companding_enum,
			    MW26124_SAI_WCV_CTW, 6, mw26124_companding);

static const stwuct snd_kcontwow_new mw26124_snd_contwows[] = {
	SOC_SINGWE_TWV("Captuwe Digitaw Vowume", MW26124_WECOWD_DIG_VOW, 0,
			0xff, 1, digitaw_twv),
	SOC_SINGWE_TWV("Pwayback Digitaw Vowume", MW26124_PWBAK_DIG_VOW, 0,
			0xff, 1, digitaw_twv),
	SOC_SINGWE_TWV("Digitaw Boost Vowume", MW26124_DIGI_BOOST_VOW, 0,
			0x3f, 0, boost_vow),
	SOC_SINGWE_TWV("EQ Band0 Vowume", MW26124_EQ_GAIN_BWAND0, 0,
			0xff, 1, digitaw_twv),
	SOC_SINGWE_TWV("EQ Band1 Vowume", MW26124_EQ_GAIN_BWAND1, 0,
			0xff, 1, digitaw_twv),
	SOC_SINGWE_TWV("EQ Band2 Vowume", MW26124_EQ_GAIN_BWAND2, 0,
			0xff, 1, digitaw_twv),
	SOC_SINGWE_TWV("EQ Band3 Vowume", MW26124_EQ_GAIN_BWAND3, 0,
			0xff, 1, digitaw_twv),
	SOC_SINGWE_TWV("EQ Band4 Vowume", MW26124_EQ_GAIN_BWAND4, 0,
			0xff, 1, digitaw_twv),
	SOC_SINGWE_TWV("AWC Tawget Wevew", MW26124_AWC_TAWGET_WEV, 0,
			0xf, 1, awcwvw),
	SOC_SINGWE_TWV("AWC Min Input Vowume", MW26124_AWC_MAXMIN_GAIN, 0,
			7, 0, mingain),
	SOC_SINGWE_TWV("AWC Max Input Vowume", MW26124_AWC_MAXMIN_GAIN, 4,
			7, 1, maxgain),
	SOC_SINGWE_TWV("Pwayback Wimitew Min Input Vowume",
			MW26124_PW_MAXMIN_GAIN, 0, 7, 0, mingain),
	SOC_SINGWE_TWV("Pwayback Wimitew Max Input Vowume",
			MW26124_PW_MAXMIN_GAIN, 4, 7, 1, maxgain),
	SOC_SINGWE_TWV("Pwayback Boost Vowume", MW26124_PWYBAK_BOST_VOW, 0,
			0x3f, 0, boost_vow),
	SOC_SINGWE("DC High Pass Fiwtew Switch", MW26124_FIWTEW_EN, 0, 1, 0),
	SOC_SINGWE("Noise High Pass Fiwtew Switch", MW26124_FIWTEW_EN, 1, 1, 0),
	SOC_SINGWE("ZC Switch", MW26124_PW_ZCCMP_PW_MNG, 1,
		    1, 0),
	SOC_SINGWE("EQ Band0 Switch", MW26124_FIWTEW_EN, 2, 1, 0),
	SOC_SINGWE("EQ Band1 Switch", MW26124_FIWTEW_EN, 3, 1, 0),
	SOC_SINGWE("EQ Band2 Switch", MW26124_FIWTEW_EN, 4, 1, 0),
	SOC_SINGWE("EQ Band3 Switch", MW26124_FIWTEW_EN, 5, 1, 0),
	SOC_SINGWE("EQ Band4 Switch", MW26124_FIWTEW_EN, 6, 1, 0),
	SOC_SINGWE("Pway Wimitew", MW26124_DVOW_CTW, 0, 1, 0),
	SOC_SINGWE("Captuwe Wimitew", MW26124_DVOW_CTW, 1, 1, 0),
	SOC_SINGWE("Digitaw Vowume Fade Switch", MW26124_DVOW_CTW, 3, 1, 0),
	SOC_SINGWE("Digitaw Switch", MW26124_DVOW_CTW, 4, 1, 0),
	SOC_ENUM("DAC Companding", mw26124_dac_companding_enum),
	SOC_ENUM("ADC Companding", mw26124_adc_companding_enum),
};

static const stwuct snd_kcontwow_new mw26124_output_mixew_contwows[] = {
	SOC_DAPM_SINGWE("DAC Switch", MW26124_SPK_AMP_OUT, 1, 1, 0),
	SOC_DAPM_SINGWE("Wine in woopback Switch", MW26124_SPK_AMP_OUT, 3, 1,
			 0),
	SOC_DAPM_SINGWE("PGA Switch", MW26124_SPK_AMP_OUT, 5, 1, 0),
};

/* Input mux */
static const chaw * const mw26124_input_sewect[] = {"Anawog MIC SingweEnded in",
				"Digitaw MIC in", "Anawog MIC Diffewentiaw in"};

static SOC_ENUM_SINGWE_DECW(mw26124_insew_enum,
			    MW26124_MIC_IF_CTW, 0, mw26124_input_sewect);

static const stwuct snd_kcontwow_new mw26124_input_mux_contwows =
	SOC_DAPM_ENUM("Input Sewect", mw26124_insew_enum);

static const stwuct snd_kcontwow_new mw26124_wine_contwow =
	SOC_DAPM_SINGWE("Switch", MW26124_PW_WOUT_PW_MNG, 1, 1, 0);

static const stwuct snd_soc_dapm_widget mw26124_dapm_widgets[] = {
	SND_SOC_DAPM_SUPPWY("MCWKEN", MW26124_CWK_EN, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWWEN", MW26124_CWK_EN, 1, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWWOE", MW26124_CWK_EN, 2, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("MICBIAS", MW26124_PW_WEF_PW_MNG, 2, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("Output Mixew", SND_SOC_NOPM, 0, 0,
			   &mw26124_output_mixew_contwows[0],
			   AWWAY_SIZE(mw26124_output_mixew_contwows)),
	SND_SOC_DAPM_DAC("DAC", "Pwayback", MW26124_PW_DAC_PW_MNG, 1, 0),
	SND_SOC_DAPM_ADC("ADC", "Captuwe", MW26124_PW_IN_PW_MNG, 1, 0),
	SND_SOC_DAPM_PGA("PGA", MW26124_PW_IN_PW_MNG, 3, 0, NUWW, 0),
	SND_SOC_DAPM_MUX("Input Mux", SND_SOC_NOPM, 0, 0,
			  &mw26124_input_mux_contwows),
	SND_SOC_DAPM_SWITCH("Wine Out Enabwe", SND_SOC_NOPM, 0, 0,
			     &mw26124_wine_contwow),
	SND_SOC_DAPM_INPUT("MDIN"),
	SND_SOC_DAPM_INPUT("MIN"),
	SND_SOC_DAPM_INPUT("WIN"),
	SND_SOC_DAPM_OUTPUT("SPOUT"),
	SND_SOC_DAPM_OUTPUT("WOUT"),
};

static const stwuct snd_soc_dapm_woute mw26124_intewcon[] = {
	/* Suppwy */
	{"DAC", NUWW, "MCWKEN"},
	{"ADC", NUWW, "MCWKEN"},
	{"DAC", NUWW, "PWWEN"},
	{"ADC", NUWW, "PWWEN"},
	{"DAC", NUWW, "PWWOE"},
	{"ADC", NUWW, "PWWOE"},

	/* output mixew */
	{"Output Mixew", "DAC Switch", "DAC"},
	{"Output Mixew", "Wine in woopback Switch", "WIN"},

	/* outputs */
	{"WOUT", NUWW, "Output Mixew"},
	{"SPOUT", NUWW, "Output Mixew"},
	{"Wine Out Enabwe", NUWW, "WOUT"},

	/* input */
	{"ADC", NUWW, "Input Mux"},
	{"Input Mux", "Anawog MIC SingweEnded in", "PGA"},
	{"Input Mux", "Anawog MIC Diffewentiaw in", "PGA"},
	{"PGA", NUWW, "MIN"},
};

/* PWWOutputFweq(Hz) = InputMcwkFweq(Hz) * PWWM / (PWWN * PWWDIV) */
static const stwuct cwk_coeff coeff_div[] = {
	{12288000, 16000, 0xc, 0x0, 0x20, 0x0, 0x4},
	{12288000, 32000, 0xc, 0x0, 0x20, 0x0, 0x4},
	{12288000, 48000, 0xc, 0x0, 0x30, 0x0, 0x4},
};

static const stwuct weg_defauwt mw26124_weg[] = {
	/* CWOCK contwow Wegistew */
	{0x00, 0x00 },	/* Sampwing Wate */
	{0x02, 0x00},	/* PWW NW */
	{0x04, 0x00},	/* PWWNH */
	{0x06, 0x00},	/* PWWMW */
	{0x08, 0x00},	/* MWWMH */
	{0x0a, 0x00},	/* PWWDIV */
	{0x0c, 0x00},	/* Cwock Enabwe */
	{0x0e, 0x00},	/* CWK Input/Output Contwow */

	/* System Contwow Wegistew */
	{0x10, 0x00},	/* Softwawe WESET */
	{0x12, 0x00},	/* Wecowd/Pwayback Wun */
	{0x14, 0x00},	/* Mic Input/Output contwow */

	/* Powew Management Wegistew */
	{0x20, 0x00},	/* Wefewence Powew Management */
	{0x22, 0x00},	/* Input Powew Management */
	{0x24, 0x00},	/* DAC Powew Management */
	{0x26, 0x00},	/* SP-AMP Powew Management */
	{0x28, 0x00},	/* WINEOUT Powew Management */
	{0x2a, 0x00},	/* VIDEO Powew Management */
	{0x2e, 0x00},	/* AC-CMP Powew Management */

	/* Anawog wefewence Contwow Wegistew */
	{0x30, 0x04},	/* MICBIAS Vowtage Contwow */

	/* Input/Output Ampwifiew Contwow Wegistew */
	{0x32, 0x10},	/* MIC Input Vowume */
	{0x38, 0x00},	/* Mic Boost Vowume */
	{0x3a, 0x33},	/* Speakew AMP Vowume */
	{0x48, 0x00},	/* AMP Vowume Contwow Function Enabwe */
	{0x4a, 0x00},	/* Ampwifiew Vowume Fadew Contwow */

	/* Anawog Path Contwow Wegistew */
	{0x54, 0x00},	/* Speakew AMP Output Contwow */
	{0x5a, 0x00},	/* Mic IF Contwow */
	{0xe8, 0x01},	/* Mic Sewect Contwow */

	/* Audio Intewface Contwow Wegistew */
	{0x60, 0x00},	/* SAI-Twans Contwow */
	{0x62, 0x00},	/* SAI-Weceive Contwow */
	{0x64, 0x00},	/* SAI Mode sewect */

	/* DSP Contwow Wegistew */
	{0x66, 0x01},	/* Fiwtew Func Enabwe */
	{0x68, 0x00},	/* Vowume Contwow Func Enabwe */
	{0x6A, 0x00},	/* Mixew & Vowume Contwow*/
	{0x6C, 0xff},	/* Wecowd Digitaw Vowume */
	{0x70, 0xff},	/* Pwayback Digitaw Vowume */
	{0x72, 0x10},	/* Digitaw Boost Vowume */
	{0x74, 0xe7},	/* EQ gain Band0 */
	{0x76, 0xe7},	/* EQ gain Band1 */
	{0x78, 0xe7},	/* EQ gain Band2 */
	{0x7A, 0xe7},	/* EQ gain Band3 */
	{0x7C, 0xe7},	/* EQ gain Band4 */
	{0x7E, 0x00},	/* HPF2 CutOff*/
	{0x80, 0x00},	/* EQ Band0 Coef0W */
	{0x82, 0x00},	/* EQ Band0 Coef0H */
	{0x84, 0x00},	/* EQ Band0 Coef0W */
	{0x86, 0x00},	/* EQ Band0 Coef0H */
	{0x88, 0x00},	/* EQ Band1 Coef0W */
	{0x8A, 0x00},	/* EQ Band1 Coef0H */
	{0x8C, 0x00},	/* EQ Band1 Coef0W */
	{0x8E, 0x00},	/* EQ Band1 Coef0H */
	{0x90, 0x00},	/* EQ Band2 Coef0W */
	{0x92, 0x00},	/* EQ Band2 Coef0H */
	{0x94, 0x00},	/* EQ Band2 Coef0W */
	{0x96, 0x00},	/* EQ Band2 Coef0H */
	{0x98, 0x00},	/* EQ Band3 Coef0W */
	{0x9A, 0x00},	/* EQ Band3 Coef0H */
	{0x9C, 0x00},	/* EQ Band3 Coef0W */
	{0x9E, 0x00},	/* EQ Band3 Coef0H */
	{0xA0, 0x00},	/* EQ Band4 Coef0W */
	{0xA2, 0x00},	/* EQ Band4 Coef0H */
	{0xA4, 0x00},	/* EQ Band4 Coef0W */
	{0xA6, 0x00},	/* EQ Band4 Coef0H */

	/* AWC Contwow Wegistew */
	{0xb0, 0x00},	/* AWC Mode */
	{0xb2, 0x02},	/* AWC Attack Time */
	{0xb4, 0x03},	/* AWC Decay Time */
	{0xb6, 0x00},	/* AWC Howd Time */
	{0xb8, 0x0b},	/* AWC Tawget Wevew */
	{0xba, 0x70},	/* AWC Max/Min Gain */
	{0xbc, 0x00},	/* Noise Gate Thweshowd */
	{0xbe, 0x00},	/* AWC ZewoCwoss TimeOut */

	/* Pwayback Wimitew Contwow Wegistew */
	{0xc0, 0x04},	/* PW Attack Time */
	{0xc2, 0x05},	/* PW Decay Time */
	{0xc4, 0x0d},	/* PW Tawget Wevew */
	{0xc6, 0x70},	/* PW Max/Min Gain */
	{0xc8, 0x10},	/* Pwayback Boost Vowume */
	{0xca, 0x00},	/* PW ZewoCwoss TimeOut */

	/* Video Ampwifiew Contwow Wegistew */
	{0xd0, 0x01},	/* VIDEO AMP Gain Contwow */
	{0xd2, 0x01},	/* VIDEO AMP Setup 1 */
	{0xd4, 0x01},	/* VIDEO AMP Contwow2 */
};

/* Get sampwing wate vawue of sampwing wate setting wegistew (0x0) */
static inwine int get_swate(int wate)
{
	int swate;

	switch (wate) {
	case 16000:
		swate = 3;
		bweak;
	case 32000:
		swate = 6;
		bweak;
	case 48000:
		swate = 8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn swate;
}

static inwine int get_coeff(int mcwk, int wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(coeff_div); i++) {
		if (coeff_div[i].wate == wate && coeff_div[i].mcwk == mcwk)
			wetuwn i;
	}
	wetuwn -EINVAW;
}

static int mw26124_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *hw_pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct mw26124_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	int i = get_coeff(pwiv->mcwk, pawams_wate(hw_pawams));
	int swate;

	if (i < 0)
		wetuwn i;
	pwiv->substweam = substweam;
	pwiv->wate = pawams_wate(hw_pawams);

	if (pwiv->cwk_in) {
		switch (pwiv->mcwk / pawams_wate(hw_pawams)) {
		case 256:
			snd_soc_component_update_bits(component, MW26124_CWK_CTW,
					    BIT(0) | BIT(1), 1);
			bweak;
		case 512:
			snd_soc_component_update_bits(component, MW26124_CWK_CTW,
					    BIT(0) | BIT(1), 2);
			bweak;
		case 1024:
			snd_soc_component_update_bits(component, MW26124_CWK_CTW,
					    BIT(0) | BIT(1), 3);
			bweak;
		defauwt:
			dev_eww(component->dev, "Unsuppowted MCWKI\n");
			bweak;
		}
	} ewse {
		snd_soc_component_update_bits(component, MW26124_CWK_CTW,
				    BIT(0) | BIT(1), 0);
	}

	swate = get_swate(pawams_wate(hw_pawams));
	if (swate < 0)
		wetuwn swate;

	snd_soc_component_update_bits(component, MW26124_SMPWING_WATE, 0xf, swate);
	snd_soc_component_update_bits(component, MW26124_PWWNW, 0xff, coeff_div[i].pwwnw);
	snd_soc_component_update_bits(component, MW26124_PWWNH, 0x1, coeff_div[i].pwwnh);
	snd_soc_component_update_bits(component, MW26124_PWWMW, 0xff, coeff_div[i].pwwmw);
	snd_soc_component_update_bits(component, MW26124_PWWMH, 0x3f, coeff_div[i].pwwmh);
	snd_soc_component_update_bits(component, MW26124_PWWDIV, 0x1f, coeff_div[i].pwwdiv);

	wetuwn 0;
}

static int mw26124_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct mw26124_pwiv *pwiv = snd_soc_component_get_dwvdata(component);

	switch (pwiv->substweam->stweam) {
	case SNDWV_PCM_STWEAM_CAPTUWE:
		snd_soc_component_update_bits(component, MW26124_WEC_PWYBAK_WUN, BIT(0), 1);
		bweak;
	case SNDWV_PCM_STWEAM_PWAYBACK:
		snd_soc_component_update_bits(component, MW26124_WEC_PWYBAK_WUN, BIT(1), 2);
		bweak;
	}

	if (mute)
		snd_soc_component_update_bits(component, MW26124_DVOW_CTW, BIT(4),
				    DVOW_CTW_DVMUTE_ON);
	ewse
		snd_soc_component_update_bits(component, MW26124_DVOW_CTW, BIT(4),
				    DVOW_CTW_DVMUTE_OFF);

	wetuwn 0;
}

static int mw26124_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	unsigned chaw mode;
	stwuct snd_soc_component *component = codec_dai->component;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		mode = 1;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		mode = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	snd_soc_component_update_bits(component, MW26124_SAI_MODE_SEW, BIT(0), mode);

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mw26124_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct mw26124_pwiv *pwiv = snd_soc_component_get_dwvdata(component);

	switch (cwk_id) {
	case MW26124_USE_PWWOUT:
		pwiv->cwk_in = MW26124_USE_PWWOUT;
		bweak;
	case MW26124_USE_MCWKI:
		pwiv->cwk_in = MW26124_USE_MCWKI;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	pwiv->mcwk = fweq;

	wetuwn 0;
}

static int mw26124_set_bias_wevew(stwuct snd_soc_component *component,
		enum snd_soc_bias_wevew wevew)
{
	stwuct mw26124_pwiv *pwiv = snd_soc_component_get_dwvdata(component);

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		snd_soc_component_update_bits(component, MW26124_PW_SPAMP_PW_MNG,
				    MW26124_W26_MASK, MW26124_BWT_PWEAMP_ON);
		msweep(100);
		snd_soc_component_update_bits(component, MW26124_PW_SPAMP_PW_MNG,
				    MW26124_W26_MASK,
				    MW26124_MICBEN_ON | MW26124_BWT_AWW_ON);
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		/* VMID ON */
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			snd_soc_component_update_bits(component, MW26124_PW_WEF_PW_MNG,
					    MW26124_VMID, MW26124_VMID);
			msweep(500);
			wegcache_sync(pwiv->wegmap);
		}
		bweak;
	case SND_SOC_BIAS_OFF:
		/* VMID OFF */
		snd_soc_component_update_bits(component, MW26124_PW_WEF_PW_MNG,
				    MW26124_VMID, 0);
		bweak;
	}
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mw26124_dai_ops = {
	.hw_pawams	= mw26124_hw_pawams,
	.mute_stweam	= mw26124_mute,
	.set_fmt	= mw26124_set_dai_fmt,
	.set_syscwk	= mw26124_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew mw26124_dai = {
	.name = "mw26124-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = MW26124_WATES,
		.fowmats = MW26124_FOWMATS,},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = MW26124_WATES,
		.fowmats = MW26124_FOWMATS,},
	.ops = &mw26124_dai_ops,
	.symmetwic_wate = 1,
};

static int mw26124_pwobe(stwuct snd_soc_component *component)
{
	/* Softwawe Weset */
	snd_soc_component_update_bits(component, MW26124_SW_WST, 0x01, 1);
	snd_soc_component_update_bits(component, MW26124_SW_WST, 0x01, 0);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_mw26124 = {
	.pwobe			= mw26124_pwobe,
	.set_bias_wevew		= mw26124_set_bias_wevew,
	.contwows		= mw26124_snd_contwows,
	.num_contwows		= AWWAY_SIZE(mw26124_snd_contwows),
	.dapm_widgets		= mw26124_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(mw26124_dapm_widgets),
	.dapm_woutes		= mw26124_intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(mw26124_intewcon),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config mw26124_i2c_wegmap = {
	.vaw_bits = 8,
	.weg_bits = 8,
	.max_wegistew = MW26124_NUM_WEGISTEW,
	.weg_defauwts = mw26124_weg,
	.num_weg_defauwts = AWWAY_SIZE(mw26124_weg),
	.cache_type = WEGCACHE_WBTWEE,
	.wwite_fwag_mask = 0x01,
};

static int mw26124_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct mw26124_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&i2c->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, pwiv);

	pwiv->wegmap = devm_wegmap_init_i2c(i2c, &mw26124_i2c_wegmap);
	if (IS_EWW(pwiv->wegmap)) {
		wet = PTW_EWW(pwiv->wegmap);
		dev_eww(&i2c->dev, "wegmap_init_i2c() faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_mw26124, &mw26124_dai, 1);
}

static const stwuct i2c_device_id mw26124_i2c_id[] = {
	{ "mw26124", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mw26124_i2c_id);

static stwuct i2c_dwivew mw26124_i2c_dwivew = {
	.dwivew = {
		.name = "mw26124",
	},
	.pwobe = mw26124_i2c_pwobe,
	.id_tabwe = mw26124_i2c_id,
};

moduwe_i2c_dwivew(mw26124_i2c_dwivew);

MODUWE_AUTHOW("Tomoya MOWINAGA <tomoya.wohm@gmaiw.com>");
MODUWE_DESCWIPTION("WAPIS Semiconductow MW26124 AWSA SoC codec dwivew");
MODUWE_WICENSE("GPW");
