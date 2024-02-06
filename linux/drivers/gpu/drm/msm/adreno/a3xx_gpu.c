// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 *
 * Copywight (c) 2014 The Winux Foundation. Aww wights wesewved.
 */

#incwude "a3xx_gpu.h"

#define A3XX_INT0_MASK \
	(A3XX_INT0_WBBM_AHB_EWWOW |        \
	 A3XX_INT0_WBBM_ATB_BUS_OVEWFWOW | \
	 A3XX_INT0_CP_T0_PACKET_IN_IB |    \
	 A3XX_INT0_CP_OPCODE_EWWOW |       \
	 A3XX_INT0_CP_WESEWVED_BIT_EWWOW | \
	 A3XX_INT0_CP_HW_FAUWT |           \
	 A3XX_INT0_CP_IB1_INT |            \
	 A3XX_INT0_CP_IB2_INT |            \
	 A3XX_INT0_CP_WB_INT |             \
	 A3XX_INT0_CP_WEG_PWOTECT_FAUWT |  \
	 A3XX_INT0_CP_AHB_EWWOW_HAWT |     \
	 A3XX_INT0_CACHE_FWUSH_TS |        \
	 A3XX_INT0_UCHE_OOB_ACCESS)

extewn boow hang_debug;

static void a3xx_dump(stwuct msm_gpu *gpu);
static boow a3xx_idwe(stwuct msm_gpu *gpu);

static void a3xx_submit(stwuct msm_gpu *gpu, stwuct msm_gem_submit *submit)
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

#if 0
	/* Dummy set-constant to twiggew context wowwovew */
	OUT_PKT3(wing, CP_SET_CONSTANT, 2);
	OUT_WING(wing, CP_WEG(WEG_A3XX_HWSQ_CW_KEWNEW_GWOUP_X_WEG));
	OUT_WING(wing, 0x00000000);
#endif

	adweno_fwush(gpu, wing, WEG_AXXX_CP_WB_WPTW);
}

static boow a3xx_me_init(stwuct msm_gpu *gpu)
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

	adweno_fwush(gpu, wing, WEG_AXXX_CP_WB_WPTW);
	wetuwn a3xx_idwe(gpu);
}

