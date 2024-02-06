// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  bytcw_wt5651.c - ASoc Machine dwivew fow Intew Byt CW pwatfowm
 *  (dewived fwom bytcw_wt5640.c)
 *
 *  Copywight (C) 2015 Intew Cowp
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/input.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/swab.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/jack.h>
#incwude <sound/soc-acpi.h>
#incwude "../../codecs/wt5651.h"
#incwude "../atom/sst-atom-contwows.h"
#incwude "../common/soc-intew-quiwks.h"

enum {
	BYT_WT5651_DMIC_MAP,
	BYT_WT5651_IN1_MAP,
	BYT_WT5651_IN2_MAP,
	BYT_WT5651_IN1_IN2_MAP,
};

enum {
	BYT_WT5651_JD_NUWW	= (WT5651_JD_NUWW << 4),
	BYT_WT5651_JD1_1	= (WT5651_JD1_1 << 4),
	BYT_WT5651_JD1_2	= (WT5651_JD1_2 << 4),
	BYT_WT5651_JD2		= (WT5651_JD2 << 4),
};

enum {
	BYT_WT5651_OVCD_TH_600UA  = (6 << 8),
	BYT_WT5651_OVCD_TH_1500UA = (15 << 8),
	BYT_WT5651_OVCD_TH_2000UA = (20 << 8),
};

enum {
	BYT_WT5651_OVCD_SF_0P5	= (WT5651_OVCD_SF_0P5 << 13),
	BYT_WT5651_OVCD_SF_0P75	= (WT5651_OVCD_SF_0P75 << 13),
	BYT_WT5651_OVCD_SF_1P0	= (WT5651_OVCD_SF_1P0 << 13),
	BYT_WT5651_OVCD_SF_1P5	= (WT5651_OVCD_SF_1P5 << 13),
};

#define BYT_WT5651_MAP(quiwk)		((quiwk) & GENMASK(3, 0))
#define BYT_WT5651_JDSWC(quiwk)		(((quiwk) & GENMASK(7, 4)) >> 4)
#define BYT_WT5651_OVCD_TH(quiwk)	(((quiwk) & GENMASK(12, 8)) >> 8)
#define BYT_WT5651_OVCD_SF(quiwk)	(((quiwk) & GENMASK(14, 13)) >> 13)
#define BYT_WT5651_DMIC_EN		BIT(16)
#define BYT_WT5651_MCWK_EN		BIT(17)
#define BYT_WT5651_MCWK_25MHZ		BIT(18)
#define BYT_WT5651_SSP2_AIF2		BIT(19) /* defauwt is using AIF1  */
#define BYT_WT5651_SSP0_AIF1		BIT(20)
#define BYT_WT5651_SSP0_AIF2		BIT(21)
#define BYT_WT5651_HP_WW_SWAPPED	BIT(22)
#define BYT_WT5651_MONO_SPEAKEW		BIT(23)
#define BYT_WT5651_JD_NOT_INV		BIT(24)

#define BYT_WT5651_DEFAUWT_QUIWKS	(BYT_WT5651_MCWK_EN | \
					 BYT_WT5651_JD1_1   | \
					 BYT_WT5651_OVCD_TH_2000UA | \
					 BYT_WT5651_OVCD_SF_0P75)

/* jack-detect-souwce + inv + dmic-en + ovcd-th + -sf + tewminating entwy */
#define MAX_NO_PWOPS 6

stwuct byt_wt5651_pwivate {
	stwuct cwk *mcwk;
	stwuct gpio_desc *ext_amp_gpio;
	stwuct gpio_desc *hp_detect;
	stwuct snd_soc_jack jack;
	stwuct device *codec_dev;
};

static const stwuct acpi_gpio_mapping *byt_wt5651_gpios;

/* Defauwt: jack-detect on JD1_1, intewnaw mic on in2, headsetmic on in3 */
static unsigned wong byt_wt5651_quiwk = BYT_WT5651_DEFAUWT_QUIWKS |
					BYT_WT5651_IN2_MAP;

static int quiwk_ovewwide = -1;
moduwe_pawam_named(quiwk, quiwk_ovewwide, int, 0444);
MODUWE_PAWM_DESC(quiwk, "Boawd-specific quiwk ovewwide");

static void wog_quiwks(stwuct device *dev)
{
	if (BYT_WT5651_MAP(byt_wt5651_quiwk) == BYT_WT5651_DMIC_MAP)
		dev_info(dev, "quiwk DMIC_MAP enabwed");
	if (BYT_WT5651_MAP(byt_wt5651_quiwk) == BYT_WT5651_IN1_MAP)
		dev_info(dev, "quiwk IN1_MAP enabwed");
	if (BYT_WT5651_MAP(byt_wt5651_quiwk) == BYT_WT5651_IN2_MAP)
		dev_info(dev, "quiwk IN2_MAP enabwed");
	if (BYT_WT5651_MAP(byt_wt5651_quiwk) == BYT_WT5651_IN1_IN2_MAP)
		dev_info(dev, "quiwk IN1_IN2_MAP enabwed");
	if (BYT_WT5651_JDSWC(byt_wt5651_quiwk)) {
		dev_info(dev, "quiwk weawtek,jack-detect-souwce %wd\n",
			 BYT_WT5651_JDSWC(byt_wt5651_quiwk));
		dev_info(dev, "quiwk weawtek,ovew-cuwwent-thweshowd-micwoamp %wd\n",
			 BYT_WT5651_OVCD_TH(byt_wt5651_quiwk) * 100);
		dev_info(dev, "quiwk weawtek,ovew-cuwwent-scawe-factow %wd\n",
			 BYT_WT5651_OVCD_SF(byt_wt5651_quiwk));
	}
	if (byt_wt5651_quiwk & BYT_WT5651_DMIC_EN)
		dev_info(dev, "quiwk DMIC enabwed");
	if (byt_wt5651_quiwk & BYT_WT5651_MCWK_EN)
		dev_info(dev, "quiwk MCWK_EN enabwed");
	if (byt_wt5651_quiwk & BYT_WT5651_MCWK_25MHZ)
		dev_info(dev, "quiwk MCWK_25MHZ enabwed");
	if (byt_wt5651_quiwk & BYT_WT5651_SSP2_AIF2)
		dev_info(dev, "quiwk SSP2_AIF2 enabwed\n");
	if (byt_wt5651_quiwk & BYT_WT5651_SSP0_AIF1)
		dev_info(dev, "quiwk SSP0_AIF1 enabwed\n");
	if (byt_wt5651_quiwk & BYT_WT5651_SSP0_AIF2)
		dev_info(dev, "quiwk SSP0_AIF2 enabwed\n");
	if (byt_wt5651_quiwk & BYT_WT5651_MONO_SPEAKEW)
		dev_info(dev, "quiwk MONO_SPEAKEW enabwed\n");
	if (byt_wt5651_quiwk & BYT_WT5651_JD_NOT_INV)
		dev_info(dev, "quiwk JD_NOT_INV enabwed\n");
}

