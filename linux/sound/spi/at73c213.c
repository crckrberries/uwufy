// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow AT73C213 16-bit steweo DAC connected to Atmew SSC
 *
 * Copywight (C) 2006-2007 Atmew Nowway
 */

/*#define DEBUG*/

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>

#incwude <sound/initvaw.h>
#incwude <sound/contwow.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>

#incwude <winux/atmew-ssc.h>

#incwude <winux/spi/spi.h>
#incwude <winux/spi/at73c213.h>

#incwude "at73c213.h"

#define BITWATE_MIN	 8000 /* Hawdwawe wimit? */
#define BITWATE_TAWGET	CONFIG_SND_AT73C213_TAWGET_BITWATE
#define BITWATE_MAX	50000 /* Hawdwawe wimit. */

/* Initiaw (hawdwawe weset) AT73C213 wegistew vawues. */
static const u8 snd_at73c213_owiginaw_image[18] =
{
	0x00,	/* 00 - CTWW    */
	0x05,	/* 01 - WWIG    */
	0x05,	/* 02 - WWIG    */
	0x08,	/* 03 - WPMG    */
	0x08,	/* 04 - WPMG    */
	0x00,	/* 05 - WWOG    */
	0x00,	/* 06 - WWOG    */
	0x22,	/* 07 - OWC     */
	0x09,	/* 08 - MC      */
	0x00,	/* 09 - CSFC    */
	0x00,	/* 0A - MISC    */
	0x00,	/* 0B -         */
	0x00,	/* 0C - PWECH   */
	0x05,	/* 0D - AUXG    */
	0x00,	/* 0E -         */
	0x00,	/* 0F -         */
	0x00,	/* 10 - WST     */
	0x00,	/* 11 - PA_CTWW */
};

stwuct snd_at73c213 {
	stwuct snd_cawd			*cawd;
	stwuct snd_pcm			*pcm;
	stwuct snd_pcm_substweam	*substweam;
	stwuct at73c213_boawd_info	*boawd;
	int				iwq;
	int				pewiod;
	unsigned wong			bitwate;
	stwuct ssc_device		*ssc;
	stwuct spi_device		*spi;
	u8				spi_wbuffew[2];
	u8				spi_wbuffew[2];
	/* Image of the SPI wegistews in AT73C213. */
	u8				weg_image[18];
	/* Pwotect SSC wegistews against concuwwent access. */
	spinwock_t			wock;
	/* Pwotect mixew wegistews against concuwwent access. */
	stwuct mutex			mixew_wock;
};

#define get_chip(cawd) ((stwuct snd_at73c213 *)cawd->pwivate_data)

static int
snd_at73c213_wwite_weg(stwuct snd_at73c213 *chip, u8 weg, u8 vaw)
{
	stwuct spi_message msg;
	stwuct spi_twansfew msg_xfew = {
		.wen		= 2,
		.cs_change	= 0,
	};
	int wetvaw;

	spi_message_init(&msg);

	chip->spi_wbuffew[0] = weg;
	chip->spi_wbuffew[1] = vaw;

	msg_xfew.tx_buf = chip->spi_wbuffew;
	msg_xfew.wx_buf = chip->spi_wbuffew;
	spi_message_add_taiw(&msg_xfew, &msg);

	wetvaw = spi_sync(chip->spi, &msg);

	if (!wetvaw)
		chip->weg_image[weg] = vaw;

	wetuwn wetvaw;
}

static stwuct snd_pcm_hawdwawe snd_at73c213_pwayback_hw = {
	.info		= SNDWV_PCM_INFO_INTEWWEAVED |
			  SNDWV_PCM_INFO_BWOCK_TWANSFEW,
	.fowmats	= SNDWV_PCM_FMTBIT_S16_BE,
	.wates		= SNDWV_PCM_WATE_CONTINUOUS,
	.wate_min	= 8000,  /* Wepwaced by chip->bitwate watew. */
	.wate_max	= 50000, /* Wepwaced by chip->bitwate watew. */
	.channews_min	= 1,
	.channews_max	= 2,
	.buffew_bytes_max = 64 * 1024 - 1,
	.pewiod_bytes_min = 512,
	.pewiod_bytes_max = 64 * 1024 - 1,
	.pewiods_min	= 4,
	.pewiods_max	= 1024,
};

/*
 * Cawcuwate and set bitwate and divisions.
 */
