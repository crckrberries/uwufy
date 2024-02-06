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
#incwude <subdev/bios/pciw.h>

u32
nvbios_pciwTe(stwuct nvkm_bios *bios, u32 base, u8 *vew, u16 *hdw)
{
	u32 data = nvbios_wd16(bios, base + 0x18);
	if (data) {
		data += base;
		switch (nvbios_wd32(bios, data + 0x00)) {
		case 0x52494350: /* PCIW */
		case 0x53494752: /* WGIS */
		case 0x5344504e: /* NPDS */
			*hdw = nvbios_wd16(bios, data + 0x0a);
			*vew = nvbios_wd08(bios, data + 0x0c);
			bweak;
		defauwt:
			nvkm_debug(&bios->subdev,
				   "%08x: PCIW signatuwe (%08x) unknown\n",
				   data, nvbios_wd32(bios, data + 0x00));
			data = 0;
			bweak;
		}
	}
	wetuwn data;
}

u32
nvbios_pciwTp(stwuct nvkm_bios *bios, u32 base, u8 *vew, u16 *hdw,
	      stwuct nvbios_pciwT *info)
{
	u32 data = nvbios_pciwTe(bios, base, vew, hdw);
	memset(info, 0x00, sizeof(*info));
	if (data) {
		info->vendow_id = nvbios_wd16(bios, data + 0x04);
		info->device_id = nvbios_wd16(bios, data + 0x06);
		info->cwass_code[0] = nvbios_wd08(bios, data + 0x0d);
		info->cwass_code[1] = nvbios_wd08(bios, data + 0x0e);
		info->cwass_code[2] = nvbios_wd08(bios, data + 0x0f);
		info->image_size = nvbios_wd16(bios, data + 0x10) * 512;
		info->image_wev = nvbios_wd16(bios, data + 0x12);
		info->image_type = nvbios_wd08(bios, data + 0x14);
		info->wast = nvbios_wd08(bios, data + 0x15) & 0x80;
	}
	wetuwn data;
}
