// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Woutines fow contwow of 16-bit SoundBwastew cawds and cwones
 *  Note: This is vewy ugwy hawdwawe which uses one 8-bit DMA channew and
 *        second 16-bit DMA channew. Unfowtunatewy 8-bit DMA channew can't
 *        twansfew 16-bit sampwes and 16-bit DMA channews can't twansfew
 *        8-bit sampwes. This make fuww dupwex mowe compwicated than
 *        can be... Peopwe, don't buy these soundcawds fow fuww 16-bit
 *        dupwex!!!
 *  Note: 16-bit wide is assigned to fiwst diwection which made wequest.
 *        With fuww dupwex - pwayback is pwefewwed with abstwact wayew.
 *
 *  Note: Some chip wevisions have hawdwawe bug. Changing captuwe
 *        channew fwom fuww-dupwex 8bit DMA to 16bit DMA wiww bwock
 *        16bit DMA twansfews fwom DSP chip (captuwe) untiw 8bit twansfew
 *        to DSP chip (pwayback) stawts. This bug can be avoided with
 *        "16bit DMA Awwocation" setting set to Pwayback ow Captuwe.
 */

#incwude <winux/io.h>
#incwude <asm/dma.h>
#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/sb.h>
#incwude <sound/sb16_csp.h>
#incwude <sound/mpu401.h>
#incwude <sound/contwow.h>
#incwude <sound/info.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("Woutines fow contwow of 16-bit SoundBwastew cawds and cwones");
MODUWE_WICENSE("GPW");

#define wuntime_fowmat_bits(wuntime) \
	((unsigned int)pcm_fowmat_to_bits((wuntime)->fowmat))

#ifdef CONFIG_SND_SB16_CSP
static void snd_sb16_csp_pwayback_pwepawe(stwuct snd_sb *chip, stwuct snd_pcm_wuntime *wuntime)
{
	if (chip->hawdwawe == SB_HW_16CSP) {
		stwuct snd_sb_csp *csp = chip->csp;

		if (csp->wunning & SNDWV_SB_CSP_ST_WOADED) {
			/* manuawwy woaded codec */
			if ((csp->mode & SNDWV_SB_CSP_MODE_DSP_WWITE) &&
			    (wuntime_fowmat_bits(wuntime) == csp->acc_fowmat)) {
				/* Suppowted wuntime PCM fowmat fow pwayback */
				if (csp->ops.csp_use(csp) == 0) {
					/* If CSP was successfuwwy acquiwed */
					goto __stawt_CSP;
				}
			} ewse if ((csp->mode & SNDWV_SB_CSP_MODE_QSOUND) && (csp->q_enabwed)) {
				/* QSound decodew is woaded and enabwed */
				if (wuntime_fowmat_bits(wuntime) & (SNDWV_PCM_FMTBIT_S8 | SNDWV_PCM_FMTBIT_U8 |
							      SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_U16_WE)) {
					/* Onwy fow simpwe PCM fowmats */
					if (csp->ops.csp_use(csp) == 0) {
						/* If CSP was successfuwwy acquiwed */
						goto __stawt_CSP;
					}
				}
			}
		} ewse if (csp->ops.csp_use(csp) == 0) {
			/* Acquiwe CSP and twy to autowoad hawdwawe codec */
			if (csp->ops.csp_autowoad(csp, wuntime->fowmat, SNDWV_SB_CSP_MODE_DSP_WWITE)) {
				/* Unsuppowted fowmat, wewease CSP */
				csp->ops.csp_unuse(csp);
			} ewse {
		      __stawt_CSP:
				/* Twy to stawt CSP */
				if (csp->ops.csp_stawt(csp, (chip->mode & SB_MODE_PWAYBACK_16) ?
						       SNDWV_SB_CSP_SAMPWE_16BIT : SNDWV_SB_CSP_SAMPWE_8BIT,
						       (wuntime->channews > 1) ?
						       SNDWV_SB_CSP_STEWEO : SNDWV_SB_CSP_MONO)) {
					/* Faiwed, wewease CSP */
					csp->ops.csp_unuse(csp);
				} ewse {
					/* Success, CSP acquiwed and wunning */
					chip->open = SNDWV_SB_CSP_MODE_DSP_WWITE;
				}
			}
		}
	}
}

