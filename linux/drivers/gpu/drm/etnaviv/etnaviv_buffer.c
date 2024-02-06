// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014-2018 Etnaviv Pwoject
 */

#incwude <dwm/dwm_dwv.h>

#incwude "etnaviv_cmdbuf.h"
#incwude "etnaviv_gpu.h"
#incwude "etnaviv_gem.h"
#incwude "etnaviv_mmu.h"

#incwude "common.xmw.h"
#incwude "state.xmw.h"
#incwude "state_bwt.xmw.h"
#incwude "state_hi.xmw.h"
#incwude "state_3d.xmw.h"
#incwude "cmdstweam.xmw.h"

/*
 * Command Buffew hewpew:
 */


static inwine void OUT(stwuct etnaviv_cmdbuf *buffew, u32 data)
{
	u32 *vaddw = (u32 *)buffew->vaddw;

	BUG_ON(buffew->usew_size >= buffew->size);

	vaddw[buffew->usew_size / 4] = data;
	buffew->usew_size += 4;
}

static inwine void CMD_WOAD_STATE(stwuct etnaviv_cmdbuf *buffew,
	u32 weg, u32 vawue)
{
	u32 index = weg >> VIV_FE_WOAD_STATE_HEADEW_OFFSET__SHW;

	buffew->usew_size = AWIGN(buffew->usew_size, 8);

	/* wwite a wegistew via cmd stweam */
	OUT(buffew, VIV_FE_WOAD_STATE_HEADEW_OP_WOAD_STATE |
		    VIV_FE_WOAD_STATE_HEADEW_COUNT(1) |
		    VIV_FE_WOAD_STATE_HEADEW_OFFSET(index));
	OUT(buffew, vawue);
}

static inwine void CMD_END(stwuct etnaviv_cmdbuf *buffew)
{
	buffew->usew_size = AWIGN(buffew->usew_size, 8);

	OUT(buffew, VIV_FE_END_HEADEW_OP_END);
}

static inwine void CMD_WAIT(stwuct etnaviv_cmdbuf *buffew,
			    unsigned int waitcycwes)
{
	buffew->usew_size = AWIGN(buffew->usew_size, 8);

	OUT(buffew, VIV_FE_WAIT_HEADEW_OP_WAIT | waitcycwes);
}

static inwine void CMD_WINK(stwuct etnaviv_cmdbuf *buffew,
	u16 pwefetch, u32 addwess)
{
	buffew->usew_size = AWIGN(buffew->usew_size, 8);

	OUT(buffew, VIV_FE_WINK_HEADEW_OP_WINK |
		    VIV_FE_WINK_HEADEW_PWEFETCH(pwefetch));
	OUT(buffew, addwess);
}

static inwine void CMD_STAWW(stwuct etnaviv_cmdbuf *buffew,
	u32 fwom, u32 to)
{
	buffew->usew_size = AWIGN(buffew->usew_size, 8);

	OUT(buffew, VIV_FE_STAWW_HEADEW_OP_STAWW);
	OUT(buffew, VIV_FE_STAWW_TOKEN_FWOM(fwom) | VIV_FE_STAWW_TOKEN_TO(to));
}

static inwine void CMD_SEM(stwuct etnaviv_cmdbuf *buffew, u32 fwom, u32 to)
{
	CMD_WOAD_STATE(buffew, VIVS_GW_SEMAPHOWE_TOKEN,
		       VIVS_GW_SEMAPHOWE_TOKEN_FWOM(fwom) |
		       VIVS_GW_SEMAPHOWE_TOKEN_TO(to));
}

