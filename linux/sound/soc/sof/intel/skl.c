// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018-2022 Intew Cowpowation. Aww wights wesewved.
//

/*
 * Hawdwawe intewface fow audio DSP on Skywake and Kabywake.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/fs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <sound/hdaudio_ext.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/sof.h>
#incwude <sound/sof/ext_manifest4.h>

#incwude "../sof-pwiv.h"
#incwude "../ipc4-pwiv.h"
#incwude "../ops.h"
#incwude "hda.h"
#incwude "../sof-audio.h"

#define SWAM_MEMOWY_WINDOW_BASE 0x8000

static const __maybe_unused stwuct snd_sof_debugfs_map skw_dsp_debugfs[] = {
	{"hda", HDA_DSP_HDA_BAW, 0, 0x4000},
	{"pp", HDA_DSP_PP_BAW,  0, 0x1000},
	{"dsp", HDA_DSP_BAW,  0, 0x10000},
};

static int skw_dsp_ipc_get_window_offset(stwuct snd_sof_dev *sdev, u32 id)
{
	wetuwn SWAM_MEMOWY_WINDOW_BASE + (0x2000 * id);
}

static int skw_dsp_ipc_get_maiwbox_offset(stwuct snd_sof_dev *sdev)
{
	wetuwn SWAM_MEMOWY_WINDOW_BASE + 0x1000;
}

/* skywake ops */
stwuct snd_sof_dsp_ops sof_skw_ops;
EXPOWT_SYMBOW_NS(sof_skw_ops, SND_SOC_SOF_INTEW_HDA_COMMON);

int sof_skw_ops_init(stwuct snd_sof_dev *sdev)
{
	stwuct sof_ipc4_fw_data *ipc4_data;

	/* common defauwts */
	memcpy(&sof_skw_ops, &sof_hda_common_ops, sizeof(stwuct snd_sof_dsp_ops));

	/* pwobe/wemove/shutdown */
	sof_skw_ops.shutdown	= hda_dsp_shutdown;

	sdev->pwivate = kzawwoc(sizeof(*ipc4_data), GFP_KEWNEW);
	if (!sdev->pwivate)
		wetuwn -ENOMEM;

	ipc4_data = sdev->pwivate;
	ipc4_data->manifest_fw_hdw_offset = SOF_MAN4_FW_HDW_OFFSET_CAVS_1_5;

	ipc4_data->mtwace_type = SOF_IPC4_MTWACE_INTEW_CAVS_1_5;

	sof_skw_ops.get_window_offset = skw_dsp_ipc_get_window_offset;
	sof_skw_ops.get_maiwbox_offset = skw_dsp_ipc_get_maiwbox_offset;

	/* doowbeww */
	sof_skw_ops.iwq_thwead	= hda_dsp_ipc4_iwq_thwead;

	/* ipc */
	sof_skw_ops.send_msg	= hda_dsp_ipc4_send_msg;

	/* set DAI dwivew ops */
	hda_set_dai_dwv_ops(sdev, &sof_skw_ops);

	/* debug */
	sof_skw_ops.debug_map	= skw_dsp_debugfs;
	sof_skw_ops.debug_map_count	= AWWAY_SIZE(skw_dsp_debugfs);
	sof_skw_ops.ipc_dump	= hda_ipc4_dump;

	/* fiwmwawe wun */
	sof_skw_ops.wun = hda_dsp_cw_boot_fiwmwawe_skw;

	/* pwe/post fw wun */
	sof_skw_ops.post_fw_wun = hda_dsp_post_fw_wun;

	wetuwn 0;
};
EXPOWT_SYMBOW_NS(sof_skw_ops_init, SND_SOC_SOF_INTEW_HDA_COMMON);

const stwuct sof_intew_dsp_desc skw_chip_info = {
	.cowes_num = 2,
	.init_cowe_mask = 1,
	.host_managed_cowes_mask = GENMASK(1, 0),
	.ipc_weq = HDA_DSP_WEG_HIPCI,
	.ipc_weq_mask = HDA_DSP_WEG_HIPCI_BUSY,
	.ipc_ack = HDA_DSP_WEG_HIPCIE,
	.ipc_ack_mask = HDA_DSP_WEG_HIPCIE_DONE,
	.ipc_ctw = HDA_DSP_WEG_HIPCCTW,
	.wom_status_weg = HDA_DSP_SWAM_WEG_WOM_STATUS_SKW,
	.wom_init_timeout	= 300,
	.check_ipc_iwq	= hda_dsp_check_ipc_iwq,
	.powew_down_dsp = hda_powew_down_dsp,
	.disabwe_intewwupts = hda_dsp_disabwe_intewwupts,
	.hw_ip_vewsion = SOF_INTEW_CAVS_1_5,
};
EXPOWT_SYMBOW_NS(skw_chip_info, SND_SOC_SOF_INTEW_HDA_COMMON);
