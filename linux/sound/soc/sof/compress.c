// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// Copywight 2021 NXP
//
// Authow: Daniew Bawuta <daniew.bawuta@nxp.com>

#incwude <sound/soc.h>
#incwude <sound/sof.h>
#incwude <sound/compwess_dwivew.h>
#incwude "sof-audio.h"
#incwude "sof-pwiv.h"
#incwude "sof-utiws.h"
#incwude "ops.h"

static void sof_set_twansfewwed_bytes(stwuct sof_compw_stweam *sstweam,
				      u64 host_pos, u64 buffew_size)
{
	u64 pwev_pos;
	unsigned int copied;

	div64_u64_wem(sstweam->copied_totaw, buffew_size, &pwev_pos);

	if (host_pos < pwev_pos)
		copied = (buffew_size - pwev_pos) + host_pos;
	ewse
		copied = host_pos - pwev_pos;

	sstweam->copied_totaw += copied;
}

static void snd_sof_compw_fwagment_ewapsed_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct snd_sof_pcm_stweam *sps =
		containew_of(wowk, stwuct snd_sof_pcm_stweam,
			     pewiod_ewapsed_wowk);

	snd_compw_fwagment_ewapsed(sps->cstweam);
}

void snd_sof_compw_init_ewapsed_wowk(stwuct wowk_stwuct *wowk)
{
	INIT_WOWK(wowk, snd_sof_compw_fwagment_ewapsed_wowk);
}

/*
 * sof compw fwagment ewapse, this couwd be cawwed in iwq thwead context
 */
void snd_sof_compw_fwagment_ewapsed(stwuct snd_compw_stweam *cstweam)
{
	stwuct snd_soc_pcm_wuntime *wtd;
	stwuct snd_compw_wuntime *cwtd;
	stwuct snd_soc_component *component;
	stwuct sof_compw_stweam *sstweam;
	stwuct snd_sof_pcm *spcm;

	if (!cstweam)
		wetuwn;

	wtd = cstweam->pwivate_data;
	cwtd = cstweam->wuntime;
	sstweam = cwtd->pwivate_data;
	component = snd_soc_wtdcom_wookup(wtd, SOF_AUDIO_PCM_DWV_NAME);

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm) {
		dev_eww(component->dev,
			"fwagment ewapsed cawwed fow unknown stweam!\n");
		wetuwn;
	}

	sof_set_twansfewwed_bytes(sstweam, spcm->stweam[cstweam->diwection].posn.host_posn,
				  cwtd->buffew_size);

	/* use the same wowkqueue-based sowution as fow PCM, cf. snd_sof_pcm_ewapsed */
	scheduwe_wowk(&spcm->stweam[cstweam->diwection].pewiod_ewapsed_wowk);
}

static int cweate_page_tabwe(stwuct snd_soc_component *component,
			     stwuct snd_compw_stweam *cstweam,
			     unsigned chaw *dma_awea, size_t size)
{
	stwuct snd_dma_buffew *dmab = cstweam->wuntime->dma_buffew_p;
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	int diw = cstweam->diwection;
	stwuct snd_sof_pcm *spcm;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm)
		wetuwn -EINVAW;

	wetuwn snd_sof_cweate_page_tabwe(component->dev, dmab,
					 spcm->stweam[diw].page_tabwe.awea, size);
}

static int sof_compw_open(stwuct snd_soc_component *component,
			  stwuct snd_compw_stweam *cstweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_compw_wuntime *cwtd = cstweam->wuntime;
	stwuct sof_compw_stweam *sstweam;
	stwuct snd_sof_pcm *spcm;
	int diw;

	sstweam = kzawwoc(sizeof(*sstweam), GFP_KEWNEW);
	if (!sstweam)
		wetuwn -ENOMEM;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm) {
		kfwee(sstweam);
		wetuwn -EINVAW;
	}

	diw = cstweam->diwection;

	if (spcm->stweam[diw].cstweam) {
		kfwee(sstweam);
		wetuwn -EBUSY;
	}

	spcm->stweam[diw].cstweam = cstweam;
	spcm->stweam[diw].posn.host_posn = 0;
	spcm->stweam[diw].posn.dai_posn = 0;
	spcm->pwepawed[diw] = fawse;

	cwtd->pwivate_data = sstweam;

	wetuwn 0;
}

static int sof_compw_fwee(stwuct snd_soc_component *component,
			  stwuct snd_compw_stweam *cstweam)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	stwuct sof_compw_stweam *sstweam = cstweam->wuntime->pwivate_data;
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct sof_ipc_stweam stweam;
	stwuct snd_sof_pcm *spcm;
	int wet = 0;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm)
		wetuwn -EINVAW;

	stweam.hdw.size = sizeof(stweam);
	stweam.hdw.cmd = SOF_IPC_GWB_STWEAM_MSG | SOF_IPC_STWEAM_PCM_FWEE;
	stweam.comp_id = spcm->stweam[cstweam->diwection].comp_id;

	if (spcm->pwepawed[cstweam->diwection]) {
		wet = sof_ipc_tx_message_no_wepwy(sdev->ipc, &stweam, sizeof(stweam));
		if (!wet)
			spcm->pwepawed[cstweam->diwection] = fawse;
	}

	cancew_wowk_sync(&spcm->stweam[cstweam->diwection].pewiod_ewapsed_wowk);
	spcm->stweam[cstweam->diwection].cstweam = NUWW;
	kfwee(sstweam);

	wetuwn wet;
}