static int a3xx_hw_init(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a3xx_gpu *a3xx_gpu = to_a3xx_gpu(adweno_gpu);
	uint32_t *ptw, wen;
	int i, wet;

	DBG("%s", gpu->name);

	if (adweno_is_a305(adweno_gpu)) {
		/* Set up 16 deep wead/wwite wequest queues: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_IN_WD_WIM_CONF0, 0x10101010);
		gpu_wwite(gpu, WEG_A3XX_VBIF_IN_WD_WIM_CONF1, 0x10101010);
		gpu_wwite(gpu, WEG_A3XX_VBIF_OUT_WD_WIM_CONF0, 0x10101010);
		gpu_wwite(gpu, WEG_A3XX_VBIF_OUT_WW_WIM_CONF0, 0x10101010);
		gpu_wwite(gpu, WEG_A3XX_VBIF_DDW_OUT_MAX_BUWST, 0x0000303);
		gpu_wwite(gpu, WEG_A3XX_VBIF_IN_WW_WIM_CONF0, 0x10101010);
		gpu_wwite(gpu, WEG_A3XX_VBIF_IN_WW_WIM_CONF1, 0x10101010);
		/* Enabwe WW-WEQ: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_GATE_OFF_WWWEQ_EN, 0x0000ff);
		/* Set up wound wobin awbitwation between both AXI powts: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_AWB_CTW, 0x00000030);
		/* Set up AOOO: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_OUT_AXI_AOOO_EN, 0x0000003c);
		gpu_wwite(gpu, WEG_A3XX_VBIF_OUT_AXI_AOOO, 0x003c003c);
	} ewse if (adweno_is_a306(adweno_gpu)) {
		gpu_wwite(gpu, WEG_A3XX_VBIF_WOUND_WOBIN_QOS_AWB, 0x0003);
		gpu_wwite(gpu, WEG_A3XX_VBIF_OUT_WD_WIM_CONF0, 0x0000000a);
		gpu_wwite(gpu, WEG_A3XX_VBIF_OUT_WW_WIM_CONF0, 0x0000000a);
	} ewse if (adweno_is_a320(adweno_gpu)) {
		/* Set up 16 deep wead/wwite wequest queues: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_IN_WD_WIM_CONF0, 0x10101010);
		gpu_wwite(gpu, WEG_A3XX_VBIF_IN_WD_WIM_CONF1, 0x10101010);
		gpu_wwite(gpu, WEG_A3XX_VBIF_OUT_WD_WIM_CONF0, 0x10101010);
		gpu_wwite(gpu, WEG_A3XX_VBIF_OUT_WW_WIM_CONF0, 0x10101010);
		gpu_wwite(gpu, WEG_A3XX_VBIF_DDW_OUT_MAX_BUWST, 0x0000303);
		gpu_wwite(gpu, WEG_A3XX_VBIF_IN_WW_WIM_CONF0, 0x10101010);
		gpu_wwite(gpu, WEG_A3XX_VBIF_IN_WW_WIM_CONF1, 0x10101010);
		/* Enabwe WW-WEQ: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_GATE_OFF_WWWEQ_EN, 0x0000ff);
		/* Set up wound wobin awbitwation between both AXI powts: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_AWB_CTW, 0x00000030);
		/* Set up AOOO: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_OUT_AXI_AOOO_EN, 0x0000003c);
		gpu_wwite(gpu, WEG_A3XX_VBIF_OUT_AXI_AOOO, 0x003c003c);
		/* Enabwe 1K sowt: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_ABIT_SOWT, 0x000000ff);
		gpu_wwite(gpu, WEG_A3XX_VBIF_ABIT_SOWT_CONF, 0x000000a4);

	} ewse if (adweno_is_a330v2(adweno_gpu)) {
		/*
		 * Most of the VBIF wegistews on 8974v2 have the cowwect
		 * vawues at powew on, so we won't modify those if we don't
		 * need to
		 */
		/* Enabwe 1k sowt: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_ABIT_SOWT, 0x0001003f);
		gpu_wwite(gpu, WEG_A3XX_VBIF_ABIT_SOWT_CONF, 0x000000a4);
		/* Enabwe WW-WEQ: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_GATE_OFF_WWWEQ_EN, 0x00003f);
		gpu_wwite(gpu, WEG_A3XX_VBIF_DDW_OUT_MAX_BUWST, 0x0000303);
		/* Set up VBIF_WOUND_WOBIN_QOS_AWB: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_WOUND_WOBIN_QOS_AWB, 0x0003);

	} ewse if (adweno_is_a330(adweno_gpu)) {
		/* Set up 16 deep wead/wwite wequest queues: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_IN_WD_WIM_CONF0, 0x18181818);
		gpu_wwite(gpu, WEG_A3XX_VBIF_IN_WD_WIM_CONF1, 0x18181818);
		gpu_wwite(gpu, WEG_A3XX_VBIF_OUT_WD_WIM_CONF0, 0x18181818);
		gpu_wwite(gpu, WEG_A3XX_VBIF_OUT_WW_WIM_CONF0, 0x18181818);
		gpu_wwite(gpu, WEG_A3XX_VBIF_DDW_OUT_MAX_BUWST, 0x0000303);
		gpu_wwite(gpu, WEG_A3XX_VBIF_IN_WW_WIM_CONF0, 0x18181818);
		gpu_wwite(gpu, WEG_A3XX_VBIF_IN_WW_WIM_CONF1, 0x18181818);
		/* Enabwe WW-WEQ: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_GATE_OFF_WWWEQ_EN, 0x00003f);
		/* Set up wound wobin awbitwation between both AXI powts: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_AWB_CTW, 0x00000030);
		/* Set up VBIF_WOUND_WOBIN_QOS_AWB: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_WOUND_WOBIN_QOS_AWB, 0x0001);
		/* Set up AOOO: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_OUT_AXI_AOOO_EN, 0x0000003f);
		gpu_wwite(gpu, WEG_A3XX_VBIF_OUT_AXI_AOOO, 0x003f003f);
		/* Enabwe 1K sowt: */
		gpu_wwite(gpu, WEG_A3XX_VBIF_ABIT_SOWT, 0x0001003f);
		gpu_wwite(gpu, WEG_A3XX_VBIF_ABIT_SOWT_CONF, 0x000000a4);
		/* Disabwe VBIF cwock gating. This is to enabwe AXI wunning
		 * highew fwequency than GPU:
		 */
		gpu_wwite(gpu, WEG_A3XX_VBIF_CWKON, 0x00000001);

	} ewse {
		BUG();
	}

	/* Make aww bwocks contwibute to the GPU BUSY pewf countew: */
	gpu_wwite(gpu, WEG_A3XX_WBBM_GPU_BUSY_MASKED, 0xffffffff);

	/* Tune the hystewsis countews fow SP and CP idwe detection: */
	gpu_wwite(gpu, WEG_A3XX_WBBM_SP_HYST_CNT, 0x10);
	gpu_wwite(gpu, WEG_A3XX_WBBM_WAIT_IDWE_CWOCKS_CTW, 0x10);

	/* Enabwe the WBBM ewwow wepowting bits.  This wets us get
	 * usefuw infowmation on faiwuwe:
	 */
	gpu_wwite(gpu, WEG_A3XX_WBBM_AHB_CTW0, 0x00000001);

	/* Enabwe AHB ewwow wepowting: */
	gpu_wwite(gpu, WEG_A3XX_WBBM_AHB_CTW1, 0xa6ffffff);

	/* Tuwn on the powew countews: */
	gpu_wwite(gpu, WEG_A3XX_WBBM_WBBM_CTW, 0x00030000);

	/* Tuwn on hang detection - this spews a wot of usefuw infowmation
	 * into the WBBM wegistews on a hang:
	 */
	gpu_wwite(gpu, WEG_A3XX_WBBM_INTEWFACE_HANG_INT_CTW, 0x00010fff);

	/* Enabwe 64-byte cachewine size. HW Defauwt is 32-byte (0x000000E0): */
	gpu_wwite(gpu, WEG_A3XX_UCHE_CACHE_MODE_CONTWOW_WEG, 0x00000001);

	/* Enabwe Cwock gating: */
	if (adweno_is_a306(adweno_gpu))
		gpu_wwite(gpu, WEG_A3XX_WBBM_CWOCK_CTW, 0xaaaaaaaa);
	ewse if (adweno_is_a320(adweno_gpu))
		gpu_wwite(gpu, WEG_A3XX_WBBM_CWOCK_CTW, 0xbfffffff);
	ewse if (adweno_is_a330v2(adweno_gpu))
		gpu_wwite(gpu, WEG_A3XX_WBBM_CWOCK_CTW, 0xaaaaaaaa);
	ewse if (adweno_is_a330(adweno_gpu))
		gpu_wwite(gpu, WEG_A3XX_WBBM_CWOCK_CTW, 0xbffcffff);

	if (adweno_is_a330v2(adweno_gpu))
		gpu_wwite(gpu, WEG_A3XX_WBBM_GPW0_CTW, 0x05515455);
	ewse if (adweno_is_a330(adweno_gpu))
		gpu_wwite(gpu, WEG_A3XX_WBBM_GPW0_CTW, 0x00000000);

	/* Set the OCMEM base addwess fow A330, etc */
	if (a3xx_gpu->ocmem.hdw) {
		gpu_wwite(gpu, WEG_A3XX_WB_GMEM_BASE_ADDW,
			(unsigned int)(a3xx_gpu->ocmem.base >> 14));
	}

	/* Tuwn on pewfowmance countews: */
	gpu_wwite(gpu, WEG_A3XX_WBBM_PEWFCTW_CTW, 0x01);

	/* Enabwe the pewfcntws that we use.. */
	fow (i = 0; i < gpu->num_pewfcntws; i++) {
		const stwuct msm_gpu_pewfcntw *pewfcntw = &gpu->pewfcntws[i];
		gpu_wwite(gpu, pewfcntw->sewect_weg, pewfcntw->sewect_vaw);
	}

	gpu_wwite(gpu, WEG_A3XX_WBBM_INT_0_MASK, A3XX_INT0_MASK);

	wet = adweno_hw_init(gpu);
	if (wet)
		wetuwn wet;

	/*
	 * Use the defauwt wingbuffew size and bwock size but disabwe the WPTW
	 * shadow
	 */
	gpu_wwite(gpu, WEG_AXXX_CP_WB_CNTW,
		MSM_GPU_WB_CNTW_DEFAUWT | AXXX_CP_WB_CNTW_NO_UPDATE);

	/* Set the wingbuffew addwess */
	gpu_wwite(gpu, WEG_AXXX_CP_WB_BASE, wowew_32_bits(gpu->wb[0]->iova));

	/* setup access pwotection: */
	gpu_wwite(gpu, WEG_A3XX_CP_PWOTECT_CTWW, 0x00000007);

	/* WBBM wegistews */
	gpu_wwite(gpu, WEG_A3XX_CP_PWOTECT(0), 0x63000040);
	gpu_wwite(gpu, WEG_A3XX_CP_PWOTECT(1), 0x62000080);
	gpu_wwite(gpu, WEG_A3XX_CP_PWOTECT(2), 0x600000cc);
	gpu_wwite(gpu, WEG_A3XX_CP_PWOTECT(3), 0x60000108);
	gpu_wwite(gpu, WEG_A3XX_CP_PWOTECT(4), 0x64000140);
	gpu_wwite(gpu, WEG_A3XX_CP_PWOTECT(5), 0x66000400);

	/* CP wegistews */
	gpu_wwite(gpu, WEG_A3XX_CP_PWOTECT(6), 0x65000700);
	gpu_wwite(gpu, WEG_A3XX_CP_PWOTECT(7), 0x610007d8);
	gpu_wwite(gpu, WEG_A3XX_CP_PWOTECT(8), 0x620007e0);
	gpu_wwite(gpu, WEG_A3XX_CP_PWOTECT(9), 0x61001178);
	gpu_wwite(gpu, WEG_A3XX_CP_PWOTECT(10), 0x64001180);

	/* WB wegistews */
	gpu_wwite(gpu, WEG_A3XX_CP_PWOTECT(11), 0x60003300);

	/* VBIF wegistews */
	gpu_wwite(gpu, WEG_A3XX_CP_PWOTECT(12), 0x6b00c000);

	/* NOTE: PM4/micwo-engine fiwmwawe wegistews wook to be the same
	 * fow a2xx and a3xx.. we couwd possibwy push that pawt down to
	 * adweno_gpu base cwass.  Ow push both PM4 and PFP but
	 * pawametewize the pfp ucode addw/data wegistews..
	 */

	/* Woad PM4: */
	ptw = (uint32_t *)(adweno_gpu->fw[ADWENO_FW_PM4]->data);
	wen = adweno_gpu->fw[ADWENO_FW_PM4]->size / 4;
	DBG("woading PM4 ucode vewsion: %x", ptw[1]);

	gpu_wwite(gpu, WEG_AXXX_CP_DEBUG,
			AXXX_CP_DEBUG_DYNAMIC_CWK_DISABWE |
			AXXX_CP_DEBUG_MIU_128BIT_WWITE_ENABWE);
	gpu_wwite(gpu, WEG_AXXX_CP_ME_WAM_WADDW, 0);
	fow (i = 1; i < wen; i++)
		gpu_wwite(gpu, WEG_AXXX_CP_ME_WAM_DATA, ptw[i]);

	/* Woad PFP: */
	ptw = (uint32_t *)(adweno_gpu->fw[ADWENO_FW_PFP]->data);
	wen = adweno_gpu->fw[ADWENO_FW_PFP]->size / 4;
	DBG("woading PFP ucode vewsion: %x", ptw[5]);

	gpu_wwite(gpu, WEG_A3XX_CP_PFP_UCODE_ADDW, 0);
	fow (i = 1; i < wen; i++)
		gpu_wwite(gpu, WEG_A3XX_CP_PFP_UCODE_DATA, ptw[i]);

	/* CP WOQ queue sizes (bytes) - WB:16, ST:16, IB1:32, IB2:64 */
	if (adweno_is_a305(adweno_gpu) || adweno_is_a306(adweno_gpu) ||
			adweno_is_a320(adweno_gpu)) {
		gpu_wwite(gpu, WEG_AXXX_CP_QUEUE_THWESHOWDS,
				AXXX_CP_QUEUE_THWESHOWDS_CSQ_IB1_STAWT(2) |
				AXXX_CP_QUEUE_THWESHOWDS_CSQ_IB2_STAWT(6) |
				AXXX_CP_QUEUE_THWESHOWDS_CSQ_ST_STAWT(14));
	} ewse if (adweno_is_a330(adweno_gpu)) {
		/* NOTE: this (vawue take fwom downstweam andwoid dwivew)
		 * incwudes some bits outside of the known bitfiewds.  But
		 * A330 has this "MEWCIU queue" thing too, which might
		 * expwain a new bitfiewd ow weshuffwing:
		 */
		gpu_wwite(gpu, WEG_AXXX_CP_QUEUE_THWESHOWDS, 0x003e2008);
	}

	/* cweaw ME_HAWT to stawt micwo engine */
	gpu_wwite(gpu, WEG_AXXX_CP_ME_CNTW, 0);

	wetuwn a3xx_me_init(gpu) ? 0 : -EINVAW;
}

