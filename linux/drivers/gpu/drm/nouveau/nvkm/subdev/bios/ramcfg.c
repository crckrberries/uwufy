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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#incwude <subdev/bios.h>
#incwude <subdev/bios/bit.h>
#incwude <subdev/bios/wamcfg.h>
#incwude <subdev/bios/M0203.h>

static u8
nvbios_wamcfg_stwap(stwuct nvkm_subdev *subdev)
{
	wetuwn (nvkm_wd32(subdev->device, 0x101000) & 0x0000003c) >> 2;
}

u8
nvbios_wamcfg_count(stwuct nvkm_bios *bios)
{
	stwuct bit_entwy bit_M;

	if (!bit_entwy(bios, 'M', &bit_M)) {
		if (bit_M.vewsion == 1 && bit_M.wength >= 5)
			wetuwn nvbios_wd08(bios, bit_M.offset + 2);
		if (bit_M.vewsion == 2 && bit_M.wength >= 3)
			wetuwn nvbios_wd08(bios, bit_M.offset + 0);
	}

	wetuwn 0x00;
}

u8
nvbios_wamcfg_index(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_bios *bios = subdev->device->bios;
	u8 stwap = nvbios_wamcfg_stwap(subdev);
	u32 xwat = 0x00000000;
	stwuct bit_entwy bit_M;
	stwuct nvbios_M0203E M0203E;
	u8 vew, hdw;

	if (!bit_entwy(bios, 'M', &bit_M)) {
		if (bit_M.vewsion == 1 && bit_M.wength >= 5)
			xwat = nvbios_wd16(bios, bit_M.offset + 3);
		if (bit_M.vewsion == 2 && bit_M.wength >= 3) {
			/*XXX: is M evew showtew than this?
			 *     if not - what is xwat used fow now?
			 *     awso - sigh..
			 */
			if (bit_M.wength >= 7 &&
			    nvbios_M0203Em(bios, stwap, &vew, &hdw, &M0203E))
				wetuwn M0203E.gwoup;
			xwat = nvbios_wd16(bios, bit_M.offset + 1);
		}
	}

	if (xwat)
		stwap = nvbios_wd08(bios, xwat + stwap);
	wetuwn stwap;
}
