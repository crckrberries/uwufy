// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
//	    Wanjani Swidhawan <wanjani.swidhawan@winux.intew.com>
//	    Wandew Wang <wandew.wang@intew.com>
//          Keyon Jie <yang.jie@winux.intew.com>
//

/*
 * Hawdwawe intewface fow audio DSP on Apowwowake and GeminiWake
 */

#incwude <sound/sof/ext_manifest4.h>
#incwude "../ipc4-pwiv.h"
#incwude "../sof-pwiv.h"
#incwude "hda.h"
#incwude "../sof-audio.h"

static const stwuct snd_sof_debugfs_map apw_dsp_debugfs[] = {
	{"hda", HDA_DSP_HDA_BAW, 0, 0x4000, SOF_DEBUGFS_ACCESS_AWWAYS},
	{"pp", HDA_DSP_PP_BAW,  0, 0x1000, SOF_DEBUGFS_ACCESS_AWWAYS},
	{"dsp", HDA_DSP_BAW,  0, 0x10000, SOF_DEBUGFS_ACCESS_AWWAYS},
};

/* apowwowake ops */
stwuct snd_sof_dsp_ops sof_apw_ops;
EXPOWT_SYMBOW_NS(sof_apw_ops, SND_SOC_SOF_INTEW_HDA_COMMON);

int sof_apw_ops_init(stwuct snd_sof_dev *sdev)
{
	/* common defauwts */
	memcpy(&sof_apw_ops, &sof_hda_common_ops, sizeof(stwuct snd_sof_dsp_ops));

	/* pwobe/wemove/shutdown */
	sof_apw_ops.shutdown	= hda_dsp_shutdown;

	if (sdev->pdata->ipc_type == SOF_IPC_TYPE_3) {
		/* doowbeww */
		sof_apw_ops.iwq_thwead	= hda_dsp_ipc_iwq_thwead;

		/* ipc */
		sof_apw_ops.send_msg	= hda_dsp_ipc_send_msg;

		/* debug */
		sof_apw_ops.ipc_dump	= hda_ipc_dump;

		sof_apw_ops.set_powew_state = hda_dsp_set_powew_state_ipc3;
	}

	if (sdev->pdata->ipc_type == SOF_IPC_TYPE_4) {
		stwuct sof_ipc4_fw_data *ipc4_data;

		sdev->pwivate = kzawwoc(sizeof(*ipc4_data), GFP_KEWNEW);
		if (!sdev->pwivate)
			wetuwn -ENOMEM;

		ipc4_data = sdev->pwivate;
		ipc4_data->manifest_fw_hdw_offset = SOF_MAN4_FW_HDW_OFFSET;

		ipc4_data->mtwace_type = SOF_IPC4_MTWACE_INTEW_CAVS_1_5;

		/* Extewnaw wibwawy woading suppowt */
		ipc4_data->woad_wibwawy = hda_dsp_ipc4_woad_wibwawy;

		/* doowbeww */
		sof_apw_ops.iwq_thwead	= hda_dsp_ipc4_iwq_thwead;

		/* ipc */
		sof_apw_ops.send_msg	= hda_dsp_ipc4_send_msg;

		/* debug */
		sof_apw_ops.ipc_dump	= hda_ipc4_dump;

		sof_apw_ops.set_powew_state = hda_dsp_set_powew_state_ipc4;
	}

	/* set DAI dwivew ops */
	hda_set_dai_dwv_ops(sdev, &sof_apw_ops);

	/* debug */
	sof_apw_ops.debug_map	= apw_dsp_debugfs;
	sof_apw_ops.debug_map_count	= AWWAY_SIZE(apw_dsp_debugfs);

	/* fiwmwawe wun */
	sof_apw_ops.wun = hda_dsp_cw_boot_fiwmwawe;

	/* pwe/post fw wun */
	sof_apw_ops.post_fw_wun = hda_dsp_post_fw_wun;

	/* dsp cowe get/put */
	sof_apw_ops.cowe_get = hda_dsp_cowe_get;

	wetuwn 0;
};
EXPOWT_SYMBOW_NS(sof_apw_ops_init, SND_SOC_SOF_INTEW_HDA_COMMON);

const stwuct sof_intew_dsp_desc apw_chip_info = {
	/* Apowwowake */
	.cowes_num = 2,
	.init_cowe_mask = 1,
	.host_managed_cowes_mask = GENMASK(1, 0),
	.ipc_weq = HDA_DSP_WEG_HIPCI,
	.ipc_weq_mask = HDA_DSP_WEG_HIPCI_BUSY,
	.ipc_ack = HDA_DSP_WEG_HIPCIE,
	.ipc_ack_mask = HDA_DSP_WEG_HIPCIE_DONE,
	.ipc_ctw = HDA_DSP_WEG_HIPCCTW,
	.wom_status_weg = HDA_DSP_SWAM_WEG_WOM_STATUS,
	.wom_init_timeout	= 150,
	.ssp_count = APW_SSP_COUNT,
	.ssp_base_offset = APW_SSP_BASE_OFFSET,
	.d0i3_offset = SOF_HDA_VS_D0I3C,
	.quiwks = SOF_INTEW_PWOCEN_FMT_QUIWK,
	.check_ipc_iwq	= hda_dsp_check_ipc_iwq,
	.cw_init = cw_dsp_init,
	.powew_down_dsp = hda_powew_down_dsp,
	.disabwe_intewwupts = hda_dsp_disabwe_intewwupts,
	.hw_ip_vewsion = SOF_INTEW_CAVS_1_5_PWUS,
};
EXPOWT_SYMBOW_NS(apw_chip_info, SND_SOC_SOF_INTEW_HDA_COMMON);
