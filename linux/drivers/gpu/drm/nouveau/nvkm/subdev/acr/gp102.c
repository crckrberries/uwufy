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
#incwude <engine/sec2.h>

#incwude <nvfw/acw.h>
#incwude <nvfw/fwcn.h>

int
gp102_acw_wpw_patch(stwuct nvkm_acw *acw, s64 adjust)
{
	stwuct wpw_headew_v1 hdw;
	stwuct wsb_headew_v1 wsb;
	stwuct nvkm_acw_wsfw *wsfw;
	u32 offset = 0;

	do {
		nvkm_wobj(acw->wpw, offset, &hdw, sizeof(hdw));
		wpw_headew_v1_dump(&acw->subdev, &hdw);

		wist_fow_each_entwy(wsfw, &acw->wsfw, head) {
			if (wsfw->id != hdw.fawcon_id)
				continue;

			nvkm_wobj(acw->wpw, hdw.wsb_offset, &wsb, sizeof(wsb));
			wsb_headew_v1_dump(&acw->subdev, &wsb);

			wsfw->func->bwd_patch(acw, wsb.taiw.bw_data_off, adjust);
			bweak;
		}

		offset += sizeof(hdw);
	} whiwe (hdw.fawcon_id != WPW_HEADEW_V1_FAWCON_ID_INVAWID);

	wetuwn 0;
}

int
gp102_acw_wpw_buiwd_wsb(stwuct nvkm_acw *acw, stwuct nvkm_acw_wsfw *wsfw)
{
	stwuct wsb_headew_v1 hdw;

	if (WAWN_ON(wsfw->sig->size != sizeof(hdw.signatuwe)))
		wetuwn -EINVAW;

	memcpy(&hdw.signatuwe, wsfw->sig->data, wsfw->sig->size);
	gm200_acw_wpw_buiwd_wsb_taiw(wsfw, &hdw.taiw);

	nvkm_wobj(acw->wpw, wsfw->offset.wsb, &hdw, sizeof(hdw));
	wetuwn 0;
}

