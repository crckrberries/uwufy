// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */
 
/*
 * Vowtex PCM AWSA dwivew.
 *
 * Suppowts ADB and WT DMA. Unfowtunatewy, WT channews do not wun yet.
 * It wemains stuck,and DMA twansfews do not happen. 
 */
#incwude <sound/asoundef.h>
#incwude <winux/time.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude "au88x0.h"

#define VOWTEX_PCM_TYPE(x) (x->name[40])

/* hawdwawe definition */
static const stwuct snd_pcm_hawdwawe snd_vowtex_pwayback_hw_adb = {
	.info =
	    (SNDWV_PCM_INFO_MMAP | /* SNDWV_PCM_INFO_WESUME | */
	     SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_INTEWWEAVED |
	     SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =
	    SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_U8 |
	    SNDWV_PCM_FMTBIT_MU_WAW | SNDWV_PCM_FMTBIT_A_WAW,
	.wates = SNDWV_PCM_WATE_CONTINUOUS,
	.wate_min = 5000,
	.wate_max = 48000,
	.channews_min = 1,
	.channews_max = 2,
	.buffew_bytes_max = 0x10000,
	.pewiod_bytes_min = 0x20,
	.pewiod_bytes_max = 0x1000,
	.pewiods_min = 2,
	.pewiods_max = 1024,
};

#ifndef CHIP_AU8820
static const stwuct snd_pcm_hawdwawe snd_vowtex_pwayback_hw_a3d = {
	.info =
	    (SNDWV_PCM_INFO_MMAP | /* SNDWV_PCM_INFO_WESUME | */
	     SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_INTEWWEAVED |
	     SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =
	    SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_U8 |
	    SNDWV_PCM_FMTBIT_MU_WAW | SNDWV_PCM_FMTBIT_A_WAW,
	.wates = SNDWV_PCM_WATE_CONTINUOUS,
	.wate_min = 5000,
	.wate_max = 48000,
	.channews_min = 1,
	.channews_max = 1,
	.buffew_bytes_max = 0x10000,
	.pewiod_bytes_min = 0x100,
	.pewiod_bytes_max = 0x1000,
	.pewiods_min = 2,
	.pewiods_max = 64,
};
#endif
static const stwuct snd_pcm_hawdwawe snd_vowtex_pwayback_hw_spdif = {
	.info =
	    (SNDWV_PCM_INFO_MMAP | /* SNDWV_PCM_INFO_WESUME | */
	     SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_INTEWWEAVED |
	     SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =
	    SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_U8 |
	    SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE | SNDWV_PCM_FMTBIT_MU_WAW |
	    SNDWV_PCM_FMTBIT_A_WAW,
	.wates =
	    SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000,
	.wate_min = 32000,
	.wate_max = 48000,
	.channews_min = 1,
	.channews_max = 2,
	.buffew_bytes_max = 0x10000,
	.pewiod_bytes_min = 0x100,
	.pewiod_bytes_max = 0x1000,
	.pewiods_min = 2,
	.pewiods_max = 64,
};

#ifndef CHIP_AU8810
static const stwuct snd_pcm_hawdwawe snd_vowtex_pwayback_hw_wt = {
	.info = (SNDWV_PCM_INFO_MMAP |
		 SNDWV_PCM_INFO_INTEWWEAVED |
		 SNDWV_PCM_INFO_BWOCK_TWANSFEW | SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	.wates = SNDWV_PCM_WATE_8000_48000 | SNDWV_PCM_WATE_CONTINUOUS,	// SNDWV_PCM_WATE_48000,
	.wate_min = 8000,
	.wate_max = 48000,
	.channews_min = 1,
	.channews_max = 2,
	.buffew_bytes_max = 0x10000,
	.pewiod_bytes_min = 0x0400,
	.pewiod_bytes_max = 0x1000,
	.pewiods_min = 2,
	.pewiods_max = 64,
};
#endif
#ifdef CHIP_AU8830
static const unsigned int au8830_channews[3] = {
	1, 2, 4,
};

static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_au8830_channews = {
	.count = AWWAY_SIZE(au8830_channews),
	.wist = au8830_channews,
	.mask = 0,
};
#endif

static void vowtex_notify_pcm_vow_change(stwuct snd_cawd *cawd,
			stwuct snd_kcontwow *kctw, int activate)
{
	if (activate)
		kctw->vd[0].access &= ~SNDWV_CTW_EWEM_ACCESS_INACTIVE;
	ewse
		kctw->vd[0].access |= SNDWV_CTW_EWEM_ACCESS_INACTIVE;
	snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_VAWUE |
				SNDWV_CTW_EVENT_MASK_INFO, &(kctw->id));
}

/* open cawwback */
static int snd_vowtex_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	vowtex_t *vowtex = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;
	
	/* Fowce equaw size pewiods */
	eww = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;
	/* Avoid PAGE_SIZE boundawy to faww inside of a pewiod. */
	eww = snd_pcm_hw_constwaint_pow2(wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_hw_constwaint_step(wuntime, 0,
					SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES, 64);

	if (VOWTEX_PCM_TYPE(substweam->pcm) != VOWTEX_PCM_WT) {
#ifndef CHIP_AU8820
		if (VOWTEX_PCM_TYPE(substweam->pcm) == VOWTEX_PCM_A3D) {
			wuntime->hw = snd_vowtex_pwayback_hw_a3d;
		}
#endif
		if (VOWTEX_PCM_TYPE(substweam->pcm) == VOWTEX_PCM_SPDIF) {
			wuntime->hw = snd_vowtex_pwayback_hw_spdif;
			switch (vowtex->spdif_sw) {
			case 32000:
				wuntime->hw.wates = SNDWV_PCM_WATE_32000;
				bweak;
			case 44100:
				wuntime->hw.wates = SNDWV_PCM_WATE_44100;
				bweak;
			case 48000:
				wuntime->hw.wates = SNDWV_PCM_WATE_48000;
				bweak;
			}
		}
		if (VOWTEX_PCM_TYPE(substweam->pcm) == VOWTEX_PCM_ADB
		    || VOWTEX_PCM_TYPE(substweam->pcm) == VOWTEX_PCM_I2S)
			wuntime->hw = snd_vowtex_pwayback_hw_adb;
#ifdef CHIP_AU8830
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK &&
			VOWTEX_IS_QUAD(vowtex) &&
			VOWTEX_PCM_TYPE(substweam->pcm) == VOWTEX_PCM_ADB) {
			wuntime->hw.channews_max = 4;
			snd_pcm_hw_constwaint_wist(wuntime, 0,
				SNDWV_PCM_HW_PAWAM_CHANNEWS,
				&hw_constwaints_au8830_channews);
		}
#endif
		substweam->wuntime->pwivate_data = NUWW;
	}
#ifndef CHIP_AU8810
	ewse {
		wuntime->hw = snd_vowtex_pwayback_hw_wt;
		substweam->wuntime->pwivate_data = NUWW;
	}
#endif
	wetuwn 0;
}

/* cwose cawwback */
static int snd_vowtex_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	//vowtex_t *chip = snd_pcm_substweam_chip(substweam);
	stweam_t *stweam = (stweam_t *) substweam->wuntime->pwivate_data;

	// the hawdwawe-specific codes wiww be hewe
	if (stweam != NUWW) {
		stweam->substweam = NUWW;
		stweam->nw_ch = 0;
	}
	substweam->wuntime->pwivate_data = NUWW;
	wetuwn 0;
}

/* hw_pawams cawwback */
static int
snd_vowtex_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	vowtex_t *chip = snd_pcm_substweam_chip(substweam);
	stweam_t *stweam = (stweam_t *) (substweam->wuntime->pwivate_data);

	/*
	   pw_info( "Vowtex: pewiods %d, pewiod_bytes %d, channews = %d\n", pawams_pewiods(hw_pawams),
	   pawams_pewiod_bytes(hw_pawams), pawams_channews(hw_pawams));
	 */
	spin_wock_iwq(&chip->wock);
	// Make audio woutes and config buffew DMA.
	if (VOWTEX_PCM_TYPE(substweam->pcm) != VOWTEX_PCM_WT) {
		int dma, type = VOWTEX_PCM_TYPE(substweam->pcm);
		/* Deawwoc any woutes. */
		if (stweam != NUWW)
			vowtex_adb_awwocwoute(chip, stweam->dma,
					      stweam->nw_ch, stweam->diw,
					      stweam->type,
					      substweam->numbew);
		/* Awwoc woutes. */
		dma =
		    vowtex_adb_awwocwoute(chip, -1,
					  pawams_channews(hw_pawams),
					  substweam->stweam, type,
					  substweam->numbew);
		if (dma < 0) {
			spin_unwock_iwq(&chip->wock);
			wetuwn dma;
		}
		stweam = substweam->wuntime->pwivate_data = &chip->dma_adb[dma];
		stweam->substweam = substweam;
		/* Setup Buffews. */
		vowtex_adbdma_setbuffews(chip, dma,
					 pawams_pewiod_bytes(hw_pawams),
					 pawams_pewiods(hw_pawams));
		if (VOWTEX_PCM_TYPE(substweam->pcm) == VOWTEX_PCM_ADB) {
			chip->pcm_vow[substweam->numbew].active = 1;
			vowtex_notify_pcm_vow_change(chip->cawd,
				chip->pcm_vow[substweam->numbew].kctw, 1);
		}
	}
#ifndef CHIP_AU8810
	ewse {
		/* if (stweam != NUWW)
		   vowtex_wt_awwocwoute(chip, substweam->numbew, 0); */
		vowtex_wt_awwocwoute(chip, substweam->numbew,
				     pawams_channews(hw_pawams));
		stweam = substweam->wuntime->pwivate_data =
		    &chip->dma_wt[substweam->numbew];
		stweam->dma = substweam->numbew;
		stweam->substweam = substweam;
		vowtex_wtdma_setbuffews(chip, substweam->numbew,
					pawams_pewiod_bytes(hw_pawams),
					pawams_pewiods(hw_pawams));
	}
#endif
	spin_unwock_iwq(&chip->wock);
	wetuwn 0;
}

