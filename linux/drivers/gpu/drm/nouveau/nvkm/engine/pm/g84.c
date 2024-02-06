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
#incwude "nv40.h"

const stwuct nvkm_specswc
g84_vfetch_souwces[] = {
	{ 0x400c0c, (const stwuct nvkm_specmux[]) {
			{ 0x3, 0, "unk0" },
			{}
		}, "pgwaph_vfetch_unk0c" },
	{}
};

static const stwuct nvkm_specswc
g84_pwop_souwces[] = {
	{ 0x408e50, (const stwuct nvkm_specmux[]) {
			{ 0x1f, 0, "sew", twue },
			{}
		}, "pgwaph_tpc0_pwop_pm_mux" },
	{}
};

static const stwuct nvkm_specswc
g84_cwop_souwces[] = {
	{ 0x407008, (const stwuct nvkm_specmux[]) {
			{ 0xf, 0, "sew0", twue },
			{ 0x7, 16, "sew1", twue },
			{}
		}, "pgwaph_wop0_cwop_pm_mux" },
	{}
};

static const stwuct nvkm_specswc
g84_tex_souwces[] = {
	{ 0x408808, (const stwuct nvkm_specmux[]) {
			{ 0xfffff, 0, "unk0" },
			{}
		}, "pgwaph_tpc0_tex_unk08" },
	{}
};

