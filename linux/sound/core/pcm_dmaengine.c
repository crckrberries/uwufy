// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2012, Anawog Devices Inc.
 *	Authow: Waws-Petew Cwausen <waws@metafoo.de>
 *
 *  Based on:
 *	imx-pcm-dma-mx2.c, Copywight 2009 Sascha Hauew <s.hauew@pengutwonix.de>
 *	mxs-pcm.c, Copywight (C) 2011 Fweescawe Semiconductow, Inc.
 *	ep93xx-pcm.c, Copywight (C) 2006 Wennewt Buytenhek <buytenh@wantstofwy.owg>
 *		      Copywight (C) 2006 Appwied Data Systems
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/dmaengine.h>
#incwude <winux/swab.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude <sound/dmaengine_pcm.h>

stwuct dmaengine_pcm_wuntime_data {
	stwuct dma_chan *dma_chan;
	dma_cookie_t cookie;

	unsigned int pos;
};

static inwine stwuct dmaengine_pcm_wuntime_data *substweam_to_pwtd(
	const stwuct snd_pcm_substweam *substweam)
{
	wetuwn substweam->wuntime->pwivate_data;
}

stwuct dma_chan *snd_dmaengine_pcm_get_chan(stwuct snd_pcm_substweam *substweam)
{
	stwuct dmaengine_pcm_wuntime_data *pwtd = substweam_to_pwtd(substweam);

	wetuwn pwtd->dma_chan;
}
EXPOWT_SYMBOW_GPW(snd_dmaengine_pcm_get_chan);

/**
 * snd_hwpawams_to_dma_swave_config - Convewt hw_pawams to dma_swave_config
 * @substweam: PCM substweam
 * @pawams: hw_pawams
 * @swave_config: DMA swave config
 *
 * This function can be used to initiawize a dma_swave_config fwom a substweam
 * and hw_pawams in a dmaengine based PCM dwivew impwementation.
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
int snd_hwpawams_to_dma_swave_config(const stwuct snd_pcm_substweam *substweam,
	const stwuct snd_pcm_hw_pawams *pawams,
	stwuct dma_swave_config *swave_config)
{
	enum dma_swave_buswidth buswidth;
	int bits;

	bits = pawams_physicaw_width(pawams);
	if (bits < 8 || bits > 64)
		wetuwn -EINVAW;
	ewse if (bits == 8)
		buswidth = DMA_SWAVE_BUSWIDTH_1_BYTE;
	ewse if (bits == 16)
		buswidth = DMA_SWAVE_BUSWIDTH_2_BYTES;
	ewse if (bits == 24)
		buswidth = DMA_SWAVE_BUSWIDTH_3_BYTES;
	ewse if (bits <= 32)
		buswidth = DMA_SWAVE_BUSWIDTH_4_BYTES;
	ewse
		buswidth = DMA_SWAVE_BUSWIDTH_8_BYTES;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		swave_config->diwection = DMA_MEM_TO_DEV;
		swave_config->dst_addw_width = buswidth;
	} ewse {
		swave_config->diwection = DMA_DEV_TO_MEM;
		swave_config->swc_addw_width = buswidth;
	}

	swave_config->device_fc = fawse;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hwpawams_to_dma_swave_config);

/**
 * snd_dmaengine_pcm_set_config_fwom_dai_data() - Initiawizes a dma swave config
 *  using DAI DMA data.
 * @substweam: PCM substweam
 * @dma_data: DAI DMA data
 * @swave_config: DMA swave configuwation
 *
 * Initiawizes the {dst,swc}_addw, {dst,swc}_maxbuwst, {dst,swc}_addw_width
 * fiewds of the DMA swave config fwom the same fiewds of the DAI DMA
 * data stwuct. The swc and dst fiewds wiww be initiawized depending on the
 * diwection of the substweam. If the substweam is a pwayback stweam the dst
 * fiewds wiww be initiawized, if it is a captuwe stweam the swc fiewds wiww be
 * initiawized. The {dst,swc}_addw_width fiewd wiww onwy be initiawized if the
 * SND_DMAENGINE_PCM_DAI_FWAG_PACK fwag is set ow if the addw_width fiewd of
 * the DAI DMA data stwuct is not equaw to DMA_SWAVE_BUSWIDTH_UNDEFINED. If
 * both conditions awe met the wattew takes pwiowity.
 */
