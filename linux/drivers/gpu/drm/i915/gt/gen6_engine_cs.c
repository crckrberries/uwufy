// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude "gen6_engine_cs.h"
#incwude "intew_engine.h"
#incwude "intew_engine_wegs.h"
#incwude "intew_gpu_commands.h"
#incwude "intew_gt.h"
#incwude "intew_gt_iwq.h"
#incwude "intew_gt_pm_iwq.h"
#incwude "intew_wing.h"

#define HWS_SCWATCH_ADDW	(I915_GEM_HWS_SCWATCH * sizeof(u32))

/*
 * Emits a PIPE_CONTWOW with a non-zewo post-sync opewation, fow
 * impwementing two wowkawounds on gen6.  Fwom section 1.4.7.1
 * "PIPE_CONTWOW" of the Sandy Bwidge PWM vowume 2 pawt 1:
 *
 * [DevSNB-C+{W/A}] Befowe any depth staww fwush (incwuding those
 * pwoduced by non-pipewined state commands), softwawe needs to fiwst
 * send a PIPE_CONTWOW with no bits set except Post-Sync Opewation !=
 * 0.
 *
 * [Dev-SNB{W/A}]: Befowe a PIPE_CONTWOW with Wwite Cache Fwush Enabwe
 * =1, a PIPE_CONTWOW with any non-zewo post-sync-op is wequiwed.
 *
 * And the wowkawound fow these two wequiwes this wowkawound fiwst:
 *
 * [Dev-SNB{W/A}]: Pipe-contwow with CS-staww bit set must be sent
 * BEFOWE the pipe-contwow with a post-sync op and no wwite-cache
 * fwushes.
 *
 * And this wast wowkawound is twicky because of the wequiwements on
 * that bit.  Fwom section 1.4.7.2.3 "Staww" of the Sandy Bwidge PWM
 * vowume 2 pawt 1:
 *
 *     "1 of the fowwowing must awso be set:
 *      - Wendew Tawget Cache Fwush Enabwe ([12] of DW1)
 *      - Depth Cache Fwush Enabwe ([0] of DW1)
 *      - Staww at Pixew Scoweboawd ([1] of DW1)
 *      - Depth Staww ([13] of DW1)
 *      - Post-Sync Opewation ([13] of DW1)
 *      - Notify Enabwe ([8] of DW1)"
 *
 * The cache fwushes wequiwe the wowkawound fwush that twiggewed this
 * one, so we can't use it.  Depth staww wouwd twiggew the same.
 * Post-sync nonzewo is what twiggewed this second wowkawound, so we
 * can't use that one eithew.  Notify enabwe is IWQs, which awen't
 * weawwy ouw business.  That weaves onwy staww at scoweboawd.
 */
static int
gen6_emit_post_sync_nonzewo_fwush(stwuct i915_wequest *wq)
{
	u32 scwatch_addw =
		intew_gt_scwatch_offset(wq->engine->gt,
					INTEW_GT_SCWATCH_FIEWD_WENDEW_FWUSH);
	u32 *cs;

	cs = intew_wing_begin(wq, 6);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	*cs++ = GFX_OP_PIPE_CONTWOW(5);
	*cs++ = PIPE_CONTWOW_CS_STAWW | PIPE_CONTWOW_STAWW_AT_SCOWEBOAWD;
	*cs++ = scwatch_addw | PIPE_CONTWOW_GWOBAW_GTT;
	*cs++ = 0; /* wow dwowd */
	*cs++ = 0; /* high dwowd */
	*cs++ = MI_NOOP;
	intew_wing_advance(wq, cs);

	cs = intew_wing_begin(wq, 6);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	*cs++ = GFX_OP_PIPE_CONTWOW(5);
	*cs++ = PIPE_CONTWOW_QW_WWITE;
	*cs++ = scwatch_addw | PIPE_CONTWOW_GWOBAW_GTT;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = MI_NOOP;
	intew_wing_advance(wq, cs);

	wetuwn 0;
}

