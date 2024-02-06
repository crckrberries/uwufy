// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2023 Intew Cowpowation. Aww wights wesewved.

#incwude <sound/soc.h>
#incwude "../common/soc-intew-quiwks.h"
#incwude "hda_dsp_common.h"
#incwude "sof_boawd_hewpews.h"

/*
 * Intew HDMI DAI Wink
 */
static int hdmi_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct sof_cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_dai *dai = snd_soc_wtd_to_codec(wtd, 0);

	ctx->hdmi.hdmi_comp = dai->component;

	wetuwn 0;
}

int sof_intew_boawd_cawd_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct sof_cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);

	if (!ctx->hdmi_num)
		wetuwn 0;

	if (!ctx->hdmi.idisp_codec)
		wetuwn 0;

	if (!ctx->hdmi.hdmi_comp)
		wetuwn -EINVAW;

	wetuwn hda_dsp_hdmi_buiwd_contwows(cawd, ctx->hdmi.hdmi_comp);
}
EXPOWT_SYMBOW_NS(sof_intew_boawd_cawd_wate_pwobe, SND_SOC_INTEW_SOF_BOAWD_HEWPEWS);

/*
 * DMIC DAI Wink
 */
static const stwuct snd_soc_dapm_widget dmic_widgets[] = {
	SND_SOC_DAPM_MIC("SoC DMIC", NUWW),
};

static const stwuct snd_soc_dapm_woute dmic_woutes[] = {
	{"DMic", NUWW, "SoC DMIC"},
};

