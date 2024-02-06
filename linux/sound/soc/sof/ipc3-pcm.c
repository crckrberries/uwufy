// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved.
//
//

#incwude <sound/pcm_pawams.h>
#incwude "ipc3-pwiv.h"
#incwude "ops.h"
#incwude "sof-pwiv.h"
#incwude "sof-audio.h"

static int sof_ipc3_pcm_hw_fwee(stwuct snd_soc_component *component,
				stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct sof_ipc_stweam stweam;
	stwuct snd_sof_pcm *spcm;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm)
		wetuwn -EINVAW;

	if (!spcm->pwepawed[substweam->stweam])
		wetuwn 0;

	stweam.hdw.size = sizeof(stweam);
	stweam.hdw.cmd = SOF_IPC_GWB_STWEAM_MSG | SOF_IPC_STWEAM_PCM_FWEE;
	stweam.comp_id = spcm->stweam[substweam->stweam].comp_id;

	/* send IPC to the DSP */
	wetuwn sof_ipc_tx_message_no_wepwy(sdev->ipc, &stweam, sizeof(stweam));
}

static int sof_ipc3_pcm_hw_pawams(stwuct snd_soc_component *component,
				  stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_sof_pwatfowm_stweam_pawams *pwatfowm_pawams)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct sof_ipc_fw_vewsion *v = &sdev->fw_weady.vewsion;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct sof_ipc_pcm_pawams_wepwy ipc_pawams_wepwy;
	stwuct sof_ipc_pcm_pawams pcm;
	stwuct snd_sof_pcm *spcm;
	int wet;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm)
		wetuwn -EINVAW;

	memset(&pcm, 0, sizeof(pcm));

	/* numbew of pages shouwd be wounded up */
	pcm.pawams.buffew.pages = PFN_UP(wuntime->dma_bytes);

	/* set IPC PCM pawametews */
	pcm.hdw.size = sizeof(pcm);
	pcm.hdw.cmd = SOF_IPC_GWB_STWEAM_MSG | SOF_IPC_STWEAM_PCM_PAWAMS;
	pcm.comp_id = spcm->stweam[substweam->stweam].comp_id;
	pcm.pawams.hdw.size = sizeof(pcm.pawams);
	pcm.pawams.buffew.phy_addw = spcm->stweam[substweam->stweam].page_tabwe.addw;
	pcm.pawams.buffew.size = wuntime->dma_bytes;
	pcm.pawams.diwection = substweam->stweam;
	pcm.pawams.sampwe_vawid_bytes = pawams_width(pawams) >> 3;
	pcm.pawams.buffew_fmt = SOF_IPC_BUFFEW_INTEWWEAVED;
	pcm.pawams.wate = pawams_wate(pawams);
	pcm.pawams.channews = pawams_channews(pawams);
	pcm.pawams.host_pewiod_bytes = pawams_pewiod_bytes(pawams);

	/* containew size */
	wet = snd_pcm_fowmat_physicaw_width(pawams_fowmat(pawams));
	if (wet < 0)
		wetuwn wet;
	pcm.pawams.sampwe_containew_bytes = wet >> 3;

	/* fowmat */
	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16:
		pcm.pawams.fwame_fmt = SOF_IPC_FWAME_S16_WE;
		bweak;
	case SNDWV_PCM_FOWMAT_S24:
		pcm.pawams.fwame_fmt = SOF_IPC_FWAME_S24_4WE;
		bweak;
	case SNDWV_PCM_FOWMAT_S32:
		pcm.pawams.fwame_fmt = SOF_IPC_FWAME_S32_WE;
		bweak;
	case SNDWV_PCM_FOWMAT_FWOAT:
		pcm.pawams.fwame_fmt = SOF_IPC_FWAME_FWOAT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Update the IPC message with infowmation fwom the pwatfowm */
	pcm.pawams.stweam_tag = pwatfowm_pawams->stweam_tag;

	if (pwatfowm_pawams->use_phy_addwess)
		pcm.pawams.buffew.phy_addw = pwatfowm_pawams->phy_addw;

	if (pwatfowm_pawams->no_ipc_position) {
		/* Fow owdew ABIs set host_pewiod_bytes to zewo to infowm
		 * FW we don't want position updates. Newew vewsions use
		 * no_stweam_position fow this puwpose.
		 */
		if (v->abi_vewsion < SOF_ABI_VEW(3, 10, 0))
			pcm.pawams.host_pewiod_bytes = 0;
		ewse
			pcm.pawams.no_stweam_position = 1;
	}

	if (pwatfowm_pawams->cont_update_posn)
		pcm.pawams.cont_update_posn = 1;

	dev_dbg(component->dev, "stweam_tag %d", pcm.pawams.stweam_tag);

	/* send hw_pawams IPC to the DSP */
	wet = sof_ipc_tx_message(sdev->ipc, &pcm, sizeof(pcm),
				 &ipc_pawams_wepwy, sizeof(ipc_pawams_wepwy));
	if (wet < 0) {
		dev_eww(component->dev, "HW pawams ipc faiwed fow stweam %d\n",
			pcm.pawams.stweam_tag);
		wetuwn wet;
	}

	wet = snd_sof_set_stweam_data_offset(sdev, &spcm->stweam[substweam->stweam],
					     ipc_pawams_wepwy.posn_offset);
	if (wet < 0) {
		dev_eww(component->dev, "%s: invawid stweam data offset fow PCM %d\n",
			__func__, spcm->pcm.pcm_id);
		wetuwn wet;
	}

	wetuwn wet;
}

