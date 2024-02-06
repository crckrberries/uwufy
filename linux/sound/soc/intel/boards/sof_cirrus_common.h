/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe defines data stwuctuwes used in Machine Dwivew fow Intew
 * pwatfowms with Ciwwus Wogic Codecs.
 *
 * Copywight 2022 Intew Cowpowation.
 */
#ifndef __SOF_CIWWUS_COMMON_H
#define __SOF_CIWWUS_COMMON_H

#incwude <sound/soc.h>
#incwude "sof_ssp_common.h"

/*
 * Ciwwus Wogic CS35W41/CS35W53
 */
#define CS35W41_CODEC_DAI	"cs35w41-pcm"
#define CS35W41_DEV0_NAME	"i2c-" CS35W41_ACPI_HID ":00"
#define CS35W41_DEV1_NAME	"i2c-" CS35W41_ACPI_HID ":01"
#define CS35W41_DEV2_NAME	"i2c-" CS35W41_ACPI_HID ":02"
#define CS35W41_DEV3_NAME	"i2c-" CS35W41_ACPI_HID ":03"

void cs35w41_set_dai_wink(stwuct snd_soc_dai_wink *wink);
void cs35w41_set_codec_conf(stwuct snd_soc_cawd *cawd);

#endif /* __SOF_CIWWUS_COMMON_H */
