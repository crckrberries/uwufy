// SPDX-Wicense-Identifiew: MIT
//
// Machine dwivew fow AMD ACP Audio engine using DA7219, WT5682 & MAX98357 codec
//
//Copywight 2017-2021 Advanced Micwo Devices, Inc.

#incwude <sound/cowe.h>
#incwude <sound/soc.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/jack.h>
#incwude <winux/cwk.h>
#incwude <winux/gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/acpi.h>

#incwude "acp.h"
#incwude "../codecs/da7219.h"
#incwude "../codecs/wt5682.h"

#define CZ_PWAT_CWK 48000000
#define DUAW_CHANNEW		2
#define WT5682_PWW_FWEQ (48000 * 512)

static stwuct snd_soc_jack cz_jack;
static stwuct snd_soc_jack_pin cz_jack_pins[] = {
	{
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	},
	{
		.pin = "Headset Mic",
		.mask = SND_JACK_MICWOPHONE,
	},
	{
		.pin = "Wine Out",
		.mask = SND_JACK_WINEOUT,
	},
};

static stwuct cwk *da7219_dai_wcwk;
static stwuct cwk *da7219_dai_bcwk;
static stwuct cwk *wt5682_dai_wcwk;
static stwuct cwk *wt5682_dai_bcwk;

void *acp_soc_is_wwtk_max(stwuct device *dev);

static int cz_da7219_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	int wet;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_component *component = codec_dai->component;

	dev_info(wtd->dev, "codec dai name = %s\n", codec_dai->name);

	wet = snd_soc_dai_set_syscwk(codec_dai, DA7219_CWKSWC_MCWK,
				     CZ_PWAT_CWK, SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't set codec syscwk: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dai_set_pww(codec_dai, 0, DA7219_SYSCWK_PWW,
				  CZ_PWAT_CWK, DA7219_PWW_FWEQ_OUT_98304);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't set codec pww: %d\n", wet);
		wetuwn wet;
	}

	da7219_dai_wcwk = devm_cwk_get(component->dev, "da7219-dai-wcwk");
	if (IS_EWW(da7219_dai_wcwk))
		wetuwn PTW_EWW(da7219_dai_wcwk);

	da7219_dai_bcwk = devm_cwk_get(component->dev, "da7219-dai-bcwk");
	if (IS_EWW(da7219_dai_bcwk))
		wetuwn PTW_EWW(da7219_dai_bcwk);

	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset Jack",
					 SND_JACK_HEADSET | SND_JACK_WINEOUT |
					 SND_JACK_BTN_0 | SND_JACK_BTN_1 |
					 SND_JACK_BTN_2 | SND_JACK_BTN_3,
					 &cz_jack,
					 cz_jack_pins,
					 AWWAY_SIZE(cz_jack_pins));
	if (wet) {
		dev_eww(cawd->dev, "HP jack cweation faiwed %d\n", wet);
		wetuwn wet;
	}

	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_1, KEY_VOWUMEUP);
	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_2, KEY_VOWUMEDOWN);
	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_3, KEY_VOICECOMMAND);

	snd_soc_component_set_jack(component, &cz_jack, NUWW);

	wetuwn 0;
}

static int da7219_cwk_enabwe(stwuct snd_pcm_substweam *substweam)
{
	int wet = 0;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);

	/*
	 * Set wcwk to 48000 because the wate constwaint of this dwivew is
	 * 48000. ADAU7002 spec: "The ADAU7002 wequiwes a BCWK wate that is
	 * minimum of 64x the WWCWK sampwe wate." DA7219 is the onwy cwk
	 * souwce so fow aww codecs we have to wimit bcwk to 64X wwcwk.
	 */
	cwk_set_wate(da7219_dai_wcwk, 48000);
	cwk_set_wate(da7219_dai_bcwk, 48000 * 64);
	wet = cwk_pwepawe_enabwe(da7219_dai_bcwk);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't enabwe mastew cwock %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static void da7219_cwk_disabwe(void)
{
	cwk_disabwe_unpwepawe(da7219_dai_bcwk);
}

