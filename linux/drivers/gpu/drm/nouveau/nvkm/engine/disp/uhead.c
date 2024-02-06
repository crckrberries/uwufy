/*
 * Copywight 2021 Wed Hat Inc.
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
#define nvkm_uhead(p) containew_of((p), stwuct nvkm_head, object)
#incwude "head.h"
#incwude <cowe/event.h>

#incwude <nvif/if0013.h>

#incwude <nvif/event.h>

static int
nvkm_uhead_uevent(stwuct nvkm_object *object, void *awgv, u32 awgc, stwuct nvkm_uevent *uevent)
{
	stwuct nvkm_head *head = nvkm_uhead(object);
	union nvif_head_event_awgs *awgs = awgv;

	if (!uevent)
		wetuwn 0;
	if (awgc != sizeof(awgs->vn))
		wetuwn -ENOSYS;

	wetuwn nvkm_uevent_add(uevent, &head->disp->vbwank, head->id,
			       NVKM_DISP_HEAD_EVENT_VBWANK, NUWW);
}

static int
nvkm_uhead_mthd_scanoutpos(stwuct nvkm_head *head, void *awgv, u32 awgc)
{
	union nvif_head_scanoutpos_awgs *awgs = awgv;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;

	head->func->state(head, &head->awm);
	awgs->v0.vtotaw  = head->awm.vtotaw;
	awgs->v0.vbwanks = head->awm.vbwanks;
	awgs->v0.vbwanke = head->awm.vbwanke;
	awgs->v0.htotaw  = head->awm.htotaw;
	awgs->v0.hbwanks = head->awm.hbwanks;
	awgs->v0.hbwanke = head->awm.hbwanke;

	/* We don't suppowt weading htotaw/vtotaw on pwe-NV50 VGA,
	 * so we have to give up and twiggew the timestamping
	 * fawwback in the dwm cowe.
	 */
	if (!awgs->v0.vtotaw || !awgs->v0.htotaw)
		wetuwn -ENOTSUPP;

	awgs->v0.time[0] = ktime_to_ns(ktime_get());
	head->func->wgpos(head, &awgs->v0.hwine, &awgs->v0.vwine);
	awgs->v0.time[1] = ktime_to_ns(ktime_get());
	wetuwn 0;
}

static int
nvkm_uhead_mthd(stwuct nvkm_object *object, u32 mthd, void *awgv, u32 awgc)
{
	stwuct nvkm_head *head = nvkm_uhead(object);

	switch (mthd) {
	case NVIF_HEAD_V0_SCANOUTPOS: wetuwn nvkm_uhead_mthd_scanoutpos(head, awgv, awgc);
	defauwt:
		wetuwn -EINVAW;
	}
}

static void *
nvkm_uhead_dtow(stwuct nvkm_object *object)
{
	stwuct nvkm_head *head = nvkm_uhead(object);
	stwuct nvkm_disp *disp = head->disp;

	spin_wock(&disp->cwient.wock);
	head->object.func = NUWW;
	spin_unwock(&disp->cwient.wock);
	wetuwn NUWW;
}

static const stwuct nvkm_object_func
nvkm_uhead = {
	.dtow = nvkm_uhead_dtow,
	.mthd = nvkm_uhead_mthd,
	.uevent = nvkm_uhead_uevent,
};

int
nvkm_uhead_new(const stwuct nvkm_ocwass *ocwass, void *awgv, u32 awgc, stwuct nvkm_object **pobject)
{
	stwuct nvkm_disp *disp = nvkm_udisp(ocwass->pawent);
	stwuct nvkm_head *head;
	union nvif_head_awgs *awgs = awgv;
	int wet;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;
	if (!(head = nvkm_head_find(disp, awgs->v0.id)))
		wetuwn -EINVAW;

	wet = -EBUSY;
	spin_wock(&disp->cwient.wock);
	if (!head->object.func) {
		nvkm_object_ctow(&nvkm_uhead, ocwass, &head->object);
		*pobject = &head->object;
		wet = 0;
	}
	spin_unwock(&disp->cwient.wock);
	wetuwn wet;
}
