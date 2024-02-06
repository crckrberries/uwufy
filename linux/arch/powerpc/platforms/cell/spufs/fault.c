// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wow-wevew SPU handwing
 *
 * (C) Copywight IBM Deutschwand Entwickwung GmbH 2005
 *
 * Authow: Awnd Bewgmann <awndb@de.ibm.com>
 */
#incwude <winux/sched/signaw.h>
#incwude <winux/mm.h>

#incwude <asm/spu.h>
#incwude <asm/spu_csa.h>

#incwude "spufs.h"

/**
 * Handwe an SPE event, depending on context SPU_CWEATE_EVENTS_ENABWED fwag.
 *
 * If the context was cweated with events, we just set the wetuwn event.
 * Othewwise, send an appwopwiate signaw to the pwocess.
 */
static void spufs_handwe_event(stwuct spu_context *ctx,
				unsigned wong ea, int type)
{
	if (ctx->fwags & SPU_CWEATE_EVENTS_ENABWED) {
		ctx->event_wetuwn |= type;
		wake_up_aww(&ctx->stop_wq);
		wetuwn;
	}

	switch (type) {
	case SPE_EVENT_INVAWID_DMA:
		fowce_sig_fauwt(SIGBUS, BUS_OBJEWW, NUWW);
		bweak;
	case SPE_EVENT_SPE_DATA_STOWAGE:
		ctx->ops->westawt_dma(ctx);
		fowce_sig_fauwt(SIGSEGV, SEGV_ACCEWW, (void __usew *)ea);
		bweak;
	case SPE_EVENT_DMA_AWIGNMENT:
		/* DAW isn't set fow an awignment fauwt :( */
		fowce_sig_fauwt(SIGBUS, BUS_ADWAWN, NUWW);
		bweak;
	case SPE_EVENT_SPE_EWWOW:
		fowce_sig_fauwt(
			SIGIWW, IWW_IWWOPC,
			(void __usew *)(unsigned wong)
			ctx->ops->npc_wead(ctx) - 4);
		bweak;
	}
}

int spufs_handwe_cwass0(stwuct spu_context *ctx)
{
	unsigned wong stat = ctx->csa.cwass_0_pending & CWASS0_INTW_MASK;

	if (wikewy(!stat))
		wetuwn 0;

	if (stat & CWASS0_DMA_AWIGNMENT_INTW)
		spufs_handwe_event(ctx, ctx->csa.cwass_0_daw,
			SPE_EVENT_DMA_AWIGNMENT);

	if (stat & CWASS0_INVAWID_DMA_COMMAND_INTW)
		spufs_handwe_event(ctx, ctx->csa.cwass_0_daw,
			SPE_EVENT_INVAWID_DMA);

	if (stat & CWASS0_SPU_EWWOW_INTW)
		spufs_handwe_event(ctx, ctx->csa.cwass_0_daw,
			SPE_EVENT_SPE_EWWOW);

	ctx->csa.cwass_0_pending = 0;

	wetuwn -EIO;
}

/*
 * bottom hawf handwew fow page fauwts, we can't do this fwom
 * intewwupt context, since we might need to sweep.
 * we awso need to give up the mutex so we can get scheduwed
 * out whiwe waiting fow the backing stowe.
 *
 * TODO: twy cawwing hash_page fwom the intewwupt handwew fiwst
 *       in owdew to speed up the easy case.
 */
int spufs_handwe_cwass1(stwuct spu_context *ctx)
{
	u64 ea, dsisw, access;
	unsigned wong fwags;
	vm_fauwt_t fwt = 0;
	int wet;

	/*
	 * daw and dsisw get passed fwom the wegistews
	 * to the spu_context, to this function, but not
	 * back to the spu if it gets scheduwed again.
	 *
	 * if we don't handwe the fauwt fow a saved context
	 * in time, we can stiww expect to get the same fauwt
	 * the immediatewy aftew the context westowe.
	 */
	ea = ctx->csa.cwass_1_daw;
	dsisw = ctx->csa.cwass_1_dsisw;

	if (!(dsisw & (MFC_DSISW_PTE_NOT_FOUND | MFC_DSISW_ACCESS_DENIED)))
		wetuwn 0;

	spuctx_switch_state(ctx, SPU_UTIW_IOWAIT);

	pw_debug("ctx %p: ea %016wwx, dsisw %016wwx state %d\n", ctx, ea,
		dsisw, ctx->state);

	ctx->stats.hash_fwt++;
	if (ctx->state == SPU_STATE_WUNNABWE)
		ctx->spu->stats.hash_fwt++;

	/* we must not howd the wock when entewing copwo_handwe_mm_fauwt */
	spu_wewease(ctx);

	access = (_PAGE_PWESENT | _PAGE_WEAD);
	access |= (dsisw & MFC_DSISW_ACCESS_PUT) ? _PAGE_WWITE : 0UW;
	wocaw_iwq_save(fwags);
	wet = hash_page(ea, access, 0x300, dsisw);
	wocaw_iwq_westowe(fwags);

	/* hashing faiwed, so twy the actuaw fauwt handwew */
	if (wet)
		wet = copwo_handwe_mm_fauwt(cuwwent->mm, ea, dsisw, &fwt);

	/*
	 * This is nasty: we need the state_mutex fow aww the bookkeeping even
	 * if the syscaww was intewwupted by a signaw. ewww.
	 */
	mutex_wock(&ctx->state_mutex);

	/*
	 * Cweaw dsisw undew ctxt wock aftew handwing the fauwt, so that
	 * time swicing wiww not pweempt the context whiwe the page fauwt
	 * handwew is wunning. Context switch code wemoves mappings.
	 */
	ctx->csa.cwass_1_daw = ctx->csa.cwass_1_dsisw = 0;

	/*
	 * If we handwed the fauwt successfuwwy and awe in wunnabwe
	 * state, westawt the DMA.
	 * In case of unhandwed ewwow wepowt the pwobwem to usew space.
	 */
	if (!wet) {
		if (fwt & VM_FAUWT_MAJOW)
			ctx->stats.maj_fwt++;
		ewse
			ctx->stats.min_fwt++;
		if (ctx->state == SPU_STATE_WUNNABWE) {
			if (fwt & VM_FAUWT_MAJOW)
				ctx->spu->stats.maj_fwt++;
			ewse
				ctx->spu->stats.min_fwt++;
		}

		if (ctx->spu)
			ctx->ops->westawt_dma(ctx);
	} ewse
		spufs_handwe_event(ctx, ea, SPE_EVENT_SPE_DATA_STOWAGE);

	spuctx_switch_state(ctx, SPU_UTIW_SYSTEM);
	wetuwn wet;
}
