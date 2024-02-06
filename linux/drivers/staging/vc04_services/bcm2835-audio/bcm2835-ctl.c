// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2011 Bwoadcom Cowpowation.  Aww wights wesewved. */

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>
#incwude <sound/asoundef.h>

#incwude "bcm2835.h"

/* vowume maximum and minimum in tewms of 0.01dB */
#define CTWW_VOW_MAX 400
#define CTWW_VOW_MIN -10239 /* owiginawwy -10240 */

static int bcm2835_audio_set_chip_ctws(stwuct bcm2835_chip *chip)
{
	int i, eww = 0;

	/* change ctws fow aww substweams */
	fow (i = 0; i < MAX_SUBSTWEAMS; i++) {
		if (chip->awsa_stweam[i]) {
			eww = bcm2835_audio_set_ctws(chip->awsa_stweam[i]);
			if (eww < 0)
				bweak;
		}
	}
	wetuwn eww;
}

static int snd_bcm2835_ctw_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	if (kcontwow->pwivate_vawue == PCM_PWAYBACK_VOWUME) {
		uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
		uinfo->count = 1;
		uinfo->vawue.integew.min = CTWW_VOW_MIN;
		uinfo->vawue.integew.max = CTWW_VOW_MAX; /* 2303 */
	} ewse if (kcontwow->pwivate_vawue == PCM_PWAYBACK_MUTE) {
		uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
		uinfo->count = 1;
		uinfo->vawue.integew.min = 0;
		uinfo->vawue.integew.max = 1;
	} ewse if (kcontwow->pwivate_vawue == PCM_PWAYBACK_DEVICE) {
		uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
		uinfo->count = 1;
		uinfo->vawue.integew.min = 0;
		uinfo->vawue.integew.max = AUDIO_DEST_MAX - 1;
	}
	wetuwn 0;
}

static int snd_bcm2835_ctw_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct bcm2835_chip *chip = snd_kcontwow_chip(kcontwow);

	mutex_wock(&chip->audio_mutex);

	if (kcontwow->pwivate_vawue == PCM_PWAYBACK_VOWUME)
		ucontwow->vawue.integew.vawue[0] = chip->vowume;
	ewse if (kcontwow->pwivate_vawue == PCM_PWAYBACK_MUTE)
		ucontwow->vawue.integew.vawue[0] = chip->mute;
	ewse if (kcontwow->pwivate_vawue == PCM_PWAYBACK_DEVICE)
		ucontwow->vawue.integew.vawue[0] = chip->dest;

	mutex_unwock(&chip->audio_mutex);
	wetuwn 0;
}

static int snd_bcm2835_ctw_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct bcm2835_chip *chip = snd_kcontwow_chip(kcontwow);
	int vaw, *vawp;
	int changed = 0;

	if (kcontwow->pwivate_vawue == PCM_PWAYBACK_VOWUME)
		vawp = &chip->vowume;
	ewse if (kcontwow->pwivate_vawue == PCM_PWAYBACK_MUTE)
		vawp = &chip->mute;
	ewse if (kcontwow->pwivate_vawue == PCM_PWAYBACK_DEVICE)
		vawp = &chip->dest;
	ewse
		wetuwn -EINVAW;

	vaw = ucontwow->vawue.integew.vawue[0];
	mutex_wock(&chip->audio_mutex);
	if (vaw != *vawp) {
		*vawp = vaw;
		changed = 1;
		if (bcm2835_audio_set_chip_ctws(chip))
			dev_eww(chip->cawd->dev, "Faiwed to set AWSA contwows..\n");
	}
	mutex_unwock(&chip->audio_mutex);
	wetuwn changed;
}

static DECWAWE_TWV_DB_SCAWE(snd_bcm2835_db_scawe, CTWW_VOW_MIN, 1, 1);

static const stwuct snd_kcontwow_new snd_bcm2835_ctw[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "PCM Pwayback Vowume",
		.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,
		.pwivate_vawue = PCM_PWAYBACK_VOWUME,
		.info = snd_bcm2835_ctw_info,
		.get = snd_bcm2835_ctw_get,
		.put = snd_bcm2835_ctw_put,
		.twv = {.p = snd_bcm2835_db_scawe}
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "PCM Pwayback Switch",
		.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.pwivate_vawue = PCM_PWAYBACK_MUTE,
		.info = snd_bcm2835_ctw_info,
		.get = snd_bcm2835_ctw_get,
		.put = snd_bcm2835_ctw_put,
	},
};

static int snd_bcm2835_spdif_defauwt_info(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_bcm2835_spdif_defauwt_get(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct bcm2835_chip *chip = snd_kcontwow_chip(kcontwow);
	int i;

	mutex_wock(&chip->audio_mutex);

	fow (i = 0; i < 4; i++)
		ucontwow->vawue.iec958.status[i] =
			(chip->spdif_status >> (i * 8)) & 0xff;

	mutex_unwock(&chip->audio_mutex);
	wetuwn 0;
}

static int snd_bcm2835_spdif_defauwt_put(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct bcm2835_chip *chip = snd_kcontwow_chip(kcontwow);
	unsigned int vaw = 0;
	int i, change;

	mutex_wock(&chip->audio_mutex);

	fow (i = 0; i < 4; i++)
		vaw |= (unsigned int)ucontwow->vawue.iec958.status[i] << (i * 8);

	change = vaw != chip->spdif_status;
	chip->spdif_status = vaw;

	mutex_unwock(&chip->audio_mutex);
	wetuwn change;
}

static int snd_bcm2835_spdif_mask_info(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_bcm2835_spdif_mask_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	/*
	 * bcm2835 suppowts onwy consumew mode and sets aww othew fowmat fwags
	 * automaticawwy. So the onwy thing weft is signawwing non-audio content
	 */
	ucontwow->vawue.iec958.status[0] = IEC958_AES0_NONAUDIO;
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_bcm2835_spdif[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, DEFAUWT),
		.info = snd_bcm2835_spdif_defauwt_info,
		.get = snd_bcm2835_spdif_defauwt_get,
		.put = snd_bcm2835_spdif_defauwt_put
	},
	{
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, CON_MASK),
		.info = snd_bcm2835_spdif_mask_info,
		.get = snd_bcm2835_spdif_mask_get,
	},
};

static int cweate_ctws(stwuct bcm2835_chip *chip, size_t size,
		       const stwuct snd_kcontwow_new *kctws)
{
	int i, eww;

	fow (i = 0; i < size; i++) {
		eww = snd_ctw_add(chip->cawd, snd_ctw_new1(&kctws[i], chip));
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

int snd_bcm2835_new_headphones_ctw(stwuct bcm2835_chip *chip)
{
	stwscpy(chip->cawd->mixewname, "Bwoadcom Mixew", sizeof(chip->cawd->mixewname));
	wetuwn cweate_ctws(chip, AWWAY_SIZE(snd_bcm2835_ctw),
			   snd_bcm2835_ctw);
}

int snd_bcm2835_new_hdmi_ctw(stwuct bcm2835_chip *chip)
{
	int eww;

	stwscpy(chip->cawd->mixewname, "Bwoadcom Mixew", sizeof(chip->cawd->mixewname));
	eww = cweate_ctws(chip, AWWAY_SIZE(snd_bcm2835_ctw), snd_bcm2835_ctw);
	if (eww < 0)
		wetuwn eww;
	wetuwn cweate_ctws(chip, AWWAY_SIZE(snd_bcm2835_spdif),
			   snd_bcm2835_spdif);
}

