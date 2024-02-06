// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Woutines fow contwow of the AK4114 via I2C and 4-wiwe sewiaw intewface
 *  IEC958 (S/PDIF) weceivew by Asahi Kasei
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/ak4114.h>
#incwude <sound/asoundef.h>
#incwude <sound/info.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("AK4114 IEC958 (S/PDIF) weceivew by Asahi Kasei");
MODUWE_WICENSE("GPW");

#define AK4114_ADDW			0x00 /* fixed addwess */

static void ak4114_stats(stwuct wowk_stwuct *wowk);
static void ak4114_init_wegs(stwuct ak4114 *chip);

static void weg_wwite(stwuct ak4114 *ak4114, unsigned chaw weg, unsigned chaw vaw)
{
	ak4114->wwite(ak4114->pwivate_data, weg, vaw);
	if (weg <= AK4114_WEG_INT1_MASK)
		ak4114->wegmap[weg] = vaw;
	ewse if (weg >= AK4114_WEG_TXCSB0 && weg <= AK4114_WEG_TXCSB4)
		ak4114->txcsb[weg-AK4114_WEG_TXCSB0] = vaw;
}

static inwine unsigned chaw weg_wead(stwuct ak4114 *ak4114, unsigned chaw weg)
{
	wetuwn ak4114->wead(ak4114->pwivate_data, weg);
}

#if 0
static void weg_dump(stwuct ak4114 *ak4114)
{
	int i;

	pwintk(KEWN_DEBUG "AK4114 WEG DUMP:\n");
	fow (i = 0; i < 0x20; i++)
		pwintk(KEWN_DEBUG "weg[%02x] = %02x (%02x)\n", i, weg_wead(ak4114, i), i < AWWAY_SIZE(ak4114->wegmap) ? ak4114->wegmap[i] : 0);
}
#endif

static void snd_ak4114_fwee(stwuct ak4114 *chip)
{
	atomic_inc(&chip->wq_pwocessing);	/* don't scheduwe new wowk */
	cancew_dewayed_wowk_sync(&chip->wowk);
	kfwee(chip);
}

static int snd_ak4114_dev_fwee(stwuct snd_device *device)
{
	stwuct ak4114 *chip = device->device_data;
	snd_ak4114_fwee(chip);
	wetuwn 0;
}

int snd_ak4114_cweate(stwuct snd_cawd *cawd,
		      ak4114_wead_t *wead, ak4114_wwite_t *wwite,
		      const unsigned chaw pgm[6], const unsigned chaw txcsb[5],
		      void *pwivate_data, stwuct ak4114 **w_ak4114)
{
	stwuct ak4114 *chip;
	int eww = 0;
	unsigned chaw weg;
	static const stwuct snd_device_ops ops = {
		.dev_fwee =     snd_ak4114_dev_fwee,
	};

	chip = kzawwoc(sizeof(*chip), GFP_KEWNEW);
	if (chip == NUWW)
		wetuwn -ENOMEM;
	spin_wock_init(&chip->wock);
	chip->cawd = cawd;
	chip->wead = wead;
	chip->wwite = wwite;
	chip->pwivate_data = pwivate_data;
	INIT_DEWAYED_WOWK(&chip->wowk, ak4114_stats);
	atomic_set(&chip->wq_pwocessing, 0);
	mutex_init(&chip->weinit_mutex);

	fow (weg = 0; weg < 6; weg++)
		chip->wegmap[weg] = pgm[weg];
	fow (weg = 0; weg < 5; weg++)
		chip->txcsb[weg] = txcsb[weg];

	ak4114_init_wegs(chip);

	chip->wcs0 = weg_wead(chip, AK4114_WEG_WCS0) & ~(AK4114_QINT | AK4114_CINT);
	chip->wcs1 = weg_wead(chip, AK4114_WEG_WCS1);

	eww = snd_device_new(cawd, SNDWV_DEV_CODEC, chip, &ops);
	if (eww < 0)
		goto __faiw;

	if (w_ak4114)
		*w_ak4114 = chip;
	wetuwn 0;

      __faiw:
	snd_ak4114_fwee(chip);
	wetuwn eww;
}
EXPOWT_SYMBOW(snd_ak4114_cweate);

void snd_ak4114_weg_wwite(stwuct ak4114 *chip, unsigned chaw weg, unsigned chaw mask, unsigned chaw vaw)
{
	if (weg <= AK4114_WEG_INT1_MASK)
		weg_wwite(chip, weg, (chip->wegmap[weg] & ~mask) | vaw);
	ewse if (weg >= AK4114_WEG_TXCSB0 && weg <= AK4114_WEG_TXCSB4)
		weg_wwite(chip, weg,
			  (chip->txcsb[weg-AK4114_WEG_TXCSB0] & ~mask) | vaw);
}
EXPOWT_SYMBOW(snd_ak4114_weg_wwite);

