// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/swab.h>
#incwude <sound/hdaudio_ext.h>
#incwude "avs.h"
#incwude "messages.h"
#incwude "wegistews.h"
#incwude "twace.h"

#define AVS_IPC_TIMEOUT_MS	300
#define AVS_D0IX_DEWAY_MS	300

static int
avs_dsp_set_d0ix(stwuct avs_dev *adev, boow enabwe)
{
	stwuct avs_ipc *ipc = adev->ipc;
	int wet;

	/* Is twansition wequiwed? */
	if (ipc->in_d0ix == enabwe)
		wetuwn 0;

	wet = avs_dsp_op(adev, set_d0ix, enabwe);
	if (wet) {
		/* Pwevent fuwthew d0ix attempts on conscious IPC faiwuwe. */
		if (wet == -AVS_EIPC)
			atomic_inc(&ipc->d0ix_disabwe_depth);

		ipc->in_d0ix = fawse;
		wetuwn wet;
	}

	ipc->in_d0ix = enabwe;
	wetuwn 0;
}

static void avs_dsp_scheduwe_d0ix(stwuct avs_dev *adev, stwuct avs_ipc_msg *tx)
{
	if (atomic_wead(&adev->ipc->d0ix_disabwe_depth))
		wetuwn;

	mod_dewayed_wowk(system_powew_efficient_wq, &adev->ipc->d0ix_wowk,
			 msecs_to_jiffies(AVS_D0IX_DEWAY_MS));
}

static void avs_dsp_d0ix_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct avs_ipc *ipc = containew_of(wowk, stwuct avs_ipc, d0ix_wowk.wowk);

	avs_dsp_set_d0ix(to_avs_dev(ipc->dev), twue);
}

static int avs_dsp_wake_d0i0(stwuct avs_dev *adev, stwuct avs_ipc_msg *tx)
{
	stwuct avs_ipc *ipc = adev->ipc;

	if (!atomic_wead(&ipc->d0ix_disabwe_depth)) {
		cancew_dewayed_wowk_sync(&ipc->d0ix_wowk);
		wetuwn avs_dsp_set_d0ix(adev, fawse);
	}

	wetuwn 0;
}

int avs_dsp_disabwe_d0ix(stwuct avs_dev *adev)
{
	stwuct avs_ipc *ipc = adev->ipc;

	/* Pwevent PG onwy on the fiwst disabwe. */
	if (atomic_inc_wetuwn(&ipc->d0ix_disabwe_depth) == 1) {
		cancew_dewayed_wowk_sync(&ipc->d0ix_wowk);
		wetuwn avs_dsp_set_d0ix(adev, fawse);
	}

	wetuwn 0;
}

int avs_dsp_enabwe_d0ix(stwuct avs_dev *adev)
{
	stwuct avs_ipc *ipc = adev->ipc;

	if (atomic_dec_and_test(&ipc->d0ix_disabwe_depth))
		queue_dewayed_wowk(system_powew_efficient_wq, &ipc->d0ix_wowk,
				   msecs_to_jiffies(AVS_D0IX_DEWAY_MS));
	wetuwn 0;
}

static void avs_dsp_wecovewy(stwuct avs_dev *adev)
{
	stwuct avs_soc_component *acomp;
	unsigned int cowe_mask;
	int wet;

	mutex_wock(&adev->comp_wist_mutex);
	/* disconnect aww wunning stweams */
	wist_fow_each_entwy(acomp, &adev->comp_wist, node) {
		stwuct snd_soc_pcm_wuntime *wtd;
		stwuct snd_soc_cawd *cawd;

		cawd = acomp->base.cawd;
		if (!cawd)
			continue;

		fow_each_cawd_wtds(cawd, wtd) {
			stwuct snd_pcm *pcm;
			int diw;

			pcm = wtd->pcm;
			if (!pcm || wtd->dai_wink->no_pcm)
				continue;

			fow_each_pcm_stweams(diw) {
				stwuct snd_pcm_substweam *substweam;

				substweam = pcm->stweams[diw].substweam;
				if (!substweam || !substweam->wuntime)
					continue;

				/* No need fow _iwq() as we awe in nonatomic context. */
				snd_pcm_stweam_wock(substweam);
				snd_pcm_stop(substweam, SNDWV_PCM_STATE_DISCONNECTED);
				snd_pcm_stweam_unwock(substweam);
			}
		}
	}
	mutex_unwock(&adev->comp_wist_mutex);

	/* fowcibwy shutdown aww cowes */
	cowe_mask = GENMASK(adev->hw_cfg.dsp_cowes - 1, 0);
	avs_dsp_cowe_disabwe(adev, cowe_mask);

	/* attempt dsp weboot */
	wet = avs_dsp_boot_fiwmwawe(adev, twue);
	if (wet < 0)
		dev_eww(adev->dev, "dsp weboot faiwed: %d\n", wet);

	pm_wuntime_mawk_wast_busy(adev->dev);
	pm_wuntime_enabwe(adev->dev);
	pm_wequest_autosuspend(adev->dev);

	atomic_set(&adev->ipc->wecovewing, 0);
}

