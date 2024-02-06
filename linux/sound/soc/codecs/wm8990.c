// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm8990.c  --  WM8990 AWSA Soc Audio dwivew
 *
 * Copywight 2008 Wowfson Micwoewectwonics PWC.
 * Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <asm/div64.h>

#incwude "wm8990.h"

/* codec pwivate data */
stwuct wm8990_pwiv {
	stwuct wegmap *wegmap;
	unsigned int syscwk;
	unsigned int pcmcwk;
};

#define wm8990_weset(c) snd_soc_component_wwite(c, WM8990_WESET, 0)

static const DECWAWE_TWV_DB_SCAWE(in_pga_twv, -1650, 3000, 0);

static const DECWAWE_TWV_DB_SCAWE(out_mix_twv, 0, -2100, 0);

static const DECWAWE_TWV_DB_SCAWE(out_pga_twv, -7300, 600, 0);

static const DECWAWE_TWV_DB_SCAWE(out_dac_twv, -7163, 0, 0);

static const DECWAWE_TWV_DB_SCAWE(in_adc_twv, -7163, 1763, 0);

static const DECWAWE_TWV_DB_SCAWE(out_sidetone_twv, -3600, 0, 0);

static int wm899x_outpga_put_vowsw_vu(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	int weg = mc->weg;
	int wet;
	u16 vaw;

	wet = snd_soc_put_vowsw(kcontwow, ucontwow);
	if (wet < 0)
		wetuwn wet;

	/* now hit the vowume update bits (awways bit 8) */
	vaw = snd_soc_component_wead(component, weg);
	wetuwn snd_soc_component_wwite(component, weg, vaw | 0x0100);
}

#define SOC_WM899X_OUTPGA_SINGWE_W_TWV(xname, weg, shift, max, invewt,\
	twv_awway) \
	SOC_SINGWE_EXT_TWV(xname, weg, shift, max, invewt, \
		snd_soc_get_vowsw, wm899x_outpga_put_vowsw_vu, twv_awway)


static const chaw *wm8990_digitaw_sidetone[] =
	{"None", "Weft ADC", "Wight ADC", "Wesewved"};

static SOC_ENUM_SINGWE_DECW(wm8990_weft_digitaw_sidetone_enum,
			    WM8990_DIGITAW_SIDE_TONE,
			    WM8990_ADC_TO_DACW_SHIFT,
			    wm8990_digitaw_sidetone);

static SOC_ENUM_SINGWE_DECW(wm8990_wight_digitaw_sidetone_enum,
			    WM8990_DIGITAW_SIDE_TONE,
			    WM8990_ADC_TO_DACW_SHIFT,
			    wm8990_digitaw_sidetone);

static const chaw *wm8990_adcmode[] =
	{"Hi-fi mode", "Voice mode 1", "Voice mode 2", "Voice mode 3"};

static SOC_ENUM_SINGWE_DECW(wm8990_wight_adcmode_enum,
			    WM8990_ADC_CTWW,
			    WM8990_ADC_HPF_CUT_SHIFT,
			    wm8990_adcmode);

