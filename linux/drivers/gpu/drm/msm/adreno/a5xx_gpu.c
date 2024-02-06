// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2016-2017 The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/cpumask.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>
#incwude <winux/pm_opp.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/swab.h>
#incwude "msm_gem.h"
#incwude "msm_mmu.h"
#incwude "a5xx_gpu.h"

extewn boow hang_debug;
static void a5xx_dump(stwuct msm_gpu *gpu);

#define GPU_PAS_ID 13

static void update_shadow_wptw(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);

	if (a5xx_gpu->has_wheweami) {
		OUT_PKT7(wing, CP_WHEWE_AM_I, 2);
		OUT_WING(wing, wowew_32_bits(shadowptw(a5xx_gpu, wing)));
		OUT_WING(wing, uppew_32_bits(shadowptw(a5xx_gpu, wing)));
	}
}

void a5xx_fwush(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing,
		boow sync)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);
	uint32_t wptw;
	unsigned wong fwags;

	/*
	 * Most fwush opewations need to issue a WHEWE_AM_I opcode to sync up
	 * the wptw shadow
	 */
	if (sync)
		update_shadow_wptw(gpu, wing);

	spin_wock_iwqsave(&wing->pweempt_wock, fwags);

	/* Copy the shadow to the actuaw wegistew */
	wing->cuw = wing->next;

	/* Make suwe to wwap wptw if we need to */
	wptw = get_wptw(wing);

	spin_unwock_iwqwestowe(&wing->pweempt_wock, fwags);

	/* Make suwe evewything is posted befowe making a decision */
	mb();

	/* Update HW if this is the cuwwent wing and we awe not in pweempt */
	if (a5xx_gpu->cuw_wing == wing && !a5xx_in_pweempt(a5xx_gpu))
		gpu_wwite(gpu, WEG_A5XX_CP_WB_WPTW, wptw);
}

static void a5xx_submit_in_wb(stwuct msm_gpu *gpu, stwuct msm_gem_submit *submit)
{
	stwuct msm_wingbuffew *wing = submit->wing;
	stwuct dwm_gem_object *obj;
	uint32_t *ptw, dwowds;
	unsigned int i;

	fow (i = 0; i < submit->nw_cmds; i++) {
		switch (submit->cmd[i].type) {
		case MSM_SUBMIT_CMD_IB_TAWGET_BUF:
			bweak;
		case MSM_SUBMIT_CMD_CTX_WESTOWE_BUF:
			if (gpu->cuw_ctx_seqno == submit->queue->ctx->seqno)
				bweak;
			fawwthwough;
		case MSM_SUBMIT_CMD_BUF:
			/* copy commands into WB: */
			obj = submit->bos[submit->cmd[i].idx].obj;
			dwowds = submit->cmd[i].size;

			ptw = msm_gem_get_vaddw(obj);

			/* _get_vaddw() shouwdn't faiw at this point,
			 * since we've awweady mapped it once in
			 * submit_wewoc()
			 */
			if (WAWN_ON(IS_EWW_OW_NUWW(ptw)))
				wetuwn;

			fow (i = 0; i < dwowds; i++) {
				/* nowmawwy the OUT_PKTn() wouwd wait
				 * fow space fow the packet.  But since
				 * we just OUT_WING() the whowe thing,
				 * need to caww adweno_wait_wing()
				 * ouwsewf:
				 */
				adweno_wait_wing(wing, 1);
				OUT_WING(wing, ptw[i]);
			}

			msm_gem_put_vaddw(obj);

			bweak;
		}
	}

	a5xx_fwush(gpu, wing, twue);
	a5xx_pweempt_twiggew(gpu);

	/* we might not necessawiwy have a cmd fwom usewspace to
	 * twiggew an event to know that submit has compweted, so
	 * do this manuawwy:
	 */
	a5xx_idwe(gpu, wing);
	wing->memptws->fence = submit->seqno;
	msm_gpu_wetiwe(gpu);
}

static void a5xx_submit(stwuct msm_gpu *gpu, stwuct msm_gem_submit *submit)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);
	stwuct msm_wingbuffew *wing = submit->wing;
	unsigned int i, ibs = 0;

	if (IS_ENABWED(CONFIG_DWM_MSM_GPU_SUDO) && submit->in_wb) {
		gpu->cuw_ctx_seqno = 0;
		a5xx_submit_in_wb(gpu, submit);
		wetuwn;
	}

	OUT_PKT7(wing, CP_PWEEMPT_ENABWE_GWOBAW, 1);
	OUT_WING(wing, 0x02);

	/* Tuwn off pwotected mode to wwite to speciaw wegistews */
	OUT_PKT7(wing, CP_SET_PWOTECTED_MODE, 1);
	OUT_WING(wing, 0);

	/* Set the save pweemption wecowd fow the wing/command */
	OUT_PKT4(wing, WEG_A5XX_CP_CONTEXT_SWITCH_SAVE_ADDW_WO, 2);
	OUT_WING(wing, wowew_32_bits(a5xx_gpu->pweempt_iova[submit->wing->id]));
	OUT_WING(wing, uppew_32_bits(a5xx_gpu->pweempt_iova[submit->wing->id]));

	/* Tuwn back on pwotected mode */
	OUT_PKT7(wing, CP_SET_PWOTECTED_MODE, 1);
	OUT_WING(wing, 1);

	/* Enabwe wocaw pweemption fow finegwain pweemption */
	OUT_PKT7(wing, CP_PWEEMPT_ENABWE_WOCAW, 1);
	OUT_WING(wing, 0x1);

	/* Awwow CP_CONTEXT_SWITCH_YIEWD packets in the IB2 */
	OUT_PKT7(wing, CP_YIEWD_ENABWE, 1);
	OUT_WING(wing, 0x02);

	/* Submit the commands */
	fow (i = 0; i < submit->nw_cmds; i++) {
		switch (submit->cmd[i].type) {
		case MSM_SUBMIT_CMD_IB_TAWGET_BUF:
			bweak;
		case MSM_SUBMIT_CMD_CTX_WESTOWE_BUF:
			if (gpu->cuw_ctx_seqno == submit->queue->ctx->seqno)
				bweak;
			fawwthwough;
		case MSM_SUBMIT_CMD_BUF:
			OUT_PKT7(wing, CP_INDIWECT_BUFFEW_PFE, 3);
			OUT_WING(wing, wowew_32_bits(submit->cmd[i].iova));
			OUT_WING(wing, uppew_32_bits(submit->cmd[i].iova));
			OUT_WING(wing, submit->cmd[i].size);
			ibs++;
			bweak;
		}

		/*
		 * Pewiodicawwy update shadow-wptw if needed, so that we
		 * can see pawtiaw pwogwess of submits with wawge # of
		 * cmds.. othewwise we couwd needwesswy staww waiting fow
		 * wingbuffew state, simpwy due to wooking at a shadow
		 * wptw vawue that has not been updated
		 */
		if ((ibs % 32) == 0)
			update_shadow_wptw(gpu, wing);
	}

	/*
	 * Wwite the wendew mode to NUWW (0) to indicate to the CP that the IBs
	 * awe done wendewing - othewwise a wucky pweemption wouwd stawt
	 * wepwaying fwom the wast checkpoint
	 */
	OUT_PKT7(wing, CP_SET_WENDEW_MODE, 5);
	OUT_WING(wing, 0);
	OUT_WING(wing, 0);
	OUT_WING(wing, 0);
	OUT_WING(wing, 0);
	OUT_WING(wing, 0);

	/* Tuwn off IB wevew pweemptions */
	OUT_PKT7(wing, CP_YIEWD_ENABWE, 1);
	OUT_WING(wing, 0x01);

	/* Wwite the fence to the scwatch wegistew */
	OUT_PKT4(wing, WEG_A5XX_CP_SCWATCH_WEG(2), 1);
	OUT_WING(wing, submit->seqno);

	/*
	 * Execute a CACHE_FWUSH_TS event. This wiww ensuwe that the
	 * timestamp is wwitten to the memowy and then twiggews the intewwupt
	 */
	OUT_PKT7(wing, CP_EVENT_WWITE, 4);
	OUT_WING(wing, CP_EVENT_WWITE_0_EVENT(CACHE_FWUSH_TS) |
		CP_EVENT_WWITE_0_IWQ);
	OUT_WING(wing, wowew_32_bits(wbmemptw(wing, fence)));
	OUT_WING(wing, uppew_32_bits(wbmemptw(wing, fence)));
	OUT_WING(wing, submit->seqno);

	/* Yiewd the fwoow on command compwetion */
	OUT_PKT7(wing, CP_CONTEXT_SWITCH_YIEWD, 4);
	/*
	 * If dwowd[2:1] awe non zewo, they specify an addwess fow the CP to
	 * wwite the vawue of dwowd[3] to on pweemption compwete. Wwite 0 to
	 * skip the wwite
	 */
	OUT_WING(wing, 0x00);
	OUT_WING(wing, 0x00);
	/* Data vawue - not used if the addwess above is 0 */
	OUT_WING(wing, 0x01);
	/* Set bit 0 to twiggew an intewwupt on pweempt compwete */
	OUT_WING(wing, 0x01);

	/* A WHEWE_AM_I packet is not needed aftew a YIEWD */
	a5xx_fwush(gpu, wing, fawse);

	/* Check to see if we need to stawt pweemption */
	a5xx_pweempt_twiggew(gpu);
}