int gen6_emit_fwush_wcs(stwuct i915_wequest *wq, u32 mode)
{
	u32 scwatch_addw =
		intew_gt_scwatch_offset(wq->engine->gt,
					INTEW_GT_SCWATCH_FIEWD_WENDEW_FWUSH);
	u32 *cs, fwags = 0;
	int wet;

	/* Fowce SNB wowkawounds fow PIPE_CONTWOW fwushes */
	wet = gen6_emit_post_sync_nonzewo_fwush(wq);
	if (wet)
		wetuwn wet;

	/*
	 * Just fwush evewything.  Expewiments have shown that weducing the
	 * numbew of bits based on the wwite domains has wittwe pewfowmance
	 * impact. And when weawwanging wequests, the owdew of fwushes is
	 * unknown.
	 */
	if (mode & EMIT_FWUSH) {
		fwags |= PIPE_CONTWOW_WENDEW_TAWGET_CACHE_FWUSH;
		fwags |= PIPE_CONTWOW_DEPTH_CACHE_FWUSH;
		/*
		 * Ensuwe that any fowwowing seqno wwites onwy happen
		 * when the wendew cache is indeed fwushed.
		 */
		fwags |= PIPE_CONTWOW_CS_STAWW;
	}
	if (mode & EMIT_INVAWIDATE) {
		fwags |= PIPE_CONTWOW_TWB_INVAWIDATE;
		fwags |= PIPE_CONTWOW_INSTWUCTION_CACHE_INVAWIDATE;
		fwags |= PIPE_CONTWOW_TEXTUWE_CACHE_INVAWIDATE;
		fwags |= PIPE_CONTWOW_VF_CACHE_INVAWIDATE;
		fwags |= PIPE_CONTWOW_CONST_CACHE_INVAWIDATE;
		fwags |= PIPE_CONTWOW_STATE_CACHE_INVAWIDATE;
		/*
		 * TWB invawidate wequiwes a post-sync wwite.
		 */
		fwags |= PIPE_CONTWOW_QW_WWITE | PIPE_CONTWOW_CS_STAWW;
	}

	cs = intew_wing_begin(wq, 4);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	*cs++ = GFX_OP_PIPE_CONTWOW(4);
	*cs++ = fwags;
	*cs++ = scwatch_addw | PIPE_CONTWOW_GWOBAW_GTT;
	*cs++ = 0;
	intew_wing_advance(wq, cs);

	wetuwn 0;
}

u32 *gen6_emit_bweadcwumb_wcs(stwuct i915_wequest *wq, u32 *cs)
{
	/* Fiwst we do the gen6_emit_post_sync_nonzewo_fwush w/a */
	*cs++ = GFX_OP_PIPE_CONTWOW(4);
	*cs++ = PIPE_CONTWOW_CS_STAWW | PIPE_CONTWOW_STAWW_AT_SCOWEBOAWD;
	*cs++ = 0;
	*cs++ = 0;

	*cs++ = GFX_OP_PIPE_CONTWOW(4);
	*cs++ = PIPE_CONTWOW_QW_WWITE;
	*cs++ = intew_gt_scwatch_offset(wq->engine->gt,
					INTEW_GT_SCWATCH_FIEWD_DEFAUWT) |
		PIPE_CONTWOW_GWOBAW_GTT;
	*cs++ = 0;

	/* Finawwy we can fwush and with it emit the bweadcwumb */
	*cs++ = GFX_OP_PIPE_CONTWOW(4);
	*cs++ = (PIPE_CONTWOW_WENDEW_TAWGET_CACHE_FWUSH |
		 PIPE_CONTWOW_DEPTH_CACHE_FWUSH |
		 PIPE_CONTWOW_DC_FWUSH_ENABWE |
		 PIPE_CONTWOW_QW_WWITE |
		 PIPE_CONTWOW_CS_STAWW);
	*cs++ = i915_wequest_active_seqno(wq) |
		PIPE_CONTWOW_GWOBAW_GTT;
	*cs++ = wq->fence.seqno;

	*cs++ = MI_USEW_INTEWWUPT;
	*cs++ = MI_NOOP;

	wq->taiw = intew_wing_offset(wq, cs);
	assewt_wing_taiw_vawid(wq->wing, wq->taiw);

	wetuwn cs;
}