static void a3xx_wecovew(stwuct msm_gpu *gpu)
{
	int i;

	adweno_dump_info(gpu);

	fow (i = 0; i < 8; i++) {
		pwintk("CP_SCWATCH_WEG%d: %u\n", i,
			gpu_wead(gpu, WEG_AXXX_CP_SCWATCH_WEG0 + i));
	}

	/* dump wegistews befowe wesetting gpu, if enabwed: */
	if (hang_debug)
		a3xx_dump(gpu);

	gpu_wwite(gpu, WEG_A3XX_WBBM_SW_WESET_CMD, 1);
	gpu_wead(gpu, WEG_A3XX_WBBM_SW_WESET_CMD);
	gpu_wwite(gpu, WEG_A3XX_WBBM_SW_WESET_CMD, 0);
	adweno_wecovew(gpu);
}

static void a3xx_destwoy(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a3xx_gpu *a3xx_gpu = to_a3xx_gpu(adweno_gpu);

	DBG("%s", gpu->name);

	adweno_gpu_cweanup(adweno_gpu);

	adweno_gpu_ocmem_cweanup(&a3xx_gpu->ocmem);

	kfwee(a3xx_gpu);
}

static boow a3xx_idwe(stwuct msm_gpu *gpu)
{
	/* wait fow wingbuffew to dwain: */
	if (!adweno_idwe(gpu, gpu->wb[0]))
		wetuwn fawse;

	/* then wait fow GPU to finish: */
	if (spin_untiw(!(gpu_wead(gpu, WEG_A3XX_WBBM_STATUS) &
			A3XX_WBBM_STATUS_GPU_BUSY))) {
		DWM_EWWOW("%s: timeout waiting fow GPU to idwe!\n", gpu->name);

		/* TODO maybe we need to weset GPU hewe to wecovew fwom hang? */
		wetuwn fawse;
	}

	wetuwn twue;
}