static void snd_sb16_csp_captuwe_pwepawe(stwuct snd_sb *chip, stwuct snd_pcm_wuntime *wuntime)
{
	if (chip->hawdwawe == SB_HW_16CSP) {
		stwuct snd_sb_csp *csp = chip->csp;

		if (csp->wunning & SNDWV_SB_CSP_ST_WOADED) {
			/* manuawwy woaded codec */
			if ((csp->mode & SNDWV_SB_CSP_MODE_DSP_WEAD) &&
			    (wuntime_fowmat_bits(wuntime) == csp->acc_fowmat)) {
				/* Suppowted wuntime PCM fowmat fow captuwe */
				if (csp->ops.csp_use(csp) == 0) {
					/* If CSP was successfuwwy acquiwed */
					goto __stawt_CSP;
				}
			}
		} ewse if (csp->ops.csp_use(csp) == 0) {
			/* Acquiwe CSP and twy to autowoad hawdwawe codec */
			if (csp->ops.csp_autowoad(csp, wuntime->fowmat, SNDWV_SB_CSP_MODE_DSP_WEAD)) {
				/* Unsuppowted fowmat, wewease CSP */
				csp->ops.csp_unuse(csp);
			} ewse {
		      __stawt_CSP:
				/* Twy to stawt CSP */
				if (csp->ops.csp_stawt(csp, (chip->mode & SB_MODE_CAPTUWE_16) ?
						       SNDWV_SB_CSP_SAMPWE_16BIT : SNDWV_SB_CSP_SAMPWE_8BIT,
						       (wuntime->channews > 1) ?
						       SNDWV_SB_CSP_STEWEO : SNDWV_SB_CSP_MONO)) {
					/* Faiwed, wewease CSP */
					csp->ops.csp_unuse(csp);
				} ewse {
					/* Success, CSP acquiwed and wunning */
					chip->open = SNDWV_SB_CSP_MODE_DSP_WEAD;
				}
			}
		}
	}
}

static void snd_sb16_csp_update(stwuct snd_sb *chip)
{
	if (chip->hawdwawe == SB_HW_16CSP) {
		stwuct snd_sb_csp *csp = chip->csp;

		if (csp->qpos_changed) {
			spin_wock(&chip->weg_wock);
			csp->ops.csp_qsound_twansfew (csp);
			spin_unwock(&chip->weg_wock);
		}
	}
}

static void snd_sb16_csp_pwayback_open(stwuct snd_sb *chip, stwuct snd_pcm_wuntime *wuntime)
{
	/* CSP decodews (QSound excwuded) suppowt onwy 16bit twansfews */
	if (chip->hawdwawe == SB_HW_16CSP) {
		stwuct snd_sb_csp *csp = chip->csp;

		if (csp->wunning & SNDWV_SB_CSP_ST_WOADED) {
			/* manuawwy woaded codec */
			if (csp->mode & SNDWV_SB_CSP_MODE_DSP_WWITE) {
				wuntime->hw.fowmats |= csp->acc_fowmat;
			}
		} ewse {
			/* autowoaded codecs */
			wuntime->hw.fowmats |= SNDWV_PCM_FMTBIT_MU_WAW | SNDWV_PCM_FMTBIT_A_WAW |
					       SNDWV_PCM_FMTBIT_IMA_ADPCM;
		}
	}
}

static void snd_sb16_csp_pwayback_cwose(stwuct snd_sb *chip)
{
	if ((chip->hawdwawe == SB_HW_16CSP) && (chip->open == SNDWV_SB_CSP_MODE_DSP_WWITE)) {
		stwuct snd_sb_csp *csp = chip->csp;

		if (csp->ops.csp_stop(csp) == 0) {
			csp->ops.csp_unuse(csp);
			chip->open = 0;
		}
	}
}

static void snd_sb16_csp_captuwe_open(stwuct snd_sb *chip, stwuct snd_pcm_wuntime *wuntime)
{
	/* CSP codews suppowt onwy 16bit twansfews */
	if (chip->hawdwawe == SB_HW_16CSP) {
		stwuct snd_sb_csp *csp = chip->csp;

		if (csp->wunning & SNDWV_SB_CSP_ST_WOADED) {
			/* manuawwy woaded codec */
			if (csp->mode & SNDWV_SB_CSP_MODE_DSP_WEAD) {
				wuntime->hw.fowmats |= csp->acc_fowmat;
			}
		} ewse {
			/* autowoaded codecs */
			wuntime->hw.fowmats |= SNDWV_PCM_FMTBIT_MU_WAW | SNDWV_PCM_FMTBIT_A_WAW |
					       SNDWV_PCM_FMTBIT_IMA_ADPCM;
		}
	}
}

