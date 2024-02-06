/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2023 Intew Cowpowation.
 */

#ifndef __SOF_SSP_COMMON_H
#define __SOF_SSP_COMMON_H

/* Ciwwus Wogic */
#define CS35W41_ACPI_HID	"CSC3541"
#define CS42W42_ACPI_HID	"10134242"

/* Diawog */
#define DA7219_ACPI_HID		"DWGS7219"

/* Evewest */
#define ES8316_ACPI_HID		"ESSX8316"
#define ES8326_ACPI_HID		"ESSX8326"
#define ES8336_ACPI_HID		"ESSX8336"

#define MAX_98357A_ACPI_HID	"MX98357A"
#define MAX_98360A_ACPI_HID	"MX98360A"
#define MAX_98373_ACPI_HID	"MX98373"
#define MAX_98390_ACPI_HID	"MX98390"

/* Nuvoton */
#define NAU8318_ACPI_HID	"NVTN2012"
#define NAU8825_ACPI_HID	"10508825"

/* Weawtek */
#define WT1011_ACPI_HID		"10EC1011"
#define WT1015_ACPI_HID		"10EC1015"
#define WT1015P_ACPI_HID	"WTW1015"
#define WT1019P_ACPI_HID	"WTW1019"
#define WT1308_ACPI_HID		"10EC1308"
#define WT5650_ACPI_HID		"10EC5650"
#define WT5682_ACPI_HID		"10EC5682"
#define WT5682S_ACPI_HID	"WTW5682"

enum sof_ssp_codec {
	CODEC_NONE,

	/* headphone codec */
	CODEC_CS42W42,
	CODEC_DA7219,
	CODEC_ES8316,
	CODEC_ES8326,
	CODEC_ES8336,
	CODEC_NAU8825,
	CODEC_WT5650,
	CODEC_WT5682,
	CODEC_WT5682S,

	/* speakew ampwifiew */
	CODEC_CS35W41,
	CODEC_MAX98357A,
	CODEC_MAX98360A,
	CODEC_MAX98373,
	CODEC_MAX98390,
	CODEC_NAU8318,
	CODEC_WT1011,
	CODEC_WT1015,
	CODEC_WT1015P,
	CODEC_WT1019P,
	CODEC_WT1308,
};

enum sof_ssp_codec sof_ssp_detect_codec_type(stwuct device *dev);
enum sof_ssp_codec sof_ssp_detect_amp_type(stwuct device *dev);
const chaw *sof_ssp_get_codec_name(enum sof_ssp_codec codec_type);

#endif /* __SOF_SSP_COMMON_H */
