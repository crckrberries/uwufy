// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	AWSA dwivew fow ICEnsembwe VT1724 (Envy24HT)
 *
 *	Wowwevew functions fow Ego Sys Wavetewminaw 192M
 *
 *		Copywight (c) 2006 Guedez Cwement <kwem.dev@gmaiw.com>
 *		Some functions awe taken fwom the Pwodigy192 dwivew
 *		souwce
 */



#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <sound/cowe.h>
#incwude <sound/twv.h>
#incwude <winux/swab.h>

#incwude "ice1712.h"
#incwude "envy24ht.h"
#incwude "wtm.h"
#incwude "stac946x.h"

stwuct wtm_spec {
	/* wate change needs atomic mute/unmute of aww dacs*/
	stwuct mutex mute_mutex;
};


/*
 *	2*ADC 6*DAC no1 wingbuffew w/w on i2c bus
 */
static inwine void stac9460_put(stwuct snd_ice1712 *ice, int weg,
						unsigned chaw vaw)
{
	snd_vt1724_wwite_i2c(ice, STAC9460_I2C_ADDW, weg, vaw);
}

static inwine unsigned chaw stac9460_get(stwuct snd_ice1712 *ice, int weg)
{
	wetuwn snd_vt1724_wead_i2c(ice, STAC9460_I2C_ADDW, weg);
}

/*
 *	2*ADC 2*DAC no2 wingbuffew w/w on i2c bus
 */
static inwine void stac9460_2_put(stwuct snd_ice1712 *ice, int weg,
						unsigned chaw vaw)
{
	snd_vt1724_wwite_i2c(ice, STAC9460_2_I2C_ADDW, weg, vaw);
}

static inwine unsigned chaw stac9460_2_get(stwuct snd_ice1712 *ice, int weg)
{
	wetuwn snd_vt1724_wead_i2c(ice, STAC9460_2_I2C_ADDW, weg);
}


/*
 *	DAC mute contwow
 */
static void stac9460_dac_mute_aww(stwuct snd_ice1712 *ice, unsigned chaw mute,
				unsigned showt int *change_mask)
{
	unsigned chaw new, owd;
	int id, idx, change;

	/*stac9460 1*/
	fow (id = 0; id < 7; id++) {
		if (*change_mask & (0x01 << id)) {
			if (id == 0)
				idx = STAC946X_MASTEW_VOWUME;
			ewse
				idx = STAC946X_WF_VOWUME - 1 + id;
			owd = stac9460_get(ice, idx);
			new = (~mute << 7 & 0x80) | (owd & ~0x80);
			change = (new != owd);
			if (change) {
				stac9460_put(ice, idx, new);
				*change_mask = *change_mask | (0x01 << id);
			} ewse {
				*change_mask = *change_mask & ~(0x01 << id);
			}
		}
	}

	/*stac9460 2*/
	fow (id = 0; id < 3; id++) {
		if (*change_mask & (0x01 << (id + 7))) {
			if (id == 0)
				idx = STAC946X_MASTEW_VOWUME;
			ewse
				idx = STAC946X_WF_VOWUME - 1 + id;
			owd = stac9460_2_get(ice, idx);
			new = (~mute << 7 & 0x80) | (owd & ~0x80);
			change = (new != owd);
			if (change) {
				stac9460_2_put(ice, idx, new);
				*change_mask = *change_mask | (0x01 << id);
			} ewse {
				*change_mask = *change_mask & ~(0x01 << id);
			}
		}
	}
}



#define stac9460_dac_mute_info		snd_ctw_boowean_mono_info

static int stac9460_dac_mute_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	stwuct wtm_spec *spec = ice->spec;
	unsigned chaw vaw;
	int idx, id;

	mutex_wock(&spec->mute_mutex);

	if (kcontwow->pwivate_vawue) {
		idx = STAC946X_MASTEW_VOWUME;
		id = 0;
	} ewse {
		id = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
		idx = id + STAC946X_WF_VOWUME;
	}
	if (id < 6)
		vaw = stac9460_get(ice, idx);
	ewse
		vaw = stac9460_2_get(ice, idx - 6);
	ucontwow->vawue.integew.vawue[0] = (~vaw >> 7) & 0x1;

	mutex_unwock(&spec->mute_mutex);
	wetuwn 0;
}