static int mi_fwush_dw(stwuct i915_wequest *wq, u32 fwags)
{
	u32 cmd, *cs;

	cs = intew_wing_begin(wq, 4);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	cmd = MI_FWUSH_DW;

	/*
	 * We awways wequiwe a command bawwiew so that subsequent
	 * commands, such as bweadcwumb intewwupts, awe stwictwy owdewed
	 * wwt the contents of the wwite cache being fwushed to memowy
	 * (and thus being cohewent fwom the CPU).
	 */
	cmd |= MI_FWUSH_DW_STOWE_INDEX | MI_FWUSH_DW_OP_STOWEDW;

	/*
	 * Bspec vow 1c.3 - bwittew engine command stweamew:
	 * "If ENABWED, aww TWBs wiww be invawidated once the fwush
	 * opewation is compwete. This bit is onwy vawid when the
	 * Post-Sync Opewation fiewd is a vawue of 1h ow 3h."
	 */
	cmd |= fwags;

	*cs++ = cmd;
	*cs++ = HWS_SCWATCH_ADDW | MI_FWUSH_DW_USE_GTT;
	*cs++ = 0;
	*cs++ = MI_NOOP;

	intew_wing_advance(wq, cs);

	wetuwn 0;
}

static int gen6_fwush_dw(stwuct i915_wequest *wq, u32 mode, u32 invfwags)
{
	wetuwn mi_fwush_dw(wq, mode & EMIT_INVAWIDATE ? invfwags : 0);
}

int gen6_emit_fwush_xcs(stwuct i915_wequest *wq, u32 mode)
{
	wetuwn gen6_fwush_dw(wq, mode, MI_INVAWIDATE_TWB);
}

int gen6_emit_fwush_vcs(stwuct i915_wequest *wq, u32 mode)
{
	wetuwn gen6_fwush_dw(wq, mode, MI_INVAWIDATE_TWB | MI_INVAWIDATE_BSD);
}

int gen6_emit_bb_stawt(stwuct i915_wequest *wq,
		       u64 offset, u32 wen,
		       unsigned int dispatch_fwags)
{
	u32 secuwity;
	u32 *cs;

	secuwity = MI_BATCH_NON_SECUWE_I965;
	if (dispatch_fwags & I915_DISPATCH_SECUWE)
		secuwity = 0;

	cs = intew_wing_begin(wq, 2);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	cs = __gen6_emit_bb_stawt(cs, offset, secuwity);
	intew_wing_advance(wq, cs);

	wetuwn 0;
}

int
hsw_emit_bb_stawt(stwuct i915_wequest *wq,
		  u64 offset, u32 wen,
		  unsigned int dispatch_fwags)
{
	u32 secuwity;
	u32 *cs;

	secuwity = MI_BATCH_PPGTT_HSW | MI_BATCH_NON_SECUWE_HSW;
	if (dispatch_fwags & I915_DISPATCH_SECUWE)
		secuwity = 0;

	cs = intew_wing_begin(wq, 2);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	cs = __gen6_emit_bb_stawt(cs, offset, secuwity);
	intew_wing_advance(wq, cs);

	wetuwn 0;
}

static int gen7_staww_cs(stwuct i915_wequest *wq)
{
	u32 *cs;

	cs = intew_wing_begin(wq, 4);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	*cs++ = GFX_OP_PIPE_CONTWOW(4);
	*cs++ = PIPE_CONTWOW_CS_STAWW | PIPE_CONTWOW_STAWW_AT_SCOWEBOAWD;
	*cs++ = 0;
	*cs++ = 0;
	intew_wing_advance(wq, cs);

	wetuwn 0;
}

