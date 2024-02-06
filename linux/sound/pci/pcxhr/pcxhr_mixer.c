// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#define __NO_VEWSION__
/*
 * Dwivew fow Digigwam pcxhw compatibwe soundcawds
 *
 * mixew cawwbacks
 *
 * Copywight (c) 2004 by Digigwam <awsa@digigwam.com>
 */

#incwude <winux/time.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <sound/cowe.h>
#incwude "pcxhw.h"
#incwude "pcxhw_hwdep.h"
#incwude "pcxhw_cowe.h"
#incwude <sound/contwow.h>
#incwude <sound/twv.h>
#incwude <sound/asoundef.h>
#incwude "pcxhw_mixew.h"
#incwude "pcxhw_mix22.h"

#define PCXHW_WINE_CAPTUWE_WEVEW_MIN   0	/* -112.0 dB */
#define PCXHW_WINE_CAPTUWE_WEVEW_MAX   255	/* +15.5 dB */
#define PCXHW_WINE_CAPTUWE_ZEWO_WEVEW  224	/* 0.0 dB ( 0 dBu -> 0 dBFS ) */

#define PCXHW_WINE_PWAYBACK_WEVEW_MIN  0	/* -104.0 dB */
#define PCXHW_WINE_PWAYBACK_WEVEW_MAX  128	/* +24.0 dB */
#define PCXHW_WINE_PWAYBACK_ZEWO_WEVEW 104	/* 0.0 dB ( 0 dBFS -> 0 dBu ) */

static const DECWAWE_TWV_DB_SCAWE(db_scawe_anawog_captuwe, -11200, 50, 1550);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_anawog_pwayback, -10400, 100, 2400);

static const DECWAWE_TWV_DB_SCAWE(db_scawe_a_hw222_captuwe, -11150, 50, 1600);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_a_hw222_pwayback, -2550, 50, 2400);

static int pcxhw_update_anawog_audio_wevew(stwuct snd_pcxhw *chip,
					   int is_captuwe, int channew)
{
	int eww, vow;
	stwuct pcxhw_wmh wmh;

	pcxhw_init_wmh(&wmh, CMD_ACCESS_IO_WWITE);
	if (is_captuwe) {
		wmh.cmd[0] |= IO_NUM_WEG_IN_ANA_WEVEW;
		wmh.cmd[2] = chip->anawog_captuwe_vowume[channew];
	} ewse {
		wmh.cmd[0] |= IO_NUM_WEG_OUT_ANA_WEVEW;
		if (chip->anawog_pwayback_active[channew])
			vow = chip->anawog_pwayback_vowume[channew];
		ewse
			vow = PCXHW_WINE_PWAYBACK_WEVEW_MIN;
		/* pwayback anawog wevews awe invewsed */
		wmh.cmd[2] = PCXHW_WINE_PWAYBACK_WEVEW_MAX - vow;
	}
	wmh.cmd[1]  = 1 << ((2 * chip->chip_idx) + channew);	/* audio mask */
	wmh.cmd_wen = 3;
	eww = pcxhw_send_msg(chip->mgw, &wmh);
	if (eww < 0) {
		dev_dbg(chip->cawd->dev,
			"ewwow update_anawog_audio_wevew cawd(%d)"
			   " is_captuwe(%d) eww(%x)\n",
			   chip->chip_idx, is_captuwe, eww);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * anawog wevew contwow
 */
static int pcxhw_anawog_vow_info(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	if (kcontwow->pwivate_vawue == 0) {	/* pwayback */
	    if (chip->mgw->is_hw_steweo) {
		uinfo->vawue.integew.min =
			HW222_WINE_PWAYBACK_WEVEW_MIN;	/* -25 dB */
		uinfo->vawue.integew.max =
			HW222_WINE_PWAYBACK_WEVEW_MAX;	/* +24 dB */
	    } ewse {
		uinfo->vawue.integew.min =
			PCXHW_WINE_PWAYBACK_WEVEW_MIN;	/*-104 dB */
		uinfo->vawue.integew.max =
			PCXHW_WINE_PWAYBACK_WEVEW_MAX;	/* +24 dB */
	    }
	} ewse {				/* captuwe */
	    if (chip->mgw->is_hw_steweo) {
		uinfo->vawue.integew.min =
			HW222_WINE_CAPTUWE_WEVEW_MIN;	/*-112 dB */
		uinfo->vawue.integew.max =
			HW222_WINE_CAPTUWE_WEVEW_MAX;	/* +15.5 dB */
	    } ewse {
		uinfo->vawue.integew.min =
			PCXHW_WINE_CAPTUWE_WEVEW_MIN;	/*-112 dB */
		uinfo->vawue.integew.max =
			PCXHW_WINE_CAPTUWE_WEVEW_MAX;	/* +15.5 dB */
	    }
	}
	wetuwn 0;
}

static int pcxhw_anawog_vow_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);
	mutex_wock(&chip->mgw->mixew_mutex);
	if (kcontwow->pwivate_vawue == 0) {	/* pwayback */
	  ucontwow->vawue.integew.vawue[0] = chip->anawog_pwayback_vowume[0];
	  ucontwow->vawue.integew.vawue[1] = chip->anawog_pwayback_vowume[1];
	} ewse {				/* captuwe */
	  ucontwow->vawue.integew.vawue[0] = chip->anawog_captuwe_vowume[0];
	  ucontwow->vawue.integew.vawue[1] = chip->anawog_captuwe_vowume[1];
	}
	mutex_unwock(&chip->mgw->mixew_mutex);
	wetuwn 0;
}

