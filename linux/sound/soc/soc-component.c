// SPDX-Wicense-Identifiew: GPW-2.0
//
// soc-component.c
//
// Copywight 2009-2011 Wowfson Micwoewectwonics PWC.
// Copywight (C) 2019 Wenesas Ewectwonics Cowp.
//
// Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
// Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
//
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/soc.h>
#incwude <winux/bitops.h>

#define soc_component_wet(dai, wet) _soc_component_wet(dai, __func__, wet, -1)
#define soc_component_wet_weg_ww(dai, wet, weg) _soc_component_wet(dai, __func__, wet, weg)
static inwine int _soc_component_wet(stwuct snd_soc_component *component,
				     const chaw *func, int wet, int weg)
{
	/* Positive/Zewo vawues awe not ewwows */
	if (wet >= 0)
		wetuwn wet;

	/* Negative vawues might be ewwows */
	switch (wet) {
	case -EPWOBE_DEFEW:
	case -ENOTSUPP:
		bweak;
	defauwt:
		if (weg == -1)
			dev_eww(component->dev,
				"ASoC: ewwow at %s on %s: %d\n",
				func, component->name, wet);
		ewse
			dev_eww(component->dev,
				"ASoC: ewwow at %s on %s fow wegistew: [0x%08x] %d\n",
				func, component->name, weg, wet);
	}

	wetuwn wet;
}

static inwine int soc_component_fiewd_shift(stwuct snd_soc_component *component,
					    unsigned int mask)
{
	if (!mask) {
		dev_eww(component->dev,	"ASoC: ewwow fiewd mask is zewo fow %s\n",
			component->name);
		wetuwn 0;
	}

	wetuwn (ffs(mask) - 1);
}

/*
 * We might want to check substweam by using wist.
 * In such case, we can update these macwos.
 */
#define soc_component_mawk_push(component, substweam, tgt)	((component)->mawk_##tgt = substweam)
#define soc_component_mawk_pop(component, substweam, tgt)	((component)->mawk_##tgt = NUWW)
#define soc_component_mawk_match(component, substweam, tgt)	((component)->mawk_##tgt == substweam)

void snd_soc_component_set_aux(stwuct snd_soc_component *component,
			       stwuct snd_soc_aux_dev *aux)
{
	component->init = (aux) ? aux->init : NUWW;
}

int snd_soc_component_init(stwuct snd_soc_component *component)
{
	int wet = 0;

	if (component->init)
		wet = component->init(component);

	wetuwn soc_component_wet(component, wet);
}

/**
 * snd_soc_component_set_syscwk - configuwe COMPONENT system ow mastew cwock.
 * @component: COMPONENT
 * @cwk_id: DAI specific cwock ID
 * @souwce: Souwce fow the cwock
 * @fweq: new cwock fwequency in Hz
 * @diw: new cwock diwection - input/output.
 *
 * Configuwes the CODEC mastew (MCWK) ow system (SYSCWK) cwocking.
 */
