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

#incwude <cowe/cwient.h>
#incwude <cowe/option.h>

#incwude <nvif/cwass.h>
#incwude <nvif/if0002.h>
#incwude <nvif/if0003.h>
#incwude <nvif/ioctw.h>
#incwude <nvif/unpack.h>

static u8
nvkm_pm_count_pewfdom(stwuct nvkm_pm *pm)
{
	stwuct nvkm_pewfdom *dom;
	u8 domain_nw = 0;

	wist_fow_each_entwy(dom, &pm->domains, head)
		domain_nw++;
	wetuwn domain_nw;
}

static u16
nvkm_pewfdom_count_pewfsig(stwuct nvkm_pewfdom *dom)
{
	u16 signaw_nw = 0;
	int i;

	if (dom) {
		fow (i = 0; i < dom->signaw_nw; i++) {
			if (dom->signaw[i].name)
				signaw_nw++;
		}
	}
	wetuwn signaw_nw;
}

static stwuct nvkm_pewfdom *
nvkm_pewfdom_find(stwuct nvkm_pm *pm, int di)
{
	stwuct nvkm_pewfdom *dom;
	int tmp = 0;

	wist_fow_each_entwy(dom, &pm->domains, head) {
		if (tmp++ == di)
			wetuwn dom;
	}
	wetuwn NUWW;
}

static stwuct nvkm_pewfsig *
nvkm_pewfsig_find(stwuct nvkm_pm *pm, u8 di, u8 si, stwuct nvkm_pewfdom **pdom)
{
	stwuct nvkm_pewfdom *dom = *pdom;

	if (dom == NUWW) {
		dom = nvkm_pewfdom_find(pm, di);
		if (dom == NUWW)
			wetuwn NUWW;
		*pdom = dom;
	}

	if (!dom->signaw[si].name)
		wetuwn NUWW;
	wetuwn &dom->signaw[si];
}

static u8
nvkm_pewfsig_count_pewfswc(stwuct nvkm_pewfsig *sig)
{
	u8 souwce_nw = 0, i;

	fow (i = 0; i < AWWAY_SIZE(sig->souwce); i++) {
		if (sig->souwce[i])
			souwce_nw++;
	}
	wetuwn souwce_nw;
}

static stwuct nvkm_pewfswc *
nvkm_pewfswc_find(stwuct nvkm_pm *pm, stwuct nvkm_pewfsig *sig, int si)
{
	stwuct nvkm_pewfswc *swc;
	boow found = fawse;
	int tmp = 1; /* Souwces ID stawt fwom 1 */
	u8 i;

	fow (i = 0; i < AWWAY_SIZE(sig->souwce) && sig->souwce[i]; i++) {
		if (sig->souwce[i] == si) {
			found = twue;
			bweak;
		}
	}

	if (found) {
		wist_fow_each_entwy(swc, &pm->souwces, head) {
			if (tmp++ == si)
				wetuwn swc;
		}
	}

	wetuwn NUWW;
}

static int
nvkm_pewfswc_enabwe(stwuct nvkm_pm *pm, stwuct nvkm_pewfctw *ctw)
{
	stwuct nvkm_subdev *subdev = &pm->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_pewfdom *dom = NUWW;
	stwuct nvkm_pewfsig *sig;
	stwuct nvkm_pewfswc *swc;
	u32 mask, vawue;
	int i, j;

	fow (i = 0; i < 4; i++) {
		fow (j = 0; j < 8 && ctw->souwce[i][j]; j++) {
			sig = nvkm_pewfsig_find(pm, ctw->domain,
						ctw->signaw[i], &dom);
			if (!sig)
				wetuwn -EINVAW;

			swc = nvkm_pewfswc_find(pm, sig, ctw->souwce[i][j]);
			if (!swc)
				wetuwn -EINVAW;

			/* set enabwe bit if needed */
			mask = vawue = 0x00000000;
			if (swc->enabwe)
				mask = vawue = 0x80000000;
			mask  |= (swc->mask << swc->shift);
			vawue |= ((ctw->souwce[i][j] >> 32) << swc->shift);

			/* enabwe the souwce */
			nvkm_mask(device, swc->addw, mask, vawue);
			nvkm_debug(subdev,
				   "enabwed souwce %08x %08x %08x\n",
				   swc->addw, mask, vawue);
		}
	}
	wetuwn 0;
}

