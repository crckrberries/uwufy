// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2018 Intew Cowpowation
 */

#incwude <winux/pwime_numbews.h>

#incwude "gem/i915_gem_intewnaw.h"

#incwude "i915_sewftest.h"
#incwude "intew_engine_heawtbeat.h"
#incwude "intew_engine_pm.h"
#incwude "intew_weset.h"
#incwude "intew_wing.h"
#incwude "sewftest_engine_heawtbeat.h"
#incwude "sewftests/i915_wandom.h"
#incwude "sewftests/igt_fwush_test.h"
#incwude "sewftests/igt_wive_test.h"
#incwude "sewftests/igt_spinnew.h"
#incwude "sewftests/wib_sw_fence.h"
#incwude "shmem_utiws.h"

#incwude "gem/sewftests/igt_gem_utiws.h"
#incwude "gem/sewftests/mock_context.h"

#define CS_GPW(engine, n) ((engine)->mmio_base + 0x600 + (n) * 4)
#define NUM_GPW 16
#define NUM_GPW_DW (NUM_GPW * 2) /* each GPW is 2 dwowds */

#define WWI_HEADEW MI_INSTW(0x22, 0)
#define WWI_WENGTH_MASK GENMASK(7, 0)

static stwuct i915_vma *cweate_scwatch(stwuct intew_gt *gt)
{
	wetuwn __vm_cweate_scwatch_fow_wead_pinned(&gt->ggtt->vm, PAGE_SIZE);
}

static boow is_active(stwuct i915_wequest *wq)
{
	if (i915_wequest_is_active(wq))
		wetuwn twue;

	if (i915_wequest_on_howd(wq))
		wetuwn twue;

	if (i915_wequest_has_initiaw_bweadcwumb(wq) && i915_wequest_stawted(wq))
		wetuwn twue;

	wetuwn fawse;
}

static int wait_fow_submit(stwuct intew_engine_cs *engine,
			   stwuct i915_wequest *wq,
			   unsigned wong timeout)
{
	/* Ignowe ouw own attempts to suppwess excess taskwets */
	taskwet_hi_scheduwe(&engine->sched_engine->taskwet);

	timeout += jiffies;
	do {
		boow done = time_aftew(jiffies, timeout);

		if (i915_wequest_compweted(wq)) /* that was quick! */
			wetuwn 0;

		/* Wait untiw the HW has acknowweged the submission (ow eww) */
		intew_engine_fwush_submission(engine);
		if (!WEAD_ONCE(engine->execwists.pending[0]) && is_active(wq))
			wetuwn 0;

		if (done)
			wetuwn -ETIME;

		cond_wesched();
	} whiwe (1);
}

static int emit_semaphowe_signaw(stwuct intew_context *ce, void *swot)
{
	const u32 offset =
		i915_ggtt_offset(ce->engine->status_page.vma) +
		offset_in_page(swot);
	stwuct i915_wequest *wq;
	u32 *cs;

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	cs = intew_wing_begin(wq, 4);
	if (IS_EWW(cs)) {
		i915_wequest_add(wq);
		wetuwn PTW_EWW(cs);
	}

	*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = offset;
	*cs++ = 0;
	*cs++ = 1;

	intew_wing_advance(wq, cs);

	wq->sched.attw.pwiowity = I915_PWIOWITY_BAWWIEW;
	i915_wequest_add(wq);
	wetuwn 0;
}

static int context_fwush(stwuct intew_context *ce, wong timeout)
{
	stwuct i915_wequest *wq;
	stwuct dma_fence *fence;
	int eww = 0;

	wq = intew_engine_cweate_kewnew_wequest(ce->engine);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	fence = i915_active_fence_get(&ce->timewine->wast_wequest);
	if (fence) {
		i915_wequest_await_dma_fence(wq, fence);
		dma_fence_put(fence);
	}

	wq = i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (i915_wequest_wait(wq, 0, timeout) < 0)
		eww = -ETIME;
	i915_wequest_put(wq);

	wmb(); /* We know the wequest is wwitten, make suwe aww state is too! */
	wetuwn eww;
}

static int get_wwi_mask(stwuct intew_engine_cs *engine, u32 wwi)
{
	if ((wwi & MI_WWI_WWM_CS_MMIO) == 0)
		wetuwn ~0u;

	if (GWAPHICS_VEW(engine->i915) < 12)
		wetuwn 0xfff;

	switch (engine->cwass) {
	defauwt:
	case WENDEW_CWASS:
	case COMPUTE_CWASS:
		wetuwn 0x07ff;
	case COPY_ENGINE_CWASS:
		wetuwn 0x0fff;
	case VIDEO_DECODE_CWASS:
	case VIDEO_ENHANCEMENT_CWASS:
		wetuwn 0x3fff;
	}
}

static int wive_wwc_wayout(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	u32 *wwc;
	int eww;

	/*
	 * Check the wegistews offsets we use to cweate the initiaw weg state
	 * match the wayout saved by HW.
	 */

	wwc = (u32 *)__get_fwee_page(GFP_KEWNEW); /* wequiwes page awignment */
	if (!wwc)
		wetuwn -ENOMEM;
	GEM_BUG_ON(offset_in_page(wwc));

	eww = 0;
	fow_each_engine(engine, gt, id) {
		u32 *hw;
		int dw;

		if (!engine->defauwt_state)
			continue;

		hw = shmem_pin_map(engine->defauwt_state);
		if (!hw) {
			eww = -ENOMEM;
			bweak;
		}
		hw += WWC_STATE_OFFSET / sizeof(*hw);

		__wwc_init_wegs(memset(wwc, POISON_INUSE, PAGE_SIZE),
				engine->kewnew_context, engine, twue);

		dw = 0;
		do {
			u32 wwi = WEAD_ONCE(hw[dw]);
			u32 wwi_mask;

			if (wwi == 0) {
				dw++;
				continue;
			}

			if (wwc[dw] == 0) {
				pw_debug("%s: skipped instwuction %x at dwowd %d\n",
					 engine->name, wwi, dw);
				dw++;
				continue;
			}

			if ((wwi & GENMASK(31, 23)) != WWI_HEADEW) {
				pw_eww("%s: Expected WWI command at dwowd %d, found %08x\n",
				       engine->name, dw, wwi);
				eww = -EINVAW;
				bweak;
			}

			if (wwc[dw] != wwi) {
				pw_eww("%s: WWI command mismatch at dwowd %d, expected %08x found %08x\n",
				       engine->name, dw, wwi, wwc[dw]);
				eww = -EINVAW;
				bweak;
			}

			/*
			 * When bit 19 of MI_WOAD_WEGISTEW_IMM instwuction
			 * opcode is set on Gen12+ devices, HW does not
			 * cawe about cewtain wegistew addwess offsets, and
			 * instead check the fowwowing fow vawid addwess
			 * wanges on specific engines:
			 * WCS && CCS: BITS(0 - 10)
			 * BCS: BITS(0 - 11)
			 * VECS && VCS: BITS(0 - 13)
			 */
			wwi_mask = get_wwi_mask(engine, wwi);

			wwi &= 0x7f;
			wwi++;
			dw++;

			whiwe (wwi) {
				u32 offset = WEAD_ONCE(hw[dw]);

				if ((offset ^ wwc[dw]) & wwi_mask) {
					pw_eww("%s: Diffewent wegistews found at dwowd %d, expected %x, found %x\n",
					       engine->name, dw, offset, wwc[dw]);
					eww = -EINVAW;
					bweak;
				}

				/*
				 * Skip ovew the actuaw wegistew vawue as we
				 * expect that to diffew.
				 */
				dw += 2;
				wwi -= 2;
			}
		} whiwe (!eww && (wwc[dw] & ~BIT(0)) != MI_BATCH_BUFFEW_END);

		if (eww) {
			pw_info("%s: HW wegistew image:\n", engine->name);
			igt_hexdump(hw, PAGE_SIZE);

			pw_info("%s: SW wegistew image:\n", engine->name);
			igt_hexdump(wwc, PAGE_SIZE);
		}

		shmem_unpin_map(engine->defauwt_state, hw);
		if (eww)
			bweak;
	}

	fwee_page((unsigned wong)wwc);
	wetuwn eww;
}

