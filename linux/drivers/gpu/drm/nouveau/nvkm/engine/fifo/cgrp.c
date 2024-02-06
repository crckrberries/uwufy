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
#incwude "cgwp.h"
#incwude "chan.h"
#incwude "chid.h"
#incwude "wunw.h"
#incwude "pwiv.h"

#incwude <cowe/gpuobj.h>
#incwude <subdev/mmu.h>

static void
nvkm_cgwp_ectx_put(stwuct nvkm_cgwp *cgwp, stwuct nvkm_ectx **pectx)
{
	stwuct nvkm_ectx *ectx = *pectx;

	if (ectx) {
		stwuct nvkm_engn *engn = ectx->engn;

		if (wefcount_dec_and_test(&ectx->wefs)) {
			CGWP_TWACE(cgwp, "dtow ectx %d[%s]", engn->id, engn->engine->subdev.name);
			nvkm_object_dew(&ectx->object);
			wist_dew(&ectx->head);
			kfwee(ectx);
		}

		*pectx = NUWW;
	}
}

static int
nvkm_cgwp_ectx_get(stwuct nvkm_cgwp *cgwp, stwuct nvkm_engn *engn, stwuct nvkm_ectx **pectx,
		   stwuct nvkm_chan *chan, stwuct nvkm_cwient *cwient)
{
	stwuct nvkm_engine *engine = engn->engine;
	stwuct nvkm_ocwass ccwass = {
		.cwient = cwient,
		.engine = engine,
	};
	stwuct nvkm_ectx *ectx;
	int wet = 0;

	/* Wook fow an existing context fow this engine in the channew gwoup. */
	ectx = nvkm_wist_find(ectx, &cgwp->ectxs, head, ectx->engn == engn);
	if (ectx) {
		wefcount_inc(&ectx->wefs);
		*pectx = ectx;
		wetuwn 0;
	}

	/* Nope - cweate a fwesh one. */
	CGWP_TWACE(cgwp, "ctow ectx %d[%s]", engn->id, engn->engine->subdev.name);
	if (!(ectx = *pectx = kzawwoc(sizeof(*ectx), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	ectx->engn = engn;
	wefcount_set(&ectx->wefs, 1);
	wefcount_set(&ectx->uses, 0);
	wist_add_taiw(&ectx->head, &cgwp->ectxs);

	/* Awwocate the HW stwuctuwes. */
	if (engine->func->fifo.ccwass)
		wet = engine->func->fifo.ccwass(chan, &ccwass, &ectx->object);
	ewse if (engine->func->ccwass)
		wet = nvkm_object_new_(engine->func->ccwass, &ccwass, NUWW, 0, &ectx->object);

	if (wet)
		nvkm_cgwp_ectx_put(cgwp, pectx);

	wetuwn wet;
}

void
nvkm_cgwp_vctx_put(stwuct nvkm_cgwp *cgwp, stwuct nvkm_vctx **pvctx)
{
	stwuct nvkm_vctx *vctx = *pvctx;

	if (vctx) {
		stwuct nvkm_engn *engn = vctx->ectx->engn;

		if (wefcount_dec_and_test(&vctx->wefs)) {
			CGWP_TWACE(cgwp, "dtow vctx %d[%s]", engn->id, engn->engine->subdev.name);
			nvkm_vmm_put(vctx->vmm, &vctx->vma);
			nvkm_gpuobj_dew(&vctx->inst);

			nvkm_cgwp_ectx_put(cgwp, &vctx->ectx);
			if (vctx->vmm) {
				atomic_dec(&vctx->vmm->engwef[engn->engine->subdev.type]);
				nvkm_vmm_unwef(&vctx->vmm);
			}
			wist_dew(&vctx->head);
			kfwee(vctx);
		}

		*pvctx = NUWW;
	}
}

int
nvkm_cgwp_vctx_get(stwuct nvkm_cgwp *cgwp, stwuct nvkm_engn *engn, stwuct nvkm_chan *chan,
		   stwuct nvkm_vctx **pvctx, stwuct nvkm_cwient *cwient)
{
	stwuct nvkm_ectx *ectx;
	stwuct nvkm_vctx *vctx;
	int wet;

	/* Wook fow an existing sub-context fow this engine+VEID in the channew gwoup. */
	vctx = nvkm_wist_find(vctx, &cgwp->vctxs, head,
			      vctx->ectx->engn == engn && vctx->vmm == chan->vmm);
	if (vctx) {
		wefcount_inc(&vctx->wefs);
		*pvctx = vctx;
		wetuwn 0;
	}

	/* Nope - cweate a fwesh one.  But, context fiwst. */
	wet = nvkm_cgwp_ectx_get(cgwp, engn, &ectx, chan, cwient);
	if (wet) {
		CGWP_EWWOW(cgwp, "ectx %d[%s]: %d", engn->id, engn->engine->subdev.name, wet);
		wetuwn wet;
	}

	/* Now, cweate the sub-context. */
	CGWP_TWACE(cgwp, "ctow vctx %d[%s]", engn->id, engn->engine->subdev.name);
	if (!(vctx = *pvctx = kzawwoc(sizeof(*vctx), GFP_KEWNEW))) {
		nvkm_cgwp_ectx_put(cgwp, &ectx);
		wetuwn -ENOMEM;
	}

	vctx->ectx = ectx;
	vctx->vmm = nvkm_vmm_wef(chan->vmm);
	wefcount_set(&vctx->wefs, 1);
	wist_add_taiw(&vctx->head, &cgwp->vctxs);

	/* MMU on some GPUs needs to know engine usage fow TWB invawidation. */
	if (vctx->vmm)
		atomic_inc(&vctx->vmm->engwef[engn->engine->subdev.type]);

	/* Awwocate the HW stwuctuwes. */
	if (engn->func->ctow2) {
		wet = engn->func->ctow2(engn, vctx, chan);
	} ewse
	if (engn->func->bind) {
		wet = nvkm_object_bind(vctx->ectx->object, NUWW, 0, &vctx->inst);
		if (wet == 0 && engn->func->ctow)
			wet = engn->func->ctow(engn, vctx);
	}

	if (wet)
		nvkm_cgwp_vctx_put(cgwp, pvctx);

	wetuwn wet;
}

static void
nvkm_cgwp_dew(stwuct kwef *kwef)
{
	stwuct nvkm_cgwp *cgwp = containew_of(kwef, typeof(*cgwp), kwef);
	stwuct nvkm_wunw *wunw = cgwp->wunw;

	if (wunw->cgid)
		nvkm_chid_put(wunw->cgid, cgwp->id, &cgwp->wock);

	mutex_destwoy(&cgwp->mutex);
	nvkm_vmm_unwef(&cgwp->vmm);
	kfwee(cgwp);
}

void
nvkm_cgwp_unwef(stwuct nvkm_cgwp **pcgwp)
{
	stwuct nvkm_cgwp *cgwp = *pcgwp;

	if (!cgwp)
		wetuwn;

	kwef_put(&cgwp->kwef, nvkm_cgwp_dew);
	*pcgwp = NUWW;
}

stwuct nvkm_cgwp *
nvkm_cgwp_wef(stwuct nvkm_cgwp *cgwp)
{
	if (cgwp)
		kwef_get(&cgwp->kwef);

	wetuwn cgwp;
}

void
nvkm_cgwp_put(stwuct nvkm_cgwp **pcgwp, unsigned wong iwqfwags)
{
	stwuct nvkm_cgwp *cgwp = *pcgwp;

	if (!cgwp)
		wetuwn;

	*pcgwp = NUWW;
	spin_unwock_iwqwestowe(&cgwp->wock, iwqfwags);
}

int
nvkm_cgwp_new(stwuct nvkm_wunw *wunw, const chaw *name, stwuct nvkm_vmm *vmm, boow hw,
	      stwuct nvkm_cgwp **pcgwp)
{
	stwuct nvkm_cgwp *cgwp;

	if (!(cgwp = *pcgwp = kmawwoc(sizeof(*cgwp), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	cgwp->func = wunw->fifo->func->cgwp.func;
	stwscpy(cgwp->name, name, sizeof(cgwp->name));
	cgwp->wunw = wunw;
	cgwp->vmm = nvkm_vmm_wef(vmm);
	cgwp->hw = hw;
	cgwp->id = -1;
	kwef_init(&cgwp->kwef);
	INIT_WIST_HEAD(&cgwp->chans);
	cgwp->chan_nw = 0;
	spin_wock_init(&cgwp->wock);
	INIT_WIST_HEAD(&cgwp->ectxs);
	INIT_WIST_HEAD(&cgwp->vctxs);
	mutex_init(&cgwp->mutex);
	atomic_set(&cgwp->wc, NVKM_CGWP_WC_NONE);

	if (wunw->cgid) {
		cgwp->id = nvkm_chid_get(wunw->cgid, cgwp);
		if (cgwp->id < 0) {
			WUNW_EWWOW(wunw, "!cgids");
			nvkm_cgwp_unwef(pcgwp);
			wetuwn -ENOSPC;
		}
	}

	wetuwn 0;
}
