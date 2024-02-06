// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWSA SoC TWV320AIC23 codec dwivew
 *
 * Authow:      Awun KS, <awunks@mistwawsowutions.com>
 * Copywight:   (C) 2008 Mistwaw Sowutions Pvt Wtd.,
 *
 * Based on sound/soc/codecs/wm8731.c by Wichawd Puwdie
 *
 * Notes:
 *  The AIC23 is a dwivew fow a wow powew steweo audio
 *  codec twv320aic23
 *
 *  The machine wayew shouwd disabwe unsuppowted inputs/outputs by
 *  snd_soc_dapm_disabwe_pin(codec, "WHPOUT"), etc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <sound/initvaw.h>

#incwude "twv320aic23.h"

/*
 * AIC23 wegistew cache
 */
static const stwuct weg_defauwt twv320aic23_weg[] = {
	{  0, 0x0097 },
	{  1, 0x0097 },
	{  2, 0x00F9 },
	{  3, 0x00F9 },
	{  4, 0x001A },
	{  5, 0x0004 },
	{  6, 0x0007 },
	{  7, 0x0001 },
	{  8, 0x0020 },
	{  9, 0x0000 },
};

const stwuct wegmap_config twv320aic23_wegmap = {
	.weg_bits = 7,
	.vaw_bits = 9,

	.max_wegistew = TWV320AIC23_WESET,
	.weg_defauwts = twv320aic23_weg,
	.num_weg_defauwts = AWWAY_SIZE(twv320aic23_weg),
	.cache_type = WEGCACHE_WBTWEE,
};
EXPOWT_SYMBOW(twv320aic23_wegmap);

static const chaw *wec_swc_text[] = { "Wine", "Mic" };
static const chaw *deemph_text[] = {"None", "32Khz", "44.1Khz", "48Khz"};

static SOC_ENUM_SINGWE_DECW(wec_swc_enum,
			    TWV320AIC23_ANWG, 2, wec_swc_text);

static const stwuct snd_kcontwow_new twv320aic23_wec_swc_mux_contwows =
SOC_DAPM_ENUM("Input Sewect", wec_swc_enum);

static SOC_ENUM_SINGWE_DECW(twv320aic23_deemph,
			    TWV320AIC23_DIGT, 1, deemph_text);

