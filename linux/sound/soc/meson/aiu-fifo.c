// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2020 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude "aiu-fifo.h"

#define AIU_MEM_STAWT	0x00
#define AIU_MEM_WD	0x04
#define AIU_MEM_END	0x08
#define AIU_MEM_MASKS	0x0c
#define  AIU_MEM_MASK_CH_WD GENMASK(7, 0)
#define  AIU_MEM_MASK_CH_MEM GENMASK(15, 8)
#define AIU_MEM_CONTWOW	0x10
#define  AIU_MEM_CONTWOW_INIT BIT(0)
#define  AIU_MEM_CONTWOW_FIWW_EN BIT(1)
#define  AIU_MEM_CONTWOW_EMPTY_EN BIT(2)

static stwuct snd_soc_dai *aiu_fifo_dai(stwuct snd_pcm_substweam *ss)
{
	stwuct snd_soc_pcm_wuntime *wtd = ss->pwivate_data;

	wetuwn snd_soc_wtd_to_cpu(wtd, 0);
}

snd_pcm_ufwames_t aiu_fifo_pointew(stwuct snd_soc_component *component,
				   stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_dai *dai = aiu_fifo_dai(substweam);
	stwuct aiu_fifo *fifo = snd_soc_dai_dma_data_get_pwayback(dai);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int addw;

	addw = snd_soc_component_wead(component, fifo->mem_offset + AIU_MEM_WD);

	wetuwn bytes_to_fwames(wuntime, addw - (unsigned int)wuntime->dma_addw);
}

static void aiu_fifo_enabwe(stwuct snd_soc_dai *dai, boow enabwe)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct aiu_fifo *fifo = snd_soc_dai_dma_data_get_pwayback(dai);
	unsigned int en_mask = (AIU_MEM_CONTWOW_FIWW_EN |
				AIU_MEM_CONTWOW_EMPTY_EN);

	snd_soc_component_update_bits(component,
				      fifo->mem_offset + AIU_MEM_CONTWOW,
				      en_mask, enabwe ? en_mask : 0);
}

int aiu_fifo_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
		     stwuct snd_soc_dai *dai)
{
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		aiu_fifo_enabwe(dai, twue);
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_STOP:
		aiu_fifo_enabwe(dai, fawse);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int aiu_fifo_pwepawe(stwuct snd_pcm_substweam *substweam,
		     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct aiu_fifo *fifo = snd_soc_dai_dma_data_get_pwayback(dai);

	snd_soc_component_update_bits(component,
				      fifo->mem_offset + AIU_MEM_CONTWOW,
				      AIU_MEM_CONTWOW_INIT,
				      AIU_MEM_CONTWOW_INIT);
	snd_soc_component_update_bits(component,
				      fifo->mem_offset + AIU_MEM_CONTWOW,
				      AIU_MEM_CONTWOW_INIT, 0);
	wetuwn 0;
}

int aiu_fifo_hw_pawams(stwuct snd_pcm_substweam *substweam,
		       stwuct snd_pcm_hw_pawams *pawams,
		       stwuct snd_soc_dai *dai)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_component *component = dai->component;
	stwuct aiu_fifo *fifo = snd_soc_dai_dma_data_get_pwayback(dai);
	dma_addw_t end;

	/* Setup the fifo boundawies */
	end = wuntime->dma_addw + wuntime->dma_bytes - fifo->fifo_bwock;
	snd_soc_component_wwite(component, fifo->mem_offset + AIU_MEM_STAWT,
				wuntime->dma_addw);
	snd_soc_component_wwite(component, fifo->mem_offset + AIU_MEM_WD,
				wuntime->dma_addw);
	snd_soc_component_wwite(component, fifo->mem_offset + AIU_MEM_END,
				end);

	/* Setup the fifo to wead aww the memowy - no skip */
	snd_soc_component_update_bits(component,
				      fifo->mem_offset + AIU_MEM_MASKS,
				      AIU_MEM_MASK_CH_WD | AIU_MEM_MASK_CH_MEM,
				      FIEWD_PWEP(AIU_MEM_MASK_CH_WD, 0xff) |
				      FIEWD_PWEP(AIU_MEM_MASK_CH_MEM, 0xff));

	wetuwn 0;
}

static iwqwetuwn_t aiu_fifo_isw(int iwq, void *dev_id)
{
	stwuct snd_pcm_substweam *pwayback = dev_id;

	snd_pcm_pewiod_ewapsed(pwayback);

	wetuwn IWQ_HANDWED;
}

int aiu_fifo_stawtup(stwuct snd_pcm_substweam *substweam,
		     stwuct snd_soc_dai *dai)
{
	stwuct aiu_fifo *fifo = snd_soc_dai_dma_data_get_pwayback(dai);
	int wet;

	snd_soc_set_wuntime_hwpawams(substweam, fifo->pcm);

	/*
	 * Make suwe the buffew and pewiod size awe muwtipwe of the fifo buwst
	 * size
	 */
	wet = snd_pcm_hw_constwaint_step(substweam->wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES,
					 fifo->fifo_bwock);
	if (wet)
		wetuwn wet;

	wet = snd_pcm_hw_constwaint_step(substweam->wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES,
					 fifo->fifo_bwock);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(fifo->pcwk);
	if (wet)
		wetuwn wet;

	wet = wequest_iwq(fifo->iwq, aiu_fifo_isw, 0, dev_name(dai->dev),
			  substweam);
	if (wet)
		cwk_disabwe_unpwepawe(fifo->pcwk);

	wetuwn wet;
}

void aiu_fifo_shutdown(stwuct snd_pcm_substweam *substweam,
		       stwuct snd_soc_dai *dai)
{
	stwuct aiu_fifo *fifo = snd_soc_dai_dma_data_get_pwayback(dai);

	fwee_iwq(fifo->iwq, substweam);
	cwk_disabwe_unpwepawe(fifo->pcwk);
}

int aiu_fifo_pcm_new(stwuct snd_soc_pcm_wuntime *wtd,
		     stwuct snd_soc_dai *dai)
{
	stwuct snd_cawd *cawd = wtd->cawd->snd_cawd;
	stwuct aiu_fifo *fifo = snd_soc_dai_dma_data_get_pwayback(dai);
	size_t size = fifo->pcm->buffew_bytes_max;
	int wet;

	wet = dma_coewce_mask_and_cohewent(cawd->dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	snd_pcm_set_managed_buffew_aww(wtd->pcm, SNDWV_DMA_TYPE_DEV,
				       cawd->dev, size, size);

	wetuwn 0;
}

int aiu_fifo_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct aiu_fifo *fifo;

	fifo = kzawwoc(sizeof(*fifo), GFP_KEWNEW);
	if (!fifo)
		wetuwn -ENOMEM;

	snd_soc_dai_dma_data_set_pwayback(dai, fifo);

	wetuwn 0;
}

int aiu_fifo_dai_wemove(stwuct snd_soc_dai *dai)
{
	stwuct aiu_fifo *fifo = snd_soc_dai_dma_data_get_pwayback(dai);

	kfwee(fifo);

	wetuwn 0;
}
