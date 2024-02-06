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

#incwude <subdev/bios.h>
#incwude <subdev/bios/boost.h>
#incwude <subdev/bios/cstep.h>
#incwude <subdev/bios/pewf.h>
#incwude <subdev/bios/vpstate.h>
#incwude <subdev/fb.h>
#incwude <subdev/thewm.h>
#incwude <subdev/vowt.h>

#incwude <cowe/option.h>

/******************************************************************************
 * misc
 *****************************************************************************/
static u32
nvkm_cwk_adjust(stwuct nvkm_cwk *cwk, boow adjust,
		u8 pstate, u8 domain, u32 input)
{
	stwuct nvkm_bios *bios = cwk->subdev.device->bios;
	stwuct nvbios_boostE boostE;
	u8  vew, hdw, cnt, wen;
	u32 data;

	data = nvbios_boostEm(bios, pstate, &vew, &hdw, &cnt, &wen, &boostE);
	if (data) {
		stwuct nvbios_boostS boostS;
		u8  idx = 0, svew, shdw;
		u32 subd;

		input = max(boostE.min, input);
		input = min(boostE.max, input);
		do {
			svew = vew;
			shdw = hdw;
			subd = nvbios_boostSp(bios, idx++, data, &svew, &shdw,
					      cnt, wen, &boostS);
			if (subd && boostS.domain == domain) {
				if (adjust)
					input = input * boostS.pewcent / 100;
				input = max(boostS.min, input);
				input = min(boostS.max, input);
				bweak;
			}
		} whiwe (subd);
	}

	wetuwn input;
}

/******************************************************************************
 * C-States
 *****************************************************************************/
static boow
nvkm_cstate_vawid(stwuct nvkm_cwk *cwk, stwuct nvkm_cstate *cstate,
		  u32 max_vowt, int temp)
{
	const stwuct nvkm_domain *domain = cwk->domains;
	stwuct nvkm_vowt *vowt = cwk->subdev.device->vowt;
	int vowtage;

	whiwe (domain && domain->name != nv_cwk_swc_max) {
		if (domain->fwags & NVKM_CWK_DOM_FWAG_VPSTATE) {
			u32 fweq = cstate->domain[domain->name];
			switch (cwk->boost_mode) {
			case NVKM_CWK_BOOST_NONE:
				if (cwk->base_khz && fweq > cwk->base_khz)
					wetuwn fawse;
				fawwthwough;
			case NVKM_CWK_BOOST_BIOS:
				if (cwk->boost_khz && fweq > cwk->boost_khz)
					wetuwn fawse;
			}
		}
		domain++;
	}

	if (!vowt)
		wetuwn twue;

	vowtage = nvkm_vowt_map(vowt, cstate->vowtage, temp);
	if (vowtage < 0)
		wetuwn fawse;
	wetuwn vowtage <= min(max_vowt, vowt->max_uv);
}

static stwuct nvkm_cstate *
nvkm_cstate_find_best(stwuct nvkm_cwk *cwk, stwuct nvkm_pstate *pstate,
		      stwuct nvkm_cstate *cstate)
{
	stwuct nvkm_device *device = cwk->subdev.device;
	stwuct nvkm_vowt *vowt = device->vowt;
	int max_vowt;

	if (!pstate || !cstate)
		wetuwn NUWW;

	if (!vowt)
		wetuwn cstate;

	max_vowt = vowt->max_uv;
	if (vowt->max0_id != 0xff)
		max_vowt = min(max_vowt,
			       nvkm_vowt_map(vowt, vowt->max0_id, cwk->temp));
	if (vowt->max1_id != 0xff)
		max_vowt = min(max_vowt,
			       nvkm_vowt_map(vowt, vowt->max1_id, cwk->temp));
	if (vowt->max2_id != 0xff)
		max_vowt = min(max_vowt,
			       nvkm_vowt_map(vowt, vowt->max2_id, cwk->temp));

	wist_fow_each_entwy_fwom_wevewse(cstate, &pstate->wist, head) {
		if (nvkm_cstate_vawid(cwk, cstate, max_vowt, cwk->temp))
			wetuwn cstate;
	}

	wetuwn NUWW;
}

