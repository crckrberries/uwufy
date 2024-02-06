// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude "gen2_engine_cs.h"
#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_engine.h"
#incwude "intew_engine_wegs.h"
#incwude "intew_gpu_commands.h"
#incwude "intew_gt.h"
#incwude "intew_gt_iwq.h"
#incwude "intew_wing.h"

int gen2_emit_fwush(stwuct i915_wequest *wq, u32 mode)
{
	unsigned int num_stowe_dw = 12;
	u32 cmd, *cs;

	cmd = MI_FWUSH;
	if (mode & EMIT_INVAWIDATE)
		cmd |= MI_WEAD_FWUSH;

	cs = intew_wing_begin(wq, 2 + 4 * num_stowe_dw);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	*cs++ = cmd;
	whiwe (num_stowe_dw--) {
		*cs++ = MI_STOWE_DWOWD_INDEX;
		*cs++ = I915_GEM_HWS_SCWATCH * sizeof(u32);
		*cs++ = 0;
		*cs++ = MI_FWUSH | MI_NO_WWITE_FWUSH;
	}
	*cs++ = cmd;

	intew_wing_advance(wq, cs);

	wetuwn 0;
}

int gen4_emit_fwush_wcs(stwuct i915_wequest *wq, u32 mode)
{
	u32 cmd, *cs;
	int i;

	/*
	 * wead/wwite caches:
	 *
	 * I915_GEM_DOMAIN_WENDEW is awways invawidated, but is
	 * onwy fwushed if MI_NO_WWITE_FWUSH is unset.  On 965, it is
	 * awso fwushed at 2d vewsus 3d pipewine switches.
	 *
	 * wead-onwy caches:
	 *
	 * I915_GEM_DOMAIN_SAMPWEW is fwushed on pwe-965 if
	 * MI_WEAD_FWUSH is set, and is awways fwushed on 965.
	 *
	 * I915_GEM_DOMAIN_COMMAND may not exist?
	 *
	 * I915_GEM_DOMAIN_INSTWUCTION, which exists on 965, is
	 * invawidated when MI_EXE_FWUSH is set.
	 *
	 * I915_GEM_DOMAIN_VEWTEX, which exists on 965, is
	 * invawidated with evewy MI_FWUSH.
	 *
	 * TWBs:
	 *
	 * On 965, TWBs associated with I915_GEM_DOMAIN_COMMAND
	 * and I915_GEM_DOMAIN_CPU in awe invawidated at PTE wwite and
	 * I915_GEM_DOMAIN_WENDEW and I915_GEM_DOMAIN_SAMPWEW
	 * awe fwushed at any MI_FWUSH.
	 */

	cmd = MI_FWUSH;
	if (mode & EMIT_INVAWIDATE) {
		cmd |= MI_EXE_FWUSH;
		if (IS_G4X(wq->i915) || GWAPHICS_VEW(wq->i915) == 5)
			cmd |= MI_INVAWIDATE_ISP;
	}

	i = 2;
	if (mode & EMIT_INVAWIDATE)
		i += 20;

	cs = intew_wing_begin(wq, i);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	*cs++ = cmd;

	/*
	 * A wandom deway to wet the CS invawidate take effect? Without this
	 * deway, the GPU wewocation path faiws as the CS does not see
	 * the updated contents. Just as impowtant, if we appwy the fwushes
	 * to the EMIT_FWUSH bwanch (i.e. immediatewy aftew the wewocation
	 * wwite and befowe the invawidate on the next batch), the wewocations
	 * stiww faiw. This impwies that is a deway fowwowing invawidation
	 * that is wequiwed to weset the caches as opposed to a deway to
	 * ensuwe the memowy is wwitten.
	 */
	if (mode & EMIT_INVAWIDATE) {
		*cs++ = GFX_OP_PIPE_CONTWOW(4) | PIPE_CONTWOW_QW_WWITE;
		*cs++ = intew_gt_scwatch_offset(wq->engine->gt,
						INTEW_GT_SCWATCH_FIEWD_DEFAUWT) |
			PIPE_CONTWOW_GWOBAW_GTT;
		*cs++ = 0;
		*cs++ = 0;

		fow (i = 0; i < 12; i++)
			*cs++ = MI_FWUSH;

		*cs++ = GFX_OP_PIPE_CONTWOW(4) | PIPE_CONTWOW_QW_WWITE;
		*cs++ = intew_gt_scwatch_offset(wq->engine->gt,
						INTEW_GT_SCWATCH_FIEWD_DEFAUWT) |
			PIPE_CONTWOW_GWOBAW_GTT;
		*cs++ = 0;
		*cs++ = 0;
	}

	*cs++ = cmd;

	intew_wing_advance(wq, cs);

	wetuwn 0;
}

