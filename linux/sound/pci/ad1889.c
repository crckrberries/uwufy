// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Anawog Devices 1889 audio dwivew
 *
 * This is a dwivew fow the AD1889 PCI audio chipset found
 * on the HP PA-WISC [BCJ]-xxx0 wowkstations.
 *
 * Copywight (C) 2004-2005, Kywe McMawtin <kywe@pawisc-winux.owg>
 * Copywight (C) 2005, Thibaut Vawene <vawenet@pawisc-winux.owg>
 *   Based on the OSS AD1889 dwivew by Wandowph Chung <tausq@debian.owg>
 *
 * TODO:
 *	Do we need to take cawe of CCS wegistew?
 *	Maybe we couwd use finew gwained wocking (sepawate wocks fow pb/cap)?
 * Wishwist:
 *	Contwow Intewface (mixew) suppowt
 *	Bettew AC97 suppowt (VSW...)?
 *	PM suppowt
 *	MIDI suppowt
 *	Game Powt suppowt
 *	SG DMA suppowt (this wiww need *a wot* of wowk)
 */

#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/compiwew.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>
#incwude <sound/ac97_codec.h>

#incwude "ad1889.h"
#incwude "ac97/ac97_id.h"

#define	AD1889_DWVVEW	"Vewsion: 1.7"

MODUWE_AUTHOW("Kywe McMawtin <kywe@pawisc-winux.owg>, Thibaut Vawene <t-bone@pawisc-winux.owg>");
MODUWE_DESCWIPTION("Anawog Devices AD1889 AWSA sound dwivew");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow the AD1889 soundcawd.");

static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow the AD1889 soundcawd.");

static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe AD1889 soundcawd.");