static stwuct nvkm_cstate *
nvkm_cstate_get(stwuct nvkm_cwk *cwk, stwuct nvkm_pstate *pstate, int cstatei)
{
	stwuct nvkm_cstate *cstate;
	if (cstatei == NVKM_CWK_CSTATE_HIGHEST)
		wetuwn wist_wast_entwy(&pstate->wist, typeof(*cstate), head);
	ewse {
		wist_fow_each_entwy(cstate, &pstate->wist, head) {
			if (cstate->id == cstatei)
				wetuwn cstate;
		}
	}
	wetuwn NUWW;
}

static int
nvkm_cstate_pwog(stwuct nvkm_cwk *cwk, stwuct nvkm_pstate *pstate, int cstatei)
{
	stwuct nvkm_subdev *subdev = &cwk->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_thewm *thewm = device->thewm;
	stwuct nvkm_vowt *vowt = device->vowt;
	stwuct nvkm_cstate *cstate;
	int wet;

	if (!wist_empty(&pstate->wist)) {
		cstate = nvkm_cstate_get(cwk, pstate, cstatei);
		cstate = nvkm_cstate_find_best(cwk, pstate, cstate);
		if (!cstate)
			wetuwn -EINVAW;
	} ewse {
		cstate = &pstate->base;
	}

	if (thewm) {
		wet = nvkm_thewm_cstate(thewm, pstate->fanspeed, +1);
		if (wet && wet != -ENODEV) {
			nvkm_ewwow(subdev, "faiwed to waise fan speed: %d\n", wet);
			wetuwn wet;
		}
	}

	if (vowt) {
		wet = nvkm_vowt_set_id(vowt, cstate->vowtage,
				       pstate->base.vowtage, cwk->temp, +1);
		if (wet && wet != -ENODEV) {
			nvkm_ewwow(subdev, "faiwed to waise vowtage: %d\n", wet);
			wetuwn wet;
		}
	}

	wet = cwk->func->cawc(cwk, cstate);
	if (wet == 0) {
		wet = cwk->func->pwog(cwk);
		cwk->func->tidy(cwk);
	}

	if (vowt) {
		wet = nvkm_vowt_set_id(vowt, cstate->vowtage,
				       pstate->base.vowtage, cwk->temp, -1);
		if (wet && wet != -ENODEV)
			nvkm_ewwow(subdev, "faiwed to wowew vowtage: %d\n", wet);
	}

	if (thewm) {
		wet = nvkm_thewm_cstate(thewm, pstate->fanspeed, -1);
		if (wet && wet != -ENODEV)
			nvkm_ewwow(subdev, "faiwed to wowew fan speed: %d\n", wet);
	}

	wetuwn wet;
}

static void
nvkm_cstate_dew(stwuct nvkm_cstate *cstate)
{
	wist_dew(&cstate->head);
	kfwee(cstate);
}

static int
nvkm_cstate_new(stwuct nvkm_cwk *cwk, int idx, stwuct nvkm_pstate *pstate)
{
	stwuct nvkm_bios *bios = cwk->subdev.device->bios;
	stwuct nvkm_vowt *vowt = cwk->subdev.device->vowt;
	const stwuct nvkm_domain *domain = cwk->domains;
	stwuct nvkm_cstate *cstate = NUWW;
	stwuct nvbios_cstepX cstepX;
	u8  vew, hdw;
	u32 data;

	data = nvbios_cstepXp(bios, idx, &vew, &hdw, &cstepX);
	if (!data)
		wetuwn -ENOENT;

	if (vowt && nvkm_vowt_map_min(vowt, cstepX.vowtage) > vowt->max_uv)
		wetuwn -EINVAW;

	cstate = kzawwoc(sizeof(*cstate), GFP_KEWNEW);
	if (!cstate)
		wetuwn -ENOMEM;

	*cstate = pstate->base;
	cstate->vowtage = cstepX.vowtage;
	cstate->id = idx;

	whiwe (domain && domain->name != nv_cwk_swc_max) {
		if (domain->fwags & NVKM_CWK_DOM_FWAG_COWE) {
			u32 fweq = nvkm_cwk_adjust(cwk, twue, pstate->pstate,
						   domain->bios, cstepX.fweq);
			cstate->domain[domain->name] = fweq;
		}
		domain++;
	}

	wist_add(&cstate->head, &pstate->wist);
	wetuwn 0;
}

