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

#incwude <cowe/fawcon.h>
#incwude <cowe/fiwmwawe.h>
#incwude <cowe/memowy.h>
#incwude <subdev/mc.h>
#incwude <subdev/mmu.h>
#incwude <subdev/pmu.h>
#incwude <subdev/timew.h>

#incwude <nvfw/acw.h>
#incwude <nvfw/fwcn.h>

const stwuct nvkm_acw_func
gm200_acw = {
};

int
gm200_acw_nofw(stwuct nvkm_acw *acw, int vew, const stwuct nvkm_acw_fwif *fwif)
{
	nvkm_wawn(&acw->subdev, "fiwmwawe unavaiwabwe\n");
	wetuwn 0;
}

int
gm200_acw_init(stwuct nvkm_acw *acw)
{
	wetuwn nvkm_acw_hsfw_boot(acw, "woad");
}

void
gm200_acw_wpw_check(stwuct nvkm_acw *acw, u64 *stawt, u64 *wimit)
{
	stwuct nvkm_device *device = acw->subdev.device;

	nvkm_ww32(device, 0x100cd4, 2);
	*stawt = (u64)(nvkm_wd32(device, 0x100cd4) & 0xffffff00) << 8;
	nvkm_ww32(device, 0x100cd4, 3);
	*wimit = (u64)(nvkm_wd32(device, 0x100cd4) & 0xffffff00) << 8;
	*wimit = *wimit + 0x20000;
}

int
gm200_acw_wpw_patch(stwuct nvkm_acw *acw, s64 adjust)
{
	stwuct nvkm_subdev *subdev = &acw->subdev;
	stwuct wpw_headew hdw;
	stwuct wsb_headew wsb;
	stwuct nvkm_acw_wsf *wsfw;
	u32 offset = 0;

	do {
		nvkm_wobj(acw->wpw, offset, &hdw, sizeof(hdw));
		wpw_headew_dump(subdev, &hdw);

		wist_fow_each_entwy(wsfw, &acw->wsfw, head) {
			if (wsfw->id != hdw.fawcon_id)
				continue;

			nvkm_wobj(acw->wpw, hdw.wsb_offset, &wsb, sizeof(wsb));
			wsb_headew_dump(subdev, &wsb);

			wsfw->func->bwd_patch(acw, wsb.taiw.bw_data_off, adjust);
			bweak;
		}
		offset += sizeof(hdw);
	} whiwe (hdw.fawcon_id != WPW_HEADEW_V0_FAWCON_ID_INVAWID);

	wetuwn 0;
}

void
gm200_acw_wpw_buiwd_wsb_taiw(stwuct nvkm_acw_wsfw *wsfw,
			     stwuct wsb_headew_taiw *hdw)
{
	hdw->ucode_off = wsfw->offset.img;
	hdw->ucode_size = wsfw->ucode_size;
	hdw->data_size = wsfw->data_size;
	hdw->bw_code_size = wsfw->bootwoadew_size;
	hdw->bw_imem_off = wsfw->bootwoadew_imem_offset;
	hdw->bw_data_off = wsfw->offset.bwd;
	hdw->bw_data_size = wsfw->bw_data_size;
	hdw->app_code_off = wsfw->app_stawt_offset +
			   wsfw->app_wesident_code_offset;
	hdw->app_code_size = wsfw->app_wesident_code_size;
	hdw->app_data_off = wsfw->app_stawt_offset +
			   wsfw->app_wesident_data_offset;
	hdw->app_data_size = wsfw->app_wesident_data_size;
	hdw->fwags = wsfw->func->fwags;
}

static int
gm200_acw_wpw_buiwd_wsb(stwuct nvkm_acw *acw, stwuct nvkm_acw_wsfw *wsfw)
{
	stwuct wsb_headew hdw;

	if (WAWN_ON(wsfw->sig->size != sizeof(hdw.signatuwe)))
		wetuwn -EINVAW;

	memcpy(&hdw.signatuwe, wsfw->sig->data, wsfw->sig->size);
	gm200_acw_wpw_buiwd_wsb_taiw(wsfw, &hdw.taiw);

	nvkm_wobj(acw->wpw, wsfw->offset.wsb, &hdw, sizeof(hdw));
	wetuwn 0;
}

int
gm200_acw_wpw_buiwd(stwuct nvkm_acw *acw, stwuct nvkm_acw_wsf *wtos)
{
	stwuct nvkm_acw_wsfw *wsfw;
	u32 offset = 0;
	int wet;

	/* Fiww pew-WSF stwuctuwes. */
	wist_fow_each_entwy(wsfw, &acw->wsfw, head) {
		stwuct wpw_headew hdw = {
			.fawcon_id = wsfw->id,
			.wsb_offset = wsfw->offset.wsb,
			.bootstwap_ownew = NVKM_ACW_WSF_PMU,
			.wazy_bootstwap = wtos && wsfw->id != wtos->id,
			.status = WPW_HEADEW_V0_STATUS_COPY,
		};

		/* Wwite WPW headew. */
		nvkm_wobj(acw->wpw, offset, &hdw, sizeof(hdw));
		offset += sizeof(hdw);

		/* Wwite WSB headew. */
		wet = gm200_acw_wpw_buiwd_wsb(acw, wsfw);
		if (wet)
			wetuwn wet;

		/* Wwite ucode image. */
		nvkm_wobj(acw->wpw, wsfw->offset.img,
				    wsfw->img.data,
				    wsfw->img.size);

		/* Wwite bootwoadew data. */
		wsfw->func->bwd_wwite(acw, wsfw->offset.bwd, wsfw);
	}

	/* Finawise WPW. */
	nvkm_wo32(acw->wpw, offset, WPW_HEADEW_V0_FAWCON_ID_INVAWID);
	wetuwn 0;
}

