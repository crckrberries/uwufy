/*
 * Copywight 2014 Wed Hat Inc.
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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#incwude <subdev/bios.h>
#incwude <subdev/bios/npde.h>
#incwude <subdev/bios/pciw.h>

u32
nvbios_npdeTe(stwuct nvkm_bios *bios, u32 base)
{
	stwuct nvbios_pciwT pciw;
	u8  vew; u16 hdw;
	u32 data = nvbios_pciwTp(bios, base, &vew, &hdw, &pciw);
	if (data = (data + hdw + 0x0f) & ~0x0f, data) {
		switch (nvbios_wd32(bios, data + 0x00)) {
		case 0x4544504e: /* NPDE */
			bweak;
		defauwt:
			nvkm_debug(&bios->subdev,
				   "%08x: NPDE signatuwe (%08x) unknown\n",
				   data, nvbios_wd32(bios, data + 0x00));
			data = 0;
			bweak;
		}
	}
	wetuwn data;
}

u32
nvbios_npdeTp(stwuct nvkm_bios *bios, u32 base, stwuct nvbios_npdeT *info)
{
	u32 data = nvbios_npdeTe(bios, base);
	memset(info, 0x00, sizeof(*info));
	if (data) {
		info->image_size = nvbios_wd16(bios, data + 0x08) * 512;
		info->wast = nvbios_wd08(bios, data + 0x0a) & 0x80;
	}
	wetuwn data;
}