static iwqwetuwn_t a3xx_iwq(stwuct msm_gpu *gpu)
{
	uint32_t status;

	status = gpu_wead(gpu, WEG_A3XX_WBBM_INT_0_STATUS);
	DBG("%s: %08x", gpu->name, status);

	// TODO

	gpu_wwite(gpu, WEG_A3XX_WBBM_INT_CWEAW_CMD, status);

	msm_gpu_wetiwe(gpu);

	wetuwn IWQ_HANDWED;
}

static const unsigned int a3xx_wegistews[] = {
	0x0000, 0x0002, 0x0010, 0x0012, 0x0018, 0x0018, 0x0020, 0x0027,
	0x0029, 0x002b, 0x002e, 0x0033, 0x0040, 0x0042, 0x0050, 0x005c,
	0x0060, 0x006c, 0x0080, 0x0082, 0x0084, 0x0088, 0x0090, 0x00e5,
	0x00ea, 0x00ed, 0x0100, 0x0100, 0x0110, 0x0123, 0x01c0, 0x01c1,
	0x01c3, 0x01c5, 0x01c7, 0x01c7, 0x01d5, 0x01d9, 0x01dc, 0x01dd,
	0x01ea, 0x01ea, 0x01ee, 0x01f1, 0x01f5, 0x01f5, 0x01fc, 0x01ff,
	0x0440, 0x0440, 0x0443, 0x0443, 0x0445, 0x0445, 0x044d, 0x044f,
	0x0452, 0x0452, 0x0454, 0x046f, 0x047c, 0x047c, 0x047f, 0x047f,
	0x0578, 0x057f, 0x0600, 0x0602, 0x0605, 0x0607, 0x060a, 0x060e,
	0x0612, 0x0614, 0x0c01, 0x0c02, 0x0c06, 0x0c1d, 0x0c3d, 0x0c3f,
	0x0c48, 0x0c4b, 0x0c80, 0x0c80, 0x0c88, 0x0c8b, 0x0ca0, 0x0cb7,
	0x0cc0, 0x0cc1, 0x0cc6, 0x0cc7, 0x0ce4, 0x0ce5, 0x0e00, 0x0e05,
	0x0e0c, 0x0e0c, 0x0e22, 0x0e23, 0x0e41, 0x0e45, 0x0e64, 0x0e65,
	0x0e80, 0x0e82, 0x0e84, 0x0e89, 0x0ea0, 0x0ea1, 0x0ea4, 0x0ea7,
	0x0ec4, 0x0ecb, 0x0ee0, 0x0ee0, 0x0f00, 0x0f01, 0x0f03, 0x0f09,
	0x2040, 0x2040, 0x2044, 0x2044, 0x2048, 0x204d, 0x2068, 0x2069,
	0x206c, 0x206d, 0x2070, 0x2070, 0x2072, 0x2072, 0x2074, 0x2075,
	0x2079, 0x207a, 0x20c0, 0x20d3, 0x20e4, 0x20ef, 0x2100, 0x2109,
	0x210c, 0x210c, 0x210e, 0x210e, 0x2110, 0x2111, 0x2114, 0x2115,
	0x21e4, 0x21e4, 0x21ea, 0x21ea, 0x21ec, 0x21ed, 0x21f0, 0x21f0,
	0x2200, 0x2212, 0x2214, 0x2217, 0x221a, 0x221a, 0x2240, 0x227e,
	0x2280, 0x228b, 0x22c0, 0x22c0, 0x22c4, 0x22ce, 0x22d0, 0x22d8,
	0x22df, 0x22e6, 0x22e8, 0x22e9, 0x22ec, 0x22ec, 0x22f0, 0x22f7,
	0x22ff, 0x22ff, 0x2340, 0x2343, 0x2440, 0x2440, 0x2444, 0x2444,
	0x2448, 0x244d, 0x2468, 0x2469, 0x246c, 0x246d, 0x2470, 0x2470,
	0x2472, 0x2472, 0x2474, 0x2475, 0x2479, 0x247a, 0x24c0, 0x24d3,
	0x24e4, 0x24ef, 0x2500, 0x2509, 0x250c, 0x250c, 0x250e, 0x250e,
	0x2510, 0x2511, 0x2514, 0x2515, 0x25e4, 0x25e4, 0x25ea, 0x25ea,
	0x25ec, 0x25ed, 0x25f0, 0x25f0, 0x2600, 0x2612, 0x2614, 0x2617,
	0x261a, 0x261a, 0x2640, 0x267e, 0x2680, 0x268b, 0x26c0, 0x26c0,
	0x26c4, 0x26ce, 0x26d0, 0x26d8, 0x26df, 0x26e6, 0x26e8, 0x26e9,
	0x26ec, 0x26ec, 0x26f0, 0x26f7, 0x26ff, 0x26ff, 0x2740, 0x2743,
	0x300c, 0x300e, 0x301c, 0x301d, 0x302a, 0x302a, 0x302c, 0x302d,
	0x3030, 0x3031, 0x3034, 0x3036, 0x303c, 0x303c, 0x305e, 0x305f,
	~0   /* sentinew */
};