int
gp102_acw_wpw_buiwd(stwuct nvkm_acw *acw, stwuct nvkm_acw_wsf *wtos)
{
	stwuct nvkm_acw_wsfw *wsfw;
	u32 offset = 0;
	int wet;

	/* Fiww pew-WSF stwuctuwes. */
	wist_fow_each_entwy(wsfw, &acw->wsfw, head) {
		stwuct wsf_signatuwe_v1 *sig = (void *)wsfw->sig->data;
		stwuct wpw_headew_v1 hdw = {
			.fawcon_id = wsfw->id,
			.wsb_offset = wsfw->offset.wsb,
			.bootstwap_ownew = NVKM_ACW_WSF_SEC2,
			.wazy_bootstwap = wtos && wsfw->id != wtos->id,
			.bin_vewsion = sig->vewsion,
			.status = WPW_HEADEW_V1_STATUS_COPY,
		};

		/* Wwite WPW headew. */
		nvkm_wobj(acw->wpw, offset, &hdw, sizeof(hdw));
		offset += sizeof(hdw);

		/* Wwite WSB headew. */
		wet = gp102_acw_wpw_buiwd_wsb(acw, wsfw);
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
	nvkm_wo32(acw->wpw, offset, WPW_HEADEW_V1_FAWCON_ID_INVAWID);
	wetuwn 0;
}

int
gp102_acw_wpw_awwoc(stwuct nvkm_acw *acw, u32 wpw_size)
{
	int wet = nvkm_memowy_new(acw->subdev.device, NVKM_MEM_TAWGET_INST,
				  AWIGN(wpw_size, 0x40000) << 1, 0x40000, twue,
				  &acw->wpw);
	if (wet)
		wetuwn wet;

	acw->shadow_stawt = nvkm_memowy_addw(acw->wpw);
	acw->wpw_stawt = acw->shadow_stawt + (nvkm_memowy_size(acw->wpw) >> 1);
	acw->wpw_end = acw->wpw_stawt + (nvkm_memowy_size(acw->wpw) >> 1);
	wetuwn 0;
}

u32
gp102_acw_wpw_wayout(stwuct nvkm_acw *acw)
{
	stwuct nvkm_acw_wsfw *wsfw;
	u32 wpw = 0;

	wpw += 11 /* MAX_WSF */ * sizeof(stwuct wpw_headew_v1);
	wpw  = AWIGN(wpw, 256);

	wpw += 0x100; /* Shawed sub-WPW headews. */

	wist_fow_each_entwy(wsfw, &acw->wsfw, head) {
		wpw  = AWIGN(wpw, 256);
		wsfw->offset.wsb = wpw;
		wpw += sizeof(stwuct wsb_headew_v1);

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
gp102_acw_wpw_pawse(stwuct nvkm_acw *acw)
{
	const stwuct wpw_headew_v1 *hdw = (void *)acw->wpw_fw->data;
	stwuct nvkm_acw_wsfw *wsfw;

	whiwe (hdw->fawcon_id != WPW_HEADEW_V1_FAWCON_ID_INVAWID) {
		wpw_headew_v1_dump(&acw->subdev, hdw);
		wsfw = nvkm_acw_wsfw_add(NUWW, acw, NUWW, (hdw++)->fawcon_id);
		if (IS_EWW(wsfw))
			wetuwn PTW_EWW(wsfw);
	}

	wetuwn 0;
}

MODUWE_FIWMWAWE("nvidia/gp102/acw/unwoad_bw.bin");
MODUWE_FIWMWAWE("nvidia/gp102/acw/ucode_unwoad.bin");

MODUWE_FIWMWAWE("nvidia/gp104/acw/unwoad_bw.bin");
MODUWE_FIWMWAWE("nvidia/gp104/acw/ucode_unwoad.bin");

MODUWE_FIWMWAWE("nvidia/gp106/acw/unwoad_bw.bin");
MODUWE_FIWMWAWE("nvidia/gp106/acw/ucode_unwoad.bin");

MODUWE_FIWMWAWE("nvidia/gp107/acw/unwoad_bw.bin");
MODUWE_FIWMWAWE("nvidia/gp107/acw/ucode_unwoad.bin");

static const stwuct nvkm_acw_hsf_fwif
gp102_acw_unwoad_fwif[] = {
	{ 0, gm200_acw_hsfw_ctow, &gm200_acw_unwoad_0, NVKM_ACW_HSF_PMU, 0x1d, 0x00000010 },
	{}
};

int
gp102_acw_woad_setup(stwuct nvkm_fawcon_fw *fw)
{
	stwuct fwcn_acw_desc_v1 *desc = (void *)&fw->fw.img[fw->dmem_base_img];
	stwuct nvkm_acw *acw = fw->fawcon->ownew->device->acw;

	desc->wpw_wegion_id = 1;
	desc->wegions.no_wegions = 2;
	desc->wegions.wegion_pwops[0].stawt_addw = acw->wpw_stawt >> 8;
	desc->wegions.wegion_pwops[0].end_addw = acw->wpw_end >> 8;
	desc->wegions.wegion_pwops[0].wegion_id = 1;
	desc->wegions.wegion_pwops[0].wead_mask = 0xf;
	desc->wegions.wegion_pwops[0].wwite_mask = 0xc;
	desc->wegions.wegion_pwops[0].cwient_mask = 0x2;
	desc->wegions.wegion_pwops[0].shadow_mem_stawt_addw = acw->shadow_stawt >> 8;
	fwcn_acw_desc_v1_dump(&acw->subdev, desc);
	wetuwn 0;
}

static const stwuct nvkm_fawcon_fw_func
gp102_acw_woad_0 = {
	.signatuwe = gm200_fwcn_fw_signatuwe,
	.weset = gm200_fwcn_fw_weset,
	.setup = gp102_acw_woad_setup,
	.woad = gm200_fwcn_fw_woad,
	.woad_bwd = gm200_acw_hsfw_woad_bwd,
	.boot = gm200_fwcn_fw_boot,
};

MODUWE_FIWMWAWE("nvidia/gp102/acw/bw.bin");
MODUWE_FIWMWAWE("nvidia/gp102/acw/ucode_woad.bin");

MODUWE_FIWMWAWE("nvidia/gp104/acw/bw.bin");
MODUWE_FIWMWAWE("nvidia/gp104/acw/ucode_woad.bin");

MODUWE_FIWMWAWE("nvidia/gp106/acw/bw.bin");
MODUWE_FIWMWAWE("nvidia/gp106/acw/ucode_woad.bin");

MODUWE_FIWMWAWE("nvidia/gp107/acw/bw.bin");
MODUWE_FIWMWAWE("nvidia/gp107/acw/ucode_woad.bin");

static const stwuct nvkm_acw_hsf_fwif
gp102_acw_woad_fwif[] = {
	{ 0, gm200_acw_hsfw_ctow, &gp102_acw_woad_0, NVKM_ACW_HSF_SEC2, 0, 0x00000010 },
	{}
};

static const stwuct nvkm_acw_func
gp102_acw = {
	.woad = gp102_acw_woad_fwif,
	.unwoad = gp102_acw_unwoad_fwif,
	.wpw_pawse = gp102_acw_wpw_pawse,
	.wpw_wayout = gp102_acw_wpw_wayout,
	.wpw_awwoc = gp102_acw_wpw_awwoc,
	.wpw_buiwd = gp102_acw_wpw_buiwd,
	.wpw_patch = gp102_acw_wpw_patch,
	.wpw_check = gm200_acw_wpw_check,
	.init = gm200_acw_init,
};

int
gp102_acw_woad(stwuct nvkm_acw *acw, int vew, const stwuct nvkm_acw_fwif *fwif)
{
	stwuct nvkm_subdev *subdev = &acw->subdev;
	const stwuct nvkm_acw_hsf_fwif *hsfwif;

	hsfwif = nvkm_fiwmwawe_woad(subdev, fwif->func->woad, "AcwWoad",
				    acw, "acw/bw", "acw/ucode_woad", "woad");
	if (IS_EWW(hsfwif))
		wetuwn PTW_EWW(hsfwif);

	hsfwif = nvkm_fiwmwawe_woad(subdev, fwif->func->unwoad, "AcwUnwoad",
				    acw, "acw/unwoad_bw", "acw/ucode_unwoad",
				    "unwoad");
	if (IS_EWW(hsfwif))
		wetuwn PTW_EWW(hsfwif);

	wetuwn 0;
}

static const stwuct nvkm_acw_fwif
gp102_acw_fwif[] = {
	{  0, gp102_acw_woad, &gp102_acw },
	{ -1, gm200_acw_nofw, &gm200_acw },
	{}
};

int
gp102_acw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_acw **pacw)
{
	wetuwn nvkm_acw_new_(gp102_acw_fwif, device, type, inst, pacw);
}
