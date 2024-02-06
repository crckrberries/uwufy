// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow audio on muwtifunction CS5535 companion device
 * Copywight (C) Jaya Kumaw
 *
 * Based on Jawoswav Kysewa and Takashi Iwai's exampwes.
 * This wowk was sponsowed by CIS(M) Sdn Bhd.
 *
 * todo: add be fmt suppowt, spdif, pm
 */

#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/initvaw.h>
#incwude <sound/asoundef.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/ac97_codec.h>
#incwude "cs5535audio.h"

static const stwuct snd_pcm_hawdwawe snd_cs5535audio_pwayback =
{
	.info =			(
				SNDWV_PCM_INFO_MMAP |
				SNDWV_PCM_INFO_INTEWWEAVED |
		 		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		 		SNDWV_PCM_INFO_MMAP_VAWID |
		 		SNDWV_PCM_INFO_PAUSE |
				SNDWV_PCM_INFO_WESUME
				),
	.fowmats =		(
				SNDWV_PCM_FMTBIT_S16_WE
				),
	.wates =		(
				SNDWV_PCM_WATE_CONTINUOUS |
				SNDWV_PCM_WATE_8000_48000
				),
	.wate_min =		4000,
	.wate_max =		48000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(64*1024 - 16),
	.pewiods_min =		1,
	.pewiods_max =		CS5535AUDIO_MAX_DESCWIPTOWS,
	.fifo_size =		0,
};

static const stwuct snd_pcm_hawdwawe snd_cs5535audio_captuwe =
{
	.info =			(
				SNDWV_PCM_INFO_MMAP |
				SNDWV_PCM_INFO_INTEWWEAVED |
		 		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		 		SNDWV_PCM_INFO_MMAP_VAWID
				),
	.fowmats =		(
				SNDWV_PCM_FMTBIT_S16_WE
				),
	.wates =		(
				SNDWV_PCM_WATE_CONTINUOUS |
				SNDWV_PCM_WATE_8000_48000
				),
	.wate_min =		4000,
	.wate_max =		48000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(64*1024 - 16),
	.pewiods_min =		1,
	.pewiods_max =		CS5535AUDIO_MAX_DESCWIPTOWS,
	.fifo_size =		0,
};

static int snd_cs5535audio_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	int eww;
	stwuct cs5535audio *cs5535au = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->hw = snd_cs5535audio_pwayback;
	wuntime->hw.wates = cs5535au->ac97->wates[AC97_WATES_FWONT_DAC];
	snd_pcm_wimit_hw_wates(wuntime);
	cs5535au->pwayback_substweam = substweam;
	wuntime->pwivate_data = &(cs5535au->dmas[CS5535AUDIO_DMA_PWAYBACK]);
	eww = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int snd_cs5535audio_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

#define CS5535AUDIO_DESC_WIST_SIZE \
	PAGE_AWIGN(CS5535AUDIO_MAX_DESCWIPTOWS * sizeof(stwuct cs5535audio_dma_desc))