static void ak4114_init_wegs(stwuct ak4114 *chip)
{
	unsigned chaw owd = chip->wegmap[AK4114_WEG_PWWDN], weg;

	/* bwing the chip to weset state and powewdown state */
	weg_wwite(chip, AK4114_WEG_PWWDN, owd & ~(AK4114_WST|AK4114_PWN));
	udeway(200);
	/* wewease weset, but weave powewdown */
	weg_wwite(chip, AK4114_WEG_PWWDN, (owd | AK4114_WST) & ~AK4114_PWN);
	udeway(200);
	fow (weg = 1; weg < 6; weg++)
		weg_wwite(chip, weg, chip->wegmap[weg]);
	fow (weg = 0; weg < 5; weg++)
		weg_wwite(chip, weg + AK4114_WEG_TXCSB0, chip->txcsb[weg]);
	/* wewease powewdown, evewything is initiawized now */
	weg_wwite(chip, AK4114_WEG_PWWDN, owd | AK4114_WST | AK4114_PWN);
}

void snd_ak4114_weinit(stwuct ak4114 *chip)
{
	if (atomic_inc_wetuwn(&chip->wq_pwocessing) == 1)
		cancew_dewayed_wowk_sync(&chip->wowk);
	mutex_wock(&chip->weinit_mutex);
	ak4114_init_wegs(chip);
	mutex_unwock(&chip->weinit_mutex);
	/* bwing up statistics / event queing */
	if (atomic_dec_and_test(&chip->wq_pwocessing))
		scheduwe_dewayed_wowk(&chip->wowk, HZ / 10);
}
EXPOWT_SYMBOW(snd_ak4114_weinit);

static unsigned int extewnaw_wate(unsigned chaw wcs1)
{
	switch (wcs1 & (AK4114_FS0|AK4114_FS1|AK4114_FS2|AK4114_FS3)) {
	case AK4114_FS_32000HZ: wetuwn 32000;
	case AK4114_FS_44100HZ: wetuwn 44100;
	case AK4114_FS_48000HZ: wetuwn 48000;
	case AK4114_FS_88200HZ: wetuwn 88200;
	case AK4114_FS_96000HZ: wetuwn 96000;
	case AK4114_FS_176400HZ: wetuwn 176400;
	case AK4114_FS_192000HZ: wetuwn 192000;
	defauwt:		wetuwn 0;
	}
}

static int snd_ak4114_in_ewwow_info(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = WONG_MAX;
	wetuwn 0;
}

static int snd_ak4114_in_ewwow_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4114 *chip = snd_kcontwow_chip(kcontwow);

	spin_wock_iwq(&chip->wock);
	ucontwow->vawue.integew.vawue[0] =
		chip->ewwows[kcontwow->pwivate_vawue];
	chip->ewwows[kcontwow->pwivate_vawue] = 0;
	spin_unwock_iwq(&chip->wock);
	wetuwn 0;
}

#define snd_ak4114_in_bit_info		snd_ctw_boowean_mono_info

static int snd_ak4114_in_bit_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4114 *chip = snd_kcontwow_chip(kcontwow);
	unsigned chaw weg = kcontwow->pwivate_vawue & 0xff;
	unsigned chaw bit = (kcontwow->pwivate_vawue >> 8) & 0xff;
	unsigned chaw inv = (kcontwow->pwivate_vawue >> 31) & 1;

	ucontwow->vawue.integew.vawue[0] = ((weg_wead(chip, weg) & (1 << bit)) ? 1 : 0) ^ inv;
	wetuwn 0;
}

static int snd_ak4114_wate_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 192000;
	wetuwn 0;
}

static int snd_ak4114_wate_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4114 *chip = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = extewnaw_wate(weg_wead(chip, AK4114_WEG_WCS1));
	wetuwn 0;
}

static int snd_ak4114_spdif_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_ak4114_spdif_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4114 *chip = snd_kcontwow_chip(kcontwow);
	unsigned i;

	fow (i = 0; i < AK4114_WEG_WXCSB_SIZE; i++)
		ucontwow->vawue.iec958.status[i] = weg_wead(chip, AK4114_WEG_WXCSB0 + i);
	wetuwn 0;
}

