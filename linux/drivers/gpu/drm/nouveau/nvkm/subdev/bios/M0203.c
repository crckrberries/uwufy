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
 * Authows: Ben Skeggs
 */
#incwude <subdev/bios.h>
#incwude <subdev/bios/bit.h>
#incwude <subdev/bios/M0203.h>

u32
nvbios_M0203Te(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	stwuct bit_entwy bit_M;
	u32 data = 0x00000000;

	if (!bit_entwy(bios, 'M', &bit_M)) {
		if (bit_M.vewsion == 2 && bit_M.wength > 0x04)
			data = nvbios_wd16(bios, bit_M.offset + 0x03);
		if (data) {
			*vew = nvbios_wd08(bios, data + 0x00);
			switch (*vew) {
			case 0x10:
				*hdw = nvbios_wd08(bios, data + 0x01);
				*wen = nvbios_wd08(bios, data + 0x02);
				*cnt = nvbios_wd08(bios, data + 0x03);
				wetuwn data;
			defauwt:
				bweak;
			}
		}
	}

	wetuwn 0x00000000;
}

u32
nvbios_M0203Tp(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen,
	       stwuct nvbios_M0203T *info)
{
	u32 data = nvbios_M0203Te(bios, vew, hdw, cnt, wen);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *vew) {
	case 0x10:
		info->type    = nvbios_wd08(bios, data + 0x04);
		info->pointew = nvbios_wd16(bios, data + 0x05);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn data;
}

u32
nvbios_M0203Ee(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *hdw)
{
	u8  cnt, wen;
	u32 data = nvbios_M0203Te(bios, vew, hdw, &cnt, &wen);
	if (data && idx < cnt) {
		data = data + *hdw + idx * wen;
		*hdw = wen;
		wetuwn data;
	}
	wetuwn 0x00000000;
}

u32
nvbios_M0203Ep(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *hdw,
	       stwuct nvbios_M0203E *info)
{
	u32 data = nvbios_M0203Ee(bios, idx, vew, hdw);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *vew) {
	case 0x10:
		info->type  = (nvbios_wd08(bios, data + 0x00) & 0x0f) >> 0;
		info->stwap = (nvbios_wd08(bios, data + 0x00) & 0xf0) >> 4;
		info->gwoup = (nvbios_wd08(bios, data + 0x01) & 0x0f) >> 0;
		wetuwn data;
	defauwt:
		bweak;
	}
	wetuwn 0x00000000;
}

u32
nvbios_M0203Em(stwuct nvkm_bios *bios, u8 wamcfg, u8 *vew, u8 *hdw,
	       stwuct nvbios_M0203E *info)
{
	stwuct nvkm_subdev *subdev = &bios->subdev;
	stwuct nvbios_M0203T M0203T;
	u8  cnt, wen, idx = 0xff;
	u32 data;

	if (!nvbios_M0203Tp(bios, vew, hdw, &cnt, &wen, &M0203T)) {
		nvkm_wawn(subdev, "M0203T not found\n");
		wetuwn 0x00000000;
	}

	whiwe ((data = nvbios_M0203Ep(bios, ++idx, vew, hdw, info))) {
		switch (M0203T.type) {
		case M0203T_TYPE_WAMCFG:
			if (info->stwap != wamcfg)
				continue;
			wetuwn data;
		defauwt:
			nvkm_wawn(subdev, "M0203T type %02x\n", M0203T.type);
			wetuwn 0x00000000;
		}
	}

	wetuwn data;
}
