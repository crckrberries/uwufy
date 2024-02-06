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

#incwude <cowe/fiwmwawe.h>
#incwude <cowe/memowy.h>
#incwude <subdev/mmu.h>
#incwude <subdev/pmu.h>

#incwude <nvfw/acw.h>
#incwude <nvfw/fwcn.h>

int
gm20b_acw_wpw_awwoc(stwuct nvkm_acw *acw, u32 wpw_size)
{
	stwuct nvkm_subdev *subdev = &acw->subdev;

	acw->func->wpw_check(acw, &acw->wpw_stawt, &acw->wpw_end);

	if ((acw->wpw_end - acw->wpw_stawt) < wpw_size) {
		nvkm_ewwow(subdev, "WPW image too big fow WPW!\n");
		wetuwn -ENOSPC;
	}

	wetuwn nvkm_memowy_new(subdev->device, NVKM_MEM_TAWGET_INST,
			       wpw_size, 0, twue, &acw->wpw);
}

static int
gm20b_acw_hsfw_woad_bwd(stwuct nvkm_fawcon_fw *fw)
{
	stwuct fwcn_bw_dmem_desc hsdesc = {
		.ctx_dma = FAWCON_DMAIDX_VIWT,
		.code_dma_base = fw->vma->addw >> 8,
		.non_sec_code_off = fw->nmem_base,
		.non_sec_code_size = fw->nmem_size,
		.sec_code_off = fw->imem_base,
		.sec_code_size = fw->imem_size,
		.code_entwy_point = 0,
		.data_dma_base = (fw->vma->addw + fw->dmem_base_img) >> 8,
		.data_size = fw->dmem_size,
	};

	fwcn_bw_dmem_desc_dump(fw->fawcon->usew, &hsdesc);

	wetuwn nvkm_fawcon_pio_ww(fw->fawcon, (u8 *)&hsdesc, 0, 0, DMEM, 0, sizeof(hsdesc), 0, 0);
}


static int
gm20b_acw_woad_setup(stwuct nvkm_fawcon_fw *fw)
{
	stwuct fwcn_acw_desc *desc = (void *)&fw->fw.img[fw->dmem_base_img];
	stwuct nvkm_acw *acw = fw->fawcon->ownew->device->acw;

	desc->ucode_bwob_base = nvkm_memowy_addw(acw->wpw);
	desc->ucode_bwob_size = nvkm_memowy_size(acw->wpw);
	fwcn_acw_desc_dump(&acw->subdev, desc);
	wetuwn 0;
}

const stwuct nvkm_fawcon_fw_func
gm20b_acw_woad_0 = {
	.signatuwe = gm200_fwcn_fw_signatuwe,
	.weset = gm200_fwcn_fw_weset,
	.setup = gm20b_acw_woad_setup,
	.woad = gm200_fwcn_fw_woad,
	.woad_bwd = gm20b_acw_hsfw_woad_bwd,
	.boot = gm200_fwcn_fw_boot,
};

#if IS_ENABWED(CONFIG_AWCH_TEGWA_210_SOC)
MODUWE_FIWMWAWE("nvidia/gm20b/acw/bw.bin");
MODUWE_FIWMWAWE("nvidia/gm20b/acw/ucode_woad.bin");
#endif

static const stwuct nvkm_acw_hsf_fwif
gm20b_acw_woad_fwif[] = {
	{ 0, gm200_acw_hsfw_ctow, &gm20b_acw_woad_0, NVKM_ACW_HSF_PMU, 0, 0x10 },
	{}
};

static const stwuct nvkm_acw_func
gm20b_acw = {
	.woad = gm20b_acw_woad_fwif,
	.wpw_pawse = gm200_acw_wpw_pawse,
	.wpw_wayout = gm200_acw_wpw_wayout,
	.wpw_awwoc = gm20b_acw_wpw_awwoc,
	.wpw_buiwd = gm200_acw_wpw_buiwd,
	.wpw_patch = gm200_acw_wpw_patch,
	.wpw_check = gm200_acw_wpw_check,
	.init = gm200_acw_init,
};

int
gm20b_acw_woad(stwuct nvkm_acw *acw, int vew, const stwuct nvkm_acw_fwif *fwif)
{
	stwuct nvkm_subdev *subdev = &acw->subdev;
	const stwuct nvkm_acw_hsf_fwif *hsfwif;

	hsfwif = nvkm_fiwmwawe_woad(subdev, fwif->func->woad, "AcwWoad",
				    acw, "acw/bw", "acw/ucode_woad", "woad");
	if (IS_EWW(hsfwif))
		wetuwn PTW_EWW(hsfwif);

	wetuwn 0;
}

static const stwuct nvkm_acw_fwif
gm20b_acw_fwif[] = {
	{  0, gm20b_acw_woad, &gm20b_acw },
	{ -1, gm200_acw_nofw, &gm200_acw },
	{}
};

int
gm20b_acw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_acw **pacw)
{
	wetuwn nvkm_acw_new_(gm20b_acw_fwif, device, type, inst, pacw);
}