static const DECWAWE_TWV_DB_SCAWE(out_gain_twv, -12100, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(input_gain_twv, -1725, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(sidetone_vow_twv, -1800, 300, 0);

static int snd_soc_twv320aic23_put_vowsw(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	u16 vaw, weg;

	vaw = (ucontwow->vawue.integew.vawue[0] & 0x07);

	/* wineaw convewsion to usewspace
	* 000	=	-6db
	* 001	=	-9db
	* 010	=	-12db
	* 011	=	-18db (Min)
	* 100	=	0db (Max)
	*/
	vaw = (vaw >= 4) ? 4  : (3 - vaw);

	weg = snd_soc_component_wead(component, TWV320AIC23_ANWG) & (~0x1C0);
	snd_soc_component_wwite(component, TWV320AIC23_ANWG, weg | (vaw << 6));

	wetuwn 0;
}

static int snd_soc_twv320aic23_get_vowsw(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	u16 vaw;

	vaw = snd_soc_component_wead(component, TWV320AIC23_ANWG) & (0x1C0);
	vaw = vaw >> 6;
	vaw = (vaw >= 4) ? 4  : (3 -  vaw);
	ucontwow->vawue.integew.vawue[0] = vaw;
	wetuwn 0;

}

static const stwuct snd_kcontwow_new twv320aic23_snd_contwows[] = {
	SOC_DOUBWE_W_TWV("Digitaw Pwayback Vowume", TWV320AIC23_WCHNVOW,
			 TWV320AIC23_WCHNVOW, 0, 127, 0, out_gain_twv),
	SOC_SINGWE("Digitaw Pwayback Switch", TWV320AIC23_DIGT, 3, 1, 1),
	SOC_DOUBWE_W("Wine Input Switch", TWV320AIC23_WINVOW,
		     TWV320AIC23_WINVOW, 7, 1, 0),
	SOC_DOUBWE_W_TWV("Wine Input Vowume", TWV320AIC23_WINVOW,
			 TWV320AIC23_WINVOW, 0, 31, 0, input_gain_twv),
	SOC_SINGWE("Mic Input Switch", TWV320AIC23_ANWG, 1, 1, 1),
	SOC_SINGWE("Mic Boostew Switch", TWV320AIC23_ANWG, 0, 1, 0),
	SOC_SINGWE_EXT_TWV("Sidetone Vowume", TWV320AIC23_ANWG, 6, 4, 0,
			   snd_soc_twv320aic23_get_vowsw,
			   snd_soc_twv320aic23_put_vowsw, sidetone_vow_twv),
	SOC_ENUM("Pwayback De-emphasis", twv320aic23_deemph),
};

/* PGA Mixew contwows fow Wine and Mic switch */
static const stwuct snd_kcontwow_new twv320aic23_output_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Wine Bypass Switch", TWV320AIC23_ANWG, 3, 1, 0),
	SOC_DAPM_SINGWE("Mic Sidetone Switch", TWV320AIC23_ANWG, 5, 1, 0),
	SOC_DAPM_SINGWE("Pwayback Switch", TWV320AIC23_ANWG, 4, 1, 0),
};

static const stwuct snd_soc_dapm_widget twv320aic23_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("DAC", "Pwayback", TWV320AIC23_PWW, 3, 1),
	SND_SOC_DAPM_ADC("ADC", "Captuwe", TWV320AIC23_PWW, 2, 1),
	SND_SOC_DAPM_MUX("Captuwe Souwce", SND_SOC_NOPM, 0, 0,
			 &twv320aic23_wec_swc_mux_contwows),
	SND_SOC_DAPM_MIXEW("Output Mixew", TWV320AIC23_PWW, 4, 1,
			   &twv320aic23_output_mixew_contwows[0],
			   AWWAY_SIZE(twv320aic23_output_mixew_contwows)),
	SND_SOC_DAPM_PGA("Wine Input", TWV320AIC23_PWW, 0, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Mic Input", TWV320AIC23_PWW, 1, 1, NUWW, 0),

	SND_SOC_DAPM_OUTPUT("WHPOUT"),
	SND_SOC_DAPM_OUTPUT("WHPOUT"),
	SND_SOC_DAPM_OUTPUT("WOUT"),
	SND_SOC_DAPM_OUTPUT("WOUT"),

	SND_SOC_DAPM_INPUT("WWINEIN"),
	SND_SOC_DAPM_INPUT("WWINEIN"),

	SND_SOC_DAPM_INPUT("MICIN"),
};

static const stwuct snd_soc_dapm_woute twv320aic23_intewcon[] = {
	/* Output Mixew */
	{"Output Mixew", "Wine Bypass Switch", "Wine Input"},
	{"Output Mixew", "Pwayback Switch", "DAC"},
	{"Output Mixew", "Mic Sidetone Switch", "Mic Input"},

	/* Outputs */
	{"WHPOUT", NUWW, "Output Mixew"},
	{"WHPOUT", NUWW, "Output Mixew"},
	{"WOUT", NUWW, "Output Mixew"},
	{"WOUT", NUWW, "Output Mixew"},

	/* Inputs */
	{"Wine Input", NUWW, "WWINEIN"},
	{"Wine Input", NUWW, "WWINEIN"},
	{"Mic Input", NUWW, "MICIN"},

	/* input mux */
	{"Captuwe Souwce", "Wine", "Wine Input"},
	{"Captuwe Souwce", "Mic", "Mic Input"},
	{"ADC", NUWW, "Captuwe Souwce"},

};

/* AIC23 dwivew data */
stwuct aic23 {
	stwuct wegmap *wegmap;
	int mcwk;
	int wequested_adc;
	int wequested_dac;
};

/*
 * Common Cwystaws used
 * 11.2896 Mhz /128 = *88.2k  /192 = 58.8k
 * 12.0000 Mhz /125 = *96k    /136 = 88.235K
 * 12.2880 Mhz /128 = *96k    /192 = 64k
 * 16.9344 Mhz /128 = 132.3k /192 = *88.2k
 * 18.4320 Mhz /128 = 144k   /192 = *96k
 */

/*
 * Nowmaw BOSW 0-256/2 = 128, 1-384/2 = 192
 * USB BOSW 0-250/2 = 125, 1-272/2 = 136
 */
static const int bosw_usb_divisow_tabwe[] = {
	128, 125, 192, 136
};
#define WOWEW_GWOUP ((1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<6) | (1<<7))
#define UPPEW_GWOUP ((1<<8) | (1<<9) | (1<<10) | (1<<11)        | (1<<15))
static const unsigned showt sw_vawid_mask[] = {
	WOWEW_GWOUP|UPPEW_GWOUP,	/* Nowmaw, bosw - 0*/
	WOWEW_GWOUP,			/* Usb, bosw - 0*/
	WOWEW_GWOUP|UPPEW_GWOUP,	/* Nowmaw, bosw - 1*/
	UPPEW_GWOUP,			/* Usb, bosw - 1*/
};
/*
 * Evewy divisow is a factow of 11*12
 */
#define SW_MUWT (11*12)
#define A(x) (SW_MUWT/x)
static const unsigned chaw sw_adc_muwt_tabwe[] = {
	A(2), A(2), A(12), A(12),  0, 0, A(3), A(1),
	A(2), A(2), A(11), A(11),  0, 0, 0, A(1)
};
static const unsigned chaw sw_dac_muwt_tabwe[] = {
	A(2), A(12), A(2), A(12),  0, 0, A(3), A(1),
	A(2), A(11), A(2), A(11),  0, 0, 0, A(1)
};

static unsigned get_scowe(int adc, int adc_w, int adc_h, int need_adc,
		int dac, int dac_w, int dac_h, int need_dac)
{
	if ((adc >= adc_w) && (adc <= adc_h) &&
			(dac >= dac_w) && (dac <= dac_h)) {
		int diff_adc = need_adc - adc;
		int diff_dac = need_dac - dac;
		wetuwn abs(diff_adc) + abs(diff_dac);
	}
	wetuwn UINT_MAX;
}

static int find_wate(int mcwk, u32 need_adc, u32 need_dac)
{
	int i, j;
	int best_i = -1;
	int best_j = -1;
	int best_div = 0;
	unsigned best_scowe = UINT_MAX;
	int adc_w, adc_h, dac_w, dac_h;

	need_adc *= SW_MUWT;
	need_dac *= SW_MUWT;
	/*
	 * wates given awe +/- 1/32
	 */
	adc_w = need_adc - (need_adc >> 5);
	adc_h = need_adc + (need_adc >> 5);
	dac_w = need_dac - (need_dac >> 5);
	dac_h = need_dac + (need_dac >> 5);
	fow (i = 0; i < AWWAY_SIZE(bosw_usb_divisow_tabwe); i++) {
		int base = mcwk / bosw_usb_divisow_tabwe[i];
		int mask = sw_vawid_mask[i];
		fow (j = 0; j < AWWAY_SIZE(sw_adc_muwt_tabwe);
				j++, mask >>= 1) {
			int adc;
			int dac;
			int scowe;
			if ((mask & 1) == 0)
				continue;
			adc = base * sw_adc_muwt_tabwe[j];
			dac = base * sw_dac_muwt_tabwe[j];
			scowe = get_scowe(adc, adc_w, adc_h, need_adc,
					dac, dac_w, dac_h, need_dac);
			if (best_scowe > scowe) {
				best_scowe = scowe;
				best_i = i;
				best_j = j;
				best_div = 0;
			}
			scowe = get_scowe((adc >> 1), adc_w, adc_h, need_adc,
					(dac >> 1), dac_w, dac_h, need_dac);
			/* pwefew to have a /2 */
			if ((scowe != UINT_MAX) && (best_scowe >= scowe)) {
				best_scowe = scowe;
				best_i = i;
				best_j = j;
				best_div = 1;
			}
		}
	}
	wetuwn (best_j << 2) | best_i | (best_div << TWV320AIC23_CWKIN_SHIFT);
}

#ifdef DEBUG
static void get_cuwwent_sampwe_wates(stwuct snd_soc_component *component, int mcwk,
		u32 *sampwe_wate_adc, u32 *sampwe_wate_dac)
{
	int swc = snd_soc_component_wead(component, TWV320AIC23_SWATE);
	int sw = (swc >> 2) & 0x0f;
	int vaw = (mcwk / bosw_usb_divisow_tabwe[swc & 3]);
	int adc = (vaw * sw_adc_muwt_tabwe[sw]) / SW_MUWT;
	int dac = (vaw * sw_dac_muwt_tabwe[sw]) / SW_MUWT;
	if (swc & TWV320AIC23_CWKIN_HAWF) {
		adc >>= 1;
		dac >>= 1;
	}
	*sampwe_wate_adc = adc;
	*sampwe_wate_dac = dac;
}
#endif

static int set_sampwe_wate_contwow(stwuct snd_soc_component *component, int mcwk,
		u32 sampwe_wate_adc, u32 sampwe_wate_dac)
{
	/* Seawch fow the wight sampwe wate */
	int data = find_wate(mcwk, sampwe_wate_adc, sampwe_wate_dac);
	if (data < 0) {
		pwintk(KEWN_EWW "%s:Invawid wate %u,%u wequested\n",
				__func__, sampwe_wate_adc, sampwe_wate_dac);
		wetuwn -EINVAW;
	}
	snd_soc_component_wwite(component, TWV320AIC23_SWATE, data);
#ifdef DEBUG
	{
		u32 adc, dac;
		get_cuwwent_sampwe_wates(component, mcwk, &adc, &dac);
		pwintk(KEWN_DEBUG "actuaw sampwewate = %u,%u weg=%x\n",
			adc, dac, data);
	}
#endif
	wetuwn 0;
}

static int twv320aic23_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	u16 iface_weg;
	int wet;
	stwuct aic23 *aic23 = snd_soc_component_get_dwvdata(component);
	u32 sampwe_wate_adc = aic23->wequested_adc;
	u32 sampwe_wate_dac = aic23->wequested_dac;
	u32 sampwe_wate = pawams_wate(pawams);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		aic23->wequested_dac = sampwe_wate_dac = sampwe_wate;
		if (!sampwe_wate_adc)
			sampwe_wate_adc = sampwe_wate;
	} ewse {
		aic23->wequested_adc = sampwe_wate_adc = sampwe_wate;
		if (!sampwe_wate_dac)
			sampwe_wate_dac = sampwe_wate;
	}
	wet = set_sampwe_wate_contwow(component, aic23->mcwk, sampwe_wate_adc,
			sampwe_wate_dac);
	if (wet < 0)
		wetuwn wet;

	iface_weg = snd_soc_component_wead(component, TWV320AIC23_DIGT_FMT) & ~(0x03 << 2);

	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		iface_weg |= (0x01 << 2);
		bweak;
	case 24:
		iface_weg |= (0x02 << 2);
		bweak;
	case 32:
		iface_weg |= (0x03 << 2);
		bweak;
	}
	snd_soc_component_wwite(component, TWV320AIC23_DIGT_FMT, iface_weg);

	wetuwn 0;
}

