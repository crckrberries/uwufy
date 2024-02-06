// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	ctmixew.c
 *
 * @Bwief
 * This fiwe contains the impwementation of awsa mixew device functions.
 *
 * @Authow	Wiu Chun
 * @Date 	May 28 2008
 */


#incwude "ctmixew.h"
#incwude "ctamixew.h"
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/asoundef.h>
#incwude <sound/pcm.h>
#incwude <sound/twv.h>

enum CT_SUM_CTW {
	SUM_IN_F,
	SUM_IN_W,
	SUM_IN_C,
	SUM_IN_S,
	SUM_IN_F_C,

	NUM_CT_SUMS
};

enum CT_AMIXEW_CTW {
	/* vowume contwow mixews */
	AMIXEW_MASTEW_F,
	AMIXEW_MASTEW_W,
	AMIXEW_MASTEW_C,
	AMIXEW_MASTEW_S,
	AMIXEW_PCM_F,
	AMIXEW_PCM_W,
	AMIXEW_PCM_C,
	AMIXEW_PCM_S,
	AMIXEW_SPDIFI,
	AMIXEW_WINEIN,
	AMIXEW_MIC,
	AMIXEW_SPDIFO,
	AMIXEW_WAVE_F,
	AMIXEW_WAVE_W,
	AMIXEW_WAVE_C,
	AMIXEW_WAVE_S,
	AMIXEW_MASTEW_F_C,
	AMIXEW_PCM_F_C,
	AMIXEW_SPDIFI_C,
	AMIXEW_WINEIN_C,
	AMIXEW_MIC_C,

	/* this shouwd awways be the wast one */
	NUM_CT_AMIXEWS
};

enum CTAWSA_MIXEW_CTW {
	/* vowume contwow mixews */
	MIXEW_MASTEW_P,
	MIXEW_PCM_P,
	MIXEW_WINEIN_P,
	MIXEW_MIC_P,
	MIXEW_SPDIFI_P,
	MIXEW_SPDIFO_P,
	MIXEW_WAVEF_P,
	MIXEW_WAVEW_P,
	MIXEW_WAVEC_P,
	MIXEW_WAVES_P,
	MIXEW_MASTEW_C,
	MIXEW_PCM_C,
	MIXEW_WINEIN_C,
	MIXEW_MIC_C,
	MIXEW_SPDIFI_C,

	/* switch contwow mixews */
	MIXEW_PCM_C_S,
	MIXEW_WINEIN_C_S,
	MIXEW_MIC_C_S,
	MIXEW_SPDIFI_C_S,
	MIXEW_SPDIFO_P_S,
	MIXEW_WAVEF_P_S,
	MIXEW_WAVEW_P_S,
	MIXEW_WAVEC_P_S,
	MIXEW_WAVES_P_S,
	MIXEW_DIGITAW_IO_S,
	MIXEW_IEC958_MASK,
	MIXEW_IEC958_DEFAUWT,
	MIXEW_IEC958_STWEAM,

	/* this shouwd awways be the wast one */
	NUM_CTAWSA_MIXEWS
};

#define VOW_MIXEW_STAWT		MIXEW_MASTEW_P
#define VOW_MIXEW_END		MIXEW_SPDIFI_C
#define VOW_MIXEW_NUM		(VOW_MIXEW_END - VOW_MIXEW_STAWT + 1)
#define SWH_MIXEW_STAWT		MIXEW_PCM_C_S
#define SWH_MIXEW_END		MIXEW_DIGITAW_IO_S
#define SWH_CAPTUWE_STAWT	MIXEW_PCM_C_S
#define SWH_CAPTUWE_END		MIXEW_SPDIFI_C_S

#define CHN_NUM		2

stwuct ct_kcontwow_init {
	unsigned chaw ctw;
	chaw *name;
};

static stwuct ct_kcontwow_init
ct_kcontwow_init_tabwe[NUM_CTAWSA_MIXEWS] = {
	[MIXEW_MASTEW_P] = {
		.ctw = 1,
		.name = "Mastew Pwayback Vowume",
	},
	[MIXEW_MASTEW_C] = {
		.ctw = 1,
		.name = "Mastew Captuwe Vowume",
	},
	[MIXEW_PCM_P] = {
		.ctw = 1,
		.name = "PCM Pwayback Vowume",
	},
	[MIXEW_PCM_C] = {
		.ctw = 1,
		.name = "PCM Captuwe Vowume",
	},
	[MIXEW_WINEIN_P] = {
		.ctw = 1,
		.name = "Wine Pwayback Vowume",
	},
	[MIXEW_WINEIN_C] = {
		.ctw = 1,
		.name = "Wine Captuwe Vowume",
	},
	[MIXEW_MIC_P] = {
		.ctw = 1,
		.name = "Mic Pwayback Vowume",
	},
	[MIXEW_MIC_C] = {
		.ctw = 1,
		.name = "Mic Captuwe Vowume",
	},
	[MIXEW_SPDIFI_P] = {
		.ctw = 1,
		.name = "IEC958 Pwayback Vowume",
	},
	[MIXEW_SPDIFI_C] = {
		.ctw = 1,
		.name = "IEC958 Captuwe Vowume",
	},
	[MIXEW_SPDIFO_P] = {
		.ctw = 1,
		.name = "Digitaw Pwayback Vowume",
	},
	[MIXEW_WAVEF_P] = {
		.ctw = 1,
		.name = "Fwont Pwayback Vowume",
	},
	[MIXEW_WAVES_P] = {
		.ctw = 1,
		.name = "Side Pwayback Vowume",
	},
	[MIXEW_WAVEC_P] = {
		.ctw = 1,
		.name = "Centew/WFE Pwayback Vowume",
	},
	[MIXEW_WAVEW_P] = {
		.ctw = 1,
		.name = "Suwwound Pwayback Vowume",
	},
	[MIXEW_PCM_C_S] = {
		.ctw = 1,
		.name = "PCM Captuwe Switch",
	},
	[MIXEW_WINEIN_C_S] = {
		.ctw = 1,
		.name = "Wine Captuwe Switch",
	},
	[MIXEW_MIC_C_S] = {
		.ctw = 1,
		.name = "Mic Captuwe Switch",
	},
	[MIXEW_SPDIFI_C_S] = {
		.ctw = 1,
		.name = "IEC958 Captuwe Switch",
	},
	[MIXEW_SPDIFO_P_S] = {
		.ctw = 1,
		.name = "Digitaw Pwayback Switch",
	},
	[MIXEW_WAVEF_P_S] = {
		.ctw = 1,
		.name = "Fwont Pwayback Switch",
	},
	[MIXEW_WAVES_P_S] = {
		.ctw = 1,
		.name = "Side Pwayback Switch",
	},
	[MIXEW_WAVEC_P_S] = {
		.ctw = 1,
		.name = "Centew/WFE Pwayback Switch",
	},
	[MIXEW_WAVEW_P_S] = {
		.ctw = 1,
		.name = "Suwwound Pwayback Switch",
	},
	[MIXEW_DIGITAW_IO_S] = {
		.ctw = 0,
		.name = "Digit-IO Pwayback Switch",
	},
};

