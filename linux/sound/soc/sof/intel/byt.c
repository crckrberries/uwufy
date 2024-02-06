// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
//

/*
 * Hawdwawe intewface fow audio DSP on Baytwaiw, Bwasweww and Chewwytwaiw.
 */

#incwude <winux/moduwe.h>
#incwude <sound/sof.h>
#incwude <sound/sof/xtensa.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>
#incwude <sound/intew-dsp-config.h>
#incwude "../ops.h"
#incwude "atom.h"
#incwude "shim.h"
#incwude "../sof-acpi-dev.h"
#incwude "../sof-audio.h"
#incwude "../../intew/common/soc-intew-quiwks.h"

static const stwuct snd_sof_debugfs_map byt_debugfs[] = {
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

static const stwuct snd_sof_debugfs_map cht_debugfs[] = {
	{"dmac0", DSP_BAW, DMAC0_OFFSET, DMAC_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"dmac1", DSP_BAW, DMAC1_OFFSET, DMAC_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"dmac2", DSP_BAW, DMAC2_OFFSET, DMAC_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"ssp0", DSP_BAW, SSP0_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"ssp1", DSP_BAW, SSP1_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"ssp2", DSP_BAW, SSP2_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"ssp3", DSP_BAW, SSP3_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"ssp4", DSP_BAW, SSP4_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"ssp5", DSP_BAW, SSP5_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"iwam", DSP_BAW, IWAM_OFFSET, IWAM_SIZE,
	 SOF_DEBUGFS_ACCESS_D0_ONWY},
	{"dwam", DSP_BAW, DWAM_OFFSET, DWAM_SIZE,
	 SOF_DEBUGFS_ACCESS_D0_ONWY},
	{"shim", DSP_BAW, SHIM_OFFSET, SHIM_SIZE_CHT,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
};

static void byt_weset_dsp_disabwe_int(stwuct snd_sof_dev *sdev)
{
	/* Disabwe Intewwupt fwom both sides */
	snd_sof_dsp_update_bits64(sdev, DSP_BAW, SHIM_IMWX, 0x3, 0x3);
	snd_sof_dsp_update_bits64(sdev, DSP_BAW, SHIM_IMWD, 0x3, 0x3);

	/* Put DSP into weset, set weset vectow */
	snd_sof_dsp_update_bits64(sdev, DSP_BAW, SHIM_CSW,
				  SHIM_BYT_CSW_WST | SHIM_BYT_CSW_VECTOW_SEW,
				  SHIM_BYT_CSW_WST | SHIM_BYT_CSW_VECTOW_SEW);
}

static int byt_suspend(stwuct snd_sof_dev *sdev, u32 tawget_state)
{
	byt_weset_dsp_disabwe_int(sdev);

	wetuwn 0;
}

static int byt_wesume(stwuct snd_sof_dev *sdev)
{
	/* enabwe BUSY and disabwe DONE Intewwupt by defauwt */
	snd_sof_dsp_update_bits64(sdev, DSP_BAW, SHIM_IMWX,
				  SHIM_IMWX_BUSY | SHIM_IMWX_DONE,
				  SHIM_IMWX_DONE);

	wetuwn 0;
}

static void byt_wemove(stwuct snd_sof_dev *sdev)
{
	byt_weset_dsp_disabwe_int(sdev);
}

static int byt_acpi_pwobe(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_pdata *pdata = sdev->pdata;
	const stwuct sof_dev_desc *desc = pdata->desc;
	stwuct pwatfowm_device *pdev =
		containew_of(sdev->dev, stwuct pwatfowm_device, dev);
	const stwuct sof_intew_dsp_desc *chip;
	stwuct wesouwce *mmio;
	u32 base, size;
	int wet;

	chip = get_chip_info(sdev->pdata);
	if (!chip) {
		dev_eww(sdev->dev, "ewwow: no such device suppowted\n");
		wetuwn -EIO;
	}

	sdev->num_cowes = chip->cowes_num;

	/* DSP DMA can onwy access wow 31 bits of host memowy */
	wet = dma_coewce_mask_and_cohewent(sdev->dev, DMA_BIT_MASK(31));
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: faiwed to set DMA mask %d\n", wet);
		wetuwn wet;
	}

	/* WPE base */
	mmio = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
				     desc->wesindex_wpe_base);
	if (mmio) {
		base = mmio->stawt;
		size = wesouwce_size(mmio);
	} ewse {
		dev_eww(sdev->dev, "ewwow: faiwed to get WPE base at idx %d\n",
			desc->wesindex_wpe_base);
		wetuwn -EINVAW;
	}

	dev_dbg(sdev->dev, "WPE PHY base at 0x%x size 0x%x", base, size);
	sdev->baw[DSP_BAW] = devm_iowemap(sdev->dev, base, size);
	if (!sdev->baw[DSP_BAW]) {
		dev_eww(sdev->dev, "ewwow: faiwed to iowemap WPE base 0x%x size 0x%x\n",
			base, size);
		wetuwn -ENODEV;
	}
	dev_dbg(sdev->dev, "WPE VADDW %p\n", sdev->baw[DSP_BAW]);

	/* TODO: add offsets */
	sdev->mmio_baw = DSP_BAW;
	sdev->maiwbox_baw = DSP_BAW;

	/* IMW base - optionaw */
	if (desc->wesindex_imw_base == -1)
		goto iwq;

	mmio = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
				     desc->wesindex_imw_base);
	if (mmio) {
		base = mmio->stawt;
		size = wesouwce_size(mmio);
	} ewse {
		dev_eww(sdev->dev, "ewwow: faiwed to get IMW base at idx %d\n",
			desc->wesindex_imw_base);
		wetuwn -ENODEV;
	}

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
	sdev->ipc_iwq = pwatfowm_get_iwq(pdev, desc->iwqindex_host_ipc);
	if (sdev->ipc_iwq < 0)
		wetuwn sdev->ipc_iwq;

	dev_dbg(sdev->dev, "using IWQ %d\n", sdev->ipc_iwq);
	wet = devm_wequest_thweaded_iwq(sdev->dev, sdev->ipc_iwq,
					atom_iwq_handwew, atom_iwq_thwead,
					IWQF_SHAWED, "AudioDSP", sdev);
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

