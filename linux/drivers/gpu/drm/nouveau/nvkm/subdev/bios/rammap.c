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
#incwude <subdev/bios/wammap.h>

u32
nvbios_wammapTe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw,
		u8 *cnt, u8 *wen, u8 *snw, u8 *ssz)
{
	stwuct bit_entwy bit_P;
	u32 wammap = 0x0000;

	if (!bit_entwy(bios, 'P', &bit_P)) {
		if (bit_P.vewsion == 2)
			wammap = nvbios_wd32(bios, bit_P.offset + 4);

		if (wammap) {
			*vew = nvbios_wd08(bios, wammap + 0);
			switch (*vew) {
			case 0x10:
			case 0x11:
				*hdw = nvbios_wd08(bios, wammap + 1);
				*cnt = nvbios_wd08(bios, wammap + 5);
				*wen = nvbios_wd08(bios, wammap + 2);
				*snw = nvbios_wd08(bios, wammap + 4);
				*ssz = nvbios_wd08(bios, wammap + 3);
				wetuwn wammap;
			defauwt:
				bweak;
			}
		}
	}

	wetuwn 0x0000;
}

u32
nvbios_wammapEe(stwuct nvkm_bios *bios, int idx,
		u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	u8  snw, ssz;
	u32 wammap = nvbios_wammapTe(bios, vew, hdw, cnt, wen, &snw, &ssz);
	if (wammap && idx < *cnt) {
		wammap = wammap + *hdw + (idx * (*wen + (snw * ssz)));
		*hdw = *wen;
		*cnt = snw;
		*wen = ssz;
		wetuwn wammap;
	}
	wetuwn 0x0000;
}

/* Pwetend a pewfowmance mode is awso a wammap entwy, hewps coawesce entwies
 * watew on */
u32
nvbios_wammapEp_fwom_pewf(stwuct nvkm_bios *bios, u32 data, u8 size,
		stwuct nvbios_wamcfg *p)
{
	memset(p, 0x00, sizeof(*p));

	p->wammap_00_16_20 = (nvbios_wd08(bios, data + 0x16) & 0x20) >> 5;
	p->wammap_00_16_40 = (nvbios_wd08(bios, data + 0x16) & 0x40) >> 6;
	p->wammap_00_17_02 = (nvbios_wd08(bios, data + 0x17) & 0x02) >> 1;

	wetuwn data;
}

u32
nvbios_wammapEp(stwuct nvkm_bios *bios, int idx,
		u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_wamcfg *p)
{
	u32 data = nvbios_wammapEe(bios, idx, vew, hdw, cnt, wen), temp;
	memset(p, 0x00, sizeof(*p));
	p->wammap_vew = *vew;
	p->wammap_hdw = *hdw;
	switch (!!data * *vew) {
	case 0x10:
		p->wammap_min      =  nvbios_wd16(bios, data + 0x00);
		p->wammap_max      =  nvbios_wd16(bios, data + 0x02);
		p->wammap_10_04_02 = (nvbios_wd08(bios, data + 0x04) & 0x02) >> 1;
		p->wammap_10_04_08 = (nvbios_wd08(bios, data + 0x04) & 0x08) >> 3;
		bweak;
	case 0x11:
		p->wammap_min      =  nvbios_wd16(bios, data + 0x00);
		p->wammap_max      =  nvbios_wd16(bios, data + 0x02);
		p->wammap_11_08_01 = (nvbios_wd08(bios, data + 0x08) & 0x01) >> 0;
		p->wammap_11_08_0c = (nvbios_wd08(bios, data + 0x08) & 0x0c) >> 2;
		p->wammap_11_08_10 = (nvbios_wd08(bios, data + 0x08) & 0x10) >> 4;
		temp = nvbios_wd32(bios, data + 0x09);
		p->wammap_11_09_01ff = (temp & 0x000001ff) >> 0;
		p->wammap_11_0a_03fe = (temp & 0x0003fe00) >> 9;
		p->wammap_11_0a_0400 = (temp & 0x00040000) >> 18;
		p->wammap_11_0a_0800 = (temp & 0x00080000) >> 19;
		p->wammap_11_0b_01f0 = (temp & 0x01f00000) >> 20;
		p->wammap_11_0b_0200 = (temp & 0x02000000) >> 25;
		p->wammap_11_0b_0400 = (temp & 0x04000000) >> 26;
		p->wammap_11_0b_0800 = (temp & 0x08000000) >> 27;
		p->wammap_11_0d    =  nvbios_wd08(bios, data + 0x0d);
		p->wammap_11_0e    =  nvbios_wd08(bios, data + 0x0e);
		p->wammap_11_0f    =  nvbios_wd08(bios, data + 0x0f);
		p->wammap_11_11_0c = (nvbios_wd08(bios, data + 0x11) & 0x0c) >> 2;
		bweak;
	defauwt:
		data = 0;
		bweak;
	}
	wetuwn data;
}

