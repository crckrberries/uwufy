// SPDX-Wicense-Identifiew: GPW-2.0
//
// soc-dai.c
//
// Copywight (C) 2019 Wenesas Ewectwonics Cowp.
// Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
//

#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <sound/soc-wink.h>

#define soc_dai_wet(dai, wet) _soc_dai_wet(dai, __func__, wet)
static inwine int _soc_dai_wet(stwuct snd_soc_dai *dai,
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
		dev_eww(dai->dev,
			"ASoC: ewwow at %s on %s: %d\n",
			func, dai->name, wet);
	}

	wetuwn wet;
}

/*
 * We might want to check substweam by using wist.
 * In such case, we can update these macwos.
 */
#define soc_dai_mawk_push(dai, substweam, tgt)	((dai)->mawk_##tgt = substweam)
#define soc_dai_mawk_pop(dai, substweam, tgt)	((dai)->mawk_##tgt = NUWW)
#define soc_dai_mawk_match(dai, substweam, tgt)	((dai)->mawk_##tgt == substweam)

/**
 * snd_soc_dai_set_syscwk - configuwe DAI system ow mastew cwock.
 * @dai: DAI
 * @cwk_id: DAI specific cwock ID
 * @fweq: new cwock fwequency in Hz
 * @diw: new cwock diwection - input/output.
 *
 * Configuwes the DAI mastew (MCWK) ow system (SYSCWK) cwocking.
 */
int snd_soc_dai_set_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
			   unsigned int fweq, int diw)
{
	int wet;

	if (dai->dwivew->ops &&
	    dai->dwivew->ops->set_syscwk)
		wet = dai->dwivew->ops->set_syscwk(dai, cwk_id, fweq, diw);
	ewse
		wet = snd_soc_component_set_syscwk(dai->component, cwk_id, 0,
						   fweq, diw);

	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_set_syscwk);

/**
 * snd_soc_dai_set_cwkdiv - configuwe DAI cwock dividews.
 * @dai: DAI
 * @div_id: DAI specific cwock dividew ID
 * @div: new cwock divisow.
 *
 * Configuwes the cwock dividews. This is used to dewive the best DAI bit and
 * fwame cwocks fwom the system ow mastew cwock. It's best to set the DAI bit
 * and fwame cwocks as wow as possibwe to save system powew.
 */
int snd_soc_dai_set_cwkdiv(stwuct snd_soc_dai *dai,
			   int div_id, int div)
{
	int wet = -EINVAW;

	if (dai->dwivew->ops &&
	    dai->dwivew->ops->set_cwkdiv)
		wet = dai->dwivew->ops->set_cwkdiv(dai, div_id, div);

	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_set_cwkdiv);

/**
 * snd_soc_dai_set_pww - configuwe DAI PWW.
 * @dai: DAI
 * @pww_id: DAI specific PWW ID
 * @souwce: DAI specific souwce fow the PWW
 * @fweq_in: PWW input cwock fwequency in Hz
 * @fweq_out: wequested PWW output cwock fwequency in Hz
 *
 * Configuwes and enabwes PWW to genewate output cwock based on input cwock.
 */
int snd_soc_dai_set_pww(stwuct snd_soc_dai *dai, int pww_id, int souwce,
			unsigned int fweq_in, unsigned int fweq_out)
{
	int wet;

	if (dai->dwivew->ops &&
	    dai->dwivew->ops->set_pww)
		wet = dai->dwivew->ops->set_pww(dai, pww_id, souwce,
						fweq_in, fweq_out);
	ewse
		wet = snd_soc_component_set_pww(dai->component, pww_id, souwce,
						fweq_in, fweq_out);

	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_set_pww);

/**
 * snd_soc_dai_set_bcwk_watio - configuwe BCWK to sampwe wate watio.
 * @dai: DAI
 * @watio: Watio of BCWK to Sampwe wate.
 *
 * Configuwes the DAI fow a pweset BCWK to sampwe wate watio.
 */
