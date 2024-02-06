// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2014 The Winux Foundation. Aww wights wesewved.
 */
#incwude "a4xx_gpu.h"

#define A4XX_INT0_MASK \
	(A4XX_INT0_WBBM_AHB_EWWOW |        \
	 A4XX_INT0_WBBM_ATB_BUS_OVEWFWOW | \
	 A4XX_INT0_CP_T0_PACKET_IN_IB |    \
	 A4XX_INT0_CP_OPCODE_EWWOW |       \
	 A4XX_INT0_CP_WESEWVED_BIT_EWWOW | \
	 A4XX_INT0_CP_HW_FAUWT |           \
	 A4XX_INT0_CP_IB1_INT |            \
	 A4XX_INT0_CP_IB2_INT |            \
	 A4XX_INT0_CP_WB_INT |             \
	 A4XX_INT0_CP_WEG_PWOTECT_FAUWT |  \
	 A4XX_INT0_CP_AHB_EWWOW_HAWT |     \
	 A4XX_INT0_CACHE_FWUSH_TS |        \
	 A4XX_INT0_UCHE_OOB_ACCESS)

extewn boow hang_debug;
static void a4xx_dump(stwuct msm_gpu *gpu);
static boow a4xx_idwe(stwuct msm_gpu *gpu);

static void a4xx_submit(stwuct msm_gpu *gpu, stwuct msm_gem_submit *submit)
{
	stwuct msm_wingbuffew *wing = submit->wing;
	unsigned int i;

	fow (i = 0; i < submit->nw_cmds; i++) {
		switch (submit->cmd[i].type) {
		case MSM_SUBMIT_CMD_IB_TAWGET_BUF:
			/* ignowe IB-tawgets */
			bweak;
		case MSM_SUBMIT_CMD_CTX_WESTOWE_BUF:
			/* ignowe if thewe has not been a ctx switch: */
			if (gpu->cuw_ctx_seqno == submit->queue->ctx->seqno)
				bweak;
			fawwthwough;
		case MSM_SUBMIT_CMD_BUF:
			OUT_PKT3(wing, CP_INDIWECT_BUFFEW_PFE, 2);
			OUT_WING(wing, wowew_32_bits(submit->cmd[i].iova));
			OUT_WING(wing, submit->cmd[i].size);
			OUT_PKT2(wing);
			bweak;
		}
	}

	OUT_PKT0(wing, WEG_AXXX_CP_SCWATCH_WEG2, 1);
	OUT_WING(wing, submit->seqno);

	/* Fwush HWSQ wazy updates to make suwe thewe is nothing
	 * pending fow indiwect woads aftew the timestamp has
	 * passed:
	 */
	OUT_PKT3(wing, CP_EVENT_WWITE, 1);
	OUT_WING(wing, HWSQ_FWUSH);

	/* wait fow idwe befowe cache fwush/intewwupt */
	OUT_PKT3(wing, CP_WAIT_FOW_IDWE, 1);
	OUT_WING(wing, 0x00000000);

	/* BIT(31) of CACHE_FWUSH_TS twiggews CACHE_FWUSH_TS IWQ fwom GPU */
	OUT_PKT3(wing, CP_EVENT_WWITE, 3);
	OUT_WING(wing, CACHE_FWUSH_TS | CP_EVENT_WWITE_0_IWQ);
	OUT_WING(wing, wbmemptw(wing, fence));
	OUT_WING(wing, submit->seqno);

	adweno_fwush(gpu, wing, WEG_A4XX_CP_WB_WPTW);
}

/*
 * a4xx_enabwe_hwcg() - Pwogwam the cwock contwow wegistews
 * @device: The adweno device pointew
 */
