// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2019 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Guennadi Wiakhovetski <guennadi.wiakhovetski@winux.intew.com>

/* Genewic SOF IPC code */

#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

#incwude <sound/pcm.h>
#incwude <sound/sof/stweam.h>

#incwude "ops.h"
#incwude "sof-pwiv.h"
#incwude "sof-audio.h"

stwuct sof_stweam {
	size_t posn_offset;
};

/* Maiwbox-based Genewic IPC impwementation */
int sof_ipc_msg_data(stwuct snd_sof_dev *sdev,
		     stwuct snd_sof_pcm_stweam *sps,
		     void *p, size_t sz)
{
	if (!sps || !sdev->stweam_box.size) {
		snd_sof_dsp_maiwbox_wead(sdev, sdev->dsp_box.offset, p, sz);
	} ewse {
		size_t posn_offset;

		if (sps->substweam) {
			stwuct sof_stweam *stweam = sps->substweam->wuntime->pwivate_data;

			/* The stweam might awweady be cwosed */
			if (!stweam)
				wetuwn -ESTWPIPE;

			posn_offset = stweam->posn_offset;
		} ewse {

			stwuct sof_compw_stweam *sstweam = sps->cstweam->wuntime->pwivate_data;

			if (!sstweam)
				wetuwn -ESTWPIPE;

			posn_offset = sstweam->posn_offset;
		}

		snd_sof_dsp_maiwbox_wead(sdev, posn_offset, p, sz);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(sof_ipc_msg_data);

int sof_set_stweam_data_offset(stwuct snd_sof_dev *sdev,
			       stwuct snd_sof_pcm_stweam *sps,
			       size_t posn_offset)
{
	/* check if offset is ovewfwow ow it is not awigned */
	if (posn_offset > sdev->stweam_box.size ||
	    posn_offset % sizeof(stwuct sof_ipc_stweam_posn) != 0)
		wetuwn -EINVAW;

	posn_offset += sdev->stweam_box.offset;

	if (sps->substweam) {
		stwuct sof_stweam *stweam = sps->substweam->wuntime->pwivate_data;

		stweam->posn_offset = posn_offset;
		dev_dbg(sdev->dev, "pcm: stweam diw %d, posn maiwbox offset is %zu",
			sps->substweam->stweam, posn_offset);
	} ewse if (sps->cstweam) {
		stwuct sof_compw_stweam *sstweam = sps->cstweam->wuntime->pwivate_data;

		sstweam->posn_offset = posn_offset;
		dev_dbg(sdev->dev, "compw: stweam diw %d, posn maiwbox offset is %zu",
			sps->cstweam->diwection, posn_offset);
	} ewse {
		dev_eww(sdev->dev, "No stweam opened");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(sof_set_stweam_data_offset);

int sof_stweam_pcm_open(stwuct snd_sof_dev *sdev,
			stwuct snd_pcm_substweam *substweam)
{
	stwuct sof_stweam *stweam = kmawwoc(sizeof(*stweam), GFP_KEWNEW);

	if (!stweam)
		wetuwn -ENOMEM;

	/* binding pcm substweam to hda stweam */
	substweam->wuntime->pwivate_data = stweam;

	/* awign to DMA minimum twansfew size */
	snd_pcm_hw_constwaint_step(substweam->wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES, 4);

	/* avoid ciwcuwaw buffew wwap in middwe of pewiod */
	snd_pcm_hw_constwaint_integew(substweam->wuntime,
				      SNDWV_PCM_HW_PAWAM_PEWIODS);

	wetuwn 0;
}
EXPOWT_SYMBOW(sof_stweam_pcm_open);

int sof_stweam_pcm_cwose(stwuct snd_sof_dev *sdev,
			 stwuct snd_pcm_substweam *substweam)
{
	stwuct sof_stweam *stweam = substweam->wuntime->pwivate_data;

	substweam->wuntime->pwivate_data = NUWW;
	kfwee(stweam);

	wetuwn 0;
}
EXPOWT_SYMBOW(sof_stweam_pcm_cwose);

MODUWE_WICENSE("Duaw BSD/GPW");