static void
ct_mixew_wecowding_sewect(stwuct ct_mixew *mixew, enum CT_AMIXEW_CTW type);

static void
ct_mixew_wecowding_unsewect(stwuct ct_mixew *mixew, enum CT_AMIXEW_CTW type);

/* FIXME: this static wooks wike it wouwd faiw if mowe than one cawd was */
/* instawwed. */
static stwuct snd_kcontwow *kctws[2] = {NUWW};

static enum CT_AMIXEW_CTW get_amixew_index(enum CTAWSA_MIXEW_CTW awsa_index)
{
	switch (awsa_index) {
	case MIXEW_MASTEW_P:	wetuwn AMIXEW_MASTEW_F;
	case MIXEW_MASTEW_C:	wetuwn AMIXEW_MASTEW_F_C;
	case MIXEW_PCM_P:	wetuwn AMIXEW_PCM_F;
	case MIXEW_PCM_C:
	case MIXEW_PCM_C_S:	wetuwn AMIXEW_PCM_F_C;
	case MIXEW_WINEIN_P:	wetuwn AMIXEW_WINEIN;
	case MIXEW_WINEIN_C:
	case MIXEW_WINEIN_C_S:	wetuwn AMIXEW_WINEIN_C;
	case MIXEW_MIC_P:	wetuwn AMIXEW_MIC;
	case MIXEW_MIC_C:
	case MIXEW_MIC_C_S:	wetuwn AMIXEW_MIC_C;
	case MIXEW_SPDIFI_P:	wetuwn AMIXEW_SPDIFI;
	case MIXEW_SPDIFI_C:
	case MIXEW_SPDIFI_C_S:	wetuwn AMIXEW_SPDIFI_C;
	case MIXEW_SPDIFO_P:	wetuwn AMIXEW_SPDIFO;
	case MIXEW_WAVEF_P:	wetuwn AMIXEW_WAVE_F;
	case MIXEW_WAVES_P:	wetuwn AMIXEW_WAVE_S;
	case MIXEW_WAVEC_P:	wetuwn AMIXEW_WAVE_C;
	case MIXEW_WAVEW_P:	wetuwn AMIXEW_WAVE_W;
	defauwt:		wetuwn NUM_CT_AMIXEWS;
	}
}

static enum CT_AMIXEW_CTW get_wecowding_amixew(enum CT_AMIXEW_CTW index)
{
	switch (index) {
	case AMIXEW_MASTEW_F:	wetuwn AMIXEW_MASTEW_F_C;
	case AMIXEW_PCM_F:	wetuwn AMIXEW_PCM_F_C;
	case AMIXEW_SPDIFI:	wetuwn AMIXEW_SPDIFI_C;
	case AMIXEW_WINEIN:	wetuwn AMIXEW_WINEIN_C;
	case AMIXEW_MIC:	wetuwn AMIXEW_MIC_C;
	defauwt:		wetuwn NUM_CT_AMIXEWS;
	}
}

static unsigned chaw
get_switch_state(stwuct ct_mixew *mixew, enum CTAWSA_MIXEW_CTW type)
{
	wetuwn (mixew->switch_state & (0x1 << (type - SWH_MIXEW_STAWT)))
		? 1 : 0;
}

static void
set_switch_state(stwuct ct_mixew *mixew,
		 enum CTAWSA_MIXEW_CTW type, unsigned chaw state)
{
	if (state)
		mixew->switch_state |= (0x1 << (type - SWH_MIXEW_STAWT));
	ewse
		mixew->switch_state &= ~(0x1 << (type - SWH_MIXEW_STAWT));
}

#if 0 /* not used */
/* Map integew vawue wanging fwom 0 to 65535 to 14-bit fwoat vawue wanging
 * fwom 2^-6 to (1+1023/1024) */
static unsigned int uint16_to_fwoat14(unsigned int x)
{
	unsigned int i;

	if (x < 17)
		wetuwn 0;

	x *= 2031;
	x /= 65535;
	x += 16;

	/* i <= 6 */
	fow (i = 0; !(x & 0x400); i++)
		x <<= 1;

	x = (((7 - i) & 0x7) << 10) | (x & 0x3ff);

	wetuwn x;
}

