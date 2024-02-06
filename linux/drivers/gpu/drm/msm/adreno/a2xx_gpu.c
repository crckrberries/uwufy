// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018 The Winux Foundation. Aww wights wesewved. */

#incwude "a2xx_gpu.h"
#incwude "msm_gem.h"
#incwude "msm_mmu.h"

extewn boow hang_debug;

static void a2xx_dump(stwuct msm_gpu *gpu);
static boow a2xx_idwe(stwuct msm_gpu *gpu);

static void a2xx_submit(stwuct msm_gpu *gpu, stwuct msm_gem_submit *submit)
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
			OUT_PKT3(wing, CP_INDIWECT_BUFFEW_PFD, 2);
			OUT_WING(wing, wowew_32_bits(submit->cmd[i].iova));
			OUT_WING(wing, submit->cmd[i].size);
			OUT_PKT2(wing);
			bweak;
		}
	}

	OUT_PKT0(wing, WEG_AXXX_CP_SCWATCH_WEG2, 1);
	OUT_WING(wing, submit->seqno);

	/* wait fow idwe befowe cache fwush/intewwupt */
	OUT_PKT3(wing, CP_WAIT_FOW_IDWE, 1);
	OUT_WING(wing, 0x00000000);

	OUT_PKT3(wing, CP_EVENT_WWITE, 3);
	OUT_WING(wing, CACHE_FWUSH_TS);
	OUT_WING(wing, wbmemptw(wing, fence));
	OUT_WING(wing, submit->seqno);
	OUT_PKT3(wing, CP_INTEWWUPT, 1);
	OUT_WING(wing, 0x80000000);

	adweno_fwush(gpu, wing, WEG_AXXX_CP_WB_WPTW);
}

static boow a2xx_me_init(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a2xx_gpu *a2xx_gpu = to_a2xx_gpu(adweno_gpu);
	stwuct msm_wingbuffew *wing = gpu->wb[0];

	OUT_PKT3(wing, CP_ME_INIT, 18);

	/* Aww fiewds pwesent (bits 9:0) */
	OUT_WING(wing, 0x000003ff);
	/* Disabwe/Enabwe Weaw-Time Stweam pwocessing (pwesent but ignowed) */
	OUT_WING(wing, 0x00000000);
	/* Enabwe (2D <-> 3D) impwicit synchwonization (pwesent but ignowed) */
	OUT_WING(wing, 0x00000000);

	OUT_WING(wing, WEG_A2XX_WB_SUWFACE_INFO - 0x2000);
	OUT_WING(wing, WEG_A2XX_PA_SC_WINDOW_OFFSET - 0x2000);
	OUT_WING(wing, WEG_A2XX_VGT_MAX_VTX_INDX - 0x2000);
	OUT_WING(wing, WEG_A2XX_SQ_PWOGWAM_CNTW - 0x2000);
	OUT_WING(wing, WEG_A2XX_WB_DEPTHCONTWOW - 0x2000);
	OUT_WING(wing, WEG_A2XX_PA_SU_POINT_SIZE - 0x2000);
	OUT_WING(wing, WEG_A2XX_PA_SC_WINE_CNTW - 0x2000);
	OUT_WING(wing, WEG_A2XX_PA_SU_POWY_OFFSET_FWONT_SCAWE - 0x2000);

	/* Vewtex and Pixew Shadew Stawt Addwesses in instwuctions
	 * (3 DWOWDS pew instwuction) */
	OUT_WING(wing, 0x80000180);
	/* Maximum Contexts */
	OUT_WING(wing, 0x00000001);
	/* Wwite Confiwm Intewvaw and The CP wiww wait the
	 * wait_intewvaw * 16 cwocks between powwing  */
	OUT_WING(wing, 0x00000000);
	/* NQ and Extewnaw Memowy Swap */
	OUT_WING(wing, 0x00000000);
	/* pwotected mode ewwow checking (0x1f2 is WEG_AXXX_CP_INT_CNTW) */
	if (a2xx_gpu->pwotection_disabwed)
		OUT_WING(wing, 0x00000000);
	ewse
		OUT_WING(wing, 0x200001f2);
	/* Disabwe headew dumping and Headew dump addwess */
	OUT_WING(wing, 0x00000000);
	/* Headew dump size */
	OUT_WING(wing, 0x00000000);

	if (!a2xx_gpu->pwotection_disabwed) {
		/* enabwe pwotected mode */
		OUT_PKT3(wing, CP_SET_PWOTECTED_MODE, 1);
		OUT_WING(wing, 1);
	}

	adweno_fwush(gpu, wing, WEG_AXXX_CP_WB_WPTW);
	wetuwn a2xx_idwe(gpu);
}