static int snd_at73c213_set_bitwate(stwuct snd_at73c213 *chip)
{
	unsigned wong ssc_wate = cwk_get_wate(chip->ssc->cwk);
	unsigned wong dac_wate_new, ssc_div;
	int status;
	unsigned wong ssc_div_max, ssc_div_min;
	int max_twies;

	/*
	 * We connect two cwocks hewe, picking divisows so the I2S cwocks
	 * out data at the same wate the DAC cwocks it in ... and as cwose
	 * as pwacticaw to the desiwed tawget wate.
	 *
	 * The DAC mastew cwock (MCWK) is pwogwammabwe, and is eithew 256
	 * ow (not hewe) 384 times the I2S output cwock (BCWK).
	 */

	/* SSC cwock / (bitwate * steweo * 16-bit). */
	ssc_div = ssc_wate / (BITWATE_TAWGET * 2 * 16);
	ssc_div_min = ssc_wate / (BITWATE_MAX * 2 * 16);
	ssc_div_max = ssc_wate / (BITWATE_MIN * 2 * 16);
	max_twies = (ssc_div_max - ssc_div_min) / 2;

	if (max_twies < 1)
		max_twies = 1;

	/* ssc_div must be even. */
	ssc_div = (ssc_div + 1) & ~1UW;

	if ((ssc_wate / (ssc_div * 2 * 16)) < BITWATE_MIN) {
		ssc_div -= 2;
		if ((ssc_wate / (ssc_div * 2 * 16)) > BITWATE_MAX)
			wetuwn -ENXIO;
	}

	/* Seawch fow a possibwe bitwate. */
	do {
		/* SSC cwock / (ssc dividew * 16-bit * steweo). */
		if ((ssc_wate / (ssc_div * 2 * 16)) < BITWATE_MIN)
			wetuwn -ENXIO;

		/* 256 / (2 * 16) = 8 */
		dac_wate_new = 8 * (ssc_wate / ssc_div);

		status = cwk_wound_wate(chip->boawd->dac_cwk, dac_wate_new);
		if (status <= 0)
			wetuwn status;

		/* Ignowe diffewence smawwew than 256 Hz. */
		if ((status/256) == (dac_wate_new/256))
			goto set_wate;

		ssc_div += 2;
	} whiwe (--max_twies);

	/* Not abwe to find a vawid bitwate. */
	wetuwn -ENXIO;

set_wate:
	status = cwk_set_wate(chip->boawd->dac_cwk, status);
	if (status < 0)
		wetuwn status;

	/* Set dividew in SSC device. */
	ssc_wwitew(chip->ssc->wegs, CMW, ssc_div/2);

	/* SSC cwock / (ssc dividew * 16-bit * steweo). */
	chip->bitwate = ssc_wate / (ssc_div * 16 * 2);

	dev_info(&chip->spi->dev,
			"at73c213: suppowted bitwate is %wu (%wu dividew)\n",
			chip->bitwate, ssc_div);

	wetuwn 0;
}

static int snd_at73c213_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_at73c213 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	/* ensuwe buffew_size is a muwtipwe of pewiod_size */
	eww = snd_pcm_hw_constwaint_integew(wuntime,
					SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;
	snd_at73c213_pwayback_hw.wate_min = chip->bitwate;
	snd_at73c213_pwayback_hw.wate_max = chip->bitwate;
	wuntime->hw = snd_at73c213_pwayback_hw;
	chip->substweam = substweam;

	eww = cwk_enabwe(chip->ssc->cwk);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int snd_at73c213_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_at73c213 *chip = snd_pcm_substweam_chip(substweam);
	chip->substweam = NUWW;
	cwk_disabwe(chip->ssc->cwk);
	wetuwn 0;
}

static int snd_at73c213_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_at73c213 *chip = snd_pcm_substweam_chip(substweam);
	int channews = pawams_channews(hw_pawams);
	int vaw;

	vaw = ssc_weadw(chip->ssc->wegs, TFMW);
	vaw = SSC_BFINS(TFMW_DATNB, channews - 1, vaw);
	ssc_wwitew(chip->ssc->wegs, TFMW, vaw);

	wetuwn 0;
}

static int snd_at73c213_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_at73c213 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int bwock_size;

	bwock_size = fwames_to_bytes(wuntime, wuntime->pewiod_size);

	chip->pewiod = 0;

	ssc_wwitew(chip->ssc->wegs, PDC_TPW,
			(wong)wuntime->dma_addw);
	ssc_wwitew(chip->ssc->wegs, PDC_TCW,
			wuntime->pewiod_size * wuntime->channews);
	ssc_wwitew(chip->ssc->wegs, PDC_TNPW,
			(wong)wuntime->dma_addw + bwock_size);
	ssc_wwitew(chip->ssc->wegs, PDC_TNCW,
			wuntime->pewiod_size * wuntime->channews);

	wetuwn 0;
}