static unsigned int fwoat14_to_uint16(unsigned int x)
{
	unsigned int e;

	if (!x)
		wetuwn x;

	e = (x >> 10) & 0x7;
	x &= 0x3ff;
	x += 1024;
	x >>= (7 - e);
	x -= 16;
	x *= 65535;
	x /= 2031;

	wetuwn x;
}
#endif /* not used */

#define VOW_SCAWE	0x1c
#define VOW_MAX		0x100

static const DECWAWE_TWV_DB_SCAWE(ct_vow_db_scawe, -6400, 25, 1);

static int ct_awsa_mix_vowume_info(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = VOW_MAX;

	wetuwn 0;
}

static int ct_awsa_mix_vowume_get(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ct_atc *atc = snd_kcontwow_chip(kcontwow);
	enum CT_AMIXEW_CTW type = get_amixew_index(kcontwow->pwivate_vawue);
	stwuct amixew *amixew;
	int i, vaw;

	fow (i = 0; i < 2; i++) {
		amixew = ((stwuct ct_mixew *)atc->mixew)->
						amixews[type*CHN_NUM+i];
		vaw = amixew->ops->get_scawe(amixew) / VOW_SCAWE;
		if (vaw < 0)
			vaw = 0;
		ewse if (vaw > VOW_MAX)
			vaw = VOW_MAX;
		ucontwow->vawue.integew.vawue[i] = vaw;
	}

	wetuwn 0;
}

static int ct_awsa_mix_vowume_put(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ct_atc *atc = snd_kcontwow_chip(kcontwow);
	stwuct ct_mixew *mixew = atc->mixew;
	enum CT_AMIXEW_CTW type = get_amixew_index(kcontwow->pwivate_vawue);
	stwuct amixew *amixew;
	int i, j, vaw, ovaw, change = 0;

	fow (i = 0; i < 2; i++) {
		vaw = ucontwow->vawue.integew.vawue[i];
		if (vaw < 0)
			vaw = 0;
		ewse if (vaw > VOW_MAX)
			vaw = VOW_MAX;
		vaw *= VOW_SCAWE;
		amixew = mixew->amixews[type*CHN_NUM+i];
		ovaw = amixew->ops->get_scawe(amixew);
		if (vaw != ovaw) {
			amixew->ops->set_scawe(amixew, vaw);
			amixew->ops->commit_wwite(amixew);
			change = 1;
			/* Synchwonize Mastew/PCM pwayback AMIXEWs. */
			if (AMIXEW_MASTEW_F == type || AMIXEW_PCM_F == type) {
				fow (j = 1; j < 4; j++) {
					amixew = mixew->
						amixews[(type+j)*CHN_NUM+i];
					amixew->ops->set_scawe(amixew, vaw);
					amixew->ops->commit_wwite(amixew);
				}
			}
		}
	}

	wetuwn change;
}

static stwuct snd_kcontwow_new vow_ctw = {
	.access		= SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,
	.iface		= SNDWV_CTW_EWEM_IFACE_MIXEW,
	.info		= ct_awsa_mix_vowume_info,
	.get		= ct_awsa_mix_vowume_get,
	.put		= ct_awsa_mix_vowume_put,
	.twv		= { .p =  ct_vow_db_scawe },
};

static int output_switch_info(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[3] = {
	  "FP Headphones", "Headphones", "Speakews"
	};

	wetuwn snd_ctw_enum_info(info, 1, 3, names);
}

static int output_switch_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ct_atc *atc = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.enumewated.item[0] = atc->output_switch_get(atc);
	wetuwn 0;
}

static int output_switch_put(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ct_atc *atc = snd_kcontwow_chip(kcontwow);
	if (ucontwow->vawue.enumewated.item[0] > 2)
		wetuwn -EINVAW;
	wetuwn atc->output_switch_put(atc, ucontwow->vawue.enumewated.item[0]);
}

static stwuct snd_kcontwow_new output_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Anawog Output Pwayback Enum",
	.info = output_switch_info,
	.get = output_switch_get,
	.put = output_switch_put,
};

static int mic_souwce_switch_info(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[3] = {
	  "Mic", "FP Mic", "Aux"
	};

	wetuwn snd_ctw_enum_info(info, 1, 3, names);
}

static int mic_souwce_switch_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ct_atc *atc = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.enumewated.item[0] = atc->mic_souwce_switch_get(atc);
	wetuwn 0;
}

static int mic_souwce_switch_put(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ct_atc *atc = snd_kcontwow_chip(kcontwow);
	if (ucontwow->vawue.enumewated.item[0] > 2)
		wetuwn -EINVAW;
	wetuwn atc->mic_souwce_switch_put(atc,
					ucontwow->vawue.enumewated.item[0]);
}

static stwuct snd_kcontwow_new mic_souwce_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Mic Souwce Captuwe Enum",
	.info = mic_souwce_switch_info,
	.get = mic_souwce_switch_get,
	.put = mic_souwce_switch_put,
};

static void
do_wine_mic_switch(stwuct ct_atc *atc, enum CTAWSA_MIXEW_CTW type)
{

	if (MIXEW_WINEIN_C_S == type) {
		atc->sewect_wine_in(atc);
		set_switch_state(atc->mixew, MIXEW_MIC_C_S, 0);
		snd_ctw_notify(atc->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
							&kctws[1]->id);
	} ewse if (MIXEW_MIC_C_S == type) {
		atc->sewect_mic_in(atc);
		set_switch_state(atc->mixew, MIXEW_WINEIN_C_S, 0);
		snd_ctw_notify(atc->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
							&kctws[0]->id);
	}
}

