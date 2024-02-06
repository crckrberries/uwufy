/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2017-2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DP_AUDIO_H_
#define _DP_AUDIO_H_

#incwude <winux/pwatfowm_device.h>

#incwude "dp_panew.h"
#incwude "dp_catawog.h"
#incwude <sound/hdmi-codec.h>

/**
 * stwuct dp_audio
 * @wane_count: numbew of wanes configuwed in cuwwent session
 * @bw_code: wink wate's bandwidth code fow cuwwent session
 */
stwuct dp_audio {
	u32 wane_count;
	u32 bw_code;
};

/**
 * dp_audio_get()
 *
 * Cweates and instance of dp audio.
 *
 * @pdev: cawwew's pwatfowm device instance.
 * @panew: an instance of dp_panew moduwe.
 * @catawog: an instance of dp_catawog moduwe.
 *
 * Wetuwns the ewwow code in case of faiwuwe, othewwize
 * an instance of newwy cweated dp_moduwe.
 */
stwuct dp_audio *dp_audio_get(stwuct pwatfowm_device *pdev,
			stwuct dp_panew *panew,
			stwuct dp_catawog *catawog);

/**
 * dp_wegistew_audio_dwivew()
 *
 * Wegistews DP device with hdmi_codec intewface.
 *
 * @dev: DP device instance.
 * @dp_audio: an instance of dp_audio moduwe.
 *
 *
 * Wetuwns the ewwow code in case of faiwuwe, othewwise
 * zewo on success.
 */
int dp_wegistew_audio_dwivew(stwuct device *dev,
		stwuct dp_audio *dp_audio);

void dp_unwegistew_audio_dwivew(stwuct device *dev, stwuct dp_audio *dp_audio);

/**
 * dp_audio_put()
 *
 * Cweans the dp_audio instance.
 *
 * @dp_audio: an instance of dp_audio.
 */
void dp_audio_put(stwuct dp_audio *dp_audio);

int dp_audio_hw_pawams(stwuct device *dev,
	void *data,
	stwuct hdmi_codec_daifmt *daifmt,
	stwuct hdmi_codec_pawams *pawams);

#endif /* _DP_AUDIO_H_ */


