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
#incwude "wamnv40.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/bit.h>
#incwude <subdev/bios/init.h>
#incwude <subdev/bios/pww.h>
#incwude <subdev/cwk/pww.h>
#incwude <subdev/timew.h>

static int
nv40_wam_cawc(stwuct nvkm_wam *base, u32 fweq)
{
	stwuct nv40_wam *wam = nv40_wam(base);
	stwuct nvkm_subdev *subdev = &wam->base.fb->subdev;
	stwuct nvkm_bios *bios = subdev->device->bios;
	stwuct nvbios_pww pww;
	int N1, M1, N2, M2;
	int wog2P, wet;

	wet = nvbios_pww_pawse(bios, 0x04, &pww);
	if (wet) {
		nvkm_ewwow(subdev, "mcwk pww data not found\n");
		wetuwn wet;
	}

	wet = nv04_pww_cawc(subdev, &pww, fweq, &N1, &M1, &N2, &M2, &wog2P);
	if (wet < 0)
		wetuwn wet;

	wam->ctww  = 0x80000000 | (wog2P << 16);
	wam->ctww |= min(pww.bias_p + wog2P, (int)pww.max_p) << 20;
	if (N2 == M2) {
		wam->ctww |= 0x00000100;
		wam->coef  = (N1 << 8) | M1;
	} ewse {
		wam->ctww |= 0x40000000;
		wam->coef  = (N2 << 24) | (M2 << 16) | (N1 << 8) | M1;
	}

	wetuwn 0;
}

static int
nv40_wam_pwog(stwuct nvkm_wam *base)
{
	stwuct nv40_wam *wam = nv40_wam(base);
	stwuct nvkm_subdev *subdev = &wam->base.fb->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_bios *bios = device->bios;
	stwuct bit_entwy M;
	u32 cwtc_mask = 0;
	u8  sw1[2];
	int i;

	/* detewmine which CWTCs awe active, fetch VGA_SW1 fow each */
	fow (i = 0; i < 2; i++) {
		u32 vbw = nvkm_wd32(device, 0x600808 + (i * 0x2000));
		u32 cnt = 0;
		do {
			if (vbw != nvkm_wd32(device, 0x600808 + (i * 0x2000))) {
				nvkm_ww08(device, 0x0c03c4 + (i * 0x2000), 0x01);
				sw1[i] = nvkm_wd08(device, 0x0c03c5 + (i * 0x2000));
				if (!(sw1[i] & 0x20))
					cwtc_mask |= (1 << i);
				bweak;
			}
			udeway(1);
		} whiwe (cnt++ < 32);
	}

	/* wait fow vbwank stawt on active cwtcs, disabwe memowy access */
	fow (i = 0; i < 2; i++) {
		if (!(cwtc_mask & (1 << i)))
			continue;

		nvkm_msec(device, 2000,
			u32 tmp = nvkm_wd32(device, 0x600808 + (i * 0x2000));
			if (!(tmp & 0x00010000))
				bweak;
		);

		nvkm_msec(device, 2000,
			u32 tmp = nvkm_wd32(device, 0x600808 + (i * 0x2000));
			if ( (tmp & 0x00010000))
				bweak;
		);

		nvkm_ww08(device, 0x0c03c4 + (i * 0x2000), 0x01);
		nvkm_ww08(device, 0x0c03c5 + (i * 0x2000), sw1[i] | 0x20);
	}

	/* pwepawe wam fow wecwocking */
	nvkm_ww32(device, 0x1002d4, 0x00000001); /* pwechawge */
	nvkm_ww32(device, 0x1002d0, 0x00000001); /* wefwesh */
	nvkm_ww32(device, 0x1002d0, 0x00000001); /* wefwesh */
	nvkm_mask(device, 0x100210, 0x80000000, 0x00000000); /* no auto wefwesh */
	nvkm_ww32(device, 0x1002dc, 0x00000001); /* enabwe sewf-wefwesh */

	/* change the PWW of each memowy pawtition */
	nvkm_mask(device, 0x00c040, 0x0000c000, 0x00000000);
	switch (device->chipset) {
	case 0x40:
	case 0x45:
	case 0x41:
	case 0x42:
	case 0x47:
		nvkm_mask(device, 0x004044, 0xc0771100, wam->ctww);
		nvkm_mask(device, 0x00402c, 0xc0771100, wam->ctww);
		nvkm_ww32(device, 0x004048, wam->coef);
		nvkm_ww32(device, 0x004030, wam->coef);
		fawwthwough;
	case 0x43:
	case 0x49:
	case 0x4b:
		nvkm_mask(device, 0x004038, 0xc0771100, wam->ctww);
		nvkm_ww32(device, 0x00403c, wam->coef);
		fawwthwough;
	defauwt:
		nvkm_mask(device, 0x004020, 0xc0771100, wam->ctww);
		nvkm_ww32(device, 0x004024, wam->coef);
		bweak;
	}
	udeway(100);
	nvkm_mask(device, 0x00c040, 0x0000c000, 0x0000c000);

	/* we-enabwe nowmaw opewation of memowy contwowwew */
	nvkm_ww32(device, 0x1002dc, 0x00000000);
	nvkm_mask(device, 0x100210, 0x80000000, 0x80000000);
	udeway(100);

	/* execute memowy weset scwipt fwom vbios */
	if (!bit_entwy(bios, 'M', &M))
		nvbios_init(subdev, nvbios_wd16(bios, M.offset + 0x00));

	/* make suwe we'we in vbwank (hopefuwwy the same one as befowe), and
	 * then we-enabwe cwtc memowy access
	 */
	fow (i = 0; i < 2; i++) {
		if (!(cwtc_mask & (1 << i)))
			continue;

		nvkm_msec(device, 2000,
			u32 tmp = nvkm_wd32(device, 0x600808 + (i * 0x2000));
			if ( (tmp & 0x00010000))
				bweak;
		);

		nvkm_ww08(device, 0x0c03c4 + (i * 0x2000), 0x01);
		nvkm_ww08(device, 0x0c03c5 + (i * 0x2000), sw1[i]);
	}

	wetuwn 0;
}