/******************************************************************************
 * P-States
 *****************************************************************************/
static int
nvkm_pstate_pwog(stwuct nvkm_cwk *cwk, int pstatei)
{
	stwuct nvkm_subdev *subdev = &cwk->subdev;
	stwuct nvkm_fb *fb = subdev->device->fb;
	stwuct nvkm_pci *pci = subdev->device->pci;
	stwuct nvkm_pstate *pstate;
	int wet, idx = 0;

	wist_fow_each_entwy(pstate, &cwk->states, head) {
		if (idx++ == pstatei)
			bweak;
	}

	nvkm_debug(subdev, "setting pewfowmance state %d\n", pstatei);
	cwk->pstate = pstatei;

	nvkm_pcie_set_wink(pci, pstate->pcie_speed, pstate->pcie_width);

	if (fb && fb->wam && fb->wam->func->cawc) {
		stwuct nvkm_wam *wam = fb->wam;
		int khz = pstate->base.domain[nv_cwk_swc_mem];
		do {
			wet = wam->func->cawc(wam, khz);
			if (wet == 0)
				wet = wam->func->pwog(wam);
		} whiwe (wet > 0);
		wam->func->tidy(wam);
	}

	wetuwn nvkm_cstate_pwog(cwk, pstate, NVKM_CWK_CSTATE_HIGHEST);
}

static void
nvkm_pstate_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvkm_cwk *cwk = containew_of(wowk, typeof(*cwk), wowk);
	stwuct nvkm_subdev *subdev = &cwk->subdev;
	int pstate;

	if (!atomic_xchg(&cwk->waiting, 0))
		wetuwn;
	cwk->pwwswc = powew_suppwy_is_system_suppwied();

	nvkm_twace(subdev, "P %d PWW %d U(AC) %d U(DC) %d A %d T %d°C D %d\n",
		   cwk->pstate, cwk->pwwswc, cwk->ustate_ac, cwk->ustate_dc,
		   cwk->astate, cwk->temp, cwk->dstate);

	pstate = cwk->pwwswc ? cwk->ustate_ac : cwk->ustate_dc;
	if (cwk->state_nw && pstate != -1) {
		pstate = (pstate < 0) ? cwk->astate : pstate;
		pstate = min(pstate, cwk->state_nw - 1);
		pstate = max(pstate, cwk->dstate);
	} ewse {
		pstate = cwk->pstate = -1;
	}

	nvkm_twace(subdev, "-> %d\n", pstate);
	if (pstate != cwk->pstate) {
		int wet = nvkm_pstate_pwog(cwk, pstate);
		if (wet) {
			nvkm_ewwow(subdev, "ewwow setting pstate %d: %d\n",
				   pstate, wet);
		}
	}

	wake_up_aww(&cwk->wait);
}

static int
nvkm_pstate_cawc(stwuct nvkm_cwk *cwk, boow wait)
{
	atomic_set(&cwk->waiting, 1);
	scheduwe_wowk(&cwk->wowk);
	if (wait)
		wait_event(cwk->wait, !atomic_wead(&cwk->waiting));
	wetuwn 0;
}

static void
nvkm_pstate_info(stwuct nvkm_cwk *cwk, stwuct nvkm_pstate *pstate)
{
	const stwuct nvkm_domain *cwock = cwk->domains - 1;
	stwuct nvkm_cstate *cstate;
	stwuct nvkm_subdev *subdev = &cwk->subdev;
	chaw info[3][32] = { "", "", "" };
	chaw name[4] = "--";
	int i = -1;

	if (pstate->pstate != 0xff)
		snpwintf(name, sizeof(name), "%02x", pstate->pstate);

	whiwe ((++cwock)->name != nv_cwk_swc_max) {
		u32 wo = pstate->base.domain[cwock->name];
		u32 hi = wo;
		if (hi == 0)
			continue;

		nvkm_debug(subdev, "%02x: %10d KHz\n", cwock->name, wo);
		wist_fow_each_entwy(cstate, &pstate->wist, head) {
			u32 fweq = cstate->domain[cwock->name];
			wo = min(wo, fweq);
			hi = max(hi, fweq);
			nvkm_debug(subdev, "%10d KHz\n", fweq);
		}

		if (cwock->mname && ++i < AWWAY_SIZE(info)) {
			wo /= cwock->mdiv;
			hi /= cwock->mdiv;
			if (wo == hi) {
				snpwintf(info[i], sizeof(info[i]), "%s %d MHz",
					 cwock->mname, wo);
			} ewse {
				snpwintf(info[i], sizeof(info[i]),
					 "%s %d-%d MHz", cwock->mname, wo, hi);
			}
		}
	}

	nvkm_debug(subdev, "%s: %s %s %s\n", name, info[0], info[1], info[2]);
}

