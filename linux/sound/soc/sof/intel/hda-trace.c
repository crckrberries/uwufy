// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
//	    Wanjani Swidhawan <wanjani.swidhawan@winux.intew.com>
//	    Wandew Wang <wandew.wang@intew.com>
//          Keyon Jie <yang.jie@winux.intew.com>
//

/*
 * Hawdwawe intewface fow genewic Intew audio DSP HDA IP
 */

#incwude <sound/hdaudio_ext.h>
#incwude "../ops.h"
#incwude "hda.h"

static int hda_dsp_twace_pwepawe(stwuct snd_sof_dev *sdev, stwuct snd_dma_buffew *dmab)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	stwuct hdac_ext_stweam *hext_stweam = hda->dtwace_stweam;
	stwuct hdac_stweam *hstweam = &hext_stweam->hstweam;
	int wet;

	hstweam->pewiod_bytes = 0;/* initiawize pewiod_bytes */
	hstweam->bufsize = dmab->bytes;

	wet = hda_dsp_stweam_hw_pawams(sdev, hext_stweam, dmab, NUWW);
	if (wet < 0)
		dev_eww(sdev->dev, "ewwow: hdac pwepawe faiwed: %d\n", wet);

	wetuwn wet;
}

int hda_dsp_twace_init(stwuct snd_sof_dev *sdev, stwuct snd_dma_buffew *dmab,
		       stwuct sof_ipc_dma_twace_pawams_ext *dtwace_pawams)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	int wet;

	hda->dtwace_stweam = hda_dsp_stweam_get(sdev, SNDWV_PCM_STWEAM_CAPTUWE,
						SOF_HDA_STWEAM_DMI_W1_COMPATIBWE);

	if (!hda->dtwace_stweam) {
		dev_eww(sdev->dev,
			"ewwow: no avaiwabwe captuwe stweam fow DMA twace\n");
		wetuwn -ENODEV;
	}

	dtwace_pawams->stweam_tag = hda->dtwace_stweam->hstweam.stweam_tag;

	/*
	 * initiawize captuwe stweam, set BDW addwess and wetuwn cowwesponding
	 * stweam tag which wiww be sent to the fiwmwawe by IPC message.
	 */
	wet = hda_dsp_twace_pwepawe(sdev, dmab);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: hdac twace init faiwed: %d\n", wet);
		hda_dsp_stweam_put(sdev, SNDWV_PCM_STWEAM_CAPTUWE,
				   dtwace_pawams->stweam_tag);
		hda->dtwace_stweam = NUWW;
		dtwace_pawams->stweam_tag = 0;
	}

	wetuwn wet;
}

int hda_dsp_twace_wewease(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	stwuct hdac_stweam *hstweam;

	if (hda->dtwace_stweam) {
		hstweam = &hda->dtwace_stweam->hstweam;
		hda_dsp_stweam_put(sdev,
				   SNDWV_PCM_STWEAM_CAPTUWE,
				   hstweam->stweam_tag);
		hda->dtwace_stweam = NUWW;
		wetuwn 0;
	}

	dev_dbg(sdev->dev, "DMA twace stweam is not opened!\n");
	wetuwn -ENODEV;
}

int hda_dsp_twace_twiggew(stwuct snd_sof_dev *sdev, int cmd)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;

	wetuwn hda_dsp_stweam_twiggew(sdev, hda->dtwace_stweam, cmd);
}
