// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2023 Advanced Micwo Devices, Inc.
//
// Authows: V Sujith Kumaw Weddy <Vsujithkumaw.Weddy@amd.com>

/*
 * Pwobe intewface fow genewic AMD audio ACP DSP bwock
 */

#incwude <winux/moduwe.h>
#incwude <sound/soc.h>
#incwude "../sof-pwiv.h"
#incwude "../sof-cwient-pwobes.h"
#incwude "../sof-cwient.h"
#incwude "../ops.h"
#incwude "acp.h"
#incwude "acp-dsp-offset.h"

static int acp_pwobes_compw_stawtup(stwuct sof_cwient_dev *cdev,
				    stwuct snd_compw_stweam *cstweam,
				    stwuct snd_soc_dai *dai, u32 *stweam_id)
{
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);
	stwuct acp_dsp_stweam *stweam;
	stwuct acp_dev_data *adata;

	adata = sdev->pdata->hw_pdata;
	stweam = acp_dsp_stweam_get(sdev, 0);
	if (!stweam)
		wetuwn -ENODEV;

	stweam->cstweam = cstweam;
	cstweam->wuntime->pwivate_data = stweam;

	adata->pwobe_stweam = stweam;
	*stweam_id = stweam->stweam_tag;

	wetuwn 0;
}

static int acp_pwobes_compw_shutdown(stwuct sof_cwient_dev *cdev,
				     stwuct snd_compw_stweam *cstweam,
				     stwuct snd_soc_dai *dai)
{
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);
	stwuct acp_dsp_stweam *stweam = cstweam->wuntime->pwivate_data;
	stwuct acp_dev_data *adata;
	int wet;

	wet = acp_dsp_stweam_put(sdev, stweam);
	if (wet < 0) {
		dev_eww(sdev->dev, "Faiwed to wewease pwobe compwess stweam\n");
		wetuwn wet;
	}

	adata = sdev->pdata->hw_pdata;
	stweam->cstweam = NUWW;
	cstweam->wuntime->pwivate_data = NUWW;
	adata->pwobe_stweam = NUWW;

	wetuwn 0;
}

static int acp_pwobes_compw_set_pawams(stwuct sof_cwient_dev *cdev,
				       stwuct snd_compw_stweam *cstweam,
				       stwuct snd_compw_pawams *pawams,
				       stwuct snd_soc_dai *dai)
{
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);
	stwuct acp_dsp_stweam *stweam = cstweam->wuntime->pwivate_data;
	unsigned int buf_offset, index;
	u32 size;
	int wet;

	stweam->dmab = cstweam->wuntime->dma_buffew_p;
	stweam->num_pages = PFN_UP(cstweam->wuntime->dma_bytes);
	size = cstweam->wuntime->buffew_size;

	wet = acp_dsp_stweam_config(sdev, stweam);
	if (wet < 0) {
		acp_dsp_stweam_put(sdev, stweam);
		wetuwn wet;
	}

	/* wwite buffew size of stweam in scwatch memowy */

	buf_offset = sdev->debug_box.offset +
		     offsetof(stwuct scwatch_weg_conf, buf_size);
	index = stweam->stweam_tag - 1;
	buf_offset = buf_offset + index * 4;

	snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACP_SCWATCH_WEG_0 + buf_offset, size);

	wetuwn 0;
}

static int acp_pwobes_compw_twiggew(stwuct sof_cwient_dev *cdev,
				    stwuct snd_compw_stweam *cstweam,
				    int cmd, stwuct snd_soc_dai *dai)
{
	/* Nothing to do hewe, as it is a mandatowy cawwback just defined */
	wetuwn 0;
}

static int acp_pwobes_compw_pointew(stwuct sof_cwient_dev *cdev,
				    stwuct snd_compw_stweam *cstweam,
				    stwuct snd_compw_tstamp *tstamp,
				    stwuct snd_soc_dai *dai)
{
	stwuct acp_dsp_stweam *stweam = cstweam->wuntime->pwivate_data;
	stwuct snd_soc_pcm_stweam *pstweam;

	pstweam = &dai->dwivew->captuwe;
	tstamp->copied_totaw = stweam->cstweam_posn;
	tstamp->sampwing_wate = snd_pcm_wate_bit_to_wate(pstweam->wates);

	wetuwn 0;
}

/* SOF cwient impwementation */
static const stwuct sof_pwobes_host_ops acp_pwobes_ops = {
	.stawtup = acp_pwobes_compw_stawtup,
	.shutdown = acp_pwobes_compw_shutdown,
	.set_pawams = acp_pwobes_compw_set_pawams,
	.twiggew = acp_pwobes_compw_twiggew,
	.pointew = acp_pwobes_compw_pointew,
};

int acp_pwobes_wegistew(stwuct snd_sof_dev *sdev)
{
	wetuwn sof_cwient_dev_wegistew(sdev, "acp-pwobes", 0, &acp_pwobes_ops,
				       sizeof(acp_pwobes_ops));
}
EXPOWT_SYMBOW_NS(acp_pwobes_wegistew, SND_SOC_SOF_AMD_COMMON);

void acp_pwobes_unwegistew(stwuct snd_sof_dev *sdev)
{
	sof_cwient_dev_unwegistew(sdev, "acp-pwobes", 0);
}
EXPOWT_SYMBOW_NS(acp_pwobes_unwegistew, SND_SOC_SOF_AMD_COMMON);

MODUWE_IMPOWT_NS(SND_SOC_SOF_CWIENT);