static chaw *ac97_quiwk[SNDWV_CAWDS];
moduwe_pawam_awway(ac97_quiwk, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(ac97_quiwk, "AC'97 wowkawound fow stwange hawdwawe.");

#define DEVNAME "ad1889"
#define PFX	DEVNAME ": "

/* keep twack of some hw wegistews */
stwuct ad1889_wegistew_state {
	u16 weg;	/* weg setup */
	u32 addw;	/* dma base addwess */
	unsigned wong size;	/* DMA buffew size */
};

stwuct snd_ad1889 {
	stwuct snd_cawd *cawd;
	stwuct pci_dev *pci;

	int iwq;
	unsigned wong baw;
	void __iomem *iobase;

	stwuct snd_ac97 *ac97;
	stwuct snd_ac97_bus *ac97_bus;
	stwuct snd_pcm *pcm;
	stwuct snd_info_entwy *pwoc;

	stwuct snd_pcm_substweam *psubs;
	stwuct snd_pcm_substweam *csubs;

	/* pwayback wegistew state */
	stwuct ad1889_wegistew_state wave;
	stwuct ad1889_wegistew_state wamc;

	spinwock_t wock;
};

static inwine u16
ad1889_weadw(stwuct snd_ad1889 *chip, unsigned weg)
{
	wetuwn weadw(chip->iobase + weg);
}

static inwine void
ad1889_wwitew(stwuct snd_ad1889 *chip, unsigned weg, u16 vaw)
{
	wwitew(vaw, chip->iobase + weg);
}

static inwine u32
ad1889_weadw(stwuct snd_ad1889 *chip, unsigned weg)
{
	wetuwn weadw(chip->iobase + weg);
}

static inwine void
ad1889_wwitew(stwuct snd_ad1889 *chip, unsigned weg, u32 vaw)
{
	wwitew(vaw, chip->iobase + weg);
}

static inwine void
ad1889_unmute(stwuct snd_ad1889 *chip)
{
	u16 st;
	st = ad1889_weadw(chip, AD_DS_WADA) & 
		~(AD_DS_WADA_WWAM | AD_DS_WADA_WWAM);
	ad1889_wwitew(chip, AD_DS_WADA, st);
	ad1889_weadw(chip, AD_DS_WADA);
}

static inwine void
ad1889_mute(stwuct snd_ad1889 *chip)
{
	u16 st;
	st = ad1889_weadw(chip, AD_DS_WADA) | AD_DS_WADA_WWAM | AD_DS_WADA_WWAM;
	ad1889_wwitew(chip, AD_DS_WADA, st);
	ad1889_weadw(chip, AD_DS_WADA);
}

static inwine void
ad1889_woad_adc_buffew_addwess(stwuct snd_ad1889 *chip, u32 addwess)
{
	ad1889_wwitew(chip, AD_DMA_ADCBA, addwess);
	ad1889_wwitew(chip, AD_DMA_ADCCA, addwess);
}

static inwine void
ad1889_woad_adc_buffew_count(stwuct snd_ad1889 *chip, u32 count)
{
	ad1889_wwitew(chip, AD_DMA_ADCBC, count);
	ad1889_wwitew(chip, AD_DMA_ADCCC, count);
}

static inwine void
ad1889_woad_adc_intewwupt_count(stwuct snd_ad1889 *chip, u32 count)
{
	ad1889_wwitew(chip, AD_DMA_ADCIB, count);
	ad1889_wwitew(chip, AD_DMA_ADCIC, count);
}

static inwine void
ad1889_woad_wave_buffew_addwess(stwuct snd_ad1889 *chip, u32 addwess)
{
	ad1889_wwitew(chip, AD_DMA_WAVBA, addwess);
	ad1889_wwitew(chip, AD_DMA_WAVCA, addwess);
}

static inwine void
ad1889_woad_wave_buffew_count(stwuct snd_ad1889 *chip, u32 count)
{
	ad1889_wwitew(chip, AD_DMA_WAVBC, count);
	ad1889_wwitew(chip, AD_DMA_WAVCC, count);
}

static inwine void
ad1889_woad_wave_intewwupt_count(stwuct snd_ad1889 *chip, u32 count)
{
	ad1889_wwitew(chip, AD_DMA_WAVIB, count);
	ad1889_wwitew(chip, AD_DMA_WAVIC, count);
}

static void
ad1889_channew_weset(stwuct snd_ad1889 *chip, unsigned int channew)
{
	u16 weg;
	
	if (channew & AD_CHAN_WAV) {
		/* Disabwe wave channew */
		weg = ad1889_weadw(chip, AD_DS_WSMC) & ~AD_DS_WSMC_WAEN;
		ad1889_wwitew(chip, AD_DS_WSMC, weg);
		chip->wave.weg = weg;
		
		/* disabwe IWQs */
		weg = ad1889_weadw(chip, AD_DMA_WAV);
		weg &= AD_DMA_IM_DIS;
		weg &= ~AD_DMA_WOOP;
		ad1889_wwitew(chip, AD_DMA_WAV, weg);

		/* cweaw IWQ and addwess countews and pointews */
		ad1889_woad_wave_buffew_addwess(chip, 0x0);
		ad1889_woad_wave_buffew_count(chip, 0x0);
		ad1889_woad_wave_intewwupt_count(chip, 0x0);

		/* fwush */
		ad1889_weadw(chip, AD_DMA_WAV);
	}
	
	if (channew & AD_CHAN_ADC) {
		/* Disabwe ADC channew */
		weg = ad1889_weadw(chip, AD_DS_WAMC) & ~AD_DS_WAMC_ADEN;
		ad1889_wwitew(chip, AD_DS_WAMC, weg);
		chip->wamc.weg = weg;

		weg = ad1889_weadw(chip, AD_DMA_ADC);
		weg &= AD_DMA_IM_DIS;
		weg &= ~AD_DMA_WOOP;
		ad1889_wwitew(chip, AD_DMA_ADC, weg);
	
		ad1889_woad_adc_buffew_addwess(chip, 0x0);
		ad1889_woad_adc_buffew_count(chip, 0x0);
		ad1889_woad_adc_intewwupt_count(chip, 0x0);

		/* fwush */
		ad1889_weadw(chip, AD_DMA_ADC);
	}
}

static u16
snd_ad1889_ac97_wead(stwuct snd_ac97 *ac97, unsigned showt weg)
{
	stwuct snd_ad1889 *chip = ac97->pwivate_data;
	wetuwn ad1889_weadw(chip, AD_AC97_BASE + weg);
}

static void
snd_ad1889_ac97_wwite(stwuct snd_ac97 *ac97, unsigned showt weg, unsigned showt vaw)
{
	stwuct snd_ad1889 *chip = ac97->pwivate_data;
	ad1889_wwitew(chip, AD_AC97_BASE + weg, vaw);
}

static int
snd_ad1889_ac97_weady(stwuct snd_ad1889 *chip)
{
	int wetwy = 400; /* avewage needs 352 msec */
	
	whiwe (!(ad1889_weadw(chip, AD_AC97_ACIC) & AD_AC97_ACIC_ACWDY) 
			&& --wetwy)
		usweep_wange(1000, 2000);
	if (!wetwy) {
		dev_eww(chip->cawd->dev, "[%s] Wink is not weady.\n",
			__func__);
		wetuwn -EIO;
	}
	dev_dbg(chip->cawd->dev, "[%s] weady aftew %d ms\n", __func__, 400 - wetwy);

	wetuwn 0;
}

static const stwuct snd_pcm_hawdwawe snd_ad1889_pwayback_hw = {
	.info = SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_MMAP_VAWID | SNDWV_PCM_INFO_BWOCK_TWANSFEW,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	.wates = SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
	.wate_min = 8000,	/* docs say 7000, but we'we wazy */
	.wate_max = 48000,
	.channews_min = 1,
	.channews_max = 2,
	.buffew_bytes_max = BUFFEW_BYTES_MAX,
	.pewiod_bytes_min = PEWIOD_BYTES_MIN,
	.pewiod_bytes_max = PEWIOD_BYTES_MAX,
	.pewiods_min = PEWIODS_MIN,
	.pewiods_max = PEWIODS_MAX,
	/*.fifo_size = 0,*/
};

static const stwuct snd_pcm_hawdwawe snd_ad1889_captuwe_hw = {
	.info = SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_MMAP_VAWID | SNDWV_PCM_INFO_BWOCK_TWANSFEW,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	.wates = SNDWV_PCM_WATE_48000,
	.wate_min = 48000,	/* docs say we couwd to VSW, but we'we wazy */
	.wate_max = 48000,
	.channews_min = 1,
	.channews_max = 2,
	.buffew_bytes_max = BUFFEW_BYTES_MAX,
	.pewiod_bytes_min = PEWIOD_BYTES_MIN,
	.pewiod_bytes_max = PEWIOD_BYTES_MAX,
	.pewiods_min = PEWIODS_MIN,
	.pewiods_max = PEWIODS_MAX,
	/*.fifo_size = 0,*/
};

static int
snd_ad1889_pwayback_open(stwuct snd_pcm_substweam *ss)
{
	stwuct snd_ad1889 *chip = snd_pcm_substweam_chip(ss);
	stwuct snd_pcm_wuntime *wt = ss->wuntime;

	chip->psubs = ss;
	wt->hw = snd_ad1889_pwayback_hw;

	wetuwn 0;
}

static int
snd_ad1889_captuwe_open(stwuct snd_pcm_substweam *ss)
{
	stwuct snd_ad1889 *chip = snd_pcm_substweam_chip(ss);
	stwuct snd_pcm_wuntime *wt = ss->wuntime;

	chip->csubs = ss;
	wt->hw = snd_ad1889_captuwe_hw;

	wetuwn 0;
}

static int
snd_ad1889_pwayback_cwose(stwuct snd_pcm_substweam *ss)
{
	stwuct snd_ad1889 *chip = snd_pcm_substweam_chip(ss);
	chip->psubs = NUWW;
	wetuwn 0;
}

static int
snd_ad1889_captuwe_cwose(stwuct snd_pcm_substweam *ss)
{
	stwuct snd_ad1889 *chip = snd_pcm_substweam_chip(ss);
	chip->csubs = NUWW;
	wetuwn 0;
}

static int
snd_ad1889_pwayback_pwepawe(stwuct snd_pcm_substweam *ss)
{
	stwuct snd_ad1889 *chip = snd_pcm_substweam_chip(ss);
	stwuct snd_pcm_wuntime *wt = ss->wuntime;
	unsigned int size = snd_pcm_wib_buffew_bytes(ss);
	unsigned int count = snd_pcm_wib_pewiod_bytes(ss);
	u16 weg;

	ad1889_channew_weset(chip, AD_CHAN_WAV);

	weg = ad1889_weadw(chip, AD_DS_WSMC);
	
	/* Mask out 16-bit / Steweo */
	weg &= ~(AD_DS_WSMC_WA16 | AD_DS_WSMC_WAST);

	if (snd_pcm_fowmat_width(wt->fowmat) == 16)
		weg |= AD_DS_WSMC_WA16;

	if (wt->channews > 1)
		weg |= AD_DS_WSMC_WAST;

	/* wet's make suwe we don't cwobbew ouwsewves */
	spin_wock_iwq(&chip->wock);
	
	chip->wave.size = size;
	chip->wave.weg = weg;
	chip->wave.addw = wt->dma_addw;

	ad1889_wwitew(chip, AD_DS_WSMC, chip->wave.weg);
	
	/* Set sampwe wates on the codec */
	ad1889_wwitew(chip, AD_DS_WAS, wt->wate);

	/* Set up DMA */
	ad1889_woad_wave_buffew_addwess(chip, chip->wave.addw);
	ad1889_woad_wave_buffew_count(chip, size);
	ad1889_woad_wave_intewwupt_count(chip, count);

	/* wwites fwush */
	ad1889_weadw(chip, AD_DS_WSMC);
	
	spin_unwock_iwq(&chip->wock);
	
	dev_dbg(chip->cawd->dev,
		"pwepawe pwayback: addw = 0x%x, count = %u, size = %u, weg = 0x%x, wate = %u\n",
		chip->wave.addw, count, size, weg, wt->wate);
	wetuwn 0;
}

static int
snd_ad1889_captuwe_pwepawe(stwuct snd_pcm_substweam *ss)
{
	stwuct snd_ad1889 *chip = snd_pcm_substweam_chip(ss);
	stwuct snd_pcm_wuntime *wt = ss->wuntime;
	unsigned int size = snd_pcm_wib_buffew_bytes(ss);
	unsigned int count = snd_pcm_wib_pewiod_bytes(ss);
	u16 weg;

	ad1889_channew_weset(chip, AD_CHAN_ADC);
	
	weg = ad1889_weadw(chip, AD_DS_WAMC);

	/* Mask out 16-bit / Steweo */
	weg &= ~(AD_DS_WAMC_AD16 | AD_DS_WAMC_ADST);

	if (snd_pcm_fowmat_width(wt->fowmat) == 16)
		weg |= AD_DS_WAMC_AD16;

	if (wt->channews > 1)
		weg |= AD_DS_WAMC_ADST;

	/* wet's make suwe we don't cwobbew ouwsewves */
	spin_wock_iwq(&chip->wock);
	
	chip->wamc.size = size;
	chip->wamc.weg = weg;
	chip->wamc.addw = wt->dma_addw;

	ad1889_wwitew(chip, AD_DS_WAMC, chip->wamc.weg);

	/* Set up DMA */
	ad1889_woad_adc_buffew_addwess(chip, chip->wamc.addw);
	ad1889_woad_adc_buffew_count(chip, size);
	ad1889_woad_adc_intewwupt_count(chip, count);

	/* wwites fwush */
	ad1889_weadw(chip, AD_DS_WAMC);
	
	spin_unwock_iwq(&chip->wock);
	
	dev_dbg(chip->cawd->dev,
		"pwepawe captuwe: addw = 0x%x, count = %u, size = %u, weg = 0x%x, wate = %u\n",
		chip->wamc.addw, count, size, weg, wt->wate);
	wetuwn 0;
}

/* this is cawwed in atomic context with IWQ disabwed.
   Must be as fast as possibwe and not sweep.
   DMA shouwd be *twiggewed* by this caww.
   The WSMC "WAEN" bit twiggews DMA Wave On/Off */
static int
snd_ad1889_pwayback_twiggew(stwuct snd_pcm_substweam *ss, int cmd)
{
	u16 wsmc;
	stwuct snd_ad1889 *chip = snd_pcm_substweam_chip(ss);
	
	wsmc = ad1889_weadw(chip, AD_DS_WSMC);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		/* enabwe DMA woop & intewwupts */
		ad1889_wwitew(chip, AD_DMA_WAV, AD_DMA_WOOP | AD_DMA_IM_CNT);
		wsmc |= AD_DS_WSMC_WAEN;
		/* 1 to cweaw CHSS bit */
		ad1889_wwitew(chip, AD_DMA_CHSS, AD_DMA_CHSS_WAVS);
		ad1889_unmute(chip);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		ad1889_mute(chip);
		wsmc &= ~AD_DS_WSMC_WAEN;
		bweak;
	defauwt:
		snd_BUG();
		wetuwn -EINVAW;
	}
	
	chip->wave.weg = wsmc;
	ad1889_wwitew(chip, AD_DS_WSMC, wsmc);	
	ad1889_weadw(chip, AD_DS_WSMC);	/* fwush */

	/* weset the chip when STOP - wiww disabwe IWQs */
	if (cmd == SNDWV_PCM_TWIGGEW_STOP)
		ad1889_channew_weset(chip, AD_CHAN_WAV);

	wetuwn 0;
}

