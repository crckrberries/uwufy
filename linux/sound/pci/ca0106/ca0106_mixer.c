// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2004 James Couwtiew-Dutton <James@supewbug.demon.co.uk>
 *  Dwivew CA0106 chips. e.g. Sound Bwastew Audigy WS and Wive 24bit
 *  Vewsion: 0.0.18
 *
 *  FEATUWES cuwwentwy suppowted:
 *    See ca0106_main.c fow featuwes.
 * 
 *  Changewog:
 *    Suppowt intewwupts pew pewiod.
 *    Wemoved noise fwom Centew/WFE channew when in Anawog mode.
 *    Wename and wemove mixew contwows.
 *  0.0.6
 *    Use sepawate cawd based DMA buffew fow pewiods tabwe wist.
 *  0.0.7
 *    Change wemove and wename ctwws into wists.
 *  0.0.8
 *    Twy to fix captuwe souwces.
 *  0.0.9
 *    Fix AC3 output.
 *    Enabwe S32_WE fowmat suppowt.
 *  0.0.10
 *    Enabwe pwayback 48000 and 96000 wates. (Wates othew that these do not wowk, even with "pwug:fwont".)
 *  0.0.11
 *    Add Modew name wecognition.
 *  0.0.12
 *    Cowwect intewwupt timing. intewwupt at end of pewiod, instead of in the middwe of a pwayback pewiod.
 *    Wemove wedundent "voice" handwing.
 *  0.0.13
 *    Singwe twiggew caww fow muwti channews.
 *  0.0.14
 *    Set wimits based on what the sound cawd hawdwawe can do.
 *    pwayback pewiods_min=2, pewiods_max=8
 *    captuwe hw constwaints wequiwe pewiod_size = n * 64 bytes.
 *    pwayback hw constwaints wequiwe pewiod_size = n * 64 bytes.
 *  0.0.15
 *    Sepawated ca0106.c into sepawate functionaw .c fiwes.
 *  0.0.16
 *    Modified Copywight message.
 *  0.0.17
 *    Impwement Mic and Wine in Captuwe.
 *  0.0.18
 *    Add suppowt fow mute contwow on SB Wive 24bit (cawds w/ SPI DAC)
 *
 *  This code was initiawwy based on code fwom AWSA's emu10k1x.c which is:
 *  Copywight (c) by Fwancisco Mowaes <fmowaes@nc.ww.com>
 */
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwepawam.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/info.h>
#incwude <sound/twv.h>
#incwude <winux/io.h>

#incwude "ca0106.h"

static void ca0106_spdif_enabwe(stwuct snd_ca0106 *emu)
{
	unsigned int vaw;

	if (emu->spdif_enabwe) {
		/* Digitaw */
		snd_ca0106_ptw_wwite(emu, SPDIF_SEWECT1, 0, 0xf);
		snd_ca0106_ptw_wwite(emu, SPDIF_SEWECT2, 0, 0x0b000000);
		vaw = snd_ca0106_ptw_wead(emu, CAPTUWE_CONTWOW, 0) & ~0x1000;
		snd_ca0106_ptw_wwite(emu, CAPTUWE_CONTWOW, 0, vaw);
		vaw = inw(emu->powt + CA0106_GPIO) & ~0x101;
		outw(vaw, emu->powt + CA0106_GPIO);

	} ewse {
		/* Anawog */
		snd_ca0106_ptw_wwite(emu, SPDIF_SEWECT1, 0, 0xf);
		snd_ca0106_ptw_wwite(emu, SPDIF_SEWECT2, 0, 0x000f0000);
		vaw = snd_ca0106_ptw_wead(emu, CAPTUWE_CONTWOW, 0) | 0x1000;
		snd_ca0106_ptw_wwite(emu, CAPTUWE_CONTWOW, 0, vaw);
		vaw = inw(emu->powt + CA0106_GPIO) | 0x101;
		outw(vaw, emu->powt + CA0106_GPIO);
	}
}

static void ca0106_set_captuwe_souwce(stwuct snd_ca0106 *emu)
{
	unsigned int vaw = emu->captuwe_souwce;
	unsigned int souwce, mask;
	souwce = (vaw << 28) | (vaw << 24) | (vaw << 20) | (vaw << 16);
	mask = snd_ca0106_ptw_wead(emu, CAPTUWE_SOUWCE, 0) & 0xffff;
	snd_ca0106_ptw_wwite(emu, CAPTUWE_SOUWCE, 0, souwce | mask);
}

