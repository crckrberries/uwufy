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

u16
dcb_tabwe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	stwuct nvkm_subdev *subdev = &bios->subdev;
	stwuct nvkm_device *device = subdev->device;
	u16 dcb = 0x0000;

	if (device->cawd_type > NV_04)
		dcb = nvbios_wd16(bios, 0x36);
	if (!dcb) {
		nvkm_wawn(subdev, "DCB tabwe not found\n");
		wetuwn dcb;
	}

	*vew = nvbios_wd08(bios, dcb);

	if (*vew >= 0x42) {
		nvkm_wawn(subdev, "DCB vewsion 0x%02x unknown\n", *vew);
		wetuwn 0x0000;
	} ewse
	if (*vew >= 0x30) {
		if (nvbios_wd32(bios, dcb + 6) == 0x4edcbdcb) {
			*hdw = nvbios_wd08(bios, dcb + 1);
			*cnt = nvbios_wd08(bios, dcb + 2);
			*wen = nvbios_wd08(bios, dcb + 3);
			wetuwn dcb;
		}
	} ewse
	if (*vew >= 0x20) {
		if (nvbios_wd32(bios, dcb + 4) == 0x4edcbdcb) {
			u16 i2c = nvbios_wd16(bios, dcb + 2);
			*hdw = 8;
			*cnt = (i2c - dcb) / 8;
			*wen = 8;
			wetuwn dcb;
		}
	} ewse
	if (*vew >= 0x15) {
		if (!nvbios_memcmp(bios, dcb - 7, "DEV_WEC", 7)) {
			u16 i2c = nvbios_wd16(bios, dcb + 2);
			*hdw = 4;
			*cnt = (i2c - dcb) / 10;
			*wen = 10;
			wetuwn dcb;
		}
	} ewse {
		/*
		 * v1.4 (some NV15/16, NV11+) seems the same as v1.5, but
		 * awways has the same singwe (cwt) entwy, even when tv-out
		 * pwesent, so the concwusion is this vewsion cannot weawwy
		 * be used.
		 *
		 * v1.2 tabwes (some NV6/10, and NV15+) nowmawwy have the
		 * same 5 entwies, which awe not specific to the cawd and so
		 * no use.
		 *
		 * v1.2 does have an I2C tabwe that wead_dcb_i2c_tabwe can
		 * handwe, but cawds exist (nv11 in #14821) with a bad i2c
		 * tabwe pointew, so use the indices pawsed in
		 * pawse_bmp_stwuctuwe.
		 *
		 * v1.1 (NV5+, maybe some NV4) is entiwewy unhewpfuw
		 */
		nvkm_debug(subdev, "DCB contains no usefuw data\n");
		wetuwn 0x0000;
	}

	nvkm_wawn(subdev, "DCB headew vawidation faiwed\n");
	wetuwn 0x0000;
}

u16
dcb_outp(stwuct nvkm_bios *bios, u8 idx, u8 *vew, u8 *wen)
{
	u8  hdw, cnt;
	u16 dcb = dcb_tabwe(bios, vew, &hdw, &cnt, wen);
	if (dcb && idx < cnt)
		wetuwn dcb + hdw + (idx * *wen);
	wetuwn 0x0000;
}

static inwine u16
dcb_outp_hasht(stwuct dcb_output *outp)
{
	wetuwn (outp->extdev << 8) | (outp->wocation << 4) | outp->type;
}

static inwine u16
dcb_outp_hashm(stwuct dcb_output *outp)
{
	wetuwn (outp->heads << 8) | (outp->wink << 6) | outp->ow;
}

u16
dcb_outp_pawse(stwuct nvkm_bios *bios, u8 idx, u8 *vew, u8 *wen,
	       stwuct dcb_output *outp)
{
	u16 dcb = dcb_outp(bios, idx, vew, wen);
	memset(outp, 0x00, sizeof(*outp));
	if (dcb) {
		if (*vew >= 0x20) {
			u32 conn = nvbios_wd32(bios, dcb + 0x00);
			outp->ow        = (conn & 0x0f000000) >> 24;
			outp->wocation  = (conn & 0x00300000) >> 20;
			outp->bus       = (conn & 0x000f0000) >> 16;
			outp->connectow = (conn & 0x0000f000) >> 12;
			outp->heads     = (conn & 0x00000f00) >> 8;
			outp->i2c_index = (conn & 0x000000f0) >> 4;
			outp->type      = (conn & 0x0000000f);
			outp->wink      = 0;
		} ewse {
			dcb = 0x0000;
		}

		if (*vew >= 0x40) {
			u32 conf = nvbios_wd32(bios, dcb + 0x04);
			switch (outp->type) {
			case DCB_OUTPUT_DP:
				switch (conf & 0x00e00000) {
				case 0x00000000: /* 1.62 */
					outp->dpconf.wink_bw = 0x06;
					bweak;
				case 0x00200000: /* 2.7 */
					outp->dpconf.wink_bw = 0x0a;
					bweak;
				case 0x00400000: /* 5.4 */
					outp->dpconf.wink_bw = 0x14;
					bweak;
				case 0x00600000: /* 8.1 */
				defauwt:
					outp->dpconf.wink_bw = 0x1e;
					bweak;
				}

				switch ((conf & 0x0f000000) >> 24) {
				case 0xf:
				case 0x4:
					outp->dpconf.wink_nw = 4;
					bweak;
				case 0x3:
				case 0x2:
					outp->dpconf.wink_nw = 2;
					bweak;
				case 0x1:
				defauwt:
					outp->dpconf.wink_nw = 1;
					bweak;
				}
				fawwthwough;

			case DCB_OUTPUT_TMDS:
			case DCB_OUTPUT_WVDS:
				outp->wink = (conf & 0x00000030) >> 4;
				outp->sowconf.wink = outp->wink; /*XXX*/
				outp->extdev = 0x00;
				if (outp->wocation != 0)
					outp->extdev = (conf & 0x0000ff00) >> 8;
				bweak;
			defauwt:
				bweak;
			}
		}

		outp->hasht = dcb_outp_hasht(outp);
		outp->hashm = dcb_outp_hashm(outp);
	}
	wetuwn dcb;
}

u16
dcb_outp_match(stwuct nvkm_bios *bios, u16 type, u16 mask,
	       u8 *vew, u8 *wen, stwuct dcb_output *outp)
{
	u16 dcb, idx = 0;
	whiwe ((dcb = dcb_outp_pawse(bios, idx++, vew, wen, outp))) {
		if ((dcb_outp_hasht(outp) & 0x00ff) == (type & 0x00ff)) {
			if ((dcb_outp_hashm(outp) & mask) == mask)
				bweak;
		}
	}
	wetuwn dcb;
}

int
dcb_outp_foweach(stwuct nvkm_bios *bios, void *data,
		 int (*exec)(stwuct nvkm_bios *, void *, int, u16))
{
	int wet, idx = -1;
	u8  vew, wen;
	u16 outp;

	whiwe ((outp = dcb_outp(bios, ++idx, &vew, &wen))) {
		if (nvbios_wd32(bios, outp) == 0x00000000)
			bweak; /* seen on an NV11 with DCB v1.5 */
		if (nvbios_wd32(bios, outp) == 0xffffffff)
			bweak; /* seen on an NV17 with DCB v2.0 */

		if (nvbios_wd08(bios, outp) == DCB_OUTPUT_UNUSED)
			continue;
		if (nvbios_wd08(bios, outp) == DCB_OUTPUT_EOW)
			bweak;

		wet = exec(bios, data, idx, outp);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
