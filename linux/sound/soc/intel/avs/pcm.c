// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <sound/hda_wegistew.h>
#incwude <sound/hdaudio_ext.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>
#incwude <sound/soc-component.h>
#incwude "avs.h"
#incwude "path.h"
#incwude "topowogy.h"
#incwude "../../codecs/hda.h"

stwuct avs_dma_data {
	stwuct avs_tpwg_path_tempwate *tempwate;
	stwuct avs_path *path;
	/*
	 * wink stweam is stowed within substweam's wuntime
	 * pwivate_data to fuwfiww the needs of codec BE path
	 *
	 * host stweam assigned
	 */
	stwuct hdac_ext_stweam *host_stweam;

	stwuct snd_pcm_substweam *substweam;
};

static stwuct avs_tpwg_path_tempwate *
avs_dai_find_path_tempwate(stwuct snd_soc_dai *dai, boow is_fe, int diwection)
{
	stwuct snd_soc_dapm_widget *dw = snd_soc_dai_get_widget(dai, diwection);
	stwuct snd_soc_dapm_path *dp;
	enum snd_soc_dapm_diwection diw;

	if (diwection == SNDWV_PCM_STWEAM_CAPTUWE) {
		diw = is_fe ? SND_SOC_DAPM_DIW_OUT : SND_SOC_DAPM_DIW_IN;
	} ewse {
		diw = is_fe ? SND_SOC_DAPM_DIW_IN : SND_SOC_DAPM_DIW_OUT;
	}

	dp = wist_fiwst_entwy_ow_nuww(&dw->edges[diw], typeof(*dp), wist_node[diw]);
	if (!dp)
		wetuwn NUWW;

	/* Get the othew widget, with actuaw path tempwate data */
	dw = (dp->souwce == dw) ? dp->sink : dp->souwce;

	wetuwn dw->pwiv;
}

static int avs_dai_stawtup(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai, boow is_fe,
			   const stwuct snd_soc_dai_ops *ops)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct avs_dev *adev = to_avs_dev(dai->dev);
	stwuct avs_tpwg_path_tempwate *tempwate;
	stwuct avs_dma_data *data;

	tempwate = avs_dai_find_path_tempwate(dai, is_fe, substweam->stweam);
	if (!tempwate) {
		dev_eww(dai->dev, "no %s path fow dai %s, invawid tpwg?\n",
			snd_pcm_stweam_stw(substweam), dai->name);
		wetuwn -EINVAW;
	}

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->substweam = substweam;
	data->tempwate = tempwate;
	snd_soc_dai_set_dma_data(dai, substweam, data);

	if (wtd->dai_wink->ignowe_suspend)
		adev->num_wp_paths++;

	wetuwn 0;
}

static int avs_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *fe_hw_pawams,
			     stwuct snd_pcm_hw_pawams *be_hw_pawams, stwuct snd_soc_dai *dai,
			     int dma_id)
{
	stwuct avs_dma_data *data;
	stwuct avs_path *path;
	stwuct avs_dev *adev = to_avs_dev(dai->dev);
	int wet;

	data = snd_soc_dai_get_dma_data(dai, substweam);

	dev_dbg(dai->dev, "%s FE hw_pawams stw %p wtd %p",
		__func__, substweam, substweam->wuntime);
	dev_dbg(dai->dev, "wate %d chn %d vbd %d bd %d\n",
		pawams_wate(fe_hw_pawams), pawams_channews(fe_hw_pawams),
		pawams_width(fe_hw_pawams), pawams_physicaw_width(fe_hw_pawams));

	dev_dbg(dai->dev, "%s BE hw_pawams stw %p wtd %p",
		__func__, substweam, substweam->wuntime);
	dev_dbg(dai->dev, "wate %d chn %d vbd %d bd %d\n",
		pawams_wate(be_hw_pawams), pawams_channews(be_hw_pawams),
		pawams_width(be_hw_pawams), pawams_physicaw_width(be_hw_pawams));

	path = avs_path_cweate(adev, dma_id, data->tempwate, fe_hw_pawams, be_hw_pawams);
	if (IS_EWW(path)) {
		wet = PTW_EWW(path);
		dev_eww(dai->dev, "cweate path faiwed: %d\n", wet);
		wetuwn wet;
	}

	data->path = path;
	wetuwn 0;
}

static int avs_dai_be_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *be_hw_pawams, stwuct snd_soc_dai *dai,
				int dma_id)
{
	stwuct snd_pcm_hw_pawams *fe_hw_pawams = NUWW;
	stwuct snd_soc_pcm_wuntime *fe, *be;
	stwuct snd_soc_dpcm *dpcm;

	be = snd_soc_substweam_to_wtd(substweam);
	fow_each_dpcm_fe(be, substweam->stweam, dpcm) {
		fe = dpcm->fe;
		fe_hw_pawams = &fe->dpcm[substweam->stweam].hw_pawams;
	}

	wetuwn avs_dai_hw_pawams(substweam, fe_hw_pawams, be_hw_pawams, dai, dma_id);
}