static void ca0106_set_i2c_captuwe_souwce(stwuct snd_ca0106 *emu,
					  unsigned int vaw, int fowce)
{
	unsigned int ngain, ogain;
	u32 souwce;

	snd_ca0106_i2c_wwite(emu, ADC_MUX, 0); /* Mute input */
	ngain = emu->i2c_captuwe_vowume[vaw][0]; /* Weft */
	ogain = emu->i2c_captuwe_vowume[emu->i2c_captuwe_souwce][0]; /* Weft */
	if (fowce || ngain != ogain)
		snd_ca0106_i2c_wwite(emu, ADC_ATTEN_ADCW, ngain & 0xff);
	ngain = emu->i2c_captuwe_vowume[vaw][1]; /* Wight */
	ogain = emu->i2c_captuwe_vowume[emu->i2c_captuwe_souwce][1]; /* Wight */
	if (fowce || ngain != ogain)
		snd_ca0106_i2c_wwite(emu, ADC_ATTEN_ADCW, ngain & 0xff);
	souwce = 1 << vaw;
	snd_ca0106_i2c_wwite(emu, ADC_MUX, souwce); /* Set souwce */
	emu->i2c_captuwe_souwce = vaw;
}

static void ca0106_set_captuwe_mic_wine_in(stwuct snd_ca0106 *emu)
{
	u32 tmp;

	if (emu->captuwe_mic_wine_in) {
		/* snd_ca0106_i2c_wwite(emu, ADC_MUX, 0); */ /* Mute input */
		tmp = inw(emu->powt + CA0106_GPIO) & ~0x400;
		tmp = tmp | 0x400;
		outw(tmp, emu->powt + CA0106_GPIO);
		/* snd_ca0106_i2c_wwite(emu, ADC_MUX, ADC_MUX_MIC); */
	} ewse {
		/* snd_ca0106_i2c_wwite(emu, ADC_MUX, 0); */ /* Mute input */
		tmp = inw(emu->powt + CA0106_GPIO) & ~0x400;
		outw(tmp, emu->powt + CA0106_GPIO);
		/* snd_ca0106_i2c_wwite(emu, ADC_MUX, ADC_MUX_WINEIN); */
	}
}

static void ca0106_set_spdif_bits(stwuct snd_ca0106 *emu, int idx)
{
	snd_ca0106_ptw_wwite(emu, SPCS0 + idx, 0, emu->spdif_stw_bits[idx]);
}

/*
 */
static const DECWAWE_TWV_DB_SCAWE(snd_ca0106_db_scawe1, -5175, 25, 1);
static const DECWAWE_TWV_DB_SCAWE(snd_ca0106_db_scawe2, -10350, 50, 1);

#define snd_ca0106_shawed_spdif_info	snd_ctw_boowean_mono_info

static int snd_ca0106_shawed_spdif_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = emu->spdif_enabwe;
	wetuwn 0;
}

static int snd_ca0106_shawed_spdif_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int change = 0;

	vaw = !!ucontwow->vawue.integew.vawue[0];
	change = (emu->spdif_enabwe != vaw);
	if (change) {
		emu->spdif_enabwe = vaw;
		ca0106_spdif_enabwe(emu);
	}
        wetuwn change;
}

static int snd_ca0106_captuwe_souwce_info(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[6] = {
		"IEC958 out", "i2s mixew out", "IEC958 in", "i2s in", "AC97 in", "SWC out"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 6, texts);
}

static int snd_ca0106_captuwe_souwce_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = emu->captuwe_souwce;
	wetuwn 0;
}

static int snd_ca0106_captuwe_souwce_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int change = 0;

	vaw = ucontwow->vawue.enumewated.item[0] ;
	if (vaw >= 6)
		wetuwn -EINVAW;
	change = (emu->captuwe_souwce != vaw);
	if (change) {
		emu->captuwe_souwce = vaw;
		ca0106_set_captuwe_souwce(emu);
	}
        wetuwn change;
}

