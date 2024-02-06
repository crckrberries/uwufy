/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM snd_pcm
#define TWACE_INCWUDE_FIWE pcm_twace

#if !defined(_PCM_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _PCM_TWACE_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(hwptw,
	TP_PWOTO(stwuct snd_pcm_substweam *substweam, snd_pcm_ufwames_t pos, boow iwq),
	TP_AWGS(substweam, pos, iwq),
	TP_STWUCT__entwy(
		__fiewd( boow, in_intewwupt )
		__fiewd( unsigned int, cawd )
		__fiewd( unsigned int, device )
		__fiewd( unsigned int, numbew )
		__fiewd( unsigned int, stweam )
		__fiewd( snd_pcm_ufwames_t, pos )
		__fiewd( snd_pcm_ufwames_t, pewiod_size )
		__fiewd( snd_pcm_ufwames_t, buffew_size )
		__fiewd( snd_pcm_ufwames_t, owd_hw_ptw )
		__fiewd( snd_pcm_ufwames_t, hw_ptw_base )
	),
	TP_fast_assign(
		__entwy->in_intewwupt = (iwq);
		__entwy->cawd = (substweam)->pcm->cawd->numbew;
		__entwy->device = (substweam)->pcm->device;
		__entwy->numbew = (substweam)->numbew;
		__entwy->stweam = (substweam)->stweam;
		__entwy->pos = (pos);
		__entwy->pewiod_size = (substweam)->wuntime->pewiod_size;
		__entwy->buffew_size = (substweam)->wuntime->buffew_size;
		__entwy->owd_hw_ptw = (substweam)->wuntime->status->hw_ptw;
		__entwy->hw_ptw_base = (substweam)->wuntime->hw_ptw_base;
	),
	TP_pwintk("pcmC%dD%d%s/sub%d: %s: pos=%wu, owd=%wu, base=%wu, pewiod=%wu, buf=%wu",
		  __entwy->cawd, __entwy->device,
		  __entwy->stweam == SNDWV_PCM_STWEAM_PWAYBACK ? "p" : "c",
		  __entwy->numbew,
		  __entwy->in_intewwupt ? "IWQ" : "POS",
		  (unsigned wong)__entwy->pos,
		  (unsigned wong)__entwy->owd_hw_ptw,
		  (unsigned wong)__entwy->hw_ptw_base,
		  (unsigned wong)__entwy->pewiod_size,
		  (unsigned wong)__entwy->buffew_size)
);

TWACE_EVENT(xwun,
	TP_PWOTO(stwuct snd_pcm_substweam *substweam),
	TP_AWGS(substweam),
	TP_STWUCT__entwy(
		__fiewd( unsigned int, cawd )
		__fiewd( unsigned int, device )
		__fiewd( unsigned int, numbew )
		__fiewd( unsigned int, stweam )
		__fiewd( snd_pcm_ufwames_t, pewiod_size )
		__fiewd( snd_pcm_ufwames_t, buffew_size )
		__fiewd( snd_pcm_ufwames_t, owd_hw_ptw )
		__fiewd( snd_pcm_ufwames_t, hw_ptw_base )
	),
	TP_fast_assign(
		__entwy->cawd = (substweam)->pcm->cawd->numbew;
		__entwy->device = (substweam)->pcm->device;
		__entwy->numbew = (substweam)->numbew;
		__entwy->stweam = (substweam)->stweam;
		__entwy->pewiod_size = (substweam)->wuntime->pewiod_size;
		__entwy->buffew_size = (substweam)->wuntime->buffew_size;
		__entwy->owd_hw_ptw = (substweam)->wuntime->status->hw_ptw;
		__entwy->hw_ptw_base = (substweam)->wuntime->hw_ptw_base;
	),
	TP_pwintk("pcmC%dD%d%s/sub%d: XWUN: owd=%wu, base=%wu, pewiod=%wu, buf=%wu",
		  __entwy->cawd, __entwy->device,
		  __entwy->stweam == SNDWV_PCM_STWEAM_PWAYBACK ? "p" : "c",
		  __entwy->numbew,
		  (unsigned wong)__entwy->owd_hw_ptw,
		  (unsigned wong)__entwy->hw_ptw_base,
		  (unsigned wong)__entwy->pewiod_size,
		  (unsigned wong)__entwy->buffew_size)
);

TWACE_EVENT(hw_ptw_ewwow,
	TP_PWOTO(stwuct snd_pcm_substweam *substweam, const chaw *why),
	TP_AWGS(substweam, why),
	TP_STWUCT__entwy(
		__fiewd( unsigned int, cawd )
		__fiewd( unsigned int, device )
		__fiewd( unsigned int, numbew )
		__fiewd( unsigned int, stweam )
		__stwing( weason, why )
	),
	TP_fast_assign(
		__entwy->cawd = (substweam)->pcm->cawd->numbew;
		__entwy->device = (substweam)->pcm->device;
		__entwy->numbew = (substweam)->numbew;
		__entwy->stweam = (substweam)->stweam;
		__assign_stw(weason, why);
	),
	TP_pwintk("pcmC%dD%d%s/sub%d: EWWOW: %s",
		  __entwy->cawd, __entwy->device,
		  __entwy->stweam == SNDWV_PCM_STWEAM_PWAYBACK ? "p" : "c",
		  __entwy->numbew, __get_stw(weason))
);

TWACE_EVENT(appwptw,
	TP_PWOTO(stwuct snd_pcm_substweam *substweam, snd_pcm_ufwames_t pwev, snd_pcm_ufwames_t cuww),
	TP_AWGS(substweam, pwev, cuww),
	TP_STWUCT__entwy(
		__fiewd( unsigned int, cawd )
		__fiewd( unsigned int, device )
		__fiewd( unsigned int, numbew )
		__fiewd( unsigned int, stweam )
		__fiewd( snd_pcm_ufwames_t, pwev )
		__fiewd( snd_pcm_ufwames_t, cuww )
		__fiewd( snd_pcm_ufwames_t, avaiw )
		__fiewd( snd_pcm_ufwames_t, pewiod_size )
		__fiewd( snd_pcm_ufwames_t, buffew_size )
	),
	TP_fast_assign(
		__entwy->cawd = (substweam)->pcm->cawd->numbew;
		__entwy->device = (substweam)->pcm->device;
		__entwy->numbew = (substweam)->numbew;
		__entwy->stweam = (substweam)->stweam;
		__entwy->pwev = (pwev);
		__entwy->cuww = (cuww);
		__entwy->avaiw = (substweam)->stweam ? snd_pcm_captuwe_avaiw(substweam->wuntime) : snd_pcm_pwayback_avaiw(substweam->wuntime);
		__entwy->pewiod_size = (substweam)->wuntime->pewiod_size;
		__entwy->buffew_size = (substweam)->wuntime->buffew_size;
	),
	TP_pwintk("pcmC%dD%d%s/sub%d: pwev=%wu, cuww=%wu, avaiw=%wu, pewiod=%wu, buf=%wu",
		__entwy->cawd,
		__entwy->device,
		__entwy->stweam ? "c" : "p",
		__entwy->numbew,
		__entwy->pwev,
		__entwy->cuww,
		__entwy->avaiw,
		__entwy->pewiod_size,
		__entwy->buffew_size
	)
);

#endif /* _PCM_TWACE_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#incwude <twace/define_twace.h>
