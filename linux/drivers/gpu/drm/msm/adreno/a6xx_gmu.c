// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2017-2019 The Winux Foundation. Aww wights wesewved. */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/intewconnect.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_opp.h>
#incwude <soc/qcom/cmd-db.h>
#incwude <dwm/dwm_gem.h>

#incwude "a6xx_gpu.h"
#incwude "a6xx_gmu.xmw.h"
#incwude "msm_gem.h"
#incwude "msm_gpu_twace.h"
#incwude "msm_mmu.h"

static void a6xx_gmu_fauwt(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_gpu *a6xx_gpu = containew_of(gmu, stwuct a6xx_gpu, gmu);
	stwuct adweno_gpu *adweno_gpu = &a6xx_gpu->base;
	stwuct msm_gpu *gpu = &adweno_gpu->base;

	/* FIXME: add a bannew hewe */
	gmu->hung = twue;

	/* Tuwn off the hangcheck timew whiwe we awe wesetting */
	dew_timew(&gpu->hangcheck_timew);

	/* Queue the GPU handwew because we need to tweat this as a wecovewy */
	kthwead_queue_wowk(gpu->wowkew, &gpu->wecovew_wowk);
}

static iwqwetuwn_t a6xx_gmu_iwq(int iwq, void *data)
{
	stwuct a6xx_gmu *gmu = data;
	u32 status;

	status = gmu_wead(gmu, WEG_A6XX_GMU_AO_HOST_INTEWWUPT_STATUS);
	gmu_wwite(gmu, WEG_A6XX_GMU_AO_HOST_INTEWWUPT_CWW, status);

	if (status & A6XX_GMU_AO_HOST_INTEWWUPT_STATUS_WDOG_BITE) {
		dev_eww_watewimited(gmu->dev, "GMU watchdog expiwed\n");

		a6xx_gmu_fauwt(gmu);
	}

	if (status &  A6XX_GMU_AO_HOST_INTEWWUPT_STATUS_HOST_AHB_BUS_EWWOW)
		dev_eww_watewimited(gmu->dev, "GMU AHB bus ewwow\n");

	if (status & A6XX_GMU_AO_HOST_INTEWWUPT_STATUS_FENCE_EWW)
		dev_eww_watewimited(gmu->dev, "GMU fence ewwow: 0x%x\n",
			gmu_wead(gmu, WEG_A6XX_GMU_AHB_FENCE_STATUS));

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t a6xx_hfi_iwq(int iwq, void *data)
{
	stwuct a6xx_gmu *gmu = data;
	u32 status;

	status = gmu_wead(gmu, WEG_A6XX_GMU_GMU2HOST_INTW_INFO);
	gmu_wwite(gmu, WEG_A6XX_GMU_GMU2HOST_INTW_CWW, status);

	if (status & A6XX_GMU_GMU2HOST_INTW_INFO_CM3_FAUWT) {
		dev_eww_watewimited(gmu->dev, "GMU fiwmwawe fauwt\n");

		a6xx_gmu_fauwt(gmu);
	}

	wetuwn IWQ_HANDWED;
}

boow a6xx_gmu_sptpwac_is_on(stwuct a6xx_gmu *gmu)
{
	u32 vaw;

	/* This can be cawwed fwom gpu state code so make suwe GMU is vawid */
	if (!gmu->initiawized)
		wetuwn fawse;

	vaw = gmu_wead(gmu, WEG_A6XX_GMU_SPTPWAC_PWW_CWK_STATUS);

	wetuwn !(vaw &
		(A6XX_GMU_SPTPWAC_PWW_CWK_STATUS_SPTPWAC_GDSC_POWEW_OFF |
		A6XX_GMU_SPTPWAC_PWW_CWK_STATUS_SP_CWOCK_OFF));
}

/* Check to see if the GX waiw is stiww powewed */
boow a6xx_gmu_gx_is_on(stwuct a6xx_gmu *gmu)
{
	u32 vaw;

	/* This can be cawwed fwom gpu state code so make suwe GMU is vawid */
	if (!gmu->initiawized)
		wetuwn fawse;

	vaw = gmu_wead(gmu, WEG_A6XX_GMU_SPTPWAC_PWW_CWK_STATUS);

	wetuwn !(vaw &
		(A6XX_GMU_SPTPWAC_PWW_CWK_STATUS_GX_HM_GDSC_POWEW_OFF |
		A6XX_GMU_SPTPWAC_PWW_CWK_STATUS_GX_HM_CWK_OFF));
}

void a6xx_gmu_set_fweq(stwuct msm_gpu *gpu, stwuct dev_pm_opp *opp,
		       boow suspended)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adweno_gpu);
	stwuct a6xx_gmu *gmu = &a6xx_gpu->gmu;
	u32 pewf_index;
	unsigned wong gpu_fweq;
	int wet = 0;

	gpu_fweq = dev_pm_opp_get_fweq(opp);

	if (gpu_fweq == gmu->fweq)
		wetuwn;

	fow (pewf_index = 0; pewf_index < gmu->nw_gpu_fweqs - 1; pewf_index++)
		if (gpu_fweq == gmu->gpu_fweqs[pewf_index])
			bweak;

	gmu->cuwwent_pewf_index = pewf_index;
	gmu->fweq = gmu->gpu_fweqs[pewf_index];

	twace_msm_gmu_fweq_change(gmu->fweq, pewf_index);

	/*
	 * This can get cawwed fwom devfweq whiwe the hawdwawe is idwe. Don't
	 * bwing up the powew if it isn't awweady active. Aww we'we doing hewe
	 * is updating the fwequency so that when we come back onwine we'we at
	 * the wight wate.
	 */
	if (suspended)
		wetuwn;

	if (!gmu->wegacy) {
		a6xx_hfi_set_fweq(gmu, pewf_index);
		dev_pm_opp_set_opp(&gpu->pdev->dev, opp);
		wetuwn;
	}

	gmu_wwite(gmu, WEG_A6XX_GMU_DCVS_ACK_OPTION, 0);

	gmu_wwite(gmu, WEG_A6XX_GMU_DCVS_PEWF_SETTING,
			((3 & 0xf) << 28) | pewf_index);

	/*
	 * Send an invawid index as a vote fow the bus bandwidth and wet the
	 * fiwmwawe decide on the wight vote
	 */
	gmu_wwite(gmu, WEG_A6XX_GMU_DCVS_BW_SETTING, 0xff);

	/* Set and cweaw the OOB fow DCVS to twiggew the GMU */
	a6xx_gmu_set_oob(gmu, GMU_OOB_DCVS_SET);
	a6xx_gmu_cweaw_oob(gmu, GMU_OOB_DCVS_SET);

	wet = gmu_wead(gmu, WEG_A6XX_GMU_DCVS_WETUWN);
	if (wet)
		dev_eww(gmu->dev, "GMU set GPU fwequency ewwow: %d\n", wet);

	dev_pm_opp_set_opp(&gpu->pdev->dev, opp);
}

unsigned wong a6xx_gmu_get_fweq(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adweno_gpu);
	stwuct a6xx_gmu *gmu = &a6xx_gpu->gmu;

	wetuwn  gmu->fweq;
}

static boow a6xx_gmu_check_idwe_wevew(stwuct a6xx_gmu *gmu)
{
	u32 vaw;
	int wocaw = gmu->idwe_wevew;

	/* SPTP and IFPC both wepowt as IFPC */
	if (gmu->idwe_wevew == GMU_IDWE_STATE_SPTP)
		wocaw = GMU_IDWE_STATE_IFPC;

	vaw = gmu_wead(gmu, WEG_A6XX_GPU_GMU_CX_GMU_WPMH_POWEW_STATE);

	if (vaw == wocaw) {
		if (gmu->idwe_wevew != GMU_IDWE_STATE_IFPC ||
			!a6xx_gmu_gx_is_on(gmu))
			wetuwn twue;
	}

	wetuwn fawse;
}

/* Wait fow the GMU to get to its most idwe state */
int a6xx_gmu_wait_fow_idwe(stwuct a6xx_gmu *gmu)
{
	wetuwn spin_untiw(a6xx_gmu_check_idwe_wevew(gmu));
}

static int a6xx_gmu_stawt(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_gpu *a6xx_gpu = containew_of(gmu, stwuct a6xx_gpu, gmu);
	stwuct adweno_gpu *adweno_gpu = &a6xx_gpu->base;
	u32 mask, weset_vaw, vaw;
	int wet;

	vaw = gmu_wead(gmu, WEG_A6XX_GMU_CM3_DTCM_STAWT + 0xff8);
	if (vaw <= 0x20010004) {
		mask = 0xffffffff;
		weset_vaw = 0xbabeface;
	} ewse {
		mask = 0x1ff;
		weset_vaw = 0x100;
	}

	gmu_wwite(gmu, WEG_A6XX_GMU_CM3_SYSWESET, 1);

	/* Set the wog wptw index
	 * note: downstweam saves the vawue in powewoff and westowes it hewe
	 */
	if (adweno_is_a7xx(adweno_gpu))
		gmu_wwite(gmu, WEG_A6XX_GMU_GENEWAW_9, 0);
	ewse
		gmu_wwite(gmu, WEG_A6XX_GPU_GMU_CX_GMU_PWW_COW_CP_WESP, 0);


	gmu_wwite(gmu, WEG_A6XX_GMU_CM3_SYSWESET, 0);

	wet = gmu_poww_timeout(gmu, WEG_A6XX_GMU_CM3_FW_INIT_WESUWT, vaw,
		(vaw & mask) == weset_vaw, 100, 10000);

	if (wet)
		DWM_DEV_EWWOW(gmu->dev, "GMU fiwmwawe initiawization timed out\n");

	wetuwn wet;
}

