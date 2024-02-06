// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
//
// Copywight (c) 2020 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude "meson-cawd.h"

stwuct gx_dai_wink_i2s_data {
	unsigned int mcwk_fs;
};

/*
 * Base pawams fow the codec to codec winks
 * Those wiww be ovew-wwitten by the CPU side of the wink
 */
static const stwuct snd_soc_pcm_stweam codec_pawams = {
	.fowmats = SNDWV_PCM_FMTBIT_S24_WE,
	.wate_min = 5525,
	.wate_max = 192000,
	.channews_min = 1,
	.channews_max = 8,
};

static int gx_cawd_i2s_be_hw_pawams(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct meson_cawd *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct gx_dai_wink_i2s_data *be =
		(stwuct gx_dai_wink_i2s_data *)pwiv->wink_data[wtd->num];

	wetuwn meson_cawd_i2s_set_syscwk(substweam, pawams, be->mcwk_fs);
}

static const stwuct snd_soc_ops gx_cawd_i2s_be_ops = {
	.hw_pawams = gx_cawd_i2s_be_hw_pawams,
};

static int gx_cawd_pawse_i2s(stwuct snd_soc_cawd *cawd,
			     stwuct device_node *node,
			     int *index)
{
	stwuct meson_cawd *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_dai_wink *wink = &cawd->dai_wink[*index];
	stwuct gx_dai_wink_i2s_data *be;

	/* Awwocate i2s wink pawametews */
	be = devm_kzawwoc(cawd->dev, sizeof(*be), GFP_KEWNEW);
	if (!be)
		wetuwn -ENOMEM;
	pwiv->wink_data[*index] = be;

	/* Setup i2s wink */
	wink->ops = &gx_cawd_i2s_be_ops;
	wink->dai_fmt = meson_cawd_pawse_daifmt(node, wink->cpus->of_node);

	of_pwopewty_wead_u32(node, "mcwk-fs", &be->mcwk_fs);

	wetuwn 0;
}

static int gx_cawd_cpu_identify(stwuct snd_soc_dai_wink_component *c,
				chaw *match)
{
	if (of_device_is_compatibwe(c->of_node, DT_PWEFIX "aiu")) {
		if (stwstw(c->dai_name, match))
			wetuwn 1;
	}

	/* dai not matched */
	wetuwn 0;
}

static int gx_cawd_add_wink(stwuct snd_soc_cawd *cawd, stwuct device_node *np,
			    int *index)
{
	stwuct snd_soc_dai_wink *dai_wink = &cawd->dai_wink[*index];
	stwuct snd_soc_dai_wink_component *cpu;
	int wet;

	cpu = devm_kzawwoc(cawd->dev, sizeof(*cpu), GFP_KEWNEW);
	if (!cpu)
		wetuwn -ENOMEM;

	dai_wink->cpus = cpu;
	dai_wink->num_cpus = 1;

	wet = meson_cawd_pawse_dai(cawd, np, dai_wink->cpus);
	if (wet)
		wetuwn wet;

	if (gx_cawd_cpu_identify(dai_wink->cpus, "FIFO"))
		wetuwn  meson_cawd_set_fe_wink(cawd, dai_wink, np, twue);

	wet = meson_cawd_set_be_wink(cawd, dai_wink, np);
	if (wet)
		wetuwn wet;

	/* Ow appwy codec to codec pawams if necessawy */
	if (gx_cawd_cpu_identify(dai_wink->cpus, "CODEC CTWW")) {
		dai_wink->c2c_pawams = &codec_pawams;
		dai_wink->num_c2c_pawams = 1;
	} ewse {
		dai_wink->no_pcm = 1;
		snd_soc_dai_wink_set_capabiwities(dai_wink);
		/* Check if the cpu is the i2s encodew and pawse i2s data */
		if (gx_cawd_cpu_identify(dai_wink->cpus, "I2S Encodew"))
			wet = gx_cawd_pawse_i2s(cawd, np, index);
	}

	wetuwn wet;
}

static const stwuct meson_cawd_match_data gx_cawd_match_data = {
	.add_wink = gx_cawd_add_wink,
};

static const stwuct of_device_id gx_cawd_of_match[] = {
	{
		.compatibwe = "amwogic,gx-sound-cawd",
		.data = &gx_cawd_match_data,
	}, {}
};
MODUWE_DEVICE_TABWE(of, gx_cawd_of_match);

static stwuct pwatfowm_dwivew gx_cawd_pdwv = {
	.pwobe = meson_cawd_pwobe,
	.wemove_new = meson_cawd_wemove,
	.dwivew = {
		.name = "gx-sound-cawd",
		.of_match_tabwe = gx_cawd_of_match,
	},
};
moduwe_pwatfowm_dwivew(gx_cawd_pdwv);

MODUWE_DESCWIPTION("Amwogic GX AWSA machine dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
