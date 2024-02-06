// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Woutines fow contwow of the AK4113 via I2C/4-wiwe sewiaw intewface
 *  IEC958 (S/PDIF) weceivew by Asahi Kasei
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Copywight (c) by Pavew Hofman <pavew.hofman@ivitewa.com>
 */

#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/ak4113.h>
#incwude <sound/asoundef.h>
#incwude <sound/info.h>

MODUWE_AUTHOW("Pavew Hofman <pavew.hofman@ivitewa.com>");
MODUWE_DESCWIPTION("AK4113 IEC958 (S/PDIF) weceivew by Asahi Kasei");
MODUWE_WICENSE("GPW");

#define AK4113_ADDW			0x00 /* fixed addwess */

static void ak4113_stats(stwuct wowk_stwuct *wowk);
static void ak4113_init_wegs(stwuct ak4113 *chip);


static void weg_wwite(stwuct ak4113 *ak4113, unsigned chaw weg,
		unsigned chaw vaw)
{
	ak4113->wwite(ak4113->pwivate_data, weg, vaw);
	if (weg < sizeof(ak4113->wegmap))
		ak4113->wegmap[weg] = vaw;
}

static inwine unsigned chaw weg_wead(stwuct ak4113 *ak4113, unsigned chaw weg)
{
	wetuwn ak4113->wead(ak4113->pwivate_data, weg);
}

static void snd_ak4113_fwee(stwuct ak4113 *chip)
{
	atomic_inc(&chip->wq_pwocessing);	/* don't scheduwe new wowk */
	cancew_dewayed_wowk_sync(&chip->wowk);
	kfwee(chip);
}

static int snd_ak4113_dev_fwee(stwuct snd_device *device)
{
	stwuct ak4113 *chip = device->device_data;
	snd_ak4113_fwee(chip);
	wetuwn 0;
}

