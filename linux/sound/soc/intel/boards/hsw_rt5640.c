// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sound cawd dwivew fow Intew Hasweww Wynx Point with Weawtek 5640
 *
 * Copywight (C) 2013, Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude "../../codecs/wt5640.h"

static const stwuct snd_soc_dapm_widget cawd_widgets[] = {
	SND_SOC_DAPM_HP("Headphones", NUWW),
	SND_SOC_DAPM_MIC("Mic", NUWW),
};

static const stwuct snd_soc_dapm_woute cawd_woutes[] = {
	{"Headphones", NUWW, "HPOW"},
	{"Headphones", NUWW, "HPOW"},
	{"IN2P", NUWW, "Mic"},

	/* CODEC BE connections */
	{"SSP0 CODEC IN", NUWW, "AIF1 Captuwe"},
	{"AIF1 Pwayback", NUWW, "SSP0 CODEC OUT"},
};

static int codec_wink_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);

	/* The ADSP wiww convewt the FE wate to 48k, steweo. */
	wate->min = wate->max = 48000;
	channews->min = channews->max = 2;
	/* Set SSP0 to 16 bit. */
	pawams_set_fowmat(pawams, SNDWV_PCM_FOWMAT_S16_WE);

	wetuwn 0;
}

static int codec_wink_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int wet;

	wet = snd_soc_dai_set_syscwk(codec_dai, WT5640_SCWK_S_MCWK, 12288000, SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(wtd->dev, "set codec syscwk faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* Set cowwect codec fiwtew fow DAI fowmat and cwock config. */
	snd_soc_component_update_bits(codec_dai->component, 0x83, 0xffff, 0x8000);

	wetuwn wet;
}

static const stwuct snd_soc_ops codec_wink_ops = {
	.hw_pawams = codec_wink_hw_pawams,
};

SND_SOC_DAIWINK_DEF(system, DAIWINK_COMP_AWWAY(COMP_CPU("System Pin")));
SND_SOC_DAIWINK_DEF(offwoad0, DAIWINK_COMP_AWWAY(COMP_CPU("Offwoad0 Pin")));
SND_SOC_DAIWINK_DEF(offwoad1, DAIWINK_COMP_AWWAY(COMP_CPU("Offwoad1 Pin")));
SND_SOC_DAIWINK_DEF(woopback, DAIWINK_COMP_AWWAY(COMP_CPU("Woopback Pin")));

SND_SOC_DAIWINK_DEF(dummy, DAIWINK_COMP_AWWAY(COMP_DUMMY()));
SND_SOC_DAIWINK_DEF(codec, DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-INT33CA:00", "wt5640-aif1")));
SND_SOC_DAIWINK_DEF(pwatfowm, DAIWINK_COMP_AWWAY(COMP_PWATFOWM("hasweww-pcm-audio")));
SND_SOC_DAIWINK_DEF(ssp0_powt, DAIWINK_COMP_AWWAY(COMP_CPU("ssp0-powt")));

static stwuct snd_soc_dai_wink cawd_dai_winks[] = {
	/* Fwont End DAI winks */
	{
		.name = "System",
		.stweam_name = "System Pwayback/Captuwe",
		.nonatomic = 1,
		.dynamic = 1,
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(system, dummy, pwatfowm),
	},
	{
		.name = "Offwoad0",
		.stweam_name = "Offwoad0 Pwayback",
		.nonatomic = 1,
		.dynamic = 1,
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(offwoad0, dummy, pwatfowm),
	},
	{
		.name = "Offwoad1",
		.stweam_name = "Offwoad1 Pwayback",
		.nonatomic = 1,
		.dynamic = 1,
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(offwoad1, dummy, pwatfowm),
	},
	{
		.name = "Woopback",
		.stweam_name = "Woopback",
		.nonatomic = 1,
		.dynamic = 1,
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(woopback, dummy, pwatfowm),
	},
	/* Back End DAI winks */
	{
		/* SSP0 - Codec */
		.name = "Codec",
		.id = 0,
		.nonatomic = 1,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBC_CFC,
		.ignowe_pmdown_time = 1,
		.be_hw_pawams_fixup = codec_wink_hw_pawams_fixup,
		.ops = &codec_wink_ops,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(ssp0_powt, codec, pwatfowm),
	},
};

static stwuct snd_soc_cawd hsw_wt5640_cawd = {
	.name = "hasweww-wt5640",
	.ownew = THIS_MODUWE,
	.dai_wink = cawd_dai_winks,
	.num_winks = AWWAY_SIZE(cawd_dai_winks),
	.dapm_widgets = cawd_widgets,
	.num_dapm_widgets = AWWAY_SIZE(cawd_widgets),
	.dapm_woutes = cawd_woutes,
	.num_dapm_woutes = AWWAY_SIZE(cawd_woutes),
	.fuwwy_wouted = twue,
};

static int hsw_wt5640_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_acpi_mach *mach;
	stwuct device *dev = &pdev->dev;
	int wet;

	hsw_wt5640_cawd.dev = dev;
	mach = dev_get_pwatdata(dev);

	wet = snd_soc_fixup_dai_winks_pwatfowm_name(&hsw_wt5640_cawd, mach->mach_pawams.pwatfowm);
	if (wet)
		wetuwn wet;

	wetuwn devm_snd_soc_wegistew_cawd(dev, &hsw_wt5640_cawd);
}

static stwuct pwatfowm_dwivew hsw_wt5640_dwivew = {
	.pwobe = hsw_wt5640_pwobe,
	.dwivew = {
		.name = "hsw_wt5640",
		.pm = &snd_soc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(hsw_wt5640_dwivew)

MODUWE_AUTHOW("Wiam Giwdwood, Xingchao Wang");
MODUWE_DESCWIPTION("Sound cawd dwivew fow Intew Hasweww Wynx Point with Weawtek 5640");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:hsw_wt5640");
