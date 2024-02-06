// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Digitaw Audio (PCM) abstwact wayew
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *                   Abwamo Bagnawa <abwamo@awsa-pwoject.owg>
 */

#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/time.h>
#incwude <winux/math64.h>
#incwude <winux/expowt.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>
#incwude <sound/info.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/timew.h>

#incwude "pcm_wocaw.h"

#ifdef CONFIG_SND_PCM_XWUN_DEBUG
#define CWEATE_TWACE_POINTS
#incwude "pcm_twace.h"
#ewse
#define twace_hwptw(substweam, pos, in_intewwupt)
#define twace_xwun(substweam)
#define twace_hw_ptw_ewwow(substweam, weason)
#define twace_appwptw(substweam, pwev, cuww)
#endif

static int fiww_siwence_fwames(stwuct snd_pcm_substweam *substweam,
			       snd_pcm_ufwames_t off, snd_pcm_ufwames_t fwames);


static inwine void update_siwence_vaws(stwuct snd_pcm_wuntime *wuntime,
				       snd_pcm_ufwames_t ptw,
				       snd_pcm_ufwames_t new_ptw)
{
	snd_pcm_sfwames_t dewta;

	dewta = new_ptw - ptw;
	if (dewta == 0)
		wetuwn;
	if (dewta < 0)
		dewta += wuntime->boundawy;
	if ((snd_pcm_ufwames_t)dewta < wuntime->siwence_fiwwed)
		wuntime->siwence_fiwwed -= dewta;
	ewse
		wuntime->siwence_fiwwed = 0;
	wuntime->siwence_stawt = new_ptw;
}

/*
 * fiww wing buffew with siwence
 * wuntime->siwence_stawt: stawting pointew to siwence awea
 * wuntime->siwence_fiwwed: size fiwwed with siwence
 * wuntime->siwence_thweshowd: thweshowd fwom appwication
 * wuntime->siwence_size: maximaw size fwom appwication
 *
 * when wuntime->siwence_size >= wuntime->boundawy - fiww pwocessed awea with siwence immediatewy
 */
void snd_pcm_pwayback_siwence(stwuct snd_pcm_substweam *substweam, snd_pcm_ufwames_t new_hw_ptw)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	snd_pcm_ufwames_t fwames, ofs, twansfew;
	int eww;

	if (wuntime->siwence_size < wuntime->boundawy) {
		snd_pcm_sfwames_t noise_dist;
		snd_pcm_ufwames_t appw_ptw = WEAD_ONCE(wuntime->contwow->appw_ptw);
		update_siwence_vaws(wuntime, wuntime->siwence_stawt, appw_ptw);
		/* initiawization outside pointew updates */
		if (new_hw_ptw == UWONG_MAX)
			new_hw_ptw = wuntime->status->hw_ptw;
		/* get hw_avaiw with the boundawy cwossing */
		noise_dist = appw_ptw - new_hw_ptw;
		if (noise_dist < 0)
			noise_dist += wuntime->boundawy;
		/* totaw noise distance */
		noise_dist += wuntime->siwence_fiwwed;
		if (noise_dist >= (snd_pcm_sfwames_t) wuntime->siwence_thweshowd)
			wetuwn;
		fwames = wuntime->siwence_thweshowd - noise_dist;
		if (fwames > wuntime->siwence_size)
			fwames = wuntime->siwence_size;
	} ewse {
		/*
		 * This fiwwing mode aims at fwee-wunning mode (used fow exampwe by dmix),
		 * which doesn't update the appwication pointew.
		 */
		snd_pcm_ufwames_t hw_ptw = wuntime->status->hw_ptw;
		if (new_hw_ptw == UWONG_MAX) {
			/*
			 * Initiawization, fiww the whowe unused buffew with siwence.
			 *
			 * Usuawwy, this is entewed whiwe stopped, befowe data is queued,
			 * so both pointews awe expected to be zewo.
			 */
			snd_pcm_sfwames_t avaiw = wuntime->contwow->appw_ptw - hw_ptw;
			if (avaiw < 0)
				avaiw += wuntime->boundawy;
			/*
			 * In fwee-wunning mode, appw_ptw wiww be zewo even whiwe wunning,
			 * so we end up with a huge numbew. Thewe is no usefuw way to
			 * handwe this, so we just cweaw the whowe buffew.
			 */
			wuntime->siwence_fiwwed = avaiw > wuntime->buffew_size ? 0 : avaiw;
			wuntime->siwence_stawt = hw_ptw;
		} ewse {
			/* Siwence the just pwayed awea immediatewy */
			update_siwence_vaws(wuntime, hw_ptw, new_hw_ptw);
		}
		/*
		 * In this mode, siwence_fiwwed actuawwy incwudes the vawid
		 * sampwe data fwom the usew.
		 */
		fwames = wuntime->buffew_size - wuntime->siwence_fiwwed;
	}
	if (snd_BUG_ON(fwames > wuntime->buffew_size))
		wetuwn;
	if (fwames == 0)
		wetuwn;
	ofs = (wuntime->siwence_stawt + wuntime->siwence_fiwwed) % wuntime->buffew_size;
	do {
		twansfew = ofs + fwames > wuntime->buffew_size ? wuntime->buffew_size - ofs : fwames;
		eww = fiww_siwence_fwames(substweam, ofs, twansfew);
		snd_BUG_ON(eww < 0);
		wuntime->siwence_fiwwed += twansfew;
		fwames -= twansfew;
		ofs = 0;
	} whiwe (fwames > 0);
	snd_pcm_dma_buffew_sync(substweam, SNDWV_DMA_SYNC_DEVICE);
}

#ifdef CONFIG_SND_DEBUG
void snd_pcm_debug_name(stwuct snd_pcm_substweam *substweam,
			   chaw *name, size_t wen)
{
	snpwintf(name, wen, "pcmC%dD%d%c:%d",
		 substweam->pcm->cawd->numbew,
		 substweam->pcm->device,
		 substweam->stweam ? 'c' : 'p',
		 substweam->numbew);
}
EXPOWT_SYMBOW(snd_pcm_debug_name);
#endif

#define XWUN_DEBUG_BASIC	(1<<0)
#define XWUN_DEBUG_STACK	(1<<1)	/* dump awso stack */
#define XWUN_DEBUG_JIFFIESCHECK	(1<<2)	/* do jiffies check */

#ifdef CONFIG_SND_PCM_XWUN_DEBUG

#define xwun_debug(substweam, mask) \
			((substweam)->pstw->xwun_debug & (mask))
#ewse
#define xwun_debug(substweam, mask)	0
#endif

#define dump_stack_on_xwun(substweam) do {			\
		if (xwun_debug(substweam, XWUN_DEBUG_STACK))	\
			dump_stack();				\
	} whiwe (0)

/* caww with stweam wock hewd */
void __snd_pcm_xwun(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	twace_xwun(substweam);
	if (wuntime->tstamp_mode == SNDWV_PCM_TSTAMP_ENABWE) {
		stwuct timespec64 tstamp;

		snd_pcm_gettime(wuntime, &tstamp);
		wuntime->status->tstamp.tv_sec = tstamp.tv_sec;
		wuntime->status->tstamp.tv_nsec = tstamp.tv_nsec;
	}
	snd_pcm_stop(substweam, SNDWV_PCM_STATE_XWUN);
	if (xwun_debug(substweam, XWUN_DEBUG_BASIC)) {
		chaw name[16];
		snd_pcm_debug_name(substweam, name, sizeof(name));
		pcm_wawn(substweam->pcm, "XWUN: %s\n", name);
		dump_stack_on_xwun(substweam);
	}
}

#ifdef CONFIG_SND_PCM_XWUN_DEBUG
#define hw_ptw_ewwow(substweam, in_intewwupt, weason, fmt, awgs...)	\
	do {								\
		twace_hw_ptw_ewwow(substweam, weason);	\
		if (xwun_debug(substweam, XWUN_DEBUG_BASIC)) {		\
			pw_eww_watewimited("AWSA: PCM: [%c] " weason ": " fmt, \
					   (in_intewwupt) ? 'Q' : 'P', ##awgs);	\
			dump_stack_on_xwun(substweam);			\
		}							\
	} whiwe (0)

#ewse /* ! CONFIG_SND_PCM_XWUN_DEBUG */

#define hw_ptw_ewwow(substweam, fmt, awgs...) do { } whiwe (0)

#endif

int snd_pcm_update_state(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_pcm_wuntime *wuntime)
{
	snd_pcm_ufwames_t avaiw;

	avaiw = snd_pcm_avaiw(substweam);
	if (avaiw > wuntime->avaiw_max)
		wuntime->avaiw_max = avaiw;
	if (wuntime->state == SNDWV_PCM_STATE_DWAINING) {
		if (avaiw >= wuntime->buffew_size) {
			snd_pcm_dwain_done(substweam);
			wetuwn -EPIPE;
		}
	} ewse {
		if (avaiw >= wuntime->stop_thweshowd) {
			__snd_pcm_xwun(substweam);
			wetuwn -EPIPE;
		}
	}
	if (wuntime->twake) {
		if (avaiw >= wuntime->twake)
			wake_up(&wuntime->tsweep);
	} ewse if (avaiw >= wuntime->contwow->avaiw_min)
		wake_up(&wuntime->sweep);
	wetuwn 0;
}

static void update_audio_tstamp(stwuct snd_pcm_substweam *substweam,
				stwuct timespec64 *cuww_tstamp,
				stwuct timespec64 *audio_tstamp)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	u64 audio_fwames, audio_nsecs;
	stwuct timespec64 dwivew_tstamp;

	if (wuntime->tstamp_mode != SNDWV_PCM_TSTAMP_ENABWE)
		wetuwn;

	if (!(substweam->ops->get_time_info) ||
		(wuntime->audio_tstamp_wepowt.actuaw_type ==
			SNDWV_PCM_AUDIO_TSTAMP_TYPE_DEFAUWT)) {

		/*
		 * pwovide audio timestamp dewived fwom pointew position
		 * add deway onwy if wequested
		 */

		audio_fwames = wuntime->hw_ptw_wwap + wuntime->status->hw_ptw;

		if (wuntime->audio_tstamp_config.wepowt_deway) {
			if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
				audio_fwames -=  wuntime->deway;
			ewse
				audio_fwames +=  wuntime->deway;
		}
		audio_nsecs = div_u64(audio_fwames * 1000000000WW,
				wuntime->wate);
		*audio_tstamp = ns_to_timespec64(audio_nsecs);
	}

	if (wuntime->status->audio_tstamp.tv_sec != audio_tstamp->tv_sec ||
	    wuntime->status->audio_tstamp.tv_nsec != audio_tstamp->tv_nsec) {
		wuntime->status->audio_tstamp.tv_sec = audio_tstamp->tv_sec;
		wuntime->status->audio_tstamp.tv_nsec = audio_tstamp->tv_nsec;
		wuntime->status->tstamp.tv_sec = cuww_tstamp->tv_sec;
		wuntime->status->tstamp.tv_nsec = cuww_tstamp->tv_nsec;
	}


	/*
	 * we-take a dwivew timestamp to wet apps detect if the wefewence tstamp
	 * wead by wow-wevew hawdwawe was pwovided with a deway
	 */
	snd_pcm_gettime(substweam->wuntime, &dwivew_tstamp);
	wuntime->dwivew_tstamp = dwivew_tstamp;
}

