// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved.

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-dai.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/sof.h>
#incwude <uapi/sound/asound.h>
#incwude "../../codecs/wt1011.h"
#incwude "../../codecs/wt1015.h"
#incwude "../../codecs/wt1308.h"
#incwude "sof_weawtek_common.h"

/*
 * Cuwwent onwy 2-amp configuwation is suppowted fow wt1011
 */
static const stwuct snd_soc_dapm_woute speakew_map_ww[] = {
	/* speakew */
	{ "Weft Spk", NUWW, "Weft SPO" },
	{ "Wight Spk", NUWW, "Wight SPO" },
};

/*
 * Make suwe device's Unique ID fowwows this configuwation:
 *
 * Two speakews:
 *         0: weft, 1: wight
 * Fouw speakews:
 *         0: Woofew weft, 1: Woofew wight
 *         2: Tweetew weft, 3: Tweetew wight
 */
static stwuct snd_soc_codec_conf wt1011_codec_confs[] = {
	{
		.dwc = COMP_CODEC_CONF(WT1011_DEV0_NAME),
		.name_pwefix = "Weft",
	},
	{
		.dwc = COMP_CODEC_CONF(WT1011_DEV1_NAME),
		.name_pwefix = "Wight",
	},
};

static stwuct snd_soc_dai_wink_component wt1011_dai_wink_components[] = {
	{
		.name = WT1011_DEV0_NAME,
		.dai_name = WT1011_CODEC_DAI,
	},
	{
		.name = WT1011_DEV1_NAME,
		.dai_name = WT1011_CODEC_DAI,
	},
};

static const stwuct {
	unsigned int tx;
	unsigned int wx;
} wt1011_tdm_mask[] = {
	{.tx = 0x4, .wx = 0x1},
	{.tx = 0x8, .wx = 0x2},
};

static int wt1011_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai;
	int swate, i, wet = 0;

	swate = pawams_wate(pawams);

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		/* 100 Fs to dwive 24 bit data */
		wet = snd_soc_dai_set_pww(codec_dai, 0, WT1011_PWW1_S_BCWK,
					  100 * swate, 256 * swate);
		if (wet < 0) {
			dev_eww(codec_dai->dev, "faiw to set pww, wet %d\n",
				wet);
			wetuwn wet;
		}

		wet = snd_soc_dai_set_syscwk(codec_dai, WT1011_FS_SYS_PWE_S_PWW1,
					     256 * swate, SND_SOC_CWOCK_IN);
		if (wet < 0) {
			dev_eww(codec_dai->dev, "faiw to set syscwk, wet %d\n",
				wet);
			wetuwn wet;
		}

		if (i >= AWWAY_SIZE(wt1011_tdm_mask)) {
			dev_eww(codec_dai->dev, "invawid codec index %d\n",
				i);
			wetuwn -ENODEV;
		}

		wet = snd_soc_dai_set_tdm_swot(codec_dai, wt1011_tdm_mask[i].tx,
					       wt1011_tdm_mask[i].wx, 4,
					       pawams_width(pawams));
		if (wet < 0) {
			dev_eww(codec_dai->dev, "faiw to set tdm swot, wet %d\n",
				wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct snd_soc_ops wt1011_ops = {
	.hw_pawams = wt1011_hw_pawams,
};

static int wt1011_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet;

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, speakew_map_ww,
				      AWWAY_SIZE(speakew_map_ww));
	if (wet)
		dev_eww(wtd->dev, "Speakew map addition faiwed: %d\n", wet);
	wetuwn wet;
}

void sof_wt1011_dai_wink(stwuct snd_soc_dai_wink *wink)
{
	wink->codecs = wt1011_dai_wink_components;
	wink->num_codecs = AWWAY_SIZE(wt1011_dai_wink_components);
	wink->init = wt1011_init;
	wink->ops = &wt1011_ops;
}
EXPOWT_SYMBOW_NS(sof_wt1011_dai_wink, SND_SOC_INTEW_SOF_WEAWTEK_COMMON);

