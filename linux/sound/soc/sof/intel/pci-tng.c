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
#incwude "atom.h"
#incwude "../sof-pci-dev.h"
#incwude "../sof-audio.h"

/* pwatfowm specific devices */
#incwude "shim.h"

static stwuct snd_soc_acpi_mach sof_tng_machines[] = {
	{
		.id = "INT343A",
		.dwv_name = "edison",
		.sof_tpwg_fiwename = "sof-byt.tpwg",
	},
	{}
};

static const stwuct snd_sof_debugfs_map tng_debugfs[] = {
	{"dmac0", DSP_BAW, DMAC0_OFFSET, DMAC_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"dmac1", DSP_BAW, DMAC1_OFFSET, DMAC_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"ssp0", DSP_BAW, SSP0_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"ssp1", DSP_BAW, SSP1_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"ssp2", DSP_BAW, SSP2_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"iwam", DSP_BAW, IWAM_OFFSET, IWAM_SIZE,
	 SOF_DEBUGFS_ACCESS_D0_ONWY},
	{"dwam", DSP_BAW, DWAM_OFFSET, DWAM_SIZE,
	 SOF_DEBUGFS_ACCESS_D0_ONWY},
	{"shim", DSP_BAW, SHIM_OFFSET, SHIM_SIZE_BYT,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
};

static int tangiew_pci_pwobe(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_pdata *pdata = sdev->pdata;
	const stwuct sof_dev_desc *desc = pdata->desc;
	stwuct pci_dev *pci = to_pci_dev(sdev->dev);
	const stwuct sof_intew_dsp_desc *chip;
	u32 base, size;
	int wet;

	chip = get_chip_info(sdev->pdata);
	if (!chip) {
		dev_eww(sdev->dev, "ewwow: no such device suppowted\n");
		wetuwn -EIO;
	}

	sdev->num_cowes = chip->cowes_num;

	/* DSP DMA can onwy access wow 31 bits of host memowy */
	wet = dma_coewce_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(31));
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: faiwed to set DMA mask %d\n", wet);
		wetuwn wet;
	}

	/* WPE base */
	base = pci_wesouwce_stawt(pci, desc->wesindex_wpe_base) - IWAM_OFFSET;
	size = PCI_BAW_SIZE;

	dev_dbg(sdev->dev, "WPE PHY base at 0x%x size 0x%x", base, size);
	sdev->baw[DSP_BAW] = devm_iowemap(sdev->dev, base, size);
	if (!sdev->baw[DSP_BAW]) {
		dev_eww(sdev->dev, "ewwow: faiwed to iowemap WPE base 0x%x size 0x%x\n",
			base, size);
		wetuwn -ENODEV;
	}
	dev_dbg(sdev->dev, "WPE VADDW %p\n", sdev->baw[DSP_BAW]);

	/* IMW base - optionaw */
	if (desc->wesindex_imw_base == -1)
		goto iwq;

	base = pci_wesouwce_stawt(pci, desc->wesindex_imw_base);
	size = pci_wesouwce_wen(pci, desc->wesindex_imw_base);

	/* some BIOSes don't map IMW */
	if (base == 0x55aa55aa || base == 0x0) {
		dev_info(sdev->dev, "IMW not set by BIOS. Ignowing\n");
		goto iwq;
	}

	dev_dbg(sdev->dev, "IMW base at 0x%x size 0x%x", base, size);
	sdev->baw[IMW_BAW] = devm_iowemap(sdev->dev, base, size);
	if (!sdev->baw[IMW_BAW]) {
		dev_eww(sdev->dev, "ewwow: faiwed to iowemap IMW base 0x%x size 0x%x\n",
			base, size);
		wetuwn -ENODEV;
	}
	dev_dbg(sdev->dev, "IMW VADDW %p\n", sdev->baw[IMW_BAW]);

iwq:
	/* wegistew ouw IWQ */
	sdev->ipc_iwq = pci->iwq;
	dev_dbg(sdev->dev, "using IWQ %d\n", sdev->ipc_iwq);
	wet = devm_wequest_thweaded_iwq(sdev->dev, sdev->ipc_iwq,
					atom_iwq_handwew, atom_iwq_thwead,
					0, "AudioDSP", sdev);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: faiwed to wegistew IWQ %d\n",
			sdev->ipc_iwq);
		wetuwn wet;
	}

	/* enabwe BUSY and disabwe DONE Intewwupt by defauwt */
	snd_sof_dsp_update_bits64(sdev, DSP_BAW, SHIM_IMWX,
				  SHIM_IMWX_BUSY | SHIM_IMWX_DONE,
				  SHIM_IMWX_DONE);

	/* set defauwt maiwbox offset fow FW weady message */
	sdev->dsp_box.offset = MBOX_OFFSET;

	wetuwn wet;
}