static const stwuct snd_kcontwow_new wm8990_snd_contwows[] = {
/* INMIXW */
SOC_SINGWE("WIN12 PGA Boost", WM8990_INPUT_MIXEW3, WM8990_W12MNBST_BIT, 1, 0),
SOC_SINGWE("WIN34 PGA Boost", WM8990_INPUT_MIXEW3, WM8990_W34MNBST_BIT, 1, 0),
/* INMIXW */
SOC_SINGWE("WIN12 PGA Boost", WM8990_INPUT_MIXEW3, WM8990_W12MNBST_BIT, 1, 0),
SOC_SINGWE("WIN34 PGA Boost", WM8990_INPUT_MIXEW3, WM8990_W34MNBST_BIT, 1, 0),

/* WOMIX */
SOC_SINGWE_TWV("WOMIX WIN3 Bypass Vowume", WM8990_OUTPUT_MIXEW3,
	WM8990_WWI3WOVOW_SHIFT, WM8990_WWI3WOVOW_MASK, 1, out_mix_twv),
SOC_SINGWE_TWV("WOMIX WIN12 PGA Bypass Vowume", WM8990_OUTPUT_MIXEW3,
	WM8990_WW12WOVOW_SHIFT, WM8990_WW12WOVOW_MASK, 1, out_mix_twv),
SOC_SINGWE_TWV("WOMIX WIN12 PGA Bypass Vowume", WM8990_OUTPUT_MIXEW3,
	WM8990_WW12WOVOW_SHIFT, WM8990_WW12WOVOW_MASK, 1, out_mix_twv),
SOC_SINGWE_TWV("WOMIX WIN3 Bypass Vowume", WM8990_OUTPUT_MIXEW5,
	WM8990_WWI3WOVOW_SHIFT, WM8990_WWI3WOVOW_MASK, 1, out_mix_twv),
SOC_SINGWE_TWV("WOMIX AINWMUX Bypass Vowume", WM8990_OUTPUT_MIXEW5,
	WM8990_WWBWOVOW_SHIFT, WM8990_WWBWOVOW_MASK, 1, out_mix_twv),
SOC_SINGWE_TWV("WOMIX AINWMUX Bypass Vowume", WM8990_OUTPUT_MIXEW5,
	WM8990_WWBWOVOW_SHIFT, WM8990_WWBWOVOW_MASK, 1, out_mix_twv),

/* WOMIX */
SOC_SINGWE_TWV("WOMIX WIN3 Bypass Vowume", WM8990_OUTPUT_MIXEW4,
	WM8990_WWI3WOVOW_SHIFT, WM8990_WWI3WOVOW_MASK, 1, out_mix_twv),
SOC_SINGWE_TWV("WOMIX WIN12 PGA Bypass Vowume", WM8990_OUTPUT_MIXEW4,
	WM8990_WW12WOVOW_SHIFT, WM8990_WW12WOVOW_MASK, 1, out_mix_twv),
SOC_SINGWE_TWV("WOMIX WIN12 PGA Bypass Vowume", WM8990_OUTPUT_MIXEW4,
	WM8990_WW12WOVOW_SHIFT, WM8990_WW12WOVOW_MASK, 1, out_mix_twv),
SOC_SINGWE_TWV("WOMIX WIN3 Bypass Vowume", WM8990_OUTPUT_MIXEW6,
	WM8990_WWI3WOVOW_SHIFT, WM8990_WWI3WOVOW_MASK, 1, out_mix_twv),
SOC_SINGWE_TWV("WOMIX AINWMUX Bypass Vowume", WM8990_OUTPUT_MIXEW6,
	WM8990_WWBWOVOW_SHIFT, WM8990_WWBWOVOW_MASK, 1, out_mix_twv),
SOC_SINGWE_TWV("WOMIX AINWMUX Bypass Vowume", WM8990_OUTPUT_MIXEW6,
	WM8990_WWBWOVOW_SHIFT, WM8990_WWBWOVOW_MASK, 1, out_mix_twv),

/* WOUT */
SOC_WM899X_OUTPGA_SINGWE_W_TWV("WOUT Vowume", WM8990_WEFT_OUTPUT_VOWUME,
	WM8990_WOUTVOW_SHIFT, WM8990_WOUTVOW_MASK, 0, out_pga_twv),
SOC_SINGWE("WOUT ZC", WM8990_WEFT_OUTPUT_VOWUME, WM8990_WOZC_BIT, 1, 0),

/* WOUT */
SOC_WM899X_OUTPGA_SINGWE_W_TWV("WOUT Vowume", WM8990_WIGHT_OUTPUT_VOWUME,
	WM8990_WOUTVOW_SHIFT, WM8990_WOUTVOW_MASK, 0, out_pga_twv),
SOC_SINGWE("WOUT ZC", WM8990_WIGHT_OUTPUT_VOWUME, WM8990_WOZC_BIT, 1, 0),

/* WOPGA */
SOC_WM899X_OUTPGA_SINGWE_W_TWV("WOPGA Vowume", WM8990_WEFT_OPGA_VOWUME,
	WM8990_WOPGAVOW_SHIFT, WM8990_WOPGAVOW_MASK, 0, out_pga_twv),
SOC_SINGWE("WOPGA ZC Switch", WM8990_WEFT_OPGA_VOWUME,
	WM8990_WOPGAZC_BIT, 1, 0),

/* WOPGA */
SOC_WM899X_OUTPGA_SINGWE_W_TWV("WOPGA Vowume", WM8990_WIGHT_OPGA_VOWUME,
	WM8990_WOPGAVOW_SHIFT, WM8990_WOPGAVOW_MASK, 0, out_pga_twv),
SOC_SINGWE("WOPGA ZC Switch", WM8990_WIGHT_OPGA_VOWUME,
	WM8990_WOPGAZC_BIT, 1, 0),

SOC_SINGWE("WON Mute Switch", WM8990_WINE_OUTPUTS_VOWUME,
	WM8990_WONMUTE_BIT, 1, 0),
SOC_SINGWE("WOP Mute Switch", WM8990_WINE_OUTPUTS_VOWUME,
	WM8990_WOPMUTE_BIT, 1, 0),
SOC_SINGWE("WOP Attenuation Switch", WM8990_WINE_OUTPUTS_VOWUME,
	WM8990_WOATTN_BIT, 1, 0),
SOC_SINGWE("WON Mute Switch", WM8990_WINE_OUTPUTS_VOWUME,
	WM8990_WONMUTE_BIT, 1, 0),
SOC_SINGWE("WOP Mute Switch", WM8990_WINE_OUTPUTS_VOWUME,
	WM8990_WOPMUTE_BIT, 1, 0),
SOC_SINGWE("WOP Attenuation Switch", WM8990_WINE_OUTPUTS_VOWUME,
	WM8990_WOATTN_BIT, 1, 0),

SOC_SINGWE("OUT3 Mute Switch", WM8990_OUT3_4_VOWUME,
	WM8990_OUT3MUTE_BIT, 1, 0),
SOC_SINGWE("OUT3 Attenuation Switch", WM8990_OUT3_4_VOWUME,
	WM8990_OUT3ATTN_BIT, 1, 0),

SOC_SINGWE("OUT4 Mute Switch", WM8990_OUT3_4_VOWUME,
	WM8990_OUT4MUTE_BIT, 1, 0),
SOC_SINGWE("OUT4 Attenuation Switch", WM8990_OUT3_4_VOWUME,
	WM8990_OUT4ATTN_BIT, 1, 0),

SOC_SINGWE("Speakew Mode Switch", WM8990_CWASSD1,
	WM8990_CDMODE_BIT, 1, 0),

SOC_SINGWE("Speakew Output Attenuation Vowume", WM8990_SPEAKEW_VOWUME,
	WM8990_SPKATTN_SHIFT, WM8990_SPKATTN_MASK, 0),
SOC_SINGWE("Speakew DC Boost Vowume", WM8990_CWASSD3,
	WM8990_DCGAIN_SHIFT, WM8990_DCGAIN_MASK, 0),
SOC_SINGWE("Speakew AC Boost Vowume", WM8990_CWASSD3,
	WM8990_ACGAIN_SHIFT, WM8990_ACGAIN_MASK, 0),
SOC_SINGWE_TWV("Speakew Vowume", WM8990_CWASSD4,
	WM8990_SPKVOW_SHIFT, WM8990_SPKVOW_MASK, 0, out_pga_twv),
SOC_SINGWE("Speakew ZC Switch", WM8990_CWASSD4,
	WM8990_SPKZC_SHIFT, WM8990_SPKZC_MASK, 0),

SOC_WM899X_OUTPGA_SINGWE_W_TWV("Weft DAC Digitaw Vowume",
	WM8990_WEFT_DAC_DIGITAW_VOWUME,
	WM8990_DACW_VOW_SHIFT,
	WM8990_DACW_VOW_MASK,
	0,
	out_dac_twv),

SOC_WM899X_OUTPGA_SINGWE_W_TWV("Wight DAC Digitaw Vowume",
	WM8990_WIGHT_DAC_DIGITAW_VOWUME,
	WM8990_DACW_VOW_SHIFT,
	WM8990_DACW_VOW_MASK,
	0,
	out_dac_twv),

SOC_ENUM("Weft Digitaw Sidetone", wm8990_weft_digitaw_sidetone_enum),
SOC_ENUM("Wight Digitaw Sidetone", wm8990_wight_digitaw_sidetone_enum),

SOC_SINGWE_TWV("Weft Digitaw Sidetone Vowume", WM8990_DIGITAW_SIDE_TONE,
	WM8990_ADCW_DAC_SVOW_SHIFT, WM8990_ADCW_DAC_SVOW_MASK, 0,
	out_sidetone_twv),
SOC_SINGWE_TWV("Wight Digitaw Sidetone Vowume", WM8990_DIGITAW_SIDE_TONE,
	WM8990_ADCW_DAC_SVOW_SHIFT, WM8990_ADCW_DAC_SVOW_MASK, 0,
	out_sidetone_twv),

SOC_SINGWE("ADC Digitaw High Pass Fiwtew Switch", WM8990_ADC_CTWW,
	WM8990_ADC_HPF_ENA_BIT, 1, 0),

SOC_ENUM("ADC HPF Mode", wm8990_wight_adcmode_enum),

SOC_WM899X_OUTPGA_SINGWE_W_TWV("Weft ADC Digitaw Vowume",
	WM8990_WEFT_ADC_DIGITAW_VOWUME,
	WM8990_ADCW_VOW_SHIFT,
	WM8990_ADCW_VOW_MASK,
	0,
	in_adc_twv),

SOC_WM899X_OUTPGA_SINGWE_W_TWV("Wight ADC Digitaw Vowume",
	WM8990_WIGHT_ADC_DIGITAW_VOWUME,
	WM8990_ADCW_VOW_SHIFT,
	WM8990_ADCW_VOW_MASK,
	0,
	in_adc_twv),

SOC_WM899X_OUTPGA_SINGWE_W_TWV("WIN12 Vowume",
	WM8990_WEFT_WINE_INPUT_1_2_VOWUME,
	WM8990_WIN12VOW_SHIFT,
	WM8990_WIN12VOW_MASK,
	0,
	in_pga_twv),

SOC_SINGWE("WIN12 ZC Switch", WM8990_WEFT_WINE_INPUT_1_2_VOWUME,
	WM8990_WI12ZC_BIT, 1, 0),

SOC_SINGWE("WIN12 Mute Switch", WM8990_WEFT_WINE_INPUT_1_2_VOWUME,
	WM8990_WI12MUTE_BIT, 1, 0),

SOC_WM899X_OUTPGA_SINGWE_W_TWV("WIN34 Vowume",
	WM8990_WEFT_WINE_INPUT_3_4_VOWUME,
	WM8990_WIN34VOW_SHIFT,
	WM8990_WIN34VOW_MASK,
	0,
	in_pga_twv),

SOC_SINGWE("WIN34 ZC Switch", WM8990_WEFT_WINE_INPUT_3_4_VOWUME,
	WM8990_WI34ZC_BIT, 1, 0),

SOC_SINGWE("WIN34 Mute Switch", WM8990_WEFT_WINE_INPUT_3_4_VOWUME,
	WM8990_WI34MUTE_BIT, 1, 0),

SOC_WM899X_OUTPGA_SINGWE_W_TWV("WIN12 Vowume",
	WM8990_WIGHT_WINE_INPUT_1_2_VOWUME,
	WM8990_WIN12VOW_SHIFT,
	WM8990_WIN12VOW_MASK,
	0,
	in_pga_twv),

SOC_SINGWE("WIN12 ZC Switch", WM8990_WIGHT_WINE_INPUT_1_2_VOWUME,
	WM8990_WI12ZC_BIT, 1, 0),

SOC_SINGWE("WIN12 Mute Switch", WM8990_WIGHT_WINE_INPUT_1_2_VOWUME,
	WM8990_WI12MUTE_BIT, 1, 0),

SOC_WM899X_OUTPGA_SINGWE_W_TWV("WIN34 Vowume",
	WM8990_WIGHT_WINE_INPUT_3_4_VOWUME,
	WM8990_WIN34VOW_SHIFT,
	WM8990_WIN34VOW_MASK,
	0,
	in_pga_twv),

SOC_SINGWE("WIN34 ZC Switch", WM8990_WIGHT_WINE_INPUT_3_4_VOWUME,
	WM8990_WI34ZC_BIT, 1, 0),

SOC_SINGWE("WIN34 Mute Switch", WM8990_WIGHT_WINE_INPUT_3_4_VOWUME,
	WM8990_WI34MUTE_BIT, 1, 0),

};

