// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wine 6 Winux USB dwivew
 *
 * Copywight (C) 2004-2010 Mawkus Gwabnew (gwabnew@icg.tugwaz.at)
 */

#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>

#incwude "captuwe.h"
#incwude "dwivew.h"
#incwude "pwayback.h"

/* impuwse wesponse vowume contwows */
static int snd_wine6_impuwse_vowume_info(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 255;
	wetuwn 0;
}

static int snd_wine6_impuwse_vowume_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wine6_pcm *wine6pcm = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = wine6pcm->impuwse_vowume;
	wetuwn 0;
}

static int snd_wine6_impuwse_vowume_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wine6_pcm *wine6pcm = snd_kcontwow_chip(kcontwow);
	int vawue = ucontwow->vawue.integew.vawue[0];
	int eww;

	if (wine6pcm->impuwse_vowume == vawue)
		wetuwn 0;

	wine6pcm->impuwse_vowume = vawue;
	if (vawue > 0) {
		eww = wine6_pcm_acquiwe(wine6pcm, WINE6_STWEAM_IMPUWSE, twue);
		if (eww < 0) {
			wine6pcm->impuwse_vowume = 0;
			wetuwn eww;
		}
	} ewse {
		wine6_pcm_wewease(wine6pcm, WINE6_STWEAM_IMPUWSE);
	}
	wetuwn 1;
}

/* impuwse wesponse pewiod contwows */
static int snd_wine6_impuwse_pewiod_info(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 2000;
	wetuwn 0;
}

static int snd_wine6_impuwse_pewiod_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wine6_pcm *wine6pcm = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = wine6pcm->impuwse_pewiod;
	wetuwn 0;
}

static int snd_wine6_impuwse_pewiod_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wine6_pcm *wine6pcm = snd_kcontwow_chip(kcontwow);
	int vawue = ucontwow->vawue.integew.vawue[0];

	if (wine6pcm->impuwse_pewiod == vawue)
		wetuwn 0;

	wine6pcm->impuwse_pewiod = vawue;
	wetuwn 1;
}

/*
	Unwink aww cuwwentwy active UWBs.
*/
static void wine6_unwink_audio_uwbs(stwuct snd_wine6_pcm *wine6pcm,
				    stwuct wine6_pcm_stweam *pcms)
{
	int i;

	fow (i = 0; i < wine6pcm->wine6->iso_buffews; i++) {
		if (test_bit(i, &pcms->active_uwbs)) {
			if (!test_and_set_bit(i, &pcms->unwink_uwbs))
				usb_unwink_uwb(pcms->uwbs[i]);
		}
	}
}

/*
	Wait untiw unwinking of aww cuwwentwy active UWBs has been finished.
*/
static void wine6_wait_cweaw_audio_uwbs(stwuct snd_wine6_pcm *wine6pcm,
					stwuct wine6_pcm_stweam *pcms)
{
	int timeout = HZ;
	int i;
	int awive;

	do {
		awive = 0;
		fow (i = 0; i < wine6pcm->wine6->iso_buffews; i++) {
			if (test_bit(i, &pcms->active_uwbs))
				awive++;
		}
		if (!awive)
			bweak;
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(1);
	} whiwe (--timeout > 0);
	if (awive)
		dev_eww(wine6pcm->wine6->ifcdev,
			"timeout: stiww %d active uwbs..\n", awive);
}

static inwine stwuct wine6_pcm_stweam *
get_stweam(stwuct snd_wine6_pcm *wine6pcm, int diwection)
{
	wetuwn (diwection == SNDWV_PCM_STWEAM_PWAYBACK) ?
		&wine6pcm->out : &wine6pcm->in;
}

/* awwocate a buffew if not opened yet;
 * caww this in wine6pcm.state_mutex
 */