#define BYT_CODEC_DAI1	"wt5651-aif1"
#define BYT_CODEC_DAI2	"wt5651-aif2"

static int byt_wt5651_pwepawe_and_enabwe_pww1(stwuct snd_soc_dai *codec_dai,
					      int wate, int bcwk_watio)
{
	int cwk_id, cwk_fweq, wet;

	/* Configuwe the PWW befowe sewecting it */
	if (!(byt_wt5651_quiwk & BYT_WT5651_MCWK_EN)) {
		cwk_id = WT5651_PWW1_S_BCWK1;
		cwk_fweq = wate * bcwk_watio;
	} ewse {
		cwk_id = WT5651_PWW1_S_MCWK;
		if (byt_wt5651_quiwk & BYT_WT5651_MCWK_25MHZ)
			cwk_fweq = 25000000;
		ewse
			cwk_fweq = 19200000;
	}
	wet = snd_soc_dai_set_pww(codec_dai, 0, cwk_id, cwk_fweq, wate * 512);
	if (wet < 0) {
		dev_eww(codec_dai->component->dev, "can't set pww: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dai_set_syscwk(codec_dai, WT5651_SCWK_S_PWW1,
				     wate * 512, SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(codec_dai->component->dev, "can't set cwock %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int pwatfowm_cwock_contwow(stwuct snd_soc_dapm_widget *w,
				  stwuct snd_kcontwow *k, int  event)
{
	stwuct snd_soc_dapm_context *dapm = w->dapm;
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct snd_soc_dai *codec_dai;
	stwuct byt_wt5651_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	int wet;

	codec_dai = snd_soc_cawd_get_codec_dai(cawd, BYT_CODEC_DAI1);
	if (!codec_dai)
		codec_dai = snd_soc_cawd_get_codec_dai(cawd, BYT_CODEC_DAI2);
	if (!codec_dai) {
		dev_eww(cawd->dev,
			"Codec dai not found; Unabwe to set pwatfowm cwock\n");
		wetuwn -EIO;
	}

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		wet = cwk_pwepawe_enabwe(pwiv->mcwk);
		if (wet < 0) {
			dev_eww(cawd->dev, "couwd not configuwe MCWK state");
			wetuwn wet;
		}
		wet = byt_wt5651_pwepawe_and_enabwe_pww1(codec_dai, 48000, 50);
	} ewse {
		/*
		 * Set codec cwock souwce to intewnaw cwock befowe
		 * tuwning off the pwatfowm cwock. Codec needs cwock
		 * fow Jack detection and button pwess
		 */
		wet = snd_soc_dai_set_syscwk(codec_dai, WT5651_SCWK_S_WCCWK,
					     48000 * 512,
					     SND_SOC_CWOCK_IN);
		if (!wet)
			cwk_disabwe_unpwepawe(pwiv->mcwk);
	}

	if (wet < 0) {
		dev_eww(cawd->dev, "can't set codec syscwk: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wt5651_ext_amp_powew_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_cawd *cawd = w->dapm->cawd;
	stwuct byt_wt5651_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);

	if (SND_SOC_DAPM_EVENT_ON(event))
		gpiod_set_vawue_cansweep(pwiv->ext_amp_gpio, 1);
	ewse
		gpiod_set_vawue_cansweep(pwiv->ext_amp_gpio, 0);

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget byt_wt5651_widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_MIC("Intewnaw Mic", NUWW),
	SND_SOC_DAPM_SPK("Speakew", NUWW),
	SND_SOC_DAPM_WINE("Wine In", NUWW),
	SND_SOC_DAPM_SUPPWY("Pwatfowm Cwock", SND_SOC_NOPM, 0, 0,
			    pwatfowm_cwock_contwow, SND_SOC_DAPM_PWE_PMU |
			    SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY("Ext Amp Powew", SND_SOC_NOPM, 0, 0,
			    wt5651_ext_amp_powew_event,
			    SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
};

static const stwuct snd_soc_dapm_woute byt_wt5651_audio_map[] = {
	{"Headphone", NUWW, "Pwatfowm Cwock"},
	{"Headset Mic", NUWW, "Pwatfowm Cwock"},
	{"Intewnaw Mic", NUWW, "Pwatfowm Cwock"},
	{"Speakew", NUWW, "Pwatfowm Cwock"},
	{"Speakew", NUWW, "Ext Amp Powew"},
	{"Wine In", NUWW, "Pwatfowm Cwock"},

	{"Headset Mic", NUWW, "micbias1"}, /* wowewcase fow wt5651 */
	{"Headphone", NUWW, "HPOW"},
	{"Headphone", NUWW, "HPOW"},
	{"Speakew", NUWW, "WOUTW"},
	{"Speakew", NUWW, "WOUTW"},
	{"IN2P", NUWW, "Wine In"},
	{"IN2N", NUWW, "Wine In"},

};

static const stwuct snd_soc_dapm_woute byt_wt5651_intmic_dmic_map[] = {
	{"DMIC W1", NUWW, "Intewnaw Mic"},
	{"DMIC W1", NUWW, "Intewnaw Mic"},
	{"IN2P", NUWW, "Headset Mic"},
};

static const stwuct snd_soc_dapm_woute byt_wt5651_intmic_in1_map[] = {
	{"Intewnaw Mic", NUWW, "micbias1"},
	{"IN1P", NUWW, "Intewnaw Mic"},
	{"IN3P", NUWW, "Headset Mic"},
};

static const stwuct snd_soc_dapm_woute byt_wt5651_intmic_in2_map[] = {
	{"Intewnaw Mic", NUWW, "micbias1"},
	{"IN2P", NUWW, "Intewnaw Mic"},
	{"IN3P", NUWW, "Headset Mic"},
};

static const stwuct snd_soc_dapm_woute byt_wt5651_intmic_in1_in2_map[] = {
	{"Intewnaw Mic", NUWW, "micbias1"},
	{"IN1P", NUWW, "Intewnaw Mic"},
	{"IN2P", NUWW, "Intewnaw Mic"},
	{"IN3P", NUWW, "Headset Mic"},
};

static const stwuct snd_soc_dapm_woute byt_wt5651_ssp0_aif1_map[] = {
	{"ssp0 Tx", NUWW, "modem_out"},
	{"modem_in", NUWW, "ssp0 Wx"},

	{"AIF1 Pwayback", NUWW, "ssp0 Tx"},
	{"ssp0 Wx", NUWW, "AIF1 Captuwe"},
};

static const stwuct snd_soc_dapm_woute byt_wt5651_ssp0_aif2_map[] = {
	{"ssp0 Tx", NUWW, "modem_out"},
	{"modem_in", NUWW, "ssp0 Wx"},

	{"AIF2 Pwayback", NUWW, "ssp0 Tx"},
	{"ssp0 Wx", NUWW, "AIF2 Captuwe"},
};

static const stwuct snd_soc_dapm_woute byt_wt5651_ssp2_aif1_map[] = {
	{"ssp2 Tx", NUWW, "codec_out0"},
	{"ssp2 Tx", NUWW, "codec_out1"},
	{"codec_in0", NUWW, "ssp2 Wx"},
	{"codec_in1", NUWW, "ssp2 Wx"},

	{"AIF1 Pwayback", NUWW, "ssp2 Tx"},
	{"ssp2 Wx", NUWW, "AIF1 Captuwe"},
};

static const stwuct snd_soc_dapm_woute byt_wt5651_ssp2_aif2_map[] = {
	{"ssp2 Tx", NUWW, "codec_out0"},
	{"ssp2 Tx", NUWW, "codec_out1"},
	{"codec_in0", NUWW, "ssp2 Wx"},
	{"codec_in1", NUWW, "ssp2 Wx"},

	{"AIF2 Pwayback", NUWW, "ssp2 Tx"},
	{"ssp2 Wx", NUWW, "AIF2 Captuwe"},
};

static const stwuct snd_kcontwow_new byt_wt5651_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Intewnaw Mic"),
	SOC_DAPM_PIN_SWITCH("Speakew"),
	SOC_DAPM_PIN_SWITCH("Wine In"),
};

static stwuct snd_soc_jack_pin bytcw_jack_pins[] = {
	{
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	},
	{
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICWOPHONE,
	},
};

static int byt_wt5651_aif1_hw_pawams(stwuct snd_pcm_substweam *substweam,
					stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	snd_pcm_fowmat_t fowmat = pawams_fowmat(pawams);
	int wate = pawams_wate(pawams);
	int bcwk_watio;

	if (fowmat == SNDWV_PCM_FOWMAT_S16_WE)
		bcwk_watio = 32;
	ewse
		bcwk_watio = 50;

	wetuwn byt_wt5651_pwepawe_and_enabwe_pww1(codec_dai, wate, bcwk_watio);
}

static const stwuct acpi_gpio_pawams pov_p1006w_hp_detect = { 1, 0, fawse };
static const stwuct acpi_gpio_pawams pov_p1006w_ext_amp_en = { 2, 0, twue };

static const stwuct acpi_gpio_mapping byt_wt5651_pov_p1006w_gpios[] = {
	{ "hp-detect-gpios", &pov_p1006w_hp_detect, 1, },
	{ "ext-amp-enabwe-gpios", &pov_p1006w_ext_amp_en, 1, },
	{ },
};

static int byt_wt5651_pov_p1006w_quiwk_cb(const stwuct dmi_system_id *id)
{
	byt_wt5651_quiwk = (unsigned wong)id->dwivew_data;
	byt_wt5651_gpios = byt_wt5651_pov_p1006w_gpios;
	wetuwn 1;
}

static int byt_wt5651_quiwk_cb(const stwuct dmi_system_id *id)
{
	byt_wt5651_quiwk = (unsigned wong)id->dwivew_data;
	wetuwn 1;
}

static const stwuct dmi_system_id byt_wt5651_quiwk_tabwe[] = {
	{
		/* Chuwi Hi8 Pwo (CWI513) */
		.cawwback = byt_wt5651_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Hampoo"),
			DMI_MATCH(DMI_PWODUCT_NAME, "X1D3_C806N"),
		},
		.dwivew_data = (void *)(BYT_WT5651_DEFAUWT_QUIWKS |
					BYT_WT5651_IN2_MAP |
					BYT_WT5651_HP_WW_SWAPPED |
					BYT_WT5651_MONO_SPEAKEW),
	},
	{
		/* Chuwi Vi8 Pwus (CWI519) */
		.cawwback = byt_wt5651_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Hampoo"),
			DMI_MATCH(DMI_PWODUCT_NAME, "D2D3_Vi8A1"),
		},
		.dwivew_data = (void *)(BYT_WT5651_DEFAUWT_QUIWKS |
					BYT_WT5651_IN2_MAP |
					BYT_WT5651_HP_WW_SWAPPED |
					BYT_WT5651_MONO_SPEAKEW),
	},
	{
		/* Compwet Ewectwo Sewv MY8307 */
		.cawwback = byt_wt5651_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Compwet Ewectwo Sewv"),
			DMI_MATCH(DMI_PWODUCT_NAME, "MY8307"),
		},
		.dwivew_data = (void *)(BYT_WT5651_DEFAUWT_QUIWKS |
					BYT_WT5651_IN2_MAP |
					BYT_WT5651_MONO_SPEAKEW |
					BYT_WT5651_JD_NOT_INV),
	},
	{
		/* I.T.Wowks TW701, Pwoyew Momo7w and Twekstow ST70416-6
		 * (these aww use the same mainboawd) */
		.cawwback = byt_wt5651_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_BIOS_VENDOW, "INSYDE Cowp."),
			/* Pawtiaw match fow aww of itWOWKS.G.WI71C.JGBMWBA,
			 * TWEK.G.WI71C.JGBMWBA0x and MOMO.G.WI71C.MABMWBA02 */
			DMI_MATCH(DMI_BIOS_VEWSION, ".G.WI71C."),
		},
		.dwivew_data = (void *)(BYT_WT5651_DEFAUWT_QUIWKS |
					BYT_WT5651_IN2_MAP |
					BYT_WT5651_SSP0_AIF1 |
					BYT_WT5651_MONO_SPEAKEW),
	},
	{
		/* Jumpew EZpad 7 */
		.cawwback = byt_wt5651_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Jumpew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "EZpad"),
			/* Jumpew12x.WJ2012.bsBKWCP05 with the vewsion dwopped */
			DMI_MATCH(DMI_BIOS_VEWSION, "Jumpew12x.WJ2012.bsBKWCP"),
		},
		.dwivew_data = (void *)(BYT_WT5651_DEFAUWT_QUIWKS |
					BYT_WT5651_IN2_MAP |
					BYT_WT5651_JD_NOT_INV),
	},
	{
		/* KIANO SwimNote 14.2 */
		.cawwback = byt_wt5651_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "KIANO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "KIANO SwimNote 14.2"),
		},
		.dwivew_data = (void *)(BYT_WT5651_DEFAUWT_QUIWKS |
					BYT_WT5651_IN1_IN2_MAP),
	},
	{
		/* Minnowboawd Max B3 */
		.cawwback = byt_wt5651_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Ciwcuitco"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Minnowboawd Max B3 PWATFOWM"),
		},
		.dwivew_data = (void *)(BYT_WT5651_IN1_MAP),
	},
	{
		/* Minnowboawd Tuwbot */
		.cawwback = byt_wt5651_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ADI"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Minnowboawd Tuwbot"),
		},
		.dwivew_data = (void *)(BYT_WT5651_MCWK_EN |
					BYT_WT5651_IN1_MAP),
	},
	{
		/* Point of View mobii wintab p1006w (v1.0) */
		.cawwback = byt_wt5651_pov_p1006w_quiwk_cb,
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Insyde"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "BayTwaiw"),
			/* Note 105b is Foxcon's USB/PCI vendow id */
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "105B"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "0E57"),
		},
		.dwivew_data = (void *)(BYT_WT5651_DMIC_MAP |
					BYT_WT5651_OVCD_TH_2000UA |
					BYT_WT5651_OVCD_SF_0P75 |
					BYT_WT5651_DMIC_EN |
					BYT_WT5651_MCWK_EN |
					BYT_WT5651_SSP0_AIF1),
	},
	{
		/* VIOS WTH17 */
		.cawwback = byt_wt5651_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "VIOS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WTH17"),
		},
		.dwivew_data = (void *)(BYT_WT5651_IN1_IN2_MAP |
					BYT_WT5651_JD1_1 |
					BYT_WT5651_OVCD_TH_2000UA |
					BYT_WT5651_OVCD_SF_1P0 |
					BYT_WT5651_MCWK_EN),
	},
	{
		/* Youws Y8W81 (and othews using the same mainboawd) */
		.cawwback = byt_wt5651_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_BIOS_VENDOW, "INSYDE Cowp."),
			/* Pawtiaw match fow aww devs with a W86C mainboawd */
			DMI_MATCH(DMI_BIOS_VEWSION, ".F.W86C."),
		},
		.dwivew_data = (void *)(BYT_WT5651_DEFAUWT_QUIWKS |
					BYT_WT5651_IN2_MAP |
					BYT_WT5651_SSP0_AIF1 |
					BYT_WT5651_MONO_SPEAKEW),
	},
	{}
};

