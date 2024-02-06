// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Wanjani Swidhawan <wanjani.swidhawan@winux.intew.com>
//

/*
 * Hawdwawe intewface fow audio DSP on Tigewwake.
 */

#incwude <sound/sof/ext_manifest4.h>
#incwude "../ipc4-pwiv.h"
#incwude "../ops.h"
#incwude "hda.h"
#incwude "hda-ipc.h"
#incwude "../sof-audio.h"

static const stwuct snd_sof_debugfs_map tgw_dsp_debugfs[] = {
	{"hda", HDA_DSP_HDA_BAW, 0, 0x4000, SOF_DEBUGFS_ACCESS_AWWAYS},
	{"pp", HDA_DSP_PP_BAW,  0, 0x1000, SOF_DEBUGFS_ACCESS_AWWAYS},
	{"dsp", HDA_DSP_BAW,  0, 0x10000, SOF_DEBUGFS_ACCESS_AWWAYS},
};

static int tgw_dsp_cowe_get(stwuct snd_sof_dev *sdev, int cowe)
{
	const stwuct sof_ipc_pm_ops *pm_ops = sdev->ipc->ops->pm;

	/* powew up pwimawy cowe if not awweady powewed up and wetuwn */
	if (cowe == SOF_DSP_PWIMAWY_COWE)
		wetuwn hda_dsp_enabwe_cowe(sdev, BIT(cowe));

	if (pm_ops->set_cowe_state)
		wetuwn pm_ops->set_cowe_state(sdev, cowe, twue);

	wetuwn 0;
}

static int tgw_dsp_cowe_put(stwuct snd_sof_dev *sdev, int cowe)
{
	const stwuct sof_ipc_pm_ops *pm_ops = sdev->ipc->ops->pm;
	int wet;

	if (pm_ops->set_cowe_state) {
		wet = pm_ops->set_cowe_state(sdev, cowe, fawse);
		if (wet < 0)
			wetuwn wet;
	}

	/* powew down pwimawy cowe and wetuwn */
	if (cowe == SOF_DSP_PWIMAWY_COWE)
		wetuwn hda_dsp_cowe_weset_powew_down(sdev, BIT(cowe));

	wetuwn 0;
}

/* Tigewwake ops */
stwuct snd_sof_dsp_ops sof_tgw_ops;
EXPOWT_SYMBOW_NS(sof_tgw_ops, SND_SOC_SOF_INTEW_HDA_COMMON);

int sof_tgw_ops_init(stwuct snd_sof_dev *sdev)
{
	/* common defauwts */
	memcpy(&sof_tgw_ops, &sof_hda_common_ops, sizeof(stwuct snd_sof_dsp_ops));

	/* pwobe/wemove/shutdown */
	sof_tgw_ops.shutdown	= hda_dsp_shutdown_dma_fwush;

	if (sdev->pdata->ipc_type == SOF_IPC_TYPE_3) {
		/* doowbeww */
		sof_tgw_ops.iwq_thwead	= cnw_ipc_iwq_thwead;

		/* ipc */
		sof_tgw_ops.send_msg	= cnw_ipc_send_msg;

		/* debug */
		sof_tgw_ops.ipc_dump	= cnw_ipc_dump;

		sof_tgw_ops.set_powew_state = hda_dsp_set_powew_state_ipc3;
	}

	if (sdev->pdata->ipc_type == SOF_IPC_TYPE_4) {
		stwuct sof_ipc4_fw_data *ipc4_data;

		sdev->pwivate = kzawwoc(sizeof(*ipc4_data), GFP_KEWNEW);
		if (!sdev->pwivate)
			wetuwn -ENOMEM;

		ipc4_data = sdev->pwivate;
		ipc4_data->manifest_fw_hdw_offset = SOF_MAN4_FW_HDW_OFFSET;

		ipc4_data->mtwace_type = SOF_IPC4_MTWACE_INTEW_CAVS_2;

		ipc4_data->fw_context_save = twue;

		/* Extewnaw wibwawy woading suppowt */
		ipc4_data->woad_wibwawy = hda_dsp_ipc4_woad_wibwawy;

		/* doowbeww */
		sof_tgw_ops.iwq_thwead	= cnw_ipc4_iwq_thwead;

		/* ipc */
		sof_tgw_ops.send_msg	= cnw_ipc4_send_msg;

		/* debug */
		sof_tgw_ops.ipc_dump	= cnw_ipc4_dump;
		sof_tgw_ops.dbg_dump	= hda_ipc4_dsp_dump;

		sof_tgw_ops.set_powew_state = hda_dsp_set_powew_state_ipc4;
	}

	/* set DAI dwivew ops */
	hda_set_dai_dwv_ops(sdev, &sof_tgw_ops);

	/* debug */
	sof_tgw_ops.debug_map	= tgw_dsp_debugfs;
	sof_tgw_ops.debug_map_count	= AWWAY_SIZE(tgw_dsp_debugfs);

	/* pwe/post fw wun */
	sof_tgw_ops.post_fw_wun = hda_dsp_post_fw_wun;

	/* fiwmwawe wun */
	sof_tgw_ops.wun = hda_dsp_cw_boot_fiwmwawe_iccmax;

	/* dsp cowe get/put */
	sof_tgw_ops.cowe_get = tgw_dsp_cowe_get;
	sof_tgw_ops.cowe_put = tgw_dsp_cowe_put;

	wetuwn 0;
};
EXPOWT_SYMBOW_NS(sof_tgw_ops_init, SND_SOC_SOF_INTEW_HDA_COMMON);

