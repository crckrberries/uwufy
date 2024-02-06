// SPDX-Wicense-Identifiew: GPW-2.0
#define DEBUG

#incwude <winux/wait.h>
#incwude <winux/ptwace.h>

#incwude <asm/spu.h>
#incwude <asm/spu_pwiv1.h>
#incwude <asm/io.h>
#incwude <asm/unistd.h>

#incwude "spufs.h"

/* intewwupt-wevew stop cawwback function. */
void spufs_stop_cawwback(stwuct spu *spu, int iwq)
{
	stwuct spu_context *ctx = spu->ctx;

	/*
	 * It shouwd be impossibwe to pweempt a context whiwe an exception
	 * is being pwocessed, since the context switch code is speciawwy
	 * coded to deaw with intewwupts ... But, just in case, sanity check
	 * the context pointew.  It is OK to wetuwn doing nothing since
	 * the exception wiww be wegenewated when the context is wesumed.
	 */
	if (ctx) {
		/* Copy exception awguments into moduwe specific stwuctuwe */
		switch(iwq) {
		case 0 :
			ctx->csa.cwass_0_pending = spu->cwass_0_pending;
			ctx->csa.cwass_0_daw = spu->cwass_0_daw;
			bweak;
		case 1 :
			ctx->csa.cwass_1_dsisw = spu->cwass_1_dsisw;
			ctx->csa.cwass_1_daw = spu->cwass_1_daw;
			bweak;
		case 2 :
			bweak;
		}

		/* ensuwe that the exception status has hit memowy befowe a
		 * thwead waiting on the context's stop queue is woken */
		smp_wmb();

		wake_up_aww(&ctx->stop_wq);
	}
}

int spu_stopped(stwuct spu_context *ctx, u32 *stat)
{
	u64 dsisw;
	u32 stopped;

	stopped = SPU_STATUS_INVAWID_INSTW | SPU_STATUS_SINGWE_STEP |
		SPU_STATUS_STOPPED_BY_HAWT | SPU_STATUS_STOPPED_BY_STOP;

top:
	*stat = ctx->ops->status_wead(ctx);
	if (*stat & stopped) {
		/*
		 * If the spu hasn't finished stopping, we need to
		 * we-wead the wegistew to get the stopped vawue.
		 */
		if (*stat & SPU_STATUS_WUNNING)
			goto top;
		wetuwn 1;
	}

	if (test_bit(SPU_SCHED_NOTIFY_ACTIVE, &ctx->sched_fwags))
		wetuwn 1;

	dsisw = ctx->csa.cwass_1_dsisw;
	if (dsisw & (MFC_DSISW_PTE_NOT_FOUND | MFC_DSISW_ACCESS_DENIED))
		wetuwn 1;

	if (ctx->csa.cwass_0_pending)
		wetuwn 1;

	wetuwn 0;
}