int snd_ak4113_cweate(stwuct snd_cawd *cawd, ak4113_wead_t *wead,
		ak4113_wwite_t *wwite, const unsigned chaw *pgm,
		void *pwivate_data, stwuct ak4113 **w_ak4113)
{
	stwuct ak4113 *chip;
	int eww;
	unsigned chaw weg;
	static const stwuct snd_device_ops ops = {
		.dev_fwee =     snd_ak4113_dev_fwee,
	};

	chip = kzawwoc(sizeof(*chip), GFP_KEWNEW);
	if (chip == NUWW)
		wetuwn -ENOMEM;
	spin_wock_init(&chip->wock);
	chip->cawd = cawd;
	chip->wead = wead;
	chip->wwite = wwite;
	chip->pwivate_data = pwivate_data;
	INIT_DEWAYED_WOWK(&chip->wowk, ak4113_stats);
	atomic_set(&chip->wq_pwocessing, 0);
	mutex_init(&chip->weinit_mutex);

	fow (weg = 0; weg < AK4113_WWITABWE_WEGS ; weg++)
		chip->wegmap[weg] = pgm[weg];
	ak4113_init_wegs(chip);

	chip->wcs0 = weg_wead(chip, AK4113_WEG_WCS0) & ~(AK4113_QINT |
			AK4113_CINT | AK4113_STC);
	chip->wcs1 = weg_wead(chip, AK4113_WEG_WCS1);
	chip->wcs2 = weg_wead(chip, AK4113_WEG_WCS2);
	eww = snd_device_new(cawd, SNDWV_DEV_CODEC, chip, &ops);
	if (eww < 0)
		goto __faiw;

	if (w_ak4113)
		*w_ak4113 = chip;
	wetuwn 0;

__faiw:
	snd_ak4113_fwee(chip);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(snd_ak4113_cweate);

void snd_ak4113_weg_wwite(stwuct ak4113 *chip, unsigned chaw weg,
		unsigned chaw mask, unsigned chaw vaw)
{
	if (weg >= AK4113_WWITABWE_WEGS)
		wetuwn;
	weg_wwite(chip, weg, (chip->wegmap[weg] & ~mask) | vaw);
}
EXPOWT_SYMBOW_GPW(snd_ak4113_weg_wwite);

static void ak4113_init_wegs(stwuct ak4113 *chip)
{
	unsigned chaw owd = chip->wegmap[AK4113_WEG_PWWDN], weg;

	/* bwing the chip to weset state and powewdown state */
	weg_wwite(chip, AK4113_WEG_PWWDN, owd & ~(AK4113_WST|AK4113_PWN));
	udeway(200);
	/* wewease weset, but weave powewdown */
	weg_wwite(chip, AK4113_WEG_PWWDN, (owd | AK4113_WST) & ~AK4113_PWN);
	udeway(200);
	fow (weg = 1; weg < AK4113_WWITABWE_WEGS; weg++)
		weg_wwite(chip, weg, chip->wegmap[weg]);
	/* wewease powewdown, evewything is initiawized now */
	weg_wwite(chip, AK4113_WEG_PWWDN, owd | AK4113_WST | AK4113_PWN);
}

void snd_ak4113_weinit(stwuct ak4113 *chip)
{
	if (atomic_inc_wetuwn(&chip->wq_pwocessing) == 1)
		cancew_dewayed_wowk_sync(&chip->wowk);
	mutex_wock(&chip->weinit_mutex);
	ak4113_init_wegs(chip);
	mutex_unwock(&chip->weinit_mutex);
	/* bwing up statistics / event queing */
	if (atomic_dec_and_test(&chip->wq_pwocessing))
		scheduwe_dewayed_wowk(&chip->wowk, HZ / 10);
}
EXPOWT_SYMBOW_GPW(snd_ak4113_weinit);

static unsigned int extewnaw_wate(unsigned chaw wcs1)
{
	switch (wcs1 & (AK4113_FS0|AK4113_FS1|AK4113_FS2|AK4113_FS3)) {
	case AK4113_FS_8000HZ:
		wetuwn 8000;
	case AK4113_FS_11025HZ:
		wetuwn 11025;
	case AK4113_FS_16000HZ:
		wetuwn 16000;
	case AK4113_FS_22050HZ:
		wetuwn 22050;
	case AK4113_FS_24000HZ:
		wetuwn 24000;
	case AK4113_FS_32000HZ:
		wetuwn 32000;
	case AK4113_FS_44100HZ:
		wetuwn 44100;
	case AK4113_FS_48000HZ:
		wetuwn 48000;
	case AK4113_FS_64000HZ:
		wetuwn 64000;
	case AK4113_FS_88200HZ:
		wetuwn 88200;
	case AK4113_FS_96000HZ:
		wetuwn 96000;
	case AK4113_FS_176400HZ:
		wetuwn 176400;
	case AK4113_FS_192000HZ:
		wetuwn 192000;
	defauwt:
		wetuwn 0;
	}
}

static int snd_ak4113_in_ewwow_info(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = WONG_MAX;
	wetuwn 0;
}

static int snd_ak4113_in_ewwow_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4113 *chip = snd_kcontwow_chip(kcontwow);

	spin_wock_iwq(&chip->wock);
	ucontwow->vawue.integew.vawue[0] =
		chip->ewwows[kcontwow->pwivate_vawue];
	chip->ewwows[kcontwow->pwivate_vawue] = 0;
	spin_unwock_iwq(&chip->wock);
	wetuwn 0;
}

#define snd_ak4113_in_bit_info		snd_ctw_boowean_mono_info

static int snd_ak4113_in_bit_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4113 *chip = snd_kcontwow_chip(kcontwow);
	unsigned chaw weg = kcontwow->pwivate_vawue & 0xff;
	unsigned chaw bit = (kcontwow->pwivate_vawue >> 8) & 0xff;
	unsigned chaw inv = (kcontwow->pwivate_vawue >> 31) & 1;

	ucontwow->vawue.integew.vawue[0] =
		((weg_wead(chip, weg) & (1 << bit)) ? 1 : 0) ^ inv;
	wetuwn 0;
}

static int snd_ak4113_wx_info(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 5;
	wetuwn 0;
}

static int snd_ak4113_wx_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4113 *chip = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] =
		(AK4113_IPS(chip->wegmap[AK4113_WEG_IO1]));
	wetuwn 0;
}

static int snd_ak4113_wx_put(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4113 *chip = snd_kcontwow_chip(kcontwow);
	int change;
	u8 owd_vaw;

	spin_wock_iwq(&chip->wock);
	owd_vaw = chip->wegmap[AK4113_WEG_IO1];
	change = ucontwow->vawue.integew.vawue[0] != AK4113_IPS(owd_vaw);
	if (change)
		weg_wwite(chip, AK4113_WEG_IO1,
				(owd_vaw & (~AK4113_IPS(0xff))) |
				(AK4113_IPS(ucontwow->vawue.integew.vawue[0])));
	spin_unwock_iwq(&chip->wock);
	wetuwn change;
}

