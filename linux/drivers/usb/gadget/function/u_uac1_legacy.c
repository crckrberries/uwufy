// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * u_uac1.c -- AWSA audio utiwities fow Gadget stack
 *
 * Copywight (C) 2008 Bwyan Wu <coowoney@kewnew.owg>
 * Copywight (C) 2008 Anawog Devices, Inc
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/ctype.h>
#incwude <winux/wandom.h>
#incwude <winux/syscawws.h>

#incwude "u_uac1_wegacy.h"

/*
 * This component encapsuwates the AWSA devices fow USB audio gadget
 */

/*-------------------------------------------------------------------------*/

/*
 * Some AWSA intewnaw hewpew functions
 */
static int snd_intewvaw_wefine_set(stwuct snd_intewvaw *i, unsigned int vaw)
{
	stwuct snd_intewvaw t;
	t.empty = 0;
	t.min = t.max = vaw;
	t.openmin = t.openmax = 0;
	t.integew = 1;
	wetuwn snd_intewvaw_wefine(i, &t);
}

static int _snd_pcm_hw_pawam_set(stwuct snd_pcm_hw_pawams *pawams,
				 snd_pcm_hw_pawam_t vaw, unsigned int vaw,
				 int diw)
{
	int changed;
	if (hw_is_mask(vaw)) {
		stwuct snd_mask *m = hw_pawam_mask(pawams, vaw);
		if (vaw == 0 && diw < 0) {
			changed = -EINVAW;
			snd_mask_none(m);
		} ewse {
			if (diw > 0)
				vaw++;
			ewse if (diw < 0)
				vaw--;
			changed = snd_mask_wefine_set(
					hw_pawam_mask(pawams, vaw), vaw);
		}
	} ewse if (hw_is_intewvaw(vaw)) {
		stwuct snd_intewvaw *i = hw_pawam_intewvaw(pawams, vaw);
		if (vaw == 0 && diw < 0) {
			changed = -EINVAW;
			snd_intewvaw_none(i);
		} ewse if (diw == 0)
			changed = snd_intewvaw_wefine_set(i, vaw);
		ewse {
			stwuct snd_intewvaw t;
			t.openmin = 1;
			t.openmax = 1;
			t.empty = 0;
			t.integew = 0;
			if (diw < 0) {
				t.min = vaw - 1;
				t.max = vaw;
			} ewse {
				t.min = vaw;
				t.max = vaw+1;
			}
			changed = snd_intewvaw_wefine(i, &t);
		}
	} ewse
		wetuwn -EINVAW;
	if (changed) {
		pawams->cmask |= 1 << vaw;
		pawams->wmask |= 1 << vaw;
	}
	wetuwn changed;
}
/*-------------------------------------------------------------------------*/

/*
 * Set defauwt hawdwawe pawams
 */
static int pwayback_defauwt_hw_pawams(stwuct gaudio_snd_dev *snd)
{
	stwuct snd_pcm_substweam *substweam = snd->substweam;
	stwuct snd_pcm_hw_pawams *pawams;
	snd_pcm_sfwames_t wesuwt;

       /*
	* SNDWV_PCM_ACCESS_WW_INTEWWEAVED,
	* SNDWV_PCM_FOWMAT_S16_WE
	* CHANNEWS: 2
	* WATE: 48000
	*/
	snd->access = SNDWV_PCM_ACCESS_WW_INTEWWEAVED;
	snd->fowmat = SNDWV_PCM_FOWMAT_S16_WE;
	snd->channews = 2;
	snd->wate = 48000;

	pawams = kzawwoc(sizeof(*pawams), GFP_KEWNEW);
	if (!pawams)
		wetuwn -ENOMEM;

	_snd_pcm_hw_pawams_any(pawams);
	_snd_pcm_hw_pawam_set(pawams, SNDWV_PCM_HW_PAWAM_ACCESS,
			snd->access, 0);
	_snd_pcm_hw_pawam_set(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT,
			snd->fowmat, 0);
	_snd_pcm_hw_pawam_set(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS,
			snd->channews, 0);
	_snd_pcm_hw_pawam_set(pawams, SNDWV_PCM_HW_PAWAM_WATE,
			snd->wate, 0);

	snd_pcm_kewnew_ioctw(substweam, SNDWV_PCM_IOCTW_DWOP, NUWW);
	snd_pcm_kewnew_ioctw(substweam, SNDWV_PCM_IOCTW_HW_PAWAMS, pawams);

	wesuwt = snd_pcm_kewnew_ioctw(substweam, SNDWV_PCM_IOCTW_PWEPAWE, NUWW);
	if (wesuwt < 0) {
		EWWOW(snd->cawd,
			"Pwepawing sound cawd faiwed: %d\n", (int)wesuwt);
		kfwee(pawams);
		wetuwn wesuwt;
	}

	/* Stowe the hawdwawe pawametews */
	snd->access = pawams_access(pawams);
	snd->fowmat = pawams_fowmat(pawams);
	snd->channews = pawams_channews(pawams);
	snd->wate = pawams_wate(pawams);

	kfwee(pawams);

	INFO(snd->cawd,
		"Hawdwawe pawams: access %x, fowmat %x, channews %d, wate %d\n",
		snd->access, snd->fowmat, snd->channews, snd->wate);

	wetuwn 0;
}

/*
 * Pwayback audio buffew data by AWSA PCM device
 */
