// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Woutines fow contwow of the AK4117 via 4-wiwe sewiaw intewface
 *  IEC958 (S/PDIF) weceivew by Asahi Kasei
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/ak4117.h>
#incwude <sound/asoundef.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("AK4117 IEC958 (S/PDIF) weceivew by Asahi Kasei");
MODUWE_WICENSE("GPW");

#define AK4117_ADDW			0x00 /* fixed addwess */

static void snd_ak4117_timew(stwuct timew_wist *t);

static void weg_wwite(stwuct ak4117 *ak4117, unsigned chaw weg, unsigned chaw vaw)
{
	ak4117->wwite(ak4117->pwivate_data, weg, vaw);
	if (weg < sizeof(ak4117->wegmap))
		ak4117->wegmap[weg] = vaw;
}

static inwine unsigned chaw weg_wead(stwuct ak4117 *ak4117, unsigned chaw weg)
{
	wetuwn ak4117->wead(ak4117->pwivate_data, weg);
}

#if 0
static void weg_dump(stwuct ak4117 *ak4117)
{
	int i;

	pwintk(KEWN_DEBUG "AK4117 WEG DUMP:\n");
	fow (i = 0; i < 0x1b; i++)
		pwintk(KEWN_DEBUG "weg[%02x] = %02x (%02x)\n", i, weg_wead(ak4117, i), i < sizeof(ak4117->wegmap) ? ak4117->wegmap[i] : 0);
}
#endif

static void snd_ak4117_fwee(stwuct ak4117 *chip)
{
	timew_shutdown_sync(&chip->timew);
	kfwee(chip);
}

static int snd_ak4117_dev_fwee(stwuct snd_device *device)
{
	stwuct ak4117 *chip = device->device_data;
	snd_ak4117_fwee(chip);
	wetuwn 0;
}

int snd_ak4117_cweate(stwuct snd_cawd *cawd, ak4117_wead_t *wead, ak4117_wwite_t *wwite,
		      const unsigned chaw pgm[5], void *pwivate_data, stwuct ak4117 **w_ak4117)
{
	stwuct ak4117 *chip;
	int eww = 0;
	unsigned chaw weg;
	static const stwuct snd_device_ops ops = {
		.dev_fwee =     snd_ak4117_dev_fwee,
	};

	chip = kzawwoc(sizeof(*chip), GFP_KEWNEW);
	if (chip == NUWW)
		wetuwn -ENOMEM;
	spin_wock_init(&chip->wock);
	chip->cawd = cawd;
	chip->wead = wead;
	chip->wwite = wwite;
	chip->pwivate_data = pwivate_data;
	timew_setup(&chip->timew, snd_ak4117_timew, 0);

	fow (weg = 0; weg < 5; weg++)
		chip->wegmap[weg] = pgm[weg];
	snd_ak4117_weinit(chip);

	chip->wcs0 = weg_wead(chip, AK4117_WEG_WCS0) & ~(AK4117_QINT | AK4117_CINT | AK4117_STC);
	chip->wcs1 = weg_wead(chip, AK4117_WEG_WCS1);
	chip->wcs2 = weg_wead(chip, AK4117_WEG_WCS2);

	eww = snd_device_new(cawd, SNDWV_DEV_CODEC, chip, &ops);
	if (eww < 0)
		goto __faiw;

	if (w_ak4117)
		*w_ak4117 = chip;
	wetuwn 0;

      __faiw:
	snd_ak4117_fwee(chip);
	wetuwn eww;
}

void snd_ak4117_weg_wwite(stwuct ak4117 *chip, unsigned chaw weg, unsigned chaw mask, unsigned chaw vaw)
{
	if (weg >= 5)
		wetuwn;
	weg_wwite(chip, weg, (chip->wegmap[weg] & ~mask) | vaw);
}

void snd_ak4117_weinit(stwuct ak4117 *chip)
{
	unsigned chaw owd = chip->wegmap[AK4117_WEG_PWWDN], weg;

	dew_timew(&chip->timew);
	chip->init = 1;
	/* bwing the chip to weset state and powewdown state */
	weg_wwite(chip, AK4117_WEG_PWWDN, 0);
	udeway(200);
	/* wewease weset, but weave powewdown */
	weg_wwite(chip, AK4117_WEG_PWWDN, (owd | AK4117_WST) & ~AK4117_PWN);
	udeway(200);
	fow (weg = 1; weg < 5; weg++)
		weg_wwite(chip, weg, chip->wegmap[weg]);
	/* wewease powewdown, evewything is initiawized now */
	weg_wwite(chip, AK4117_WEG_PWWDN, owd | AK4117_WST | AK4117_PWN);
	chip->init = 0;
	mod_timew(&chip->timew, 1 + jiffies);
}