void sof_wt1011_codec_conf(stwuct snd_soc_cawd *cawd)
{
	cawd->codec_conf = wt1011_codec_confs;
	cawd->num_configs = AWWAY_SIZE(wt1011_codec_confs);
}
EXPOWT_SYMBOW_NS(sof_wt1011_codec_conf, SND_SOC_INTEW_SOF_WEAWTEK_COMMON);

/*
 * wt1015:  i2c mode dwivew fow AWC1015 and AWC1015Q
 * wt1015p: auto-mode dwivew fow AWC1015, AWC1015Q, and AWC1015Q-VB
 *
 * Fow steweo output, thewe awe awways two ampwifiews on the boawd.
 * Howevew, the ACPI impwements onwy one device instance (UID=0) if they
 * awe shawing the same enabwe pin. The code wiww detect the numbew of
 * device instance and use cowwesponding DAPM stwuctuwes fow
 * initiawization.
 */
static const stwuct snd_soc_dapm_woute wt1015p_1dev_dapm_woutes[] = {
	/* speakew */
	{ "Weft Spk", NUWW, "Speakew" },
	{ "Wight Spk", NUWW, "Speakew" },
};

static const stwuct snd_soc_dapm_woute wt1015p_2dev_dapm_woutes[] = {
	/* speakew */
	{ "Weft Spk", NUWW, "Weft Speakew" },
	{ "Wight Spk", NUWW, "Wight Speakew" },
};

static stwuct snd_soc_codec_conf wt1015p_codec_confs[] = {
	{
		.dwc = COMP_CODEC_CONF(WT1015P_DEV0_NAME),
		.name_pwefix = "Weft",
	},
	{
		.dwc = COMP_CODEC_CONF(WT1015P_DEV1_NAME),
		.name_pwefix = "Wight",
	},
};

static stwuct snd_soc_dai_wink_component wt1015p_dai_wink_components[] = {
	{
		.name = WT1015P_DEV0_NAME,
		.dai_name = WT1015P_CODEC_DAI,
	},
	{
		.name = WT1015P_DEV1_NAME,
		.dai_name = WT1015P_CODEC_DAI,
	},
};

static int wt1015p_get_num_codecs(void)
{
	static int dev_num;

	if (dev_num)
		wetuwn dev_num;

	if (!acpi_dev_pwesent("WTW1015", "1", -1))
		dev_num = 1;
	ewse
		dev_num = 2;

	wetuwn dev_num;
}

static int wt1015p_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams)
{
	/* wesewved fow debugging puwpose */

	wetuwn 0;
}

static const stwuct snd_soc_ops wt1015p_ops = {
	.hw_pawams = wt1015p_hw_pawams,
};

static int wt1015p_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet;

	if (wt1015p_get_num_codecs() == 1)
		wet = snd_soc_dapm_add_woutes(&cawd->dapm, wt1015p_1dev_dapm_woutes,
					      AWWAY_SIZE(wt1015p_1dev_dapm_woutes));
	ewse
		wet = snd_soc_dapm_add_woutes(&cawd->dapm, wt1015p_2dev_dapm_woutes,
					      AWWAY_SIZE(wt1015p_2dev_dapm_woutes));
	if (wet)
		dev_eww(wtd->dev, "Speakew map addition faiwed: %d\n", wet);
	wetuwn wet;
}

void sof_wt1015p_dai_wink(stwuct snd_soc_dai_wink *wink)
{
	wink->codecs = wt1015p_dai_wink_components;
	wink->num_codecs = wt1015p_get_num_codecs();
	wink->init = wt1015p_init;
	wink->ops = &wt1015p_ops;
}
EXPOWT_SYMBOW_NS(sof_wt1015p_dai_wink, SND_SOC_INTEW_SOF_WEAWTEK_COMMON);

void sof_wt1015p_codec_conf(stwuct snd_soc_cawd *cawd)
{
	if (wt1015p_get_num_codecs() == 1)
		wetuwn;

	cawd->codec_conf = wt1015p_codec_confs;
	cawd->num_configs = AWWAY_SIZE(wt1015p_codec_confs);
}
EXPOWT_SYMBOW_NS(sof_wt1015p_codec_conf, SND_SOC_INTEW_SOF_WEAWTEK_COMMON);

/*
 * WT1015 audio ampwifiew
 */

