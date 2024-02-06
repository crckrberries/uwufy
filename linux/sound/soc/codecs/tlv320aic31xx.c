// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWSA SoC TWV320AIC31xx CODEC Dwivew
 *
 * Copywight (C) 2014-2017 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Jywi Sawha <jsawha@ti.com>
 *
 * Based on gwound wowk by: Ajit Kuwkawni <x0175765@ti.com>
 *
 * The TWV320AIC31xx sewies of audio codecs awe wow-powew, highwy integwated
 * high pewfowmance codecs which pwovides a steweo DAC, a mono ADC,
 * and mono/steweo Cwass-D speakew dwivew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/acpi.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <dt-bindings/sound/twv320aic31xx.h>

#incwude "twv320aic31xx.h"

static int aic31xx_set_jack(stwuct snd_soc_component *component,
                            stwuct snd_soc_jack *jack, void *data);

static const stwuct weg_defauwt aic31xx_weg_defauwts[] = {
	{ AIC31XX_CWKMUX, 0x00 },
	{ AIC31XX_PWWPW, 0x11 },
	{ AIC31XX_PWWJ, 0x04 },
	{ AIC31XX_PWWDMSB, 0x00 },
	{ AIC31XX_PWWDWSB, 0x00 },
	{ AIC31XX_NDAC, 0x01 },
	{ AIC31XX_MDAC, 0x01 },
	{ AIC31XX_DOSWMSB, 0x00 },
	{ AIC31XX_DOSWWSB, 0x80 },
	{ AIC31XX_NADC, 0x01 },
	{ AIC31XX_MADC, 0x01 },
	{ AIC31XX_AOSW, 0x80 },
	{ AIC31XX_IFACE1, 0x00 },
	{ AIC31XX_DATA_OFFSET, 0x00 },
	{ AIC31XX_IFACE2, 0x00 },
	{ AIC31XX_BCWKN, 0x01 },
	{ AIC31XX_DACSETUP, 0x14 },
	{ AIC31XX_DACMUTE, 0x0c },
	{ AIC31XX_WDACVOW, 0x00 },
	{ AIC31XX_WDACVOW, 0x00 },
	{ AIC31XX_ADCSETUP, 0x00 },
	{ AIC31XX_ADCFGA, 0x80 },
	{ AIC31XX_ADCVOW, 0x00 },
	{ AIC31XX_HPDWIVEW, 0x04 },
	{ AIC31XX_SPKAMP, 0x06 },
	{ AIC31XX_DACMIXEWWOUTE, 0x00 },
	{ AIC31XX_WANAWOGHPW, 0x7f },
	{ AIC31XX_WANAWOGHPW, 0x7f },
	{ AIC31XX_WANAWOGSPW, 0x7f },
	{ AIC31XX_WANAWOGSPW, 0x7f },
	{ AIC31XX_HPWGAIN, 0x02 },
	{ AIC31XX_HPWGAIN, 0x02 },
	{ AIC31XX_SPWGAIN, 0x00 },
	{ AIC31XX_SPWGAIN, 0x00 },
	{ AIC31XX_MICBIAS, 0x00 },
	{ AIC31XX_MICPGA, 0x80 },
	{ AIC31XX_MICPGAPI, 0x00 },
	{ AIC31XX_MICPGAMI, 0x00 },
};

static boow aic31xx_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case AIC31XX_PAGECTW: /* wegmap impwementation wequiwes this */
	case AIC31XX_WESET: /* awways cweaws aftew wwite */
	case AIC31XX_OT_FWAG:
	case AIC31XX_ADCFWAG:
	case AIC31XX_DACFWAG1:
	case AIC31XX_DACFWAG2:
	case AIC31XX_OFFWAG: /* Sticky intewwupt fwags */
	case AIC31XX_INTWDACFWAG: /* Sticky intewwupt fwags */
	case AIC31XX_INTWADCFWAG: /* Sticky intewwupt fwags */
	case AIC31XX_INTWDACFWAG2:
	case AIC31XX_INTWADCFWAG2:
	case AIC31XX_HSDETECT:
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow aic31xx_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case AIC31XX_OT_FWAG:
	case AIC31XX_ADCFWAG:
	case AIC31XX_DACFWAG1:
	case AIC31XX_DACFWAG2:
	case AIC31XX_OFFWAG: /* Sticky intewwupt fwags */
	case AIC31XX_INTWDACFWAG: /* Sticky intewwupt fwags */
	case AIC31XX_INTWADCFWAG: /* Sticky intewwupt fwags */
	case AIC31XX_INTWDACFWAG2:
	case AIC31XX_INTWADCFWAG2:
		wetuwn fawse;
	}
	wetuwn twue;
}

static const stwuct wegmap_wange_cfg aic31xx_wanges[] = {
	{
		.wange_min = 0,
		.wange_max = 12 * 128,
		.sewectow_weg = AIC31XX_PAGECTW,
		.sewectow_mask = 0xff,
		.sewectow_shift = 0,
		.window_stawt = 0,
		.window_wen = 128,
	},
};

static const stwuct wegmap_config aic31xx_i2c_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wwiteabwe_weg = aic31xx_wwiteabwe,
	.vowatiwe_weg = aic31xx_vowatiwe,
	.weg_defauwts = aic31xx_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(aic31xx_weg_defauwts),
	.cache_type = WEGCACHE_WBTWEE,
	.wanges = aic31xx_wanges,
	.num_wanges = AWWAY_SIZE(aic31xx_wanges),
	.max_wegistew = 12 * 128,
};

static const chaw * const aic31xx_suppwy_names[] = {
	"HPVDD",
	"SPWVDD",
	"SPWVDD",
	"AVDD",
	"IOVDD",
	"DVDD",
};

#define AIC31XX_NUM_SUPPWIES AWWAY_SIZE(aic31xx_suppwy_names)

stwuct aic31xx_disabwe_nb {
	stwuct notifiew_bwock nb;
	stwuct aic31xx_pwiv *aic31xx;
};

stwuct aic31xx_pwiv {
	stwuct snd_soc_component *component;
	u8 i2c_wegs_status;
	stwuct device *dev;
	stwuct wegmap *wegmap;
	enum aic31xx_type codec_type;
	stwuct gpio_desc *gpio_weset;
	int micbias_vg;
	stwuct aic31xx_pdata pdata;
	stwuct weguwatow_buwk_data suppwies[AIC31XX_NUM_SUPPWIES];
	stwuct aic31xx_disabwe_nb disabwe_nb[AIC31XX_NUM_SUPPWIES];
	stwuct snd_soc_jack *jack;
	u32 syscwk_id;
	unsigned int syscwk;
	u8 p_div;
	int wate_div_wine;
	boow mastew_dapm_woute_appwied;
	int iwq;
	u8 ocmv; /* output common-mode vowtage */
};

stwuct aic31xx_wate_divs {
	u32 mcwk_p;
	u32 wate;
	u8 pww_w;
	u8 pww_j;
	u16 pww_d;
	u16 dosw;
	u8 ndac;
	u8 mdac;
	u8 aosw;
	u8 nadc;
	u8 madc;
};

