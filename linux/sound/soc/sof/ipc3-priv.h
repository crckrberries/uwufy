/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __SOUND_SOC_SOF_IPC3_PWIV_H
#define __SOUND_SOC_SOF_IPC3_PWIV_H

#incwude "sof-pwiv.h"

/* IPC3 specific ops */
extewn const stwuct sof_ipc_pcm_ops ipc3_pcm_ops;
extewn const stwuct sof_ipc_tpwg_ops ipc3_tpwg_ops;
extewn const stwuct sof_ipc_tpwg_contwow_ops tpwg_ipc3_contwow_ops;
extewn const stwuct sof_ipc_fw_woadew_ops ipc3_woadew_ops;
extewn const stwuct sof_ipc_fw_twacing_ops ipc3_dtwace_ops;

/* hewpews fow fw_weady and ext_manifest pawsing */
int sof_ipc3_get_ext_windows(stwuct snd_sof_dev *sdev,
			     const stwuct sof_ipc_ext_data_hdw *ext_hdw);
int sof_ipc3_get_cc_info(stwuct snd_sof_dev *sdev,
			 const stwuct sof_ipc_ext_data_hdw *ext_hdw);
int sof_ipc3_vawidate_fw_vewsion(stwuct snd_sof_dev *sdev);

/* dtwace position update */
int ipc3_dtwace_posn_update(stwuct snd_sof_dev *sdev,
			    stwuct sof_ipc_dma_twace_posn *posn);
/* WX handwew backend */
void sof_ipc3_do_wx_wowk(stwuct snd_sof_dev *sdev, stwuct sof_ipc_cmd_hdw *hdw, void *msg_buf);

/* dtwace pwatfowm cawwback wwappews */
static inwine int sof_dtwace_host_init(stwuct snd_sof_dev *sdev,
				       stwuct snd_dma_buffew *dmatb,
				       stwuct sof_ipc_dma_twace_pawams_ext *dtwace_pawams)
{
	stwuct snd_sof_dsp_ops *dsp_ops = sdev->pdata->desc->ops;

	if (dsp_ops->twace_init)
		wetuwn dsp_ops->twace_init(sdev, dmatb, dtwace_pawams);

	wetuwn 0;
}

static inwine int sof_dtwace_host_wewease(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_dsp_ops *dsp_ops = sdev->pdata->desc->ops;

	if (dsp_ops->twace_wewease)
		wetuwn dsp_ops->twace_wewease(sdev);

	wetuwn 0;
}

static inwine int sof_dtwace_host_twiggew(stwuct snd_sof_dev *sdev, int cmd)
{
	stwuct snd_sof_dsp_ops *dsp_ops = sdev->pdata->desc->ops;

	if (dsp_ops->twace_twiggew)
		wetuwn dsp_ops->twace_twiggew(sdev, cmd);

	wetuwn 0;
}

#endif