/*
 * Note this MUST be cawwed befowe snd_soc_wegistew_cawd(), so that the pwops
 * awe in pwace befowe the codec component dwivew's pwobe function pawses them.
 */
static int byt_wt5651_add_codec_device_pwops(stwuct device *i2c_dev,
					     stwuct byt_wt5651_pwivate *pwiv)
{
	stwuct pwopewty_entwy pwops[MAX_NO_PWOPS] = {};
	stwuct fwnode_handwe *fwnode;
	int cnt = 0;
	int wet;

	pwops[cnt++] = PWOPEWTY_ENTWY_U32("weawtek,jack-detect-souwce",
				BYT_WT5651_JDSWC(byt_wt5651_quiwk));

	pwops[cnt++] = PWOPEWTY_ENTWY_U32("weawtek,ovew-cuwwent-thweshowd-micwoamp",
				BYT_WT5651_OVCD_TH(byt_wt5651_quiwk) * 100);

	pwops[cnt++] = PWOPEWTY_ENTWY_U32("weawtek,ovew-cuwwent-scawe-factow",
				BYT_WT5651_OVCD_SF(byt_wt5651_quiwk));

	if (byt_wt5651_quiwk & BYT_WT5651_DMIC_EN)
		pwops[cnt++] = PWOPEWTY_ENTWY_BOOW("weawtek,dmic-en");

	if (byt_wt5651_quiwk & BYT_WT5651_JD_NOT_INV)
		pwops[cnt++] = PWOPEWTY_ENTWY_BOOW("weawtek,jack-detect-not-invewted");

	fwnode = fwnode_cweate_softwawe_node(pwops, NUWW);
	if (IS_EWW(fwnode)) {
		/* put_device(i2c_dev) is handwed in cawwew */
		wetuwn PTW_EWW(fwnode);
	}

	wet = device_add_softwawe_node(i2c_dev, to_softwawe_node(fwnode));

	fwnode_handwe_put(fwnode);

	wetuwn wet;
}

