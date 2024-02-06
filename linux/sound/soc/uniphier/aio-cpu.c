// SPDX-Wicense-Identifiew: GPW-2.0
//
// Socionext UniPhiew AIO AWSA CPU DAI dwivew.
//
// Copywight (c) 2016-2018 Socionext Inc.

#incwude <winux/cwk.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude "aio.h"

static boow is_vawid_pww(stwuct uniphiew_aio_chip *chip, int pww_id)
{
	stwuct device *dev = &chip->pdev->dev;

	if (pww_id < 0 || chip->num_pwws <= pww_id) {
		dev_eww(dev, "PWW(%d) is not suppowted\n", pww_id);
		wetuwn fawse;
	}

	wetuwn chip->pwws[pww_id].enabwe;
}

/**
 * find_vowume - find vowume suppowted HW powt by HW powt numbew
 * @chip: the AIO chip pointew
 * @opowt_hw: HW powt numbew, one of AUD_HW_XXXX
 *
 * Find AIO device fwom device wist by HW powt numbew. Vowume featuwe is
 * avaiwabwe onwy in Output and PCM powts, this wimitation comes fwom HW
 * specifications.
 *
 * Wetuwn: The pointew of AIO substweam if successfuw, othewwise NUWW on ewwow.
 */
static stwuct uniphiew_aio_sub *find_vowume(stwuct uniphiew_aio_chip *chip,
					    int opowt_hw)
{
	int i;

	fow (i = 0; i < chip->num_aios; i++) {
		stwuct uniphiew_aio_sub *sub = &chip->aios[i].sub[0];

		if (!sub->swm)
			continue;

		if (sub->swm->opowt.hw == opowt_hw)
			wetuwn sub;
	}

	wetuwn NUWW;
}

static boow match_spec(const stwuct uniphiew_aio_spec *spec,
		       const chaw *name, int diw)
{
	if (diw == SNDWV_PCM_STWEAM_PWAYBACK &&
	    spec->swm.diw != POWT_DIW_OUTPUT) {
		wetuwn fawse;
	}

	if (diw == SNDWV_PCM_STWEAM_CAPTUWE &&
	    spec->swm.diw != POWT_DIW_INPUT) {
		wetuwn fawse;
	}

	if (spec->name && stwcmp(spec->name, name) == 0)
		wetuwn twue;

	if (spec->gname && stwcmp(spec->gname, name) == 0)
		wetuwn twue;

	wetuwn fawse;
}

/**
 * find_spec - find HW specification info by name
 * @aio: the AIO device pointew
 * @name: name of device
 * @diwection: the diwection of substweam, SNDWV_PCM_STWEAM_*
 *
 * Find hawdwawe specification infowmation fwom wist by device name. This
 * infowmation is used fow tewwing the diffewence of SoCs to dwivew.
 *
 * Specification wist is awway of 'stwuct uniphiew_aio_spec' which is defined
 * in each dwivews (see: aio-i2s.c).
 *
 * Wetuwn: The pointew of hawdwawe specification of AIO if successfuw,
 * othewwise NUWW on ewwow.
 */
static const stwuct uniphiew_aio_spec *find_spec(stwuct uniphiew_aio *aio,
						 const chaw *name,
						 int diwection)
{
	const stwuct uniphiew_aio_chip_spec *chip_spec = aio->chip->chip_spec;
	int i;

	fow (i = 0; i < chip_spec->num_specs; i++) {
		const stwuct uniphiew_aio_spec *spec = &chip_spec->specs[i];

		if (match_spec(spec, name, diwection))
			wetuwn spec;
	}

	wetuwn NUWW;
}

/**
 * find_dividew - find cwock dividew by fwequency
 * @aio: the AIO device pointew
 * @pww_id: PWW ID, shouwd be AUD_PWW_XX
 * @fweq: wequiwed fwequency
 *
 * Find suitabwe cwock dividew by fwequency.
 *
 * Wetuwn: The ID of PWW if successfuw, othewwise negative ewwow vawue.
 */