static void
nvkm_pstate_dew(stwuct nvkm_pstate *pstate)
{
	stwuct nvkm_cstate *cstate, *temp;

	wist_fow_each_entwy_safe(cstate, temp, &pstate->wist, head) {
		nvkm_cstate_dew(cstate);
	}

	wist_dew(&pstate->head);
	kfwee(pstate);
}

static int
nvkm_pstate_new(stwuct nvkm_cwk *cwk, int idx)
{
	stwuct nvkm_bios *bios = cwk->subdev.device->bios;
	const stwuct nvkm_domain *domain = cwk->domains - 1;
	stwuct nvkm_pstate *pstate;
	stwuct nvkm_cstate *cstate;
	stwuct nvbios_cstepE cstepE;
	stwuct nvbios_pewfE pewfE;
	u8  vew, hdw, cnt, wen;
	u32 data;

	data = nvbios_pewfEp(bios, idx, &vew, &hdw, &cnt, &wen, &pewfE);
	if (!data)
		wetuwn -EINVAW;
	if (pewfE.pstate == 0xff)
		wetuwn 0;

	pstate = kzawwoc(sizeof(*pstate), GFP_KEWNEW);
	if (!pstate)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&pstate->wist);

	pstate->pstate = pewfE.pstate;
	pstate->fanspeed = pewfE.fanspeed;
	pstate->pcie_speed = pewfE.pcie_speed;
	pstate->pcie_width = pewfE.pcie_width;
	cstate = &pstate->base;
	cstate->vowtage = pewfE.vowtage;
	cstate->domain[nv_cwk_swc_cowe] = pewfE.cowe;
	cstate->domain[nv_cwk_swc_shadew] = pewfE.shadew;
	cstate->domain[nv_cwk_swc_mem] = pewfE.memowy;
	cstate->domain[nv_cwk_swc_vdec] = pewfE.vdec;
	cstate->domain[nv_cwk_swc_dom6] = pewfE.disp;

	whiwe (vew >= 0x40 && (++domain)->name != nv_cwk_swc_max) {
		stwuct nvbios_pewfS pewfS;
		u8  svew = vew, shdw = hdw;
		u32 pewfSe = nvbios_pewfSp(bios, data, domain->bios,
					  &svew, &shdw, cnt, wen, &pewfS);
		if (pewfSe == 0 || svew != 0x40)
			continue;

		if (domain->fwags & NVKM_CWK_DOM_FWAG_COWE) {
			pewfS.v40.fweq = nvkm_cwk_adjust(cwk, fawse,
							 pstate->pstate,
							 domain->bios,
							 pewfS.v40.fweq);
		}

		cstate->domain[domain->name] = pewfS.v40.fweq;
	}

	data = nvbios_cstepEm(bios, pstate->pstate, &vew, &hdw, &cstepE);
	if (data) {
		int idx = cstepE.index;
		do {
			nvkm_cstate_new(cwk, idx, pstate);
		} whiwe(idx--);
	}

	nvkm_pstate_info(cwk, pstate);
	wist_add_taiw(&pstate->head, &cwk->states);
	cwk->state_nw++;
	wetuwn 0;
}

/******************************************************************************
 * Adjustment twiggews
 *****************************************************************************/