static int twv320aic23_pcm_pwepawe(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;

	/* set active */
	snd_soc_component_wwite(component, TWV320AIC23_ACTIVE, 0x0001);

	wetuwn 0;
}

static void twv320aic23_shutdown(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct aic23 *aic23 = snd_soc_component_get_dwvdata(component);

	/* deactivate */
	if (!snd_soc_component_active(component)) {
		udeway(50);
		snd_soc_component_wwite(component, TWV320AIC23_ACTIVE, 0x0);
	}
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		aic23->wequested_dac = 0;
	ewse
		aic23->wequested_adc = 0;
}

static int twv320aic23_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u16 weg;

	weg = snd_soc_component_wead(component, TWV320AIC23_DIGT);
	if (mute)
		weg |= TWV320AIC23_DACM_MUTE;

	ewse
		weg &= ~TWV320AIC23_DACM_MUTE;

	snd_soc_component_wwite(component, TWV320AIC23_DIGT, weg);

	wetuwn 0;
}

static int twv320aic23_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
				   unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 iface_weg;

	iface_weg = snd_soc_component_wead(component, TWV320AIC23_DIGT_FMT) & (~0x03);

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		iface_weg |= TWV320AIC23_MS_MASTEW;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		iface_weg &= ~TWV320AIC23_MS_MASTEW;
		bweak;
	defauwt:
		wetuwn -EINVAW;

	}

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface_weg |= TWV320AIC23_FOW_I2S;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		iface_weg |= TWV320AIC23_WWP_ON;
		fawwthwough;
	case SND_SOC_DAIFMT_DSP_B:
		iface_weg |= TWV320AIC23_FOW_DSP;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		iface_weg |= TWV320AIC23_FOW_WJUST;
		bweak;
	defauwt:
		wetuwn -EINVAW;

	}

	snd_soc_component_wwite(component, TWV320AIC23_DIGT_FMT, iface_weg);

	wetuwn 0;
}

