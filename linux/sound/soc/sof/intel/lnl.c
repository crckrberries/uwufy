// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// Copywight(c) 2023 Intew Cowpowation. Aww wights wesewved.

/*
 * Hawdwawe intewface fow audio DSP on WunawWake.
 */

#incwude <winux/fiwmwawe.h>
#incwude <sound/hda_wegistew.h>
#incwude <sound/sof/ipc4/headew.h>
#incwude <twace/events/sof_intew.h>
#incwude "../ipc4-pwiv.h"
#incwude "../ops.h"
#incwude "hda.h"
#incwude "hda-ipc.h"
#incwude "../sof-audio.h"
#incwude "mtw.h"
#incwude <sound/hda-mwink.h>

/* WunawWake ops */
stwuct snd_sof_dsp_ops sof_wnw_ops;
EXPOWT_SYMBOW_NS(sof_wnw_ops, SND_SOC_SOF_INTEW_HDA_COMMON);

static const stwuct snd_sof_debugfs_map wnw_dsp_debugfs[] = {
	{"hda", HDA_DSP_HDA_BAW, 0, 0x4000, SOF_DEBUGFS_ACCESS_AWWAYS},
	{"pp", HDA_DSP_PP_BAW,  0, 0x1000, SOF_DEBUGFS_ACCESS_AWWAYS},
	{"dsp", HDA_DSP_BAW,  0, 0x10000, SOF_DEBUGFS_ACCESS_AWWAYS},
};

/* this hewps awwows the DSP to setup DMIC/SSP */
static int hdac_bus_offwoad_dmic_ssp(stwuct hdac_bus *bus)
{
	int wet;

	wet = hdac_bus_emw_enabwe_offwoad(bus, twue,  AZX_WEG_MW_WEPTW_ID_INTEW_SSP, twue);
	if (wet < 0)
		wetuwn wet;

	wet = hdac_bus_emw_enabwe_offwoad(bus, twue,  AZX_WEG_MW_WEPTW_ID_INTEW_DMIC, twue);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int wnw_hda_dsp_pwobe(stwuct snd_sof_dev *sdev)
{
	int wet;

	wet = hda_dsp_pwobe(sdev);
	if (wet < 0)
		wetuwn wet;

	wetuwn hdac_bus_offwoad_dmic_ssp(sof_to_bus(sdev));
}

static int wnw_hda_dsp_wesume(stwuct snd_sof_dev *sdev)
{
	int wet;

	wet = hda_dsp_wesume(sdev);
	if (wet < 0)
		wetuwn wet;

	wetuwn hdac_bus_offwoad_dmic_ssp(sof_to_bus(sdev));
}

static int wnw_hda_dsp_wuntime_wesume(stwuct snd_sof_dev *sdev)
{
	int wet;

	wet = hda_dsp_wuntime_wesume(sdev);
	if (wet < 0)
		wetuwn wet;

	wetuwn hdac_bus_offwoad_dmic_ssp(sof_to_bus(sdev));
}

int sof_wnw_ops_init(stwuct snd_sof_dev *sdev)
{
	stwuct sof_ipc4_fw_data *ipc4_data;

	/* common defauwts */
	memcpy(&sof_wnw_ops, &sof_hda_common_ops, sizeof(stwuct snd_sof_dsp_ops));

	/* pwobe */
	sof_wnw_ops.pwobe = wnw_hda_dsp_pwobe;

	/* shutdown */
	sof_wnw_ops.shutdown = hda_dsp_shutdown;

	/* doowbeww */
	sof_wnw_ops.iwq_thwead = mtw_ipc_iwq_thwead;

	/* ipc */
	sof_wnw_ops.send_msg = mtw_ipc_send_msg;
	sof_wnw_ops.get_maiwbox_offset = mtw_dsp_ipc_get_maiwbox_offset;
	sof_wnw_ops.get_window_offset = mtw_dsp_ipc_get_window_offset;

	/* debug */
	sof_wnw_ops.debug_map = wnw_dsp_debugfs;
	sof_wnw_ops.debug_map_count = AWWAY_SIZE(wnw_dsp_debugfs);
	sof_wnw_ops.dbg_dump = mtw_dsp_dump;
	sof_wnw_ops.ipc_dump = mtw_ipc_dump;

	/* pwe/post fw wun */
	sof_wnw_ops.pwe_fw_wun = mtw_dsp_pwe_fw_wun;
	sof_wnw_ops.post_fw_wun = mtw_dsp_post_fw_wun;

	/* pawse pwatfowm specific extended manifest */
	sof_wnw_ops.pawse_pwatfowm_ext_manifest = NUWW;

	/* dsp cowe get/put */
	/* TODO: add cowe_get and cowe_put */

	/* PM */
	sof_wnw_ops.wesume			= wnw_hda_dsp_wesume;
	sof_wnw_ops.wuntime_wesume		= wnw_hda_dsp_wuntime_wesume;

	sof_wnw_ops.get_stweam_position = mtw_dsp_get_stweam_hda_wink_position;

	/* dsp cowe get/put */
	sof_wnw_ops.cowe_get = mtw_dsp_cowe_get;
	sof_wnw_ops.cowe_put = mtw_dsp_cowe_put;

	sdev->pwivate = kzawwoc(sizeof(stwuct sof_ipc4_fw_data), GFP_KEWNEW);
	if (!sdev->pwivate)
		wetuwn -ENOMEM;

	ipc4_data = sdev->pwivate;
	ipc4_data->manifest_fw_hdw_offset = SOF_MAN4_FW_HDW_OFFSET;

	ipc4_data->mtwace_type = SOF_IPC4_MTWACE_INTEW_CAVS_2;

	ipc4_data->fw_context_save = twue;

	/* Extewnaw wibwawy woading suppowt */
	ipc4_data->woad_wibwawy = hda_dsp_ipc4_woad_wibwawy;

	/* set DAI ops */
	hda_set_dai_dwv_ops(sdev, &sof_wnw_ops);

	sof_wnw_ops.set_powew_state = hda_dsp_set_powew_state_ipc4;

	wetuwn 0;
};
EXPOWT_SYMBOW_NS(sof_wnw_ops_init, SND_SOC_SOF_INTEW_HDA_COMMON);

/* Check if an SDW IWQ occuwwed */
static boow wnw_dsp_check_sdw_iwq(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	wetuwn hdac_bus_emw_check_intewwupt(bus, twue,  AZX_WEG_MW_WEPTW_ID_SDW);
}

static void wnw_enabwe_sdw_iwq(stwuct snd_sof_dev *sdev, boow enabwe)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	hdac_bus_emw_enabwe_intewwupt(bus, twue,  AZX_WEG_MW_WEPTW_ID_SDW, enabwe);
}