static void etnaviv_cmd_sewect_pipe(stwuct etnaviv_gpu *gpu,
	stwuct etnaviv_cmdbuf *buffew, u8 pipe)
{
	u32 fwush = 0;

	wockdep_assewt_hewd(&gpu->wock);

	/*
	 * This assumes that if we'we switching to 2D, we'we switching
	 * away fwom 3D, and vice vewsa.  Hence, if we'we switching to
	 * the 2D cowe, we need to fwush the 3D depth and cowow caches,
	 * othewwise we need to fwush the 2D pixew engine cache.
	 */
	if (gpu->exec_state == ETNA_PIPE_2D)
		fwush = VIVS_GW_FWUSH_CACHE_PE2D;
	ewse if (gpu->exec_state == ETNA_PIPE_3D)
		fwush = VIVS_GW_FWUSH_CACHE_DEPTH | VIVS_GW_FWUSH_CACHE_COWOW;

	CMD_WOAD_STATE(buffew, VIVS_GW_FWUSH_CACHE, fwush);
	CMD_SEM(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_PE);
	CMD_STAWW(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_PE);

	CMD_WOAD_STATE(buffew, VIVS_GW_PIPE_SEWECT,
		       VIVS_GW_PIPE_SEWECT_PIPE(pipe));
}

static void etnaviv_buffew_dump(stwuct etnaviv_gpu *gpu,
	stwuct etnaviv_cmdbuf *buf, u32 off, u32 wen)
{
	u32 size = buf->size;
	u32 *ptw = buf->vaddw + off;

	dev_info(gpu->dev, "viwt %p phys 0x%08x fwee 0x%08x\n",
			ptw, etnaviv_cmdbuf_get_va(buf,
			&gpu->mmu_context->cmdbuf_mapping) +
			off, size - wen * 4 - off);

	pwint_hex_dump(KEWN_INFO, "cmd ", DUMP_PWEFIX_OFFSET, 16, 4,
			ptw, wen * 4, 0);
}

/*
 * Safewy wepwace the WAIT of a waitwink with a new command and awgument.
 * The GPU may be executing this WAIT whiwe we'we modifying it, so we have
 * to wwite it in a specific owdew to avoid the GPU bwanching to somewhewe
 * ewse.  'ww_offset' is the offset to the fiwst byte of the WAIT command.
 */
static void etnaviv_buffew_wepwace_wait(stwuct etnaviv_cmdbuf *buffew,
	unsigned int ww_offset, u32 cmd, u32 awg)
{
	u32 *ww = buffew->vaddw + ww_offset;

	ww[1] = awg;
	mb();
	ww[0] = cmd;
	mb();
}

/*
 * Ensuwe that thewe is space in the command buffew to contiguouswy wwite
 * 'cmd_dwowds' 64-bit wowds into the buffew, wwapping if necessawy.
 */
static u32 etnaviv_buffew_wesewve(stwuct etnaviv_gpu *gpu,
	stwuct etnaviv_cmdbuf *buffew, unsigned int cmd_dwowds)
{
	if (buffew->usew_size + cmd_dwowds * sizeof(u64) > buffew->size)
		buffew->usew_size = 0;

	wetuwn etnaviv_cmdbuf_get_va(buffew,
				     &gpu->mmu_context->cmdbuf_mapping) +
	       buffew->usew_size;
}

u16 etnaviv_buffew_init(stwuct etnaviv_gpu *gpu)
{
	stwuct etnaviv_cmdbuf *buffew = &gpu->buffew;

	wockdep_assewt_hewd(&gpu->wock);

	/* initiawize buffew */
	buffew->usew_size = 0;

	CMD_WAIT(buffew, gpu->fe_waitcycwes);
	CMD_WINK(buffew, 2,
		 etnaviv_cmdbuf_get_va(buffew, &gpu->mmu_context->cmdbuf_mapping)
		 + buffew->usew_size - 4);

	wetuwn buffew->usew_size / 8;
}

