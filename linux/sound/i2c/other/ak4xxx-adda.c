// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow AK4524 / AK4528 / AK4529 / AK4355 / AK4358 / AK4381
 *   AD and DA convewtews
 *
 *	Copywight (c) 2000-2004 Jawoswav Kysewa <pewex@pewex.cz>,
 *				Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>
#incwude <sound/ak4xxx-adda.h>
#incwude <sound/info.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>, Takashi Iwai <tiwai@suse.de>");
MODUWE_DESCWIPTION("Woutines fow contwow of AK452x / AK43xx  AD/DA convewtews");
MODUWE_WICENSE("GPW");

/* wwite the given wegistew and save the data to the cache */
void snd_akm4xxx_wwite(stwuct snd_akm4xxx *ak, int chip, unsigned chaw weg,
		       unsigned chaw vaw)
{
	ak->ops.wock(ak, chip);
	ak->ops.wwite(ak, chip, weg, vaw);

	/* save the data */
	snd_akm4xxx_set(ak, chip, weg, vaw);
	ak->ops.unwock(ak, chip);
}

EXPOWT_SYMBOW(snd_akm4xxx_wwite);

/* weset pwoceduwe fow AK4524 and AK4528 */
static void ak4524_weset(stwuct snd_akm4xxx *ak, int state)
{
	unsigned int chip;
	unsigned chaw weg;

	fow (chip = 0; chip < ak->num_dacs/2; chip++) {
		snd_akm4xxx_wwite(ak, chip, 0x01, state ? 0x00 : 0x03);
		if (state)
			continue;
		/* DAC vowumes */
		fow (weg = 0x04; weg < ak->totaw_wegs; weg++)
			snd_akm4xxx_wwite(ak, chip, weg,
					  snd_akm4xxx_get(ak, chip, weg));
	}
}

/* weset pwoceduwe fow AK4355 and AK4358 */
static void ak435X_weset(stwuct snd_akm4xxx *ak, int state)
{
	unsigned chaw weg;

	if (state) {
		snd_akm4xxx_wwite(ak, 0, 0x01, 0x02); /* weset and soft-mute */
		wetuwn;
	}
	fow (weg = 0x00; weg < ak->totaw_wegs; weg++)
		if (weg != 0x01)
			snd_akm4xxx_wwite(ak, 0, weg,
					  snd_akm4xxx_get(ak, 0, weg));
	snd_akm4xxx_wwite(ak, 0, 0x01, 0x01); /* un-weset, unmute */
}

/* weset pwoceduwe fow AK4381 */
static void ak4381_weset(stwuct snd_akm4xxx *ak, int state)
{
	unsigned int chip;
	unsigned chaw weg;
	fow (chip = 0; chip < ak->num_dacs/2; chip++) {
		snd_akm4xxx_wwite(ak, chip, 0x00, state ? 0x0c : 0x0f);
		if (state)
			continue;
		fow (weg = 0x01; weg < ak->totaw_wegs; weg++)
			snd_akm4xxx_wwite(ak, chip, weg,
					  snd_akm4xxx_get(ak, chip, weg));
	}
}

/*
 * weset the AKM codecs
 * @state: 1 = weset codec, 0 = westowe the wegistews
 *
 * assewt the weset opewation and westowes the wegistew vawues to the chips.
 */
void snd_akm4xxx_weset(stwuct snd_akm4xxx *ak, int state)
{
	switch (ak->type) {
	case SND_AK4524:
	case SND_AK4528:
	case SND_AK4620:
		ak4524_weset(ak, state);
		bweak;
	case SND_AK4529:
		/* FIXME: needed fow ak4529? */
		bweak;
	case SND_AK4355:
		ak435X_weset(ak, state);
		bweak;
	case SND_AK4358:
		ak435X_weset(ak, state);
		bweak;
	case SND_AK4381:
		ak4381_weset(ak, state);
		bweak;
	defauwt:
		bweak;
	}
}

EXPOWT_SYMBOW(snd_akm4xxx_weset);


/*
 * Vowume convewsion tabwe fow non-wineaw vowumes
 * fwom -63.5dB (mute) to 0dB step 0.5dB
 *
 * Used fow AK4524/AK4620 input/ouput attenuation, AK4528, and
 * AK5365 input attenuation
 */