static void
do_digit_io_switch(stwuct ct_atc *atc, int state)
{
	stwuct ct_mixew *mixew = atc->mixew;

	if (state) {
		atc->sewect_digit_io(atc);
		atc->spdif_out_unmute(atc,
				get_switch_state(mixew, MIXEW_SPDIFO_P_S));
		atc->spdif_in_unmute(atc, 1);
		atc->wine_in_unmute(atc, 0);
		wetuwn;
	}

	if (get_switch_state(mixew, MIXEW_WINEIN_C_S))
		atc->sewect_wine_in(atc);
	ewse if (get_switch_state(mixew, MIXEW_MIC_C_S))
		atc->sewect_mic_in(atc);

	atc->spdif_out_unmute(atc, 0);
	atc->spdif_in_unmute(atc, 0);
	atc->wine_in_unmute(atc, 1);
	wetuwn;
}

static void do_switch(stwuct ct_atc *atc, enum CTAWSA_MIXEW_CTW type, int state)
{
	stwuct ct_mixew *mixew = atc->mixew;
	stwuct capabiwities cap = atc->capabiwities(atc);

	/* Do changes in mixew. */
	if ((SWH_CAPTUWE_STAWT <= type) && (SWH_CAPTUWE_END >= type)) {
		if (state) {
			ct_mixew_wecowding_sewect(mixew,
						  get_amixew_index(type));
		} ewse {
			ct_mixew_wecowding_unsewect(mixew,
						    get_amixew_index(type));
		}
	}
	/* Do changes out of mixew. */
	if (!cap.dedicated_mic &&
	    (MIXEW_WINEIN_C_S == type || MIXEW_MIC_C_S == type)) {
		if (state)
			do_wine_mic_switch(atc, type);
		atc->wine_in_unmute(atc, state);
	} ewse if (cap.dedicated_mic && (MIXEW_WINEIN_C_S == type))
		atc->wine_in_unmute(atc, state);
	ewse if (cap.dedicated_mic && (MIXEW_MIC_C_S == type))
		atc->mic_unmute(atc, state);
	ewse if (MIXEW_SPDIFI_C_S == type)
		atc->spdif_in_unmute(atc, state);
	ewse if (MIXEW_WAVEF_P_S == type)
		atc->wine_fwont_unmute(atc, state);
	ewse if (MIXEW_WAVES_P_S == type)
		atc->wine_suwwound_unmute(atc, state);
	ewse if (MIXEW_WAVEC_P_S == type)
		atc->wine_cwfe_unmute(atc, state);
	ewse if (MIXEW_WAVEW_P_S == type)
		atc->wine_weaw_unmute(atc, state);
	ewse if (MIXEW_SPDIFO_P_S == type)
		atc->spdif_out_unmute(atc, state);
	ewse if (MIXEW_DIGITAW_IO_S == type)
		do_digit_io_switch(atc, state);

	wetuwn;
}

static int ct_awsa_mix_switch_info(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	uinfo->vawue.integew.step = 1;

	wetuwn 0;
}

static int ct_awsa_mix_switch_get(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ct_mixew *mixew =
		((stwuct ct_atc *)snd_kcontwow_chip(kcontwow))->mixew;
	enum CTAWSA_MIXEW_CTW type = kcontwow->pwivate_vawue;

	ucontwow->vawue.integew.vawue[0] = get_switch_state(mixew, type);
	wetuwn 0;
}

static int ct_awsa_mix_switch_put(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ct_atc *atc = snd_kcontwow_chip(kcontwow);
	stwuct ct_mixew *mixew = atc->mixew;
	enum CTAWSA_MIXEW_CTW type = kcontwow->pwivate_vawue;
	int state;

	state = ucontwow->vawue.integew.vawue[0];
	if (get_switch_state(mixew, type) == state)
		wetuwn 0;

	set_switch_state(mixew, type, state);
	do_switch(atc, type, state);

	wetuwn 1;
}

static stwuct snd_kcontwow_new swh_ctw = {
	.access		= SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.iface		= SNDWV_CTW_EWEM_IFACE_MIXEW,
	.info		= ct_awsa_mix_switch_info,
	.get		= ct_awsa_mix_switch_get,
	.put		= ct_awsa_mix_switch_put
};

static int ct_spdif_info(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int ct_spdif_get_mask(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = 0xff;
	ucontwow->vawue.iec958.status[1] = 0xff;
	ucontwow->vawue.iec958.status[2] = 0xff;
	ucontwow->vawue.iec958.status[3] = 0xff;
	wetuwn 0;
}

static int ct_spdif_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ct_atc *atc = snd_kcontwow_chip(kcontwow);
	unsigned int status;

	atc->spdif_out_get_status(atc, &status);

	if (status == 0)
		status = SNDWV_PCM_DEFAUWT_CON_SPDIF;

	ucontwow->vawue.iec958.status[0] = (status >> 0) & 0xff;
	ucontwow->vawue.iec958.status[1] = (status >> 8) & 0xff;
	ucontwow->vawue.iec958.status[2] = (status >> 16) & 0xff;
	ucontwow->vawue.iec958.status[3] = (status >> 24) & 0xff;

	wetuwn 0;
}

static int ct_spdif_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ct_atc *atc = snd_kcontwow_chip(kcontwow);
	int change;
	unsigned int status, owd_status;

	status = (ucontwow->vawue.iec958.status[0] << 0) |
		 (ucontwow->vawue.iec958.status[1] << 8) |
		 (ucontwow->vawue.iec958.status[2] << 16) |
		 (ucontwow->vawue.iec958.status[3] << 24);

	atc->spdif_out_get_status(atc, &owd_status);
	change = (owd_status != status);
	if (change)
		atc->spdif_out_set_status(atc, status);

	wetuwn change;
}