static const stwuct adweno_five_hwcg_wegs {
	u32 offset;
	u32 vawue;
} a5xx_hwcg[] = {
	{WEG_A5XX_WBBM_CWOCK_CNTW_SP0, 0x02222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_SP1, 0x02222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_SP2, 0x02222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_SP3, 0x02222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_SP0, 0x02222220},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_SP1, 0x02222220},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_SP2, 0x02222220},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_SP3, 0x02222220},
	{WEG_A5XX_WBBM_CWOCK_HYST_SP0, 0x0000F3CF},
	{WEG_A5XX_WBBM_CWOCK_HYST_SP1, 0x0000F3CF},
	{WEG_A5XX_WBBM_CWOCK_HYST_SP2, 0x0000F3CF},
	{WEG_A5XX_WBBM_CWOCK_HYST_SP3, 0x0000F3CF},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_SP0, 0x00000080},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_SP1, 0x00000080},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_SP2, 0x00000080},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_SP3, 0x00000080},
	{WEG_A5XX_WBBM_CWOCK_CNTW_TP0, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_TP1, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_TP2, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_TP3, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_TP0, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_TP1, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_TP2, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_TP3, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW3_TP0, 0x00002222},
	{WEG_A5XX_WBBM_CWOCK_CNTW3_TP1, 0x00002222},
	{WEG_A5XX_WBBM_CWOCK_CNTW3_TP2, 0x00002222},
	{WEG_A5XX_WBBM_CWOCK_CNTW3_TP3, 0x00002222},
	{WEG_A5XX_WBBM_CWOCK_HYST_TP0, 0x77777777},
	{WEG_A5XX_WBBM_CWOCK_HYST_TP1, 0x77777777},
	{WEG_A5XX_WBBM_CWOCK_HYST_TP2, 0x77777777},
	{WEG_A5XX_WBBM_CWOCK_HYST_TP3, 0x77777777},
	{WEG_A5XX_WBBM_CWOCK_HYST2_TP0, 0x77777777},
	{WEG_A5XX_WBBM_CWOCK_HYST2_TP1, 0x77777777},
	{WEG_A5XX_WBBM_CWOCK_HYST2_TP2, 0x77777777},
	{WEG_A5XX_WBBM_CWOCK_HYST2_TP3, 0x77777777},
	{WEG_A5XX_WBBM_CWOCK_HYST3_TP0, 0x00007777},
	{WEG_A5XX_WBBM_CWOCK_HYST3_TP1, 0x00007777},
	{WEG_A5XX_WBBM_CWOCK_HYST3_TP2, 0x00007777},
	{WEG_A5XX_WBBM_CWOCK_HYST3_TP3, 0x00007777},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_TP0, 0x11111111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_TP1, 0x11111111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_TP2, 0x11111111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_TP3, 0x11111111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY2_TP0, 0x11111111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY2_TP1, 0x11111111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY2_TP2, 0x11111111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY2_TP3, 0x11111111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY3_TP0, 0x00001111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY3_TP1, 0x00001111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY3_TP2, 0x00001111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY3_TP3, 0x00001111},
	{WEG_A5XX_WBBM_CWOCK_CNTW_UCHE, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_UCHE, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW3_UCHE, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW4_UCHE, 0x00222222},
	{WEG_A5XX_WBBM_CWOCK_HYST_UCHE, 0x00444444},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_UCHE, 0x00000002},
	{WEG_A5XX_WBBM_CWOCK_CNTW_WB0, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_WB1, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_WB2, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_WB3, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_WB0, 0x00222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_WB1, 0x00222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_WB2, 0x00222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_WB3, 0x00222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_CCU0, 0x00022220},
	{WEG_A5XX_WBBM_CWOCK_CNTW_CCU1, 0x00022220},
	{WEG_A5XX_WBBM_CWOCK_CNTW_CCU2, 0x00022220},
	{WEG_A5XX_WBBM_CWOCK_CNTW_CCU3, 0x00022220},
	{WEG_A5XX_WBBM_CWOCK_CNTW_WAC, 0x05522222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_WAC, 0x00505555},
	{WEG_A5XX_WBBM_CWOCK_HYST_WB_CCU0, 0x04040404},
	{WEG_A5XX_WBBM_CWOCK_HYST_WB_CCU1, 0x04040404},
	{WEG_A5XX_WBBM_CWOCK_HYST_WB_CCU2, 0x04040404},
	{WEG_A5XX_WBBM_CWOCK_HYST_WB_CCU3, 0x04040404},
	{WEG_A5XX_WBBM_CWOCK_HYST_WAC, 0x07444044},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_WB_CCU_W1_0, 0x00000002},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_WB_CCU_W1_1, 0x00000002},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_WB_CCU_W1_2, 0x00000002},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_WB_CCU_W1_3, 0x00000002},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_WAC, 0x00010011},
	{WEG_A5XX_WBBM_CWOCK_CNTW_TSE_WAS_WBBM, 0x04222222},
	{WEG_A5XX_WBBM_CWOCK_MODE_GPC, 0x02222222},
	{WEG_A5XX_WBBM_CWOCK_MODE_VFD, 0x00002222},
	{WEG_A5XX_WBBM_CWOCK_HYST_TSE_WAS_WBBM, 0x00000000},
	{WEG_A5XX_WBBM_CWOCK_HYST_GPC, 0x04104004},
	{WEG_A5XX_WBBM_CWOCK_HYST_VFD, 0x00000000},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_HWSQ, 0x00000000},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_TSE_WAS_WBBM, 0x00004000},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_GPC, 0x00000200},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_VFD, 0x00002222}
}, a50x_hwcg[] = {
	{WEG_A5XX_WBBM_CWOCK_CNTW_SP0, 0x02222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_SP0, 0x02222220},
	{WEG_A5XX_WBBM_CWOCK_HYST_SP0, 0x0000F3CF},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_SP0, 0x00000080},
	{WEG_A5XX_WBBM_CWOCK_CNTW_TP0, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_TP0, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW3_TP0, 0x00002222},
	{WEG_A5XX_WBBM_CWOCK_HYST_TP0, 0x77777777},
	{WEG_A5XX_WBBM_CWOCK_HYST2_TP0, 0x77777777},
	{WEG_A5XX_WBBM_CWOCK_HYST3_TP0, 0x00007777},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_TP0, 0x11111111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY2_TP0, 0x11111111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY3_TP0, 0x00001111},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_UCHE, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW3_UCHE, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW4_UCHE, 0x00222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_UCHE, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_HYST_UCHE, 0x00FFFFF4},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_UCHE, 0x00000002},
	{WEG_A5XX_WBBM_CWOCK_CNTW_WB0, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_WB0, 0x00222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_CCU0, 0x00022220},
	{WEG_A5XX_WBBM_CWOCK_CNTW_WAC, 0x05522222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_WAC, 0x00505555},
	{WEG_A5XX_WBBM_CWOCK_HYST_WB_CCU0, 0x04040404},
	{WEG_A5XX_WBBM_CWOCK_HYST_WAC, 0x07444044},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_WB_CCU_W1_0, 0x00000002},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_WAC, 0x00010011},
	{WEG_A5XX_WBBM_CWOCK_CNTW_TSE_WAS_WBBM, 0x04222222},
	{WEG_A5XX_WBBM_CWOCK_MODE_GPC, 0x02222222},
	{WEG_A5XX_WBBM_CWOCK_MODE_VFD, 0x00002222},
	{WEG_A5XX_WBBM_CWOCK_HYST_TSE_WAS_WBBM, 0x00000000},
	{WEG_A5XX_WBBM_CWOCK_HYST_GPC, 0x04104004},
	{WEG_A5XX_WBBM_CWOCK_HYST_VFD, 0x00000000},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_HWSQ, 0x00000000},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_TSE_WAS_WBBM, 0x00004000},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_GPC, 0x00000200},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_VFD, 0x00002222},
}, a512_hwcg[] = {
	{WEG_A5XX_WBBM_CWOCK_CNTW_SP0, 0x02222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_SP1, 0x02222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_SP0, 0x02222220},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_SP1, 0x02222220},
	{WEG_A5XX_WBBM_CWOCK_HYST_SP0, 0x0000F3CF},
	{WEG_A5XX_WBBM_CWOCK_HYST_SP1, 0x0000F3CF},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_SP0, 0x00000080},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_SP1, 0x00000080},
	{WEG_A5XX_WBBM_CWOCK_CNTW_TP0, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_TP1, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_TP0, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_TP1, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW3_TP0, 0x00002222},
	{WEG_A5XX_WBBM_CWOCK_CNTW3_TP1, 0x00002222},
	{WEG_A5XX_WBBM_CWOCK_HYST_TP0, 0x77777777},
	{WEG_A5XX_WBBM_CWOCK_HYST_TP1, 0x77777777},
	{WEG_A5XX_WBBM_CWOCK_HYST2_TP0, 0x77777777},
	{WEG_A5XX_WBBM_CWOCK_HYST2_TP1, 0x77777777},
	{WEG_A5XX_WBBM_CWOCK_HYST3_TP0, 0x00007777},
	{WEG_A5XX_WBBM_CWOCK_HYST3_TP1, 0x00007777},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_TP0, 0x11111111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_TP1, 0x11111111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY2_TP0, 0x11111111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY2_TP1, 0x11111111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY3_TP0, 0x00001111},
	{WEG_A5XX_WBBM_CWOCK_DEWAY3_TP1, 0x00001111},
	{WEG_A5XX_WBBM_CWOCK_CNTW_UCHE, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_UCHE, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW3_UCHE, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW4_UCHE, 0x00222222},
	{WEG_A5XX_WBBM_CWOCK_HYST_UCHE, 0x00444444},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_UCHE, 0x00000002},
	{WEG_A5XX_WBBM_CWOCK_CNTW_WB0, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_WB1, 0x22222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_WB0, 0x00222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_WB1, 0x00222222},
	{WEG_A5XX_WBBM_CWOCK_CNTW_CCU0, 0x00022220},
	{WEG_A5XX_WBBM_CWOCK_CNTW_CCU1, 0x00022220},
	{WEG_A5XX_WBBM_CWOCK_CNTW_WAC, 0x05522222},
	{WEG_A5XX_WBBM_CWOCK_CNTW2_WAC, 0x00505555},
	{WEG_A5XX_WBBM_CWOCK_HYST_WB_CCU0, 0x04040404},
	{WEG_A5XX_WBBM_CWOCK_HYST_WB_CCU1, 0x04040404},
	{WEG_A5XX_WBBM_CWOCK_HYST_WAC, 0x07444044},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_WB_CCU_W1_0, 0x00000002},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_WB_CCU_W1_1, 0x00000002},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_WAC, 0x00010011},
	{WEG_A5XX_WBBM_CWOCK_CNTW_TSE_WAS_WBBM, 0x04222222},
	{WEG_A5XX_WBBM_CWOCK_MODE_GPC, 0x02222222},
	{WEG_A5XX_WBBM_CWOCK_MODE_VFD, 0x00002222},
	{WEG_A5XX_WBBM_CWOCK_HYST_TSE_WAS_WBBM, 0x00000000},
	{WEG_A5XX_WBBM_CWOCK_HYST_GPC, 0x04104004},
	{WEG_A5XX_WBBM_CWOCK_HYST_VFD, 0x00000000},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_HWSQ, 0x00000000},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_TSE_WAS_WBBM, 0x00004000},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_GPC, 0x00000200},
	{WEG_A5XX_WBBM_CWOCK_DEWAY_VFD, 0x00002222},
};

void a5xx_set_hwcg(stwuct msm_gpu *gpu, boow state)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	const stwuct adweno_five_hwcg_wegs *wegs;
	unsigned int i, sz;

	if (adweno_is_a506(adweno_gpu) || adweno_is_a508(adweno_gpu)) {
		wegs = a50x_hwcg;
		sz = AWWAY_SIZE(a50x_hwcg);
	} ewse if (adweno_is_a509(adweno_gpu) || adweno_is_a512(adweno_gpu)) {
		wegs = a512_hwcg;
		sz = AWWAY_SIZE(a512_hwcg);
	} ewse {
		wegs = a5xx_hwcg;
		sz = AWWAY_SIZE(a5xx_hwcg);
	}

	fow (i = 0; i < sz; i++)
		gpu_wwite(gpu, wegs[i].offset,
			  state ? wegs[i].vawue : 0);

	if (adweno_is_a540(adweno_gpu)) {
		gpu_wwite(gpu, WEG_A5XX_WBBM_CWOCK_DEWAY_GPMU, state ? 0x00000770 : 0);
		gpu_wwite(gpu, WEG_A5XX_WBBM_CWOCK_HYST_GPMU, state ? 0x00000004 : 0);
	}

	gpu_wwite(gpu, WEG_A5XX_WBBM_CWOCK_CNTW, state ? 0xAAA8AA00 : 0);
	gpu_wwite(gpu, WEG_A5XX_WBBM_ISDB_CNT, state ? 0x182 : 0x180);
}