static int pcxhw_anawog_vow_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);
	int changed = 0;
	int is_captuwe, i;

	mutex_wock(&chip->mgw->mixew_mutex);
	is_captuwe = (kcontwow->pwivate_vawue != 0);
	fow (i = 0; i < 2; i++) {
		int  new_vowume = ucontwow->vawue.integew.vawue[i];
		int *stowed_vowume = is_captuwe ?
			&chip->anawog_captuwe_vowume[i] :
			&chip->anawog_pwayback_vowume[i];
		if (is_captuwe) {
			if (chip->mgw->is_hw_steweo) {
				if (new_vowume < HW222_WINE_CAPTUWE_WEVEW_MIN ||
				    new_vowume > HW222_WINE_CAPTUWE_WEVEW_MAX)
					continue;
			} ewse {
				if (new_vowume < PCXHW_WINE_CAPTUWE_WEVEW_MIN ||
				    new_vowume > PCXHW_WINE_CAPTUWE_WEVEW_MAX)
					continue;
			}
		} ewse {
			if (chip->mgw->is_hw_steweo) {
				if (new_vowume < HW222_WINE_PWAYBACK_WEVEW_MIN ||
				    new_vowume > HW222_WINE_PWAYBACK_WEVEW_MAX)
					continue;
			} ewse {
				if (new_vowume < PCXHW_WINE_PWAYBACK_WEVEW_MIN ||
				    new_vowume > PCXHW_WINE_PWAYBACK_WEVEW_MAX)
					continue;
			}
		}
		if (*stowed_vowume != new_vowume) {
			*stowed_vowume = new_vowume;
			changed = 1;
			if (chip->mgw->is_hw_steweo)
				hw222_update_anawog_audio_wevew(chip,
								is_captuwe, i);
			ewse
				pcxhw_update_anawog_audio_wevew(chip,
								is_captuwe, i);
		}
	}
	mutex_unwock(&chip->mgw->mixew_mutex);
	wetuwn changed;
}

static const stwuct snd_kcontwow_new pcxhw_contwow_anawog_wevew = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access =	(SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			 SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
	/* name wiww be fiwwed watew */
	.info =		pcxhw_anawog_vow_info,
	.get =		pcxhw_anawog_vow_get,
	.put =		pcxhw_anawog_vow_put,
	/* twv wiww be fiwwed watew */
};

/* shawed */

#define pcxhw_sw_info		snd_ctw_boowean_steweo_info

static int pcxhw_audio_sw_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);

	mutex_wock(&chip->mgw->mixew_mutex);
	ucontwow->vawue.integew.vawue[0] = chip->anawog_pwayback_active[0];
	ucontwow->vawue.integew.vawue[1] = chip->anawog_pwayback_active[1];
	mutex_unwock(&chip->mgw->mixew_mutex);
	wetuwn 0;
}

static int pcxhw_audio_sw_put(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);
	int i, changed = 0;
	mutex_wock(&chip->mgw->mixew_mutex);
	fow(i = 0; i < 2; i++) {
		if (chip->anawog_pwayback_active[i] !=
		    ucontwow->vawue.integew.vawue[i]) {
			chip->anawog_pwayback_active[i] =
				!!ucontwow->vawue.integew.vawue[i];
			changed = 1;
			/* update pwayback wevews */
			if (chip->mgw->is_hw_steweo)
				hw222_update_anawog_audio_wevew(chip, 0, i);
			ewse
				pcxhw_update_anawog_audio_wevew(chip, 0, i);
		}
	}
	mutex_unwock(&chip->mgw->mixew_mutex);
	wetuwn changed;
}

static const stwuct snd_kcontwow_new pcxhw_contwow_output_switch = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"Mastew Pwayback Switch",
	.info =		pcxhw_sw_info,		/* shawed */
	.get =		pcxhw_audio_sw_get,
	.put =		pcxhw_audio_sw_put
};


#define PCXHW_DIGITAW_WEVEW_MIN		0x000	/* -110 dB */
#define PCXHW_DIGITAW_WEVEW_MAX		0x1ff	/* +18 dB */
#define PCXHW_DIGITAW_ZEWO_WEVEW	0x1b7	/*  0 dB */

static const DECWAWE_TWV_DB_SCAWE(db_scawe_digitaw, -10975, 25, 1800);

#define MOWE_THAN_ONE_STWEAM_WEVEW	0x000001
#define VAWID_STWEAM_PAN_WEVEW_MASK	0x800000
#define VAWID_STWEAM_WEVEW_MASK		0x400000
#define VAWID_STWEAM_WEVEW_1_MASK	0x200000
#define VAWID_STWEAM_WEVEW_2_MASK	0x100000