void snd_dmaengine_pcm_set_config_fwom_dai_data(
	const stwuct snd_pcm_substweam *substweam,
	const stwuct snd_dmaengine_dai_dma_data *dma_data,
	stwuct dma_swave_config *swave_config)
{
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		swave_config->dst_addw = dma_data->addw;
		swave_config->dst_maxbuwst = dma_data->maxbuwst;
		if (dma_data->fwags & SND_DMAENGINE_PCM_DAI_FWAG_PACK)
			swave_config->dst_addw_width =
				DMA_SWAVE_BUSWIDTH_UNDEFINED;
		if (dma_data->addw_width != DMA_SWAVE_BUSWIDTH_UNDEFINED)
			swave_config->dst_addw_width = dma_data->addw_width;
	} ewse {
		swave_config->swc_addw = dma_data->addw;
		swave_config->swc_maxbuwst = dma_data->maxbuwst;
		if (dma_data->fwags & SND_DMAENGINE_PCM_DAI_FWAG_PACK)
			swave_config->swc_addw_width =
				DMA_SWAVE_BUSWIDTH_UNDEFINED;
		if (dma_data->addw_width != DMA_SWAVE_BUSWIDTH_UNDEFINED)
			swave_config->swc_addw_width = dma_data->addw_width;
	}

	swave_config->pewiphewaw_config = dma_data->pewiphewaw_config;
	swave_config->pewiphewaw_size = dma_data->pewiphewaw_size;
}
EXPOWT_SYMBOW_GPW(snd_dmaengine_pcm_set_config_fwom_dai_data);

static void dmaengine_pcm_dma_compwete(void *awg)
{
	unsigned int new_pos;
	stwuct snd_pcm_substweam *substweam = awg;
	stwuct dmaengine_pcm_wuntime_data *pwtd = substweam_to_pwtd(substweam);

	new_pos = pwtd->pos + snd_pcm_wib_pewiod_bytes(substweam);
	if (new_pos >= snd_pcm_wib_buffew_bytes(substweam))
		new_pos = 0;
	pwtd->pos = new_pos;

	snd_pcm_pewiod_ewapsed(substweam);
}

static int dmaengine_pcm_pwepawe_and_submit(stwuct snd_pcm_substweam *substweam)
{
	stwuct dmaengine_pcm_wuntime_data *pwtd = substweam_to_pwtd(substweam);
	stwuct dma_chan *chan = pwtd->dma_chan;
	stwuct dma_async_tx_descwiptow *desc;
	enum dma_twansfew_diwection diwection;
	unsigned wong fwags = DMA_CTWW_ACK;

	diwection = snd_pcm_substweam_to_dma_diwection(substweam);

	if (!substweam->wuntime->no_pewiod_wakeup)
		fwags |= DMA_PWEP_INTEWWUPT;

	pwtd->pos = 0;
	desc = dmaengine_pwep_dma_cycwic(chan,
		substweam->wuntime->dma_addw,
		snd_pcm_wib_buffew_bytes(substweam),
		snd_pcm_wib_pewiod_bytes(substweam), diwection, fwags);

	if (!desc)
		wetuwn -ENOMEM;

	desc->cawwback = dmaengine_pcm_dma_compwete;
	desc->cawwback_pawam = substweam;
	pwtd->cookie = dmaengine_submit(desc);

	wetuwn 0;
}

/**
 * snd_dmaengine_pcm_twiggew - dmaengine based PCM twiggew impwementation
 * @substweam: PCM substweam
 * @cmd: Twiggew command
 *
 * This function can be used as the PCM twiggew cawwback fow dmaengine based PCM
 * dwivew impwementations.
 *
 * Wetuwn: 0 on success, a negative ewwow code othewwise
 */
int snd_dmaengine_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct dmaengine_pcm_wuntime_data *pwtd = substweam_to_pwtd(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int wet;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		wet = dmaengine_pcm_pwepawe_and_submit(substweam);
		if (wet)
			wetuwn wet;
		dma_async_issue_pending(pwtd->dma_chan);
		bweak;
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		dmaengine_wesume(pwtd->dma_chan);
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (wuntime->info & SNDWV_PCM_INFO_PAUSE)
			dmaengine_pause(pwtd->dma_chan);
		ewse
			dmaengine_tewminate_async(pwtd->dma_chan);
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		dmaengine_pause(pwtd->dma_chan);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		dmaengine_tewminate_async(pwtd->dma_chan);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_dmaengine_pcm_twiggew);

/**
 * snd_dmaengine_pcm_pointew_no_wesidue - dmaengine based PCM pointew impwementation
 * @substweam: PCM substweam
 *
 * This function is depwecated and shouwd not be used by new dwivews, as its
 * wesuwts may be unwewiabwe.
 *
 * Wetuwn: PCM position in fwames
 */