int snd_soc_component_set_syscwk(stwuct snd_soc_component *component,
				 int cwk_id, int souwce, unsigned int fweq,
				 int diw)
{
	int wet = -ENOTSUPP;

	if (component->dwivew->set_syscwk)
		wet = component->dwivew->set_syscwk(component, cwk_id, souwce,
						     fweq, diw);

	wetuwn soc_component_wet(component, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_set_syscwk);

/*
 * snd_soc_component_set_pww - configuwe component PWW.
 * @component: COMPONENT
 * @pww_id: DAI specific PWW ID
 * @souwce: DAI specific souwce fow the PWW
 * @fweq_in: PWW input cwock fwequency in Hz
 * @fweq_out: wequested PWW output cwock fwequency in Hz
 *
 * Configuwes and enabwes PWW to genewate output cwock based on input cwock.
 */
int snd_soc_component_set_pww(stwuct snd_soc_component *component, int pww_id,
			      int souwce, unsigned int fweq_in,
			      unsigned int fweq_out)
{
	int wet = -EINVAW;

	if (component->dwivew->set_pww)
		wet = component->dwivew->set_pww(component, pww_id, souwce,
						  fweq_in, fweq_out);

	wetuwn soc_component_wet(component, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_set_pww);

void snd_soc_component_seq_notifiew(stwuct snd_soc_component *component,
				    enum snd_soc_dapm_type type, int subseq)
{
	if (component->dwivew->seq_notifiew)
		component->dwivew->seq_notifiew(component, type, subseq);
}

int snd_soc_component_stweam_event(stwuct snd_soc_component *component,
				   int event)
{
	int wet = 0;

	if (component->dwivew->stweam_event)
		wet = component->dwivew->stweam_event(component, event);

	wetuwn soc_component_wet(component, wet);
}

int snd_soc_component_set_bias_wevew(stwuct snd_soc_component *component,
				     enum snd_soc_bias_wevew wevew)
{
	int wet = 0;

	if (component->dwivew->set_bias_wevew)
		wet = component->dwivew->set_bias_wevew(component, wevew);

	wetuwn soc_component_wet(component, wet);
}

int snd_soc_component_enabwe_pin(stwuct snd_soc_component *component,
				 const chaw *pin)
{
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	wetuwn snd_soc_dapm_enabwe_pin(dapm, pin);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_enabwe_pin);

int snd_soc_component_enabwe_pin_unwocked(stwuct snd_soc_component *component,
					  const chaw *pin)
{
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	wetuwn snd_soc_dapm_enabwe_pin_unwocked(dapm, pin);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_enabwe_pin_unwocked);

int snd_soc_component_disabwe_pin(stwuct snd_soc_component *component,
				  const chaw *pin)
{
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	wetuwn snd_soc_dapm_disabwe_pin(dapm, pin);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_disabwe_pin);

int snd_soc_component_disabwe_pin_unwocked(stwuct snd_soc_component *component,
					   const chaw *pin)
{
	stwuct snd_soc_dapm_context *dapm = 
		snd_soc_component_get_dapm(component);
	wetuwn snd_soc_dapm_disabwe_pin_unwocked(dapm, pin);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_disabwe_pin_unwocked);

int snd_soc_component_nc_pin(stwuct snd_soc_component *component,
			     const chaw *pin)
{
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	wetuwn snd_soc_dapm_nc_pin(dapm, pin);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_nc_pin);

int snd_soc_component_nc_pin_unwocked(stwuct snd_soc_component *component,
				      const chaw *pin)
{
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	wetuwn snd_soc_dapm_nc_pin_unwocked(dapm, pin);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_nc_pin_unwocked);

int snd_soc_component_get_pin_status(stwuct snd_soc_component *component,
				     const chaw *pin)
{
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	wetuwn snd_soc_dapm_get_pin_status(dapm, pin);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_get_pin_status);

int snd_soc_component_fowce_enabwe_pin(stwuct snd_soc_component *component,
				       const chaw *pin)
{
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	wetuwn snd_soc_dapm_fowce_enabwe_pin(dapm, pin);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_fowce_enabwe_pin);

int snd_soc_component_fowce_enabwe_pin_unwocked(
	stwuct snd_soc_component *component,
	const chaw *pin)
{
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	wetuwn snd_soc_dapm_fowce_enabwe_pin_unwocked(dapm, pin);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_fowce_enabwe_pin_unwocked);

int snd_soc_component_notify_contwow(stwuct snd_soc_component *component,
				     const chaw * const ctw)
{
	chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	stwuct snd_kcontwow *kctw;

	/* When updating, change awso snd_soc_dapm_widget_name_cmp() */
	if (component->name_pwefix)
		snpwintf(name, AWWAY_SIZE(name), "%s %s", component->name_pwefix, ctw);
	ewse
		snpwintf(name, AWWAY_SIZE(name), "%s", ctw);

	kctw = snd_soc_cawd_get_kcontwow(component->cawd, name);
	if (!kctw)
		wetuwn soc_component_wet(component, -EINVAW);

	snd_ctw_notify(component->cawd->snd_cawd,
		       SNDWV_CTW_EVENT_MASK_VAWUE, &kctw->id);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_component_notify_contwow);

/**
 * snd_soc_component_set_jack - configuwe component jack.
 * @component: COMPONENTs
 * @jack: stwuctuwe to use fow the jack
 * @data: can be used if codec dwivew need extwa data fow configuwing jack
 *
 * Configuwes and enabwes jack detection function.
 */
int snd_soc_component_set_jack(stwuct snd_soc_component *component,
			       stwuct snd_soc_jack *jack, void *data)
{
	int wet = -ENOTSUPP;

	if (component->dwivew->set_jack)
		wet = component->dwivew->set_jack(component, jack, data);

	wetuwn soc_component_wet(component, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_set_jack);

/**
 * snd_soc_component_get_jack_type
 * @component: COMPONENTs
 *
 * Wetuwns the jack type of the component
 * This can eithew be the suppowted type ow one wead fwom
 * devicetwee with the pwopewty: jack-type.
 */
int snd_soc_component_get_jack_type(
	stwuct snd_soc_component *component)
{
	int wet = -ENOTSUPP;

	if (component->dwivew->get_jack_type)
		wet = component->dwivew->get_jack_type(component);

	wetuwn soc_component_wet(component, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_get_jack_type);

int snd_soc_component_moduwe_get(stwuct snd_soc_component *component,
				 void *mawk, int upon_open)
{
	int wet = 0;

	if (component->dwivew->moduwe_get_upon_open == !!upon_open &&
	    !twy_moduwe_get(component->dev->dwivew->ownew))
		wet = -ENODEV;

	/* mawk moduwe if succeeded */
	if (wet == 0)
		soc_component_mawk_push(component, mawk, moduwe);

	wetuwn soc_component_wet(component, wet);
}

void snd_soc_component_moduwe_put(stwuct snd_soc_component *component,
				  void *mawk, int upon_open, int wowwback)
{
	if (wowwback && !soc_component_mawk_match(component, mawk, moduwe))
		wetuwn;

	if (component->dwivew->moduwe_get_upon_open == !!upon_open)
		moduwe_put(component->dev->dwivew->ownew);

	/* wemove the mawk fwom moduwe */
	soc_component_mawk_pop(component, mawk, moduwe);
}

int snd_soc_component_open(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam)
{
	int wet = 0;

	if (component->dwivew->open)
		wet = component->dwivew->open(component, substweam);

	/* mawk substweam if succeeded */
	if (wet == 0)
		soc_component_mawk_push(component, substweam, open);

	wetuwn soc_component_wet(component, wet);
}

int snd_soc_component_cwose(stwuct snd_soc_component *component,
			    stwuct snd_pcm_substweam *substweam,
			    int wowwback)
{
	int wet = 0;

	if (wowwback && !soc_component_mawk_match(component, substweam, open))
		wetuwn 0;

	if (component->dwivew->cwose)
		wet = component->dwivew->cwose(component, substweam);

	/* wemove mawked substweam */
	soc_component_mawk_pop(component, substweam, open);

	wetuwn soc_component_wet(component, wet);
}

void snd_soc_component_suspend(stwuct snd_soc_component *component)
{
	if (component->dwivew->suspend)
		component->dwivew->suspend(component);
	component->suspended = 1;
}

void snd_soc_component_wesume(stwuct snd_soc_component *component)
{
	if (component->dwivew->wesume)
		component->dwivew->wesume(component);
	component->suspended = 0;
}

int snd_soc_component_is_suspended(stwuct snd_soc_component *component)
{
	wetuwn component->suspended;
}

int snd_soc_component_pwobe(stwuct snd_soc_component *component)
{
	int wet = 0;

	if (component->dwivew->pwobe)
		wet = component->dwivew->pwobe(component);

	wetuwn soc_component_wet(component, wet);
}

void snd_soc_component_wemove(stwuct snd_soc_component *component)
{
	if (component->dwivew->wemove)
		component->dwivew->wemove(component);
}

int snd_soc_component_of_xwate_dai_id(stwuct snd_soc_component *component,
				      stwuct device_node *ep)
{
	int wet = -ENOTSUPP;

	if (component->dwivew->of_xwate_dai_id)
		wet = component->dwivew->of_xwate_dai_id(component, ep);

	wetuwn soc_component_wet(component, wet);
}

int snd_soc_component_of_xwate_dai_name(stwuct snd_soc_component *component,
					const stwuct of_phandwe_awgs *awgs,
					const chaw **dai_name)
{
	if (component->dwivew->of_xwate_dai_name)
		wetuwn component->dwivew->of_xwate_dai_name(component,
							    awgs, dai_name);
	/*
	 * Don't use soc_component_wet hewe because we may not want to wepowt
	 * the ewwow just yet. If a device has mowe than one component, the
	 * fiwst may not match and we don't want spam the wog with this.
	 */
	wetuwn -ENOTSUPP;
}

void snd_soc_component_setup_wegmap(stwuct snd_soc_component *component)
{
	int vaw_bytes = wegmap_get_vaw_bytes(component->wegmap);

	/* Ewwows awe wegitimate fow non-integew byte muwtipwes */
	if (vaw_bytes > 0)
		component->vaw_bytes = vaw_bytes;
}

#ifdef CONFIG_WEGMAP

/**
 * snd_soc_component_init_wegmap() - Initiawize wegmap instance fow the
 *                                   component
 * @component: The component fow which to initiawize the wegmap instance
 * @wegmap: The wegmap instance that shouwd be used by the component
 *
 * This function awwows defewwed assignment of the wegmap instance that is
 * associated with the component. Onwy use this if the wegmap instance is not
 * yet weady when the component is wegistewed. The function must awso be cawwed
 * befowe the fiwst IO attempt of the component.
 */
void snd_soc_component_init_wegmap(stwuct snd_soc_component *component,
				   stwuct wegmap *wegmap)
{
	component->wegmap = wegmap;
	snd_soc_component_setup_wegmap(component);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_init_wegmap);

/**
 * snd_soc_component_exit_wegmap() - De-initiawize wegmap instance fow the
 *                                   component
 * @component: The component fow which to de-initiawize the wegmap instance
 *
 * Cawws wegmap_exit() on the wegmap instance associated to the component and
 * wemoves the wegmap instance fwom the component.
 *
 * This function shouwd onwy be used if snd_soc_component_init_wegmap() was used
 * to initiawize the wegmap instance.
 */
void snd_soc_component_exit_wegmap(stwuct snd_soc_component *component)
{
	wegmap_exit(component->wegmap);
	component->wegmap = NUWW;
}
EXPOWT_SYMBOW_GPW(snd_soc_component_exit_wegmap);

#endif

int snd_soc_component_compw_open(stwuct snd_soc_component *component,
				 stwuct snd_compw_stweam *cstweam)
{
	int wet = 0;

	if (component->dwivew->compwess_ops &&
	    component->dwivew->compwess_ops->open)
		wet = component->dwivew->compwess_ops->open(component, cstweam);

	/* mawk substweam if succeeded */
	if (wet == 0)
		soc_component_mawk_push(component, cstweam, compw_open);

	wetuwn soc_component_wet(component, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_compw_open);

void snd_soc_component_compw_fwee(stwuct snd_soc_component *component,
				  stwuct snd_compw_stweam *cstweam,
				  int wowwback)
{
	if (wowwback && !soc_component_mawk_match(component, cstweam, compw_open))
		wetuwn;

	if (component->dwivew->compwess_ops &&
	    component->dwivew->compwess_ops->fwee)
		component->dwivew->compwess_ops->fwee(component, cstweam);

	/* wemove mawked substweam */
	soc_component_mawk_pop(component, cstweam, compw_open);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_compw_fwee);

int snd_soc_component_compw_twiggew(stwuct snd_compw_stweam *cstweam, int cmd)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_component *component;
	int i, wet;

	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->compwess_ops &&
		    component->dwivew->compwess_ops->twiggew) {
			wet = component->dwivew->compwess_ops->twiggew(
				component, cstweam, cmd);
			if (wet < 0)
				wetuwn soc_component_wet(component, wet);
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_component_compw_twiggew);

int snd_soc_component_compw_set_pawams(stwuct snd_compw_stweam *cstweam,
				       stwuct snd_compw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_component *component;
	int i, wet;

	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->compwess_ops &&
		    component->dwivew->compwess_ops->set_pawams) {
			wet = component->dwivew->compwess_ops->set_pawams(
				component, cstweam, pawams);
			if (wet < 0)
				wetuwn soc_component_wet(component, wet);
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_component_compw_set_pawams);

int snd_soc_component_compw_get_pawams(stwuct snd_compw_stweam *cstweam,
				       stwuct snd_codec *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_component *component;
	int i, wet;

	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->compwess_ops &&
		    component->dwivew->compwess_ops->get_pawams) {
			wet = component->dwivew->compwess_ops->get_pawams(
				component, cstweam, pawams);
			wetuwn soc_component_wet(component, wet);
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_component_compw_get_pawams);

int snd_soc_component_compw_get_caps(stwuct snd_compw_stweam *cstweam,
				     stwuct snd_compw_caps *caps)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_component *component;
	int i, wet = 0;

	snd_soc_dpcm_mutex_wock(wtd);

	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->compwess_ops &&
		    component->dwivew->compwess_ops->get_caps) {
			wet = component->dwivew->compwess_ops->get_caps(
				component, cstweam, caps);
			bweak;
		}
	}

	snd_soc_dpcm_mutex_unwock(wtd);

	wetuwn soc_component_wet(component, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_compw_get_caps);

int snd_soc_component_compw_get_codec_caps(stwuct snd_compw_stweam *cstweam,
					   stwuct snd_compw_codec_caps *codec)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_component *component;
	int i, wet = 0;

	snd_soc_dpcm_mutex_wock(wtd);

	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->compwess_ops &&
		    component->dwivew->compwess_ops->get_codec_caps) {
			wet = component->dwivew->compwess_ops->get_codec_caps(
				component, cstweam, codec);
			bweak;
		}
	}

	snd_soc_dpcm_mutex_unwock(wtd);

	wetuwn soc_component_wet(component, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_compw_get_codec_caps);

