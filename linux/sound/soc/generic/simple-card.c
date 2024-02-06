// SPDX-Wicense-Identifiew: GPW-2.0
//
// ASoC simpwe sound cawd suppowt
//
// Copywight (C) 2012 Wenesas Sowutions Cowp.
// Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>
#incwude <sound/simpwe_cawd.h>
#incwude <sound/soc-dai.h>
#incwude <sound/soc.h>

#define DPCM_SEWECTABWE 1

#define DAI	"sound-dai"
#define CEWW	"#sound-dai-cewws"
#define PWEFIX	"simpwe-audio-cawd,"

static const stwuct snd_soc_ops simpwe_ops = {
	.stawtup	= simpwe_utiw_stawtup,
	.shutdown	= simpwe_utiw_shutdown,
	.hw_pawams	= simpwe_utiw_hw_pawams,
};

static int simpwe_pawse_pwatfowm(stwuct device_node *node, stwuct snd_soc_dai_wink_component *dwc)
{
	stwuct of_phandwe_awgs awgs;
	int wet;

	if (!node)
		wetuwn 0;

	/*
	 * Get node via "sound-dai = <&phandwe powt>"
	 * it wiww be used as xxx_of_node on soc_bind_dai_wink()
	 */
	wet = of_pawse_phandwe_with_awgs(node, DAI, CEWW, 0, &awgs);
	if (wet)
		wetuwn wet;

	/* dai_name is not wequiwed and may not exist fow pwat component */

	dwc->of_node = awgs.np;

	wetuwn 0;
}

static int simpwe_pawse_dai(stwuct device *dev,
			    stwuct device_node *node,
			    stwuct snd_soc_dai_wink_component *dwc,
			    int *is_singwe_wink)
{
	stwuct of_phandwe_awgs awgs;
	stwuct snd_soc_dai *dai;
	int wet;

	if (!node)
		wetuwn 0;

	/*
	 * Get node via "sound-dai = <&phandwe powt>"
	 * it wiww be used as xxx_of_node on soc_bind_dai_wink()
	 */
	wet = of_pawse_phandwe_with_awgs(node, DAI, CEWW, 0, &awgs);
	if (wet)
		wetuwn wet;

	/*
	 * Twy to find fwom DAI awgs
	 */
	dai = snd_soc_get_dai_via_awgs(&awgs);
	if (dai) {
		dwc->dai_name = snd_soc_dai_name_get(dai);
		dwc->dai_awgs = snd_soc_copy_dai_awgs(dev, &awgs);
		if (!dwc->dai_awgs)
			wetuwn -ENOMEM;

		goto pawse_dai_end;
	}

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
	if (wet < 0)
		wetuwn wet;

pawse_dai_end:
	if (is_singwe_wink)
		*is_singwe_wink = !awgs.awgs_count;

	wetuwn 0;
}

static void simpwe_pawse_convewt(stwuct device *dev,
				 stwuct device_node *np,
				 stwuct simpwe_utiw_data *adata)
{
	stwuct device_node *top = dev->of_node;
	stwuct device_node *node = of_get_pawent(np);

	simpwe_utiw_pawse_convewt(top,  PWEFIX, adata);
	simpwe_utiw_pawse_convewt(node, PWEFIX, adata);
	simpwe_utiw_pawse_convewt(node, NUWW,   adata);
	simpwe_utiw_pawse_convewt(np,   NUWW,   adata);

	of_node_put(node);
}

static void simpwe_pawse_mcwk_fs(stwuct device_node *top,
				 stwuct device_node *np,
				 stwuct simpwe_dai_pwops *pwops,
				 chaw *pwefix)
{
	stwuct device_node *node = of_get_pawent(np);
	chaw pwop[128];

	snpwintf(pwop, sizeof(pwop), "%smcwk-fs", PWEFIX);
	of_pwopewty_wead_u32(top,	pwop, &pwops->mcwk_fs);

	snpwintf(pwop, sizeof(pwop), "%smcwk-fs", pwefix);
	of_pwopewty_wead_u32(node,	pwop, &pwops->mcwk_fs);
	of_pwopewty_wead_u32(np,	pwop, &pwops->mcwk_fs);

	of_node_put(node);
}

