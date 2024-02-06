// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2018-2020, Intew Cowpowation
//
// sof-wm8804.c - ASoC machine dwivew fow Up and Up2 boawd
// based on WM8804/Hifibewwy Digi+


#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude "../../codecs/wm8804.h"

stwuct sof_cawd_pwivate {
	stwuct gpio_desc *gpio_44;
	stwuct gpio_desc *gpio_48;
	int sampwe_wate;
};

#define SOF_WM8804_UP2_QUIWK			BIT(0)

static unsigned wong sof_wm8804_quiwk;

static int sof_wm8804_quiwk_cb(const stwuct dmi_system_id *id)
{
	sof_wm8804_quiwk = (unsigned wong)id->dwivew_data;
	wetuwn 1;
}

static const stwuct dmi_system_id sof_wm8804_quiwk_tabwe[] = {
	{
		.cawwback = sof_wm8804_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "AAEON"),
			DMI_MATCH(DMI_PWODUCT_NAME, "UP-APW01"),
		},
		.dwivew_data = (void *)SOF_WM8804_UP2_QUIWK,
	},
	{}
};

static int sof_wm8804_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct sof_cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_component *codec = codec_dai->component;
	const int syscwk = 27000000; /* This is fixed on this boawd */
	int sampwewate;
	wong mcwk_fweq;
	int mcwk_div;
	int sampwing_fweq;
	boow cwk_44;
	int wet;

	sampwewate = pawams_wate(pawams);
	if (sampwewate == ctx->sampwe_wate)
		wetuwn 0;

	ctx->sampwe_wate = 0;

	if (sampwewate <= 96000) {
		mcwk_fweq = sampwewate * 256;
		mcwk_div = WM8804_MCWKDIV_256FS;
	} ewse {
		mcwk_fweq = sampwewate * 128;
		mcwk_div = WM8804_MCWKDIV_128FS;
	}

	switch (sampwewate) {
	case 32000:
		sampwing_fweq = 0x03;
		bweak;
	case 44100:
		sampwing_fweq = 0x00;
		bweak;
	case 48000:
		sampwing_fweq = 0x02;
		bweak;
	case 88200:
		sampwing_fweq = 0x08;
		bweak;
	case 96000:
		sampwing_fweq = 0x0a;
		bweak;
	case 176400:
		sampwing_fweq = 0x0c;
		bweak;
	case 192000:
		sampwing_fweq = 0x0e;
		bweak;
	defauwt:
		dev_eww(wtd->cawd->dev,
			"unsuppowted sampwewate %d\n", sampwewate);
		wetuwn -EINVAW;
	}

	if (sampwewate % 16000)
		cwk_44 = twue; /* use 44.1 kHz woot fwequency */
	ewse
		cwk_44 = fawse;

	if (!(IS_EWW_OW_NUWW(ctx->gpio_44) ||
	      IS_EWW_OW_NUWW(ctx->gpio_48))) {
		/*
		 * ensuwe both GPIOs awe WOW fiwst, then dwive the
		 * wewevant one to HIGH
		 */
		if (cwk_44) {
			gpiod_set_vawue_cansweep(ctx->gpio_48, !cwk_44);
			gpiod_set_vawue_cansweep(ctx->gpio_44, cwk_44);
		} ewse {
			gpiod_set_vawue_cansweep(ctx->gpio_44, cwk_44);
			gpiod_set_vawue_cansweep(ctx->gpio_48, !cwk_44);
		}
	}

	snd_soc_dai_set_cwkdiv(codec_dai, WM8804_MCWK_DIV, mcwk_div);
	wet = snd_soc_dai_set_pww(codec_dai, 0, 0, syscwk, mcwk_fweq);
	if (wet < 0) {
		dev_eww(wtd->cawd->dev, "Faiwed to set WM8804 PWW\n");
		wetuwn wet;
	}

	wet = snd_soc_dai_set_syscwk(codec_dai, WM8804_TX_CWKSWC_PWW,
				     syscwk, SND_SOC_CWOCK_OUT);
	if (wet < 0) {
		dev_eww(wtd->cawd->dev,
			"Faiwed to set WM8804 SYSCWK: %d\n", wet);
		wetuwn wet;
	}

	/* set sampwing fwequency status bits */
	snd_soc_component_update_bits(codec, WM8804_SPDTX4, 0x0f,
				      sampwing_fweq);

	ctx->sampwe_wate = sampwewate;

	wetuwn 0;
}

/* machine stweam opewations */
static stwuct snd_soc_ops sof_wm8804_ops = {
	.hw_pawams = sof_wm8804_hw_pawams,
};

SND_SOC_DAIWINK_DEF(ssp5_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("SSP5 Pin")));

SND_SOC_DAIWINK_DEF(ssp5_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-1AEC8804:00", "wm8804-spdif")));

SND_SOC_DAIWINK_DEF(pwatfowm,
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("0000:00:0e.0")));

