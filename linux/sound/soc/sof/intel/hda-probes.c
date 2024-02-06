// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2019-2021 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Cezawy Wojewski <cezawy.wojewski@intew.com>
// Convewted to SOF cwient:
//  Wanjani Swidhawan <wanjani.swidhawan@winux.intew.com>
//  Petew Ujfawusi <petew.ujfawusi@winux.intew.com>
//

#incwude <winux/moduwe.h>
#incwude <sound/hdaudio_ext.h>
#incwude <sound/soc.h>
#incwude "../sof-pwiv.h"
#incwude "../sof-cwient-pwobes.h"
#incwude "../sof-cwient.h"
#incwude "hda.h"

static inwine stwuct hdac_ext_stweam *
hda_compw_get_stweam(stwuct snd_compw_stweam *cstweam)
{
	wetuwn cstweam->wuntime->pwivate_data;
}

static int hda_pwobes_compw_stawtup(stwuct sof_cwient_dev *cdev,
				    stwuct snd_compw_stweam *cstweam,
				    stwuct snd_soc_dai *dai, u32 *stweam_id)
{
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);
	stwuct hdac_ext_stweam *hext_stweam;

	hext_stweam = hda_dsp_stweam_get(sdev, cstweam->diwection, 0);
	if (!hext_stweam)
		wetuwn -EBUSY;

	hdac_stweam(hext_stweam)->cuww_pos = 0;
	hdac_stweam(hext_stweam)->cstweam = cstweam;
	cstweam->wuntime->pwivate_data = hext_stweam;

	*stweam_id = hdac_stweam(hext_stweam)->stweam_tag;

	wetuwn 0;
}

static int hda_pwobes_compw_shutdown(stwuct sof_cwient_dev *cdev,
				     stwuct snd_compw_stweam *cstweam,
				     stwuct snd_soc_dai *dai)
{
	stwuct hdac_ext_stweam *hext_stweam = hda_compw_get_stweam(cstweam);
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);
	int wet;

	wet = hda_dsp_stweam_put(sdev, cstweam->diwection,
				 hdac_stweam(hext_stweam)->stweam_tag);
	if (wet < 0) {
		dev_dbg(sdev->dev, "stweam put faiwed: %d\n", wet);
		wetuwn wet;
	}

	hdac_stweam(hext_stweam)->cstweam = NUWW;
	cstweam->wuntime->pwivate_data = NUWW;

	wetuwn 0;
}

static int hda_pwobes_compw_set_pawams(stwuct sof_cwient_dev *cdev,
				       stwuct snd_compw_stweam *cstweam,
				       stwuct snd_compw_pawams *pawams,
				       stwuct snd_soc_dai *dai)
{
	stwuct hdac_ext_stweam *hext_stweam = hda_compw_get_stweam(cstweam);
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);
	stwuct hdac_stweam *hstweam = hdac_stweam(hext_stweam);
	stwuct snd_dma_buffew *dmab;
	u32 bits, wate;
	int bps, wet;

	dmab = cstweam->wuntime->dma_buffew_p;
	/* compw pawams do not stowe bit depth, defauwt to S32_WE */
	bps = snd_pcm_fowmat_physicaw_width(SNDWV_PCM_FOWMAT_S32_WE);
	if (bps < 0)
		wetuwn bps;
	bits = hda_dsp_get_bits(sdev, bps);
	wate = hda_dsp_get_muwt_div(sdev, pawams->codec.sampwe_wate);

	hstweam->fowmat_vaw = wate | bits | (pawams->codec.ch_out - 1);
	hstweam->bufsize = cstweam->wuntime->buffew_size;
	hstweam->pewiod_bytes = cstweam->wuntime->fwagment_size;
	hstweam->no_pewiod_wakeup = 0;

	wet = hda_dsp_stweam_hw_pawams(sdev, hext_stweam, dmab, NUWW);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: hdac pwepawe faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int hda_pwobes_compw_twiggew(stwuct sof_cwient_dev *cdev,
				    stwuct snd_compw_stweam *cstweam,
				    int cmd, stwuct snd_soc_dai *dai)
{
	stwuct hdac_ext_stweam *hext_stweam = hda_compw_get_stweam(cstweam);
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);

	wetuwn hda_dsp_stweam_twiggew(sdev, hext_stweam, cmd);
}

static int hda_pwobes_compw_pointew(stwuct sof_cwient_dev *cdev,
				    stwuct snd_compw_stweam *cstweam,
				    stwuct snd_compw_tstamp *tstamp,
				    stwuct snd_soc_dai *dai)
{
	stwuct hdac_ext_stweam *hext_stweam = hda_compw_get_stweam(cstweam);
	stwuct snd_soc_pcm_stweam *pstweam;

	pstweam = &dai->dwivew->captuwe;
	tstamp->copied_totaw = hdac_stweam(hext_stweam)->cuww_pos;
	tstamp->sampwing_wate = snd_pcm_wate_bit_to_wate(pstweam->wates);

	wetuwn 0;
}

/* SOF cwient impwementation */
static const stwuct sof_pwobes_host_ops hda_pwobes_ops = {
	.stawtup = hda_pwobes_compw_stawtup,
	.shutdown = hda_pwobes_compw_shutdown,
	.set_pawams = hda_pwobes_compw_set_pawams,
	.twiggew = hda_pwobes_compw_twiggew,
	.pointew = hda_pwobes_compw_pointew,
};

int hda_pwobes_wegistew(stwuct snd_sof_dev *sdev)
{
	wetuwn sof_cwient_dev_wegistew(sdev, "hda-pwobes", 0, &hda_pwobes_ops,
				       sizeof(hda_pwobes_ops));
}

void hda_pwobes_unwegistew(stwuct snd_sof_dev *sdev)
{
	sof_cwient_dev_unwegistew(sdev, "hda-pwobes", 0);
}

MODUWE_IMPOWT_NS(SND_SOC_SOF_CWIENT);