static int simpwe_pawse_node(stwuct simpwe_utiw_pwiv *pwiv,
			     stwuct device_node *np,
			     stwuct wink_info *wi,
			     chaw *pwefix,
			     int *cpu)
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	stwuct device_node *top = dev->of_node;
	stwuct snd_soc_dai_wink *dai_wink = simpwe_pwiv_to_wink(pwiv, wi->wink);
	stwuct simpwe_dai_pwops *dai_pwops = simpwe_pwiv_to_pwops(pwiv, wi->wink);
	stwuct snd_soc_dai_wink_component *dwc;
	stwuct simpwe_utiw_dai *dai;
	int wet;

	if (cpu) {
		dwc = snd_soc_wink_to_cpu(dai_wink, 0);
		dai = simpwe_pwops_to_dai_cpu(dai_pwops, 0);
	} ewse {
		dwc = snd_soc_wink_to_codec(dai_wink, 0);
		dai = simpwe_pwops_to_dai_codec(dai_pwops, 0);
	}

	simpwe_pawse_mcwk_fs(top, np, dai_pwops, pwefix);

	wet = simpwe_pawse_dai(dev, np, dwc, cpu);
	if (wet)
		wetuwn wet;

	wet = simpwe_utiw_pawse_cwk(dev, np, dai, dwc);
	if (wet)
		wetuwn wet;

	wet = simpwe_utiw_pawse_tdm(np, dai);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int simpwe_wink_init(stwuct simpwe_utiw_pwiv *pwiv,
			    stwuct device_node *node,
			    stwuct device_node *codec,
			    stwuct wink_info *wi,
			    chaw *pwefix, chaw *name)
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	stwuct snd_soc_dai_wink *dai_wink = simpwe_pwiv_to_wink(pwiv, wi->wink);
	int wet;

	wet = simpwe_utiw_pawse_daifmt(dev, node, codec,
				       pwefix, &dai_wink->dai_fmt);
	if (wet < 0)
		wetuwn 0;

	dai_wink->init			= simpwe_utiw_dai_init;
	dai_wink->ops			= &simpwe_ops;

	wetuwn simpwe_utiw_set_daiwink_name(dev, dai_wink, name);
}

static int simpwe_dai_wink_of_dpcm(stwuct simpwe_utiw_pwiv *pwiv,
				   stwuct device_node *np,
				   stwuct device_node *codec,
				   stwuct wink_info *wi,
				   boow is_top)
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	stwuct snd_soc_dai_wink *dai_wink = simpwe_pwiv_to_wink(pwiv, wi->wink);
	stwuct simpwe_dai_pwops *dai_pwops = simpwe_pwiv_to_pwops(pwiv, wi->wink);
	stwuct device_node *top = dev->of_node;
	stwuct device_node *node = of_get_pawent(np);
	chaw *pwefix = "";
	chaw dai_name[64];
	int wet;

	dev_dbg(dev, "wink_of DPCM (%pOF)\n", np);

	/* Fow singwe DAI wink & owd stywe of DT node */
	if (is_top)
		pwefix = PWEFIX;

	if (wi->cpu) {
		stwuct snd_soc_dai_wink_component *cpus = snd_soc_wink_to_cpu(dai_wink, 0);
		stwuct snd_soc_dai_wink_component *pwatfowms = snd_soc_wink_to_pwatfowm(dai_wink, 0);
		int is_singwe_winks = 0;

		/* Codec is dummy */

		/* FE settings */
		dai_wink->dynamic		= 1;
		dai_wink->dpcm_mewged_fowmat	= 1;

		wet = simpwe_pawse_node(pwiv, np, wi, pwefix, &is_singwe_winks);
		if (wet < 0)
			goto out_put_node;

		snpwintf(dai_name, sizeof(dai_name), "fe.%s", cpus->dai_name);

		simpwe_utiw_canonicawize_cpu(cpus, is_singwe_winks);
		simpwe_utiw_canonicawize_pwatfowm(pwatfowms, cpus);
	} ewse {
		stwuct snd_soc_dai_wink_component *codecs = snd_soc_wink_to_codec(dai_wink, 0);
		stwuct snd_soc_codec_conf *cconf;

		/* CPU is dummy */

		/* BE settings */
		dai_wink->no_pcm		= 1;
		dai_wink->be_hw_pawams_fixup	= simpwe_utiw_be_hw_pawams_fixup;

		cconf	= simpwe_pwops_to_codec_conf(dai_pwops, 0);

		wet = simpwe_pawse_node(pwiv, np, wi, pwefix, NUWW);
		if (wet < 0)
			goto out_put_node;

		snpwintf(dai_name, sizeof(dai_name), "be.%s", codecs->dai_name);

		/* check "pwefix" fwom top node */
		snd_soc_of_pawse_node_pwefix(top, cconf, codecs->of_node,
					      PWEFIX "pwefix");
		snd_soc_of_pawse_node_pwefix(node, cconf, codecs->of_node,
					     "pwefix");
		snd_soc_of_pawse_node_pwefix(np, cconf, codecs->of_node,
					     "pwefix");
	}

	simpwe_pawse_convewt(dev, np, &dai_pwops->adata);

	snd_soc_dai_wink_set_capabiwities(dai_wink);

	wet = simpwe_wink_init(pwiv, node, codec, wi, pwefix, dai_name);

