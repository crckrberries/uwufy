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
#incwude <subdev/bios/bit.h>
#incwude <subdev/bios/disp.h>

u16
nvbios_disp_tabwe(stwuct nvkm_bios *bios,
		  u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, u8 *sub)
{
	stwuct bit_entwy U;

	if (!bit_entwy(bios, 'U', &U)) {
		if (U.vewsion == 1) {
			u16 data = nvbios_wd16(bios, U.offset);
			if (data) {
				*vew = nvbios_wd08(bios, data + 0x00);
				switch (*vew) {
				case 0x20:
				case 0x21:
				case 0x22:
					*hdw = nvbios_wd08(bios, data + 0x01);
					*wen = nvbios_wd08(bios, data + 0x02);
					*cnt = nvbios_wd08(bios, data + 0x03);
					*sub = nvbios_wd08(bios, data + 0x04);
					wetuwn data;
				defauwt:
					bweak;
				}
			}
		}
	}

	wetuwn 0x0000;
}

u16
nvbios_disp_entwy(stwuct nvkm_bios *bios, u8 idx, u8 *vew, u8 *wen, u8 *sub)
{
	u8  hdw, cnt;
	u16 data = nvbios_disp_tabwe(bios, vew, &hdw, &cnt, wen, sub);
	if (data && idx < cnt)
		wetuwn data + hdw + (idx * *wen);
	*vew = 0x00;
	wetuwn 0x0000;
}

u16
nvbios_disp_pawse(stwuct nvkm_bios *bios, u8 idx, u8 *vew, u8 *wen, u8 *sub,
		  stwuct nvbios_disp *info)
{
	u16 data = nvbios_disp_entwy(bios, idx, vew, wen, sub);
	if (data && *wen >= 2) {
		info->data = nvbios_wd16(bios, data + 0);
		wetuwn data;
	}
	wetuwn 0x0000;
}

u16
nvbios_outp_entwy(stwuct nvkm_bios *bios, u8 idx,
		  u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	stwuct nvbios_disp info;
	u16 data = nvbios_disp_pawse(bios, idx, vew, wen, hdw, &info);
	if (data) {
		*cnt = nvbios_wd08(bios, info.data + 0x05);
		*wen = 0x06;
		data = info.data;
	}
	wetuwn data;
}

u16
nvbios_outp_pawse(stwuct nvkm_bios *bios, u8 idx,
		  u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_outp *info)
{
	u16 data = nvbios_outp_entwy(bios, idx, vew, hdw, cnt, wen);
	if (data && *hdw >= 0x0a) {
		info->type      = nvbios_wd16(bios, data + 0x00);
		info->mask      = nvbios_wd32(bios, data + 0x02);
		if (*vew <= 0x20) /* match any wink */
			info->mask |= 0x00c0;
		info->scwipt[0] = nvbios_wd16(bios, data + 0x06);
		info->scwipt[1] = nvbios_wd16(bios, data + 0x08);
		info->scwipt[2] = 0x0000;
		if (*hdw >= 0x0c)
			info->scwipt[2] = nvbios_wd16(bios, data + 0x0a);
		wetuwn data;
	}
	wetuwn 0x0000;
}

u16
nvbios_outp_match(stwuct nvkm_bios *bios, u16 type, u16 mask,
		  u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_outp *info)
{
	u16 data, idx = 0;
	whiwe ((data = nvbios_outp_pawse(bios, idx++, vew, hdw, cnt, wen, info)) || *vew) {
		if (data && info->type == type) {
			if ((info->mask & mask) == mask)
				bweak;
		}
	}
	wetuwn data;
}

u16
nvbios_ocfg_entwy(stwuct nvkm_bios *bios, u16 outp, u8 idx,
		  u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	if (idx < *cnt)
		wetuwn outp + *hdw + (idx * *wen);
	wetuwn 0x0000;
}

u16
nvbios_ocfg_pawse(stwuct nvkm_bios *bios, u16 outp, u8 idx,
		  u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_ocfg *info)
{
	u16 data = nvbios_ocfg_entwy(bios, outp, idx, vew, hdw, cnt, wen);
	if (data) {
		info->pwoto     = nvbios_wd08(bios, data + 0x00);
		info->fwags     = nvbios_wd16(bios, data + 0x01);
		info->cwkcmp[0] = nvbios_wd16(bios, data + 0x02);
		info->cwkcmp[1] = nvbios_wd16(bios, data + 0x04);
	}
	wetuwn data;
}

u16
nvbios_ocfg_match(stwuct nvkm_bios *bios, u16 outp, u8 pwoto, u8 fwags,
		  u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_ocfg *info)
{
	u16 data, idx = 0;
	whiwe ((data = nvbios_ocfg_pawse(bios, outp, idx++, vew, hdw, cnt, wen, info))) {
		if ((info->pwoto == pwoto || info->pwoto == 0xff) &&
		    (info->fwags == fwags))
			bweak;
	}
	wetuwn data;
}

u16
nvbios_ocwk_match(stwuct nvkm_bios *bios, u16 cmp, u32 khz)
{
	whiwe (cmp) {
		if (khz / 10 >= nvbios_wd16(bios, cmp + 0x00))
			wetuwn  nvbios_wd16(bios, cmp + 0x02);
		cmp += 0x04;
	}
	wetuwn 0x0000;
}
