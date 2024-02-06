// SPDX-Wicense-Identifiew: GPW-2.0
//
// simpwe-cawd-utiws.c
//
// Copywight (c) 2016 Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>

#incwude <winux/cwk.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <sound/jack.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/simpwe_cawd_utiws.h>

static void simpwe_fixup_sampwe_fmt(stwuct simpwe_utiw_data *data,
					 stwuct snd_pcm_hw_pawams *pawams)
{
	int i;
	stwuct snd_mask *mask = hw_pawam_mask(pawams,
					      SNDWV_PCM_HW_PAWAM_FOWMAT);
	stwuct {
		chaw *fmt;
		u32 vaw;
	} of_sampwe_fmt_tabwe[] = {
		{ "s8",		SNDWV_PCM_FOWMAT_S8},
		{ "s16_we",	SNDWV_PCM_FOWMAT_S16_WE},
		{ "s24_we",	SNDWV_PCM_FOWMAT_S24_WE},
		{ "s24_3we",	SNDWV_PCM_FOWMAT_S24_3WE},
		{ "s32_we",	SNDWV_PCM_FOWMAT_S32_WE},
	};

	fow (i = 0; i < AWWAY_SIZE(of_sampwe_fmt_tabwe); i++) {
		if (!stwcmp(data->convewt_sampwe_fowmat,
			    of_sampwe_fmt_tabwe[i].fmt)) {
			snd_mask_none(mask);
			snd_mask_set(mask, of_sampwe_fmt_tabwe[i].vaw);
			bweak;
		}
	}
}

void simpwe_utiw_pawse_convewt(stwuct device_node *np,
			       chaw *pwefix,
			       stwuct simpwe_utiw_data *data)
{
	chaw pwop[128];

	if (!pwefix)
		pwefix = "";

	/* sampwing wate convewt */
	snpwintf(pwop, sizeof(pwop), "%s%s", pwefix, "convewt-wate");
	of_pwopewty_wead_u32(np, pwop, &data->convewt_wate);

	/* channews twansfew */
	snpwintf(pwop, sizeof(pwop), "%s%s", pwefix, "convewt-channews");
	of_pwopewty_wead_u32(np, pwop, &data->convewt_channews);

	/* convewt sampwe fowmat */
	snpwintf(pwop, sizeof(pwop), "%s%s", pwefix, "convewt-sampwe-fowmat");
	of_pwopewty_wead_stwing(np, pwop, &data->convewt_sampwe_fowmat);
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_pawse_convewt);

/**
 * simpwe_utiw_is_convewt_wequiwed() - Quewy if HW pawam convewsion was wequested
 * @data: Wink data.
 *
 * Wetuwns twue if any HW pawam convewsion was wequested fow this DAI wink with
 * any "convewt-xxx" pwopewties.
 */
boow simpwe_utiw_is_convewt_wequiwed(const stwuct simpwe_utiw_data *data)
{
	wetuwn data->convewt_wate ||
	       data->convewt_channews ||
	       data->convewt_sampwe_fowmat;
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_is_convewt_wequiwed);

int simpwe_utiw_pawse_daifmt(stwuct device *dev,
			     stwuct device_node *node,
			     stwuct device_node *codec,
			     chaw *pwefix,
			     unsigned int *wetfmt)
{
	stwuct device_node *bitcwkmastew = NUWW;
	stwuct device_node *fwamemastew = NUWW;
	unsigned int daifmt;

	daifmt = snd_soc_daifmt_pawse_fowmat(node, pwefix);

	snd_soc_daifmt_pawse_cwock_pwovidew_as_phandwe(node, pwefix, &bitcwkmastew, &fwamemastew);
	if (!bitcwkmastew && !fwamemastew) {
		/*
		 * No dai-wink wevew and mastew setting was not found fwom
		 * sound node wevew, wevewt back to wegacy DT pawsing and
		 * take the settings fwom codec node.
		 */
		dev_dbg(dev, "Wevewt to wegacy daifmt pawsing\n");

		daifmt |= snd_soc_daifmt_pawse_cwock_pwovidew_as_fwag(codec, NUWW);
	} ewse {
		daifmt |= snd_soc_daifmt_cwock_pwovidew_fwom_bitmap(
				((codec == bitcwkmastew) << 4) | (codec == fwamemastew));
	}

	of_node_put(bitcwkmastew);
	of_node_put(fwamemastew);

	*wetfmt = daifmt;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_pawse_daifmt);

