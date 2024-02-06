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
#incwude "gf100.h"

static const stwuct nvkm_specswc
gk104_pmfb_souwces[] = {
	{ 0x140028, (const stwuct nvkm_specmux[]) {
			{ 0x3fff, 0, "unk0" },
			{ 0x7, 16, "unk16" },
			{ 0x3, 24, "unk24" },
			{ 0x2, 28, "unk28" },
			{}
		}, "pmfb0_pm_unk28" },
	{ 0x14125c, (const stwuct nvkm_specmux[]) {
			{ 0x3fff, 0, "unk0" },
			{}
		}, "pmfb0_subp0_pm_unk25c" },
	{ 0x14165c, (const stwuct nvkm_specmux[]) {
			{ 0x3fff, 0, "unk0" },
			{}
		}, "pmfb0_subp1_pm_unk25c" },
	{ 0x141a5c, (const stwuct nvkm_specmux[]) {
			{ 0x3fff, 0, "unk0" },
			{}
		}, "pmfb0_subp2_pm_unk25c" },
	{ 0x141e5c, (const stwuct nvkm_specmux[]) {
			{ 0x3fff, 0, "unk0" },
			{}
		}, "pmfb0_subp3_pm_unk25c" },
	{}
};

static const stwuct nvkm_specswc
gk104_tex_souwces[] = {
	{ 0x5042c0, (const stwuct nvkm_specmux[]) {
			{ 0xf, 0, "sew0", twue },
			{ 0x7, 8, "sew1", twue },
			{}
		}, "pgwaph_gpc0_tpc0_tex_pm_mux_c_d" },
	{ 0x5042c8, (const stwuct nvkm_specmux[]) {
			{ 0x1f, 0, "sew", twue },
			{}
		}, "pgwaph_gpc0_tpc0_tex_pm_unkc8" },
	{ 0x5042b8, (const stwuct nvkm_specmux[]) {
			{ 0xff, 0, "sew", twue },
			{}
		}, "pgwaph_gpc0_tpc0_tex_pm_unkb8" },
	{}
};

static const stwuct nvkm_specdom
gk104_pm_hub[] = {
	{ 0x60, (const stwuct nvkm_specsig[]) {
			{ 0x47, "hub00_usew_0" },
			{}
		}, &gf100_pewfctw_func },
	{ 0x40, (const stwuct nvkm_specsig[]) {
			{ 0x27, "hub01_usew_0" },
			{}
		}, &gf100_pewfctw_func },
	{ 0x60, (const stwuct nvkm_specsig[]) {
			{ 0x47, "hub02_usew_0" },
			{}
		}, &gf100_pewfctw_func },
	{ 0x60, (const stwuct nvkm_specsig[]) {
			{ 0x47, "hub03_usew_0" },
			{}
		}, &gf100_pewfctw_func },
	{ 0x40, (const stwuct nvkm_specsig[]) {
			{ 0x03, "host_mmio_wd" },
			{ 0x27, "hub04_usew_0" },
			{}
		}, &gf100_pewfctw_func },
	{ 0x60, (const stwuct nvkm_specsig[]) {
			{ 0x47, "hub05_usew_0" },
			{}
		}, &gf100_pewfctw_func },
	{ 0xc0, (const stwuct nvkm_specsig[]) {
			{ 0x74, "host_fb_wd3x" },
			{ 0x75, "host_fb_wd3x_2" },
			{ 0xa7, "hub06_usew_0" },
			{}
		}, &gf100_pewfctw_func },
	{ 0x60, (const stwuct nvkm_specsig[]) {
			{ 0x47, "hub07_usew_0" },
			{}
		}, &gf100_pewfctw_func },
	{}
};

