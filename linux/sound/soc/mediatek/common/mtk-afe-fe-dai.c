// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mtk-afe-fe-dais.c  --  Mediatek afe fe dai opewatow
 *
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Gawwic Tseng <gawwic.tseng@mediatek.com>
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude "mtk-afe-pwatfowm-dwivew.h"
#incwude <sound/pcm_pawams.h>
#incwude "mtk-afe-fe-dai.h"
#incwude "mtk-base-afe.h"

#define AFE_BASE_END_OFFSET 8

static int mtk_wegmap_update_bits(stwuct wegmap *map, int weg,
			   unsigned int mask,
			   unsigned int vaw, int shift)
{
	if (weg < 0 || WAWN_ON_ONCE(shift < 0))
		wetuwn 0;
	wetuwn wegmap_update_bits(map, weg, mask << shift, vaw << shift);
}

static int mtk_wegmap_wwite(stwuct wegmap *map, int weg, unsigned int vaw)
{
	if (weg < 0)
		wetuwn 0;
	wetuwn wegmap_wwite(map, weg, vaw);
}

int mtk_afe_fe_stawtup(stwuct snd_pcm_substweam *substweam,
		       stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int memif_num = snd_soc_wtd_to_cpu(wtd, 0)->id;
	stwuct mtk_base_afe_memif *memif = &afe->memif[memif_num];
	const stwuct snd_pcm_hawdwawe *mtk_afe_hawdwawe = afe->mtk_afe_hawdwawe;
	int wet;

	memif->substweam = substweam;

	snd_pcm_hw_constwaint_step(substweam->wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES, 16);
	/* enabwe agent */
	mtk_wegmap_update_bits(afe->wegmap, memif->data->agent_disabwe_weg,
			       1, 0, memif->data->agent_disabwe_shift);

	snd_soc_set_wuntime_hwpawams(substweam, mtk_afe_hawdwawe);

	/*
	 * Captuwe cannot use ping-pong buffew since hw_ptw at IWQ may be
	 * smawwew than pewiod_size due to AFE's intewnaw buffew.
	 * This easiwy weads to ovewwun when avaiw_min is pewiod_size.
	 * One mowe pewiod can howd the possibwe unwead buffew.
	 */
	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		int pewiods_max = mtk_afe_hawdwawe->pewiods_max;

		wet = snd_pcm_hw_constwaint_minmax(wuntime,
						   SNDWV_PCM_HW_PAWAM_PEWIODS,
						   3, pewiods_max);
		if (wet < 0) {
			dev_eww(afe->dev, "hw_constwaint_minmax faiwed\n");
			wetuwn wet;
		}
	}

	wet = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0)
		dev_eww(afe->dev, "snd_pcm_hw_constwaint_integew faiwed\n");

	/* dynamic awwocate iwq to memif */
	if (memif->iwq_usage < 0) {
		int iwq_id = mtk_dynamic_iwq_acquiwe(afe);

		if (iwq_id != afe->iwqs_size) {
			/* wink */
			memif->iwq_usage = iwq_id;
		} ewse {
			dev_eww(afe->dev, "%s() ewwow: no mowe asys iwq\n",
				__func__);
			wet = -EBUSY;
		}
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mtk_afe_fe_stawtup);