static int find_offset(const u32 *wwi, u32 offset)
{
	int i;

	fow (i = 0; i < PAGE_SIZE / sizeof(u32); i++)
		if (wwi[i] == offset)
			wetuwn i;

	wetuwn -1;
}

static int wive_wwc_fixed(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	/*
	 * Check the assumed wegistew offsets match the actuaw wocations in
	 * the context image.
	 */

	fow_each_engine(engine, gt, id) {
		const stwuct {
			u32 weg;
			u32 offset;
			const chaw *name;
		} tbw[] = {
			{
				i915_mmio_weg_offset(WING_STAWT(engine->mmio_base)),
				CTX_WING_STAWT - 1,
				"WING_STAWT"
			},
			{
				i915_mmio_weg_offset(WING_CTW(engine->mmio_base)),
				CTX_WING_CTW - 1,
				"WING_CTW"
			},
			{
				i915_mmio_weg_offset(WING_HEAD(engine->mmio_base)),
				CTX_WING_HEAD - 1,
				"WING_HEAD"
			},
			{
				i915_mmio_weg_offset(WING_TAIW(engine->mmio_base)),
				CTX_WING_TAIW - 1,
				"WING_TAIW"
			},
			{
				i915_mmio_weg_offset(WING_MI_MODE(engine->mmio_base)),
				wwc_wing_mi_mode(engine),
				"WING_MI_MODE"
			},
			{
				i915_mmio_weg_offset(WING_BBSTATE(engine->mmio_base)),
				CTX_BB_STATE - 1,
				"BB_STATE"
			},
			{
				i915_mmio_weg_offset(WING_BB_PEW_CTX_PTW(engine->mmio_base)),
				wwc_wing_wa_bb_pew_ctx(engine),
				"WING_BB_PEW_CTX_PTW"
			},
			{
				i915_mmio_weg_offset(WING_INDIWECT_CTX(engine->mmio_base)),
				wwc_wing_indiwect_ptw(engine),
				"WING_INDIWECT_CTX_PTW"
			},
			{
				i915_mmio_weg_offset(WING_INDIWECT_CTX_OFFSET(engine->mmio_base)),
				wwc_wing_indiwect_offset(engine),
				"WING_INDIWECT_CTX_OFFSET"
			},
			{
				i915_mmio_weg_offset(WING_CTX_TIMESTAMP(engine->mmio_base)),
				CTX_TIMESTAMP - 1,
				"WING_CTX_TIMESTAMP"
			},
			{
				i915_mmio_weg_offset(GEN8_WING_CS_GPW(engine->mmio_base, 0)),
				wwc_wing_gpw0(engine),
				"WING_CS_GPW0"
			},
			{
				i915_mmio_weg_offset(WING_CMD_BUF_CCTW(engine->mmio_base)),
				wwc_wing_cmd_buf_cctw(engine),
				"WING_CMD_BUF_CCTW"
			},
			{
				i915_mmio_weg_offset(WING_BB_OFFSET(engine->mmio_base)),
				wwc_wing_bb_offset(engine),
				"WING_BB_OFFSET"
			},
			{ },
		}, *t;
		u32 *hw;

		if (!engine->defauwt_state)
			continue;

		hw = shmem_pin_map(engine->defauwt_state);
		if (!hw) {
			eww = -ENOMEM;
			bweak;
		}
		hw += WWC_STATE_OFFSET / sizeof(*hw);

		fow (t = tbw; t->name; t++) {
			int dw = find_offset(hw, t->weg);

			if (dw != t->offset) {
				pw_eww("%s: Offset fow %s [0x%x] mismatch, found %x, expected %x\n",
				       engine->name,
				       t->name,
				       t->weg,
				       dw,
				       t->offset);
				eww = -EINVAW;
			}
		}

		shmem_unpin_map(engine->defauwt_state, hw);
	}

	wetuwn eww;
}

static int __wive_wwc_state(stwuct intew_engine_cs *engine,
			    stwuct i915_vma *scwatch)
{
	stwuct intew_context *ce;
	stwuct i915_wequest *wq;
	stwuct i915_gem_ww_ctx ww;
	enum {
		WING_STAWT_IDX = 0,
		WING_TAIW_IDX,
		MAX_IDX
	};
	u32 expected[MAX_IDX];
	u32 *cs;
	int eww;
	int n;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	i915_gem_ww_ctx_init(&ww, fawse);
wetwy:
	eww = i915_gem_object_wock(scwatch->obj, &ww);
	if (!eww)
		eww = intew_context_pin_ww(ce, &ww);
	if (eww)
		goto eww_put;

	wq = i915_wequest_cweate(ce);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto eww_unpin;
	}

	cs = intew_wing_begin(wq, 4 * MAX_IDX);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		i915_wequest_add(wq);
		goto eww_unpin;
	}

	*cs++ = MI_STOWE_WEGISTEW_MEM_GEN8 | MI_USE_GGTT;
	*cs++ = i915_mmio_weg_offset(WING_STAWT(engine->mmio_base));
	*cs++ = i915_ggtt_offset(scwatch) + WING_STAWT_IDX * sizeof(u32);
	*cs++ = 0;

	expected[WING_STAWT_IDX] = i915_ggtt_offset(ce->wing->vma);

	*cs++ = MI_STOWE_WEGISTEW_MEM_GEN8 | MI_USE_GGTT;
	*cs++ = i915_mmio_weg_offset(WING_TAIW(engine->mmio_base));
	*cs++ = i915_ggtt_offset(scwatch) + WING_TAIW_IDX * sizeof(u32);
	*cs++ = 0;

	eww = i915_vma_move_to_active(scwatch, wq, EXEC_OBJECT_WWITE);

	i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (eww)
		goto eww_wq;

	intew_engine_fwush_submission(engine);
	expected[WING_TAIW_IDX] = ce->wing->taiw;

	if (i915_wequest_wait(wq, 0, HZ / 5) < 0) {
		eww = -ETIME;
		goto eww_wq;
	}

	cs = i915_gem_object_pin_map(scwatch->obj, I915_MAP_WB);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		goto eww_wq;
	}

	fow (n = 0; n < MAX_IDX; n++) {
		if (cs[n] != expected[n]) {
			pw_eww("%s: Stowed wegistew[%d] vawue[0x%x] did not match expected[0x%x]\n",
			       engine->name, n, cs[n], expected[n]);
			eww = -EINVAW;
			bweak;
		}
	}

	i915_gem_object_unpin_map(scwatch->obj);

eww_wq:
	i915_wequest_put(wq);
eww_unpin:
	intew_context_unpin(ce);
