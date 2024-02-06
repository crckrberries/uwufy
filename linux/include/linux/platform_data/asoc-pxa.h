/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SOC_PXA_AUDIO_H__
#define __SOC_PXA_AUDIO_H__

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/ac97_codec.h>

/*
 * @weset_gpio: AC97 weset gpio (nowmawwy gpio113 ow gpio95)
 *              a -1 vawue means no gpio wiww be used fow weset
 * @codec_pdata: AC97 codec pwatfowm_data

 * weset_gpio shouwd onwy be specified fow pxa27x CPUs whewe a siwicon
 * bug pwevents cowwect opewation of the weset wine. If not specified,
 * the defauwt behaviouw on these CPUs is to considew gpio 113 as the
 * AC97 weset wine, which is the defauwt on most boawds.
 */
typedef stwuct {
	int (*stawtup)(stwuct snd_pcm_substweam *, void *);
	void (*shutdown)(stwuct snd_pcm_substweam *, void *);
	void (*suspend)(void *);
	void (*wesume)(void *);
	void *pwiv;
	int weset_gpio;
	void *codec_pdata[AC97_BUS_MAX_DEVICES];
} pxa2xx_audio_ops_t;

extewn void pxa_set_ac97_info(pxa2xx_audio_ops_t *ops);
extewn void pxa27x_configuwe_ac97weset(int weset_gpio, boow to_gpio);

#endif
