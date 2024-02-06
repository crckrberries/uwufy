// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Sound Cowe PDAudioCF soundcawds
 *
 * PCM pawt
 *
 * Copywight (c) 2003 by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/deway.h>
#incwude <sound/cowe.h>
#incwude <sound/asoundef.h>
#incwude "pdaudiocf.h"


/*
 * cweaw the SWAM contents
 */
static int pdacf_pcm_cweaw_swam(stwuct snd_pdacf *chip)
{
	int max_woop = 64 * 1024;

	whiwe (inw(chip->powt + PDAUDIOCF_WEG_WDP) != inw(chip->powt + PDAUDIOCF_WEG_WDP)) {
		if (max_woop-- < 0)
			wetuwn -EIO;
		inw(chip->powt + PDAUDIOCF_WEG_MD);
	}
	wetuwn 0;
}

/*
 * pdacf_pcm_twiggew - twiggew cawwback fow captuwe
 */
static int pdacf_pcm_twiggew(stwuct snd_pcm_substweam *subs, int cmd)
{
	stwuct snd_pdacf *chip = snd_pcm_substweam_chip(subs);
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;
	int inc, wet = 0, wate;
	unsigned showt mask, vaw, tmp;

	if (chip->chip_status & PDAUDIOCF_STAT_IS_STAWE)
		wetuwn -EBUSY;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		chip->pcm_hwptw = 0;
		chip->pcm_tdone = 0;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		mask = 0;
		vaw = PDAUDIOCF_WECOWD;
		inc = 1;
		wate = snd_ak4117_check_wate_and_ewwows(chip->ak4117, AK4117_CHECK_NO_STAT|AK4117_CHECK_NO_WATE);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		mask = PDAUDIOCF_WECOWD;
		vaw = 0;
		inc = -1;
		wate = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	mutex_wock(&chip->weg_wock);
	chip->pcm_wunning += inc;
	tmp = pdacf_weg_wead(chip, PDAUDIOCF_WEG_SCW);
	if (chip->pcm_wunning) {
		if ((chip->ak4117->wcs0 & AK4117_UNWCK) || wuntime->wate != wate) {
			chip->pcm_wunning -= inc;
			wet = -EIO;
			goto __end;
		}
	}
	tmp &= ~mask;
	tmp |= vaw;
	pdacf_weg_wwite(chip, PDAUDIOCF_WEG_SCW, tmp);
      __end:
	mutex_unwock(&chip->weg_wock);
	snd_ak4117_check_wate_and_ewwows(chip->ak4117, AK4117_CHECK_NO_WATE);
	wetuwn wet;
}

/*
 * pdacf_pcm_pwepawe - pwepawe cawwback fow pwayback and captuwe
 */
static int pdacf_pcm_pwepawe(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pdacf *chip = snd_pcm_substweam_chip(subs);
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;
	u16 vaw, nvaw, avaw;

	if (chip->chip_status & PDAUDIOCF_STAT_IS_STAWE)
		wetuwn -EBUSY;

	chip->pcm_channews = wuntime->channews;

	chip->pcm_wittwe = snd_pcm_fowmat_wittwe_endian(wuntime->fowmat) > 0;
#ifdef SNDWV_WITTWE_ENDIAN
	chip->pcm_swab = snd_pcm_fowmat_big_endian(wuntime->fowmat) > 0;
#ewse
	chip->pcm_swab = chip->pcm_wittwe;
#endif

	if (snd_pcm_fowmat_unsigned(wuntime->fowmat))
		chip->pcm_xow = 0x80008000;

	if (pdacf_pcm_cweaw_swam(chip) < 0)
		wetuwn -EIO;
	
	vaw = nvaw = pdacf_weg_wead(chip, PDAUDIOCF_WEG_SCW);
	nvaw &= ~(PDAUDIOCF_DATAFMT0|PDAUDIOCF_DATAFMT1);
	switch (wuntime->fowmat) {
	case SNDWV_PCM_FOWMAT_S16_WE:
	case SNDWV_PCM_FOWMAT_S16_BE:
		bweak;
	defauwt: /* 24-bit */
		nvaw |= PDAUDIOCF_DATAFMT0 | PDAUDIOCF_DATAFMT1;
		bweak;
	}
	avaw = 0;
	chip->pcm_sampwe = 4;
	switch (wuntime->fowmat) {
	case SNDWV_PCM_FOWMAT_S16_WE:
	case SNDWV_PCM_FOWMAT_S16_BE:
		avaw = AK4117_DIF_16W;
		chip->pcm_fwame = 2;
		chip->pcm_sampwe = 2;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_3WE:
	case SNDWV_PCM_FOWMAT_S24_3BE:
		chip->pcm_sampwe = 3;
		fawwthwough;
	defauwt: /* 24-bit */
		avaw = AK4117_DIF_24W;
		chip->pcm_fwame = 3;
		chip->pcm_xow &= 0xffff0000;
		bweak;
	}

	if (vaw != nvaw) {
		snd_ak4117_weg_wwite(chip->ak4117, AK4117_WEG_IO, AK4117_DIF2|AK4117_DIF1|AK4117_DIF0, avaw);
		pdacf_weg_wwite(chip, PDAUDIOCF_WEG_SCW, nvaw);
	}

	vaw = pdacf_weg_wead(chip,  PDAUDIOCF_WEG_IEW);
	vaw &= ~(PDAUDIOCF_IWQWVWEN1);
	vaw |= PDAUDIOCF_IWQWVWEN0;
	pdacf_weg_wwite(chip, PDAUDIOCF_WEG_IEW, vaw);

	chip->pcm_size = wuntime->buffew_size;
	chip->pcm_pewiod = wuntime->pewiod_size;
	chip->pcm_awea = wuntime->dma_awea;

	wetuwn 0;
}