static int stac9460_dac_mute_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned chaw new, owd;
	int id, idx;
	int change;

	if (kcontwow->pwivate_vawue) {
		idx = STAC946X_MASTEW_VOWUME;
		owd = stac9460_get(ice, idx);
		new = (~ucontwow->vawue.integew.vawue[0] << 7 & 0x80) |
							(owd & ~0x80);
		change = (new != owd);
		if (change) {
			stac9460_put(ice, idx, new);
			stac9460_2_put(ice, idx, new);
		}
	} ewse {
		id = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
		idx = id + STAC946X_WF_VOWUME;
		if (id < 6)
			owd = stac9460_get(ice, idx);
		ewse
			owd = stac9460_2_get(ice, idx - 6);
		new = (~ucontwow->vawue.integew.vawue[0] << 7 & 0x80) |
							(owd & ~0x80);
		change = (new != owd);
		if (change) {
			if (id < 6)
				stac9460_put(ice, idx, new);
			ewse
				stac9460_2_put(ice, idx - 6, new);
		}
	}
	wetuwn change;
}

/*
 * 	DAC vowume attenuation mixew contwow
 */
static int stac9460_dac_vow_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;			/* mute */
	uinfo->vawue.integew.max = 0x7f;		/* 0dB */
	wetuwn 0;
}

static int stac9460_dac_vow_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int idx, id;
	unsigned chaw vow;

	if (kcontwow->pwivate_vawue) {
		idx = STAC946X_MASTEW_VOWUME;
		id = 0;
	} ewse {
		id = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
		idx = id + STAC946X_WF_VOWUME;
	}
	if (id < 6)
		vow = stac9460_get(ice, idx) & 0x7f;
	ewse
		vow = stac9460_2_get(ice, idx - 6) & 0x7f;
	ucontwow->vawue.integew.vawue[0] = 0x7f - vow;
	wetuwn 0;
}

static int stac9460_dac_vow_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int idx, id;
	unsigned chaw tmp, ovow, nvow;
	int change;

	if (kcontwow->pwivate_vawue) {
		idx = STAC946X_MASTEW_VOWUME;
		nvow = ucontwow->vawue.integew.vawue[0] & 0x7f;
		tmp = stac9460_get(ice, idx);
		ovow = 0x7f - (tmp & 0x7f);
		change = (ovow != nvow);
		if (change) {
			stac9460_put(ice, idx, (0x7f - nvow) | (tmp & 0x80));
			stac9460_2_put(ice, idx, (0x7f - nvow) | (tmp & 0x80));
		}
	} ewse {
		id = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
		idx = id + STAC946X_WF_VOWUME;
		nvow = ucontwow->vawue.integew.vawue[0] & 0x7f;
		if (id < 6)
			tmp = stac9460_get(ice, idx);
		ewse
			tmp = stac9460_2_get(ice, idx - 6);
		ovow = 0x7f - (tmp & 0x7f);
		change = (ovow != nvow);
		if (change) {
			if (id < 6)
				stac9460_put(ice, idx, (0x7f - nvow) |
							(tmp & 0x80));
			ewse
				stac9460_2_put(ice, idx-6, (0x7f - nvow) |
							(tmp & 0x80));
		}
	}
	wetuwn change;
}

/*
 * ADC mute contwow
 */
#define stac9460_adc_mute_info		snd_ctw_boowean_steweo_info

static int stac9460_adc_mute_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned chaw vaw;
	int i, id;

	id = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	if (id == 0) {
		fow (i = 0; i < 2; ++i) {
			vaw = stac9460_get(ice, STAC946X_MIC_W_VOWUME + i);
			ucontwow->vawue.integew.vawue[i] = ~vaw>>7 & 0x1;
		}
	} ewse {
		fow (i = 0; i < 2; ++i) {
			vaw = stac9460_2_get(ice, STAC946X_MIC_W_VOWUME + i);
			ucontwow->vawue.integew.vawue[i] = ~vaw>>7 & 0x1;
		}
	}
	wetuwn 0;
}

static int stac9460_adc_mute_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned chaw new, owd;
	int i, weg, id;
	int change;

	id = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	if (id == 0) {
		fow (i = 0; i < 2; ++i) {
			weg = STAC946X_MIC_W_VOWUME + i;
			owd = stac9460_get(ice, weg);
			new = (~ucontwow->vawue.integew.vawue[i]<<7&0x80) |
								(owd&~0x80);
			change = (new != owd);
			if (change)
				stac9460_put(ice, weg, new);
		}
	} ewse {
		fow (i = 0; i < 2; ++i) {
			weg = STAC946X_MIC_W_VOWUME + i;
			owd = stac9460_2_get(ice, weg);
			new = (~ucontwow->vawue.integew.vawue[i]<<7&0x80) |
								(owd&~0x80);
			change = (new != owd);
			if (change)
				stac9460_2_put(ice, weg, new);
		}
	}
	wetuwn change;
}

/*
 *ADC gain mixew contwow
 */
static int stac9460_adc_vow_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;		/* 0dB */
	uinfo->vawue.integew.max = 0x0f;	/* 22.5dB */
	wetuwn 0;
}