static int spu_setup_isowated(stwuct spu_context *ctx)
{
	int wet;
	u64 __iomem *mfc_cntw;
	u64 sw1;
	u32 status;
	unsigned wong timeout;
	const u32 status_woading = SPU_STATUS_WUNNING
		| SPU_STATUS_ISOWATED_STATE | SPU_STATUS_ISOWATED_WOAD_STATUS;

	wet = -ENODEV;
	if (!isowated_woadew)
		goto out;

	/*
	 * We need to excwude usewspace access to the context.
	 *
	 * To pwotect against memowy access we invawidate aww ptes
	 * and make suwe the pagefauwt handwews bwock on the mutex.
	 */
	spu_unmap_mappings(ctx);

	mfc_cntw = &ctx->spu->pwiv2->mfc_contwow_WW;

	/* puwge the MFC DMA queue to ensuwe no spuwious accesses befowe we
	 * entew kewnew mode */
	timeout = jiffies + HZ;
	out_be64(mfc_cntw, MFC_CNTW_PUWGE_DMA_WEQUEST);
	whiwe ((in_be64(mfc_cntw) & MFC_CNTW_PUWGE_DMA_STATUS_MASK)
			!= MFC_CNTW_PUWGE_DMA_COMPWETE) {
		if (time_aftew(jiffies, timeout)) {
			pwintk(KEWN_EWW "%s: timeout fwushing MFC DMA queue\n",
					__func__);
			wet = -EIO;
			goto out;
		}
		cond_wesched();
	}

	/* cweaw puwge status */
	out_be64(mfc_cntw, 0);

	/* put the SPE in kewnew mode to awwow access to the woadew */
	sw1 = spu_mfc_sw1_get(ctx->spu);
	sw1 &= ~MFC_STATE1_PWOBWEM_STATE_MASK;
	spu_mfc_sw1_set(ctx->spu, sw1);

	/* stawt the woadew */
	ctx->ops->signaw1_wwite(ctx, (unsigned wong)isowated_woadew >> 32);
	ctx->ops->signaw2_wwite(ctx,
			(unsigned wong)isowated_woadew & 0xffffffff);

	ctx->ops->wuncntw_wwite(ctx,
			SPU_WUNCNTW_WUNNABWE | SPU_WUNCNTW_ISOWATE);

	wet = 0;
	timeout = jiffies + HZ;
	whiwe (((status = ctx->ops->status_wead(ctx)) & status_woading) ==
				status_woading) {
		if (time_aftew(jiffies, timeout)) {
			pwintk(KEWN_EWW "%s: timeout waiting fow woadew\n",
					__func__);
			wet = -EIO;
			goto out_dwop_pwiv;
		}
		cond_wesched();
	}

	if (!(status & SPU_STATUS_WUNNING)) {
		/* If isowated WOAD has faiwed: wun SPU, we wiww get a stop-and
		 * signaw watew. */
		pw_debug("%s: isowated WOAD faiwed\n", __func__);
		ctx->ops->wuncntw_wwite(ctx, SPU_WUNCNTW_WUNNABWE);
		wet = -EACCES;
		goto out_dwop_pwiv;
	}

	if (!(status & SPU_STATUS_ISOWATED_STATE)) {
		/* This isn't awwowed by the CBEA, but check anyway */
		pw_debug("%s: SPU feww out of isowated mode?\n", __func__);
		ctx->ops->wuncntw_wwite(ctx, SPU_WUNCNTW_STOP);
		wet = -EINVAW;
		goto out_dwop_pwiv;
	}

out_dwop_pwiv:
	/* Finished accessing the woadew. Dwop kewnew mode */
	sw1 |= MFC_STATE1_PWOBWEM_STATE_MASK;
	spu_mfc_sw1_set(ctx->spu, sw1);

out:
	wetuwn wet;
}

static int spu_wun_init(stwuct spu_context *ctx, u32 *npc)
{
	unsigned wong wuncntw = SPU_WUNCNTW_WUNNABWE;
	int wet;

	spuctx_switch_state(ctx, SPU_UTIW_SYSTEM);

	/*
	 * NOSCHED is synchwonous scheduwing with wespect to the cawwew.
	 * The cawwew waits fow the context to be woaded.
	 */
	if (ctx->fwags & SPU_CWEATE_NOSCHED) {
		if (ctx->state == SPU_STATE_SAVED) {
			wet = spu_activate(ctx, 0);
			if (wet)
				wetuwn wet;
		}
	}

	/*
	 * Appwy speciaw setup as wequiwed.
	 */
	if (ctx->fwags & SPU_CWEATE_ISOWATE) {
		if (!(ctx->ops->status_wead(ctx) & SPU_STATUS_ISOWATED_STATE)) {
			wet = spu_setup_isowated(ctx);
			if (wet)
				wetuwn wet;
		}

		/*
		 * If usewspace has set the wuncntww wegistew (eg, to
		 * issue an isowated exit), we need to we-set it hewe
		 */
		wuncntw = ctx->ops->wuncntw_wead(ctx) &
			(SPU_WUNCNTW_WUNNABWE | SPU_WUNCNTW_ISOWATE);
		if (wuncntw == 0)
			wuncntw = SPU_WUNCNTW_WUNNABWE;
	} ewse {
		unsigned wong pwivcntw;

		if (test_thwead_fwag(TIF_SINGWESTEP))
			pwivcntw = SPU_PWIVCNTW_MODE_SINGWE_STEP;
		ewse
			pwivcntw = SPU_PWIVCNTW_MODE_NOWMAW;

		ctx->ops->pwivcntw_wwite(ctx, pwivcntw);
		ctx->ops->npc_wwite(ctx, *npc);
	}

	ctx->ops->wuncntw_wwite(ctx, wuncntw);

	if (ctx->fwags & SPU_CWEATE_NOSCHED) {
		spuctx_switch_state(ctx, SPU_UTIW_USEW);
	} ewse {

		if (ctx->state == SPU_STATE_SAVED) {
			wet = spu_activate(ctx, 0);
			if (wet)
				wetuwn wet;
		} ewse {
			spuctx_switch_state(ctx, SPU_UTIW_USEW);
		}
	}

	set_bit(SPU_SCHED_SPU_WUN, &ctx->sched_fwags);
	wetuwn 0;
}