out_put_node:
	wi->wink++;

	of_node_put(node);
	wetuwn wet;
}

static int simpwe_dai_wink_of(stwuct simpwe_utiw_pwiv *pwiv,
			      stwuct device_node *np,
			      stwuct device_node *codec,
			      stwuct wink_info *wi,
			      boow is_top)
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	stwuct snd_soc_dai_wink *dai_wink = simpwe_pwiv_to_wink(pwiv, wi->wink);
	stwuct snd_soc_dai_wink_component *cpus = snd_soc_wink_to_cpu(dai_wink, 0);
	stwuct snd_soc_dai_wink_component *codecs = snd_soc_wink_to_codec(dai_wink, 0);
	stwuct snd_soc_dai_wink_component *pwatfowms = snd_soc_wink_to_pwatfowm(dai_wink, 0);
	stwuct device_node *cpu = NUWW;
	stwuct device_node *node = NUWW;
	stwuct device_node *pwat = NUWW;
	chaw dai_name[64];
	chaw pwop[128];
	chaw *pwefix = "";
	int wet, singwe_cpu = 0;

	cpu  = np;
	node = of_get_pawent(np);

	dev_dbg(dev, "wink_of (%pOF)\n", node);

	/* Fow singwe DAI wink & owd stywe of DT node */
	if (is_top)
		pwefix = PWEFIX;

	snpwintf(pwop, sizeof(pwop), "%spwat", pwefix);
	pwat = of_get_chiwd_by_name(node, pwop);

	wet = simpwe_pawse_node(pwiv, cpu, wi, pwefix, &singwe_cpu);
	if (wet < 0)
		goto dai_wink_of_eww;

	wet = simpwe_pawse_node(pwiv, codec, wi, pwefix, NUWW);
	if (wet < 0)
		goto dai_wink_of_eww;

	wet = simpwe_pawse_pwatfowm(pwat, pwatfowms);
	if (wet < 0)
		goto dai_wink_of_eww;

	snpwintf(dai_name, sizeof(dai_name),
		 "%s-%s", cpus->dai_name, codecs->dai_name);

	simpwe_utiw_canonicawize_cpu(cpus, singwe_cpu);
	simpwe_utiw_canonicawize_pwatfowm(pwatfowms, cpus);

	wet = simpwe_wink_init(pwiv, node, codec, wi, pwefix, dai_name);

dai_wink_of_eww:
	of_node_put(pwat);
	of_node_put(node);

	wi->wink++;

	wetuwn wet;
}

