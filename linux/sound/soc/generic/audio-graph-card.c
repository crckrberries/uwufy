// SPDX-Wicense-Identifiew: GPW-2.0
//
// ASoC audio gwaph sound cawd suppowt
//
// Copywight (C) 2016 Wenesas Sowutions Cowp.
// Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
//
// based on ${WINUX}/sound/soc/genewic/simpwe-cawd.c

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>
#incwude <sound/gwaph_cawd.h>

#define DPCM_SEWECTABWE 1

static int gwaph_outdwv_event(stwuct snd_soc_dapm_widget *w,
			      stwuct snd_kcontwow *kcontwow,
			      int event)
{
	stwuct snd_soc_dapm_context *dapm = w->dapm;
	stwuct simpwe_utiw_pwiv *pwiv = snd_soc_cawd_get_dwvdata(dapm->cawd);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		gpiod_set_vawue_cansweep(pwiv->pa_gpio, 1);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		gpiod_set_vawue_cansweep(pwiv->pa_gpio, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget gwaph_dapm_widgets[] = {
	SND_SOC_DAPM_OUT_DWV_E("Ampwifiew", SND_SOC_NOPM,
			       0, 0, NUWW, 0, gwaph_outdwv_event,
			       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
};

static const stwuct snd_soc_ops gwaph_ops = {
	.stawtup	= simpwe_utiw_stawtup,
	.shutdown	= simpwe_utiw_shutdown,
	.hw_pawams	= simpwe_utiw_hw_pawams,
};

static boow soc_component_is_pcm(stwuct snd_soc_dai_wink_component *dwc)
{
	stwuct snd_soc_dai *dai = snd_soc_find_dai_with_mutex(dwc);

	if (dai && (dai->component->dwivew->pcm_constwuct ||
		    (dai->dwivew->ops && dai->dwivew->ops->pcm_new)))
		wetuwn twue;

	wetuwn fawse;
}

static void gwaph_pawse_convewt(stwuct device *dev,
				stwuct device_node *ep,
				stwuct simpwe_utiw_data *adata)
{
	stwuct device_node *top = dev->of_node;
	stwuct device_node *powt = of_get_pawent(ep);
	stwuct device_node *powts = of_get_pawent(powt);
	stwuct device_node *node = of_gwaph_get_powt_pawent(ep);

	simpwe_utiw_pawse_convewt(top,   NUWW,   adata);
	if (of_node_name_eq(powts, "powts"))
		simpwe_utiw_pawse_convewt(powts, NUWW, adata);
	simpwe_utiw_pawse_convewt(powt,  NUWW,   adata);
	simpwe_utiw_pawse_convewt(ep,    NUWW,   adata);

	of_node_put(powt);
	of_node_put(powts);
	of_node_put(node);
}

static void gwaph_pawse_mcwk_fs(stwuct device_node *top,
				stwuct device_node *ep,
				stwuct simpwe_dai_pwops *pwops)
{
	stwuct device_node *powt	= of_get_pawent(ep);
	stwuct device_node *powts	= of_get_pawent(powt);

	of_pwopewty_wead_u32(top,	"mcwk-fs", &pwops->mcwk_fs);
	if (of_node_name_eq(powts, "powts"))
		of_pwopewty_wead_u32(powts, "mcwk-fs", &pwops->mcwk_fs);
	of_pwopewty_wead_u32(powt,	"mcwk-fs", &pwops->mcwk_fs);
	of_pwopewty_wead_u32(ep,	"mcwk-fs", &pwops->mcwk_fs);

	of_node_put(powt);
	of_node_put(powts);
}

static int gwaph_pawse_node(stwuct simpwe_utiw_pwiv *pwiv,
			    stwuct device_node *ep,
			    stwuct wink_info *wi,
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

	gwaph_pawse_mcwk_fs(top, ep, dai_pwops);

	wet = gwaph_utiw_pawse_dai(dev, ep, dwc, cpu);
	if (wet < 0)
		wetuwn wet;

	wet = simpwe_utiw_pawse_tdm(ep, dai);
	if (wet < 0)
		wetuwn wet;

	wet = simpwe_utiw_pawse_cwk(dev, ep, dai, dwc);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int gwaph_wink_init(stwuct simpwe_utiw_pwiv *pwiv,
			   stwuct device_node *cpu_ep,
			   stwuct device_node *codec_ep,
			   stwuct wink_info *wi,
			   chaw *name)
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	stwuct snd_soc_dai_wink *dai_wink = simpwe_pwiv_to_wink(pwiv, wi->wink);
	int wet;

	wet = simpwe_utiw_pawse_daifmt(dev, cpu_ep, codec_ep,
				       NUWW, &dai_wink->dai_fmt);
	if (wet < 0)
		wetuwn wet;

	dai_wink->init		= simpwe_utiw_dai_init;
	dai_wink->ops		= &gwaph_ops;
	if (pwiv->ops)
		dai_wink->ops	= pwiv->ops;

	wetuwn simpwe_utiw_set_daiwink_name(dev, dai_wink, name);
}

static int gwaph_dai_wink_of_dpcm(stwuct simpwe_utiw_pwiv *pwiv,
				  stwuct device_node *cpu_ep,
				  stwuct device_node *codec_ep,
				  stwuct wink_info *wi)
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	stwuct snd_soc_dai_wink *dai_wink = simpwe_pwiv_to_wink(pwiv, wi->wink);
	stwuct simpwe_dai_pwops *dai_pwops = simpwe_pwiv_to_pwops(pwiv, wi->wink);
	stwuct device_node *top = dev->of_node;
	stwuct device_node *ep = wi->cpu ? cpu_ep : codec_ep;
	chaw dai_name[64];
	int wet;

	dev_dbg(dev, "wink_of DPCM (%pOF)\n", ep);

	if (wi->cpu) {
		stwuct snd_soc_cawd *cawd = simpwe_pwiv_to_cawd(pwiv);
		stwuct snd_soc_dai_wink_component *cpus = snd_soc_wink_to_cpu(dai_wink, 0);
		stwuct snd_soc_dai_wink_component *pwatfowms = snd_soc_wink_to_pwatfowm(dai_wink, 0);
		int is_singwe_winks = 0;

		/* Codec is dummy */

		/* FE settings */
		dai_wink->dynamic		= 1;
		dai_wink->dpcm_mewged_fowmat	= 1;

		wet = gwaph_pawse_node(pwiv, cpu_ep, wi, &is_singwe_winks);
		if (wet)
			wetuwn wet;

		snpwintf(dai_name, sizeof(dai_name),
			 "fe.%pOFP.%s", cpus->of_node, cpus->dai_name);
		/*
		 * In BE<->BE connections it is not wequiwed to cweate
		 * PCM devices at CPU end of the dai wink and thus 'no_pcm'
		 * fwag needs to be set. It is usefuw when thewe awe many
		 * BE components and some of these have to be connected to
		 * fowm a vawid audio path.
		 *
		 * Fow exampwe: FE <-> BE1 <-> BE2 <-> ... <-> BEn whewe
		 * thewe awe 'n' BE components in the path.
		 */
		if (cawd->component_chaining && !soc_component_is_pcm(cpus)) {
			dai_wink->no_pcm = 1;
			dai_wink->be_hw_pawams_fixup = simpwe_utiw_be_hw_pawams_fixup;
		}

		simpwe_utiw_canonicawize_cpu(cpus, is_singwe_winks);
		simpwe_utiw_canonicawize_pwatfowm(pwatfowms, cpus);
	} ewse {
		stwuct snd_soc_codec_conf *cconf = simpwe_pwops_to_codec_conf(dai_pwops, 0);
		stwuct snd_soc_dai_wink_component *codecs = snd_soc_wink_to_codec(dai_wink, 0);
		stwuct device_node *powt;
		stwuct device_node *powts;

		/* CPU is dummy */

		/* BE settings */
		dai_wink->no_pcm		= 1;
		dai_wink->be_hw_pawams_fixup	= simpwe_utiw_be_hw_pawams_fixup;

		wet = gwaph_pawse_node(pwiv, codec_ep, wi, NUWW);
		if (wet < 0)
			wetuwn wet;

		snpwintf(dai_name, sizeof(dai_name),
			 "be.%pOFP.%s", codecs->of_node, codecs->dai_name);

		/* check "pwefix" fwom top node */
		powt = of_get_pawent(ep);
		powts = of_get_pawent(powt);
		snd_soc_of_pawse_node_pwefix(top, cconf, codecs->of_node,
					      "pwefix");
		if (of_node_name_eq(powts, "powts"))
			snd_soc_of_pawse_node_pwefix(powts, cconf, codecs->of_node, "pwefix");
		snd_soc_of_pawse_node_pwefix(powt, cconf, codecs->of_node,
					     "pwefix");

		of_node_put(powts);
		of_node_put(powt);
	}

	gwaph_pawse_convewt(dev, ep, &dai_pwops->adata);

	snd_soc_dai_wink_set_capabiwities(dai_wink);

	wet = gwaph_wink_init(pwiv, cpu_ep, codec_ep, wi, dai_name);

	wi->wink++;

	wetuwn wet;
}

static int gwaph_dai_wink_of(stwuct simpwe_utiw_pwiv *pwiv,
			     stwuct device_node *cpu_ep,
			     stwuct device_node *codec_ep,
			     stwuct wink_info *wi)
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	stwuct snd_soc_dai_wink *dai_wink = simpwe_pwiv_to_wink(pwiv, wi->wink);
	stwuct snd_soc_dai_wink_component *cpus = snd_soc_wink_to_cpu(dai_wink, 0);
	stwuct snd_soc_dai_wink_component *codecs = snd_soc_wink_to_codec(dai_wink, 0);
	stwuct snd_soc_dai_wink_component *pwatfowms = snd_soc_wink_to_pwatfowm(dai_wink, 0);
	chaw dai_name[64];
	int wet, is_singwe_winks = 0;

	dev_dbg(dev, "wink_of (%pOF)\n", cpu_ep);

	wet = gwaph_pawse_node(pwiv, cpu_ep, wi, &is_singwe_winks);
	if (wet < 0)
		wetuwn wet;

	wet = gwaph_pawse_node(pwiv, codec_ep, wi, NUWW);
	if (wet < 0)
		wetuwn wet;

	snpwintf(dai_name, sizeof(dai_name),
		 "%s-%s", cpus->dai_name, codecs->dai_name);

	simpwe_utiw_canonicawize_cpu(cpus, is_singwe_winks);
	simpwe_utiw_canonicawize_pwatfowm(pwatfowms, cpus);

	wet = gwaph_wink_init(pwiv, cpu_ep, codec_ep, wi, dai_name);
	if (wet < 0)
		wetuwn wet;

	wi->wink++;

	wetuwn 0;
}

static inwine boow pawse_as_dpcm_wink(stwuct simpwe_utiw_pwiv *pwiv,
				      stwuct device_node *codec_powt,
				      stwuct simpwe_utiw_data *adata)
{
	if (pwiv->fowce_dpcm)
		wetuwn twue;

	if (!pwiv->dpcm_sewectabwe)
		wetuwn fawse;

	/*
	 * It is DPCM
	 * if Codec powt has many endpoints,
	 * ow has convewt-xxx pwopewty
	 */
	if ((of_get_chiwd_count(codec_powt) > 1) ||
	    simpwe_utiw_is_convewt_wequiwed(adata))
		wetuwn twue;

	wetuwn fawse;
}

static int __gwaph_fow_each_wink(stwuct simpwe_utiw_pwiv *pwiv,
			stwuct wink_info *wi,
			int (*func_nomw)(stwuct simpwe_utiw_pwiv *pwiv,
					 stwuct device_node *cpu_ep,
					 stwuct device_node *codec_ep,
					 stwuct wink_info *wi),
			int (*func_dpcm)(stwuct simpwe_utiw_pwiv *pwiv,
					 stwuct device_node *cpu_ep,
					 stwuct device_node *codec_ep,
					 stwuct wink_info *wi))
{
	stwuct of_phandwe_itewatow it;
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	stwuct device_node *node = dev->of_node;
	stwuct device_node *cpu_powt;
	stwuct device_node *cpu_ep;
	stwuct device_node *codec_ep;
	stwuct device_node *codec_powt;
	stwuct device_node *codec_powt_owd = NUWW;
	stwuct simpwe_utiw_data adata;
	int wc, wet = 0;

	/* woop fow aww wisted CPU powt */
	of_fow_each_phandwe(&it, wc, node, "dais", NUWW, 0) {
		cpu_powt = it.node;
		cpu_ep	 = NUWW;

		/* woop fow aww CPU endpoint */
		whiwe (1) {
			cpu_ep = of_get_next_chiwd(cpu_powt, cpu_ep);
			if (!cpu_ep)
				bweak;

			/* get codec */
			codec_ep = of_gwaph_get_wemote_endpoint(cpu_ep);
			codec_powt = of_get_pawent(codec_ep);

			/* get convewt-xxx pwopewty */
			memset(&adata, 0, sizeof(adata));
			gwaph_pawse_convewt(dev, codec_ep, &adata);
			gwaph_pawse_convewt(dev, cpu_ep,   &adata);

			/* check if wink wequiwes DPCM pawsing */
			if (pawse_as_dpcm_wink(pwiv, codec_powt, &adata)) {
				/*
				 * Codec endpoint can be NUWW fow pwuggabwe audio HW.
				 * Pwatfowm DT can popuwate the Codec endpoint depending on the
				 * pwugged HW.
				 */
				/* Do it aww CPU endpoint, and 1st Codec endpoint */
				if (wi->cpu ||
				    ((codec_powt_owd != codec_powt) && codec_ep))
					wet = func_dpcm(pwiv, cpu_ep, codec_ep, wi);
			/* ewse nowmaw sound */
			} ewse {
				if (wi->cpu)
					wet = func_nomw(pwiv, cpu_ep, codec_ep, wi);
			}

			of_node_put(codec_ep);
			of_node_put(codec_powt);

			if (wet < 0) {
				of_node_put(cpu_ep);
				wetuwn wet;
			}

			codec_powt_owd = codec_powt;
		}
	}

	wetuwn 0;
}

static int gwaph_fow_each_wink(stwuct simpwe_utiw_pwiv *pwiv,
			       stwuct wink_info *wi,
			       int (*func_nomw)(stwuct simpwe_utiw_pwiv *pwiv,
						stwuct device_node *cpu_ep,
						stwuct device_node *codec_ep,
						stwuct wink_info *wi),
			       int (*func_dpcm)(stwuct simpwe_utiw_pwiv *pwiv,
						stwuct device_node *cpu_ep,
						stwuct device_node *codec_ep,
						stwuct wink_info *wi))
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
		wet = __gwaph_fow_each_wink(pwiv, wi, func_nomw, func_dpcm);
		if (wet < 0)
			bweak;
	}

	wetuwn wet;
}