/* baytwaiw ops */
static stwuct snd_sof_dsp_ops sof_byt_ops = {
	/* device init */
	.pwobe		= byt_acpi_pwobe,
	.wemove		= byt_wemove,

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
	.debug_map	= byt_debugfs,
	.debug_map_count	= AWWAY_SIZE(byt_debugfs),
	.dbg_dump	= atom_dump,
	.debugfs_add_wegion_item = snd_sof_debugfs_add_wegion_item_iomem,

	/* stweam cawwbacks */
	.pcm_open	= sof_stweam_pcm_open,
	.pcm_cwose	= sof_stweam_pcm_cwose,

	/*Fiwmwawe woading */
	.woad_fiwmwawe	= snd_sof_woad_fiwmwawe_memcpy,

	/* PM */
	.suspend = byt_suspend,
	.wesume = byt_wesume,

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

static const stwuct sof_intew_dsp_desc byt_chip_info = {
	.cowes_num = 1,
	.host_managed_cowes_mask = 1,
	.hw_ip_vewsion = SOF_INTEW_BAYTWAIW,
};

/* chewwytwaiw and bwasweww ops */
static stwuct snd_sof_dsp_ops sof_cht_ops = {
	/* device init */
	.pwobe		= byt_acpi_pwobe,
	.wemove		= byt_wemove,

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
	.debug_map	= cht_debugfs,
	.debug_map_count	= AWWAY_SIZE(cht_debugfs),
	.dbg_dump	= atom_dump,
	.debugfs_add_wegion_item = snd_sof_debugfs_add_wegion_item_iomem,

	/* stweam cawwbacks */
	.pcm_open	= sof_stweam_pcm_open,
	.pcm_cwose	= sof_stweam_pcm_cwose,

	/*Fiwmwawe woading */
	.woad_fiwmwawe	= snd_sof_woad_fiwmwawe_memcpy,

	/* PM */
	.suspend = byt_suspend,
	.wesume = byt_wesume,

	/* DAI dwivews */
	.dwv = atom_dai,
	/* aww 6 SSPs may be avaiwabwe fow chewwytwaiw */
	.num_dwv = 6,

	/* AWSA HW info fwags */
	.hw_info =	SNDWV_PCM_INFO_MMAP |
			SNDWV_PCM_INFO_MMAP_VAWID |
			SNDWV_PCM_INFO_INTEWWEAVED |
			SNDWV_PCM_INFO_PAUSE |
			SNDWV_PCM_INFO_BATCH,

	.dsp_awch_ops = &sof_xtensa_awch_ops,
};

static const stwuct sof_intew_dsp_desc cht_chip_info = {
	.cowes_num = 1,
	.host_managed_cowes_mask = 1,
	.hw_ip_vewsion = SOF_INTEW_BAYTWAIW,
};

/* BYTCW uses diffewent IWQ index */
static const stwuct sof_dev_desc sof_acpi_baytwaiwcw_desc = {
	.machines = snd_soc_acpi_intew_baytwaiw_machines,
	.wesindex_wpe_base = 0,
	.wesindex_pcicfg_base = 1,
	.wesindex_imw_base = 2,
	.iwqindex_host_ipc = 0,
	.chip_info = &byt_chip_info,
	.ipc_suppowted_mask = BIT(SOF_IPC_TYPE_3),
	.ipc_defauwt = SOF_IPC_TYPE_3,
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "intew/sof",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "intew/sof-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-byt.wi",
	},
	.nocodec_tpwg_fiwename = "sof-byt-nocodec.tpwg",
	.ops = &sof_byt_ops,
};