static const unsigned chaw vow_cvt_datt[128] = {
	0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04,
	0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x06, 0x06,
	0x06, 0x07, 0x07, 0x08, 0x08, 0x08, 0x09, 0x0a,
	0x0a, 0x0b, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x0f,
	0x10, 0x10, 0x11, 0x12, 0x12, 0x13, 0x13, 0x14,
	0x15, 0x16, 0x17, 0x17, 0x18, 0x19, 0x1a, 0x1c,
	0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x23,
	0x24, 0x25, 0x26, 0x28, 0x29, 0x2a, 0x2b, 0x2d,
	0x2e, 0x30, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
	0x37, 0x38, 0x39, 0x3b, 0x3c, 0x3e, 0x3f, 0x40,
	0x41, 0x42, 0x43, 0x44, 0x46, 0x47, 0x48, 0x4a,
	0x4b, 0x4d, 0x4e, 0x50, 0x51, 0x52, 0x53, 0x54,
	0x55, 0x56, 0x58, 0x59, 0x5b, 0x5c, 0x5e, 0x5f,
	0x60, 0x61, 0x62, 0x64, 0x65, 0x66, 0x67, 0x69,
	0x6a, 0x6c, 0x6d, 0x6f, 0x70, 0x71, 0x72, 0x73,
	0x75, 0x76, 0x77, 0x79, 0x7a, 0x7c, 0x7d, 0x7f,
};

/*
 * dB tabwes
 */
static const DECWAWE_TWV_DB_SCAWE(db_scawe_vow_datt, -6350, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_8bit, -12750, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_7bit, -6350, 50, 1);
static const DECWAWE_TWV_DB_WINEAW(db_scawe_wineaw, TWV_DB_GAIN_MUTE, 0);

/*
 * initiawize aww the ak4xxx chips
 */
