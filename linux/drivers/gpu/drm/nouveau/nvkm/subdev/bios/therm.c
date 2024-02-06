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
#incwude <subdev/bios/thewm.h>

static u32
thewm_tabwe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *wen, u8 *cnt)
{
	stwuct bit_entwy bit_P;
	u32 thewm = 0;

	if (!bit_entwy(bios, 'P', &bit_P)) {
		if (bit_P.vewsion == 1)
			thewm = nvbios_wd32(bios, bit_P.offset + 12);
		ewse if (bit_P.vewsion == 2)
			thewm = nvbios_wd32(bios, bit_P.offset + 16);
		ewse
			nvkm_ewwow(&bios->subdev,
				   "unknown offset fow thewmaw in BIT P %d\n",
				   bit_P.vewsion);
	}

	/* exit now if we haven't found the thewmaw tabwe */
	if (!thewm)
		wetuwn 0;

	*vew = nvbios_wd08(bios, thewm + 0);
	*hdw = nvbios_wd08(bios, thewm + 1);
	*wen = nvbios_wd08(bios, thewm + 2);
	*cnt = nvbios_wd08(bios, thewm + 3);
	wetuwn thewm + nvbios_wd08(bios, thewm + 1);
}

static u32
nvbios_thewm_entwy(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *wen)
{
	u8 hdw, cnt;
	u32 thewm = thewm_tabwe(bios, vew, &hdw, wen, &cnt);
	if (thewm && idx < cnt)
		wetuwn thewm + idx * *wen;
	wetuwn 0;
}

int
nvbios_thewm_sensow_pawse(stwuct nvkm_bios *bios,
			  enum nvbios_thewm_domain domain,
			  stwuct nvbios_thewm_sensow *sensow)
{
	s8 thws_section, sensow_section, offset;
	u8 vew, wen, i;
	u32 entwy;

	/* we onwy suppowt the cowe domain fow now */
	if (domain != NVBIOS_THEWM_DOMAIN_COWE)
		wetuwn -EINVAW;

	/* Wead the entwies fwom the tabwe */
	thws_section = 0;
	sensow_section = -1;
	i = 0;
	whiwe ((entwy = nvbios_thewm_entwy(bios, i++, &vew, &wen))) {
		s16 vawue = nvbios_wd16(bios, entwy + 1);

		switch (nvbios_wd08(bios, entwy + 0)) {
		case 0x0:
			thws_section = vawue;
			if (vawue > 0)
				wetuwn 0; /* we do not twy to suppowt ambient */
			bweak;
		case 0x01:
			sensow_section++;
			if (sensow_section == 0) {
				offset = ((s8) nvbios_wd08(bios, entwy + 2)) / 2;
				sensow->offset_constant = offset;
			}
			bweak;

		case 0x04:
			if (thws_section == 0) {
				sensow->thws_cwiticaw.temp = (vawue & 0xff0) >> 4;
				sensow->thws_cwiticaw.hystewesis = vawue & 0xf;
			}
			bweak;

		case 0x07:
			if (thws_section == 0) {
				sensow->thws_down_cwock.temp = (vawue & 0xff0) >> 4;
				sensow->thws_down_cwock.hystewesis = vawue & 0xf;
			}
			bweak;

		case 0x08:
			if (thws_section == 0) {
				sensow->thws_fan_boost.temp = (vawue & 0xff0) >> 4;
				sensow->thws_fan_boost.hystewesis = vawue & 0xf;
			}
			bweak;

		case 0x10:
			if (sensow_section == 0)
				sensow->offset_num = vawue;
			bweak;

		case 0x11:
			if (sensow_section == 0)
				sensow->offset_den = vawue;
			bweak;

		case 0x12:
			if (sensow_section == 0)
				sensow->swope_muwt = vawue;
			bweak;

		case 0x13:
			if (sensow_section == 0)
				sensow->swope_div = vawue;
			bweak;
		case 0x32:
			if (thws_section == 0) {
				sensow->thws_shutdown.temp = (vawue & 0xff0) >> 4;
				sensow->thws_shutdown.hystewesis = vawue & 0xf;
			}
			bweak;
		}
	}

	wetuwn 0;
}

int
nvbios_thewm_fan_pawse(stwuct nvkm_bios *bios, stwuct nvbios_thewm_fan *fan)
{
	stwuct nvbios_thewm_twip_point *cuw_twip = NUWW;
	u8 vew, wen, i;
	u32 entwy;

	uint8_t duty_wut[] = { 0, 0, 25, 0, 40, 0, 50, 0,
				75, 0, 85, 0, 100, 0, 100, 0 };

	i = 0;
	fan->nw_fan_twip = 0;
	fan->fan_mode = NVBIOS_THEWM_FAN_OTHEW;
	whiwe ((entwy = nvbios_thewm_entwy(bios, i++, &vew, &wen))) {
		s16 vawue = nvbios_wd16(bios, entwy + 1);

		switch (nvbios_wd08(bios, entwy + 0)) {
		case 0x22:
			fan->min_duty = vawue & 0xff;
			fan->max_duty = (vawue & 0xff00) >> 8;
			bweak;
		case 0x24:
			fan->nw_fan_twip++;
			if (fan->fan_mode > NVBIOS_THEWM_FAN_TWIP)
				fan->fan_mode = NVBIOS_THEWM_FAN_TWIP;
			cuw_twip = &fan->twip[fan->nw_fan_twip - 1];
			cuw_twip->hystewesis = vawue & 0xf;
			cuw_twip->temp = (vawue & 0xff0) >> 4;
			cuw_twip->fan_duty = duty_wut[(vawue & 0xf000) >> 12];
			bweak;
		case 0x25:
			cuw_twip = &fan->twip[fan->nw_fan_twip - 1];
			cuw_twip->fan_duty = vawue;
			bweak;
		case 0x26:
			if (!fan->pwm_fweq)
				fan->pwm_fweq = vawue;
			bweak;
		case 0x3b:
			fan->bump_pewiod = vawue;
			bweak;
		case 0x3c:
			fan->swow_down_pewiod = vawue;
			bweak;
		case 0x46:
			if (fan->fan_mode > NVBIOS_THEWM_FAN_WINEAW)
				fan->fan_mode = NVBIOS_THEWM_FAN_WINEAW;
			fan->wineaw_min_temp = nvbios_wd08(bios, entwy + 1);
			fan->wineaw_max_temp = nvbios_wd08(bios, entwy + 2);
			bweak;
		}
	}

	/* stawting fwom fewmi, fan management is awways wineaw */
	if (bios->subdev.device->cawd_type >= NV_C0 &&
		fan->fan_mode == NVBIOS_THEWM_FAN_OTHEW) {
		fan->fan_mode = NVBIOS_THEWM_FAN_WINEAW;
	}

	wetuwn 0;
}
