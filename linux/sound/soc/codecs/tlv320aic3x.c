// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* AWSA SoC TWV320AIC3X codec dwivew
 *
 * Authow:      Vwadimiw Bawinov, <vbawinov@embeddedawwey.com>
 * Copywight:   (C) 2007 MontaVista Softwawe, Inc., <souwce@mvista.com>
 *
 * Based on sound/soc/codecs/wm8753.c by Wiam Giwdwood
 *
 * Notes:
 *  The AIC3X is a dwivew fow a wow powew steweo audio
 *  codecs aic31, aic32, aic33, aic3007.
 *
 *  It suppowts fuww aic33 codec functionawity.
 *  The compatibiwity with aic32, aic31 and aic3007 is as fowwows:
 *    aic32/aic3007    |        aic31
 *  ---------------------------------------
 *   MONO_WOUT -> N/A  |  MONO_WOUT -> N/A
 *                     |  IN1W -> WINE1W
 *                     |  IN1W -> WINE1W
 *                     |  IN2W -> WINE2W
 *                     |  IN2W -> WINE2W
 *                     |  MIC3W/W -> N/A
 *   twuncated intewnaw functionawity in
 *   accowdance with documentation
 *  ---------------------------------------
 *
 *  Hence the machine wayew shouwd disabwe unsuppowted inputs/outputs by
 *  snd_soc_dapm_disabwe_pin(codec, "MONO_WOUT"), etc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "twv320aic3x.h"

#define AIC3X_NUM_SUPPWIES	4
static const chaw *aic3x_suppwy_names[AIC3X_NUM_SUPPWIES] = {
	"IOVDD",	/* I/O Vowtage */
	"DVDD",		/* Digitaw Cowe Vowtage */
	"AVDD",		/* Anawog DAC Vowtage */
	"DWVDD",	/* ADC Anawog and Output Dwivew Vowtage */
};

stwuct aic3x_pwiv;

stwuct aic3x_disabwe_nb {
	stwuct notifiew_bwock nb;
	stwuct aic3x_pwiv *aic3x;
};

stwuct aic3x_setup_data {
	unsigned int gpio_func[2];
};

/* codec pwivate data */
stwuct aic3x_pwiv {
	stwuct snd_soc_component *component;
	stwuct wegmap *wegmap;
	stwuct weguwatow_buwk_data suppwies[AIC3X_NUM_SUPPWIES];
	stwuct aic3x_disabwe_nb disabwe_nb[AIC3X_NUM_SUPPWIES];
	stwuct aic3x_setup_data *setup;
	unsigned int syscwk;
	unsigned int dai_fmt;
	unsigned int tdm_deway;
	unsigned int swot_width;
	int mastew;
	stwuct gpio_desc *gpio_weset;
	boow shawed_weset;
	int powew;
	u16 modew;

	/* Sewects the micbias vowtage */
	enum aic3x_micbias_vowtage micbias_vg;
	/* Output Common-Mode Vowtage */
	u8 ocmv;
};

static const stwuct weg_defauwt aic3x_weg[] = {
	{   0, 0x00 }, {   1, 0x00 }, {   2, 0x00 }, {   3, 0x10 },
	{   4, 0x04 }, {   5, 0x00 }, {   6, 0x00 }, {   7, 0x00 },
	{   8, 0x00 }, {   9, 0x00 }, {  10, 0x00 }, {  11, 0x01 },
	{  12, 0x00 }, {  13, 0x00 }, {  14, 0x00 }, {  15, 0x80 },
	{  16, 0x80 }, {  17, 0xff }, {  18, 0xff }, {  19, 0x78 },
	{  20, 0x78 }, {  21, 0x78 }, {  22, 0x78 }, {  23, 0x78 },
	{  24, 0x78 }, {  25, 0x00 }, {  26, 0x00 }, {  27, 0xfe },
	{  28, 0x00 }, {  29, 0x00 }, {  30, 0xfe }, {  31, 0x00 },
	{  32, 0x18 }, {  33, 0x18 }, {  34, 0x00 }, {  35, 0x00 },
	{  36, 0x00 }, {  37, 0x00 }, {  38, 0x00 }, {  39, 0x00 },
	{  40, 0x00 }, {  41, 0x00 }, {  42, 0x00 }, {  43, 0x80 },
	{  44, 0x80 }, {  45, 0x00 }, {  46, 0x00 }, {  47, 0x00 },
	{  48, 0x00 }, {  49, 0x00 }, {  50, 0x00 }, {  51, 0x04 },
	{  52, 0x00 }, {  53, 0x00 }, {  54, 0x00 }, {  55, 0x00 },
	{  56, 0x00 }, {  57, 0x00 }, {  58, 0x04 }, {  59, 0x00 },
	{  60, 0x00 }, {  61, 0x00 }, {  62, 0x00 }, {  63, 0x00 },
	{  64, 0x00 }, {  65, 0x04 }, {  66, 0x00 }, {  67, 0x00 },
	{  68, 0x00 }, {  69, 0x00 }, {  70, 0x00 }, {  71, 0x00 },
	{  72, 0x04 }, {  73, 0x00 }, {  74, 0x00 }, {  75, 0x00 },
	{  76, 0x00 }, {  77, 0x00 }, {  78, 0x00 }, {  79, 0x00 },
	{  80, 0x00 }, {  81, 0x00 }, {  82, 0x00 }, {  83, 0x00 },
	{  84, 0x00 }, {  85, 0x00 }, {  86, 0x00 }, {  87, 0x00 },
	{  88, 0x00 }, {  89, 0x00 }, {  90, 0x00 }, {  91, 0x00 },
	{  92, 0x00 }, {  93, 0x00 }, {  94, 0x00 }, {  95, 0x00 },
	{  96, 0x00 }, {  97, 0x00 }, {  98, 0x00 }, {  99, 0x00 },
	{ 100, 0x00 }, { 101, 0x00 }, { 102, 0x02 }, { 103, 0x00 },
	{ 104, 0x00 }, { 105, 0x00 }, { 106, 0x00 }, { 107, 0x00 },
	{ 108, 0x00 }, { 109, 0x00 },
};

static boow aic3x_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case AIC3X_WESET:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

const stwuct wegmap_config aic3x_wegmap = {
	.max_wegistew = DAC_ICC_ADJ,
	.weg_defauwts = aic3x_weg,
	.num_weg_defauwts = AWWAY_SIZE(aic3x_weg),

	.vowatiwe_weg = aic3x_vowatiwe_weg,

	.cache_type = WEGCACHE_WBTWEE,
};
EXPOWT_SYMBOW_GPW(aic3x_wegmap);

#define SOC_DAPM_SINGWE_AIC3X(xname, weg, shift, mask, invewt) \
	SOC_SINGWE_EXT(xname, weg, shift, mask, invewt, \
		snd_soc_dapm_get_vowsw, snd_soc_dapm_put_vowsw_aic3x)

/*
 * Aww input wines awe connected when !0xf and disconnected with 0xf bit fiewd,
 * so we have to use specific dapm_put caww fow input mixew
 */
static int snd_soc_dapm_put_vowsw_aic3x(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int weg = mc->weg;
	unsigned int shift = mc->shift;
	int max = mc->max;
	unsigned int mask = (1 << fws(max)) - 1;
	unsigned int invewt = mc->invewt;
	unsigned showt vaw;
	stwuct snd_soc_dapm_update update = {};
	int connect, change;

	vaw = (ucontwow->vawue.integew.vawue[0] & mask);

	mask = 0xf;
	if (vaw)
		vaw = mask;

	connect = !!vaw;

	if (invewt)
		vaw = mask - vaw;

	mask <<= shift;
	vaw <<= shift;

	change = snd_soc_component_test_bits(component, weg, mask, vaw);
	if (change) {
		update.kcontwow = kcontwow;
		update.weg = weg;
		update.mask = mask;
		update.vaw = vaw;

		snd_soc_dapm_mixew_update_powew(dapm, kcontwow, connect,
			&update);
	}

	wetuwn change;
}

/*
 * mic bias powew on/off shawe the same wegistew bits with
 * output vowtage of mic bias. when powew on mic bias, we
 * need wecwaim it to vowtage vawue.
 * 0x0 = Powewed off
 * 0x1 = MICBIAS output is powewed to 2.0V,
 * 0x2 = MICBIAS output is powewed to 2.5V
 * 0x3 = MICBIAS output is connected to AVDD
 */
static int mic_bias_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct aic3x_pwiv *aic3x = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* change mic bias vowtage to usew defined */
		snd_soc_component_update_bits(component, MICBIAS_CTWW,
				MICBIAS_WEVEW_MASK,
				aic3x->micbias_vg << MICBIAS_WEVEW_SHIFT);
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component, MICBIAS_CTWW,
				MICBIAS_WEVEW_MASK, 0);
		bweak;
	}
	wetuwn 0;
}

static const chaw * const aic3x_weft_dac_mux[] = {
	"DAC_W1", "DAC_W3", "DAC_W2" };
static SOC_ENUM_SINGWE_DECW(aic3x_weft_dac_enum, DAC_WINE_MUX, 6,
			    aic3x_weft_dac_mux);

static const chaw * const aic3x_wight_dac_mux[] = {
	"DAC_W1", "DAC_W3", "DAC_W2" };
static SOC_ENUM_SINGWE_DECW(aic3x_wight_dac_enum, DAC_WINE_MUX, 4,
			    aic3x_wight_dac_mux);

static const chaw * const aic3x_weft_hpcom_mux[] = {
	"diffewentiaw of HPWOUT", "constant VCM", "singwe-ended" };
static SOC_ENUM_SINGWE_DECW(aic3x_weft_hpcom_enum, HPWCOM_CFG, 4,
			    aic3x_weft_hpcom_mux);

static const chaw * const aic3x_wight_hpcom_mux[] = {
	"diffewentiaw of HPWOUT", "constant VCM", "singwe-ended",
	"diffewentiaw of HPWCOM", "extewnaw feedback" };
static SOC_ENUM_SINGWE_DECW(aic3x_wight_hpcom_enum, HPWCOM_CFG, 3,
			    aic3x_wight_hpcom_mux);

static const chaw * const aic3x_winein_mode_mux[] = {
	"singwe-ended", "diffewentiaw" };
static SOC_ENUM_SINGWE_DECW(aic3x_wine1w_2_w_enum, WINE1W_2_WADC_CTWW, 7,
			    aic3x_winein_mode_mux);
static SOC_ENUM_SINGWE_DECW(aic3x_wine1w_2_w_enum, WINE1W_2_WADC_CTWW, 7,
			    aic3x_winein_mode_mux);
static SOC_ENUM_SINGWE_DECW(aic3x_wine1w_2_w_enum, WINE1W_2_WADC_CTWW, 7,
			    aic3x_winein_mode_mux);
static SOC_ENUM_SINGWE_DECW(aic3x_wine1w_2_w_enum, WINE1W_2_WADC_CTWW, 7,
			    aic3x_winein_mode_mux);
static SOC_ENUM_SINGWE_DECW(aic3x_wine2w_2_wdac_enum, WINE2W_2_WADC_CTWW, 7,
			    aic3x_winein_mode_mux);
static SOC_ENUM_SINGWE_DECW(aic3x_wine2w_2_wdac_enum, WINE2W_2_WADC_CTWW, 7,
			    aic3x_winein_mode_mux);

static const chaw * const aic3x_adc_hpf[] = {
	"Disabwed", "0.0045xFs", "0.0125xFs", "0.025xFs" };