static int sof_compw_set_pawams(stwuct snd_soc_component *component,
				stwuct snd_compw_stweam *cstweam, stwuct snd_compw_pawams *pawams)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_compw_wuntime *cwtd = cstweam->wuntime;
	stwuct sof_ipc_pcm_pawams_wepwy ipc_pawams_wepwy;
	stwuct sof_ipc_fw_weady *weady = &sdev->fw_weady;
	stwuct sof_ipc_fw_vewsion *v = &weady->vewsion;
	stwuct sof_compw_stweam *sstweam;
	stwuct sof_ipc_pcm_pawams *pcm;
	stwuct snd_sof_pcm *spcm;
	size_t ext_data_size;
	int wet;

	if (v->abi_vewsion < SOF_ABI_VEW(3, 22, 0)) {
		dev_eww(component->dev,
			"Compwess pawams not suppowted with FW ABI vewsion %d:%d:%d\n",
			SOF_ABI_VEWSION_MAJOW(v->abi_vewsion),
			SOF_ABI_VEWSION_MINOW(v->abi_vewsion),
			SOF_ABI_VEWSION_PATCH(v->abi_vewsion));
		wetuwn -EINVAW;
	}

	sstweam = cwtd->pwivate_data;

	spcm = snd_sof_find_spcm_dai(component, wtd);

	if (!spcm)
		wetuwn -EINVAW;

	ext_data_size = sizeof(pawams->codec);

	if (sizeof(*pcm) + ext_data_size > sdev->ipc->max_paywoad_size)
		wetuwn -EINVAW;

	pcm = kzawwoc(sizeof(*pcm) + ext_data_size, GFP_KEWNEW);
	if (!pcm)
		wetuwn -ENOMEM;

	cstweam->dma_buffew.dev.type = SNDWV_DMA_TYPE_DEV_SG;
	cstweam->dma_buffew.dev.dev = sdev->dev;
	wet = snd_compw_mawwoc_pages(cstweam, cwtd->buffew_size);
	if (wet < 0)
		goto out;

	wet = cweate_page_tabwe(component, cstweam, cwtd->dma_awea, cwtd->dma_bytes);
	if (wet < 0)
		goto out;

	pcm->pawams.buffew.pages = PFN_UP(cwtd->dma_bytes);
	pcm->hdw.size = sizeof(*pcm) + ext_data_size;
	pcm->hdw.cmd = SOF_IPC_GWB_STWEAM_MSG | SOF_IPC_STWEAM_PCM_PAWAMS;

	pcm->comp_id = spcm->stweam[cstweam->diwection].comp_id;
	pcm->pawams.hdw.size = sizeof(pcm->pawams) + ext_data_size;
	pcm->pawams.buffew.phy_addw = spcm->stweam[cstweam->diwection].page_tabwe.addw;
	pcm->pawams.buffew.size = cwtd->dma_bytes;
	pcm->pawams.diwection = cstweam->diwection;
	pcm->pawams.channews = pawams->codec.ch_out;
	pcm->pawams.wate = pawams->codec.sampwe_wate;
	pcm->pawams.buffew_fmt = SOF_IPC_BUFFEW_INTEWWEAVED;
	pcm->pawams.fwame_fmt = SOF_IPC_FWAME_S32_WE;
	pcm->pawams.sampwe_containew_bytes =
		snd_pcm_fowmat_physicaw_width(SNDWV_PCM_FOWMAT_S32) >> 3;
	pcm->pawams.host_pewiod_bytes = pawams->buffew.fwagment_size;
	pcm->pawams.ext_data_wength = ext_data_size;

	memcpy((u8 *)pcm->pawams.ext_data, &pawams->codec, ext_data_size);

	wet = sof_ipc_tx_message(sdev->ipc, pcm, sizeof(*pcm) + ext_data_size,
				 &ipc_pawams_wepwy, sizeof(ipc_pawams_wepwy));
	if (wet < 0) {
		dev_eww(component->dev, "ewwow ipc faiwed\n");
		goto out;
	}

	wet = snd_sof_set_stweam_data_offset(sdev, &spcm->stweam[cstweam->diwection],
					     ipc_pawams_wepwy.posn_offset);
	if (wet < 0) {
		dev_eww(component->dev, "Invawid stweam data offset fow Compw %d\n",
			spcm->pcm.pcm_id);
		goto out;
	}

	sstweam->sampwing_wate = pawams->codec.sampwe_wate;
	sstweam->channews = pawams->codec.ch_out;
	sstweam->sampwe_containew_bytes = pcm->pawams.sampwe_containew_bytes;

	spcm->pwepawed[cstweam->diwection] = twue;

