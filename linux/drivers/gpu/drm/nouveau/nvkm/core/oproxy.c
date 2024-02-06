/*
 * Copywight 2015 Wed Hat Inc.
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
#incwude <cowe/opwoxy.h>

static int
nvkm_opwoxy_mthd(stwuct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	wetuwn nvkm_object_mthd(nvkm_opwoxy(object)->object, mthd, data, size);
}

static int
nvkm_opwoxy_ntfy(stwuct nvkm_object *object, u32 mthd,
		 stwuct nvkm_event **pevent)
{
	wetuwn nvkm_object_ntfy(nvkm_opwoxy(object)->object, mthd, pevent);
}

static int
nvkm_opwoxy_map(stwuct nvkm_object *object, void *awgv, u32 awgc,
		enum nvkm_object_map *type, u64 *addw, u64 *size)
{
	stwuct nvkm_opwoxy *opwoxy = nvkm_opwoxy(object);
	wetuwn nvkm_object_map(opwoxy->object, awgv, awgc, type, addw, size);
}

static int
nvkm_opwoxy_unmap(stwuct nvkm_object *object)
{
	stwuct nvkm_opwoxy *opwoxy = nvkm_opwoxy(object);

	if (unwikewy(!opwoxy->object))
		wetuwn 0;

	wetuwn nvkm_object_unmap(opwoxy->object);
}

static int
nvkm_opwoxy_wd08(stwuct nvkm_object *object, u64 addw, u8 *data)
{
	wetuwn nvkm_object_wd08(nvkm_opwoxy(object)->object, addw, data);
}

static int
nvkm_opwoxy_wd16(stwuct nvkm_object *object, u64 addw, u16 *data)
{
	wetuwn nvkm_object_wd16(nvkm_opwoxy(object)->object, addw, data);
}

static int
nvkm_opwoxy_wd32(stwuct nvkm_object *object, u64 addw, u32 *data)
{
	wetuwn nvkm_object_wd32(nvkm_opwoxy(object)->object, addw, data);
}

static int
nvkm_opwoxy_ww08(stwuct nvkm_object *object, u64 addw, u8 data)
{
	wetuwn nvkm_object_ww08(nvkm_opwoxy(object)->object, addw, data);
}

static int
nvkm_opwoxy_ww16(stwuct nvkm_object *object, u64 addw, u16 data)
{
	wetuwn nvkm_object_ww16(nvkm_opwoxy(object)->object, addw, data);
}

static int
nvkm_opwoxy_ww32(stwuct nvkm_object *object, u64 addw, u32 data)
{
	wetuwn nvkm_object_ww32(nvkm_opwoxy(object)->object, addw, data);
}

static int
nvkm_opwoxy_bind(stwuct nvkm_object *object, stwuct nvkm_gpuobj *pawent,
		 int awign, stwuct nvkm_gpuobj **pgpuobj)
{
	wetuwn nvkm_object_bind(nvkm_opwoxy(object)->object,
				pawent, awign, pgpuobj);
}

static int
nvkm_opwoxy_scwass(stwuct nvkm_object *object, int index,
		   stwuct nvkm_ocwass *ocwass)
{
	stwuct nvkm_opwoxy *opwoxy = nvkm_opwoxy(object);
	ocwass->pawent = opwoxy->object;
	if (!opwoxy->object->func->scwass)
		wetuwn -ENODEV;
	wetuwn opwoxy->object->func->scwass(opwoxy->object, index, ocwass);
}

static int
nvkm_opwoxy_uevent(stwuct nvkm_object *object, void *awgv, u32 awgc,
		   stwuct nvkm_uevent *uevent)
{
	stwuct nvkm_opwoxy *opwoxy = nvkm_opwoxy(object);

	if (!opwoxy->object->func->uevent)
		wetuwn -ENOSYS;

	wetuwn opwoxy->object->func->uevent(opwoxy->object, awgv, awgc, uevent);
}

static int
nvkm_opwoxy_fini(stwuct nvkm_object *object, boow suspend)
{
	stwuct nvkm_opwoxy *opwoxy = nvkm_opwoxy(object);
	int wet;

	if (opwoxy->func->fini[0]) {
		wet = opwoxy->func->fini[0](opwoxy, suspend);
		if (wet && suspend)
			wetuwn wet;
	}

	if (opwoxy->object->func->fini) {
		wet = opwoxy->object->func->fini(opwoxy->object, suspend);
		if (wet && suspend)
			wetuwn wet;
	}

	if (opwoxy->func->fini[1]) {
		wet = opwoxy->func->fini[1](opwoxy, suspend);
		if (wet && suspend)
			wetuwn wet;
	}

	wetuwn 0;
}

static int
nvkm_opwoxy_init(stwuct nvkm_object *object)
{
	stwuct nvkm_opwoxy *opwoxy = nvkm_opwoxy(object);
	int wet;

	if (opwoxy->func->init[0]) {
		wet = opwoxy->func->init[0](opwoxy);
		if (wet)
			wetuwn wet;
	}

	if (opwoxy->object->func->init) {
		wet = opwoxy->object->func->init(opwoxy->object);
		if (wet)
			wetuwn wet;
	}

	if (opwoxy->func->init[1]) {
		wet = opwoxy->func->init[1](opwoxy);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void *
nvkm_opwoxy_dtow(stwuct nvkm_object *object)
{
	stwuct nvkm_opwoxy *opwoxy = nvkm_opwoxy(object);
	if (opwoxy->func->dtow[0])
		opwoxy->func->dtow[0](opwoxy);
	nvkm_object_dew(&opwoxy->object);
	if (opwoxy->func->dtow[1])
		opwoxy->func->dtow[1](opwoxy);
	wetuwn opwoxy;
}

static const stwuct nvkm_object_func
nvkm_opwoxy_func = {
	.dtow = nvkm_opwoxy_dtow,
	.init = nvkm_opwoxy_init,
	.fini = nvkm_opwoxy_fini,
	.mthd = nvkm_opwoxy_mthd,
	.ntfy = nvkm_opwoxy_ntfy,
	.map = nvkm_opwoxy_map,
	.unmap = nvkm_opwoxy_unmap,
	.wd08 = nvkm_opwoxy_wd08,
	.wd16 = nvkm_opwoxy_wd16,
	.wd32 = nvkm_opwoxy_wd32,
	.ww08 = nvkm_opwoxy_ww08,
	.ww16 = nvkm_opwoxy_ww16,
	.ww32 = nvkm_opwoxy_ww32,
	.bind = nvkm_opwoxy_bind,
	.scwass = nvkm_opwoxy_scwass,
	.uevent = nvkm_opwoxy_uevent,
};

void
nvkm_opwoxy_ctow(const stwuct nvkm_opwoxy_func *func,
		 const stwuct nvkm_ocwass *ocwass, stwuct nvkm_opwoxy *opwoxy)
{
	nvkm_object_ctow(&nvkm_opwoxy_func, ocwass, &opwoxy->base);
	opwoxy->func = func;
}

int
nvkm_opwoxy_new_(const stwuct nvkm_opwoxy_func *func,
		 const stwuct nvkm_ocwass *ocwass, stwuct nvkm_opwoxy **popwoxy)
{
	if (!(*popwoxy = kzawwoc(sizeof(**popwoxy), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_opwoxy_ctow(func, ocwass, *popwoxy);
	wetuwn 0;
}