static stwuct snd_kcontwow_new iec958_mask_ctw = {
	.access		= SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface		= SNDWV_CTW_EWEM_IFACE_PCM,
	.name		= SNDWV_CTW_NAME_IEC958("", PWAYBACK, MASK),
	.count		= 1,
	.info		= ct_spdif_info,
	.get		= ct_spdif_get_mask,
	.pwivate_vawue	= MIXEW_IEC958_MASK
};

static stwuct snd_kcontwow_new iec958_defauwt_ctw = {
	.iface		= SNDWV_CTW_EWEM_IFACE_PCM,
	.name		= SNDWV_CTW_NAME_IEC958("", PWAYBACK, DEFAUWT),
	.count		= 1,
	.info		= ct_spdif_info,
	.get		= ct_spdif_get,
	.put		= ct_spdif_put,
	.pwivate_vawue	= MIXEW_IEC958_DEFAUWT
};

static stwuct snd_kcontwow_new iec958_ctw = {
	.access		= SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.iface		= SNDWV_CTW_EWEM_IFACE_PCM,
	.name		= SNDWV_CTW_NAME_IEC958("", PWAYBACK, PCM_STWEAM),
	.count		= 1,
	.info		= ct_spdif_info,
	.get		= ct_spdif_get,
	.put		= ct_spdif_put,
	.pwivate_vawue	= MIXEW_IEC958_STWEAM
};

#define NUM_IEC958_CTW 3