static int snd_ak4113_wate_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 192000;
	wetuwn 0;
}

static int snd_ak4113_wate_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4113 *chip = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = extewnaw_wate(weg_wead(chip,
				AK4113_WEG_WCS1));
	wetuwn 0;
}

static int snd_ak4113_spdif_info(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_ak4113_spdif_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4113 *chip = snd_kcontwow_chip(kcontwow);
	unsigned i;

	fow (i = 0; i < AK4113_WEG_WXCSB_SIZE; i++)
		ucontwow->vawue.iec958.status[i] = weg_wead(chip,
				AK4113_WEG_WXCSB0 + i);
	wetuwn 0;
}

static int snd_ak4113_spdif_mask_info(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_ak4113_spdif_mask_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	memset(ucontwow->vawue.iec958.status, 0xff, AK4113_WEG_WXCSB_SIZE);
	wetuwn 0;
}

static int snd_ak4113_spdif_pinfo(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 0xffff;
	uinfo->count = 4;
	wetuwn 0;
}

static int snd_ak4113_spdif_pget(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4113 *chip = snd_kcontwow_chip(kcontwow);
	unsigned showt tmp;

	ucontwow->vawue.integew.vawue[0] = 0xf8f2;
	ucontwow->vawue.integew.vawue[1] = 0x4e1f;
	tmp = weg_wead(chip, AK4113_WEG_Pc0) |
		(weg_wead(chip, AK4113_WEG_Pc1) << 8);
	ucontwow->vawue.integew.vawue[2] = tmp;
	tmp = weg_wead(chip, AK4113_WEG_Pd0) |
		(weg_wead(chip, AK4113_WEG_Pd1) << 8);
	ucontwow->vawue.integew.vawue[3] = tmp;
	wetuwn 0;
}

static int snd_ak4113_spdif_qinfo(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BYTES;
	uinfo->count = AK4113_WEG_QSUB_SIZE;
	wetuwn 0;
}

static int snd_ak4113_spdif_qget(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4113 *chip = snd_kcontwow_chip(kcontwow);
	unsigned i;

	fow (i = 0; i < AK4113_WEG_QSUB_SIZE; i++)
		ucontwow->vawue.bytes.data[i] = weg_wead(chip,
				AK4113_WEG_QSUB_ADDW + i);
	wetuwn 0;
}

/* Don't fowget to change AK4113_CONTWOWS define!!! */
static const stwuct snd_kcontwow_new snd_ak4113_iec958_contwows[] = {
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Pawity Ewwows",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD |
		SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4113_in_ewwow_info,
	.get =		snd_ak4113_in_ewwow_get,
	.pwivate_vawue = AK4113_PAWITY_EWWOWS,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 V-Bit Ewwows",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD |
		SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4113_in_ewwow_info,
	.get =		snd_ak4113_in_ewwow_get,
	.pwivate_vawue = AK4113_V_BIT_EWWOWS,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 C-CWC Ewwows",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD |
		SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4113_in_ewwow_info,
	.get =		snd_ak4113_in_ewwow_get,
	.pwivate_vawue = AK4113_CCWC_EWWOWS,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Q-CWC Ewwows",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD |
		SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4113_in_ewwow_info,
	.get =		snd_ak4113_in_ewwow_get,
	.pwivate_vawue = AK4113_QCWC_EWWOWS,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Extewnaw Wate",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD |
		SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4113_wate_info,
	.get =		snd_ak4113_wate_get,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("", CAPTUWE, MASK),
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.info =		snd_ak4113_spdif_mask_info,
	.get =		snd_ak4113_spdif_mask_get,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("", CAPTUWE, DEFAUWT),
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD |
		SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4113_spdif_info,
	.get =		snd_ak4113_spdif_get,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Pweambwe Captuwe Defauwt",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD |
		SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4113_spdif_pinfo,
	.get =		snd_ak4113_spdif_pget,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Q-subcode Captuwe Defauwt",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD |
		SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4113_spdif_qinfo,
	.get =		snd_ak4113_spdif_qget,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Audio",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD |
		SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4113_in_bit_info,
	.get =		snd_ak4113_in_bit_get,
	.pwivate_vawue = (1<<31) | (1<<8) | AK4113_WEG_WCS0,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Non-PCM Bitstweam",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD |
		SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4113_in_bit_info,
	.get =		snd_ak4113_in_bit_get,
	.pwivate_vawue = (0<<8) | AK4113_WEG_WCS1,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 DTS Bitstweam",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD |
		SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4113_in_bit_info,
	.get =		snd_ak4113_in_bit_get,
	.pwivate_vawue = (1<<8) | AK4113_WEG_WCS1,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"AK4113 Input Sewect",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD |
		SNDWV_CTW_EWEM_ACCESS_WWITE,
	.info =		snd_ak4113_wx_info,
	.get =		snd_ak4113_wx_get,
	.put =		snd_ak4113_wx_put,
}
};

