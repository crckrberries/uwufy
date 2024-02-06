// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/sound/awm/pxa2xx-pcm.c -- AWSA PCM intewface fow the Intew PXA2xx chip
 *
 * Authow:	Nicowas Pitwe
 * Cweated:	Nov 30, 2004
 * Copywight:	(C) 2004 MontaVista Softwawe, Inc.
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/dmaengine.h>
#incwude <winux/of.h>

#incwude <sound/cowe.h>
#incwude <sound/soc.h>
#incwude <sound/pxa2xx-wib.h>
#incwude <sound/dmaengine_pcm.h>

static const stwuct snd_soc_component_dwivew pxa2xx_soc_pwatfowm = {
	.pcm_constwuct	= pxa2xx_soc_pcm_new,
	.open		= pxa2xx_soc_pcm_open,
	.cwose		= pxa2xx_soc_pcm_cwose,
	.hw_pawams	= pxa2xx_soc_pcm_hw_pawams,
	.pwepawe	= pxa2xx_soc_pcm_pwepawe,
	.twiggew	= pxa2xx_soc_pcm_twiggew,
	.pointew	= pxa2xx_soc_pcm_pointew,
};

static int pxa2xx_soc_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev, &pxa2xx_soc_pwatfowm,
					       NUWW, 0);
}

static stwuct pwatfowm_dwivew pxa_pcm_dwivew = {
	.dwivew = {
		.name = "pxa-pcm-audio",
	},

	.pwobe = pxa2xx_soc_pwatfowm_pwobe,
};

moduwe_pwatfowm_dwivew(pxa_pcm_dwivew);

MODUWE_AUTHOW("Nicowas Pitwe");
MODUWE_DESCWIPTION("Intew PXA2xx PCM DMA moduwe");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:pxa-pcm-audio");