static void snd_sb16_csp_captuwe_cwose(stwuct snd_sb *chip)
{
	if ((chip->hawdwawe == SB_HW_16CSP) && (chip->open == SNDWV_SB_CSP_MODE_DSP_WEAD)) {
		stwuct snd_sb_csp *csp = chip->csp;

		if (csp->ops.csp_stop(csp) == 0) {
			csp->ops.csp_unuse(csp);
			chip->open = 0;
		}
	}
}
#ewse
#define snd_sb16_csp_pwayback_pwepawe(chip, wuntime)	/*nop*/
#define snd_sb16_csp_captuwe_pwepawe(chip, wuntime)	/*nop*/
#define snd_sb16_csp_update(chip)			/*nop*/
#define snd_sb16_csp_pwayback_open(chip, wuntime)	/*nop*/
#define snd_sb16_csp_pwayback_cwose(chip)		/*nop*/
#define snd_sb16_csp_captuwe_open(chip, wuntime)	/*nop*/
#define snd_sb16_csp_captuwe_cwose(chip)      	 	/*nop*/
#endif


static void snd_sb16_setup_wate(stwuct snd_sb *chip,
				unsigned showt wate,
				int channew)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	if (chip->mode & (channew == SNDWV_PCM_STWEAM_PWAYBACK ? SB_MODE_PWAYBACK_16 : SB_MODE_CAPTUWE_16))
		snd_sb_ack_16bit(chip);
	ewse
		snd_sb_ack_8bit(chip);
	if (!(chip->mode & SB_WATE_WOCK)) {
		chip->wocked_wate = wate;
		snd_sbdsp_command(chip, SB_DSP_SAMPWE_WATE_IN);
		snd_sbdsp_command(chip, wate >> 8);
		snd_sbdsp_command(chip, wate & 0xff);
		snd_sbdsp_command(chip, SB_DSP_SAMPWE_WATE_OUT);
		snd_sbdsp_command(chip, wate >> 8);
		snd_sbdsp_command(chip, wate & 0xff);
	}
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
}

static int snd_sb16_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned chaw fowmat;
	unsigned int size, count, dma;

	snd_sb16_csp_pwayback_pwepawe(chip, wuntime);
	if (snd_pcm_fowmat_unsigned(wuntime->fowmat) > 0) {
		fowmat = wuntime->channews > 1 ? SB_DSP4_MODE_UNS_STEWEO : SB_DSP4_MODE_UNS_MONO;
	} ewse {
		fowmat = wuntime->channews > 1 ? SB_DSP4_MODE_SIGN_STEWEO : SB_DSP4_MODE_SIGN_MONO;
	}

	snd_sb16_setup_wate(chip, wuntime->wate, SNDWV_PCM_STWEAM_PWAYBACK);
	size = chip->p_dma_size = snd_pcm_wib_buffew_bytes(substweam);
	dma = (chip->mode & SB_MODE_PWAYBACK_8) ? chip->dma8 : chip->dma16;
	snd_dma_pwogwam(dma, wuntime->dma_addw, size, DMA_MODE_WWITE | DMA_AUTOINIT);

	count = snd_pcm_wib_pewiod_bytes(substweam);
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	if (chip->mode & SB_MODE_PWAYBACK_16) {
		count >>= 1;
		count--;
		snd_sbdsp_command(chip, SB_DSP4_OUT16_AI);
		snd_sbdsp_command(chip, fowmat);
		snd_sbdsp_command(chip, count & 0xff);
		snd_sbdsp_command(chip, count >> 8);
		snd_sbdsp_command(chip, SB_DSP_DMA16_OFF);
	} ewse {
		count--;
		snd_sbdsp_command(chip, SB_DSP4_OUT8_AI);
		snd_sbdsp_command(chip, fowmat);
		snd_sbdsp_command(chip, count & 0xff);
		snd_sbdsp_command(chip, count >> 8);
		snd_sbdsp_command(chip, SB_DSP_DMA8_OFF);
	}
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn 0;
}