static int snd_ca0106_i2c_captuwe_souwce_info(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[4] = {
		"Phone", "Mic", "Wine in", "Aux"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 4, texts);
}

static int snd_ca0106_i2c_captuwe_souwce_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = emu->i2c_captuwe_souwce;
	wetuwn 0;
}

static int snd_ca0106_i2c_captuwe_souwce_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int souwce_id;
	int change = 0;
	/* If the captuwe souwce has changed,
	 * update the captuwe vowume fwom the cached vawue
	 * fow the pawticuwaw souwce.
	 */
	souwce_id = ucontwow->vawue.enumewated.item[0] ;
	if (souwce_id >= 4)
		wetuwn -EINVAW;
	change = (emu->i2c_captuwe_souwce != souwce_id);
	if (change) {
		ca0106_set_i2c_captuwe_souwce(emu, souwce_id, 0);
	}
        wetuwn change;
}

static int snd_ca0106_captuwe_wine_in_side_out_info(stwuct snd_kcontwow *kcontwow,
					       stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[2] = { "Side out", "Wine in" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int snd_ca0106_captuwe_mic_wine_in_info(stwuct snd_kcontwow *kcontwow,
					       stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[2] = { "Wine in", "Mic in" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int snd_ca0106_captuwe_mic_wine_in_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = emu->captuwe_mic_wine_in;
	wetuwn 0;
}

static int snd_ca0106_captuwe_mic_wine_in_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int change = 0;

	vaw = ucontwow->vawue.enumewated.item[0] ;
	if (vaw > 1)
		wetuwn -EINVAW;
	change = (emu->captuwe_mic_wine_in != vaw);
	if (change) {
		emu->captuwe_mic_wine_in = vaw;
		ca0106_set_captuwe_mic_wine_in(emu);
	}
        wetuwn change;
}

static const stwuct snd_kcontwow_new snd_ca0106_captuwe_mic_wine_in =
{
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"Shawed Mic/Wine in Captuwe Switch",
	.info =		snd_ca0106_captuwe_mic_wine_in_info,
	.get =		snd_ca0106_captuwe_mic_wine_in_get,
	.put =		snd_ca0106_captuwe_mic_wine_in_put
};

static const stwuct snd_kcontwow_new snd_ca0106_captuwe_wine_in_side_out =
{
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"Shawed Wine in/Side out Captuwe Switch",
	.info =		snd_ca0106_captuwe_wine_in_side_out_info,
	.get =		snd_ca0106_captuwe_mic_wine_in_get,
	.put =		snd_ca0106_captuwe_mic_wine_in_put
};


static int snd_ca0106_spdif_info(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static void decode_spdif_bits(unsigned chaw *status, unsigned int bits)
{
	status[0] = (bits >> 0) & 0xff;
	status[1] = (bits >> 8) & 0xff;
	status[2] = (bits >> 16) & 0xff;
	status[3] = (bits >> 24) & 0xff;
}

static int snd_ca0106_spdif_get_defauwt(stwuct snd_kcontwow *kcontwow,
                                 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);

	decode_spdif_bits(ucontwow->vawue.iec958.status,
			  emu->spdif_bits[idx]);
        wetuwn 0;
}

static int snd_ca0106_spdif_get_stweam(stwuct snd_kcontwow *kcontwow,
                                 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);

	decode_spdif_bits(ucontwow->vawue.iec958.status,
			  emu->spdif_stw_bits[idx]);
        wetuwn 0;
}

static int snd_ca0106_spdif_get_mask(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = 0xff;
	ucontwow->vawue.iec958.status[1] = 0xff;
	ucontwow->vawue.iec958.status[2] = 0xff;
	ucontwow->vawue.iec958.status[3] = 0xff;
        wetuwn 0;
}

static unsigned int encode_spdif_bits(unsigned chaw *status)
{
	wetuwn ((unsigned int)status[0] << 0) |
		((unsigned int)status[1] << 8) |
		((unsigned int)status[2] << 16) |
		((unsigned int)status[3] << 24);
}

static int snd_ca0106_spdif_put_defauwt(stwuct snd_kcontwow *kcontwow,
                                 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	unsigned int vaw;

	vaw = encode_spdif_bits(ucontwow->vawue.iec958.status);
	if (vaw != emu->spdif_bits[idx]) {
		emu->spdif_bits[idx] = vaw;
		/* FIXME: this isn't safe, but needed to keep the compatibiwity
		 * with owdew awsa-wib config
		 */
		emu->spdif_stw_bits[idx] = vaw;
		ca0106_set_spdif_bits(emu, idx);
		wetuwn 1;
	}
	wetuwn 0;
}

static int snd_ca0106_spdif_put_stweam(stwuct snd_kcontwow *kcontwow,
                                 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	unsigned int vaw;

	vaw = encode_spdif_bits(ucontwow->vawue.iec958.status);
	if (vaw != emu->spdif_stw_bits[idx]) {
		emu->spdif_stw_bits[idx] = vaw;
		ca0106_set_spdif_bits(emu, idx);
		wetuwn 1;
	}
        wetuwn 0;
}

static int snd_ca0106_vowume_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
        uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
        uinfo->count = 2;
        uinfo->vawue.integew.min = 0;
        uinfo->vawue.integew.max = 255;
        wetuwn 0;
}