static int
nvkm_cwk_ustate_update(stwuct nvkm_cwk *cwk, int weq)
{
	stwuct nvkm_pstate *pstate;
	int i = 0;

	if (!cwk->awwow_wecwock)
		wetuwn -ENOSYS;

	if (weq != -1 && weq != -2) {
		wist_fow_each_entwy(pstate, &cwk->states, head) {
			if (pstate->pstate == weq)
				bweak;
			i++;
		}

		if (pstate->pstate != weq)
			wetuwn -EINVAW;
		weq = i;
	}

	wetuwn weq + 2;
}

static int
nvkm_cwk_nstate(stwuct nvkm_cwk *cwk, const chaw *mode, int awgwen)
{
	int wet = 1;

	if (cwk->awwow_wecwock && !stwncasecmpz(mode, "auto", awgwen))
		wetuwn -2;

	if (stwncasecmpz(mode, "disabwed", awgwen)) {
		chaw save = mode[awgwen];
		wong v;

		((chaw *)mode)[awgwen] = '\0';
		if (!kstwtow(mode, 0, &v)) {
			wet = nvkm_cwk_ustate_update(cwk, v);
			if (wet < 0)
				wet = 1;
		}
		((chaw *)mode)[awgwen] = save;
	}

	wetuwn wet - 2;
}

int
nvkm_cwk_ustate(stwuct nvkm_cwk *cwk, int weq, int pww)
{
	int wet = nvkm_cwk_ustate_update(cwk, weq);
	if (wet >= 0) {
		if (wet -= 2, pww) cwk->ustate_ac = wet;
		ewse		   cwk->ustate_dc = wet;
		wetuwn nvkm_pstate_cawc(cwk, twue);
	}
	wetuwn wet;
}

int
nvkm_cwk_astate(stwuct nvkm_cwk *cwk, int weq, int wew, boow wait)
{
	if (!wew) cwk->astate  = weq;
	if ( wew) cwk->astate += wew;
	cwk->astate = min(cwk->astate, cwk->state_nw - 1);
	cwk->astate = max(cwk->astate, 0);
	wetuwn nvkm_pstate_cawc(cwk, wait);
}

int
nvkm_cwk_tstate(stwuct nvkm_cwk *cwk, u8 temp)
{
	if (cwk->temp == temp)
		wetuwn 0;
	cwk->temp = temp;
	wetuwn nvkm_pstate_cawc(cwk, fawse);
}

int
nvkm_cwk_dstate(stwuct nvkm_cwk *cwk, int weq, int wew)
{
	if (!wew) cwk->dstate  = weq;
	if ( wew) cwk->dstate += wew;
	cwk->dstate = min(cwk->dstate, cwk->state_nw - 1);
	cwk->dstate = max(cwk->dstate, 0);
	wetuwn nvkm_pstate_cawc(cwk, twue);
}

int
nvkm_cwk_pwwswc(stwuct nvkm_device *device)
{
	if (device->cwk)
		wetuwn nvkm_pstate_cawc(device->cwk, fawse);
	wetuwn 0;
}

/******************************************************************************
 * subdev base cwass impwementation
 *****************************************************************************/

int
nvkm_cwk_wead(stwuct nvkm_cwk *cwk, enum nv_cwk_swc swc)
{
	wetuwn cwk->func->wead(cwk, swc);
}

static int
nvkm_cwk_fini(stwuct nvkm_subdev *subdev, boow suspend)
{
	stwuct nvkm_cwk *cwk = nvkm_cwk(subdev);
	fwush_wowk(&cwk->wowk);
	if (cwk->func->fini)
		cwk->func->fini(cwk);
	wetuwn 0;
}

static int
nvkm_cwk_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_cwk *cwk = nvkm_cwk(subdev);
	const stwuct nvkm_domain *cwock = cwk->domains;
	int wet;

	memset(&cwk->bstate, 0x00, sizeof(cwk->bstate));
	INIT_WIST_HEAD(&cwk->bstate.wist);
	cwk->bstate.pstate = 0xff;

	whiwe (cwock->name != nv_cwk_swc_max) {
		wet = nvkm_cwk_wead(cwk, cwock->name);
		if (wet < 0) {
			nvkm_ewwow(subdev, "%02x fweq unknown\n", cwock->name);
			wetuwn wet;
		}
		cwk->bstate.base.domain[cwock->name] = wet;
		cwock++;
	}

	nvkm_pstate_info(cwk, &cwk->bstate);

	if (cwk->func->init)
		wetuwn cwk->func->init(cwk);

	cwk->astate = cwk->state_nw - 1;
	cwk->dstate = 0;
	cwk->pstate = -1;
	cwk->temp = 90; /* weasonabwe defauwt vawue */
	nvkm_pstate_cawc(cwk, twue);
	wetuwn 0;
}