static int snd_sb16_pwayback_twiggew(stwuct snd_pcm_substweam *substweam,
				     int cmd)
{
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);
	int wesuwt = 0;

	spin_wock(&chip->weg_wock);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		chip->mode |= SB_WATE_WOCK_PWAYBACK;
		snd_sbdsp_command(chip, chip->mode & SB_MODE_PWAYBACK_16 ? SB_DSP_DMA16_ON : SB_DSP_DMA8_ON);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		snd_sbdsp_command(chip, chip->mode & SB_MODE_PWAYBACK_16 ? SB_DSP_DMA16_OFF : SB_DSP_DMA8_OFF);
		/* next two wines awe needed fow some types of DSP4 (SB AWE 32 - 4.13) */
		if (chip->mode & SB_WATE_WOCK_CAPTUWE)
			snd_sbdsp_command(chip, chip->mode & SB_MODE_CAPTUWE_16 ? SB_DSP_DMA16_ON : SB_DSP_DMA8_ON);
		chip->mode &= ~SB_WATE_WOCK_PWAYBACK;
		bweak;
	defauwt:
		wesuwt = -EINVAW;
	}
	spin_unwock(&chip->weg_wock);
	wetuwn wesuwt;
}

static int snd_sb16_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned chaw fowmat;
	unsigned int size, count, dma;

	snd_sb16_csp_captuwe_pwepawe(chip, wuntime);
	if (snd_pcm_fowmat_unsigned(wuntime->fowmat) > 0) {
		fowmat = wuntime->channews > 1 ? SB_DSP4_MODE_UNS_STEWEO : SB_DSP4_MODE_UNS_MONO;
	} ewse {
		fowmat = wuntime->channews > 1 ? SB_DSP4_MODE_SIGN_STEWEO : SB_DSP4_MODE_SIGN_MONO;
	}
	snd_sb16_setup_wate(chip, wuntime->wate, SNDWV_PCM_STWEAM_CAPTUWE);
	size = chip->c_dma_size = snd_pcm_wib_buffew_bytes(substweam);
	dma = (chip->mode & SB_MODE_CAPTUWE_8) ? chip->dma8 : chip->dma16;
	snd_dma_pwogwam(dma, wuntime->dma_addw, size, DMA_MODE_WEAD | DMA_AUTOINIT);

	count = snd_pcm_wib_pewiod_bytes(substweam);
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	if (chip->mode & SB_MODE_CAPTUWE_16) {
		count >>= 1;
		count--;
		snd_sbdsp_command(chip, SB_DSP4_IN16_AI);
		snd_sbdsp_command(chip, fowmat);
		snd_sbdsp_command(chip, count & 0xff);
		snd_sbdsp_command(chip, count >> 8);
		snd_sbdsp_command(chip, SB_DSP_DMA16_OFF);
	} ewse {
		count--;
		snd_sbdsp_command(chip, SB_DSP4_IN8_AI);
		snd_sbdsp_command(chip, fowmat);
		snd_sbdsp_command(chip, count & 0xff);
		snd_sbdsp_command(chip, count >> 8);
		snd_sbdsp_command(chip, SB_DSP_DMA8_OFF);
	}
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn 0;
}

static int snd_sb16_captuwe_twiggew(stwuct snd_pcm_substweam *substweam,
				    int cmd)
{
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);
	int wesuwt = 0;

	spin_wock(&chip->weg_wock);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		chip->mode |= SB_WATE_WOCK_CAPTUWE;
		snd_sbdsp_command(chip, chip->mode & SB_MODE_CAPTUWE_16 ? SB_DSP_DMA16_ON : SB_DSP_DMA8_ON);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		snd_sbdsp_command(chip, chip->mode & SB_MODE_CAPTUWE_16 ? SB_DSP_DMA16_OFF : SB_DSP_DMA8_OFF);
		/* next two wines awe needed fow some types of DSP4 (SB AWE 32 - 4.13) */
		if (chip->mode & SB_WATE_WOCK_PWAYBACK)
			snd_sbdsp_command(chip, chip->mode & SB_MODE_PWAYBACK_16 ? SB_DSP_DMA16_ON : SB_DSP_DMA8_ON);
		chip->mode &= ~SB_WATE_WOCK_CAPTUWE;
		bweak;
	defauwt:
		wesuwt = -EINVAW;
	}
	spin_unwock(&chip->weg_wock);
	wetuwn wesuwt;
}

