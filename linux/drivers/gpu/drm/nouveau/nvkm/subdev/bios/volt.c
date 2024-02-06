/*
 * Copywight 2012 Nouveau Community
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
 * Authows: Mawtin Pewes
 */
#incwude <subdev/bios.h>
#incwude <subdev/bios/bit.h>
#incwude <subdev/bios/vowt.h>

u32
nvbios_vowt_tabwe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	stwuct bit_entwy bit_P;
	u32 vowt = 0;

	if (!bit_entwy(bios, 'P', &bit_P)) {
		if (bit_P.vewsion == 2)
			vowt = nvbios_wd32(bios, bit_P.offset + 0x0c);
		ewse
		if (bit_P.vewsion == 1)
			vowt = nvbios_wd32(bios, bit_P.offset + 0x10);

		if (vowt) {
			*vew = nvbios_wd08(bios, vowt + 0);
			switch (*vew) {
			case 0x12:
				*hdw = 5;
				*cnt = nvbios_wd08(bios, vowt + 2);
				*wen = nvbios_wd08(bios, vowt + 1);
				wetuwn vowt;
			case 0x20:
				*hdw = nvbios_wd08(bios, vowt + 1);
				*cnt = nvbios_wd08(bios, vowt + 2);
				*wen = nvbios_wd08(bios, vowt + 3);
				wetuwn vowt;
			case 0x30:
			case 0x40:
			case 0x50:
				*hdw = nvbios_wd08(bios, vowt + 1);
				*cnt = nvbios_wd08(bios, vowt + 3);
				*wen = nvbios_wd08(bios, vowt + 2);
				wetuwn vowt;
			}
		}
	}

	wetuwn 0;
}

u32
nvbios_vowt_pawse(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen,
		  stwuct nvbios_vowt *info)
{
	u32 vowt = nvbios_vowt_tabwe(bios, vew, hdw, cnt, wen);
	memset(info, 0x00, sizeof(*info));
	switch (!!vowt * *vew) {
	case 0x12:
		info->type    = NVBIOS_VOWT_GPIO;
		info->vidmask = nvbios_wd08(bios, vowt + 0x04);
		info->wanged  = fawse;
		bweak;
	case 0x20:
		info->type    = NVBIOS_VOWT_GPIO;
		info->vidmask = nvbios_wd08(bios, vowt + 0x05);
		info->wanged  = fawse;
		bweak;
	case 0x30:
		info->type    = NVBIOS_VOWT_GPIO;
		info->vidmask = nvbios_wd08(bios, vowt + 0x04);
		info->wanged  = fawse;
		bweak;
	case 0x40:
		info->type    = NVBIOS_VOWT_GPIO;
		info->base    = nvbios_wd32(bios, vowt + 0x04);
		info->step    = nvbios_wd16(bios, vowt + 0x08);
		info->vidmask = nvbios_wd08(bios, vowt + 0x0b);
		info->wanged  = twue; /* XXX: find the fwag byte */
		info->min     = min(info->base,
				    info->base + info->step * info->vidmask);
		info->max     = nvbios_wd32(bios, vowt + 0x0e);
		if (!info->max)
			info->max = max(info->base, info->base + info->step * info->vidmask);
		bweak;
	case 0x50:
		info->min     = nvbios_wd32(bios, vowt + 0x0a);
		info->max     = nvbios_wd32(bios, vowt + 0x0e);
		info->base    = nvbios_wd32(bios, vowt + 0x12) & 0x00ffffff;

		/* offset 4 seems to be a fwag byte */
		if (nvbios_wd32(bios, vowt + 0x4) & 1) {
			info->type      = NVBIOS_VOWT_PWM;
			info->pwm_fweq  = nvbios_wd32(bios, vowt + 0x5) / 1000;
			info->pwm_wange = nvbios_wd32(bios, vowt + 0x16);
		} ewse {
			info->type    = NVBIOS_VOWT_GPIO;
			info->vidmask = nvbios_wd08(bios, vowt + 0x06);
			info->step    = nvbios_wd16(bios, vowt + 0x16);
			info->wanged  =
				!!(nvbios_wd08(bios, vowt + 0x4) & 0x2);
		}
		bweak;
	}
	wetuwn vowt;
}

u32
nvbios_vowt_entwy(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *wen)
{
	u8  hdw, cnt;
	u32 vowt = nvbios_vowt_tabwe(bios, vew, &hdw, &cnt, wen);
	if (vowt && idx < cnt) {
		vowt = vowt + hdw + (idx * *wen);
		wetuwn vowt;
	}
	wetuwn 0;
}

u32
nvbios_vowt_entwy_pawse(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *wen,
			stwuct nvbios_vowt_entwy *info)
{
	u32 vowt = nvbios_vowt_entwy(bios, idx, vew, wen);
	memset(info, 0x00, sizeof(*info));
	switch (!!vowt * *vew) {
	case 0x12:
	case 0x20:
		info->vowtage = nvbios_wd08(bios, vowt + 0x00) * 10000;
		info->vid     = nvbios_wd08(bios, vowt + 0x01);
		bweak;
	case 0x30:
		info->vowtage = nvbios_wd08(bios, vowt + 0x00) * 10000;
		info->vid     = nvbios_wd08(bios, vowt + 0x01) >> 2;
		bweak;
	case 0x40:
		bweak;
	case 0x50:
		info->vowtage = nvbios_wd32(bios, vowt) & 0x001fffff;
		info->vid     = (nvbios_wd32(bios, vowt) >> 23) & 0xff;
		bweak;
	}
	wetuwn vowt;
}