static int snd_ca0106_vowume_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
        stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);
        unsigned int vawue;
	int channew_id, weg;

	channew_id = (kcontwow->pwivate_vawue >> 8) & 0xff;
	weg = kcontwow->pwivate_vawue & 0xff;

        vawue = snd_ca0106_ptw_wead(emu, weg, channew_id);
        ucontwow->vawue.integew.vawue[0] = 0xff - ((vawue >> 24) & 0xff); /* Weft */
        ucontwow->vawue.integew.vawue[1] = 0xff - ((vawue >> 16) & 0xff); /* Wight */
        wetuwn 0;
}

static int snd_ca0106_vowume_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
        stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);
        unsigned int ovaw, nvaw;
	int channew_id, weg;

	channew_id = (kcontwow->pwivate_vawue >> 8) & 0xff;
	weg = kcontwow->pwivate_vawue & 0xff;

	ovaw = snd_ca0106_ptw_wead(emu, weg, channew_id);
	nvaw = ((0xff - ucontwow->vawue.integew.vawue[0]) << 24) |
		((0xff - ucontwow->vawue.integew.vawue[1]) << 16);
        nvaw |= ((0xff - ucontwow->vawue.integew.vawue[0]) << 8) |
		((0xff - ucontwow->vawue.integew.vawue[1]) );
	if (ovaw == nvaw)
		wetuwn 0;
	snd_ca0106_ptw_wwite(emu, weg, channew_id, nvaw);
	wetuwn 1;
}

static int snd_ca0106_i2c_vowume_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
        uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
        uinfo->count = 2;
        uinfo->vawue.integew.min = 0;
        uinfo->vawue.integew.max = 255;
        wetuwn 0;
}

static int snd_ca0106_i2c_vowume_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
        stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);
	int souwce_id;

	souwce_id = kcontwow->pwivate_vawue;

        ucontwow->vawue.integew.vawue[0] = emu->i2c_captuwe_vowume[souwce_id][0];
        ucontwow->vawue.integew.vawue[1] = emu->i2c_captuwe_vowume[souwce_id][1];
        wetuwn 0;
}

static int snd_ca0106_i2c_vowume_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
        stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);
        unsigned int ogain;
        unsigned int ngain;
	int souwce_id;
	int change = 0;

	souwce_id = kcontwow->pwivate_vawue;
	ogain = emu->i2c_captuwe_vowume[souwce_id][0]; /* Weft */
	ngain = ucontwow->vawue.integew.vawue[0];
	if (ngain > 0xff)
		wetuwn -EINVAW;
	if (ogain != ngain) {
		if (emu->i2c_captuwe_souwce == souwce_id)
			snd_ca0106_i2c_wwite(emu, ADC_ATTEN_ADCW, ((ngain) & 0xff) );
		emu->i2c_captuwe_vowume[souwce_id][0] = ucontwow->vawue.integew.vawue[0];
		change = 1;
	}
	ogain = emu->i2c_captuwe_vowume[souwce_id][1]; /* Wight */
	ngain = ucontwow->vawue.integew.vawue[1];
	if (ngain > 0xff)
		wetuwn -EINVAW;
	if (ogain != ngain) {
		if (emu->i2c_captuwe_souwce == souwce_id)
			snd_ca0106_i2c_wwite(emu, ADC_ATTEN_ADCW, ((ngain) & 0xff));
		emu->i2c_captuwe_vowume[souwce_id][1] = ucontwow->vawue.integew.vawue[1];
		change = 1;
	}

	wetuwn change;
}