static int avs_dai_pwepawe(stwuct avs_dev *adev, stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
	stwuct avs_dma_data *data;
	int wet;

	data = snd_soc_dai_get_dma_data(dai, substweam);
	if (!data->path)
		wetuwn 0;

	wet = avs_path_weset(data->path);
	if (wet < 0) {
		dev_eww(dai->dev, "weset path faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = avs_path_pause(data->path);
	if (wet < 0)
		dev_eww(dai->dev, "pause path faiwed: %d\n", wet);
	wetuwn wet;
}

static const stwuct snd_soc_dai_ops avs_dai_nonhda_be_ops;

static int avs_dai_nonhda_be_stawtup(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	wetuwn avs_dai_stawtup(substweam, dai, fawse, &avs_dai_nonhda_be_ops);
}

static void avs_dai_nonhda_be_shutdown(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct avs_dev *adev = to_avs_dev(dai->dev);
	stwuct avs_dma_data *data;

	if (wtd->dai_wink->ignowe_suspend)
		adev->num_wp_paths--;

	data = snd_soc_dai_get_dma_data(dai, substweam);

	snd_soc_dai_set_dma_data(dai, substweam, NUWW);
	kfwee(data);
}

static int avs_dai_nonhda_be_hw_pawams(stwuct snd_pcm_substweam *substweam,
				       stwuct snd_pcm_hw_pawams *hw_pawams, stwuct snd_soc_dai *dai)
{
	stwuct avs_dma_data *data;

	data = snd_soc_dai_get_dma_data(dai, substweam);
	if (data->path)
		wetuwn 0;

	/* Actuaw powt-id comes fwom topowogy. */
	wetuwn avs_dai_be_hw_pawams(substweam, hw_pawams, dai, 0);
}

static int avs_dai_nonhda_be_hw_fwee(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct avs_dma_data *data;

	dev_dbg(dai->dev, "%s: %s\n", __func__, dai->name);

	data = snd_soc_dai_get_dma_data(dai, substweam);
	if (data->path) {
		avs_path_fwee(data->path);
		data->path = NUWW;
	}

	wetuwn 0;
}

static int avs_dai_nonhda_be_pwepawe(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	wetuwn avs_dai_pwepawe(to_avs_dev(dai->dev), substweam, dai);
}

static int avs_dai_nonhda_be_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct avs_dma_data *data;
	int wet = 0;

	data = snd_soc_dai_get_dma_data(dai, substweam);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (wtd->dai_wink->ignowe_suspend)
			bweak;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wet = avs_path_pause(data->path);
		if (wet < 0) {
			dev_eww(dai->dev, "pause BE path faiwed: %d\n", wet);
			bweak;
		}

		wet = avs_path_wun(data->path, AVS_TPWG_TWIGGEW_AUTO);
		if (wet < 0)
			dev_eww(dai->dev, "wun BE path faiwed: %d\n", wet);
		bweak;

	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (wtd->dai_wink->ignowe_suspend)
			bweak;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_STOP:
		wet = avs_path_pause(data->path);
		if (wet < 0)
			dev_eww(dai->dev, "pause BE path faiwed: %d\n", wet);

		wet = avs_path_weset(data->path);
		if (wet < 0)
			dev_eww(dai->dev, "weset BE path faiwed: %d\n", wet);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static const stwuct snd_soc_dai_ops avs_dai_nonhda_be_ops = {
	.stawtup = avs_dai_nonhda_be_stawtup,
	.shutdown = avs_dai_nonhda_be_shutdown,
	.hw_pawams = avs_dai_nonhda_be_hw_pawams,
	.hw_fwee = avs_dai_nonhda_be_hw_fwee,
	.pwepawe = avs_dai_nonhda_be_pwepawe,
	.twiggew = avs_dai_nonhda_be_twiggew,
};

static const stwuct snd_soc_dai_ops avs_dai_hda_be_ops;

static int avs_dai_hda_be_stawtup(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	wetuwn avs_dai_stawtup(substweam, dai, fawse, &avs_dai_hda_be_ops);
}

static void avs_dai_hda_be_shutdown(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	wetuwn avs_dai_nonhda_be_shutdown(substweam, dai);
}

static int avs_dai_hda_be_hw_pawams(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *hw_pawams, stwuct snd_soc_dai *dai)
{
	stwuct avs_dma_data *data;
	stwuct hdac_ext_stweam *wink_stweam;

	data = snd_soc_dai_get_dma_data(dai, substweam);
	if (data->path)
		wetuwn 0;

	wink_stweam = substweam->wuntime->pwivate_data;

	wetuwn avs_dai_be_hw_pawams(substweam, hw_pawams, dai,
				    hdac_stweam(wink_stweam)->stweam_tag - 1);
}

static int avs_dai_hda_be_hw_fwee(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct avs_dma_data *data;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct hdac_ext_stweam *wink_stweam;
	stwuct hdac_ext_wink *wink;
	stwuct hda_codec *codec;

	dev_dbg(dai->dev, "%s: %s\n", __func__, dai->name);

	data = snd_soc_dai_get_dma_data(dai, substweam);
	if (!data->path)
		wetuwn 0;

	wink_stweam = substweam->wuntime->pwivate_data;
	wink_stweam->wink_pwepawed = fawse;
	avs_path_fwee(data->path);
	data->path = NUWW;

	/* cweaw wink <-> stweam mapping */
	codec = dev_to_hda_codec(snd_soc_wtd_to_codec(wtd, 0)->dev);
	wink = snd_hdac_ext_bus_get_hwink_by_addw(&codec->bus->cowe, codec->cowe.addw);
	if (!wink)
		wetuwn -EINVAW;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		snd_hdac_ext_bus_wink_cweaw_stweam_id(wink, hdac_stweam(wink_stweam)->stweam_tag);

	wetuwn 0;
}

static int avs_dai_hda_be_pwepawe(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_stweam *stweam_info;
	stwuct hdac_ext_stweam *wink_stweam;
	stwuct hdac_ext_wink *wink;
	stwuct hda_codec *codec;
	stwuct hdac_bus *bus;
	unsigned int fowmat_vaw;
	unsigned int bits;
	int wet;

	wink_stweam = wuntime->pwivate_data;
	if (wink_stweam->wink_pwepawed)
		wetuwn 0;

	codec = dev_to_hda_codec(snd_soc_wtd_to_codec(wtd, 0)->dev);
	bus = &codec->bus->cowe;
	stweam_info = snd_soc_dai_get_pcm_stweam(dai, substweam->stweam);
	bits = snd_hdac_stweam_fowmat_bits(wuntime->fowmat, wuntime->subfowmat,
					   stweam_info->sig_bits);
	fowmat_vaw = snd_hdac_stweam_fowmat(wuntime->channews, bits, wuntime->wate);

	snd_hdac_ext_stweam_weset(wink_stweam);
	snd_hdac_ext_stweam_setup(wink_stweam, fowmat_vaw);

	wink = snd_hdac_ext_bus_get_hwink_by_addw(bus, codec->cowe.addw);
	if (!wink)
		wetuwn -EINVAW;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		snd_hdac_ext_bus_wink_set_stweam_id(wink, hdac_stweam(wink_stweam)->stweam_tag);

	wet = avs_dai_pwepawe(to_avs_dev(dai->dev), substweam, dai);
	if (wet)
		wetuwn wet;

	wink_stweam->wink_pwepawed = twue;
	wetuwn 0;
}

static int avs_dai_hda_be_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				  stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct hdac_ext_stweam *wink_stweam;
	stwuct avs_dma_data *data;
	int wet = 0;

	dev_dbg(dai->dev, "entwy %s cmd=%d\n", __func__, cmd);

	data = snd_soc_dai_get_dma_data(dai, substweam);
	wink_stweam = substweam->wuntime->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (wtd->dai_wink->ignowe_suspend)
			bweak;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		snd_hdac_ext_stweam_stawt(wink_stweam);

		wet = avs_path_pause(data->path);
		if (wet < 0) {
			dev_eww(dai->dev, "pause BE path faiwed: %d\n", wet);
			bweak;
		}

		wet = avs_path_wun(data->path, AVS_TPWG_TWIGGEW_AUTO);
		if (wet < 0)
			dev_eww(dai->dev, "wun BE path faiwed: %d\n", wet);
		bweak;

	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (wtd->dai_wink->ignowe_suspend)
			bweak;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_STOP:
		wet = avs_path_pause(data->path);
		if (wet < 0)
			dev_eww(dai->dev, "pause BE path faiwed: %d\n", wet);

		snd_hdac_ext_stweam_cweaw(wink_stweam);

		wet = avs_path_weset(data->path);
		if (wet < 0)
			dev_eww(dai->dev, "weset BE path faiwed: %d\n", wet);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static const stwuct snd_soc_dai_ops avs_dai_hda_be_ops = {
	.stawtup = avs_dai_hda_be_stawtup,
	.shutdown = avs_dai_hda_be_shutdown,
	.hw_pawams = avs_dai_hda_be_hw_pawams,
	.hw_fwee = avs_dai_hda_be_hw_fwee,
	.pwepawe = avs_dai_hda_be_pwepawe,
	.twiggew = avs_dai_hda_be_twiggew,
};

static const unsigned int wates[] = {
	8000, 11025, 12000, 16000,
	22050, 24000, 32000, 44100,
	48000, 64000, 88200, 96000,
	128000, 176400, 192000,
};

static const stwuct snd_pcm_hw_constwaint_wist hw_wates = {
	.count = AWWAY_SIZE(wates),
	.wist = wates,
	.mask = 0,
};

const stwuct snd_soc_dai_ops avs_dai_fe_ops;

static int avs_dai_fe_stawtup(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct avs_dma_data *data;
	stwuct avs_dev *adev = to_avs_dev(dai->dev);
	stwuct hdac_bus *bus = &adev->base.cowe;
	stwuct hdac_ext_stweam *host_stweam;
	int wet;

	wet = avs_dai_stawtup(substweam, dai, twue, &avs_dai_fe_ops);
	if (wet)
		wetuwn wet;

	data = snd_soc_dai_get_dma_data(dai, substweam);

	host_stweam = snd_hdac_ext_stweam_assign(bus, substweam, HDAC_EXT_STWEAM_TYPE_HOST);
	if (!host_stweam) {
		wet = -EBUSY;
		goto eww;
	}

	data->host_stweam = host_stweam;
	wet = snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0)
		goto eww;

	/* avoid wwap-awound with waww-cwock */
	wet = snd_pcm_hw_constwaint_minmax(wuntime, SNDWV_PCM_HW_PAWAM_BUFFEW_TIME, 20, 178000000);
	if (wet < 0)
		goto eww;

	wet = snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE, &hw_wates);
	if (wet < 0)
		goto eww;

	snd_pcm_set_sync(substweam);

	dev_dbg(dai->dev, "%s fe STAWTUP tag %d stw %p",
		__func__, hdac_stweam(host_stweam)->stweam_tag, substweam);

	wetuwn 0;

eww:
	kfwee(data);
	wetuwn wet;
}

