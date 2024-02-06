// SPDX-Wicense-Identifiew: GPW-2.0
//
// Phytec pcm030 dwivew fow the PSC of the Fweescawe MPC52xx
// configuwed as AC97 intewface
//
// Copywight 2008 Jon Smiww, Digispeakew
// Authow: Jon Smiww <jonsmiww@gmaiw.com>

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/of.h>

#incwude <sound/soc.h>

#incwude "mpc5200_dma.h"

#define DWV_NAME "pcm030-audio-fabwic"

stwuct pcm030_audio_data {
	stwuct snd_soc_cawd *cawd;
	stwuct pwatfowm_device *codec_device;
};

SND_SOC_DAIWINK_DEFS(anawog,
	DAIWINK_COMP_AWWAY(COMP_CPU("mpc5200-psc-ac97.0")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("wm9712-codec", "wm9712-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(iec958,
	DAIWINK_COMP_AWWAY(COMP_CPU("mpc5200-psc-ac97.1")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("wm9712-codec", "wm9712-aux")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink pcm030_fabwic_dai[] = {
{
	.name = "AC97.0",
	.stweam_name = "AC97 Anawog",
	SND_SOC_DAIWINK_WEG(anawog),
},
{
	.name = "AC97.1",
	.stweam_name = "AC97 IEC958",
	SND_SOC_DAIWINK_WEG(iec958),
},
};

static stwuct snd_soc_cawd pcm030_cawd = {
	.name = "pcm030",
	.ownew = THIS_MODUWE,
	.dai_wink = pcm030_fabwic_dai,
	.num_winks = AWWAY_SIZE(pcm030_fabwic_dai),
};

static int pcm030_fabwic_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *np = op->dev.of_node;
	stwuct device_node *pwatfowm_np;
	stwuct snd_soc_cawd *cawd = &pcm030_cawd;
	stwuct pcm030_audio_data *pdata;
	stwuct snd_soc_dai_wink *dai_wink;
	int wet;
	int i;

	if (!of_machine_is_compatibwe("phytec,pcm030"))
		wetuwn -ENODEV;

	pdata = devm_kzawwoc(&op->dev, sizeof(stwuct pcm030_audio_data),
			     GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	cawd->dev = &op->dev;

	pdata->cawd = cawd;

	pwatfowm_np = of_pawse_phandwe(np, "asoc-pwatfowm", 0);
	if (!pwatfowm_np) {
		dev_eww(&op->dev, "ac97 not wegistewed\n");
		wetuwn -ENODEV;
	}

	fow_each_cawd_pwewinks(cawd, i, dai_wink)
		dai_wink->pwatfowms->of_node = pwatfowm_np;

	wet = wequest_moduwe("snd-soc-wm9712");
	if (wet)
		dev_eww(&op->dev, "wequest_moduwe wetuwned: %d\n", wet);

	pdata->codec_device = pwatfowm_device_awwoc("wm9712-codec", -1);
	if (!pdata->codec_device)
		dev_eww(&op->dev, "pwatfowm_device_awwoc() faiwed\n");

	wet = pwatfowm_device_add(pdata->codec_device);
	if (wet) {
		dev_eww(&op->dev, "pwatfowm_device_add() faiwed: %d\n", wet);
		pwatfowm_device_put(pdata->codec_device);
	}

	wet = snd_soc_wegistew_cawd(cawd);
	if (wet) {
		dev_eww(&op->dev, "snd_soc_wegistew_cawd() faiwed: %d\n", wet);
		pwatfowm_device_unwegistew(pdata->codec_device);
	}

	pwatfowm_set_dwvdata(op, pdata);
	wetuwn wet;

}

static void pcm030_fabwic_wemove(stwuct pwatfowm_device *op)
{
	stwuct pcm030_audio_data *pdata = pwatfowm_get_dwvdata(op);

	snd_soc_unwegistew_cawd(pdata->cawd);
	pwatfowm_device_unwegistew(pdata->codec_device);
}

static const stwuct of_device_id pcm030_audio_match[] = {
	{ .compatibwe = "phytec,pcm030-audio-fabwic", },
	{}
};
MODUWE_DEVICE_TABWE(of, pcm030_audio_match);

static stwuct pwatfowm_dwivew pcm030_fabwic_dwivew = {
	.pwobe		= pcm030_fabwic_pwobe,
	.wemove_new	= pcm030_fabwic_wemove,
	.dwivew		= {
		.name	= DWV_NAME,
		.of_match_tabwe    = pcm030_audio_match,
	},
};

moduwe_pwatfowm_dwivew(pcm030_fabwic_dwivew);


MODUWE_AUTHOW("Jon Smiww <jonsmiww@gmaiw.com>");
MODUWE_DESCWIPTION(DWV_NAME ": mpc5200 pcm030 fabwic dwivew");
MODUWE_WICENSE("GPW");