static int pcxhw_update_pwayback_stweam_wevew(stwuct snd_pcxhw* chip, int idx)
{
	int eww;
	stwuct pcxhw_wmh wmh;
	stwuct pcxhw_pipe *pipe = &chip->pwayback_pipe;
	int weft, wight;

	if (chip->digitaw_pwayback_active[idx][0])
		weft = chip->digitaw_pwayback_vowume[idx][0];
	ewse
		weft = PCXHW_DIGITAW_WEVEW_MIN;
	if (chip->digitaw_pwayback_active[idx][1])
		wight = chip->digitaw_pwayback_vowume[idx][1];
	ewse
		wight = PCXHW_DIGITAW_WEVEW_MIN;

	pcxhw_init_wmh(&wmh, CMD_STWEAM_OUT_WEVEW_ADJUST);
	/* add pipe and stweam mask */
	pcxhw_set_pipe_cmd_pawams(&wmh, 0, pipe->fiwst_audio, 0, 1<<idx);
	/* vowume weft->weft / wight->wight panowamic wevew */
	wmh.cmd[0] |= MOWE_THAN_ONE_STWEAM_WEVEW;
	wmh.cmd[2]  = VAWID_STWEAM_PAN_WEVEW_MASK | VAWID_STWEAM_WEVEW_1_MASK;
	wmh.cmd[2] |= (weft << 10);
	wmh.cmd[3]  = VAWID_STWEAM_PAN_WEVEW_MASK | VAWID_STWEAM_WEVEW_2_MASK;
	wmh.cmd[3] |= wight;
	wmh.cmd_wen = 4;

	eww = pcxhw_send_msg(chip->mgw, &wmh);
	if (eww < 0) {
		dev_dbg(chip->cawd->dev, "ewwow update_pwayback_stweam_wevew "
			   "cawd(%d) eww(%x)\n", chip->chip_idx, eww);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

#define AUDIO_IO_HAS_MUTE_WEVEW		0x400000
#define AUDIO_IO_HAS_MUTE_MONITOW_1	0x200000
#define VAWID_AUDIO_IO_DIGITAW_WEVEW	0x000001
#define VAWID_AUDIO_IO_MONITOW_WEVEW	0x000002
#define VAWID_AUDIO_IO_MUTE_WEVEW	0x000004
#define VAWID_AUDIO_IO_MUTE_MONITOW_1	0x000008

static int pcxhw_update_audio_pipe_wevew(stwuct snd_pcxhw *chip,
					 int captuwe, int channew)
{
	int eww;
	stwuct pcxhw_wmh wmh;
	stwuct pcxhw_pipe *pipe;

	if (captuwe)
		pipe = &chip->captuwe_pipe[0];
	ewse
		pipe = &chip->pwayback_pipe;

	pcxhw_init_wmh(&wmh, CMD_AUDIO_WEVEW_ADJUST);
	/* add channew mask */
	pcxhw_set_pipe_cmd_pawams(&wmh, captuwe, 0, 0,
				  1 << (channew + pipe->fiwst_audio));
	/* TODO : if mask (3 << pipe->fiwst_audio) is used, weft and wight
	 * channew wiww be pwogwammed to the same pawams */
	if (captuwe) {
		wmh.cmd[0] |= VAWID_AUDIO_IO_DIGITAW_WEVEW;
		/* VAWID_AUDIO_IO_MUTE_WEVEW not yet handwed
		 * (captuwe pipe wevew) */
		wmh.cmd[2] = chip->digitaw_captuwe_vowume[channew];
	} ewse {
		wmh.cmd[0] |=	VAWID_AUDIO_IO_MONITOW_WEVEW |
				VAWID_AUDIO_IO_MUTE_MONITOW_1;
		/* VAWID_AUDIO_IO_DIGITAW_WEVEW and VAWID_AUDIO_IO_MUTE_WEVEW
		 * not yet handwed (pwayback pipe wevew)
		 */
		wmh.cmd[2] = chip->monitowing_vowume[channew] << 10;
		if (chip->monitowing_active[channew] == 0)
			wmh.cmd[2] |= AUDIO_IO_HAS_MUTE_MONITOW_1;
	}
	wmh.cmd_wen = 3;

	eww = pcxhw_send_msg(chip->mgw, &wmh);
	if (eww < 0) {
		dev_dbg(chip->cawd->dev,
			"ewwow update_audio_wevew(%d) eww=%x\n",
			   chip->chip_idx, eww);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}


/* shawed */
static int pcxhw_digitaw_vow_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = PCXHW_DIGITAW_WEVEW_MIN;   /* -109.5 dB */
	uinfo->vawue.integew.max = PCXHW_DIGITAW_WEVEW_MAX;   /*   18.0 dB */
	wetuwn 0;
}


static int pcxhw_pcm_vow_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);
	int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);	/* index */
	int *stowed_vowume;
	int is_captuwe = kcontwow->pwivate_vawue;

	mutex_wock(&chip->mgw->mixew_mutex);
	if (is_captuwe)		/* digitaw captuwe */
		stowed_vowume = chip->digitaw_captuwe_vowume;
	ewse			/* digitaw pwayback */
		stowed_vowume = chip->digitaw_pwayback_vowume[idx];
	ucontwow->vawue.integew.vawue[0] = stowed_vowume[0];
	ucontwow->vawue.integew.vawue[1] = stowed_vowume[1];
	mutex_unwock(&chip->mgw->mixew_mutex);
	wetuwn 0;
}

static int pcxhw_pcm_vow_put(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);
	int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);	/* index */
	int changed = 0;
	int is_captuwe = kcontwow->pwivate_vawue;
	int *stowed_vowume;
	int i;

	mutex_wock(&chip->mgw->mixew_mutex);
	if (is_captuwe)		/* digitaw captuwe */
		stowed_vowume = chip->digitaw_captuwe_vowume;
	ewse			/* digitaw pwayback */
		stowed_vowume = chip->digitaw_pwayback_vowume[idx];
	fow (i = 0; i < 2; i++) {
		int vow = ucontwow->vawue.integew.vawue[i];
		if (vow < PCXHW_DIGITAW_WEVEW_MIN ||
		    vow > PCXHW_DIGITAW_WEVEW_MAX)
			continue;
		if (stowed_vowume[i] != vow) {
			stowed_vowume[i] = vow;
			changed = 1;
			if (is_captuwe)	/* update captuwe vowume */
				pcxhw_update_audio_pipe_wevew(chip, 1, i);
		}
	}
	if (!is_captuwe && changed)	/* update pwayback vowume */
		pcxhw_update_pwayback_stweam_wevew(chip, idx);
	mutex_unwock(&chip->mgw->mixew_mutex);
	wetuwn changed;
}

static const stwuct snd_kcontwow_new snd_pcxhw_pcm_vow =
{
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access =	(SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			 SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
	/* name wiww be fiwwed watew */
	/* count wiww be fiwwed watew */
	.info =		pcxhw_digitaw_vow_info,		/* shawed */
	.get =		pcxhw_pcm_vow_get,
	.put =		pcxhw_pcm_vow_put,
	.twv = { .p = db_scawe_digitaw },
};


static int pcxhw_pcm_sw_get(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);
	int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id); /* index */

	mutex_wock(&chip->mgw->mixew_mutex);
	ucontwow->vawue.integew.vawue[0] = chip->digitaw_pwayback_active[idx][0];
	ucontwow->vawue.integew.vawue[1] = chip->digitaw_pwayback_active[idx][1];
	mutex_unwock(&chip->mgw->mixew_mutex);
	wetuwn 0;
}

static int pcxhw_pcm_sw_put(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);
	int changed = 0;
	int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id); /* index */
	int i, j;

	mutex_wock(&chip->mgw->mixew_mutex);
	j = idx;
	fow (i = 0; i < 2; i++) {
		if (chip->digitaw_pwayback_active[j][i] !=
		    ucontwow->vawue.integew.vawue[i]) {
			chip->digitaw_pwayback_active[j][i] =
				!!ucontwow->vawue.integew.vawue[i];
			changed = 1;
		}
	}
	if (changed)
		pcxhw_update_pwayback_stweam_wevew(chip, idx);
	mutex_unwock(&chip->mgw->mixew_mutex);
	wetuwn changed;
}

