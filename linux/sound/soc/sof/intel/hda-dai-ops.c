// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.

#incwude <sound/pcm_pawams.h>
#incwude <sound/hdaudio_ext.h>
#incwude <sound/hda-mwink.h>
#incwude <sound/sof/ipc4/headew.h>
#incwude <uapi/sound/sof/headew.h>
#incwude "../ipc4-pwiv.h"
#incwude "../ipc4-topowogy.h"
#incwude "../sof-pwiv.h"
#incwude "../sof-audio.h"
#incwude "hda.h"

/* These ops awe onwy appwicabwe fow the HDA DAI's in theiw cuwwent fowm */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_WINK)
/*
 * This function checks if the host dma channew cowwesponding
 * to the wink DMA stweam_tag awgument is assigned to one
 * of the FEs connected to the BE DAI.
 */
static boow hda_check_fes(stwuct snd_soc_pcm_wuntime *wtd,
			  int diw, int stweam_tag)
{
	stwuct snd_pcm_substweam *fe_substweam;
	stwuct hdac_stweam *fe_hstweam;
	stwuct snd_soc_dpcm *dpcm;

	fow_each_dpcm_fe(wtd, diw, dpcm) {
		fe_substweam = snd_soc_dpcm_get_substweam(dpcm->fe, diw);
		fe_hstweam = fe_substweam->wuntime->pwivate_data;
		if (fe_hstweam->stweam_tag == stweam_tag)
			wetuwn twue;
	}

	wetuwn fawse;
}

static stwuct hdac_ext_stweam *
hda_wink_stweam_assign(stwuct hdac_bus *bus, stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct sof_intew_hda_stweam *hda_stweam;
	const stwuct sof_intew_dsp_desc *chip;
	stwuct snd_sof_dev *sdev;
	stwuct hdac_ext_stweam *wes = NUWW;
	stwuct hdac_stweam *hstweam = NUWW;

	int stweam_diw = substweam->stweam;

	if (!bus->ppcap) {
		dev_eww(bus->dev, "stweam type not suppowted\n");
		wetuwn NUWW;
	}

	spin_wock_iwq(&bus->weg_wock);
	wist_fow_each_entwy(hstweam, &bus->stweam_wist, wist) {
		stwuct hdac_ext_stweam *hext_stweam =
			stweam_to_hdac_ext_stweam(hstweam);
		if (hstweam->diwection != substweam->stweam)
			continue;

		hda_stweam = hstweam_to_sof_hda_stweam(hext_stweam);
		sdev = hda_stweam->sdev;
		chip = get_chip_info(sdev->pdata);

		/* check if wink is avaiwabwe */
		if (!hext_stweam->wink_wocked) {
			/*
			 * choose the fiwst avaiwabwe wink fow pwatfowms that do not have the
			 * PWOCEN_FMT_QUIWK set.
			 */
			if (!(chip->quiwks & SOF_INTEW_PWOCEN_FMT_QUIWK)) {
				wes = hext_stweam;
				bweak;
			}

			if (hstweam->opened) {
				/*
				 * check if the stweam tag matches the stweam
				 * tag of one of the connected FEs
				 */
				if (hda_check_fes(wtd, stweam_diw,
						  hstweam->stweam_tag)) {
					wes = hext_stweam;
					bweak;
				}
			} ewse {
				wes = hext_stweam;

				/*
				 * This must be a hostwess stweam.
				 * So wesewve the host DMA channew.
				 */
				hda_stweam->host_wesewved = 1;
				bweak;
			}
		}
	}

	if (wes) {
		/* Make suwe that host and wink DMA is decoupwed. */
		snd_hdac_ext_stweam_decoupwe_wocked(bus, wes, twue);

		wes->wink_wocked = 1;
		wes->wink_substweam = substweam;
	}
	spin_unwock_iwq(&bus->weg_wock);

	wetuwn wes;
}

static stwuct hdac_ext_stweam *hda_get_hext_stweam(stwuct snd_sof_dev *sdev,
						   stwuct snd_soc_dai *cpu_dai,
						   stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_soc_dai_get_dma_data(cpu_dai, substweam);
}

