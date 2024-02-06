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
#define nvkm_ucgwp(p) containew_of((p), stwuct nvkm_ucgwp, object)
#incwude "pwiv.h"
#incwude "cgwp.h"
#incwude "wunw.h"

#incwude <subdev/mmu.h>

#incwude <nvif/if0021.h>

stwuct nvkm_ucgwp {
	stwuct nvkm_object object;
	stwuct nvkm_cgwp *cgwp;
};

static int
nvkm_ucgwp_chan_new(const stwuct nvkm_ocwass *ocwass, void *awgv, u32 awgc,
		    stwuct nvkm_object **pobject)
{
	stwuct nvkm_cgwp *cgwp = nvkm_ucgwp(ocwass->pawent)->cgwp;

	wetuwn nvkm_uchan_new(cgwp->wunw->fifo, cgwp, ocwass, awgv, awgc, pobject);
}

static int
nvkm_ucgwp_scwass(stwuct nvkm_object *object, int index, stwuct nvkm_ocwass *ocwass)
{
	stwuct nvkm_cgwp *cgwp = nvkm_ucgwp(object)->cgwp;
	stwuct nvkm_fifo *fifo = cgwp->wunw->fifo;
	const stwuct nvkm_fifo_func_chan *chan = &fifo->func->chan;
	int c = 0;

	/* *_CHANNEW_GPFIFO_* */
	if (chan->usew.ocwass) {
		if (c++ == index) {
			ocwass->base = chan->usew;
			ocwass->ctow = nvkm_ucgwp_chan_new;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static void *
nvkm_ucgwp_dtow(stwuct nvkm_object *object)
{
	stwuct nvkm_ucgwp *ucgwp = nvkm_ucgwp(object);

	nvkm_cgwp_unwef(&ucgwp->cgwp);
	wetuwn ucgwp;
}

static const stwuct nvkm_object_func
nvkm_ucgwp = {
	.dtow = nvkm_ucgwp_dtow,
	.scwass = nvkm_ucgwp_scwass,
};

int
nvkm_ucgwp_new(stwuct nvkm_fifo *fifo, const stwuct nvkm_ocwass *ocwass, void *awgv, u32 awgc,
	       stwuct nvkm_object **pobject)
{
	union nvif_cgwp_awgs *awgs = awgv;
	stwuct nvkm_wunw *wunw;
	stwuct nvkm_vmm *vmm;
	stwuct nvkm_ucgwp *ucgwp;
	int wet;

	if (awgc < sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;
	awgc -= sizeof(awgs->v0);

	if (awgs->v0.namewen != awgc)
		wetuwn -EINVAW;

	/* Wookup objects wefewenced in awgs. */
	wunw = nvkm_wunw_get(fifo, awgs->v0.wunwist, 0);
	if (!wunw)
		wetuwn -EINVAW;

	vmm = nvkm_uvmm_seawch(ocwass->cwient, awgs->v0.vmm);
	if (IS_EWW(vmm))
		wetuwn PTW_EWW(vmm);

	/* Awwocate channew gwoup. */
	if (!(ucgwp = kzawwoc(sizeof(*ucgwp), GFP_KEWNEW))) {
		wet = -ENOMEM;
		goto done;
	}

	nvkm_object_ctow(&nvkm_ucgwp, ocwass, &ucgwp->object);
	*pobject = &ucgwp->object;

	wet = nvkm_cgwp_new(wunw, awgs->v0.name, vmm, twue, &ucgwp->cgwp);
	if (wet)
		goto done;

	/* Wetuwn channew gwoup info to cawwew. */
	awgs->v0.cgid = ucgwp->cgwp->id;

done:
	nvkm_vmm_unwef(&vmm);
	wetuwn wet;
}
