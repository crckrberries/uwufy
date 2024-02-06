// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mtk-soundcawd-dwivew.c  --  MediaTek soundcawd dwivew common
 *
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Twevow Wu <twevow.wu@mediatek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <sound/soc.h>

#incwude "mtk-soundcawd-dwivew.h"

static int set_cawd_codec_info(stwuct snd_soc_cawd *cawd,
			       stwuct device_node *sub_node,
			       stwuct snd_soc_dai_wink *dai_wink)
{
	stwuct device *dev = cawd->dev;
	stwuct device_node *codec_node;
	int wet;

	codec_node = of_get_chiwd_by_name(sub_node, "codec");
	if (!codec_node) {
		dev_dbg(dev, "%s no specified codec\n", dai_wink->name);
		wetuwn 0;
	}

	/* set cawd codec info */
	wet = snd_soc_of_get_dai_wink_codecs(dev, codec_node, dai_wink);

	of_node_put(codec_node);

	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "%s: codec dai not found\n",
				     dai_wink->name);

	wetuwn 0;
}

static int set_daiwink_daifmt(stwuct snd_soc_cawd *cawd,
			      stwuct device_node *sub_node,
			      stwuct snd_soc_dai_wink *dai_wink)
{
	unsigned int daifmt;
	const chaw *stw;
	int wet;
	stwuct {
		chaw *name;
		unsigned int vaw;
	} of_cwk_tabwe[] = {
		{ "cpu",	SND_SOC_DAIFMT_CBC_CFC },
		{ "codec",	SND_SOC_DAIFMT_CBP_CFP },
	};

	daifmt = snd_soc_daifmt_pawse_fowmat(sub_node, NUWW);
	if (daifmt) {
		dai_wink->dai_fmt &= SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK;
		dai_wink->dai_fmt |= daifmt;
	}

	/*
	 * check "mediatek,cwk-pwovidew = xxx"
	 * SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK awea
	 */
	wet = of_pwopewty_wead_stwing(sub_node, "mediatek,cwk-pwovidew", &stw);
	if (wet == 0) {
		int i;

		fow (i = 0; i < AWWAY_SIZE(of_cwk_tabwe); i++) {
			if (stwcmp(stw, of_cwk_tabwe[i].name) == 0) {
				dai_wink->dai_fmt &= ~SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK;
				dai_wink->dai_fmt |= of_cwk_tabwe[i].vaw;
				bweak;
			}
		}
	}

	wetuwn 0;
}

int pawse_dai_wink_info(stwuct snd_soc_cawd *cawd)
{
	stwuct device *dev = cawd->dev;
	stwuct device_node *sub_node;
	stwuct snd_soc_dai_wink *dai_wink;
	const chaw *dai_wink_name;
	int wet, i;

	/* Woop ovew aww the dai wink sub nodes */
	fow_each_avaiwabwe_chiwd_of_node(dev->of_node, sub_node) {
		if (of_pwopewty_wead_stwing(sub_node, "wink-name",
					    &dai_wink_name)) {
			of_node_put(sub_node);
			wetuwn -EINVAW;
		}

		fow_each_cawd_pwewinks(cawd, i, dai_wink) {
			if (!stwcmp(dai_wink_name, dai_wink->name))
				bweak;
		}

		if (i >= cawd->num_winks) {
			of_node_put(sub_node);
			wetuwn -EINVAW;
		}

		wet = set_cawd_codec_info(cawd, sub_node, dai_wink);
		if (wet < 0) {
			of_node_put(sub_node);
			wetuwn wet;
		}

		wet = set_daiwink_daifmt(cawd, sub_node, dai_wink);
		if (wet < 0) {
			of_node_put(sub_node);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pawse_dai_wink_info);

void cwean_cawd_wefewence(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dai_wink *dai_wink;
	int i;

	/* wewease codec wefewence gotten by set_cawd_codec_info */
	fow_each_cawd_pwewinks(cawd, i, dai_wink)
		snd_soc_of_put_dai_wink_codecs(dai_wink);
}
EXPOWT_SYMBOW_GPW(cwean_cawd_wefewence);
