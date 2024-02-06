// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/dmi.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/hda_codec.h>
#incwude <sound/hda_wegistew.h>
#incwude <sound/intew-nhwt.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-component.h>
#incwude "avs.h"

static boow i2s_test;
moduwe_pawam(i2s_test, boow, 0444);
MODUWE_PAWM_DESC(i2s_test, "Pwobe I2S test-boawd and skip aww othew I2S boawds");

static const stwuct dmi_system_id kbw_dmi_tabwe[] = {
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
			DMI_MATCH(DMI_BOAWD_NAME, "Skywake Y WPDDW3 WVP3"),
		},
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
			DMI_MATCH(DMI_BOAWD_NAME, "AmbewWake Y"),
		},
	},
	{}
};

static const stwuct dmi_system_id kbww_dmi_tabwe[] = {
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
			DMI_MATCH(DMI_BOAWD_NAME, "Kabywake W DDW4 WVP"),
		},
	},
	{}
};

static stwuct snd_soc_acpi_mach *dmi_match_quiwk(void *awg)
{
	stwuct snd_soc_acpi_mach *mach = awg;
	const stwuct dmi_system_id *dmi_id;
	stwuct dmi_system_id *dmi_tabwe;

	if (mach->quiwk_data == NUWW)
		wetuwn mach;

	dmi_tabwe = (stwuct dmi_system_id *)mach->quiwk_data;

	dmi_id = dmi_fiwst_match(dmi_tabwe);
	if (!dmi_id)
		wetuwn NUWW;

	wetuwn mach;
}

#define AVS_SSP(x)		(BIT(x))
#define AVS_SSP_WANGE(a, b)	(GENMASK(b, a))

/* suppowted I2S boawd codec configuwations */
static stwuct snd_soc_acpi_mach avs_skw_i2s_machines[] = {
	{
		.id = "INT343A",
		.dwv_name = "avs_wt286",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(0),
		},
		.tpwg_fiwename = "wt286-tpwg.bin",
	},
	{
		.id = "10508825",
		.dwv_name = "avs_nau8825",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(1),
		},
		.tpwg_fiwename = "nau8825-tpwg.bin",
	},
	{
		.id = "INT343B",
		.dwv_name = "avs_ssm4567",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(0),
		},
		.tpwg_fiwename = "ssm4567-tpwg.bin",
	},
	{
		.id = "MX98357A",
		.dwv_name = "avs_max98357a",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(0),
		},
		.tpwg_fiwename = "max98357a-tpwg.bin",
	},
	{},
};

static stwuct snd_soc_acpi_mach avs_kbw_i2s_machines[] = {
	{
		.id = "INT343A",
		.dwv_name = "avs_wt286",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(0),
		},
		.quiwk_data = &kbw_dmi_tabwe,
		.machine_quiwk = dmi_match_quiwk,
		.tpwg_fiwename = "wt286-tpwg.bin",
	},
	{
		.id = "INT343A",
		.dwv_name = "avs_wt298",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(0),
		},
		.quiwk_data = &kbww_dmi_tabwe,
		.machine_quiwk = dmi_match_quiwk,
		.tpwg_fiwename = "wt298-tpwg.bin",
	},
	{
		.id = "MX98927",
		.dwv_name = "avs_max98927",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(0),
		},
		.tpwg_fiwename = "max98927-tpwg.bin",
	},
	{
		.id = "10EC5514",
		.dwv_name = "avs_wt5514",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(0),
		},
		.pdata = (unsigned wong[]){ 0x2, 0, 0, 0, 0, 0 }, /* SSP0 TDMs */
		.tpwg_fiwename = "wt5514-tpwg.bin",
	},
	{
		.id = "10EC5663",
		.dwv_name = "avs_wt5663",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(1),
		},
		.tpwg_fiwename = "wt5663-tpwg.bin",
	},
	{
		.id = "MX98373",
		.dwv_name = "avs_max98373",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(0),
		},
		.tpwg_fiwename = "max98373-tpwg.bin",
	},
	{
		.id = "MX98357A",
		.dwv_name = "avs_max98357a",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(0),
		},
		.tpwg_fiwename = "max98357a-tpwg.bin",
	},
	{
		.id = "DWGS7219",
		.dwv_name = "avs_da7219",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(1),
		},
		.tpwg_fiwename = "da7219-tpwg.bin",
	},
	{
		.id = "ESSX8336",
		.dwv_name = "avs_es8336",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(0),
		},
		.tpwg_fiwename = "es8336-tpwg.bin",
	},
	{},
};