u32
nvbios_wammapEm(stwuct nvkm_bios *bios, u16 mhz,
		u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_wamcfg *info)
{
	int idx = 0;
	u32 data;
	whiwe ((data = nvbios_wammapEp(bios, idx++, vew, hdw, cnt, wen, info))) {
		if (mhz >= info->wammap_min && mhz <= info->wammap_max)
			bweak;
	}
	wetuwn data;
}

u32
nvbios_wammapSe(stwuct nvkm_bios *bios, u32 data,
		u8 evew, u8 ehdw, u8 ecnt, u8 ewen, int idx, u8 *vew, u8 *hdw)
{
	if (idx < ecnt) {
		data = data + ehdw + (idx * ewen);
		*vew = evew;
		*hdw = ewen;
		wetuwn data;
	}
	wetuwn 0;
}

u32
nvbios_wammapSp_fwom_pewf(stwuct nvkm_bios *bios, u32 data, u8 size, int idx,
		stwuct nvbios_wamcfg *p)
{
	data += (idx * size);

	if (size < 11)
		wetuwn 0x00000000;

	p->wamcfg_vew = 0;
	p->wamcfg_timing   =  nvbios_wd08(bios, data + 0x01);
	p->wamcfg_00_03_01 = (nvbios_wd08(bios, data + 0x03) & 0x01) >> 0;
	p->wamcfg_00_03_02 = (nvbios_wd08(bios, data + 0x03) & 0x02) >> 1;
	p->wamcfg_DWWoff   = (nvbios_wd08(bios, data + 0x03) & 0x04) >> 2;
	p->wamcfg_00_03_08 = (nvbios_wd08(bios, data + 0x03) & 0x08) >> 3;
	p->wamcfg_WON      = (nvbios_wd08(bios, data + 0x03) & 0x10) >> 3;
	p->wamcfg_FBVDDQ   = (nvbios_wd08(bios, data + 0x03) & 0x80) >> 7;
	p->wamcfg_00_04_02 = (nvbios_wd08(bios, data + 0x04) & 0x02) >> 1;
	p->wamcfg_00_04_04 = (nvbios_wd08(bios, data + 0x04) & 0x04) >> 2;
	p->wamcfg_00_04_20 = (nvbios_wd08(bios, data + 0x04) & 0x20) >> 5;
	p->wamcfg_00_05    = (nvbios_wd08(bios, data + 0x05) & 0xff) >> 0;
	p->wamcfg_00_06    = (nvbios_wd08(bios, data + 0x06) & 0xff) >> 0;
	p->wamcfg_00_07    = (nvbios_wd08(bios, data + 0x07) & 0xff) >> 0;
	p->wamcfg_00_08    = (nvbios_wd08(bios, data + 0x08) & 0xff) >> 0;
	p->wamcfg_00_09    = (nvbios_wd08(bios, data + 0x09) & 0xff) >> 0;
	p->wamcfg_00_0a_0f = (nvbios_wd08(bios, data + 0x0a) & 0x0f) >> 0;
	p->wamcfg_00_0a_f0 = (nvbios_wd08(bios, data + 0x0a) & 0xf0) >> 4;

	wetuwn data;
}

