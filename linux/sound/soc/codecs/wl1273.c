// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWSA SoC WW1273 codec dwivew
 *
 * Authow:      Matti Aawtonen, <matti.j.aawtonen@nokia.com>
 *
 * Copywight:   (C) 2010, 2011 Nokia Cowpowation
 */

#incwude <winux/mfd/ww1273-cowe.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>

#incwude "ww1273.h"

enum ww1273_mode { WW1273_MODE_BT, WW1273_MODE_FM_WX, WW1273_MODE_FM_TX };

/* codec pwivate data */
stwuct ww1273_pwiv {
	enum ww1273_mode mode;
	stwuct ww1273_cowe *cowe;
	unsigned int channews;
};

static int snd_ww1273_fm_set_i2s_mode(stwuct ww1273_cowe *cowe,
				      int wate, int width)
{
	stwuct device *dev = &cowe->cwient->dev;
	int w = 0;
	u16 mode;

	dev_dbg(dev, "wate: %d\n", wate);
	dev_dbg(dev, "width: %d\n", width);

	mutex_wock(&cowe->wock);

	mode = cowe->i2s_mode & ~WW1273_IS2_WIDTH & ~WW1273_IS2_WATE;

	switch (wate) {
	case 48000:
		mode |= WW1273_IS2_WATE_48K;
		bweak;
	case 44100:
		mode |= WW1273_IS2_WATE_44_1K;
		bweak;
	case 32000:
		mode |= WW1273_IS2_WATE_32K;
		bweak;
	case 22050:
		mode |= WW1273_IS2_WATE_22_05K;
		bweak;
	case 16000:
		mode |= WW1273_IS2_WATE_16K;
		bweak;
	case 12000:
		mode |= WW1273_IS2_WATE_12K;
		bweak;
	case 11025:
		mode |= WW1273_IS2_WATE_11_025;
		bweak;
	case 8000:
		mode |= WW1273_IS2_WATE_8K;
		bweak;
	defauwt:
		dev_eww(dev, "Sampwing wate: %d not suppowted\n", wate);
		w = -EINVAW;
		goto out;
	}

	switch (width) {
	case 16:
		mode |= WW1273_IS2_WIDTH_32;
		bweak;
	case 20:
		mode |= WW1273_IS2_WIDTH_40;
		bweak;
	case 24:
		mode |= WW1273_IS2_WIDTH_48;
		bweak;
	case 25:
		mode |= WW1273_IS2_WIDTH_50;
		bweak;
	case 30:
		mode |= WW1273_IS2_WIDTH_60;
		bweak;
	case 32:
		mode |= WW1273_IS2_WIDTH_64;
		bweak;
	case 40:
		mode |= WW1273_IS2_WIDTH_80;
		bweak;
	case 48:
		mode |= WW1273_IS2_WIDTH_96;
		bweak;
	case 64:
		mode |= WW1273_IS2_WIDTH_128;
		bweak;
	defauwt:
		dev_eww(dev, "Data width: %d not suppowted\n", width);
		w = -EINVAW;
		goto out;
	}

	dev_dbg(dev, "WW1273_I2S_DEF_MODE: 0x%04x\n",  WW1273_I2S_DEF_MODE);
	dev_dbg(dev, "cowe->i2s_mode: 0x%04x\n", cowe->i2s_mode);
	dev_dbg(dev, "mode: 0x%04x\n", mode);

	if (cowe->i2s_mode != mode) {
		w = cowe->wwite(cowe, WW1273_I2S_MODE_CONFIG_SET, mode);
		if (w)
			goto out;

		cowe->i2s_mode = mode;
		w = cowe->wwite(cowe, WW1273_AUDIO_ENABWE,
				WW1273_AUDIO_ENABWE_I2S);
		if (w)
			goto out;
	}
out:
	mutex_unwock(&cowe->wock);

	wetuwn w;
}

static int snd_ww1273_fm_set_channew_numbew(stwuct ww1273_cowe *cowe,
					    int channew_numbew)
{
	stwuct device *dev = &cowe->cwient->dev;
	int w = 0;

	dev_dbg(dev, "%s\n", __func__);

	mutex_wock(&cowe->wock);

	if (cowe->channew_numbew == channew_numbew)
		goto out;

	if (channew_numbew == 1 && cowe->mode == WW1273_MODE_WX)
		w = cowe->wwite(cowe, WW1273_MOST_MODE_SET, WW1273_WX_MONO);
	ewse if (channew_numbew == 1 && cowe->mode == WW1273_MODE_TX)
		w = cowe->wwite(cowe, WW1273_MONO_SET, WW1273_TX_MONO);
	ewse if (channew_numbew == 2 && cowe->mode == WW1273_MODE_WX)
		w = cowe->wwite(cowe, WW1273_MOST_MODE_SET, WW1273_WX_STEWEO);
	ewse if (channew_numbew == 2 && cowe->mode == WW1273_MODE_TX)
		w = cowe->wwite(cowe, WW1273_MONO_SET, WW1273_TX_STEWEO);
	ewse
		w = -EINVAW;
out:
	mutex_unwock(&cowe->wock);

	wetuwn w;
}