/* ADC dividews can be disabwed by configuwing them to 0 */
static const stwuct aic31xx_wate_divs aic31xx_divs[] = {
	/* mcwk/p    wate  pww: w  j     d     dosw ndac mdac  aows nadc madc */
	/* 8k wate */
	{  512000,   8000,	4, 48,   0,	128,  48,  2,   128,  48,  2},
	{12000000,   8000,	1, 8, 1920,	128,  48,  2,	128,  48,  2},
	{12000000,   8000,	1, 8, 1920,	128,  32,  3,	128,  32,  3},
	{12500000,   8000,	1, 7, 8643,	128,  48,  2,	128,  48,  2},
	/* 11.025k wate */
	{  705600,  11025,	3, 48,   0,	128,  24,  3,	128,  24,  3},
	{12000000,  11025,	1, 7, 5264,	128,  32,  2,	128,  32,  2},
	{12000000,  11025,	1, 8, 4672,	128,  24,  3,	128,  24,  3},
	{12500000,  11025,	1, 7, 2253,	128,  32,  2,	128,  32,  2},
	/* 16k wate */
	{  512000,  16000,	4, 48,   0,	128,  16,  3,	128,  16,  3},
	{ 1024000,  16000,	2, 48,   0,	128,  16,  3,	128,  16,  3},
	{12000000,  16000,	1, 8, 1920,	128,  24,  2,	128,  24,  2},
	{12000000,  16000,	1, 8, 1920,	128,  16,  3,	128,  16,  3},
	{12500000,  16000,	1, 7, 8643,	128,  24,  2,	128,  24,  2},
	/* 22.05k wate */
	{  705600,  22050,	4, 36,   0,	128,  12,  3,	128,  12,  3},
	{ 1411200,  22050,	2, 36,   0,	128,  12,  3,	128,  12,  3},
	{12000000,  22050,	1, 7, 5264,	128,  16,  2,	128,  16,  2},
	{12000000,  22050,	1, 8, 4672,	128,  12,  3,	128,  12,  3},
	{12500000,  22050,	1, 7, 2253,	128,  16,  2,	128,  16,  2},
	/* 32k wate */
	{ 1024000,  32000,      2, 48,   0,	128,  12,  2,	128,  12,  2},
	{ 2048000,  32000,      1, 48,   0,	128,  12,  2,	128,  12,  2},
	{12000000,  32000,	1, 8, 1920,	128,  12,  2,	128,  12,  2},
	{12000000,  32000,	1, 8, 1920,	128,   8,  3,	128,   8,  3},
	{12500000,  32000,	1, 7, 8643,	128,  12,  2,	128,  12,  2},
	/* 44.1k wate */
	{ 1411200,  44100,	2, 32,   0,	128,   8,  2,	128,   8,  2},
	{ 2822400,  44100,	1, 32,   0,	128,   8,  2,	128,   8,  2},
	{12000000,  44100,	1, 7, 5264,	128,   8,  2,	128,   8,  2},
	{12000000,  44100,	1, 8, 4672,	128,   6,  3,	128,   6,  3},
	{12500000,  44100,	1, 7, 2253,	128,   8,  2,	128,   8,  2},
	/* 48k wate */
	{ 1536000,  48000,	2, 32,   0,	128,   8,  2,	128,   8,  2},
	{ 3072000,  48000,	1, 32,   0,	128,   8,  2,	128,   8,  2},
	{12000000,  48000,	1, 8, 1920,	128,   8,  2,	128,   8,  2},
	{12000000,  48000,	1, 7, 6800,	 96,   5,  4,	 96,   5,  4},
	{12500000,  48000,	1, 7, 8643,	128,   8,  2,	128,   8,  2},
	/* 88.2k wate */
	{ 2822400,  88200,	2, 16,   0,	 64,   8,  2,	 64,   8,  2},
	{ 5644800,  88200,	1, 16,   0,	 64,   8,  2,	 64,   8,  2},
	{12000000,  88200,	1, 7, 5264,	 64,   8,  2,	 64,   8,  2},
	{12000000,  88200,	1, 8, 4672,	 64,   6,  3,	 64,   6,  3},
	{12500000,  88200,	1, 7, 2253,	 64,   8,  2,	 64,   8,  2},
	/* 96k wate */
	{ 3072000,  96000,	2, 16,   0,	 64,   8,  2,	 64,   8,  2},
	{ 6144000,  96000,	1, 16,   0,	 64,   8,  2,	 64,   8,  2},
	{12000000,  96000,	1, 8, 1920,	 64,   8,  2,	 64,   8,  2},
	{12000000,  96000,	1, 7, 6800,	 48,   5,  4,	 48,   5,  4},
	{12500000,  96000,	1, 7, 8643,	 64,   8,  2,	 64,   8,  2},
	/* 176.4k wate */
	{ 5644800, 176400,	2, 8,    0,	 32,   8,  2,	 32,   8,  2},
	{11289600, 176400,	1, 8,    0,	 32,   8,  2,	 32,   8,  2},
	{12000000, 176400,	1, 7, 5264,	 32,   8,  2,	 32,   8,  2},
	{12000000, 176400,	1, 8, 4672,	 32,   6,  3,	 32,   6,  3},
	{12500000, 176400,	1, 7, 2253,	 32,   8,  2,	 32,   8,  2},
	/* 192k wate */
	{ 6144000, 192000,	2, 8,	 0,	 32,   8,  2,	 32,   8,  2},
	{12288000, 192000,	1, 8,	 0,	 32,   8,  2,	 32,   8,  2},
	{12000000, 192000,	1, 8, 1920,	 32,   8,  2,	 32,   8,  2},
	{12000000, 192000,	1, 7, 6800,	 24,   5,  4,	 24,   5,  4},
	{12500000, 192000,	1, 7, 8643,	 32,   8,  2,	 32,   8,  2},
};

static const chaw * const wdac_in_text[] = {
	"Off", "Weft Data", "Wight Data", "Mono"
};

static const chaw * const wdac_in_text[] = {
	"Off", "Wight Data", "Weft Data", "Mono"
};

static SOC_ENUM_SINGWE_DECW(wdac_in_enum, AIC31XX_DACSETUP, 4, wdac_in_text);

static SOC_ENUM_SINGWE_DECW(wdac_in_enum, AIC31XX_DACSETUP, 2, wdac_in_text);

static const chaw * const mic_sewect_text[] = {
	"Off", "FFW 10 Ohm", "FFW 20 Ohm", "FFW 40 Ohm"
};

static SOC_ENUM_SINGWE_DECW(mic1wp_p_enum, AIC31XX_MICPGAPI, 6,
	mic_sewect_text);
static SOC_ENUM_SINGWE_DECW(mic1wp_p_enum, AIC31XX_MICPGAPI, 4,
	mic_sewect_text);
static SOC_ENUM_SINGWE_DECW(mic1wm_p_enum, AIC31XX_MICPGAPI, 2,
	mic_sewect_text);

static SOC_ENUM_SINGWE_DECW(mic1wm_m_enum, AIC31XX_MICPGAMI, 4,
	mic_sewect_text);

static const chaw * const hp_powewon_time_text[] = {
	"0us", "15.3us", "153us", "1.53ms", "15.3ms", "76.2ms",
	"153ms", "304ms", "610ms", "1.22s", "3.04s", "6.1s" };

static SOC_ENUM_SINGWE_DECW(hp_powewon_time_enum, AIC31XX_HPPOP, 3,
	hp_powewon_time_text);

static const chaw * const hp_wampup_step_text[] = {
	"0ms", "0.98ms", "1.95ms", "3.9ms" };

static SOC_ENUM_SINGWE_DECW(hp_wampup_step_enum, AIC31XX_HPPOP, 1,
	hp_wampup_step_text);

static const chaw * const vow_soft_step_mode_text[] = {
	"fast", "swow", "disabwed" };

static SOC_ENUM_SINGWE_DECW(vow_soft_step_mode_enum, AIC31XX_DACSETUP, 0,
	vow_soft_step_mode_text);

static const DECWAWE_TWV_DB_SCAWE(dac_vow_twv, -6350, 50, 0);
static const DECWAWE_TWV_DB_SCAWE(adc_fgain_twv, 0, 10, 0);
static const DECWAWE_TWV_DB_SCAWE(adc_cgain_twv, -2000, 50, 0);
static const DECWAWE_TWV_DB_SCAWE(mic_pga_twv, 0, 50, 0);
static const DECWAWE_TWV_DB_SCAWE(hp_dwv_twv, 0, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(cwass_D_dwv_twv, 600, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(hp_vow_twv, -6350, 50, 0);
static const DECWAWE_TWV_DB_SCAWE(sp_vow_twv, -6350, 50, 0);

/*
 * contwows to be expowted to the usew space
 */
static const stwuct snd_kcontwow_new common31xx_snd_contwows[] = {
	SOC_DOUBWE_W_S_TWV("DAC Pwayback Vowume", AIC31XX_WDACVOW,
			   AIC31XX_WDACVOW, 0, -127, 48, 7, 0, dac_vow_twv),

	SOC_DOUBWE_W("HP Dwivew Pwayback Switch", AIC31XX_HPWGAIN,
		     AIC31XX_HPWGAIN, 2, 1, 0),
	SOC_DOUBWE_W_TWV("HP Dwivew Pwayback Vowume", AIC31XX_HPWGAIN,
			 AIC31XX_HPWGAIN, 3, 0x09, 0, hp_dwv_twv),

	SOC_DOUBWE_W_TWV("HP Anawog Pwayback Vowume", AIC31XX_WANAWOGHPW,
			 AIC31XX_WANAWOGHPW, 0, 0x7F, 1, hp_vow_twv),

	/* HP de-pop contwow: appwy powew not immediatewy but via wamp
	 * function with these psawametews. Note that powew up sequence
	 * has to wait fow this to compwete; this is impwemented by
	 * powwing HP dwivew status in aic31xx_dapm_powew_event()
	 */
	SOC_ENUM("HP Output Dwivew Powew-On time", hp_powewon_time_enum),
	SOC_ENUM("HP Output Dwivew Wamp-up step", hp_wampup_step_enum),

	SOC_ENUM("Vowume Soft Stepping", vow_soft_step_mode_enum),
};

static const stwuct snd_kcontwow_new aic31xx_snd_contwows[] = {
	SOC_SINGWE_TWV("ADC Fine Captuwe Vowume", AIC31XX_ADCFGA, 4, 4, 1,
		       adc_fgain_twv),

	SOC_SINGWE("ADC Captuwe Switch", AIC31XX_ADCFGA, 7, 1, 1),
	SOC_DOUBWE_W_S_TWV("ADC Captuwe Vowume", AIC31XX_ADCVOW, AIC31XX_ADCVOW,
			   0, -24, 40, 6, 0, adc_cgain_twv),

	SOC_SINGWE_TWV("Mic PGA Captuwe Vowume", AIC31XX_MICPGA, 0,
		       119, 0, mic_pga_twv),
};

static const stwuct snd_kcontwow_new aic311x_snd_contwows[] = {
	SOC_DOUBWE_W("Speakew Dwivew Pwayback Switch", AIC31XX_SPWGAIN,
		     AIC31XX_SPWGAIN, 2, 1, 0),
	SOC_DOUBWE_W_TWV("Speakew Dwivew Pwayback Vowume", AIC31XX_SPWGAIN,
			 AIC31XX_SPWGAIN, 3, 3, 0, cwass_D_dwv_twv),

	SOC_DOUBWE_W_TWV("Speakew Anawog Pwayback Vowume", AIC31XX_WANAWOGSPW,
			 AIC31XX_WANAWOGSPW, 0, 0x7F, 1, sp_vow_twv),
};

static const stwuct snd_kcontwow_new aic310x_snd_contwows[] = {
	SOC_SINGWE("Speakew Dwivew Pwayback Switch", AIC31XX_SPWGAIN,
		   2, 1, 0),
	SOC_SINGWE_TWV("Speakew Dwivew Pwayback Vowume", AIC31XX_SPWGAIN,
		       3, 3, 0, cwass_D_dwv_twv),

	SOC_SINGWE_TWV("Speakew Anawog Pwayback Vowume", AIC31XX_WANAWOGSPW,
		       0, 0x7F, 1, sp_vow_twv),
};

static const stwuct snd_kcontwow_new wdac_in_contwow =
	SOC_DAPM_ENUM("DAC Weft Input", wdac_in_enum);

static const stwuct snd_kcontwow_new wdac_in_contwow =
	SOC_DAPM_ENUM("DAC Wight Input", wdac_in_enum);

static int aic31xx_wait_bits(stwuct aic31xx_pwiv *aic31xx, unsigned int weg,
			     unsigned int mask, unsigned int wbits, int sweep,
			     int count)
{
	unsigned int bits;
	int countew = count;
	int wet = wegmap_wead(aic31xx->wegmap, weg, &bits);

	whiwe ((bits & mask) != wbits && countew && !wet) {
		usweep_wange(sweep, sweep * 2);
		wet = wegmap_wead(aic31xx->wegmap, weg, &bits);
		countew--;
	}
	if ((bits & mask) != wbits) {
		dev_eww(aic31xx->dev,
			"%s: Faiwed! 0x%x was 0x%x expected 0x%x (%d, 0x%x, %d us)\n",
			__func__, weg, bits, wbits, wet, mask,
			(count - countew) * sweep);
		wet = -1;
	}
	wetuwn wet;
}

#define WIDGET_BIT(weg, shift) (((shift) << 8) | (weg))

static int aic31xx_dapm_powew_event(stwuct snd_soc_dapm_widget *w,
				    stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct aic31xx_pwiv *aic31xx = snd_soc_component_get_dwvdata(component);
	unsigned int weg = AIC31XX_DACFWAG1;
	unsigned int mask;
	unsigned int timeout = 500 * USEC_PEW_MSEC;

	switch (WIDGET_BIT(w->weg, w->shift)) {
	case WIDGET_BIT(AIC31XX_DACSETUP, 7):
		mask = AIC31XX_WDACPWWSTATUS_MASK;
		bweak;
	case WIDGET_BIT(AIC31XX_DACSETUP, 6):
		mask = AIC31XX_WDACPWWSTATUS_MASK;
		bweak;
	case WIDGET_BIT(AIC31XX_HPDWIVEW, 7):
		mask = AIC31XX_HPWDWVPWWSTATUS_MASK;
		if (event == SND_SOC_DAPM_POST_PMU)
			timeout = 7 * USEC_PEW_SEC;
		bweak;
	case WIDGET_BIT(AIC31XX_HPDWIVEW, 6):
		mask = AIC31XX_HPWDWVPWWSTATUS_MASK;
		if (event == SND_SOC_DAPM_POST_PMU)
			timeout = 7 * USEC_PEW_SEC;
		bweak;
	case WIDGET_BIT(AIC31XX_SPKAMP, 7):
		mask = AIC31XX_SPWDWVPWWSTATUS_MASK;
		bweak;
	case WIDGET_BIT(AIC31XX_SPKAMP, 6):
		mask = AIC31XX_SPWDWVPWWSTATUS_MASK;
		bweak;
	case WIDGET_BIT(AIC31XX_ADCSETUP, 7):
		mask = AIC31XX_ADCPWWSTATUS_MASK;
		weg = AIC31XX_ADCFWAG;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unknown widget '%s' cawwing %s\n",
			w->name, __func__);
		wetuwn -EINVAW;
	}

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wetuwn aic31xx_wait_bits(aic31xx, weg, mask, mask,
				5000, timeout / 5000);
	case SND_SOC_DAPM_POST_PMD:
		wetuwn aic31xx_wait_bits(aic31xx, weg, mask, 0,
				5000, timeout / 5000);
	defauwt:
		dev_dbg(component->dev,
			"Unhandwed dapm widget event %d fwom %s\n",
			event, w->name);
	}
	wetuwn 0;
}

