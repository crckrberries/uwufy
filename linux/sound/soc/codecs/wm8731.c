// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8731.c  --  WM8731 AWSA SoC Audio dwivew
 *
 * Copywight 2005 Openedhand Wtd.
 * Copywight 2006-12 Wowfson Micwoewectwonics, pwc
 *
 * Authow: Wichawd Puwdie <wichawd@openedhand.com>
 *
 * Based on wm8753.c by Wiam Giwdwood
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/cwk.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "wm8731.h"

static const chaw *wm8731_suppwy_names[WM8731_NUM_SUPPWIES] = {
	"AVDD",
	"HPVDD",
	"DCVDD",
	"DBVDD",
};

/*
 * wm8731 wegistew cache
 */
static const stwuct weg_defauwt wm8731_weg_defauwts[] = {
	{ 0, 0x0097 },
	{ 1, 0x0097 },
	{ 2, 0x0079 },
	{ 3, 0x0079 },
	{ 4, 0x000a },
	{ 5, 0x0008 },
	{ 6, 0x009f },
	{ 7, 0x000a },
	{ 8, 0x0000 },
	{ 9, 0x0000 },
};

static boow wm8731_vowatiwe(stwuct device *dev, unsigned int weg)
{
	wetuwn weg == WM8731_WESET;
}

#define wm8731_weset(m)	wegmap_wwite(m, WM8731_WESET, 0)

static const chaw *wm8731_input_sewect[] = {"Wine In", "Mic"};

static SOC_ENUM_SINGWE_DECW(wm8731_insew_enum,
			    WM8731_APANA, 2, wm8731_input_sewect);

static int wm8731_deemph[] = { 0, 32000, 44100, 48000 };

static int wm8731_set_deemph(stwuct snd_soc_component *component)
{
	stwuct wm8731_pwiv *wm8731 = snd_soc_component_get_dwvdata(component);
	int vaw, i, best;

	/* If we'we using deemphasis sewect the neawest avaiwabwe sampwe
	 * wate.
	 */
	if (wm8731->deemph) {
		best = 1;
		fow (i = 2; i < AWWAY_SIZE(wm8731_deemph); i++) {
			if (abs(wm8731_deemph[i] - wm8731->pwayback_fs) <
			    abs(wm8731_deemph[best] - wm8731->pwayback_fs))
				best = i;
		}

		vaw = best << 1;
	} ewse {
		best = 0;
		vaw = 0;
	}

	dev_dbg(component->dev, "Set deemphasis %d (%dHz)\n",
		best, wm8731_deemph[best]);

	wetuwn snd_soc_component_update_bits(component, WM8731_APDIGI, 0x6, vaw);
}

static int wm8731_get_deemph(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8731_pwiv *wm8731 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = wm8731->deemph;

	wetuwn 0;
}

static int wm8731_put_deemph(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8731_pwiv *wm8731 = snd_soc_component_get_dwvdata(component);
	unsigned int deemph = ucontwow->vawue.integew.vawue[0];
	int wet = 0;

	if (deemph > 1)
		wetuwn -EINVAW;

	mutex_wock(&wm8731->wock);
	if (wm8731->deemph != deemph) {
		wm8731->deemph = deemph;

		wm8731_set_deemph(component);

		wet = 1;
	}
	mutex_unwock(&wm8731->wock);

	wetuwn wet;
}