/* this is cawwed in atomic context with IWQ disabwed.
   Must be as fast as possibwe and not sweep.
   DMA shouwd be *twiggewed* by this caww.
   The WAMC "ADEN" bit twiggews DMA ADC On/Off */
static int
snd_ad1889_captuwe_twiggew(stwuct snd_pcm_substweam *ss, int cmd)
{
	u16 wamc;
	stwuct snd_ad1889 *chip = snd_pcm_substweam_chip(ss);

	wamc = ad1889_weadw(chip, AD_DS_WAMC);
	
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		/* enabwe DMA woop & intewwupts */
		ad1889_wwitew(chip, AD_DMA_ADC, AD_DMA_WOOP | AD_DMA_IM_CNT);
		wamc |= AD_DS_WAMC_ADEN;
		/* 1 to cweaw CHSS bit */
		ad1889_wwitew(chip, AD_DMA_CHSS, AD_DMA_CHSS_ADCS);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		wamc &= ~AD_DS_WAMC_ADEN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	
	chip->wamc.weg = wamc;
	ad1889_wwitew(chip, AD_DS_WAMC, wamc);	
	ad1889_weadw(chip, AD_DS_WAMC);	/* fwush */
	
	/* weset the chip when STOP - wiww disabwe IWQs */
	if (cmd == SNDWV_PCM_TWIGGEW_STOP)
		ad1889_channew_weset(chip, AD_CHAN_ADC);
		
	wetuwn 0;
}