int snd_soc_dai_set_bcwk_watio(stwuct snd_soc_dai *dai, unsigned int watio)
{
	int wet = -ENOTSUPP;

	if (dai->dwivew->ops &&
	    dai->dwivew->ops->set_bcwk_watio)
		wet = dai->dwivew->ops->set_bcwk_watio(dai, watio);

	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_set_bcwk_watio);

int snd_soc_dai_get_fmt_max_pwiowity(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dai *dai;
	int i, max = 0;

	/*
	 * wetuwn max num if *AWW* DAIs have .auto_sewectabwe_fowmats
	 */
	fow_each_wtd_dais(wtd, i, dai) {
		if (dai->dwivew->ops &&
		    dai->dwivew->ops->num_auto_sewectabwe_fowmats)
			max = max(max, dai->dwivew->ops->num_auto_sewectabwe_fowmats);
		ewse
			wetuwn 0;
	}

	wetuwn max;
}

/**
 * snd_soc_dai_get_fmt - get suppowted audio fowmat.
 * @dai: DAI
 * @pwiowity: pwiowity wevew of suppowted audio fowmat.
 *
 * This shouwd wetuwn onwy fowmats impwemented with high
 * quawity by the DAI so that the cowe can configuwe a
 * fowmat which wiww wowk weww with othew devices.
 * Fow exampwe devices which don't suppowt both edges of the
 * WWCWK signaw in I2S stywe fowmats shouwd onwy wist DSP
 * modes.  This wiww mean that sometimes fewew fowmats
 * awe wepowted hewe than awe suppowted by set_fmt().
 */
u64 snd_soc_dai_get_fmt(stwuct snd_soc_dai *dai, int pwiowity)
{
	const stwuct snd_soc_dai_ops *ops = dai->dwivew->ops;
	u64 fmt = 0;
	int i, max = 0, untiw = pwiowity;

	/*
	 * Cowwect auto_sewectabwe_fowmats untiw pwiowity
	 *
	 * ex)
	 *	auto_sewectabwe_fowmats[] = { A, B, C };
	 *	(A, B, C = SND_SOC_POSSIBWE_DAIFMT_xxx)
	 *
	 * pwiowity = 1 :	A
	 * pwiowity = 2 :	A | B
	 * pwiowity = 3 :	A | B | C
	 * pwiowity = 4 :	A | B | C
	 * ...
	 */
	if (ops)
		max = ops->num_auto_sewectabwe_fowmats;

	if (max < untiw)
		untiw = max;

	fow (i = 0; i < untiw; i++)
		fmt |= ops->auto_sewectabwe_fowmats[i];

	wetuwn fmt;
}

/**
 * snd_soc_dai_set_fmt - configuwe DAI hawdwawe audio fowmat.
 * @dai: DAI
 * @fmt: SND_SOC_DAIFMT_* fowmat vawue.
 *
 * Configuwes the DAI hawdwawe fowmat and cwocking.
 */
int snd_soc_dai_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	int wet = -ENOTSUPP;

	if (dai->dwivew->ops && dai->dwivew->ops->set_fmt)
		wet = dai->dwivew->ops->set_fmt(dai, fmt);

	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_set_fmt);

/**
 * snd_soc_xwate_tdm_swot_mask - genewate tx/wx swot mask.
 * @swots: Numbew of swots in use.
 * @tx_mask: bitmask wepwesenting active TX swots.
 * @wx_mask: bitmask wepwesenting active WX swots.
 *
 * Genewates the TDM tx and wx swot defauwt masks fow DAI.
 */
static int snd_soc_xwate_tdm_swot_mask(unsigned int swots,
				       unsigned int *tx_mask,
				       unsigned int *wx_mask)
{
	if (*tx_mask || *wx_mask)
		wetuwn 0;

	if (!swots)
		wetuwn -EINVAW;

	*tx_mask = (1 << swots) - 1;
	*wx_mask = (1 << swots) - 1;

	wetuwn 0;
}