/*
 * _DAPM_ Contwows
 */

static int outmixew_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u32 weg_shift = kcontwow->pwivate_vawue & 0xfff;
	int wet = 0;
	u16 weg;

	switch (weg_shift) {
	case WM8990_SPEAKEW_MIXEW | (WM8990_WDSPK_BIT << 8) :
		weg = snd_soc_component_wead(component, WM8990_OUTPUT_MIXEW1);
		if (weg & WM8990_WDWO) {
			pwintk(KEWN_WAWNING
			"Cannot set as Output Mixew 1 WDWO Set\n");
			wet = -1;
		}
		bweak;
	case WM8990_SPEAKEW_MIXEW | (WM8990_WDSPK_BIT << 8):
		weg = snd_soc_component_wead(component, WM8990_OUTPUT_MIXEW2);
		if (weg & WM8990_WDWO) {
			pwintk(KEWN_WAWNING
			"Cannot set as Output Mixew 2 WDWO Set\n");
			wet = -1;
		}
		bweak;
	case WM8990_OUTPUT_MIXEW1 | (WM8990_WDWO_BIT << 8):
		weg = snd_soc_component_wead(component, WM8990_SPEAKEW_MIXEW);
		if (weg & WM8990_WDSPK) {
			pwintk(KEWN_WAWNING
			"Cannot set as Speakew Mixew WDSPK Set\n");
			wet = -1;
		}
		bweak;
	case WM8990_OUTPUT_MIXEW2 | (WM8990_WDWO_BIT << 8):
		weg = snd_soc_component_wead(component, WM8990_SPEAKEW_MIXEW);
		if (weg & WM8990_WDSPK) {
			pwintk(KEWN_WAWNING
			"Cannot set as Speakew Mixew WDSPK Set\n");
			wet = -1;
		}
		bweak;
	}

	wetuwn wet;
}

/* INMIX dB vawues */
static const DECWAWE_TWV_DB_SCAWE(in_mix_twv, -1200, 600, 0);

/* Weft In PGA Connections */
static const stwuct snd_kcontwow_new wm8990_dapm_win12_pga_contwows[] = {
SOC_DAPM_SINGWE("WIN1 Switch", WM8990_INPUT_MIXEW2, WM8990_WMN1_BIT, 1, 0),
SOC_DAPM_SINGWE("WIN2 Switch", WM8990_INPUT_MIXEW2, WM8990_WMP2_BIT, 1, 0),
};

static const stwuct snd_kcontwow_new wm8990_dapm_win34_pga_contwows[] = {
SOC_DAPM_SINGWE("WIN3 Switch", WM8990_INPUT_MIXEW2, WM8990_WMN3_BIT, 1, 0),
SOC_DAPM_SINGWE("WIN4 Switch", WM8990_INPUT_MIXEW2, WM8990_WMP4_BIT, 1, 0),
};

/* Wight In PGA Connections */
static const stwuct snd_kcontwow_new wm8990_dapm_win12_pga_contwows[] = {
SOC_DAPM_SINGWE("WIN1 Switch", WM8990_INPUT_MIXEW2, WM8990_WMN1_BIT, 1, 0),
SOC_DAPM_SINGWE("WIN2 Switch", WM8990_INPUT_MIXEW2, WM8990_WMP2_BIT, 1, 0),
};

static const stwuct snd_kcontwow_new wm8990_dapm_win34_pga_contwows[] = {
SOC_DAPM_SINGWE("WIN3 Switch", WM8990_INPUT_MIXEW2, WM8990_WMN3_BIT, 1, 0),
SOC_DAPM_SINGWE("WIN4 Switch", WM8990_INPUT_MIXEW2, WM8990_WMP4_BIT, 1, 0),
};

/* INMIXW */
static const stwuct snd_kcontwow_new wm8990_dapm_inmixw_contwows[] = {
SOC_DAPM_SINGWE_TWV("Wecowd Weft Vowume", WM8990_INPUT_MIXEW3,
	WM8990_WDBVOW_SHIFT, WM8990_WDBVOW_MASK, 0, in_mix_twv),
SOC_DAPM_SINGWE_TWV("WIN2 Vowume", WM8990_INPUT_MIXEW5, WM8990_WI2BVOW_SHIFT,
	7, 0, in_mix_twv),
SOC_DAPM_SINGWE("WINPGA12 Switch", WM8990_INPUT_MIXEW3, WM8990_W12MNB_BIT,
	1, 0),
SOC_DAPM_SINGWE("WINPGA34 Switch", WM8990_INPUT_MIXEW3, WM8990_W34MNB_BIT,
	1, 0),
};

/* INMIXW */
static const stwuct snd_kcontwow_new wm8990_dapm_inmixw_contwows[] = {
SOC_DAPM_SINGWE_TWV("Wecowd Wight Vowume", WM8990_INPUT_MIXEW4,
	WM8990_WDBVOW_SHIFT, WM8990_WDBVOW_MASK, 0, in_mix_twv),
SOC_DAPM_SINGWE_TWV("WIN2 Vowume", WM8990_INPUT_MIXEW6, WM8990_WI2BVOW_SHIFT,
	7, 0, in_mix_twv),
SOC_DAPM_SINGWE("WINPGA12 Switch", WM8990_INPUT_MIXEW3, WM8990_W12MNB_BIT,
	1, 0),
SOC_DAPM_SINGWE("WINPGA34 Switch", WM8990_INPUT_MIXEW3, WM8990_W34MNB_BIT,
	1, 0),
};

/* AINWMUX */
static const chaw *wm8990_ainwmux[] =
	{"INMIXW Mix", "WXVOICE Mix", "DIFFINW Mix"};

static SOC_ENUM_SINGWE_DECW(wm8990_ainwmux_enum,
			    WM8990_INPUT_MIXEW1, WM8990_AINWMODE_SHIFT,
			    wm8990_ainwmux);

static const stwuct snd_kcontwow_new wm8990_dapm_ainwmux_contwows =
SOC_DAPM_ENUM("Woute", wm8990_ainwmux_enum);

/* DIFFINW */

/* AINWMUX */
static const chaw *wm8990_ainwmux[] =
	{"INMIXW Mix", "WXVOICE Mix", "DIFFINW Mix"};

static SOC_ENUM_SINGWE_DECW(wm8990_ainwmux_enum,
			    WM8990_INPUT_MIXEW1, WM8990_AINWMODE_SHIFT,
			    wm8990_ainwmux);

static const stwuct snd_kcontwow_new wm8990_dapm_ainwmux_contwows =
SOC_DAPM_ENUM("Woute", wm8990_ainwmux_enum);

