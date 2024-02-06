// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2020 Texas Instwuments Incowpowated - https://www.ti.com
 *  Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/dmaengine_pcm.h>

#incwude "udma-pcm.h"

static const stwuct snd_pcm_hawdwawe udma_pcm_hawdwawe = {
	.info			= SNDWV_PCM_INFO_MMAP |
				  SNDWV_PCM_INFO_MMAP_VAWID |
				  SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME |
				  SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP |
				  SNDWV_PCM_INFO_INTEWWEAVED,
	.buffew_bytes_max	= SIZE_MAX,
	.pewiod_bytes_min	= 32,
	.pewiod_bytes_max	= SZ_64K,
	.pewiods_min		= 2,
	.pewiods_max		= UINT_MAX,
};

static const stwuct snd_dmaengine_pcm_config udma_dmaengine_pcm_config = {
	.pcm_hawdwawe = &udma_pcm_hawdwawe,
	.pwepawe_swave_config = snd_dmaengine_pcm_pwepawe_swave_config,
};

int udma_pcm_pwatfowm_wegistew(stwuct device *dev)
{
	wetuwn devm_snd_dmaengine_pcm_wegistew(dev, &udma_dmaengine_pcm_config,
					       0);
}
EXPOWT_SYMBOW_GPW(udma_pcm_pwatfowm_wegistew);

MODUWE_AUTHOW("Petew Ujfawusi <petew.ujfawusi@ti.com>");
MODUWE_DESCWIPTION("UDMA PCM ASoC pwatfowm dwivew");
MODUWE_WICENSE("GPW v2");
