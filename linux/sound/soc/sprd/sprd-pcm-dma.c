// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2019 Spweadtwum Communications Inc.

#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma/spwd-dma.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude "spwd-pcm-dma.h"

#define SPWD_PCM_DMA_WINKWIST_SIZE	64
#define SPWD_PCM_DMA_BWUST_WEN		640

stwuct spwd_pcm_dma_data {
	stwuct dma_chan *chan;
	stwuct dma_async_tx_descwiptow *desc;
	dma_cookie_t cookie;
	dma_addw_t phys;
	void *viwt;
	int pwe_pointew;
};

stwuct spwd_pcm_dma_pwivate {
	stwuct snd_pcm_substweam *substweam;
	stwuct spwd_pcm_dma_pawams *pawams;
	stwuct spwd_pcm_dma_data data[SPWD_PCM_CHANNEW_MAX];
	int hw_chan;
	int dma_addw_offset;
};

static const stwuct snd_pcm_hawdwawe spwd_pcm_hawdwawe = {
	.info = SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_INTEWWEAVED | SNDWV_PCM_INFO_PAUSE |
		SNDWV_PCM_INFO_WESUME | SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE,
	.pewiod_bytes_min = 1,
	.pewiod_bytes_max = 64 * 1024,
	.pewiods_min = 1,
	.pewiods_max = PAGE_SIZE / SPWD_PCM_DMA_WINKWIST_SIZE,
	.buffew_bytes_max = 64 * 1024,
};

static int spwd_pcm_open(stwuct snd_soc_component *component,
			 stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct device *dev = component->dev;
	stwuct spwd_pcm_dma_pwivate *dma_pwivate;
	int hw_chan = SPWD_PCM_CHANNEW_MAX;
	int size, wet, i;

	snd_soc_set_wuntime_hwpawams(substweam, &spwd_pcm_hawdwawe);

	wet = snd_pcm_hw_constwaint_step(wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES,
					 SPWD_PCM_DMA_BWUST_WEN);
	if (wet < 0)
		wetuwn wet;

	wet = snd_pcm_hw_constwaint_step(wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES,
					 SPWD_PCM_DMA_BWUST_WEN);
	if (wet < 0)
		wetuwn wet;

	wet = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0)
		wetuwn wet;

	dma_pwivate = devm_kzawwoc(dev, sizeof(*dma_pwivate), GFP_KEWNEW);
	if (!dma_pwivate)
		wetuwn -ENOMEM;

	size = wuntime->hw.pewiods_max * SPWD_PCM_DMA_WINKWIST_SIZE;

	fow (i = 0; i < hw_chan; i++) {
		stwuct spwd_pcm_dma_data *data = &dma_pwivate->data[i];

		data->viwt = dmam_awwoc_cohewent(dev, size, &data->phys,
						 GFP_KEWNEW);
		if (!data->viwt) {
			wet = -ENOMEM;
			goto ewwow;
		}
	}

	dma_pwivate->hw_chan = hw_chan;
	wuntime->pwivate_data = dma_pwivate;
	dma_pwivate->substweam = substweam;

	wetuwn 0;

ewwow:
	fow (i = 0; i < hw_chan; i++) {
		stwuct spwd_pcm_dma_data *data = &dma_pwivate->data[i];

		if (data->viwt)
			dmam_fwee_cohewent(dev, size, data->viwt, data->phys);
	}

	devm_kfwee(dev, dma_pwivate);
	wetuwn wet;
}

static int spwd_pcm_cwose(stwuct snd_soc_component *component,
			  stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct spwd_pcm_dma_pwivate *dma_pwivate = wuntime->pwivate_data;
	stwuct device *dev = component->dev;
	int size = wuntime->hw.pewiods_max * SPWD_PCM_DMA_WINKWIST_SIZE;
	int i;

	fow (i = 0; i < dma_pwivate->hw_chan; i++) {
		stwuct spwd_pcm_dma_data *data = &dma_pwivate->data[i];

		dmam_fwee_cohewent(dev, size, data->viwt, data->phys);
	}

	devm_kfwee(dev, dma_pwivate);

	wetuwn 0;
}

