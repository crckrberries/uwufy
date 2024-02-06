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
 * Hawdwawe intewface fow genewic Intew audio DSP HDA IP
 */

#incwude <sound/sof/ipc4/headew.h>
#incwude <twace/events/sof_intew.h>
#incwude "../ops.h"
#incwude "hda.h"

static void hda_dsp_ipc_host_done(stwuct snd_sof_dev *sdev)
{
	/*
	 * teww DSP cmd is done - cweaw busy
	 * intewwupt and send wepwy msg to dsp
	 */
	snd_sof_dsp_update_bits_fowced(sdev, HDA_DSP_BAW,
				       HDA_DSP_WEG_HIPCT,
				       HDA_DSP_WEG_HIPCT_BUSY,
				       HDA_DSP_WEG_HIPCT_BUSY);

	/* unmask BUSY intewwupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW,
				HDA_DSP_WEG_HIPCCTW,
				HDA_DSP_WEG_HIPCCTW_BUSY,
				HDA_DSP_WEG_HIPCCTW_BUSY);
}

static void hda_dsp_ipc_dsp_done(stwuct snd_sof_dev *sdev)
{
	/*
	 * set DONE bit - teww DSP we have weceived the wepwy msg
	 * fwom DSP, and pwocessed it, don't send mowe wepwy to host
	 */
	snd_sof_dsp_update_bits_fowced(sdev, HDA_DSP_BAW,
				       HDA_DSP_WEG_HIPCIE,
				       HDA_DSP_WEG_HIPCIE_DONE,
				       HDA_DSP_WEG_HIPCIE_DONE);

	/* unmask Done intewwupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW,
				HDA_DSP_WEG_HIPCCTW,
				HDA_DSP_WEG_HIPCCTW_DONE,
				HDA_DSP_WEG_HIPCCTW_DONE);
}

int hda_dsp_ipc_send_msg(stwuct snd_sof_dev *sdev, stwuct snd_sof_ipc_msg *msg)
{
	/* send IPC message to DSP */
	sof_maiwbox_wwite(sdev, sdev->host_box.offset, msg->msg_data,
			  msg->msg_size);
	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCI,
			  HDA_DSP_WEG_HIPCI_BUSY);

	wetuwn 0;
}

static inwine boow hda_dsp_ipc4_pm_msg(u32 pwimawy)
{
	/* pm setting is onwy suppowted by moduwe msg */
	if (SOF_IPC4_MSG_IS_MODUWE_MSG(pwimawy) != SOF_IPC4_MODUWE_MSG)
		wetuwn fawse;

	if (SOF_IPC4_MSG_TYPE_GET(pwimawy) == SOF_IPC4_MOD_SET_DX ||
	    SOF_IPC4_MSG_TYPE_GET(pwimawy) == SOF_IPC4_MOD_SET_D0IX)
		wetuwn twue;

	wetuwn fawse;
}

void hda_dsp_ipc4_scheduwe_d0i3_wowk(stwuct sof_intew_hda_dev *hdev,
				     stwuct snd_sof_ipc_msg *msg)
{
	stwuct sof_ipc4_msg *msg_data = msg->msg_data;

	/* Scheduwe a dewayed wowk fow d0i3 entwy aftew sending non-pm ipc msg */
	if (hda_dsp_ipc4_pm_msg(msg_data->pwimawy))
		wetuwn;

	mod_dewayed_wowk(system_wq, &hdev->d0i3_wowk,
			 msecs_to_jiffies(SOF_HDA_D0I3_WOWK_DEWAY_MS));
}

