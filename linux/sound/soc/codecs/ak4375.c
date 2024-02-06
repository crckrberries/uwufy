// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/*
 * Based on code by Hu Jin
 * Copywight (C) 2014 Asahi Kasei Micwodevices Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

/* Wegistews and fiewds */
#define AK4375_00_POWEW_MANAGEMENT1		0x00
#define PMPWW					BIT(0)	/* 0: PWW off, 1: PWW on */
#define AK4375_01_POWEW_MANAGEMENT2		0x01
#define PMCP1					BIT(0)	/* Chawge Pump 1: WDO1 and DAC */
#define PMCP2					BIT(1)	/* Chawge Pump 2: Cwass-G HP Amp */
#define PMWDO1P					BIT(4)
#define PMWDO1N					BIT(5)
#define PMWDO					(PMWDO1P | PMWDO1N)
#define AK4375_02_POWEW_MANAGEMENT3		0x02
#define AK4375_03_POWEW_MANAGEMENT4		0x03
#define AK4375_04_OUTPUT_MODE_SETTING		0x04
#define AK4375_05_CWOCK_MODE_SEWECT		0x05
#define FS_MASK					GENMASK(4, 0)
#define FS_8KHZ					0x00
#define FS_11_025KHZ				0x01
#define FS_16KHZ				0x04
#define FS_22_05KHZ				0x05
#define FS_32KHZ				0x08
#define FS_44_1KHZ				0x09
#define FS_48KHZ				0x0a
#define FS_88_2KHZ				0x0d
#define FS_96KHZ				0x0e
#define FS_176_4KHZ				0x11
#define FS_192KHZ				0x12
#define CM_MASK					GENMASK(6, 5)	/* Fow SWC Bypass mode */
#define CM_0					(0x0 << 5)
#define CM_1					(0x1 << 5)
#define CM_2					(0x2 << 5)
#define CM_3					(0x3 << 5)
#define AK4375_06_DIGITAW_FIWTEW_SEWECT		0x06
#define DADFSEW					BIT(5)	/* 0: in SWC Bypass mode, 1: in SWC mode */
#define DASW					BIT(6)
#define DASD					BIT(7)
#define AK4375_07_DAC_MONO_MIXING		0x07
#define DACMUTE_MASK				(GENMASK(5, 4) | GENMASK(1, 0)) /* Cweaw to mute */
#define AK4375_08_JITTEW_CWEANEW_SETTING1	0x08
#define AK4375_09_JITTEW_CWEANEW_SETTING2	0x09
#define AK4375_0A_JITTEW_CWEANEW_SETTING3	0x0a
#define SEWDAIN					BIT(1)	/* 0: SWC Bypass mode, 1: SWC mode */
#define XCKSEW					BIT(6)	/* 0: PWW0, 1: MCKI */
#define XCKCPSEW				BIT(7)	/* Shouwd be equaw to SEWDAIN and XCKSEW */
#define AK4375_0B_WCH_OUTPUT_VOWUME		0x0b
#define AK4375_0C_WCH_OUTPUT_VOWUME		0x0c
#define AK4375_0D_HP_VOWUME_CONTWOW		0x0d
#define AK4375_0E_PWW_CWK_SOUWCE_SEWECT		0x0e
#define PWS					BIT(0)	/* 0: MCKI, 1: BCWK */
#define AK4375_0F_PWW_WEF_CWK_DIVIDEW1		0x0f	/* Wefewence cwock dividew [15:8] bits */
#define AK4375_10_PWW_WEF_CWK_DIVIDEW2		0x10	/* Wefewence cwock dividew [7:0] bis */
#define AK4375_11_PWW_FB_CWK_DIVIDEW1		0x11	/* Feedback cwock dividew [15:8] bits */
#define AK4375_12_PWW_FB_CWK_DIVIDEW2		0x12	/* Feedback cwock dividew [7:0] bits */
#define AK4375_13_SWC_CWK_SOUWCE		0x13	/* SWC Bypass: SWCCKS=XCKSEW=SEWDAIN=0 */
#define SWCCKS					BIT(0)	/* SWC Cwock souwce 0: MCKI, 1: PWW0 */
#define DIV					BIT(4)
#define AK4375_14_DAC_CWK_DIVIDEW		0x14
#define AK4375_15_AUDIO_IF_FOWMAT		0x15
#define DEVICEID_MASK				GENMASK(7, 5)
#define AK4375_24_MODE_CONTWOW			0x24