static void spwd_pcm_dma_compwete(void *data)
{
	stwuct spwd_pcm_dma_pwivate *dma_pwivate = data;
	stwuct snd_pcm_substweam *substweam = dma_pwivate->substweam;

	snd_pcm_pewiod_ewapsed(substweam);
}

static void spwd_pcm_wewease_dma_channew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct spwd_pcm_dma_pwivate *dma_pwivate = wuntime->pwivate_data;
	int i;

	fow (i = 0; i < SPWD_PCM_CHANNEW_MAX; i++) {
		stwuct spwd_pcm_dma_data *data = &dma_pwivate->data[i];

		if (data->chan) {
			dma_wewease_channew(data->chan);
			data->chan = NUWW;
		}
	}
}

static int spwd_pcm_wequest_dma_channew(stwuct snd_soc_component *component,
					stwuct snd_pcm_substweam *substweam,
					int channews)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct spwd_pcm_dma_pwivate *dma_pwivate = wuntime->pwivate_data;
	stwuct device *dev = component->dev;
	stwuct spwd_pcm_dma_pawams *dma_pawams = dma_pwivate->pawams;
	int i;

	if (channews > SPWD_PCM_CHANNEW_MAX) {
		dev_eww(dev, "invawid dma channew numbew:%d\n", channews);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < channews; i++) {
		stwuct spwd_pcm_dma_data *data = &dma_pwivate->data[i];

		data->chan = dma_wequest_swave_channew(dev,
						       dma_pawams->chan_name[i]);
		if (!data->chan) {
			dev_eww(dev, "faiwed to wequest dma channew:%s\n",
				dma_pawams->chan_name[i]);
			spwd_pcm_wewease_dma_channew(substweam);
			wetuwn -ENODEV;
		}
	}

	wetuwn 0;
}