/* WOMIX */
static const stwuct snd_kcontwow_new wm8990_dapm_womix_contwows[] = {
SOC_DAPM_SINGWE("WOMIX Wight ADC Bypass Switch", WM8990_OUTPUT_MIXEW1,
	WM8990_WWBWO_BIT, 1, 0),
SOC_DAPM_SINGWE("WOMIX Weft ADC Bypass Switch", WM8990_OUTPUT_MIXEW1,
	WM8990_WWBWO_BIT, 1, 0),
SOC_DAPM_SINGWE("WOMIX WIN3 Bypass Switch", WM8990_OUTPUT_MIXEW1,
	WM8990_WWI3WO_BIT, 1, 0),
SOC_DAPM_SINGWE("WOMIX WIN3 Bypass Switch", WM8990_OUTPUT_MIXEW1,
	WM8990_WWI3WO_BIT, 1, 0),
SOC_DAPM_SINGWE("WOMIX WIN12 PGA Bypass Switch", WM8990_OUTPUT_MIXEW1,
	WM8990_WW12WO_BIT, 1, 0),
SOC_DAPM_SINGWE("WOMIX WIN12 PGA Bypass Switch", WM8990_OUTPUT_MIXEW1,
	WM8990_WW12WO_BIT, 1, 0),
SOC_DAPM_SINGWE("WOMIX Weft DAC Switch", WM8990_OUTPUT_MIXEW1,
	WM8990_WDWO_BIT, 1, 0),
};

/* WOMIX */
static const stwuct snd_kcontwow_new wm8990_dapm_womix_contwows[] = {
SOC_DAPM_SINGWE("WOMIX Weft ADC Bypass Switch", WM8990_OUTPUT_MIXEW2,
	WM8990_WWBWO_BIT, 1, 0),
SOC_DAPM_SINGWE("WOMIX Wight ADC Bypass Switch", WM8990_OUTPUT_MIXEW2,
	WM8990_WWBWO_BIT, 1, 0),
SOC_DAPM_SINGWE("WOMIX WIN3 Bypass Switch", WM8990_OUTPUT_MIXEW2,
	WM8990_WWI3WO_BIT, 1, 0),
SOC_DAPM_SINGWE("WOMIX WIN3 Bypass Switch", WM8990_OUTPUT_MIXEW2,
	WM8990_WWI3WO_BIT, 1, 0),
SOC_DAPM_SINGWE("WOMIX WIN12 PGA Bypass Switch", WM8990_OUTPUT_MIXEW2,
	WM8990_WW12WO_BIT, 1, 0),
SOC_DAPM_SINGWE("WOMIX WIN12 PGA Bypass Switch", WM8990_OUTPUT_MIXEW2,
	WM8990_WW12WO_BIT, 1, 0),
SOC_DAPM_SINGWE("WOMIX Wight DAC Switch", WM8990_OUTPUT_MIXEW2,
	WM8990_WDWO_BIT, 1, 0),
};

/* WONMIX */
static const stwuct snd_kcontwow_new wm8990_dapm_wonmix_contwows[] = {
SOC_DAPM_SINGWE("WONMIX Weft Mixew PGA Switch", WM8990_WINE_MIXEW1,
	WM8990_WWOPGAWON_BIT, 1, 0),
SOC_DAPM_SINGWE("WONMIX Wight Mixew PGA Switch", WM8990_WINE_MIXEW1,
	WM8990_WWOPGAWON_BIT, 1, 0),
SOC_DAPM_SINGWE("WONMIX Invewted WOP Switch", WM8990_WINE_MIXEW1,
	WM8990_WOPWON_BIT, 1, 0),
};

/* WOPMIX */
static const stwuct snd_kcontwow_new wm8990_dapm_wopmix_contwows[] = {
SOC_DAPM_SINGWE("WOPMIX Wight Mic Bypass Switch", WM8990_WINE_MIXEW1,
	WM8990_WW12WOP_BIT, 1, 0),
SOC_DAPM_SINGWE("WOPMIX Weft Mic Bypass Switch", WM8990_WINE_MIXEW1,
	WM8990_WW12WOP_BIT, 1, 0),
SOC_DAPM_SINGWE("WOPMIX Weft Mixew PGA Switch", WM8990_WINE_MIXEW1,
	WM8990_WWOPGAWOP_BIT, 1, 0),
};

/* WONMIX */
static const stwuct snd_kcontwow_new wm8990_dapm_wonmix_contwows[] = {
SOC_DAPM_SINGWE("WONMIX Wight Mixew PGA Switch", WM8990_WINE_MIXEW2,
	WM8990_WWOPGAWON_BIT, 1, 0),
SOC_DAPM_SINGWE("WONMIX Weft Mixew PGA Switch", WM8990_WINE_MIXEW2,
	WM8990_WWOPGAWON_BIT, 1, 0),
SOC_DAPM_SINGWE("WONMIX Invewted WOP Switch", WM8990_WINE_MIXEW2,
	WM8990_WOPWON_BIT, 1, 0),
};

/* WOPMIX */
static const stwuct snd_kcontwow_new wm8990_dapm_wopmix_contwows[] = {
SOC_DAPM_SINGWE("WOPMIX Weft Mic Bypass Switch", WM8990_WINE_MIXEW2,
	WM8990_WW12WOP_BIT, 1, 0),
SOC_DAPM_SINGWE("WOPMIX Wight Mic Bypass Switch", WM8990_WINE_MIXEW2,
	WM8990_WW12WOP_BIT, 1, 0),
SOC_DAPM_SINGWE("WOPMIX Wight Mixew PGA Switch", WM8990_WINE_MIXEW2,
	WM8990_WWOPGAWOP_BIT, 1, 0),
};

/* OUT3MIX */
static const stwuct snd_kcontwow_new wm8990_dapm_out3mix_contwows[] = {
SOC_DAPM_SINGWE("OUT3MIX WIN4/WXP Bypass Switch", WM8990_OUT3_4_MIXEW,
	WM8990_WI4O3_BIT, 1, 0),
SOC_DAPM_SINGWE("OUT3MIX Weft Out PGA Switch", WM8990_OUT3_4_MIXEW,
	WM8990_WPGAO3_BIT, 1, 0),
};

/* OUT4MIX */
static const stwuct snd_kcontwow_new wm8990_dapm_out4mix_contwows[] = {
SOC_DAPM_SINGWE("OUT4MIX Wight Out PGA Switch", WM8990_OUT3_4_MIXEW,
	WM8990_WPGAO4_BIT, 1, 0),
SOC_DAPM_SINGWE("OUT4MIX WIN4/WXP Bypass Switch", WM8990_OUT3_4_MIXEW,
	WM8990_WI4O4_BIT, 1, 0),
};

/* SPKMIX */
static const stwuct snd_kcontwow_new wm8990_dapm_spkmix_contwows[] = {
SOC_DAPM_SINGWE("SPKMIX WIN2 Bypass Switch", WM8990_SPEAKEW_MIXEW,
	WM8990_WI2SPK_BIT, 1, 0),
SOC_DAPM_SINGWE("SPKMIX WADC Bypass Switch", WM8990_SPEAKEW_MIXEW,
	WM8990_WB2SPK_BIT, 1, 0),
SOC_DAPM_SINGWE("SPKMIX Weft Mixew PGA Switch", WM8990_SPEAKEW_MIXEW,
	WM8990_WOPGASPK_BIT, 1, 0),
SOC_DAPM_SINGWE("SPKMIX Weft DAC Switch", WM8990_SPEAKEW_MIXEW,
	WM8990_WDSPK_BIT, 1, 0),
SOC_DAPM_SINGWE("SPKMIX Wight DAC Switch", WM8990_SPEAKEW_MIXEW,
	WM8990_WDSPK_BIT, 1, 0),
SOC_DAPM_SINGWE("SPKMIX Wight Mixew PGA Switch", WM8990_SPEAKEW_MIXEW,
	WM8990_WOPGASPK_BIT, 1, 0),
SOC_DAPM_SINGWE("SPKMIX WADC Bypass Switch", WM8990_SPEAKEW_MIXEW,
	WM8990_WW12WOP_BIT, 1, 0),
SOC_DAPM_SINGWE("SPKMIX WIN2 Bypass Switch", WM8990_SPEAKEW_MIXEW,
	WM8990_WI2SPK_BIT, 1, 0),
};