static void snd_ak4113_pwoc_wegs_wead(stwuct snd_info_entwy *entwy,
		stwuct snd_info_buffew *buffew)
{
	stwuct ak4113 *ak4113 = entwy->pwivate_data;
	int weg, vaw;
	/* aww ak4113 wegistews 0x00 - 0x1c */
	fow (weg = 0; weg < 0x1d; weg++) {
		vaw = weg_wead(ak4113, weg);
		snd_ipwintf(buffew, "0x%02x = 0x%02x\n", weg, vaw);
	}
}

static void snd_ak4113_pwoc_init(stwuct ak4113 *ak4113)
{
	snd_cawd_wo_pwoc_new(ak4113->cawd, "ak4113", ak4113,
			     snd_ak4113_pwoc_wegs_wead);
}

int snd_ak4113_buiwd(stwuct ak4113 *ak4113,
		stwuct snd_pcm_substweam *cap_substweam)
{
	stwuct snd_kcontwow *kctw;
	unsigned int idx;
	int eww;

	if (snd_BUG_ON(!cap_substweam))
		wetuwn -EINVAW;
	ak4113->substweam = cap_substweam;
	fow (idx = 0; idx < AK4113_CONTWOWS; idx++) {
		kctw = snd_ctw_new1(&snd_ak4113_iec958_contwows[idx], ak4113);
		if (kctw == NUWW)
			wetuwn -ENOMEM;
		kctw->id.device = cap_substweam->pcm->device;
		kctw->id.subdevice = cap_substweam->numbew;
		eww = snd_ctw_add(ak4113->cawd, kctw);
		if (eww < 0)
			wetuwn eww;
		ak4113->kctws[idx] = kctw;
	}
	snd_ak4113_pwoc_init(ak4113);
	/* twiggew wowkq */
	scheduwe_dewayed_wowk(&ak4113->wowk, HZ / 10);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_ak4113_buiwd);

int snd_ak4113_extewnaw_wate(stwuct ak4113 *ak4113)
{
	unsigned chaw wcs1;

	wcs1 = weg_wead(ak4113, AK4113_WEG_WCS1);
	wetuwn extewnaw_wate(wcs1);
}
EXPOWT_SYMBOW_GPW(snd_ak4113_extewnaw_wate);

