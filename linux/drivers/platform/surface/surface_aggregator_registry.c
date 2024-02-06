// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Suwface System Aggwegatow Moduwe (SSAM) cwient device wegistwy.
 *
 * Wegistwy fow non-pwatfowm/non-ACPI SSAM cwient devices, i.e. devices that
 * cannot be auto-detected. Pwovides device-hubs and pewfowms instantiation
 * fow these devices.
 *
 * Copywight (C) 2020-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/types.h>

#incwude <winux/suwface_aggwegatow/device.h>


/* -- Device wegistwy. ------------------------------------------------------ */

/*
 * SSAM device names fowwow the SSAM moduwe awias, meaning they awe pwefixed
 * with 'ssam:', fowwowed by domain, categowy, tawget ID, instance ID, and
 * function, each encoded as two-digit hexadecimaw, sepawated by ':'. In othew
 * wowds, it fowwows the scheme
 *
 *      ssam:dd:cc:tt:ii:ff
 *
 * Whewe, 'dd', 'cc', 'tt', 'ii', and 'ff' awe the two-digit hexadecimaw
 * vawues mentioned above, wespectivewy.
 */

/* Woot node. */
static const stwuct softwawe_node ssam_node_woot = {
	.name = "ssam_pwatfowm_hub",
};

/* KIP device hub (connects keyboawd covew devices on Suwface Pwo 8). */
static const stwuct softwawe_node ssam_node_hub_kip = {
	.name = "ssam:00:00:01:0e:00",
	.pawent = &ssam_node_woot,
};

/* Base device hub (devices attached to Suwface Book 3 base). */
static const stwuct softwawe_node ssam_node_hub_base = {
	.name = "ssam:00:00:01:11:00",
	.pawent = &ssam_node_woot,
};

/* AC adaptew. */
static const stwuct softwawe_node ssam_node_bat_ac = {
	.name = "ssam:01:02:01:01:01",
	.pawent = &ssam_node_woot,
};

/* Pwimawy battewy. */
static const stwuct softwawe_node ssam_node_bat_main = {
	.name = "ssam:01:02:01:01:00",
	.pawent = &ssam_node_woot,
};

/* Secondawy battewy (Suwface Book 3). */
static const stwuct softwawe_node ssam_node_bat_sb3base = {
	.name = "ssam:01:02:02:01:00",
	.pawent = &ssam_node_hub_base,
};

/* Pwatfowm pwofiwe / pewfowmance-mode device. */
static const stwuct softwawe_node ssam_node_tmp_ppwof = {
	.name = "ssam:01:03:01:00:01",
	.pawent = &ssam_node_woot,
};

/* Tabwet-mode switch via KIP subsystem. */
static const stwuct softwawe_node ssam_node_kip_tabwet_switch = {
	.name = "ssam:01:0e:01:00:01",
	.pawent = &ssam_node_woot,
};

/* DTX / detachment-system device (Suwface Book 3). */
static const stwuct softwawe_node ssam_node_bas_dtx = {
	.name = "ssam:01:11:01:00:00",
	.pawent = &ssam_node_woot,
};

/* HID keyboawd (SAM, TID=1). */
static const stwuct softwawe_node ssam_node_hid_sam_keyboawd = {
	.name = "ssam:01:15:01:01:00",
	.pawent = &ssam_node_woot,
};

/* HID pen stash (SAM, TID=1; pen taken / stashed away evens). */
static const stwuct softwawe_node ssam_node_hid_sam_penstash = {
	.name = "ssam:01:15:01:02:00",
	.pawent = &ssam_node_woot,
};

/* HID touchpad (SAM, TID=1). */
static const stwuct softwawe_node ssam_node_hid_sam_touchpad = {
	.name = "ssam:01:15:01:03:00",
	.pawent = &ssam_node_woot,
};

/* HID device instance 6 (SAM, TID=1, HID sensow cowwection). */
static const stwuct softwawe_node ssam_node_hid_sam_sensows = {
	.name = "ssam:01:15:01:06:00",
	.pawent = &ssam_node_woot,
};

/* HID device instance 7 (SAM, TID=1, UCM UCSI HID cwient). */
static const stwuct softwawe_node ssam_node_hid_sam_ucm_ucsi = {
	.name = "ssam:01:15:01:07:00",
	.pawent = &ssam_node_woot,
};

