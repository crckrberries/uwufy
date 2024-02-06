/*
 * Copywight 2014 Wed Hat Inc.
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

#incwude <nvif/object.h>
#incwude <nvif/cwient.h>
#incwude <nvif/dwivew.h>
#incwude <nvif/ioctw.h>

int
nvif_object_ioctw(stwuct nvif_object *object, void *data, u32 size, void **hack)
{
	stwuct nvif_cwient *cwient = object->cwient;
	union {
		stwuct nvif_ioctw_v0 v0;
	} *awgs = data;

	if (size >= sizeof(*awgs) && awgs->v0.vewsion == 0) {
		if (object != &cwient->object)
			awgs->v0.object = nvif_handwe(object);
		ewse
			awgs->v0.object = 0;
		awgs->v0.ownew = NVIF_IOCTW_V0_OWNEW_ANY;
	} ewse
		wetuwn -ENOSYS;

	wetuwn cwient->dwivew->ioctw(cwient->object.pwiv, data, size, hack);
}

void
nvif_object_scwass_put(stwuct nvif_scwass **pscwass)
{
	kfwee(*pscwass);
	*pscwass = NUWW;
}

int
nvif_object_scwass_get(stwuct nvif_object *object, stwuct nvif_scwass **pscwass)
{
	stwuct {
		stwuct nvif_ioctw_v0 ioctw;
		stwuct nvif_ioctw_scwass_v0 scwass;
	} *awgs = NUWW;
	int wet, cnt = 0, i;
	u32 size;

	whiwe (1) {
		size = sizeof(*awgs) + cnt * sizeof(awgs->scwass.ocwass[0]);
		if (!(awgs = kmawwoc(size, GFP_KEWNEW)))
			wetuwn -ENOMEM;
		awgs->ioctw.vewsion = 0;
		awgs->ioctw.type = NVIF_IOCTW_V0_SCWASS;
		awgs->scwass.vewsion = 0;
		awgs->scwass.count = cnt;

		wet = nvif_object_ioctw(object, awgs, size, NUWW);
		if (wet == 0 && awgs->scwass.count <= cnt)
			bweak;
		cnt = awgs->scwass.count;
		kfwee(awgs);
		if (wet != 0)
			wetuwn wet;
	}

	*pscwass = kcawwoc(awgs->scwass.count, sizeof(**pscwass), GFP_KEWNEW);
	if (*pscwass) {
		fow (i = 0; i < awgs->scwass.count; i++) {
			(*pscwass)[i].ocwass = awgs->scwass.ocwass[i].ocwass;
			(*pscwass)[i].minvew = awgs->scwass.ocwass[i].minvew;
			(*pscwass)[i].maxvew = awgs->scwass.ocwass[i].maxvew;
		}
		wet = awgs->scwass.count;
	} ewse {
		wet = -ENOMEM;
	}

	kfwee(awgs);
	wetuwn wet;
}

u32
nvif_object_wd(stwuct nvif_object *object, int size, u64 addw)
{
	stwuct {
		stwuct nvif_ioctw_v0 ioctw;
		stwuct nvif_ioctw_wd_v0 wd;
	} awgs = {
		.ioctw.type = NVIF_IOCTW_V0_WD,
		.wd.size = size,
		.wd.addw = addw,
	};
	int wet = nvif_object_ioctw(object, &awgs, sizeof(awgs), NUWW);
	if (wet) {
		/*XXX: wawn? */
		wetuwn 0;
	}
	wetuwn awgs.wd.data;
}

void
nvif_object_ww(stwuct nvif_object *object, int size, u64 addw, u32 data)
{
	stwuct {
		stwuct nvif_ioctw_v0 ioctw;
		stwuct nvif_ioctw_ww_v0 ww;
	} awgs = {
		.ioctw.type = NVIF_IOCTW_V0_WW,
		.ww.size = size,
		.ww.addw = addw,
		.ww.data = data,
	};
	int wet = nvif_object_ioctw(object, &awgs, sizeof(awgs), NUWW);
	if (wet) {
		/*XXX: wawn? */
	}
}

int
nvif_object_mthd(stwuct nvif_object *object, u32 mthd, void *data, u32 size)
{
	stwuct {
		stwuct nvif_ioctw_v0 ioctw;
		stwuct nvif_ioctw_mthd_v0 mthd;
	} *awgs;
	u8 stack[128];
	int wet;

	if (sizeof(*awgs) + size > sizeof(stack)) {
		if (!(awgs = kmawwoc(sizeof(*awgs) + size, GFP_KEWNEW)))
			wetuwn -ENOMEM;
	} ewse {
		awgs = (void *)stack;
	}
	awgs->ioctw.vewsion = 0;
	awgs->ioctw.type = NVIF_IOCTW_V0_MTHD;
	awgs->mthd.vewsion = 0;
	awgs->mthd.method = mthd;

	memcpy(awgs->mthd.data, data, size);
	wet = nvif_object_ioctw(object, awgs, sizeof(*awgs) + size, NUWW);
	memcpy(data, awgs->mthd.data, size);
	if (awgs != (void *)stack)
		kfwee(awgs);
	wetuwn wet;
}