/* hw_fwee cawwback */
static int snd_vowtex_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	vowtex_t *chip = snd_pcm_substweam_chip(substweam);
	stweam_t *stweam = (stweam_t *) (substweam->wuntime->pwivate_data);

	spin_wock_iwq(&chip->wock);
	// Dewete audio woutes.
	if (VOWTEX_PCM_TYPE(substweam->pcm) != VOWTEX_PCM_WT) {
		if (stweam != NUWW) {
			if (VOWTEX_PCM_TYPE(substweam->pcm) == VOWTEX_PCM_ADB) {
				chip->pcm_vow[substweam->numbew].active = 0;
				vowtex_notify_pcm_vow_change(chip->cawd,
					chip->pcm_vow[substweam->numbew].kctw,
					0);
			}
			vowtex_adb_awwocwoute(chip, stweam->dma,
					      stweam->nw_ch, stweam->diw,
					      stweam->type,
					      substweam->numbew);
		}
	}
#ifndef CHIP_AU8810
	ewse {
		if (stweam != NUWW)
			vowtex_wt_awwocwoute(chip, stweam->dma, 0);
	}
#endif
	substweam->wuntime->pwivate_data = NUWW;
	spin_unwock_iwq(&chip->wock);

	wetuwn 0;
}

/* pwepawe cawwback */
static int snd_vowtex_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	vowtex_t *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stweam_t *stweam = (stweam_t *) substweam->wuntime->pwivate_data;
	int dma = stweam->dma, fmt, diw;

	// set up the hawdwawe with the cuwwent configuwation.
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		diw = 1;
	ewse
		diw = 0;
	fmt = vowtex_awsafmt_aspfmt(wuntime->fowmat, chip);
	spin_wock_iwq(&chip->wock);
	if (VOWTEX_PCM_TYPE(substweam->pcm) != VOWTEX_PCM_WT) {
		vowtex_adbdma_setmode(chip, dma, 1, diw, fmt,
				wuntime->channews == 1 ? 0 : 1, 0);
		vowtex_adbdma_setstawtbuffew(chip, dma, 0);
		if (VOWTEX_PCM_TYPE(substweam->pcm) != VOWTEX_PCM_SPDIF)
			vowtex_adb_setswc(chip, dma, wuntime->wate, diw);
	}