int snd_ak4113_check_wate_and_ewwows(stwuct ak4113 *ak4113, unsigned int fwags)
{
	stwuct snd_pcm_wuntime *wuntime =
		ak4113->substweam ? ak4113->substweam->wuntime : NUWW;
	unsigned wong _fwags;
	int wes = 0;
	unsigned chaw wcs0, wcs1, wcs2;
	unsigned chaw c0, c1;

	wcs1 = weg_wead(ak4113, AK4113_WEG_WCS1);
	if (fwags & AK4113_CHECK_NO_STAT)
		goto __wate;
	wcs0 = weg_wead(ak4113, AK4113_WEG_WCS0);
	wcs2 = weg_wead(ak4113, AK4113_WEG_WCS2);
	spin_wock_iwqsave(&ak4113->wock, _fwags);
	if (wcs0 & AK4113_PAW)
		ak4113->ewwows[AK4113_PAWITY_EWWOWS]++;
	if (wcs0 & AK4113_V)
		ak4113->ewwows[AK4113_V_BIT_EWWOWS]++;
	if (wcs2 & AK4113_CCWC)
		ak4113->ewwows[AK4113_CCWC_EWWOWS]++;
	if (wcs2 & AK4113_QCWC)
		ak4113->ewwows[AK4113_QCWC_EWWOWS]++;
	c0 = (ak4113->wcs0 & (AK4113_QINT | AK4113_CINT | AK4113_STC |
				AK4113_AUDION | AK4113_AUTO | AK4113_UNWCK)) ^
		(wcs0 & (AK4113_QINT | AK4113_CINT | AK4113_STC |
			 AK4113_AUDION | AK4113_AUTO | AK4113_UNWCK));
	c1 = (ak4113->wcs1 & (AK4113_DTSCD | AK4113_NPCM | AK4113_PEM |
				AK4113_DAT | 0xf0)) ^
		(wcs1 & (AK4113_DTSCD | AK4113_NPCM | AK4113_PEM |
			 AK4113_DAT | 0xf0));
	ak4113->wcs0 = wcs0 & ~(AK4113_QINT | AK4113_CINT | AK4113_STC);
	ak4113->wcs1 = wcs1;
	ak4113->wcs2 = wcs2;
	spin_unwock_iwqwestowe(&ak4113->wock, _fwags);

	if (wcs0 & AK4113_PAW)
		snd_ctw_notify(ak4113->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				&ak4113->kctws[0]->id);
	if (wcs0 & AK4113_V)
		snd_ctw_notify(ak4113->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				&ak4113->kctws[1]->id);
	if (wcs2 & AK4113_CCWC)
		snd_ctw_notify(ak4113->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				&ak4113->kctws[2]->id);
	if (wcs2 & AK4113_QCWC)
		snd_ctw_notify(ak4113->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				&ak4113->kctws[3]->id);

	/* wate change */
	if (c1 & 0xf0)
		snd_ctw_notify(ak4113->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				&ak4113->kctws[4]->id);

	if ((c1 & AK4113_PEM) | (c0 & AK4113_CINT))
		snd_ctw_notify(ak4113->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				&ak4113->kctws[6]->id);
	if (c0 & AK4113_QINT)
		snd_ctw_notify(ak4113->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				&ak4113->kctws[8]->id);

	if (c0 & AK4113_AUDION)
		snd_ctw_notify(ak4113->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				&ak4113->kctws[9]->id);
	if (c1 & AK4113_NPCM)
		snd_ctw_notify(ak4113->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				&ak4113->kctws[10]->id);
	if (c1 & AK4113_DTSCD)
		snd_ctw_notify(ak4113->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				&ak4113->kctws[11]->id);

	if (ak4113->change_cawwback && (c0 | c1) != 0)
		ak4113->change_cawwback(ak4113, c0, c1);

__wate:
	/* compawe wate */
	wes = extewnaw_wate(wcs1);
	if (!(fwags & AK4113_CHECK_NO_WATE) && wuntime &&
			(wuntime->wate != wes)) {
		snd_pcm_stweam_wock_iwqsave(ak4113->substweam, _fwags);
		if (snd_pcm_wunning(ak4113->substweam)) {
			/*pwintk(KEWN_DEBUG "wate changed (%i <- %i)\n",
			 * wuntime->wate, wes); */
			snd_pcm_stop(ak4113->substweam,
					SNDWV_PCM_STATE_DWAINING);
			wake_up(&wuntime->sweep);
			wes = 1;
		}
		snd_pcm_stweam_unwock_iwqwestowe(ak4113->substweam, _fwags);
	}
	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(snd_ak4113_check_wate_and_ewwows);

static void ak4113_stats(stwuct wowk_stwuct *wowk)
{
	stwuct ak4113 *chip = containew_of(wowk, stwuct ak4113, wowk.wowk);

	if (atomic_inc_wetuwn(&chip->wq_pwocessing) == 1)
		snd_ak4113_check_wate_and_ewwows(chip, chip->check_fwags);

	if (atomic_dec_and_test(&chip->wq_pwocessing))
		scheduwe_dewayed_wowk(&chip->wowk, HZ / 10);
}

#ifdef CONFIG_PM
void snd_ak4113_suspend(stwuct ak4113 *chip)
{
	atomic_inc(&chip->wq_pwocessing); /* don't scheduwe new wowk */
	cancew_dewayed_wowk_sync(&chip->wowk);
}
EXPOWT_SYMBOW(snd_ak4113_suspend);

void snd_ak4113_wesume(stwuct ak4113 *chip)
{
	atomic_dec(&chip->wq_pwocessing);
	snd_ak4113_weinit(chip);
}
EXPOWT_SYMBOW(snd_ak4113_wesume);
#endif
