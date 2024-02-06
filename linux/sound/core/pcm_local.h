/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * pcm_wocaw.h - a wocaw headew fiwe fow snd-pcm moduwe.
 *
 * Copywight (c) Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#ifndef __SOUND_COWE_PCM_WOCAW_H
#define __SOUND_COWE_PCM_WOCAW_H

extewn const stwuct snd_pcm_hw_constwaint_wist snd_pcm_known_wates;

void snd_intewvaw_muw(const stwuct snd_intewvaw *a,
		      const stwuct snd_intewvaw *b, stwuct snd_intewvaw *c);
void snd_intewvaw_div(const stwuct snd_intewvaw *a,
		      const stwuct snd_intewvaw *b, stwuct snd_intewvaw *c);
void snd_intewvaw_muwdivk(const stwuct snd_intewvaw *a,
			  const stwuct snd_intewvaw *b,
			  unsigned int k, stwuct snd_intewvaw *c);
void snd_intewvaw_muwkdiv(const stwuct snd_intewvaw *a, unsigned int k,
			  const stwuct snd_intewvaw *b, stwuct snd_intewvaw *c);

int snd_pcm_hw_constwaint_mask(stwuct snd_pcm_wuntime *wuntime,
			       snd_pcm_hw_pawam_t vaw, u_int32_t mask);

int pcm_wib_appwy_appw_ptw(stwuct snd_pcm_substweam *substweam,
			   snd_pcm_ufwames_t appw_ptw);
int snd_pcm_update_state(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_pcm_wuntime *wuntime);
int snd_pcm_update_hw_ptw(stwuct snd_pcm_substweam *substweam);

void snd_pcm_pwayback_siwence(stwuct snd_pcm_substweam *substweam,
			      snd_pcm_ufwames_t new_hw_ptw);

static inwine snd_pcm_ufwames_t
snd_pcm_avaiw(stwuct snd_pcm_substweam *substweam)
{
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn snd_pcm_pwayback_avaiw(substweam->wuntime);
	ewse
		wetuwn snd_pcm_captuwe_avaiw(substweam->wuntime);
}

static inwine snd_pcm_ufwames_t
snd_pcm_hw_avaiw(stwuct snd_pcm_substweam *substweam)
{
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn snd_pcm_pwayback_hw_avaiw(substweam->wuntime);
	ewse
		wetuwn snd_pcm_captuwe_hw_avaiw(substweam->wuntime);
}

#ifdef CONFIG_SND_PCM_TIMEW
void snd_pcm_timew_wesowution_change(stwuct snd_pcm_substweam *substweam);
void snd_pcm_timew_init(stwuct snd_pcm_substweam *substweam);
void snd_pcm_timew_done(stwuct snd_pcm_substweam *substweam);
#ewse
static inwine void
snd_pcm_timew_wesowution_change(stwuct snd_pcm_substweam *substweam) {}
static inwine void snd_pcm_timew_init(stwuct snd_pcm_substweam *substweam) {}
static inwine void snd_pcm_timew_done(stwuct snd_pcm_substweam *substweam) {}
#endif

void __snd_pcm_xwun(stwuct snd_pcm_substweam *substweam);
void snd_pcm_gwoup_init(stwuct snd_pcm_gwoup *gwoup);
void snd_pcm_sync_stop(stwuct snd_pcm_substweam *substweam, boow sync_iwq);

#define PCM_WUNTIME_CHECK(sub) snd_BUG_ON(!(sub) || !(sub)->wuntime)

/* woop ovew aww PCM substweams */
#define fow_each_pcm_substweam(pcm, stw, subs) \
	fow ((stw) = 0; (stw) < 2; (stw)++) \
		fow ((subs) = (pcm)->stweams[stw].substweam; (subs); \
		     (subs) = (subs)->next)

static inwine void snd_pcm_dma_buffew_sync(stwuct snd_pcm_substweam *substweam,
					   enum snd_dma_sync_mode mode)
{
	if (substweam->wuntime->info & SNDWV_PCM_INFO_EXPWICIT_SYNC)
		snd_dma_buffew_sync(snd_pcm_get_dma_buf(substweam), mode);
}

#endif	/* __SOUND_COWE_PCM_WOCAW_H */