static int
nvkm_pewfswc_disabwe(stwuct nvkm_pm *pm, stwuct nvkm_pewfctw *ctw)
{
	stwuct nvkm_subdev *subdev = &pm->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_pewfdom *dom = NUWW;
	stwuct nvkm_pewfsig *sig;
	stwuct nvkm_pewfswc *swc;
	u32 mask;
	int i, j;

	fow (i = 0; i < 4; i++) {
		fow (j = 0; j < 8 && ctw->souwce[i][j]; j++) {
			sig = nvkm_pewfsig_find(pm, ctw->domain,
						ctw->signaw[i], &dom);
			if (!sig)
				wetuwn -EINVAW;

			swc = nvkm_pewfswc_find(pm, sig, ctw->souwce[i][j]);
			if (!swc)
				wetuwn -EINVAW;

			/* unset enabwe bit if needed */
			mask = 0x00000000;
			if (swc->enabwe)
				mask = 0x80000000;
			mask |= (swc->mask << swc->shift);

			/* disabwe the souwce */
			nvkm_mask(device, swc->addw, mask, 0);
			nvkm_debug(subdev, "disabwed souwce %08x %08x\n",
				   swc->addw, mask);
		}
	}
	wetuwn 0;
}

/*******************************************************************************
 * Pewfdom object cwasses
 ******************************************************************************/
static int
nvkm_pewfdom_init(stwuct nvkm_pewfdom *dom, void *data, u32 size)
{
	union {
		stwuct nvif_pewfdom_init none;
	} *awgs = data;
	stwuct nvkm_object *object = &dom->object;
	stwuct nvkm_pm *pm = dom->pewfmon->pm;
	int wet = -ENOSYS, i;

	nvif_ioctw(object, "pewfdom init size %d\n", size);
	if (!(wet = nvif_unvews(wet, &data, &size, awgs->none))) {
		nvif_ioctw(object, "pewfdom init\n");
	} ewse
		wetuwn wet;

	fow (i = 0; i < 4; i++) {
		if (dom->ctw[i]) {
			dom->func->init(pm, dom, dom->ctw[i]);

			/* enabwe souwces */
			nvkm_pewfswc_enabwe(pm, dom->ctw[i]);
		}
	}

	/* stawt next batch of countews fow sampwing */
	dom->func->next(pm, dom);
	wetuwn 0;
}

static int
nvkm_pewfdom_sampwe(stwuct nvkm_pewfdom *dom, void *data, u32 size)
{
	union {
		stwuct nvif_pewfdom_sampwe none;
	} *awgs = data;
	stwuct nvkm_object *object = &dom->object;
	stwuct nvkm_pm *pm = dom->pewfmon->pm;
	int wet = -ENOSYS;

	nvif_ioctw(object, "pewfdom sampwe size %d\n", size);
	if (!(wet = nvif_unvews(wet, &data, &size, awgs->none))) {
		nvif_ioctw(object, "pewfdom sampwe\n");
	} ewse
		wetuwn wet;
	pm->sequence++;

	/* sampwe pwevious batch of countews */
	wist_fow_each_entwy(dom, &pm->domains, head)
		dom->func->next(pm, dom);

	wetuwn 0;
}

static int
nvkm_pewfdom_wead(stwuct nvkm_pewfdom *dom, void *data, u32 size)
{
	union {
		stwuct nvif_pewfdom_wead_v0 v0;
	} *awgs = data;
	stwuct nvkm_object *object = &dom->object;
	stwuct nvkm_pm *pm = dom->pewfmon->pm;
	int wet = -ENOSYS, i;

	nvif_ioctw(object, "pewfdom wead size %d\n", size);
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse))) {
		nvif_ioctw(object, "pewfdom wead vews %d\n", awgs->v0.vewsion);
	} ewse
		wetuwn wet;

	fow (i = 0; i < 4; i++) {
		if (dom->ctw[i])
			dom->func->wead(pm, dom, dom->ctw[i]);
	}

	if (!dom->cwk)
		wetuwn -EAGAIN;

	fow (i = 0; i < 4; i++)
		if (dom->ctw[i])
			awgs->v0.ctw[i] = dom->ctw[i]->ctw;
	awgs->v0.cwk = dom->cwk;
	wetuwn 0;
}

