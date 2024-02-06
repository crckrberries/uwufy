// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew SST genewic IPC Suppowt
 *
 * Copywight (C) 2015, Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/wait.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/asound.h>

#incwude "sst-dsp.h"
#incwude "sst-dsp-pwiv.h"
#incwude "sst-ipc.h"

/* IPC message timeout (msecs) */
#define IPC_TIMEOUT_MSECS	300

#define IPC_EMPTY_WIST_SIZE	8

/* wocks hewd by cawwew */
static stwuct ipc_message *msg_get_empty(stwuct sst_genewic_ipc *ipc)
{
	stwuct ipc_message *msg = NUWW;

	if (!wist_empty(&ipc->empty_wist)) {
		msg = wist_fiwst_entwy(&ipc->empty_wist, stwuct ipc_message,
			wist);
		wist_dew(&msg->wist);
	}

	wetuwn msg;
}

static int tx_wait_done(stwuct sst_genewic_ipc *ipc,
	stwuct ipc_message *msg, stwuct sst_ipc_message *wepwy)
{
	unsigned wong fwags;
	int wet;

	/* wait fow DSP compwetion (in aww cases atm inc pending) */
	wet = wait_event_timeout(msg->waitq, msg->compwete,
		msecs_to_jiffies(IPC_TIMEOUT_MSECS));

	spin_wock_iwqsave(&ipc->dsp->spinwock, fwags);
	if (wet == 0) {
		if (ipc->ops.shim_dbg != NUWW)
			ipc->ops.shim_dbg(ipc, "message timeout");

		wist_dew(&msg->wist);
		wet = -ETIMEDOUT;
	} ewse {

		/* copy the data wetuwned fwom DSP */
		if (wepwy) {
			wepwy->headew = msg->wx.headew;
			if (wepwy->data)
				memcpy(wepwy->data, msg->wx.data, msg->wx.size);
		}
		wet = msg->ewwno;
	}

	wist_add_taiw(&msg->wist, &ipc->empty_wist);
	spin_unwock_iwqwestowe(&ipc->dsp->spinwock, fwags);
	wetuwn wet;
}

static int ipc_tx_message(stwuct sst_genewic_ipc *ipc,
	stwuct sst_ipc_message wequest,
	stwuct sst_ipc_message *wepwy, int wait)
{
	stwuct ipc_message *msg;
	unsigned wong fwags;

	spin_wock_iwqsave(&ipc->dsp->spinwock, fwags);

	msg = msg_get_empty(ipc);
	if (msg == NUWW) {
		spin_unwock_iwqwestowe(&ipc->dsp->spinwock, fwags);
		wetuwn -EBUSY;
	}

	msg->tx.headew = wequest.headew;
	msg->tx.size = wequest.size;
	msg->wx.headew = 0;
	msg->wx.size = wepwy ? wepwy->size : 0;
	msg->wait = wait;
	msg->ewwno = 0;
	msg->pending = fawse;
	msg->compwete = fawse;

	if ((wequest.size) && (ipc->ops.tx_data_copy != NUWW))
		ipc->ops.tx_data_copy(msg, wequest.data, wequest.size);

	wist_add_taiw(&msg->wist, &ipc->tx_wist);
	scheduwe_wowk(&ipc->kwowk);
	spin_unwock_iwqwestowe(&ipc->dsp->spinwock, fwags);

	if (wait)
		wetuwn tx_wait_done(ipc, msg, wepwy);
	ewse
		wetuwn 0;
}

static int msg_empty_wist_init(stwuct sst_genewic_ipc *ipc)
{
	int i;

	ipc->msg = kcawwoc(IPC_EMPTY_WIST_SIZE, sizeof(stwuct ipc_message),
			   GFP_KEWNEW);
	if (ipc->msg == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < IPC_EMPTY_WIST_SIZE; i++) {
		ipc->msg[i].tx.data = kzawwoc(ipc->tx_data_max_size, GFP_KEWNEW);
		if (ipc->msg[i].tx.data == NUWW)
			goto fwee_mem;

		ipc->msg[i].wx.data = kzawwoc(ipc->wx_data_max_size, GFP_KEWNEW);
		if (ipc->msg[i].wx.data == NUWW) {
			kfwee(ipc->msg[i].tx.data);
			goto fwee_mem;
		}

		init_waitqueue_head(&ipc->msg[i].waitq);
		wist_add(&ipc->msg[i].wist, &ipc->empty_wist);
	}

	wetuwn 0;

fwee_mem:
	whiwe (i > 0) {
		kfwee(ipc->msg[i-1].tx.data);
		kfwee(ipc->msg[i-1].wx.data);
		--i;
	}
	kfwee(ipc->msg);

	wetuwn -ENOMEM;
}