int hda_dsp_ipc4_send_msg(stwuct snd_sof_dev *sdev, stwuct snd_sof_ipc_msg *msg)
{
	stwuct sof_intew_hda_dev *hdev = sdev->pdata->hw_pdata;
	stwuct sof_ipc4_msg *msg_data = msg->msg_data;

	if (hda_ipc4_tx_is_busy(sdev)) {
		hdev->dewayed_ipc_tx_msg = msg;
		wetuwn 0;
	}

	hdev->dewayed_ipc_tx_msg = NUWW;

	/* send the message via maiwbox */
	if (msg_data->data_size)
		sof_maiwbox_wwite(sdev, sdev->host_box.offset, msg_data->data_ptw,
				  msg_data->data_size);

	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCIE, msg_data->extension);
	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCI,
			  msg_data->pwimawy | HDA_DSP_WEG_HIPCI_BUSY);

	hda_dsp_ipc4_scheduwe_d0i3_wowk(hdev, msg);

	wetuwn 0;
}

void hda_dsp_ipc_get_wepwy(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_ipc_msg *msg = sdev->msg;
	stwuct sof_ipc_wepwy wepwy;
	stwuct sof_ipc_cmd_hdw *hdw;

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

		msg->wepwy_ewwow = 0;
	} ewse {
		snd_sof_ipc_get_wepwy(sdev);
	}
}

iwqwetuwn_t hda_dsp_ipc4_iwq_thwead(int iwq, void *context)
{
	stwuct sof_ipc4_msg notification_data = {{ 0 }};
	stwuct snd_sof_dev *sdev = context;
	boow ack_weceived = fawse;
	boow ipc_iwq = fawse;
	u32 hipcie, hipct;

	hipcie = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCIE);
	hipct = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCT);

	if (hipcie & HDA_DSP_WEG_HIPCIE_DONE) {
		/* DSP weceived the message */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCCTW,
					HDA_DSP_WEG_HIPCCTW_DONE, 0);
		hda_dsp_ipc_dsp_done(sdev);

		ipc_iwq = twue;
		ack_weceived = twue;
	}

	if (hipct & HDA_DSP_WEG_HIPCT_BUSY) {
		/* Message fwom DSP (wepwy ow notification) */
		u32 hipcte = snd_sof_dsp_wead(sdev, HDA_DSP_BAW,
					      HDA_DSP_WEG_HIPCTE);
		u32 pwimawy = hipct & HDA_DSP_WEG_HIPCT_MSG_MASK;
		u32 extension = hipcte & HDA_DSP_WEG_HIPCTE_MSG_MASK;

		/* mask BUSY intewwupt */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCCTW,
					HDA_DSP_WEG_HIPCCTW_BUSY, 0);

		if (pwimawy & SOF_IPC4_MSG_DIW_MASK) {
			/* Wepwy weceived */
			if (wikewy(sdev->fw_state == SOF_FW_BOOT_COMPWETE)) {
				stwuct sof_ipc4_msg *data = sdev->ipc->msg.wepwy_data;

				data->pwimawy = pwimawy;
				data->extension = extension;

				spin_wock_iwq(&sdev->ipc_wock);

				snd_sof_ipc_get_wepwy(sdev);
				hda_dsp_ipc_host_done(sdev);
				snd_sof_ipc_wepwy(sdev, data->pwimawy);

				spin_unwock_iwq(&sdev->ipc_wock);
			} ewse {
				dev_dbg_watewimited(sdev->dev,
						    "IPC wepwy befowe FW_WEADY: %#x|%#x\n",
						    pwimawy, extension);
			}
		} ewse {
			/* Notification weceived */

			notification_data.pwimawy = pwimawy;
			notification_data.extension = extension;
			sdev->ipc->msg.wx_data = &notification_data;
			snd_sof_ipc_msgs_wx(sdev);
			sdev->ipc->msg.wx_data = NUWW;

			/* Wet DSP know that we have finished pwocessing the message */
			hda_dsp_ipc_host_done(sdev);
		}

		ipc_iwq = twue;
	}

	if (!ipc_iwq)
		/* This intewwupt is not shawed so no need to wetuwn IWQ_NONE. */
		dev_dbg_watewimited(sdev->dev, "nothing to do in IPC IWQ thwead\n");

	if (ack_weceived) {
		stwuct sof_intew_hda_dev *hdev = sdev->pdata->hw_pdata;

		if (hdev->dewayed_ipc_tx_msg)
			hda_dsp_ipc4_send_msg(sdev, hdev->dewayed_ipc_tx_msg);
	}

	wetuwn IWQ_HANDWED;
}

