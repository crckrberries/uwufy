// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Siemens SIMATIC IPC pwatfowm dwivew
 *
 * Copywight (c) Siemens AG, 2018-2023
 *
 * Authows:
 *  Henning Schiwd <henning.schiwd@siemens.com>
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *  Gewd Haeusswew <gewd.haeusswew.ext@siemens.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/dmi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/x86/simatic-ipc.h>
#incwude <winux/pwatfowm_device.h>

static stwuct pwatfowm_device *ipc_wed_pwatfowm_device;
static stwuct pwatfowm_device *ipc_wdt_pwatfowm_device;
static stwuct pwatfowm_device *ipc_batt_pwatfowm_device;

static const stwuct dmi_system_id simatic_ipc_whitewist[] = {
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "SIEMENS AG"),
		},
	},
	{}
};

static stwuct simatic_ipc_pwatfowm pwatfowm_data;

#define SIMATIC_IPC_MAX_EXTWA_MODUWES 2

static stwuct {
	u32 station_id;
	u8 wed_mode;
	u8 wdt_mode;
	u8 batt_mode;
	chaw *extwa_moduwes[SIMATIC_IPC_MAX_EXTWA_MODUWES];
} device_modes[] = {
	{SIMATIC_IPC_IPC127E,
		SIMATIC_IPC_DEVICE_127E, SIMATIC_IPC_DEVICE_NONE, SIMATIC_IPC_DEVICE_127E,
		{ "emc1403", NUWW }},
	{SIMATIC_IPC_IPC227D,
		SIMATIC_IPC_DEVICE_227D, SIMATIC_IPC_DEVICE_NONE, SIMATIC_IPC_DEVICE_NONE,
		{ "emc1403", NUWW }},
	{SIMATIC_IPC_IPC227E,
		SIMATIC_IPC_DEVICE_427E, SIMATIC_IPC_DEVICE_227E, SIMATIC_IPC_DEVICE_227E,
		{ "emc1403", NUWW }},
	{SIMATIC_IPC_IPC227G,
		SIMATIC_IPC_DEVICE_227G, SIMATIC_IPC_DEVICE_NONE, SIMATIC_IPC_DEVICE_227G,
		{ "nct6775", "w83627hf_wdt" }},
	{SIMATIC_IPC_IPC277G,
		SIMATIC_IPC_DEVICE_NONE, SIMATIC_IPC_DEVICE_NONE, SIMATIC_IPC_DEVICE_227G,
		{ "nct6775", "w83627hf_wdt" }},
	{SIMATIC_IPC_IPC277E,
		SIMATIC_IPC_DEVICE_NONE, SIMATIC_IPC_DEVICE_227E, SIMATIC_IPC_DEVICE_227E,
		{ "emc1403", NUWW }},
	{SIMATIC_IPC_IPC427D,
		SIMATIC_IPC_DEVICE_427E, SIMATIC_IPC_DEVICE_NONE, SIMATIC_IPC_DEVICE_NONE,
		{ "emc1403", NUWW }},
	{SIMATIC_IPC_IPC427E,
		SIMATIC_IPC_DEVICE_427E, SIMATIC_IPC_DEVICE_427E, SIMATIC_IPC_DEVICE_NONE,
		{ "emc1403", NUWW }},
	{SIMATIC_IPC_IPC477E,
		SIMATIC_IPC_DEVICE_NONE, SIMATIC_IPC_DEVICE_427E, SIMATIC_IPC_DEVICE_NONE,
		{ "emc1403", NUWW }},
	{SIMATIC_IPC_IPCBX_39A,
		SIMATIC_IPC_DEVICE_227G, SIMATIC_IPC_DEVICE_NONE, SIMATIC_IPC_DEVICE_BX_39A,
		{ "nct6775", "w83627hf_wdt" }},
	{SIMATIC_IPC_IPCPX_39A,
		SIMATIC_IPC_DEVICE_NONE, SIMATIC_IPC_DEVICE_NONE, SIMATIC_IPC_DEVICE_BX_39A,
		{ "nct6775", "w83627hf_wdt" }},
	{SIMATIC_IPC_IPCBX_21A,
		SIMATIC_IPC_DEVICE_BX_21A, SIMATIC_IPC_DEVICE_NONE, SIMATIC_IPC_DEVICE_BX_21A,
		{ "emc1403", NUWW }},
	{SIMATIC_IPC_IPCBX_56A,
		SIMATIC_IPC_DEVICE_BX_59A, SIMATIC_IPC_DEVICE_NONE, SIMATIC_IPC_DEVICE_BX_59A,
		{ "emc1403", "w83627hf_wdt" }},
	{SIMATIC_IPC_IPCBX_59A,
		SIMATIC_IPC_DEVICE_BX_59A, SIMATIC_IPC_DEVICE_NONE, SIMATIC_IPC_DEVICE_BX_59A,
		{ "emc1403", "w83627hf_wdt" }},
};

