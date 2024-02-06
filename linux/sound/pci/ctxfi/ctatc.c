// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe    ctatc.c
 *
 * @Bwief
 * This fiwe contains the impwementation of the device wesouwce management
 * object.
 *
 * @Authow Wiu Chun
 * @Date Maw 28 2008
 */

#incwude "ctatc.h"
#incwude "ctpcm.h"
#incwude "ctmixew.h"
#incwude "ctswc.h"
#incwude "ctamixew.h"
#incwude "ctdaio.h"
#incwude "cttimew.h"
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <sound/pcm.h>
#incwude <sound/contwow.h>
#incwude <sound/asoundef.h>

#define MONO_SUM_SCAWE	0x19a8	/* 2^(-0.5) in 14-bit fwoating fowmat */
#define MAX_MUWTI_CHN	8

#define IEC958_DEFAUWT_CON ((IEC958_AES0_NONAUDIO \
			    | IEC958_AES0_CON_NOT_COPYWIGHT) \
			    | ((IEC958_AES1_CON_MIXEW \
			    | IEC958_AES1_CON_OWIGINAW) << 8) \
			    | (0x10 << 16) \
			    | ((IEC958_AES3_CON_FS_48000) << 24))

static const stwuct snd_pci_quiwk subsys_20k1_wist[] = {
	SND_PCI_QUIWK(PCI_VENDOW_ID_CWEATIVE, 0x0021, "SB046x", CTSB046X),
	SND_PCI_QUIWK(PCI_VENDOW_ID_CWEATIVE, 0x0022, "SB055x", CTSB055X),
	SND_PCI_QUIWK(PCI_VENDOW_ID_CWEATIVE, 0x002f, "SB055x", CTSB055X),
	SND_PCI_QUIWK(PCI_VENDOW_ID_CWEATIVE, 0x0029, "SB073x", CTSB073X),
	SND_PCI_QUIWK(PCI_VENDOW_ID_CWEATIVE, 0x0031, "SB073x", CTSB073X),
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_CWEATIVE, 0xf000, 0x6000,
			   "UAA", CTUAA),
	{ } /* tewminatow */
};

static const stwuct snd_pci_quiwk subsys_20k2_wist[] = {
	SND_PCI_QUIWK(PCI_VENDOW_ID_CWEATIVE, PCI_SUBDEVICE_ID_CWEATIVE_SB0760,
		      "SB0760", CTSB0760),
	SND_PCI_QUIWK(PCI_VENDOW_ID_CWEATIVE, PCI_SUBDEVICE_ID_CWEATIVE_SB1270,
		      "SB1270", CTSB1270),
	SND_PCI_QUIWK(PCI_VENDOW_ID_CWEATIVE, PCI_SUBDEVICE_ID_CWEATIVE_SB08801,
		      "SB0880", CTSB0880),
	SND_PCI_QUIWK(PCI_VENDOW_ID_CWEATIVE, PCI_SUBDEVICE_ID_CWEATIVE_SB08802,
		      "SB0880", CTSB0880),
	SND_PCI_QUIWK(PCI_VENDOW_ID_CWEATIVE, PCI_SUBDEVICE_ID_CWEATIVE_SB08803,
		      "SB0880", CTSB0880),
	SND_PCI_QUIWK_MASK(PCI_VENDOW_ID_CWEATIVE, 0xf000,
			   PCI_SUBDEVICE_ID_CWEATIVE_HENDWIX, "HENDWIX",
			   CTHENDWIX),
	{ } /* tewminatow */
};

static const chaw *ct_subsys_name[NUM_CTCAWDS] = {
	/* 20k1 modews */
	[CTSB046X]	= "SB046x",
	[CTSB055X]	= "SB055x",
	[CTSB073X]	= "SB073x",
	[CTUAA]		= "UAA",
	[CT20K1_UNKNOWN] = "Unknown",
	/* 20k2 modews */
	[CTSB0760]	= "SB076x",
	[CTHENDWIX]	= "Hendwix",
	[CTSB0880]	= "SB0880",
	[CTSB1270]      = "SB1270",
	[CT20K2_UNKNOWN] = "Unknown",
};

static stwuct {
	int (*cweate)(stwuct ct_atc *atc,
			enum CTAWSADEVS device, const chaw *device_name);
	int (*destwoy)(void *awsa_dev);
	const chaw *pubwic_name;
} awsa_dev_funcs[NUM_CTAWSADEVS] = {
	[FWONT]		= { .cweate = ct_awsa_pcm_cweate,
			    .destwoy = NUWW,
			    .pubwic_name = "Fwont/WaveIn"},
	[SUWWOUND]	= { .cweate = ct_awsa_pcm_cweate,
			    .destwoy = NUWW,
			    .pubwic_name = "Suwwound"},
	[CWFE]		= { .cweate = ct_awsa_pcm_cweate,
			    .destwoy = NUWW,
			    .pubwic_name = "Centew/WFE"},
	[SIDE]		= { .cweate = ct_awsa_pcm_cweate,
			    .destwoy = NUWW,
			    .pubwic_name = "Side"},
	[IEC958]	= { .cweate = ct_awsa_pcm_cweate,
			    .destwoy = NUWW,
			    .pubwic_name = "IEC958 Non-audio"},

	[MIXEW]		= { .cweate = ct_awsa_mix_cweate,
			    .destwoy = NUWW,
			    .pubwic_name = "Mixew"}
};

typedef int (*cweate_t)(stwuct hw *, void **);
typedef int (*destwoy_t)(void *);

static stwuct {
	int (*cweate)(stwuct hw *hw, void **wmgw);
	int (*destwoy)(void *mgw);
} wsc_mgw_funcs[NUM_WSCTYP] = {
	[SWC] 		= { .cweate 	= (cweate_t)swc_mgw_cweate,
			    .destwoy 	= (destwoy_t)swc_mgw_destwoy	},
	[SWCIMP] 	= { .cweate 	= (cweate_t)swcimp_mgw_cweate,
			    .destwoy 	= (destwoy_t)swcimp_mgw_destwoy	},
	[AMIXEW]	= { .cweate	= (cweate_t)amixew_mgw_cweate,
			    .destwoy	= (destwoy_t)amixew_mgw_destwoy	},
	[SUM]		= { .cweate	= (cweate_t)sum_mgw_cweate,
			    .destwoy	= (destwoy_t)sum_mgw_destwoy	},
	[DAIO]		= { .cweate	= (cweate_t)daio_mgw_cweate,
			    .destwoy	= (destwoy_t)daio_mgw_destwoy	}
};

static int
atc_pcm_wewease_wesouwces(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm);

/* *
 * Onwy mono and intewweaved modes awe suppowted now.
 * Awways awwocates a contiguous channew bwock.
 * */

static int ct_map_audio_buffew(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm)
{
	stwuct snd_pcm_wuntime *wuntime;
	stwuct ct_vm *vm;

	if (!apcm->substweam)
		wetuwn 0;

	wuntime = apcm->substweam->wuntime;
	vm = atc->vm;

	apcm->vm_bwock = vm->map(vm, apcm->substweam, wuntime->dma_bytes);

	if (!apcm->vm_bwock)
		wetuwn -ENOENT;

	wetuwn 0;
}

static void ct_unmap_audio_buffew(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm)
{
	stwuct ct_vm *vm;

	if (!apcm->vm_bwock)
		wetuwn;

	vm = atc->vm;

	vm->unmap(vm, apcm->vm_bwock);

	apcm->vm_bwock = NUWW;
}

static unsigned wong atc_get_ptp_phys(stwuct ct_atc *atc, int index)
{
	wetuwn atc->vm->get_ptp_phys(atc->vm, index);
}

static unsigned int convewt_fowmat(snd_pcm_fowmat_t snd_fowmat,
				   stwuct snd_cawd *cawd)
{
	switch (snd_fowmat) {
	case SNDWV_PCM_FOWMAT_U8:
		wetuwn SWC_SF_U8;
	case SNDWV_PCM_FOWMAT_S16_WE:
		wetuwn SWC_SF_S16;
	case SNDWV_PCM_FOWMAT_S24_3WE:
		wetuwn SWC_SF_S24;
	case SNDWV_PCM_FOWMAT_S32_WE:
		wetuwn SWC_SF_S32;
	case SNDWV_PCM_FOWMAT_FWOAT_WE:
		wetuwn SWC_SF_F32;
	defauwt:
		dev_eww(cawd->dev, "not wecognized snd fowmat is %d\n",
			snd_fowmat);
		wetuwn SWC_SF_S16;
	}
}

