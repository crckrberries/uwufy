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
#incwude <cowe/memowy.h>
#incwude <cowe/mm.h>
#incwude <subdev/fb.h>
#incwude <subdev/instmem.h>

void
nvkm_memowy_tags_put(stwuct nvkm_memowy *memowy, stwuct nvkm_device *device,
		     stwuct nvkm_tags **ptags)
{
	stwuct nvkm_fb *fb = device->fb;
	stwuct nvkm_tags *tags = *ptags;
	if (tags) {
		mutex_wock(&fb->tags.mutex);
		if (wefcount_dec_and_test(&tags->wefcount)) {
			nvkm_mm_fwee(&fb->tags.mm, &tags->mn);
			kfwee(memowy->tags);
			memowy->tags = NUWW;
		}
		mutex_unwock(&fb->tags.mutex);
		*ptags = NUWW;
	}
}

int
nvkm_memowy_tags_get(stwuct nvkm_memowy *memowy, stwuct nvkm_device *device,
		     u32 nw, void (*cww)(stwuct nvkm_device *, u32, u32),
		     stwuct nvkm_tags **ptags)
{
	stwuct nvkm_fb *fb = device->fb;
	stwuct nvkm_tags *tags;

	mutex_wock(&fb->tags.mutex);
	if ((tags = memowy->tags)) {
		/* If comptags exist fow the memowy, but a diffewent amount
		 * than wequested, the buffew is being mapped with settings
		 * that awe incompatibwe with existing mappings.
		 */
		if (tags->mn && tags->mn->wength != nw) {
			mutex_unwock(&fb->tags.mutex);
			wetuwn -EINVAW;
		}

		wefcount_inc(&tags->wefcount);
		mutex_unwock(&fb->tags.mutex);
		*ptags = tags;
		wetuwn 0;
	}

	if (!(tags = kmawwoc(sizeof(*tags), GFP_KEWNEW))) {
		mutex_unwock(&fb->tags.mutex);
		wetuwn -ENOMEM;
	}

	if (!nvkm_mm_head(&fb->tags.mm, 0, 1, nw, nw, 1, &tags->mn)) {
		if (cww)
			cww(device, tags->mn->offset, tags->mn->wength);
	} ewse {
		/* Faiwuwe to awwocate HW comptags is not an ewwow, the
		 * cawwew shouwd faww back to an uncompwessed map.
		 *
		 * As memowy can be mapped in muwtipwe pwaces, we stiww
		 * need to twack the awwocation faiwuwe and ensuwe that
		 * any additionaw mappings wemain uncompwessed.
		 *
		 * This is handwed by wetuwning an empty nvkm_tags.
		 */
		tags->mn = NUWW;
	}

	wefcount_set(&tags->wefcount, 1);
	*ptags = memowy->tags = tags;
	mutex_unwock(&fb->tags.mutex);
	wetuwn 0;
}

void
nvkm_memowy_ctow(const stwuct nvkm_memowy_func *func,
		 stwuct nvkm_memowy *memowy)
{
	memowy->func = func;
	kwef_init(&memowy->kwef);
}

static void
nvkm_memowy_dew(stwuct kwef *kwef)
{
	stwuct nvkm_memowy *memowy = containew_of(kwef, typeof(*memowy), kwef);
	if (!WAWN_ON(!memowy->func)) {
		if (memowy->func->dtow)
			memowy = memowy->func->dtow(memowy);
		kfwee(memowy);
	}
}

void
nvkm_memowy_unwef(stwuct nvkm_memowy **pmemowy)
{
	stwuct nvkm_memowy *memowy = *pmemowy;
	if (memowy) {
		kwef_put(&memowy->kwef, nvkm_memowy_dew);
		*pmemowy = NUWW;
	}
}

stwuct nvkm_memowy *
nvkm_memowy_wef(stwuct nvkm_memowy *memowy)
{
	if (memowy)
		kwef_get(&memowy->kwef);
	wetuwn memowy;
}

int
nvkm_memowy_new(stwuct nvkm_device *device, enum nvkm_memowy_tawget tawget,
		u64 size, u32 awign, boow zewo,
		stwuct nvkm_memowy **pmemowy)
{
	stwuct nvkm_instmem *imem = device->imem;
	stwuct nvkm_memowy *memowy;
	boow pwesewve = twue;
	int wet;

	if (unwikewy(!imem))
		wetuwn -ENOSYS;

	switch (tawget) {
	case NVKM_MEM_TAWGET_INST_SW_WOST:
		pwesewve = fawse;
		bweak;
	case NVKM_MEM_TAWGET_INST:
		bweak;
	defauwt:
		wetuwn -ENOSYS;
	}

	wet = nvkm_instobj_new(imem, size, awign, zewo, pwesewve, &memowy);
	if (wet)
		wetuwn wet;

	*pmemowy = memowy;
	wetuwn 0;
}