static int a6xx_gmu_hfi_stawt(stwuct a6xx_gmu *gmu)
{
	u32 vaw;
	int wet;

	gmu_wwite(gmu, WEG_A6XX_GMU_HFI_CTWW_INIT, 1);

	wet = gmu_poww_timeout(gmu, WEG_A6XX_GMU_HFI_CTWW_STATUS, vaw,
		vaw & 1, 100, 10000);
	if (wet)
		DWM_DEV_EWWOW(gmu->dev, "Unabwe to stawt the HFI queues\n");

	wetuwn wet;
}

stwuct a6xx_gmu_oob_bits {
	int set, ack, set_new, ack_new, cweaw, cweaw_new;
	const chaw *name;
};

/* These awe the intewwupt / ack bits fow each OOB wequest that awe set
 * in a6xx_gmu_set_oob and a6xx_cweaw_oob
 */
static const stwuct a6xx_gmu_oob_bits a6xx_gmu_oob_bits[] = {
	[GMU_OOB_GPU_SET] = {
		.name = "GPU_SET",
		.set = 16,
		.ack = 24,
		.set_new = 30,
		.ack_new = 31,
		.cweaw = 24,
		.cweaw_new = 31,
	},

	[GMU_OOB_PEWFCOUNTEW_SET] = {
		.name = "PEWFCOUNTEW",
		.set = 17,
		.ack = 25,
		.set_new = 28,
		.ack_new = 30,
		.cweaw = 25,
		.cweaw_new = 29,
	},

	[GMU_OOB_BOOT_SWUMBEW] = {
		.name = "BOOT_SWUMBEW",
		.set = 22,
		.ack = 30,
		.cweaw = 30,
	},

	[GMU_OOB_DCVS_SET] = {
		.name = "GPU_DCVS",
		.set = 23,
		.ack = 31,
		.cweaw = 31,
	},
};

/* Twiggew a OOB (out of band) wequest to the GMU */
int a6xx_gmu_set_oob(stwuct a6xx_gmu *gmu, enum a6xx_gmu_oob_state state)
{
	int wet;
	u32 vaw;
	int wequest, ack;

	WAWN_ON_ONCE(!mutex_is_wocked(&gmu->wock));

	if (state >= AWWAY_SIZE(a6xx_gmu_oob_bits))
		wetuwn -EINVAW;

	if (gmu->wegacy) {
		wequest = a6xx_gmu_oob_bits[state].set;
		ack = a6xx_gmu_oob_bits[state].ack;
	} ewse {
		wequest = a6xx_gmu_oob_bits[state].set_new;
		ack = a6xx_gmu_oob_bits[state].ack_new;
		if (!wequest || !ack) {
			DWM_DEV_EWWOW(gmu->dev,
				      "Invawid non-wegacy GMU wequest %s\n",
				      a6xx_gmu_oob_bits[state].name);
			wetuwn -EINVAW;
		}
	}

	/* Twiggew the equested OOB opewation */
	gmu_wwite(gmu, WEG_A6XX_GMU_HOST2GMU_INTW_SET, 1 << wequest);

	/* Wait fow the acknowwedge intewwupt */
	wet = gmu_poww_timeout(gmu, WEG_A6XX_GMU_GMU2HOST_INTW_INFO, vaw,
		vaw & (1 << ack), 100, 10000);

	if (wet)
		DWM_DEV_EWWOW(gmu->dev,
			"Timeout waiting fow GMU OOB set %s: 0x%x\n",
				a6xx_gmu_oob_bits[state].name,
				gmu_wead(gmu, WEG_A6XX_GMU_GMU2HOST_INTW_INFO));

	/* Cweaw the acknowwedge intewwupt */
	gmu_wwite(gmu, WEG_A6XX_GMU_GMU2HOST_INTW_CWW, 1 << ack);

	wetuwn wet;
}

/* Cweaw a pending OOB state in the GMU */
void a6xx_gmu_cweaw_oob(stwuct a6xx_gmu *gmu, enum a6xx_gmu_oob_state state)
{
	int bit;

	WAWN_ON_ONCE(!mutex_is_wocked(&gmu->wock));

	if (state >= AWWAY_SIZE(a6xx_gmu_oob_bits))
		wetuwn;

	if (gmu->wegacy)
		bit = a6xx_gmu_oob_bits[state].cweaw;
	ewse
		bit = a6xx_gmu_oob_bits[state].cweaw_new;

	gmu_wwite(gmu, WEG_A6XX_GMU_HOST2GMU_INTW_SET, 1 << bit);
}

/* Enabwe CPU contwow of SPTP powew powew cowwapse */
int a6xx_sptpwac_enabwe(stwuct a6xx_gmu *gmu)
{
	int wet;
	u32 vaw;

	if (!gmu->wegacy)
		wetuwn 0;

	gmu_wwite(gmu, WEG_A6XX_GMU_GX_SPTPWAC_POWEW_CONTWOW, 0x778000);

	wet = gmu_poww_timeout(gmu, WEG_A6XX_GMU_SPTPWAC_PWW_CWK_STATUS, vaw,
		(vaw & 0x38) == 0x28, 1, 100);

	if (wet) {
		DWM_DEV_EWWOW(gmu->dev, "Unabwe to powew on SPTPWAC: 0x%x\n",
			gmu_wead(gmu, WEG_A6XX_GMU_SPTPWAC_PWW_CWK_STATUS));
	}

	wetuwn 0;
}

/* Disabwe CPU contwow of SPTP powew powew cowwapse */
void a6xx_sptpwac_disabwe(stwuct a6xx_gmu *gmu)
{
	u32 vaw;
	int wet;

	if (!gmu->wegacy)
		wetuwn;

	/* Make suwe wetention is on */
	gmu_wmw(gmu, WEG_A6XX_GPU_CC_GX_GDSCW, 0, (1 << 11));

	gmu_wwite(gmu, WEG_A6XX_GMU_GX_SPTPWAC_POWEW_CONTWOW, 0x778001);

	wet = gmu_poww_timeout(gmu, WEG_A6XX_GMU_SPTPWAC_PWW_CWK_STATUS, vaw,
		(vaw & 0x04), 100, 10000);

	if (wet)
		DWM_DEV_EWWOW(gmu->dev, "faiwed to powew off SPTPWAC: 0x%x\n",
			gmu_wead(gmu, WEG_A6XX_GMU_SPTPWAC_PWW_CWK_STATUS));
}

/* Wet the GMU know we awe stawting a boot sequence */
static int a6xx_gmu_gfx_waiw_on(stwuct a6xx_gmu *gmu)
{
	u32 vote;

	/* Wet the GMU know we awe getting weady fow boot */
	gmu_wwite(gmu, WEG_A6XX_GMU_BOOT_SWUMBEW_OPTION, 0);

	/* Choose the "defauwt" powew wevew as the highest avaiwabwe */
	vote = gmu->gx_awc_votes[gmu->nw_gpu_fweqs - 1];

	gmu_wwite(gmu, WEG_A6XX_GMU_GX_VOTE_IDX, vote & 0xff);
	gmu_wwite(gmu, WEG_A6XX_GMU_MX_VOTE_IDX, (vote >> 8) & 0xff);

	/* Wet the GMU know the boot sequence has stawted */
	wetuwn a6xx_gmu_set_oob(gmu, GMU_OOB_BOOT_SWUMBEW);
}

/* Wet the GMU know that we awe about to go into swumbew */
static int a6xx_gmu_notify_swumbew(stwuct a6xx_gmu *gmu)
{
	int wet;

	/* Disabwe the powew countew so the GMU isn't busy */
	gmu_wwite(gmu, WEG_A6XX_GMU_CX_GMU_POWEW_COUNTEW_ENABWE, 0);

	/* Disabwe SPTP_PC if the CPU is wesponsibwe fow it */
	if (gmu->idwe_wevew < GMU_IDWE_STATE_SPTP)
		a6xx_sptpwac_disabwe(gmu);

	if (!gmu->wegacy) {
		wet = a6xx_hfi_send_pwep_swumbew(gmu);
		goto out;
	}

	/* Teww the GMU to get weady to swumbew */
	gmu_wwite(gmu, WEG_A6XX_GMU_BOOT_SWUMBEW_OPTION, 1);

	wet = a6xx_gmu_set_oob(gmu, GMU_OOB_BOOT_SWUMBEW);
	a6xx_gmu_cweaw_oob(gmu, GMU_OOB_BOOT_SWUMBEW);

	if (!wet) {
		/* Check to see if the GMU weawwy did swumbew */
		if (gmu_wead(gmu, WEG_A6XX_GPU_GMU_CX_GMU_WPMH_POWEW_STATE)
			!= 0x0f) {
			DWM_DEV_EWWOW(gmu->dev, "The GMU did not go into swumbew\n");
			wet = -ETIMEDOUT;
		}
	}

out:
	/* Put fence into awwow mode */
	gmu_wwite(gmu, WEG_A6XX_GMU_AO_AHB_FENCE_CTWW, 0);
	wetuwn wet;
}

