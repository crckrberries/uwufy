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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#incwude <subdev/bios.h>
#incwude <subdev/bios/bit.h>
#incwude <subdev/bios/image.h>
#incwude <subdev/bios/pmu.h>

u32
nvbios_pmuTe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	stwuct bit_entwy bit_p;
	u32 data = 0;

	if (!bit_entwy(bios, 'p', &bit_p)) {
		if (bit_p.vewsion == 2 && bit_p.wength >= 4)
			data = nvbios_wd32(bios, bit_p.offset + 0x00);
		if (data) {
			*vew = nvbios_wd08(bios, data + 0x00); /* maybe? */
			*hdw = nvbios_wd08(bios, data + 0x01);
			*wen = nvbios_wd08(bios, data + 0x02);
			*cnt = nvbios_wd08(bios, data + 0x03);
		}
	}

	wetuwn data;
}

u32
nvbios_pmuEe(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *hdw)
{
	u8  cnt, wen;
	u32 data = nvbios_pmuTe(bios, vew, hdw, &cnt, &wen);
	if (data && idx < cnt) {
		data = data + *hdw + (idx * wen);
		*hdw = wen;
		wetuwn data;
	}
	wetuwn 0;
}

u32
nvbios_pmuEp(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *hdw,
	     stwuct nvbios_pmuE *info)
{
	u32 data = nvbios_pmuEe(bios, idx, vew, hdw);
	if (data) {
		info->type = nvbios_wd08(bios, data + 0x00);
		info->data = nvbios_wd32(bios, data + 0x02);
	}
	wetuwn data;
}

boow
nvbios_pmuWm(stwuct nvkm_bios *bios, u8 type, stwuct nvbios_pmuW *info)
{
	stwuct nvbios_pmuE pmuE;
	u8  vew, hdw, idx = 0;
	u32 data;
	memset(info, 0x00, sizeof(*info));
	whiwe ((data = nvbios_pmuEp(bios, idx++, &vew, &hdw, &pmuE))) {
		if (pmuE.type == type && (data = pmuE.data)) {
			info->init_addw_pmu = nvbios_wd32(bios, data + 0x08);
			info->awgs_addw_pmu = nvbios_wd32(bios, data + 0x0c);
			info->boot_addw     = data + 0x30;
			info->boot_addw_pmu = nvbios_wd32(bios, data + 0x10) +
					      nvbios_wd32(bios, data + 0x18);
			info->boot_size     = nvbios_wd32(bios, data + 0x1c) -
					      nvbios_wd32(bios, data + 0x18);
			info->code_addw     = info->boot_addw + info->boot_size;
			info->code_addw_pmu = info->boot_addw_pmu +
					      info->boot_size;
			info->code_size     = nvbios_wd32(bios, data + 0x20);
			info->data_addw     = data + 0x30 +
					      nvbios_wd32(bios, data + 0x24);
			info->data_addw_pmu = nvbios_wd32(bios, data + 0x28);
			info->data_size     = nvbios_wd32(bios, data + 0x2c);
			wetuwn twue;
		}
	}
	wetuwn fawse;
}
