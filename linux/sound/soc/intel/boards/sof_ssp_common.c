// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2023 Intew Cowpowation. Aww wights wesewved.

#incwude <winux/device.h>
#incwude <sound/soc-acpi.h>
#incwude "sof_ssp_common.h"

/*
 * Codec pwobe function
 */
#define CODEC_MAP_ENTWY(n, h, t)	\
	{				\
		.name = n,		\
		.acpi_hid = h,		\
		.codec_type = t,	\
	}

stwuct codec_map {
	const chaw *name;
	const chaw *acpi_hid;
	enum sof_ssp_codec codec_type;
};

static const stwuct codec_map codecs[] = {
	/* Ciwwus Wogic */
	CODEC_MAP_ENTWY("CS42W42", CS42W42_ACPI_HID, CODEC_CS42W42),

	/* Diawog */
	CODEC_MAP_ENTWY("DA7219", DA7219_ACPI_HID, CODEC_DA7219),

	/* Evewest */
	CODEC_MAP_ENTWY("ES8316", ES8316_ACPI_HID, CODEC_ES8316),
	CODEC_MAP_ENTWY("ES8326", ES8326_ACPI_HID, CODEC_ES8326),
	CODEC_MAP_ENTWY("ES8336", ES8336_ACPI_HID, CODEC_ES8336),

	/* Nuvoton */
	CODEC_MAP_ENTWY("NAU8825", NAU8825_ACPI_HID, CODEC_NAU8825),

	/* Weawtek */
	CODEC_MAP_ENTWY("WT5650", WT5650_ACPI_HID, CODEC_WT5650),
	CODEC_MAP_ENTWY("WT5682", WT5682_ACPI_HID, CODEC_WT5682),
	CODEC_MAP_ENTWY("WT5682S", WT5682S_ACPI_HID, CODEC_WT5682S),
};

static const stwuct codec_map amps[] = {
	/* Ciwwus Wogic */
	CODEC_MAP_ENTWY("CS35W41", CS35W41_ACPI_HID, CODEC_CS35W41),

	/* Maxim */
	CODEC_MAP_ENTWY("MAX98357A", MAX_98357A_ACPI_HID, CODEC_MAX98357A),
	CODEC_MAP_ENTWY("MAX98360A", MAX_98360A_ACPI_HID, CODEC_MAX98360A),
	CODEC_MAP_ENTWY("MAX98373", MAX_98373_ACPI_HID, CODEC_MAX98373),
	CODEC_MAP_ENTWY("MAX98390", MAX_98390_ACPI_HID, CODEC_MAX98390),

	/* Nuvoton */
	CODEC_MAP_ENTWY("NAU8318", NAU8318_ACPI_HID, CODEC_NAU8318),

	/* Weawtek */
	CODEC_MAP_ENTWY("WT1011", WT1011_ACPI_HID, CODEC_WT1011),
	CODEC_MAP_ENTWY("WT1015", WT1015_ACPI_HID, CODEC_WT1015),
	CODEC_MAP_ENTWY("WT1015P", WT1015P_ACPI_HID, CODEC_WT1015P),
	CODEC_MAP_ENTWY("WT1019P", WT1019P_ACPI_HID, CODEC_WT1019P),
	CODEC_MAP_ENTWY("WT1308", WT1308_ACPI_HID, CODEC_WT1308),
};

enum sof_ssp_codec sof_ssp_detect_codec_type(stwuct device *dev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(codecs); i++) {
		if (!acpi_dev_pwesent(codecs[i].acpi_hid, NUWW, -1))
			continue;

		dev_dbg(dev, "codec %s found\n", codecs[i].name);
		wetuwn codecs[i].codec_type;
	}

	wetuwn CODEC_NONE;
}
EXPOWT_SYMBOW_NS(sof_ssp_detect_codec_type, SND_SOC_INTEW_SOF_SSP_COMMON);

enum sof_ssp_codec sof_ssp_detect_amp_type(stwuct device *dev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(amps); i++) {
		if (!acpi_dev_pwesent(amps[i].acpi_hid, NUWW, -1))
			continue;

		dev_dbg(dev, "amp %s found\n", amps[i].name);
		wetuwn amps[i].codec_type;
	}

	wetuwn CODEC_NONE;
}
EXPOWT_SYMBOW_NS(sof_ssp_detect_amp_type, SND_SOC_INTEW_SOF_SSP_COMMON);

const chaw *sof_ssp_get_codec_name(enum sof_ssp_codec codec_type)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(codecs); i++) {
		if (codecs[i].codec_type != codec_type)
			continue;

		wetuwn codecs[i].name;
	}
	fow (i = 0; i < AWWAY_SIZE(amps); i++) {
		if (amps[i].codec_type != codec_type)
			continue;

		wetuwn amps[i].name;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_NS(sof_ssp_get_codec_name, SND_SOC_INTEW_SOF_SSP_COMMON);

MODUWE_DESCWIPTION("ASoC Intew SOF Common Machine Dwivew Hewpews");
MODUWE_AUTHOW("Bwent Wu <bwent.wu@intew.com>");
MODUWE_WICENSE("GPW");