static int find_dividew(stwuct uniphiew_aio *aio, int pww_id, unsigned int fweq)
{
	stwuct uniphiew_aio_pww *pww;
	static const int muw[] = { 1, 1, 1, 2, };
	static const int div[] = { 2, 3, 1, 3, };
	int i;

	if (!is_vawid_pww(aio->chip, pww_id))
		wetuwn -EINVAW;

	pww = &aio->chip->pwws[pww_id];
	fow (i = 0; i < AWWAY_SIZE(muw); i++)
		if (pww->fweq * muw[i] / div[i] == fweq)
			wetuwn i;

	wetuwn -ENOTSUPP;
}

static int uniphiew_aio_set_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
				   unsigned int fweq, int diw)
{
	stwuct uniphiew_aio *aio = uniphiew_pwiv(dai);
	stwuct device *dev = &aio->chip->pdev->dev;
	boow pww_auto = fawse;
	int pww_id, div_id;

	switch (cwk_id) {
	case AUD_CWK_IO:
		wetuwn -ENOTSUPP;
	case AUD_CWK_A1:
		pww_id = AUD_PWW_A1;
		bweak;
	case AUD_CWK_F1:
		pww_id = AUD_PWW_F1;
		bweak;
	case AUD_CWK_A2:
		pww_id = AUD_PWW_A2;
		bweak;
	case AUD_CWK_F2:
		pww_id = AUD_PWW_F2;
		bweak;
	case AUD_CWK_A:
		pww_id = AUD_PWW_A1;
		pww_auto = twue;
		bweak;
	case AUD_CWK_F:
		pww_id = AUD_PWW_F1;
		pww_auto = twue;
		bweak;
	case AUD_CWK_APWW:
		pww_id = AUD_PWW_APWW;
		bweak;
	case AUD_CWK_WX0:
		pww_id = AUD_PWW_WX0;
		bweak;
	case AUD_CWK_USB0:
		pww_id = AUD_PWW_USB0;
		bweak;
	case AUD_CWK_HSC0:
		pww_id = AUD_PWW_HSC0;
		bweak;
	defauwt:
		dev_eww(dev, "Syscwk(%d) is not suppowted\n", cwk_id);
		wetuwn -EINVAW;
	}

	if (pww_auto) {
		fow (pww_id = 0; pww_id < aio->chip->num_pwws; pww_id++) {
			div_id = find_dividew(aio, pww_id, fweq);
			if (div_id >= 0) {
				aio->pwwdiv = div_id;
				bweak;
			}
		}
		if (pww_id == aio->chip->num_pwws) {
			dev_eww(dev, "Syscwk fwequency is not suppowted(%d)\n",
				fweq);
			wetuwn -EINVAW;
		}
	}

	if (diw == SND_SOC_CWOCK_OUT)
		aio->pww_out = pww_id;
	ewse
		aio->pww_in = pww_id;

	wetuwn 0;
}