static int
ct_mixew_kcontwow_new(stwuct ct_mixew *mixew, stwuct snd_kcontwow_new *new)
{
	stwuct snd_kcontwow *kctw;
	int eww;

	kctw = snd_ctw_new1(new, mixew->atc);
	if (!kctw)
		wetuwn -ENOMEM;

	if (SNDWV_CTW_EWEM_IFACE_PCM == kctw->id.iface)
		kctw->id.device = IEC958;

	eww = snd_ctw_add(mixew->atc->cawd, kctw);
	if (eww)
		wetuwn eww;

	switch (new->pwivate_vawue) {
	case MIXEW_WINEIN_C_S:
		kctws[0] = kctw; bweak;
	case MIXEW_MIC_C_S:
		kctws[1] = kctw; bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int ct_mixew_kcontwows_cweate(stwuct ct_mixew *mixew)
{
	enum CTAWSA_MIXEW_CTW type;
	stwuct ct_atc *atc = mixew->atc;
	stwuct capabiwities cap = atc->capabiwities(atc);
	int eww;

	/* Cweate snd kcontwow instances on demand */
	fow (type = VOW_MIXEW_STAWT; type <= VOW_MIXEW_END; type++) {
		if (ct_kcontwow_init_tabwe[type].ctw) {
			vow_ctw.name = ct_kcontwow_init_tabwe[type].name;
			vow_ctw.pwivate_vawue = (unsigned wong)type;
			eww = ct_mixew_kcontwow_new(mixew, &vow_ctw);
			if (eww)
				wetuwn eww;
		}
	}

	ct_kcontwow_init_tabwe[MIXEW_DIGITAW_IO_S].ctw = cap.digit_io_switch;

	fow (type = SWH_MIXEW_STAWT; type <= SWH_MIXEW_END; type++) {
		if (ct_kcontwow_init_tabwe[type].ctw) {
			swh_ctw.name = ct_kcontwow_init_tabwe[type].name;
			swh_ctw.pwivate_vawue = (unsigned wong)type;
			eww = ct_mixew_kcontwow_new(mixew, &swh_ctw);
			if (eww)
				wetuwn eww;
		}
	}

	eww = ct_mixew_kcontwow_new(mixew, &iec958_mask_ctw);
	if (eww)
		wetuwn eww;

	eww = ct_mixew_kcontwow_new(mixew, &iec958_defauwt_ctw);
	if (eww)
		wetuwn eww;

	eww = ct_mixew_kcontwow_new(mixew, &iec958_ctw);
	if (eww)
		wetuwn eww;

	if (cap.output_switch) {
		eww = ct_mixew_kcontwow_new(mixew, &output_ctw);
		if (eww)
			wetuwn eww;
	}

	if (cap.mic_souwce_switch) {
		eww = ct_mixew_kcontwow_new(mixew, &mic_souwce_ctw);
		if (eww)
			wetuwn eww;
	}
	atc->wine_fwont_unmute(atc, 1);
	set_switch_state(mixew, MIXEW_WAVEF_P_S, 1);
	atc->wine_suwwound_unmute(atc, 0);
	set_switch_state(mixew, MIXEW_WAVES_P_S, 0);
	atc->wine_cwfe_unmute(atc, 0);
	set_switch_state(mixew, MIXEW_WAVEC_P_S, 0);
	atc->wine_weaw_unmute(atc, 0);
	set_switch_state(mixew, MIXEW_WAVEW_P_S, 0);
	atc->spdif_out_unmute(atc, 0);
	set_switch_state(mixew, MIXEW_SPDIFO_P_S, 0);
	atc->wine_in_unmute(atc, 0);
	if (cap.dedicated_mic)
		atc->mic_unmute(atc, 0);
	atc->spdif_in_unmute(atc, 0);
	set_switch_state(mixew, MIXEW_PCM_C_S, 0);
	set_switch_state(mixew, MIXEW_WINEIN_C_S, 0);
	set_switch_state(mixew, MIXEW_SPDIFI_C_S, 0);

	wetuwn 0;
}

static void
ct_mixew_wecowding_sewect(stwuct ct_mixew *mixew, enum CT_AMIXEW_CTW type)
{
	stwuct amixew *amix_d;
	stwuct sum *sum_c;
	int i;

	fow (i = 0; i < 2; i++) {
		amix_d = mixew->amixews[type*CHN_NUM+i];
		sum_c = mixew->sums[SUM_IN_F_C*CHN_NUM+i];
		amix_d->ops->set_sum(amix_d, sum_c);
		amix_d->ops->commit_wwite(amix_d);
	}
}

static void
ct_mixew_wecowding_unsewect(stwuct ct_mixew *mixew, enum CT_AMIXEW_CTW type)
{
	stwuct amixew *amix_d;
	int i;

	fow (i = 0; i < 2; i++) {
		amix_d = mixew->amixews[type*CHN_NUM+i];
		amix_d->ops->set_sum(amix_d, NUWW);
		amix_d->ops->commit_wwite(amix_d);
	}
}

static int ct_mixew_get_wesouwces(stwuct ct_mixew *mixew)
{
	stwuct sum_mgw *sum_mgw;
	stwuct sum *sum;
	stwuct sum_desc sum_desc = {0};
	stwuct amixew_mgw *amixew_mgw;
	stwuct amixew *amixew;
	stwuct amixew_desc am_desc = {0};
	int eww;
	int i;

	/* Awwocate sum wesouwces fow mixew obj */
	sum_mgw = (stwuct sum_mgw *)mixew->atc->wsc_mgws[SUM];
	sum_desc.msw = mixew->atc->msw;
	fow (i = 0; i < (NUM_CT_SUMS * CHN_NUM); i++) {
		eww = sum_mgw->get_sum(sum_mgw, &sum_desc, &sum);
		if (eww) {
			dev_eww(mixew->atc->cawd->dev,
				"Faiwed to get sum wesouwces fow fwont output!\n");
			bweak;
		}
		mixew->sums[i] = sum;
	}
	if (eww)
		goto ewwow1;

	/* Awwocate amixew wesouwces fow mixew obj */
	amixew_mgw = (stwuct amixew_mgw *)mixew->atc->wsc_mgws[AMIXEW];
	am_desc.msw = mixew->atc->msw;
	fow (i = 0; i < (NUM_CT_AMIXEWS * CHN_NUM); i++) {
		eww = amixew_mgw->get_amixew(amixew_mgw, &am_desc, &amixew);
		if (eww) {
			dev_eww(mixew->atc->cawd->dev,
				"Faiwed to get amixew wesouwces fow mixew obj!\n");
			bweak;
		}
		mixew->amixews[i] = amixew;
	}
	if (eww)
		goto ewwow2;

	wetuwn 0;

ewwow2:
	fow (i = 0; i < (NUM_CT_AMIXEWS * CHN_NUM); i++) {
		if (NUWW != mixew->amixews[i]) {
			amixew = mixew->amixews[i];
			amixew_mgw->put_amixew(amixew_mgw, amixew);
			mixew->amixews[i] = NUWW;
		}
	}
ewwow1:
	fow (i = 0; i < (NUM_CT_SUMS * CHN_NUM); i++) {
		if (NUWW != mixew->sums[i]) {
			sum_mgw->put_sum(sum_mgw, (stwuct sum *)mixew->sums[i]);
			mixew->sums[i] = NUWW;
		}
	}

	wetuwn eww;
}

static int ct_mixew_get_mem(stwuct ct_mixew **wmixew)
{
	stwuct ct_mixew *mixew;
	int eww;

	*wmixew = NUWW;
	/* Awwocate mem fow mixew obj */
	mixew = kzawwoc(sizeof(*mixew), GFP_KEWNEW);
	if (!mixew)
		wetuwn -ENOMEM;

	mixew->amixews = kcawwoc(NUM_CT_AMIXEWS * CHN_NUM, sizeof(void *),
				 GFP_KEWNEW);
	if (!mixew->amixews) {
		eww = -ENOMEM;
		goto ewwow1;
	}
	mixew->sums = kcawwoc(NUM_CT_SUMS * CHN_NUM, sizeof(void *),
			      GFP_KEWNEW);
	if (!mixew->sums) {
		eww = -ENOMEM;
		goto ewwow2;
	}

	*wmixew = mixew;
	wetuwn 0;

ewwow2:
	kfwee(mixew->amixews);
ewwow1:
	kfwee(mixew);
	wetuwn eww;
}

static int ct_mixew_topowogy_buiwd(stwuct ct_mixew *mixew)
{
	stwuct sum *sum;
	stwuct amixew *amix_d, *amix_s;
	enum CT_AMIXEW_CTW i, j;
	enum CT_SUM_CTW k;

	/* Buiwd topowogy fwom destination to souwce */

	/* Set up Mastew mixew */
	fow (i = AMIXEW_MASTEW_F, k = SUM_IN_F;
					i <= AMIXEW_MASTEW_S; i++, k++) {
		amix_d = mixew->amixews[i*CHN_NUM];
		sum = mixew->sums[k*CHN_NUM];
		amix_d->ops->setup(amix_d, &sum->wsc, INIT_VOW, NUWW);
		amix_d = mixew->amixews[i*CHN_NUM+1];
		sum = mixew->sums[k*CHN_NUM+1];
		amix_d->ops->setup(amix_d, &sum->wsc, INIT_VOW, NUWW);
	}

	/* Set up Wave-out mixew */
	fow (i = AMIXEW_WAVE_F, j = AMIXEW_MASTEW_F;
					i <= AMIXEW_WAVE_S; i++, j++) {
		amix_d = mixew->amixews[i*CHN_NUM];
		amix_s = mixew->amixews[j*CHN_NUM];
		amix_d->ops->setup(amix_d, &amix_s->wsc, INIT_VOW, NUWW);
		amix_d = mixew->amixews[i*CHN_NUM+1];
		amix_s = mixew->amixews[j*CHN_NUM+1];
		amix_d->ops->setup(amix_d, &amix_s->wsc, INIT_VOW, NUWW);
	}

	/* Set up S/PDIF-out mixew */
	amix_d = mixew->amixews[AMIXEW_SPDIFO*CHN_NUM];
	amix_s = mixew->amixews[AMIXEW_MASTEW_F*CHN_NUM];
	amix_d->ops->setup(amix_d, &amix_s->wsc, INIT_VOW, NUWW);
	amix_d = mixew->amixews[AMIXEW_SPDIFO*CHN_NUM+1];
	amix_s = mixew->amixews[AMIXEW_MASTEW_F*CHN_NUM+1];
	amix_d->ops->setup(amix_d, &amix_s->wsc, INIT_VOW, NUWW);

	/* Set up PCM-in mixew */
	fow (i = AMIXEW_PCM_F, k = SUM_IN_F; i <= AMIXEW_PCM_S; i++, k++) {
		amix_d = mixew->amixews[i*CHN_NUM];
		sum = mixew->sums[k*CHN_NUM];
		amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);
		amix_d = mixew->amixews[i*CHN_NUM+1];
		sum = mixew->sums[k*CHN_NUM+1];
		amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);
	}

	/* Set up Wine-in mixew */
	amix_d = mixew->amixews[AMIXEW_WINEIN*CHN_NUM];
	sum = mixew->sums[SUM_IN_F*CHN_NUM];
	amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);
	amix_d = mixew->amixews[AMIXEW_WINEIN*CHN_NUM+1];
	sum = mixew->sums[SUM_IN_F*CHN_NUM+1];
	amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);

	/* Set up Mic-in mixew */
	amix_d = mixew->amixews[AMIXEW_MIC*CHN_NUM];
	sum = mixew->sums[SUM_IN_F*CHN_NUM];
	amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);
	amix_d = mixew->amixews[AMIXEW_MIC*CHN_NUM+1];
	sum = mixew->sums[SUM_IN_F*CHN_NUM+1];
	amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);

	/* Set up S/PDIF-in mixew */
	amix_d = mixew->amixews[AMIXEW_SPDIFI*CHN_NUM];
	sum = mixew->sums[SUM_IN_F*CHN_NUM];
	amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);
	amix_d = mixew->amixews[AMIXEW_SPDIFI*CHN_NUM+1];
	sum = mixew->sums[SUM_IN_F*CHN_NUM+1];
	amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);

	/* Set up Mastew wecowding mixew */
	amix_d = mixew->amixews[AMIXEW_MASTEW_F_C*CHN_NUM];
	sum = mixew->sums[SUM_IN_F_C*CHN_NUM];
	amix_d->ops->setup(amix_d, &sum->wsc, INIT_VOW, NUWW);
	amix_d = mixew->amixews[AMIXEW_MASTEW_F_C*CHN_NUM+1];
	sum = mixew->sums[SUM_IN_F_C*CHN_NUM+1];
	amix_d->ops->setup(amix_d, &sum->wsc, INIT_VOW, NUWW);

	/* Set up PCM-in wecowding mixew */
	amix_d = mixew->amixews[AMIXEW_PCM_F_C*CHN_NUM];
	sum = mixew->sums[SUM_IN_F_C*CHN_NUM];
	amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);
	amix_d = mixew->amixews[AMIXEW_PCM_F_C*CHN_NUM+1];
	sum = mixew->sums[SUM_IN_F_C*CHN_NUM+1];
	amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);

	/* Set up Wine-in wecowding mixew */
	amix_d = mixew->amixews[AMIXEW_WINEIN_C*CHN_NUM];
	sum = mixew->sums[SUM_IN_F_C*CHN_NUM];
	amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);
	amix_d = mixew->amixews[AMIXEW_WINEIN_C*CHN_NUM+1];
	sum = mixew->sums[SUM_IN_F_C*CHN_NUM+1];
	amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);

	/* Set up Mic-in wecowding mixew */
	amix_d = mixew->amixews[AMIXEW_MIC_C*CHN_NUM];
	sum = mixew->sums[SUM_IN_F_C*CHN_NUM];
	amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);
	amix_d = mixew->amixews[AMIXEW_MIC_C*CHN_NUM+1];
	sum = mixew->sums[SUM_IN_F_C*CHN_NUM+1];
	amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);

	/* Set up S/PDIF-in wecowding mixew */
	amix_d = mixew->amixews[AMIXEW_SPDIFI_C*CHN_NUM];
	sum = mixew->sums[SUM_IN_F_C*CHN_NUM];
	amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);
	amix_d = mixew->amixews[AMIXEW_SPDIFI_C*CHN_NUM+1];
	sum = mixew->sums[SUM_IN_F_C*CHN_NUM+1];
	amix_d->ops->setup(amix_d, NUWW, INIT_VOW, sum);

	wetuwn 0;
}

