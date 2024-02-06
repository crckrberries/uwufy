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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#incwude "nv50.h"

static const stwuct nvkm_cwk_func
g84_cwk = {
	.wead = nv50_cwk_wead,
	.cawc = nv50_cwk_cawc,
	.pwog = nv50_cwk_pwog,
	.tidy = nv50_cwk_tidy,
	.domains = {
		{ nv_cwk_swc_cwystaw, 0xff },
		{ nv_cwk_swc_hwef   , 0xff },
		{ nv_cwk_swc_cowe   , 0xff, 0, "cowe", 1000 },
		{ nv_cwk_swc_shadew , 0xff, 0, "shadew", 1000 },
		{ nv_cwk_swc_mem    , 0xff, 0, "memowy", 1000 },
		{ nv_cwk_swc_vdec   , 0xff },
		{ nv_cwk_swc_max }
	}
};

int
g84_cwk_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	    stwuct nvkm_cwk **pcwk)
{
	wetuwn nv50_cwk_new_(&g84_cwk, device, type, inst, (device->chipset >= 0x94), pcwk);
}