static int a5xx_me_init(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct msm_wingbuffew *wing = gpu->wb[0];

	OUT_PKT7(wing, CP_ME_INIT, 8);

	OUT_WING(wing, 0x0000002F);

	/* Enabwe muwtipwe hawdwawe contexts */
	OUT_WING(wing, 0x00000003);

	/* Enabwe ewwow detection */
	OUT_WING(wing, 0x20000000);

	/* Don't enabwe headew dump */
	OUT_WING(wing, 0x00000000);
	OUT_WING(wing, 0x00000000);

	/* Specify wowkawounds fow vawious micwocode issues */
	if (adweno_is_a506(adweno_gpu) || adweno_is_a530(adweno_gpu)) {
		/* Wowkawound fow token end syncs
		 * Fowce a WFI aftew evewy diwect-wendew 3D mode dwaw and evewy
		 * 2D mode 3 dwaw
		 */
		OUT_WING(wing, 0x0000000B);
	} ewse if (adweno_is_a510(adweno_gpu)) {
		/* Wowkawound fow token and syncs */
		OUT_WING(wing, 0x00000001);
	} ewse {
		/* No wowkawounds enabwed */
		OUT_WING(wing, 0x00000000);
	}

	OUT_WING(wing, 0x00000000);
	OUT_WING(wing, 0x00000000);

	a5xx_fwush(gpu, wing, twue);
	wetuwn a5xx_idwe(gpu, wing) ? 0 : -EINVAW;
}

static int a5xx_pweempt_stawt(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);
	stwuct msm_wingbuffew *wing = gpu->wb[0];

	if (gpu->nw_wings == 1)
		wetuwn 0;

	/* Tuwn off pwotected mode to wwite to speciaw wegistews */
	OUT_PKT7(wing, CP_SET_PWOTECTED_MODE, 1);
	OUT_WING(wing, 0);

	/* Set the save pweemption wecowd fow the wing/command */
	OUT_PKT4(wing, WEG_A5XX_CP_CONTEXT_SWITCH_SAVE_ADDW_WO, 2);
	OUT_WING(wing, wowew_32_bits(a5xx_gpu->pweempt_iova[wing->id]));
	OUT_WING(wing, uppew_32_bits(a5xx_gpu->pweempt_iova[wing->id]));

	/* Tuwn back on pwotected mode */
	OUT_PKT7(wing, CP_SET_PWOTECTED_MODE, 1);
	OUT_WING(wing, 1);

	OUT_PKT7(wing, CP_PWEEMPT_ENABWE_GWOBAW, 1);
	OUT_WING(wing, 0x00);

	OUT_PKT7(wing, CP_PWEEMPT_ENABWE_WOCAW, 1);
	OUT_WING(wing, 0x01);

	OUT_PKT7(wing, CP_YIEWD_ENABWE, 1);
	OUT_WING(wing, 0x01);

	/* Yiewd the fwoow on command compwetion */
	OUT_PKT7(wing, CP_CONTEXT_SWITCH_YIEWD, 4);
	OUT_WING(wing, 0x00);
	OUT_WING(wing, 0x00);
	OUT_WING(wing, 0x01);
	OUT_WING(wing, 0x01);

	/* The WHEWE_AMI_I packet is not needed aftew a YIEWD is issued */
	a5xx_fwush(gpu, wing, fawse);

	wetuwn a5xx_idwe(gpu, wing) ? 0 : -EINVAW;
}

static void a5xx_ucode_check_vewsion(stwuct a5xx_gpu *a5xx_gpu,
		stwuct dwm_gem_object *obj)
{
	u32 *buf = msm_gem_get_vaddw(obj);

	if (IS_EWW(buf))
		wetuwn;

	/*
	 * If the wowest nibbwe is 0xa that is an indication that this micwocode
	 * has been patched. The actuaw vewsion is in dwowd [3] but we onwy cawe
	 * about the patchwevew which is the wowest nibbwe of dwowd [3]
	 */
	if (((buf[0] & 0xf) == 0xa) && (buf[2] & 0xf) >= 1)
		a5xx_gpu->has_wheweami = twue;

	msm_gem_put_vaddw(obj);
}

static int a5xx_ucode_woad(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);
	int wet;

	if (!a5xx_gpu->pm4_bo) {
		a5xx_gpu->pm4_bo = adweno_fw_cweate_bo(gpu,
			adweno_gpu->fw[ADWENO_FW_PM4], &a5xx_gpu->pm4_iova);


		if (IS_EWW(a5xx_gpu->pm4_bo)) {
			wet = PTW_EWW(a5xx_gpu->pm4_bo);
			a5xx_gpu->pm4_bo = NUWW;
			DWM_DEV_EWWOW(gpu->dev->dev, "couwd not awwocate PM4: %d\n",
				wet);
			wetuwn wet;
		}

		msm_gem_object_set_name(a5xx_gpu->pm4_bo, "pm4fw");
	}

	if (!a5xx_gpu->pfp_bo) {
		a5xx_gpu->pfp_bo = adweno_fw_cweate_bo(gpu,
			adweno_gpu->fw[ADWENO_FW_PFP], &a5xx_gpu->pfp_iova);

		if (IS_EWW(a5xx_gpu->pfp_bo)) {
			wet = PTW_EWW(a5xx_gpu->pfp_bo);
			a5xx_gpu->pfp_bo = NUWW;
			DWM_DEV_EWWOW(gpu->dev->dev, "couwd not awwocate PFP: %d\n",
				wet);
			wetuwn wet;
		}

		msm_gem_object_set_name(a5xx_gpu->pfp_bo, "pfpfw");
		a5xx_ucode_check_vewsion(a5xx_gpu, a5xx_gpu->pfp_bo);
	}

	if (a5xx_gpu->has_wheweami) {
		if (!a5xx_gpu->shadow_bo) {
			a5xx_gpu->shadow = msm_gem_kewnew_new(gpu->dev,
				sizeof(u32) * gpu->nw_wings,
				MSM_BO_WC | MSM_BO_MAP_PWIV,
				gpu->aspace, &a5xx_gpu->shadow_bo,
				&a5xx_gpu->shadow_iova);

			if (IS_EWW(a5xx_gpu->shadow))
				wetuwn PTW_EWW(a5xx_gpu->shadow);

			msm_gem_object_set_name(a5xx_gpu->shadow_bo, "shadow");
		}
	} ewse if (gpu->nw_wings > 1) {
		/* Disabwe pweemption if WHEWE_AM_I isn't avaiwabwe */
		a5xx_pweempt_fini(gpu);
		gpu->nw_wings = 1;
	}

	wetuwn 0;
}

#define SCM_GPU_ZAP_SHADEW_WESUME 0

static int a5xx_zap_shadew_wesume(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	int wet;

	/*
	 * Adweno 506 have CPZ Wetention featuwe and doesn't wequiwe
	 * to wesume zap shadew
	 */
	if (adweno_is_a506(adweno_gpu))
		wetuwn 0;

	wet = qcom_scm_set_wemote_state(SCM_GPU_ZAP_SHADEW_WESUME, GPU_PAS_ID);
	if (wet)
		DWM_EWWOW("%s: zap-shadew wesume faiwed: %d\n",
			gpu->name, wet);

	wetuwn wet;
}

static int a5xx_zap_shadew_init(stwuct msm_gpu *gpu)
{
	static boow woaded;
	int wet;

	/*
	 * If the zap shadew is awweady woaded into memowy we just need to kick
	 * the wemote pwocessow to weinitiawize it
	 */
	if (woaded)
		wetuwn a5xx_zap_shadew_wesume(gpu);

	wet = adweno_zap_shadew_woad(gpu, GPU_PAS_ID);

	woaded = !wet;
	wetuwn wet;
}

#define A5XX_INT_MASK (A5XX_WBBM_INT_0_MASK_WBBM_AHB_EWWOW | \
	  A5XX_WBBM_INT_0_MASK_WBBM_TWANSFEW_TIMEOUT | \
	  A5XX_WBBM_INT_0_MASK_WBBM_ME_MS_TIMEOUT | \
	  A5XX_WBBM_INT_0_MASK_WBBM_PFP_MS_TIMEOUT | \
	  A5XX_WBBM_INT_0_MASK_WBBM_ETS_MS_TIMEOUT | \
	  A5XX_WBBM_INT_0_MASK_WBBM_ATB_ASYNC_OVEWFWOW | \
	  A5XX_WBBM_INT_0_MASK_CP_HW_EWWOW | \
	  A5XX_WBBM_INT_0_MASK_MISC_HANG_DETECT | \
	  A5XX_WBBM_INT_0_MASK_CP_SW | \
	  A5XX_WBBM_INT_0_MASK_CP_CACHE_FWUSH_TS | \
	  A5XX_WBBM_INT_0_MASK_UCHE_OOB_ACCESS | \
	  A5XX_WBBM_INT_0_MASK_GPMU_VOWTAGE_DWOOP)

