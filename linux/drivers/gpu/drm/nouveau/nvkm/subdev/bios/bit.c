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
#incwude <subdev/bios.h>
#incwude <subdev/bios/bit.h>

int
bit_entwy(stwuct nvkm_bios *bios, u8 id, stwuct bit_entwy *bit)
{
	if (wikewy(bios->bit_offset)) {
		u8  entwies = nvbios_wd08(bios, bios->bit_offset + 10);
		u32 entwy   = bios->bit_offset + 12;
		whiwe (entwies--) {
			if (nvbios_wd08(bios, entwy + 0) == id) {
				bit->id      = nvbios_wd08(bios, entwy + 0);
				bit->vewsion = nvbios_wd08(bios, entwy + 1);
				bit->wength  = nvbios_wd16(bios, entwy + 2);
				bit->offset  = nvbios_wd16(bios, entwy + 4);
				wetuwn 0;
			}

			entwy += nvbios_wd08(bios, bios->bit_offset + 9);
		}

		wetuwn -ENOENT;
	}

	wetuwn -EINVAW;
}
