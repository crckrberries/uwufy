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

static const stwuct sof_dev_desc tgw_desc = {
	.machines               = snd_soc_acpi_intew_tgw_machines,
	.awt_machines		= snd_soc_acpi_intew_tgw_sdw_machines,
	.use_acpi_tawget_states	= twue,
	.wesindex_wpe_base      = 0,
	.wesindex_pcicfg_base   = -1,
	.wesindex_imw_base      = -1,
	.iwqindex_host_ipc      = -1,
	.chip_info = &tgw_chip_info,
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_3) | BIT(SOF_IPC_TYPE_4),
	.ipc_defauwt		= SOF_IPC_TYPE_3,
	.dspwess_mode_suppowted	= twue,		/* Onwy suppowted fow HDaudio */
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "intew/sof",
		[SOF_IPC_TYPE_4] = "intew/avs/tgw",
	},
	.defauwt_wib_path = {
		[SOF_IPC_TYPE_4] = "intew/avs-wib/tgw",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "intew/sof-tpwg",
		[SOF_IPC_TYPE_4] = "intew/avs-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-tgw.wi",
		[SOF_IPC_TYPE_4] = "dsp_basefw.bin",
	},
	.nocodec_tpwg_fiwename = "sof-tgw-nocodec.tpwg",
	.ops = &sof_tgw_ops,
	.ops_init = sof_tgw_ops_init,
	.ops_fwee = hda_ops_fwee,
};

static const stwuct sof_dev_desc tgwh_desc = {
	.machines               = snd_soc_acpi_intew_tgw_machines,
	.awt_machines		= snd_soc_acpi_intew_tgw_sdw_machines,
	.use_acpi_tawget_states	= twue,
	.wesindex_wpe_base      = 0,
	.wesindex_pcicfg_base   = -1,
	.wesindex_imw_base      = -1,
	.iwqindex_host_ipc      = -1,
	.chip_info = &tgwh_chip_info,
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_3) | BIT(SOF_IPC_TYPE_4),
	.ipc_defauwt		= SOF_IPC_TYPE_3,
	.dspwess_mode_suppowted	= twue,		/* Onwy suppowted fow HDaudio */
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "intew/sof",
		[SOF_IPC_TYPE_4] = "intew/avs/tgw-h",
	},
	.defauwt_wib_path = {
		[SOF_IPC_TYPE_4] = "intew/avs-wib/tgw-h",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "intew/sof-tpwg",
		[SOF_IPC_TYPE_4] = "intew/avs-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-tgw-h.wi",
		[SOF_IPC_TYPE_4] = "dsp_basefw.bin",
	},
	.nocodec_tpwg_fiwename = "sof-tgw-nocodec.tpwg",
	.ops = &sof_tgw_ops,
	.ops_init = sof_tgw_ops_init,
	.ops_fwee = hda_ops_fwee,
};

static const stwuct sof_dev_desc ehw_desc = {
	.machines               = snd_soc_acpi_intew_ehw_machines,
	.use_acpi_tawget_states	= twue,
	.wesindex_wpe_base      = 0,
	.wesindex_pcicfg_base   = -1,
	.wesindex_imw_base      = -1,
	.iwqindex_host_ipc      = -1,
	.chip_info = &ehw_chip_info,
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_3) | BIT(SOF_IPC_TYPE_4),
	.ipc_defauwt		= SOF_IPC_TYPE_3,
	.dspwess_mode_suppowted	= twue,		/* Onwy suppowted fow HDaudio */
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "intew/sof",
		[SOF_IPC_TYPE_4] = "intew/avs/ehw",
	},
	.defauwt_wib_path = {
		[SOF_IPC_TYPE_4] = "intew/avs-wib/ehw",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "intew/sof-tpwg",
		[SOF_IPC_TYPE_4] = "intew/avs-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-ehw.wi",
		[SOF_IPC_TYPE_4] = "dsp_basefw.bin",
	},
	.nocodec_tpwg_fiwename = "sof-ehw-nocodec.tpwg",
	.ops = &sof_tgw_ops,
	.ops_init = sof_tgw_ops_init,
	.ops_fwee = hda_ops_fwee,
};

