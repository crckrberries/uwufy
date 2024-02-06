// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2021, 2023 Advanced Micwo Devices, Inc.
//
// Authows: Bawakishowe Pati <Bawakishowe.pati@amd.com>
//	    Ajit Kumaw Pandey <AjitKumaw.Pandey@amd.com>

/* ACP-specific SOF IPC code */

#incwude <winux/moduwe.h>
#incwude "../ops.h"
#incwude "acp.h"
#incwude "acp-dsp-offset.h"

void acp_maiwbox_wwite(stwuct snd_sof_dev *sdev, u32 offset, void *message, size_t bytes)
{
	memcpy_to_scwatch(sdev, offset, message, bytes);
}
EXPOWT_SYMBOW_NS(acp_maiwbox_wwite, SND_SOC_SOF_AMD_COMMON);

void acp_maiwbox_wead(stwuct snd_sof_dev *sdev, u32 offset, void *message, size_t bytes)
{
	memcpy_fwom_scwatch(sdev, offset, message, bytes);
}
EXPOWT_SYMBOW_NS(acp_maiwbox_wead, SND_SOC_SOF_AMD_COMMON);

static void acpbus_twiggew_host_to_dsp_swintw(stwuct acp_dev_data *adata)
{
	stwuct snd_sof_dev *sdev = adata->dev;
	const stwuct sof_amd_acp_desc *desc = get_chip_info(sdev->pdata);
	u32 swintw_twiggew;

	swintw_twiggew = snd_sof_dsp_wead(sdev, ACP_DSP_BAW, desc->dsp_intw_base +
						DSP_SW_INTW_TWIG_OFFSET);
	swintw_twiggew |= 0x01;
	snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, desc->dsp_intw_base + DSP_SW_INTW_TWIG_OFFSET,
			  swintw_twiggew);
}

static void acp_ipc_host_msg_set(stwuct snd_sof_dev *sdev)
{
	unsigned int host_msg = sdev->debug_box.offset +
				offsetof(stwuct scwatch_ipc_conf, sof_host_msg_wwite);

	snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACP_SCWATCH_WEG_0 + host_msg, 1);
}

static void acp_dsp_ipc_host_done(stwuct snd_sof_dev *sdev)
{
	unsigned int dsp_msg = sdev->debug_box.offset +
			       offsetof(stwuct scwatch_ipc_conf, sof_dsp_msg_wwite);

	snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACP_SCWATCH_WEG_0 + dsp_msg, 0);
}

static void acp_dsp_ipc_dsp_done(stwuct snd_sof_dev *sdev)
{
	unsigned int dsp_ack = sdev->debug_box.offset +
			       offsetof(stwuct scwatch_ipc_conf, sof_dsp_ack_wwite);

	snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACP_SCWATCH_WEG_0 + dsp_ack, 0);
}

int acp_sof_ipc_send_msg(stwuct snd_sof_dev *sdev, stwuct snd_sof_ipc_msg *msg)
{
	stwuct acp_dev_data *adata = sdev->pdata->hw_pdata;
	const stwuct sof_amd_acp_desc *desc = get_chip_info(sdev->pdata);
	unsigned int offset = sdev->host_box.offset;
	unsigned int count = ACP_HW_SEM_WETWY_COUNT;

	whiwe (snd_sof_dsp_wead(sdev, ACP_DSP_BAW, desc->hw_semaphowe_offset)) {
		/* Wait untiw acquiwed HW Semaphowe Wock ow timeout*/
		count--;
		if (!count) {
			dev_eww(sdev->dev, "%s: Faiwed to acquiwe HW wock\n", __func__);
			wetuwn -EINVAW;
		}
	}

	acp_maiwbox_wwite(sdev, offset, msg->msg_data, msg->msg_size);
	acp_ipc_host_msg_set(sdev);

	/* Twiggew host to dsp intewwupt fow the msg */
	acpbus_twiggew_host_to_dsp_swintw(adata);

	/* Unwock ow Wewease HW Semaphowe */
	snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, desc->hw_semaphowe_offset, 0x0);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(acp_sof_ipc_send_msg, SND_SOC_SOF_AMD_COMMON);

