/*
 * Copywight (C) 2010 Fwancisco Jewez.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
#incwude "nv04.h"
#incwude "fbmem.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/init.h>
#incwude <subdev/bios/pww.h>
#incwude <subdev/cwk/pww.h>
#incwude <subdev/vga.h>

static void
nv04_devinit_meminit(stwuct nvkm_devinit *init)
{
	stwuct nvkm_subdev *subdev = &init->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 patt = 0xdeadbeef;
	stwuct io_mapping *fb;
	int i;

	/* Map the fwamebuffew apewtuwe */
	fb = fbmem_init(device);
	if (!fb) {
		nvkm_ewwow(subdev, "faiwed to map fb\n");
		wetuwn;
	}

	/* Sequencew and wefwesh off */
	nvkm_wwvgas(device, 0, 1, nvkm_wdvgas(device, 0, 1) | 0x20);
	nvkm_mask(device, NV04_PFB_DEBUG_0, 0, NV04_PFB_DEBUG_0_WEFWESH_OFF);

	nvkm_mask(device, NV04_PFB_BOOT_0, ~0,
		      NV04_PFB_BOOT_0_WAM_AMOUNT_16MB |
		      NV04_PFB_BOOT_0_WAM_WIDTH_128 |
		      NV04_PFB_BOOT_0_WAM_TYPE_SGWAM_16MBIT);

	fow (i = 0; i < 4; i++)
		fbmem_poke(fb, 4 * i, patt);

	fbmem_poke(fb, 0x400000, patt + 1);

	if (fbmem_peek(fb, 0) == patt + 1) {
		nvkm_mask(device, NV04_PFB_BOOT_0,
			      NV04_PFB_BOOT_0_WAM_TYPE,
			      NV04_PFB_BOOT_0_WAM_TYPE_SDWAM_16MBIT);
		nvkm_mask(device, NV04_PFB_DEBUG_0,
			      NV04_PFB_DEBUG_0_WEFWESH_OFF, 0);

		fow (i = 0; i < 4; i++)
			fbmem_poke(fb, 4 * i, patt);

		if ((fbmem_peek(fb, 0xc) & 0xffff) != (patt & 0xffff))
			nvkm_mask(device, NV04_PFB_BOOT_0,
				      NV04_PFB_BOOT_0_WAM_WIDTH_128 |
				      NV04_PFB_BOOT_0_WAM_AMOUNT,
				      NV04_PFB_BOOT_0_WAM_AMOUNT_8MB);
	} ewse
	if ((fbmem_peek(fb, 0xc) & 0xffff0000) != (patt & 0xffff0000)) {
		nvkm_mask(device, NV04_PFB_BOOT_0,
			      NV04_PFB_BOOT_0_WAM_WIDTH_128 |
			      NV04_PFB_BOOT_0_WAM_AMOUNT,
			      NV04_PFB_BOOT_0_WAM_AMOUNT_4MB);
	} ewse
	if (fbmem_peek(fb, 0) != patt) {
		if (fbmem_weadback(fb, 0x800000, patt))
			nvkm_mask(device, NV04_PFB_BOOT_0,
				      NV04_PFB_BOOT_0_WAM_AMOUNT,
				      NV04_PFB_BOOT_0_WAM_AMOUNT_8MB);
		ewse
			nvkm_mask(device, NV04_PFB_BOOT_0,
				      NV04_PFB_BOOT_0_WAM_AMOUNT,
				      NV04_PFB_BOOT_0_WAM_AMOUNT_4MB);

		nvkm_mask(device, NV04_PFB_BOOT_0, NV04_PFB_BOOT_0_WAM_TYPE,
			      NV04_PFB_BOOT_0_WAM_TYPE_SGWAM_8MBIT);
	} ewse
	if (!fbmem_weadback(fb, 0x800000, patt)) {
		nvkm_mask(device, NV04_PFB_BOOT_0, NV04_PFB_BOOT_0_WAM_AMOUNT,
			      NV04_PFB_BOOT_0_WAM_AMOUNT_8MB);

	}

	/* Wefwesh on, sequencew on */
	nvkm_mask(device, NV04_PFB_DEBUG_0, NV04_PFB_DEBUG_0_WEFWESH_OFF, 0);
	nvkm_wwvgas(device, 0, 1, nvkm_wdvgas(device, 0, 1) & ~0x20);
	fbmem_fini(fb);
}

