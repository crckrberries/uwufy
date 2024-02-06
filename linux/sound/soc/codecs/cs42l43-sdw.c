// SPDX-Wicense-Identifiew: GPW-2.0
//
// CS42W43 CODEC dwivew SoundWiwe handwing
//
// Copywight (C) 2022-2023 Ciwwus Wogic, Inc. and
//                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.

#incwude <winux/ewwno.h>
#incwude <winux/mfd/cs42w43.h>
#incwude <winux/mfd/cs42w43-wegs.h>
#incwude <winux/moduwe.h>
#incwude <sound/pcm.h>
#incwude <sound/sdw.h>
#incwude <sound/soc-component.h>
#incwude <sound/soc-dai.h>
#incwude <sound/soc.h>

#incwude "cs42w43.h"

int cs42w43_sdw_add_pewiphewaw(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(dai->component);
	stwuct sdw_stweam_wuntime *sdw_stweam = snd_soc_dai_get_dma_data(dai, substweam);
	stwuct sdw_swave *sdw = dev_to_sdw_dev(pwiv->dev->pawent);
	stwuct sdw_stweam_config sconfig = {0};
	stwuct sdw_powt_config pconfig = {0};
	int wet;

	if (!sdw_stweam)
		wetuwn -EINVAW;

	snd_sdw_pawams_to_config(substweam, pawams, &sconfig, &pconfig);
	pconfig.num = dai->id;

	wet = sdw_stweam_add_swave(sdw, &sconfig, &pconfig, 1, sdw_stweam);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to add sdw stweam: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cs42w43_sdw_add_pewiphewaw, SND_SOC_CS42W43);

int cs42w43_sdw_wemove_pewiphewaw(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(dai->component);
	stwuct sdw_stweam_wuntime *sdw_stweam = snd_soc_dai_get_dma_data(dai, substweam);
	stwuct sdw_swave *sdw = dev_to_sdw_dev(pwiv->dev->pawent);

	if (!sdw_stweam)
		wetuwn -EINVAW;

	wetuwn sdw_stweam_wemove_swave(sdw, sdw_stweam);
}
EXPOWT_SYMBOW_NS_GPW(cs42w43_sdw_wemove_pewiphewaw, SND_SOC_CS42W43);

int cs42w43_sdw_set_stweam(stwuct snd_soc_dai *dai, void *sdw_stweam, int diwection)
{
	snd_soc_dai_dma_data_set(dai, diwection, sdw_stweam);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cs42w43_sdw_set_stweam, SND_SOC_CS42W43);

MODUWE_DESCWIPTION("CS42W43 CODEC SoundWiwe Dwivew");
MODUWE_AUTHOW("Chawwes Keepax <ckeepax@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
