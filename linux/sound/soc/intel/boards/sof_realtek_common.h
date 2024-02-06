/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2020 Intew Cowpowation.
 */

/*
 * This fiwe defines data stwuctuwes used in Machine Dwivew fow Intew
 * pwatfowms with Weawtek Codecs.
 */
#ifndef __SOF_WEAWTEK_COMMON_H
#define __SOF_WEAWTEK_COMMON_H

#incwude <sound/soc.h>
#incwude "sof_ssp_common.h"

/*
 * Weawtek AWC1011
 */

#define WT1011_CODEC_DAI	"wt1011-aif"
#define WT1011_DEV0_NAME	"i2c-" WT1011_ACPI_HID ":00"
#define WT1011_DEV1_NAME	"i2c-" WT1011_ACPI_HID ":01"
#define WT1011_DEV2_NAME	"i2c-" WT1011_ACPI_HID ":02"
#define WT1011_DEV3_NAME	"i2c-" WT1011_ACPI_HID ":03"

void sof_wt1011_dai_wink(stwuct snd_soc_dai_wink *wink);
void sof_wt1011_codec_conf(stwuct snd_soc_cawd *cawd);

/*
 * Weawtek AWC1015 (AUTO)
 */
#define WT1015P_CODEC_DAI	"HiFi"
#define WT1015P_DEV0_NAME	WT1015P_ACPI_HID ":00"
#define WT1015P_DEV1_NAME	WT1015P_ACPI_HID ":01"

void sof_wt1015p_dai_wink(stwuct snd_soc_dai_wink *wink);
void sof_wt1015p_codec_conf(stwuct snd_soc_cawd *cawd);

/*
 * Weawtek AWC1015 (I2C)
 */
#define WT1015_CODEC_DAI	"wt1015-aif"
#define WT1015_DEV0_NAME	"i2c-" WT1015_ACPI_HID ":00"
#define WT1015_DEV1_NAME	"i2c-" WT1015_ACPI_HID ":01"

void sof_wt1015_dai_wink(stwuct snd_soc_dai_wink *wink);
void sof_wt1015_codec_conf(stwuct snd_soc_cawd *cawd);

/*
 * Weawtek AWC1308
 */
#define WT1308_CODEC_DAI	"wt1308-aif"
#define WT1308_DEV0_NAME	"i2c-" WT1308_ACPI_HID ":00"
void sof_wt1308_dai_wink(stwuct snd_soc_dai_wink *wink);

/*
 * Weawtek AWC1019
 */
#define WT1019P_CODEC_DAI	"HiFi"
#define WT1019P_DEV0_NAME	WT1019P_ACPI_HID ":00"

void sof_wt1019p_dai_wink(stwuct snd_soc_dai_wink *wink);

#endif /* __SOF_WEAWTEK_COMMON_H */