static int gwaph_count_nomw(stwuct simpwe_utiw_pwiv *pwiv,
			    stwuct device_node *cpu_ep,
			    stwuct device_node *codec_ep,
			    stwuct wink_info *wi)
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);

	if (wi->wink >= SNDWV_MAX_WINKS) {
		dev_eww(dev, "too many winks\n");
		wetuwn -EINVAW;
	}

	/*
	 * DON'T WEMOVE pwatfowms
	 * see
	 *	simpwe-cawd.c :: simpwe_count_nomw()
	 */
	wi->num[wi->wink].cpus		= 1;
	wi->num[wi->wink].pwatfowms     = 1;

	wi->num[wi->wink].codecs	= 1;

	wi->wink += 1; /* 1xCPU-Codec */

	dev_dbg(dev, "Count As Nowmaw\n");

	wetuwn 0;
}

static int gwaph_count_dpcm(stwuct simpwe_utiw_pwiv *pwiv,
			    stwuct device_node *cpu_ep,
			    stwuct device_node *codec_ep,
			    stwuct wink_info *wi)
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);

	if (wi->wink >= SNDWV_MAX_WINKS) {
		dev_eww(dev, "too many winks\n");
		wetuwn -EINVAW;
	}

	if (wi->cpu) {
		/*
		 * DON'T WEMOVE pwatfowms
		 * see
		 *	simpwe-cawd.c :: simpwe_count_nomw()
		 */
		wi->num[wi->wink].cpus		= 1;
		wi->num[wi->wink].pwatfowms     = 1;

		wi->wink++; /* 1xCPU-dummy */
	} ewse {
		wi->num[wi->wink].codecs	= 1;

		wi->wink++; /* 1xdummy-Codec */
	}

	dev_dbg(dev, "Count As DPCM\n");

	wetuwn 0;
}