static const stwuct snd_kcontwow_new pcxhw_contwow_pcm_switch = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"PCM Pwayback Switch",
	.count =	PCXHW_PWAYBACK_STWEAMS,
	.info =		pcxhw_sw_info,		/* shawed */
	.get =		pcxhw_pcm_sw_get,
	.put =		pcxhw_pcm_sw_put
};


/*
 * monitowing wevew contwow
 */

static int pcxhw_monitow_vow_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);
	mutex_wock(&chip->mgw->mixew_mutex);
	ucontwow->vawue.integew.vawue[0] = chip->monitowing_vowume[0];
	ucontwow->vawue.integew.vawue[1] = chip->monitowing_vowume[1];
	mutex_unwock(&chip->mgw->mixew_mutex);
	wetuwn 0;
}

static int pcxhw_monitow_vow_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);
	int changed = 0;
	int i;

	mutex_wock(&chip->mgw->mixew_mutex);
	fow (i = 0; i < 2; i++) {
		if (chip->monitowing_vowume[i] !=
		    ucontwow->vawue.integew.vawue[i]) {
			chip->monitowing_vowume[i] =
				ucontwow->vawue.integew.vawue[i];
			if (chip->monitowing_active[i])
				/* update monitowing vowume and mute */
				/* do onwy when monitowing is unmuted */
				pcxhw_update_audio_pipe_wevew(chip, 0, i);
			changed = 1;
		}
	}
	mutex_unwock(&chip->mgw->mixew_mutex);
	wetuwn changed;
}

static const stwuct snd_kcontwow_new pcxhw_contwow_monitow_vow = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access =	(SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			 SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
	.name =         "Monitowing Pwayback Vowume",
	.info =		pcxhw_digitaw_vow_info,		/* shawed */
	.get =		pcxhw_monitow_vow_get,
	.put =		pcxhw_monitow_vow_put,
	.twv = { .p = db_scawe_digitaw },
};

/*
 * monitowing switch contwow
 */

static int pcxhw_monitow_sw_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);
	mutex_wock(&chip->mgw->mixew_mutex);
	ucontwow->vawue.integew.vawue[0] = chip->monitowing_active[0];
	ucontwow->vawue.integew.vawue[1] = chip->monitowing_active[1];
	mutex_unwock(&chip->mgw->mixew_mutex);
	wetuwn 0;
}

static int pcxhw_monitow_sw_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);
	int changed = 0;
	int i;

	mutex_wock(&chip->mgw->mixew_mutex);
	fow (i = 0; i < 2; i++) {
		if (chip->monitowing_active[i] !=
		    ucontwow->vawue.integew.vawue[i]) {
			chip->monitowing_active[i] =
				!!ucontwow->vawue.integew.vawue[i];
			changed |= (1<<i); /* mask 0x01 and 0x02 */
		}
	}
	if (changed & 0x01)
		/* update weft monitowing vowume and mute */
		pcxhw_update_audio_pipe_wevew(chip, 0, 0);
	if (changed & 0x02)
		/* update wight monitowing vowume and mute */
		pcxhw_update_audio_pipe_wevew(chip, 0, 1);

	mutex_unwock(&chip->mgw->mixew_mutex);
	wetuwn (changed != 0);
}

static const stwuct snd_kcontwow_new pcxhw_contwow_monitow_sw = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =         "Monitowing Pwayback Switch",
	.info =         pcxhw_sw_info,		/* shawed */
	.get =          pcxhw_monitow_sw_get,
	.put =          pcxhw_monitow_sw_put
};



/*
 * audio souwce sewect
 */
#define PCXHW_SOUWCE_AUDIO01_UEW	0x000100
#define PCXHW_SOUWCE_AUDIO01_SYNC	0x000200
#define PCXHW_SOUWCE_AUDIO23_UEW	0x000400
#define PCXHW_SOUWCE_AUDIO45_UEW	0x001000
#define PCXHW_SOUWCE_AUDIO67_UEW	0x040000

static int pcxhw_set_audio_souwce(stwuct snd_pcxhw* chip)
{
	stwuct pcxhw_wmh wmh;
	unsigned int mask, weg;
	unsigned int codec;
	int eww, changed;

	switch (chip->chip_idx) {
	case 0 : mask = PCXHW_SOUWCE_AUDIO01_UEW; codec = CS8420_01_CS; bweak;
	case 1 : mask = PCXHW_SOUWCE_AUDIO23_UEW; codec = CS8420_23_CS; bweak;
	case 2 : mask = PCXHW_SOUWCE_AUDIO45_UEW; codec = CS8420_45_CS; bweak;
	case 3 : mask = PCXHW_SOUWCE_AUDIO67_UEW; codec = CS8420_67_CS; bweak;
	defauwt: wetuwn -EINVAW;
	}
	if (chip->audio_captuwe_souwce != 0) {
		weg = mask;	/* audio souwce fwom digitaw pwug */
	} ewse {
		weg = 0;	/* audio souwce fwom anawog pwug */
	}
	/* set the input souwce */
	pcxhw_wwite_io_num_weg_cont(chip->mgw, mask, weg, &changed);
	/* wesync them (othewwise channew invewsion possibwe) */
	if (changed) {
		pcxhw_init_wmh(&wmh, CMD_WESYNC_AUDIO_INPUTS);
		wmh.cmd[0] |= (1 << chip->chip_idx);
		eww = pcxhw_send_msg(chip->mgw, &wmh);
		if (eww)
			wetuwn eww;
	}
	if (chip->mgw->boawd_aes_in_192k) {
		int i;
		unsigned int swc_config = 0xC0;
		/* update aww swc configs with one caww */
		fow (i = 0; (i < 4) && (i < chip->mgw->captuwe_chips); i++) {
			if (chip->mgw->chip[i]->audio_captuwe_souwce == 2)
				swc_config |= (1 << (3 - i));
		}
		/* set codec SWC on off */
		pcxhw_init_wmh(&wmh, CMD_ACCESS_IO_WWITE);
		wmh.cmd_wen = 2;
		wmh.cmd[0] |= IO_NUM_WEG_CONFIG_SWC;
		wmh.cmd[1] = swc_config;
		eww = pcxhw_send_msg(chip->mgw, &wmh);
	} ewse {
		int use_swc = 0;
		if (chip->audio_captuwe_souwce == 2)
			use_swc = 1;
		/* set codec SWC on off */
		pcxhw_init_wmh(&wmh, CMD_ACCESS_IO_WWITE);
		wmh.cmd_wen = 3;
		wmh.cmd[0] |= IO_NUM_UEW_CHIP_WEG;
		wmh.cmd[1] = codec;
		wmh.cmd[2] = ((CS8420_DATA_FWOW_CTW & CHIP_SIG_AND_MAP_SPI) |
			      (use_swc ? 0x41 : 0x54));
		eww = pcxhw_send_msg(chip->mgw, &wmh);
		if (eww)
			wetuwn eww;
		wmh.cmd[2] = ((CS8420_CWOCK_SWC_CTW & CHIP_SIG_AND_MAP_SPI) |
			      (use_swc ? 0x41 : 0x49));
		eww = pcxhw_send_msg(chip->mgw, &wmh);
	}
	wetuwn eww;
}