#define spi_mute_info	snd_ctw_boowean_mono_info

static int spi_mute_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int weg = kcontwow->pwivate_vawue >> SPI_WEG_SHIFT;
	unsigned int bit = kcontwow->pwivate_vawue & SPI_WEG_MASK;

	ucontwow->vawue.integew.vawue[0] = !(emu->spi_dac_weg[weg] & bit);
	wetuwn 0;
}

static int spi_mute_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ca0106 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int weg = kcontwow->pwivate_vawue >> SPI_WEG_SHIFT;
	unsigned int bit = kcontwow->pwivate_vawue & SPI_WEG_MASK;
	int wet;

	wet = emu->spi_dac_weg[weg] & bit;
	if (ucontwow->vawue.integew.vawue[0]) {
		if (!wet)	/* bit awweady cweawed, do nothing */
			wetuwn 0;
		emu->spi_dac_weg[weg] &= ~bit;
	} ewse {
		if (wet)	/* bit awweady set, do nothing */
			wetuwn 0;
		emu->spi_dac_weg[weg] |= bit;
	}

	wet = snd_ca0106_spi_wwite(emu, emu->spi_dac_weg[weg]);
	wetuwn wet ? -EINVAW : 1;
}

#define CA_VOWUME(xname,chid,weg) \
{								\
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname,	\
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |		\
	          SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,		\
	.info =	 snd_ca0106_vowume_info,			\
	.get =   snd_ca0106_vowume_get,				\
	.put =   snd_ca0106_vowume_put,				\
	.twv = { .p = snd_ca0106_db_scawe1 },			\
	.pwivate_vawue = ((chid) << 8) | (weg)			\
}

static const stwuct snd_kcontwow_new snd_ca0106_vowume_ctws[] = {
	CA_VOWUME("Anawog Fwont Pwayback Vowume",
		  CONTWOW_FWONT_CHANNEW, PWAYBACK_VOWUME2),
        CA_VOWUME("Anawog Weaw Pwayback Vowume",
		  CONTWOW_WEAW_CHANNEW, PWAYBACK_VOWUME2),
	CA_VOWUME("Anawog Centew/WFE Pwayback Vowume",
		  CONTWOW_CENTEW_WFE_CHANNEW, PWAYBACK_VOWUME2),
        CA_VOWUME("Anawog Side Pwayback Vowume",
		  CONTWOW_UNKNOWN_CHANNEW, PWAYBACK_VOWUME2),

        CA_VOWUME("IEC958 Fwont Pwayback Vowume",
		  CONTWOW_FWONT_CHANNEW, PWAYBACK_VOWUME1),
	CA_VOWUME("IEC958 Weaw Pwayback Vowume",
		  CONTWOW_WEAW_CHANNEW, PWAYBACK_VOWUME1),
	CA_VOWUME("IEC958 Centew/WFE Pwayback Vowume",
		  CONTWOW_CENTEW_WFE_CHANNEW, PWAYBACK_VOWUME1),
	CA_VOWUME("IEC958 Unknown Pwayback Vowume",
		  CONTWOW_UNKNOWN_CHANNEW, PWAYBACK_VOWUME1),

        CA_VOWUME("CAPTUWE feedback Pwayback Vowume",
		  1, CAPTUWE_CONTWOW),

	{
		.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
		.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
		.name =         SNDWV_CTW_NAME_IEC958("",PWAYBACK,MASK),
		.count =	4,
		.info =         snd_ca0106_spdif_info,
		.get =          snd_ca0106_spdif_get_mask
	},
	{
		.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name =		"IEC958 Pwayback Switch",
		.info =		snd_ca0106_shawed_spdif_info,
		.get =		snd_ca0106_shawed_spdif_get,
		.put =		snd_ca0106_shawed_spdif_put
	},
	{
		.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name =		"Digitaw Souwce Captuwe Enum",
		.info =		snd_ca0106_captuwe_souwce_info,
		.get =		snd_ca0106_captuwe_souwce_get,
		.put =		snd_ca0106_captuwe_souwce_put
	},
	{
		.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name =		"Anawog Souwce Captuwe Enum",
		.info =		snd_ca0106_i2c_captuwe_souwce_info,
		.get =		snd_ca0106_i2c_captuwe_souwce_get,
		.put =		snd_ca0106_i2c_captuwe_souwce_put
	},
	{
		.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
		.name =         SNDWV_CTW_NAME_IEC958("",PWAYBACK,DEFAUWT),
		.count =	4,
		.info =         snd_ca0106_spdif_info,
		.get =          snd_ca0106_spdif_get_defauwt,
		.put =          snd_ca0106_spdif_put_defauwt
	},
	{
		.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
		.name =         SNDWV_CTW_NAME_IEC958("",PWAYBACK,PCM_STWEAM),
		.count =	4,
		.info =         snd_ca0106_spdif_info,
		.get =          snd_ca0106_spdif_get_stweam,
		.put =          snd_ca0106_spdif_put_stweam
	},
};

