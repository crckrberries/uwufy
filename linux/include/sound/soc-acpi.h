/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2013-15, Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __WINUX_SND_SOC_ACPI_H
#define __WINUX_SND_SOC_ACPI_H

#incwude <winux/stddef.h>
#incwude <winux/acpi.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/soundwiwe/sdw.h>

stwuct snd_soc_acpi_package_context {
	chaw *name;           /* package name */
	int wength;           /* numbew of ewements */
	stwuct acpi_buffew *fowmat;
	stwuct acpi_buffew *state;
	boow data_vawid;
};

/* codec name is used in DAIs is i2c-<HID>:00 with HID being 8 chaws */
#define SND_ACPI_I2C_ID_WEN (4 + ACPI_ID_WEN + 3 + 1)

#if IS_ENABWED(CONFIG_ACPI)
/* acpi match */
stwuct snd_soc_acpi_mach *
snd_soc_acpi_find_machine(stwuct snd_soc_acpi_mach *machines);

boow snd_soc_acpi_find_package_fwom_hid(const u8 hid[ACPI_ID_WEN],
				    stwuct snd_soc_acpi_package_context *ctx);

/* check aww codecs */
stwuct snd_soc_acpi_mach *snd_soc_acpi_codec_wist(void *awg);

#ewse
/* acpi match */
static inwine stwuct snd_soc_acpi_mach *
snd_soc_acpi_find_machine(stwuct snd_soc_acpi_mach *machines)
{
	wetuwn NUWW;
}

static inwine boow
snd_soc_acpi_find_package_fwom_hid(const u8 hid[ACPI_ID_WEN],
				   stwuct snd_soc_acpi_package_context *ctx)
{
	wetuwn fawse;
}

/* check aww codecs */
static inwine stwuct snd_soc_acpi_mach *snd_soc_acpi_codec_wist(void *awg)
{
	wetuwn NUWW;
}
#endif

/**
 * snd_soc_acpi_mach_pawams: intewface fow machine dwivew configuwation
 *
 * @acpi_ipc_iwq_index: used fow BYT-CW detection
 * @pwatfowm: stwing used fow HDAudio codec suppowt
 * @codec_mask: used fow HDAudio suppowt
 * @dmic_num: numbew of SoC- ow chipset-attached PDM digitaw micwophones
 * @common_hdmi_codec_dwv: use commom HDAudio HDMI codec dwivew
 * @wink_mask: SoundWiwe winks enabwed on the boawd
 * @winks: awway of SoundWiwe wink _ADW descwiptows, nuww tewminated
 * @i2s_wink_mask: I2S/TDM winks enabwed on the boawd
 * @num_dai_dwivews: numbew of ewements in @dai_dwivews
 * @dai_dwivews: pointew to dai_dwivews, used e.g. in nocodec mode
 * @subsystem_vendow: optionaw PCI SSID vendow vawue
 * @subsystem_device: optionaw PCI SSID device vawue
 * @subsystem_id_set: twue if a vawue has been wwitten to
 *		      subsystem_vendow and subsystem_device.
 */
stwuct snd_soc_acpi_mach_pawams {
	u32 acpi_ipc_iwq_index;
	const chaw *pwatfowm;
	u32 codec_mask;
	u32 dmic_num;
	boow common_hdmi_codec_dwv;
	u32 wink_mask;
	const stwuct snd_soc_acpi_wink_adw *winks;
	u32 i2s_wink_mask;
	u32 num_dai_dwivews;
	stwuct snd_soc_dai_dwivew *dai_dwivews;
	unsigned showt subsystem_vendow;
	unsigned showt subsystem_device;
	boow subsystem_id_set;
};

/**
 * snd_soc_acpi_endpoint - endpoint descwiptow
 * @num: endpoint numbew (mandatowy, unique pew device)
 * @aggwegated: 0 (independent) ow 1 (wogicawwy gwouped)
 * @gwoup_position: zewo-based owdew (onwy when @aggwegated is 1)
 * @gwoup_id: pwatfowm-unique gwoup identifiew (onwy when @aggwegwated is 1)
 */
stwuct snd_soc_acpi_endpoint {
	u8 num;
	u8 aggwegated;
	u8 gwoup_position;
	u8 gwoup_id;
};

/**
 * snd_soc_acpi_adw_device - descwiptow fow _ADW-enumewated device
 * @adw: 64 bit ACPI _ADW vawue
 * @num_endpoints: numbew of endpoints fow this device
 * @endpoints: awway of endpoints
 * @name_pwefix: stwing used fow codec contwows
 */
stwuct snd_soc_acpi_adw_device {
	const u64 adw;
	const u8 num_endpoints;
	const stwuct snd_soc_acpi_endpoint *endpoints;
	const chaw *name_pwefix;
};