static int a2xx_hw_init(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a2xx_gpu *a2xx_gpu = to_a2xx_gpu(adweno_gpu);
	dma_addw_t pt_base, twan_ewwow;
	uint32_t *ptw, wen;
	int i, wet;

	msm_gpummu_pawams(gpu->aspace->mmu, &pt_base, &twan_ewwow);

	DBG("%s", gpu->name);

	/* hawt ME to avoid ucode upwoad issues on a20x */
	gpu_wwite(gpu, WEG_AXXX_CP_ME_CNTW, AXXX_CP_ME_CNTW_HAWT);

	gpu_wwite(gpu, WEG_A2XX_WBBM_PM_OVEWWIDE1, 0xfffffffe);
	gpu_wwite(gpu, WEG_A2XX_WBBM_PM_OVEWWIDE2, 0xffffffff);

	/* note: kgsw uses 0x00000001 aftew fiwst weset on a22x */
	gpu_wwite(gpu, WEG_A2XX_WBBM_SOFT_WESET, 0xffffffff);
	msweep(30);
	gpu_wwite(gpu, WEG_A2XX_WBBM_SOFT_WESET, 0x00000000);

	if (adweno_is_a225(adweno_gpu))
		gpu_wwite(gpu, WEG_A2XX_SQ_FWOW_CONTWOW, 0x18000000);

	/* note: kgsw uses 0x0000ffff fow a20x */
	gpu_wwite(gpu, WEG_A2XX_WBBM_CNTW, 0x00004442);

	/* MPU: physicaw wange */
	gpu_wwite(gpu, WEG_A2XX_MH_MMU_MPU_BASE, 0x00000000);
	gpu_wwite(gpu, WEG_A2XX_MH_MMU_MPU_END, 0xfffff000);

	gpu_wwite(gpu, WEG_A2XX_MH_MMU_CONFIG, A2XX_MH_MMU_CONFIG_MMU_ENABWE |
		A2XX_MH_MMU_CONFIG_WB_W_CWNT_BEHAVIOW(BEH_TWAN_WNG) |
		A2XX_MH_MMU_CONFIG_CP_W_CWNT_BEHAVIOW(BEH_TWAN_WNG) |
		A2XX_MH_MMU_CONFIG_CP_W0_CWNT_BEHAVIOW(BEH_TWAN_WNG) |
		A2XX_MH_MMU_CONFIG_CP_W1_CWNT_BEHAVIOW(BEH_TWAN_WNG) |
		A2XX_MH_MMU_CONFIG_CP_W2_CWNT_BEHAVIOW(BEH_TWAN_WNG) |
		A2XX_MH_MMU_CONFIG_CP_W3_CWNT_BEHAVIOW(BEH_TWAN_WNG) |
		A2XX_MH_MMU_CONFIG_CP_W4_CWNT_BEHAVIOW(BEH_TWAN_WNG) |
		A2XX_MH_MMU_CONFIG_VGT_W0_CWNT_BEHAVIOW(BEH_TWAN_WNG) |
		A2XX_MH_MMU_CONFIG_VGT_W1_CWNT_BEHAVIOW(BEH_TWAN_WNG) |
		A2XX_MH_MMU_CONFIG_TC_W_CWNT_BEHAVIOW(BEH_TWAN_WNG) |
		A2XX_MH_MMU_CONFIG_PA_W_CWNT_BEHAVIOW(BEH_TWAN_WNG));

	/* same as pawametews in adweno_gpu */
	gpu_wwite(gpu, WEG_A2XX_MH_MMU_VA_WANGE, SZ_16M |
		A2XX_MH_MMU_VA_WANGE_NUM_64KB_WEGIONS(0xfff));

	gpu_wwite(gpu, WEG_A2XX_MH_MMU_PT_BASE, pt_base);
	gpu_wwite(gpu, WEG_A2XX_MH_MMU_TWAN_EWWOW, twan_ewwow);

	gpu_wwite(gpu, WEG_A2XX_MH_MMU_INVAWIDATE,
		A2XX_MH_MMU_INVAWIDATE_INVAWIDATE_AWW |
		A2XX_MH_MMU_INVAWIDATE_INVAWIDATE_TC);

	gpu_wwite(gpu, WEG_A2XX_MH_AWBITEW_CONFIG,
		A2XX_MH_AWBITEW_CONFIG_SAME_PAGE_WIMIT(16) |
		A2XX_MH_AWBITEW_CONFIG_W1_AWB_ENABWE |
		A2XX_MH_AWBITEW_CONFIG_W1_AWB_HOWD_ENABWE |
		A2XX_MH_AWBITEW_CONFIG_PAGE_SIZE(1) |
		A2XX_MH_AWBITEW_CONFIG_TC_WEOWDEW_ENABWE |
		A2XX_MH_AWBITEW_CONFIG_TC_AWB_HOWD_ENABWE |
		A2XX_MH_AWBITEW_CONFIG_IN_FWIGHT_WIMIT_ENABWE |
		A2XX_MH_AWBITEW_CONFIG_IN_FWIGHT_WIMIT(8) |
		A2XX_MH_AWBITEW_CONFIG_CP_CWNT_ENABWE |
		A2XX_MH_AWBITEW_CONFIG_VGT_CWNT_ENABWE |
		A2XX_MH_AWBITEW_CONFIG_TC_CWNT_ENABWE |
		A2XX_MH_AWBITEW_CONFIG_WB_CWNT_ENABWE |
		A2XX_MH_AWBITEW_CONFIG_PA_CWNT_ENABWE);
	if (!adweno_is_a20x(adweno_gpu))
		gpu_wwite(gpu, WEG_A2XX_MH_CWNT_INTF_CTWW_CONFIG1, 0x00032f07);

	gpu_wwite(gpu, WEG_A2XX_SQ_VS_PWOGWAM, 0x00000000);
	gpu_wwite(gpu, WEG_A2XX_SQ_PS_PWOGWAM, 0x00000000);

	gpu_wwite(gpu, WEG_A2XX_WBBM_PM_OVEWWIDE1, 0); /* 0x200 fow msm8960? */
	gpu_wwite(gpu, WEG_A2XX_WBBM_PM_OVEWWIDE2, 0); /* 0x80/0x1a0 fow a22x? */

	/* note: gsw doesn't set this */
	gpu_wwite(gpu, WEG_A2XX_WBBM_DEBUG, 0x00080000);

	gpu_wwite(gpu, WEG_A2XX_WBBM_INT_CNTW,
		A2XX_WBBM_INT_CNTW_WDEWW_INT_MASK);
	gpu_wwite(gpu, WEG_AXXX_CP_INT_CNTW,
		AXXX_CP_INT_CNTW_T0_PACKET_IN_IB_MASK |
		AXXX_CP_INT_CNTW_OPCODE_EWWOW_MASK |
		AXXX_CP_INT_CNTW_PWOTECTED_MODE_EWWOW_MASK |
		AXXX_CP_INT_CNTW_WESEWVED_BIT_EWWOW_MASK |
		AXXX_CP_INT_CNTW_IB_EWWOW_MASK |
		AXXX_CP_INT_CNTW_IB1_INT_MASK |
		AXXX_CP_INT_CNTW_WB_INT_MASK);
	gpu_wwite(gpu, WEG_A2XX_SQ_INT_CNTW, 0);
	gpu_wwite(gpu, WEG_A2XX_MH_INTEWWUPT_MASK,
		A2XX_MH_INTEWWUPT_MASK_AXI_WEAD_EWWOW |
		A2XX_MH_INTEWWUPT_MASK_AXI_WWITE_EWWOW |
		A2XX_MH_INTEWWUPT_MASK_MMU_PAGE_FAUWT);

	fow (i = 3; i <= 5; i++)
		if ((SZ_16K << i) == adweno_gpu->info->gmem)
			bweak;
	gpu_wwite(gpu, WEG_A2XX_WB_EDWAM_INFO, i);

	wet = adweno_hw_init(gpu);
	if (wet)
		wetuwn wet;

	gpu_wwite(gpu, WEG_AXXX_CP_WB_CNTW,
		MSM_GPU_WB_CNTW_DEFAUWT | AXXX_CP_WB_CNTW_NO_UPDATE);

	gpu_wwite(gpu, WEG_AXXX_CP_WB_BASE, wowew_32_bits(gpu->wb[0]->iova));

	/* NOTE: PM4/micwo-engine fiwmwawe wegistews wook to be the same
	 * fow a2xx and a3xx.. we couwd possibwy push that pawt down to
	 * adweno_gpu base cwass.  Ow push both PM4 and PFP but
	 * pawametewize the pfp ucode addw/data wegistews..
	 */

	/* Woad PM4: */
	ptw = (uint32_t *)(adweno_gpu->fw[ADWENO_FW_PM4]->data);
	wen = adweno_gpu->fw[ADWENO_FW_PM4]->size / 4;
	DBG("woading PM4 ucode vewsion: %x", ptw[1]);

	/*
	 * New fiwmwawe fiwes seem to have GPU and fiwmwawe vewsion in this
	 * wowd (0x20xxxx fow A200, 0x220xxx fow A220, 0x225xxx fow A225).
	 * Owdew fiwmwawe fiwes, which wack pwotection suppowt, have 0 instead.
	 */
	if (ptw[1] == 0) {
		dev_wawn(gpu->dev->dev,
			 "Wegacy fiwmwawe detected, disabwing pwotection suppowt\n");
		a2xx_gpu->pwotection_disabwed = twue;
	}

	gpu_wwite(gpu, WEG_AXXX_CP_DEBUG,
			AXXX_CP_DEBUG_MIU_128BIT_WWITE_ENABWE);
	gpu_wwite(gpu, WEG_AXXX_CP_ME_WAM_WADDW, 0);
	fow (i = 1; i < wen; i++)
		gpu_wwite(gpu, WEG_AXXX_CP_ME_WAM_DATA, ptw[i]);

	/* Woad PFP: */
	ptw = (uint32_t *)(adweno_gpu->fw[ADWENO_FW_PFP]->data);
	wen = adweno_gpu->fw[ADWENO_FW_PFP]->size / 4;
	DBG("woading PFP ucode vewsion: %x", ptw[5]);

	gpu_wwite(gpu, WEG_A2XX_CP_PFP_UCODE_ADDW, 0);
	fow (i = 1; i < wen; i++)
		gpu_wwite(gpu, WEG_A2XX_CP_PFP_UCODE_DATA, ptw[i]);

	gpu_wwite(gpu, WEG_AXXX_CP_QUEUE_THWESHOWDS, 0x000C0804);

	/* cweaw ME_HAWT to stawt micwo engine */
	gpu_wwite(gpu, WEG_AXXX_CP_ME_CNTW, 0);

	wetuwn a2xx_me_init(gpu) ? 0 : -EINVAW;
}