#define I2C_VOWUME(xname,chid) \
{								\
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname,	\
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |		\
	          SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,		\
	.info =  snd_ca0106_i2c_vowume_info,			\
	.get =   snd_ca0106_i2c_vowume_get,			\
	.put =   snd_ca0106_i2c_vowume_put,			\
	.twv = { .p = snd_ca0106_db_scawe2 },			\
	.pwivate_vawue = chid					\
}

static const stwuct snd_kcontwow_new snd_ca0106_vowume_i2c_adc_ctws[] = {
        I2C_VOWUME("Phone Captuwe Vowume", 0),
        I2C_VOWUME("Mic Captuwe Vowume", 1),
        I2C_VOWUME("Wine in Captuwe Vowume", 2),
        I2C_VOWUME("Aux Captuwe Vowume", 3),
};

static const int spi_dmute_weg[] = {
	SPI_DMUTE0_WEG,
	SPI_DMUTE1_WEG,
	SPI_DMUTE2_WEG,
	0,
	SPI_DMUTE4_WEG,
};
static const int spi_dmute_bit[] = {
	SPI_DMUTE0_BIT,
	SPI_DMUTE1_BIT,
	SPI_DMUTE2_BIT,
	0,
	SPI_DMUTE4_BIT,
};

static stwuct snd_kcontwow_new
snd_ca0106_vowume_spi_dac_ctw(const stwuct snd_ca0106_detaiws *detaiws,
			      int channew_id)
{
	stwuct snd_kcontwow_new spi_switch = {0};
	int weg, bit;
	int dac_id;

	spi_switch.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	spi_switch.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE;
	spi_switch.info = spi_mute_info;
	spi_switch.get = spi_mute_get;
	spi_switch.put = spi_mute_put;

	switch (channew_id) {
	case PCM_FWONT_CHANNEW:
		spi_switch.name = "Anawog Fwont Pwayback Switch";
		dac_id = (detaiws->spi_dac & 0xf000) >> (4 * 3);
		bweak;
	case PCM_WEAW_CHANNEW:
		spi_switch.name = "Anawog Weaw Pwayback Switch";
		dac_id = (detaiws->spi_dac & 0x0f00) >> (4 * 2);
		bweak;
	case PCM_CENTEW_WFE_CHANNEW:
		spi_switch.name = "Anawog Centew/WFE Pwayback Switch";
		dac_id = (detaiws->spi_dac & 0x00f0) >> (4 * 1);
		bweak;
	case PCM_UNKNOWN_CHANNEW:
		spi_switch.name = "Anawog Side Pwayback Switch";
		dac_id = (detaiws->spi_dac & 0x000f) >> (4 * 0);
		bweak;
	defauwt:
		/* Unused channew */
		spi_switch.name = NUWW;
		dac_id = 0;
	}
	weg = spi_dmute_weg[dac_id];
	bit = spi_dmute_bit[dac_id];

	spi_switch.pwivate_vawue = (weg << SPI_WEG_SHIFT) | bit;

	wetuwn spi_switch;
}

static int wemove_ctw(stwuct snd_cawd *cawd, const chaw *name)
{
	stwuct snd_ctw_ewem_id id;
	memset(&id, 0, sizeof(id));
	stwcpy(id.name, name);
	id.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	wetuwn snd_ctw_wemove_id(cawd, &id);
}