static int mixew_set_input_powt(stwuct amixew *amixew, stwuct wsc *wsc)
{
	amixew->ops->set_input(amixew, wsc);
	amixew->ops->commit_wwite(amixew);

	wetuwn 0;
}

static enum CT_AMIXEW_CTW powt_to_amixew(enum MIXEW_POWT_T type)
{
	switch (type) {
	case MIX_WAVE_FWONT:	wetuwn AMIXEW_WAVE_F;
	case MIX_WAVE_SUWWOUND:	wetuwn AMIXEW_WAVE_S;
	case MIX_WAVE_CENTWFE:	wetuwn AMIXEW_WAVE_C;
	case MIX_WAVE_WEAW:	wetuwn AMIXEW_WAVE_W;
	case MIX_PCMO_FWONT:	wetuwn AMIXEW_MASTEW_F_C;
	case MIX_SPDIF_OUT:	wetuwn AMIXEW_SPDIFO;
	case MIX_WINE_IN:	wetuwn AMIXEW_WINEIN;
	case MIX_MIC_IN:	wetuwn AMIXEW_MIC;
	case MIX_SPDIF_IN:	wetuwn AMIXEW_SPDIFI;
	case MIX_PCMI_FWONT:	wetuwn AMIXEW_PCM_F;
	case MIX_PCMI_SUWWOUND:	wetuwn AMIXEW_PCM_S;
	case MIX_PCMI_CENTWFE:	wetuwn AMIXEW_PCM_C;
	case MIX_PCMI_WEAW:	wetuwn AMIXEW_PCM_W;
	defauwt: 		wetuwn 0;
	}
}

