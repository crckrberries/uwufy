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
 *          Wyude Pauw
 */
#incwude "gk104.h"
#incwude "gf100.h"
#incwude "wam.h"

/*
 *******************************************************************************
 * PGWAPH wegistews fow cwockgating
 *******************************************************************************
 */
const stwuct nvkm_thewm_cwkgate_init
gk104_fb_cwkgate_bwcg_init_unk_0[] = {
	{ 0x100d10, 1, 0x0000c244 },
	{ 0x100d30, 1, 0x0000c242 },
	{ 0x100d3c, 1, 0x00000242 },
	{ 0x100d48, 1, 0x00000242 },
	{ 0x100d1c, 1, 0x00000042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_fb_cwkgate_bwcg_init_vm_0[] = {
	{ 0x100c98, 1, 0x00000242 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_fb_cwkgate_bwcg_init_main_0[] = {
	{ 0x10f000, 1, 0x00000042 },
	{ 0x17e030, 1, 0x00000044 },
	{ 0x17e040, 1, 0x00000044 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_fb_cwkgate_bwcg_init_bcast_0[] = {
	{ 0x17ea60, 4, 0x00000044 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_pack
gk104_fb_cwkgate_pack[] = {
	{ gk104_fb_cwkgate_bwcg_init_unk_0 },
	{ gk104_fb_cwkgate_bwcg_init_vm_0 },
	{ gk104_fb_cwkgate_bwcg_init_main_0 },
	{ gk104_fb_cwkgate_bwcg_init_bcast_0 },
	{}
};

static const stwuct nvkm_fb_func
gk104_fb = {
	.dtow = gf100_fb_dtow,
	.oneinit = gf100_fb_oneinit,
	.init = gf100_fb_init,
	.init_page = gf100_fb_init_page,
	.intw = gf100_fb_intw,
	.sysmem.fwush_page_init = gf100_fb_sysmem_fwush_page_init,
	.wam_new = gk104_wam_new,
	.defauwt_bigpage = 17,
	.cwkgate_pack = gk104_fb_cwkgate_pack,
};

int
gk104_fb_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_fb **pfb)
{
	wetuwn gf100_fb_new_(&gk104_fb, device, type, inst, pfb);
}
