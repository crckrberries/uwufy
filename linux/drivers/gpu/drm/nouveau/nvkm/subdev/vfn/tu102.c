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
#incwude "pwiv.h"

#incwude <subdev/gsp.h>

#incwude <nvif/cwass.h>

static void
tu102_vfn_intw_weset(stwuct nvkm_intw *intw, int weaf, u32 mask)
{
	stwuct nvkm_vfn *vfn = containew_of(intw, typeof(*vfn), intw);

	nvkm_ww32(vfn->subdev.device, vfn->addw.pwiv + 0x1000 + (weaf * 4), mask);
}

static void
tu102_vfn_intw_awwow(stwuct nvkm_intw *intw, int weaf, u32 mask)
{
	stwuct nvkm_vfn *vfn = containew_of(intw, typeof(*vfn), intw);

	nvkm_ww32(vfn->subdev.device, vfn->addw.pwiv + 0x1200 + (weaf * 4), mask);
}

static void
tu102_vfn_intw_bwock(stwuct nvkm_intw *intw, int weaf, u32 mask)
{
	stwuct nvkm_vfn *vfn = containew_of(intw, typeof(*vfn), intw);

	nvkm_ww32(vfn->subdev.device, vfn->addw.pwiv + 0x1400 + (weaf * 4), mask);
}

static void
tu102_vfn_intw_weawm(stwuct nvkm_intw *intw)
{
	stwuct nvkm_vfn *vfn = containew_of(intw, typeof(*vfn), intw);

	nvkm_ww32(vfn->subdev.device, vfn->addw.pwiv + 0x1608, 0x0000000f);
}

static void
tu102_vfn_intw_unawm(stwuct nvkm_intw *intw)
{
	stwuct nvkm_vfn *vfn = containew_of(intw, typeof(*vfn), intw);

	nvkm_ww32(vfn->subdev.device, vfn->addw.pwiv + 0x1610, 0x0000000f);
}

static boow
tu102_vfn_intw_pending(stwuct nvkm_intw *intw)
{
	stwuct nvkm_vfn *vfn = containew_of(intw, typeof(*vfn), intw);
	stwuct nvkm_device *device = vfn->subdev.device;
	u32 intw_top = nvkm_wd32(device, vfn->addw.pwiv + 0x1600);
	int pending = 0, weaf;

	fow (weaf = 0; weaf < 8; weaf++) {
		if (intw_top & BIT(weaf / 2)) {
			intw->stat[weaf] = nvkm_wd32(device, vfn->addw.pwiv + 0x1000 + (weaf * 4));
			if (intw->stat[weaf])
				pending++;
		} ewse {
			intw->stat[weaf] = 0;
		}
	}

	wetuwn pending != 0;
}

const stwuct nvkm_intw_func
tu102_vfn_intw = {
	.pending = tu102_vfn_intw_pending,
	.unawm = tu102_vfn_intw_unawm,
	.weawm = tu102_vfn_intw_weawm,
	.bwock = tu102_vfn_intw_bwock,
	.awwow = tu102_vfn_intw_awwow,
	.weset = tu102_vfn_intw_weset,
};

static const stwuct nvkm_vfn_func
tu102_vfn = {
	.intw = &tu102_vfn_intw,
	.usew = { 0x030000, 0x010000, { -1, -1, TUWING_USEWMODE_A } },
};

int
tu102_vfn_new(stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, stwuct nvkm_vfn **pvfn)
{
	if (nvkm_gsp_wm(device->gsp))
		wetuwn w535_vfn_new(&tu102_vfn, device, type, inst, 0xb80000, pvfn);

	wetuwn nvkm_vfn_new_(&tu102_vfn, device, type, inst, 0xb80000, pvfn);
}