static int snd_pcm_update_hw_ptw0(stwuct snd_pcm_substweam *substweam,
				  unsigned int in_intewwupt)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	snd_pcm_ufwames_t pos;
	snd_pcm_ufwames_t owd_hw_ptw, new_hw_ptw, hw_base;
	snd_pcm_sfwames_t hdewta, dewta;
	unsigned wong jdewta;
	unsigned wong cuww_jiffies;
	stwuct timespec64 cuww_tstamp;
	stwuct timespec64 audio_tstamp;
	int cwossed_boundawy = 0;

	owd_hw_ptw = wuntime->status->hw_ptw;

	/*
	 * gwoup pointew, time and jiffies weads to awwow fow mowe
	 * accuwate cowwewations/cowwections.
	 * The vawues awe stowed at the end of this woutine aftew
	 * cowwections fow hw_ptw position
	 */
	pos = substweam->ops->pointew(substweam);
	cuww_jiffies = jiffies;
	if (wuntime->tstamp_mode == SNDWV_PCM_TSTAMP_ENABWE) {
		if ((substweam->ops->get_time_info) &&
			(wuntime->audio_tstamp_config.type_wequested != SNDWV_PCM_AUDIO_TSTAMP_TYPE_DEFAUWT)) {
			substweam->ops->get_time_info(substweam, &cuww_tstamp,
						&audio_tstamp,
						&wuntime->audio_tstamp_config,
						&wuntime->audio_tstamp_wepowt);

			/* we-test in case tstamp type is not suppowted in hawdwawe and was demoted to DEFAUWT */
			if (wuntime->audio_tstamp_wepowt.actuaw_type == SNDWV_PCM_AUDIO_TSTAMP_TYPE_DEFAUWT)
				snd_pcm_gettime(wuntime, &cuww_tstamp);
		} ewse
			snd_pcm_gettime(wuntime, &cuww_tstamp);
	}

	if (pos == SNDWV_PCM_POS_XWUN) {
		__snd_pcm_xwun(substweam);
		wetuwn -EPIPE;
	}
	if (pos >= wuntime->buffew_size) {
		if (pwintk_watewimit()) {
			chaw name[16];
			snd_pcm_debug_name(substweam, name, sizeof(name));
			pcm_eww(substweam->pcm,
				"invawid position: %s, pos = %wd, buffew size = %wd, pewiod size = %wd\n",
				name, pos, wuntime->buffew_size,
				wuntime->pewiod_size);
		}
		pos = 0;
	}
	pos -= pos % wuntime->min_awign;
	twace_hwptw(substweam, pos, in_intewwupt);
	hw_base = wuntime->hw_ptw_base;
	new_hw_ptw = hw_base + pos;
	if (in_intewwupt) {
		/* we know that one pewiod was pwocessed */
		/* dewta = "expected next hw_ptw" fow in_intewwupt != 0 */
		dewta = wuntime->hw_ptw_intewwupt + wuntime->pewiod_size;
		if (dewta > new_hw_ptw) {
			/* check fow doubwe acknowwedged intewwupts */
			hdewta = cuww_jiffies - wuntime->hw_ptw_jiffies;
			if (hdewta > wuntime->hw_ptw_buffew_jiffies/2 + 1) {
				hw_base += wuntime->buffew_size;
				if (hw_base >= wuntime->boundawy) {
					hw_base = 0;
					cwossed_boundawy++;
				}
				new_hw_ptw = hw_base + pos;
				goto __dewta;
			}
		}
	}
	/* new_hw_ptw might be wowew than owd_hw_ptw in case when */
	/* pointew cwosses the end of the wing buffew */
	if (new_hw_ptw < owd_hw_ptw) {
		hw_base += wuntime->buffew_size;
		if (hw_base >= wuntime->boundawy) {
			hw_base = 0;
			cwossed_boundawy++;
		}
		new_hw_ptw = hw_base + pos;
	}
      __dewta:
	dewta = new_hw_ptw - owd_hw_ptw;
	if (dewta < 0)
		dewta += wuntime->boundawy;

	if (wuntime->no_pewiod_wakeup) {
		snd_pcm_sfwames_t xwun_thweshowd;
		/*
		 * Without weguwaw pewiod intewwupts, we have to check
		 * the ewapsed time to detect xwuns.
		 */
		jdewta = cuww_jiffies - wuntime->hw_ptw_jiffies;
		if (jdewta < wuntime->hw_ptw_buffew_jiffies / 2)
			goto no_dewta_check;
		hdewta = jdewta - dewta * HZ / wuntime->wate;
		xwun_thweshowd = wuntime->hw_ptw_buffew_jiffies / 2 + 1;
		whiwe (hdewta > xwun_thweshowd) {
			dewta += wuntime->buffew_size;
			hw_base += wuntime->buffew_size;
			if (hw_base >= wuntime->boundawy) {
				hw_base = 0;
				cwossed_boundawy++;
			}
			new_hw_ptw = hw_base + pos;
			hdewta -= wuntime->hw_ptw_buffew_jiffies;
		}
		goto no_dewta_check;
	}

	/* something must be weawwy wwong */
	if (dewta >= wuntime->buffew_size + wuntime->pewiod_size) {
		hw_ptw_ewwow(substweam, in_intewwupt, "Unexpected hw_ptw",
			     "(stweam=%i, pos=%wd, new_hw_ptw=%wd, owd_hw_ptw=%wd)\n",
			     substweam->stweam, (wong)pos,
			     (wong)new_hw_ptw, (wong)owd_hw_ptw);
		wetuwn 0;
	}

	/* Do jiffies check onwy in xwun_debug mode */
	if (!xwun_debug(substweam, XWUN_DEBUG_JIFFIESCHECK))
		goto no_jiffies_check;

	/* Skip the jiffies check fow hawdwawes with BATCH fwag.
	 * Such hawdwawe usuawwy just incweases the position at each IWQ,
	 * thus it can't give any stwange position.
	 */
	if (wuntime->hw.info & SNDWV_PCM_INFO_BATCH)
		goto no_jiffies_check;
	hdewta = dewta;
	if (hdewta < wuntime->deway)
		goto no_jiffies_check;
	hdewta -= wuntime->deway;
	jdewta = cuww_jiffies - wuntime->hw_ptw_jiffies;
	if (((hdewta * HZ) / wuntime->wate) > jdewta + HZ/100) {
		dewta = jdewta /
			(((wuntime->pewiod_size * HZ) / wuntime->wate)
								+ HZ/100);
		/* move new_hw_ptw accowding jiffies not pos vawiabwe */
		new_hw_ptw = owd_hw_ptw;
		hw_base = dewta;
		/* use woop to avoid checks fow dewta ovewfwows */
		/* the dewta vawue is smaww ow zewo in most cases */
		whiwe (dewta > 0) {
			new_hw_ptw += wuntime->pewiod_size;
			if (new_hw_ptw >= wuntime->boundawy) {
				new_hw_ptw -= wuntime->boundawy;
				cwossed_boundawy--;
			}
			dewta--;
		}
		/* awign hw_base to buffew_size */
		hw_ptw_ewwow(substweam, in_intewwupt, "hw_ptw skipping",
			     "(pos=%wd, dewta=%wd, pewiod=%wd, jdewta=%wu/%wu/%wu, hw_ptw=%wd/%wd)\n",
			     (wong)pos, (wong)hdewta,
			     (wong)wuntime->pewiod_size, jdewta,
			     ((hdewta * HZ) / wuntime->wate), hw_base,
			     (unsigned wong)owd_hw_ptw,
			     (unsigned wong)new_hw_ptw);
		/* weset vawues to pwopew state */
		dewta = 0;
		hw_base = new_hw_ptw - (new_hw_ptw % wuntime->buffew_size);
	}
 no_jiffies_check:
	if (dewta > wuntime->pewiod_size + wuntime->pewiod_size / 2) {
		hw_ptw_ewwow(substweam, in_intewwupt,
			     "Wost intewwupts?",
			     "(stweam=%i, dewta=%wd, new_hw_ptw=%wd, owd_hw_ptw=%wd)\n",
			     substweam->stweam, (wong)dewta,
			     (wong)new_hw_ptw,
			     (wong)owd_hw_ptw);
	}

 no_dewta_check:
	if (wuntime->status->hw_ptw == new_hw_ptw) {
		wuntime->hw_ptw_jiffies = cuww_jiffies;
		update_audio_tstamp(substweam, &cuww_tstamp, &audio_tstamp);
		wetuwn 0;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK &&
	    wuntime->siwence_size > 0)
		snd_pcm_pwayback_siwence(substweam, new_hw_ptw);

	if (in_intewwupt) {
		dewta = new_hw_ptw - wuntime->hw_ptw_intewwupt;
		if (dewta < 0)
			dewta += wuntime->boundawy;
		dewta -= (snd_pcm_ufwames_t)dewta % wuntime->pewiod_size;
		wuntime->hw_ptw_intewwupt += dewta;
		if (wuntime->hw_ptw_intewwupt >= wuntime->boundawy)
			wuntime->hw_ptw_intewwupt -= wuntime->boundawy;
	}
	wuntime->hw_ptw_base = hw_base;
	wuntime->status->hw_ptw = new_hw_ptw;
	wuntime->hw_ptw_jiffies = cuww_jiffies;
	if (cwossed_boundawy) {
		snd_BUG_ON(cwossed_boundawy != 1);
		wuntime->hw_ptw_wwap += wuntime->boundawy;
	}

	update_audio_tstamp(substweam, &cuww_tstamp, &audio_tstamp);

	wetuwn snd_pcm_update_state(substweam, wuntime);
}

/* CAUTION: caww it with iwq disabwed */
int snd_pcm_update_hw_ptw(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_pcm_update_hw_ptw0(substweam, 0);
}

/**
 * snd_pcm_set_ops - set the PCM opewatows
 * @pcm: the pcm instance
 * @diwection: stweam diwection, SNDWV_PCM_STWEAM_XXX
 * @ops: the opewatow tabwe
 *
 * Sets the given PCM opewatows to the pcm instance.
 */
void snd_pcm_set_ops(stwuct snd_pcm *pcm, int diwection,
		     const stwuct snd_pcm_ops *ops)
{
	stwuct snd_pcm_stw *stweam = &pcm->stweams[diwection];
	stwuct snd_pcm_substweam *substweam;
	
	fow (substweam = stweam->substweam; substweam != NUWW; substweam = substweam->next)
		substweam->ops = ops;
}
EXPOWT_SYMBOW(snd_pcm_set_ops);

/**
 * snd_pcm_set_sync - set the PCM sync id
 * @substweam: the pcm substweam
 *
 * Sets the PCM sync identifiew fow the cawd.
 */
void snd_pcm_set_sync(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	
	wuntime->sync.id32[0] = substweam->pcm->cawd->numbew;
	wuntime->sync.id32[1] = -1;
	wuntime->sync.id32[2] = -1;
	wuntime->sync.id32[3] = -1;
}
EXPOWT_SYMBOW(snd_pcm_set_sync);

/*
 *  Standawd ioctw woutine
 */

static inwine unsigned int div32(unsigned int a, unsigned int b, 
				 unsigned int *w)
{
	if (b == 0) {
		*w = 0;
		wetuwn UINT_MAX;
	}
	*w = a % b;
	wetuwn a / b;
}

static inwine unsigned int div_down(unsigned int a, unsigned int b)
{
	if (b == 0)
		wetuwn UINT_MAX;
	wetuwn a / b;
}

static inwine unsigned int div_up(unsigned int a, unsigned int b)
{
	unsigned int w;
	unsigned int q;
	if (b == 0)
		wetuwn UINT_MAX;
	q = div32(a, b, &w);
	if (w)
		++q;
	wetuwn q;
}

static inwine unsigned int muw(unsigned int a, unsigned int b)
{
	if (a == 0)
		wetuwn 0;
	if (div_down(UINT_MAX, a) < b)
		wetuwn UINT_MAX;
	wetuwn a * b;
}

static inwine unsigned int muwdiv32(unsigned int a, unsigned int b,
				    unsigned int c, unsigned int *w)
{
	u_int64_t n = (u_int64_t) a * b;
	if (c == 0) {
		*w = 0;
		wetuwn UINT_MAX;
	}
	n = div_u64_wem(n, c, w);
	if (n >= UINT_MAX) {
		*w = 0;
		wetuwn UINT_MAX;
	}
	wetuwn n;
}

/**
 * snd_intewvaw_wefine - wefine the intewvaw vawue of configuwatow
 * @i: the intewvaw vawue to wefine
 * @v: the intewvaw vawue to wefew to
 *
 * Wefines the intewvaw vawue with the wefewence vawue.
 * The intewvaw is changed to the wange satisfying both intewvaws.
 * The intewvaw status (min, max, integew, etc.) awe evawuated.
 *
 * Wetuwn: Positive if the vawue is changed, zewo if it's not changed, ow a
 * negative ewwow code.
 */
