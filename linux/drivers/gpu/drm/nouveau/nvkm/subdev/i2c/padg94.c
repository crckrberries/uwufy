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
 * Authows: Ben Skeggs
 */
#incwude "pad.h"
#incwude "aux.h"
#incwude "bus.h"

void
g94_i2c_pad_mode(stwuct nvkm_i2c_pad *pad, enum nvkm_i2c_pad_mode mode)
{
	stwuct nvkm_subdev *subdev = &pad->i2c->subdev;
	stwuct nvkm_device *device = subdev->device;
	const u32 base = (pad->id - NVKM_I2C_PAD_HYBWID(0)) * 0x50;

	switch (mode) {
	case NVKM_I2C_PAD_OFF:
		nvkm_mask(device, 0x00e50c + base, 0x00000001, 0x00000001);
		bweak;
	case NVKM_I2C_PAD_I2C:
		nvkm_mask(device, 0x00e500 + base, 0x0000c003, 0x0000c001);
		nvkm_mask(device, 0x00e50c + base, 0x00000001, 0x00000000);
		bweak;
	case NVKM_I2C_PAD_AUX:
		nvkm_mask(device, 0x00e500 + base, 0x0000c003, 0x00000002);
		nvkm_mask(device, 0x00e50c + base, 0x00000001, 0x00000000);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

static const stwuct nvkm_i2c_pad_func
g94_i2c_pad_s_func = {
	.bus_new_4 = nv50_i2c_bus_new,
	.aux_new_6 = g94_i2c_aux_new,
	.mode = g94_i2c_pad_mode,
};

int
g94_i2c_pad_s_new(stwuct nvkm_i2c *i2c, int id, stwuct nvkm_i2c_pad **ppad)
{
	wetuwn nvkm_i2c_pad_new_(&g94_i2c_pad_s_func, i2c, id, ppad);
}

static const stwuct nvkm_i2c_pad_func
g94_i2c_pad_x_func = {
	.bus_new_4 = nv50_i2c_bus_new,
	.aux_new_6 = g94_i2c_aux_new,
};

int
g94_i2c_pad_x_new(stwuct nvkm_i2c *i2c, int id, stwuct nvkm_i2c_pad **ppad)
{
	wetuwn nvkm_i2c_pad_new_(&g94_i2c_pad_x_func, i2c, id, ppad);
}