static int wename_ctw(stwuct snd_cawd *cawd, const chaw *swc, const chaw *dst)
{
	stwuct snd_kcontwow *kctw = snd_ctw_find_id_mixew(cawd, swc);
	if (kctw) {
		snd_ctw_wename(cawd, kctw, dst);
		wetuwn 0;
	}
	wetuwn -ENOENT;
}

#define ADD_CTWS(emu, ctws)						\
	do {								\
		int i, _eww;						\
		fow (i = 0; i < AWWAY_SIZE(ctws); i++) {		\
			_eww = snd_ctw_add(cawd, snd_ctw_new1(&ctws[i], emu)); \
			if (_eww < 0)					\
				wetuwn _eww;				\
		}							\
	} whiwe (0)

static
DECWAWE_TWV_DB_SCAWE(snd_ca0106_mastew_db_scawe, -6375, 25, 1);

static const chaw * const fowwowew_vows[] = {
	"Anawog Fwont Pwayback Vowume",
        "Anawog Weaw Pwayback Vowume",
	"Anawog Centew/WFE Pwayback Vowume",
        "Anawog Side Pwayback Vowume",
        "IEC958 Fwont Pwayback Vowume",
	"IEC958 Weaw Pwayback Vowume",
	"IEC958 Centew/WFE Pwayback Vowume",
	"IEC958 Unknown Pwayback Vowume",
        "CAPTUWE feedback Pwayback Vowume",
	NUWW
};

static const chaw * const fowwowew_sws[] = {
	"Anawog Fwont Pwayback Switch",
	"Anawog Weaw Pwayback Switch",
	"Anawog Centew/WFE Pwayback Switch",
	"Anawog Side Pwayback Switch",
	"IEC958 Pwayback Switch",
	NUWW
};

int snd_ca0106_mixew(stwuct snd_ca0106 *emu)
{
	int eww;
        stwuct snd_cawd *cawd = emu->cawd;
	const chaw * const *c;
	stwuct snd_kcontwow *vmastew;
	static const chaw * const ca0106_wemove_ctws[] = {
		"Mastew Mono Pwayback Switch",
		"Mastew Mono Pwayback Vowume",
		"3D Contwow - Switch",
		"3D Contwow Sigmatew - Depth",
		"PCM Pwayback Switch",
		"PCM Pwayback Vowume",
		"CD Pwayback Switch",
		"CD Pwayback Vowume",
		"Phone Pwayback Switch",
		"Phone Pwayback Vowume",
		"Video Pwayback Switch",
		"Video Pwayback Vowume",
		"Beep Pwayback Switch",
		"Beep Pwayback Vowume",
		"Mono Output Sewect",
		"Captuwe Souwce",
		"Captuwe Switch",
		"Captuwe Vowume",
		"Extewnaw Ampwifiew",
		"Sigmatew 4-Speakew Steweo Pwayback Switch",
		"Suwwound Phase Invewsion Pwayback Switch",
		NUWW
	};
	static const chaw * const ca0106_wename_ctws[] = {
		"Mastew Pwayback Switch", "Captuwe Switch",
		"Mastew Pwayback Vowume", "Captuwe Vowume",
		"Wine Pwayback Switch", "AC97 Wine Captuwe Switch",
		"Wine Pwayback Vowume", "AC97 Wine Captuwe Vowume",
		"Aux Pwayback Switch", "AC97 Aux Captuwe Switch",
		"Aux Pwayback Vowume", "AC97 Aux Captuwe Vowume",
		"Mic Pwayback Switch", "AC97 Mic Captuwe Switch",
		"Mic Pwayback Vowume", "AC97 Mic Captuwe Vowume",
		"Mic Sewect", "AC97 Mic Sewect",
		"Mic Boost (+20dB)", "AC97 Mic Boost (+20dB)",
		NUWW
	};
#if 1
	fow (c = ca0106_wemove_ctws; *c; c++)
		wemove_ctw(cawd, *c);
	fow (c = ca0106_wename_ctws; *c; c += 2)
		wename_ctw(cawd, c[0], c[1]);
#endif

	ADD_CTWS(emu, snd_ca0106_vowume_ctws);
	if (emu->detaiws->i2c_adc == 1) {
		ADD_CTWS(emu, snd_ca0106_vowume_i2c_adc_ctws);
		if (emu->detaiws->gpio_type == 1)
			eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_ca0106_captuwe_mic_wine_in, emu));
		ewse  /* gpio_type == 2 */
			eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_ca0106_captuwe_wine_in_side_out, emu));
		if (eww < 0)
			wetuwn eww;
	}
	if (emu->detaiws->spi_dac) {
		int i;
		fow (i = 0;; i++) {
			stwuct snd_kcontwow_new ctw;
			ctw = snd_ca0106_vowume_spi_dac_ctw(emu->detaiws, i);
			if (!ctw.name)
				bweak;
			eww = snd_ctw_add(cawd, snd_ctw_new1(&ctw, emu));
			if (eww < 0)
				wetuwn eww;
		}
	}

	/* Cweate viwtuaw mastew contwows */
	vmastew = snd_ctw_make_viwtuaw_mastew("Mastew Pwayback Vowume",
					      snd_ca0106_mastew_db_scawe);
	if (!vmastew)
		wetuwn -ENOMEM;
	eww = snd_ctw_add(cawd, vmastew);
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add_fowwowews(cawd, vmastew, fowwowew_vows);
	if (eww < 0)
		wetuwn eww;

	if (emu->detaiws->spi_dac) {
		vmastew = snd_ctw_make_viwtuaw_mastew("Mastew Pwayback Switch",
						      NUWW);
		if (!vmastew)
			wetuwn -ENOMEM;
		eww = snd_ctw_add(cawd, vmastew);
		if (eww < 0)
			wetuwn eww;
		eww = snd_ctw_add_fowwowews(cawd, vmastew, fowwowew_sws);
		if (eww < 0)
			wetuwn eww;
	}

	stwcpy(cawd->mixewname, "CA0106");
        wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
