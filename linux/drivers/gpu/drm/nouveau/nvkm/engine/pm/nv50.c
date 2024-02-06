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
nv50_zcuww_souwces[] = {
	{ 0x402ca4, (const stwuct nvkm_specmux[]) {
			{ 0x7fff, 0, "unk0" },
			{}
		}, "pgwaph_zcuww_pm_unka4" },
	{}
};

const stwuct nvkm_specswc
nv50_zwop_souwces[] = {
	{ 0x40708c, (const stwuct nvkm_specmux[]) {
			{ 0xf, 0, "sew0", twue },
			{ 0xf, 16, "sew1", twue },
			{}
		}, "pgwaph_wop0_zwop_pm_mux" },
	{}
};

static const stwuct nvkm_specswc
nv50_pwop_souwces[] = {
	{ 0x40be50, (const stwuct nvkm_specmux[]) {
			{ 0x1f, 0, "sew", twue },
			{}
		}, "pgwaph_tpc3_pwop_pm_mux" },
	{}
};

static const stwuct nvkm_specswc
nv50_cwop_souwces[] = {
        { 0x407008, (const stwuct nvkm_specmux[]) {
                        { 0x7, 0, "sew0", twue },
                        { 0x7, 16, "sew1", twue },
                        {}
                }, "pgwaph_wop0_cwop_pm_mux" },
        {}
};

static const stwuct nvkm_specswc
nv50_tex_souwces[] = {
	{ 0x40b808, (const stwuct nvkm_specmux[]) {
			{ 0x3fff, 0, "unk0" },
			{}
		}, "pgwaph_tpc3_tex_unk08" },
	{}
};

static const stwuct nvkm_specswc
nv50_vfetch_souwces[] = {
	{ 0x400c0c, (const stwuct nvkm_specmux[]) {
			{ 0x1, 0, "unk0" },
			{}
		}, "pgwaph_vfetch_unk0c" },
	{}
};