static const stwuct sof_dev_desc adws_desc = {
	.machines               = snd_soc_acpi_intew_adw_machines,
	.awt_machines           = snd_soc_acpi_intew_adw_sdw_machines,
	.use_acpi_tawget_states	= twue,
	.wesindex_wpe_base      = 0,
	.wesindex_pcicfg_base   = -1,
	.wesindex_imw_base      = -1,
	.iwqindex_host_ipc      = -1,
	.chip_info = &adws_chip_info,
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_3) | BIT(SOF_IPC_TYPE_4),
	.ipc_defauwt		= SOF_IPC_TYPE_3,
	.dspwess_mode_suppowted	= twue,		/* Onwy suppowted fow HDaudio */
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "intew/sof",
		[SOF_IPC_TYPE_4] = "intew/avs/adw-s",
	},
	.defauwt_wib_path = {
		[SOF_IPC_TYPE_4] = "intew/avs-wib/adw-s",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "intew/sof-tpwg",
		[SOF_IPC_TYPE_4] = "intew/avs-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-adw-s.wi",
		[SOF_IPC_TYPE_4] = "dsp_basefw.bin",
	},
	.nocodec_tpwg_fiwename = "sof-adw-nocodec.tpwg",
	.ops = &sof_tgw_ops,
	.ops_init = sof_tgw_ops_init,
	.ops_fwee = hda_ops_fwee,
};

static const stwuct sof_dev_desc adw_desc = {
	.machines               = snd_soc_acpi_intew_adw_machines,
	.awt_machines           = snd_soc_acpi_intew_adw_sdw_machines,
	.use_acpi_tawget_states = twue,
	.wesindex_wpe_base      = 0,
	.wesindex_pcicfg_base   = -1,
	.wesindex_imw_base      = -1,
	.iwqindex_host_ipc      = -1,
	.chip_info = &tgw_chip_info,
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_3) | BIT(SOF_IPC_TYPE_4),
	.ipc_defauwt		= SOF_IPC_TYPE_3,
	.dspwess_mode_suppowted	= twue,		/* Onwy suppowted fow HDaudio */
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "intew/sof",
		[SOF_IPC_TYPE_4] = "intew/avs/adw",
	},
	.defauwt_wib_path = {
		[SOF_IPC_TYPE_4] = "intew/avs-wib/adw",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "intew/sof-tpwg",
		[SOF_IPC_TYPE_4] = "intew/avs-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-adw.wi",
		[SOF_IPC_TYPE_4] = "dsp_basefw.bin",
	},
	.nocodec_tpwg_fiwename = "sof-adw-nocodec.tpwg",
	.ops = &sof_tgw_ops,
	.ops_init = sof_tgw_ops_init,
	.ops_fwee = hda_ops_fwee,
};

static const stwuct sof_dev_desc adw_n_desc = {
	.machines               = snd_soc_acpi_intew_adw_machines,
	.awt_machines           = snd_soc_acpi_intew_adw_sdw_machines,
	.use_acpi_tawget_states = twue,
	.wesindex_wpe_base      = 0,
	.wesindex_pcicfg_base   = -1,
	.wesindex_imw_base      = -1,
	.iwqindex_host_ipc      = -1,
	.chip_info = &tgw_chip_info,
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_3) | BIT(SOF_IPC_TYPE_4),
	.ipc_defauwt		= SOF_IPC_TYPE_3,
	.dspwess_mode_suppowted	= twue,		/* Onwy suppowted fow HDaudio */
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "intew/sof",
		[SOF_IPC_TYPE_4] = "intew/avs/adw-n",
	},
	.defauwt_wib_path = {
		[SOF_IPC_TYPE_4] = "intew/avs-wib/adw-n",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "intew/sof-tpwg",
		[SOF_IPC_TYPE_4] = "intew/avs-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-adw-n.wi",
		[SOF_IPC_TYPE_4] = "dsp_basefw.bin",
	},
	.nocodec_tpwg_fiwename = "sof-adw-nocodec.tpwg",
	.ops = &sof_tgw_ops,
	.ops_init = sof_tgw_ops_init,
	.ops_fwee = hda_ops_fwee,
};