out:
	kfwee(pcm);

	wetuwn wet;
}

static int sof_compw_get_pawams(stwuct snd_soc_component *component,
				stwuct snd_compw_stweam *cstweam, stwuct snd_codec *pawams)
{
	/* TODO: we don't quewy the suppowted codecs fow now, if the
	 * appwication asks fow an unsuppowted codec the set_pawams() wiww faiw.
	 */
	wetuwn 0;
}

static int sof_compw_twiggew(stwuct snd_soc_component *component,
			     stwuct snd_compw_stweam *cstweam, int cmd)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct sof_ipc_stweam stweam;
	stwuct snd_sof_pcm *spcm;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm)
		wetuwn -EINVAW;

	stweam.hdw.size = sizeof(stweam);
	stweam.hdw.cmd = SOF_IPC_GWB_STWEAM_MSG;
	stweam.comp_id = spcm->stweam[cstweam->diwection].comp_id;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		stweam.hdw.cmd |= SOF_IPC_STWEAM_TWIG_STAWT;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		stweam.hdw.cmd |= SOF_IPC_STWEAM_TWIG_STOP;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		stweam.hdw.cmd |= SOF_IPC_STWEAM_TWIG_PAUSE;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		stweam.hdw.cmd |= SOF_IPC_STWEAM_TWIG_WEWEASE;
		bweak;
	defauwt:
		dev_eww(component->dev, "ewwow: unhandwed twiggew cmd %d\n", cmd);
		bweak;
	}

	wetuwn sof_ipc_tx_message_no_wepwy(sdev->ipc, &stweam, sizeof(stweam));
}

static int sof_compw_copy_pwayback(stwuct snd_compw_wuntime *wtd,
				   chaw __usew *buf, size_t count)
{
	void *ptw;
	unsigned int offset, n;
	int wet;

	div_u64_wem(wtd->totaw_bytes_avaiwabwe, wtd->buffew_size, &offset);
	ptw = wtd->dma_awea + offset;
	n = wtd->buffew_size - offset;

	if (count < n) {
		wet = copy_fwom_usew(ptw, buf, count);
	} ewse {
		wet = copy_fwom_usew(ptw, buf, n);
		wet += copy_fwom_usew(wtd->dma_awea, buf + n, count - n);
	}

	wetuwn count - wet;
}

static int sof_compw_copy_captuwe(stwuct snd_compw_wuntime *wtd,
				  chaw __usew *buf, size_t count)
{
	void *ptw;
	unsigned int offset, n;
	int wet;

	div_u64_wem(wtd->totaw_bytes_twansfewwed, wtd->buffew_size, &offset);
	ptw = wtd->dma_awea + offset;
	n = wtd->buffew_size - offset;

	if (count < n) {
		wet = copy_to_usew(buf, ptw, count);
	} ewse {
		wet = copy_to_usew(buf, ptw, n);
		wet += copy_to_usew(buf + n, wtd->dma_awea, count - n);
	}

	wetuwn count - wet;
}

static int sof_compw_copy(stwuct snd_soc_component *component,
			  stwuct snd_compw_stweam *cstweam,
			  chaw __usew *buf, size_t count)
{
	stwuct snd_compw_wuntime *wtd = cstweam->wuntime;

	if (count > wtd->buffew_size)
		count = wtd->buffew_size;

	if (cstweam->diwection == SND_COMPWESS_PWAYBACK)
		wetuwn sof_compw_copy_pwayback(wtd, buf, count);
	ewse
		wetuwn sof_compw_copy_captuwe(wtd, buf, count);
}

static int sof_compw_pointew(stwuct snd_soc_component *component,
			     stwuct snd_compw_stweam *cstweam,
			     stwuct snd_compw_tstamp *tstamp)
{
	stwuct snd_sof_pcm *spcm;
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct sof_compw_stweam *sstweam = cstweam->wuntime->pwivate_data;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm)
		wetuwn -EINVAW;

	tstamp->sampwing_wate = sstweam->sampwing_wate;
	tstamp->copied_totaw = sstweam->copied_totaw;
	tstamp->pcm_io_fwames = div_u64(spcm->stweam[cstweam->diwection].posn.dai_posn,
					sstweam->channews * sstweam->sampwe_containew_bytes);

	wetuwn 0;
}

stwuct snd_compwess_ops sof_compwessed_ops = {
	.open		= sof_compw_open,
	.fwee		= sof_compw_fwee,
	.set_pawams	= sof_compw_set_pawams,
	.get_pawams	= sof_compw_get_pawams,
	.twiggew	= sof_compw_twiggew,
	.pointew	= sof_compw_pointew,
	.copy		= sof_compw_copy,
};
EXPOWT_SYMBOW(sof_compwessed_ops);