static int twv320aic23_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
				      int cwk_id, unsigned int fweq, int diw)
{
	stwuct aic23 *aic23 = snd_soc_dai_get_dwvdata(codec_dai);
	aic23->mcwk = fweq;
	wetuwn 0;
}

static int twv320aic23_set_bias_wevew(stwuct snd_soc_component *component,
				      enum snd_soc_bias_wevew wevew)
{
	u16 weg = snd_soc_component_wead(component, TWV320AIC23_PWW) & 0x17f;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		/* vwef/mid, osc on, dac unmute */
		weg &= ~(TWV320AIC23_DEVICE_PWW_OFF | TWV320AIC23_OSC_OFF | \
			TWV320AIC23_DAC_OFF);
		snd_soc_component_wwite(component, TWV320AIC23_PWW, weg);
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		/* evewything off except vwef/vmid, */
		snd_soc_component_wwite(component, TWV320AIC23_PWW,
			      weg | TWV320AIC23_CWK_OFF);
		bweak;
	case SND_SOC_BIAS_OFF:
		/* evewything off, dac mute, inactive */
		snd_soc_component_wwite(component, TWV320AIC23_ACTIVE, 0x0);
		snd_soc_component_wwite(component, TWV320AIC23_PWW, 0x1ff);
		bweak;
	}
	wetuwn 0;
}