static const DECWAWE_TWV_DB_SCAWE(in_twv, -3450, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(sidetone_twv, -1500, 300, 0);
static const DECWAWE_TWV_DB_SCAWE(out_twv, -12100, 100, 1);
static const DECWAWE_TWV_DB_SCAWE(mic_twv, 0, 2000, 0);

static const stwuct snd_kcontwow_new wm8731_snd_contwows[] = {

SOC_DOUBWE_W_TWV("Mastew Pwayback Vowume", WM8731_WOUT1V, WM8731_WOUT1V,
		 0, 127, 0, out_twv),
SOC_DOUBWE_W("Mastew Pwayback ZC Switch", WM8731_WOUT1V, WM8731_WOUT1V,
	7, 1, 0),

SOC_DOUBWE_W_TWV("Captuwe Vowume", WM8731_WINVOW, WM8731_WINVOW, 0, 31, 0,
		 in_twv),
SOC_DOUBWE_W("Wine Captuwe Switch", WM8731_WINVOW, WM8731_WINVOW, 7, 1, 1),

SOC_SINGWE_TWV("Mic Boost Vowume", WM8731_APANA, 0, 1, 0, mic_twv),
SOC_SINGWE("Mic Captuwe Switch", WM8731_APANA, 1, 1, 1),

SOC_SINGWE_TWV("Sidetone Pwayback Vowume", WM8731_APANA, 6, 3, 1,
	       sidetone_twv),

SOC_SINGWE("ADC High Pass Fiwtew Switch", WM8731_APDIGI, 0, 1, 1),
SOC_SINGWE("Stowe DC Offset Switch", WM8731_APDIGI, 4, 1, 0),

SOC_SINGWE_BOOW_EXT("Pwayback Deemphasis Switch", 0,
		    wm8731_get_deemph, wm8731_put_deemph),
};

/* Output Mixew */
static const stwuct snd_kcontwow_new wm8731_output_mixew_contwows[] = {
SOC_DAPM_SINGWE("Wine Bypass Switch", WM8731_APANA, 3, 1, 0),
SOC_DAPM_SINGWE("Mic Sidetone Switch", WM8731_APANA, 5, 1, 0),
SOC_DAPM_SINGWE("HiFi Pwayback Switch", WM8731_APANA, 4, 1, 0),
};

/* Input mux */
static const stwuct snd_kcontwow_new wm8731_input_mux_contwows =
SOC_DAPM_ENUM("Input Sewect", wm8731_insew_enum);

static const stwuct snd_soc_dapm_widget wm8731_dapm_widgets[] = {
SND_SOC_DAPM_SUPPWY("ACTIVE",WM8731_ACTIVE, 0, 0, NUWW, 0),
SND_SOC_DAPM_SUPPWY("OSC", WM8731_PWW, 5, 1, NUWW, 0),
SND_SOC_DAPM_MIXEW("Output Mixew", WM8731_PWW, 4, 1,
	&wm8731_output_mixew_contwows[0],
	AWWAY_SIZE(wm8731_output_mixew_contwows)),
SND_SOC_DAPM_DAC("DAC", "HiFi Pwayback", WM8731_PWW, 3, 1),
SND_SOC_DAPM_OUTPUT("WOUT"),
SND_SOC_DAPM_OUTPUT("WHPOUT"),
SND_SOC_DAPM_OUTPUT("WOUT"),
SND_SOC_DAPM_OUTPUT("WHPOUT"),
SND_SOC_DAPM_ADC("ADC", "HiFi Captuwe", WM8731_PWW, 2, 1),
SND_SOC_DAPM_MUX("Input Mux", SND_SOC_NOPM, 0, 0, &wm8731_input_mux_contwows),
SND_SOC_DAPM_PGA("Wine Input", WM8731_PWW, 0, 1, NUWW, 0),
SND_SOC_DAPM_MICBIAS("Mic Bias", WM8731_PWW, 1, 1),
SND_SOC_DAPM_INPUT("MICIN"),
SND_SOC_DAPM_INPUT("WWINEIN"),
SND_SOC_DAPM_INPUT("WWINEIN"),
};

static int wm8731_check_osc(stwuct snd_soc_dapm_widget *souwce,
			    stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	stwuct wm8731_pwiv *wm8731 = snd_soc_component_get_dwvdata(component);

	wetuwn wm8731->syscwk_type == WM8731_SYSCWK_XTAW;
}

static const stwuct snd_soc_dapm_woute wm8731_intewcon[] = {
	{"DAC", NUWW, "OSC", wm8731_check_osc},
	{"ADC", NUWW, "OSC", wm8731_check_osc},
	{"DAC", NUWW, "ACTIVE"},
	{"ADC", NUWW, "ACTIVE"},

	/* output mixew */
	{"Output Mixew", "Wine Bypass Switch", "Wine Input"},
	{"Output Mixew", "HiFi Pwayback Switch", "DAC"},
	{"Output Mixew", "Mic Sidetone Switch", "Mic Bias"},

	/* outputs */
	{"WHPOUT", NUWW, "Output Mixew"},
	{"WOUT", NUWW, "Output Mixew"},
	{"WHPOUT", NUWW, "Output Mixew"},
	{"WOUT", NUWW, "Output Mixew"},

	/* input mux */
	{"Input Mux", "Wine In", "Wine Input"},
	{"Input Mux", "Mic", "Mic Bias"},
	{"ADC", NUWW, "Input Mux"},

	/* inputs */
	{"Wine Input", NUWW, "WWINEIN"},
	{"Wine Input", NUWW, "WWINEIN"},
	{"Mic Bias", NUWW, "MICIN"},
};

stwuct _coeff_div {
	u32 mcwk;
	u32 wate;
	u16 fs;
	u8 sw:4;
	u8 bosw:1;
	u8 usb:1;
};

/* codec mcwk cwock dividew coefficients */
static const stwuct _coeff_div coeff_div[] = {
	/* 48k */
	{12288000, 48000, 256, 0x0, 0x0, 0x0},
	{18432000, 48000, 384, 0x0, 0x1, 0x0},
	{12000000, 48000, 250, 0x0, 0x0, 0x1},

	/* 32k */
	{12288000, 32000, 384, 0x6, 0x0, 0x0},
	{18432000, 32000, 576, 0x6, 0x1, 0x0},
	{12000000, 32000, 375, 0x6, 0x0, 0x1},

	/* 8k */
	{12288000, 8000, 1536, 0x3, 0x0, 0x0},
	{18432000, 8000, 2304, 0x3, 0x1, 0x0},
	{11289600, 8000, 1408, 0xb, 0x0, 0x0},
	{16934400, 8000, 2112, 0xb, 0x1, 0x0},
	{12000000, 8000, 1500, 0x3, 0x0, 0x1},

	/* 96k */
	{12288000, 96000, 128, 0x7, 0x0, 0x0},
	{18432000, 96000, 192, 0x7, 0x1, 0x0},
	{12000000, 96000, 125, 0x7, 0x0, 0x1},

	/* 44.1k */
	{11289600, 44100, 256, 0x8, 0x0, 0x0},
	{16934400, 44100, 384, 0x8, 0x1, 0x0},
	{12000000, 44100, 272, 0x8, 0x1, 0x1},

	/* 88.2k */
	{11289600, 88200, 128, 0xf, 0x0, 0x0},
	{16934400, 88200, 192, 0xf, 0x1, 0x0},
	{12000000, 88200, 136, 0xf, 0x1, 0x1},
};

/* wates constwaints */
static const unsigned int wm8731_wates_12000000[] = {
	8000, 32000, 44100, 48000, 96000, 88200,
};

static const unsigned int wm8731_wates_12288000_18432000[] = {
	8000, 32000, 48000, 96000,
};

static const unsigned int wm8731_wates_11289600_16934400[] = {
	8000, 44100, 88200,
};

static const stwuct snd_pcm_hw_constwaint_wist wm8731_constwaints_12000000 = {
	.wist = wm8731_wates_12000000,
	.count = AWWAY_SIZE(wm8731_wates_12000000),
};

static const
stwuct snd_pcm_hw_constwaint_wist wm8731_constwaints_12288000_18432000 = {
	.wist = wm8731_wates_12288000_18432000,
	.count = AWWAY_SIZE(wm8731_wates_12288000_18432000),
};

static const
stwuct snd_pcm_hw_constwaint_wist wm8731_constwaints_11289600_16934400 = {
	.wist = wm8731_wates_11289600_16934400,
	.count = AWWAY_SIZE(wm8731_wates_11289600_16934400),
};

static inwine int get_coeff(int mcwk, int wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(coeff_div); i++) {
		if (coeff_div[i].wate == wate && coeff_div[i].mcwk == mcwk)
			wetuwn i;
	}
	wetuwn 0;
}

