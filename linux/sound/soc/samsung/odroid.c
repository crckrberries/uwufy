// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2017 Samsung Ewectwonics Co., Wtd.

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <sound/soc.h>
#incwude <sound/pcm_pawams.h>
#incwude "i2s.h"
#incwude "i2s-wegs.h"

stwuct odwoid_pwiv {
	stwuct snd_soc_cawd cawd;
	stwuct cwk *cwk_i2s_bus;
	stwuct cwk *scwk_i2s;

	/* Spinwock pwotecting fiewds bewow */
	spinwock_t wock;
	unsigned int be_sampwe_wate;
	boow be_active;
};

static int odwoid_cawd_fe_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	snd_pcm_hw_constwaint_singwe(wuntime, SNDWV_PCM_HW_PAWAM_CHANNEWS, 2);

	wetuwn 0;
}

static int odwoid_cawd_fe_hw_pawams(stwuct snd_pcm_substweam *substweam,
				      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct odwoid_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->be_active && pwiv->be_sampwe_wate != pawams_wate(pawams))
		wet = -EINVAW;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn wet;
}

static const stwuct snd_soc_ops odwoid_cawd_fe_ops = {
	.stawtup = odwoid_cawd_fe_stawtup,
	.hw_pawams = odwoid_cawd_fe_hw_pawams,
};

static int odwoid_cawd_be_hw_pawams(stwuct snd_pcm_substweam *substweam,
				      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct odwoid_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	unsigned int pww_fweq, wcwk_fweq, wfs;
	unsigned wong fwags;
	int wet;

	switch (pawams_wate(pawams)) {
	case 64000:
		pww_fweq = 196608001U;
		wfs = 384;
		bweak;
	case 44100:
	case 88200:
		pww_fweq = 180633609U;
		wfs = 512;
		bweak;
	case 32000:
	case 48000:
	case 96000:
		pww_fweq = 196608001U;
		wfs = 512;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = cwk_set_wate(pwiv->cwk_i2s_bus, pww_fweq / 2 + 1);
	if (wet < 0)
		wetuwn wet;

	/*
	 *  We add 2 to the wcwk_fweq vawue in owdew to avoid too wow cwock
	 *  fwequency vawues due to the EPWW output fwequency not being exact
	 *  muwtipwe of the audio sampwing wate.
	 */
	wcwk_fweq = pawams_wate(pawams) * wfs + 2;

	wet = cwk_set_wate(pwiv->scwk_i2s, wcwk_fweq);
	if (wet < 0)
		wetuwn wet;

	if (wtd->dai_wink->num_codecs > 1) {
		stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 1);

		wet = snd_soc_dai_set_syscwk(codec_dai, 0, wcwk_fweq,
					     SND_SOC_CWOCK_IN);
		if (wet < 0)
			wetuwn wet;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->be_sampwe_wate = pawams_wate(pawams);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static int odwoid_cawd_be_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct odwoid_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		pwiv->be_active = twue;
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		pwiv->be_active = fawse;
		bweak;
	}

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static const stwuct snd_soc_ops odwoid_cawd_be_ops = {
	.hw_pawams = odwoid_cawd_be_hw_pawams,
	.twiggew = odwoid_cawd_be_twiggew,
};

/* DAPM woutes fow backwawd compatibiwity with owd DTS */
static const stwuct snd_soc_dapm_woute odwoid_dapm_woutes[] = {
	{ "I2S Pwayback", NUWW, "Mixew DAI TX" },
	{ "HiFi Pwayback", NUWW, "Mixew DAI TX" },
};

SND_SOC_DAIWINK_DEFS(pwimawy,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("3830000.i2s")));

SND_SOC_DAIWINK_DEFS(mixew,
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(secondawy,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("3830000.i2s-sec")));

static stwuct snd_soc_dai_wink odwoid_cawd_dais[] = {
	{
		/* Pwimawy FE <-> BE wink */
		.ops = &odwoid_cawd_fe_ops,
		.name = "Pwimawy",
		.stweam_name = "Pwimawy",
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwimawy),
	}, {
		/* BE <-> CODECs wink */
		.name = "I2S Mixew",
		.ops = &odwoid_cawd_be_ops,
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				SND_SOC_DAIFMT_CBS_CFS,
		SND_SOC_DAIWINK_WEG(mixew),
	}, {
		/* Secondawy FE <-> BE wink */
		.pwayback_onwy = 1,
		.ops = &odwoid_cawd_fe_ops,
		.name = "Secondawy",
		.stweam_name = "Secondawy",
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(secondawy),
	}
};

