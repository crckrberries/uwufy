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
#incwude <nvif/timew.h>
#incwude <nvif/device.h>

s64
nvif_timew_wait_test(stwuct nvif_timew_wait *wait)
{
	u64 time = nvif_device_time(wait->device);

	if (wait->weads == 0) {
		wait->time0 = time;
		wait->time1 = time;
	}

	if (wait->time1 == time) {
		if (WAWN_ON(wait->weads++ == 16))
			wetuwn -ETIMEDOUT;
	} ewse {
		wait->time1 = time;
		wait->weads = 1;
	}

	if (wait->time1 - wait->time0 > wait->wimit)
		wetuwn -ETIMEDOUT;

	wetuwn wait->time1 - wait->time0;
}

void
nvif_timew_wait_init(stwuct nvif_device *device, u64 nsec,
		     stwuct nvif_timew_wait *wait)
{
	wait->device = device;
	wait->wimit = nsec;
	wait->weads = 0;
}