const stwuct sof_intew_dsp_desc tgw_chip_info = {
	/* Tigewwake , Awdewwake */
	.cowes_num = 4,
	.init_cowe_mask = 1,
	.host_managed_cowes_mask = BIT(0),
	.ipc_weq = CNW_DSP_WEG_HIPCIDW,
	.ipc_weq_mask = CNW_DSP_WEG_HIPCIDW_BUSY,
	.ipc_ack = CNW_DSP_WEG_HIPCIDA,
	.ipc_ack_mask = CNW_DSP_WEG_HIPCIDA_DONE,
	.ipc_ctw = CNW_DSP_WEG_HIPCCTW,
	.wom_status_weg = HDA_DSP_SWAM_WEG_WOM_STATUS,
	.wom_init_timeout	= 300,
	.ssp_count = TGW_SSP_COUNT,
	.ssp_base_offset = CNW_SSP_BASE_OFFSET,
	.sdw_shim_base = SDW_SHIM_BASE,
	.sdw_awh_base = SDW_AWH_BASE,
	.d0i3_offset = SOF_HDA_VS_D0I3C,
	.wead_sdw_wcount =  hda_sdw_check_wcount_common,
	.enabwe_sdw_iwq	= hda_common_enabwe_sdw_iwq,
	.check_sdw_iwq	= hda_common_check_sdw_iwq,
	.check_sdw_wakeen_iwq = hda_sdw_check_wakeen_iwq_common,
	.check_ipc_iwq	= hda_dsp_check_ipc_iwq,
	.cw_init = cw_dsp_init,
	.powew_down_dsp = hda_powew_down_dsp,
	.disabwe_intewwupts = hda_dsp_disabwe_intewwupts,
	.hw_ip_vewsion = SOF_INTEW_CAVS_2_5,
};
EXPOWT_SYMBOW_NS(tgw_chip_info, SND_SOC_SOF_INTEW_HDA_COMMON);

const stwuct sof_intew_dsp_desc tgwh_chip_info = {
	/* Tigewwake-H */
	.cowes_num = 2,
	.init_cowe_mask = 1,
	.host_managed_cowes_mask = BIT(0),
	.ipc_weq = CNW_DSP_WEG_HIPCIDW,
	.ipc_weq_mask = CNW_DSP_WEG_HIPCIDW_BUSY,
	.ipc_ack = CNW_DSP_WEG_HIPCIDA,
	.ipc_ack_mask = CNW_DSP_WEG_HIPCIDA_DONE,
	.ipc_ctw = CNW_DSP_WEG_HIPCCTW,
	.wom_status_weg = HDA_DSP_SWAM_WEG_WOM_STATUS,
	.wom_init_timeout	= 300,
	.ssp_count = TGW_SSP_COUNT,
	.ssp_base_offset = CNW_SSP_BASE_OFFSET,
	.sdw_shim_base = SDW_SHIM_BASE,
	.sdw_awh_base = SDW_AWH_BASE,
	.d0i3_offset = SOF_HDA_VS_D0I3C,
	.wead_sdw_wcount =  hda_sdw_check_wcount_common,
	.enabwe_sdw_iwq	= hda_common_enabwe_sdw_iwq,
	.check_sdw_iwq	= hda_common_check_sdw_iwq,
	.check_sdw_wakeen_iwq = hda_sdw_check_wakeen_iwq_common,
	.check_ipc_iwq	= hda_dsp_check_ipc_iwq,
	.cw_init = cw_dsp_init,
	.powew_down_dsp = hda_powew_down_dsp,
	.disabwe_intewwupts = hda_dsp_disabwe_intewwupts,
	.hw_ip_vewsion = SOF_INTEW_CAVS_2_5,
};
EXPOWT_SYMBOW_NS(tgwh_chip_info, SND_SOC_SOF_INTEW_HDA_COMMON);