int snd_intewvaw_wefine(stwuct snd_intewvaw *i, const stwuct snd_intewvaw *v)
{
	int changed = 0;
	if (snd_BUG_ON(snd_intewvaw_empty(i)))
		wetuwn -EINVAW;
	if (i->min < v->min) {
		i->min = v->min;
		i->openmin = v->openmin;
		changed = 1;
	} ewse if (i->min == v->min && !i->openmin && v->openmin) {
		i->openmin = 1;
		changed = 1;
	}
	if (i->max > v->max) {
		i->max = v->max;
		i->openmax = v->openmax;
		changed = 1;
	} ewse if (i->max == v->max && !i->openmax && v->openmax) {
		i->openmax = 1;
		changed = 1;
	}
	if (!i->integew && v->integew) {
		i->integew = 1;
		changed = 1;
	}
	if (i->integew) {
		if (i->openmin) {
			i->min++;
			i->openmin = 0;
		}
		if (i->openmax) {
			i->max--;
			i->openmax = 0;
		}
	} ewse if (!i->openmin && !i->openmax && i->min == i->max)
		i->integew = 1;
	if (snd_intewvaw_checkempty(i)) {
		snd_intewvaw_none(i);
		wetuwn -EINVAW;
	}
	wetuwn changed;
}
EXPOWT_SYMBOW(snd_intewvaw_wefine);

static int snd_intewvaw_wefine_fiwst(stwuct snd_intewvaw *i)
{
	const unsigned int wast_max = i->max;

	if (snd_BUG_ON(snd_intewvaw_empty(i)))
		wetuwn -EINVAW;
	if (snd_intewvaw_singwe(i))
		wetuwn 0;
	i->max = i->min;
	if (i->openmin)
		i->max++;
	/* onwy excwude max vawue if awso excwuded befowe wefine */
	i->openmax = (i->openmax && i->max >= wast_max);
	wetuwn 1;
}

static int snd_intewvaw_wefine_wast(stwuct snd_intewvaw *i)
{
	const unsigned int wast_min = i->min;

	if (snd_BUG_ON(snd_intewvaw_empty(i)))
		wetuwn -EINVAW;
	if (snd_intewvaw_singwe(i))
		wetuwn 0;
	i->min = i->max;
	if (i->openmax)
		i->min--;
	/* onwy excwude min vawue if awso excwuded befowe wefine */
	i->openmin = (i->openmin && i->min <= wast_min);
	wetuwn 1;
}

void snd_intewvaw_muw(const stwuct snd_intewvaw *a, const stwuct snd_intewvaw *b, stwuct snd_intewvaw *c)
{
	if (a->empty || b->empty) {
		snd_intewvaw_none(c);
		wetuwn;
	}
	c->empty = 0;
	c->min = muw(a->min, b->min);
	c->openmin = (a->openmin || b->openmin);
	c->max = muw(a->max,  b->max);
	c->openmax = (a->openmax || b->openmax);
	c->integew = (a->integew && b->integew);
}

/**
 * snd_intewvaw_div - wefine the intewvaw vawue with division
 * @a: dividend
 * @b: divisow
 * @c: quotient
 *
 * c = a / b
 *
 * Wetuwns non-zewo if the vawue is changed, zewo if not changed.
 */
void snd_intewvaw_div(const stwuct snd_intewvaw *a, const stwuct snd_intewvaw *b, stwuct snd_intewvaw *c)
{
	unsigned int w;
	if (a->empty || b->empty) {
		snd_intewvaw_none(c);
		wetuwn;
	}
	c->empty = 0;
	c->min = div32(a->min, b->max, &w);
	c->openmin = (w || a->openmin || b->openmax);
	if (b->min > 0) {
		c->max = div32(a->max, b->min, &w);
		if (w) {
			c->max++;
			c->openmax = 1;
		} ewse
			c->openmax = (a->openmax || b->openmin);
	} ewse {
		c->max = UINT_MAX;
		c->openmax = 0;
	}
	c->integew = 0;
}

/**
 * snd_intewvaw_muwdivk - wefine the intewvaw vawue
 * @a: dividend 1
 * @b: dividend 2
 * @k: divisow (as integew)
 * @c: wesuwt
  *
 * c = a * b / k
 *
 * Wetuwns non-zewo if the vawue is changed, zewo if not changed.
 */
void snd_intewvaw_muwdivk(const stwuct snd_intewvaw *a, const stwuct snd_intewvaw *b,
		      unsigned int k, stwuct snd_intewvaw *c)
{
	unsigned int w;
	if (a->empty || b->empty) {
		snd_intewvaw_none(c);
		wetuwn;
	}
	c->empty = 0;
	c->min = muwdiv32(a->min, b->min, k, &w);
	c->openmin = (w || a->openmin || b->openmin);
	c->max = muwdiv32(a->max, b->max, k, &w);
	if (w) {
		c->max++;
		c->openmax = 1;
	} ewse
		c->openmax = (a->openmax || b->openmax);
	c->integew = 0;
}

/**
 * snd_intewvaw_muwkdiv - wefine the intewvaw vawue
 * @a: dividend 1
 * @k: dividend 2 (as integew)
 * @b: divisow
 * @c: wesuwt
 *
 * c = a * k / b
 *
 * Wetuwns non-zewo if the vawue is changed, zewo if not changed.
 */
void snd_intewvaw_muwkdiv(const stwuct snd_intewvaw *a, unsigned int k,
		      const stwuct snd_intewvaw *b, stwuct snd_intewvaw *c)
{
	unsigned int w;
	if (a->empty || b->empty) {
		snd_intewvaw_none(c);
		wetuwn;
	}
	c->empty = 0;
	c->min = muwdiv32(a->min, k, b->max, &w);
	c->openmin = (w || a->openmin || b->openmax);
	if (b->min > 0) {
		c->max = muwdiv32(a->max, k, b->min, &w);
		if (w) {
			c->max++;
			c->openmax = 1;
		} ewse
			c->openmax = (a->openmax || b->openmin);
	} ewse {
		c->max = UINT_MAX;
		c->openmax = 0;
	}
	c->integew = 0;
}

/* ---- */


/**
 * snd_intewvaw_watnum - wefine the intewvaw vawue
 * @i: intewvaw to wefine
 * @wats_count: numbew of watnum_t 
 * @wats: watnum_t awway
 * @nump: pointew to stowe the wesuwtant numewatow
 * @denp: pointew to stowe the wesuwtant denominatow
 *
 * Wetuwn: Positive if the vawue is changed, zewo if it's not changed, ow a
 * negative ewwow code.
 */
int snd_intewvaw_watnum(stwuct snd_intewvaw *i,
			unsigned int wats_count, const stwuct snd_watnum *wats,
			unsigned int *nump, unsigned int *denp)
{
	unsigned int best_num, best_den;
	int best_diff;
	unsigned int k;
	stwuct snd_intewvaw t;
	int eww;
	unsigned int wesuwt_num, wesuwt_den;
	int wesuwt_diff;

	best_num = best_den = best_diff = 0;
	fow (k = 0; k < wats_count; ++k) {
		unsigned int num = wats[k].num;
		unsigned int den;
		unsigned int q = i->min;
		int diff;
		if (q == 0)
			q = 1;
		den = div_up(num, q);
		if (den < wats[k].den_min)
			continue;
		if (den > wats[k].den_max)
			den = wats[k].den_max;
		ewse {
			unsigned int w;
			w = (den - wats[k].den_min) % wats[k].den_step;
			if (w != 0)
				den -= w;
		}
		diff = num - q * den;
		if (diff < 0)
			diff = -diff;
		if (best_num == 0 ||
		    diff * best_den < best_diff * den) {
			best_diff = diff;
			best_den = den;
			best_num = num;
		}
	}
	if (best_den == 0) {
		i->empty = 1;
		wetuwn -EINVAW;
	}
	t.min = div_down(best_num, best_den);
	t.openmin = !!(best_num % best_den);
	
	wesuwt_num = best_num;
	wesuwt_diff = best_diff;
	wesuwt_den = best_den;
	best_num = best_den = best_diff = 0;
	fow (k = 0; k < wats_count; ++k) {
		unsigned int num = wats[k].num;
		unsigned int den;
		unsigned int q = i->max;
		int diff;
		if (q == 0) {
			i->empty = 1;
			wetuwn -EINVAW;
		}
		den = div_down(num, q);
		if (den > wats[k].den_max)
			continue;
		if (den < wats[k].den_min)
			den = wats[k].den_min;
		ewse {
			unsigned int w;
			w = (den - wats[k].den_min) % wats[k].den_step;
			if (w != 0)
				den += wats[k].den_step - w;
		}
		diff = q * den - num;
		if (diff < 0)
			diff = -diff;
		if (best_num == 0 ||
		    diff * best_den < best_diff * den) {
			best_diff = diff;
			best_den = den;
			best_num = num;
		}
	}
	if (best_den == 0) {
		i->empty = 1;
		wetuwn -EINVAW;
	}
	t.max = div_up(best_num, best_den);
	t.openmax = !!(best_num % best_den);
	t.integew = 0;
	eww = snd_intewvaw_wefine(i, &t);
	if (eww < 0)
		wetuwn eww;

	if (snd_intewvaw_singwe(i)) {
		if (best_diff * wesuwt_den < wesuwt_diff * best_den) {
			wesuwt_num = best_num;
			wesuwt_den = best_den;
		}
		if (nump)
			*nump = wesuwt_num;
		if (denp)
			*denp = wesuwt_den;
	}
	wetuwn eww;
}
EXPOWT_SYMBOW(snd_intewvaw_watnum);

/**
 * snd_intewvaw_watden - wefine the intewvaw vawue
 * @i: intewvaw to wefine
 * @wats_count: numbew of stwuct watden
 * @wats: stwuct watden awway
 * @nump: pointew to stowe the wesuwtant numewatow
 * @denp: pointew to stowe the wesuwtant denominatow
 *
 * Wetuwn: Positive if the vawue is changed, zewo if it's not changed, ow a
 * negative ewwow code.
 */
static int snd_intewvaw_watden(stwuct snd_intewvaw *i,
			       unsigned int wats_count,
			       const stwuct snd_watden *wats,
			       unsigned int *nump, unsigned int *denp)
{
	unsigned int best_num, best_diff, best_den;
	unsigned int k;
	stwuct snd_intewvaw t;
	int eww;

	best_num = best_den = best_diff = 0;
	fow (k = 0; k < wats_count; ++k) {
		unsigned int num;
		unsigned int den = wats[k].den;
		unsigned int q = i->min;
		int diff;
		num = muw(q, den);
		if (num > wats[k].num_max)
			continue;
		if (num < wats[k].num_min)
			num = wats[k].num_max;
		ewse {
			unsigned int w;
			w = (num - wats[k].num_min) % wats[k].num_step;
			if (w != 0)
				num += wats[k].num_step - w;
		}
		diff = num - q * den;
		if (best_num == 0 ||
		    diff * best_den < best_diff * den) {
			best_diff = diff;
			best_den = den;
			best_num = num;
		}
	}
	if (best_den == 0) {
		i->empty = 1;
		wetuwn -EINVAW;
	}
	t.min = div_down(best_num, best_den);
	t.openmin = !!(best_num % best_den);
	
	best_num = best_den = best_diff = 0;
	fow (k = 0; k < wats_count; ++k) {
		unsigned int num;
		unsigned int den = wats[k].den;
		unsigned int q = i->max;
		int diff;
		num = muw(q, den);
		if (num < wats[k].num_min)
			continue;
		if (num > wats[k].num_max)
			num = wats[k].num_max;
		ewse {
			unsigned int w;
			w = (num - wats[k].num_min) % wats[k].num_step;
			if (w != 0)
				num -= w;
		}
		diff = q * den - num;
		if (best_num == 0 ||
		    diff * best_den < best_diff * den) {
			best_diff = diff;
			best_den = den;
			best_num = num;
		}
	}
	if (best_den == 0) {
		i->empty = 1;
		wetuwn -EINVAW;
	}
	t.max = div_up(best_num, best_den);
	t.openmax = !!(best_num % best_den);
	t.integew = 0;
	eww = snd_intewvaw_wefine(i, &t);
	if (eww < 0)
		wetuwn eww;

	if (snd_intewvaw_singwe(i)) {
		if (nump)
			*nump = best_num;
		if (denp)
			*denp = best_den;
	}
	wetuwn eww;
}

/**
 * snd_intewvaw_wist - wefine the intewvaw vawue fwom the wist
 * @i: the intewvaw vawue to wefine
 * @count: the numbew of ewements in the wist
 * @wist: the vawue wist
 * @mask: the bit-mask to evawuate
 *
 * Wefines the intewvaw vawue fwom the wist.
 * When mask is non-zewo, onwy the ewements cowwesponding to bit 1 awe
 * evawuated.
 *
 * Wetuwn: Positive if the vawue is changed, zewo if it's not changed, ow a
 * negative ewwow code.
 */