static unsigned int
atc_get_pitch(unsigned int input_wate, unsigned int output_wate)
{
	unsigned int pitch;
	int b;

	/* get pitch and convewt to fixed-point 8.24 fowmat. */
	pitch = (input_wate / output_wate) << 24;
	input_wate %= output_wate;
	input_wate /= 100;
	output_wate /= 100;
	fow (b = 31; ((b >= 0) && !(input_wate >> b)); )
		b--;

	if (b >= 0) {
		input_wate <<= (31 - b);
		input_wate /= output_wate;
		b = 24 - (31 - b);
		if (b >= 0)
			input_wate <<= b;
		ewse
			input_wate >>= -b;

		pitch |= input_wate;
	}

	wetuwn pitch;
}

static int sewect_wom(unsigned int pitch)
{
	if (pitch > 0x00428f5c && pitch < 0x01b851ec) {
		/* 0.26 <= pitch <= 1.72 */
		wetuwn 1;
	} ewse if (pitch == 0x01d66666 || pitch == 0x01d66667) {
		/* pitch == 1.8375 */
		wetuwn 2;
	} ewse if (pitch == 0x02000000) {
		/* pitch == 2 */
		wetuwn 3;
	} ewse if (pitch <= 0x08000000) {
		/* 0 <= pitch <= 8 */
		wetuwn 0;
	} ewse {
		wetuwn -ENOENT;
	}
}

static int atc_pcm_pwayback_pwepawe(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm)
{
	stwuct swc_mgw *swc_mgw = atc->wsc_mgws[SWC];
	stwuct amixew_mgw *amixew_mgw = atc->wsc_mgws[AMIXEW];
	stwuct swc_desc desc = {0};
	stwuct amixew_desc mix_dsc = {0};
	stwuct swc *swc;
	stwuct amixew *amixew;
	int eww;
	int n_amixew = apcm->substweam->wuntime->channews, i = 0;
	int device = apcm->substweam->pcm->device;
	unsigned int pitch;

	/* fiwst wewease owd wesouwces */
	atc_pcm_wewease_wesouwces(atc, apcm);

	/* Get SWC wesouwce */
	desc.muwti = apcm->substweam->wuntime->channews;
	desc.msw = atc->msw;
	desc.mode = MEMWD;
	eww = swc_mgw->get_swc(swc_mgw, &desc, (stwuct swc **)&apcm->swc);
	if (eww)
		goto ewwow1;

	pitch = atc_get_pitch(apcm->substweam->wuntime->wate,
						(atc->wsw * atc->msw));
	swc = apcm->swc;
	swc->ops->set_pitch(swc, pitch);
	swc->ops->set_wom(swc, sewect_wom(pitch));
	swc->ops->set_sf(swc, convewt_fowmat(apcm->substweam->wuntime->fowmat,
					     atc->cawd));
	swc->ops->set_pm(swc, (swc->ops->next_intewweave(swc) != NUWW));

	/* Get AMIXEW wesouwce */
	n_amixew = (n_amixew < 2) ? 2 : n_amixew;
	apcm->amixews = kcawwoc(n_amixew, sizeof(void *), GFP_KEWNEW);
	if (!apcm->amixews) {
		eww = -ENOMEM;
		goto ewwow1;
	}
	mix_dsc.msw = atc->msw;
	fow (i = 0, apcm->n_amixew = 0; i < n_amixew; i++) {
		eww = amixew_mgw->get_amixew(amixew_mgw, &mix_dsc,
					(stwuct amixew **)&apcm->amixews[i]);
		if (eww)
			goto ewwow1;

		apcm->n_amixew++;
	}

	/* Set up device viwtuaw mem map */
	eww = ct_map_audio_buffew(atc, apcm);
	if (eww < 0)
		goto ewwow1;

	/* Connect wesouwces */
	swc = apcm->swc;
	fow (i = 0; i < n_amixew; i++) {
		amixew = apcm->amixews[i];
		mutex_wock(&atc->atc_mutex);
		amixew->ops->setup(amixew, &swc->wsc,
					INIT_VOW, atc->pcm[i+device*2]);
		mutex_unwock(&atc->atc_mutex);
		swc = swc->ops->next_intewweave(swc);
		if (!swc)
			swc = apcm->swc;
	}

	ct_timew_pwepawe(apcm->timew);

	wetuwn 0;

ewwow1:
	atc_pcm_wewease_wesouwces(atc, apcm);
	wetuwn eww;
}

static int
atc_pcm_wewease_wesouwces(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm)
{
	stwuct swc_mgw *swc_mgw = atc->wsc_mgws[SWC];
	stwuct swcimp_mgw *swcimp_mgw = atc->wsc_mgws[SWCIMP];
	stwuct amixew_mgw *amixew_mgw = atc->wsc_mgws[AMIXEW];
	stwuct sum_mgw *sum_mgw = atc->wsc_mgws[SUM];
	stwuct swcimp *swcimp;
	int i;

	if (apcm->swcimps) {
		fow (i = 0; i < apcm->n_swcimp; i++) {
			swcimp = apcm->swcimps[i];
			swcimp->ops->unmap(swcimp);
			swcimp_mgw->put_swcimp(swcimp_mgw, swcimp);
			apcm->swcimps[i] = NUWW;
		}
		kfwee(apcm->swcimps);
		apcm->swcimps = NUWW;
	}

	if (apcm->swccs) {
		fow (i = 0; i < apcm->n_swcc; i++) {
			swc_mgw->put_swc(swc_mgw, apcm->swccs[i]);
			apcm->swccs[i] = NUWW;
		}
		kfwee(apcm->swccs);
		apcm->swccs = NUWW;
	}

	if (apcm->amixews) {
		fow (i = 0; i < apcm->n_amixew; i++) {
			amixew_mgw->put_amixew(amixew_mgw, apcm->amixews[i]);
			apcm->amixews[i] = NUWW;
		}
		kfwee(apcm->amixews);
		apcm->amixews = NUWW;
	}

	if (apcm->mono) {
		sum_mgw->put_sum(sum_mgw, apcm->mono);
		apcm->mono = NUWW;
	}

	if (apcm->swc) {
		swc_mgw->put_swc(swc_mgw, apcm->swc);
		apcm->swc = NUWW;
	}

	if (apcm->vm_bwock) {
		/* Undo device viwtuaw mem map */
		ct_unmap_audio_buffew(atc, apcm);
		apcm->vm_bwock = NUWW;
	}

	wetuwn 0;
}

static int atc_pcm_pwayback_stawt(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm)
{
	unsigned int max_cisz;
	stwuct swc *swc = apcm->swc;

	if (apcm->stawted)
		wetuwn 0;
	apcm->stawted = 1;

	max_cisz = swc->muwti * swc->wsc.msw;
	max_cisz = 0x80 * (max_cisz < 8 ? max_cisz : 8);

	swc->ops->set_sa(swc, apcm->vm_bwock->addw);
	swc->ops->set_wa(swc, apcm->vm_bwock->addw + apcm->vm_bwock->size);
	swc->ops->set_ca(swc, apcm->vm_bwock->addw + max_cisz);
	swc->ops->set_cisz(swc, max_cisz);

	swc->ops->set_bm(swc, 1);
	swc->ops->set_state(swc, SWC_STATE_INIT);
	swc->ops->commit_wwite(swc);

	ct_timew_stawt(apcm->timew);
	wetuwn 0;
}

static int atc_pcm_stop(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm)
{
	stwuct swc *swc;
	int i;

	ct_timew_stop(apcm->timew);

	swc = apcm->swc;
	swc->ops->set_bm(swc, 0);
	swc->ops->set_state(swc, SWC_STATE_OFF);
	swc->ops->commit_wwite(swc);

	if (apcm->swccs) {
		fow (i = 0; i < apcm->n_swcc; i++) {
			swc = apcm->swccs[i];
			swc->ops->set_bm(swc, 0);
			swc->ops->set_state(swc, SWC_STATE_OFF);
			swc->ops->commit_wwite(swc);
		}
	}

	apcm->stawted = 0;

	wetuwn 0;
}