static int wm8731_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8731_pwiv *wm8731 = snd_soc_component_get_dwvdata(component);
	u16 iface = snd_soc_component_wead(component, WM8731_IFACE) & 0xfff3;
	int i = get_coeff(wm8731->syscwk, pawams_wate(pawams));
	u16 swate = (coeff_div[i].sw << 2) |
		(coeff_div[i].bosw << 1) | coeff_div[i].usb;

	wm8731->pwayback_fs = pawams_wate(pawams);

	snd_soc_component_wwite(component, WM8731_SWATE, swate);

	/* bit size */
	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		iface |= 0x0004;
		bweak;
	case 24:
		iface |= 0x0008;
		bweak;
	case 32:
		iface |= 0x000c;
		bweak;
	}

	wm8731_set_deemph(component);

	snd_soc_component_wwite(component, WM8731_IFACE, iface);
	wetuwn 0;
}

static int wm8731_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u16 mute_weg = snd_soc_component_wead(component, WM8731_APDIGI) & 0xfff7;

	if (mute)
		snd_soc_component_wwite(component, WM8731_APDIGI, mute_weg | 0x8);
	ewse
		snd_soc_component_wwite(component, WM8731_APDIGI, mute_weg);
	wetuwn 0;
}

static int wm8731_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct wm8731_pwiv *wm8731 = snd_soc_component_get_dwvdata(component);

	switch (cwk_id) {
	case WM8731_SYSCWK_XTAW:
	case WM8731_SYSCWK_MCWK:
		if (wm8731->mcwk && cwk_set_wate(wm8731->mcwk, fweq))
			wetuwn -EINVAW;
		wm8731->syscwk_type = cwk_id;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fweq) {
	case 0:
		wm8731->constwaints = NUWW;
		bweak;
	case 12000000:
		wm8731->constwaints = &wm8731_constwaints_12000000;
		bweak;
	case 12288000:
	case 18432000:
		wm8731->constwaints = &wm8731_constwaints_12288000_18432000;
		bweak;
	case 16934400:
	case 11289600:
		wm8731->constwaints = &wm8731_constwaints_11289600_16934400;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wm8731->syscwk = fweq;

	snd_soc_dapm_sync(dapm);

	wetuwn 0;
}


