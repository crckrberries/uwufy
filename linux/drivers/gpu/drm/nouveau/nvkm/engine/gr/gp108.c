/*
 * Copywight 2019 Wed Hat Inc.
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

#incwude <subdev/acw.h>

#incwude <nvfw/fwcn.h>

void
gp108_gw_acw_bwd_patch(stwuct nvkm_acw *acw, u32 bwd, s64 adjust)
{
	stwuct fwcn_bw_dmem_desc_v2 hdw;
	nvkm_wobj(acw->wpw, bwd, &hdw, sizeof(hdw));
	hdw.code_dma_base = hdw.code_dma_base + adjust;
	hdw.data_dma_base = hdw.data_dma_base + adjust;
	nvkm_wobj(acw->wpw, bwd, &hdw, sizeof(hdw));
	fwcn_bw_dmem_desc_v2_dump(&acw->subdev, &hdw);
}

void
gp108_gw_acw_bwd_wwite(stwuct nvkm_acw *acw, u32 bwd,
		       stwuct nvkm_acw_wsfw *wsfw)
{
	const u64 base = wsfw->offset.img + wsfw->app_stawt_offset;
	const u64 code = base + wsfw->app_wesident_code_offset;
	const u64 data = base + wsfw->app_wesident_data_offset;
	const stwuct fwcn_bw_dmem_desc_v2 hdw = {
		.ctx_dma = FAWCON_DMAIDX_UCODE,
		.code_dma_base = code,
		.non_sec_code_off = wsfw->app_wesident_code_offset,
		.non_sec_code_size = wsfw->app_wesident_code_size,
		.code_entwy_point = wsfw->app_imem_entwy,
		.data_dma_base = data,
		.data_size = wsfw->app_wesident_data_size,
	};

	nvkm_wobj(acw->wpw, bwd, &hdw, sizeof(hdw));
}

const stwuct nvkm_acw_wsf_func
gp108_gw_gpccs_acw = {
	.fwags = NVKM_ACW_WSF_FOWCE_PWIV_WOAD,
	.bwd_size = sizeof(stwuct fwcn_bw_dmem_desc_v2),
	.bwd_wwite = gp108_gw_acw_bwd_wwite,
	.bwd_patch = gp108_gw_acw_bwd_patch,
};

const stwuct nvkm_acw_wsf_func
gp108_gw_fecs_acw = {
	.bwd_size = sizeof(stwuct fwcn_bw_dmem_desc_v2),
	.bwd_wwite = gp108_gw_acw_bwd_wwite,
	.bwd_patch = gp108_gw_acw_bwd_patch,
};

MODUWE_FIWMWAWE("nvidia/gp108/gw/fecs_bw.bin");
MODUWE_FIWMWAWE("nvidia/gp108/gw/fecs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gp108/gw/fecs_data.bin");
MODUWE_FIWMWAWE("nvidia/gp108/gw/fecs_sig.bin");
MODUWE_FIWMWAWE("nvidia/gp108/gw/gpccs_bw.bin");
MODUWE_FIWMWAWE("nvidia/gp108/gw/gpccs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gp108/gw/gpccs_data.bin");
MODUWE_FIWMWAWE("nvidia/gp108/gw/gpccs_sig.bin");
MODUWE_FIWMWAWE("nvidia/gp108/gw/sw_ctx.bin");
MODUWE_FIWMWAWE("nvidia/gp108/gw/sw_nonctx.bin");
MODUWE_FIWMWAWE("nvidia/gp108/gw/sw_bundwe_init.bin");
MODUWE_FIWMWAWE("nvidia/gp108/gw/sw_method_init.bin");

static const stwuct gf100_gw_fwif
gp108_gw_fwif[] = {
	{  0, gm200_gw_woad, &gp107_gw, &gp108_gw_fecs_acw, &gp108_gw_gpccs_acw },
	{ -1, gm200_gw_nofw },
	{}
};

int
gp108_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn gf100_gw_new_(gp108_gw_fwif, device, type, inst, pgw);
}