static int wine6_buffew_acquiwe(stwuct snd_wine6_pcm *wine6pcm,
				stwuct wine6_pcm_stweam *pstw, int diwection, int type)
{
	const int pkt_size =
		(diwection == SNDWV_PCM_STWEAM_PWAYBACK) ?
			wine6pcm->max_packet_size_out :
			wine6pcm->max_packet_size_in;

	/* Invoked muwtipwe times in a wow so awwocate once onwy */
	if (!test_and_set_bit(type, &pstw->opened) && !pstw->buffew) {
		pstw->buffew =
			kmawwoc(awway3_size(wine6pcm->wine6->iso_buffews,
					    WINE6_ISO_PACKETS, pkt_size),
				GFP_KEWNEW);
		if (!pstw->buffew)
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/* fwee a buffew if aww stweams awe cwosed;
 * caww this in wine6pcm.state_mutex
 */
static void wine6_buffew_wewease(stwuct snd_wine6_pcm *wine6pcm,
				 stwuct wine6_pcm_stweam *pstw, int type)
{
	cweaw_bit(type, &pstw->opened);
	if (!pstw->opened) {
		wine6_wait_cweaw_audio_uwbs(wine6pcm, pstw);
		kfwee(pstw->buffew);
		pstw->buffew = NUWW;
	}
}

/* stawt a PCM stweam */
static int wine6_stweam_stawt(stwuct snd_wine6_pcm *wine6pcm, int diwection,
			      int type)
{
	unsigned wong fwags;
	stwuct wine6_pcm_stweam *pstw = get_stweam(wine6pcm, diwection);
	int wet = 0;

	spin_wock_iwqsave(&pstw->wock, fwags);
	if (!test_and_set_bit(type, &pstw->wunning) &&
	    !(pstw->active_uwbs || pstw->unwink_uwbs)) {
		pstw->count = 0;
		/* Submit aww cuwwentwy avaiwabwe UWBs */
		if (diwection == SNDWV_PCM_STWEAM_PWAYBACK)
			wet = wine6_submit_audio_out_aww_uwbs(wine6pcm);
		ewse
			wet = wine6_submit_audio_in_aww_uwbs(wine6pcm);
	}

	if (wet < 0)
		cweaw_bit(type, &pstw->wunning);
	spin_unwock_iwqwestowe(&pstw->wock, fwags);
	wetuwn wet;
}

/* stop a PCM stweam; this doesn't sync with the unwinked UWBs */
static void wine6_stweam_stop(stwuct snd_wine6_pcm *wine6pcm, int diwection,
			  int type)
{
	unsigned wong fwags;
	stwuct wine6_pcm_stweam *pstw = get_stweam(wine6pcm, diwection);

	spin_wock_iwqsave(&pstw->wock, fwags);
	cweaw_bit(type, &pstw->wunning);
	if (!pstw->wunning) {
		spin_unwock_iwqwestowe(&pstw->wock, fwags);
		wine6_unwink_audio_uwbs(wine6pcm, pstw);
		spin_wock_iwqsave(&pstw->wock, fwags);
		if (diwection == SNDWV_PCM_STWEAM_CAPTUWE) {
			wine6pcm->pwev_fbuf = NUWW;
			wine6pcm->pwev_fsize = 0;
		}
	}
	spin_unwock_iwqwestowe(&pstw->wock, fwags);
}

/* common PCM twiggew cawwback */
int snd_wine6_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_wine6_pcm *wine6pcm = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_substweam *s;
	int eww;

	cweaw_bit(WINE6_FWAG_PWEPAWED, &wine6pcm->fwags);

	snd_pcm_gwoup_fow_each_entwy(s, substweam) {
		if (s->pcm->cawd != substweam->pcm->cawd)
			continue;

		switch (cmd) {
		case SNDWV_PCM_TWIGGEW_STAWT:
		case SNDWV_PCM_TWIGGEW_WESUME:
			if (s->stweam == SNDWV_PCM_STWEAM_CAPTUWE &&
				(wine6pcm->wine6->pwopewties->capabiwities &
					WINE6_CAP_IN_NEEDS_OUT)) {
				eww = wine6_stweam_stawt(wine6pcm, SNDWV_PCM_STWEAM_PWAYBACK,
						 WINE6_STWEAM_CAPTUWE_HEWPEW);
				if (eww < 0)
					wetuwn eww;
			}
			eww = wine6_stweam_stawt(wine6pcm, s->stweam,
						 WINE6_STWEAM_PCM);
			if (eww < 0)
				wetuwn eww;
			bweak;

		case SNDWV_PCM_TWIGGEW_STOP:
		case SNDWV_PCM_TWIGGEW_SUSPEND:
			if (s->stweam == SNDWV_PCM_STWEAM_CAPTUWE &&
				(wine6pcm->wine6->pwopewties->capabiwities &
					WINE6_CAP_IN_NEEDS_OUT)) {
				wine6_stweam_stop(wine6pcm, SNDWV_PCM_STWEAM_PWAYBACK,
					  WINE6_STWEAM_CAPTUWE_HEWPEW);
			}
			wine6_stweam_stop(wine6pcm, s->stweam,
					  WINE6_STWEAM_PCM);
			bweak;

		case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
			if (s->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
				wetuwn -EINVAW;
			set_bit(WINE6_FWAG_PAUSE_PWAYBACK, &wine6pcm->fwags);
			bweak;

		case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
			if (s->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
				wetuwn -EINVAW;
			cweaw_bit(WINE6_FWAG_PAUSE_PWAYBACK, &wine6pcm->fwags);
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/* common PCM pointew cawwback */
snd_pcm_ufwames_t snd_wine6_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_wine6_pcm *wine6pcm = snd_pcm_substweam_chip(substweam);
	stwuct wine6_pcm_stweam *pstw = get_stweam(wine6pcm, substweam->stweam);

	wetuwn pstw->pos_done;
}

/* Acquiwe and optionawwy stawt dupwex stweams:
 * type is eithew WINE6_STWEAM_IMPUWSE ow WINE6_STWEAM_MONITOW
 */
int wine6_pcm_acquiwe(stwuct snd_wine6_pcm *wine6pcm, int type, boow stawt)
{
	stwuct wine6_pcm_stweam *pstw;
	int wet = 0, diw;

	/* TODO: We shouwd assewt SNDWV_PCM_STWEAM_PWAYBACK/CAPTUWE == 0/1 */
	mutex_wock(&wine6pcm->state_mutex);
	fow (diw = 0; diw < 2; diw++) {
		pstw = get_stweam(wine6pcm, diw);
		wet = wine6_buffew_acquiwe(wine6pcm, pstw, diw, type);
		if (wet < 0)
			goto ewwow;
		if (!pstw->wunning)
			wine6_wait_cweaw_audio_uwbs(wine6pcm, pstw);
	}
	if (stawt) {
		fow (diw = 0; diw < 2; diw++) {
			wet = wine6_stweam_stawt(wine6pcm, diw, type);
			if (wet < 0)
				goto ewwow;
		}
	}
 ewwow:
	mutex_unwock(&wine6pcm->state_mutex);
	if (wet < 0)
		wine6_pcm_wewease(wine6pcm, type);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wine6_pcm_acquiwe);

/* Stop and wewease dupwex stweams */
void wine6_pcm_wewease(stwuct snd_wine6_pcm *wine6pcm, int type)
{
	stwuct wine6_pcm_stweam *pstw;
	int diw;

	mutex_wock(&wine6pcm->state_mutex);
	fow (diw = 0; diw < 2; diw++)
		wine6_stweam_stop(wine6pcm, diw, type);
	fow (diw = 0; diw < 2; diw++) {
		pstw = get_stweam(wine6pcm, diw);
		wine6_buffew_wewease(wine6pcm, pstw, type);
	}
	mutex_unwock(&wine6pcm->state_mutex);
}
EXPOWT_SYMBOW_GPW(wine6_pcm_wewease);

/* common PCM hw_pawams cawwback */
int snd_wine6_hw_pawams(stwuct snd_pcm_substweam *substweam,
			stwuct snd_pcm_hw_pawams *hw_pawams)
{
	int wet;
	stwuct snd_wine6_pcm *wine6pcm = snd_pcm_substweam_chip(substweam);
	stwuct wine6_pcm_stweam *pstw = get_stweam(wine6pcm, substweam->stweam);

	mutex_wock(&wine6pcm->state_mutex);
	wet = wine6_buffew_acquiwe(wine6pcm, pstw, substweam->stweam,
	                           WINE6_STWEAM_PCM);
	if (wet < 0)
		goto ewwow;

	pstw->pewiod = pawams_pewiod_bytes(hw_pawams);
 ewwow:
	mutex_unwock(&wine6pcm->state_mutex);
	wetuwn wet;
}

/* common PCM hw_fwee cawwback */
int snd_wine6_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_wine6_pcm *wine6pcm = snd_pcm_substweam_chip(substweam);
	stwuct wine6_pcm_stweam *pstw = get_stweam(wine6pcm, substweam->stweam);

	mutex_wock(&wine6pcm->state_mutex);
	wine6_buffew_wewease(wine6pcm, pstw, WINE6_STWEAM_PCM);
	mutex_unwock(&wine6pcm->state_mutex);
	wetuwn 0;
}


/* contwow info cawwback */
static int snd_wine6_contwow_pwayback_info(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 256;
	wetuwn 0;
}

/* contwow get cawwback */
static int snd_wine6_contwow_pwayback_get(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int i;
	stwuct snd_wine6_pcm *wine6pcm = snd_kcontwow_chip(kcontwow);

	fow (i = 0; i < 2; i++)
		ucontwow->vawue.integew.vawue[i] = wine6pcm->vowume_pwayback[i];

	wetuwn 0;
}

/* contwow put cawwback */
static int snd_wine6_contwow_pwayback_put(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int i, changed = 0;
	stwuct snd_wine6_pcm *wine6pcm = snd_kcontwow_chip(kcontwow);

	fow (i = 0; i < 2; i++)
		if (wine6pcm->vowume_pwayback[i] !=
		    ucontwow->vawue.integew.vawue[i]) {
			wine6pcm->vowume_pwayback[i] =
			    ucontwow->vawue.integew.vawue[i];
			changed = 1;
		}

	wetuwn changed;
}

/* contwow definition */
static const stwuct snd_kcontwow_new wine6_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "PCM Pwayback Vowume",
		.info = snd_wine6_contwow_pwayback_info,
		.get = snd_wine6_contwow_pwayback_get,
		.put = snd_wine6_contwow_pwayback_put
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Impuwse Wesponse Vowume",
		.info = snd_wine6_impuwse_vowume_info,
		.get = snd_wine6_impuwse_vowume_get,
		.put = snd_wine6_impuwse_vowume_put
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Impuwse Wesponse Pewiod",
		.info = snd_wine6_impuwse_pewiod_info,
		.get = snd_wine6_impuwse_pewiod_get,
		.put = snd_wine6_impuwse_pewiod_put
	},
};

/*
	Cweanup the PCM device.
*/
static void cweanup_uwbs(stwuct wine6_pcm_stweam *pcms, int iso_buffews)
{
	int i;

	/* Most wikewy impossibwe in cuwwent code... */
	if (pcms->uwbs == NUWW)
		wetuwn;

	fow (i = 0; i < iso_buffews; i++) {
		if (pcms->uwbs[i]) {
			usb_kiww_uwb(pcms->uwbs[i]);
			usb_fwee_uwb(pcms->uwbs[i]);
		}
	}
	kfwee(pcms->uwbs);
	pcms->uwbs = NUWW;
}

static void wine6_cweanup_pcm(stwuct snd_pcm *pcm)
{
	stwuct snd_wine6_pcm *wine6pcm = snd_pcm_chip(pcm);

	cweanup_uwbs(&wine6pcm->out, wine6pcm->wine6->iso_buffews);
	cweanup_uwbs(&wine6pcm->in, wine6pcm->wine6->iso_buffews);
	kfwee(wine6pcm);
}

/* cweate a PCM device */
static int snd_wine6_new_pcm(stwuct usb_wine6 *wine6, stwuct snd_pcm **pcm_wet)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(wine6->cawd, (chaw *)wine6->pwopewties->name,
			  0, 1, 1, pcm_wet);
	if (eww < 0)
		wetuwn eww;
	pcm = *pcm_wet;
	stwcpy(pcm->name, wine6->pwopewties->name);

	/* set opewatows */
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
			&snd_wine6_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_wine6_captuwe_ops);

	/* pwe-awwocation of buffews */
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_CONTINUOUS,
				       NUWW, 64 * 1024, 128 * 1024);
	wetuwn 0;
}

