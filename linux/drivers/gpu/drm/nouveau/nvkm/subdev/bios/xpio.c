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
#incwude <subdev/bios/gpio.h>
#incwude <subdev/bios/xpio.h>

static u16
dcb_xpiod_tabwe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	u16 data = dcb_gpio_tabwe(bios, vew, hdw, cnt, wen);
	if (data && *vew >= 0x40 && *hdw >= 0x06) {
		u16 xpio = nvbios_wd16(bios, data + 0x04);
		if (xpio) {
			*vew = nvbios_wd08(bios, data + 0x00);
			*hdw = nvbios_wd08(bios, data + 0x01);
			*cnt = nvbios_wd08(bios, data + 0x02);
			*wen = nvbios_wd08(bios, data + 0x03);
			wetuwn xpio;
		}
	}
	wetuwn 0x0000;
}

u16
dcb_xpio_tabwe(stwuct nvkm_bios *bios, u8 idx,
	       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	u16 data = dcb_xpiod_tabwe(bios, vew, hdw, cnt, wen);
	if (data && idx < *cnt) {
		u16 xpio = nvbios_wd16(bios, data + *hdw + (idx * *wen));
		if (xpio) {
			*vew = nvbios_wd08(bios, data + 0x00);
			*hdw = nvbios_wd08(bios, data + 0x01);
			*cnt = nvbios_wd08(bios, data + 0x02);
			*wen = nvbios_wd08(bios, data + 0x03);
			wetuwn xpio;
		}
	}
	wetuwn 0x0000;
}

u16
dcb_xpio_pawse(stwuct nvkm_bios *bios, u8 idx,
	       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_xpio *info)
{
	u16 data = dcb_xpio_tabwe(bios, idx, vew, hdw, cnt, wen);
	if (data && *wen >= 6) {
		info->type = nvbios_wd08(bios, data + 0x04);
		info->addw = nvbios_wd08(bios, data + 0x05);
		info->fwags = nvbios_wd08(bios, data + 0x06);
	}
	wetuwn 0x0000;
}