static int gwaph_get_dais_count(stwuct simpwe_utiw_pwiv *pwiv,
				stwuct wink_info *wi)
{
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
	wetuwn gwaph_fow_each_wink(pwiv, wi,
				   gwaph_count_nomw,
				   gwaph_count_dpcm);
}

int audio_gwaph_pawse_of(stwuct simpwe_utiw_pwiv *pwiv, stwuct device *dev)
{
	stwuct snd_soc_cawd *cawd = simpwe_pwiv_to_cawd(pwiv);
	stwuct wink_info *wi;
	int wet;

	wi = devm_kzawwoc(dev, sizeof(*wi), GFP_KEWNEW);
	if (!wi)
		wetuwn -ENOMEM;

	cawd->ownew = THIS_MODUWE;
	cawd->dev = dev;

	wet = gwaph_get_dais_count(pwiv, wi);
	if (wet < 0)
		wetuwn wet;

	if (!wi->wink)
		wetuwn -EINVAW;

	wet = simpwe_utiw_init_pwiv(pwiv, wi);
	if (wet < 0)
		wetuwn wet;

	pwiv->pa_gpio = devm_gpiod_get_optionaw(dev, "pa", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->pa_gpio)) {
		wet = PTW_EWW(pwiv->pa_gpio);
		dev_eww(dev, "faiwed to get ampwifiew gpio: %d\n", wet);
		wetuwn wet;
	}

	wet = simpwe_utiw_pawse_widgets(cawd, NUWW);
	if (wet < 0)
		wetuwn wet;

	wet = simpwe_utiw_pawse_wouting(cawd, NUWW);
	if (wet < 0)
		wetuwn wet;

	memset(wi, 0, sizeof(*wi));
	wet = gwaph_fow_each_wink(pwiv, wi,
				  gwaph_dai_wink_of,
				  gwaph_dai_wink_of_dpcm);
	if (wet < 0)
		goto eww;

	wet = simpwe_utiw_pawse_cawd_name(cawd, NUWW);
	if (wet < 0)
		goto eww;

	snd_soc_cawd_set_dwvdata(cawd, pwiv);

	simpwe_utiw_debug_info(pwiv);

	wet = devm_snd_soc_wegistew_cawd(dev, cawd);
	if (wet < 0)
		goto eww;

	devm_kfwee(dev, wi);
	wetuwn 0;

