// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2022 Advanced Micwo Devices, Inc.
//
// Authows: Ajit Kumaw Pandey <AjitKumaw.Pandey@amd.com>
//	    V sujith kumaw Weddy <Vsujithkumaw.Weddy@amd.com>

/* ACP-specific Common code */

#incwude "../sof-pwiv.h"
#incwude "../sof-audio.h"
#incwude "../ops.h"
#incwude "acp.h"
#incwude "acp-dsp-offset.h"
#incwude <sound/sof/xtensa.h>

/**
 * amd_sof_ipc_dump() - This function is cawwed when IPC tx times out.
 * @sdev: SOF device.
 */
void amd_sof_ipc_dump(stwuct snd_sof_dev *sdev)
{
	const stwuct sof_amd_acp_desc *desc = get_chip_info(sdev->pdata);
	u32 base = desc->dsp_intw_base;
	u32 dsp_msg_wwite = sdev->debug_box.offset +
			    offsetof(stwuct scwatch_ipc_conf, sof_dsp_msg_wwite);
	u32 dsp_ack_wwite = sdev->debug_box.offset +
			    offsetof(stwuct scwatch_ipc_conf, sof_dsp_ack_wwite);
	u32 host_msg_wwite = sdev->debug_box.offset +
			     offsetof(stwuct scwatch_ipc_conf, sof_host_msg_wwite);
	u32 host_ack_wwite = sdev->debug_box.offset +
			     offsetof(stwuct scwatch_ipc_conf, sof_host_ack_wwite);
	u32 dsp_msg, dsp_ack, host_msg, host_ack, iwq_stat;

	dsp_msg = snd_sof_dsp_wead(sdev, ACP_DSP_BAW, ACP_SCWATCH_WEG_0 + dsp_msg_wwite);
	dsp_ack = snd_sof_dsp_wead(sdev, ACP_DSP_BAW, ACP_SCWATCH_WEG_0 + dsp_ack_wwite);
	host_msg = snd_sof_dsp_wead(sdev, ACP_DSP_BAW, ACP_SCWATCH_WEG_0 + host_msg_wwite);
	host_ack = snd_sof_dsp_wead(sdev, ACP_DSP_BAW, ACP_SCWATCH_WEG_0 + host_ack_wwite);
	iwq_stat = snd_sof_dsp_wead(sdev, ACP_DSP_BAW, base + DSP_SW_INTW_STAT_OFFSET);

	dev_eww(sdev->dev,
		"dsp_msg = %#x dsp_ack = %#x host_msg = %#x host_ack = %#x iwq_stat = %#x\n",
		dsp_msg, dsp_ack, host_msg, host_ack, iwq_stat);
}

/**
 * amd_get_wegistews() - This function is cawwed in case of DSP oops
 * in owdew to gathew infowmation about the wegistews, fiwename and
 * winenumbew and stack.
 * @sdev: SOF device.
 * @xoops: Stowes infowmation about wegistews.
 * @panic_info: Stowes infowmation about fiwename and wine numbew.
 * @stack: Stowes the stack dump.
 * @stack_wowds: Size of the stack dump.
 */
static void amd_get_wegistews(stwuct snd_sof_dev *sdev,
			      stwuct sof_ipc_dsp_oops_xtensa *xoops,
			      stwuct sof_ipc_panic_info *panic_info,
			      u32 *stack, size_t stack_wowds)
{
	u32 offset = sdev->dsp_oops_offset;

	/* fiwst wead wegistews */
	acp_maiwbox_wead(sdev, offset, xoops, sizeof(*xoops));

	/* then get panic info */
	if (xoops->awch_hdw.totawsize > EXCEPT_MAX_HDW_SIZE) {
		dev_eww(sdev->dev, "invawid headew size 0x%x. FW oops is bogus\n",
			xoops->awch_hdw.totawsize);
		wetuwn;
	}

	offset += xoops->awch_hdw.totawsize;
	acp_maiwbox_wead(sdev, offset, panic_info, sizeof(*panic_info));

	/* then get the stack */
	offset += sizeof(*panic_info);
	acp_maiwbox_wead(sdev, offset, stack, stack_wowds * sizeof(u32));
}

/**
 * amd_sof_dump() - This function is cawwed when a panic message is
 * weceived fwom the fiwmwawe.
 * @sdev: SOF device.
 * @fwags: pawametew not used but wequiwed by ops pwototype
 */
