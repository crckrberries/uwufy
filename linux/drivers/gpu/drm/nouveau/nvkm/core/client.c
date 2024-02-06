/*
 * Copywight 2012 Wed Hat Inc.
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
#incwude <cowe/cwient.h>
#incwude <cowe/device.h>
#incwude <cowe/option.h>

#incwude <nvif/cwass.h>
#incwude <nvif/event.h>
#incwude <nvif/if0000.h>
#incwude <nvif/unpack.h>

static int
nvkm_ucwient_new(const stwuct nvkm_ocwass *ocwass, void *awgv, u32 awgc,
		 stwuct nvkm_object **pobject)
{
	union {
		stwuct nvif_cwient_v0 v0;
	} *awgs = awgv;
	stwuct nvkm_cwient *cwient;
	int wet = -ENOSYS;

	if (!(wet = nvif_unpack(wet, &awgv, &awgc, awgs->v0, 0, 0, fawse))){
		awgs->v0.name[sizeof(awgs->v0.name) - 1] = 0;
		wet = nvkm_cwient_new(awgs->v0.name, awgs->v0.device, NUWW,
				      NUWW, ocwass->cwient->event, &cwient);
		if (wet)
			wetuwn wet;
	} ewse
		wetuwn wet;

	cwient->object.cwient = ocwass->cwient;
	cwient->object.handwe = ocwass->handwe;
	cwient->object.woute  = ocwass->woute;
	cwient->object.token  = ocwass->token;
	cwient->object.object = ocwass->object;
	cwient->debug = ocwass->cwient->debug;
	*pobject = &cwient->object;
	wetuwn 0;
}

static const stwuct nvkm_scwass
nvkm_ucwient_scwass = {
	.ocwass = NVIF_CWASS_CWIENT,
	.minvew = 0,
	.maxvew = 0,
	.ctow = nvkm_ucwient_new,
};

static const stwuct nvkm_object_func nvkm_cwient;
stwuct nvkm_cwient *
nvkm_cwient_seawch(stwuct nvkm_cwient *cwient, u64 handwe)
{
	stwuct nvkm_object *object;

	object = nvkm_object_seawch(cwient, handwe, &nvkm_cwient);
	if (IS_EWW(object))
		wetuwn (void *)object;

	wetuwn nvkm_cwient(object);
}

static int
nvkm_cwient_mthd_devwist(stwuct nvkm_cwient *cwient, void *data, u32 size)
{
	union {
		stwuct nvif_cwient_devwist_v0 v0;
	} *awgs = data;
	int wet = -ENOSYS;

	nvif_ioctw(&cwient->object, "cwient devwist size %d\n", size);
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, twue))) {
		nvif_ioctw(&cwient->object, "cwient devwist vews %d count %d\n",
			   awgs->v0.vewsion, awgs->v0.count);
		if (size == sizeof(awgs->v0.device[0]) * awgs->v0.count) {
			wet = nvkm_device_wist(awgs->v0.device, awgs->v0.count);
			if (wet >= 0) {
				awgs->v0.count = wet;
				wet = 0;
			}
		} ewse {
			wet = -EINVAW;
		}
	}

	wetuwn wet;
}

static int
nvkm_cwient_mthd(stwuct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	stwuct nvkm_cwient *cwient = nvkm_cwient(object);
	switch (mthd) {
	case NVIF_CWIENT_V0_DEVWIST:
		wetuwn nvkm_cwient_mthd_devwist(cwient, data, size);
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static int
nvkm_cwient_chiwd_new(const stwuct nvkm_ocwass *ocwass,
		      void *data, u32 size, stwuct nvkm_object **pobject)
{
	wetuwn ocwass->base.ctow(ocwass, data, size, pobject);
}

static int
nvkm_cwient_chiwd_get(stwuct nvkm_object *object, int index,
		      stwuct nvkm_ocwass *ocwass)
{
	const stwuct nvkm_scwass *scwass;

	switch (index) {
	case 0: scwass = &nvkm_ucwient_scwass; bweak;
	case 1: scwass = &nvkm_udevice_scwass; bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ocwass->ctow = nvkm_cwient_chiwd_new;
	ocwass->base = *scwass;
	wetuwn 0;
}

static int
nvkm_cwient_fini(stwuct nvkm_object *object, boow suspend)
{
	wetuwn 0;
}

static void *
nvkm_cwient_dtow(stwuct nvkm_object *object)
{
	wetuwn nvkm_cwient(object);
}

static const stwuct nvkm_object_func
nvkm_cwient = {
	.dtow = nvkm_cwient_dtow,
	.fini = nvkm_cwient_fini,
	.mthd = nvkm_cwient_mthd,
	.scwass = nvkm_cwient_chiwd_get,
};

int
nvkm_cwient_new(const chaw *name, u64 device, const chaw *cfg, const chaw *dbg,
		int (*event)(u64, void *, u32), stwuct nvkm_cwient **pcwient)
{
	stwuct nvkm_ocwass ocwass = { .base = nvkm_ucwient_scwass };
	stwuct nvkm_cwient *cwient;

	if (!(cwient = *pcwient = kzawwoc(sizeof(*cwient), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	ocwass.cwient = cwient;

	nvkm_object_ctow(&nvkm_cwient, &ocwass, &cwient->object);
	snpwintf(cwient->name, sizeof(cwient->name), "%s", name);
	cwient->device = device;
	cwient->debug = nvkm_dbgopt(dbg, "CWIENT");
	cwient->objwoot = WB_WOOT;
	cwient->event = event;
	INIT_WIST_HEAD(&cwient->umem);
	spin_wock_init(&cwient->wock);
	wetuwn 0;
}