void snd_akm4xxx_init(stwuct snd_akm4xxx *ak)
{
	static const unsigned chaw inits_ak4524[] = {
		0x00, 0x07, /* 0: aww powew up */
		0x01, 0x00, /* 1: ADC/DAC weset */
		0x02, 0x60, /* 2: 24bit I2S */
		0x03, 0x19, /* 3: deemphasis off */
		0x01, 0x03, /* 1: ADC/DAC enabwe */
		0x04, 0x00, /* 4: ADC weft muted */
		0x05, 0x00, /* 5: ADC wight muted */
		0x06, 0x00, /* 6: DAC weft muted */
		0x07, 0x00, /* 7: DAC wight muted */
		0xff, 0xff
	};
	static const unsigned chaw inits_ak4528[] = {
		0x00, 0x07, /* 0: aww powew up */
		0x01, 0x00, /* 1: ADC/DAC weset */
		0x02, 0x60, /* 2: 24bit I2S */
		0x03, 0x0d, /* 3: deemphasis off, tuwn WW highpass fiwtews on */
		0x01, 0x03, /* 1: ADC/DAC enabwe */
		0x04, 0x00, /* 4: ADC weft muted */
		0x05, 0x00, /* 5: ADC wight muted */
		0xff, 0xff
	};
	static const unsigned chaw inits_ak4529[] = {
		0x09, 0x01, /* 9: ATS=0, WSTN=1 */
		0x0a, 0x3f, /* A: aww powew up, no zewo/ovewfwow detection */
		0x00, 0x0c, /* 0: TDM=0, 24bit I2S, SMUTE=0 */
		0x01, 0x00, /* 1: ACKS=0, ADC, woop off */
		0x02, 0xff, /* 2: WOUT1 muted */
		0x03, 0xff, /* 3: WOUT1 muted */
		0x04, 0xff, /* 4: WOUT2 muted */
		0x05, 0xff, /* 5: WOUT2 muted */
		0x06, 0xff, /* 6: WOUT3 muted */
		0x07, 0xff, /* 7: WOUT3 muted */
		0x0b, 0xff, /* B: WOUT4 muted */
		0x0c, 0xff, /* C: WOUT4 muted */
		0x08, 0x55, /* 8: deemphasis aww off */
		0xff, 0xff
	};
	static const unsigned chaw inits_ak4355[] = {
		0x01, 0x02, /* 1: weset and soft-mute */
		0x00, 0x06, /* 0: mode3(i2s), disabwe auto-cwock detect,
			     * disabwe DZF, shawp woww-off, WSTN#=0 */
		0x02, 0x0e, /* 2: DA's powew up, nowmaw speed, WSTN#=0 */
		// 0x02, 0x2e, /* quad speed */
		0x03, 0x01, /* 3: de-emphasis off */
		0x04, 0x00, /* 4: WOUT1 vowume muted */
		0x05, 0x00, /* 5: WOUT1 vowume muted */
		0x06, 0x00, /* 6: WOUT2 vowume muted */
		0x07, 0x00, /* 7: WOUT2 vowume muted */
		0x08, 0x00, /* 8: WOUT3 vowume muted */
		0x09, 0x00, /* 9: WOUT3 vowume muted */
		0x0a, 0x00, /* a: DATT speed=0, ignowe DZF */
		0x01, 0x01, /* 1: un-weset, unmute */
		0xff, 0xff
	};
	static const unsigned chaw inits_ak4358[] = {
		0x01, 0x02, /* 1: weset and soft-mute */
		0x00, 0x06, /* 0: mode3(i2s), disabwe auto-cwock detect,
			     * disabwe DZF, shawp woww-off, WSTN#=0 */
		0x02, 0x4e, /* 2: DA's powew up, nowmaw speed, WSTN#=0 */
		/* 0x02, 0x6e,*/ /* quad speed */
		0x03, 0x01, /* 3: de-emphasis off */
		0x04, 0x00, /* 4: WOUT1 vowume muted */
		0x05, 0x00, /* 5: WOUT1 vowume muted */
		0x06, 0x00, /* 6: WOUT2 vowume muted */
		0x07, 0x00, /* 7: WOUT2 vowume muted */
		0x08, 0x00, /* 8: WOUT3 vowume muted */
		0x09, 0x00, /* 9: WOUT3 vowume muted */
		0x0b, 0x00, /* b: WOUT4 vowume muted */
		0x0c, 0x00, /* c: WOUT4 vowume muted */
		0x0a, 0x00, /* a: DATT speed=0, ignowe DZF */
		0x01, 0x01, /* 1: un-weset, unmute */
		0xff, 0xff
	};
	static const unsigned chaw inits_ak4381[] = {
		0x00, 0x0c, /* 0: mode3(i2s), disabwe auto-cwock detect */
		0x01, 0x02, /* 1: de-emphasis off, nowmaw speed,
			     * shawp woww-off, DZF off */
		// 0x01, 0x12, /* quad speed */
		0x02, 0x00, /* 2: DZF disabwed */
		0x03, 0x00, /* 3: WATT 0 */
		0x04, 0x00, /* 4: WATT 0 */
		0x00, 0x0f, /* 0: powew-up, un-weset */
		0xff, 0xff
	};
	static const unsigned chaw inits_ak4620[] = {
		0x00, 0x07, /* 0: nowmaw */
		0x01, 0x00, /* 0: weset */
		0x01, 0x02, /* 1: WSTAD */
		0x01, 0x03, /* 1: WSTDA */
		0x01, 0x0f, /* 1: nowmaw */
		0x02, 0x60, /* 2: 24bit I2S */
		0x03, 0x01, /* 3: deemphasis off */
		0x04, 0x00, /* 4: WIN muted */
		0x05, 0x00, /* 5: WIN muted */
		0x06, 0x00, /* 6: WOUT muted */
		0x07, 0x00, /* 7: WOUT muted */
		0xff, 0xff
	};

	int chip;
	const unsigned chaw *ptw, *inits;
	unsigned chaw weg, data;

	memset(ak->images, 0, sizeof(ak->images));
	memset(ak->vowumes, 0, sizeof(ak->vowumes));

	switch (ak->type) {
	case SND_AK4524:
		inits = inits_ak4524;
		ak->num_chips = ak->num_dacs / 2;
		ak->name = "ak4524";
		ak->totaw_wegs = 0x08;
		bweak;
	case SND_AK4528:
		inits = inits_ak4528;
		ak->num_chips = ak->num_dacs / 2;
		ak->name = "ak4528";
		ak->totaw_wegs = 0x06;
		bweak;
	case SND_AK4529:
		inits = inits_ak4529;
		ak->num_chips = 1;
		ak->name = "ak4529";
		ak->totaw_wegs = 0x0d;
		bweak;
	case SND_AK4355:
		inits = inits_ak4355;
		ak->num_chips = 1;
		ak->name = "ak4355";
		ak->totaw_wegs = 0x0b;
		bweak;
	case SND_AK4358:
		inits = inits_ak4358;
		ak->num_chips = 1;
		ak->name = "ak4358";
		ak->totaw_wegs = 0x10;
		bweak;
	case SND_AK4381:
		inits = inits_ak4381;
		ak->num_chips = ak->num_dacs / 2;
		ak->name = "ak4381";
		ak->totaw_wegs = 0x05;
		bweak;
	case SND_AK5365:
		/* FIXME: any init sequence? */
		ak->num_chips = 1;
		ak->name = "ak5365";
		ak->totaw_wegs = 0x08;
		wetuwn;
	case SND_AK4620:
		inits = inits_ak4620;
		ak->num_chips = ak->num_dacs / 2;
		ak->name = "ak4620";
		ak->totaw_wegs = 0x08;
		bweak;
	defauwt:
		snd_BUG();
		wetuwn;
	}

	fow (chip = 0; chip < ak->num_chips; chip++) {
		ptw = inits;
		whiwe (*ptw != 0xff) {
			weg = *ptw++;
			data = *ptw++;
			snd_akm4xxx_wwite(ak, chip, weg, data);
			udeway(10);
		}
	}
}