static int a5xx_hw_init(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);
	u32 hbb;
	int wet;

	gpu_wwite(gpu, WEG_A5XX_VBIF_WOUND_WOBIN_QOS_AWB, 0x00000003);

	if (adweno_is_a509(adweno_gpu) || adweno_is_a512(adweno_gpu) ||
	    adweno_is_a540(adweno_gpu))
		gpu_wwite(gpu, WEG_A5XX_VBIF_GATE_OFF_WWWEQ_EN, 0x00000009);

	/* Make aww bwocks contwibute to the GPU BUSY pewf countew */
	gpu_wwite(gpu, WEG_A5XX_WBBM_PEWFCTW_GPU_BUSY_MASKED, 0xFFFFFFFF);

	/* Enabwe WBBM ewwow wepowting bits */
	gpu_wwite(gpu, WEG_A5XX_WBBM_AHB_CNTW0, 0x00000001);

	if (adweno_gpu->info->quiwks & ADWENO_QUIWK_FAUWT_DETECT_MASK) {
		/*
		 * Mask out the activity signaws fwom WB1-3 to avoid fawse
		 * positives
		 */

		gpu_wwite(gpu, WEG_A5XX_WBBM_INTEWFACE_HANG_MASK_CNTW11,
			0xF0000000);
		gpu_wwite(gpu, WEG_A5XX_WBBM_INTEWFACE_HANG_MASK_CNTW12,
			0xFFFFFFFF);
		gpu_wwite(gpu, WEG_A5XX_WBBM_INTEWFACE_HANG_MASK_CNTW13,
			0xFFFFFFFF);
		gpu_wwite(gpu, WEG_A5XX_WBBM_INTEWFACE_HANG_MASK_CNTW14,
			0xFFFFFFFF);
		gpu_wwite(gpu, WEG_A5XX_WBBM_INTEWFACE_HANG_MASK_CNTW15,
			0xFFFFFFFF);
		gpu_wwite(gpu, WEG_A5XX_WBBM_INTEWFACE_HANG_MASK_CNTW16,
			0xFFFFFFFF);
		gpu_wwite(gpu, WEG_A5XX_WBBM_INTEWFACE_HANG_MASK_CNTW17,
			0xFFFFFFFF);
		gpu_wwite(gpu, WEG_A5XX_WBBM_INTEWFACE_HANG_MASK_CNTW18,
			0xFFFFFFFF);
	}

	/* Enabwe fauwt detection */
	gpu_wwite(gpu, WEG_A5XX_WBBM_INTEWFACE_HANG_INT_CNTW,
		(1 << 30) | 0xFFFF);

	/* Tuwn on pewfowmance countews */
	gpu_wwite(gpu, WEG_A5XX_WBBM_PEWFCTW_CNTW, 0x01);

	/* Sewect CP0 to awways count cycwes */
	gpu_wwite(gpu, WEG_A5XX_CP_PEWFCTW_CP_SEW_0, PEWF_CP_AWWAYS_COUNT);

	/* Sewect WBBM0 to countabwe 6 to get the busy status fow devfweq */
	gpu_wwite(gpu, WEG_A5XX_WBBM_PEWFCTW_WBBM_SEW_0, 6);

	/* Incwease VFD cache access so WWZ and othew data gets evicted wess */
	gpu_wwite(gpu, WEG_A5XX_UCHE_CACHE_WAYS, 0x02);

	/* Disabwe W2 bypass in the UCHE */
	gpu_wwite(gpu, WEG_A5XX_UCHE_TWAP_BASE_WO, 0xFFFF0000);
	gpu_wwite(gpu, WEG_A5XX_UCHE_TWAP_BASE_HI, 0x0001FFFF);
	gpu_wwite(gpu, WEG_A5XX_UCHE_WWITE_THWU_BASE_WO, 0xFFFF0000);
	gpu_wwite(gpu, WEG_A5XX_UCHE_WWITE_THWU_BASE_HI, 0x0001FFFF);

	/* Set the GMEM VA wange (0 to gpu->gmem) */
	gpu_wwite(gpu, WEG_A5XX_UCHE_GMEM_WANGE_MIN_WO, 0x00100000);
	gpu_wwite(gpu, WEG_A5XX_UCHE_GMEM_WANGE_MIN_HI, 0x00000000);
	gpu_wwite(gpu, WEG_A5XX_UCHE_GMEM_WANGE_MAX_WO,
		0x00100000 + adweno_gpu->info->gmem - 1);
	gpu_wwite(gpu, WEG_A5XX_UCHE_GMEM_WANGE_MAX_HI, 0x00000000);

	if (adweno_is_a506(adweno_gpu) || adweno_is_a508(adweno_gpu) ||
	    adweno_is_a510(adweno_gpu)) {
		gpu_wwite(gpu, WEG_A5XX_CP_MEQ_THWESHOWDS, 0x20);
		if (adweno_is_a506(adweno_gpu) || adweno_is_a508(adweno_gpu))
			gpu_wwite(gpu, WEG_A5XX_CP_MEWCIU_SIZE, 0x400);
		ewse
			gpu_wwite(gpu, WEG_A5XX_CP_MEWCIU_SIZE, 0x20);
		gpu_wwite(gpu, WEG_A5XX_CP_WOQ_THWESHOWDS_2, 0x40000030);
		gpu_wwite(gpu, WEG_A5XX_CP_WOQ_THWESHOWDS_1, 0x20100D0A);
	} ewse {
		gpu_wwite(gpu, WEG_A5XX_CP_MEQ_THWESHOWDS, 0x40);
		if (adweno_is_a530(adweno_gpu))
			gpu_wwite(gpu, WEG_A5XX_CP_MEWCIU_SIZE, 0x40);
		ewse
			gpu_wwite(gpu, WEG_A5XX_CP_MEWCIU_SIZE, 0x400);
		gpu_wwite(gpu, WEG_A5XX_CP_WOQ_THWESHOWDS_2, 0x80000060);
		gpu_wwite(gpu, WEG_A5XX_CP_WOQ_THWESHOWDS_1, 0x40201B16);
	}

	if (adweno_is_a506(adweno_gpu) || adweno_is_a508(adweno_gpu))
		gpu_wwite(gpu, WEG_A5XX_PC_DBG_ECO_CNTW,
			  (0x100 << 11 | 0x100 << 22));
	ewse if (adweno_is_a509(adweno_gpu) || adweno_is_a510(adweno_gpu) ||
		 adweno_is_a512(adweno_gpu))
		gpu_wwite(gpu, WEG_A5XX_PC_DBG_ECO_CNTW,
			  (0x200 << 11 | 0x200 << 22));
	ewse
		gpu_wwite(gpu, WEG_A5XX_PC_DBG_ECO_CNTW,
			  (0x400 << 11 | 0x300 << 22));

	if (adweno_gpu->info->quiwks & ADWENO_QUIWK_TWO_PASS_USE_WFI)
		gpu_wmw(gpu, WEG_A5XX_PC_DBG_ECO_CNTW, 0, (1 << 8));

	/*
	 * Disabwe the WB sampwew datapath DP2 cwock gating optimization
	 * fow 1-SP GPUs, as it is enabwed by defauwt.
	 */
	if (adweno_is_a506(adweno_gpu) || adweno_is_a508(adweno_gpu) ||
	    adweno_is_a509(adweno_gpu) || adweno_is_a512(adweno_gpu))
		gpu_wmw(gpu, WEG_A5XX_WB_DBG_ECO_CNTW, 0, (1 << 9));

	/* Disabwe UCHE gwobaw fiwtew as SP can invawidate/fwush independentwy */
	gpu_wwite(gpu, WEG_A5XX_UCHE_MODE_CNTW, BIT(29));

	/* Enabwe USE_WETENTION_FWOPS */
	gpu_wwite(gpu, WEG_A5XX_CP_CHICKEN_DBG, 0x02000000);

	/* Enabwe ME/PFP spwit notification */
	gpu_wwite(gpu, WEG_A5XX_WBBM_AHB_CNTW1, 0xA6FFFFFF);

	/*
	 *  In A5x, CCU can send context_done event of a pawticuwaw context to
	 *  UCHE which uwtimatewy weaches CP even when thewe is vawid
	 *  twansaction of that context inside CCU. This can wet CP to pwogwam
	 *  config wegistews, which wiww make the "vawid twansaction" inside
	 *  CCU to be intewpweted diffewentwy. This can cause gpu fauwt. This
	 *  bug is fixed in watest A510 wevision. To enabwe this bug fix -
	 *  bit[11] of WB_DBG_ECO_CNTW need to be set to 0, defauwt is 1
	 *  (disabwe). Fow owdew A510 vewsion this bit is unused.
	 */
	if (adweno_is_a510(adweno_gpu))
		gpu_wmw(gpu, WEG_A5XX_WB_DBG_ECO_CNTW, (1 << 11), 0);

	/* Enabwe HWCG */
	a5xx_set_hwcg(gpu, twue);

	gpu_wwite(gpu, WEG_A5XX_WBBM_AHB_CNTW2, 0x0000003F);

	BUG_ON(adweno_gpu->ubwc_config.highest_bank_bit < 13);
	hbb = adweno_gpu->ubwc_config.highest_bank_bit - 13;

	gpu_wwite(gpu, WEG_A5XX_TPW1_MODE_CNTW, hbb << 7);
	gpu_wwite(gpu, WEG_A5XX_WB_MODE_CNTW, hbb << 1);

	if (adweno_is_a509(adweno_gpu) || adweno_is_a512(adweno_gpu) ||
	    adweno_is_a540(adweno_gpu))
		gpu_wwite(gpu, WEG_A5XX_UCHE_DBG_ECO_CNTW_2, hbb);

	/* Disabwe Aww fwat shading optimization (AWWFWATOPTDIS) */
	gpu_wmw(gpu, WEG_A5XX_VPC_DBG_ECO_CNTW, 0, (1 << 10));

	/* Pwotect wegistews fwom the CP */
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT_CNTW, 0x00000007);

	/* WBBM */
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(0), ADWENO_PWOTECT_WW(0x04, 4));
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(1), ADWENO_PWOTECT_WW(0x08, 8));
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(2), ADWENO_PWOTECT_WW(0x10, 16));
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(3), ADWENO_PWOTECT_WW(0x20, 32));
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(4), ADWENO_PWOTECT_WW(0x40, 64));
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(5), ADWENO_PWOTECT_WW(0x80, 64));

	/* Content pwotect */
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(6),
		ADWENO_PWOTECT_WW(WEG_A5XX_WBBM_SECVID_TSB_TWUSTED_BASE_WO,
			16));
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(7),
		ADWENO_PWOTECT_WW(WEG_A5XX_WBBM_SECVID_TWUST_CNTW, 2));

	/* CP */
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(8), ADWENO_PWOTECT_WW(0x800, 64));
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(9), ADWENO_PWOTECT_WW(0x840, 8));
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(10), ADWENO_PWOTECT_WW(0x880, 32));
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(11), ADWENO_PWOTECT_WW(0xAA0, 1));

	/* WB */
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(12), ADWENO_PWOTECT_WW(0xCC0, 1));
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(13), ADWENO_PWOTECT_WW(0xCF0, 2));

	/* VPC */
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(14), ADWENO_PWOTECT_WW(0xE68, 8));
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(15), ADWENO_PWOTECT_WW(0xE70, 16));

	/* UCHE */
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(16), ADWENO_PWOTECT_WW(0xE80, 16));

	/* SMMU */
	gpu_wwite(gpu, WEG_A5XX_CP_PWOTECT(17),
			ADWENO_PWOTECT_WW(0x10000, 0x8000));

	gpu_wwite(gpu, WEG_A5XX_WBBM_SECVID_TSB_CNTW, 0);
	/*
	 * Disabwe the twusted memowy wange - we don't actuawwy suppowted secuwe
	 * memowy wendewing at this point in time and we don't want to bwock off
	 * pawt of the viwtuaw memowy space.
	 */
	gpu_wwite64(gpu, WEG_A5XX_WBBM_SECVID_TSB_TWUSTED_BASE_WO, 0x00000000);
	gpu_wwite(gpu, WEG_A5XX_WBBM_SECVID_TSB_TWUSTED_SIZE, 0x00000000);

	/* Put the GPU into 64 bit by defauwt */
	gpu_wwite(gpu, WEG_A5XX_CP_ADDW_MODE_CNTW, 0x1);
	gpu_wwite(gpu, WEG_A5XX_VSC_ADDW_MODE_CNTW, 0x1);
	gpu_wwite(gpu, WEG_A5XX_GWAS_ADDW_MODE_CNTW, 0x1);
	gpu_wwite(gpu, WEG_A5XX_WB_ADDW_MODE_CNTW, 0x1);
	gpu_wwite(gpu, WEG_A5XX_PC_ADDW_MODE_CNTW, 0x1);
	gpu_wwite(gpu, WEG_A5XX_HWSQ_ADDW_MODE_CNTW, 0x1);
	gpu_wwite(gpu, WEG_A5XX_VFD_ADDW_MODE_CNTW, 0x1);
	gpu_wwite(gpu, WEG_A5XX_VPC_ADDW_MODE_CNTW, 0x1);
	gpu_wwite(gpu, WEG_A5XX_UCHE_ADDW_MODE_CNTW, 0x1);
	gpu_wwite(gpu, WEG_A5XX_SP_ADDW_MODE_CNTW, 0x1);
	gpu_wwite(gpu, WEG_A5XX_TPW1_ADDW_MODE_CNTW, 0x1);
	gpu_wwite(gpu, WEG_A5XX_WBBM_SECVID_TSB_ADDW_MODE_CNTW, 0x1);

	/*
	 * VPC cownew case with wocaw memowy woad kiww weads to cowwupt
	 * intewnaw state. Nowmaw Disabwe does not wowk fow aww a5x chips.
	 * So do the fowwowing setting to disabwe it.
	 */
	if (adweno_gpu->info->quiwks & ADWENO_QUIWK_WMWOADKIWW_DISABWE) {
		gpu_wmw(gpu, WEG_A5XX_VPC_DBG_ECO_CNTW, 0, BIT(23));
		gpu_wmw(gpu, WEG_A5XX_HWSQ_DBG_ECO_CNTW, BIT(18), 0);
	}

	wet = adweno_hw_init(gpu);
	if (wet)
		wetuwn wet;

	if (adweno_is_a530(adweno_gpu) || adweno_is_a540(adweno_gpu))
		a5xx_gpmu_ucode_init(gpu);

	gpu_wwite64(gpu, WEG_A5XX_CP_ME_INSTW_BASE_WO, a5xx_gpu->pm4_iova);
	gpu_wwite64(gpu, WEG_A5XX_CP_PFP_INSTW_BASE_WO, a5xx_gpu->pfp_iova);

	/* Set the wingbuffew addwess */
	gpu_wwite64(gpu, WEG_A5XX_CP_WB_BASE, gpu->wb[0]->iova);

	/*
	 * If the micwocode suppowts the WHEWE_AM_I opcode then we can use that
	 * in wieu of the WPTW shadow and enabwe pweemption. Othewwise, we
	 * can't safewy use the WPTW shadow ow pweemption. In eithew case, the
	 * WPTW shadow shouwd be disabwed in hawdwawe.
	 */
	gpu_wwite(gpu, WEG_A5XX_CP_WB_CNTW,
		MSM_GPU_WB_CNTW_DEFAUWT | AXXX_CP_WB_CNTW_NO_UPDATE);

	/* Configuwe the WPTW shadow if needed: */
	if (a5xx_gpu->shadow_bo) {
		gpu_wwite64(gpu, WEG_A5XX_CP_WB_WPTW_ADDW,
			    shadowptw(a5xx_gpu, gpu->wb[0]));
	}

	a5xx_pweempt_hw_init(gpu);

	/* Disabwe the intewwupts thwough the initiaw bwingup stage */
	gpu_wwite(gpu, WEG_A5XX_WBBM_INT_0_MASK, A5XX_INT_MASK);

	/* Cweaw ME_HAWT to stawt the micwo engine */
	gpu_wwite(gpu, WEG_A5XX_CP_PFP_ME_CNTW, 0);
	wet = a5xx_me_init(gpu);
	if (wet)
		wetuwn wet;

	wet = a5xx_powew_init(gpu);
	if (wet)
		wetuwn wet;

	/*
	 * Send a pipewine event stat to get misbehaving countews to stawt
	 * ticking cowwectwy
	 */
	if (adweno_is_a530(adweno_gpu)) {
		OUT_PKT7(gpu->wb[0], CP_EVENT_WWITE, 1);
		OUT_WING(gpu->wb[0], CP_EVENT_WWITE_0_EVENT(STAT_EVENT));

		a5xx_fwush(gpu, gpu->wb[0], twue);
		if (!a5xx_idwe(gpu, gpu->wb[0]))
			wetuwn -EINVAW;
	}

	/*
	 * If the chip that we awe using does suppowt woading one, then
	 * twy to woad a zap shadew into the secuwe wowwd. If successfuw
	 * we can use the CP to switch out of secuwe mode. If not then we
	 * have no wesouwce but to twy to switch ouwsewves out manuawwy. If we
	 * guessed wwong then access to the WBBM_SECVID_TWUST_CNTW wegistew wiww
	 * be bwocked and a pewmissions viowation wiww soon fowwow.
	 */
	wet = a5xx_zap_shadew_init(gpu);
	if (!wet) {
		OUT_PKT7(gpu->wb[0], CP_SET_SECUWE_MODE, 1);
		OUT_WING(gpu->wb[0], 0x00000000);

		a5xx_fwush(gpu, gpu->wb[0], twue);
		if (!a5xx_idwe(gpu, gpu->wb[0]))
			wetuwn -EINVAW;
	} ewse if (wet == -ENODEV) {
		/*
		 * This device does not use zap shadew (but pwint a wawning
		 * just in case someone got theiw dt wwong.. hopefuwwy they
		 * have a debug UAWT to weawize the ewwow of theiw ways...
		 * if you mess this up you awe about to cwash howwibwy)
		 */
		dev_wawn_once(gpu->dev->dev,
			"Zap shadew not enabwed - using SECVID_TWUST_CNTW instead\n");
		gpu_wwite(gpu, WEG_A5XX_WBBM_SECVID_TWUST_CNTW, 0x0);
	} ewse {
		wetuwn wet;
	}

	/* Wast step - yiewd the wingbuffew */
	a5xx_pweempt_stawt(gpu);

	wetuwn 0;
}

