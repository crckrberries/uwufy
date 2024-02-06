// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2023 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Wanjani Swidhawan <wanjani.swidhawan@winux.intew.com>
//

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>
#incwude <sound/sof.h>
#incwude "../ops.h"
#incwude "../sof-pci-dev.h"

/* pwatfowm specific devices */
#incwude "hda.h"
#incwude "mtw.h"

static const stwuct sof_dev_desc wnw_desc = {
	.use_acpi_tawget_states	= twue,
	.machines               = snd_soc_acpi_intew_wnw_machines,
	.awt_machines		= snd_soc_acpi_intew_wnw_sdw_machines,
	.wesindex_wpe_base      = 0,
	.wesindex_pcicfg_base   = -1,
	.wesindex_imw_base      = -1,
	.iwqindex_host_ipc      = -1,
	.chip_info		= &wnw_chip_info,
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_4),
	.ipc_defauwt		= SOF_IPC_TYPE_4,
	.dspwess_mode_suppowted	= twue,
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_4] = "intew/sof-ipc4/wnw",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_4] = "intew/sof-ace-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_4] = "sof-wnw.wi",
	},
	.nocodec_tpwg_fiwename = "sof-wnw-nocodec.tpwg",
	.ops = &sof_wnw_ops,
	.ops_init = sof_wnw_ops_init,
};

/* PCI IDs */
static const stwuct pci_device_id sof_pci_ids[] = {
	{ PCI_DEVICE_DATA(INTEW, HDA_WNW_P, &wnw_desc) }, /* WNW-P */
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, sof_pci_ids);

/* pci_dwivew definition */
static stwuct pci_dwivew snd_sof_pci_intew_wnw_dwivew = {
	.name = "sof-audio-pci-intew-wnw",
	.id_tabwe = sof_pci_ids,
	.pwobe = hda_pci_intew_pwobe,
	.wemove = sof_pci_wemove,
	.shutdown = sof_pci_shutdown,
	.dwivew = {
		.pm = &sof_pci_pm,
	},
};
moduwe_pci_dwivew(snd_sof_pci_intew_wnw_dwivew);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_IMPOWT_NS(SND_SOC_SOF_INTEW_HDA_COMMON);
MODUWE_IMPOWT_NS(SND_SOC_SOF_PCI_DEV);