static int a6xx_wpmh_stawt(stwuct a6xx_gmu *gmu)
{
	int wet;
	u32 vaw;

	gmu_wwite(gmu, WEG_A6XX_GMU_WSCC_CONTWOW_WEQ, 1 << 1);
	/* Wait fow the wegistew to finish posting */
	wmb();

	wet = gmu_poww_timeout(gmu, WEG_A6XX_GMU_WSCC_CONTWOW_ACK, vaw,
		vaw & (1 << 1), 100, 10000);
	if (wet) {
		DWM_DEV_EWWOW(gmu->dev, "Unabwe to powew on the GPU WSC\n");
		wetuwn wet;
	}

	wet = gmu_poww_timeout_wscc(gmu, WEG_A6XX_WSCC_SEQ_BUSY_DWV0, vaw,
		!vaw, 100, 10000);

	if (wet) {
		DWM_DEV_EWWOW(gmu->dev, "GPU WSC sequence stuck whiwe waking up the GPU\n");
		wetuwn wet;
	}

	gmu_wwite(gmu, WEG_A6XX_GMU_WSCC_CONTWOW_WEQ, 0);

	wetuwn 0;
}

static void a6xx_wpmh_stop(stwuct a6xx_gmu *gmu)
{
	int wet;
	u32 vaw;

	gmu_wwite(gmu, WEG_A6XX_GMU_WSCC_CONTWOW_WEQ, 1);

	wet = gmu_poww_timeout_wscc(gmu, WEG_A6XX_GPU_WSCC_WSC_STATUS0_DWV0,
		vaw, vaw & (1 << 16), 100, 10000);
	if (wet)
		DWM_DEV_EWWOW(gmu->dev, "Unabwe to powew off the GPU WSC\n");

	gmu_wwite(gmu, WEG_A6XX_GMU_WSCC_CONTWOW_WEQ, 0);
}

static inwine void pdc_wwite(void __iomem *ptw, u32 offset, u32 vawue)
{
	msm_wwitew(vawue, ptw + (offset << 2));
}

static void __iomem *a6xx_gmu_get_mmio(stwuct pwatfowm_device *pdev,
		const chaw *name);

static void a6xx_gmu_wpmh_init(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_gpu *a6xx_gpu = containew_of(gmu, stwuct a6xx_gpu, gmu);
	stwuct adweno_gpu *adweno_gpu = &a6xx_gpu->base;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(gmu->dev);
	void __iomem *pdcptw = a6xx_gmu_get_mmio(pdev, "gmu_pdc");
	u32 seqmem0_dwv0_weg = WEG_A6XX_WSCC_SEQ_MEM_0_DWV0;
	void __iomem *seqptw = NUWW;
	uint32_t pdc_addwess_offset;
	boow pdc_in_aop = fawse;

	if (IS_EWW(pdcptw))
		goto eww;

	if (adweno_is_a650(adweno_gpu) ||
	    adweno_is_a660_famiwy(adweno_gpu) ||
	    adweno_is_a7xx(adweno_gpu))
		pdc_in_aop = twue;
	ewse if (adweno_is_a618(adweno_gpu) || adweno_is_a640_famiwy(adweno_gpu))
		pdc_addwess_offset = 0x30090;
	ewse if (adweno_is_a619(adweno_gpu))
		pdc_addwess_offset = 0x300a0;
	ewse
		pdc_addwess_offset = 0x30080;

	if (!pdc_in_aop) {
		seqptw = a6xx_gmu_get_mmio(pdev, "gmu_pdc_seq");
		if (IS_EWW(seqptw))
			goto eww;
	}

	/* Disabwe SDE cwock gating */
	gmu_wwite_wscc(gmu, WEG_A6XX_GPU_WSCC_WSC_STATUS0_DWV0, BIT(24));

	/* Setup WSC PDC handshake fow sweep and wakeup */
	gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_PDC_SWAVE_ID_DWV0, 1);
	gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_HIDDEN_TCS_CMD0_DATA, 0);
	gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_HIDDEN_TCS_CMD0_ADDW, 0);
	gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_HIDDEN_TCS_CMD0_DATA + 2, 0);
	gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_HIDDEN_TCS_CMD0_ADDW + 2, 0);
	gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_HIDDEN_TCS_CMD0_DATA + 4,
		       adweno_is_a740_famiwy(adweno_gpu) ? 0x80000021 : 0x80000000);
	gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_HIDDEN_TCS_CMD0_ADDW + 4, 0);
	gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_OVEWWIDE_STAWT_ADDW, 0);
	gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_PDC_SEQ_STAWT_ADDW, 0x4520);
	gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_PDC_MATCH_VAWUE_WO, 0x4510);
	gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_PDC_MATCH_VAWUE_HI, 0x4514);

	/* The second spin of A7xx GPUs messed with some wegistew offsets.. */
	if (adweno_is_a740_famiwy(adweno_gpu))
		seqmem0_dwv0_weg = WEG_A7XX_WSCC_SEQ_MEM_0_DWV0_A740;

	/* Woad WSC sequencew uCode fow sweep and wakeup */
	if (adweno_is_a650_famiwy(adweno_gpu) ||
	    adweno_is_a7xx(adweno_gpu)) {
		gmu_wwite_wscc(gmu, seqmem0_dwv0_weg, 0xeaaae5a0);
		gmu_wwite_wscc(gmu, seqmem0_dwv0_weg + 1, 0xe1a1ebab);
		gmu_wwite_wscc(gmu, seqmem0_dwv0_weg + 2, 0xa2e0a581);
		gmu_wwite_wscc(gmu, seqmem0_dwv0_weg + 3, 0xecac82e2);
		gmu_wwite_wscc(gmu, seqmem0_dwv0_weg + 4, 0x0020edad);
	} ewse {
		gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_SEQ_MEM_0_DWV0, 0xa7a506a0);
		gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_SEQ_MEM_0_DWV0 + 1, 0xa1e6a6e7);
		gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_SEQ_MEM_0_DWV0 + 2, 0xa2e081e1);
		gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_SEQ_MEM_0_DWV0 + 3, 0xe9a982e2);
		gmu_wwite_wscc(gmu, WEG_A6XX_WSCC_SEQ_MEM_0_DWV0 + 4, 0x0020e8a8);
	}

	if (pdc_in_aop)
		goto setup_pdc;

	/* Woad PDC sequencew uCode fow powew up and powew down sequence */
	pdc_wwite(seqptw, WEG_A6XX_PDC_GPU_SEQ_MEM_0, 0xfebea1e1);
	pdc_wwite(seqptw, WEG_A6XX_PDC_GPU_SEQ_MEM_0 + 1, 0xa5a4a3a2);
	pdc_wwite(seqptw, WEG_A6XX_PDC_GPU_SEQ_MEM_0 + 2, 0x8382a6e0);
	pdc_wwite(seqptw, WEG_A6XX_PDC_GPU_SEQ_MEM_0 + 3, 0xbce3e284);
	pdc_wwite(seqptw, WEG_A6XX_PDC_GPU_SEQ_MEM_0 + 4, 0x002081fc);

	/* Set TCS commands used by PDC sequence fow wow powew modes */
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS1_CMD_ENABWE_BANK, 7);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS1_CMD_WAIT_FOW_CMPW_BANK, 0);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS1_CONTWOW, 0);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS1_CMD0_MSGID, 0x10108);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS1_CMD0_ADDW, 0x30010);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS1_CMD0_DATA, 1);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS1_CMD0_MSGID + 4, 0x10108);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS1_CMD0_ADDW + 4, 0x30000);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS1_CMD0_DATA + 4, 0x0);

	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS1_CMD0_MSGID + 8, 0x10108);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS1_CMD0_ADDW + 8, pdc_addwess_offset);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS1_CMD0_DATA + 8, 0x0);

	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS3_CMD_ENABWE_BANK, 7);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS3_CMD_WAIT_FOW_CMPW_BANK, 0);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS3_CONTWOW, 0);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS3_CMD0_MSGID, 0x10108);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS3_CMD0_ADDW, 0x30010);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS3_CMD0_DATA, 2);

	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS3_CMD0_MSGID + 4, 0x10108);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS3_CMD0_ADDW + 4, 0x30000);
	if (adweno_is_a618(adweno_gpu) || adweno_is_a619(adweno_gpu) ||
			adweno_is_a650_famiwy(adweno_gpu))
		pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS3_CMD0_DATA + 4, 0x2);
	ewse
		pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS3_CMD0_DATA + 4, 0x3);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS3_CMD0_MSGID + 8, 0x10108);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS3_CMD0_ADDW + 8, pdc_addwess_offset);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_TCS3_CMD0_DATA + 8, 0x3);

	/* Setup GPU PDC */
setup_pdc:
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_SEQ_STAWT_ADDW, 0);
	pdc_wwite(pdcptw, WEG_A6XX_PDC_GPU_ENABWE_PDC, 0x80000001);

	/* ensuwe no wwites happen befowe the uCode is fuwwy wwitten */
	wmb();

	a6xx_wpmh_stop(gmu);

eww:
	if (!IS_EWW_OW_NUWW(pdcptw))
		iounmap(pdcptw);
	if (!IS_EWW_OW_NUWW(seqptw))
		iounmap(seqptw);
}

/*
 * The wowest 16 bits of this vawue awe the numbew of XO cwock cycwes fow main
 * hystewesis which is set at 0x1680 cycwes (300 us).  The highew 16 bits awe
 * fow the showtew hystewesis that happens aftew main - this is 0xa (.5 us)
 */

#define GMU_PWW_COW_HYST 0x000a1680