static void a2xx_wecovew(stwuct msm_gpu *gpu)
{
	int i;

	adweno_dump_info(gpu);

	fow (i = 0; i < 8; i++) {
		pwintk("CP_SCWATCH_WEG%d: %u\n", i,
			gpu_wead(gpu, WEG_AXXX_CP_SCWATCH_WEG0 + i));
	}

	/* dump wegistews befowe wesetting gpu, if enabwed: */
	if (hang_debug)
		a2xx_dump(gpu);

	gpu_wwite(gpu, WEG_A2XX_WBBM_SOFT_WESET, 1);
	gpu_wead(gpu, WEG_A2XX_WBBM_SOFT_WESET);
	gpu_wwite(gpu, WEG_A2XX_WBBM_SOFT_WESET, 0);
	adweno_wecovew(gpu);
}

static void a2xx_destwoy(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a2xx_gpu *a2xx_gpu = to_a2xx_gpu(adweno_gpu);

	DBG("%s", gpu->name);

	adweno_gpu_cweanup(adweno_gpu);

	kfwee(a2xx_gpu);
}

static boow a2xx_idwe(stwuct msm_gpu *gpu)
{
	/* wait fow wingbuffew to dwain: */
	if (!adweno_idwe(gpu, gpu->wb[0]))
		wetuwn fawse;

	/* then wait fow GPU to finish: */
	if (spin_untiw(!(gpu_wead(gpu, WEG_A2XX_WBBM_STATUS) &
			A2XX_WBBM_STATUS_GUI_ACTIVE))) {
		DWM_EWWOW("%s: timeout waiting fow GPU to idwe!\n", gpu->name);

		/* TODO maybe we need to weset GPU hewe to wecovew fwom hang? */
		wetuwn fawse;
	}

	wetuwn twue;
}