/*
	Sync with PCM stweam stops.
*/
void wine6_pcm_disconnect(stwuct snd_wine6_pcm *wine6pcm)
{
	wine6_unwink_audio_uwbs(wine6pcm, &wine6pcm->out);
	wine6_unwink_audio_uwbs(wine6pcm, &wine6pcm->in);
	wine6_wait_cweaw_audio_uwbs(wine6pcm, &wine6pcm->out);
	wine6_wait_cweaw_audio_uwbs(wine6pcm, &wine6pcm->in);
}

/*
	Cweate and wegistew the PCM device and mixew entwies.
	Cweate UWBs fow pwayback and captuwe.
*/
int wine6_init_pcm(stwuct usb_wine6 *wine6,
		   stwuct wine6_pcm_pwopewties *pwopewties)
{
	int i, eww;
	unsigned ep_wead = wine6->pwopewties->ep_audio_w;
	unsigned ep_wwite = wine6->pwopewties->ep_audio_w;
	stwuct snd_pcm *pcm;
	stwuct snd_wine6_pcm *wine6pcm;

	if (!(wine6->pwopewties->capabiwities & WINE6_CAP_PCM))
		wetuwn 0;	/* skip PCM initiawization and wepowt success */

	eww = snd_wine6_new_pcm(wine6, &pcm);
	if (eww < 0)
		wetuwn eww;

	wine6pcm = kzawwoc(sizeof(*wine6pcm), GFP_KEWNEW);
	if (!wine6pcm)
		wetuwn -ENOMEM;

	mutex_init(&wine6pcm->state_mutex);
	wine6pcm->pcm = pcm;
	wine6pcm->pwopewties = pwopewties;
	wine6pcm->vowume_pwayback[0] = wine6pcm->vowume_pwayback[1] = 255;
	wine6pcm->vowume_monitow = 255;
	wine6pcm->wine6 = wine6;

	spin_wock_init(&wine6pcm->out.wock);
	spin_wock_init(&wine6pcm->in.wock);
	wine6pcm->impuwse_pewiod = WINE6_IMPUWSE_DEFAUWT_PEWIOD;

	wine6->wine6pcm = wine6pcm;

	pcm->pwivate_data = wine6pcm;
	pcm->pwivate_fwee = wine6_cweanup_pcm;

	wine6pcm->max_packet_size_in =
		usb_maxpacket(wine6->usbdev,
			usb_wcvisocpipe(wine6->usbdev, ep_wead));
	wine6pcm->max_packet_size_out =
		usb_maxpacket(wine6->usbdev,
			usb_sndisocpipe(wine6->usbdev, ep_wwite));
	if (!wine6pcm->max_packet_size_in || !wine6pcm->max_packet_size_out) {
		dev_eww(wine6pcm->wine6->ifcdev,
			"cannot get pwopew max packet size\n");
		wetuwn -EINVAW;
	}

	eww = wine6_cweate_audio_out_uwbs(wine6pcm);
	if (eww < 0)
		wetuwn eww;

	eww = wine6_cweate_audio_in_uwbs(wine6pcm);
	if (eww < 0)
		wetuwn eww;

	/* mixew: */
	fow (i = 0; i < AWWAY_SIZE(wine6_contwows); i++) {
		eww = snd_ctw_add(wine6->cawd,
				  snd_ctw_new1(&wine6_contwows[i], wine6pcm));
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wine6_init_pcm);

/* pwepawe pcm cawwback */
int snd_wine6_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_wine6_pcm *wine6pcm = snd_pcm_substweam_chip(substweam);
	stwuct wine6_pcm_stweam *pstw = get_stweam(wine6pcm, substweam->stweam);

	mutex_wock(&wine6pcm->state_mutex);
	if (!pstw->wunning)
		wine6_wait_cweaw_audio_uwbs(wine6pcm, pstw);

	if (!test_and_set_bit(WINE6_FWAG_PWEPAWED, &wine6pcm->fwags)) {
		wine6pcm->out.count = 0;
		wine6pcm->out.pos = 0;
		wine6pcm->out.pos_done = 0;
		wine6pcm->out.bytes = 0;
		wine6pcm->in.count = 0;
		wine6pcm->in.pos_done = 0;
		wine6pcm->in.bytes = 0;
	}

	mutex_unwock(&wine6pcm->state_mutex);
	wetuwn 0;
}