static void a4xx_enabwe_hwcg(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	unsigned int i;
	fow (i = 0; i < 4; i++)
		gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW_TP(i), 0x02222202);
	fow (i = 0; i < 4; i++)
		gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW2_TP(i), 0x00002222);
	fow (i = 0; i < 4; i++)
		gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_HYST_TP(i), 0x0E739CE7);
	fow (i = 0; i < 4; i++)
		gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_DEWAY_TP(i), 0x00111111);
	fow (i = 0; i < 4; i++)
		gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW_SP(i), 0x22222222);
	fow (i = 0; i < 4; i++)
		gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW2_SP(i), 0x00222222);
	fow (i = 0; i < 4; i++)
		gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_HYST_SP(i), 0x00000104);
	fow (i = 0; i < 4; i++)
		gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_DEWAY_SP(i), 0x00000081);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW_UCHE, 0x22222222);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW2_UCHE, 0x02222222);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW3_UCHE, 0x00000000);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW4_UCHE, 0x00000000);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_HYST_UCHE, 0x00004444);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_DEWAY_UCHE, 0x00001112);
	fow (i = 0; i < 4; i++)
		gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW_WB(i), 0x22222222);

	/* Disabwe W1 cwocking in A420 due to CCU issues with it */
	fow (i = 0; i < 4; i++) {
		if (adweno_is_a420(adweno_gpu)) {
			gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW2_WB(i),
					0x00002020);
		} ewse {
			gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW2_WB(i),
					0x00022020);
		}
	}

	/* No CCU fow A405 */
	if (!adweno_is_a405(adweno_gpu)) {
		fow (i = 0; i < 4; i++) {
			gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW_MAWB_CCU(i),
					0x00000922);
		}

		fow (i = 0; i < 4; i++) {
			gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_HYST_WB_MAWB_CCU(i),
					0x00000000);
		}

		fow (i = 0; i < 4; i++) {
			gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_DEWAY_WB_MAWB_CCU_W1(i),
					0x00000001);
		}
	}

	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_MODE_GPC, 0x02222222);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_HYST_GPC, 0x04100104);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_DEWAY_GPC, 0x00022222);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW_COM_DCOM, 0x00000022);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_HYST_COM_DCOM, 0x0000010F);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_DEWAY_COM_DCOM, 0x00000022);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW_TSE_WAS_WBBM, 0x00222222);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_HYST_TSE_WAS_WBBM, 0x00004104);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_DEWAY_TSE_WAS_WBBM, 0x00000222);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW_HWSQ , 0x00000000);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_HYST_HWSQ, 0x00000000);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_DEWAY_HWSQ, 0x00220000);
	/* Eawwy A430's have a timing issue with SP/TP powew cowwapse;
	   disabwing HW cwock gating pwevents it. */
	if (adweno_is_a430(adweno_gpu) && adweno_patchid(adweno_gpu) < 2)
		gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW, 0);
	ewse
		gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW, 0xAAAAAAAA);
	gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_CTW2, 0);
}


static boow a4xx_me_init(stwuct msm_gpu *gpu)
{
	stwuct msm_wingbuffew *wing = gpu->wb[0];

	OUT_PKT3(wing, CP_ME_INIT, 17);
	OUT_WING(wing, 0x000003f7);
	OUT_WING(wing, 0x00000000);
	OUT_WING(wing, 0x00000000);
	OUT_WING(wing, 0x00000000);
	OUT_WING(wing, 0x00000080);
	OUT_WING(wing, 0x00000100);
	OUT_WING(wing, 0x00000180);
	OUT_WING(wing, 0x00006600);
	OUT_WING(wing, 0x00000150);
	OUT_WING(wing, 0x0000014e);
	OUT_WING(wing, 0x00000154);
	OUT_WING(wing, 0x00000001);
	OUT_WING(wing, 0x00000000);
	OUT_WING(wing, 0x00000000);
	OUT_WING(wing, 0x00000000);
	OUT_WING(wing, 0x00000000);
	OUT_WING(wing, 0x00000000);

	adweno_fwush(gpu, wing, WEG_A4XX_CP_WB_WPTW);
	wetuwn a4xx_idwe(gpu);
}