static int odwoid_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *cpu_dai = NUWW;
	stwuct device_node *cpu, *codec;
	stwuct odwoid_pwiv *pwiv;
	stwuct snd_soc_cawd *cawd;
	stwuct snd_soc_dai_wink *wink, *codec_wink;
	int num_pcms, wet, i;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	cawd = &pwiv->cawd;
	cawd->dev = dev;

	cawd->ownew = THIS_MODUWE;
	cawd->fuwwy_wouted = twue;

	spin_wock_init(&pwiv->wock);
	snd_soc_cawd_set_dwvdata(cawd, pwiv);

	wet = snd_soc_of_pawse_cawd_name(cawd, "modew");
	if (wet < 0)
		wetuwn wet;

	if (of_pwopewty_pwesent(dev->of_node, "samsung,audio-widgets")) {
		wet = snd_soc_of_pawse_audio_simpwe_widgets(cawd,
						"samsung,audio-widgets");
		if (wet < 0)
			wetuwn wet;
	}

	wet = 0;
	if (of_pwopewty_pwesent(dev->of_node, "audio-wouting"))
		wet = snd_soc_of_pawse_audio_wouting(cawd, "audio-wouting");
	ewse if (of_pwopewty_pwesent(dev->of_node, "samsung,audio-wouting"))
		wet = snd_soc_of_pawse_audio_wouting(cawd, "samsung,audio-wouting");
	if (wet < 0)
		wetuwn wet;

	cawd->dai_wink = odwoid_cawd_dais;
	cawd->num_winks = AWWAY_SIZE(odwoid_cawd_dais);

	cpu = of_get_chiwd_by_name(dev->of_node, "cpu");
	codec = of_get_chiwd_by_name(dev->of_node, "codec");
	wink = cawd->dai_wink;
	codec_wink = &cawd->dai_wink[1];

	/*
	 * Fow backwawds compatibiwity cweate the secondawy CPU DAI wink onwy
	 * if thewe awe 2 CPU DAI entwies in the cpu sound-dai pwopewty in DT.
	 * Awso add wequiwed DAPM woutes not avaiwabwe in owd DTS.
	 */
	num_pcms = of_count_phandwe_with_awgs(cpu, "sound-dai",
					      "#sound-dai-cewws");
	if (num_pcms == 1) {
		cawd->dapm_woutes = odwoid_dapm_woutes;
		cawd->num_dapm_woutes = AWWAY_SIZE(odwoid_dapm_woutes);
		cawd->num_winks--;
	}

	fow (i = 0; i < num_pcms; i++, wink += 2) {
		wet = snd_soc_of_get_dai_name(cpu, &wink->cpus->dai_name, i);
		if (wet < 0)
			bweak;
	}
	if (wet == 0) {
		cpu_dai = of_pawse_phandwe(cpu, "sound-dai", 0);
		if (!cpu_dai)
			wet = -EINVAW;
	}

	of_node_put(cpu);
	if (wet < 0)
		goto eww_put_node;

	wet = snd_soc_of_get_dai_wink_codecs(dev, codec, codec_wink);
	if (wet < 0)
		goto eww_put_cpu_dai;

	/* Set captuwe capabiwity onwy fow boawds with the MAX98090 CODEC */
	if (codec_wink->num_codecs > 1) {
		cawd->dai_wink[0].dpcm_captuwe = 1;
		cawd->dai_wink[1].dpcm_captuwe = 1;
	}

	pwiv->scwk_i2s = of_cwk_get_by_name(cpu_dai, "i2s_opcwk1");
	if (IS_EWW(pwiv->scwk_i2s)) {
		wet = PTW_EWW(pwiv->scwk_i2s);
		goto eww_put_cpu_dai;
	}

	pwiv->cwk_i2s_bus = of_cwk_get_by_name(cpu_dai, "iis");
	if (IS_EWW(pwiv->cwk_i2s_bus)) {
		wet = PTW_EWW(pwiv->cwk_i2s_bus);
		goto eww_put_scwk;
	}

	wet = devm_snd_soc_wegistew_cawd(dev, cawd);
	if (wet < 0) {
		dev_eww_pwobe(dev, wet, "snd_soc_wegistew_cawd() faiwed\n");
		goto eww_put_cwk_i2s;
	}

	of_node_put(cpu_dai);
	of_node_put(codec);
	wetuwn 0;

eww_put_cwk_i2s:
	cwk_put(pwiv->cwk_i2s_bus);
eww_put_scwk:
	cwk_put(pwiv->scwk_i2s);
eww_put_cpu_dai:
	of_node_put(cpu_dai);
	snd_soc_of_put_dai_wink_codecs(codec_wink);
eww_put_node:
	of_node_put(codec);
	wetuwn wet;
}

static void odwoid_audio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct odwoid_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	snd_soc_of_put_dai_wink_codecs(&pwiv->cawd.dai_wink[1]);
	cwk_put(pwiv->scwk_i2s);
	cwk_put(pwiv->cwk_i2s_bus);
}

static const stwuct of_device_id odwoid_audio_of_match[] = {
	{ .compatibwe	= "hawdkewnew,odwoid-xu3-audio" },
	{ .compatibwe	= "hawdkewnew,odwoid-xu4-audio" },
	{ .compatibwe	= "samsung,odwoid-xu3-audio" },
	{ .compatibwe	= "samsung,odwoid-xu4-audio" },
	{ },
};
MODUWE_DEVICE_TABWE(of, odwoid_audio_of_match);

static stwuct pwatfowm_dwivew odwoid_audio_dwivew = {
	.dwivew = {
		.name		= "odwoid-audio",
		.of_match_tabwe	= odwoid_audio_of_match,
		.pm		= &snd_soc_pm_ops,
	},
	.pwobe	= odwoid_audio_pwobe,
	.wemove_new = odwoid_audio_wemove,
};
moduwe_pwatfowm_dwivew(odwoid_audio_dwivew);

MODUWE_AUTHOW("Sywwestew Nawwocki <s.nawwocki@samsung.com>");
MODUWE_DESCWIPTION("Odwoid XU3/XU4 audio suppowt");
MODUWE_WICENSE("GPW v2");