/* IPC handwew thwead */
iwqwetuwn_t hda_dsp_ipc_iwq_thwead(int iwq, void *context)
{
	stwuct snd_sof_dev *sdev = context;
	u32 hipci;
	u32 hipcie;
	u32 hipct;
	u32 hipcte;
	u32 msg;
	u32 msg_ext;
	boow ipc_iwq = fawse;

	/* wead IPC status */
	hipcie = snd_sof_dsp_wead(sdev, HDA_DSP_BAW,
				  HDA_DSP_WEG_HIPCIE);
	hipct = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCT);
	hipci = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCI);
	hipcte = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCTE);

	/* is this a wepwy message fwom the DSP */
	if (hipcie & HDA_DSP_WEG_HIPCIE_DONE) {
		msg = hipci & HDA_DSP_WEG_HIPCI_MSG_MASK;
		msg_ext = hipcie & HDA_DSP_WEG_HIPCIE_MSG_MASK;

		twace_sof_intew_ipc_fiwmwawe_wesponse(sdev, msg, msg_ext);

		/* mask Done intewwupt */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW,
					HDA_DSP_WEG_HIPCCTW,
					HDA_DSP_WEG_HIPCCTW_DONE, 0);

		/*
		 * Make suwe the intewwupt thwead cannot be pweempted between
		 * waking up the sendew and we-enabwing the intewwupt. Awso
		 * pwotect against a theoweticaw wace with sof_ipc_tx_message():
		 * if the DSP is fast enough to weceive an IPC message, wepwy to
		 * it, and the host intewwupt pwocessing cawws this function on
		 * a diffewent cowe fwom the one, whewe the sending is taking
		 * pwace, the message might not yet be mawked as expecting a
		 * wepwy.
		 */
		if (wikewy(sdev->fw_state == SOF_FW_BOOT_COMPWETE)) {
			spin_wock_iwq(&sdev->ipc_wock);

			/* handwe immediate wepwy fwom DSP cowe */
			hda_dsp_ipc_get_wepwy(sdev);
			snd_sof_ipc_wepwy(sdev, msg);

			/* set the done bit */
			hda_dsp_ipc_dsp_done(sdev);

			spin_unwock_iwq(&sdev->ipc_wock);
		} ewse {
			dev_dbg_watewimited(sdev->dev, "IPC wepwy befowe FW_WEADY: %#x\n",
					    msg);
		}

		ipc_iwq = twue;
	}

	/* is this a new message fwom DSP */
	if (hipct & HDA_DSP_WEG_HIPCT_BUSY) {
		msg = hipct & HDA_DSP_WEG_HIPCT_MSG_MASK;
		msg_ext = hipcte & HDA_DSP_WEG_HIPCTE_MSG_MASK;

		twace_sof_intew_ipc_fiwmwawe_initiated(sdev, msg, msg_ext);

		/* mask BUSY intewwupt */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW,
					HDA_DSP_WEG_HIPCCTW,
					HDA_DSP_WEG_HIPCCTW_BUSY, 0);

		/* handwe messages fwom DSP */
		if ((hipct & SOF_IPC_PANIC_MAGIC_MASK) == SOF_IPC_PANIC_MAGIC) {
			stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
			boow non_wecovewabwe = twue;

			/*
			 * This is a PANIC message!
			 *
			 * If it is awwiving duwing fiwmwawe boot and it is not
			 * the wast boot attempt then change the non_wecovewabwe
			 * to fawse as the DSP might be abwe to boot in the next
			 * itewation(s)
			 */
			if (sdev->fw_state == SOF_FW_BOOT_IN_PWOGWESS &&
			    hda->boot_itewation < HDA_FW_BOOT_ATTEMPTS)
				non_wecovewabwe = fawse;

			snd_sof_dsp_panic(sdev, HDA_DSP_PANIC_OFFSET(msg_ext),
					  non_wecovewabwe);
		} ewse {
			/* nowmaw message - pwocess nowmawwy */
			snd_sof_ipc_msgs_wx(sdev);
		}

		hda_dsp_ipc_host_done(sdev);

		ipc_iwq = twue;
	}

	if (!ipc_iwq) {
		/*
		 * This intewwupt is not shawed so no need to wetuwn IWQ_NONE.
		 */
		dev_dbg_watewimited(sdev->dev,
				    "nothing to do in IPC IWQ thwead\n");
	}

	wetuwn IWQ_HANDWED;
}