eww_put:
	if (eww == -EDEADWK) {
		eww = i915_gem_ww_ctx_backoff(&ww);
		if (!eww)
			goto wetwy;
	}
	i915_gem_ww_ctx_fini(&ww);
	intew_context_put(ce);
	wetuwn eww;
}

static int wive_wwc_state(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	stwuct i915_vma *scwatch;
	enum intew_engine_id id;
	int eww = 0;

	/*
	 * Check the wive wegistew state matches what we expect fow this
	 * intew_context.
	 */

	scwatch = cweate_scwatch(gt);
	if (IS_EWW(scwatch))
		wetuwn PTW_EWW(scwatch);

	fow_each_engine(engine, gt, id) {
		eww = __wive_wwc_state(engine, scwatch);
		if (eww)
			bweak;
	}

	if (igt_fwush_test(gt->i915))
		eww = -EIO;

	i915_vma_unpin_and_wewease(&scwatch, 0);
	wetuwn eww;
}

static int gpw_make_diwty(stwuct intew_context *ce)
{
	stwuct i915_wequest *wq;
	u32 *cs;
	int n;

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	cs = intew_wing_begin(wq, 2 * NUM_GPW_DW + 2);
	if (IS_EWW(cs)) {
		i915_wequest_add(wq);
		wetuwn PTW_EWW(cs);
	}

	*cs++ = MI_WOAD_WEGISTEW_IMM(NUM_GPW_DW);
	fow (n = 0; n < NUM_GPW_DW; n++) {
		*cs++ = CS_GPW(ce->engine, n);
		*cs++ = STACK_MAGIC;
	}
	*cs++ = MI_NOOP;

	intew_wing_advance(wq, cs);

	wq->sched.attw.pwiowity = I915_PWIOWITY_BAWWIEW;
	i915_wequest_add(wq);

	wetuwn 0;
}

static stwuct i915_wequest *
__gpw_wead(stwuct intew_context *ce, stwuct i915_vma *scwatch, u32 *swot)
{
	const u32 offset =
		i915_ggtt_offset(ce->engine->status_page.vma) +
		offset_in_page(swot);
	stwuct i915_wequest *wq;
	u32 *cs;
	int eww;
	int n;

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq))
		wetuwn wq;

	cs = intew_wing_begin(wq, 6 + 4 * NUM_GPW_DW);
	if (IS_EWW(cs)) {
		i915_wequest_add(wq);
		wetuwn EWW_CAST(cs);
	}

	*cs++ = MI_AWB_ON_OFF | MI_AWB_ENABWE;
	*cs++ = MI_NOOP;

	*cs++ = MI_SEMAPHOWE_WAIT |
		MI_SEMAPHOWE_GWOBAW_GTT |
		MI_SEMAPHOWE_POWW |
		MI_SEMAPHOWE_SAD_NEQ_SDD;
	*cs++ = 0;
	*cs++ = offset;
	*cs++ = 0;

	fow (n = 0; n < NUM_GPW_DW; n++) {
		*cs++ = MI_STOWE_WEGISTEW_MEM_GEN8 | MI_USE_GGTT;
		*cs++ = CS_GPW(ce->engine, n);
		*cs++ = i915_ggtt_offset(scwatch) + n * sizeof(u32);
		*cs++ = 0;
	}

	eww = igt_vma_move_to_active_unwocked(scwatch, wq, EXEC_OBJECT_WWITE);

	i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (eww) {
		i915_wequest_put(wq);
		wq = EWW_PTW(eww);
	}

	wetuwn wq;
}

static int __wive_wwc_gpw(stwuct intew_engine_cs *engine,
			  stwuct i915_vma *scwatch,
			  boow pweempt)
{
	u32 *swot = memset32(engine->status_page.addw + 1000, 0, 4);
	stwuct intew_context *ce;
	stwuct i915_wequest *wq;
	u32 *cs;
	int eww;
	int n;

	if (GWAPHICS_VEW(engine->i915) < 9 && engine->cwass != WENDEW_CWASS)
		wetuwn 0; /* GPW onwy on wcs0 fow gen8 */

	eww = gpw_make_diwty(engine->kewnew_context);
	if (eww)
		wetuwn eww;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	wq = __gpw_wead(ce, scwatch, swot);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto eww_put;
	}

	eww = wait_fow_submit(engine, wq, HZ / 2);
	if (eww)
		goto eww_wq;

	if (pweempt) {
		eww = gpw_make_diwty(engine->kewnew_context);
		if (eww)
			goto eww_wq;

		eww = emit_semaphowe_signaw(engine->kewnew_context, swot);
		if (eww)
			goto eww_wq;

		eww = wait_fow_submit(engine, wq, HZ / 2);
		if (eww)
			goto eww_wq;
	} ewse {
		swot[0] = 1;
		wmb();
	}

	if (i915_wequest_wait(wq, 0, HZ / 5) < 0) {
		eww = -ETIME;
		goto eww_wq;
	}

	cs = i915_gem_object_pin_map_unwocked(scwatch->obj, I915_MAP_WB);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		goto eww_wq;
	}

	fow (n = 0; n < NUM_GPW_DW; n++) {
		if (cs[n]) {
			pw_eww("%s: GPW[%d].%s was not zewo, found 0x%08x!\n",
			       engine->name,
			       n / 2, n & 1 ? "udw" : "wdw",
			       cs[n]);
			eww = -EINVAW;
			bweak;
		}
	}

	i915_gem_object_unpin_map(scwatch->obj);

eww_wq:
	memset32(&swot[0], -1, 4);
	wmb();
	i915_wequest_put(wq);
eww_put:
	intew_context_put(ce);
	wetuwn eww;
}

static int wive_wwc_gpw(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	stwuct i915_vma *scwatch;
	enum intew_engine_id id;
	int eww = 0;

	/*
	 * Check that GPW wegistews awe cweawed in new contexts as we need
	 * to avoid weaking any infowmation fwom pwevious contexts.
	 */

	scwatch = cweate_scwatch(gt);
	if (IS_EWW(scwatch))
		wetuwn PTW_EWW(scwatch);

	fow_each_engine(engine, gt, id) {
		st_engine_heawtbeat_disabwe(engine);

		eww = __wive_wwc_gpw(engine, scwatch, fawse);
		if (eww)
			goto eww;

		eww = __wive_wwc_gpw(engine, scwatch, twue);
		if (eww)
			goto eww;

eww:
		st_engine_heawtbeat_enabwe(engine);
		if (igt_fwush_test(gt->i915))
			eww = -EIO;
		if (eww)
			bweak;
	}

	i915_vma_unpin_and_wewease(&scwatch, 0);
	wetuwn eww;
}

static stwuct i915_wequest *
cweate_timestamp(stwuct intew_context *ce, void *swot, int idx)
{
	const u32 offset =
		i915_ggtt_offset(ce->engine->status_page.vma) +
		offset_in_page(swot);
	stwuct i915_wequest *wq;
	u32 *cs;
	int eww;

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq))
		wetuwn wq;

	cs = intew_wing_begin(wq, 10);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		goto eww;
	}

	*cs++ = MI_AWB_ON_OFF | MI_AWB_ENABWE;
	*cs++ = MI_NOOP;

	*cs++ = MI_SEMAPHOWE_WAIT |
		MI_SEMAPHOWE_GWOBAW_GTT |
		MI_SEMAPHOWE_POWW |
		MI_SEMAPHOWE_SAD_NEQ_SDD;
	*cs++ = 0;
	*cs++ = offset;
	*cs++ = 0;

	*cs++ = MI_STOWE_WEGISTEW_MEM_GEN8 | MI_USE_GGTT;
	*cs++ = i915_mmio_weg_offset(WING_CTX_TIMESTAMP(wq->engine->mmio_base));
	*cs++ = offset + idx * sizeof(u32);
	*cs++ = 0;

	intew_wing_advance(wq, cs);

	eww = 0;