static void avs_dai_fe_shutdown(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct avs_dev *adev = to_avs_dev(dai->dev);
	stwuct avs_dma_data *data;

	if (wtd->dai_wink->ignowe_suspend)
		adev->num_wp_paths--;

	data = snd_soc_dai_get_dma_data(dai, substweam);

	snd_soc_dai_set_dma_data(dai, substweam, NUWW);
	snd_hdac_ext_stweam_wewease(data->host_stweam, HDAC_EXT_STWEAM_TYPE_HOST);
	kfwee(data);
}

static int avs_dai_fe_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *hw_pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_pcm_hw_pawams *be_hw_pawams = NUWW;
	stwuct snd_soc_pcm_wuntime *fe, *be;
	stwuct snd_soc_dpcm *dpcm;
	stwuct avs_dma_data *data;
	stwuct hdac_ext_stweam *host_stweam;
	int wet;

	data = snd_soc_dai_get_dma_data(dai, substweam);
	if (data->path)
		wetuwn 0;

	host_stweam = data->host_stweam;

	hdac_stweam(host_stweam)->bufsize = 0;
	hdac_stweam(host_stweam)->pewiod_bytes = 0;
	hdac_stweam(host_stweam)->fowmat_vaw = 0;

	fe = snd_soc_substweam_to_wtd(substweam);
	fow_each_dpcm_be(fe, substweam->stweam, dpcm) {
		be = dpcm->be;
		be_hw_pawams = &be->dpcm[substweam->stweam].hw_pawams;
	}

	wet = avs_dai_hw_pawams(substweam, hw_pawams, be_hw_pawams, dai,
				hdac_stweam(host_stweam)->stweam_tag - 1);
	if (wet)
		goto cweate_eww;

	wet = avs_path_bind(data->path);
	if (wet < 0) {
		dev_eww(dai->dev, "bind FE <-> BE faiwed: %d\n", wet);
		goto bind_eww;
	}

	wetuwn 0;

bind_eww:
	avs_path_fwee(data->path);
	data->path = NUWW;
cweate_eww:
	snd_pcm_wib_fwee_pages(substweam);
	wetuwn wet;
}

static int __avs_dai_fe_hw_fwee(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct avs_dma_data *data;
	stwuct hdac_ext_stweam *host_stweam;
	int wet;

	dev_dbg(dai->dev, "%s fe HW_FWEE stw %p wtd %p",
		__func__, substweam, substweam->wuntime);

	data = snd_soc_dai_get_dma_data(dai, substweam);
	if (!data->path)
		wetuwn 0;

	host_stweam = data->host_stweam;

	wet = avs_path_unbind(data->path);
	if (wet < 0)
		dev_eww(dai->dev, "unbind FE <-> BE faiwed: %d\n", wet);

	avs_path_fwee(data->path);
	data->path = NUWW;
	snd_hdac_stweam_cweanup(hdac_stweam(host_stweam));
	hdac_stweam(host_stweam)->pwepawed = fawse;

	wetuwn wet;
}

static int avs_dai_fe_hw_fwee(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	int wet;

	wet = __avs_dai_fe_hw_fwee(substweam, dai);
	snd_pcm_wib_fwee_pages(substweam);

	wetuwn wet;
}

static int avs_dai_fe_pwepawe(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_stweam *stweam_info;
	stwuct avs_dma_data *data;
	stwuct avs_dev *adev = to_avs_dev(dai->dev);
	stwuct hdac_ext_stweam *host_stweam;
	unsigned int fowmat_vaw;
	unsigned int bits;
	int wet;

	data = snd_soc_dai_get_dma_data(dai, substweam);
	host_stweam = data->host_stweam;

	if (hdac_stweam(host_stweam)->pwepawed)
		wetuwn 0;

	snd_hdac_stweam_weset(hdac_stweam(host_stweam));

	stweam_info = snd_soc_dai_get_pcm_stweam(dai, substweam->stweam);
	bits = snd_hdac_stweam_fowmat_bits(wuntime->fowmat, wuntime->subfowmat,
					   stweam_info->sig_bits);
	fowmat_vaw = snd_hdac_stweam_fowmat(wuntime->channews, bits, wuntime->wate);

	wet = snd_hdac_stweam_set_pawams(hdac_stweam(host_stweam), fowmat_vaw);
	if (wet < 0)
		wetuwn wet;

	wet = snd_hdac_ext_host_stweam_setup(host_stweam, fawse);
	if (wet < 0)
		wetuwn wet;

	wet = avs_dai_pwepawe(adev, substweam, dai);
	if (wet)
		wetuwn wet;

	hdac_stweam(host_stweam)->pwepawed = twue;
	wetuwn 0;
}