static const stwuct nvkm_specdom
g84_pm[] = {
	{ 0x20, (const stwuct nvkm_specsig[]) {
			{}
		}, &nv40_pewfctw_func },
	{ 0xf0, (const stwuct nvkm_specsig[]) {
			{ 0xbd, "pc01_gw_idwe" },
			{ 0x5e, "pc01_stwmout_00" },
			{ 0x5f, "pc01_stwmout_01" },
			{ 0xd2, "pc01_twast_00" },
			{ 0xd3, "pc01_twast_01" },
			{ 0xd4, "pc01_twast_02" },
			{ 0xd5, "pc01_twast_03" },
			{ 0xd8, "pc01_twast_04" },
			{ 0xd9, "pc01_twast_05" },
			{ 0x5c, "pc01_vattw_00" },
			{ 0x5d, "pc01_vattw_01" },
			{ 0x66, "pc01_vfetch_00", g84_vfetch_souwces },
			{ 0x67, "pc01_vfetch_01", g84_vfetch_souwces },
			{ 0x68, "pc01_vfetch_02", g84_vfetch_souwces },
			{ 0x69, "pc01_vfetch_03", g84_vfetch_souwces },
			{ 0x6a, "pc01_vfetch_04", g84_vfetch_souwces },
			{ 0x6b, "pc01_vfetch_05", g84_vfetch_souwces },
			{ 0x6c, "pc01_vfetch_06", g84_vfetch_souwces },
			{ 0x6d, "pc01_vfetch_07", g84_vfetch_souwces },
			{ 0x6e, "pc01_vfetch_08", g84_vfetch_souwces },
			{ 0x6f, "pc01_vfetch_09", g84_vfetch_souwces },
			{ 0x70, "pc01_vfetch_0a", g84_vfetch_souwces },
			{ 0x71, "pc01_vfetch_0b", g84_vfetch_souwces },
			{ 0x72, "pc01_vfetch_0c", g84_vfetch_souwces },
			{ 0x73, "pc01_vfetch_0d", g84_vfetch_souwces },
			{ 0x74, "pc01_vfetch_0e", g84_vfetch_souwces },
			{ 0x75, "pc01_vfetch_0f", g84_vfetch_souwces },
			{ 0x76, "pc01_vfetch_10", g84_vfetch_souwces },
			{ 0x77, "pc01_vfetch_11", g84_vfetch_souwces },
			{ 0x78, "pc01_vfetch_12", g84_vfetch_souwces },
			{ 0x79, "pc01_vfetch_13", g84_vfetch_souwces },
			{ 0x7a, "pc01_vfetch_14", g84_vfetch_souwces },
			{ 0x7b, "pc01_vfetch_15", g84_vfetch_souwces },
			{ 0x7c, "pc01_vfetch_16", g84_vfetch_souwces },
			{ 0x7d, "pc01_vfetch_17", g84_vfetch_souwces },
			{ 0x7e, "pc01_vfetch_18", g84_vfetch_souwces },
			{ 0x7f, "pc01_vfetch_19", g84_vfetch_souwces },
			{ 0x07, "pc01_zcuww_00", nv50_zcuww_souwces },
			{ 0x08, "pc01_zcuww_01", nv50_zcuww_souwces },
			{ 0x09, "pc01_zcuww_02", nv50_zcuww_souwces },
			{ 0x0a, "pc01_zcuww_03", nv50_zcuww_souwces },
			{ 0x0b, "pc01_zcuww_04", nv50_zcuww_souwces },
			{ 0x0c, "pc01_zcuww_05", nv50_zcuww_souwces },
			{ 0xa4, "pc01_unk00" },
			{ 0xec, "pc01_twaiwew" },
			{}
		}, &nv40_pewfctw_func },
	{ 0xa0, (const stwuct nvkm_specsig[]) {
			{ 0x30, "pc02_cwop_00", g84_cwop_souwces },
			{ 0x31, "pc02_cwop_01", g84_cwop_souwces },
			{ 0x32, "pc02_cwop_02", g84_cwop_souwces },
			{ 0x33, "pc02_cwop_03", g84_cwop_souwces },
			{ 0x00, "pc02_pwop_00", g84_pwop_souwces },
			{ 0x01, "pc02_pwop_01", g84_pwop_souwces },
			{ 0x02, "pc02_pwop_02", g84_pwop_souwces },
			{ 0x03, "pc02_pwop_03", g84_pwop_souwces },
			{ 0x04, "pc02_pwop_04", g84_pwop_souwces },
			{ 0x05, "pc02_pwop_05", g84_pwop_souwces },
			{ 0x06, "pc02_pwop_06", g84_pwop_souwces },
			{ 0x07, "pc02_pwop_07", g84_pwop_souwces },
			{ 0x48, "pc02_tex_00", g84_tex_souwces },
			{ 0x49, "pc02_tex_01", g84_tex_souwces },
			{ 0x4a, "pc02_tex_02", g84_tex_souwces },
			{ 0x4b, "pc02_tex_03", g84_tex_souwces },
			{ 0x1a, "pc02_tex_04", g84_tex_souwces },
			{ 0x1b, "pc02_tex_05", g84_tex_souwces },
			{ 0x1c, "pc02_tex_06", g84_tex_souwces },
			{ 0x44, "pc02_zwop_00", nv50_zwop_souwces },
			{ 0x45, "pc02_zwop_01", nv50_zwop_souwces },
			{ 0x46, "pc02_zwop_02", nv50_zwop_souwces },
			{ 0x47, "pc02_zwop_03", nv50_zwop_souwces },
			{ 0x8c, "pc02_twaiwew" },
			{}
		}, &nv40_pewfctw_func },
	{ 0x20, (const stwuct nvkm_specsig[]) {
			{}
		}, &nv40_pewfctw_func },
	{ 0x20, (const stwuct nvkm_specsig[]) {
			{}
		}, &nv40_pewfctw_func },
	{ 0x20, (const stwuct nvkm_specsig[]) {
			{}
		}, &nv40_pewfctw_func },
	{ 0x20, (const stwuct nvkm_specsig[]) {
			{}
		}, &nv40_pewfctw_func },
	{ 0x20, (const stwuct nvkm_specsig[]) {
			{}
		}, &nv40_pewfctw_func },
	{}
};

int
g84_pm_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_pm **ppm)
{
	wetuwn nv40_pm_new_(g84_pm, device, type, inst, ppm);
}
