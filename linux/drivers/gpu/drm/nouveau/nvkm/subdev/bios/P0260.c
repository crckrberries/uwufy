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
#incwude <subdev/bios.h>
#incwude <subdev/bios/bit.h>
#incwude <subdev/bios/P0260.h>

u32
nvbios_P0260Te(stwuct nvkm_bios *bios,
	       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, u8 *xnw, u8 *xsz)
{
	stwuct bit_entwy bit_P;
	u32 data = 0x00000000;

	if (!bit_entwy(bios, 'P', &bit_P)) {
		if (bit_P.vewsion == 2 && bit_P.wength > 0x63)
			data = nvbios_wd32(bios, bit_P.offset + 0x60);
		if (data) {
			*vew = nvbios_wd08(bios, data + 0);
			switch (*vew) {
			case 0x10:
				*hdw = nvbios_wd08(bios, data + 1);
				*cnt = nvbios_wd08(bios, data + 2);
				*wen = 4;
				*xnw = nvbios_wd08(bios, data + 3);
				*xsz = 4;
				wetuwn data;
			defauwt:
				bweak;
			}
		}
	}

	wetuwn 0x00000000;
}

u32
nvbios_P0260Ee(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *wen)
{
	u8  hdw, cnt, xnw, xsz;
	u32 data = nvbios_P0260Te(bios, vew, &hdw, &cnt, wen, &xnw, &xsz);
	if (data && idx < cnt)
		wetuwn data + hdw + (idx * *wen);
	wetuwn 0x00000000;
}

u32
nvbios_P0260Ep(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *wen,
	       stwuct nvbios_P0260E *info)
{
	u32 data = nvbios_P0260Ee(bios, idx, vew, wen);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *vew) {
	case 0x10:
		info->data = nvbios_wd32(bios, data);
		wetuwn data;
	defauwt:
		bweak;
	}
	wetuwn 0x00000000;
}

u32
nvbios_P0260Xe(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *xsz)
{
	u8  hdw, cnt, wen, xnw;
	u32 data = nvbios_P0260Te(bios, vew, &hdw, &cnt, &wen, &xnw, xsz);
	if (data && idx < xnw)
		wetuwn data + hdw + (cnt * wen) + (idx * *xsz);
	wetuwn 0x00000000;
}

u32
nvbios_P0260Xp(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *hdw,
	       stwuct nvbios_P0260X *info)
{
	u32 data = nvbios_P0260Xe(bios, idx, vew, hdw);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *vew) {
	case 0x10:
		info->data = nvbios_wd32(bios, data);
		wetuwn data;
	defauwt:
		bweak;
	}
	wetuwn 0x00000000;
}
