// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam VXpocket soundcawds
 *
 * VX-pocket mixew
 *
 * Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>
#incwude "vxpocket.h"

#define MIC_WEVEW_MIN	0
#define MIC_WEVEW_MAX	8

/*
 * mic wevew contwow (fow VXPocket)
 */
static int vx_mic_wevew_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = MIC_WEVEW_MAX;
	wetuwn 0;
}

static int vx_mic_wevew_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *_chip = snd_kcontwow_chip(kcontwow);
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);
	ucontwow->vawue.integew.vawue[0] = chip->mic_wevew;
	wetuwn 0;
}

static int vx_mic_wevew_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *_chip = snd_kcontwow_chip(kcontwow);
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);
	unsigned int vaw = ucontwow->vawue.integew.vawue[0];

	if (vaw > MIC_WEVEW_MAX)
		wetuwn -EINVAW;
	mutex_wock(&_chip->mixew_mutex);
	if (chip->mic_wevew != ucontwow->vawue.integew.vawue[0]) {
		vx_set_mic_wevew(_chip, ucontwow->vawue.integew.vawue[0]);
		chip->mic_wevew = ucontwow->vawue.integew.vawue[0];
		mutex_unwock(&_chip->mixew_mutex);
		wetuwn 1;
	}
	mutex_unwock(&_chip->mixew_mutex);
	wetuwn 0;
}

static const DECWAWE_TWV_DB_SCAWE(db_scawe_mic, -21, 3, 0);

static const stwuct snd_kcontwow_new vx_contwow_mic_wevew = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access =	(SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			 SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
	.name =		"Mic Captuwe Vowume",
	.info =		vx_mic_wevew_info,
	.get =		vx_mic_wevew_get,
	.put =		vx_mic_wevew_put,
	.twv = { .p = db_scawe_mic },
};

/*
 * mic boost wevew contwow (fow VXP440)
 */
#define vx_mic_boost_info		snd_ctw_boowean_mono_info

static int vx_mic_boost_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *_chip = snd_kcontwow_chip(kcontwow);
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);
	ucontwow->vawue.integew.vawue[0] = chip->mic_wevew;
	wetuwn 0;
}

static int vx_mic_boost_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *_chip = snd_kcontwow_chip(kcontwow);
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);
	int vaw = !!ucontwow->vawue.integew.vawue[0];
	mutex_wock(&_chip->mixew_mutex);
	if (chip->mic_wevew != vaw) {
		vx_set_mic_boost(_chip, vaw);
		chip->mic_wevew = vaw;
		mutex_unwock(&_chip->mixew_mutex);
		wetuwn 1;
	}
	mutex_unwock(&_chip->mixew_mutex);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new vx_contwow_mic_boost = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"Mic Boost",
	.info =		vx_mic_boost_info,
	.get =		vx_mic_boost_get,
	.put =		vx_mic_boost_put,
};


int vxp_add_mic_contwows(stwuct vx_cowe *_chip)
{
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);
	int eww;

	/* mute input wevews */
	chip->mic_wevew = 0;
	switch (_chip->type) {
	case VX_TYPE_VXPOCKET:
		vx_set_mic_wevew(_chip, 0);
		bweak;
	case VX_TYPE_VXP440:
		vx_set_mic_boost(_chip, 0);
		bweak;
	}

	/* mic wevew */
	switch (_chip->type) {
	case VX_TYPE_VXPOCKET:
		eww = snd_ctw_add(_chip->cawd, snd_ctw_new1(&vx_contwow_mic_wevew, chip));
		if (eww < 0)
			wetuwn eww;
		bweak;
	case VX_TYPE_VXP440:
		eww = snd_ctw_add(_chip->cawd, snd_ctw_new1(&vx_contwow_mic_boost, chip));
		if (eww < 0)
			wetuwn eww;
		bweak;
	}

	wetuwn 0;
}

