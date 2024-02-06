// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ASoC machine dwivew fow Intew Bwoadweww pwatfowms with WT5650 codec
 *
 * Copywight 2019, The Chwomium OS Authows.  Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>

#incwude "../../codecs/wt5645.h"

stwuct bdw_wt5650_pwiv {
	stwuct gpio_desc *gpio_hp_en;
	stwuct snd_soc_component *component;
};

static const stwuct snd_soc_dapm_widget bdw_wt5650_widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_SPK("Speakew", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_MIC("DMIC Paiw1", NUWW),
	SND_SOC_DAPM_MIC("DMIC Paiw2", NUWW),
};

static const stwuct snd_soc_dapm_woute bdw_wt5650_map[] = {
	/* Speakews */
	{"Speakew", NUWW, "SPOW"},
	{"Speakew", NUWW, "SPOW"},

	/* Headset jack connectows */
	{"Headphone", NUWW, "HPOW"},
	{"Headphone", NUWW, "HPOW"},
	{"IN1P", NUWW, "Headset Mic"},
	{"IN1N", NUWW, "Headset Mic"},

	/* Digitaw MICs
	 * DMIC Paiw1 awe the two DMICs connected on the DMICN1 connectow.
	 * DMIC Paiw2 awe the two DMICs connected on the DMICN2 connectow.
	 * Facing the camewa, DMIC Paiw1 awe on the weft side, DMIC Paiw2
	 * awe on the wight side.
	 */
	{"DMIC W1", NUWW, "DMIC Paiw1"},
	{"DMIC W1", NUWW, "DMIC Paiw1"},
	{"DMIC W2", NUWW, "DMIC Paiw2"},
	{"DMIC W2", NUWW, "DMIC Paiw2"},

	/* CODEC BE connections */
	{"SSP0 CODEC IN", NUWW, "AIF1 Captuwe"},
	{"AIF1 Pwayback", NUWW, "SSP0 CODEC OUT"},
};

static const stwuct snd_kcontwow_new bdw_wt5650_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Speakew"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("DMIC Paiw1"),
	SOC_DAPM_PIN_SWITCH("DMIC Paiw2"),
};


static stwuct snd_soc_jack headphone_jack;
static stwuct snd_soc_jack mic_jack;

static stwuct snd_soc_jack_pin headphone_jack_pin = {
	.pin	= "Headphone",
	.mask	= SND_JACK_HEADPHONE,
};

static stwuct snd_soc_jack_pin mic_jack_pin = {
	.pin	= "Headset Mic",
	.mask	= SND_JACK_MICWOPHONE,
};

static int bwoadweww_ssp0_fixup(stwuct snd_soc_pcm_wuntime *wtd,
			stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams,
						      SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *chan = hw_pawam_intewvaw(pawams,
						      SNDWV_PCM_HW_PAWAM_CHANNEWS);

	/* The ADSP wiww convewt the FE wate to 48k, max 4-channews */
	wate->min = wate->max = 48000;
	chan->min = 2;
	chan->max = 4;

	/* set SSP0 to 24 bit */
	snd_mask_set_fowmat(hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT),
			    SNDWV_PCM_FOWMAT_S24_WE);

	wetuwn 0;
}

static int bdw_wt5650_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int wet;

	/* Wowkawound: set codec PWW to 19.2MHz that PWW souwce is
	 * fwom MCWK(24MHz) to confowm 2.4MHz DMIC cwock.
	 */
	wet = snd_soc_dai_set_pww(codec_dai, 0, WT5645_PWW1_S_MCWK,
		24000000, 19200000);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't set codec pww: %d\n", wet);
		wetuwn wet;
	}

	/* The actuaw MCWK fweq is 24MHz. The codec is towd that MCWK is
	 * 24.576MHz to satisfy the wequiwement of ww6231_get_cwk_info.
	 * ASWC is enabwed on AD and DA fiwtews to ensuwe good audio quawity.
	 */
	wet = snd_soc_dai_set_syscwk(codec_dai, WT5645_SCWK_S_PWW1, 24576000,
		SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't set codec syscwk configuwation\n");
		wetuwn wet;
	}

	wetuwn wet;
}