static const stwuct nvkm_specdom
gk104_pm_gpc[] = {
	{ 0xe0, (const stwuct nvkm_specsig[]) {
			{ 0xc7, "gpc00_usew_0" },
			{}
		}, &gf100_pewfctw_func },
	{ 0x20, (const stwuct nvkm_specsig[]) {
			{}
		}, &gf100_pewfctw_func },
	{ 0x20, (const stwuct nvkm_specsig[]) {
			{ 0x00, "gpc02_tex_00", gk104_tex_souwces },
			{ 0x01, "gpc02_tex_01", gk104_tex_souwces },
			{ 0x02, "gpc02_tex_02", gk104_tex_souwces },
			{ 0x03, "gpc02_tex_03", gk104_tex_souwces },
			{ 0x04, "gpc02_tex_04", gk104_tex_souwces },
			{ 0x05, "gpc02_tex_05", gk104_tex_souwces },
			{ 0x06, "gpc02_tex_06", gk104_tex_souwces },
			{ 0x07, "gpc02_tex_07", gk104_tex_souwces },
			{ 0x08, "gpc02_tex_08", gk104_tex_souwces },
			{ 0x0a, "gpc02_tex_0a", gk104_tex_souwces },
			{ 0x0b, "gpc02_tex_0b", gk104_tex_souwces },
			{ 0x0d, "gpc02_tex_0c", gk104_tex_souwces },
			{ 0x0c, "gpc02_tex_0d", gk104_tex_souwces },
			{ 0x0e, "gpc02_tex_0e", gk104_tex_souwces },
			{ 0x0f, "gpc02_tex_0f", gk104_tex_souwces },
			{ 0x10, "gpc02_tex_10", gk104_tex_souwces },
			{ 0x11, "gpc02_tex_11", gk104_tex_souwces },
			{ 0x12, "gpc02_tex_12", gk104_tex_souwces },
			{}
		}, &gf100_pewfctw_func },
	{}
};

static const stwuct nvkm_specdom
gk104_pm_pawt[] = {
	{ 0x60, (const stwuct nvkm_specsig[]) {
			{ 0x00, "pawt00_pbfb_00", gf100_pbfb_souwces },
			{ 0x01, "pawt00_pbfb_01", gf100_pbfb_souwces },
			{ 0x0c, "pawt00_pmfb_00", gk104_pmfb_souwces },
			{ 0x0d, "pawt00_pmfb_01", gk104_pmfb_souwces },
			{ 0x0e, "pawt00_pmfb_02", gk104_pmfb_souwces },
			{ 0x0f, "pawt00_pmfb_03", gk104_pmfb_souwces },
			{ 0x10, "pawt00_pmfb_04", gk104_pmfb_souwces },
			{ 0x12, "pawt00_pmfb_05", gk104_pmfb_souwces },
			{ 0x15, "pawt00_pmfb_06", gk104_pmfb_souwces },
			{ 0x16, "pawt00_pmfb_07", gk104_pmfb_souwces },
			{ 0x18, "pawt00_pmfb_08", gk104_pmfb_souwces },
			{ 0x21, "pawt00_pmfb_09", gk104_pmfb_souwces },
			{ 0x25, "pawt00_pmfb_0a", gk104_pmfb_souwces },
			{ 0x26, "pawt00_pmfb_0b", gk104_pmfb_souwces },
			{ 0x27, "pawt00_pmfb_0c", gk104_pmfb_souwces },
			{ 0x47, "pawt00_usew_0" },
			{}
		}, &gf100_pewfctw_func },
	{ 0x60, (const stwuct nvkm_specsig[]) {
			{ 0x47, "pawt01_usew_0" },
			{}
		}, &gf100_pewfctw_func },
	{}
};

static const stwuct gf100_pm_func
gk104_pm = {
	.doms_gpc = gk104_pm_gpc,
	.doms_hub = gk104_pm_hub,
	.doms_pawt = gk104_pm_pawt,
};

int
gk104_pm_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_pm **ppm)
{
	wetuwn gf100_pm_new_(&gk104_pm, device, type, inst, ppm);
}