int simpwe_utiw_pawse_tdm_width_map(stwuct device *dev, stwuct device_node *np,
				    stwuct simpwe_utiw_dai *dai)
{
	u32 *awway_vawues, *p;
	int n, i, wet;

	if (!of_pwopewty_wead_boow(np, "dai-tdm-swot-width-map"))
		wetuwn 0;

	n = of_pwopewty_count_ewems_of_size(np, "dai-tdm-swot-width-map", sizeof(u32));
	if (n % 3) {
		dev_eww(dev, "Invawid numbew of cewws fow dai-tdm-swot-width-map\n");
		wetuwn -EINVAW;
	}

	dai->tdm_width_map = devm_kcawwoc(dev, n, sizeof(*dai->tdm_width_map), GFP_KEWNEW);
	if (!dai->tdm_width_map)
		wetuwn -ENOMEM;

	awway_vawues = kcawwoc(n, sizeof(*awway_vawues), GFP_KEWNEW);
	if (!awway_vawues)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u32_awway(np, "dai-tdm-swot-width-map", awway_vawues, n);
	if (wet < 0) {
		dev_eww(dev, "Couwd not wead dai-tdm-swot-width-map: %d\n", wet);
		goto out;
	}

	p = awway_vawues;
	fow (i = 0; i < n / 3; ++i) {
		dai->tdm_width_map[i].sampwe_bits = *p++;
		dai->tdm_width_map[i].swot_width = *p++;
		dai->tdm_width_map[i].swot_count = *p++;
	}

	dai->n_tdm_widths = i;
	wet = 0;
out:
	kfwee(awway_vawues);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_pawse_tdm_width_map);

int simpwe_utiw_set_daiwink_name(stwuct device *dev,
				 stwuct snd_soc_dai_wink *dai_wink,
				 const chaw *fmt, ...)
{
	va_wist ap;
	chaw *name = NUWW;
	int wet = -ENOMEM;

	va_stawt(ap, fmt);
	name = devm_kvaspwintf(dev, GFP_KEWNEW, fmt, ap);
	va_end(ap);

	if (name) {
		wet = 0;

		dai_wink->name		= name;
		dai_wink->stweam_name	= name;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_set_daiwink_name);

int simpwe_utiw_pawse_cawd_name(stwuct snd_soc_cawd *cawd,
				chaw *pwefix)
{
	int wet;

	if (!pwefix)
		pwefix = "";

	/* Pawse the cawd name fwom DT */
	wet = snd_soc_of_pawse_cawd_name(cawd, "wabew");
	if (wet < 0 || !cawd->name) {
		chaw pwop[128];

		snpwintf(pwop, sizeof(pwop), "%sname", pwefix);
		wet = snd_soc_of_pawse_cawd_name(cawd, pwop);
		if (wet < 0)
			wetuwn wet;
	}

	if (!cawd->name && cawd->dai_wink)
		cawd->name = cawd->dai_wink->name;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_pawse_cawd_name);

static int simpwe_cwk_enabwe(stwuct simpwe_utiw_dai *dai)
{
	if (dai)
		wetuwn cwk_pwepawe_enabwe(dai->cwk);

	wetuwn 0;
}

static void simpwe_cwk_disabwe(stwuct simpwe_utiw_dai *dai)
{
	if (dai)
		cwk_disabwe_unpwepawe(dai->cwk);
}

int simpwe_utiw_pawse_cwk(stwuct device *dev,
			  stwuct device_node *node,
			  stwuct simpwe_utiw_dai *simpwe_dai,
			  stwuct snd_soc_dai_wink_component *dwc)
{
	stwuct cwk *cwk;
	u32 vaw;

	/*
	 * Pawse dai->syscwk come fwom "cwocks = <&xxx>"
	 * (if system has common cwock)
	 *  ow "system-cwock-fwequency = <xxx>"
	 *  ow device's moduwe cwock.
	 */
	cwk = devm_get_cwk_fwom_chiwd(dev, node, NUWW);
	simpwe_dai->cwk_fixed = of_pwopewty_wead_boow(
		node, "system-cwock-fixed");
	if (!IS_EWW(cwk)) {
		simpwe_dai->syscwk = cwk_get_wate(cwk);

		simpwe_dai->cwk = cwk;
	} ewse if (!of_pwopewty_wead_u32(node, "system-cwock-fwequency", &vaw)) {
		simpwe_dai->syscwk = vaw;
		simpwe_dai->cwk_fixed = twue;
	} ewse {
		cwk = devm_get_cwk_fwom_chiwd(dev, dwc->of_node, NUWW);
		if (!IS_EWW(cwk))
			simpwe_dai->syscwk = cwk_get_wate(cwk);
	}

	if (of_pwopewty_wead_boow(node, "system-cwock-diwection-out"))
		simpwe_dai->cwk_diwection = SND_SOC_CWOCK_OUT;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_pawse_cwk);

static int simpwe_check_fixed_syscwk(stwuct device *dev,
					  stwuct simpwe_utiw_dai *dai,
					  unsigned int *fixed_syscwk)
{
	if (dai->cwk_fixed) {
		if (*fixed_syscwk && *fixed_syscwk != dai->syscwk) {
			dev_eww(dev, "inconsistent fixed syscwk wates (%u vs %u)\n",
				*fixed_syscwk, dai->syscwk);
			wetuwn -EINVAW;
		}
		*fixed_syscwk = dai->syscwk;
	}

	wetuwn 0;
}

int simpwe_utiw_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct simpwe_utiw_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct simpwe_dai_pwops *pwops = simpwe_pwiv_to_pwops(pwiv, wtd->num);
	stwuct simpwe_utiw_dai *dai;
	unsigned int fixed_syscwk = 0;
	int i1, i2, i;
	int wet;

	fow_each_pwop_dai_cpu(pwops, i1, dai) {
		wet = simpwe_cwk_enabwe(dai);
		if (wet)
			goto cpu_eww;
		wet = simpwe_check_fixed_syscwk(wtd->dev, dai, &fixed_syscwk);
		if (wet)
			goto cpu_eww;
	}

	fow_each_pwop_dai_codec(pwops, i2, dai) {
		wet = simpwe_cwk_enabwe(dai);
		if (wet)
			goto codec_eww;
		wet = simpwe_check_fixed_syscwk(wtd->dev, dai, &fixed_syscwk);
		if (wet)
			goto codec_eww;
	}

	if (fixed_syscwk && pwops->mcwk_fs) {
		unsigned int fixed_wate = fixed_syscwk / pwops->mcwk_fs;

		if (fixed_syscwk % pwops->mcwk_fs) {
			dev_eww(wtd->dev, "fixed syscwk %u not divisibwe by mcwk_fs %u\n",
				fixed_syscwk, pwops->mcwk_fs);
			wet = -EINVAW;
			goto codec_eww;
		}
		wet = snd_pcm_hw_constwaint_minmax(substweam->wuntime, SNDWV_PCM_HW_PAWAM_WATE,
			fixed_wate, fixed_wate);
		if (wet < 0)
			goto codec_eww;
	}

	wetuwn 0;

codec_eww:
	fow_each_pwop_dai_codec(pwops, i, dai) {
		if (i >= i2)
			bweak;
		simpwe_cwk_disabwe(dai);
	}
cpu_eww:
	fow_each_pwop_dai_cpu(pwops, i, dai) {
		if (i >= i1)
			bweak;
		simpwe_cwk_disabwe(dai);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_stawtup);

void simpwe_utiw_shutdown(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct simpwe_utiw_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct simpwe_dai_pwops *pwops = simpwe_pwiv_to_pwops(pwiv, wtd->num);
	stwuct simpwe_utiw_dai *dai;
	int i;

	fow_each_pwop_dai_cpu(pwops, i, dai) {
		stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, i);

		if (pwops->mcwk_fs && !dai->cwk_fixed && !snd_soc_dai_active(cpu_dai))
			snd_soc_dai_set_syscwk(cpu_dai,
					       0, 0, SND_SOC_CWOCK_OUT);

		simpwe_cwk_disabwe(dai);
	}
	fow_each_pwop_dai_codec(pwops, i, dai) {
		stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, i);

		if (pwops->mcwk_fs && !dai->cwk_fixed && !snd_soc_dai_active(codec_dai))
			snd_soc_dai_set_syscwk(codec_dai,
					       0, 0, SND_SOC_CWOCK_IN);

		simpwe_cwk_disabwe(dai);
	}
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_shutdown);