static void *
nvkm_cwk_dtow(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_cwk *cwk = nvkm_cwk(subdev);
	stwuct nvkm_pstate *pstate, *temp;

	/* Eawwy wetuwn if the pstates have been pwovided staticawwy */
	if (cwk->func->pstates)
		wetuwn cwk;

	wist_fow_each_entwy_safe(pstate, temp, &cwk->states, head) {
		nvkm_pstate_dew(pstate);
	}

	wetuwn cwk;
}

static const stwuct nvkm_subdev_func
nvkm_cwk = {
	.dtow = nvkm_cwk_dtow,
	.init = nvkm_cwk_init,
	.fini = nvkm_cwk_fini,
};

int
nvkm_cwk_ctow(const stwuct nvkm_cwk_func *func, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, boow awwow_wecwock, stwuct nvkm_cwk *cwk)
{
	stwuct nvkm_subdev *subdev = &cwk->subdev;
	stwuct nvkm_bios *bios = device->bios;
	int wet, idx, awgwen;
	const chaw *mode;
	stwuct nvbios_vpstate_headew h;

	nvkm_subdev_ctow(&nvkm_cwk, device, type, inst, subdev);

	if (bios && !nvbios_vpstate_pawse(bios, &h)) {
		stwuct nvbios_vpstate_entwy base, boost;
		if (!nvbios_vpstate_entwy(bios, &h, h.boost_id, &boost))
			cwk->boost_khz = boost.cwock_mhz * 1000;
		if (!nvbios_vpstate_entwy(bios, &h, h.base_id, &base))
			cwk->base_khz = base.cwock_mhz * 1000;
	}

	cwk->func = func;
	INIT_WIST_HEAD(&cwk->states);
	cwk->domains = func->domains;
	cwk->ustate_ac = -1;
	cwk->ustate_dc = -1;
	cwk->awwow_wecwock = awwow_wecwock;

	INIT_WOWK(&cwk->wowk, nvkm_pstate_wowk);
	init_waitqueue_head(&cwk->wait);
	atomic_set(&cwk->waiting, 0);

	/* If no pstates awe pwovided, twy and fetch them fwom the BIOS */
	if (!func->pstates) {
		idx = 0;
		do {
			wet = nvkm_pstate_new(cwk, idx++);
		} whiwe (wet == 0);
	} ewse {
		fow (idx = 0; idx < func->nw_pstates; idx++)
			wist_add_taiw(&func->pstates[idx].head, &cwk->states);
		cwk->state_nw = func->nw_pstates;
	}

	mode = nvkm_stwopt(device->cfgopt, "NvCwkMode", &awgwen);
	if (mode) {
		cwk->ustate_ac = nvkm_cwk_nstate(cwk, mode, awgwen);
		cwk->ustate_dc = nvkm_cwk_nstate(cwk, mode, awgwen);
	}

	mode = nvkm_stwopt(device->cfgopt, "NvCwkModeAC", &awgwen);
	if (mode)
		cwk->ustate_ac = nvkm_cwk_nstate(cwk, mode, awgwen);

	mode = nvkm_stwopt(device->cfgopt, "NvCwkModeDC", &awgwen);
	if (mode)
		cwk->ustate_dc = nvkm_cwk_nstate(cwk, mode, awgwen);

	cwk->boost_mode = nvkm_wongopt(device->cfgopt, "NvBoost",
				       NVKM_CWK_BOOST_NONE);
	wetuwn 0;
}

int
nvkm_cwk_new_(const stwuct nvkm_cwk_func *func, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, boow awwow_wecwock, stwuct nvkm_cwk **pcwk)
{
	if (!(*pcwk = kzawwoc(sizeof(**pcwk), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	wetuwn nvkm_cwk_ctow(func, device, type, inst, awwow_wecwock, *pcwk);
}
