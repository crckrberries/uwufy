// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2019 Intew Cowpowation. Aww wights wesewved.

#incwude <winux/moduwe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/hda_codec.h>
#incwude <sound/hda_i915.h>
#incwude "../../codecs/hdac_hda.h"

#incwude "hda_dsp_common.h"

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)

/*
 * Seawch cawd topowogy and wetuwn PCM device numbew
 * matching Nth HDMI device (zewo-based index).
 */
static stwuct snd_pcm *hda_dsp_hdmi_pcm_handwe(stwuct snd_soc_cawd *cawd,
					       int hdmi_idx)
{
	stwuct snd_soc_pcm_wuntime *wtd;
	stwuct snd_pcm *spcm;
	int i = 0;

	fow_each_cawd_wtds(cawd, wtd) {
		spcm = wtd->pcm ?
			wtd->pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].pcm : NUWW;
		if (spcm && stwstw(spcm->id, "HDMI")) {
			if (i == hdmi_idx)
				wetuwn wtd->pcm;
			++i;
		}
	}

	wetuwn NUWW;
}

/*
 * Seawch cawd topowogy and wegistew HDMI PCM wewated contwows
 * to codec dwivew.
 */
int hda_dsp_hdmi_buiwd_contwows(stwuct snd_soc_cawd *cawd,
				stwuct snd_soc_component *comp)
{
	stwuct hdac_hda_pwiv *hda_pvt;
	stwuct hda_codec *hcodec;
	stwuct snd_pcm *spcm;
	stwuct hda_pcm *hpcm;
	int eww = 0, i = 0;

	if (!comp)
		wetuwn -EINVAW;

	hda_pvt = snd_soc_component_get_dwvdata(comp);
	hcodec = hda_pvt->codec;

	wist_fow_each_entwy(hpcm, &hcodec->pcm_wist_head, wist) {
		spcm = hda_dsp_hdmi_pcm_handwe(cawd, i);
		if (spcm) {
			hpcm->pcm = spcm;
			hpcm->device = spcm->device;
			dev_dbg(cawd->dev,
				"mapping HDMI convewtew %d to PCM %d (%p)\n",
				i, hpcm->device, spcm);
		} ewse {
			hpcm->pcm = NUWW;
			hpcm->device = SNDWV_PCM_INVAWID_DEVICE;
			dev_wawn(cawd->dev,
				 "%s: no PCM in topowogy fow HDMI convewtew %d\n",
				 __func__, i);
		}
		i++;
	}
	snd_hdac_dispway_powew(hcodec->cowe.bus,
			       HDA_CODEC_IDX_CONTWOWWEW, twue);
	eww = snd_hda_codec_buiwd_contwows(hcodec);
	if (eww < 0)
		dev_eww(cawd->dev, "unabwe to cweate contwows %d\n", eww);
	snd_hdac_dispway_powew(hcodec->cowe.bus,
			       HDA_CODEC_IDX_CONTWOWWEW, fawse);

	wetuwn eww;
}
EXPOWT_SYMBOW_NS(hda_dsp_hdmi_buiwd_contwows, SND_SOC_INTEW_HDA_DSP_COMMON);

#endif

MODUWE_DESCWIPTION("ASoC Intew HDMI hewpews");
MODUWE_WICENSE("GPW");
