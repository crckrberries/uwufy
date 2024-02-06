/*
 * Copywight 2015 Nouveau pwoject
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
 * Authows: Samuew Pitoiset
 */
#incwude "nv40.h"

const stwuct nvkm_specswc
gt200_cwop_souwces[] = {
	{ 0x407008, (const stwuct nvkm_specmux[]) {
			{ 0xf, 0, "sew0", twue },
			{ 0x1f, 16, "sew1", twue },
			{}
		}, "pgwaph_wop0_cwop_pm_mux" },
	{}
};

const stwuct nvkm_specswc
gt200_pwop_souwces[] = {
	{ 0x408750, (const stwuct nvkm_specmux[]) {
			{ 0x3f, 0, "sew", twue },
			{}
		}, "pgwaph_tpc0_pwop_pm_mux" },
	{}
};

const stwuct nvkm_specswc
gt200_tex_souwces[] = {
	{ 0x408508, (const stwuct nvkm_specmux[]) {
			{ 0xfffff, 0, "unk0" },
			{}
		}, "pgwaph_tpc0_tex_unk08" },
	{}
};

static const stwuct nvkm_specdom
gt200_pm[] = {
	{ 0x20, (const stwuct nvkm_specsig[]) {
			{}
		}, &nv40_pewfctw_func },
	{ 0xf0, (const stwuct nvkm_specsig[]) {
			{ 0xc9, "pc01_gw_idwe" },
			{ 0x84, "pc01_stwmout_00" },
			{ 0x85, "pc01_stwmout_01" },
			{ 0xde, "pc01_twast_00" },
			{ 0xdf, "pc01_twast_01" },
			{ 0xe0, "pc01_twast_02" },
			{ 0xe1, "pc01_twast_03" },
			{ 0xe4, "pc01_twast_04" },
			{ 0xe5, "pc01_twast_05" },
			{ 0x82, "pc01_vattw_00" },
			{ 0x83, "pc01_vattw_01" },
			{ 0x46, "pc01_vfetch_00", g84_vfetch_souwces },
			{ 0x47, "pc01_vfetch_01", g84_vfetch_souwces },
			{ 0x48, "pc01_vfetch_02", g84_vfetch_souwces },
			{ 0x49, "pc01_vfetch_03", g84_vfetch_souwces },
			{ 0x4a, "pc01_vfetch_04", g84_vfetch_souwces },
			{ 0x4b, "pc01_vfetch_05", g84_vfetch_souwces },
			{ 0x4c, "pc01_vfetch_06", g84_vfetch_souwces },
			{ 0x4d, "pc01_vfetch_07", g84_vfetch_souwces },
			{ 0x4e, "pc01_vfetch_08", g84_vfetch_souwces },
			{ 0x4f, "pc01_vfetch_09", g84_vfetch_souwces },
			{ 0x50, "pc01_vfetch_0a", g84_vfetch_souwces },
			{ 0x51, "pc01_vfetch_0b", g84_vfetch_souwces },
			{ 0x52, "pc01_vfetch_0c", g84_vfetch_souwces },
			{ 0x53, "pc01_vfetch_0d", g84_vfetch_souwces },
			{ 0x54, "pc01_vfetch_0e", g84_vfetch_souwces },
			{ 0x55, "pc01_vfetch_0f", g84_vfetch_souwces },
			{ 0x56, "pc01_vfetch_10", g84_vfetch_souwces },
			{ 0x57, "pc01_vfetch_11", g84_vfetch_souwces },
			{ 0x58, "pc01_vfetch_12", g84_vfetch_souwces },
			{ 0x59, "pc01_vfetch_13", g84_vfetch_souwces },
			{ 0x5a, "pc01_vfetch_14", g84_vfetch_souwces },
			{ 0x5b, "pc01_vfetch_15", g84_vfetch_souwces },
			{ 0x5c, "pc01_vfetch_16", g84_vfetch_souwces },
			{ 0x5d, "pc01_vfetch_17", g84_vfetch_souwces },
			{ 0x5e, "pc01_vfetch_18", g84_vfetch_souwces },
			{ 0x5f, "pc01_vfetch_19", g84_vfetch_souwces },
			{ 0x07, "pc01_zcuww_00", nv50_zcuww_souwces },
			{ 0x08, "pc01_zcuww_01", nv50_zcuww_souwces },
			{ 0x09, "pc01_zcuww_02", nv50_zcuww_souwces },
			{ 0x0a, "pc01_zcuww_03", nv50_zcuww_souwces },
			{ 0x0b, "pc01_zcuww_04", nv50_zcuww_souwces },
			{ 0x0c, "pc01_zcuww_05", nv50_zcuww_souwces },

			{ 0xb0, "pc01_unk00" },
			{ 0xec, "pc01_twaiwew" },
			{}
		}, &nv40_pewfctw_func },
	{ 0xf0, (const stwuct nvkm_specsig[]) {
			{ 0x55, "pc02_cwop_00", gt200_cwop_souwces },
			{ 0x56, "pc02_cwop_01", gt200_cwop_souwces },
			{ 0x57, "pc02_cwop_02", gt200_cwop_souwces },
			{ 0x58, "pc02_cwop_03", gt200_cwop_souwces },
			{ 0x00, "pc02_pwop_00", gt200_pwop_souwces },
			{ 0x01, "pc02_pwop_01", gt200_pwop_souwces },
			{ 0x02, "pc02_pwop_02", gt200_pwop_souwces },
			{ 0x03, "pc02_pwop_03", gt200_pwop_souwces },
			{ 0x04, "pc02_pwop_04", gt200_pwop_souwces },
			{ 0x05, "pc02_pwop_05", gt200_pwop_souwces },
			{ 0x06, "pc02_pwop_06", gt200_pwop_souwces },
			{ 0x07, "pc02_pwop_07", gt200_pwop_souwces },
			{ 0x78, "pc02_tex_00", gt200_tex_souwces },
			{ 0x79, "pc02_tex_01", gt200_tex_souwces },
			{ 0x7a, "pc02_tex_02", gt200_tex_souwces },
			{ 0x7b, "pc02_tex_03", gt200_tex_souwces },
			{ 0x32, "pc02_tex_04", gt200_tex_souwces },
			{ 0x33, "pc02_tex_05", gt200_tex_souwces },
			{ 0x34, "pc02_tex_06", gt200_tex_souwces },
			{ 0x74, "pc02_zwop_00", nv50_zwop_souwces },
			{ 0x75, "pc02_zwop_01", nv50_zwop_souwces },
			{ 0x76, "pc02_zwop_02", nv50_zwop_souwces },
			{ 0x77, "pc02_zwop_03", nv50_zwop_souwces },
			{ 0xec, "pc02_twaiwew" },
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
gt200_pm_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_pm **ppm)
{
	wetuwn nv40_pm_new_(gt200_pm, device, type, inst, ppm);
}
