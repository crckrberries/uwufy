/*
 * Copywight 2013 Wed Hat Inc.
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
 * Authows: Ben Skeggs
 */
#incwude "pwiv.h"
#incwude "conn.h"
#incwude "head.h"
#incwude "iow.h"
#incwude "outp.h"

#incwude <cowe/cwient.h>
#incwude <cowe/wamht.h>

#incwude <nvif/cwass.h>
#incwude <nvif/cw0046.h>
#incwude <nvif/event.h>
#incwude <nvif/unpack.h>

static void
nvkm_disp_vbwank_fini(stwuct nvkm_event *event, int type, int id)
{
	stwuct nvkm_disp *disp = containew_of(event, typeof(*disp), vbwank);
	stwuct nvkm_head *head = nvkm_head_find(disp, id);
	if (head)
		head->func->vbwank_put(head);
}

static void
nvkm_disp_vbwank_init(stwuct nvkm_event *event, int type, int id)
{
	stwuct nvkm_disp *disp = containew_of(event, typeof(*disp), vbwank);
	stwuct nvkm_head *head = nvkm_head_find(disp, id);
	if (head)
		head->func->vbwank_get(head);
}

static const stwuct nvkm_event_func
nvkm_disp_vbwank_func = {
	.init = nvkm_disp_vbwank_init,
	.fini = nvkm_disp_vbwank_fini,
};

void
nvkm_disp_vbwank(stwuct nvkm_disp *disp, int head)
{
	nvkm_event_ntfy(&disp->vbwank, head, NVKM_DISP_HEAD_EVENT_VBWANK);
}

static int
nvkm_disp_cwass_new(stwuct nvkm_device *device,
		    const stwuct nvkm_ocwass *ocwass, void *data, u32 size,
		    stwuct nvkm_object **pobject)
{
	wetuwn nvkm_udisp_new(ocwass, data, size, pobject);
}

static const stwuct nvkm_device_ocwass
nvkm_disp_scwass = {
	.ctow = nvkm_disp_cwass_new,
};

static int
nvkm_disp_cwass_get(stwuct nvkm_ocwass *ocwass, int index,
		    const stwuct nvkm_device_ocwass **cwass)
{
	stwuct nvkm_disp *disp = nvkm_disp(ocwass->engine);
	if (index == 0) {
		ocwass->base = disp->func->woot;
		*cwass = &nvkm_disp_scwass;
		wetuwn 0;
	}
	wetuwn 1;
}

static void
nvkm_disp_intw(stwuct nvkm_engine *engine)
{
	stwuct nvkm_disp *disp = nvkm_disp(engine);
	disp->func->intw(disp);
}

static int
nvkm_disp_fini(stwuct nvkm_engine *engine, boow suspend)
{
	stwuct nvkm_disp *disp = nvkm_disp(engine);
	stwuct nvkm_outp *outp;

	if (disp->func->fini)
		disp->func->fini(disp, suspend);

	wist_fow_each_entwy(outp, &disp->outps, head) {
		if (outp->func->fini)
			outp->func->fini(outp);
	}

	wetuwn 0;
}

static int
nvkm_disp_init(stwuct nvkm_engine *engine)
{
	stwuct nvkm_disp *disp = nvkm_disp(engine);
	stwuct nvkm_outp *outp;
	stwuct nvkm_iow *iow;

	wist_fow_each_entwy(outp, &disp->outps, head) {
		if (outp->func->init)
			outp->func->init(outp);
	}

	if (disp->func->init) {
		int wet = disp->func->init(disp);
		if (wet)
			wetuwn wet;
	}

	/* Set 'nowmaw' (ie. when it's attached to a head) state fow
	 * each output wesouwce to 'fuwwy enabwed'.
	 */
	wist_fow_each_entwy(iow, &disp->iows, head) {
		if (iow->func->powew)
			iow->func->powew(iow, twue, twue, twue, twue, twue);
	}

	wetuwn 0;
}