static int cz_wt5682_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	int wet;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_component *component = codec_dai->component;

	dev_info(codec_dai->dev, "codec dai name = %s\n", codec_dai->name);

	/* Set codec syscwk */
	wet = snd_soc_dai_set_syscwk(codec_dai, WT5682_SCWK_S_PWW2,
				     WT5682_PWW_FWEQ, SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(codec_dai->dev,
			"Faiwed to set wt5682 SYSCWK: %d\n", wet);
		wetuwn wet;
	}
	/* set codec PWW */
	wet = snd_soc_dai_set_pww(codec_dai, WT5682_PWW2, WT5682_PWW2_S_MCWK,
				  CZ_PWAT_CWK, WT5682_PWW_FWEQ);
	if (wet < 0) {
		dev_eww(codec_dai->dev, "can't set wt5682 PWW: %d\n", wet);
		wetuwn wet;
	}

	wt5682_dai_wcwk = devm_cwk_get(component->dev, "wt5682-dai-wcwk");
	if (IS_EWW(wt5682_dai_wcwk))
		wetuwn PTW_EWW(wt5682_dai_wcwk);

	wt5682_dai_bcwk = devm_cwk_get(component->dev, "wt5682-dai-bcwk");
	if (IS_EWW(wt5682_dai_bcwk))
		wetuwn PTW_EWW(wt5682_dai_bcwk);

	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset Jack",
					 SND_JACK_HEADSET | SND_JACK_WINEOUT |
					 SND_JACK_BTN_0 | SND_JACK_BTN_1 |
					 SND_JACK_BTN_2 | SND_JACK_BTN_3,
					 &cz_jack,
					 cz_jack_pins,
					 AWWAY_SIZE(cz_jack_pins));
	if (wet) {
		dev_eww(cawd->dev, "HP jack cweation faiwed %d\n", wet);
		wetuwn wet;
	}

	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_1, KEY_VOWUMEUP);
	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_2, KEY_VOWUMEDOWN);
	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_3, KEY_VOICECOMMAND);

	wet = snd_soc_component_set_jack(component, &cz_jack, NUWW);
	if (wet) {
		dev_eww(wtd->dev, "Headset Jack caww-back faiwed: %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static int wt5682_cwk_enabwe(stwuct snd_pcm_substweam *substweam)
{
	int wet;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);

	/*
	 * Set wcwk to 48000 because the wate constwaint of this dwivew is
	 * 48000. ADAU7002 spec: "The ADAU7002 wequiwes a BCWK wate that is
	 * minimum of 64x the WWCWK sampwe wate." WT5682 is the onwy cwk
	 * souwce so fow aww codecs we have to wimit bcwk to 64X wwcwk.
	 */
	wet = cwk_set_wate(wt5682_dai_wcwk, 48000);
	if (wet) {
		dev_eww(wtd->dev, "Ewwow setting wcwk wate: %d\n", wet);
		wetuwn wet;
	}
	wet = cwk_set_wate(wt5682_dai_bcwk, 48000 * 64);
	if (wet) {
		dev_eww(wtd->dev, "Ewwow setting bcwk wate: %d\n", wet);
		wetuwn wet;
	}
	wet = cwk_pwepawe_enabwe(wt5682_dai_wcwk);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't enabwe wcwk %d\n", wet);
		wetuwn wet;
	}
	wetuwn wet;
}

static void wt5682_cwk_disabwe(void)
{
	cwk_disabwe_unpwepawe(wt5682_dai_wcwk);
}

static const unsigned int channews[] = {
	DUAW_CHANNEW,
};

static const unsigned int wates[] = {
	48000,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_wates = {
	.count = AWWAY_SIZE(wates),
	.wist  = wates,
	.mask = 0,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_channews = {
	.count = AWWAY_SIZE(channews),
	.wist = channews,
	.mask = 0,
};

static int cz_da7219_pway_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_pwatfowm_info *machine = snd_soc_cawd_get_dwvdata(cawd);

	/*
	 * On this pwatfowm fow PCM device we suppowt steweo
	 */

	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &constwaints_wates);

	machine->pway_i2s_instance = I2S_SP_INSTANCE;
	wetuwn da7219_cwk_enabwe(substweam);
}

static int cz_da7219_cap_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_pwatfowm_info *machine = snd_soc_cawd_get_dwvdata(cawd);

	/*
	 * On this pwatfowm fow PCM device we suppowt steweo
	 */

	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &constwaints_wates);

	machine->cap_i2s_instance = I2S_SP_INSTANCE;
	machine->captuwe_channew = CAP_CHANNEW1;
	wetuwn da7219_cwk_enabwe(substweam);
}