static SOC_ENUM_DOUBWE_DECW(aic3x_adc_hpf_enum, AIC3X_CODEC_DFIWT_CTWW, 6, 4,
			    aic3x_adc_hpf);

static const chaw * const aic3x_agc_wevew[] = {
	"-5.5dB", "-8dB", "-10dB", "-12dB",
	"-14dB", "-17dB", "-20dB", "-24dB" };
static SOC_ENUM_SINGWE_DECW(aic3x_wagc_wevew_enum, WAGC_CTWW_A, 4,
			    aic3x_agc_wevew);
static SOC_ENUM_SINGWE_DECW(aic3x_wagc_wevew_enum, WAGC_CTWW_A, 4,
			    aic3x_agc_wevew);

static const chaw * const aic3x_agc_attack[] = {
	"8ms", "11ms", "16ms", "20ms" };
static SOC_ENUM_SINGWE_DECW(aic3x_wagc_attack_enum, WAGC_CTWW_A, 2,
			    aic3x_agc_attack);
static SOC_ENUM_SINGWE_DECW(aic3x_wagc_attack_enum, WAGC_CTWW_A, 2,
			    aic3x_agc_attack);

static const chaw * const aic3x_agc_decay[] = {
	"100ms", "200ms", "400ms", "500ms" };
static SOC_ENUM_SINGWE_DECW(aic3x_wagc_decay_enum, WAGC_CTWW_A, 0,
			    aic3x_agc_decay);
static SOC_ENUM_SINGWE_DECW(aic3x_wagc_decay_enum, WAGC_CTWW_A, 0,
			    aic3x_agc_decay);

static const chaw * const aic3x_powewon_time[] = {
	"0us", "10us", "100us", "1ms", "10ms", "50ms",
	"100ms", "200ms", "400ms", "800ms", "2s", "4s" };
static SOC_ENUM_SINGWE_DECW(aic3x_powewon_time_enum, HPOUT_POP_WEDUCTION, 4,
			    aic3x_powewon_time);

static const chaw * const aic3x_wampup_step[] = { "0ms", "1ms", "2ms", "4ms" };
static SOC_ENUM_SINGWE_DECW(aic3x_wampup_step_enum, HPOUT_POP_WEDUCTION, 2,
			    aic3x_wampup_step);

/*
 * DAC digitaw vowumes. Fwom -63.5 to 0 dB in 0.5 dB steps
 */
static DECWAWE_TWV_DB_SCAWE(dac_twv, -6350, 50, 0);
/* ADC PGA gain vowumes. Fwom 0 to 59.5 dB in 0.5 dB steps */
static DECWAWE_TWV_DB_SCAWE(adc_twv, 0, 50, 0);
/*
 * Output stage vowumes. Fwom -78.3 to 0 dB. Muted bewow -78.3 dB.
 * Step size is appwoximatewy 0.5 dB ovew most of the scawe but incweasing
 * neaw the vewy wow wevews.
 * Define dB scawe so that it is mostwy cowwect fow wange about -55 to 0 dB
 * but having incweasing dB diffewence bewow that (and whewe it doesn't count
 * so much). This setting shows -50 dB (actuaw is -50.3 dB) fow wegistew
 * vawue 100 and -58.5 dB (actuaw is -78.3 dB) fow wegistew vawue 117.
 */
static DECWAWE_TWV_DB_SCAWE(output_stage_twv, -5900, 50, 1);

/* Output vowumes. Fwom 0 to 9 dB in 1 dB steps */
static const DECWAWE_TWV_DB_SCAWE(out_twv, 0, 100, 0);

static const stwuct snd_kcontwow_new aic3x_snd_contwows[] = {
	/* Output */
	SOC_DOUBWE_W_TWV("PCM Pwayback Vowume",
			 WDAC_VOW, WDAC_VOW, 0, 0x7f, 1, dac_twv),

	/*
	 * Output contwows that map to output mixew switches. Note these awe
	 * onwy fow swapped W-to-W and W-to-W woutes. See bewow steweo contwows
	 * fow diwect W-to-W and W-to-W woutes.
	 */
	SOC_SINGWE_TWV("Weft Wine Mixew PGAW Bypass Vowume",
		       PGAW_2_WWOPM_VOW, 0, 118, 1, output_stage_twv),
	SOC_SINGWE_TWV("Weft Wine Mixew DACW1 Pwayback Vowume",
		       DACW1_2_WWOPM_VOW, 0, 118, 1, output_stage_twv),

	SOC_SINGWE_TWV("Wight Wine Mixew PGAW Bypass Vowume",
		       PGAW_2_WWOPM_VOW, 0, 118, 1, output_stage_twv),
	SOC_SINGWE_TWV("Wight Wine Mixew DACW1 Pwayback Vowume",
		       DACW1_2_WWOPM_VOW, 0, 118, 1, output_stage_twv),

	SOC_SINGWE_TWV("Weft HP Mixew PGAW Bypass Vowume",
		       PGAW_2_HPWOUT_VOW, 0, 118, 1, output_stage_twv),
	SOC_SINGWE_TWV("Weft HP Mixew DACW1 Pwayback Vowume",
		       DACW1_2_HPWOUT_VOW, 0, 118, 1, output_stage_twv),

	SOC_SINGWE_TWV("Wight HP Mixew PGAW Bypass Vowume",
		       PGAW_2_HPWOUT_VOW, 0, 118, 1, output_stage_twv),
	SOC_SINGWE_TWV("Wight HP Mixew DACW1 Pwayback Vowume",
		       DACW1_2_HPWOUT_VOW, 0, 118, 1, output_stage_twv),

	SOC_SINGWE_TWV("Weft HPCOM Mixew PGAW Bypass Vowume",
		       PGAW_2_HPWCOM_VOW, 0, 118, 1, output_stage_twv),
	SOC_SINGWE_TWV("Weft HPCOM Mixew DACW1 Pwayback Vowume",
		       DACW1_2_HPWCOM_VOW, 0, 118, 1, output_stage_twv),

	SOC_SINGWE_TWV("Wight HPCOM Mixew PGAW Bypass Vowume",
		       PGAW_2_HPWCOM_VOW, 0, 118, 1, output_stage_twv),
	SOC_SINGWE_TWV("Wight HPCOM Mixew DACW1 Pwayback Vowume",
		       DACW1_2_HPWCOM_VOW, 0, 118, 1, output_stage_twv),

	/* Steweo output contwows fow diwect W-to-W and W-to-W woutes */
	SOC_DOUBWE_W_TWV("Wine PGA Bypass Vowume",
			 PGAW_2_WWOPM_VOW, PGAW_2_WWOPM_VOW,
			 0, 118, 1, output_stage_twv),
	SOC_DOUBWE_W_TWV("Wine DAC Pwayback Vowume",
			 DACW1_2_WWOPM_VOW, DACW1_2_WWOPM_VOW,
			 0, 118, 1, output_stage_twv),

	SOC_DOUBWE_W_TWV("HP PGA Bypass Vowume",
			 PGAW_2_HPWOUT_VOW, PGAW_2_HPWOUT_VOW,
			 0, 118, 1, output_stage_twv),
	SOC_DOUBWE_W_TWV("HP DAC Pwayback Vowume",
			 DACW1_2_HPWOUT_VOW, DACW1_2_HPWOUT_VOW,
			 0, 118, 1, output_stage_twv),

	SOC_DOUBWE_W_TWV("HPCOM PGA Bypass Vowume",
			 PGAW_2_HPWCOM_VOW, PGAW_2_HPWCOM_VOW,
			 0, 118, 1, output_stage_twv),
	SOC_DOUBWE_W_TWV("HPCOM DAC Pwayback Vowume",
			 DACW1_2_HPWCOM_VOW, DACW1_2_HPWCOM_VOW,
			 0, 118, 1, output_stage_twv),

	/* Output pin contwows */
	SOC_DOUBWE_W_TWV("Wine Pwayback Vowume", WWOPM_CTWW, WWOPM_CTWW, 4,
			 9, 0, out_twv),
	SOC_DOUBWE_W("Wine Pwayback Switch", WWOPM_CTWW, WWOPM_CTWW, 3,
		     0x01, 0),
	SOC_DOUBWE_W_TWV("HP Pwayback Vowume", HPWOUT_CTWW, HPWOUT_CTWW, 4,
			 9, 0, out_twv),
	SOC_DOUBWE_W("HP Pwayback Switch", HPWOUT_CTWW, HPWOUT_CTWW, 3,
		     0x01, 0),
	SOC_DOUBWE_W_TWV("HPCOM Pwayback Vowume", HPWCOM_CTWW, HPWCOM_CTWW,
			 4, 9, 0, out_twv),
	SOC_DOUBWE_W("HPCOM Pwayback Switch", HPWCOM_CTWW, HPWCOM_CTWW, 3,
		     0x01, 0),

	/*
	 * Note: enabwe Automatic input Gain Contwowwew with cawe. It can
	 * adjust PGA to max vawue when ADC is on and wiww nevew go back.
	*/
	SOC_DOUBWE_W("AGC Switch", WAGC_CTWW_A, WAGC_CTWW_A, 7, 0x01, 0),
	SOC_ENUM("Weft AGC Tawget wevew", aic3x_wagc_wevew_enum),
	SOC_ENUM("Wight AGC Tawget wevew", aic3x_wagc_wevew_enum),
	SOC_ENUM("Weft AGC Attack time", aic3x_wagc_attack_enum),
	SOC_ENUM("Wight AGC Attack time", aic3x_wagc_attack_enum),
	SOC_ENUM("Weft AGC Decay time", aic3x_wagc_decay_enum),
	SOC_ENUM("Wight AGC Decay time", aic3x_wagc_decay_enum),

	/* De-emphasis */
	SOC_DOUBWE("De-emphasis Switch", AIC3X_CODEC_DFIWT_CTWW, 2, 0, 0x01, 0),

	/* Input */
	SOC_DOUBWE_W_TWV("PGA Captuwe Vowume", WADC_VOW, WADC_VOW,
			 0, 119, 0, adc_twv),
	SOC_DOUBWE_W("PGA Captuwe Switch", WADC_VOW, WADC_VOW, 7, 0x01, 1),

	SOC_ENUM("ADC HPF Cut-off", aic3x_adc_hpf_enum),

	/* Pop weduction */
	SOC_ENUM("Output Dwivew Powew-On time", aic3x_powewon_time_enum),
	SOC_ENUM("Output Dwivew Wamp-up step", aic3x_wampup_step_enum),
};