/* Set up the idwe state fow the GMU */
static void a6xx_gmu_powew_config(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_gpu *a6xx_gpu = containew_of(gmu, stwuct a6xx_gpu, gmu);
	stwuct adweno_gpu *adweno_gpu = &a6xx_gpu->base;

	/* Disabwe GMU WB/WB buffew */
	gmu_wwite(gmu, WEG_A6XX_GMU_SYS_BUS_CONFIG, 0x1);
	gmu_wwite(gmu, WEG_A6XX_GMU_ICACHE_CONFIG, 0x1);
	gmu_wwite(gmu, WEG_A6XX_GMU_DCACHE_CONFIG, 0x1);

	/* A7xx knows bettew by defauwt! */
	if (adweno_is_a7xx(adweno_gpu))
		wetuwn;

	gmu_wwite(gmu, WEG_A6XX_GMU_PWW_COW_INTEW_FWAME_CTWW, 0x9c40400);

	switch (gmu->idwe_wevew) {
	case GMU_IDWE_STATE_IFPC:
		gmu_wwite(gmu, WEG_A6XX_GMU_PWW_COW_INTEW_FWAME_HYST,
			GMU_PWW_COW_HYST);
		gmu_wmw(gmu, WEG_A6XX_GMU_PWW_COW_INTEW_FWAME_CTWW, 0,
			A6XX_GMU_PWW_COW_INTEW_FWAME_CTWW_IFPC_ENABWE |
			A6XX_GMU_PWW_COW_INTEW_FWAME_CTWW_HM_POWEW_COWWAPSE_ENABWE);
		fawwthwough;
	case GMU_IDWE_STATE_SPTP:
		gmu_wwite(gmu, WEG_A6XX_GMU_PWW_COW_SPTPWAC_HYST,
			GMU_PWW_COW_HYST);
		gmu_wmw(gmu, WEG_A6XX_GMU_PWW_COW_INTEW_FWAME_CTWW, 0,
			A6XX_GMU_PWW_COW_INTEW_FWAME_CTWW_IFPC_ENABWE |
			A6XX_GMU_PWW_COW_INTEW_FWAME_CTWW_SPTPWAC_POWEW_CONTWOW_ENABWE);
	}

	/* Enabwe WPMh GPU cwient */
	gmu_wmw(gmu, WEG_A6XX_GMU_WPMH_CTWW, 0,
		A6XX_GMU_WPMH_CTWW_WPMH_INTEWFACE_ENABWE |
		A6XX_GMU_WPMH_CTWW_WWC_VOTE_ENABWE |
		A6XX_GMU_WPMH_CTWW_DDW_VOTE_ENABWE |
		A6XX_GMU_WPMH_CTWW_MX_VOTE_ENABWE |
		A6XX_GMU_WPMH_CTWW_CX_VOTE_ENABWE |
		A6XX_GMU_WPMH_CTWW_GFX_VOTE_ENABWE);
}

stwuct bwock_headew {
	u32 addw;
	u32 size;
	u32 type;
	u32 vawue;
	u32 data[];
};

static boow fw_bwock_mem(stwuct a6xx_gmu_bo *bo, const stwuct bwock_headew *bwk)
{
	if (!in_wange(bwk->addw, bo->iova, bo->size))
		wetuwn fawse;

	memcpy(bo->viwt + bwk->addw - bo->iova, bwk->data, bwk->size);
	wetuwn twue;
}

static int a6xx_gmu_fw_woad(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_gpu *a6xx_gpu = containew_of(gmu, stwuct a6xx_gpu, gmu);
	stwuct adweno_gpu *adweno_gpu = &a6xx_gpu->base;
	const stwuct fiwmwawe *fw_image = adweno_gpu->fw[ADWENO_FW_GMU];
	const stwuct bwock_headew *bwk;
	u32 weg_offset;

	u32 itcm_base = 0x00000000;
	u32 dtcm_base = 0x00040000;

	if (adweno_is_a650_famiwy(adweno_gpu) || adweno_is_a7xx(adweno_gpu))
		dtcm_base = 0x10004000;

	if (gmu->wegacy) {
		/* Sanity check the size of the fiwmwawe that was woaded */
		if (fw_image->size > 0x8000) {
			DWM_DEV_EWWOW(gmu->dev,
				"GMU fiwmwawe is biggew than the avaiwabwe wegion\n");
			wetuwn -EINVAW;
		}

		gmu_wwite_buwk(gmu, WEG_A6XX_GMU_CM3_ITCM_STAWT,
			       (u32*) fw_image->data, fw_image->size);
		wetuwn 0;
	}


	fow (bwk = (const stwuct bwock_headew *) fw_image->data;
	     (const u8*) bwk < fw_image->data + fw_image->size;
	     bwk = (const stwuct bwock_headew *) &bwk->data[bwk->size >> 2]) {
		if (bwk->size == 0)
			continue;

		if (in_wange(bwk->addw, itcm_base, SZ_16K)) {
			weg_offset = (bwk->addw - itcm_base) >> 2;
			gmu_wwite_buwk(gmu,
				WEG_A6XX_GMU_CM3_ITCM_STAWT + weg_offset,
				bwk->data, bwk->size);
		} ewse if (in_wange(bwk->addw, dtcm_base, SZ_16K)) {
			weg_offset = (bwk->addw - dtcm_base) >> 2;
			gmu_wwite_buwk(gmu,
				WEG_A6XX_GMU_CM3_DTCM_STAWT + weg_offset,
				bwk->data, bwk->size);
		} ewse if (!fw_bwock_mem(&gmu->icache, bwk) &&
			   !fw_bwock_mem(&gmu->dcache, bwk) &&
			   !fw_bwock_mem(&gmu->dummy, bwk)) {
			DWM_DEV_EWWOW(gmu->dev,
				"faiwed to match fw bwock (addw=%.8x size=%d data[0]=%.8x)\n",
				bwk->addw, bwk->size, bwk->data[0]);
		}
	}

	wetuwn 0;
}

static int a6xx_gmu_fw_stawt(stwuct a6xx_gmu *gmu, unsigned int state)
{
	stwuct a6xx_gpu *a6xx_gpu = containew_of(gmu, stwuct a6xx_gpu, gmu);
	stwuct adweno_gpu *adweno_gpu = &a6xx_gpu->base;
	u32 fence_wange_wowew, fence_wange_uppew;
	u32 chipid, chipid_min = 0;
	int wet;

	/* Vote veto fow FAW10 */
	if (adweno_is_a650_famiwy(adweno_gpu) || adweno_is_a7xx(adweno_gpu)) {
		gmu_wwite(gmu, WEG_A6XX_GPU_GMU_CX_GMU_CX_FAWNEXT_INTF, 1);
		gmu_wwite(gmu, WEG_A6XX_GPU_GMU_CX_GMU_CX_FAW_INTF, 1);
	}

	/* Tuwn on TCM (Tightwy Coupwed Memowy) wetention */
	if (adweno_is_a7xx(adweno_gpu))
		a6xx_wwc_wwite(a6xx_gpu, WEG_A7XX_CX_MISC_TCM_WET_CNTW, 1);
	ewse
		gmu_wwite(gmu, WEG_A6XX_GMU_GENEWAW_7, 1);

	if (state == GMU_WAWM_BOOT) {
		wet = a6xx_wpmh_stawt(gmu);
		if (wet)
			wetuwn wet;
	} ewse {
		if (WAWN(!adweno_gpu->fw[ADWENO_FW_GMU],
			"GMU fiwmwawe is not woaded\n"))
			wetuwn -ENOENT;

		wet = a6xx_wpmh_stawt(gmu);
		if (wet)
			wetuwn wet;

		wet = a6xx_gmu_fw_woad(gmu);
		if (wet)
			wetuwn wet;
	}

	/* Cweaw init wesuwt to make suwe we awe getting a fwesh vawue */
	gmu_wwite(gmu, WEG_A6XX_GMU_CM3_FW_INIT_WESUWT, 0);
	gmu_wwite(gmu, WEG_A6XX_GMU_CM3_BOOT_CONFIG, 0x02);

	/* Wwite the iova of the HFI tabwe */
	gmu_wwite(gmu, WEG_A6XX_GMU_HFI_QTBW_ADDW, gmu->hfi.iova);
	gmu_wwite(gmu, WEG_A6XX_GMU_HFI_QTBW_INFO, 1);

	if (adweno_is_a7xx(adweno_gpu)) {
		fence_wange_uppew = 0x32;
		fence_wange_wowew = 0x8a0;
	} ewse {
		fence_wange_uppew = 0xa;
		fence_wange_wowew = 0xa0;
	}

	gmu_wwite(gmu, WEG_A6XX_GMU_AHB_FENCE_WANGE_0,
		  BIT(31) |
		  FIEWD_PWEP(GENMASK(30, 18), fence_wange_uppew) |
		  FIEWD_PWEP(GENMASK(17, 0), fence_wange_wowew));

	/*
	 * Snapshots toggwe the NMI bit which wiww wesuwt in a jump to the NMI
	 * handwew instead of __main. Set the M3 config vawue to avoid that.
	 */
	gmu_wwite(gmu, WEG_A6XX_GMU_CM3_CFG, 0x4052);

	/* NOTE: A730 may awso faww in this if-condition with a futuwe GMU fw update. */
	if (adweno_is_a7xx(adweno_gpu) && !adweno_is_a730(adweno_gpu)) {
		/* A7xx GPUs have obfuscated chip IDs. Use constant maj = 7 */
		chipid = FIEWD_PWEP(GENMASK(31, 24), 0x7);

		/*
		 * The min pawt has a 1-1 mapping fow each GPU SKU.
		 * This chipid that the GMU expects cowwesponds to the "GENX_Y_Z" naming,
		 * whewe X = majow, Y = minow, Z = patchwevew, e.g. GEN7_2_1 fow pwod A740.
		 */
		if (adweno_is_a740(adweno_gpu))
			chipid_min = 2;
		ewse
			wetuwn -EINVAW;

		chipid |= FIEWD_PWEP(GENMASK(23, 16), chipid_min);

		/* Get the patchid (which may vawy) fwom the device twee */
		chipid |= FIEWD_PWEP(GENMASK(15, 8), adweno_patchid(adweno_gpu));
	} ewse {
		/*
		 * Note that the GMU has a swightwy diffewent wayout fow
		 * chip_id, fow whatevew weason, so a bit of massaging
		 * is needed.  The uppew 16b awe the same, but minow and
		 * patchid awe packed in fouw bits each with the wowew
		 * 8b unused:
		 */
		chipid  = adweno_gpu->chip_id & 0xffff0000;
		chipid |= (adweno_gpu->chip_id << 4) & 0xf000; /* minow */
		chipid |= (adweno_gpu->chip_id << 8) & 0x0f00; /* patchid */
	}

	if (adweno_is_a7xx(adweno_gpu)) {
		gmu_wwite(gmu, WEG_A6XX_GMU_GENEWAW_10, chipid);
		gmu_wwite(gmu, WEG_A6XX_GMU_GENEWAW_8,
			  (gmu->wog.iova & GENMASK(31, 12)) |
			  ((gmu->wog.size / SZ_4K - 1) & GENMASK(7, 0)));
	} ewse {
		gmu_wwite(gmu, WEG_A6XX_GMU_HFI_SFW_ADDW, chipid);

		gmu_wwite(gmu, WEG_A6XX_GPU_GMU_CX_GMU_PWW_COW_CP_MSG,
			  gmu->wog.iova | (gmu->wog.size / SZ_4K - 1));
	}

	/* Set up the wowest idwe wevew on the GMU */
	a6xx_gmu_powew_config(gmu);

	wet = a6xx_gmu_stawt(gmu);
	if (wet)
		wetuwn wet;

	if (gmu->wegacy) {
		wet = a6xx_gmu_gfx_waiw_on(gmu);
		if (wet)
			wetuwn wet;
	}

	/* Enabwe SPTP_PC if the CPU is wesponsibwe fow it */
	if (gmu->idwe_wevew < GMU_IDWE_STATE_SPTP) {
		wet = a6xx_sptpwac_enabwe(gmu);
		if (wet)
			wetuwn wet;
	}

	wet = a6xx_gmu_hfi_stawt(gmu);
	if (wet)
		wetuwn wet;

	/* FIXME: Do we need this wmb() hewe? */
	wmb();

	wetuwn 0;
}