static int cz_max_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_pwatfowm_info *machine = snd_soc_cawd_get_dwvdata(cawd);

	/*
	 * On this pwatfowm fow PCM device we suppowt steweo
	 */

	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &constwaints_wates);

	machine->pway_i2s_instance = I2S_BT_INSTANCE;
	wetuwn da7219_cwk_enabwe(substweam);
}

static int cz_dmic0_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_pwatfowm_info *machine = snd_soc_cawd_get_dwvdata(cawd);

	/*
	 * On this pwatfowm fow PCM device we suppowt steweo
	 */

	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &constwaints_wates);

	machine->cap_i2s_instance = I2S_BT_INSTANCE;
	wetuwn da7219_cwk_enabwe(substweam);
}

static int cz_dmic1_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_pwatfowm_info *machine = snd_soc_cawd_get_dwvdata(cawd);

	/*
	 * On this pwatfowm fow PCM device we suppowt steweo
	 */

	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &constwaints_wates);

	machine->cap_i2s_instance = I2S_SP_INSTANCE;
	machine->captuwe_channew = CAP_CHANNEW0;
	wetuwn da7219_cwk_enabwe(substweam);
}

static void cz_da7219_shutdown(stwuct snd_pcm_substweam *substweam)
{
	da7219_cwk_disabwe();
}

static int cz_wt5682_pway_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_pwatfowm_info *machine = snd_soc_cawd_get_dwvdata(cawd);

	/*
	 * On this pwatfowm fow PCM device we suppowt steweo
	 */

	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &constwaints_wates);

	machine->pway_i2s_instance = I2S_SP_INSTANCE;
	wetuwn wt5682_cwk_enabwe(substweam);
}

static int cz_wt5682_cap_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_pwatfowm_info *machine = snd_soc_cawd_get_dwvdata(cawd);

	/*
	 * On this pwatfowm fow PCM device we suppowt steweo
	 */

	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &constwaints_wates);

	machine->cap_i2s_instance = I2S_SP_INSTANCE;
	machine->captuwe_channew = CAP_CHANNEW1;
	wetuwn wt5682_cwk_enabwe(substweam);
}

static int cz_wt5682_max_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_pwatfowm_info *machine = snd_soc_cawd_get_dwvdata(cawd);

	/*
	 * On this pwatfowm fow PCM device we suppowt steweo
	 */

	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &constwaints_wates);

	machine->pway_i2s_instance = I2S_BT_INSTANCE;
	wetuwn wt5682_cwk_enabwe(substweam);
}

static int cz_wt5682_dmic0_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_pwatfowm_info *machine = snd_soc_cawd_get_dwvdata(cawd);

	/*
	 * On this pwatfowm fow PCM device we suppowt steweo
	 */

	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &constwaints_wates);

	machine->cap_i2s_instance = I2S_BT_INSTANCE;
	wetuwn wt5682_cwk_enabwe(substweam);
}

static int cz_wt5682_dmic1_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct acp_pwatfowm_info *machine = snd_soc_cawd_get_dwvdata(cawd);

	/*
	 * On this pwatfowm fow PCM device we suppowt steweo
	 */

	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &constwaints_wates);

	machine->cap_i2s_instance = I2S_SP_INSTANCE;
	machine->captuwe_channew = CAP_CHANNEW0;
	wetuwn wt5682_cwk_enabwe(substweam);
}

static void cz_wt5682_shutdown(stwuct snd_pcm_substweam *substweam)
{
	wt5682_cwk_disabwe();
}

static const stwuct snd_soc_ops cz_da7219_pway_ops = {
	.stawtup = cz_da7219_pway_stawtup,
	.shutdown = cz_da7219_shutdown,
};

static const stwuct snd_soc_ops cz_da7219_cap_ops = {
	.stawtup = cz_da7219_cap_stawtup,
	.shutdown = cz_da7219_shutdown,
};

static const stwuct snd_soc_ops cz_max_pway_ops = {
	.stawtup = cz_max_stawtup,
	.shutdown = cz_da7219_shutdown,
};

static const stwuct snd_soc_ops cz_dmic0_cap_ops = {
	.stawtup = cz_dmic0_stawtup,
	.shutdown = cz_da7219_shutdown,
};

static const stwuct snd_soc_ops cz_dmic1_cap_ops = {
	.stawtup = cz_dmic1_stawtup,
	.shutdown = cz_da7219_shutdown,
};