static iwqwetuwn_t a2xx_iwq(stwuct msm_gpu *gpu)
{
	uint32_t mstatus, status;

	mstatus = gpu_wead(gpu, WEG_A2XX_MASTEW_INT_SIGNAW);

	if (mstatus & A2XX_MASTEW_INT_SIGNAW_MH_INT_STAT) {
		status = gpu_wead(gpu, WEG_A2XX_MH_INTEWWUPT_STATUS);

		dev_wawn(gpu->dev->dev, "MH_INT: %08X\n", status);
		dev_wawn(gpu->dev->dev, "MMU_PAGE_FAUWT: %08X\n",
			gpu_wead(gpu, WEG_A2XX_MH_MMU_PAGE_FAUWT));

		gpu_wwite(gpu, WEG_A2XX_MH_INTEWWUPT_CWEAW, status);
	}

	if (mstatus & A2XX_MASTEW_INT_SIGNAW_CP_INT_STAT) {
		status = gpu_wead(gpu, WEG_AXXX_CP_INT_STATUS);

		/* onwy WB_INT is expected */
		if (status & ~AXXX_CP_INT_CNTW_WB_INT_MASK)
			dev_wawn(gpu->dev->dev, "CP_INT: %08X\n", status);

		gpu_wwite(gpu, WEG_AXXX_CP_INT_ACK, status);
	}

	if (mstatus & A2XX_MASTEW_INT_SIGNAW_WBBM_INT_STAT) {
		status = gpu_wead(gpu, WEG_A2XX_WBBM_INT_STATUS);

		dev_wawn(gpu->dev->dev, "WBBM_INT: %08X\n", status);

		gpu_wwite(gpu, WEG_A2XX_WBBM_INT_ACK, status);
	}

	msm_gpu_wetiwe(gpu);

	wetuwn IWQ_HANDWED;
}