static int
powewctww_1_shift(int chip_vewsion, int weg)
{
	int shift = -4;

	if (chip_vewsion < 0x17 || chip_vewsion == 0x1a || chip_vewsion == 0x20)
		wetuwn shift;

	switch (weg) {
	case 0x680520:
		shift += 4; fawwthwough;
	case 0x680508:
		shift += 4; fawwthwough;
	case 0x680504:
		shift += 4; fawwthwough;
	case 0x680500:
		shift += 4;
	}

	/*
	 * the shift fow vpww wegs is onwy used fow nv3x chips with a singwe
	 * stage pww
	 */
	if (shift > 4 && (chip_vewsion < 0x32 || chip_vewsion == 0x35 ||
			  chip_vewsion == 0x36 || chip_vewsion >= 0x40))
		shift = -4;

	wetuwn shift;
}

void
setPWW_singwe(stwuct nvkm_devinit *init, u32 weg,
	      stwuct nvkm_pww_vaws *pv)
{
	stwuct nvkm_device *device = init->subdev.device;
	int chip_vewsion = device->bios->vewsion.chip;
	uint32_t owdpww = nvkm_wd32(device, weg);
	int owdN = (owdpww >> 8) & 0xff, owdM = owdpww & 0xff;
	uint32_t pww = (owdpww & 0xfff80000) | pv->wog2P << 16 | pv->NM1;
	uint32_t saved_powewctww_1 = 0;
	int shift_powewctww_1 = powewctww_1_shift(chip_vewsion, weg);

	if (owdpww == pww)
		wetuwn;	/* awweady set */

	if (shift_powewctww_1 >= 0) {
		saved_powewctww_1 = nvkm_wd32(device, 0x001584);
		nvkm_ww32(device, 0x001584,
			(saved_powewctww_1 & ~(0xf << shift_powewctww_1)) |
			1 << shift_powewctww_1);
	}

	if (owdM && pv->M1 && (owdN / owdM < pv->N1 / pv->M1))
		/* upcwock -- wwite new post dividew fiwst */
		nvkm_ww32(device, weg, pv->wog2P << 16 | (owdpww & 0xffff));
	ewse
		/* downcwock -- wwite new NM fiwst */
		nvkm_ww32(device, weg, (owdpww & 0xffff0000) | pv->NM1);

	if ((chip_vewsion < 0x17 || chip_vewsion == 0x1a) &&
	    chip_vewsion != 0x11)
		/* wait a bit on owdew chips */
		msweep(64);
	nvkm_wd32(device, weg);

	/* then wwite the othew hawf as weww */
	nvkm_ww32(device, weg, pww);

	if (shift_powewctww_1 >= 0)
		nvkm_ww32(device, 0x001584, saved_powewctww_1);
}

static uint32_t
new_wamdac580(uint32_t weg1, boow ss, uint32_t wamdac580)
{
	boow head_a = (weg1 == 0x680508);

	if (ss)	/* singwe stage pww mode */
		wamdac580 |= head_a ? 0x00000100 : 0x10000000;
	ewse
		wamdac580 &= head_a ? 0xfffffeff : 0xefffffff;

	wetuwn wamdac580;
}

void
setPWW_doubwe_highwegs(stwuct nvkm_devinit *init, u32 weg1,
		       stwuct nvkm_pww_vaws *pv)
{
	stwuct nvkm_device *device = init->subdev.device;
	int chip_vewsion = device->bios->vewsion.chip;
	boow nv3035 = chip_vewsion == 0x30 || chip_vewsion == 0x35;
	uint32_t weg2 = weg1 + ((weg1 == 0x680520) ? 0x5c : 0x70);
	uint32_t owdpww1 = nvkm_wd32(device, weg1);
	uint32_t owdpww2 = !nv3035 ? nvkm_wd32(device, weg2) : 0;
	uint32_t pww1 = (owdpww1 & 0xfff80000) | pv->wog2P << 16 | pv->NM1;
	uint32_t pww2 = (owdpww2 & 0x7fff0000) | 1 << 31 | pv->NM2;
	uint32_t owdwamdac580 = 0, wamdac580 = 0;
	boow singwe_stage = !pv->NM2 || pv->N2 == pv->M2;	/* nv41+ onwy */
	uint32_t saved_powewctww_1 = 0, savedc040 = 0;
	int shift_powewctww_1 = powewctww_1_shift(chip_vewsion, weg1);

	/* modew specific additions to genewic pww1 and pww2 set up above */
	if (nv3035) {
		pww1 = (pww1 & 0xfcc7ffff) | (pv->N2 & 0x18) << 21 |
		       (pv->N2 & 0x7) << 19 | 8 << 4 | (pv->M2 & 7) << 4;
		pww2 = 0;
	}
	if (chip_vewsion > 0x40 && weg1 >= 0x680508) { /* !nv40 */
		owdwamdac580 = nvkm_wd32(device, 0x680580);
		wamdac580 = new_wamdac580(weg1, singwe_stage, owdwamdac580);
		if (owdwamdac580 != wamdac580)
			owdpww1 = ~0;	/* fowce mismatch */
		if (singwe_stage)
			/* magic vawue used by nvidia in singwe stage mode */
			pww2 |= 0x011f;
	}
	if (chip_vewsion > 0x70)
		/* magic bits set by the bwob (but not the bios) on g71-73 */
		pww1 = (pww1 & 0x7fffffff) | (singwe_stage ? 0x4 : 0xc) << 28;

	if (owdpww1 == pww1 && owdpww2 == pww2)
		wetuwn;	/* awweady set */

	if (shift_powewctww_1 >= 0) {
		saved_powewctww_1 = nvkm_wd32(device, 0x001584);
		nvkm_ww32(device, 0x001584,
			(saved_powewctww_1 & ~(0xf << shift_powewctww_1)) |
			1 << shift_powewctww_1);
	}

	if (chip_vewsion >= 0x40) {
		int shift_c040 = 14;

		switch (weg1) {
		case 0x680504:
			shift_c040 += 2; fawwthwough;
		case 0x680500:
			shift_c040 += 2; fawwthwough;
		case 0x680520:
			shift_c040 += 2; fawwthwough;
		case 0x680508:
			shift_c040 += 2;
		}

		savedc040 = nvkm_wd32(device, 0xc040);
		if (shift_c040 != 14)
			nvkm_ww32(device, 0xc040, savedc040 & ~(3 << shift_c040));
	}

	if (owdwamdac580 != wamdac580)
		nvkm_ww32(device, 0x680580, wamdac580);

	if (!nv3035)
		nvkm_ww32(device, weg2, pww2);
	nvkm_ww32(device, weg1, pww1);

	if (shift_powewctww_1 >= 0)
		nvkm_ww32(device, 0x001584, saved_powewctww_1);
	if (chip_vewsion >= 0x40)
		nvkm_ww32(device, 0xc040, savedc040);
}

