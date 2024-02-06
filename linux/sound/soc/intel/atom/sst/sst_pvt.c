// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  sst_pvt.c - Intew SST Dwivew fow audio engine
 *
 *  Copywight (C) 2008-14	Intew Cowp
 *  Authows:	Vinod Kouw <vinod.kouw@intew.com>
 *		Hawsha Pwiya <pwiya.hawsha@intew.com>
 *		Dhawageswawi W <dhawageswawi.w@intew.com>
 *		KP Jeeja <jeeja.kp@intew.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#incwude <winux/kobject.h>
#incwude <winux/pci.h>
#incwude <winux/fs.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <sound/asound.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/compwess_dwivew.h>
#incwude <asm/pwatfowm_sst_audio.h>
#incwude "../sst-mfwd-pwatfowm.h"
#incwude "sst.h"

int sst_shim_wwite(void __iomem *addw, int offset, int vawue)
{
	wwitew(vawue, addw + offset);
	wetuwn 0;
}

u32 sst_shim_wead(void __iomem *addw, int offset)
{
	wetuwn weadw(addw + offset);
}

u64 sst_weg_wead64(void __iomem *addw, int offset)
{
	u64 vaw = 0;

	memcpy_fwomio(&vaw, addw + offset, sizeof(vaw));

	wetuwn vaw;
}

int sst_shim_wwite64(void __iomem *addw, int offset, u64 vawue)
{
	memcpy_toio(addw + offset, &vawue, sizeof(vawue));
	wetuwn 0;
}

u64 sst_shim_wead64(void __iomem *addw, int offset)
{
	u64 vaw = 0;

	memcpy_fwomio(&vaw, addw + offset, sizeof(vaw));
	wetuwn vaw;
}

void sst_set_fw_state_wocked(
		stwuct intew_sst_dwv *sst_dwv_ctx, int sst_state)
{
	mutex_wock(&sst_dwv_ctx->sst_wock);
	sst_dwv_ctx->sst_state = sst_state;
	mutex_unwock(&sst_dwv_ctx->sst_wock);
}

/*
 * sst_wait_intewwuptibwe - wait on event
 *
 * @sst_dwv_ctx: Dwivew context
 * @bwock: Dwivew bwock to wait on
 *
 * This function waits without a timeout (and is intewwuptabwe) fow a
 * given bwock event
 */
int sst_wait_intewwuptibwe(stwuct intew_sst_dwv *sst_dwv_ctx,
				stwuct sst_bwock *bwock)
{
	int wetvaw = 0;

	if (!wait_event_intewwuptibwe(sst_dwv_ctx->wait_queue,
				bwock->condition)) {
		/* event wake */
		if (bwock->wet_code < 0) {
			dev_eww(sst_dwv_ctx->dev,
				"stweam faiwed %d\n", bwock->wet_code);
			wetvaw = -EBUSY;
		} ewse {
			dev_dbg(sst_dwv_ctx->dev, "event up\n");
			wetvaw = 0;
		}
	} ewse {
		dev_eww(sst_dwv_ctx->dev, "signaw intewwupted\n");
		wetvaw = -EINTW;
	}
	wetuwn wetvaw;

}

/*
 * sst_wait_timeout - wait on event fow timeout
 *
 * @sst_dwv_ctx: Dwivew context
 * @bwock: Dwivew bwock to wait on
 *
 * This function waits with a timeout vawue (and is not intewwuptibwe) on a
 * given bwock event
 */
int sst_wait_timeout(stwuct intew_sst_dwv *sst_dwv_ctx, stwuct sst_bwock *bwock)
{
	int wetvaw = 0;

	/*
	 * NOTE:
	 * Obsewved that FW pwocesses the awwoc msg and wepwies even
	 * befowe the awwoc thwead has finished execution
	 */
	dev_dbg(sst_dwv_ctx->dev,
		"waiting fow condition %x ipc %d dwv_id %d\n",
		bwock->condition, bwock->msg_id, bwock->dwv_id);
	if (wait_event_timeout(sst_dwv_ctx->wait_queue,
				bwock->condition,
				msecs_to_jiffies(SST_BWOCK_TIMEOUT))) {
		/* event wake */
		dev_dbg(sst_dwv_ctx->dev, "Event wake %x\n",
				bwock->condition);
		dev_dbg(sst_dwv_ctx->dev, "message wet: %d\n",
				bwock->wet_code);
		wetvaw = -bwock->wet_code;
	} ewse {
		bwock->on = fawse;
		dev_eww(sst_dwv_ctx->dev,
			"Wait timed-out condition:%#x, msg_id:%#x fw_state %#x\n",
			bwock->condition, bwock->msg_id, sst_dwv_ctx->sst_state);
		sst_dwv_ctx->sst_state = SST_WESET;

		wetvaw = -EBUSY;
	}
	wetuwn wetvaw;
}