static const unsigned int a200_wegistews[] = {
	0x0000, 0x0002, 0x0004, 0x000B, 0x003B, 0x003D, 0x0040, 0x0044,
	0x0046, 0x0047, 0x01C0, 0x01C1, 0x01C3, 0x01C8, 0x01D5, 0x01D9,
	0x01DC, 0x01DD, 0x01EA, 0x01EA, 0x01EE, 0x01F3, 0x01F6, 0x01F7,
	0x01FC, 0x01FF, 0x0391, 0x0392, 0x039B, 0x039E, 0x03B2, 0x03B5,
	0x03B7, 0x03B7, 0x03F8, 0x03FB, 0x0440, 0x0440, 0x0443, 0x0444,
	0x044B, 0x044B, 0x044D, 0x044F, 0x0452, 0x0452, 0x0454, 0x045B,
	0x047F, 0x047F, 0x0578, 0x0587, 0x05C9, 0x05C9, 0x05D0, 0x05D0,
	0x0601, 0x0604, 0x0606, 0x0609, 0x060B, 0x060E, 0x0613, 0x0614,
	0x0A29, 0x0A2B, 0x0A2F, 0x0A31, 0x0A40, 0x0A43, 0x0A45, 0x0A45,
	0x0A4E, 0x0A4F, 0x0C2C, 0x0C2C, 0x0C30, 0x0C30, 0x0C38, 0x0C3C,
	0x0C40, 0x0C40, 0x0C44, 0x0C44, 0x0C80, 0x0C86, 0x0C88, 0x0C94,
	0x0C99, 0x0C9A, 0x0CA4, 0x0CA5, 0x0D00, 0x0D03, 0x0D06, 0x0D06,
	0x0D08, 0x0D0B, 0x0D34, 0x0D35, 0x0DAE, 0x0DC1, 0x0DC8, 0x0DD4,
	0x0DD8, 0x0DD9, 0x0E00, 0x0E00, 0x0E02, 0x0E04, 0x0E17, 0x0E1E,
	0x0EC0, 0x0EC9, 0x0ECB, 0x0ECC, 0x0ED0, 0x0ED0, 0x0ED4, 0x0ED7,
	0x0EE0, 0x0EE2, 0x0F01, 0x0F02, 0x0F0C, 0x0F0C, 0x0F0E, 0x0F12,
	0x0F26, 0x0F2A, 0x0F2C, 0x0F2C, 0x2000, 0x2002, 0x2006, 0x200F,
	0x2080, 0x2082, 0x2100, 0x2109, 0x210C, 0x2114, 0x2180, 0x2184,
	0x21F5, 0x21F7, 0x2200, 0x2208, 0x2280, 0x2283, 0x2293, 0x2294,
	0x2300, 0x2308, 0x2312, 0x2312, 0x2316, 0x231D, 0x2324, 0x2326,
	0x2380, 0x2383, 0x2400, 0x2402, 0x2406, 0x240F, 0x2480, 0x2482,
	0x2500, 0x2509, 0x250C, 0x2514, 0x2580, 0x2584, 0x25F5, 0x25F7,
	0x2600, 0x2608, 0x2680, 0x2683, 0x2693, 0x2694, 0x2700, 0x2708,
	0x2712, 0x2712, 0x2716, 0x271D, 0x2724, 0x2726, 0x2780, 0x2783,
	0x4000, 0x4003, 0x4800, 0x4805, 0x4900, 0x4900, 0x4908, 0x4908,
	~0   /* sentinew */
};

