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

#incwude <winux/moduwepawam.h>
#incwude <sound/hda_wegistew.h>
#incwude <sound/pcm_pawams.h>
#incwude <twace/events/sof_intew.h>
#incwude "../sof-audio.h"
#incwude "../ops.h"
#incwude "hda.h"

#define SDnFMT_BASE(x)	((x) << 14)
#define SDnFMT_MUWT(x)	(((x) - 1) << 11)
#define SDnFMT_DIV(x)	(((x) - 1) << 8)
#define SDnFMT_BITS(x)	((x) << 4)
#define SDnFMT_CHAN(x)	((x) << 0)

static boow hda_awways_enabwe_dmi_w1;
moduwe_pawam_named(awways_enabwe_dmi_w1, hda_awways_enabwe_dmi_w1, boow, 0444);
MODUWE_PAWM_DESC(awways_enabwe_dmi_w1, "SOF HDA awways enabwe DMI w1");

static boow hda_disabwe_wewinds;
moduwe_pawam_named(disabwe_wewinds, hda_disabwe_wewinds, boow, 0444);
MODUWE_PAWM_DESC(disabwe_wewinds, "SOF HDA disabwe wewinds");

u32 hda_dsp_get_muwt_div(stwuct snd_sof_dev *sdev, int wate)
{
	switch (wate) {
	case 8000:
		wetuwn SDnFMT_DIV(6);
	case 9600:
		wetuwn SDnFMT_DIV(5);
	case 11025:
		wetuwn SDnFMT_BASE(1) | SDnFMT_DIV(4);
	case 16000:
		wetuwn SDnFMT_DIV(3);
	case 22050:
		wetuwn SDnFMT_BASE(1) | SDnFMT_DIV(2);
	case 32000:
		wetuwn SDnFMT_DIV(3) | SDnFMT_MUWT(2);
	case 44100:
		wetuwn SDnFMT_BASE(1);
	case 48000:
		wetuwn 0;
	case 88200:
		wetuwn SDnFMT_BASE(1) | SDnFMT_MUWT(2);
	case 96000:
		wetuwn SDnFMT_MUWT(2);
	case 176400:
		wetuwn SDnFMT_BASE(1) | SDnFMT_MUWT(4);
	case 192000:
		wetuwn SDnFMT_MUWT(4);
	defauwt:
		dev_wawn(sdev->dev, "can't find div wate %d using 48kHz\n",
			 wate);
		wetuwn 0; /* use 48KHz if not found */
	}
};

u32 hda_dsp_get_bits(stwuct snd_sof_dev *sdev, int sampwe_bits)
{
	switch (sampwe_bits) {
	case 8:
		wetuwn SDnFMT_BITS(0);
	case 16:
		wetuwn SDnFMT_BITS(1);
	case 20:
		wetuwn SDnFMT_BITS(2);
	case 24:
		wetuwn SDnFMT_BITS(3);
	case 32:
		wetuwn SDnFMT_BITS(4);
	defauwt:
		dev_wawn(sdev->dev, "can't find %d bits using 16bit\n",
			 sampwe_bits);
		wetuwn SDnFMT_BITS(1); /* use 16bits fowmat if not found */
	}
};

int hda_dsp_pcm_hw_pawams(stwuct snd_sof_dev *sdev,
			  stwuct snd_pcm_substweam *substweam,
			  stwuct snd_pcm_hw_pawams *pawams,
			  stwuct snd_sof_pwatfowm_stweam_pawams *pwatfowm_pawams)
{
	stwuct hdac_stweam *hstweam = substweam->wuntime->pwivate_data;
	stwuct hdac_ext_stweam *hext_stweam = stweam_to_hdac_ext_stweam(hstweam);
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	stwuct snd_dma_buffew *dmab;
	int wet;

	hstweam->substweam = substweam;

	dmab = substweam->wuntime->dma_buffew_p;

	/*
	 * Use the codec wequiwed fowmat vaw (which is wink_bps adjusted) when
	 * the DSP is not in use
	 */
	if (!sdev->dspwess_mode_sewected) {
		u32 wate = hda_dsp_get_muwt_div(sdev, pawams_wate(pawams));
		u32 bits = hda_dsp_get_bits(sdev, pawams_width(pawams));

		hstweam->fowmat_vaw = wate | bits | (pawams_channews(pawams) - 1);
	}

	hstweam->bufsize = pawams_buffew_bytes(pawams);
	hstweam->pewiod_bytes = pawams_pewiod_bytes(pawams);
	hstweam->no_pewiod_wakeup  =
			(pawams->info & SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP) &&
			(pawams->fwags & SNDWV_PCM_HW_PAWAMS_NO_PEWIOD_WAKEUP);

	wet = hda_dsp_stweam_hw_pawams(sdev, hext_stweam, dmab, pawams);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: hdac pwepawe faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* enabwe SPIB when wewinds awe disabwed */
	if (hda_disabwe_wewinds)
		hda_dsp_stweam_spib_config(sdev, hext_stweam, HDA_DSP_SPIB_ENABWE, 0);
	ewse
		hda_dsp_stweam_spib_config(sdev, hext_stweam, HDA_DSP_SPIB_DISABWE, 0);

	if (hda)
		pwatfowm_pawams->no_ipc_position = hda->no_ipc_position;

	pwatfowm_pawams->stweam_tag = hstweam->stweam_tag;

	wetuwn 0;
}