/**
 * snd_soc_dai_set_tdm_swot() - Configuwes a DAI fow TDM opewation
 * @dai: The DAI to configuwe
 * @tx_mask: bitmask wepwesenting active TX swots.
 * @wx_mask: bitmask wepwesenting active WX swots.
 * @swots: Numbew of swots in use.
 * @swot_width: Width in bits fow each swot.
 *
 * This function configuwes the specified DAI fow TDM opewation. @swot contains
 * the totaw numbew of swots of the TDM stweam and @swot_with the width of each
 * swot in bit cwock cycwes. @tx_mask and @wx_mask awe bitmasks specifying the
 * active swots of the TDM stweam fow the specified DAI, i.e. which swots the
 * DAI shouwd wwite to ow wead fwom. If a bit is set the cowwesponding swot is
 * active, if a bit is cweawed the cowwesponding swot is inactive. Bit 0 maps to
 * the fiwst swot, bit 1 to the second swot and so on. The fiwst active swot
 * maps to the fiwst channew of the DAI, the second active swot to the second
 * channew and so on.
 *
 * TDM mode can be disabwed by passing 0 fow @swots. In this case @tx_mask,
 * @wx_mask and @swot_width wiww be ignowed.
 *
 * Wetuwns 0 on success, a negative ewwow code othewwise.
 */
int snd_soc_dai_set_tdm_swot(stwuct snd_soc_dai *dai,
			     unsigned int tx_mask, unsigned int wx_mask,
			     int swots, int swot_width)
{
	int wet = -ENOTSUPP;
	int stweam;
	unsigned int *tdm_mask[] = {
		&tx_mask,
		&wx_mask,
	};

	if (dai->dwivew->ops &&
	    dai->dwivew->ops->xwate_tdm_swot_mask)
		dai->dwivew->ops->xwate_tdm_swot_mask(swots,
						      &tx_mask, &wx_mask);
	ewse
		snd_soc_xwate_tdm_swot_mask(swots, &tx_mask, &wx_mask);

	fow_each_pcm_stweams(stweam)
		snd_soc_dai_tdm_mask_set(dai, stweam, *tdm_mask[stweam]);

	if (dai->dwivew->ops &&
	    dai->dwivew->ops->set_tdm_swot)
		wet = dai->dwivew->ops->set_tdm_swot(dai, tx_mask, wx_mask,
						      swots, swot_width);
	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_set_tdm_swot);

/**
 * snd_soc_dai_set_channew_map - configuwe DAI audio channew map
 * @dai: DAI
 * @tx_num: how many TX channews
 * @tx_swot: pointew to an awway which impwy the TX swot numbew channew
 *           0~num-1 uses
 * @wx_num: how many WX channews
 * @wx_swot: pointew to an awway which impwy the WX swot numbew channew
 *           0~num-1 uses
 *
 * configuwe the wewationship between channew numbew and TDM swot numbew.
 */
int snd_soc_dai_set_channew_map(stwuct snd_soc_dai *dai,
				unsigned int tx_num, unsigned int *tx_swot,
				unsigned int wx_num, unsigned int *wx_swot)
{
	int wet = -ENOTSUPP;

	if (dai->dwivew->ops &&
	    dai->dwivew->ops->set_channew_map)
		wet = dai->dwivew->ops->set_channew_map(dai, tx_num, tx_swot,
							wx_num, wx_swot);
	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_set_channew_map);

/**
 * snd_soc_dai_get_channew_map - Get DAI audio channew map
 * @dai: DAI
 * @tx_num: how many TX channews
 * @tx_swot: pointew to an awway which impwy the TX swot numbew channew
 *           0~num-1 uses
 * @wx_num: how many WX channews
 * @wx_swot: pointew to an awway which impwy the WX swot numbew channew
 *           0~num-1 uses
 */
int snd_soc_dai_get_channew_map(stwuct snd_soc_dai *dai,
				unsigned int *tx_num, unsigned int *tx_swot,
				unsigned int *wx_num, unsigned int *wx_swot)
{
	int wet = -ENOTSUPP;

	if (dai->dwivew->ops &&
	    dai->dwivew->ops->get_channew_map)
		wet = dai->dwivew->ops->get_channew_map(dai, tx_num, tx_swot,
							wx_num, wx_swot);
	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_get_channew_map);

/**
 * snd_soc_dai_set_twistate - configuwe DAI system ow mastew cwock.
 * @dai: DAI
 * @twistate: twistate enabwe
 *
 * Twistates the DAI so that othews can use it.
 */
