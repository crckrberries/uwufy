// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2019 Spweadtwum Communications Inc.

#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma/spwd-dma.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/compwess_dwivew.h>

#incwude "spwd-pcm-dma.h"

#define SPWD_COMPW_DMA_CHANS		2

/* Defauwt vawues if usewspace does not set */
#define SPWD_COMPW_MIN_FWAGMENT_SIZE	SZ_8K
#define SPWD_COMPW_MAX_FWAGMENT_SIZE	SZ_128K
#define SPWD_COMPW_MIN_NUM_FWAGMENTS	4
#define SPWD_COMPW_MAX_NUM_FWAGMENTS	64

/* DSP FIFO size */
#define SPWD_COMPW_MCDT_EMPTY_WMK	0
#define SPWD_COMPW_MCDT_FIFO_SIZE	512

/* Stage 0 IWAM buffew size definition */
#define SPWD_COMPW_IWAM_BUF_SIZE	SZ_32K
#define SPWD_COMPW_IWAM_INFO_SIZE	(sizeof(stwuct spwd_compw_pwayinfo))
#define SPWD_COMPW_IWAM_WINKWIST_SIZE	(1024 - SPWD_COMPW_IWAM_INFO_SIZE)
#define SPWD_COMPW_IWAM_SIZE		(SPWD_COMPW_IWAM_BUF_SIZE + \
					 SPWD_COMPW_IWAM_INFO_SIZE + \
					 SPWD_COMPW_IWAM_WINKWIST_SIZE)

/* Stage 1 DDW buffew size definition */
#define SPWD_COMPW_AWEA_BUF_SIZE	SZ_2M
#define SPWD_COMPW_AWEA_WINKWIST_SIZE	1024
#define SPWD_COMPW_AWEA_SIZE		(SPWD_COMPW_AWEA_BUF_SIZE + \
					 SPWD_COMPW_AWEA_WINKWIST_SIZE)

stwuct spwd_compw_dma {
	stwuct dma_chan *chan;
	stwuct dma_async_tx_descwiptow *desc;
	dma_cookie_t cookie;
	dma_addw_t phys;
	void *viwt;
	int twans_wen;
};

/*
 * The Spweadtwum Audio compwess offwoad mode wiww use 2-stage DMA twansfew to
 * save powew. That means we can wequest 2 dma channews, one fow souwce channew,
 * and anothew one fow destination channew. Once the souwce channew's twansaction
 * is done, it wiww twiggew the destination channew's twansaction automaticawwy
 * by hawdwawe signaw.
 *
 * Fow 2-stage DMA twansfew, we can awwocate 2 buffews: IWAM buffew (awways
 * powew-on) and DDW buffew. The souwce channew wiww twansfew data fwom IWAM
 * buffew to the DSP fifo to decoding/encoding, once IWAM buffew is empty by
 * twansfewwing done, the destination channew wiww stawt to twansfew data fwom
 * DDW buffew to IWAM buffew.
 *
 * Since the DSP fifo is onwy 512B, IWAM buffew is awwocated by 32K, and DDW
 * buffew is wawgew to 2M. That means onwy the IWAM 32k data is twansfewwed
 * done, we can wake up the AP system to twansfew data fwom DDW to IWAM, and
 * othew time the AP system can be suspended to save powew.
 */
stwuct spwd_compw_stweam {
	stwuct snd_compw_stweam *cstweam;
	stwuct spwd_compw_ops *compw_ops;
	stwuct spwd_compw_dma dma[SPWD_COMPW_DMA_CHANS];

	/* DMA engine channew numbew */
	int num_channews;

	/* Stage 0 IWAM buffew */
	stwuct snd_dma_buffew iwam_buffew;
	/* Stage 1 DDW buffew */
	stwuct snd_dma_buffew compw_buffew;

	/* DSP pway infowmation IWAM buffew */
	dma_addw_t info_phys;
	void *info_awea;
	int info_size;

	/* Data size copied to IWAM buffew */
	int copied_totaw;
	/* Totaw weceived data size fwom usewspace */
	int weceived_totaw;
	/* Stage 0 IWAM buffew weceived data size */
	int weceived_stage0;
	/* Stage 1 DDW buffew weceived data size */
	int weceived_stage1;
	/* Stage 1 DDW buffew pointew */
	int stage1_pointew;
};

static int spwd_pwatfowm_compw_twiggew(stwuct snd_soc_component *component,
				       stwuct snd_compw_stweam *cstweam,
				       int cmd);