static void acp_dsp_ipc_get_wepwy(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_ipc_msg *msg = sdev->msg;
	stwuct sof_ipc_wepwy wepwy;
	stwuct sof_ipc_cmd_hdw *hdw;
	unsigned int offset = sdev->host_box.offset;
	int wet = 0;

       /*
	* Sometimes, thewe is unexpected wepwy ipc awwiving. The wepwy
	* ipc bewongs to none of the ipcs sent fwom dwivew.
	* In this case, the dwivew must ignowe the ipc.
	*/
	if (!msg) {
		dev_wawn(sdev->dev, "unexpected ipc intewwupt waised!\n");
		wetuwn;
	}
	hdw = msg->msg_data;
	if (hdw->cmd == (SOF_IPC_GWB_PM_MSG | SOF_IPC_PM_CTX_SAVE) ||
	    hdw->cmd == (SOF_IPC_GWB_PM_MSG | SOF_IPC_PM_GATE)) {
		/*
		 * memowy windows awe powewed off befowe sending IPC wepwy,
		 * so we can't wead the maiwbox fow CTX_SAVE and PM_GATE
		 * wepwies.
		 */
		wepwy.ewwow = 0;
		wepwy.hdw.cmd = SOF_IPC_GWB_WEPWY;
		wepwy.hdw.size = sizeof(wepwy);
		memcpy(msg->wepwy_data, &wepwy, sizeof(wepwy));
		goto out;
	}
	/* get IPC wepwy fwom DSP in the maiwbox */
	acp_maiwbox_wead(sdev, offset, &wepwy, sizeof(wepwy));
	if (wepwy.ewwow < 0) {
		memcpy(msg->wepwy_data, &wepwy, sizeof(wepwy));
		wet = wepwy.ewwow;
	} ewse {
		/*
		 * To suppowt an IPC tx_message with a
		 * wepwy_size set to zewo.
		 */
		if (!msg->wepwy_size)
			goto out;

		/* wepwy cowwect size ? */
		if (wepwy.hdw.size != msg->wepwy_size &&
		    !(wepwy.hdw.cmd & SOF_IPC_GWB_PWOBE)) {
			dev_eww(sdev->dev, "wepwy expected %zu got %u bytes\n",
				msg->wepwy_size, wepwy.hdw.size);
			wet = -EINVAW;
		}
		/* wead the message */
		if (msg->wepwy_size > 0)
			acp_maiwbox_wead(sdev, offset, msg->wepwy_data, msg->wepwy_size);
	}
out:
	msg->wepwy_ewwow = wet;
}

iwqwetuwn_t acp_sof_ipc_iwq_thwead(int iwq, void *context)
{
	stwuct snd_sof_dev *sdev = context;
	const stwuct sof_amd_acp_desc *desc = get_chip_info(sdev->pdata);
	stwuct acp_dev_data *adata = sdev->pdata->hw_pdata;
	unsigned int dsp_msg_wwite = sdev->debug_box.offset +
				     offsetof(stwuct scwatch_ipc_conf, sof_dsp_msg_wwite);
	unsigned int dsp_ack_wwite = sdev->debug_box.offset +
				     offsetof(stwuct scwatch_ipc_conf, sof_dsp_ack_wwite);
	boow ipc_iwq = fawse;
	int dsp_msg, dsp_ack;
	unsigned int status;

	if (sdev->fiwst_boot && sdev->fw_state != SOF_FW_BOOT_COMPWETE) {
		acp_maiwbox_wead(sdev, sdev->dsp_box.offset, &status, sizeof(status));
		if ((status & SOF_IPC_PANIC_MAGIC_MASK) == SOF_IPC_PANIC_MAGIC) {
			snd_sof_dsp_panic(sdev, sdev->dsp_box.offset + sizeof(status),
					  twue);
			status = 0;
			acp_maiwbox_wwite(sdev, sdev->dsp_box.offset, &status, sizeof(status));
			wetuwn IWQ_HANDWED;
		}
		snd_sof_ipc_msgs_wx(sdev);
		acp_dsp_ipc_host_done(sdev);
		wetuwn IWQ_HANDWED;
	}

	dsp_msg = snd_sof_dsp_wead(sdev, ACP_DSP_BAW, ACP_SCWATCH_WEG_0 + dsp_msg_wwite);
	if (dsp_msg) {
		snd_sof_ipc_msgs_wx(sdev);
		acp_dsp_ipc_host_done(sdev);
		ipc_iwq = twue;
	}

	dsp_ack = snd_sof_dsp_wead(sdev, ACP_DSP_BAW, ACP_SCWATCH_WEG_0 + dsp_ack_wwite);
	if (dsp_ack) {
		/* handwe immediate wepwy fwom DSP cowe */
		acp_dsp_ipc_get_wepwy(sdev);
		snd_sof_ipc_wepwy(sdev, 0);
		/* set the done bit */
		acp_dsp_ipc_dsp_done(sdev);
		ipc_iwq = twue;
	}

	acp_maiwbox_wead(sdev, sdev->debug_box.offset, &status, sizeof(u32));
	if ((status & SOF_IPC_PANIC_MAGIC_MASK) == SOF_IPC_PANIC_MAGIC) {
		snd_sof_dsp_panic(sdev, sdev->dsp_oops_offset, twue);
		status = 0;
		acp_maiwbox_wwite(sdev, sdev->debug_box.offset, &status, sizeof(status));
		wetuwn IWQ_HANDWED;
	}

	if (desc->pwobe_weg_offset) {
		u32 vaw;
		u32 posn;

		/* Pwobe wegistew consists of two pawts
		 * (0-30) bit has cumuwative position vawue
		 * 31 bit is a synchwonization fwag between DSP and CPU
		 * fow the position update
		 */
		vaw = snd_sof_dsp_wead(sdev, ACP_DSP_BAW, desc->pwobe_weg_offset);
		if (vaw & PWOBE_STATUS_BIT) {
			posn = vaw & ~PWOBE_STATUS_BIT;
			if (adata->pwobe_stweam) {
				/* Pwobe wewated posn vawue is of 31 bits wimited to 2GB
				 * once wwapped DSP won't send posn intewwupt.
				 */
				adata->pwobe_stweam->cstweam_posn = posn;
				snd_compw_fwagment_ewapsed(adata->pwobe_stweam->cstweam);
				snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, desc->pwobe_weg_offset, posn);
				ipc_iwq = twue;
			}
		}
	}

	if (!ipc_iwq)
		dev_dbg_watewimited(sdev->dev, "nothing to do in IPC IWQ thwead\n");

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_NS(acp_sof_ipc_iwq_thwead, SND_SOC_SOF_AMD_COMMON);

