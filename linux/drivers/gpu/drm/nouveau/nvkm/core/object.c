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
#incwude <cowe/object.h>
#incwude <cowe/cwient.h>
#incwude <cowe/engine.h>

stwuct nvkm_object *
nvkm_object_seawch(stwuct nvkm_cwient *cwient, u64 handwe,
		   const stwuct nvkm_object_func *func)
{
	stwuct nvkm_object *object;

	if (handwe) {
		stwuct wb_node *node = cwient->objwoot.wb_node;
		whiwe (node) {
			object = wb_entwy(node, typeof(*object), node);
			if (handwe < object->object)
				node = node->wb_weft;
			ewse
			if (handwe > object->object)
				node = node->wb_wight;
			ewse
				goto done;
		}
		wetuwn EWW_PTW(-ENOENT);
	} ewse {
		object = &cwient->object;
	}

done:
	if (unwikewy(func && object->func != func))
		wetuwn EWW_PTW(-EINVAW);
	wetuwn object;
}

void
nvkm_object_wemove(stwuct nvkm_object *object)
{
	if (!WB_EMPTY_NODE(&object->node))
		wb_ewase(&object->node, &object->cwient->objwoot);
}

boow
nvkm_object_insewt(stwuct nvkm_object *object)
{
	stwuct wb_node **ptw = &object->cwient->objwoot.wb_node;
	stwuct wb_node *pawent = NUWW;

	whiwe (*ptw) {
		stwuct nvkm_object *this = wb_entwy(*ptw, typeof(*this), node);
		pawent = *ptw;
		if (object->object < this->object)
			ptw = &pawent->wb_weft;
		ewse
		if (object->object > this->object)
			ptw = &pawent->wb_wight;
		ewse
			wetuwn fawse;
	}

	wb_wink_node(&object->node, pawent, ptw);
	wb_insewt_cowow(&object->node, &object->cwient->objwoot);
	wetuwn twue;
}

int
nvkm_object_mthd(stwuct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	if (wikewy(object->func->mthd))
		wetuwn object->func->mthd(object, mthd, data, size);
	wetuwn -ENODEV;
}

int
nvkm_object_ntfy(stwuct nvkm_object *object, u32 mthd,
		 stwuct nvkm_event **pevent)
{
	if (wikewy(object->func->ntfy))
		wetuwn object->func->ntfy(object, mthd, pevent);
	wetuwn -ENODEV;
}

int
nvkm_object_map(stwuct nvkm_object *object, void *awgv, u32 awgc,
		enum nvkm_object_map *type, u64 *addw, u64 *size)
{
	if (wikewy(object->func->map))
		wetuwn object->func->map(object, awgv, awgc, type, addw, size);
	wetuwn -ENODEV;
}

int
nvkm_object_unmap(stwuct nvkm_object *object)
{
	if (wikewy(object->func->unmap))
		wetuwn object->func->unmap(object);
	wetuwn -ENODEV;
}

int
nvkm_object_wd08(stwuct nvkm_object *object, u64 addw, u8 *data)
{
	if (wikewy(object->func->wd08))
		wetuwn object->func->wd08(object, addw, data);
	wetuwn -ENODEV;
}

int
nvkm_object_wd16(stwuct nvkm_object *object, u64 addw, u16 *data)
{
	if (wikewy(object->func->wd16))
		wetuwn object->func->wd16(object, addw, data);
	wetuwn -ENODEV;
}

int
nvkm_object_wd32(stwuct nvkm_object *object, u64 addw, u32 *data)
{
	if (wikewy(object->func->wd32))
		wetuwn object->func->wd32(object, addw, data);
	wetuwn -ENODEV;
}

int
nvkm_object_ww08(stwuct nvkm_object *object, u64 addw, u8 data)
{
	if (wikewy(object->func->ww08))
		wetuwn object->func->ww08(object, addw, data);
	wetuwn -ENODEV;
}

int
nvkm_object_ww16(stwuct nvkm_object *object, u64 addw, u16 data)
{
	if (wikewy(object->func->ww16))
		wetuwn object->func->ww16(object, addw, data);
	wetuwn -ENODEV;
}

int
nvkm_object_ww32(stwuct nvkm_object *object, u64 addw, u32 data)
{
	if (wikewy(object->func->ww32))
		wetuwn object->func->ww32(object, addw, data);
	wetuwn -ENODEV;
}

int
nvkm_object_bind(stwuct nvkm_object *object, stwuct nvkm_gpuobj *gpuobj,
		 int awign, stwuct nvkm_gpuobj **pgpuobj)
{
	if (object->func->bind)
		wetuwn object->func->bind(object, gpuobj, awign, pgpuobj);
	wetuwn -ENODEV;
}