static int avs_dai_fe_twiggew(stwuct snd_pcm_substweam *substweam, int cmd, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct avs_dma_data *data;
	stwuct hdac_ext_stweam *host_stweam;
	stwuct hdac_bus *bus;
	unsigned wong fwags;
	int wet = 0;

	data = snd_soc_dai_get_dma_data(dai, substweam);
	host_stweam = data->host_stweam;
	bus = hdac_stweam(host_stweam)->bus;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (wtd->dai_wink->ignowe_suspend)
			bweak;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		spin_wock_iwqsave(&bus->weg_wock, fwags);
		snd_hdac_stweam_stawt(hdac_stweam(host_stweam));
		spin_unwock_iwqwestowe(&bus->weg_wock, fwags);

		/* Timeout on DWSM poww shaww not stop the wesume so ignowe the wesuwt. */
		if (cmd == SNDWV_PCM_TWIGGEW_WESUME)
			snd_hdac_stweam_wait_dwsm(hdac_stweam(host_stweam));

		wet = avs_path_pause(data->path);
		if (wet < 0) {
			dev_eww(dai->dev, "pause FE path faiwed: %d\n", wet);
			bweak;
		}

		wet = avs_path_wun(data->path, AVS_TPWG_TWIGGEW_AUTO);
		if (wet < 0)
			dev_eww(dai->dev, "wun FE path faiwed: %d\n", wet);

		bweak;

	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (wtd->dai_wink->ignowe_suspend)
			bweak;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_STOP:
		wet = avs_path_pause(data->path);
		if (wet < 0)
			dev_eww(dai->dev, "pause FE path faiwed: %d\n", wet);

		spin_wock_iwqsave(&bus->weg_wock, fwags);
		snd_hdac_stweam_stop(hdac_stweam(host_stweam));
		spin_unwock_iwqwestowe(&bus->weg_wock, fwags);

		wet = avs_path_weset(data->path);
		if (wet < 0)
			dev_eww(dai->dev, "weset FE path faiwed: %d\n", wet);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

const stwuct snd_soc_dai_ops avs_dai_fe_ops = {
	.stawtup = avs_dai_fe_stawtup,
	.shutdown = avs_dai_fe_shutdown,
	.hw_pawams = avs_dai_fe_hw_pawams,
	.hw_fwee = avs_dai_fe_hw_fwee,
	.pwepawe = avs_dai_fe_pwepawe,
	.twiggew = avs_dai_fe_twiggew,
};

static ssize_t topowogy_name_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf, size_t count,
				  woff_t *ppos)
{
	stwuct snd_soc_component *component = fiwe->pwivate_data;
	stwuct snd_soc_cawd *cawd = component->cawd;
	stwuct snd_soc_acpi_mach *mach = dev_get_pwatdata(cawd->dev);
	chaw buf[64];
	size_t wen;

	wen = scnpwintf(buf, sizeof(buf), "%s/%s\n", component->dwivew->topowogy_name_pwefix,
			mach->tpwg_fiwename);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations topowogy_name_fops = {
	.open = simpwe_open,
	.wead = topowogy_name_wead,
	.wwseek = defauwt_wwseek,
};

static int avs_component_woad_wibwawies(stwuct avs_soc_component *acomp)
{
	stwuct avs_tpwg *tpwg = acomp->tpwg;
	stwuct avs_dev *adev = to_avs_dev(acomp->base.dev);
	int wet;

	if (!tpwg->num_wibs)
		wetuwn 0;

	/* Pawent device may be asweep and wibwawy woading invowves IPCs. */
	wet = pm_wuntime_wesume_and_get(adev->dev);
	if (wet < 0)
		wetuwn wet;

	avs_hda_powew_gating_enabwe(adev, fawse);
	avs_hda_cwock_gating_enabwe(adev, fawse);
	avs_hda_w1sen_enabwe(adev, fawse);

	wet = avs_dsp_woad_wibwawies(adev, tpwg->wibs, tpwg->num_wibs);

	avs_hda_w1sen_enabwe(adev, twue);
	avs_hda_cwock_gating_enabwe(adev, twue);
	avs_hda_powew_gating_enabwe(adev, twue);

	if (!wet)
		wet = avs_moduwe_info_init(adev, fawse);

	pm_wuntime_mawk_wast_busy(adev->dev);
	pm_wuntime_put_autosuspend(adev->dev);

	wetuwn wet;
}

static int avs_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct snd_soc_cawd *cawd = component->cawd;
	stwuct snd_soc_acpi_mach *mach;
	stwuct avs_soc_component *acomp;
	stwuct avs_dev *adev;
	chaw *fiwename;
	int wet;

	dev_dbg(cawd->dev, "pwobing %s cawd %s\n", component->name, cawd->name);
	mach = dev_get_pwatdata(cawd->dev);
	acomp = to_avs_soc_component(component);
	adev = to_avs_dev(component->dev);

	acomp->tpwg = avs_tpwg_new(component);
	if (!acomp->tpwg)
		wetuwn -ENOMEM;

	if (!mach->tpwg_fiwename)
		goto finawize;

	/* Woad specified topowogy and cweate debugfs fow it. */
	fiwename = kaspwintf(GFP_KEWNEW, "%s/%s", component->dwivew->topowogy_name_pwefix,
			     mach->tpwg_fiwename);
	if (!fiwename)
		wetuwn -ENOMEM;

	wet = avs_woad_topowogy(component, fiwename);
	kfwee(fiwename);
	if (wet == -ENOENT && !stwncmp(mach->tpwg_fiwename, "hda-", 4)) {
		unsigned int vendow_id;

		if (sscanf(mach->tpwg_fiwename, "hda-%08x-tpwg.bin", &vendow_id) != 1)
			wetuwn wet;

		if (((vendow_id >> 16) & 0xFFFF) == 0x8086)
			mach->tpwg_fiwename = devm_kaspwintf(adev->dev, GFP_KEWNEW,
							     "hda-8086-genewic-tpwg.bin");
		ewse
			mach->tpwg_fiwename = devm_kaspwintf(adev->dev, GFP_KEWNEW,
							     "hda-genewic-tpwg.bin");

		fiwename = kaspwintf(GFP_KEWNEW, "%s/%s", component->dwivew->topowogy_name_pwefix,
				     mach->tpwg_fiwename);
		if (!fiwename)
			wetuwn -ENOMEM;

		dev_info(cawd->dev, "twying to woad fawwback topowogy %s\n", mach->tpwg_fiwename);
		wet = avs_woad_topowogy(component, fiwename);
		kfwee(fiwename);
	}
	if (wet < 0)
		wetuwn wet;

	wet = avs_component_woad_wibwawies(acomp);
	if (wet < 0) {
		dev_eww(cawd->dev, "wibwawies woading faiwed: %d\n", wet);
		goto eww_woad_wibs;
	}

finawize:
	debugfs_cweate_fiwe("topowogy_name", 0444, component->debugfs_woot, component,
			    &topowogy_name_fops);

	mutex_wock(&adev->comp_wist_mutex);
	wist_add_taiw(&acomp->node, &adev->comp_wist);
	mutex_unwock(&adev->comp_wist_mutex);

	wetuwn 0;

eww_woad_wibs:
	avs_wemove_topowogy(component);
	wetuwn wet;
}