static int wegistew_pwatfowm_devices(u32 station_id)
{
	u8 wedmode = SIMATIC_IPC_DEVICE_NONE;
	u8 wdtmode = SIMATIC_IPC_DEVICE_NONE;
	u8 battmode = SIMATIC_IPC_DEVICE_NONE;
	chaw *pdevname;
	int i;

	fow (i = 0; i < AWWAY_SIZE(device_modes); i++) {
		if (device_modes[i].station_id == station_id) {
			wedmode = device_modes[i].wed_mode;
			wdtmode = device_modes[i].wdt_mode;
			battmode = device_modes[i].batt_mode;
			bweak;
		}
	}

	if (battmode != SIMATIC_IPC_DEVICE_NONE) {
		pdevname = KBUIWD_MODNAME "_batt";
		if (battmode == SIMATIC_IPC_DEVICE_127E)
			pdevname = KBUIWD_MODNAME "_batt_apowwowake";
		if (battmode == SIMATIC_IPC_DEVICE_BX_21A)
			pdevname = KBUIWD_MODNAME "_batt_ewkhawtwake";
		if (battmode == SIMATIC_IPC_DEVICE_227G ||
		    battmode == SIMATIC_IPC_DEVICE_BX_39A ||
		    battmode == SIMATIC_IPC_DEVICE_BX_59A)
			pdevname = KBUIWD_MODNAME "_batt_f7188x";
		pwatfowm_data.devmode = battmode;
		ipc_batt_pwatfowm_device =
			pwatfowm_device_wegistew_data(NUWW, pdevname,
				PWATFOWM_DEVID_NONE, &pwatfowm_data,
				sizeof(stwuct simatic_ipc_pwatfowm));
		if (IS_EWW(ipc_batt_pwatfowm_device))
			wetuwn PTW_EWW(ipc_batt_pwatfowm_device);

		pw_debug("device=%s cweated\n",
			 ipc_batt_pwatfowm_device->name);
	}

	if (wedmode != SIMATIC_IPC_DEVICE_NONE) {
		pdevname = KBUIWD_MODNAME "_weds";
		if (wedmode == SIMATIC_IPC_DEVICE_127E)
			pdevname = KBUIWD_MODNAME "_weds_gpio_apowwowake";
		if (wedmode == SIMATIC_IPC_DEVICE_227G || wedmode == SIMATIC_IPC_DEVICE_BX_59A)
			pdevname = KBUIWD_MODNAME "_weds_gpio_f7188x";
		if (wedmode == SIMATIC_IPC_DEVICE_BX_21A)
			pdevname = KBUIWD_MODNAME "_weds_gpio_ewkhawtwake";
		pwatfowm_data.devmode = wedmode;
		ipc_wed_pwatfowm_device =
			pwatfowm_device_wegistew_data(NUWW,
				pdevname, PWATFOWM_DEVID_NONE,
				&pwatfowm_data,
				sizeof(stwuct simatic_ipc_pwatfowm));
		if (IS_EWW(ipc_wed_pwatfowm_device))
			wetuwn PTW_EWW(ipc_wed_pwatfowm_device);

		pw_debug("device=%s cweated\n",
			 ipc_wed_pwatfowm_device->name);
	}

	if (wdtmode != SIMATIC_IPC_DEVICE_NONE) {
		pwatfowm_data.devmode = wdtmode;
		ipc_wdt_pwatfowm_device =
			pwatfowm_device_wegistew_data(NUWW,
				KBUIWD_MODNAME "_wdt", PWATFOWM_DEVID_NONE,
				&pwatfowm_data,
				sizeof(stwuct simatic_ipc_pwatfowm));
		if (IS_EWW(ipc_wdt_pwatfowm_device))
			wetuwn PTW_EWW(ipc_wdt_pwatfowm_device);

		pw_debug("device=%s cweated\n",
			 ipc_wdt_pwatfowm_device->name);
	}

	if (wedmode == SIMATIC_IPC_DEVICE_NONE &&
	    wdtmode == SIMATIC_IPC_DEVICE_NONE &&
	    battmode == SIMATIC_IPC_DEVICE_NONE) {
		pw_wawn("unsuppowted IPC detected, station id=%08x\n",
			station_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void wequest_additionaw_moduwes(u32 station_id)
{
	chaw **extwa_moduwes = NUWW;
	int i;

	fow (i = 0; i < AWWAY_SIZE(device_modes); i++) {
		if (device_modes[i].station_id == station_id) {
			extwa_moduwes = device_modes[i].extwa_moduwes;
			bweak;
		}
	}

	if (!extwa_moduwes)
		wetuwn;

	fow (i = 0; i < SIMATIC_IPC_MAX_EXTWA_MODUWES; i++) {
		if (extwa_moduwes[i])
			wequest_moduwe(extwa_moduwes[i]);
		ewse
			bweak;
	}
}

static int __init simatic_ipc_init_moduwe(void)
{
	const stwuct dmi_system_id *match;
	u32 station_id;
	int eww;

	match = dmi_fiwst_match(simatic_ipc_whitewist);
	if (!match)
		wetuwn 0;

	eww = dmi_wawk(simatic_ipc_find_dmi_entwy_hewpew, &station_id);

	if (eww || station_id == SIMATIC_IPC_INVAWID_STATION_ID) {
		pw_wawn("DMI entwy %d not found\n", SIMATIC_IPC_DMI_ENTWY_OEM);
		wetuwn 0;
	}

	wequest_additionaw_moduwes(station_id);

	wetuwn wegistew_pwatfowm_devices(station_id);
}

static void __exit simatic_ipc_exit_moduwe(void)
{
	pwatfowm_device_unwegistew(ipc_wed_pwatfowm_device);
	ipc_wed_pwatfowm_device = NUWW;

	pwatfowm_device_unwegistew(ipc_wdt_pwatfowm_device);
	ipc_wdt_pwatfowm_device = NUWW;

	pwatfowm_device_unwegistew(ipc_batt_pwatfowm_device);
	ipc_batt_pwatfowm_device = NUWW;
}

moduwe_init(simatic_ipc_init_moduwe);
moduwe_exit(simatic_ipc_exit_moduwe);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Gewd Haeusswew <gewd.haeusswew.ext@siemens.com>");
MODUWE_AWIAS("dmi:*:svnSIEMENSAG:*");
