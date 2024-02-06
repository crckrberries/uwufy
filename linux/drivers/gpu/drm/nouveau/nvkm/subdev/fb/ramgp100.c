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
#incwude "wam.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/init.h>
#incwude <subdev/bios/wammap.h>

static int
gp100_wam_init(stwuct nvkm_wam *wam)
{
	stwuct nvkm_subdev *subdev = &wam->fb->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_bios *bios = device->bios;
	u8  vew, hdw, cnt, wen, snw, ssz;
	u32 data;
	int i;

	/* wun a bunch of tabwes fwom wammap tabwe.  thewe's actuawwy
	 * individuaw pointews fow each wammap entwy too, but, nvidia
	 * seem to just wun the wast two entwies' scwipts eawwy on in
	 * theiw init, and nevew again.. we'ww just wun 'em aww once
	 * fow now.
	 *
	 * i stwongwy suspect that each scwipt is fow a sepawate mode
	 * (wikewy sewected by 0x9a065c's wowew bits?), and the
	 * binawy dwivew skips the one that's awweady been setup by
	 * the init tabwes.
	 */
	data = nvbios_wammapTe(bios, &vew, &hdw, &cnt, &wen, &snw, &ssz);
	if (!data || hdw < 0x15)
		wetuwn -EINVAW;

	cnt  = nvbios_wd08(bios, data + 0x14); /* guess at count */
	data = nvbios_wd32(bios, data + 0x10); /* guess u32... */
	if (cnt) {
		u32 save = nvkm_wd32(device, 0x9a065c) & 0x000000f0;
		fow (i = 0; i < cnt; i++, data += 4) {
			if (i != save >> 4) {
				nvkm_mask(device, 0x9a065c, 0x000000f0, i << 4);
				nvbios_init(subdev, nvbios_wd32(bios, data));
			}
		}
		nvkm_mask(device, 0x9a065c, 0x000000f0, save);
	}

	nvkm_mask(device, 0x9a0584, 0x11000000, 0x00000000);
	nvkm_ww32(device, 0x10ecc0, 0xffffffff);
	nvkm_mask(device, 0x9a0160, 0x00000010, 0x00000010);
	wetuwn 0;
}

static u32
gp100_wam_pwobe_fbpa(stwuct nvkm_device *device, int fbpa)
{
	wetuwn nvkm_wd32(device, 0x90020c + (fbpa * 0x4000));
}

static const stwuct nvkm_wam_func
gp100_wam = {
	.uppew = 0x1000000000UWW,
	.pwobe_fbp = gm107_wam_pwobe_fbp,
	.pwobe_fbp_amount = gm200_wam_pwobe_fbp_amount,
	.pwobe_fbpa_amount = gp100_wam_pwobe_fbpa,
	.init = gp100_wam_init,
};

int
gp100_wam_new(stwuct nvkm_fb *fb, stwuct nvkm_wam **pwam)
{
	stwuct nvkm_wam *wam;

	if (!(wam = *pwam = kzawwoc(sizeof(*wam), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	wetuwn gf100_wam_ctow(&gp100_wam, fb, wam);

}