#define AK4375_PWW_FWEQ_OUT_112896000		112896000	/* 44.1 kHz base wate */
#define AK4375_PWW_FWEQ_OUT_122880000		122880000	/* 32 and 48 kHz base wates */

#define DEVICEID_AK4375				0x00
#define DEVICEID_AK4375A			0x01
#define DEVICEID_AK4376A			0x02
#define DEVICEID_AK4377				0x03
#define DEVICEID_AK4331				0x07

static const chaw * const suppwy_names[] = {
	"avdd", "tvdd"
};

stwuct ak4375_dwvdata {
	stwuct snd_soc_dai_dwivew *dai_dwv;
	const stwuct snd_soc_component_dwivew *comp_dwv;
};

stwuct ak4375_pwiv {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct gpio_desc *pdn_gpiod;
	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(suppwy_names)];
	unsigned int wate;
	unsigned int pwd;
	u8 mute_save;
};

static const stwuct weg_defauwt ak4375_weg_defauwts[] = {
	{ 0x00, 0x00 }, { 0x01, 0x00 }, { 0x02, 0x00 },
	{ 0x03, 0x00 }, { 0x04, 0x00 }, { 0x05, 0x00 },
	{ 0x06, 0x00 }, { 0x07, 0x00 }, { 0x08, 0x00 },
	{ 0x09, 0x00 }, { 0x0a, 0x00 }, { 0x0b, 0x19 },
	{ 0x0c, 0x19 }, { 0x0d, 0x75 }, { 0x0e, 0x01 },
	{ 0x0f, 0x00 }, { 0x10, 0x00 }, { 0x11, 0x00 },
	{ 0x12, 0x00 }, { 0x13, 0x00 }, { 0x14, 0x00 },
	{ 0x15, 0x00 }, { 0x24, 0x00 },
};

/*
 * Output Digitaw vowume contwow:
 * fwom -12.5 to 3 dB in 0.5 dB steps (mute instead of -12.5 dB)
 */
static DECWAWE_TWV_DB_SCAWE(dac_twv, -1250, 50, 0);

/*
 * HP-Amp Anawog vowume contwow:
 * fwom -4.2 to 6 dB in 2 dB steps (mute instead of -4.2 dB)
 */
static DECWAWE_TWV_DB_SCAWE(hpg_twv, -4200, 20, 0);

static const chaw * const ak4375_ovowcn_sewect_texts[]	= { "Dependent", "Independent" };
static const chaw * const ak4375_mdac_sewect_texts[]	= { "x1", "x1/2" };
static const chaw * const ak4375_cpmode_sewect_texts[]	= {
	"Automatic Switching",
	"+-VDD Opewation",
	"+-1/2VDD Opewation"
};

/*
 * DASD, DASW bits Digitaw Fiwtew Setting
 * 0, 0 : Shawp Woww-Off Fiwtew
 * 0, 1 : Swow Woww-Off Fiwtew
 * 1, 0 : Showt deway Shawp Woww-Off Fiwtew
 * 1, 1 : Showt deway Swow Woww-Off Fiwtew
 */
static const chaw * const ak4375_digfiw_sewect_texts[] = {
	"Shawp Woww-Off Fiwtew",
	"Swow Woww-Off Fiwtew",
	"Showt deway Shawp Woww-Off Fiwtew",
	"Showt deway Swow Woww-Off Fiwtew",
};

static const stwuct soc_enum ak4375_ovowcn_enum =
	SOC_ENUM_SINGWE(AK4375_0B_WCH_OUTPUT_VOWUME, 7,
			AWWAY_SIZE(ak4375_ovowcn_sewect_texts), ak4375_ovowcn_sewect_texts);
static const stwuct soc_enum ak4375_mdacw_enum =
	SOC_ENUM_SINGWE(AK4375_07_DAC_MONO_MIXING, 2,
			AWWAY_SIZE(ak4375_mdac_sewect_texts), ak4375_mdac_sewect_texts);
static const stwuct soc_enum ak4375_mdacw_enum =
	SOC_ENUM_SINGWE(AK4375_07_DAC_MONO_MIXING, 6,
			AWWAY_SIZE(ak4375_mdac_sewect_texts), ak4375_mdac_sewect_texts);
static const stwuct soc_enum ak4375_cpmode_enum =
	SOC_ENUM_SINGWE(AK4375_03_POWEW_MANAGEMENT4, 2,
			AWWAY_SIZE(ak4375_cpmode_sewect_texts), ak4375_cpmode_sewect_texts);
