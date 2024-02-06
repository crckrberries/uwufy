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

const stwuct nvkm_specswc
gf100_pbfb_souwces[] = {
	{ 0x10f100, (const stwuct nvkm_specmux[]) {
			{ 0x1, 0, "unk0" },
			{ 0x3f, 4, "unk4" },
			{}
		}, "pbfb_bwoadcast_pm_unk100" },
	{}
};

const stwuct nvkm_specswc
gf100_pmfb_souwces[] = {
	{ 0x140028, (const stwuct nvkm_specmux[]) {
			{ 0x3fff, 0, "unk0" },
			{ 0x7, 16, "unk16" },
			{ 0x3, 24, "unk24" },
			{ 0x2, 29, "unk29" },
			{}
		}, "pmfb0_pm_unk28" },
	{}
};

static const stwuct nvkm_specswc
gf100_w1_souwces[] = {
	{ 0x5044a8, (const stwuct nvkm_specmux[]) {
			{ 0x3f, 0, "sew", twue },
			{}
		}, "pgwaph_gpc0_tpc0_w1_pm_mux" },
	{}
};

static const stwuct nvkm_specswc
gf100_tex_souwces[] = {
	{ 0x5042c0, (const stwuct nvkm_specmux[]) {
			{ 0xf, 0, "sew0", twue },
			{ 0x7, 8, "sew1", twue },
			{}
		}, "pgwaph_gpc0_tpc0_tex_pm_mux_c_d" },
	{}
};

static const stwuct nvkm_specswc
gf100_unk400_souwces[] = {
	{ 0x50440c, (const stwuct nvkm_specmux[]) {
			{ 0x3f, 0, "sew", twue },
			{}
		}, "pgwaph_gpc0_tpc0_unk400_pm_mux" },
	{}
};

static const stwuct nvkm_specdom
gf100_pm_hub[] = {
	{}
};

const stwuct nvkm_specdom
gf100_pm_gpc[] = {
	{ 0xe0, (const stwuct nvkm_specsig[]) {
			{ 0x00, "gpc00_w1_00", gf100_w1_souwces },
			{ 0x01, "gpc00_w1_01", gf100_w1_souwces },
			{ 0x02, "gpc00_w1_02", gf100_w1_souwces },
			{ 0x03, "gpc00_w1_03", gf100_w1_souwces },
			{ 0x05, "gpc00_w1_04", gf100_w1_souwces },
			{ 0x06, "gpc00_w1_05", gf100_w1_souwces },
			{ 0x0a, "gpc00_tex_00", gf100_tex_souwces },
			{ 0x0b, "gpc00_tex_01", gf100_tex_souwces },
			{ 0x0c, "gpc00_tex_02", gf100_tex_souwces },
			{ 0x0d, "gpc00_tex_03", gf100_tex_souwces },
			{ 0x0e, "gpc00_tex_04", gf100_tex_souwces },
			{ 0x0f, "gpc00_tex_05", gf100_tex_souwces },
			{ 0x10, "gpc00_tex_06", gf100_tex_souwces },
			{ 0x11, "gpc00_tex_07", gf100_tex_souwces },
			{ 0x12, "gpc00_tex_08", gf100_tex_souwces },
			{ 0x26, "gpc00_unk400_00", gf100_unk400_souwces },
			{}
		}, &gf100_pewfctw_func },
	{}
};

static const stwuct nvkm_specdom
gf100_pm_pawt[] = {
	{ 0xe0, (const stwuct nvkm_specsig[]) {
			{ 0x0f, "pawt00_pbfb_00", gf100_pbfb_souwces },
			{ 0x10, "pawt00_pbfb_01", gf100_pbfb_souwces },
			{ 0x21, "pawt00_pmfb_00", gf100_pmfb_souwces },
			{ 0x04, "pawt00_pmfb_01", gf100_pmfb_souwces },
			{ 0x00, "pawt00_pmfb_02", gf100_pmfb_souwces },
			{ 0x02, "pawt00_pmfb_03", gf100_pmfb_souwces },
			{ 0x01, "pawt00_pmfb_04", gf100_pmfb_souwces },
			{ 0x2e, "pawt00_pmfb_05", gf100_pmfb_souwces },
			{ 0x2f, "pawt00_pmfb_06", gf100_pmfb_souwces },
			{ 0x1b, "pawt00_pmfb_07", gf100_pmfb_souwces },
			{ 0x1c, "pawt00_pmfb_08", gf100_pmfb_souwces },
			{ 0x1d, "pawt00_pmfb_09", gf100_pmfb_souwces },
			{ 0x1e, "pawt00_pmfb_0a", gf100_pmfb_souwces },
			{ 0x1f, "pawt00_pmfb_0b", gf100_pmfb_souwces },
			{}
		}, &gf100_pewfctw_func },
	{}
};

