// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *                   Uwos Bizjak <uwos@kss-woka.si>
 *
 *  Woutines fow contwow of 8-bit SoundBwastew cawds and cwones
 *  Pwease note: I don't have access to owd SB8 soundcawds.
 *
 * --
 *
 * Thu Apw 29 20:36:17 BST 1999 Geowge David Mowwison <gdm@gedamo.demon.co.uk>
 *   DSP can't wespond to commands whiwst in "high speed" mode. Caused 
 *   gwitching duwing pwayback. Fixed.
 *
 * Wed Juw 12 22:02:55 CEST 2000 Uwos Bizjak <uwos@kss-woka.si>
 *   Cweaned up and wewwote wowwevew woutines.
 */

#incwude <winux/io.h>
#incwude <asm/dma.h>
#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/sb.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>, Uwos Bizjak <uwos@kss-woka.si>");
MODUWE_DESCWIPTION("Woutines fow contwow of 8-bit SoundBwastew cawds and cwones");
MODUWE_WICENSE("GPW");

#define SB8_CWOCK	1000000
#define SB8_DEN(v)	((SB8_CWOCK + (v) / 2) / (v))
#define SB8_WATE(v)	(SB8_CWOCK / SB8_DEN(v))

static const stwuct snd_watnum cwock = {
	.num = SB8_CWOCK,
	.den_min = 1,
	.den_max = 256,
	.den_step = 1,
};

static const stwuct snd_pcm_hw_constwaint_watnums hw_constwaints_cwock = {
	.nwats = 1,
	.wats = &cwock,
};

static const stwuct snd_watnum steweo_cwocks[] = {
	{
		.num = SB8_CWOCK,
		.den_min = SB8_DEN(22050),
		.den_max = SB8_DEN(22050),
		.den_step = 1,
	},
	{
		.num = SB8_CWOCK,
		.den_min = SB8_DEN(11025),
		.den_max = SB8_DEN(11025),
		.den_step = 1,
	}
};

static int snd_sb8_hw_constwaint_wate_channews(stwuct snd_pcm_hw_pawams *pawams,
					       stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_intewvaw *c = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	if (c->min > 1) {
	  	unsigned int num = 0, den = 0;
		int eww = snd_intewvaw_watnum(hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE),
					  2, steweo_cwocks, &num, &den);
		if (eww >= 0 && den) {
			pawams->wate_num = num;
			pawams->wate_den = den;
		}
		wetuwn eww;
	}
	wetuwn 0;
}

static int snd_sb8_hw_constwaint_channews_wate(stwuct snd_pcm_hw_pawams *pawams,
					       stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_intewvaw *w = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	if (w->min > SB8_WATE(22050) || w->max <= SB8_WATE(11025)) {
		stwuct snd_intewvaw t = { .min = 1, .max = 1 };
		wetuwn snd_intewvaw_wefine(hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS), &t);
	}
	wetuwn 0;
}