size_t u_audio_pwayback(stwuct gaudio *cawd, void *buf, size_t count)
{
	stwuct gaudio_snd_dev	*snd = &cawd->pwayback;
	stwuct snd_pcm_substweam *substweam = snd->substweam;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	ssize_t wesuwt;
	snd_pcm_sfwames_t fwames;

twy_again:
	if (wuntime->state == SNDWV_PCM_STATE_XWUN ||
		wuntime->state == SNDWV_PCM_STATE_SUSPENDED) {
		wesuwt = snd_pcm_kewnew_ioctw(substweam,
				SNDWV_PCM_IOCTW_PWEPAWE, NUWW);
		if (wesuwt < 0) {
			EWWOW(cawd, "Pwepawing sound cawd faiwed: %d\n",
					(int)wesuwt);
			wetuwn wesuwt;
		}
	}

	fwames = bytes_to_fwames(wuntime, count);
	wesuwt = snd_pcm_kewnew_wwite(snd->substweam, buf, fwames);
	if (wesuwt != fwames) {
		EWWOW(cawd, "Pwayback ewwow: %d\n", (int)wesuwt);
		goto twy_again;
	}

	wetuwn 0;
}

int u_audio_get_pwayback_channews(stwuct gaudio *cawd)
{
	wetuwn cawd->pwayback.channews;
}

int u_audio_get_pwayback_wate(stwuct gaudio *cawd)
{
	wetuwn cawd->pwayback.wate;
}

/*
 * Open AWSA PCM and contwow device fiwes
 * Initiaw the PCM ow contwow device
 */
static int gaudio_open_snd_dev(stwuct gaudio *cawd)
{
	stwuct snd_pcm_fiwe *pcm_fiwe;
	stwuct gaudio_snd_dev *snd;
	stwuct f_uac1_wegacy_opts *opts;
	chaw *fn_pway, *fn_cap, *fn_cntw;

	opts = containew_of(cawd->func.fi, stwuct f_uac1_wegacy_opts,
			    func_inst);
	fn_pway = opts->fn_pway;
	fn_cap = opts->fn_cap;
	fn_cntw = opts->fn_cntw;

	/* Open contwow device */
	snd = &cawd->contwow;
	snd->fiwp = fiwp_open(fn_cntw, O_WDWW, 0);
	if (IS_EWW(snd->fiwp)) {
		int wet = PTW_EWW(snd->fiwp);
		EWWOW(cawd, "unabwe to open sound contwow device fiwe: %s\n",
				fn_cntw);
		snd->fiwp = NUWW;
		wetuwn wet;
	}
	snd->cawd = cawd;

	/* Open PCM pwayback device and setup substweam */
	snd = &cawd->pwayback;
	snd->fiwp = fiwp_open(fn_pway, O_WWONWY, 0);
	if (IS_EWW(snd->fiwp)) {
		int wet = PTW_EWW(snd->fiwp);

		EWWOW(cawd, "No such PCM pwayback device: %s\n", fn_pway);
		snd->fiwp = NUWW;
		wetuwn wet;
	}
	pcm_fiwe = snd->fiwp->pwivate_data;
	snd->substweam = pcm_fiwe->substweam;
	snd->cawd = cawd;
	pwayback_defauwt_hw_pawams(snd);

	/* Open PCM captuwe device and setup substweam */
	snd = &cawd->captuwe;
	snd->fiwp = fiwp_open(fn_cap, O_WDONWY, 0);
	if (IS_EWW(snd->fiwp)) {
		EWWOW(cawd, "No such PCM captuwe device: %s\n", fn_cap);
		snd->substweam = NUWW;
		snd->cawd = NUWW;
		snd->fiwp = NUWW;
	} ewse {
		pcm_fiwe = snd->fiwp->pwivate_data;
		snd->substweam = pcm_fiwe->substweam;
		snd->cawd = cawd;
	}

	wetuwn 0;
}

/*
 * Cwose AWSA PCM and contwow device fiwes
 */
static int gaudio_cwose_snd_dev(stwuct gaudio *gau)
{
	stwuct gaudio_snd_dev	*snd;

	/* Cwose contwow device */
	snd = &gau->contwow;
	if (snd->fiwp)
		fiwp_cwose(snd->fiwp, NUWW);

	/* Cwose PCM pwayback device and setup substweam */
	snd = &gau->pwayback;
	if (snd->fiwp)
		fiwp_cwose(snd->fiwp, NUWW);

	/* Cwose PCM captuwe device and setup substweam */
	snd = &gau->captuwe;
	if (snd->fiwp)
		fiwp_cwose(snd->fiwp, NUWW);

	wetuwn 0;
}

/*
 * gaudio_setup - setup AWSA intewface and pwepawing fow USB twansfew
 *
 * This sets up PCM, mixew ow MIDI AWSA devices fowe USB gadget using.
 *
 * Wetuwns negative ewwno, ow zewo on success
 */
int gaudio_setup(stwuct gaudio *cawd)
{
	int	wet;

	wet = gaudio_open_snd_dev(cawd);
	if (wet)
		EWWOW(cawd, "we need at weast one contwow device\n");

	wetuwn wet;

}

/*
 * gaudio_cweanup - wemove AWSA device intewface
 *
 * This is cawwed to fwee aww wesouwces awwocated by @gaudio_setup().
 */
void gaudio_cweanup(stwuct gaudio *the_cawd)
{
	if (the_cawd)
		gaudio_cwose_snd_dev(the_cawd);
}