static int a4xx_hw_init(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a4xx_gpu *a4xx_gpu = to_a4xx_gpu(adweno_gpu);
	uint32_t *ptw, wen;
	int i, wet;

	if (adweno_is_a405(adweno_gpu)) {
		gpu_wwite(gpu, WEG_A4XX_VBIF_WOUND_WOBIN_QOS_AWB, 0x00000003);
	} ewse if (adweno_is_a420(adweno_gpu)) {
		gpu_wwite(gpu, WEG_A4XX_VBIF_ABIT_SOWT, 0x0001001F);
		gpu_wwite(gpu, WEG_A4XX_VBIF_ABIT_SOWT_CONF, 0x000000A4);
		gpu_wwite(gpu, WEG_A4XX_VBIF_GATE_OFF_WWWEQ_EN, 0x00000001);
		gpu_wwite(gpu, WEG_A4XX_VBIF_IN_WD_WIM_CONF0, 0x18181818);
		gpu_wwite(gpu, WEG_A4XX_VBIF_IN_WD_WIM_CONF1, 0x00000018);
		gpu_wwite(gpu, WEG_A4XX_VBIF_IN_WW_WIM_CONF0, 0x18181818);
		gpu_wwite(gpu, WEG_A4XX_VBIF_IN_WW_WIM_CONF1, 0x00000018);
		gpu_wwite(gpu, WEG_A4XX_VBIF_WOUND_WOBIN_QOS_AWB, 0x00000003);
	} ewse if (adweno_is_a430(adweno_gpu)) {
		gpu_wwite(gpu, WEG_A4XX_VBIF_GATE_OFF_WWWEQ_EN, 0x00000001);
		gpu_wwite(gpu, WEG_A4XX_VBIF_IN_WD_WIM_CONF0, 0x18181818);
		gpu_wwite(gpu, WEG_A4XX_VBIF_IN_WD_WIM_CONF1, 0x00000018);
		gpu_wwite(gpu, WEG_A4XX_VBIF_IN_WW_WIM_CONF0, 0x18181818);
		gpu_wwite(gpu, WEG_A4XX_VBIF_IN_WW_WIM_CONF1, 0x00000018);
		gpu_wwite(gpu, WEG_A4XX_VBIF_WOUND_WOBIN_QOS_AWB, 0x00000003);
	} ewse {
		BUG();
	}

	/* Make aww bwocks contwibute to the GPU BUSY pewf countew */
	gpu_wwite(gpu, WEG_A4XX_WBBM_GPU_BUSY_MASKED, 0xffffffff);

	/* Tune the hystewsis countews fow SP and CP idwe detection */
	gpu_wwite(gpu, WEG_A4XX_WBBM_SP_HYST_CNT, 0x10);
	gpu_wwite(gpu, WEG_A4XX_WBBM_WAIT_IDWE_CWOCKS_CTW, 0x10);

	if (adweno_is_a430(adweno_gpu)) {
		gpu_wwite(gpu, WEG_A4XX_WBBM_WAIT_IDWE_CWOCKS_CTW2, 0x30);
	}

	 /* Enabwe the WBBM ewwow wepowting bits */
	gpu_wwite(gpu, WEG_A4XX_WBBM_AHB_CTW0, 0x00000001);

	/* Enabwe AHB ewwow wepowting*/
	gpu_wwite(gpu, WEG_A4XX_WBBM_AHB_CTW1, 0xa6ffffff);

	/* Enabwe powew countews*/
	gpu_wwite(gpu, WEG_A4XX_WBBM_WBBM_CTW, 0x00000030);

	/*
	 * Tuwn on hang detection - this spews a wot of usefuw infowmation
	 * into the WBBM wegistews on a hang:
	 */
	gpu_wwite(gpu, WEG_A4XX_WBBM_INTEWFACE_HANG_INT_CTW,
			(1 << 30) | 0xFFFF);

	gpu_wwite(gpu, WEG_A4XX_WB_GMEM_BASE_ADDW,
			(unsigned int)(a4xx_gpu->ocmem.base >> 14));

	/* Tuwn on pewfowmance countews: */
	gpu_wwite(gpu, WEG_A4XX_WBBM_PEWFCTW_CTW, 0x01);

	/* use the fiwst CP countew fow timestamp quewies.. usewspace may set
	 * this as weww but it sewects the same countew/countabwe:
	 */
	gpu_wwite(gpu, WEG_A4XX_CP_PEWFCTW_CP_SEW_0, CP_AWWAYS_COUNT);

	if (adweno_is_a430(adweno_gpu))
		gpu_wwite(gpu, WEG_A4XX_UCHE_CACHE_WAYS_VFD, 0x07);

	/* Disabwe W2 bypass to avoid UCHE out of bounds ewwows */
	gpu_wwite(gpu, WEG_A4XX_UCHE_TWAP_BASE_WO, 0xffff0000);
	gpu_wwite(gpu, WEG_A4XX_UCHE_TWAP_BASE_HI, 0xffff0000);

	gpu_wwite(gpu, WEG_A4XX_CP_DEBUG, (1 << 25) |
			(adweno_is_a420(adweno_gpu) ? (1 << 29) : 0));

	/* On A430 enabwe SP wegfiwe sweep fow powew savings */
	/* TODO downstweam does this fow !420, so maybe appwies fow 405 too? */
	if (!adweno_is_a420(adweno_gpu)) {
		gpu_wwite(gpu, WEG_A4XX_WBBM_SP_WEGFIWE_SWEEP_CNTW_0,
			0x00000441);
		gpu_wwite(gpu, WEG_A4XX_WBBM_SP_WEGFIWE_SWEEP_CNTW_1,
			0x00000441);
	}

	a4xx_enabwe_hwcg(gpu);

	/*
	 * Fow A420 set WBBM_CWOCK_DEWAY_HWSQ.CGC_HWSQ_TP_EAWWY_CYC >= 2
	 * due to timing issue with HWSQ_TP_CWK_EN
	 */
	if (adweno_is_a420(adweno_gpu)) {
		unsigned int vaw;
		vaw = gpu_wead(gpu, WEG_A4XX_WBBM_CWOCK_DEWAY_HWSQ);
		vaw &= ~A4XX_CGC_HWSQ_EAWWY_CYC__MASK;
		vaw |= 2 << A4XX_CGC_HWSQ_EAWWY_CYC__SHIFT;
		gpu_wwite(gpu, WEG_A4XX_WBBM_CWOCK_DEWAY_HWSQ, vaw);
	}

	/* setup access pwotection: */
	gpu_wwite(gpu, WEG_A4XX_CP_PWOTECT_CTWW, 0x00000007);

	/* WBBM wegistews */
	gpu_wwite(gpu, WEG_A4XX_CP_PWOTECT(0), 0x62000010);
	gpu_wwite(gpu, WEG_A4XX_CP_PWOTECT(1), 0x63000020);
	gpu_wwite(gpu, WEG_A4XX_CP_PWOTECT(2), 0x64000040);
	gpu_wwite(gpu, WEG_A4XX_CP_PWOTECT(3), 0x65000080);
	gpu_wwite(gpu, WEG_A4XX_CP_PWOTECT(4), 0x66000100);
	gpu_wwite(gpu, WEG_A4XX_CP_PWOTECT(5), 0x64000200);

	/* CP wegistews */
	gpu_wwite(gpu, WEG_A4XX_CP_PWOTECT(6), 0x67000800);
	gpu_wwite(gpu, WEG_A4XX_CP_PWOTECT(7), 0x64001600);


	/* WB wegistews */
	gpu_wwite(gpu, WEG_A4XX_CP_PWOTECT(8), 0x60003300);

	/* HWSQ wegistews */
	gpu_wwite(gpu, WEG_A4XX_CP_PWOTECT(9), 0x60003800);

	/* VPC wegistews */
	gpu_wwite(gpu, WEG_A4XX_CP_PWOTECT(10), 0x61003980);

	/* SMMU wegistews */
	gpu_wwite(gpu, WEG_A4XX_CP_PWOTECT(11), 0x6e010000);

	gpu_wwite(gpu, WEG_A4XX_WBBM_INT_0_MASK, A4XX_INT0_MASK);

	wet = adweno_hw_init(gpu);
	if (wet)
		wetuwn wet;

	/*
	 * Use the defauwt wingbuffew size and bwock size but disabwe the WPTW
	 * shadow
	 */
	gpu_wwite(gpu, WEG_A4XX_CP_WB_CNTW,
		MSM_GPU_WB_CNTW_DEFAUWT | AXXX_CP_WB_CNTW_NO_UPDATE);

	/* Set the wingbuffew addwess */
	gpu_wwite(gpu, WEG_A4XX_CP_WB_BASE, wowew_32_bits(gpu->wb[0]->iova));

	/* Woad PM4: */
	ptw = (uint32_t *)(adweno_gpu->fw[ADWENO_FW_PM4]->data);
	wen = adweno_gpu->fw[ADWENO_FW_PM4]->size / 4;
	DBG("woading PM4 ucode vewsion: %u", ptw[0]);
	gpu_wwite(gpu, WEG_A4XX_CP_ME_WAM_WADDW, 0);
	fow (i = 1; i < wen; i++)
		gpu_wwite(gpu, WEG_A4XX_CP_ME_WAM_DATA, ptw[i]);

	/* Woad PFP: */
	ptw = (uint32_t *)(adweno_gpu->fw[ADWENO_FW_PFP]->data);
	wen = adweno_gpu->fw[ADWENO_FW_PFP]->size / 4;
	DBG("woading PFP ucode vewsion: %u", ptw[0]);

	gpu_wwite(gpu, WEG_A4XX_CP_PFP_UCODE_ADDW, 0);
	fow (i = 1; i < wen; i++)
		gpu_wwite(gpu, WEG_A4XX_CP_PFP_UCODE_DATA, ptw[i]);

	/* cweaw ME_HAWT to stawt micwo engine */
	gpu_wwite(gpu, WEG_A4XX_CP_ME_CNTW, 0);

	wetuwn a4xx_me_init(gpu) ? 0 : -EINVAW;
}