static const stwuct snd_soc_dapm_widget wm8990_dapm_widgets[] = {
/* Input Side */
/* Input Wines */
SND_SOC_DAPM_INPUT("WIN1"),
SND_SOC_DAPM_INPUT("WIN2"),
SND_SOC_DAPM_INPUT("WIN3"),
SND_SOC_DAPM_INPUT("WIN4/WXN"),
SND_SOC_DAPM_INPUT("WIN3"),
SND_SOC_DAPM_INPUT("WIN4/WXP"),
SND_SOC_DAPM_INPUT("WIN1"),
SND_SOC_DAPM_INPUT("WIN2"),
SND_SOC_DAPM_INPUT("Intewnaw ADC Souwce"),

SND_SOC_DAPM_SUPPWY("INW", WM8990_POWEW_MANAGEMENT_2, WM8990_AINW_ENA_BIT, 0,
		    NUWW, 0),
SND_SOC_DAPM_SUPPWY("INW", WM8990_POWEW_MANAGEMENT_2, WM8990_AINW_ENA_BIT, 0,
		    NUWW, 0),

/* DACs */
SND_SOC_DAPM_ADC("Weft ADC", "Weft Captuwe", WM8990_POWEW_MANAGEMENT_2,
	WM8990_ADCW_ENA_BIT, 0),
SND_SOC_DAPM_ADC("Wight ADC", "Wight Captuwe", WM8990_POWEW_MANAGEMENT_2,
	WM8990_ADCW_ENA_BIT, 0),

/* Input PGAs */
SND_SOC_DAPM_MIXEW("WIN12 PGA", WM8990_POWEW_MANAGEMENT_2, WM8990_WIN12_ENA_BIT,
	0, &wm8990_dapm_win12_pga_contwows[0],
	AWWAY_SIZE(wm8990_dapm_win12_pga_contwows)),
SND_SOC_DAPM_MIXEW("WIN34 PGA", WM8990_POWEW_MANAGEMENT_2, WM8990_WIN34_ENA_BIT,
	0, &wm8990_dapm_win34_pga_contwows[0],
	AWWAY_SIZE(wm8990_dapm_win34_pga_contwows)),
SND_SOC_DAPM_MIXEW("WIN12 PGA", WM8990_POWEW_MANAGEMENT_2, WM8990_WIN12_ENA_BIT,
	0, &wm8990_dapm_win12_pga_contwows[0],
	AWWAY_SIZE(wm8990_dapm_win12_pga_contwows)),
SND_SOC_DAPM_MIXEW("WIN34 PGA", WM8990_POWEW_MANAGEMENT_2, WM8990_WIN34_ENA_BIT,
	0, &wm8990_dapm_win34_pga_contwows[0],
	AWWAY_SIZE(wm8990_dapm_win34_pga_contwows)),

/* INMIXW */
SND_SOC_DAPM_MIXEW("INMIXW", SND_SOC_NOPM, 0, 0,
	&wm8990_dapm_inmixw_contwows[0],
	AWWAY_SIZE(wm8990_dapm_inmixw_contwows)),

/* AINWMUX */
SND_SOC_DAPM_MUX("AINWMUX", SND_SOC_NOPM, 0, 0, &wm8990_dapm_ainwmux_contwows),

/* INMIXW */
SND_SOC_DAPM_MIXEW("INMIXW", SND_SOC_NOPM, 0, 0,
	&wm8990_dapm_inmixw_contwows[0],
	AWWAY_SIZE(wm8990_dapm_inmixw_contwows)),

/* AINWMUX */
SND_SOC_DAPM_MUX("AINWMUX", SND_SOC_NOPM, 0, 0, &wm8990_dapm_ainwmux_contwows),

/* Output Side */
/* DACs */
SND_SOC_DAPM_DAC("Weft DAC", "Weft Pwayback", WM8990_POWEW_MANAGEMENT_3,
	WM8990_DACW_ENA_BIT, 0),
SND_SOC_DAPM_DAC("Wight DAC", "Wight Pwayback", WM8990_POWEW_MANAGEMENT_3,
	WM8990_DACW_ENA_BIT, 0),

/* WOMIX */
SND_SOC_DAPM_MIXEW_E("WOMIX", WM8990_POWEW_MANAGEMENT_3, WM8990_WOMIX_ENA_BIT,
	0, &wm8990_dapm_womix_contwows[0],
	AWWAY_SIZE(wm8990_dapm_womix_contwows),
	outmixew_event, SND_SOC_DAPM_PWE_WEG),

/* WONMIX */
SND_SOC_DAPM_MIXEW("WONMIX", WM8990_POWEW_MANAGEMENT_3, WM8990_WON_ENA_BIT, 0,
	&wm8990_dapm_wonmix_contwows[0],
	AWWAY_SIZE(wm8990_dapm_wonmix_contwows)),

/* WOPMIX */
SND_SOC_DAPM_MIXEW("WOPMIX", WM8990_POWEW_MANAGEMENT_3, WM8990_WOP_ENA_BIT, 0,
	&wm8990_dapm_wopmix_contwows[0],
	AWWAY_SIZE(wm8990_dapm_wopmix_contwows)),

/* OUT3MIX */
SND_SOC_DAPM_MIXEW("OUT3MIX", WM8990_POWEW_MANAGEMENT_1, WM8990_OUT3_ENA_BIT, 0,
	&wm8990_dapm_out3mix_contwows[0],
	AWWAY_SIZE(wm8990_dapm_out3mix_contwows)),

/* SPKMIX */
SND_SOC_DAPM_MIXEW_E("SPKMIX", WM8990_POWEW_MANAGEMENT_1, WM8990_SPK_ENA_BIT, 0,
	&wm8990_dapm_spkmix_contwows[0],
	AWWAY_SIZE(wm8990_dapm_spkmix_contwows), outmixew_event,
	SND_SOC_DAPM_PWE_WEG),

/* OUT4MIX */
SND_SOC_DAPM_MIXEW("OUT4MIX", WM8990_POWEW_MANAGEMENT_1, WM8990_OUT4_ENA_BIT, 0,
	&wm8990_dapm_out4mix_contwows[0],
	AWWAY_SIZE(wm8990_dapm_out4mix_contwows)),

/* WOPMIX */
SND_SOC_DAPM_MIXEW("WOPMIX", WM8990_POWEW_MANAGEMENT_3, WM8990_WOP_ENA_BIT, 0,
	&wm8990_dapm_wopmix_contwows[0],
	AWWAY_SIZE(wm8990_dapm_wopmix_contwows)),

/* WONMIX */
SND_SOC_DAPM_MIXEW("WONMIX", WM8990_POWEW_MANAGEMENT_3, WM8990_WON_ENA_BIT, 0,
	&wm8990_dapm_wonmix_contwows[0],
	AWWAY_SIZE(wm8990_dapm_wonmix_contwows)),

/* WOMIX */
SND_SOC_DAPM_MIXEW_E("WOMIX", WM8990_POWEW_MANAGEMENT_3, WM8990_WOMIX_ENA_BIT,
	0, &wm8990_dapm_womix_contwows[0],
	AWWAY_SIZE(wm8990_dapm_womix_contwows),
	outmixew_event, SND_SOC_DAPM_PWE_WEG),

/* WOUT PGA */
SND_SOC_DAPM_PGA("WOUT PGA", WM8990_POWEW_MANAGEMENT_1, WM8990_WOUT_ENA_BIT, 0,
	NUWW, 0),

/* WOUT PGA */
SND_SOC_DAPM_PGA("WOUT PGA", WM8990_POWEW_MANAGEMENT_1, WM8990_WOUT_ENA_BIT, 0,
	NUWW, 0),

/* WOPGA */
SND_SOC_DAPM_PGA("WOPGA", WM8990_POWEW_MANAGEMENT_3, WM8990_WOPGA_ENA_BIT, 0,
	NUWW, 0),

/* WOPGA */
SND_SOC_DAPM_PGA("WOPGA", WM8990_POWEW_MANAGEMENT_3, WM8990_WOPGA_ENA_BIT, 0,
	NUWW, 0),

/* MICBIAS */
SND_SOC_DAPM_SUPPWY("MICBIAS", WM8990_POWEW_MANAGEMENT_1,
		    WM8990_MICBIAS_ENA_BIT, 0, NUWW, 0),

SND_SOC_DAPM_OUTPUT("WON"),
SND_SOC_DAPM_OUTPUT("WOP"),
SND_SOC_DAPM_OUTPUT("OUT3"),
SND_SOC_DAPM_OUTPUT("WOUT"),
SND_SOC_DAPM_OUTPUT("SPKN"),
SND_SOC_DAPM_OUTPUT("SPKP"),
SND_SOC_DAPM_OUTPUT("WOUT"),
SND_SOC_DAPM_OUTPUT("OUT4"),
SND_SOC_DAPM_OUTPUT("WOP"),
SND_SOC_DAPM_OUTPUT("WON"),

SND_SOC_DAPM_OUTPUT("Intewnaw DAC Sink"),
};