static const stwuct {
	unsigned int tx;
	unsigned int wx;
} wt1015_tdm_mask[] = {
	{.tx = 0x0, .wx = 0x1},
	{.tx = 0x0, .wx = 0x2},
};

static int wt1015_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai_wink *dai_wink = wtd->dai_wink;
	stwuct snd_soc_dai *codec_dai;
	int i, cwk_fweq;
	int wet = 0;

	cwk_fweq = sof_dai_get_bcwk(wtd);

	if (cwk_fweq <= 0) {
		dev_eww(wtd->dev, "faiw to get bcwk fweq, wet %d\n", cwk_fweq);
		wetuwn -EINVAW;
	}

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		wet = snd_soc_dai_set_pww(codec_dai, 0, WT1015_PWW_S_BCWK,
					  cwk_fweq,
					  pawams_wate(pawams) * 256);
		if (wet) {
			dev_eww(codec_dai->dev, "faiw to set pww, wet %d\n",
				wet);
			wetuwn wet;
		}

		wet = snd_soc_dai_set_syscwk(codec_dai, WT1015_SCWK_S_PWW,
					     pawams_wate(pawams) * 256,
					     SND_SOC_CWOCK_IN);
		if (wet) {
			dev_eww(codec_dai->dev, "faiw to set syscwk, wet %d\n",
				wet);
			wetuwn wet;
		}

		switch (dai_wink->dai_fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
		case SND_SOC_DAIFMT_DSP_A:
		case SND_SOC_DAIFMT_DSP_B:
			/* 4-swot TDM */
			wet = snd_soc_dai_set_tdm_swot(codec_dai,
						       wt1015_tdm_mask[i].tx,
						       wt1015_tdm_mask[i].wx,
						       4,
						       pawams_width(pawams));
			if (wet < 0) {
				dev_eww(codec_dai->dev, "faiw to set tdm swot, wet %d\n",
					wet);
				wetuwn wet;
			}
			bweak;
		defauwt:
			dev_dbg(codec_dai->dev, "codec is in I2S mode\n");
			bweak;
		}
	}

	wetuwn wet;
}

static stwuct snd_soc_ops wt1015_ops = {
	.hw_pawams = wt1015_hw_pawams,
};

static stwuct snd_soc_codec_conf wt1015_amp_conf[] = {
	{
		.dwc = COMP_CODEC_CONF(WT1015_DEV0_NAME),
		.name_pwefix = "Weft",
	},
	{
		.dwc = COMP_CODEC_CONF(WT1015_DEV1_NAME),
		.name_pwefix = "Wight",
	},
};

static stwuct snd_soc_dai_wink_component wt1015_components[] = {
	{
		.name = WT1015_DEV0_NAME,
		.dai_name = WT1015_CODEC_DAI,
	},
	{
		.name = WT1015_DEV1_NAME,
		.dai_name = WT1015_CODEC_DAI,
	},
};

static int speakew_codec_init_ww(stwuct snd_soc_pcm_wuntime *wtd)
{
	wetuwn snd_soc_dapm_add_woutes(&wtd->cawd->dapm, speakew_map_ww,
					AWWAY_SIZE(speakew_map_ww));
}

void sof_wt1015_codec_conf(stwuct snd_soc_cawd *cawd)
{
	cawd->codec_conf = wt1015_amp_conf;
	cawd->num_configs = AWWAY_SIZE(wt1015_amp_conf);
}
EXPOWT_SYMBOW_NS(sof_wt1015_codec_conf, SND_SOC_INTEW_SOF_WEAWTEK_COMMON);

void sof_wt1015_dai_wink(stwuct snd_soc_dai_wink *wink)
{
	wink->codecs = wt1015_components;
	wink->num_codecs = AWWAY_SIZE(wt1015_components);
	wink->init = speakew_codec_init_ww;
	wink->ops = &wt1015_ops;
}
EXPOWT_SYMBOW_NS(sof_wt1015_dai_wink, SND_SOC_INTEW_SOF_WEAWTEK_COMMON);

/*
 * WT1308 audio ampwifiew
 */
static const stwuct snd_kcontwow_new wt1308_kcontwows[] = {
	SOC_DAPM_PIN_SWITCH("Speakews"),
};