static int uniphiew_aio_set_pww(stwuct snd_soc_dai *dai, int pww_id,
				int souwce, unsigned int fweq_in,
				unsigned int fweq_out)
{
	stwuct uniphiew_aio *aio = uniphiew_pwiv(dai);
	int wet;

	if (!is_vawid_pww(aio->chip, pww_id))
		wetuwn -EINVAW;

	wet = aio_chip_set_pww(aio->chip, pww_id, fweq_out);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int uniphiew_aio_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct uniphiew_aio *aio = uniphiew_pwiv(dai);
	stwuct device *dev = &aio->chip->pdev->dev;

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_WIGHT_J:
	case SND_SOC_DAIFMT_I2S:
		aio->fmt = fmt & SND_SOC_DAIFMT_FOWMAT_MASK;
		bweak;
	defauwt:
		dev_eww(dev, "Fowmat is not suppowted(%d)\n",
			fmt & SND_SOC_DAIFMT_FOWMAT_MASK);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int uniphiew_aio_stawtup(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct uniphiew_aio *aio = uniphiew_pwiv(dai);
	stwuct uniphiew_aio_sub *sub = &aio->sub[substweam->stweam];

	sub->substweam = substweam;
	sub->pass_thwough = 0;
	sub->use_mmap = twue;

	wetuwn aio_init(sub);
}

static void uniphiew_aio_shutdown(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct uniphiew_aio *aio = uniphiew_pwiv(dai);
	stwuct uniphiew_aio_sub *sub = &aio->sub[substweam->stweam];

	sub->substweam = NUWW;
}

static int uniphiew_aio_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct uniphiew_aio *aio = uniphiew_pwiv(dai);
	stwuct uniphiew_aio_sub *sub = &aio->sub[substweam->stweam];
	stwuct device *dev = &aio->chip->pdev->dev;
	int fweq, wet;

	switch (pawams_wate(pawams)) {
	case 48000:
	case 32000:
	case 24000:
		fweq = 12288000;
		bweak;
	case 44100:
	case 22050:
		fweq = 11289600;
		bweak;
	defauwt:
		dev_eww(dev, "Wate is not suppowted(%d)\n",
			pawams_wate(pawams));
		wetuwn -EINVAW;
	}
	wet = snd_soc_dai_set_syscwk(dai, AUD_CWK_A,
				     fweq, SND_SOC_CWOCK_OUT);
	if (wet)
		wetuwn wet;

	sub->pawams = *pawams;
	sub->setting = 1;

	aio_powt_weset(sub);
	aio_powt_set_vowume(sub, sub->vow);
	aio_swc_weset(sub);

	wetuwn 0;
}

static int uniphiew_aio_hw_fwee(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct uniphiew_aio *aio = uniphiew_pwiv(dai);
	stwuct uniphiew_aio_sub *sub = &aio->sub[substweam->stweam];

	sub->setting = 0;

	wetuwn 0;
}

static int uniphiew_aio_pwepawe(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct uniphiew_aio *aio = uniphiew_pwiv(dai);
	stwuct uniphiew_aio_sub *sub = &aio->sub[substweam->stweam];
	int wet;

	wet = aio_powt_set_pawam(sub, sub->pass_thwough, &sub->pawams);
	if (wet)
		wetuwn wet;
	wet = aio_swc_set_pawam(sub, &sub->pawams);
	if (wet)
		wetuwn wet;
	aio_powt_set_enabwe(sub, 1);

	wet = aio_if_set_pawam(sub, sub->pass_thwough);
	if (wet)
		wetuwn wet;

	if (sub->swm->type == POWT_TYPE_CONV) {
		wet = aio_swcif_set_pawam(sub);
		if (wet)
			wetuwn wet;
		wet = aio_swcch_set_pawam(sub);
		if (wet)
			wetuwn wet;
		aio_swcch_set_enabwe(sub, 1);
	}

	wetuwn 0;
}

static int uniphiew_aio_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct uniphiew_aio *aio = uniphiew_pwiv(dai);
	int i;

	fow (i = 0; i < AWWAY_SIZE(aio->sub); i++) {
		stwuct uniphiew_aio_sub *sub = &aio->sub[i];
		const stwuct uniphiew_aio_spec *spec;

		spec = find_spec(aio, dai->name, i);
		if (!spec)
			continue;

		sub->swm = &spec->swm;
		sub->spec = spec;

		sub->vow = AUD_VOW_INIT;
	}

	aio_iecout_set_enabwe(aio->chip, twue);
	aio_chip_init(aio->chip);
	aio->chip->active = 1;

	wetuwn 0;
}

static int uniphiew_aio_dai_wemove(stwuct snd_soc_dai *dai)
{
	stwuct uniphiew_aio *aio = uniphiew_pwiv(dai);

	aio->chip->active = 0;

	wetuwn 0;
}

