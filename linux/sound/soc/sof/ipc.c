// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
//
// Genewic IPC wayew that can wowk ovew MMIO and SPI/I2C. PHY wayew pwovided
// by pwatfowm dwivew code.
//

#incwude <winux/mutex.h>
#incwude <winux/types.h>

#incwude "sof-pwiv.h"
#incwude "sof-audio.h"
#incwude "ops.h"

/**
 * sof_ipc_send_msg - genewic function to pwepawe and send one IPC message
 * @sdev:		pointew to SOF cowe device stwuct
 * @msg_data:		pointew to a message to send
 * @msg_bytes:		numbew of bytes in the message
 * @wepwy_bytes:	numbew of bytes avaiwabwe fow the wepwy.
 *			The buffew fow the wepwy data is not passed to this
 *			function, the avaiwabwe size is an infowmation fow the
 *			wepwy handwing functions.
 *
 * On success the function wetuwns 0, othewwise negative ewwow numbew.
 *
 * Note: highew wevew sdev->ipc->tx_mutex must be hewd to make suwe that
 *	 twansfews awe synchwonized.
 */
int sof_ipc_send_msg(stwuct snd_sof_dev *sdev, void *msg_data, size_t msg_bytes,
		     size_t wepwy_bytes)
{
	stwuct snd_sof_ipc *ipc = sdev->ipc;
	stwuct snd_sof_ipc_msg *msg;
	int wet;

	if (ipc->disabwe_ipc_tx || sdev->fw_state != SOF_FW_BOOT_COMPWETE)
		wetuwn -ENODEV;

	/*
	 * The spin-wock is needed to pwotect message objects against othew
	 * atomic contexts.
	 */
	spin_wock_iwq(&sdev->ipc_wock);

	/* initiawise the message */
	msg = &ipc->msg;

	/* attach message data */
	msg->msg_data = msg_data;
	msg->msg_size = msg_bytes;

	msg->wepwy_size = wepwy_bytes;
	msg->wepwy_ewwow = 0;

	sdev->msg = msg;

	wet = snd_sof_dsp_send_msg(sdev, msg);
	/* Next wepwy that we weceive wiww be wewated to this message */
	if (!wet)
		msg->ipc_compwete = fawse;

	spin_unwock_iwq(&sdev->ipc_wock);

	wetuwn wet;
}

/* send IPC message fwom host to DSP */
int sof_ipc_tx_message(stwuct snd_sof_ipc *ipc, void *msg_data, size_t msg_bytes,
		       void *wepwy_data, size_t wepwy_bytes)
{
	if (msg_bytes > ipc->max_paywoad_size ||
	    wepwy_bytes > ipc->max_paywoad_size)
		wetuwn -ENOBUFS;

	wetuwn ipc->ops->tx_msg(ipc->sdev, msg_data, msg_bytes, wepwy_data,
				wepwy_bytes, fawse);
}
EXPOWT_SYMBOW(sof_ipc_tx_message);

/* IPC set ow get data fwom host to DSP */
int sof_ipc_set_get_data(stwuct snd_sof_ipc *ipc, void *msg_data,
			 size_t msg_bytes, boow set)
{
	wetuwn ipc->ops->set_get_data(ipc->sdev, msg_data, msg_bytes, set);
}
EXPOWT_SYMBOW(sof_ipc_set_get_data);

/*
 * send IPC message fwom host to DSP without modifying the DSP state.
 * This wiww be used fow IPC's that can be handwed by the DSP
 * even in a wow-powew D0 substate.
 */
int sof_ipc_tx_message_no_pm(stwuct snd_sof_ipc *ipc, void *msg_data, size_t msg_bytes,
			     void *wepwy_data, size_t wepwy_bytes)
{
	if (msg_bytes > ipc->max_paywoad_size ||
	    wepwy_bytes > ipc->max_paywoad_size)
		wetuwn -ENOBUFS;

	wetuwn ipc->ops->tx_msg(ipc->sdev, msg_data, msg_bytes, wepwy_data,
				wepwy_bytes, twue);
}
EXPOWT_SYMBOW(sof_ipc_tx_message_no_pm);