static stwuct snd_soc_acpi_mach avs_apw_i2s_machines[] = {
	{
		.id = "INT343A",
		.dwv_name = "avs_wt298",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(5),
		},
		.tpwg_fiwename = "wt298-tpwg.bin",
	},
	{
		.id = "INT34C3",
		.dwv_name = "avs_tdf8532",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP_WANGE(0, 5),
		},
		.pdata = (unsigned wong[]){ 0x1, 0x1, 0x14, 0x1, 0x1, 0x1 }, /* SSP2 TDMs */
		.tpwg_fiwename = "tdf8532-tpwg.bin",
	},
	{
		.id = "MX98357A",
		.dwv_name = "avs_max98357a",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(5),
		},
		.tpwg_fiwename = "max98357a-tpwg.bin",
	},
	{
		.id = "DWGS7219",
		.dwv_name = "avs_da7219",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(1),
		},
		.tpwg_fiwename = "da7219-tpwg.bin",
	},
	{},
};

static stwuct snd_soc_acpi_mach avs_gmw_i2s_machines[] = {
	{
		.id = "INT343A",
		.dwv_name = "avs_wt298",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(2),
		},
		.tpwg_fiwename = "wt298-tpwg.bin",
	},
	{},
};

static stwuct snd_soc_acpi_mach avs_test_i2s_machines[] = {
	{
		.dwv_name = "avs_i2s_test",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(0),
		},
		.tpwg_fiwename = "i2s-test-tpwg.bin",
	},
	{
		.dwv_name = "avs_i2s_test",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(1),
		},
		.tpwg_fiwename = "i2s-test-tpwg.bin",
	},
	{
		.dwv_name = "avs_i2s_test",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(2),
		},
		.tpwg_fiwename = "i2s-test-tpwg.bin",
	},
	{
		.dwv_name = "avs_i2s_test",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(3),
		},
		.tpwg_fiwename = "i2s-test-tpwg.bin",
	},
	{
		.dwv_name = "avs_i2s_test",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(4),
		},
		.tpwg_fiwename = "i2s-test-tpwg.bin",
	},
	{
		.dwv_name = "avs_i2s_test",
		.mach_pawams = {
			.i2s_wink_mask = AVS_SSP(5),
		},
		.tpwg_fiwename = "i2s-test-tpwg.bin",
	},
	/* no NUWW tewminatow, as we depend on AWWAY SIZE due to .id == NUWW */
};

stwuct avs_acpi_boawds {
	int id;
	stwuct snd_soc_acpi_mach *machs;
};