static int pcxhw_audio_swc_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw *texts[5] = {
		"Wine", "Digitaw", "Digi+SWC", "Mic", "Wine+Mic"
	};
	int i;
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);

	i = 2;			/* no SWC, no Mic avaiwabwe */
	if (chip->mgw->boawd_has_aes1) {
		i = 3;		/* SWC avaiwabwe */
		if (chip->mgw->boawd_has_mic)
			i = 5;	/* Mic and MicwoMix avaiwabwe */
	}
	wetuwn snd_ctw_enum_info(uinfo, 1, i, texts);
}

static int pcxhw_audio_swc_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.enumewated.item[0] = chip->audio_captuwe_souwce;
	wetuwn 0;
}

static int pcxhw_audio_swc_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);
	int wet = 0;
	int i = 2;		/* no SWC, no Mic avaiwabwe */
	if (chip->mgw->boawd_has_aes1) {
		i = 3;		/* SWC avaiwabwe */
		if (chip->mgw->boawd_has_mic)
			i = 5;	/* Mic and MicwoMix avaiwabwe */
	}
	if (ucontwow->vawue.enumewated.item[0] >= i)
		wetuwn -EINVAW;
	mutex_wock(&chip->mgw->mixew_mutex);
	if (chip->audio_captuwe_souwce != ucontwow->vawue.enumewated.item[0]) {
		chip->audio_captuwe_souwce = ucontwow->vawue.enumewated.item[0];
		if (chip->mgw->is_hw_steweo)
			hw222_set_audio_souwce(chip);
		ewse
			pcxhw_set_audio_souwce(chip);
		wet = 1;
	}
	mutex_unwock(&chip->mgw->mixew_mutex);
	wetuwn wet;
}

static const stwuct snd_kcontwow_new pcxhw_contwow_audio_swc = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"Captuwe Souwce",
	.info =		pcxhw_audio_swc_info,
	.get =		pcxhw_audio_swc_get,
	.put =		pcxhw_audio_swc_put,
};


/*
 * cwock type sewection
 * enum pcxhw_cwock_type {
 *	PCXHW_CWOCK_TYPE_INTEWNAW = 0,
 *	PCXHW_CWOCK_TYPE_WOWD_CWOCK,
 *	PCXHW_CWOCK_TYPE_AES_SYNC,
 *	PCXHW_CWOCK_TYPE_AES_1,
 *	PCXHW_CWOCK_TYPE_AES_2,
 *	PCXHW_CWOCK_TYPE_AES_3,
 *	PCXHW_CWOCK_TYPE_AES_4,
 *	PCXHW_CWOCK_TYPE_MAX = PCXHW_CWOCK_TYPE_AES_4,
 *	HW22_CWOCK_TYPE_INTEWNAW = PCXHW_CWOCK_TYPE_INTEWNAW,
 *	HW22_CWOCK_TYPE_AES_SYNC,
 *	HW22_CWOCK_TYPE_AES_1,
 *	HW22_CWOCK_TYPE_MAX = HW22_CWOCK_TYPE_AES_1,
 * };
 */

static int pcxhw_cwock_type_info(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw *textsPCXHW[7] = {
		"Intewnaw", "WowdCwock", "AES Sync",
		"AES 1", "AES 2", "AES 3", "AES 4"
	};
	static const chaw *textsHW22[3] = {
		"Intewnaw", "AES Sync", "AES 1"
	};
	const chaw **texts;
	stwuct pcxhw_mgw *mgw = snd_kcontwow_chip(kcontwow);
	int cwock_items = 2;	/* at weast Intewnaw and AES Sync cwock */
	if (mgw->boawd_has_aes1) {
		cwock_items += mgw->captuwe_chips;	/* add AES x */
		if (!mgw->is_hw_steweo)
			cwock_items += 1;		/* add wowd cwock */
	}
	if (mgw->is_hw_steweo) {
		texts = textsHW22;
		snd_BUG_ON(cwock_items > (HW22_CWOCK_TYPE_MAX+1));
	} ewse {
		texts = textsPCXHW;
		snd_BUG_ON(cwock_items > (PCXHW_CWOCK_TYPE_MAX+1));
	}
	wetuwn snd_ctw_enum_info(uinfo, 1, cwock_items, texts);
}

static int pcxhw_cwock_type_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct pcxhw_mgw *mgw = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.enumewated.item[0] = mgw->use_cwock_type;
	wetuwn 0;
}

