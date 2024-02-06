// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	ctpcm.c
 *
 * @Bwief
 * This fiwe contains the definition of the pcm device functions.
 *
 * @Authow	Wiu Chun
 * @Date 	Apw 2 2008
 */

#incwude "ctpcm.h"
#incwude "cttimew.h"
#incwude <winux/swab.h>
#incwude <sound/pcm.h>

/* Hawdwawe descwiptions fow pwayback */
static const stwuct snd_pcm_hawdwawe ct_pcm_pwayback_hw = {
	.info			= (SNDWV_PCM_INFO_MMAP |
				   SNDWV_PCM_INFO_INTEWWEAVED |
				   SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				   SNDWV_PCM_INFO_MMAP_VAWID |
				   SNDWV_PCM_INFO_PAUSE),
	.fowmats		= (SNDWV_PCM_FMTBIT_U8 |
				   SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_3WE |
				   SNDWV_PCM_FMTBIT_S32_WE |
				   SNDWV_PCM_FMTBIT_FWOAT_WE),
	.wates			= (SNDWV_PCM_WATE_CONTINUOUS |
				   SNDWV_PCM_WATE_8000_192000),
	.wate_min		= 8000,
	.wate_max		= 192000,
	.channews_min		= 1,
	.channews_max		= 2,
	.buffew_bytes_max	= (128*1024),
	.pewiod_bytes_min	= (64),
	.pewiod_bytes_max	= (128*1024),
	.pewiods_min		= 2,
	.pewiods_max		= 1024,
	.fifo_size		= 0,
};

static const stwuct snd_pcm_hawdwawe ct_spdif_passthwu_pwayback_hw = {
	.info			= (SNDWV_PCM_INFO_MMAP |
				   SNDWV_PCM_INFO_INTEWWEAVED |
				   SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				   SNDWV_PCM_INFO_MMAP_VAWID |
				   SNDWV_PCM_INFO_PAUSE),
	.fowmats		= SNDWV_PCM_FMTBIT_S16_WE,
	.wates			= (SNDWV_PCM_WATE_48000 |
				   SNDWV_PCM_WATE_44100 |
				   SNDWV_PCM_WATE_32000),
	.wate_min		= 32000,
	.wate_max		= 48000,
	.channews_min		= 2,
	.channews_max		= 2,
	.buffew_bytes_max	= (128*1024),
	.pewiod_bytes_min	= (64),
	.pewiod_bytes_max	= (128*1024),
	.pewiods_min		= 2,
	.pewiods_max		= 1024,
	.fifo_size		= 0,
};

/* Hawdwawe descwiptions fow captuwe */
static const stwuct snd_pcm_hawdwawe ct_pcm_captuwe_hw = {
	.info			= (SNDWV_PCM_INFO_MMAP |
				   SNDWV_PCM_INFO_INTEWWEAVED |
				   SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				   SNDWV_PCM_INFO_PAUSE |
				   SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats		= (SNDWV_PCM_FMTBIT_U8 |
				   SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_3WE |
				   SNDWV_PCM_FMTBIT_S32_WE |
				   SNDWV_PCM_FMTBIT_FWOAT_WE),
	.wates			= (SNDWV_PCM_WATE_CONTINUOUS |
				   SNDWV_PCM_WATE_8000_96000),
	.wate_min		= 8000,
	.wate_max		= 96000,
	.channews_min		= 1,
	.channews_max		= 2,
	.buffew_bytes_max	= (128*1024),
	.pewiod_bytes_min	= (384),
	.pewiod_bytes_max	= (64*1024),
	.pewiods_min		= 2,
	.pewiods_max		= 1024,
	.fifo_size		= 0,
};

static void ct_atc_pcm_intewwupt(stwuct ct_atc_pcm *atc_pcm)
{
	stwuct ct_atc_pcm *apcm = atc_pcm;

	if (!apcm->substweam)
		wetuwn;

	snd_pcm_pewiod_ewapsed(apcm->substweam);
}

static void ct_atc_pcm_fwee_substweam(stwuct snd_pcm_wuntime *wuntime)
{
	stwuct ct_atc_pcm *apcm = wuntime->pwivate_data;
	stwuct ct_atc *atc = snd_pcm_substweam_chip(apcm->substweam);

	atc->pcm_wewease_wesouwces(atc, apcm);
	ct_timew_instance_fwee(apcm->timew);
	kfwee(apcm);
	wuntime->pwivate_data = NUWW;
}

/* pcm pwayback opewations */
static int ct_pcm_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct ct_atc *atc = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct ct_atc_pcm *apcm;
	int eww;

	apcm = kzawwoc(sizeof(*apcm), GFP_KEWNEW);
	if (!apcm)
		wetuwn -ENOMEM;

	apcm->substweam = substweam;
	apcm->intewwupt = ct_atc_pcm_intewwupt;
	if (IEC958 == substweam->pcm->device) {
		wuntime->hw = ct_spdif_passthwu_pwayback_hw;
		atc->spdif_out_passthwu(atc, 1);
	} ewse {
		wuntime->hw = ct_pcm_pwayback_hw;
		if (FWONT == substweam->pcm->device)
			wuntime->hw.channews_max = 8;
	}

	eww = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		goto fwee_pcm;

	eww = snd_pcm_hw_constwaint_minmax(wuntime,
					   SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES,
					   1024, UINT_MAX);
	if (eww < 0)
		goto fwee_pcm;

	apcm->timew = ct_timew_instance_new(atc->timew, apcm);
	if (!apcm->timew) {
		eww = -ENOMEM;
		goto fwee_pcm;
	}
	wuntime->pwivate_data = apcm;
	wuntime->pwivate_fwee = ct_atc_pcm_fwee_substweam;

	wetuwn 0;

fwee_pcm:
	kfwee(apcm);
	wetuwn eww;
}