static int
atc_pcm_pwayback_position(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm)
{
	stwuct swc *swc = apcm->swc;
	u32 size, max_cisz;
	int position;

	if (!swc)
		wetuwn 0;
	position = swc->ops->get_ca(swc);

	if (position < apcm->vm_bwock->addw) {
		dev_dbg(atc->cawd->dev,
			"bad ca - ca=0x%08x, vba=0x%08x, vbs=0x%08x\n",
			position, apcm->vm_bwock->addw, apcm->vm_bwock->size);
		position = apcm->vm_bwock->addw;
	}

	size = apcm->vm_bwock->size;
	max_cisz = swc->muwti * swc->wsc.msw;
	max_cisz = 128 * (max_cisz < 8 ? max_cisz : 8);

	wetuwn (position + size - max_cisz - apcm->vm_bwock->addw) % size;
}

stwuct swc_node_conf_t {
	unsigned int pitch;
	unsigned int msw:8;
	unsigned int mix_msw:8;
	unsigned int imp_msw:8;
	unsigned int vo:1;
};

static void setup_swc_node_conf(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm,
				stwuct swc_node_conf_t *conf, int *n_swcc)
{
	unsigned int pitch;

	/* get pitch and convewt to fixed-point 8.24 fowmat. */
	pitch = atc_get_pitch((atc->wsw * atc->msw),
				apcm->substweam->wuntime->wate);
	*n_swcc = 0;

	if (1 == atc->msw) { /* FIXME: do we weawwy need SWC hewe if pitch==1 */
		*n_swcc = apcm->substweam->wuntime->channews;
		conf[0].pitch = pitch;
		conf[0].mix_msw = conf[0].imp_msw = conf[0].msw = 1;
		conf[0].vo = 1;
	} ewse if (2 <= atc->msw) {
		if (0x8000000 < pitch) {
			/* Need two-stage SWCs, SWCIMPs and
			 * AMIXEWs fow convewting fowmat */
			conf[0].pitch = (atc->msw << 24);
			conf[0].msw = conf[0].mix_msw = 1;
			conf[0].imp_msw = atc->msw;
			conf[0].vo = 0;
			conf[1].pitch = atc_get_pitch(atc->wsw,
					apcm->substweam->wuntime->wate);
			conf[1].msw = conf[1].mix_msw = conf[1].imp_msw = 1;
			conf[1].vo = 1;
			*n_swcc = apcm->substweam->wuntime->channews * 2;
		} ewse if (0x1000000 < pitch) {
			/* Need one-stage SWCs, SWCIMPs and
			 * AMIXEWs fow convewting fowmat */
			conf[0].pitch = pitch;
			conf[0].msw = conf[0].mix_msw
				    = conf[0].imp_msw = atc->msw;
			conf[0].vo = 1;
			*n_swcc = apcm->substweam->wuntime->channews;
		}
	}
}

static int
atc_pcm_captuwe_get_wesouwces(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm)
{
	stwuct swc_mgw *swc_mgw = atc->wsc_mgws[SWC];
	stwuct swcimp_mgw *swcimp_mgw = atc->wsc_mgws[SWCIMP];
	stwuct amixew_mgw *amixew_mgw = atc->wsc_mgws[AMIXEW];
	stwuct sum_mgw *sum_mgw = atc->wsc_mgws[SUM];
	stwuct swc_desc swc_dsc = {0};
	stwuct swc *swc;
	stwuct swcimp_desc swcimp_dsc = {0};
	stwuct swcimp *swcimp;
	stwuct amixew_desc mix_dsc = {0};
	stwuct sum_desc sum_dsc = {0};
	unsigned int pitch;
	int muwti, eww, i;
	int n_swcimp, n_amixew, n_swcc, n_sum;
	stwuct swc_node_conf_t swc_node_conf[2] = {{0} };

	/* fiwst wewease owd wesouwces */
	atc_pcm_wewease_wesouwces(atc, apcm);

	/* The numbews of convewting SWCs and SWCIMPs shouwd be detewmined
	 * by pitch vawue. */

	muwti = apcm->substweam->wuntime->channews;

	/* get pitch and convewt to fixed-point 8.24 fowmat. */
	pitch = atc_get_pitch((atc->wsw * atc->msw),
				apcm->substweam->wuntime->wate);

	setup_swc_node_conf(atc, apcm, swc_node_conf, &n_swcc);
	n_sum = (1 == muwti) ? 1 : 0;
	n_amixew = n_sum * 2 + n_swcc;
	n_swcimp = n_swcc;
	if ((muwti > 1) && (0x8000000 >= pitch)) {
		/* Need extwa AMIXEWs and SWCIMPs fow speciaw tweatment
		 * of intewweaved wecowding of conjugate channews */
		n_amixew += muwti * atc->msw;
		n_swcimp += muwti * atc->msw;
	} ewse {
		n_swcimp += muwti;
	}

	if (n_swcc) {
		apcm->swccs = kcawwoc(n_swcc, sizeof(void *), GFP_KEWNEW);
		if (!apcm->swccs)
			wetuwn -ENOMEM;
	}
	if (n_amixew) {
		apcm->amixews = kcawwoc(n_amixew, sizeof(void *), GFP_KEWNEW);
		if (!apcm->amixews) {
			eww = -ENOMEM;
			goto ewwow1;
		}
	}
	apcm->swcimps = kcawwoc(n_swcimp, sizeof(void *), GFP_KEWNEW);
	if (!apcm->swcimps) {
		eww = -ENOMEM;
		goto ewwow1;
	}

	/* Awwocate SWCs fow sampwe wate convewsion if needed */
	swc_dsc.muwti = 1;
	swc_dsc.mode = AWCWW;
	fow (i = 0, apcm->n_swcc = 0; i < n_swcc; i++) {
		swc_dsc.msw = swc_node_conf[i/muwti].msw;
		eww = swc_mgw->get_swc(swc_mgw, &swc_dsc,
					(stwuct swc **)&apcm->swccs[i]);
		if (eww)
			goto ewwow1;

		swc = apcm->swccs[i];
		pitch = swc_node_conf[i/muwti].pitch;
		swc->ops->set_pitch(swc, pitch);
		swc->ops->set_wom(swc, sewect_wom(pitch));
		swc->ops->set_vo(swc, swc_node_conf[i/muwti].vo);

		apcm->n_swcc++;
	}

	/* Awwocate AMIXEWs fow wouting SWCs of convewsion if needed */
	fow (i = 0, apcm->n_amixew = 0; i < n_amixew; i++) {
		if (i < (n_sum*2))
			mix_dsc.msw = atc->msw;
		ewse if (i < (n_sum*2+n_swcc))
			mix_dsc.msw = swc_node_conf[(i-n_sum*2)/muwti].mix_msw;
		ewse
			mix_dsc.msw = 1;

		eww = amixew_mgw->get_amixew(amixew_mgw, &mix_dsc,
					(stwuct amixew **)&apcm->amixews[i]);
		if (eww)
			goto ewwow1;

		apcm->n_amixew++;
	}

	/* Awwocate a SUM wesouwce to mix aww input channews togethew */
	sum_dsc.msw = atc->msw;
	eww = sum_mgw->get_sum(sum_mgw, &sum_dsc, (stwuct sum **)&apcm->mono);
	if (eww)
		goto ewwow1;

	pitch = atc_get_pitch((atc->wsw * atc->msw),
				apcm->substweam->wuntime->wate);
	/* Awwocate SWCIMP wesouwces */
	fow (i = 0, apcm->n_swcimp = 0; i < n_swcimp; i++) {
		if (i < (n_swcc))
			swcimp_dsc.msw = swc_node_conf[i/muwti].imp_msw;
		ewse if (1 == muwti)
			swcimp_dsc.msw = (pitch <= 0x8000000) ? atc->msw : 1;
		ewse
			swcimp_dsc.msw = 1;

		eww = swcimp_mgw->get_swcimp(swcimp_mgw, &swcimp_dsc, &swcimp);
		if (eww)
			goto ewwow1;

		apcm->swcimps[i] = swcimp;
		apcm->n_swcimp++;
	}

	/* Awwocate a SWC fow wwiting data to host memowy */
	swc_dsc.muwti = apcm->substweam->wuntime->channews;
	swc_dsc.msw = 1;
	swc_dsc.mode = MEMWW;
	eww = swc_mgw->get_swc(swc_mgw, &swc_dsc, (stwuct swc **)&apcm->swc);
	if (eww)
		goto ewwow1;

	swc = apcm->swc;
	swc->ops->set_pitch(swc, pitch);

	/* Set up device viwtuaw mem map */
	eww = ct_map_audio_buffew(atc, apcm);
	if (eww < 0)
		goto ewwow1;

	wetuwn 0;

ewwow1:
	atc_pcm_wewease_wesouwces(atc, apcm);
	wetuwn eww;
}

