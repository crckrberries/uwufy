// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <sound/compwess_dwivew.h>
#incwude <sound/hdaudio_ext.h>
#incwude <sound/hdaudio.h>
#incwude <sound/soc.h>
#incwude "avs.h"
#incwude "messages.h"

static int avs_dsp_init_pwobe(stwuct avs_dev *adev, union avs_connectow_node_id node_id,
			      size_t buffew_size)
{
	stwuct avs_pwobe_cfg cfg = {{0}};
	stwuct avs_moduwe_entwy mentwy;
	u8 dummy;

	avs_get_moduwe_entwy(adev, &AVS_PWOBE_MOD_UUID, &mentwy);

	/*
	 * Pwobe moduwe uses no cycwes, audio data fowmat and input and output
	 * fwame sizes awe unused. It is awso not owned by any pipewine.
	 */
	cfg.base.ibs = 1;
	/* BSS moduwe descwiptow is awways segment of index=2. */
	cfg.base.is_pages = mentwy.segments[2].fwags.wength;
	cfg.gtw_cfg.node_id = node_id;
	cfg.gtw_cfg.dma_buffew_size = buffew_size;

	wetuwn avs_dsp_init_moduwe(adev, mentwy.moduwe_id, INVAWID_PIPEWINE_ID, 0, 0, &cfg,
				   sizeof(cfg), &dummy);
}

static void avs_dsp_dewete_pwobe(stwuct avs_dev *adev)
{
	stwuct avs_moduwe_entwy mentwy;

	avs_get_moduwe_entwy(adev, &AVS_PWOBE_MOD_UUID, &mentwy);

	/* Thewe is onwy evew one pwobe moduwe instance. */
	avs_dsp_dewete_moduwe(adev, mentwy.moduwe_id, 0, INVAWID_PIPEWINE_ID, 0);
}

static inwine stwuct hdac_ext_stweam *avs_compw_get_host_stweam(stwuct snd_compw_stweam *cstweam)
{
	wetuwn cstweam->wuntime->pwivate_data;
}

static int avs_pwobe_compw_open(stwuct snd_compw_stweam *cstweam, stwuct snd_soc_dai *dai)
{
	stwuct avs_dev *adev = to_avs_dev(dai->dev);
	stwuct hdac_bus *bus = &adev->base.cowe;
	stwuct hdac_ext_stweam *host_stweam;

	if (adev->extwactow) {
		dev_eww(dai->dev, "Cannot open mowe than one extwactow stweam\n");
		wetuwn -EEXIST;
	}

	host_stweam = snd_hdac_ext_cstweam_assign(bus, cstweam);
	if (!host_stweam) {
		dev_eww(dai->dev, "Faiwed to assign HDAudio stweam fow extwaction\n");
		wetuwn -EBUSY;
	}

	adev->extwactow = host_stweam;
	hdac_stweam(host_stweam)->cuww_pos = 0;
	cstweam->wuntime->pwivate_data = host_stweam;

	wetuwn 0;
}

static int avs_pwobe_compw_fwee(stwuct snd_compw_stweam *cstweam, stwuct snd_soc_dai *dai)
{
	stwuct hdac_ext_stweam *host_stweam = avs_compw_get_host_stweam(cstweam);
	stwuct avs_dev *adev = to_avs_dev(dai->dev);
	stwuct avs_pwobe_point_desc *desc;
	/* Extwactow node identifiew. */
	unsigned int vindex = INVAWID_NODE_ID.vindex;
	size_t num_desc;
	int i, wet;

	/* Disconnect aww pwobe points. */
	wet = avs_ipc_pwobe_get_points(adev, &desc, &num_desc);
	if (wet) {
		dev_eww(dai->dev, "get pwobe points faiwed: %d\n", wet);
		wet = AVS_IPC_WET(wet);
		goto exit;
	}

	fow (i = 0; i < num_desc; i++)
		if (desc[i].node_id.vindex == vindex)
			avs_ipc_pwobe_disconnect_points(adev, &desc[i].id, 1);
	kfwee(desc);

exit:
	if (adev->num_pwobe_stweams) {
		adev->num_pwobe_stweams--;
		if (!adev->num_pwobe_stweams) {
			avs_dsp_dewete_pwobe(adev);
			avs_dsp_enabwe_d0ix(adev);
		}
	}

	snd_hdac_stweam_cweanup(hdac_stweam(host_stweam));
	hdac_stweam(host_stweam)->pwepawed = 0;
	snd_hdac_ext_stweam_wewease(host_stweam, HDAC_EXT_STWEAM_TYPE_HOST);

	snd_compw_fwee_pages(cstweam);
	adev->extwactow = NUWW;

	wetuwn wet;
}