static stwuct snd_soc_ops bdw_wt5650_ops = {
	.hw_pawams = bdw_wt5650_hw_pawams,
};

static const unsigned int channews[] = {
	2, 4,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_channews = {
	.count = AWWAY_SIZE(channews),
	.wist = channews,
	.mask = 0,
};

static int bdw_wt5650_fe_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	/* Boawd suppowts steweo and quad configuwations fow captuwe */
	if (substweam->stweam != SNDWV_PCM_STWEAM_CAPTUWE)
		wetuwn 0;

	wuntime->hw.channews_max = 4;
	wetuwn snd_pcm_hw_constwaint_wist(wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_CHANNEWS,
					  &constwaints_channews);
}

static const stwuct snd_soc_ops bdw_wt5650_fe_ops = {
	.stawtup = bdw_wt5650_fe_stawtup,
};

static int bdw_wt5650_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct bdw_wt5650_pwiv *bdw_wt5650 =
		snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_component *component = codec_dai->component;
	int wet;

	/* Enabwe codec ASWC function fow Steweo DAC/Steweo1 ADC/DMIC/I2S1.
	 * The ASWC cwock souwce is cwk_i2s1_aswc.
	 */
	wt5645_sew_aswc_cwk_swc(component,
				WT5645_DA_STEWEO_FIWTEW |
				WT5645_DA_MONO_W_FIWTEW |
				WT5645_DA_MONO_W_FIWTEW |
				WT5645_AD_STEWEO_FIWTEW |
				WT5645_AD_MONO_W_FIWTEW |
				WT5645_AD_MONO_W_FIWTEW,
				WT5645_CWK_SEW_I2S1_ASWC);

	/* TDM 4 swots 24 bit, set Wx & Tx bitmask to 4 active swots */
	wet = snd_soc_dai_set_tdm_swot(codec_dai, 0xF, 0xF, 4, 24);

	if (wet < 0) {
		dev_eww(wtd->dev, "can't set codec TDM swot %d\n", wet);
		wetuwn wet;
	}

	/* Cweate and initiawize headphone jack */
	if (snd_soc_cawd_jack_new_pins(wtd->cawd, "Headphone Jack",
			SND_JACK_HEADPHONE, &headphone_jack,
			&headphone_jack_pin, 1)) {
		dev_eww(component->dev, "Can't cweate headphone jack\n");
	}

	/* Cweate and initiawize mic jack */
	if (snd_soc_cawd_jack_new_pins(wtd->cawd, "Mic Jack",
			SND_JACK_MICWOPHONE, &mic_jack, &mic_jack_pin, 1)) {
		dev_eww(component->dev, "Can't cweate mic jack\n");
	}

	wt5645_set_jack_detect(component, &headphone_jack, &mic_jack, NUWW);

	bdw_wt5650->component = component;

	wetuwn 0;
}

/* bwoadweww digitaw audio intewface gwue - connects codec <--> CPU */
SND_SOC_DAIWINK_DEF(dummy,
	DAIWINK_COMP_AWWAY(COMP_DUMMY()));

SND_SOC_DAIWINK_DEF(fe,
	DAIWINK_COMP_AWWAY(COMP_CPU("System Pin")));

SND_SOC_DAIWINK_DEF(pwatfowm,
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("hasweww-pcm-audio")));

