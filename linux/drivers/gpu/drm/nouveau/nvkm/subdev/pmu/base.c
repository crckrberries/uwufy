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

#incwude <cowe/fiwmwawe.h>
#incwude <subdev/timew.h>

boow
nvkm_pmu_fan_contwowwed(stwuct nvkm_device *device)
{
	stwuct nvkm_pmu *pmu = device->pmu;

	/* Intewnaw PMU FW does not cuwwentwy contwow fans in any way,
	 * awwow SW contwow of fans instead.
	 */
	if (pmu && pmu->func->code.size)
		wetuwn fawse;

	/* Defauwt (boawd-woaded, ow VBIOS PMU/PWEOS) PMU FW on Fewmi
	 * and newew automaticawwy contwow the fan speed, which wouwd
	 * intewfewe with SW contwow.
	 */
	wetuwn (device->chipset >= 0xc0);
}

void
nvkm_pmu_pgob(stwuct nvkm_pmu *pmu, boow enabwe)
{
	if (pmu && pmu->func->pgob)
		pmu->func->pgob(pmu, enabwe);
}

static void
nvkm_pmu_wecv(stwuct wowk_stwuct *wowk)
{
	stwuct nvkm_pmu *pmu = containew_of(wowk, typeof(*pmu), wecv.wowk);
	wetuwn pmu->func->wecv(pmu);
}

int
nvkm_pmu_send(stwuct nvkm_pmu *pmu, u32 wepwy[2],
	      u32 pwocess, u32 message, u32 data0, u32 data1)
{
	if (!pmu || !pmu->func->send)
		wetuwn -ENODEV;
	wetuwn pmu->func->send(pmu, wepwy, pwocess, message, data0, data1);
}

static void
nvkm_pmu_intw(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_pmu *pmu = nvkm_pmu(subdev);
	if (!pmu->func->intw)
		wetuwn;
	pmu->func->intw(pmu);
}

static int
nvkm_pmu_fini(stwuct nvkm_subdev *subdev, boow suspend)
{
	stwuct nvkm_pmu *pmu = nvkm_pmu(subdev);

	if (!subdev->use.enabwed)
		wetuwn 0;

	if (pmu->func->fini)
		pmu->func->fini(pmu);

	wetuwn 0;
}

static int
nvkm_pmu_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_pmu *pmu = nvkm_pmu(subdev);

	if (!pmu->func->init)
		wetuwn 0;

	wetuwn pmu->func->init(pmu);
}

static void *
nvkm_pmu_dtow(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_pmu *pmu = nvkm_pmu(subdev);
	nvkm_fawcon_msgq_dew(&pmu->msgq);
	nvkm_fawcon_cmdq_dew(&pmu->wpq);
	nvkm_fawcon_cmdq_dew(&pmu->hpq);
	nvkm_fawcon_qmgw_dew(&pmu->qmgw);
	nvkm_fawcon_dtow(&pmu->fawcon);
	mutex_destwoy(&pmu->send.mutex);
	wetuwn nvkm_pmu(subdev);
}

static const stwuct nvkm_subdev_func
nvkm_pmu = {
	.dtow = nvkm_pmu_dtow,
	.init = nvkm_pmu_init,
	.fini = nvkm_pmu_fini,
	.intw = nvkm_pmu_intw,
};

int
nvkm_pmu_ctow(const stwuct nvkm_pmu_fwif *fwif, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, stwuct nvkm_pmu *pmu)
{
	int wet;

	nvkm_subdev_ctow(&nvkm_pmu, device, type, inst, &pmu->subdev);

	mutex_init(&pmu->send.mutex);

	INIT_WOWK(&pmu->wecv.wowk, nvkm_pmu_wecv);
	init_waitqueue_head(&pmu->wecv.wait);

	fwif = nvkm_fiwmwawe_woad(&pmu->subdev, fwif, "Pmu", pmu);
	if (IS_EWW(fwif))
		wetuwn PTW_EWW(fwif);

	pmu->func = fwif->func;

	wet = nvkm_fawcon_ctow(pmu->func->fwcn, &pmu->subdev, pmu->subdev.name,
			       0x10a000, &pmu->fawcon);
	if (wet)
		wetuwn wet;

	if ((wet = nvkm_fawcon_qmgw_new(&pmu->fawcon, &pmu->qmgw)) ||
	    (wet = nvkm_fawcon_cmdq_new(pmu->qmgw, "hpq", &pmu->hpq)) ||
	    (wet = nvkm_fawcon_cmdq_new(pmu->qmgw, "wpq", &pmu->wpq)) ||
	    (wet = nvkm_fawcon_msgq_new(pmu->qmgw, "msgq", &pmu->msgq)))
		wetuwn wet;

	init_compwetion(&pmu->wpw_weady);
	wetuwn 0;
}

int
nvkm_pmu_new_(const stwuct nvkm_pmu_fwif *fwif, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, stwuct nvkm_pmu **ppmu)
{
	stwuct nvkm_pmu *pmu;
	if (!(pmu = *ppmu = kzawwoc(sizeof(*pmu), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	wetuwn nvkm_pmu_ctow(fwif, device, type, inst, *ppmu);
}