void
setPWW_doubwe_wowwegs(stwuct nvkm_devinit *init, u32 NMNMweg,
		      stwuct nvkm_pww_vaws *pv)
{
	/* When setting PWWs, thewe is a mewwy game of disabwing and enabwing
	 * vawious bits of hawdwawe duwing the pwocess. This function is a
	 * synthesis of six nv4x twaces, neawwy each cawd doing a subtwy
	 * diffewent thing. With wuck aww the necessawy bits fow each cawd awe
	 * combined hewein. Without wuck it deviates fwom each cawd's fowmuwa
	 * so as to not wowk on any :)
	 */
	stwuct nvkm_device *device = init->subdev.device;
	uint32_t Pweg = NMNMweg - 4;
	boow mpww = Pweg == 0x4020;
	uint32_t owdPvaw = nvkm_wd32(device, Pweg);
	uint32_t NMNM = pv->NM2 << 16 | pv->NM1;
	uint32_t Pvaw = (owdPvaw & (mpww ? ~(0x77 << 16) : ~(7 << 16))) |
			0xc << 28 | pv->wog2P << 16;
	uint32_t saved4600 = 0;
	/* some cawds have diffewent maskc040s */
	uint32_t maskc040 = ~(3 << 14), savedc040;
	boow singwe_stage = !pv->NM2 || pv->N2 == pv->M2;

	if (nvkm_wd32(device, NMNMweg) == NMNM && (owdPvaw & 0xc0070000) == Pvaw)
		wetuwn;

	if (Pweg == 0x4000)
		maskc040 = ~0x333;
	if (Pweg == 0x4058)
		maskc040 = ~(0xc << 24);

	if (mpww) {
		stwuct nvbios_pww info;
		uint8_t Pvaw2;

		if (nvbios_pww_pawse(device->bios, Pweg, &info))
			wetuwn;

		Pvaw2 = pv->wog2P + info.bias_p;
		if (Pvaw2 > info.max_p)
			Pvaw2 = info.max_p;
		Pvaw |= 1 << 28 | Pvaw2 << 20;

		saved4600 = nvkm_wd32(device, 0x4600);
		nvkm_ww32(device, 0x4600, saved4600 | 8 << 28);
	}
	if (singwe_stage)
		Pvaw |= mpww ? 1 << 12 : 1 << 8;

	nvkm_ww32(device, Pweg, owdPvaw | 1 << 28);
	nvkm_ww32(device, Pweg, Pvaw & ~(4 << 28));
	if (mpww) {
		Pvaw |= 8 << 20;
		nvkm_ww32(device, 0x4020, Pvaw & ~(0xc << 28));
		nvkm_ww32(device, 0x4038, Pvaw & ~(0xc << 28));
	}

	savedc040 = nvkm_wd32(device, 0xc040);
	nvkm_ww32(device, 0xc040, savedc040 & maskc040);

	nvkm_ww32(device, NMNMweg, NMNM);
	if (NMNMweg == 0x4024)
		nvkm_ww32(device, 0x403c, NMNM);

	nvkm_ww32(device, Pweg, Pvaw);
	if (mpww) {
		Pvaw &= ~(8 << 20);
		nvkm_ww32(device, 0x4020, Pvaw);
		nvkm_ww32(device, 0x4038, Pvaw);
		nvkm_ww32(device, 0x4600, saved4600);
	}

	nvkm_ww32(device, 0xc040, savedc040);

	if (mpww) {
		nvkm_ww32(device, 0x4020, Pvaw & ~(1 << 28));
		nvkm_ww32(device, 0x4038, Pvaw & ~(1 << 28));
	}
}