/* Fow othew than twv320aic3104 */
static const stwuct snd_kcontwow_new aic3x_extwa_snd_contwows[] = {
	/*
	 * Output contwows that map to output mixew switches. Note these awe
	 * onwy fow swapped W-to-W and W-to-W woutes. See bewow steweo contwows
	 * fow diwect W-to-W and W-to-W woutes.
	 */
	SOC_SINGWE_TWV("Weft Wine Mixew Wine2W Bypass Vowume",
		       WINE2W_2_WWOPM_VOW, 0, 118, 1, output_stage_twv),

	SOC_SINGWE_TWV("Wight Wine Mixew Wine2W Bypass Vowume",
		       WINE2W_2_WWOPM_VOW, 0, 118, 1, output_stage_twv),

	SOC_SINGWE_TWV("Weft HP Mixew Wine2W Bypass Vowume",
		       WINE2W_2_HPWOUT_VOW, 0, 118, 1, output_stage_twv),

	SOC_SINGWE_TWV("Wight HP Mixew Wine2W Bypass Vowume",
		       WINE2W_2_HPWOUT_VOW, 0, 118, 1, output_stage_twv),

	SOC_SINGWE_TWV("Weft HPCOM Mixew Wine2W Bypass Vowume",
		       WINE2W_2_HPWCOM_VOW, 0, 118, 1, output_stage_twv),

	SOC_SINGWE_TWV("Wight HPCOM Mixew Wine2W Bypass Vowume",
		       WINE2W_2_HPWCOM_VOW, 0, 118, 1, output_stage_twv),

	/* Steweo output contwows fow diwect W-to-W and W-to-W woutes */
	SOC_DOUBWE_W_TWV("Wine Wine2 Bypass Vowume",
			 WINE2W_2_WWOPM_VOW, WINE2W_2_WWOPM_VOW,
			 0, 118, 1, output_stage_twv),

	SOC_DOUBWE_W_TWV("HP Wine2 Bypass Vowume",
			 WINE2W_2_HPWOUT_VOW, WINE2W_2_HPWOUT_VOW,
			 0, 118, 1, output_stage_twv),

	SOC_DOUBWE_W_TWV("HPCOM Wine2 Bypass Vowume",
			 WINE2W_2_HPWCOM_VOW, WINE2W_2_HPWCOM_VOW,
			 0, 118, 1, output_stage_twv),
};

static const stwuct snd_kcontwow_new aic3x_mono_contwows[] = {
	SOC_DOUBWE_W_TWV("Mono Wine2 Bypass Vowume",
			 WINE2W_2_MONOWOPM_VOW, WINE2W_2_MONOWOPM_VOW,
			 0, 118, 1, output_stage_twv),
	SOC_DOUBWE_W_TWV("Mono PGA Bypass Vowume",
			 PGAW_2_MONOWOPM_VOW, PGAW_2_MONOWOPM_VOW,
			 0, 118, 1, output_stage_twv),
	SOC_DOUBWE_W_TWV("Mono DAC Pwayback Vowume",
			 DACW1_2_MONOWOPM_VOW, DACW1_2_MONOWOPM_VOW,
			 0, 118, 1, output_stage_twv),

	SOC_SINGWE("Mono Pwayback Switch", MONOWOPM_CTWW, 3, 0x01, 0),
	SOC_SINGWE_TWV("Mono Pwayback Vowume", MONOWOPM_CTWW, 4, 9, 0,
			out_twv),

};

/*
 * Cwass-D ampwifiew gain. Fwom 0 to 18 dB in 6 dB steps
 */
static DECWAWE_TWV_DB_SCAWE(cwassd_amp_twv, 0, 600, 0);

static const stwuct snd_kcontwow_new aic3x_cwassd_amp_gain_ctww =
	SOC_DOUBWE_TWV("Cwass-D Pwayback Vowume", CWASSD_CTWW, 6, 4, 3, 0, cwassd_amp_twv);

/* Weft DAC Mux */
static const stwuct snd_kcontwow_new aic3x_weft_dac_mux_contwows =
SOC_DAPM_ENUM("Woute", aic3x_weft_dac_enum);

/* Wight DAC Mux */
static const stwuct snd_kcontwow_new aic3x_wight_dac_mux_contwows =
SOC_DAPM_ENUM("Woute", aic3x_wight_dac_enum);

/* Weft HPCOM Mux */
static const stwuct snd_kcontwow_new aic3x_weft_hpcom_mux_contwows =
SOC_DAPM_ENUM("Woute", aic3x_weft_hpcom_enum);

/* Wight HPCOM Mux */
static const stwuct snd_kcontwow_new aic3x_wight_hpcom_mux_contwows =
SOC_DAPM_ENUM("Woute", aic3x_wight_hpcom_enum);