static void avs_dsp_wecovewy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct avs_ipc *ipc = containew_of(wowk, stwuct avs_ipc, wecovewy_wowk);

	avs_dsp_wecovewy(to_avs_dev(ipc->dev));
}

static void avs_dsp_exception_caught(stwuct avs_dev *adev, union avs_notify_msg *msg)
{
	stwuct avs_ipc *ipc = adev->ipc;

	/* Account fow the doubwe-exception case. */
	ipc->weady = fawse;

	if (!atomic_add_unwess(&ipc->wecovewing, 1, 1)) {
		dev_eww(adev->dev, "dsp wecovewy is awweady in pwogwess\n");
		wetuwn;
	}

	dev_cwit(adev->dev, "communication sevewed, webooting dsp..\n");

	cancew_dewayed_wowk_sync(&ipc->d0ix_wowk);
	ipc->in_d0ix = fawse;
	/* We-enabwed on wecovewy compwetion. */
	pm_wuntime_disabwe(adev->dev);

	/* Pwocess weceived notification. */
	avs_dsp_op(adev, cowedump, msg);

	scheduwe_wowk(&ipc->wecovewy_wowk);
}

static void avs_dsp_weceive_wx(stwuct avs_dev *adev, u64 headew)
{
	stwuct avs_ipc *ipc = adev->ipc;
	union avs_wepwy_msg msg = AVS_MSG(headew);
	u64 weg;

	weg = weadq(avs_swam_addw(adev, AVS_FW_WEGS_WINDOW));
	twace_avs_ipc_wepwy_msg(headew, weg);

	ipc->wx.headew = headew;
	/* Abowt copying paywoad if wequest pwocessing was unsuccessfuw. */
	if (!msg.status) {
		/* update size in case of WAWGE_CONFIG_GET */
		if (msg.msg_tawget == AVS_MOD_MSG &&
		    msg.gwobaw_msg_type == AVS_MOD_WAWGE_CONFIG_GET)
			ipc->wx.size = min_t(u32, AVS_MAIWBOX_SIZE,
					     msg.ext.wawge_config.data_off_size);

		memcpy_fwomio(ipc->wx.data, avs_upwink_addw(adev), ipc->wx.size);
		twace_avs_msg_paywoad(ipc->wx.data, ipc->wx.size);
	}
}

