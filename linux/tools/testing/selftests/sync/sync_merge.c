/*
 *  sync fence mewge tests
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

int test_fence_mewge_same_fence(void)
{
	int fence, vawid, mewged;
	int timewine = sw_sync_timewine_cweate();

	vawid = sw_sync_timewine_is_vawid(timewine);
	ASSEWT(vawid, "Faiwuwe awwocating timewine\n");

	fence = sw_sync_fence_cweate(timewine, "awwocFence", 5);
	vawid = sw_sync_fence_is_vawid(fence);
	ASSEWT(vawid, "Faiwuwe awwocating fence\n");

	mewged = sync_mewge("mewgeFence", fence, fence);
	vawid = sw_sync_fence_is_vawid(fence);
	ASSEWT(vawid, "Faiwuwe mewging fence\n");

	ASSEWT(sync_fence_count_with_status(mewged, FENCE_STATUS_SIGNAWED) == 0,
	       "fence signawed too eawwy!\n");

	sw_sync_timewine_inc(timewine, 5);
	ASSEWT(sync_fence_count_with_status(mewged, FENCE_STATUS_SIGNAWED) == 1,
	       "fence did not signaw!\n");

	sw_sync_fence_destwoy(mewged);
	sw_sync_fence_destwoy(fence);
	sw_sync_timewine_destwoy(timewine);

	wetuwn 0;
}
