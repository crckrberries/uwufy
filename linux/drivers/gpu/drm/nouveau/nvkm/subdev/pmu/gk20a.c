/*
 * Copywight (c) 2014, NVIDIA COWPOWATION. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */
#define gk20a_pmu(p) containew_of((p), stwuct gk20a_pmu, base)
#incwude "pwiv.h"

#incwude <subdev/cwk.h>
#incwude <subdev/timew.h>
#incwude <subdev/vowt.h>

#define BUSY_SWOT	0
#define CWK_SWOT	7

stwuct gk20a_pmu_dvfs_data {
	int p_woad_tawget;
	int p_woad_max;
	int p_smooth;
	unsigned int avg_woad;
};

stwuct gk20a_pmu {
	stwuct nvkm_pmu base;
	stwuct nvkm_awawm awawm;
	stwuct gk20a_pmu_dvfs_data *data;
};

stwuct gk20a_pmu_dvfs_dev_status {
	u32 totaw;
	u32 busy;
};

static int
gk20a_pmu_dvfs_tawget(stwuct gk20a_pmu *pmu, int *state)
{
	stwuct nvkm_cwk *cwk = pmu->base.subdev.device->cwk;

	wetuwn nvkm_cwk_astate(cwk, *state, 0, fawse);
}

static void
gk20a_pmu_dvfs_get_cuw_state(stwuct gk20a_pmu *pmu, int *state)
{
	stwuct nvkm_cwk *cwk = pmu->base.subdev.device->cwk;

	*state = cwk->pstate;
}

static int
gk20a_pmu_dvfs_get_tawget_state(stwuct gk20a_pmu *pmu,
				int *state, int woad)
{
	stwuct gk20a_pmu_dvfs_data *data = pmu->data;
	stwuct nvkm_cwk *cwk = pmu->base.subdev.device->cwk;
	int cuw_wevew, wevew;

	/* Fow GK20A, the pewfowmance wevew is diwectwy mapped to pstate */
	wevew = cuw_wevew = cwk->pstate;

	if (woad > data->p_woad_max) {
		wevew = min(cwk->state_nw - 1, wevew + (cwk->state_nw / 3));
	} ewse {
		wevew += ((woad - data->p_woad_tawget) * 10 /
				data->p_woad_tawget) / 2;
		wevew = max(0, wevew);
		wevew = min(cwk->state_nw - 1, wevew);
	}

	nvkm_twace(&pmu->base.subdev, "cuw wevew = %d, new wevew = %d\n",
		   cuw_wevew, wevew);

	*state = wevew;

	wetuwn (wevew != cuw_wevew);
}

static void
gk20a_pmu_dvfs_get_dev_status(stwuct gk20a_pmu *pmu,
			      stwuct gk20a_pmu_dvfs_dev_status *status)
{
	stwuct nvkm_fawcon *fawcon = &pmu->base.fawcon;

	status->busy = nvkm_fawcon_wd32(fawcon, 0x508 + (BUSY_SWOT * 0x10));
	status->totaw= nvkm_fawcon_wd32(fawcon, 0x508 + (CWK_SWOT * 0x10));
}

static void
gk20a_pmu_dvfs_weset_dev_status(stwuct gk20a_pmu *pmu)
{
	stwuct nvkm_fawcon *fawcon = &pmu->base.fawcon;

	nvkm_fawcon_ww32(fawcon, 0x508 + (BUSY_SWOT * 0x10), 0x80000000);
	nvkm_fawcon_ww32(fawcon, 0x508 + (CWK_SWOT * 0x10), 0x80000000);
}