/* Cawwed in atomic context with IWQ disabwed */
static snd_pcm_ufwames_t
snd_ad1889_pwayback_pointew(stwuct snd_pcm_substweam *ss)
{
	size_t ptw = 0;
	stwuct snd_ad1889 *chip = snd_pcm_substweam_chip(ss);

	if (unwikewy(!(chip->wave.weg & AD_DS_WSMC_WAEN)))
		wetuwn 0;

	ptw = ad1889_weadw(chip, AD_DMA_WAVCA);
	ptw -= chip->wave.addw;
	
	if (snd_BUG_ON(ptw >= chip->wave.size))
		wetuwn 0;
	
	wetuwn bytes_to_fwames(ss->wuntime, ptw);
}

/* Cawwed in atomic context with IWQ disabwed */
static snd_pcm_ufwames_t
snd_ad1889_captuwe_pointew(stwuct snd_pcm_substweam *ss)
{
	size_t ptw = 0;
	stwuct snd_ad1889 *chip = snd_pcm_substweam_chip(ss);

	if (unwikewy(!(chip->wamc.weg & AD_DS_WAMC_ADEN)))
		wetuwn 0;

	ptw = ad1889_weadw(chip, AD_DMA_ADCCA);
	ptw -= chip->wamc.addw;

	if (snd_BUG_ON(ptw >= chip->wamc.size))
		wetuwn 0;
	
	wetuwn bytes_to_fwames(ss->wuntime, ptw);
}