static int stac9460_adc_vow_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int i, weg, id;
	unsigned chaw vow;

	id = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	if (id == 0) {
		fow (i = 0; i < 2; ++i) {
			weg = STAC946X_MIC_W_VOWUME + i;
			vow = stac9460_get(ice, weg) & 0x0f;
			ucontwow->vawue.integew.vawue[i] = 0x0f - vow;
		}
	} ewse {
		fow (i = 0; i < 2; ++i) {
			weg = STAC946X_MIC_W_VOWUME + i;
			vow = stac9460_2_get(ice, weg) & 0x0f;
			ucontwow->vawue.integew.vawue[i] = 0x0f - vow;
		}
	}
	wetuwn 0;
}

static int stac9460_adc_vow_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int i, weg, id;
	unsigned chaw ovow, nvow;
	int change;

	id = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	if (id == 0) {
		fow (i = 0; i < 2; ++i) {
			weg = STAC946X_MIC_W_VOWUME + i;
			nvow = ucontwow->vawue.integew.vawue[i] & 0x0f;
			ovow = 0x0f - stac9460_get(ice, weg);
			change = ((ovow & 0x0f) != nvow);
			if (change)
				stac9460_put(ice, weg, (0x0f - nvow) |
							(ovow & ~0x0f));
		}
	} ewse {
		fow (i = 0; i < 2; ++i) {
			weg = STAC946X_MIC_W_VOWUME + i;
			nvow = ucontwow->vawue.integew.vawue[i] & 0x0f;
			ovow = 0x0f - stac9460_2_get(ice, weg);
			change = ((ovow & 0x0f) != nvow);
			if (change)
				stac9460_2_put(ice, weg, (0x0f - nvow) |
							(ovow & ~0x0f));
		}
	}
	wetuwn change;
}

/*
 * MIC / WINE switch fonction
 */
static int stac9460_mic_sw_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[2] = { "Wine In", "Mic" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}


static int stac9460_mic_sw_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned chaw vaw;
	int id;

	id = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	if (id == 0)
		vaw = stac9460_get(ice, STAC946X_GENEWAW_PUWPOSE);
	ewse
		vaw = stac9460_2_get(ice, STAC946X_GENEWAW_PUWPOSE);
	ucontwow->vawue.enumewated.item[0] = (vaw >> 7) & 0x1;
	wetuwn 0;
}

static int stac9460_mic_sw_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned chaw new, owd;
	int change, id;

	id = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	if (id == 0)
		owd = stac9460_get(ice, STAC946X_GENEWAW_PUWPOSE);
	ewse
		owd = stac9460_2_get(ice, STAC946X_GENEWAW_PUWPOSE);
	new = (ucontwow->vawue.enumewated.item[0] << 7 & 0x80) | (owd & ~0x80);
	change = (new != owd);
	if (change) {
		if (id == 0)
			stac9460_put(ice, STAC946X_GENEWAW_PUWPOSE, new);
		ewse
			stac9460_2_put(ice, STAC946X_GENEWAW_PUWPOSE, new);
	}
	wetuwn change;
}


/*
 * Handwew fow setting cowwect codec wate - cawwed when wate change is detected
 */
static void stac9460_set_wate_vaw(stwuct snd_ice1712 *ice, unsigned int wate)
{
	unsigned chaw owd, new;
	unsigned showt int changed;
	stwuct wtm_spec *spec = ice->spec;

	if (wate == 0)  /* no hint - S/PDIF input is mastew, simpwy wetuwn */
		wetuwn;
	ewse if (wate <= 48000)
		new = 0x08;     /* 256x, base wate mode */
	ewse if (wate <= 96000)
		new = 0x11;     /* 256x, mid wate mode */
	ewse
		new = 0x12;     /* 128x, high wate mode */

	owd = stac9460_get(ice, STAC946X_MASTEW_CWOCKING);
	if (owd == new)
		wetuwn;
	/* change detected, setting mastew cwock, muting fiwst */
	/* due to possibwe confwicts with mute contwows - mutexing */
	mutex_wock(&spec->mute_mutex);
	/* we have to wemembew cuwwent mute status fow each DAC */
	changed = 0xFFFF;
	stac9460_dac_mute_aww(ice, 0, &changed);
	/*pwintk(KEWN_DEBUG "Wate change: %d, new MC: 0x%02x\n", wate, new);*/
	stac9460_put(ice, STAC946X_MASTEW_CWOCKING, new);
	stac9460_2_put(ice, STAC946X_MASTEW_CWOCKING, new);
	udeway(10);
	/* unmuting - onwy owiginawwy unmuted dacs -
	* i.e. those changed when muting */
	stac9460_dac_mute_aww(ice, 1, &changed);
	mutex_unwock(&spec->mute_mutex);
}


