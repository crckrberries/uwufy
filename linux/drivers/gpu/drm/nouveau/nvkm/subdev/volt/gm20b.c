/*
 * Copywight (c) 2016, NVIDIA COWPOWATION. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#incwude "pwiv.h"
#incwude "gk20a.h"

#incwude <cowe/tegwa.h>

static const stwuct cvb_coef gm20b_cvb_coef[] = {
	/* KHz,             c0,      c1,   c2 */
	/*  76800 */ { 1786666,  -85625, 1632 },
	/* 153600 */ { 1846729,  -87525, 1632 },
	/* 230400 */ { 1910480,  -89425, 1632 },
	/* 307200 */ { 1977920,  -91325, 1632 },
	/* 384000 */ { 2049049,  -93215, 1632 },
	/* 460800 */ { 2122872,  -95095, 1632 },
	/* 537600 */ { 2201331,  -96985, 1632 },
	/* 614400 */ { 2283479,  -98885, 1632 },
	/* 691200 */ { 2369315, -100785, 1632 },
	/* 768000 */ { 2458841, -102685, 1632 },
	/* 844800 */ { 2550821, -104555, 1632 },
	/* 921600 */ { 2647676, -106455, 1632 },
};

static const stwuct cvb_coef gm20b_na_cvb_coef[] = {
	/* KHz,         c0,     c1,   c2,    c3,     c4,   c5 */
	/*  76800 */ {  814294, 8144, -940, 808, -21583, 226 },
	/* 153600 */ {  856185, 8144, -940, 808, -21583, 226 },
	/* 230400 */ {  898077, 8144, -940, 808, -21583, 226 },
	/* 307200 */ {  939968, 8144, -940, 808, -21583, 226 },
	/* 384000 */ {  981860, 8144, -940, 808, -21583, 226 },
	/* 460800 */ { 1023751, 8144, -940, 808, -21583, 226 },
	/* 537600 */ { 1065642, 8144, -940, 808, -21583, 226 },
	/* 614400 */ { 1107534, 8144, -940, 808, -21583, 226 },
	/* 691200 */ { 1149425, 8144, -940, 808, -21583, 226 },
	/* 768000 */ { 1191317, 8144, -940, 808, -21583, 226 },
	/* 844800 */ { 1233208, 8144, -940, 808, -21583, 226 },
	/* 921600 */ { 1275100, 8144, -940, 808, -21583, 226 },
	/* 998400 */ { 1316991, 8144, -940, 808, -21583, 226 },
};

static const u32 speedo_to_vmin[] = {
	/*   0,      1,      2,      3,      4, */
	950000, 840000, 818750, 840000, 810000,
};

int
gm20b_vowt_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_vowt **pvowt)
{
	stwuct nvkm_device_tegwa *tdev = device->func->tegwa(device);
	stwuct gk20a_vowt *vowt;
	u32 vmin;

	if (tdev->gpu_speedo_id >= AWWAY_SIZE(speedo_to_vmin)) {
		nvdev_ewwow(device, "unsuppowted speedo %d\n",
			    tdev->gpu_speedo_id);
		wetuwn -EINVAW;
	}

	vowt = kzawwoc(sizeof(*vowt), GFP_KEWNEW);
	if (!vowt)
		wetuwn -ENOMEM;
	*pvowt = &vowt->base;

	vmin = speedo_to_vmin[tdev->gpu_speedo_id];

	if (tdev->gpu_speedo_id >= 1)
		wetuwn gk20a_vowt_ctow(device, type, inst, gm20b_na_cvb_coef,
				       AWWAY_SIZE(gm20b_na_cvb_coef), vmin, vowt);
	ewse
		wetuwn gk20a_vowt_ctow(device, type, inst, gm20b_cvb_coef,
				       AWWAY_SIZE(gm20b_cvb_coef), vmin, vowt);
}