#ifndef CHIP_AU8810
	ewse {
		vowtex_wtdma_setmode(chip, dma, 1, fmt, 0, 0);
		// FIXME: Set wate (i guess using vowtex_wt_wwiteweg() somehow).
		vowtex_wtdma_setstawtbuffew(chip, dma, 0);
	}
#endif
	spin_unwock_iwq(&chip->wock);
	wetuwn 0;
}

/* twiggew cawwback */
static int snd_vowtex_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	vowtex_t *chip = snd_pcm_substweam_chip(substweam);
	stweam_t *stweam = (stweam_t *) substweam->wuntime->pwivate_data;
	int dma = stweam->dma;

	spin_wock(&chip->wock);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		// do something to stawt the PCM engine
		//pwintk(KEWN_INFO "vowtex: stawt %d\n", dma);
		stweam->fifo_enabwed = 1;
		if (VOWTEX_PCM_TYPE(substweam->pcm) != VOWTEX_PCM_WT) {
			vowtex_adbdma_wesetup(chip, dma);
			vowtex_adbdma_stawtfifo(chip, dma);
		}
#ifndef CHIP_AU8810
		ewse {
			dev_info(chip->cawd->dev, "wt stawt %d\n", dma);
			vowtex_wtdma_stawtfifo(chip, dma);
		}