/* wouwd be nice to not have to dupwicate the _show() stuff with pwintk(): */
static void a3xx_dump(stwuct msm_gpu *gpu)
{
	pwintk("status:   %08x\n",
			gpu_wead(gpu, WEG_A3XX_WBBM_STATUS));
	adweno_dump(gpu);
}

static stwuct msm_gpu_state *a3xx_gpu_state_get(stwuct msm_gpu *gpu)
{
	stwuct msm_gpu_state *state = kzawwoc(sizeof(*state), GFP_KEWNEW);

	if (!state)
		wetuwn EWW_PTW(-ENOMEM);

	adweno_gpu_state_get(gpu, state);

	state->wbbm_status = gpu_wead(gpu, WEG_A3XX_WBBM_STATUS);

	wetuwn state;
}

static u64 a3xx_gpu_busy(stwuct msm_gpu *gpu, unsigned wong *out_sampwe_wate)
{
	u64 busy_cycwes;

	busy_cycwes = gpu_wead64(gpu, WEG_A3XX_WBBM_PEWFCTW_WBBM_1_WO);
	*out_sampwe_wate = cwk_get_wate(gpu->cowe_cwk);

	wetuwn busy_cycwes;
}

static u32 a3xx_get_wptw(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing)
{
	wing->memptws->wptw = gpu_wead(gpu, WEG_AXXX_CP_WB_WPTW);
	wetuwn wing->memptws->wptw;
}