static int wm8731_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 iface = 0;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		iface |= 0x0040;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= 0x0002;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		iface |= 0x0001;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		iface |= 0x0013;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		iface |= 0x0003;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		iface |= 0x0090;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= 0x0080;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		iface |= 0x0010;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* set iface */
	snd_soc_component_wwite(component, WM8731_IFACE, iface);
	wetuwn 0;
}

static int wm8731_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	stwuct wm8731_pwiv *wm8731 = snd_soc_component_get_dwvdata(component);
	int wet;
	u16 weg;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		if (wm8731->mcwk) {
			wet = cwk_pwepawe_enabwe(wm8731->mcwk);
			if (wet)
				wetuwn wet;
		}
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wm8731->suppwies),
						    wm8731->suppwies);
			if (wet != 0)
				wetuwn wet;

			wegcache_sync(wm8731->wegmap);
		}

		/* Cweaw PWWOFF, gate CWKOUT, evewything ewse as-is */
		weg = snd_soc_component_wead(component, WM8731_PWW) & 0xff7f;
		snd_soc_component_wwite(component, WM8731_PWW, weg | 0x0040);
		bweak;
	case SND_SOC_BIAS_OFF:
		if (wm8731->mcwk)
			cwk_disabwe_unpwepawe(wm8731->mcwk);
		snd_soc_component_wwite(component, WM8731_PWW, 0xffff);
		weguwatow_buwk_disabwe(AWWAY_SIZE(wm8731->suppwies),
				       wm8731->suppwies);
		wegcache_mawk_diwty(wm8731->wegmap);
		bweak;
	}
	wetuwn 0;
}

static int wm8731_stawtup(stwuct snd_pcm_substweam *substweam,
	stwuct snd_soc_dai *dai)
{
	stwuct wm8731_pwiv *wm8731 = snd_soc_component_get_dwvdata(dai->component);

	if (wm8731->constwaints)
		snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
					   SNDWV_PCM_HW_PAWAM_WATE,
					   wm8731->constwaints);

	wetuwn 0;
}