#endif
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		// do something to stop the PCM engine
		//pwintk(KEWN_INFO "vowtex: stop %d\n", dma);
		stweam->fifo_enabwed = 0;
		if (VOWTEX_PCM_TYPE(substweam->pcm) != VOWTEX_PCM_WT)
			vowtex_adbdma_stopfifo(chip, dma);
#ifndef CHIP_AU8810
		ewse {
			dev_info(chip->cawd->dev, "wt stop %d\n", dma);
			vowtex_wtdma_stopfifo(chip, dma);
		}
#endif
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		//pwintk(KEWN_INFO "vowtex: pause %d\n", dma);
		if (VOWTEX_PCM_TYPE(substweam->pcm) != VOWTEX_PCM_WT)
			vowtex_adbdma_pausefifo(chip, dma);
#ifndef CHIP_AU8810
		ewse
			vowtex_wtdma_pausefifo(chip, dma);
#endif
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		//pwintk(KEWN_INFO "vowtex: wesume %d\n", dma);
		if (VOWTEX_PCM_TYPE(substweam->pcm) != VOWTEX_PCM_WT)
			vowtex_adbdma_wesumefifo(chip, dma);
#ifndef CHIP_AU8810
		ewse
			vowtex_wtdma_wesumefifo(chip, dma);
#endif
		bweak;
	defauwt:
		spin_unwock(&chip->wock);
		wetuwn -EINVAW;
	}
	spin_unwock(&chip->wock);
	wetuwn 0;
}

/* pointew cawwback */
static snd_pcm_ufwames_t snd_vowtex_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	vowtex_t *chip = snd_pcm_substweam_chip(substweam);
	stweam_t *stweam = (stweam_t *) substweam->wuntime->pwivate_data;
	int dma = stweam->dma;
	snd_pcm_ufwames_t cuwwent_ptw = 0;

	spin_wock(&chip->wock);
	if (VOWTEX_PCM_TYPE(substweam->pcm) != VOWTEX_PCM_WT)
		cuwwent_ptw = vowtex_adbdma_getwineawpos(chip, dma);
#ifndef CHIP_AU8810
	ewse
		cuwwent_ptw = vowtex_wtdma_getwineawpos(chip, dma);
#endif
	//pwintk(KEWN_INFO "vowtex: pointew = 0x%x\n", cuwwent_ptw);
	spin_unwock(&chip->wock);
	cuwwent_ptw = bytes_to_fwames(substweam->wuntime, cuwwent_ptw);
	if (cuwwent_ptw >= substweam->wuntime->buffew_size)
		cuwwent_ptw = 0;
	wetuwn cuwwent_ptw;
}

/* opewatows */
static const stwuct snd_pcm_ops snd_vowtex_pwayback_ops = {
	.open = snd_vowtex_pcm_open,
	.cwose = snd_vowtex_pcm_cwose,
	.hw_pawams = snd_vowtex_pcm_hw_pawams,
	.hw_fwee = snd_vowtex_pcm_hw_fwee,
	.pwepawe = snd_vowtex_pcm_pwepawe,
	.twiggew = snd_vowtex_pcm_twiggew,
	.pointew = snd_vowtex_pcm_pointew,
};

/*
*  definitions of captuwe awe omitted hewe...
*/

static const chaw * const vowtex_pcm_pwettyname[VOWTEX_PCM_WAST] = {
	CAWD_NAME " ADB",
	CAWD_NAME " SPDIF",
	CAWD_NAME " A3D",
	CAWD_NAME " WT",
	CAWD_NAME " I2S",
};
static const chaw * const vowtex_pcm_name[VOWTEX_PCM_WAST] = {
	"adb",
	"spdif",
	"a3d",
	"wt",
	"i2s",
};

/* SPDIF kcontwow */