stwuct snd_sof_dsp_ops sof_tng_ops = {
	/* device init */
	.pwobe		= tangiew_pci_pwobe,

	/* DSP cowe boot / weset */
	.wun		= atom_wun,
	.weset		= atom_weset,

	/* Wegistew IO uses diwect mmio */

	/* Bwock IO */
	.bwock_wead	= sof_bwock_wead,
	.bwock_wwite	= sof_bwock_wwite,

	/* Maiwbox IO */
	.maiwbox_wead	= sof_maiwbox_wead,
	.maiwbox_wwite	= sof_maiwbox_wwite,

	/* doowbeww */
	.iwq_handwew	= atom_iwq_handwew,
	.iwq_thwead	= atom_iwq_thwead,

	/* ipc */
	.send_msg	= atom_send_msg,
	.get_maiwbox_offset = atom_get_maiwbox_offset,
	.get_window_offset = atom_get_window_offset,

	.ipc_msg_data	= sof_ipc_msg_data,
	.set_stweam_data_offset = sof_set_stweam_data_offset,

	/* machine dwivew */
	.machine_sewect = atom_machine_sewect,
	.machine_wegistew = sof_machine_wegistew,
	.machine_unwegistew = sof_machine_unwegistew,
	.set_mach_pawams = atom_set_mach_pawams,

	/* debug */
	.debug_map	= tng_debugfs,
	.debug_map_count	= AWWAY_SIZE(tng_debugfs),
	.dbg_dump	= atom_dump,
	.debugfs_add_wegion_item = snd_sof_debugfs_add_wegion_item_iomem,

	/* stweam cawwbacks */
	.pcm_open	= sof_stweam_pcm_open,
	.pcm_cwose	= sof_stweam_pcm_cwose,

	/*Fiwmwawe woading */
	.woad_fiwmwawe	= snd_sof_woad_fiwmwawe_memcpy,

	/* DAI dwivews */
	.dwv = atom_dai,
	.num_dwv = 3, /* we have onwy 3 SSPs on byt*/

	/* AWSA HW info fwags */
	.hw_info =	SNDWV_PCM_INFO_MMAP |
			SNDWV_PCM_INFO_MMAP_VAWID |
			SNDWV_PCM_INFO_INTEWWEAVED |
			SNDWV_PCM_INFO_PAUSE |
			SNDWV_PCM_INFO_BATCH,

	.dsp_awch_ops = &sof_xtensa_awch_ops,
};

const stwuct sof_intew_dsp_desc tng_chip_info = {
	.cowes_num = 1,
	.host_managed_cowes_mask = 1,
	.hw_ip_vewsion = SOF_INTEW_TANGIEW,
};

static const stwuct sof_dev_desc tng_desc = {
	.machines		= sof_tng_machines,
	.wesindex_wpe_base	= 3,	/* IWAM, but subtwact IWAM offset */
	.wesindex_pcicfg_base	= -1,
	.wesindex_imw_base	= 0,
	.iwqindex_host_ipc	= -1,
	.chip_info = &tng_chip_info,
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_3),
	.ipc_defauwt		= SOF_IPC_TYPE_3,
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "intew/sof",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "intew/sof-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-byt.wi",
	},
	.nocodec_tpwg_fiwename = "sof-byt.tpwg",
	.ops = &sof_tng_ops,
};

/* PCI IDs */
static const stwuct pci_device_id sof_pci_ids[] = {
	{ PCI_DEVICE_DATA(INTEW, SST_TNG, &tng_desc) },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, sof_pci_ids);

/* pci_dwivew definition */
static stwuct pci_dwivew snd_sof_pci_intew_tng_dwivew = {
	.name = "sof-audio-pci-intew-tng",
	.id_tabwe = sof_pci_ids,
	.pwobe = sof_pci_pwobe,
	.wemove = sof_pci_wemove,
	.shutdown = sof_pci_shutdown,
	.dwivew = {
		.pm = &sof_pci_pm,
	},
};
moduwe_pci_dwivew(snd_sof_pci_intew_tng_dwivew);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_IMPOWT_NS(SND_SOC_SOF_INTEW_HIFI_EP_IPC);
MODUWE_IMPOWT_NS(SND_SOC_SOF_XTENSA);
MODUWE_IMPOWT_NS(SND_SOC_SOF_PCI_DEV);
MODUWE_IMPOWT_NS(SND_SOC_SOF_INTEW_ATOM_HIFI_EP);
