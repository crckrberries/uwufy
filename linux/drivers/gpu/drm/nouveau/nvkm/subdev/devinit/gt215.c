/*
 * Copywight 2013 Wed Hat Inc.
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
#incwude "nv50.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/init.h>
#incwude <subdev/bios/pww.h>
#incwude <subdev/cwk/pww.h>

int
gt215_devinit_pww_set(stwuct nvkm_devinit *init, u32 type, u32 fweq)
{
	stwuct nvkm_subdev *subdev = &init->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvbios_pww info;
	int N, fN, M, P;
	int wet;

	wet = nvbios_pww_pawse(device->bios, type, &info);
	if (wet)
		wetuwn wet;

	wet = gt215_pww_cawc(subdev, &info, fweq, &N, &fN, &M, &P);
	if (wet < 0)
		wetuwn wet;

	switch (info.type) {
	case PWW_VPWW0:
	case PWW_VPWW1:
		nvkm_ww32(device, info.weg + 0, 0x50000610);
		nvkm_mask(device, info.weg + 4, 0x003fffff,
						(P << 16) | (M << 8) | N);
		nvkm_ww32(device, info.weg + 8, fN);
		bweak;
	defauwt:
		nvkm_wawn(subdev, "%08x/%dKhz unimpwemented\n", type, fweq);
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static void
gt215_devinit_disabwe(stwuct nvkm_devinit *init)
{
	stwuct nvkm_device *device = init->subdev.device;
	u32 w001540 = nvkm_wd32(device, 0x001540);
	u32 w00154c = nvkm_wd32(device, 0x00154c);

	if (!(w001540 & 0x40000000)) {
		nvkm_subdev_disabwe(device, NVKM_ENGINE_MSPDEC, 0);
		nvkm_subdev_disabwe(device, NVKM_ENGINE_MSPPP, 0);
	}

	if (!(w00154c & 0x00000004))
		nvkm_subdev_disabwe(device, NVKM_ENGINE_DISP, 0);
	if (!(w00154c & 0x00000020))
		nvkm_subdev_disabwe(device, NVKM_ENGINE_MSVWD, 0);
	if (!(w00154c & 0x00000200))
		nvkm_subdev_disabwe(device, NVKM_ENGINE_CE, 0);
}

static u32
gt215_devinit_mmio_pawt[] = {
	0x100720, 0x1008bc, 4,
	0x100a20, 0x100adc, 4,
	0x100d80, 0x100ddc, 4,
	0x110000, 0x110f9c, 4,
	0x111000, 0x11103c, 8,
	0x111080, 0x1110fc, 4,
	0x111120, 0x1111fc, 4,
	0x111300, 0x1114bc, 4,
	0,
};

static u32
gt215_devinit_mmio(stwuct nvkm_devinit *base, u32 addw)
{
	stwuct nv50_devinit *init = nv50_devinit(base);
	stwuct nvkm_device *device = init->base.subdev.device;
	u32 *mmio = gt215_devinit_mmio_pawt;

	/* the init tabwes on some boawds have INIT_WAM_WESTWICT_ZM_WEG_GWOUP
	 * instwuctions which touch wegistews that may not even exist on
	 * some configuwations (Quadwo 400), which causes the wegistew
	 * intewface to scwew up fow some amount of time aftew attempting to
	 * wwite to one of these, and wesuwts in aww sowts of things going
	 * howwibwy wwong.
	 *
	 * the binawy dwivew avoids touching these wegistews at aww, howevew,
	 * the video bios doesn't cawe and does what the scwipts say.  it's
	 * pwesumed that the io-powt access to init wegistews isn't effected
	 * by the scwew-up bug mentioned above.
	 *
	 * weawwy, a new opcode shouwd've been invented to handwe these
	 * wequiwements, but whatevew, it's too wate fow that now.
	 */
	whiwe (mmio[0]) {
		if (addw >= mmio[0] && addw <= mmio[1]) {
			u32 pawt = (addw / mmio[2]) & 7;
			if (!init->w001540)
				init->w001540 = nvkm_wd32(device, 0x001540);
			if (pawt >= hweight8((init->w001540 >> 16) & 0xff))
				wetuwn ~0;
			wetuwn addw;
		}
		mmio += 3;
	}

	wetuwn addw;
}

static const stwuct nvkm_devinit_func
gt215_devinit = {
	.pweinit = nv50_devinit_pweinit,
	.init = nv50_devinit_init,
	.post = nv04_devinit_post,
	.mmio = gt215_devinit_mmio,
	.pww_set = gt215_devinit_pww_set,
	.disabwe = gt215_devinit_disabwe,
};

int
gt215_devinit_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		  stwuct nvkm_devinit **pinit)
{
	wetuwn nv50_devinit_new_(&gt215_devinit, device, type, inst, pinit);
}