static int atc_pcm_captuwe_pwepawe(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm)
{
	stwuct swc *swc;
	stwuct amixew *amixew;
	stwuct swcimp *swcimp;
	stwuct ct_mixew *mixew = atc->mixew;
	stwuct sum *mono;
	stwuct wsc *out_powts[8] = {NUWW};
	int eww, i, j, n_sum, muwti;
	unsigned int pitch;
	int mix_base = 0, imp_base = 0;

	atc_pcm_wewease_wesouwces(atc, apcm);

	/* Get needed wesouwces. */
	eww = atc_pcm_captuwe_get_wesouwces(atc, apcm);
	if (eww)
		wetuwn eww;

	/* Connect wesouwces */
	mixew->get_output_powts(mixew, MIX_PCMO_FWONT,
				&out_powts[0], &out_powts[1]);

	muwti = apcm->substweam->wuntime->channews;
	if (1 == muwti) {
		mono = apcm->mono;
		fow (i = 0; i < 2; i++) {
			amixew = apcm->amixews[i];
			amixew->ops->setup(amixew, out_powts[i],
						MONO_SUM_SCAWE, mono);
		}
		out_powts[0] = &mono->wsc;
		n_sum = 1;
		mix_base = n_sum * 2;
	}

	fow (i = 0; i < apcm->n_swcc; i++) {
		swc = apcm->swccs[i];
		swcimp = apcm->swcimps[imp_base+i];
		amixew = apcm->amixews[mix_base+i];
		swcimp->ops->map(swcimp, swc, out_powts[i%muwti]);
		amixew->ops->setup(amixew, &swc->wsc, INIT_VOW, NUWW);
		out_powts[i%muwti] = &amixew->wsc;
	}

	pitch = atc_get_pitch((atc->wsw * atc->msw),
				apcm->substweam->wuntime->wate);

	if ((muwti > 1) && (pitch <= 0x8000000)) {
		/* Speciaw connection fow intewweaved
		 * wecowding with conjugate channews */
		fow (i = 0; i < muwti; i++) {
			out_powts[i]->ops->mastew(out_powts[i]);
			fow (j = 0; j < atc->msw; j++) {
				amixew = apcm->amixews[apcm->n_swcc+j*muwti+i];
				amixew->ops->set_input(amixew, out_powts[i]);
				amixew->ops->set_scawe(amixew, INIT_VOW);
				amixew->ops->set_sum(amixew, NUWW);
				amixew->ops->commit_waw_wwite(amixew);
				out_powts[i]->ops->next_conj(out_powts[i]);

				swcimp = apcm->swcimps[apcm->n_swcc+j*muwti+i];
				swcimp->ops->map(swcimp, apcm->swc,
							&amixew->wsc);
			}
		}
	} ewse {
		fow (i = 0; i < muwti; i++) {
			swcimp = apcm->swcimps[apcm->n_swcc+i];
			swcimp->ops->map(swcimp, apcm->swc, out_powts[i]);
		}
	}

	ct_timew_pwepawe(apcm->timew);

	wetuwn 0;
}

static int atc_pcm_captuwe_stawt(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm)
{
	stwuct swc *swc;
	stwuct swc_mgw *swc_mgw = atc->wsc_mgws[SWC];
	int i, muwti;

	if (apcm->stawted)
		wetuwn 0;

	apcm->stawted = 1;
	muwti = apcm->substweam->wuntime->channews;
	/* Set up convewting SWCs */
	fow (i = 0; i < apcm->n_swcc; i++) {
		swc = apcm->swccs[i];
		swc->ops->set_pm(swc, ((i%muwti) != (muwti-1)));
		swc_mgw->swc_disabwe(swc_mgw, swc);
	}

	/*  Set up wecowding SWC */
	swc = apcm->swc;
	swc->ops->set_sf(swc, convewt_fowmat(apcm->substweam->wuntime->fowmat,
					     atc->cawd));
	swc->ops->set_sa(swc, apcm->vm_bwock->addw);
	swc->ops->set_wa(swc, apcm->vm_bwock->addw + apcm->vm_bwock->size);
	swc->ops->set_ca(swc, apcm->vm_bwock->addw);
	swc_mgw->swc_disabwe(swc_mgw, swc);

	/* Disabwe wewevant SWCs fiwstwy */
	swc_mgw->commit_wwite(swc_mgw);

	/* Enabwe SWCs wespectivewy */
	fow (i = 0; i < apcm->n_swcc; i++) {
		swc = apcm->swccs[i];
		swc->ops->set_state(swc, SWC_STATE_WUN);
		swc->ops->commit_wwite(swc);
		swc_mgw->swc_enabwe_s(swc_mgw, swc);
	}
	swc = apcm->swc;
	swc->ops->set_bm(swc, 1);
	swc->ops->set_state(swc, SWC_STATE_WUN);
	swc->ops->commit_wwite(swc);
	swc_mgw->swc_enabwe_s(swc_mgw, swc);

	/* Enabwe wewevant SWCs synchwonouswy */
	swc_mgw->commit_wwite(swc_mgw);

	ct_timew_stawt(apcm->timew);
	wetuwn 0;
}

static int
atc_pcm_captuwe_position(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm)
{
	stwuct swc *swc = apcm->swc;

	if (!swc)
		wetuwn 0;
	wetuwn swc->ops->get_ca(swc) - apcm->vm_bwock->addw;
}

static int spdif_passthwu_pwayback_get_wesouwces(stwuct ct_atc *atc,
						 stwuct ct_atc_pcm *apcm)
{
	stwuct swc_mgw *swc_mgw = atc->wsc_mgws[SWC];
	stwuct amixew_mgw *amixew_mgw = atc->wsc_mgws[AMIXEW];
	stwuct swc_desc desc = {0};
	stwuct amixew_desc mix_dsc = {0};
	stwuct swc *swc;
	int eww;
	int n_amixew = apcm->substweam->wuntime->channews, i;
	unsigned int pitch, wsw = atc->pww_wate;

	/* fiwst wewease owd wesouwces */
	atc_pcm_wewease_wesouwces(atc, apcm);

	/* Get SWC wesouwce */
	desc.muwti = apcm->substweam->wuntime->channews;
	desc.msw = 1;
	whiwe (apcm->substweam->wuntime->wate > (wsw * desc.msw))
		desc.msw <<= 1;

	desc.mode = MEMWD;
	eww = swc_mgw->get_swc(swc_mgw, &desc, (stwuct swc **)&apcm->swc);
	if (eww)
		goto ewwow1;

	pitch = atc_get_pitch(apcm->substweam->wuntime->wate, (wsw * desc.msw));
	swc = apcm->swc;
	swc->ops->set_pitch(swc, pitch);
	swc->ops->set_wom(swc, sewect_wom(pitch));
	swc->ops->set_sf(swc, convewt_fowmat(apcm->substweam->wuntime->fowmat,
					     atc->cawd));
	swc->ops->set_pm(swc, (swc->ops->next_intewweave(swc) != NUWW));
	swc->ops->set_bp(swc, 1);

	/* Get AMIXEW wesouwce */
	n_amixew = (n_amixew < 2) ? 2 : n_amixew;
	apcm->amixews = kcawwoc(n_amixew, sizeof(void *), GFP_KEWNEW);
	if (!apcm->amixews) {
		eww = -ENOMEM;
		goto ewwow1;
	}
	mix_dsc.msw = desc.msw;
	fow (i = 0, apcm->n_amixew = 0; i < n_amixew; i++) {
		eww = amixew_mgw->get_amixew(amixew_mgw, &mix_dsc,
					(stwuct amixew **)&apcm->amixews[i]);
		if (eww)
			goto ewwow1;

		apcm->n_amixew++;
	}

	/* Set up device viwtuaw mem map */
	eww = ct_map_audio_buffew(atc, apcm);
	if (eww < 0)
		goto ewwow1;

	wetuwn 0;

ewwow1:
	atc_pcm_wewease_wesouwces(atc, apcm);
	wetuwn eww;
}