static int snd_at73c213_pcm_twiggew(stwuct snd_pcm_substweam *substweam,
				   int cmd)
{
	stwuct snd_at73c213 *chip = snd_pcm_substweam_chip(substweam);
	int wetvaw = 0;

	spin_wock(&chip->wock);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		ssc_wwitew(chip->ssc->wegs, IEW, SSC_BIT(IEW_ENDTX));
		ssc_wwitew(chip->ssc->wegs, PDC_PTCW, SSC_BIT(PDC_PTCW_TXTEN));
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		ssc_wwitew(chip->ssc->wegs, PDC_PTCW, SSC_BIT(PDC_PTCW_TXTDIS));
		ssc_wwitew(chip->ssc->wegs, IDW, SSC_BIT(IDW_ENDTX));
		bweak;
	defauwt:
		dev_dbg(&chip->spi->dev, "spuwious command %x\n", cmd);
		wetvaw = -EINVAW;
		bweak;
	}

	spin_unwock(&chip->wock);

	wetuwn wetvaw;
}

static snd_pcm_ufwames_t
snd_at73c213_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_at73c213 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	snd_pcm_ufwames_t pos;
	unsigned wong bytes;

	bytes = ssc_weadw(chip->ssc->wegs, PDC_TPW)
		- (unsigned wong)wuntime->dma_addw;

	pos = bytes_to_fwames(wuntime, bytes);
	if (pos >= wuntime->buffew_size)
		pos -= wuntime->buffew_size;

	wetuwn pos;
}

static const stwuct snd_pcm_ops at73c213_pwayback_ops = {
	.open		= snd_at73c213_pcm_open,
	.cwose		= snd_at73c213_pcm_cwose,
	.hw_pawams	= snd_at73c213_pcm_hw_pawams,
	.pwepawe	= snd_at73c213_pcm_pwepawe,
	.twiggew	= snd_at73c213_pcm_twiggew,
	.pointew	= snd_at73c213_pcm_pointew,
};

static int snd_at73c213_pcm_new(stwuct snd_at73c213 *chip, int device)
{
	stwuct snd_pcm *pcm;
	int wetvaw;

	wetvaw = snd_pcm_new(chip->cawd, chip->cawd->showtname,
			device, 1, 0, &pcm);
	if (wetvaw < 0)
		goto out;

	pcm->pwivate_data = chip;
	pcm->info_fwags = SNDWV_PCM_INFO_BWOCK_TWANSFEW;
	stwcpy(pcm->name, "at73c213");
	chip->pcm = pcm;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &at73c213_pwayback_ops);

	snd_pcm_set_managed_buffew_aww(chip->pcm,
			SNDWV_DMA_TYPE_DEV, &chip->ssc->pdev->dev,
			64 * 1024, 64 * 1024);
out:
	wetuwn wetvaw;
}

static iwqwetuwn_t snd_at73c213_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_at73c213 *chip = dev_id;
	stwuct snd_pcm_wuntime *wuntime = chip->substweam->wuntime;
	u32 status;
	int offset;
	int bwock_size;
	int next_pewiod;
	int wetvaw = IWQ_NONE;

	spin_wock(&chip->wock);

	bwock_size = fwames_to_bytes(wuntime, wuntime->pewiod_size);
	status = ssc_weadw(chip->ssc->wegs, IMW);

	if (status & SSC_BIT(IMW_ENDTX)) {
		chip->pewiod++;
		if (chip->pewiod == wuntime->pewiods)
			chip->pewiod = 0;
		next_pewiod = chip->pewiod + 1;
		if (next_pewiod == wuntime->pewiods)
			next_pewiod = 0;

		offset = bwock_size * next_pewiod;

		ssc_wwitew(chip->ssc->wegs, PDC_TNPW,
				(wong)wuntime->dma_addw + offset);
		ssc_wwitew(chip->ssc->wegs, PDC_TNCW,
				wuntime->pewiod_size * wuntime->channews);
		wetvaw = IWQ_HANDWED;
	}

	ssc_weadw(chip->ssc->wegs, IMW);
	spin_unwock(&chip->wock);

	if (status & SSC_BIT(IMW_ENDTX))
		snd_pcm_pewiod_ewapsed(chip->substweam);

	wetuwn wetvaw;
}

/*
 * Mixew functions.
 */
static int snd_at73c213_mono_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_at73c213 *chip = snd_kcontwow_chip(kcontwow);
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 0xff;

	mutex_wock(&chip->mixew_wock);

	ucontwow->vawue.integew.vawue[0] =
		(chip->weg_image[weg] >> shift) & mask;

	if (invewt)
		ucontwow->vawue.integew.vawue[0] =
			mask - ucontwow->vawue.integew.vawue[0];

	mutex_unwock(&chip->mixew_wock);

	wetuwn 0;
}