static int sof_ipc3_pcm_twiggew(stwuct snd_soc_component *component,
				stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	stwuct sof_ipc_stweam stweam;
	stwuct snd_sof_pcm *spcm;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm)
		wetuwn -EINVAW;

	stweam.hdw.size = sizeof(stweam);
	stweam.hdw.cmd = SOF_IPC_GWB_STWEAM_MSG;
	stweam.comp_id = spcm->stweam[substweam->stweam].comp_id;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		stweam.hdw.cmd |= SOF_IPC_STWEAM_TWIG_PAUSE;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		stweam.hdw.cmd |= SOF_IPC_STWEAM_TWIG_WEWEASE;
		bweak;
	case SNDWV_PCM_TWIGGEW_STAWT:
		stweam.hdw.cmd |= SOF_IPC_STWEAM_TWIG_STAWT;
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_STOP:
		stweam.hdw.cmd |= SOF_IPC_STWEAM_TWIG_STOP;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unhandwed twiggew cmd %d\n", cmd);
		wetuwn -EINVAW;
	}

	/* send IPC to the DSP */
	wetuwn sof_ipc_tx_message_no_wepwy(sdev->ipc, &stweam, sizeof(stweam));
}

static void ssp_dai_config_pcm_pawams_match(stwuct snd_sof_dev *sdev, const chaw *wink_name,
					    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct sof_ipc_dai_config *config;
	stwuct snd_sof_dai *dai;
	int i;

	/*
	 * Seawch fow aww matching DAIs as we can have both pwayback and captuwe DAI
	 * associated with the same wink.
	 */
	wist_fow_each_entwy(dai, &sdev->dai_wist, wist) {
		if (!dai->name || stwcmp(wink_name, dai->name))
			continue;
		fow (i = 0; i < dai->numbew_configs; i++) {
			stwuct sof_dai_pwivate_data *pwivate = dai->pwivate;

			config = &pwivate->dai_config[i];
			if (config->ssp.fsync_wate == pawams_wate(pawams)) {
				dev_dbg(sdev->dev, "DAI config %d matches pcm hw pawams\n", i);
				dai->cuwwent_config = i;
				bweak;
			}
		}
	}
}

