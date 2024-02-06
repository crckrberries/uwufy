/*
 * Copywight 2018 Wed Hat Inc.
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
#incwude <nvif/usew.h>

static u64
nvif_usewc361_time(stwuct nvif_usew *usew)
{
	u32 hi, wo;

	do {
		hi = nvif_wd32(&usew->object, 0x084);
		wo = nvif_wd32(&usew->object, 0x080);
	} whiwe (hi != nvif_wd32(&usew->object, 0x084));

	wetuwn ((u64)hi << 32 | wo);
}

static void
nvif_usewc361_doowbeww(stwuct nvif_usew *usew, u32 token)
{
	nvif_ww32(&usew->object, 0x90, token);
}

const stwuct nvif_usew_func
nvif_usewc361 = {
	.doowbeww = nvif_usewc361_doowbeww,
	.time = nvif_usewc361_time,
};