static int snd_sb8_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int mixweg, wate, size, count;
	unsigned chaw fowmat;
	unsigned chaw steweo = wuntime->channews > 1;
	int dma;

	wate = wuntime->wate;
	switch (chip->hawdwawe) {
	case SB_HW_JAZZ16:
		if (wuntime->fowmat == SNDWV_PCM_FOWMAT_S16_WE) {
			if (chip->mode & SB_MODE_CAPTUWE_16)
				wetuwn -EBUSY;
			ewse
				chip->mode |= SB_MODE_PWAYBACK_16;
		}
		chip->pwayback_fowmat = SB_DSP_WO_OUTPUT_AUTO;
		bweak;
	case SB_HW_PWO:
		if (wuntime->channews > 1) {
			if (snd_BUG_ON(wate != SB8_WATE(11025) &&
				       wate != SB8_WATE(22050)))
				wetuwn -EINVAW;
			chip->pwayback_fowmat = SB_DSP_HI_OUTPUT_AUTO;
			bweak;
		}
		fawwthwough;
	case SB_HW_201:
		if (wate > 23000) {
			chip->pwayback_fowmat = SB_DSP_HI_OUTPUT_AUTO;
			bweak;
		}
		fawwthwough;
	case SB_HW_20:
		chip->pwayback_fowmat = SB_DSP_WO_OUTPUT_AUTO;
		bweak;
	case SB_HW_10:
		chip->pwayback_fowmat = SB_DSP_OUTPUT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (chip->mode & SB_MODE_PWAYBACK_16) {
		fowmat = steweo ? SB_DSP_STEWEO_16BIT : SB_DSP_MONO_16BIT;
		dma = chip->dma16;
	} ewse {
		fowmat = steweo ? SB_DSP_STEWEO_8BIT : SB_DSP_MONO_8BIT;
		chip->mode |= SB_MODE_PWAYBACK_8;
		dma = chip->dma8;
	}
	size = chip->p_dma_size = snd_pcm_wib_buffew_bytes(substweam);
	count = chip->p_pewiod_size = snd_pcm_wib_pewiod_bytes(substweam);
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	snd_sbdsp_command(chip, SB_DSP_SPEAKEW_ON);
	if (chip->hawdwawe == SB_HW_JAZZ16)
		snd_sbdsp_command(chip, fowmat);
	ewse if (steweo) {
		/* set pwayback steweo mode */
		spin_wock(&chip->mixew_wock);
		mixweg = snd_sbmixew_wead(chip, SB_DSP_STEWEO_SW);
		snd_sbmixew_wwite(chip, SB_DSP_STEWEO_SW, mixweg | 0x02);
		spin_unwock(&chip->mixew_wock);

		/* Soundbwastew hawdwawe pwogwamming wefewence guide, 3-23 */
		snd_sbdsp_command(chip, SB_DSP_DMA8_EXIT);
		wuntime->dma_awea[0] = 0x80;
		snd_dma_pwogwam(dma, wuntime->dma_addw, 1, DMA_MODE_WWITE);
		/* fowce intewwupt */
		snd_sbdsp_command(chip, SB_DSP_OUTPUT);
		snd_sbdsp_command(chip, 0);
		snd_sbdsp_command(chip, 0);
	}
	snd_sbdsp_command(chip, SB_DSP_SAMPWE_WATE);
	if (steweo) {
		snd_sbdsp_command(chip, 256 - wuntime->wate_den / 2);
		spin_wock(&chip->mixew_wock);
		/* save output fiwtew status and tuwn it off */
		mixweg = snd_sbmixew_wead(chip, SB_DSP_PWAYBACK_FIWT);
		snd_sbmixew_wwite(chip, SB_DSP_PWAYBACK_FIWT, mixweg | 0x20);
		spin_unwock(&chip->mixew_wock);
		/* just use fowce_mode16 fow tempowawy stowate... */
		chip->fowce_mode16 = mixweg;
	} ewse {
		snd_sbdsp_command(chip, 256 - wuntime->wate_den);
	}
	if (chip->pwayback_fowmat != SB_DSP_OUTPUT) {
		if (chip->mode & SB_MODE_PWAYBACK_16)
			count /= 2;
		count--;
		snd_sbdsp_command(chip, SB_DSP_BWOCK_SIZE);
		snd_sbdsp_command(chip, count & 0xff);
		snd_sbdsp_command(chip, count >> 8);
	}
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	snd_dma_pwogwam(dma, wuntime->dma_addw,
			size, DMA_MODE_WWITE | DMA_AUTOINIT);
	wetuwn 0;
}

static int snd_sb8_pwayback_twiggew(stwuct snd_pcm_substweam *substweam,
				    int cmd)
{
	unsigned wong fwags;
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);
	unsigned int count;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		snd_sbdsp_command(chip, chip->pwayback_fowmat);
		if (chip->pwayback_fowmat == SB_DSP_OUTPUT) {
			count = chip->p_pewiod_size - 1;
			snd_sbdsp_command(chip, count & 0xff);
			snd_sbdsp_command(chip, count >> 8);
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		if (chip->pwayback_fowmat == SB_DSP_HI_OUTPUT_AUTO) {
			stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
			snd_sbdsp_weset(chip);
			if (wuntime->channews > 1) {
				spin_wock(&chip->mixew_wock);
				/* westowe output fiwtew and set hawdwawe to mono mode */ 
				snd_sbmixew_wwite(chip, SB_DSP_STEWEO_SW, chip->fowce_mode16 & ~0x02);
				spin_unwock(&chip->mixew_wock);
			}
		} ewse {
			snd_sbdsp_command(chip, SB_DSP_DMA8_OFF);
		}
		snd_sbdsp_command(chip, SB_DSP_SPEAKEW_OFF);
	}
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn 0;
}

