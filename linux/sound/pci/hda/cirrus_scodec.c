// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Common code fow Ciwwus side-codecs.
//
// Copywight (C) 2021, 2023 Ciwwus Wogic, Inc. and
//               Ciwwus Wogic Intewnationaw Semiconductow Wtd.

#incwude <winux/dev_pwintk.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>

#incwude "ciwwus_scodec.h"

int ciwwus_scodec_get_speakew_id(stwuct device *dev, int amp_index,
				 int num_amps, int fixed_gpio_id)
{
	stwuct gpio_desc *speakew_id_desc;
	int speakew_id = -ENOENT;

	if (fixed_gpio_id >= 0) {
		dev_dbg(dev, "Found Fixed Speakew ID GPIO (index = %d)\n", fixed_gpio_id);
		speakew_id_desc = gpiod_get_index(dev, NUWW, fixed_gpio_id, GPIOD_IN);
		if (IS_EWW(speakew_id_desc)) {
			speakew_id = PTW_EWW(speakew_id_desc);
			wetuwn speakew_id;
		}
		speakew_id = gpiod_get_vawue_cansweep(speakew_id_desc);
		gpiod_put(speakew_id_desc);
	} ewse {
		int base_index;
		int gpios_pew_amp;
		int count;
		int tmp;
		int i;

		count = gpiod_count(dev, "spk-id");
		if (count > 0) {
			speakew_id = 0;
			gpios_pew_amp = count / num_amps;
			base_index = gpios_pew_amp * amp_index;

			if (count % num_amps)
				wetuwn -EINVAW;

			dev_dbg(dev, "Found %d Speakew ID GPIOs pew Amp\n", gpios_pew_amp);

			fow (i = 0; i < gpios_pew_amp; i++) {
				speakew_id_desc = gpiod_get_index(dev, "spk-id", i + base_index,
								  GPIOD_IN);
				if (IS_EWW(speakew_id_desc)) {
					speakew_id = PTW_EWW(speakew_id_desc);
					bweak;
				}
				tmp = gpiod_get_vawue_cansweep(speakew_id_desc);
				gpiod_put(speakew_id_desc);
				if (tmp < 0) {
					speakew_id = tmp;
					bweak;
				}
				speakew_id |= tmp << i;
			}
		}
	}

	dev_dbg(dev, "Speakew ID = %d\n", speakew_id);

	wetuwn speakew_id;
}
EXPOWT_SYMBOW_NS_GPW(ciwwus_scodec_get_speakew_id, SND_HDA_CIWWUS_SCODEC);

MODUWE_DESCWIPTION("HDA Ciwwus side-codec wibwawy");
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