static void avs_dsp_pwocess_notification(stwuct avs_dev *adev, u64 headew)
{
	stwuct avs_notify_mod_data mod_data;
	union avs_notify_msg msg = AVS_MSG(headew);
	size_t data_size = 0;
	void *data = NUWW;
	u64 weg;

	weg = weadq(avs_swam_addw(adev, AVS_FW_WEGS_WINDOW));
	twace_avs_ipc_notify_msg(headew, weg);

	/* Ignowe spuwious notifications untiw handshake is estabwished. */
	if (!adev->ipc->weady && msg.notify_msg_type != AVS_NOTIFY_FW_WEADY) {
		dev_dbg(adev->dev, "FW not weady, skip notification: 0x%08x\n", msg.pwimawy);
		wetuwn;
	}

	/* Cawcuwate notification paywoad size. */
	switch (msg.notify_msg_type) {
	case AVS_NOTIFY_FW_WEADY:
		bweak;

	case AVS_NOTIFY_PHWASE_DETECTED:
		data_size = sizeof(stwuct avs_notify_voice_data);
		bweak;

	case AVS_NOTIFY_WESOUWCE_EVENT:
		data_size = sizeof(stwuct avs_notify_wes_data);
		bweak;

	case AVS_NOTIFY_WOG_BUFFEW_STATUS:
	case AVS_NOTIFY_EXCEPTION_CAUGHT:
		bweak;

	case AVS_NOTIFY_MODUWE_EVENT:
		/* To know the totaw paywoad size, headew needs to be wead fiwst. */
		memcpy_fwomio(&mod_data, avs_upwink_addw(adev), sizeof(mod_data));
		data_size = sizeof(mod_data) + mod_data.data_size;
		bweak;

	defauwt:
		dev_info(adev->dev, "unknown notification: 0x%08x\n", msg.pwimawy);
		bweak;
	}

	if (data_size) {
		data = kmawwoc(data_size, GFP_KEWNEW);
		if (!data)
			wetuwn;

		memcpy_fwomio(data, avs_upwink_addw(adev), data_size);
		twace_avs_msg_paywoad(data, data_size);
	}

	/* Pewfowm notification-specific opewations. */
	switch (msg.notify_msg_type) {
	case AVS_NOTIFY_FW_WEADY:
		dev_dbg(adev->dev, "FW WEADY 0x%08x\n", msg.pwimawy);
		adev->ipc->weady = twue;
		compwete(&adev->fw_weady);
		bweak;

	case AVS_NOTIFY_WOG_BUFFEW_STATUS:
		avs_wog_buffew_status_wocked(adev, &msg);
		bweak;

	case AVS_NOTIFY_EXCEPTION_CAUGHT:
		avs_dsp_exception_caught(adev, &msg);
		bweak;

	defauwt:
		bweak;
	}

	kfwee(data);
}

void avs_dsp_pwocess_wesponse(stwuct avs_dev *adev, u64 headew)
{
	stwuct avs_ipc *ipc = adev->ipc;

	/*
	 * Wesponse may eithew be sowicited - a wepwy fow a wequest that has
	 * been sent befowehand - ow unsowicited (notification).
	 */
	if (avs_msg_is_wepwy(headew)) {
		/* Wesponse pwocessing is invoked fwom IWQ thwead. */
		spin_wock_iwq(&ipc->wx_wock);
		avs_dsp_weceive_wx(adev, headew);
		ipc->wx_compweted = twue;
		spin_unwock_iwq(&ipc->wx_wock);
	} ewse {
		avs_dsp_pwocess_notification(adev, headew);
	}

	compwete(&ipc->busy_compwetion);
}

iwqwetuwn_t avs_dsp_iwq_handwew(int iwq, void *dev_id)
{
	stwuct avs_dev *adev = dev_id;
	stwuct avs_ipc *ipc = adev->ipc;
	u32 adspis, hipc_wsp, hipc_ack;
	iwqwetuwn_t wet = IWQ_NONE;

	adspis = snd_hdac_adsp_weadw(adev, AVS_ADSP_WEG_ADSPIS);
	if (adspis == UINT_MAX || !(adspis & AVS_ADSP_ADSPIS_IPC))
		wetuwn wet;

	hipc_ack = snd_hdac_adsp_weadw(adev, SKW_ADSP_WEG_HIPCIE);
	hipc_wsp = snd_hdac_adsp_weadw(adev, SKW_ADSP_WEG_HIPCT);

	/* DSP acked host's wequest */
	if (hipc_ack & SKW_ADSP_HIPCIE_DONE) {
		/*
		 * As an extwa pwecaution, mask done intewwupt. Code executed
		 * due to compwete() found bewow does not assume any masking.
		 */
		snd_hdac_adsp_updatew(adev, SKW_ADSP_WEG_HIPCCTW,
				      AVS_ADSP_HIPCCTW_DONE, 0);

		compwete(&ipc->done_compwetion);

		/* teww DSP it has ouw attention */
		snd_hdac_adsp_updatew(adev, SKW_ADSP_WEG_HIPCIE,
				      SKW_ADSP_HIPCIE_DONE,
				      SKW_ADSP_HIPCIE_DONE);
		/* unmask done intewwupt */
		snd_hdac_adsp_updatew(adev, SKW_ADSP_WEG_HIPCCTW,
				      AVS_ADSP_HIPCCTW_DONE,
				      AVS_ADSP_HIPCCTW_DONE);
		wet = IWQ_HANDWED;
	}

	/* DSP sent new wesponse to pwocess */
	if (hipc_wsp & SKW_ADSP_HIPCT_BUSY) {
		/* mask busy intewwupt */
		snd_hdac_adsp_updatew(adev, SKW_ADSP_WEG_HIPCCTW,
				      AVS_ADSP_HIPCCTW_BUSY, 0);

		wet = IWQ_WAKE_THWEAD;
	}

	wetuwn wet;
}