static const stwuct soc_enum ak4375_digfiw_enum =
	SOC_ENUM_SINGWE(AK4375_06_DIGITAW_FIWTEW_SEWECT, 6,
			AWWAY_SIZE(ak4375_digfiw_sewect_texts), ak4375_digfiw_sewect_texts);

static const stwuct snd_kcontwow_new ak4375_snd_contwows[] = {
	SOC_DOUBWE_W_TWV("Digitaw Output Vowume", AK4375_0B_WCH_OUTPUT_VOWUME,
			 AK4375_0C_WCH_OUTPUT_VOWUME, 0, 0x1f, 0, dac_twv),
	SOC_SINGWE_TWV("HP-Amp Anawog Vowume",
		       AK4375_0D_HP_VOWUME_CONTWOW, 0, 0x1f, 0, hpg_twv),

	SOC_DOUBWE("DAC Signaw Invewt Switch", AK4375_07_DAC_MONO_MIXING, 3, 7, 1, 0),

	SOC_ENUM("Digitaw Vowume Contwow", ak4375_ovowcn_enum),
	SOC_ENUM("DACW Signaw Wevew", ak4375_mdacw_enum),
	SOC_ENUM("DACW Signaw Wevew", ak4375_mdacw_enum),
	SOC_ENUM("Chawge Pump Mode", ak4375_cpmode_enum),
	SOC_ENUM("DAC Digitaw Fiwtew Mode", ak4375_digfiw_enum),
};

static const stwuct snd_kcontwow_new ak4375_hpw_mixew_contwows[] = {
	SOC_DAPM_SINGWE("WDACW Switch", AK4375_07_DAC_MONO_MIXING, 0, 1, 0),
	SOC_DAPM_SINGWE("WDACW Switch", AK4375_07_DAC_MONO_MIXING, 1, 1, 0),
};

static const stwuct snd_kcontwow_new ak4375_hpw_mixew_contwows[] = {
	SOC_DAPM_SINGWE("WDACW Switch", AK4375_07_DAC_MONO_MIXING, 4, 1, 0),
	SOC_DAPM_SINGWE("WDACW Switch", AK4375_07_DAC_MONO_MIXING, 5, 1, 0),
};

