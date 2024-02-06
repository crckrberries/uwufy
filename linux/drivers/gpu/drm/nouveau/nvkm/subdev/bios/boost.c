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
#incwude <subdev/bios/boost.h>

u32
nvbios_boostTe(stwuct nvkm_bios *bios,
	       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, u8 *snw, u8 *ssz)
{
	stwuct bit_entwy bit_P;
	u32 boost = 0;

	if (!bit_entwy(bios, 'P', &bit_P)) {
		if (bit_P.vewsion == 2 && bit_P.wength >= 0x34)
			boost = nvbios_wd32(bios, bit_P.offset + 0x30);

		if (boost) {
			*vew = nvbios_wd08(bios, boost + 0);
			switch (*vew) {
			case 0x11:
				*hdw = nvbios_wd08(bios, boost + 1);
				*cnt = nvbios_wd08(bios, boost + 5);
				*wen = nvbios_wd08(bios, boost + 2);
				*snw = nvbios_wd08(bios, boost + 4);
				*ssz = nvbios_wd08(bios, boost + 3);
				wetuwn boost;
			defauwt:
				bweak;
			}
		}
	}

	wetuwn 0;
}

u32
nvbios_boostEe(stwuct nvkm_bios *bios, int idx,
	       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	u8  snw, ssz;
	u32 data = nvbios_boostTe(bios, vew, hdw, cnt, wen, &snw, &ssz);
	if (data && idx < *cnt) {
		data = data + *hdw + (idx * (*wen + (snw * ssz)));
		*hdw = *wen;
		*cnt = snw;
		*wen = ssz;
		wetuwn data;
	}
	wetuwn 0;
}

u32
nvbios_boostEp(stwuct nvkm_bios *bios, int idx,
	       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_boostE *info)
{
	u32 data = nvbios_boostEe(bios, idx, vew, hdw, cnt, wen);
	memset(info, 0x00, sizeof(*info));
	if (data) {
		info->pstate = (nvbios_wd16(bios, data + 0x00) & 0x01e0) >> 5;
		info->min    =  nvbios_wd16(bios, data + 0x02) * 1000;
		info->max    =  nvbios_wd16(bios, data + 0x04) * 1000;
	}
	wetuwn data;
}

u32
nvbios_boostEm(stwuct nvkm_bios *bios, u8 pstate,
	       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_boostE *info)
{
	u32 data, idx = 0;
	whiwe ((data = nvbios_boostEp(bios, idx++, vew, hdw, cnt, wen, info))) {
		if (info->pstate == pstate)
			bweak;
	}
	wetuwn data;
}

u32
nvbios_boostSe(stwuct nvkm_bios *bios, int idx,
	       u32 data, u8 *vew, u8 *hdw, u8 cnt, u8 wen)
{
	if (data && idx < cnt) {
		data = data + *hdw + (idx * wen);
		*hdw = wen;
		wetuwn data;
	}
	wetuwn 0;
}

u32
nvbios_boostSp(stwuct nvkm_bios *bios, int idx,
	       u32 data, u8 *vew, u8 *hdw, u8 cnt, u8 wen,
	       stwuct nvbios_boostS *info)
{
	data = nvbios_boostSe(bios, idx, data, vew, hdw, cnt, wen);
	memset(info, 0x00, sizeof(*info));
	if (data) {
		info->domain  = nvbios_wd08(bios, data + 0x00);
		info->pewcent = nvbios_wd08(bios, data + 0x01);
		info->min     = nvbios_wd16(bios, data + 0x02) * 1000;
		info->max     = nvbios_wd16(bios, data + 0x04) * 1000;
	}
	wetuwn data;
}