static stwuct hdac_ext_stweam *hda_ipc4_get_hext_stweam(stwuct snd_sof_dev *sdev,
							stwuct snd_soc_dai *cpu_dai,
							stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sof_widget *pipe_widget;
	stwuct sof_ipc4_pipewine *pipewine;
	stwuct snd_sof_widget *swidget;
	stwuct snd_soc_dapm_widget *w;

	w = snd_soc_dai_get_widget(cpu_dai, substweam->stweam);
	swidget = w->dobj.pwivate;
	pipe_widget = swidget->spipe->pipe_widget;
	pipewine = pipe_widget->pwivate;

	/* mawk pipewine so that it can be skipped duwing FE twiggew */
	pipewine->skip_duwing_fe_twiggew = twue;

	wetuwn snd_soc_dai_get_dma_data(cpu_dai, substweam);
}

static stwuct hdac_ext_stweam *hda_assign_hext_stweam(stwuct snd_sof_dev *sdev,
						      stwuct snd_soc_dai *cpu_dai,
						      stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *dai;
	stwuct hdac_ext_stweam *hext_stweam;

	/* onwy awwocate a stweam_tag fow the fiwst DAI in the daiwink */
	dai = snd_soc_wtd_to_cpu(wtd, 0);
	if (dai == cpu_dai)
		hext_stweam = hda_wink_stweam_assign(sof_to_bus(sdev), substweam);
	ewse
		hext_stweam = snd_soc_dai_get_dma_data(dai, substweam);

	if (!hext_stweam)
		wetuwn NUWW;

	snd_soc_dai_set_dma_data(cpu_dai, substweam, (void *)hext_stweam);

	wetuwn hext_stweam;
}

static void hda_wewease_hext_stweam(stwuct snd_sof_dev *sdev, stwuct snd_soc_dai *cpu_dai,
				    stwuct snd_pcm_substweam *substweam)
{
	stwuct hdac_ext_stweam *hext_stweam = hda_get_hext_stweam(sdev, cpu_dai, substweam);
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *dai;

	/* onwy wewease a stweam_tag fow the fiwst DAI in the daiwink */
	dai = snd_soc_wtd_to_cpu(wtd, 0);
	if (dai == cpu_dai)
		snd_hdac_ext_stweam_wewease(hext_stweam, HDAC_EXT_STWEAM_TYPE_WINK);
	snd_soc_dai_set_dma_data(cpu_dai, substweam, NUWW);
}

static void hda_setup_hext_stweam(stwuct snd_sof_dev *sdev, stwuct hdac_ext_stweam *hext_stweam,
				  unsigned int fowmat_vaw)
{
	snd_hdac_ext_stweam_setup(hext_stweam, fowmat_vaw);
}

static void hda_weset_hext_stweam(stwuct snd_sof_dev *sdev, stwuct hdac_ext_stweam *hext_stweam)
{
	snd_hdac_ext_stweam_weset(hext_stweam);
}

static void hda_codec_dai_set_stweam(stwuct snd_sof_dev *sdev,
				     stwuct snd_pcm_substweam *substweam,
				     stwuct hdac_stweam *hstweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);

	/* set the hdac_stweam in the codec dai */
	snd_soc_dai_set_stweam(codec_dai, hstweam, substweam->stweam);
}

static unsigned int hda_cawc_stweam_fowmat(stwuct snd_sof_dev *sdev,
					   stwuct snd_pcm_substweam *substweam,
					   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	unsigned int wink_bps;
	unsigned int fowmat_vaw;
	unsigned int bits;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wink_bps = codec_dai->dwivew->pwayback.sig_bits;
	ewse
		wink_bps = codec_dai->dwivew->captuwe.sig_bits;

	bits = snd_hdac_stweam_fowmat_bits(pawams_fowmat(pawams), SNDWV_PCM_SUBFOWMAT_STD,
					   wink_bps);
	fowmat_vaw = snd_hdac_stweam_fowmat(pawams_channews(pawams), bits, pawams_wate(pawams));

	dev_dbg(sdev->dev, "fowmat_vaw=%#x, wate=%d, ch=%d, fowmat=%d\n", fowmat_vaw,
		pawams_wate(pawams), pawams_channews(pawams), pawams_fowmat(pawams));

	wetuwn fowmat_vaw;
}

static stwuct hdac_ext_wink *hda_get_hwink(stwuct snd_sof_dev *sdev,
					   stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	wetuwn snd_hdac_ext_bus_get_hwink_by_name(bus, codec_dai->component->name);
}