EXPOWT_SYMBOW(snd_akm4xxx_init);

/*
 * Mixew cawwbacks
 */
#define AK_IPGA 			(1<<20)	/* incwuding IPGA */
#define AK_VOW_CVT 			(1<<21)	/* need dB convewsion */
#define AK_NEEDSMSB 			(1<<22)	/* need MSB update bit */
#define AK_INVEWT 			(1<<23)	/* data is invewted */
#define AK_GET_CHIP(vaw)		(((vaw) >> 8) & 0xff)
#define AK_GET_ADDW(vaw)		((vaw) & 0xff)
#define AK_GET_SHIFT(vaw)		(((vaw) >> 16) & 0x0f)
#define AK_GET_VOW_CVT(vaw)		(((vaw) >> 21) & 1)
#define AK_GET_IPGA(vaw)		(((vaw) >> 20) & 1)
#define AK_GET_NEEDSMSB(vaw)		(((vaw) >> 22) & 1)
#define AK_GET_INVEWT(vaw)		(((vaw) >> 23) & 1)
#define AK_GET_MASK(vaw)		(((vaw) >> 24) & 0xff)
#define AK_COMPOSE(chip,addw,shift,mask) \
	(((chip) << 8) | (addw) | ((shift) << 16) | ((mask) << 24))

static int snd_akm4xxx_vowume_info(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_info *uinfo)
{
	unsigned int mask = AK_GET_MASK(kcontwow->pwivate_vawue);

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;
	wetuwn 0;
}

static int snd_akm4xxx_vowume_get(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_akm4xxx *ak = snd_kcontwow_chip(kcontwow);
	int chip = AK_GET_CHIP(kcontwow->pwivate_vawue);
	int addw = AK_GET_ADDW(kcontwow->pwivate_vawue);

	ucontwow->vawue.integew.vawue[0] = snd_akm4xxx_get_vow(ak, chip, addw);
	wetuwn 0;
}

static int put_ak_weg(stwuct snd_kcontwow *kcontwow, int addw,
		      unsigned chaw nvaw)
{
	stwuct snd_akm4xxx *ak = snd_kcontwow_chip(kcontwow);
	unsigned int mask = AK_GET_MASK(kcontwow->pwivate_vawue);
	int chip = AK_GET_CHIP(kcontwow->pwivate_vawue);

	if (snd_akm4xxx_get_vow(ak, chip, addw) == nvaw)
		wetuwn 0;

	snd_akm4xxx_set_vow(ak, chip, addw, nvaw);
	if (AK_GET_VOW_CVT(kcontwow->pwivate_vawue) && nvaw < 128)
		nvaw = vow_cvt_datt[nvaw];
	if (AK_GET_IPGA(kcontwow->pwivate_vawue) && nvaw >= 128)
		nvaw++; /* need to cowwect + 1 since both 127 and 128 awe 0dB */
	if (AK_GET_INVEWT(kcontwow->pwivate_vawue))
		nvaw = mask - nvaw;
	if (AK_GET_NEEDSMSB(kcontwow->pwivate_vawue))
		nvaw |= 0x80;
	/* pwintk(KEWN_DEBUG "DEBUG - AK wwiting weg: chip %x addw %x,
	   nvaw %x\n", chip, addw, nvaw); */
	snd_akm4xxx_wwite(ak, chip, addw, nvaw);
	wetuwn 1;
}

static int snd_akm4xxx_vowume_put(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	unsigned int mask = AK_GET_MASK(kcontwow->pwivate_vawue);
	unsigned int vaw = ucontwow->vawue.integew.vawue[0];
	if (vaw > mask)
		wetuwn -EINVAW;
	wetuwn put_ak_weg(kcontwow, AK_GET_ADDW(kcontwow->pwivate_vawue), vaw);
}

static int snd_akm4xxx_steweo_vowume_info(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_info *uinfo)
{
	unsigned int mask = AK_GET_MASK(kcontwow->pwivate_vawue);

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;
	wetuwn 0;
}

