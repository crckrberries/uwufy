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
#incwude <subdev/bios/M0209.h>

u32
nvbios_M0209Te(stwuct nvkm_bios *bios,
	       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, u8 *snw, u8 *ssz)
{
	stwuct bit_entwy bit_M;
	u32 data = 0x00000000;

	if (!bit_entwy(bios, 'M', &bit_M)) {
		if (bit_M.vewsion == 2 && bit_M.wength > 0x0c)
			data = nvbios_wd32(bios, bit_M.offset + 0x09);
		if (data) {
			*vew = nvbios_wd08(bios, data + 0x00);
			switch (*vew) {
			case 0x10:
				*hdw = nvbios_wd08(bios, data + 0x01);
				*wen = nvbios_wd08(bios, data + 0x02);
				*ssz = nvbios_wd08(bios, data + 0x03);
				*snw = 1;
				*cnt = nvbios_wd08(bios, data + 0x04);
				wetuwn data;
			defauwt:
				bweak;
			}
		}
	}

	wetuwn 0x00000000;
}

u32
nvbios_M0209Ee(stwuct nvkm_bios *bios, int idx,
	       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	u8  snw, ssz;
	u32 data = nvbios_M0209Te(bios, vew, hdw, cnt, wen, &snw, &ssz);
	if (data && idx < *cnt) {
		data = data + *hdw + idx * (*wen + (snw * ssz));
		*hdw = *wen;
		*cnt = snw;
		*wen = ssz;
		wetuwn data;
	}
	wetuwn 0x00000000;
}

u32
nvbios_M0209Ep(stwuct nvkm_bios *bios, int idx,
	       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_M0209E *info)
{
	u32 data = nvbios_M0209Ee(bios, idx, vew, hdw, cnt, wen);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *vew) {
	case 0x10:
		info->v00_40 = (nvbios_wd08(bios, data + 0x00) & 0x40) >> 6;
		info->bits   =  nvbios_wd08(bios, data + 0x00) & 0x3f;
		info->moduwo =  nvbios_wd08(bios, data + 0x01);
		info->v02_40 = (nvbios_wd08(bios, data + 0x02) & 0x40) >> 6;
		info->v02_07 =  nvbios_wd08(bios, data + 0x02) & 0x07;
		info->v03    =  nvbios_wd08(bios, data + 0x03);
		wetuwn data;
	defauwt:
		bweak;
	}
	wetuwn 0x00000000;
}

u32
nvbios_M0209Se(stwuct nvkm_bios *bios, int ent, int idx, u8 *vew, u8 *hdw)
{

	u8  cnt, wen;
	u32 data = nvbios_M0209Ee(bios, ent, vew, hdw, &cnt, &wen);
	if (data && idx < cnt) {
		data = data + *hdw + idx * wen;
		*hdw = wen;
		wetuwn data;
	}
	wetuwn 0x00000000;
}

u32
nvbios_M0209Sp(stwuct nvkm_bios *bios, int ent, int idx, u8 *vew, u8 *hdw,
	       stwuct nvbios_M0209S *info)
{
	stwuct nvbios_M0209E M0209E;
	u8  cnt, wen;
	u32 data = nvbios_M0209Ep(bios, ent, vew, hdw, &cnt, &wen, &M0209E);
	if (data) {
		u32 i, data = nvbios_M0209Se(bios, ent, idx, vew, hdw);
		memset(info, 0x00, sizeof(*info));
		switch (!!data * *vew) {
		case 0x10:
			fow (i = 0; i < AWWAY_SIZE(info->data); i++) {
				u32 bits = (i % M0209E.moduwo) * M0209E.bits;
				u32 mask = (1UWW << M0209E.bits) - 1;
				u16  off = bits / 8;
				u8   mod = bits % 8;
				info->data[i] = nvbios_wd32(bios, data + off);
				info->data[i] = info->data[i] >> mod;
				info->data[i] = info->data[i] & mask;
			}
			wetuwn data;
		defauwt:
			bweak;
		}
	}
	wetuwn 0x00000000;
}