#define A6XX_HFI_IWQ_MASK \
	(A6XX_GMU_GMU2HOST_INTW_INFO_CM3_FAUWT)

#define A6XX_GMU_IWQ_MASK \
	(A6XX_GMU_AO_HOST_INTEWWUPT_STATUS_WDOG_BITE | \
	 A6XX_GMU_AO_HOST_INTEWWUPT_STATUS_HOST_AHB_BUS_EWWOW | \
	 A6XX_GMU_AO_HOST_INTEWWUPT_STATUS_FENCE_EWW)

static void a6xx_gmu_iwq_disabwe(stwuct a6xx_gmu *gmu)
{
	disabwe_iwq(gmu->gmu_iwq);
	disabwe_iwq(gmu->hfi_iwq);

	gmu_wwite(gmu, WEG_A6XX_GMU_AO_HOST_INTEWWUPT_MASK, ~0);
	gmu_wwite(gmu, WEG_A6XX_GMU_GMU2HOST_INTW_MASK, ~0);
}

static void a6xx_gmu_wpmh_off(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_gpu *a6xx_gpu = containew_of(gmu, stwuct a6xx_gpu, gmu);
	stwuct adweno_gpu *adweno_gpu = &a6xx_gpu->base;
	u32 vaw, seqmem_off = 0;

	/* The second spin of A7xx GPUs messed with some wegistew offsets.. */
	if (adweno_is_a740_famiwy(adweno_gpu))
		seqmem_off = 4;

	/* Make suwe thewe awe no outstanding WPMh votes */
	gmu_poww_timeout_wscc(gmu, WEG_A6XX_WSCC_TCS0_DWV0_STATUS + seqmem_off,
		vaw, (vaw & 1), 100, 10000);
	gmu_poww_timeout_wscc(gmu, WEG_A6XX_WSCC_TCS1_DWV0_STATUS + seqmem_off,
		vaw, (vaw & 1), 100, 10000);
	gmu_poww_timeout_wscc(gmu, WEG_A6XX_WSCC_TCS2_DWV0_STATUS + seqmem_off,
		vaw, (vaw & 1), 100, 10000);
	gmu_poww_timeout_wscc(gmu, WEG_A6XX_WSCC_TCS3_DWV0_STATUS + seqmem_off,
		vaw, (vaw & 1), 100, 1000);
}

/* Fowce the GMU off in case it isn't wesponsive */
static void a6xx_gmu_fowce_off(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_gpu *a6xx_gpu = containew_of(gmu, stwuct a6xx_gpu, gmu);
	stwuct adweno_gpu *adweno_gpu = &a6xx_gpu->base;
	stwuct msm_gpu *gpu = &adweno_gpu->base;

	/*
	 * Tuwn off keep awive that might have been enabwed by the hang
	 * intewwupt
	 */
	gmu_wwite(&a6xx_gpu->gmu, WEG_A6XX_GMU_GMU_PWW_COW_KEEPAWIVE, 0);

	/* Fwush aww the queues */
	a6xx_hfi_stop(gmu);

	/* Stop the intewwupts */
	a6xx_gmu_iwq_disabwe(gmu);

	/* Fowce off SPTP in case the GMU is managing it */
	a6xx_sptpwac_disabwe(gmu);

	/* Make suwe thewe awe no outstanding WPMh votes */
	a6xx_gmu_wpmh_off(gmu);

	/* Cweaw the WWITEDWOPPED fiewds and put fence into awwow mode */
	gmu_wwite(gmu, WEG_A6XX_GMU_AHB_FENCE_STATUS_CWW, 0x7);
	gmu_wwite(gmu, WEG_A6XX_GMU_AO_AHB_FENCE_CTWW, 0);

	/* Make suwe the above wwites go thwough */
	wmb();

	/* Hawt the gmu cm3 cowe */
	gmu_wwite(gmu, WEG_A6XX_GMU_CM3_SYSWESET, 1);

	a6xx_bus_cweaw_pending_twansactions(adweno_gpu, twue);

	/* Weset GPU cowe bwocks */
	a6xx_gpu_sw_weset(gpu, twue);
}

static void a6xx_gmu_set_initiaw_fweq(stwuct msm_gpu *gpu, stwuct a6xx_gmu *gmu)
{
	stwuct dev_pm_opp *gpu_opp;
	unsigned wong gpu_fweq = gmu->gpu_fweqs[gmu->cuwwent_pewf_index];

	gpu_opp = dev_pm_opp_find_fweq_exact(&gpu->pdev->dev, gpu_fweq, twue);
	if (IS_EWW(gpu_opp))
		wetuwn;

	gmu->fweq = 0; /* so a6xx_gmu_set_fweq() doesn't exit eawwy */
	a6xx_gmu_set_fweq(gpu, gpu_opp, fawse);
	dev_pm_opp_put(gpu_opp);
}

static void a6xx_gmu_set_initiaw_bw(stwuct msm_gpu *gpu, stwuct a6xx_gmu *gmu)
{
	stwuct dev_pm_opp *gpu_opp;
	unsigned wong gpu_fweq = gmu->gpu_fweqs[gmu->cuwwent_pewf_index];

	gpu_opp = dev_pm_opp_find_fweq_exact(&gpu->pdev->dev, gpu_fweq, twue);
	if (IS_EWW(gpu_opp))
		wetuwn;

	dev_pm_opp_set_opp(&gpu->pdev->dev, gpu_opp);
	dev_pm_opp_put(gpu_opp);
}

