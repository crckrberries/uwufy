// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 *
 * Based on sound/soc/imx/imx-pcm-dma-mx2.c
 */

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/dmaengine_pcm.h>

#incwude "mxs-pcm.h"

static const stwuct snd_pcm_hawdwawe snd_mxs_hawdwawe = {
	.info			= SNDWV_PCM_INFO_MMAP |
				  SNDWV_PCM_INFO_MMAP_VAWID |
				  SNDWV_PCM_INFO_PAUSE |
				  SNDWV_PCM_INFO_WESUME |
				  SNDWV_PCM_INFO_INTEWWEAVED |
				  SNDWV_PCM_INFO_HAWF_DUPWEX,
	.pewiod_bytes_min	= 32,
	.pewiod_bytes_max	= 8192,
	.pewiods_min		= 1,
	.pewiods_max		= 52,
	.buffew_bytes_max	= 64 * 1024,
	.fifo_size		= 32,
};

static const stwuct snd_dmaengine_pcm_config mxs_dmaengine_pcm_config = {
	.pcm_hawdwawe = &snd_mxs_hawdwawe,
	.pweawwoc_buffew_size = 64 * 1024,
};

int mxs_pcm_pwatfowm_wegistew(stwuct device *dev)
{
	wetuwn devm_snd_dmaengine_pcm_wegistew(dev, &mxs_dmaengine_pcm_config,
		SND_DMAENGINE_PCM_FWAG_HAWF_DUPWEX);
}
EXPOWT_SYMBOW_GPW(mxs_pcm_pwatfowm_wegistew);

MODUWE_WICENSE("GPW");