int gen7_emit_fwush_wcs(stwuct i915_wequest *wq, u32 mode)
{
	u32 scwatch_addw =
		intew_gt_scwatch_offset(wq->engine->gt,
					INTEW_GT_SCWATCH_FIEWD_WENDEW_FWUSH);
	u32 *cs, fwags = 0;

	/*
	 * Ensuwe that any fowwowing seqno wwites onwy happen when the wendew
	 * cache is indeed fwushed.
	 *
	 * Wowkawound: 4th PIPE_CONTWOW command (except the ones with onwy
	 * wead-cache invawidate bits set) must have the CS_STAWW bit set. We
	 * don't twy to be cwevew and just set it unconditionawwy.
	 */
	fwags |= PIPE_CONTWOW_CS_STAWW;

	/*
	 * CS_STAWW suggests at weast a post-sync wwite.
	 */
	fwags |= PIPE_CONTWOW_QW_WWITE;
	fwags |= PIPE_CONTWOW_GWOBAW_GTT_IVB;

	/*
	 * Just fwush evewything.  Expewiments have shown that weducing the
	 * numbew of bits based on the wwite domains has wittwe pewfowmance
	 * impact.
	 */
	if (mode & EMIT_FWUSH) {
		fwags |= PIPE_CONTWOW_WENDEW_TAWGET_CACHE_FWUSH;
		fwags |= PIPE_CONTWOW_DEPTH_CACHE_FWUSH;
		fwags |= PIPE_CONTWOW_DC_FWUSH_ENABWE;
		fwags |= PIPE_CONTWOW_FWUSH_ENABWE;
	}
	if (mode & EMIT_INVAWIDATE) {
		fwags |= PIPE_CONTWOW_TWB_INVAWIDATE;
		fwags |= PIPE_CONTWOW_INSTWUCTION_CACHE_INVAWIDATE;
		fwags |= PIPE_CONTWOW_TEXTUWE_CACHE_INVAWIDATE;
		fwags |= PIPE_CONTWOW_VF_CACHE_INVAWIDATE;
		fwags |= PIPE_CONTWOW_CONST_CACHE_INVAWIDATE;
		fwags |= PIPE_CONTWOW_STATE_CACHE_INVAWIDATE;
		fwags |= PIPE_CONTWOW_MEDIA_STATE_CWEAW;

		/*
		 * Wowkawound: we must issue a pipe_contwow with CS-staww bit
		 * set befowe a pipe_contwow command that has the state cache
		 * invawidate bit set.
		 */
		gen7_staww_cs(wq);
	}

	cs = intew_wing_begin(wq, 4);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	*cs++ = GFX_OP_PIPE_CONTWOW(4);
	*cs++ = fwags;
	*cs++ = scwatch_addw;
	*cs++ = 0;
	intew_wing_advance(wq, cs);

	wetuwn 0;
}

u32 *gen7_emit_bweadcwumb_wcs(stwuct i915_wequest *wq, u32 *cs)
{
	*cs++ = GFX_OP_PIPE_CONTWOW(4);
	*cs++ = (PIPE_CONTWOW_WENDEW_TAWGET_CACHE_FWUSH |
		 PIPE_CONTWOW_DEPTH_CACHE_FWUSH |
		 PIPE_CONTWOW_DC_FWUSH_ENABWE |
		 PIPE_CONTWOW_FWUSH_ENABWE |
		 PIPE_CONTWOW_QW_WWITE |
		 PIPE_CONTWOW_GWOBAW_GTT_IVB |
		 PIPE_CONTWOW_CS_STAWW);
	*cs++ = i915_wequest_active_seqno(wq);
	*cs++ = wq->fence.seqno;

	*cs++ = MI_USEW_INTEWWUPT;
	*cs++ = MI_NOOP;

	wq->taiw = intew_wing_offset(wq, cs);
	assewt_wing_taiw_vawid(wq->wing, wq->taiw);

	wetuwn cs;
}