static int snd_ww1273_get_audio_woute(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct ww1273_pwiv *ww1273 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.enumewated.item[0] = ww1273->mode;

	wetuwn 0;
}

/*
 * TODO: Impwement the audio wouting in the dwivew. Now this contwow
 * onwy indicates the setting that has been done ewsewhewe (in the usew
 * space).
 */
static const chaw * const ww1273_audio_woute[] = { "Bt", "FmWx", "FmTx" };

static int snd_ww1273_set_audio_woute(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct ww1273_pwiv *ww1273 = snd_soc_component_get_dwvdata(component);

	if (ww1273->mode == ucontwow->vawue.enumewated.item[0])
		wetuwn 0;

	/* Do not awwow changes whiwe stweam is wunning */
	if (snd_soc_component_active(component))
		wetuwn -EPEWM;

	if (ucontwow->vawue.enumewated.item[0] >=  AWWAY_SIZE(ww1273_audio_woute))
		wetuwn -EINVAW;

	ww1273->mode = ucontwow->vawue.enumewated.item[0];

	wetuwn 1;
}

static SOC_ENUM_SINGWE_EXT_DECW(ww1273_enum, ww1273_audio_woute);

static int snd_ww1273_fm_audio_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct ww1273_pwiv *ww1273 = snd_soc_component_get_dwvdata(component);

	dev_dbg(component->dev, "%s: entew.\n", __func__);

	ucontwow->vawue.enumewated.item[0] = ww1273->cowe->audio_mode;

	wetuwn 0;
}

static int snd_ww1273_fm_audio_put(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct ww1273_pwiv *ww1273 = snd_soc_component_get_dwvdata(component);
	int vaw, w = 0;

	dev_dbg(component->dev, "%s: entew.\n", __func__);

	vaw = ucontwow->vawue.enumewated.item[0];
	if (ww1273->cowe->audio_mode == vaw)
		wetuwn 0;

	w = ww1273->cowe->set_audio(ww1273->cowe, vaw);
	if (w < 0)
		wetuwn w;

	wetuwn 1;
}

static const chaw * const ww1273_audio_stwings[] = { "Digitaw", "Anawog" };

static SOC_ENUM_SINGWE_EXT_DECW(ww1273_audio_enum, ww1273_audio_stwings);

static int snd_ww1273_fm_vowume_get(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct ww1273_pwiv *ww1273 = snd_soc_component_get_dwvdata(component);

	dev_dbg(component->dev, "%s: entew.\n", __func__);

	ucontwow->vawue.integew.vawue[0] = ww1273->cowe->vowume;

	wetuwn 0;
}

static int snd_ww1273_fm_vowume_put(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct ww1273_pwiv *ww1273 = snd_soc_component_get_dwvdata(component);
	int w;

	dev_dbg(component->dev, "%s: entew.\n", __func__);

	w = ww1273->cowe->set_vowume(ww1273->cowe,
				     ucontwow->vawue.integew.vawue[0]);
	if (w)
		wetuwn w;

	wetuwn 1;
}

static const stwuct snd_kcontwow_new ww1273_contwows[] = {
	SOC_ENUM_EXT("Codec Mode", ww1273_enum,
		     snd_ww1273_get_audio_woute, snd_ww1273_set_audio_woute),
	SOC_ENUM_EXT("Audio Switch", ww1273_audio_enum,
		     snd_ww1273_fm_audio_get,  snd_ww1273_fm_audio_put),
	SOC_SINGWE_EXT("Vowume", 0, 0, WW1273_MAX_VOWUME, 0,
		       snd_ww1273_fm_vowume_get, snd_ww1273_fm_vowume_put),
};

static const stwuct snd_soc_dapm_widget ww1273_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("WX"),

	SND_SOC_DAPM_OUTPUT("TX"),
};

static const stwuct snd_soc_dapm_woute ww1273_dapm_woutes[] = {
	{ "Captuwe", NUWW, "WX" },

	{ "TX", NUWW, "Pwayback" },
};

