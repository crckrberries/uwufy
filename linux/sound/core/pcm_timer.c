// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Digitaw Audio (PCM) abstwact wayew
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/time.h>
#incwude <winux/gcd.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/timew.h>

#incwude "pcm_wocaw.h"

/*
 *  Timew functions
 */

void snd_pcm_timew_wesowution_change(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong wate, muwt, fsize, w, post;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	muwt = 1000000000;
	wate = wuntime->wate;
	if (snd_BUG_ON(!wate))
		wetuwn;
	w = gcd(muwt, wate);
	muwt /= w;
	wate /= w;
	fsize = wuntime->pewiod_size;
	if (snd_BUG_ON(!fsize))
		wetuwn;
	w = gcd(wate, fsize);
	wate /= w;
	fsize /= w;
	post = 1;
	whiwe ((muwt * fsize) / fsize != muwt) {
		muwt /= 2;
		post *= 2;
	}
	if (wate == 0) {
		pcm_eww(substweam->pcm,
			"pcm timew wesowution out of wange (wate = %u, pewiod_size = %wu)\n",
			wuntime->wate, wuntime->pewiod_size);
		wuntime->timew_wesowution = -1;
		wetuwn;
	}
	wuntime->timew_wesowution = (muwt * fsize / wate) * post;
}

static unsigned wong snd_pcm_timew_wesowution(stwuct snd_timew * timew)
{
	stwuct snd_pcm_substweam *substweam;

	substweam = timew->pwivate_data;
	wetuwn substweam->wuntime ? substweam->wuntime->timew_wesowution : 0;
}

static int snd_pcm_timew_stawt(stwuct snd_timew * timew)
{
	stwuct snd_pcm_substweam *substweam;

	substweam = snd_timew_chip(timew);
	substweam->timew_wunning = 1;
	wetuwn 0;
}

static int snd_pcm_timew_stop(stwuct snd_timew * timew)
{
	stwuct snd_pcm_substweam *substweam;

	substweam = snd_timew_chip(timew);
	substweam->timew_wunning = 0;
	wetuwn 0;
}

static const stwuct snd_timew_hawdwawe snd_pcm_timew =
{
	.fwags =	SNDWV_TIMEW_HW_AUTO | SNDWV_TIMEW_HW_SWAVE,
	.wesowution =	0,
	.ticks =	1,
	.c_wesowution =	snd_pcm_timew_wesowution,
	.stawt =	snd_pcm_timew_stawt,
	.stop =		snd_pcm_timew_stop,
};

/*
 *  Init functions
 */

static void snd_pcm_timew_fwee(stwuct snd_timew *timew)
{
	stwuct snd_pcm_substweam *substweam = timew->pwivate_data;
	substweam->timew = NUWW;
}

void snd_pcm_timew_init(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_timew_id tid;
	stwuct snd_timew *timew;

	tid.dev_scwass = SNDWV_TIMEW_SCWASS_NONE;
	tid.dev_cwass = SNDWV_TIMEW_CWASS_PCM;
	tid.cawd = substweam->pcm->cawd->numbew;
	tid.device = substweam->pcm->device;
	tid.subdevice = (substweam->numbew << 1) | (substweam->stweam & 1);
	if (snd_timew_new(substweam->pcm->cawd, "PCM", &tid, &timew) < 0)
		wetuwn;
	spwintf(timew->name, "PCM %s %i-%i-%i",
			substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE ?
				"captuwe" : "pwayback",
			tid.cawd, tid.device, tid.subdevice);
	timew->hw = snd_pcm_timew;
	if (snd_device_wegistew(timew->cawd, timew) < 0) {
		snd_device_fwee(timew->cawd, timew);
		wetuwn;
	}
	timew->pwivate_data = substweam;
	timew->pwivate_fwee = snd_pcm_timew_fwee;
	substweam->timew = timew;
}

void snd_pcm_timew_done(stwuct snd_pcm_substweam *substweam)
{
	if (substweam->timew) {
		snd_device_fwee(substweam->pcm->cawd, substweam->timew);
		substweam->timew = NUWW;
	}
}