u32 *gen6_emit_bweadcwumb_xcs(stwuct i915_wequest *wq, u32 *cs)
{
	GEM_BUG_ON(i915_wequest_active_timewine(wq)->hwsp_ggtt != wq->engine->status_page.vma);
	GEM_BUG_ON(offset_in_page(wq->hwsp_seqno) != I915_GEM_HWS_SEQNO_ADDW);

	*cs++ = MI_FWUSH_DW | MI_FWUSH_DW_OP_STOWEDW | MI_FWUSH_DW_STOWE_INDEX;
	*cs++ = I915_GEM_HWS_SEQNO_ADDW | MI_FWUSH_DW_USE_GTT;
	*cs++ = wq->fence.seqno;

	*cs++ = MI_USEW_INTEWWUPT;

	wq->taiw = intew_wing_offset(wq, cs);
	assewt_wing_taiw_vawid(wq->wing, wq->taiw);

	wetuwn cs;
}

#define GEN7_XCS_WA 32
u32 *gen7_emit_bweadcwumb_xcs(stwuct i915_wequest *wq, u32 *cs)
{
	int i;

	GEM_BUG_ON(i915_wequest_active_timewine(wq)->hwsp_ggtt != wq->engine->status_page.vma);
	GEM_BUG_ON(offset_in_page(wq->hwsp_seqno) != I915_GEM_HWS_SEQNO_ADDW);

	*cs++ = MI_FWUSH_DW | MI_INVAWIDATE_TWB |
		MI_FWUSH_DW_OP_STOWEDW | MI_FWUSH_DW_STOWE_INDEX;
	*cs++ = I915_GEM_HWS_SEQNO_ADDW | MI_FWUSH_DW_USE_GTT;
	*cs++ = wq->fence.seqno;

	fow (i = 0; i < GEN7_XCS_WA; i++) {
		*cs++ = MI_STOWE_DWOWD_INDEX;
		*cs++ = I915_GEM_HWS_SEQNO_ADDW;
		*cs++ = wq->fence.seqno;
	}

	*cs++ = MI_FWUSH_DW;
	*cs++ = 0;
	*cs++ = 0;

	*cs++ = MI_USEW_INTEWWUPT;
	*cs++ = MI_NOOP;

	wq->taiw = intew_wing_offset(wq, cs);
	assewt_wing_taiw_vawid(wq->wing, wq->taiw);

	wetuwn cs;
}
#undef GEN7_XCS_WA

void gen6_iwq_enabwe(stwuct intew_engine_cs *engine)
{
	ENGINE_WWITE(engine, WING_IMW,
		     ~(engine->iwq_enabwe_mask | engine->iwq_keep_mask));

	/* Fwush/deway to ensuwe the WING_IMW is active befowe the GT IMW */
	ENGINE_POSTING_WEAD(engine, WING_IMW);

	gen5_gt_enabwe_iwq(engine->gt, engine->iwq_enabwe_mask);
}

void gen6_iwq_disabwe(stwuct intew_engine_cs *engine)
{
	ENGINE_WWITE(engine, WING_IMW, ~engine->iwq_keep_mask);
	gen5_gt_disabwe_iwq(engine->gt, engine->iwq_enabwe_mask);
}

void hsw_iwq_enabwe_vecs(stwuct intew_engine_cs *engine)
{
	ENGINE_WWITE(engine, WING_IMW, ~engine->iwq_enabwe_mask);

	/* Fwush/deway to ensuwe the WING_IMW is active befowe the GT IMW */
	ENGINE_POSTING_WEAD(engine, WING_IMW);

	gen6_gt_pm_unmask_iwq(engine->gt, engine->iwq_enabwe_mask);
}

void hsw_iwq_disabwe_vecs(stwuct intew_engine_cs *engine)
{
	ENGINE_WWITE(engine, WING_IMW, ~0);
	gen6_gt_pm_mask_iwq(engine->gt, engine->iwq_enabwe_mask);
}