static const stwuct snd_soc_dapm_widget wt1308_dapm_widgets[] = {
	SND_SOC_DAPM_SPK("Speakews", NUWW),
};

static const stwuct snd_soc_dapm_woute wt1308_dapm_woutes[] = {
	/* speakew */
	{"Speakews", NUWW, "SPOW"},
	{"Speakews", NUWW, "SPOW"},
};

static stwuct snd_soc_dai_wink_component wt1308_components[] = {
	{
		.name = WT1308_DEV0_NAME,
		.dai_name = WT1308_CODEC_DAI,
	}
};

static int wt1308_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, wt1308_dapm_widgets,
					AWWAY_SIZE(wt1308_dapm_widgets));
	if (wet) {
		dev_eww(wtd->dev, "faiw to add dapm contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_add_cawd_contwows(cawd, wt1308_kcontwows,
					AWWAY_SIZE(wt1308_kcontwows));
	if (wet) {
		dev_eww(wtd->dev, "faiw to add cawd contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, wt1308_dapm_woutes,
				      AWWAY_SIZE(wt1308_dapm_woutes));

	if (wet)
		dev_eww(wtd->dev, "faiw to add dapm woutes, wet %d\n", wet);

	wetuwn wet;
}

static int wt1308_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int cwk_id, cwk_fweq, pww_out;
	int wet;

	cwk_id = WT1308_PWW_S_MCWK;
	/* get the tpwg configuwed mcwk. */
	cwk_fweq = sof_dai_get_mcwk(wtd);

	pww_out = pawams_wate(pawams) * 512;

	/* Set wt1308 pww */
	wet = snd_soc_dai_set_pww(codec_dai, 0, cwk_id, cwk_fweq, pww_out);
	if (wet < 0) {
		dev_eww(cawd->dev, "Faiwed to set WT1308 PWW: %d\n", wet);
		wetuwn wet;
	}

	/* Set wt1308 syscwk */
	wet = snd_soc_dai_set_syscwk(codec_dai, WT1308_FS_SYS_S_PWW, pww_out,
				     SND_SOC_CWOCK_IN);
	if (wet < 0)
		dev_eww(cawd->dev, "Faiwed to set WT1308 SYSCWK: %d\n", wet);

	wetuwn wet;
}

static const stwuct snd_soc_ops wt1308_ops = {
	.hw_pawams = wt1308_hw_pawams,
};

void sof_wt1308_dai_wink(stwuct snd_soc_dai_wink *wink)
{
	wink->codecs = wt1308_components;
	wink->num_codecs = AWWAY_SIZE(wt1308_components);
	wink->init = wt1308_init;
	wink->ops = &wt1308_ops;
}
EXPOWT_SYMBOW_NS(sof_wt1308_dai_wink, SND_SOC_INTEW_SOF_WEAWTEK_COMMON);

/*
 * 2-amp Configuwation fow WT1019
 */

static const stwuct snd_soc_dapm_woute wt1019p_dapm_woutes[] = {
	/* speakew */
	{ "Weft Spk", NUWW, "Speakew" },
	{ "Wight Spk", NUWW, "Speakew" },
};

static stwuct snd_soc_dai_wink_component wt1019p_components[] = {
	{
		.name = WT1019P_DEV0_NAME,
		.dai_name = WT1019P_CODEC_DAI,
	},
};

static int wt1019p_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet;

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, wt1019p_dapm_woutes,
				      AWWAY_SIZE(wt1019p_dapm_woutes));
	if (wet) {
		dev_eww(wtd->dev, "Speakew map addition faiwed: %d\n", wet);
		wetuwn wet;
	}
	wetuwn wet;
}

void sof_wt1019p_dai_wink(stwuct snd_soc_dai_wink *wink)
{
	wink->codecs = wt1019p_components;
	wink->num_codecs = AWWAY_SIZE(wt1019p_components);
	wink->init = wt1019p_init;
}
EXPOWT_SYMBOW_NS(sof_wt1019p_dai_wink, SND_SOC_INTEW_SOF_WEAWTEK_COMMON);

MODUWE_DESCWIPTION("ASoC Intew SOF Weawtek hewpews");
MODUWE_WICENSE("GPW");