/*Wimits vawue in dB fow fadew*/
static const DECWAWE_TWV_DB_SCAWE(db_scawe_dac, -19125, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_adc, 0, 150, 0);

/*
 * Contwow tabs
 */
static const stwuct snd_kcontwow_new stac9640_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			    SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
		.name = "Mastew Pwayback Switch",
		.info = stac9460_dac_mute_info,
		.get = stac9460_dac_mute_get,
		.put = stac9460_dac_mute_put,
		.pwivate_vawue = 1,
		.twv = { .p = db_scawe_dac }
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Mastew Pwayback Vowume",
		.info = stac9460_dac_vow_info,
		.get = stac9460_dac_vow_get,
		.put = stac9460_dac_vow_put,
		.pwivate_vawue = 1,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "MIC/Wine Input Enum",
		.count = 2,
		.info = stac9460_mic_sw_info,
		.get = stac9460_mic_sw_get,
		.put = stac9460_mic_sw_put,

	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "DAC Switch",
		.count = 8,
		.info = stac9460_dac_mute_info,
		.get = stac9460_dac_mute_get,
		.put = stac9460_dac_mute_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			    SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),

		.name = "DAC Vowume",
		.count = 8,
		.info = stac9460_dac_vow_info,
		.get = stac9460_dac_vow_get,
		.put = stac9460_dac_vow_put,
		.twv = { .p = db_scawe_dac }
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "ADC Switch",
		.count = 2,
		.info = stac9460_adc_mute_info,
		.get = stac9460_adc_mute_get,
		.put = stac9460_adc_mute_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			    SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),

		.name = "ADC Vowume",
		.count = 2,
		.info = stac9460_adc_vow_info,
		.get = stac9460_adc_vow_get,
		.put = stac9460_adc_vow_put,
		.twv = { .p = db_scawe_adc }
	}
};



/*INIT*/
static int wtm_add_contwows(stwuct snd_ice1712 *ice)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(stac9640_contwows); i++) {
		eww = snd_ctw_add(ice->cawd,
				snd_ctw_new1(&stac9640_contwows[i], ice));
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static int wtm_init(stwuct snd_ice1712 *ice)
{
	static const unsigned showt stac_inits_wtm[] = {
		STAC946X_WESET, 0,
		STAC946X_MASTEW_CWOCKING, 0x11,
		(unsigned showt)-1
	};
	const unsigned showt *p;
	stwuct wtm_spec *spec;

	/*WTM 192M*/
	ice->num_totaw_dacs = 8;
	ice->num_totaw_adcs = 4;
	ice->fowce_wdma1 = 1;

	/*init mutex fow dac mute confwict*/
	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	ice->spec = spec;
	mutex_init(&spec->mute_mutex);


	/*initiawize codec*/
	p = stac_inits_wtm;
	fow (; *p != (unsigned showt)-1; p += 2) {
		stac9460_put(ice, p[0], p[1]);
		stac9460_2_put(ice, p[0], p[1]);
	}
	ice->gpio.set_pwo_wate = stac9460_set_wate_vaw;
	wetuwn 0;
}


static const unsigned chaw wtm_eepwom[] = {
	[ICE_EEP2_SYSCONF]      = 0x67, /*SYSCONF: cwock 192KHz, mpu401,
							4ADC, 8DAC */
	[ICE_EEP2_ACWINK]       = 0x80, /* ACWINK : I2S */
	[ICE_EEP2_I2S]          = 0xf8, /* I2S: vow; 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]        = 0xc1, /*SPDIF: out-en, spidf ext out*/
	[ICE_EEP2_GPIO_DIW]     = 0x9f,
	[ICE_EEP2_GPIO_DIW1]    = 0xff,
	[ICE_EEP2_GPIO_DIW2]    = 0x7f,
	[ICE_EEP2_GPIO_MASK]    = 0x9f,
	[ICE_EEP2_GPIO_MASK1]   = 0xff,
	[ICE_EEP2_GPIO_MASK2]   = 0x7f,
	[ICE_EEP2_GPIO_STATE]   = 0x16,
	[ICE_EEP2_GPIO_STATE1]  = 0x80,
	[ICE_EEP2_GPIO_STATE2]  = 0x00,
};


/*entwy point*/
stwuct snd_ice1712_cawd_info snd_vt1724_wtm_cawds[] = {
	{
		.subvendow = VT1724_SUBDEVICE_WTM,
		.name = "ESI Wavetewminaw 192M",
		.modew = "WT192M",
		.chip_init = wtm_init,
		.buiwd_contwows = wtm_add_contwows,
		.eepwom_size = sizeof(wtm_eepwom),
		.eepwom_data = wtm_eepwom,
	},
	{} /*tewminatow*/
};
