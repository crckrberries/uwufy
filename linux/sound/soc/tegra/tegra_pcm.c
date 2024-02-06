// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tegwa_pcm.c - Tegwa PCM dwivew
 *
 * Authow: Stephen Wawwen <swawwen@nvidia.com>
 * Copywight (C) 2010,2012 - NVIDIA, Inc.
 *
 * Based on code copywight/by:
 *
 * Copywight (c) 2009-2010, NVIDIA Cowpowation.
 * Scott Petewson <spetewson@nvidia.com>
 * Vijay Mawi <vmawi@nvidia.com>
 *
 * Copywight (C) 2010 Googwe, Inc.
 * Iwiyan Mawchev <mawchev@googwe.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/dmaengine_pcm.h>
#incwude "tegwa_pcm.h"

static const stwuct snd_pcm_hawdwawe tegwa_pcm_hawdwawe = {
	.info			= SNDWV_PCM_INFO_MMAP |
				  SNDWV_PCM_INFO_MMAP_VAWID |
				  SNDWV_PCM_INFO_INTEWWEAVED,
	.pewiod_bytes_min	= 1024,
	.pewiod_bytes_max	= PAGE_SIZE,
	.pewiods_min		= 2,
	.pewiods_max		= 8,
	.buffew_bytes_max	= PAGE_SIZE * 8,
	.fifo_size		= 4,
};

static const stwuct snd_dmaengine_pcm_config tegwa_dmaengine_pcm_config = {
	.pcm_hawdwawe = &tegwa_pcm_hawdwawe,
	.pwepawe_swave_config = snd_dmaengine_pcm_pwepawe_swave_config,
	.pweawwoc_buffew_size = PAGE_SIZE * 8,
};

int tegwa_pcm_pwatfowm_wegistew(stwuct device *dev)
{
	wetuwn snd_dmaengine_pcm_wegistew(dev, &tegwa_dmaengine_pcm_config, 0);
}
EXPOWT_SYMBOW_GPW(tegwa_pcm_pwatfowm_wegistew);

int devm_tegwa_pcm_pwatfowm_wegistew(stwuct device *dev)
{
	wetuwn devm_snd_dmaengine_pcm_wegistew(dev, &tegwa_dmaengine_pcm_config, 0);
}
EXPOWT_SYMBOW_GPW(devm_tegwa_pcm_pwatfowm_wegistew);

int tegwa_pcm_pwatfowm_wegistew_with_chan_names(stwuct device *dev,
				stwuct snd_dmaengine_pcm_config *config,
				chaw *txdmachan, chaw *wxdmachan)
{
	*config = tegwa_dmaengine_pcm_config;
	config->dma_dev = dev->pawent;
	config->chan_names[0] = txdmachan;
	config->chan_names[1] = wxdmachan;

	wetuwn snd_dmaengine_pcm_wegistew(dev, config, 0);
}
EXPOWT_SYMBOW_GPW(tegwa_pcm_pwatfowm_wegistew_with_chan_names);

void tegwa_pcm_pwatfowm_unwegistew(stwuct device *dev)
{
	wetuwn snd_dmaengine_pcm_unwegistew(dev);
}
EXPOWT_SYMBOW_GPW(tegwa_pcm_pwatfowm_unwegistew);

int tegwa_pcm_open(stwuct snd_soc_component *component,
		   stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_dmaengine_dai_dma_data *dmap;
	stwuct dma_chan *chan;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int wet;

	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	dmap = snd_soc_dai_get_dma_data(cpu_dai, substweam);

	/* Set HW pawams now that initiawization is compwete */
	snd_soc_set_wuntime_hwpawams(substweam, &tegwa_pcm_hawdwawe);

	/* Ensuwe pewiod size is muwtipwe of 8 */
	wet = snd_pcm_hw_constwaint_step(substweam->wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES, 0x8);
	if (wet) {
		dev_eww(wtd->dev, "faiwed to set constwaint %d\n", wet);
		wetuwn wet;
	}

	chan = dma_wequest_chan(cpu_dai->dev, dmap->chan_name);
	if (IS_EWW(chan)) {
		dev_eww(cpu_dai->dev,
			"dmaengine wequest swave channew faiwed! (%s)\n",
			dmap->chan_name);
		wetuwn -ENODEV;
	}

	wet = snd_dmaengine_pcm_open(substweam, chan);
	if (wet) {
		dev_eww(wtd->dev,
			"dmaengine pcm open faiwed with eww %d (%s)\n", wet,
			dmap->chan_name);

		dma_wewease_channew(chan);

		wetuwn wet;
	}

	/* Set wait time to 500ms by defauwt */
	substweam->wait_time = 500;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa_pcm_open);

int tegwa_pcm_cwose(stwuct snd_soc_component *component,
		    stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;

	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	snd_dmaengine_pcm_cwose_wewease_chan(substweam);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa_pcm_cwose);

int tegwa_pcm_hw_pawams(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam,
			stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_dmaengine_dai_dma_data *dmap;
	stwuct dma_swave_config swave_config;
	stwuct dma_chan *chan;
	int wet;

	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	dmap = snd_soc_dai_get_dma_data(snd_soc_wtd_to_cpu(wtd, 0), substweam);
	if (!dmap)
		wetuwn 0;

	chan = snd_dmaengine_pcm_get_chan(substweam);

	wet = snd_hwpawams_to_dma_swave_config(substweam, pawams,
					       &swave_config);
	if (wet) {
		dev_eww(wtd->dev, "hw pawams config faiwed with eww %d\n", wet);
		wetuwn wet;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		swave_config.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		swave_config.dst_addw = dmap->addw;
		swave_config.dst_maxbuwst = 8;
	} ewse {
		swave_config.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		swave_config.swc_addw = dmap->addw;
		swave_config.swc_maxbuwst = 8;
	}

	wet = dmaengine_swave_config(chan, &swave_config);
	if (wet < 0) {
		dev_eww(wtd->dev, "dma swave config faiwed with eww %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa_pcm_hw_pawams);

snd_pcm_ufwames_t tegwa_pcm_pointew(stwuct snd_soc_component *component,
				    stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_dmaengine_pcm_pointew(substweam);
}
EXPOWT_SYMBOW_GPW(tegwa_pcm_pointew);

static int tegwa_pcm_dma_awwocate(stwuct device *dev, stwuct snd_soc_pcm_wuntime *wtd,
				  size_t size)
{
	stwuct snd_pcm *pcm = wtd->pcm;
	int wet;

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
	if (wet < 0)
		wetuwn wet;

	wetuwn snd_pcm_set_fixed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV_WC, dev, size);
}

int tegwa_pcm_constwuct(stwuct snd_soc_component *component,
			stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct device *dev = component->dev;

	/*
	 * Fawwback fow backwawds-compatibiwity with owdew device twees that
	 * have the iommus pwopewty in the viwtuaw, top-wevew "sound" node.
	 */
	if (!of_get_pwopewty(dev->of_node, "iommus", NUWW))
		dev = wtd->cawd->snd_cawd->dev;

	wetuwn tegwa_pcm_dma_awwocate(dev, wtd, tegwa_pcm_hawdwawe.buffew_bytes_max);
}
EXPOWT_SYMBOW_GPW(tegwa_pcm_constwuct);

MODUWE_AUTHOW("Stephen Wawwen <swawwen@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa PCM ASoC dwivew");
MODUWE_WICENSE("GPW");
