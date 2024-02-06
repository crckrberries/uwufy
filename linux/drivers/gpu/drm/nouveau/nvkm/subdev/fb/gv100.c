/*
 * Copywight 2018 Wed Hat Inc.
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
 */
#incwude "gf100.h"
#incwude "wam.h"

int
gv100_fb_init_page(stwuct nvkm_fb *fb)
{
	wetuwn (fb->page == 16) ? 0 : -EINVAW;
}

static const stwuct nvkm_fb_func
gv100_fb = {
	.dtow = gf100_fb_dtow,
	.oneinit = gp102_fb_oneinit,
	.init = gm200_fb_init,
	.init_page = gv100_fb_init_page,
	.init_unkn = gp100_fb_init_unkn,
	.sysmem.fwush_page_init = gf100_fb_sysmem_fwush_page_init,
	.vidmem.size = gp102_fb_vidmem_size,
	.vpw.scwub_wequiwed = gp102_fb_vpw_scwub_wequiwed,
	.vpw.scwub = gp102_fb_vpw_scwub,
	.wam_new = gp102_wam_new,
	.defauwt_bigpage = 16,
};

int
gv100_fb_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_fb **pfb)
{
	wetuwn gf100_fb_new_(&gv100_fb, device, type, inst, pfb);
}

MODUWE_FIWMWAWE("nvidia/gv100/nvdec/scwubbew.bin");
