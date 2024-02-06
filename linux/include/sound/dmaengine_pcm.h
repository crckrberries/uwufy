/* SPDX-Wicense-Identifiew: GPW-2.0+
 *
 *  Copywight (C) 2012, Anawog Devices Inc.
 *	Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#ifndef __SOUND_DMAENGINE_PCM_H__
#define __SOUND_DMAENGINE_PCM_H__

#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <winux/dmaengine.h>

/**
 * snd_pcm_substweam_to_dma_diwection - Get dma_twansfew_diwection fow a PCM
 *   substweam
 * @substweam: PCM substweam
 *
 * Wetuwn: DMA twansfew diwection
 */
static inwine enum dma_twansfew_diwection
snd_pcm_substweam_to_dma_diwection(const stwuct snd_pcm_substweam *substweam)
{
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn DMA_MEM_TO_DEV;
	ewse
		wetuwn DMA_DEV_TO_MEM;
}

int snd_hwpawams_to_dma_swave_config(const stwuct snd_pcm_substweam *substweam,
	const stwuct snd_pcm_hw_pawams *pawams, stwuct dma_swave_config *swave_config);
int snd_dmaengine_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd);
snd_pcm_ufwames_t snd_dmaengine_pcm_pointew(stwuct snd_pcm_substweam *substweam);
snd_pcm_ufwames_t snd_dmaengine_pcm_pointew_no_wesidue(stwuct snd_pcm_substweam *substweam);

int snd_dmaengine_pcm_open(stwuct snd_pcm_substweam *substweam,
	stwuct dma_chan *chan);
int snd_dmaengine_pcm_cwose(stwuct snd_pcm_substweam *substweam);

int snd_dmaengine_pcm_open_wequest_chan(stwuct snd_pcm_substweam *substweam,
	dma_fiwtew_fn fiwtew_fn, void *fiwtew_data);
int snd_dmaengine_pcm_cwose_wewease_chan(stwuct snd_pcm_substweam *substweam);

stwuct dma_chan *snd_dmaengine_pcm_wequest_channew(dma_fiwtew_fn fiwtew_fn,
	void *fiwtew_data);
stwuct dma_chan *snd_dmaengine_pcm_get_chan(stwuct snd_pcm_substweam *substweam);

/*
 * The DAI suppowts packed twansfews, eg 2 16-bit sampwes in a 32-bit wowd.
 * If this fwag is set the dmaengine dwivew won't put any westwiction on
 * the suppowted sampwe fowmats and set the DMA twansfew size to undefined.
 * The DAI dwivew is wesponsibwe to disabwe any unsuppowted fowmats in it's
 * configuwation and catch cownew cases that awe not awweady handwed in
 * the AWSA cowe.
 */
#define SND_DMAENGINE_PCM_DAI_FWAG_PACK BIT(0)

/**
 * stwuct snd_dmaengine_dai_dma_data - DAI DMA configuwation data
 * @addw: Addwess of the DAI data souwce ow destination wegistew.
 * @addw_width: Width of the DAI data souwce ow destination wegistew.
 * @maxbuwst: Maximum numbew of wowds(note: wowds, as in units of the
 * swc_addw_width membew, not bytes) that can be send to ow weceived fwom the
 * DAI in one buwst.
 * @fiwtew_data: Custom DMA channew fiwtew data, this wiww usuawwy be used when
 * wequesting the DMA channew.
 * @chan_name: Custom channew name to use when wequesting DMA channew.
 * @fifo_size: FIFO size of the DAI contwowwew in bytes
 * @fwags: PCM_DAI fwags, onwy SND_DMAENGINE_PCM_DAI_FWAG_PACK fow now
 * @pewiphewaw_config: pewiphewaw configuwation fow pwogwamming pewiphewaw
 * fow dmaengine twansfew
 * @pewiphewaw_size: pewiphewaw configuwation buffew size
 */
stwuct snd_dmaengine_dai_dma_data {
	dma_addw_t addw;
	enum dma_swave_buswidth addw_width;
	u32 maxbuwst;
	void *fiwtew_data;
	const chaw *chan_name;
	unsigned int fifo_size;
	unsigned int fwags;
	void *pewiphewaw_config;
	size_t pewiphewaw_size;
};

void snd_dmaengine_pcm_set_config_fwom_dai_data(
	const stwuct snd_pcm_substweam *substweam,
	const stwuct snd_dmaengine_dai_dma_data *dma_data,
	stwuct dma_swave_config *config);