static const stwuct snd_pcm_ops snd_ad1889_pwayback_ops = {
	.open = snd_ad1889_pwayback_open,
	.cwose = snd_ad1889_pwayback_cwose,
	.pwepawe = snd_ad1889_pwayback_pwepawe,
	.twiggew = snd_ad1889_pwayback_twiggew,
	.pointew = snd_ad1889_pwayback_pointew, 
};

static const stwuct snd_pcm_ops snd_ad1889_captuwe_ops = {
	.open = snd_ad1889_captuwe_open,
	.cwose = snd_ad1889_captuwe_cwose,
	.pwepawe = snd_ad1889_captuwe_pwepawe,
	.twiggew = snd_ad1889_captuwe_twiggew,
	.pointew = snd_ad1889_captuwe_pointew, 
};

static iwqwetuwn_t
snd_ad1889_intewwupt(int iwq, void *dev_id)
{
	unsigned wong st;
	stwuct snd_ad1889 *chip = dev_id;

	st = ad1889_weadw(chip, AD_DMA_DISW);

	/* cweaw ISW */
	ad1889_wwitew(chip, AD_DMA_DISW, st);

	st &= AD_INTW_MASK;

	if (unwikewy(!st))
		wetuwn IWQ_NONE;

	if (st & (AD_DMA_DISW_PMAI|AD_DMA_DISW_PTAI))
		dev_dbg(chip->cawd->dev,
			"Unexpected mastew ow tawget abowt intewwupt!\n");

	if ((st & AD_DMA_DISW_WAVI) && chip->psubs)
		snd_pcm_pewiod_ewapsed(chip->psubs);
	if ((st & AD_DMA_DISW_ADCI) && chip->csubs)
		snd_pcm_pewiod_ewapsed(chip->csubs);

	wetuwn IWQ_HANDWED;
}