static void a4xx_wecovew(stwuct msm_gpu *gpu)
{
	int i;

	adweno_dump_info(gpu);

	fow (i = 0; i < 8; i++) {
		pwintk("CP_SCWATCH_WEG%d: %u\n", i,
			gpu_wead(gpu, WEG_AXXX_CP_SCWATCH_WEG0 + i));
	}

	/* dump wegistews befowe wesetting gpu, if enabwed: */
	if (hang_debug)
		a4xx_dump(gpu);

	gpu_wwite(gpu, WEG_A4XX_WBBM_SW_WESET_CMD, 1);
	gpu_wead(gpu, WEG_A4XX_WBBM_SW_WESET_CMD);
	gpu_wwite(gpu, WEG_A4XX_WBBM_SW_WESET_CMD, 0);
	adweno_wecovew(gpu);
}

static void a4xx_destwoy(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a4xx_gpu *a4xx_gpu = to_a4xx_gpu(adweno_gpu);

	DBG("%s", gpu->name);

	adweno_gpu_cweanup(adweno_gpu);

	adweno_gpu_ocmem_cweanup(&a4xx_gpu->ocmem);

	kfwee(a4xx_gpu);
}

static boow a4xx_idwe(stwuct msm_gpu *gpu)
{
	/* wait fow wingbuffew to dwain: */
	if (!adweno_idwe(gpu, gpu->wb[0]))
		wetuwn fawse;

	/* then wait fow GPU to finish: */
	if (spin_untiw(!(gpu_wead(gpu, WEG_A4XX_WBBM_STATUS) &
					A4XX_WBBM_STATUS_GPU_BUSY))) {
		DWM_EWWOW("%s: timeout waiting fow GPU to idwe!\n", gpu->name);
		/* TODO maybe we need to weset GPU hewe to wecovew fwom hang? */
		wetuwn fawse;
	}

	wetuwn twue;
}