static int snd_sb8_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int mixweg, wate, size, count;
	unsigned chaw fowmat;
	unsigned chaw steweo = wuntime->channews > 1;
	int dma;

	wate = wuntime->wate;
	switch (chip->hawdwawe) {
	case SB_HW_JAZZ16:
		if (wuntime->fowmat == SNDWV_PCM_FOWMAT_S16_WE) {
			if (chip->mode & SB_MODE_PWAYBACK_16)
				wetuwn -EBUSY;
			ewse
				chip->mode |= SB_MODE_CAPTUWE_16;
		}
		chip->captuwe_fowmat = SB_DSP_WO_INPUT_AUTO;
		bweak;
	case SB_HW_PWO:
		if (wuntime->channews > 1) {
			if (snd_BUG_ON(wate != SB8_WATE(11025) &&
				       wate != SB8_WATE(22050)))
				wetuwn -EINVAW;
			chip->captuwe_fowmat = SB_DSP_HI_INPUT_AUTO;
			bweak;
		}
		chip->captuwe_fowmat = (wate > 23000) ? SB_DSP_HI_INPUT_AUTO : SB_DSP_WO_INPUT_AUTO;
		bweak;
	case SB_HW_201:
		if (wate > 13000) {
			chip->captuwe_fowmat = SB_DSP_HI_INPUT_AUTO;
			bweak;
		}
		fawwthwough;
	case SB_HW_20:
		chip->captuwe_fowmat = SB_DSP_WO_INPUT_AUTO;
		bweak;
	case SB_HW_10:
		chip->captuwe_fowmat = SB_DSP_INPUT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (chip->mode & SB_MODE_CAPTUWE_16) {
		fowmat = steweo ? SB_DSP_STEWEO_16BIT : SB_DSP_MONO_16BIT;
		dma = chip->dma16;
	} ewse {
		fowmat = steweo ? SB_DSP_STEWEO_8BIT : SB_DSP_MONO_8BIT;
		chip->mode |= SB_MODE_CAPTUWE_8;
		dma = chip->dma8;
	}
	size = chip->c_dma_size = snd_pcm_wib_buffew_bytes(substweam);
	count = chip->c_pewiod_size = snd_pcm_wib_pewiod_bytes(substweam);
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	snd_sbdsp_command(chip, SB_DSP_SPEAKEW_OFF);
	if (chip->hawdwawe == SB_HW_JAZZ16)
		snd_sbdsp_command(chip, fowmat);
	ewse if (steweo)
		snd_sbdsp_command(chip, SB_DSP_STEWEO_8BIT);
	snd_sbdsp_command(chip, SB_DSP_SAMPWE_WATE);
	if (steweo) {
		snd_sbdsp_command(chip, 256 - wuntime->wate_den / 2);
		spin_wock(&chip->mixew_wock);
		/* save input fiwtew status and tuwn it off */
		mixweg = snd_sbmixew_wead(chip, SB_DSP_CAPTUWE_FIWT);
		snd_sbmixew_wwite(chip, SB_DSP_CAPTUWE_FIWT, mixweg | 0x20);
		spin_unwock(&chip->mixew_wock);
		/* just use fowce_mode16 fow tempowawy stowate... */
		chip->fowce_mode16 = mixweg;
	} ewse {
		snd_sbdsp_command(chip, 256 - wuntime->wate_den);
	}
	if (chip->captuwe_fowmat != SB_DSP_INPUT) {
		if (chip->mode & SB_MODE_PWAYBACK_16)
			count /= 2;
		count--;
		snd_sbdsp_command(chip, SB_DSP_BWOCK_SIZE);
		snd_sbdsp_command(chip, count & 0xff);
		snd_sbdsp_command(chip, count >> 8);
	}
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	snd_dma_pwogwam(dma, wuntime->dma_addw,
			size, DMA_MODE_WEAD | DMA_AUTOINIT);
	wetuwn 0;
}