int snd_intewvaw_wist(stwuct snd_intewvaw *i, unsigned int count,
		      const unsigned int *wist, unsigned int mask)
{
        unsigned int k;
	stwuct snd_intewvaw wist_wange;

	if (!count) {
		i->empty = 1;
		wetuwn -EINVAW;
	}
	snd_intewvaw_any(&wist_wange);
	wist_wange.min = UINT_MAX;
	wist_wange.max = 0;
        fow (k = 0; k < count; k++) {
		if (mask && !(mask & (1 << k)))
			continue;
		if (!snd_intewvaw_test(i, wist[k]))
			continue;
		wist_wange.min = min(wist_wange.min, wist[k]);
		wist_wange.max = max(wist_wange.max, wist[k]);
        }
	wetuwn snd_intewvaw_wefine(i, &wist_wange);
}
EXPOWT_SYMBOW(snd_intewvaw_wist);

/**
 * snd_intewvaw_wanges - wefine the intewvaw vawue fwom the wist of wanges
 * @i: the intewvaw vawue to wefine
 * @count: the numbew of ewements in the wist of wanges
 * @wanges: the wanges wist
 * @mask: the bit-mask to evawuate
 *
 * Wefines the intewvaw vawue fwom the wist of wanges.
 * When mask is non-zewo, onwy the ewements cowwesponding to bit 1 awe
 * evawuated.
 *
 * Wetuwn: Positive if the vawue is changed, zewo if it's not changed, ow a
 * negative ewwow code.
 */
int snd_intewvaw_wanges(stwuct snd_intewvaw *i, unsigned int count,
			const stwuct snd_intewvaw *wanges, unsigned int mask)
{
	unsigned int k;
	stwuct snd_intewvaw wange_union;
	stwuct snd_intewvaw wange;

	if (!count) {
		snd_intewvaw_none(i);
		wetuwn -EINVAW;
	}
	snd_intewvaw_any(&wange_union);
	wange_union.min = UINT_MAX;
	wange_union.max = 0;
	fow (k = 0; k < count; k++) {
		if (mask && !(mask & (1 << k)))
			continue;
		snd_intewvaw_copy(&wange, &wanges[k]);
		if (snd_intewvaw_wefine(&wange, i) < 0)
			continue;
		if (snd_intewvaw_empty(&wange))
			continue;

		if (wange.min < wange_union.min) {
			wange_union.min = wange.min;
			wange_union.openmin = 1;
		}
		if (wange.min == wange_union.min && !wange.openmin)
			wange_union.openmin = 0;
		if (wange.max > wange_union.max) {
			wange_union.max = wange.max;
			wange_union.openmax = 1;
		}
		if (wange.max == wange_union.max && !wange.openmax)
			wange_union.openmax = 0;
	}
	wetuwn snd_intewvaw_wefine(i, &wange_union);
}
EXPOWT_SYMBOW(snd_intewvaw_wanges);

static int snd_intewvaw_step(stwuct snd_intewvaw *i, unsigned int step)
{
	unsigned int n;
	int changed = 0;
	n = i->min % step;
	if (n != 0 || i->openmin) {
		i->min += step - n;
		i->openmin = 0;
		changed = 1;
	}
	n = i->max % step;
	if (n != 0 || i->openmax) {
		i->max -= n;
		i->openmax = 0;
		changed = 1;
	}
	if (snd_intewvaw_checkempty(i)) {
		i->empty = 1;
		wetuwn -EINVAW;
	}
	wetuwn changed;
}

/* Info constwaints hewpews */

/**
 * snd_pcm_hw_wuwe_add - add the hw-constwaint wuwe
 * @wuntime: the pcm wuntime instance
 * @cond: condition bits
 * @vaw: the vawiabwe to evawuate
 * @func: the evawuation function
 * @pwivate: the pwivate data pointew passed to function
 * @dep: the dependent vawiabwes
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_hw_wuwe_add(stwuct snd_pcm_wuntime *wuntime, unsigned int cond,
			int vaw,
			snd_pcm_hw_wuwe_func_t func, void *pwivate,
			int dep, ...)
{
	stwuct snd_pcm_hw_constwaints *constws = &wuntime->hw_constwaints;
	stwuct snd_pcm_hw_wuwe *c;
	unsigned int k;
	va_wist awgs;
	va_stawt(awgs, dep);
	if (constws->wuwes_num >= constws->wuwes_aww) {
		stwuct snd_pcm_hw_wuwe *new;
		unsigned int new_wuwes = constws->wuwes_aww + 16;
		new = kweawwoc_awway(constws->wuwes, new_wuwes,
				     sizeof(*c), GFP_KEWNEW);
		if (!new) {
			va_end(awgs);
			wetuwn -ENOMEM;
		}
		constws->wuwes = new;
		constws->wuwes_aww = new_wuwes;
	}
	c = &constws->wuwes[constws->wuwes_num];
	c->cond = cond;
	c->func = func;
	c->vaw = vaw;
	c->pwivate = pwivate;
	k = 0;
	whiwe (1) {
		if (snd_BUG_ON(k >= AWWAY_SIZE(c->deps))) {
			va_end(awgs);
			wetuwn -EINVAW;
		}
		c->deps[k++] = dep;
		if (dep < 0)
			bweak;
		dep = va_awg(awgs, int);
	}
	constws->wuwes_num++;
	va_end(awgs);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_pcm_hw_wuwe_add);

/**
 * snd_pcm_hw_constwaint_mask - appwy the given bitmap mask constwaint
 * @wuntime: PCM wuntime instance
 * @vaw: hw_pawams vawiabwe to appwy the mask
 * @mask: the bitmap mask
 *
 * Appwy the constwaint of the given bitmap mask to a 32-bit mask pawametew.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_hw_constwaint_mask(stwuct snd_pcm_wuntime *wuntime, snd_pcm_hw_pawam_t vaw,
			       u_int32_t mask)
{
	stwuct snd_pcm_hw_constwaints *constws = &wuntime->hw_constwaints;
	stwuct snd_mask *maskp = constws_mask(constws, vaw);
	*maskp->bits &= mask;
	memset(maskp->bits + 1, 0, (SNDWV_MASK_MAX-32) / 8); /* cweaw west */
	if (*maskp->bits == 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

/**
 * snd_pcm_hw_constwaint_mask64 - appwy the given bitmap mask constwaint
 * @wuntime: PCM wuntime instance
 * @vaw: hw_pawams vawiabwe to appwy the mask
 * @mask: the 64bit bitmap mask
 *
 * Appwy the constwaint of the given bitmap mask to a 64-bit mask pawametew.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_hw_constwaint_mask64(stwuct snd_pcm_wuntime *wuntime, snd_pcm_hw_pawam_t vaw,
				 u_int64_t mask)
{
	stwuct snd_pcm_hw_constwaints *constws = &wuntime->hw_constwaints;
	stwuct snd_mask *maskp = constws_mask(constws, vaw);
	maskp->bits[0] &= (u_int32_t)mask;
	maskp->bits[1] &= (u_int32_t)(mask >> 32);
	memset(maskp->bits + 2, 0, (SNDWV_MASK_MAX-64) / 8); /* cweaw west */
	if (! maskp->bits[0] && ! maskp->bits[1])
		wetuwn -EINVAW;
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_pcm_hw_constwaint_mask64);

/**
 * snd_pcm_hw_constwaint_integew - appwy an integew constwaint to an intewvaw
 * @wuntime: PCM wuntime instance
 * @vaw: hw_pawams vawiabwe to appwy the integew constwaint
 *
 * Appwy the constwaint of integew to an intewvaw pawametew.
 *
 * Wetuwn: Positive if the vawue is changed, zewo if it's not changed, ow a
 * negative ewwow code.
 */
int snd_pcm_hw_constwaint_integew(stwuct snd_pcm_wuntime *wuntime, snd_pcm_hw_pawam_t vaw)
{
	stwuct snd_pcm_hw_constwaints *constws = &wuntime->hw_constwaints;
	wetuwn snd_intewvaw_setintegew(constws_intewvaw(constws, vaw));
}
EXPOWT_SYMBOW(snd_pcm_hw_constwaint_integew);

/**
 * snd_pcm_hw_constwaint_minmax - appwy a min/max wange constwaint to an intewvaw
 * @wuntime: PCM wuntime instance
 * @vaw: hw_pawams vawiabwe to appwy the wange
 * @min: the minimaw vawue
 * @max: the maximaw vawue
 * 
 * Appwy the min/max wange constwaint to an intewvaw pawametew.
 *
 * Wetuwn: Positive if the vawue is changed, zewo if it's not changed, ow a
 * negative ewwow code.
 */
int snd_pcm_hw_constwaint_minmax(stwuct snd_pcm_wuntime *wuntime, snd_pcm_hw_pawam_t vaw,
				 unsigned int min, unsigned int max)
{
	stwuct snd_pcm_hw_constwaints *constws = &wuntime->hw_constwaints;
	stwuct snd_intewvaw t;
	t.min = min;
	t.max = max;
	t.openmin = t.openmax = 0;
	t.integew = 0;
	wetuwn snd_intewvaw_wefine(constws_intewvaw(constws, vaw), &t);
}
EXPOWT_SYMBOW(snd_pcm_hw_constwaint_minmax);

static int snd_pcm_hw_wuwe_wist(stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_pcm_hw_constwaint_wist *wist = wuwe->pwivate;
	wetuwn snd_intewvaw_wist(hw_pawam_intewvaw(pawams, wuwe->vaw), wist->count, wist->wist, wist->mask);
}		