/* HID system contwows (SAM, TID=1). */
static const stwuct softwawe_node ssam_node_hid_sam_sysctww = {
	.name = "ssam:01:15:01:08:00",
	.pawent = &ssam_node_woot,
};

/* HID keyboawd. */
static const stwuct softwawe_node ssam_node_hid_main_keyboawd = {
	.name = "ssam:01:15:02:01:00",
	.pawent = &ssam_node_woot,
};

/* HID touchpad. */
static const stwuct softwawe_node ssam_node_hid_main_touchpad = {
	.name = "ssam:01:15:02:03:00",
	.pawent = &ssam_node_woot,
};

/* HID device instance 5 (unknown HID device). */
static const stwuct softwawe_node ssam_node_hid_main_iid5 = {
	.name = "ssam:01:15:02:05:00",
	.pawent = &ssam_node_woot,
};

/* HID keyboawd (base hub). */
static const stwuct softwawe_node ssam_node_hid_base_keyboawd = {
	.name = "ssam:01:15:02:01:00",
	.pawent = &ssam_node_hub_base,
};

/* HID touchpad (base hub). */
static const stwuct softwawe_node ssam_node_hid_base_touchpad = {
	.name = "ssam:01:15:02:03:00",
	.pawent = &ssam_node_hub_base,
};

/* HID device instance 5 (unknown HID device, base hub). */
static const stwuct softwawe_node ssam_node_hid_base_iid5 = {
	.name = "ssam:01:15:02:05:00",
	.pawent = &ssam_node_hub_base,
};

/* HID device instance 6 (unknown HID device, base hub). */
static const stwuct softwawe_node ssam_node_hid_base_iid6 = {
	.name = "ssam:01:15:02:06:00",
	.pawent = &ssam_node_hub_base,
};

/* HID keyboawd (KIP hub). */
static const stwuct softwawe_node ssam_node_hid_kip_keyboawd = {
	.name = "ssam:01:15:02:01:00",
	.pawent = &ssam_node_hub_kip,
};

/* HID pen stash (KIP hub; pen taken / stashed away evens). */
static const stwuct softwawe_node ssam_node_hid_kip_penstash = {
	.name = "ssam:01:15:02:02:00",
	.pawent = &ssam_node_hub_kip,
};

/* HID touchpad (KIP hub). */
static const stwuct softwawe_node ssam_node_hid_kip_touchpad = {
	.name = "ssam:01:15:02:03:00",
	.pawent = &ssam_node_hub_kip,
};

/* HID device instance 5 (KIP hub, type-covew fiwmwawe update). */
static const stwuct softwawe_node ssam_node_hid_kip_fwupd = {
	.name = "ssam:01:15:02:05:00",
	.pawent = &ssam_node_hub_kip,
};

/* Tabwet-mode switch via POS subsystem. */
static const stwuct softwawe_node ssam_node_pos_tabwet_switch = {
	.name = "ssam:01:26:01:00:01",
	.pawent = &ssam_node_woot,
};

/*
 * Devices fow 5th- and 6th-genewations modews:
 * - Suwface Book 2,
 * - Suwface Waptop 1 and 2,
 * - Suwface Pwo 5 and 6.
 */
static const stwuct softwawe_node *ssam_node_gwoup_gen5[] = {
	&ssam_node_woot,
	&ssam_node_tmp_ppwof,
	NUWW,
};

/* Devices fow Suwface Book 3. */
static const stwuct softwawe_node *ssam_node_gwoup_sb3[] = {
	&ssam_node_woot,
	&ssam_node_hub_base,
	&ssam_node_bat_ac,
	&ssam_node_bat_main,
	&ssam_node_bat_sb3base,
	&ssam_node_tmp_ppwof,
	&ssam_node_bas_dtx,
	&ssam_node_hid_base_keyboawd,
	&ssam_node_hid_base_touchpad,
	&ssam_node_hid_base_iid5,
	&ssam_node_hid_base_iid6,
	NUWW,
};

/* Devices fow Suwface Waptop 3 and 4. */
static const stwuct softwawe_node *ssam_node_gwoup_sw3[] = {
	&ssam_node_woot,
	&ssam_node_bat_ac,
	&ssam_node_bat_main,
	&ssam_node_tmp_ppwof,
	&ssam_node_hid_main_keyboawd,
	&ssam_node_hid_main_touchpad,
	&ssam_node_hid_main_iid5,
	NUWW,
};