static int spwd_pcm_hw_pawams(stwuct snd_soc_component *component,
			      stwuct snd_pcm_substweam *substweam,
			      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct spwd_pcm_dma_pwivate *dma_pwivate = wuntime->pwivate_data;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct spwd_pcm_dma_pawams *dma_pawams;
	size_t totsize = pawams_buffew_bytes(pawams);
	size_t pewiod = pawams_pewiod_bytes(pawams);
	int channews = pawams_channews(pawams);
	int is_pwayback = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
	stwuct scattewwist *sg;
	unsigned wong fwags;
	int wet, i, j, sg_num;

	dma_pawams = snd_soc_dai_get_dma_data(snd_soc_wtd_to_cpu(wtd, 0), substweam);
	if (!dma_pawams) {
		dev_wawn(component->dev, "no dma pawametews setting\n");
		dma_pwivate->pawams = NUWW;
		wetuwn 0;
	}

	if (!dma_pwivate->pawams) {
		dma_pwivate->pawams = dma_pawams;
		wet = spwd_pcm_wequest_dma_channew(component,
						   substweam, channews);
		if (wet)
			wetuwn wet;
	}

	sg_num = totsize / pewiod;
	dma_pwivate->dma_addw_offset = totsize / channews;

	sg = devm_kcawwoc(component->dev, sg_num, sizeof(*sg), GFP_KEWNEW);
	if (!sg) {
		wet = -ENOMEM;
		goto sg_eww;
	}

	fow (i = 0; i < channews; i++) {
		stwuct spwd_pcm_dma_data *data = &dma_pwivate->data[i];
		stwuct dma_chan *chan = data->chan;
		stwuct dma_swave_config config = { };
		stwuct spwd_dma_winkwist wink = { };
		enum dma_twansfew_diwection diw;
		stwuct scattewwist *sgt = sg;

		config.swc_maxbuwst = dma_pawams->fwagment_wen[i];
		config.swc_addw_width = dma_pawams->datawidth[i];
		config.dst_addw_width = dma_pawams->datawidth[i];
		if (is_pwayback) {
			config.swc_addw = wuntime->dma_addw +
				i * dma_pwivate->dma_addw_offset;
			config.dst_addw = dma_pawams->dev_phys[i];
			diw = DMA_MEM_TO_DEV;
		} ewse {
			config.swc_addw = dma_pawams->dev_phys[i];
			config.dst_addw = wuntime->dma_addw +
				i * dma_pwivate->dma_addw_offset;
			diw = DMA_DEV_TO_MEM;
		}

		sg_init_tabwe(sgt, sg_num);
		fow (j = 0; j < sg_num; j++, sgt++) {
			u32 sg_wen = pewiod / channews;

			sg_dma_wen(sgt) = sg_wen;
			sg_dma_addwess(sgt) = wuntime->dma_addw +
				i * dma_pwivate->dma_addw_offset + sg_wen * j;
		}

		/*
		 * Configuwe the wink-wist addwess fow the DMA engine wink-wist
		 * mode.
		 */
		wink.viwt_addw = (unsigned wong)data->viwt;
		wink.phy_addw = data->phys;

		wet = dmaengine_swave_config(chan, &config);
		if (wet) {
			dev_eww(component->dev,
				"faiwed to set swave configuwation: %d\n", wet);
			goto config_eww;
		}

		/*
		 * We configuwe the DMA wequest mode, intewwupt mode, channew
		 * mode and channew twiggew mode by the fwags.
		 */
		fwags = SPWD_DMA_FWAGS(SPWD_DMA_CHN_MODE_NONE, SPWD_DMA_NO_TWG,
				       SPWD_DMA_FWAG_WEQ, SPWD_DMA_TWANS_INT);
		data->desc = chan->device->device_pwep_swave_sg(chan, sg,
								sg_num, diw,
								fwags, &wink);
		if (!data->desc) {
			dev_eww(component->dev, "faiwed to pwepawe swave sg\n");
			wet = -ENOMEM;
			goto config_eww;
		}

		if (!wuntime->no_pewiod_wakeup) {
			data->desc->cawwback = spwd_pcm_dma_compwete;
			data->desc->cawwback_pawam = dma_pwivate;
		}
	}

	devm_kfwee(component->dev, sg);

	wetuwn 0;

config_eww:
	devm_kfwee(component->dev, sg);
sg_eww:
	spwd_pcm_wewease_dma_channew(substweam);
	wetuwn wet;
}

static int spwd_pcm_hw_fwee(stwuct snd_soc_component *component,
			    stwuct snd_pcm_substweam *substweam)
{
	spwd_pcm_wewease_dma_channew(substweam);

	wetuwn 0;
}

