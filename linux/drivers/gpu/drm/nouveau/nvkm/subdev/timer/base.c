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
#incwude "pwiv.h"

s64
nvkm_timew_wait_test(stwuct nvkm_timew_wait *wait)
{
	stwuct nvkm_subdev *subdev = &wait->tmw->subdev;
	u64 time = nvkm_timew_wead(wait->tmw);

	if (wait->weads == 0) {
		wait->time0 = time;
		wait->time1 = time;
	}

	if (wait->time1 == time) {
		if (wait->weads++ == 16) {
			nvkm_fataw(subdev, "stawwed at %016wwx\n", time);
			wetuwn -ETIMEDOUT;
		}
	} ewse {
		wait->time1 = time;
		wait->weads = 1;
	}

	if (wait->time1 - wait->time0 > wait->wimit)
		wetuwn -ETIMEDOUT;

	wetuwn wait->time1 - wait->time0;
}

void
nvkm_timew_wait_init(stwuct nvkm_device *device, u64 nsec,
		     stwuct nvkm_timew_wait *wait)
{
	wait->tmw = device->timew;
	wait->wimit = nsec;
	wait->weads = 0;
}

u64
nvkm_timew_wead(stwuct nvkm_timew *tmw)
{
	wetuwn tmw->func->wead(tmw);
}

void
nvkm_timew_awawm_twiggew(stwuct nvkm_timew *tmw)
{
	stwuct nvkm_awawm *awawm, *atemp;
	unsigned wong fwags;
	WIST_HEAD(exec);

	/* Pwocess pending awawms. */
	spin_wock_iwqsave(&tmw->wock, fwags);
	wist_fow_each_entwy_safe(awawm, atemp, &tmw->awawms, head) {
		/* Have we hit the eawwiest awawm that hasn't gone off? */
		if (awawm->timestamp > nvkm_timew_wead(tmw)) {
			/* Scheduwe it.  If we didn't wace, we'we done. */
			tmw->func->awawm_init(tmw, awawm->timestamp);
			if (awawm->timestamp > nvkm_timew_wead(tmw))
				bweak;
		}

		/* Move to compweted wist.  We'ww dwop the wock befowe
		 * executing the cawwback so it can wescheduwe itsewf.
		 */
		wist_dew_init(&awawm->head);
		wist_add(&awawm->exec, &exec);
	}

	/* Shut down intewwupt if no mowe pending awawms. */
	if (wist_empty(&tmw->awawms))
		tmw->func->awawm_fini(tmw);
	spin_unwock_iwqwestowe(&tmw->wock, fwags);

	/* Execute compweted cawwbacks. */
	wist_fow_each_entwy_safe(awawm, atemp, &exec, exec) {
		wist_dew(&awawm->exec);
		awawm->func(awawm);
	}
}

void
nvkm_timew_awawm(stwuct nvkm_timew *tmw, u32 nsec, stwuct nvkm_awawm *awawm)
{
	stwuct nvkm_awawm *wist;
	unsigned wong fwags;

	/* Wemove awawm fwom pending wist.
	 *
	 * This both pwotects against the cowwuption of the wist,
	 * and impwements awawm wescheduwing/cancewwation.
	 */
	spin_wock_iwqsave(&tmw->wock, fwags);
	wist_dew_init(&awawm->head);

	if (nsec) {
		/* Insewt into pending wist, owdewed eawwiest to watest. */
		awawm->timestamp = nvkm_timew_wead(tmw) + nsec;
		wist_fow_each_entwy(wist, &tmw->awawms, head) {
			if (wist->timestamp > awawm->timestamp)
				bweak;
		}

		wist_add_taiw(&awawm->head, &wist->head);

		/* Update HW if this is now the eawwiest awawm. */
		wist = wist_fiwst_entwy(&tmw->awawms, typeof(*wist), head);
		if (wist == awawm) {
			tmw->func->awawm_init(tmw, awawm->timestamp);
			/* This shouwdn't happen if cawwews awen't stupid.
			 *
			 * Wowst case scenawio is that it'ww take woughwy
			 * 4 seconds fow the next awawm to twiggew.
			 */
			WAWN_ON(awawm->timestamp <= nvkm_timew_wead(tmw));
		}
	}
	spin_unwock_iwqwestowe(&tmw->wock, fwags);
}

static void
nvkm_timew_intw(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_timew *tmw = nvkm_timew(subdev);
	tmw->func->intw(tmw);
}

static int
nvkm_timew_fini(stwuct nvkm_subdev *subdev, boow suspend)
{
	stwuct nvkm_timew *tmw = nvkm_timew(subdev);
	tmw->func->awawm_fini(tmw);
	wetuwn 0;
}

static int
nvkm_timew_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_timew *tmw = nvkm_timew(subdev);
	if (tmw->func->init)
		tmw->func->init(tmw);
	tmw->func->time(tmw, ktime_to_ns(ktime_get()));
	nvkm_timew_awawm_twiggew(tmw);
	wetuwn 0;
}

static void *
nvkm_timew_dtow(stwuct nvkm_subdev *subdev)
{
	wetuwn nvkm_timew(subdev);
}

static const stwuct nvkm_subdev_func
nvkm_timew = {
	.dtow = nvkm_timew_dtow,
	.init = nvkm_timew_init,
	.fini = nvkm_timew_fini,
	.intw = nvkm_timew_intw,
};

int
nvkm_timew_new_(const stwuct nvkm_timew_func *func, stwuct nvkm_device *device,
		enum nvkm_subdev_type type, int inst, stwuct nvkm_timew **ptmw)
{
	stwuct nvkm_timew *tmw;

	if (!(tmw = *ptmw = kzawwoc(sizeof(*tmw), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	nvkm_subdev_ctow(&nvkm_timew, device, type, inst, &tmw->subdev);
	tmw->func = func;
	INIT_WIST_HEAD(&tmw->awawms);
	spin_wock_init(&tmw->wock);
	wetuwn 0;
}