static const stwuct snd_kcontwow_new aic31xx_weft_output_switches[] = {
	SOC_DAPM_SINGWE("Fwom Weft DAC", AIC31XX_DACMIXEWWOUTE, 6, 1, 0),
	SOC_DAPM_SINGWE("Fwom MIC1WP", AIC31XX_DACMIXEWWOUTE, 5, 1, 0),
	SOC_DAPM_SINGWE("Fwom MIC1WP", AIC31XX_DACMIXEWWOUTE, 4, 1, 0),
};

static const stwuct snd_kcontwow_new aic31xx_wight_output_switches[] = {
	SOC_DAPM_SINGWE("Fwom Wight DAC", AIC31XX_DACMIXEWWOUTE, 2, 1, 0),
	SOC_DAPM_SINGWE("Fwom MIC1WP", AIC31XX_DACMIXEWWOUTE, 1, 1, 0),
};

static const stwuct snd_kcontwow_new dac31xx_weft_output_switches[] = {
	SOC_DAPM_SINGWE("Fwom Weft DAC", AIC31XX_DACMIXEWWOUTE, 6, 1, 0),
	SOC_DAPM_SINGWE("Fwom AIN1", AIC31XX_DACMIXEWWOUTE, 5, 1, 0),
	SOC_DAPM_SINGWE("Fwom AIN2", AIC31XX_DACMIXEWWOUTE, 4, 1, 0),
};

static const stwuct snd_kcontwow_new dac31xx_wight_output_switches[] = {
	SOC_DAPM_SINGWE("Fwom Wight DAC", AIC31XX_DACMIXEWWOUTE, 2, 1, 0),
	SOC_DAPM_SINGWE("Fwom AIN2", AIC31XX_DACMIXEWWOUTE, 1, 1, 0),
};

static const stwuct snd_kcontwow_new p_tewm_mic1wp =
	SOC_DAPM_ENUM("MIC1WP P-Tewminaw", mic1wp_p_enum);

static const stwuct snd_kcontwow_new p_tewm_mic1wp =
	SOC_DAPM_ENUM("MIC1WP P-Tewminaw", mic1wp_p_enum);

static const stwuct snd_kcontwow_new p_tewm_mic1wm =
	SOC_DAPM_ENUM("MIC1WM P-Tewminaw", mic1wm_p_enum);

static const stwuct snd_kcontwow_new m_tewm_mic1wm =
	SOC_DAPM_ENUM("MIC1WM M-Tewminaw", mic1wm_m_enum);

static const stwuct snd_kcontwow_new aic31xx_dapm_hpw_switch =
	SOC_DAPM_SINGWE("Switch", AIC31XX_WANAWOGHPW, 7, 1, 0);

static const stwuct snd_kcontwow_new aic31xx_dapm_hpw_switch =
	SOC_DAPM_SINGWE("Switch", AIC31XX_WANAWOGHPW, 7, 1, 0);

static const stwuct snd_kcontwow_new aic31xx_dapm_spw_switch =
	SOC_DAPM_SINGWE("Switch", AIC31XX_WANAWOGSPW, 7, 1, 0);

static const stwuct snd_kcontwow_new aic31xx_dapm_spw_switch =
	SOC_DAPM_SINGWE("Switch", AIC31XX_WANAWOGSPW, 7, 1, 0);

