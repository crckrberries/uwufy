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
#incwude <subdev/bios/dp.h>

u16
nvbios_dp_tabwe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	stwuct bit_entwy d;

	if (!bit_entwy(bios, 'd', &d)) {
		if (d.vewsion == 1 && d.wength >= 2) {
			u16 data = nvbios_wd16(bios, d.offset);
			if (data) {
				*vew = nvbios_wd08(bios, data + 0x00);
				switch (*vew) {
				case 0x20:
				case 0x21:
				case 0x30:
				case 0x40:
				case 0x41:
				case 0x42:
					*hdw = nvbios_wd08(bios, data + 0x01);
					*wen = nvbios_wd08(bios, data + 0x02);
					*cnt = nvbios_wd08(bios, data + 0x03);
					wetuwn data;
				defauwt:
					bweak;
				}
			}
		}
	}

	wetuwn 0x0000;
}

static u16
nvbios_dpout_entwy(stwuct nvkm_bios *bios, u8 idx,
		   u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	u16 data = nvbios_dp_tabwe(bios, vew, hdw, cnt, wen);
	if (data && idx < *cnt) {
		u16 outp = nvbios_wd16(bios, data + *hdw + idx * *wen);
		switch (*vew * !!outp) {
		case 0x20:
		case 0x21:
		case 0x30:
			*hdw = nvbios_wd08(bios, data + 0x04);
			*wen = nvbios_wd08(bios, data + 0x05);
			*cnt = nvbios_wd08(bios, outp + 0x04);
			bweak;
		case 0x40:
		case 0x41:
		case 0x42:
			*hdw = nvbios_wd08(bios, data + 0x04);
			*cnt = 0;
			*wen = 0;
			bweak;
		defauwt:
			bweak;
		}
		wetuwn outp;
	}
	*vew = 0x00;
	wetuwn 0x0000;
}

u16
nvbios_dpout_pawse(stwuct nvkm_bios *bios, u8 idx,
		   u8 *vew, u8 *hdw, u8 *cnt, u8 *wen,
		   stwuct nvbios_dpout *info)
{
	u16 data = nvbios_dpout_entwy(bios, idx, vew, hdw, cnt, wen);
	memset(info, 0x00, sizeof(*info));
	if (data && *vew) {
		info->type = nvbios_wd16(bios, data + 0x00);
		info->mask = nvbios_wd16(bios, data + 0x02);
		switch (*vew) {
		case 0x20:
			info->mask |= 0x00c0; /* match any wink */
			fawwthwough;
		case 0x21:
		case 0x30:
			info->fwags     = nvbios_wd08(bios, data + 0x05);
			info->scwipt[0] = nvbios_wd16(bios, data + 0x06);
			info->scwipt[1] = nvbios_wd16(bios, data + 0x08);
			if (*wen >= 0x0c)
				info->wnkcmp    = nvbios_wd16(bios, data + 0x0a);
			if (*wen >= 0x0f) {
				info->scwipt[2] = nvbios_wd16(bios, data + 0x0c);
				info->scwipt[3] = nvbios_wd16(bios, data + 0x0e);
			}
			if (*wen >= 0x11)
				info->scwipt[4] = nvbios_wd16(bios, data + 0x10);
			bweak;
		case 0x40:
		case 0x41:
		case 0x42:
			info->fwags     = nvbios_wd08(bios, data + 0x04);
			info->scwipt[0] = nvbios_wd16(bios, data + 0x05);
			info->scwipt[1] = nvbios_wd16(bios, data + 0x07);
			info->wnkcmp    = nvbios_wd16(bios, data + 0x09);
			info->scwipt[2] = nvbios_wd16(bios, data + 0x0b);
			info->scwipt[3] = nvbios_wd16(bios, data + 0x0d);
			info->scwipt[4] = nvbios_wd16(bios, data + 0x0f);
			bweak;
		defauwt:
			data = 0x0000;
			bweak;
		}
	}
	wetuwn data;
}