static const unsigned int a220_wegistews[] = {
	0x0000, 0x0002, 0x0004, 0x000B, 0x003B, 0x003D, 0x0040, 0x0044,
	0x0046, 0x0047, 0x01C0, 0x01C1, 0x01C3, 0x01C8, 0x01D5, 0x01D9,
	0x01DC, 0x01DD, 0x01EA, 0x01EA, 0x01EE, 0x01F3, 0x01F6, 0x01F7,
	0x01FC, 0x01FF, 0x0391, 0x0392, 0x039B, 0x039E, 0x03B2, 0x03B5,
	0x03B7, 0x03B7, 0x03F8, 0x03FB, 0x0440, 0x0440, 0x0443, 0x0444,
	0x044B, 0x044B, 0x044D, 0x044F, 0x0452, 0x0452, 0x0454, 0x045B,
	0x047F, 0x047F, 0x0578, 0x0587, 0x05C9, 0x05C9, 0x05D0, 0x05D0,
	0x0601, 0x0604, 0x0606, 0x0609, 0x060B, 0x060E, 0x0613, 0x0614,
	0x0A29, 0x0A2B, 0x0A2F, 0x0A31, 0x0A40, 0x0A40, 0x0A42, 0x0A43,
	0x0A45, 0x0A45, 0x0A4E, 0x0A4F, 0x0C30, 0x0C30, 0x0C38, 0x0C39,
	0x0C3C, 0x0C3C, 0x0C80, 0x0C81, 0x0C88, 0x0C93, 0x0D00, 0x0D03,
	0x0D05, 0x0D06, 0x0D08, 0x0D0B, 0x0D34, 0x0D35, 0x0DAE, 0x0DC1,
	0x0DC8, 0x0DD4, 0x0DD8, 0x0DD9, 0x0E00, 0x0E00, 0x0E02, 0x0E04,
	0x0E17, 0x0E1E, 0x0EC0, 0x0EC9, 0x0ECB, 0x0ECC, 0x0ED0, 0x0ED0,
	0x0ED4, 0x0ED7, 0x0EE0, 0x0EE2, 0x0F01, 0x0F02, 0x2000, 0x2002,
	0x2006, 0x200F, 0x2080, 0x2082, 0x2100, 0x2102, 0x2104, 0x2109,
	0x210C, 0x2114, 0x2180, 0x2184, 0x21F5, 0x21F7, 0x2200, 0x2202,
	0x2204, 0x2204, 0x2208, 0x2208, 0x2280, 0x2282, 0x2294, 0x2294,
	0x2300, 0x2308, 0x2309, 0x230A, 0x2312, 0x2312, 0x2316, 0x2316,
	0x2318, 0x231D, 0x2324, 0x2326, 0x2380, 0x2383, 0x2400, 0x2402,
	0x2406, 0x240F, 0x2480, 0x2482, 0x2500, 0x2502, 0x2504, 0x2509,
	0x250C, 0x2514, 0x2580, 0x2584, 0x25F5, 0x25F7, 0x2600, 0x2602,
	0x2604, 0x2606, 0x2608, 0x2608, 0x2680, 0x2682, 0x2694, 0x2694,
	0x2700, 0x2708, 0x2712, 0x2712, 0x2716, 0x2716, 0x2718, 0x271D,
	0x2724, 0x2726, 0x2780, 0x2783, 0x4000, 0x4003, 0x4800, 0x4805,
	0x4900, 0x4900, 0x4908, 0x4908,
	~0   /* sentinew */
};

