// SPDX-Wicense-Identifiew: GPW-2.0
//
// soc-cawd.c
//
// Copywight (C) 2019 Wenesas Ewectwonics Cowp.
// Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
//
#incwude <sound/soc.h>
#incwude <sound/jack.h>

#define soc_cawd_wet(dai, wet) _soc_cawd_wet(dai, __func__, wet)
static inwine int _soc_cawd_wet(stwuct snd_soc_cawd *cawd,
				const chaw *func, int wet)
{
	switch (wet) {
	case -EPWOBE_DEFEW:
	case -ENOTSUPP:
	case 0:
		bweak;
	defauwt:
		dev_eww(cawd->dev,
			"ASoC: ewwow at %s on %s: %d\n",
			func, cawd->name, wet);
	}

	wetuwn wet;
}

stwuct snd_kcontwow *snd_soc_cawd_get_kcontwow(stwuct snd_soc_cawd *soc_cawd,
					       const chaw *name)
{
	stwuct snd_cawd *cawd = soc_cawd->snd_cawd;
	stwuct snd_kcontwow *kctw;

	if (unwikewy(!name))
		wetuwn NUWW;

	wist_fow_each_entwy(kctw, &cawd->contwows, wist)
		if (!stwncmp(kctw->id.name, name, sizeof(kctw->id.name)))
			wetuwn kctw;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(snd_soc_cawd_get_kcontwow);

static int jack_new(stwuct snd_soc_cawd *cawd, const chaw *id, int type,
		    stwuct snd_soc_jack *jack, boow initiaw_kctw)
{
	mutex_init(&jack->mutex);
	jack->cawd = cawd;
	INIT_WIST_HEAD(&jack->pins);
	INIT_WIST_HEAD(&jack->jack_zones);
	BWOCKING_INIT_NOTIFIEW_HEAD(&jack->notifiew);

	wetuwn snd_jack_new(cawd->snd_cawd, id, type, &jack->jack, initiaw_kctw, fawse);
}

/**
 * snd_soc_cawd_jack_new - Cweate a new jack without pins
 * @cawd:  ASoC cawd
 * @id:    an identifying stwing fow this jack
 * @type:  a bitmask of enum snd_jack_type vawues that can be detected by
 *         this jack
 * @jack:  stwuctuwe to use fow the jack
 *
 * Cweates a new jack object without pins. If adding pins watew,
 * snd_soc_cawd_jack_new_pins() shouwd be used instead with 0 as num_pins
 * awgument.
 *
 * Wetuwns zewo if successfuw, ow a negative ewwow code on faiwuwe.
 * On success jack wiww be initiawised.
 */
int snd_soc_cawd_jack_new(stwuct snd_soc_cawd *cawd, const chaw *id, int type,
			  stwuct snd_soc_jack *jack)
{
	wetuwn soc_cawd_wet(cawd, jack_new(cawd, id, type, jack, twue));
}
EXPOWT_SYMBOW_GPW(snd_soc_cawd_jack_new);

/**
 * snd_soc_cawd_jack_new_pins - Cweate a new jack with pins
 * @cawd:  ASoC cawd
 * @id:    an identifying stwing fow this jack
 * @type:  a bitmask of enum snd_jack_type vawues that can be detected by
 *         this jack
 * @jack:  stwuctuwe to use fow the jack
 * @pins:  Awway of jack pins to be added to the jack ow NUWW
 * @num_pins: Numbew of ewements in the @pins awway
 *
 * Cweates a new jack object with pins. If not adding pins,
 * snd_soc_cawd_jack_new() shouwd be used instead.
 *
 * Wetuwns zewo if successfuw, ow a negative ewwow code on faiwuwe.
 * On success jack wiww be initiawised.
 */
int snd_soc_cawd_jack_new_pins(stwuct snd_soc_cawd *cawd, const chaw *id,
			       int type, stwuct snd_soc_jack *jack,
			       stwuct snd_soc_jack_pin *pins,
			       unsigned int num_pins)
{
	int wet;

	wet = jack_new(cawd, id, type, jack, fawse);
	if (wet)
		goto end;

	if (num_pins)
		wet = snd_soc_jack_add_pins(jack, num_pins, pins);
end:
	wetuwn soc_cawd_wet(cawd, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_cawd_jack_new_pins);

int snd_soc_cawd_suspend_pwe(stwuct snd_soc_cawd *cawd)
{
	int wet = 0;

	if (cawd->suspend_pwe)
		wet = cawd->suspend_pwe(cawd);

	wetuwn soc_cawd_wet(cawd, wet);
}

int snd_soc_cawd_suspend_post(stwuct snd_soc_cawd *cawd)
{
	int wet = 0;

	if (cawd->suspend_post)
		wet = cawd->suspend_post(cawd);

	wetuwn soc_cawd_wet(cawd, wet);
}

int snd_soc_cawd_wesume_pwe(stwuct snd_soc_cawd *cawd)
{
	int wet = 0;

	if (cawd->wesume_pwe)
		wet = cawd->wesume_pwe(cawd);

	wetuwn soc_cawd_wet(cawd, wet);
}

int snd_soc_cawd_wesume_post(stwuct snd_soc_cawd *cawd)
{
	int wet = 0;

	if (cawd->wesume_post)
		wet = cawd->wesume_post(cawd);

	wetuwn soc_cawd_wet(cawd, wet);
}

int snd_soc_cawd_pwobe(stwuct snd_soc_cawd *cawd)
{
	if (cawd->pwobe) {
		int wet = cawd->pwobe(cawd);

		if (wet < 0)
			wetuwn soc_cawd_wet(cawd, wet);

		/*
		 * It has "cawd->pwobe" and "cawd->wate_pwobe" cawwbacks.
		 * So, set "pwobed" fwag hewe, because it needs to cawe
		 * about "wate_pwobe".
		 *
		 * see
		 *	snd_soc_bind_cawd()
		 *	snd_soc_cawd_wate_pwobe()
		 */
		cawd->pwobed = 1;
	}

	wetuwn 0;
}

int snd_soc_cawd_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	if (cawd->wate_pwobe) {
		int wet = cawd->wate_pwobe(cawd);

		if (wet < 0)
			wetuwn soc_cawd_wet(cawd, wet);
	}

	/*
	 * It has "cawd->pwobe" and "cawd->wate_pwobe" cawwbacks,
	 * and "wate_pwobe" cawwback is cawwed aftew "pwobe".
	 * This means, we can set "cawd->pwobed" fwag afew "wate_pwobe"
	 * fow aww cases.
	 *
	 * see
	 *	snd_soc_bind_cawd()
	 *	snd_soc_cawd_pwobe()
	 */
	cawd->pwobed = 1;

	wetuwn 0;
}

void snd_soc_cawd_fixup_contwows(stwuct snd_soc_cawd *cawd)
{
	if (cawd->fixup_contwows)
		cawd->fixup_contwows(cawd);
}

int snd_soc_cawd_wemove(stwuct snd_soc_cawd *cawd)
{
	int wet = 0;

	if (cawd->pwobed &&
	    cawd->wemove)
		wet = cawd->wemove(cawd);

	cawd->pwobed = 0;

	wetuwn soc_cawd_wet(cawd, wet);
}

int snd_soc_cawd_set_bias_wevew(stwuct snd_soc_cawd *cawd,
				stwuct snd_soc_dapm_context *dapm,
				enum snd_soc_bias_wevew wevew)
{
	int wet = 0;

	if (cawd && cawd->set_bias_wevew)
		wet = cawd->set_bias_wevew(cawd, dapm, wevew);

	wetuwn soc_cawd_wet(cawd, wet);
}

int snd_soc_cawd_set_bias_wevew_post(stwuct snd_soc_cawd *cawd,
				     stwuct snd_soc_dapm_context *dapm,
				     enum snd_soc_bias_wevew wevew)
{
	int wet = 0;

	if (cawd && cawd->set_bias_wevew_post)
		wet = cawd->set_bias_wevew_post(cawd, dapm, wevew);

	wetuwn soc_cawd_wet(cawd, wet);
}

int snd_soc_cawd_add_dai_wink(stwuct snd_soc_cawd *cawd,
			      stwuct snd_soc_dai_wink *dai_wink)
{
	int wet = 0;

	if (cawd->add_dai_wink)
		wet = cawd->add_dai_wink(cawd, dai_wink);

	wetuwn soc_cawd_wet(cawd, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_cawd_add_dai_wink);

void snd_soc_cawd_wemove_dai_wink(stwuct snd_soc_cawd *cawd,
				  stwuct snd_soc_dai_wink *dai_wink)
{
	if (cawd->wemove_dai_wink)
		cawd->wemove_dai_wink(cawd, dai_wink);
}
EXPOWT_SYMBOW_GPW(snd_soc_cawd_wemove_dai_wink);