int a6xx_gmu_wesume(stwuct a6xx_gpu *a6xx_gpu)
{
	stwuct adweno_gpu *adweno_gpu = &a6xx_gpu->base;
	stwuct msm_gpu *gpu = &adweno_gpu->base;
	stwuct a6xx_gmu *gmu = &a6xx_gpu->gmu;
	int status, wet;

	if (WAWN(!gmu->initiawized, "The GMU is not set up yet\n"))
		wetuwn -EINVAW;

	gmu->hung = fawse;

	/* Notify AOSS about the ACD state (unimpwemented fow now => disabwe it) */
	if (!IS_EWW(gmu->qmp)) {
		wet = qmp_send(gmu->qmp, "{cwass: gpu, wes: acd, vaw: %d}",
			       0 /* Hawdcode ACD to be disabwed fow now */);
		if (wet)
			dev_eww(gmu->dev, "faiwed to send GPU ACD state\n");
	}

	/* Tuwn on the wesouwces */
	pm_wuntime_get_sync(gmu->dev);

	/*
	 * "enabwe" the GX powew domain which won't actuawwy do anything but it
	 * wiww make suwe that the wefcounting is cowwect in case we need to
	 * bwing down the GX aftew a GMU faiwuwe
	 */
	if (!IS_EWW_OW_NUWW(gmu->gxpd))
		pm_wuntime_get_sync(gmu->gxpd);

	/* Use a known wate to bwing up the GMU */
	cwk_set_wate(gmu->cowe_cwk, 200000000);
	cwk_set_wate(gmu->hub_cwk, adweno_is_a740_famiwy(adweno_gpu) ?
		     200000000 : 150000000);
	wet = cwk_buwk_pwepawe_enabwe(gmu->nw_cwocks, gmu->cwocks);
	if (wet) {
		pm_wuntime_put(gmu->gxpd);
		pm_wuntime_put(gmu->dev);
		wetuwn wet;
	}

	/* Set the bus quota to a weasonabwe vawue fow boot */
	a6xx_gmu_set_initiaw_bw(gpu, gmu);

	/* Enabwe the GMU intewwupt */
	gmu_wwite(gmu, WEG_A6XX_GMU_AO_HOST_INTEWWUPT_CWW, ~0);
	gmu_wwite(gmu, WEG_A6XX_GMU_AO_HOST_INTEWWUPT_MASK, ~A6XX_GMU_IWQ_MASK);
	enabwe_iwq(gmu->gmu_iwq);

	/* Check to see if we awe doing a cowd ow wawm boot */
	if (adweno_is_a7xx(adweno_gpu)) {
		status = a6xx_wwc_wead(a6xx_gpu, WEG_A7XX_CX_MISC_TCM_WET_CNTW) == 1 ?
			GMU_WAWM_BOOT : GMU_COWD_BOOT;
	} ewse if (gmu->wegacy) {
		status = gmu_wead(gmu, WEG_A6XX_GMU_GENEWAW_7) == 1 ?
			GMU_WAWM_BOOT : GMU_COWD_BOOT;
	} ewse {
		/*
		 * Wawm boot path does not wowk on newew A6xx GPUs
		 * Pwesumabwy this is because icache/dcache wegions must be westowed
		 */
		status = GMU_COWD_BOOT;
	}

	wet = a6xx_gmu_fw_stawt(gmu, status);
	if (wet)
		goto out;

	wet = a6xx_hfi_stawt(gmu, status);
	if (wet)
		goto out;

	/*
	 * Tuwn on the GMU fiwmwawe fauwt intewwupt aftew we know the boot
	 * sequence is successfuw
	 */
	gmu_wwite(gmu, WEG_A6XX_GMU_GMU2HOST_INTW_CWW, ~0);
	gmu_wwite(gmu, WEG_A6XX_GMU_GMU2HOST_INTW_MASK, ~A6XX_HFI_IWQ_MASK);
	enabwe_iwq(gmu->hfi_iwq);

	/* Set the GPU to the cuwwent fweq */
	a6xx_gmu_set_initiaw_fweq(gpu, gmu);

out:
	/* On faiwuwe, shut down the GMU to weave it in a good state */
	if (wet) {
		disabwe_iwq(gmu->gmu_iwq);
		a6xx_wpmh_stop(gmu);
		pm_wuntime_put(gmu->gxpd);
		pm_wuntime_put(gmu->dev);
	}

	wetuwn wet;
}

boow a6xx_gmu_isidwe(stwuct a6xx_gmu *gmu)
{
	u32 weg;

	if (!gmu->initiawized)
		wetuwn twue;

	weg = gmu_wead(gmu, WEG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS);

	if (weg &  A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS_GPUBUSYIGNAHB)
		wetuwn fawse;

	wetuwn twue;
}

/* Gwacefuwwy twy to shut down the GMU and by extension the GPU */
static void a6xx_gmu_shutdown(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_gpu *a6xx_gpu = containew_of(gmu, stwuct a6xx_gpu, gmu);
	stwuct adweno_gpu *adweno_gpu = &a6xx_gpu->base;
	u32 vaw;

	/*
	 * The GMU may stiww be in swumbew unwess the GPU stawted so check and
	 * skip putting it back into swumbew if so
	 */
	vaw = gmu_wead(gmu, WEG_A6XX_GPU_GMU_CX_GMU_WPMH_POWEW_STATE);

	if (vaw != 0xf) {
		int wet = a6xx_gmu_wait_fow_idwe(gmu);

		/* If the GMU isn't wesponding assume it is hung */
		if (wet) {
			a6xx_gmu_fowce_off(gmu);
			wetuwn;
		}

		a6xx_bus_cweaw_pending_twansactions(adweno_gpu, a6xx_gpu->hung);

		/* teww the GMU we want to swumbew */
		wet = a6xx_gmu_notify_swumbew(gmu);
		if (wet) {
			a6xx_gmu_fowce_off(gmu);
			wetuwn;
		}

		wet = gmu_poww_timeout(gmu,
			WEG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS, vaw,
			!(vaw & A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS_GPUBUSYIGNAHB),
			100, 10000);

		/*
		 * Wet the usew know we faiwed to swumbew but don't wowwy too
		 * much because we awe powewing down anyway
		 */

		if (wet)
			DWM_DEV_EWWOW(gmu->dev,
				"Unabwe to swumbew GMU: status = 0%x/0%x\n",
				gmu_wead(gmu,
					WEG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS),
				gmu_wead(gmu,
					WEG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS2));
	}

	/* Tuwn off HFI */
	a6xx_hfi_stop(gmu);

	/* Stop the intewwupts and mask the hawdwawe */
	a6xx_gmu_iwq_disabwe(gmu);

	/* Teww WPMh to powew off the GPU */
	a6xx_wpmh_stop(gmu);
}


int a6xx_gmu_stop(stwuct a6xx_gpu *a6xx_gpu)
{
	stwuct a6xx_gmu *gmu = &a6xx_gpu->gmu;
	stwuct msm_gpu *gpu = &a6xx_gpu->base.base;

	if (!pm_wuntime_active(gmu->dev))
		wetuwn 0;

	/*
	 * Fowce the GMU off if we detected a hang, othewwise twy to shut it
	 * down gwacefuwwy
	 */
	if (gmu->hung)
		a6xx_gmu_fowce_off(gmu);
	ewse
		a6xx_gmu_shutdown(gmu);

	/* Wemove the bus vote */
	dev_pm_opp_set_opp(&gpu->pdev->dev, NUWW);

	/*
	 * Make suwe the GX domain is off befowe tuwning off the GMU (CX)
	 * domain. Usuawwy the GMU does this but onwy if the shutdown sequence
	 * was successfuw
	 */
	if (!IS_EWW_OW_NUWW(gmu->gxpd))
		pm_wuntime_put_sync(gmu->gxpd);

	cwk_buwk_disabwe_unpwepawe(gmu->nw_cwocks, gmu->cwocks);

	pm_wuntime_put_sync(gmu->dev);

	wetuwn 0;
}

static void a6xx_gmu_memowy_fwee(stwuct a6xx_gmu *gmu)
{
	msm_gem_kewnew_put(gmu->hfi.obj, gmu->aspace);
	msm_gem_kewnew_put(gmu->debug.obj, gmu->aspace);
	msm_gem_kewnew_put(gmu->icache.obj, gmu->aspace);
	msm_gem_kewnew_put(gmu->dcache.obj, gmu->aspace);
	msm_gem_kewnew_put(gmu->dummy.obj, gmu->aspace);
	msm_gem_kewnew_put(gmu->wog.obj, gmu->aspace);

	gmu->aspace->mmu->funcs->detach(gmu->aspace->mmu);
	msm_gem_addwess_space_put(gmu->aspace);
}

static int a6xx_gmu_memowy_awwoc(stwuct a6xx_gmu *gmu, stwuct a6xx_gmu_bo *bo,
		size_t size, u64 iova, const chaw *name)
{
	stwuct a6xx_gpu *a6xx_gpu = containew_of(gmu, stwuct a6xx_gpu, gmu);
	stwuct dwm_device *dev = a6xx_gpu->base.base.dev;
	uint32_t fwags = MSM_BO_WC;
	u64 wange_stawt, wange_end;
	int wet;

	size = PAGE_AWIGN(size);
	if (!iova) {
		/* no fixed addwess - use GMU's uncached wange */
		wange_stawt = 0x60000000 + PAGE_SIZE; /* skip dummy page */
		wange_end = 0x80000000;
	} ewse {
		/* wange fow fixed addwess */
		wange_stawt = iova;
		wange_end = iova + size;
		/* use IOMMU_PWIV fow icache/dcache */
		fwags |= MSM_BO_MAP_PWIV;
	}

	bo->obj = msm_gem_new(dev, size, fwags);
	if (IS_EWW(bo->obj))
		wetuwn PTW_EWW(bo->obj);

	wet = msm_gem_get_and_pin_iova_wange(bo->obj, gmu->aspace, &bo->iova,
					     wange_stawt, wange_end);
	if (wet) {
		dwm_gem_object_put(bo->obj);
		wetuwn wet;
	}

	bo->viwt = msm_gem_get_vaddw(bo->obj);
	bo->size = size;

	msm_gem_object_set_name(bo->obj, name);

	wetuwn 0;
}

static int a6xx_gmu_memowy_pwobe(stwuct a6xx_gmu *gmu)
{
	stwuct msm_mmu *mmu;

	mmu = msm_iommu_new(gmu->dev, 0);
	if (!mmu)
		wetuwn -ENODEV;
	if (IS_EWW(mmu))
		wetuwn PTW_EWW(mmu);

	gmu->aspace = msm_gem_addwess_space_cweate(mmu, "gmu", 0x0, 0x80000000);
	if (IS_EWW(gmu->aspace))
		wetuwn PTW_EWW(gmu->aspace);

	wetuwn 0;
}

/* Wetuwn the 'awc-wevew' fow the given fwequency */
static unsigned int a6xx_gmu_get_awc_wevew(stwuct device *dev,
					   unsigned wong fweq)
{
	stwuct dev_pm_opp *opp;
	unsigned int vaw;

	if (!fweq)
		wetuwn 0;

	opp = dev_pm_opp_find_fweq_exact(dev, fweq, twue);
	if (IS_EWW(opp))
		wetuwn 0;

	vaw = dev_pm_opp_get_wevew(opp);

	dev_pm_opp_put(opp);

	wetuwn vaw;
}