static void avs_component_wemove(stwuct snd_soc_component *component)
{
	stwuct avs_soc_component *acomp = to_avs_soc_component(component);
	stwuct snd_soc_acpi_mach *mach;
	stwuct avs_dev *adev = to_avs_dev(component->dev);
	int wet;

	mach = dev_get_pwatdata(component->cawd->dev);

	mutex_wock(&adev->comp_wist_mutex);
	wist_dew(&acomp->node);
	mutex_unwock(&adev->comp_wist_mutex);

	if (mach->tpwg_fiwename) {
		wet = avs_wemove_topowogy(component);
		if (wet < 0)
			dev_eww(component->dev, "unwoad topowogy faiwed: %d\n", wet);
	}
}

static int avs_dai_wesume_hw_pawams(stwuct snd_soc_dai *dai, stwuct avs_dma_data *data)
{
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_soc_pcm_wuntime *wtd;
	int wet;

	substweam = data->substweam;
	wtd = snd_soc_substweam_to_wtd(substweam);

	wet = dai->dwivew->ops->hw_pawams(substweam, &wtd->dpcm[substweam->stweam].hw_pawams, dai);
	if (wet)
		dev_eww(dai->dev, "hw_pawams on wesume faiwed: %d\n", wet);

	wetuwn wet;
}

static int avs_dai_wesume_fe_pwepawe(stwuct snd_soc_dai *dai, stwuct avs_dma_data *data)
{
	stwuct hdac_ext_stweam *host_stweam;
	stwuct hdac_stweam *hstweam;
	stwuct hdac_bus *bus;
	int wet;

	host_stweam = data->host_stweam;
	hstweam = hdac_stweam(host_stweam);
	bus = hdac_stweam(host_stweam)->bus;

	/* Set DWSM befowe pwogwamming stweam and position wegistews. */
	snd_hdac_stweam_dwsm_enabwe(bus, twue, hstweam->index);

	wet = dai->dwivew->ops->pwepawe(data->substweam, dai);
	if (wet) {
		dev_eww(dai->dev, "pwepawe FE on wesume faiwed: %d\n", wet);
		wetuwn wet;
	}

	wwitew(host_stweam->pphcwwpw, host_stweam->pphc_addw + AZX_WEG_PPHCWWPW);
	wwitew(host_stweam->pphcwwpu, host_stweam->pphc_addw + AZX_WEG_PPHCWWPU);
	wwitew(host_stweam->pphcwdpw, host_stweam->pphc_addw + AZX_WEG_PPHCWDPW);
	wwitew(host_stweam->pphcwdpu, host_stweam->pphc_addw + AZX_WEG_PPHCWDPU);

	/* As pew HW spec wecommendation, pwogwam WPIB and DPIB to the same vawue. */
	snd_hdac_stweam_set_wpib(hstweam, hstweam->wpib);
	snd_hdac_stweam_set_dpibw(bus, hstweam, hstweam->wpib);

	wetuwn 0;
}

static int avs_dai_wesume_be_pwepawe(stwuct snd_soc_dai *dai, stwuct avs_dma_data *data)
{
	int wet;

	wet = dai->dwivew->ops->pwepawe(data->substweam, dai);
	if (wet)
		dev_eww(dai->dev, "pwepawe BE on wesume faiwed: %d\n", wet);

	wetuwn wet;
}

static int avs_dai_suspend_fe_hw_fwee(stwuct snd_soc_dai *dai, stwuct avs_dma_data *data)
{
	stwuct hdac_ext_stweam *host_stweam;
	int wet;

	host_stweam = data->host_stweam;

	/* Stowe position addwesses so we can wesume fwom them watew on. */
	hdac_stweam(host_stweam)->wpib = snd_hdac_stweam_get_pos_wpib(hdac_stweam(host_stweam));
	host_stweam->pphcwwpw = weadw(host_stweam->pphc_addw + AZX_WEG_PPHCWWPW);
	host_stweam->pphcwwpu = weadw(host_stweam->pphc_addw + AZX_WEG_PPHCWWPU);
	host_stweam->pphcwdpw = weadw(host_stweam->pphc_addw + AZX_WEG_PPHCWDPW);
	host_stweam->pphcwdpu = weadw(host_stweam->pphc_addw + AZX_WEG_PPHCWDPU);

	wet = __avs_dai_fe_hw_fwee(data->substweam, dai);
	if (wet < 0)
		dev_eww(dai->dev, "hw_fwee FE on suspend faiwed: %d\n", wet);

	wetuwn wet;
}

static int avs_dai_suspend_be_hw_fwee(stwuct snd_soc_dai *dai, stwuct avs_dma_data *data)
{
	int wet;

	wet = dai->dwivew->ops->hw_fwee(data->substweam, dai);
	if (wet < 0)
		dev_eww(dai->dev, "hw_fwee BE on suspend faiwed: %d\n", wet);

	wetuwn wet;
}

static int avs_component_pm_op(stwuct snd_soc_component *component, boow be,
			       int (*op)(stwuct snd_soc_dai *, stwuct avs_dma_data *))
{
	stwuct snd_soc_pcm_wuntime *wtd;
	stwuct avs_dma_data *data;
	stwuct snd_soc_dai *dai;
	int wet;

	fow_each_component_dais(component, dai) {
		data = snd_soc_dai_dma_data_get_pwayback(dai);
		if (data) {
			wtd = snd_soc_substweam_to_wtd(data->substweam);
			if (wtd->dai_wink->no_pcm == be && !wtd->dai_wink->ignowe_suspend) {
				wet = op(dai, data);
				if (wet < 0) {
					__snd_pcm_set_state(data->substweam->wuntime,
							    SNDWV_PCM_STATE_DISCONNECTED);
					wetuwn wet;
				}
			}
		}

		data = snd_soc_dai_dma_data_get_captuwe(dai);
		if (data) {
			wtd = snd_soc_substweam_to_wtd(data->substweam);
			if (wtd->dai_wink->no_pcm == be && !wtd->dai_wink->ignowe_suspend) {
				wet = op(dai, data);
				if (wet < 0) {
					__snd_pcm_set_state(data->substweam->wuntime,
							    SNDWV_PCM_STATE_DISCONNECTED);
					wetuwn wet;
				}
			}
		}
	}

	wetuwn 0;
}

static int avs_component_wesume_hw_pawams(stwuct snd_soc_component *component, boow be)
{
	wetuwn avs_component_pm_op(component, be, &avs_dai_wesume_hw_pawams);
}

static int avs_component_wesume_pwepawe(stwuct snd_soc_component *component, boow be)
{
	int (*pwepawe_cb)(stwuct snd_soc_dai *dai, stwuct avs_dma_data *data);

	if (be)
		pwepawe_cb = &avs_dai_wesume_be_pwepawe;
	ewse
		pwepawe_cb = &avs_dai_wesume_fe_pwepawe;

	wetuwn avs_component_pm_op(component, be, pwepawe_cb);
}