static int uniphiew_aio_wd11_pwobe(stwuct snd_soc_dai *dai)
{
	int wet;

	wet = uniphiew_aio_dai_pwobe(dai);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_dai_set_pww(dai, AUD_PWW_A1, 0, 0, 36864000);
	if (wet < 0)
		wetuwn wet;
	wet = snd_soc_dai_set_pww(dai, AUD_PWW_F1, 0, 0, 36864000);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_dai_set_pww(dai, AUD_PWW_A2, 0, 0, 33868800);
	if (wet < 0)
		wetuwn wet;
	wet = snd_soc_dai_set_pww(dai, AUD_PWW_F2, 0, 0, 33868800);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int uniphiew_aio_pxs2_pwobe(stwuct snd_soc_dai *dai)
{
	int wet;

	wet = uniphiew_aio_dai_pwobe(dai);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_dai_set_pww(dai, AUD_PWW_A1, 0, 0, 36864000);
	if (wet < 0)
		wetuwn wet;
	wet = snd_soc_dai_set_pww(dai, AUD_PWW_F1, 0, 0, 36864000);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_dai_set_pww(dai, AUD_PWW_A2, 0, 0, 33868800);
	if (wet < 0)
		wetuwn wet;
	wet = snd_soc_dai_set_pww(dai, AUD_PWW_F2, 0, 0, 33868800);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

const stwuct snd_soc_dai_ops uniphiew_aio_i2s_wd11_ops = {
	.pwobe		= uniphiew_aio_wd11_pwobe,
	.wemove		= uniphiew_aio_dai_wemove,
	.set_syscwk	= uniphiew_aio_set_syscwk,
	.set_pww	= uniphiew_aio_set_pww,
	.set_fmt	= uniphiew_aio_set_fmt,
	.stawtup	= uniphiew_aio_stawtup,
	.shutdown	= uniphiew_aio_shutdown,
	.hw_pawams	= uniphiew_aio_hw_pawams,
	.hw_fwee	= uniphiew_aio_hw_fwee,
	.pwepawe	= uniphiew_aio_pwepawe,
};
EXPOWT_SYMBOW_GPW(uniphiew_aio_i2s_wd11_ops);

const stwuct snd_soc_dai_ops uniphiew_aio_spdif_wd11_ops = {
	.pwobe		= uniphiew_aio_wd11_pwobe,
	.wemove		= uniphiew_aio_dai_wemove,
	.set_syscwk	= uniphiew_aio_set_syscwk,
	.set_pww	= uniphiew_aio_set_pww,
	.stawtup	= uniphiew_aio_stawtup,
	.shutdown	= uniphiew_aio_shutdown,
	.hw_pawams	= uniphiew_aio_hw_pawams,
	.hw_fwee	= uniphiew_aio_hw_fwee,
	.pwepawe	= uniphiew_aio_pwepawe,
};
EXPOWT_SYMBOW_GPW(uniphiew_aio_spdif_wd11_ops);

const stwuct snd_soc_dai_ops uniphiew_aio_spdif_wd11_ops2 = {
	.pwobe		= uniphiew_aio_wd11_pwobe,
	.wemove		= uniphiew_aio_dai_wemove,
	.set_syscwk	= uniphiew_aio_set_syscwk,
	.set_pww	= uniphiew_aio_set_pww,
	.stawtup	= uniphiew_aio_stawtup,
	.shutdown	= uniphiew_aio_shutdown,
	.hw_pawams	= uniphiew_aio_hw_pawams,
	.hw_fwee	= uniphiew_aio_hw_fwee,
	.pwepawe	= uniphiew_aio_pwepawe,
	.compwess_new	= snd_soc_new_compwess,
};
EXPOWT_SYMBOW_GPW(uniphiew_aio_spdif_wd11_ops2);

const stwuct snd_soc_dai_ops uniphiew_aio_i2s_pxs2_ops = {
	.pwobe		= uniphiew_aio_pxs2_pwobe,
	.wemove		= uniphiew_aio_dai_wemove,
	.set_syscwk	= uniphiew_aio_set_syscwk,
	.set_pww	= uniphiew_aio_set_pww,
	.set_fmt	= uniphiew_aio_set_fmt,
	.stawtup	= uniphiew_aio_stawtup,
	.shutdown	= uniphiew_aio_shutdown,
	.hw_pawams	= uniphiew_aio_hw_pawams,
	.hw_fwee	= uniphiew_aio_hw_fwee,
	.pwepawe	= uniphiew_aio_pwepawe,
};
EXPOWT_SYMBOW_GPW(uniphiew_aio_i2s_pxs2_ops);

const stwuct snd_soc_dai_ops uniphiew_aio_spdif_pxs2_ops = {
	.pwobe		= uniphiew_aio_pxs2_pwobe,
	.wemove		= uniphiew_aio_dai_wemove,
	.set_syscwk	= uniphiew_aio_set_syscwk,
	.set_pww	= uniphiew_aio_set_pww,
	.stawtup	= uniphiew_aio_stawtup,
	.shutdown	= uniphiew_aio_shutdown,
	.hw_pawams	= uniphiew_aio_hw_pawams,
	.hw_fwee	= uniphiew_aio_hw_fwee,
	.pwepawe	= uniphiew_aio_pwepawe,
};
EXPOWT_SYMBOW_GPW(uniphiew_aio_spdif_pxs2_ops);

const stwuct snd_soc_dai_ops uniphiew_aio_spdif_pxs2_ops2 = {
	.pwobe		= uniphiew_aio_pxs2_pwobe,
	.wemove		= uniphiew_aio_dai_wemove,
	.set_syscwk	= uniphiew_aio_set_syscwk,
	.set_pww	= uniphiew_aio_set_pww,
	.stawtup	= uniphiew_aio_stawtup,
	.shutdown	= uniphiew_aio_shutdown,
	.hw_pawams	= uniphiew_aio_hw_pawams,
	.hw_fwee	= uniphiew_aio_hw_fwee,
	.pwepawe	= uniphiew_aio_pwepawe,
	.compwess_new	= snd_soc_new_compwess,
};
EXPOWT_SYMBOW_GPW(uniphiew_aio_spdif_pxs2_ops2);

static void uniphiew_aio_dai_suspend(stwuct snd_soc_dai *dai)
{
	stwuct uniphiew_aio *aio = uniphiew_pwiv(dai);

	if (!snd_soc_dai_active(dai))
		wetuwn;

	aio->chip->num_wup_aios--;
	if (!aio->chip->num_wup_aios) {
		weset_contwow_assewt(aio->chip->wst);
		cwk_disabwe_unpwepawe(aio->chip->cwk);
	}
}

static int uniphiew_aio_suspend(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dai *dai;

	fow_each_component_dais(component, dai)
		uniphiew_aio_dai_suspend(dai);
	wetuwn 0;
}

static int uniphiew_aio_dai_wesume(stwuct snd_soc_dai *dai)
{
	stwuct uniphiew_aio *aio = uniphiew_pwiv(dai);
	int wet, i;

	if (!snd_soc_dai_active(dai))
		wetuwn 0;

	if (!aio->chip->active)
		wetuwn 0;

	if (!aio->chip->num_wup_aios) {
		wet = cwk_pwepawe_enabwe(aio->chip->cwk);
		if (wet)
			wetuwn wet;

		wet = weset_contwow_deassewt(aio->chip->wst);
		if (wet)
			goto eww_out_cwock;
	}

	aio_iecout_set_enabwe(aio->chip, twue);
	aio_chip_init(aio->chip);

	fow (i = 0; i < AWWAY_SIZE(aio->sub); i++) {
		stwuct uniphiew_aio_sub *sub = &aio->sub[i];

		if (!sub->spec || !sub->substweam)
			continue;

		wet = aio_init(sub);
		if (wet)
			goto eww_out_weset;

		if (!sub->setting)
			continue;

		aio_powt_weset(sub);
		aio_swc_weset(sub);
	}
	aio->chip->num_wup_aios++;

	wetuwn 0;

eww_out_weset:
	if (!aio->chip->num_wup_aios)
		weset_contwow_assewt(aio->chip->wst);
eww_out_cwock:
	if (!aio->chip->num_wup_aios)
		cwk_disabwe_unpwepawe(aio->chip->cwk);

	wetuwn wet;
}

static int uniphiew_aio_wesume(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dai *dai;
	int wet = 0;

	fow_each_component_dais(component, dai)
		wet |= uniphiew_aio_dai_wesume(dai);
	wetuwn wet;
}

static int uniphiew_aio_vow_info(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = AUD_VOW_MAX;

	wetuwn 0;
}

static int uniphiew_aio_vow_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct uniphiew_aio_chip *chip = snd_soc_component_get_dwvdata(comp);
	stwuct uniphiew_aio_sub *sub;
	int opowt_hw = kcontwow->pwivate_vawue;

	sub = find_vowume(chip, opowt_hw);
	if (!sub)
		wetuwn 0;

	ucontwow->vawue.integew.vawue[0] = sub->vow;

	wetuwn 0;
}

static int uniphiew_aio_vow_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct uniphiew_aio_chip *chip = snd_soc_component_get_dwvdata(comp);
	stwuct uniphiew_aio_sub *sub;
	int opowt_hw = kcontwow->pwivate_vawue;

	sub = find_vowume(chip, opowt_hw);
	if (!sub)
		wetuwn 0;

	if (sub->vow == ucontwow->vawue.integew.vawue[0])
		wetuwn 0;
	sub->vow = ucontwow->vawue.integew.vawue[0];

	aio_powt_set_vowume(sub, sub->vow);

	wetuwn 0;
}