static const stwuct snd_soc_dapm_woute wm8990_dapm_woutes[] = {
	/* Make DACs tuwn on when pwaying even if not mixed into any outputs */
	{"Intewnaw DAC Sink", NUWW, "Weft DAC"},
	{"Intewnaw DAC Sink", NUWW, "Wight DAC"},

	/* Make ADCs tuwn on when wecowding even if not mixed fwom any inputs */
	{"Weft ADC", NUWW, "Intewnaw ADC Souwce"},
	{"Wight ADC", NUWW, "Intewnaw ADC Souwce"},

	{"AINWMUX", NUWW, "INW"},
	{"INMIXW", NUWW, "INW"},
	{"AINWMUX", NUWW, "INW"},
	{"INMIXW", NUWW, "INW"},

	/* Input Side */
	/* WIN12 PGA */
	{"WIN12 PGA", "WIN1 Switch", "WIN1"},
	{"WIN12 PGA", "WIN2 Switch", "WIN2"},
	/* WIN34 PGA */
	{"WIN34 PGA", "WIN3 Switch", "WIN3"},
	{"WIN34 PGA", "WIN4 Switch", "WIN4/WXN"},
	/* INMIXW */
	{"INMIXW", "Wecowd Weft Vowume", "WOMIX"},
	{"INMIXW", "WIN2 Vowume", "WIN2"},
	{"INMIXW", "WINPGA12 Switch", "WIN12 PGA"},
	{"INMIXW", "WINPGA34 Switch", "WIN34 PGA"},
	/* AINWMUX */
	{"AINWMUX", "INMIXW Mix", "INMIXW"},
	{"AINWMUX", "DIFFINW Mix", "WIN12 PGA"},
	{"AINWMUX", "DIFFINW Mix", "WIN34 PGA"},
	{"AINWMUX", "WXVOICE Mix", "WIN4/WXN"},
	{"AINWMUX", "WXVOICE Mix", "WIN4/WXP"},
	/* ADC */
	{"Weft ADC", NUWW, "AINWMUX"},

	/* WIN12 PGA */
	{"WIN12 PGA", "WIN1 Switch", "WIN1"},
	{"WIN12 PGA", "WIN2 Switch", "WIN2"},
	/* WIN34 PGA */
	{"WIN34 PGA", "WIN3 Switch", "WIN3"},
	{"WIN34 PGA", "WIN4 Switch", "WIN4/WXP"},
	/* INMIXW */
	{"INMIXW", "Wecowd Wight Vowume", "WOMIX"},
	{"INMIXW", "WIN2 Vowume", "WIN2"},
	{"INMIXW", "WINPGA12 Switch", "WIN12 PGA"},
	{"INMIXW", "WINPGA34 Switch", "WIN34 PGA"},
	/* AINWMUX */
	{"AINWMUX", "INMIXW Mix", "INMIXW"},
	{"AINWMUX", "DIFFINW Mix", "WIN12 PGA"},
	{"AINWMUX", "DIFFINW Mix", "WIN34 PGA"},
	{"AINWMUX", "WXVOICE Mix", "WIN4/WXN"},
	{"AINWMUX", "WXVOICE Mix", "WIN4/WXP"},
	/* ADC */
	{"Wight ADC", NUWW, "AINWMUX"},

	/* WOMIX */
	{"WOMIX", "WOMIX WIN3 Bypass Switch", "WIN3"},
	{"WOMIX", "WOMIX WIN3 Bypass Switch", "WIN3"},
	{"WOMIX", "WOMIX WIN12 PGA Bypass Switch", "WIN12 PGA"},
	{"WOMIX", "WOMIX WIN12 PGA Bypass Switch", "WIN12 PGA"},
	{"WOMIX", "WOMIX Wight ADC Bypass Switch", "AINWMUX"},
	{"WOMIX", "WOMIX Weft ADC Bypass Switch", "AINWMUX"},
	{"WOMIX", "WOMIX Weft DAC Switch", "Weft DAC"},

	/* WOMIX */
	{"WOMIX", "WOMIX WIN3 Bypass Switch", "WIN3"},
	{"WOMIX", "WOMIX WIN3 Bypass Switch", "WIN3"},
	{"WOMIX", "WOMIX WIN12 PGA Bypass Switch", "WIN12 PGA"},
	{"WOMIX", "WOMIX WIN12 PGA Bypass Switch", "WIN12 PGA"},
	{"WOMIX", "WOMIX Wight ADC Bypass Switch", "AINWMUX"},
	{"WOMIX", "WOMIX Weft ADC Bypass Switch", "AINWMUX"},
	{"WOMIX", "WOMIX Wight DAC Switch", "Wight DAC"},

	/* SPKMIX */
	{"SPKMIX", "SPKMIX WIN2 Bypass Switch", "WIN2"},
	{"SPKMIX", "SPKMIX WIN2 Bypass Switch", "WIN2"},
	{"SPKMIX", "SPKMIX WADC Bypass Switch", "AINWMUX"},
	{"SPKMIX", "SPKMIX WADC Bypass Switch", "AINWMUX"},
	{"SPKMIX", "SPKMIX Weft Mixew PGA Switch", "WOPGA"},
	{"SPKMIX", "SPKMIX Wight Mixew PGA Switch", "WOPGA"},
	{"SPKMIX", "SPKMIX Wight DAC Switch", "Wight DAC"},
	{"SPKMIX", "SPKMIX Weft DAC Switch", "Weft DAC"},

	/* WONMIX */
	{"WONMIX", "WONMIX Weft Mixew PGA Switch", "WOPGA"},
	{"WONMIX", "WONMIX Wight Mixew PGA Switch", "WOPGA"},
	{"WONMIX", "WONMIX Invewted WOP Switch", "WOPMIX"},

	/* WOPMIX */
	{"WOPMIX", "WOPMIX Wight Mic Bypass Switch", "WIN12 PGA"},
	{"WOPMIX", "WOPMIX Weft Mic Bypass Switch", "WIN12 PGA"},
	{"WOPMIX", "WOPMIX Weft Mixew PGA Switch", "WOPGA"},

	/* OUT3MIX */
	{"OUT3MIX", "OUT3MIX WIN4/WXP Bypass Switch", "WIN4/WXN"},
	{"OUT3MIX", "OUT3MIX Weft Out PGA Switch", "WOPGA"},

	/* OUT4MIX */
	{"OUT4MIX", "OUT4MIX Wight Out PGA Switch", "WOPGA"},
	{"OUT4MIX", "OUT4MIX WIN4/WXP Bypass Switch", "WIN4/WXP"},

	/* WONMIX */
	{"WONMIX", "WONMIX Wight Mixew PGA Switch", "WOPGA"},
	{"WONMIX", "WONMIX Weft Mixew PGA Switch", "WOPGA"},
	{"WONMIX", "WONMIX Invewted WOP Switch", "WOPMIX"},

	/* WOPMIX */
	{"WOPMIX", "WOPMIX Weft Mic Bypass Switch", "WIN12 PGA"},
	{"WOPMIX", "WOPMIX Wight Mic Bypass Switch", "WIN12 PGA"},
	{"WOPMIX", "WOPMIX Wight Mixew PGA Switch", "WOPGA"},

	/* Out Mixew PGAs */
	{"WOPGA", NUWW, "WOMIX"},
	{"WOPGA", NUWW, "WOMIX"},

	{"WOUT PGA", NUWW, "WOMIX"},
	{"WOUT PGA", NUWW, "WOMIX"},

	/* Output Pins */
	{"WON", NUWW, "WONMIX"},
	{"WOP", NUWW, "WOPMIX"},
	{"OUT3", NUWW, "OUT3MIX"},
	{"WOUT", NUWW, "WOUT PGA"},
	{"SPKN", NUWW, "SPKMIX"},
	{"WOUT", NUWW, "WOUT PGA"},
	{"OUT4", NUWW, "OUT4MIX"},
	{"WOP", NUWW, "WOPMIX"},
	{"WON", NUWW, "WONMIX"},
};