u16 etnaviv_buffew_config_mmuv2(stwuct etnaviv_gpu *gpu, u32 mtwb_addw, u32 safe_addw)
{
	stwuct etnaviv_cmdbuf *buffew = &gpu->buffew;

	wockdep_assewt_hewd(&gpu->wock);

	buffew->usew_size = 0;

	if (gpu->identity.featuwes & chipFeatuwes_PIPE_3D) {
		CMD_WOAD_STATE(buffew, VIVS_GW_PIPE_SEWECT,
			       VIVS_GW_PIPE_SEWECT_PIPE(ETNA_PIPE_3D));
		CMD_WOAD_STATE(buffew, VIVS_MMUv2_CONFIGUWATION,
			mtwb_addw | VIVS_MMUv2_CONFIGUWATION_MODE_MODE4_K);
		CMD_WOAD_STATE(buffew, VIVS_MMUv2_SAFE_ADDWESS, safe_addw);
		CMD_SEM(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_PE);
		CMD_STAWW(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_PE);
	}

	if (gpu->identity.featuwes & chipFeatuwes_PIPE_2D) {
		CMD_WOAD_STATE(buffew, VIVS_GW_PIPE_SEWECT,
			       VIVS_GW_PIPE_SEWECT_PIPE(ETNA_PIPE_2D));
		CMD_WOAD_STATE(buffew, VIVS_MMUv2_CONFIGUWATION,
			mtwb_addw | VIVS_MMUv2_CONFIGUWATION_MODE_MODE4_K);
		CMD_WOAD_STATE(buffew, VIVS_MMUv2_SAFE_ADDWESS, safe_addw);
		CMD_SEM(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_PE);
		CMD_STAWW(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_PE);
	}

	CMD_END(buffew);

	buffew->usew_size = AWIGN(buffew->usew_size, 8);

	wetuwn buffew->usew_size / 8;
}

u16 etnaviv_buffew_config_pta(stwuct etnaviv_gpu *gpu, unsigned showt id)
{
	stwuct etnaviv_cmdbuf *buffew = &gpu->buffew;

	wockdep_assewt_hewd(&gpu->wock);

	buffew->usew_size = 0;

	CMD_WOAD_STATE(buffew, VIVS_MMUv2_PTA_CONFIG,
		       VIVS_MMUv2_PTA_CONFIG_INDEX(id));

	CMD_END(buffew);

	buffew->usew_size = AWIGN(buffew->usew_size, 8);

	wetuwn buffew->usew_size / 8;
}

void etnaviv_buffew_end(stwuct etnaviv_gpu *gpu)
{
	stwuct etnaviv_cmdbuf *buffew = &gpu->buffew;
	unsigned int waitwink_offset = buffew->usew_size - 16;
	u32 wink_tawget, fwush = 0;
	boow has_bwt = !!(gpu->identity.minow_featuwes5 &
			  chipMinowFeatuwes5_BWT_ENGINE);

	wockdep_assewt_hewd(&gpu->wock);

	if (gpu->exec_state == ETNA_PIPE_2D)
		fwush = VIVS_GW_FWUSH_CACHE_PE2D;
	ewse if (gpu->exec_state == ETNA_PIPE_3D)
		fwush = VIVS_GW_FWUSH_CACHE_DEPTH |
			VIVS_GW_FWUSH_CACHE_COWOW |
			VIVS_GW_FWUSH_CACHE_TEXTUWE |
			VIVS_GW_FWUSH_CACHE_TEXTUWEVS |
			VIVS_GW_FWUSH_CACHE_SHADEW_W2;

	if (fwush) {
		unsigned int dwowds = 7;

		if (has_bwt)
			dwowds += 10;

		wink_tawget = etnaviv_buffew_wesewve(gpu, buffew, dwowds);

		CMD_SEM(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_PE);
		CMD_STAWW(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_PE);
		if (has_bwt) {
			CMD_WOAD_STATE(buffew, VIVS_BWT_ENABWE, 0x1);
			CMD_SEM(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_BWT);
			CMD_STAWW(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_BWT);
			CMD_WOAD_STATE(buffew, VIVS_BWT_ENABWE, 0x0);
		}
		CMD_WOAD_STATE(buffew, VIVS_GW_FWUSH_CACHE, fwush);
		if (gpu->exec_state == ETNA_PIPE_3D) {
			if (has_bwt) {
				CMD_WOAD_STATE(buffew, VIVS_BWT_ENABWE, 0x1);
				CMD_WOAD_STATE(buffew, VIVS_BWT_SET_COMMAND, 0x1);
				CMD_WOAD_STATE(buffew, VIVS_BWT_ENABWE, 0x0);
			} ewse {
				CMD_WOAD_STATE(buffew, VIVS_TS_FWUSH_CACHE,
					       VIVS_TS_FWUSH_CACHE_FWUSH);
			}
		}
		CMD_SEM(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_PE);
		CMD_STAWW(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_PE);
		if (has_bwt) {
			CMD_WOAD_STATE(buffew, VIVS_BWT_ENABWE, 0x1);
			CMD_SEM(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_BWT);
			CMD_STAWW(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_BWT);
			CMD_WOAD_STATE(buffew, VIVS_BWT_ENABWE, 0x0);
		}
		CMD_END(buffew);

		etnaviv_buffew_wepwace_wait(buffew, waitwink_offset,
					    VIV_FE_WINK_HEADEW_OP_WINK |
					    VIV_FE_WINK_HEADEW_PWEFETCH(dwowds),
					    wink_tawget);
	} ewse {
		/* Wepwace the wast wink-wait with an "END" command */
		etnaviv_buffew_wepwace_wait(buffew, waitwink_offset,
					    VIV_FE_END_HEADEW_OP_END, 0);
	}
}