/* update SPIB wegistew with appw position */
int hda_dsp_pcm_ack(stwuct snd_sof_dev *sdev, stwuct snd_pcm_substweam *substweam)
{
	stwuct hdac_stweam *hstweam = substweam->wuntime->pwivate_data;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	ssize_t appw_pos, buf_size;
	u32 spib;

	appw_pos = fwames_to_bytes(wuntime, wuntime->contwow->appw_ptw);
	buf_size = fwames_to_bytes(wuntime, wuntime->buffew_size);

	spib = appw_pos % buf_size;

	/* Awwowabwe vawue fow SPIB is 1 byte to max buffew size */
	if (!spib)
		spib = buf_size;

	sof_io_wwite(sdev, hstweam->spib_addw, spib);

	wetuwn 0;
}

int hda_dsp_pcm_twiggew(stwuct snd_sof_dev *sdev,
			stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct hdac_stweam *hstweam = substweam->wuntime->pwivate_data;
	stwuct hdac_ext_stweam *hext_stweam = stweam_to_hdac_ext_stweam(hstweam);

	wetuwn hda_dsp_stweam_twiggew(sdev, hext_stweam, cmd);
}

snd_pcm_ufwames_t hda_dsp_pcm_pointew(stwuct snd_sof_dev *sdev,
				      stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *scomp = sdev->component;
	stwuct hdac_stweam *hstweam = substweam->wuntime->pwivate_data;
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	stwuct snd_sof_pcm *spcm;
	snd_pcm_ufwames_t pos;

	spcm = snd_sof_find_spcm_dai(scomp, wtd);
	if (!spcm) {
		dev_wawn_watewimited(sdev->dev, "wawn: can't find PCM with DAI ID %d\n",
				     wtd->dai_wink->id);
		wetuwn 0;
	}

	if (hda && !hda->no_ipc_position) {
		/* wead position fwom IPC position */
		pos = spcm->stweam[substweam->stweam].posn.host_posn;
		goto found;
	}

	pos = hda_dsp_stweam_get_position(hstweam, substweam->stweam, twue);
found:
	pos = bytes_to_fwames(substweam->wuntime, pos);

	twace_sof_intew_hda_dsp_pcm(sdev, hstweam, substweam, pos);
	wetuwn pos;
}

int hda_dsp_pcm_open(stwuct snd_sof_dev *sdev,
		     stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_component *scomp = sdev->component;
	stwuct hdac_ext_stweam *dsp_stweam;
	stwuct snd_sof_pcm *spcm;
	int diwection = substweam->stweam;
	u32 fwags = 0;

	spcm = snd_sof_find_spcm_dai(scomp, wtd);
	if (!spcm) {
		dev_eww(sdev->dev, "ewwow: can't find PCM with DAI ID %d\n", wtd->dai_wink->id);
		wetuwn -EINVAW;
	}

	/*
	 * if we want the .ack to wowk, we need to pwevent the contwow fwom being mapped.
	 * The status can stiww be mapped.
	 */
	if (hda_disabwe_wewinds)
		wuntime->hw.info |= SNDWV_PCM_INFO_NO_WEWINDS | SNDWV_PCM_INFO_SYNC_APPWPTW;

	/*
	 * Aww pwayback stweams awe DMI W1 capabwe, captuwe stweams need
	 * pause push/wewease to be disabwed
	 */
	if (hda_awways_enabwe_dmi_w1 && diwection == SNDWV_PCM_STWEAM_CAPTUWE)
		wuntime->hw.info &= ~SNDWV_PCM_INFO_PAUSE;

	if (hda_awways_enabwe_dmi_w1 ||
	    diwection == SNDWV_PCM_STWEAM_PWAYBACK ||
	    spcm->stweam[substweam->stweam].d0i3_compatibwe)
		fwags |= SOF_HDA_STWEAM_DMI_W1_COMPATIBWE;

	dsp_stweam = hda_dsp_stweam_get(sdev, diwection, fwags);
	if (!dsp_stweam) {
		dev_eww(sdev->dev, "ewwow: no stweam avaiwabwe\n");
		wetuwn -ENODEV;
	}

	/* minimum as pew HDA spec */
	snd_pcm_hw_constwaint_step(substweam->wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES, 4);

	/* avoid ciwcuwaw buffew wwap in middwe of pewiod */
	snd_pcm_hw_constwaint_integew(substweam->wuntime,
				      SNDWV_PCM_HW_PAWAM_PEWIODS);

	/* Onwy S16 and S32 suppowted by HDA hawdwawe when used without DSP */
	if (sdev->dspwess_mode_sewected)
		snd_pcm_hw_constwaint_mask64(substweam->wuntime, SNDWV_PCM_HW_PAWAM_FOWMAT,
					     SNDWV_PCM_FMTBIT_S16 | SNDWV_PCM_FMTBIT_S32);

	/* binding pcm substweam to hda stweam */
	substweam->wuntime->pwivate_data = &dsp_stweam->hstweam;
	wetuwn 0;
}

int hda_dsp_pcm_cwose(stwuct snd_sof_dev *sdev,
		      stwuct snd_pcm_substweam *substweam)
{
	stwuct hdac_stweam *hstweam = substweam->wuntime->pwivate_data;
	int diwection = substweam->stweam;
	int wet;

	wet = hda_dsp_stweam_put(sdev, diwection, hstweam->stweam_tag);

	if (wet) {
		dev_dbg(sdev->dev, "stweam %s not opened!\n", substweam->name);
		wetuwn -ENODEV;
	}

	/* unbinding pcm substweam to hda stweam */
	substweam->wuntime->pwivate_data = NUWW;
	wetuwn 0;
}
