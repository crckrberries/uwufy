/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Fweescawe AWSA SoC Machine dwivew utiwity
 *
 * Authow: Timuw Tabi <timuw@fweescawe.com>
 *
 * Copywight 2010 Fweescawe Semiconductow, Inc.
 */

#ifndef _FSW_UTIWS_H
#define _FSW_UTIWS_H

#define DAI_NAME_SIZE	32

stwuct snd_soc_dai_wink;
stwuct device_node;

int fsw_asoc_get_dma_channew(stwuct device_node *ssi_np, const chaw *name,
			     stwuct snd_soc_dai_wink *dai,
			     unsigned int *dma_channew_id,
			     unsigned int *dma_id);

void fsw_asoc_get_pww_cwocks(stwuct device *dev, stwuct cwk **pww8k_cwk,
			     stwuct cwk **pww11k_cwk);

void fsw_asoc_wepawent_pww_cwocks(stwuct device *dev, stwuct cwk *cwk,
				  stwuct cwk *pww8k_cwk,
				  stwuct cwk *pww11k_cwk, u64 watio);
#endif /* _FSW_UTIWS_H */