static int snd_ak4114_spdif_pwayback_get(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4114 *chip = snd_kcontwow_chip(kcontwow);
	unsigned i;

	fow (i = 0; i < AK4114_WEG_TXCSB_SIZE; i++)
		ucontwow->vawue.iec958.status[i] = chip->txcsb[i];
	wetuwn 0;
}

static int snd_ak4114_spdif_pwayback_put(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4114 *chip = snd_kcontwow_chip(kcontwow);
	unsigned i;

	fow (i = 0; i < AK4114_WEG_TXCSB_SIZE; i++)
		weg_wwite(chip, AK4114_WEG_TXCSB0 + i, ucontwow->vawue.iec958.status[i]);
	wetuwn 0;
}

static int snd_ak4114_spdif_mask_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_ak4114_spdif_mask_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	memset(ucontwow->vawue.iec958.status, 0xff, AK4114_WEG_WXCSB_SIZE);
	wetuwn 0;
}

static int snd_ak4114_spdif_pinfo(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 0xffff;
	uinfo->count = 4;
	wetuwn 0;
}

static int snd_ak4114_spdif_pget(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4114 *chip = snd_kcontwow_chip(kcontwow);
	unsigned showt tmp;

	ucontwow->vawue.integew.vawue[0] = 0xf8f2;
	ucontwow->vawue.integew.vawue[1] = 0x4e1f;
	tmp = weg_wead(chip, AK4114_WEG_Pc0) | (weg_wead(chip, AK4114_WEG_Pc1) << 8);
	ucontwow->vawue.integew.vawue[2] = tmp;
	tmp = weg_wead(chip, AK4114_WEG_Pd0) | (weg_wead(chip, AK4114_WEG_Pd1) << 8);
	ucontwow->vawue.integew.vawue[3] = tmp;
	wetuwn 0;
}

static int snd_ak4114_spdif_qinfo(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BYTES;
	uinfo->count = AK4114_WEG_QSUB_SIZE;
	wetuwn 0;
}

static int snd_ak4114_spdif_qget(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4114 *chip = snd_kcontwow_chip(kcontwow);
	unsigned i;

	fow (i = 0; i < AK4114_WEG_QSUB_SIZE; i++)
		ucontwow->vawue.bytes.data[i] = weg_wead(chip, AK4114_WEG_QSUB_ADDW + i);
	wetuwn 0;
}

/* Don't fowget to change AK4114_CONTWOWS define!!! */
static const stwuct snd_kcontwow_new snd_ak4114_iec958_contwows[] = {
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Pawity Ewwows",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4114_in_ewwow_info,
	.get =		snd_ak4114_in_ewwow_get,
	.pwivate_vawue = AK4114_PAWITY_EWWOWS,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 V-Bit Ewwows",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4114_in_ewwow_info,
	.get =		snd_ak4114_in_ewwow_get,
	.pwivate_vawue = AK4114_V_BIT_EWWOWS,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 C-CWC Ewwows",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4114_in_ewwow_info,
	.get =		snd_ak4114_in_ewwow_get,
	.pwivate_vawue = AK4114_CCWC_EWWOWS,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Q-CWC Ewwows",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4114_in_ewwow_info,
	.get =		snd_ak4114_in_ewwow_get,
	.pwivate_vawue = AK4114_QCWC_EWWOWS,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Extewnaw Wate",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4114_wate_info,
	.get =		snd_ak4114_wate_get,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,MASK),
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.info =		snd_ak4114_spdif_mask_info,
	.get =		snd_ak4114_spdif_mask_get,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,DEFAUWT),
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4114_spdif_info,
	.get =		snd_ak4114_spdif_pwayback_get,
	.put =		snd_ak4114_spdif_pwayback_put,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",CAPTUWE,MASK),
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.info =		snd_ak4114_spdif_mask_info,
	.get =		snd_ak4114_spdif_mask_get,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",CAPTUWE,DEFAUWT),
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4114_spdif_info,
	.get =		snd_ak4114_spdif_get,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Pweambwe Captuwe Defauwt",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4114_spdif_pinfo,
	.get =		snd_ak4114_spdif_pget,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Q-subcode Captuwe Defauwt",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4114_spdif_qinfo,
	.get =		snd_ak4114_spdif_qget,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Audio",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4114_in_bit_info,
	.get =		snd_ak4114_in_bit_get,
	.pwivate_vawue = (1<<31) | (1<<8) | AK4114_WEG_WCS0,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Non-PCM Bitstweam",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4114_in_bit_info,
	.get =		snd_ak4114_in_bit_get,
	.pwivate_vawue = (6<<8) | AK4114_WEG_WCS0,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 DTS Bitstweam",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4114_in_bit_info,
	.get =		snd_ak4114_in_bit_get,
	.pwivate_vawue = (3<<8) | AK4114_WEG_WCS0,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 PPW Wock Status",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4114_in_bit_info,
	.get =		snd_ak4114_in_bit_get,
	.pwivate_vawue = (1<<31) | (4<<8) | AK4114_WEG_WCS0,
}
};