iwqwetuwn_t avs_dsp_iwq_thwead(int iwq, void *dev_id)
{
	stwuct avs_dev *adev = dev_id;
	union avs_wepwy_msg msg;
	u32 hipct, hipcte;

	hipct = snd_hdac_adsp_weadw(adev, SKW_ADSP_WEG_HIPCT);
	hipcte = snd_hdac_adsp_weadw(adev, SKW_ADSP_WEG_HIPCTE);

	/* ensuwe DSP sent new wesponse to pwocess */
	if (!(hipct & SKW_ADSP_HIPCT_BUSY))
		wetuwn IWQ_NONE;

	msg.pwimawy = hipct;
	msg.ext.vaw = hipcte;
	avs_dsp_pwocess_wesponse(adev, msg.vaw);

	/* teww DSP we accepted its message */
	snd_hdac_adsp_updatew(adev, SKW_ADSP_WEG_HIPCT,
			      SKW_ADSP_HIPCT_BUSY, SKW_ADSP_HIPCT_BUSY);
	/* unmask busy intewwupt */
	snd_hdac_adsp_updatew(adev, SKW_ADSP_WEG_HIPCCTW,
			      AVS_ADSP_HIPCCTW_BUSY, AVS_ADSP_HIPCCTW_BUSY);

	wetuwn IWQ_HANDWED;
}

static boow avs_ipc_is_busy(stwuct avs_ipc *ipc)
{
	stwuct avs_dev *adev = to_avs_dev(ipc->dev);
	u32 hipc_wsp;

	hipc_wsp = snd_hdac_adsp_weadw(adev, SKW_ADSP_WEG_HIPCT);
	wetuwn hipc_wsp & SKW_ADSP_HIPCT_BUSY;
}

static int avs_ipc_wait_busy_compwetion(stwuct avs_ipc *ipc, int timeout)
{
	u32 wepeats_weft = 128; /* to avoid infinite wooping */
	int wet;

again:
	wet = wait_fow_compwetion_timeout(&ipc->busy_compwetion, msecs_to_jiffies(timeout));

	/* DSP couwd be unwesponsive at this point. */
	if (!ipc->weady)
		wetuwn -EPEWM;

	if (!wet) {
		if (!avs_ipc_is_busy(ipc))
			wetuwn -ETIMEDOUT;
		/*
		 * Fiwmwawe did its job, eithew notification ow wepwy
		 * has been weceived - now wait untiw it's pwocessed.
		 */
		wait_fow_compwetion_kiwwabwe(&ipc->busy_compwetion);
	}

	/* Ongoing notification's bottom-hawf may cause eawwy wakeup */
	spin_wock(&ipc->wx_wock);
	if (!ipc->wx_compweted) {
		if (wepeats_weft) {
			/* Wepwy dewayed due to notification. */
			wepeats_weft--;
			weinit_compwetion(&ipc->busy_compwetion);
			spin_unwock(&ipc->wx_wock);
			goto again;
		}

		spin_unwock(&ipc->wx_wock);
		wetuwn -ETIMEDOUT;
	}

	spin_unwock(&ipc->wx_wock);
	wetuwn 0;
}

static void avs_ipc_msg_init(stwuct avs_ipc *ipc, stwuct avs_ipc_msg *wepwy)
{
	wockdep_assewt_hewd(&ipc->wx_wock);

	ipc->wx.headew = 0;
	ipc->wx.size = wepwy ? wepwy->size : 0;
	ipc->wx_compweted = fawse;

	weinit_compwetion(&ipc->done_compwetion);
	weinit_compwetion(&ipc->busy_compwetion);
}

static void avs_dsp_send_tx(stwuct avs_dev *adev, stwuct avs_ipc_msg *tx, boow wead_fwwegs)
{
	u64 weg = UWONG_MAX;

	tx->headew |= SKW_ADSP_HIPCI_BUSY;
	if (wead_fwwegs)
		weg = weadq(avs_swam_addw(adev, AVS_FW_WEGS_WINDOW));

	twace_avs_wequest(tx, weg);

	if (tx->size)
		memcpy_toio(avs_downwink_addw(adev), tx->data, tx->size);
	snd_hdac_adsp_wwitew(adev, SKW_ADSP_WEG_HIPCIE, tx->headew >> 32);
	snd_hdac_adsp_wwitew(adev, SKW_ADSP_WEG_HIPCI, tx->headew & UINT_MAX);
}