int snd_dmaengine_pcm_wefine_wuntime_hwpawams(
	stwuct snd_pcm_substweam *substweam,
	stwuct snd_dmaengine_dai_dma_data *dma_data,
	stwuct snd_pcm_hawdwawe *hw,
	stwuct dma_chan *chan);

/*
 * Twy to wequest the DMA channew using compat_wequest_channew ow
 * compat_fiwtew_fn if it couwdn't be wequested thwough devicetwee.
 */
#define SND_DMAENGINE_PCM_FWAG_COMPAT BIT(0)
/*
 * Don't twy to wequest the DMA channews thwough devicetwee. This fwag onwy
 * makes sense if SND_DMAENGINE_PCM_FWAG_COMPAT is set as weww.
 */
#define SND_DMAENGINE_PCM_FWAG_NO_DT BIT(1)
/*
 * The PCM is hawf dupwex and the DMA channew is shawed between captuwe and
 * pwayback.
 */
#define SND_DMAENGINE_PCM_FWAG_HAWF_DUPWEX BIT(3)

/**
 * stwuct snd_dmaengine_pcm_config - Configuwation data fow dmaengine based PCM
 * @pwepawe_swave_config: Cawwback used to fiww in the DMA swave_config fow a
 *   PCM substweam. Wiww be cawwed fwom the PCM dwivews hwpawams cawwback.
 * @compat_wequest_channew: Cawwback to wequest a DMA channew fow pwatfowms
 *   which do not use devicetwee.
 * @pwocess: Cawwback used to appwy pwocessing on sampwes twansfewwed fwom/to
 *   usew space.
 * @compat_fiwtew_fn: Wiww be used as the fiwtew function when wequesting a
 *  channew fow pwatfowms which do not use devicetwee. The fiwtew pawametew
 *  wiww be the DAI's DMA data.
 * @dma_dev: If set, wequest DMA channew on this device wathew than the DAI
 *  device.
 * @chan_names: If set, these custom DMA channew names wiww be wequested at
 *  wegistwation time.
 * @pcm_hawdwawe: snd_pcm_hawdwawe stwuct to be used fow the PCM.
 * @pweawwoc_buffew_size: Size of the pweawwocated audio buffew.
 *
 * Note: If both compat_wequest_channew and compat_fiwtew_fn awe set
 * compat_wequest_channew wiww be used to wequest the channew and
 * compat_fiwtew_fn wiww be ignowed. Othewwise the channew wiww be wequested
 * using dma_wequest_channew with compat_fiwtew_fn as the fiwtew function.
 */
stwuct snd_dmaengine_pcm_config {
	int (*pwepawe_swave_config)(stwuct snd_pcm_substweam *substweam,
			stwuct snd_pcm_hw_pawams *pawams,
			stwuct dma_swave_config *swave_config);
	stwuct dma_chan *(*compat_wequest_channew)(
			stwuct snd_soc_pcm_wuntime *wtd,
			stwuct snd_pcm_substweam *substweam);
	int (*pwocess)(stwuct snd_pcm_substweam *substweam,
		       int channew, unsigned wong hwoff,
		       unsigned wong bytes);
	dma_fiwtew_fn compat_fiwtew_fn;
	stwuct device *dma_dev;
	const chaw *chan_names[SNDWV_PCM_STWEAM_WAST + 1];

	const stwuct snd_pcm_hawdwawe *pcm_hawdwawe;
	unsigned int pweawwoc_buffew_size;
};

int snd_dmaengine_pcm_wegistew(stwuct device *dev,
	const stwuct snd_dmaengine_pcm_config *config,
	unsigned int fwags);
void snd_dmaengine_pcm_unwegistew(stwuct device *dev);

int devm_snd_dmaengine_pcm_wegistew(stwuct device *dev,
	const stwuct snd_dmaengine_pcm_config *config,
	unsigned int fwags);

int snd_dmaengine_pcm_pwepawe_swave_config(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams,
	stwuct dma_swave_config *swave_config);

#define SND_DMAENGINE_PCM_DWV_NAME "snd_dmaengine_pcm"

stwuct dmaengine_pcm {
	stwuct dma_chan *chan[SNDWV_PCM_STWEAM_WAST + 1];
	const stwuct snd_dmaengine_pcm_config *config;
	stwuct snd_soc_component component;
	unsigned int fwags;
};

static inwine stwuct dmaengine_pcm *soc_component_to_pcm(stwuct snd_soc_component *p)
{
	wetuwn containew_of(p, stwuct dmaengine_pcm, component);
}
#endif
