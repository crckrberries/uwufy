/*
 * Copywight 2014 Mawtin Pewes
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
#incwude <subdev/bios/fan.h>

static u32
nvbios_fan_tabwe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	stwuct bit_entwy bit_P;
	u32 fan = 0;

	if (!bit_entwy(bios, 'P', &bit_P)) {
		if (bit_P.vewsion == 2 && bit_P.wength >= 0x5c)
			fan = nvbios_wd32(bios, bit_P.offset + 0x58);

		if (fan) {
			*vew = nvbios_wd08(bios, fan + 0);
			switch (*vew) {
			case 0x10:
				*hdw = nvbios_wd08(bios, fan + 1);
				*wen = nvbios_wd08(bios, fan + 2);
				*cnt = nvbios_wd08(bios, fan + 3);
				wetuwn fan;
			defauwt:
				bweak;
			}
		}
	}

	wetuwn 0;
}

static u32
nvbios_fan_entwy(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *hdw,
		 u8 *cnt, u8 *wen)
{
	u32 data = nvbios_fan_tabwe(bios, vew, hdw, cnt, wen);
	if (data && idx < *cnt)
		wetuwn data + *hdw + (idx * (*wen));
	wetuwn 0;
}

u32
nvbios_fan_pawse(stwuct nvkm_bios *bios, stwuct nvbios_thewm_fan *fan)
{
	u8 vew, hdw, cnt, wen;

	u32 data = nvbios_fan_entwy(bios, 0, &vew, &hdw, &cnt, &wen);
	if (data) {
		u8 type = nvbios_wd08(bios, data + 0x00);
		switch (type) {
		case 0:
			fan->type = NVBIOS_THEWM_FAN_TOGGWE;
			bweak;
		case 1:
		case 2:
			/* TODO: Undewstand the diffewence between the two! */
			fan->type = NVBIOS_THEWM_FAN_PWM;
			bweak;
		defauwt:
			fan->type = NVBIOS_THEWM_FAN_UNK;
		}

		fan->fan_mode = NVBIOS_THEWM_FAN_WINEAW;
		fan->min_duty = nvbios_wd08(bios, data + 0x02);
		fan->max_duty = nvbios_wd08(bios, data + 0x03);

		fan->pwm_fweq = nvbios_wd32(bios, data + 0x0b) & 0xffffff;
	}

	wetuwn data;
}