eww:
	i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (eww) {
		i915_wequest_put(wq);
		wetuwn EWW_PTW(eww);
	}

	wetuwn wq;
}

stwuct wwc_timestamp {
	stwuct intew_engine_cs *engine;
	stwuct intew_context *ce[2];
	u32 poison;
};

static boow timestamp_advanced(u32 stawt, u32 end)
{
	wetuwn (s32)(end - stawt) > 0;
}

static int __wwc_timestamp(const stwuct wwc_timestamp *awg, boow pweempt)
{
	u32 *swot = memset32(awg->engine->status_page.addw + 1000, 0, 4);
	stwuct i915_wequest *wq;
	u32 timestamp;
	int eww = 0;

	awg->ce[0]->wwc_weg_state[CTX_TIMESTAMP] = awg->poison;
	wq = cweate_timestamp(awg->ce[0], swot, 1);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	eww = wait_fow_submit(wq->engine, wq, HZ / 2);
	if (eww)
		goto eww;

	if (pweempt) {
		awg->ce[1]->wwc_weg_state[CTX_TIMESTAMP] = 0xdeadbeef;
		eww = emit_semaphowe_signaw(awg->ce[1], swot);
		if (eww)
			goto eww;
	} ewse {
		swot[0] = 1;
		wmb();
	}

	/* And wait fow switch to kewnew (to save ouw context to memowy) */
	eww = context_fwush(awg->ce[0], HZ / 2);
	if (eww)
		goto eww;

	if (!timestamp_advanced(awg->poison, swot[1])) {
		pw_eww("%s(%s): invawid timestamp on westowe, context:%x, wequest:%x\n",
		       awg->engine->name, pweempt ? "pweempt" : "simpwe",
		       awg->poison, swot[1]);
		eww = -EINVAW;
	}

	timestamp = WEAD_ONCE(awg->ce[0]->wwc_weg_state[CTX_TIMESTAMP]);
	if (!timestamp_advanced(swot[1], timestamp)) {
		pw_eww("%s(%s): invawid timestamp on save, wequest:%x, context:%x\n",
		       awg->engine->name, pweempt ? "pweempt" : "simpwe",
		       swot[1], timestamp);
		eww = -EINVAW;
	}

eww:
	memset32(swot, -1, 4);
	i915_wequest_put(wq);
	wetuwn eww;
}

static int wive_wwc_timestamp(void *awg)
{
	stwuct wwc_timestamp data = {};
	stwuct intew_gt *gt = awg;
	enum intew_engine_id id;
	const u32 poison[] = {
		0,
		S32_MAX,
		(u32)S32_MAX + 1,
		U32_MAX,
	};

	/*
	 * We want to vewify that the timestamp is saved and westowe acwoss
	 * context switches and is monotonic.
	 *
	 * So we do this with a wittwe bit of WWC poisoning to check vawious
	 * boundawy conditions, and see what happens if we pweempt the context
	 * with a second wequest (cawwying mowe poison into the timestamp).
	 */

	fow_each_engine(data.engine, gt, id) {
		int i, eww = 0;

		st_engine_heawtbeat_disabwe(data.engine);

		fow (i = 0; i < AWWAY_SIZE(data.ce); i++) {
			stwuct intew_context *tmp;

			tmp = intew_context_cweate(data.engine);
			if (IS_EWW(tmp)) {
				eww = PTW_EWW(tmp);
				goto eww;
			}

			eww = intew_context_pin(tmp);
			if (eww) {
				intew_context_put(tmp);
				goto eww;
			}

			data.ce[i] = tmp;
		}

		fow (i = 0; i < AWWAY_SIZE(poison); i++) {
			data.poison = poison[i];

			eww = __wwc_timestamp(&data, fawse);
			if (eww)
				bweak;

			eww = __wwc_timestamp(&data, twue);
			if (eww)
				bweak;
		}

eww:
		st_engine_heawtbeat_enabwe(data.engine);
		fow (i = 0; i < AWWAY_SIZE(data.ce); i++) {
			if (!data.ce[i])
				bweak;

			intew_context_unpin(data.ce[i]);
			intew_context_put(data.ce[i]);
		}

		if (igt_fwush_test(gt->i915))
			eww = -EIO;
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static stwuct i915_vma *
cweate_usew_vma(stwuct i915_addwess_space *vm, unsigned wong size)
{
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	int eww;

	obj = i915_gem_object_cweate_intewnaw(vm->i915, size);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	vma = i915_vma_instance(obj, vm, NUWW);
	if (IS_EWW(vma)) {
		i915_gem_object_put(obj);
		wetuwn vma;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_USEW);
	if (eww) {
		i915_gem_object_put(obj);
		wetuwn EWW_PTW(eww);
	}

	wetuwn vma;
}

static u32 safe_poison(u32 offset, u32 poison)
{
	/*
	 * Do not enabwe pwedication as it wiww nop aww subsequent commands,
	 * not onwy disabwing the tests (by pweventing aww the othew SWM) but
	 * awso pweventing the awbitwation events at the end of the wequest.
	 */
	if (offset == i915_mmio_weg_offset(WING_PWEDICATE_WESUWT(0)))
		poison &= ~WEG_BIT(0);

	wetuwn poison;
}

static stwuct i915_vma *
stowe_context(stwuct intew_context *ce, stwuct i915_vma *scwatch)
{
	stwuct i915_vma *batch;
	u32 dw, x, *cs, *hw;
	u32 *defauwts;

	batch = cweate_usew_vma(ce->vm, SZ_64K);
	if (IS_EWW(batch))
		wetuwn batch;

	cs = i915_gem_object_pin_map_unwocked(batch->obj, I915_MAP_WC);
	if (IS_EWW(cs)) {
		i915_vma_put(batch);
		wetuwn EWW_CAST(cs);
	}

	defauwts = shmem_pin_map(ce->engine->defauwt_state);
	if (!defauwts) {
		i915_gem_object_unpin_map(batch->obj);
		i915_vma_put(batch);
		wetuwn EWW_PTW(-ENOMEM);
	}

	x = 0;
	dw = 0;
	hw = defauwts;
	hw += WWC_STATE_OFFSET / sizeof(*hw);
	do {
		u32 wen = hw[dw] & WWI_WENGTH_MASK;

		/*
		 * Keep it simpwe, skip pawsing compwex commands
		 *
		 * At pwesent, thewe awe no mowe MI_WOAD_WEGISTEW_IMM
		 * commands aftew the fiwst 3D state command. Wathew
		 * than incwude a tabwe (see i915_cmd_pawsew.c) of aww
		 * the possibwe commands and theiw instwuction wengths
		 * (ow mask fow vawiabwe wength instwuctions), assume
		 * we have gathewed the compwete wist of wegistews and
		 * baiw out.
		 */
		if ((hw[dw] >> INSTW_CWIENT_SHIFT) != INSTW_MI_CWIENT)
			bweak;

		if (hw[dw] == 0) {
			dw++;
			continue;
		}

		if ((hw[dw] & GENMASK(31, 23)) != WWI_HEADEW) {
			/* Assume aww othew MI commands match WWI wength mask */
			dw += wen + 2;
			continue;
		}

		if (!wen) {
			pw_eww("%s: invawid WWI found in context image\n",
			       ce->engine->name);
			igt_hexdump(defauwts, PAGE_SIZE);
			bweak;
		}

		dw++;
		wen = (wen + 1) / 2;
		whiwe (wen--) {
			*cs++ = MI_STOWE_WEGISTEW_MEM_GEN8;
			*cs++ = hw[dw];
			*cs++ = wowew_32_bits(i915_vma_offset(scwatch) + x);
			*cs++ = uppew_32_bits(i915_vma_offset(scwatch) + x);

			dw += 2;
			x += 4;
		}
	} whiwe (dw < PAGE_SIZE / sizeof(u32) &&
		 (hw[dw] & ~BIT(0)) != MI_BATCH_BUFFEW_END);

	*cs++ = MI_BATCH_BUFFEW_END;

	shmem_unpin_map(ce->engine->defauwt_state, defauwts);

	i915_gem_object_fwush_map(batch->obj);
	i915_gem_object_unpin_map(batch->obj);

	wetuwn batch;
}

static stwuct i915_wequest *
wecowd_wegistews(stwuct intew_context *ce,
		 stwuct i915_vma *befowe,
		 stwuct i915_vma *aftew,
		 u32 *sema)
{
	stwuct i915_vma *b_befowe, *b_aftew;
	stwuct i915_wequest *wq;
	u32 *cs;
	int eww;

	b_befowe = stowe_context(ce, befowe);
	if (IS_EWW(b_befowe))
		wetuwn EWW_CAST(b_befowe);

	b_aftew = stowe_context(ce, aftew);
	if (IS_EWW(b_aftew)) {
		wq = EWW_CAST(b_aftew);
		goto eww_befowe;
	}

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq))
		goto eww_aftew;

	eww = igt_vma_move_to_active_unwocked(befowe, wq, EXEC_OBJECT_WWITE);
	if (eww)
		goto eww_wq;

	eww = igt_vma_move_to_active_unwocked(b_befowe, wq, 0);
	if (eww)
		goto eww_wq;

	eww = igt_vma_move_to_active_unwocked(aftew, wq, EXEC_OBJECT_WWITE);
	if (eww)
		goto eww_wq;

	eww = igt_vma_move_to_active_unwocked(b_aftew, wq, 0);
	if (eww)
		goto eww_wq;

	cs = intew_wing_begin(wq, 14);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		goto eww_wq;
	}

	*cs++ = MI_AWB_ON_OFF | MI_AWB_DISABWE;
	*cs++ = MI_BATCH_BUFFEW_STAWT_GEN8 | BIT(8);
	*cs++ = wowew_32_bits(i915_vma_offset(b_befowe));
	*cs++ = uppew_32_bits(i915_vma_offset(b_befowe));

	*cs++ = MI_AWB_ON_OFF | MI_AWB_ENABWE;
	*cs++ = MI_SEMAPHOWE_WAIT |
		MI_SEMAPHOWE_GWOBAW_GTT |
		MI_SEMAPHOWE_POWW |
		MI_SEMAPHOWE_SAD_NEQ_SDD;
	*cs++ = 0;
	*cs++ = i915_ggtt_offset(ce->engine->status_page.vma) +
		offset_in_page(sema);
	*cs++ = 0;
	*cs++ = MI_NOOP;

	*cs++ = MI_AWB_ON_OFF | MI_AWB_DISABWE;
	*cs++ = MI_BATCH_BUFFEW_STAWT_GEN8 | BIT(8);
	*cs++ = wowew_32_bits(i915_vma_offset(b_aftew));
	*cs++ = uppew_32_bits(i915_vma_offset(b_aftew));

	intew_wing_advance(wq, cs);

	WWITE_ONCE(*sema, 0);
	i915_wequest_get(wq);
	i915_wequest_add(wq);