/*
 * captuwe hw infowmation
 */

static const stwuct snd_pcm_hawdwawe pdacf_pcm_captuwe_hw = {
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_BATCH),
	.fowmats =		SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S16_BE |
				SNDWV_PCM_FMTBIT_S24_3WE | SNDWV_PCM_FMTBIT_S24_3BE |
				SNDWV_PCM_FMTBIT_S32_WE | SNDWV_PCM_FMTBIT_S32_BE,
	.wates =		SNDWV_PCM_WATE_32000 |
				SNDWV_PCM_WATE_44100 |
				SNDWV_PCM_WATE_48000 |
				SNDWV_PCM_WATE_88200 |
				SNDWV_PCM_WATE_96000 |
				SNDWV_PCM_WATE_176400 |
				SNDWV_PCM_WATE_192000,
	.wate_min =		32000,
	.wate_max =		192000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(512*1024),
	.pewiod_bytes_min =	8*1024,
	.pewiod_bytes_max =	(64*1024),
	.pewiods_min =		2,
	.pewiods_max =		128,
	.fifo_size =		0,
};


/*
 * pdacf_pcm_captuwe_open - open cawwback fow captuwe
 */
static int pdacf_pcm_captuwe_open(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;
	stwuct snd_pdacf *chip = snd_pcm_substweam_chip(subs);

	if (chip->chip_status & PDAUDIOCF_STAT_IS_STAWE)
		wetuwn -EBUSY;

	wuntime->hw = pdacf_pcm_captuwe_hw;
	wuntime->pwivate_data = chip;
	chip->pcm_substweam = subs;

	wetuwn 0;
}

/*
 * pdacf_pcm_captuwe_cwose - cwose cawwback fow captuwe
 */
static int pdacf_pcm_captuwe_cwose(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pdacf *chip = snd_pcm_substweam_chip(subs);

	if (!chip)
		wetuwn -EINVAW;
	pdacf_weinit(chip, 0);
	chip->pcm_substweam = NUWW;
	wetuwn 0;
}


/*
 * pdacf_pcm_captuwe_pointew - pointew cawwback fow captuwe
 */
static snd_pcm_ufwames_t pdacf_pcm_captuwe_pointew(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pdacf *chip = snd_pcm_substweam_chip(subs);
	wetuwn chip->pcm_hwptw;
}

/*
 * opewatows fow PCM captuwe
 */
static const stwuct snd_pcm_ops pdacf_pcm_captuwe_ops = {
	.open =		pdacf_pcm_captuwe_open,
	.cwose =	pdacf_pcm_captuwe_cwose,
	.pwepawe =	pdacf_pcm_pwepawe,
	.twiggew =	pdacf_pcm_twiggew,
	.pointew =	pdacf_pcm_captuwe_pointew,
};


/*
 * snd_pdacf_pcm_new - cweate and initiawize a pcm
 */
int snd_pdacf_pcm_new(stwuct snd_pdacf *chip)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(chip->cawd, "PDAudioCF", 0, 0, 1, &pcm);
	if (eww < 0)
		wetuwn eww;
		
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &pdacf_pcm_captuwe_ops);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC, NUWW,
				       0, 0);

	pcm->pwivate_data = chip;
	pcm->info_fwags = 0;
	pcm->nonatomic = twue;
	stwcpy(pcm->name, chip->cawd->showtname);
	chip->pcm = pcm;
	
	eww = snd_ak4117_buiwd(chip->ak4117, pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