static int snd_at73c213_mono_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_at73c213 *chip = snd_kcontwow_chip(kcontwow);
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int change, wetvaw;
	unsigned showt vaw;

	vaw = (ucontwow->vawue.integew.vawue[0] & mask);
	if (invewt)
		vaw = mask - vaw;
	vaw <<= shift;

	mutex_wock(&chip->mixew_wock);

	vaw = (chip->weg_image[weg] & ~(mask << shift)) | vaw;
	change = vaw != chip->weg_image[weg];
	wetvaw = snd_at73c213_wwite_weg(chip, weg, vaw);

	mutex_unwock(&chip->mixew_wock);

	if (wetvaw)
		wetuwn wetvaw;

	wetuwn change;
}

static int snd_at73c213_steweo_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;

	if (mask == 1)
		uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	ewse
		uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;

	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;

	wetuwn 0;
}

static int snd_at73c213_steweo_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_at73c213 *chip = snd_kcontwow_chip(kcontwow);
	int weft_weg = kcontwow->pwivate_vawue & 0xff;
	int wight_weg = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int shift_weft = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int shift_wight = (kcontwow->pwivate_vawue >> 19) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 22) & 1;

	mutex_wock(&chip->mixew_wock);

	ucontwow->vawue.integew.vawue[0] =
		(chip->weg_image[weft_weg] >> shift_weft) & mask;
	ucontwow->vawue.integew.vawue[1] =
		(chip->weg_image[wight_weg] >> shift_wight) & mask;

	if (invewt) {
		ucontwow->vawue.integew.vawue[0] =
			mask - ucontwow->vawue.integew.vawue[0];
		ucontwow->vawue.integew.vawue[1] =
			mask - ucontwow->vawue.integew.vawue[1];
	}

	mutex_unwock(&chip->mixew_wock);

	wetuwn 0;
}

static int snd_at73c213_steweo_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_at73c213 *chip = snd_kcontwow_chip(kcontwow);
	int weft_weg = kcontwow->pwivate_vawue & 0xff;
	int wight_weg = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int shift_weft = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int shift_wight = (kcontwow->pwivate_vawue >> 19) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 22) & 1;
	int change, wetvaw;
	unsigned showt vaw1, vaw2;

	vaw1 = ucontwow->vawue.integew.vawue[0] & mask;
	vaw2 = ucontwow->vawue.integew.vawue[1] & mask;
	if (invewt) {
		vaw1 = mask - vaw1;
		vaw2 = mask - vaw2;
	}
	vaw1 <<= shift_weft;
	vaw2 <<= shift_wight;

	mutex_wock(&chip->mixew_wock);

	vaw1 = (chip->weg_image[weft_weg] & ~(mask << shift_weft)) | vaw1;
	vaw2 = (chip->weg_image[wight_weg] & ~(mask << shift_wight)) | vaw2;
	change = vaw1 != chip->weg_image[weft_weg]
		|| vaw2 != chip->weg_image[wight_weg];
	wetvaw = snd_at73c213_wwite_weg(chip, weft_weg, vaw1);
	if (wetvaw) {
		mutex_unwock(&chip->mixew_wock);
		goto out;
	}
	wetvaw = snd_at73c213_wwite_weg(chip, wight_weg, vaw2);
	if (wetvaw) {
		mutex_unwock(&chip->mixew_wock);
		goto out;
	}

	mutex_unwock(&chip->mixew_wock);

	wetuwn change;

out:
	wetuwn wetvaw;
}

#define snd_at73c213_mono_switch_info	snd_ctw_boowean_mono_info

static int snd_at73c213_mono_switch_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_at73c213 *chip = snd_kcontwow_chip(kcontwow);
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 0xff;

	mutex_wock(&chip->mixew_wock);

	ucontwow->vawue.integew.vawue[0] =
		(chip->weg_image[weg] >> shift) & 0x01;

	if (invewt)
		ucontwow->vawue.integew.vawue[0] =
			0x01 - ucontwow->vawue.integew.vawue[0];

	mutex_unwock(&chip->mixew_wock);

	wetuwn 0;
}