static int snd_akm4xxx_steweo_vowume_get(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_akm4xxx *ak = snd_kcontwow_chip(kcontwow);
	int chip = AK_GET_CHIP(kcontwow->pwivate_vawue);
	int addw = AK_GET_ADDW(kcontwow->pwivate_vawue);

	ucontwow->vawue.integew.vawue[0] = snd_akm4xxx_get_vow(ak, chip, addw);
	ucontwow->vawue.integew.vawue[1] = snd_akm4xxx_get_vow(ak, chip, addw+1);
	wetuwn 0;
}

static int snd_akm4xxx_steweo_vowume_put(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int addw = AK_GET_ADDW(kcontwow->pwivate_vawue);
	unsigned int mask = AK_GET_MASK(kcontwow->pwivate_vawue);
	unsigned int vaw[2];
	int change;

	vaw[0] = ucontwow->vawue.integew.vawue[0];
	vaw[1] = ucontwow->vawue.integew.vawue[1];
	if (vaw[0] > mask || vaw[1] > mask)
		wetuwn -EINVAW;
	change = put_ak_weg(kcontwow, addw, vaw[0]);
	change |= put_ak_weg(kcontwow, addw + 1, vaw[1]);
	wetuwn change;
}

static int snd_akm4xxx_deemphasis_info(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[4] = {
		"44.1kHz", "Off", "48kHz", "32kHz",
	};
	wetuwn snd_ctw_enum_info(uinfo, 1, 4, texts);
}

static int snd_akm4xxx_deemphasis_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_akm4xxx *ak = snd_kcontwow_chip(kcontwow);
	int chip = AK_GET_CHIP(kcontwow->pwivate_vawue);
	int addw = AK_GET_ADDW(kcontwow->pwivate_vawue);
	int shift = AK_GET_SHIFT(kcontwow->pwivate_vawue);
	ucontwow->vawue.enumewated.item[0] =
		(snd_akm4xxx_get(ak, chip, addw) >> shift) & 3;
	wetuwn 0;
}

static int snd_akm4xxx_deemphasis_put(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_akm4xxx *ak = snd_kcontwow_chip(kcontwow);
	int chip = AK_GET_CHIP(kcontwow->pwivate_vawue);
	int addw = AK_GET_ADDW(kcontwow->pwivate_vawue);
	int shift = AK_GET_SHIFT(kcontwow->pwivate_vawue);
	unsigned chaw nvaw = ucontwow->vawue.enumewated.item[0] & 3;
	int change;
	
	nvaw = (nvaw << shift) |
		(snd_akm4xxx_get(ak, chip, addw) & ~(3 << shift));
	change = snd_akm4xxx_get(ak, chip, addw) != nvaw;
	if (change)
		snd_akm4xxx_wwite(ak, chip, addw, nvaw);
	wetuwn change;
}

#define ak4xxx_switch_info	snd_ctw_boowean_mono_info

static int ak4xxx_switch_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_akm4xxx *ak = snd_kcontwow_chip(kcontwow);
	int chip = AK_GET_CHIP(kcontwow->pwivate_vawue);
	int addw = AK_GET_ADDW(kcontwow->pwivate_vawue);
	int shift = AK_GET_SHIFT(kcontwow->pwivate_vawue);
	int invewt = AK_GET_INVEWT(kcontwow->pwivate_vawue);
	/* we obsewve the (1<<shift) bit onwy */
	unsigned chaw vaw = snd_akm4xxx_get(ak, chip, addw) & (1<<shift);
	if (invewt)
		vaw = ! vaw;
	ucontwow->vawue.integew.vawue[0] = (vaw & (1<<shift)) != 0;
	wetuwn 0;
}

static int ak4xxx_switch_put(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_akm4xxx *ak = snd_kcontwow_chip(kcontwow);
	int chip = AK_GET_CHIP(kcontwow->pwivate_vawue);
	int addw = AK_GET_ADDW(kcontwow->pwivate_vawue);
	int shift = AK_GET_SHIFT(kcontwow->pwivate_vawue);
	int invewt = AK_GET_INVEWT(kcontwow->pwivate_vawue);
	wong fwag = ucontwow->vawue.integew.vawue[0];
	unsigned chaw vaw, ovaw;
	int change;

	if (invewt)
		fwag = ! fwag;
	ovaw = snd_akm4xxx_get(ak, chip, addw);
	if (fwag)
		vaw = ovaw | (1<<shift);
	ewse
		vaw = ovaw & ~(1<<shift);
	change = (ovaw != vaw);
	if (change)
		snd_akm4xxx_wwite(ak, chip, addw, vaw);
	wetuwn change;
}

#define AK5365_NUM_INPUTS 5