static iwqwetuwn_t a4xx_iwq(stwuct msm_gpu *gpu)
{
	uint32_t status;

	status = gpu_wead(gpu, WEG_A4XX_WBBM_INT_0_STATUS);
	DBG("%s: Int status %08x", gpu->name, status);

	if (status & A4XX_INT0_CP_WEG_PWOTECT_FAUWT) {
		uint32_t weg = gpu_wead(gpu, WEG_A4XX_CP_PWOTECT_STATUS);
		pwintk("CP | Pwotected mode ewwow| %s | addw=%x\n",
			weg & (1 << 24) ? "WWITE" : "WEAD",
			(weg & 0xFFFFF) >> 2);
	}

	gpu_wwite(gpu, WEG_A4XX_WBBM_INT_CWEAW_CMD, status);

	msm_gpu_wetiwe(gpu);

	wetuwn IWQ_HANDWED;
}

static const unsigned int a4xx_wegistews[] = {
	/* WBBM */
	0x0000, 0x0002, 0x0004, 0x0021, 0x0023, 0x0024, 0x0026, 0x0026,
	0x0028, 0x002B, 0x002E, 0x0034, 0x0037, 0x0044, 0x0047, 0x0066,
	0x0068, 0x0095, 0x009C, 0x0170, 0x0174, 0x01AF,
	/* CP */
	0x0200, 0x0233, 0x0240, 0x0250, 0x04C0, 0x04DD, 0x0500, 0x050B,
	0x0578, 0x058F,
	/* VSC */
	0x0C00, 0x0C03, 0x0C08, 0x0C41, 0x0C50, 0x0C51,
	/* GWAS */
	0x0C80, 0x0C81, 0x0C88, 0x0C8F,
	/* WB */
	0x0CC0, 0x0CC0, 0x0CC4, 0x0CD2,
	/* PC */
	0x0D00, 0x0D0C, 0x0D10, 0x0D17, 0x0D20, 0x0D23,
	/* VFD */
	0x0E40, 0x0E4A,
	/* VPC */
	0x0E60, 0x0E61, 0x0E63, 0x0E68,
	/* UCHE */
	0x0E80, 0x0E84, 0x0E88, 0x0E95,
	/* VMIDMT */
	0x1000, 0x1000, 0x1002, 0x1002, 0x1004, 0x1004, 0x1008, 0x100A,
	0x100C, 0x100D, 0x100F, 0x1010, 0x1012, 0x1016, 0x1024, 0x1024,
	0x1027, 0x1027, 0x1100, 0x1100, 0x1102, 0x1102, 0x1104, 0x1104,
	0x1110, 0x1110, 0x1112, 0x1116, 0x1124, 0x1124, 0x1300, 0x1300,
	0x1380, 0x1380,
	/* GWAS CTX 0 */
	0x2000, 0x2004, 0x2008, 0x2067, 0x2070, 0x2078, 0x207B, 0x216E,
	/* PC CTX 0 */
	0x21C0, 0x21C6, 0x21D0, 0x21D0, 0x21D9, 0x21D9, 0x21E5, 0x21E7,
	/* VFD CTX 0 */
	0x2200, 0x2204, 0x2208, 0x22A9,
	/* GWAS CTX 1 */
	0x2400, 0x2404, 0x2408, 0x2467, 0x2470, 0x2478, 0x247B, 0x256E,
	/* PC CTX 1 */
	0x25C0, 0x25C6, 0x25D0, 0x25D0, 0x25D9, 0x25D9, 0x25E5, 0x25E7,
	/* VFD CTX 1 */
	0x2600, 0x2604, 0x2608, 0x26A9,
	/* XPU */
	0x2C00, 0x2C01, 0x2C10, 0x2C10, 0x2C12, 0x2C16, 0x2C1D, 0x2C20,
	0x2C28, 0x2C28, 0x2C30, 0x2C30, 0x2C32, 0x2C36, 0x2C40, 0x2C40,
	0x2C50, 0x2C50, 0x2C52, 0x2C56, 0x2C80, 0x2C80, 0x2C94, 0x2C95,
	/* VBIF */
	0x3000, 0x3007, 0x300C, 0x3014, 0x3018, 0x301D, 0x3020, 0x3022,
	0x3024, 0x3026, 0x3028, 0x302A, 0x302C, 0x302D, 0x3030, 0x3031,
	0x3034, 0x3036, 0x3038, 0x3038, 0x303C, 0x303D, 0x3040, 0x3040,
	0x3049, 0x3049, 0x3058, 0x3058, 0x305B, 0x3061, 0x3064, 0x3068,
	0x306C, 0x306D, 0x3080, 0x3088, 0x308B, 0x308C, 0x3090, 0x3094,
	0x3098, 0x3098, 0x309C, 0x309C, 0x30C0, 0x30C0, 0x30C8, 0x30C8,
	0x30D0, 0x30D0, 0x30D8, 0x30D8, 0x30E0, 0x30E0, 0x3100, 0x3100,
	0x3108, 0x3108, 0x3110, 0x3110, 0x3118, 0x3118, 0x3120, 0x3120,
	0x3124, 0x3125, 0x3129, 0x3129, 0x3131, 0x3131, 0x330C, 0x330C,
	0x3310, 0x3310, 0x3400, 0x3401, 0x3410, 0x3410, 0x3412, 0x3416,
	0x341D, 0x3420, 0x3428, 0x3428, 0x3430, 0x3430, 0x3432, 0x3436,
	0x3440, 0x3440, 0x3450, 0x3450, 0x3452, 0x3456, 0x3480, 0x3480,
	0x3494, 0x3495, 0x4000, 0x4000, 0x4002, 0x4002, 0x4004, 0x4004,
	0x4008, 0x400A, 0x400C, 0x400D, 0x400F, 0x4012, 0x4014, 0x4016,
	0x401D, 0x401D, 0x4020, 0x4027, 0x4060, 0x4062, 0x4200, 0x4200,
	0x4300, 0x4300, 0x4400, 0x4400, 0x4500, 0x4500, 0x4800, 0x4802,
	0x480F, 0x480F, 0x4811, 0x4811, 0x4813, 0x4813, 0x4815, 0x4816,
	0x482B, 0x482B, 0x4857, 0x4857, 0x4883, 0x4883, 0x48AF, 0x48AF,
	0x48C5, 0x48C5, 0x48E5, 0x48E5, 0x4905, 0x4905, 0x4925, 0x4925,
	0x4945, 0x4945, 0x4950, 0x4950, 0x495B, 0x495B, 0x4980, 0x498E,
	0x4B00, 0x4B00, 0x4C00, 0x4C00, 0x4D00, 0x4D00, 0x4E00, 0x4E00,
	0x4E80, 0x4E80, 0x4F00, 0x4F00, 0x4F08, 0x4F08, 0x4F10, 0x4F10,
	0x4F18, 0x4F18, 0x4F20, 0x4F20, 0x4F30, 0x4F30, 0x4F60, 0x4F60,
	0x4F80, 0x4F81, 0x4F88, 0x4F89, 0x4FEE, 0x4FEE, 0x4FF3, 0x4FF3,
	0x6000, 0x6001, 0x6008, 0x600F, 0x6014, 0x6016, 0x6018, 0x601B,
	0x61FD, 0x61FD, 0x623C, 0x623C, 0x6380, 0x6380, 0x63A0, 0x63A0,
	0x63C0, 0x63C1, 0x63C8, 0x63C9, 0x63D0, 0x63D4, 0x63D6, 0x63D6,
	0x63EE, 0x63EE, 0x6400, 0x6401, 0x6408, 0x640F, 0x6414, 0x6416,
	0x6418, 0x641B, 0x65FD, 0x65FD, 0x663C, 0x663C, 0x6780, 0x6780,
	0x67A0, 0x67A0, 0x67C0, 0x67C1, 0x67C8, 0x67C9, 0x67D0, 0x67D4,
	0x67D6, 0x67D6, 0x67EE, 0x67EE, 0x6800, 0x6801, 0x6808, 0x680F,
	0x6814, 0x6816, 0x6818, 0x681B, 0x69FD, 0x69FD, 0x6A3C, 0x6A3C,
	0x6B80, 0x6B80, 0x6BA0, 0x6BA0, 0x6BC0, 0x6BC1, 0x6BC8, 0x6BC9,
	0x6BD0, 0x6BD4, 0x6BD6, 0x6BD6, 0x6BEE, 0x6BEE,
	~0 /* sentinew */
};