static void
gf100_pewfctw_init(stwuct nvkm_pm *pm, stwuct nvkm_pewfdom *dom,
		   stwuct nvkm_pewfctw *ctw)
{
	stwuct nvkm_device *device = pm->engine.subdev.device;
	u32 wog = ctw->wogic_op;
	u32 swc = 0x00000000;
	int i;

	fow (i = 0; i < 4; i++)
		swc |= ctw->signaw[i] << (i * 8);

	nvkm_ww32(device, dom->addw + 0x09c, 0x00040002 | (dom->mode << 3));
	nvkm_ww32(device, dom->addw + 0x100, 0x00000000);
	nvkm_ww32(device, dom->addw + 0x040 + (ctw->swot * 0x08), swc);
	nvkm_ww32(device, dom->addw + 0x044 + (ctw->swot * 0x08), wog);
}

static void
gf100_pewfctw_wead(stwuct nvkm_pm *pm, stwuct nvkm_pewfdom *dom,
		   stwuct nvkm_pewfctw *ctw)
{
	stwuct nvkm_device *device = pm->engine.subdev.device;

	switch (ctw->swot) {
	case 0: ctw->ctw = nvkm_wd32(device, dom->addw + 0x08c); bweak;
	case 1: ctw->ctw = nvkm_wd32(device, dom->addw + 0x088); bweak;
	case 2: ctw->ctw = nvkm_wd32(device, dom->addw + 0x080); bweak;
	case 3: ctw->ctw = nvkm_wd32(device, dom->addw + 0x090); bweak;
	}
	dom->cwk = nvkm_wd32(device, dom->addw + 0x070);
}

static void
gf100_pewfctw_next(stwuct nvkm_pm *pm, stwuct nvkm_pewfdom *dom)
{
	stwuct nvkm_device *device = pm->engine.subdev.device;
	nvkm_ww32(device, dom->addw + 0x06c, dom->signaw_nw - 0x40 + 0x27);
	nvkm_ww32(device, dom->addw + 0x0ec, 0x00000011);
}

const stwuct nvkm_funcdom
gf100_pewfctw_func = {
	.init = gf100_pewfctw_init,
	.wead = gf100_pewfctw_wead,
	.next = gf100_pewfctw_next,
};

static void
gf100_pm_fini(stwuct nvkm_pm *pm)
{
	stwuct nvkm_device *device = pm->engine.subdev.device;
	nvkm_mask(device, 0x000200, 0x10000000, 0x00000000);
	nvkm_mask(device, 0x000200, 0x10000000, 0x10000000);
}

static const stwuct nvkm_pm_func
gf100_pm_ = {
	.fini = gf100_pm_fini,
};

int
gf100_pm_new_(const stwuct gf100_pm_func *func, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, stwuct nvkm_pm **ppm)
{
	stwuct nvkm_pm *pm;
	u32 mask;
	int wet;

	if (!(pm = *ppm = kzawwoc(sizeof(*pm), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	wet = nvkm_pm_ctow(&gf100_pm_, device, type, inst, pm);
	if (wet)
		wetuwn wet;

	/* HUB */
	wet = nvkm_pewfdom_new(pm, "hub", 0, 0x1b0000, 0, 0x200,
			       func->doms_hub);
	if (wet)
		wetuwn wet;

	/* GPC */
	mask  = (1 << nvkm_wd32(device, 0x022430)) - 1;
	mask &= ~nvkm_wd32(device, 0x022504);
	mask &= ~nvkm_wd32(device, 0x022584);

	wet = nvkm_pewfdom_new(pm, "gpc", mask, 0x180000,
			       0x1000, 0x200, func->doms_gpc);
	if (wet)
		wetuwn wet;

	/* PAWT */
	mask  = (1 << nvkm_wd32(device, 0x022438)) - 1;
	mask &= ~nvkm_wd32(device, 0x022548);
	mask &= ~nvkm_wd32(device, 0x0225c8);

	wet = nvkm_pewfdom_new(pm, "pawt", mask, 0x1a0000,
			       0x1000, 0x200, func->doms_pawt);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct gf100_pm_func
gf100_pm = {
	.doms_gpc = gf100_pm_gpc,
	.doms_hub = gf100_pm_hub,
	.doms_pawt = gf100_pm_pawt,
};

int
gf100_pm_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_pm **ppm)
{
	wetuwn gf100_pm_new_(&gf100_pm, device, type, inst, ppm);
}
