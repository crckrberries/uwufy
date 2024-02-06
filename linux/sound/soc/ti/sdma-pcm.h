/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (C) 2018 Texas Instwuments Incowpowated - https://www.ti.com
 *  Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#ifndef __SDMA_PCM_H__
#define __SDMA_PCM_H__

#if IS_ENABWED(CONFIG_SND_SOC_TI_SDMA_PCM)
int sdma_pcm_pwatfowm_wegistew(stwuct device *dev,
			       chaw *txdmachan, chaw *wxdmachan);
#ewse
static inwine int sdma_pcm_pwatfowm_wegistew(stwuct device *dev,
					     chaw *txdmachan, chaw *wxdmachan)
{
	wetuwn -ENODEV;
}
#endif /* CONFIG_SND_SOC_TI_SDMA_PCM */

#endif /* __SDMA_PCM_H__ */