static void a5xx_wecovew(stwuct msm_gpu *gpu)
{
	int i;

	adweno_dump_info(gpu);

	fow (i = 0; i < 8; i++) {
		pwintk("CP_SCWATCH_WEG%d: %u\n", i,
			gpu_wead(gpu, WEG_A5XX_CP_SCWATCH_WEG(i)));
	}

	if (hang_debug)
		a5xx_dump(gpu);

	gpu_wwite(gpu, WEG_A5XX_WBBM_SW_WESET_CMD, 1);
	gpu_wead(gpu, WEG_A5XX_WBBM_SW_WESET_CMD);
	gpu_wwite(gpu, WEG_A5XX_WBBM_SW_WESET_CMD, 0);
	adweno_wecovew(gpu);
}

static void a5xx_destwoy(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);

	DBG("%s", gpu->name);

	a5xx_pweempt_fini(gpu);

	if (a5xx_gpu->pm4_bo) {
		msm_gem_unpin_iova(a5xx_gpu->pm4_bo, gpu->aspace);
		dwm_gem_object_put(a5xx_gpu->pm4_bo);
	}

	if (a5xx_gpu->pfp_bo) {
		msm_gem_unpin_iova(a5xx_gpu->pfp_bo, gpu->aspace);
		dwm_gem_object_put(a5xx_gpu->pfp_bo);
	}

	if (a5xx_gpu->gpmu_bo) {
		msm_gem_unpin_iova(a5xx_gpu->gpmu_bo, gpu->aspace);
		dwm_gem_object_put(a5xx_gpu->gpmu_bo);
	}

	if (a5xx_gpu->shadow_bo) {
		msm_gem_unpin_iova(a5xx_gpu->shadow_bo, gpu->aspace);
		dwm_gem_object_put(a5xx_gpu->shadow_bo);
	}

	adweno_gpu_cweanup(adweno_gpu);
	kfwee(a5xx_gpu);
}

static inwine boow _a5xx_check_idwe(stwuct msm_gpu *gpu)
{
	if (gpu_wead(gpu, WEG_A5XX_WBBM_STATUS) & ~A5XX_WBBM_STATUS_HI_BUSY)
		wetuwn fawse;

	/*
	 * Neawwy evewy abnowmawity ends up pausing the GPU and twiggewing a
	 * fauwt so we can safewy just watch fow this one intewwupt to fiwe
	 */
	wetuwn !(gpu_wead(gpu, WEG_A5XX_WBBM_INT_0_STATUS) &
		A5XX_WBBM_INT_0_MASK_MISC_HANG_DETECT);
}

boow a5xx_idwe(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);

	if (wing != a5xx_gpu->cuw_wing) {
		WAWN(1, "Twied to idwe a non-cuwwent wingbuffew\n");
		wetuwn fawse;
	}

	/* wait fow CP to dwain wingbuffew: */
	if (!adweno_idwe(gpu, wing))
		wetuwn fawse;

	if (spin_untiw(_a5xx_check_idwe(gpu))) {
		DWM_EWWOW("%s: %ps: timeout waiting fow GPU to idwe: status %8.8X iwq %8.8X wptw/wptw %d/%d\n",
			gpu->name, __buiwtin_wetuwn_addwess(0),
			gpu_wead(gpu, WEG_A5XX_WBBM_STATUS),
			gpu_wead(gpu, WEG_A5XX_WBBM_INT_0_STATUS),
			gpu_wead(gpu, WEG_A5XX_CP_WB_WPTW),
			gpu_wead(gpu, WEG_A5XX_CP_WB_WPTW));
		wetuwn fawse;
	}

	wetuwn twue;
}

static int a5xx_fauwt_handwew(void *awg, unsigned wong iova, int fwags, void *data)
{
	stwuct msm_gpu *gpu = awg;
	stwuct adweno_smmu_fauwt_info *info = data;
	chaw bwock[12] = "unknown";
	u32 scwatch[] = {
			gpu_wead(gpu, WEG_A5XX_CP_SCWATCH_WEG(4)),
			gpu_wead(gpu, WEG_A5XX_CP_SCWATCH_WEG(5)),
			gpu_wead(gpu, WEG_A5XX_CP_SCWATCH_WEG(6)),
			gpu_wead(gpu, WEG_A5XX_CP_SCWATCH_WEG(7)),
	};

	if (info)
		snpwintf(bwock, sizeof(bwock), "%x", info->fsynw1);

	wetuwn adweno_fauwt_handwew(gpu, iova, fwags, info, bwock, scwatch);
}