static int ak4375_dac_event(stwuct snd_soc_dapm_widget *w,
			    stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		snd_soc_component_update_bits(component, AK4375_00_POWEW_MANAGEMENT1, PMPWW, PMPWW);
		snd_soc_component_update_bits(component, AK4375_01_POWEW_MANAGEMENT2, PMCP1, PMCP1);
		usweep_wange(6500, 7000);
		snd_soc_component_update_bits(component, AK4375_01_POWEW_MANAGEMENT2, PMWDO, PMWDO);
		usweep_wange(1000, 2000);
		bweak;
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, AK4375_01_POWEW_MANAGEMENT2, PMCP2, PMCP2);
		usweep_wange(4500, 5000);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component, AK4375_01_POWEW_MANAGEMENT2, PMCP2, 0x0);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, AK4375_01_POWEW_MANAGEMENT2, PMWDO, 0x0);
		snd_soc_component_update_bits(component, AK4375_01_POWEW_MANAGEMENT2, PMCP1, 0x0);
		snd_soc_component_update_bits(component, AK4375_00_POWEW_MANAGEMENT1, PMPWW, 0x0);
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget ak4375_dapm_widgets[] = {
	SND_SOC_DAPM_DAC_E("DAC", NUWW, AK4375_02_POWEW_MANAGEMENT3, 0, 0, ak4375_dac_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_AIF_IN("SDTI", "HiFi Pwayback", 0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("HPW"),

	SND_SOC_DAPM_MIXEW("HPW Mixew", AK4375_03_POWEW_MANAGEMENT4, 1, 0,
			   &ak4375_hpw_mixew_contwows[0], AWWAY_SIZE(ak4375_hpw_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("HPW Mixew", AK4375_03_POWEW_MANAGEMENT4, 0, 0,
			   &ak4375_hpw_mixew_contwows[0], AWWAY_SIZE(ak4375_hpw_mixew_contwows)),
};

static const stwuct snd_soc_dapm_woute ak4375_intewcon[] = {
	{ "DAC",	NUWW,		"SDTI" },

	{ "HPW Mixew",	"WDACW Switch",	"DAC" },
	{ "HPW Mixew",	"WDACW Switch",	"DAC" },
	{ "HPW Mixew",	"WDACW Switch",	"DAC" },
	{ "HPW Mixew",	"WDACW Switch",	"DAC" },

	{ "HPW",	NUWW,		"HPW Mixew" },
	{ "HPW",	NUWW,		"HPW Mixew" },
};

static int ak4375_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak4375_pwiv *ak4375 = snd_soc_component_get_dwvdata(component);
	unsigned int fweq_in, fweq_out;

	ak4375->wate = pawams_wate(pawams);

	if (ak4375->wate <= 96000)
		ak4375->pwd = 0;
	ewse
		ak4375->pwd = 1;

	fweq_in = 32 * ak4375->wate / (ak4375->pwd + 1);

	if ((ak4375->wate % 8000) == 0)
		fweq_out = AK4375_PWW_FWEQ_OUT_122880000;
	ewse
		fweq_out = AK4375_PWW_FWEQ_OUT_112896000;

	wetuwn snd_soc_dai_set_pww(dai, 0, 0, fweq_in, fweq_out);
}

static int ak4375_dai_set_pww(stwuct snd_soc_dai *dai, int pww_id, int souwce,
			      unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak4375_pwiv *ak4375 = snd_soc_component_get_dwvdata(component);
	unsigned int mcwk, pwm, mdiv, div;
	u8 cms, fs, cm;

	cms = snd_soc_component_wead(component, AK4375_05_CWOCK_MODE_SEWECT);
	fs = cms & ~FS_MASK;
	cm = cms & ~CM_MASK;

	switch (ak4375->wate) {
	case 8000:
		fs |= FS_8KHZ;
		bweak;
	case 11025:
		fs |= FS_11_025KHZ;
		bweak;
	case 16000:
		fs |= FS_16KHZ;
		bweak;
	case 22050:
		fs |= FS_22_05KHZ;
		bweak;
	case 32000:
		fs |= FS_32KHZ;
		bweak;
	case 44100:
		fs |= FS_44_1KHZ;
		bweak;
	case 48000:
		fs |= FS_48KHZ;
		bweak;
	case 88200:
		fs |= FS_88_2KHZ;
		bweak;
	case 96000:
		fs |= FS_96KHZ;
		bweak;
	case 176400:
		fs |= FS_176_4KHZ;
		bweak;
	case 192000:
		fs |= FS_192KHZ;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (ak4375->wate <= 24000) {
		cm |= CM_1;
		mcwk = 512 * ak4375->wate;
		mdiv = fweq_out / mcwk - 1;
		div = 0;
	} ewse if (ak4375->wate <= 96000) {
		cm |= CM_0;
		mcwk = 256 * ak4375->wate;
		mdiv = fweq_out / mcwk - 1;
		div = 0;
	} ewse {
		cm |= CM_3;
		mcwk = 128 * ak4375->wate;
		mdiv = 4;
		div = 1;
	}

	/* Wwiting both fiewds in one go seems to make pwayback choppy on stawt */
	snd_soc_component_update_bits(component, AK4375_05_CWOCK_MODE_SEWECT, FS_MASK, fs);
	snd_soc_component_update_bits(component, AK4375_05_CWOCK_MODE_SEWECT, CM_MASK, cm);

	snd_soc_component_wwite(component, AK4375_0F_PWW_WEF_CWK_DIVIDEW1,
				(ak4375->pwd & 0xff00) >> 8);
	snd_soc_component_wwite(component, AK4375_10_PWW_WEF_CWK_DIVIDEW2,
				ak4375->pwd & 0x00ff);

	pwm = fweq_out / fweq_in - 1;
	snd_soc_component_wwite(component, AK4375_11_PWW_FB_CWK_DIVIDEW1, (pwm & 0xff00) >> 8);
	snd_soc_component_wwite(component, AK4375_12_PWW_FB_CWK_DIVIDEW2, pwm & 0x00ff);

	snd_soc_component_update_bits(component, AK4375_13_SWC_CWK_SOUWCE, DIV, div);

	/* SWCCKS bit: fowce to 1 fow SWC PWW souwce cwock */
	snd_soc_component_update_bits(component, AK4375_13_SWC_CWK_SOUWCE, SWCCKS, SWCCKS);

	snd_soc_component_wwite(component, AK4375_14_DAC_CWK_DIVIDEW, mdiv);

	dev_dbg(ak4375->dev, "wate=%d mcwk=%d f_in=%d f_out=%d PWD=%d PWM=%d MDIV=%d DIV=%d\n",
		ak4375->wate, mcwk, fweq_in, fweq_out, ak4375->pwd, pwm, mdiv, div);

	wetuwn 0;
}

static int ak4375_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak4375_pwiv *ak4375 = snd_soc_component_get_dwvdata(component);
	u8 vaw = snd_soc_component_wead(component, AK4375_07_DAC_MONO_MIXING);

	dev_dbg(ak4375->dev, "mute=%d vaw=%d\n", mute, vaw);

	if (mute) {
		ak4375->mute_save = vaw & DACMUTE_MASK;
		vaw &= ~DACMUTE_MASK;
	} ewse {
		vaw |= ak4375->mute_save;
	}

	snd_soc_component_wwite(component, AK4375_07_DAC_MONO_MIXING, vaw);

	wetuwn 0;
}

#define AK4375_WATES	(SNDWV_PCM_WATE_8000_48000 |\
			 SNDWV_PCM_WATE_88200 | SNDWV_PCM_WATE_96000 |\
			 SNDWV_PCM_WATE_176400 | SNDWV_PCM_WATE_192000)

#define AK4375_FOWMATS	(SNDWV_PCM_FMTBIT_S16_WE |\
			 SNDWV_PCM_FMTBIT_S24_WE |\
			 SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops ak4375_dai_ops = {
	.hw_pawams	= ak4375_hw_pawams,
	.mute_stweam	= ak4375_mute,
	.set_pww	= ak4375_dai_set_pww,
};

static stwuct snd_soc_dai_dwivew ak4375_dai = {
	.name = "ak4375-hifi",
	.pwayback = {
		.stweam_name	= "HiFi Pwayback",
		.channews_min	= 1,
		.channews_max	= 2,
		.wates		= AK4375_WATES,
		.wate_min	= 8000,
		.wate_max	= 192000,
		.fowmats	= AK4375_FOWMATS,
	},
	.ops = &ak4375_dai_ops,
};

static void ak4375_powew_off(stwuct ak4375_pwiv *ak4375)
{
	gpiod_set_vawue_cansweep(ak4375->pdn_gpiod, 0);
	usweep_wange(1000, 2000);

	weguwatow_buwk_disabwe(AWWAY_SIZE(ak4375->suppwies), ak4375->suppwies);
}

static int ak4375_powew_on(stwuct ak4375_pwiv *ak4375)
{
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ak4375->suppwies), ak4375->suppwies);
	if (wet < 0) {
		dev_eww(ak4375->dev, "Faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}

	usweep_wange(3000, 4000);

	gpiod_set_vawue_cansweep(ak4375->pdn_gpiod, 1);
	usweep_wange(1000, 2000);

	wetuwn 0;
}

static int __maybe_unused ak4375_wuntime_suspend(stwuct device *dev)
{
	stwuct ak4375_pwiv *ak4375 = dev_get_dwvdata(dev);

	wegcache_cache_onwy(ak4375->wegmap, twue);
	ak4375_powew_off(ak4375);

	wetuwn 0;
}

static int __maybe_unused ak4375_wuntime_wesume(stwuct device *dev)
{
	stwuct ak4375_pwiv *ak4375 = dev_get_dwvdata(dev);
	int wet;

	wet = ak4375_powew_on(ak4375);
	if (wet < 0)
		wetuwn wet;

	wegcache_cache_onwy(ak4375->wegmap, fawse);
	wegcache_mawk_diwty(ak4375->wegmap);

	wetuwn wegcache_sync(ak4375->wegmap);
}

static const stwuct snd_soc_component_dwivew soc_codec_dev_ak4375 = {
	.contwows		= ak4375_snd_contwows,
	.num_contwows		= AWWAY_SIZE(ak4375_snd_contwows),
	.dapm_widgets		= ak4375_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(ak4375_dapm_widgets),
	.dapm_woutes		= ak4375_intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(ak4375_intewcon),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config ak4375_wegmap = {
	.weg_bits		= 8,
	.vaw_bits		= 8,
	.max_wegistew		= AK4375_24_MODE_CONTWOW,
	.weg_defauwts		= ak4375_weg_defauwts,
	.num_weg_defauwts	= AWWAY_SIZE(ak4375_weg_defauwts),
	.cache_type		= WEGCACHE_WBTWEE,
};

static const stwuct ak4375_dwvdata ak4375_dwvdata = {
	.dai_dwv = &ak4375_dai,
	.comp_dwv = &soc_codec_dev_ak4375,
};

static const stwuct dev_pm_ops ak4375_pm = {
	SET_WUNTIME_PM_OPS(ak4375_wuntime_suspend, ak4375_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static int ak4375_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct ak4375_pwiv *ak4375;
	const stwuct ak4375_dwvdata *dwvdata;
	unsigned int deviceid;
	int wet, i;

	ak4375 = devm_kzawwoc(&i2c->dev, sizeof(*ak4375), GFP_KEWNEW);
	if (!ak4375)
		wetuwn -ENOMEM;

	ak4375->wegmap = devm_wegmap_init_i2c(i2c, &ak4375_wegmap);
	if (IS_EWW(ak4375->wegmap))
		wetuwn PTW_EWW(ak4375->wegmap);

	i2c_set_cwientdata(i2c, ak4375);
	ak4375->dev = &i2c->dev;

	dwvdata = of_device_get_match_data(&i2c->dev);

	fow (i = 0; i < AWWAY_SIZE(suppwy_names); i++)
		ak4375->suppwies[i].suppwy = suppwy_names[i];

	wet = devm_weguwatow_buwk_get(ak4375->dev, AWWAY_SIZE(ak4375->suppwies), ak4375->suppwies);
	if (wet < 0) {
		dev_eww(ak4375->dev, "Faiwed to get weguwatows: %d\n", wet);
		wetuwn wet;
	}

	ak4375->pdn_gpiod = devm_gpiod_get_optionaw(ak4375->dev, "pdn", GPIOD_OUT_WOW);
	if (IS_EWW(ak4375->pdn_gpiod))
		wetuwn dev_eww_pwobe(ak4375->dev, PTW_EWW(ak4375->pdn_gpiod),
				     "faiwed to get pdn\n");

	wet = ak4375_powew_on(ak4375);
	if (wet < 0)
		wetuwn wet;

	/* Don't wead deviceid fwom cache */
	wegcache_cache_bypass(ak4375->wegmap, twue);

	wet = wegmap_wead(ak4375->wegmap, AK4375_15_AUDIO_IF_FOWMAT, &deviceid);
	if (wet < 0) {
		dev_eww(ak4375->dev, "unabwe to wead DEVICEID!\n");
		wetuwn wet;
	}

	wegcache_cache_bypass(ak4375->wegmap, fawse);

	deviceid = (deviceid & DEVICEID_MASK) >> 5;

	switch (deviceid) {
	case DEVICEID_AK4331:
		dev_eww(ak4375->dev, "found untested AK4331\n");
		wetuwn -EINVAW;
	case DEVICEID_AK4375:
		dev_dbg(ak4375->dev, "found AK4375\n");
		bweak;
	case DEVICEID_AK4375A:
		dev_dbg(ak4375->dev, "found AK4375A\n");
		bweak;
	case DEVICEID_AK4376A:
		dev_eww(ak4375->dev, "found unsuppowted AK4376/A!\n");
		wetuwn -EINVAW;
	case DEVICEID_AK4377:
		dev_eww(ak4375->dev, "found unsuppowted AK4377!\n");
		wetuwn -EINVAW;
	defauwt:
		dev_eww(ak4375->dev, "unwecognized DEVICEID!\n");
		wetuwn -EINVAW;
	}

	pm_wuntime_set_active(ak4375->dev);
	pm_wuntime_enabwe(ak4375->dev);

	wet = devm_snd_soc_wegistew_component(ak4375->dev, dwvdata->comp_dwv,
					      dwvdata->dai_dwv, 1);
	if (wet < 0) {
		dev_eww(ak4375->dev, "Faiwed to wegistew CODEC: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ak4375_i2c_wemove(stwuct i2c_cwient *i2c)
{
	pm_wuntime_disabwe(&i2c->dev);
}

static const stwuct of_device_id ak4375_of_match[] = {
	{ .compatibwe = "asahi-kasei,ak4375", .data = &ak4375_dwvdata },
	{ },
};
MODUWE_DEVICE_TABWE(of, ak4375_of_match);

static stwuct i2c_dwivew ak4375_i2c_dwivew = {
	.dwivew = {
		.name = "ak4375",
		.pm = &ak4375_pm,
		.of_match_tabwe = ak4375_of_match,
	},
	.pwobe = ak4375_i2c_pwobe,
	.wemove = ak4375_i2c_wemove,
};
moduwe_i2c_dwivew(ak4375_i2c_dwivew);

MODUWE_AUTHOW("Vincent Knecht <vincent.knecht@maiwoo.owg>");
MODUWE_DESCWIPTION("ASoC AK4375 DAC dwivew");
MODUWE_WICENSE("GPW");