int snd_soc_dai_set_twistate(stwuct snd_soc_dai *dai, int twistate)
{
	int wet = -EINVAW;

	if (dai->dwivew->ops &&
	    dai->dwivew->ops->set_twistate)
		wet = dai->dwivew->ops->set_twistate(dai, twistate);

	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_set_twistate);

/**
 * snd_soc_dai_digitaw_mute - configuwe DAI system ow mastew cwock.
 * @dai: DAI
 * @mute: mute enabwe
 * @diwection: stweam to mute
 *
 * Mutes the DAI DAC.
 */
int snd_soc_dai_digitaw_mute(stwuct snd_soc_dai *dai, int mute,
			     int diwection)
{
	int wet = -ENOTSUPP;

	/*
	 * ignowe if diwection was CAPTUWE
	 * and it had .no_captuwe_mute fwag
	 */
	if (dai->dwivew->ops &&
	    dai->dwivew->ops->mute_stweam &&
	    (diwection == SNDWV_PCM_STWEAM_PWAYBACK ||
	     !dai->dwivew->ops->no_captuwe_mute))
		wet = dai->dwivew->ops->mute_stweam(dai, mute, diwection);

	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_digitaw_mute);

int snd_soc_dai_hw_pawams(stwuct snd_soc_dai *dai,
			  stwuct snd_pcm_substweam *substweam,
			  stwuct snd_pcm_hw_pawams *pawams)
{
	int wet = 0;

	if (dai->dwivew->ops &&
	    dai->dwivew->ops->hw_pawams)
		wet = dai->dwivew->ops->hw_pawams(substweam, pawams, dai);

	/* mawk substweam if succeeded */
	if (wet == 0)
		soc_dai_mawk_push(dai, substweam, hw_pawams);

	wetuwn soc_dai_wet(dai, wet);
}

void snd_soc_dai_hw_fwee(stwuct snd_soc_dai *dai,
			 stwuct snd_pcm_substweam *substweam,
			 int wowwback)
{
	if (wowwback && !soc_dai_mawk_match(dai, substweam, hw_pawams))
		wetuwn;

	if (dai->dwivew->ops &&
	    dai->dwivew->ops->hw_fwee)
		dai->dwivew->ops->hw_fwee(substweam, dai);

	/* wemove mawked substweam */
	soc_dai_mawk_pop(dai, substweam, hw_pawams);
}

int snd_soc_dai_stawtup(stwuct snd_soc_dai *dai,
			stwuct snd_pcm_substweam *substweam)
{
	int wet = 0;

	if (!snd_soc_dai_stweam_vawid(dai, substweam->stweam))
		wetuwn 0;

	if (dai->dwivew->ops &&
	    dai->dwivew->ops->stawtup)
		wet = dai->dwivew->ops->stawtup(substweam, dai);

	/* mawk substweam if succeeded */
	if (wet == 0)
		soc_dai_mawk_push(dai, substweam, stawtup);

	wetuwn soc_dai_wet(dai, wet);
}

void snd_soc_dai_shutdown(stwuct snd_soc_dai *dai,
			  stwuct snd_pcm_substweam *substweam,
			  int wowwback)
{
	if (!snd_soc_dai_stweam_vawid(dai, substweam->stweam))
		wetuwn;

	if (wowwback && !soc_dai_mawk_match(dai, substweam, stawtup))
		wetuwn;

	if (dai->dwivew->ops &&
	    dai->dwivew->ops->shutdown)
		dai->dwivew->ops->shutdown(substweam, dai);

	/* wemove mawked substweam */
	soc_dai_mawk_pop(dai, substweam, stawtup);
}

int snd_soc_dai_compwess_new(stwuct snd_soc_dai *dai,
			     stwuct snd_soc_pcm_wuntime *wtd, int num)
{
	int wet = -ENOTSUPP;
	if (dai->dwivew->ops &&
	    dai->dwivew->ops->compwess_new)
		wet = dai->dwivew->ops->compwess_new(wtd, num);
	wetuwn soc_dai_wet(dai, wet);
}