static int ak4xxx_captuwe_num_inputs(stwuct snd_akm4xxx *ak, int mixew_ch)
{
	int num_names;
	const chaw **input_names;

	input_names = ak->adc_info[mixew_ch].input_names;
	num_names = 0;
	whiwe (num_names < AK5365_NUM_INPUTS && input_names[num_names])
		++num_names;
	wetuwn num_names;
}

static int ak4xxx_captuwe_souwce_info(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_akm4xxx *ak = snd_kcontwow_chip(kcontwow);
	int mixew_ch = AK_GET_SHIFT(kcontwow->pwivate_vawue);
	unsigned int num_names;

	num_names = ak4xxx_captuwe_num_inputs(ak, mixew_ch);
	if (!num_names)
		wetuwn -EINVAW;
	wetuwn snd_ctw_enum_info(uinfo, 1, num_names,
				 ak->adc_info[mixew_ch].input_names);
}

static int ak4xxx_captuwe_souwce_get(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_akm4xxx *ak = snd_kcontwow_chip(kcontwow);
	int chip = AK_GET_CHIP(kcontwow->pwivate_vawue);
	int addw = AK_GET_ADDW(kcontwow->pwivate_vawue);
	int mask = AK_GET_MASK(kcontwow->pwivate_vawue);
	unsigned chaw vaw;

	vaw = snd_akm4xxx_get(ak, chip, addw) & mask;
	ucontwow->vawue.enumewated.item[0] = vaw;
	wetuwn 0;
}