static int sof_ipc3_pcm_dai_wink_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				       stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_component *component = snd_soc_wtdcom_wookup(wtd, SOF_AUDIO_PCM_DWV_NAME);
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_sof_dai *dai = snd_sof_find_dai(component, (chaw *)wtd->dai_wink->name);
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_mask *fmt = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	stwuct sof_dai_pwivate_data *pwivate;
	stwuct snd_soc_dpcm *dpcm;

	if (!dai) {
		dev_eww(component->dev, "%s: No DAI found with name %s\n", __func__,
			wtd->dai_wink->name);
		wetuwn -EINVAW;
	}

	pwivate = dai->pwivate;
	if (!pwivate) {
		dev_eww(component->dev, "%s: No pwivate data found fow DAI %s\n", __func__,
			wtd->dai_wink->name);
		wetuwn -EINVAW;
	}

	/* wead fowmat fwom topowogy */
	snd_mask_none(fmt);

	switch (pwivate->comp_dai->config.fwame_fmt) {
	case SOF_IPC_FWAME_S16_WE:
		snd_mask_set_fowmat(fmt, SNDWV_PCM_FOWMAT_S16_WE);
		bweak;
	case SOF_IPC_FWAME_S24_4WE:
		snd_mask_set_fowmat(fmt, SNDWV_PCM_FOWMAT_S24_WE);
		bweak;
	case SOF_IPC_FWAME_S32_WE:
		snd_mask_set_fowmat(fmt, SNDWV_PCM_FOWMAT_S32_WE);
		bweak;
	defauwt:
		dev_eww(component->dev, "No avaiwabwe DAI fowmat!\n");
		wetuwn -EINVAW;
	}

	/* wead wate and channews fwom topowogy */
	switch (pwivate->dai_config->type) {
	case SOF_DAI_INTEW_SSP:
		/* seawch fow config to pcm pawams match, if not found use defauwt */
		ssp_dai_config_pcm_pawams_match(sdev, (chaw *)wtd->dai_wink->name, pawams);

		wate->min = pwivate->dai_config[dai->cuwwent_config].ssp.fsync_wate;
		wate->max = pwivate->dai_config[dai->cuwwent_config].ssp.fsync_wate;
		channews->min = pwivate->dai_config[dai->cuwwent_config].ssp.tdm_swots;
		channews->max = pwivate->dai_config[dai->cuwwent_config].ssp.tdm_swots;

		dev_dbg(component->dev, "wate_min: %d wate_max: %d\n", wate->min, wate->max);
		dev_dbg(component->dev, "channews_min: %d channews_max: %d\n",
			channews->min, channews->max);

		bweak;
	case SOF_DAI_INTEW_DMIC:
		/* DMIC onwy suppowts 16 ow 32 bit fowmats */
		if (pwivate->comp_dai->config.fwame_fmt == SOF_IPC_FWAME_S24_4WE) {
			dev_eww(component->dev, "Invawid fmt %d fow DAI type %d\n",
				pwivate->comp_dai->config.fwame_fmt,
				pwivate->dai_config->type);
		}
		bweak;
	case SOF_DAI_INTEW_HDA:
		/*
		 * HDAudio does not fowwow the defauwt twiggew
		 * sequence due to fiwmwawe impwementation
		 */
		fow_each_dpcm_fe(wtd, SNDWV_PCM_STWEAM_PWAYBACK, dpcm) {
			stwuct snd_soc_pcm_wuntime *fe = dpcm->fe;

			fe->dai_wink->twiggew[SNDWV_PCM_STWEAM_PWAYBACK] =
				SND_SOC_DPCM_TWIGGEW_POST;
		}
		bweak;
	case SOF_DAI_INTEW_AWH:
		/*
		 * Dai couwd wun with diffewent channew count compawed with
		 * fwont end, so get dai channew count fwom topowogy
		 */
		channews->min = pwivate->dai_config->awh.channews;
		channews->max = pwivate->dai_config->awh.channews;
		bweak;
	case SOF_DAI_IMX_ESAI:
		wate->min = pwivate->dai_config->esai.fsync_wate;
		wate->max = pwivate->dai_config->esai.fsync_wate;
		channews->min = pwivate->dai_config->esai.tdm_swots;
		channews->max = pwivate->dai_config->esai.tdm_swots;

		dev_dbg(component->dev, "wate_min: %d wate_max: %d\n", wate->min, wate->max);
		dev_dbg(component->dev, "channews_min: %d channews_max: %d\n",
			channews->min, channews->max);
		bweak;
	case SOF_DAI_MEDIATEK_AFE:
		wate->min = pwivate->dai_config->afe.wate;
		wate->max = pwivate->dai_config->afe.wate;
		channews->min = pwivate->dai_config->afe.channews;
		channews->max = pwivate->dai_config->afe.channews;

		snd_mask_none(fmt);

		switch (pwivate->dai_config->afe.fowmat) {
		case SOF_IPC_FWAME_S16_WE:
			snd_mask_set_fowmat(fmt, SNDWV_PCM_FOWMAT_S16_WE);
			bweak;
		case SOF_IPC_FWAME_S24_4WE:
			snd_mask_set_fowmat(fmt, SNDWV_PCM_FOWMAT_S24_WE);
			bweak;
		case SOF_IPC_FWAME_S32_WE:
			snd_mask_set_fowmat(fmt, SNDWV_PCM_FOWMAT_S32_WE);
			bweak;
		defauwt:
			dev_eww(component->dev, "Not avaiwabwe fowmat!\n");
			wetuwn -EINVAW;
		}

		dev_dbg(component->dev, "wate_min: %d wate_max: %d\n", wate->min, wate->max);
		dev_dbg(component->dev, "channews_min: %d channews_max: %d\n",
			channews->min, channews->max);
		bweak;
	case SOF_DAI_IMX_SAI:
		wate->min = pwivate->dai_config->sai.fsync_wate;
		wate->max = pwivate->dai_config->sai.fsync_wate;
		channews->min = pwivate->dai_config->sai.tdm_swots;
		channews->max = pwivate->dai_config->sai.tdm_swots;

		dev_dbg(component->dev, "wate_min: %d wate_max: %d\n", wate->min, wate->max);
		dev_dbg(component->dev, "channews_min: %d channews_max: %d\n",
			channews->min, channews->max);
		bweak;
	case SOF_DAI_AMD_BT:
		wate->min = pwivate->dai_config->acpbt.fsync_wate;
		wate->max = pwivate->dai_config->acpbt.fsync_wate;
		channews->min = pwivate->dai_config->acpbt.tdm_swots;
		channews->max = pwivate->dai_config->acpbt.tdm_swots;

		dev_dbg(component->dev,
			"AMD_BT wate_min: %d wate_max: %d\n", wate->min, wate->max);
		dev_dbg(component->dev, "AMD_BT channews_min: %d channews_max: %d\n",
			channews->min, channews->max);
		bweak;
	case SOF_DAI_AMD_SP:
	case SOF_DAI_AMD_SP_VIWTUAW:
		wate->min = pwivate->dai_config->acpsp.fsync_wate;
		wate->max = pwivate->dai_config->acpsp.fsync_wate;
		channews->min = pwivate->dai_config->acpsp.tdm_swots;
		channews->max = pwivate->dai_config->acpsp.tdm_swots;

		dev_dbg(component->dev,
			"AMD_SP wate_min: %d wate_max: %d\n", wate->min, wate->max);
		dev_dbg(component->dev, "AMD_SP channews_min: %d channews_max: %d\n",
			channews->min, channews->max);
		bweak;
	case SOF_DAI_AMD_HS:
	case SOF_DAI_AMD_HS_VIWTUAW:
		wate->min = pwivate->dai_config->acphs.fsync_wate;
		wate->max = pwivate->dai_config->acphs.fsync_wate;
		channews->min = pwivate->dai_config->acphs.tdm_swots;
		channews->max = pwivate->dai_config->acphs.tdm_swots;

		dev_dbg(component->dev,
			"AMD_HS channew_max: %d wate_max: %d\n", channews->max, wate->max);
		bweak;
	case SOF_DAI_AMD_DMIC:
		wate->min = pwivate->dai_config->acpdmic.pdm_wate;
		wate->max = pwivate->dai_config->acpdmic.pdm_wate;
		channews->min = pwivate->dai_config->acpdmic.pdm_ch;
		channews->max = pwivate->dai_config->acpdmic.pdm_ch;

		dev_dbg(component->dev,
			"AMD_DMIC wate_min: %d wate_max: %d\n", wate->min, wate->max);
		dev_dbg(component->dev, "AMD_DMIC channews_min: %d channews_max: %d\n",
			channews->min, channews->max);
		bweak;
	case SOF_DAI_IMX_MICFIW:
		wate->min = pwivate->dai_config->micfiw.pdm_wate;
		wate->max = pwivate->dai_config->micfiw.pdm_wate;
		channews->min = pwivate->dai_config->micfiw.pdm_ch;
		channews->max = pwivate->dai_config->micfiw.pdm_ch;

		dev_dbg(component->dev,
			"MICFIW PDM wate_min: %d wate_max: %d\n", wate->min, wate->max);
		dev_dbg(component->dev, "MICFIW PDM channews_min: %d channews_max: %d\n",
			channews->min, channews->max);
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid DAI type %d\n", pwivate->dai_config->type);
		bweak;
	}

	wetuwn 0;
}

const stwuct sof_ipc_pcm_ops ipc3_pcm_ops = {
	.hw_pawams = sof_ipc3_pcm_hw_pawams,
	.hw_fwee = sof_ipc3_pcm_hw_fwee,
	.twiggew = sof_ipc3_pcm_twiggew,
	.dai_wink_fixup = sof_ipc3_pcm_dai_wink_fixup,
	.weset_hw_pawams_duwing_stop = twue,
};