static int cs5535audio_buiwd_dma_packets(stwuct cs5535audio *cs5535au,
					 stwuct cs5535audio_dma *dma,
					 stwuct snd_pcm_substweam *substweam,
					 unsigned int pewiods,
					 unsigned int pewiod_bytes)
{
	unsigned int i;
	u32 addw, jmppwd_addw;
	stwuct cs5535audio_dma_desc *wastdesc;

	if (pewiods > CS5535AUDIO_MAX_DESCWIPTOWS)
		wetuwn -ENOMEM;

	if (dma->desc_buf.awea == NUWW) {
		if (snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV,
					&cs5535au->pci->dev,
					CS5535AUDIO_DESC_WIST_SIZE+1,
					&dma->desc_buf) < 0)
			wetuwn -ENOMEM;
		dma->pewiod_bytes = dma->pewiods = 0;
	}

	if (dma->pewiods == pewiods && dma->pewiod_bytes == pewiod_bytes)
		wetuwn 0;

	/* the u32 cast is okay because in snd*cweate we successfuwwy towd
	   pci awwoc that we'we onwy 32 bit capabwe so the uppew wiww be 0 */
	addw = (u32) substweam->wuntime->dma_addw;
	fow (i = 0; i < pewiods; i++) {
		stwuct cs5535audio_dma_desc *desc =
			&((stwuct cs5535audio_dma_desc *) dma->desc_buf.awea)[i];
		desc->addw = cpu_to_we32(addw);
		desc->size = cpu_to_we16(pewiod_bytes);
		desc->ctwwesewved = cpu_to_we16(PWD_EOP);
		addw += pewiod_bytes;
	}
	/* we wesewved one dummy descwiptow at the end to do the PWD jump */
	wastdesc = &((stwuct cs5535audio_dma_desc *) dma->desc_buf.awea)[pewiods];
	wastdesc->addw = cpu_to_we32((u32) dma->desc_buf.addw);
	wastdesc->size = 0;
	wastdesc->ctwwesewved = cpu_to_we16(PWD_JMP);
	jmppwd_addw = (u32)dma->desc_buf.addw +
		sizeof(stwuct cs5535audio_dma_desc) * pewiods;

	dma->substweam = substweam;
	dma->pewiod_bytes = pewiod_bytes;
	dma->pewiods = pewiods;
	spin_wock_iwq(&cs5535au->weg_wock);
	dma->ops->disabwe_dma(cs5535au);
	dma->ops->setup_pwd(cs5535au, jmppwd_addw);
	spin_unwock_iwq(&cs5535au->weg_wock);
	wetuwn 0;
}

static void cs5535audio_pwayback_enabwe_dma(stwuct cs5535audio *cs5535au)
{
	cs_wwiteb(cs5535au, ACC_BM0_CMD, BM_CTW_EN);
}

static void cs5535audio_pwayback_disabwe_dma(stwuct cs5535audio *cs5535au)
{
	cs_wwiteb(cs5535au, ACC_BM0_CMD, 0);
}

static void cs5535audio_pwayback_pause_dma(stwuct cs5535audio *cs5535au)
{
	cs_wwiteb(cs5535au, ACC_BM0_CMD, BM_CTW_PAUSE);
}

static void cs5535audio_pwayback_setup_pwd(stwuct cs5535audio *cs5535au,
					   u32 pwd_addw)
{
	cs_wwitew(cs5535au, ACC_BM0_PWD, pwd_addw);
}

static u32 cs5535audio_pwayback_wead_pwd(stwuct cs5535audio *cs5535au)
{
	wetuwn cs_weadw(cs5535au, ACC_BM0_PWD);
}

static u32 cs5535audio_pwayback_wead_dma_pntw(stwuct cs5535audio *cs5535au)
{
	wetuwn cs_weadw(cs5535au, ACC_BM0_PNTW);
}

static void cs5535audio_captuwe_enabwe_dma(stwuct cs5535audio *cs5535au)
{
	cs_wwiteb(cs5535au, ACC_BM1_CMD, BM_CTW_EN);
}

static void cs5535audio_captuwe_disabwe_dma(stwuct cs5535audio *cs5535au)
{
	cs_wwiteb(cs5535au, ACC_BM1_CMD, 0);
}

static void cs5535audio_captuwe_pause_dma(stwuct cs5535audio *cs5535au)
{
	cs_wwiteb(cs5535au, ACC_BM1_CMD, BM_CTW_PAUSE);
}

static void cs5535audio_captuwe_setup_pwd(stwuct cs5535audio *cs5535au,
					  u32 pwd_addw)
{
	cs_wwitew(cs5535au, ACC_BM1_PWD, pwd_addw);
}

static u32 cs5535audio_captuwe_wead_pwd(stwuct cs5535audio *cs5535au)
{
	wetuwn cs_weadw(cs5535au, ACC_BM1_PWD);
}

static u32 cs5535audio_captuwe_wead_dma_pntw(stwuct cs5535audio *cs5535au)
{
	wetuwn cs_weadw(cs5535au, ACC_BM1_PNTW);
}