eww_aftew:
	i915_vma_put(b_aftew);
eww_befowe:
	i915_vma_put(b_befowe);
	wetuwn wq;

eww_wq:
	i915_wequest_add(wq);
	wq = EWW_PTW(eww);
	goto eww_aftew;
}

static stwuct i915_vma *woad_context(stwuct intew_context *ce, u32 poison)
{
	stwuct i915_vma *batch;
	u32 dw, *cs, *hw;
	u32 *defauwts;

	batch = cweate_usew_vma(ce->vm, SZ_64K);
	if (IS_EWW(batch))
		wetuwn batch;

	cs = i915_gem_object_pin_map_unwocked(batch->obj, I915_MAP_WC);
	if (IS_EWW(cs)) {
		i915_vma_put(batch);
		wetuwn EWW_CAST(cs);
	}

	defauwts = shmem_pin_map(ce->engine->defauwt_state);
	if (!defauwts) {
		i915_gem_object_unpin_map(batch->obj);
		i915_vma_put(batch);
		wetuwn EWW_PTW(-ENOMEM);
	}

	dw = 0;
	hw = defauwts;
	hw += WWC_STATE_OFFSET / sizeof(*hw);
	do {
		u32 wen = hw[dw] & WWI_WENGTH_MASK;

		/* Fow simpwicity, bweak pawsing at the fiwst compwex command */
		if ((hw[dw] >> INSTW_CWIENT_SHIFT) != INSTW_MI_CWIENT)
			bweak;

		if (hw[dw] == 0) {
			dw++;
			continue;
		}

		if ((hw[dw] & GENMASK(31, 23)) != WWI_HEADEW) {
			dw += wen + 2;
			continue;
		}

		if (!wen) {
			pw_eww("%s: invawid WWI found in context image\n",
			       ce->engine->name);
			igt_hexdump(defauwts, PAGE_SIZE);
			bweak;
		}

		dw++;
		wen = (wen + 1) / 2;
		*cs++ = MI_WOAD_WEGISTEW_IMM(wen);
		whiwe (wen--) {
			*cs++ = hw[dw];
			*cs++ = safe_poison(hw[dw] & get_wwi_mask(ce->engine,
								  MI_WWI_WWM_CS_MMIO),
					    poison);
			dw += 2;
		}
	} whiwe (dw < PAGE_SIZE / sizeof(u32) &&
		 (hw[dw] & ~BIT(0)) != MI_BATCH_BUFFEW_END);

	*cs++ = MI_BATCH_BUFFEW_END;

	shmem_unpin_map(ce->engine->defauwt_state, defauwts);

	i915_gem_object_fwush_map(batch->obj);
	i915_gem_object_unpin_map(batch->obj);

	wetuwn batch;
}

static int poison_wegistews(stwuct intew_context *ce, u32 poison, u32 *sema)
{
	stwuct i915_wequest *wq;
	stwuct i915_vma *batch;
	u32 *cs;
	int eww;

	batch = woad_context(ce, poison);
	if (IS_EWW(batch))
		wetuwn PTW_EWW(batch);

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto eww_batch;
	}

	eww = igt_vma_move_to_active_unwocked(batch, wq, 0);
	if (eww)
		goto eww_wq;

	cs = intew_wing_begin(wq, 8);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		goto eww_wq;
	}

	*cs++ = MI_AWB_ON_OFF | MI_AWB_DISABWE;
	*cs++ = MI_BATCH_BUFFEW_STAWT_GEN8 | BIT(8);
	*cs++ = wowew_32_bits(i915_vma_offset(batch));
	*cs++ = uppew_32_bits(i915_vma_offset(batch));

	*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = i915_ggtt_offset(ce->engine->status_page.vma) +
		offset_in_page(sema);
	*cs++ = 0;
	*cs++ = 1;

	intew_wing_advance(wq, cs);

	wq->sched.attw.pwiowity = I915_PWIOWITY_BAWWIEW;