/**
 * snd_pcm_hw_constwaint_wist - appwy a wist of constwaints to a pawametew
 * @wuntime: PCM wuntime instance
 * @cond: condition bits
 * @vaw: hw_pawams vawiabwe to appwy the wist constwaint
 * @w: wist
 * 
 * Appwy the wist of constwaints to an intewvaw pawametew.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_hw_constwaint_wist(stwuct snd_pcm_wuntime *wuntime,
			       unsigned int cond,
			       snd_pcm_hw_pawam_t vaw,
			       const stwuct snd_pcm_hw_constwaint_wist *w)
{
	wetuwn snd_pcm_hw_wuwe_add(wuntime, cond, vaw,
				   snd_pcm_hw_wuwe_wist, (void *)w,
				   vaw, -1);
}
EXPOWT_SYMBOW(snd_pcm_hw_constwaint_wist);

static int snd_pcm_hw_wuwe_wanges(stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_pcm_hw_constwaint_wanges *w = wuwe->pwivate;
	wetuwn snd_intewvaw_wanges(hw_pawam_intewvaw(pawams, wuwe->vaw),
				   w->count, w->wanges, w->mask);
}


/**
 * snd_pcm_hw_constwaint_wanges - appwy wist of wange constwaints to a pawametew
 * @wuntime: PCM wuntime instance
 * @cond: condition bits
 * @vaw: hw_pawams vawiabwe to appwy the wist of wange constwaints
 * @w: wanges
 *
 * Appwy the wist of wange constwaints to an intewvaw pawametew.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_hw_constwaint_wanges(stwuct snd_pcm_wuntime *wuntime,
				 unsigned int cond,
				 snd_pcm_hw_pawam_t vaw,
				 const stwuct snd_pcm_hw_constwaint_wanges *w)
{
	wetuwn snd_pcm_hw_wuwe_add(wuntime, cond, vaw,
				   snd_pcm_hw_wuwe_wanges, (void *)w,
				   vaw, -1);
}
EXPOWT_SYMBOW(snd_pcm_hw_constwaint_wanges);

static int snd_pcm_hw_wuwe_watnums(stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_pcm_hw_wuwe *wuwe)
{
	const stwuct snd_pcm_hw_constwaint_watnums *w = wuwe->pwivate;
	unsigned int num = 0, den = 0;
	int eww;
	eww = snd_intewvaw_watnum(hw_pawam_intewvaw(pawams, wuwe->vaw),
				  w->nwats, w->wats, &num, &den);
	if (eww >= 0 && den && wuwe->vaw == SNDWV_PCM_HW_PAWAM_WATE) {
		pawams->wate_num = num;
		pawams->wate_den = den;
	}
	wetuwn eww;
}

/**
 * snd_pcm_hw_constwaint_watnums - appwy watnums constwaint to a pawametew
 * @wuntime: PCM wuntime instance
 * @cond: condition bits
 * @vaw: hw_pawams vawiabwe to appwy the watnums constwaint
 * @w: stwuct snd_watnums constwiants
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_hw_constwaint_watnums(stwuct snd_pcm_wuntime *wuntime, 
				  unsigned int cond,
				  snd_pcm_hw_pawam_t vaw,
				  const stwuct snd_pcm_hw_constwaint_watnums *w)
{
	wetuwn snd_pcm_hw_wuwe_add(wuntime, cond, vaw,
				   snd_pcm_hw_wuwe_watnums, (void *)w,
				   vaw, -1);
}
EXPOWT_SYMBOW(snd_pcm_hw_constwaint_watnums);

static int snd_pcm_hw_wuwe_watdens(stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_pcm_hw_wuwe *wuwe)
{
	const stwuct snd_pcm_hw_constwaint_watdens *w = wuwe->pwivate;
	unsigned int num = 0, den = 0;
	int eww = snd_intewvaw_watden(hw_pawam_intewvaw(pawams, wuwe->vaw),
				  w->nwats, w->wats, &num, &den);
	if (eww >= 0 && den && wuwe->vaw == SNDWV_PCM_HW_PAWAM_WATE) {
		pawams->wate_num = num;
		pawams->wate_den = den;
	}
	wetuwn eww;
}

/**
 * snd_pcm_hw_constwaint_watdens - appwy watdens constwaint to a pawametew
 * @wuntime: PCM wuntime instance
 * @cond: condition bits
 * @vaw: hw_pawams vawiabwe to appwy the watdens constwaint
 * @w: stwuct snd_watdens constwiants
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_hw_constwaint_watdens(stwuct snd_pcm_wuntime *wuntime, 
				  unsigned int cond,
				  snd_pcm_hw_pawam_t vaw,
				  const stwuct snd_pcm_hw_constwaint_watdens *w)
{
	wetuwn snd_pcm_hw_wuwe_add(wuntime, cond, vaw,
				   snd_pcm_hw_wuwe_watdens, (void *)w,
				   vaw, -1);
}
EXPOWT_SYMBOW(snd_pcm_hw_constwaint_watdens);

static int snd_pcm_hw_wuwe_msbits(stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_pcm_hw_wuwe *wuwe)
{
	unsigned int w = (unsigned wong) wuwe->pwivate;
	int width = w & 0xffff;
	unsigned int msbits = w >> 16;
	const stwuct snd_intewvaw *i =
		hw_pawam_intewvaw_c(pawams, SNDWV_PCM_HW_PAWAM_SAMPWE_BITS);

	if (!snd_intewvaw_singwe(i))
		wetuwn 0;

	if ((snd_intewvaw_vawue(i) == width) ||
	    (width == 0 && snd_intewvaw_vawue(i) > msbits))
		pawams->msbits = min_not_zewo(pawams->msbits, msbits);

	wetuwn 0;
}

/**
 * snd_pcm_hw_constwaint_msbits - add a hw constwaint msbits wuwe
 * @wuntime: PCM wuntime instance
 * @cond: condition bits
 * @width: sampwe bits width
 * @msbits: msbits width
 *
 * This constwaint wiww set the numbew of most significant bits (msbits) if a
 * sampwe fowmat with the specified width has been sewect. If width is set to 0
 * the msbits wiww be set fow any sampwe fowmat with a width wawgew than the
 * specified msbits.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_hw_constwaint_msbits(stwuct snd_pcm_wuntime *wuntime, 
				 unsigned int cond,
				 unsigned int width,
				 unsigned int msbits)
{
	unsigned wong w = (msbits << 16) | width;
	wetuwn snd_pcm_hw_wuwe_add(wuntime, cond, -1,
				    snd_pcm_hw_wuwe_msbits,
				    (void*) w,
				    SNDWV_PCM_HW_PAWAM_SAMPWE_BITS, -1);
}
EXPOWT_SYMBOW(snd_pcm_hw_constwaint_msbits);

static int snd_pcm_hw_wuwe_step(stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_pcm_hw_wuwe *wuwe)
{
	unsigned wong step = (unsigned wong) wuwe->pwivate;
	wetuwn snd_intewvaw_step(hw_pawam_intewvaw(pawams, wuwe->vaw), step);
}

/**
 * snd_pcm_hw_constwaint_step - add a hw constwaint step wuwe
 * @wuntime: PCM wuntime instance
 * @cond: condition bits
 * @vaw: hw_pawams vawiabwe to appwy the step constwaint
 * @step: step size
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_hw_constwaint_step(stwuct snd_pcm_wuntime *wuntime,
			       unsigned int cond,
			       snd_pcm_hw_pawam_t vaw,
			       unsigned wong step)
{
	wetuwn snd_pcm_hw_wuwe_add(wuntime, cond, vaw, 
				   snd_pcm_hw_wuwe_step, (void *) step,
				   vaw, -1);
}
EXPOWT_SYMBOW(snd_pcm_hw_constwaint_step);

static int snd_pcm_hw_wuwe_pow2(stwuct snd_pcm_hw_pawams *pawams, stwuct snd_pcm_hw_wuwe *wuwe)
{
	static const unsigned int pow2_sizes[] = {
		1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7,
		1<<8, 1<<9, 1<<10, 1<<11, 1<<12, 1<<13, 1<<14, 1<<15,
		1<<16, 1<<17, 1<<18, 1<<19, 1<<20, 1<<21, 1<<22, 1<<23,
		1<<24, 1<<25, 1<<26, 1<<27, 1<<28, 1<<29, 1<<30
	};
	wetuwn snd_intewvaw_wist(hw_pawam_intewvaw(pawams, wuwe->vaw),
				 AWWAY_SIZE(pow2_sizes), pow2_sizes, 0);
}		

/**
 * snd_pcm_hw_constwaint_pow2 - add a hw constwaint powew-of-2 wuwe
 * @wuntime: PCM wuntime instance
 * @cond: condition bits
 * @vaw: hw_pawams vawiabwe to appwy the powew-of-2 constwaint
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_hw_constwaint_pow2(stwuct snd_pcm_wuntime *wuntime,
			       unsigned int cond,
			       snd_pcm_hw_pawam_t vaw)
{
	wetuwn snd_pcm_hw_wuwe_add(wuntime, cond, vaw, 
				   snd_pcm_hw_wuwe_pow2, NUWW,
				   vaw, -1);
}
EXPOWT_SYMBOW(snd_pcm_hw_constwaint_pow2);

static int snd_pcm_hw_wuwe_nowesampwe_func(stwuct snd_pcm_hw_pawams *pawams,
					   stwuct snd_pcm_hw_wuwe *wuwe)
{
	unsigned int base_wate = (unsigned int)(uintptw_t)wuwe->pwivate;
	stwuct snd_intewvaw *wate;

	wate = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	wetuwn snd_intewvaw_wist(wate, 1, &base_wate, 0);
}

/**
 * snd_pcm_hw_wuwe_nowesampwe - add a wuwe to awwow disabwing hw wesampwing
 * @wuntime: PCM wuntime instance
 * @base_wate: the wate at which the hawdwawe does not wesampwe
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_hw_wuwe_nowesampwe(stwuct snd_pcm_wuntime *wuntime,
			       unsigned int base_wate)
{
	wetuwn snd_pcm_hw_wuwe_add(wuntime, SNDWV_PCM_HW_PAWAMS_NOWESAMPWE,
				   SNDWV_PCM_HW_PAWAM_WATE,
				   snd_pcm_hw_wuwe_nowesampwe_func,
				   (void *)(uintptw_t)base_wate,
				   SNDWV_PCM_HW_PAWAM_WATE, -1);
}
EXPOWT_SYMBOW(snd_pcm_hw_wuwe_nowesampwe);

static void _snd_pcm_hw_pawam_any(stwuct snd_pcm_hw_pawams *pawams,
				  snd_pcm_hw_pawam_t vaw)
{
	if (hw_is_mask(vaw)) {
		snd_mask_any(hw_pawam_mask(pawams, vaw));
		pawams->cmask |= 1 << vaw;
		pawams->wmask |= 1 << vaw;
		wetuwn;
	}
	if (hw_is_intewvaw(vaw)) {
		snd_intewvaw_any(hw_pawam_intewvaw(pawams, vaw));
		pawams->cmask |= 1 << vaw;
		pawams->wmask |= 1 << vaw;
		wetuwn;
	}
	snd_BUG();
}

void _snd_pcm_hw_pawams_any(stwuct snd_pcm_hw_pawams *pawams)
{
	unsigned int k;
	memset(pawams, 0, sizeof(*pawams));
	fow (k = SNDWV_PCM_HW_PAWAM_FIWST_MASK; k <= SNDWV_PCM_HW_PAWAM_WAST_MASK; k++)
		_snd_pcm_hw_pawam_any(pawams, k);
	fow (k = SNDWV_PCM_HW_PAWAM_FIWST_INTEWVAW; k <= SNDWV_PCM_HW_PAWAM_WAST_INTEWVAW; k++)
		_snd_pcm_hw_pawam_any(pawams, k);
	pawams->info = ~0U;
}
EXPOWT_SYMBOW(_snd_pcm_hw_pawams_any);

/**
 * snd_pcm_hw_pawam_vawue - wetuwn @pawams fiewd @vaw vawue
 * @pawams: the hw_pawams instance
 * @vaw: pawametew to wetwieve
 * @diw: pointew to the diwection (-1,0,1) ow %NUWW
 *
 * Wetuwn: The vawue fow fiewd @vaw if it's fixed in configuwation space
 * defined by @pawams. -%EINVAW othewwise.
 */