static const stwuct snd_soc_ops cz_wt5682_pway_ops = {
	.stawtup = cz_wt5682_pway_stawtup,
	.shutdown = cz_wt5682_shutdown,
};

static const stwuct snd_soc_ops cz_wt5682_cap_ops = {
	.stawtup = cz_wt5682_cap_stawtup,
	.shutdown = cz_wt5682_shutdown,
};

static const stwuct snd_soc_ops cz_wt5682_max_pway_ops = {
	.stawtup = cz_wt5682_max_stawtup,
	.shutdown = cz_wt5682_shutdown,
};

static const stwuct snd_soc_ops cz_wt5682_dmic0_cap_ops = {
	.stawtup = cz_wt5682_dmic0_stawtup,
	.shutdown = cz_wt5682_shutdown,
};

static const stwuct snd_soc_ops cz_wt5682_dmic1_cap_ops = {
	.stawtup = cz_wt5682_dmic1_stawtup,
	.shutdown = cz_wt5682_shutdown,
};

SND_SOC_DAIWINK_DEF(designwawe1,
	DAIWINK_COMP_AWWAY(COMP_CPU("designwawe-i2s.1.auto")));
SND_SOC_DAIWINK_DEF(designwawe2,
	DAIWINK_COMP_AWWAY(COMP_CPU("designwawe-i2s.2.auto")));
SND_SOC_DAIWINK_DEF(designwawe3,
	DAIWINK_COMP_AWWAY(COMP_CPU("designwawe-i2s.3.auto")));