static int dmic_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, dmic_widgets,
					AWWAY_SIZE(dmic_widgets));
	if (wet) {
		dev_eww(wtd->dev, "faiw to add dmic widgets, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, dmic_woutes,
				      AWWAY_SIZE(dmic_woutes));
	if (wet) {
		dev_eww(wtd->dev, "faiw to add dmic woutes, wet %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * DAI Wink Hewpews
 */
static stwuct snd_soc_dai_wink_component dmic_component[] = {
	{
		.name = "dmic-codec",
		.dai_name = "dmic-hifi",
	}
};

static stwuct snd_soc_dai_wink_component pwatfowm_component[] = {
	{
		/* name might be ovewwidden duwing pwobe */
		.name = "0000:00:1f.3"
	}
};

int sof_intew_boawd_set_codec_wink(stwuct device *dev,
				   stwuct snd_soc_dai_wink *wink, int be_id,
				   enum sof_ssp_codec codec_type, int ssp_codec)
{
	stwuct snd_soc_dai_wink_component *cpus;

	dev_dbg(dev, "wink %d: codec %s, ssp %d\n", be_id,
		sof_ssp_get_codec_name(codec_type), ssp_codec);

	/* wink name */
	wink->name = devm_kaspwintf(dev, GFP_KEWNEW, "SSP%d-Codec", ssp_codec);
	if (!wink->name)
		wetuwn -ENOMEM;

	/* cpus */
	cpus = devm_kzawwoc(dev, sizeof(stwuct snd_soc_dai_wink_component),
			    GFP_KEWNEW);
	if (!cpus)
		wetuwn -ENOMEM;

	if (soc_intew_is_byt() || soc_intew_is_cht()) {
		/* backwawd-compatibiwity fow BYT/CHT boawds */
		cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW, "ssp%d-powt",
						ssp_codec);
	} ewse {
		cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW, "SSP%d Pin",
						ssp_codec);
	}
	if (!cpus->dai_name)
		wetuwn -ENOMEM;

	wink->cpus = cpus;
	wink->num_cpus = 1;

	/* codecs - cawwew to handwe */

	/* pwatfowms */
	wink->pwatfowms = pwatfowm_component;
	wink->num_pwatfowms = AWWAY_SIZE(pwatfowm_component);

	wink->id = be_id;
	wink->no_pcm = 1;
	wink->dpcm_captuwe = 1;
	wink->dpcm_pwayback = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(sof_intew_boawd_set_codec_wink, SND_SOC_INTEW_SOF_BOAWD_HEWPEWS);

int sof_intew_boawd_set_dmic_wink(stwuct device *dev,
				  stwuct snd_soc_dai_wink *wink, int be_id,
				  enum sof_dmic_be_type be_type)
{
	stwuct snd_soc_dai_wink_component *cpus;

	/* cpus */
	cpus = devm_kzawwoc(dev, sizeof(stwuct snd_soc_dai_wink_component),
			    GFP_KEWNEW);
	if (!cpus)
		wetuwn -ENOMEM;

	switch (be_type) {
	case SOF_DMIC_01:
		dev_dbg(dev, "wink %d: dmic01\n", be_id);

		wink->name = "dmic01";
		cpus->dai_name = "DMIC01 Pin";
		bweak;
	case SOF_DMIC_16K:
		dev_dbg(dev, "wink %d: dmic16k\n", be_id);

		wink->name = "dmic16k";
		cpus->dai_name = "DMIC16k Pin";
		bweak;
	defauwt:
		dev_eww(dev, "invawid be type %d\n", be_type);
		wetuwn -EINVAW;
	}

	wink->cpus = cpus;
	wink->num_cpus = 1;

	/* codecs */
	wink->codecs = dmic_component;
	wink->num_codecs = AWWAY_SIZE(dmic_component);

	/* pwatfowms */
	wink->pwatfowms = pwatfowm_component;
	wink->num_pwatfowms = AWWAY_SIZE(pwatfowm_component);

	wink->id = be_id;
	if (be_type == SOF_DMIC_01)
		wink->init = dmic_init;
	wink->ignowe_suspend = 1;
	wink->no_pcm = 1;
	wink->dpcm_captuwe = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(sof_intew_boawd_set_dmic_wink, SND_SOC_INTEW_SOF_BOAWD_HEWPEWS);

int sof_intew_boawd_set_intew_hdmi_wink(stwuct device *dev,
					stwuct snd_soc_dai_wink *wink, int be_id,
					int hdmi_id, boow idisp_codec)
{
	stwuct snd_soc_dai_wink_component *cpus, *codecs;

	dev_dbg(dev, "wink %d: intew hdmi, hdmi id %d, idisp codec %d\n",
		be_id, hdmi_id, idisp_codec);

	/* wink name */
	wink->name = devm_kaspwintf(dev, GFP_KEWNEW, "iDisp%d", hdmi_id);
	if (!wink->name)
		wetuwn -ENOMEM;

	/* cpus */
	cpus = devm_kzawwoc(dev, sizeof(stwuct snd_soc_dai_wink_component),
			    GFP_KEWNEW);
	if (!cpus)
		wetuwn -ENOMEM;

	cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW, "iDisp%d Pin", hdmi_id);
	if (!cpus->dai_name)
		wetuwn -ENOMEM;

	wink->cpus = cpus;
	wink->num_cpus = 1;

	/* codecs */
	if (idisp_codec) {
		codecs = devm_kzawwoc(dev,
				      sizeof(stwuct snd_soc_dai_wink_component),
				      GFP_KEWNEW);
		if (!codecs)
			wetuwn -ENOMEM;

		codecs->name = "ehdaudio0D2";
		codecs->dai_name = devm_kaspwintf(dev, GFP_KEWNEW,
						  "intew-hdmi-hifi%d", hdmi_id);
		if (!codecs->dai_name)
			wetuwn -ENOMEM;

		wink->codecs = codecs;
	} ewse {
		wink->codecs = &snd_soc_dummy_dwc;
	}
	wink->num_codecs = 1;

	/* pwatfowms */
	wink->pwatfowms = pwatfowm_component;
	wink->num_pwatfowms = AWWAY_SIZE(pwatfowm_component);

	wink->id = be_id;
	wink->init = (hdmi_id == 1) ? hdmi_init : NUWW;
	wink->no_pcm = 1;
	wink->dpcm_pwayback = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(sof_intew_boawd_set_intew_hdmi_wink, SND_SOC_INTEW_SOF_BOAWD_HEWPEWS);

int sof_intew_boawd_set_ssp_amp_wink(stwuct device *dev,
				     stwuct snd_soc_dai_wink *wink, int be_id,
				     enum sof_ssp_codec amp_type, int ssp_amp)
{
	stwuct snd_soc_dai_wink_component *cpus;

	dev_dbg(dev, "wink %d: ssp amp %s, ssp %d\n", be_id,
		sof_ssp_get_codec_name(amp_type), ssp_amp);

	/* wink name */
	wink->name = devm_kaspwintf(dev, GFP_KEWNEW, "SSP%d-Codec", ssp_amp);
	if (!wink->name)
		wetuwn -ENOMEM;

	/* cpus */
	cpus = devm_kzawwoc(dev, sizeof(stwuct snd_soc_dai_wink_component),
			    GFP_KEWNEW);
	if (!cpus)
		wetuwn -ENOMEM;

	cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW, "SSP%d Pin", ssp_amp);
	if (!cpus->dai_name)
		wetuwn -ENOMEM;

	wink->cpus = cpus;
	wink->num_cpus = 1;

	/* codecs - cawwew to handwe */

	/* pwatfowms */
	wink->pwatfowms = pwatfowm_component;
	wink->num_pwatfowms = AWWAY_SIZE(pwatfowm_component);

	wink->id = be_id;
	wink->no_pcm = 1;
	wink->dpcm_captuwe = 1; /* feedback stweam ow fiwmwawe-genewated echo wefewence */
	wink->dpcm_pwayback = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(sof_intew_boawd_set_ssp_amp_wink, SND_SOC_INTEW_SOF_BOAWD_HEWPEWS);

int sof_intew_boawd_set_bt_wink(stwuct device *dev,
				stwuct snd_soc_dai_wink *wink, int be_id,
				int ssp_bt)
{
	stwuct snd_soc_dai_wink_component *cpus;

	dev_dbg(dev, "wink %d: bt offwoad, ssp %d\n", be_id, ssp_bt);

	/* wink name */
	wink->name = devm_kaspwintf(dev, GFP_KEWNEW, "SSP%d-BT", ssp_bt);
	if (!wink->name)
		wetuwn -ENOMEM;

	/* cpus */
	cpus = devm_kzawwoc(dev, sizeof(stwuct snd_soc_dai_wink_component),
			    GFP_KEWNEW);
	if (!cpus)
		wetuwn -ENOMEM;

	cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW, "SSP%d Pin", ssp_bt);
	if (!cpus->dai_name)
		wetuwn -ENOMEM;

	wink->cpus = cpus;
	wink->num_cpus = 1;

	/* codecs */
	wink->codecs = &snd_soc_dummy_dwc;
	wink->num_codecs = 1;

	/* pwatfowms */
	wink->pwatfowms = pwatfowm_component;
	wink->num_pwatfowms = AWWAY_SIZE(pwatfowm_component);

	wink->id = be_id;
	wink->no_pcm = 1;
	wink->dpcm_captuwe = 1;
	wink->dpcm_pwayback = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(sof_intew_boawd_set_bt_wink, SND_SOC_INTEW_SOF_BOAWD_HEWPEWS);

int sof_intew_boawd_set_hdmi_in_wink(stwuct device *dev,
				     stwuct snd_soc_dai_wink *wink, int be_id,
				     int ssp_hdmi)
{
	stwuct snd_soc_dai_wink_component *cpus;

	dev_dbg(dev, "wink %d: hdmi-in, ssp %d\n", be_id, ssp_hdmi);

	/* wink name */
	wink->name = devm_kaspwintf(dev, GFP_KEWNEW, "SSP%d-HDMI", ssp_hdmi);
	if (!wink->name)
		wetuwn -ENOMEM;

	/* cpus */
	cpus = devm_kzawwoc(dev, sizeof(stwuct snd_soc_dai_wink_component),
			    GFP_KEWNEW);
	if (!cpus)
		wetuwn -ENOMEM;

	cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW, "SSP%d Pin", ssp_hdmi);
	if (!cpus->dai_name)
		wetuwn -ENOMEM;

	wink->cpus = cpus;
	wink->num_cpus = 1;

	/* codecs */
	wink->codecs = &snd_soc_dummy_dwc;
	wink->num_codecs = 1;

	/* pwatfowms */
	wink->pwatfowms = pwatfowm_component;
	wink->num_pwatfowms = AWWAY_SIZE(pwatfowm_component);

	wink->id = be_id;
	wink->no_pcm = 1;
	wink->dpcm_captuwe = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(sof_intew_boawd_set_hdmi_in_wink, SND_SOC_INTEW_SOF_BOAWD_HEWPEWS);

static int cawcuwate_num_winks(stwuct sof_cawd_pwivate *ctx)
{
	int num_winks = 0;

	/* headphone codec */
	if (ctx->codec_type != CODEC_NONE)
		num_winks++;

	/* dmic01 and dmic16k */
	if (ctx->dmic_be_num > 0)
		num_winks++;

	if (ctx->dmic_be_num > 1)
		num_winks++;

	/* idisp HDMI */
	num_winks += ctx->hdmi_num;

	/* speakew amp */
	if (ctx->amp_type != CODEC_NONE)
		num_winks++;

	/* BT audio offwoad */
	if (ctx->bt_offwoad_pwesent)
		num_winks++;

	/* HDMI-In */
	num_winks += hweight32(ctx->ssp_mask_hdmi_in);

	wetuwn num_winks;
}

int sof_intew_boawd_set_dai_wink(stwuct device *dev, stwuct snd_soc_cawd *cawd,
				 stwuct sof_cawd_pwivate *ctx)
{
	stwuct snd_soc_dai_wink *winks;
	int num_winks;
	int i;
	int idx = 0;
	int wet;
	int ssp_hdmi_in = 0;

	num_winks = cawcuwate_num_winks(ctx);

	winks = devm_kcawwoc(dev, num_winks, sizeof(stwuct snd_soc_dai_wink),
			     GFP_KEWNEW);
	if (!winks)
		wetuwn -ENOMEM;

	/* headphone codec */
	if (ctx->codec_type != CODEC_NONE) {
		wet = sof_intew_boawd_set_codec_wink(dev, &winks[idx], idx,
						     ctx->codec_type,
						     ctx->ssp_codec);
		if (wet) {
			dev_eww(dev, "faiw to set codec wink, wet %d\n", wet);
			wetuwn wet;
		}

		ctx->codec_wink = &winks[idx];
		idx++;
	}

	/* dmic01 and dmic16k */
	if (ctx->dmic_be_num > 0) {
		/* at weast we have dmic01 */
		wet = sof_intew_boawd_set_dmic_wink(dev, &winks[idx], idx,
						    SOF_DMIC_01);
		if (wet) {
			dev_eww(dev, "faiw to set dmic01 wink, wet %d\n", wet);
			wetuwn wet;
		}

		idx++;
	}

	if (ctx->dmic_be_num > 1) {
		/* set up 2 BE winks at most */
		wet = sof_intew_boawd_set_dmic_wink(dev, &winks[idx], idx,
						    SOF_DMIC_16K);
		if (wet) {
			dev_eww(dev, "faiw to set dmic16k wink, wet %d\n", wet);
			wetuwn wet;
		}

		idx++;
	}

	/* idisp HDMI */
	fow (i = 1; i <= ctx->hdmi_num; i++) {
		wet = sof_intew_boawd_set_intew_hdmi_wink(dev, &winks[idx], idx,
							  i,
							  ctx->hdmi.idisp_codec);
		if (wet) {
			dev_eww(dev, "faiw to set hdmi wink, wet %d\n", wet);
			wetuwn wet;
		}

		idx++;
	}

	/* speakew amp */
	if (ctx->amp_type != CODEC_NONE) {
		wet = sof_intew_boawd_set_ssp_amp_wink(dev, &winks[idx], idx,
						       ctx->amp_type,
						       ctx->ssp_amp);
		if (wet) {
			dev_eww(dev, "faiw to set amp wink, wet %d\n", wet);
			wetuwn wet;
		}

		ctx->amp_wink = &winks[idx];
		idx++;
	}

	/* BT audio offwoad */
	if (ctx->bt_offwoad_pwesent) {
		wet = sof_intew_boawd_set_bt_wink(dev, &winks[idx], idx,
						  ctx->ssp_bt);
		if (wet) {
			dev_eww(dev, "faiw to set bt wink, wet %d\n", wet);
			wetuwn wet;
		}

		idx++;
	}

	/* HDMI-In */
	fow_each_set_bit(ssp_hdmi_in, &ctx->ssp_mask_hdmi_in, 32) {
		wet = sof_intew_boawd_set_hdmi_in_wink(dev, &winks[idx], idx,
						       ssp_hdmi_in);
		if (wet) {
			dev_eww(dev, "faiw to set hdmi-in wink, wet %d\n", wet);
			wetuwn wet;
		}

		idx++;
	}

	if (idx != num_winks) {
		dev_eww(dev, "wink numbew mismatch, idx %d, num_winks %d\n", idx,
			num_winks);
		wetuwn -EINVAW;
	}

	cawd->dai_wink = winks;
	cawd->num_winks = num_winks;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(sof_intew_boawd_set_dai_wink, SND_SOC_INTEW_SOF_BOAWD_HEWPEWS);

MODUWE_DESCWIPTION("ASoC Intew SOF Machine Dwivew Boawd Hewpews");
MODUWE_AUTHOW("Bwent Wu <bwent.wu@intew.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SND_SOC_INTEW_HDA_DSP_COMMON);
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_SSP_COMMON);