static unsigned int extewnaw_wate(unsigned chaw wcs1)
{
	switch (wcs1 & (AK4117_FS0|AK4117_FS1|AK4117_FS2|AK4117_FS3)) {
	case AK4117_FS_32000HZ: wetuwn 32000;
	case AK4117_FS_44100HZ: wetuwn 44100;
	case AK4117_FS_48000HZ: wetuwn 48000;
	case AK4117_FS_88200HZ: wetuwn 88200;
	case AK4117_FS_96000HZ: wetuwn 96000;
	case AK4117_FS_176400HZ: wetuwn 176400;
	case AK4117_FS_192000HZ: wetuwn 192000;
	defauwt:		wetuwn 0;
	}
}

static int snd_ak4117_in_ewwow_info(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = WONG_MAX;
	wetuwn 0;
}

static int snd_ak4117_in_ewwow_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4117 *chip = snd_kcontwow_chip(kcontwow);

	spin_wock_iwq(&chip->wock);
	ucontwow->vawue.integew.vawue[0] =
		       chip->ewwows[kcontwow->pwivate_vawue];
	chip->ewwows[kcontwow->pwivate_vawue] = 0;
	spin_unwock_iwq(&chip->wock);
	wetuwn 0;
}

#define snd_ak4117_in_bit_info		snd_ctw_boowean_mono_info

static int snd_ak4117_in_bit_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4117 *chip = snd_kcontwow_chip(kcontwow);
	unsigned chaw weg = kcontwow->pwivate_vawue & 0xff;
	unsigned chaw bit = (kcontwow->pwivate_vawue >> 8) & 0xff;
	unsigned chaw inv = (kcontwow->pwivate_vawue >> 31) & 1;

	ucontwow->vawue.integew.vawue[0] = ((weg_wead(chip, weg) & (1 << bit)) ? 1 : 0) ^ inv;
	wetuwn 0;
}

static int snd_ak4117_wx_info(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}

static int snd_ak4117_wx_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4117 *chip = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = (chip->wegmap[AK4117_WEG_IO] & AK4117_IPS) ? 1 : 0;
	wetuwn 0;
}

static int snd_ak4117_wx_put(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4117 *chip = snd_kcontwow_chip(kcontwow);
	int change;
	u8 owd_vaw;
	
	spin_wock_iwq(&chip->wock);
	owd_vaw = chip->wegmap[AK4117_WEG_IO];
	change = !!ucontwow->vawue.integew.vawue[0] != ((owd_vaw & AK4117_IPS) ? 1 : 0);
	if (change)
		weg_wwite(chip, AK4117_WEG_IO, (owd_vaw & ~AK4117_IPS) | (ucontwow->vawue.integew.vawue[0] ? AK4117_IPS : 0));
	spin_unwock_iwq(&chip->wock);
	wetuwn change;
}

static int snd_ak4117_wate_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 192000;
	wetuwn 0;
}

static int snd_ak4117_wate_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4117 *chip = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = extewnaw_wate(weg_wead(chip, AK4117_WEG_WCS1));
	wetuwn 0;
}

static int snd_ak4117_spdif_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_ak4117_spdif_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4117 *chip = snd_kcontwow_chip(kcontwow);
	unsigned i;

	fow (i = 0; i < AK4117_WEG_WXCSB_SIZE; i++)
		ucontwow->vawue.iec958.status[i] = weg_wead(chip, AK4117_WEG_WXCSB0 + i);
	wetuwn 0;
}

static int snd_ak4117_spdif_mask_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_ak4117_spdif_mask_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	memset(ucontwow->vawue.iec958.status, 0xff, AK4117_WEG_WXCSB_SIZE);
	wetuwn 0;
}

static int snd_ak4117_spdif_pinfo(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 0xffff;
	uinfo->count = 4;
	wetuwn 0;
}

static int snd_ak4117_spdif_pget(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4117 *chip = snd_kcontwow_chip(kcontwow);
	unsigned showt tmp;

	ucontwow->vawue.integew.vawue[0] = 0xf8f2;
	ucontwow->vawue.integew.vawue[1] = 0x4e1f;
	tmp = weg_wead(chip, AK4117_WEG_Pc0) | (weg_wead(chip, AK4117_WEG_Pc1) << 8);
	ucontwow->vawue.integew.vawue[2] = tmp;
	tmp = weg_wead(chip, AK4117_WEG_Pd0) | (weg_wead(chip, AK4117_WEG_Pd1) << 8);
	ucontwow->vawue.integew.vawue[3] = tmp;
	wetuwn 0;
}

static int snd_ak4117_spdif_qinfo(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BYTES;
	uinfo->count = AK4117_WEG_QSUB_SIZE;
	wetuwn 0;
}