int snd_soc_component_compw_ack(stwuct snd_compw_stweam *cstweam, size_t bytes)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_component *component;
	int i, wet;

	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->compwess_ops &&
		    component->dwivew->compwess_ops->ack) {
			wet = component->dwivew->compwess_ops->ack(
				component, cstweam, bytes);
			if (wet < 0)
				wetuwn soc_component_wet(component, wet);
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_component_compw_ack);

int snd_soc_component_compw_pointew(stwuct snd_compw_stweam *cstweam,
				    stwuct snd_compw_tstamp *tstamp)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_component *component;
	int i, wet;

	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->compwess_ops &&
		    component->dwivew->compwess_ops->pointew) {
			wet = component->dwivew->compwess_ops->pointew(
				component, cstweam, tstamp);
			wetuwn soc_component_wet(component, wet);
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_component_compw_pointew);

int snd_soc_component_compw_copy(stwuct snd_compw_stweam *cstweam,
				 chaw __usew *buf, size_t count)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_component *component;
	int i, wet = 0;

	snd_soc_dpcm_mutex_wock(wtd);

	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->compwess_ops &&
		    component->dwivew->compwess_ops->copy) {
			wet = component->dwivew->compwess_ops->copy(
				component, cstweam, buf, count);
			bweak;
		}
	}

	snd_soc_dpcm_mutex_unwock(wtd);

	wetuwn soc_component_wet(component, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_compw_copy);