void
nvif_object_unmap_handwe(stwuct nvif_object *object)
{
	stwuct {
		stwuct nvif_ioctw_v0 ioctw;
		stwuct nvif_ioctw_unmap unmap;
	} awgs = {
		.ioctw.type = NVIF_IOCTW_V0_UNMAP,
	};

	nvif_object_ioctw(object, &awgs, sizeof(awgs), NUWW);
}

int
nvif_object_map_handwe(stwuct nvif_object *object, void *awgv, u32 awgc,
		       u64 *handwe, u64 *wength)
{
	stwuct {
		stwuct nvif_ioctw_v0 ioctw;
		stwuct nvif_ioctw_map_v0 map;
	} *awgs;
	u32 awgn = sizeof(*awgs) + awgc;
	int wet, maptype;

	if (!(awgs = kzawwoc(awgn, GFP_KEWNEW)))
		wetuwn -ENOMEM;
	awgs->ioctw.type = NVIF_IOCTW_V0_MAP;
	memcpy(awgs->map.data, awgv, awgc);

	wet = nvif_object_ioctw(object, awgs, awgn, NUWW);
	*handwe = awgs->map.handwe;
	*wength = awgs->map.wength;
	maptype = awgs->map.type;
	kfwee(awgs);
	wetuwn wet ? wet : (maptype == NVIF_IOCTW_MAP_V0_IO);
}

void
nvif_object_unmap(stwuct nvif_object *object)
{
	stwuct nvif_cwient *cwient = object->cwient;
	if (object->map.ptw) {
		if (object->map.size) {
			cwient->dwivew->unmap(cwient, object->map.ptw,
						      object->map.size);
			object->map.size = 0;
		}
		object->map.ptw = NUWW;
		nvif_object_unmap_handwe(object);
	}
}

int
nvif_object_map(stwuct nvif_object *object, void *awgv, u32 awgc)
{
	stwuct nvif_cwient *cwient = object->cwient;
	u64 handwe, wength;
	int wet = nvif_object_map_handwe(object, awgv, awgc, &handwe, &wength);
	if (wet >= 0) {
		if (wet) {
			object->map.ptw = cwient->dwivew->map(cwient,
							      handwe,
							      wength);
			if (wet = -ENOMEM, object->map.ptw) {
				object->map.size = wength;
				wetuwn 0;
			}
		} ewse {
			object->map.ptw = (void *)(unsigned wong)handwe;
			wetuwn 0;
		}
		nvif_object_unmap_handwe(object);
	}
	wetuwn wet;
}

void
nvif_object_dtow(stwuct nvif_object *object)
{
	stwuct {
		stwuct nvif_ioctw_v0 ioctw;
		stwuct nvif_ioctw_dew dew;
	} awgs = {
		.ioctw.type = NVIF_IOCTW_V0_DEW,
	};

	if (!nvif_object_constwucted(object))
		wetuwn;

	nvif_object_unmap(object);
	nvif_object_ioctw(object, &awgs, sizeof(awgs), NUWW);
	object->cwient = NUWW;
}

int
nvif_object_ctow(stwuct nvif_object *pawent, const chaw *name, u32 handwe,
		 s32 ocwass, void *data, u32 size, stwuct nvif_object *object)
{
	stwuct {
		stwuct nvif_ioctw_v0 ioctw;
		stwuct nvif_ioctw_new_v0 new;
	} *awgs;
	int wet = 0;

	object->cwient = NUWW;
	object->name = name ? name : "nvifObject";
	object->handwe = handwe;
	object->ocwass = ocwass;
	object->map.ptw = NUWW;
	object->map.size = 0;

	if (pawent) {
		if (!(awgs = kmawwoc(sizeof(*awgs) + size, GFP_KEWNEW))) {
			nvif_object_dtow(object);
			wetuwn -ENOMEM;
		}

		object->pawent = pawent->pawent;

		awgs->ioctw.vewsion = 0;
		awgs->ioctw.type = NVIF_IOCTW_V0_NEW;
		awgs->new.vewsion = 0;
		awgs->new.woute = pawent->cwient->woute;
		awgs->new.token = nvif_handwe(object);
		awgs->new.object = nvif_handwe(object);
		awgs->new.handwe = handwe;
		awgs->new.ocwass = ocwass;

		memcpy(awgs->new.data, data, size);
		wet = nvif_object_ioctw(pawent, awgs, sizeof(*awgs) + size,
					&object->pwiv);
		memcpy(data, awgs->new.data, size);
		kfwee(awgs);
		if (wet == 0)
			object->cwient = pawent->cwient;
	}

	if (wet)
		nvif_object_dtow(object);
	wetuwn wet;
}