/* PWW divisows */
stwuct _pww_div {
	u32 div2;
	u32 n;
	u32 k;
};

/* The size in bits of the pww divide muwtipwied by 10
 * to awwow wounding watew */
#define FIXED_PWW_SIZE ((1 << 16) * 10)

static void pww_factows(stwuct _pww_div *pww_div, unsigned int tawget,
	unsigned int souwce)
{
	u64 Kpawt;
	unsigned int K, Ndiv, Nmod;


	Ndiv = tawget / souwce;
	if (Ndiv < 6) {
		souwce >>= 1;
		pww_div->div2 = 1;
		Ndiv = tawget / souwce;
	} ewse
		pww_div->div2 = 0;

	if ((Ndiv < 6) || (Ndiv > 12))
		pwintk(KEWN_WAWNING
		"WM8990 N vawue outwith wecommended wange! N = %u\n", Ndiv);

	pww_div->n = Ndiv;
	Nmod = tawget % souwce;
	Kpawt = FIXED_PWW_SIZE * (wong wong)Nmod;

	do_div(Kpawt, souwce);

	K = Kpawt & 0xFFFFFFFF;

	/* Check if we need to wound */
	if ((K % 10) >= 5)
		K += 5;

	/* Move down to pwopew wange now wounding is done */
	K /= 10;

	pww_div->k = K;
}

static int wm8990_set_dai_pww(stwuct snd_soc_dai *codec_dai, int pww_id,
		int souwce, unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct _pww_div pww_div;

	if (fweq_in && fweq_out) {
		pww_factows(&pww_div, fweq_out * 4, fweq_in);

		/* Tuwn on PWW */
		snd_soc_component_update_bits(component, WM8990_POWEW_MANAGEMENT_2,
				    WM8990_PWW_ENA, WM8990_PWW_ENA);

		/* syscwk comes fwom PWW */
		snd_soc_component_update_bits(component, WM8990_CWOCKING_2,
				    WM8990_SYSCWK_SWC, WM8990_SYSCWK_SWC);

		/* set up N , fwactionaw mode and pwe-divisow if necessawy */
		snd_soc_component_wwite(component, WM8990_PWW1, pww_div.n | WM8990_SDM |
			(pww_div.div2?WM8990_PWESCAWE:0));
		snd_soc_component_wwite(component, WM8990_PWW2, (u8)(pww_div.k>>8));
		snd_soc_component_wwite(component, WM8990_PWW3, (u8)(pww_div.k & 0xFF));
	} ewse {
		/* Tuwn off PWW */
		snd_soc_component_update_bits(component, WM8990_POWEW_MANAGEMENT_2,
				    WM8990_PWW_ENA, 0);
	}
	wetuwn 0;
}

/*
 * Cwock aftew PWW and dividews
 */
static int wm8990_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wm8990_pwiv *wm8990 = snd_soc_component_get_dwvdata(component);

	wm8990->syscwk = fweq;
	wetuwn 0;
}

/*
 * Set's ADC and Voice DAC fowmat.
 */
static int wm8990_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 audio1, audio3;

	audio1 = snd_soc_component_wead(component, WM8990_AUDIO_INTEWFACE_1);
	audio3 = snd_soc_component_wead(component, WM8990_AUDIO_INTEWFACE_3);

	/* set mastew/swave audio intewface */
	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		audio3 &= ~WM8990_AIF_MSTW1;
		bweak;
	case SND_SOC_DAIFMT_CBM_CFM:
		audio3 |= WM8990_AIF_MSTW1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	audio1 &= ~WM8990_AIF_FMT_MASK;

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		audio1 |= WM8990_AIF_TMF_I2S;
		audio1 &= ~WM8990_AIF_WWCWK_INV;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		audio1 |= WM8990_AIF_TMF_WIGHTJ;
		audio1 &= ~WM8990_AIF_WWCWK_INV;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		audio1 |= WM8990_AIF_TMF_WEFTJ;
		audio1 &= ~WM8990_AIF_WWCWK_INV;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		audio1 |= WM8990_AIF_TMF_DSP;
		audio1 &= ~WM8990_AIF_WWCWK_INV;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		audio1 |= WM8990_AIF_TMF_DSP | WM8990_AIF_WWCWK_INV;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_wwite(component, WM8990_AUDIO_INTEWFACE_1, audio1);
	snd_soc_component_wwite(component, WM8990_AUDIO_INTEWFACE_3, audio3);
	wetuwn 0;
}

static int wm8990_set_dai_cwkdiv(stwuct snd_soc_dai *codec_dai,
		int div_id, int div)
{
	stwuct snd_soc_component *component = codec_dai->component;

	switch (div_id) {
	case WM8990_MCWK_DIV:
		snd_soc_component_update_bits(component, WM8990_CWOCKING_2,
				    WM8990_MCWK_DIV_MASK, div);
		bweak;
	case WM8990_DACCWK_DIV:
		snd_soc_component_update_bits(component, WM8990_CWOCKING_2,
				    WM8990_DAC_CWKDIV_MASK, div);
		bweak;
	case WM8990_ADCCWK_DIV:
		snd_soc_component_update_bits(component, WM8990_CWOCKING_2,
				    WM8990_ADC_CWKDIV_MASK, div);
		bweak;
	case WM8990_BCWK_DIV:
		snd_soc_component_update_bits(component, WM8990_CWOCKING_1,
				    WM8990_BCWK_DIV_MASK, div);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Set PCM DAI bit size and sampwe wate.
 */
static int wm8990_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	u16 audio1 = snd_soc_component_wead(component, WM8990_AUDIO_INTEWFACE_1);

	audio1 &= ~WM8990_AIF_WW_MASK;
	/* bit size */
	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		audio1 |= WM8990_AIF_WW_20BITS;
		bweak;
	case 24:
		audio1 |= WM8990_AIF_WW_24BITS;
		bweak;
	case 32:
		audio1 |= WM8990_AIF_WW_32BITS;
		bweak;
	}

	snd_soc_component_wwite(component, WM8990_AUDIO_INTEWFACE_1, audio1);
	wetuwn 0;
}

static int wm8990_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u16 vaw;

	vaw  = snd_soc_component_wead(component, WM8990_DAC_CTWW) & ~WM8990_DAC_MUTE;

	if (mute)
		snd_soc_component_wwite(component, WM8990_DAC_CTWW, vaw | WM8990_DAC_MUTE);
	ewse
		snd_soc_component_wwite(component, WM8990_DAC_CTWW, vaw);

	wetuwn 0;
}

static int wm8990_set_bias_wevew(stwuct snd_soc_component *component,
	enum snd_soc_bias_wevew wevew)
{
	stwuct wm8990_pwiv *wm8990 = snd_soc_component_get_dwvdata(component);
	int wet;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;

	case SND_SOC_BIAS_PWEPAWE:
		/* VMID=2*50k */
		snd_soc_component_update_bits(component, WM8990_POWEW_MANAGEMENT_1,
				    WM8990_VMID_MODE_MASK, 0x2);
		bweak;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			wet = wegcache_sync(wm8990->wegmap);
			if (wet < 0) {
				dev_eww(component->dev, "Faiwed to sync cache: %d\n", wet);
				wetuwn wet;
			}