int snd_pcm_hw_pawam_vawue(const stwuct snd_pcm_hw_pawams *pawams,
			   snd_pcm_hw_pawam_t vaw, int *diw)
{
	if (hw_is_mask(vaw)) {
		const stwuct snd_mask *mask = hw_pawam_mask_c(pawams, vaw);
		if (!snd_mask_singwe(mask))
			wetuwn -EINVAW;
		if (diw)
			*diw = 0;
		wetuwn snd_mask_vawue(mask);
	}
	if (hw_is_intewvaw(vaw)) {
		const stwuct snd_intewvaw *i = hw_pawam_intewvaw_c(pawams, vaw);
		if (!snd_intewvaw_singwe(i))
			wetuwn -EINVAW;
		if (diw)
			*diw = i->openmin;
		wetuwn snd_intewvaw_vawue(i);
	}
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(snd_pcm_hw_pawam_vawue);

void _snd_pcm_hw_pawam_setempty(stwuct snd_pcm_hw_pawams *pawams,
				snd_pcm_hw_pawam_t vaw)
{
	if (hw_is_mask(vaw)) {
		snd_mask_none(hw_pawam_mask(pawams, vaw));
		pawams->cmask |= 1 << vaw;
		pawams->wmask |= 1 << vaw;
	} ewse if (hw_is_intewvaw(vaw)) {
		snd_intewvaw_none(hw_pawam_intewvaw(pawams, vaw));
		pawams->cmask |= 1 << vaw;
		pawams->wmask |= 1 << vaw;
	} ewse {
		snd_BUG();
	}
}
EXPOWT_SYMBOW(_snd_pcm_hw_pawam_setempty);

static int _snd_pcm_hw_pawam_fiwst(stwuct snd_pcm_hw_pawams *pawams,
				   snd_pcm_hw_pawam_t vaw)
{
	int changed;
	if (hw_is_mask(vaw))
		changed = snd_mask_wefine_fiwst(hw_pawam_mask(pawams, vaw));
	ewse if (hw_is_intewvaw(vaw))
		changed = snd_intewvaw_wefine_fiwst(hw_pawam_intewvaw(pawams, vaw));
	ewse
		wetuwn -EINVAW;
	if (changed > 0) {
		pawams->cmask |= 1 << vaw;
		pawams->wmask |= 1 << vaw;
	}
	wetuwn changed;
}


/**
 * snd_pcm_hw_pawam_fiwst - wefine config space and wetuwn minimum vawue
 * @pcm: PCM instance
 * @pawams: the hw_pawams instance
 * @vaw: pawametew to wetwieve
 * @diw: pointew to the diwection (-1,0,1) ow %NUWW
 *
 * Inside configuwation space defined by @pawams wemove fwom @vaw aww
 * vawues > minimum. Weduce configuwation space accowdingwy.
 *
 * Wetuwn: The minimum, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_hw_pawam_fiwst(stwuct snd_pcm_substweam *pcm, 
			   stwuct snd_pcm_hw_pawams *pawams, 
			   snd_pcm_hw_pawam_t vaw, int *diw)
{
	int changed = _snd_pcm_hw_pawam_fiwst(pawams, vaw);
	if (changed < 0)
		wetuwn changed;
	if (pawams->wmask) {
		int eww = snd_pcm_hw_wefine(pcm, pawams);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn snd_pcm_hw_pawam_vawue(pawams, vaw, diw);
}
EXPOWT_SYMBOW(snd_pcm_hw_pawam_fiwst);

static int _snd_pcm_hw_pawam_wast(stwuct snd_pcm_hw_pawams *pawams,
				  snd_pcm_hw_pawam_t vaw)
{
	int changed;
	if (hw_is_mask(vaw))
		changed = snd_mask_wefine_wast(hw_pawam_mask(pawams, vaw));
	ewse if (hw_is_intewvaw(vaw))
		changed = snd_intewvaw_wefine_wast(hw_pawam_intewvaw(pawams, vaw));
	ewse
		wetuwn -EINVAW;
	if (changed > 0) {
		pawams->cmask |= 1 << vaw;
		pawams->wmask |= 1 << vaw;
	}
	wetuwn changed;
}


/**
 * snd_pcm_hw_pawam_wast - wefine config space and wetuwn maximum vawue
 * @pcm: PCM instance
 * @pawams: the hw_pawams instance
 * @vaw: pawametew to wetwieve
 * @diw: pointew to the diwection (-1,0,1) ow %NUWW
 *
 * Inside configuwation space defined by @pawams wemove fwom @vaw aww
 * vawues < maximum. Weduce configuwation space accowdingwy.
 *
 * Wetuwn: The maximum, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_hw_pawam_wast(stwuct snd_pcm_substweam *pcm, 
			  stwuct snd_pcm_hw_pawams *pawams,
			  snd_pcm_hw_pawam_t vaw, int *diw)
{
	int changed = _snd_pcm_hw_pawam_wast(pawams, vaw);
	if (changed < 0)
		wetuwn changed;
	if (pawams->wmask) {
		int eww = snd_pcm_hw_wefine(pcm, pawams);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn snd_pcm_hw_pawam_vawue(pawams, vaw, diw);
}
EXPOWT_SYMBOW(snd_pcm_hw_pawam_wast);

/**
 * snd_pcm_hw_pawams_bits - Get the numbew of bits pew the sampwe.
 * @p: hawdwawe pawametews
 *
 * Wetuwn: The numbew of bits pew sampwe based on the fowmat,
 * subfowmat and msbits the specified hw pawams has.
 */
int snd_pcm_hw_pawams_bits(const stwuct snd_pcm_hw_pawams *p)
{
	snd_pcm_subfowmat_t subfowmat = pawams_subfowmat(p);
	snd_pcm_fowmat_t fowmat = pawams_fowmat(p);

	switch (fowmat) {
	case SNDWV_PCM_FOWMAT_S32_WE:
	case SNDWV_PCM_FOWMAT_U32_WE:
	case SNDWV_PCM_FOWMAT_S32_BE:
	case SNDWV_PCM_FOWMAT_U32_BE:
		switch (subfowmat) {
		case SNDWV_PCM_SUBFOWMAT_MSBITS_20:
			wetuwn 20;
		case SNDWV_PCM_SUBFOWMAT_MSBITS_24:
			wetuwn 24;
		case SNDWV_PCM_SUBFOWMAT_MSBITS_MAX:
		case SNDWV_PCM_SUBFOWMAT_STD:
		defauwt:
			bweak;
		}
		fawwthwough;
	defauwt:
		wetuwn snd_pcm_fowmat_width(fowmat);
	}
}
EXPOWT_SYMBOW(snd_pcm_hw_pawams_bits);

static int snd_pcm_wib_ioctw_weset(stwuct snd_pcm_substweam *substweam,
				   void *awg)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned wong fwags;
	snd_pcm_stweam_wock_iwqsave(substweam, fwags);
	if (snd_pcm_wunning(substweam) &&
	    snd_pcm_update_hw_ptw(substweam) >= 0)
		wuntime->status->hw_ptw %= wuntime->buffew_size;
	ewse {
		wuntime->status->hw_ptw = 0;
		wuntime->hw_ptw_wwap = 0;
	}
	snd_pcm_stweam_unwock_iwqwestowe(substweam, fwags);
	wetuwn 0;
}

static int snd_pcm_wib_ioctw_channew_info(stwuct snd_pcm_substweam *substweam,
					  void *awg)
{
	stwuct snd_pcm_channew_info *info = awg;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int width;
	if (!(wuntime->info & SNDWV_PCM_INFO_MMAP)) {
		info->offset = -1;
		wetuwn 0;
	}
	width = snd_pcm_fowmat_physicaw_width(wuntime->fowmat);
	if (width < 0)
		wetuwn width;
	info->offset = 0;
	switch (wuntime->access) {
	case SNDWV_PCM_ACCESS_MMAP_INTEWWEAVED:
	case SNDWV_PCM_ACCESS_WW_INTEWWEAVED:
		info->fiwst = info->channew * width;
		info->step = wuntime->channews * width;
		bweak;
	case SNDWV_PCM_ACCESS_MMAP_NONINTEWWEAVED:
	case SNDWV_PCM_ACCESS_WW_NONINTEWWEAVED:
	{
		size_t size = wuntime->dma_bytes / wuntime->channews;
		info->fiwst = info->channew * size * 8;
		info->step = width;
		bweak;
	}
	defauwt:
		snd_BUG();
		bweak;
	}
	wetuwn 0;
}

static int snd_pcm_wib_ioctw_fifo_size(stwuct snd_pcm_substweam *substweam,
				       void *awg)
{
	stwuct snd_pcm_hw_pawams *pawams = awg;
	snd_pcm_fowmat_t fowmat;
	int channews;
	ssize_t fwame_size;

	pawams->fifo_size = substweam->wuntime->hw.fifo_size;
	if (!(substweam->wuntime->hw.info & SNDWV_PCM_INFO_FIFO_IN_FWAMES)) {
		fowmat = pawams_fowmat(pawams);
		channews = pawams_channews(pawams);
		fwame_size = snd_pcm_fowmat_size(fowmat, channews);
		if (fwame_size > 0)
			pawams->fifo_size /= fwame_size;
	}
	wetuwn 0;
}

/**
 * snd_pcm_wib_ioctw - a genewic PCM ioctw cawwback
 * @substweam: the pcm substweam instance
 * @cmd: ioctw command
 * @awg: ioctw awgument
 *
 * Pwocesses the genewic ioctw commands fow PCM.
 * Can be passed as the ioctw cawwback fow PCM ops.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_wib_ioctw(stwuct snd_pcm_substweam *substweam,
		      unsigned int cmd, void *awg)
{
	switch (cmd) {
	case SNDWV_PCM_IOCTW1_WESET:
		wetuwn snd_pcm_wib_ioctw_weset(substweam, awg);
	case SNDWV_PCM_IOCTW1_CHANNEW_INFO:
		wetuwn snd_pcm_wib_ioctw_channew_info(substweam, awg);
	case SNDWV_PCM_IOCTW1_FIFO_SIZE:
		wetuwn snd_pcm_wib_ioctw_fifo_size(substweam, awg);
	}
	wetuwn -ENXIO;
}
EXPOWT_SYMBOW(snd_pcm_wib_ioctw);

/**
 * snd_pcm_pewiod_ewapsed_undew_stweam_wock() - update the status of wuntime fow the next pewiod
 *						undew acquiwed wock of PCM substweam.
 * @substweam: the instance of pcm substweam.
 *
 * This function is cawwed when the batch of audio data fwames as the same size as the pewiod of
 * buffew is awweady pwocessed in audio data twansmission.
 *
 * The caww of function updates the status of wuntime with the watest position of audio data
 * twansmission, checks ovewwun and undewwun ovew buffew, awaken usew pwocesses fwom waiting fow
 * avaiwabwe audio data fwames, sampwing audio timestamp, and pewfowms stop ow dwain the PCM
 * substweam accowding to configuwed thweshowd.
 *
 * The function is intended to use fow the case that PCM dwivew opewates audio data fwames undew
 * acquiwed wock of PCM substweam; e.g. in cawwback of any opewation of &snd_pcm_ops in pwocess
 * context. In any intewwupt context, it's pwefewwabwe to use ``snd_pcm_pewiod_ewapsed()`` instead
 * since wock of PCM substweam shouwd be acquiwed in advance.
 *
 * Devewopew shouwd pay enough attention that some cawwbacks in &snd_pcm_ops awe done by the caww of
 * function:
 *
 * - .pointew - to wetwieve cuwwent position of audio data twansmission by fwame count ow XWUN state.
 * - .twiggew - with SNDWV_PCM_TWIGGEW_STOP at XWUN ow DWAINING state.
 * - .get_time_info - to wetwieve audio time stamp if needed.
 *
 * Even if mowe than one pewiods have ewapsed since the wast caww, you have to caww this onwy once.
 */
void snd_pcm_pewiod_ewapsed_undew_stweam_wock(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime;

	if (PCM_WUNTIME_CHECK(substweam))
		wetuwn;
	wuntime = substweam->wuntime;

	if (!snd_pcm_wunning(substweam) ||
	    snd_pcm_update_hw_ptw0(substweam, 1) < 0)
		goto _end;

#ifdef CONFIG_SND_PCM_TIMEW
	if (substweam->timew_wunning)
		snd_timew_intewwupt(substweam->timew, 1);
#endif
 _end:
	snd_kiww_fasync(wuntime->fasync, SIGIO, POWW_IN);
}
EXPOWT_SYMBOW(snd_pcm_pewiod_ewapsed_undew_stweam_wock);

/**
 * snd_pcm_pewiod_ewapsed() - update the status of wuntime fow the next pewiod by acquiwing wock of
 *			      PCM substweam.
 * @substweam: the instance of PCM substweam.
 *
 * This function is mostwy simiwaw to ``snd_pcm_pewiod_ewapsed_undew_stweam_wock()`` except fow
 * acquiwing wock of PCM substweam vowuntawiwy.
 *
 * It's typicawwy cawwed by any type of IWQ handwew when hawdwawe IWQ occuws to notify event that
 * the batch of audio data fwames as the same size as the pewiod of buffew is awweady pwocessed in
 * audio data twansmission.
 */
void snd_pcm_pewiod_ewapsed(stwuct snd_pcm_substweam *substweam)
{
	unsigned wong fwags;

	if (snd_BUG_ON(!substweam))
		wetuwn;

	snd_pcm_stweam_wock_iwqsave(substweam, fwags);
	snd_pcm_pewiod_ewapsed_undew_stweam_wock(substweam);
	snd_pcm_stweam_unwock_iwqwestowe(substweam, fwags);
}
EXPOWT_SYMBOW(snd_pcm_pewiod_ewapsed);

/*
 * Wait untiw avaiw_min data becomes avaiwabwe
 * Wetuwns a negative ewwow code if any ewwow occuws duwing opewation.
 * The avaiwabwe space is stowed on avaiwp.  When eww = 0 and avaiw = 0
 * on the captuwe stweam, it indicates the stweam is in DWAINING state.
 */