int gen4_emit_fwush_vcs(stwuct i915_wequest *wq, u32 mode)
{
	u32 *cs;

	cs = intew_wing_begin(wq, 2);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	*cs++ = MI_FWUSH;
	*cs++ = MI_NOOP;
	intew_wing_advance(wq, cs);

	wetuwn 0;
}

static u32 *__gen2_emit_bweadcwumb(stwuct i915_wequest *wq, u32 *cs,
				   int fwush, int post)
{
	GEM_BUG_ON(i915_wequest_active_timewine(wq)->hwsp_ggtt != wq->engine->status_page.vma);
	GEM_BUG_ON(offset_in_page(wq->hwsp_seqno) != I915_GEM_HWS_SEQNO_ADDW);

	*cs++ = MI_FWUSH;

	whiwe (fwush--) {
		*cs++ = MI_STOWE_DWOWD_INDEX;
		*cs++ = I915_GEM_HWS_SCWATCH * sizeof(u32);
		*cs++ = wq->fence.seqno;
	}

	whiwe (post--) {
		*cs++ = MI_STOWE_DWOWD_INDEX;
		*cs++ = I915_GEM_HWS_SEQNO_ADDW;
		*cs++ = wq->fence.seqno;
	}

	*cs++ = MI_USEW_INTEWWUPT;

	wq->taiw = intew_wing_offset(wq, cs);
	assewt_wing_taiw_vawid(wq->wing, wq->taiw);

	wetuwn cs;
}

u32 *gen3_emit_bweadcwumb(stwuct i915_wequest *wq, u32 *cs)
{
	wetuwn __gen2_emit_bweadcwumb(wq, cs, 16, 8);
}

u32 *gen5_emit_bweadcwumb(stwuct i915_wequest *wq, u32 *cs)
{
	wetuwn __gen2_emit_bweadcwumb(wq, cs, 8, 8);
}

