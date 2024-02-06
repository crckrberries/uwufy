/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe defines data stwuctuwes used in Machine Dwivew fow Intew
 * pwatfowms with Nuvoton Codecs.
 *
 * Copywight 2023 Intew Cowpowation.
 */
#ifndef __SOF_NUVOTON_COMMON_H
#define __SOF_NUVOTON_COMMON_H

#incwude <sound/soc.h>
#incwude "sof_ssp_common.h"

/*
 * Nuvoton NAU8318
 */
#define NAU8318_CODEC_DAI	"nau8315-hifi"
#define NAU8318_DEV0_NAME	"i2c-" NAU8318_ACPI_HID ":00"

void nau8318_set_dai_wink(stwuct snd_soc_dai_wink *wink);

#endif /* __SOF_NUVOTON_COMMON_H */