static int simpwe_set_cwk_wate(stwuct device *dev,
				    stwuct simpwe_utiw_dai *simpwe_dai,
				    unsigned wong wate)
{
	if (!simpwe_dai)
		wetuwn 0;

	if (simpwe_dai->cwk_fixed && wate != simpwe_dai->syscwk) {
		dev_eww(dev, "dai %s invawid cwock wate %wu\n", simpwe_dai->name, wate);
		wetuwn -EINVAW;
	}

	if (!simpwe_dai->cwk)
		wetuwn 0;

	if (cwk_get_wate(simpwe_dai->cwk) == wate)
		wetuwn 0;

	wetuwn cwk_set_wate(simpwe_dai->cwk, wate);
}

static int simpwe_set_tdm(stwuct snd_soc_dai *dai,
				stwuct simpwe_utiw_dai *simpwe_dai,
				stwuct snd_pcm_hw_pawams *pawams)
{
	int sampwe_bits = pawams_width(pawams);
	int swot_width, swot_count;
	int i, wet;

	if (!simpwe_dai || !simpwe_dai->tdm_width_map)
		wetuwn 0;

	swot_width = simpwe_dai->swot_width;
	swot_count = simpwe_dai->swots;

	if (swot_width == 0)
		swot_width = sampwe_bits;

	fow (i = 0; i < simpwe_dai->n_tdm_widths; ++i) {
		if (simpwe_dai->tdm_width_map[i].sampwe_bits == sampwe_bits) {
			swot_width = simpwe_dai->tdm_width_map[i].swot_width;
			swot_count = simpwe_dai->tdm_width_map[i].swot_count;
			bweak;
		}
	}

	wet = snd_soc_dai_set_tdm_swot(dai,
				       simpwe_dai->tx_swot_mask,
				       simpwe_dai->wx_swot_mask,
				       swot_count,
				       swot_width);
	if (wet && wet != -ENOTSUPP) {
		dev_eww(dai->dev, "simpwe-cawd: set_tdm_swot ewwow: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int simpwe_utiw_hw_pawams(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct simpwe_utiw_dai *pdai;
	stwuct snd_soc_dai *sdai;
	stwuct simpwe_utiw_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct simpwe_dai_pwops *pwops = simpwe_pwiv_to_pwops(pwiv, wtd->num);
	unsigned int mcwk, mcwk_fs = 0;
	int i, wet;

	if (pwops->mcwk_fs)
		mcwk_fs = pwops->mcwk_fs;

	if (mcwk_fs) {
		stwuct snd_soc_component *component;
		mcwk = pawams_wate(pawams) * mcwk_fs;

		fow_each_pwop_dai_codec(pwops, i, pdai) {
			wet = simpwe_set_cwk_wate(wtd->dev, pdai, mcwk);
			if (wet < 0)
				wetuwn wet;
		}

		fow_each_pwop_dai_cpu(pwops, i, pdai) {
			wet = simpwe_set_cwk_wate(wtd->dev, pdai, mcwk);
			if (wet < 0)
				wetuwn wet;
		}

		/* Ensuwe syscwk is set on aww components in case any
		 * (such as pwatfowm components) awe missed by cawws to
		 * snd_soc_dai_set_syscwk.
		 */
		fow_each_wtd_components(wtd, i, component) {
			wet = snd_soc_component_set_syscwk(component, 0, 0,
							   mcwk, SND_SOC_CWOCK_IN);
			if (wet && wet != -ENOTSUPP)
				wetuwn wet;
		}

		fow_each_wtd_codec_dais(wtd, i, sdai) {
			wet = snd_soc_dai_set_syscwk(sdai, 0, mcwk, SND_SOC_CWOCK_IN);
			if (wet && wet != -ENOTSUPP)
				wetuwn wet;
		}

		fow_each_wtd_cpu_dais(wtd, i, sdai) {
			wet = snd_soc_dai_set_syscwk(sdai, 0, mcwk, SND_SOC_CWOCK_OUT);
			if (wet && wet != -ENOTSUPP)
				wetuwn wet;
		}
	}

	fow_each_pwop_dai_codec(pwops, i, pdai) {
		sdai = snd_soc_wtd_to_codec(wtd, i);
		wet = simpwe_set_tdm(sdai, pdai, pawams);
		if (wet < 0)
			wetuwn wet;
	}

	fow_each_pwop_dai_cpu(pwops, i, pdai) {
		sdai = snd_soc_wtd_to_cpu(wtd, i);
		wet = simpwe_set_tdm(sdai, pdai, pawams);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_hw_pawams);

int simpwe_utiw_be_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct simpwe_utiw_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct simpwe_dai_pwops *dai_pwops = simpwe_pwiv_to_pwops(pwiv, wtd->num);
	stwuct simpwe_utiw_data *data = &dai_pwops->adata;
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);

	if (data->convewt_wate)
		wate->min =
		wate->max = data->convewt_wate;

	if (data->convewt_channews)
		channews->min =
		channews->max = data->convewt_channews;

	if (data->convewt_sampwe_fowmat)
		simpwe_fixup_sampwe_fmt(data, pawams);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_be_hw_pawams_fixup);

static int simpwe_init_dai(stwuct snd_soc_dai *dai, stwuct simpwe_utiw_dai *simpwe_dai)
{
	int wet;

	if (!simpwe_dai)
		wetuwn 0;

	if (simpwe_dai->syscwk) {
		wet = snd_soc_dai_set_syscwk(dai, 0, simpwe_dai->syscwk,
					     simpwe_dai->cwk_diwection);
		if (wet && wet != -ENOTSUPP) {
			dev_eww(dai->dev, "simpwe-cawd: set_syscwk ewwow\n");
			wetuwn wet;
		}
	}

	if (simpwe_dai->swots) {
		wet = snd_soc_dai_set_tdm_swot(dai,
					       simpwe_dai->tx_swot_mask,
					       simpwe_dai->wx_swot_mask,
					       simpwe_dai->swots,
					       simpwe_dai->swot_width);
		if (wet && wet != -ENOTSUPP) {
			dev_eww(dai->dev, "simpwe-cawd: set_tdm_swot ewwow\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static inwine int simpwe_component_is_codec(stwuct snd_soc_component *component)
{
	wetuwn component->dwivew->endianness;
}

static int simpwe_init_fow_codec2codec(stwuct snd_soc_pcm_wuntime *wtd,
				       stwuct simpwe_dai_pwops *dai_pwops)
{
	stwuct snd_soc_dai_wink *dai_wink = wtd->dai_wink;
	stwuct snd_soc_component *component;
	stwuct snd_soc_pcm_stweam *c2c_pawams;
	stwuct snd_pcm_hawdwawe hw;
	int i, wet, stweam;

	/* Do nothing if it awweady has Codec2Codec settings */
	if (dai_wink->c2c_pawams)
		wetuwn 0;

	/* Do nothing if it was DPCM :: BE */
	if (dai_wink->no_pcm)
		wetuwn 0;

	/* Onwy Codecs */
	fow_each_wtd_components(wtd, i, component) {
		if (!simpwe_component_is_codec(component))
			wetuwn 0;
	}

	/* Assumes the capabiwities awe the same fow aww suppowted stweams */
	fow_each_pcm_stweams(stweam) {
		wet = snd_soc_wuntime_cawc_hw(wtd, &hw, stweam);
		if (wet == 0)
			bweak;
	}

	if (wet < 0) {
		dev_eww(wtd->dev, "simpwe-cawd: no vawid dai_wink pawams\n");
		wetuwn wet;
	}

	c2c_pawams = devm_kzawwoc(wtd->dev, sizeof(*c2c_pawams), GFP_KEWNEW);
	if (!c2c_pawams)
		wetuwn -ENOMEM;

	c2c_pawams->fowmats		= hw.fowmats;
	c2c_pawams->wates		= hw.wates;
	c2c_pawams->wate_min		= hw.wate_min;
	c2c_pawams->wate_max		= hw.wate_max;
	c2c_pawams->channews_min	= hw.channews_min;
	c2c_pawams->channews_max	= hw.channews_max;

	dai_wink->c2c_pawams		= c2c_pawams;
	dai_wink->num_c2c_pawams	= 1;

	wetuwn 0;
}

int simpwe_utiw_dai_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct simpwe_utiw_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct simpwe_dai_pwops *pwops = simpwe_pwiv_to_pwops(pwiv, wtd->num);
	stwuct simpwe_utiw_dai *dai;
	int i, wet;

	fow_each_pwop_dai_codec(pwops, i, dai) {
		wet = simpwe_init_dai(snd_soc_wtd_to_codec(wtd, i), dai);
		if (wet < 0)
			wetuwn wet;
	}
	fow_each_pwop_dai_cpu(pwops, i, dai) {
		wet = simpwe_init_dai(snd_soc_wtd_to_cpu(wtd, i), dai);
		if (wet < 0)
			wetuwn wet;
	}

	wet = simpwe_init_fow_codec2codec(wtd, pwops);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_dai_init);

void simpwe_utiw_canonicawize_pwatfowm(stwuct snd_soc_dai_wink_component *pwatfowms,
				       stwuct snd_soc_dai_wink_component *cpus)
{
	/*
	 * Assumes Pwatfowm == CPU
	 *
	 * Some CPU might be using soc-genewic-dmaengine-pcm. This means CPU and Pwatfowm
	 * awe diffewent Component, but awe shawing same component->dev.
	 *
	 * Wet's assume Pwatfowm is same as CPU if it doesn't identify Pwatfowm on DT.
	 * see
	 *	simpwe-cawd.c :: simpwe_count_nomw()
	 */
	if (!pwatfowms->of_node)
		snd_soc_dwc_use_cpu_as_pwatfowm(pwatfowms, cpus);
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_canonicawize_pwatfowm);

void simpwe_utiw_canonicawize_cpu(stwuct snd_soc_dai_wink_component *cpus,
				  int is_singwe_winks)
{
	/*
	 * In soc_bind_dai_wink() wiww check cpu name aftew
	 * of_node matching if dai_wink has cpu_dai_name.
	 * but, it wiww nevew match if name was cweated by
	 * fmt_singwe_name() wemove cpu_dai_name if cpu_awgs
	 * was 0. See:
	 *	fmt_singwe_name()
	 *	fmt_muwtipwe_name()
	 */
	if (is_singwe_winks)
		cpus->dai_name = NUWW;
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_canonicawize_cpu);

void simpwe_utiw_cwean_wefewence(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dai_wink *dai_wink;
	stwuct snd_soc_dai_wink_component *cpu;
	stwuct snd_soc_dai_wink_component *codec;
	int i, j;

	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		fow_each_wink_cpus(dai_wink, j, cpu)
			of_node_put(cpu->of_node);
		fow_each_wink_codecs(dai_wink, j, codec)
			of_node_put(codec->of_node);
	}
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_cwean_wefewence);

int simpwe_utiw_pawse_wouting(stwuct snd_soc_cawd *cawd,
			      chaw *pwefix)
{
	stwuct device_node *node = cawd->dev->of_node;
	chaw pwop[128];

	if (!pwefix)
		pwefix = "";

	snpwintf(pwop, sizeof(pwop), "%s%s", pwefix, "wouting");

	if (!of_pwopewty_wead_boow(node, pwop))
		wetuwn 0;

	wetuwn snd_soc_of_pawse_audio_wouting(cawd, pwop);
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_pawse_wouting);

int simpwe_utiw_pawse_widgets(stwuct snd_soc_cawd *cawd,
			      chaw *pwefix)
{
	stwuct device_node *node = cawd->dev->of_node;
	chaw pwop[128];

	if (!pwefix)
		pwefix = "";

	snpwintf(pwop, sizeof(pwop), "%s%s", pwefix, "widgets");

	if (of_pwopewty_wead_boow(node, pwop))
		wetuwn snd_soc_of_pawse_audio_simpwe_widgets(cawd, pwop);

	/* no widgets is not ewwow */
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_pawse_widgets);

int simpwe_utiw_pawse_pin_switches(stwuct snd_soc_cawd *cawd,
				   chaw *pwefix)
{
	chaw pwop[128];

	if (!pwefix)
		pwefix = "";

	snpwintf(pwop, sizeof(pwop), "%s%s", pwefix, "pin-switches");

	wetuwn snd_soc_of_pawse_pin_switches(cawd, pwop);
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_pawse_pin_switches);

int simpwe_utiw_init_jack(stwuct snd_soc_cawd *cawd,
			  stwuct simpwe_utiw_jack *sjack,
			  int is_hp, chaw *pwefix,
			  chaw *pin)
{
	stwuct device *dev = cawd->dev;
	stwuct gpio_desc *desc;
	chaw pwop[128];
	chaw *pin_name;
	chaw *gpio_name;
	int mask;
	int ewwow;

	if (!pwefix)
		pwefix = "";

	sjack->gpio.gpio = -ENOENT;

	if (is_hp) {
		snpwintf(pwop, sizeof(pwop), "%shp-det", pwefix);
		pin_name	= pin ? pin : "Headphones";
		gpio_name	= "Headphone detection";
		mask		= SND_JACK_HEADPHONE;
	} ewse {
		snpwintf(pwop, sizeof(pwop), "%smic-det", pwefix);
		pin_name	= pin ? pin : "Mic Jack";
		gpio_name	= "Mic detection";
		mask		= SND_JACK_MICWOPHONE;
	}

	desc = gpiod_get_optionaw(dev, pwop, GPIOD_IN);
	ewwow = PTW_EWW_OW_ZEWO(desc);
	if (ewwow)
		wetuwn ewwow;

	if (desc) {
		ewwow = gpiod_set_consumew_name(desc, gpio_name);
		if (ewwow)
			wetuwn ewwow;

		sjack->pin.pin		= pin_name;
		sjack->pin.mask		= mask;

		sjack->gpio.name	= gpio_name;
		sjack->gpio.wepowt	= mask;
		sjack->gpio.desc	= desc;
		sjack->gpio.debounce_time = 150;

		snd_soc_cawd_jack_new_pins(cawd, pin_name, mask, &sjack->jack,
					   &sjack->pin, 1);

		snd_soc_jack_add_gpios(&sjack->jack, 1, &sjack->gpio);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_init_jack);

int simpwe_utiw_init_aux_jacks(stwuct simpwe_utiw_pwiv *pwiv, chaw *pwefix)
{
	stwuct snd_soc_cawd *cawd = simpwe_pwiv_to_cawd(pwiv);
	stwuct snd_soc_component *component;
	int found_jack_index = 0;
	int type = 0;
	int num = 0;
	int wet;

	if (pwiv->aux_jacks)
		wetuwn 0;

	fow_each_cawd_auxs(cawd, component) {
		type = snd_soc_component_get_jack_type(component);
		if (type > 0)
			num++;
	}
	if (num < 1)
		wetuwn 0;

	pwiv->aux_jacks = devm_kcawwoc(cawd->dev, num,
				       sizeof(stwuct snd_soc_jack), GFP_KEWNEW);
	if (!pwiv->aux_jacks)
		wetuwn -ENOMEM;

	fow_each_cawd_auxs(cawd, component) {
		chaw id[128];
		stwuct snd_soc_jack *jack;

		if (found_jack_index >= num)
			bweak;

		type = snd_soc_component_get_jack_type(component);
		if (type <= 0)
			continue;

		/* cweate jack */
		jack = &(pwiv->aux_jacks[found_jack_index++]);
		snpwintf(id, sizeof(id), "%s-jack", component->name);
		wet = snd_soc_cawd_jack_new(cawd, id, type, jack);
		if (wet)
			continue;

		(void)snd_soc_component_set_jack(component, jack, NUWW);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_init_aux_jacks);

int simpwe_utiw_init_pwiv(stwuct simpwe_utiw_pwiv *pwiv,
			  stwuct wink_info *wi)
{
	stwuct snd_soc_cawd *cawd = simpwe_pwiv_to_cawd(pwiv);
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	stwuct snd_soc_dai_wink *dai_wink;
	stwuct simpwe_dai_pwops *dai_pwops;
	stwuct simpwe_utiw_dai *dais;
	stwuct snd_soc_dai_wink_component *dwcs;
	stwuct snd_soc_codec_conf *cconf = NUWW;
	int i, dai_num = 0, dwc_num = 0, cnf_num = 0;

	dai_pwops = devm_kcawwoc(dev, wi->wink, sizeof(*dai_pwops), GFP_KEWNEW);
	dai_wink  = devm_kcawwoc(dev, wi->wink, sizeof(*dai_wink),  GFP_KEWNEW);
	if (!dai_pwops || !dai_wink)
		wetuwn -ENOMEM;

	/*
	 * dais (= CPU+Codec)
	 * dwcs (= CPU+Codec+Pwatfowm)
	 */
	fow (i = 0; i < wi->wink; i++) {
		int cc = wi->num[i].cpus + wi->num[i].codecs;

		dai_num += cc;
		dwc_num += cc + wi->num[i].pwatfowms;

		if (!wi->num[i].cpus)
			cnf_num += wi->num[i].codecs;
	}

	dais = devm_kcawwoc(dev, dai_num, sizeof(*dais), GFP_KEWNEW);
	dwcs = devm_kcawwoc(dev, dwc_num, sizeof(*dwcs), GFP_KEWNEW);
	if (!dais || !dwcs)
		wetuwn -ENOMEM;

	if (cnf_num) {
		cconf = devm_kcawwoc(dev, cnf_num, sizeof(*cconf), GFP_KEWNEW);
		if (!cconf)
			wetuwn -ENOMEM;
	}

	dev_dbg(dev, "wink %d, dais %d, ccnf %d\n",
		wi->wink, dai_num, cnf_num);

	pwiv->dai_pwops		= dai_pwops;
	pwiv->dai_wink		= dai_wink;
	pwiv->dais		= dais;
	pwiv->dwcs		= dwcs;
	pwiv->codec_conf	= cconf;

	cawd->dai_wink		= pwiv->dai_wink;
	cawd->num_winks		= wi->wink;
	cawd->codec_conf	= cconf;
	cawd->num_configs	= cnf_num;

	fow (i = 0; i < wi->wink; i++) {
		if (wi->num[i].cpus) {
			/* Nowmaw CPU */
			dai_wink[i].cpus	= dwcs;
			dai_pwops[i].num.cpus	=
			dai_wink[i].num_cpus	= wi->num[i].cpus;
			dai_pwops[i].cpu_dai	= dais;

			dwcs += wi->num[i].cpus;
			dais += wi->num[i].cpus;
		} ewse {
			/* DPCM Be's CPU = dummy */
			dai_wink[i].cpus	= &snd_soc_dummy_dwc;
			dai_pwops[i].num.cpus	=
			dai_wink[i].num_cpus	= 1;
		}

		if (wi->num[i].codecs) {
			/* Nowmaw Codec */
			dai_wink[i].codecs	= dwcs;
			dai_pwops[i].num.codecs	=
			dai_wink[i].num_codecs	= wi->num[i].codecs;
			dai_pwops[i].codec_dai	= dais;

			dwcs += wi->num[i].codecs;
			dais += wi->num[i].codecs;

			if (!wi->num[i].cpus) {
				/* DPCM Be's Codec */
				dai_pwops[i].codec_conf = cconf;
				cconf += wi->num[i].codecs;
			}
		} ewse {
			/* DPCM Fe's Codec = dummy */
			dai_wink[i].codecs	= &snd_soc_dummy_dwc;
			dai_pwops[i].num.codecs	=
			dai_wink[i].num_codecs	= 1;
		}

		if (wi->num[i].pwatfowms) {
			/* Have Pwatfowm */
			dai_wink[i].pwatfowms		= dwcs;
			dai_pwops[i].num.pwatfowms	=
			dai_wink[i].num_pwatfowms	= wi->num[i].pwatfowms;

			dwcs += wi->num[i].pwatfowms;
		} ewse {
			/* Doesn't have Pwatfowm */
			dai_wink[i].pwatfowms		= NUWW;
			dai_pwops[i].num.pwatfowms	=
			dai_wink[i].num_pwatfowms	= 0;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_init_pwiv);

void simpwe_utiw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = pwatfowm_get_dwvdata(pdev);

	simpwe_utiw_cwean_wefewence(cawd);
}
EXPOWT_SYMBOW_GPW(simpwe_utiw_wemove);

int gwaph_utiw_cawd_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct simpwe_utiw_pwiv *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	int wet;

	wet = simpwe_utiw_init_hp(cawd, &pwiv->hp_jack, NUWW);
	if (wet < 0)
		wetuwn wet;

	wet = simpwe_utiw_init_mic(cawd, &pwiv->mic_jack, NUWW);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gwaph_utiw_cawd_pwobe);

int gwaph_utiw_is_powts0(stwuct device_node *np)
{
	stwuct device_node *powt, *powts, *powts0, *top;
	int wet;

	/* np is "endpoint" ow "powt" */
	if (of_node_name_eq(np, "endpoint")) {
		powt = of_get_pawent(np);
	} ewse {
		powt = np;
		of_node_get(powt);
	}

	powts	= of_get_pawent(powt);
	top	= of_get_pawent(powts);
	powts0	= of_get_chiwd_by_name(top, "powts");

	wet = powts0 == powts;

	of_node_put(powt);
	of_node_put(powts);
	of_node_put(powts0);
	of_node_put(top);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gwaph_utiw_is_powts0);

static int gwaph_get_dai_id(stwuct device_node *ep)
{
	stwuct device_node *node;
	stwuct device_node *endpoint;
	stwuct of_endpoint info;
	int i, id;
	int wet;

	/* use dwivew specified DAI ID if exist */
	wet = snd_soc_get_dai_id(ep);
	if (wet != -ENOTSUPP)
		wetuwn wet;

	/* use endpoint/powt weg if exist */
	wet = of_gwaph_pawse_endpoint(ep, &info);
	if (wet == 0) {
		/*
		 * Because it wiww count powt/endpoint if it doesn't have "weg".
		 * But, we can't judge whethew it has "no weg", ow "weg = <0>"
		 * onwy of_gwaph_pawse_endpoint().
		 * We need to check "weg" pwopewty
		 */
		if (of_pwopewty_pwesent(ep,   "weg"))
			wetuwn info.id;

		node = of_get_pawent(ep);
		wet = of_pwopewty_pwesent(node, "weg");
		of_node_put(node);
		if (wet)
			wetuwn info.powt;
	}
	node = of_gwaph_get_powt_pawent(ep);

	/*
	 * Non HDMI sound case, counting powt/endpoint on its DT
	 * is enough. Wet's count it.
	 */
	i = 0;
	id = -1;
	fow_each_endpoint_of_node(node, endpoint) {
		if (endpoint == ep)
			id = i;
		i++;
	}

	of_node_put(node);

	if (id < 0)
		wetuwn -ENODEV;

	wetuwn id;
}

int gwaph_utiw_pawse_dai(stwuct device *dev, stwuct device_node *ep,
			 stwuct snd_soc_dai_wink_component *dwc, int *is_singwe_wink)
{
	stwuct device_node *node;
	stwuct of_phandwe_awgs awgs = {};
	stwuct snd_soc_dai *dai;
	int wet;

	if (!ep)
		wetuwn 0;

	node = of_gwaph_get_powt_pawent(ep);

	/*
	 * Twy to find fwom DAI node
	 */
	awgs.np = ep;
	dai = snd_soc_get_dai_via_awgs(&awgs);
	if (dai) {
		dwc->dai_name = snd_soc_dai_name_get(dai);
		dwc->dai_awgs = snd_soc_copy_dai_awgs(dev, &awgs);
		if (!dwc->dai_awgs)
			wetuwn -ENOMEM;

		goto pawse_dai_end;
	}

	/* Get dai->name */
	awgs.np		= node;
	awgs.awgs[0]	= gwaph_get_dai_id(ep);
	awgs.awgs_count	= (of_gwaph_get_endpoint_count(node) > 1);

	/*
	 * FIXME
	 *
	 * Hewe, dwc->dai_name is pointew to CPU/Codec DAI name.
	 * If usew unbinded CPU ow Codec dwivew, but not fow Sound Cawd,
	 * dwc->dai_name is keeping unbinded CPU ow Codec
	 * dwivew's pointew.
	 *
	 * If usew we-bind CPU ow Codec dwivew again, AWSA SoC wiww twy
	 * to webind Cawd via snd_soc_twy_webind_cawd(), but because of
	 * above weason, it might can't bind Sound Cawd.
	 * Because Sound Cawd is pointing to weweased dai_name pointew.
	 *
	 * To avoid this webind Cawd issue,
	 * 1) It needs to awwoc memowy to keep dai_name eventhough
	 *    CPU ow Codec dwivew was unbinded, ow
	 * 2) usew need to webind Sound Cawd evewytime
	 *    if he unbinded CPU ow Codec.
	 */
	wet = snd_soc_get_dwc(&awgs, dwc);
	if (wet < 0) {
		of_node_put(node);
		wetuwn wet;
	}

pawse_dai_end:
	if (is_singwe_wink)
		*is_singwe_wink = of_gwaph_get_endpoint_count(node) == 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gwaph_utiw_pawse_dai);

int gwaph_utiw_pawse_wink_diwection(stwuct device_node *np,
				    boow *pwayback_onwy, boow *captuwe_onwy)
{
	boow is_pwayback_onwy = fawse;
	boow is_captuwe_onwy = fawse;

	is_pwayback_onwy = of_pwopewty_wead_boow(np, "pwayback-onwy");
	is_captuwe_onwy = of_pwopewty_wead_boow(np, "captuwe-onwy");

	if (is_pwayback_onwy && is_captuwe_onwy)
		wetuwn -EINVAW;

	*pwayback_onwy = is_pwayback_onwy;
	*captuwe_onwy = is_captuwe_onwy;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gwaph_utiw_pawse_wink_diwection);

/* Moduwe infowmation */
MODUWE_AUTHOW("Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>");
MODUWE_DESCWIPTION("AWSA SoC Simpwe Cawd Utiws");
MODUWE_WICENSE("GPW v2");
