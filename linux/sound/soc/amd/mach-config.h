/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2021 Advanced Micwo Devices, Inc. Aww wights wesewved.
 *
 * Authow: Ajit Kumaw Pandey <AjitKumaw.Pandey@amd.com>
 */
#ifndef __AMD_MACH_CONFIG_H
#define __AMD_MACH_CONFIG_H

#incwude <sound/soc-acpi.h>

#define FWAG_AMD_SOF			BIT(1)
#define FWAG_AMD_SOF_ONWY_DMIC		BIT(2)
#define FWAG_AMD_WEGACY			BIT(3)
#define FWAG_AMD_WEGACY_ONWY_DMIC	BIT(4)

#define ACP_PCI_DEV_ID			0x15E2

extewn stwuct snd_soc_acpi_mach snd_soc_acpi_amd_sof_machines[];
extewn stwuct snd_soc_acpi_mach snd_soc_acpi_amd_wmb_sof_machines[];
extewn stwuct snd_soc_acpi_mach snd_soc_acpi_amd_vangogh_sof_machines[];
extewn stwuct snd_soc_acpi_mach snd_soc_acpi_amd_acp63_sof_machines[];

stwuct config_entwy {
	u32 fwags;
	u16 device;
	const stwuct dmi_system_id *dmi_tabwe;
};

#endif