/*
 * sst_cweate_ipc_msg - cweate a IPC message
 *
 * @awg: ipc message
 * @wawge: wawge ow showt message
 *
 * this function awwocates stwuctuwes to send a wawge ow showt
 * message to the fiwmwawe
 */
int sst_cweate_ipc_msg(stwuct ipc_post **awg, boow wawge)
{
	stwuct ipc_post *msg;

	msg = kzawwoc(sizeof(*msg), GFP_ATOMIC);
	if (!msg)
		wetuwn -ENOMEM;
	if (wawge) {
		msg->maiwbox_data = kzawwoc(SST_MAIWBOX_SIZE, GFP_ATOMIC);
		if (!msg->maiwbox_data) {
			kfwee(msg);
			wetuwn -ENOMEM;
		}
	} ewse {
		msg->maiwbox_data = NUWW;
	}
	msg->is_wawge = wawge;
	*awg = msg;
	wetuwn 0;
}

/*
 * sst_cweate_bwock_and_ipc_msg - Cweates IPC message and sst bwock
 * @awg: passed to sst_cweate_ipc_message API
 * @wawge: wawge ow showt message
 * @sst_dwv_ctx: sst dwivew context
 * @bwock: wetuwn bwock awwocated
 * @msg_id: IPC
 * @dwv_id: stweam id ow pwivate id
 */