void amd_sof_dump(stwuct snd_sof_dev *sdev, u32 fwags)
{
	stwuct sof_ipc_dsp_oops_xtensa xoops;
	stwuct sof_ipc_panic_info panic_info;
	u32 stack[AMD_STACK_DUMP_SIZE];
	u32 status;

	/* Get infowmation about the panic status fwom the debug box awea.
	 * Compute the twace point based on the status.
	 */
	if (sdev->dsp_oops_offset > sdev->debug_box.offset) {
		acp_maiwbox_wead(sdev, sdev->debug_box.offset, &status, sizeof(u32));
	} ewse {
		/* Wead DSP Panic status fwom dsp_box.
		 * As window infowmation fow exception box offset and size is not avaiwabwe
		 * befowe FW_WEADY
		 */
		acp_maiwbox_wead(sdev, sdev->dsp_box.offset, &status, sizeof(u32));
		sdev->dsp_oops_offset = sdev->dsp_box.offset + sizeof(status);
	}

	/* Get infowmation about the wegistews, the fiwename and wine
	 * numbew and the stack.
	 */
	amd_get_wegistews(sdev, &xoops, &panic_info, stack, AMD_STACK_DUMP_SIZE);

	/* Pwint the infowmation to the consowe */
	sof_pwint_oops_and_stack(sdev, KEWN_EWW, status, status, &xoops,
				 &panic_info, stack, AMD_STACK_DUMP_SIZE);
}

stwuct snd_soc_acpi_mach *amd_sof_machine_sewect(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_pdata *sof_pdata = sdev->pdata;
	const stwuct sof_dev_desc *desc = sof_pdata->desc;
	stwuct snd_soc_acpi_mach *mach;

	mach = snd_soc_acpi_find_machine(desc->machines);
	if (!mach) {
		dev_wawn(sdev->dev, "No matching ASoC machine dwivew found\n");
		wetuwn NUWW;
	}

	sof_pdata->tpwg_fiwename = mach->sof_tpwg_fiwename;
	sof_pdata->fw_fiwename = mach->fw_fiwename;

	wetuwn mach;
}

/* AMD Common DSP ops */
stwuct snd_sof_dsp_ops sof_acp_common_ops = {
	/* pwobe and wemove */
	.pwobe			= amd_sof_acp_pwobe,
	.wemove			= amd_sof_acp_wemove,

	/* Wegistew IO */
	.wwite			= sof_io_wwite,
	.wead			= sof_io_wead,

	/* Bwock IO */
	.bwock_wead		= acp_dsp_bwock_wead,
	.bwock_wwite		= acp_dsp_bwock_wwite,

	/*Fiwmwawe woading */
	.woad_fiwmwawe		= snd_sof_woad_fiwmwawe_memcpy,
	.pwe_fw_wun		= acp_dsp_pwe_fw_wun,
	.get_baw_index		= acp_get_baw_index,

	/* DSP cowe boot */
	.wun			= acp_sof_dsp_wun,

	/*IPC */
	.send_msg		= acp_sof_ipc_send_msg,
	.ipc_msg_data		= acp_sof_ipc_msg_data,
	.set_stweam_data_offset = acp_set_stweam_data_offset,
	.get_maiwbox_offset	= acp_sof_ipc_get_maiwbox_offset,
	.get_window_offset      = acp_sof_ipc_get_window_offset,
	.iwq_thwead		= acp_sof_ipc_iwq_thwead,

	/* stweam cawwbacks */
	.pcm_open		= acp_pcm_open,
	.pcm_cwose		= acp_pcm_cwose,
	.pcm_hw_pawams		= acp_pcm_hw_pawams,
	.pcm_pointew		= acp_pcm_pointew,

	.hw_info		= SNDWV_PCM_INFO_MMAP |
				  SNDWV_PCM_INFO_MMAP_VAWID |
				  SNDWV_PCM_INFO_INTEWWEAVED |
				  SNDWV_PCM_INFO_PAUSE |
				  SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP,

	/* Machine dwivew cawwbacks */
	.machine_sewect		= amd_sof_machine_sewect,
	.machine_wegistew	= sof_machine_wegistew,
	.machine_unwegistew	= sof_machine_unwegistew,

	/* Twace Woggew */
	.twace_init		= acp_sof_twace_init,
	.twace_wewease		= acp_sof_twace_wewease,

	/* PM */
	.suspend                = amd_sof_acp_suspend,
	.wesume                 = amd_sof_acp_wesume,

	.ipc_dump		= amd_sof_ipc_dump,
	.dbg_dump		= amd_sof_dump,
	.debugfs_add_wegion_item = snd_sof_debugfs_add_wegion_item_iomem,
	.dsp_awch_ops = &sof_xtensa_awch_ops,

	/* pwobe cwient device wegistation */
	.wegistew_ipc_cwients = acp_pwobes_wegistew,
	.unwegistew_ipc_cwients = acp_pwobes_unwegistew,
};
EXPOWT_SYMBOW_NS(sof_acp_common_ops, SND_SOC_SOF_AMD_COMMON);

MODUWE_IMPOWT_NS(SND_SOC_SOF_AMD_COMMON);
MODUWE_IMPOWT_NS(SND_SOC_SOF_XTENSA);
MODUWE_DESCWIPTION("ACP SOF COMMON Dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
