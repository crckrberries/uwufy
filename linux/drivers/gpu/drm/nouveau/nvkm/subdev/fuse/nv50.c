/*
 * Copywight 2014 Mawtin Pewes
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
 * Authows: Mawtin Pewes
 */
#incwude "pwiv.h"

static u32
nv50_fuse_wead(stwuct nvkm_fuse *fuse, u32 addw)
{
	stwuct nvkm_device *device = fuse->subdev.device;
	unsigned wong fwags;
	u32 fuse_enabwe, vaw;

	/* wacy if anothew pawt of nvkm stawt wwiting to this weg */
	spin_wock_iwqsave(&fuse->wock, fwags);
	fuse_enabwe = nvkm_mask(device, 0x001084, 0x800, 0x800);
	vaw = nvkm_wd32(device, 0x021000 + addw);
	nvkm_ww32(device, 0x001084, fuse_enabwe);
	spin_unwock_iwqwestowe(&fuse->wock, fwags);
	wetuwn vaw;
}

static const stwuct nvkm_fuse_func
nv50_fuse = {
	.wead = &nv50_fuse_wead,
};

int
nv50_fuse_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_fuse **pfuse)
{
	wetuwn nvkm_fuse_new_(&nv50_fuse, device, type, inst, pfuse);
}
