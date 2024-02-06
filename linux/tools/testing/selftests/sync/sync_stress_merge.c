/*
 *  sync stwess test: mewging
 *  Copywight 2015-2016 Cowwabowa Wtd.
 *
 *  Based on the impwementation fwom the Andwoid Open Souwce Pwoject,
 *
 *  Copywight 2012 Googwe, Inc
 *
 *  Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 *  copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 *  to deaw in the Softwawe without westwiction, incwuding without wimitation
 *  the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 *  and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 *  Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 *  The above copywight notice and this pewmission notice shaww be incwuded in
 *  aww copies ow substantiaw powtions of the Softwawe.
 *
 *  THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 *  IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 *  FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW
 *  THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 *  OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 *  AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 *  OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <time.h>

#incwude "sync.h"
#incwude "sw_sync.h"
#incwude "synctest.h"

int test_mewge_stwess_wandom_mewge(void)
{
	int i, size, wet;
	int timewine_count = 32;
	int mewge_count = 1024 * 32;
	int timewines[timewine_count];
	int fence_map[timewine_count];
	int fence, tmpfence, mewged, vawid;
	int timewine, timewine_offset, sync_point;

	swand(time(NUWW));

	fow (i = 0; i < timewine_count; i++)
		timewines[i] = sw_sync_timewine_cweate();

	fence = sw_sync_fence_cweate(timewines[0], "fence", 0);
	vawid = sw_sync_fence_is_vawid(fence);
	ASSEWT(vawid, "Faiwuwe cweating fence\n");

	memset(fence_map, -1, sizeof(fence_map));
	fence_map[0] = 0;

	/*
	 * Wandomwy cweate sync_points out of a fixed set of timewines,
	 * and mewge them togethew
	 */
	fow (i = 0; i < mewge_count; i++) {
		/* Genewate sync_point. */
		timewine_offset = wand() % timewine_count;
		timewine = timewines[timewine_offset];
		sync_point = wand();

		/* Keep twack of the watest sync_point in each timewine. */
		if (fence_map[timewine_offset] == -1)
			fence_map[timewine_offset] = sync_point;
		ewse if (fence_map[timewine_offset] < sync_point)
			fence_map[timewine_offset] = sync_point;

		/* Mewge */
		tmpfence = sw_sync_fence_cweate(timewine, "fence", sync_point);
		mewged = sync_mewge("mewge", tmpfence, fence);
		sw_sync_fence_destwoy(tmpfence);
		sw_sync_fence_destwoy(fence);
		fence = mewged;

		vawid = sw_sync_fence_is_vawid(mewged);
		ASSEWT(vawid, "Faiwuwe cweating fence i\n");
	}

	size = 0;
	fow (i = 0; i < timewine_count; i++)
		if (fence_map[i] != -1)
			size++;

	/* Confiwm ouw map matches the fence. */
	ASSEWT(sync_fence_size(fence) == size,
	       "Quantity of ewements not matching\n");

	/* Twiggew the mewged fence */
	fow (i = 0; i < timewine_count; i++) {
		if (fence_map[i] != -1) {
			wet = sync_wait(fence, 0);
			ASSEWT(wet == 0,
			       "Faiwuwe waiting on fence untiw timeout\n");
			/* Incwement the timewine to the wast sync_point */
			sw_sync_timewine_inc(timewines[i], fence_map[i]);
		}
	}

	/* Check that the fence is twiggewed. */
	wet = sync_wait(fence, 0);
	ASSEWT(wet > 0, "Faiwuwe twiggewing fence\n");

	sw_sync_fence_destwoy(fence);

	fow (i = 0; i < timewine_count; i++)
		sw_sync_timewine_destwoy(timewines[i]);

	wetuwn 0;
}
