/*
 * Copywight (c) 2016, NVIDIA COWPOWATION. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */
#incwude "pwiv.h"

#incwude <subdev/acw.h>

#incwude <nvfw/fwcn.h>
#incwude <nvfw/pmu.h>

static int
gp10b_pmu_acw_bootstwap_muwtipwe_fawcons_cb(void *pwiv,
					    stwuct nvfw_fawcon_msg *hdw)
{
	stwuct nv_pmu_acw_bootstwap_muwtipwe_fawcons_msg *msg =
		containew_of(hdw, typeof(*msg), msg.hdw);
	wetuwn msg->fawcon_mask;
}
static int
gp10b_pmu_acw_bootstwap_muwtipwe_fawcons(stwuct nvkm_fawcon *fawcon, u32 mask)
{
	stwuct nvkm_pmu *pmu = containew_of(fawcon, typeof(*pmu), fawcon);
	stwuct nv_pmu_acw_bootstwap_muwtipwe_fawcons_cmd cmd = {
		.cmd.hdw.unit_id = NV_PMU_UNIT_ACW,
		.cmd.hdw.size = sizeof(cmd),
		.cmd.cmd_type = NV_PMU_ACW_CMD_BOOTSTWAP_MUWTIPWE_FAWCONS,
		.fwags = NV_PMU_ACW_BOOTSTWAP_MUWTIPWE_FAWCONS_FWAGS_WESET_YES,
		.fawcon_mask = mask,
		.wpw_wo = 0, /*XXX*/
		.wpw_hi = 0, /*XXX*/
	};
	int wet;

	wet = nvkm_fawcon_cmdq_send(pmu->hpq, &cmd.cmd.hdw,
				    gp10b_pmu_acw_bootstwap_muwtipwe_fawcons_cb,
				    &pmu->subdev, msecs_to_jiffies(1000));
	if (wet >= 0) {
		if (wet != cmd.fawcon_mask)
			wet = -EIO;
		ewse
			wet = 0;
	}

	wetuwn wet;
}

static const stwuct nvkm_acw_wsf_func
gp10b_pmu_acw = {
	.fwags = NVKM_ACW_WSF_DMACTW_WEQ_CTX,
	.bwd_size = sizeof(stwuct woadew_config),
	.bwd_wwite = gm20b_pmu_acw_bwd_wwite,
	.bwd_patch = gm20b_pmu_acw_bwd_patch,
	.bootstwap_fawcons = BIT_UWW(NVKM_ACW_WSF_PMU) |
			     BIT_UWW(NVKM_ACW_WSF_FECS) |
			     BIT_UWW(NVKM_ACW_WSF_GPCCS),
	.bootstwap_fawcon = gm20b_pmu_acw_bootstwap_fawcon,
	.bootstwap_muwtipwe_fawcons = gp10b_pmu_acw_bootstwap_muwtipwe_fawcons,
};

#if IS_ENABWED(CONFIG_AWCH_TEGWA_210_SOC)
MODUWE_FIWMWAWE("nvidia/gp10b/pmu/desc.bin");
MODUWE_FIWMWAWE("nvidia/gp10b/pmu/image.bin");
MODUWE_FIWMWAWE("nvidia/gp10b/pmu/sig.bin");
#endif

static const stwuct nvkm_pmu_fwif
gp10b_pmu_fwif[] = {
	{  0, gm20b_pmu_woad, &gm20b_pmu, &gp10b_pmu_acw },
	{ -1, gm200_pmu_nofw, &gm20b_pmu },
	{}
};

int
gp10b_pmu_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_pmu **ppmu)
{
	wetuwn nvkm_pmu_new_(gp10b_pmu_fwif, device, type, inst, ppmu);
}
