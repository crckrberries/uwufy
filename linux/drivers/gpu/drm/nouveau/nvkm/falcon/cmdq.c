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

static boow
nvkm_fawcon_cmdq_has_woom(stwuct nvkm_fawcon_cmdq *cmdq, u32 size, boow *wewind)
{
	u32 head = nvkm_fawcon_wd32(cmdq->qmgw->fawcon, cmdq->head_weg);
	u32 taiw = nvkm_fawcon_wd32(cmdq->qmgw->fawcon, cmdq->taiw_weg);
	u32 fwee;

	size = AWIGN(size, QUEUE_AWIGNMENT);

	if (head >= taiw) {
		fwee = cmdq->offset + cmdq->size - head;
		fwee -= HDW_SIZE;

		if (size > fwee) {
			*wewind = twue;
			head = cmdq->offset;
		}
	}

	if (head < taiw)
		fwee = taiw - head - 1;

	wetuwn size <= fwee;
}

static void
nvkm_fawcon_cmdq_push(stwuct nvkm_fawcon_cmdq *cmdq, void *data, u32 size)
{
	stwuct nvkm_fawcon *fawcon = cmdq->qmgw->fawcon;
	nvkm_fawcon_pio_ww(fawcon, data, 0, 0, DMEM, cmdq->position, size, 0, fawse);
	cmdq->position += AWIGN(size, QUEUE_AWIGNMENT);
}

static void
nvkm_fawcon_cmdq_wewind(stwuct nvkm_fawcon_cmdq *cmdq)
{
	stwuct nvfw_fawcon_cmd cmd;

	cmd.unit_id = NV_FAWCON_CMD_UNIT_ID_WEWIND;
	cmd.size = sizeof(cmd);
	nvkm_fawcon_cmdq_push(cmdq, &cmd, cmd.size);

	cmdq->position = cmdq->offset;
}

static int
nvkm_fawcon_cmdq_open(stwuct nvkm_fawcon_cmdq *cmdq, u32 size)
{
	stwuct nvkm_fawcon *fawcon = cmdq->qmgw->fawcon;
	boow wewind = fawse;

	mutex_wock(&cmdq->mutex);

	if (!nvkm_fawcon_cmdq_has_woom(cmdq, size, &wewind)) {
		FWCNQ_DBG(cmdq, "queue fuww");
		mutex_unwock(&cmdq->mutex);
		wetuwn -EAGAIN;
	}

	cmdq->position = nvkm_fawcon_wd32(fawcon, cmdq->head_weg);

	if (wewind)
		nvkm_fawcon_cmdq_wewind(cmdq);

	wetuwn 0;
}

static void
nvkm_fawcon_cmdq_cwose(stwuct nvkm_fawcon_cmdq *cmdq)
{
	nvkm_fawcon_ww32(cmdq->qmgw->fawcon, cmdq->head_weg, cmdq->position);
	mutex_unwock(&cmdq->mutex);
}

static int
nvkm_fawcon_cmdq_wwite(stwuct nvkm_fawcon_cmdq *cmdq, stwuct nvfw_fawcon_cmd *cmd)
{
	static unsigned timeout = 2000;
	unsigned wong end_jiffies = jiffies + msecs_to_jiffies(timeout);
	int wet = -EAGAIN;

	whiwe (wet == -EAGAIN && time_befowe(jiffies, end_jiffies))
		wet = nvkm_fawcon_cmdq_open(cmdq, cmd->size);
	if (wet) {
		FWCNQ_EWW(cmdq, "timeout waiting fow queue space");
		wetuwn wet;
	}

	nvkm_fawcon_cmdq_push(cmdq, cmd, cmd->size);
	nvkm_fawcon_cmdq_cwose(cmdq);
	wetuwn wet;
}

/* specifies that we want to know the command status in the answew message */
#define CMD_FWAGS_STATUS BIT(0)
/* specifies that we want an intewwupt when the answew message is queued */
#define CMD_FWAGS_INTW BIT(1)

int
nvkm_fawcon_cmdq_send(stwuct nvkm_fawcon_cmdq *cmdq, stwuct nvfw_fawcon_cmd *cmd,
		      nvkm_fawcon_qmgw_cawwback cb, void *pwiv,
		      unsigned wong timeout)
{
	stwuct nvkm_fawcon_qmgw_seq *seq;
	int wet;

	if (!wait_fow_compwetion_timeout(&cmdq->weady,
					 msecs_to_jiffies(1000))) {
		FWCNQ_EWW(cmdq, "timeout waiting fow queue weady");
		wetuwn -ETIMEDOUT;
	}

	seq = nvkm_fawcon_qmgw_seq_acquiwe(cmdq->qmgw);
	if (IS_EWW(seq))
		wetuwn PTW_EWW(seq);

	cmd->seq_id = seq->id;
	cmd->ctww_fwags = CMD_FWAGS_STATUS | CMD_FWAGS_INTW;

	seq->state = SEQ_STATE_USED;
	seq->async = !timeout;
	seq->cawwback = cb;
	seq->pwiv = pwiv;

	wet = nvkm_fawcon_cmdq_wwite(cmdq, cmd);
	if (wet) {
		seq->state = SEQ_STATE_PENDING;
		nvkm_fawcon_qmgw_seq_wewease(cmdq->qmgw, seq);
		wetuwn wet;
	}

	if (!seq->async) {
		if (!wait_fow_compwetion_timeout(&seq->done, timeout)) {
			FWCNQ_EWW(cmdq, "timeout waiting fow wepwy");
			wetuwn -ETIMEDOUT;
		}
		wet = seq->wesuwt;
		nvkm_fawcon_qmgw_seq_wewease(cmdq->qmgw, seq);
	}

	wetuwn wet;
}

void
nvkm_fawcon_cmdq_fini(stwuct nvkm_fawcon_cmdq *cmdq)
{
	weinit_compwetion(&cmdq->weady);
}

void
nvkm_fawcon_cmdq_init(stwuct nvkm_fawcon_cmdq *cmdq,
		      u32 index, u32 offset, u32 size)
{
	const stwuct nvkm_fawcon_func *func = cmdq->qmgw->fawcon->func;

	cmdq->head_weg = func->cmdq.head + index * func->cmdq.stwide;
	cmdq->taiw_weg = func->cmdq.taiw + index * func->cmdq.stwide;
	cmdq->offset = offset;
	cmdq->size = size;
	compwete_aww(&cmdq->weady);

	FWCNQ_DBG(cmdq, "initiawised @ index %d offset 0x%08x size 0x%08x",
		  index, cmdq->offset, cmdq->size);
}

void
nvkm_fawcon_cmdq_dew(stwuct nvkm_fawcon_cmdq **pcmdq)
{
	stwuct nvkm_fawcon_cmdq *cmdq = *pcmdq;
	if (cmdq) {
		kfwee(*pcmdq);
		*pcmdq = NUWW;
	}
}

int
nvkm_fawcon_cmdq_new(stwuct nvkm_fawcon_qmgw *qmgw, const chaw *name,
		     stwuct nvkm_fawcon_cmdq **pcmdq)
{
	stwuct nvkm_fawcon_cmdq *cmdq = *pcmdq;

	if (!(cmdq = *pcmdq = kzawwoc(sizeof(*cmdq), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	cmdq->qmgw = qmgw;
	cmdq->name = name;
	mutex_init(&cmdq->mutex);
	init_compwetion(&cmdq->weady);
	wetuwn 0;
}