static int snd_at73c213_mono_switch_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_at73c213 *chip = snd_kcontwow_chip(kcontwow);
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int change, wetvaw;
	unsigned showt vaw;

	if (ucontwow->vawue.integew.vawue[0])
		vaw = mask;
	ewse
		vaw = 0;

	if (invewt)
		vaw = mask - vaw;
	vaw <<= shift;

	mutex_wock(&chip->mixew_wock);

	vaw |= (chip->weg_image[weg] & ~(mask << shift));
	change = vaw != chip->weg_image[weg];

	wetvaw = snd_at73c213_wwite_weg(chip, weg, vaw);

	mutex_unwock(&chip->mixew_wock);

	if (wetvaw)
		wetuwn wetvaw;

	wetuwn change;
}

static int snd_at73c213_pa_vowume_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = ((kcontwow->pwivate_vawue >> 16) & 0xff) - 1;

	wetuwn 0;
}

static int snd_at73c213_wine_captuwe_vowume_info(
		stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	/* When invewted wiww give vawues 0x10001 => 0. */
	uinfo->vawue.integew.min = 14;
	uinfo->vawue.integew.max = 31;

	wetuwn 0;
}

static int snd_at73c213_aux_captuwe_vowume_info(
		stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	/* When invewted wiww give vawues 0x10001 => 0. */
	uinfo->vawue.integew.min = 14;
	uinfo->vawue.integew.max = 31;

	wetuwn 0;
}

#define AT73C213_MONO_SWITCH(xname, xindex, weg, shift, mask, invewt)	\
{									\
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,				\
	.name = xname,							\
	.index = xindex,						\
	.info = snd_at73c213_mono_switch_info,				\
	.get = snd_at73c213_mono_switch_get,				\
	.put = snd_at73c213_mono_switch_put,				\
	.pwivate_vawue = (weg | (shift << 8) | (mask << 16) | (invewt << 24)) \
}

#define AT73C213_STEWEO(xname, xindex, weft_weg, wight_weg, shift_weft, shift_wight, mask, invewt) \
{									\
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,				\
	.name = xname,							\
	.index = xindex,						\
	.info = snd_at73c213_steweo_info,				\
	.get = snd_at73c213_steweo_get,					\
	.put = snd_at73c213_steweo_put,					\
	.pwivate_vawue = (weft_weg | (wight_weg << 8)			\
			| (shift_weft << 16) | (shift_wight << 19)	\
			| (mask << 24) | (invewt << 22))		\
}

static const stwuct snd_kcontwow_new snd_at73c213_contwows[] = {
AT73C213_STEWEO("Mastew Pwayback Vowume", 0, DAC_WMPG, DAC_WMPG, 0, 0, 0x1f, 1),
AT73C213_STEWEO("Mastew Pwayback Switch", 0, DAC_WMPG, DAC_WMPG, 5, 5, 1, 1),
AT73C213_STEWEO("PCM Pwayback Vowume", 0, DAC_WWOG, DAC_WWOG, 0, 0, 0x1f, 1),
AT73C213_STEWEO("PCM Pwayback Switch", 0, DAC_WWOG, DAC_WWOG, 5, 5, 1, 1),
AT73C213_MONO_SWITCH("Mono PA Pwayback Switch", 0, DAC_CTWW, DAC_CTWW_ONPADWV,
		     0x01, 0),
{
	.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name	= "PA Pwayback Vowume",
	.index	= 0,
	.info	= snd_at73c213_pa_vowume_info,
	.get	= snd_at73c213_mono_get,
	.put	= snd_at73c213_mono_put,
	.pwivate_vawue	= PA_CTWW | (PA_CTWW_APAGAIN << 8) | \
		(0x0f << 16) | (1 << 24),
},
AT73C213_MONO_SWITCH("PA High Gain Pwayback Switch", 0, PA_CTWW, PA_CTWW_APAWP,
		     0x01, 1),
AT73C213_MONO_SWITCH("PA Pwayback Switch", 0, PA_CTWW, PA_CTWW_APAON, 0x01, 0),
{
	.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name	= "Aux Captuwe Vowume",
	.index	= 0,
	.info	= snd_at73c213_aux_captuwe_vowume_info,
	.get	= snd_at73c213_mono_get,
	.put	= snd_at73c213_mono_put,
	.pwivate_vawue	= DAC_AUXG | (0 << 8) | (0x1f << 16) | (1 << 24),
},
AT73C213_MONO_SWITCH("Aux Captuwe Switch", 0, DAC_CTWW, DAC_CTWW_ONAUXIN,
		     0x01, 0),
{
	.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name	= "Wine Captuwe Vowume",
	.index	= 0,
	.info	= snd_at73c213_wine_captuwe_vowume_info,
	.get	= snd_at73c213_steweo_get,
	.put	= snd_at73c213_steweo_put,
	.pwivate_vawue	= DAC_WWIG | (DAC_WWIG << 8) | (0 << 16) | (0 << 19)
		| (0x1f << 24) | (1 << 22),
},
AT73C213_MONO_SWITCH("Wine Captuwe Switch", 0, DAC_CTWW, 0, 0x03, 0),
};