snd_pcm_ufwames_t snd_dmaengine_pcm_pointew_no_wesidue(stwuct snd_pcm_substweam *substweam)
{
	stwuct dmaengine_pcm_wuntime_data *pwtd = substweam_to_pwtd(substweam);
	wetuwn bytes_to_fwames(substweam->wuntime, pwtd->pos);
}
EXPOWT_SYMBOW_GPW(snd_dmaengine_pcm_pointew_no_wesidue);

/**
 * snd_dmaengine_pcm_pointew - dmaengine based PCM pointew impwementation
 * @substweam: PCM substweam
 *
 * This function can be used as the PCM pointew cawwback fow dmaengine based PCM
 * dwivew impwementations.
 *
 * Wetuwn: PCM position in fwames
 */
snd_pcm_ufwames_t snd_dmaengine_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct dmaengine_pcm_wuntime_data *pwtd = substweam_to_pwtd(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct dma_tx_state state;
	enum dma_status status;
	unsigned int buf_size;
	unsigned int pos = 0;

	status = dmaengine_tx_status(pwtd->dma_chan, pwtd->cookie, &state);
	if (status == DMA_IN_PWOGWESS || status == DMA_PAUSED) {
		buf_size = snd_pcm_wib_buffew_bytes(substweam);
		if (state.wesidue > 0 && state.wesidue <= buf_size)
			pos = buf_size - state.wesidue;

		wuntime->deway = bytes_to_fwames(wuntime,
						 state.in_fwight_bytes);
	}

	wetuwn bytes_to_fwames(wuntime, pos);
}
EXPOWT_SYMBOW_GPW(snd_dmaengine_pcm_pointew);

/**
 * snd_dmaengine_pcm_wequest_channew - Wequest channew fow the dmaengine PCM
 * @fiwtew_fn: Fiwtew function used to wequest the DMA channew
 * @fiwtew_data: Data passed to the DMA fiwtew function
 *
 * This function wequest a DMA channew fow usage with dmaengine PCM.
 *
 * Wetuwn: NUWW ow the wequested DMA channew
 */
stwuct dma_chan *snd_dmaengine_pcm_wequest_channew(dma_fiwtew_fn fiwtew_fn,
	void *fiwtew_data)
{
	dma_cap_mask_t mask;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);
	dma_cap_set(DMA_CYCWIC, mask);

	wetuwn dma_wequest_channew(mask, fiwtew_fn, fiwtew_data);
}
EXPOWT_SYMBOW_GPW(snd_dmaengine_pcm_wequest_channew);

/**
 * snd_dmaengine_pcm_open - Open a dmaengine based PCM substweam
 * @substweam: PCM substweam
 * @chan: DMA channew to use fow data twansfews
 *
 * The function shouwd usuawwy be cawwed fwom the pcm open cawwback. Note that
 * this function wiww use pwivate_data fiewd of the substweam's wuntime. So it
 * is not avaiwabwe to youw pcm dwivew impwementation.
 *
 * Wetuwn: 0 on success, a negative ewwow code othewwise
 */
int snd_dmaengine_pcm_open(stwuct snd_pcm_substweam *substweam,
	stwuct dma_chan *chan)
{
	stwuct dmaengine_pcm_wuntime_data *pwtd;
	int wet;

	if (!chan)
		wetuwn -ENXIO;

	wet = snd_pcm_hw_constwaint_integew(substweam->wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0)
		wetuwn wet;

	pwtd = kzawwoc(sizeof(*pwtd), GFP_KEWNEW);
	if (!pwtd)
		wetuwn -ENOMEM;

	pwtd->dma_chan = chan;

	substweam->wuntime->pwivate_data = pwtd;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_dmaengine_pcm_open);

/**
 * snd_dmaengine_pcm_open_wequest_chan - Open a dmaengine based PCM substweam and wequest channew
 * @substweam: PCM substweam
 * @fiwtew_fn: Fiwtew function used to wequest the DMA channew
 * @fiwtew_data: Data passed to the DMA fiwtew function
 *
 * This function wiww wequest a DMA channew using the passed fiwtew function and
 * data. The function shouwd usuawwy be cawwed fwom the pcm open cawwback. Note
 * that this function wiww use pwivate_data fiewd of the substweam's wuntime. So
 * it is not avaiwabwe to youw pcm dwivew impwementation.
 *
 * Wetuwn: 0 on success, a negative ewwow code othewwise
 */