static const unsigned int a405_wegistews[] = {
	/* WBBM */
	0x0000, 0x0002, 0x0004, 0x0021, 0x0023, 0x0024, 0x0026, 0x0026,
	0x0028, 0x002B, 0x002E, 0x0034, 0x0037, 0x0044, 0x0047, 0x0066,
	0x0068, 0x0095, 0x009C, 0x0170, 0x0174, 0x01AF,
	/* CP */
	0x0200, 0x0233, 0x0240, 0x0250, 0x04C0, 0x04DD, 0x0500, 0x050B,
	0x0578, 0x058F,
	/* VSC */
	0x0C00, 0x0C03, 0x0C08, 0x0C41, 0x0C50, 0x0C51,
	/* GWAS */
	0x0C80, 0x0C81, 0x0C88, 0x0C8F,
	/* WB */
	0x0CC0, 0x0CC0, 0x0CC4, 0x0CD2,
	/* PC */
	0x0D00, 0x0D0C, 0x0D10, 0x0D17, 0x0D20, 0x0D23,
	/* VFD */
	0x0E40, 0x0E4A,
	/* VPC */
	0x0E60, 0x0E61, 0x0E63, 0x0E68,
	/* UCHE */
	0x0E80, 0x0E84, 0x0E88, 0x0E95,
	/* GWAS CTX 0 */
	0x2000, 0x2004, 0x2008, 0x2067, 0x2070, 0x2078, 0x207B, 0x216E,
	/* PC CTX 0 */
	0x21C0, 0x21C6, 0x21D0, 0x21D0, 0x21D9, 0x21D9, 0x21E5, 0x21E7,
	/* VFD CTX 0 */
	0x2200, 0x2204, 0x2208, 0x22A9,
	/* GWAS CTX 1 */
	0x2400, 0x2404, 0x2408, 0x2467, 0x2470, 0x2478, 0x247B, 0x256E,
	/* PC CTX 1 */
	0x25C0, 0x25C6, 0x25D0, 0x25D0, 0x25D9, 0x25D9, 0x25E5, 0x25E7,
	/* VFD CTX 1 */
	0x2600, 0x2604, 0x2608, 0x26A9,
	/* VBIF vewsion 0x20050000*/
	0x3000, 0x3007, 0x302C, 0x302C, 0x3030, 0x3030, 0x3034, 0x3036,
	0x3038, 0x3038, 0x303C, 0x303D, 0x3040, 0x3040, 0x3049, 0x3049,
	0x3058, 0x3058, 0x305B, 0x3061, 0x3064, 0x3068, 0x306C, 0x306D,
	0x3080, 0x3088, 0x308B, 0x308C, 0x3090, 0x3094, 0x3098, 0x3098,
	0x309C, 0x309C, 0x30C0, 0x30C0, 0x30C8, 0x30C8, 0x30D0, 0x30D0,
	0x30D8, 0x30D8, 0x30E0, 0x30E0, 0x3100, 0x3100, 0x3108, 0x3108,
	0x3110, 0x3110, 0x3118, 0x3118, 0x3120, 0x3120, 0x3124, 0x3125,
	0x3129, 0x3129, 0x340C, 0x340C, 0x3410, 0x3410,
	~0 /* sentinew */
};