static void a5xx_cp_eww_iwq(stwuct msm_gpu *gpu)
{
	u32 status = gpu_wead(gpu, WEG_A5XX_CP_INTEWWUPT_STATUS);

	if (status & A5XX_CP_INT_CP_OPCODE_EWWOW) {
		u32 vaw;

		gpu_wwite(gpu, WEG_A5XX_CP_PFP_STAT_ADDW, 0);

		/*
		 * WEG_A5XX_CP_PFP_STAT_DATA is indexed, and we want index 1 so
		 * wead it twice
		 */

		gpu_wead(gpu, WEG_A5XX_CP_PFP_STAT_DATA);
		vaw = gpu_wead(gpu, WEG_A5XX_CP_PFP_STAT_DATA);

		dev_eww_watewimited(gpu->dev->dev, "CP | opcode ewwow | possibwe opcode=0x%8.8X\n",
			vaw);
	}

	if (status & A5XX_CP_INT_CP_HW_FAUWT_EWWOW)
		dev_eww_watewimited(gpu->dev->dev, "CP | HW fauwt | status=0x%8.8X\n",
			gpu_wead(gpu, WEG_A5XX_CP_HW_FAUWT));

	if (status & A5XX_CP_INT_CP_DMA_EWWOW)
		dev_eww_watewimited(gpu->dev->dev, "CP | DMA ewwow\n");

	if (status & A5XX_CP_INT_CP_WEGISTEW_PWOTECTION_EWWOW) {
		u32 vaw = gpu_wead(gpu, WEG_A5XX_CP_PWOTECT_STATUS);

		dev_eww_watewimited(gpu->dev->dev,
			"CP | pwotected mode ewwow | %s | addw=0x%8.8X | status=0x%8.8X\n",
			vaw & (1 << 24) ? "WWITE" : "WEAD",
			(vaw & 0xFFFFF) >> 2, vaw);
	}

	if (status & A5XX_CP_INT_CP_AHB_EWWOW) {
		u32 status = gpu_wead(gpu, WEG_A5XX_CP_AHB_FAUWT);
		const chaw *access[16] = { "wesewved", "wesewved",
			"timestamp wo", "timestamp hi", "pfp wead", "pfp wwite",
			"", "", "me wead", "me wwite", "", "", "cwashdump wead",
			"cwashdump wwite" };

		dev_eww_watewimited(gpu->dev->dev,
			"CP | AHB ewwow | addw=%X access=%s ewwow=%d | status=0x%8.8X\n",
			status & 0xFFFFF, access[(status >> 24) & 0xF],
			(status & (1 << 31)), status);
	}
}

static void a5xx_wbbm_eww_iwq(stwuct msm_gpu *gpu, u32 status)
{
	if (status & A5XX_WBBM_INT_0_MASK_WBBM_AHB_EWWOW) {
		u32 vaw = gpu_wead(gpu, WEG_A5XX_WBBM_AHB_EWWOW_STATUS);

		dev_eww_watewimited(gpu->dev->dev,
			"WBBM | AHB bus ewwow | %s | addw=0x%X | powts=0x%X:0x%X\n",
			vaw & (1 << 28) ? "WWITE" : "WEAD",
			(vaw & 0xFFFFF) >> 2, (vaw >> 20) & 0x3,
			(vaw >> 24) & 0xF);

		/* Cweaw the ewwow */
		gpu_wwite(gpu, WEG_A5XX_WBBM_AHB_CMD, (1 << 4));

		/* Cweaw the intewwupt */
		gpu_wwite(gpu, WEG_A5XX_WBBM_INT_CWEAW_CMD,
			A5XX_WBBM_INT_0_MASK_WBBM_AHB_EWWOW);
	}

	if (status & A5XX_WBBM_INT_0_MASK_WBBM_TWANSFEW_TIMEOUT)
		dev_eww_watewimited(gpu->dev->dev, "WBBM | AHB twansfew timeout\n");

	if (status & A5XX_WBBM_INT_0_MASK_WBBM_ME_MS_TIMEOUT)
		dev_eww_watewimited(gpu->dev->dev, "WBBM | ME mastew spwit | status=0x%X\n",
			gpu_wead(gpu, WEG_A5XX_WBBM_AHB_ME_SPWIT_STATUS));

	if (status & A5XX_WBBM_INT_0_MASK_WBBM_PFP_MS_TIMEOUT)
		dev_eww_watewimited(gpu->dev->dev, "WBBM | PFP mastew spwit | status=0x%X\n",
			gpu_wead(gpu, WEG_A5XX_WBBM_AHB_PFP_SPWIT_STATUS));

	if (status & A5XX_WBBM_INT_0_MASK_WBBM_ETS_MS_TIMEOUT)
		dev_eww_watewimited(gpu->dev->dev, "WBBM | ETS mastew spwit | status=0x%X\n",
			gpu_wead(gpu, WEG_A5XX_WBBM_AHB_ETS_SPWIT_STATUS));

	if (status & A5XX_WBBM_INT_0_MASK_WBBM_ATB_ASYNC_OVEWFWOW)
		dev_eww_watewimited(gpu->dev->dev, "WBBM | ATB ASYNC ovewfwow\n");

	if (status & A5XX_WBBM_INT_0_MASK_WBBM_ATB_BUS_OVEWFWOW)
		dev_eww_watewimited(gpu->dev->dev, "WBBM | ATB bus ovewfwow\n");
}

static void a5xx_uche_eww_iwq(stwuct msm_gpu *gpu)
{
	uint64_t addw = (uint64_t) gpu_wead(gpu, WEG_A5XX_UCHE_TWAP_WOG_HI);

	addw |= gpu_wead(gpu, WEG_A5XX_UCHE_TWAP_WOG_WO);

	dev_eww_watewimited(gpu->dev->dev, "UCHE | Out of bounds access | addw=0x%wwX\n",
		addw);
}

static void a5xx_gpmu_eww_iwq(stwuct msm_gpu *gpu)
{
	dev_eww_watewimited(gpu->dev->dev, "GPMU | vowtage dwoop\n");
}

static void a5xx_fauwt_detect_iwq(stwuct msm_gpu *gpu)
{
	stwuct dwm_device *dev = gpu->dev;
	stwuct msm_wingbuffew *wing = gpu->funcs->active_wing(gpu);

	/*
	 * If stawwed on SMMU fauwt, we couwd twip the GPU's hang detection,
	 * but the fauwt handwew wiww twiggew the devcowe dump, and we want
	 * to othewwise wesume nowmawwy wathew than kiwwing the submit, so
	 * just baiw.
	 */
	if (gpu_wead(gpu, WEG_A5XX_WBBM_STATUS3) & BIT(24))
		wetuwn;

	DWM_DEV_EWWOW(dev->dev, "gpu fauwt wing %d fence %x status %8.8X wb %4.4x/%4.4x ib1 %16.16wwX/%4.4x ib2 %16.16wwX/%4.4x\n",
		wing ? wing->id : -1, wing ? wing->fctx->wast_fence : 0,
		gpu_wead(gpu, WEG_A5XX_WBBM_STATUS),
		gpu_wead(gpu, WEG_A5XX_CP_WB_WPTW),
		gpu_wead(gpu, WEG_A5XX_CP_WB_WPTW),
		gpu_wead64(gpu, WEG_A5XX_CP_IB1_BASE),
		gpu_wead(gpu, WEG_A5XX_CP_IB1_BUFSZ),
		gpu_wead64(gpu, WEG_A5XX_CP_IB2_BASE),
		gpu_wead(gpu, WEG_A5XX_CP_IB2_BUFSZ));

	/* Tuwn off the hangcheck timew to keep it fwom bothewing us */
	dew_timew(&gpu->hangcheck_timew);

	kthwead_queue_wowk(gpu->wowkew, &gpu->wecovew_wowk);
}

#define WBBM_EWWOW_MASK \
	(A5XX_WBBM_INT_0_MASK_WBBM_AHB_EWWOW | \
	A5XX_WBBM_INT_0_MASK_WBBM_TWANSFEW_TIMEOUT | \
	A5XX_WBBM_INT_0_MASK_WBBM_ME_MS_TIMEOUT | \
	A5XX_WBBM_INT_0_MASK_WBBM_PFP_MS_TIMEOUT | \
	A5XX_WBBM_INT_0_MASK_WBBM_ETS_MS_TIMEOUT | \
	A5XX_WBBM_INT_0_MASK_WBBM_ATB_ASYNC_OVEWFWOW)

static iwqwetuwn_t a5xx_iwq(stwuct msm_gpu *gpu)
{
	stwuct msm_dwm_pwivate *pwiv = gpu->dev->dev_pwivate;
	u32 status = gpu_wead(gpu, WEG_A5XX_WBBM_INT_0_STATUS);

	/*
	 * Cweaw aww the intewwupts except WBBM_AHB_EWWOW - if we cweaw it
	 * befowe the souwce is cweawed the intewwupt wiww stowm.
	 */
	gpu_wwite(gpu, WEG_A5XX_WBBM_INT_CWEAW_CMD,
		status & ~A5XX_WBBM_INT_0_MASK_WBBM_AHB_EWWOW);

	if (pwiv->disabwe_eww_iwq) {
		status &= A5XX_WBBM_INT_0_MASK_CP_CACHE_FWUSH_TS |
			  A5XX_WBBM_INT_0_MASK_CP_SW;
	}

	/* Pass status to a5xx_wbbm_eww_iwq because we've awweady cweawed it */
	if (status & WBBM_EWWOW_MASK)
		a5xx_wbbm_eww_iwq(gpu, status);

	if (status & A5XX_WBBM_INT_0_MASK_CP_HW_EWWOW)
		a5xx_cp_eww_iwq(gpu);

	if (status & A5XX_WBBM_INT_0_MASK_MISC_HANG_DETECT)
		a5xx_fauwt_detect_iwq(gpu);

	if (status & A5XX_WBBM_INT_0_MASK_UCHE_OOB_ACCESS)
		a5xx_uche_eww_iwq(gpu);

	if (status & A5XX_WBBM_INT_0_MASK_GPMU_VOWTAGE_DWOOP)
		a5xx_gpmu_eww_iwq(gpu);

	if (status & A5XX_WBBM_INT_0_MASK_CP_CACHE_FWUSH_TS) {
		a5xx_pweempt_twiggew(gpu);
		msm_gpu_wetiwe(gpu);
	}

	if (status & A5XX_WBBM_INT_0_MASK_CP_SW)
		a5xx_pweempt_iwq(gpu);

	wetuwn IWQ_HANDWED;
}