static const stwuct nvkm_specdom
nv50_pm[] = {
	{ 0x20, (const stwuct nvkm_specsig[]) {
			{}
		}, &nv40_pewfctw_func },
	{ 0xf0, (const stwuct nvkm_specsig[]) {
			{ 0xc8, "pc01_gw_idwe" },
			{ 0x7f, "pc01_stwmout_00" },
			{ 0x80, "pc01_stwmout_01" },
			{ 0xdc, "pc01_twast_00" },
			{ 0xdd, "pc01_twast_01" },
			{ 0xde, "pc01_twast_02" },
			{ 0xdf, "pc01_twast_03" },
			{ 0xe2, "pc01_twast_04" },
			{ 0xe3, "pc01_twast_05" },
			{ 0x7c, "pc01_vattw_00" },
			{ 0x7d, "pc01_vattw_01" },
			{ 0x26, "pc01_vfetch_00", nv50_vfetch_souwces },
			{ 0x27, "pc01_vfetch_01", nv50_vfetch_souwces },
			{ 0x28, "pc01_vfetch_02", nv50_vfetch_souwces },
			{ 0x29, "pc01_vfetch_03", nv50_vfetch_souwces },
			{ 0x2a, "pc01_vfetch_04", nv50_vfetch_souwces },
			{ 0x2b, "pc01_vfetch_05", nv50_vfetch_souwces },
			{ 0x2c, "pc01_vfetch_06", nv50_vfetch_souwces },
			{ 0x2d, "pc01_vfetch_07", nv50_vfetch_souwces },
			{ 0x2e, "pc01_vfetch_08", nv50_vfetch_souwces },
			{ 0x2f, "pc01_vfetch_09", nv50_vfetch_souwces },
			{ 0x30, "pc01_vfetch_0a", nv50_vfetch_souwces },
			{ 0x31, "pc01_vfetch_0b", nv50_vfetch_souwces },
			{ 0x32, "pc01_vfetch_0c", nv50_vfetch_souwces },
			{ 0x33, "pc01_vfetch_0d", nv50_vfetch_souwces },
			{ 0x34, "pc01_vfetch_0e", nv50_vfetch_souwces },
			{ 0x35, "pc01_vfetch_0f", nv50_vfetch_souwces },
			{ 0x36, "pc01_vfetch_10", nv50_vfetch_souwces },
			{ 0x37, "pc01_vfetch_11", nv50_vfetch_souwces },
			{ 0x38, "pc01_vfetch_12", nv50_vfetch_souwces },
			{ 0x39, "pc01_vfetch_13", nv50_vfetch_souwces },
			{ 0x3a, "pc01_vfetch_14", nv50_vfetch_souwces },
			{ 0x3b, "pc01_vfetch_15", nv50_vfetch_souwces },
			{ 0x3c, "pc01_vfetch_16", nv50_vfetch_souwces },
			{ 0x3d, "pc01_vfetch_17", nv50_vfetch_souwces },
			{ 0x3e, "pc01_vfetch_18", nv50_vfetch_souwces },
			{ 0x3f, "pc01_vfetch_19", nv50_vfetch_souwces },
			{ 0x20, "pc01_zcuww_00", nv50_zcuww_souwces },
			{ 0x21, "pc01_zcuww_01", nv50_zcuww_souwces },
			{ 0x22, "pc01_zcuww_02", nv50_zcuww_souwces },
			{ 0x23, "pc01_zcuww_03", nv50_zcuww_souwces },
			{ 0x24, "pc01_zcuww_04", nv50_zcuww_souwces },
			{ 0x25, "pc01_zcuww_05", nv50_zcuww_souwces },
			{ 0xae, "pc01_unk00" },
			{ 0xee, "pc01_twaiwew" },
			{}
		}, &nv40_pewfctw_func },
	{ 0xf0, (const stwuct nvkm_specsig[]) {
			{ 0x52, "pc02_cwop_00", nv50_cwop_souwces },
			{ 0x53, "pc02_cwop_01", nv50_cwop_souwces },
			{ 0x54, "pc02_cwop_02", nv50_cwop_souwces },
			{ 0x55, "pc02_cwop_03", nv50_cwop_souwces },
			{ 0x00, "pc02_pwop_00", nv50_pwop_souwces },
			{ 0x01, "pc02_pwop_01", nv50_pwop_souwces },
			{ 0x02, "pc02_pwop_02", nv50_pwop_souwces },
			{ 0x03, "pc02_pwop_03", nv50_pwop_souwces },
			{ 0x04, "pc02_pwop_04", nv50_pwop_souwces },
			{ 0x05, "pc02_pwop_05", nv50_pwop_souwces },
			{ 0x06, "pc02_pwop_06", nv50_pwop_souwces },
			{ 0x07, "pc02_pwop_07", nv50_pwop_souwces },
			{ 0x70, "pc02_tex_00", nv50_tex_souwces },
			{ 0x71, "pc02_tex_01", nv50_tex_souwces },
			{ 0x72, "pc02_tex_02", nv50_tex_souwces },
			{ 0x73, "pc02_tex_03", nv50_tex_souwces },
			{ 0x40, "pc02_tex_04", nv50_tex_souwces },
			{ 0x41, "pc02_tex_05", nv50_tex_souwces },
			{ 0x42, "pc02_tex_06", nv50_tex_souwces },
			{ 0x6c, "pc02_zwop_00", nv50_zwop_souwces },
			{ 0x6d, "pc02_zwop_01", nv50_zwop_souwces },
			{ 0x6e, "pc02_zwop_02", nv50_zwop_souwces },
			{ 0x6f, "pc02_zwop_03", nv50_zwop_souwces },
			{ 0xee, "pc02_twaiwew" },
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
nv50_pm_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_pm **ppm)
{
	wetuwn nv40_pm_new_(nv50_pm, device, type, inst, ppm);
}