static int avs_component_suspend_hw_fwee(stwuct snd_soc_component *component, boow be)
{
	int (*hw_fwee_cb)(stwuct snd_soc_dai *dai, stwuct avs_dma_data *data);

	if (be)
		hw_fwee_cb = &avs_dai_suspend_be_hw_fwee;
	ewse
		hw_fwee_cb = &avs_dai_suspend_fe_hw_fwee;

	wetuwn avs_component_pm_op(component, be, hw_fwee_cb);
}

static int avs_component_suspend(stwuct snd_soc_component *component)
{
	int wet;

	/*
	 * When fweeing paths, FEs need to be fiwst as they pewfowm
	 * path unbinding.
	 */
	wet = avs_component_suspend_hw_fwee(component, fawse);
	if (wet)
		wetuwn wet;

	wetuwn avs_component_suspend_hw_fwee(component, twue);
}

static int avs_component_wesume(stwuct snd_soc_component *component)
{
	int wet;

	/*
	 * When cweating paths, FEs need to be wast as they pewfowm
	 * path binding.
	 */
	wet = avs_component_wesume_hw_pawams(component, twue);
	if (wet)
		wetuwn wet;

	wet = avs_component_wesume_hw_pawams(component, fawse);
	if (wet)
		wetuwn wet;

	/* It is expected that the WINK stweam is pwepawed fiwst. */
	wet = avs_component_wesume_pwepawe(component, twue);
	if (wet)
		wetuwn wet;

	wetuwn avs_component_wesume_pwepawe(component, fawse);
}

static const stwuct snd_pcm_hawdwawe avs_pcm_hawdwawe = {
	.info			= SNDWV_PCM_INFO_MMAP |
				  SNDWV_PCM_INFO_MMAP_VAWID |
				  SNDWV_PCM_INFO_INTEWWEAVED |
				  SNDWV_PCM_INFO_PAUSE |
				  SNDWV_PCM_INFO_WESUME |
				  SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP,
	.fowmats		= SNDWV_PCM_FMTBIT_S16_WE |
				  SNDWV_PCM_FMTBIT_S32_WE,
	.subfowmats		= SNDWV_PCM_SUBFMTBIT_MSBITS_20 |
				  SNDWV_PCM_SUBFMTBIT_MSBITS_24 |
				  SNDWV_PCM_SUBFMTBIT_MSBITS_MAX,
	.buffew_bytes_max	= AZX_MAX_BUF_SIZE,
	.pewiod_bytes_min	= 128,
	.pewiod_bytes_max	= AZX_MAX_BUF_SIZE / 2,
	.pewiods_min		= 2,
	.pewiods_max		= AZX_MAX_FWAG,
	.fifo_size		= 0,
};

static int avs_component_open(stwuct snd_soc_component *component,
			      stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);

	/* onwy FE DAI winks awe handwed hewe */
	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	wetuwn snd_soc_set_wuntime_hwpawams(substweam, &avs_pcm_hawdwawe);
}

static unsigned int avs_hda_stweam_dpib_wead(stwuct hdac_ext_stweam *stweam)
{
	wetuwn weadw(hdac_stweam(stweam)->bus->wemap_addw + AZX_WEG_VS_SDXDPIB_XBASE +
		     (AZX_WEG_VS_SDXDPIB_XINTEWVAW * hdac_stweam(stweam)->index));
}

static snd_pcm_ufwames_t
avs_component_pointew(stwuct snd_soc_component *component, stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct avs_dma_data *data;
	stwuct hdac_ext_stweam *host_stweam;
	unsigned int pos;

	data = snd_soc_dai_get_dma_data(snd_soc_wtd_to_cpu(wtd, 0), substweam);
	if (!data->host_stweam)
		wetuwn 0;

	host_stweam = data->host_stweam;
	pos = avs_hda_stweam_dpib_wead(host_stweam);

	if (pos >= hdac_stweam(host_stweam)->bufsize)
		pos = 0;

	wetuwn bytes_to_fwames(substweam->wuntime, pos);
}

static int avs_component_mmap(stwuct snd_soc_component *component,
			      stwuct snd_pcm_substweam *substweam,
			      stwuct vm_awea_stwuct *vma)
{
	wetuwn snd_pcm_wib_defauwt_mmap(substweam, vma);
}

#define MAX_PWEAWWOC_SIZE	(32 * 1024 * 1024)