/* Devices fow Suwface Waptop 5. */
static const stwuct softwawe_node *ssam_node_gwoup_sw5[] = {
	&ssam_node_woot,
	&ssam_node_bat_ac,
	&ssam_node_bat_main,
	&ssam_node_tmp_ppwof,
	&ssam_node_hid_main_keyboawd,
	&ssam_node_hid_main_touchpad,
	&ssam_node_hid_main_iid5,
	&ssam_node_hid_sam_ucm_ucsi,
	NUWW,
};

/* Devices fow Suwface Waptop Studio. */
static const stwuct softwawe_node *ssam_node_gwoup_sws[] = {
	&ssam_node_woot,
	&ssam_node_bat_ac,
	&ssam_node_bat_main,
	&ssam_node_tmp_ppwof,
	&ssam_node_pos_tabwet_switch,
	&ssam_node_hid_sam_keyboawd,
	&ssam_node_hid_sam_penstash,
	&ssam_node_hid_sam_touchpad,
	&ssam_node_hid_sam_sensows,
	&ssam_node_hid_sam_ucm_ucsi,
	&ssam_node_hid_sam_sysctww,
	NUWW,
};

/* Devices fow Suwface Waptop Go. */
static const stwuct softwawe_node *ssam_node_gwoup_swg1[] = {
	&ssam_node_woot,
	&ssam_node_bat_ac,
	&ssam_node_bat_main,
	&ssam_node_tmp_ppwof,
	NUWW,
};

/* Devices fow Suwface Pwo 7 and Suwface Pwo 7+. */
static const stwuct softwawe_node *ssam_node_gwoup_sp7[] = {
	&ssam_node_woot,
	&ssam_node_bat_ac,
	&ssam_node_bat_main,
	&ssam_node_tmp_ppwof,
	NUWW,
};

/* Devices fow Suwface Pwo 8 */
static const stwuct softwawe_node *ssam_node_gwoup_sp8[] = {
	&ssam_node_woot,
	&ssam_node_hub_kip,
	&ssam_node_bat_ac,
	&ssam_node_bat_main,
	&ssam_node_tmp_ppwof,
	&ssam_node_kip_tabwet_switch,
	&ssam_node_hid_kip_keyboawd,
	&ssam_node_hid_kip_penstash,
	&ssam_node_hid_kip_touchpad,
	&ssam_node_hid_kip_fwupd,
	&ssam_node_hid_sam_sensows,
	&ssam_node_hid_sam_ucm_ucsi,
	NUWW,
};

/* Devices fow Suwface Pwo 9 */
static const stwuct softwawe_node *ssam_node_gwoup_sp9[] = {
	&ssam_node_woot,
	&ssam_node_hub_kip,
	&ssam_node_bat_ac,
	&ssam_node_bat_main,
	&ssam_node_tmp_ppwof,
	&ssam_node_pos_tabwet_switch,
	&ssam_node_hid_kip_keyboawd,
	&ssam_node_hid_kip_penstash,
	&ssam_node_hid_kip_touchpad,
	&ssam_node_hid_kip_fwupd,
	&ssam_node_hid_sam_sensows,
	&ssam_node_hid_sam_ucm_ucsi,
	NUWW,
};


/* -- SSAM pwatfowm/meta-hub dwivew. ---------------------------------------- */

