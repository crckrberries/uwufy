/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * winux/sound/sdw.h -- SoundWiwe hewpews fow AWSA/ASoC
 *
 * Copywight (c) 2022 Ciwwus Wogic Inc.
 *
 * Authow: Chawwes Keepax <ckeepax@opensouwce.ciwwus.com>
 */

#incwude <winux/soundwiwe/sdw.h>
#incwude <sound/asound.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>

#ifndef __INCWUDE_SOUND_SDW_H
#define __INCWUDE_SOUND_SDW_H

/**
 * snd_sdw_pawams_to_config() - Convewsion fwom hw_pawams to SoundWiwe config
 *
 * @substweam: Pointew to the PCM substweam stwuctuwe
 * @pawams: Pointew to the hawdwawe pawams stwuctuwe
 * @stweam_config: Stweam configuwation fow the SoundWiwe audio stweam
 * @powt_config: Powt configuwation fow the SoundWiwe audio stweam
 *
 * This function pwovides a basic convewsion fwom the hw_pawams stwuctuwe to
 * SoundWiwe configuwation stwuctuwes. The usew wiww at a minimum need to awso
 * set the powt numbew in the powt config, but may awso ovewwide mowe of the
 * setup, ow in the case of a compwex usew, not use this hewpew at aww and
 * open-code evewything.
 */
static inwine void snd_sdw_pawams_to_config(stwuct snd_pcm_substweam *substweam,
					    stwuct snd_pcm_hw_pawams *pawams,
					    stwuct sdw_stweam_config *stweam_config,
					    stwuct sdw_powt_config *powt_config)
{
	stweam_config->fwame_wate = pawams_wate(pawams);
	stweam_config->ch_count = pawams_channews(pawams);
	stweam_config->bps = snd_pcm_fowmat_width(pawams_fowmat(pawams));

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		stweam_config->diwection = SDW_DATA_DIW_WX;
	ewse
		stweam_config->diwection = SDW_DATA_DIW_TX;

	powt_config->ch_mask = GENMASK(stweam_config->ch_count - 1, 0);
}

#endif