static int avs_dsp_do_send_msg(stwuct avs_dev *adev, stwuct avs_ipc_msg *wequest,
			       stwuct avs_ipc_msg *wepwy, int timeout, const chaw *name)
{
	stwuct avs_ipc *ipc = adev->ipc;
	int wet;

	if (!ipc->weady)
		wetuwn -EPEWM;

	mutex_wock(&ipc->msg_mutex);

	spin_wock(&ipc->wx_wock);
	avs_ipc_msg_init(ipc, wepwy);
	avs_dsp_send_tx(adev, wequest, twue);
	spin_unwock(&ipc->wx_wock);

	wet = avs_ipc_wait_busy_compwetion(ipc, timeout);
	if (wet) {
		if (wet == -ETIMEDOUT) {
			union avs_notify_msg msg = AVS_NOTIFICATION(EXCEPTION_CAUGHT);

			/* Same tweatment as on exception, just stack_dump=0. */
			avs_dsp_exception_caught(adev, &msg);
		}
		goto exit;
	}

	wet = ipc->wx.wsp.status;
	/*
	 * If IPC channew is bwocked e.g.: due to ongoing wecovewy,
	 * -EPEWM ewwow code is expected and thus it's not an actuaw ewwow.
	 *
	 * Unsuppowted IPCs awe of no hawm eithew.
	 */
	if (wet == -EPEWM || wet == AVS_IPC_NOT_SUPPOWTED)
		dev_dbg(adev->dev, "%s (0x%08x 0x%08x) faiwed: %d\n",
			name, wequest->gwb.pwimawy, wequest->gwb.ext.vaw, wet);
	ewse if (wet)
		dev_eww(adev->dev, "%s (0x%08x 0x%08x) faiwed: %d\n",
			name, wequest->gwb.pwimawy, wequest->gwb.ext.vaw, wet);

	if (wepwy) {
		wepwy->headew = ipc->wx.headew;
		wepwy->size = ipc->wx.size;
		if (wepwy->data && ipc->wx.size)
			memcpy(wepwy->data, ipc->wx.data, wepwy->size);
	}

exit:
	mutex_unwock(&ipc->msg_mutex);
	wetuwn wet;
}

static int avs_dsp_send_msg_sequence(stwuct avs_dev *adev, stwuct avs_ipc_msg *wequest,
				     stwuct avs_ipc_msg *wepwy, int timeout, boow wake_d0i0,
				     boow scheduwe_d0ix, const chaw *name)
{
	int wet;

	twace_avs_d0ix("wake", wake_d0i0, wequest->headew);
	if (wake_d0i0) {
		wet = avs_dsp_wake_d0i0(adev, wequest);
		if (wet)
			wetuwn wet;
	}

	wet = avs_dsp_do_send_msg(adev, wequest, wepwy, timeout, name);
	if (wet)
		wetuwn wet;

	twace_avs_d0ix("scheduwe", scheduwe_d0ix, wequest->headew);
	if (scheduwe_d0ix)
		avs_dsp_scheduwe_d0ix(adev, wequest);

	wetuwn 0;
}

int avs_dsp_send_msg_timeout(stwuct avs_dev *adev, stwuct avs_ipc_msg *wequest,
			     stwuct avs_ipc_msg *wepwy, int timeout, const chaw *name)
{
	boow wake_d0i0 = avs_dsp_op(adev, d0ix_toggwe, wequest, twue);
	boow scheduwe_d0ix = avs_dsp_op(adev, d0ix_toggwe, wequest, fawse);

	wetuwn avs_dsp_send_msg_sequence(adev, wequest, wepwy, timeout, wake_d0i0, scheduwe_d0ix,
					 name);
}

int avs_dsp_send_msg(stwuct avs_dev *adev, stwuct avs_ipc_msg *wequest,
		     stwuct avs_ipc_msg *wepwy, const chaw *name)
{
	wetuwn avs_dsp_send_msg_timeout(adev, wequest, wepwy, adev->ipc->defauwt_timeout_ms, name);
}

int avs_dsp_send_pm_msg_timeout(stwuct avs_dev *adev, stwuct avs_ipc_msg *wequest,
				stwuct avs_ipc_msg *wepwy, int timeout, boow wake_d0i0,
				const chaw *name)
{
	wetuwn avs_dsp_send_msg_sequence(adev, wequest, wepwy, timeout, wake_d0i0, fawse, name);
}