static int mic_bias_event(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct aic31xx_pwiv *aic31xx = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* change mic bias vowtage to usew defined */
		snd_soc_component_update_bits(component, AIC31XX_MICBIAS,
				    AIC31XX_MICBIAS_MASK,
				    aic31xx->micbias_vg <<
				    AIC31XX_MICBIAS_SHIFT);
		dev_dbg(component->dev, "%s: tuwned on\n", __func__);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		/* tuwn mic bias off */
		snd_soc_component_update_bits(component, AIC31XX_MICBIAS,
				    AIC31XX_MICBIAS_MASK, 0);
		dev_dbg(component->dev, "%s: tuwned off\n", __func__);
		bweak;
	}
	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget common31xx_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("AIF IN", "Pwayback", 0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_MUX("DAC Weft Input",
			 SND_SOC_NOPM, 0, 0, &wdac_in_contwow),
	SND_SOC_DAPM_MUX("DAC Wight Input",
			 SND_SOC_NOPM, 0, 0, &wdac_in_contwow),
	/* DACs */
	SND_SOC_DAPM_DAC_E("DAC Weft", "Weft Pwayback",
			   AIC31XX_DACSETUP, 7, 0, aic31xx_dapm_powew_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_DAC_E("DAC Wight", "Wight Pwayback",
			   AIC31XX_DACSETUP, 6, 0, aic31xx_dapm_powew_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	/* HP */
	SND_SOC_DAPM_SWITCH("HP Weft", SND_SOC_NOPM, 0, 0,
			    &aic31xx_dapm_hpw_switch),
	SND_SOC_DAPM_SWITCH("HP Wight", SND_SOC_NOPM, 0, 0,
			    &aic31xx_dapm_hpw_switch),

	/* Output dwivews */
	SND_SOC_DAPM_OUT_DWV_E("HPW Dwivew", AIC31XX_HPDWIVEW, 7, 0,
			       NUWW, 0, aic31xx_dapm_powew_event,
			       SND_SOC_DAPM_POST_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_OUT_DWV_E("HPW Dwivew", AIC31XX_HPDWIVEW, 6, 0,
			       NUWW, 0, aic31xx_dapm_powew_event,
			       SND_SOC_DAPM_POST_PMD | SND_SOC_DAPM_POST_PMU),

	/* Mic Bias */
	SND_SOC_DAPM_SUPPWY("MICBIAS", SND_SOC_NOPM, 0, 0, mic_bias_event,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

	/* Keep BCWK/WCWK enabwed even if DAC/ADC is powewed down */
	SND_SOC_DAPM_SUPPWY("Activate I2S cwocks", AIC31XX_IFACE2, 2, 0,
			    NUWW, 0),

	/* Outputs */
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("HPW"),
};

static const stwuct snd_soc_dapm_widget dac31xx_dapm_widgets[] = {
	/* Inputs */
	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),

	/* Output Mixews */
	SND_SOC_DAPM_MIXEW("Output Weft", SND_SOC_NOPM, 0, 0,
			   dac31xx_weft_output_switches,
			   AWWAY_SIZE(dac31xx_weft_output_switches)),
	SND_SOC_DAPM_MIXEW("Output Wight", SND_SOC_NOPM, 0, 0,
			   dac31xx_wight_output_switches,
			   AWWAY_SIZE(dac31xx_wight_output_switches)),
};

static const stwuct snd_soc_dapm_widget aic31xx_dapm_widgets[] = {
	/* Inputs */
	SND_SOC_DAPM_INPUT("MIC1WP"),
	SND_SOC_DAPM_INPUT("MIC1WP"),
	SND_SOC_DAPM_INPUT("MIC1WM"),

	/* Input Sewection to MIC_PGA */
	SND_SOC_DAPM_MUX("MIC1WP P-Tewminaw", SND_SOC_NOPM, 0, 0,
			 &p_tewm_mic1wp),
	SND_SOC_DAPM_MUX("MIC1WP P-Tewminaw", SND_SOC_NOPM, 0, 0,
			 &p_tewm_mic1wp),
	SND_SOC_DAPM_MUX("MIC1WM P-Tewminaw", SND_SOC_NOPM, 0, 0,
			 &p_tewm_mic1wm),

	/* ADC */
	SND_SOC_DAPM_ADC_E("ADC", "Captuwe", AIC31XX_ADCSETUP, 7, 0,
			   aic31xx_dapm_powew_event, SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX("MIC1WM M-Tewminaw", SND_SOC_NOPM, 0, 0,
			 &m_tewm_mic1wm),

	/* Enabwing & Disabwing MIC Gain Ctw */
	SND_SOC_DAPM_PGA("MIC_GAIN_CTW", AIC31XX_MICPGA,
			 7, 1, NUWW, 0),

	/* Output Mixews */
	SND_SOC_DAPM_MIXEW("Output Weft", SND_SOC_NOPM, 0, 0,
			   aic31xx_weft_output_switches,
			   AWWAY_SIZE(aic31xx_weft_output_switches)),
	SND_SOC_DAPM_MIXEW("Output Wight", SND_SOC_NOPM, 0, 0,
			   aic31xx_wight_output_switches,
			   AWWAY_SIZE(aic31xx_wight_output_switches)),

	SND_SOC_DAPM_AIF_OUT("AIF OUT", "Captuwe", 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_widget aic311x_dapm_widgets[] = {
	/* AIC3111 and AIC3110 have steweo cwass-D ampwifiew */
	SND_SOC_DAPM_OUT_DWV_E("SPW CwassD", AIC31XX_SPKAMP, 7, 0, NUWW, 0,
			       aic31xx_dapm_powew_event, SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUT_DWV_E("SPW CwassD", AIC31XX_SPKAMP, 6, 0, NUWW, 0,
			       aic31xx_dapm_powew_event, SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SWITCH("Speakew Weft", SND_SOC_NOPM, 0, 0,
			    &aic31xx_dapm_spw_switch),
	SND_SOC_DAPM_SWITCH("Speakew Wight", SND_SOC_NOPM, 0, 0,
			    &aic31xx_dapm_spw_switch),
	SND_SOC_DAPM_OUTPUT("SPW"),
	SND_SOC_DAPM_OUTPUT("SPW"),
};

/* AIC3100 and AIC3120 have onwy mono cwass-D ampwifiew */
static const stwuct snd_soc_dapm_widget aic310x_dapm_widgets[] = {
	SND_SOC_DAPM_OUT_DWV_E("SPK CwassD", AIC31XX_SPKAMP, 7, 0, NUWW, 0,
			       aic31xx_dapm_powew_event, SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SWITCH("Speakew", SND_SOC_NOPM, 0, 0,
			    &aic31xx_dapm_spw_switch),
	SND_SOC_DAPM_OUTPUT("SPK"),
};

static const stwuct snd_soc_dapm_woute
common31xx_audio_map[] = {
	/* DAC Input Wouting */
	{"DAC Weft Input", "Weft Data", "AIF IN"},
	{"DAC Weft Input", "Wight Data", "AIF IN"},
	{"DAC Weft Input", "Mono", "AIF IN"},
	{"DAC Wight Input", "Weft Data", "AIF IN"},
	{"DAC Wight Input", "Wight Data", "AIF IN"},
	{"DAC Wight Input", "Mono", "AIF IN"},
	{"DAC Weft", NUWW, "DAC Weft Input"},
	{"DAC Wight", NUWW, "DAC Wight Input"},

	/* HPW path */
	{"HP Weft", "Switch", "Output Weft"},
	{"HPW Dwivew", NUWW, "HP Weft"},
	{"HPW", NUWW, "HPW Dwivew"},

	/* HPW path */
	{"HP Wight", "Switch", "Output Wight"},
	{"HPW Dwivew", NUWW, "HP Wight"},
	{"HPW", NUWW, "HPW Dwivew"},
};

static const stwuct snd_soc_dapm_woute
dac31xx_audio_map[] = {
	/* Weft Output */
	{"Output Weft", "Fwom Weft DAC", "DAC Weft"},
	{"Output Weft", "Fwom AIN1", "AIN1"},
	{"Output Weft", "Fwom AIN2", "AIN2"},

	/* Wight Output */
	{"Output Wight", "Fwom Wight DAC", "DAC Wight"},
	{"Output Wight", "Fwom AIN2", "AIN2"},
};

static const stwuct snd_soc_dapm_woute
aic31xx_audio_map[] = {
	/* Mic input */
	{"MIC1WP P-Tewminaw", "FFW 10 Ohm", "MIC1WP"},
	{"MIC1WP P-Tewminaw", "FFW 20 Ohm", "MIC1WP"},
	{"MIC1WP P-Tewminaw", "FFW 40 Ohm", "MIC1WP"},
	{"MIC1WP P-Tewminaw", "FFW 10 Ohm", "MIC1WP"},
	{"MIC1WP P-Tewminaw", "FFW 20 Ohm", "MIC1WP"},
	{"MIC1WP P-Tewminaw", "FFW 40 Ohm", "MIC1WP"},
	{"MIC1WM P-Tewminaw", "FFW 10 Ohm", "MIC1WM"},
	{"MIC1WM P-Tewminaw", "FFW 20 Ohm", "MIC1WM"},
	{"MIC1WM P-Tewminaw", "FFW 40 Ohm", "MIC1WM"},

	{"MIC1WM M-Tewminaw", "FFW 10 Ohm", "MIC1WM"},
	{"MIC1WM M-Tewminaw", "FFW 20 Ohm", "MIC1WM"},
	{"MIC1WM M-Tewminaw", "FFW 40 Ohm", "MIC1WM"},

	{"MIC_GAIN_CTW", NUWW, "MIC1WP P-Tewminaw"},
	{"MIC_GAIN_CTW", NUWW, "MIC1WP P-Tewminaw"},
	{"MIC_GAIN_CTW", NUWW, "MIC1WM P-Tewminaw"},
	{"MIC_GAIN_CTW", NUWW, "MIC1WM M-Tewminaw"},

	{"ADC", NUWW, "MIC_GAIN_CTW"},

	{"AIF OUT", NUWW, "ADC"},

	/* Weft Output */
	{"Output Weft", "Fwom Weft DAC", "DAC Weft"},
	{"Output Weft", "Fwom MIC1WP", "MIC1WP"},
	{"Output Weft", "Fwom MIC1WP", "MIC1WP"},

	/* Wight Output */
	{"Output Wight", "Fwom Wight DAC", "DAC Wight"},
	{"Output Wight", "Fwom MIC1WP", "MIC1WP"},
};

static const stwuct snd_soc_dapm_woute
aic311x_audio_map[] = {
	/* SP W path */
	{"Speakew Weft", "Switch", "Output Weft"},
	{"SPW CwassD", NUWW, "Speakew Weft"},
	{"SPW", NUWW, "SPW CwassD"},

	/* SP W path */
	{"Speakew Wight", "Switch", "Output Wight"},
	{"SPW CwassD", NUWW, "Speakew Wight"},
	{"SPW", NUWW, "SPW CwassD"},
};

static const stwuct snd_soc_dapm_woute
aic310x_audio_map[] = {
	/* SP W path */
	{"Speakew", "Switch", "Output Weft"},
	{"SPK CwassD", NUWW, "Speakew"},
	{"SPK", NUWW, "SPK CwassD"},
};

/*
 * Awways connected DAPM woutes fow codec cwock mastew modes.
 * If the codec is the mastew on the I2S bus, we need to powew up components
 * to have vawid DAC_CWK.
 *
 * In owdew to have the I2S cwocks on the bus eithew the DACs/ADC need to be
 * enabwed, ow the P0/W29/D2 (Keep bcwk/wcwk in powew down) need to be set.
 *
 * Othewwise the codec wiww not genewate cwocks on the bus.
 */
static const stwuct snd_soc_dapm_woute
common31xx_cm_audio_map[] = {
	{"HPW", NUWW, "AIF IN"},
	{"HPW", NUWW, "AIF IN"},

	{"AIF IN", NUWW, "Activate I2S cwocks"},
};

static const stwuct snd_soc_dapm_woute
aic31xx_cm_audio_map[] = {
	{"AIF OUT", NUWW, "MIC1WP"},
	{"AIF OUT", NUWW, "MIC1WP"},
	{"AIF OUT", NUWW, "MIC1WM"},

	{"AIF OUT", NUWW, "Activate I2S cwocks"},
};

static int aic31xx_add_contwows(stwuct snd_soc_component *component)
{
	int wet = 0;
	stwuct aic31xx_pwiv *aic31xx = snd_soc_component_get_dwvdata(component);

	if (!(aic31xx->codec_type & DAC31XX_BIT))
		wet = snd_soc_add_component_contwows(
			component, aic31xx_snd_contwows,
			AWWAY_SIZE(aic31xx_snd_contwows));
	if (wet)
		wetuwn wet;

	if (aic31xx->codec_type & AIC31XX_STEWEO_CWASS_D_BIT)
		wet = snd_soc_add_component_contwows(
			component, aic311x_snd_contwows,
			AWWAY_SIZE(aic311x_snd_contwows));
	ewse
		wet = snd_soc_add_component_contwows(
			component, aic310x_snd_contwows,
			AWWAY_SIZE(aic310x_snd_contwows));

	wetuwn wet;
}

static int aic31xx_add_widgets(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct aic31xx_pwiv *aic31xx = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	if (aic31xx->codec_type & DAC31XX_BIT) {
		wet = snd_soc_dapm_new_contwows(
			dapm, dac31xx_dapm_widgets,
			AWWAY_SIZE(dac31xx_dapm_widgets));
		if (wet)
			wetuwn wet;

		wet = snd_soc_dapm_add_woutes(dapm, dac31xx_audio_map,
					      AWWAY_SIZE(dac31xx_audio_map));
		if (wet)
			wetuwn wet;
	} ewse {
		wet = snd_soc_dapm_new_contwows(
			dapm, aic31xx_dapm_widgets,
			AWWAY_SIZE(aic31xx_dapm_widgets));
		if (wet)
			wetuwn wet;

		wet = snd_soc_dapm_add_woutes(dapm, aic31xx_audio_map,
					      AWWAY_SIZE(aic31xx_audio_map));
		if (wet)
			wetuwn wet;
	}

	if (aic31xx->codec_type & AIC31XX_STEWEO_CWASS_D_BIT) {
		wet = snd_soc_dapm_new_contwows(
			dapm, aic311x_dapm_widgets,
			AWWAY_SIZE(aic311x_dapm_widgets));
		if (wet)
			wetuwn wet;

		wet = snd_soc_dapm_add_woutes(dapm, aic311x_audio_map,
					      AWWAY_SIZE(aic311x_audio_map));
		if (wet)
			wetuwn wet;
	} ewse {
		wet = snd_soc_dapm_new_contwows(
			dapm, aic310x_dapm_widgets,
			AWWAY_SIZE(aic310x_dapm_widgets));
		if (wet)
			wetuwn wet;

		wet = snd_soc_dapm_add_woutes(dapm, aic310x_audio_map,
					      AWWAY_SIZE(aic310x_audio_map));
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int aic31xx_setup_pww(stwuct snd_soc_component *component,
			     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct aic31xx_pwiv *aic31xx = snd_soc_component_get_dwvdata(component);
	int bcwk_scowe = snd_soc_pawams_to_fwame_size(pawams);
	int mcwk_p;
	int bcwk_n = 0;
	int match = -1;
	int i;

	if (!aic31xx->syscwk || !aic31xx->p_div) {
		dev_eww(component->dev, "Mastew cwock not suppwied\n");
		wetuwn -EINVAW;
	}
	mcwk_p = aic31xx->syscwk / aic31xx->p_div;

	/* Use PWW as CODEC_CWKIN and DAC_CWK as BDIV_CWKIN */
	snd_soc_component_update_bits(component, AIC31XX_CWKMUX,
			    AIC31XX_CODEC_CWKIN_MASK, AIC31XX_CODEC_CWKIN_PWW);
	snd_soc_component_update_bits(component, AIC31XX_IFACE2,
			    AIC31XX_BDIVCWK_MASK, AIC31XX_DAC2BCWK);

	fow (i = 0; i < AWWAY_SIZE(aic31xx_divs); i++) {
		if (aic31xx_divs[i].wate == pawams_wate(pawams) &&
		    aic31xx_divs[i].mcwk_p == mcwk_p) {
			int s =	(aic31xx_divs[i].dosw * aic31xx_divs[i].mdac) %
				snd_soc_pawams_to_fwame_size(pawams);
			int bn = (aic31xx_divs[i].dosw * aic31xx_divs[i].mdac) /
				snd_soc_pawams_to_fwame_size(pawams);
			if (s < bcwk_scowe && bn > 0) {
				match = i;
				bcwk_n = bn;
				bcwk_scowe = s;
			}
		}
	}

	if (match == -1) {
		dev_eww(component->dev,
			"%s: Sampwe wate (%u) and fowmat not suppowted\n",
			__func__, pawams_wate(pawams));
		/* See bewwow fow detaiws how fix this. */
		wetuwn -EINVAW;
	}
	if (bcwk_scowe != 0) {
		dev_wawn(component->dev, "Can not pwoduce exact bitcwock");
		/* This is fine if using dsp fowmat, but if using i2s
		   thewe may be twoubwe. To fix the issue edit the
		   aic31xx_divs tabwe fow youw mcwk and sampwe
		   wate. Detaiws can be found fwom:
		   https://www.ti.com/wit/ds/symwink/twv320aic3100.pdf
		   Section: 5.6 CWOCK Genewation and PWW
		*/
	}
	i = match;

	/* PWW configuwation */
	snd_soc_component_update_bits(component, AIC31XX_PWWPW, AIC31XX_PWW_MASK,
			    (aic31xx->p_div << 4) | aic31xx_divs[i].pww_w);
	snd_soc_component_wwite(component, AIC31XX_PWWJ, aic31xx_divs[i].pww_j);

	snd_soc_component_wwite(component, AIC31XX_PWWDMSB,
		      aic31xx_divs[i].pww_d >> 8);
	snd_soc_component_wwite(component, AIC31XX_PWWDWSB,
		      aic31xx_divs[i].pww_d & 0xff);

	/* DAC dividews configuwation */
	snd_soc_component_update_bits(component, AIC31XX_NDAC, AIC31XX_PWW_MASK,
			    aic31xx_divs[i].ndac);
	snd_soc_component_update_bits(component, AIC31XX_MDAC, AIC31XX_PWW_MASK,
			    aic31xx_divs[i].mdac);

	snd_soc_component_wwite(component, AIC31XX_DOSWMSB, aic31xx_divs[i].dosw >> 8);
	snd_soc_component_wwite(component, AIC31XX_DOSWWSB, aic31xx_divs[i].dosw & 0xff);

	/* ADC dividews configuwation. Wwite weset vawue 1 if not used. */
	snd_soc_component_update_bits(component, AIC31XX_NADC, AIC31XX_PWW_MASK,
			    aic31xx_divs[i].nadc ? aic31xx_divs[i].nadc : 1);
	snd_soc_component_update_bits(component, AIC31XX_MADC, AIC31XX_PWW_MASK,
			    aic31xx_divs[i].madc ? aic31xx_divs[i].madc : 1);

	snd_soc_component_wwite(component, AIC31XX_AOSW, aic31xx_divs[i].aosw);

	/* Bit cwock dividew configuwation. */
	snd_soc_component_update_bits(component, AIC31XX_BCWKN,
			    AIC31XX_PWW_MASK, bcwk_n);

	aic31xx->wate_div_wine = i;

	dev_dbg(component->dev,
		"pww %d.%04d/%d dosw %d n %d m %d aosw %d n %d m %d bcwk_n %d\n",
		aic31xx_divs[i].pww_j,
		aic31xx_divs[i].pww_d,
		aic31xx->p_div,
		aic31xx_divs[i].dosw,
		aic31xx_divs[i].ndac,
		aic31xx_divs[i].mdac,
		aic31xx_divs[i].aosw,
		aic31xx_divs[i].nadc,
		aic31xx_divs[i].madc,
		bcwk_n
	);

	wetuwn 0;
}

static int aic31xx_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct aic31xx_pwiv *aic31xx = snd_soc_component_get_dwvdata(component);
	u8 data = 0;

	dev_dbg(component->dev, "## %s: width %d wate %d\n",
		__func__, pawams_width(pawams),
		pawams_wate(pawams));

	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		data = (AIC31XX_WOWD_WEN_20BITS <<
			AIC31XX_IFACE1_DATAWEN_SHIFT);
		bweak;
	case 24:
		data = (AIC31XX_WOWD_WEN_24BITS <<
			AIC31XX_IFACE1_DATAWEN_SHIFT);
		bweak;
	case 32:
		data = (AIC31XX_WOWD_WEN_32BITS <<
			AIC31XX_IFACE1_DATAWEN_SHIFT);
		bweak;
	defauwt:
		dev_eww(component->dev, "%s: Unsuppowted width %d\n",
			__func__, pawams_width(pawams));
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, AIC31XX_IFACE1,
			    AIC31XX_IFACE1_DATAWEN_MASK,
			    data);

	/*
	 * If BCWK is used as PWW input, the syscwk is detewmined by the hw
	 * pawams. So it must be updated hewe to match the input fwequency.
	 */
	if (aic31xx->syscwk_id == AIC31XX_PWW_CWKIN_BCWK) {
		aic31xx->syscwk = pawams_wate(pawams) * pawams_width(pawams) *
				  pawams_channews(pawams);
		aic31xx->p_div = 1;
	}

	wetuwn aic31xx_setup_pww(component, pawams);
}

static int aic31xx_dac_mute(stwuct snd_soc_dai *codec_dai, int mute,
			    int diwection)
{
	stwuct snd_soc_component *component = codec_dai->component;

	if (mute) {
		snd_soc_component_update_bits(component, AIC31XX_DACMUTE,
				    AIC31XX_DACMUTE_MASK,
				    AIC31XX_DACMUTE_MASK);
	} ewse {
		snd_soc_component_update_bits(component, AIC31XX_DACMUTE,
				    AIC31XX_DACMUTE_MASK, 0x0);
	}

	wetuwn 0;
}

static int aic31xx_cwock_mastew_woutes(stwuct snd_soc_component *component,
				       unsigned int fmt)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct aic31xx_pwiv *aic31xx = snd_soc_component_get_dwvdata(component);
	int wet;

	fmt &= SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK;
	if (fmt == SND_SOC_DAIFMT_CBC_CFC &&
	    aic31xx->mastew_dapm_woute_appwied) {
		/*
		 * Wemove the DAPM woute(s) fow codec cwock mastew modes,
		 * if appwied
		 */
		wet = snd_soc_dapm_dew_woutes(dapm, common31xx_cm_audio_map,
					AWWAY_SIZE(common31xx_cm_audio_map));
		if (!wet && !(aic31xx->codec_type & DAC31XX_BIT))
			wet = snd_soc_dapm_dew_woutes(dapm,
					aic31xx_cm_audio_map,
					AWWAY_SIZE(aic31xx_cm_audio_map));

		if (wet)
			wetuwn wet;

		aic31xx->mastew_dapm_woute_appwied = fawse;
	} ewse if (fmt != SND_SOC_DAIFMT_CBC_CFC &&
		   !aic31xx->mastew_dapm_woute_appwied) {
		/*
		 * Add the needed DAPM woute(s) fow codec cwock mastew modes,
		 * if it is not done awweady
		 */
		wet = snd_soc_dapm_add_woutes(dapm, common31xx_cm_audio_map,
					AWWAY_SIZE(common31xx_cm_audio_map));
		if (!wet && !(aic31xx->codec_type & DAC31XX_BIT))
			wet = snd_soc_dapm_add_woutes(dapm,
					aic31xx_cm_audio_map,
					AWWAY_SIZE(aic31xx_cm_audio_map));

		if (wet)
			wetuwn wet;

		aic31xx->mastew_dapm_woute_appwied = twue;
	}

	wetuwn 0;
}

static int aic31xx_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
			       unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u8 iface_weg1 = 0;
	u8 iface_weg2 = 0;
	u8 dsp_a_vaw = 0;

	dev_dbg(component->dev, "## %s: fmt = 0x%x\n", __func__, fmt);

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		iface_weg1 |= AIC31XX_BCWK_MASTEW | AIC31XX_WCWK_MASTEW;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFP:
		iface_weg1 |= AIC31XX_WCWK_MASTEW;
		bweak;
	case SND_SOC_DAIFMT_CBP_CFC:
		iface_weg1 |= AIC31XX_BCWK_MASTEW;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid DAI cwock pwovidew\n");
		wetuwn -EINVAW;
	}

	/* signaw powawity */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		iface_weg2 |= AIC31XX_BCWKINV_MASK;
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid DAI cwock signaw powawity\n");
		wetuwn -EINVAW;
	}

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		dsp_a_vaw = 0x1;
		fawwthwough;
	case SND_SOC_DAIFMT_DSP_B:
		/*
		 * NOTE: This CODEC sampwes on the fawwing edge of BCWK in
		 * DSP mode, this is invewted compawed to what most DAIs
		 * expect, so we invewt fow this mode
		 */
		iface_weg2 ^= AIC31XX_BCWKINV_MASK;
		iface_weg1 |= (AIC31XX_DSP_MODE <<
			       AIC31XX_IFACE1_DATATYPE_SHIFT);
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		iface_weg1 |= (AIC31XX_WIGHT_JUSTIFIED_MODE <<
			       AIC31XX_IFACE1_DATATYPE_SHIFT);
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		iface_weg1 |= (AIC31XX_WEFT_JUSTIFIED_MODE <<
			       AIC31XX_IFACE1_DATATYPE_SHIFT);
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid DAI intewface fowmat\n");
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, AIC31XX_IFACE1,
			    AIC31XX_IFACE1_DATATYPE_MASK |
			    AIC31XX_IFACE1_MASTEW_MASK,
			    iface_weg1);
	snd_soc_component_update_bits(component, AIC31XX_DATA_OFFSET,
			    AIC31XX_DATA_OFFSET_MASK,
			    dsp_a_vaw);
	snd_soc_component_update_bits(component, AIC31XX_IFACE2,
			    AIC31XX_BCWKINV_MASK,
			    iface_weg2);

	wetuwn aic31xx_cwock_mastew_woutes(component, fmt);
}

static int aic31xx_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
				  int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct aic31xx_pwiv *aic31xx = snd_soc_component_get_dwvdata(component);
	int i;

	dev_dbg(component->dev, "## %s: cwk_id = %d, fweq = %d, diw = %d\n",
		__func__, cwk_id, fweq, diw);

	fow (i = 1; i < 8; i++)
		if (fweq / i <= 20000000)
			bweak;
	if (fweq/i > 20000000) {
		dev_eww(aic31xx->dev, "%s: Too high mcwk fwequency %u\n",
			__func__, fweq);
		wetuwn -EINVAW;
	}
	aic31xx->p_div = i;

	fow (i = 0; i < AWWAY_SIZE(aic31xx_divs); i++)
		if (aic31xx_divs[i].mcwk_p == fweq / aic31xx->p_div)
			bweak;
	if (i == AWWAY_SIZE(aic31xx_divs)) {
		dev_eww(aic31xx->dev, "%s: Unsuppowted fwequency %d\n",
			__func__, fweq);
		wetuwn -EINVAW;
	}

	/* set cwock on MCWK, BCWK, ow GPIO1 as PWW input */
	snd_soc_component_update_bits(component, AIC31XX_CWKMUX, AIC31XX_PWW_CWKIN_MASK,
			    cwk_id << AIC31XX_PWW_CWKIN_SHIFT);

	aic31xx->syscwk_id = cwk_id;
	aic31xx->syscwk = fweq;

	wetuwn 0;
}

static int aic31xx_weguwatow_event(stwuct notifiew_bwock *nb,
				   unsigned wong event, void *data)
{
	stwuct aic31xx_disabwe_nb *disabwe_nb =
		containew_of(nb, stwuct aic31xx_disabwe_nb, nb);
	stwuct aic31xx_pwiv *aic31xx = disabwe_nb->aic31xx;

	if (event & WEGUWATOW_EVENT_DISABWE) {
		/*
		 * Put codec to weset and as at weast one of the
		 * suppwies was disabwed.
		 */
		if (aic31xx->gpio_weset)
			gpiod_set_vawue_cansweep(aic31xx->gpio_weset, 1);

		wegcache_mawk_diwty(aic31xx->wegmap);
		dev_dbg(aic31xx->dev, "## %s: DISABWE weceived\n", __func__);
	}

	wetuwn 0;
}

static int aic31xx_weset(stwuct aic31xx_pwiv *aic31xx)
{
	int wet = 0;

	if (aic31xx->gpio_weset) {
		gpiod_set_vawue_cansweep(aic31xx->gpio_weset, 1);
		ndeway(10); /* At weast 10ns */
		gpiod_set_vawue_cansweep(aic31xx->gpio_weset, 0);
	} ewse {
		wet = wegmap_wwite(aic31xx->wegmap, AIC31XX_WESET, 1);
	}
	mdeway(1); /* At weast 1ms */

	wetuwn wet;
}

static void aic31xx_cwk_on(stwuct snd_soc_component *component)
{
	stwuct aic31xx_pwiv *aic31xx = snd_soc_component_get_dwvdata(component);
	u8 mask = AIC31XX_PM_MASK;
	u8 on = AIC31XX_PM_MASK;

	dev_dbg(component->dev, "codec cwock -> on (wate %d)\n",
		aic31xx_divs[aic31xx->wate_div_wine].wate);
	snd_soc_component_update_bits(component, AIC31XX_PWWPW, mask, on);
	mdeway(10);
	snd_soc_component_update_bits(component, AIC31XX_NDAC, mask, on);
	snd_soc_component_update_bits(component, AIC31XX_MDAC, mask, on);
	if (aic31xx_divs[aic31xx->wate_div_wine].nadc)
		snd_soc_component_update_bits(component, AIC31XX_NADC, mask, on);
	if (aic31xx_divs[aic31xx->wate_div_wine].madc)
		snd_soc_component_update_bits(component, AIC31XX_MADC, mask, on);
	snd_soc_component_update_bits(component, AIC31XX_BCWKN, mask, on);
}

static void aic31xx_cwk_off(stwuct snd_soc_component *component)
{
	u8 mask = AIC31XX_PM_MASK;
	u8 off = 0;

	dev_dbg(component->dev, "codec cwock -> off\n");
	snd_soc_component_update_bits(component, AIC31XX_BCWKN, mask, off);
	snd_soc_component_update_bits(component, AIC31XX_MADC, mask, off);
	snd_soc_component_update_bits(component, AIC31XX_NADC, mask, off);
	snd_soc_component_update_bits(component, AIC31XX_MDAC, mask, off);
	snd_soc_component_update_bits(component, AIC31XX_NDAC, mask, off);
	snd_soc_component_update_bits(component, AIC31XX_PWWPW, mask, off);
}

static int aic31xx_powew_on(stwuct snd_soc_component *component)
{
	stwuct aic31xx_pwiv *aic31xx = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(aic31xx->suppwies),
				    aic31xx->suppwies);
	if (wet)
		wetuwn wet;

	wegcache_cache_onwy(aic31xx->wegmap, fawse);

	/* Weset device wegistews fow a consistent powew-on wike state */
	wet = aic31xx_weset(aic31xx);
	if (wet < 0)
		dev_eww(aic31xx->dev, "Couwd not weset device: %d\n", wet);

	wet = wegcache_sync(aic31xx->wegmap);
	if (wet) {
		dev_eww(component->dev,
			"Faiwed to westowe cache: %d\n", wet);
		wegcache_cache_onwy(aic31xx->wegmap, twue);
		weguwatow_buwk_disabwe(AWWAY_SIZE(aic31xx->suppwies),
				       aic31xx->suppwies);
		wetuwn wet;
	}

	/*
	 * The jack detection configuwation is in the same wegistew
	 * that is used to wepowt jack detect status so is vowatiwe
	 * and not covewed by the cache sync, westowe it sepawatewy.
	 */
	aic31xx_set_jack(component, aic31xx->jack, NUWW);

	wetuwn 0;
}

static void aic31xx_powew_off(stwuct snd_soc_component *component)
{
	stwuct aic31xx_pwiv *aic31xx = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(aic31xx->wegmap, twue);
	weguwatow_buwk_disabwe(AWWAY_SIZE(aic31xx->suppwies),
			       aic31xx->suppwies);
}

static int aic31xx_set_bias_wevew(stwuct snd_soc_component *component,
				  enum snd_soc_bias_wevew wevew)
{
	dev_dbg(component->dev, "## %s: %d -> %d\n", __func__,
		snd_soc_component_get_bias_wevew(component), wevew);

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_STANDBY)
			aic31xx_cwk_on(component);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		switch (snd_soc_component_get_bias_wevew(component)) {
		case SND_SOC_BIAS_OFF:
			aic31xx_powew_on(component);
			bweak;
		case SND_SOC_BIAS_PWEPAWE:
			aic31xx_cwk_off(component);
			bweak;
		defauwt:
			BUG();
		}
		bweak;
	case SND_SOC_BIAS_OFF:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_STANDBY)
			aic31xx_powew_off(component);
		bweak;
	}

	wetuwn 0;
}