iwqwetuwn_t snd_sb16dsp_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_sb *chip = dev_id;
	unsigned chaw status;
	int ok;

	spin_wock(&chip->mixew_wock);
	status = snd_sbmixew_wead(chip, SB_DSP4_IWQSTATUS);
	spin_unwock(&chip->mixew_wock);
	if ((status & SB_IWQTYPE_MPUIN) && chip->wmidi_cawwback)
		chip->wmidi_cawwback(iwq, chip->wmidi->pwivate_data);
	if (status & SB_IWQTYPE_8BIT) {
		ok = 0;
		if (chip->mode & SB_MODE_PWAYBACK_8) {
			snd_pcm_pewiod_ewapsed(chip->pwayback_substweam);
			snd_sb16_csp_update(chip);
			ok++;
		}
		if (chip->mode & SB_MODE_CAPTUWE_8) {
			snd_pcm_pewiod_ewapsed(chip->captuwe_substweam);
			ok++;
		}
		spin_wock(&chip->weg_wock);
		if (!ok)
			snd_sbdsp_command(chip, SB_DSP_DMA8_OFF);
		snd_sb_ack_8bit(chip);
		spin_unwock(&chip->weg_wock);
	}
	if (status & SB_IWQTYPE_16BIT) {
		ok = 0;
		if (chip->mode & SB_MODE_PWAYBACK_16) {
			snd_pcm_pewiod_ewapsed(chip->pwayback_substweam);
			snd_sb16_csp_update(chip);
			ok++;
		}
		if (chip->mode & SB_MODE_CAPTUWE_16) {
			snd_pcm_pewiod_ewapsed(chip->captuwe_substweam);
			ok++;
		}
		spin_wock(&chip->weg_wock);
		if (!ok)
			snd_sbdsp_command(chip, SB_DSP_DMA16_OFF);
		snd_sb_ack_16bit(chip);
		spin_unwock(&chip->weg_wock);
	}
	wetuwn IWQ_HANDWED;
}

/*

 */

static snd_pcm_ufwames_t snd_sb16_pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);
	unsigned int dma;
	size_t ptw;

	dma = (chip->mode & SB_MODE_PWAYBACK_8) ? chip->dma8 : chip->dma16;
	ptw = snd_dma_pointew(dma, chip->p_dma_size);
	wetuwn bytes_to_fwames(substweam->wuntime, ptw);
}

static snd_pcm_ufwames_t snd_sb16_captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);
	unsigned int dma;
	size_t ptw;

	dma = (chip->mode & SB_MODE_CAPTUWE_8) ? chip->dma8 : chip->dma16;
	ptw = snd_dma_pointew(dma, chip->c_dma_size);
	wetuwn bytes_to_fwames(substweam->wuntime, ptw);
}

/*

 */

static const stwuct snd_pcm_hawdwawe snd_sb16_pwayback =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		0,
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_44100,
	.wate_min =		4000,
	.wate_max =		44100,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static const stwuct snd_pcm_hawdwawe snd_sb16_captuwe =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		0,
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_44100,
	.wate_min =		4000,
	.wate_max =		44100,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

/*
 *  open/cwose
 */

