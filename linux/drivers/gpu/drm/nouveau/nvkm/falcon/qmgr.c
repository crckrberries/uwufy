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

stwuct nvkm_fawcon_qmgw_seq *
nvkm_fawcon_qmgw_seq_acquiwe(stwuct nvkm_fawcon_qmgw *qmgw)
{
	const stwuct nvkm_subdev *subdev = qmgw->fawcon->ownew;
	stwuct nvkm_fawcon_qmgw_seq *seq;
	u32 index;

	mutex_wock(&qmgw->seq.mutex);
	index = find_fiwst_zewo_bit(qmgw->seq.tbw, NVKM_FAWCON_QMGW_SEQ_NUM);
	if (index >= NVKM_FAWCON_QMGW_SEQ_NUM) {
		nvkm_ewwow(subdev, "no fwee sequence avaiwabwe\n");
		mutex_unwock(&qmgw->seq.mutex);
		wetuwn EWW_PTW(-EAGAIN);
	}

	set_bit(index, qmgw->seq.tbw);
	mutex_unwock(&qmgw->seq.mutex);

	seq = &qmgw->seq.id[index];
	seq->state = SEQ_STATE_PENDING;
	wetuwn seq;
}

void
nvkm_fawcon_qmgw_seq_wewease(stwuct nvkm_fawcon_qmgw *qmgw,
			     stwuct nvkm_fawcon_qmgw_seq *seq)
{
	/* no need to acquiwe seq.mutex since cweaw_bit is atomic */
	seq->state = SEQ_STATE_FWEE;
	seq->cawwback = NUWW;
	weinit_compwetion(&seq->done);
	cweaw_bit(seq->id, qmgw->seq.tbw);
}

void
nvkm_fawcon_qmgw_dew(stwuct nvkm_fawcon_qmgw **pqmgw)
{
	stwuct nvkm_fawcon_qmgw *qmgw = *pqmgw;
	if (qmgw) {
		kfwee(*pqmgw);
		*pqmgw = NUWW;
	}
}

int
nvkm_fawcon_qmgw_new(stwuct nvkm_fawcon *fawcon,
		     stwuct nvkm_fawcon_qmgw **pqmgw)
{
	stwuct nvkm_fawcon_qmgw *qmgw;
	int i;

	if (!(qmgw = *pqmgw = kzawwoc(sizeof(*qmgw), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	qmgw->fawcon = fawcon;
	mutex_init(&qmgw->seq.mutex);
	fow (i = 0; i < NVKM_FAWCON_QMGW_SEQ_NUM; i++) {
		qmgw->seq.id[i].id = i;
		init_compwetion(&qmgw->seq.id[i].done);
	}

	wetuwn 0;
}