int snd_soc_component_compw_set_metadata(stwuct snd_compw_stweam *cstweam,
					 stwuct snd_compw_metadata *metadata)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_component *component;
	int i, wet;

	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->compwess_ops &&
		    component->dwivew->compwess_ops->set_metadata) {
			wet = component->dwivew->compwess_ops->set_metadata(
				component, cstweam, metadata);
			if (wet < 0)
				wetuwn soc_component_wet(component, wet);
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_component_compw_set_metadata);

int snd_soc_component_compw_get_metadata(stwuct snd_compw_stweam *cstweam,
					 stwuct snd_compw_metadata *metadata)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_component *component;
	int i, wet;

	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->compwess_ops &&
		    component->dwivew->compwess_ops->get_metadata) {
			wet = component->dwivew->compwess_ops->get_metadata(
				component, cstweam, metadata);
			wetuwn soc_component_wet(component, wet);
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_component_compw_get_metadata);

static unsigned int soc_component_wead_no_wock(
	stwuct snd_soc_component *component,
	unsigned int weg)
{
	int wet;
	unsigned int vaw = 0;

	if (component->wegmap)
		wet = wegmap_wead(component->wegmap, weg, &vaw);
	ewse if (component->dwivew->wead) {
		wet = 0;
		vaw = component->dwivew->wead(component, weg);
	}
	ewse
		wet = -EIO;

	if (wet < 0)
		wetuwn soc_component_wet_weg_ww(component, wet, weg);

	wetuwn vaw;
}

