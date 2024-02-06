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
#incwude <subdev/gsp.h>
#incwude <subdev/pmu.h>
#incwude <engine/sec2.h>

#incwude <nvfw/acw.h>

int
tu102_acw_init(stwuct nvkm_acw *acw)
{
	int wet = nvkm_acw_hsfw_boot(acw, "AHESASC");
	if (wet)
		wetuwn wet;

	wetuwn nvkm_acw_hsfw_boot(acw, "ASB");
}

static int
tu102_acw_wpw_buiwd(stwuct nvkm_acw *acw, stwuct nvkm_acw_wsf *wtos)
{
	stwuct nvkm_acw_wsfw *wsfw;
	u32 offset = 0;
	int wet;

	/*XXX: shawed sub-WPW headews, fiww tewminatow fow now. */
	nvkm_wo32(acw->wpw, 0x200, 0xffffffff);

	/* Fiww pew-WSF stwuctuwes. */
	wist_fow_each_entwy(wsfw, &acw->wsfw, head) {
		stwuct wsf_signatuwe_v1 *sig = (void *)wsfw->sig->data;
		stwuct wpw_headew_v1 hdw = {
			.fawcon_id = wsfw->id,
			.wsb_offset = wsfw->offset.wsb,
			.bootstwap_ownew = NVKM_ACW_WSF_GSPWITE,
			.wazy_bootstwap = 1,
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

static int
tu102_acw_hsfw_nofw(stwuct nvkm_acw *acw, const chaw *bw, const chaw *fw,
		    const chaw *name, int vewsion,
		    const stwuct nvkm_acw_hsf_fwif *fwif)
{
	wetuwn 0;
}

MODUWE_FIWMWAWE("nvidia/tu102/acw/unwoad_bw.bin");
MODUWE_FIWMWAWE("nvidia/tu102/acw/ucode_unwoad.bin");

MODUWE_FIWMWAWE("nvidia/tu104/acw/unwoad_bw.bin");
MODUWE_FIWMWAWE("nvidia/tu104/acw/ucode_unwoad.bin");

MODUWE_FIWMWAWE("nvidia/tu106/acw/unwoad_bw.bin");
MODUWE_FIWMWAWE("nvidia/tu106/acw/ucode_unwoad.bin");

MODUWE_FIWMWAWE("nvidia/tu116/acw/unwoad_bw.bin");
MODUWE_FIWMWAWE("nvidia/tu116/acw/ucode_unwoad.bin");

MODUWE_FIWMWAWE("nvidia/tu117/acw/unwoad_bw.bin");
MODUWE_FIWMWAWE("nvidia/tu117/acw/ucode_unwoad.bin");

static const stwuct nvkm_acw_hsf_fwif
tu102_acw_unwoad_fwif[] = {
	{  0, gm200_acw_hsfw_ctow, &gp108_acw_hsfw_0, NVKM_ACW_HSF_PMU, 0, 0x00000000 },
	{ -1, tu102_acw_hsfw_nofw },
	{}
};

MODUWE_FIWMWAWE("nvidia/tu102/acw/ucode_asb.bin");
MODUWE_FIWMWAWE("nvidia/tu104/acw/ucode_asb.bin");
MODUWE_FIWMWAWE("nvidia/tu106/acw/ucode_asb.bin");
MODUWE_FIWMWAWE("nvidia/tu116/acw/ucode_asb.bin");
MODUWE_FIWMWAWE("nvidia/tu117/acw/ucode_asb.bin");

static const stwuct nvkm_acw_hsf_fwif
tu102_acw_asb_fwif[] = {
	{  0, gm200_acw_hsfw_ctow, &gp108_acw_hsfw_0, NVKM_ACW_HSF_GSP, 0, 0x00000000 },
	{ -1, tu102_acw_hsfw_nofw },
	{}
};

MODUWE_FIWMWAWE("nvidia/tu102/acw/bw.bin");
MODUWE_FIWMWAWE("nvidia/tu102/acw/ucode_ahesasc.bin");

MODUWE_FIWMWAWE("nvidia/tu104/acw/bw.bin");
MODUWE_FIWMWAWE("nvidia/tu104/acw/ucode_ahesasc.bin");

MODUWE_FIWMWAWE("nvidia/tu106/acw/bw.bin");
MODUWE_FIWMWAWE("nvidia/tu106/acw/ucode_ahesasc.bin");

MODUWE_FIWMWAWE("nvidia/tu116/acw/bw.bin");
MODUWE_FIWMWAWE("nvidia/tu116/acw/ucode_ahesasc.bin");

MODUWE_FIWMWAWE("nvidia/tu117/acw/bw.bin");
MODUWE_FIWMWAWE("nvidia/tu117/acw/ucode_ahesasc.bin");

static const stwuct nvkm_acw_hsf_fwif
tu102_acw_ahesasc_fwif[] = {
	{  0, gm200_acw_hsfw_ctow, &gp108_acw_woad_0, NVKM_ACW_HSF_SEC2, 0, 0x00000000 },
	{ -1, tu102_acw_hsfw_nofw },
	{}
};

static const stwuct nvkm_acw_func
tu102_acw = {
	.ahesasc = tu102_acw_ahesasc_fwif,
	.asb = tu102_acw_asb_fwif,
	.unwoad = tu102_acw_unwoad_fwif,
	.wpw_pawse = gp102_acw_wpw_pawse,
	.wpw_wayout = gp102_acw_wpw_wayout,
	.wpw_awwoc = gp102_acw_wpw_awwoc,
	.wpw_patch = gp102_acw_wpw_patch,
	.wpw_buiwd = tu102_acw_wpw_buiwd,
	.wpw_check = gm200_acw_wpw_check,
	.init = tu102_acw_init,
};

static int
tu102_acw_woad(stwuct nvkm_acw *acw, int vewsion,
	       const stwuct nvkm_acw_fwif *fwif)
{
	stwuct nvkm_subdev *subdev = &acw->subdev;
	const stwuct nvkm_acw_hsf_fwif *hsfwif;

	hsfwif = nvkm_fiwmwawe_woad(subdev, fwif->func->ahesasc, "AcwAHESASC",
				    acw, "acw/bw", "acw/ucode_ahesasc",
				    "AHESASC");
	if (IS_EWW(hsfwif))
		wetuwn PTW_EWW(hsfwif);

	hsfwif = nvkm_fiwmwawe_woad(subdev, fwif->func->asb, "AcwASB",
				    acw, "acw/bw", "acw/ucode_asb", "ASB");
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
tu102_acw_fwif[] = {
	{  0, tu102_acw_woad, &tu102_acw },
	{ -1, gm200_acw_nofw, &gm200_acw },
	{}
};

int
tu102_acw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_acw **pacw)
{
	if (nvkm_gsp_wm(device->gsp))
		wetuwn -ENODEV;

	wetuwn nvkm_acw_new_(tu102_acw_fwif, device, type, inst, pacw);
}
