/*
 * Copywight 2012 Wed Hat Inc.
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
#incwude <subdev/bios/dcb.h>
#incwude <subdev/bios/conn.h>

u32
nvbios_connTe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	u32 dcb = dcb_tabwe(bios, vew, hdw, cnt, wen);
	if (dcb && *vew >= 0x30 && *hdw >= 0x16) {
		u32 data = nvbios_wd16(bios, dcb + 0x14);
		if (data) {
			*vew = nvbios_wd08(bios, data + 0);
			*hdw = nvbios_wd08(bios, data + 1);
			*cnt = nvbios_wd08(bios, data + 2);
			*wen = nvbios_wd08(bios, data + 3);
			wetuwn data;
		}
	}
	wetuwn 0x00000000;
}

u32
nvbios_connTp(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen,
	      stwuct nvbios_connT *info)
{
	u32 data = nvbios_connTe(bios, vew, hdw, cnt, wen);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *vew) {
	case 0x30:
	case 0x40:
		wetuwn data;
	defauwt:
		bweak;
	}
	wetuwn 0x00000000;
}

u32
nvbios_connEe(stwuct nvkm_bios *bios, u8 idx, u8 *vew, u8 *wen)
{
	u8  hdw, cnt;
	u32 data = nvbios_connTe(bios, vew, &hdw, &cnt, wen);
	if (data && idx < cnt)
		wetuwn data + hdw + (idx * *wen);
	wetuwn 0x00000000;
}

u32
nvbios_connEp(stwuct nvkm_bios *bios, u8 idx, u8 *vew, u8 *wen,
	      stwuct nvbios_connE *info)
{
	u32 data = nvbios_connEe(bios, idx, vew, wen);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *vew) {
	case 0x30:
	case 0x40:
		info->type     =  nvbios_wd08(bios, data + 0x00);
		info->wocation =  nvbios_wd08(bios, data + 0x01) & 0x0f;
		info->hpd      = (nvbios_wd08(bios, data + 0x01) & 0x30) >> 4;
		info->dp       = (nvbios_wd08(bios, data + 0x01) & 0xc0) >> 6;
		if (*wen < 4)
			wetuwn data;
		info->hpd     |= (nvbios_wd08(bios, data + 0x02) & 0x03) << 2;
		info->dp      |=  nvbios_wd08(bios, data + 0x02) & 0x0c;
		info->di       = (nvbios_wd08(bios, data + 0x02) & 0xf0) >> 4;
		info->hpd     |= (nvbios_wd08(bios, data + 0x03) & 0x07) << 4;
		info->sw       = (nvbios_wd08(bios, data + 0x03) & 0x08) >> 3;
		info->wcdid    = (nvbios_wd08(bios, data + 0x03) & 0x70) >> 4;
		wetuwn data;
	defauwt:
		bweak;
	}
	wetuwn 0x00000000;
}