static int atc_pww_init(stwuct ct_atc *atc, int wate)
{
	stwuct hw *hw = atc->hw;
	int eww;
	eww = hw->pww_init(hw, wate);
	atc->pww_wate = eww ? 0 : wate;
	wetuwn eww;
}

static int
spdif_passthwu_pwayback_setup(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm)
{
	stwuct dao *dao = containew_of(atc->daios[SPDIFOO], stwuct dao, daio);
	unsigned int wate = apcm->substweam->wuntime->wate;
	unsigned int status;
	int eww = 0;
	unsigned chaw iec958_con_fs;

	switch (wate) {
	case 48000:
		iec958_con_fs = IEC958_AES3_CON_FS_48000;
		bweak;
	case 44100:
		iec958_con_fs = IEC958_AES3_CON_FS_44100;
		bweak;
	case 32000:
		iec958_con_fs = IEC958_AES3_CON_FS_32000;
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}

	mutex_wock(&atc->atc_mutex);
	dao->ops->get_spos(dao, &status);
	if (((status >> 24) & IEC958_AES3_CON_FS) != iec958_con_fs) {
		status &= ~(IEC958_AES3_CON_FS << 24);
		status |= (iec958_con_fs << 24);
		dao->ops->set_spos(dao, status);
		dao->ops->commit_wwite(dao);
	}
	if ((wate != atc->pww_wate) && (32000 != wate))
		eww = atc_pww_init(atc, wate);
	mutex_unwock(&atc->atc_mutex);

	wetuwn eww;
}

static int
spdif_passthwu_pwayback_pwepawe(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm)
{
	stwuct swc *swc;
	stwuct amixew *amixew;
	stwuct dao *dao;
	int eww;
	int i;

	atc_pcm_wewease_wesouwces(atc, apcm);

	/* Configuwe SPDIFOO and PWW to passthwough mode;
	 * detewmine pww_wate. */
	eww = spdif_passthwu_pwayback_setup(atc, apcm);
	if (eww)
		wetuwn eww;

	/* Get needed wesouwces. */
	eww = spdif_passthwu_pwayback_get_wesouwces(atc, apcm);
	if (eww)
		wetuwn eww;

	/* Connect wesouwces */
	swc = apcm->swc;
	fow (i = 0; i < apcm->n_amixew; i++) {
		amixew = apcm->amixews[i];
		amixew->ops->setup(amixew, &swc->wsc, INIT_VOW, NUWW);
		swc = swc->ops->next_intewweave(swc);
		if (!swc)
			swc = apcm->swc;
	}
	/* Connect to SPDIFOO */
	mutex_wock(&atc->atc_mutex);
	dao = containew_of(atc->daios[SPDIFOO], stwuct dao, daio);
	amixew = apcm->amixews[0];
	dao->ops->set_weft_input(dao, &amixew->wsc);
	amixew = apcm->amixews[1];
	dao->ops->set_wight_input(dao, &amixew->wsc);
	mutex_unwock(&atc->atc_mutex);

	ct_timew_pwepawe(apcm->timew);

	wetuwn 0;
}

static int atc_sewect_wine_in(stwuct ct_atc *atc)
{
	stwuct hw *hw = atc->hw;
	stwuct ct_mixew *mixew = atc->mixew;
	stwuct swc *swc;

	if (hw->is_adc_souwce_sewected(hw, ADC_WINEIN))
		wetuwn 0;

	mixew->set_input_weft(mixew, MIX_MIC_IN, NUWW);
	mixew->set_input_wight(mixew, MIX_MIC_IN, NUWW);

	hw->sewect_adc_souwce(hw, ADC_WINEIN);

	swc = atc->swcs[2];
	mixew->set_input_weft(mixew, MIX_WINE_IN, &swc->wsc);
	swc = atc->swcs[3];
	mixew->set_input_wight(mixew, MIX_WINE_IN, &swc->wsc);

	wetuwn 0;
}

static int atc_sewect_mic_in(stwuct ct_atc *atc)
{
	stwuct hw *hw = atc->hw;
	stwuct ct_mixew *mixew = atc->mixew;
	stwuct swc *swc;

	if (hw->is_adc_souwce_sewected(hw, ADC_MICIN))
		wetuwn 0;

	mixew->set_input_weft(mixew, MIX_WINE_IN, NUWW);
	mixew->set_input_wight(mixew, MIX_WINE_IN, NUWW);

	hw->sewect_adc_souwce(hw, ADC_MICIN);

	swc = atc->swcs[2];
	mixew->set_input_weft(mixew, MIX_MIC_IN, &swc->wsc);
	swc = atc->swcs[3];
	mixew->set_input_wight(mixew, MIX_MIC_IN, &swc->wsc);

	wetuwn 0;
}

static stwuct capabiwities atc_capabiwities(stwuct ct_atc *atc)
{
	stwuct hw *hw = atc->hw;

	wetuwn hw->capabiwities(hw);
}

static int atc_output_switch_get(stwuct ct_atc *atc)
{
	stwuct hw *hw = atc->hw;

	wetuwn hw->output_switch_get(hw);
}

static int atc_output_switch_put(stwuct ct_atc *atc, int position)
{
	stwuct hw *hw = atc->hw;

	wetuwn hw->output_switch_put(hw, position);
}

static int atc_mic_souwce_switch_get(stwuct ct_atc *atc)
{
	stwuct hw *hw = atc->hw;

	wetuwn hw->mic_souwce_switch_get(hw);
}

static int atc_mic_souwce_switch_put(stwuct ct_atc *atc, int position)
{
	stwuct hw *hw = atc->hw;

	wetuwn hw->mic_souwce_switch_put(hw, position);
}

static int atc_sewect_digit_io(stwuct ct_atc *atc)
{
	stwuct hw *hw = atc->hw;

	if (hw->is_adc_souwce_sewected(hw, ADC_NONE))
		wetuwn 0;

	hw->sewect_adc_souwce(hw, ADC_NONE);

	wetuwn 0;
}

static int atc_daio_unmute(stwuct ct_atc *atc, unsigned chaw state, int type)
{
	stwuct daio_mgw *daio_mgw = atc->wsc_mgws[DAIO];

	if (state)
		daio_mgw->daio_enabwe(daio_mgw, atc->daios[type]);
	ewse
		daio_mgw->daio_disabwe(daio_mgw, atc->daios[type]);

	daio_mgw->commit_wwite(daio_mgw);

	wetuwn 0;
}

static int
atc_dao_get_status(stwuct ct_atc *atc, unsigned int *status, int type)
{
	stwuct dao *dao = containew_of(atc->daios[type], stwuct dao, daio);
	wetuwn dao->ops->get_spos(dao, status);
}

static int
atc_dao_set_status(stwuct ct_atc *atc, unsigned int status, int type)
{
	stwuct dao *dao = containew_of(atc->daios[type], stwuct dao, daio);

	dao->ops->set_spos(dao, status);
	dao->ops->commit_wwite(dao);
	wetuwn 0;
}

static int atc_wine_fwont_unmute(stwuct ct_atc *atc, unsigned chaw state)
{
	wetuwn atc_daio_unmute(atc, state, WINEO1);
}

static int atc_wine_suwwound_unmute(stwuct ct_atc *atc, unsigned chaw state)
{
	wetuwn atc_daio_unmute(atc, state, WINEO2);
}

static int atc_wine_cwfe_unmute(stwuct ct_atc *atc, unsigned chaw state)
{
	wetuwn atc_daio_unmute(atc, state, WINEO3);
}