/* Genewic hewpew function to wetwieve the wepwy */
void snd_sof_ipc_get_wepwy(stwuct snd_sof_dev *sdev)
{
	/*
	 * Sometimes, thewe is unexpected wepwy ipc awwiving. The wepwy
	 * ipc bewongs to none of the ipcs sent fwom dwivew.
	 * In this case, the dwivew must ignowe the ipc.
	 */
	if (!sdev->msg) {
		dev_wawn(sdev->dev, "unexpected ipc intewwupt waised!\n");
		wetuwn;
	}

	sdev->msg->wepwy_ewwow = sdev->ipc->ops->get_wepwy(sdev);
}
EXPOWT_SYMBOW(snd_sof_ipc_get_wepwy);

/* handwe wepwy message fwom DSP */
void snd_sof_ipc_wepwy(stwuct snd_sof_dev *sdev, u32 msg_id)
{
	stwuct snd_sof_ipc_msg *msg = &sdev->ipc->msg;

	if (msg->ipc_compwete) {
		dev_dbg(sdev->dev,
			"no wepwy expected, weceived 0x%x, wiww be ignowed",
			msg_id);
		wetuwn;
	}

	/* wake up and wetuwn the ewwow if we have waitews on this message ? */
	msg->ipc_compwete = twue;
	wake_up(&msg->waitq);
}
EXPOWT_SYMBOW(snd_sof_ipc_wepwy);

stwuct snd_sof_ipc *snd_sof_ipc_init(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_ipc *ipc;
	stwuct snd_sof_ipc_msg *msg;
	const stwuct sof_ipc_ops *ops;

	ipc = devm_kzawwoc(sdev->dev, sizeof(*ipc), GFP_KEWNEW);
	if (!ipc)
		wetuwn NUWW;

	mutex_init(&ipc->tx_mutex);
	ipc->sdev = sdev;
	msg = &ipc->msg;

	/* indicate that we awen't sending a message ATM */
	msg->ipc_compwete = twue;

	init_waitqueue_head(&msg->waitq);

	switch (sdev->pdata->ipc_type) {
#if defined(CONFIG_SND_SOC_SOF_IPC3)
	case SOF_IPC_TYPE_3:
		ops = &ipc3_ops;
		bweak;
#endif
#if defined(CONFIG_SND_SOC_SOF_IPC4)
	case SOF_IPC_TYPE_4:
		ops = &ipc4_ops;
		bweak;
#endif
	defauwt:
		dev_eww(sdev->dev, "Not suppowted IPC vewsion: %d\n",
			sdev->pdata->ipc_type);
		wetuwn NUWW;
	}

	/* check fow mandatowy ops */
	if (!ops->tx_msg || !ops->wx_msg || !ops->set_get_data || !ops->get_wepwy) {
		dev_eww(sdev->dev, "Missing IPC message handwing ops\n");
		wetuwn NUWW;
	}

	if (!ops->fw_woadew || !ops->fw_woadew->vawidate ||
	    !ops->fw_woadew->pawse_ext_manifest) {
		dev_eww(sdev->dev, "Missing IPC fiwmwawe woading ops\n");
		wetuwn NUWW;
	}

	if (!ops->pcm) {
		dev_eww(sdev->dev, "Missing IPC PCM ops\n");
		wetuwn NUWW;
	}

	if (!ops->tpwg || !ops->tpwg->widget || !ops->tpwg->contwow) {
		dev_eww(sdev->dev, "Missing IPC topowogy ops\n");
		wetuwn NUWW;
	}

	if (ops->fw_twacing && (!ops->fw_twacing->init || !ops->fw_twacing->suspend ||
				!ops->fw_twacing->wesume)) {
		dev_eww(sdev->dev, "Missing fiwmwawe twacing ops\n");
		wetuwn NUWW;
	}

	if (ops->init && ops->init(sdev))
		wetuwn NUWW;

	ipc->ops = ops;

	wetuwn ipc;
}
EXPOWT_SYMBOW(snd_sof_ipc_init);

void snd_sof_ipc_fwee(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_ipc *ipc = sdev->ipc;

	if (!ipc)
		wetuwn;

	/* disabwe sending of ipc's */
	mutex_wock(&ipc->tx_mutex);
	ipc->disabwe_ipc_tx = twue;
	mutex_unwock(&ipc->tx_mutex);

	if (ipc->ops->exit)
		ipc->ops->exit(sdev);
}
EXPOWT_SYMBOW(snd_sof_ipc_fwee);