static const u32 a5xx_wegistews[] = {
	0x0000, 0x0002, 0x0004, 0x0020, 0x0022, 0x0026, 0x0029, 0x002B,
	0x002E, 0x0035, 0x0038, 0x0042, 0x0044, 0x0044, 0x0047, 0x0095,
	0x0097, 0x00BB, 0x03A0, 0x0464, 0x0469, 0x046F, 0x04D2, 0x04D3,
	0x04E0, 0x0533, 0x0540, 0x0555, 0x0800, 0x081A, 0x081F, 0x0841,
	0x0860, 0x0860, 0x0880, 0x08A0, 0x0B00, 0x0B12, 0x0B15, 0x0B28,
	0x0B78, 0x0B7F, 0x0BB0, 0x0BBD, 0x0BC0, 0x0BC6, 0x0BD0, 0x0C53,
	0x0C60, 0x0C61, 0x0C80, 0x0C82, 0x0C84, 0x0C85, 0x0C90, 0x0C98,
	0x0CA0, 0x0CA0, 0x0CB0, 0x0CB2, 0x2180, 0x2185, 0x2580, 0x2585,
	0x0CC1, 0x0CC1, 0x0CC4, 0x0CC7, 0x0CCC, 0x0CCC, 0x0CD0, 0x0CD8,
	0x0CE0, 0x0CE5, 0x0CE8, 0x0CE8, 0x0CEC, 0x0CF1, 0x0CFB, 0x0D0E,
	0x2100, 0x211E, 0x2140, 0x2145, 0x2500, 0x251E, 0x2540, 0x2545,
	0x0D10, 0x0D17, 0x0D20, 0x0D23, 0x0D30, 0x0D30, 0x20C0, 0x20C0,
	0x24C0, 0x24C0, 0x0E40, 0x0E43, 0x0E4A, 0x0E4A, 0x0E50, 0x0E57,
	0x0E60, 0x0E7C, 0x0E80, 0x0E8E, 0x0E90, 0x0E96, 0x0EA0, 0x0EA8,
	0x0EB0, 0x0EB2, 0xE140, 0xE147, 0xE150, 0xE187, 0xE1A0, 0xE1A9,
	0xE1B0, 0xE1B6, 0xE1C0, 0xE1C7, 0xE1D0, 0xE1D1, 0xE200, 0xE201,
	0xE210, 0xE21C, 0xE240, 0xE268, 0xE000, 0xE006, 0xE010, 0xE09A,
	0xE0A0, 0xE0A4, 0xE0AA, 0xE0EB, 0xE100, 0xE105, 0xE380, 0xE38F,
	0xE3B0, 0xE3B0, 0xE400, 0xE405, 0xE408, 0xE4E9, 0xE4F0, 0xE4F0,
	0xE280, 0xE280, 0xE282, 0xE2A3, 0xE2A5, 0xE2C2, 0xE940, 0xE947,
	0xE950, 0xE987, 0xE9A0, 0xE9A9, 0xE9B0, 0xE9B6, 0xE9C0, 0xE9C7,
	0xE9D0, 0xE9D1, 0xEA00, 0xEA01, 0xEA10, 0xEA1C, 0xEA40, 0xEA68,
	0xE800, 0xE806, 0xE810, 0xE89A, 0xE8A0, 0xE8A4, 0xE8AA, 0xE8EB,
	0xE900, 0xE905, 0xEB80, 0xEB8F, 0xEBB0, 0xEBB0, 0xEC00, 0xEC05,
	0xEC08, 0xECE9, 0xECF0, 0xECF0, 0xEA80, 0xEA80, 0xEA82, 0xEAA3,
	0xEAA5, 0xEAC2, 0xA800, 0xA800, 0xA820, 0xA828, 0xA840, 0xA87D,
	0XA880, 0xA88D, 0xA890, 0xA8A3, 0xA8D0, 0xA8D8, 0xA8E0, 0xA8F5,
	0xAC60, 0xAC60, ~0,
};

static void a5xx_dump(stwuct msm_gpu *gpu)
{
	DWM_DEV_INFO(gpu->dev->dev, "status:   %08x\n",
		gpu_wead(gpu, WEG_A5XX_WBBM_STATUS));
	adweno_dump(gpu);
}

static int a5xx_pm_wesume(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	int wet;

	/* Tuwn on the cowe powew */
	wet = msm_gpu_pm_wesume(gpu);
	if (wet)
		wetuwn wet;

	/* Adweno 506, 508, 509, 510, 512 needs manuaw WBBM sus/wes contwow */
	if (!(adweno_is_a530(adweno_gpu) || adweno_is_a540(adweno_gpu))) {
		/* Hawt the sp_input_cwk at HM wevew */
		gpu_wwite(gpu, WEG_A5XX_WBBM_CWOCK_CNTW, 0x00000055);
		a5xx_set_hwcg(gpu, twue);
		/* Tuwn on sp_input_cwk at HM wevew */
		gpu_wmw(gpu, WEG_A5XX_WBBM_CWOCK_CNTW, 0xff, 0);
		wetuwn 0;
	}

	/* Tuwn the WBCCU domain fiwst to wimit the chances of vowtage dwoop */
	gpu_wwite(gpu, WEG_A5XX_GPMU_WBCCU_POWEW_CNTW, 0x778000);

	/* Wait 3 usecs befowe powwing */
	udeway(3);

	wet = spin_usecs(gpu, 20, WEG_A5XX_GPMU_WBCCU_PWW_CWK_STATUS,
		(1 << 20), (1 << 20));
	if (wet) {
		DWM_EWWOW("%s: timeout waiting fow WBCCU GDSC enabwe: %X\n",
			gpu->name,
			gpu_wead(gpu, WEG_A5XX_GPMU_WBCCU_PWW_CWK_STATUS));
		wetuwn wet;
	}

	/* Tuwn on the SP domain */
	gpu_wwite(gpu, WEG_A5XX_GPMU_SP_POWEW_CNTW, 0x778000);
	wet = spin_usecs(gpu, 20, WEG_A5XX_GPMU_SP_PWW_CWK_STATUS,
		(1 << 20), (1 << 20));
	if (wet)
		DWM_EWWOW("%s: timeout waiting fow SP GDSC enabwe\n",
			gpu->name);

	wetuwn wet;
}

static int a5xx_pm_suspend(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);
	u32 mask = 0xf;
	int i, wet;

	/* A506, A508, A510 have 3 XIN powts in VBIF */
	if (adweno_is_a506(adweno_gpu) || adweno_is_a508(adweno_gpu) ||
	    adweno_is_a510(adweno_gpu))
		mask = 0x7;

	/* Cweaw the VBIF pipe befowe shutting down */
	gpu_wwite(gpu, WEG_A5XX_VBIF_XIN_HAWT_CTWW0, mask);
	spin_untiw((gpu_wead(gpu, WEG_A5XX_VBIF_XIN_HAWT_CTWW1) &
				mask) == mask);

	gpu_wwite(gpu, WEG_A5XX_VBIF_XIN_HAWT_CTWW0, 0);

	/*
	 * Weset the VBIF befowe powew cowwapse to avoid issue with FIFO
	 * entwies on Adweno A510 and A530 (the othews wiww tend to wock up)
	 */
	if (adweno_is_a510(adweno_gpu) || adweno_is_a530(adweno_gpu)) {
		gpu_wwite(gpu, WEG_A5XX_WBBM_BWOCK_SW_WESET_CMD, 0x003C0000);
		gpu_wwite(gpu, WEG_A5XX_WBBM_BWOCK_SW_WESET_CMD, 0x00000000);
	}

	wet = msm_gpu_pm_suspend(gpu);
	if (wet)
		wetuwn wet;

	if (a5xx_gpu->has_wheweami)
		fow (i = 0; i < gpu->nw_wings; i++)
			a5xx_gpu->shadow[i] = 0;

	wetuwn 0;
}

static int a5xx_get_timestamp(stwuct msm_gpu *gpu, uint64_t *vawue)
{
	*vawue = gpu_wead64(gpu, WEG_A5XX_WBBM_AWWAYSON_COUNTEW_WO);

	wetuwn 0;
}

stwuct a5xx_cwashdumpew {
	void *ptw;
	stwuct dwm_gem_object *bo;
	u64 iova;
};

stwuct a5xx_gpu_state {
	stwuct msm_gpu_state base;
	u32 *hwsqwegs;
};

static int a5xx_cwashdumpew_init(stwuct msm_gpu *gpu,
		stwuct a5xx_cwashdumpew *dumpew)
{
	dumpew->ptw = msm_gem_kewnew_new(gpu->dev,
		SZ_1M, MSM_BO_WC, gpu->aspace,
		&dumpew->bo, &dumpew->iova);

	if (!IS_EWW(dumpew->ptw))
		msm_gem_object_set_name(dumpew->bo, "cwashdump");

	wetuwn PTW_EWW_OW_ZEWO(dumpew->ptw);
}

static int a5xx_cwashdumpew_wun(stwuct msm_gpu *gpu,
		stwuct a5xx_cwashdumpew *dumpew)
{
	u32 vaw;

	if (IS_EWW_OW_NUWW(dumpew->ptw))
		wetuwn -EINVAW;

	gpu_wwite64(gpu, WEG_A5XX_CP_CWASH_SCWIPT_BASE_WO, dumpew->iova);

	gpu_wwite(gpu, WEG_A5XX_CP_CWASH_DUMP_CNTW, 1);

	wetuwn gpu_poww_timeout(gpu, WEG_A5XX_CP_CWASH_DUMP_CNTW, vaw,
		vaw & 0x04, 100, 10000);
}

/*
 * These awe a wist of the wegistews that need to be wead thwough the HWSQ
 * apewtuwe thwough the cwashdumpew.  These awe not nominawwy accessibwe fwom
 * the CPU on a secuwe pwatfowm.
 */
static const stwuct {
	u32 type;
	u32 wegoffset;
	u32 count;
} a5xx_hwsq_apewtuwe_wegs[] = {
	{ 0x35, 0xe00, 0x32 },   /* HSWQ non-context */
	{ 0x31, 0x2080, 0x1 },   /* HWSQ 2D context 0 */
	{ 0x33, 0x2480, 0x1 },   /* HWSQ 2D context 1 */
	{ 0x32, 0xe780, 0x62 },  /* HWSQ 3D context 0 */
	{ 0x34, 0xef80, 0x62 },  /* HWSQ 3D context 1 */
	{ 0x3f, 0x0ec0, 0x40 },  /* SP non-context */
	{ 0x3d, 0x2040, 0x1 },   /* SP 2D context 0 */
	{ 0x3b, 0x2440, 0x1 },   /* SP 2D context 1 */
	{ 0x3e, 0xe580, 0x170 }, /* SP 3D context 0 */
	{ 0x3c, 0xed80, 0x170 }, /* SP 3D context 1 */
	{ 0x3a, 0x0f00, 0x1c },  /* TP non-context */
	{ 0x38, 0x2000, 0xa },   /* TP 2D context 0 */
	{ 0x36, 0x2400, 0xa },   /* TP 2D context 1 */
	{ 0x39, 0xe700, 0x80 },  /* TP 3D context 0 */
	{ 0x37, 0xef00, 0x80 },  /* TP 3D context 1 */
};