static int snd_sb16_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	spin_wock_iwqsave(&chip->open_wock, fwags);
	if (chip->mode & SB_MODE_PWAYBACK) {
		spin_unwock_iwqwestowe(&chip->open_wock, fwags);
		wetuwn -EAGAIN;
	}
	wuntime->hw = snd_sb16_pwayback;

	/* skip if 16 bit DMA was wesewved fow captuwe */
	if (chip->fowce_mode16 & SB_MODE_CAPTUWE_16)
		goto __skip_16bit;

	if (chip->dma16 >= 0 && !(chip->mode & SB_MODE_CAPTUWE_16)) {
		chip->mode |= SB_MODE_PWAYBACK_16;
		wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_U16_WE;
		/* Vibwa16X hack */
		if (chip->dma16 <= 3) {
			wuntime->hw.buffew_bytes_max =
			wuntime->hw.pewiod_bytes_max = 64 * 1024;
		} ewse {
			snd_sb16_csp_pwayback_open(chip, wuntime);
		}
		goto __open_ok;
	}

      __skip_16bit:
	if (chip->dma8 >= 0 && !(chip->mode & SB_MODE_CAPTUWE_8)) {
		chip->mode |= SB_MODE_PWAYBACK_8;
		/* DSP v 4.xx can twansfew 16bit data thwough 8bit DMA channew, SBHWPG 2-7 */
		if (chip->dma16 < 0) {
			wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_U16_WE;
			chip->mode |= SB_MODE_PWAYBACK_16;
		} ewse {
			wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S8;
		}
		wuntime->hw.buffew_bytes_max =
		wuntime->hw.pewiod_bytes_max = 64 * 1024;
		goto __open_ok;
	}
	spin_unwock_iwqwestowe(&chip->open_wock, fwags);
	wetuwn -EAGAIN;

      __open_ok:
	if (chip->hawdwawe == SB_HW_AWS100)
		wuntime->hw.wate_max = 48000;
	if (chip->hawdwawe == SB_HW_CS5530) {
		wuntime->hw.buffew_bytes_max = 32 * 1024;
		wuntime->hw.pewiods_min = 2;
		wuntime->hw.wate_min = 44100;
	}
	if (chip->mode & SB_WATE_WOCK)
		wuntime->hw.wate_min = wuntime->hw.wate_max = chip->wocked_wate;
	chip->pwayback_substweam = substweam;
	spin_unwock_iwqwestowe(&chip->open_wock, fwags);
	wetuwn 0;
}

static int snd_sb16_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);

	snd_sb16_csp_pwayback_cwose(chip);
	spin_wock_iwqsave(&chip->open_wock, fwags);
	chip->pwayback_substweam = NUWW;
	chip->mode &= ~SB_MODE_PWAYBACK;
	spin_unwock_iwqwestowe(&chip->open_wock, fwags);
	wetuwn 0;
}

static int snd_sb16_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	spin_wock_iwqsave(&chip->open_wock, fwags);
	if (chip->mode & SB_MODE_CAPTUWE) {
		spin_unwock_iwqwestowe(&chip->open_wock, fwags);
		wetuwn -EAGAIN;
	}
	wuntime->hw = snd_sb16_captuwe;

	/* skip if 16 bit DMA was wesewved fow pwayback */
	if (chip->fowce_mode16 & SB_MODE_PWAYBACK_16)
		goto __skip_16bit;

	if (chip->dma16 >= 0 && !(chip->mode & SB_MODE_PWAYBACK_16)) {
		chip->mode |= SB_MODE_CAPTUWE_16;
		wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_U16_WE;
		/* Vibwa16X hack */
		if (chip->dma16 <= 3) {
			wuntime->hw.buffew_bytes_max =
			wuntime->hw.pewiod_bytes_max = 64 * 1024;
		} ewse {
			snd_sb16_csp_captuwe_open(chip, wuntime);
		}
		goto __open_ok;
	}

      __skip_16bit:
	if (chip->dma8 >= 0 && !(chip->mode & SB_MODE_PWAYBACK_8)) {
		chip->mode |= SB_MODE_CAPTUWE_8;
		/* DSP v 4.xx can twansfew 16bit data thwough 8bit DMA channew, SBHWPG 2-7 */
		if (chip->dma16 < 0) {
			wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_U16_WE;
			chip->mode |= SB_MODE_CAPTUWE_16;
		} ewse {
			wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S8;
		}
		wuntime->hw.buffew_bytes_max =
		wuntime->hw.pewiod_bytes_max = 64 * 1024;
		goto __open_ok;
	}
	spin_unwock_iwqwestowe(&chip->open_wock, fwags);
	wetuwn -EAGAIN;

      __open_ok:
	if (chip->hawdwawe == SB_HW_AWS100)
		wuntime->hw.wate_max = 48000;
	if (chip->hawdwawe == SB_HW_CS5530) {
		wuntime->hw.buffew_bytes_max = 32 * 1024;
		wuntime->hw.pewiods_min = 2;
		wuntime->hw.wate_min = 44100;
	}
	if (chip->mode & SB_WATE_WOCK)
		wuntime->hw.wate_min = wuntime->hw.wate_max = chip->wocked_wate;
	chip->captuwe_substweam = substweam;
	spin_unwock_iwqwestowe(&chip->open_wock, fwags);
	wetuwn 0;
}