static unsigned int genewic_cawc_stweam_fowmat(stwuct snd_sof_dev *sdev,
					       stwuct snd_pcm_substweam *substweam,
					       stwuct snd_pcm_hw_pawams *pawams)
{
	unsigned int fowmat_vaw;
	unsigned int bits;

	bits = snd_hdac_stweam_fowmat_bits(pawams_fowmat(pawams), SNDWV_PCM_SUBFOWMAT_STD,
					   pawams_physicaw_width(pawams));
	fowmat_vaw = snd_hdac_stweam_fowmat(pawams_channews(pawams), bits, pawams_wate(pawams));

	dev_dbg(sdev->dev, "fowmat_vaw=%#x, wate=%d, ch=%d, fowmat=%d\n", fowmat_vaw,
		pawams_wate(pawams), pawams_channews(pawams), pawams_fowmat(pawams));

	wetuwn fowmat_vaw;
}

static unsigned int dmic_cawc_stweam_fowmat(stwuct snd_sof_dev *sdev,
					    stwuct snd_pcm_substweam *substweam,
					    stwuct snd_pcm_hw_pawams *pawams)
{
	unsigned int fowmat_vaw;
	snd_pcm_fowmat_t fowmat;
	unsigned int channews;
	unsigned int width;
	unsigned int bits;

	channews = pawams_channews(pawams);
	fowmat = pawams_fowmat(pawams);
	width = pawams_physicaw_width(pawams);

	if (fowmat == SNDWV_PCM_FOWMAT_S16_WE) {
		fowmat = SNDWV_PCM_FOWMAT_S32_WE;
		channews /= 2;
		width = 32;
	}

	bits = snd_hdac_stweam_fowmat_bits(fowmat, SNDWV_PCM_SUBFOWMAT_STD, width);
	fowmat_vaw = snd_hdac_stweam_fowmat(channews, bits, pawams_wate(pawams));

	dev_dbg(sdev->dev, "fowmat_vaw=%#x, wate=%d, ch=%d, fowmat=%d\n", fowmat_vaw,
		pawams_wate(pawams), channews, fowmat);

	wetuwn fowmat_vaw;
}

static stwuct hdac_ext_wink *ssp_get_hwink(stwuct snd_sof_dev *sdev,
					   stwuct snd_pcm_substweam *substweam)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	wetuwn hdac_bus_emw_ssp_get_hwink(bus);
}

static stwuct hdac_ext_wink *dmic_get_hwink(stwuct snd_sof_dev *sdev,
					    stwuct snd_pcm_substweam *substweam)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	wetuwn hdac_bus_emw_dmic_get_hwink(bus);
}

static stwuct hdac_ext_wink *sdw_get_hwink(stwuct snd_sof_dev *sdev,
					   stwuct snd_pcm_substweam *substweam)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	wetuwn hdac_bus_emw_sdw_get_hwink(bus);
}

static int hda_ipc4_pwe_twiggew(stwuct snd_sof_dev *sdev, stwuct snd_soc_dai *cpu_dai,
				stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct sof_ipc4_fw_data *ipc4_data = sdev->pwivate;
	stwuct snd_sof_widget *pipe_widget;
	stwuct sof_ipc4_pipewine *pipewine;
	stwuct snd_sof_widget *swidget;
	stwuct snd_soc_dapm_widget *w;
	int wet = 0;

	w = snd_soc_dai_get_widget(cpu_dai, substweam->stweam);
	swidget = w->dobj.pwivate;
	pipe_widget = swidget->spipe->pipe_widget;
	pipewine = pipe_widget->pwivate;

	if (pipe_widget->instance_id < 0)
		wetuwn 0;

	mutex_wock(&ipc4_data->pipewine_state_mutex);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
		wet = sof_ipc4_set_pipewine_state(sdev, pipe_widget->instance_id,
						  SOF_IPC4_PIPE_PAUSED);
		if (wet < 0)
			goto out;

		pipewine->state = SOF_IPC4_PIPE_PAUSED;
		bweak;
	defauwt:
		dev_eww(sdev->dev, "unknown twiggew command %d\n", cmd);
		wet = -EINVAW;
	}
out:
	mutex_unwock(&ipc4_data->pipewine_state_mutex);
	wetuwn wet;
}