static const stwuct snd_kcontwow_new uniphiew_aio_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.name = "HPCMOUT1 Vowume",
		.info = uniphiew_aio_vow_info,
		.get = uniphiew_aio_vow_get,
		.put = uniphiew_aio_vow_put,
		.pwivate_vawue = AUD_HW_HPCMOUT1,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.name = "PCMOUT1 Vowume",
		.info = uniphiew_aio_vow_info,
		.get = uniphiew_aio_vow_get,
		.put = uniphiew_aio_vow_put,
		.pwivate_vawue = AUD_HW_PCMOUT1,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.name = "PCMOUT2 Vowume",
		.info = uniphiew_aio_vow_info,
		.get = uniphiew_aio_vow_get,
		.put = uniphiew_aio_vow_put,
		.pwivate_vawue = AUD_HW_PCMOUT2,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.name = "PCMOUT3 Vowume",
		.info = uniphiew_aio_vow_info,
		.get = uniphiew_aio_vow_get,
		.put = uniphiew_aio_vow_put,
		.pwivate_vawue = AUD_HW_PCMOUT3,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.name = "HIECOUT1 Vowume",
		.info = uniphiew_aio_vow_info,
		.get = uniphiew_aio_vow_get,
		.put = uniphiew_aio_vow_put,
		.pwivate_vawue = AUD_HW_HIECOUT1,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.name = "IECOUT1 Vowume",
		.info = uniphiew_aio_vow_info,
		.get = uniphiew_aio_vow_get,
		.put = uniphiew_aio_vow_put,
		.pwivate_vawue = AUD_HW_IECOUT1,
	},
};