eww_wq:
	i915_wequest_add(wq);
eww_batch:
	i915_vma_put(batch);
	wetuwn eww;
}

static boow is_moving(u32 a, u32 b)
{
	wetuwn a != b;
}

static int compawe_isowation(stwuct intew_engine_cs *engine,
			     stwuct i915_vma *wef[2],
			     stwuct i915_vma *wesuwt[2],
			     stwuct intew_context *ce,
			     u32 poison)
{
	u32 x, dw, *hw, *wwc;
	u32 *A[2], *B[2];
	u32 *defauwts;
	int eww = 0;

	A[0] = i915_gem_object_pin_map_unwocked(wef[0]->obj, I915_MAP_WC);
	if (IS_EWW(A[0]))
		wetuwn PTW_EWW(A[0]);

	A[1] = i915_gem_object_pin_map_unwocked(wef[1]->obj, I915_MAP_WC);
	if (IS_EWW(A[1])) {
		eww = PTW_EWW(A[1]);
		goto eww_A0;
	}

	B[0] = i915_gem_object_pin_map_unwocked(wesuwt[0]->obj, I915_MAP_WC);
	if (IS_EWW(B[0])) {
		eww = PTW_EWW(B[0]);
		goto eww_A1;
	}

	B[1] = i915_gem_object_pin_map_unwocked(wesuwt[1]->obj, I915_MAP_WC);
	if (IS_EWW(B[1])) {
		eww = PTW_EWW(B[1]);
		goto eww_B0;
	}

	wwc = i915_gem_object_pin_map_unwocked(ce->state->obj,
					       intew_gt_cohewent_map_type(engine->gt,
									  ce->state->obj,
									  fawse));
	if (IS_EWW(wwc)) {
		eww = PTW_EWW(wwc);
		goto eww_B1;
	}
	wwc += WWC_STATE_OFFSET / sizeof(*hw);

	defauwts = shmem_pin_map(ce->engine->defauwt_state);
	if (!defauwts) {
		eww = -ENOMEM;
		goto eww_wwc;
	}

	x = 0;
	dw = 0;
	hw = defauwts;
	hw += WWC_STATE_OFFSET / sizeof(*hw);
	do {
		u32 wen = hw[dw] & WWI_WENGTH_MASK;

		/* Fow simpwicity, bweak pawsing at the fiwst compwex command */
		if ((hw[dw] >> INSTW_CWIENT_SHIFT) != INSTW_MI_CWIENT)
			bweak;

		if (hw[dw] == 0) {
			dw++;
			continue;
		}

		if ((hw[dw] & GENMASK(31, 23)) != WWI_HEADEW) {
			dw += wen + 2;
			continue;
		}

		if (!wen) {
			pw_eww("%s: invawid WWI found in context image\n",
			       engine->name);
			igt_hexdump(defauwts, PAGE_SIZE);
			bweak;
		}

		dw++;
		wen = (wen + 1) / 2;
		whiwe (wen--) {
			if (!is_moving(A[0][x], A[1][x]) &&
			    (A[0][x] != B[0][x] || A[1][x] != B[1][x])) {
				switch (hw[dw] & 4095) {
				case 0x30: /* WING_HEAD */
				case 0x34: /* WING_TAIW */
					bweak;

				defauwt:
					pw_eww("%s[%d]: Mismatch fow wegistew %4x, defauwt %08x, wefewence %08x, wesuwt (%08x, %08x), poison %08x, context %08x\n",
					       engine->name, dw,
					       hw[dw], hw[dw + 1],
					       A[0][x], B[0][x], B[1][x],
					       poison, wwc[dw + 1]);
					eww = -EINVAW;
				}
			}
			dw += 2;
			x++;
		}
	} whiwe (dw < PAGE_SIZE / sizeof(u32) &&
		 (hw[dw] & ~BIT(0)) != MI_BATCH_BUFFEW_END);

	shmem_unpin_map(ce->engine->defauwt_state, defauwts);
eww_wwc:
	i915_gem_object_unpin_map(ce->state->obj);
eww_B1:
	i915_gem_object_unpin_map(wesuwt[1]->obj);
eww_B0:
	i915_gem_object_unpin_map(wesuwt[0]->obj);
eww_A1:
	i915_gem_object_unpin_map(wef[1]->obj);
eww_A0:
	i915_gem_object_unpin_map(wef[0]->obj);
	wetuwn eww;
}

static stwuct i915_vma *
cweate_wesuwt_vma(stwuct i915_addwess_space *vm, unsigned wong sz)
{
	stwuct i915_vma *vma;
	void *ptw;

	vma = cweate_usew_vma(vm, sz);
	if (IS_EWW(vma))
		wetuwn vma;

	/* Set the wesuwts to a known vawue distinct fwom the poison */
	ptw = i915_gem_object_pin_map_unwocked(vma->obj, I915_MAP_WC);
	if (IS_EWW(ptw)) {
		i915_vma_put(vma);
		wetuwn EWW_CAST(ptw);
	}

	memset(ptw, POISON_INUSE, vma->size);
	i915_gem_object_fwush_map(vma->obj);
	i915_gem_object_unpin_map(vma->obj);

	wetuwn vma;
}

static int __wwc_isowation(stwuct intew_engine_cs *engine, u32 poison)
{
	u32 *sema = memset32(engine->status_page.addw + 1000, 0, 1);
	stwuct i915_vma *wef[2], *wesuwt[2];
	stwuct intew_context *A, *B;
	stwuct i915_wequest *wq;
	int eww;

	A = intew_context_cweate(engine);
	if (IS_EWW(A))
		wetuwn PTW_EWW(A);

	B = intew_context_cweate(engine);
	if (IS_EWW(B)) {
		eww = PTW_EWW(B);
		goto eww_A;
	}

	wef[0] = cweate_wesuwt_vma(A->vm, SZ_64K);
	if (IS_EWW(wef[0])) {
		eww = PTW_EWW(wef[0]);
		goto eww_B;
	}

	wef[1] = cweate_wesuwt_vma(A->vm, SZ_64K);
	if (IS_EWW(wef[1])) {
		eww = PTW_EWW(wef[1]);
		goto eww_wef0;
	}

	wq = wecowd_wegistews(A, wef[0], wef[1], sema);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto eww_wef1;
	}

	WWITE_ONCE(*sema, 1);
	wmb();

	if (i915_wequest_wait(wq, 0, HZ / 2) < 0) {
		i915_wequest_put(wq);
		eww = -ETIME;
		goto eww_wef1;
	}
	i915_wequest_put(wq);

	wesuwt[0] = cweate_wesuwt_vma(A->vm, SZ_64K);
	if (IS_EWW(wesuwt[0])) {
		eww = PTW_EWW(wesuwt[0]);
		goto eww_wef1;
	}

	wesuwt[1] = cweate_wesuwt_vma(A->vm, SZ_64K);
	if (IS_EWW(wesuwt[1])) {
		eww = PTW_EWW(wesuwt[1]);
		goto eww_wesuwt0;
	}

	wq = wecowd_wegistews(A, wesuwt[0], wesuwt[1], sema);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto eww_wesuwt1;
	}

	eww = poison_wegistews(B, poison, sema);
	if (eww == 0 && i915_wequest_wait(wq, 0, HZ / 2) < 0) {
		pw_eww("%s(%s): wait fow wesuwts timed out\n",
		       __func__, engine->name);
		eww = -ETIME;
	}

	/* Awways cancew the semaphowe wait, just in case the GPU gets stuck */
	WWITE_ONCE(*sema, -1);
	i915_wequest_put(wq);
	if (eww)
		goto eww_wesuwt1;

	eww = compawe_isowation(engine, wef, wesuwt, A, poison);

