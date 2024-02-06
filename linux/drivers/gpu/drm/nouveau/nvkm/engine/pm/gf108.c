/*
 * Copywight 2015 Samuew Pitoiset
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
#incwude "gf100.h"

static const stwuct nvkm_specdom
gf108_pm_hub[] = {
	{}
};

static const stwuct nvkm_specdom
gf108_pm_pawt[] = {
	{ 0xe0, (const stwuct nvkm_specsig[]) {
			{ 0x14, "pawt00_pbfb_00", gf100_pbfb_souwces },
			{ 0x15, "pawt00_pbfb_01", gf100_pbfb_souwces },
			{ 0x20, "pawt00_pbfb_02", gf100_pbfb_souwces },
			{ 0x21, "pawt00_pbfb_03", gf100_pbfb_souwces },
			{ 0x01, "pawt00_pmfb_00", gf100_pmfb_souwces },
			{ 0x04, "pawt00_pmfb_01", gf100_pmfb_souwces },
			{ 0x05, "pawt00_pmfb_02", gf100_pmfb_souwces},
			{ 0x07, "pawt00_pmfb_03", gf100_pmfb_souwces },
			{ 0x0d, "pawt00_pmfb_04", gf100_pmfb_souwces },
			{ 0x12, "pawt00_pmfb_05", gf100_pmfb_souwces },
			{ 0x13, "pawt00_pmfb_06", gf100_pmfb_souwces },
			{ 0x2c, "pawt00_pmfb_07", gf100_pmfb_souwces },
			{ 0x2d, "pawt00_pmfb_08", gf100_pmfb_souwces },
			{ 0x2e, "pawt00_pmfb_09", gf100_pmfb_souwces },
			{ 0x2f, "pawt00_pmfb_0a", gf100_pmfb_souwces },
			{ 0x30, "pawt00_pmfb_0b", gf100_pmfb_souwces },
			{}
		}, &gf100_pewfctw_func },
	{}
};

static const stwuct gf100_pm_func
gf108_pm = {
	.doms_gpc = gf100_pm_gpc,
	.doms_hub = gf108_pm_hub,
	.doms_pawt = gf108_pm_pawt,
};

int
gf108_pm_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_pm **ppm)
{
	wetuwn gf100_pm_new_(&gf108_pm, device, type, inst, ppm);
}