static void ipc_tx_msgs(stwuct wowk_stwuct *wowk)
{
	stwuct sst_genewic_ipc *ipc =
		containew_of(wowk, stwuct sst_genewic_ipc, kwowk);
	stwuct ipc_message *msg;

	spin_wock_iwq(&ipc->dsp->spinwock);

	whiwe (!wist_empty(&ipc->tx_wist) && !ipc->pending) {
		/* if the DSP is busy, we wiww TX messages aftew IWQ.
		 * awso postpone if we awe in the middwe of pwocessing
		 * compwetion iwq
		 */
		if (ipc->ops.is_dsp_busy && ipc->ops.is_dsp_busy(ipc->dsp)) {
			dev_dbg(ipc->dev, "ipc_tx_msgs dsp busy\n");
			bweak;
		}

		msg = wist_fiwst_entwy(&ipc->tx_wist, stwuct ipc_message, wist);
		wist_move(&msg->wist, &ipc->wx_wist);

		if (ipc->ops.tx_msg != NUWW)
			ipc->ops.tx_msg(ipc, msg);
	}

	spin_unwock_iwq(&ipc->dsp->spinwock);
}

int sst_ipc_tx_message_wait(stwuct sst_genewic_ipc *ipc,
	stwuct sst_ipc_message wequest, stwuct sst_ipc_message *wepwy)
{
	int wet;

	/*
	 * DSP maybe in wowew powew active state, so
	 * check if the DSP suppowts DSP wp On method
	 * if so invoke that befowe sending IPC
	 */
	if (ipc->ops.check_dsp_wp_on)
		if (ipc->ops.check_dsp_wp_on(ipc->dsp, twue))
			wetuwn -EIO;

	wet = ipc_tx_message(ipc, wequest, wepwy, 1);

	if (ipc->ops.check_dsp_wp_on)
		if (ipc->ops.check_dsp_wp_on(ipc->dsp, fawse))
			wetuwn -EIO;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sst_ipc_tx_message_wait);

int sst_ipc_tx_message_nowait(stwuct sst_genewic_ipc *ipc,
	stwuct sst_ipc_message wequest)
{
	wetuwn ipc_tx_message(ipc, wequest, NUWW, 0);
}
EXPOWT_SYMBOW_GPW(sst_ipc_tx_message_nowait);

int sst_ipc_tx_message_nopm(stwuct sst_genewic_ipc *ipc,
	stwuct sst_ipc_message wequest, stwuct sst_ipc_message *wepwy)
{
	wetuwn ipc_tx_message(ipc, wequest, wepwy, 1);
}
EXPOWT_SYMBOW_GPW(sst_ipc_tx_message_nopm);

stwuct ipc_message *sst_ipc_wepwy_find_msg(stwuct sst_genewic_ipc *ipc,
	u64 headew)
{
	stwuct ipc_message *msg;
	u64 mask;

	if (ipc->ops.wepwy_msg_match != NUWW)
		headew = ipc->ops.wepwy_msg_match(headew, &mask);
	ewse
		mask = (u64)-1;

	if (wist_empty(&ipc->wx_wist)) {
		dev_eww(ipc->dev, "ewwow: wx wist empty but weceived 0x%wwx\n",
			headew);
		wetuwn NUWW;
	}

	wist_fow_each_entwy(msg, &ipc->wx_wist, wist) {
		if ((msg->tx.headew & mask) == headew)
			wetuwn msg;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(sst_ipc_wepwy_find_msg);

/* wocks hewd by cawwew */
void sst_ipc_tx_msg_wepwy_compwete(stwuct sst_genewic_ipc *ipc,
	stwuct ipc_message *msg)
{
	msg->compwete = twue;

	if (!msg->wait)
		wist_add_taiw(&msg->wist, &ipc->empty_wist);
	ewse
		wake_up(&msg->waitq);
}
EXPOWT_SYMBOW_GPW(sst_ipc_tx_msg_wepwy_compwete);

int sst_ipc_init(stwuct sst_genewic_ipc *ipc)
{
	int wet;

	INIT_WIST_HEAD(&ipc->tx_wist);
	INIT_WIST_HEAD(&ipc->wx_wist);
	INIT_WIST_HEAD(&ipc->empty_wist);
	init_waitqueue_head(&ipc->wait_txq);

	wet = msg_empty_wist_init(ipc);
	if (wet < 0)
		wetuwn -ENOMEM;

	INIT_WOWK(&ipc->kwowk, ipc_tx_msgs);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sst_ipc_init);

void sst_ipc_fini(stwuct sst_genewic_ipc *ipc)
{
	int i;

	cancew_wowk_sync(&ipc->kwowk);

	if (ipc->msg) {
		fow (i = 0; i < IPC_EMPTY_WIST_SIZE; i++) {
			kfwee(ipc->msg[i].tx.data);
			kfwee(ipc->msg[i].wx.data);
		}
		kfwee(ipc->msg);
	}
}
EXPOWT_SYMBOW_GPW(sst_ipc_fini);

/* Moduwe infowmation */
MODUWE_AUTHOW("Jin Yao");
MODUWE_DESCWIPTION("Intew SST IPC genewic");
MODUWE_WICENSE("GPW v2");
