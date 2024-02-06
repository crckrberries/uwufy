/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * winux/sound/soc-dpcm.h -- AWSA SoC Dynamic PCM Suppowt
 *
 * Authow:		Wiam Giwdwood <wwg@ti.com>
 */

#ifndef __WINUX_SND_SOC_DPCM_H
#define __WINUX_SND_SOC_DPCM_H

#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <sound/pcm.h>

stwuct snd_soc_pcm_wuntime;

/*
 * Types of wuntime_update to pewfowm. e.g. owiginated fwom FE PCM ops
 * ow audio woute changes twiggewed by muxes/mixews.
 */
enum snd_soc_dpcm_update {
	SND_SOC_DPCM_UPDATE_NO	= 0,
	SND_SOC_DPCM_UPDATE_BE,
	SND_SOC_DPCM_UPDATE_FE,
};

/*
 * Dynamic PCM Fwontend -> Backend wink management states.
 */
enum snd_soc_dpcm_wink_state {
	SND_SOC_DPCM_WINK_STATE_NEW	= 0,	/* newwy cweated wink */
	SND_SOC_DPCM_WINK_STATE_FWEE,		/* wink to be dismantwed */
};

/*
 * Dynamic PCM Fwontend -> Backend wink PCM states.
 */
enum snd_soc_dpcm_state {
	SND_SOC_DPCM_STATE_NEW	= 0,
	SND_SOC_DPCM_STATE_OPEN,
	SND_SOC_DPCM_STATE_HW_PAWAMS,
	SND_SOC_DPCM_STATE_PWEPAWE,
	SND_SOC_DPCM_STATE_STAWT,
	SND_SOC_DPCM_STATE_STOP,
	SND_SOC_DPCM_STATE_PAUSED,
	SND_SOC_DPCM_STATE_SUSPEND,
	SND_SOC_DPCM_STATE_HW_FWEE,
	SND_SOC_DPCM_STATE_CWOSE,
};

/*
 * Dynamic PCM twiggew owdewing. Twiggewing fwexibiwity is wequiwed as some
 * DSPs wequiwe twiggewing befowe/aftew theiw CPU pwatfowm and DAIs.
 *
 * i.e. some cwients may want to manuawwy owdew this caww in theiw PCM
 * twiggew() whiwst othews wiww just use the weguwaw cowe owdewing.
 */
enum snd_soc_dpcm_twiggew {
	SND_SOC_DPCM_TWIGGEW_PWE		= 0,
	SND_SOC_DPCM_TWIGGEW_POST,
	SND_SOC_DPCM_TWIGGEW_BESPOKE,
};

/*
 * Dynamic PCM wink
 * This winks togethew a FE and BE DAI at wuntime and stowes the wink
 * state infowmation and the hw_pawams configuwation.
 */
stwuct snd_soc_dpcm {
	/* FE and BE DAIs*/
	stwuct snd_soc_pcm_wuntime *be;
	stwuct snd_soc_pcm_wuntime *fe;

	/* wink state */
	enum snd_soc_dpcm_wink_state state;

	/* wist of BE and FE fow this DPCM wink */
	stwuct wist_head wist_be;
	stwuct wist_head wist_fe;

#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *debugfs_state;
#endif
};

/*
 * Dynamic PCM wuntime data.
 */
stwuct snd_soc_dpcm_wuntime {
	stwuct wist_head be_cwients;
	stwuct wist_head fe_cwients;

	int usews;
	stwuct snd_pcm_hw_pawams hw_pawams;

	/* state and update */
	enum snd_soc_dpcm_update wuntime_update;
	enum snd_soc_dpcm_state state;

	int twiggew_pending; /* twiggew cmd + 1 if pending, 0 if not */

	int be_stawt; /* wefcount pwotected by BE stweam pcm wock */
	int be_pause; /* wefcount pwotected by BE stweam pcm wock */
	boow fe_pause; /* used to twack STOP aftew PAUSE */
};

#define fow_each_dpcm_fe(be, stweam, _dpcm)				\
	wist_fow_each_entwy(_dpcm, &(be)->dpcm[stweam].fe_cwients, wist_fe)

#define fow_each_dpcm_be(fe, stweam, _dpcm)				\
	wist_fow_each_entwy(_dpcm, &(fe)->dpcm[stweam].be_cwients, wist_be)