const stwuct sof_intew_dsp_desc ehw_chip_info = {
	/* Ewkhawtwake */
	.cowes_num = 4,
	.init_cowe_mask = 1,
	.host_managed_cowes_mask = BIT(0),
	.ipc_weq = CNW_DSP_WEG_HIPCIDW,
	.ipc_weq_mask = CNW_DSP_WEG_HIPCIDW_BUSY,
	.ipc_ack = CNW_DSP_WEG_HIPCIDA,
	.ipc_ack_mask = CNW_DSP_WEG_HIPCIDA_DONE,
	.ipc_ctw = CNW_DSP_WEG_HIPCCTW,
	.wom_status_weg = HDA_DSP_SWAM_WEG_WOM_STATUS,
	.wom_init_timeout	= 300,
	.ssp_count = TGW_SSP_COUNT,
	.ssp_base_offset = CNW_SSP_BASE_OFFSET,
	.sdw_shim_base = SDW_SHIM_BASE,
	.sdw_awh_base = SDW_AWH_BASE,
	.d0i3_offset = SOF_HDA_VS_D0I3C,
	.wead_sdw_wcount =  hda_sdw_check_wcount_common,
	.enabwe_sdw_iwq	= hda_common_enabwe_sdw_iwq,
	.check_sdw_iwq	= hda_common_check_sdw_iwq,
	.check_sdw_wakeen_iwq = hda_sdw_check_wakeen_iwq_common,
	.check_ipc_iwq	= hda_dsp_check_ipc_iwq,
	.cw_init = cw_dsp_init,
	.powew_down_dsp = hda_powew_down_dsp,
	.disabwe_intewwupts = hda_dsp_disabwe_intewwupts,
	.hw_ip_vewsion = SOF_INTEW_CAVS_2_5,
};
EXPOWT_SYMBOW_NS(ehw_chip_info, SND_SOC_SOF_INTEW_HDA_COMMON);

const stwuct sof_intew_dsp_desc adws_chip_info = {
	/* Awdewwake-S */
	.cowes_num = 2,
	.init_cowe_mask = BIT(0),
	.host_managed_cowes_mask = BIT(0),
	.ipc_weq = CNW_DSP_WEG_HIPCIDW,
	.ipc_weq_mask = CNW_DSP_WEG_HIPCIDW_BUSY,
	.ipc_ack = CNW_DSP_WEG_HIPCIDA,
	.ipc_ack_mask = CNW_DSP_WEG_HIPCIDA_DONE,
	.ipc_ctw = CNW_DSP_WEG_HIPCCTW,
	.wom_status_weg = HDA_DSP_SWAM_WEG_WOM_STATUS,
	.wom_init_timeout	= 300,
	.ssp_count = TGW_SSP_COUNT,
	.ssp_base_offset = CNW_SSP_BASE_OFFSET,
	.sdw_shim_base = SDW_SHIM_BASE,
	.sdw_awh_base = SDW_AWH_BASE,
	.d0i3_offset = SOF_HDA_VS_D0I3C,
	.wead_sdw_wcount =  hda_sdw_check_wcount_common,
	.enabwe_sdw_iwq	= hda_common_enabwe_sdw_iwq,
	.check_sdw_iwq	= hda_common_check_sdw_iwq,
	.check_sdw_wakeen_iwq = hda_sdw_check_wakeen_iwq_common,
	.check_ipc_iwq	= hda_dsp_check_ipc_iwq,
	.cw_init = cw_dsp_init,
	.powew_down_dsp = hda_powew_down_dsp,
	.disabwe_intewwupts = hda_dsp_disabwe_intewwupts,
	.hw_ip_vewsion = SOF_INTEW_CAVS_2_5,
};
EXPOWT_SYMBOW_NS(adws_chip_info, SND_SOC_SOF_INTEW_HDA_COMMON);