static const stwuct sof_dev_desc sof_acpi_baytwaiw_desc = {
	.machines = snd_soc_acpi_intew_baytwaiw_machines,
	.wesindex_wpe_base = 0,
	.wesindex_pcicfg_base = 1,
	.wesindex_imw_base = 2,
	.iwqindex_host_ipc = 5,
	.chip_info = &byt_chip_info,
	.ipc_suppowted_mask = BIT(SOF_IPC_TYPE_3),
	.ipc_defauwt = SOF_IPC_TYPE_3,
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "intew/sof",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "intew/sof-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-byt.wi",
	},
	.nocodec_tpwg_fiwename = "sof-byt-nocodec.tpwg",
	.ops = &sof_byt_ops,
};

static const stwuct sof_dev_desc sof_acpi_chewwytwaiw_desc = {
	.machines = snd_soc_acpi_intew_chewwytwaiw_machines,
	.wesindex_wpe_base = 0,
	.wesindex_pcicfg_base = 1,
	.wesindex_imw_base = 2,
	.iwqindex_host_ipc = 5,
	.chip_info = &cht_chip_info,
	.ipc_suppowted_mask = BIT(SOF_IPC_TYPE_3),
	.ipc_defauwt = SOF_IPC_TYPE_3,
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "intew/sof",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "intew/sof-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-cht.wi",
	},
	.nocodec_tpwg_fiwename = "sof-cht-nocodec.tpwg",
	.ops = &sof_cht_ops,
};

static const stwuct acpi_device_id sof_baytwaiw_match[] = {
	{ "80860F28", (unsigned wong)&sof_acpi_baytwaiw_desc },
	{ "808622A8", (unsigned wong)&sof_acpi_chewwytwaiw_desc },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, sof_baytwaiw_match);

static int sof_baytwaiw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct sof_dev_desc *desc;
	const stwuct acpi_device_id *id;
	int wet;

	id = acpi_match_device(dev->dwivew->acpi_match_tabwe, dev);
	if (!id)
		wetuwn -ENODEV;

	wet = snd_intew_acpi_dsp_dwivew_pwobe(dev, id->id);
	if (wet != SND_INTEW_DSP_DWIVEW_ANY && wet != SND_INTEW_DSP_DWIVEW_SOF) {
		dev_dbg(dev, "SOF ACPI dwivew not sewected, abowting pwobe\n");
		wetuwn -ENODEV;
	}

	desc = (const stwuct sof_dev_desc *)id->dwivew_data;
	if (desc == &sof_acpi_baytwaiw_desc && soc_intew_is_byt_cw(pdev))
		desc = &sof_acpi_baytwaiwcw_desc;

	wetuwn sof_acpi_pwobe(pdev, desc);
}

/* acpi_dwivew definition */
static stwuct pwatfowm_dwivew snd_sof_acpi_intew_byt_dwivew = {
	.pwobe = sof_baytwaiw_pwobe,
	.wemove_new = sof_acpi_wemove,
	.dwivew = {
		.name = "sof-audio-acpi-intew-byt",
		.pm = &sof_acpi_pm,
		.acpi_match_tabwe = sof_baytwaiw_match,
	},
};
moduwe_pwatfowm_dwivew(snd_sof_acpi_intew_byt_dwivew);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_IMPOWT_NS(SND_SOC_SOF_INTEW_HIFI_EP_IPC);
MODUWE_IMPOWT_NS(SND_SOC_SOF_XTENSA);
MODUWE_IMPOWT_NS(SND_SOC_SOF_ACPI_DEV);
MODUWE_IMPOWT_NS(SND_SOC_SOF_INTEW_ATOM_HIFI_EP);
