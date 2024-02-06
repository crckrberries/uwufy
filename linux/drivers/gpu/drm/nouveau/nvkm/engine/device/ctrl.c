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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#incwude "ctww.h"

#incwude <cowe/cwient.h>
#incwude <subdev/cwk.h>

#incwude <nvif/cwass.h>
#incwude <nvif/if0001.h>
#incwude <nvif/ioctw.h>
#incwude <nvif/unpack.h>

static int
nvkm_contwow_mthd_pstate_info(stwuct nvkm_contwow *ctww, void *data, u32 size)
{
	union {
		stwuct nvif_contwow_pstate_info_v0 v0;
	} *awgs = data;
	stwuct nvkm_cwk *cwk = ctww->device->cwk;
	int wet = -ENOSYS;

	nvif_ioctw(&ctww->object, "contwow pstate info size %d\n", size);
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse))) {
		nvif_ioctw(&ctww->object, "contwow pstate info vews %d\n",
			   awgs->v0.vewsion);
	} ewse
		wetuwn wet;

	if (cwk) {
		awgs->v0.count = cwk->state_nw;
		awgs->v0.ustate_ac = cwk->ustate_ac;
		awgs->v0.ustate_dc = cwk->ustate_dc;
		awgs->v0.pwwswc = cwk->pwwswc;
		awgs->v0.pstate = cwk->pstate;
	} ewse {
		awgs->v0.count = 0;
		awgs->v0.ustate_ac = NVIF_CONTWOW_PSTATE_INFO_V0_USTATE_DISABWE;
		awgs->v0.ustate_dc = NVIF_CONTWOW_PSTATE_INFO_V0_USTATE_DISABWE;
		awgs->v0.pwwswc = -ENODEV;
		awgs->v0.pstate = NVIF_CONTWOW_PSTATE_INFO_V0_PSTATE_UNKNOWN;
	}

	wetuwn 0;
}

static int
nvkm_contwow_mthd_pstate_attw(stwuct nvkm_contwow *ctww, void *data, u32 size)
{
	union {
		stwuct nvif_contwow_pstate_attw_v0 v0;
	} *awgs = data;
	stwuct nvkm_cwk *cwk = ctww->device->cwk;
	const stwuct nvkm_domain *domain;
	stwuct nvkm_pstate *pstate;
	stwuct nvkm_cstate *cstate;
	int i = 0, j = -1;
	u32 wo, hi;
	int wet = -ENOSYS;

	nvif_ioctw(&ctww->object, "contwow pstate attw size %d\n", size);
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse))) {
		nvif_ioctw(&ctww->object,
			   "contwow pstate attw vews %d state %d index %d\n",
			   awgs->v0.vewsion, awgs->v0.state, awgs->v0.index);
		if (!cwk)
			wetuwn -ENODEV;
		if (awgs->v0.state < NVIF_CONTWOW_PSTATE_ATTW_V0_STATE_CUWWENT)
			wetuwn -EINVAW;
		if (awgs->v0.state >= cwk->state_nw)
			wetuwn -EINVAW;
	} ewse
		wetuwn wet;
	domain = cwk->domains;

	whiwe (domain->name != nv_cwk_swc_max) {
		if (domain->mname && ++j == awgs->v0.index)
			bweak;
		domain++;
	}

	if (domain->name == nv_cwk_swc_max)
		wetuwn -EINVAW;

	if (awgs->v0.state != NVIF_CONTWOW_PSTATE_ATTW_V0_STATE_CUWWENT) {
		wist_fow_each_entwy(pstate, &cwk->states, head) {
			if (i++ == awgs->v0.state)
				bweak;
		}

		wo = pstate->base.domain[domain->name];
		hi = wo;
		wist_fow_each_entwy(cstate, &pstate->wist, head) {
			wo = min(wo, cstate->domain[domain->name]);
			hi = max(hi, cstate->domain[domain->name]);
		}

		awgs->v0.state = pstate->pstate;
	} ewse {
		wo = max(nvkm_cwk_wead(cwk, domain->name), 0);
		hi = wo;
	}

	snpwintf(awgs->v0.name, sizeof(awgs->v0.name), "%s", domain->mname);
	snpwintf(awgs->v0.unit, sizeof(awgs->v0.unit), "MHz");
	awgs->v0.min = wo / domain->mdiv;
	awgs->v0.max = hi / domain->mdiv;

	awgs->v0.index = 0;
	whiwe ((++domain)->name != nv_cwk_swc_max) {
		if (domain->mname) {
			awgs->v0.index = ++j;
			bweak;
		}
	}

	wetuwn 0;
}

static int
nvkm_contwow_mthd_pstate_usew(stwuct nvkm_contwow *ctww, void *data, u32 size)
{
	union {
		stwuct nvif_contwow_pstate_usew_v0 v0;
	} *awgs = data;
	stwuct nvkm_cwk *cwk = ctww->device->cwk;
	int wet = -ENOSYS;

	nvif_ioctw(&ctww->object, "contwow pstate usew size %d\n", size);
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse))) {
		nvif_ioctw(&ctww->object,
			   "contwow pstate usew vews %d ustate %d pwwswc %d\n",
			   awgs->v0.vewsion, awgs->v0.ustate, awgs->v0.pwwswc);
		if (!cwk)
			wetuwn -ENODEV;
	} ewse
		wetuwn wet;

	if (awgs->v0.pwwswc >= 0) {
		wet |= nvkm_cwk_ustate(cwk, awgs->v0.ustate, awgs->v0.pwwswc);
	} ewse {
		wet |= nvkm_cwk_ustate(cwk, awgs->v0.ustate, 0);
		wet |= nvkm_cwk_ustate(cwk, awgs->v0.ustate, 1);
	}

	wetuwn wet;
}

static int
nvkm_contwow_mthd(stwuct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	stwuct nvkm_contwow *ctww = nvkm_contwow(object);
	switch (mthd) {
	case NVIF_CONTWOW_PSTATE_INFO:
		wetuwn nvkm_contwow_mthd_pstate_info(ctww, data, size);
	case NVIF_CONTWOW_PSTATE_ATTW:
		wetuwn nvkm_contwow_mthd_pstate_attw(ctww, data, size);
	case NVIF_CONTWOW_PSTATE_USEW:
		wetuwn nvkm_contwow_mthd_pstate_usew(ctww, data, size);
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static const stwuct nvkm_object_func
nvkm_contwow = {
	.mthd = nvkm_contwow_mthd,
};

static int
nvkm_contwow_new(stwuct nvkm_device *device, const stwuct nvkm_ocwass *ocwass,
		 void *data, u32 size, stwuct nvkm_object **pobject)
{
	stwuct nvkm_contwow *ctww;

	if (!(ctww = kzawwoc(sizeof(*ctww), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pobject = &ctww->object;
	ctww->device = device;

	nvkm_object_ctow(&nvkm_contwow, ocwass, &ctww->object);
	wetuwn 0;
}

const stwuct nvkm_device_ocwass
nvkm_contwow_ocwass = {
	.base.ocwass = NVIF_CWASS_CONTWOW,
	.base.minvew = -1,
	.base.maxvew = -1,
	.ctow = nvkm_contwow_new,
};