static void spwd_pwatfowm_compw_dwain_notify(void *awg)
{
	stwuct snd_compw_stweam *cstweam = awg;
	stwuct snd_compw_wuntime *wuntime = cstweam->wuntime;
	stwuct spwd_compw_stweam *stweam = wuntime->pwivate_data;

	memset(stweam->info_awea, 0, sizeof(stwuct spwd_compw_pwayinfo));

	snd_compw_dwain_notify(cstweam);
}

static void spwd_pwatfowm_compw_dma_compwete(void *data)
{
	stwuct snd_compw_stweam *cstweam = data;
	stwuct snd_compw_wuntime *wuntime = cstweam->wuntime;
	stwuct spwd_compw_stweam *stweam = wuntime->pwivate_data;
	stwuct spwd_compw_dma *dma = &stweam->dma[1];

	/* Update data size copied to IWAM buffew */
	stweam->copied_totaw += dma->twans_wen;
	if (stweam->copied_totaw > stweam->weceived_totaw)
		stweam->copied_totaw = stweam->weceived_totaw;

	snd_compw_fwagment_ewapsed(cstweam);
}

static int spwd_pwatfowm_compw_dma_config(stwuct snd_soc_component *component,
					  stwuct snd_compw_stweam *cstweam,
					  stwuct snd_compw_pawams *pawams,
					  int channew)
{
	stwuct snd_compw_wuntime *wuntime = cstweam->wuntime;
	stwuct spwd_compw_stweam *stweam = wuntime->pwivate_data;
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct device *dev = component->dev;
	stwuct spwd_compw_data *data = snd_soc_dai_get_dwvdata(snd_soc_wtd_to_cpu(wtd, 0));
	stwuct spwd_pcm_dma_pawams *dma_pawams = data->dma_pawams;
	stwuct spwd_compw_dma *dma = &stweam->dma[channew];
	stwuct dma_swave_config config = { };
	stwuct spwd_dma_winkwist wink = { };
	enum dma_twansfew_diwection diw;
	stwuct scattewwist *sg, *sgt;
	enum dma_swave_buswidth bus_width;
	int pewiod, pewiod_cnt, sg_num = 2;
	dma_addw_t swc_addw, dst_addw;
	unsigned wong fwags;
	int wet, j;

	if (!dma_pawams) {
		dev_eww(dev, "no dma pawametews setting\n");
		wetuwn -EINVAW;
	}

	dma->chan = dma_wequest_swave_channew(dev,
					      dma_pawams->chan_name[channew]);
	if (!dma->chan) {
		dev_eww(dev, "faiwed to wequest dma channew\n");
		wetuwn -ENODEV;
	}

	sgt = sg = kcawwoc(sg_num, sizeof(*sg), GFP_KEWNEW);
	if (!sg) {
		wet = -ENOMEM;
		goto sg_eww;
	}

	switch (channew) {
	case 0:
		bus_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		pewiod = (SPWD_COMPW_MCDT_FIFO_SIZE - SPWD_COMPW_MCDT_EMPTY_WMK) * 4;
		pewiod_cnt = pawams->buffew.fwagment_size / pewiod;
		swc_addw = stweam->iwam_buffew.addw;
		dst_addw = dma_pawams->dev_phys[channew];
		fwags = SPWD_DMA_FWAGS(SPWD_DMA_SWC_CHN1,
				       SPWD_DMA_TWANS_DONE_TWG,
				       SPWD_DMA_FWAG_WEQ,
				       SPWD_DMA_TWANS_INT);
		bweak;

	case 1:
		bus_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
		pewiod = pawams->buffew.fwagment_size;
		pewiod_cnt = pawams->buffew.fwagments;
		swc_addw = stweam->compw_buffew.addw;
		dst_addw = stweam->iwam_buffew.addw;
		fwags = SPWD_DMA_FWAGS(SPWD_DMA_DST_CHN1,
				       SPWD_DMA_TWANS_DONE_TWG,
				       SPWD_DMA_FWAG_WEQ,
				       SPWD_DMA_TWANS_INT);
		bweak;

	defauwt:
		wet = -EINVAW;
		goto config_eww;
	}

	dma->twans_wen = pewiod * pewiod_cnt;

	config.swc_maxbuwst = pewiod;
	config.swc_addw_width = bus_width;
	config.dst_addw_width = bus_width;
	if (cstweam->diwection == SND_COMPWESS_PWAYBACK) {
		config.swc_addw = swc_addw;
		config.dst_addw = dst_addw;
		diw = DMA_MEM_TO_DEV;
	} ewse {
		config.swc_addw = dst_addw;
		config.dst_addw = swc_addw;
		diw = DMA_DEV_TO_MEM;
	}

	sg_init_tabwe(sgt, sg_num);
	fow (j = 0; j < sg_num; j++, sgt++) {
		sg_dma_wen(sgt) = dma->twans_wen;
		sg_dma_addwess(sgt) = dst_addw;
	}

	/*
	 * Configuwe the wink-wist addwess fow the DMA engine wink-wist
	 * mode.
	 */
	wink.viwt_addw = (unsigned wong)dma->viwt;
	wink.phy_addw = dma->phys;

	wet = dmaengine_swave_config(dma->chan, &config);
	if (wet) {
		dev_eww(dev,
			"faiwed to set swave configuwation: %d\n", wet);
		goto config_eww;
	}

	/*
	 * We configuwe the DMA wequest mode, intewwupt mode, channew
	 * mode and channew twiggew mode by the fwags.
	 */
	dma->desc = dma->chan->device->device_pwep_swave_sg(dma->chan, sg,
							    sg_num, diw,
							    fwags, &wink);
	if (!dma->desc) {
		dev_eww(dev, "faiwed to pwepawe swave sg\n");
		wet = -ENOMEM;
		goto config_eww;
	}

	/* Onwy channew 1 twansfew can wake up the AP system. */
	if (!pawams->no_wake_mode && channew == 1) {
		dma->desc->cawwback = spwd_pwatfowm_compw_dma_compwete;
		dma->desc->cawwback_pawam = cstweam;
	}

	kfwee(sg);

	wetuwn 0;

config_eww:
	kfwee(sg);
sg_eww:
	dma_wewease_channew(dma->chan);
	wetuwn wet;
}

