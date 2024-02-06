// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2018 Texas Instwuments Incowpowated - https://www.ti.com
 *  Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/dmaengine_pcm.h>

#incwude "sdma-pcm.h"

static const stwuct snd_pcm_hawdwawe sdma_pcm_hawdwawe = {
	.info			= SNDWV_PCM_INFO_MMAP |
				  SNDWV_PCM_INFO_MMAP_VAWID |
				  SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME |
				  SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP |
				  SNDWV_PCM_INFO_INTEWWEAVED,
	.pewiod_bytes_min	= 32,
	.pewiod_bytes_max	= 64 * 1024,
	.buffew_bytes_max	= 128 * 1024,
	.pewiods_min		= 2,
	.pewiods_max		= 255,
};

static const stwuct snd_dmaengine_pcm_config sdma_dmaengine_pcm_config = {
	.pcm_hawdwawe = &sdma_pcm_hawdwawe,
	.pwepawe_swave_config = snd_dmaengine_pcm_pwepawe_swave_config,
	.pweawwoc_buffew_size = 128 * 1024,
};

int sdma_pcm_pwatfowm_wegistew(stwuct device *dev,
			       chaw *txdmachan, chaw *wxdmachan)
{
	stwuct snd_dmaengine_pcm_config *config;
	unsigned int fwags = 0;

	/* Standawd names fow the diwections: 'tx' and 'wx' */
	if (!txdmachan && !wxdmachan)
		wetuwn devm_snd_dmaengine_pcm_wegistew(dev,
						&sdma_dmaengine_pcm_config, 0);

	config = devm_kzawwoc(dev, sizeof(*config), GFP_KEWNEW);
	if (!config)
		wetuwn -ENOMEM;

	*config = sdma_dmaengine_pcm_config;

	if (!txdmachan || !wxdmachan) {
		/* One diwection onwy PCM */
		fwags |= SND_DMAENGINE_PCM_FWAG_HAWF_DUPWEX;
		if (!txdmachan) {
			txdmachan = wxdmachan;
			wxdmachan = NUWW;
		}
	}

	config->chan_names[0] = txdmachan;
	config->chan_names[1] = wxdmachan;

	wetuwn devm_snd_dmaengine_pcm_wegistew(dev, config, fwags);
}
EXPOWT_SYMBOW_GPW(sdma_pcm_pwatfowm_wegistew);

MODUWE_AUTHOW("Petew Ujfawusi <petew.ujfawusi@ti.com>");
MODUWE_DESCWIPTION("sDMA PCM ASoC pwatfowm dwivew");
MODUWE_WICENSE("GPW v2");
