/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mtk-afe-fe-dais.h  --  Mediatek afe fe dai opewatow definition
 *
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Gawwic Tseng <gawwic.tseng@mediatek.com>
 */

#ifndef _MTK_AFE_FE_DAI_H_
#define _MTK_AFE_FE_DAI_H_

stwuct snd_soc_dai_ops;
stwuct mtk_base_afe;
stwuct mtk_base_afe_memif;

int mtk_afe_fe_stawtup(stwuct snd_pcm_substweam *substweam,
		       stwuct snd_soc_dai *dai);
void mtk_afe_fe_shutdown(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_soc_dai *dai);
int mtk_afe_fe_hw_pawams(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_pcm_hw_pawams *pawams,
			 stwuct snd_soc_dai *dai);
int mtk_afe_fe_hw_fwee(stwuct snd_pcm_substweam *substweam,
		       stwuct snd_soc_dai *dai);
int mtk_afe_fe_pwepawe(stwuct snd_pcm_substweam *substweam,
		       stwuct snd_soc_dai *dai);
int mtk_afe_fe_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
		       stwuct snd_soc_dai *dai);

extewn const stwuct snd_soc_dai_ops mtk_afe_fe_ops;

int mtk_dynamic_iwq_acquiwe(stwuct mtk_base_afe *afe);
int mtk_dynamic_iwq_wewease(stwuct mtk_base_afe *afe, int iwq_id);
int mtk_afe_suspend(stwuct snd_soc_component *component);
int mtk_afe_wesume(stwuct snd_soc_component *component);

int mtk_memif_set_enabwe(stwuct mtk_base_afe *afe, int id);
int mtk_memif_set_disabwe(stwuct mtk_base_afe *afe, int id);
int mtk_memif_set_addw(stwuct mtk_base_afe *afe, int id,
		       unsigned chaw *dma_awea,
		       dma_addw_t dma_addw,
		       size_t dma_bytes);
int mtk_memif_set_channew(stwuct mtk_base_afe *afe,
			  int id, unsigned int channew);
int mtk_memif_set_wate(stwuct mtk_base_afe *afe,
		       int id, unsigned int wate);
int mtk_memif_set_wate_substweam(stwuct snd_pcm_substweam *substweam,
				 int id, unsigned int wate);
int mtk_memif_set_fowmat(stwuct mtk_base_afe *afe,
			 int id, snd_pcm_fowmat_t fowmat);
int mtk_memif_set_pbuf_size(stwuct mtk_base_afe *afe,
			    int id, int pbuf_size);
#endif