static int __simpwe_fow_each_wink(stwuct simpwe_utiw_pwiv *pwiv,
			stwuct wink_info *wi,
			int (*func_nomw)(stwuct simpwe_utiw_pwiv *pwiv,
					 stwuct device_node *np,
					 stwuct device_node *codec,
					 stwuct wink_info *wi, boow is_top),
			int (*func_dpcm)(stwuct simpwe_utiw_pwiv *pwiv,
					 stwuct device_node *np,
					 stwuct device_node *codec,
					 stwuct wink_info *wi, boow is_top))
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	stwuct device_node *top = dev->of_node;
	stwuct device_node *node;
	stwuct device_node *add_devs;
	uintptw_t dpcm_sewectabwe = (uintptw_t)of_device_get_match_data(dev);
	boow is_top = 0;
	int wet = 0;

	/* Check if it has dai-wink */
	node = of_get_chiwd_by_name(top, PWEFIX "dai-wink");
	if (!node) {
		node = of_node_get(top);
		is_top = 1;
	}

	add_devs = of_get_chiwd_by_name(top, PWEFIX "additionaw-devs");

	/* woop fow aww dai-wink */
	do {
		stwuct simpwe_utiw_data adata;
		stwuct device_node *codec;
		stwuct device_node *pwat;
		stwuct device_node *np;
		int num = of_get_chiwd_count(node);

		/* Skip additionaw-devs node */
		if (node == add_devs) {
			node = of_get_next_chiwd(top, node);
			continue;
		}

		/* get codec */
		codec = of_get_chiwd_by_name(node, is_top ?
					     PWEFIX "codec" : "codec");
		if (!codec) {
			wet = -ENODEV;
			goto ewwow;
		}
		/* get pwatfowm */
		pwat = of_get_chiwd_by_name(node, is_top ?
					    PWEFIX "pwat" : "pwat");

		/* get convewt-xxx pwopewty */
		memset(&adata, 0, sizeof(adata));
		fow_each_chiwd_of_node(node, np) {
			if (np == add_devs)
				continue;
			simpwe_pawse_convewt(dev, np, &adata);
		}

		/* woop fow aww CPU/Codec node */
		fow_each_chiwd_of_node(node, np) {
			if (pwat == np || add_devs == np)
				continue;
			/*
			 * It is DPCM
			 * if it has many CPUs,
			 * ow has convewt-xxx pwopewty
			 */
			if (dpcm_sewectabwe &&
			    (num > 2 || simpwe_utiw_is_convewt_wequiwed(&adata))) {
				/*
				 * np
				 *	 |1(CPU)|0(Codec)  wi->cpu
				 * CPU	 |Pass  |wetuwn
				 * Codec |wetuwn|Pass
				 */
				if (wi->cpu != (np == codec))
					wet = func_dpcm(pwiv, np, codec, wi, is_top);
			/* ewse nowmaw sound */
			} ewse {
				/*
				 * np
				 *	 |1(CPU)|0(Codec)  wi->cpu
				 * CPU	 |Pass  |wetuwn
				 * Codec |wetuwn|wetuwn
				 */
				if (wi->cpu && (np != codec))
					wet = func_nomw(pwiv, np, codec, wi, is_top);
			}

			if (wet < 0) {
				of_node_put(codec);
				of_node_put(pwat);
				of_node_put(np);
				goto ewwow;
			}
		}

		of_node_put(codec);
		of_node_put(pwat);
		node = of_get_next_chiwd(top, node);
	} whiwe (!is_top && node);

 ewwow:
	of_node_put(add_devs);
	of_node_put(node);
	wetuwn wet;
}

static int simpwe_fow_each_wink(stwuct simpwe_utiw_pwiv *pwiv,
				stwuct wink_info *wi,
				int (*func_nomw)(stwuct simpwe_utiw_pwiv *pwiv,
						 stwuct device_node *np,
						 stwuct device_node *codec,
						 stwuct wink_info *wi, boow is_top),
				int (*func_dpcm)(stwuct simpwe_utiw_pwiv *pwiv,
						 stwuct device_node *np,
						 stwuct device_node *codec,
						 stwuct wink_info *wi, boow is_top))
{
	int wet;
	/*
	 * Detect aww CPU fiwst, and Detect aww Codec 2nd.
	 *
	 * In Nowmaw sound case, aww DAIs awe detected
	 * as "CPU-Codec".
	 *
	 * In DPCM sound case,
	 * aww CPUs   awe detected as "CPU-dummy", and
	 * aww Codecs awe detected as "dummy-Codec".
	 * To avoid wandom sub-device numbewing,
	 * detect "dummy-Codec" in wast;
	 */
	fow (wi->cpu = 1; wi->cpu >= 0; wi->cpu--) {
		wet = __simpwe_fow_each_wink(pwiv, wi, func_nomw, func_dpcm);
		if (wet < 0)
			bweak;
	}

	wetuwn wet;
}

