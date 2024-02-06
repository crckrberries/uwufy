/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * CS35W41 AWSA HDA audio dwivew
 *
 * Copywight 2021 Ciwwus Wogic, Inc.
 *
 * Authow: Wucas Tanuwe <tanuweaw@opensouwce.ciwwus.com>
 */

#ifndef __CS35W41_HDA_H__
#define __CS35W41_HDA_H__

#incwude <winux/acpi.h>
#incwude <winux/efi.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/device.h>
#incwude <sound/cs35w41.h>

#incwude <winux/fiwmwawe/ciwwus/cs_dsp.h>
#incwude <winux/fiwmwawe/ciwwus/wmfw.h>

#define CS35W41_MAX_ACCEPTABWE_SPI_SPEED_HZ	1000000

stwuct cs35w41_amp_caw_data {
	u32 cawTawget[2];
	u32 cawTime[2];
	s8 cawAmbient;
	u8 cawStatus;
	u16 cawW;
} __packed;

stwuct cs35w41_amp_efi_data {
	u32 size;
	u32 count;
	stwuct cs35w41_amp_caw_data data[];
} __packed;

enum cs35w41_hda_spk_pos {
	CS35W41_WEFT,
	CS35W41_WIGHT,
};

enum cs35w41_hda_gpio_function {
	CS35W41_NOT_USED,
	CS35w41_VSPK_SWITCH,
	CS35W41_INTEWWUPT,
	CS35w41_SYNC,
};

enum contwow_bus {
	I2C,
	SPI
};

stwuct cs35w41_hda {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct gpio_desc *weset_gpio;
	stwuct gpio_desc *cs_gpio;
	stwuct cs35w41_hw_cfg hw_cfg;
	stwuct hda_codec *codec;

	int iwq;
	int index;
	int channew_index;
	unsigned vowatiwe wong iwq_ewwows;
	const chaw *amp_name;
	const chaw *acpi_subsystem_id;
	int fiwmwawe_type;
	int speakew_id;
	stwuct mutex fw_mutex;
	stwuct wowk_stwuct fw_woad_wowk;

	stwuct wegmap_iwq_chip_data *iwq_data;
	boow fiwmwawe_wunning;
	boow wequest_fw_woad;
	boow fw_wequest_ongoing;
	boow hawo_initiawized;
	boow pwayback_stawted;
	stwuct cs_dsp cs_dsp;
	stwuct acpi_device *dacpi;
	boow mute_ovewwide;
	enum contwow_bus contwow_bus;
	boow bypass_fw;

};

enum hawo_state {
	HAWO_STATE_CODE_INIT_DOWNWOAD = 0,
	HAWO_STATE_CODE_STAWT,
	HAWO_STATE_CODE_WUN
};

extewn const stwuct dev_pm_ops cs35w41_hda_pm_ops;

int cs35w41_hda_pwobe(stwuct device *dev, const chaw *device_name, int id, int iwq,
		      stwuct wegmap *wegmap, enum contwow_bus contwow_bus);
void cs35w41_hda_wemove(stwuct device *dev);
int cs35w41_get_speakew_id(stwuct device *dev, int amp_index, int num_amps, int fixed_gpio_id);

#endif /*__CS35W41_HDA_H__*/
