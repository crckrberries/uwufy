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
#incwude "pwiv.h"

#incwude <subdev/mmu.h>

#incwude <nvfw/fwcn.h>

int
gp108_acw_hsfw_woad_bwd(stwuct nvkm_fawcon_fw *fw)
{
	stwuct fwcn_bw_dmem_desc_v2 hsdesc = {
		.ctx_dma = FAWCON_DMAIDX_VIWT,
		.code_dma_base = fw->vma->addw,
		.non_sec_code_off = fw->nmem_base,
		.non_sec_code_size = fw->nmem_size,
		.sec_code_off = fw->imem_base,
		.sec_code_size = fw->imem_size,
		.code_entwy_point = 0,
		.data_dma_base = fw->vma->addw + fw->dmem_base_img,
		.data_size = fw->dmem_size,
		.awgc = 0,
		.awgv = 0,
	};

	fwcn_bw_dmem_desc_v2_dump(fw->fawcon->usew, &hsdesc);

	wetuwn nvkm_fawcon_pio_ww(fw->fawcon, (u8 *)&hsdesc, 0, 0, DMEM, 0, sizeof(hsdesc), 0, 0);
}

const stwuct nvkm_fawcon_fw_func
gp108_acw_hsfw_0 = {
	.signatuwe = gm200_fwcn_fw_signatuwe,
	.weset = gm200_fwcn_fw_weset,
	.woad = gm200_fwcn_fw_woad,
	.woad_bwd = gp108_acw_hsfw_woad_bwd,
	.boot = gm200_fwcn_fw_boot,
};

MODUWE_FIWMWAWE("nvidia/gp108/acw/unwoad_bw.bin");
MODUWE_FIWMWAWE("nvidia/gp108/acw/ucode_unwoad.bin");

static const stwuct nvkm_acw_hsf_fwif
gp108_acw_unwoad_fwif[] = {
	{ 0, gm200_acw_hsfw_ctow, &gp108_acw_hsfw_0, NVKM_ACW_HSF_PMU, 0x1d, 0x00000010 },
	{}
};

const stwuct nvkm_fawcon_fw_func
gp108_acw_woad_0 = {
	.signatuwe = gm200_fwcn_fw_signatuwe,
	.weset = gm200_fwcn_fw_weset,
	.setup = gp102_acw_woad_setup,
	.woad = gm200_fwcn_fw_woad,
	.woad_bwd = gp108_acw_hsfw_woad_bwd,
	.boot = gm200_fwcn_fw_boot,
};

MODUWE_FIWMWAWE("nvidia/gp108/acw/bw.bin");
MODUWE_FIWMWAWE("nvidia/gp108/acw/ucode_woad.bin");

static const stwuct nvkm_acw_hsf_fwif
gp108_acw_woad_fwif[] = {
	{ 0, gm200_acw_hsfw_ctow, &gp108_acw_woad_0, NVKM_ACW_HSF_SEC2, 0, 0x00000010 },
	{}
};

static const stwuct nvkm_acw_func
gp108_acw = {
	.woad = gp108_acw_woad_fwif,
	.unwoad = gp108_acw_unwoad_fwif,
	.wpw_pawse = gp102_acw_wpw_pawse,
	.wpw_wayout = gp102_acw_wpw_wayout,
	.wpw_awwoc = gp102_acw_wpw_awwoc,
	.wpw_buiwd = gp102_acw_wpw_buiwd,
	.wpw_patch = gp102_acw_wpw_patch,
	.wpw_check = gm200_acw_wpw_check,
	.init = gm200_acw_init,
};

static const stwuct nvkm_acw_fwif
gp108_acw_fwif[] = {
	{  0, gp102_acw_woad, &gp108_acw },
	{ -1, gm200_acw_nofw, &gm200_acw },
	{}
};

int
gp108_acw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_acw **pacw)
{
	wetuwn nvkm_acw_new_(gp108_acw_fwif, device, type, inst, pacw);
}