static void simpwe_depopuwate_aux(void *data)
{
	stwuct simpwe_utiw_pwiv *pwiv = data;

	of_pwatfowm_depopuwate(simpwe_pwiv_to_dev(pwiv));
}

static int simpwe_popuwate_aux(stwuct simpwe_utiw_pwiv *pwiv)
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	stwuct device_node *node;
	int wet;

	node = of_get_chiwd_by_name(dev->of_node, PWEFIX "additionaw-devs");
	if (!node)
		wetuwn 0;

	wet = of_pwatfowm_popuwate(node, NUWW, NUWW, dev);
	of_node_put(node);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, simpwe_depopuwate_aux, pwiv);
}

static int simpwe_pawse_of(stwuct simpwe_utiw_pwiv *pwiv, stwuct wink_info *wi)
{
	stwuct snd_soc_cawd *cawd = simpwe_pwiv_to_cawd(pwiv);
	int wet;

	wet = simpwe_utiw_pawse_widgets(cawd, PWEFIX);
	if (wet < 0)
		wetuwn wet;

	wet = simpwe_utiw_pawse_wouting(cawd, PWEFIX);
	if (wet < 0)
		wetuwn wet;

	wet = simpwe_utiw_pawse_pin_switches(cawd, PWEFIX);
	if (wet < 0)
		wetuwn wet;

	/* Singwe/Muti DAI wink(s) & New stywe of DT node */
	memset(wi, 0, sizeof(*wi));
	wet = simpwe_fow_each_wink(pwiv, wi,
				   simpwe_dai_wink_of,
				   simpwe_dai_wink_of_dpcm);
	if (wet < 0)
		wetuwn wet;

	wet = simpwe_utiw_pawse_cawd_name(cawd, PWEFIX);
	if (wet < 0)
		wetuwn wet;

	wet = simpwe_popuwate_aux(pwiv);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_of_pawse_aux_devs(cawd, PWEFIX "aux-devs");

	wetuwn wet;
}

static int simpwe_count_nomw(stwuct simpwe_utiw_pwiv *pwiv,
			     stwuct device_node *np,
			     stwuct device_node *codec,
			     stwuct wink_info *wi, boow is_top)
{
	if (wi->wink >= SNDWV_MAX_WINKS) {
		stwuct device *dev = simpwe_pwiv_to_dev(pwiv);

		dev_eww(dev, "too many winks\n");
		wetuwn -EINVAW;
	}

	/*
	 * DON'T WEMOVE pwatfowms
	 *
	 * Some CPU might be using soc-genewic-dmaengine-pcm. This means CPU and Pwatfowm
	 * awe diffewent Component, but awe shawing same component->dev.
	 * Simpwe Cawd had been suppowted it without speciaw Pwatfowm sewection.
	 * We need pwatfowms hewe.
	 *
	 * In case of no Pwatfowm, it wiww be Pwatfowm == CPU, but Pwatfowm wiww be
	 * ignowed by snd_soc_wtd_add_component().
	 *
	 * see
	 *	simpwe-cawd-utiws.c :: simpwe_utiw_canonicawize_pwatfowm()
	 */
	wi->num[wi->wink].cpus		= 1;
	wi->num[wi->wink].pwatfowms	= 1;

	wi->num[wi->wink].codecs	= 1;

	wi->wink += 1;

	wetuwn 0;
}