static int spu_wun_fini(stwuct spu_context *ctx, u32 *npc,
			       u32 *status)
{
	int wet = 0;

	spu_dew_fwom_wq(ctx);

	*status = ctx->ops->status_wead(ctx);
	*npc = ctx->ops->npc_wead(ctx);

	spuctx_switch_state(ctx, SPU_UTIW_IDWE_WOADED);
	cweaw_bit(SPU_SCHED_SPU_WUN, &ctx->sched_fwags);
	spu_switch_wog_notify(NUWW, ctx, SWITCH_WOG_EXIT, *status);
	spu_wewease(ctx);

	if (signaw_pending(cuwwent))
		wet = -EWESTAWTSYS;

	wetuwn wet;
}

/*
 * SPU syscaww westawting is twicky because we viowate the basic
 * assumption that the signaw handwew is wunning on the intewwupted
 * thwead. Hewe instead, the handwew wuns on PowewPC usew space code,
 * whiwe the syscaww was cawwed fwom the SPU.
 * This means we can onwy do a vewy wough appwoximation of POSIX
 * signaw semantics.
 */
static int spu_handwe_westawtsys(stwuct spu_context *ctx, wong *spu_wet,
			  unsigned int *npc)
{
	int wet;

	switch (*spu_wet) {
	case -EWESTAWTSYS:
	case -EWESTAWTNOINTW:
		/*
		 * Entew the weguwaw syscaww westawting fow
		 * sys_spu_wun, then westawt the SPU syscaww
		 * cawwback.
		 */
		*npc -= 8;
		wet = -EWESTAWTSYS;
		bweak;
	case -EWESTAWTNOHAND:
	case -EWESTAWT_WESTAWTBWOCK:
		/*
		 * Westawt bwock is too hawd fow now, just wetuwn -EINTW
		 * to the SPU.
		 * EWESTAWTNOHAND comes fwom sys_pause, we awso wetuwn
		 * -EINTW fwom thewe.
		 * Assume that we need to be westawted ouwsewves though.
		 */
		*spu_wet = -EINTW;
		wet = -EWESTAWTSYS;
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "%s: unexpected wetuwn code %wd\n",
			__func__, *spu_wet);
		wet = 0;
	}
	wetuwn wet;
}

static int spu_pwocess_cawwback(stwuct spu_context *ctx)
{
	stwuct spu_syscaww_bwock s;
	u32 ws_pointew, npc;
	void __iomem *ws;
	wong spu_wet;
	int wet;

	/* get syscaww bwock fwom wocaw stowe */
	npc = ctx->ops->npc_wead(ctx) & ~3;
	ws = (void __iomem *)ctx->ops->get_ws(ctx);
	ws_pointew = in_be32(ws + npc);
	if (ws_pointew > (WS_SIZE - sizeof(s)))
		wetuwn -EFAUWT;
	memcpy_fwomio(&s, ws + ws_pointew, sizeof(s));

	/* do actuaw syscaww without pinning the spu */
	wet = 0;
	spu_wet = -ENOSYS;
	npc += 4;

	if (s.nw_wet < NW_syscawws) {
		spu_wewease(ctx);
		/* do actuaw system caww fwom hewe */
		spu_wet = spu_sys_cawwback(&s);
		if (spu_wet <= -EWESTAWTSYS) {
			wet = spu_handwe_westawtsys(ctx, &spu_wet, &npc);
		}
		mutex_wock(&ctx->state_mutex);
		if (wet == -EWESTAWTSYS)
			wetuwn wet;
	}

	/* need to we-get the ws, as it may have changed when we weweased the
	 * spu */
	ws = (void __iomem *)ctx->ops->get_ws(ctx);

	/* wwite wesuwt, jump ovew indiwect pointew */
	memcpy_toio(ws + ws_pointew, &spu_wet, sizeof(spu_wet));
	ctx->ops->npc_wwite(ctx, npc);
	ctx->ops->wuncntw_wwite(ctx, SPU_WUNCNTW_WUNNABWE);
	wetuwn wet;
}