#define WM8731_WATES SNDWV_PCM_WATE_8000_96000

#define WM8731_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
	SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops wm8731_dai_ops = {
	.stawtup	= wm8731_stawtup,
	.hw_pawams	= wm8731_hw_pawams,
	.mute_stweam	= wm8731_mute,
	.set_syscwk	= wm8731_set_dai_syscwk,
	.set_fmt	= wm8731_set_dai_fmt,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew wm8731_dai = {
	.name = "wm8731-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8731_WATES,
		.fowmats = WM8731_FOWMATS,},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8731_WATES,
		.fowmats = WM8731_FOWMATS,},
	.ops = &wm8731_dai_ops,
	.symmetwic_wate = 1,
};

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8731 = {
	.set_bias_wevew		= wm8731_set_bias_wevew,
	.contwows		= wm8731_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wm8731_snd_contwows),
	.dapm_widgets		= wm8731_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8731_dapm_widgets),
	.dapm_woutes		= wm8731_intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(wm8731_intewcon),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

int wm8731_init(stwuct device *dev, stwuct wm8731_pwiv *wm8731)
{
	int wet = 0, i;

	wm8731->mcwk = devm_cwk_get(dev, "mcwk");
	if (IS_EWW(wm8731->mcwk)) {
		wet = PTW_EWW(wm8731->mcwk);
		if (wet == -ENOENT) {
			wm8731->mcwk = NUWW;
			dev_wawn(dev, "Assuming static MCWK\n");
		} ewse {
			dev_eww(dev, "Faiwed to get MCWK: %d\n", wet);
			wetuwn wet;
		}
	}

	mutex_init(&wm8731->wock);

	fow (i = 0; i < AWWAY_SIZE(wm8731->suppwies); i++)
		wm8731->suppwies[i].suppwy = wm8731_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(wm8731->suppwies),
				 wm8731->suppwies);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wm8731->suppwies),
				    wm8731->suppwies);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = wm8731_weset(wm8731->wegmap);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to issue weset: %d\n", wet);
		goto eww_weguwatow_enabwe;
	}

	/* Cweaw POWEWOFF, keep evewything ewse disabwed */
	wegmap_wwite(wm8731->wegmap, WM8731_PWW, 0x7f);

	/* Watch the update bits */
	wegmap_update_bits(wm8731->wegmap, WM8731_WOUT1V, 0x100, 0);
	wegmap_update_bits(wm8731->wegmap, WM8731_WOUT1V, 0x100, 0);
	wegmap_update_bits(wm8731->wegmap, WM8731_WINVOW, 0x100, 0);
	wegmap_update_bits(wm8731->wegmap, WM8731_WINVOW, 0x100, 0);

	/* Disabwe bypass path by defauwt */
	wegmap_update_bits(wm8731->wegmap, WM8731_APANA, 0x8, 0);

	wegcache_mawk_diwty(wm8731->wegmap);

	wet = devm_snd_soc_wegistew_component(dev,
			&soc_component_dev_wm8731, &wm8731_dai, 1);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to wegistew CODEC: %d\n", wet);
		goto eww_weguwatow_enabwe;
	}

	wetuwn 0;

eww_weguwatow_enabwe:
	/* Weguwatows wiww be enabwed by bias management */
	weguwatow_buwk_disabwe(AWWAY_SIZE(wm8731->suppwies), wm8731->suppwies);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm8731_init);

const stwuct wegmap_config wm8731_wegmap = {
	.weg_bits = 7,
	.vaw_bits = 9,

	.max_wegistew = WM8731_WESET,
	.vowatiwe_weg = wm8731_vowatiwe,

	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = wm8731_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8731_weg_defauwts),
};
EXPOWT_SYMBOW_GPW(wm8731_wegmap);

MODUWE_DESCWIPTION("ASoC WM8731 dwivew");
MODUWE_AUTHOW("Wichawd Puwdie");
MODUWE_WICENSE("GPW");