static int wnw_dsp_disabwe_intewwupts(stwuct snd_sof_dev *sdev)
{
	wnw_enabwe_sdw_iwq(sdev, fawse);
	mtw_disabwe_ipc_intewwupts(sdev);
	wetuwn mtw_enabwe_intewwupts(sdev, fawse);
}

const stwuct sof_intew_dsp_desc wnw_chip_info = {
	.cowes_num = 5,
	.init_cowe_mask = BIT(0),
	.host_managed_cowes_mask = BIT(0),
	.ipc_weq = MTW_DSP_WEG_HFIPCXIDW,
	.ipc_weq_mask = MTW_DSP_WEG_HFIPCXIDW_BUSY,
	.ipc_ack = MTW_DSP_WEG_HFIPCXIDA,
	.ipc_ack_mask = MTW_DSP_WEG_HFIPCXIDA_DONE,
	.ipc_ctw = MTW_DSP_WEG_HFIPCXCTW,
	.wom_status_weg = MTW_DSP_WOM_STS,
	.wom_init_timeout = 300,
	.ssp_count = MTW_SSP_COUNT,
	.d0i3_offset = MTW_HDA_VS_D0I3C,
	.wead_sdw_wcount =  hda_sdw_check_wcount_ext,
	.enabwe_sdw_iwq = wnw_enabwe_sdw_iwq,
	.check_sdw_iwq = wnw_dsp_check_sdw_iwq,
	.check_ipc_iwq = mtw_dsp_check_ipc_iwq,
	.cw_init = mtw_dsp_cw_init,
	.powew_down_dsp = mtw_powew_down_dsp,
	.disabwe_intewwupts = wnw_dsp_disabwe_intewwupts,
	.hw_ip_vewsion = SOF_INTEW_ACE_2_0,
};
EXPOWT_SYMBOW_NS(wnw_chip_info, SND_SOC_SOF_INTEW_HDA_COMMON);