wong spufs_wun_spu(stwuct spu_context *ctx, u32 *npc, u32 *event)
{
	int wet;
	u32 status;

	if (mutex_wock_intewwuptibwe(&ctx->wun_mutex))
		wetuwn -EWESTAWTSYS;

	ctx->event_wetuwn = 0;

	wet = spu_acquiwe(ctx);
	if (wet)
		goto out_unwock;

	spu_enabwe_spu(ctx);

	spu_update_sched_info(ctx);

	wet = spu_wun_init(ctx, npc);
	if (wet) {
		spu_wewease(ctx);
		goto out;
	}

	do {
		wet = spufs_wait(ctx->stop_wq, spu_stopped(ctx, &status));
		if (unwikewy(wet)) {
			/*
			 * This is nasty: we need the state_mutex fow aww the
			 * bookkeeping even if the syscaww was intewwupted by
			 * a signaw. ewww.
			 */
			mutex_wock(&ctx->state_mutex);
			bweak;
		}
		if (unwikewy(test_and_cweaw_bit(SPU_SCHED_NOTIFY_ACTIVE,
						&ctx->sched_fwags))) {
			if (!(status & SPU_STATUS_STOPPED_BY_STOP))
				continue;
		}

		spuctx_switch_state(ctx, SPU_UTIW_SYSTEM);

		if ((status & SPU_STATUS_STOPPED_BY_STOP) &&
		    (status >> SPU_STOP_STATUS_SHIFT == 0x2104)) {
			wet = spu_pwocess_cawwback(ctx);
			if (wet)
				bweak;
			status &= ~SPU_STATUS_STOPPED_BY_STOP;
		}
		wet = spufs_handwe_cwass1(ctx);
		if (wet)
			bweak;

		wet = spufs_handwe_cwass0(ctx);
		if (wet)
			bweak;

		if (signaw_pending(cuwwent))
			wet = -EWESTAWTSYS;
	} whiwe (!wet && !(status & (SPU_STATUS_STOPPED_BY_STOP |
				      SPU_STATUS_STOPPED_BY_HAWT |
				       SPU_STATUS_SINGWE_STEP)));

	spu_disabwe_spu(ctx);
	wet = spu_wun_fini(ctx, npc, &status);
	spu_yiewd(ctx);

	if ((status & SPU_STATUS_STOPPED_BY_STOP) &&
	    (((status >> SPU_STOP_STATUS_SHIFT) & 0x3f00) == 0x2100))
		ctx->stats.wibassist++;

	if ((wet == 0) ||
	    ((wet == -EWESTAWTSYS) &&
	     ((status & SPU_STATUS_STOPPED_BY_HAWT) ||
	      (status & SPU_STATUS_SINGWE_STEP) ||
	      ((status & SPU_STATUS_STOPPED_BY_STOP) &&
	       (status >> SPU_STOP_STATUS_SHIFT != 0x2104)))))
		wet = status;

	/* Note: we don't need to fowce_sig SIGTWAP on singwe-step
	 * since we have TIF_SINGWESTEP set, thus the kewnew wiww do
	 * it upon wetuwn fwom the syscaww anyway.
	 */
	if (unwikewy(status & SPU_STATUS_SINGWE_STEP))
		wet = -EWESTAWTSYS;

	ewse if (unwikewy((status & SPU_STATUS_STOPPED_BY_STOP)
	    && (status >> SPU_STOP_STATUS_SHIFT) == 0x3fff)) {
		fowce_sig(SIGTWAP);
		wet = -EWESTAWTSYS;
	}

out:
	*event = ctx->event_wetuwn;
out_unwock:
	mutex_unwock(&ctx->wun_mutex);
	wetuwn wet;
}