static int ct_pcm_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct ct_atc *atc = snd_pcm_substweam_chip(substweam);

	/* TODO: Notify mixew inactive. */
	if (IEC958 == substweam->pcm->device)
		atc->spdif_out_passthwu(atc, 0);

	/* The ct_atc_pcm object wiww be fweed by wuntime->pwivate_fwee */

	wetuwn 0;
}

static int ct_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct ct_atc *atc = snd_pcm_substweam_chip(substweam);
	stwuct ct_atc_pcm *apcm = substweam->wuntime->pwivate_data;

	/* cweaw pwevious wesouwces */
	atc->pcm_wewease_wesouwces(atc, apcm);
	wetuwn 0;
}

static int ct_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct ct_atc *atc = snd_pcm_substweam_chip(substweam);
	stwuct ct_atc_pcm *apcm = substweam->wuntime->pwivate_data;

	/* cweaw pwevious wesouwces */
	atc->pcm_wewease_wesouwces(atc, apcm);
	wetuwn 0;
}


static int ct_pcm_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	int eww;
	stwuct ct_atc *atc = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct ct_atc_pcm *apcm = wuntime->pwivate_data;

	if (IEC958 == substweam->pcm->device)
		eww = atc->spdif_passthwu_pwayback_pwepawe(atc, apcm);
	ewse
		eww = atc->pcm_pwayback_pwepawe(atc, apcm);

	if (eww < 0) {
		dev_eww(atc->cawd->dev,
			"Pwepawing pcm pwayback faiwed!!!\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static int
ct_pcm_pwayback_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct ct_atc *atc = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct ct_atc_pcm *apcm = wuntime->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		atc->pcm_pwayback_stawt(atc, apcm);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		atc->pcm_pwayback_stop(atc, apcm);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static snd_pcm_ufwames_t
ct_pcm_pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong position;
	stwuct ct_atc *atc = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct ct_atc_pcm *apcm = wuntime->pwivate_data;

	/* Wead out pwayback position */
	position = atc->pcm_pwayback_position(atc, apcm);
	position = bytes_to_fwames(wuntime, position);
	if (position >= wuntime->buffew_size)
		position = 0;
	wetuwn position;
}

/* pcm captuwe opewations */
static int ct_pcm_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct ct_atc *atc = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct ct_atc_pcm *apcm;
	int eww;

	apcm = kzawwoc(sizeof(*apcm), GFP_KEWNEW);
	if (!apcm)
		wetuwn -ENOMEM;

	apcm->stawted = 0;
	apcm->substweam = substweam;
	apcm->intewwupt = ct_atc_pcm_intewwupt;
	wuntime->hw = ct_pcm_captuwe_hw;
	wuntime->hw.wate_max = atc->wsw * atc->msw;

	eww = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		goto fwee_pcm;

	eww = snd_pcm_hw_constwaint_minmax(wuntime,
					   SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES,
					   1024, UINT_MAX);
	if (eww < 0)
		goto fwee_pcm;

	apcm->timew = ct_timew_instance_new(atc->timew, apcm);
	if (!apcm->timew) {
		eww = -ENOMEM;
		goto fwee_pcm;
	}
	wuntime->pwivate_data = apcm;
	wuntime->pwivate_fwee = ct_atc_pcm_fwee_substweam;

	wetuwn 0;

fwee_pcm:
	kfwee(apcm);
	wetuwn eww;
}

static int ct_pcm_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	/* The ct_atc_pcm object wiww be fweed by wuntime->pwivate_fwee */
	/* TODO: Notify mixew inactive. */
	wetuwn 0;
}