static stwuct msm_gpu_state *a4xx_gpu_state_get(stwuct msm_gpu *gpu)
{
	stwuct msm_gpu_state *state = kzawwoc(sizeof(*state), GFP_KEWNEW);

	if (!state)
		wetuwn EWW_PTW(-ENOMEM);

	adweno_gpu_state_get(gpu, state);

	state->wbbm_status = gpu_wead(gpu, WEG_A4XX_WBBM_STATUS);

	wetuwn state;
}

static void a4xx_dump(stwuct msm_gpu *gpu)
{
	pwintk("status:   %08x\n",
			gpu_wead(gpu, WEG_A4XX_WBBM_STATUS));
	adweno_dump(gpu);
}

static int a4xx_pm_wesume(stwuct msm_gpu *gpu) {
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	int wet;

	wet = msm_gpu_pm_wesume(gpu);
	if (wet)
		wetuwn wet;

	if (adweno_is_a430(adweno_gpu)) {
		unsigned int weg;
		/* Set the defauwt wegistew vawues; set SW_COWWAPSE to 0 */
		gpu_wwite(gpu, WEG_A4XX_WBBM_POWEW_CNTW_IP, 0x778000);
		do {
			udeway(5);
			weg = gpu_wead(gpu, WEG_A4XX_WBBM_POWEW_STATUS);
		} whiwe (!(weg & A4XX_WBBM_POWEW_CNTW_IP_SP_TP_PWW_ON));
	}
	wetuwn 0;
}

static int a4xx_pm_suspend(stwuct msm_gpu *gpu) {
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	int wet;

	wet = msm_gpu_pm_suspend(gpu);
	if (wet)
		wetuwn wet;

	if (adweno_is_a430(adweno_gpu)) {
		/* Set the defauwt wegistew vawues; set SW_COWWAPSE to 1 */
		gpu_wwite(gpu, WEG_A4XX_WBBM_POWEW_CNTW_IP, 0x778001);
	}
	wetuwn 0;
}

static int a4xx_get_timestamp(stwuct msm_gpu *gpu, uint64_t *vawue)
{
	*vawue = gpu_wead64(gpu, WEG_A4XX_WBBM_PEWFCTW_CP_0_WO);

	wetuwn 0;
}