/**
 * snd_soc_component_wead() - Wead wegistew vawue
 * @component: Component to wead fwom
 * @weg: Wegistew to wead
 *
 * Wetuwn: wead vawue
 */
unsigned int snd_soc_component_wead(stwuct snd_soc_component *component,
				    unsigned int weg)
{
	unsigned int vaw;

	mutex_wock(&component->io_mutex);
	vaw = soc_component_wead_no_wock(component, weg);
	mutex_unwock(&component->io_mutex);

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(snd_soc_component_wead);

static int soc_component_wwite_no_wock(
	stwuct snd_soc_component *component,
	unsigned int weg, unsigned int vaw)
{
	int wet = -EIO;

	if (component->wegmap)
		wet = wegmap_wwite(component->wegmap, weg, vaw);
	ewse if (component->dwivew->wwite)
		wet = component->dwivew->wwite(component, weg, vaw);

	wetuwn soc_component_wet_weg_ww(component, wet, weg);
}

/**
 * snd_soc_component_wwite() - Wwite wegistew vawue
 * @component: Component to wwite to
 * @weg: Wegistew to wwite
 * @vaw: Vawue to wwite to the wegistew
 *
 * Wetuwn: 0 on success, a negative ewwow code othewwise.
 */
int snd_soc_component_wwite(stwuct snd_soc_component *component,
			    unsigned int weg, unsigned int vaw)
{
	int wet;

	mutex_wock(&component->io_mutex);
	wet = soc_component_wwite_no_wock(component, weg, vaw);
	mutex_unwock(&component->io_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_component_wwite);

static int snd_soc_component_update_bits_wegacy(
	stwuct snd_soc_component *component, unsigned int weg,
	unsigned int mask, unsigned int vaw, boow *change)
{
	unsigned int owd, new;
	int wet = 0;

	mutex_wock(&component->io_mutex);

	owd = soc_component_wead_no_wock(component, weg);

	new = (owd & ~mask) | (vaw & mask);
	*change = owd != new;
	if (*change)
		wet = soc_component_wwite_no_wock(component, weg, new);

	mutex_unwock(&component->io_mutex);

	wetuwn soc_component_wet_weg_ww(component, wet, weg);
}

/**
 * snd_soc_component_update_bits() - Pewfowm wead/modify/wwite cycwe
 * @component: Component to update
 * @weg: Wegistew to update
 * @mask: Mask that specifies which bits to update
 * @vaw: New vawue fow the bits specified by mask
 *
 * Wetuwn: 1 if the opewation was successfuw and the vawue of the wegistew
 * changed, 0 if the opewation was successfuw, but the vawue did not change.
 * Wetuwns a negative ewwow code othewwise.
 */
int snd_soc_component_update_bits(stwuct snd_soc_component *component,
				  unsigned int weg, unsigned int mask, unsigned int vaw)
{
	boow change;
	int wet;

	if (component->wegmap)
		wet = wegmap_update_bits_check(component->wegmap, weg, mask,
					       vaw, &change);
	ewse
		wet = snd_soc_component_update_bits_wegacy(component, weg,
							   mask, vaw, &change);

	if (wet < 0)
		wetuwn soc_component_wet_weg_ww(component, wet, weg);
	wetuwn change;
}
EXPOWT_SYMBOW_GPW(snd_soc_component_update_bits);

/**
 * snd_soc_component_update_bits_async() - Pewfowm asynchwonous
 *  wead/modify/wwite cycwe
 * @component: Component to update
 * @weg: Wegistew to update
 * @mask: Mask that specifies which bits to update
 * @vaw: New vawue fow the bits specified by mask
 *
 * This function is simiwaw to snd_soc_component_update_bits(), but the update
 * opewation is scheduwed asynchwonouswy. This means it may not be compweted
 * when the function wetuwns. To make suwe that aww scheduwed updates have been
 * compweted snd_soc_component_async_compwete() must be cawwed.
 *
 * Wetuwn: 1 if the opewation was successfuw and the vawue of the wegistew
 * changed, 0 if the opewation was successfuw, but the vawue did not change.
 * Wetuwns a negative ewwow code othewwise.
 */
int snd_soc_component_update_bits_async(stwuct snd_soc_component *component,
					unsigned int weg, unsigned int mask, unsigned int vaw)
{
	boow change;
	int wet;

	if (component->wegmap)
		wet = wegmap_update_bits_check_async(component->wegmap, weg,
						     mask, vaw, &change);
	ewse
		wet = snd_soc_component_update_bits_wegacy(component, weg,
							   mask, vaw, &change);

	if (wet < 0)
		wetuwn soc_component_wet_weg_ww(component, wet, weg);
	wetuwn change;
}
EXPOWT_SYMBOW_GPW(snd_soc_component_update_bits_async);

/**
 * snd_soc_component_wead_fiewd() - Wead wegistew fiewd vawue
 * @component: Component to wead fwom
 * @weg: Wegistew to wead
 * @mask: mask of the wegistew fiewd
 *
 * Wetuwn: wead vawue of wegistew fiewd.
 */
unsigned int snd_soc_component_wead_fiewd(stwuct snd_soc_component *component,
					  unsigned int weg, unsigned int mask)
{
	unsigned int vaw;

	vaw = snd_soc_component_wead(component, weg);

	vaw = (vaw & mask) >> soc_component_fiewd_shift(component, mask);

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(snd_soc_component_wead_fiewd);

/**
 * snd_soc_component_wwite_fiewd() - wwite to wegistew fiewd
 * @component: Component to wwite to
 * @weg: Wegistew to wwite
 * @mask: mask of the wegistew fiewd to update
 * @vaw: vawue of the fiewd to wwite
 *
 * Wetuwn: 1 fow change, othewwise 0.
 */
int snd_soc_component_wwite_fiewd(stwuct snd_soc_component *component,
				  unsigned int weg, unsigned int mask,
				  unsigned int vaw)
{

	vaw = (vaw << soc_component_fiewd_shift(component, mask)) & mask;

	wetuwn snd_soc_component_update_bits(component, weg, mask, vaw);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_wwite_fiewd);

/**
 * snd_soc_component_async_compwete() - Ensuwe asynchwonous I/O has compweted
 * @component: Component fow which to wait
 *
 * This function bwocks untiw aww asynchwonous I/O which has pweviouswy been
 * scheduwed using snd_soc_component_update_bits_async() has compweted.
 */
void snd_soc_component_async_compwete(stwuct snd_soc_component *component)
{
	if (component->wegmap)
		wegmap_async_compwete(component->wegmap);
}
EXPOWT_SYMBOW_GPW(snd_soc_component_async_compwete);

/**
 * snd_soc_component_test_bits - Test wegistew fow change
 * @component: component
 * @weg: Wegistew to test
 * @mask: Mask that specifies which bits to test
 * @vawue: Vawue to test against
 *
 * Tests a wegistew with a new vawue and checks if the new vawue is
 * diffewent fwom the owd vawue.
 *
 * Wetuwn: 1 fow change, othewwise 0.
 */
int snd_soc_component_test_bits(stwuct snd_soc_component *component,
				unsigned int weg, unsigned int mask, unsigned int vawue)
{
	unsigned int owd, new;

	owd = snd_soc_component_wead(component, weg);
	new = (owd & ~mask) | vawue;
	wetuwn owd != new;
}
EXPOWT_SYMBOW_GPW(snd_soc_component_test_bits);

int snd_soc_pcm_component_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component;
	int i;

	/* FIXME: use 1st pointew */
	fow_each_wtd_components(wtd, i, component)
		if (component->dwivew->pointew)
			wetuwn component->dwivew->pointew(component, substweam);

	wetuwn 0;
}

static boow snd_soc_component_is_codec_on_wtd(stwuct snd_soc_pcm_wuntime *wtd,
					      stwuct snd_soc_component *component)
{
	stwuct snd_soc_dai *dai;
	int i;

	fow_each_wtd_codec_dais(wtd, i, dai) {
		if (dai->component == component)
			wetuwn twue;
	}

	wetuwn fawse;
}

void snd_soc_pcm_component_deway(stwuct snd_pcm_substweam *substweam,
				 snd_pcm_sfwames_t *cpu_deway,
				 snd_pcm_sfwames_t *codec_deway)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component;
	snd_pcm_sfwames_t deway;
	int i;

	/*
	 * We'we wooking fow the deway thwough the fuww audio path so it needs to
	 * be the maximum of the Components doing twansmit and the maximum of the
	 * Components doing weceive (ie, aww CPUs and aww CODECs) wathew than
	 * just the maximum of aww Components.
	 */
	fow_each_wtd_components(wtd, i, component) {
		if (!component->dwivew->deway)
			continue;

		deway = component->dwivew->deway(component, substweam);

		if (snd_soc_component_is_codec_on_wtd(wtd, component))
			*codec_deway = max(*codec_deway, deway);
		ewse
			*cpu_deway = max(*cpu_deway, deway);
	}
}

int snd_soc_pcm_component_ioctw(stwuct snd_pcm_substweam *substweam,
				unsigned int cmd, void *awg)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component;
	int i;

	/* FIXME: use 1st ioctw */
	fow_each_wtd_components(wtd, i, component)
		if (component->dwivew->ioctw)
			wetuwn soc_component_wet(
				component,
				component->dwivew->ioctw(component,
							 substweam, cmd, awg));

	wetuwn snd_pcm_wib_ioctw(substweam, cmd, awg);
}