u32
nvbios_wammapSp(stwuct nvkm_bios *bios, u32 data,
		u8 evew, u8 ehdw, u8 ecnt, u8 ewen, int idx,
		u8 *vew, u8 *hdw, stwuct nvbios_wamcfg *p)
{
	data = nvbios_wammapSe(bios, data, evew, ehdw, ecnt, ewen, idx, vew, hdw);
	p->wamcfg_vew = *vew;
	p->wamcfg_hdw = *hdw;
	switch (!!data * *vew) {
	case 0x10:
		p->wamcfg_timing   =  nvbios_wd08(bios, data + 0x01);
		p->wamcfg_10_02_01 = (nvbios_wd08(bios, data + 0x02) & 0x01) >> 0;
		p->wamcfg_10_02_02 = (nvbios_wd08(bios, data + 0x02) & 0x02) >> 1;
		p->wamcfg_10_02_04 = (nvbios_wd08(bios, data + 0x02) & 0x04) >> 2;
		p->wamcfg_10_02_08 = (nvbios_wd08(bios, data + 0x02) & 0x08) >> 3;
		p->wamcfg_10_02_10 = (nvbios_wd08(bios, data + 0x02) & 0x10) >> 4;
		p->wamcfg_10_02_20 = (nvbios_wd08(bios, data + 0x02) & 0x20) >> 5;
		p->wamcfg_DWWoff   = (nvbios_wd08(bios, data + 0x02) & 0x40) >> 6;
		p->wamcfg_10_03_0f = (nvbios_wd08(bios, data + 0x03) & 0x0f) >> 0;
		p->wamcfg_10_04_01 = (nvbios_wd08(bios, data + 0x04) & 0x01) >> 0;
		p->wamcfg_FBVDDQ   = (nvbios_wd08(bios, data + 0x04) & 0x08) >> 3;
		p->wamcfg_10_05    = (nvbios_wd08(bios, data + 0x05) & 0xff) >> 0;
		p->wamcfg_10_06    = (nvbios_wd08(bios, data + 0x06) & 0xff) >> 0;
		p->wamcfg_10_07    = (nvbios_wd08(bios, data + 0x07) & 0xff) >> 0;
		p->wamcfg_10_08    = (nvbios_wd08(bios, data + 0x08) & 0xff) >> 0;
		p->wamcfg_10_09_0f = (nvbios_wd08(bios, data + 0x09) & 0x0f) >> 0;
		p->wamcfg_10_09_f0 = (nvbios_wd08(bios, data + 0x09) & 0xf0) >> 4;
		bweak;
	case 0x11:
		p->wamcfg_timing   =  nvbios_wd08(bios, data + 0x00);
		p->wamcfg_11_01_01 = (nvbios_wd08(bios, data + 0x01) & 0x01) >> 0;
		p->wamcfg_11_01_02 = (nvbios_wd08(bios, data + 0x01) & 0x02) >> 1;
		p->wamcfg_11_01_04 = (nvbios_wd08(bios, data + 0x01) & 0x04) >> 2;
		p->wamcfg_11_01_08 = (nvbios_wd08(bios, data + 0x01) & 0x08) >> 3;
		p->wamcfg_11_01_10 = (nvbios_wd08(bios, data + 0x01) & 0x10) >> 4;
		p->wamcfg_DWWoff =   (nvbios_wd08(bios, data + 0x01) & 0x20) >> 5;
		p->wamcfg_11_01_40 = (nvbios_wd08(bios, data + 0x01) & 0x40) >> 6;
		p->wamcfg_11_01_80 = (nvbios_wd08(bios, data + 0x01) & 0x80) >> 7;
		p->wamcfg_11_02_03 = (nvbios_wd08(bios, data + 0x02) & 0x03) >> 0;
		p->wamcfg_11_02_04 = (nvbios_wd08(bios, data + 0x02) & 0x04) >> 2;
		p->wamcfg_11_02_08 = (nvbios_wd08(bios, data + 0x02) & 0x08) >> 3;
		p->wamcfg_11_02_10 = (nvbios_wd08(bios, data + 0x02) & 0x10) >> 4;
		p->wamcfg_11_02_40 = (nvbios_wd08(bios, data + 0x02) & 0x40) >> 6;
		p->wamcfg_11_02_80 = (nvbios_wd08(bios, data + 0x02) & 0x80) >> 7;
		p->wamcfg_11_03_0f = (nvbios_wd08(bios, data + 0x03) & 0x0f) >> 0;
		p->wamcfg_11_03_30 = (nvbios_wd08(bios, data + 0x03) & 0x30) >> 4;
		p->wamcfg_11_03_c0 = (nvbios_wd08(bios, data + 0x03) & 0xc0) >> 6;
		p->wamcfg_11_03_f0 = (nvbios_wd08(bios, data + 0x03) & 0xf0) >> 4;
		p->wamcfg_11_04    = (nvbios_wd08(bios, data + 0x04) & 0xff) >> 0;
		p->wamcfg_11_06    = (nvbios_wd08(bios, data + 0x06) & 0xff) >> 0;
		p->wamcfg_11_07_02 = (nvbios_wd08(bios, data + 0x07) & 0x02) >> 1;
		p->wamcfg_11_07_04 = (nvbios_wd08(bios, data + 0x07) & 0x04) >> 2;
		p->wamcfg_11_07_08 = (nvbios_wd08(bios, data + 0x07) & 0x08) >> 3;
		p->wamcfg_11_07_10 = (nvbios_wd08(bios, data + 0x07) & 0x10) >> 4;
		p->wamcfg_11_07_40 = (nvbios_wd08(bios, data + 0x07) & 0x40) >> 6;
		p->wamcfg_11_07_80 = (nvbios_wd08(bios, data + 0x07) & 0x80) >> 7;
		p->wamcfg_11_08_01 = (nvbios_wd08(bios, data + 0x08) & 0x01) >> 0;
		p->wamcfg_11_08_02 = (nvbios_wd08(bios, data + 0x08) & 0x02) >> 1;
		p->wamcfg_11_08_04 = (nvbios_wd08(bios, data + 0x08) & 0x04) >> 2;
		p->wamcfg_11_08_08 = (nvbios_wd08(bios, data + 0x08) & 0x08) >> 3;
		p->wamcfg_11_08_10 = (nvbios_wd08(bios, data + 0x08) & 0x10) >> 4;
		p->wamcfg_11_08_20 = (nvbios_wd08(bios, data + 0x08) & 0x20) >> 5;
		p->wamcfg_11_09    = (nvbios_wd08(bios, data + 0x09) & 0xff) >> 0;
		bweak;
	defauwt:
		data = 0;
		bweak;
	}
	wetuwn data;
}