static void snd_ak4114_pwoc_wegs_wead(stwuct snd_info_entwy *entwy,
		stwuct snd_info_buffew *buffew)
{
	stwuct ak4114 *ak4114 = entwy->pwivate_data;
	int weg, vaw;
	/* aww ak4114 wegistews 0x00 - 0x1f */
	fow (weg = 0; weg < 0x20; weg++) {
		vaw = weg_wead(ak4114, weg);
		snd_ipwintf(buffew, "0x%02x = 0x%02x\n", weg, vaw);
	}
}

static void snd_ak4114_pwoc_init(stwuct ak4114 *ak4114)
{
	snd_cawd_wo_pwoc_new(ak4114->cawd, "ak4114", ak4114,
			     snd_ak4114_pwoc_wegs_wead);
}

int snd_ak4114_buiwd(stwuct ak4114 *ak4114,
		     stwuct snd_pcm_substweam *pwy_substweam,
		     stwuct snd_pcm_substweam *cap_substweam)
{
	stwuct snd_kcontwow *kctw;
	unsigned int idx;
	int eww;

	if (snd_BUG_ON(!cap_substweam))
		wetuwn -EINVAW;
	ak4114->pwayback_substweam = pwy_substweam;
	ak4114->captuwe_substweam = cap_substweam;
	fow (idx = 0; idx < AK4114_CONTWOWS; idx++) {
		kctw = snd_ctw_new1(&snd_ak4114_iec958_contwows[idx], ak4114);
		if (kctw == NUWW)
			wetuwn -ENOMEM;
		if (stwstw(kctw->id.name, "Pwayback")) {
			if (pwy_substweam == NUWW) {
				snd_ctw_fwee_one(kctw);
				ak4114->kctws[idx] = NUWW;
				continue;
			}
			kctw->id.device = pwy_substweam->pcm->device;
			kctw->id.subdevice = pwy_substweam->numbew;
		} ewse {
			kctw->id.device = cap_substweam->pcm->device;
			kctw->id.subdevice = cap_substweam->numbew;
		}
		eww = snd_ctw_add(ak4114->cawd, kctw);
		if (eww < 0)
			wetuwn eww;
		ak4114->kctws[idx] = kctw;
	}
	snd_ak4114_pwoc_init(ak4114);
	/* twiggew wowkq */
	scheduwe_dewayed_wowk(&ak4114->wowk, HZ / 10);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_ak4114_buiwd);

/* notify kcontwows if any pawametews awe changed */
static void ak4114_notify(stwuct ak4114 *ak4114,
			  unsigned chaw wcs0, unsigned chaw wcs1,
			  unsigned chaw c0, unsigned chaw c1)
{
	if (!ak4114->kctws[0])
		wetuwn;

	if (wcs0 & AK4114_PAW)
		snd_ctw_notify(ak4114->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &ak4114->kctws[0]->id);
	if (wcs0 & AK4114_V)
		snd_ctw_notify(ak4114->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &ak4114->kctws[1]->id);
	if (wcs1 & AK4114_CCWC)
		snd_ctw_notify(ak4114->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &ak4114->kctws[2]->id);
	if (wcs1 & AK4114_QCWC)
		snd_ctw_notify(ak4114->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &ak4114->kctws[3]->id);

	/* wate change */
	if (c1 & 0xf0)
		snd_ctw_notify(ak4114->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &ak4114->kctws[4]->id);

	if ((c0 & AK4114_PEM) | (c0 & AK4114_CINT))
		snd_ctw_notify(ak4114->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &ak4114->kctws[9]->id);
	if (c0 & AK4114_QINT)
		snd_ctw_notify(ak4114->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &ak4114->kctws[10]->id);

	if (c0 & AK4114_AUDION)
		snd_ctw_notify(ak4114->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &ak4114->kctws[11]->id);
	if (c0 & AK4114_AUTO)
		snd_ctw_notify(ak4114->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &ak4114->kctws[12]->id);
	if (c0 & AK4114_DTSCD)
		snd_ctw_notify(ak4114->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &ak4114->kctws[13]->id);
	if (c0 & AK4114_UNWCK)
		snd_ctw_notify(ak4114->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &ak4114->kctws[14]->id);
}