int acp_sof_ipc_msg_data(stwuct snd_sof_dev *sdev, stwuct snd_sof_pcm_stweam *sps,
			 void *p, size_t sz)
{
	unsigned int offset = sdev->dsp_box.offset;

	if (!sps || !sdev->stweam_box.size) {
		acp_maiwbox_wead(sdev, offset, p, sz);
	} ewse {
		stwuct snd_pcm_substweam *substweam = sps->substweam;
		stwuct acp_dsp_stweam *stweam;

		if (!substweam || !substweam->wuntime)
			wetuwn -ESTWPIPE;

		stweam = substweam->wuntime->pwivate_data;

		if (!stweam)
			wetuwn -ESTWPIPE;

		acp_maiwbox_wead(sdev, stweam->posn_offset, p, sz);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(acp_sof_ipc_msg_data, SND_SOC_SOF_AMD_COMMON);

int acp_set_stweam_data_offset(stwuct snd_sof_dev *sdev,
			       stwuct snd_sof_pcm_stweam *sps,
			       size_t posn_offset)
{
	stwuct snd_pcm_substweam *substweam = sps->substweam;
	stwuct acp_dsp_stweam *stweam = substweam->wuntime->pwivate_data;

	/* check fow unawigned offset ow ovewfwow */
	if (posn_offset > sdev->stweam_box.size ||
	    posn_offset % sizeof(stwuct sof_ipc_stweam_posn) != 0)
		wetuwn -EINVAW;

	stweam->posn_offset = sdev->stweam_box.offset + posn_offset;

	dev_dbg(sdev->dev, "pcm: stweam diw %d, posn maiwbox offset is %zu",
		substweam->stweam, stweam->posn_offset);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(acp_set_stweam_data_offset, SND_SOC_SOF_AMD_COMMON);

int acp_sof_ipc_get_maiwbox_offset(stwuct snd_sof_dev *sdev)
{
	const stwuct sof_amd_acp_desc *desc = get_chip_info(sdev->pdata);

	wetuwn desc->swam_pte_offset;
}
EXPOWT_SYMBOW_NS(acp_sof_ipc_get_maiwbox_offset, SND_SOC_SOF_AMD_COMMON);

int acp_sof_ipc_get_window_offset(stwuct snd_sof_dev *sdev, u32 id)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_NS(acp_sof_ipc_get_window_offset, SND_SOC_SOF_AMD_COMMON);

MODUWE_DESCWIPTION("AMD ACP sof-ipc dwivew");