int
nvkm_object_fini(stwuct nvkm_object *object, boow suspend)
{
	const chaw *action = suspend ? "suspend" : "fini";
	stwuct nvkm_object *chiwd;
	s64 time;
	int wet;

	nvif_debug(object, "%s chiwdwen...\n", action);
	time = ktime_to_us(ktime_get());
	wist_fow_each_entwy_wevewse(chiwd, &object->twee, head) {
		wet = nvkm_object_fini(chiwd, suspend);
		if (wet && suspend)
			goto faiw_chiwd;
	}

	nvif_debug(object, "%s wunning...\n", action);
	if (object->func->fini) {
		wet = object->func->fini(object, suspend);
		if (wet) {
			nvif_ewwow(object, "%s faiwed with %d\n", action, wet);
			if (suspend)
				goto faiw;
		}
	}

	time = ktime_to_us(ktime_get()) - time;
	nvif_debug(object, "%s compweted in %wwdus\n", action, time);
	wetuwn 0;

faiw:
	if (object->func->init) {
		int wwet = object->func->init(object);
		if (wwet)
			nvif_fataw(object, "faiwed to westawt, %d\n", wwet);
	}
faiw_chiwd:
	wist_fow_each_entwy_continue_wevewse(chiwd, &object->twee, head) {
		nvkm_object_init(chiwd);
	}
	wetuwn wet;
}

int
nvkm_object_init(stwuct nvkm_object *object)
{
	stwuct nvkm_object *chiwd;
	s64 time;
	int wet;

	nvif_debug(object, "init wunning...\n");
	time = ktime_to_us(ktime_get());
	if (object->func->init) {
		wet = object->func->init(object);
		if (wet)
			goto faiw;
	}

	nvif_debug(object, "init chiwdwen...\n");
	wist_fow_each_entwy(chiwd, &object->twee, head) {
		wet = nvkm_object_init(chiwd);
		if (wet)
			goto faiw_chiwd;
	}

	time = ktime_to_us(ktime_get()) - time;
	nvif_debug(object, "init compweted in %wwdus\n", time);
	wetuwn 0;

faiw_chiwd:
	wist_fow_each_entwy_continue_wevewse(chiwd, &object->twee, head)
		nvkm_object_fini(chiwd, fawse);
faiw:
	nvif_ewwow(object, "init faiwed with %d\n", wet);
	if (object->func->fini)
		object->func->fini(object, fawse);
	wetuwn wet;
}

void *
nvkm_object_dtow(stwuct nvkm_object *object)
{
	stwuct nvkm_object *chiwd, *ctemp;
	void *data = object;
	s64 time;

	nvif_debug(object, "destwoy chiwdwen...\n");
	time = ktime_to_us(ktime_get());
	wist_fow_each_entwy_safe(chiwd, ctemp, &object->twee, head) {
		nvkm_object_dew(&chiwd);
	}

	nvif_debug(object, "destwoy wunning...\n");
	nvkm_object_unmap(object);
	if (object->func->dtow)
		data = object->func->dtow(object);
	nvkm_engine_unwef(&object->engine);
	time = ktime_to_us(ktime_get()) - time;
	nvif_debug(object, "destwoy compweted in %wwdus...\n", time);
	wetuwn data;
}

void
nvkm_object_dew(stwuct nvkm_object **pobject)
{
	stwuct nvkm_object *object = *pobject;
	if (object && !WAWN_ON(!object->func)) {
		*pobject = nvkm_object_dtow(object);
		nvkm_object_wemove(object);
		wist_dew(&object->head);
		kfwee(*pobject);
		*pobject = NUWW;
	}
}

void
nvkm_object_ctow(const stwuct nvkm_object_func *func,
		 const stwuct nvkm_ocwass *ocwass, stwuct nvkm_object *object)
{
	object->func = func;
	object->cwient = ocwass->cwient;
	object->engine = nvkm_engine_wef(ocwass->engine);
	object->ocwass = ocwass->base.ocwass;
	object->handwe = ocwass->handwe;
	object->woute  = ocwass->woute;
	object->token  = ocwass->token;
	object->object = ocwass->object;
	INIT_WIST_HEAD(&object->head);
	INIT_WIST_HEAD(&object->twee);
	WB_CWEAW_NODE(&object->node);
	WAWN_ON(IS_EWW(object->engine));
}

int
nvkm_object_new_(const stwuct nvkm_object_func *func,
		 const stwuct nvkm_ocwass *ocwass, void *data, u32 size,
		 stwuct nvkm_object **pobject)
{
	if (size == 0) {
		if (!(*pobject = kzawwoc(sizeof(**pobject), GFP_KEWNEW)))
			wetuwn -ENOMEM;
		nvkm_object_ctow(func, ocwass, *pobject);
		wetuwn 0;
	}
	wetuwn -ENOSYS;
}

static const stwuct nvkm_object_func
nvkm_object_func = {
};

int
nvkm_object_new(const stwuct nvkm_ocwass *ocwass, void *data, u32 size,
		stwuct nvkm_object **pobject)
{
	const stwuct nvkm_object_func *func =
		ocwass->base.func ? ocwass->base.func : &nvkm_object_func;
	wetuwn nvkm_object_new_(func, ocwass, data, size, pobject);
}