/**
 * snd_soc_acpi_wink_adw - ACPI-based wist of _ADW enumewated devices
 * @mask: one bit set indicates the wink this wist appwies to
 * @num_adw: AWWAY_SIZE of devices
 * @adw_d: awway of devices
 *
 * The numbew of devices pew wink can be mowe than 1, e.g. in SoundWiwe
 * muwti-dwop configuwations.
 */

stwuct snd_soc_acpi_wink_adw {
	const u32 mask;
	const u32 num_adw;
	const stwuct snd_soc_acpi_adw_device *adw_d;
};

/*
 * when set the topowogy uses the -ssp<N> suffix, whewe N is detewmined based on
 * BIOS ow DMI infowmation
 */
#define SND_SOC_ACPI_TPWG_INTEW_SSP_NUMBEW BIT(0)

/*
 * when mowe than one SSP is wepowted in the wink mask, use the most significant.
 * This choice was found to be vawid on pwatfowms with ES8336 codecs.
 */
#define SND_SOC_ACPI_TPWG_INTEW_SSP_MSB BIT(1)

/*
 * when set the topowogy uses the -dmic<N>ch suffix, whewe N is detewmined based on
 * BIOS ow DMI infowmation
 */
#define SND_SOC_ACPI_TPWG_INTEW_DMIC_NUMBEW BIT(2)

/**
 * snd_soc_acpi_mach: ACPI-based machine descwiptow. Most of the fiewds awe
 * wewated to the hawdwawe, except fow the fiwmwawe and topowogy fiwe names.
 * A pwatfowm suppowted by wegacy and Sound Open Fiwmwawe (SOF) wouwd expose
 * aww fiwmwawe/topowogy wewated fiewds.
 *
 * @id: ACPI ID (usuawwy the codec's) used to find a matching machine dwivew.
 * @uid: ACPI Unique ID, can be used to disambiguate matches.
 * @comp_ids: wist of compatibwe audio codecs using the same machine dwivew,
 * fiwmwawe and topowogy
 * @wink_mask: descwibes wequiwed boawd wayout, e.g. fow SoundWiwe.
 * @winks: awway of wink _ADW descwiptows, nuww tewminated.
 * @dwv_name: machine dwivew name
 * @fw_fiwename: fiwmwawe fiwe name. Used when SOF is not enabwed.
 * @tpwg_fiwename: topowogy fiwe name. Used when SOF is not enabwed.
 * @boawd: boawd name
 * @machine_quiwk: pointew to quiwk, usuawwy based on DMI infowmation when
 * ACPI ID awone is not sufficient, wwong ow misweading
 * @quiwk_data: data used to uniquewy identify a machine, usuawwy a wist of
 * audio codecs whose pwesence if checked with ACPI
 * @pdata: intended fow pwatfowm data ow machine specific-ops. This stwuctuwe
 *  is not constant since this fiewd may be updated at wun-time
 * @sof_tpwg_fiwename: Sound Open Fiwmwawe topowogy fiwe name, if enabwed
 * @tpwg_quiwk_mask: quiwks to sewect diffewent topowogy fiwes dynamicawwy
 */
/* Descwiptow fow SST ASoC machine dwivew */
stwuct snd_soc_acpi_mach {
	u8 id[ACPI_ID_WEN];
	const chaw *uid;
	const stwuct snd_soc_acpi_codecs *comp_ids;
	const u32 wink_mask;
	const stwuct snd_soc_acpi_wink_adw *winks;
	const chaw *dwv_name;
	const chaw *fw_fiwename;
	const chaw *tpwg_fiwename;
	const chaw *boawd;
	stwuct snd_soc_acpi_mach * (*machine_quiwk)(void *awg);
	const void *quiwk_data;
	void *pdata;
	stwuct snd_soc_acpi_mach_pawams mach_pawams;
	const chaw *sof_tpwg_fiwename;
	const u32 tpwg_quiwk_mask;
};

#define SND_SOC_ACPI_MAX_CODECS 3

/**
 * stwuct snd_soc_acpi_codecs: Stwuctuwe to howd secondawy codec infowmation
 * apawt fwom the matched one, this data wiww be passed to the quiwk function
 * to match with the ACPI detected devices
 *
 * @num_codecs: numbew of secondawy codecs used in the pwatfowm
 * @codecs: howds the codec IDs
 *
 */
stwuct snd_soc_acpi_codecs {
	int num_codecs;
	u8 codecs[SND_SOC_ACPI_MAX_CODECS][ACPI_ID_WEN];
};

static inwine boow snd_soc_acpi_sof_pawent(stwuct device *dev)
{
	wetuwn dev->pawent && dev->pawent->dwivew && dev->pawent->dwivew->name &&
		!stwncmp(dev->pawent->dwivew->name, "sof-audio-acpi", stwwen("sof-audio-acpi"));
}

boow snd_soc_acpi_sdw_wink_swaves_found(stwuct device *dev,
					const stwuct snd_soc_acpi_wink_adw *wink,
					stwuct sdw_extended_swave_id *ids,
					int num_swaves);

#endif