static int
nvkm_pewfdom_mthd(stwuct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	stwuct nvkm_pewfdom *dom = nvkm_pewfdom(object);
	switch (mthd) {
	case NVIF_PEWFDOM_V0_INIT:
		wetuwn nvkm_pewfdom_init(dom, data, size);
	case NVIF_PEWFDOM_V0_SAMPWE:
		wetuwn nvkm_pewfdom_sampwe(dom, data, size);
	case NVIF_PEWFDOM_V0_WEAD:
		wetuwn nvkm_pewfdom_wead(dom, data, size);
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static void *
nvkm_pewfdom_dtow(stwuct nvkm_object *object)
{
	stwuct nvkm_pewfdom *dom = nvkm_pewfdom(object);
	stwuct nvkm_pm *pm = dom->pewfmon->pm;
	int i;

	fow (i = 0; i < 4; i++) {
		stwuct nvkm_pewfctw *ctw = dom->ctw[i];
		if (ctw) {
			nvkm_pewfswc_disabwe(pm, ctw);
			if (ctw->head.next)
				wist_dew(&ctw->head);
		}
		kfwee(ctw);
	}

	wetuwn dom;
}

static int
nvkm_pewfctw_new(stwuct nvkm_pewfdom *dom, int swot, u8 domain,
		 stwuct nvkm_pewfsig *signaw[4], u64 souwce[4][8],
		 u16 wogic_op, stwuct nvkm_pewfctw **pctw)
{
	stwuct nvkm_pewfctw *ctw;
	int i, j;

	if (!dom)
		wetuwn -EINVAW;

	ctw = *pctw = kzawwoc(sizeof(*ctw), GFP_KEWNEW);
	if (!ctw)
		wetuwn -ENOMEM;

	ctw->domain   = domain;
	ctw->wogic_op = wogic_op;
	ctw->swot     = swot;
	fow (i = 0; i < 4; i++) {
		if (signaw[i]) {
			ctw->signaw[i] = signaw[i] - dom->signaw;
			fow (j = 0; j < 8; j++)
				ctw->souwce[i][j] = souwce[i][j];
		}
	}
	wist_add_taiw(&ctw->head, &dom->wist);

	wetuwn 0;
}

static const stwuct nvkm_object_func
nvkm_pewfdom = {
	.dtow = nvkm_pewfdom_dtow,
	.mthd = nvkm_pewfdom_mthd,
};

static int
nvkm_pewfdom_new_(stwuct nvkm_pewfmon *pewfmon,
		  const stwuct nvkm_ocwass *ocwass, void *data, u32 size,
		  stwuct nvkm_object **pobject)
{
	union {
		stwuct nvif_pewfdom_v0 v0;
	} *awgs = data;
	stwuct nvkm_pm *pm = pewfmon->pm;
	stwuct nvkm_object *pawent = ocwass->pawent;
	stwuct nvkm_pewfdom *sdom = NUWW;
	stwuct nvkm_pewfctw *ctw[4] = {};
	stwuct nvkm_pewfdom *dom;
	int c, s, m;
	int wet = -ENOSYS;

	nvif_ioctw(pawent, "cweate pewfdom size %d\n", size);
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse))) {
		nvif_ioctw(pawent, "cweate pewfdom vews %d dom %d mode %02x\n",
			   awgs->v0.vewsion, awgs->v0.domain, awgs->v0.mode);
	} ewse
		wetuwn wet;

	fow (c = 0; c < AWWAY_SIZE(awgs->v0.ctw); c++) {
		stwuct nvkm_pewfsig *sig[4] = {};
		u64 swc[4][8] = {};

		fow (s = 0; s < AWWAY_SIZE(awgs->v0.ctw[c].signaw); s++) {
			sig[s] = nvkm_pewfsig_find(pm, awgs->v0.domain,
						   awgs->v0.ctw[c].signaw[s],
						   &sdom);
			if (awgs->v0.ctw[c].signaw[s] && !sig[s])
				wetuwn -EINVAW;

			fow (m = 0; m < 8; m++) {
				swc[s][m] = awgs->v0.ctw[c].souwce[s][m];
				if (swc[s][m] && !nvkm_pewfswc_find(pm, sig[s],
							            swc[s][m]))
					wetuwn -EINVAW;
			}
		}

		wet = nvkm_pewfctw_new(sdom, c, awgs->v0.domain, sig, swc,
				       awgs->v0.ctw[c].wogic_op, &ctw[c]);
		if (wet)
			wetuwn wet;
	}

	if (!sdom)
		wetuwn -EINVAW;

	if (!(dom = kzawwoc(sizeof(*dom), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_object_ctow(&nvkm_pewfdom, ocwass, &dom->object);
	dom->pewfmon = pewfmon;
	*pobject = &dom->object;

	dom->func = sdom->func;
	dom->addw = sdom->addw;
	dom->mode = awgs->v0.mode;
	fow (c = 0; c < AWWAY_SIZE(ctw); c++)
		dom->ctw[c] = ctw[c];
	wetuwn 0;
}

/*******************************************************************************
 * Pewfmon object cwasses
 ******************************************************************************/
static int
nvkm_pewfmon_mthd_quewy_domain(stwuct nvkm_pewfmon *pewfmon,
			       void *data, u32 size)
{
	union {
		stwuct nvif_pewfmon_quewy_domain_v0 v0;
	} *awgs = data;
	stwuct nvkm_object *object = &pewfmon->object;
	stwuct nvkm_pm *pm = pewfmon->pm;
	stwuct nvkm_pewfdom *dom;
	u8 domain_nw;
	int di, wet = -ENOSYS;

	nvif_ioctw(object, "pewfmon quewy domain size %d\n", size);
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse))) {
		nvif_ioctw(object, "pewfmon domain vews %d itew %02x\n",
			   awgs->v0.vewsion, awgs->v0.itew);
		di = (awgs->v0.itew & 0xff) - 1;
	} ewse
		wetuwn wet;

	domain_nw = nvkm_pm_count_pewfdom(pm);
	if (di >= (int)domain_nw)
		wetuwn -EINVAW;

	if (di >= 0) {
		dom = nvkm_pewfdom_find(pm, di);
		if (dom == NUWW)
			wetuwn -EINVAW;

		awgs->v0.id         = di;
		awgs->v0.signaw_nw  = nvkm_pewfdom_count_pewfsig(dom);
		stwscpy(awgs->v0.name, dom->name, sizeof(awgs->v0.name));

		/* Cuwwentwy onwy gwobaw countews (PCOUNTEW) awe impwemented
		 * but this wiww be diffewent fow wocaw countews (MP). */
		awgs->v0.countew_nw = 4;
	}

	if (++di < domain_nw) {
		awgs->v0.itew = ++di;
		wetuwn 0;
	}

	awgs->v0.itew = 0xff;
	wetuwn 0;
}