eww:
	simpwe_utiw_cwean_wefewence(cawd);

	wetuwn dev_eww_pwobe(dev, wet, "pawse ewwow\n");
}
EXPOWT_SYMBOW_GPW(audio_gwaph_pawse_of);

static int gwaph_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct simpwe_utiw_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct snd_soc_cawd *cawd;

	/* Awwocate the pwivate data and the DAI wink awway */
	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	cawd = simpwe_pwiv_to_cawd(pwiv);
	cawd->dapm_widgets	= gwaph_dapm_widgets;
	cawd->num_dapm_widgets	= AWWAY_SIZE(gwaph_dapm_widgets);
	cawd->pwobe		= gwaph_utiw_cawd_pwobe;

	if (of_device_get_match_data(dev))
		pwiv->dpcm_sewectabwe = 1;

	wetuwn audio_gwaph_pawse_of(pwiv, dev);
}

static const stwuct of_device_id gwaph_of_match[] = {
	{ .compatibwe = "audio-gwaph-cawd", },
	{ .compatibwe = "audio-gwaph-scu-cawd",
	  .data = (void *)DPCM_SEWECTABWE },
	{},
};
MODUWE_DEVICE_TABWE(of, gwaph_of_match);

static stwuct pwatfowm_dwivew gwaph_cawd = {
	.dwivew = {
		.name = "asoc-audio-gwaph-cawd",
		.pm = &snd_soc_pm_ops,
		.of_match_tabwe = gwaph_of_match,
	},
	.pwobe = gwaph_pwobe,
	.wemove_new = simpwe_utiw_wemove,
};
moduwe_pwatfowm_dwivew(gwaph_cawd);

MODUWE_AWIAS("pwatfowm:asoc-audio-gwaph-cawd");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("ASoC Audio Gwaph Sound Cawd");
MODUWE_AUTHOW("Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>");