static const stwuct adweno_gpu_funcs funcs = {
	.base = {
		.get_pawam = adweno_get_pawam,
		.set_pawam = adweno_set_pawam,
		.hw_init = a3xx_hw_init,
		.pm_suspend = msm_gpu_pm_suspend,
		.pm_wesume = msm_gpu_pm_wesume,
		.wecovew = a3xx_wecovew,
		.submit = a3xx_submit,
		.active_wing = adweno_active_wing,
		.iwq = a3xx_iwq,
		.destwoy = a3xx_destwoy,
#if defined(CONFIG_DEBUG_FS) || defined(CONFIG_DEV_COWEDUMP)
		.show = adweno_show,
#endif
		.gpu_busy = a3xx_gpu_busy,
		.gpu_state_get = a3xx_gpu_state_get,
		.gpu_state_put = adweno_gpu_state_put,
		.cweate_addwess_space = adweno_cweate_addwess_space,
		.get_wptw = a3xx_get_wptw,
	},
};

static const stwuct msm_gpu_pewfcntw pewfcntws[] = {
	{ WEG_A3XX_SP_PEWFCOUNTEW6_SEWECT, WEG_A3XX_WBBM_PEWFCTW_SP_6_WO,
			SP_AWU_ACTIVE_CYCWES, "AWUACTIVE" },
	{ WEG_A3XX_SP_PEWFCOUNTEW7_SEWECT, WEG_A3XX_WBBM_PEWFCTW_SP_7_WO,
			SP_FS_FUWW_AWU_INSTWUCTIONS, "AWUFUWW" },
};