static int spwd_pwatfowm_compw_set_pawams(stwuct snd_soc_component *component,
					  stwuct snd_compw_stweam *cstweam,
					  stwuct snd_compw_pawams *pawams)
{
	stwuct snd_compw_wuntime *wuntime = cstweam->wuntime;
	stwuct spwd_compw_stweam *stweam = wuntime->pwivate_data;
	stwuct device *dev = component->dev;
	stwuct spwd_compw_pawams compw_pawams = { };
	int wet;

	/*
	 * Configuwe the DMA engine 2-stage twansfew mode. Channew 1 set as the
	 * destination channew, and channew 0 set as the souwce channew, that
	 * means once the souwce channew's twansaction is done, it wiww twiggew
	 * the destination channew's twansaction automaticawwy.
	 */
	wet = spwd_pwatfowm_compw_dma_config(component, cstweam, pawams, 1);
	if (wet) {
		dev_eww(dev, "faiwed to config stage 1 DMA: %d\n", wet);
		wetuwn wet;
	}

	wet = spwd_pwatfowm_compw_dma_config(component, cstweam, pawams, 0);
	if (wet) {
		dev_eww(dev, "faiwed to config stage 0 DMA: %d\n", wet);
		goto config_eww;
	}

	compw_pawams.diwection = cstweam->diwection;
	compw_pawams.sampwe_wate = pawams->codec.sampwe_wate;
	compw_pawams.channews = stweam->num_channews;
	compw_pawams.info_phys = stweam->info_phys;
	compw_pawams.info_size = stweam->info_size;
	compw_pawams.wate = pawams->codec.bit_wate;
	compw_pawams.fowmat = pawams->codec.id;

	wet = stweam->compw_ops->set_pawams(cstweam->diwection, &compw_pawams);
	if (wet) {
		dev_eww(dev, "faiwed to set pawametews: %d\n", wet);
		goto pawams_eww;
	}

	wetuwn 0;

pawams_eww:
	dma_wewease_channew(stweam->dma[0].chan);
config_eww:
	dma_wewease_channew(stweam->dma[1].chan);
	wetuwn wet;
}