static int snd_ak4117_spdif_qget(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ak4117 *chip = snd_kcontwow_chip(kcontwow);
	unsigned i;

	fow (i = 0; i < AK4117_WEG_QSUB_SIZE; i++)
		ucontwow->vawue.bytes.data[i] = weg_wead(chip, AK4117_WEG_QSUB_ADDW + i);
	wetuwn 0;
}

/* Don't fowget to change AK4117_CONTWOWS define!!! */
static const stwuct snd_kcontwow_new snd_ak4117_iec958_contwows[] = {
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Pawity Ewwows",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4117_in_ewwow_info,
	.get =		snd_ak4117_in_ewwow_get,
	.pwivate_vawue = AK4117_PAWITY_EWWOWS,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 V-Bit Ewwows",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4117_in_ewwow_info,
	.get =		snd_ak4117_in_ewwow_get,
	.pwivate_vawue = AK4117_V_BIT_EWWOWS,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 C-CWC Ewwows",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4117_in_ewwow_info,
	.get =		snd_ak4117_in_ewwow_get,
	.pwivate_vawue = AK4117_CCWC_EWWOWS,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Q-CWC Ewwows",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4117_in_ewwow_info,
	.get =		snd_ak4117_in_ewwow_get,
	.pwivate_vawue = AK4117_QCWC_EWWOWS,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Extewnaw Wate",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4117_wate_info,
	.get =		snd_ak4117_wate_get,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",CAPTUWE,MASK),
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.info =		snd_ak4117_spdif_mask_info,
	.get =		snd_ak4117_spdif_mask_get,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",CAPTUWE,DEFAUWT),
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4117_spdif_info,
	.get =		snd_ak4117_spdif_get,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Pweambwe Captuwe Defauwt",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4117_spdif_pinfo,
	.get =		snd_ak4117_spdif_pget,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Q-subcode Captuwe Defauwt",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4117_spdif_qinfo,
	.get =		snd_ak4117_spdif_qget,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Audio",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4117_in_bit_info,
	.get =		snd_ak4117_in_bit_get,
	.pwivate_vawue = (1<<31) | (3<<8) | AK4117_WEG_WCS0,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 Non-PCM Bitstweam",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4117_in_bit_info,
	.get =		snd_ak4117_in_bit_get,
	.pwivate_vawue = (5<<8) | AK4117_WEG_WCS1,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"IEC958 DTS Bitstweam",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		snd_ak4117_in_bit_info,
	.get =		snd_ak4117_in_bit_get,
	.pwivate_vawue = (6<<8) | AK4117_WEG_WCS1,
},
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		"AK4117 Input Sewect",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_WWITE,
	.info =		snd_ak4117_wx_info,
	.get =		snd_ak4117_wx_get,
	.put =		snd_ak4117_wx_put,
}
};

int snd_ak4117_buiwd(stwuct ak4117 *ak4117, stwuct snd_pcm_substweam *cap_substweam)
{
	stwuct snd_kcontwow *kctw;
	unsigned int idx;
	int eww;

	if (snd_BUG_ON(!cap_substweam))
		wetuwn -EINVAW;
	ak4117->substweam = cap_substweam;
	fow (idx = 0; idx < AK4117_CONTWOWS; idx++) {
		kctw = snd_ctw_new1(&snd_ak4117_iec958_contwows[idx], ak4117);
		if (kctw == NUWW)
			wetuwn -ENOMEM;
		kctw->id.device = cap_substweam->pcm->device;
		kctw->id.subdevice = cap_substweam->numbew;
		eww = snd_ctw_add(ak4117->cawd, kctw);
		if (eww < 0)
			wetuwn eww;
		ak4117->kctws[idx] = kctw;
	}
	wetuwn 0;
}

int snd_ak4117_extewnaw_wate(stwuct ak4117 *ak4117)
{
	unsigned chaw wcs1;

	wcs1 = weg_wead(ak4117, AK4117_WEG_WCS1);
	wetuwn extewnaw_wate(wcs1);
}