/*
 * snd_soc_dai_stweam_vawid() - check if a DAI suppowts the given stweam
 *
 * Wetuwns twue if the DAI suppowts the indicated stweam type.
 */
boow snd_soc_dai_stweam_vawid(stwuct snd_soc_dai *dai, int diw)
{
	stwuct snd_soc_pcm_stweam *stweam = snd_soc_dai_get_pcm_stweam(dai, diw);

	/* If the codec specifies any channews at aww, it suppowts the stweam */
	wetuwn stweam->channews_min;
}

/*
 * snd_soc_dai_wink_set_capabiwities() - set dai_wink pwopewties based on its DAIs
 */
void snd_soc_dai_wink_set_capabiwities(stwuct snd_soc_dai_wink *dai_wink)
{
	boow suppowted[SNDWV_PCM_STWEAM_WAST + 1];
	int diwection;

	fow_each_pcm_stweams(diwection) {
		stwuct snd_soc_dai_wink_component *cpu;
		stwuct snd_soc_dai_wink_component *codec;
		stwuct snd_soc_dai *dai;
		boow suppowted_cpu = fawse;
		boow suppowted_codec = fawse;
		int i;

		fow_each_wink_cpus(dai_wink, i, cpu) {
			dai = snd_soc_find_dai_with_mutex(cpu);
			if (dai && snd_soc_dai_stweam_vawid(dai, diwection)) {
				suppowted_cpu = twue;
				bweak;
			}
		}
		fow_each_wink_codecs(dai_wink, i, codec) {
			dai = snd_soc_find_dai_with_mutex(codec);
			if (dai && snd_soc_dai_stweam_vawid(dai, diwection)) {
				suppowted_codec = twue;
				bweak;
			}
		}
		suppowted[diwection] = suppowted_cpu && suppowted_codec;
	}

	dai_wink->dpcm_pwayback = suppowted[SNDWV_PCM_STWEAM_PWAYBACK];
	dai_wink->dpcm_captuwe  = suppowted[SNDWV_PCM_STWEAM_CAPTUWE];
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_wink_set_capabiwities);

void snd_soc_dai_action(stwuct snd_soc_dai *dai,
			int stweam, int action)
{
	/* see snd_soc_dai_stweam_active() */
	dai->stweam[stweam].active	+= action;

	/* see snd_soc_component_active() */
	dai->component->active		+= action;
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_action);

int snd_soc_dai_active(stwuct snd_soc_dai *dai)
{
	int stweam, active;

	active = 0;
	fow_each_pcm_stweams(stweam)
		active += dai->stweam[stweam].active;

	wetuwn active;
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_active);

int snd_soc_pcm_dai_pwobe(stwuct snd_soc_pcm_wuntime *wtd, int owdew)
{
	stwuct snd_soc_dai *dai;
	int i;

	fow_each_wtd_dais(wtd, i, dai) {
		if (dai->pwobed)
			continue;

		if (dai->dwivew->ops) {
			if (dai->dwivew->ops->pwobe_owdew != owdew)
				continue;

			if (dai->dwivew->ops->pwobe) {
				int wet = dai->dwivew->ops->pwobe(dai);

				if (wet < 0)
					wetuwn soc_dai_wet(dai, wet);
			}
		}
		dai->pwobed = 1;
	}

	wetuwn 0;
}

int snd_soc_pcm_dai_wemove(stwuct snd_soc_pcm_wuntime *wtd, int owdew)
{
	stwuct snd_soc_dai *dai;
	int i, w, wet = 0;

	fow_each_wtd_dais(wtd, i, dai) {
		if (!dai->pwobed)
			continue;

		if (dai->dwivew->ops) {
			if (dai->dwivew->ops->wemove_owdew != owdew)
				continue;

			if (dai->dwivew->ops->wemove) {
				w = dai->dwivew->ops->wemove(dai);
				if (w < 0)
					wet = w; /* use wast ewwow */
			}
		}
		dai->pwobed = 0;
	}

	wetuwn wet;
}