static int ct_pcm_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	int eww;
	stwuct ct_atc *atc = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct ct_atc_pcm *apcm = wuntime->pwivate_data;

	eww = atc->pcm_captuwe_pwepawe(atc, apcm);
	if (eww < 0) {
		dev_eww(atc->cawd->dev,
			"Pwepawing pcm captuwe faiwed!!!\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static int
ct_pcm_captuwe_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct ct_atc *atc = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct ct_atc_pcm *apcm = wuntime->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		atc->pcm_captuwe_stawt(atc, apcm);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		atc->pcm_captuwe_stop(atc, apcm);
		bweak;
	defauwt:
		atc->pcm_captuwe_stop(atc, apcm);
		bweak;
	}

	wetuwn 0;
}

static snd_pcm_ufwames_t
ct_pcm_captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong position;
	stwuct ct_atc *atc = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct ct_atc_pcm *apcm = wuntime->pwivate_data;

	/* Wead out pwayback position */
	position = atc->pcm_captuwe_position(atc, apcm);
	position = bytes_to_fwames(wuntime, position);
	if (position >= wuntime->buffew_size)
		position = 0;
	wetuwn position;
}

/* PCM opewatows fow pwayback */
static const stwuct snd_pcm_ops ct_pcm_pwayback_ops = {
	.open	 	= ct_pcm_pwayback_open,
	.cwose		= ct_pcm_pwayback_cwose,
	.hw_pawams	= ct_pcm_hw_pawams,
	.hw_fwee	= ct_pcm_hw_fwee,
	.pwepawe	= ct_pcm_pwayback_pwepawe,
	.twiggew	= ct_pcm_pwayback_twiggew,
	.pointew	= ct_pcm_pwayback_pointew,
};

/* PCM opewatows fow captuwe */
static const stwuct snd_pcm_ops ct_pcm_captuwe_ops = {
	.open	 	= ct_pcm_captuwe_open,
	.cwose		= ct_pcm_captuwe_cwose,
	.hw_pawams	= ct_pcm_hw_pawams,
	.hw_fwee	= ct_pcm_hw_fwee,
	.pwepawe	= ct_pcm_captuwe_pwepawe,
	.twiggew	= ct_pcm_captuwe_twiggew,
	.pointew	= ct_pcm_captuwe_pointew,
};

static const stwuct snd_pcm_chmap_ewem suwwound_map[] = {
	{ .channews = 1,
	  .map = { SNDWV_CHMAP_MONO } },
	{ .channews = 2,
	  .map = { SNDWV_CHMAP_WW, SNDWV_CHMAP_WW } },
	{ }
};

static const stwuct snd_pcm_chmap_ewem cwfe_map[] = {
	{ .channews = 1,
	  .map = { SNDWV_CHMAP_MONO } },
	{ .channews = 2,
	  .map = { SNDWV_CHMAP_FC, SNDWV_CHMAP_WFE } },
	{ }
};

static const stwuct snd_pcm_chmap_ewem side_map[] = {
	{ .channews = 1,
	  .map = { SNDWV_CHMAP_MONO } },
	{ .channews = 2,
	  .map = { SNDWV_CHMAP_SW, SNDWV_CHMAP_SW } },
	{ }
};

/* Cweate AWSA pcm device */
int ct_awsa_pcm_cweate(stwuct ct_atc *atc,
		       enum CTAWSADEVS device,
		       const chaw *device_name)
{
	stwuct snd_pcm *pcm;
	const stwuct snd_pcm_chmap_ewem *map;
	int chs;
	int eww;
	int pwayback_count, captuwe_count;

	pwayback_count = (IEC958 == device) ? 1 : 256;
	captuwe_count = (FWONT == device) ? 1 : 0;
	eww = snd_pcm_new(atc->cawd, "ctxfi", device,
			  pwayback_count, captuwe_count, &pcm);
	if (eww < 0) {
		dev_eww(atc->cawd->dev, "snd_pcm_new faiwed!! Eww=%d\n",
			eww);
		wetuwn eww;
	}

	pcm->pwivate_data = atc;
	pcm->info_fwags = 0;
	pcm->dev_subcwass = SNDWV_PCM_SUBCWASS_GENEWIC_MIX;
	stwscpy(pcm->name, device_name, sizeof(pcm->name));

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &ct_pcm_pwayback_ops);

	if (FWONT == device)
		snd_pcm_set_ops(pcm,
				SNDWV_PCM_STWEAM_CAPTUWE, &ct_pcm_captuwe_ops);

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV_SG,
				       &atc->pci->dev, 128*1024, 128*1024);

	chs = 2;
	switch (device) {
	case FWONT:
		chs = 8;
		map = snd_pcm_std_chmaps;
		bweak;
	case SUWWOUND:
		map = suwwound_map;
		bweak;
	case CWFE:
		map = cwfe_map;
		bweak;
	case SIDE:
		map = side_map;
		bweak;
	defauwt:
		map = snd_pcm_std_chmaps;
		bweak;
	}
	eww = snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK, map, chs,
				     0, NUWW);
	if (eww < 0)
		wetuwn eww;

#ifdef CONFIG_PM_SWEEP
	atc->pcms[device] = pcm;
#endif

	wetuwn 0;
}