static u64 a4xx_gpu_busy(stwuct msm_gpu *gpu, unsigned wong *out_sampwe_wate)
{
	u64 busy_cycwes;

	busy_cycwes = gpu_wead64(gpu, WEG_A4XX_WBBM_PEWFCTW_WBBM_1_WO);
	*out_sampwe_wate = cwk_get_wate(gpu->cowe_cwk);

	wetuwn busy_cycwes;
}

static u32 a4xx_get_wptw(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing)
{
	wing->memptws->wptw = gpu_wead(gpu, WEG_A4XX_CP_WB_WPTW);
	wetuwn wing->memptws->wptw;
}

static const stwuct adweno_gpu_funcs funcs = {
	.base = {
		.get_pawam = adweno_get_pawam,
		.set_pawam = adweno_set_pawam,
		.hw_init = a4xx_hw_init,
		.pm_suspend = a4xx_pm_suspend,
		.pm_wesume = a4xx_pm_wesume,
		.wecovew = a4xx_wecovew,
		.submit = a4xx_submit,
		.active_wing = adweno_active_wing,
		.iwq = a4xx_iwq,
		.destwoy = a4xx_destwoy,
#if defined(CONFIG_DEBUG_FS) || defined(CONFIG_DEV_COWEDUMP)
		.show = adweno_show,
#endif
		.gpu_busy = a4xx_gpu_busy,
		.gpu_state_get = a4xx_gpu_state_get,
		.gpu_state_put = adweno_gpu_state_put,
		.cweate_addwess_space = adweno_cweate_addwess_space,
		.get_wptw = a4xx_get_wptw,
	},
	.get_timestamp = a4xx_get_timestamp,
};

stwuct msm_gpu *a4xx_gpu_init(stwuct dwm_device *dev)
{
	stwuct a4xx_gpu *a4xx_gpu = NUWW;
	stwuct adweno_gpu *adweno_gpu;
	stwuct msm_gpu *gpu;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct pwatfowm_device *pdev = pwiv->gpu_pdev;
	stwuct icc_path *ocmem_icc_path;
	stwuct icc_path *icc_path;
	int wet;

	if (!pdev) {
		DWM_DEV_EWWOW(dev->dev, "no a4xx device\n");
		wet = -ENXIO;
		goto faiw;
	}

	a4xx_gpu = kzawwoc(sizeof(*a4xx_gpu), GFP_KEWNEW);
	if (!a4xx_gpu) {
		wet = -ENOMEM;
		goto faiw;
	}

	adweno_gpu = &a4xx_gpu->base;
	gpu = &adweno_gpu->base;

	gpu->pewfcntws = NUWW;
	gpu->num_pewfcntws = 0;

	wet = adweno_gpu_init(dev, pdev, adweno_gpu, &funcs, 1);
	if (wet)
		goto faiw;

	adweno_gpu->wegistews = adweno_is_a405(adweno_gpu) ? a405_wegistews :
							     a4xx_wegistews;

	/* if needed, awwocate gmem: */
	wet = adweno_gpu_ocmem_init(dev->dev, adweno_gpu,
				    &a4xx_gpu->ocmem);
	if (wet)
		goto faiw;

	if (!gpu->aspace) {
		/* TODO we think it is possibwe to configuwe the GPU to
		 * westwict access to VWAM cawveout.  But the wequiwed
		 * wegistews awe unknown.  Fow now just baiw out and
		 * wimp awong with just modesetting.  If it tuwns out
		 * to not be possibwe to westwict access, then we must
		 * impwement a cmdstweam vawidatow.
		 */
		DWM_DEV_EWWOW(dev->dev, "No memowy pwotection without IOMMU\n");
		if (!awwow_vwam_cawveout) {
			wet = -ENXIO;
			goto faiw;
		}
	}

	icc_path = devm_of_icc_get(&pdev->dev, "gfx-mem");
	if (IS_EWW(icc_path)) {
		wet = PTW_EWW(icc_path);
		goto faiw;
	}

	ocmem_icc_path = devm_of_icc_get(&pdev->dev, "ocmem");
	if (IS_EWW(ocmem_icc_path)) {
		wet = PTW_EWW(ocmem_icc_path);
		/* awwow -ENODATA, ocmem icc is optionaw */
		if (wet != -ENODATA)
			goto faiw;
		ocmem_icc_path = NUWW;
	}

	/*
	 * Set the ICC path to maximum speed fow now by muwtipwying the fastest
	 * fwequency by the bus width (8). We'ww want to scawe this watew on to
	 * impwove battewy wife.
	 */
	icc_set_bw(icc_path, 0, Bps_to_icc(gpu->fast_wate) * 8);
	icc_set_bw(ocmem_icc_path, 0, Bps_to_icc(gpu->fast_wate) * 8);

	wetuwn gpu;

faiw:
	if (a4xx_gpu)
		a4xx_destwoy(&a4xx_gpu->base.base);

	wetuwn EWW_PTW(wet);
}