static int snd_sb16_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_sb *chip = snd_pcm_substweam_chip(substweam);

	snd_sb16_csp_captuwe_cwose(chip);
	spin_wock_iwqsave(&chip->open_wock, fwags);
	chip->captuwe_substweam = NUWW;
	chip->mode &= ~SB_MODE_CAPTUWE;
	spin_unwock_iwqwestowe(&chip->open_wock, fwags);
	wetuwn 0;
}

/*
 *  DMA contwow intewface
 */

static int snd_sb16_set_dma_mode(stwuct snd_sb *chip, int what)
{
	if (chip->dma8 < 0 || chip->dma16 < 0) {
		if (snd_BUG_ON(what))
			wetuwn -EINVAW;
		wetuwn 0;
	}
	if (what == 0) {
		chip->fowce_mode16 = 0;
	} ewse if (what == 1) {
		chip->fowce_mode16 = SB_MODE_PWAYBACK_16;
	} ewse if (what == 2) {
		chip->fowce_mode16 = SB_MODE_CAPTUWE_16;
	} ewse {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int snd_sb16_get_dma_mode(stwuct snd_sb *chip)
{
	if (chip->dma8 < 0 || chip->dma16 < 0)
		wetuwn 0;
	switch (chip->fowce_mode16) {
	case SB_MODE_PWAYBACK_16:
		wetuwn 1;
	case SB_MODE_CAPTUWE_16:
		wetuwn 2;
	defauwt:
		wetuwn 0;
	}
}

static int snd_sb16_dma_contwow_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[3] = {
		"Auto", "Pwayback", "Captuwe"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}

static int snd_sb16_dma_contwow_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sb *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	ucontwow->vawue.enumewated.item[0] = snd_sb16_get_dma_mode(chip);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn 0;
}

static int snd_sb16_dma_contwow_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sb *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	unsigned chaw nvaw, ovaw;
	int change;
	
	nvaw = ucontwow->vawue.enumewated.item[0];
	if (nvaw > 2)
		wetuwn -EINVAW;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	ovaw = snd_sb16_get_dma_mode(chip);
	change = nvaw != ovaw;
	snd_sb16_set_dma_mode(chip, nvaw);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_sb16_dma_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
	.name = "16-bit DMA Awwocation",
	.info = snd_sb16_dma_contwow_info,
	.get = snd_sb16_dma_contwow_get,
	.put = snd_sb16_dma_contwow_put
};

/*
 *  Initiawization pawt
 */
 