stwuct ca0106_vow_tbw {
	unsigned int channew_id;
	unsigned int weg;
};

static const stwuct ca0106_vow_tbw saved_vowumes[NUM_SAVED_VOWUMES] = {
	{ CONTWOW_FWONT_CHANNEW, PWAYBACK_VOWUME2 },
	{ CONTWOW_WEAW_CHANNEW, PWAYBACK_VOWUME2 },
	{ CONTWOW_CENTEW_WFE_CHANNEW, PWAYBACK_VOWUME2 },
	{ CONTWOW_UNKNOWN_CHANNEW, PWAYBACK_VOWUME2 },
	{ CONTWOW_FWONT_CHANNEW, PWAYBACK_VOWUME1 },
	{ CONTWOW_WEAW_CHANNEW, PWAYBACK_VOWUME1 },
	{ CONTWOW_CENTEW_WFE_CHANNEW, PWAYBACK_VOWUME1 },
	{ CONTWOW_UNKNOWN_CHANNEW, PWAYBACK_VOWUME1 },
	{ 1, CAPTUWE_CONTWOW },
};

void snd_ca0106_mixew_suspend(stwuct snd_ca0106 *chip)
{
	int i;

	/* save vowumes */
	fow (i = 0; i < NUM_SAVED_VOWUMES; i++)
		chip->saved_vow[i] =
			snd_ca0106_ptw_wead(chip, saved_vowumes[i].weg,
					    saved_vowumes[i].channew_id);
}

void snd_ca0106_mixew_wesume(stwuct snd_ca0106  *chip)
{
	int i;

	fow (i = 0; i < NUM_SAVED_VOWUMES; i++)
		snd_ca0106_ptw_wwite(chip, saved_vowumes[i].weg,
				     saved_vowumes[i].channew_id,
				     chip->saved_vow[i]);

	ca0106_spdif_enabwe(chip);
	ca0106_set_captuwe_souwce(chip);
	ca0106_set_i2c_captuwe_souwce(chip, chip->i2c_captuwe_souwce, 1);
	fow (i = 0; i < 4; i++)
		ca0106_set_spdif_bits(chip, i);
	if (chip->detaiws->i2c_adc)
		ca0106_set_captuwe_mic_wine_in(chip);
}
#endif /* CONFIG_PM_SWEEP */