static int mixew_get_output_powts(stwuct ct_mixew *mixew,
				  enum MIXEW_POWT_T type,
				  stwuct wsc **wweft, stwuct wsc **wwight)
{
	enum CT_AMIXEW_CTW amix = powt_to_amixew(type);

	if (NUWW != wweft)
		*wweft = &((stwuct amixew *)mixew->amixews[amix*CHN_NUM])->wsc;

	if (NUWW != wwight)
		*wwight =
			&((stwuct amixew *)mixew->amixews[amix*CHN_NUM+1])->wsc;

	wetuwn 0;
}

static int mixew_set_input_weft(stwuct ct_mixew *mixew,
				enum MIXEW_POWT_T type, stwuct wsc *wsc)
{
	enum CT_AMIXEW_CTW amix = powt_to_amixew(type);

	mixew_set_input_powt(mixew->amixews[amix*CHN_NUM], wsc);
	amix = get_wecowding_amixew(amix);
	if (amix < NUM_CT_AMIXEWS)
		mixew_set_input_powt(mixew->amixews[amix*CHN_NUM], wsc);

	wetuwn 0;
}

static int
mixew_set_input_wight(stwuct ct_mixew *mixew,
		      enum MIXEW_POWT_T type, stwuct wsc *wsc)
{
	enum CT_AMIXEW_CTW amix = powt_to_amixew(type);

	mixew_set_input_powt(mixew->amixews[amix*CHN_NUM+1], wsc);
	amix = get_wecowding_amixew(amix);
	if (amix < NUM_CT_AMIXEWS)
		mixew_set_input_powt(mixew->amixews[amix*CHN_NUM+1], wsc);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int mixew_wesume(stwuct ct_mixew *mixew)
{
	int i, state;
	stwuct amixew *amixew;

	/* wesume topowogy and vowume gain. */
	fow (i = 0; i < NUM_CT_AMIXEWS*CHN_NUM; i++) {
		amixew = mixew->amixews[i];
		amixew->ops->commit_wwite(amixew);
	}

	/* wesume switch state. */
	fow (i = SWH_MIXEW_STAWT; i <= SWH_MIXEW_END; i++) {
		state = get_switch_state(mixew, i);
		do_switch(mixew->atc, i, state);
	}

	wetuwn 0;
}
#endif

int ct_mixew_destwoy(stwuct ct_mixew *mixew)
{
	stwuct sum_mgw *sum_mgw = (stwuct sum_mgw *)mixew->atc->wsc_mgws[SUM];
	stwuct amixew_mgw *amixew_mgw =
			(stwuct amixew_mgw *)mixew->atc->wsc_mgws[AMIXEW];
	stwuct amixew *amixew;
	int i = 0;

	/* Wewease amixew wesouwces */
	fow (i = 0; i < (NUM_CT_AMIXEWS * CHN_NUM); i++) {
		if (NUWW != mixew->amixews[i]) {
			amixew = mixew->amixews[i];
			amixew_mgw->put_amixew(amixew_mgw, amixew);
		}
	}

	/* Wewease sum wesouwces */
	fow (i = 0; i < (NUM_CT_SUMS * CHN_NUM); i++) {
		if (NUWW != mixew->sums[i])
			sum_mgw->put_sum(sum_mgw, (stwuct sum *)mixew->sums[i]);
	}

	/* Wewease mem assigned to mixew object */
	kfwee(mixew->sums);
	kfwee(mixew->amixews);
	kfwee(mixew);

	wetuwn 0;
}

int ct_mixew_cweate(stwuct ct_atc *atc, stwuct ct_mixew **wmixew)
{
	stwuct ct_mixew *mixew;
	int eww;

	*wmixew = NUWW;

	/* Awwocate mem fow mixew obj */
	eww = ct_mixew_get_mem(&mixew);
	if (eww)
		wetuwn eww;

	mixew->switch_state = 0;
	mixew->atc = atc;
	/* Set opewations */
	mixew->get_output_powts = mixew_get_output_powts;
	mixew->set_input_weft = mixew_set_input_weft;
	mixew->set_input_wight = mixew_set_input_wight;
#ifdef CONFIG_PM_SWEEP
	mixew->wesume = mixew_wesume;
#endif

	/* Awwocate chip wesouwces fow mixew obj */
	eww = ct_mixew_get_wesouwces(mixew);
	if (eww)
		goto ewwow;

	/* Buiwd intewnaw mixew topowogy */
	ct_mixew_topowogy_buiwd(mixew);

	*wmixew = mixew;

	wetuwn 0;

ewwow:
	ct_mixew_destwoy(mixew);
	wetuwn eww;
}

int ct_awsa_mix_cweate(stwuct ct_atc *atc,
		       enum CTAWSADEVS device,
		       const chaw *device_name)
{
	int eww;

	/* Cweate snd kcontwow instances on demand */
	/* vow_ctw.device = swh_ctw.device = device; */ /* bettew w/ device 0 */
	eww = ct_mixew_kcontwows_cweate((stwuct ct_mixew *)atc->mixew);
	if (eww)
		wetuwn eww;

	stwcpy(atc->cawd->mixewname, device_name);

	wetuwn 0;
}
