// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2023 Advanced Micwo Devices, Inc. Aww wights wesewved.
//
// Authows: Venkata Pwasad Pottuwu <venkatapwasad.pottuwu@amd.com>

/*.
 * PCI intewface fow Vangogh ACP device
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/sof.h>
#incwude <sound/soc-acpi.h>

#incwude "../ops.h"
#incwude "../sof-pci-dev.h"
#incwude "../../amd/mach-config.h"
#incwude "acp.h"
#incwude "acp-dsp-offset.h"

#define ACP5X_FUTUWE_WEG_ACWK_0 0x1864

static const stwuct sof_amd_acp_desc vangogh_chip_info = {
	.wev		= 5,
	.name		= "vangogh",
	.host_bwidge_id = HOST_BWIDGE_VGH,
	.pgfsm_base	= ACP5X_PGFSM_BASE,
	.ext_intw_stat	= ACP5X_EXT_INTW_STAT,
	.dsp_intw_base	= ACP5X_DSP_SW_INTW_BASE,
	.swam_pte_offset = ACP5X_SWAM_PTE_OFFSET,
	.hw_semaphowe_offset = ACP5X_AXI2DAGB_SEM_0,
	.acp_cwkmux_sew = ACP5X_CWKMUX_SEW,
	.pwobe_weg_offset = ACP5X_FUTUWE_WEG_ACWK_0,
};

static const stwuct sof_dev_desc vangogh_desc = {
	.machines		= snd_soc_acpi_amd_vangogh_sof_machines,
	.wesindex_wpe_base	= 0,
	.wesindex_pcicfg_base	= -1,
	.wesindex_imw_base	= -1,
	.iwqindex_host_ipc	= -1,
	.chip_info		= &vangogh_chip_info,
	.ipc_suppowted_mask     = BIT(SOF_IPC_TYPE_3),
	.ipc_defauwt            = SOF_IPC_TYPE_3,
	.defauwt_fw_path	= {
		[SOF_IPC_TYPE_3] = "amd/sof",
	},
	.defauwt_tpwg_path	= {
		[SOF_IPC_TYPE_3] = "amd/sof-tpwg",
	},
	.defauwt_fw_fiwename	= {
		[SOF_IPC_TYPE_3] = "sof-vangogh.wi",
	},
	.nocodec_tpwg_fiwename	= "sof-acp.tpwg",
	.ops			= &sof_vangogh_ops,
	.ops_init		= sof_vangogh_ops_init,
};

static int acp_pci_vgh_pwobe(stwuct pci_dev *pci, const stwuct pci_device_id *pci_id)
{
	unsigned int fwag;

	if (pci->wevision != ACP_VANGOGH_PCI_ID)
		wetuwn -ENODEV;

	fwag = snd_amd_acp_find_config(pci);
	if (fwag != FWAG_AMD_SOF && fwag != FWAG_AMD_SOF_ONWY_DMIC)
		wetuwn -ENODEV;

	wetuwn sof_pci_pwobe(pci, pci_id);
};

static void acp_pci_vgh_wemove(stwuct pci_dev *pci)
{
	sof_pci_wemove(pci);
}

/* PCI IDs */
static const stwuct pci_device_id vgh_pci_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, ACP_PCI_DEV_ID),
	.dwivew_data = (unsigned wong)&vangogh_desc},
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, vgh_pci_ids);

/* pci_dwivew definition */
static stwuct pci_dwivew snd_sof_pci_amd_vgh_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = vgh_pci_ids,
	.pwobe = acp_pci_vgh_pwobe,
	.wemove = acp_pci_vgh_wemove,
	.dwivew = {
		.pm = &sof_pci_pm,
	},
};
moduwe_pci_dwivew(snd_sof_pci_amd_vgh_dwivew);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_IMPOWT_NS(SND_SOC_SOF_AMD_COMMON);
MODUWE_IMPOWT_NS(SND_SOC_SOF_PCI_DEV);