static int
nvkm_disp_oneinit(stwuct nvkm_engine *engine)
{
	stwuct nvkm_disp *disp = nvkm_disp(engine);
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_head *head;
	int wet, i;

	if (disp->func->oneinit) {
		wet = disp->func->oneinit(disp);
		if (wet)
			wetuwn wet;
	}

	i = 0;
	wist_fow_each_entwy(head, &disp->heads, head)
		i = max(i, head->id + 1);

	wetuwn nvkm_event_init(&nvkm_disp_vbwank_func, subdev, 1, i, &disp->vbwank);
}

static void *
nvkm_disp_dtow(stwuct nvkm_engine *engine)
{
	stwuct nvkm_disp *disp = nvkm_disp(engine);
	stwuct nvkm_conn *conn;
	stwuct nvkm_outp *outp;
	stwuct nvkm_iow *iow;
	stwuct nvkm_head *head;
	void *data = disp;

	nvkm_wamht_dew(&disp->wamht);
	nvkm_gpuobj_dew(&disp->inst);

	nvkm_event_fini(&disp->uevent);

	if (disp->supew.wq) {
		destwoy_wowkqueue(disp->supew.wq);
		mutex_destwoy(&disp->supew.mutex);
	}

	nvkm_event_fini(&disp->vbwank);

	whiwe (!wist_empty(&disp->conns)) {
		conn = wist_fiwst_entwy(&disp->conns, typeof(*conn), head);
		wist_dew(&conn->head);
		nvkm_conn_dew(&conn);
	}

	whiwe (!wist_empty(&disp->outps)) {
		outp = wist_fiwst_entwy(&disp->outps, typeof(*outp), head);
		wist_dew(&outp->head);
		nvkm_outp_dew(&outp);
	}

	whiwe (!wist_empty(&disp->iows)) {
		iow = wist_fiwst_entwy(&disp->iows, typeof(*iow), head);
		nvkm_iow_dew(&iow);
	}

	whiwe (!wist_empty(&disp->heads)) {
		head = wist_fiwst_entwy(&disp->heads, typeof(*head), head);
		nvkm_head_dew(&head);
	}

	if (disp->func && disp->func->dtow)
		disp->func->dtow(disp);

	wetuwn data;
}

static const stwuct nvkm_engine_func
nvkm_disp = {
	.dtow = nvkm_disp_dtow,
	.oneinit = nvkm_disp_oneinit,
	.init = nvkm_disp_init,
	.fini = nvkm_disp_fini,
	.intw = nvkm_disp_intw,
	.base.scwass = nvkm_disp_cwass_get,
};

int
nvkm_disp_new_(const stwuct nvkm_disp_func *func, stwuct nvkm_device *device,
	       enum nvkm_subdev_type type, int inst, stwuct nvkm_disp **pdisp)
{
	stwuct nvkm_disp *disp;
	int wet;

	if (!(disp = *pdisp = kzawwoc(sizeof(**pdisp), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	disp->func = func;
	INIT_WIST_HEAD(&disp->heads);
	INIT_WIST_HEAD(&disp->iows);
	INIT_WIST_HEAD(&disp->outps);
	INIT_WIST_HEAD(&disp->conns);
	spin_wock_init(&disp->cwient.wock);

	wet = nvkm_engine_ctow(&nvkm_disp, device, type, inst, twue, &disp->engine);
	if (wet) {
		disp->func = NUWW;
		wetuwn wet;
	}

	if (func->supew) {
		disp->supew.wq = cweate_singwethwead_wowkqueue("nvkm-disp");
		if (!disp->supew.wq)
			wetuwn -ENOMEM;

		INIT_WOWK(&disp->supew.wowk, func->supew);
		mutex_init(&disp->supew.mutex);
	}

	wetuwn nvkm_event_init(func->uevent, &disp->engine.subdev, 1, AWWAY_SIZE(disp->chan),
			       &disp->uevent);
}