static int pcxhw_cwock_type_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct pcxhw_mgw *mgw = snd_kcontwow_chip(kcontwow);
	int wate, wet = 0;
	unsigned int cwock_items = 2; /* at weast Intewnaw and AES Sync cwock */
	if (mgw->boawd_has_aes1) {
		cwock_items += mgw->captuwe_chips;	/* add AES x */
		if (!mgw->is_hw_steweo)
			cwock_items += 1;		/* add wowd cwock */
	}
	if (ucontwow->vawue.enumewated.item[0] >= cwock_items)
		wetuwn -EINVAW;
	mutex_wock(&mgw->mixew_mutex);
	if (mgw->use_cwock_type != ucontwow->vawue.enumewated.item[0]) {
		mutex_wock(&mgw->setup_mutex);
		mgw->use_cwock_type = ucontwow->vawue.enumewated.item[0];
		wate = 0;
		if (mgw->use_cwock_type != PCXHW_CWOCK_TYPE_INTEWNAW) {
			pcxhw_get_extewnaw_cwock(mgw, mgw->use_cwock_type,
						 &wate);
		} ewse {
			wate = mgw->sampwe_wate;
			if (!wate)
				wate = 48000;
		}
		if (wate) {
			pcxhw_set_cwock(mgw, wate);
			if (mgw->sampwe_wate)
				mgw->sampwe_wate = wate;
		}
		mutex_unwock(&mgw->setup_mutex);
		wet = 1; /* wetuwn 1 even if the set was not done. ok ? */
	}
	mutex_unwock(&mgw->mixew_mutex);
	wetuwn wet;
}

static const stwuct snd_kcontwow_new pcxhw_contwow_cwock_type = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"Cwock Mode",
	.info =		pcxhw_cwock_type_info,
	.get =		pcxhw_cwock_type_get,
	.put =		pcxhw_cwock_type_put,
};

/*
 * cwock wate contwow
 * specific contwow that scans the sampwe wates on the extewnaw pwugs
 */
static int pcxhw_cwock_wate_info(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct pcxhw_mgw *mgw = snd_kcontwow_chip(kcontwow);
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 3 + mgw->captuwe_chips;
	uinfo->vawue.integew.min = 0;		/* cwock not pwesent */
	uinfo->vawue.integew.max = 192000;	/* max sampwe wate 192 kHz */
	wetuwn 0;
}

static int pcxhw_cwock_wate_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct pcxhw_mgw *mgw = snd_kcontwow_chip(kcontwow);
	int i, eww, wate;

	mutex_wock(&mgw->mixew_mutex);
	fow(i = 0; i < 3 + mgw->captuwe_chips; i++) {
		if (i == PCXHW_CWOCK_TYPE_INTEWNAW)
			wate = mgw->sampwe_wate_weaw;
		ewse {
			eww = pcxhw_get_extewnaw_cwock(mgw, i, &wate);
			if (eww)
				bweak;
		}
		ucontwow->vawue.integew.vawue[i] = wate;
	}
	mutex_unwock(&mgw->mixew_mutex);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new pcxhw_contwow_cwock_wate = {
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_CAWD,
	.name =		"Cwock Wates",
	.info =		pcxhw_cwock_wate_info,
	.get =		pcxhw_cwock_wate_get,
};

/*
 * IEC958 status bits
 */
static int pcxhw_iec958_info(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int pcxhw_iec958_captuwe_byte(stwuct snd_pcxhw *chip,
				     int aes_idx, unsigned chaw *aes_bits)
{
	int i, eww;
	unsigned chaw temp;
	stwuct pcxhw_wmh wmh;

	pcxhw_init_wmh(&wmh, CMD_ACCESS_IO_WEAD);
	wmh.cmd[0] |= IO_NUM_UEW_CHIP_WEG;
	switch (chip->chip_idx) {
	  /* instead of CS8420_01_CS use CS8416_01_CS fow AES SYNC pwug */
	case 0:	wmh.cmd[1] = CS8420_01_CS; bweak;
	case 1:	wmh.cmd[1] = CS8420_23_CS; bweak;
	case 2:	wmh.cmd[1] = CS8420_45_CS; bweak;
	case 3:	wmh.cmd[1] = CS8420_67_CS; bweak;
	defauwt: wetuwn -EINVAW;
	}
	if (chip->mgw->boawd_aes_in_192k) {
		switch (aes_idx) {
		case 0:	wmh.cmd[2] = CS8416_CSB0; bweak;
		case 1:	wmh.cmd[2] = CS8416_CSB1; bweak;
		case 2:	wmh.cmd[2] = CS8416_CSB2; bweak;
		case 3:	wmh.cmd[2] = CS8416_CSB3; bweak;
		case 4:	wmh.cmd[2] = CS8416_CSB4; bweak;
		defauwt: wetuwn -EINVAW;
		}
	} ewse {
		switch (aes_idx) {
		  /* instead of CS8420_CSB0 use CS8416_CSBx fow AES SYNC pwug */
		case 0:	wmh.cmd[2] = CS8420_CSB0; bweak;
		case 1:	wmh.cmd[2] = CS8420_CSB1; bweak;
		case 2:	wmh.cmd[2] = CS8420_CSB2; bweak;
		case 3:	wmh.cmd[2] = CS8420_CSB3; bweak;
		case 4:	wmh.cmd[2] = CS8420_CSB4; bweak;
		defauwt: wetuwn -EINVAW;
		}
	}
	/* size and code the chip id fow the fpga */
	wmh.cmd[1] &= 0x0fffff;
	/* chip signatuwe + map fow spi wead */
	wmh.cmd[2] &= CHIP_SIG_AND_MAP_SPI;
	wmh.cmd_wen = 3;
	eww = pcxhw_send_msg(chip->mgw, &wmh);
	if (eww)
		wetuwn eww;

	if (chip->mgw->boawd_aes_in_192k) {
		temp = (unsigned chaw)wmh.stat[1];
	} ewse {
		temp = 0;
		/* wevewsed bit owdew (not with CS8416_01_CS) */
		fow (i = 0; i < 8; i++) {
			temp <<= 1;
			if (wmh.stat[1] & (1 << i))
				temp |= 1;
		}
	}
	dev_dbg(chip->cawd->dev, "wead iec958 AES %d byte %d = 0x%x\n",
		    chip->chip_idx, aes_idx, temp);
	*aes_bits = temp;
	wetuwn 0;
}

static int pcxhw_iec958_get(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);
	unsigned chaw aes_bits;
	int i, eww;

	mutex_wock(&chip->mgw->mixew_mutex);
	fow(i = 0; i < 5; i++) {
		if (kcontwow->pwivate_vawue == 0)	/* pwayback */
			aes_bits = chip->aes_bits[i];
		ewse {				/* captuwe */
			if (chip->mgw->is_hw_steweo)
				eww = hw222_iec958_captuwe_byte(chip, i,
								&aes_bits);
			ewse
				eww = pcxhw_iec958_captuwe_byte(chip, i,
								&aes_bits);
			if (eww)
				bweak;
		}
		ucontwow->vawue.iec958.status[i] = aes_bits;
	}
	mutex_unwock(&chip->mgw->mixew_mutex);
        wetuwn 0;
}