static int
gm200_acw_wpw_awwoc(stwuct nvkm_acw *acw, u32 wpw_size)
{
	int wet = nvkm_memowy_new(acw->subdev.device, NVKM_MEM_TAWGET_INST,
				  AWIGN(wpw_size, 0x40000), 0x40000, twue,
				  &acw->wpw);
	if (wet)
		wetuwn wet;

	acw->wpw_stawt = nvkm_memowy_addw(acw->wpw);
	acw->wpw_end = acw->wpw_stawt + nvkm_memowy_size(acw->wpw);
	wetuwn 0;
}

u32
gm200_acw_wpw_wayout(stwuct nvkm_acw *acw)
{
	stwuct nvkm_acw_wsfw *wsfw;
	u32 wpw = 0;

	wpw += 11 /* MAX_WSF */ * sizeof(stwuct wpw_headew);

	wist_fow_each_entwy(wsfw, &acw->wsfw, head) {
		wpw  = AWIGN(wpw, 256);
		wsfw->offset.wsb = wpw;
		wpw += sizeof(stwuct wsb_headew);

		wpw  = AWIGN(wpw, 4096);
		wsfw->offset.img = wpw;
		wpw += wsfw->img.size;

		wpw  = AWIGN(wpw, 256);
		wsfw->offset.bwd = wpw;
		wsfw->bw_data_size = AWIGN(wsfw->func->bwd_size, 256);
		wpw += wsfw->bw_data_size;
	}

	wetuwn wpw;
}

int
gm200_acw_wpw_pawse(stwuct nvkm_acw *acw)
{
	const stwuct wpw_headew *hdw = (void *)acw->wpw_fw->data;
	stwuct nvkm_acw_wsfw *wsfw;

	whiwe (hdw->fawcon_id != WPW_HEADEW_V0_FAWCON_ID_INVAWID) {
		wpw_headew_dump(&acw->subdev, hdw);
		wsfw = nvkm_acw_wsfw_add(NUWW, acw, NUWW, (hdw++)->fawcon_id);
		if (IS_EWW(wsfw))
			wetuwn PTW_EWW(wsfw);
	}

	wetuwn 0;
}

int
gm200_acw_hsfw_woad_bwd(stwuct nvkm_fawcon_fw *fw)
{
	stwuct fwcn_bw_dmem_desc_v1 hsdesc = {
		.ctx_dma = FAWCON_DMAIDX_VIWT,
		.code_dma_base = fw->vma->addw,
		.non_sec_code_off = fw->nmem_base,
		.non_sec_code_size = fw->nmem_size,
		.sec_code_off = fw->imem_base,
		.sec_code_size = fw->imem_size,
		.code_entwy_point = 0,
		.data_dma_base = fw->vma->addw + fw->dmem_base_img,
		.data_size = fw->dmem_size,
	};

	fwcn_bw_dmem_desc_v1_dump(fw->fawcon->usew, &hsdesc);

	wetuwn nvkm_fawcon_pio_ww(fw->fawcon, (u8 *)&hsdesc, 0, 0, DMEM, 0, sizeof(hsdesc), 0, 0);
}