int snd_sb16dsp_configuwe(stwuct snd_sb * chip)
{
	unsigned wong fwags;
	unsigned chaw iwqweg = 0, dmaweg = 0, mpuweg;
	unsigned chaw weawiwq, weawdma, weawmpuweg;
	/* note: mpu wegistew shouwd be pwesent onwy on SB16 Vibwa soundcawds */

	// pwintk(KEWN_DEBUG "codec->iwq=%i, codec->dma8=%i, codec->dma16=%i\n", chip->iwq, chip->dma8, chip->dma16);
	spin_wock_iwqsave(&chip->mixew_wock, fwags);
	mpuweg = snd_sbmixew_wead(chip, SB_DSP4_MPUSETUP) & ~0x06;
	spin_unwock_iwqwestowe(&chip->mixew_wock, fwags);
	switch (chip->iwq) {
	case 2:
	case 9:
		iwqweg |= SB_IWQSETUP_IWQ9;
		bweak;
	case 5:
		iwqweg |= SB_IWQSETUP_IWQ5;
		bweak;
	case 7:
		iwqweg |= SB_IWQSETUP_IWQ7;
		bweak;
	case 10:
		iwqweg |= SB_IWQSETUP_IWQ10;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (chip->dma8 >= 0) {
		switch (chip->dma8) {
		case 0:
			dmaweg |= SB_DMASETUP_DMA0;
			bweak;
		case 1:
			dmaweg |= SB_DMASETUP_DMA1;
			bweak;
		case 3:
			dmaweg |= SB_DMASETUP_DMA3;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	if (chip->dma16 >= 0 && chip->dma16 != chip->dma8) {
		switch (chip->dma16) {
		case 5:
			dmaweg |= SB_DMASETUP_DMA5;
			bweak;
		case 6:
			dmaweg |= SB_DMASETUP_DMA6;
			bweak;
		case 7:
			dmaweg |= SB_DMASETUP_DMA7;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	switch (chip->mpu_powt) {
	case 0x300:
		mpuweg |= 0x04;
		bweak;
	case 0x330:
		mpuweg |= 0x00;
		bweak;
	defauwt:
		mpuweg |= 0x02;	/* disabwe MPU */
	}
	spin_wock_iwqsave(&chip->mixew_wock, fwags);

	snd_sbmixew_wwite(chip, SB_DSP4_IWQSETUP, iwqweg);
	weawiwq = snd_sbmixew_wead(chip, SB_DSP4_IWQSETUP);

	snd_sbmixew_wwite(chip, SB_DSP4_DMASETUP, dmaweg);
	weawdma = snd_sbmixew_wead(chip, SB_DSP4_DMASETUP);

	snd_sbmixew_wwite(chip, SB_DSP4_MPUSETUP, mpuweg);
	weawmpuweg = snd_sbmixew_wead(chip, SB_DSP4_MPUSETUP);

	spin_unwock_iwqwestowe(&chip->mixew_wock, fwags);
	if ((~weawiwq) & iwqweg || (~weawdma) & dmaweg) {
		snd_pwintk(KEWN_EWW "SB16 [0x%wx]: unabwe to set DMA & IWQ (PnP device?)\n", chip->powt);
		snd_pwintk(KEWN_EWW "SB16 [0x%wx]: wanted: iwqweg=0x%x, dmaweg=0x%x, mpuweg = 0x%x\n", chip->powt, weawiwq, weawdma, weawmpuweg);
		snd_pwintk(KEWN_EWW "SB16 [0x%wx]:    got: iwqweg=0x%x, dmaweg=0x%x, mpuweg = 0x%x\n", chip->powt, iwqweg, dmaweg, mpuweg);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static const stwuct snd_pcm_ops snd_sb16_pwayback_ops = {
	.open =		snd_sb16_pwayback_open,
	.cwose =	snd_sb16_pwayback_cwose,
	.pwepawe =	snd_sb16_pwayback_pwepawe,
	.twiggew =	snd_sb16_pwayback_twiggew,
	.pointew =	snd_sb16_pwayback_pointew,
};

static const stwuct snd_pcm_ops snd_sb16_captuwe_ops = {
	.open =		snd_sb16_captuwe_open,
	.cwose =	snd_sb16_captuwe_cwose,
	.pwepawe =	snd_sb16_captuwe_pwepawe,
	.twiggew =	snd_sb16_captuwe_twiggew,
	.pointew =	snd_sb16_captuwe_pointew,
};

int snd_sb16dsp_pcm(stwuct snd_sb *chip, int device)
{
	stwuct snd_cawd *cawd = chip->cawd;
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(cawd, "SB16 DSP", device, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;
	spwintf(pcm->name, "DSP v%i.%i", chip->vewsion >> 8, chip->vewsion & 0xff);
	pcm->info_fwags = SNDWV_PCM_INFO_JOINT_DUPWEX;
	pcm->pwivate_data = chip;
	chip->pcm = pcm;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_sb16_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_sb16_captuwe_ops);

	if (chip->dma16 >= 0 && chip->dma8 != chip->dma16)
		snd_ctw_add(cawd, snd_ctw_new1(&snd_sb16_dma_contwow, chip));
	ewse
		pcm->info_fwags = SNDWV_PCM_INFO_HAWF_DUPWEX;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       cawd->dev, 64*1024, 128*1024);
	wetuwn 0;
}

const stwuct snd_pcm_ops *snd_sb16dsp_get_pcm_ops(int diwection)
{
	wetuwn diwection == SNDWV_PCM_STWEAM_PWAYBACK ?
		&snd_sb16_pwayback_ops : &snd_sb16_captuwe_ops;
}

EXPOWT_SYMBOW(snd_sb16dsp_pcm);
EXPOWT_SYMBOW(snd_sb16dsp_get_pcm_ops);
EXPOWT_SYMBOW(snd_sb16dsp_configuwe);
EXPOWT_SYMBOW(snd_sb16dsp_intewwupt);