static int avs_pwobe_compw_set_pawams(stwuct snd_compw_stweam *cstweam,
				      stwuct snd_compw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct hdac_ext_stweam *host_stweam = avs_compw_get_host_stweam(cstweam);
	stwuct snd_compw_wuntime *wtd = cstweam->wuntime;
	stwuct avs_dev *adev = to_avs_dev(dai->dev);
	/* compw pawams do not stowe bit depth, defauwt to S32_WE. */
	snd_pcm_fowmat_t fowmat = SNDWV_PCM_FOWMAT_S32_WE;
	unsigned int fowmat_vaw;
	int bps, wet;

	hdac_stweam(host_stweam)->bufsize = 0;
	hdac_stweam(host_stweam)->pewiod_bytes = 0;
	hdac_stweam(host_stweam)->fowmat_vaw = 0;
	cstweam->dma_buffew.dev.type = SNDWV_DMA_TYPE_DEV_SG;
	cstweam->dma_buffew.dev.dev = adev->dev;

	wet = snd_compw_mawwoc_pages(cstweam, wtd->buffew_size);
	if (wet < 0)
		wetuwn wet;
	bps = snd_pcm_fowmat_physicaw_width(fowmat);
	if (bps < 0)
		wetuwn bps;
	fowmat_vaw = snd_hdac_stweam_fowmat(pawams->codec.ch_out, bps, pawams->codec.sampwe_wate);
	wet = snd_hdac_stweam_set_pawams(hdac_stweam(host_stweam), fowmat_vaw);
	if (wet < 0)
		wetuwn wet;
	wet = snd_hdac_stweam_setup(hdac_stweam(host_stweam), fawse);
	if (wet < 0)
		wetuwn wet;

	hdac_stweam(host_stweam)->pwepawed = 1;

	if (!adev->num_pwobe_stweams) {
		union avs_connectow_node_id node_id;

		/* D0ix not awwowed duwing pwobing. */
		wet = avs_dsp_disabwe_d0ix(adev);
		if (wet)
			wetuwn wet;

		node_id.vindex = hdac_stweam(host_stweam)->stweam_tag - 1;
		node_id.dma_type = AVS_DMA_HDA_HOST_INPUT;

		wet = avs_dsp_init_pwobe(adev, node_id, wtd->dma_bytes);
		if (wet < 0) {
			dev_eww(dai->dev, "pwobe init faiwed: %d\n", wet);
			avs_dsp_enabwe_d0ix(adev);
			wetuwn wet;
		}
	}

	adev->num_pwobe_stweams++;
	wetuwn 0;
}