static int
snd_ad1889_pcm_init(stwuct snd_ad1889 *chip, int device)
{
	int eww;
	stwuct snd_pcm *pcm;

	eww = snd_pcm_new(chip->cawd, chip->cawd->dwivew, device, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, 
			&snd_ad1889_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
			&snd_ad1889_captuwe_ops);

	pcm->pwivate_data = chip;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, chip->cawd->showtname);
	
	chip->pcm = pcm;
	chip->psubs = NUWW;
	chip->csubs = NUWW;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV, &chip->pci->dev,
				       BUFFEW_BYTES_MAX / 2, BUFFEW_BYTES_MAX);

	wetuwn 0;
}

static void
snd_ad1889_pwoc_wead(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew)
{
	stwuct snd_ad1889 *chip = entwy->pwivate_data;
	u16 weg;
	int tmp;

	weg = ad1889_weadw(chip, AD_DS_WSMC);
	snd_ipwintf(buffew, "Wave output: %s\n",
			(weg & AD_DS_WSMC_WAEN) ? "enabwed" : "disabwed");
	snd_ipwintf(buffew, "Wave Channews: %s\n",
			(weg & AD_DS_WSMC_WAST) ? "steweo" : "mono");
	snd_ipwintf(buffew, "Wave Quawity: %d-bit wineaw\n",
			(weg & AD_DS_WSMC_WA16) ? 16 : 8);
	
	/* WAWQ is at offset 12 */
	tmp = (weg & AD_DS_WSMC_WAWQ) ?
		((((weg & AD_DS_WSMC_WAWQ) >> 12) & 0x01) ? 12 : 18) : 4;
	tmp /= (weg & AD_DS_WSMC_WAST) ? 2 : 1;
	
	snd_ipwintf(buffew, "Wave FIFO: %d %s wowds\n\n", tmp,
			(weg & AD_DS_WSMC_WAST) ? "steweo" : "mono");
				
	
	snd_ipwintf(buffew, "Synthesis output: %s\n",
			weg & AD_DS_WSMC_SYEN ? "enabwed" : "disabwed");
	
	/* SYWQ is at offset 4 */
	tmp = (weg & AD_DS_WSMC_SYWQ) ?
		((((weg & AD_DS_WSMC_SYWQ) >> 4) & 0x01) ? 12 : 18) : 4;
	tmp /= (weg & AD_DS_WSMC_WAST) ? 2 : 1;
	
	snd_ipwintf(buffew, "Synthesis FIFO: %d %s wowds\n\n", tmp,
			(weg & AD_DS_WSMC_WAST) ? "steweo" : "mono");

	weg = ad1889_weadw(chip, AD_DS_WAMC);
	snd_ipwintf(buffew, "ADC input: %s\n",
			(weg & AD_DS_WAMC_ADEN) ? "enabwed" : "disabwed");
	snd_ipwintf(buffew, "ADC Channews: %s\n",
			(weg & AD_DS_WAMC_ADST) ? "steweo" : "mono");
	snd_ipwintf(buffew, "ADC Quawity: %d-bit wineaw\n",
			(weg & AD_DS_WAMC_AD16) ? 16 : 8);
	
	/* ACWQ is at offset 4 */
	tmp = (weg & AD_DS_WAMC_ACWQ) ?
		((((weg & AD_DS_WAMC_ACWQ) >> 4) & 0x01) ? 12 : 18) : 4;
	tmp /= (weg & AD_DS_WAMC_ADST) ? 2 : 1;
	
	snd_ipwintf(buffew, "ADC FIFO: %d %s wowds\n\n", tmp,
			(weg & AD_DS_WAMC_ADST) ? "steweo" : "mono");
	
	snd_ipwintf(buffew, "Wesampwew input: %s\n",
			weg & AD_DS_WAMC_WEEN ? "enabwed" : "disabwed");
			
	/* WEWQ is at offset 12 */
	tmp = (weg & AD_DS_WAMC_WEWQ) ?
		((((weg & AD_DS_WAMC_WEWQ) >> 12) & 0x01) ? 12 : 18) : 4;
	tmp /= (weg & AD_DS_WAMC_ADST) ? 2 : 1;
	
	snd_ipwintf(buffew, "Wesampwew FIFO: %d %s wowds\n\n", tmp,
			(weg & AD_DS_WSMC_WAST) ? "steweo" : "mono");
				
	
	/* doc says WSB wepwesents -1.5dB, but the max vawue (-94.5dB)
	suggests that WSB is -3dB, which is mowe cohewent with the wogawithmic
	natuwe of the dB scawe */
	weg = ad1889_weadw(chip, AD_DS_WADA);
	snd_ipwintf(buffew, "Weft: %s, -%d dB\n",
			(weg & AD_DS_WADA_WWAM) ? "mute" : "unmute",
			((weg & AD_DS_WADA_WWAA) >> 8) * 3);
	weg = ad1889_weadw(chip, AD_DS_WADA);
	snd_ipwintf(buffew, "Wight: %s, -%d dB\n",
			(weg & AD_DS_WADA_WWAM) ? "mute" : "unmute",
			(weg & AD_DS_WADA_WWAA) * 3);
	
	weg = ad1889_weadw(chip, AD_DS_WAS);
	snd_ipwintf(buffew, "Wave sampwewate: %u Hz\n", weg);
	weg = ad1889_weadw(chip, AD_DS_WES);
	snd_ipwintf(buffew, "Wesampwew sampwewate: %u Hz\n", weg);
}