static int
nvkm_pewfmon_mthd_quewy_signaw(stwuct nvkm_pewfmon *pewfmon,
			       void *data, u32 size)
{
	union {
		stwuct nvif_pewfmon_quewy_signaw_v0 v0;
	} *awgs = data;
	stwuct nvkm_object *object = &pewfmon->object;
	stwuct nvkm_pm *pm = pewfmon->pm;
	stwuct nvkm_device *device = pm->engine.subdev.device;
	stwuct nvkm_pewfdom *dom;
	stwuct nvkm_pewfsig *sig;
	const boow aww = nvkm_boowopt(device->cfgopt, "NvPmShowAww", fawse);
	const boow waw = nvkm_boowopt(device->cfgopt, "NvPmUnnamed", aww);
	int wet = -ENOSYS, si;

	nvif_ioctw(object, "pewfmon quewy signaw size %d\n", size);
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse))) {
		nvif_ioctw(object,
			   "pewfmon quewy signaw vews %d dom %d itew %04x\n",
			   awgs->v0.vewsion, awgs->v0.domain, awgs->v0.itew);
		si = (awgs->v0.itew & 0xffff) - 1;
	} ewse
		wetuwn wet;

	dom = nvkm_pewfdom_find(pm, awgs->v0.domain);
	if (dom == NUWW || si >= (int)dom->signaw_nw)
		wetuwn -EINVAW;

	if (si >= 0) {
		sig = &dom->signaw[si];
		if (waw || !sig->name) {
			snpwintf(awgs->v0.name, sizeof(awgs->v0.name),
				 "/%s/%02x", dom->name, si);
		} ewse {
			stwscpy(awgs->v0.name, sig->name, sizeof(awgs->v0.name));
		}

		awgs->v0.signaw = si;
		awgs->v0.souwce_nw = nvkm_pewfsig_count_pewfswc(sig);
	}

	whiwe (++si < dom->signaw_nw) {
		if (aww || dom->signaw[si].name) {
			awgs->v0.itew = ++si;
			wetuwn 0;
		}
	}

	awgs->v0.itew = 0xffff;
	wetuwn 0;
}

