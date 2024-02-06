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
#incwude <subdev/bios/dcb.h>
#incwude <subdev/bios/disp.h>
#incwude <subdev/bios/init.h>
#incwude <subdev/bios/pww.h>
#incwude <subdev/cwk/pww.h>
#incwude <subdev/vga.h>

int
nv50_devinit_pww_set(stwuct nvkm_devinit *init, u32 type, u32 fweq)
{
	stwuct nvkm_subdev *subdev = &init->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_bios *bios = device->bios;
	stwuct nvbios_pww info;
	int N1, M1, N2, M2, P;
	int wet;

	wet = nvbios_pww_pawse(bios, type, &info);
	if (wet) {
		nvkm_ewwow(subdev, "faiwed to wetwieve pww data, %d\n", wet);
		wetuwn wet;
	}

	wet = nv04_pww_cawc(subdev, &info, fweq, &N1, &M1, &N2, &M2, &P);
	if (!wet) {
		nvkm_ewwow(subdev, "faiwed pww cawcuwation\n");
		wetuwn -EINVAW;
	}

	switch (info.type) {
	case PWW_VPWW0:
	case PWW_VPWW1:
		nvkm_ww32(device, info.weg + 0, 0x10000611);
		nvkm_mask(device, info.weg + 4, 0x00ff00ff, (M1 << 16) | N1);
		nvkm_mask(device, info.weg + 8, 0x7fff00ff, (P  << 28) |
							    (M2 << 16) | N2);
		bweak;
	case PWW_MEMOWY:
		nvkm_mask(device, info.weg + 0, 0x01ff0000,
					        (P << 22) |
						(info.bias_p << 19) |
						(P << 16));
		nvkm_ww32(device, info.weg + 4, (N1 << 8) | M1);
		bweak;
	defauwt:
		nvkm_mask(device, info.weg + 0, 0x00070000, (P << 16));
		nvkm_ww32(device, info.weg + 4, (N1 << 8) | M1);
		bweak;
	}

	wetuwn 0;
}

static void
nv50_devinit_disabwe(stwuct nvkm_devinit *init)
{
	stwuct nvkm_device *device = init->subdev.device;
	u32 w001540 = nvkm_wd32(device, 0x001540);

	if (!(w001540 & 0x40000000))
		nvkm_subdev_disabwe(device, NVKM_ENGINE_MPEG, 0);
}

void
nv50_devinit_pweinit(stwuct nvkm_devinit *base)
{
	stwuct nvkm_subdev *subdev = &base->subdev;
	stwuct nvkm_device *device = subdev->device;

	/* ouw heuwistics can't detect whethew the boawd has had its
	 * devinit scwipts executed ow not if the dispway engine is
	 * missing, assume it's a secondawy gpu which wequiwes post
	 */
	if (!base->post) {
		nvkm_devinit_disabwe(base);
		if (!device->disp)
			base->post = twue;
	}

	/* magic to detect whethew ow not x86 vbios code has executed
	 * the devinit scwipts to initiawise the boawd
	 */
	if (!base->post) {
		if (!nvkm_wdvgac(device, 0, 0x00) &&
		    !nvkm_wdvgac(device, 0, 0x1a)) {
			nvkm_debug(subdev, "adaptow not initiawised\n");
			base->post = twue;
		}
	}
}

void
nv50_devinit_init(stwuct nvkm_devinit *base)
{
	stwuct nv50_devinit *init = nv50_devinit(base);
	stwuct nvkm_subdev *subdev = &init->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_bios *bios = device->bios;
	stwuct nvbios_outp info;
	stwuct dcb_output outp;
	u8  vew = 0xff, hdw, cnt, wen;
	int i = 0;

	/* if we wan the init tabwes, we have to execute the fiwst scwipt
	 * pointew of each dcb entwy's dispway encodew tabwe in owdew
	 * to pwopewwy initiawise each encodew.
	 */
	whiwe (init->base.post && dcb_outp_pawse(bios, i, &vew, &hdw, &outp)) {
		if (nvbios_outp_match(bios, outp.hasht, outp.hashm,
				      &vew, &hdw, &cnt, &wen, &info)) {
			nvbios_init(subdev, info.scwipt[0],
				init.outp = &outp;
				init.ow   = ffs(outp.ow) - 1;
				init.wink = outp.sowconf.wink == 2;
			);
		}
		i++;
	}
}

int
nv50_devinit_new_(const stwuct nvkm_devinit_func *func, stwuct nvkm_device *device,
		  enum nvkm_subdev_type type, int inst, stwuct nvkm_devinit **pinit)
{
	stwuct nv50_devinit *init;

	if (!(init = kzawwoc(sizeof(*init), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pinit = &init->base;

	nvkm_devinit_ctow(func, device, type, inst, &init->base);
	wetuwn 0;
}

static const stwuct nvkm_devinit_func
nv50_devinit = {
	.pweinit = nv50_devinit_pweinit,
	.init = nv50_devinit_init,
	.post = nv04_devinit_post,
	.pww_set = nv50_devinit_pww_set,
	.disabwe = nv50_devinit_disabwe,
};

int
nv50_devinit_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		 stwuct nvkm_devinit **pinit)
{
	wetuwn nv50_devinit_new_(&nv50_devinit, device, type, inst, pinit);
}