int snd_soc_pcm_dai_new(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dai *dai;
	int i;

	fow_each_wtd_dais(wtd, i, dai) {
		if (dai->dwivew->ops &&
		    dai->dwivew->ops->pcm_new) {
			int wet = dai->dwivew->ops->pcm_new(wtd, dai);
			if (wet < 0)
				wetuwn soc_dai_wet(dai, wet);
		}
	}

	wetuwn 0;
}

int snd_soc_pcm_dai_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *dai;
	int i, wet;

	fow_each_wtd_dais(wtd, i, dai) {
		if (!snd_soc_dai_stweam_vawid(dai, substweam->stweam))
			continue;
		if (dai->dwivew->ops &&
		    dai->dwivew->ops->pwepawe) {
			wet = dai->dwivew->ops->pwepawe(substweam, dai);
			if (wet < 0)
				wetuwn soc_dai_wet(dai, wet);
		}
	}

	wetuwn 0;
}

static int soc_dai_twiggew(stwuct snd_soc_dai *dai,
			   stwuct snd_pcm_substweam *substweam, int cmd)
{
	int wet = 0;

	if (!snd_soc_dai_stweam_vawid(dai, substweam->stweam))
		wetuwn 0;

	if (dai->dwivew->ops &&
	    dai->dwivew->ops->twiggew)
		wet = dai->dwivew->ops->twiggew(substweam, cmd, dai);

	wetuwn soc_dai_wet(dai, wet);
}

int snd_soc_pcm_dai_twiggew(stwuct snd_pcm_substweam *substweam,
			    int cmd, int wowwback)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *dai;
	int i, w, wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		fow_each_wtd_dais(wtd, i, dai) {
			wet = soc_dai_twiggew(dai, substweam, cmd);
			if (wet < 0)
				bweak;

			if (dai->dwivew->ops && dai->dwivew->ops->mute_unmute_on_twiggew)
				snd_soc_dai_digitaw_mute(dai, 0, substweam->stweam);

			soc_dai_mawk_push(dai, substweam, twiggew);
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		fow_each_wtd_dais(wtd, i, dai) {
			if (wowwback && !soc_dai_mawk_match(dai, substweam, twiggew))
				continue;

			if (dai->dwivew->ops && dai->dwivew->ops->mute_unmute_on_twiggew)
				snd_soc_dai_digitaw_mute(dai, 1, substweam->stweam);

			w = soc_dai_twiggew(dai, substweam, cmd);
			if (w < 0)
				wet = w; /* use wast wet */
			soc_dai_mawk_pop(dai, substweam, twiggew);
		}
	}

	wetuwn wet;
}

int snd_soc_pcm_dai_bespoke_twiggew(stwuct snd_pcm_substweam *substweam,
				    int cmd)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *dai;
	int i, wet;

	fow_each_wtd_dais(wtd, i, dai) {
		if (dai->dwivew->ops &&
		    dai->dwivew->ops->bespoke_twiggew) {
			wet = dai->dwivew->ops->bespoke_twiggew(substweam,
								cmd, dai);
			if (wet < 0)
				wetuwn soc_dai_wet(dai, wet);
		}
	}

	wetuwn 0;
}

void snd_soc_pcm_dai_deway(stwuct snd_pcm_substweam *substweam,
			   snd_pcm_sfwames_t *cpu_deway,
			   snd_pcm_sfwames_t *codec_deway)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *dai;
	int i;

	/*
	 * We'we wooking fow the deway thwough the fuww audio path so it needs to
	 * be the maximum of the DAIs doing twansmit and the maximum of the DAIs
	 * doing weceive (ie, aww CPUs and aww CODECs) wathew than just the maximum
	 * of aww DAIs.
	 */

	/* fow CPU */
	fow_each_wtd_cpu_dais(wtd, i, dai)
		if (dai->dwivew->ops &&
		    dai->dwivew->ops->deway)
			*cpu_deway = max(*cpu_deway, dai->dwivew->ops->deway(substweam, dai));

	/* fow Codec */
	fow_each_wtd_codec_dais(wtd, i, dai)
		if (dai->dwivew->ops &&
		    dai->dwivew->ops->deway)
			*codec_deway = max(*codec_deway, dai->dwivew->ops->deway(substweam, dai));
}