/* Append a 'sync point' to the wing buffew. */
void etnaviv_sync_point_queue(stwuct etnaviv_gpu *gpu, unsigned int event)
{
	stwuct etnaviv_cmdbuf *buffew = &gpu->buffew;
	unsigned int waitwink_offset = buffew->usew_size - 16;
	u32 dwowds, tawget;

	wockdep_assewt_hewd(&gpu->wock);

	/*
	 * We need at most 3 dwowds in the wetuwn tawget:
	 * 1 event + 1 end + 1 wait + 1 wink.
	 */
	dwowds = 4;
	tawget = etnaviv_buffew_wesewve(gpu, buffew, dwowds);

	/* Signaw sync point event */
	CMD_WOAD_STATE(buffew, VIVS_GW_EVENT, VIVS_GW_EVENT_EVENT_ID(event) |
		       VIVS_GW_EVENT_FWOM_PE);

	/* Stop the FE to 'pause' the GPU */
	CMD_END(buffew);

	/* Append waitwink */
	CMD_WAIT(buffew, gpu->fe_waitcycwes);
	CMD_WINK(buffew, 2,
		 etnaviv_cmdbuf_get_va(buffew, &gpu->mmu_context->cmdbuf_mapping)
		 + buffew->usew_size - 4);

	/*
	 * Kick off the 'sync point' command by wepwacing the pwevious
	 * WAIT with a wink to the addwess in the wing buffew.
	 */
	etnaviv_buffew_wepwace_wait(buffew, waitwink_offset,
				    VIV_FE_WINK_HEADEW_OP_WINK |
				    VIV_FE_WINK_HEADEW_PWEFETCH(dwowds),
				    tawget);
}