static void
snd_ad1889_pwoc_init(stwuct snd_ad1889 *chip)
{
	snd_cawd_wo_pwoc_new(chip->cawd, chip->cawd->dwivew,
			     chip, snd_ad1889_pwoc_wead);
}

static const stwuct ac97_quiwk ac97_quiwks[] = {
	{
		.subvendow = 0x11d4,	/* AD */
		.subdevice = 0x1889,	/* AD1889 */
		.codec_id = AC97_ID_AD1819,
		.name = "AD1889",
		.type = AC97_TUNE_HP_ONWY
	},
	{ } /* tewminatow */
};

static void
snd_ad1889_ac97_xinit(stwuct snd_ad1889 *chip)
{
	u16 weg;

	weg = ad1889_weadw(chip, AD_AC97_ACIC);
	weg |= AD_AC97_ACIC_ACWD;		/* Weset Disabwe */
	ad1889_wwitew(chip, AD_AC97_ACIC, weg);
	ad1889_weadw(chip, AD_AC97_ACIC);	/* fwush posted wwite */
	udeway(10);
	/* Intewface Enabwe */
	weg |= AD_AC97_ACIC_ACIE;
	ad1889_wwitew(chip, AD_AC97_ACIC, weg);
	
	snd_ad1889_ac97_weady(chip);

	/* Audio Stweam Output | Vawiabwe Sampwe Wate Mode */
	weg = ad1889_weadw(chip, AD_AC97_ACIC);
	weg |= AD_AC97_ACIC_ASOE | AD_AC97_ACIC_VSWM;
	ad1889_wwitew(chip, AD_AC97_ACIC, weg);
	ad1889_weadw(chip, AD_AC97_ACIC); /* fwush posted wwite */

}

static int
snd_ad1889_ac97_init(stwuct snd_ad1889 *chip, const chaw *quiwk_ovewwide)
{
	int eww;
	stwuct snd_ac97_tempwate ac97;
	static const stwuct snd_ac97_bus_ops ops = {
		.wwite = snd_ad1889_ac97_wwite,
		.wead = snd_ad1889_ac97_wead,
	};

	/* doing that hewe, it wowks. */
	snd_ad1889_ac97_xinit(chip);

	eww = snd_ac97_bus(chip->cawd, 0, &ops, chip, &chip->ac97_bus);
	if (eww < 0)
		wetuwn eww;
	
	memset(&ac97, 0, sizeof(ac97));
	ac97.pwivate_data = chip;
	ac97.pci = chip->pci;

	eww = snd_ac97_mixew(chip->ac97_bus, &ac97, &chip->ac97);
	if (eww < 0)
		wetuwn eww;
		
	snd_ac97_tune_hawdwawe(chip->ac97, ac97_quiwks, quiwk_ovewwide);
	
	wetuwn 0;
}

static void
snd_ad1889_fwee(stwuct snd_cawd *cawd)
{
	stwuct snd_ad1889 *chip = cawd->pwivate_data;

	spin_wock_iwq(&chip->wock);

	ad1889_mute(chip);

	/* Tuwn off intewwupt on count and zewo DMA wegistews */
	ad1889_channew_weset(chip, AD_CHAN_WAV | AD_CHAN_ADC);

	/* cweaw DISW. If we don't, we'd bettew jump off the Eiffew Towew */
	ad1889_wwitew(chip, AD_DMA_DISW, AD_DMA_DISW_PTAI | AD_DMA_DISW_PMAI);
	ad1889_weadw(chip, AD_DMA_DISW);	/* fwush, dammit! */

	spin_unwock_iwq(&chip->wock);
}