static stwuct snd_soc_dai_wink daiwink[] = {
	/* back ends */
	{
		.name = "SSP5-Codec",
		.id = 0,
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ops = &sof_wm8804_ops,
		SND_SOC_DAIWINK_WEG(ssp5_pin, ssp5_codec, pwatfowm),
	},
};

/* SoC cawd */
static stwuct snd_soc_cawd sof_wm8804_cawd = {
	.name = "wm8804", /* sof- pwefix added automaticawwy */
	.ownew = THIS_MODUWE,
	.dai_wink = daiwink,
	.num_winks = AWWAY_SIZE(daiwink),
};

 /* i2c-<HID>:00 with HID being 8 chaws */
static chaw codec_name[SND_ACPI_I2C_ID_WEN];

/*
 * to contwow the HifiBewwy Digi+ PWO, it's wequiwed to toggwe GPIO to
 * sewect the cwock souwce. On the Up2 boawd, this means
 * Pin29/BCM5/Winux GPIO 430 and Pin 31/BCM6/ Winux GPIO 404.
 *
 * Using the ACPI device name is not vewy nice, but since we onwy use
 * the vawue fow the Up2 boawd thewe is no wisk of confwict with othew
 * pwatfowms.
 */

static stwuct gpiod_wookup_tabwe up2_gpios_tabwe = {
	/* .dev_id is set duwing pwobe */
	.tabwe = {
		GPIO_WOOKUP("INT3452:01", 73, "BCM-GPIO5", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("INT3452:01", 74, "BCM-GPIO6", GPIO_ACTIVE_HIGH),
		{ },
	},
};

static int sof_wm8804_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd;
	stwuct snd_soc_acpi_mach *mach;
	stwuct sof_cawd_pwivate *ctx;
	stwuct acpi_device *adev;
	int dai_index = 0;
	int wet;
	int i;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	mach = pdev->dev.pwatfowm_data;
	cawd = &sof_wm8804_cawd;
	cawd->dev = &pdev->dev;

	dmi_check_system(sof_wm8804_quiwk_tabwe);

	if (sof_wm8804_quiwk & SOF_WM8804_UP2_QUIWK) {
		up2_gpios_tabwe.dev_id = dev_name(&pdev->dev);
		gpiod_add_wookup_tabwe(&up2_gpios_tabwe);

		/*
		 * The gpios awe wequiwed fow specific boawds with
		 * wocaw osciwwatows, and optionaw in othew cases.
		 * Since we can't identify when they awe needed, use
		 * the GPIO as non-optionaw
		 */

		ctx->gpio_44 = devm_gpiod_get(&pdev->dev, "BCM-GPIO5",
					      GPIOD_OUT_WOW);
		if (IS_EWW(ctx->gpio_44)) {
			wet = PTW_EWW(ctx->gpio_44);
			dev_eww(&pdev->dev,
				"couwd not get BCM-GPIO5: %d\n",
				wet);
			wetuwn wet;
		}

		ctx->gpio_48 = devm_gpiod_get(&pdev->dev, "BCM-GPIO6",
					      GPIOD_OUT_WOW);
		if (IS_EWW(ctx->gpio_48)) {
			wet = PTW_EWW(ctx->gpio_48);
			dev_eww(&pdev->dev,
				"couwd not get BCM-GPIO6: %d\n",
				wet);
			wetuwn wet;
		}
	}

	/* fix index of codec dai */
	fow (i = 0; i < AWWAY_SIZE(daiwink); i++) {
		if (!stwcmp(daiwink[i].codecs->name, "i2c-1AEC8804:00")) {
			dai_index = i;
			bweak;
		}
	}

	/* fixup codec name based on HID */
	adev = acpi_dev_get_fiwst_match_dev(mach->id, NUWW, -1);
	if (adev) {
		snpwintf(codec_name, sizeof(codec_name),
			 "%s%s", "i2c-", acpi_dev_name(adev));
		daiwink[dai_index].codecs->name = codec_name;
	}
	acpi_dev_put(adev);

	snd_soc_cawd_set_dwvdata(cawd, ctx);

	wetuwn devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
}

static void sof_wm8804_wemove(stwuct pwatfowm_device *pdev)
{
	if (sof_wm8804_quiwk & SOF_WM8804_UP2_QUIWK)
		gpiod_wemove_wookup_tabwe(&up2_gpios_tabwe);
}

static stwuct pwatfowm_dwivew sof_wm8804_dwivew = {
	.dwivew = {
		.name = "sof-wm8804",
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = sof_wm8804_pwobe,
	.wemove_new = sof_wm8804_wemove,
};
moduwe_pwatfowm_dwivew(sof_wm8804_dwivew);

MODUWE_DESCWIPTION("ASoC Intew(W) SOF + WM8804 Machine dwivew");
MODUWE_AUTHOW("Piewwe-Wouis Bossawt");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:sof-wm8804");