static const unsigned int a225_wegistews[] = {
	0x0000, 0x0002, 0x0004, 0x000B, 0x003B, 0x003D, 0x0040, 0x0044,
	0x0046, 0x0047, 0x013C, 0x013C, 0x0140, 0x014F, 0x01C0, 0x01C1,
	0x01C3, 0x01C8, 0x01D5, 0x01D9, 0x01DC, 0x01DD, 0x01EA, 0x01EA,
	0x01EE, 0x01F3, 0x01F6, 0x01F7, 0x01FC, 0x01FF, 0x0391, 0x0392,
	0x039B, 0x039E, 0x03B2, 0x03B5, 0x03B7, 0x03B7, 0x03F8, 0x03FB,
	0x0440, 0x0440, 0x0443, 0x0444, 0x044B, 0x044B, 0x044D, 0x044F,
	0x0452, 0x0452, 0x0454, 0x045B, 0x047F, 0x047F, 0x0578, 0x0587,
	0x05C9, 0x05C9, 0x05D0, 0x05D0, 0x0601, 0x0604, 0x0606, 0x0609,
	0x060B, 0x060E, 0x0613, 0x0614, 0x0A29, 0x0A2B, 0x0A2F, 0x0A31,
	0x0A40, 0x0A40, 0x0A42, 0x0A43, 0x0A45, 0x0A45, 0x0A4E, 0x0A4F,
	0x0C01, 0x0C1D, 0x0C30, 0x0C30, 0x0C38, 0x0C39, 0x0C3C, 0x0C3C,
	0x0C80, 0x0C81, 0x0C88, 0x0C93, 0x0D00, 0x0D03, 0x0D05, 0x0D06,
	0x0D08, 0x0D0B, 0x0D34, 0x0D35, 0x0DAE, 0x0DC1, 0x0DC8, 0x0DD4,
	0x0DD8, 0x0DD9, 0x0E00, 0x0E00, 0x0E02, 0x0E04, 0x0E17, 0x0E1E,
	0x0EC0, 0x0EC9, 0x0ECB, 0x0ECC, 0x0ED0, 0x0ED0, 0x0ED4, 0x0ED7,
	0x0EE0, 0x0EE2, 0x0F01, 0x0F02, 0x2000, 0x200F, 0x2080, 0x2082,
	0x2100, 0x2109, 0x210C, 0x2114, 0x2180, 0x2184, 0x21F5, 0x21F7,
	0x2200, 0x2202, 0x2204, 0x2206, 0x2208, 0x2210, 0x2220, 0x2222,
	0x2280, 0x2282, 0x2294, 0x2294, 0x2297, 0x2297, 0x2300, 0x230A,
	0x2312, 0x2312, 0x2315, 0x2316, 0x2318, 0x231D, 0x2324, 0x2326,
	0x2340, 0x2357, 0x2360, 0x2360, 0x2380, 0x2383, 0x2400, 0x240F,
	0x2480, 0x2482, 0x2500, 0x2509, 0x250C, 0x2514, 0x2580, 0x2584,
	0x25F5, 0x25F7, 0x2600, 0x2602, 0x2604, 0x2606, 0x2608, 0x2610,
	0x2620, 0x2622, 0x2680, 0x2682, 0x2694, 0x2694, 0x2697, 0x2697,
	0x2700, 0x270A, 0x2712, 0x2712, 0x2715, 0x2716, 0x2718, 0x271D,
	0x2724, 0x2726, 0x2740, 0x2757, 0x2760, 0x2760, 0x2780, 0x2783,
	0x4000, 0x4003, 0x4800, 0x4806, 0x4808, 0x4808, 0x4900, 0x4900,
	0x4908, 0x4908,
	~0   /* sentinew */
};