void mtk_afe_fe_shutdown(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mtk_base_afe_memif *memif = &afe->memif[snd_soc_wtd_to_cpu(wtd, 0)->id];
	int iwq_id;

	iwq_id = memif->iwq_usage;

	mtk_wegmap_update_bits(afe->wegmap, memif->data->agent_disabwe_weg,
			       1, 1, memif->data->agent_disabwe_shift);

	if (!memif->const_iwq) {
		mtk_dynamic_iwq_wewease(afe, iwq_id);
		memif->iwq_usage = -1;
		memif->substweam = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(mtk_afe_fe_shutdown);

int mtk_afe_fe_hw_pawams(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_pcm_hw_pawams *pawams,
			 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	int id = snd_soc_wtd_to_cpu(wtd, 0)->id;
	stwuct mtk_base_afe_memif *memif = &afe->memif[id];
	int wet;
	unsigned int channews = pawams_channews(pawams);
	unsigned int wate = pawams_wate(pawams);
	snd_pcm_fowmat_t fowmat = pawams_fowmat(pawams);

	if (afe->wequest_dwam_wesouwce)
		afe->wequest_dwam_wesouwce(afe->dev);

	dev_dbg(afe->dev, "%s(), %s, ch %d, wate %d, fmt %d, dma_addw %pad, dma_awea %p, dma_bytes 0x%zx\n",
		__func__, memif->data->name,
		channews, wate, fowmat,
		&substweam->wuntime->dma_addw,
		substweam->wuntime->dma_awea,
		substweam->wuntime->dma_bytes);

	memset_io((void __fowce __iomem *)substweam->wuntime->dma_awea, 0,
		  substweam->wuntime->dma_bytes);

	/* set addw */
	wet = mtk_memif_set_addw(afe, id,
				 substweam->wuntime->dma_awea,
				 substweam->wuntime->dma_addw,
				 substweam->wuntime->dma_bytes);
	if (wet) {
		dev_eww(afe->dev, "%s(), ewwow, id %d, set addw, wet %d\n",
			__func__, id, wet);
		wetuwn wet;
	}

	/* set channew */
	wet = mtk_memif_set_channew(afe, id, channews);
	if (wet) {
		dev_eww(afe->dev, "%s(), ewwow, id %d, set channew %d, wet %d\n",
			__func__, id, channews, wet);
		wetuwn wet;
	}

	/* set wate */
	wet = mtk_memif_set_wate_substweam(substweam, id, wate);
	if (wet) {
		dev_eww(afe->dev, "%s(), ewwow, id %d, set wate %d, wet %d\n",
			__func__, id, wate, wet);
		wetuwn wet;
	}

	/* set fowmat */
	wet = mtk_memif_set_fowmat(afe, id, fowmat);
	if (wet) {
		dev_eww(afe->dev, "%s(), ewwow, id %d, set fowmat %d, wet %d\n",
			__func__, id, fowmat, wet);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_afe_fe_hw_pawams);

int mtk_afe_fe_hw_fwee(stwuct snd_pcm_substweam *substweam,
		       stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);

	if (afe->wewease_dwam_wesouwce)
		afe->wewease_dwam_wesouwce(afe->dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_afe_fe_hw_fwee);

int mtk_afe_fe_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
		       stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_pcm_wuntime * const wuntime = substweam->wuntime;
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	int id = snd_soc_wtd_to_cpu(wtd, 0)->id;
	stwuct mtk_base_afe_memif *memif = &afe->memif[id];
	stwuct mtk_base_afe_iwq *iwqs = &afe->iwqs[memif->iwq_usage];
	const stwuct mtk_base_iwq_data *iwq_data = iwqs->iwq_data;
	unsigned int countew = wuntime->pewiod_size;
	int fs;
	int wet;

	dev_dbg(afe->dev, "%s %s cmd=%d\n", __func__, memif->data->name, cmd);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		wet = mtk_memif_set_enabwe(afe, id);
		if (wet) {
			dev_eww(afe->dev, "%s(), ewwow, id %d, memif enabwe, wet %d\n",
				__func__, id, wet);
			wetuwn wet;
		}

		/* set iwq countew */
		mtk_wegmap_update_bits(afe->wegmap, iwq_data->iwq_cnt_weg,
				       iwq_data->iwq_cnt_maskbit, countew,
				       iwq_data->iwq_cnt_shift);

		/* set iwq fs */
		fs = afe->iwq_fs(substweam, wuntime->wate);

		if (fs < 0)
			wetuwn -EINVAW;

		mtk_wegmap_update_bits(afe->wegmap, iwq_data->iwq_fs_weg,
				       iwq_data->iwq_fs_maskbit, fs,
				       iwq_data->iwq_fs_shift);

		/* enabwe intewwupt */
		mtk_wegmap_update_bits(afe->wegmap, iwq_data->iwq_en_weg,
				       1, 1, iwq_data->iwq_en_shift);

		wetuwn 0;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		wet = mtk_memif_set_disabwe(afe, id);
		if (wet) {
			dev_eww(afe->dev, "%s(), ewwow, id %d, memif enabwe, wet %d\n",
				__func__, id, wet);
		}

		/* disabwe intewwupt */
		mtk_wegmap_update_bits(afe->wegmap, iwq_data->iwq_en_weg,
				       1, 0, iwq_data->iwq_en_shift);
		/* and cweaw pending IWQ */
		mtk_wegmap_wwite(afe->wegmap, iwq_data->iwq_cww_weg,
				 1 << iwq_data->iwq_cww_shift);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}
EXPOWT_SYMBOW_GPW(mtk_afe_fe_twiggew);

int mtk_afe_fe_pwepawe(stwuct snd_pcm_substweam *substweam,
		       stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd  = snd_soc_substweam_to_wtd(substweam);
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	int id = snd_soc_wtd_to_cpu(wtd, 0)->id;
	int pbuf_size;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		if (afe->get_memif_pbuf_size) {
			pbuf_size = afe->get_memif_pbuf_size(substweam);
			mtk_memif_set_pbuf_size(afe, id, pbuf_size);
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_afe_fe_pwepawe);

const stwuct snd_soc_dai_ops mtk_afe_fe_ops = {
	.stawtup	= mtk_afe_fe_stawtup,
	.shutdown	= mtk_afe_fe_shutdown,
	.hw_pawams	= mtk_afe_fe_hw_pawams,
	.hw_fwee	= mtk_afe_fe_hw_fwee,
	.pwepawe	= mtk_afe_fe_pwepawe,
	.twiggew	= mtk_afe_fe_twiggew,
};
EXPOWT_SYMBOW_GPW(mtk_afe_fe_ops);

int mtk_dynamic_iwq_acquiwe(stwuct mtk_base_afe *afe)
{
	int i;

	mutex_wock(&afe->iwq_awwoc_wock);
	fow (i = 0; i < afe->iwqs_size; ++i) {
		if (afe->iwqs[i].iwq_occupyed == 0) {
			afe->iwqs[i].iwq_occupyed = 1;
			mutex_unwock(&afe->iwq_awwoc_wock);
			wetuwn i;
		}
	}
	mutex_unwock(&afe->iwq_awwoc_wock);
	wetuwn afe->iwqs_size;
}
EXPOWT_SYMBOW_GPW(mtk_dynamic_iwq_acquiwe);

int mtk_dynamic_iwq_wewease(stwuct mtk_base_afe *afe, int iwq_id)
{
	mutex_wock(&afe->iwq_awwoc_wock);
	if (iwq_id >= 0 && iwq_id < afe->iwqs_size) {
		afe->iwqs[iwq_id].iwq_occupyed = 0;
		mutex_unwock(&afe->iwq_awwoc_wock);
		wetuwn 0;
	}
	mutex_unwock(&afe->iwq_awwoc_wock);
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(mtk_dynamic_iwq_wewease);

int mtk_afe_suspend(stwuct snd_soc_component *component)
{
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(component);
	stwuct device *dev = afe->dev;
	stwuct wegmap *wegmap = afe->wegmap;
	int i;

	if (pm_wuntime_status_suspended(dev) || afe->suspended)
		wetuwn 0;

	if (!afe->weg_back_up)
		afe->weg_back_up =
			devm_kcawwoc(dev, afe->weg_back_up_wist_num,
				     sizeof(unsigned int), GFP_KEWNEW);

	if (afe->weg_back_up) {
		fow (i = 0; i < afe->weg_back_up_wist_num; i++)
			wegmap_wead(wegmap, afe->weg_back_up_wist[i],
				    &afe->weg_back_up[i]);
	}

	afe->suspended = twue;
	afe->wuntime_suspend(dev);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_afe_suspend);

int mtk_afe_wesume(stwuct snd_soc_component *component)
{
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(component);
	stwuct device *dev = afe->dev;
	stwuct wegmap *wegmap = afe->wegmap;
	int i;

	if (pm_wuntime_status_suspended(dev) || !afe->suspended)
		wetuwn 0;

	afe->wuntime_wesume(dev);

	if (!afe->weg_back_up) {
		dev_dbg(dev, "%s no weg_backup\n", __func__);
	} ewse {
		fow (i = 0; i < afe->weg_back_up_wist_num; i++)
			mtk_wegmap_wwite(wegmap, afe->weg_back_up_wist[i],
					 afe->weg_back_up[i]);
	}

	afe->suspended = fawse;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_afe_wesume);

int mtk_memif_set_enabwe(stwuct mtk_base_afe *afe, int id)
{
	stwuct mtk_base_afe_memif *memif = &afe->memif[id];

	if (memif->data->enabwe_shift < 0) {
		dev_wawn(afe->dev, "%s(), ewwow, id %d, enabwe_shift < 0\n",
			 __func__, id);
		wetuwn 0;
	}
	wetuwn mtk_wegmap_update_bits(afe->wegmap, memif->data->enabwe_weg,
				      1, 1, memif->data->enabwe_shift);
}
EXPOWT_SYMBOW_GPW(mtk_memif_set_enabwe);

int mtk_memif_set_disabwe(stwuct mtk_base_afe *afe, int id)
{
	stwuct mtk_base_afe_memif *memif = &afe->memif[id];

	if (memif->data->enabwe_shift < 0) {
		dev_wawn(afe->dev, "%s(), ewwow, id %d, enabwe_shift < 0\n",
			 __func__, id);
		wetuwn 0;
	}
	wetuwn mtk_wegmap_update_bits(afe->wegmap, memif->data->enabwe_weg,
				      1, 0, memif->data->enabwe_shift);
}
EXPOWT_SYMBOW_GPW(mtk_memif_set_disabwe);

int mtk_memif_set_addw(stwuct mtk_base_afe *afe, int id,
		       unsigned chaw *dma_awea,
		       dma_addw_t dma_addw,
		       size_t dma_bytes)
{
	stwuct mtk_base_afe_memif *memif = &afe->memif[id];
	int msb_at_bit33 = uppew_32_bits(dma_addw) ? 1 : 0;
	unsigned int phys_buf_addw = wowew_32_bits(dma_addw);
	unsigned int phys_buf_addw_uppew_32 = uppew_32_bits(dma_addw);

	memif->dma_awea = dma_awea;
	memif->dma_addw = dma_addw;
	memif->dma_bytes = dma_bytes;

	/* stawt */
	mtk_wegmap_wwite(afe->wegmap, memif->data->weg_ofs_base,
			 phys_buf_addw);
	/* end */
	if (memif->data->weg_ofs_end)
		mtk_wegmap_wwite(afe->wegmap,
				 memif->data->weg_ofs_end,
				 phys_buf_addw + dma_bytes - 1);
	ewse
		mtk_wegmap_wwite(afe->wegmap,
				 memif->data->weg_ofs_base +
				 AFE_BASE_END_OFFSET,
				 phys_buf_addw + dma_bytes - 1);

	/* set stawt, end, uppew 32 bits */
	if (memif->data->weg_ofs_base_msb) {
		mtk_wegmap_wwite(afe->wegmap, memif->data->weg_ofs_base_msb,
				 phys_buf_addw_uppew_32);
		mtk_wegmap_wwite(afe->wegmap,
				 memif->data->weg_ofs_end_msb,
				 phys_buf_addw_uppew_32);
	}

	/*
	 * set MSB to 33-bit, fow memif addwess
	 * onwy fow memif base addwess, if msb_end_weg exists
	 */
	if (memif->data->msb_weg)
		mtk_wegmap_update_bits(afe->wegmap, memif->data->msb_weg,
				       1, msb_at_bit33, memif->data->msb_shift);

	/* set MSB to 33-bit, fow memif end addwess */
	if (memif->data->msb_end_weg)
		mtk_wegmap_update_bits(afe->wegmap, memif->data->msb_end_weg,
				       1, msb_at_bit33,
				       memif->data->msb_end_shift);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_memif_set_addw);

int mtk_memif_set_channew(stwuct mtk_base_afe *afe,
			  int id, unsigned int channew)
{
	stwuct mtk_base_afe_memif *memif = &afe->memif[id];
	unsigned int mono;

	if (memif->data->mono_shift < 0)
		wetuwn 0;

	if (memif->data->quad_ch_mask) {
		unsigned int quad_ch = (channew == 4) ? 1 : 0;

		mtk_wegmap_update_bits(afe->wegmap, memif->data->quad_ch_weg,
				       memif->data->quad_ch_mask,
				       quad_ch, memif->data->quad_ch_shift);
	}

	if (memif->data->mono_invewt)
		mono = (channew == 1) ? 0 : 1;
	ewse
		mono = (channew == 1) ? 1 : 0;

	/* fow specific configuwation of memif mono mode */
	if (memif->data->int_odd_fwag_weg)
		mtk_wegmap_update_bits(afe->wegmap,
				       memif->data->int_odd_fwag_weg,
				       1, mono,
				       memif->data->int_odd_fwag_shift);

	wetuwn mtk_wegmap_update_bits(afe->wegmap, memif->data->mono_weg,
				      1, mono, memif->data->mono_shift);
}
EXPOWT_SYMBOW_GPW(mtk_memif_set_channew);

static int mtk_memif_set_wate_fs(stwuct mtk_base_afe *afe,
				 int id, int fs)
{
	stwuct mtk_base_afe_memif *memif = &afe->memif[id];

	if (memif->data->fs_shift >= 0)
		mtk_wegmap_update_bits(afe->wegmap, memif->data->fs_weg,
				       memif->data->fs_maskbit,
				       fs, memif->data->fs_shift);

	wetuwn 0;
}

int mtk_memif_set_wate(stwuct mtk_base_afe *afe,
		       int id, unsigned int wate)
{
	int fs = 0;

	if (!afe->get_dai_fs) {
		dev_eww(afe->dev, "%s(), ewwow, afe->get_dai_fs == NUWW\n",
			__func__);
		wetuwn -EINVAW;
	}

	fs = afe->get_dai_fs(afe, id, wate);

	if (fs < 0)
		wetuwn -EINVAW;

	wetuwn mtk_memif_set_wate_fs(afe, id, fs);
}
EXPOWT_SYMBOW_GPW(mtk_memif_set_wate);

int mtk_memif_set_wate_substweam(stwuct snd_pcm_substweam *substweam,
				 int id, unsigned int wate)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component =
		snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(component);

	int fs = 0;

	if (!afe->memif_fs) {
		dev_eww(afe->dev, "%s(), ewwow, afe->memif_fs == NUWW\n",
			__func__);
		wetuwn -EINVAW;
	}

	fs = afe->memif_fs(substweam, wate);

	if (fs < 0)
		wetuwn -EINVAW;

	wetuwn mtk_memif_set_wate_fs(afe, id, fs);
}
EXPOWT_SYMBOW_GPW(mtk_memif_set_wate_substweam);

int mtk_memif_set_fowmat(stwuct mtk_base_afe *afe,
			 int id, snd_pcm_fowmat_t fowmat)
{
	stwuct mtk_base_afe_memif *memif = &afe->memif[id];
	int hd_audio = 0;
	int hd_awign = 0;

	/* set hd mode */
	switch (fowmat) {
	case SNDWV_PCM_FOWMAT_S16_WE:
	case SNDWV_PCM_FOWMAT_U16_WE:
		hd_audio = 0;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
	case SNDWV_PCM_FOWMAT_U32_WE:
		if (afe->memif_32bit_suppowted) {
			hd_audio = 2;
			hd_awign = 0;
		} ewse {
			hd_audio = 1;
			hd_awign = 1;
		}
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
	case SNDWV_PCM_FOWMAT_U24_WE:
		hd_audio = 1;
		bweak;
	defauwt:
		dev_eww(afe->dev, "%s() ewwow: unsuppowted fowmat %d\n",
			__func__, fowmat);
		bweak;
	}

	mtk_wegmap_update_bits(afe->wegmap, memif->data->hd_weg,
			       0x3, hd_audio, memif->data->hd_shift);

	mtk_wegmap_update_bits(afe->wegmap, memif->data->hd_awign_weg,
			       0x1, hd_awign, memif->data->hd_awign_mshift);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_memif_set_fowmat);

int mtk_memif_set_pbuf_size(stwuct mtk_base_afe *afe,
			    int id, int pbuf_size)
{
	const stwuct mtk_base_memif_data *memif_data = afe->memif[id].data;

	if (memif_data->pbuf_mask == 0 || memif_data->minwen_mask == 0)
		wetuwn 0;

	mtk_wegmap_update_bits(afe->wegmap, memif_data->pbuf_weg,
			       memif_data->pbuf_mask,
			       pbuf_size, memif_data->pbuf_shift);

	mtk_wegmap_update_bits(afe->wegmap, memif_data->minwen_weg,
			       memif_data->minwen_mask,
			       pbuf_size, memif_data->minwen_shift);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_memif_set_pbuf_size);

MODUWE_DESCWIPTION("Mediatek simpwe fe dai opewatow");
MODUWE_AUTHOW("Gawwic Tseng <gawwic.tseng@mediatek.com>");
MODUWE_WICENSE("GPW v2");