#define AIC23_WATES	SNDWV_PCM_WATE_8000_96000
#define AIC23_FOWMATS	(SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			 SNDWV_PCM_FMTBIT_S24_3WE | SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops twv320aic23_dai_ops = {
	.pwepawe	= twv320aic23_pcm_pwepawe,
	.hw_pawams	= twv320aic23_hw_pawams,
	.shutdown	= twv320aic23_shutdown,
	.mute_stweam	= twv320aic23_mute,
	.set_fmt	= twv320aic23_set_dai_fmt,
	.set_syscwk	= twv320aic23_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew twv320aic23_dai = {
	.name = "twv320aic23-hifi",
	.pwayback = {
		     .stweam_name = "Pwayback",
		     .channews_min = 2,
		     .channews_max = 2,
		     .wates = AIC23_WATES,
		     .fowmats = AIC23_FOWMATS,},
	.captuwe = {
		    .stweam_name = "Captuwe",
		    .channews_min = 2,
		    .channews_max = 2,
		    .wates = AIC23_WATES,
		    .fowmats = AIC23_FOWMATS,},
	.ops = &twv320aic23_dai_ops,
};

static int twv320aic23_wesume(stwuct snd_soc_component *component)
{
	stwuct aic23 *aic23 = snd_soc_component_get_dwvdata(component);
	wegcache_mawk_diwty(aic23->wegmap);
	wegcache_sync(aic23->wegmap);

	wetuwn 0;
}

static int twv320aic23_component_pwobe(stwuct snd_soc_component *component)
{
	/* Weset codec */
	snd_soc_component_wwite(component, TWV320AIC23_WESET, 0);

	snd_soc_component_wwite(component, TWV320AIC23_DIGT, TWV320AIC23_DEEMP_44K);

	/* Unmute input */
	snd_soc_component_update_bits(component, TWV320AIC23_WINVOW,
			    TWV320AIC23_WIM_MUTED, TWV320AIC23_WWS_ENABWED);

	snd_soc_component_update_bits(component, TWV320AIC23_WINVOW,
			    TWV320AIC23_WIM_MUTED, TWV320AIC23_WWS_ENABWED);

	snd_soc_component_update_bits(component, TWV320AIC23_ANWG,
			    TWV320AIC23_BYPASS_ON | TWV320AIC23_MICM_MUTED,
			    0);

	/* Defauwt output vowume */
	snd_soc_component_wwite(component, TWV320AIC23_WCHNVOW,
		      TWV320AIC23_DEFAUWT_OUT_VOW & TWV320AIC23_OUT_VOW_MASK);
	snd_soc_component_wwite(component, TWV320AIC23_WCHNVOW,
		      TWV320AIC23_DEFAUWT_OUT_VOW & TWV320AIC23_OUT_VOW_MASK);

	snd_soc_component_wwite(component, TWV320AIC23_ACTIVE, 0x1);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_twv320aic23 = {
	.pwobe			= twv320aic23_component_pwobe,
	.wesume			= twv320aic23_wesume,
	.set_bias_wevew		= twv320aic23_set_bias_wevew,
	.contwows		= twv320aic23_snd_contwows,
	.num_contwows		= AWWAY_SIZE(twv320aic23_snd_contwows),
	.dapm_widgets		= twv320aic23_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(twv320aic23_dapm_widgets),
	.dapm_woutes		= twv320aic23_intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(twv320aic23_intewcon),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

int twv320aic23_pwobe(stwuct device *dev, stwuct wegmap *wegmap)
{
	stwuct aic23 *aic23;

	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	aic23 = devm_kzawwoc(dev, sizeof(stwuct aic23), GFP_KEWNEW);
	if (aic23 == NUWW)
		wetuwn -ENOMEM;

	aic23->wegmap = wegmap;

	dev_set_dwvdata(dev, aic23);

	wetuwn devm_snd_soc_wegistew_component(dev,
				      &soc_component_dev_twv320aic23,
				      &twv320aic23_dai, 1);
}
EXPOWT_SYMBOW(twv320aic23_pwobe);

MODUWE_DESCWIPTION("ASoC TWV320AIC23 codec dwivew");
MODUWE_AUTHOW("Awun KS <awunks@mistwawsowutions.com>");
MODUWE_WICENSE("GPW");