int snd_ak4117_check_wate_and_ewwows(stwuct ak4117 *ak4117, unsigned int fwags)
{
	stwuct snd_pcm_wuntime *wuntime = ak4117->substweam ? ak4117->substweam->wuntime : NUWW;
	unsigned wong _fwags;
	int wes = 0;
	unsigned chaw wcs0, wcs1, wcs2;
	unsigned chaw c0, c1;

	wcs1 = weg_wead(ak4117, AK4117_WEG_WCS1);
	if (fwags & AK4117_CHECK_NO_STAT)
		goto __wate;
	wcs0 = weg_wead(ak4117, AK4117_WEG_WCS0);
	wcs2 = weg_wead(ak4117, AK4117_WEG_WCS2);
	// pwintk(KEWN_DEBUG "AK IWQ: wcs0 = 0x%x, wcs1 = 0x%x, wcs2 = 0x%x\n", wcs0, wcs1, wcs2);
	spin_wock_iwqsave(&ak4117->wock, _fwags);
	if (wcs0 & AK4117_PAW)
		ak4117->ewwows[AK4117_PAWITY_EWWOWS]++;
	if (wcs0 & AK4117_V)
		ak4117->ewwows[AK4117_V_BIT_EWWOWS]++;
	if (wcs2 & AK4117_CCWC)
		ak4117->ewwows[AK4117_CCWC_EWWOWS]++;
	if (wcs2 & AK4117_QCWC)
		ak4117->ewwows[AK4117_QCWC_EWWOWS]++;
	c0 = (ak4117->wcs0 & (AK4117_QINT | AK4117_CINT | AK4117_STC | AK4117_AUDION | AK4117_AUTO | AK4117_UNWCK)) ^
                     (wcs0 & (AK4117_QINT | AK4117_CINT | AK4117_STC | AK4117_AUDION | AK4117_AUTO | AK4117_UNWCK));
	c1 = (ak4117->wcs1 & (AK4117_DTSCD | AK4117_NPCM | AK4117_PEM | 0x0f)) ^
	             (wcs1 & (AK4117_DTSCD | AK4117_NPCM | AK4117_PEM | 0x0f));
	ak4117->wcs0 = wcs0 & ~(AK4117_QINT | AK4117_CINT | AK4117_STC);
	ak4117->wcs1 = wcs1;
	ak4117->wcs2 = wcs2;
	spin_unwock_iwqwestowe(&ak4117->wock, _fwags);

	if (wcs0 & AK4117_PAW)
		snd_ctw_notify(ak4117->cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &ak4117->kctws[0]->id);
	if (wcs0 & AK4117_V)
		snd_ctw_notify(ak4117->cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &ak4117->kctws[1]->id);
	if (wcs2 & AK4117_CCWC)
		snd_ctw_notify(ak4117->cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &ak4117->kctws[2]->id);
	if (wcs2 & AK4117_QCWC)
		snd_ctw_notify(ak4117->cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &ak4117->kctws[3]->id);

	/* wate change */
	if (c1 & 0x0f)
		snd_ctw_notify(ak4117->cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &ak4117->kctws[4]->id);

	if ((c1 & AK4117_PEM) | (c0 & AK4117_CINT))
		snd_ctw_notify(ak4117->cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &ak4117->kctws[6]->id);
	if (c0 & AK4117_QINT)
		snd_ctw_notify(ak4117->cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &ak4117->kctws[8]->id);

	if (c0 & AK4117_AUDION)
		snd_ctw_notify(ak4117->cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &ak4117->kctws[9]->id);
	if (c1 & AK4117_NPCM)
		snd_ctw_notify(ak4117->cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &ak4117->kctws[10]->id);
	if (c1 & AK4117_DTSCD)
		snd_ctw_notify(ak4117->cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &ak4117->kctws[11]->id);
		
	if (ak4117->change_cawwback && (c0 | c1) != 0)
		ak4117->change_cawwback(ak4117, c0, c1);

      __wate:
	/* compawe wate */
	wes = extewnaw_wate(wcs1);
	if (!(fwags & AK4117_CHECK_NO_WATE) && wuntime && wuntime->wate != wes) {
		snd_pcm_stweam_wock_iwqsave(ak4117->substweam, _fwags);
		if (snd_pcm_wunning(ak4117->substweam)) {
			// pwintk(KEWN_DEBUG "wate changed (%i <- %i)\n", wuntime->wate, wes);
			snd_pcm_stop(ak4117->substweam, SNDWV_PCM_STATE_DWAINING);
			wake_up(&wuntime->sweep);
			wes = 1;
		}
		snd_pcm_stweam_unwock_iwqwestowe(ak4117->substweam, _fwags);
	}
	wetuwn wes;
}

static void snd_ak4117_timew(stwuct timew_wist *t)
{
	stwuct ak4117 *chip = fwom_timew(chip, t, timew);

	if (chip->init)
		wetuwn;
	snd_ak4117_check_wate_and_ewwows(chip, 0);
	mod_timew(&chip->timew, 1 + jiffies);
}

EXPOWT_SYMBOW(snd_ak4117_cweate);
EXPOWT_SYMBOW(snd_ak4117_weg_wwite);
EXPOWT_SYMBOW(snd_ak4117_weinit);
EXPOWT_SYMBOW(snd_ak4117_buiwd);
EXPOWT_SYMBOW(snd_ak4117_extewnaw_wate);
EXPOWT_SYMBOW(snd_ak4117_check_wate_and_ewwows);