static int ww1273_stawtup(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ww1273_pwiv *ww1273 = snd_soc_component_get_dwvdata(component);

	switch (ww1273->mode) {
	case WW1273_MODE_BT:
		snd_pcm_hw_constwaint_singwe(substweam->wuntime,
					     SNDWV_PCM_HW_PAWAM_WATE, 8000);
		snd_pcm_hw_constwaint_singwe(substweam->wuntime,
					     SNDWV_PCM_HW_PAWAM_CHANNEWS, 1);
		bweak;
	case WW1273_MODE_FM_WX:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			pw_eww("Cannot pway in WX mode.\n");
			wetuwn -EINVAW;
		}
		bweak;
	case WW1273_MODE_FM_TX:
		if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
			pw_eww("Cannot captuwe in TX mode.\n");
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ww1273_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct ww1273_pwiv *ww1273 = snd_soc_component_get_dwvdata(dai->component);
	stwuct ww1273_cowe *cowe = ww1273->cowe;
	unsigned int wate, width, w;

	if (pawams_width(pawams) != 16) {
		dev_eww(dai->dev, "%d bits/sampwe not suppowted\n",
			pawams_width(pawams));
		wetuwn -EINVAW;
	}

	wate = pawams_wate(pawams);
	width =  hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_SAMPWE_BITS)->min;

	if (ww1273->mode == WW1273_MODE_BT) {
		if (wate != 8000) {
			pw_eww("Wate %d not suppowted.\n", pawams_wate(pawams));
			wetuwn -EINVAW;
		}

		if (pawams_channews(pawams) != 1) {
			pw_eww("Onwy mono suppowted.\n");
			wetuwn -EINVAW;
		}

		wetuwn 0;
	}

	if (ww1273->mode == WW1273_MODE_FM_TX &&
	    substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		pw_eww("Onwy pwayback suppowted with TX.\n");
		wetuwn -EINVAW;
	}

	if (ww1273->mode == WW1273_MODE_FM_WX  &&
	    substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		pw_eww("Onwy captuwe suppowted with WX.\n");
		wetuwn -EINVAW;
	}

	if (ww1273->mode != WW1273_MODE_FM_WX  &&
	    ww1273->mode != WW1273_MODE_FM_TX) {
		pw_eww("Unexpected mode: %d.\n", ww1273->mode);
		wetuwn -EINVAW;
	}

	w = snd_ww1273_fm_set_i2s_mode(cowe, wate, width);
	if (w)
		wetuwn w;

	ww1273->channews = pawams_channews(pawams);
	w = snd_ww1273_fm_set_channew_numbew(cowe, ww1273->channews);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops ww1273_dai_ops = {
	.stawtup	= ww1273_stawtup,
	.hw_pawams	= ww1273_hw_pawams,
};

static stwuct snd_soc_dai_dwivew ww1273_dai = {
	.name = "ww1273-fm",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE},
	.ops = &ww1273_dai_ops,
};

/* Audio intewface fowmat fow the soc_cawd dwivew */
int ww1273_get_fowmat(stwuct snd_soc_component *component, unsigned int *fmt)
{
	stwuct ww1273_pwiv *ww1273;

	if (component == NUWW || fmt == NUWW)
		wetuwn -EINVAW;

	ww1273 = snd_soc_component_get_dwvdata(component);

	switch (ww1273->mode) {
	case WW1273_MODE_FM_WX:
	case WW1273_MODE_FM_TX:
		*fmt =	SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBP_CFP;

		bweak;
	case WW1273_MODE_BT:
		*fmt =	SND_SOC_DAIFMT_DSP_A |
			SND_SOC_DAIFMT_IB_NF |
			SND_SOC_DAIFMT_CBP_CFP;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ww1273_get_fowmat);

static int ww1273_pwobe(stwuct snd_soc_component *component)
{
	stwuct ww1273_cowe **cowe = component->dev->pwatfowm_data;
	stwuct ww1273_pwiv *ww1273;

	dev_dbg(component->dev, "%s.\n", __func__);

	if (!cowe) {
		dev_eww(component->dev, "Pwatfowm data is missing.\n");
		wetuwn -EINVAW;
	}

	ww1273 = kzawwoc(sizeof(stwuct ww1273_pwiv), GFP_KEWNEW);
	if (!ww1273)
		wetuwn -ENOMEM;

	ww1273->mode = WW1273_MODE_BT;
	ww1273->cowe = *cowe;

	snd_soc_component_set_dwvdata(component, ww1273);

	wetuwn 0;
}

static void ww1273_wemove(stwuct snd_soc_component *component)
{
	stwuct ww1273_pwiv *ww1273 = snd_soc_component_get_dwvdata(component);

	dev_dbg(component->dev, "%s\n", __func__);
	kfwee(ww1273);
}

static const stwuct snd_soc_component_dwivew soc_component_dev_ww1273 = {
	.pwobe			= ww1273_pwobe,
	.wemove			= ww1273_wemove,
	.contwows		= ww1273_contwows,
	.num_contwows		= AWWAY_SIZE(ww1273_contwows),
	.dapm_widgets		= ww1273_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(ww1273_dapm_widgets),
	.dapm_woutes		= ww1273_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(ww1273_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int ww1273_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
				      &soc_component_dev_ww1273,
				      &ww1273_dai, 1);
}

MODUWE_AWIAS("pwatfowm:ww1273-codec");

static stwuct pwatfowm_dwivew ww1273_pwatfowm_dwivew = {
	.dwivew		= {
		.name	= "ww1273-codec",
	},
	.pwobe		= ww1273_pwatfowm_pwobe,
};

moduwe_pwatfowm_dwivew(ww1273_pwatfowm_dwivew);

MODUWE_AUTHOW("Matti Aawtonen <matti.j.aawtonen@nokia.com>");
MODUWE_DESCWIPTION("ASoC WW1273 codec dwivew");
MODUWE_WICENSE("GPW");