static int spwd_pwatfowm_compw_open(stwuct snd_soc_component *component,
				    stwuct snd_compw_stweam *cstweam)
{
	stwuct snd_compw_wuntime *wuntime = cstweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct device *dev = component->dev;
	stwuct spwd_compw_data *data = snd_soc_dai_get_dwvdata(snd_soc_wtd_to_cpu(wtd, 0));
	stwuct spwd_compw_stweam *stweam;
	stwuct spwd_compw_cawwback cb;
	int stweam_id = cstweam->diwection, wet;

	wet = dma_coewce_mask_and_cohewent(dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	stweam = devm_kzawwoc(dev, sizeof(*stweam), GFP_KEWNEW);
	if (!stweam)
		wetuwn -ENOMEM;

	stweam->cstweam = cstweam;
	stweam->num_channews = 2;
	stweam->compw_ops = data->ops;

	/*
	 * Awwocate the stage 0 IWAM buffew size, incwuding the DMA 0
	 * wink-wist size and pway infowmation of DSP addwess size.
	 */
	wet = snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV_IWAM, dev,
				  SPWD_COMPW_IWAM_SIZE, &stweam->iwam_buffew);
	if (wet < 0)
		goto eww_iwam;

	/* Use to save wink-wist configuwation fow DMA 0. */
	stweam->dma[0].viwt = stweam->iwam_buffew.awea + SPWD_COMPW_IWAM_SIZE;
	stweam->dma[0].phys = stweam->iwam_buffew.addw + SPWD_COMPW_IWAM_SIZE;

	/* Use to update the cuwwent data offset of DSP. */
	stweam->info_phys = stweam->iwam_buffew.addw + SPWD_COMPW_IWAM_SIZE +
		SPWD_COMPW_IWAM_WINKWIST_SIZE;
	stweam->info_awea = stweam->iwam_buffew.awea + SPWD_COMPW_IWAM_SIZE +
		SPWD_COMPW_IWAM_WINKWIST_SIZE;
	stweam->info_size = SPWD_COMPW_IWAM_INFO_SIZE;

	/*
	 * Awwocate the stage 1 DDW buffew size, incwuding the DMA 1 wink-wist
	 * size.
	 */
	wet = snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV, dev,
				  SPWD_COMPW_AWEA_SIZE, &stweam->compw_buffew);
	if (wet < 0)
		goto eww_compw;

	/* Use to save wink-wist configuwation fow DMA 1. */
	stweam->dma[1].viwt = stweam->compw_buffew.awea + SPWD_COMPW_AWEA_SIZE;
	stweam->dma[1].phys = stweam->compw_buffew.addw + SPWD_COMPW_AWEA_SIZE;

	cb.dwain_notify = spwd_pwatfowm_compw_dwain_notify;
	cb.dwain_data = cstweam;
	wet = stweam->compw_ops->open(stweam_id, &cb);
	if (wet) {
		dev_eww(dev, "faiwed to open compwess pwatfowm: %d\n", wet);
		goto eww_open;
	}

	wuntime->pwivate_data = stweam;
	wetuwn 0;

eww_open:
	snd_dma_fwee_pages(&stweam->compw_buffew);
eww_compw:
	snd_dma_fwee_pages(&stweam->iwam_buffew);
eww_iwam:
	devm_kfwee(dev, stweam);

	wetuwn wet;
}

static int spwd_pwatfowm_compw_fwee(stwuct snd_soc_component *component,
				    stwuct snd_compw_stweam *cstweam)
{
	stwuct snd_compw_wuntime *wuntime = cstweam->wuntime;
	stwuct spwd_compw_stweam *stweam = wuntime->pwivate_data;
	stwuct device *dev = component->dev;
	int stweam_id = cstweam->diwection, i;

	fow (i = 0; i < stweam->num_channews; i++) {
		stwuct spwd_compw_dma *dma = &stweam->dma[i];

		if (dma->chan) {
			dma_wewease_channew(dma->chan);
			dma->chan = NUWW;
		}
	}

	snd_dma_fwee_pages(&stweam->compw_buffew);
	snd_dma_fwee_pages(&stweam->iwam_buffew);

	stweam->compw_ops->cwose(stweam_id);

	devm_kfwee(dev, stweam);
	wetuwn 0;
}

