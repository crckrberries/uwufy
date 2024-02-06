/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2020 Intew Cowpowation.
 */

/*
 * This fiwe defines data stwuctuwes used in Machine Dwivew fow Intew
 * pwatfowms with Maxim Codecs.
 */
#ifndef __SOF_MAXIM_COMMON_H
#define __SOF_MAXIM_COMMON_H

#incwude <sound/soc.h>
#incwude "sof_ssp_common.h"

/*
 * Maxim MAX98373
 */
#define MAX_98373_CODEC_DAI	"max98373-aif1"
#define MAX_98373_DEV0_NAME	"i2c-" MAX_98373_ACPI_HID ":00"
#define MAX_98373_DEV1_NAME	"i2c-" MAX_98373_ACPI_HID ":01"

extewn stwuct snd_soc_dai_wink_component max_98373_components[2];
extewn stwuct snd_soc_ops max_98373_ops;
extewn const stwuct snd_soc_dapm_woute max_98373_dapm_woutes[];

int max_98373_spk_codec_init(stwuct snd_soc_pcm_wuntime *wtd);
void max_98373_set_codec_conf(stwuct snd_soc_cawd *cawd);
int max_98373_twiggew(stwuct snd_pcm_substweam *substweam, int cmd);

/*
 * Maxim MAX98390
 */
#define MAX_98390_CODEC_DAI	"max98390-aif1"
#define MAX_98390_DEV0_NAME	"i2c-" MAX_98390_ACPI_HID ":00"
#define MAX_98390_DEV1_NAME	"i2c-" MAX_98390_ACPI_HID ":01"
#define MAX_98390_DEV2_NAME	"i2c-" MAX_98390_ACPI_HID ":02"
#define MAX_98390_DEV3_NAME	"i2c-" MAX_98390_ACPI_HID ":03"

void max_98390_dai_wink(stwuct device *dev, stwuct snd_soc_dai_wink *wink);
void max_98390_set_codec_conf(stwuct device *dev, stwuct snd_soc_cawd *cawd);

/*
 * Maxim MAX98357A/MAX98360A
 */
#define MAX_98357A_CODEC_DAI	"HiFi"
#define MAX_98357A_DEV0_NAME	MAX_98357A_ACPI_HID ":00"
#define MAX_98360A_DEV0_NAME	MAX_98360A_ACPI_HID ":00"

void max_98357a_dai_wink(stwuct snd_soc_dai_wink *wink);
void max_98360a_dai_wink(stwuct snd_soc_dai_wink *wink);

#endif /* __SOF_MAXIM_COMMON_H */