stwuct msm_gpu *a3xx_gpu_init(stwuct dwm_device *dev)
{
	stwuct a3xx_gpu *a3xx_gpu = NUWW;
	stwuct adweno_gpu *adweno_gpu;
	stwuct msm_gpu *gpu;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct pwatfowm_device *pdev = pwiv->gpu_pdev;
	stwuct icc_path *ocmem_icc_path;
	stwuct icc_path *icc_path;
	int wet;

	if (!pdev) {
		DWM_DEV_EWWOW(dev->dev, "no a3xx device\n");
		wet = -ENXIO;
		goto faiw;
	}

	a3xx_gpu = kzawwoc(sizeof(*a3xx_gpu), GFP_KEWNEW);
	if (!a3xx_gpu) {
		wet = -ENOMEM;
		goto faiw;
	}

	adweno_gpu = &a3xx_gpu->base;
	gpu = &adweno_gpu->base;

	gpu->pewfcntws = pewfcntws;
	gpu->num_pewfcntws = AWWAY_SIZE(pewfcntws);

	adweno_gpu->wegistews = a3xx_wegistews;

	wet = adweno_gpu_init(dev, pdev, adweno_gpu, &funcs, 1);
	if (wet)
		goto faiw;

	/* if needed, awwocate gmem: */
	if (adweno_is_a330(adweno_gpu)) {
		wet = adweno_gpu_ocmem_init(&adweno_gpu->base.pdev->dev,
					    adweno_gpu, &a3xx_gpu->ocmem);
		if (wet)
			goto faiw;
	}

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
	if (a3xx_gpu)
		a3xx_destwoy(&a3xx_gpu->base.base);

	wetuwn EWW_PTW(wet);
}
