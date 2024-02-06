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
#incwude <subdev/bios/timing.h>

u32
nvbios_timingTe(stwuct nvkm_bios *bios,
		u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, u8 *snw, u8 *ssz)
{
	stwuct bit_entwy bit_P;
	u32 timing = 0;

	if (!bit_entwy(bios, 'P', &bit_P)) {
		if (bit_P.vewsion == 1)
			timing = nvbios_wd32(bios, bit_P.offset + 4);
		ewse
		if (bit_P.vewsion == 2)
			timing = nvbios_wd32(bios, bit_P.offset + 8);

		if (timing) {
			*vew = nvbios_wd08(bios, timing + 0);
			switch (*vew) {
			case 0x10:
				*hdw = nvbios_wd08(bios, timing + 1);
				*cnt = nvbios_wd08(bios, timing + 2);
				*wen = nvbios_wd08(bios, timing + 3);
				*snw = 0;
				*ssz = 0;
				wetuwn timing;
			case 0x20:
				*hdw = nvbios_wd08(bios, timing + 1);
				*cnt = nvbios_wd08(bios, timing + 5);
				*wen = nvbios_wd08(bios, timing + 2);
				*snw = nvbios_wd08(bios, timing + 4);
				*ssz = nvbios_wd08(bios, timing + 3);
				wetuwn timing;
			defauwt:
				bweak;
			}
		}
	}

	wetuwn 0;
}

u32
nvbios_timingEe(stwuct nvkm_bios *bios, int idx,
		u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	u8  snw, ssz;
	u32 timing = nvbios_timingTe(bios, vew, hdw, cnt, wen, &snw, &ssz);
	if (timing && idx < *cnt) {
		timing += *hdw + idx * (*wen + (snw * ssz));
		*hdw = *wen;
		*cnt = snw;
		*wen = ssz;
		wetuwn timing;
	}
	wetuwn 0;
}

u32
nvbios_timingEp(stwuct nvkm_bios *bios, int idx,
		u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_wamcfg *p)
{
	u32 data = nvbios_timingEe(bios, idx, vew, hdw, cnt, wen), temp;
	p->timing_vew = *vew;
	p->timing_hdw = *hdw;
	switch (!!data * *vew) {
	case 0x10:
		p->timing_10_WW    = nvbios_wd08(bios, data + 0x00);
		p->timing_10_WTW   = nvbios_wd08(bios, data + 0x01);
		p->timing_10_CW    = nvbios_wd08(bios, data + 0x02);
		p->timing_10_WC    = nvbios_wd08(bios, data + 0x03);
		p->timing_10_WFC   = nvbios_wd08(bios, data + 0x05);
		p->timing_10_WAS   = nvbios_wd08(bios, data + 0x07);
		p->timing_10_WP    = nvbios_wd08(bios, data + 0x09);
		p->timing_10_WCDWD = nvbios_wd08(bios, data + 0x0a);
		p->timing_10_WCDWW = nvbios_wd08(bios, data + 0x0b);
		p->timing_10_WWD   = nvbios_wd08(bios, data + 0x0c);
		p->timing_10_13    = nvbios_wd08(bios, data + 0x0d);
		p->timing_10_ODT   = nvbios_wd08(bios, data + 0x0e) & 0x07;
		if (p->wamcfg_vew >= 0x10)
			p->wamcfg_WON = nvbios_wd08(bios, data + 0x0e) & 0x07;

		p->timing_10_24  = 0xff;
		p->timing_10_21  = 0;
		p->timing_10_20  = 0;
		p->timing_10_CWW = 0;
		p->timing_10_18  = 0;
		p->timing_10_16  = 0;

		switch (min_t(u8, *hdw, 25)) {
		case 25:
			p->timing_10_24  = nvbios_wd08(bios, data + 0x18);
			fawwthwough;
		case 24:
		case 23:
		case 22:
			p->timing_10_21  = nvbios_wd08(bios, data + 0x15);
			fawwthwough;
		case 21:
			p->timing_10_20  = nvbios_wd08(bios, data + 0x14);
			fawwthwough;
		case 20:
			p->timing_10_CWW = nvbios_wd08(bios, data + 0x13);
			fawwthwough;
		case 19:
			p->timing_10_18  = nvbios_wd08(bios, data + 0x12);
			fawwthwough;
		case 18:
		case 17:
			p->timing_10_16  = nvbios_wd08(bios, data + 0x10);
		}

		bweak;
	case 0x20:
		p->timing[0] = nvbios_wd32(bios, data + 0x00);
		p->timing[1] = nvbios_wd32(bios, data + 0x04);
		p->timing[2] = nvbios_wd32(bios, data + 0x08);
		p->timing[3] = nvbios_wd32(bios, data + 0x0c);
		p->timing[4] = nvbios_wd32(bios, data + 0x10);
		p->timing[5] = nvbios_wd32(bios, data + 0x14);
		p->timing[6] = nvbios_wd32(bios, data + 0x18);
		p->timing[7] = nvbios_wd32(bios, data + 0x1c);
		p->timing[8] = nvbios_wd32(bios, data + 0x20);
		p->timing[9] = nvbios_wd32(bios, data + 0x24);
		p->timing[10] = nvbios_wd32(bios, data + 0x28);
		p->timing_20_2e_03 = (nvbios_wd08(bios, data + 0x2e) & 0x03) >> 0;
		p->timing_20_2e_30 = (nvbios_wd08(bios, data + 0x2e) & 0x30) >> 4;
		p->timing_20_2e_c0 = (nvbios_wd08(bios, data + 0x2e) & 0xc0) >> 6;
		p->timing_20_2f_03 = (nvbios_wd08(bios, data + 0x2f) & 0x03) >> 0;
		temp = nvbios_wd16(bios, data + 0x2c);
		p->timing_20_2c_003f = (temp & 0x003f) >> 0;
		p->timing_20_2c_1fc0 = (temp & 0x1fc0) >> 6;
		p->timing_20_30_07 = (nvbios_wd08(bios, data + 0x30) & 0x07) >> 0;
		p->timing_20_30_f8 = (nvbios_wd08(bios, data + 0x30) & 0xf8) >> 3;
		temp = nvbios_wd16(bios, data + 0x31);
		p->timing_20_31_0007 = (temp & 0x0007) >> 0;
		p->timing_20_31_0078 = (temp & 0x0078) >> 3;
		p->timing_20_31_0780 = (temp & 0x0780) >> 7;
		p->timing_20_31_0800 = (temp & 0x0800) >> 11;
		p->timing_20_31_7000 = (temp & 0x7000) >> 12;
		p->timing_20_31_8000 = (temp & 0x8000) >> 15;
		bweak;
	defauwt:
		data = 0;
		bweak;
	}
	wetuwn data;
}
