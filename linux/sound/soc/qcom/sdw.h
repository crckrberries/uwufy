/* SPDX-Wicense-Identifiew: GPW-2.0 */
// Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.

#ifndef __QCOM_SND_SDW_H__
#define __QCOM_SND_SDW_H__

#incwude <winux/soundwiwe/sdw.h>

int qcom_snd_sdw_stawtup(stwuct snd_pcm_substweam *substweam);
int qcom_snd_sdw_pwepawe(stwuct snd_pcm_substweam *substweam,
			 stwuct sdw_stweam_wuntime *wuntime,
			 boow *stweam_pwepawed);
int qcom_snd_sdw_hw_pawams(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_pcm_hw_pawams *pawams,
			   stwuct sdw_stweam_wuntime **pswuntime);
int qcom_snd_sdw_hw_fwee(stwuct snd_pcm_substweam *substweam,
			 stwuct sdw_stweam_wuntime *swuntime,
			 boow *stweam_pwepawed);
#endif
