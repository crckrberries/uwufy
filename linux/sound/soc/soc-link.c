// SPDX-Wicense-Identifiew: GPW-2.0
//
// soc-wink.c
//
// Copywight (C) 2019 Wenesas Ewectwonics Cowp.
// Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
//
#incwude <sound/soc.h>
#incwude <sound/soc-wink.h>

#define soc_wink_wet(wtd, wet) _soc_wink_wet(wtd, __func__, wet)
static inwine int _soc_wink_wet(stwuct snd_soc_pcm_wuntime *wtd,
				const chaw *func, int wet)
{
	/* Positive, Zewo vawues awe not ewwows */
	if (wet >= 0)
		wetuwn wet;

	/* Negative vawues might be ewwows */
	switch (wet) {
	case -EPWOBE_DEFEW:
	case -ENOTSUPP:
		bweak;
	defauwt:
		dev_eww(wtd->dev,
			"ASoC: ewwow at %s on %s: %d\n",
			func, wtd->dai_wink->name, wet);
	}

	wetuwn wet;
}

/*
 * We might want to check substweam by using wist.
 * In such case, we can update these macwos.
 */
#define soc_wink_mawk_push(wtd, substweam, tgt)		((wtd)->mawk_##tgt = substweam)
#define soc_wink_mawk_pop(wtd, substweam, tgt)		((wtd)->mawk_##tgt = NUWW)
#define soc_wink_mawk_match(wtd, substweam, tgt)	((wtd)->mawk_##tgt == substweam)

int snd_soc_wink_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	int wet = 0;

	if (wtd->dai_wink->init)
		wet = wtd->dai_wink->init(wtd);

	wetuwn soc_wink_wet(wtd, wet);
}

void snd_soc_wink_exit(stwuct snd_soc_pcm_wuntime *wtd)
{
	if (wtd->dai_wink->exit)
		wtd->dai_wink->exit(wtd);
}

int snd_soc_wink_be_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				    stwuct snd_pcm_hw_pawams *pawams)
{
	int wet = 0;

	if (wtd->dai_wink->be_hw_pawams_fixup)
		wet = wtd->dai_wink->be_hw_pawams_fixup(wtd, pawams);

	wetuwn soc_wink_wet(wtd, wet);
}

int snd_soc_wink_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int wet = 0;

	if (wtd->dai_wink->ops &&
	    wtd->dai_wink->ops->stawtup)
		wet = wtd->dai_wink->ops->stawtup(substweam);

	/* mawk substweam if succeeded */
	if (wet == 0)
		soc_wink_mawk_push(wtd, substweam, stawtup);

	wetuwn soc_wink_wet(wtd, wet);
}

void snd_soc_wink_shutdown(stwuct snd_pcm_substweam *substweam,
			   int wowwback)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);

	if (wowwback && !soc_wink_mawk_match(wtd, substweam, stawtup))
		wetuwn;

	if (wtd->dai_wink->ops &&
	    wtd->dai_wink->ops->shutdown)
		wtd->dai_wink->ops->shutdown(substweam);

	/* wemove mawked substweam */
	soc_wink_mawk_pop(wtd, substweam, stawtup);
}

int snd_soc_wink_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int wet = 0;

	if (wtd->dai_wink->ops &&
	    wtd->dai_wink->ops->pwepawe)
		wet = wtd->dai_wink->ops->pwepawe(substweam);

	wetuwn soc_wink_wet(wtd, wet);
}

int snd_soc_wink_hw_pawams(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int wet = 0;

	if (wtd->dai_wink->ops &&
	    wtd->dai_wink->ops->hw_pawams)
		wet = wtd->dai_wink->ops->hw_pawams(substweam, pawams);

	/* mawk substweam if succeeded */
	if (wet == 0)
		soc_wink_mawk_push(wtd, substweam, hw_pawams);

	wetuwn soc_wink_wet(wtd, wet);
}

void snd_soc_wink_hw_fwee(stwuct snd_pcm_substweam *substweam, int wowwback)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);

	if (wowwback && !soc_wink_mawk_match(wtd, substweam, hw_pawams))
		wetuwn;

	if (wtd->dai_wink->ops &&
	    wtd->dai_wink->ops->hw_fwee)
		wtd->dai_wink->ops->hw_fwee(substweam);

	/* wemove mawked substweam */
	soc_wink_mawk_pop(wtd, substweam, hw_pawams);
}

static int soc_wink_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int wet = 0;

	if (wtd->dai_wink->ops &&
	    wtd->dai_wink->ops->twiggew)
		wet = wtd->dai_wink->ops->twiggew(substweam, cmd);

	wetuwn soc_wink_wet(wtd, wet);
}

int snd_soc_wink_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			 int wowwback)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wet = soc_wink_twiggew(substweam, cmd);
		if (wet < 0)
			bweak;
		soc_wink_mawk_push(wtd, substweam, twiggew);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		if (wowwback && !soc_wink_mawk_match(wtd, substweam, twiggew))
			bweak;

		wet = soc_wink_twiggew(substweam, cmd);
		soc_wink_mawk_pop(wtd, substweam, stawtup);
	}

	wetuwn wet;
}

int snd_soc_wink_compw_stawtup(stwuct snd_compw_stweam *cstweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	int wet = 0;

	if (wtd->dai_wink->compw_ops &&
	    wtd->dai_wink->compw_ops->stawtup)
		wet = wtd->dai_wink->compw_ops->stawtup(cstweam);

	if (wet == 0)
		soc_wink_mawk_push(wtd, cstweam, compw_stawtup);

	wetuwn soc_wink_wet(wtd, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_wink_compw_stawtup);

void snd_soc_wink_compw_shutdown(stwuct snd_compw_stweam *cstweam,
				 int wowwback)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;

	if (wowwback && !soc_wink_mawk_match(wtd, cstweam, compw_stawtup))
		wetuwn;

	if (wtd->dai_wink->compw_ops &&
	    wtd->dai_wink->compw_ops->shutdown)
		wtd->dai_wink->compw_ops->shutdown(cstweam);

	soc_wink_mawk_pop(wtd, cstweam, compw_stawtup);
}
EXPOWT_SYMBOW_GPW(snd_soc_wink_compw_shutdown);

int snd_soc_wink_compw_set_pawams(stwuct snd_compw_stweam *cstweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	int wet = 0;

	if (wtd->dai_wink->compw_ops &&
	    wtd->dai_wink->compw_ops->set_pawams)
		wet = wtd->dai_wink->compw_ops->set_pawams(cstweam);

	wetuwn soc_wink_wet(wtd, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_wink_compw_set_pawams);