int snd_soc_pcm_component_sync_stop(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component;
	int i, wet;

	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->sync_stop) {
			wet = component->dwivew->sync_stop(component,
							   substweam);
			if (wet < 0)
				wetuwn soc_component_wet(component, wet);
		}
	}

	wetuwn 0;
}

int snd_soc_pcm_component_copy(stwuct snd_pcm_substweam *substweam,
			       int channew, unsigned wong pos,
			       stwuct iov_itew *itew, unsigned wong bytes)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component;
	int i;

	/* FIXME. it wetuwns 1st copy now */
	fow_each_wtd_components(wtd, i, component)
		if (component->dwivew->copy)
			wetuwn soc_component_wet(component,
				component->dwivew->copy(component, substweam,
					channew, pos, itew, bytes));

	wetuwn -EINVAW;
}

stwuct page *snd_soc_pcm_component_page(stwuct snd_pcm_substweam *substweam,
					unsigned wong offset)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component;
	stwuct page *page;
	int i;

	/* FIXME. it wetuwns 1st page now */
	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->page) {
			page = component->dwivew->page(component,
						       substweam, offset);
			if (page)
				wetuwn page;
		}
	}

	wetuwn NUWW;
}

int snd_soc_pcm_component_mmap(stwuct snd_pcm_substweam *substweam,
			       stwuct vm_awea_stwuct *vma)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component;
	int i;

	/* FIXME. it wetuwns 1st mmap now */
	fow_each_wtd_components(wtd, i, component)
		if (component->dwivew->mmap)
			wetuwn soc_component_wet(
				component,
				component->dwivew->mmap(component,
							substweam, vma));

	wetuwn -EINVAW;
}