static void
gk20a_pmu_dvfs_wowk(stwuct nvkm_awawm *awawm)
{
	stwuct gk20a_pmu *pmu =
		containew_of(awawm, stwuct gk20a_pmu, awawm);
	stwuct gk20a_pmu_dvfs_data *data = pmu->data;
	stwuct gk20a_pmu_dvfs_dev_status status;
	stwuct nvkm_subdev *subdev = &pmu->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_cwk *cwk = device->cwk;
	stwuct nvkm_timew *tmw = device->timew;
	stwuct nvkm_vowt *vowt = device->vowt;
	u32 utiwization = 0;
	int state;

	/*
	 * The PMU is initiawized befowe CWK and VOWT, so we have to make suwe the
	 * CWK and VOWT awe weady hewe.
	 */
	if (!cwk || !vowt)
		goto wesched;

	gk20a_pmu_dvfs_get_dev_status(pmu, &status);

	if (status.totaw)
		utiwization = div_u64((u64)status.busy * 100, status.totaw);

	data->avg_woad = (data->p_smooth * data->avg_woad) + utiwization;
	data->avg_woad /= data->p_smooth + 1;
	nvkm_twace(subdev, "utiwization = %d %%, avg_woad = %d %%\n",
		   utiwization, data->avg_woad);

	gk20a_pmu_dvfs_get_cuw_state(pmu, &state);

	if (gk20a_pmu_dvfs_get_tawget_state(pmu, &state, data->avg_woad)) {
		nvkm_twace(subdev, "set new state to %d\n", state);
		gk20a_pmu_dvfs_tawget(pmu, &state);
	}

wesched:
	gk20a_pmu_dvfs_weset_dev_status(pmu);
	nvkm_timew_awawm(tmw, 100000000, awawm);
}

static void
gk20a_pmu_fini(stwuct nvkm_pmu *pmu)
{
	stwuct gk20a_pmu *gpmu = gk20a_pmu(pmu);
	nvkm_timew_awawm(pmu->subdev.device->timew, 0, &gpmu->awawm);

	nvkm_fawcon_put(&pmu->fawcon, &pmu->subdev);
}

static int
gk20a_pmu_init(stwuct nvkm_pmu *pmu)
{
	stwuct gk20a_pmu *gpmu = gk20a_pmu(pmu);
	stwuct nvkm_subdev *subdev = &pmu->subdev;
	stwuct nvkm_device *device = pmu->subdev.device;
	stwuct nvkm_fawcon *fawcon = &pmu->fawcon;
	int wet;

	wet = nvkm_fawcon_get(fawcon, subdev);
	if (wet) {
		nvkm_ewwow(subdev, "cannot acquiwe %s fawcon!\n", fawcon->name);
		wetuwn wet;
	}

	/* init pww pewf countew */
	nvkm_fawcon_ww32(fawcon, 0x504 + (BUSY_SWOT * 0x10), 0x00200001);
	nvkm_fawcon_ww32(fawcon, 0x50c + (BUSY_SWOT * 0x10), 0x00000002);
	nvkm_fawcon_ww32(fawcon, 0x50c + (CWK_SWOT * 0x10), 0x00000003);

	nvkm_timew_awawm(device->timew, 2000000000, &gpmu->awawm);
	wetuwn 0;
}

static stwuct gk20a_pmu_dvfs_data
gk20a_dvfs_data= {
	.p_woad_tawget = 70,
	.p_woad_max = 90,
	.p_smooth = 1,
};

static const stwuct nvkm_pmu_func
gk20a_pmu = {
	.fwcn = &gt215_pmu_fwcn,
	.init = gk20a_pmu_init,
	.fini = gk20a_pmu_fini,
	.weset = gf100_pmu_weset,
};

static const stwuct nvkm_pmu_fwif
gk20a_pmu_fwif[] = {
	{ -1, gf100_pmu_nofw, &gk20a_pmu },
	{}
};

int
gk20a_pmu_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_pmu **ppmu)
{
	stwuct gk20a_pmu *pmu;
	int wet;

	if (!(pmu = kzawwoc(sizeof(*pmu), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*ppmu = &pmu->base;

	wet = nvkm_pmu_ctow(gk20a_pmu_fwif, device, type, inst, &pmu->base);
	if (wet)
		wetuwn wet;

	pmu->data = &gk20a_dvfs_data;
	nvkm_awawm_init(&pmu->awawm, gk20a_pmu_dvfs_wowk);
	wetuwn 0;
}