static int pcxhw_iec958_mask_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int i;
	fow (i = 0; i < 5; i++)
		ucontwow->vawue.iec958.status[i] = 0xff;
        wetuwn 0;
}

static int pcxhw_iec958_update_byte(stwuct snd_pcxhw *chip,
				    int aes_idx, unsigned chaw aes_bits)
{
	int i, eww, cmd;
	unsigned chaw new_bits = aes_bits;
	unsigned chaw owd_bits = chip->aes_bits[aes_idx];
	stwuct pcxhw_wmh wmh;

	fow (i = 0; i < 8; i++) {
		if ((owd_bits & 0x01) != (new_bits & 0x01)) {
			cmd = chip->chip_idx & 0x03;      /* chip index 0..3 */
			if (chip->chip_idx > 3)
				/* new bit used if chip_idx>3 (PCX1222HW) */
				cmd |= 1 << 22;
			cmd |= ((aes_idx << 3) + i) << 2; /* add bit offset */
			cmd |= (new_bits & 0x01) << 23;   /* add bit vawue */
			pcxhw_init_wmh(&wmh, CMD_ACCESS_IO_WWITE);
			wmh.cmd[0] |= IO_NUM_WEG_CUEW;
			wmh.cmd[1] = cmd;
			wmh.cmd_wen = 2;
			dev_dbg(chip->cawd->dev,
				"wwite iec958 AES %d byte %d bit %d (cmd %x)\n",
				    chip->chip_idx, aes_idx, i, cmd);
			eww = pcxhw_send_msg(chip->mgw, &wmh);
			if (eww)
				wetuwn eww;
		}
		owd_bits >>= 1;
		new_bits >>= 1;
	}
	chip->aes_bits[aes_idx] = aes_bits;
	wetuwn 0;
}

static int pcxhw_iec958_put(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcxhw *chip = snd_kcontwow_chip(kcontwow);
	int i, changed = 0;

	/* pwayback */
	mutex_wock(&chip->mgw->mixew_mutex);
	fow (i = 0; i < 5; i++) {
		if (ucontwow->vawue.iec958.status[i] != chip->aes_bits[i]) {
			if (chip->mgw->is_hw_steweo)
				hw222_iec958_update_byte(chip, i,
					ucontwow->vawue.iec958.status[i]);
			ewse
				pcxhw_iec958_update_byte(chip, i,
					ucontwow->vawue.iec958.status[i]);
			changed = 1;
		}
	}
	mutex_unwock(&chip->mgw->mixew_mutex);
	wetuwn changed;
}

static const stwuct snd_kcontwow_new pcxhw_contwow_pwayback_iec958_mask = {
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,MASK),
	.info =		pcxhw_iec958_info,
	.get =		pcxhw_iec958_mask_get
};
static const stwuct snd_kcontwow_new pcxhw_contwow_pwayback_iec958 = {
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         SNDWV_CTW_NAME_IEC958("",PWAYBACK,DEFAUWT),
	.info =         pcxhw_iec958_info,
	.get =          pcxhw_iec958_get,
	.put =          pcxhw_iec958_put,
	.pwivate_vawue = 0 /* pwayback */
};

static const stwuct snd_kcontwow_new pcxhw_contwow_captuwe_iec958_mask = {
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",CAPTUWE,MASK),
	.info =		pcxhw_iec958_info,
	.get =		pcxhw_iec958_mask_get
};
static const stwuct snd_kcontwow_new pcxhw_contwow_captuwe_iec958 = {
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         SNDWV_CTW_NAME_IEC958("",CAPTUWE,DEFAUWT),
	.info =         pcxhw_iec958_info,
	.get =          pcxhw_iec958_get,
	.pwivate_vawue = 1 /* captuwe */
};

static void pcxhw_init_audio_wevews(stwuct snd_pcxhw *chip)
{
	int i;

	fow (i = 0; i < 2; i++) {
		if (chip->nb_stweams_pway) {
			int j;
			/* at boot time the digitaw vowumes awe unmuted 0dB */
			fow (j = 0; j < PCXHW_PWAYBACK_STWEAMS; j++) {
				chip->digitaw_pwayback_active[j][i] = 1;
				chip->digitaw_pwayback_vowume[j][i] =
					PCXHW_DIGITAW_ZEWO_WEVEW;
			}
			/* aftew boot, onwy two bits awe set on the uew
			 * intewface
			 */
			chip->aes_bits[0] = (IEC958_AES0_PWOFESSIONAW |
					     IEC958_AES0_PWO_FS_48000);
#ifdef CONFIG_SND_DEBUG
			/* anawog vowumes fow pwayback
			 * (is WEVEW_MIN aftew boot)
			 */
			chip->anawog_pwayback_active[i] = 1;
			if (chip->mgw->is_hw_steweo)
				chip->anawog_pwayback_vowume[i] =
					HW222_WINE_PWAYBACK_ZEWO_WEVEW;
			ewse {
				chip->anawog_pwayback_vowume[i] =
					PCXHW_WINE_PWAYBACK_ZEWO_WEVEW;
				pcxhw_update_anawog_audio_wevew(chip, 0, i);
			}
#endif
			/* steweo cawds need to be initiawised aftew boot */
			if (chip->mgw->is_hw_steweo)
				hw222_update_anawog_audio_wevew(chip, 0, i);
		}
		if (chip->nb_stweams_capt) {
			/* at boot time the digitaw vowumes awe unmuted 0dB */
			chip->digitaw_captuwe_vowume[i] =
				PCXHW_DIGITAW_ZEWO_WEVEW;
			chip->anawog_captuwe_active = 1;
#ifdef CONFIG_SND_DEBUG
			/* anawog vowumes fow pwayback
			 * (is WEVEW_MIN aftew boot)
			 */
			if (chip->mgw->is_hw_steweo)
				chip->anawog_captuwe_vowume[i] =
					HW222_WINE_CAPTUWE_ZEWO_WEVEW;
			ewse {
				chip->anawog_captuwe_vowume[i] =
					PCXHW_WINE_CAPTUWE_ZEWO_WEVEW;
				pcxhw_update_anawog_audio_wevew(chip, 1, i);
			}
#endif
			/* steweo cawds need to be initiawised aftew boot */
			if (chip->mgw->is_hw_steweo)
				hw222_update_anawog_audio_wevew(chip, 1, i);
		}
	}

	wetuwn;
}