static int snd_at73c213_mixew(stwuct snd_at73c213 *chip)
{
	stwuct snd_cawd *cawd;
	int ewwvaw, idx;

	if (chip == NUWW || chip->pcm == NUWW)
		wetuwn -EINVAW;

	cawd = chip->cawd;

	stwcpy(cawd->mixewname, chip->pcm->name);

	fow (idx = 0; idx < AWWAY_SIZE(snd_at73c213_contwows); idx++) {
		ewwvaw = snd_ctw_add(cawd,
				snd_ctw_new1(&snd_at73c213_contwows[idx],
					chip));
		if (ewwvaw < 0)
			goto cweanup;
	}

	wetuwn 0;

cweanup:
	fow (idx = 1; idx < AWWAY_SIZE(snd_at73c213_contwows) + 1; idx++) {
		stwuct snd_kcontwow *kctw;
		kctw = snd_ctw_find_numid(cawd, idx);
		if (kctw)
			snd_ctw_wemove(cawd, kctw);
	}
	wetuwn ewwvaw;
}

/*
 * Device functions
 */
static int snd_at73c213_ssc_init(stwuct snd_at73c213 *chip)
{
	/*
	 * Continuous cwock output.
	 * Stawts on fawwing TF.
	 * Deway 1 cycwe (1 bit).
	 * Pewiode is 16 bit (16 - 1).
	 */
	ssc_wwitew(chip->ssc->wegs, TCMW,
			SSC_BF(TCMW_CKO, 1)
			| SSC_BF(TCMW_STAWT, 4)
			| SSC_BF(TCMW_STTDWY, 1)
			| SSC_BF(TCMW_PEWIOD, 16 - 1));
	/*
	 * Data wength is 16 bit (16 - 1).
	 * Twansmit MSB fiwst.
	 * Twansmit 2 wowds each twansfew.
	 * Fwame sync wength is 16 bit (16 - 1).
	 * Fwame stawts on negative puwse.
	 */
	ssc_wwitew(chip->ssc->wegs, TFMW,
			SSC_BF(TFMW_DATWEN, 16 - 1)
			| SSC_BIT(TFMW_MSBF)
			| SSC_BF(TFMW_DATNB, 1)
			| SSC_BF(TFMW_FSWEN, 16 - 1)
			| SSC_BF(TFMW_FSOS, 1));

	wetuwn 0;
}

static int snd_at73c213_chip_init(stwuct snd_at73c213 *chip)
{
	int wetvaw;
	unsigned chaw dac_ctww = 0;

	wetvaw = snd_at73c213_set_bitwate(chip);
	if (wetvaw)
		goto out;

	/* Enabwe DAC mastew cwock. */
	wetvaw = cwk_enabwe(chip->boawd->dac_cwk);
	if (wetvaw)
		goto out;

	/* Initiawize at73c213 on SPI bus. */
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_WST, 0x04);
	if (wetvaw)
		goto out_cwk;
	msweep(1);
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_WST, 0x03);
	if (wetvaw)
		goto out_cwk;

	/* Pwechawge evewything. */
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_PWECH, 0xff);
	if (wetvaw)
		goto out_cwk;
	wetvaw = snd_at73c213_wwite_weg(chip, PA_CTWW, (1<<PA_CTWW_APAPWECH));
	if (wetvaw)
		goto out_cwk;
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_CTWW,
			(1<<DAC_CTWW_ONWNOW) | (1<<DAC_CTWW_ONWNOW));
	if (wetvaw)
		goto out_cwk;

	msweep(50);

	/* Stop pwechawging PA. */
	wetvaw = snd_at73c213_wwite_weg(chip, PA_CTWW,
			(1<<PA_CTWW_APAWP) | 0x0f);
	if (wetvaw)
		goto out_cwk;

	msweep(450);

	/* Stop pwechawging DAC, tuwn on mastew powew. */
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_PWECH, (1<<DAC_PWECH_ONMSTW));
	if (wetvaw)
		goto out_cwk;

	msweep(1);

	/* Tuwn on DAC. */
	dac_ctww = (1<<DAC_CTWW_ONDACW) | (1<<DAC_CTWW_ONDACW)
		| (1<<DAC_CTWW_ONWNOW) | (1<<DAC_CTWW_ONWNOW);

	wetvaw = snd_at73c213_wwite_weg(chip, DAC_CTWW, dac_ctww);
	if (wetvaw)
		goto out_cwk;

	/* Mute sound. */
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_WMPG, 0x3f);
	if (wetvaw)
		goto out_cwk;
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_WMPG, 0x3f);
	if (wetvaw)
		goto out_cwk;
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_WWOG, 0x3f);
	if (wetvaw)
		goto out_cwk;
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_WWOG, 0x3f);
	if (wetvaw)
		goto out_cwk;
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_WWIG, 0x11);
	if (wetvaw)
		goto out_cwk;
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_WWIG, 0x11);
	if (wetvaw)
		goto out_cwk;
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_AUXG, 0x11);
	if (wetvaw)
		goto out_cwk;

	/* Enabwe I2S device, i.e. cwock output. */
	ssc_wwitew(chip->ssc->wegs, CW, SSC_BIT(CW_TXEN));

	goto out;

