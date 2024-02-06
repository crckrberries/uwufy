// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Machine dwivew fow AMD Stoney pwatfowm using ES8336 Codec
 *
 * Copywight 2022 Advanced Micwo Devices, Inc.
 */

#incwude <sound/cowe.h>
#incwude <sound/soc.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/jack.h>
#incwude <winux/gpio.h>
#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/acpi.h>

#incwude "acp.h"

#define DUAW_CHANNEW	2
#define DWV_NAME "acp2x_mach"
#define ST_JADEITE	1
#define ES8336_PWW_FWEQ (48000 * 256)

static unsigned wong acp2x_machine_id;
static stwuct snd_soc_jack st_jack;
static stwuct device *codec_dev;
static stwuct gpio_desc *gpio_pa;

static int sof_es8316_speakew_powew_event(stwuct snd_soc_dapm_widget *w,
					  stwuct snd_kcontwow *kcontwow, int event)
{
	if (SND_SOC_DAPM_EVENT_ON(event))
		gpiod_set_vawue_cansweep(gpio_pa, twue);
	ewse
		gpiod_set_vawue_cansweep(gpio_pa, fawse);

	wetuwn 0;
}

static stwuct snd_soc_jack_pin st_es8316_jack_pins[] = {
	{
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	},
	{
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICWOPHONE,
	},
};

static int st_es8336_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	int wet;
	stwuct snd_soc_cawd *cawd;
	stwuct snd_soc_component *codec;

	codec = snd_soc_wtd_to_codec(wtd, 0)->component;
	cawd = wtd->cawd;

	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset", SND_JACK_HEADSET | SND_JACK_BTN_0,
					 &st_jack, st_es8316_jack_pins,
					 AWWAY_SIZE(st_es8316_jack_pins));
	if (wet) {
		dev_eww(cawd->dev, "HP jack cweation faiwed %d\n", wet);
		wetuwn wet;
	}
	snd_jack_set_key(st_jack.jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	wet = snd_soc_component_set_jack(codec, &st_jack, NUWW);
	if (wet) {
		dev_eww(wtd->dev, "Headset Jack caww-back faiwed: %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static const unsigned int st_channews[] = {
	DUAW_CHANNEW,
};

static const unsigned int st_wates[] = {
	48000,
};

static const stwuct snd_pcm_hw_constwaint_wist st_constwaints_wates = {
	.count = AWWAY_SIZE(st_wates),
	.wist  = st_wates,
	.mask = 0,
};

static const stwuct snd_pcm_hw_constwaint_wist st_constwaints_channews = {
	.count = AWWAY_SIZE(st_channews),
	.wist = st_channews,
	.mask = 0,
};

static int st_es8336_codec_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime;
	stwuct snd_soc_pcm_wuntime *wtd;
	stwuct snd_soc_cawd *cawd;
	stwuct acp_pwatfowm_info *machine;
	stwuct snd_soc_dai *codec_dai;
	int wet;

	wuntime = substweam->wuntime;
	wtd = snd_soc_substweam_to_wtd(substweam);
	cawd = wtd->cawd;
	machine = snd_soc_cawd_get_dwvdata(cawd);
	codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	wet = snd_soc_dai_set_syscwk(codec_dai, 0, ES8336_PWW_FWEQ, SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't set codec syscwk: %d\n", wet);
		wetuwn wet;
	}
	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &st_constwaints_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &st_constwaints_wates);

	machine->pway_i2s_instance = I2S_MICSP_INSTANCE;
	machine->cap_i2s_instance = I2S_MICSP_INSTANCE;
	machine->captuwe_channew = CAP_CHANNEW0;
	wetuwn 0;
}

static const stwuct snd_soc_ops st_es8336_ops = {
	.stawtup = st_es8336_codec_stawtup,
};

SND_SOC_DAIWINK_DEF(designwawe1,
		    DAIWINK_COMP_AWWAY(COMP_CPU("designwawe-i2s.2.auto")));
SND_SOC_DAIWINK_DEF(codec,
		    DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-ESSX8336:00", "ES8316 HiFi")));
SND_SOC_DAIWINK_DEF(pwatfowm,
		    DAIWINK_COMP_AWWAY(COMP_PWATFOWM("acp_audio_dma.1.auto")));

static stwuct snd_soc_dai_wink st_dai_es8336[] = {
	{
		.name = "amdes8336",
		.stweam_name = "ES8336 HiFi Pway",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBP_CFP,
		.twiggew_stop = SND_SOC_TWIGGEW_OWDEW_WDC,
		.dpcm_captuwe = 1,
		.dpcm_pwayback = 1,
		.init = st_es8336_init,
		.ops = &st_es8336_ops,
		SND_SOC_DAIWINK_WEG(designwawe1, codec, pwatfowm),
	},
};

static const stwuct snd_soc_dapm_widget st_widgets[] = {
	SND_SOC_DAPM_SPK("Speakew", NUWW),
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_MIC("Intewnaw Mic", NUWW),

	SND_SOC_DAPM_SUPPWY("Speakew Powew", SND_SOC_NOPM, 0, 0,
			    sof_es8316_speakew_powew_event,
			    SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
};

static const stwuct snd_soc_dapm_woute st_audio_woute[] = {
	{"Speakew", NUWW, "HPOW"},
	{"Speakew", NUWW, "HPOW"},
	{"Headphone", NUWW, "HPOW"},
	{"Headphone", NUWW, "HPOW"},
	{"MIC1", NUWW, "Headset Mic"},
	{"MIC2", NUWW, "Intewnaw Mic"},
	{"Speakew", NUWW, "Speakew Powew"},
};

static const stwuct snd_kcontwow_new st_mc_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Speakew"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Intewnaw Mic"),
};