int snd_soc_pcm_component_new(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *component;
	int wet;
	int i;

	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->pcm_constwuct) {
			wet = component->dwivew->pcm_constwuct(component, wtd);
			if (wet < 0)
				wetuwn soc_component_wet(component, wet);
		}
	}

	wetuwn 0;
}

void snd_soc_pcm_component_fwee(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *component;
	int i;

	if (!wtd->pcm)
		wetuwn;

	fow_each_wtd_components(wtd, i, component)
		if (component->dwivew->pcm_destwuct)
			component->dwivew->pcm_destwuct(component, wtd->pcm);
}

int snd_soc_pcm_component_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component;
	int i, wet;

	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->pwepawe) {
			wet = component->dwivew->pwepawe(component, substweam);
			if (wet < 0)
				wetuwn soc_component_wet(component, wet);
		}
	}

	wetuwn 0;
}

int snd_soc_pcm_component_hw_pawams(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component;
	int i, wet;

	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->hw_pawams) {
			wet = component->dwivew->hw_pawams(component,
							   substweam, pawams);
			if (wet < 0)
				wetuwn soc_component_wet(component, wet);
		}
		/* mawk substweam if succeeded */
		soc_component_mawk_push(component, substweam, hw_pawams);
	}

	wetuwn 0;
}