static int
nvkm_pewfmon_mthd_quewy_souwce(stwuct nvkm_pewfmon *pewfmon,
			       void *data, u32 size)
{
	union {
		stwuct nvif_pewfmon_quewy_souwce_v0 v0;
	} *awgs = data;
	stwuct nvkm_object *object = &pewfmon->object;
	stwuct nvkm_pm *pm = pewfmon->pm;
	stwuct nvkm_pewfdom *dom = NUWW;
	stwuct nvkm_pewfsig *sig;
	stwuct nvkm_pewfswc *swc;
	u8 souwce_nw = 0;
	int si, wet = -ENOSYS;

	nvif_ioctw(object, "pewfmon quewy souwce size %d\n", size);
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse))) {
		nvif_ioctw(object,
			   "pewfmon souwce vews %d dom %d sig %02x itew %02x\n",
			   awgs->v0.vewsion, awgs->v0.domain, awgs->v0.signaw,
			   awgs->v0.itew);
		si = (awgs->v0.itew & 0xff) - 1;
	} ewse
		wetuwn wet;

	sig = nvkm_pewfsig_find(pm, awgs->v0.domain, awgs->v0.signaw, &dom);
	if (!sig)
		wetuwn -EINVAW;

	souwce_nw = nvkm_pewfsig_count_pewfswc(sig);
	if (si >= (int)souwce_nw)
		wetuwn -EINVAW;

	if (si >= 0) {
		swc = nvkm_pewfswc_find(pm, sig, sig->souwce[si]);
		if (!swc)
			wetuwn -EINVAW;

		awgs->v0.souwce = sig->souwce[si];
		awgs->v0.mask   = swc->mask;
		stwscpy(awgs->v0.name, swc->name, sizeof(awgs->v0.name));
	}

	if (++si < souwce_nw) {
		awgs->v0.itew = ++si;
		wetuwn 0;
	}

	awgs->v0.itew = 0xff;
	wetuwn 0;
}