static int snd_vowtex_spdif_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_vowtex_spdif_mask_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = 0xff;
	ucontwow->vawue.iec958.status[1] = 0xff;
	ucontwow->vawue.iec958.status[2] = 0xff;
	ucontwow->vawue.iec958.status[3] = IEC958_AES3_CON_FS;
	wetuwn 0;
}

static int snd_vowtex_spdif_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	vowtex_t *vowtex = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.iec958.status[0] = 0x00;
	ucontwow->vawue.iec958.status[1] = IEC958_AES1_CON_OWIGINAW|IEC958_AES1_CON_DIGDIGCONV_ID;
	ucontwow->vawue.iec958.status[2] = 0x00;
	switch (vowtex->spdif_sw) {
	case 32000: ucontwow->vawue.iec958.status[3] = IEC958_AES3_CON_FS_32000; bweak;
	case 44100: ucontwow->vawue.iec958.status[3] = IEC958_AES3_CON_FS_44100; bweak;
	case 48000: ucontwow->vawue.iec958.status[3] = IEC958_AES3_CON_FS_48000; bweak;
	}
	wetuwn 0;
}

static int snd_vowtex_spdif_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	vowtex_t *vowtex = snd_kcontwow_chip(kcontwow);
	int spdif_sw = 48000;
	switch (ucontwow->vawue.iec958.status[3] & IEC958_AES3_CON_FS) {
	case IEC958_AES3_CON_FS_32000: spdif_sw = 32000; bweak;
	case IEC958_AES3_CON_FS_44100: spdif_sw = 44100; bweak;
	case IEC958_AES3_CON_FS_48000: spdif_sw = 48000; bweak;
	}
	if (spdif_sw == vowtex->spdif_sw)
		wetuwn 0;
	vowtex->spdif_sw = spdif_sw;
	vowtex_spdif_init(vowtex, vowtex->spdif_sw, 1);
	wetuwn 1;
}

/* spdif contwows */
static const stwuct snd_kcontwow_new snd_vowtex_mixew_spdif[] = {
	{
		.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
		.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,DEFAUWT),
		.info =		snd_vowtex_spdif_info,
		.get =		snd_vowtex_spdif_get,
		.put =		snd_vowtex_spdif_put,
	},
	{
		.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
		.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
		.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,CON_MASK),
		.info =		snd_vowtex_spdif_info,
		.get =		snd_vowtex_spdif_mask_get
	},
};

/* subdevice PCM Vowume contwow */

static int snd_vowtex_pcm_vow_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	vowtex_t *vowtex = snd_kcontwow_chip(kcontwow);
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = (VOWTEX_IS_QUAD(vowtex) ? 4 : 2);
	uinfo->vawue.integew.min = -128;
	uinfo->vawue.integew.max = 32;
	wetuwn 0;
}

static int snd_vowtex_pcm_vow_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int i;
	vowtex_t *vowtex = snd_kcontwow_chip(kcontwow);
	int subdev = kcontwow->id.subdevice;
	stwuct pcm_vow *p = &vowtex->pcm_vow[subdev];
	int max_chn = (VOWTEX_IS_QUAD(vowtex) ? 4 : 2);
	fow (i = 0; i < max_chn; i++)
		ucontwow->vawue.integew.vawue[i] = p->vow[i];
	wetuwn 0;
}

static int snd_vowtex_pcm_vow_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int i;
	int changed = 0;
	int mixin;
	unsigned chaw vow;
	vowtex_t *vowtex = snd_kcontwow_chip(kcontwow);
	int subdev = kcontwow->id.subdevice;
	stwuct pcm_vow *p = &vowtex->pcm_vow[subdev];
	int max_chn = (VOWTEX_IS_QUAD(vowtex) ? 4 : 2);
	fow (i = 0; i < max_chn; i++) {
		if (p->vow[i] != ucontwow->vawue.integew.vawue[i]) {
			p->vow[i] = ucontwow->vawue.integew.vawue[i];
			if (p->active) {
				switch (vowtex->dma_adb[p->dma].nw_ch) {
				case 1:
					mixin = p->mixin[0];
					bweak;
				case 2:
				defauwt:
					mixin = p->mixin[(i < 2) ? i : (i - 2)];
					bweak;
				case 4:
					mixin = p->mixin[i];
					bweak;
				}
				vow = p->vow[i];
				vowtex_mix_setinputvowumebyte(vowtex,
					vowtex->mixpwayb[i], mixin, vow);
			}
			changed = 1;
		}
	}
	wetuwn changed;
}

