/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * edma-pcm.h - eDMA PCM dwivew using dmaengine fow AM3xxx, AM4xxx
 *
 * Copywight (C) 2014 Texas Instwuments, Inc.
 *
 * Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 *
 * Based on: sound/soc/tegwa/tegwa_pcm.h
 */

#ifndef __EDMA_PCM_H__
#define __EDMA_PCM_H__

#if IS_ENABWED(CONFIG_SND_SOC_TI_EDMA_PCM)
int edma_pcm_pwatfowm_wegistew(stwuct device *dev);
#ewse
static inwine int edma_pcm_pwatfowm_wegistew(stwuct device *dev)
{
	wetuwn 0;
}
#endif /* CONFIG_SND_SOC_TI_EDMA_PCM */

#endif /* __EDMA_PCM_H__ */