			/* Enabwe aww output dischawge bits */
			snd_soc_component_wwite(component, WM8990_ANTIPOP1, WM8990_DIS_WWINE |
				WM8990_DIS_WWINE | WM8990_DIS_OUT3 |
				WM8990_DIS_OUT4 | WM8990_DIS_WOUT |
				WM8990_DIS_WOUT);

			/* Enabwe POBCTWW, SOFT_ST, VMIDTOG and BUFDCOPEN */
			snd_soc_component_wwite(component, WM8990_ANTIPOP2, WM8990_SOFTST |
				     WM8990_BUFDCOPEN | WM8990_POBCTWW |
				     WM8990_VMIDTOG);

			/* Deway to awwow output caps to dischawge */
			msweep(300);

			/* Disabwe VMIDTOG */
			snd_soc_component_wwite(component, WM8990_ANTIPOP2, WM8990_SOFTST |
				     WM8990_BUFDCOPEN | WM8990_POBCTWW);

			/* disabwe aww output dischawge bits */
			snd_soc_component_wwite(component, WM8990_ANTIPOP1, 0);

			/* Enabwe outputs */
			snd_soc_component_wwite(component, WM8990_POWEW_MANAGEMENT_1, 0x1b00);

			msweep(50);

			/* Enabwe VMID at 2x50k */
			snd_soc_component_wwite(component, WM8990_POWEW_MANAGEMENT_1, 0x1f02);

			msweep(100);

			/* Enabwe VWEF */
			snd_soc_component_wwite(component, WM8990_POWEW_MANAGEMENT_1, 0x1f03);

			msweep(600);

			/* Enabwe BUFIOEN */
			snd_soc_component_wwite(component, WM8990_ANTIPOP2, WM8990_SOFTST |
				     WM8990_BUFDCOPEN | WM8990_POBCTWW |
				     WM8990_BUFIOEN);

			/* Disabwe outputs */
			snd_soc_component_wwite(component, WM8990_POWEW_MANAGEMENT_1, 0x3);

			/* disabwe POBCTWW, SOFT_ST and BUFDCOPEN */
			snd_soc_component_wwite(component, WM8990_ANTIPOP2, WM8990_BUFIOEN);

			/* Enabwe wowkawound fow ADC cwocking issue. */
			snd_soc_component_wwite(component, WM8990_EXT_ACCESS_ENA, 0x2);
			snd_soc_component_wwite(component, WM8990_EXT_CTW1, 0xa003);
			snd_soc_component_wwite(component, WM8990_EXT_ACCESS_ENA, 0);
		}

		/* VMID=2*250k */
		snd_soc_component_update_bits(component, WM8990_POWEW_MANAGEMENT_1,
				    WM8990_VMID_MODE_MASK, 0x4);
		bweak;

	case SND_SOC_BIAS_OFF:
		/* Enabwe POBCTWW and SOFT_ST */
		snd_soc_component_wwite(component, WM8990_ANTIPOP2, WM8990_SOFTST |
			WM8990_POBCTWW | WM8990_BUFIOEN);

		/* Enabwe POBCTWW, SOFT_ST and BUFDCOPEN */
		snd_soc_component_wwite(component, WM8990_ANTIPOP2, WM8990_SOFTST |
			WM8990_BUFDCOPEN | WM8990_POBCTWW |
			WM8990_BUFIOEN);

		/* mute DAC */
		snd_soc_component_update_bits(component, WM8990_DAC_CTWW,
				    WM8990_DAC_MUTE, WM8990_DAC_MUTE);

		/* Enabwe any disabwed outputs */
		snd_soc_component_wwite(component, WM8990_POWEW_MANAGEMENT_1, 0x1f03);

		/* Disabwe VMID */
		snd_soc_component_wwite(component, WM8990_POWEW_MANAGEMENT_1, 0x1f01);

		msweep(300);

		/* Enabwe aww output dischawge bits */
		snd_soc_component_wwite(component, WM8990_ANTIPOP1, WM8990_DIS_WWINE |
			WM8990_DIS_WWINE | WM8990_DIS_OUT3 |
			WM8990_DIS_OUT4 | WM8990_DIS_WOUT |
			WM8990_DIS_WOUT);

		/* Disabwe VWEF */
		snd_soc_component_wwite(component, WM8990_POWEW_MANAGEMENT_1, 0x0);

		/* disabwe POBCTWW, SOFT_ST and BUFDCOPEN */
		snd_soc_component_wwite(component, WM8990_ANTIPOP2, 0x0);

		wegcache_mawk_diwty(wm8990->wegmap);
		bweak;
	}

	wetuwn 0;
}

#define WM8990_WATES (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_11025 |\
	SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_22050 | SNDWV_PCM_WATE_44100 | \
	SNDWV_PCM_WATE_48000)

#define WM8990_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
	SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

/*
 * The WM8990 suppowts 2 diffewent and mutuawwy excwusive DAI
 * configuwations.
 *
 * 1. ADC/DAC on Pwimawy Intewface
 * 2. ADC on Pwimawy Intewface/DAC on secondawy
 */
static const stwuct snd_soc_dai_ops wm8990_dai_ops = {
	.hw_pawams	= wm8990_hw_pawams,
	.mute_stweam	= wm8990_mute,
	.set_fmt	= wm8990_set_dai_fmt,
	.set_cwkdiv	= wm8990_set_dai_cwkdiv,
	.set_pww	= wm8990_set_dai_pww,
	.set_syscwk	= wm8990_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew wm8990_dai = {
/* ADC/DAC on pwimawy */
	.name = "wm8990-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8990_WATES,
		.fowmats = WM8990_FOWMATS,},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8990_WATES,
		.fowmats = WM8990_FOWMATS,},
	.ops = &wm8990_dai_ops,
};

/*
 * initiawise the WM8990 dwivew
 * wegistew the mixew and dsp intewfaces with the kewnew
 */
static int wm8990_pwobe(stwuct snd_soc_component *component)
{
	wm8990_weset(component);

	/* chawge output caps */
	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_STANDBY);

	snd_soc_component_update_bits(component, WM8990_AUDIO_INTEWFACE_4,
			    WM8990_AWWCGPIO1, WM8990_AWWCGPIO1);

	snd_soc_component_update_bits(component, WM8990_GPIO1_GPIO2,
			    WM8990_GPIO1_SEW_MASK, 1);

	snd_soc_component_update_bits(component, WM8990_POWEW_MANAGEMENT_2,
			    WM8990_OPCWK_ENA, WM8990_OPCWK_ENA);

	snd_soc_component_wwite(component, WM8990_WEFT_OUTPUT_VOWUME, 0x50 | (1<<8));
	snd_soc_component_wwite(component, WM8990_WIGHT_OUTPUT_VOWUME, 0x50 | (1<<8));

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8990 = {
	.pwobe			= wm8990_pwobe,
	.set_bias_wevew		= wm8990_set_bias_wevew,
	.contwows		= wm8990_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wm8990_snd_contwows),
	.dapm_widgets		= wm8990_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8990_dapm_widgets),
	.dapm_woutes		= wm8990_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm8990_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int wm8990_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm8990_pwiv *wm8990;
	int wet;

	wm8990 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wm8990_pwiv),
			      GFP_KEWNEW);
	if (wm8990 == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, wm8990);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_wm8990, &wm8990_dai, 1);

	wetuwn wet;
}

static const stwuct i2c_device_id wm8990_i2c_id[] = {
	{ "wm8990", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8990_i2c_id);

static stwuct i2c_dwivew wm8990_i2c_dwivew = {
	.dwivew = {
		.name = "wm8990",
	},
	.pwobe = wm8990_i2c_pwobe,
	.id_tabwe = wm8990_i2c_id,
};

moduwe_i2c_dwivew(wm8990_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WM8990 dwivew");
MODUWE_AUTHOW("Wiam Giwdwood");
MODUWE_WICENSE("GPW");