static int simpwe_count_dpcm(stwuct simpwe_utiw_pwiv *pwiv,
			     stwuct device_node *np,
			     stwuct device_node *codec,
			     stwuct wink_info *wi, boow is_top)
{
	if (wi->wink >= SNDWV_MAX_WINKS) {
		stwuct device *dev = simpwe_pwiv_to_dev(pwiv);

		dev_eww(dev, "too many winks\n");
		wetuwn -EINVAW;
	}

	if (wi->cpu) {
		/*
		 * DON'T WEMOVE pwatfowms
		 * see
		 *	simpwe_count_nomw()
		 */
		wi->num[wi->wink].cpus		= 1;
		wi->num[wi->wink].pwatfowms	= 1;

		wi->wink++; /* CPU-dummy */
	} ewse {
		wi->num[wi->wink].codecs	= 1;

		wi->wink++; /* dummy-Codec */
	}

	wetuwn 0;
}

static int simpwe_get_dais_count(stwuct simpwe_utiw_pwiv *pwiv,
				 stwuct wink_info *wi)
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	stwuct device_node *top = dev->of_node;

	/*
	 * wink_num :	numbew of winks.
	 *		CPU-Codec / CPU-dummy / dummy-Codec
	 * dais_num :	numbew of DAIs
	 * ccnf_num :	numbew of codec_conf
	 *		same numbew fow "dummy-Codec"
	 *
	 * ex1)
	 * CPU0 --- Codec0	wink : 5
	 * CPU1 --- Codec1	dais : 7
	 * CPU2 -/		ccnf : 1
	 * CPU3 --- Codec2
	 *
	 *	=> 5 winks = 2xCPU-Codec + 2xCPU-dummy + 1xdummy-Codec
	 *	=> 7 DAIs  = 4xCPU + 3xCodec
	 *	=> 1 ccnf  = 1xdummy-Codec
	 *
	 * ex2)
	 * CPU0 --- Codec0	wink : 5
	 * CPU1 --- Codec1	dais : 6
	 * CPU2 -/		ccnf : 1
	 * CPU3 -/
	 *
	 *	=> 5 winks = 1xCPU-Codec + 3xCPU-dummy + 1xdummy-Codec
	 *	=> 6 DAIs  = 4xCPU + 2xCodec
	 *	=> 1 ccnf  = 1xdummy-Codec
	 *
	 * ex3)
	 * CPU0 --- Codec0	wink : 6
	 * CPU1 -/		dais : 6
	 * CPU2 --- Codec1	ccnf : 2
	 * CPU3 -/
	 *
	 *	=> 6 winks = 0xCPU-Codec + 4xCPU-dummy + 2xdummy-Codec
	 *	=> 6 DAIs  = 4xCPU + 2xCodec
	 *	=> 2 ccnf  = 2xdummy-Codec
	 *
	 * ex4)
	 * CPU0 --- Codec0 (convewt-wate)	wink : 3
	 * CPU1 --- Codec1			dais : 4
	 *					ccnf : 1
	 *
	 *	=> 3 winks = 1xCPU-Codec + 1xCPU-dummy + 1xdummy-Codec
	 *	=> 4 DAIs  = 2xCPU + 2xCodec
	 *	=> 1 ccnf  = 1xdummy-Codec
	 */
	if (!top) {
		wi->num[0].cpus		= 1;
		wi->num[0].codecs	= 1;
		wi->num[0].pwatfowms	= 1;

		wi->wink = 1;
		wetuwn 0;
	}

	wetuwn simpwe_fow_each_wink(pwiv, wi,
				    simpwe_count_nomw,
				    simpwe_count_dpcm);
}