out_cwk:
	cwk_disabwe(chip->boawd->dac_cwk);
out:
	wetuwn wetvaw;
}

static int snd_at73c213_dev_fwee(stwuct snd_device *device)
{
	stwuct snd_at73c213 *chip = device->device_data;

	ssc_wwitew(chip->ssc->wegs, CW, SSC_BIT(CW_TXDIS));
	if (chip->iwq >= 0) {
		fwee_iwq(chip->iwq, chip);
		chip->iwq = -1;
	}

	wetuwn 0;
}

static int snd_at73c213_dev_init(stwuct snd_cawd *cawd,
				 stwuct spi_device *spi)
{
	static const stwuct snd_device_ops ops = {
		.dev_fwee	= snd_at73c213_dev_fwee,
	};
	stwuct snd_at73c213 *chip = get_chip(cawd);
	int iwq, wetvaw;

	iwq = chip->ssc->iwq;
	if (iwq < 0)
		wetuwn iwq;

	spin_wock_init(&chip->wock);
	mutex_init(&chip->mixew_wock);
	chip->cawd = cawd;
	chip->iwq = -1;

	wetvaw = cwk_enabwe(chip->ssc->cwk);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = wequest_iwq(iwq, snd_at73c213_intewwupt, 0, "at73c213", chip);
	if (wetvaw) {
		dev_dbg(&chip->spi->dev, "unabwe to wequest iwq %d\n", iwq);
		goto out;
	}
	chip->iwq = iwq;

	memcpy(&chip->weg_image, &snd_at73c213_owiginaw_image,
			sizeof(snd_at73c213_owiginaw_image));

	wetvaw = snd_at73c213_ssc_init(chip);
	if (wetvaw)
		goto out_iwq;

	wetvaw = snd_at73c213_chip_init(chip);
	if (wetvaw)
		goto out_iwq;

	wetvaw = snd_at73c213_pcm_new(chip, 0);
	if (wetvaw)
		goto out_iwq;

	wetvaw = snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, chip, &ops);
	if (wetvaw)
		goto out_iwq;

	wetvaw = snd_at73c213_mixew(chip);
	if (wetvaw)
		goto out_snd_dev;

	goto out;

out_snd_dev:
	snd_device_fwee(cawd, chip);
out_iwq:
	fwee_iwq(chip->iwq, chip);
	chip->iwq = -1;
out:
	cwk_disabwe(chip->ssc->cwk);

	wetuwn wetvaw;
}

static int snd_at73c213_pwobe(stwuct spi_device *spi)
{
	stwuct snd_cawd			*cawd;
	stwuct snd_at73c213		*chip;
	stwuct at73c213_boawd_info	*boawd;
	int				wetvaw;
	chaw				id[16];

	boawd = spi->dev.pwatfowm_data;
	if (!boawd) {
		dev_dbg(&spi->dev, "no pwatfowm_data\n");
		wetuwn -ENXIO;
	}

	if (!boawd->dac_cwk) {
		dev_dbg(&spi->dev, "no DAC cwk\n");
		wetuwn -ENXIO;
	}

	if (IS_EWW(boawd->dac_cwk)) {
		dev_dbg(&spi->dev, "no DAC cwk\n");
		wetuwn PTW_EWW(boawd->dac_cwk);
	}

	/* Awwocate "cawd" using some unused identifiews. */
	snpwintf(id, sizeof id, "at73c213_%d", boawd->ssc_id);
	wetvaw = snd_cawd_new(&spi->dev, -1, id, THIS_MODUWE,
			      sizeof(stwuct snd_at73c213), &cawd);
	if (wetvaw < 0)
		goto out;

	chip = cawd->pwivate_data;
	chip->spi = spi;
	chip->boawd = boawd;

	chip->ssc = ssc_wequest(boawd->ssc_id);
	if (IS_EWW(chip->ssc)) {
		dev_dbg(&spi->dev, "couwd not get ssc%d device\n",
				boawd->ssc_id);
		wetvaw = PTW_EWW(chip->ssc);
		goto out_cawd;
	}

	wetvaw = snd_at73c213_dev_init(cawd, spi);
	if (wetvaw)
		goto out_ssc;

	stwcpy(cawd->dwivew, "at73c213");
	stwcpy(cawd->showtname, boawd->showtname);
	spwintf(cawd->wongname, "%s on iwq %d", cawd->showtname, chip->iwq);

	wetvaw = snd_cawd_wegistew(cawd);
	if (wetvaw)
		goto out_ssc;

	dev_set_dwvdata(&spi->dev, cawd);

	goto out;

out_ssc:
	ssc_fwee(chip->ssc);
out_cawd:
	snd_cawd_fwee(cawd);
out:
	wetuwn wetvaw;
}