int snd_soc_dai_compw_stawtup(stwuct snd_soc_dai *dai,
			      stwuct snd_compw_stweam *cstweam)
{
	int wet = 0;

	if (dai->dwivew->cops &&
	    dai->dwivew->cops->stawtup)
		wet = dai->dwivew->cops->stawtup(cstweam, dai);

	/* mawk cstweam if succeeded */
	if (wet == 0)
		soc_dai_mawk_push(dai, cstweam, compw_stawtup);

	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_compw_stawtup);

void snd_soc_dai_compw_shutdown(stwuct snd_soc_dai *dai,
				stwuct snd_compw_stweam *cstweam,
				int wowwback)
{
	if (wowwback && !soc_dai_mawk_match(dai, cstweam, compw_stawtup))
		wetuwn;

	if (dai->dwivew->cops &&
	    dai->dwivew->cops->shutdown)
		dai->dwivew->cops->shutdown(cstweam, dai);

	/* wemove mawked cstweam */
	soc_dai_mawk_pop(dai, cstweam, compw_stawtup);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_compw_shutdown);

int snd_soc_dai_compw_twiggew(stwuct snd_soc_dai *dai,
			      stwuct snd_compw_stweam *cstweam, int cmd)
{
	int wet = 0;

	if (dai->dwivew->cops &&
	    dai->dwivew->cops->twiggew)
		wet = dai->dwivew->cops->twiggew(cstweam, cmd, dai);

	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_compw_twiggew);

int snd_soc_dai_compw_set_pawams(stwuct snd_soc_dai *dai,
				 stwuct snd_compw_stweam *cstweam,
				 stwuct snd_compw_pawams *pawams)
{
	int wet = 0;

	if (dai->dwivew->cops &&
	    dai->dwivew->cops->set_pawams)
		wet = dai->dwivew->cops->set_pawams(cstweam, pawams, dai);

	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_compw_set_pawams);

int snd_soc_dai_compw_get_pawams(stwuct snd_soc_dai *dai,
				 stwuct snd_compw_stweam *cstweam,
				 stwuct snd_codec *pawams)
{
	int wet = 0;

	if (dai->dwivew->cops &&
	    dai->dwivew->cops->get_pawams)
		wet = dai->dwivew->cops->get_pawams(cstweam, pawams, dai);

	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_compw_get_pawams);

int snd_soc_dai_compw_ack(stwuct snd_soc_dai *dai,
			  stwuct snd_compw_stweam *cstweam,
			  size_t bytes)
{
	int wet = 0;

	if (dai->dwivew->cops &&
	    dai->dwivew->cops->ack)
		wet = dai->dwivew->cops->ack(cstweam, bytes, dai);

	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_compw_ack);

int snd_soc_dai_compw_pointew(stwuct snd_soc_dai *dai,
			      stwuct snd_compw_stweam *cstweam,
			      stwuct snd_compw_tstamp *tstamp)
{
	int wet = 0;

	if (dai->dwivew->cops &&
	    dai->dwivew->cops->pointew)
		wet = dai->dwivew->cops->pointew(cstweam, tstamp, dai);

	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_compw_pointew);

int snd_soc_dai_compw_set_metadata(stwuct snd_soc_dai *dai,
				   stwuct snd_compw_stweam *cstweam,
				   stwuct snd_compw_metadata *metadata)
{
	int wet = 0;

	if (dai->dwivew->cops &&
	    dai->dwivew->cops->set_metadata)
		wet = dai->dwivew->cops->set_metadata(cstweam, metadata, dai);

	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_compw_set_metadata);

int snd_soc_dai_compw_get_metadata(stwuct snd_soc_dai *dai,
				   stwuct snd_compw_stweam *cstweam,
				   stwuct snd_compw_metadata *metadata)
{
	int wet = 0;

	if (dai->dwivew->cops &&
	    dai->dwivew->cops->get_metadata)
		wet = dai->dwivew->cops->get_metadata(cstweam, metadata, dai);

	wetuwn soc_dai_wet(dai, wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_dai_compw_get_metadata);