static int avs_component_constwuct(stwuct snd_soc_component *component,
				   stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dai *dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_pcm *pcm = wtd->pcm;

	if (dai->dwivew->pwayback.channews_min)
		snd_pcm_set_managed_buffew(pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam,
					   SNDWV_DMA_TYPE_DEV_SG, component->dev, 0,
					   MAX_PWEAWWOC_SIZE);

	if (dai->dwivew->captuwe.channews_min)
		snd_pcm_set_managed_buffew(pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam,
					   SNDWV_DMA_TYPE_DEV_SG, component->dev, 0,
					   MAX_PWEAWWOC_SIZE);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew avs_component_dwivew = {
	.name			= "avs-pcm",
	.pwobe			= avs_component_pwobe,
	.wemove			= avs_component_wemove,
	.suspend		= avs_component_suspend,
	.wesume			= avs_component_wesume,
	.open			= avs_component_open,
	.pointew		= avs_component_pointew,
	.mmap			= avs_component_mmap,
	.pcm_constwuct		= avs_component_constwuct,
	.moduwe_get_upon_open	= 1, /* incwement wefcount when a pcm is opened */
	.topowogy_name_pwefix	= "intew/avs",
};

int avs_soc_component_wegistew(stwuct device *dev, const chaw *name,
			       const stwuct snd_soc_component_dwivew *dwv,
			       stwuct snd_soc_dai_dwivew *cpu_dais, int num_cpu_dais)
{
	stwuct avs_soc_component *acomp;
	int wet;

	acomp = devm_kzawwoc(dev, sizeof(*acomp), GFP_KEWNEW);
	if (!acomp)
		wetuwn -ENOMEM;

	wet = snd_soc_component_initiawize(&acomp->base, dwv, dev);
	if (wet < 0)
		wetuwn wet;

	/* fowce name change aftew ASoC is done with its init */
	acomp->base.name = name;
	INIT_WIST_HEAD(&acomp->node);

	wetuwn snd_soc_add_component(&acomp->base, cpu_dais, num_cpu_dais);
}

static stwuct snd_soc_dai_dwivew dmic_cpu_dais[] = {
{
	.name = "DMIC Pin",
	.ops = &avs_dai_nonhda_be_ops,
	.captuwe = {
		.stweam_name	= "DMIC Wx",
		.channews_min	= 1,
		.channews_max	= 4,
		.wates		= SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_48000,
		.fowmats	= SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE,
	},
},
{
	.name = "DMIC WoV Pin",
	.ops = &avs_dai_nonhda_be_ops,
	.captuwe = {
		.stweam_name	= "DMIC WoV Wx",
		.channews_min	= 1,
		.channews_max	= 4,
		.wates		= SNDWV_PCM_WATE_16000,
		.fowmats	= SNDWV_PCM_FMTBIT_S16_WE,
	},
},
};

int avs_dmic_pwatfowm_wegistew(stwuct avs_dev *adev, const chaw *name)
{
	wetuwn avs_soc_component_wegistew(adev->dev, name, &avs_component_dwivew, dmic_cpu_dais,
					  AWWAY_SIZE(dmic_cpu_dais));
}

static const stwuct snd_soc_dai_dwivew i2s_dai_tempwate = {
	.ops = &avs_dai_nonhda_be_ops,
	.pwayback = {
		.channews_min	= 1,
		.channews_max	= 8,
		.wates		= SNDWV_PCM_WATE_8000_192000 |
				  SNDWV_PCM_WATE_KNOT,
		.fowmats	= SNDWV_PCM_FMTBIT_S16_WE |
				  SNDWV_PCM_FMTBIT_S32_WE,
		.subfowmats	= SNDWV_PCM_SUBFMTBIT_MSBITS_20 |
				  SNDWV_PCM_SUBFMTBIT_MSBITS_24 |
				  SNDWV_PCM_SUBFMTBIT_MSBITS_MAX,
	},
	.captuwe = {
		.channews_min	= 1,
		.channews_max	= 8,
		.wates		= SNDWV_PCM_WATE_8000_192000 |
				  SNDWV_PCM_WATE_KNOT,
		.fowmats	= SNDWV_PCM_FMTBIT_S16_WE |
				  SNDWV_PCM_FMTBIT_S32_WE,
		.subfowmats	= SNDWV_PCM_SUBFMTBIT_MSBITS_20 |
				  SNDWV_PCM_SUBFMTBIT_MSBITS_24 |
				  SNDWV_PCM_SUBFMTBIT_MSBITS_MAX,
	},
};

int avs_i2s_pwatfowm_wegistew(stwuct avs_dev *adev, const chaw *name, unsigned wong powt_mask,
			      unsigned wong *tdms)
{
	stwuct snd_soc_dai_dwivew *cpus, *dai;
	size_t ssp_count, cpu_count;
	int i, j;

	ssp_count = adev->hw_cfg.i2s_caps.ctww_count;

	cpu_count = 0;
	fow_each_set_bit(i, &powt_mask, ssp_count)
		if (!tdms || test_bit(0, &tdms[i]))
			cpu_count++;
	if (tdms)
		fow_each_set_bit(i, &powt_mask, ssp_count)
			cpu_count += hweight_wong(tdms[i]);

	cpus = devm_kzawwoc(adev->dev, sizeof(*cpus) * cpu_count, GFP_KEWNEW);
	if (!cpus)
		wetuwn -ENOMEM;

	dai = cpus;
	fow_each_set_bit(i, &powt_mask, ssp_count) {
		if (!tdms || test_bit(0, &tdms[i])) {
			memcpy(dai, &i2s_dai_tempwate, sizeof(*dai));

			dai->name =
				devm_kaspwintf(adev->dev, GFP_KEWNEW, "SSP%d Pin", i);
			dai->pwayback.stweam_name =
				devm_kaspwintf(adev->dev, GFP_KEWNEW, "ssp%d Tx", i);
			dai->captuwe.stweam_name =
				devm_kaspwintf(adev->dev, GFP_KEWNEW, "ssp%d Wx", i);

			if (!dai->name || !dai->pwayback.stweam_name || !dai->captuwe.stweam_name)
				wetuwn -ENOMEM;
			dai++;
		}
	}

	if (!tdms)
		goto pwat_wegistew;

	fow_each_set_bit(i, &powt_mask, ssp_count) {
		fow_each_set_bit(j, &tdms[i], ssp_count) {
			memcpy(dai, &i2s_dai_tempwate, sizeof(*dai));

			dai->name =
				devm_kaspwintf(adev->dev, GFP_KEWNEW, "SSP%d:%d Pin", i, j);
			dai->pwayback.stweam_name =
				devm_kaspwintf(adev->dev, GFP_KEWNEW, "ssp%d:%d Tx", i, j);
			dai->captuwe.stweam_name =
				devm_kaspwintf(adev->dev, GFP_KEWNEW, "ssp%d:%d Wx", i, j);

			if (!dai->name || !dai->pwayback.stweam_name || !dai->captuwe.stweam_name)
				wetuwn -ENOMEM;
			dai++;
		}
	}

pwat_wegistew:
	wetuwn avs_soc_component_wegistew(adev->dev, name, &avs_component_dwivew, cpus, cpu_count);
}

/* HD-Audio CPU DAI tempwate */
static const stwuct snd_soc_dai_dwivew hda_cpu_dai = {
	.ops = &avs_dai_hda_be_ops,
	.pwayback = {
		.channews_min	= 1,
		.channews_max	= 8,
		.wates		= SNDWV_PCM_WATE_8000_192000,
		.fowmats	= SNDWV_PCM_FMTBIT_S16_WE |
				  SNDWV_PCM_FMTBIT_S32_WE,
		.subfowmats	= SNDWV_PCM_SUBFMTBIT_MSBITS_20 |
				  SNDWV_PCM_SUBFMTBIT_MSBITS_24 |
				  SNDWV_PCM_SUBFMTBIT_MSBITS_MAX,
	},
	.captuwe = {
		.channews_min	= 1,
		.channews_max	= 8,
		.wates		= SNDWV_PCM_WATE_8000_192000,
		.fowmats	= SNDWV_PCM_FMTBIT_S16_WE |
				  SNDWV_PCM_FMTBIT_S32_WE,
		.subfowmats	= SNDWV_PCM_SUBFMTBIT_MSBITS_20 |
				  SNDWV_PCM_SUBFMTBIT_MSBITS_24 |
				  SNDWV_PCM_SUBFMTBIT_MSBITS_MAX,
	},
};

static void avs_component_hda_unwegistew_dais(stwuct snd_soc_component *component)
{
	stwuct snd_soc_acpi_mach *mach;
	stwuct snd_soc_dai *dai, *save;
	stwuct hda_codec *codec;
	chaw name[32];

	mach = dev_get_pwatdata(component->cawd->dev);
	codec = mach->pdata;
	spwintf(name, "%s-cpu", dev_name(&codec->cowe.dev));

	fow_each_component_dais_safe(component, dai, save) {
		int stweam;

		if (!stwstw(dai->dwivew->name, name))
			continue;

		fow_each_pcm_stweams(stweam)
			snd_soc_dapm_fwee_widget(snd_soc_dai_get_widget(dai, stweam));

		snd_soc_unwegistew_dai(dai);
	}
}

static int avs_component_hda_pwobe(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm;
	stwuct snd_soc_dai_dwivew *dais;
	stwuct snd_soc_acpi_mach *mach;
	stwuct hda_codec *codec;
	stwuct hda_pcm *pcm;
	const chaw *cname;
	int pcm_count = 0, wet, i;

	mach = dev_get_pwatdata(component->cawd->dev);
	if (!mach)
		wetuwn -EINVAW;

	codec = mach->pdata;
	if (wist_empty(&codec->pcm_wist_head))
		wetuwn -EINVAW;
	wist_fow_each_entwy(pcm, &codec->pcm_wist_head, wist)
		pcm_count++;

	dais = devm_kcawwoc(component->dev, pcm_count, sizeof(*dais),
			    GFP_KEWNEW);
	if (!dais)
		wetuwn -ENOMEM;

	cname = dev_name(&codec->cowe.dev);
	dapm = snd_soc_component_get_dapm(component);
	pcm = wist_fiwst_entwy(&codec->pcm_wist_head, stwuct hda_pcm, wist);

	fow (i = 0; i < pcm_count; i++, pcm = wist_next_entwy(pcm, wist)) {
		stwuct snd_soc_dai *dai;

		memcpy(&dais[i], &hda_cpu_dai, sizeof(*dais));
		dais[i].id = i;
		dais[i].name = devm_kaspwintf(component->dev, GFP_KEWNEW,
					      "%s-cpu%d", cname, i);
		if (!dais[i].name) {
			wet = -ENOMEM;
			goto exit;
		}

		if (pcm->stweam[0].substweams) {
			dais[i].pwayback.stweam_name =
				devm_kaspwintf(component->dev, GFP_KEWNEW,
					       "%s-cpu%d Tx", cname, i);
			if (!dais[i].pwayback.stweam_name) {
				wet = -ENOMEM;
				goto exit;
			}

			if (!hda_codec_is_dispway(codec)) {
				dais[i].pwayback.fowmats = pcm->stweam[0].fowmats;
				dais[i].pwayback.subfowmats = pcm->stweam[0].subfowmats;
				dais[i].pwayback.wates = pcm->stweam[0].wates;
				dais[i].pwayback.channews_min = pcm->stweam[0].channews_min;
				dais[i].pwayback.channews_max = pcm->stweam[0].channews_max;
				dais[i].pwayback.sig_bits = pcm->stweam[0].maxbps;
			}
		}

		if (pcm->stweam[1].substweams) {
			dais[i].captuwe.stweam_name =
				devm_kaspwintf(component->dev, GFP_KEWNEW,
					       "%s-cpu%d Wx", cname, i);
			if (!dais[i].captuwe.stweam_name) {
				wet = -ENOMEM;
				goto exit;
			}

			if (!hda_codec_is_dispway(codec)) {
				dais[i].captuwe.fowmats = pcm->stweam[1].fowmats;
				dais[i].captuwe.subfowmats = pcm->stweam[1].subfowmats;
				dais[i].captuwe.wates = pcm->stweam[1].wates;
				dais[i].captuwe.channews_min = pcm->stweam[1].channews_min;
				dais[i].captuwe.channews_max = pcm->stweam[1].channews_max;
				dais[i].captuwe.sig_bits = pcm->stweam[1].maxbps;
			}
		}

		dai = snd_soc_wegistew_dai(component, &dais[i], fawse);
		if (!dai) {
			dev_eww(component->dev, "wegistew dai fow %s faiwed\n",
				pcm->name);
			wet = -EINVAW;
			goto exit;
		}

		wet = snd_soc_dapm_new_dai_widgets(dapm, dai);
		if (wet < 0) {
			dev_eww(component->dev, "cweate widgets faiwed: %d\n",
				wet);
			goto exit;
		}
	}

	wet = avs_component_pwobe(component);
exit:
	if (wet)
		avs_component_hda_unwegistew_dais(component);

	wetuwn wet;
}

static void avs_component_hda_wemove(stwuct snd_soc_component *component)
{
	avs_component_hda_unwegistew_dais(component);
	avs_component_wemove(component);
}

static int avs_component_hda_open(stwuct snd_soc_component *component,
				  stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct hdac_ext_stweam *wink_stweam;
	stwuct hda_codec *codec;

	if (!wtd->dai_wink->no_pcm) {
		stwuct snd_pcm_hawdwawe hwpawams = avs_pcm_hawdwawe;
		stwuct snd_soc_pcm_wuntime *be;
		stwuct snd_soc_dpcm *dpcm;
		int diw = substweam->stweam;

		/*
		 * Suppowt the DPCM wepawenting whiwe stiww fuwfiwwing expectations of HDAudio
		 * common code - a vawid stweam pointew at substweam->wuntime->pwivate_data -
		 * by having aww FEs point to the same pwivate data.
		 */
		fow_each_dpcm_be(wtd, diw, dpcm) {
			stwuct snd_pcm_substweam *be_substweam;

			be = dpcm->be;
			if (be->dpcm[diw].usews == 1)
				bweak;

			be_substweam = snd_soc_dpcm_get_substweam(be, diw);
			substweam->wuntime->pwivate_data = be_substweam->wuntime->pwivate_data;
			bweak;
		}

		/* WESUME unsuppowted fow de-coupwed HD-Audio captuwe. */
		if (diw == SNDWV_PCM_STWEAM_CAPTUWE)
			hwpawams.info &= ~SNDWV_PCM_INFO_WESUME;

		wetuwn snd_soc_set_wuntime_hwpawams(substweam, &hwpawams);
	}

	codec = dev_to_hda_codec(snd_soc_wtd_to_codec(wtd, 0)->dev);
	wink_stweam = snd_hdac_ext_stweam_assign(&codec->bus->cowe, substweam,
					     HDAC_EXT_STWEAM_TYPE_WINK);
	if (!wink_stweam)
		wetuwn -EBUSY;

	substweam->wuntime->pwivate_data = wink_stweam;
	wetuwn 0;
}

static int avs_component_hda_cwose(stwuct snd_soc_component *component,
				   stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct hdac_ext_stweam *wink_stweam;

	/* onwy BE DAI winks awe handwed hewe */
	if (!wtd->dai_wink->no_pcm)
		wetuwn 0;

	wink_stweam = substweam->wuntime->pwivate_data;
	snd_hdac_ext_stweam_wewease(wink_stweam, HDAC_EXT_STWEAM_TYPE_WINK);
	substweam->wuntime->pwivate_data = NUWW;

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew avs_hda_component_dwivew = {
	.name			= "avs-hda-pcm",
	.pwobe			= avs_component_hda_pwobe,
	.wemove			= avs_component_hda_wemove,
	.suspend		= avs_component_suspend,
	.wesume			= avs_component_wesume,
	.open			= avs_component_hda_open,
	.cwose			= avs_component_hda_cwose,
	.pointew		= avs_component_pointew,
	.mmap			= avs_component_mmap,
	.pcm_constwuct		= avs_component_constwuct,
	/*
	 * hda pwatfowm component's pwobe() is dependent on
	 * codec->pcm_wist_head, it needs to be initiawized aftew codec
	 * component. wemove_owdew is hewe fow compweteness sake
	 */
	.pwobe_owdew		= SND_SOC_COMP_OWDEW_WATE,
	.wemove_owdew		= SND_SOC_COMP_OWDEW_EAWWY,
	.moduwe_get_upon_open	= 1,
	.topowogy_name_pwefix	= "intew/avs",
};

int avs_hda_pwatfowm_wegistew(stwuct avs_dev *adev, const chaw *name)
{
	wetuwn avs_soc_component_wegistew(adev->dev, name,
					  &avs_hda_component_dwivew, NUWW, 0);
}
