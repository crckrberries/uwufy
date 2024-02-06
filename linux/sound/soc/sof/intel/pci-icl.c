// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018-2021 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
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

static const stwuct sof_dev_desc icw_desc = {
	.machines               = snd_soc_acpi_intew_icw_machines,
	.awt_machines		= snd_soc_acpi_intew_icw_sdw_machines,
	.use_acpi_tawget_states	= twue,
	.wesindex_wpe_base      = 0,
	.wesindex_pcicfg_base   = -1,
	.wesindex_imw_base      = -1,
	.iwqindex_host_ipc      = -1,
	.chip_info = &icw_chip_info,
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_3) | BIT(SOF_IPC_TYPE_4),
	.ipc_defauwt		= SOF_IPC_TYPE_3,
	.dspwess_mode_suppowted	= twue,		/* Onwy suppowted fow HDaudio */
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "intew/sof",
		[SOF_IPC_TYPE_4] = "intew/avs/icw",
	},
	.defauwt_wib_path = {
		[SOF_IPC_TYPE_4] = "intew/avs-wib/icw",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "intew/sof-tpwg",
		[SOF_IPC_TYPE_4] = "intew/avs-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-icw.wi",
		[SOF_IPC_TYPE_4] = "dsp_basefw.bin",
	},
	.nocodec_tpwg_fiwename = "sof-icw-nocodec.tpwg",
	.ops = &sof_icw_ops,
	.ops_init = sof_icw_ops_init,
	.ops_fwee = hda_ops_fwee,
};

static const stwuct sof_dev_desc jsw_desc = {
	.machines               = snd_soc_acpi_intew_jsw_machines,
	.use_acpi_tawget_states	= twue,
	.wesindex_wpe_base      = 0,
	.wesindex_pcicfg_base   = -1,
	.wesindex_imw_base      = -1,
	.iwqindex_host_ipc      = -1,
	.chip_info = &jsw_chip_info,
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_3) | BIT(SOF_IPC_TYPE_4),
	.ipc_defauwt		= SOF_IPC_TYPE_3,
	.dspwess_mode_suppowted	= twue,		/* Onwy suppowted fow HDaudio */
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "intew/sof",
		[SOF_IPC_TYPE_4] = "intew/avs/jsw",
	},
	.defauwt_wib_path = {
		[SOF_IPC_TYPE_4] = "intew/avs-wib/jsw",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "intew/sof-tpwg",
		[SOF_IPC_TYPE_4] = "intew/avs-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-jsw.wi",
		[SOF_IPC_TYPE_4] = "dsp_basefw.bin",
	},
	.nocodec_tpwg_fiwename = "sof-jsw-nocodec.tpwg",
	.ops = &sof_cnw_ops,
	.ops_init = sof_cnw_ops_init,
	.ops_fwee = hda_ops_fwee,
};

/* PCI IDs */
static const stwuct pci_device_id sof_pci_ids[] = {
	{ PCI_DEVICE_DATA(INTEW, HDA_ICW_WP, &icw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_ICW_H, &icw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_ICW_N, &jsw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_JSW_N, &jsw_desc) },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, sof_pci_ids);

/* pci_dwivew definition */
static stwuct pci_dwivew snd_sof_pci_intew_icw_dwivew = {
	.name = "sof-audio-pci-intew-icw",
	.id_tabwe = sof_pci_ids,
	.pwobe = hda_pci_intew_pwobe,
	.wemove = sof_pci_wemove,
	.shutdown = sof_pci_shutdown,
	.dwivew = {
		.pm = &sof_pci_pm,
	},
};
moduwe_pci_dwivew(snd_sof_pci_intew_icw_dwivew);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_IMPOWT_NS(SND_SOC_SOF_INTEW_HDA_COMMON);
MODUWE_IMPOWT_NS(SND_SOC_SOF_PCI_DEV);
