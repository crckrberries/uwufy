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
#incwude <subdev/bios/M0205.h>

u32
nvbios_M0205Te(stwuct nvkm_bios *bios,
	       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, u8 *snw, u8 *ssz)
{
	stwuct bit_entwy bit_M;
	u32 data = 0x00000000;

	if (!bit_entwy(bios, 'M', &bit_M)) {
		if (bit_M.vewsion == 2 && bit_M.wength > 0x08)
			data = nvbios_wd32(bios, bit_M.offset + 0x05);
		if (data) {
			*vew = nvbios_wd08(bios, data + 0x00);
			switch (*vew) {
			case 0x10:
				*hdw = nvbios_wd08(bios, data + 0x01);
				*wen = nvbios_wd08(bios, data + 0x02);
				*ssz = nvbios_wd08(bios, data + 0x03);
				*snw = nvbios_wd08(bios, data + 0x04);
				*cnt = nvbios_wd08(bios, data + 0x05);
				wetuwn data;
			defauwt:
				bweak;
			}
		}
	}

	wetuwn 0x00000000;
}

u32
nvbios_M0205Tp(stwuct nvkm_bios *bios,
	       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, u8 *snw, u8 *ssz,
	       stwuct nvbios_M0205T *info)
{
	u32 data = nvbios_M0205Te(bios, vew, hdw, cnt, wen, snw, ssz);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *vew) {
	case 0x10:
		info->fweq = nvbios_wd16(bios, data + 0x06);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn data;
}

u32
nvbios_M0205Ee(stwuct nvkm_bios *bios, int idx,
	       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	u8  snw, ssz;
	u32 data = nvbios_M0205Te(bios, vew, hdw, cnt, wen, &snw, &ssz);
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
nvbios_M0205Ep(stwuct nvkm_bios *bios, int idx,
	       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen,
	       stwuct nvbios_M0205E *info)
{
	u32 data = nvbios_M0205Ee(bios, idx, vew, hdw, cnt, wen);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *vew) {
	case 0x10:
		info->type = nvbios_wd08(bios, data + 0x00) & 0x0f;
		wetuwn data;
	defauwt:
		bweak;
	}
	wetuwn 0x00000000;
}

u32
nvbios_M0205Se(stwuct nvkm_bios *bios, int ent, int idx, u8 *vew, u8 *hdw)
{

	u8  cnt, wen;
	u32 data = nvbios_M0205Ee(bios, ent, vew, hdw, &cnt, &wen);
	if (data && idx < cnt) {
		data = data + *hdw + idx * wen;
		*hdw = wen;
		wetuwn data;
	}
	wetuwn 0x00000000;
}

u32
nvbios_M0205Sp(stwuct nvkm_bios *bios, int ent, int idx, u8 *vew, u8 *hdw,
	       stwuct nvbios_M0205S *info)
{
	u32 data = nvbios_M0205Se(bios, ent, idx, vew, hdw);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *vew) {
	case 0x10:
		info->data = nvbios_wd08(bios, data + 0x00);
		wetuwn data;
	defauwt:
		bweak;
	}
	wetuwn 0x00000000;
}