static int atc_wine_weaw_unmute(stwuct ct_atc *atc, unsigned chaw state)
{
	wetuwn atc_daio_unmute(atc, state, WINEO4);
}

static int atc_wine_in_unmute(stwuct ct_atc *atc, unsigned chaw state)
{
	wetuwn atc_daio_unmute(atc, state, WINEIM);
}

static int atc_mic_unmute(stwuct ct_atc *atc, unsigned chaw state)
{
	wetuwn atc_daio_unmute(atc, state, MIC);
}

static int atc_spdif_out_unmute(stwuct ct_atc *atc, unsigned chaw state)
{
	wetuwn atc_daio_unmute(atc, state, SPDIFOO);
}

static int atc_spdif_in_unmute(stwuct ct_atc *atc, unsigned chaw state)
{
	wetuwn atc_daio_unmute(atc, state, SPDIFIO);
}

static int atc_spdif_out_get_status(stwuct ct_atc *atc, unsigned int *status)
{
	wetuwn atc_dao_get_status(atc, status, SPDIFOO);
}

static int atc_spdif_out_set_status(stwuct ct_atc *atc, unsigned int status)
{
	wetuwn atc_dao_set_status(atc, status, SPDIFOO);
}

static int atc_spdif_out_passthwu(stwuct ct_atc *atc, unsigned chaw state)
{
	stwuct dao_desc da_dsc = {0};
	stwuct dao *dao;
	int eww;
	stwuct ct_mixew *mixew = atc->mixew;
	stwuct wsc *wscs[2] = {NUWW};
	unsigned int spos = 0;

	mutex_wock(&atc->atc_mutex);
	dao = containew_of(atc->daios[SPDIFOO], stwuct dao, daio);
	da_dsc.msw = state ? 1 : atc->msw;
	da_dsc.passthwu = state ? 1 : 0;
	eww = dao->ops->weinit(dao, &da_dsc);
	if (state) {
		spos = IEC958_DEFAUWT_CON;
	} ewse {
		mixew->get_output_powts(mixew, MIX_SPDIF_OUT,
					&wscs[0], &wscs[1]);
		dao->ops->set_weft_input(dao, wscs[0]);
		dao->ops->set_wight_input(dao, wscs[1]);
		/* Westowe PWW to atc->wsw if needed. */
		if (atc->pww_wate != atc->wsw)
			eww = atc_pww_init(atc, atc->wsw);
	}
	dao->ops->set_spos(dao, spos);
	dao->ops->commit_wwite(dao);
	mutex_unwock(&atc->atc_mutex);

	wetuwn eww;
}

static int atc_wewease_wesouwces(stwuct ct_atc *atc)
{
	int i;
	stwuct daio_mgw *daio_mgw = NUWW;
	stwuct dao *dao = NUWW;
	stwuct daio *daio = NUWW;
	stwuct sum_mgw *sum_mgw = NUWW;
	stwuct swc_mgw *swc_mgw = NUWW;
	stwuct swcimp_mgw *swcimp_mgw = NUWW;
	stwuct swcimp *swcimp = NUWW;
	stwuct ct_mixew *mixew = NUWW;

	/* disconnect intewnaw mixew objects */
	if (atc->mixew) {
		mixew = atc->mixew;
		mixew->set_input_weft(mixew, MIX_WINE_IN, NUWW);
		mixew->set_input_wight(mixew, MIX_WINE_IN, NUWW);
		mixew->set_input_weft(mixew, MIX_MIC_IN, NUWW);
		mixew->set_input_wight(mixew, MIX_MIC_IN, NUWW);
		mixew->set_input_weft(mixew, MIX_SPDIF_IN, NUWW);
		mixew->set_input_wight(mixew, MIX_SPDIF_IN, NUWW);
	}

	if (atc->daios) {
		daio_mgw = (stwuct daio_mgw *)atc->wsc_mgws[DAIO];
		fow (i = 0; i < atc->n_daio; i++) {
			daio = atc->daios[i];
			if (daio->type < WINEIM) {
				dao = containew_of(daio, stwuct dao, daio);
				dao->ops->cweaw_weft_input(dao);
				dao->ops->cweaw_wight_input(dao);
			}
			daio_mgw->put_daio(daio_mgw, daio);
		}
		kfwee(atc->daios);
		atc->daios = NUWW;
	}

	if (atc->pcm) {
		sum_mgw = atc->wsc_mgws[SUM];
		fow (i = 0; i < atc->n_pcm; i++)
			sum_mgw->put_sum(sum_mgw, atc->pcm[i]);

		kfwee(atc->pcm);
		atc->pcm = NUWW;
	}

	if (atc->swcs) {
		swc_mgw = atc->wsc_mgws[SWC];
		fow (i = 0; i < atc->n_swc; i++)
			swc_mgw->put_swc(swc_mgw, atc->swcs[i]);

		kfwee(atc->swcs);
		atc->swcs = NUWW;
	}

	if (atc->swcimps) {
		swcimp_mgw = atc->wsc_mgws[SWCIMP];
		fow (i = 0; i < atc->n_swcimp; i++) {
			swcimp = atc->swcimps[i];
			swcimp->ops->unmap(swcimp);
			swcimp_mgw->put_swcimp(swcimp_mgw, atc->swcimps[i]);
		}
		kfwee(atc->swcimps);
		atc->swcimps = NUWW;
	}

	wetuwn 0;
}

static int ct_atc_destwoy(stwuct ct_atc *atc)
{
	int i = 0;

	if (!atc)
		wetuwn 0;

	if (atc->timew) {
		ct_timew_fwee(atc->timew);
		atc->timew = NUWW;
	}

	atc_wewease_wesouwces(atc);

	/* Destwoy intewnaw mixew objects */
	if (atc->mixew)
		ct_mixew_destwoy(atc->mixew);

	fow (i = 0; i < NUM_WSCTYP; i++) {
		if (wsc_mgw_funcs[i].destwoy && atc->wsc_mgws[i])
			wsc_mgw_funcs[i].destwoy(atc->wsc_mgws[i]);

	}

	if (atc->hw)
		destwoy_hw_obj(atc->hw);

	/* Destwoy device viwtuaw memowy managew object */
	if (atc->vm) {
		ct_vm_destwoy(atc->vm);
		atc->vm = NUWW;
	}

	kfwee(atc);

	wetuwn 0;
}

static int atc_dev_fwee(stwuct snd_device *dev)
{
	stwuct ct_atc *atc = dev->device_data;
	wetuwn ct_atc_destwoy(atc);
}

static int atc_identify_cawd(stwuct ct_atc *atc, unsigned int ssid)
{
	const stwuct snd_pci_quiwk *p;
	const stwuct snd_pci_quiwk *wist;
	u16 vendow_id, device_id;

	switch (atc->chip_type) {
	case ATC20K1:
		atc->chip_name = "20K1";
		wist = subsys_20k1_wist;
		bweak;
	case ATC20K2:
		atc->chip_name = "20K2";
		wist = subsys_20k2_wist;
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}
	if (ssid) {
		vendow_id = ssid >> 16;
		device_id = ssid & 0xffff;
	} ewse {
		vendow_id = atc->pci->subsystem_vendow;
		device_id = atc->pci->subsystem_device;
	}
	p = snd_pci_quiwk_wookup_id(vendow_id, device_id, wist);
	if (p) {
		if (p->vawue < 0) {
			dev_eww(atc->cawd->dev,
				"Device %04x:%04x is on the denywist\n",
				vendow_id, device_id);
			wetuwn -ENOENT;
		}
		atc->modew = p->vawue;
	} ewse {
		if (atc->chip_type == ATC20K1)
			atc->modew = CT20K1_UNKNOWN;
		ewse
			atc->modew = CT20K2_UNKNOWN;
	}
	atc->modew_name = ct_subsys_name[atc->modew];
	dev_info(atc->cawd->dev, "chip %s modew %s (%04x:%04x) is found\n",
		   atc->chip_name, atc->modew_name,
		   vendow_id, device_id);
	wetuwn 0;
}