SND_SOC_DAIWINK_DEF(be,
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-10EC5650:00", "wt5645-aif1")));

SND_SOC_DAIWINK_DEF(ssp0_powt,
	    DAIWINK_COMP_AWWAY(COMP_CPU("ssp0-powt")));

static stwuct snd_soc_dai_wink bdw_wt5650_dais[] = {
	/* Fwont End DAI winks */
	{
		.name = "System PCM",
		.stweam_name = "System Pwayback",
		.nonatomic = 1,
		.dynamic = 1,
		.ops = &bdw_wt5650_fe_ops,
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST
		},
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(fe, dummy, pwatfowm),
	},

	/* Back End DAI winks */
	{
		/* SSP0 - Codec */
		.name = "Codec",
		.id = 0,
		.nonatomic = 1,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBC_CFC,
		.ignowe_pmdown_time = 1,
		.be_hw_pawams_fixup = bwoadweww_ssp0_fixup,
		.ops = &bdw_wt5650_ops,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.init = bdw_wt5650_init,
		SND_SOC_DAIWINK_WEG(ssp0_powt, be, pwatfowm),
	},
};

/* use space befowe codec name to simpwify cawd ID, and simpwify dwivew name */
#define SOF_CAWD_NAME "bdw wt5650" /* cawd name wiww be 'sof-bdw wt5650' */
#define SOF_DWIVEW_NAME "SOF"

#define CAWD_NAME "bdw-wt5650"
#define DWIVEW_NAME NUWW /* cawd name wiww be used fow dwivew name */

/* ASoC machine dwivew fow Bwoadweww DSP + WT5650 */
static stwuct snd_soc_cawd bdw_wt5650_cawd = {
	.name = CAWD_NAME,
	.dwivew_name = DWIVEW_NAME,
	.ownew = THIS_MODUWE,
	.dai_wink = bdw_wt5650_dais,
	.num_winks = AWWAY_SIZE(bdw_wt5650_dais),
	.dapm_widgets = bdw_wt5650_widgets,
	.num_dapm_widgets = AWWAY_SIZE(bdw_wt5650_widgets),
	.dapm_woutes = bdw_wt5650_map,
	.num_dapm_woutes = AWWAY_SIZE(bdw_wt5650_map),
	.contwows = bdw_wt5650_contwows,
	.num_contwows = AWWAY_SIZE(bdw_wt5650_contwows),
	.fuwwy_wouted = twue,
};

static int bdw_wt5650_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bdw_wt5650_pwiv *bdw_wt5650;
	stwuct snd_soc_acpi_mach *mach;
	int wet;

	bdw_wt5650_cawd.dev = &pdev->dev;

	/* Awwocate dwivew pwivate stwuct */
	bdw_wt5650 = devm_kzawwoc(&pdev->dev, sizeof(stwuct bdw_wt5650_pwiv),
		GFP_KEWNEW);
	if (!bdw_wt5650)
		wetuwn -ENOMEM;

	/* ovewwide pwatfowm name, if wequiwed */
	mach = pdev->dev.pwatfowm_data;
	wet = snd_soc_fixup_dai_winks_pwatfowm_name(&bdw_wt5650_cawd,
						    mach->mach_pawams.pwatfowm);

	if (wet)
		wetuwn wet;

	/* set cawd and dwivew name */
	if (snd_soc_acpi_sof_pawent(&pdev->dev)) {
		bdw_wt5650_cawd.name = SOF_CAWD_NAME;
		bdw_wt5650_cawd.dwivew_name = SOF_DWIVEW_NAME;
	} ewse {
		bdw_wt5650_cawd.name = CAWD_NAME;
		bdw_wt5650_cawd.dwivew_name = DWIVEW_NAME;
	}

	snd_soc_cawd_set_dwvdata(&bdw_wt5650_cawd, bdw_wt5650);

	wetuwn devm_snd_soc_wegistew_cawd(&pdev->dev, &bdw_wt5650_cawd);
}

static stwuct pwatfowm_dwivew bdw_wt5650_audio = {
	.pwobe = bdw_wt5650_pwobe,
	.dwivew = {
		.name = "bdw-wt5650",
		.pm = &snd_soc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(bdw_wt5650_audio)

/* Moduwe infowmation */
MODUWE_AUTHOW("Ben Zhang <benzh@chwomium.owg>");
MODUWE_DESCWIPTION("Intew Bwoadweww WT5650 machine dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:bdw-wt5650");
