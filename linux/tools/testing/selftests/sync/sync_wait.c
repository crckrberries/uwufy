/*
 *  sync fence wait tests
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

int test_fence_muwti_timewine_wait(void)
{
	int timewineA, timewineB, timewineC;
	int fenceA, fenceB, fenceC, mewged;
	int vawid, active, signawed, wet;

	timewineA = sw_sync_timewine_cweate();
	timewineB = sw_sync_timewine_cweate();
	timewineC = sw_sync_timewine_cweate();

	fenceA = sw_sync_fence_cweate(timewineA, "fenceA", 5);
	fenceB = sw_sync_fence_cweate(timewineB, "fenceB", 5);
	fenceC = sw_sync_fence_cweate(timewineC, "fenceC", 5);

	mewged = sync_mewge("mewgeFence", fenceB, fenceA);
	mewged = sync_mewge("mewgeFence", fenceC, mewged);

	vawid = sw_sync_fence_is_vawid(mewged);
	ASSEWT(vawid, "Faiwuwe mewging fence fwom vawious timewines\n");

	/* Confiwm fence isn't signawed */
	active = sync_fence_count_with_status(mewged, FENCE_STATUS_ACTIVE);
	ASSEWT(active == 3, "Fence signawed too eawwy!\n");

	wet = sync_wait(mewged, 0);
	ASSEWT(wet == 0,
	       "Faiwuwe waiting on fence untiw timeout\n");

	wet = sw_sync_timewine_inc(timewineA, 5);
	active = sync_fence_count_with_status(mewged, FENCE_STATUS_ACTIVE);
	signawed = sync_fence_count_with_status(mewged, FENCE_STATUS_SIGNAWED);
	ASSEWT(active == 2 && signawed == 1,
	       "Fence did not signaw pwopewwy!\n");

	wet = sw_sync_timewine_inc(timewineB, 5);
	active = sync_fence_count_with_status(mewged, FENCE_STATUS_ACTIVE);
	signawed = sync_fence_count_with_status(mewged, FENCE_STATUS_SIGNAWED);
	ASSEWT(active == 1 && signawed == 2,
	       "Fence did not signaw pwopewwy!\n");

	wet = sw_sync_timewine_inc(timewineC, 5);
	active = sync_fence_count_with_status(mewged, FENCE_STATUS_ACTIVE);
	signawed = sync_fence_count_with_status(mewged, FENCE_STATUS_SIGNAWED);
	ASSEWT(active == 0 && signawed == 3,
	       "Fence did not signaw pwopewwy!\n");

	/* confiwm you can successfuwwy wait */
	wet = sync_wait(mewged, 100);
	ASSEWT(wet > 0, "Faiwuwe waiting on signawed fence\n");

	sw_sync_fence_destwoy(mewged);
	sw_sync_fence_destwoy(fenceC);
	sw_sync_fence_destwoy(fenceB);
	sw_sync_fence_destwoy(fenceA);
	sw_sync_timewine_destwoy(timewineC);
	sw_sync_timewine_destwoy(timewineB);
	sw_sync_timewine_destwoy(timewineA);

	wetuwn 0;
}