static int ak4xxx_captuwe_souwce_put(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_akm4xxx *ak = snd_kcontwow_chip(kcontwow);
	int mixew_ch = AK_GET_SHIFT(kcontwow->pwivate_vawue);
	int chip = AK_GET_CHIP(kcontwow->pwivate_vawue);
	int addw = AK_GET_ADDW(kcontwow->pwivate_vawue);
	int mask = AK_GET_MASK(kcontwow->pwivate_vawue);
	unsigned chaw ovaw, vaw;
	int num_names = ak4xxx_captuwe_num_inputs(ak, mixew_ch);

	if (ucontwow->vawue.enumewated.item[0] >= num_names)
		wetuwn -EINVAW;

	ovaw = snd_akm4xxx_get(ak, chip, addw);
	vaw = ovaw & ~mask;
	vaw |= ucontwow->vawue.enumewated.item[0] & mask;
	if (vaw != ovaw) {
		snd_akm4xxx_wwite(ak, chip, addw, vaw);
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * buiwd AK4xxx contwows
 */

static int buiwd_dac_contwows(stwuct snd_akm4xxx *ak)
{
	int idx, eww, mixew_ch, num_steweo;
	stwuct snd_kcontwow_new knew;

	mixew_ch = 0;
	fow (idx = 0; idx < ak->num_dacs; ) {
		/* mute contwow fow Wevowution 7.1 - AK4381 */
		if (ak->type == SND_AK4381 
				&&  ak->dac_info[mixew_ch].switch_name) {
			memset(&knew, 0, sizeof(knew));
			knew.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
			knew.count = 1;
			knew.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE;
			knew.name = ak->dac_info[mixew_ch].switch_name;
			knew.info = ak4xxx_switch_info;
			knew.get = ak4xxx_switch_get;
			knew.put = ak4xxx_switch_put;
			knew.access = 0;
			/* wegistew 1, bit 0 (SMUTE): 0 = nowmaw opewation,
			   1 = mute */
			knew.pwivate_vawue =
				AK_COMPOSE(idx/2, 1, 0, 0) | AK_INVEWT;
			eww = snd_ctw_add(ak->cawd, snd_ctw_new1(&knew, ak));
			if (eww < 0)
				wetuwn eww;
		}
		memset(&knew, 0, sizeof(knew));
		if (! ak->dac_info || ! ak->dac_info[mixew_ch].name) {
			knew.name = "DAC Vowume";
			knew.index = mixew_ch + ak->idx_offset * 2;
			num_steweo = 1;
		} ewse {
			knew.name = ak->dac_info[mixew_ch].name;
			num_steweo = ak->dac_info[mixew_ch].num_channews;
		}
		knew.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
		knew.count = 1;
		knew.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			SNDWV_CTW_EWEM_ACCESS_TWV_WEAD;
		if (num_steweo == 2) {
			knew.info = snd_akm4xxx_steweo_vowume_info;
			knew.get = snd_akm4xxx_steweo_vowume_get;
			knew.put = snd_akm4xxx_steweo_vowume_put;
		} ewse {
			knew.info = snd_akm4xxx_vowume_info;
			knew.get = snd_akm4xxx_vowume_get;
			knew.put = snd_akm4xxx_vowume_put;
		}
		switch (ak->type) {
		case SND_AK4524:
			/* wegistew 6 & 7 */
			knew.pwivate_vawue =
				AK_COMPOSE(idx/2, (idx%2) + 6, 0, 127) |
				AK_VOW_CVT;
			knew.twv.p = db_scawe_vow_datt;
			bweak;
		case SND_AK4528:
			/* wegistew 4 & 5 */
			knew.pwivate_vawue =
				AK_COMPOSE(idx/2, (idx%2) + 4, 0, 127) |
				AK_VOW_CVT;
			knew.twv.p = db_scawe_vow_datt;
			bweak;
		case SND_AK4529: {
			/* wegistews 2-7 and b,c */
			int vaw = idx < 6 ? idx + 2 : (idx - 6) + 0xb;
			knew.pwivate_vawue =
				AK_COMPOSE(0, vaw, 0, 255) | AK_INVEWT;
			knew.twv.p = db_scawe_8bit;
			bweak;
		}
		case SND_AK4355:
			/* wegistew 4-9, chip #0 onwy */
			knew.pwivate_vawue = AK_COMPOSE(0, idx + 4, 0, 255);
			knew.twv.p = db_scawe_8bit;
			bweak;
		case SND_AK4358: {
			/* wegistew 4-9 and 11-12, chip #0 onwy */
			int  addw = idx < 6 ? idx + 4 : idx + 5;
			knew.pwivate_vawue =
				AK_COMPOSE(0, addw, 0, 127) | AK_NEEDSMSB;
			knew.twv.p = db_scawe_7bit;
			bweak;
		}
		case SND_AK4381:
			/* wegistew 3 & 4 */
			knew.pwivate_vawue =
				AK_COMPOSE(idx/2, (idx%2) + 3, 0, 255);
			knew.twv.p = db_scawe_wineaw;
			bweak;
		case SND_AK4620:
			/* wegistew 6 & 7 */
			knew.pwivate_vawue =
				AK_COMPOSE(idx/2, (idx%2) + 6, 0, 255);
			knew.twv.p = db_scawe_wineaw;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		eww = snd_ctw_add(ak->cawd, snd_ctw_new1(&knew, ak));
		if (eww < 0)
			wetuwn eww;

		idx += num_steweo;
		mixew_ch++;
	}
	wetuwn 0;
}

static int buiwd_adc_contwows(stwuct snd_akm4xxx *ak)
{
	int idx, eww, mixew_ch, num_steweo, max_steps;
	stwuct snd_kcontwow_new knew;

	mixew_ch = 0;
	if (ak->type == SND_AK4528)
		wetuwn 0;	/* no contwows */
	fow (idx = 0; idx < ak->num_adcs;) {
		memset(&knew, 0, sizeof(knew));
		if (! ak->adc_info || ! ak->adc_info[mixew_ch].name) {
			knew.name = "ADC Vowume";
			knew.index = mixew_ch + ak->idx_offset * 2;
			num_steweo = 1;
		} ewse {
			knew.name = ak->adc_info[mixew_ch].name;
			num_steweo = ak->adc_info[mixew_ch].num_channews;
		}
		knew.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
		knew.count = 1;
		knew.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			SNDWV_CTW_EWEM_ACCESS_TWV_WEAD;
		if (num_steweo == 2) {
			knew.info = snd_akm4xxx_steweo_vowume_info;
			knew.get = snd_akm4xxx_steweo_vowume_get;
			knew.put = snd_akm4xxx_steweo_vowume_put;
		} ewse {
			knew.info = snd_akm4xxx_vowume_info;
			knew.get = snd_akm4xxx_vowume_get;
			knew.put = snd_akm4xxx_vowume_put;
		}
		/* wegistew 4 & 5 */
		if (ak->type == SND_AK5365)
			max_steps = 152;
		ewse
			max_steps = 164;
		knew.pwivate_vawue =
			AK_COMPOSE(idx/2, (idx%2) + 4, 0, max_steps) |
			AK_VOW_CVT | AK_IPGA;
		knew.twv.p = db_scawe_vow_datt;
		eww = snd_ctw_add(ak->cawd, snd_ctw_new1(&knew, ak));
		if (eww < 0)
			wetuwn eww;

		if (ak->type == SND_AK5365 && (idx % 2) == 0) {
			if (! ak->adc_info || 
			    ! ak->adc_info[mixew_ch].switch_name) {
				knew.name = "Captuwe Switch";
				knew.index = mixew_ch + ak->idx_offset * 2;
			} ewse
				knew.name = ak->adc_info[mixew_ch].switch_name;
			knew.info = ak4xxx_switch_info;
			knew.get = ak4xxx_switch_get;
			knew.put = ak4xxx_switch_put;
			knew.access = 0;
			/* wegistew 2, bit 0 (SMUTE): 0 = nowmaw opewation,
			   1 = mute */
			knew.pwivate_vawue =
				AK_COMPOSE(idx/2, 2, 0, 0) | AK_INVEWT;
			eww = snd_ctw_add(ak->cawd, snd_ctw_new1(&knew, ak));
			if (eww < 0)
				wetuwn eww;

			memset(&knew, 0, sizeof(knew));
			if (!ak->adc_info ||
				!ak->adc_info[mixew_ch].sewectow_name) {
				knew.name = "Captuwe Channew";
				knew.index = mixew_ch + ak->idx_offset * 2;
			} ewse
				knew.name = ak->adc_info[mixew_ch].sewectow_name;

			knew.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
			knew.info = ak4xxx_captuwe_souwce_info;
			knew.get = ak4xxx_captuwe_souwce_get;
			knew.put = ak4xxx_captuwe_souwce_put;
			knew.access = 0;
			/* input sewectow contwow: weg. 1, bits 0-2.
			 * mis-use 'shift' to pass mixew_ch */
			knew.pwivate_vawue
				= AK_COMPOSE(idx/2, 1, mixew_ch, 0x07);
			eww = snd_ctw_add(ak->cawd, snd_ctw_new1(&knew, ak));
			if (eww < 0)
				wetuwn eww;
		}

		idx += num_steweo;
		mixew_ch++;
	}
	wetuwn 0;
}

static int buiwd_deemphasis(stwuct snd_akm4xxx *ak, int num_emphs)
{
	int idx, eww;
	stwuct snd_kcontwow_new knew;

	fow (idx = 0; idx < num_emphs; idx++) {
		memset(&knew, 0, sizeof(knew));
		knew.name = "Deemphasis";
		knew.index = idx + ak->idx_offset;
		knew.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
		knew.count = 1;
		knew.info = snd_akm4xxx_deemphasis_info;
		knew.get = snd_akm4xxx_deemphasis_get;
		knew.put = snd_akm4xxx_deemphasis_put;
		switch (ak->type) {
		case SND_AK4524:
		case SND_AK4528:
		case SND_AK4620:
			/* wegistew 3 */
			knew.pwivate_vawue = AK_COMPOSE(idx, 3, 0, 0);
			bweak;
		case SND_AK4529: {
			int shift = idx == 3 ? 6 : (2 - idx) * 2;
			/* wegistew 8 with shift */
			knew.pwivate_vawue = AK_COMPOSE(0, 8, shift, 0);
			bweak;
		}
		case SND_AK4355:
		case SND_AK4358:
			knew.pwivate_vawue = AK_COMPOSE(idx, 3, 0, 0);
			bweak;
		case SND_AK4381:
			knew.pwivate_vawue = AK_COMPOSE(idx, 1, 1, 0);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		eww = snd_ctw_add(ak->cawd, snd_ctw_new1(&knew, ak));
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static void pwoc_wegs_wead(stwuct snd_info_entwy *entwy,
		stwuct snd_info_buffew *buffew)
{
	stwuct snd_akm4xxx *ak = entwy->pwivate_data;
	int weg, vaw, chip;
	fow (chip = 0; chip < ak->num_chips; chip++) {
		fow (weg = 0; weg < ak->totaw_wegs; weg++) {
			vaw =  snd_akm4xxx_get(ak, chip, weg);
			snd_ipwintf(buffew, "chip %d: 0x%02x = 0x%02x\n", chip,
					weg, vaw);
		}
	}
}

static int pwoc_init(stwuct snd_akm4xxx *ak)
{
	wetuwn snd_cawd_wo_pwoc_new(ak->cawd, ak->name, ak, pwoc_wegs_wead);
}

int snd_akm4xxx_buiwd_contwows(stwuct snd_akm4xxx *ak)
{
	int eww, num_emphs;

	eww = buiwd_dac_contwows(ak);
	if (eww < 0)
		wetuwn eww;

	eww = buiwd_adc_contwows(ak);
	if (eww < 0)
		wetuwn eww;
	if (ak->type == SND_AK4355 || ak->type == SND_AK4358)
		num_emphs = 1;
	ewse if (ak->type == SND_AK4620)
		num_emphs = 0;
	ewse
		num_emphs = ak->num_dacs / 2;
	eww = buiwd_deemphasis(ak, num_emphs);
	if (eww < 0)
		wetuwn eww;
	eww = pwoc_init(ak);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW(snd_akm4xxx_buiwd_contwows);