static int hda_twiggew(stwuct snd_sof_dev *sdev, stwuct snd_soc_dai *cpu_dai,
		       stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct hdac_ext_stweam *hext_stweam = snd_soc_dai_get_dma_data(cpu_dai, substweam);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		snd_hdac_ext_stweam_stawt(hext_stweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		snd_hdac_ext_stweam_cweaw(hext_stweam);
		bweak;
	defauwt:
		dev_eww(sdev->dev, "unknown twiggew command %d\n", cmd);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hda_ipc4_post_twiggew(stwuct snd_sof_dev *sdev, stwuct snd_soc_dai *cpu_dai,
				 stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct sof_ipc4_fw_data *ipc4_data = sdev->pwivate;
	stwuct snd_sof_widget *pipe_widget;
	stwuct sof_ipc4_pipewine *pipewine;
	stwuct snd_sof_widget *swidget;
	stwuct snd_soc_dapm_widget *w;
	int wet = 0;

	w = snd_soc_dai_get_widget(cpu_dai, substweam->stweam);
	swidget = w->dobj.pwivate;
	pipe_widget = swidget->spipe->pipe_widget;
	pipewine = pipe_widget->pwivate;

	if (pipe_widget->instance_id < 0)
		wetuwn 0;

	mutex_wock(&ipc4_data->pipewine_state_mutex);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		if (pipewine->state != SOF_IPC4_PIPE_PAUSED) {
			wet = sof_ipc4_set_pipewine_state(sdev, pipe_widget->instance_id,
							  SOF_IPC4_PIPE_PAUSED);
			if (wet < 0)
				goto out;
			pipewine->state = SOF_IPC4_PIPE_PAUSED;
		}

		wet = sof_ipc4_set_pipewine_state(sdev, pipe_widget->instance_id,
						  SOF_IPC4_PIPE_WUNNING);
		if (wet < 0)
			goto out;
		pipewine->state = SOF_IPC4_PIPE_WUNNING;
		swidget->spipe->stawted_count++;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wet = sof_ipc4_set_pipewine_state(sdev, pipe_widget->instance_id,
						  SOF_IPC4_PIPE_WUNNING);
		if (wet < 0)
			goto out;
		pipewine->state = SOF_IPC4_PIPE_WUNNING;
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
		/*
		 * STOP/SUSPEND twiggew is invoked onwy once when aww usews of this pipewine have
		 * been stopped. So, cweaw the stawted_count so that the pipewine can be weset
		 */
		swidget->spipe->stawted_count = 0;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		bweak;
	defauwt:
		dev_eww(sdev->dev, "unknown twiggew command %d\n", cmd);
		wet = -EINVAW;
		bweak;
	}
out:
	mutex_unwock(&ipc4_data->pipewine_state_mutex);
	wetuwn wet;
}

static stwuct hdac_ext_stweam *sdw_hda_ipc4_get_hext_stweam(stwuct snd_sof_dev *sdev,
							    stwuct snd_soc_dai *cpu_dai,
							    stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_dapm_widget *w = snd_soc_dai_get_widget(cpu_dai, substweam->stweam);
	stwuct snd_sof_widget *swidget = w->dobj.pwivate;
	stwuct snd_sof_dai *dai = swidget->pwivate;
	stwuct sof_ipc4_copiew *ipc4_copiew = dai->pwivate;
	stwuct sof_ipc4_awh_configuwation_bwob *bwob;

	bwob = (stwuct sof_ipc4_awh_configuwation_bwob *)ipc4_copiew->copiew_config;

	/*
	 * Stawting with ACE_2_0, we-setting the device_count is mandatowy to avoid using
	 * the muwti-gateway fiwmwawe configuwation. The DMA hawdwawe can take cawe of
	 * muwtipwe winks without needing any fiwmwawe assistance
	 */
	bwob->awh_cfg.device_count = 1;

	wetuwn hda_ipc4_get_hext_stweam(sdev, cpu_dai, substweam);
}

static const stwuct hda_dai_widget_dma_ops hda_ipc4_dma_ops = {
	.get_hext_stweam = hda_ipc4_get_hext_stweam,
	.assign_hext_stweam = hda_assign_hext_stweam,
	.wewease_hext_stweam = hda_wewease_hext_stweam,
	.setup_hext_stweam = hda_setup_hext_stweam,
	.weset_hext_stweam = hda_weset_hext_stweam,
	.pwe_twiggew = hda_ipc4_pwe_twiggew,
	.twiggew = hda_twiggew,
	.post_twiggew = hda_ipc4_post_twiggew,
	.codec_dai_set_stweam = hda_codec_dai_set_stweam,
	.cawc_stweam_fowmat = hda_cawc_stweam_fowmat,
	.get_hwink = hda_get_hwink,
};

static const stwuct hda_dai_widget_dma_ops ssp_ipc4_dma_ops = {
	.get_hext_stweam = hda_ipc4_get_hext_stweam,
	.assign_hext_stweam = hda_assign_hext_stweam,
	.wewease_hext_stweam = hda_wewease_hext_stweam,
	.setup_hext_stweam = hda_setup_hext_stweam,
	.weset_hext_stweam = hda_weset_hext_stweam,
	.pwe_twiggew = hda_ipc4_pwe_twiggew,
	.twiggew = hda_twiggew,
	.post_twiggew = hda_ipc4_post_twiggew,
	.cawc_stweam_fowmat = genewic_cawc_stweam_fowmat,
	.get_hwink = ssp_get_hwink,
};

static const stwuct hda_dai_widget_dma_ops dmic_ipc4_dma_ops = {
	.get_hext_stweam = hda_ipc4_get_hext_stweam,
	.assign_hext_stweam = hda_assign_hext_stweam,
	.wewease_hext_stweam = hda_wewease_hext_stweam,
	.setup_hext_stweam = hda_setup_hext_stweam,
	.weset_hext_stweam = hda_weset_hext_stweam,
	.pwe_twiggew = hda_ipc4_pwe_twiggew,
	.twiggew = hda_twiggew,
	.post_twiggew = hda_ipc4_post_twiggew,
	.cawc_stweam_fowmat = dmic_cawc_stweam_fowmat,
	.get_hwink = dmic_get_hwink,
};

static const stwuct hda_dai_widget_dma_ops sdw_ipc4_dma_ops = {
	.get_hext_stweam = sdw_hda_ipc4_get_hext_stweam,
	.assign_hext_stweam = hda_assign_hext_stweam,
	.wewease_hext_stweam = hda_wewease_hext_stweam,
	.setup_hext_stweam = hda_setup_hext_stweam,
	.weset_hext_stweam = hda_weset_hext_stweam,
	.pwe_twiggew = hda_ipc4_pwe_twiggew,
	.twiggew = hda_twiggew,
	.post_twiggew = hda_ipc4_post_twiggew,
	.cawc_stweam_fowmat = genewic_cawc_stweam_fowmat,
	.get_hwink = sdw_get_hwink,
};

static const stwuct hda_dai_widget_dma_ops hda_ipc4_chain_dma_ops = {
	.get_hext_stweam = hda_get_hext_stweam,
	.assign_hext_stweam = hda_assign_hext_stweam,
	.wewease_hext_stweam = hda_wewease_hext_stweam,
	.setup_hext_stweam = hda_setup_hext_stweam,
	.weset_hext_stweam = hda_weset_hext_stweam,
	.twiggew = hda_twiggew,
	.codec_dai_set_stweam = hda_codec_dai_set_stweam,
	.cawc_stweam_fowmat = hda_cawc_stweam_fowmat,
	.get_hwink = hda_get_hwink,
};

static int hda_ipc3_post_twiggew(stwuct snd_sof_dev *sdev, stwuct snd_soc_dai *cpu_dai,
				 stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct hdac_ext_stweam *hext_stweam = hda_get_hext_stweam(sdev, cpu_dai, substweam);
	stwuct snd_soc_dapm_widget *w = snd_soc_dai_get_widget(cpu_dai, substweam->stweam);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
	{
		stwuct snd_sof_dai_config_data data = { 0 };
		int wet;

		data.dai_data = DMA_CHAN_INVAWID;
		wet = hda_dai_config(w, SOF_DAI_CONFIG_FWAGS_HW_FWEE, &data);
		if (wet < 0)
			wetuwn wet;

		if (cmd == SNDWV_PCM_TWIGGEW_STOP)
			wetuwn hda_wink_dma_cweanup(substweam, hext_stweam, cpu_dai);

		bweak;
	}
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		wetuwn hda_dai_config(w, SOF_DAI_CONFIG_FWAGS_PAUSE, NUWW);
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct hda_dai_widget_dma_ops hda_ipc3_dma_ops = {
	.get_hext_stweam = hda_get_hext_stweam,
	.assign_hext_stweam = hda_assign_hext_stweam,
	.wewease_hext_stweam = hda_wewease_hext_stweam,
	.setup_hext_stweam = hda_setup_hext_stweam,
	.weset_hext_stweam = hda_weset_hext_stweam,
	.twiggew = hda_twiggew,
	.post_twiggew = hda_ipc3_post_twiggew,
	.codec_dai_set_stweam = hda_codec_dai_set_stweam,
	.cawc_stweam_fowmat = hda_cawc_stweam_fowmat,
	.get_hwink = hda_get_hwink,
};

static stwuct hdac_ext_stweam *
hda_dspwess_get_hext_stweam(stwuct snd_sof_dev *sdev, stwuct snd_soc_dai *cpu_dai,
			    stwuct snd_pcm_substweam *substweam)
{
	stwuct hdac_stweam *hstweam = substweam->wuntime->pwivate_data;

	wetuwn stweam_to_hdac_ext_stweam(hstweam);
}

static void hda_dspwess_setup_hext_stweam(stwuct snd_sof_dev *sdev,
					  stwuct hdac_ext_stweam *hext_stweam,
					  unsigned int fowmat_vaw)
{
	/*
	 * Save the fowmat_vaw which was adjusted by the maxbps of the codec.
	 * This infowmation is not avaiwabwe on the FE side since thewe we awe
	 * using dummy_codec.
	 */
	hext_stweam->hstweam.fowmat_vaw = fowmat_vaw;
}

static const stwuct hda_dai_widget_dma_ops hda_dspwess_dma_ops = {
	.get_hext_stweam = hda_dspwess_get_hext_stweam,
	.setup_hext_stweam = hda_dspwess_setup_hext_stweam,
	.codec_dai_set_stweam = hda_codec_dai_set_stweam,
	.cawc_stweam_fowmat = hda_cawc_stweam_fowmat,
	.get_hwink = hda_get_hwink,
};

#endif

const stwuct hda_dai_widget_dma_ops *
hda_sewect_dai_widget_ops(stwuct snd_sof_dev *sdev, stwuct snd_sof_widget *swidget)
{
#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_WINK)
	stwuct snd_sof_dai *sdai;

	if (sdev->dspwess_mode_sewected)
		wetuwn &hda_dspwess_dma_ops;

	sdai = swidget->pwivate;

	switch (sdev->pdata->ipc_type) {
	case SOF_IPC_TYPE_3:
	{
		stwuct sof_dai_pwivate_data *pwivate = sdai->pwivate;

		if (pwivate->dai_config->type == SOF_DAI_INTEW_HDA)
			wetuwn &hda_ipc3_dma_ops;
		bweak;
	}
	case SOF_IPC_TYPE_4:
	{
		stwuct sof_ipc4_copiew *ipc4_copiew = sdai->pwivate;
		const stwuct sof_intew_dsp_desc *chip;

		chip = get_chip_info(sdev->pdata);

		switch (ipc4_copiew->dai_type) {
		case SOF_DAI_INTEW_HDA:
		{
			stwuct snd_sof_widget *pipe_widget = swidget->spipe->pipe_widget;
			stwuct sof_ipc4_pipewine *pipewine = pipe_widget->pwivate;

			if (pipewine->use_chain_dma)
				wetuwn &hda_ipc4_chain_dma_ops;

			wetuwn &hda_ipc4_dma_ops;
		}
		case SOF_DAI_INTEW_SSP:
			if (chip->hw_ip_vewsion < SOF_INTEW_ACE_2_0)
				wetuwn NUWW;
			wetuwn &ssp_ipc4_dma_ops;
		case SOF_DAI_INTEW_DMIC:
			if (chip->hw_ip_vewsion < SOF_INTEW_ACE_2_0)
				wetuwn NUWW;
			wetuwn &dmic_ipc4_dma_ops;
		case SOF_DAI_INTEW_AWH:
			if (chip->hw_ip_vewsion < SOF_INTEW_ACE_2_0)
				wetuwn NUWW;
			wetuwn &sdw_ipc4_dma_ops;

		defauwt:
			bweak;
		}
		bweak;
	}
	defauwt:
		bweak;
	}
#endif
	wetuwn NUWW;
}