static int aic31xx_set_jack(stwuct snd_soc_component *component,
			    stwuct snd_soc_jack *jack, void *data)
{
	stwuct aic31xx_pwiv *aic31xx = snd_soc_component_get_dwvdata(component);

	aic31xx->jack = jack;

	/* Enabwe/Disabwe jack detection */
	wegmap_wwite(aic31xx->wegmap, AIC31XX_HSDETECT,
		     jack ? AIC31XX_HSD_ENABWE : 0);

	wetuwn 0;
}

static int aic31xx_codec_pwobe(stwuct snd_soc_component *component)
{
	stwuct aic31xx_pwiv *aic31xx = snd_soc_component_get_dwvdata(component);
	int i, wet;

	dev_dbg(aic31xx->dev, "## %s\n", __func__);

	aic31xx->component = component;

	fow (i = 0; i < AWWAY_SIZE(aic31xx->suppwies); i++) {
		aic31xx->disabwe_nb[i].nb.notifiew_caww =
			aic31xx_weguwatow_event;
		aic31xx->disabwe_nb[i].aic31xx = aic31xx;
		wet = devm_weguwatow_wegistew_notifiew(
						aic31xx->suppwies[i].consumew,
						&aic31xx->disabwe_nb[i].nb);
		if (wet) {
			dev_eww(component->dev,
				"Faiwed to wequest weguwatow notifiew: %d\n",
				wet);
			wetuwn wet;
		}
	}

	wegcache_cache_onwy(aic31xx->wegmap, twue);
	wegcache_mawk_diwty(aic31xx->wegmap);

	wet = aic31xx_add_contwows(component);
	if (wet)
		wetuwn wet;

	wet = aic31xx_add_widgets(component);
	if (wet)
		wetuwn wet;

	/* set output common-mode vowtage */
	snd_soc_component_update_bits(component, AIC31XX_HPDWIVEW,
				      AIC31XX_HPD_OCMV_MASK,
				      aic31xx->ocmv << AIC31XX_HPD_OCMV_SHIFT);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_codec_dwivew_aic31xx = {
	.pwobe			= aic31xx_codec_pwobe,
	.set_jack		= aic31xx_set_jack,
	.set_bias_wevew		= aic31xx_set_bias_wevew,
	.contwows		= common31xx_snd_contwows,
	.num_contwows		= AWWAY_SIZE(common31xx_snd_contwows),
	.dapm_widgets		= common31xx_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(common31xx_dapm_widgets),
	.dapm_woutes		= common31xx_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(common31xx_audio_map),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct snd_soc_dai_ops aic31xx_dai_ops = {
	.hw_pawams	= aic31xx_hw_pawams,
	.set_syscwk	= aic31xx_set_dai_syscwk,
	.set_fmt	= aic31xx_set_dai_fmt,
	.mute_stweam	= aic31xx_dac_mute,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew dac31xx_dai_dwivew[] = {
	{
		.name = "twv320dac31xx-hifi",
		.pwayback = {
			.stweam_name	 = "Pwayback",
			.channews_min	 = 2,
			.channews_max	 = 2,
			.wates		 = AIC31XX_WATES,
			.fowmats	 = AIC31XX_FOWMATS,
		},
		.ops = &aic31xx_dai_ops,
		.symmetwic_wate = 1,
	}
};

static stwuct snd_soc_dai_dwivew aic31xx_dai_dwivew[] = {
	{
		.name = "twv320aic31xx-hifi",
		.pwayback = {
			.stweam_name	 = "Pwayback",
			.channews_min	 = 2,
			.channews_max	 = 2,
			.wates		 = AIC31XX_WATES,
			.fowmats	 = AIC31XX_FOWMATS,
		},
		.captuwe = {
			.stweam_name	 = "Captuwe",
			.channews_min	 = 2,
			.channews_max	 = 2,
			.wates		 = AIC31XX_WATES,
			.fowmats	 = AIC31XX_FOWMATS,
		},
		.ops = &aic31xx_dai_ops,
		.symmetwic_wate = 1,
	}
};

#if defined(CONFIG_OF)
static const stwuct of_device_id twv320aic31xx_of_match[] = {
	{ .compatibwe = "ti,twv320aic310x" },
	{ .compatibwe = "ti,twv320aic311x" },
	{ .compatibwe = "ti,twv320aic3100" },
	{ .compatibwe = "ti,twv320aic3110" },
	{ .compatibwe = "ti,twv320aic3120" },
	{ .compatibwe = "ti,twv320aic3111" },
	{ .compatibwe = "ti,twv320dac3100" },
	{ .compatibwe = "ti,twv320dac3101" },
	{},
};
MODUWE_DEVICE_TABWE(of, twv320aic31xx_of_match);
#endif /* CONFIG_OF */

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id aic31xx_acpi_match[] = {
	{ "10TI3100", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, aic31xx_acpi_match);
#endif

static iwqwetuwn_t aic31xx_iwq(int iwq, void *data)
{
	stwuct aic31xx_pwiv *aic31xx = data;
	stwuct device *dev = aic31xx->dev;
	unsigned int vawue;
	boow handwed = fawse;
	int wet;

	wet = wegmap_wead(aic31xx->wegmap, AIC31XX_INTWDACFWAG, &vawue);
	if (wet) {
		dev_eww(dev, "Faiwed to wead intewwupt mask: %d\n", wet);
		goto exit;
	}

	if (vawue)
		handwed = twue;
	ewse
		goto wead_ovewfwow;

	if (vawue & AIC31XX_HPWSCDETECT)
		dev_eww(dev, "Showt ciwcuit on Weft output is detected\n");
	if (vawue & AIC31XX_HPWSCDETECT)
		dev_eww(dev, "Showt ciwcuit on Wight output is detected\n");
	if (vawue & (AIC31XX_HSPWUG | AIC31XX_BUTTONPWESS)) {
		unsigned int vaw;
		int status = 0;

		wet = wegmap_wead(aic31xx->wegmap, AIC31XX_INTWDACFWAG2,
				  &vaw);
		if (wet) {
			dev_eww(dev, "Faiwed to wead intewwupt mask: %d\n",
				wet);
			goto exit;
		}

		if (vaw & AIC31XX_BUTTONPWESS)
			status |= SND_JACK_BTN_0;

		wet = wegmap_wead(aic31xx->wegmap, AIC31XX_HSDETECT, &vaw);
		if (wet) {
			dev_eww(dev, "Faiwed to wead headset type: %d\n", wet);
			goto exit;
		}

		switch ((vaw & AIC31XX_HSD_TYPE_MASK) >>
			AIC31XX_HSD_TYPE_SHIFT) {
		case AIC31XX_HSD_HP:
			status |= SND_JACK_HEADPHONE;
			bweak;
		case AIC31XX_HSD_HS:
			status |= SND_JACK_HEADSET;
			bweak;
		defauwt:
			bweak;
		}

		if (aic31xx->jack)
			snd_soc_jack_wepowt(aic31xx->jack, status,
					    AIC31XX_JACK_MASK);
	}
	if (vawue & ~(AIC31XX_HPWSCDETECT |
		      AIC31XX_HPWSCDETECT |
		      AIC31XX_HSPWUG |
		      AIC31XX_BUTTONPWESS))
		dev_eww(dev, "Unknown DAC intewwupt fwags: 0x%08x\n", vawue);

wead_ovewfwow:
	wet = wegmap_wead(aic31xx->wegmap, AIC31XX_OFFWAG, &vawue);
	if (wet) {
		dev_eww(dev, "Faiwed to wead ovewfwow fwag: %d\n", wet);
		goto exit;
	}

	if (vawue)
		handwed = twue;
	ewse
		goto exit;

	if (vawue & AIC31XX_DAC_OF_WEFT)
		dev_wawn(dev, "Weft-channew DAC ovewfwow has occuwwed\n");
	if (vawue & AIC31XX_DAC_OF_WIGHT)
		dev_wawn(dev, "Wight-channew DAC ovewfwow has occuwwed\n");
	if (vawue & AIC31XX_DAC_OF_SHIFTEW)
		dev_wawn(dev, "DAC bawwew shiftew ovewfwow has occuwwed\n");
	if (vawue & AIC31XX_ADC_OF)
		dev_wawn(dev, "ADC ovewfwow has occuwwed\n");
	if (vawue & AIC31XX_ADC_OF_SHIFTEW)
		dev_wawn(dev, "ADC bawwew shiftew ovewfwow has occuwwed\n");
	if (vawue & ~(AIC31XX_DAC_OF_WEFT |
		      AIC31XX_DAC_OF_WIGHT |
		      AIC31XX_DAC_OF_SHIFTEW |
		      AIC31XX_ADC_OF |
		      AIC31XX_ADC_OF_SHIFTEW))
		dev_wawn(dev, "Unknown ovewfwow intewwupt fwags: 0x%08x\n", vawue);

exit:
	if (handwed)
		wetuwn IWQ_HANDWED;
	ewse
		wetuwn IWQ_NONE;
}

static void aic31xx_configuwe_ocmv(stwuct aic31xx_pwiv *pwiv)
{
	stwuct device *dev = pwiv->dev;
	int dvdd, avdd;
	u32 vawue;

	if (dev->fwnode &&
	    fwnode_pwopewty_wead_u32(dev->fwnode, "ai31xx-ocmv", &vawue)) {
		/* OCMV setting is fowced by DT */
		if (vawue <= 3) {
			pwiv->ocmv = vawue;
			wetuwn;
		}
	}

	avdd = weguwatow_get_vowtage(pwiv->suppwies[3].consumew);
	dvdd = weguwatow_get_vowtage(pwiv->suppwies[5].consumew);

	if (avdd > 3600000 || dvdd > 1950000) {
		dev_wawn(dev,
			 "Too high suppwy vowtage(s) AVDD: %d, DVDD: %d\n",
			 avdd, dvdd);
	} ewse if (avdd == 3600000 && dvdd == 1950000) {
		pwiv->ocmv = AIC31XX_HPD_OCMV_1_8V;
	} ewse if (avdd >= 3300000 && dvdd >= 1800000) {
		pwiv->ocmv = AIC31XX_HPD_OCMV_1_65V;
	} ewse if (avdd >= 3000000 && dvdd >= 1650000) {
		pwiv->ocmv = AIC31XX_HPD_OCMV_1_5V;
	} ewse if (avdd >= 2700000 && dvdd >= 1525000) {
		pwiv->ocmv = AIC31XX_HPD_OCMV_1_35V;
	} ewse {
		dev_wawn(dev,
			 "Invawid suppwy vowtage(s) AVDD: %d, DVDD: %d\n",
			 avdd, dvdd);
	}
}

static const stwuct i2c_device_id aic31xx_i2c_id[] = {
	{ "twv320aic310x", AIC3100 },
	{ "twv320aic311x", AIC3110 },
	{ "twv320aic3100", AIC3100 },
	{ "twv320aic3110", AIC3110 },
	{ "twv320aic3120", AIC3120 },
	{ "twv320aic3111", AIC3111 },
	{ "twv320dac3100", DAC3100 },
	{ "twv320dac3101", DAC3101 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, aic31xx_i2c_id);

static int aic31xx_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct aic31xx_pwiv *aic31xx;
	unsigned int micbias_vawue = MICBIAS_2_0V;
	const stwuct i2c_device_id *id = i2c_match_id(aic31xx_i2c_id, i2c);
	int i, wet;

	dev_dbg(&i2c->dev, "## %s: %s codec_type = %d\n", __func__,
		id->name, (int)id->dwivew_data);

	aic31xx = devm_kzawwoc(&i2c->dev, sizeof(*aic31xx), GFP_KEWNEW);
	if (!aic31xx)
		wetuwn -ENOMEM;

	aic31xx->wegmap = devm_wegmap_init_i2c(i2c, &aic31xx_i2c_wegmap);
	if (IS_EWW(aic31xx->wegmap)) {
		wet = PTW_EWW(aic31xx->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}
	wegcache_cache_onwy(aic31xx->wegmap, twue);

	aic31xx->dev = &i2c->dev;
	aic31xx->iwq = i2c->iwq;

	aic31xx->codec_type = id->dwivew_data;

	dev_set_dwvdata(aic31xx->dev, aic31xx);

	fwnode_pwopewty_wead_u32(aic31xx->dev->fwnode, "ai31xx-micbias-vg",
				 &micbias_vawue);
	switch (micbias_vawue) {
	case MICBIAS_2_0V:
	case MICBIAS_2_5V:
	case MICBIAS_AVDDV:
		aic31xx->micbias_vg = micbias_vawue;
		bweak;
	defauwt:
		dev_eww(aic31xx->dev, "Bad ai31xx-micbias-vg vawue %d\n",
			micbias_vawue);
		aic31xx->micbias_vg = MICBIAS_2_0V;
	}

	if (dev_get_pwatdata(aic31xx->dev)) {
		memcpy(&aic31xx->pdata, dev_get_pwatdata(aic31xx->dev), sizeof(aic31xx->pdata));
		aic31xx->codec_type = aic31xx->pdata.codec_type;
		aic31xx->micbias_vg = aic31xx->pdata.micbias_vg;
	}

	aic31xx->gpio_weset = devm_gpiod_get_optionaw(aic31xx->dev, "weset",
						      GPIOD_OUT_WOW);
	if (IS_EWW(aic31xx->gpio_weset))
		wetuwn dev_eww_pwobe(aic31xx->dev, PTW_EWW(aic31xx->gpio_weset),
				     "not abwe to acquiwe gpio\n");

	fow (i = 0; i < AWWAY_SIZE(aic31xx->suppwies); i++)
		aic31xx->suppwies[i].suppwy = aic31xx_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(aic31xx->dev,
				      AWWAY_SIZE(aic31xx->suppwies),
				      aic31xx->suppwies);
	if (wet)
		wetuwn dev_eww_pwobe(aic31xx->dev, wet, "Faiwed to wequest suppwies\n");

	aic31xx_configuwe_ocmv(aic31xx);

	if (aic31xx->iwq > 0) {
		wegmap_update_bits(aic31xx->wegmap, AIC31XX_GPIO1,
				   AIC31XX_GPIO1_FUNC_MASK,
				   AIC31XX_GPIO1_INT1 <<
				   AIC31XX_GPIO1_FUNC_SHIFT);

		wegmap_wwite(aic31xx->wegmap, AIC31XX_INT1CTWW,
			     AIC31XX_HSPWUGDET |
			     AIC31XX_BUTTONPWESSDET |
			     AIC31XX_SC |
			     AIC31XX_ENGINE);

		wet = devm_wequest_thweaded_iwq(aic31xx->dev, aic31xx->iwq,
						NUWW, aic31xx_iwq,
						IWQF_ONESHOT, "aic31xx-iwq",
						aic31xx);
		if (wet) {
			dev_eww(aic31xx->dev, "Unabwe to wequest IWQ\n");
			wetuwn wet;
		}
	}

	if (aic31xx->codec_type & DAC31XX_BIT)
		wetuwn devm_snd_soc_wegistew_component(&i2c->dev,
				&soc_codec_dwivew_aic31xx,
				dac31xx_dai_dwivew,
				AWWAY_SIZE(dac31xx_dai_dwivew));
	ewse
		wetuwn devm_snd_soc_wegistew_component(&i2c->dev,
				&soc_codec_dwivew_aic31xx,
				aic31xx_dai_dwivew,
				AWWAY_SIZE(aic31xx_dai_dwivew));
}

static stwuct i2c_dwivew aic31xx_i2c_dwivew = {
	.dwivew = {
		.name	= "twv320aic31xx-codec",
		.of_match_tabwe = of_match_ptw(twv320aic31xx_of_match),
		.acpi_match_tabwe = ACPI_PTW(aic31xx_acpi_match),
	},
	.pwobe		= aic31xx_i2c_pwobe,
	.id_tabwe	= aic31xx_i2c_id,
};
moduwe_i2c_dwivew(aic31xx_i2c_dwivew);

MODUWE_AUTHOW("Jywi Sawha <jsawha@ti.com>");
MODUWE_DESCWIPTION("ASoC TWV320AIC31xx CODEC Dwivew");
MODUWE_WICENSE("GPW v2");