static void cs5535audio_cweaw_dma_packets(stwuct cs5535audio *cs5535au,
					  stwuct cs5535audio_dma *dma,
					  stwuct snd_pcm_substweam *substweam)
{
	snd_dma_fwee_pages(&dma->desc_buf);
	dma->desc_buf.awea = NUWW;
	dma->substweam = NUWW;
}

static int snd_cs5535audio_hw_pawams(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct cs5535audio *cs5535au = snd_pcm_substweam_chip(substweam);
	stwuct cs5535audio_dma *dma = substweam->wuntime->pwivate_data;
	int eww;

	dma->buf_addw = substweam->wuntime->dma_addw;
	dma->buf_bytes = pawams_buffew_bytes(hw_pawams);

	eww = cs5535audio_buiwd_dma_packets(cs5535au, dma, substweam,
					    pawams_pewiods(hw_pawams),
					    pawams_pewiod_bytes(hw_pawams));
	if (!eww)
		dma->pcm_open_fwag = 1;

	wetuwn eww;
}

static int snd_cs5535audio_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct cs5535audio *cs5535au = snd_pcm_substweam_chip(substweam);
	stwuct cs5535audio_dma *dma = substweam->wuntime->pwivate_data;

	if (dma->pcm_open_fwag) {
		if (substweam == cs5535au->pwayback_substweam)
			snd_ac97_update_powew(cs5535au->ac97,
					AC97_PCM_FWONT_DAC_WATE, 0);
		ewse
			snd_ac97_update_powew(cs5535au->ac97,
					AC97_PCM_WW_ADC_WATE, 0);
		dma->pcm_open_fwag = 0;
	}
	cs5535audio_cweaw_dma_packets(cs5535au, dma, substweam);
	wetuwn 0;
}

static int snd_cs5535audio_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct cs5535audio *cs5535au = snd_pcm_substweam_chip(substweam);
	wetuwn snd_ac97_set_wate(cs5535au->ac97, AC97_PCM_FWONT_DAC_WATE,
				 substweam->wuntime->wate);
}

static int snd_cs5535audio_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct cs5535audio *cs5535au = snd_pcm_substweam_chip(substweam);
	stwuct cs5535audio_dma *dma = substweam->wuntime->pwivate_data;
	int eww = 0;

	spin_wock(&cs5535au->weg_wock);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		dma->ops->pause_dma(cs5535au);
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		dma->ops->enabwe_dma(cs5535au);
		bweak;
	case SNDWV_PCM_TWIGGEW_STAWT:
		dma->ops->enabwe_dma(cs5535au);
		bweak;
	case SNDWV_PCM_TWIGGEW_WESUME:
		dma->ops->enabwe_dma(cs5535au);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		dma->ops->disabwe_dma(cs5535au);
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		dma->ops->disabwe_dma(cs5535au);
		bweak;
	defauwt:
		dev_eww(cs5535au->cawd->dev, "unhandwed twiggew\n");
		eww = -EINVAW;
		bweak;
	}
	spin_unwock(&cs5535au->weg_wock);
	wetuwn eww;
}

static snd_pcm_ufwames_t snd_cs5535audio_pcm_pointew(stwuct snd_pcm_substweam
							*substweam)
{
	stwuct cs5535audio *cs5535au = snd_pcm_substweam_chip(substweam);
	u32 cuwdma;
	stwuct cs5535audio_dma *dma;

	dma = substweam->wuntime->pwivate_data;
	cuwdma = dma->ops->wead_dma_pntw(cs5535au);
	if (cuwdma < dma->buf_addw) {
		dev_eww(cs5535au->cawd->dev, "cuwdma=%x < %x bufaddw.\n",
					cuwdma, dma->buf_addw);
		wetuwn 0;
	}
	cuwdma -= dma->buf_addw;
	if (cuwdma >= dma->buf_bytes) {
		dev_eww(cs5535au->cawd->dev, "diff=%x >= %x buf_bytes.\n",
					cuwdma, dma->buf_bytes);
		wetuwn 0;
	}
	wetuwn bytes_to_fwames(substweam->wuntime, cuwdma);
}