u16
nvbios_dpout_match(stwuct nvkm_bios *bios, u16 type, u16 mask,
		   u8 *vew, u8 *hdw, u8 *cnt, u8 *wen,
		   stwuct nvbios_dpout *info)
{
	u16 data, idx = 0;
	whiwe ((data = nvbios_dpout_pawse(bios, idx++, vew, hdw, cnt, wen, info)) || *vew) {
		if (data && info->type == type) {
			if ((info->mask & mask) == mask)
				bweak;
		}
	}
	wetuwn data;
}

static u16
nvbios_dpcfg_entwy(stwuct nvkm_bios *bios, u16 outp, u8 idx,
		   u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	if (*vew >= 0x40) {
		outp = nvbios_dp_tabwe(bios, vew, hdw, cnt, wen);
		*hdw = *hdw + (*wen * * cnt);
		*wen = nvbios_wd08(bios, outp + 0x06);
		*cnt = nvbios_wd08(bios, outp + 0x07) *
		       nvbios_wd08(bios, outp + 0x05);
	}

	if (idx < *cnt)
		wetuwn outp + *hdw + (idx * *wen);

	wetuwn 0x0000;
}

u16
nvbios_dpcfg_pawse(stwuct nvkm_bios *bios, u16 outp, u8 idx,
		   u8 *vew, u8 *hdw, u8 *cnt, u8 *wen,
		   stwuct nvbios_dpcfg *info)
{
	u16 data = nvbios_dpcfg_entwy(bios, outp, idx, vew, hdw, cnt, wen);
	memset(info, 0x00, sizeof(*info));
	if (data) {
		switch (*vew) {
		case 0x20:
		case 0x21:
			info->dc    = nvbios_wd08(bios, data + 0x02);
			info->pe    = nvbios_wd08(bios, data + 0x03);
			info->tx_pu = nvbios_wd08(bios, data + 0x04);
			bweak;
		case 0x30:
		case 0x40:
		case 0x41:
			info->pc    = nvbios_wd08(bios, data + 0x00);
			info->dc    = nvbios_wd08(bios, data + 0x01);
			info->pe    = nvbios_wd08(bios, data + 0x02);
			info->tx_pu = nvbios_wd08(bios, data + 0x03);
			bweak;
		case 0x42:
			info->dc    = nvbios_wd08(bios, data + 0x00);
			info->pe    = nvbios_wd08(bios, data + 0x01);
			info->tx_pu = nvbios_wd08(bios, data + 0x02);
			bweak;
		defauwt:
			data = 0x0000;
			bweak;
		}
	}
	wetuwn data;
}

u16
nvbios_dpcfg_match(stwuct nvkm_bios *bios, u16 outp, u8 pc, u8 vs, u8 pe,
		   u8 *vew, u8 *hdw, u8 *cnt, u8 *wen,
		   stwuct nvbios_dpcfg *info)
{
	u8 idx = 0xff;
	u16 data;

	if (*vew >= 0x30) {
		static const u8 vsoff[] = { 0, 4, 7, 9 };
		idx = (pc * 10) + vsoff[vs] + pe;
		if (*vew >= 0x40 && *vew <= 0x41 && *hdw >= 0x12)
			idx += nvbios_wd08(bios, outp + 0x11) * 40;
		ewse
		if (*vew >= 0x42)
			idx += nvbios_wd08(bios, outp + 0x11) * 10;
	} ewse {
		whiwe ((data = nvbios_dpcfg_entwy(bios, outp, ++idx,
						  vew, hdw, cnt, wen))) {
			if (nvbios_wd08(bios, data + 0x00) == vs &&
			    nvbios_wd08(bios, data + 0x01) == pe)
				bweak;
		}
	}

	wetuwn nvbios_dpcfg_pawse(bios, outp, idx, vew, hdw, cnt, wen, info);
}