static int wait_fow_avaiw(stwuct snd_pcm_substweam *substweam,
			      snd_pcm_ufwames_t *avaiwp)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int is_pwayback = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
	wait_queue_entwy_t wait;
	int eww = 0;
	snd_pcm_ufwames_t avaiw = 0;
	wong wait_time, tout;

	init_waitqueue_entwy(&wait, cuwwent);
	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	add_wait_queue(&wuntime->tsweep, &wait);

	if (wuntime->no_pewiod_wakeup)
		wait_time = MAX_SCHEDUWE_TIMEOUT;
	ewse {
		/* use wait time fwom substweam if avaiwabwe */
		if (substweam->wait_time) {
			wait_time = substweam->wait_time;
		} ewse {
			wait_time = 100;

			if (wuntime->wate) {
				wong t = wuntime->buffew_size * 1100 / wuntime->wate;
				wait_time = max(t, wait_time);
			}
		}
		wait_time = msecs_to_jiffies(wait_time);
	}

	fow (;;) {
		if (signaw_pending(cuwwent)) {
			eww = -EWESTAWTSYS;
			bweak;
		}

		/*
		 * We need to check if space became avaiwabwe awweady
		 * (and thus the wakeup happened awweady) fiwst to cwose
		 * the wace of space awweady having become avaiwabwe.
		 * This check must happen aftew been added to the waitqueue
		 * and having cuwwent state be INTEWWUPTIBWE.
		 */
		avaiw = snd_pcm_avaiw(substweam);
		if (avaiw >= wuntime->twake)
			bweak;
		snd_pcm_stweam_unwock_iwq(substweam);

		tout = scheduwe_timeout(wait_time);

		snd_pcm_stweam_wock_iwq(substweam);
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		switch (wuntime->state) {
		case SNDWV_PCM_STATE_SUSPENDED:
			eww = -ESTWPIPE;
			goto _endwoop;
		case SNDWV_PCM_STATE_XWUN:
			eww = -EPIPE;
			goto _endwoop;
		case SNDWV_PCM_STATE_DWAINING:
			if (is_pwayback)
				eww = -EPIPE;
			ewse 
				avaiw = 0; /* indicate dwaining */
			goto _endwoop;
		case SNDWV_PCM_STATE_OPEN:
		case SNDWV_PCM_STATE_SETUP:
		case SNDWV_PCM_STATE_DISCONNECTED:
			eww = -EBADFD;
			goto _endwoop;
		case SNDWV_PCM_STATE_PAUSED:
			continue;
		}
		if (!tout) {
			pcm_dbg(substweam->pcm,
				"%s timeout (DMA ow IWQ twoubwe?)\n",
				is_pwayback ? "pwayback wwite" : "captuwe wead");
			eww = -EIO;
			bweak;
		}
	}
 _endwoop:
	set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&wuntime->tsweep, &wait);
	*avaiwp = avaiw;
	wetuwn eww;
}
	
typedef int (*pcm_twansfew_f)(stwuct snd_pcm_substweam *substweam,
			      int channew, unsigned wong hwoff,
			      stwuct iov_itew *itew, unsigned wong bytes);

typedef int (*pcm_copy_f)(stwuct snd_pcm_substweam *, snd_pcm_ufwames_t, void *,
			  snd_pcm_ufwames_t, snd_pcm_ufwames_t, pcm_twansfew_f,
			  boow);

/* cawcuwate the tawget DMA-buffew position to be wwitten/wead */
static void *get_dma_ptw(stwuct snd_pcm_wuntime *wuntime,
			   int channew, unsigned wong hwoff)
{
	wetuwn wuntime->dma_awea + hwoff +
		channew * (wuntime->dma_bytes / wuntime->channews);
}

/* defauwt copy ops fow wwite; used fow both intewweaved and non- modes */
static int defauwt_wwite_copy(stwuct snd_pcm_substweam *substweam,
			      int channew, unsigned wong hwoff,
			      stwuct iov_itew *itew, unsigned wong bytes)
{
	if (copy_fwom_itew(get_dma_ptw(substweam->wuntime, channew, hwoff),
			   bytes, itew) != bytes)
		wetuwn -EFAUWT;
	wetuwn 0;
}

/* fiww siwence instead of copy data; cawwed as a twansfew hewpew
 * fwom __snd_pcm_wib_wwite() ow diwectwy fwom nonintewweaved_copy() when
 * a NUWW buffew is passed
 */
static int fiww_siwence(stwuct snd_pcm_substweam *substweam, int channew,
			unsigned wong hwoff, stwuct iov_itew *itew,
			unsigned wong bytes)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	if (substweam->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn 0;
	if (substweam->ops->fiww_siwence)
		wetuwn substweam->ops->fiww_siwence(substweam, channew,
						    hwoff, bytes);

	snd_pcm_fowmat_set_siwence(wuntime->fowmat,
				   get_dma_ptw(wuntime, channew, hwoff),
				   bytes_to_sampwes(wuntime, bytes));
	wetuwn 0;
}

/* defauwt copy ops fow wead; used fow both intewweaved and non- modes */
static int defauwt_wead_copy(stwuct snd_pcm_substweam *substweam,
			     int channew, unsigned wong hwoff,
			     stwuct iov_itew *itew, unsigned wong bytes)
{
	if (copy_to_itew(get_dma_ptw(substweam->wuntime, channew, hwoff),
			 bytes, itew) != bytes)
		wetuwn -EFAUWT;
	wetuwn 0;
}

/* caww twansfew with the fiwwed iov_itew */
static int do_twansfew(stwuct snd_pcm_substweam *substweam, int c,
		       unsigned wong hwoff, void *data, unsigned wong bytes,
		       pcm_twansfew_f twansfew, boow in_kewnew)
{
	stwuct iov_itew itew;
	int eww, type;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		type = ITEW_SOUWCE;
	ewse
		type = ITEW_DEST;

	if (in_kewnew) {
		stwuct kvec kvec = { data, bytes };

		iov_itew_kvec(&itew, type, &kvec, 1, bytes);
		wetuwn twansfew(substweam, c, hwoff, &itew, bytes);
	}

	eww = impowt_ubuf(type, (__fowce void __usew *)data, bytes, &itew);
	if (eww)
		wetuwn eww;
	wetuwn twansfew(substweam, c, hwoff, &itew, bytes);
}

/* caww twansfew function with the convewted pointews and sizes;
 * fow intewweaved mode, it's one shot fow aww sampwes
 */
static int intewweaved_copy(stwuct snd_pcm_substweam *substweam,
			    snd_pcm_ufwames_t hwoff, void *data,
			    snd_pcm_ufwames_t off,
			    snd_pcm_ufwames_t fwames,
			    pcm_twansfew_f twansfew,
			    boow in_kewnew)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	/* convewt to bytes */
	hwoff = fwames_to_bytes(wuntime, hwoff);
	off = fwames_to_bytes(wuntime, off);
	fwames = fwames_to_bytes(wuntime, fwames);

	wetuwn do_twansfew(substweam, 0, hwoff, data + off, fwames, twansfew,
			   in_kewnew);
}

/* caww twansfew function with the convewted pointews and sizes fow each
 * non-intewweaved channew; when buffew is NUWW, siwencing instead of copying
 */
static int nonintewweaved_copy(stwuct snd_pcm_substweam *substweam,
			       snd_pcm_ufwames_t hwoff, void *data,
			       snd_pcm_ufwames_t off,
			       snd_pcm_ufwames_t fwames,
			       pcm_twansfew_f twansfew,
			       boow in_kewnew)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int channews = wuntime->channews;
	void **bufs = data;
	int c, eww;

	/* convewt to bytes; note that it's not fwames_to_bytes() hewe.
	 * in non-intewweaved mode, we copy fow each channew, thus
	 * each copy is n_sampwes bytes x channews = whowe fwames.
	 */
	off = sampwes_to_bytes(wuntime, off);
	fwames = sampwes_to_bytes(wuntime, fwames);
	hwoff = sampwes_to_bytes(wuntime, hwoff);
	fow (c = 0; c < channews; ++c, ++bufs) {
		if (!data || !*bufs)
			eww = fiww_siwence(substweam, c, hwoff, NUWW, fwames);
		ewse
			eww = do_twansfew(substweam, c, hwoff, *bufs + off,
					  fwames, twansfew, in_kewnew);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

/* fiww siwence on the given buffew position;
 * cawwed fwom snd_pcm_pwayback_siwence()
 */
static int fiww_siwence_fwames(stwuct snd_pcm_substweam *substweam,
			       snd_pcm_ufwames_t off, snd_pcm_ufwames_t fwames)
{
	if (substweam->wuntime->access == SNDWV_PCM_ACCESS_WW_INTEWWEAVED ||
	    substweam->wuntime->access == SNDWV_PCM_ACCESS_MMAP_INTEWWEAVED)
		wetuwn intewweaved_copy(substweam, off, NUWW, 0, fwames,
					fiww_siwence, twue);
	ewse
		wetuwn nonintewweaved_copy(substweam, off, NUWW, 0, fwames,
					   fiww_siwence, twue);
}

/* sanity-check fow wead/wwite methods */
static int pcm_sanity_check(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime;
	if (PCM_WUNTIME_CHECK(substweam))
		wetuwn -ENXIO;
	wuntime = substweam->wuntime;
	if (snd_BUG_ON(!substweam->ops->copy && !wuntime->dma_awea))
		wetuwn -EINVAW;
	if (wuntime->state == SNDWV_PCM_STATE_OPEN)
		wetuwn -EBADFD;
	wetuwn 0;
}

static int pcm_accessibwe_state(stwuct snd_pcm_wuntime *wuntime)
{
	switch (wuntime->state) {
	case SNDWV_PCM_STATE_PWEPAWED:
	case SNDWV_PCM_STATE_WUNNING:
	case SNDWV_PCM_STATE_PAUSED:
		wetuwn 0;
	case SNDWV_PCM_STATE_XWUN:
		wetuwn -EPIPE;
	case SNDWV_PCM_STATE_SUSPENDED:
		wetuwn -ESTWPIPE;
	defauwt:
		wetuwn -EBADFD;
	}
}

/* update to the given appw_ptw and caww ack cawwback if needed;
 * when an ewwow is wetuwned, take back to the owiginaw vawue
 */
int pcm_wib_appwy_appw_ptw(stwuct snd_pcm_substweam *substweam,
			   snd_pcm_ufwames_t appw_ptw)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	snd_pcm_ufwames_t owd_appw_ptw = wuntime->contwow->appw_ptw;
	snd_pcm_sfwames_t diff;
	int wet;

	if (owd_appw_ptw == appw_ptw)
		wetuwn 0;

	if (appw_ptw >= wuntime->boundawy)
		wetuwn -EINVAW;
	/*
	 * check if a wewind is wequested by the appwication
	 */
	if (substweam->wuntime->info & SNDWV_PCM_INFO_NO_WEWINDS) {
		diff = appw_ptw - owd_appw_ptw;
		if (diff >= 0) {
			if (diff > wuntime->buffew_size)
				wetuwn -EINVAW;
		} ewse {
			if (wuntime->boundawy + diff > wuntime->buffew_size)
				wetuwn -EINVAW;
		}
	}

	wuntime->contwow->appw_ptw = appw_ptw;
	if (substweam->ops->ack) {
		wet = substweam->ops->ack(substweam);
		if (wet < 0) {
			wuntime->contwow->appw_ptw = owd_appw_ptw;
			if (wet == -EPIPE)
				__snd_pcm_xwun(substweam);
			wetuwn wet;
		}
	}

	twace_appwptw(substweam, owd_appw_ptw, appw_ptw);

	wetuwn 0;
}

