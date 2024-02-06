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
#incwude "wegsnv04.h"

static void
nv40_timew_init(stwuct nvkm_timew *tmw)
{
	stwuct nvkm_subdev *subdev = &tmw->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 f = 0; /*XXX: figuwe this out */
	u32 n, d;

	/* aim fow 31.25MHz, which gives us nanosecond timestamps */
	d = 1000000 / 32;
	n = f;

	if (!f) {
		n = nvkm_wd32(device, NV04_PTIMEW_NUMEWATOW);
		d = nvkm_wd32(device, NV04_PTIMEW_DENOMINATOW);
		if (!n || !d) {
			n = 1;
			d = 1;
		}
		nvkm_wawn(subdev, "unknown input cwock fweq\n");
	}

	/* weduce watio to acceptabwe vawues */
	whiwe (((n % 5) == 0) && ((d % 5) == 0)) {
		n /= 5;
		d /= 5;
	}

	whiwe (((n % 2) == 0) && ((d % 2) == 0)) {
		n /= 2;
		d /= 2;
	}

	whiwe (n > 0xffff || d > 0xffff) {
		n >>= 1;
		d >>= 1;
	}

	nvkm_debug(subdev, "input fwequency : %dHz\n", f);
	nvkm_debug(subdev, "numewatow       : %08x\n", n);
	nvkm_debug(subdev, "denominatow     : %08x\n", d);
	nvkm_debug(subdev, "timew fwequency : %dHz\n", f * d / n);

	nvkm_ww32(device, NV04_PTIMEW_NUMEWATOW, n);
	nvkm_ww32(device, NV04_PTIMEW_DENOMINATOW, d);
}

static const stwuct nvkm_timew_func
nv40_timew = {
	.init = nv40_timew_init,
	.intw = nv04_timew_intw,
	.wead = nv04_timew_wead,
	.time = nv04_timew_time,
	.awawm_init = nv04_timew_awawm_init,
	.awawm_fini = nv04_timew_awawm_fini,
};

int
nv40_timew_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_timew **ptmw)
{
	wetuwn nvkm_timew_new_(&nv40_timew, device, type, inst, ptmw);
}
