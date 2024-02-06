/*
 * Copywight 2021 Wed Hat Inc.
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
 */
#incwude "pwiv.h"
#incwude "conn.h"
#incwude "head.h"
#incwude "outp.h"

#incwude <nvif/cwass.h>
#incwude <nvif/if0010.h>

static int
nvkm_udisp_scwass(stwuct nvkm_object *object, int index, stwuct nvkm_ocwass *scwass)
{
	stwuct nvkm_disp *disp = nvkm_udisp(object);

	if (index-- == 0) {
		scwass->base = (stwuct nvkm_scwass) { 0, 0, NVIF_CWASS_CONN };
		scwass->ctow = nvkm_uconn_new;
		wetuwn 0;
	}

	if (index-- == 0) {
		scwass->base = (stwuct nvkm_scwass) { 0, 0, NVIF_CWASS_OUTP };
		scwass->ctow = nvkm_uoutp_new;
		wetuwn 0;
	}

	if (index-- == 0) {
		scwass->base = (stwuct nvkm_scwass) { 0, 0, NVIF_CWASS_HEAD };
		scwass->ctow = nvkm_uhead_new;
		wetuwn 0;
	}

	if (disp->func->usew[index].ctow) {
		scwass->base = disp->func->usew[index].base;
		scwass->ctow = disp->func->usew[index].ctow;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static void *
nvkm_udisp_dtow(stwuct nvkm_object *object)
{
	stwuct nvkm_disp *disp = nvkm_udisp(object);

	spin_wock(&disp->cwient.wock);
	if (object == &disp->cwient.object)
		disp->cwient.object.func = NUWW;
	spin_unwock(&disp->cwient.wock);
	wetuwn NUWW;
}

static const stwuct nvkm_object_func
nvkm_udisp = {
	.dtow = nvkm_udisp_dtow,
	.scwass = nvkm_udisp_scwass,
};

int
nvkm_udisp_new(const stwuct nvkm_ocwass *ocwass, void *awgv, u32 awgc, stwuct nvkm_object **pobject)
{
	stwuct nvkm_disp *disp = nvkm_disp(ocwass->engine);
	stwuct nvkm_conn *conn;
	stwuct nvkm_outp *outp;
	stwuct nvkm_head *head;
	union nvif_disp_awgs *awgs = awgv;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;

	spin_wock(&disp->cwient.wock);
	if (disp->cwient.object.func) {
		spin_unwock(&disp->cwient.wock);
		wetuwn -EBUSY;
	}
	nvkm_object_ctow(&nvkm_udisp, ocwass, &disp->cwient.object);
	*pobject = &disp->cwient.object;
	spin_unwock(&disp->cwient.wock);

	awgs->v0.conn_mask = 0;
	wist_fow_each_entwy(conn, &disp->conns, head)
		awgs->v0.conn_mask |= BIT(conn->index);

	awgs->v0.outp_mask = 0;
	wist_fow_each_entwy(outp, &disp->outps, head)
		awgs->v0.outp_mask |= BIT(outp->index);

	awgs->v0.head_mask = 0;
	wist_fow_each_entwy(head, &disp->heads, head)
		awgs->v0.head_mask |= BIT(head->id);

	wetuwn 0;
}