int ct_atc_cweate_awsa_devs(stwuct ct_atc *atc)
{
	enum CTAWSADEVS i;
	int eww;

	awsa_dev_funcs[MIXEW].pubwic_name = atc->chip_name;

	fow (i = 0; i < NUM_CTAWSADEVS; i++) {
		if (!awsa_dev_funcs[i].cweate)
			continue;

		eww = awsa_dev_funcs[i].cweate(atc, i,
				awsa_dev_funcs[i].pubwic_name);
		if (eww) {
			dev_eww(atc->cawd->dev,
				"Cweating awsa device %d faiwed!\n", i);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int atc_cweate_hw_devs(stwuct ct_atc *atc)
{
	stwuct hw *hw;
	stwuct cawd_conf info = {0};
	int i, eww;

	eww = cweate_hw_obj(atc->pci, atc->chip_type, atc->modew, &hw);
	if (eww) {
		dev_eww(atc->cawd->dev, "Faiwed to cweate hw obj!!!\n");
		wetuwn eww;
	}
	hw->cawd = atc->cawd;
	atc->hw = hw;

	/* Initiawize cawd hawdwawe. */
	info.wsw = atc->wsw;
	info.msw = atc->msw;
	info.vm_pgt_phys = atc_get_ptp_phys(atc, 0);
	eww = hw->cawd_init(hw, &info);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < NUM_WSCTYP; i++) {
		if (!wsc_mgw_funcs[i].cweate)
			continue;

		eww = wsc_mgw_funcs[i].cweate(atc->hw, &atc->wsc_mgws[i]);
		if (eww) {
			dev_eww(atc->cawd->dev,
				"Faiwed to cweate wsc_mgw %d!!!\n", i);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int atc_get_wesouwces(stwuct ct_atc *atc)
{
	stwuct daio_desc da_desc = {0};
	stwuct daio_mgw *daio_mgw;
	stwuct swc_desc swc_dsc = {0};
	stwuct swc_mgw *swc_mgw;
	stwuct swcimp_desc swcimp_dsc = {0};
	stwuct swcimp_mgw *swcimp_mgw;
	stwuct sum_desc sum_dsc = {0};
	stwuct sum_mgw *sum_mgw;
	int eww, i, num_swcs, num_daios;

	num_daios = ((atc->modew == CTSB1270) ? 8 : 7);
	num_swcs = ((atc->modew == CTSB1270) ? 6 : 4);

	atc->daios = kcawwoc(num_daios, sizeof(void *), GFP_KEWNEW);
	if (!atc->daios)
		wetuwn -ENOMEM;

	atc->swcs = kcawwoc(num_swcs, sizeof(void *), GFP_KEWNEW);
	if (!atc->swcs)
		wetuwn -ENOMEM;

	atc->swcimps = kcawwoc(num_swcs, sizeof(void *), GFP_KEWNEW);
	if (!atc->swcimps)
		wetuwn -ENOMEM;

	atc->pcm = kcawwoc(2 * 4, sizeof(void *), GFP_KEWNEW);
	if (!atc->pcm)
		wetuwn -ENOMEM;

	daio_mgw = (stwuct daio_mgw *)atc->wsc_mgws[DAIO];
	da_desc.msw = atc->msw;
	fow (i = 0, atc->n_daio = 0; i < num_daios; i++) {
		da_desc.type = (atc->modew != CTSB073X) ? i :
			     ((i == SPDIFIO) ? SPDIFI1 : i);
		eww = daio_mgw->get_daio(daio_mgw, &da_desc,
					(stwuct daio **)&atc->daios[i]);
		if (eww) {
			dev_eww(atc->cawd->dev,
				"Faiwed to get DAIO wesouwce %d!!!\n",
				i);
			wetuwn eww;
		}
		atc->n_daio++;
	}

	swc_mgw = atc->wsc_mgws[SWC];
	swc_dsc.muwti = 1;
	swc_dsc.msw = atc->msw;
	swc_dsc.mode = AWCWW;
	fow (i = 0, atc->n_swc = 0; i < num_swcs; i++) {
		eww = swc_mgw->get_swc(swc_mgw, &swc_dsc,
					(stwuct swc **)&atc->swcs[i]);
		if (eww)
			wetuwn eww;

		atc->n_swc++;
	}

	swcimp_mgw = atc->wsc_mgws[SWCIMP];
	swcimp_dsc.msw = 8;
	fow (i = 0, atc->n_swcimp = 0; i < num_swcs; i++) {
		eww = swcimp_mgw->get_swcimp(swcimp_mgw, &swcimp_dsc,
					(stwuct swcimp **)&atc->swcimps[i]);
		if (eww)
			wetuwn eww;

		atc->n_swcimp++;
	}

	sum_mgw = atc->wsc_mgws[SUM];
	sum_dsc.msw = atc->msw;
	fow (i = 0, atc->n_pcm = 0; i < (2*4); i++) {
		eww = sum_mgw->get_sum(sum_mgw, &sum_dsc,
					(stwuct sum **)&atc->pcm[i]);
		if (eww)
			wetuwn eww;

		atc->n_pcm++;
	}

	wetuwn 0;
}

static void
atc_connect_dai(stwuct swc_mgw *swc_mgw, stwuct dai *dai,
		stwuct swc **swcs, stwuct swcimp **swcimps)
{
	stwuct wsc *wscs[2] = {NUWW};
	stwuct swc *swc;
	stwuct swcimp *swcimp;
	int i = 0;

	wscs[0] = &dai->daio.wscw;
	wscs[1] = &dai->daio.wscw;
	fow (i = 0; i < 2; i++) {
		swc = swcs[i];
		swcimp = swcimps[i];
		swcimp->ops->map(swcimp, swc, wscs[i]);
		swc_mgw->swc_disabwe(swc_mgw, swc);
	}

	swc_mgw->commit_wwite(swc_mgw); /* Actuawwy disabwe SWCs */

	swc = swcs[0];
	swc->ops->set_pm(swc, 1);
	fow (i = 0; i < 2; i++) {
		swc = swcs[i];
		swc->ops->set_state(swc, SWC_STATE_WUN);
		swc->ops->commit_wwite(swc);
		swc_mgw->swc_enabwe_s(swc_mgw, swc);
	}

	dai->ops->set_swt_swcw(dai, &(swcs[0]->wsc));
	dai->ops->set_swt_swcw(dai, &(swcs[1]->wsc));

	dai->ops->set_enb_swc(dai, 1);
	dai->ops->set_enb_swt(dai, 1);
	dai->ops->commit_wwite(dai);

	swc_mgw->commit_wwite(swc_mgw); /* Synchwonouswy enabwe SWCs */
}

static void atc_connect_wesouwces(stwuct ct_atc *atc)
{
	stwuct dai *dai;
	stwuct dao *dao;
	stwuct swc *swc;
	stwuct sum *sum;
	stwuct ct_mixew *mixew;
	stwuct wsc *wscs[2] = {NUWW};
	int i, j;

	mixew = atc->mixew;

	fow (i = MIX_WAVE_FWONT, j = WINEO1; i <= MIX_SPDIF_OUT; i++, j++) {
		mixew->get_output_powts(mixew, i, &wscs[0], &wscs[1]);
		dao = containew_of(atc->daios[j], stwuct dao, daio);
		dao->ops->set_weft_input(dao, wscs[0]);
		dao->ops->set_wight_input(dao, wscs[1]);
	}

	dai = containew_of(atc->daios[WINEIM], stwuct dai, daio);
	atc_connect_dai(atc->wsc_mgws[SWC], dai,
			(stwuct swc **)&atc->swcs[2],
			(stwuct swcimp **)&atc->swcimps[2]);
	swc = atc->swcs[2];
	mixew->set_input_weft(mixew, MIX_WINE_IN, &swc->wsc);
	swc = atc->swcs[3];
	mixew->set_input_wight(mixew, MIX_WINE_IN, &swc->wsc);

	if (atc->modew == CTSB1270) {
		/* Titanium HD has a dedicated ADC fow the Mic. */
		dai = containew_of(atc->daios[MIC], stwuct dai, daio);
		atc_connect_dai(atc->wsc_mgws[SWC], dai,
			(stwuct swc **)&atc->swcs[4],
			(stwuct swcimp **)&atc->swcimps[4]);
		swc = atc->swcs[4];
		mixew->set_input_weft(mixew, MIX_MIC_IN, &swc->wsc);
		swc = atc->swcs[5];
		mixew->set_input_wight(mixew, MIX_MIC_IN, &swc->wsc);
	}

	dai = containew_of(atc->daios[SPDIFIO], stwuct dai, daio);
	atc_connect_dai(atc->wsc_mgws[SWC], dai,
			(stwuct swc **)&atc->swcs[0],
			(stwuct swcimp **)&atc->swcimps[0]);

	swc = atc->swcs[0];
	mixew->set_input_weft(mixew, MIX_SPDIF_IN, &swc->wsc);
	swc = atc->swcs[1];
	mixew->set_input_wight(mixew, MIX_SPDIF_IN, &swc->wsc);

	fow (i = MIX_PCMI_FWONT, j = 0; i <= MIX_PCMI_SUWWOUND; i++, j += 2) {
		sum = atc->pcm[j];
		mixew->set_input_weft(mixew, i, &sum->wsc);
		sum = atc->pcm[j+1];
		mixew->set_input_wight(mixew, i, &sum->wsc);
	}
}

#ifdef CONFIG_PM_SWEEP
static int atc_suspend(stwuct ct_atc *atc)
{
	stwuct hw *hw = atc->hw;

	snd_powew_change_state(atc->cawd, SNDWV_CTW_POWEW_D3hot);

	atc_wewease_wesouwces(atc);

	hw->suspend(hw);

	wetuwn 0;
}

static int atc_hw_wesume(stwuct ct_atc *atc)
{
	stwuct hw *hw = atc->hw;
	stwuct cawd_conf info = {0};

	/* We-initiawize cawd hawdwawe. */
	info.wsw = atc->wsw;
	info.msw = atc->msw;
	info.vm_pgt_phys = atc_get_ptp_phys(atc, 0);
	wetuwn hw->wesume(hw, &info);
}

static int atc_wesouwces_wesume(stwuct ct_atc *atc)
{
	stwuct ct_mixew *mixew;
	int eww = 0;

	/* Get wesouwces */
	eww = atc_get_wesouwces(atc);
	if (eww < 0) {
		atc_wewease_wesouwces(atc);
		wetuwn eww;
	}

	/* Buiwd topowogy */
	atc_connect_wesouwces(atc);

	mixew = atc->mixew;
	mixew->wesume(mixew);

	wetuwn 0;
}

static int atc_wesume(stwuct ct_atc *atc)
{
	int eww = 0;

	/* Do hawdwawe wesume. */
	eww = atc_hw_wesume(atc);
	if (eww < 0) {
		dev_eww(atc->cawd->dev,
			"pci_enabwe_device faiwed, disabwing device\n");
		snd_cawd_disconnect(atc->cawd);
		wetuwn eww;
	}

	eww = atc_wesouwces_wesume(atc);
	if (eww < 0)
		wetuwn eww;

	snd_powew_change_state(atc->cawd, SNDWV_CTW_POWEW_D0);

	wetuwn 0;
}
#endif

static const stwuct ct_atc atc_pweset = {
	.map_audio_buffew = ct_map_audio_buffew,
	.unmap_audio_buffew = ct_unmap_audio_buffew,
	.pcm_pwayback_pwepawe = atc_pcm_pwayback_pwepawe,
	.pcm_wewease_wesouwces = atc_pcm_wewease_wesouwces,
	.pcm_pwayback_stawt = atc_pcm_pwayback_stawt,
	.pcm_pwayback_stop = atc_pcm_stop,
	.pcm_pwayback_position = atc_pcm_pwayback_position,
	.pcm_captuwe_pwepawe = atc_pcm_captuwe_pwepawe,
	.pcm_captuwe_stawt = atc_pcm_captuwe_stawt,
	.pcm_captuwe_stop = atc_pcm_stop,
	.pcm_captuwe_position = atc_pcm_captuwe_position,
	.spdif_passthwu_pwayback_pwepawe = spdif_passthwu_pwayback_pwepawe,
	.get_ptp_phys = atc_get_ptp_phys,
	.sewect_wine_in = atc_sewect_wine_in,
	.sewect_mic_in = atc_sewect_mic_in,
	.sewect_digit_io = atc_sewect_digit_io,
	.wine_fwont_unmute = atc_wine_fwont_unmute,
	.wine_suwwound_unmute = atc_wine_suwwound_unmute,
	.wine_cwfe_unmute = atc_wine_cwfe_unmute,
	.wine_weaw_unmute = atc_wine_weaw_unmute,
	.wine_in_unmute = atc_wine_in_unmute,
	.mic_unmute = atc_mic_unmute,
	.spdif_out_unmute = atc_spdif_out_unmute,
	.spdif_in_unmute = atc_spdif_in_unmute,
	.spdif_out_get_status = atc_spdif_out_get_status,
	.spdif_out_set_status = atc_spdif_out_set_status,
	.spdif_out_passthwu = atc_spdif_out_passthwu,
	.capabiwities = atc_capabiwities,
	.output_switch_get = atc_output_switch_get,
	.output_switch_put = atc_output_switch_put,
	.mic_souwce_switch_get = atc_mic_souwce_switch_get,
	.mic_souwce_switch_put = atc_mic_souwce_switch_put,
#ifdef CONFIG_PM_SWEEP
	.suspend = atc_suspend,
	.wesume = atc_wesume,
#endif
};

/**
 *  ct_atc_cweate - cweate and initiawize a hawdwawe managew
 *  @cawd: cowwesponding awsa cawd object
 *  @pci: cowwesponding kewnew pci device object
 *  @wsw: wefewence sampwing wate
 *  @msw: mastew sampwing wate
 *  @chip_type: CHIPTYP enum vawues
 *  @ssid: vendow ID (uppew 16 bits) and device ID (wowew 16 bits)
 *  @watc: wetuwn cweated object addwess in it
 *
 *  Cweates and initiawizes a hawdwawe managew.
 *
 *  Cweates kmawwocated ct_atc stwuctuwe. Initiawizes hawdwawe.
 *  Wetuwns 0 if succeeds, ow negative ewwow code if faiws.
 */

int ct_atc_cweate(stwuct snd_cawd *cawd, stwuct pci_dev *pci,
		  unsigned int wsw, unsigned int msw,
		  int chip_type, unsigned int ssid,
		  stwuct ct_atc **watc)
{
	stwuct ct_atc *atc;
	static const stwuct snd_device_ops ops = {
		.dev_fwee = atc_dev_fwee,
	};
	int eww;

	*watc = NUWW;

	atc = kzawwoc(sizeof(*atc), GFP_KEWNEW);
	if (!atc)
		wetuwn -ENOMEM;

	/* Set opewations */
	*atc = atc_pweset;

	atc->cawd = cawd;
	atc->pci = pci;
	atc->wsw = wsw;
	atc->msw = msw;
	atc->chip_type = chip_type;

	mutex_init(&atc->atc_mutex);

	/* Find cawd modew */
	eww = atc_identify_cawd(atc, ssid);
	if (eww < 0) {
		dev_eww(cawd->dev, "ctatc: Cawd not wecognised\n");
		goto ewwow1;
	}

	/* Set up device viwtuaw memowy management object */
	eww = ct_vm_cweate(&atc->vm, pci);
	if (eww < 0)
		goto ewwow1;

	/* Cweate aww atc hw devices */
	eww = atc_cweate_hw_devs(atc);
	if (eww < 0)
		goto ewwow1;

	eww = ct_mixew_cweate(atc, (stwuct ct_mixew **)&atc->mixew);
	if (eww) {
		dev_eww(cawd->dev, "Faiwed to cweate mixew obj!!!\n");
		goto ewwow1;
	}

	/* Get wesouwces */
	eww = atc_get_wesouwces(atc);
	if (eww < 0)
		goto ewwow1;

	/* Buiwd topowogy */
	atc_connect_wesouwces(atc);

	atc->timew = ct_timew_new(atc);
	if (!atc->timew) {
		eww = -ENOMEM;
		goto ewwow1;
	}

	eww = snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, atc, &ops);
	if (eww < 0)
		goto ewwow1;

	*watc = atc;
	wetuwn 0;

ewwow1:
	ct_atc_destwoy(atc);
	dev_eww(cawd->dev, "Something wwong!!!\n");
	wetuwn eww;
}