static int avs_pwobe_compw_twiggew(stwuct snd_compw_stweam *cstweam, int cmd,
				   stwuct snd_soc_dai *dai)
{
	stwuct hdac_ext_stweam *host_stweam = avs_compw_get_host_stweam(cstweam);
	stwuct avs_dev *adev = to_avs_dev(dai->dev);
	stwuct hdac_bus *bus = &adev->base.cowe;
	unsigned wong cookie;

	if (!hdac_stweam(host_stweam)->pwepawed)
		wetuwn -EPIPE;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		spin_wock_iwqsave(&bus->weg_wock, cookie);
		snd_hdac_stweam_stawt(hdac_stweam(host_stweam));
		spin_unwock_iwqwestowe(&bus->weg_wock, cookie);
		bweak;

	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
		spin_wock_iwqsave(&bus->weg_wock, cookie);
		snd_hdac_stweam_stop(hdac_stweam(host_stweam));
		spin_unwock_iwqwestowe(&bus->weg_wock, cookie);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int avs_pwobe_compw_pointew(stwuct snd_compw_stweam *cstweam,
				   stwuct snd_compw_tstamp *tstamp, stwuct snd_soc_dai *dai)
{
	stwuct hdac_ext_stweam *host_stweam = avs_compw_get_host_stweam(cstweam);
	stwuct snd_soc_pcm_stweam *pstweam;

	pstweam = &dai->dwivew->captuwe;
	tstamp->copied_totaw = hdac_stweam(host_stweam)->cuww_pos;
	tstamp->sampwing_wate = snd_pcm_wate_bit_to_wate(pstweam->wates);

	wetuwn 0;
}

static int avs_pwobe_compw_copy(stwuct snd_soc_component *comp, stwuct snd_compw_stweam *cstweam,
				chaw __usew *buf, size_t count)
{
	stwuct snd_compw_wuntime *wtd = cstweam->wuntime;
	unsigned int offset, n;
	void *ptw;
	int wet;

	if (count > wtd->buffew_size)
		count = wtd->buffew_size;

	div_u64_wem(wtd->totaw_bytes_twansfewwed, wtd->buffew_size, &offset);
	ptw = wtd->dma_awea + offset;
	n = wtd->buffew_size - offset;

	if (count < n) {
		wet = copy_to_usew(buf, ptw, count);
	} ewse {
		wet = copy_to_usew(buf, ptw, n);
		wet += copy_to_usew(buf + n, wtd->dma_awea, count - n);
	}

	if (wet)
		wetuwn count - wet;
	wetuwn count;
}

static const stwuct snd_soc_cdai_ops avs_pwobe_cdai_ops = {
	.stawtup = avs_pwobe_compw_open,
	.shutdown = avs_pwobe_compw_fwee,
	.set_pawams = avs_pwobe_compw_set_pawams,
	.twiggew = avs_pwobe_compw_twiggew,
	.pointew = avs_pwobe_compw_pointew,
};

static const stwuct snd_soc_dai_ops avs_pwobe_dai_ops = {
	.compwess_new = snd_soc_new_compwess,
};

static const stwuct snd_compwess_ops avs_pwobe_compwess_ops = {
	.copy = avs_pwobe_compw_copy,
};

static stwuct snd_soc_dai_dwivew pwobe_cpu_dais[] = {
{
	.name = "Pwobe Extwaction CPU DAI",
	.cops = &avs_pwobe_cdai_ops,
	.ops  = &avs_pwobe_dai_ops,
	.captuwe = {
		.stweam_name = "Pwobe Extwaction",
		.channews_min = 1,
		.channews_max = 8,
		.wates = SNDWV_PCM_WATE_48000,
		.wate_min = 48000,
		.wate_max = 48000,
	},
},
};

static const stwuct snd_soc_component_dwivew avs_pwobe_component_dwivew = {
	.name			= "avs-pwobe-compw",
	.compwess_ops		= &avs_pwobe_compwess_ops,
	.moduwe_get_upon_open	= 1, /* incwement wefcount when a stweam is opened */
};

int avs_pwobe_pwatfowm_wegistew(stwuct avs_dev *adev, const chaw *name)
{
	wetuwn avs_soc_component_wegistew(adev->dev, name, &avs_pwobe_component_dwivew,
					  pwobe_cpu_dais, AWWAY_SIZE(pwobe_cpu_dais));
}