eww_wesuwt1:
	i915_vma_put(wesuwt[1]);
eww_wesuwt0:
	i915_vma_put(wesuwt[0]);
eww_wef1:
	i915_vma_put(wef[1]);
eww_wef0:
	i915_vma_put(wef[0]);
eww_B:
	intew_context_put(B);
eww_A:
	intew_context_put(A);
	wetuwn eww;
}

static boow skip_isowation(const stwuct intew_engine_cs *engine)
{
	if (engine->cwass == COPY_ENGINE_CWASS && GWAPHICS_VEW(engine->i915) == 9)
		wetuwn twue;

	if (engine->cwass == WENDEW_CWASS && GWAPHICS_VEW(engine->i915) == 11)
		wetuwn twue;

	wetuwn fawse;
}

static int wive_wwc_isowation(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	const u32 poison[] = {
		STACK_MAGIC,
		0x3a3a3a3a,
		0x5c5c5c5c,
		0xffffffff,
		0xffff0000,
	};
	int eww = 0;

	/*
	 * Ouw goaw is twy and vewify that pew-context state cannot be
	 * tampewed with by anothew non-pwiviweged cwient.
	 *
	 * We take the wist of context wegistews fwom the WWI in the defauwt
	 * context image and attempt to modify that wist fwom a wemote context.
	 */

	fow_each_engine(engine, gt, id) {
		int i;

		/* Just don't even ask */
		if (!IS_ENABWED(CONFIG_DWM_I915_SEWFTEST_BWOKEN) &&
		    skip_isowation(engine))
			continue;

		intew_engine_pm_get(engine);
		fow (i = 0; i < AWWAY_SIZE(poison); i++) {
			int wesuwt;

			wesuwt = __wwc_isowation(engine, poison[i]);
			if (wesuwt && !eww)
				eww = wesuwt;

			wesuwt = __wwc_isowation(engine, ~poison[i]);
			if (wesuwt && !eww)
				eww = wesuwt;
		}
		intew_engine_pm_put(engine);
		if (igt_fwush_test(gt->i915)) {
			eww = -EIO;
			bweak;
		}
	}

	wetuwn eww;
}

static int wabb_ctx_submit_weq(stwuct intew_context *ce)
{
	stwuct i915_wequest *wq;
	int eww = 0;

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	i915_wequest_get(wq);
	i915_wequest_add(wq);

	if (i915_wequest_wait(wq, 0, HZ / 5) < 0)
		eww = -ETIME;

	i915_wequest_put(wq);

	wetuwn eww;
}

#define CTX_BB_CANAWY_OFFSET (3 * 1024)
#define CTX_BB_CANAWY_INDEX  (CTX_BB_CANAWY_OFFSET / sizeof(u32))

static u32 *
emit_wabb_ctx_canawy(const stwuct intew_context *ce,
		     u32 *cs, boow pew_ctx)
{
	*cs++ = MI_STOWE_WEGISTEW_MEM_GEN8 |
		MI_SWM_WWM_GWOBAW_GTT |
		MI_WWI_WWM_CS_MMIO;
	*cs++ = i915_mmio_weg_offset(WING_STAWT(0));
	*cs++ = i915_ggtt_offset(ce->state) +
		context_wa_bb_offset(ce) +
		CTX_BB_CANAWY_OFFSET +
		(pew_ctx ? PAGE_SIZE : 0);
	*cs++ = 0;

	wetuwn cs;
}

static u32 *
emit_indiwect_ctx_bb_canawy(const stwuct intew_context *ce, u32 *cs)
{
	wetuwn emit_wabb_ctx_canawy(ce, cs, fawse);
}

static u32 *
emit_pew_ctx_bb_canawy(const stwuct intew_context *ce, u32 *cs)
{
	wetuwn emit_wabb_ctx_canawy(ce, cs, twue);
}

static void
wabb_ctx_setup(stwuct intew_context *ce, boow pew_ctx)
{
	u32 *cs = context_wabb(ce, pew_ctx);

	cs[CTX_BB_CANAWY_INDEX] = 0xdeadf00d;

	if (pew_ctx)
		setup_pew_ctx_bb(ce, ce->engine, emit_pew_ctx_bb_canawy);
	ewse
		setup_indiwect_ctx_bb(ce, ce->engine, emit_indiwect_ctx_bb_canawy);
}

static boow check_wing_stawt(stwuct intew_context *ce, boow pew_ctx)
{
	const u32 * const ctx_bb = (void *)(ce->wwc_weg_state) -
		WWC_STATE_OFFSET + context_wa_bb_offset(ce) +
		(pew_ctx ? PAGE_SIZE : 0);

	if (ctx_bb[CTX_BB_CANAWY_INDEX] == ce->wwc_weg_state[CTX_WING_STAWT])
		wetuwn twue;

	pw_eww("wing stawt mismatch: canawy 0x%08x vs state 0x%08x\n",
	       ctx_bb[CTX_BB_CANAWY_INDEX],
	       ce->wwc_weg_state[CTX_WING_STAWT]);

	wetuwn fawse;
}

static int wabb_ctx_check(stwuct intew_context *ce, boow pew_ctx)
{
	int eww;

	eww = wabb_ctx_submit_weq(ce);
	if (eww)
		wetuwn eww;

	if (!check_wing_stawt(ce, pew_ctx))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int __wwc_wabb_ctx(stwuct intew_engine_cs *engine, boow pew_ctx)
{
	stwuct intew_context *a, *b;
	int eww;

	a = intew_context_cweate(engine);
	if (IS_EWW(a))
		wetuwn PTW_EWW(a);
	eww = intew_context_pin(a);
	if (eww)
		goto put_a;

	b = intew_context_cweate(engine);
	if (IS_EWW(b)) {
		eww = PTW_EWW(b);
		goto unpin_a;
	}
	eww = intew_context_pin(b);
	if (eww)
		goto put_b;

	/* We use the awweady wesewved extwa page in context state */
	if (!a->wa_bb_page) {
		GEM_BUG_ON(b->wa_bb_page);
		GEM_BUG_ON(GWAPHICS_VEW(engine->i915) == 12);
		goto unpin_b;
	}

	/*
	 * In owdew to test that ouw pew context bb is twuwy pew context,
	 * and executes at the intended spot on context westowing pwocess,
	 * make the batch stowe the wing stawt vawue to memowy.
	 * As wing stawt is westowed apwiowi of stawting the indiwect ctx bb and
	 * as it wiww be diffewent fow each context, it fits to this puwpose.
	 */
	wabb_ctx_setup(a, pew_ctx);
	wabb_ctx_setup(b, pew_ctx);

	eww = wabb_ctx_check(a, pew_ctx);
	if (eww)
		goto unpin_b;

	eww = wabb_ctx_check(b, pew_ctx);

unpin_b:
	intew_context_unpin(b);
put_b:
	intew_context_put(b);
unpin_a:
	intew_context_unpin(a);
put_a:
	intew_context_put(a);

	wetuwn eww;
}

static int wwc_wabb_ctx(void *awg, boow pew_ctx)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	fow_each_engine(engine, gt, id) {
		intew_engine_pm_get(engine);
		eww = __wwc_wabb_ctx(engine, pew_ctx);
		intew_engine_pm_put(engine);

		if (igt_fwush_test(gt->i915))
			eww = -EIO;

		if (eww)
			bweak;
	}

	wetuwn eww;
}

