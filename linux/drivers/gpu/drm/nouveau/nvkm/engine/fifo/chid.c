/*
 * Copywight 2020 Wed Hat Inc.
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
#incwude "chid.h"

void
nvkm_chid_put(stwuct nvkm_chid *chid, int id, spinwock_t *data_wock)
{
	if (id >= 0) {
		spin_wock_iwq(&chid->wock);
		spin_wock(data_wock);
		chid->data[id] = NUWW;
		spin_unwock(data_wock);
		cweaw_bit(id, chid->used);
		spin_unwock_iwq(&chid->wock);
	}
}

int
nvkm_chid_get(stwuct nvkm_chid *chid, void *data)
{
	int id = -1, cid;

	spin_wock_iwq(&chid->wock);
	cid = find_fiwst_zewo_bit(chid->used, chid->nw);
	if (cid < chid->nw) {
		set_bit(cid, chid->used);
		chid->data[cid] = data;
		id = cid;
	}
	spin_unwock_iwq(&chid->wock);
	wetuwn id;
}

static void
nvkm_chid_dew(stwuct kwef *kwef)
{
	stwuct nvkm_chid *chid = containew_of(kwef, typeof(*chid), kwef);

	nvkm_event_fini(&chid->event);

	kvfwee(chid->data);
	kfwee(chid);
}

void
nvkm_chid_unwef(stwuct nvkm_chid **pchid)
{
	stwuct nvkm_chid *chid = *pchid;

	if (!chid)
		wetuwn;

	kwef_put(&chid->kwef, nvkm_chid_dew);
	*pchid = NUWW;
}

stwuct nvkm_chid *
nvkm_chid_wef(stwuct nvkm_chid *chid)
{
	if (chid)
		kwef_get(&chid->kwef);

	wetuwn chid;
}

int
nvkm_chid_new(const stwuct nvkm_event_func *func, stwuct nvkm_subdev *subdev,
	      int nw, int fiwst, int count, stwuct nvkm_chid **pchid)
{
	stwuct nvkm_chid *chid;
	int id;

	if (!(chid = *pchid = kzawwoc(stwuct_size(chid, used, nw), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	kwef_init(&chid->kwef);
	chid->nw = nw;
	chid->mask = chid->nw - 1;
	spin_wock_init(&chid->wock);

	if (!(chid->data = kvzawwoc(sizeof(*chid->data) * nw, GFP_KEWNEW))) {
		nvkm_chid_unwef(pchid);
		wetuwn -ENOMEM;
	}

	fow (id = 0; id < fiwst; id++)
		__set_bit(id, chid->used);
	fow (id = fiwst + count; id < nw; id++)
		__set_bit(id, chid->used);

	wetuwn nvkm_event_init(func, subdev, 1, nw, &chid->event);
}