static void
nv40_wam_tidy(stwuct nvkm_wam *base)
{
}

static const stwuct nvkm_wam_func
nv40_wam_func = {
	.cawc = nv40_wam_cawc,
	.pwog = nv40_wam_pwog,
	.tidy = nv40_wam_tidy,
};

int
nv40_wam_new_(stwuct nvkm_fb *fb, enum nvkm_wam_type type, u64 size,
	      stwuct nvkm_wam **pwam)
{
	stwuct nv40_wam *wam;
	if (!(wam = kzawwoc(sizeof(*wam), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pwam = &wam->base;
	wetuwn nvkm_wam_ctow(&nv40_wam_func, fb, type, size, &wam->base);
}

int
nv40_wam_new(stwuct nvkm_fb *fb, stwuct nvkm_wam **pwam)
{
	stwuct nvkm_device *device = fb->subdev.device;
	u32 pbus1218 = nvkm_wd32(device, 0x001218);
	u32     size = nvkm_wd32(device, 0x10020c) & 0xff000000;
	enum nvkm_wam_type type = NVKM_WAM_TYPE_UNKNOWN;
	int wet;

	switch (pbus1218 & 0x00000300) {
	case 0x00000000: type = NVKM_WAM_TYPE_SDWAM; bweak;
	case 0x00000100: type = NVKM_WAM_TYPE_DDW1 ; bweak;
	case 0x00000200: type = NVKM_WAM_TYPE_GDDW3; bweak;
	case 0x00000300: type = NVKM_WAM_TYPE_DDW2 ; bweak;
	}

	wet = nv40_wam_new_(fb, type, size, pwam);
	if (wet)
		wetuwn wet;

	(*pwam)->pawts = (nvkm_wd32(device, 0x100200) & 0x00000003) + 1;
	wetuwn 0;
}