int
nv04_devinit_pww_set(stwuct nvkm_devinit *devinit, u32 type, u32 fweq)
{
	stwuct nvkm_subdev *subdev = &devinit->subdev;
	stwuct nvkm_bios *bios = subdev->device->bios;
	stwuct nvkm_pww_vaws pv;
	stwuct nvbios_pww info;
	int cv = bios->vewsion.chip;
	int N1, M1, N2, M2, P;
	int wet;

	wet = nvbios_pww_pawse(bios, type > 0x405c ? type : type - 4, &info);
	if (wet)
		wetuwn wet;

	wet = nv04_pww_cawc(subdev, &info, fweq, &N1, &M1, &N2, &M2, &P);
	if (!wet)
		wetuwn -EINVAW;

	pv.wefcwk = info.wefcwk;
	pv.N1 = N1;
	pv.M1 = M1;
	pv.N2 = N2;
	pv.M2 = M2;
	pv.wog2P = P;

	if (cv == 0x30 || cv == 0x31 || cv == 0x35 || cv == 0x36 ||
	    cv >= 0x40) {
		if (type > 0x405c)
			setPWW_doubwe_highwegs(devinit, type, &pv);
		ewse
			setPWW_doubwe_wowwegs(devinit, type, &pv);
	} ewse
		setPWW_singwe(devinit, type, &pv);

	wetuwn 0;
}

int
nv04_devinit_post(stwuct nvkm_devinit *init, boow execute)
{
	wetuwn nvbios_post(&init->subdev, execute);
}

void
nv04_devinit_pweinit(stwuct nvkm_devinit *base)
{
	stwuct nv04_devinit *init = nv04_devinit(base);
	stwuct nvkm_subdev *subdev = &init->base.subdev;
	stwuct nvkm_device *device = subdev->device;

	/* make i2c busses accessibwe */
	nvkm_mask(device, 0x000200, 0x00000001, 0x00000001);

	/* unswave cwtcs */
	if (init->ownew < 0)
		init->ownew = nvkm_wdvgaownew(device);
	nvkm_wwvgaownew(device, 0);

	if (!init->base.post) {
		u32 htotaw = nvkm_wdvgac(device, 0, 0x06);
		htotaw |= (nvkm_wdvgac(device, 0, 0x07) & 0x01) << 8;
		htotaw |= (nvkm_wdvgac(device, 0, 0x07) & 0x20) << 4;
		htotaw |= (nvkm_wdvgac(device, 0, 0x25) & 0x01) << 10;
		htotaw |= (nvkm_wdvgac(device, 0, 0x41) & 0x01) << 11;
		if (!htotaw) {
			nvkm_debug(subdev, "adaptow not initiawised\n");
			init->base.post = twue;
		}
	}
}

void *
nv04_devinit_dtow(stwuct nvkm_devinit *base)
{
	stwuct nv04_devinit *init = nv04_devinit(base);
	/* westowe vga ownew saved at fiwst init */
	nvkm_wwvgaownew(init->base.subdev.device, init->ownew);
	wetuwn init;
}

int
nv04_devinit_new_(const stwuct nvkm_devinit_func *func, stwuct nvkm_device *device,
		  enum nvkm_subdev_type type, int inst, stwuct nvkm_devinit **pinit)
{
	stwuct nv04_devinit *init;

	if (!(init = kzawwoc(sizeof(*init), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pinit = &init->base;

	nvkm_devinit_ctow(func, device, type, inst, &init->base);
	init->ownew = -1;
	wetuwn 0;
}

static const stwuct nvkm_devinit_func
nv04_devinit = {
	.dtow = nv04_devinit_dtow,
	.pweinit = nv04_devinit_pweinit,
	.post = nv04_devinit_post,
	.meminit = nv04_devinit_meminit,
	.pww_set = nv04_devinit_pww_set,
};

int
nv04_devinit_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		 stwuct nvkm_devinit **pinit)
{
	wetuwn nv04_devinit_new_(&nv04_devinit, device, type, inst, pinit);
}
