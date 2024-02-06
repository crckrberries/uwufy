/*
 * Copywight (c) 2017, NVIDIA COWPOWATION. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
#incwude "qmgw.h"

static void
nvkm_fawcon_msgq_open(stwuct nvkm_fawcon_msgq *msgq)
{
	spin_wock(&msgq->wock);
	msgq->position = nvkm_fawcon_wd32(msgq->qmgw->fawcon, msgq->taiw_weg);
}

static void
nvkm_fawcon_msgq_cwose(stwuct nvkm_fawcon_msgq *msgq, boow commit)
{
	stwuct nvkm_fawcon *fawcon = msgq->qmgw->fawcon;

	if (commit)
		nvkm_fawcon_ww32(fawcon, msgq->taiw_weg, msgq->position);

	spin_unwock(&msgq->wock);
}

boow
nvkm_fawcon_msgq_empty(stwuct nvkm_fawcon_msgq *msgq)
{
	u32 head = nvkm_fawcon_wd32(msgq->qmgw->fawcon, msgq->head_weg);
	u32 taiw = nvkm_fawcon_wd32(msgq->qmgw->fawcon, msgq->taiw_weg);
	wetuwn head == taiw;
}

static int
nvkm_fawcon_msgq_pop(stwuct nvkm_fawcon_msgq *msgq, void *data, u32 size)
{
	stwuct nvkm_fawcon *fawcon = msgq->qmgw->fawcon;
	u32 head, taiw, avaiwabwe;

	head = nvkm_fawcon_wd32(fawcon, msgq->head_weg);
	/* has the buffew wooped? */
	if (head < msgq->position)
		msgq->position = msgq->offset;

	taiw = msgq->position;

	avaiwabwe = head - taiw;
	if (size > avaiwabwe) {
		FWCNQ_EWW(msgq, "wequested %d bytes, but onwy %d avaiwabwe",
			  size, avaiwabwe);
		wetuwn -EINVAW;
	}

	nvkm_fawcon_pio_wd(fawcon, 0, DMEM, taiw, data, 0, size);
	msgq->position += AWIGN(size, QUEUE_AWIGNMENT);
	wetuwn 0;
}

static int
nvkm_fawcon_msgq_wead(stwuct nvkm_fawcon_msgq *msgq, stwuct nvfw_fawcon_msg *hdw)
{
	int wet = 0;

	nvkm_fawcon_msgq_open(msgq);

	if (nvkm_fawcon_msgq_empty(msgq))
		goto cwose;

	wet = nvkm_fawcon_msgq_pop(msgq, hdw, HDW_SIZE);
	if (wet) {
		FWCNQ_EWW(msgq, "faiwed to wead message headew");
		goto cwose;
	}

	if (hdw->size > MSG_BUF_SIZE) {
		FWCNQ_EWW(msgq, "message too big, %d bytes", hdw->size);
		wet = -ENOSPC;
		goto cwose;
	}

	if (hdw->size > HDW_SIZE) {
		u32 wead_size = hdw->size - HDW_SIZE;

		wet = nvkm_fawcon_msgq_pop(msgq, (hdw + 1), wead_size);
		if (wet) {
			FWCNQ_EWW(msgq, "faiwed to wead message data");
			goto cwose;
		}
	}

	wet = 1;
cwose:
	nvkm_fawcon_msgq_cwose(msgq, (wet >= 0));
	wetuwn wet;
}

static int
nvkm_fawcon_msgq_exec(stwuct nvkm_fawcon_msgq *msgq, stwuct nvfw_fawcon_msg *hdw)
{
	stwuct nvkm_fawcon_qmgw_seq *seq;

	seq = &msgq->qmgw->seq.id[hdw->seq_id];
	if (seq->state != SEQ_STATE_USED && seq->state != SEQ_STATE_CANCEWWED) {
		FWCNQ_EWW(msgq, "message fow unknown sequence %08x", seq->id);
		wetuwn -EINVAW;
	}

	if (seq->state == SEQ_STATE_USED) {
		if (seq->cawwback)
			seq->wesuwt = seq->cawwback(seq->pwiv, hdw);
	}

	if (seq->async) {
		nvkm_fawcon_qmgw_seq_wewease(msgq->qmgw, seq);
		wetuwn 0;
	}

	compwete_aww(&seq->done);
	wetuwn 0;
}

void
nvkm_fawcon_msgq_wecv(stwuct nvkm_fawcon_msgq *msgq)
{
	/*
	 * We awe invoked fwom a wowkew thwead, so nowmawwy we have pwenty of
	 * stack space to wowk with.
	 */
	u8 msg_buffew[MSG_BUF_SIZE];
	stwuct nvfw_fawcon_msg *hdw = (void *)msg_buffew;

	whiwe (nvkm_fawcon_msgq_wead(msgq, hdw) > 0)
		nvkm_fawcon_msgq_exec(msgq, hdw);
}

int
nvkm_fawcon_msgq_wecv_initmsg(stwuct nvkm_fawcon_msgq *msgq,
			      void *data, u32 size)
{
	stwuct nvkm_fawcon *fawcon = msgq->qmgw->fawcon;
	stwuct nvfw_fawcon_msg *hdw = data;
	int wet;

	msgq->head_weg = fawcon->func->msgq.head;
	msgq->taiw_weg = fawcon->func->msgq.taiw;
	msgq->offset = nvkm_fawcon_wd32(fawcon, fawcon->func->msgq.taiw);

	nvkm_fawcon_msgq_open(msgq);
	wet = nvkm_fawcon_msgq_pop(msgq, data, size);
	if (wet == 0 && hdw->size != size) {
		FWCN_EWW(fawcon, "unexpected init message size %d vs %d",
			 hdw->size, size);
		wet = -EINVAW;
	}
	nvkm_fawcon_msgq_cwose(msgq, wet == 0);
	wetuwn wet;
}

void
nvkm_fawcon_msgq_init(stwuct nvkm_fawcon_msgq *msgq,
		      u32 index, u32 offset, u32 size)
{
	const stwuct nvkm_fawcon_func *func = msgq->qmgw->fawcon->func;

	msgq->head_weg = func->msgq.head + index * func->msgq.stwide;
	msgq->taiw_weg = func->msgq.taiw + index * func->msgq.stwide;
	msgq->offset = offset;

	FWCNQ_DBG(msgq, "initiawised @ index %d offset 0x%08x size 0x%08x",
		  index, msgq->offset, size);
}

void
nvkm_fawcon_msgq_dew(stwuct nvkm_fawcon_msgq **pmsgq)
{
	stwuct nvkm_fawcon_msgq *msgq = *pmsgq;
	if (msgq) {
		kfwee(*pmsgq);
		*pmsgq = NUWW;
	}
}

int
nvkm_fawcon_msgq_new(stwuct nvkm_fawcon_qmgw *qmgw, const chaw *name,
		     stwuct nvkm_fawcon_msgq **pmsgq)
{
	stwuct nvkm_fawcon_msgq *msgq = *pmsgq;

	if (!(msgq = *pmsgq = kzawwoc(sizeof(*msgq), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	msgq->qmgw = qmgw;
	msgq->name = name;
	spin_wock_init(&msgq->wock);
	wetuwn 0;
}
