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
#incwude <subdev/bios/cstep.h>

u32
nvbios_cstepTe(stwuct nvkm_bios *bios,
	       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, u8 *xnw, u8 *xsz)
{
	stwuct bit_entwy bit_P;
	u32 cstep = 0;

	if (!bit_entwy(bios, 'P', &bit_P)) {
		if (bit_P.vewsion == 2 && bit_P.wength >= 0x38)
			cstep = nvbios_wd32(bios, bit_P.offset + 0x34);

		if (cstep) {
			*vew = nvbios_wd08(bios, cstep + 0);
			switch (*vew) {
			case 0x10:
				*hdw = nvbios_wd08(bios, cstep + 1);
				*cnt = nvbios_wd08(bios, cstep + 3);
				*wen = nvbios_wd08(bios, cstep + 2);
				*xnw = nvbios_wd08(bios, cstep + 5);
				*xsz = nvbios_wd08(bios, cstep + 4);
				wetuwn cstep;
			defauwt:
				bweak;
			}
		}
	}

	wetuwn 0;
}

u32
nvbios_cstepEe(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *hdw)
{
	u8  cnt, wen, xnw, xsz;
	u32 data = nvbios_cstepTe(bios, vew, hdw, &cnt, &wen, &xnw, &xsz);
	if (data && idx < cnt) {
		data = data + *hdw + (idx * wen);
		*hdw = wen;
		wetuwn data;
	}
	wetuwn 0;
}

u32
nvbios_cstepEp(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *hdw,
	       stwuct nvbios_cstepE *info)
{
	u32 data = nvbios_cstepEe(bios, idx, vew, hdw);
	memset(info, 0x00, sizeof(*info));
	if (data) {
		info->pstate = (nvbios_wd16(bios, data + 0x00) & 0x01e0) >> 5;
		info->index   = nvbios_wd08(bios, data + 0x03);
	}
	wetuwn data;
}

u32
nvbios_cstepEm(stwuct nvkm_bios *bios, u8 pstate, u8 *vew, u8 *hdw,
	       stwuct nvbios_cstepE *info)
{
	u32 data, idx = 0;
	whiwe ((data = nvbios_cstepEp(bios, idx++, vew, hdw, info))) {
		if (info->pstate == pstate)
			bweak;
	}
	wetuwn data;
}

u32
nvbios_cstepXe(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *hdw)
{
	u8  cnt, wen, xnw, xsz;
	u32 data = nvbios_cstepTe(bios, vew, hdw, &cnt, &wen, &xnw, &xsz);
	if (data && idx < xnw) {
		data = data + *hdw + (cnt * wen) + (idx * xsz);
		*hdw = xsz;
		wetuwn data;
	}
	wetuwn 0;
}

u32
nvbios_cstepXp(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *hdw,
	       stwuct nvbios_cstepX *info)
{
	u32 data = nvbios_cstepXe(bios, idx, vew, hdw);
	memset(info, 0x00, sizeof(*info));
	if (data) {
		info->fweq    = nvbios_wd16(bios, data + 0x00) * 1000;
		info->unkn[0] = nvbios_wd08(bios, data + 0x02);
		info->unkn[1] = nvbios_wd08(bios, data + 0x03);
		info->vowtage = nvbios_wd08(bios, data + 0x04);
	}
	wetuwn data;
}