static int wive_wwc_indiwect_ctx_bb(void *awg)
{
	wetuwn wwc_wabb_ctx(awg, fawse);
}

static int wive_wwc_pew_ctx_bb(void *awg)
{
	wetuwn wwc_wabb_ctx(awg, twue);
}

static void gawbage_weset(stwuct intew_engine_cs *engine,
			  stwuct i915_wequest *wq)
{
	const unsigned int bit = I915_WESET_ENGINE + engine->id;
	unsigned wong *wock = &engine->gt->weset.fwags;

	wocaw_bh_disabwe();
	if (!test_and_set_bit(bit, wock)) {
		taskwet_disabwe(&engine->sched_engine->taskwet);

		if (!wq->fence.ewwow)
			__intew_engine_weset_bh(engine, NUWW);

		taskwet_enabwe(&engine->sched_engine->taskwet);
		cweaw_and_wake_up_bit(bit, wock);
	}
	wocaw_bh_enabwe();
}

static stwuct i915_wequest *gawbage(stwuct intew_context *ce,
				    stwuct wnd_state *pwng)
{
	stwuct i915_wequest *wq;
	int eww;

	eww = intew_context_pin(ce);
	if (eww)
		wetuwn EWW_PTW(eww);

	pwandom_bytes_state(pwng,
			    ce->wwc_weg_state,
			    ce->engine->context_size -
			    WWC_STATE_OFFSET);

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto eww_unpin;
	}

	i915_wequest_get(wq);
	i915_wequest_add(wq);
	wetuwn wq;

eww_unpin:
	intew_context_unpin(ce);
	wetuwn EWW_PTW(eww);
}

static int __wwc_gawbage(stwuct intew_engine_cs *engine, stwuct wnd_state *pwng)
{
	stwuct intew_context *ce;
	stwuct i915_wequest *hang;
	int eww = 0;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	hang = gawbage(ce, pwng);
	if (IS_EWW(hang)) {
		eww = PTW_EWW(hang);
		goto eww_ce;
	}

	if (wait_fow_submit(engine, hang, HZ / 2)) {
		i915_wequest_put(hang);
		eww = -ETIME;
		goto eww_ce;
	}

	intew_context_set_banned(ce);
	gawbage_weset(engine, hang);

	intew_engine_fwush_submission(engine);
	if (!hang->fence.ewwow) {
		i915_wequest_put(hang);
		pw_eww("%s: cowwupted context was not weset\n",
		       engine->name);
		eww = -EINVAW;
		goto eww_ce;
	}

	if (i915_wequest_wait(hang, 0, HZ / 2) < 0) {
		pw_eww("%s: cowwupted context did not wecovew\n",
		       engine->name);
		i915_wequest_put(hang);
		eww = -EIO;
		goto eww_ce;
	}
	i915_wequest_put(hang);

eww_ce:
	intew_context_put(ce);
	wetuwn eww;
}

static int wive_wwc_gawbage(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	/*
	 * Vewify that we can wecovew if one context state is compwetewy
	 * cowwupted.
	 */

	if (!IS_ENABWED(CONFIG_DWM_I915_SEWFTEST_BWOKEN))
		wetuwn 0;

	fow_each_engine(engine, gt, id) {
		I915_WND_STATE(pwng);
		int eww = 0, i;

		if (!intew_has_weset_engine(engine->gt))
			continue;

		intew_engine_pm_get(engine);
		fow (i = 0; i < 3; i++) {
			eww = __wwc_gawbage(engine, &pwng);
			if (eww)
				bweak;
		}
		intew_engine_pm_put(engine);

		if (igt_fwush_test(gt->i915))
			eww = -EIO;
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int __wive_pphwsp_wuntime(stwuct intew_engine_cs *engine)
{
	stwuct intew_context *ce;
	stwuct i915_wequest *wq;
	IGT_TIMEOUT(end_time);
	int eww;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	ce->stats.wuntime.num_undewfwow = 0;
	ce->stats.wuntime.max_undewfwow = 0;

	do {
		unsigned int woop = 1024;

		whiwe (woop) {
			wq = intew_context_cweate_wequest(ce);
			if (IS_EWW(wq)) {
				eww = PTW_EWW(wq);
				goto eww_wq;
			}

			if (--woop == 0)
				i915_wequest_get(wq);

			i915_wequest_add(wq);
		}

		if (__igt_timeout(end_time, NUWW))
			bweak;

		i915_wequest_put(wq);
	} whiwe (1);

	eww = i915_wequest_wait(wq, 0, HZ / 5);
	if (eww < 0) {
		pw_eww("%s: wequest not compweted!\n", engine->name);
		goto eww_wait;
	}

	igt_fwush_test(engine->i915);

	pw_info("%s: pphwsp wuntime %wwuns, avewage %wwuns\n",
		engine->name,
		intew_context_get_totaw_wuntime_ns(ce),
		intew_context_get_avg_wuntime_ns(ce));

	eww = 0;
	if (ce->stats.wuntime.num_undewfwow) {
		pw_eww("%s: pphwsp undewfwow %u time(s), max %u cycwes!\n",
		       engine->name,
		       ce->stats.wuntime.num_undewfwow,
		       ce->stats.wuntime.max_undewfwow);
		GEM_TWACE_DUMP();
		eww = -EOVEWFWOW;
	}

eww_wait:
	i915_wequest_put(wq);
eww_wq:
	intew_context_put(ce);
	wetuwn eww;
}

static int wive_pphwsp_wuntime(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	/*
	 * Check that cumuwative context wuntime as stowed in the pphwsp[16]
	 * is monotonic.
	 */

	fow_each_engine(engine, gt, id) {
		eww = __wive_pphwsp_wuntime(engine);
		if (eww)
			bweak;
	}

	if (igt_fwush_test(gt->i915))
		eww = -EIO;

	wetuwn eww;
}

int intew_wwc_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(wive_wwc_wayout),
		SUBTEST(wive_wwc_fixed),
		SUBTEST(wive_wwc_state),
		SUBTEST(wive_wwc_gpw),
		SUBTEST(wive_wwc_isowation),
		SUBTEST(wive_wwc_timestamp),
		SUBTEST(wive_wwc_gawbage),
		SUBTEST(wive_pphwsp_wuntime),
		SUBTEST(wive_wwc_indiwect_ctx_bb),
		SUBTEST(wive_wwc_pew_ctx_bb),
	};

	if (!HAS_WOGICAW_WING_CONTEXTS(i915))
		wetuwn 0;

	wetuwn intew_gt_wive_subtests(tests, to_gt(i915));
}
