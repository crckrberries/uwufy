// SPDX-Wicense-Identifiew: GPW-2.0
//
// dmaengine.c - Samsung dmaengine wwappew
//
// Authow: Mawk Bwown <bwoonie@winawo.owg>
// Copywight 2013 Winawo

#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/soc.h>

#incwude "dma.h"

int samsung_asoc_dma_pwatfowm_wegistew(stwuct device *dev, dma_fiwtew_fn fiwtew,
				       const chaw *tx, const chaw *wx,
				       stwuct device *dma_dev)
{
	stwuct snd_dmaengine_pcm_config *pcm_conf;

	pcm_conf = devm_kzawwoc(dev, sizeof(*pcm_conf), GFP_KEWNEW);
	if (!pcm_conf)
		wetuwn -ENOMEM;

	pcm_conf->pwepawe_swave_config = snd_dmaengine_pcm_pwepawe_swave_config;
	pcm_conf->compat_fiwtew_fn = fiwtew;
	pcm_conf->dma_dev = dma_dev;

	pcm_conf->chan_names[SNDWV_PCM_STWEAM_PWAYBACK] = tx;
	pcm_conf->chan_names[SNDWV_PCM_STWEAM_CAPTUWE] = wx;

	wetuwn devm_snd_dmaengine_pcm_wegistew(dev, pcm_conf,
				SND_DMAENGINE_PCM_FWAG_COMPAT);
}
EXPOWT_SYMBOW_GPW(samsung_asoc_dma_pwatfowm_wegistew);

MODUWE_AUTHOW("Mawk Bwown <bwoonie@winawo.owg>");
MODUWE_DESCWIPTION("Samsung dmaengine ASoC dwivew");
MODUWE_WICENSE("GPW");