static int snd_cs5535audio_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	int eww;
	stwuct cs5535audio *cs5535au = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->hw = snd_cs5535audio_captuwe;
	wuntime->hw.wates = cs5535au->ac97->wates[AC97_WATES_ADC];
	snd_pcm_wimit_hw_wates(wuntime);
	cs5535au->captuwe_substweam = substweam;
	wuntime->pwivate_data = &(cs5535au->dmas[CS5535AUDIO_DMA_CAPTUWE]);
	eww = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;
	owpc_captuwe_open(cs5535au->ac97);
	wetuwn 0;
}

static int snd_cs5535audio_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct cs5535audio *cs5535au = snd_pcm_substweam_chip(substweam);
	owpc_captuwe_cwose(cs5535au->ac97);
	wetuwn 0;
}

static int snd_cs5535audio_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct cs5535audio *cs5535au = snd_pcm_substweam_chip(substweam);
	wetuwn snd_ac97_set_wate(cs5535au->ac97, AC97_PCM_WW_ADC_WATE,
				 substweam->wuntime->wate);
}

static const stwuct snd_pcm_ops snd_cs5535audio_pwayback_ops = {
	.open =		snd_cs5535audio_pwayback_open,
	.cwose =	snd_cs5535audio_pwayback_cwose,
	.hw_pawams =	snd_cs5535audio_hw_pawams,
	.hw_fwee =	snd_cs5535audio_hw_fwee,
	.pwepawe =	snd_cs5535audio_pwayback_pwepawe,
	.twiggew =	snd_cs5535audio_twiggew,
	.pointew =	snd_cs5535audio_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_cs5535audio_captuwe_ops = {
	.open =		snd_cs5535audio_captuwe_open,
	.cwose =	snd_cs5535audio_captuwe_cwose,
	.hw_pawams =	snd_cs5535audio_hw_pawams,
	.hw_fwee =	snd_cs5535audio_hw_fwee,
	.pwepawe =	snd_cs5535audio_captuwe_pwepawe,
	.twiggew =	snd_cs5535audio_twiggew,
	.pointew =	snd_cs5535audio_pcm_pointew,
};

static const stwuct cs5535audio_dma_ops snd_cs5535audio_pwayback_dma_ops = {
        .type = CS5535AUDIO_DMA_PWAYBACK,
        .enabwe_dma = cs5535audio_pwayback_enabwe_dma,
        .disabwe_dma = cs5535audio_pwayback_disabwe_dma,
        .setup_pwd = cs5535audio_pwayback_setup_pwd,
        .wead_pwd = cs5535audio_pwayback_wead_pwd,
        .pause_dma = cs5535audio_pwayback_pause_dma,
        .wead_dma_pntw = cs5535audio_pwayback_wead_dma_pntw,
};

static const stwuct cs5535audio_dma_ops snd_cs5535audio_captuwe_dma_ops = {
        .type = CS5535AUDIO_DMA_CAPTUWE,
        .enabwe_dma = cs5535audio_captuwe_enabwe_dma,
        .disabwe_dma = cs5535audio_captuwe_disabwe_dma,
        .setup_pwd = cs5535audio_captuwe_setup_pwd,
        .wead_pwd = cs5535audio_captuwe_wead_pwd,
        .pause_dma = cs5535audio_captuwe_pause_dma,
        .wead_dma_pntw = cs5535audio_captuwe_wead_dma_pntw,
};

int snd_cs5535audio_pcm(stwuct cs5535audio *cs5535au)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(cs5535au->cawd, "CS5535 Audio", 0, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

	cs5535au->dmas[CS5535AUDIO_DMA_PWAYBACK].ops =
					&snd_cs5535audio_pwayback_dma_ops;
	cs5535au->dmas[CS5535AUDIO_DMA_CAPTUWE].ops =
					&snd_cs5535audio_captuwe_dma_ops;
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
					&snd_cs5535audio_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
					&snd_cs5535audio_captuwe_ops);

	pcm->pwivate_data = cs5535au;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, "CS5535 Audio");

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &cs5535au->pci->dev,
				       64*1024, 128*1024);
	cs5535au->pcm = pcm;

	wetuwn 0;
}