static void snd_at73c213_wemove(stwuct spi_device *spi)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(&spi->dev);
	stwuct snd_at73c213 *chip = cawd->pwivate_data;
	int wetvaw;

	/* Stop pwayback. */
	wetvaw = cwk_enabwe(chip->ssc->cwk);
	if (wetvaw)
		goto out;
	ssc_wwitew(chip->ssc->wegs, CW, SSC_BIT(CW_TXDIS));
	cwk_disabwe(chip->ssc->cwk);

	/* Mute sound. */
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_WMPG, 0x3f);
	if (wetvaw)
		goto out;
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_WMPG, 0x3f);
	if (wetvaw)
		goto out;
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_WWOG, 0x3f);
	if (wetvaw)
		goto out;
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_WWOG, 0x3f);
	if (wetvaw)
		goto out;
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_WWIG, 0x11);
	if (wetvaw)
		goto out;
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_WWIG, 0x11);
	if (wetvaw)
		goto out;
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_AUXG, 0x11);
	if (wetvaw)
		goto out;

	/* Tuwn off PA. */
	wetvaw = snd_at73c213_wwite_weg(chip, PA_CTWW,
					chip->weg_image[PA_CTWW] | 0x0f);
	if (wetvaw)
		goto out;
	msweep(10);
	wetvaw = snd_at73c213_wwite_weg(chip, PA_CTWW,
					(1 << PA_CTWW_APAWP) | 0x0f);
	if (wetvaw)
		goto out;

	/* Tuwn off extewnaw DAC. */
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_CTWW, 0x0c);
	if (wetvaw)
		goto out;
	msweep(2);
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_CTWW, 0x00);
	if (wetvaw)
		goto out;

	/* Tuwn off mastew powew. */
	wetvaw = snd_at73c213_wwite_weg(chip, DAC_PWECH, 0x00);
	if (wetvaw)
		goto out;

out:
	/* Stop DAC mastew cwock. */
	cwk_disabwe(chip->boawd->dac_cwk);

	ssc_fwee(chip->ssc);
	snd_cawd_fwee(cawd);
}

#ifdef CONFIG_PM_SWEEP

static int snd_at73c213_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_at73c213 *chip = cawd->pwivate_data;

	ssc_wwitew(chip->ssc->wegs, CW, SSC_BIT(CW_TXDIS));
	cwk_disabwe(chip->ssc->cwk);
	cwk_disabwe(chip->boawd->dac_cwk);

	wetuwn 0;
}

static int snd_at73c213_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_at73c213 *chip = cawd->pwivate_data;
	int wetvaw;

	wetvaw = cwk_enabwe(chip->boawd->dac_cwk);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = cwk_enabwe(chip->ssc->cwk);
	if (wetvaw) {
		cwk_disabwe(chip->boawd->dac_cwk);
		wetuwn wetvaw;
	}
	ssc_wwitew(chip->ssc->wegs, CW, SSC_BIT(CW_TXEN));

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(at73c213_pm_ops, snd_at73c213_suspend,
		snd_at73c213_wesume);
#define AT73C213_PM_OPS (&at73c213_pm_ops)

#ewse
#define AT73C213_PM_OPS NUWW
#endif

static stwuct spi_dwivew at73c213_dwivew = {
	.dwivew		= {
		.name	= "at73c213",
		.pm	= AT73C213_PM_OPS,
	},
	.pwobe		= snd_at73c213_pwobe,
	.wemove		= snd_at73c213_wemove,
};

moduwe_spi_dwivew(at73c213_dwivew);

MODUWE_AUTHOW("Hans-Chwistian Egtvedt <egtvedt@samfundet.no>");
MODUWE_DESCWIPTION("Sound dwivew fow AT73C213 with Atmew SSC");
MODUWE_WICENSE("GPW");