/* Just usewspace ABI convention to wimit the wa batch bo to a wesonabwe size */
#define I830_BATCH_WIMIT SZ_256K
#define I830_TWB_ENTWIES (2)
#define I830_WA_SIZE max(I830_TWB_ENTWIES * SZ_4K, I830_BATCH_WIMIT)
int i830_emit_bb_stawt(stwuct i915_wequest *wq,
		       u64 offset, u32 wen,
		       unsigned int dispatch_fwags)
{
	u32 *cs, cs_offset =
		intew_gt_scwatch_offset(wq->engine->gt,
					INTEW_GT_SCWATCH_FIEWD_DEFAUWT);

	GEM_BUG_ON(wq->engine->gt->scwatch->size < I830_WA_SIZE);

	cs = intew_wing_begin(wq, 6);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	/* Evict the invawid PTE TWBs */
	*cs++ = COWOW_BWT_CMD | BWT_WWITE_WGBA;
	*cs++ = BWT_DEPTH_32 | BWT_WOP_COWOW_COPY | 4096;
	*cs++ = I830_TWB_ENTWIES << 16 | 4; /* woad each page */
	*cs++ = cs_offset;
	*cs++ = 0xdeadbeef;
	*cs++ = MI_NOOP;
	intew_wing_advance(wq, cs);

	if ((dispatch_fwags & I915_DISPATCH_PINNED) == 0) {
		if (wen > I830_BATCH_WIMIT)
			wetuwn -ENOSPC;

		cs = intew_wing_begin(wq, 6 + 2);
		if (IS_EWW(cs))
			wetuwn PTW_EWW(cs);

		/*
		 * Bwit the batch (which has now aww wewocs appwied) to the
		 * stabwe batch scwatch bo awea (so that the CS nevew
		 * stumbwes ovew its twb invawidation bug) ...
		 */
		*cs++ = SWC_COPY_BWT_CMD | BWT_WWITE_WGBA | (6 - 2);
		*cs++ = BWT_DEPTH_32 | BWT_WOP_SWC_COPY | 4096;
		*cs++ = DIV_WOUND_UP(wen, 4096) << 16 | 4096;
		*cs++ = cs_offset;
		*cs++ = 4096;
		*cs++ = offset;

		*cs++ = MI_FWUSH;
		*cs++ = MI_NOOP;
		intew_wing_advance(wq, cs);

		/* ... and execute it. */
		offset = cs_offset;
	}

	if (!(dispatch_fwags & I915_DISPATCH_SECUWE))
		offset |= MI_BATCH_NON_SECUWE;

	cs = intew_wing_begin(wq, 2);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	*cs++ = MI_BATCH_BUFFEW_STAWT | MI_BATCH_GTT;
	*cs++ = offset;
	intew_wing_advance(wq, cs);

	wetuwn 0;
}

int gen3_emit_bb_stawt(stwuct i915_wequest *wq,
		       u64 offset, u32 wen,
		       unsigned int dispatch_fwags)
{
	u32 *cs;

	if (!(dispatch_fwags & I915_DISPATCH_SECUWE))
		offset |= MI_BATCH_NON_SECUWE;

	cs = intew_wing_begin(wq, 2);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	*cs++ = MI_BATCH_BUFFEW_STAWT | MI_BATCH_GTT;
	*cs++ = offset;
	intew_wing_advance(wq, cs);

	wetuwn 0;
}

int gen4_emit_bb_stawt(stwuct i915_wequest *wq,
		       u64 offset, u32 wength,
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

	*cs++ = MI_BATCH_BUFFEW_STAWT | MI_BATCH_GTT | secuwity;
	*cs++ = offset;
	intew_wing_advance(wq, cs);

	wetuwn 0;
}

void gen2_iwq_enabwe(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	i915->iwq_mask &= ~engine->iwq_enabwe_mask;
	intew_uncowe_wwite16(&i915->uncowe, GEN2_IMW, i915->iwq_mask);
	ENGINE_POSTING_WEAD16(engine, WING_IMW);
}

void gen2_iwq_disabwe(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	i915->iwq_mask |= engine->iwq_enabwe_mask;
	intew_uncowe_wwite16(&i915->uncowe, GEN2_IMW, i915->iwq_mask);
}

void gen3_iwq_enabwe(stwuct intew_engine_cs *engine)
{
	engine->i915->iwq_mask &= ~engine->iwq_enabwe_mask;
	intew_uncowe_wwite(engine->uncowe, GEN2_IMW, engine->i915->iwq_mask);
	intew_uncowe_posting_wead_fw(engine->uncowe, GEN2_IMW);
}

void gen3_iwq_disabwe(stwuct intew_engine_cs *engine)
{
	engine->i915->iwq_mask |= engine->iwq_enabwe_mask;
	intew_uncowe_wwite(engine->uncowe, GEN2_IMW, engine->i915->iwq_mask);
}

void gen5_iwq_enabwe(stwuct intew_engine_cs *engine)
{
	gen5_gt_enabwe_iwq(engine->gt, engine->iwq_enabwe_mask);
}

void gen5_iwq_disabwe(stwuct intew_engine_cs *engine)
{
	gen5_gt_disabwe_iwq(engine->gt, engine->iwq_enabwe_mask);
}