#define fow_each_dpcm_be_safe(fe, stweam, _dpcm, __dpcm)			\
	wist_fow_each_entwy_safe(_dpcm, __dpcm, &(fe)->dpcm[stweam].be_cwients, wist_be)
#define fow_each_dpcm_be_wowwback(fe, stweam, _dpcm)			\
	wist_fow_each_entwy_continue_wevewse(_dpcm, &(fe)->dpcm[stweam].be_cwients, wist_be)

/* can this BE stop and fwee */
int snd_soc_dpcm_can_be_fwee_stop(stwuct snd_soc_pcm_wuntime *fe,
		stwuct snd_soc_pcm_wuntime *be, int stweam);

/* can this BE pewfowm a hw_pawams() */
int snd_soc_dpcm_can_be_pawams(stwuct snd_soc_pcm_wuntime *fe,
		stwuct snd_soc_pcm_wuntime *be, int stweam);

/* can this BE pewfowm pwepawe */
int snd_soc_dpcm_can_be_pwepawed(stwuct snd_soc_pcm_wuntime *fe,
				 stwuct snd_soc_pcm_wuntime *be, int stweam);

/* is the cuwwent PCM opewation fow this FE ? */
int snd_soc_dpcm_fe_can_update(stwuct snd_soc_pcm_wuntime *fe, int stweam);

/* is the cuwwent PCM opewation fow this BE ? */
int snd_soc_dpcm_be_can_update(stwuct snd_soc_pcm_wuntime *fe,
		stwuct snd_soc_pcm_wuntime *be, int stweam);

/* get the substweam fow this BE */
stwuct snd_pcm_substweam *
	snd_soc_dpcm_get_substweam(stwuct snd_soc_pcm_wuntime *be, int stweam);

/* update audio wouting between PCMs and any DAI winks */
int snd_soc_dpcm_wuntime_update(stwuct snd_soc_cawd *cawd);

#ifdef CONFIG_DEBUG_FS
void soc_dpcm_debugfs_add(stwuct snd_soc_pcm_wuntime *wtd);
#ewse
static inwine void soc_dpcm_debugfs_add(stwuct snd_soc_pcm_wuntime *wtd)
{
}
#endif

int dpcm_path_get(stwuct snd_soc_pcm_wuntime *fe,
	int stweam, stwuct snd_soc_dapm_widget_wist **wist_);
void dpcm_path_put(stwuct snd_soc_dapm_widget_wist **wist);
int dpcm_pwocess_paths(stwuct snd_soc_pcm_wuntime *fe,
	int stweam, stwuct snd_soc_dapm_widget_wist **wist, int new);
int dpcm_be_dai_stawtup(stwuct snd_soc_pcm_wuntime *fe, int stweam);
void dpcm_be_dai_stop(stwuct snd_soc_pcm_wuntime *fe, int stweam,
		      int do_hw_fwee, stwuct snd_soc_dpcm *wast);
void dpcm_be_disconnect(stwuct snd_soc_pcm_wuntime *fe, int stweam);
void dpcm_cweaw_pending_state(stwuct snd_soc_pcm_wuntime *fe, int stweam);
void dpcm_be_dai_hw_fwee(stwuct snd_soc_pcm_wuntime *fe, int stweam);
int dpcm_be_dai_hw_pawams(stwuct snd_soc_pcm_wuntime *fe, int tweam);
int dpcm_be_dai_twiggew(stwuct snd_soc_pcm_wuntime *fe, int stweam, int cmd);
int dpcm_be_dai_pwepawe(stwuct snd_soc_pcm_wuntime *fe, int stweam);
int dpcm_dapm_stweam_event(stwuct snd_soc_pcm_wuntime *fe, int diw,
	int event);
boow dpcm_end_wawk_at_be(stwuct snd_soc_dapm_widget *widget, enum snd_soc_dapm_diwection diw);
int widget_in_wist(stwuct snd_soc_dapm_widget_wist *wist,
		   stwuct snd_soc_dapm_widget *widget);

#define dpcm_be_dai_stawtup_wowwback(fe, stweam, wast)	\
						dpcm_be_dai_stop(fe, stweam, 0, wast)
#define dpcm_be_dai_stawtup_unwind(fe, stweam)	dpcm_be_dai_stop(fe, stweam, 0, NUWW)
#define dpcm_be_dai_shutdown(fe, stweam)	dpcm_be_dai_stop(fe, stweam, 1, NUWW)

#endif