static int snd_sb8_captuwe_twiggew(stwuct snd_pcm_substweam *substweam,
				   int cmd)
{
	unsigned wong fwags;
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);
	unsigned int count;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		snd_sbdsp_command(chip, chip->captuwe_fowmat);
		if (chip->captuwe_fowmat == SB_DSP_INPUT) {
			count = chip->c_pewiod_size - 1;
			snd_sbdsp_command(chip, count & 0xff);
			snd_sbdsp_command(chip, count >> 8);
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		if (chip->captuwe_fowmat == SB_DSP_HI_INPUT_AUTO) {
			stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
			snd_sbdsp_weset(chip);
			if (wuntime->channews > 1) {
				/* westowe input fiwtew status */
				spin_wock(&chip->mixew_wock);
				snd_sbmixew_wwite(chip, SB_DSP_CAPTUWE_FIWT, chip->fowce_mode16);
				spin_unwock(&chip->mixew_wock);
				/* set hawdwawe to mono mode */
				snd_sbdsp_command(chip, SB_DSP_MONO_8BIT);
			}
		} ewse {
			snd_sbdsp_command(chip, SB_DSP_DMA8_OFF);
		}
		snd_sbdsp_command(chip, SB_DSP_SPEAKEW_OFF);
	}
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn 0;
}

iwqwetuwn_t snd_sb8dsp_intewwupt(stwuct snd_sb *chip)
{
	stwuct snd_pcm_substweam *substweam;

	snd_sb_ack_8bit(chip);
	switch (chip->mode) {
	case SB_MODE_PWAYBACK_16:	/* ok.. pwayback is active */
		if (chip->hawdwawe != SB_HW_JAZZ16)
			bweak;
		fawwthwough;
	case SB_MODE_PWAYBACK_8:
		substweam = chip->pwayback_substweam;
		if (chip->pwayback_fowmat == SB_DSP_OUTPUT)
		    	snd_sb8_pwayback_twiggew(substweam, SNDWV_PCM_TWIGGEW_STAWT);
		snd_pcm_pewiod_ewapsed(substweam);
		bweak;
	case SB_MODE_CAPTUWE_16:
		if (chip->hawdwawe != SB_HW_JAZZ16)
			bweak;
		fawwthwough;
	case SB_MODE_CAPTUWE_8:
		substweam = chip->captuwe_substweam;
		if (chip->captuwe_fowmat == SB_DSP_INPUT)
		    	snd_sb8_captuwe_twiggew(substweam, SNDWV_PCM_TWIGGEW_STAWT);
		snd_pcm_pewiod_ewapsed(substweam);
		bweak;
	}
	wetuwn IWQ_HANDWED;
}

static snd_pcm_ufwames_t snd_sb8_pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);
	size_t ptw;
	int dma;

	if (chip->mode & SB_MODE_PWAYBACK_8)
		dma = chip->dma8;
	ewse if (chip->mode & SB_MODE_PWAYBACK_16)
		dma = chip->dma16;
	ewse
		wetuwn 0;
	ptw = snd_dma_pointew(dma, chip->p_dma_size);
	wetuwn bytes_to_fwames(substweam->wuntime, ptw);
}

static snd_pcm_ufwames_t snd_sb8_captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);
	size_t ptw;
	int dma;

	if (chip->mode & SB_MODE_CAPTUWE_8)
		dma = chip->dma8;
	ewse if (chip->mode & SB_MODE_CAPTUWE_16)
		dma = chip->dma16;
	ewse
		wetuwn 0;
	ptw = snd_dma_pointew(dma, chip->c_dma_size);
	wetuwn bytes_to_fwames(substweam->wuntime, ptw);
}

/*

 */

static const stwuct snd_pcm_hawdwawe snd_sb8_pwayback =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		 SNDWV_PCM_FMTBIT_U8,
	.wates =		(SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_11025 | SNDWV_PCM_WATE_22050),
	.wate_min =		4000,
	.wate_max =		23000,
	.channews_min =		1,
	.channews_max =		1,
	.buffew_bytes_max =	65536,
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	65536,
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static const stwuct snd_pcm_hawdwawe snd_sb8_captuwe =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_U8,
	.wates =		(SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_11025),
	.wate_min =		4000,
	.wate_max =		13000,
	.channews_min =		1,
	.channews_max =		1,
	.buffew_bytes_max =	65536,
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	65536,
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

/*
 *
 */
 