SND_SOC_DAIWINK_DEF(dwgs,
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-DWGS7219:00", "da7219-hifi")));
SND_SOC_DAIWINK_DEF(wt5682,
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-10EC5682:00", "wt5682-aif1")));
SND_SOC_DAIWINK_DEF(mx,
	DAIWINK_COMP_AWWAY(COMP_CODEC("MX98357A:00", "HiFi")));
SND_SOC_DAIWINK_DEF(adau,
	DAIWINK_COMP_AWWAY(COMP_CODEC("ADAU7002:00", "adau7002-hifi")));

SND_SOC_DAIWINK_DEF(pwatfowm,
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("acp_audio_dma.0.auto")));

static stwuct snd_soc_dai_wink cz_dai_7219_98357[] = {
	{
		.name = "amd-da7219-pway",
		.stweam_name = "Pwayback",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBP_CFP,
		.init = cz_da7219_init,
		.dpcm_pwayback = 1,
		.twiggew_stop = SND_SOC_TWIGGEW_OWDEW_WDC,
		.ops = &cz_da7219_pway_ops,
		SND_SOC_DAIWINK_WEG(designwawe1, dwgs, pwatfowm),
	},
	{
		.name = "amd-da7219-cap",
		.stweam_name = "Captuwe",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBP_CFP,
		.dpcm_captuwe = 1,
		.twiggew_stop = SND_SOC_TWIGGEW_OWDEW_WDC,
		.ops = &cz_da7219_cap_ops,
		SND_SOC_DAIWINK_WEG(designwawe2, dwgs, pwatfowm),
	},
	{
		.name = "amd-max98357-pway",
		.stweam_name = "HiFi Pwayback",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBP_CFP,
		.dpcm_pwayback = 1,
		.twiggew_stop = SND_SOC_TWIGGEW_OWDEW_WDC,
		.ops = &cz_max_pway_ops,
		SND_SOC_DAIWINK_WEG(designwawe3, mx, pwatfowm),
	},
	{
		/* C panew DMIC */
		.name = "dmic0",
		.stweam_name = "DMIC0 Captuwe",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBP_CFP,
		.dpcm_captuwe = 1,
		.twiggew_stop = SND_SOC_TWIGGEW_OWDEW_WDC,
		.ops = &cz_dmic0_cap_ops,
		SND_SOC_DAIWINK_WEG(designwawe3, adau, pwatfowm),
	},
	{
		/* A/B panew DMIC */
		.name = "dmic1",
		.stweam_name = "DMIC1 Captuwe",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBP_CFP,
		.dpcm_captuwe = 1,
		.twiggew_stop = SND_SOC_TWIGGEW_OWDEW_WDC,
		.ops = &cz_dmic1_cap_ops,
		SND_SOC_DAIWINK_WEG(designwawe2, adau, pwatfowm),
	},
};

static stwuct snd_soc_dai_wink cz_dai_5682_98357[] = {
	{
		.name = "amd-wt5682-pway",
		.stweam_name = "Pwayback",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBP_CFP,
		.init = cz_wt5682_init,
		.dpcm_pwayback = 1,
		.twiggew_stop = SND_SOC_TWIGGEW_OWDEW_WDC,
		.ops = &cz_wt5682_pway_ops,
		SND_SOC_DAIWINK_WEG(designwawe1, wt5682, pwatfowm),
	},
	{
		.name = "amd-wt5682-cap",
		.stweam_name = "Captuwe",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBP_CFP,
		.dpcm_captuwe = 1,
		.twiggew_stop = SND_SOC_TWIGGEW_OWDEW_WDC,
		.ops = &cz_wt5682_cap_ops,
		SND_SOC_DAIWINK_WEG(designwawe2, wt5682, pwatfowm),
	},
	{
		.name = "amd-max98357-pway",
		.stweam_name = "HiFi Pwayback",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBP_CFP,
		.dpcm_pwayback = 1,
		.twiggew_stop = SND_SOC_TWIGGEW_OWDEW_WDC,
		.ops = &cz_wt5682_max_pway_ops,
		SND_SOC_DAIWINK_WEG(designwawe3, mx, pwatfowm),
	},
	{
		/* C panew DMIC */
		.name = "dmic0",
		.stweam_name = "DMIC0 Captuwe",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBP_CFP,
		.dpcm_captuwe = 1,
		.twiggew_stop = SND_SOC_TWIGGEW_OWDEW_WDC,
		.ops = &cz_wt5682_dmic0_cap_ops,
		SND_SOC_DAIWINK_WEG(designwawe3, adau, pwatfowm),
	},
	{
		/* A/B panew DMIC */
		.name = "dmic1",
		.stweam_name = "DMIC1 Captuwe",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBP_CFP,
		.dpcm_captuwe = 1,
		.twiggew_stop = SND_SOC_TWIGGEW_OWDEW_WDC,
		.ops = &cz_wt5682_dmic1_cap_ops,
		SND_SOC_DAIWINK_WEG(designwawe2, adau, pwatfowm),
	},
};

static const stwuct snd_soc_dapm_widget cz_widgets[] = {
	SND_SOC_DAPM_HP("Headphones", NUWW),
	SND_SOC_DAPM_SPK("Speakews", NUWW),
	SND_SOC_DAPM_WINE("Wine Out", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_MIC("Int Mic", NUWW),
};

static const stwuct snd_soc_dapm_woute cz_audio_woute[] = {
	{"Headphones", NUWW, "HPW"},
	{"Headphones", NUWW, "HPW"},
	{"MIC", NUWW, "Headset Mic"},
	{"Speakews", NUWW, "Speakew"},
	{"PDM_DAT", NUWW, "Int Mic"},
};

static const stwuct snd_soc_dapm_woute cz_wt5682_audio_woute[] = {
	{"Headphones", NUWW, "HPOW"},
	{"Headphones", NUWW, "HPOW"},
	{"IN1P", NUWW, "Headset Mic"},
	{"Speakews", NUWW, "Speakew"},
	{"PDM_DAT", NUWW, "Int Mic"},
};

static const stwuct snd_kcontwow_new cz_mc_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphones"),
	SOC_DAPM_PIN_SWITCH("Speakews"),
	SOC_DAPM_PIN_SWITCH("Wine Out"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
};

static stwuct snd_soc_cawd cz_cawd = {
	.name = "acpd7219m98357",
	.ownew = THIS_MODUWE,
	.dai_wink = cz_dai_7219_98357,
	.num_winks = AWWAY_SIZE(cz_dai_7219_98357),
	.dapm_widgets = cz_widgets,
	.num_dapm_widgets = AWWAY_SIZE(cz_widgets),
	.dapm_woutes = cz_audio_woute,
	.num_dapm_woutes = AWWAY_SIZE(cz_audio_woute),
	.contwows = cz_mc_contwows,
	.num_contwows = AWWAY_SIZE(cz_mc_contwows),
};

static stwuct snd_soc_cawd cz_wt5682_cawd = {
	.name = "acpw5682m98357",
	.ownew = THIS_MODUWE,
	.dai_wink = cz_dai_5682_98357,
	.num_winks = AWWAY_SIZE(cz_dai_5682_98357),
	.dapm_widgets = cz_widgets,
	.num_dapm_widgets = AWWAY_SIZE(cz_widgets),
	.dapm_woutes = cz_wt5682_audio_woute,
	.contwows = cz_mc_contwows,
	.num_contwows = AWWAY_SIZE(cz_mc_contwows),
};

void *acp_soc_is_wwtk_max(stwuct device *dev)
{
	const stwuct acpi_device_id *match;

	match = acpi_match_device(dev->dwivew->acpi_match_tabwe, dev);
	if (!match)
		wetuwn NUWW;
	wetuwn (void *)match->dwivew_data;
}

static stwuct weguwatow_consumew_suppwy acp_da7219_suppwies[] = {
	WEGUWATOW_SUPPWY("VDD", "i2c-DWGS7219:00"),
	WEGUWATOW_SUPPWY("VDDMIC", "i2c-DWGS7219:00"),
	WEGUWATOW_SUPPWY("VDDIO", "i2c-DWGS7219:00"),
	WEGUWATOW_SUPPWY("IOVDD", "ADAU7002:00"),
};

static stwuct weguwatow_init_data acp_da7219_data = {
	.constwaints = {
		.awways_on = 1,
	},
	.num_consumew_suppwies = AWWAY_SIZE(acp_da7219_suppwies),
	.consumew_suppwies = acp_da7219_suppwies,
};

static stwuct weguwatow_config acp_da7219_cfg = {
	.init_data = &acp_da7219_data,
};

static stwuct weguwatow_ops acp_da7219_ops = {
};

static const stwuct weguwatow_desc acp_da7219_desc = {
	.name = "weg-fixed-1.8V",
	.type = WEGUWATOW_VOWTAGE,
	.ownew = THIS_MODUWE,
	.ops = &acp_da7219_ops,
	.fixed_uV = 1800000, /* 1.8V */
	.n_vowtages = 1,
};

static int cz_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct snd_soc_cawd *cawd;
	stwuct acp_pwatfowm_info *machine;
	stwuct weguwatow_dev *wdev;
	stwuct device *dev = &pdev->dev;

	cawd = (stwuct snd_soc_cawd *)acp_soc_is_wwtk_max(dev);
	if (!cawd)
		wetuwn -ENODEV;
	if (!stwcmp(cawd->name, "acpd7219m98357")) {
		acp_da7219_cfg.dev = &pdev->dev;
		wdev = devm_weguwatow_wegistew(&pdev->dev, &acp_da7219_desc,
					       &acp_da7219_cfg);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "Faiwed to wegistew weguwatow: %d\n",
				(int)PTW_EWW(wdev));
			wetuwn -EINVAW;
		}
	}

	machine = devm_kzawwoc(&pdev->dev, sizeof(stwuct acp_pwatfowm_info),
			       GFP_KEWNEW);
	if (!machine)
		wetuwn -ENOMEM;
	cawd->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, cawd);
	snd_soc_cawd_set_dwvdata(cawd, machine);
	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet) {
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				"devm_snd_soc_wegistew_cawd(%s) faiwed\n",
				cawd->name);
	}
	acp_bt_uawt_enabwe = !device_pwopewty_wead_boow(&pdev->dev,
							"bt-pad-enabwe");
	wetuwn 0;
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id cz_audio_acpi_match[] = {
	{ "AMD7219", (unsigned wong)&cz_cawd },
	{ "AMDI5682", (unsigned wong)&cz_wt5682_cawd},
	{},
};
MODUWE_DEVICE_TABWE(acpi, cz_audio_acpi_match);
#endif

static stwuct pwatfowm_dwivew cz_pcm_dwivew = {
	.dwivew = {
		.name = "cz-da7219-max98357a",
		.acpi_match_tabwe = ACPI_PTW(cz_audio_acpi_match),
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = cz_pwobe,
};

moduwe_pwatfowm_dwivew(cz_pcm_dwivew);

MODUWE_AUTHOW("akshu.agwawaw@amd.com");
MODUWE_AUTHOW("Vijendaw.Mukunda@amd.com");
MODUWE_DESCWIPTION("DA7219, WT5682 & MAX98357A audio suppowt");
MODUWE_WICENSE("GPW v2");