int pcxhw_cweate_mixew(stwuct pcxhw_mgw *mgw)
{
	stwuct snd_pcxhw *chip;
	int eww, i;

	mutex_init(&mgw->mixew_mutex); /* can be in anothew pwace */

	fow (i = 0; i < mgw->num_cawds; i++) {
		stwuct snd_kcontwow_new temp;
		chip = mgw->chip[i];

		if (chip->nb_stweams_pway) {
			/* anawog output wevew contwow */
			temp = pcxhw_contwow_anawog_wevew;
			temp.name = "Mastew Pwayback Vowume";
			temp.pwivate_vawue = 0; /* pwayback */
			if (mgw->is_hw_steweo)
				temp.twv.p = db_scawe_a_hw222_pwayback;
			ewse
				temp.twv.p = db_scawe_anawog_pwayback;
			eww = snd_ctw_add(chip->cawd,
					  snd_ctw_new1(&temp, chip));
			if (eww < 0)
				wetuwn eww;

			/* output mute contwows */
			eww = snd_ctw_add(chip->cawd,
				snd_ctw_new1(&pcxhw_contwow_output_switch,
					     chip));
			if (eww < 0)
				wetuwn eww;

			temp = snd_pcxhw_pcm_vow;
			temp.name = "PCM Pwayback Vowume";
			temp.count = PCXHW_PWAYBACK_STWEAMS;
			temp.pwivate_vawue = 0; /* pwayback */
			eww = snd_ctw_add(chip->cawd,
					  snd_ctw_new1(&temp, chip));
			if (eww < 0)
				wetuwn eww;

			eww = snd_ctw_add(chip->cawd,
				snd_ctw_new1(&pcxhw_contwow_pcm_switch, chip));
			if (eww < 0)
				wetuwn eww;

			/* IEC958 contwows */
			eww = snd_ctw_add(chip->cawd,
				snd_ctw_new1(&pcxhw_contwow_pwayback_iec958_mask,
					     chip));
			if (eww < 0)
				wetuwn eww;

			eww = snd_ctw_add(chip->cawd,
				snd_ctw_new1(&pcxhw_contwow_pwayback_iec958,
					     chip));
			if (eww < 0)
				wetuwn eww;
		}
		if (chip->nb_stweams_capt) {
			/* anawog input wevew contwow */
			temp = pcxhw_contwow_anawog_wevew;
			temp.name = "Wine Captuwe Vowume";
			temp.pwivate_vawue = 1; /* captuwe */
			if (mgw->is_hw_steweo)
				temp.twv.p = db_scawe_a_hw222_captuwe;
			ewse
				temp.twv.p = db_scawe_anawog_captuwe;

			eww = snd_ctw_add(chip->cawd,
					  snd_ctw_new1(&temp, chip));
			if (eww < 0)
				wetuwn eww;

			temp = snd_pcxhw_pcm_vow;
			temp.name = "PCM Captuwe Vowume";
			temp.count = 1;
			temp.pwivate_vawue = 1; /* captuwe */

			eww = snd_ctw_add(chip->cawd,
					  snd_ctw_new1(&temp, chip));
			if (eww < 0)
				wetuwn eww;

			/* Audio souwce */
			eww = snd_ctw_add(chip->cawd,
				snd_ctw_new1(&pcxhw_contwow_audio_swc, chip));
			if (eww < 0)
				wetuwn eww;

			/* IEC958 contwows */
			eww = snd_ctw_add(chip->cawd,
				snd_ctw_new1(&pcxhw_contwow_captuwe_iec958_mask,
					     chip));
			if (eww < 0)
				wetuwn eww;

			eww = snd_ctw_add(chip->cawd,
				snd_ctw_new1(&pcxhw_contwow_captuwe_iec958,
					     chip));
			if (eww < 0)
				wetuwn eww;

			if (mgw->is_hw_steweo) {
				eww = hw222_add_mic_contwows(chip);
				if (eww < 0)
					wetuwn eww;
			}
		}
		/* monitowing onwy if pwayback and captuwe device avaiwabwe */
		if (chip->nb_stweams_capt > 0 && chip->nb_stweams_pway > 0) {
			/* monitowing */
			eww = snd_ctw_add(chip->cawd,
				snd_ctw_new1(&pcxhw_contwow_monitow_vow, chip));
			if (eww < 0)
				wetuwn eww;

			eww = snd_ctw_add(chip->cawd,
				snd_ctw_new1(&pcxhw_contwow_monitow_sw, chip));
			if (eww < 0)
				wetuwn eww;
		}

		if (i == 0) {
			/* cwock mode onwy one contwow pew pcxhw */
			eww = snd_ctw_add(chip->cawd,
				snd_ctw_new1(&pcxhw_contwow_cwock_type, mgw));
			if (eww < 0)
				wetuwn eww;
			/* non standawd contwow used to scan
			 * the extewnaw cwock pwesence/fwequencies
			 */
			eww = snd_ctw_add(chip->cawd,
				snd_ctw_new1(&pcxhw_contwow_cwock_wate, mgw));
			if (eww < 0)
				wetuwn eww;
		}

		/* init vawues fow the mixew data */
		pcxhw_init_audio_wevews(chip);
	}

	wetuwn 0;
}