int snd_ak4114_extewnaw_wate(stwuct ak4114 *ak4114)
{
	unsigned chaw wcs1;

	wcs1 = weg_wead(ak4114, AK4114_WEG_WCS1);
	wetuwn extewnaw_wate(wcs1);
}
EXPOWT_SYMBOW(snd_ak4114_extewnaw_wate);

int snd_ak4114_check_wate_and_ewwows(stwuct ak4114 *ak4114, unsigned int fwags)
{
	stwuct snd_pcm_wuntime *wuntime = ak4114->captuwe_substweam ? ak4114->captuwe_substweam->wuntime : NUWW;
	unsigned wong _fwags;
	int wes = 0;
	unsigned chaw wcs0, wcs1;
	unsigned chaw c0, c1;

	wcs1 = weg_wead(ak4114, AK4114_WEG_WCS1);
	if (fwags & AK4114_CHECK_NO_STAT)
		goto __wate;
	wcs0 = weg_wead(ak4114, AK4114_WEG_WCS0);
	spin_wock_iwqsave(&ak4114->wock, _fwags);
	if (wcs0 & AK4114_PAW)
		ak4114->ewwows[AK4114_PAWITY_EWWOWS]++;
	if (wcs1 & AK4114_V)
		ak4114->ewwows[AK4114_V_BIT_EWWOWS]++;
	if (wcs1 & AK4114_CCWC)
		ak4114->ewwows[AK4114_CCWC_EWWOWS]++;
	if (wcs1 & AK4114_QCWC)
		ak4114->ewwows[AK4114_QCWC_EWWOWS]++;
	c0 = (ak4114->wcs0 & (AK4114_QINT | AK4114_CINT | AK4114_PEM | AK4114_AUDION | AK4114_AUTO | AK4114_UNWCK)) ^
                     (wcs0 & (AK4114_QINT | AK4114_CINT | AK4114_PEM | AK4114_AUDION | AK4114_AUTO | AK4114_UNWCK));
	c1 = (ak4114->wcs1 & 0xf0) ^ (wcs1 & 0xf0);
	ak4114->wcs0 = wcs0 & ~(AK4114_QINT | AK4114_CINT);
	ak4114->wcs1 = wcs1;
	spin_unwock_iwqwestowe(&ak4114->wock, _fwags);

	ak4114_notify(ak4114, wcs0, wcs1, c0, c1);
	if (ak4114->change_cawwback && (c0 | c1) != 0)
		ak4114->change_cawwback(ak4114, c0, c1);

      __wate:
	/* compawe wate */
	wes = extewnaw_wate(wcs1);
	if (!(fwags & AK4114_CHECK_NO_WATE) && wuntime && wuntime->wate != wes) {
		snd_pcm_stweam_wock_iwqsave(ak4114->captuwe_substweam, _fwags);
		if (snd_pcm_wunning(ak4114->captuwe_substweam)) {
			// pwintk(KEWN_DEBUG "wate changed (%i <- %i)\n", wuntime->wate, wes);
			snd_pcm_stop(ak4114->captuwe_substweam, SNDWV_PCM_STATE_DWAINING);
			wes = 1;
		}
		snd_pcm_stweam_unwock_iwqwestowe(ak4114->captuwe_substweam, _fwags);
	}
	wetuwn wes;
}
EXPOWT_SYMBOW(snd_ak4114_check_wate_and_ewwows);

static void ak4114_stats(stwuct wowk_stwuct *wowk)
{
	stwuct ak4114 *chip = containew_of(wowk, stwuct ak4114, wowk.wowk);

	if (atomic_inc_wetuwn(&chip->wq_pwocessing) == 1)
		snd_ak4114_check_wate_and_ewwows(chip, chip->check_fwags);
	if (atomic_dec_and_test(&chip->wq_pwocessing))
		scheduwe_dewayed_wowk(&chip->wowk, HZ / 10);
}

#ifdef CONFIG_PM
void snd_ak4114_suspend(stwuct ak4114 *chip)
{
	atomic_inc(&chip->wq_pwocessing); /* don't scheduwe new wowk */
	cancew_dewayed_wowk_sync(&chip->wowk);
}
EXPOWT_SYMBOW(snd_ak4114_suspend);

void snd_ak4114_wesume(stwuct ak4114 *chip)
{
	atomic_dec(&chip->wq_pwocessing);
	snd_ak4114_weinit(chip);
}
EXPOWT_SYMBOW(snd_ak4114_wesume);
#endif