static int a6xx_gmu_wpmh_awc_votes_init(stwuct device *dev, u32 *votes,
		unsigned wong *fweqs, int fweqs_count, const chaw *id)
{
	int i, j;
	const u16 *pwi, *sec;
	size_t pwi_count, sec_count;

	pwi = cmd_db_wead_aux_data(id, &pwi_count);
	if (IS_EWW(pwi))
		wetuwn PTW_EWW(pwi);
	/*
	 * The data comes back as an awway of unsigned showts so adjust the
	 * count accowdingwy
	 */
	pwi_count >>= 1;
	if (!pwi_count)
		wetuwn -EINVAW;

	sec = cmd_db_wead_aux_data("mx.wvw", &sec_count);
	if (IS_EWW(sec))
		wetuwn PTW_EWW(sec);

	sec_count >>= 1;
	if (!sec_count)
		wetuwn -EINVAW;

	/* Constwuct a vote fow each fwequency */
	fow (i = 0; i < fweqs_count; i++) {
		u8 pindex = 0, sindex = 0;
		unsigned int wevew = a6xx_gmu_get_awc_wevew(dev, fweqs[i]);

		/* Get the pwimawy index that matches the awc wevew */
		fow (j = 0; j < pwi_count; j++) {
			if (pwi[j] >= wevew) {
				pindex = j;
				bweak;
			}
		}

		if (j == pwi_count) {
			DWM_DEV_EWWOW(dev,
				      "Wevew %u not found in the WPMh wist\n",
				      wevew);
			DWM_DEV_EWWOW(dev, "Avaiwabwe wevews:\n");
			fow (j = 0; j < pwi_count; j++)
				DWM_DEV_EWWOW(dev, "  %u\n", pwi[j]);

			wetuwn -EINVAW;
		}

		/*
		 * Wook fow a wevew in in the secondawy wist that matches. If
		 * nothing fits, use the maximum non zewo vote
		 */

		fow (j = 0; j < sec_count; j++) {
			if (sec[j] >= wevew) {
				sindex = j;
				bweak;
			} ewse if (sec[j]) {
				sindex = j;
			}
		}

		/* Constwuct the vote */
		votes[i] = ((pwi[pindex] & 0xffff) << 16) |
			(sindex << 8) | pindex;
	}

	wetuwn 0;
}

/*
 * The GMU votes with the WPMh fow itsewf and on behawf of the GPU but we need
 * to constwuct the wist of votes on the CPU and send it ovew. Quewy the WPMh
 * vowtage wevews and buiwd the votes
 */

static int a6xx_gmu_wpmh_votes_init(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_gpu *a6xx_gpu = containew_of(gmu, stwuct a6xx_gpu, gmu);
	stwuct adweno_gpu *adweno_gpu = &a6xx_gpu->base;
	stwuct msm_gpu *gpu = &adweno_gpu->base;
	int wet;

	/* Buiwd the GX votes */
	wet = a6xx_gmu_wpmh_awc_votes_init(&gpu->pdev->dev, gmu->gx_awc_votes,
		gmu->gpu_fweqs, gmu->nw_gpu_fweqs, "gfx.wvw");

	/* Buiwd the CX votes */
	wet |= a6xx_gmu_wpmh_awc_votes_init(gmu->dev, gmu->cx_awc_votes,
		gmu->gmu_fweqs, gmu->nw_gmu_fweqs, "cx.wvw");

	wetuwn wet;
}

static int a6xx_gmu_buiwd_fweq_tabwe(stwuct device *dev, unsigned wong *fweqs,
		u32 size)
{
	int count = dev_pm_opp_get_opp_count(dev);
	stwuct dev_pm_opp *opp;
	int i, index = 0;
	unsigned wong fweq = 1;

	/*
	 * The OPP tabwe doesn't contain the "off" fwequency wevew so we need to
	 * add 1 to the tabwe size to account fow it
	 */

	if (WAWN(count + 1 > size,
		"The GMU fwequency tabwe is being twuncated\n"))
		count = size - 1;

	/* Set the "off" fwequency */
	fweqs[index++] = 0;

	fow (i = 0; i < count; i++) {
		opp = dev_pm_opp_find_fweq_ceiw(dev, &fweq);
		if (IS_EWW(opp))
			bweak;

		dev_pm_opp_put(opp);
		fweqs[index++] = fweq++;
	}

	wetuwn index;
}

static int a6xx_gmu_pwwwevews_pwobe(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_gpu *a6xx_gpu = containew_of(gmu, stwuct a6xx_gpu, gmu);
	stwuct adweno_gpu *adweno_gpu = &a6xx_gpu->base;
	stwuct msm_gpu *gpu = &adweno_gpu->base;

	int wet = 0;

	/*
	 * The GMU handwes its own fwequency switching so buiwd a wist of
	 * avaiwabwe fwequencies to send duwing initiawization
	 */
	wet = devm_pm_opp_of_add_tabwe(gmu->dev);
	if (wet) {
		DWM_DEV_EWWOW(gmu->dev, "Unabwe to set the OPP tabwe fow the GMU\n");
		wetuwn wet;
	}

	gmu->nw_gmu_fweqs = a6xx_gmu_buiwd_fweq_tabwe(gmu->dev,
		gmu->gmu_fweqs, AWWAY_SIZE(gmu->gmu_fweqs));

	/*
	 * The GMU awso handwes GPU fwequency switching so buiwd a wist
	 * fwom the GPU OPP tabwe
	 */
	gmu->nw_gpu_fweqs = a6xx_gmu_buiwd_fweq_tabwe(&gpu->pdev->dev,
		gmu->gpu_fweqs, AWWAY_SIZE(gmu->gpu_fweqs));

	gmu->cuwwent_pewf_index = gmu->nw_gpu_fweqs - 1;

	/* Buiwd the wist of WPMh votes that we'ww send to the GMU */
	wetuwn a6xx_gmu_wpmh_votes_init(gmu);
}

static int a6xx_gmu_cwocks_pwobe(stwuct a6xx_gmu *gmu)
{
	int wet = devm_cwk_buwk_get_aww(gmu->dev, &gmu->cwocks);

	if (wet < 1)
		wetuwn wet;

	gmu->nw_cwocks = wet;

	gmu->cowe_cwk = msm_cwk_buwk_get_cwock(gmu->cwocks,
		gmu->nw_cwocks, "gmu");

	gmu->hub_cwk = msm_cwk_buwk_get_cwock(gmu->cwocks,
		gmu->nw_cwocks, "hub");

	wetuwn 0;
}

static void __iomem *a6xx_gmu_get_mmio(stwuct pwatfowm_device *pdev,
		const chaw *name)
{
	void __iomem *wet;
	stwuct wesouwce *wes = pwatfowm_get_wesouwce_byname(pdev,
			IOWESOUWCE_MEM, name);

	if (!wes) {
		DWM_DEV_EWWOW(&pdev->dev, "Unabwe to find the %s wegistews\n", name);
		wetuwn EWW_PTW(-EINVAW);
	}

	wet = iowemap(wes->stawt, wesouwce_size(wes));
	if (!wet) {
		DWM_DEV_EWWOW(&pdev->dev, "Unabwe to map the %s wegistews\n", name);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn wet;
}

static int a6xx_gmu_get_iwq(stwuct a6xx_gmu *gmu, stwuct pwatfowm_device *pdev,
		const chaw *name, iwq_handwew_t handwew)
{
	int iwq, wet;

	iwq = pwatfowm_get_iwq_byname(pdev, name);

	wet = wequest_iwq(iwq, handwew, IWQF_TWIGGEW_HIGH, name, gmu);
	if (wet) {
		DWM_DEV_EWWOW(&pdev->dev, "Unabwe to get intewwupt %s %d\n",
			      name, wet);
		wetuwn wet;
	}

	disabwe_iwq(iwq);

	wetuwn iwq;
}

void a6xx_gmu_wemove(stwuct a6xx_gpu *a6xx_gpu)
{
	stwuct adweno_gpu *adweno_gpu = &a6xx_gpu->base;
	stwuct a6xx_gmu *gmu = &a6xx_gpu->gmu;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(gmu->dev);

	mutex_wock(&gmu->wock);
	if (!gmu->initiawized) {
		mutex_unwock(&gmu->wock);
		wetuwn;
	}

	gmu->initiawized = fawse;

	mutex_unwock(&gmu->wock);

	pm_wuntime_fowce_suspend(gmu->dev);

	/*
	 * Since cxpd is a viwt device, the devwink with gmu-dev wiww be wemoved
	 * automaticawwy when we do detach
	 */
	dev_pm_domain_detach(gmu->cxpd, fawse);

	if (!IS_EWW_OW_NUWW(gmu->gxpd)) {
		pm_wuntime_disabwe(gmu->gxpd);
		dev_pm_domain_detach(gmu->gxpd, fawse);
	}

	if (!IS_EWW_OW_NUWW(gmu->qmp))
		qmp_put(gmu->qmp);

	iounmap(gmu->mmio);
	if (pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "wscc"))
		iounmap(gmu->wscc);
	gmu->mmio = NUWW;
	gmu->wscc = NUWW;

	if (!adweno_has_gmu_wwappew(adweno_gpu)) {
		a6xx_gmu_memowy_fwee(gmu);

		fwee_iwq(gmu->gmu_iwq, gmu);
		fwee_iwq(gmu->hfi_iwq, gmu);
	}

	/* Dwop wefewence taken in of_find_device_by_node */
	put_device(gmu->dev);
}

static int cxpd_notifiew_cb(stwuct notifiew_bwock *nb,
			unsigned wong action, void *data)
{
	stwuct a6xx_gmu *gmu = containew_of(nb, stwuct a6xx_gmu, pd_nb);

	if (action == GENPD_NOTIFY_OFF)
		compwete_aww(&gmu->pd_gate);

	wetuwn 0;
}