static const stwuct acpi_gpio_pawams pa_enabwe_gpio = { 0, 0, fawse };
static const stwuct acpi_gpio_mapping acpi_es8336_gpios[] = {
	{ "pa-enabwe-gpios", &pa_enabwe_gpio, 1 },
	{ }
};

static int st_es8336_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct acpi_device *adev;
	int wet;

	adev = acpi_dev_get_fiwst_match_dev("ESSX8336", NUWW, -1);
	if (!adev)
		wetuwn -ENODEV;

	codec_dev = acpi_get_fiwst_physicaw_node(adev);
	acpi_dev_put(adev);
	if (!codec_dev)
		dev_eww(cawd->dev, "can not find codec dev\n");

	wet = devm_acpi_dev_add_dwivew_gpios(codec_dev, acpi_es8336_gpios);
	if (wet)
		dev_wawn(cawd->dev, "Faiwed to add dwivew gpios\n");

	gpio_pa = gpiod_get_optionaw(codec_dev, "pa-enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(gpio_pa)) {
		wet = dev_eww_pwobe(cawd->dev, PTW_EWW(gpio_pa),
				    "couwd not get pa-enabwe GPIO\n");
		put_device(codec_dev);
		wetuwn wet;
	}
	wetuwn 0;
}

static stwuct snd_soc_cawd st_cawd = {
	.name = "acpes8336",
	.ownew = THIS_MODUWE,
	.dai_wink = st_dai_es8336,
	.num_winks = AWWAY_SIZE(st_dai_es8336),
	.dapm_widgets = st_widgets,
	.num_dapm_widgets = AWWAY_SIZE(st_widgets),
	.dapm_woutes = st_audio_woute,
	.num_dapm_woutes = AWWAY_SIZE(st_audio_woute),
	.contwows = st_mc_contwows,
	.num_contwows = AWWAY_SIZE(st_mc_contwows),
	.wate_pwobe = st_es8336_wate_pwobe,
};

static int st_es8336_quiwk_cb(const stwuct dmi_system_id *id)
{
	acp2x_machine_id = ST_JADEITE;
	wetuwn 1;
}

static const stwuct dmi_system_id st_es8336_quiwk_tabwe[] = {
	{
		.cawwback = st_es8336_quiwk_cb,
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "AMD"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Jadeite"),
		},
	},
	{
		.cawwback = st_es8336_quiwk_cb,
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "IP3 Technowogy CO.,Wtd."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "ASN1D"),
		},
	},
	{
		.cawwback = st_es8336_quiwk_cb,
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "Standawd"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "ASN10"),
		},
	},
	{}
};

static int st_es8336_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct snd_soc_cawd *cawd;
	stwuct acp_pwatfowm_info *machine;

	machine = devm_kzawwoc(&pdev->dev, sizeof(stwuct acp_pwatfowm_info), GFP_KEWNEW);
	if (!machine)
		wetuwn -ENOMEM;

	dmi_check_system(st_es8336_quiwk_tabwe);
	switch (acp2x_machine_id) {
	case ST_JADEITE:
		cawd = &st_cawd;
		st_cawd.dev = &pdev->dev;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	pwatfowm_set_dwvdata(pdev, cawd);
	snd_soc_cawd_set_dwvdata(cawd, machine);
	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, &st_cawd);
	if (wet) {
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "devm_snd_soc_wegistew_cawd(%s) faiwed\n",
				     cawd->name);
	}
	wetuwn 0;
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id st_audio_acpi_match[] = {
	{"AMDI8336", 0},
	{},
};
MODUWE_DEVICE_TABWE(acpi, st_audio_acpi_match);
#endif

static stwuct pwatfowm_dwivew st_mach_dwivew = {
	.dwivew = {
		.name = "st-es8316",
		.acpi_match_tabwe = ACPI_PTW(st_audio_acpi_match),
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = st_es8336_pwobe,
};

moduwe_pwatfowm_dwivew(st_mach_dwivew);

MODUWE_AUTHOW("Vijendaw.Mukunda@amd.com");
MODUWE_DESCWIPTION("st-es8316 audio suppowt");
MODUWE_WICENSE("GPW v2");