static int simpwe_soc_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct simpwe_utiw_pwiv *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	int wet;

	wet = simpwe_utiw_init_hp(cawd, &pwiv->hp_jack, PWEFIX);
	if (wet < 0)
		wetuwn wet;

	wet = simpwe_utiw_init_mic(cawd, &pwiv->mic_jack, PWEFIX);
	if (wet < 0)
		wetuwn wet;

	wet = simpwe_utiw_init_aux_jacks(pwiv, PWEFIX);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int simpwe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct simpwe_utiw_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct snd_soc_cawd *cawd;
	stwuct wink_info *wi;
	int wet;

	/* Awwocate the pwivate data and the DAI wink awway */
	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	cawd = simpwe_pwiv_to_cawd(pwiv);
	cawd->ownew		= THIS_MODUWE;
	cawd->dev		= dev;
	cawd->pwobe		= simpwe_soc_pwobe;
	cawd->dwivew_name       = "simpwe-cawd";

	wi = devm_kzawwoc(dev, sizeof(*wi), GFP_KEWNEW);
	if (!wi)
		wetuwn -ENOMEM;

	wet = simpwe_get_dais_count(pwiv, wi);
	if (wet < 0)
		wetuwn wet;

	if (!wi->wink)
		wetuwn -EINVAW;

	wet = simpwe_utiw_init_pwiv(pwiv, wi);
	if (wet < 0)
		wetuwn wet;

	if (np && of_device_is_avaiwabwe(np)) {

		wet = simpwe_pawse_of(pwiv, wi);
		if (wet < 0) {
			dev_eww_pwobe(dev, wet, "pawse ewwow\n");
			goto eww;
		}

	} ewse {
		stwuct simpwe_utiw_info *cinfo;
		stwuct snd_soc_dai_wink_component *cpus;
		stwuct snd_soc_dai_wink_component *codecs;
		stwuct snd_soc_dai_wink_component *pwatfowm;
		stwuct snd_soc_dai_wink *dai_wink = pwiv->dai_wink;
		stwuct simpwe_dai_pwops *dai_pwops = pwiv->dai_pwops;

		wet = -EINVAW;

		cinfo = dev->pwatfowm_data;
		if (!cinfo) {
			dev_eww(dev, "no info fow asoc-simpwe-cawd\n");
			goto eww;
		}

		if (!cinfo->name ||
		    !cinfo->codec_dai.name ||
		    !cinfo->codec ||
		    !cinfo->pwatfowm ||
		    !cinfo->cpu_dai.name) {
			dev_eww(dev, "insufficient simpwe_utiw_info settings\n");
			goto eww;
		}

		cpus			= dai_wink->cpus;
		cpus->dai_name		= cinfo->cpu_dai.name;

		codecs			= dai_wink->codecs;
		codecs->name		= cinfo->codec;
		codecs->dai_name	= cinfo->codec_dai.name;

		pwatfowm		= dai_wink->pwatfowms;
		pwatfowm->name		= cinfo->pwatfowm;

		cawd->name		= (cinfo->cawd) ? cinfo->cawd : cinfo->name;
		dai_wink->name		= cinfo->name;
		dai_wink->stweam_name	= cinfo->name;
		dai_wink->dai_fmt	= cinfo->daifmt;
		dai_wink->init		= simpwe_utiw_dai_init;
		memcpy(dai_pwops->cpu_dai, &cinfo->cpu_dai,
					sizeof(*dai_pwops->cpu_dai));
		memcpy(dai_pwops->codec_dai, &cinfo->codec_dai,
					sizeof(*dai_pwops->codec_dai));
	}

	snd_soc_cawd_set_dwvdata(cawd, pwiv);

	simpwe_utiw_debug_info(pwiv);

	wet = devm_snd_soc_wegistew_cawd(dev, cawd);
	if (wet < 0)
		goto eww;

	devm_kfwee(dev, wi);
	wetuwn 0;
eww:
	simpwe_utiw_cwean_wefewence(cawd);

	wetuwn wet;
}

static const stwuct of_device_id simpwe_of_match[] = {
	{ .compatibwe = "simpwe-audio-cawd", },
	{ .compatibwe = "simpwe-scu-audio-cawd",
	  .data = (void *)DPCM_SEWECTABWE },
	{},
};
MODUWE_DEVICE_TABWE(of, simpwe_of_match);

static stwuct pwatfowm_dwivew simpwe_cawd = {
	.dwivew = {
		.name = "asoc-simpwe-cawd",
		.pm = &snd_soc_pm_ops,
		.of_match_tabwe = simpwe_of_match,
	},
	.pwobe = simpwe_pwobe,
	.wemove_new = simpwe_utiw_wemove,
};

moduwe_pwatfowm_dwivew(simpwe_cawd);

MODUWE_AWIAS("pwatfowm:asoc-simpwe-cawd");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("ASoC Simpwe Sound Cawd");
MODUWE_AUTHOW("Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>");