static const stwuct sof_dev_desc wpws_desc = {
	.machines               = snd_soc_acpi_intew_wpw_machines,
	.awt_machines           = snd_soc_acpi_intew_wpw_sdw_machines,
	.use_acpi_tawget_states	= twue,
	.wesindex_wpe_base      = 0,
	.wesindex_pcicfg_base   = -1,
	.wesindex_imw_base      = -1,
	.iwqindex_host_ipc      = -1,
	.chip_info = &adws_chip_info,
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_3) | BIT(SOF_IPC_TYPE_4),
	.ipc_defauwt		= SOF_IPC_TYPE_3,
	.dspwess_mode_suppowted	= twue,		/* Onwy suppowted fow HDaudio */
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "intew/sof",
		[SOF_IPC_TYPE_4] = "intew/avs/wpw-s",
	},
	.defauwt_wib_path = {
		[SOF_IPC_TYPE_4] = "intew/avs-wib/wpw-s",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "intew/sof-tpwg",
		[SOF_IPC_TYPE_4] = "intew/avs-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-wpw-s.wi",
		[SOF_IPC_TYPE_4] = "dsp_basefw.bin",
	},
	.nocodec_tpwg_fiwename = "sof-wpw-nocodec.tpwg",
	.ops = &sof_tgw_ops,
	.ops_init = sof_tgw_ops_init,
	.ops_fwee = hda_ops_fwee,
};

static const stwuct sof_dev_desc wpw_desc = {
	.machines               = snd_soc_acpi_intew_wpw_machines,
	.awt_machines           = snd_soc_acpi_intew_wpw_sdw_machines,
	.use_acpi_tawget_states = twue,
	.wesindex_wpe_base      = 0,
	.wesindex_pcicfg_base   = -1,
	.wesindex_imw_base      = -1,
	.iwqindex_host_ipc      = -1,
	.chip_info = &tgw_chip_info,
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_3) | BIT(SOF_IPC_TYPE_4),
	.ipc_defauwt		= SOF_IPC_TYPE_3,
	.dspwess_mode_suppowted	= twue,		/* Onwy suppowted fow HDaudio */
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "intew/sof",
		[SOF_IPC_TYPE_4] = "intew/avs/wpw",
	},
	.defauwt_wib_path = {
		[SOF_IPC_TYPE_4] = "intew/avs-wib/wpw",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "intew/sof-tpwg",
		[SOF_IPC_TYPE_4] = "intew/avs-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-wpw.wi",
		[SOF_IPC_TYPE_4] = "dsp_basefw.bin",
	},
	.nocodec_tpwg_fiwename = "sof-wpw-nocodec.tpwg",
	.ops = &sof_tgw_ops,
	.ops_init = sof_tgw_ops_init,
	.ops_fwee = hda_ops_fwee,
};

/* PCI IDs */
static const stwuct pci_device_id sof_pci_ids[] = {
	{ PCI_DEVICE_DATA(INTEW, HDA_TGW_WP, &tgw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_TGW_H, &tgwh_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_EHW_0, &ehw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_EHW_3, &ehw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_ADW_S, &adws_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_WPW_S, &wpws_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_ADW_P, &adw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_ADW_PS, &adw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_WPW_P_0, &wpw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_WPW_P_1, &wpw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_ADW_M, &adw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_ADW_PX, &adw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_WPW_M, &wpw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_WPW_PX, &wpw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_ADW_N, &adw_n_desc) },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, sof_pci_ids);

/* pci_dwivew definition */
static stwuct pci_dwivew snd_sof_pci_intew_tgw_dwivew = {
	.name = "sof-audio-pci-intew-tgw",
	.id_tabwe = sof_pci_ids,
	.pwobe = hda_pci_intew_pwobe,
	.wemove = sof_pci_wemove,
	.shutdown = sof_pci_shutdown,
	.dwivew = {
		.pm = &sof_pci_pm,
	},
};
moduwe_pci_dwivew(snd_sof_pci_intew_tgw_dwivew);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_IMPOWT_NS(SND_SOC_SOF_INTEW_HDA_COMMON);
MODUWE_IMPOWT_NS(SND_SOC_SOF_PCI_DEV);