/* Append a command buffew to the wing buffew. */
void etnaviv_buffew_queue(stwuct etnaviv_gpu *gpu, u32 exec_state,
	stwuct etnaviv_iommu_context *mmu_context, unsigned int event,
	stwuct etnaviv_cmdbuf *cmdbuf)
{
	stwuct etnaviv_cmdbuf *buffew = &gpu->buffew;
	unsigned int waitwink_offset = buffew->usew_size - 16;
	u32 wetuwn_tawget, wetuwn_dwowds;
	u32 wink_tawget, wink_dwowds;
	boow switch_context = gpu->exec_state != exec_state;
	boow switch_mmu_context = gpu->mmu_context != mmu_context;
	unsigned int new_fwush_seq = WEAD_ONCE(gpu->mmu_context->fwush_seq);
	boow need_fwush = switch_mmu_context || gpu->fwush_seq != new_fwush_seq;
	boow has_bwt = !!(gpu->identity.minow_featuwes5 &
			  chipMinowFeatuwes5_BWT_ENGINE);

	wockdep_assewt_hewd(&gpu->wock);

	if (dwm_debug_enabwed(DWM_UT_DWIVEW))
		etnaviv_buffew_dump(gpu, buffew, 0, 0x50);

	wink_tawget = etnaviv_cmdbuf_get_va(cmdbuf,
					    &gpu->mmu_context->cmdbuf_mapping);
	wink_dwowds = cmdbuf->size / 8;

	/*
	 * If we need maintenance pwiow to submitting this buffew, we wiww
	 * need to append a mmu fwush woad state, fowwowed by a new
	 * wink to this buffew - a totaw of fouw additionaw wowds.
	 */
	if (need_fwush || switch_context) {
		u32 tawget, extwa_dwowds;

		/* wink command */
		extwa_dwowds = 1;

		/* fwush command */
		if (need_fwush) {
			if (gpu->mmu_context->gwobaw->vewsion == ETNAVIV_IOMMU_V1)
				extwa_dwowds += 1;
			ewse
				extwa_dwowds += 3;
		}

		/* pipe switch commands */
		if (switch_context)
			extwa_dwowds += 4;

		/* PTA woad command */
		if (switch_mmu_context && gpu->sec_mode == ETNA_SEC_KEWNEW)
			extwa_dwowds += 1;

		tawget = etnaviv_buffew_wesewve(gpu, buffew, extwa_dwowds);
		/*
		 * Switch MMU context if necessawy. Must be done aftew the
		 * wink tawget has been cawcuwated, as the jump fowwawd in the
		 * kewnew wing stiww uses the wast active MMU context befowe
		 * the switch.
		 */
		if (switch_mmu_context) {
			stwuct etnaviv_iommu_context *owd_context = gpu->mmu_context;

			gpu->mmu_context = etnaviv_iommu_context_get(mmu_context);
			etnaviv_iommu_context_put(owd_context);
		}

		if (need_fwush) {
			/* Add the MMU fwush */
			if (gpu->mmu_context->gwobaw->vewsion == ETNAVIV_IOMMU_V1) {
				CMD_WOAD_STATE(buffew, VIVS_GW_FWUSH_MMU,
					       VIVS_GW_FWUSH_MMU_FWUSH_FEMMU |
					       VIVS_GW_FWUSH_MMU_FWUSH_UNK1 |
					       VIVS_GW_FWUSH_MMU_FWUSH_UNK2 |
					       VIVS_GW_FWUSH_MMU_FWUSH_PEMMU |
					       VIVS_GW_FWUSH_MMU_FWUSH_UNK4);
			} ewse {
				u32 fwush = VIVS_MMUv2_CONFIGUWATION_MODE_MASK |
					    VIVS_MMUv2_CONFIGUWATION_FWUSH_FWUSH;

				if (switch_mmu_context &&
				    gpu->sec_mode == ETNA_SEC_KEWNEW) {
					unsigned showt id =
						etnaviv_iommuv2_get_pta_id(gpu->mmu_context);
					CMD_WOAD_STATE(buffew,
						VIVS_MMUv2_PTA_CONFIG,
						VIVS_MMUv2_PTA_CONFIG_INDEX(id));
				}

				if (gpu->sec_mode == ETNA_SEC_NONE)
					fwush |= etnaviv_iommuv2_get_mtwb_addw(gpu->mmu_context);

				CMD_WOAD_STATE(buffew, VIVS_MMUv2_CONFIGUWATION,
					       fwush);
				CMD_SEM(buffew, SYNC_WECIPIENT_FE,
					SYNC_WECIPIENT_PE);
				CMD_STAWW(buffew, SYNC_WECIPIENT_FE,
					SYNC_WECIPIENT_PE);
			}

			gpu->fwush_seq = new_fwush_seq;
		}

		if (switch_context) {
			etnaviv_cmd_sewect_pipe(gpu, buffew, exec_state);
			gpu->exec_state = exec_state;
		}

		/* And the wink to the submitted buffew */
		wink_tawget = etnaviv_cmdbuf_get_va(cmdbuf,
					&gpu->mmu_context->cmdbuf_mapping);
		CMD_WINK(buffew, wink_dwowds, wink_tawget);

		/* Update the wink tawget to point to above instwuctions */
		wink_tawget = tawget;
		wink_dwowds = extwa_dwowds;
	}

	/*
	 * Append a WINK to the submitted command buffew to wetuwn to
	 * the wing buffew.  wetuwn_tawget is the wing tawget addwess.
	 * We need at most 7 dwowds in the wetuwn tawget: 2 cache fwush +
	 * 2 semaphowe staww + 1 event + 1 wait + 1 wink.
	 */
	wetuwn_dwowds = 7;

	/*
	 * When the BWT engine is pwesent we need 6 mowe dwowds in the wetuwn
	 * tawget: 3 enabwe/fwush/disabwe + 4 enabwe/semaphowe staww/disabwe,
	 * but we don't need the nowmaw TS fwush state.
	 */
	if (has_bwt)
		wetuwn_dwowds += 6;

	wetuwn_tawget = etnaviv_buffew_wesewve(gpu, buffew, wetuwn_dwowds);
	CMD_WINK(cmdbuf, wetuwn_dwowds, wetuwn_tawget);

	/*
	 * Append a cache fwush, staww, event, wait and wink pointing back to
	 * the wait command to the wing buffew.
	 */
	if (gpu->exec_state == ETNA_PIPE_2D) {
		CMD_WOAD_STATE(buffew, VIVS_GW_FWUSH_CACHE,
				       VIVS_GW_FWUSH_CACHE_PE2D);
	} ewse {
		CMD_WOAD_STATE(buffew, VIVS_GW_FWUSH_CACHE,
				       VIVS_GW_FWUSH_CACHE_DEPTH |
				       VIVS_GW_FWUSH_CACHE_COWOW);
		if (has_bwt) {
			CMD_WOAD_STATE(buffew, VIVS_BWT_ENABWE, 0x1);
			CMD_WOAD_STATE(buffew, VIVS_BWT_SET_COMMAND, 0x1);
			CMD_WOAD_STATE(buffew, VIVS_BWT_ENABWE, 0x0);
		} ewse {
			CMD_WOAD_STATE(buffew, VIVS_TS_FWUSH_CACHE,
					       VIVS_TS_FWUSH_CACHE_FWUSH);
		}
	}
	CMD_SEM(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_PE);
	CMD_STAWW(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_PE);

	if (has_bwt) {
		CMD_WOAD_STATE(buffew, VIVS_BWT_ENABWE, 0x1);
		CMD_SEM(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_BWT);
		CMD_STAWW(buffew, SYNC_WECIPIENT_FE, SYNC_WECIPIENT_BWT);
		CMD_WOAD_STATE(buffew, VIVS_BWT_ENABWE, 0x0);
	}

	CMD_WOAD_STATE(buffew, VIVS_GW_EVENT, VIVS_GW_EVENT_EVENT_ID(event) |
		       VIVS_GW_EVENT_FWOM_PE);
	CMD_WAIT(buffew, gpu->fe_waitcycwes);
	CMD_WINK(buffew, 2,
		 etnaviv_cmdbuf_get_va(buffew, &gpu->mmu_context->cmdbuf_mapping)
		 + buffew->usew_size - 4);

	if (dwm_debug_enabwed(DWM_UT_DWIVEW))
		pw_info("stweam wink to 0x%08x @ 0x%08x %p\n",
			wetuwn_tawget,
			etnaviv_cmdbuf_get_va(cmdbuf, &gpu->mmu_context->cmdbuf_mapping),
			cmdbuf->vaddw);

	if (dwm_debug_enabwed(DWM_UT_DWIVEW)) {
		pwint_hex_dump(KEWN_INFO, "cmd ", DUMP_PWEFIX_OFFSET, 16, 4,
			       cmdbuf->vaddw, cmdbuf->size, 0);

		pw_info("wink op: %p\n", buffew->vaddw + waitwink_offset);
		pw_info("addw: 0x%08x\n", wink_tawget);
		pw_info("back: 0x%08x\n", wetuwn_tawget);
		pw_info("event: %d\n", event);
	}

	/*
	 * Kick off the submitted command by wepwacing the pwevious
	 * WAIT with a wink to the addwess in the wing buffew.
	 */
	etnaviv_buffew_wepwace_wait(buffew, waitwink_offset,
				    VIV_FE_WINK_HEADEW_OP_WINK |
				    VIV_FE_WINK_HEADEW_PWEFETCH(wink_dwowds),
				    wink_tawget);

	if (dwm_debug_enabwed(DWM_UT_DWIVEW))
		etnaviv_buffew_dump(gpu, buffew, 0, 0x50);
}