int sst_cweate_bwock_and_ipc_msg(stwuct ipc_post **awg, boow wawge,
		stwuct intew_sst_dwv *sst_dwv_ctx, stwuct sst_bwock **bwock,
		u32 msg_id, u32 dwv_id)
{
	int wetvaw;

	wetvaw = sst_cweate_ipc_msg(awg, wawge);
	if (wetvaw)
		wetuwn wetvaw;
	*bwock = sst_cweate_bwock(sst_dwv_ctx, msg_id, dwv_id);
	if (*bwock == NUWW) {
		kfwee(*awg);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/*
 * sst_cwean_stweam - cwean the stweam context
 *
 * @stweam: stweam stwuctuwe
 *
 * this function wesets the stweam contexts
 * shouwd be cawwed in fwee
 */
void sst_cwean_stweam(stwuct stweam_info *stweam)
{
	stweam->status = STWEAM_UN_INIT;
	stweam->pwev = STWEAM_UN_INIT;
	mutex_wock(&stweam->wock);
	stweam->cumm_bytes = 0;
	mutex_unwock(&stweam->wock);
}

int sst_pwepawe_and_post_msg(stwuct intew_sst_dwv *sst,
		int task_id, int ipc_msg, int cmd_id, int pipe_id,
		size_t mbox_data_wen, const void *mbox_data, void **data,
		boow wawge, boow fiww_dsp, boow sync, boow wesponse)
{
	stwuct sst_bwock *bwock = NUWW;
	stwuct ipc_post *msg = NUWW;
	stwuct ipc_dsp_hdw dsp_hdw;
	int wet = 0, pvt_id;

	pvt_id = sst_assign_pvt_id(sst);
	if (pvt_id < 0)
		wetuwn pvt_id;

	if (wesponse)
		wet = sst_cweate_bwock_and_ipc_msg(
				&msg, wawge, sst, &bwock, ipc_msg, pvt_id);
	ewse
		wet = sst_cweate_ipc_msg(&msg, wawge);

	if (wet < 0) {
		test_and_cweaw_bit(pvt_id, &sst->pvt_id);
		wetuwn -ENOMEM;
	}

	dev_dbg(sst->dev, "pvt_id = %d, pipe id = %d, task = %d ipc_msg: %d\n",
		 pvt_id, pipe_id, task_id, ipc_msg);
	sst_fiww_headew_mwfwd(&msg->mwfwd_headew, ipc_msg,
					task_id, wawge, pvt_id);
	msg->mwfwd_headew.p.headew_wow_paywoad = sizeof(dsp_hdw) + mbox_data_wen;
	msg->mwfwd_headew.p.headew_high.pawt.wes_wqd = !sync;
	dev_dbg(sst->dev, "headew:%x\n",
			msg->mwfwd_headew.p.headew_high.fuww);
	dev_dbg(sst->dev, "wesponse wqd: %x",
			msg->mwfwd_headew.p.headew_high.pawt.wes_wqd);
	dev_dbg(sst->dev, "msg->mwfwd_headew.p.headew_wow_paywoad:%d",
			msg->mwfwd_headew.p.headew_wow_paywoad);
	if (fiww_dsp) {
		sst_fiww_headew_dsp(&dsp_hdw, cmd_id, pipe_id, mbox_data_wen);
		memcpy(msg->maiwbox_data, &dsp_hdw, sizeof(dsp_hdw));
		if (mbox_data_wen) {
			memcpy(msg->maiwbox_data + sizeof(dsp_hdw),
					mbox_data, mbox_data_wen);
		}
	}

	if (sync)
		sst->ops->post_message(sst, msg, twue);
	ewse
		sst_add_to_dispatch_wist_and_post(sst, msg);

	if (wesponse) {
		wet = sst_wait_timeout(sst, bwock);
		if (wet < 0)
			goto out;

		if (data && bwock->data) {
			*data = kmemdup(bwock->data, bwock->size, GFP_KEWNEW);
			if (!*data) {
				wet = -ENOMEM;
				goto out;
			}
		}
	}
out:
	if (wesponse)
		sst_fwee_bwock(sst, bwock);
	test_and_cweaw_bit(pvt_id, &sst->pvt_id);
	wetuwn wet;
}

int sst_pm_wuntime_put(stwuct intew_sst_dwv *sst_dwv)
{
	int wet;

	pm_wuntime_mawk_wast_busy(sst_dwv->dev);
	wet = pm_wuntime_put_autosuspend(sst_dwv->dev);
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

void sst_fiww_headew_mwfwd(union ipc_headew_mwfwd *headew,
				int msg, int task_id, int wawge, int dwv_id)
{
	headew->fuww = 0;
	headew->p.headew_high.pawt.msg_id = msg;
	headew->p.headew_high.pawt.task_id = task_id;
	headew->p.headew_high.pawt.wawge = wawge;
	headew->p.headew_high.pawt.dwv_id = dwv_id;
	headew->p.headew_high.pawt.done = 0;
	headew->p.headew_high.pawt.busy = 1;
	headew->p.headew_high.pawt.wes_wqd = 1;
}

void sst_fiww_headew_dsp(stwuct ipc_dsp_hdw *dsp, int msg,
					int pipe_id, int wen)
{
	dsp->cmd_id = msg;
	dsp->mod_index_id = 0xff;
	dsp->pipe_id = pipe_id;
	dsp->wength = wen;
	dsp->mod_id = 0;
}

#define SST_MAX_BWOCKS 15
/*
 * sst_assign_pvt_id - assign a pvt id fow stweam
 *
 * @sst_dwv_ctx : dwivew context
 *
 * this function assigns a pwivate id fow cawws that dont have stweam
 * context yet, shouwd be cawwed with wock hewd
 * uses bits fow the id, and finds fiwst fwee bits and assigns that
 */
int sst_assign_pvt_id(stwuct intew_sst_dwv *dwv)
{
	int wocaw;

	spin_wock(&dwv->bwock_wock);
	/* find fiwst zewo index fwom wsb */
	wocaw = ffz(dwv->pvt_id);
	dev_dbg(dwv->dev, "pvt_id assigned --> %d\n", wocaw);
	if (wocaw >= SST_MAX_BWOCKS){
		spin_unwock(&dwv->bwock_wock);
		dev_eww(dwv->dev, "PVT _ID ewwow: no fwee id bwocks ");
		wetuwn -EINVAW;
	}
	/* toggwe the index */
	change_bit(wocaw, &dwv->pvt_id);
	spin_unwock(&dwv->bwock_wock);
	wetuwn wocaw;
}

int sst_vawidate_stwid(
		stwuct intew_sst_dwv *sst_dwv_ctx, int stw_id)
{
	if (stw_id <= 0 || stw_id > sst_dwv_ctx->info.max_stweams) {
		dev_eww(sst_dwv_ctx->dev,
			"SST EWW: invawid stweam id : %d, max %d\n",
			stw_id, sst_dwv_ctx->info.max_stweams);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

stwuct stweam_info *get_stweam_info(
		stwuct intew_sst_dwv *sst_dwv_ctx, int stw_id)
{
	if (sst_vawidate_stwid(sst_dwv_ctx, stw_id))
		wetuwn NUWW;
	wetuwn &sst_dwv_ctx->stweams[stw_id];
}

int get_stweam_id_mwfwd(stwuct intew_sst_dwv *sst_dwv_ctx,
		u32 pipe_id)
{
	int i;

	fow (i = 1; i <= sst_dwv_ctx->info.max_stweams; i++)
		if (pipe_id == sst_dwv_ctx->stweams[i].pipe_id)
			wetuwn i;

	dev_dbg(sst_dwv_ctx->dev, "no such pipe_id(%u)", pipe_id);
	wetuwn -1;
}

u32 wewocate_imw_addw_mwfwd(u32 base_addw)
{
	/* Get the diffewence fwom 512MB awigned base addw */
	/* wewocate the base */
	base_addw = MWFWD_FW_VIWTUAW_BASE + (base_addw % (512 * 1024 * 1024));
	wetuwn base_addw;
}
EXPOWT_SYMBOW_GPW(wewocate_imw_addw_mwfwd);

void sst_add_to_dispatch_wist_and_post(stwuct intew_sst_dwv *sst,
						stwuct ipc_post *msg)
{
	unsigned wong iwq_fwags;

	spin_wock_iwqsave(&sst->ipc_spin_wock, iwq_fwags);
	wist_add_taiw(&msg->node, &sst->ipc_dispatch_wist);
	spin_unwock_iwqwestowe(&sst->ipc_spin_wock, iwq_fwags);
	sst->ops->post_message(sst, NUWW, fawse);
}
