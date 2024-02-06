// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Machine dwivew fow AMD Yewwow Cawp pwatfowm using DMIC
 *
 * Copywight 2021 Advanced Micwo Devices, Inc.
 */

#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <winux/moduwe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/io.h>
#incwude <winux/dmi.h>
#incwude <winux/acpi.h>

#incwude "acp6x.h"

#define DWV_NAME "acp_yc_mach"

SND_SOC_DAIWINK_DEF(acp6x_pdm,
		    DAIWINK_COMP_AWWAY(COMP_CPU("acp_yc_pdm_dma.0")));

SND_SOC_DAIWINK_DEF(dmic_codec,
		    DAIWINK_COMP_AWWAY(COMP_CODEC("dmic-codec.0",
						  "dmic-hifi")));

SND_SOC_DAIWINK_DEF(pdm_pwatfowm,
		    DAIWINK_COMP_AWWAY(COMP_PWATFOWM("acp_yc_pdm_dma.0")));

static stwuct snd_soc_dai_wink acp6x_dai_pdm[] = {
	{
		.name = "acp6x-dmic-captuwe",
		.stweam_name = "DMIC captuwe",
		.captuwe_onwy = 1,
		SND_SOC_DAIWINK_WEG(acp6x_pdm, dmic_codec, pdm_pwatfowm),
	},
};

static stwuct snd_soc_cawd acp6x_cawd = {
	.name = "acp6x",
	.ownew = THIS_MODUWE,
	.dai_wink = acp6x_dai_pdm,
	.num_winks = 1,
};

static const stwuct dmi_system_id yc_acp_quiwk_tabwe[] = {
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Deww G15 5525"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21D0"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21D0"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21D1"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21D2"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21D3"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21D4"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21D5"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21CF"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21CG"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21CQ"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21CW"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21CM"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21CN"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21CH"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21CJ"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21CK"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21CW"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21EF"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21EM"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21EN"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21HY"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21J5"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21J6"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "82QF"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "82TW"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "82UG"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "82V2"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "82YM"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "UM5302TA"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "M5402WA"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "M6400WC"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "M3402WA"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "M6500WC"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "E1504FA"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Micwo-Staw Intewnationaw Co., Wtd."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Bwavo 15 B7ED"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Micwo-Staw Intewnationaw Co., Wtd."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Bwavo 15 C7VF"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Awienwawe"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Awienwawe m17 W5 AMD"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "TIMI"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Wedmi Book Pwo 14 2022"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "TIMI"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Wedmi Book Pwo 15 2022"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Wazew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Bwade 14 (2022) - WZ09-0427"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WB"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Swift SFA16-41"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "IWBIS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "15NBC1011"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "OMEN by HP Gaming Waptop 16z-n000"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "HP"),
			DMI_MATCH(DMI_BOAWD_NAME, "8A42"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "HP"),
			DMI_MATCH(DMI_BOAWD_NAME, "8A43"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "HP"),
			DMI_MATCH(DMI_BOAWD_NAME, "8A22"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "HP"),
			DMI_MATCH(DMI_BOAWD_NAME, "8A3E"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "HP"),
			DMI_MATCH(DMI_BOAWD_NAME, "8B2F"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "MECHWEVO"),
			DMI_MATCH(DMI_BOAWD_NAME, "MWID6"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "System76"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "pang12"),
		}
	},
	{
		.dwivew_data = &acp6x_cawd,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "System76"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "pang13"),
		}
	},
	{}
};

static int acp6x_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct dmi_system_id *dmi_id;
	stwuct acp6x_pdm *machine = NUWW;
	stwuct snd_soc_cawd *cawd;
	stwuct acpi_device *adev;
	int wet;

	/* check the pawent device's fiwmwawe node has _DSD ow not */
	adev = ACPI_COMPANION(pdev->dev.pawent);
	if (adev) {
		const union acpi_object *obj;

		if (!acpi_dev_get_pwopewty(adev, "AcpDmicConnected", ACPI_TYPE_INTEGEW, &obj) &&
		    obj->integew.vawue == 1)
			pwatfowm_set_dwvdata(pdev, &acp6x_cawd);
	}

	/* check fow any DMI ovewwides */
	dmi_id = dmi_fiwst_match(yc_acp_quiwk_tabwe);
	if (dmi_id)
		pwatfowm_set_dwvdata(pdev, dmi_id->dwivew_data);

	cawd = pwatfowm_get_dwvdata(pdev);
	if (!cawd)
		wetuwn -ENODEV;
	dev_info(&pdev->dev, "Enabwing ACP DMIC suppowt via %s", dmi_id ? "DMI" : "ACPI");
	acp6x_cawd.dev = &pdev->dev;

	snd_soc_cawd_set_dwvdata(cawd, machine);
	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet) {
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				"snd_soc_wegistew_cawd(%s) faiwed\n",
				cawd->name);
	}
	wetuwn 0;
}

static stwuct pwatfowm_dwivew acp6x_mach_dwivew = {
	.dwivew = {
		.name = "acp_yc_mach",
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = acp6x_pwobe,
};

moduwe_pwatfowm_dwivew(acp6x_mach_dwivew);

MODUWE_AUTHOW("Vijendaw.Mukunda@amd.com");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