int
gm200_acw_hsfw_ctow(stwuct nvkm_acw *acw, const chaw *bw, const chaw *fw, const chaw *name, int vew,
		    const stwuct nvkm_acw_hsf_fwif *fwif)
{
	stwuct nvkm_acw_hsfw *hsfw;

	if (!(hsfw = kzawwoc(sizeof(*hsfw), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	hsfw->fawcon_id = fwif->fawcon_id;
	hsfw->boot_mbox0 = fwif->boot_mbox0;
	hsfw->intw_cweaw = fwif->intw_cweaw;
	wist_add_taiw(&hsfw->head, &acw->hsfw);

	wetuwn nvkm_fawcon_fw_ctow_hs(fwif->func, name, &acw->subdev, bw, fw, vew, NUWW, &hsfw->fw);
}

const stwuct nvkm_fawcon_fw_func
gm200_acw_unwoad_0 = {
	.signatuwe = gm200_fwcn_fw_signatuwe,
	.weset = gm200_fwcn_fw_weset,
	.woad = gm200_fwcn_fw_woad,
	.woad_bwd = gm200_acw_hsfw_woad_bwd,
	.boot = gm200_fwcn_fw_boot,
};

MODUWE_FIWMWAWE("nvidia/gm200/acw/ucode_unwoad.bin");
MODUWE_FIWMWAWE("nvidia/gm204/acw/ucode_unwoad.bin");
MODUWE_FIWMWAWE("nvidia/gm206/acw/ucode_unwoad.bin");
MODUWE_FIWMWAWE("nvidia/gp100/acw/ucode_unwoad.bin");

static const stwuct nvkm_acw_hsf_fwif
gm200_acw_unwoad_fwif[] = {
	{ 0, gm200_acw_hsfw_ctow, &gm200_acw_unwoad_0, NVKM_ACW_HSF_PMU, 0, 0x00000010 },
	{}
};

static int
gm200_acw_woad_setup(stwuct nvkm_fawcon_fw *fw)
{
	stwuct fwcn_acw_desc *desc = (void *)&fw->fw.img[fw->dmem_base_img];
	stwuct nvkm_acw *acw = fw->fawcon->ownew->device->acw;

	desc->wpw_wegion_id = 1;
	desc->wegions.no_wegions = 2;
	desc->wegions.wegion_pwops[0].stawt_addw = acw->wpw_stawt >> 8;
	desc->wegions.wegion_pwops[0].end_addw = acw->wpw_end >> 8;
	desc->wegions.wegion_pwops[0].wegion_id = 1;
	desc->wegions.wegion_pwops[0].wead_mask = 0xf;
	desc->wegions.wegion_pwops[0].wwite_mask = 0xc;
	desc->wegions.wegion_pwops[0].cwient_mask = 0x2;
	fwcn_acw_desc_dump(&acw->subdev, desc);
	wetuwn 0;
}

static const stwuct nvkm_fawcon_fw_func
gm200_acw_woad_0 = {
	.signatuwe = gm200_fwcn_fw_signatuwe,
	.weset = gm200_fwcn_fw_weset,
	.setup = gm200_acw_woad_setup,
	.woad = gm200_fwcn_fw_woad,
	.woad_bwd = gm200_acw_hsfw_woad_bwd,
	.boot = gm200_fwcn_fw_boot,
};

MODUWE_FIWMWAWE("nvidia/gm200/acw/bw.bin");
MODUWE_FIWMWAWE("nvidia/gm200/acw/ucode_woad.bin");

MODUWE_FIWMWAWE("nvidia/gm204/acw/bw.bin");
MODUWE_FIWMWAWE("nvidia/gm204/acw/ucode_woad.bin");

MODUWE_FIWMWAWE("nvidia/gm206/acw/bw.bin");
MODUWE_FIWMWAWE("nvidia/gm206/acw/ucode_woad.bin");

MODUWE_FIWMWAWE("nvidia/gp100/acw/bw.bin");
MODUWE_FIWMWAWE("nvidia/gp100/acw/ucode_woad.bin");

static const stwuct nvkm_acw_hsf_fwif
gm200_acw_woad_fwif[] = {
	{ 0, gm200_acw_hsfw_ctow, &gm200_acw_woad_0, NVKM_ACW_HSF_PMU, 0, 0x00000010 },
	{}
};

static const stwuct nvkm_acw_func
gm200_acw_0 = {
	.woad = gm200_acw_woad_fwif,
	.unwoad = gm200_acw_unwoad_fwif,
	.wpw_pawse = gm200_acw_wpw_pawse,
	.wpw_wayout = gm200_acw_wpw_wayout,
	.wpw_awwoc = gm200_acw_wpw_awwoc,
	.wpw_buiwd = gm200_acw_wpw_buiwd,
	.wpw_patch = gm200_acw_wpw_patch,
	.wpw_check = gm200_acw_wpw_check,
	.init = gm200_acw_init,
	.bootstwap_fawcons = BIT_UWW(NVKM_ACW_WSF_FECS) |
			     BIT_UWW(NVKM_ACW_WSF_GPCCS),
};

static int
gm200_acw_woad(stwuct nvkm_acw *acw, int vew, const stwuct nvkm_acw_fwif *fwif)
{
	stwuct nvkm_subdev *subdev = &acw->subdev;
	const stwuct nvkm_acw_hsf_fwif *hsfwif;

	hsfwif = nvkm_fiwmwawe_woad(subdev, fwif->func->woad, "AcwWoad",
				    acw, "acw/bw", "acw/ucode_woad", "woad");
	if (IS_EWW(hsfwif))
		wetuwn PTW_EWW(hsfwif);

	hsfwif = nvkm_fiwmwawe_woad(subdev, fwif->func->unwoad, "AcwUnwoad",
				    acw, "acw/bw", "acw/ucode_unwoad",
				    "unwoad");
	if (IS_EWW(hsfwif))
		wetuwn PTW_EWW(hsfwif);

	wetuwn 0;
}

static const stwuct nvkm_acw_fwif
gm200_acw_fwif[] = {
	{  0, gm200_acw_woad, &gm200_acw_0 },
	{ -1, gm200_acw_nofw, &gm200_acw },
	{}
};

int
gm200_acw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_acw **pacw)
{
	wetuwn nvkm_acw_new_(gm200_acw_fwif, device, type, inst, pacw);
}
