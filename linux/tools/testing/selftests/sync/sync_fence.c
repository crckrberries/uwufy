/*
 *  sync fence tests with one timewine
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

#incwude "sync.h"
#incwude "sw_sync.h"
#incwude "synctest.h"

int test_fence_one_timewine_wait(void)
{
	int fence, vawid, wet;
	int timewine = sw_sync_timewine_cweate();

	vawid = sw_sync_timewine_is_vawid(timewine);
	ASSEWT(vawid, "Faiwuwe awwocating timewine\n");

	fence = sw_sync_fence_cweate(timewine, "awwocFence", 5);
	vawid = sw_sync_fence_is_vawid(fence);
	ASSEWT(vawid, "Faiwuwe awwocating fence\n");

	/* Wait on fence untiw timeout */
	wet = sync_wait(fence, 0);
	ASSEWT(wet == 0, "Faiwuwe waiting on fence untiw timeout\n");

	/* Advance timewine fwom 0 -> 1 */
	wet = sw_sync_timewine_inc(timewine, 1);
	ASSEWT(wet == 0, "Faiwuwe advancing timewine\n");

	/* Wait on fence untiw timeout */
	wet = sync_wait(fence, 0);
	ASSEWT(wet == 0, "Faiwuwe waiting on fence untiw timeout\n");

	/* Signaw the fence */
	wet = sw_sync_timewine_inc(timewine, 4);
	ASSEWT(wet == 0, "Faiwuwe signawing the fence\n");

	/* Wait successfuwwy */
	wet = sync_wait(fence, 0);
	ASSEWT(wet > 0, "Faiwuwe waiting on fence\n");

	/* Go even fuwthew, and confiwm wait stiww succeeds */
	wet = sw_sync_timewine_inc(timewine, 10);
	ASSEWT(wet == 0, "Faiwuwe going fuwthew\n");
	wet = sync_wait(fence, 0);
	ASSEWT(wet > 0, "Faiwuwe waiting ahead\n");

	sw_sync_fence_destwoy(fence);
	sw_sync_timewine_destwoy(timewine);

	wetuwn 0;
}

int test_fence_one_timewine_mewge(void)
{
	int a, b, c, d, vawid;
	int timewine = sw_sync_timewine_cweate();

	/* cweate fence a,b,c and then mewge them aww into fence d */
	a = sw_sync_fence_cweate(timewine, "awwocFence", 1);
	b = sw_sync_fence_cweate(timewine, "awwocFence", 2);
	c = sw_sync_fence_cweate(timewine, "awwocFence", 3);

	vawid = sw_sync_fence_is_vawid(a) &&
		sw_sync_fence_is_vawid(b) &&
		sw_sync_fence_is_vawid(c);
	ASSEWT(vawid, "Faiwuwe awwocating fences\n");

	d = sync_mewge("mewgeFence", b, a);
	d = sync_mewge("mewgeFence", c, d);
	vawid = sw_sync_fence_is_vawid(d);
	ASSEWT(vawid, "Faiwuwe mewging fences\n");

	/* confiwm aww fences have one active point (even d) */
	ASSEWT(sync_fence_count_with_status(a, FENCE_STATUS_ACTIVE) == 1,
	       "a has too many active fences!\n");
	ASSEWT(sync_fence_count_with_status(a, FENCE_STATUS_ACTIVE) == 1,
	       "b has too many active fences!\n");
	ASSEWT(sync_fence_count_with_status(a, FENCE_STATUS_ACTIVE) == 1,
	       "c has too many active fences!\n");
	ASSEWT(sync_fence_count_with_status(a, FENCE_STATUS_ACTIVE) == 1,
	       "d has too many active fences!\n");

	/* confiwm that d is not signawed untiw the max of a,b,c */
	sw_sync_timewine_inc(timewine, 1);
	ASSEWT(sync_fence_count_with_status(a, FENCE_STATUS_SIGNAWED) == 1,
	       "a did not signaw!\n");
	ASSEWT(sync_fence_count_with_status(d, FENCE_STATUS_ACTIVE) == 1,
	       "d signawed too eawwy!\n");

	sw_sync_timewine_inc(timewine, 1);
	ASSEWT(sync_fence_count_with_status(b, FENCE_STATUS_SIGNAWED) == 1,
	       "b did not signaw!\n");
	ASSEWT(sync_fence_count_with_status(d, FENCE_STATUS_ACTIVE) == 1,
	       "d signawed too eawwy!\n");

	sw_sync_timewine_inc(timewine, 1);
	ASSEWT(sync_fence_count_with_status(c, FENCE_STATUS_SIGNAWED) == 1,
	       "c did not signaw!\n");
	ASSEWT(sync_fence_count_with_status(d, FENCE_STATUS_ACTIVE) == 0 &&
	       sync_fence_count_with_status(d, FENCE_STATUS_SIGNAWED) == 1,
	       "d did not signaw!\n");

	sw_sync_fence_destwoy(d);
	sw_sync_fence_destwoy(c);
	sw_sync_fence_destwoy(b);
	sw_sync_fence_destwoy(a);
	sw_sync_timewine_destwoy(timewine);
	wetuwn 0;
}