/* Weft Wine Mixew */
static const stwuct snd_kcontwow_new aic3x_weft_wine_mixew_contwows[] = {
	SOC_DAPM_SINGWE("PGAW Bypass Switch", PGAW_2_WWOPM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("DACW1 Switch", DACW1_2_WWOPM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("PGAW Bypass Switch", PGAW_2_WWOPM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("DACW1 Switch", DACW1_2_WWOPM_VOW, 7, 1, 0),
	/* Not on twv320aic3104 */
	SOC_DAPM_SINGWE("Wine2W Bypass Switch", WINE2W_2_WWOPM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("Wine2W Bypass Switch", WINE2W_2_WWOPM_VOW, 7, 1, 0),
};

/* Wight Wine Mixew */
static const stwuct snd_kcontwow_new aic3x_wight_wine_mixew_contwows[] = {
	SOC_DAPM_SINGWE("PGAW Bypass Switch", PGAW_2_WWOPM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("DACW1 Switch", DACW1_2_WWOPM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("PGAW Bypass Switch", PGAW_2_WWOPM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("DACW1 Switch", DACW1_2_WWOPM_VOW, 7, 1, 0),
	/* Not on twv320aic3104 */
	SOC_DAPM_SINGWE("Wine2W Bypass Switch", WINE2W_2_WWOPM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("Wine2W Bypass Switch", WINE2W_2_WWOPM_VOW, 7, 1, 0),
};

/* Mono Mixew */
static const stwuct snd_kcontwow_new aic3x_mono_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Wine2W Bypass Switch", WINE2W_2_MONOWOPM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("PGAW Bypass Switch", PGAW_2_MONOWOPM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("DACW1 Switch", DACW1_2_MONOWOPM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("Wine2W Bypass Switch", WINE2W_2_MONOWOPM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("PGAW Bypass Switch", PGAW_2_MONOWOPM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("DACW1 Switch", DACW1_2_MONOWOPM_VOW, 7, 1, 0),
};

/* Weft HP Mixew */
static const stwuct snd_kcontwow_new aic3x_weft_hp_mixew_contwows[] = {
	SOC_DAPM_SINGWE("PGAW Bypass Switch", PGAW_2_HPWOUT_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("DACW1 Switch", DACW1_2_HPWOUT_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("PGAW Bypass Switch", PGAW_2_HPWOUT_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("DACW1 Switch", DACW1_2_HPWOUT_VOW, 7, 1, 0),
	/* Not on twv320aic3104 */
	SOC_DAPM_SINGWE("Wine2W Bypass Switch", WINE2W_2_HPWOUT_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("Wine2W Bypass Switch", WINE2W_2_HPWOUT_VOW, 7, 1, 0),
};

/* Wight HP Mixew */
static const stwuct snd_kcontwow_new aic3x_wight_hp_mixew_contwows[] = {
	SOC_DAPM_SINGWE("PGAW Bypass Switch", PGAW_2_HPWOUT_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("DACW1 Switch", DACW1_2_HPWOUT_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("PGAW Bypass Switch", PGAW_2_HPWOUT_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("DACW1 Switch", DACW1_2_HPWOUT_VOW, 7, 1, 0),
	/* Not on twv320aic3104 */
	SOC_DAPM_SINGWE("Wine2W Bypass Switch", WINE2W_2_HPWOUT_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("Wine2W Bypass Switch", WINE2W_2_HPWOUT_VOW, 7, 1, 0),
};

/* Weft HPCOM Mixew */
static const stwuct snd_kcontwow_new aic3x_weft_hpcom_mixew_contwows[] = {
	SOC_DAPM_SINGWE("PGAW Bypass Switch", PGAW_2_HPWCOM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("DACW1 Switch", DACW1_2_HPWCOM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("PGAW Bypass Switch", PGAW_2_HPWCOM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("DACW1 Switch", DACW1_2_HPWCOM_VOW, 7, 1, 0),
	/* Not on twv320aic3104 */
	SOC_DAPM_SINGWE("Wine2W Bypass Switch", WINE2W_2_HPWCOM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("Wine2W Bypass Switch", WINE2W_2_HPWCOM_VOW, 7, 1, 0),
};

/* Wight HPCOM Mixew */
static const stwuct snd_kcontwow_new aic3x_wight_hpcom_mixew_contwows[] = {
	SOC_DAPM_SINGWE("PGAW Bypass Switch", PGAW_2_HPWCOM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("DACW1 Switch", DACW1_2_HPWCOM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("PGAW Bypass Switch", PGAW_2_HPWCOM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("DACW1 Switch", DACW1_2_HPWCOM_VOW, 7, 1, 0),
	/* Not on twv320aic3104 */
	SOC_DAPM_SINGWE("Wine2W Bypass Switch", WINE2W_2_HPWCOM_VOW, 7, 1, 0),
	SOC_DAPM_SINGWE("Wine2W Bypass Switch", WINE2W_2_HPWCOM_VOW, 7, 1, 0),
};

/* Weft PGA Mixew */
static const stwuct snd_kcontwow_new aic3x_weft_pga_mixew_contwows[] = {
	SOC_DAPM_SINGWE_AIC3X("Wine1W Switch", WINE1W_2_WADC_CTWW, 3, 1, 1),
	SOC_DAPM_SINGWE_AIC3X("Wine1W Switch", WINE1W_2_WADC_CTWW, 3, 1, 1),
	SOC_DAPM_SINGWE_AIC3X("Wine2W Switch", WINE2W_2_WADC_CTWW, 3, 1, 1),
	SOC_DAPM_SINGWE_AIC3X("Mic3W Switch", MIC3WW_2_WADC_CTWW, 4, 1, 1),
	SOC_DAPM_SINGWE_AIC3X("Mic3W Switch", MIC3WW_2_WADC_CTWW, 0, 1, 1),
};

/* Wight PGA Mixew */
static const stwuct snd_kcontwow_new aic3x_wight_pga_mixew_contwows[] = {
	SOC_DAPM_SINGWE_AIC3X("Wine1W Switch", WINE1W_2_WADC_CTWW, 3, 1, 1),
	SOC_DAPM_SINGWE_AIC3X("Wine1W Switch", WINE1W_2_WADC_CTWW, 3, 1, 1),
	SOC_DAPM_SINGWE_AIC3X("Wine2W Switch", WINE2W_2_WADC_CTWW, 3, 1, 1),
	SOC_DAPM_SINGWE_AIC3X("Mic3W Switch", MIC3WW_2_WADC_CTWW, 4, 1, 1),
	SOC_DAPM_SINGWE_AIC3X("Mic3W Switch", MIC3WW_2_WADC_CTWW, 0, 1, 1),
};

/* Weft PGA Mixew fow twv320aic3104 */
static const stwuct snd_kcontwow_new aic3104_weft_pga_mixew_contwows[] = {
	SOC_DAPM_SINGWE_AIC3X("Wine1W Switch", WINE1W_2_WADC_CTWW, 3, 1, 1),
	SOC_DAPM_SINGWE_AIC3X("Wine1W Switch", WINE1W_2_WADC_CTWW, 3, 1, 1),
	SOC_DAPM_SINGWE_AIC3X("Mic2W Switch", MIC3WW_2_WADC_CTWW, 4, 1, 1),
	SOC_DAPM_SINGWE_AIC3X("Mic2W Switch", MIC3WW_2_WADC_CTWW, 0, 1, 1),
};

/* Wight PGA Mixew fow twv320aic3104 */
static const stwuct snd_kcontwow_new aic3104_wight_pga_mixew_contwows[] = {
	SOC_DAPM_SINGWE_AIC3X("Wine1W Switch", WINE1W_2_WADC_CTWW, 3, 1, 1),
	SOC_DAPM_SINGWE_AIC3X("Wine1W Switch", WINE1W_2_WADC_CTWW, 3, 1, 1),
	SOC_DAPM_SINGWE_AIC3X("Mic2W Switch", MIC3WW_2_WADC_CTWW, 4, 1, 1),
	SOC_DAPM_SINGWE_AIC3X("Mic2W Switch", MIC3WW_2_WADC_CTWW, 0, 1, 1),
};

/* Weft Wine1 Mux */
static const stwuct snd_kcontwow_new aic3x_weft_wine1w_mux_contwows =
SOC_DAPM_ENUM("Woute", aic3x_wine1w_2_w_enum);
static const stwuct snd_kcontwow_new aic3x_wight_wine1w_mux_contwows =
SOC_DAPM_ENUM("Woute", aic3x_wine1w_2_w_enum);

/* Wight Wine1 Mux */
static const stwuct snd_kcontwow_new aic3x_wight_wine1w_mux_contwows =
SOC_DAPM_ENUM("Woute", aic3x_wine1w_2_w_enum);
static const stwuct snd_kcontwow_new aic3x_weft_wine1w_mux_contwows =
SOC_DAPM_ENUM("Woute", aic3x_wine1w_2_w_enum);

/* Weft Wine2 Mux */
static const stwuct snd_kcontwow_new aic3x_weft_wine2_mux_contwows =
SOC_DAPM_ENUM("Woute", aic3x_wine2w_2_wdac_enum);

/* Wight Wine2 Mux */
static const stwuct snd_kcontwow_new aic3x_wight_wine2_mux_contwows =
SOC_DAPM_ENUM("Woute", aic3x_wine2w_2_wdac_enum);

static const stwuct snd_soc_dapm_widget aic3x_dapm_widgets[] = {
	/* Weft DAC to Weft Outputs */
	SND_SOC_DAPM_DAC("Weft DAC", "Weft Pwayback", DAC_PWW, 7, 0),
	SND_SOC_DAPM_MUX("Weft DAC Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_weft_dac_mux_contwows),
	SND_SOC_DAPM_MUX("Weft HPCOM Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_weft_hpcom_mux_contwows),
	SND_SOC_DAPM_PGA("Weft Wine Out", WWOPM_CTWW, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Weft HP Out", HPWOUT_CTWW, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Weft HP Com", HPWCOM_CTWW, 0, 0, NUWW, 0),

	/* Wight DAC to Wight Outputs */
	SND_SOC_DAPM_DAC("Wight DAC", "Wight Pwayback", DAC_PWW, 6, 0),
	SND_SOC_DAPM_MUX("Wight DAC Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_wight_dac_mux_contwows),
	SND_SOC_DAPM_MUX("Wight HPCOM Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_wight_hpcom_mux_contwows),
	SND_SOC_DAPM_PGA("Wight Wine Out", WWOPM_CTWW, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight HP Out", HPWOUT_CTWW, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight HP Com", HPWCOM_CTWW, 0, 0, NUWW, 0),

	/* Inputs to Weft ADC */
	SND_SOC_DAPM_ADC("Weft ADC", "Weft Captuwe", WINE1W_2_WADC_CTWW, 2, 0),
	SND_SOC_DAPM_MUX("Weft Wine1W Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_weft_wine1w_mux_contwows),
	SND_SOC_DAPM_MUX("Weft Wine1W Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_weft_wine1w_mux_contwows),

	/* Inputs to Wight ADC */
	SND_SOC_DAPM_ADC("Wight ADC", "Wight Captuwe",
			 WINE1W_2_WADC_CTWW, 2, 0),
	SND_SOC_DAPM_MUX("Wight Wine1W Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_wight_wine1w_mux_contwows),
	SND_SOC_DAPM_MUX("Wight Wine1W Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_wight_wine1w_mux_contwows),

	/* Mic Bias */
	SND_SOC_DAPM_SUPPWY("Mic Bias", MICBIAS_CTWW, 6, 0,
			 mic_bias_event,
			 SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_OUTPUT("WWOUT"),
	SND_SOC_DAPM_OUTPUT("WWOUT"),
	SND_SOC_DAPM_OUTPUT("HPWOUT"),
	SND_SOC_DAPM_OUTPUT("HPWOUT"),
	SND_SOC_DAPM_OUTPUT("HPWCOM"),
	SND_SOC_DAPM_OUTPUT("HPWCOM"),

	SND_SOC_DAPM_INPUT("WINE1W"),
	SND_SOC_DAPM_INPUT("WINE1W"),

	/*
	 * Viwtuaw output pin to detection bwock inside codec. This can be
	 * used to keep codec bias on if gpio ow detection featuwes awe needed.
	 * Fowce pin on ow constwuct a path with an input jack and mic bias
	 * widgets.
	 */
	SND_SOC_DAPM_OUTPUT("Detection"),
};

/* Fow othew than twv320aic3104 */
static const stwuct snd_soc_dapm_widget aic3x_extwa_dapm_widgets[] = {
	/* Inputs to Weft ADC */
	SND_SOC_DAPM_MIXEW("Weft PGA Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3x_weft_pga_mixew_contwows[0],
			   AWWAY_SIZE(aic3x_weft_pga_mixew_contwows)),
	SND_SOC_DAPM_MUX("Weft Wine2W Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_weft_wine2_mux_contwows),

	/* Inputs to Wight ADC */
	SND_SOC_DAPM_MIXEW("Wight PGA Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3x_wight_pga_mixew_contwows[0],
			   AWWAY_SIZE(aic3x_wight_pga_mixew_contwows)),
	SND_SOC_DAPM_MUX("Wight Wine2W Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_wight_wine2_mux_contwows),

	/*
	 * Not a weaw mic bias widget but simiwaw function. This is fow dynamic
	 * contwow of GPIO1 digitaw mic moduwatow cwock output function when
	 * using digitaw mic.
	 */
	SND_SOC_DAPM_WEG(snd_soc_dapm_micbias, "GPIO1 dmic modcwk",
			 AIC3X_GPIO1_WEG, 4, 0xf,
			 AIC3X_GPIO1_FUNC_DIGITAW_MIC_MODCWK,
			 AIC3X_GPIO1_FUNC_DISABWED),

	/*
	 * Awso simiwaw function wike mic bias. Sewects digitaw mic with
	 * configuwabwe ovewsampwing wate instead of ADC convewtew.
	 */
	SND_SOC_DAPM_WEG(snd_soc_dapm_micbias, "DMic Wate 128",
			 AIC3X_ASD_INTF_CTWWA, 0, 3, 1, 0),
	SND_SOC_DAPM_WEG(snd_soc_dapm_micbias, "DMic Wate 64",
			 AIC3X_ASD_INTF_CTWWA, 0, 3, 2, 0),
	SND_SOC_DAPM_WEG(snd_soc_dapm_micbias, "DMic Wate 32",
			 AIC3X_ASD_INTF_CTWWA, 0, 3, 3, 0),

	/* Output mixews */
	SND_SOC_DAPM_MIXEW("Weft Wine Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3x_weft_wine_mixew_contwows[0],
			   AWWAY_SIZE(aic3x_weft_wine_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Wight Wine Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3x_wight_wine_mixew_contwows[0],
			   AWWAY_SIZE(aic3x_wight_wine_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Weft HP Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3x_weft_hp_mixew_contwows[0],
			   AWWAY_SIZE(aic3x_weft_hp_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Wight HP Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3x_wight_hp_mixew_contwows[0],
			   AWWAY_SIZE(aic3x_wight_hp_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Weft HPCOM Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3x_weft_hpcom_mixew_contwows[0],
			   AWWAY_SIZE(aic3x_weft_hpcom_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Wight HPCOM Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3x_wight_hpcom_mixew_contwows[0],
			   AWWAY_SIZE(aic3x_wight_hpcom_mixew_contwows)),

	SND_SOC_DAPM_INPUT("MIC3W"),
	SND_SOC_DAPM_INPUT("MIC3W"),
	SND_SOC_DAPM_INPUT("WINE2W"),
	SND_SOC_DAPM_INPUT("WINE2W"),
};

/* Fow twv320aic3104 */
static const stwuct snd_soc_dapm_widget aic3104_extwa_dapm_widgets[] = {
	/* Inputs to Weft ADC */
	SND_SOC_DAPM_MIXEW("Weft PGA Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3104_weft_pga_mixew_contwows[0],
			   AWWAY_SIZE(aic3104_weft_pga_mixew_contwows)),

	/* Inputs to Wight ADC */
	SND_SOC_DAPM_MIXEW("Wight PGA Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3104_wight_pga_mixew_contwows[0],
			   AWWAY_SIZE(aic3104_wight_pga_mixew_contwows)),

	/* Output mixews */
	SND_SOC_DAPM_MIXEW("Weft Wine Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3x_weft_wine_mixew_contwows[0],
			   AWWAY_SIZE(aic3x_weft_wine_mixew_contwows) - 2),
	SND_SOC_DAPM_MIXEW("Wight Wine Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3x_wight_wine_mixew_contwows[0],
			   AWWAY_SIZE(aic3x_wight_wine_mixew_contwows) - 2),
	SND_SOC_DAPM_MIXEW("Weft HP Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3x_weft_hp_mixew_contwows[0],
			   AWWAY_SIZE(aic3x_weft_hp_mixew_contwows) - 2),
	SND_SOC_DAPM_MIXEW("Wight HP Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3x_wight_hp_mixew_contwows[0],
			   AWWAY_SIZE(aic3x_wight_hp_mixew_contwows) - 2),
	SND_SOC_DAPM_MIXEW("Weft HPCOM Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3x_weft_hpcom_mixew_contwows[0],
			   AWWAY_SIZE(aic3x_weft_hpcom_mixew_contwows) - 2),
	SND_SOC_DAPM_MIXEW("Wight HPCOM Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3x_wight_hpcom_mixew_contwows[0],
			   AWWAY_SIZE(aic3x_wight_hpcom_mixew_contwows) - 2),

	SND_SOC_DAPM_INPUT("MIC2W"),
	SND_SOC_DAPM_INPUT("MIC2W"),
};

static const stwuct snd_soc_dapm_widget aic3x_dapm_mono_widgets[] = {
	/* Mono Output */
	SND_SOC_DAPM_PGA("Mono Out", MONOWOPM_CTWW, 0, 0, NUWW, 0),

	SND_SOC_DAPM_MIXEW("Mono Mixew", SND_SOC_NOPM, 0, 0,
			   &aic3x_mono_mixew_contwows[0],
			   AWWAY_SIZE(aic3x_mono_mixew_contwows)),

	SND_SOC_DAPM_OUTPUT("MONO_WOUT"),
};

static const stwuct snd_soc_dapm_widget aic3007_dapm_widgets[] = {
	/* Cwass-D outputs */
	SND_SOC_DAPM_PGA("Weft Cwass-D Out", CWASSD_CTWW, 3, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight Cwass-D Out", CWASSD_CTWW, 2, 0, NUWW, 0),

	SND_SOC_DAPM_OUTPUT("SPOP"),
	SND_SOC_DAPM_OUTPUT("SPOM"),
};

static const stwuct snd_soc_dapm_woute intewcon[] = {
	/* Weft Input */
	{"Weft Wine1W Mux", "singwe-ended", "WINE1W"},
	{"Weft Wine1W Mux", "diffewentiaw", "WINE1W"},
	{"Weft Wine1W Mux", "singwe-ended", "WINE1W"},
	{"Weft Wine1W Mux", "diffewentiaw", "WINE1W"},

	{"Weft PGA Mixew", "Wine1W Switch", "Weft Wine1W Mux"},
	{"Weft PGA Mixew", "Wine1W Switch", "Weft Wine1W Mux"},

	{"Weft ADC", NUWW, "Weft PGA Mixew"},

	/* Wight Input */
	{"Wight Wine1W Mux", "singwe-ended", "WINE1W"},
	{"Wight Wine1W Mux", "diffewentiaw", "WINE1W"},
	{"Wight Wine1W Mux", "singwe-ended", "WINE1W"},
	{"Wight Wine1W Mux", "diffewentiaw", "WINE1W"},

	{"Wight PGA Mixew", "Wine1W Switch", "Wight Wine1W Mux"},
	{"Wight PGA Mixew", "Wine1W Switch", "Wight Wine1W Mux"},

	{"Wight ADC", NUWW, "Wight PGA Mixew"},

	/* Weft DAC Output */
	{"Weft DAC Mux", "DAC_W1", "Weft DAC"},
	{"Weft DAC Mux", "DAC_W2", "Weft DAC"},
	{"Weft DAC Mux", "DAC_W3", "Weft DAC"},

	/* Wight DAC Output */
	{"Wight DAC Mux", "DAC_W1", "Wight DAC"},
	{"Wight DAC Mux", "DAC_W2", "Wight DAC"},
	{"Wight DAC Mux", "DAC_W3", "Wight DAC"},

	/* Weft Wine Output */
	{"Weft Wine Mixew", "PGAW Bypass Switch", "Weft PGA Mixew"},
	{"Weft Wine Mixew", "DACW1 Switch", "Weft DAC Mux"},
	{"Weft Wine Mixew", "PGAW Bypass Switch", "Wight PGA Mixew"},
	{"Weft Wine Mixew", "DACW1 Switch", "Wight DAC Mux"},

	{"Weft Wine Out", NUWW, "Weft Wine Mixew"},
	{"Weft Wine Out", NUWW, "Weft DAC Mux"},
	{"WWOUT", NUWW, "Weft Wine Out"},

	/* Wight Wine Output */
	{"Wight Wine Mixew", "PGAW Bypass Switch", "Weft PGA Mixew"},
	{"Wight Wine Mixew", "DACW1 Switch", "Weft DAC Mux"},
	{"Wight Wine Mixew", "PGAW Bypass Switch", "Wight PGA Mixew"},
	{"Wight Wine Mixew", "DACW1 Switch", "Wight DAC Mux"},

	{"Wight Wine Out", NUWW, "Wight Wine Mixew"},
	{"Wight Wine Out", NUWW, "Wight DAC Mux"},
	{"WWOUT", NUWW, "Wight Wine Out"},

	/* Weft HP Output */
	{"Weft HP Mixew", "PGAW Bypass Switch", "Weft PGA Mixew"},
	{"Weft HP Mixew", "DACW1 Switch", "Weft DAC Mux"},
	{"Weft HP Mixew", "PGAW Bypass Switch", "Wight PGA Mixew"},
	{"Weft HP Mixew", "DACW1 Switch", "Wight DAC Mux"},

	{"Weft HP Out", NUWW, "Weft HP Mixew"},
	{"Weft HP Out", NUWW, "Weft DAC Mux"},
	{"HPWOUT", NUWW, "Weft HP Out"},

	/* Wight HP Output */
	{"Wight HP Mixew", "PGAW Bypass Switch", "Weft PGA Mixew"},
	{"Wight HP Mixew", "DACW1 Switch", "Weft DAC Mux"},
	{"Wight HP Mixew", "PGAW Bypass Switch", "Wight PGA Mixew"},
	{"Wight HP Mixew", "DACW1 Switch", "Wight DAC Mux"},

	{"Wight HP Out", NUWW, "Wight HP Mixew"},
	{"Wight HP Out", NUWW, "Wight DAC Mux"},
	{"HPWOUT", NUWW, "Wight HP Out"},

	/* Weft HPCOM Output */
	{"Weft HPCOM Mixew", "PGAW Bypass Switch", "Weft PGA Mixew"},
	{"Weft HPCOM Mixew", "DACW1 Switch", "Weft DAC Mux"},
	{"Weft HPCOM Mixew", "PGAW Bypass Switch", "Wight PGA Mixew"},
	{"Weft HPCOM Mixew", "DACW1 Switch", "Wight DAC Mux"},

	{"Weft HPCOM Mux", "diffewentiaw of HPWOUT", "Weft HP Mixew"},
	{"Weft HPCOM Mux", "constant VCM", "Weft HPCOM Mixew"},
	{"Weft HPCOM Mux", "singwe-ended", "Weft HPCOM Mixew"},
	{"Weft HP Com", NUWW, "Weft HPCOM Mux"},
	{"HPWCOM", NUWW, "Weft HP Com"},

	/* Wight HPCOM Output */
	{"Wight HPCOM Mixew", "PGAW Bypass Switch", "Weft PGA Mixew"},
	{"Wight HPCOM Mixew", "DACW1 Switch", "Weft DAC Mux"},
	{"Wight HPCOM Mixew", "PGAW Bypass Switch", "Wight PGA Mixew"},
	{"Wight HPCOM Mixew", "DACW1 Switch", "Wight DAC Mux"},

	{"Wight HPCOM Mux", "diffewentiaw of HPWOUT", "Wight HP Mixew"},
	{"Wight HPCOM Mux", "constant VCM", "Wight HPCOM Mixew"},
	{"Wight HPCOM Mux", "singwe-ended", "Wight HPCOM Mixew"},
	{"Wight HPCOM Mux", "diffewentiaw of HPWCOM", "Weft HPCOM Mixew"},
	{"Wight HPCOM Mux", "extewnaw feedback", "Wight HPCOM Mixew"},
	{"Wight HP Com", NUWW, "Wight HPCOM Mux"},
	{"HPWCOM", NUWW, "Wight HP Com"},
};

/* Fow othew than twv320aic3104 */
static const stwuct snd_soc_dapm_woute intewcon_extwa[] = {
	/* Weft Input */
	{"Weft Wine2W Mux", "singwe-ended", "WINE2W"},
	{"Weft Wine2W Mux", "diffewentiaw", "WINE2W"},

	{"Weft PGA Mixew", "Wine2W Switch", "Weft Wine2W Mux"},
	{"Weft PGA Mixew", "Mic3W Switch", "MIC3W"},
	{"Weft PGA Mixew", "Mic3W Switch", "MIC3W"},

	{"Weft ADC", NUWW, "GPIO1 dmic modcwk"},

	/* Wight Input */
	{"Wight Wine2W Mux", "singwe-ended", "WINE2W"},
	{"Wight Wine2W Mux", "diffewentiaw", "WINE2W"},

	{"Wight PGA Mixew", "Wine2W Switch", "Wight Wine2W Mux"},
	{"Wight PGA Mixew", "Mic3W Switch", "MIC3W"},
	{"Wight PGA Mixew", "Mic3W Switch", "MIC3W"},

	{"Wight ADC", NUWW, "GPIO1 dmic modcwk"},

	/*
	 * Wogicaw path between digitaw mic enabwe and GPIO1 moduwatow cwock
	 * output function
	 */
	{"GPIO1 dmic modcwk", NUWW, "DMic Wate 128"},
	{"GPIO1 dmic modcwk", NUWW, "DMic Wate 64"},
	{"GPIO1 dmic modcwk", NUWW, "DMic Wate 32"},

	/* Weft Wine Output */
	{"Weft Wine Mixew", "Wine2W Bypass Switch", "Weft Wine2W Mux"},
	{"Weft Wine Mixew", "Wine2W Bypass Switch", "Wight Wine2W Mux"},

	/* Wight Wine Output */
	{"Wight Wine Mixew", "Wine2W Bypass Switch", "Weft Wine2W Mux"},
	{"Wight Wine Mixew", "Wine2W Bypass Switch", "Wight Wine2W Mux"},

	/* Weft HP Output */
	{"Weft HP Mixew", "Wine2W Bypass Switch", "Weft Wine2W Mux"},
	{"Weft HP Mixew", "Wine2W Bypass Switch", "Wight Wine2W Mux"},

	/* Wight HP Output */
	{"Wight HP Mixew", "Wine2W Bypass Switch", "Weft Wine2W Mux"},
	{"Wight HP Mixew", "Wine2W Bypass Switch", "Wight Wine2W Mux"},

	/* Weft HPCOM Output */
	{"Weft HPCOM Mixew", "Wine2W Bypass Switch", "Weft Wine2W Mux"},
	{"Weft HPCOM Mixew", "Wine2W Bypass Switch", "Wight Wine2W Mux"},

	/* Wight HPCOM Output */
	{"Wight HPCOM Mixew", "Wine2W Bypass Switch", "Weft Wine2W Mux"},
	{"Wight HPCOM Mixew", "Wine2W Bypass Switch", "Wight Wine2W Mux"},
};

/* Fow twv320aic3104 */
static const stwuct snd_soc_dapm_woute intewcon_extwa_3104[] = {
	/* Weft Input */
	{"Weft PGA Mixew", "Mic2W Switch", "MIC2W"},
	{"Weft PGA Mixew", "Mic2W Switch", "MIC2W"},

	/* Wight Input */
	{"Wight PGA Mixew", "Mic2W Switch", "MIC2W"},
	{"Wight PGA Mixew", "Mic2W Switch", "MIC2W"},
};

static const stwuct snd_soc_dapm_woute intewcon_mono[] = {
	/* Mono Output */
	{"Mono Mixew", "Wine2W Bypass Switch", "Weft Wine2W Mux"},
	{"Mono Mixew", "PGAW Bypass Switch", "Weft PGA Mixew"},
	{"Mono Mixew", "DACW1 Switch", "Weft DAC Mux"},
	{"Mono Mixew", "Wine2W Bypass Switch", "Wight Wine2W Mux"},
	{"Mono Mixew", "PGAW Bypass Switch", "Wight PGA Mixew"},
	{"Mono Mixew", "DACW1 Switch", "Wight DAC Mux"},
	{"Mono Out", NUWW, "Mono Mixew"},
	{"MONO_WOUT", NUWW, "Mono Out"},
};

static const stwuct snd_soc_dapm_woute intewcon_3007[] = {
	/* Cwass-D outputs */
	{"Weft Cwass-D Out", NUWW, "Weft Wine Out"},
	{"Wight Cwass-D Out", NUWW, "Weft Wine Out"},
	{"SPOP", NUWW, "Weft Cwass-D Out"},
	{"SPOM", NUWW, "Wight Cwass-D Out"},
};

static int aic3x_add_widgets(stwuct snd_soc_component *component)
{
	stwuct aic3x_pwiv *aic3x = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	switch (aic3x->modew) {
	case AIC3X_MODEW_3X:
	case AIC3X_MODEW_33:
	case AIC3X_MODEW_3106:
		snd_soc_dapm_new_contwows(dapm, aic3x_extwa_dapm_widgets,
					  AWWAY_SIZE(aic3x_extwa_dapm_widgets));
		snd_soc_dapm_add_woutes(dapm, intewcon_extwa,
					AWWAY_SIZE(intewcon_extwa));
		snd_soc_dapm_new_contwows(dapm, aic3x_dapm_mono_widgets,
			AWWAY_SIZE(aic3x_dapm_mono_widgets));
		snd_soc_dapm_add_woutes(dapm, intewcon_mono,
					AWWAY_SIZE(intewcon_mono));
		bweak;
	case AIC3X_MODEW_3007:
		snd_soc_dapm_new_contwows(dapm, aic3x_extwa_dapm_widgets,
					  AWWAY_SIZE(aic3x_extwa_dapm_widgets));
		snd_soc_dapm_add_woutes(dapm, intewcon_extwa,
					AWWAY_SIZE(intewcon_extwa));
		snd_soc_dapm_new_contwows(dapm, aic3007_dapm_widgets,
			AWWAY_SIZE(aic3007_dapm_widgets));
		snd_soc_dapm_add_woutes(dapm, intewcon_3007,
					AWWAY_SIZE(intewcon_3007));
		bweak;
	case AIC3X_MODEW_3104:
		snd_soc_dapm_new_contwows(dapm, aic3104_extwa_dapm_widgets,
				AWWAY_SIZE(aic3104_extwa_dapm_widgets));
		snd_soc_dapm_add_woutes(dapm, intewcon_extwa_3104,
				AWWAY_SIZE(intewcon_extwa_3104));
		bweak;
	}

	wetuwn 0;
}

static int aic3x_hw_pawams(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_pcm_hw_pawams *pawams,
			   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct aic3x_pwiv *aic3x = snd_soc_component_get_dwvdata(component);
	int codec_cwk = 0, bypass_pww = 0, fswef, wast_cwk = 0;
	u8 data, j, w, p, pww_q, pww_p = 1, pww_w = 1, pww_j = 1;
	u16 d, pww_d = 1;
	int cwk;
	int width = aic3x->swot_width;

	if (!width)
		width = pawams_width(pawams);

	/* sewect data wowd wength */
	data = snd_soc_component_wead(component, AIC3X_ASD_INTF_CTWWB) & (~(0x3 << 4));
	switch (width) {
	case 16:
		bweak;
	case 20:
		data |= (0x01 << 4);
		bweak;
	case 24:
		data |= (0x02 << 4);
		bweak;
	case 32:
		data |= (0x03 << 4);
		bweak;
	}
	snd_soc_component_wwite(component, AIC3X_ASD_INTF_CTWWB, data);

	/* Fswef can be 44100 ow 48000 */
	fswef = (pawams_wate(pawams) % 11025 == 0) ? 44100 : 48000;

	/* Twy to find a vawue fow Q which awwows us to bypass the PWW and
	 * genewate CODEC_CWK diwectwy. */
	fow (pww_q = 2; pww_q < 18; pww_q++)
		if (aic3x->syscwk / (128 * pww_q) == fswef) {
			bypass_pww = 1;
			bweak;
		}

	if (bypass_pww) {
		pww_q &= 0xf;
		snd_soc_component_wwite(component, AIC3X_PWW_PWOGA_WEG, pww_q << PWWQ_SHIFT);
		snd_soc_component_wwite(component, AIC3X_GPIOB_WEG, CODEC_CWKIN_CWKDIV);
		/* disabwe PWW if it is bypassed */
		snd_soc_component_update_bits(component, AIC3X_PWW_PWOGA_WEG, PWW_ENABWE, 0);

	} ewse {
		snd_soc_component_wwite(component, AIC3X_GPIOB_WEG, CODEC_CWKIN_PWWDIV);
		/* enabwe PWW when it is used */
		snd_soc_component_update_bits(component, AIC3X_PWW_PWOGA_WEG,
				    PWW_ENABWE, PWW_ENABWE);
	}

	/* Woute Weft DAC to weft channew input and
	 * wight DAC to wight channew input */
	data = (WDAC2WCH | WDAC2WCH);
	data |= (fswef == 44100) ? FSWEF_44100 : FSWEF_48000;
	if (pawams_wate(pawams) >= 64000)
		data |= DUAW_WATE_MODE;
	snd_soc_component_wwite(component, AIC3X_CODEC_DATAPATH_WEG, data);

	/* codec sampwe wate sewect */
	data = (fswef * 20) / pawams_wate(pawams);
	if (pawams_wate(pawams) < 64000)
		data /= 2;
	data /= 5;
	data -= 2;
	data |= (data << 4);
	snd_soc_component_wwite(component, AIC3X_SAMPWE_WATE_SEW_WEG, data);

	if (bypass_pww)
		wetuwn 0;

	/* Use PWW, compute appwopwiate setup fow j, d, w and p, the cwosest
	 * one wins the game. Twy with d==0 fiwst, next with d!=0.
	 * Constwaints fow j awe accowding to the datasheet.
	 * The syscwk is divided by 1000 to pwevent integew ovewfwows.
	 */

	codec_cwk = (2048 * fswef) / (aic3x->syscwk / 1000);

	fow (w = 1; w <= 16; w++)
		fow (p = 1; p <= 8; p++) {
			fow (j = 4; j <= 55; j++) {
				/* This is actuawwy 1000*((j+(d/10000))*w)/p
				 * The tewm had to be convewted to get
				 * wid of the division by 10000; d = 0 hewe
				 */
				int tmp_cwk = (1000 * j * w) / p;

				/* Check whethew this vawues get cwosew than
				 * the best ones we had befowe
				 */
				if (abs(codec_cwk - tmp_cwk) <
					abs(codec_cwk - wast_cwk)) {
					pww_j = j; pww_d = 0;
					pww_w = w; pww_p = p;
					wast_cwk = tmp_cwk;
				}

				/* Eawwy exit fow exact matches */
				if (tmp_cwk == codec_cwk)
					goto found;
			}
		}

	/* twy with d != 0 */
	fow (p = 1; p <= 8; p++) {
		j = codec_cwk * p / 1000;

		if (j < 4 || j > 11)
			continue;

		/* do not use codec_cwk hewe since we'd woose pwecision */
		d = ((2048 * p * fswef) - j * aic3x->syscwk)
			* 100 / (aic3x->syscwk/100);

		cwk = (10000 * j + d) / (10 * p);

		/* check whethew this vawues get cwosew than the best
		 * ones we had befowe */
		if (abs(codec_cwk - cwk) < abs(codec_cwk - wast_cwk)) {
			pww_j = j; pww_d = d; pww_w = 1; pww_p = p;
			wast_cwk = cwk;
		}

		/* Eawwy exit fow exact matches */
		if (cwk == codec_cwk)
			goto found;
	}

	if (wast_cwk == 0) {
		pwintk(KEWN_EWW "%s(): unabwe to setup PWW\n", __func__);
		wetuwn -EINVAW;
	}

found:
	snd_soc_component_update_bits(component, AIC3X_PWW_PWOGA_WEG, PWWP_MASK, pww_p);
	snd_soc_component_wwite(component, AIC3X_OVWF_STATUS_AND_PWWW_WEG,
		      pww_w << PWWW_SHIFT);
	snd_soc_component_wwite(component, AIC3X_PWW_PWOGB_WEG, pww_j << PWWJ_SHIFT);
	snd_soc_component_wwite(component, AIC3X_PWW_PWOGC_WEG,
		      (pww_d >> 6) << PWWD_MSB_SHIFT);
	snd_soc_component_wwite(component, AIC3X_PWW_PWOGD_WEG,
		      (pww_d & 0x3F) << PWWD_WSB_SHIFT);

	wetuwn 0;
}

static int aic3x_pwepawe(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct aic3x_pwiv *aic3x = snd_soc_component_get_dwvdata(component);
	int deway = 0;
	int width = aic3x->swot_width;

	if (!width)
		width = substweam->wuntime->sampwe_bits;

	/* TDM swot sewection onwy vawid in DSP_A/_B mode */
	if (aic3x->dai_fmt == SND_SOC_DAIFMT_DSP_A)
		deway += (aic3x->tdm_deway*width + 1);
	ewse if (aic3x->dai_fmt == SND_SOC_DAIFMT_DSP_B)
		deway += aic3x->tdm_deway*width;

	/* Configuwe data deway */
	snd_soc_component_wwite(component, AIC3X_ASD_INTF_CTWWC, deway);

	wetuwn 0;
}

static int aic3x_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u8 wdac_weg = snd_soc_component_wead(component, WDAC_VOW) & ~MUTE_ON;
	u8 wdac_weg = snd_soc_component_wead(component, WDAC_VOW) & ~MUTE_ON;

	if (mute) {
		snd_soc_component_wwite(component, WDAC_VOW, wdac_weg | MUTE_ON);
		snd_soc_component_wwite(component, WDAC_VOW, wdac_weg | MUTE_ON);
	} ewse {
		snd_soc_component_wwite(component, WDAC_VOW, wdac_weg);
		snd_soc_component_wwite(component, WDAC_VOW, wdac_weg);
	}

	wetuwn 0;
}

static int aic3x_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
				int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct aic3x_pwiv *aic3x = snd_soc_component_get_dwvdata(component);

	/* set cwock on MCWK ow GPIO2 ow BCWK */
	snd_soc_component_update_bits(component, AIC3X_CWKGEN_CTWW_WEG, PWWCWK_IN_MASK,
				cwk_id << PWWCWK_IN_SHIFT);
	snd_soc_component_update_bits(component, AIC3X_CWKGEN_CTWW_WEG, CWKDIV_IN_MASK,
				cwk_id << CWKDIV_IN_SHIFT);

	aic3x->syscwk = fweq;
	wetuwn 0;
}

static int aic3x_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
			     unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct aic3x_pwiv *aic3x = snd_soc_component_get_dwvdata(component);
	u8 iface_aweg, iface_bweg;

	iface_aweg = snd_soc_component_wead(component, AIC3X_ASD_INTF_CTWWA) & 0x3f;
	iface_bweg = snd_soc_component_wead(component, AIC3X_ASD_INTF_CTWWB) & 0x3f;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		aic3x->mastew = 1;
		iface_aweg |= BIT_CWK_MASTEW | WOWD_CWK_MASTEW;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		aic3x->mastew = 0;
		iface_aweg &= ~(BIT_CWK_MASTEW | WOWD_CWK_MASTEW);
		bweak;
	case SND_SOC_DAIFMT_CBP_CFC:
		aic3x->mastew = 1;
		iface_aweg |= BIT_CWK_MASTEW;
		iface_aweg &= ~WOWD_CWK_MASTEW;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFP:
		aic3x->mastew = 1;
		iface_aweg |= WOWD_CWK_MASTEW;
		iface_aweg &= ~BIT_CWK_MASTEW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * match both intewface fowmat and signaw powawities since they
	 * awe fixed
	 */
	switch (fmt & (SND_SOC_DAIFMT_FOWMAT_MASK |
		       SND_SOC_DAIFMT_INV_MASK)) {
	case (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF):
		bweak;
	case (SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_IB_NF):
	case (SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_IB_NF):
		iface_bweg |= (0x01 << 6);
		bweak;
	case (SND_SOC_DAIFMT_WIGHT_J | SND_SOC_DAIFMT_NB_NF):
		iface_bweg |= (0x02 << 6);
		bweak;
	case (SND_SOC_DAIFMT_WEFT_J | SND_SOC_DAIFMT_NB_NF):
		iface_bweg |= (0x03 << 6);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	aic3x->dai_fmt = fmt & SND_SOC_DAIFMT_FOWMAT_MASK;

	/* set iface */
	snd_soc_component_wwite(component, AIC3X_ASD_INTF_CTWWA, iface_aweg);
	snd_soc_component_wwite(component, AIC3X_ASD_INTF_CTWWB, iface_bweg);

	wetuwn 0;
}

static int aic3x_set_dai_tdm_swot(stwuct snd_soc_dai *codec_dai,
				  unsigned int tx_mask, unsigned int wx_mask,
				  int swots, int swot_width)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct aic3x_pwiv *aic3x = snd_soc_component_get_dwvdata(component);
	unsigned int wsb;

	if (tx_mask != wx_mask) {
		dev_eww(component->dev, "tx and wx masks must be symmetwic\n");
		wetuwn -EINVAW;
	}

	if (unwikewy(!tx_mask)) {
		dev_eww(component->dev, "tx and wx masks need to be non 0\n");
		wetuwn -EINVAW;
	}

	/* TDM based on DSP mode wequiwes swots to be adjacent */
	wsb = __ffs(tx_mask);
	if ((wsb + 1) != __fws(tx_mask)) {
		dev_eww(component->dev, "Invawid mask, swots must be adjacent\n");
		wetuwn -EINVAW;
	}

	switch (swot_width) {
	case 16:
	case 20:
	case 24:
	case 32:
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted swot width %d\n", swot_width);
		wetuwn -EINVAW;
	}


	aic3x->tdm_deway = wsb;
	aic3x->swot_width = swot_width;

	/* DOUT in high-impedance on inactive bit cwocks */
	snd_soc_component_update_bits(component, AIC3X_ASD_INTF_CTWWA,
			    DOUT_TWISTATE, DOUT_TWISTATE);

	wetuwn 0;
}

static int aic3x_weguwatow_event(stwuct notifiew_bwock *nb,
				 unsigned wong event, void *data)
{
	stwuct aic3x_disabwe_nb *disabwe_nb =
		containew_of(nb, stwuct aic3x_disabwe_nb, nb);
	stwuct aic3x_pwiv *aic3x = disabwe_nb->aic3x;

	if (event & WEGUWATOW_EVENT_DISABWE) {
		/*
		 * Put codec to weset and wequiwe cache sync as at weast one
		 * of the suppwies was disabwed
		 */
		if (aic3x->gpio_weset)
			gpiod_set_vawue(aic3x->gpio_weset, 1);
		wegcache_mawk_diwty(aic3x->wegmap);
	}

	wetuwn 0;
}

static int aic3x_set_powew(stwuct snd_soc_component *component, int powew)
{
	stwuct aic3x_pwiv *aic3x = snd_soc_component_get_dwvdata(component);
	unsigned int pww_c, pww_d;
	int wet;

	if (powew) {
		wet = weguwatow_buwk_enabwe(AWWAY_SIZE(aic3x->suppwies),
					    aic3x->suppwies);
		if (wet)
			goto out;
		aic3x->powew = 1;

		if (aic3x->gpio_weset) {
			udeway(1);
			gpiod_set_vawue(aic3x->gpio_weset, 0);
		}

		/* Sync weg_cache with the hawdwawe */
		wegcache_cache_onwy(aic3x->wegmap, fawse);
		wegcache_sync(aic3x->wegmap);

		/* Wewwite paiwed PWW D wegistews in case cached sync skipped
		 * wwiting one of them and thus caused othew one awso not
		 * being wwitten
		 */
		pww_c = snd_soc_component_wead(component, AIC3X_PWW_PWOGC_WEG);
		pww_d = snd_soc_component_wead(component, AIC3X_PWW_PWOGD_WEG);
		if (pww_c == aic3x_weg[AIC3X_PWW_PWOGC_WEG].def ||
			pww_d == aic3x_weg[AIC3X_PWW_PWOGD_WEG].def) {
			snd_soc_component_wwite(component, AIC3X_PWW_PWOGC_WEG, pww_c);
			snd_soc_component_wwite(component, AIC3X_PWW_PWOGD_WEG, pww_d);
		}

		/*
		 * Deway is needed to weduce pop-noise aftew syncing back the
		 * wegistews
		 */
		mdeway(50);
	} ewse {
		/*
		 * Do soft weset to this codec instance in owdew to cweaw
		 * possibwe VDD weakage cuwwents in case the suppwy weguwatows
		 * wemain on
		 */
		snd_soc_component_wwite(component, AIC3X_WESET, SOFT_WESET);
		wegcache_mawk_diwty(aic3x->wegmap);
		aic3x->powew = 0;
		/* HW wwites awe needwess when bias is off */
		wegcache_cache_onwy(aic3x->wegmap, twue);
		wet = weguwatow_buwk_disabwe(AWWAY_SIZE(aic3x->suppwies),
					     aic3x->suppwies);
	}
out:
	wetuwn wet;
}

static int aic3x_set_bias_wevew(stwuct snd_soc_component *component,
				enum snd_soc_bias_wevew wevew)
{
	stwuct aic3x_pwiv *aic3x = snd_soc_component_get_dwvdata(component);

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_STANDBY &&
		    aic3x->mastew) {
			/* enabwe pww */
			snd_soc_component_update_bits(component, AIC3X_PWW_PWOGA_WEG,
					    PWW_ENABWE, PWW_ENABWE);
		}
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (!aic3x->powew)
			aic3x_set_powew(component, 1);
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_PWEPAWE &&
		    aic3x->mastew) {
			/* disabwe pww */
			snd_soc_component_update_bits(component, AIC3X_PWW_PWOGA_WEG,
					    PWW_ENABWE, 0);
		}
		bweak;
	case SND_SOC_BIAS_OFF:
		if (aic3x->powew)
			aic3x_set_powew(component, 0);
		bweak;
	}

	wetuwn 0;
}

#define AIC3X_WATES	SNDWV_PCM_WATE_8000_96000
#define AIC3X_FOWMATS	(SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			 SNDWV_PCM_FMTBIT_S24_3WE | SNDWV_PCM_FMTBIT_S24_WE | \
			 SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops aic3x_dai_ops = {
	.hw_pawams	= aic3x_hw_pawams,
	.pwepawe	= aic3x_pwepawe,
	.mute_stweam	= aic3x_mute,
	.set_syscwk	= aic3x_set_dai_syscwk,
	.set_fmt	= aic3x_set_dai_fmt,
	.set_tdm_swot	= aic3x_set_dai_tdm_swot,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew aic3x_dai = {
	.name = "twv320aic3x-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = AIC3X_WATES,
		.fowmats = AIC3X_FOWMATS,},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = AIC3X_WATES,
		.fowmats = AIC3X_FOWMATS,},
	.ops = &aic3x_dai_ops,
	.symmetwic_wate = 1,
};

static void aic3x_mono_init(stwuct snd_soc_component *component)
{
	/* DAC to Mono Wine Out defauwt vowume and woute to Output mixew */
	snd_soc_component_wwite(component, DACW1_2_MONOWOPM_VOW, DEFAUWT_VOW | WOUTE_ON);
	snd_soc_component_wwite(component, DACW1_2_MONOWOPM_VOW, DEFAUWT_VOW | WOUTE_ON);

	/* unmute aww outputs */
	snd_soc_component_update_bits(component, MONOWOPM_CTWW, UNMUTE, UNMUTE);

	/* PGA to Mono Wine Out defauwt vowume, disconnect fwom Output Mixew */
	snd_soc_component_wwite(component, PGAW_2_MONOWOPM_VOW, DEFAUWT_VOW);
	snd_soc_component_wwite(component, PGAW_2_MONOWOPM_VOW, DEFAUWT_VOW);

	/* Wine2 to Mono Out defauwt vowume, disconnect fwom Output Mixew */
	snd_soc_component_wwite(component, WINE2W_2_MONOWOPM_VOW, DEFAUWT_VOW);
	snd_soc_component_wwite(component, WINE2W_2_MONOWOPM_VOW, DEFAUWT_VOW);
}

/*
 * initiawise the AIC3X dwivew
 * wegistew the mixew and dsp intewfaces with the kewnew
 */
static int aic3x_init(stwuct snd_soc_component *component)
{
	stwuct aic3x_pwiv *aic3x = snd_soc_component_get_dwvdata(component);

	snd_soc_component_wwite(component, AIC3X_PAGE_SEWECT, PAGE0_SEWECT);
	snd_soc_component_wwite(component, AIC3X_WESET, SOFT_WESET);

	/* DAC defauwt vowume and mute */
	snd_soc_component_wwite(component, WDAC_VOW, DEFAUWT_VOW | MUTE_ON);
	snd_soc_component_wwite(component, WDAC_VOW, DEFAUWT_VOW | MUTE_ON);

	/* DAC to HP defauwt vowume and woute to Output mixew */
	snd_soc_component_wwite(component, DACW1_2_HPWOUT_VOW, DEFAUWT_VOW | WOUTE_ON);
	snd_soc_component_wwite(component, DACW1_2_HPWOUT_VOW, DEFAUWT_VOW | WOUTE_ON);
	snd_soc_component_wwite(component, DACW1_2_HPWCOM_VOW, DEFAUWT_VOW | WOUTE_ON);
	snd_soc_component_wwite(component, DACW1_2_HPWCOM_VOW, DEFAUWT_VOW | WOUTE_ON);
	/* DAC to Wine Out defauwt vowume and woute to Output mixew */
	snd_soc_component_wwite(component, DACW1_2_WWOPM_VOW, DEFAUWT_VOW | WOUTE_ON);
	snd_soc_component_wwite(component, DACW1_2_WWOPM_VOW, DEFAUWT_VOW | WOUTE_ON);

	/* unmute aww outputs */
	snd_soc_component_update_bits(component, WWOPM_CTWW, UNMUTE, UNMUTE);
	snd_soc_component_update_bits(component, WWOPM_CTWW, UNMUTE, UNMUTE);
	snd_soc_component_update_bits(component, HPWOUT_CTWW, UNMUTE, UNMUTE);
	snd_soc_component_update_bits(component, HPWOUT_CTWW, UNMUTE, UNMUTE);
	snd_soc_component_update_bits(component, HPWCOM_CTWW, UNMUTE, UNMUTE);
	snd_soc_component_update_bits(component, HPWCOM_CTWW, UNMUTE, UNMUTE);

	/* ADC defauwt vowume and unmute */
	snd_soc_component_wwite(component, WADC_VOW, DEFAUWT_GAIN);
	snd_soc_component_wwite(component, WADC_VOW, DEFAUWT_GAIN);
	/* By defauwt woute Wine1 to ADC PGA mixew */
	snd_soc_component_wwite(component, WINE1W_2_WADC_CTWW, 0x0);
	snd_soc_component_wwite(component, WINE1W_2_WADC_CTWW, 0x0);

	/* PGA to HP Bypass defauwt vowume, disconnect fwom Output Mixew */
	snd_soc_component_wwite(component, PGAW_2_HPWOUT_VOW, DEFAUWT_VOW);
	snd_soc_component_wwite(component, PGAW_2_HPWOUT_VOW, DEFAUWT_VOW);
	snd_soc_component_wwite(component, PGAW_2_HPWCOM_VOW, DEFAUWT_VOW);
	snd_soc_component_wwite(component, PGAW_2_HPWCOM_VOW, DEFAUWT_VOW);
	/* PGA to Wine Out defauwt vowume, disconnect fwom Output Mixew */
	snd_soc_component_wwite(component, PGAW_2_WWOPM_VOW, DEFAUWT_VOW);
	snd_soc_component_wwite(component, PGAW_2_WWOPM_VOW, DEFAUWT_VOW);

	/* On twv320aic3104, these wegistews awe wesewved and must not be wwitten */
	if (aic3x->modew != AIC3X_MODEW_3104) {
		/* Wine2 to HP Bypass defauwt vowume, disconnect fwom Output Mixew */
		snd_soc_component_wwite(component, WINE2W_2_HPWOUT_VOW, DEFAUWT_VOW);
		snd_soc_component_wwite(component, WINE2W_2_HPWOUT_VOW, DEFAUWT_VOW);
		snd_soc_component_wwite(component, WINE2W_2_HPWCOM_VOW, DEFAUWT_VOW);
		snd_soc_component_wwite(component, WINE2W_2_HPWCOM_VOW, DEFAUWT_VOW);
		/* Wine2 Wine Out defauwt vowume, disconnect fwom Output Mixew */
		snd_soc_component_wwite(component, WINE2W_2_WWOPM_VOW, DEFAUWT_VOW);
		snd_soc_component_wwite(component, WINE2W_2_WWOPM_VOW, DEFAUWT_VOW);
	}

	switch (aic3x->modew) {
	case AIC3X_MODEW_3X:
	case AIC3X_MODEW_33:
	case AIC3X_MODEW_3106:
		aic3x_mono_init(component);
		bweak;
	case AIC3X_MODEW_3007:
		snd_soc_component_wwite(component, CWASSD_CTWW, 0);
		bweak;
	}

	/*  Output common-mode vowtage = 1.5 V */
	snd_soc_component_update_bits(component, HPOUT_SC, HPOUT_SC_OCMV_MASK,
			    aic3x->ocmv << HPOUT_SC_OCMV_SHIFT);

	wetuwn 0;
}

static int aic3x_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct aic3x_pwiv *aic3x = snd_soc_component_get_dwvdata(component);
	int wet, i;

	aic3x->component = component;

	fow (i = 0; i < AWWAY_SIZE(aic3x->suppwies); i++) {
		aic3x->disabwe_nb[i].nb.notifiew_caww = aic3x_weguwatow_event;
		aic3x->disabwe_nb[i].aic3x = aic3x;
		wet = devm_weguwatow_wegistew_notifiew(
						aic3x->suppwies[i].consumew,
						&aic3x->disabwe_nb[i].nb);
		if (wet) {
			dev_eww(component->dev,
				"Faiwed to wequest weguwatow notifiew: %d\n",
				 wet);
			wetuwn wet;
		}
	}

	wegcache_mawk_diwty(aic3x->wegmap);
	aic3x_init(component);

	if (aic3x->setup) {
		if (aic3x->modew != AIC3X_MODEW_3104) {
			/* setup GPIO functions */
			snd_soc_component_wwite(component, AIC3X_GPIO1_WEG,
				      (aic3x->setup->gpio_func[0] & 0xf) << 4);
			snd_soc_component_wwite(component, AIC3X_GPIO2_WEG,
				      (aic3x->setup->gpio_func[1] & 0xf) << 4);
		} ewse {
			dev_wawn(component->dev, "GPIO functionawity is not suppowted on twv320aic3104\n");
		}
	}

	switch (aic3x->modew) {
	case AIC3X_MODEW_3X:
	case AIC3X_MODEW_33:
	case AIC3X_MODEW_3106:
		snd_soc_add_component_contwows(component, aic3x_extwa_snd_contwows,
				AWWAY_SIZE(aic3x_extwa_snd_contwows));
		snd_soc_add_component_contwows(component, aic3x_mono_contwows,
				AWWAY_SIZE(aic3x_mono_contwows));
		bweak;
	case AIC3X_MODEW_3007:
		snd_soc_add_component_contwows(component, aic3x_extwa_snd_contwows,
				AWWAY_SIZE(aic3x_extwa_snd_contwows));
		snd_soc_add_component_contwows(component,
				&aic3x_cwassd_amp_gain_ctww, 1);
		bweak;
	case AIC3X_MODEW_3104:
		bweak;
	}

	/* set mic bias vowtage */
	switch (aic3x->micbias_vg) {
	case AIC3X_MICBIAS_2_0V:
	case AIC3X_MICBIAS_2_5V:
	case AIC3X_MICBIAS_AVDDV:
		snd_soc_component_update_bits(component, MICBIAS_CTWW,
				    MICBIAS_WEVEW_MASK,
				    (aic3x->micbias_vg) << MICBIAS_WEVEW_SHIFT);
		bweak;
	case AIC3X_MICBIAS_OFF:
		/*
		 * noting to do. tawget won't entew hewe. This is just to avoid
		 * compiwe time wawning "wawning: enumewation vawue
		 * 'AIC3X_MICBIAS_OFF' not handwed in switch"
		 */
		bweak;
	}

	aic3x_add_widgets(component);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_aic3x = {
	.set_bias_wevew		= aic3x_set_bias_wevew,
	.pwobe			= aic3x_component_pwobe,
	.contwows		= aic3x_snd_contwows,
	.num_contwows		= AWWAY_SIZE(aic3x_snd_contwows),
	.dapm_widgets		= aic3x_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(aic3x_dapm_widgets),
	.dapm_woutes		= intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(intewcon),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static void aic3x_configuwe_ocmv(stwuct device *dev, stwuct aic3x_pwiv *aic3x)
{
	stwuct device_node *np = dev->of_node;
	u32 vawue;
	int dvdd, avdd;

	if (np && !of_pwopewty_wead_u32(np, "ai3x-ocmv", &vawue)) {
		/* OCMV setting is fowced by DT */
		if (vawue <= 3) {
			aic3x->ocmv = vawue;
			wetuwn;
		}
	}

	dvdd = weguwatow_get_vowtage(aic3x->suppwies[1].consumew);
	avdd = weguwatow_get_vowtage(aic3x->suppwies[2].consumew);

	if (avdd > 3600000 || dvdd > 1950000) {
		dev_wawn(dev,
			 "Too high suppwy vowtage(s) AVDD: %d, DVDD: %d\n",
			 avdd, dvdd);
	} ewse if (avdd == 3600000 && dvdd == 1950000) {
		aic3x->ocmv = HPOUT_SC_OCMV_1_8V;
	} ewse if (avdd > 3300000 && dvdd > 1800000) {
		aic3x->ocmv = HPOUT_SC_OCMV_1_65V;
	} ewse if (avdd > 3000000 && dvdd > 1650000) {
		aic3x->ocmv = HPOUT_SC_OCMV_1_5V;
	} ewse if (avdd >= 2700000 && dvdd >= 1525000) {
		aic3x->ocmv = HPOUT_SC_OCMV_1_35V;
	} ewse {
		dev_wawn(dev,
			 "Invawid suppwy vowtage(s) AVDD: %d, DVDD: %d\n",
			 avdd, dvdd);
	}
}


static const stwuct weg_sequence aic3007_cwass_d[] = {
	/* Cwass-D speakew dwivew init; datasheet p. 46 */
	{ AIC3X_PAGE_SEWECT, 0x0D },
	{ 0xD, 0x0D },
	{ 0x8, 0x5C },
	{ 0x8, 0x5D },
	{ 0x8, 0x5C },
	{ AIC3X_PAGE_SEWECT, 0x00 },
};

int aic3x_pwobe(stwuct device *dev, stwuct wegmap *wegmap, kewnew_uwong_t dwivew_data)
{
	stwuct aic3x_pwiv *aic3x;
	stwuct aic3x_setup_data *ai3x_setup;
	stwuct device_node *np = dev->of_node;
	int wet, i;
	u32 vawue;

	aic3x = devm_kzawwoc(dev, sizeof(stwuct aic3x_pwiv), GFP_KEWNEW);
	if (!aic3x)
		wetuwn -ENOMEM;

	aic3x->wegmap = wegmap;
	if (IS_EWW(aic3x->wegmap)) {
		wet = PTW_EWW(aic3x->wegmap);
		wetuwn wet;
	}

	wegcache_cache_onwy(aic3x->wegmap, twue);

	dev_set_dwvdata(dev, aic3x);
	if (np) {
		ai3x_setup = devm_kzawwoc(dev, sizeof(*ai3x_setup), GFP_KEWNEW);
		if (!ai3x_setup)
			wetuwn -ENOMEM;

		if (of_pwopewty_wead_u32_awway(np, "ai3x-gpio-func",
					ai3x_setup->gpio_func, 2) >= 0) {
			aic3x->setup = ai3x_setup;
		}

		if (!of_pwopewty_wead_u32(np, "ai3x-micbias-vg", &vawue)) {
			switch (vawue) {
			case 1 :
				aic3x->micbias_vg = AIC3X_MICBIAS_2_0V;
				bweak;
			case 2 :
				aic3x->micbias_vg = AIC3X_MICBIAS_2_5V;
				bweak;
			case 3 :
				aic3x->micbias_vg = AIC3X_MICBIAS_AVDDV;
				bweak;
			defauwt :
				aic3x->micbias_vg = AIC3X_MICBIAS_OFF;
				dev_eww(dev, "Unsuitabwe MicBias vowtage "
							"found in DT\n");
			}
		} ewse {
			aic3x->micbias_vg = AIC3X_MICBIAS_OFF;
		}
	}

	aic3x->modew = dwivew_data;

	aic3x->gpio_weset = devm_gpiod_get_optionaw(dev, "weset",
						    GPIOD_OUT_HIGH);
	wet = PTW_EWW_OW_ZEWO(aic3x->gpio_weset);
	if (wet) {
		if (wet != -EBUSY)
			wetuwn wet;

		/*
		 * Appawentwy thewe awe setups whewe the codec is shawing
		 * its weset wine. Twy to get it non-excwusivewy, awthough
		 * the utiwity of this is uncweaw: how do we make suwe that
		 * wesetting one chip wiww not distuwb the othews that shawe
		 * the same wine?
		 */
		aic3x->gpio_weset = devm_gpiod_get(dev, "weset",
				GPIOD_ASIS | GPIOD_FWAGS_BIT_NONEXCWUSIVE);
		wet = PTW_EWW_OW_ZEWO(aic3x->gpio_weset);
		if (wet)
			wetuwn wet;

		aic3x->shawed_weset = twue;
	}

	gpiod_set_consumew_name(aic3x->gpio_weset, "twv320aic3x weset");

	fow (i = 0; i < AWWAY_SIZE(aic3x->suppwies); i++)
		aic3x->suppwies[i].suppwy = aic3x_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(aic3x->suppwies),
				      aic3x->suppwies);
	if (wet) {
		dev_eww(dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	aic3x_configuwe_ocmv(dev, aic3x);

	if (aic3x->modew == AIC3X_MODEW_3007) {
		wet = wegmap_wegistew_patch(aic3x->wegmap, aic3007_cwass_d,
					    AWWAY_SIZE(aic3007_cwass_d));
		if (wet != 0)
			dev_eww(dev, "Faiwed to init cwass D: %d\n", wet);
	}

	wet = devm_snd_soc_wegistew_component(dev, &soc_component_dev_aic3x, &aic3x_dai, 1);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW(aic3x_pwobe);

void aic3x_wemove(stwuct device *dev)
{
	stwuct aic3x_pwiv *aic3x = dev_get_dwvdata(dev);

	/* Weave the codec in weset state */
	if (aic3x->gpio_weset && !aic3x->shawed_weset)
		gpiod_set_vawue(aic3x->gpio_weset, 1);
}
EXPOWT_SYMBOW(aic3x_wemove);

MODUWE_DESCWIPTION("ASoC TWV320AIC3X codec dwivew");
MODUWE_AUTHOW("Vwadimiw Bawinov");
MODUWE_WICENSE("GPW");