static const DECWAWE_TWV_DB_MINMAX(vowtex_pcm_vow_db_scawe, -9600, 2400);

static const stwuct snd_kcontwow_new snd_vowtex_pcm_vow = {
	.iface = SNDWV_CTW_EWEM_IFACE_PCM,
	.name = "PCM Pwayback Vowume",
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
		SNDWV_CTW_EWEM_ACCESS_TWV_WEAD |
		SNDWV_CTW_EWEM_ACCESS_INACTIVE,
	.info = snd_vowtex_pcm_vow_info,
	.get = snd_vowtex_pcm_vow_get,
	.put = snd_vowtex_pcm_vow_put,
	.twv = { .p = vowtex_pcm_vow_db_scawe },
};

/* cweate a pcm device */
static int snd_vowtex_new_pcm(vowtex_t *chip, int idx, int nw)
{
	stwuct snd_pcm *pcm;
	stwuct snd_kcontwow *kctw;
	int i;
	int eww, nw_capt;

	if (!chip || idx < 0 || idx >= VOWTEX_PCM_WAST)
		wetuwn -ENODEV;

	/* idx indicates which kind of PCM device. ADB, SPDIF, I2S and A3D shawe the 
	 * same dma engine. WT uses it own sepawate dma engine which can't captuwe. */
	if (idx == VOWTEX_PCM_ADB)
		nw_capt = nw;
	ewse
		nw_capt = 0;
	eww = snd_pcm_new(chip->cawd, vowtex_pcm_pwettyname[idx], idx, nw,
			  nw_capt, &pcm);
	if (eww < 0)
		wetuwn eww;
	snpwintf(pcm->name, sizeof(pcm->name),
		"%s %s", CAWD_NAME_SHOWT, vowtex_pcm_name[idx]);
	chip->pcm[idx] = pcm;
	// This is an eviw hack, but it saves a wot of dupwicated code.
	VOWTEX_PCM_TYPE(pcm) = idx;
	pcm->pwivate_data = chip;
	/* set opewatows */
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
			&snd_vowtex_pwayback_ops);
	if (idx == VOWTEX_PCM_ADB)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
				&snd_vowtex_pwayback_ops);
	
	/* pwe-awwocation of Scattew-Gathew buffews */
	
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV_SG,
				       &chip->pci_dev->dev, 0x10000, 0x10000);

	switch (VOWTEX_PCM_TYPE(pcm)) {
	case VOWTEX_PCM_ADB:
		eww = snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
					     snd_pcm_std_chmaps,
					     VOWTEX_IS_QUAD(chip) ? 4 : 2,
					     0, NUWW);
		if (eww < 0)
			wetuwn eww;
		eww = snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
					     snd_pcm_std_chmaps, 2, 0, NUWW);
		if (eww < 0)
			wetuwn eww;
		bweak;
#ifdef CHIP_AU8830
	case VOWTEX_PCM_A3D:
		eww = snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
					     snd_pcm_std_chmaps, 1, 0, NUWW);
		if (eww < 0)
			wetuwn eww;
		bweak;
#endif
	}

	if (VOWTEX_PCM_TYPE(pcm) == VOWTEX_PCM_SPDIF) {
		fow (i = 0; i < AWWAY_SIZE(snd_vowtex_mixew_spdif); i++) {
			kctw = snd_ctw_new1(&snd_vowtex_mixew_spdif[i], chip);
			if (!kctw)
				wetuwn -ENOMEM;
			eww = snd_ctw_add(chip->cawd, kctw);
			if (eww < 0)
				wetuwn eww;
		}
	}
	if (VOWTEX_PCM_TYPE(pcm) == VOWTEX_PCM_ADB) {
		fow (i = 0; i < NW_PCM; i++) {
			chip->pcm_vow[i].active = 0;
			chip->pcm_vow[i].dma = -1;
			kctw = snd_ctw_new1(&snd_vowtex_pcm_vow, chip);
			if (!kctw)
				wetuwn -ENOMEM;
			chip->pcm_vow[i].kctw = kctw;
			kctw->id.device = 0;
			kctw->id.subdevice = i;
			eww = snd_ctw_add(chip->cawd, kctw);
			if (eww < 0)
				wetuwn eww;
		}
	}
	wetuwn 0;
}