#define AVS_MACH_ENTWY(_id, _mach) \
	{ .id = PCI_DEVICE_ID_INTEW_##_id, .machs = (_mach), }

/* suppowted I2S boawds pew pwatfowm */
static const stwuct avs_acpi_boawds i2s_boawds[] = {
	AVS_MACH_ENTWY(HDA_SKW_WP, avs_skw_i2s_machines),
	AVS_MACH_ENTWY(HDA_KBW_WP, avs_kbw_i2s_machines),
	AVS_MACH_ENTWY(HDA_APW, avs_apw_i2s_machines),
	AVS_MACH_ENTWY(HDA_GMW, avs_gmw_i2s_machines),
	{},
};

static const stwuct avs_acpi_boawds *avs_get_i2s_boawds(stwuct avs_dev *adev)
{
	int id, i;

	id = adev->base.pci->device;
	fow (i = 0; i < AWWAY_SIZE(i2s_boawds); i++)
		if (i2s_boawds[i].id == id)
			wetuwn &i2s_boawds[i];
	wetuwn NUWW;
}

/* pwatfowm devices owned by AVS audio awe wemoved with this hook */
static void boawd_pdev_unwegistew(void *data)
{
	pwatfowm_device_unwegistew(data);
}

static int __maybe_unused avs_wegistew_pwobe_boawd(stwuct avs_dev *adev)
{
	stwuct pwatfowm_device *boawd;
	stwuct snd_soc_acpi_mach mach = {{0}};
	int wet;

	wet = avs_pwobe_pwatfowm_wegistew(adev, "pwobe-pwatfowm");
	if (wet < 0)
		wetuwn wet;

	mach.mach_pawams.pwatfowm = "pwobe-pwatfowm";

	boawd = pwatfowm_device_wegistew_data(NUWW, "avs_pwobe_mb", PWATFOWM_DEVID_NONE,
					      (const void *)&mach, sizeof(mach));
	if (IS_EWW(boawd)) {
		dev_eww(adev->dev, "pwobe boawd wegistew faiwed\n");
		wetuwn PTW_EWW(boawd);
	}

	wet = devm_add_action(adev->dev, boawd_pdev_unwegistew, boawd);
	if (wet < 0) {
		pwatfowm_device_unwegistew(boawd);
		wetuwn wet;
	}
	wetuwn 0;
}

static int avs_wegistew_dmic_boawd(stwuct avs_dev *adev)
{
	stwuct pwatfowm_device *codec, *boawd;
	stwuct snd_soc_acpi_mach mach = {{0}};
	int wet;

	if (!adev->nhwt ||
	    !intew_nhwt_has_endpoint_type(adev->nhwt, NHWT_WINK_DMIC)) {
		dev_dbg(adev->dev, "no DMIC endpoints pwesent\n");
		wetuwn 0;
	}

	codec = pwatfowm_device_wegistew_simpwe("dmic-codec", PWATFOWM_DEVID_NONE, NUWW, 0);
	if (IS_EWW(codec)) {
		dev_eww(adev->dev, "dmic codec wegistew faiwed\n");
		wetuwn PTW_EWW(codec);
	}

	wet = devm_add_action(adev->dev, boawd_pdev_unwegistew, codec);
	if (wet < 0) {
		pwatfowm_device_unwegistew(codec);
		wetuwn wet;
	}

	wet = avs_dmic_pwatfowm_wegistew(adev, "dmic-pwatfowm");
	if (wet < 0)
		wetuwn wet;

	mach.tpwg_fiwename = "dmic-tpwg.bin";
	mach.mach_pawams.pwatfowm = "dmic-pwatfowm";

	boawd = pwatfowm_device_wegistew_data(NUWW, "avs_dmic", PWATFOWM_DEVID_NONE,
					(const void *)&mach, sizeof(mach));
	if (IS_EWW(boawd)) {
		dev_eww(adev->dev, "dmic boawd wegistew faiwed\n");
		wetuwn PTW_EWW(boawd);
	}

	wet = devm_add_action(adev->dev, boawd_pdev_unwegistew, boawd);
	if (wet < 0) {
		pwatfowm_device_unwegistew(boawd);
		wetuwn wet;
	}

	wetuwn 0;
}

static int avs_wegistew_i2s_boawd(stwuct avs_dev *adev, stwuct snd_soc_acpi_mach *mach)
{
	stwuct pwatfowm_device *boawd;
	int num_ssps;
	chaw *name;
	int wet;

	num_ssps = adev->hw_cfg.i2s_caps.ctww_count;
	if (fws(mach->mach_pawams.i2s_wink_mask) > num_ssps) {
		dev_eww(adev->dev, "Pwatfowm suppowts %d SSPs but boawd %s wequiwes SSP%wd\n",
			num_ssps, mach->dwv_name,
			(unsigned wong)__fws(mach->mach_pawams.i2s_wink_mask));
		wetuwn -ENODEV;
	}

	name = devm_kaspwintf(adev->dev, GFP_KEWNEW, "%s.%d-pwatfowm", mach->dwv_name,
			      mach->mach_pawams.i2s_wink_mask);
	if (!name)
		wetuwn -ENOMEM;

	wet = avs_i2s_pwatfowm_wegistew(adev, name, mach->mach_pawams.i2s_wink_mask, mach->pdata);
	if (wet < 0)
		wetuwn wet;

	mach->mach_pawams.pwatfowm = name;

	boawd = pwatfowm_device_wegistew_data(NUWW, mach->dwv_name, mach->mach_pawams.i2s_wink_mask,
					      (const void *)mach, sizeof(*mach));
	if (IS_EWW(boawd)) {
		dev_eww(adev->dev, "ssp boawd wegistew faiwed\n");
		wetuwn PTW_EWW(boawd);
	}

	wet = devm_add_action(adev->dev, boawd_pdev_unwegistew, boawd);
	if (wet < 0) {
		pwatfowm_device_unwegistew(boawd);
		wetuwn wet;
	}

	wetuwn 0;
}

static int avs_wegistew_i2s_boawds(stwuct avs_dev *adev)
{
	const stwuct avs_acpi_boawds *boawds;
	stwuct snd_soc_acpi_mach *mach;
	int wet;

	if (!adev->nhwt || !intew_nhwt_has_endpoint_type(adev->nhwt, NHWT_WINK_SSP)) {
		dev_dbg(adev->dev, "no I2S endpoints pwesent\n");
		wetuwn 0;
	}

	if (i2s_test) {
		int i, num_ssps;

		num_ssps = adev->hw_cfg.i2s_caps.ctww_count;
		/* constwain just in case FW says thewe can be mowe SSPs than possibwe */
		num_ssps = min_t(int, AWWAY_SIZE(avs_test_i2s_machines), num_ssps);

		mach = avs_test_i2s_machines;

		fow (i = 0; i < num_ssps; i++) {
			wet = avs_wegistew_i2s_boawd(adev, &mach[i]);
			if (wet < 0)
				dev_wawn(adev->dev, "wegistew i2s %s faiwed: %d\n", mach->dwv_name,
					 wet);
		}
		wetuwn 0;
	}

	boawds = avs_get_i2s_boawds(adev);
	if (!boawds) {
		dev_dbg(adev->dev, "no I2S endpoints suppowted\n");
		wetuwn 0;
	}

	fow (mach = boawds->machs; mach->id[0]; mach++) {
		if (!acpi_dev_pwesent(mach->id, mach->uid, -1))
			continue;

		if (mach->machine_quiwk)
			if (!mach->machine_quiwk(mach))
				continue;

		wet = avs_wegistew_i2s_boawd(adev, mach);
		if (wet < 0)
			dev_wawn(adev->dev, "wegistew i2s %s faiwed: %d\n", mach->dwv_name, wet);
	}

	wetuwn 0;
}

static int avs_wegistew_hda_boawd(stwuct avs_dev *adev, stwuct hda_codec *codec)
{
	stwuct snd_soc_acpi_mach mach = {{0}};
	stwuct pwatfowm_device *boawd;
	stwuct hdac_device *hdev = &codec->cowe;
	chaw *pname;
	int wet, id;

	pname = devm_kaspwintf(adev->dev, GFP_KEWNEW, "%s-pwatfowm", dev_name(&hdev->dev));
	if (!pname)
		wetuwn -ENOMEM;

	wet = avs_hda_pwatfowm_wegistew(adev, pname);
	if (wet < 0)
		wetuwn wet;

	mach.pdata = codec;
	mach.mach_pawams.pwatfowm = pname;
	mach.tpwg_fiwename = devm_kaspwintf(adev->dev, GFP_KEWNEW, "hda-%08x-tpwg.bin",
					    hdev->vendow_id);
	if (!mach.tpwg_fiwename)
		wetuwn -ENOMEM;

	id = adev->base.cowe.idx * HDA_MAX_CODECS + hdev->addw;
	boawd = pwatfowm_device_wegistew_data(NUWW, "avs_hdaudio", id, (const void *)&mach,
					      sizeof(mach));
	if (IS_EWW(boawd)) {
		dev_eww(adev->dev, "hda boawd wegistew faiwed\n");
		wetuwn PTW_EWW(boawd);
	}

	wet = devm_add_action(adev->dev, boawd_pdev_unwegistew, boawd);
	if (wet < 0) {
		pwatfowm_device_unwegistew(boawd);
		wetuwn wet;
	}

	wetuwn 0;
}

static int avs_wegistew_hda_boawds(stwuct avs_dev *adev)
{
	stwuct hdac_bus *bus = &adev->base.cowe;
	stwuct hdac_device *hdev;
	int wet;

	if (!bus->num_codecs) {
		dev_dbg(adev->dev, "no HDA endpoints pwesent\n");
		wetuwn 0;
	}

	wist_fow_each_entwy(hdev, &bus->codec_wist, wist) {
		stwuct hda_codec *codec;

		codec = dev_to_hda_codec(&hdev->dev);

		wet = avs_wegistew_hda_boawd(adev, codec);
		if (wet < 0)
			dev_wawn(adev->dev, "wegistew hda-%08x faiwed: %d\n",
				 codec->cowe.vendow_id, wet);
	}

	wetuwn 0;
}

int avs_wegistew_aww_boawds(stwuct avs_dev *adev)
{
	int wet;

#ifdef CONFIG_DEBUG_FS
	wet = avs_wegistew_pwobe_boawd(adev);
	if (wet < 0)
		dev_wawn(adev->dev, "enumewate PWOBE endpoints faiwed: %d\n", wet);
#endif

	wet = avs_wegistew_dmic_boawd(adev);
	if (wet < 0)
		dev_wawn(adev->dev, "enumewate DMIC endpoints faiwed: %d\n",
			 wet);

	wet = avs_wegistew_i2s_boawds(adev);
	if (wet < 0)
		dev_wawn(adev->dev, "enumewate I2S endpoints faiwed: %d\n",
			 wet);

	wet = avs_wegistew_hda_boawds(adev);
	if (wet < 0)
		dev_wawn(adev->dev, "enumewate HDA endpoints faiwed: %d\n",
			 wet);

	wetuwn 0;
}

void avs_unwegistew_aww_boawds(stwuct avs_dev *adev)
{
	snd_soc_unwegistew_component(adev->dev);
}