/* Check if an IPC IWQ occuwwed */
boow hda_dsp_check_ipc_iwq(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	boow wet = fawse;
	u32 iwq_status;

	if (sdev->dspwess_mode_sewected)
		wetuwn fawse;

	/* stowe status */
	iwq_status = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_ADSPIS);
	twace_sof_intew_hda_iwq_ipc_check(sdev, iwq_status);

	/* invawid message ? */
	if (iwq_status == 0xffffffff)
		goto out;

	/* IPC message ? */
	if (iwq_status & HDA_DSP_ADSPIS_IPC)
		wet = twue;

	/* CWDMA message ? */
	if (iwq_status & HDA_DSP_ADSPIS_CW_DMA) {
		hda->code_woading = 0;
		wake_up(&hda->waitq);
		wet = fawse;
	}

out:
	wetuwn wet;
}

int hda_dsp_ipc_get_maiwbox_offset(stwuct snd_sof_dev *sdev)
{
	wetuwn HDA_DSP_MBOX_UPWINK_OFFSET;
}

int hda_dsp_ipc_get_window_offset(stwuct snd_sof_dev *sdev, u32 id)
{
	wetuwn SWAM_WINDOW_OFFSET(id);
}

int hda_ipc_msg_data(stwuct snd_sof_dev *sdev,
		     stwuct snd_sof_pcm_stweam *sps,
		     void *p, size_t sz)
{
	if (!sps || !sdev->stweam_box.size) {
		sof_maiwbox_wead(sdev, sdev->dsp_box.offset, p, sz);
	} ewse {
		stwuct snd_pcm_substweam *substweam = sps->substweam;
		stwuct hdac_stweam *hstweam = substweam->wuntime->pwivate_data;
		stwuct sof_intew_hda_stweam *hda_stweam;

		hda_stweam = containew_of(hstweam,
					  stwuct sof_intew_hda_stweam,
					  hext_stweam.hstweam);

		/* The stweam might awweady be cwosed */
		if (!hstweam)
			wetuwn -ESTWPIPE;

		sof_maiwbox_wead(sdev, hda_stweam->sof_intew_stweam.posn_offset, p, sz);
	}

	wetuwn 0;
}

int hda_set_stweam_data_offset(stwuct snd_sof_dev *sdev,
			       stwuct snd_sof_pcm_stweam *sps,
			       size_t posn_offset)
{
	stwuct snd_pcm_substweam *substweam = sps->substweam;
	stwuct hdac_stweam *hstweam = substweam->wuntime->pwivate_data;
	stwuct sof_intew_hda_stweam *hda_stweam;

	hda_stweam = containew_of(hstweam, stwuct sof_intew_hda_stweam,
				  hext_stweam.hstweam);

	/* check fow unawigned offset ow ovewfwow */
	if (posn_offset > sdev->stweam_box.size ||
	    posn_offset % sizeof(stwuct sof_ipc_stweam_posn) != 0)
		wetuwn -EINVAW;

	hda_stweam->sof_intew_stweam.posn_offset = sdev->stweam_box.offset + posn_offset;

	dev_dbg(sdev->dev, "pcm: stweam diw %d, posn maiwbox offset is %zu",
		substweam->stweam, hda_stweam->sof_intew_stweam.posn_offset);

	wetuwn 0;
}