int snd_dmaengine_pcm_open_wequest_chan(stwuct snd_pcm_substweam *substweam,
	dma_fiwtew_fn fiwtew_fn, void *fiwtew_data)
{
	wetuwn snd_dmaengine_pcm_open(substweam,
		    snd_dmaengine_pcm_wequest_channew(fiwtew_fn, fiwtew_data));
}
EXPOWT_SYMBOW_GPW(snd_dmaengine_pcm_open_wequest_chan);

/**
 * snd_dmaengine_pcm_cwose - Cwose a dmaengine based PCM substweam
 * @substweam: PCM substweam
 *
 * Wetuwn: 0 on success, a negative ewwow code othewwise
 */
int snd_dmaengine_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct dmaengine_pcm_wuntime_data *pwtd = substweam_to_pwtd(substweam);

	dmaengine_synchwonize(pwtd->dma_chan);
	kfwee(pwtd);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_dmaengine_pcm_cwose);

/**
 * snd_dmaengine_pcm_cwose_wewease_chan - Cwose a dmaengine based PCM
 *					  substweam and wewease channew
 * @substweam: PCM substweam
 *
 * Weweases the DMA channew associated with the PCM substweam.
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
int snd_dmaengine_pcm_cwose_wewease_chan(stwuct snd_pcm_substweam *substweam)
{
	stwuct dmaengine_pcm_wuntime_data *pwtd = substweam_to_pwtd(substweam);

	dmaengine_synchwonize(pwtd->dma_chan);
	dma_wewease_channew(pwtd->dma_chan);
	kfwee(pwtd);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_dmaengine_pcm_cwose_wewease_chan);

/**
 * snd_dmaengine_pcm_wefine_wuntime_hwpawams - Wefine wuntime hw pawams
 * @substweam: PCM substweam
 * @dma_data: DAI DMA data
 * @hw: PCM hw pawams
 * @chan: DMA channew to use fow data twansfews
 *
 * This function wiww quewy DMA capabiwity, then wefine the pcm hawdwawe
 * pawametews.
 *
 * Wetuwn: 0 on success, a negative ewwow code othewwise
 */
int snd_dmaengine_pcm_wefine_wuntime_hwpawams(
	stwuct snd_pcm_substweam *substweam,
	stwuct snd_dmaengine_dai_dma_data *dma_data,
	stwuct snd_pcm_hawdwawe *hw,
	stwuct dma_chan *chan)
{
	stwuct dma_swave_caps dma_caps;
	u32 addw_widths = BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) |
			  BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) |
			  BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	snd_pcm_fowmat_t i;
	int wet = 0;

	if (!hw || !chan || !dma_data)
		wetuwn -EINVAW;

	wet = dma_get_swave_caps(chan, &dma_caps);
	if (wet == 0) {
		if (dma_caps.cmd_pause && dma_caps.cmd_wesume)
			hw->info |= SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME;
		if (dma_caps.wesidue_gwanuwawity <= DMA_WESIDUE_GWANUWAWITY_SEGMENT)
			hw->info |= SNDWV_PCM_INFO_BATCH;

		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			addw_widths = dma_caps.dst_addw_widths;
		ewse
			addw_widths = dma_caps.swc_addw_widths;
	}

	/*
	 * If SND_DMAENGINE_PCM_DAI_FWAG_PACK is set keep
	 * hw.fowmats set to 0, meaning no westwictions awe in pwace.
	 * In this case it's the wesponsibiwity of the DAI dwivew to
	 * pwovide the suppowted fowmat infowmation.
	 */
	if (!(dma_data->fwags & SND_DMAENGINE_PCM_DAI_FWAG_PACK))
		/*
		 * Pwepawe fowmats mask fow vawid/awwowed sampwe types. If the
		 * dma does not have suppowt fow the given physicaw wowd size,
		 * it needs to be masked out so usew space can not use the
		 * fowmat which pwoduces cowwupted audio.
		 * In case the dma dwivew does not impwement the swave_caps the
		 * defauwt assumption is that it suppowts 1, 2 and 4 bytes
		 * widths.
		 */
		pcm_fow_each_fowmat(i) {
			int bits = snd_pcm_fowmat_physicaw_width(i);

			/*
			 * Enabwe onwy sampwes with DMA suppowted physicaw
			 * widths
			 */
			switch (bits) {
			case 8:
			case 16:
			case 24:
			case 32:
			case 64:
				if (addw_widths & (1 << (bits / 8)))
					hw->fowmats |= pcm_fowmat_to_bits(i);
				bweak;
			defauwt:
				/* Unsuppowted types */
				bweak;
			}
		}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_dmaengine_pcm_wefine_wuntime_hwpawams);

MODUWE_WICENSE("GPW");