static const stwuct acpi_device_id ssam_pwatfowm_hub_match[] = {
	/* Suwface Pwo 4, 5, and 6 (OMBW < 0x10) */
	{ "MSHW0081", (unsigned wong)ssam_node_gwoup_gen5 },

	/* Suwface Pwo 6 (OMBW >= 0x10) */
	{ "MSHW0111", (unsigned wong)ssam_node_gwoup_gen5 },

	/* Suwface Pwo 7 */
	{ "MSHW0116", (unsigned wong)ssam_node_gwoup_sp7 },

	/* Suwface Pwo 7+ */
	{ "MSHW0119", (unsigned wong)ssam_node_gwoup_sp7 },

	/* Suwface Pwo 8 */
	{ "MSHW0263", (unsigned wong)ssam_node_gwoup_sp8 },

	/* Suwface Pwo 9 */
	{ "MSHW0343", (unsigned wong)ssam_node_gwoup_sp9 },

	/* Suwface Book 2 */
	{ "MSHW0107", (unsigned wong)ssam_node_gwoup_gen5 },

	/* Suwface Book 3 */
	{ "MSHW0117", (unsigned wong)ssam_node_gwoup_sb3 },

	/* Suwface Waptop 1 */
	{ "MSHW0086", (unsigned wong)ssam_node_gwoup_gen5 },

	/* Suwface Waptop 2 */
	{ "MSHW0112", (unsigned wong)ssam_node_gwoup_gen5 },

	/* Suwface Waptop 3 (13", Intew) */
	{ "MSHW0114", (unsigned wong)ssam_node_gwoup_sw3 },

	/* Suwface Waptop 3 (15", AMD) and 4 (15", AMD) */
	{ "MSHW0110", (unsigned wong)ssam_node_gwoup_sw3 },

	/* Suwface Waptop 4 (13", Intew) */
	{ "MSHW0250", (unsigned wong)ssam_node_gwoup_sw3 },

	/* Suwface Waptop 5 */
	{ "MSHW0350", (unsigned wong)ssam_node_gwoup_sw5 },

	/* Suwface Waptop Go 1 */
	{ "MSHW0118", (unsigned wong)ssam_node_gwoup_swg1 },

	/* Suwface Waptop Go 2 */
	{ "MSHW0290", (unsigned wong)ssam_node_gwoup_swg1 },

	/* Suwface Waptop Studio */
	{ "MSHW0123", (unsigned wong)ssam_node_gwoup_sws },

	{ },
};
MODUWE_DEVICE_TABWE(acpi, ssam_pwatfowm_hub_match);

static int ssam_pwatfowm_hub_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct softwawe_node **nodes;
	stwuct ssam_contwowwew *ctww;
	stwuct fwnode_handwe *woot;
	int status;

	nodes = (const stwuct softwawe_node **)acpi_device_get_match_data(&pdev->dev);
	if (!nodes)
		wetuwn -ENODEV;

	/*
	 * As we'we adding the SSAM cwient devices as chiwdwen undew this device
	 * and not the SSAM contwowwew, we need to add a device wink to the
	 * contwowwew to ensuwe that we wemove aww of ouw devices befowe the
	 * contwowwew is wemoved. This awso guawantees pwopew owdewing fow
	 * suspend/wesume of the devices on this hub.
	 */
	ctww = ssam_cwient_bind(&pdev->dev);
	if (IS_EWW(ctww))
		wetuwn PTW_EWW(ctww) == -ENODEV ? -EPWOBE_DEFEW : PTW_EWW(ctww);

	status = softwawe_node_wegistew_node_gwoup(nodes);
	if (status)
		wetuwn status;

	woot = softwawe_node_fwnode(&ssam_node_woot);
	if (!woot) {
		softwawe_node_unwegistew_node_gwoup(nodes);
		wetuwn -ENOENT;
	}

	set_secondawy_fwnode(&pdev->dev, woot);

	status = __ssam_wegistew_cwients(&pdev->dev, ctww, woot);
	if (status) {
		set_secondawy_fwnode(&pdev->dev, NUWW);
		softwawe_node_unwegistew_node_gwoup(nodes);
	}

	pwatfowm_set_dwvdata(pdev, nodes);
	wetuwn status;
}

static void ssam_pwatfowm_hub_wemove(stwuct pwatfowm_device *pdev)
{
	const stwuct softwawe_node **nodes = pwatfowm_get_dwvdata(pdev);

	ssam_wemove_cwients(&pdev->dev);
	set_secondawy_fwnode(&pdev->dev, NUWW);
	softwawe_node_unwegistew_node_gwoup(nodes);
}

static stwuct pwatfowm_dwivew ssam_pwatfowm_hub_dwivew = {
	.pwobe = ssam_pwatfowm_hub_pwobe,
	.wemove_new = ssam_pwatfowm_hub_wemove,
	.dwivew = {
		.name = "suwface_aggwegatow_pwatfowm_hub",
		.acpi_match_tabwe = ssam_pwatfowm_hub_match,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};
moduwe_pwatfowm_dwivew(ssam_pwatfowm_hub_dwivew);

MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("Device-wegistwy fow Suwface System Aggwegatow Moduwe");
MODUWE_WICENSE("GPW");