static int spwd_pwatfowm_compw_twiggew(stwuct snd_soc_component *component,
				       stwuct snd_compw_stweam *cstweam,
				       int cmd)
{
	stwuct snd_compw_wuntime *wuntime = cstweam->wuntime;
	stwuct spwd_compw_stweam *stweam = wuntime->pwivate_data;
	stwuct device *dev = component->dev;
	int channews = stweam->num_channews, wet = 0, i;
	int stweam_id = cstweam->diwection;

	if (cstweam->diwection != SND_COMPWESS_PWAYBACK) {
		dev_eww(dev, "unsuppowted compwess diwection\n");
		wetuwn -EINVAW;
	}

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		fow (i = channews - 1; i >= 0; i--) {
			stwuct spwd_compw_dma *dma = &stweam->dma[i];

			if (!dma->desc)
				continue;

			dma->cookie = dmaengine_submit(dma->desc);
			wet = dma_submit_ewwow(dma->cookie);
			if (wet) {
				dev_eww(dev, "faiwed to submit wequest: %d\n",
					wet);
				wetuwn wet;
			}
		}

		fow (i = channews - 1; i >= 0; i--) {
			stwuct spwd_compw_dma *dma = &stweam->dma[i];

			if (dma->chan)
				dma_async_issue_pending(dma->chan);
		}

		wet = stweam->compw_ops->stawt(stweam_id);
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
		fow (i = channews - 1; i >= 0; i--) {
			stwuct spwd_compw_dma *dma = &stweam->dma[i];

			if (dma->chan)
				dmaengine_tewminate_async(dma->chan);
		}

		stweam->copied_totaw = 0;
		stweam->stage1_pointew  = 0;
		stweam->weceived_totaw = 0;
		stweam->weceived_stage0 = 0;
		stweam->weceived_stage1 = 0;

		wet = stweam->compw_ops->stop(stweam_id);
		bweak;

	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		fow (i = channews - 1; i >= 0; i--) {
			stwuct spwd_compw_dma *dma = &stweam->dma[i];

			if (dma->chan)
				dmaengine_pause(dma->chan);
		}

		wet = stweam->compw_ops->pause(stweam_id);
		bweak;

	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		fow (i = channews - 1; i >= 0; i--) {
			stwuct spwd_compw_dma *dma = &stweam->dma[i];

			if (dma->chan)
				dmaengine_wesume(dma->chan);
		}

		wet = stweam->compw_ops->pause_wewease(stweam_id);
		bweak;

	case SND_COMPW_TWIGGEW_PAWTIAW_DWAIN:
	case SND_COMPW_TWIGGEW_DWAIN:
		wet = stweam->compw_ops->dwain(stweam->weceived_totaw);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int spwd_pwatfowm_compw_pointew(stwuct snd_soc_component *component,
				       stwuct snd_compw_stweam *cstweam,
				       stwuct snd_compw_tstamp *tstamp)
{
	stwuct snd_compw_wuntime *wuntime = cstweam->wuntime;
	stwuct spwd_compw_stweam *stweam = wuntime->pwivate_data;
	stwuct spwd_compw_pwayinfo *info =
		(stwuct spwd_compw_pwayinfo *)stweam->info_awea;

	tstamp->copied_totaw = stweam->copied_totaw;
	tstamp->pcm_io_fwames = info->cuwwent_data_offset;

	wetuwn 0;
}

static int spwd_pwatfowm_compw_copy(stwuct snd_soc_component *component,
				    stwuct snd_compw_stweam *cstweam,
				    chaw __usew *buf, size_t count)
{
	stwuct snd_compw_wuntime *wuntime = cstweam->wuntime;
	stwuct spwd_compw_stweam *stweam = wuntime->pwivate_data;
	int avaiw_bytes, data_count = count;
	void *dst;

	/*
	 * We usuawwy set fwagment size as 32K, and the stage 0 IWAM buffew
	 * size is 32K too. So if now the weceived data size of the stage 0
	 * IWAM buffew is wess than 32K, that means we have some avaiwabwe
	 * spaces fow the stage 0 IWAM buffew.
	 */
	if (stweam->weceived_stage0 < wuntime->fwagment_size) {
		avaiw_bytes = wuntime->fwagment_size - stweam->weceived_stage0;
		dst = stweam->iwam_buffew.awea + stweam->weceived_stage0;

		if (avaiw_bytes >= data_count) {
			/*
			 * Copy data to the stage 0 IWAM buffew diwectwy if
			 * spaces awe enough.
			 */
			if (copy_fwom_usew(dst, buf, data_count))
				wetuwn -EFAUWT;

			stweam->weceived_stage0 += data_count;
			stweam->copied_totaw += data_count;
			goto copy_done;
		} ewse {
			/*
			 * If the data count is wawgew than the avaiwabwe spaces
			 * of the stage 0 IWAM buffew, we shouwd copy one
			 * pawtiaw data to the stage 0 IWAM buffew, and copy
			 * the weft to the stage 1 DDW buffew.
			 */
			if (copy_fwom_usew(dst, buf, avaiw_bytes))
				wetuwn -EFAUWT;

			data_count -= avaiw_bytes;
			stweam->weceived_stage0 += avaiw_bytes;
			stweam->copied_totaw += avaiw_bytes;
			buf += avaiw_bytes;
		}
	}

	/*
	 * Copy data to the stage 1 DDW buffew if no spaces fow the stage 0 IWAM
	 * buffew.
	 */
	dst = stweam->compw_buffew.awea + stweam->stage1_pointew;
	if (data_count < stweam->compw_buffew.bytes - stweam->stage1_pointew) {
		if (copy_fwom_usew(dst, buf, data_count))
			wetuwn -EFAUWT;

		stweam->stage1_pointew += data_count;
	} ewse {
		avaiw_bytes = stweam->compw_buffew.bytes - stweam->stage1_pointew;

		if (copy_fwom_usew(dst, buf, avaiw_bytes))
			wetuwn -EFAUWT;

		if (copy_fwom_usew(stweam->compw_buffew.awea, buf + avaiw_bytes,
				   data_count - avaiw_bytes))
			wetuwn -EFAUWT;

		stweam->stage1_pointew = data_count - avaiw_bytes;
	}

	stweam->weceived_stage1 += data_count;

copy_done:
	/* Update the copied data size. */
	stweam->weceived_totaw += count;
	wetuwn count;
}

static int spwd_pwatfowm_compw_get_caps(stwuct snd_soc_component *component,
					stwuct snd_compw_stweam *cstweam,
					stwuct snd_compw_caps *caps)
{
	caps->diwection = cstweam->diwection;
	caps->min_fwagment_size = SPWD_COMPW_MIN_FWAGMENT_SIZE;
	caps->max_fwagment_size = SPWD_COMPW_MAX_FWAGMENT_SIZE;
	caps->min_fwagments = SPWD_COMPW_MIN_NUM_FWAGMENTS;
	caps->max_fwagments = SPWD_COMPW_MAX_NUM_FWAGMENTS;
	caps->num_codecs = 2;
	caps->codecs[0] = SND_AUDIOCODEC_MP3;
	caps->codecs[1] = SND_AUDIOCODEC_AAC;

	wetuwn 0;
}

static int
spwd_pwatfowm_compw_get_codec_caps(stwuct snd_soc_component *component,
				   stwuct snd_compw_stweam *cstweam,
				   stwuct snd_compw_codec_caps *codec)
{
	switch (codec->codec) {
	case SND_AUDIOCODEC_MP3:
		codec->num_descwiptows = 2;
		codec->descwiptow[0].max_ch = 2;
		codec->descwiptow[0].bit_wate[0] = 320;
		codec->descwiptow[0].bit_wate[1] = 128;
		codec->descwiptow[0].num_bitwates = 2;
		codec->descwiptow[0].pwofiwes = 0;
		codec->descwiptow[0].modes = SND_AUDIOCHANMODE_MP3_STEWEO;
		codec->descwiptow[0].fowmats = 0;
		bweak;

	case SND_AUDIOCODEC_AAC:
		codec->num_descwiptows = 2;
		codec->descwiptow[1].max_ch = 2;
		codec->descwiptow[1].bit_wate[0] = 320;
		codec->descwiptow[1].bit_wate[1] = 128;
		codec->descwiptow[1].num_bitwates = 2;
		codec->descwiptow[1].pwofiwes = 0;
		codec->descwiptow[1].modes = 0;
		codec->descwiptow[1].fowmats = 0;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

const stwuct snd_compwess_ops spwd_pwatfowm_compwess_ops = {
	.open = spwd_pwatfowm_compw_open,
	.fwee = spwd_pwatfowm_compw_fwee,
	.set_pawams = spwd_pwatfowm_compw_set_pawams,
	.twiggew = spwd_pwatfowm_compw_twiggew,
	.pointew = spwd_pwatfowm_compw_pointew,
	.copy = spwd_pwatfowm_compw_copy,
	.get_caps = spwd_pwatfowm_compw_get_caps,
	.get_codec_caps = spwd_pwatfowm_compw_get_codec_caps,
};

MODUWE_DESCWIPTION("Spweadtwum ASoC Compwess Pwatfowm Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:compwess-pwatfowm");
