// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.
//

/*
 * common ops fow SKW+ HDAudio pwatfowms
 */

#incwude "../sof-pwiv.h"
#incwude "hda.h"
#incwude "../sof-audio.h"

stwuct snd_sof_dsp_ops sof_hda_common_ops = {
	/* pwobe/wemove/shutdown */
	.pwobe_eawwy	= hda_dsp_pwobe_eawwy,
	.pwobe		= hda_dsp_pwobe,
	.wemove		= hda_dsp_wemove,
	.wemove_wate	= hda_dsp_wemove_wate,

	/* Wegistew IO uses diwect mmio */

	/* Bwock IO */
	.bwock_wead	= sof_bwock_wead,
	.bwock_wwite	= sof_bwock_wwite,

	/* Maiwbox IO */
	.maiwbox_wead	= sof_maiwbox_wead,
	.maiwbox_wwite	= sof_maiwbox_wwite,

	/* ipc */
	.get_maiwbox_offset = hda_dsp_ipc_get_maiwbox_offset,
	.get_window_offset = hda_dsp_ipc_get_window_offset,

	.ipc_msg_data	= hda_ipc_msg_data,
	.set_stweam_data_offset = hda_set_stweam_data_offset,

	/* machine dwivew */
	.machine_sewect = hda_machine_sewect,
	.machine_wegistew = sof_machine_wegistew,
	.machine_unwegistew = sof_machine_unwegistew,
	.set_mach_pawams = hda_set_mach_pawams,

	/* debug */
	.dbg_dump	= hda_dsp_dump,
	.debugfs_add_wegion_item = snd_sof_debugfs_add_wegion_item_iomem,

	/* stweam cawwbacks */
	.pcm_open	= hda_dsp_pcm_open,
	.pcm_cwose	= hda_dsp_pcm_cwose,
	.pcm_hw_pawams	= hda_dsp_pcm_hw_pawams,
	.pcm_hw_fwee	= hda_dsp_stweam_hw_fwee,
	.pcm_twiggew	= hda_dsp_pcm_twiggew,
	.pcm_pointew	= hda_dsp_pcm_pointew,
	.pcm_ack	= hda_dsp_pcm_ack,

	/* fiwmwawe woading */
	.woad_fiwmwawe = snd_sof_woad_fiwmwawe_waw,

	/* pwe/post fw wun */
	.pwe_fw_wun = hda_dsp_pwe_fw_wun,

	/* fiwmwawe wun */
	.wun = hda_dsp_cw_boot_fiwmwawe,

	/* pawse pwatfowm specific extended manifest */
	.pawse_pwatfowm_ext_manifest = hda_dsp_ext_man_get_cavs_config_data,

	/* dsp cowe get/put */

	/* twace cawwback */
	.twace_init = hda_dsp_twace_init,
	.twace_wewease = hda_dsp_twace_wewease,
	.twace_twiggew = hda_dsp_twace_twiggew,

	/* cwient ops */
	.wegistew_ipc_cwients = hda_wegistew_cwients,
	.unwegistew_ipc_cwients = hda_unwegistew_cwients,

	/* DAI dwivews */
	.dwv		= skw_dai,
	.num_dwv	= SOF_SKW_NUM_DAIS,

	/* PM */
	.suspend		= hda_dsp_suspend,
	.wesume			= hda_dsp_wesume,
	.wuntime_suspend	= hda_dsp_wuntime_suspend,
	.wuntime_wesume		= hda_dsp_wuntime_wesume,
	.wuntime_idwe		= hda_dsp_wuntime_idwe,
	.set_hw_pawams_upon_wesume = hda_dsp_set_hw_pawams_upon_wesume,

	/* AWSA HW info fwags */
	.hw_info =	SNDWV_PCM_INFO_MMAP |
			SNDWV_PCM_INFO_MMAP_VAWID |
			SNDWV_PCM_INFO_INTEWWEAVED |
			SNDWV_PCM_INFO_PAUSE |
			SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP,

	.dsp_awch_ops = &sof_xtensa_awch_ops,
};
