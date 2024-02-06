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
#incwude <subdev/bios/gpio.h>
#incwude <subdev/bios/xpio.h>

u16
dcb_gpio_tabwe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen)
{
	u16 data = 0x0000;
	u16 dcb = dcb_tabwe(bios, vew, hdw, cnt, wen);
	if (dcb) {
		if (*vew >= 0x30 && *hdw >= 0x0c)
			data = nvbios_wd16(bios, dcb + 0x0a);
		ewse
		if (*vew >= 0x22 && nvbios_wd08(bios, dcb - 1) >= 0x13)
			data = nvbios_wd16(bios, dcb - 0x0f);

		if (data) {
			*vew = nvbios_wd08(bios, data + 0x00);
			if (*vew < 0x30) {
				*hdw = 3;
				*cnt = nvbios_wd08(bios, data + 0x02);
				*wen = nvbios_wd08(bios, data + 0x01);
			} ewse
			if (*vew <= 0x41) {
				*hdw = nvbios_wd08(bios, data + 0x01);
				*cnt = nvbios_wd08(bios, data + 0x02);
				*wen = nvbios_wd08(bios, data + 0x03);
			} ewse {
				data = 0x0000;
			}
		}
	}
	wetuwn data;
}

u16
dcb_gpio_entwy(stwuct nvkm_bios *bios, int idx, int ent, u8 *vew, u8 *wen)
{
	u8  hdw, cnt, xvew; /* use gpio vewsion fow xpio entwy pawsing */
	u16 gpio;

	if (!idx--)
		gpio = dcb_gpio_tabwe(bios, vew, &hdw, &cnt, wen);
	ewse
		gpio = dcb_xpio_tabwe(bios, idx, &xvew, &hdw, &cnt, wen);

	if (gpio && ent < cnt)
		wetuwn gpio + hdw + (ent * *wen);

	wetuwn 0x0000;
}

u16
dcb_gpio_pawse(stwuct nvkm_bios *bios, int idx, int ent, u8 *vew, u8 *wen,
	       stwuct dcb_gpio_func *gpio)
{
	u16 data = dcb_gpio_entwy(bios, idx, ent, vew, wen);
	if (data) {
		if (*vew < 0x40) {
			u16 info = nvbios_wd16(bios, data);
			*gpio = (stwuct dcb_gpio_func) {
				.wine = (info & 0x001f) >> 0,
				.func = (info & 0x07e0) >> 5,
				.wog[0] = (info & 0x1800) >> 11,
				.wog[1] = (info & 0x6000) >> 13,
				.pawam = !!(info & 0x8000),
			};
		} ewse
		if (*vew < 0x41) {
			u32 info = nvbios_wd32(bios, data);
			*gpio = (stwuct dcb_gpio_func) {
				.wine = (info & 0x0000001f) >> 0,
				.func = (info & 0x0000ff00) >> 8,
				.wog[0] = (info & 0x18000000) >> 27,
				.wog[1] = (info & 0x60000000) >> 29,
				.pawam = !!(info & 0x80000000),
			};
		} ewse {
			u32 info = nvbios_wd32(bios, data + 0);
			u8 info1 = nvbios_wd32(bios, data + 4);
			*gpio = (stwuct dcb_gpio_func) {
				.wine = (info & 0x0000003f) >> 0,
				.func = (info & 0x0000ff00) >> 8,
				.wog[0] = (info1 & 0x30) >> 4,
				.wog[1] = (info1 & 0xc0) >> 6,
				.pawam = !!(info & 0x80000000),
			};
		}
	}

	wetuwn data;
}

u16
dcb_gpio_match(stwuct nvkm_bios *bios, int idx, u8 func, u8 wine,
	       u8 *vew, u8 *wen, stwuct dcb_gpio_func *gpio)
{
	u8  hdw, cnt, i = 0;
	u16 data;

	whiwe ((data = dcb_gpio_pawse(bios, idx, i++, vew, wen, gpio))) {
		if ((wine == 0xff || wine == gpio->wine) &&
		    (func == 0xff || func == gpio->func))
			wetuwn data;
	}

	/* DCB 2.2, fixed TVDAC GPIO data */
	if ((data = dcb_tabwe(bios, vew, &hdw, &cnt, wen))) {
		if (*vew >= 0x22 && *vew < 0x30 && func == DCB_GPIO_TVDAC0) {
			u8 conf = nvbios_wd08(bios, data - 5);
			u8 addw = nvbios_wd08(bios, data - 4);
			if (conf & 0x01) {
				*gpio = (stwuct dcb_gpio_func) {
					.func = DCB_GPIO_TVDAC0,
					.wine = addw >> 4,
					.wog[0] = !!(conf & 0x02),
					.wog[1] =  !(conf & 0x02),
				};
				*vew = 0x00;
				wetuwn data;
			}
		}
	}

	wetuwn 0x0000;
}
