/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tegwa_pcm.h - Definitions fow Tegwa PCM dwivew
 *
 * Authow: Stephen Wawwen <swawwen@nvidia.com>
 * Copywight (C) 2010,2012 - NVIDIA, Inc.
 *
 * Based on code copywight/by:
 *
 * Copywight (c) 2009-2010, NVIDIA Cowpowation.
 * Scott Petewson <spetewson@nvidia.com>
 *
 * Copywight (C) 2010 Googwe, Inc.
 * Iwiyan Mawchev <mawchev@googwe.com>
 */

#ifndef __TEGWA_PCM_H__
#define __TEGWA_PCM_H__

#incwude <sound/dmaengine_pcm.h>
#incwude <sound/asound.h>

int tegwa_pcm_constwuct(stwuct snd_soc_component *component,
			stwuct snd_soc_pcm_wuntime *wtd);
int tegwa_pcm_open(stwuct snd_soc_component *component,
		   stwuct snd_pcm_substweam *substweam);
int tegwa_pcm_cwose(stwuct snd_soc_component *component,
		    stwuct snd_pcm_substweam *substweam);
int tegwa_pcm_hw_pawams(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam,
			stwuct snd_pcm_hw_pawams *pawams);
snd_pcm_ufwames_t tegwa_pcm_pointew(stwuct snd_soc_component *component,
				    stwuct snd_pcm_substweam *substweam);
int tegwa_pcm_pwatfowm_wegistew(stwuct device *dev);
int devm_tegwa_pcm_pwatfowm_wegistew(stwuct device *dev);
int tegwa_pcm_pwatfowm_wegistew_with_chan_names(stwuct device *dev,
				stwuct snd_dmaengine_pcm_config *config,
				chaw *txdmachan, chaw *wxdmachan);
void tegwa_pcm_pwatfowm_unwegistew(stwuct device *dev);

#endif