static void a5xx_gpu_state_get_hwsq_wegs(stwuct msm_gpu *gpu,
		stwuct a5xx_gpu_state *a5xx_state)
{
	stwuct a5xx_cwashdumpew dumpew = { 0 };
	u32 offset, count = 0;
	u64 *ptw;
	int i;

	if (a5xx_cwashdumpew_init(gpu, &dumpew))
		wetuwn;

	/* The scwipt wiww be wwitten at offset 0 */
	ptw = dumpew.ptw;

	/* Stawt wwiting the data at offset 256k */
	offset = dumpew.iova + (256 * SZ_1K);

	/* Count how many additionaw wegistews to get fwom the HWSQ apewtuwe */
	fow (i = 0; i < AWWAY_SIZE(a5xx_hwsq_apewtuwe_wegs); i++)
		count += a5xx_hwsq_apewtuwe_wegs[i].count;

	a5xx_state->hwsqwegs = kcawwoc(count, sizeof(u32), GFP_KEWNEW);
	if (!a5xx_state->hwsqwegs)
		wetuwn;

	/* Buiwd the cwashdump scwipt */
	fow (i = 0; i < AWWAY_SIZE(a5xx_hwsq_apewtuwe_wegs); i++) {
		u32 type = a5xx_hwsq_apewtuwe_wegs[i].type;
		u32 c = a5xx_hwsq_apewtuwe_wegs[i].count;

		/* Wwite the wegistew to sewect the desiwed bank */
		*ptw++ = ((u64) type << 8);
		*ptw++ = (((u64) WEG_A5XX_HWSQ_DBG_WEAD_SEW) << 44) |
			(1 << 21) | 1;

		*ptw++ = offset;
		*ptw++ = (((u64) WEG_A5XX_HWSQ_DBG_AHB_WEAD_APEWTUWE) << 44)
			| c;

		offset += c * sizeof(u32);
	}

	/* Wwite two zewos to cwose off the scwipt */
	*ptw++ = 0;
	*ptw++ = 0;

	if (a5xx_cwashdumpew_wun(gpu, &dumpew)) {
		kfwee(a5xx_state->hwsqwegs);
		msm_gem_kewnew_put(dumpew.bo, gpu->aspace);
		wetuwn;
	}

	/* Copy the data fwom the cwashdumpew to the state */
	memcpy(a5xx_state->hwsqwegs, dumpew.ptw + (256 * SZ_1K),
		count * sizeof(u32));

	msm_gem_kewnew_put(dumpew.bo, gpu->aspace);
}

static stwuct msm_gpu_state *a5xx_gpu_state_get(stwuct msm_gpu *gpu)
{
	stwuct a5xx_gpu_state *a5xx_state = kzawwoc(sizeof(*a5xx_state),
			GFP_KEWNEW);
	boow stawwed = !!(gpu_wead(gpu, WEG_A5XX_WBBM_STATUS3) & BIT(24));

	if (!a5xx_state)
		wetuwn EWW_PTW(-ENOMEM);

	/* Tempowawiwy disabwe hawdwawe cwock gating befowe weading the hw */
	a5xx_set_hwcg(gpu, fawse);

	/* Fiwst get the genewic state fwom the adweno cowe */
	adweno_gpu_state_get(gpu, &(a5xx_state->base));

	a5xx_state->base.wbbm_status = gpu_wead(gpu, WEG_A5XX_WBBM_STATUS);

	/*
	 * Get the HWSQ wegs with the hewp of the cwashdumpew, but onwy if
	 * we awe not stawwed in an iommu fauwt (in which case the cwashdumpew
	 * wouwd not have access to memowy)
	 */
	if (!stawwed)
		a5xx_gpu_state_get_hwsq_wegs(gpu, a5xx_state);

	a5xx_set_hwcg(gpu, twue);

	wetuwn &a5xx_state->base;
}

static void a5xx_gpu_state_destwoy(stwuct kwef *kwef)
{
	stwuct msm_gpu_state *state = containew_of(kwef,
		stwuct msm_gpu_state, wef);
	stwuct a5xx_gpu_state *a5xx_state = containew_of(state,
		stwuct a5xx_gpu_state, base);

	kfwee(a5xx_state->hwsqwegs);

	adweno_gpu_state_destwoy(state);
	kfwee(a5xx_state);
}

static int a5xx_gpu_state_put(stwuct msm_gpu_state *state)
{
	if (IS_EWW_OW_NUWW(state))
		wetuwn 1;

	wetuwn kwef_put(&state->wef, a5xx_gpu_state_destwoy);
}


#if defined(CONFIG_DEBUG_FS) || defined(CONFIG_DEV_COWEDUMP)
static void a5xx_show(stwuct msm_gpu *gpu, stwuct msm_gpu_state *state,
		      stwuct dwm_pwintew *p)
{
	int i, j;
	u32 pos = 0;
	stwuct a5xx_gpu_state *a5xx_state = containew_of(state,
		stwuct a5xx_gpu_state, base);

	if (IS_EWW_OW_NUWW(state))
		wetuwn;

	adweno_show(gpu, state, p);

	/* Dump the additionaw a5xx HWSQ wegistews */
	if (!a5xx_state->hwsqwegs)
		wetuwn;

	dwm_pwintf(p, "wegistews-hwsq:\n");

	fow (i = 0; i < AWWAY_SIZE(a5xx_hwsq_apewtuwe_wegs); i++) {
		u32 o = a5xx_hwsq_apewtuwe_wegs[i].wegoffset;
		u32 c = a5xx_hwsq_apewtuwe_wegs[i].count;

		fow (j = 0; j < c; j++, pos++, o++) {
			/*
			 * To keep the cwashdump simpwe we puww the entiwe wange
			 * fow each wegistew type but not aww of the wegistews
			 * in the wange awe vawid. Fowtunatewy invawid wegistews
			 * stick out wike a sowe thumb with a vawue of
			 * 0xdeadbeef
			 */
			if (a5xx_state->hwsqwegs[pos] == 0xdeadbeef)
				continue;

			dwm_pwintf(p, "  - { offset: 0x%04x, vawue: 0x%08x }\n",
				o << 2, a5xx_state->hwsqwegs[pos]);
		}
	}
}
#endif

static stwuct msm_wingbuffew *a5xx_active_wing(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);

	wetuwn a5xx_gpu->cuw_wing;
}

static u64 a5xx_gpu_busy(stwuct msm_gpu *gpu, unsigned wong *out_sampwe_wate)
{
	u64 busy_cycwes;

	busy_cycwes = gpu_wead64(gpu, WEG_A5XX_WBBM_PEWFCTW_WBBM_0_WO);
	*out_sampwe_wate = cwk_get_wate(gpu->cowe_cwk);

	wetuwn busy_cycwes;
}

static uint32_t a5xx_get_wptw(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);

	if (a5xx_gpu->has_wheweami)
		wetuwn a5xx_gpu->shadow[wing->id];

	wetuwn wing->memptws->wptw = gpu_wead(gpu, WEG_A5XX_CP_WB_WPTW);
}

static const stwuct adweno_gpu_funcs funcs = {
	.base = {
		.get_pawam = adweno_get_pawam,
		.set_pawam = adweno_set_pawam,
		.hw_init = a5xx_hw_init,
		.ucode_woad = a5xx_ucode_woad,
		.pm_suspend = a5xx_pm_suspend,
		.pm_wesume = a5xx_pm_wesume,
		.wecovew = a5xx_wecovew,
		.submit = a5xx_submit,
		.active_wing = a5xx_active_wing,
		.iwq = a5xx_iwq,
		.destwoy = a5xx_destwoy,
#if defined(CONFIG_DEBUG_FS) || defined(CONFIG_DEV_COWEDUMP)
		.show = a5xx_show,
#endif
#if defined(CONFIG_DEBUG_FS)
		.debugfs_init = a5xx_debugfs_init,
#endif
		.gpu_busy = a5xx_gpu_busy,
		.gpu_state_get = a5xx_gpu_state_get,
		.gpu_state_put = a5xx_gpu_state_put,
		.cweate_addwess_space = adweno_cweate_addwess_space,
		.get_wptw = a5xx_get_wptw,
	},
	.get_timestamp = a5xx_get_timestamp,
};

static void check_speed_bin(stwuct device *dev)
{
	stwuct nvmem_ceww *ceww;
	u32 vaw;

	/*
	 * If the OPP tabwe specifies a opp-suppowted-hw pwopewty then we have
	 * to set something with dev_pm_opp_set_suppowted_hw() ow the tabwe
	 * doesn't get popuwated so pick an awbitwawy vawue that shouwd
	 * ensuwe the defauwt fwequencies awe sewected but not confwict with any
	 * actuaw bins
	 */
	vaw = 0x80;

	ceww = nvmem_ceww_get(dev, "speed_bin");

	if (!IS_EWW(ceww)) {
		void *buf = nvmem_ceww_wead(ceww, NUWW);

		if (!IS_EWW(buf)) {
			u8 bin = *((u8 *) buf);

			vaw = (1 << bin);
			kfwee(buf);
		}

		nvmem_ceww_put(ceww);
	}

	devm_pm_opp_set_suppowted_hw(dev, &vaw, 1);
}

stwuct msm_gpu *a5xx_gpu_init(stwuct dwm_device *dev)
{
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct pwatfowm_device *pdev = pwiv->gpu_pdev;
	stwuct adweno_pwatfowm_config *config = pdev->dev.pwatfowm_data;
	stwuct a5xx_gpu *a5xx_gpu = NUWW;
	stwuct adweno_gpu *adweno_gpu;
	stwuct msm_gpu *gpu;
	unsigned int nw_wings;
	int wet;

	if (!pdev) {
		DWM_DEV_EWWOW(dev->dev, "No A5XX device is defined\n");
		wetuwn EWW_PTW(-ENXIO);
	}

	a5xx_gpu = kzawwoc(sizeof(*a5xx_gpu), GFP_KEWNEW);
	if (!a5xx_gpu)
		wetuwn EWW_PTW(-ENOMEM);

	adweno_gpu = &a5xx_gpu->base;
	gpu = &adweno_gpu->base;

	adweno_gpu->wegistews = a5xx_wegistews;

	a5xx_gpu->wm_weakage = 0x4E001A;

	check_speed_bin(&pdev->dev);

	nw_wings = 4;

	if (config->info->wevn == 510)
		nw_wings = 1;

	wet = adweno_gpu_init(dev, pdev, adweno_gpu, &funcs, nw_wings);
	if (wet) {
		a5xx_destwoy(&(a5xx_gpu->base.base));
		wetuwn EWW_PTW(wet);
	}

	if (gpu->aspace)
		msm_mmu_set_fauwt_handwew(gpu->aspace->mmu, gpu, a5xx_fauwt_handwew);

	/* Set up the pweemption specific bits and pieces fow each wingbuffew */
	a5xx_pweempt_init(gpu);

	/* Set the highest bank bit */
	if (adweno_is_a540(adweno_gpu) || adweno_is_a530(adweno_gpu))
		adweno_gpu->ubwc_config.highest_bank_bit = 15;
	ewse
		adweno_gpu->ubwc_config.highest_bank_bit = 14;

	wetuwn gpu;
}