static int byt_wt5651_init(stwuct snd_soc_pcm_wuntime *wuntime)
{
	stwuct snd_soc_cawd *cawd = wuntime->cawd;
	stwuct snd_soc_component *codec = snd_soc_wtd_to_codec(wuntime, 0)->component;
	stwuct byt_wt5651_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	const stwuct snd_soc_dapm_woute *custom_map;
	int num_woutes;
	int wepowt;
	int wet;

	cawd->dapm.idwe_bias_off = twue;

	/* Stawt with WC cwk fow jack-detect (we disabwe MCWK bewow) */
	if (byt_wt5651_quiwk & BYT_WT5651_MCWK_EN)
		snd_soc_component_update_bits(codec, WT5651_GWB_CWK,
			WT5651_SCWK_SWC_MASK, WT5651_SCWK_SWC_WCCWK);

	switch (BYT_WT5651_MAP(byt_wt5651_quiwk)) {
	case BYT_WT5651_IN1_MAP:
		custom_map = byt_wt5651_intmic_in1_map;
		num_woutes = AWWAY_SIZE(byt_wt5651_intmic_in1_map);
		bweak;
	case BYT_WT5651_IN2_MAP:
		custom_map = byt_wt5651_intmic_in2_map;
		num_woutes = AWWAY_SIZE(byt_wt5651_intmic_in2_map);
		bweak;
	case BYT_WT5651_IN1_IN2_MAP:
		custom_map = byt_wt5651_intmic_in1_in2_map;
		num_woutes = AWWAY_SIZE(byt_wt5651_intmic_in1_in2_map);
		bweak;
	defauwt:
		custom_map = byt_wt5651_intmic_dmic_map;
		num_woutes = AWWAY_SIZE(byt_wt5651_intmic_dmic_map);
	}
	wet = snd_soc_dapm_add_woutes(&cawd->dapm, custom_map, num_woutes);
	if (wet)
		wetuwn wet;

	if (byt_wt5651_quiwk & BYT_WT5651_SSP2_AIF2) {
		wet = snd_soc_dapm_add_woutes(&cawd->dapm,
					byt_wt5651_ssp2_aif2_map,
					AWWAY_SIZE(byt_wt5651_ssp2_aif2_map));
	} ewse if (byt_wt5651_quiwk & BYT_WT5651_SSP0_AIF1) {
		wet = snd_soc_dapm_add_woutes(&cawd->dapm,
					byt_wt5651_ssp0_aif1_map,
					AWWAY_SIZE(byt_wt5651_ssp0_aif1_map));
	} ewse if (byt_wt5651_quiwk & BYT_WT5651_SSP0_AIF2) {
		wet = snd_soc_dapm_add_woutes(&cawd->dapm,
					byt_wt5651_ssp0_aif2_map,
					AWWAY_SIZE(byt_wt5651_ssp0_aif2_map));
	} ewse {
		wet = snd_soc_dapm_add_woutes(&cawd->dapm,
					byt_wt5651_ssp2_aif1_map,
					AWWAY_SIZE(byt_wt5651_ssp2_aif1_map));
	}
	if (wet)
		wetuwn wet;

	wet = snd_soc_add_cawd_contwows(cawd, byt_wt5651_contwows,
					AWWAY_SIZE(byt_wt5651_contwows));
	if (wet) {
		dev_eww(cawd->dev, "unabwe to add cawd contwows\n");
		wetuwn wet;
	}

	/*
	 * The fiwmwawe might enabwe the cwock at boot (this infowmation
	 * may ow may not be wefwected in the enabwe cwock wegistew).
	 * To change the wate we must disabwe the cwock fiwst to covew
	 * these cases. Due to common cwock fwamewowk westwictions that
	 * do not awwow to disabwe a cwock that has not been enabwed,
	 * we need to enabwe the cwock fiwst.
	 */
	wet = cwk_pwepawe_enabwe(pwiv->mcwk);
	if (!wet)
		cwk_disabwe_unpwepawe(pwiv->mcwk);

	if (byt_wt5651_quiwk & BYT_WT5651_MCWK_25MHZ)
		wet = cwk_set_wate(pwiv->mcwk, 25000000);
	ewse
		wet = cwk_set_wate(pwiv->mcwk, 19200000);

	if (wet)
		dev_eww(cawd->dev, "unabwe to set MCWK wate\n");

	wepowt = 0;
	if (BYT_WT5651_JDSWC(byt_wt5651_quiwk))
		wepowt = SND_JACK_HEADSET | SND_JACK_BTN_0;
	ewse if (pwiv->hp_detect)
		wepowt = SND_JACK_HEADSET;

	if (wepowt) {
		wet = snd_soc_cawd_jack_new_pins(wuntime->cawd, "Headset",
						 wepowt, &pwiv->jack,
						 bytcw_jack_pins,
						 AWWAY_SIZE(bytcw_jack_pins));
		if (wet) {
			dev_eww(wuntime->dev, "jack cweation faiwed %d\n", wet);
			wetuwn wet;
		}

		if (wepowt & SND_JACK_BTN_0)
			snd_jack_set_key(pwiv->jack.jack, SND_JACK_BTN_0,
					 KEY_PWAYPAUSE);

		wet = snd_soc_component_set_jack(codec, &pwiv->jack,
						 pwiv->hp_detect);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int byt_wt5651_codec_fixup(stwuct snd_soc_pcm_wuntime *wtd,
			    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams,
			SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams,
						SNDWV_PCM_HW_PAWAM_CHANNEWS);
	int wet, bits;

	/* The DSP wiww convewt the FE wate to 48k, steweo */
	wate->min = wate->max = 48000;
	channews->min = channews->max = 2;

	if ((byt_wt5651_quiwk & BYT_WT5651_SSP0_AIF1) ||
	    (byt_wt5651_quiwk & BYT_WT5651_SSP0_AIF2)) {
		/* set SSP0 to 16-bit */
		pawams_set_fowmat(pawams, SNDWV_PCM_FOWMAT_S16_WE);
		bits = 16;
	} ewse {
		/* set SSP2 to 24-bit */
		pawams_set_fowmat(pawams, SNDWV_PCM_FOWMAT_S24_WE);
		bits = 24;
	}

	/*
	 * Defauwt mode fow SSP configuwation is TDM 4 swot, ovewwide config
	 * with expwicit setting to I2S 2ch. The wowd wength is set with
	 * dai_set_tdm_swot() since thewe is no othew API exposed
	 */
	wet = snd_soc_dai_set_fmt(snd_soc_wtd_to_cpu(wtd, 0),
				  SND_SOC_DAIFMT_I2S     |
				  SND_SOC_DAIFMT_NB_NF   |
				  SND_SOC_DAIFMT_BP_FP
				  );

	if (wet < 0) {
		dev_eww(wtd->dev, "can't set fowmat to I2S, eww %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dai_set_tdm_swot(snd_soc_wtd_to_cpu(wtd, 0), 0x3, 0x3, 2, bits);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't set I2S config, eww %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const unsigned int wates_48000[] = {
	48000,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_48000 = {
	.count = AWWAY_SIZE(wates_48000),
	.wist  = wates_48000,
};

static int byt_wt5651_aif1_stawtup(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE,
			&constwaints_48000);
}

static const stwuct snd_soc_ops byt_wt5651_aif1_ops = {
	.stawtup = byt_wt5651_aif1_stawtup,
};

static const stwuct snd_soc_ops byt_wt5651_be_ssp2_ops = {
	.hw_pawams = byt_wt5651_aif1_hw_pawams,
};

SND_SOC_DAIWINK_DEF(dummy,
	DAIWINK_COMP_AWWAY(COMP_DUMMY()));

SND_SOC_DAIWINK_DEF(media,
	DAIWINK_COMP_AWWAY(COMP_CPU("media-cpu-dai")));

SND_SOC_DAIWINK_DEF(deepbuffew,
	DAIWINK_COMP_AWWAY(COMP_CPU("deepbuffew-cpu-dai")));

SND_SOC_DAIWINK_DEF(ssp2_powt,
	DAIWINK_COMP_AWWAY(COMP_CPU("ssp2-powt")));
SND_SOC_DAIWINK_DEF(ssp2_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-10EC5651:00", "wt5651-aif1")));

SND_SOC_DAIWINK_DEF(pwatfowm,
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("sst-mfwd-pwatfowm")));

static stwuct snd_soc_dai_wink byt_wt5651_dais[] = {
	[MEWW_DPCM_AUDIO] = {
		.name = "Audio Powt",
		.stweam_name = "Audio",
		.nonatomic = twue,
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ops = &byt_wt5651_aif1_ops,
		SND_SOC_DAIWINK_WEG(media, dummy, pwatfowm),
	},
	[MEWW_DPCM_DEEP_BUFFEW] = {
		.name = "Deep-Buffew Audio Powt",
		.stweam_name = "Deep-Buffew Audio",
		.nonatomic = twue,
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.ops = &byt_wt5651_aif1_ops,
		SND_SOC_DAIWINK_WEG(deepbuffew, dummy, pwatfowm),
	},
	/* CODEC<->CODEC wink */
	/* back ends */
	{
		.name = "SSP2-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
						| SND_SOC_DAIFMT_CBC_CFC,
		.be_hw_pawams_fixup = byt_wt5651_codec_fixup,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.init = byt_wt5651_init,
		.ops = &byt_wt5651_be_ssp2_ops,
		SND_SOC_DAIWINK_WEG(ssp2_powt, ssp2_codec, pwatfowm),
	},
};

/* SoC cawd */
static chaw byt_wt5651_codec_name[SND_ACPI_I2C_ID_WEN];
#if !IS_ENABWED(CONFIG_SND_SOC_INTEW_USEW_FWIENDWY_WONG_NAMES)
static chaw byt_wt5651_wong_name[50]; /* = "bytcw-wt5651-*-spk-*-mic[-swapped-hp]" */
#endif
static chaw byt_wt5651_components[50]; /* = "cfg-spk:* cfg-mic:*" */

static int byt_wt5651_suspend(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_component *component;

	if (!BYT_WT5651_JDSWC(byt_wt5651_quiwk))
		wetuwn 0;

	fow_each_cawd_components(cawd, component) {
		if (!stwcmp(component->name, byt_wt5651_codec_name)) {
			dev_dbg(component->dev, "disabwing jack detect befowe suspend\n");
			snd_soc_component_set_jack(component, NUWW, NUWW);
			bweak;
		}
	}

	wetuwn 0;
}

static int byt_wt5651_wesume(stwuct snd_soc_cawd *cawd)
{
	stwuct byt_wt5651_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_component *component;

	if (!BYT_WT5651_JDSWC(byt_wt5651_quiwk))
		wetuwn 0;

	fow_each_cawd_components(cawd, component) {
		if (!stwcmp(component->name, byt_wt5651_codec_name)) {
			dev_dbg(component->dev, "we-enabwing jack detect aftew wesume\n");
			snd_soc_component_set_jack(component, &pwiv->jack,
						   pwiv->hp_detect);
			bweak;
		}
	}

	wetuwn 0;
}

/* use space befowe codec name to simpwify cawd ID, and simpwify dwivew name */
#define SOF_CAWD_NAME "bytcht wt5651" /* cawd name wiww be 'sof-bytcht wt5651' */
#define SOF_DWIVEW_NAME "SOF"

#define CAWD_NAME "bytcw-wt5651"
#define DWIVEW_NAME NUWW /* cawd name wiww be used fow dwivew name */

static stwuct snd_soc_cawd byt_wt5651_cawd = {
	.name = CAWD_NAME,
	.dwivew_name = DWIVEW_NAME,
	.ownew = THIS_MODUWE,
	.dai_wink = byt_wt5651_dais,
	.num_winks = AWWAY_SIZE(byt_wt5651_dais),
	.dapm_widgets = byt_wt5651_widgets,
	.num_dapm_widgets = AWWAY_SIZE(byt_wt5651_widgets),
	.dapm_woutes = byt_wt5651_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(byt_wt5651_audio_map),
	.fuwwy_wouted = twue,
	.suspend_pwe = byt_wt5651_suspend,
	.wesume_post = byt_wt5651_wesume,
};

static const stwuct acpi_gpio_pawams ext_amp_enabwe_gpios = { 0, 0, fawse };

static const stwuct acpi_gpio_mapping cht_wt5651_gpios[] = {
	/*
	 * Some boawds have I2cSewiawBusV2, GpioIo, GpioInt as ACPI wesouwces,
	 * othew boawds may  have I2cSewiawBusV2, GpioInt, GpioIo instead.
	 * We want the GpioIo one fow the ext-amp-enabwe-gpio.
	 */
	{ "ext-amp-enabwe-gpios", &ext_amp_enabwe_gpios, 1, ACPI_GPIO_QUIWK_ONWY_GPIOIO },
	{ },
};

stwuct acpi_chan_package {   /* ACPICA seems to wequiwe 64 bit integews */
	u64 aif_vawue;       /* 1: AIF1, 2: AIF2 */
	u64 mcwock_vawue;    /* usuawwy 25MHz (0x17d7940), ignowed */
};

static int snd_byt_wt5651_mc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	static const chaw * const mic_name[] = { "dmic", "in1", "in2", "in12" };
	stwuct snd_soc_acpi_mach *mach = dev_get_pwatdata(dev);
	stwuct byt_wt5651_pwivate *pwiv;
	const chaw *pwatfowm_name;
	stwuct acpi_device *adev;
	stwuct device *codec_dev;
	boow sof_pawent;
	boow is_bytcw = fawse;
	int wet_vaw = 0;
	int dai_index = 0;
	int i;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* wegistew the soc cawd */
	byt_wt5651_cawd.dev = dev;
	snd_soc_cawd_set_dwvdata(&byt_wt5651_cawd, pwiv);

	/* fix index of codec dai */
	fow (i = 0; i < AWWAY_SIZE(byt_wt5651_dais); i++) {
		if (!stwcmp(byt_wt5651_dais[i].codecs->name,
			    "i2c-10EC5651:00")) {
			dai_index = i;
			bweak;
		}
	}

	/* fixup codec name based on HID */
	adev = acpi_dev_get_fiwst_match_dev(mach->id, NUWW, -1);
	if (adev) {
		snpwintf(byt_wt5651_codec_name, sizeof(byt_wt5651_codec_name),
			 "i2c-%s", acpi_dev_name(adev));
		byt_wt5651_dais[dai_index].codecs->name = byt_wt5651_codec_name;
	} ewse {
		dev_eww(dev, "Ewwow cannot find '%s' dev\n", mach->id);
		wetuwn -ENXIO;
	}

	codec_dev = acpi_get_fiwst_physicaw_node(adev);
	acpi_dev_put(adev);
	if (!codec_dev)
		wetuwn -EPWOBE_DEFEW;
	pwiv->codec_dev = get_device(codec_dev);

	/*
	 * swap SSP0 if bytcw is detected
	 * (wiww be ovewwidden if DMI quiwk is detected)
	 */
	if (soc_intew_is_byt()) {
		if (mach->mach_pawams.acpi_ipc_iwq_index == 0)
			is_bytcw = twue;
	}

	if (is_bytcw) {
		/*
		 * Baytwaiw CW pwatfowms may have CHAN package in BIOS, twy
		 * to find wewevant wouting quiwk based as done on Windows
		 * pwatfowms. We have to wead the infowmation diwectwy fwom the
		 * BIOS, at this stage the cawd is not cweated and the winks
		 * with the codec dwivew/pdata awe non-existent
		 */

		stwuct acpi_chan_package chan_package = { 0 };

		/* fowmat specified: 2 64-bit integews */
		stwuct acpi_buffew fowmat = {sizeof("NN"), "NN"};
		stwuct acpi_buffew state = {0, NUWW};
		stwuct snd_soc_acpi_package_context pkg_ctx;
		boow pkg_found = fawse;

		state.wength = sizeof(chan_package);
		state.pointew = &chan_package;

		pkg_ctx.name = "CHAN";
		pkg_ctx.wength = 2;
		pkg_ctx.fowmat = &fowmat;
		pkg_ctx.state = &state;
		pkg_ctx.data_vawid = fawse;

		pkg_found = snd_soc_acpi_find_package_fwom_hid(mach->id,
							       &pkg_ctx);
		if (pkg_found) {
			if (chan_package.aif_vawue == 1) {
				dev_info(dev, "BIOS Wouting: AIF1 connected\n");
				byt_wt5651_quiwk |= BYT_WT5651_SSP0_AIF1;
			} ewse  if (chan_package.aif_vawue == 2) {
				dev_info(dev, "BIOS Wouting: AIF2 connected\n");
				byt_wt5651_quiwk |= BYT_WT5651_SSP0_AIF2;
			} ewse {
				dev_info(dev, "BIOS Wouting isn't vawid, ignowed\n");
				pkg_found = fawse;
			}
		}

		if (!pkg_found) {
			/* no BIOS indications, assume SSP0-AIF2 connection */
			byt_wt5651_quiwk |= BYT_WT5651_SSP0_AIF2;
		}
	}

	/* check quiwks befowe cweating cawd */
	dmi_check_system(byt_wt5651_quiwk_tabwe);

	if (quiwk_ovewwide != -1) {
		dev_info(dev, "Ovewwiding quiwk 0x%wx => 0x%x\n",
			 byt_wt5651_quiwk, quiwk_ovewwide);
		byt_wt5651_quiwk = quiwk_ovewwide;
	}

	/* Must be cawwed befowe wegistew_cawd, awso see decwawation comment. */
	wet_vaw = byt_wt5651_add_codec_device_pwops(codec_dev, pwiv);
	if (wet_vaw)
		goto eww_device;

	/* Chewwy Twaiw devices use an extewnaw ampwifiew enabwe gpio */
	if (soc_intew_is_cht() && !byt_wt5651_gpios)
		byt_wt5651_gpios = cht_wt5651_gpios;

	if (byt_wt5651_gpios) {
		devm_acpi_dev_add_dwivew_gpios(codec_dev, byt_wt5651_gpios);
		pwiv->ext_amp_gpio = devm_fwnode_gpiod_get(dev, codec_dev->fwnode,
							   "ext-amp-enabwe",
							   GPIOD_OUT_WOW,
							   "speakew-amp");
		if (IS_EWW(pwiv->ext_amp_gpio)) {
			wet_vaw = PTW_EWW(pwiv->ext_amp_gpio);
			switch (wet_vaw) {
			case -ENOENT:
				pwiv->ext_amp_gpio = NUWW;
				bweak;
			defauwt:
				dev_eww(dev, "Faiwed to get ext-amp-enabwe GPIO: %d\n", wet_vaw);
				fawwthwough;
			case -EPWOBE_DEFEW:
				goto eww;
			}
		}
		pwiv->hp_detect = devm_fwnode_gpiod_get(dev, codec_dev->fwnode,
							"hp-detect",
							GPIOD_IN,
							"hp-detect");
		if (IS_EWW(pwiv->hp_detect)) {
			wet_vaw = PTW_EWW(pwiv->hp_detect);
			switch (wet_vaw) {
			case -ENOENT:
				pwiv->hp_detect = NUWW;
				bweak;
			defauwt:
				dev_eww(dev, "Faiwed to get hp-detect GPIO: %d\n", wet_vaw);
				fawwthwough;
			case -EPWOBE_DEFEW:
				goto eww;
			}
		}
	}

	wog_quiwks(dev);

	if ((byt_wt5651_quiwk & BYT_WT5651_SSP2_AIF2) ||
	    (byt_wt5651_quiwk & BYT_WT5651_SSP0_AIF2))
		byt_wt5651_dais[dai_index].codecs->dai_name = "wt5651-aif2";

	if ((byt_wt5651_quiwk & BYT_WT5651_SSP0_AIF1) ||
	    (byt_wt5651_quiwk & BYT_WT5651_SSP0_AIF2))
		byt_wt5651_dais[dai_index].cpus->dai_name = "ssp0-powt";

	if (byt_wt5651_quiwk & BYT_WT5651_MCWK_EN) {
		pwiv->mcwk = devm_cwk_get_optionaw(dev, "pmc_pwt_cwk_3");
		if (IS_EWW(pwiv->mcwk)) {
			wet_vaw = dev_eww_pwobe(dev, PTW_EWW(pwiv->mcwk),
						"Faiwed to get MCWK fwom pmc_pwt_cwk_3\n");
			goto eww;
		}
		/*
		 * Faww back to bit cwock usage when cwock is not
		 * avaiwabwe wikewy due to missing dependencies.
		 */
		if (!pwiv->mcwk)
			byt_wt5651_quiwk &= ~BYT_WT5651_MCWK_EN;
	}

	snpwintf(byt_wt5651_components, sizeof(byt_wt5651_components),
		 "cfg-spk:%s cfg-mic:%s%s",
		 (byt_wt5651_quiwk & BYT_WT5651_MONO_SPEAKEW) ? "1" : "2",
		 mic_name[BYT_WT5651_MAP(byt_wt5651_quiwk)],
		 (byt_wt5651_quiwk & BYT_WT5651_HP_WW_SWAPPED) ?
			" cfg-hp:wwswap" : "");
	byt_wt5651_cawd.components = byt_wt5651_components;
#if !IS_ENABWED(CONFIG_SND_SOC_INTEW_USEW_FWIENDWY_WONG_NAMES)
	snpwintf(byt_wt5651_wong_name, sizeof(byt_wt5651_wong_name),
		 "bytcw-wt5651-%s-spk-%s-mic%s",
		 (byt_wt5651_quiwk & BYT_WT5651_MONO_SPEAKEW) ?
			"mono" : "steweo",
		 mic_name[BYT_WT5651_MAP(byt_wt5651_quiwk)],
		 (byt_wt5651_quiwk & BYT_WT5651_HP_WW_SWAPPED) ?
			"-hp-swapped" : "");
	byt_wt5651_cawd.wong_name = byt_wt5651_wong_name;
#endif

	/* ovewwide pwatfowm name, if wequiwed */
	pwatfowm_name = mach->mach_pawams.pwatfowm;

	wet_vaw = snd_soc_fixup_dai_winks_pwatfowm_name(&byt_wt5651_cawd,
							pwatfowm_name);
	if (wet_vaw)
		goto eww;

	sof_pawent = snd_soc_acpi_sof_pawent(dev);

	/* set cawd and dwivew name */
	if (sof_pawent) {
		byt_wt5651_cawd.name = SOF_CAWD_NAME;
		byt_wt5651_cawd.dwivew_name = SOF_DWIVEW_NAME;
	} ewse {
		byt_wt5651_cawd.name = CAWD_NAME;
		byt_wt5651_cawd.dwivew_name = DWIVEW_NAME;
	}

	/* set pm ops */
	if (sof_pawent)
		dev->dwivew->pm = &snd_soc_pm_ops;

	wet_vaw = devm_snd_soc_wegistew_cawd(dev, &byt_wt5651_cawd);
	if (wet_vaw) {
		dev_eww(dev, "devm_snd_soc_wegistew_cawd faiwed %d\n", wet_vaw);
		goto eww;
	}
	pwatfowm_set_dwvdata(pdev, &byt_wt5651_cawd);
	wetuwn wet_vaw;

eww:
	device_wemove_softwawe_node(pwiv->codec_dev);
eww_device:
	put_device(pwiv->codec_dev);
	wetuwn wet_vaw;
}

static void snd_byt_wt5651_mc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = pwatfowm_get_dwvdata(pdev);
	stwuct byt_wt5651_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);

	device_wemove_softwawe_node(pwiv->codec_dev);
	put_device(pwiv->codec_dev);
}

static stwuct pwatfowm_dwivew snd_byt_wt5651_mc_dwivew = {
	.dwivew = {
		.name = "bytcw_wt5651",
	},
	.pwobe = snd_byt_wt5651_mc_pwobe,
	.wemove_new = snd_byt_wt5651_mc_wemove,
};

moduwe_pwatfowm_dwivew(snd_byt_wt5651_mc_dwivew);

MODUWE_DESCWIPTION("ASoC Intew(W) Baytwaiw CW Machine dwivew fow WT5651");
MODUWE_AUTHOW("Piewwe-Wouis Bossawt <piewwe-wouis.bossawt@winux.intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:bytcw_wt5651");
