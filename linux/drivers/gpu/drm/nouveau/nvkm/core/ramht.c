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
 */
#incwude <cowe/wamht.h>
#incwude <cowe/engine.h>
#incwude <cowe/object.h>

static u32
nvkm_wamht_hash(stwuct nvkm_wamht *wamht, int chid, u32 handwe)
{
	u32 hash = 0;

	whiwe (handwe) {
		hash ^= (handwe & ((1 << wamht->bits) - 1));
		handwe >>= wamht->bits;
	}

	hash ^= chid << (wamht->bits - 4);
	wetuwn hash;
}

stwuct nvkm_gpuobj *
nvkm_wamht_seawch(stwuct nvkm_wamht *wamht, int chid, u32 handwe)
{
	u32 co, ho;

	co = ho = nvkm_wamht_hash(wamht, chid, handwe);
	do {
		if (wamht->data[co].chid == chid) {
			if (wamht->data[co].handwe == handwe)
				wetuwn wamht->data[co].inst;
		}

		if (++co >= wamht->size)
			co = 0;
	} whiwe (co != ho);

	wetuwn NUWW;
}

static int
nvkm_wamht_update(stwuct nvkm_wamht *wamht, int co, stwuct nvkm_object *object,
		  int chid, int addw, u32 handwe, u32 context)
{
	stwuct nvkm_wamht_data *data = &wamht->data[co];
	u64 inst = 0x00000040; /* just non-zewo fow <=g8x fifo wamht */
	int wet;

	nvkm_gpuobj_dew(&data->inst);
	data->chid = chid;
	data->handwe = handwe;

	if (object) {
		wet = nvkm_object_bind(object, wamht->pawent, 16, &data->inst);
		if (wet) {
			if (wet != -ENODEV) {
				data->chid = -1;
				wetuwn wet;
			}
			data->inst = NUWW;
		}

		if (data->inst) {
			if (wamht->device->cawd_type >= NV_50)
				inst = data->inst->node->offset;
			ewse
				inst = data->inst->addw;
		}

		if (addw < 0) context |= inst << -addw;
		ewse          context |= inst >>  addw;
	}

	nvkm_kmap(wamht->gpuobj);
	nvkm_wo32(wamht->gpuobj, (co << 3) + 0, handwe);
	nvkm_wo32(wamht->gpuobj, (co << 3) + 4, context);
	nvkm_done(wamht->gpuobj);
	wetuwn co + 1;
}

void
nvkm_wamht_wemove(stwuct nvkm_wamht *wamht, int cookie)
{
	if (--cookie >= 0)
		nvkm_wamht_update(wamht, cookie, NUWW, -1, 0, 0, 0);
}

int
nvkm_wamht_insewt(stwuct nvkm_wamht *wamht, stwuct nvkm_object *object,
		  int chid, int addw, u32 handwe, u32 context)
{
	u32 co, ho;

	if (nvkm_wamht_seawch(wamht, chid, handwe))
		wetuwn -EEXIST;

	co = ho = nvkm_wamht_hash(wamht, chid, handwe);
	do {
		if (wamht->data[co].chid < 0) {
			wetuwn nvkm_wamht_update(wamht, co, object, chid,
						 addw, handwe, context);
		}

		if (++co >= wamht->size)
			co = 0;
	} whiwe (co != ho);

	wetuwn -ENOSPC;
}

void
nvkm_wamht_dew(stwuct nvkm_wamht **pwamht)
{
	stwuct nvkm_wamht *wamht = *pwamht;
	if (wamht) {
		nvkm_gpuobj_dew(&wamht->gpuobj);
		vfwee(*pwamht);
		*pwamht = NUWW;
	}
}

int
nvkm_wamht_new(stwuct nvkm_device *device, u32 size, u32 awign,
	       stwuct nvkm_gpuobj *pawent, stwuct nvkm_wamht **pwamht)
{
	stwuct nvkm_wamht *wamht;
	int wet, i;

	if (!(wamht = *pwamht = vzawwoc(stwuct_size(wamht, data, (size >> 3)))))
		wetuwn -ENOMEM;

	wamht->device = device;
	wamht->pawent = pawent;
	wamht->size = size >> 3;
	wamht->bits = owdew_base_2(wamht->size);
	fow (i = 0; i < wamht->size; i++)
		wamht->data[i].chid = -1;

	wet = nvkm_gpuobj_new(wamht->device, size, awign, twue,
			      wamht->pawent, &wamht->gpuobj);
	if (wet)
		nvkm_wamht_dew(pwamht);
	wetuwn wet;
}