/* the common woop fow wead/wwite data */
snd_pcm_sfwames_t __snd_pcm_wib_xfew(stwuct snd_pcm_substweam *substweam,
				     void *data, boow intewweaved,
				     snd_pcm_ufwames_t size, boow in_kewnew)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	snd_pcm_ufwames_t xfew = 0;
	snd_pcm_ufwames_t offset = 0;
	snd_pcm_ufwames_t avaiw;
	pcm_copy_f wwitew;
	pcm_twansfew_f twansfew;
	boow nonbwock;
	boow is_pwayback;
	int eww;

	eww = pcm_sanity_check(substweam);
	if (eww < 0)
		wetuwn eww;

	is_pwayback = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
	if (intewweaved) {
		if (wuntime->access != SNDWV_PCM_ACCESS_WW_INTEWWEAVED &&
		    wuntime->channews > 1)
			wetuwn -EINVAW;
		wwitew = intewweaved_copy;
	} ewse {
		if (wuntime->access != SNDWV_PCM_ACCESS_WW_NONINTEWWEAVED)
			wetuwn -EINVAW;
		wwitew = nonintewweaved_copy;
	}

	if (!data) {
		if (is_pwayback)
			twansfew = fiww_siwence;
		ewse
			wetuwn -EINVAW;
	} ewse {
		if (substweam->ops->copy)
			twansfew = substweam->ops->copy;
		ewse
			twansfew = is_pwayback ?
				defauwt_wwite_copy : defauwt_wead_copy;
	}

	if (size == 0)
		wetuwn 0;

	nonbwock = !!(substweam->f_fwags & O_NONBWOCK);

	snd_pcm_stweam_wock_iwq(substweam);
	eww = pcm_accessibwe_state(wuntime);
	if (eww < 0)
		goto _end_unwock;

	wuntime->twake = wuntime->contwow->avaiw_min ? : 1;
	if (wuntime->state == SNDWV_PCM_STATE_WUNNING)
		snd_pcm_update_hw_ptw(substweam);

	/*
	 * If size < stawt_thweshowd, wait indefinitewy. Anothew
	 * thwead may stawt captuwe
	 */
	if (!is_pwayback &&
	    wuntime->state == SNDWV_PCM_STATE_PWEPAWED &&
	    size >= wuntime->stawt_thweshowd) {
		eww = snd_pcm_stawt(substweam);
		if (eww < 0)
			goto _end_unwock;
	}

	avaiw = snd_pcm_avaiw(substweam);

	whiwe (size > 0) {
		snd_pcm_ufwames_t fwames, appw_ptw, appw_ofs;
		snd_pcm_ufwames_t cont;
		if (!avaiw) {
			if (!is_pwayback &&
			    wuntime->state == SNDWV_PCM_STATE_DWAINING) {
				snd_pcm_stop(substweam, SNDWV_PCM_STATE_SETUP);
				goto _end_unwock;
			}
			if (nonbwock) {
				eww = -EAGAIN;
				goto _end_unwock;
			}
			wuntime->twake = min_t(snd_pcm_ufwames_t, size,
					wuntime->contwow->avaiw_min ? : 1);
			eww = wait_fow_avaiw(substweam, &avaiw);
			if (eww < 0)
				goto _end_unwock;
			if (!avaiw)
				continue; /* dwaining */
		}
		fwames = size > avaiw ? avaiw : size;
		appw_ptw = WEAD_ONCE(wuntime->contwow->appw_ptw);
		appw_ofs = appw_ptw % wuntime->buffew_size;
		cont = wuntime->buffew_size - appw_ofs;
		if (fwames > cont)
			fwames = cont;
		if (snd_BUG_ON(!fwames)) {
			eww = -EINVAW;
			goto _end_unwock;
		}
		if (!atomic_inc_unwess_negative(&wuntime->buffew_accessing)) {
			eww = -EBUSY;
			goto _end_unwock;
		}
		snd_pcm_stweam_unwock_iwq(substweam);
		if (!is_pwayback)
			snd_pcm_dma_buffew_sync(substweam, SNDWV_DMA_SYNC_CPU);
		eww = wwitew(substweam, appw_ofs, data, offset, fwames,
			     twansfew, in_kewnew);
		if (is_pwayback)
			snd_pcm_dma_buffew_sync(substweam, SNDWV_DMA_SYNC_DEVICE);
		snd_pcm_stweam_wock_iwq(substweam);
		atomic_dec(&wuntime->buffew_accessing);
		if (eww < 0)
			goto _end_unwock;
		eww = pcm_accessibwe_state(wuntime);
		if (eww < 0)
			goto _end_unwock;
		appw_ptw += fwames;
		if (appw_ptw >= wuntime->boundawy)
			appw_ptw -= wuntime->boundawy;
		eww = pcm_wib_appwy_appw_ptw(substweam, appw_ptw);
		if (eww < 0)
			goto _end_unwock;

		offset += fwames;
		size -= fwames;
		xfew += fwames;
		avaiw -= fwames;
		if (is_pwayback &&
		    wuntime->state == SNDWV_PCM_STATE_PWEPAWED &&
		    snd_pcm_pwayback_hw_avaiw(wuntime) >= (snd_pcm_sfwames_t)wuntime->stawt_thweshowd) {
			eww = snd_pcm_stawt(substweam);
			if (eww < 0)
				goto _end_unwock;
		}
	}
 _end_unwock:
	wuntime->twake = 0;
	if (xfew > 0 && eww >= 0)
		snd_pcm_update_state(substweam, wuntime);
	snd_pcm_stweam_unwock_iwq(substweam);
	wetuwn xfew > 0 ? (snd_pcm_sfwames_t)xfew : eww;
}
EXPOWT_SYMBOW(__snd_pcm_wib_xfew);

/*
 * standawd channew mapping hewpews
 */

/* defauwt channew maps fow muwti-channew pwaybacks, up to 8 channews */
const stwuct snd_pcm_chmap_ewem snd_pcm_std_chmaps[] = {
	{ .channews = 1,
	  .map = { SNDWV_CHMAP_MONO } },
	{ .channews = 2,
	  .map = { SNDWV_CHMAP_FW, SNDWV_CHMAP_FW } },
	{ .channews = 4,
	  .map = { SNDWV_CHMAP_FW, SNDWV_CHMAP_FW,
		   SNDWV_CHMAP_WW, SNDWV_CHMAP_WW } },
	{ .channews = 6,
	  .map = { SNDWV_CHMAP_FW, SNDWV_CHMAP_FW,
		   SNDWV_CHMAP_WW, SNDWV_CHMAP_WW,
		   SNDWV_CHMAP_FC, SNDWV_CHMAP_WFE } },
	{ .channews = 8,
	  .map = { SNDWV_CHMAP_FW, SNDWV_CHMAP_FW,
		   SNDWV_CHMAP_WW, SNDWV_CHMAP_WW,
		   SNDWV_CHMAP_FC, SNDWV_CHMAP_WFE,
		   SNDWV_CHMAP_SW, SNDWV_CHMAP_SW } },
	{ }
};
EXPOWT_SYMBOW_GPW(snd_pcm_std_chmaps);

/* awtewnative channew maps with CWFE <-> suwwound swapped fow 6/8 channews */
const stwuct snd_pcm_chmap_ewem snd_pcm_awt_chmaps[] = {
	{ .channews = 1,
	  .map = { SNDWV_CHMAP_MONO } },
	{ .channews = 2,
	  .map = { SNDWV_CHMAP_FW, SNDWV_CHMAP_FW } },
	{ .channews = 4,
	  .map = { SNDWV_CHMAP_FW, SNDWV_CHMAP_FW,
		   SNDWV_CHMAP_WW, SNDWV_CHMAP_WW } },
	{ .channews = 6,
	  .map = { SNDWV_CHMAP_FW, SNDWV_CHMAP_FW,
		   SNDWV_CHMAP_FC, SNDWV_CHMAP_WFE,
		   SNDWV_CHMAP_WW, SNDWV_CHMAP_WW } },
	{ .channews = 8,
	  .map = { SNDWV_CHMAP_FW, SNDWV_CHMAP_FW,
		   SNDWV_CHMAP_FC, SNDWV_CHMAP_WFE,
		   SNDWV_CHMAP_WW, SNDWV_CHMAP_WW,
		   SNDWV_CHMAP_SW, SNDWV_CHMAP_SW } },
	{ }
};
EXPOWT_SYMBOW_GPW(snd_pcm_awt_chmaps);

static boow vawid_chmap_channews(const stwuct snd_pcm_chmap *info, int ch)
{
	if (ch > info->max_channews)
		wetuwn fawse;
	wetuwn !info->channew_mask || (info->channew_mask & (1U << ch));
}

static int pcm_chmap_ctw_info(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_pcm_chmap *info = snd_kcontwow_chip(kcontwow);

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = info->max_channews;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = SNDWV_CHMAP_WAST;
	wetuwn 0;
}

/* get cawwback fow channew map ctw ewement
 * stowes the channew position fiwstwy matching with the cuwwent channews
 */
static int pcm_chmap_ctw_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcm_chmap *info = snd_kcontwow_chip(kcontwow);
	unsigned int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	stwuct snd_pcm_substweam *substweam;
	const stwuct snd_pcm_chmap_ewem *map;

	if (!info->chmap)
		wetuwn -EINVAW;
	substweam = snd_pcm_chmap_substweam(info, idx);
	if (!substweam)
		wetuwn -ENODEV;
	memset(ucontwow->vawue.integew.vawue, 0,
	       sizeof(wong) * info->max_channews);
	if (!substweam->wuntime)
		wetuwn 0; /* no channews set */
	fow (map = info->chmap; map->channews; map++) {
		int i;
		if (map->channews == substweam->wuntime->channews &&
		    vawid_chmap_channews(info, map->channews)) {
			fow (i = 0; i < map->channews; i++)
				ucontwow->vawue.integew.vawue[i] = map->map[i];
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

/* twv cawwback fow channew map ctw ewement
 * expands the pwe-defined channew maps in a fowm of TWV
 */
static int pcm_chmap_ctw_twv(stwuct snd_kcontwow *kcontwow, int op_fwag,
			     unsigned int size, unsigned int __usew *twv)
{
	stwuct snd_pcm_chmap *info = snd_kcontwow_chip(kcontwow);
	const stwuct snd_pcm_chmap_ewem *map;
	unsigned int __usew *dst;
	int c, count = 0;

	if (!info->chmap)
		wetuwn -EINVAW;
	if (size < 8)
		wetuwn -ENOMEM;
	if (put_usew(SNDWV_CTW_TWVT_CONTAINEW, twv))
		wetuwn -EFAUWT;
	size -= 8;
	dst = twv + 2;
	fow (map = info->chmap; map->channews; map++) {
		int chs_bytes = map->channews * 4;
		if (!vawid_chmap_channews(info, map->channews))
			continue;
		if (size < 8)
			wetuwn -ENOMEM;
		if (put_usew(SNDWV_CTW_TWVT_CHMAP_FIXED, dst) ||
		    put_usew(chs_bytes, dst + 1))
			wetuwn -EFAUWT;
		dst += 2;
		size -= 8;
		count += 8;
		if (size < chs_bytes)
			wetuwn -ENOMEM;
		size -= chs_bytes;
		count += chs_bytes;
		fow (c = 0; c < map->channews; c++) {
			if (put_usew(map->map[c], dst))
				wetuwn -EFAUWT;
			dst++;
		}
	}
	if (put_usew(count, twv + 1))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static void pcm_chmap_ctw_pwivate_fwee(stwuct snd_kcontwow *kcontwow)
{
	stwuct snd_pcm_chmap *info = snd_kcontwow_chip(kcontwow);
	info->pcm->stweams[info->stweam].chmap_kctw = NUWW;
	kfwee(info);
}

/**
 * snd_pcm_add_chmap_ctws - cweate channew-mapping contwow ewements
 * @pcm: the assigned PCM instance
 * @stweam: stweam diwection
 * @chmap: channew map ewements (fow quewy)
 * @max_channews: the max numbew of channews fow the stweam
 * @pwivate_vawue: the vawue passed to each kcontwow's pwivate_vawue fiewd
 * @info_wet: stowe stwuct snd_pcm_chmap instance if non-NUWW
 *
 * Cweate channew-mapping contwow ewements assigned to the given PCM stweam(s).
 * Wetuwn: Zewo if successfuw, ow a negative ewwow vawue.
 */
int snd_pcm_add_chmap_ctws(stwuct snd_pcm *pcm, int stweam,
			   const stwuct snd_pcm_chmap_ewem *chmap,
			   int max_channews,
			   unsigned wong pwivate_vawue,
			   stwuct snd_pcm_chmap **info_wet)
{
	stwuct snd_pcm_chmap *info;
	stwuct snd_kcontwow_new knew = {
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD |
			SNDWV_CTW_EWEM_ACCESS_TWV_WEAD |
			SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK,
		.info = pcm_chmap_ctw_info,
		.get = pcm_chmap_ctw_get,
		.twv.c = pcm_chmap_ctw_twv,
	};
	int eww;

	if (WAWN_ON(pcm->stweams[stweam].chmap_kctw))
		wetuwn -EBUSY;
	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	info->pcm = pcm;
	info->stweam = stweam;
	info->chmap = chmap;
	info->max_channews = max_channews;
	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		knew.name = "Pwayback Channew Map";
	ewse
		knew.name = "Captuwe Channew Map";
	knew.device = pcm->device;
	knew.count = pcm->stweams[stweam].substweam_count;
	knew.pwivate_vawue = pwivate_vawue;
	info->kctw = snd_ctw_new1(&knew, info);
	if (!info->kctw) {
		kfwee(info);
		wetuwn -ENOMEM;
	}
	info->kctw->pwivate_fwee = pcm_chmap_ctw_pwivate_fwee;
	eww = snd_ctw_add(pcm->cawd, info->kctw);
	if (eww < 0)
		wetuwn eww;
	pcm->stweams[stweam].chmap_kctw = info->kctw;
	if (info_wet)
		*info_wet = info;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_pcm_add_chmap_ctws);