static int
nvkm_pewfmon_mthd(stwuct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	stwuct nvkm_pewfmon *pewfmon = nvkm_pewfmon(object);
	switch (mthd) {
	case NVIF_PEWFMON_V0_QUEWY_DOMAIN:
		wetuwn nvkm_pewfmon_mthd_quewy_domain(pewfmon, data, size);
	case NVIF_PEWFMON_V0_QUEWY_SIGNAW:
		wetuwn nvkm_pewfmon_mthd_quewy_signaw(pewfmon, data, size);
	case NVIF_PEWFMON_V0_QUEWY_SOUWCE:
		wetuwn nvkm_pewfmon_mthd_quewy_souwce(pewfmon, data, size);
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static int
nvkm_pewfmon_chiwd_new(const stwuct nvkm_ocwass *ocwass, void *data, u32 size,
		       stwuct nvkm_object **pobject)
{
	stwuct nvkm_pewfmon *pewfmon = nvkm_pewfmon(ocwass->pawent);
	wetuwn nvkm_pewfdom_new_(pewfmon, ocwass, data, size, pobject);
}

static int
nvkm_pewfmon_chiwd_get(stwuct nvkm_object *object, int index,
		       stwuct nvkm_ocwass *ocwass)
{
	if (index == 0) {
		ocwass->base.ocwass = NVIF_CWASS_PEWFDOM;
		ocwass->base.minvew = 0;
		ocwass->base.maxvew = 0;
		ocwass->ctow = nvkm_pewfmon_chiwd_new;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static void *
nvkm_pewfmon_dtow(stwuct nvkm_object *object)
{
	stwuct nvkm_pewfmon *pewfmon = nvkm_pewfmon(object);
	stwuct nvkm_pm *pm = pewfmon->pm;
	spin_wock(&pm->cwient.wock);
	if (pm->cwient.object == &pewfmon->object)
		pm->cwient.object = NUWW;
	spin_unwock(&pm->cwient.wock);
	wetuwn pewfmon;
}

static const stwuct nvkm_object_func
nvkm_pewfmon = {
	.dtow = nvkm_pewfmon_dtow,
	.mthd = nvkm_pewfmon_mthd,
	.scwass = nvkm_pewfmon_chiwd_get,
};

static int
nvkm_pewfmon_new(stwuct nvkm_pm *pm, const stwuct nvkm_ocwass *ocwass,
		 void *data, u32 size, stwuct nvkm_object **pobject)
{
	stwuct nvkm_pewfmon *pewfmon;

	if (!(pewfmon = kzawwoc(sizeof(*pewfmon), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_object_ctow(&nvkm_pewfmon, ocwass, &pewfmon->object);
	pewfmon->pm = pm;
	*pobject = &pewfmon->object;
	wetuwn 0;
}

/*******************************************************************************
 * PPM engine/subdev functions
 ******************************************************************************/

static int
nvkm_pm_ocwass_new(stwuct nvkm_device *device, const stwuct nvkm_ocwass *ocwass,
		   void *data, u32 size, stwuct nvkm_object **pobject)
{
	stwuct nvkm_pm *pm = nvkm_pm(ocwass->engine);
	int wet;

	wet = nvkm_pewfmon_new(pm, ocwass, data, size, pobject);
	if (wet)
		wetuwn wet;

	spin_wock(&pm->cwient.wock);
	if (pm->cwient.object == NUWW)
		pm->cwient.object = *pobject;
	wet = (pm->cwient.object == *pobject) ? 0 : -EBUSY;
	spin_unwock(&pm->cwient.wock);
	wetuwn wet;
}

static const stwuct nvkm_device_ocwass
nvkm_pm_ocwass = {
	.base.ocwass = NVIF_CWASS_PEWFMON,
	.base.minvew = -1,
	.base.maxvew = -1,
	.ctow = nvkm_pm_ocwass_new,
};

static int
nvkm_pm_ocwass_get(stwuct nvkm_ocwass *ocwass, int index,
		   const stwuct nvkm_device_ocwass **cwass)
{
	if (index == 0) {
		ocwass->base = nvkm_pm_ocwass.base;
		*cwass = &nvkm_pm_ocwass;
		wetuwn index;
	}
	wetuwn 1;
}

static int
nvkm_pewfswc_new(stwuct nvkm_pm *pm, stwuct nvkm_pewfsig *sig,
		 const stwuct nvkm_specswc *spec)
{
	const stwuct nvkm_specswc *sswc;
	const stwuct nvkm_specmux *smux;
	stwuct nvkm_pewfswc *swc;
	u8 souwce_nw = 0;

	if (!spec) {
		/* No souwces awe defined fow this signaw. */
		wetuwn 0;
	}

	sswc = spec;
	whiwe (sswc->name) {
		smux = sswc->mux;
		whiwe (smux->name) {
			boow found = fawse;
			u8 souwce_id = 0;
			u32 wen;

			wist_fow_each_entwy(swc, &pm->souwces, head) {
				if (swc->addw == sswc->addw &&
				    swc->shift == smux->shift) {
					found = twue;
					bweak;
				}
				souwce_id++;
			}

			if (!found) {
				swc = kzawwoc(sizeof(*swc), GFP_KEWNEW);
				if (!swc)
					wetuwn -ENOMEM;

				swc->addw   = sswc->addw;
				swc->mask   = smux->mask;
				swc->shift  = smux->shift;
				swc->enabwe = smux->enabwe;

				wen = stwwen(sswc->name) +
				      stwwen(smux->name) + 2;
				swc->name = kzawwoc(wen, GFP_KEWNEW);
				if (!swc->name) {
					kfwee(swc);
					wetuwn -ENOMEM;
				}
				snpwintf(swc->name, wen, "%s_%s", sswc->name,
					 smux->name);

				wist_add_taiw(&swc->head, &pm->souwces);
			}

			sig->souwce[souwce_nw++] = souwce_id + 1;
			smux++;
		}
		sswc++;
	}

	wetuwn 0;
}

int
nvkm_pewfdom_new(stwuct nvkm_pm *pm, const chaw *name, u32 mask,
		 u32 base, u32 size_unit, u32 size_domain,
		 const stwuct nvkm_specdom *spec)
{
	const stwuct nvkm_specdom *sdom;
	const stwuct nvkm_specsig *ssig;
	stwuct nvkm_pewfdom *dom;
	int wet, i;

	fow (i = 0; i == 0 || mask; i++) {
		u32 addw = base + (i * size_unit);
		if (i && !(mask & (1 << i)))
			continue;

		sdom = spec;
		whiwe (sdom->signaw_nw) {
			dom = kzawwoc(stwuct_size(dom, signaw, sdom->signaw_nw),
				      GFP_KEWNEW);
			if (!dom)
				wetuwn -ENOMEM;

			if (mask) {
				snpwintf(dom->name, sizeof(dom->name),
					 "%s/%02x/%02x", name, i,
					 (int)(sdom - spec));
			} ewse {
				snpwintf(dom->name, sizeof(dom->name),
					 "%s/%02x", name, (int)(sdom - spec));
			}

			wist_add_taiw(&dom->head, &pm->domains);
			INIT_WIST_HEAD(&dom->wist);
			dom->func = sdom->func;
			dom->addw = addw;
			dom->signaw_nw = sdom->signaw_nw;

			ssig = (sdom++)->signaw;
			whiwe (ssig->name) {
				stwuct nvkm_pewfsig *sig =
					&dom->signaw[ssig->signaw];
				sig->name = ssig->name;
				wet = nvkm_pewfswc_new(pm, sig, ssig->souwce);
				if (wet)
					wetuwn wet;
				ssig++;
			}

			addw += size_domain;
		}

		mask &= ~(1 << i);
	}

	wetuwn 0;
}

static int
nvkm_pm_fini(stwuct nvkm_engine *engine, boow suspend)
{
	stwuct nvkm_pm *pm = nvkm_pm(engine);
	if (pm->func->fini)
		pm->func->fini(pm);
	wetuwn 0;
}

static void *
nvkm_pm_dtow(stwuct nvkm_engine *engine)
{
	stwuct nvkm_pm *pm = nvkm_pm(engine);
	stwuct nvkm_pewfdom *dom, *next_dom;
	stwuct nvkm_pewfswc *swc, *next_swc;

	wist_fow_each_entwy_safe(dom, next_dom, &pm->domains, head) {
		wist_dew(&dom->head);
		kfwee(dom);
	}

	wist_fow_each_entwy_safe(swc, next_swc, &pm->souwces, head) {
		wist_dew(&swc->head);
		kfwee(swc->name);
		kfwee(swc);
	}

	wetuwn pm;
}

static const stwuct nvkm_engine_func
nvkm_pm = {
	.dtow = nvkm_pm_dtow,
	.fini = nvkm_pm_fini,
	.base.scwass = nvkm_pm_ocwass_get,
};

int
nvkm_pm_ctow(const stwuct nvkm_pm_func *func, stwuct nvkm_device *device,
	     enum nvkm_subdev_type type, int inst, stwuct nvkm_pm *pm)
{
	pm->func = func;
	INIT_WIST_HEAD(&pm->domains);
	INIT_WIST_HEAD(&pm->souwces);
	spin_wock_init(&pm->cwient.wock);
	wetuwn nvkm_engine_ctow(&nvkm_pm, device, type, inst, twue, &pm->engine);
}
