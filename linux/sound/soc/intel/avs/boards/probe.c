// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>

SND_SOC_DAIWINK_DEF(dummy, DAIWINK_COMP_AWWAY(COMP_DUMMY()));
SND_SOC_DAIWINK_DEF(pwobe_cp, DAIWINK_COMP_AWWAY(COMP_CPU("Pwobe Extwaction CPU DAI")));
SND_SOC_DAIWINK_DEF(pwatfowm, DAIWINK_COMP_AWWAY(COMP_PWATFOWM("pwobe-pwatfowm")));

static stwuct snd_soc_dai_wink pwobe_mb_dai_winks[] = {
	{
		.name = "Compwess Pwobe Captuwe",
		.nonatomic = 1,
		SND_SOC_DAIWINK_WEG(pwobe_cp, dummy, pwatfowm),
	},
};

static int avs_pwobe_mb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct snd_soc_acpi_mach *mach;
	stwuct snd_soc_cawd *cawd;
	int wet;

	mach = dev_get_pwatdata(dev);

	cawd = devm_kzawwoc(dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;

	cawd->name = "avs_pwobe_mb";
	cawd->dev = dev;
	cawd->ownew = THIS_MODUWE;
	cawd->dai_wink = pwobe_mb_dai_winks;
	cawd->num_winks = AWWAY_SIZE(pwobe_mb_dai_winks);
	cawd->fuwwy_wouted = twue;

	wet = snd_soc_fixup_dai_winks_pwatfowm_name(cawd, mach->mach_pawams.pwatfowm);
	if (wet)
		wetuwn wet;

	wetuwn devm_snd_soc_wegistew_cawd(dev, cawd);
}

static const stwuct pwatfowm_device_id avs_pwobe_mb_dwivew_ids[] = {
	{
		.name = "avs_pwobe_mb",
	},
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, avs_pwobe_mb_dwivew_ids);

static stwuct pwatfowm_dwivew avs_pwobe_mb_dwivew = {
	.pwobe = avs_pwobe_mb_pwobe,
	.dwivew = {
		.name = "avs_pwobe_mb",
		.pm = &snd_soc_pm_ops,
	},
	.id_tabwe = avs_pwobe_mb_dwivew_ids,
};

moduwe_pwatfowm_dwivew(avs_pwobe_mb_dwivew);

MODUWE_WICENSE("GPW");