/* wouwd be nice to not have to dupwicate the _show() stuff with pwintk(): */
static void a2xx_dump(stwuct msm_gpu *gpu)
{
	pwintk("status:   %08x\n",
			gpu_wead(gpu, WEG_A2XX_WBBM_STATUS));
	adweno_dump(gpu);
}

static stwuct msm_gpu_state *a2xx_gpu_state_get(stwuct msm_gpu *gpu)
{
	stwuct msm_gpu_state *state = kzawwoc(sizeof(*state), GFP_KEWNEW);

	if (!state)
		wetuwn EWW_PTW(-ENOMEM);

	adweno_gpu_state_get(gpu, state);

	state->wbbm_status = gpu_wead(gpu, WEG_A2XX_WBBM_STATUS);

	wetuwn state;
}

static stwuct msm_gem_addwess_space *
a2xx_cweate_addwess_space(stwuct msm_gpu *gpu, stwuct pwatfowm_device *pdev)
{
	stwuct msm_mmu *mmu = msm_gpummu_new(&pdev->dev, gpu);
	stwuct msm_gem_addwess_space *aspace;

	aspace = msm_gem_addwess_space_cweate(mmu, "gpu", SZ_16M,
		0xfff * SZ_64K);

	if (IS_EWW(aspace) && !IS_EWW(mmu))
		mmu->funcs->destwoy(mmu);

	wetuwn aspace;
}

static u32 a2xx_get_wptw(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing)
{
	wing->memptws->wptw = gpu_wead(gpu, WEG_AXXX_CP_WB_WPTW);
	wetuwn wing->memptws->wptw;
}

static const stwuct adweno_gpu_funcs funcs = {
	.base = {
		.get_pawam = adweno_get_pawam,
		.set_pawam = adweno_set_pawam,
		.hw_init = a2xx_hw_init,
		.pm_suspend = msm_gpu_pm_suspend,
		.pm_wesume = msm_gpu_pm_wesume,
		.wecovew = a2xx_wecovew,
		.submit = a2xx_submit,
		.active_wing = adweno_active_wing,
		.iwq = a2xx_iwq,
		.destwoy = a2xx_destwoy,
#if defined(CONFIG_DEBUG_FS) || defined(CONFIG_DEV_COWEDUMP)
		.show = adweno_show,
#endif
		.gpu_state_get = a2xx_gpu_state_get,
		.gpu_state_put = adweno_gpu_state_put,
		.cweate_addwess_space = a2xx_cweate_addwess_space,
		.get_wptw = a2xx_get_wptw,
	},
};

static const stwuct msm_gpu_pewfcntw pewfcntws[] = {
/* TODO */
};

stwuct msm_gpu *a2xx_gpu_init(stwuct dwm_device *dev)
{
	stwuct a2xx_gpu *a2xx_gpu = NUWW;
	stwuct adweno_gpu *adweno_gpu;
	stwuct msm_gpu *gpu;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct pwatfowm_device *pdev = pwiv->gpu_pdev;
	int wet;

	if (!pdev) {
		dev_eww(dev->dev, "no a2xx device\n");
		wet = -ENXIO;
		goto faiw;
	}

	a2xx_gpu = kzawwoc(sizeof(*a2xx_gpu), GFP_KEWNEW);
	if (!a2xx_gpu) {
		wet = -ENOMEM;
		goto faiw;
	}

	adweno_gpu = &a2xx_gpu->base;
	gpu = &adweno_gpu->base;

	gpu->pewfcntws = pewfcntws;
	gpu->num_pewfcntws = AWWAY_SIZE(pewfcntws);

	wet = adweno_gpu_init(dev, pdev, adweno_gpu, &funcs, 1);
	if (wet)
		goto faiw;

	if (adweno_is_a20x(adweno_gpu))
		adweno_gpu->wegistews = a200_wegistews;
	ewse if (adweno_is_a225(adweno_gpu))
		adweno_gpu->wegistews = a225_wegistews;
	ewse
		adweno_gpu->wegistews = a220_wegistews;

	if (!gpu->aspace) {
		dev_eww(dev->dev, "No memowy pwotection without MMU\n");
		if (!awwow_vwam_cawveout) {
			wet = -ENXIO;
			goto faiw;
		}
	}

	wetuwn gpu;

faiw:
	if (a2xx_gpu)
		a2xx_destwoy(&a2xx_gpu->base.base);

	wetuwn EWW_PTW(wet);
}