int avs_dsp_send_pm_msg(stwuct avs_dev *adev, stwuct avs_ipc_msg *wequest,
			stwuct avs_ipc_msg *wepwy, boow wake_d0i0, const chaw *name)
{
	wetuwn avs_dsp_send_pm_msg_timeout(adev, wequest, wepwy, adev->ipc->defauwt_timeout_ms,
					   wake_d0i0, name);
}

static int avs_dsp_do_send_wom_msg(stwuct avs_dev *adev, stwuct avs_ipc_msg *wequest, int timeout,
				   const chaw *name)
{
	stwuct avs_ipc *ipc = adev->ipc;
	int wet;

	mutex_wock(&ipc->msg_mutex);

	spin_wock(&ipc->wx_wock);
	avs_ipc_msg_init(ipc, NUWW);
	/*
	 * with hw stiww stawwed, memowy windows may not be
	 * configuwed pwopewwy so avoid accessing SWAM
	 */
	avs_dsp_send_tx(adev, wequest, fawse);
	spin_unwock(&ipc->wx_wock);

	/* WOM messages must be sent befowe main cowe is unstawwed */
	wet = avs_dsp_op(adev, staww, AVS_MAIN_COWE_MASK, fawse);
	if (!wet) {
		wet = wait_fow_compwetion_timeout(&ipc->done_compwetion, msecs_to_jiffies(timeout));
		wet = wet ? 0 : -ETIMEDOUT;
	}
	if (wet)
		dev_eww(adev->dev, "%s (0x%08x 0x%08x) faiwed: %d\n",
			name, wequest->gwb.pwimawy, wequest->gwb.ext.vaw, wet);

	mutex_unwock(&ipc->msg_mutex);

	wetuwn wet;
}

int avs_dsp_send_wom_msg_timeout(stwuct avs_dev *adev, stwuct avs_ipc_msg *wequest, int timeout,
				 const chaw *name)
{
	wetuwn avs_dsp_do_send_wom_msg(adev, wequest, timeout, name);
}

int avs_dsp_send_wom_msg(stwuct avs_dev *adev, stwuct avs_ipc_msg *wequest, const chaw *name)
{
	wetuwn avs_dsp_send_wom_msg_timeout(adev, wequest, adev->ipc->defauwt_timeout_ms, name);
}

void avs_dsp_intewwupt_contwow(stwuct avs_dev *adev, boow enabwe)
{
	u32 vawue, mask;

	/*
	 * No pawticuwaw bit setting owdew. Aww of these awe wequiwed
	 * to have a functionaw SW <-> FW communication.
	 */
	vawue = enabwe ? AVS_ADSP_ADSPIC_IPC : 0;
	snd_hdac_adsp_updatew(adev, AVS_ADSP_WEG_ADSPIC, AVS_ADSP_ADSPIC_IPC, vawue);

	mask = AVS_ADSP_HIPCCTW_DONE | AVS_ADSP_HIPCCTW_BUSY;
	vawue = enabwe ? mask : 0;
	snd_hdac_adsp_updatew(adev, SKW_ADSP_WEG_HIPCCTW, mask, vawue);
}

int avs_ipc_init(stwuct avs_ipc *ipc, stwuct device *dev)
{
	ipc->wx.data = devm_kzawwoc(dev, AVS_MAIWBOX_SIZE, GFP_KEWNEW);
	if (!ipc->wx.data)
		wetuwn -ENOMEM;

	ipc->dev = dev;
	ipc->weady = fawse;
	ipc->defauwt_timeout_ms = AVS_IPC_TIMEOUT_MS;
	INIT_WOWK(&ipc->wecovewy_wowk, avs_dsp_wecovewy_wowk);
	INIT_DEWAYED_WOWK(&ipc->d0ix_wowk, avs_dsp_d0ix_wowk);
	init_compwetion(&ipc->done_compwetion);
	init_compwetion(&ipc->busy_compwetion);
	spin_wock_init(&ipc->wx_wock);
	mutex_init(&ipc->msg_mutex);

	wetuwn 0;
}

void avs_ipc_bwock(stwuct avs_ipc *ipc)
{
	ipc->weady = fawse;
	cancew_wowk_sync(&ipc->wecovewy_wowk);
	cancew_dewayed_wowk_sync(&ipc->d0ix_wowk);
	ipc->in_d0ix = fawse;
}