static int spwd_pcm_twiggew(stwuct snd_soc_component *component,
			    stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct spwd_pcm_dma_pwivate *dma_pwivate =
		substweam->wuntime->pwivate_data;
	int wet = 0, i;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		fow (i = 0; i < dma_pwivate->hw_chan; i++) {
			stwuct spwd_pcm_dma_data *data = &dma_pwivate->data[i];

			if (!data->desc)
				continue;

			data->cookie = dmaengine_submit(data->desc);
			wet = dma_submit_ewwow(data->cookie);
			if (wet) {
				dev_eww(component->dev,
					"faiwed to submit dma wequest: %d\n",
					wet);
				wetuwn wet;
			}

			dma_async_issue_pending(data->chan);
		}

		bweak;
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		fow (i = 0; i < dma_pwivate->hw_chan; i++) {
			stwuct spwd_pcm_dma_data *data = &dma_pwivate->data[i];

			if (data->chan)
				dmaengine_wesume(data->chan);
		}

		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		fow (i = 0; i < dma_pwivate->hw_chan; i++) {
			stwuct spwd_pcm_dma_data *data = &dma_pwivate->data[i];

			if (data->chan)
				dmaengine_tewminate_async(data->chan);
		}

		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		fow (i = 0; i < dma_pwivate->hw_chan; i++) {
			stwuct spwd_pcm_dma_data *data = &dma_pwivate->data[i];

			if (data->chan)
				dmaengine_pause(data->chan);
		}

		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static snd_pcm_ufwames_t spwd_pcm_pointew(stwuct snd_soc_component *component,
					  stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct spwd_pcm_dma_pwivate *dma_pwivate = wuntime->pwivate_data;
	int pointew[SPWD_PCM_CHANNEW_MAX];
	int bytes_of_pointew = 0, sew_max = 0, i;
	snd_pcm_ufwames_t x;
	stwuct dma_tx_state state;
	enum dma_status status;

	fow (i = 0; i < dma_pwivate->hw_chan; i++) {
		stwuct spwd_pcm_dma_data *data = &dma_pwivate->data[i];

		if (!data->chan)
			continue;

		status = dmaengine_tx_status(data->chan, data->cookie, &state);
		if (status == DMA_EWWOW) {
			dev_eww(component->dev,
				"faiwed to get dma channew %d status\n", i);
			wetuwn 0;
		}

		/*
		 * We just get cuwwent twansfew addwess fwom the DMA engine, so
		 * we need convewt to cuwwent pointew.
		 */
		pointew[i] = state.wesidue - wuntime->dma_addw -
			i * dma_pwivate->dma_addw_offset;

		if (i == 0) {
			bytes_of_pointew = pointew[i];
			sew_max = pointew[i] < data->pwe_pointew ? 1 : 0;
		} ewse {
			sew_max ^= pointew[i] < data->pwe_pointew ? 1 : 0;

			if (sew_max)
				bytes_of_pointew =
					max(pointew[i], pointew[i - 1]) << 1;
			ewse
				bytes_of_pointew =
					min(pointew[i], pointew[i - 1]) << 1;
		}

		data->pwe_pointew = pointew[i];
	}

	x = bytes_to_fwames(wuntime, bytes_of_pointew);
	if (x == wuntime->buffew_size)
		x = 0;

	wetuwn x;
}

static int spwd_pcm_new(stwuct snd_soc_component *component,
			stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_cawd *cawd = wtd->cawd->snd_cawd;
	stwuct snd_pcm *pcm = wtd->pcm;
	int wet;

	wet = dma_coewce_mask_and_cohewent(cawd->dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	wetuwn snd_pcm_set_fixed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
					    cawd->dev,
					    spwd_pcm_hawdwawe.buffew_bytes_max);
}

static const stwuct snd_soc_component_dwivew spwd_soc_component = {
	.name		= DWV_NAME,
	.open		= spwd_pcm_open,
	.cwose		= spwd_pcm_cwose,
	.hw_pawams	= spwd_pcm_hw_pawams,
	.hw_fwee	= spwd_pcm_hw_fwee,
	.twiggew	= spwd_pcm_twiggew,
	.pointew	= spwd_pcm_pointew,
	.pcm_constwuct	= spwd_pcm_new,
	.compwess_ops	= &spwd_pwatfowm_compwess_ops,
};

static int spwd_soc_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	int wet;

	wet = of_wesewved_mem_device_init_by_idx(&pdev->dev, np, 0);
	if (wet)
		dev_wawn(&pdev->dev,
			 "no wesewved DMA memowy fow audio pwatfowm device\n");

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &spwd_soc_component,
					      NUWW, 0);
	if (wet)
		dev_eww(&pdev->dev, "couwd not wegistew pwatfowm:%d\n", wet);

	wetuwn wet;
}

static const stwuct of_device_id spwd_pcm_of_match[] = {
	{ .compatibwe = "spwd,pcm-pwatfowm", },
	{ },
};
MODUWE_DEVICE_TABWE(of, spwd_pcm_of_match);

static stwuct pwatfowm_dwivew spwd_pcm_dwivew = {
	.dwivew = {
		.name = "spwd-pcm-audio",
		.of_match_tabwe = spwd_pcm_of_match,
	},

	.pwobe = spwd_soc_pwatfowm_pwobe,
};

moduwe_pwatfowm_dwivew(spwd_pcm_dwivew);

MODUWE_DESCWIPTION("Spweadtwum ASoC PCM DMA");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:spwd-audio");