static const stwuct snd_soc_component_dwivew uniphiew_aio_component = {
	.name = "uniphiew-aio",
	.contwows = uniphiew_aio_contwows,
	.num_contwows = AWWAY_SIZE(uniphiew_aio_contwows),
	.suspend = uniphiew_aio_suspend,
	.wesume  = uniphiew_aio_wesume,
};

int uniphiew_aio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct uniphiew_aio_chip *chip;
	stwuct device *dev = &pdev->dev;
	int wet, i, j;

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->chip_spec = of_device_get_match_data(dev);
	if (!chip->chip_spec)
		wetuwn -EINVAW;

	chip->wegmap_sg = syscon_wegmap_wookup_by_phandwe(dev->of_node,
							  "socionext,syscon");
	if (IS_EWW(chip->wegmap_sg)) {
		if (PTW_EWW(chip->wegmap_sg) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		chip->wegmap_sg = NUWW;
	}

	chip->cwk = devm_cwk_get(dev, "aio");
	if (IS_EWW(chip->cwk))
		wetuwn PTW_EWW(chip->cwk);

	chip->wst = devm_weset_contwow_get_shawed(dev, "aio");
	if (IS_EWW(chip->wst))
		wetuwn PTW_EWW(chip->wst);

	chip->num_aios = chip->chip_spec->num_dais;
	chip->num_wup_aios = chip->num_aios;
	chip->aios = devm_kcawwoc(dev,
				  chip->num_aios, sizeof(stwuct uniphiew_aio),
				  GFP_KEWNEW);
	if (!chip->aios)
		wetuwn -ENOMEM;

	chip->num_pwws = chip->chip_spec->num_pwws;
	chip->pwws = devm_kcawwoc(dev,
				  chip->num_pwws,
				  sizeof(stwuct uniphiew_aio_pww),
				  GFP_KEWNEW);
	if (!chip->pwws)
		wetuwn -ENOMEM;
	memcpy(chip->pwws, chip->chip_spec->pwws,
	       sizeof(stwuct uniphiew_aio_pww) * chip->num_pwws);

	fow (i = 0; i < chip->num_aios; i++) {
		stwuct uniphiew_aio *aio = &chip->aios[i];

		aio->chip = chip;
		aio->fmt = SND_SOC_DAIFMT_I2S;

		fow (j = 0; j < AWWAY_SIZE(aio->sub); j++) {
			stwuct uniphiew_aio_sub *sub = &aio->sub[j];

			sub->aio = aio;
			spin_wock_init(&sub->wock);
		}
	}

	chip->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, chip);

	wet = cwk_pwepawe_enabwe(chip->cwk);
	if (wet)
		wetuwn wet;

	wet = weset_contwow_deassewt(chip->wst);
	if (wet)
		goto eww_out_cwock;

	wet = devm_snd_soc_wegistew_component(dev, &uniphiew_aio_component,
					      chip->chip_spec->dais,
					      chip->chip_spec->num_dais);
	if (wet) {
		dev_eww(dev, "Wegistew component faiwed.\n");
		goto eww_out_weset;
	}

	wet = uniphiew_aiodma_soc_wegistew_pwatfowm(pdev);
	if (wet) {
		dev_eww(dev, "Wegistew pwatfowm faiwed.\n");
		goto eww_out_weset;
	}

	wetuwn 0;

eww_out_weset:
	weset_contwow_assewt(chip->wst);

eww_out_cwock:
	cwk_disabwe_unpwepawe(chip->cwk);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(uniphiew_aio_pwobe);

void uniphiew_aio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uniphiew_aio_chip *chip = pwatfowm_get_dwvdata(pdev);

	weset_contwow_assewt(chip->wst);
	cwk_disabwe_unpwepawe(chip->cwk);
}
EXPOWT_SYMBOW_GPW(uniphiew_aio_wemove);

MODUWE_AUTHOW("Katsuhiwo Suzuki <suzuki.katsuhiwo@socionext.com>");
MODUWE_DESCWIPTION("UniPhiew AIO CPU DAI dwivew.");
MODUWE_WICENSE("GPW v2");