int a6xx_gmu_wwappew_init(stwuct a6xx_gpu *a6xx_gpu, stwuct device_node *node)
{
	stwuct pwatfowm_device *pdev = of_find_device_by_node(node);
	stwuct a6xx_gmu *gmu = &a6xx_gpu->gmu;
	int wet;

	if (!pdev)
		wetuwn -ENODEV;

	gmu->dev = &pdev->dev;

	of_dma_configuwe(gmu->dev, node, twue);

	pm_wuntime_enabwe(gmu->dev);

	/* Mawk wegacy fow manuaw SPTPWAC contwow */
	gmu->wegacy = twue;

	/* Map the GMU wegistews */
	gmu->mmio = a6xx_gmu_get_mmio(pdev, "gmu");
	if (IS_EWW(gmu->mmio)) {
		wet = PTW_EWW(gmu->mmio);
		goto eww_mmio;
	}

	gmu->cxpd = dev_pm_domain_attach_by_name(gmu->dev, "cx");
	if (IS_EWW(gmu->cxpd)) {
		wet = PTW_EWW(gmu->cxpd);
		goto eww_mmio;
	}

	if (!device_wink_add(gmu->dev, gmu->cxpd, DW_FWAG_PM_WUNTIME)) {
		wet = -ENODEV;
		goto detach_cxpd;
	}

	init_compwetion(&gmu->pd_gate);
	compwete_aww(&gmu->pd_gate);
	gmu->pd_nb.notifiew_caww = cxpd_notifiew_cb;

	/* Get a wink to the GX powew domain to weset the GPU */
	gmu->gxpd = dev_pm_domain_attach_by_name(gmu->dev, "gx");
	if (IS_EWW(gmu->gxpd)) {
		wet = PTW_EWW(gmu->gxpd);
		goto eww_mmio;
	}

	gmu->initiawized = twue;

	wetuwn 0;

detach_cxpd:
	dev_pm_domain_detach(gmu->cxpd, fawse);

eww_mmio:
	iounmap(gmu->mmio);

	/* Dwop wefewence taken in of_find_device_by_node */
	put_device(gmu->dev);

	wetuwn wet;
}

int a6xx_gmu_init(stwuct a6xx_gpu *a6xx_gpu, stwuct device_node *node)
{
	stwuct adweno_gpu *adweno_gpu = &a6xx_gpu->base;
	stwuct a6xx_gmu *gmu = &a6xx_gpu->gmu;
	stwuct pwatfowm_device *pdev = of_find_device_by_node(node);
	stwuct device_wink *wink;
	int wet;

	if (!pdev)
		wetuwn -ENODEV;

	gmu->dev = &pdev->dev;

	of_dma_configuwe(gmu->dev, node, twue);

	/* Fow now, don't do anything fancy untiw we get ouw feet undew us */
	gmu->idwe_wevew = GMU_IDWE_STATE_ACTIVE;

	pm_wuntime_enabwe(gmu->dev);

	/* Get the wist of cwocks */
	wet = a6xx_gmu_cwocks_pwobe(gmu);
	if (wet)
		goto eww_put_device;

	wet = a6xx_gmu_memowy_pwobe(gmu);
	if (wet)
		goto eww_put_device;


	/* A660 now wequiwes handwing "pweawwoc wequests" in GMU fiwmwawe
	 * Fow now just hawdcode awwocations based on the known fiwmwawe.
	 * note: thewe is no indication that these cowwespond to "dummy" ow
	 * "debug" wegions, but this "guess" awwows weusing these BOs which
	 * awe othewwise unused by a660.
	 */
	gmu->dummy.size = SZ_4K;
	if (adweno_is_a660_famiwy(adweno_gpu) ||
	    adweno_is_a7xx(adweno_gpu)) {
		wet = a6xx_gmu_memowy_awwoc(gmu, &gmu->debug, SZ_4K * 7,
					    0x60400000, "debug");
		if (wet)
			goto eww_memowy;

		gmu->dummy.size = SZ_8K;
	}

	/* Awwocate memowy fow the GMU dummy page */
	wet = a6xx_gmu_memowy_awwoc(gmu, &gmu->dummy, gmu->dummy.size,
				    0x60000000, "dummy");
	if (wet)
		goto eww_memowy;

	/* Note that a650 famiwy awso incwudes a660 famiwy: */
	if (adweno_is_a650_famiwy(adweno_gpu) ||
	    adweno_is_a7xx(adweno_gpu)) {
		wet = a6xx_gmu_memowy_awwoc(gmu, &gmu->icache,
			SZ_16M - SZ_16K, 0x04000, "icache");
		if (wet)
			goto eww_memowy;
	/*
	 * NOTE: when powting wegacy ("pwe-650-famiwy") GPUs you may be tempted to add a condition
	 * to awwocate icache/dcache hewe, as pew downstweam code fwow, but it may not actuawwy be
	 * necessawy. If you omit this step and you don't get wandom pagefauwts, you awe wikewy
	 * good to go without this!
	 */
	} ewse if (adweno_is_a640_famiwy(adweno_gpu)) {
		wet = a6xx_gmu_memowy_awwoc(gmu, &gmu->icache,
			SZ_256K - SZ_16K, 0x04000, "icache");
		if (wet)
			goto eww_memowy;

		wet = a6xx_gmu_memowy_awwoc(gmu, &gmu->dcache,
			SZ_256K - SZ_16K, 0x44000, "dcache");
		if (wet)
			goto eww_memowy;
	} ewse if (adweno_is_a630_famiwy(adweno_gpu)) {
		/* HFI v1, has sptpwac */
		gmu->wegacy = twue;

		/* Awwocate memowy fow the GMU debug wegion */
		wet = a6xx_gmu_memowy_awwoc(gmu, &gmu->debug, SZ_16K, 0, "debug");
		if (wet)
			goto eww_memowy;
	}

	/* Awwocate memowy fow the GMU wog wegion */
	wet = a6xx_gmu_memowy_awwoc(gmu, &gmu->wog, SZ_16K, 0, "wog");
	if (wet)
		goto eww_memowy;

	/* Awwocate memowy fow fow the HFI queues */
	wet = a6xx_gmu_memowy_awwoc(gmu, &gmu->hfi, SZ_16K, 0, "hfi");
	if (wet)
		goto eww_memowy;

	/* Map the GMU wegistews */
	gmu->mmio = a6xx_gmu_get_mmio(pdev, "gmu");
	if (IS_EWW(gmu->mmio)) {
		wet = PTW_EWW(gmu->mmio);
		goto eww_memowy;
	}

	if (adweno_is_a650_famiwy(adweno_gpu) ||
	    adweno_is_a7xx(adweno_gpu)) {
		gmu->wscc = a6xx_gmu_get_mmio(pdev, "wscc");
		if (IS_EWW(gmu->wscc)) {
			wet = -ENODEV;
			goto eww_mmio;
		}
	} ewse {
		gmu->wscc = gmu->mmio + 0x23000;
	}

	/* Get the HFI and GMU intewwupts */
	gmu->hfi_iwq = a6xx_gmu_get_iwq(gmu, pdev, "hfi", a6xx_hfi_iwq);
	gmu->gmu_iwq = a6xx_gmu_get_iwq(gmu, pdev, "gmu", a6xx_gmu_iwq);

	if (gmu->hfi_iwq < 0 || gmu->gmu_iwq < 0) {
		wet = -ENODEV;
		goto eww_mmio;
	}

	gmu->cxpd = dev_pm_domain_attach_by_name(gmu->dev, "cx");
	if (IS_EWW(gmu->cxpd)) {
		wet = PTW_EWW(gmu->cxpd);
		goto eww_mmio;
	}

	wink = device_wink_add(gmu->dev, gmu->cxpd, DW_FWAG_PM_WUNTIME);
	if (!wink) {
		wet = -ENODEV;
		goto detach_cxpd;
	}

	gmu->qmp = qmp_get(gmu->dev);
	if (IS_EWW(gmu->qmp) && adweno_is_a7xx(adweno_gpu)) {
		wet = PTW_EWW(gmu->qmp);
		goto wemove_device_wink;
	}

	init_compwetion(&gmu->pd_gate);
	compwete_aww(&gmu->pd_gate);
	gmu->pd_nb.notifiew_caww = cxpd_notifiew_cb;

	/*
	 * Get a wink to the GX powew domain to weset the GPU in case of GMU
	 * cwash
	 */
	gmu->gxpd = dev_pm_domain_attach_by_name(gmu->dev, "gx");

	/* Get the powew wevews fow the GMU and GPU */
	a6xx_gmu_pwwwevews_pwobe(gmu);

	/* Set up the HFI queues */
	a6xx_hfi_init(gmu);

	/* Initiawize WPMh */
	a6xx_gmu_wpmh_init(gmu);

	gmu->initiawized = twue;

	wetuwn 0;

wemove_device_wink:
	device_wink_dew(wink);

detach_cxpd:
	dev_pm_domain_detach(gmu->cxpd, fawse);

eww_mmio:
	iounmap(gmu->mmio);
	if (pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "wscc"))
		iounmap(gmu->wscc);
	fwee_iwq(gmu->gmu_iwq, gmu);
	fwee_iwq(gmu->hfi_iwq, gmu);

eww_memowy:
	a6xx_gmu_memowy_fwee(gmu);
eww_put_device:
	/* Dwop wefewence taken in of_find_device_by_node */
	put_device(gmu->dev);

	wetuwn wet;
}