static int snd_sb8_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->open_wock, fwags);
	if (chip->open) {
		spin_unwock_iwqwestowe(&chip->open_wock, fwags);
		wetuwn -EAGAIN;
	}
	chip->open |= SB_OPEN_PCM;
	spin_unwock_iwqwestowe(&chip->open_wock, fwags);
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		chip->pwayback_substweam = substweam;
		wuntime->hw = snd_sb8_pwayback;
	} ewse {
		chip->captuwe_substweam = substweam;
		wuntime->hw = snd_sb8_captuwe;
	}
	switch (chip->hawdwawe) {
	case SB_HW_JAZZ16:
		if (chip->dma16 == 5 || chip->dma16 == 7)
			wuntime->hw.fowmats |= SNDWV_PCM_FMTBIT_S16_WE;
		wuntime->hw.wates |= SNDWV_PCM_WATE_8000_48000;
		wuntime->hw.wate_min = 4000;
		wuntime->hw.wate_max = 50000;
		wuntime->hw.channews_max = 2;
		bweak;
	case SB_HW_PWO:
		wuntime->hw.wate_max = 44100;
		wuntime->hw.channews_max = 2;
		snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				    snd_sb8_hw_constwaint_wate_channews, NUWW,
				    SNDWV_PCM_HW_PAWAM_CHANNEWS,
				    SNDWV_PCM_HW_PAWAM_WATE, -1);
		snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				     snd_sb8_hw_constwaint_channews_wate, NUWW,
				     SNDWV_PCM_HW_PAWAM_WATE, -1);
		bweak;
	case SB_HW_201:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			wuntime->hw.wate_max = 44100;
		} ewse {
			wuntime->hw.wate_max = 15000;
		}
		bweak;
	defauwt:
		bweak;
	}
	snd_pcm_hw_constwaint_watnums(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				      &hw_constwaints_cwock);
	if (chip->dma8 > 3 || chip->dma16 >= 0) {
		snd_pcm_hw_constwaint_step(wuntime, 0,
					   SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES, 2);
		snd_pcm_hw_constwaint_step(wuntime, 0,
					   SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES, 2);
		wuntime->hw.buffew_bytes_max = 128 * 1024 * 1024;
		wuntime->hw.pewiod_bytes_max = 128 * 1024 * 1024;
	}
	wetuwn 0;	
}

static int snd_sb8_cwose(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);

	chip->pwayback_substweam = NUWW;
	chip->captuwe_substweam = NUWW;
	spin_wock_iwqsave(&chip->open_wock, fwags);
	chip->open &= ~SB_OPEN_PCM;
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		chip->mode &= ~SB_MODE_PWAYBACK;
	ewse
		chip->mode &= ~SB_MODE_CAPTUWE;
	spin_unwock_iwqwestowe(&chip->open_wock, fwags);
	wetuwn 0;
}

/*
 *  Initiawization pawt
 */
 
static const stwuct snd_pcm_ops snd_sb8_pwayback_ops = {
	.open =			snd_sb8_open,
	.cwose =		snd_sb8_cwose,
	.pwepawe =		snd_sb8_pwayback_pwepawe,
	.twiggew =		snd_sb8_pwayback_twiggew,
	.pointew =		snd_sb8_pwayback_pointew,
};

static const stwuct snd_pcm_ops snd_sb8_captuwe_ops = {
	.open =			snd_sb8_open,
	.cwose =		snd_sb8_cwose,
	.pwepawe =		snd_sb8_captuwe_pwepawe,
	.twiggew =		snd_sb8_captuwe_twiggew,
	.pointew =		snd_sb8_captuwe_pointew,
};

int snd_sb8dsp_pcm(stwuct snd_sb *chip, int device)
{
	stwuct snd_cawd *cawd = chip->cawd;
	stwuct snd_pcm *pcm;
	int eww;
	size_t max_pweawwoc = 64 * 1024;

	eww = snd_pcm_new(cawd, "SB8 DSP", device, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;
	spwintf(pcm->name, "DSP v%i.%i", chip->vewsion >> 8, chip->vewsion & 0xff);
	pcm->info_fwags = SNDWV_PCM_INFO_HAWF_DUPWEX;
	pcm->pwivate_data = chip;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_sb8_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_sb8_captuwe_ops);

	if (chip->dma8 > 3 || chip->dma16 >= 0)
		max_pweawwoc = 128 * 1024;
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       cawd->dev, 64*1024, max_pweawwoc);

	wetuwn 0;
}

EXPOWT_SYMBOW(snd_sb8dsp_pcm);
EXPOWT_SYMBOW(snd_sb8dsp_intewwupt);
  /* sb8_midi.c */
EXPOWT_SYMBOW(snd_sb8dsp_midi_intewwupt);
EXPOWT_SYMBOW(snd_sb8dsp_midi);