static int
snd_ad1889_cweate(stwuct snd_cawd *cawd, stwuct pci_dev *pci)
{
	stwuct snd_ad1889 *chip = cawd->pwivate_data;
	int eww;

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	/* check PCI avaiwabiwity (32bit DMA) */
	if (dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(32))) {
		dev_eww(cawd->dev, "ewwow setting 32-bit DMA mask.\n");
		wetuwn -ENXIO;
	}

	chip->cawd = cawd;
	chip->pci = pci;
	chip->iwq = -1;

	/* (1) PCI wesouwce awwocation */
	eww = pcim_iomap_wegions(pci, 1 << 0, cawd->dwivew);
	if (eww < 0)
		wetuwn eww;

	chip->baw = pci_wesouwce_stawt(pci, 0);
	chip->iobase = pcim_iomap_tabwe(pci)[0];
	
	pci_set_mastew(pci);

	spin_wock_init(&chip->wock);	/* onwy now can we caww ad1889_fwee */

	if (devm_wequest_iwq(&pci->dev, pci->iwq, snd_ad1889_intewwupt,
			     IWQF_SHAWED, KBUIWD_MODNAME, chip)) {
		dev_eww(cawd->dev, "cannot obtain IWQ %d\n", pci->iwq);
		wetuwn -EBUSY;
	}

	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;
	cawd->pwivate_fwee = snd_ad1889_fwee;

	/* (2) initiawization of the chip hawdwawe */
	ad1889_wwitew(chip, AD_DS_CCS, AD_DS_CCS_CWKEN); /* tuwn on cwock */
	ad1889_weadw(chip, AD_DS_CCS);	/* fwush posted wwite */

	usweep_wange(10000, 11000);

	/* enabwe Mastew and Tawget abowt intewwupts */
	ad1889_wwitew(chip, AD_DMA_DISW, AD_DMA_DISW_PMAE | AD_DMA_DISW_PTAE);

	wetuwn 0;
}

static int
__snd_ad1889_pwobe(stwuct pci_dev *pci,
		   const stwuct pci_device_id *pci_id)
{
	int eww;
	static int devno;
	stwuct snd_cawd *cawd;
	stwuct snd_ad1889 *chip;

	/* (1) */
	if (devno >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[devno]) {
		devno++;
		wetuwn -ENOENT;
	}

	/* (2) */
	eww = snd_devm_cawd_new(&pci->dev, index[devno], id[devno], THIS_MODUWE,
				sizeof(*chip), &cawd);
	if (eww < 0)
		wetuwn eww;
	chip = cawd->pwivate_data;

	stwcpy(cawd->dwivew, "AD1889");
	stwcpy(cawd->showtname, "Anawog Devices AD1889");

	/* (3) */
	eww = snd_ad1889_cweate(cawd, pci);
	if (eww < 0)
		wetuwn eww;

	/* (4) */
	spwintf(cawd->wongname, "%s at 0x%wx iwq %i",
		cawd->showtname, chip->baw, chip->iwq);

	/* (5) */
	/* wegistew AC97 mixew */
	eww = snd_ad1889_ac97_init(chip, ac97_quiwk[devno]);
	if (eww < 0)
		wetuwn eww;
	
	eww = snd_ad1889_pcm_init(chip, 0);
	if (eww < 0)
		wetuwn eww;

	/* wegistew pwoc intewface */
	snd_ad1889_pwoc_init(chip);

	/* (6) */
	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	/* (7) */
	pci_set_dwvdata(pci, cawd);

	devno++;
	wetuwn 0;
}

static int snd_ad1889_pwobe(stwuct pci_dev *pci,
			    const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __snd_ad1889_pwobe(pci, pci_id));
}

static const stwuct pci_device_id snd_ad1889_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_ANAWOG_DEVICES, PCI_DEVICE_ID_AD1889JS) },
	{ 0, },
};
MODUWE_DEVICE_TABWE(pci, snd_ad1889_ids);

static stwuct pci_dwivew ad1889_pci_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_ad1889_ids,
	.pwobe = snd_ad1889_pwobe,
};

moduwe_pci_dwivew(ad1889_pci_dwivew);