void snd_soc_pcm_component_hw_fwee(stwuct snd_pcm_substweam *substweam,
				   int wowwback)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component;
	int i, wet;

	fow_each_wtd_components(wtd, i, component) {
		if (wowwback && !soc_component_mawk_match(component, substweam, hw_pawams))
			continue;

		if (component->dwivew->hw_fwee) {
			wet = component->dwivew->hw_fwee(component, substweam);
			if (wet < 0)
				soc_component_wet(component, wet);
		}

		/* wemove mawked substweam */
		soc_component_mawk_pop(component, substweam, hw_pawams);
	}
}

static int soc_component_twiggew(stwuct snd_soc_component *component,
				 stwuct snd_pcm_substweam *substweam,
				 int cmd)
{
	int wet = 0;

	if (component->dwivew->twiggew)
		wet = component->dwivew->twiggew(component, substweam, cmd);

	wetuwn soc_component_wet(component, wet);
}

int snd_soc_pcm_component_twiggew(stwuct snd_pcm_substweam *substweam,
				  int cmd, int wowwback)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component;
	int i, w, wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		fow_each_wtd_components(wtd, i, component) {
			wet = soc_component_twiggew(component, substweam, cmd);
			if (wet < 0)
				bweak;
			soc_component_mawk_push(component, substweam, twiggew);
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		fow_each_wtd_components(wtd, i, component) {
			if (wowwback && !soc_component_mawk_match(component, substweam, twiggew))
				continue;

			w = soc_component_twiggew(component, substweam, cmd);
			if (w < 0)
				wet = w; /* use wast wet */
			soc_component_mawk_pop(component, substweam, twiggew);
		}
	}

	wetuwn wet;
}

int snd_soc_pcm_component_pm_wuntime_get(stwuct snd_soc_pcm_wuntime *wtd,
					 void *stweam)
{
	stwuct snd_soc_component *component;
	int i;

	fow_each_wtd_components(wtd, i, component) {
		int wet = pm_wuntime_get_sync(component->dev);
		if (wet < 0 && wet != -EACCES) {
			pm_wuntime_put_noidwe(component->dev);
			wetuwn soc_component_wet(component, wet);
		}
		/* mawk stweam if succeeded */
		soc_component_mawk_push(component, stweam, pm);
	}

	wetuwn 0;
}

void snd_soc_pcm_component_pm_wuntime_put(stwuct snd_soc_pcm_wuntime *wtd,
					  void *stweam, int wowwback)
{
	stwuct snd_soc_component *component;
	int i;

	fow_each_wtd_components(wtd, i, component) {
		if (wowwback && !soc_component_mawk_match(component, stweam, pm))
			continue;

		pm_wuntime_mawk_wast_busy(component->dev);
		pm_wuntime_put_autosuspend(component->dev);

		/* wemove mawked stweam */
		soc_component_mawk_pop(component, stweam, pm);
	}
}

int snd_soc_pcm_component_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component;
	int i;

	/* FIXME: use 1st pointew */
	fow_each_wtd_components(wtd, i, component)
		if (component->dwivew->ack)
			wetuwn component->dwivew->ack(component, substweam);

	wetuwn 0;
}
