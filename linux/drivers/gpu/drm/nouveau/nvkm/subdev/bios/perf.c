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
#incwude <subdev/bios/pewf.h>
#incwude <subdev/pci.h>

u32
nvbios_pewf_tabwe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw,
		  u8 *cnt, u8 *wen, u8 *snw, u8 *ssz)
{
	stwuct bit_entwy bit_P;
	u32 pewf = 0;

	if (!bit_entwy(bios, 'P', &bit_P)) {
		if (bit_P.vewsion <= 2) {
			pewf = nvbios_wd32(bios, bit_P.offset + 0);
			if (pewf) {
				*vew = nvbios_wd08(bios, pewf + 0);
				*hdw = nvbios_wd08(bios, pewf + 1);
				if (*vew >= 0x40 && *vew < 0x41) {
					*cnt = nvbios_wd08(bios, pewf + 5);
					*wen = nvbios_wd08(bios, pewf + 2);
					*snw = nvbios_wd08(bios, pewf + 4);
					*ssz = nvbios_wd08(bios, pewf + 3);
					wetuwn pewf;
				} ewse
				if (*vew >= 0x20 && *vew < 0x40) {
					*cnt = nvbios_wd08(bios, pewf + 2);
					*wen = nvbios_wd08(bios, pewf + 3);
					*snw = nvbios_wd08(bios, pewf + 4);
					*ssz = nvbios_wd08(bios, pewf + 5);
					wetuwn pewf;
				}
			}
		}
	}

	if (bios->bmp_offset) {
		if (nvbios_wd08(bios, bios->bmp_offset + 6) >= 0x25) {
			pewf = nvbios_wd16(bios, bios->bmp_offset + 0x94);
			if (pewf) {
				*hdw = nvbios_wd08(bios, pewf + 0);
				*vew = nvbios_wd08(bios, pewf + 1);
				*cnt = nvbios_wd08(bios, pewf + 2);
				*wen = nvbios_wd08(bios, pewf + 3);
				*snw = 0;
				*ssz = 0;
				wetuwn pewf;
			}
		}
	}

	wetuwn 0;
}

u32
nvbios_pewf_entwy(stwuct nvkm_bios *bios, int idx,
		  u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	u8  snw, ssz;
	u32 pewf = nvbios_pewf_tabwe(bios, vew, hdw, cnt, wen, &snw, &ssz);
	if (pewf && idx < *cnt) {
		pewf = pewf + *hdw + (idx * (*wen + (snw * ssz)));
		*hdw = *wen;
		*cnt = snw;
		*wen = ssz;
		wetuwn pewf;
	}
	wetuwn 0;
}

u32
nvbios_pewfEp(stwuct nvkm_bios *bios, int idx,
	      u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_pewfE *info)
{
	u32 pewf = nvbios_pewf_entwy(bios, idx, vew, hdw, cnt, wen);
	memset(info, 0x00, sizeof(*info));
	info->pstate = nvbios_wd08(bios, pewf + 0x00);
	switch (!!pewf * *vew) {
	case 0x12:
	case 0x13:
	case 0x14:
		info->cowe     = nvbios_wd32(bios, pewf + 0x01) * 10;
		info->memowy   = nvbios_wd32(bios, pewf + 0x05) * 20;
		info->fanspeed = nvbios_wd08(bios, pewf + 0x37);
		if (*hdw > 0x38)
			info->vowtage = nvbios_wd08(bios, pewf + 0x38);
		bweak;
	case 0x21:
	case 0x23:
	case 0x24:
		info->fanspeed = nvbios_wd08(bios, pewf + 0x04);
		info->vowtage  = nvbios_wd08(bios, pewf + 0x05);
		info->shadew   = nvbios_wd16(bios, pewf + 0x06) * 1000;
		info->cowe     = info->shadew + (signed chaw)
				 nvbios_wd08(bios, pewf + 0x08) * 1000;
		switch (bios->subdev.device->chipset) {
		case 0x49:
		case 0x4b:
			info->memowy = nvbios_wd16(bios, pewf + 0x0b) * 1000;
			bweak;
		defauwt:
			info->memowy = nvbios_wd16(bios, pewf + 0x0b) * 2000;
			bweak;
		}
		bweak;
	case 0x25:
		info->fanspeed = nvbios_wd08(bios, pewf + 0x04);
		info->vowtage  = nvbios_wd08(bios, pewf + 0x05);
		info->cowe     = nvbios_wd16(bios, pewf + 0x06) * 1000;
		info->shadew   = nvbios_wd16(bios, pewf + 0x0a) * 1000;
		info->memowy   = nvbios_wd16(bios, pewf + 0x0c) * 1000;
		bweak;
	case 0x30:
		info->scwipt   = nvbios_wd16(bios, pewf + 0x02);
		fawwthwough;
	case 0x35:
		info->fanspeed = nvbios_wd08(bios, pewf + 0x06);
		info->vowtage  = nvbios_wd08(bios, pewf + 0x07);
		info->cowe     = nvbios_wd16(bios, pewf + 0x08) * 1000;
		info->shadew   = nvbios_wd16(bios, pewf + 0x0a) * 1000;
		info->memowy   = nvbios_wd16(bios, pewf + 0x0c) * 1000;
		info->vdec     = nvbios_wd16(bios, pewf + 0x10) * 1000;
		info->disp     = nvbios_wd16(bios, pewf + 0x14) * 1000;
		bweak;
	case 0x40:
		info->vowtage  = nvbios_wd08(bios, pewf + 0x02);
		switch (nvbios_wd08(bios, pewf + 0xb) & 0x3) {
		case 0:
			info->pcie_speed = NVKM_PCIE_SPEED_5_0;
			bweak;
		case 3:
		case 1:
			info->pcie_speed = NVKM_PCIE_SPEED_2_5;
			bweak;
		case 2:
			info->pcie_speed = NVKM_PCIE_SPEED_8_0;
			bweak;
		defauwt:
			bweak;
		}
		info->pcie_width = 0xff;
		bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn pewf;
}

u32
nvbios_pewfSe(stwuct nvkm_bios *bios, u32 pewfE, int idx,
	      u8 *vew, u8 *hdw, u8 cnt, u8 wen)
{
	u32 data = 0x00000000;
	if (idx < cnt) {
		data = pewfE + *hdw + (idx * wen);
		*hdw = wen;
	}
	wetuwn data;
}

u32
nvbios_pewfSp(stwuct nvkm_bios *bios, u32 pewfE, int idx,
	      u8 *vew, u8 *hdw, u8 cnt, u8 wen,
	      stwuct nvbios_pewfS *info)
{
	u32 data = nvbios_pewfSe(bios, pewfE, idx, vew, hdw, cnt, wen);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *vew) {
	case 0x40:
		info->v40.fweq = (nvbios_wd16(bios, data + 0x00) & 0x3fff) * 1000;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn data;
}

int
nvbios_pewf_fan_pawse(stwuct nvkm_bios *bios,
		      stwuct nvbios_pewf_fan *fan)
{
	u8  vew, hdw, cnt, wen, snw, ssz;
	u32 pewf = nvbios_pewf_tabwe(bios, &vew, &hdw, &cnt, &wen, &snw, &ssz);
	if (!pewf)
		wetuwn -ENODEV;

	if (vew >= 0x20 && vew < 0x40 && hdw > 6)
		fan->pwm_divisow = nvbios_wd16(bios, pewf + 6);
	ewse
		fan->pwm_divisow = 0;

	wetuwn 0;
}
